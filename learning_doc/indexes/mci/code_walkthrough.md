# MCI：代码逐段导读

[直观图解](visual_guide.md)

[返回设计说明](README.md) · [所有索引](../README.md)

源码基线：`fd363937`。下面引用真实源码，不将摘录伪装为独立可编译程序。完整实现还包含未展示的检查和分支，请结合链接阅读。

先看 HGraph 是否真的选择 MCI，再看挂件内部搜索。没有满足路由条件时，仅设置 use_mci 也不一定执行团搜索。

## 1. MCI 的完整路由前置条件

源码：[src/algorithm/hgraph/hgraph_mci.cpp](../../../src/algorithm/hgraph/hgraph_mci.cpp)，基线行号 525–546。以下为连续原文摘录，可能是函数的一部分。

```cpp
HGraph::try_mci_search(const SearchRequest& request,
                       const HGraphSearchParameters& params,
                       const FilterPtr& inner_filter,
                       const void* query,
                       const InnerSearchParam& search_param,
                       QueryContext* ctx) const {
    MCIHybridSearchResult result(params, inner_filter);
    const bool bitset_seed_source = has_bitset_source(request.filter_);
    const bool can_use_mci = params.use_mci and this->mci_parameters_.enabled and
                             search_param.executors.empty() and
                             (has_valid_id_source(request.filter_) or bitset_seed_source) and
                             this->mci_cliques_ != nullptr and
                             this->mci_cliques_->HasCliqueIndex(this->total_count_.load());
    if (not can_use_mci) {
        return result;
    }

    result.route = "hgraph";
    if (request.mode_ == SearchMode::RANGE_SEARCH or result.valid_ratio >= result.threshold) {
        return result;
    }

```

1. 查询启用、构建启用、团索引存在且覆盖当前数据，都是必要检查。
2. 还需要可用 seed 来源，并且这条路径要求 executors 为空。
3. RangeSearch 或有效比例高于阈值会返回普通路径。
4. 因此“有 Filter 且 ValidRatio 小”不是唯一条件，不能据此承诺所有自定义过滤器都走 MCI。

## 2. seed 预算与实际 seed 数

源码：[src/algorithm/hgraph/hgraph_mci.cpp](../../../src/algorithm/hgraph/hgraph_mci.cpp)，基线行号 548–574。以下为连续原文摘录，可能是函数的一部分。

```cpp
    const auto total_count = this->total_count_.load();
    const auto scaled_seed_count = std::ceil(std::sqrt(static_cast<double>(total_count)) *
                                             static_cast<double>(params.mci_seed_ratio));
    mci_param.seed_count = scaled_seed_count >= static_cast<double>(total_count)
                               ? total_count
                               : std::max<uint64_t>(1, static_cast<uint64_t>(scaled_seed_count));
    mci_param.hops_limit = search_param.hops_limit;

    Vector<InnerIdType> seed_inner_ids(ctx->alloc);
    if (bitset_seed_source) {
        seed_inner_ids = collect_bitset_seed_inner_ids(
            inner_filter, total_count, mci_param.seed_count, ctx->alloc);
    } else {
        std::shared_lock label_lock(this->label_lookup_mutex_);
        seed_inner_ids = collect_seed_inner_ids(
            request.filter_, this->label_table_, mci_param.seed_count, ctx->alloc);
    }
    result.seed_count = seed_inner_ids.size();
    mci_param.seed_count = result.seed_count;
    mci_param.seed_inner_ids = &seed_inner_ids;
    if (seed_inner_ids.empty()) {
        return result;
    }

    std::shared_lock<std::shared_mutex> codes_lock(this->persistent_codes_mutex_);
    auto precise_flatten = this->get_precise_codes();
    if (precise_flatten != nullptr) {
```

目标数是 ceil(sqrt(total_count)×ratio)，再限制在数据规模内并设置至少 1 的目标。随后根据 bitset 或有效 ID 源真正收集 seed；实际数可能小于目标，甚至为 0。最终把实际 vector 大小回写统计和参数，空 seed 时退出该尝试。

## 3. epoch 标记如何避免每次清零

源码：[src/impl/searcher/mci_searcher.cpp](../../../src/impl/searcher/mci_searcher.cpp)，基线行号 38–78。以下为连续原文摘录，可能是函数的一部分。

```cpp
    std::vector<uint16_t> marks;
    uint16_t tag{1};

    void
    Reset(uint64_t size) {
        if (marks.size() < size) {
            marks.assign(size, 0);
            tag = 1;
            return;
        }
        ++tag;
        if (tag == 0) {
            std::memset(marks.data(), 0, marks.size() * sizeof(uint16_t));
            tag = 1;
        }
    }

    [[nodiscard]] bool
    Get(InnerIdType id) const {
        return id < marks.size() and marks[id] == tag;
    }

    void
    Set(InnerIdType id) {
        if (id >= marks.size()) {
            marks.resize(static_cast<uint64_t>(id) + 1, 0);
        }
        marks[id] = tag;
    }
};

bool
mci_check_overtime(const InnerSearchParam& inner_search_param, QueryContext* ctx) {
    if (inner_search_param.time_cost == nullptr or
        not inner_search_param.time_cost->CheckOvertime()) {
        return false;
    }
    if (ctx != nullptr and ctx->stats != nullptr) {
        ctx->stats->is_timeout.store(true, std::memory_order_relaxed);
    }
    return true;
```

Reset 在容量不足时重新分配，否则只增加 tag；tag 回绕到 0 才完整清零。Get 比较当前 tag，Set 写入当前 tag。这将多数查询的“初始化全部 visited”变成常量工作，但数组增长和回绕仍会产生额外成本，不能声称永远无需清理。

## 4. 节点和团分别维护 visited

源码：[src/impl/searcher/mci_searcher.cpp](../../../src/impl/searcher/mci_searcher.cpp)，基线行号 118–140。以下为连续原文摘录，可能是函数的一部分。

```cpp
                         uint64_t dim,
                         uint64_t precise_vector_stride,
                         MetricType metric,
                         InnerIdType total,
                         const InnerSearchParam& inner_search_param,
                         const MCISearcherParam& mci_param,
                         QueryContext* ctx,
                         Allocator* allocator) {
    const auto candidate_limit =
        std::max<int64_t>(inner_search_param.topk, static_cast<int64_t>(inner_search_param.ef));
    auto result_heap = DistanceHeap::MakeInstanceBySize<true, true>(allocator, candidate_limit);
    thread_local MCIEpochMarks visited_nodes;
    thread_local MCIEpochMarks visited_cliques;
    SearchCandidateQueue candidates(allocator);
    visited_nodes.Reset(total);
    visited_cliques.Reset(view.total_clique_count);
    candidates.Reset(static_cast<uint64_t>(candidate_limit));
    uint32_t dist_cmp = 0;

    const auto cosine_query_inv_norm = metric == MetricType::METRIC_TYPE_COSINE
                                           ? calc_mci_cosine_query_inv_norm(query, dim)
                                           : 1.0F;
    const auto cosine_hold_mold =
```

这里是连续 FP32 CSR 的专用路径。candidate_limit 同时考虑 topk 与 ef；visited_nodes 和 visited_cliques 使用两个 thread_local 标记数组。团去重减少重复扩展同一个组，节点去重减少重复距离计算，两者不能互相替代。专用路径之外还要按真实编码与存储继续看后面的实现。

## 读完以后应能解释

为什么 use_mci=true 仍可能返回普通 HGraph 路由？目标 seed 数和实际 seed 数为何不同？为什么需要节点和团两种 visited？额外 membership 存储在哪个统计量里体现？
