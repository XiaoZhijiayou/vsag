# SINDI_V2：代码逐段导读

[直观图解](visual_guide.md)

[返回设计说明](README.md) · [所有索引](../README.md)

源码基线：`fd363937`。下面引用真实源码，不将摘录伪装为独立可编译程序。完整实现还包含未展示的检查和分支，请结合链接阅读。

与 SINDI 对照时，把共同评分逻辑和新增 term 读取规划分开。特别看实际读取哪些词项，而非只看窗口循环。

## 1. n_candidate=0 并非返回空候选

源码：[src/algorithm/sindi_v2/sindi_v2.cpp](../../../src/algorithm/sindi_v2/sindi_v2.cpp)，基线行号 783–814。以下为连续原文摘录，可能是函数的一部分。

```cpp
    auto* search_allocator = allocator != nullptr ? allocator : allocator_;

    const auto* sparse_vectors = query->GetSparseVectors();
    CHECK_ARGUMENT(query->GetNumElements() == 1, "num of query should be 1");
    CHECK_ARGUMENT(k > 0, "k must be greater than 0");
    auto sparse_query = sparse_vectors[0];
    CHECK_ARGUMENT(
        sparse_query.len_ > 0,
        fmt::format("query->GetSparseVectors()->len_ ({}) is invalid", sparse_query.len_));
    SearchStatistics statistics;
    if (cur_element_count_ == 0) {
        auto [results, ret_dists, ret_ids] = create_fast_dataset(0, search_allocator);
        results->Statistics(statistics.Dump());
        return results;
    }

    SINDIV2SearchParameter search_param;
    search_param.FromJson(JsonType::Parse(parameters));
    CHECK_ARGUMENT(k <= std::numeric_limits<int64_t>::max() / SPARSE_AMPLIFICATION_FACTOR,
                   "k is too large to derive the SINDI_V2 candidate limit");
    const auto max_candidate_count = SPARSE_AMPLIFICATION_FACTOR * k;
    CHECK_ARGUMENT(search_param.n_candidate <= static_cast<uint64_t>(max_candidate_count),
                   fmt::format("n_candidate ({}) should be less than {} * k ({})",
                               search_param.n_candidate,
                               SPARSE_AMPLIFICATION_FACTOR,
                               k));
    const auto candidate_count = search_param.n_candidate == 0
                                     ? static_cast<uint64_t>(max_candidate_count)
                                     : static_cast<uint64_t>(search_param.n_candidate);
    InnerSearchParam inner_param;
    inner_param.ef = std::max(candidate_count, static_cast<uint64_t>(k));
    inner_param.topk = k;
```

先检查 k 放大不会溢出，再限制外部候选预算；0 被转换为允许的最大候选数，正数保留其值，ef 至少为 k。这个语义是 V2 的代码分支，不能凭参数名称套用别的索引。外部 Filter 通过 InnerIdWrapperFilter 转为内部编号判断。

## 2. 为 query 准备 term 数据

源码：[src/algorithm/sindi_v2/sindi_v2.cpp](../../../src/algorithm/sindi_v2/sindi_v2.cpp)，基线行号 833–865。以下为连续原文摘录，可能是函数的一部分。

```cpp
    Vector<float> tmp_vals(search_allocator);
    if (remap_term_ids_) {
        effective_query = remap_sparse_vector_for_query(sparse_query, tmp_ids, tmp_vals);
    }

    auto computer = std::make_shared<SparseTermComputer>(
        effective_query, search_param, search_allocator, term_datacell_->GetWindowCount());
    const SparseVector* rerank_query = (remap_term_ids_ && use_reorder_) ? &sparse_query : nullptr;

    SindiQueryContext query_context(search_allocator);
    auto query_term_ids = collect_query_term_ids(computer, search_allocator);
    query_context.query_term_buffers =
        term_datacell_->LoadQueryTermBuffers(query_term_ids, search_allocator);
    const bool use_term_lists_heap_insert =
        effective_query.len_ != 0 && UseTermListsHeapInsert(search_param);

    auto result = search_impl<KNN_SEARCH>(computer,
                                          inner_param,
                                          search_allocator,
                                          use_term_lists_heap_insert,
                                          query_context,
                                          rerank_query,
                                          &statistics,
                                          metadata_route);
    result->Statistics(statistics.Dump());
    return result;
}

template <InnerSearchMode mode>
DatasetPtr
SINDIV2::search_impl(const SparseTermComputerPtr& computer,
                     const InnerSearchParam& inner_param,
                     Allocator* allocator,
```

先构建 SparseTermComputer，再收集本次要用的 term IDs，调用 term_datacell_->LoadQueryTermBuffers。查询上下文保存这些缓冲供后续窗口计算使用。rerank_query 保留原始词项坐标，避免重映射污染正排评分。term-first 的实际 IO 入口就在这个调用，而非仅仅存在于序列化函数名中。

## 3. 磁盘 DataCell 去重并筛选有效词项

源码：[src/datacell/disk_sindi_term_datacell.cpp](../../../src/datacell/disk_sindi_term_datacell.cpp)，基线行号 279–321。以下为连续原文摘录，可能是函数的一部分。

```cpp
DiskSindiTermDataCell<IOTmpl>::LoadQueryTermBuffers(const Vector<uint32_t>& query_term_ids,
                                                    Allocator* query_allocator) const {
    auto* allocator = query_allocator == nullptr ? allocator_ : query_allocator;
    QueryTermBuffers query_term_buffers(allocator);
    if (not payload_layout_.IsBound()) {
        return query_term_buffers;
    }

    struct QueryTermReadPlan {
        uint32_t term_id{0};
        DiskTermEntry entry{};
    };

    Vector<QueryTermReadPlan> read_plans(allocator);
    UnorderedSet<uint32_t> planned_terms(allocator);
    read_plans.reserve(query_term_ids.size());
    planned_terms.reserve(query_term_ids.size());
    query_term_buffers.reserve(query_term_ids.size());
    uint32_t window_count = 0;
    uint32_t window_size = 0;
    uint64_t total_count = 0;
    uint64_t payload_size = 0;
    SparseValueQuantizationType sparse_value_quant_type = SparseValueQuantizationType::FP32;
    {
        std::shared_lock lock(term_layout_mutex_);
        window_count = window_count_;
        window_size = window_size_;
        total_count = total_count_;
        payload_size = payload_size_;
        CHECK_ARGUMENT(payloads_validated_, "SINDI_V2 term payloads have not been validated");
        sparse_value_quant_type = sparse_value_quant_type_;
        for (uint32_t term_id : query_term_ids) {
            if (term_id >= term_dict_.size() || planned_terms.contains(term_id)) {
                continue;
            }

            const auto entry = term_dict_[term_id];
            if (entry.posting_count == 0) {
                continue;
            }
            planned_terms.insert(term_id);
            read_plans.push_back({term_id, entry});
        }
```

1. 无绑定 payload 布局时返回空缓冲集合。
2. 在共享布局锁下读取窗口和编码元数据。
3. planned_terms 防止同一词项重复规划，越界和 posting_count=0 的项直接跳过。
4. 锁内取得 entry 快照形成 read_plans，后续读取与解析不需要在这一段里逐项完成。

## 4. 非 mmap 后端批量读取 posting

源码：[src/datacell/disk_sindi_term_datacell.cpp](../../../src/datacell/disk_sindi_term_datacell.cpp)，基线行号 333–378。以下为连续原文摘录，可能是函数的一部分。

```cpp
    const auto value_code_size = sindi_datacell_utils::GetValueCodeSize(sparse_value_quant_type);

    if constexpr (not std::is_same_v<IOTmpl, MMapIO>) {
        Vector<uint64_t> sizes(allocator);
        Vector<uint64_t> offsets(allocator);
        Vector<uint64_t> buffer_offsets(allocator);
        sizes.reserve(read_plans.size());
        offsets.reserve(read_plans.size());
        buffer_offsets.reserve(read_plans.size());

        uint64_t total_payload_size = 0;
        for (const auto& plan : read_plans) {
            validate_entry(plan);

            CHECK_ARGUMENT(plan.entry.posting_payload_size <=
                               std::numeric_limits<uint64_t>::max() - total_payload_size,
                           "SINDI_V2 query term payload size overflow");
            buffer_offsets.push_back(total_payload_size);
            sizes.push_back(plan.entry.posting_payload_size);
            offsets.push_back(plan.entry.posting_payload_offset);
            total_payload_size += plan.entry.posting_payload_size;
        }

        if (not read_plans.empty()) {
            Vector<uint8_t> payloads(total_payload_size, 0, allocator);
            const bool read_succeeded = payload_layout_.MultiRead(
                offsets.data(), sizes.data(), read_plans.size(), payloads.data());
            if (not read_succeeded) {
                throw VsagException(ErrorType::INTERNAL_ERROR,
                                    "failed to batch read SINDI_V2 term payloads");
            }

            for (uint64_t i = 0; i < read_plans.size(); ++i) {
                const auto& plan = read_plans[i];
                auto term_buffer = sindi_datacell_utils::ParseTrustedTermPayload(
                    payloads.data() + buffer_offsets[i],
                    plan.entry.posting_payload_size,
                    plan.entry,
                    window_count,
                    window_size,
                    total_count,
                    value_code_size,
                    allocator);
                query_term_buffers.emplace(plan.term_id, std::move(term_buffer));
            }
        }
```

为每个 term 记录 payload 大小、源偏移和目标缓冲偏移；累加总大小前防溢出。MultiRead 一次表达多个区间的读取需求，但后端是否真正并发由 IO 实现决定。随后按各 term 的偏移解析 payload。mmap 走后续独立借用路径，不能把这段缓冲复制成本套在全部后端上。

## 5. 增量能力是条件组合

源码：[src/algorithm/sindi_v2/sindi_v2.cpp](../../../src/algorithm/sindi_v2/sindi_v2.cpp)，基线行号 1956–1983。以下为连续原文摘录，可能是函数的一部分。

```cpp
SINDIV2::InitFeatures() {
    this->index_feature_list_->SetFeatures({
        IndexFeature::SUPPORT_BUILD,
        IndexFeature::SUPPORT_BUILD_WITH_MULTI_THREAD,
        IndexFeature::SUPPORT_KNN_SEARCH,
        IndexFeature::SUPPORT_KNN_SEARCH_WITH_ID_FILTER,
        IndexFeature::SUPPORT_RANGE_SEARCH,
        IndexFeature::SUPPORT_RANGE_SEARCH_WITH_ID_FILTER,
        IndexFeature::SUPPORT_SERIALIZE_FILE,
        IndexFeature::SUPPORT_SERIALIZE_BINARY_SET,
        IndexFeature::SUPPORT_DESERIALIZE_FILE,
        IndexFeature::SUPPORT_DESERIALIZE_BINARY_SET,
        IndexFeature::SUPPORT_DESERIALIZE_READER_SET,
        IndexFeature::SUPPORT_CLONE,
        IndexFeature::SUPPORT_ESTIMATE_MEMORY,
        IndexFeature::SUPPORT_CAL_DISTANCE_BY_ID,
        IndexFeature::SUPPORT_GET_RAW_VECTOR_BY_IDS,
        IndexFeature::SUPPORT_SEARCH_CONCURRENT,
        IndexFeature::SUPPORT_METRIC_TYPE_INNER_PRODUCT,
    });
    if (not immutable_enabled_) {
        this->index_feature_list_->SetFeature(IndexFeature::SUPPORT_BATCH_CALC_DISTANCE_BY_ID);
    }
    if (not immutable_enabled_ && rerank_type_ != SPARSE_RERANK_TYPE_DMQ8 &&
        param_->term_io_parameter->GetTypeName() == IO_TYPE_VALUE_MEMORY_IO) {
        this->index_feature_list_->SetFeature(IndexFeature::SUPPORT_ADD_AFTER_BUILD);
    }
}
```

常规搜索和持久化能力先统一声明；Add-after-Build 只有在非 immutable、非 DMQ8 rerank 且 term 后端为 memory_io 时启用。这个条件把存储可写性与正排维护限制明确结合起来。存在 Add 方法不代表任意加载后的实例都支持 Add。

## 读完以后应能解释

为什么 term-first 读取之后仍需要 window offset？planned_terms 消除了哪种重复 IO？MultiRead 是否意味着所有后端都异步？为什么更换 term_io 会改变 Add 能力？
