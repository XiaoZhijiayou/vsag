# graph_bucket_searcher.cpp：逐函数完整源码与调用点

[主讲解](../code_walkthrough.md) · [函数总目录](README.md)

源码：[ src/algorithm/ivf/graph_bucket_searcher.cpp ](../../../../src/algorithm/ivf/graph_bucket_searcher.cpp)。基线 `fd363937`。以下源码函数体完整保留；调用点表是语法树中的显式调用表达式，按源码位置排列，不代表 C++ 参数求值顺序。表中“候选实现”需结合类型和参数选分支，不能将同名函数全部视为必经路径。

- [GraphBucketSearcher::GraphBucketSearcher · L27](graph_bucket_searcher.md#L27)

- [GraphBucketSearcher::Search · L36](graph_bucket_searcher.md#L36)

- [GraphBucketSearcher::search_graph · L77](graph_bucket_searcher.md#L77)


<a id="L27"></a>

## `GraphBucketSearcher::GraphBucketSearcher`

源码位置：`src/algorithm/ivf/graph_bucket_searcher.cpp:27–34`。

先从签名确认输入、返回值和 const/override，再按完整函数体的条件阅读调用点。下表保留了本函数的显式调用以及 lambda 中的调用；进入下层时用“候选实现”定位，未解析的对象由源码静态类型/运行时类型确认。

### 完整函数

```cpp
GraphBucketSearcher::GraphBucketSearcher(int64_t graph_build_threshold,
                                         const Vector<GraphInterfacePtr>& bucket_graphs,
                                         Allocator* allocator)
    : graph_build_threshold_(graph_build_threshold),
      bucket_graphs_(bucket_graphs),
      allocator_(allocator),
      flat_searcher_(std::make_shared<FlatBucketSearcher>()) {
}
```

### 函数内部调用点：不省略标准库和辅助调用

此函数体没有显式函数调用表达式。赋值、成员初始化和隐式操作请看上面的完整源码。


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L36"></a>

## `GraphBucketSearcher::Search`

源码位置：`src/algorithm/ivf/graph_bucket_searcher.cpp:36–75`。

先辨认类名：FlatBucketSearcher 整桶算分后过滤；GraphBucketSearcher 先判断图新鲜度；BasicSearcher 负责图遍历。它们同名但输入编号和算法层次不同。

### 完整函数

```cpp
void
GraphBucketSearcher::Search(BucketIdType bucket_id,
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
    bool has_graph = (bucket_id < static_cast<BucketIdType>(bucket_graphs_.size()) &&
                      bucket_graphs_[bucket_id] != nullptr);

    bool graph_fresh = has_graph && bucket_graphs_[bucket_id]->TotalCount() ==
                                        static_cast<InnerIdType>(bucket_size);
    if (graph_fresh && bucket_size >= graph_build_threshold_) {
        search_graph(bucket_id,
                     bucket,
                     computer,
                     param,
                     thread_id,
                     topk,
                     buckets_per_data,
                     heap,
                     reasoning_ctx);
    } else {
        flat_searcher_->Search(bucket_id,
                               bucket,
                               computer,
                               param,
                               thread_id,
                               topk,
                               buckets_per_data,
                               heap,
                               dist,
                               reasoning_ctx);
    }
}
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L47 | bucket-&gt;GetBucketSize | 函数本体；短路求值/提前返回见源码 | [BucketDataCell::GetBucketSize · L180](bucket_datacell_h.md#L180) |

| L48 | bucket_graphs_.size | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L51 | bucket_graphs_[bucket_id]-&gt;TotalCount | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L54 | search_graph | if_statement@53 (graph_fresh && bucket_size &gt;= graph_build_threshold_) | [GraphBucketSearcher::search_graph · L77](graph_bucket_searcher.md#L77) |

| L64 | flat_searcher_-&gt;Search | if_statement@53 (graph_fresh && bucket_size &gt;= graph_build_threshold_) [else 分支] | [FlatBucketSearcher::Search · L26](flat_bucket_searcher.md#L26) |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L77"></a>

## `GraphBucketSearcher::search_graph`

源码位置：`src/algorithm/ivf/graph_bucket_searcher.cpp:77–145`。

入口是首个有效桶内 offset，ef 根据 topk 和桶大小调整。BasicSearcher 返回 local ID，必须通过 ids[local_id] 转成 posting ID 后加入上层堆。

### 完整函数

```cpp
void
GraphBucketSearcher::search_graph(BucketIdType bucket_id,
                                  const BucketInterfacePtr& bucket,
                                  const ComputerInterfacePtr& computer,
                                  const InnerSearchParam& param,
                                  int64_t thread_id,
                                  int64_t topk,
                                  BucketIdType buckets_per_data,
                                  DistHeapPtr& heap,
                                  ReasoningContext* reasoning_ctx) const {
    const auto bucket_size = bucket->GetBucketSize(bucket_id);
    if (bucket_size == 0) {
        return;
    }
    const auto& graph = bucket_graphs_[bucket_id];
    const auto* ids = bucket->GetInnerIds(bucket_id);
    InnerIdType entry = 0;
    while (entry < bucket_size && ids[entry] == std::numeric_limits<InnerIdType>::max()) {
        ++entry;
    }
    if (entry == bucket_size) {
        return;
    }

    Filter* attr_filter = nullptr;
    if (not param.executors.empty() && static_cast<uint64_t>(thread_id) < param.executors.size() &&
        param.executors[thread_id] != nullptr) {
        param.executors[thread_id]->Clear();
        attr_filter = param.executors[thread_id]->Run(bucket_id);
    }
    InnerSearchParam search_param = param;
    search_param.ep = entry;
    uint64_t result_limit = std::numeric_limits<uint64_t>::max();
    if (search_param.search_mode == KNN_SEARCH) {
        CHECK_ARGUMENT(topk > 0, "topk must be greater than 0");
        result_limit = static_cast<uint64_t>(topk);
        search_param.ef = std::max(search_param.ef, result_limit);
    } else if (topk > 0) {
        result_limit = static_cast<uint64_t>(topk);
    }
    search_param.ef = std::min<uint64_t>(search_param.ef, bucket_size);
    search_param.topk = topk;
    if (search_param.search_mode == RANGE_SEARCH) {
        // BasicSearcher uses a non-positive range limit to mean unlimited; clamp only positive
        // limits because InnerSearchParam stores this field as int.
        search_param.range_search_limit_size =
            topk > 0 ? static_cast<int>(std::min<int64_t>(topk, std::numeric_limits<int>::max()))
                     : 0;
    }

    // BucketInterface can create computers only from raw queries, not local IDs. Search only
    // needs query distances, so use the no-factory provider and make pairwise misuse explicit.
    BucketDistanceProvider distance_provider(bucket, bucket_id, computer, ids, buckets_per_data);
    auto visited = std::make_shared<VisitedList>(bucket_size, allocator_);
    QueryContext query_context =
        param.query_context == nullptr ? QueryContext{} : *param.query_context;
    query_context.reasoning_ctx = reasoning_ctx;
    BasicSearcher searcher(allocator_);
    auto top_candidates = searcher.Search(
        graph, distance_provider, visited, search_param, attr_filter, &query_context);
    while (not top_candidates->Empty()) {
        const auto [distance, local_id] = top_candidates->Top();
        heap->Push(distance, ids[local_id]);
        top_candidates->Pop();
    }
    while (heap->Size() > result_limit) {
        heap->Pop();
    }
}
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L87 | bucket-&gt;GetBucketSize | 函数本体；短路求值/提前返回见源码 | [BucketDataCell::GetBucketSize · L180](bucket_datacell_h.md#L180) |

| L92 | bucket-&gt;GetInnerIds | 函数本体；短路求值/提前返回见源码 | [BucketDataCell::GetInnerIds · L120](bucket_datacell_h.md#L120) |

| L94 | std::numeric_limits&lt;InnerIdType&gt;::max | while_statement@94 (entry &lt; bucket_size && ids[entry] == std::numeric_limits&lt;InnerIdType&gt;::max()) | 当前参考未静态绑定；见下方边界说明 |

| L102 | param.executors.empty | if_statement@102 (not param.executors.empty() && static_cast&lt;uint64_t&gt;(thread_id) &lt; param.executors.size() && param.executors[thread_id] != nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L102 | param.executors.size | if_statement@102 (not param.executors.empty() && static_cast&lt;uint64_t&gt;(thread_id) &lt; param.executors.size() && param.executors[thread_id] != nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L104 | param.executors[thread_id]-&gt;Clear | if_statement@102 (not param.executors.empty() && static_cast&lt;uint64_t&gt;(thread_id) &lt; param.executors.size() && param.executors[thread_id] != nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L105 | param.executors[thread_id]-&gt;Run | if_statement@102 (not param.executors.empty() && static_cast&lt;uint64_t&gt;(thread_id) &lt; param.executors.size() && param.executors[thread_id] != nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L109 | std::numeric_limits&lt;uint64_t&gt;::max | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L111 | CHECK_ARGUMENT | if_statement@110 (search_param.search_mode == KNN_SEARCH) | 当前参考未静态绑定；见下方边界说明 |

| L113 | std::max | if_statement@110 (search_param.search_mode == KNN_SEARCH) | 当前参考未静态绑定；见下方边界说明 |

| L117 | std::min&lt;uint64_t&gt; | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L123 | std::min&lt;int64_t&gt; | if_statement@119 (search_param.search_mode == RANGE_SEARCH) → conditional_expression@123 topk &gt; 0 | 当前参考未静态绑定；见下方边界说明 |

| L123 | std::numeric_limits&lt;int&gt;::max | if_statement@119 (search_param.search_mode == RANGE_SEARCH) → conditional_expression@123 topk &gt; 0 | 当前参考未静态绑定；见下方边界说明 |

| L130 | std::make_shared&lt;VisitedList&gt; | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L135 | searcher.Search | 函数本体；短路求值/提前返回见源码 | [BasicSearcher::Search · L76](basic_searcher.md#L76)；[BasicSearcher::Search · L139](basic_searcher.md#L139)；[BasicSearcher::Search · L158](basic_searcher.md#L158) |

| L137 | top_candidates-&gt;Empty | while_statement@137 (not top_candidates-&gt;Empty()) | 当前参考未静态绑定；见下方边界说明 |

| L138 | top_candidates-&gt;Top | while_statement@137 (not top_candidates-&gt;Empty()) | 当前参考未静态绑定；见下方边界说明 |

| L139 | heap-&gt;Push | while_statement@137 (not top_candidates-&gt;Empty()) | 当前参考未静态绑定；见下方边界说明 |

| L140 | top_candidates-&gt;Pop | while_statement@137 (not top_candidates-&gt;Empty()) | 当前参考未静态绑定；见下方边界说明 |

| L142 | heap-&gt;Size | while_statement@142 (heap-&gt;Size() &gt; result_limit) | 当前参考未静态绑定；见下方边界说明 |

| L143 | heap-&gt;Pop | while_statement@142 (heap-&gt;Size() &gt; result_limit) | 当前参考未静态绑定；见下方边界说明 |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。
