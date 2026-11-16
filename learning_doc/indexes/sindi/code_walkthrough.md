# SINDI：代码逐段导读

[直观图解](visual_guide.md)

[返回设计说明](README.md) · [所有索引](../README.md)

源码基线：`fd363937`。下面引用真实源码，不将摘录伪装为独立可编译程序。完整实现还包含未展示的检查和分支，请结合链接阅读。

稀疏检索要同时看索引调度、SparseTermComputer 和 term DataCell。下列片段展示如何把一个 query 变成窗口累加过程。

## 1. query 与候选预算校验

源码：[src/algorithm/sindi/sindi.cpp](../../../src/algorithm/sindi/sindi.cpp)，基线行号 722–751。以下为连续原文摘录，可能是函数的一部分。

```cpp
SINDI::KnnSearch(const DatasetPtr& query,
                 int64_t k,
                 const std::string& parameters,
                 const FilterPtr& filter,
                 vsag::Allocator* allocator) const {
    std::shared_lock rlock(this->global_mutex_);

    const auto* sparse_vectors = query->GetSparseVectors();
    CHECK_ARGUMENT(query->GetNumElements() == 1, "num of query should be 1");
    auto sparse_query = sparse_vectors[0];
    CHECK_ARGUMENT(
        sparse_query.len_ > 0,
        fmt::format("query->GetSparseVectors()->len_ ({}) is invalid", sparse_query.len_));

    // search parameter
    SINDISearchParameter search_param;
    search_param.FromJson(JsonType::Parse(parameters));
    const auto threshold = ParseSearchThreshold(parameters);
    CHECK_ARGUMENT(search_param.n_candidate <= SPARSE_AMPLIFICATION_FACTOR * k,
                   fmt::format("n_candidate ({}) should be less than {} * k ({})",
                               search_param.n_candidate,
                               AMPLIFICATION_FACTOR,
                               k));
    InnerSearchParam inner_param;
    inner_param.ef = std::max(static_cast<int64_t>(search_param.n_candidate), k);
    inner_param.topk = threshold.has_value() ? static_cast<int64_t>(inner_param.ef) : k;
    inner_param.distance_threshold = threshold;
    inner_param.enable_reorder = use_reorder_;

    auto filter_callback_remaining =
```

当前入口要求单条 sparse query；n_candidate 受 k 的放大倍数约束。内部 ef 至少为 k，threshold 存在时保留预算的处理也不同。因此不能把外部 n_candidate 原样视为最后输出数量。这里持有共享锁，写入同步要继续看 Add/Build。

## 2. 元数据路由与词项重映射

源码：[src/algorithm/sindi/sindi.cpp](../../../src/algorithm/sindi/sindi.cpp)，基线行号 763–793。以下为连续原文摘录，可能是函数的一部分。

```cpp
        result->Statistics(statistics.Dump());
        return result;
    }
    metadata_filter_.ApplyFilter(metadata_route, inner_param.is_inner_id_allowed);
    SparseVector effective_query = sparse_query;
    Vector<uint32_t> tmp_ids(allocator);
    Vector<float> tmp_vals(allocator);
    if (remap_term_ids_) {
        effective_query = remap_sparse_vector_for_query(sparse_query, tmp_ids, tmp_vals);
        if (effective_query.len_ == 0) {
            auto result = make_empty_result();
            result->Statistics(statistics.Dump());
            return result;
        }
    }

    auto computer = std::make_shared<SparseTermComputer>(
        effective_query, search_param, allocator_, term_datacell_->GetWindowCount());
    const SparseVector* rerank_query = (remap_term_ids_ && use_reorder_) ? &sparse_query : nullptr;
    auto result = search_impl<KNN_SEARCH>(computer,
                                          inner_param,
                                          allocator,
                                          UseTermListsHeapInsert(search_param, threshold),
                                          rerank_query,
                                          nullptr,
                                          &statistics,
                                          filter_callback_remaining_ptr,
                                          metadata_route);
    result->Statistics(statistics.Dump());
    return FilterDatasetByThreshold(result, threshold, allocator, k);
}
```

metadata_route 可以直接判空，或给已有过滤器加上范围约束。重映射后没有已知词项时也直接返回空结果。粗排使用内部 term ID；需要重排时保留原始 sparse_query，让原始正排表示有正确的查询坐标。两套编号混用会让同一个 term 对错权重。

## 3. 临时数组只覆盖一个窗口

源码：[src/algorithm/sindi/sindi.cpp](../../../src/algorithm/sindi/sindi.cpp)，基线行号 815–836。以下为连续原文摘录，可能是函数的一部分。

```cpp
    // window iteration
    Vector<float> dists(window_size_, 0.0F, search_allocator);
    auto filter = inner_param.is_inner_id_allowed;
    auto [min_window_id, max_window_id] = this->get_min_max_window_id(filter);
    SindiMetadataFilter::ApplyWindowRoute(
        metadata_route, window_size_, min_window_id, max_window_id);
    auto selected_buckets = reasoning_ctx != nullptr
                                ? std::make_unique<Vector<BucketIdType>>(search_allocator)
                                : nullptr;
    SindiQueryContext query_context(search_allocator);
    for (auto cur = min_window_id; cur <= max_window_id; ++cur) {
        cur = metadata_filter_.NextMatchingWindow(metadata_route, window_size_, cur, max_window_id);
        if (cur > max_window_id) {
            break;
        }
        const auto window_id = static_cast<uint32_t>(cur);
        const auto window_start_id = window_id * window_size_;
        computer->SetTermPruneEnabled(
            not metadata_filter_.RequiresFullTermScan(metadata_route, window_id, window_size_));
        // compute
        term_datacell_->QueryWindow(
            dists.data(), window_id, computer, use_term_lists_heap_insert, query_context);
```

1. dists 的长度是 window_size_，不是全体文档数。
2. 先根据过滤器得到窗口范围，再应用 metadata 路由进一步跳过不相关窗口。
3. window_start_id 将局部窗口编号转回全局内部 ID。
4. 每窗可以调整 term 剪枝开关，再调用 QueryWindow。元数据条件可能改变剪枝策略，不能认为所有窗口使用相同近似路径。

## 4. 构建入口区分 mutable 与 immutable

源码：[src/algorithm/sindi/sindi.cpp](../../../src/algorithm/sindi/sindi.cpp)，基线行号 547–570。以下为连续原文摘录，可能是函数的一部分。

```cpp
SINDI::Build(const DatasetPtr& base) {
    if (immutable_enabled_) {
        return this->build_immutable(base);
    }
    std::scoped_lock wlock(this->global_mutex_);
    CHECK_ARGUMENT(base->GetNumElements() > 0, "data_num is zero when add vectors");
    auto failed_ids = this->add(base, false);
    mutable_term_datacell_->Finalize();
    this->cal_memory_usage();
    return failed_ids;
}

std::vector<int64_t>
SINDI::build_immutable(const DatasetPtr& base) {
    std::scoped_lock wlock(this->global_mutex_);
    CHECK_ARGUMENT(immutable_enabled_, "mutable SINDI cannot use immutable build");
    CHECK_ARGUMENT(not immutable_build_started_, "immutable SINDI has already been built");

    const auto data_num = base->GetNumElements();
    CHECK_ARGUMENT(data_num > 0, "data_num is zero when build immutable SINDI");
    const auto* sparse_vectors = base->GetSparseVectors();
    const auto* ids = base->GetIds();
    const auto* extra_info = base->GetExtraInfos();
    const auto extra_info_size = base->GetExtraInfoSize();
```

Build 根据 immutable_enabled_ 选择不同路径；普通路径复用 add，之后做构建需要的处理。紧凑 immutable 布局并不是给 mutable 对象简单加一个只读布尔值，后面的专门构建逻辑会组织不同的数据表示。具体是否允许后续 Add 需要检查能力声明和 Add 检查。

## 5. Add 入口先保护可写状态

源码：[src/algorithm/sindi/sindi.cpp](../../../src/algorithm/sindi/sindi.cpp)，基线行号 430–465。以下为连续原文摘录，可能是函数的一部分。

```cpp
SINDI::Add(const DatasetPtr& base) {
    std::scoped_lock wlock(this->global_mutex_);
    CHECK_ARGUMENT(not immutable_enabled_, "immutable SINDI runtime does not support Add");
    if (rerank_type_ == SPARSE_RERANK_TYPE_DMQ8 and
        cur_element_count_.load(std::memory_order_relaxed) != 0) {
        throw VsagException(ErrorType::UNSUPPORTED_INDEX_OPERATION,
                            "SINDI DMQ rerank does not support incremental Add");
    }
    const auto previous_window_count = mutable_term_datacell_->GetWindowCount();
    auto failed_ids = this->add(base, true);
    if (mutable_term_datacell_->GetWindowCount() != previous_window_count) {
        this->cal_memory_usage();
    }
    return failed_ids;
}

std::vector<int64_t>
SINDI::add(const DatasetPtr& base, bool sort_affected_windows) {
    CHECK_ARGUMENT(mutable_term_datacell_ != nullptr, "mutable SINDI data cell is not initialized");
    std::vector<int64_t> failed_ids;

    auto data_num = base->GetNumElements();
    CHECK_ARGUMENT(data_num > 0, "data_num is zero when add vectors");
    const auto current_element_count = cur_element_count_.load(std::memory_order_relaxed);
    auto metadata_build = metadata_filter_.PrepareBuild(base, current_element_count);
    const auto first_inner_id = static_cast<uint32_t>(current_element_count);

    const auto* sparse_vectors = base->GetSparseVectors();
    const auto* ids = base->GetIds();
    const auto* extra_info = base->GetExtraInfos();
    const auto extra_info_size = base->GetExtraInfoSize();

    if (sparse_value_quant_type_ == SparseValueQuantizationType::SQ8 && cur_element_count_ == 0) {
        this->init_quantization_params_from_vectors(base);
    }

```

外层 Add 先取得写锁并拒绝 immutable 追加，然后委托内部 add。内部 add 准备输入、metadata 和可变 term DataCell。这样 QueryWindow 可以面对相对统一的查询接口，而写入路径仍明确要求可变实现。这里尚未展开完整逐文档插入，继续向下跟 sort/prune、InsertVector 和失败 ID 列表。

## 6. 进入 QueryWindow：逐词项选择实际扫描量

源码：[src/datacell/mutable_sindi_term_datacell.cpp](../../../src/datacell/mutable_sindi_term_datacell.cpp)，基线行号 214–262。以下是连续原文摘录。

```cpp
MutableSindiTermDataCell::QueryWindow(float* dists,
                                      uint32_t window_id,
                                      const SparseTermComputerPtr& computer,
                                      bool use_term_lists_heap_insert,
                                      SindiQueryContext& query_context) const {
    (void)use_term_lists_heap_insert;
    CHECK_ARGUMENT(window_id < windows_.size(), "mutable SINDI window id out of range");
    const auto& window = windows_[window_id];
    while (computer->HasNextTerm()) {
        auto it = computer->NextTermIter();
        auto term = computer->GetTerm(it);
        if (computer->HasNextTerm()) {
            auto next_it = it + 1;
            auto next_term = computer->GetTerm(next_it);
            if (next_term < window.term_ids_.size() && window.term_ids_[next_term]) {
                __builtin_prefetch(window.term_ids_[next_term]->data(), 0, 3);
                __builtin_prefetch(window.term_datas_[next_term]->data(), 0, 3);
            }
        }
        if (term >= window.term_sizes_.size() || window.term_sizes_[term] == 0) {
            continue;
        }

        const auto posting_count = window.term_sizes_[term];
        const auto term_size = computer->GetTermScanCount(posting_count);
        query_context.has_untracked_approximate_evaluations |= term_size > 0;

        if (sparse_value_quant_type_ == SparseValueQuantizationType::SQ8) {
            computer->ScanForAccumulateSQ8(it,
                                           window.term_ids_[term]->data(),
                                           window.term_datas_[term]->data(),
                                           term_size,
                                           dists);
        } else if (sparse_value_quant_type_ == SparseValueQuantizationType::FP16) {
            computer->ScanForAccumulateFP16Bytes(it,
                                                 window.term_ids_[term]->data(),
                                                 window.term_datas_[term]->data(),
                                                 term_size,
                                                 dists);
        } else {
            computer->ScanForAccumulateFloatBytes(it,
                                                  window.term_ids_[term]->data(),
                                                  window.term_datas_[term]->data(),
                                                  term_size,
                                                  dists);
        }
    }
    computer->ResetTerm();
}
```

Computer 逐项提供 query term；当前窗口无该词项则跳过。GetTermScanCount 将 posting_count 转成实际扫描数量，剪枝在这里影响访问量。SQ8、FP16 与 FP32 分支调用不同累加内核，所以窗口调度无需自己解码所有格式。循环结束 ResetTerm，让下一个窗口可以重新遍历 query term；分数数组的清理还要结合 InsertHeapByWindow 等后续路径看，ResetTerm 只重置词项迭代器。

## 读完以后应能解释

window_start_id 与局部 doc ID 怎样组合？重排为何可能需要原始 query？doc 剪枝与 query 剪枝各改变哪一份数据？临时 dists 如何在不同窗口之间初始化或复用，应继续到 QueryWindow 核对。
