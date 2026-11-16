# ivf_search.cpp：逐函数完整源码与调用点

[主讲解](../code_walkthrough.md) · [函数总目录](README.md)

源码：[ src/algorithm/ivf/ivf_search.cpp ](../../../../src/algorithm/ivf/ivf_search.cpp)。基线 `fd363937`。以下源码函数体完整保留；调用点表是语法树中的显式调用表达式，按源码位置排列，不代表 C++ 参数求值顺序。表中“候选实现”需结合类型和参数选分支，不能将同名函数全部视为必经路径。

- [IVF::KnnSearch · L51](ivf_search.md#L51)

- [IVF::RangeSearch · L68](ivf_search.md#L68)

- [IVF::create_search_param · L86](ivf_search.md#L86)

- [IVF::route_buckets_only · L110](ivf_search.md#L110)

- [IVF::reorder · L183](ivf_search.md#L183)

- [IVF::search · L199](ivf_search.md#L199)

- [IVF::search_with_custom_distance · L334](ivf_search.md#L334)

- [IVF::SearchWithRequest · L492](ivf_search.md#L492)

- [IVF::AttachReasoningReport · L799](ivf_search.md#L799)


<a id="L51"></a>

## `IVF::KnnSearch`

源码位置：`src/algorithm/ivf/ivf_search.cpp:51–66`。

先从签名确认输入、返回值和 const/override，再按完整函数体的条件阅读调用点。下表保留了本函数的显式调用以及 lambda 中的调用；进入下层时用“候选实现”定位，未解析的对象由源码静态类型/运行时类型确认。

### 完整函数

```cpp
DatasetPtr
IVF::KnnSearch(const DatasetPtr& query,
               int64_t k,
               const std::string& parameters,
               const FilterPtr& filter) const {
    SearchRequest req;
    req.mode_ = SearchMode::KNN_SEARCH;
    req.query_ = query;
    req.topk_ = k;
    req.params_str_ = parameters;
    req.threshold_ = ParseSearchThreshold(parameters);
    if (filter != nullptr) {
        req.filter_ = filter;
    }
    return this->SearchWithRequest(req);
}
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L61 | ParseSearchThreshold | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L65 | this-&gt;SearchWithRequest | 函数本体；短路求值/提前返回见源码 | [IVF::SearchWithRequest · L492](ivf_search.md#L492) |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L68"></a>

## `IVF::RangeSearch`

源码位置：`src/algorithm/ivf/ivf_search.cpp:68–84`。

先从签名确认输入、返回值和 const/override，再按完整函数体的条件阅读调用点。下表保留了本函数的显式调用以及 lambda 中的调用；进入下层时用“候选实现”定位，未解析的对象由源码静态类型/运行时类型确认。

### 完整函数

```cpp
DatasetPtr
IVF::RangeSearch(const DatasetPtr& query,
                 float radius,
                 const std::string& parameters,
                 const FilterPtr& filter,
                 int64_t limited_size) const {
    SearchRequest req;
    req.mode_ = SearchMode::RANGE_SEARCH;
    req.query_ = query;
    req.radius_ = radius;
    req.limited_size_ = limited_size;
    req.params_str_ = parameters;
    if (filter != nullptr) {
        req.filter_ = filter;
    }
    return this->SearchWithRequest(req);
}
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L83 | this-&gt;SearchWithRequest | 函数本体；短路求值/提前返回见源码 | [IVF::SearchWithRequest · L492](ivf_search.md#L492) |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L86"></a>

## `IVF::create_search_param`

源码位置：`src/algorithm/ivf/ivf_search.cpp:86–108`。

输出 InnerSearchParam。过滤器、JSON 解析、桶数裁剪和计时器准备都发生在真正访问桶之前；用户 label 过滤必须包装成 origin ID 过滤。

### 完整函数

```cpp
InnerSearchParam
IVF::create_search_param(const std::string& parameters, const FilterPtr& filter) const {
    InnerSearchParam param;
    param.is_inner_id_allowed = this->create_search_filter(filter);
    auto search_param = IVFSearchParameters::FromJson(parameters);
    if (search_param.disable_bucket_scan) {
        param.scan_bucket_size = static_cast<BucketIdType>(search_param.scan_buckets_count);
    } else {
        param.scan_bucket_size = std::min(
            static_cast<BucketIdType>(search_param.scan_buckets_count), bucket_->bucket_count_);
    }
    param.disable_bucket_scan = search_param.disable_bucket_scan;
    param.factor = search_param.topk_factor;
    param.enable_reorder = search_param.enable_reorder;
    param.first_order_scan_ratio = search_param.first_order_scan_ratio;
    param.parallel_search_thread_count = search_param.parallel_search_thread_count;
    param.ef = static_cast<uint64_t>(search_param.ef_search);
    if (search_param.enable_time_record) {
        param.time_cost = std::make_shared<Timer>();
        param.time_cost->SetThreshold(search_param.timeout_ms);
    }
    return param;
}
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L89 | this-&gt;create_search_filter | 函数本体；短路求值/提前返回见源码 | [InnerIndexInterface::create_search_filter · L1108](inner_index_interface.md#L1108) |

| L90 | IVFSearchParameters::FromJson | 函数本体；短路求值/提前返回见源码 | [IVFSearchParameters::FromJson · L150](ivf_parameter.md#L150) |

| L94 | std::min | if_statement@91 (search_param.disable_bucket_scan) [else 分支] | 当前参考未静态绑定；见下方边界说明 |

| L104 | std::make_shared&lt;Timer&gt; | if_statement@103 (search_param.enable_time_record) | 当前参考未静态绑定；见下方边界说明 |

| L105 | param.time_cost-&gt;SetThreshold | if_statement@103 (search_param.enable_time_record) | 当前参考未静态绑定；见下方边界说明 |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L110"></a>

## `IVF::route_buckets_only`

源码位置：`src/algorithm/ivf/ivf_search.cpp:110–181`。

输出是桶 ID 与 query 到中心的距离，不是记录检索结果。它重新计算 L2/IP/cosine 距离，而不是直接返回选桶的排序键。

### 完整函数

```cpp
DatasetPtr
IVF::route_buckets_only(const DatasetPtr& query,
                        const InnerSearchParam& param,
                        QueryContext& ctx) const {
    const auto num_queries = query->GetNumElements();
    const auto* query_data = query->GetFloat32Vectors();
    const auto buckets_per_query = param.scan_bucket_size;
    const auto candidate_buckets =
        partition_strategy_->ClassifyDatasForSearch(query_data, num_queries, param, &ctx);

    auto result = Dataset::Make();
    if (num_queries == 0 || buckets_per_query == 0) {
        return result->NumElements(0)->Dim(0);
    }

    auto* alloc = (ctx.alloc != nullptr) ? ctx.alloc : allocator_;
    const auto total_slots = num_queries * buckets_per_query;
    auto* ids = static_cast<int64_t*>(alloc->Allocate(sizeof(int64_t) * total_slots));
    auto* distances = static_cast<float*>(alloc->Allocate(sizeof(float) * total_slots));
    const auto dim = partition_strategy_->dim_;
    const auto metric = partition_strategy_->metric_type_;

    Vector<float> centroid(dim, allocator_);
    Vector<float> norm_query(dim, allocator_);
    Vector<float> norm_centroid(dim, allocator_);
    for (int64_t q = 0; q < num_queries; ++q) {
        const auto* query_vec = query_data + q * dim;
        if (metric == MetricType::METRIC_TYPE_COSINE) {
            Normalize(query_vec, norm_query.data(), dim);
        }
        for (int64_t b = 0; b < buckets_per_query; ++b) {
            const auto idx = q * buckets_per_query + b;
            const auto bucket_id = candidate_buckets[idx];
            if (bucket_id == INVALID_BUCKET_ID) {
                ids[idx] = -1;
                distances[idx] = std::numeric_limits<float>::infinity();
                continue;
            }
            partition_strategy_->GetCentroid(bucket_id, centroid);
            float dist = 0.0F;
            if (metric == MetricType::METRIC_TYPE_L2SQR) {
                for (int64_t d = 0; d < dim; ++d) {
                    auto diff = query_vec[d] - centroid[d];
                    dist += diff * diff;
                }
            } else if (metric == MetricType::METRIC_TYPE_COSINE) {
                Normalize(centroid.data(), norm_centroid.data(), dim);
                for (int64_t d = 0; d < dim; ++d) {
                    dist += norm_query[d] * norm_centroid[d];
                }
                dist = 1.0F - dist;
            } else {
                for (int64_t d = 0; d < dim; ++d) {
                    dist += query_vec[d] * centroid[d];
                }
                dist = 1.0F - dist;
            }
            ids[idx] = static_cast<int64_t>(bucket_id);
            distances[idx] = dist;
            if (ctx.stats != nullptr) {
                ctx.stats->AddDistance(SearchStatistics::DistancePhase::ROUTING,
                                       DistanceEvaluationBackend::FP32);
            }
        }
    }

    return result->NumElements(num_queries)
        ->Dim(buckets_per_query)
        ->Ids(ids)
        ->Distances(distances)
        ->Owner(true, alloc);
}
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L114 | query-&gt;GetNumElements | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L115 | query-&gt;GetFloat32Vectors | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L118 | partition_strategy_-&gt;ClassifyDatasForSearch | 函数本体；短路求值/提前返回见源码 | [GNOIMIPartition::ClassifyDatasForSearch · L221](gno_imi_partition.md#L221)；[IVFPartitionStrategy::ClassifyDatasForSearch · L64](ivf_partition_strategy_h.md#L64) |

| L120 | Dataset::Make | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L122 | result-&gt;NumElements(0)-&gt;Dim | if_statement@121 (num_queries == 0 &#124;&#124; buckets_per_query == 0) | 当前参考未静态绑定；见下方边界说明 |

| L122 | result-&gt;NumElements | if_statement@121 (num_queries == 0 &#124;&#124; buckets_per_query == 0) | 当前参考未静态绑定；见下方边界说明 |

| L127 | alloc-&gt;Allocate | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L128 | alloc-&gt;Allocate | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L138 | Normalize | for_statement@135 q &lt; num_queries → if_statement@137 (metric == MetricType::METRIC_TYPE_COSINE) | 当前参考未静态绑定；见下方边界说明 |

| L138 | norm_query.data | for_statement@135 q &lt; num_queries → if_statement@137 (metric == MetricType::METRIC_TYPE_COSINE) | 当前参考未静态绑定；见下方边界说明 |

| L145 | std::numeric_limits&lt;float&gt;::infinity | for_statement@135 q &lt; num_queries → for_statement@140 b &lt; buckets_per_query → if_statement@143 (bucket_id == INVALID_BUCKET_ID) | 当前参考未静态绑定；见下方边界说明 |

| L148 | partition_strategy_-&gt;GetCentroid | for_statement@135 q &lt; num_queries → for_statement@140 b &lt; buckets_per_query | [GNOIMIPartition::GetCentroid · L440](gno_imi_partition.md#L440)；[IVFNearestPartition::GetCentroid · L286](ivf_nearest_partition.md#L286) |

| L156 | Normalize | for_statement@135 q &lt; num_queries → for_statement@140 b &lt; buckets_per_query → if_statement@150 (metric == MetricType::METRIC_TYPE_L2SQR) [else 分支] → if_statement@155 (metric == MetricType::METRIC_TYPE_COSINE) | 当前参考未静态绑定；见下方边界说明 |

| L156 | centroid.data | for_statement@135 q &lt; num_queries → for_statement@140 b &lt; buckets_per_query → if_statement@150 (metric == MetricType::METRIC_TYPE_L2SQR) [else 分支] → if_statement@155 (metric == MetricType::METRIC_TYPE_COSINE) | 当前参考未静态绑定；见下方边界说明 |

| L156 | norm_centroid.data | for_statement@135 q &lt; num_queries → for_statement@140 b &lt; buckets_per_query → if_statement@150 (metric == MetricType::METRIC_TYPE_L2SQR) [else 分支] → if_statement@155 (metric == MetricType::METRIC_TYPE_COSINE) | 当前参考未静态绑定；见下方边界说明 |

| L170 | ctx.stats-&gt;AddDistance | for_statement@135 q &lt; num_queries → for_statement@140 b &lt; buckets_per_query → if_statement@169 (ctx.stats != nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L176 | result-&gt;NumElements(num_queries) -&gt;Dim(buckets_per_query) -&gt;Ids(ids) -&gt;Distances(distances) -&gt;Owner | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L176 | result-&gt;NumElements(num_queries) -&gt;Dim(buckets_per_query) -&gt;Ids(ids) -&gt;Distances | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L176 | result-&gt;NumElements(num_queries) -&gt;Dim(buckets_per_query) -&gt;Ids | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L176 | result-&gt;NumElements(num_queries) -&gt;Dim | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L176 | result-&gt;NumElements | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L183"></a>

## `IVF::reorder`

源码位置：`src/algorithm/ivf/ivf_search.cpp:183–196`。

输入候选堆，调用选定的精排布局重算距离，然后 pack_knn_result。只能重排已有候选，不能补回未路由到的桶。

### 完整函数

```cpp
DatasetPtr
IVF::reorder(int64_t topk,
             DistHeapPtr& input,
             const float* query,
             const InnerSearchParam& param,
             QueryContext& ctx,
             ReasoningContext* reasoning_ctx,
             const std::optional<float>& distance_threshold) const {
    auto reorder_heap =
        reorder_->Reorder(input, query, topk, ctx, nullptr, nullptr, distance_threshold);
    auto dataset_results = this->pack_knn_result(reorder_heap, ctx.alloc);

    return dataset_results;
}
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L192 | reorder_-&gt;Reorder | 函数本体；短路求值/提前返回见源码 | [BucketReorder::Reorder · L28](bucket_reorder.md#L28)；[FlattenReorder::Reorder · L156](flatten_reorder.md#L156) |

| L193 | this-&gt;pack_knn_result | 函数本体；短路求值/提前返回见源码 | [InnerIndexInterface::pack_knn_result · L1140](inner_index_interface.md#L1140) |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L199"></a>

## `IVF::search`

源码位置：`src/algorithm/ivf/ivf_search.cpp:199–332`。

返回候选距离堆。先决定桶列表和 posting 预算，再分配桶任务，最后合并并按 origin ID 去重。搜索 lambda 在线程池与同步路径中二选一执行。

### 完整函数

```cpp
DistHeapPtr
IVF::search(const DatasetPtr& query,
            const InnerSearchParam& param,
            QueryContext& ctx,
            ReasoningContext* reasoning_ctx) const {
    const auto* query_data = query->GetFloat32Vectors();
    Vector<BucketIdType> candidate_buckets(allocator_);
    if (not param.bucket_ids.empty()) {
        candidate_buckets.reserve(param.bucket_ids.size());
        for (auto id : param.bucket_ids) {
            candidate_buckets.push_back(static_cast<BucketIdType>(id));
        }
    } else {
        candidate_buckets = partition_strategy_->ClassifyDatasForSearch(query_data, 1, param, &ctx);
    }
    if (reasoning_ctx != nullptr) {
        reasoning_ctx->RecordBucketSelection(candidate_buckets);
    }
    auto computer = bucket_->FactoryComputer(query_data);

    int64_t topk = param.topk;
    if constexpr (mode == RANGE_SEARCH) {
        topk = param.range_search_limit_size;
        if (topk < 0) {
            topk = this->GetNumElements();
        }
    }
    // Scale topk to ensure sufficient candidates after deduplication when buckets_per_data_ > 1
    int64_t origin_topk = topk;
    if (buckets_per_data_ > 1) {
        if (topk <= std::numeric_limits<int64_t>::max() / buckets_per_data_) {
            topk *= buckets_per_data_;
        } else {
            topk = std::numeric_limits<int64_t>::max();
        }
    }

    DistHeapPtr search_result = nullptr;

    auto bucket_count = candidate_buckets.size();
    auto search_thread_count = param.parallel_search_thread_count;
    if (this->thread_pool_ == nullptr) {
        search_thread_count = 1;
    }
    std::vector<DistHeapPtr> heaps(search_thread_count);
    std::atomic<uint64_t> cur_bucket_num(0);
    auto search_func = [&](int64_t thread_id) -> void {
        heaps[thread_id] = DistanceHeap::MakeInstanceBySize<true, false>(this->allocator_, topk);
        auto& heap = heaps[thread_id];
        Vector<float> dist(allocator_);
        uint64_t i = cur_bucket_num.fetch_add(1);
        for (; i < bucket_count; i = cur_bucket_num.fetch_add(1)) {
            if (param.time_cost != nullptr and param.time_cost->CheckOvertime() and
                ctx.stats != nullptr) {
                ctx.stats->is_timeout.store(true, std::memory_order_relaxed);
                break;
            }
            auto bucket_id = candidate_buckets[i];
            if (bucket_id == INVALID_BUCKET_ID) {
                break;
            }
            bucket_searcher_->Search(bucket_id,
                                     bucket_,
                                     computer,
                                     param,
                                     thread_id,
                                     topk,
                                     buckets_per_data_,
                                     heap,
                                     dist,
                                     reasoning_ctx);
        }
    };
    std::vector<std::future<void>> futures;
    if (this->thread_pool_ != nullptr and search_thread_count > 1) {
        for (int64_t thread_id = 0; thread_id < search_thread_count; ++thread_id) {
            auto future = this->thread_pool_->GeneralEnqueue(search_func, thread_id);
            futures.emplace_back(std::move(future));
        }
    } else {
        search_func(0);
        search_result = heaps[0];
    }

    if (this->thread_pool_ != nullptr and search_thread_count > 1) {
        for (auto& future : futures) {
            future.get();
        }
        search_result = DistanceHeap::MakeInstanceBySize<true, true>(this->allocator_, topk);
        for (auto& heap : heaps) {
            auto size = heap->Size();
            const auto* data = heap->GetData();
            for (int i = 0; i < size; ++i) {
                if (reasoning_ctx != nullptr and
                    search_result->Size() >= static_cast<uint64_t>(topk) and
                    data[i].first < search_result->Top().first) {
                    reasoning_ctx->RecordEviction(search_result->Top().second / buckets_per_data_,
                                                  1);
                }
                search_result->Push(data[i]);
            }
        }
    }

    // Deduplicate ids when buckets_per_data_ > 1
    if (buckets_per_data_ > 1) {
        std::unordered_map<InnerIdType, float> id_to_min_dist;
        while (!search_result->Empty()) {
            const auto& [dist_val, id] = search_result->Top();
            auto origin_id = id / buckets_per_data_;
            // Keep the smallest distance for each id
            if (id_to_min_dist.find(origin_id) == id_to_min_dist.end() ||
                dist_val < id_to_min_dist[origin_id]) {
                id_to_min_dist[origin_id] = dist_val;
            }
            search_result->Pop();
        }

        auto cur_heap_top2 = std::numeric_limits<float>::max();
        for (const auto& [origin_id, dist_val] : id_to_min_dist) {
            if (dist_val < cur_heap_top2) {
                search_result->Push(dist_val, origin_id);
            }
            if (search_result->Size() > origin_topk) {
                search_result->Pop();
            }
            if (not search_result->Empty() and search_result->Size() == origin_topk) {
                cur_heap_top2 = search_result->Top().first;
            }
        }
    }

    return search_result;
}
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L204 | query-&gt;GetFloat32Vectors | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L206 | param.bucket_ids.empty | if_statement@206 (not param.bucket_ids.empty()) | 当前参考未静态绑定；见下方边界说明 |

| L207 | candidate_buckets.reserve | if_statement@206 (not param.bucket_ids.empty()) | 当前参考未静态绑定；见下方边界说明 |

| L207 | param.bucket_ids.size | if_statement@206 (not param.bucket_ids.empty()) | 当前参考未静态绑定；见下方边界说明 |

| L209 | candidate_buckets.push_back | if_statement@206 (not param.bucket_ids.empty()) → for_range_loop@208 | 当前参考未静态绑定；见下方边界说明 |

| L212 | partition_strategy_-&gt;ClassifyDatasForSearch | if_statement@206 (not param.bucket_ids.empty()) [else 分支] | [GNOIMIPartition::ClassifyDatasForSearch · L221](gno_imi_partition.md#L221)；[IVFPartitionStrategy::ClassifyDatasForSearch · L64](ivf_partition_strategy_h.md#L64) |

| L215 | reasoning_ctx-&gt;RecordBucketSelection | if_statement@214 (reasoning_ctx != nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L217 | bucket_-&gt;FactoryComputer | 函数本体；短路求值/提前返回见源码 | [BucketDataCell&lt;QuantTmpl, IOTmpl&gt;::FactoryComputer · L566](bucket_datacell_h.md#L566) |

| L223 | this-&gt;GetNumElements | if_statement@220 (mode == RANGE_SEARCH) → if_statement@222 (topk &lt; 0) | [IVF::GetNumElements · L291](ivf.md#L291) |

| L229 | std::numeric_limits&lt;int64_t&gt;::max | if_statement@228 (buckets_per_data_ &gt; 1) → if_statement@229 (topk &lt;= std::numeric_limits&lt;int64_t&gt;::max() / buckets_per_data_) | 当前参考未静态绑定；见下方边界说明 |

| L232 | std::numeric_limits&lt;int64_t&gt;::max | if_statement@228 (buckets_per_data_ &gt; 1) → if_statement@229 (topk &lt;= std::numeric_limits&lt;int64_t&gt;::max() / buckets_per_data_) [else 分支] | 当前参考未静态绑定；见下方边界说明 |

| L238 | candidate_buckets.size | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L246 | DistanceHeap::MakeInstanceBySize&lt;true, false&gt; | lambda@245（定义体，执行时间取决于调用/调度） | 当前参考未静态绑定；见下方边界说明 |

| L249 | cur_bucket_num.fetch_add | lambda@245（定义体，执行时间取决于调用/调度） | 当前参考未静态绑定；见下方边界说明 |

| L250 | cur_bucket_num.fetch_add | lambda@245（定义体，执行时间取决于调用/调度） → for_statement@250 i &lt; bucket_count | 当前参考未静态绑定；见下方边界说明 |

| L251 | param.time_cost-&gt;CheckOvertime | lambda@245（定义体，执行时间取决于调用/调度） → for_statement@250 i &lt; bucket_count → if_statement@251 (param.time_cost != nullptr and param.time_cost-&gt;CheckOvertime() and ctx.stats != nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L253 | ctx.stats-&gt;is_timeout.store | lambda@245（定义体，执行时间取决于调用/调度） → for_statement@250 i &lt; bucket_count → if_statement@251 (param.time_cost != nullptr and param.time_cost-&gt;CheckOvertime() and ctx.stats != nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L260 | bucket_searcher_-&gt;Search | lambda@245（定义体，执行时间取决于调用/调度） → for_statement@250 i &lt; bucket_count | [FlatBucketSearcher::Search · L26](flat_bucket_searcher.md#L26)；[GraphBucketSearcher::Search · L36](graph_bucket_searcher.md#L36) |

| L275 | this-&gt;thread_pool_-&gt;GeneralEnqueue | if_statement@273 (this-&gt;thread_pool_ != nullptr and search_thread_count &gt; 1) → for_statement@274 thread_id &lt; search_thread_count | 当前参考未静态绑定；见下方边界说明 |

| L276 | futures.emplace_back | if_statement@273 (this-&gt;thread_pool_ != nullptr and search_thread_count &gt; 1) → for_statement@274 thread_id &lt; search_thread_count | 当前参考未静态绑定；见下方边界说明 |

| L276 | std::move | if_statement@273 (this-&gt;thread_pool_ != nullptr and search_thread_count &gt; 1) → for_statement@274 thread_id &lt; search_thread_count | 当前参考未静态绑定；见下方边界说明 |

| L279 | search_func | if_statement@273 (this-&gt;thread_pool_ != nullptr and search_thread_count &gt; 1) [else 分支] | 当前参考未静态绑定；见下方边界说明 |

| L285 | future.get | if_statement@283 (this-&gt;thread_pool_ != nullptr and search_thread_count &gt; 1) → for_range_loop@284 | 当前参考未静态绑定；见下方边界说明 |

| L287 | DistanceHeap::MakeInstanceBySize&lt;true, true&gt; | if_statement@283 (this-&gt;thread_pool_ != nullptr and search_thread_count &gt; 1) | 当前参考未静态绑定；见下方边界说明 |

| L289 | heap-&gt;Size | if_statement@283 (this-&gt;thread_pool_ != nullptr and search_thread_count &gt; 1) → for_range_loop@288 | 当前参考未静态绑定；见下方边界说明 |

| L290 | heap-&gt;GetData | if_statement@283 (this-&gt;thread_pool_ != nullptr and search_thread_count &gt; 1) → for_range_loop@288 | 当前参考未静态绑定；见下方边界说明 |

| L293 | search_result-&gt;Size | if_statement@283 (this-&gt;thread_pool_ != nullptr and search_thread_count &gt; 1) → for_range_loop@288 → for_statement@291 i &lt; size → if_statement@292 (reasoning_ctx != nullptr and search_result-&gt;Size() &gt;= static_cast&lt;uint64_t&gt;(topk) and data[i].first &lt; search_result-&gt;Top().first) | 当前参考未静态绑定；见下方边界说明 |

| L294 | search_result-&gt;Top | if_statement@283 (this-&gt;thread_pool_ != nullptr and search_thread_count &gt; 1) → for_range_loop@288 → for_statement@291 i &lt; size → if_statement@292 (reasoning_ctx != nullptr and search_result-&gt;Size() &gt;= static_cast&lt;uint64_t&gt;(topk) and data[i].first &lt; search_result-&gt;Top().first) | 当前参考未静态绑定；见下方边界说明 |

| L295 | reasoning_ctx-&gt;RecordEviction | if_statement@283 (this-&gt;thread_pool_ != nullptr and search_thread_count &gt; 1) → for_range_loop@288 → for_statement@291 i &lt; size → if_statement@292 (reasoning_ctx != nullptr and search_result-&gt;Size() &gt;= static_cast&lt;uint64_t&gt;(topk) and data[i].first &lt; search_result-&gt;Top().first) | 当前参考未静态绑定；见下方边界说明 |

| L295 | search_result-&gt;Top | if_statement@283 (this-&gt;thread_pool_ != nullptr and search_thread_count &gt; 1) → for_range_loop@288 → for_statement@291 i &lt; size → if_statement@292 (reasoning_ctx != nullptr and search_result-&gt;Size() &gt;= static_cast&lt;uint64_t&gt;(topk) and data[i].first &lt; search_result-&gt;Top().first) | 当前参考未静态绑定；见下方边界说明 |

| L298 | search_result-&gt;Push | if_statement@283 (this-&gt;thread_pool_ != nullptr and search_thread_count &gt; 1) → for_range_loop@288 → for_statement@291 i &lt; size | 当前参考未静态绑定；见下方边界说明 |

| L306 | search_result-&gt;Empty | if_statement@304 (buckets_per_data_ &gt; 1) → while_statement@306 (!search_result-&gt;Empty()) | 当前参考未静态绑定；见下方边界说明 |

| L307 | search_result-&gt;Top | if_statement@304 (buckets_per_data_ &gt; 1) → while_statement@306 (!search_result-&gt;Empty()) | 当前参考未静态绑定；见下方边界说明 |

| L310 | id_to_min_dist.find | if_statement@304 (buckets_per_data_ &gt; 1) → while_statement@306 (!search_result-&gt;Empty()) → if_statement@310 (id_to_min_dist.find(origin_id) == id_to_min_dist.end() &#124;&#124; dist_val &lt; id_to_min_dist[origin_id]) | 当前参考未静态绑定；见下方边界说明 |

| L310 | id_to_min_dist.end | if_statement@304 (buckets_per_data_ &gt; 1) → while_statement@306 (!search_result-&gt;Empty()) → if_statement@310 (id_to_min_dist.find(origin_id) == id_to_min_dist.end() &#124;&#124; dist_val &lt; id_to_min_dist[origin_id]) | 当前参考未静态绑定；见下方边界说明 |

| L314 | search_result-&gt;Pop | if_statement@304 (buckets_per_data_ &gt; 1) → while_statement@306 (!search_result-&gt;Empty()) | 当前参考未静态绑定；见下方边界说明 |

| L317 | std::numeric_limits&lt;float&gt;::max | if_statement@304 (buckets_per_data_ &gt; 1) | 当前参考未静态绑定；见下方边界说明 |

| L320 | search_result-&gt;Push | if_statement@304 (buckets_per_data_ &gt; 1) → for_range_loop@318 → if_statement@319 (dist_val &lt; cur_heap_top2) | 当前参考未静态绑定；见下方边界说明 |

| L322 | search_result-&gt;Size | if_statement@304 (buckets_per_data_ &gt; 1) → for_range_loop@318 → if_statement@322 (search_result-&gt;Size() &gt; origin_topk) | 当前参考未静态绑定；见下方边界说明 |

| L323 | search_result-&gt;Pop | if_statement@304 (buckets_per_data_ &gt; 1) → for_range_loop@318 → if_statement@322 (search_result-&gt;Size() &gt; origin_topk) | 当前参考未静态绑定；见下方边界说明 |

| L325 | search_result-&gt;Empty | if_statement@304 (buckets_per_data_ &gt; 1) → for_range_loop@318 → if_statement@325 (not search_result-&gt;Empty() and search_result-&gt;Size() == origin_topk) | 当前参考未静态绑定；见下方边界说明 |

| L325 | search_result-&gt;Size | if_statement@304 (buckets_per_data_ &gt; 1) → for_range_loop@318 → if_statement@325 (not search_result-&gt;Empty() and search_result-&gt;Size() == origin_topk) | 当前参考未静态绑定；见下方边界说明 |

| L326 | search_result-&gt;Top | if_statement@304 (buckets_per_data_ &gt; 1) → for_range_loop@318 → if_statement@325 (not search_result-&gt;Empty() and search_result-&gt;Size() == origin_topk) | 当前参考未静态绑定；见下方边界说明 |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L334"></a>

## `IVF::search_with_custom_distance`

源码位置：`src/algorithm/ivf/ivf_search.cpp:334–490`。

保留完整 submit_batch/is_timed_out lambda。先在桶内进行属性检查，收集外部 labels 后调用用户批量距离函数，再做 origin ID 普通过滤与入堆，最后多桶去重。

### 完整函数

```cpp
DistHeapPtr
IVF::search_with_custom_distance(const DatasetPtr& query,
                                 const SearchRequest& request,
                                 const InnerSearchParam& param,
                                 QueryContext& ctx,
                                 ReasoningContext* reasoning_ctx) const {
    const auto* query_data = query->GetFloat32Vectors();
    Vector<BucketIdType> candidate_buckets(allocator_);
    if (not param.bucket_ids.empty()) {
        candidate_buckets.reserve(param.bucket_ids.size());
        for (auto id : param.bucket_ids) {
            candidate_buckets.push_back(static_cast<BucketIdType>(id));
        }
    } else {
        candidate_buckets = partition_strategy_->ClassifyDatasForSearch(query_data, 1, param, &ctx);
    }
    if (reasoning_ctx != nullptr) {
        reasoning_ctx->RecordBucketSelection(candidate_buckets);
    }

    int64_t topk = request.topk_;
    const int64_t origin_topk = topk;
    if (buckets_per_data_ > 1) {
        CHECK_ARGUMENT(topk <= std::numeric_limits<int64_t>::max() / buckets_per_data_,
                       "topk is too large for multi-bucket IVF search");
        topk *= buckets_per_data_;
    }

    auto search_result = DistanceHeap::MakeInstanceBySize<true, false>(this->allocator_, topk);
    const auto& filter = param.is_inner_id_allowed;
    Filter* attr_filter = nullptr;

    Vector<InnerIdType> candidate_ids(this->allocator_);
    Vector<int64_t> candidate_labels(this->allocator_);
    Vector<float> scores(this->allocator_);
    const uint64_t batch_capacity = std::min<uint64_t>(
        request.distance_batch_size_, std::max<uint64_t>(1, this->GetNumElements()));
    candidate_ids.reserve(batch_capacity);
    candidate_labels.reserve(batch_capacity);
    scores.resize(batch_capacity);

    auto is_timed_out = [&]() {
        if (param.time_cost == nullptr or not param.time_cost->CheckOvertime()) {
            return false;
        }
        if (ctx.stats != nullptr) {
            ctx.stats->is_timeout.store(true, std::memory_order_relaxed);
        }
        return true;
    };

    auto submit_batch = [&]() {
        if (candidate_ids.empty()) {
            return true;
        }
        if (is_timed_out()) {
            return false;
        }
        request.distance_batch_func_(
            candidate_labels.data(), candidate_labels.size(), scores.data());
        if (ctx.stats != nullptr) {
            ctx.stats->AddDistance(SearchStatistics::DistancePhase::APPROXIMATE,
                                   DistanceEvaluationBackend::UNKNOWN,
                                   candidate_ids.size());
        }
        for (uint64_t i = 0; i < candidate_ids.size(); ++i) {
            CHECK_ARGUMENT(std::isfinite(scores[i]),
                           "custom query distance callback must return finite scores");
            const auto origin_id = candidate_ids[i] / buckets_per_data_;
            if (filter != nullptr and not filter->CheckValid(origin_id)) {
                if (reasoning_ctx != nullptr) {
                    reasoning_ctx->RecordFilterReject(origin_id);
                }
                continue;
            }
            if (reasoning_ctx != nullptr) {
                reasoning_ctx->RecordVisit(origin_id, scores[i], 0);
            }
            search_result->Push(scores[i], candidate_ids[i]);
            while (search_result->Size() > static_cast<uint64_t>(topk)) {
                if (reasoning_ctx != nullptr) {
                    reasoning_ctx->RecordEviction(search_result->Top().second / buckets_per_data_,
                                                  0);
                }
                search_result->Pop();
            }
        }
        candidate_ids.clear();
        candidate_labels.clear();
        return true;
    };

    bool timed_out = false;
    for (const auto bucket_id : candidate_buckets) {
        if (is_timed_out()) {
            timed_out = true;
            break;
        }
        if (bucket_id == INVALID_BUCKET_ID) {
            continue;
        }
        if (not param.executors.empty()) {
            param.executors[0]->Clear();
            attr_filter = param.executors[0]->Run(bucket_id);
        }
        const auto bucket_size = bucket_->GetBucketSize(bucket_id);
        const auto* ids = bucket_->GetInnerIds(bucket_id);
        for (InnerIdType offset = 0; offset < bucket_size; ++offset) {
            const auto inner_id = ids[offset];
            if (inner_id == std::numeric_limits<InnerIdType>::max()) {
                continue;
            }
            const auto origin_id = inner_id / buckets_per_data_;
            if (attr_filter != nullptr and not attr_filter->CheckValid(offset)) {
                if (reasoning_ctx != nullptr) {
                    reasoning_ctx->RecordFilterReject(origin_id);
                }
                continue;
            }
            candidate_ids.push_back(inner_id);
            candidate_labels.push_back(label_table_->GetLabelById(origin_id));
            if (candidate_ids.size() == batch_capacity and not submit_batch()) {
                timed_out = true;
                break;
            }
        }
        if (timed_out) {
            break;
        }
    }
    if (not timed_out) {
        submit_batch();
    }

    if (buckets_per_data_ == 1) {
        return search_result;
    }

    std::unordered_map<InnerIdType, float> id_to_min_score;
    while (not search_result->Empty()) {
        const auto& [score, inner_id] = search_result->Top();
        const auto origin_id = inner_id / buckets_per_data_;
        auto iter = id_to_min_score.find(origin_id);
        if (iter == id_to_min_score.end() or score < iter->second) {
            id_to_min_score[origin_id] = score;
        }
        search_result->Pop();
    }

    for (const auto& [origin_id, score] : id_to_min_score) {
        search_result->Push(score, origin_id);
        if (search_result->Size() > static_cast<uint64_t>(origin_topk)) {
            search_result->Pop();
        }
    }
    return search_result;
}
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L340 | query-&gt;GetFloat32Vectors | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L342 | param.bucket_ids.empty | if_statement@342 (not param.bucket_ids.empty()) | 当前参考未静态绑定；见下方边界说明 |

| L343 | candidate_buckets.reserve | if_statement@342 (not param.bucket_ids.empty()) | 当前参考未静态绑定；见下方边界说明 |

| L343 | param.bucket_ids.size | if_statement@342 (not param.bucket_ids.empty()) | 当前参考未静态绑定；见下方边界说明 |

| L345 | candidate_buckets.push_back | if_statement@342 (not param.bucket_ids.empty()) → for_range_loop@344 | 当前参考未静态绑定；见下方边界说明 |

| L348 | partition_strategy_-&gt;ClassifyDatasForSearch | if_statement@342 (not param.bucket_ids.empty()) [else 分支] | [GNOIMIPartition::ClassifyDatasForSearch · L221](gno_imi_partition.md#L221)；[IVFPartitionStrategy::ClassifyDatasForSearch · L64](ivf_partition_strategy_h.md#L64) |

| L351 | reasoning_ctx-&gt;RecordBucketSelection | if_statement@350 (reasoning_ctx != nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L357 | CHECK_ARGUMENT | if_statement@356 (buckets_per_data_ &gt; 1) | 当前参考未静态绑定；见下方边界说明 |

| L357 | std::numeric_limits&lt;int64_t&gt;::max | if_statement@356 (buckets_per_data_ &gt; 1) | 当前参考未静态绑定；见下方边界说明 |

| L362 | DistanceHeap::MakeInstanceBySize&lt;true, false&gt; | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L369 | std::min&lt;uint64_t&gt; | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L370 | std::max&lt;uint64_t&gt; | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L370 | this-&gt;GetNumElements | 函数本体；短路求值/提前返回见源码 | [IVF::GetNumElements · L291](ivf.md#L291) |

| L371 | candidate_ids.reserve | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L372 | candidate_labels.reserve | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L373 | scores.resize | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L376 | param.time_cost-&gt;CheckOvertime | lambda@375（定义体，执行时间取决于调用/调度） → if_statement@376 (param.time_cost == nullptr or not param.time_cost-&gt;CheckOvertime()) | 当前参考未静态绑定；见下方边界说明 |

| L380 | ctx.stats-&gt;is_timeout.store | lambda@375（定义体，执行时间取决于调用/调度） → if_statement@379 (ctx.stats != nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L386 | candidate_ids.empty | lambda@385（定义体，执行时间取决于调用/调度） → if_statement@386 (candidate_ids.empty()) | 当前参考未静态绑定；见下方边界说明 |

| L389 | is_timed_out | lambda@385（定义体，执行时间取决于调用/调度） → if_statement@389 (is_timed_out()) | 当前参考未静态绑定；见下方边界说明 |

| L392 | request.distance_batch_func_ | lambda@385（定义体，执行时间取决于调用/调度） | 当前参考未静态绑定；见下方边界说明 |

| L393 | candidate_labels.data | lambda@385（定义体，执行时间取决于调用/调度） | 当前参考未静态绑定；见下方边界说明 |

| L393 | candidate_labels.size | lambda@385（定义体，执行时间取决于调用/调度） | 当前参考未静态绑定；见下方边界说明 |

| L393 | scores.data | lambda@385（定义体，执行时间取决于调用/调度） | 当前参考未静态绑定；见下方边界说明 |

| L395 | ctx.stats-&gt;AddDistance | lambda@385（定义体，执行时间取决于调用/调度） → if_statement@394 (ctx.stats != nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L397 | candidate_ids.size | lambda@385（定义体，执行时间取决于调用/调度） → if_statement@394 (ctx.stats != nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L399 | candidate_ids.size | lambda@385（定义体，执行时间取决于调用/调度） → for_statement@399 i &lt; candidate_ids.size() | 当前参考未静态绑定；见下方边界说明 |

| L400 | CHECK_ARGUMENT | lambda@385（定义体，执行时间取决于调用/调度） → for_statement@399 i &lt; candidate_ids.size() | 当前参考未静态绑定；见下方边界说明 |

| L400 | std::isfinite | lambda@385（定义体，执行时间取决于调用/调度） → for_statement@399 i &lt; candidate_ids.size() | 当前参考未静态绑定；见下方边界说明 |

| L403 | filter-&gt;CheckValid | lambda@385（定义体，执行时间取决于调用/调度） → for_statement@399 i &lt; candidate_ids.size() → if_statement@403 (filter != nullptr and not filter-&gt;CheckValid(origin_id)) | 当前参考未静态绑定；见下方边界说明 |

| L405 | reasoning_ctx-&gt;RecordFilterReject | lambda@385（定义体，执行时间取决于调用/调度） → for_statement@399 i &lt; candidate_ids.size() → if_statement@403 (filter != nullptr and not filter-&gt;CheckValid(origin_id)) → if_statement@404 (reasoning_ctx != nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L410 | reasoning_ctx-&gt;RecordVisit | lambda@385（定义体，执行时间取决于调用/调度） → for_statement@399 i &lt; candidate_ids.size() → if_statement@409 (reasoning_ctx != nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L412 | search_result-&gt;Push | lambda@385（定义体，执行时间取决于调用/调度） → for_statement@399 i &lt; candidate_ids.size() | 当前参考未静态绑定；见下方边界说明 |

| L413 | search_result-&gt;Size | lambda@385（定义体，执行时间取决于调用/调度） → for_statement@399 i &lt; candidate_ids.size() → while_statement@413 (search_result-&gt;Size() &gt; static_cast&lt;uint64_t&gt;(topk)) | 当前参考未静态绑定；见下方边界说明 |

| L415 | reasoning_ctx-&gt;RecordEviction | lambda@385（定义体，执行时间取决于调用/调度） → for_statement@399 i &lt; candidate_ids.size() → while_statement@413 (search_result-&gt;Size() &gt; static_cast&lt;uint64_t&gt;(topk)) → if_statement@414 (reasoning_ctx != nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L415 | search_result-&gt;Top | lambda@385（定义体，执行时间取决于调用/调度） → for_statement@399 i &lt; candidate_ids.size() → while_statement@413 (search_result-&gt;Size() &gt; static_cast&lt;uint64_t&gt;(topk)) → if_statement@414 (reasoning_ctx != nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L418 | search_result-&gt;Pop | lambda@385（定义体，执行时间取决于调用/调度） → for_statement@399 i &lt; candidate_ids.size() → while_statement@413 (search_result-&gt;Size() &gt; static_cast&lt;uint64_t&gt;(topk)) | 当前参考未静态绑定；见下方边界说明 |

| L421 | candidate_ids.clear | lambda@385（定义体，执行时间取决于调用/调度） | 当前参考未静态绑定；见下方边界说明 |

| L422 | candidate_labels.clear | lambda@385（定义体，执行时间取决于调用/调度） | 当前参考未静态绑定；见下方边界说明 |

| L428 | is_timed_out | for_range_loop@427 → if_statement@428 (is_timed_out()) | 当前参考未静态绑定；见下方边界说明 |

| L435 | param.executors.empty | for_range_loop@427 → if_statement@435 (not param.executors.empty()) | 当前参考未静态绑定；见下方边界说明 |

| L436 | param.executors[0]-&gt;Clear | for_range_loop@427 → if_statement@435 (not param.executors.empty()) | 当前参考未静态绑定；见下方边界说明 |

| L437 | param.executors[0]-&gt;Run | for_range_loop@427 → if_statement@435 (not param.executors.empty()) | 当前参考未静态绑定；见下方边界说明 |

| L439 | bucket_-&gt;GetBucketSize | for_range_loop@427 | [BucketDataCell::GetBucketSize · L180](bucket_datacell_h.md#L180) |

| L440 | bucket_-&gt;GetInnerIds | for_range_loop@427 | [BucketDataCell::GetInnerIds · L120](bucket_datacell_h.md#L120) |

| L443 | std::numeric_limits&lt;InnerIdType&gt;::max | for_range_loop@427 → for_statement@441 offset &lt; bucket_size → if_statement@443 (inner_id == std::numeric_limits&lt;InnerIdType&gt;::max()) | 当前参考未静态绑定；见下方边界说明 |

| L447 | attr_filter-&gt;CheckValid | for_range_loop@427 → for_statement@441 offset &lt; bucket_size → if_statement@447 (attr_filter != nullptr and not attr_filter-&gt;CheckValid(offset)) | 当前参考未静态绑定；见下方边界说明 |

| L449 | reasoning_ctx-&gt;RecordFilterReject | for_range_loop@427 → for_statement@441 offset &lt; bucket_size → if_statement@447 (attr_filter != nullptr and not attr_filter-&gt;CheckValid(offset)) → if_statement@448 (reasoning_ctx != nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L453 | candidate_ids.push_back | for_range_loop@427 → for_statement@441 offset &lt; bucket_size | 当前参考未静态绑定；见下方边界说明 |

| L454 | candidate_labels.push_back | for_range_loop@427 → for_statement@441 offset &lt; bucket_size | 当前参考未静态绑定；见下方边界说明 |

| L454 | label_table_-&gt;GetLabelById | for_range_loop@427 → for_statement@441 offset &lt; bucket_size | 当前参考未静态绑定；见下方边界说明 |

| L455 | candidate_ids.size | for_range_loop@427 → for_statement@441 offset &lt; bucket_size → if_statement@455 (candidate_ids.size() == batch_capacity and not submit_batch()) | 当前参考未静态绑定；见下方边界说明 |

| L455 | submit_batch | for_range_loop@427 → for_statement@441 offset &lt; bucket_size → if_statement@455 (candidate_ids.size() == batch_capacity and not submit_batch()) | 当前参考未静态绑定；见下方边界说明 |

| L465 | submit_batch | if_statement@464 (not timed_out) | 当前参考未静态绑定；见下方边界说明 |

| L473 | search_result-&gt;Empty | while_statement@473 (not search_result-&gt;Empty()) | 当前参考未静态绑定；见下方边界说明 |

| L474 | search_result-&gt;Top | while_statement@473 (not search_result-&gt;Empty()) | 当前参考未静态绑定；见下方边界说明 |

| L476 | id_to_min_score.find | while_statement@473 (not search_result-&gt;Empty()) | 当前参考未静态绑定；见下方边界说明 |

| L477 | id_to_min_score.end | while_statement@473 (not search_result-&gt;Empty()) → if_statement@477 (iter == id_to_min_score.end() or score &lt; iter-&gt;second) | 当前参考未静态绑定；见下方边界说明 |

| L480 | search_result-&gt;Pop | while_statement@473 (not search_result-&gt;Empty()) | 当前参考未静态绑定；见下方边界说明 |

| L484 | search_result-&gt;Push | for_range_loop@483 | 当前参考未静态绑定；见下方边界说明 |

| L485 | search_result-&gt;Size | for_range_loop@483 → if_statement@485 (search_result-&gt;Size() &gt; static_cast&lt;uint64_t&gt;(origin_topk)) | 当前参考未静态绑定；见下方边界说明 |

| L486 | search_result-&gt;Pop | for_range_loop@483 → if_statement@485 (search_result-&gt;Size() &gt; static_cast&lt;uint64_t&gt;(origin_topk)) | 当前参考未静态绑定；见下方边界说明 |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L492"></a>

## `IVF::SearchWithRequest`

源码位置：`src/algorithm/ivf/ivf_search.cpp:492–797`。

按源码顺序先参数校验，再分离仅路由、批查询、属性/诊断、自定义距离、Range、KNN。每个提前 return 都终止当前分支。批查询的递归请求只有一条 query，不能无限展开成相同状态。

### 完整函数

```cpp
DatasetPtr
IVF::SearchWithRequest(const SearchRequest& request) const {
    ValidateSearchThreshold(request.threshold_);
    SearchStatistics stats;
    QueryContext ctx{.alloc = request.search_allocator_, .stats = &stats};

    bool is_range = (request.mode_ == SearchMode::RANGE_SEARCH);

    auto param = this->create_search_param(request.params_str_, request.filter_);
    const bool use_custom_distance = request.distance_batch_func_ != nullptr;
    if (use_custom_distance) {
        CHECK_ARGUMENT(request.distance_batch_size_ > 0,
                       "custom query distance batch size must be greater than 0");
        CHECK_ARGUMENT(not is_range, "IVF custom query distance only supports KNN search");
        CHECK_ARGUMENT(not param.disable_bucket_scan,
                       "IVF custom query distance does not support disable_bucket_scan");
        CHECK_ARGUMENT(request.topk_ > 0, "topk must be greater than 0");
        CHECK_ARGUMENT(param.parallel_search_thread_count == 1,
                       "IVF custom query distance does not support parallel search");
        param.enable_reorder = false;
    }
    param.query_context = &ctx;

    if (not request.bucket_ids_.empty()) {
        auto query_check = request.query_;
        CHECK_ARGUMENT(query_check != nullptr, "query dataset cannot be null");
        CHECK_ARGUMENT(request.bucket_ids_.size() == query_check->GetNumElements(),
                       fmt::format("bucket_ids_ size must match the number of query vectors; "
                                   "got {} bucket lists for {} queries",
                                   request.bucket_ids_.size(),
                                   query_check->GetNumElements()));
        CHECK_ARGUMENT(query_check->GetFloat32Vectors() != nullptr,
                       "query float32 vectors cannot be null");
        CHECK_ARGUMENT(query_check->GetDim() == this->dim_,
                       "query dimension must match index dimension");
        CHECK_ARGUMENT(not param.disable_bucket_scan,
                       "bucket_ids_ is incompatible with disable_bucket_scan mode");
        for (uint64_t query_idx = 0; query_idx < request.bucket_ids_.size(); ++query_idx) {
            const auto& ids = request.bucket_ids_[query_idx];
            CHECK_ARGUMENT(not ids.empty(),
                           fmt::format("bucket_ids_[{}] must not be empty; "
                                       "use empty outer vector for default routing",
                                       query_idx));
            std::set<int64_t> seen_ids;
            for (auto id : ids) {
                CHECK_ARGUMENT(
                    id >= 0,
                    fmt::format(
                        "bucket_id {} out of range [0, {})", id, this->bucket_->bucket_count_));
                CHECK_ARGUMENT(
                    id < static_cast<int64_t>(this->bucket_->bucket_count_),
                    fmt::format(
                        "bucket_id {} out of range [0, {})", id, this->bucket_->bucket_count_));
                CHECK_ARGUMENT(seen_ids.insert(id).second,
                               fmt::format("duplicate bucket_id {}", id));
            }
        }
        if (query_check->GetNumElements() == 1) {
            param.bucket_ids.assign(request.bucket_ids_[0].begin(), request.bucket_ids_[0].end());
        }
    }

    auto query = request.query_;
    if (use_custom_distance) {
        CHECK_ARGUMENT(query != nullptr, "query dataset cannot be null");
        CHECK_ARGUMENT(query->GetNumElements() == 1,
                       "IVF custom search requires exactly one query");
        CHECK_ARGUMENT(query->GetFloat32Vectors() != nullptr,
                       "query float32 vectors cannot be null");
        CHECK_ARGUMENT(query->GetDim() == this->dim_, "query dimension must match index dimension");
    }
    if (param.disable_bucket_scan) {
        CHECK_ARGUMENT(query != nullptr, "query dataset cannot be null");
        CHECK_ARGUMENT(query->GetNumElements() >= 1,
                       "disable bucket scan requires at least one query");
        CHECK_ARGUMENT(query->GetFloat32Vectors() != nullptr,
                       "query float32 vectors cannot be null");
        CHECK_ARGUMENT(query->GetDim() == this->dim_, "query dimension must match index dimension");
        CHECK_ARGUMENT(not request.threshold_.has_value(),
                       "threshold filtering is not supported with disable_bucket_scan");
        auto result = this->route_buckets_only(query, param, ctx);
        result->Statistics(stats.Dump());
        return result;
    }

    if (query != nullptr && query->GetNumElements() > 1) {
        CHECK_ARGUMENT(not is_range, "IVF batch search only supports KNN search");
        CHECK_ARGUMENT(not use_custom_distance,
                       "IVF batch search does not support custom query distance");
        CHECK_ARGUMENT(request.expected_labels_.empty(),
                       "IVF batch search does not support expected labels");
        CHECK_ARGUMENT(request.topk_ > 0, "topk must be greater than 0");
        CHECK_ARGUMENT(query->GetFloat32Vectors() != nullptr,
                       "query float32 vectors cannot be null");
        CHECK_ARGUMENT(query->GetDim() == this->dim_, "query dimension must match index dimension");

        const auto num_queries = query->GetNumElements();
        const auto total_slots = num_queries * request.topk_;
        auto* alloc = select_query_allocator(ctx.alloc, this->allocator_);
        auto* ids = static_cast<int64_t*>(alloc->Allocate(sizeof(int64_t) * total_slots));
        auto* distances = static_cast<float*>(alloc->Allocate(sizeof(float) * total_slots));
        std::fill_n(ids, total_slots, -1);
        std::fill_n(distances, total_slots, std::numeric_limits<float>::infinity());

        const auto* query_data = query->GetFloat32Vectors();
        auto base_request = request;
        base_request.expected_labels_.clear();
        if (not request.bucket_ids_.empty()) {
            base_request.bucket_ids_.clear();
        }
        auto search_func = [&](int64_t query_idx) -> void {
            auto one_query = Dataset::Make();
            one_query->NumElements(1)
                ->Dim(query->GetDim())
                ->Float32Vectors(query_data + query_idx * query->GetDim())
                ->Owner(false);

            auto one_request = base_request;
            one_request.query_ = one_query;
            if (not request.bucket_ids_.empty()) {
                one_request.bucket_ids_ = {request.bucket_ids_[query_idx]};
            }
            JsonType json = JsonType::Parse(base_request.params_str_);
            if (json.Contains("ivf")) {
                json["ivf"]["parallelism"].SetInt64(1);
            }
            one_request.params_str_ = json.Dump();
            auto one_result = this->SearchWithRequest(one_request);
            const auto count = std::min(request.topk_, one_result->GetDim());
            if (count > 0) {
                std::copy_n(one_result->GetIds(), count, ids + query_idx * request.topk_);
                std::copy_n(
                    one_result->GetDistances(), count, distances + query_idx * request.topk_);
            }
        };

        if (this->thread_pool_ != nullptr and param.parallel_search_thread_count > 1) {
            std::vector<std::future<void>> futures;
            for (int64_t query_idx = 0; query_idx < num_queries; ++query_idx) {
                auto future = this->thread_pool_->GeneralEnqueue(search_func, query_idx);
                futures.emplace_back(std::move(future));
            }
            for (auto& future : futures) {
                future.get();
            }
        } else {
            for (int64_t query_idx = 0; query_idx < num_queries; ++query_idx) {
                search_func(query_idx);
            }
        }
        auto result = Dataset::Make()
                          ->NumElements(num_queries)
                          ->Dim(request.topk_)
                          ->Ids(ids)
                          ->Distances(distances)
                          ->Owner(true, alloc);
        result->Statistics(stats.Dump());
        return result;
    }

    if (request.enable_attribute_filter_ and this->attr_filter_index_ != nullptr) {
        ExprPtr expression = request.expression_;
        if (expression == nullptr) {
            auto& schema = this->attr_filter_index_->field_type_map_;
            expression = AstParse(request.attribute_filter_str_, &schema);
        }
        for (int64_t i = 0; i < param.parallel_search_thread_count; ++i) {
            auto executor =
                Executor::MakeInstance(this->allocator_, expression, this->attr_filter_index_);
            executor->Init();
            param.executors.emplace_back(executor);
        }
    }
    std::shared_ptr<ReasoningContext> reasoning_ctx;
    if (not request.expected_labels_.empty()) {
        reasoning_ctx = std::make_shared<ReasoningContext>(this->allocator_);
        reasoning_ctx->SetSearchParams(
            request.topk_, "IVF", use_reorder_, request.filter_ != nullptr);

        UnorderedMap<int64_t, InnerIdType> label_to_inner_id(this->allocator_);
        std::vector<std::tuple<InnerIdType, BucketIdType, InnerIdType>> locations;
        {
            std::shared_lock<std::shared_mutex> lock(this->label_lookup_mutex_);
            locations.reserve(request.expected_labels_.size());
            for (const auto& label : request.expected_labels_) {
                auto [success, inner_id] = this->label_table_->TryGetIdByLabel(label, true);
                if (success) {
                    label_to_inner_id[label] = inner_id;
                    auto [bucket_id, offset_id] = this->get_location(inner_id);
                    locations.emplace_back(inner_id, bucket_id, offset_id);
                }
            }
        }

        Vector<int64_t> expected_labels_vec(this->allocator_);
        expected_labels_vec.reserve(request.expected_labels_.size());
        for (const auto& label : request.expected_labels_) {
            expected_labels_vec.push_back(label);
        }
        reasoning_ctx->InitializeExpectedTargets(expected_labels_vec, label_to_inner_id);

        const auto* query_data = query->GetFloat32Vectors();
        auto computer = this->bucket_->FactoryComputer(query_data);
        for (const auto& [inner_id, bucket_id, offset_id] : locations) {
            float dist = this->bucket_->QueryOneById(computer, bucket_id, offset_id);
            if (ctx.stats != nullptr) {
                ctx.stats->AddDistance(SearchStatistics::DistancePhase::APPROXIMATE,
                                       this->bucket_->backend_);
            }
            reasoning_ctx->SetTrueDistance(inner_id, dist);
        }
        ctx.reasoning_ctx = reasoning_ctx.get();
    }

    if (use_custom_distance) {
        param.search_mode = KNN_SEARCH;
        param.topk = request.topk_;
        auto search_result =
            search_with_custom_distance(query, request, param, ctx, reasoning_ctx.get());
        filter_search_result_by_threshold(
            search_result, request.threshold_, select_query_allocator(ctx.alloc, this->allocator_));
        if (search_result == nullptr || search_result->Empty()) {
            auto dataset_results = DatasetImpl::MakeEmptyDataset();
            this->AttachReasoningReport(dataset_results, reasoning_ctx.get());
            dataset_results->Statistics(stats.Dump());
            return dataset_results;
        }
        auto dataset_results = this->pack_knn_result(search_result, ctx.alloc);
        this->AttachReasoningReport(dataset_results, reasoning_ctx.get());
        dataset_results->Statistics(stats.Dump());
        return dataset_results;
    }

    if (is_range) {
        param.search_mode = RANGE_SEARCH;
        param.radius = request.radius_;
        param.range_search_limit_size = static_cast<int>(request.limited_size_);
        if (use_reorder_ and param.enable_reorder and request.limited_size_ > 0) {
            CHECK_ARGUMENT(param.factor > 0.0F,
                           fmt::format("factor must be positive when use_reorder is true, got {}",
                                       param.factor));
            param.range_search_limit_size =
                static_cast<int>(param.factor * static_cast<float>(request.limited_size_));
        }
        auto search_result = this->search<RANGE_SEARCH>(query, param, ctx, reasoning_ctx.get());
        if (use_reorder_ and param.enable_reorder) {
            int64_t k = (request.limited_size_ > 0) ? request.limited_size_
                                                    : static_cast<int64_t>(search_result->Size());
            auto result = reorder(
                k, search_result, query->GetFloat32Vectors(), param, ctx, reasoning_ctx.get());
            result->Statistics(stats.Dump());
            this->AttachReasoningReport(result, reasoning_ctx.get());
            return result;
        }
        auto dataset_results = this->pack_knn_result(search_result, ctx.alloc);
        dataset_results->Statistics(stats.Dump());
        this->AttachReasoningReport(dataset_results, reasoning_ctx.get());
        return dataset_results;
    }

    // KNN mode
    param.search_mode = KNN_SEARCH;
    param.topk = request.topk_;
    if (use_reorder_ and param.enable_reorder) {
        CHECK_ARGUMENT(
            param.factor > 0.0F,
            fmt::format("factor must be positive when use_reorder is true, got {}", param.factor));
        param.topk = static_cast<int64_t>(param.factor * static_cast<float>(request.topk_));
        if (request.threshold_.has_value()) {
            param.topk = std::max(param.topk, request.topk_);
        }
    }
    const bool reorder_enabled = use_reorder_ and param.enable_reorder;
    // Reordered searches defer the finite bound to exact distances, but bucket selection still
    // needs threshold-mode state so non-finite approximations cannot consume the rerank pool.
    param.distance_threshold = request.threshold_;
    auto search_result = this->search<KNN_SEARCH>(query, param, ctx, reasoning_ctx.get());
    if (reorder_enabled) {
        auto result = reorder(request.threshold_.has_value() ? param.topk : request.topk_,
                              search_result,
                              query->GetFloat32Vectors(),
                              param,
                              ctx,
                              reasoning_ctx.get(),
                              request.threshold_);
        result = FilterDatasetByThreshold(result, request.threshold_, ctx.alloc, request.topk_);
        AttachReasoningReport(result, reasoning_ctx.get());
        result->Statistics(stats.Dump());
        return result;
    }
    filter_search_result_by_threshold(
        search_result, request.threshold_, select_query_allocator(ctx.alloc, this->allocator_));
    if (search_result == nullptr || search_result->Empty()) {
        auto dataset_results = DatasetImpl::MakeEmptyDataset();
        this->AttachReasoningReport(dataset_results, reasoning_ctx.get());
        dataset_results->Statistics(stats.Dump());
        return dataset_results;
    }

    auto dataset_results = this->pack_knn_result(search_result, ctx.alloc);
    dataset_results->Statistics(stats.Dump());

    this->AttachReasoningReport(dataset_results, reasoning_ctx.get());

    return dataset_results;
}
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L494 | ValidateSearchThreshold | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L500 | this-&gt;create_search_param | 函数本体；短路求值/提前返回见源码 | [IVF::create_search_param · L86](ivf_search.md#L86) |

| L503 | CHECK_ARGUMENT | if_statement@502 (use_custom_distance) | 当前参考未静态绑定；见下方边界说明 |

| L505 | CHECK_ARGUMENT | if_statement@502 (use_custom_distance) | 当前参考未静态绑定；见下方边界说明 |

| L506 | CHECK_ARGUMENT | if_statement@502 (use_custom_distance) | 当前参考未静态绑定；见下方边界说明 |

| L508 | CHECK_ARGUMENT | if_statement@502 (use_custom_distance) | 当前参考未静态绑定；见下方边界说明 |

| L509 | CHECK_ARGUMENT | if_statement@502 (use_custom_distance) | 当前参考未静态绑定；见下方边界说明 |

| L515 | request.bucket_ids_.empty | if_statement@515 (not request.bucket_ids_.empty()) | 当前参考未静态绑定；见下方边界说明 |

| L517 | CHECK_ARGUMENT | if_statement@515 (not request.bucket_ids_.empty()) | 当前参考未静态绑定；见下方边界说明 |

| L518 | CHECK_ARGUMENT | if_statement@515 (not request.bucket_ids_.empty()) | 当前参考未静态绑定；见下方边界说明 |

| L518 | request.bucket_ids_.size | if_statement@515 (not request.bucket_ids_.empty()) | 当前参考未静态绑定；见下方边界说明 |

| L518 | query_check-&gt;GetNumElements | if_statement@515 (not request.bucket_ids_.empty()) | 当前参考未静态绑定；见下方边界说明 |

| L519 | fmt::format | if_statement@515 (not request.bucket_ids_.empty()) | 当前参考未静态绑定；见下方边界说明 |

| L521 | request.bucket_ids_.size | if_statement@515 (not request.bucket_ids_.empty()) | 当前参考未静态绑定；见下方边界说明 |

| L522 | query_check-&gt;GetNumElements | if_statement@515 (not request.bucket_ids_.empty()) | 当前参考未静态绑定；见下方边界说明 |

| L523 | CHECK_ARGUMENT | if_statement@515 (not request.bucket_ids_.empty()) | 当前参考未静态绑定；见下方边界说明 |

| L523 | query_check-&gt;GetFloat32Vectors | if_statement@515 (not request.bucket_ids_.empty()) | 当前参考未静态绑定；见下方边界说明 |

| L525 | CHECK_ARGUMENT | if_statement@515 (not request.bucket_ids_.empty()) | 当前参考未静态绑定；见下方边界说明 |

| L525 | query_check-&gt;GetDim | if_statement@515 (not request.bucket_ids_.empty()) | 当前参考未静态绑定；见下方边界说明 |

| L527 | CHECK_ARGUMENT | if_statement@515 (not request.bucket_ids_.empty()) | 当前参考未静态绑定；见下方边界说明 |

| L529 | request.bucket_ids_.size | if_statement@515 (not request.bucket_ids_.empty()) → for_statement@529 query_idx &lt; request.bucket_ids_.size() | 当前参考未静态绑定；见下方边界说明 |

| L531 | CHECK_ARGUMENT | if_statement@515 (not request.bucket_ids_.empty()) → for_statement@529 query_idx &lt; request.bucket_ids_.size() | 当前参考未静态绑定；见下方边界说明 |

| L531 | ids.empty | if_statement@515 (not request.bucket_ids_.empty()) → for_statement@529 query_idx &lt; request.bucket_ids_.size() | 当前参考未静态绑定；见下方边界说明 |

| L532 | fmt::format | if_statement@515 (not request.bucket_ids_.empty()) → for_statement@529 query_idx &lt; request.bucket_ids_.size() | 当前参考未静态绑定；见下方边界说明 |

| L537 | CHECK_ARGUMENT | if_statement@515 (not request.bucket_ids_.empty()) → for_statement@529 query_idx &lt; request.bucket_ids_.size() → for_range_loop@536 | 当前参考未静态绑定；见下方边界说明 |

| L539 | fmt::format | if_statement@515 (not request.bucket_ids_.empty()) → for_statement@529 query_idx &lt; request.bucket_ids_.size() → for_range_loop@536 | 当前参考未静态绑定；见下方边界说明 |

| L541 | CHECK_ARGUMENT | if_statement@515 (not request.bucket_ids_.empty()) → for_statement@529 query_idx &lt; request.bucket_ids_.size() → for_range_loop@536 | 当前参考未静态绑定；见下方边界说明 |

| L543 | fmt::format | if_statement@515 (not request.bucket_ids_.empty()) → for_statement@529 query_idx &lt; request.bucket_ids_.size() → for_range_loop@536 | 当前参考未静态绑定；见下方边界说明 |

| L545 | CHECK_ARGUMENT | if_statement@515 (not request.bucket_ids_.empty()) → for_statement@529 query_idx &lt; request.bucket_ids_.size() → for_range_loop@536 | 当前参考未静态绑定；见下方边界说明 |

| L545 | seen_ids.insert | if_statement@515 (not request.bucket_ids_.empty()) → for_statement@529 query_idx &lt; request.bucket_ids_.size() → for_range_loop@536 | 当前参考未静态绑定；见下方边界说明 |

| L546 | fmt::format | if_statement@515 (not request.bucket_ids_.empty()) → for_statement@529 query_idx &lt; request.bucket_ids_.size() → for_range_loop@536 | 当前参考未静态绑定；见下方边界说明 |

| L549 | query_check-&gt;GetNumElements | if_statement@515 (not request.bucket_ids_.empty()) → if_statement@549 (query_check-&gt;GetNumElements() == 1) | 当前参考未静态绑定；见下方边界说明 |

| L550 | param.bucket_ids.assign | if_statement@515 (not request.bucket_ids_.empty()) → if_statement@549 (query_check-&gt;GetNumElements() == 1) | 当前参考未静态绑定；见下方边界说明 |

| L550 | request.bucket_ids_[0].begin | if_statement@515 (not request.bucket_ids_.empty()) → if_statement@549 (query_check-&gt;GetNumElements() == 1) | 当前参考未静态绑定；见下方边界说明 |

| L550 | request.bucket_ids_[0].end | if_statement@515 (not request.bucket_ids_.empty()) → if_statement@549 (query_check-&gt;GetNumElements() == 1) | 当前参考未静态绑定；见下方边界说明 |

| L556 | CHECK_ARGUMENT | if_statement@555 (use_custom_distance) | 当前参考未静态绑定；见下方边界说明 |

| L557 | CHECK_ARGUMENT | if_statement@555 (use_custom_distance) | 当前参考未静态绑定；见下方边界说明 |

| L557 | query-&gt;GetNumElements | if_statement@555 (use_custom_distance) | 当前参考未静态绑定；见下方边界说明 |

| L559 | CHECK_ARGUMENT | if_statement@555 (use_custom_distance) | 当前参考未静态绑定；见下方边界说明 |

| L559 | query-&gt;GetFloat32Vectors | if_statement@555 (use_custom_distance) | 当前参考未静态绑定；见下方边界说明 |

| L561 | CHECK_ARGUMENT | if_statement@555 (use_custom_distance) | 当前参考未静态绑定；见下方边界说明 |

| L561 | query-&gt;GetDim | if_statement@555 (use_custom_distance) | 当前参考未静态绑定；见下方边界说明 |

| L564 | CHECK_ARGUMENT | if_statement@563 (param.disable_bucket_scan) | 当前参考未静态绑定；见下方边界说明 |

| L565 | CHECK_ARGUMENT | if_statement@563 (param.disable_bucket_scan) | 当前参考未静态绑定；见下方边界说明 |

| L565 | query-&gt;GetNumElements | if_statement@563 (param.disable_bucket_scan) | 当前参考未静态绑定；见下方边界说明 |

| L567 | CHECK_ARGUMENT | if_statement@563 (param.disable_bucket_scan) | 当前参考未静态绑定；见下方边界说明 |

| L567 | query-&gt;GetFloat32Vectors | if_statement@563 (param.disable_bucket_scan) | 当前参考未静态绑定；见下方边界说明 |

| L569 | CHECK_ARGUMENT | if_statement@563 (param.disable_bucket_scan) | 当前参考未静态绑定；见下方边界说明 |

| L569 | query-&gt;GetDim | if_statement@563 (param.disable_bucket_scan) | 当前参考未静态绑定；见下方边界说明 |

| L570 | CHECK_ARGUMENT | if_statement@563 (param.disable_bucket_scan) | 当前参考未静态绑定；见下方边界说明 |

| L570 | request.threshold_.has_value | if_statement@563 (param.disable_bucket_scan) | 当前参考未静态绑定；见下方边界说明 |

| L572 | this-&gt;route_buckets_only | if_statement@563 (param.disable_bucket_scan) | [IVF::route_buckets_only · L110](ivf_search.md#L110) |

| L573 | result-&gt;Statistics | if_statement@563 (param.disable_bucket_scan) | 当前参考未静态绑定；见下方边界说明 |

| L573 | stats.Dump | if_statement@563 (param.disable_bucket_scan) | 当前参考未静态绑定；见下方边界说明 |

| L577 | query-&gt;GetNumElements | if_statement@577 (query != nullptr && query-&gt;GetNumElements() &gt; 1) | 当前参考未静态绑定；见下方边界说明 |

| L578 | CHECK_ARGUMENT | if_statement@577 (query != nullptr && query-&gt;GetNumElements() &gt; 1) | 当前参考未静态绑定；见下方边界说明 |

| L579 | CHECK_ARGUMENT | if_statement@577 (query != nullptr && query-&gt;GetNumElements() &gt; 1) | 当前参考未静态绑定；见下方边界说明 |

| L581 | CHECK_ARGUMENT | if_statement@577 (query != nullptr && query-&gt;GetNumElements() &gt; 1) | 当前参考未静态绑定；见下方边界说明 |

| L581 | request.expected_labels_.empty | if_statement@577 (query != nullptr && query-&gt;GetNumElements() &gt; 1) | 当前参考未静态绑定；见下方边界说明 |

| L583 | CHECK_ARGUMENT | if_statement@577 (query != nullptr && query-&gt;GetNumElements() &gt; 1) | 当前参考未静态绑定；见下方边界说明 |

| L584 | CHECK_ARGUMENT | if_statement@577 (query != nullptr && query-&gt;GetNumElements() &gt; 1) | 当前参考未静态绑定；见下方边界说明 |

| L584 | query-&gt;GetFloat32Vectors | if_statement@577 (query != nullptr && query-&gt;GetNumElements() &gt; 1) | 当前参考未静态绑定；见下方边界说明 |

| L586 | CHECK_ARGUMENT | if_statement@577 (query != nullptr && query-&gt;GetNumElements() &gt; 1) | 当前参考未静态绑定；见下方边界说明 |

| L586 | query-&gt;GetDim | if_statement@577 (query != nullptr && query-&gt;GetNumElements() &gt; 1) | 当前参考未静态绑定；见下方边界说明 |

| L588 | query-&gt;GetNumElements | if_statement@577 (query != nullptr && query-&gt;GetNumElements() &gt; 1) | 当前参考未静态绑定；见下方边界说明 |

| L590 | select_query_allocator | if_statement@577 (query != nullptr && query-&gt;GetNumElements() &gt; 1) | 当前参考未静态绑定；见下方边界说明 |

| L591 | alloc-&gt;Allocate | if_statement@577 (query != nullptr && query-&gt;GetNumElements() &gt; 1) | 当前参考未静态绑定；见下方边界说明 |

| L592 | alloc-&gt;Allocate | if_statement@577 (query != nullptr && query-&gt;GetNumElements() &gt; 1) | 当前参考未静态绑定；见下方边界说明 |

| L593 | std::fill_n | if_statement@577 (query != nullptr && query-&gt;GetNumElements() &gt; 1) | 当前参考未静态绑定；见下方边界说明 |

| L594 | std::fill_n | if_statement@577 (query != nullptr && query-&gt;GetNumElements() &gt; 1) | 当前参考未静态绑定；见下方边界说明 |

| L594 | std::numeric_limits&lt;float&gt;::infinity | if_statement@577 (query != nullptr && query-&gt;GetNumElements() &gt; 1) | 当前参考未静态绑定；见下方边界说明 |

| L596 | query-&gt;GetFloat32Vectors | if_statement@577 (query != nullptr && query-&gt;GetNumElements() &gt; 1) | 当前参考未静态绑定；见下方边界说明 |

| L598 | base_request.expected_labels_.clear | if_statement@577 (query != nullptr && query-&gt;GetNumElements() &gt; 1) | 当前参考未静态绑定；见下方边界说明 |

| L599 | request.bucket_ids_.empty | if_statement@577 (query != nullptr && query-&gt;GetNumElements() &gt; 1) → if_statement@599 (not request.bucket_ids_.empty()) | 当前参考未静态绑定；见下方边界说明 |

| L600 | base_request.bucket_ids_.clear | if_statement@577 (query != nullptr && query-&gt;GetNumElements() &gt; 1) → if_statement@599 (not request.bucket_ids_.empty()) | 当前参考未静态绑定；见下方边界说明 |

| L603 | Dataset::Make | if_statement@577 (query != nullptr && query-&gt;GetNumElements() &gt; 1) → lambda@602（定义体，执行时间取决于调用/调度） | 当前参考未静态绑定；见下方边界说明 |

| L604 | one_query-&gt;NumElements(1) -&gt;Dim(query-&gt;GetDim()) -&gt;Float32Vectors(query_data + query_idx * query-&gt;GetDim()) -&gt;Owner | if_statement@577 (query != nullptr && query-&gt;GetNumElements() &gt; 1) → lambda@602（定义体，执行时间取决于调用/调度） | 当前参考未静态绑定；见下方边界说明 |

| L604 | one_query-&gt;NumElements(1) -&gt;Dim(query-&gt;GetDim()) -&gt;Float32Vectors | if_statement@577 (query != nullptr && query-&gt;GetNumElements() &gt; 1) → lambda@602（定义体，执行时间取决于调用/调度） | 当前参考未静态绑定；见下方边界说明 |

| L604 | one_query-&gt;NumElements(1) -&gt;Dim | if_statement@577 (query != nullptr && query-&gt;GetNumElements() &gt; 1) → lambda@602（定义体，执行时间取决于调用/调度） | 当前参考未静态绑定；见下方边界说明 |

| L604 | one_query-&gt;NumElements | if_statement@577 (query != nullptr && query-&gt;GetNumElements() &gt; 1) → lambda@602（定义体，执行时间取决于调用/调度） | 当前参考未静态绑定；见下方边界说明 |

| L605 | query-&gt;GetDim | if_statement@577 (query != nullptr && query-&gt;GetNumElements() &gt; 1) → lambda@602（定义体，执行时间取决于调用/调度） | 当前参考未静态绑定；见下方边界说明 |

| L606 | query-&gt;GetDim | if_statement@577 (query != nullptr && query-&gt;GetNumElements() &gt; 1) → lambda@602（定义体，执行时间取决于调用/调度） | 当前参考未静态绑定；见下方边界说明 |

| L611 | request.bucket_ids_.empty | if_statement@577 (query != nullptr && query-&gt;GetNumElements() &gt; 1) → lambda@602（定义体，执行时间取决于调用/调度） → if_statement@611 (not request.bucket_ids_.empty()) | 当前参考未静态绑定；见下方边界说明 |

| L614 | JsonType::Parse | if_statement@577 (query != nullptr && query-&gt;GetNumElements() &gt; 1) → lambda@602（定义体，执行时间取决于调用/调度） | 当前参考未静态绑定；见下方边界说明 |

| L615 | json.Contains | if_statement@577 (query != nullptr && query-&gt;GetNumElements() &gt; 1) → lambda@602（定义体，执行时间取决于调用/调度） → if_statement@615 (json.Contains("ivf")) | 当前参考未静态绑定；见下方边界说明 |

| L616 | json["ivf"]["parallelism"].SetInt64 | if_statement@577 (query != nullptr && query-&gt;GetNumElements() &gt; 1) → lambda@602（定义体，执行时间取决于调用/调度） → if_statement@615 (json.Contains("ivf")) | 当前参考未静态绑定；见下方边界说明 |

| L618 | json.Dump | if_statement@577 (query != nullptr && query-&gt;GetNumElements() &gt; 1) → lambda@602（定义体，执行时间取决于调用/调度） | 当前参考未静态绑定；见下方边界说明 |

| L619 | this-&gt;SearchWithRequest | if_statement@577 (query != nullptr && query-&gt;GetNumElements() &gt; 1) → lambda@602（定义体，执行时间取决于调用/调度） | [IVF::SearchWithRequest · L492](ivf_search.md#L492) |

| L620 | std::min | if_statement@577 (query != nullptr && query-&gt;GetNumElements() &gt; 1) → lambda@602（定义体，执行时间取决于调用/调度） | 当前参考未静态绑定；见下方边界说明 |

| L620 | one_result-&gt;GetDim | if_statement@577 (query != nullptr && query-&gt;GetNumElements() &gt; 1) → lambda@602（定义体，执行时间取决于调用/调度） | 当前参考未静态绑定；见下方边界说明 |

| L622 | std::copy_n | if_statement@577 (query != nullptr && query-&gt;GetNumElements() &gt; 1) → lambda@602（定义体，执行时间取决于调用/调度） → if_statement@621 (count &gt; 0) | 当前参考未静态绑定；见下方边界说明 |

| L622 | one_result-&gt;GetIds | if_statement@577 (query != nullptr && query-&gt;GetNumElements() &gt; 1) → lambda@602（定义体，执行时间取决于调用/调度） → if_statement@621 (count &gt; 0) | 当前参考未静态绑定；见下方边界说明 |

| L623 | std::copy_n | if_statement@577 (query != nullptr && query-&gt;GetNumElements() &gt; 1) → lambda@602（定义体，执行时间取决于调用/调度） → if_statement@621 (count &gt; 0) | 当前参考未静态绑定；见下方边界说明 |

| L624 | one_result-&gt;GetDistances | if_statement@577 (query != nullptr && query-&gt;GetNumElements() &gt; 1) → lambda@602（定义体，执行时间取决于调用/调度） → if_statement@621 (count &gt; 0) | 当前参考未静态绑定；见下方边界说明 |

| L631 | this-&gt;thread_pool_-&gt;GeneralEnqueue | if_statement@577 (query != nullptr && query-&gt;GetNumElements() &gt; 1) → if_statement@628 (this-&gt;thread_pool_ != nullptr and param.parallel_search_thread_count &gt; 1) → for_statement@630 query_idx &lt; num_queries | 当前参考未静态绑定；见下方边界说明 |

| L632 | futures.emplace_back | if_statement@577 (query != nullptr && query-&gt;GetNumElements() &gt; 1) → if_statement@628 (this-&gt;thread_pool_ != nullptr and param.parallel_search_thread_count &gt; 1) → for_statement@630 query_idx &lt; num_queries | 当前参考未静态绑定；见下方边界说明 |

| L632 | std::move | if_statement@577 (query != nullptr && query-&gt;GetNumElements() &gt; 1) → if_statement@628 (this-&gt;thread_pool_ != nullptr and param.parallel_search_thread_count &gt; 1) → for_statement@630 query_idx &lt; num_queries | 当前参考未静态绑定；见下方边界说明 |

| L635 | future.get | if_statement@577 (query != nullptr && query-&gt;GetNumElements() &gt; 1) → if_statement@628 (this-&gt;thread_pool_ != nullptr and param.parallel_search_thread_count &gt; 1) → for_range_loop@634 | 当前参考未静态绑定；见下方边界说明 |

| L639 | search_func | if_statement@577 (query != nullptr && query-&gt;GetNumElements() &gt; 1) → if_statement@628 (this-&gt;thread_pool_ != nullptr and param.parallel_search_thread_count &gt; 1) [else 分支] → for_statement@638 query_idx &lt; num_queries | 当前参考未静态绑定；见下方边界说明 |

| L642 | Dataset::Make() -&gt;NumElements(num_queries) -&gt;Dim(request.topk_) -&gt;Ids(ids) -&gt;Distances(distances) -&gt;Owner | if_statement@577 (query != nullptr && query-&gt;GetNumElements() &gt; 1) | 当前参考未静态绑定；见下方边界说明 |

| L642 | Dataset::Make() -&gt;NumElements(num_queries) -&gt;Dim(request.topk_) -&gt;Ids(ids) -&gt;Distances | if_statement@577 (query != nullptr && query-&gt;GetNumElements() &gt; 1) | 当前参考未静态绑定；见下方边界说明 |

| L642 | Dataset::Make() -&gt;NumElements(num_queries) -&gt;Dim(request.topk_) -&gt;Ids | if_statement@577 (query != nullptr && query-&gt;GetNumElements() &gt; 1) | 当前参考未静态绑定；见下方边界说明 |

| L642 | Dataset::Make() -&gt;NumElements(num_queries) -&gt;Dim | if_statement@577 (query != nullptr && query-&gt;GetNumElements() &gt; 1) | 当前参考未静态绑定；见下方边界说明 |

| L642 | Dataset::Make() -&gt;NumElements | if_statement@577 (query != nullptr && query-&gt;GetNumElements() &gt; 1) | 当前参考未静态绑定；见下方边界说明 |

| L642 | Dataset::Make | if_statement@577 (query != nullptr && query-&gt;GetNumElements() &gt; 1) | 当前参考未静态绑定；见下方边界说明 |

| L648 | result-&gt;Statistics | if_statement@577 (query != nullptr && query-&gt;GetNumElements() &gt; 1) | 当前参考未静态绑定；见下方边界说明 |

| L648 | stats.Dump | if_statement@577 (query != nullptr && query-&gt;GetNumElements() &gt; 1) | 当前参考未静态绑定；见下方边界说明 |

| L656 | AstParse | if_statement@652 (request.enable_attribute_filter_ and this-&gt;attr_filter_index_ != nullptr) → if_statement@654 (expression == nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L660 | Executor::MakeInstance | if_statement@652 (request.enable_attribute_filter_ and this-&gt;attr_filter_index_ != nullptr) → for_statement@658 i &lt; param.parallel_search_thread_count | 当前参考未静态绑定；见下方边界说明 |

| L661 | executor-&gt;Init | if_statement@652 (request.enable_attribute_filter_ and this-&gt;attr_filter_index_ != nullptr) → for_statement@658 i &lt; param.parallel_search_thread_count | 当前参考未静态绑定；见下方边界说明 |

| L662 | param.executors.emplace_back | if_statement@652 (request.enable_attribute_filter_ and this-&gt;attr_filter_index_ != nullptr) → for_statement@658 i &lt; param.parallel_search_thread_count | 当前参考未静态绑定；见下方边界说明 |

| L666 | request.expected_labels_.empty | if_statement@666 (not request.expected_labels_.empty()) | 当前参考未静态绑定；见下方边界说明 |

| L667 | std::make_shared&lt;ReasoningContext&gt; | if_statement@666 (not request.expected_labels_.empty()) | 当前参考未静态绑定；见下方边界说明 |

| L668 | reasoning_ctx-&gt;SetSearchParams | if_statement@666 (not request.expected_labels_.empty()) | 当前参考未静态绑定；见下方边界说明 |

| L675 | locations.reserve | if_statement@666 (not request.expected_labels_.empty()) | 当前参考未静态绑定；见下方边界说明 |

| L675 | request.expected_labels_.size | if_statement@666 (not request.expected_labels_.empty()) | 当前参考未静态绑定；见下方边界说明 |

| L677 | this-&gt;label_table_-&gt;TryGetIdByLabel | if_statement@666 (not request.expected_labels_.empty()) → for_range_loop@676 | [LabelTable::TryGetIdByLabel · L96](label_table.md#L96) |

| L680 | this-&gt;get_location | if_statement@666 (not request.expected_labels_.empty()) → for_range_loop@676 → if_statement@678 (success) | [IVF::get_location · L312](ivf.md#L312) |

| L681 | locations.emplace_back | if_statement@666 (not request.expected_labels_.empty()) → for_range_loop@676 → if_statement@678 (success) | 当前参考未静态绑定；见下方边界说明 |

| L687 | expected_labels_vec.reserve | if_statement@666 (not request.expected_labels_.empty()) | 当前参考未静态绑定；见下方边界说明 |

| L687 | request.expected_labels_.size | if_statement@666 (not request.expected_labels_.empty()) | 当前参考未静态绑定；见下方边界说明 |

| L689 | expected_labels_vec.push_back | if_statement@666 (not request.expected_labels_.empty()) → for_range_loop@688 | 当前参考未静态绑定；见下方边界说明 |

| L691 | reasoning_ctx-&gt;InitializeExpectedTargets | if_statement@666 (not request.expected_labels_.empty()) | 当前参考未静态绑定；见下方边界说明 |

| L693 | query-&gt;GetFloat32Vectors | if_statement@666 (not request.expected_labels_.empty()) | 当前参考未静态绑定；见下方边界说明 |

| L694 | this-&gt;bucket_-&gt;FactoryComputer | if_statement@666 (not request.expected_labels_.empty()) | [BucketDataCell&lt;QuantTmpl, IOTmpl&gt;::FactoryComputer · L566](bucket_datacell_h.md#L566) |

| L696 | this-&gt;bucket_-&gt;QueryOneById | if_statement@666 (not request.expected_labels_.empty()) → for_range_loop@695 | [BucketDataCell::QueryOneById · L71](bucket_datacell_h.md#L71) |

| L698 | ctx.stats-&gt;AddDistance | if_statement@666 (not request.expected_labels_.empty()) → for_range_loop@695 → if_statement@697 (ctx.stats != nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L701 | reasoning_ctx-&gt;SetTrueDistance | if_statement@666 (not request.expected_labels_.empty()) → for_range_loop@695 | 当前参考未静态绑定；见下方边界说明 |

| L703 | reasoning_ctx.get | if_statement@666 (not request.expected_labels_.empty()) | 当前参考未静态绑定；见下方边界说明 |

| L710 | search_with_custom_distance | if_statement@706 (use_custom_distance) | [IVF::search_with_custom_distance · L334](ivf_search.md#L334) |

| L710 | reasoning_ctx.get | if_statement@706 (use_custom_distance) | 当前参考未静态绑定；见下方边界说明 |

| L711 | filter_search_result_by_threshold | if_statement@706 (use_custom_distance) | [InnerIndexInterface::filter_search_result_by_threshold · L1156](inner_index_interface.md#L1156) |

| L712 | select_query_allocator | if_statement@706 (use_custom_distance) | 当前参考未静态绑定；见下方边界说明 |

| L713 | search_result-&gt;Empty | if_statement@706 (use_custom_distance) → if_statement@713 (search_result == nullptr &#124;&#124; search_result-&gt;Empty()) | 当前参考未静态绑定；见下方边界说明 |

| L714 | DatasetImpl::MakeEmptyDataset | if_statement@706 (use_custom_distance) → if_statement@713 (search_result == nullptr &#124;&#124; search_result-&gt;Empty()) | 当前参考未静态绑定；见下方边界说明 |

| L715 | this-&gt;AttachReasoningReport | if_statement@706 (use_custom_distance) → if_statement@713 (search_result == nullptr &#124;&#124; search_result-&gt;Empty()) | [IVF::AttachReasoningReport · L799](ivf_search.md#L799) |

| L715 | reasoning_ctx.get | if_statement@706 (use_custom_distance) → if_statement@713 (search_result == nullptr &#124;&#124; search_result-&gt;Empty()) | 当前参考未静态绑定；见下方边界说明 |

| L716 | dataset_results-&gt;Statistics | if_statement@706 (use_custom_distance) → if_statement@713 (search_result == nullptr &#124;&#124; search_result-&gt;Empty()) | 当前参考未静态绑定；见下方边界说明 |

| L716 | stats.Dump | if_statement@706 (use_custom_distance) → if_statement@713 (search_result == nullptr &#124;&#124; search_result-&gt;Empty()) | 当前参考未静态绑定；见下方边界说明 |

| L719 | this-&gt;pack_knn_result | if_statement@706 (use_custom_distance) | [InnerIndexInterface::pack_knn_result · L1140](inner_index_interface.md#L1140) |

| L720 | this-&gt;AttachReasoningReport | if_statement@706 (use_custom_distance) | [IVF::AttachReasoningReport · L799](ivf_search.md#L799) |

| L720 | reasoning_ctx.get | if_statement@706 (use_custom_distance) | 当前参考未静态绑定；见下方边界说明 |

| L721 | dataset_results-&gt;Statistics | if_statement@706 (use_custom_distance) | 当前参考未静态绑定；见下方边界说明 |

| L721 | stats.Dump | if_statement@706 (use_custom_distance) | 当前参考未静态绑定；见下方边界说明 |

| L730 | CHECK_ARGUMENT | if_statement@725 (is_range) → if_statement@729 (use_reorder_ and param.enable_reorder and request.limited_size_ &gt; 0) | 当前参考未静态绑定；见下方边界说明 |

| L731 | fmt::format | if_statement@725 (is_range) → if_statement@729 (use_reorder_ and param.enable_reorder and request.limited_size_ &gt; 0) | 当前参考未静态绑定；见下方边界说明 |

| L736 | this-&gt;search&lt;RANGE_SEARCH&gt; | if_statement@725 (is_range) | [IVF::search · L199](ivf_search.md#L199) |

| L736 | reasoning_ctx.get | if_statement@725 (is_range) | 当前参考未静态绑定；见下方边界说明 |

| L739 | search_result-&gt;Size | if_statement@725 (is_range) → if_statement@737 (use_reorder_ and param.enable_reorder) → conditional_expression@738 (request.limited_size_ &gt; 0) | 当前参考未静态绑定；见下方边界说明 |

| L740 | reorder | if_statement@725 (is_range) → if_statement@737 (use_reorder_ and param.enable_reorder) | [IVF::reorder · L183](ivf_search.md#L183) |

| L741 | query-&gt;GetFloat32Vectors | if_statement@725 (is_range) → if_statement@737 (use_reorder_ and param.enable_reorder) | 当前参考未静态绑定；见下方边界说明 |

| L741 | reasoning_ctx.get | if_statement@725 (is_range) → if_statement@737 (use_reorder_ and param.enable_reorder) | 当前参考未静态绑定；见下方边界说明 |

| L742 | result-&gt;Statistics | if_statement@725 (is_range) → if_statement@737 (use_reorder_ and param.enable_reorder) | 当前参考未静态绑定；见下方边界说明 |

| L742 | stats.Dump | if_statement@725 (is_range) → if_statement@737 (use_reorder_ and param.enable_reorder) | 当前参考未静态绑定；见下方边界说明 |

| L743 | this-&gt;AttachReasoningReport | if_statement@725 (is_range) → if_statement@737 (use_reorder_ and param.enable_reorder) | [IVF::AttachReasoningReport · L799](ivf_search.md#L799) |

| L743 | reasoning_ctx.get | if_statement@725 (is_range) → if_statement@737 (use_reorder_ and param.enable_reorder) | 当前参考未静态绑定；见下方边界说明 |

| L746 | this-&gt;pack_knn_result | if_statement@725 (is_range) | [InnerIndexInterface::pack_knn_result · L1140](inner_index_interface.md#L1140) |

| L747 | dataset_results-&gt;Statistics | if_statement@725 (is_range) | 当前参考未静态绑定；见下方边界说明 |

| L747 | stats.Dump | if_statement@725 (is_range) | 当前参考未静态绑定；见下方边界说明 |

| L748 | this-&gt;AttachReasoningReport | if_statement@725 (is_range) | [IVF::AttachReasoningReport · L799](ivf_search.md#L799) |

| L748 | reasoning_ctx.get | if_statement@725 (is_range) | 当前参考未静态绑定；见下方边界说明 |

| L756 | CHECK_ARGUMENT | if_statement@755 (use_reorder_ and param.enable_reorder) | 当前参考未静态绑定；见下方边界说明 |

| L758 | fmt::format | if_statement@755 (use_reorder_ and param.enable_reorder) | 当前参考未静态绑定；见下方边界说明 |

| L760 | request.threshold_.has_value | if_statement@755 (use_reorder_ and param.enable_reorder) → if_statement@760 (request.threshold_.has_value()) | 当前参考未静态绑定；见下方边界说明 |

| L761 | std::max | if_statement@755 (use_reorder_ and param.enable_reorder) → if_statement@760 (request.threshold_.has_value()) | 当前参考未静态绑定；见下方边界说明 |

| L768 | this-&gt;search&lt;KNN_SEARCH&gt; | 函数本体；短路求值/提前返回见源码 | [IVF::search · L199](ivf_search.md#L199) |

| L768 | reasoning_ctx.get | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L770 | reorder | if_statement@769 (reorder_enabled) | [IVF::reorder · L183](ivf_search.md#L183) |

| L770 | request.threshold_.has_value | if_statement@769 (reorder_enabled) → conditional_expression@770 request.threshold_.has_value() | 当前参考未静态绑定；见下方边界说明 |

| L772 | query-&gt;GetFloat32Vectors | if_statement@769 (reorder_enabled) | 当前参考未静态绑定；见下方边界说明 |

| L775 | reasoning_ctx.get | if_statement@769 (reorder_enabled) | 当前参考未静态绑定；见下方边界说明 |

| L777 | FilterDatasetByThreshold | if_statement@769 (reorder_enabled) | 当前参考未静态绑定；见下方边界说明 |

| L778 | AttachReasoningReport | if_statement@769 (reorder_enabled) | [IVF::AttachReasoningReport · L799](ivf_search.md#L799) |

| L778 | reasoning_ctx.get | if_statement@769 (reorder_enabled) | 当前参考未静态绑定；见下方边界说明 |

| L779 | result-&gt;Statistics | if_statement@769 (reorder_enabled) | 当前参考未静态绑定；见下方边界说明 |

| L779 | stats.Dump | if_statement@769 (reorder_enabled) | 当前参考未静态绑定；见下方边界说明 |

| L782 | filter_search_result_by_threshold | 函数本体；短路求值/提前返回见源码 | [InnerIndexInterface::filter_search_result_by_threshold · L1156](inner_index_interface.md#L1156) |

| L783 | select_query_allocator | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L784 | search_result-&gt;Empty | if_statement@784 (search_result == nullptr &#124;&#124; search_result-&gt;Empty()) | 当前参考未静态绑定；见下方边界说明 |

| L785 | DatasetImpl::MakeEmptyDataset | if_statement@784 (search_result == nullptr &#124;&#124; search_result-&gt;Empty()) | 当前参考未静态绑定；见下方边界说明 |

| L786 | this-&gt;AttachReasoningReport | if_statement@784 (search_result == nullptr &#124;&#124; search_result-&gt;Empty()) | [IVF::AttachReasoningReport · L799](ivf_search.md#L799) |

| L786 | reasoning_ctx.get | if_statement@784 (search_result == nullptr &#124;&#124; search_result-&gt;Empty()) | 当前参考未静态绑定；见下方边界说明 |

| L787 | dataset_results-&gt;Statistics | if_statement@784 (search_result == nullptr &#124;&#124; search_result-&gt;Empty()) | 当前参考未静态绑定；见下方边界说明 |

| L787 | stats.Dump | if_statement@784 (search_result == nullptr &#124;&#124; search_result-&gt;Empty()) | 当前参考未静态绑定；见下方边界说明 |

| L791 | this-&gt;pack_knn_result | 函数本体；短路求值/提前返回见源码 | [InnerIndexInterface::pack_knn_result · L1140](inner_index_interface.md#L1140) |

| L792 | dataset_results-&gt;Statistics | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L792 | stats.Dump | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L794 | this-&gt;AttachReasoningReport | 函数本体；短路求值/提前返回见源码 | [IVF::AttachReasoningReport · L799](ivf_search.md#L799) |

| L794 | reasoning_ctx.get | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L799"></a>

## `IVF::AttachReasoningReport`

源码位置：`src/algorithm/ivf/ivf_search.cpp:799–819`。

输出标签先恢复成内部编号以标记命中，然后诊断 expected targets 并生成报告。诊断是检索后的解释步骤，不会重新补入漏掉的候选。

### 完整函数

```cpp
void
IVF::AttachReasoningReport(const DatasetPtr& dataset_results,
                           ReasoningContext* reasoning_ctx) const {
    if (reasoning_ctx == nullptr) {
        return;
    }
    auto count = dataset_results->GetDim();
    if (count > 0 and dataset_results->GetIds() != nullptr) {
        Vector<InnerIdType> result_inner_ids(static_cast<uint64_t>(count), this->allocator_);
        {
            std::shared_lock<std::shared_mutex> lock(this->label_lookup_mutex_);
            for (int64_t i = 0; i < count; ++i) {
                result_inner_ids[i] =
                    this->label_table_->GetIdByLabel(dataset_results->GetIds()[i]);
            }
        }
        reasoning_ctx->MarkResult(result_inner_ids);
    }
    reasoning_ctx->DiagnoseExpectedTargets();
    dataset_results->Reasoning(reasoning_ctx->GenerateReport());
}
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L805 | dataset_results-&gt;GetDim | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L806 | dataset_results-&gt;GetIds | if_statement@806 (count &gt; 0 and dataset_results-&gt;GetIds() != nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L812 | this-&gt;label_table_-&gt;GetIdByLabel | if_statement@806 (count &gt; 0 and dataset_results-&gt;GetIds() != nullptr) → for_statement@810 i &lt; count | [LabelTable::GetIdByLabel · L116](label_table.md#L116) |

| L812 | dataset_results-&gt;GetIds | if_statement@806 (count &gt; 0 and dataset_results-&gt;GetIds() != nullptr) → for_statement@810 i &lt; count | 当前参考未静态绑定；见下方边界说明 |

| L815 | reasoning_ctx-&gt;MarkResult | if_statement@806 (count &gt; 0 and dataset_results-&gt;GetIds() != nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L817 | reasoning_ctx-&gt;DiagnoseExpectedTargets | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L818 | dataset_results-&gt;Reasoning | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L818 | reasoning_ctx-&gt;GenerateReport | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。
