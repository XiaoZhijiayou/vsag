# HGraph：代码逐段导读

[直观图解](visual_guide.md) · [遍历路由专章](traversal_walkthrough.md)

[返回设计说明](README.md) · [所有索引](../README.md)

源码基线：`fd363937`。下面引用真实源码，不将摘录伪装为独立可编译程序。完整实现还包含未展示的检查和分支，请结合链接阅读。

先看组件成员与 Build 分支，再沿普通 SearchWithRequest 阅读。上层导航、底层扩展和重排是三个阶段，专用快路径可能将其中部分工作融合。

## 1. 向量编码与图边分开保存

源码：[src/algorithm/hgraph/hgraph.h](../../../src/algorithm/hgraph/hgraph.h)，基线行号 894–927。以下为连续原文摘录，可能是函数的一部分。

```cpp
    try_join_mci_clique(InnerIdType new_inner_id, const Vector<InnerIdType>& knn_ids);

    void
    build_incremental_mci_clique(InnerIdType new_inner_id, const Vector<InnerIdType>& knn_ids);

private:
    FlattenInterfacePtr basic_flatten_codes_{nullptr};  // coarse/quantized codes for graph search
    std::shared_ptr<FlattenOptimizedBuildInterface> optimized_build_codes_{nullptr};
    FlattenInterfacePtr high_precise_codes_{nullptr};  // precise codes for reorder (optional)
    std::shared_ptr<CodeSlotMap> code_slot_map_{nullptr};

    Vector<GraphInterfacePtr> route_graphs_;   // upper-layer route graphs
    GraphInterfacePtr bottom_graph_{nullptr};  // base-level graph (all vectors)
    std::shared_ptr<HGraphRaBitQFusedDataCell> rabitq_fused_datacell_{nullptr};
    std::shared_ptr<RaBitQSplitDataCellInterface> rabitq_split_codes_{nullptr};
    std::shared_ptr<HGraphRaBitQSearcher> rabitq_fused_searcher_{nullptr};
    SparseGraphDatacellParamPtr hierarchical_datacell_param_{nullptr};  // params for route graphs

    bool use_elp_optimizer_{false};  // enable ELP edge-link pruning
    bool ignore_reorder_{false};     // skip reorder even if configured
    bool build_by_base_{false};      // build graph using base (not quantized) codes
    bool reorder_by_base_{false};    // use base codes for reorder (no separate precise)

    BasicSearcherPtr searcher_;              // single-thread graph searcher
    MCISearcherPtr mci_searcher_;            // companion MCI clique searcher
    ParallelSearcherPtr parallel_searcher_;  // multi-thread graph searcher

    std::default_random_engine level_generator_{
        2021};          // random number generator for level sampling
    double mult_{1.0};  // level multiplier (1/ln(max_degree))

    InnerIdType entry_point_id_{INVALID_ENTRY_POINT};  // top-level entry point

    ODescentParameterPtr odescent_param_{nullptr};  // ODescent build parameters
```

`basic_flatten_codes_` 负责基础评分，`high_precise_codes_` 用于需要独立精排表示的配置；`route_graphs_` 和 `bottom_graph_` 存邻接关系。入口 ID 是导航起点。理解这些成员后，就能区分一条调用是在“读取边”还是“读取向量”。融合 RaBitQ 的成员说明这里还允许专用组合结构，不能把分层理解成强制物理分离。

## 2. Build 实际选择什么路径

源码：[src/algorithm/hgraph/hgraph_build.cpp](../../../src/algorithm/hgraph/hgraph_build.cpp)，基线行号 155–193。以下为连续原文摘录，可能是函数的一部分。

```cpp
HGraph::Build(const DatasetPtr& data) {
    CHECK_ARGUMENT(GetNumElements() == 0, "index is not empty");
    if (this->rabitq_fused_datacell_ != nullptr) {
        this->validate_add_data(data);
    }
    this->build_cache_hit_rate_ = -1.0F;
    this->build_cache_hit_nodes_ = 0;
    this->build_cache_missed_nodes_ = 0;
    std::vector<int64_t> ret;
    const bool using_build_cache = this->has_loaded_cache();
    if (using_build_cache) {
        this->check_fused_mutation_supported("Build with imported cache");
        if (this->using_dedup_storage()) {
            throw VsagException(ErrorType::INVALID_ARGUMENT,
                                "HGraph deduplicate_storage does not support build_with_cache");
        }
        // A previously exported cache has been imported via ImportCache().
        // Take the accelerated build path that warm-starts neighbours from
        // the cache and refines them, instead of building from scratch.
        ret = this->build_with_cache(data);
    } else {
        auto optimized_result = this->try_optimized_build(data);
        if (optimized_result.has_value()) {
            ret = std::move(optimized_result.value());
        } else if (graph_type_ == GRAPH_TYPE_VALUE_NSW) {
            ret = this->add_impl(data);
        } else {
            ret = this->build_by_odescent(data);
        }
    }
    if (use_elp_optimizer_) {
        elp_optimize();
    }
    if (this->mci_parameters_.enabled and
        (using_build_cache or graph_type_ != GRAPH_TYPE_VALUE_NSW)) {
        this->build_mci_clique_index(ret.empty() ? this->get_data(data) : nullptr);
    }
    return ret;
}
```

1. 必须在空索引上 Build，并重置构建缓存统计。
2. 已导入缓存时进入 build_with_cache；去重存储与该路径存在显式互斥。
3. 否则先尝试优化构建，未命中再选择 NSW 的 add_impl 或 ODescent。训练与编码准备下沉在所选路径中，不是这段代码直接统一调用一次 Train。
4. 末尾按条件做 ELP 或 MCI 处理，所以 Build 的总成本不能只按插入节点计算。

## 3. 查询建立请求级状态与锁

源码：[src/algorithm/hgraph/hgraph_search.cpp](../../../src/algorithm/hgraph/hgraph_search.cpp)，基线行号 509–568。以下为连续原文摘录，可能是函数的一部分。

```cpp
HGraph::SearchWithRequest(const SearchRequest& request) const {
    ValidateSearchThreshold(request.threshold_);
    SearchStatistics stats;
    QueryContext ctx{.alloc = this->allocator_, .stats = &stats};
    if (request.search_allocator_ != nullptr) {
        ctx.alloc = request.search_allocator_;
    }

    const auto& query = request.query_;
    bool is_range = (request.mode_ == SearchMode::RANGE_SEARCH);
    auto k = request.topk_;
    const bool use_custom_distance = request.distance_batch_func_ != nullptr;

    if (use_custom_distance) {
        CHECK_ARGUMENT(request.distance_batch_size_ > 0,
                       "distance_batch_size must be greater than 0");
        CHECK_ARGUMENT(not is_range, "HGraph custom distance only supports KNN search");
    }

    if (is_range) {
        if (not use_custom_distance) {
            this->validate_range_args(query, request.radius_, request.limited_size_);
        }
    } else {
        if (not use_custom_distance) {
            this->validate_knn_args(query, k);
        } else {
            CHECK_ARGUMENT(k > 0, "topk must be greater than 0");
        }
    }

    auto params = HGraphSearchParameters::FromJson(request.params_str_);
    ctx.rabitq_error_rate = params.rabitq_error_rate;
    ctx.enable_rabitq_reorder = params.enable_reorder;

    if (use_custom_distance) {
        CHECK_ARGUMENT(params.parallel_search_thread_count == 1,
                       "HGraph custom query distance does not support parallel search");
        CHECK_ARGUMENT(params.brute_force_threshold <= 0.0F,
                       "HGraph custom query distance does not support brute_force_threshold");
    }

    CHECK_ARGUMENT(  // NOLINT
        params.ef_search >= 1,
        fmt::format("ef_search({}) must be at least 1", params.ef_search));

    std::shared_lock<std::shared_mutex> force_remove_rlock;
    std::shared_lock<std::shared_mutex> shared_lock;
    if (!this->immutable_.load(std::memory_order_acquire)) {
        if (this->support_force_remove()) {
            force_remove_rlock = std::shared_lock<std::shared_mutex>(this->force_remove_mutex_);
        }
        shared_lock = this->acquire_global_read_lock();
    }
    const auto element_count = GetNumElements();
    if (element_count == 0) {
        return make_empty_dataset_with_stats(stats);
    }
    k = std::min(k, element_count);
    const auto* raw_query = use_custom_distance ? nullptr : get_data(query);
```

1. `ctx.alloc` 可由请求覆盖，临时查询分配不必全部使用索引分配器。
2. KNN、RangeSearch、自定义距离分别有参数限制。
3. 搜索参数经过 FromJson，`ef_search >= 1` 是显式不变量。
4. immutable、强制删除支持与全局读锁共同决定同步方式。
5. k 被裁剪到有效元素数，防止后续把请求大小误当作可返回数量。

## 4. 底层搜索可能改走扫描或 MCI

源码：[src/algorithm/hgraph/hgraph_search.cpp](../../../src/algorithm/hgraph/hgraph_search.cpp)，基线行号 765–800。以下为连续原文摘录，可能是函数的一部分。

```cpp

    DistHeapPtr search_result;
    bool brute_force_used = false;
    bool fused_search_finalized = false;
    MCIHybridSearchResult mci_result(params, ft);
    if (not use_custom_distance) {
        if (params.brute_force_threshold > 0.0F and
            mci_result.valid_ratio <= params.brute_force_threshold) {
            if (is_range) {
                search_result = this->brute_force_search<InnerSearchMode::RANGE_SEARCH>(
                    raw_query, ft, request.limited_size_, request.radius_, &ctx);
            } else {
                search_result = this->brute_force_search<InnerSearchMode::KNN_SEARCH>(
                    raw_query, ft, k, 0.0F, &ctx, request.threshold_);
            }
            brute_force_used = true;
            mci_result.route = "brute_force";
        } else {
            mci_result = this->try_mci_search(request, params, ft, raw_query, search_param, &ctx);
            if (mci_result.route == "mci") {
                search_result = std::move(mci_result.result);
            } else {
                search_result = this->search_one_graph(raw_query,
                                                       this->bottom_graph_,
                                                       this->basic_flatten_codes_,
                                                       search_param,
                                                       vt,
                                                       &ctx,
                                                       rabitq_candidates_ptr,
                                                       &fused_search_finalized);
            }
        }
    } else {
        search_result = this->search_one_graph(raw_query,
                                               this->bottom_graph_,
                                               this->basic_flatten_codes_,
```

1. `brute_force_threshold` 比较的是当前有效比例，不是某个固定 N 阈值。
2. 满足扫描回退条件时直接对有效集合评分；否则先尝试 MCI。
3. MCI 没有接管时才调用 bottom_graph 的 search_one_graph。
4. 分支结果统一为距离堆，便于后续转换。性能统计应记录实际 route，不能只凭索引名断定本次发生了图搜索。

## 5. 为什么精排前有多重判断

源码：[src/algorithm/hgraph/hgraph_search.cpp](../../../src/algorithm/hgraph/hgraph_search.cpp)，基线行号 813–841。以下为连续原文摘录，可能是函数的一部分。

```cpp
    // Reorder
    if (not fused_search_already_reranked and mci_result.route != "mci" and not brute_force_used and
        use_reorder_ and search_param.enable_reorder) {
        auto limit = is_range ? request.limited_size_ : k;
        if (not is_range and this->use_conjugate_graph_ and params.use_conjugate_graph_search) {
            limit = std::max(limit, LOOK_AT_K);
        }
        auto reorder_threshold = is_range ? std::nullopt : request.threshold_;
        this->reorder(raw_query,
                      this->get_reorder_codes(),
                      search_result,
                      limit,
                      nullptr,
                      ctx,
                      rabitq_candidates_ptr,
                      reorder_threshold);
    } else if (not fused_search_already_reranked and mci_result.route != "mci" and
               not brute_force_used and search_param.enable_reorder and
               params.rabitq_one_bit_search) {
        auto limit = is_range ? request.limited_size_ : k;
        if (not is_range and this->use_conjugate_graph_ and params.use_conjugate_graph_search) {
            limit = std::max(limit, LOOK_AT_K);
        }
        auto reorder_threshold = is_range ? std::nullopt : request.threshold_;
        this->reorder(raw_query,
                      this->basic_flatten_codes_,
                      search_result,
                      limit,
                      nullptr,
```

融合路径可能已完成重排，MCI 和暴力分支也有自身评分语义；统一再重排一次可能浪费计算或破坏设计。因此需要 `fused_search_already_reranked`、route 与 `brute_force_used` 判断。普通精排的 codes 来自 `get_reorder_codes()`，并不保证一定是一份单独 FP32。k/范围限制决定重排后保留量。

## 6. 核心循环：扩展候选与停止条件

源码：[src/impl/searcher/basic_searcher.cpp](../../../src/impl/searcher/basic_searcher.cpp)，基线行号 222–245。以下是连续原文摘录。

```cpp
    while (not candidate_set->Empty()) {
        ++hops;
        if (hops >= inner_search_param.hops_limit) {
            break;
        }
        if constexpr (mode == InnerSearchMode::KNN_SEARCH) {
            if (-candidate_set->Top().first > lower_bound && top_candidates->Size() >= ef) {
                break;
            }
        }
        const auto current_node_pair = candidate_set->Top();
        candidate_set->Pop();
        if (not candidate_set->Empty()) {
            graph->Prefetch(candidate_set->Top().second, 0);
        }
        const auto count_no_visited =
            visit(graph, vl, current_node_pair, nullptr, nullptr, to_be_visited_id, neighbors);
        distance_provider.BatchQueryDistance(
            line_dists.data(), to_be_visited_id.data(), count_no_visited, ctx);
        dist_cmp += count_no_visited;
        for (uint32_t i = 0; i < count_no_visited; ++i) {
            const auto id = to_be_visited_id[i];
            dist = line_dists[i];
            if (not distance_provider.IsValid(id)) {
```

这是 BasicSearcher 中使用 DistanceProvider 的搜索循环片段，具体调用路径仍需跟随前面的分派。candidate_set 保存待扩展节点，top_candidates 保存当前结果，两者职责不同。KNN 路径比较下一个候选距离与 lower_bound，且结果数量已达到 ef 才提前结束；hops_limit 是另一种停止限制。visit 收集未访问邻居，BatchQueryDistance 一次计算它们的距离。这里批量的是一个扩展节点的邻居集合，不是一次算所有 N 个节点。后续循环还负责结果合法性、非有限距离和更新 lower_bound。

## 7. 邻居去重与导航过滤

源码：[src/impl/searcher/basic_searcher.cpp](../../../src/impl/searcher/basic_searcher.cpp)，基线行号 52–73。以下是连续原文摘录。

```cpp

    if (this->mutex_array_ != nullptr) {
        SharedLock lock(this->mutex_array_, current_node_pair.second);
        graph->GetNeighbors(current_node_pair.second, neighbors);
    } else {
        graph->GetNeighbors(current_node_pair.second, neighbors);
    }

    for (uint32_t i = 0; i < neighbors.size(); i++) {
        if (i + prefetch_stride_visit_ < neighbors.size()) {
            vl->Prefetch(neighbors[i + prefetch_stride_visit_]);
        }
        if (not vl->Get(neighbors[i])) {
            vl->Set(neighbors[i]);
            if (not filter || count_no_visited == 0 || skip_strategy == nullptr ||
                skip_strategy->ShouldVisit() || filter->CheckValid(neighbors[i])) {
                to_be_visited_id[count_no_visited] = neighbors[i];
                count_no_visited++;
            }
        }
    }
    return count_no_visited;
```

有邻接锁数组时先加共享锁读取邻居，否则直接读。visited 在候选收集阶段置位，减少重复入队；预取 visited 的后续地址是一种缓存延迟优化。ShouldVisit 与 CheckValid 的组合说明“可访问”和“可返回”并非完全一致。注意上一段特定路径传入 nullptr filter/skip_strategy，不能把这里所有分支都当成该路径实际执行的过滤行为。

## 8. 构图剪枝不是简单取最近 M 个点

源码：[src/impl/pruning_strategy.cpp](../../../src/impl/pruning_strategy.cpp)，基线行号 93–128。以下是连续原文摘录。

```cpp

    auto queue_closest = std::make_shared<StandardHeap<true, false>>(allocator, -1);
    Vector<std::pair<float, InnerIdType>> return_list(allocator);
    PairwiseDistanceComputer pairwise_distance(distance_provider, allocator);
    while (not edges->Empty()) {
        queue_closest->Push(-edges->Top().first, edges->Top().second);
        edges->Pop();
    }

    while (not queue_closest->Empty()) {
        if (return_list.size() >= max_size) {
            break;
        }
        std::pair<float, InnerIdType> current_pair = queue_closest->Top();
        float float_query = -current_pair.first;
        queue_closest->Pop();
        bool good = true;

        for (const auto& second_pair : return_list) {
            float curdist =
                pairwise_distance.PairwiseDistance(second_pair.second, current_pair.second);
            if (alpha * curdist < float_query) {
                good = false;
                break;
            }
        }
        if (good) {
            return_list.emplace_back(current_pair);
        }
    }

    for (const auto& current_pair : return_list) {
        edges->Push(-current_pair.first, current_pair.second);
    }
}

```

先把候选转为从近到远处理的队列。对当前候选，既看它到新节点的距离 float_query，也比较它与已选邻居的距离 curdist；当 alpha×curdist < float_query 时将该候选视为可被已有邻居覆盖而放弃。由此保留的邻居更强调导航覆盖，而不是完全按距离截取。alpha 改变冗余判断的宽松程度；max_size 限制最终边预算。此逻辑是一种启发式，不构成对所有数据的召回保证。

## 读完以后应能解释

为什么 Build 不总是 NSW？ef_search 与 max_degree 分别影响哪一阶段？扫描回退依据是什么？为什么“提高精排精度”无法找回没有被候选扩展访问的节点？下一步进入 basic_searcher.cpp 看队列停止条件和 visited。
