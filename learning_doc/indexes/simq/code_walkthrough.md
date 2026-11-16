# SIMQ：代码逐段导读

[直观图解](visual_guide.md)

[返回设计说明](README.md) · [所有索引](../README.md)

源码基线：`fd363937`。下面引用真实源码，不将摘录伪装为独立可编译程序。完整实现还包含未展示的检查和分支，请结合链接阅读。

按“代表图 → 簇文档映射 → 粗排分数 → 完整 token 重评”阅读。粗排的 seen 数组是理解近似 MaxSim 的关键。

## 1. 动态聚类用代表 token 构建 HGraph

源码：[src/algorithm/simq/simq.cpp](../../../src/algorithm/simq/simq.cpp)，基线行号 182–203。以下为连续原文摘录，可能是函数的一部分。

```cpp
HGraphDynamicClustering::build_hgraph(const std::vector<int>& center_ids, int64_t dim) {
    IndexCommonParam cp = common_param_;
    cp.metric_ = MetricType::METRIC_TYPE_IP;
    cp.data_type_ = DataTypes::DATA_TYPE_FLOAT;
    cp.dim_ = dim;

    auto param = HGraph::CheckAndMappingExternalParam(
        JsonType::Parse(R"({"max_degree":32,"ef_construction":50})"), cp);
    hgraph_ = std::make_shared<HGraph>(param, cp);

    auto n = static_cast<int64_t>(center_ids.size());
    std::vector<float> vecs(static_cast<uint64_t>(n) * static_cast<uint64_t>(dim));
    std::vector<int64_t> labels(static_cast<uint64_t>(n));
    for (int64_t i = 0; i < n; ++i) {
        std::memcpy(vecs.data() + i * dim, vecs_ + center_ids[i] * dim, dim * sizeof(float));
        labels[i] = static_cast<int64_t>(center_ids[i]);
    }

    auto ds = Dataset::Make();
    ds->NumElements(n)->Dim(dim)->Float32Vectors(vecs.data())->Ids(labels.data())->Owner(false);
    hgraph_->Build(ds);
}
```

内部 cp 设为 FP32/IP，按 center_ids 抽取实际 token 向量组成 Dataset，labels 使用代表 token 的编号。这里是动态聚类辅助图的构建片段，后续 SIMQ 还会形成最终 rep_hgraph_；不能把两者的成员名混为同一个对象。

## 2. 为什么粗排缓冲复用影响并发

源码：[src/algorithm/simq/simq.cpp](../../../src/algorithm/simq/simq.cpp)，基线行号 1223–1246。以下为连续原文摘录，可能是函数的一部分。

```cpp
SIMQ::coarse_search(const float* query_tokens,
                    uint32_t query_token_count,
                    int64_t coarse_k,
                    uint64_t* coarse_dist_cmp,
                    uint64_t* coarse_probe_count) const {
    // Flat-array fast-path replacing the previous unordered_map + unordered_set
    // pair, which dominated coarse-search latency. Buffers are reused across
    // queries via mutable member state and lazily grown to fit total_count_ on
    // first call after Build/Add/Deserialize.
    const auto n_docs = static_cast<size_t>(total_count_);
    if (coarse_score_buf_.size() < n_docs) {
        coarse_score_buf_.assign(n_docs, 0.0F);
        coarse_seen_buf_.assign(n_docs, false);
    }
    coarse_dirty_.clear();

    // Each query token's search is independent. We do all KnnSearch calls in
    // parallel, then sequentially propagate scores (which is fast O(k) per token).
    struct TokenSearchResult {
        std::vector<std::pair<float, InnerIdType>> cscores;
        int64_t actual_coarse_k{0};
        uint64_t dist_cmp{0};
    };
    std::vector<TokenSearchResult> token_results(query_token_count);
```

coarse_score_buf_ 和 seen 数组按文档总数增长，dirty 列表记录本次修改位置，减少每次清零工作。它们是 mutable 成员，不是函数局部隔离的状态；后面的 KnnSearch 因此使用全局独占锁。query token 的图搜索可以内部并行，但不会改变这些成员的共享事实。

## 3. 每个 query token 对同一文档只记最高簇分数

源码：[src/algorithm/simq/simq.cpp](../../../src/algorithm/simq/simq.cpp)，基线行号 1322–1354。以下为连续原文摘录，可能是函数的一部分。

```cpp
    for (uint32_t ti = 0; ti < query_token_count; ++ti) {
        const auto& result = token_results[ti];
        if (result.actual_coarse_k <= 0) {
            continue;
        }
        if (coarse_probe_count != nullptr) {
            *coarse_probe_count += static_cast<uint64_t>(result.actual_coarse_k);
        }
        if (coarse_dist_cmp != nullptr) {
            *coarse_dist_cmp += result.dist_cmp;
        }

        coarse_seen_dirty_.clear();
        for (const auto& [cscore, cidx] : result.cscores) {
            if (cidx >= static_cast<InnerIdType>(num_clusters_)) {
                continue;
            }
            for (InnerIdType doc_id : cluster_lists_[cidx]) {
                if (coarse_seen_buf_[doc_id]) {
                    continue;
                }
                coarse_seen_buf_[doc_id] = true;
                coarse_seen_dirty_.push_back(doc_id);
                if (coarse_score_buf_[doc_id] == 0.0F) {
                    coarse_dirty_.push_back(doc_id);
                }
                coarse_score_buf_[doc_id] += cscore;
            }
        }
        for (InnerIdType doc_id : coarse_seen_dirty_) {
            coarse_seen_buf_[doc_id] = false;
        }
    }
```

输入 cscores 已按簇相似度降序。遍历簇中的文档时，seen 为 true 就跳过，因此当前 query token 只给该文档累加第一次遇到的最高簇分数。当前 token 完成后清理 seen，下一个 query token 可以再给同一文档贡献。这个循环模拟 MaxSim 的按 query token 取最大值结构，但使用的是代表簇分数。

## 4. 候选截断与过滤的先后顺序

源码：[src/algorithm/simq/simq.cpp](../../../src/algorithm/simq/simq.cpp)，基线行号 1371–1427。以下为连续原文摘录，可能是函数的一部分。

```cpp
SIMQ::KnnSearch(const DatasetPtr& query,
                int64_t k,
                const std::string& parameters,
                const FilterPtr& filter) const {
    std::unique_lock lock(global_mutex_);
    SearchStatistics stats;

    if (total_count_ == 0 || rep_hgraph_ == nullptr) {
        auto result = Dataset::Make();
        result->Statistics(
            dump_simq_statistics(stats, 0, 0, 0, 0, 0, 0, false, 0.0, 0.0, 0.0, 0, 0, 0));
        return result;
    }

    CHECK_ARGUMENT(query->GetNumElements() > 0, "simq search: query.num_elements must be > 0");
    const MultiVector* query_mvs = query->GetMultiVectors();
    CHECK_ARGUMENT(query_mvs != nullptr, "simq search: query.multi_vectors is nullptr");
    CHECK_ARGUMENT(query_mvs[0].len_ > 0, "simq search: query multi_vector length must be > 0");
    CHECK_ARGUMENT(query_mvs[0].vectors_ != nullptr,
                   "simq search: query multi_vector vectors is nullptr");

    auto sp = SIMQSearchParameters::FromJson(parameters);
    int64_t coarse_k = sp.coarse_k > 0 ? sp.coarse_k : default_coarse_k_;
    int64_t rerank_k = sp.rerank_k > 0 ? sp.rerank_k : default_rerank_k_;
    rerank_k = std::min(rerank_k, static_cast<int64_t>(total_count_));
    k = std::min(k, static_cast<int64_t>(total_count_));
    const auto threshold = ParseSearchThreshold(parameters);

    uint64_t coarse_dist_cmp = 0;
    uint64_t coarse_probe_count = 0;
    auto t_coarse_start = std::chrono::steady_clock::now();
    auto coarse_results = coarse_search(
        query_mvs[0].vectors_, query_mvs[0].len_, coarse_k, &coarse_dist_cmp, &coarse_probe_count);
    double coarse_ms =
        std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - t_coarse_start)
            .count();
    uint64_t coarse_candidate_count = coarse_results.size();
    if (static_cast<int64_t>(coarse_results.size()) > rerank_k) {
        coarse_results.resize(rerank_k);
    }
    uint64_t rerank_candidate_count = coarse_results.size();

    auto computer = mv_codes_->FactoryComputer(&query_mvs[0]);
    std::vector<std::pair<float, InnerIdType>> reranked;
    reranked.reserve(coarse_results.size());
    uint64_t filtered_candidate_count = 0;

    std::vector<InnerIdType> batch_ids;
    batch_ids.reserve(coarse_results.size());
    for (auto& [doc_id, _] : coarse_results) {
        if (filter != nullptr && !filter->CheckValid(this->label_table_->GetLabelById(doc_id))) {
            ++filtered_candidate_count;
            continue;
        }
        batch_ids.push_back(doc_id);
    }

```

入口先独占 global_mutex_，解析 coarse_k/rerank_k 并裁剪到文档数；coarse_search 后先 resize 到 rerank_k，再逐个过滤并形成 batch_ids。过滤后不会在这段逻辑中从已截掉的尾部补齐候选。高过滤率下结果不足 k，可能是候选流程的结果，不代表底层没有足够合法文档。

## 5. 批量精排与统计

源码：[src/algorithm/simq/simq.cpp](../../../src/algorithm/simq/simq.cpp)，基线行号 1429–1455。以下为连续原文摘录，可能是函数的一部分。

```cpp
    auto t_query_start = std::chrono::steady_clock::now();
    uint32_t mv_io_ms = 0;
    uint32_t mv_compute_ms = 0;
    uint32_t mv_candidates = 0;
    if (!batch_ids.empty()) {
        std::vector<float> batch_dists(batch_ids.size());
        // Use QueryContext so MultiVectorDataCell can report fine-grained timing
        // back through SearchStatistics.
        QueryContext query_context{.stats = &stats,
                                   .distance_phase = DistanceEvaluationPhase::RERANK};
        mv_codes_->Query(batch_dists.data(),
                         computer,
                         batch_ids.data(),
                         static_cast<InnerIdType>(batch_ids.size()),
                         &query_context);
        stats.dist_cmp.fetch_add(static_cast<uint32_t>(batch_ids.size()),
                                 std::memory_order_relaxed);
        for (uint64_t i = 0; i < batch_ids.size(); i++) {
            reranked.emplace_back(batch_dists[i], batch_ids[i]);
        }
        mv_io_ms = stats.mv_io_time_ms.load(std::memory_order_relaxed);
        mv_compute_ms = stats.mv_compute_time_ms.load(std::memory_order_relaxed);
        mv_candidates = stats.mv_candidate_count.load(std::memory_order_relaxed);
    }
    double query_ms =
        std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - t_query_start)
            .count();
```

对 batch_ids 一次调用 mv_codes_->Query，DataCell 可据此组织 MultiRead 与计算。QueryContext 把阶段标为 RERANK，分别收集 IO 和 compute 时间。结果以 `(distance, inner_id)` 进入 reranked，后续才排序和转外部 label。这里的精排文档数与粗排图的 token 距离比较数不是同一统计单位。

## 6. 簇分裂要同步文档映射与代表向量

源码：[src/algorithm/simq/simq.cpp](../../../src/algorithm/simq/simq.cpp)，基线行号 1051–1087。以下是连续原文摘录。

```cpp
SIMQ::execute_split_parallel(const SplitTask& task) {
    for (uint64_t rank = task.half; rank < task.tokens.size(); ++rank) {
        InnerIdType tid = task.tokens[rank];
        vec_to_cluster_[tid] = task.new_cluster_idx;
    }

    cluster_lists_[task.cluster_idx].clear();
    for (InnerIdType doc_id : task.old_docs) {
        cluster_lists_[task.cluster_idx].push_back(doc_id);
    }

    cluster_lists_[task.new_cluster_idx].clear();
    for (InnerIdType doc_id : task.new_docs) {
        cluster_lists_[task.new_cluster_idx].push_back(doc_id);
    }

    cluster_token_counts_[task.cluster_idx] = task.half;
    cluster_token_counts_[task.new_cluster_idx] = task.tokens.size() - task.half;

    // Use the farthest token (from old center) in the new half as new center
    InnerIdType rep_tid = task.tokens[task.tokens.size() - 1];
    InnerIdType rep_doc = token_to_doc_[rep_tid];
    uint32_t rep_offset = token_to_offset_[rep_tid];

    const auto udim = static_cast<uint64_t>(dim_);
    const uint64_t code_size_per_token = mv_codes_->GetQuantizerCodeSize();
    auto codes = mv_codes_->AcquireCodesById(rep_doc);
    CHECK_ARGUMENT(codes, "failed to read simq representative vector");

    std::vector<float> new_rep_vec(udim);
    mv_codes_->Decode(
        codes.Data() + sizeof(uint32_t) + static_cast<uint64_t>(rep_offset) * code_size_per_token,
        new_rep_vec.data());

    auto new_label = static_cast<int64_t>(task.new_cluster_idx);
    auto new_ds = Dataset::Make();
    new_ds->NumElements(1)
```

分裂把部分 token 改挂新簇，分别重建旧簇和新簇的文档集合，并更新 token 计数。新代表取自一个实际 token，根据 token_to_doc_ 与 token_to_offset_ 找到文档内编码，再 Acquire/Decode 得到代表向量。后续将代表加入图。只新增一个中心而忘记 cluster_lists_，粗排就无法正确从簇找到文档；只改映射而不更新代表图，也会使路由与簇内容不一致。

## 读完以后应能解释

seen 为什么必须在每个 query token 结束时重置？representative 的分数为何只是近似？扩大 rerank_k 能否补回未被 coarse 触及的文档？为什么多请求并发与 token 内部并行不是同一回事？
