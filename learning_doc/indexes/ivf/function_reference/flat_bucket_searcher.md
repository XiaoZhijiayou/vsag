# flat_bucket_searcher.cpp：逐函数完整源码与调用点

[主讲解](../code_walkthrough.md) · [函数总目录](README.md)

源码：[ src/algorithm/ivf/flat_bucket_searcher.cpp ](../../../../src/algorithm/ivf/flat_bucket_searcher.cpp)。基线 `fd363937`。以下源码函数体完整保留；调用点表是语法树中的显式调用表达式，按源码位置排列，不代表 C++ 参数求值顺序。表中“候选实现”需结合类型和参数选分支，不能将同名函数全部视为必经路径。

- [FlatBucketSearcher::Search · L26](flat_bucket_searcher.md#L26)


<a id="L26"></a>

## `FlatBucketSearcher::Search`

源码位置：`src/algorithm/ivf/flat_bucket_searcher.cpp:26–138`。

先辨认类名：FlatBucketSearcher 整桶算分后过滤；GraphBucketSearcher 先判断图新鲜度；BasicSearcher 负责图遍历。它们同名但输入编号和算法层次不同。

### 完整函数

```cpp
void
FlatBucketSearcher::Search(BucketIdType bucket_id,
                           const BucketInterfacePtr& bucket,
                           const ComputerInterfacePtr& computer,
                           const InnerSearchParam& param,
                           int64_t thread_id,
                           int64_t topk,
                           BucketIdType buckets_per_data,
                           DistHeapPtr& heap,
                           Vector<float>& dist,
                           ReasoningContext* reasoning_ctx) const {
    auto bucket_size = bucket->GetBucketSize(bucket_id);
    const auto* ids = bucket->GetInnerIds(bucket_id);
    if (bucket_size > static_cast<int64_t>(dist.size())) {
        dist.resize(bucket_size);
    }

    bucket->ScanBucketById(dist.data(), computer, bucket_id);
    if (param.query_context != nullptr and param.query_context->stats != nullptr and
        bucket_size > 0) {
        param.query_context->stats->AddDistance(SearchStatistics::DistancePhase::APPROXIMATE,
                                                bucket->backend_,
                                                static_cast<uint64_t>(bucket_size));
    }

    Filter* attr_ft = nullptr;
    size_t tid = 0;
    if (thread_id >= 0 and param.executors.size() > static_cast<uint64_t>(thread_id)) {
        tid = static_cast<size_t>(thread_id);
        if (param.executors[tid] != nullptr) {
            param.executors[tid]->Clear();
            attr_ft = param.executors[tid]->Run(bucket_id);
        }
    }

    const auto& ft = param.is_inner_id_allowed;
    const auto topk_u = static_cast<uint64_t>(topk);
    auto cur_heap_top = std::numeric_limits<float>::max();
    if (not heap->Empty() and heap->Size() == topk_u) {
        cur_heap_top = heap->Top().first;
    }

    if (param.search_mode == KNN_SEARCH) {
        for (int64_t j = 0; j < bucket_size; ++j) {
            if (ids[j] == std::numeric_limits<InnerIdType>::max()) {
                continue;
            }
            auto origin_id = ids[j] / buckets_per_data;
            if (reasoning_ctx != nullptr) {
                reasoning_ctx->RecordVisit(origin_id, dist[j], 0);
            }
            if (param.distance_threshold.has_value() and
                (not std::isfinite(dist[j]) or
                 (not param.enable_reorder and dist[j] > param.distance_threshold.value()))) {
                continue;
            }
            if (attr_ft != nullptr and not attr_ft->CheckValid(j)) {
                if (reasoning_ctx != nullptr) {
                    reasoning_ctx->RecordFilterReject(origin_id);
                }
                continue;
            }
            if (ft == nullptr or ft->CheckValid(origin_id)) {
                if (heap->Size() < topk_u or dist[j] < cur_heap_top) {
                    heap->Push(dist[j], ids[j]);
                }
                while (heap->Size() > topk_u) {
                    if (reasoning_ctx != nullptr) {
                        reasoning_ctx->RecordEviction(heap->Top().second / buckets_per_data, 0);
                    }
                    heap->Pop();
                }
                if (not heap->Empty() and heap->Size() == topk_u) {
                    cur_heap_top = heap->Top().first;
                }
            } else if (reasoning_ctx != nullptr) {
                reasoning_ctx->RecordFilterReject(origin_id);
            }
        }
    } else {  // RANGE_SEARCH
        for (int64_t j = 0; j < bucket_size; ++j) {
            if (ids[j] == std::numeric_limits<InnerIdType>::max()) {
                continue;
            }
            auto origin_id = ids[j] / buckets_per_data;
            if (reasoning_ctx != nullptr) {
                reasoning_ctx->RecordVisit(origin_id, dist[j], 0);
            }
            if (attr_ft != nullptr and not attr_ft->CheckValid(j)) {
                if (reasoning_ctx != nullptr) {
                    reasoning_ctx->RecordFilterReject(origin_id);
                }
                continue;
            }
            if (ft == nullptr or ft->CheckValid(origin_id)) {
                if (dist[j] <= param.radius + THRESHOLD_ERROR and dist[j] < cur_heap_top) {
                    heap->Push(dist[j], ids[j]);
                }
                while (heap->Size() > topk_u) {
                    if (reasoning_ctx != nullptr) {
                        reasoning_ctx->RecordEviction(heap->Top().second / buckets_per_data, 0);
                    }
                    heap->Pop();
                }
                if (not heap->Empty() and heap->Size() == topk_u) {
                    cur_heap_top = heap->Top().first;
                }
            } else if (reasoning_ctx != nullptr) {
                reasoning_ctx->RecordFilterReject(origin_id);
            }
        }
    }
}
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L37 | bucket-&gt;GetBucketSize | 函数本体；短路求值/提前返回见源码 | [BucketDataCell::GetBucketSize · L180](bucket_datacell_h.md#L180) |

| L38 | bucket-&gt;GetInnerIds | 函数本体；短路求值/提前返回见源码 | [BucketDataCell::GetInnerIds · L120](bucket_datacell_h.md#L120) |

| L39 | dist.size | if_statement@39 (bucket_size &gt; static_cast&lt;int64_t&gt;(dist.size())) | 当前参考未静态绑定；见下方边界说明 |

| L40 | dist.resize | if_statement@39 (bucket_size &gt; static_cast&lt;int64_t&gt;(dist.size())) | 当前参考未静态绑定；见下方边界说明 |

| L43 | bucket-&gt;ScanBucketById | 函数本体；短路求值/提前返回见源码 | [BucketDataCell::ScanBucketById · L63](bucket_datacell_h.md#L63) |

| L43 | dist.data | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L46 | param.query_context-&gt;stats-&gt;AddDistance | if_statement@44 (param.query_context != nullptr and param.query_context-&gt;stats != nullptr and bucket_size &gt; 0) | 当前参考未静态绑定；见下方边界说明 |

| L53 | param.executors.size | if_statement@53 (thread_id &gt;= 0 and param.executors.size() &gt; static_cast&lt;uint64_t&gt;(thread_id)) | 当前参考未静态绑定；见下方边界说明 |

| L56 | param.executors[tid]-&gt;Clear | if_statement@53 (thread_id &gt;= 0 and param.executors.size() &gt; static_cast&lt;uint64_t&gt;(thread_id)) → if_statement@55 (param.executors[tid] != nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L57 | param.executors[tid]-&gt;Run | if_statement@53 (thread_id &gt;= 0 and param.executors.size() &gt; static_cast&lt;uint64_t&gt;(thread_id)) → if_statement@55 (param.executors[tid] != nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L63 | std::numeric_limits&lt;float&gt;::max | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L64 | heap-&gt;Empty | if_statement@64 (not heap-&gt;Empty() and heap-&gt;Size() == topk_u) | 当前参考未静态绑定；见下方边界说明 |

| L64 | heap-&gt;Size | if_statement@64 (not heap-&gt;Empty() and heap-&gt;Size() == topk_u) | 当前参考未静态绑定；见下方边界说明 |

| L65 | heap-&gt;Top | if_statement@64 (not heap-&gt;Empty() and heap-&gt;Size() == topk_u) | 当前参考未静态绑定；见下方边界说明 |

| L70 | std::numeric_limits&lt;InnerIdType&gt;::max | if_statement@68 (param.search_mode == KNN_SEARCH) → for_statement@69 j &lt; bucket_size → if_statement@70 (ids[j] == std::numeric_limits&lt;InnerIdType&gt;::max()) | 当前参考未静态绑定；见下方边界说明 |

| L75 | reasoning_ctx-&gt;RecordVisit | if_statement@68 (param.search_mode == KNN_SEARCH) → for_statement@69 j &lt; bucket_size → if_statement@74 (reasoning_ctx != nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L77 | param.distance_threshold.has_value | if_statement@68 (param.search_mode == KNN_SEARCH) → for_statement@69 j &lt; bucket_size → if_statement@77 (param.distance_threshold.has_value() and (not std::isfinite(dist[j]) or (not param.enable_reorder and dist[j] &gt; param.distance_threshold.value()))) | 当前参考未静态绑定；见下方边界说明 |

| L78 | std::isfinite | if_statement@68 (param.search_mode == KNN_SEARCH) → for_statement@69 j &lt; bucket_size → if_statement@77 (param.distance_threshold.has_value() and (not std::isfinite(dist[j]) or (not param.enable_reorder and dist[j] &gt; param.distance_threshold.value()))) | 当前参考未静态绑定；见下方边界说明 |

| L79 | param.distance_threshold.value | if_statement@68 (param.search_mode == KNN_SEARCH) → for_statement@69 j &lt; bucket_size → if_statement@77 (param.distance_threshold.has_value() and (not std::isfinite(dist[j]) or (not param.enable_reorder and dist[j] &gt; param.distance_threshold.value()))) | 当前参考未静态绑定；见下方边界说明 |

| L82 | attr_ft-&gt;CheckValid | if_statement@68 (param.search_mode == KNN_SEARCH) → for_statement@69 j &lt; bucket_size → if_statement@82 (attr_ft != nullptr and not attr_ft-&gt;CheckValid(j)) | 当前参考未静态绑定；见下方边界说明 |

| L84 | reasoning_ctx-&gt;RecordFilterReject | if_statement@68 (param.search_mode == KNN_SEARCH) → for_statement@69 j &lt; bucket_size → if_statement@82 (attr_ft != nullptr and not attr_ft-&gt;CheckValid(j)) → if_statement@83 (reasoning_ctx != nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L88 | ft-&gt;CheckValid | if_statement@68 (param.search_mode == KNN_SEARCH) → for_statement@69 j &lt; bucket_size → if_statement@88 (ft == nullptr or ft-&gt;CheckValid(origin_id)) | 当前参考未静态绑定；见下方边界说明 |

| L89 | heap-&gt;Size | if_statement@68 (param.search_mode == KNN_SEARCH) → for_statement@69 j &lt; bucket_size → if_statement@88 (ft == nullptr or ft-&gt;CheckValid(origin_id)) → if_statement@89 (heap-&gt;Size() &lt; topk_u or dist[j] &lt; cur_heap_top) | 当前参考未静态绑定；见下方边界说明 |

| L90 | heap-&gt;Push | if_statement@68 (param.search_mode == KNN_SEARCH) → for_statement@69 j &lt; bucket_size → if_statement@88 (ft == nullptr or ft-&gt;CheckValid(origin_id)) → if_statement@89 (heap-&gt;Size() &lt; topk_u or dist[j] &lt; cur_heap_top) | 当前参考未静态绑定；见下方边界说明 |

| L92 | heap-&gt;Size | if_statement@68 (param.search_mode == KNN_SEARCH) → for_statement@69 j &lt; bucket_size → if_statement@88 (ft == nullptr or ft-&gt;CheckValid(origin_id)) → while_statement@92 (heap-&gt;Size() &gt; topk_u) | 当前参考未静态绑定；见下方边界说明 |

| L94 | reasoning_ctx-&gt;RecordEviction | if_statement@68 (param.search_mode == KNN_SEARCH) → for_statement@69 j &lt; bucket_size → if_statement@88 (ft == nullptr or ft-&gt;CheckValid(origin_id)) → while_statement@92 (heap-&gt;Size() &gt; topk_u) → if_statement@93 (reasoning_ctx != nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L94 | heap-&gt;Top | if_statement@68 (param.search_mode == KNN_SEARCH) → for_statement@69 j &lt; bucket_size → if_statement@88 (ft == nullptr or ft-&gt;CheckValid(origin_id)) → while_statement@92 (heap-&gt;Size() &gt; topk_u) → if_statement@93 (reasoning_ctx != nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L96 | heap-&gt;Pop | if_statement@68 (param.search_mode == KNN_SEARCH) → for_statement@69 j &lt; bucket_size → if_statement@88 (ft == nullptr or ft-&gt;CheckValid(origin_id)) → while_statement@92 (heap-&gt;Size() &gt; topk_u) | 当前参考未静态绑定；见下方边界说明 |

| L98 | heap-&gt;Empty | if_statement@68 (param.search_mode == KNN_SEARCH) → for_statement@69 j &lt; bucket_size → if_statement@88 (ft == nullptr or ft-&gt;CheckValid(origin_id)) → if_statement@98 (not heap-&gt;Empty() and heap-&gt;Size() == topk_u) | 当前参考未静态绑定；见下方边界说明 |

| L98 | heap-&gt;Size | if_statement@68 (param.search_mode == KNN_SEARCH) → for_statement@69 j &lt; bucket_size → if_statement@88 (ft == nullptr or ft-&gt;CheckValid(origin_id)) → if_statement@98 (not heap-&gt;Empty() and heap-&gt;Size() == topk_u) | 当前参考未静态绑定；见下方边界说明 |

| L99 | heap-&gt;Top | if_statement@68 (param.search_mode == KNN_SEARCH) → for_statement@69 j &lt; bucket_size → if_statement@88 (ft == nullptr or ft-&gt;CheckValid(origin_id)) → if_statement@98 (not heap-&gt;Empty() and heap-&gt;Size() == topk_u) | 当前参考未静态绑定；见下方边界说明 |

| L102 | reasoning_ctx-&gt;RecordFilterReject | if_statement@68 (param.search_mode == KNN_SEARCH) → for_statement@69 j &lt; bucket_size → if_statement@88 (ft == nullptr or ft-&gt;CheckValid(origin_id)) [else 分支] → if_statement@101 (reasoning_ctx != nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L107 | std::numeric_limits&lt;InnerIdType&gt;::max | if_statement@68 (param.search_mode == KNN_SEARCH) [else 分支] → for_statement@106 j &lt; bucket_size → if_statement@107 (ids[j] == std::numeric_limits&lt;InnerIdType&gt;::max()) | 当前参考未静态绑定；见下方边界说明 |

| L112 | reasoning_ctx-&gt;RecordVisit | if_statement@68 (param.search_mode == KNN_SEARCH) [else 分支] → for_statement@106 j &lt; bucket_size → if_statement@111 (reasoning_ctx != nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L114 | attr_ft-&gt;CheckValid | if_statement@68 (param.search_mode == KNN_SEARCH) [else 分支] → for_statement@106 j &lt; bucket_size → if_statement@114 (attr_ft != nullptr and not attr_ft-&gt;CheckValid(j)) | 当前参考未静态绑定；见下方边界说明 |

| L116 | reasoning_ctx-&gt;RecordFilterReject | if_statement@68 (param.search_mode == KNN_SEARCH) [else 分支] → for_statement@106 j &lt; bucket_size → if_statement@114 (attr_ft != nullptr and not attr_ft-&gt;CheckValid(j)) → if_statement@115 (reasoning_ctx != nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L120 | ft-&gt;CheckValid | if_statement@68 (param.search_mode == KNN_SEARCH) [else 分支] → for_statement@106 j &lt; bucket_size → if_statement@120 (ft == nullptr or ft-&gt;CheckValid(origin_id)) | 当前参考未静态绑定；见下方边界说明 |

| L122 | heap-&gt;Push | if_statement@68 (param.search_mode == KNN_SEARCH) [else 分支] → for_statement@106 j &lt; bucket_size → if_statement@120 (ft == nullptr or ft-&gt;CheckValid(origin_id)) → if_statement@121 (dist[j] &lt;= param.radius + THRESHOLD_ERROR and dist[j] &lt; cur_heap_top) | 当前参考未静态绑定；见下方边界说明 |

| L124 | heap-&gt;Size | if_statement@68 (param.search_mode == KNN_SEARCH) [else 分支] → for_statement@106 j &lt; bucket_size → if_statement@120 (ft == nullptr or ft-&gt;CheckValid(origin_id)) → while_statement@124 (heap-&gt;Size() &gt; topk_u) | 当前参考未静态绑定；见下方边界说明 |

| L126 | reasoning_ctx-&gt;RecordEviction | if_statement@68 (param.search_mode == KNN_SEARCH) [else 分支] → for_statement@106 j &lt; bucket_size → if_statement@120 (ft == nullptr or ft-&gt;CheckValid(origin_id)) → while_statement@124 (heap-&gt;Size() &gt; topk_u) → if_statement@125 (reasoning_ctx != nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L126 | heap-&gt;Top | if_statement@68 (param.search_mode == KNN_SEARCH) [else 分支] → for_statement@106 j &lt; bucket_size → if_statement@120 (ft == nullptr or ft-&gt;CheckValid(origin_id)) → while_statement@124 (heap-&gt;Size() &gt; topk_u) → if_statement@125 (reasoning_ctx != nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L128 | heap-&gt;Pop | if_statement@68 (param.search_mode == KNN_SEARCH) [else 分支] → for_statement@106 j &lt; bucket_size → if_statement@120 (ft == nullptr or ft-&gt;CheckValid(origin_id)) → while_statement@124 (heap-&gt;Size() &gt; topk_u) | 当前参考未静态绑定；见下方边界说明 |

| L130 | heap-&gt;Empty | if_statement@68 (param.search_mode == KNN_SEARCH) [else 分支] → for_statement@106 j &lt; bucket_size → if_statement@120 (ft == nullptr or ft-&gt;CheckValid(origin_id)) → if_statement@130 (not heap-&gt;Empty() and heap-&gt;Size() == topk_u) | 当前参考未静态绑定；见下方边界说明 |

| L130 | heap-&gt;Size | if_statement@68 (param.search_mode == KNN_SEARCH) [else 分支] → for_statement@106 j &lt; bucket_size → if_statement@120 (ft == nullptr or ft-&gt;CheckValid(origin_id)) → if_statement@130 (not heap-&gt;Empty() and heap-&gt;Size() == topk_u) | 当前参考未静态绑定；见下方边界说明 |

| L131 | heap-&gt;Top | if_statement@68 (param.search_mode == KNN_SEARCH) [else 分支] → for_statement@106 j &lt; bucket_size → if_statement@120 (ft == nullptr or ft-&gt;CheckValid(origin_id)) → if_statement@130 (not heap-&gt;Empty() and heap-&gt;Size() == topk_u) | 当前参考未静态绑定；见下方边界说明 |

| L134 | reasoning_ctx-&gt;RecordFilterReject | if_statement@68 (param.search_mode == KNN_SEARCH) [else 分支] → for_statement@106 j &lt; bucket_size → if_statement@120 (ft == nullptr or ft-&gt;CheckValid(origin_id)) [else 分支] → if_statement@133 (reasoning_ctx != nullptr) | 当前参考未静态绑定；见下方边界说明 |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。
