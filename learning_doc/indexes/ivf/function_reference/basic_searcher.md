# basic_searcher.cpp：逐函数完整源码与调用点

[主讲解](../code_walkthrough.md) · [函数总目录](README.md)

源码：[ src/impl/searcher/basic_searcher.cpp ](../../../../src/impl/searcher/basic_searcher.cpp)。基线 `fd363937`。以下源码函数体完整保留；调用点表是语法树中的显式调用表达式，按源码位置排列，不代表 C++ 参数求值顺序。表中“候选实现”需结合类型和参数选分支，不能将同名函数全部视为必经路径。

- [BasicSearcher::BasicSearcher · L35](basic_searcher.md#L35)

- [BasicSearcher::BasicSearcher · L39](basic_searcher.md#L39)

- [BasicSearcher::visit · L43](basic_searcher.md#L43)

- [BasicSearcher::Search · L76](basic_searcher.md#L76)

- [BasicSearcher::SearchWithPresetComputer · L107](basic_searcher.md#L107)

- [BasicSearcher::Search · L139](basic_searcher.md#L139)

- [BasicSearcher::Search · L158](basic_searcher.md#L158)

- [BasicSearcher::search_impl · L174](basic_searcher.md#L174)

- [BasicSearcher::search_impl · L322](basic_searcher.md#L322)

- [BasicSearcher::search_impl · L551](basic_searcher.md#L551)

- [BasicSearcher::SetRuntimeParameters · L938](basic_searcher.md#L938)

- [BasicSearcher::SetMockParameters · L951](basic_searcher.md#L951)

- [BasicSearcher::MockRun · L966](basic_searcher.md#L966)

- [BasicSearcher::SetMutexArray · L997](basic_searcher.md#L997)


<a id="L35"></a>

## `BasicSearcher::BasicSearcher`

源码位置：`src/impl/searcher/basic_searcher.cpp:35–37`。

先从签名确认输入、返回值和 const/override，再按完整函数体的条件阅读调用点。下表保留了本函数的显式调用以及 lambda 中的调用；进入下层时用“候选实现”定位，未解析的对象由源码静态类型/运行时类型确认。

### 完整函数

```cpp
BasicSearcher::BasicSearcher(const IndexCommonParam& common_param, MutexArrayPtr mutex_array)
    : allocator_(common_param.allocator_.get()), mutex_array_(std::move(mutex_array)) {
}
```

### 函数内部调用点：不省略标准库和辅助调用

此函数体没有显式函数调用表达式。赋值、成员初始化和隐式操作请看上面的完整源码。


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L39"></a>

## `BasicSearcher::BasicSearcher`

源码位置：`src/impl/searcher/basic_searcher.cpp:39–41`。

先从签名确认输入、返回值和 const/override，再按完整函数体的条件阅读调用点。下表保留了本函数的显式调用以及 lambda 中的调用；进入下层时用“候选实现”定位，未解析的对象由源码静态类型/运行时类型确认。

### 完整函数

```cpp
BasicSearcher::BasicSearcher(Allocator* allocator, MutexArrayPtr mutex_array)
    : allocator_(allocator), mutex_array_(std::move(mutex_array)) {
}
```

### 函数内部调用点：不省略标准库和辅助调用

此函数体没有显式函数调用表达式。赋值、成员初始化和隐式操作请看上面的完整源码。


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L43"></a>

## `BasicSearcher::visit`

源码位置：`src/impl/searcher/basic_searcher.cpp:43–74`。

先从签名确认输入、返回值和 const/override，再按完整函数体的条件阅读调用点。下表保留了本函数的显式调用以及 lambda 中的调用；进入下层时用“候选实现”定位，未解析的对象由源码静态类型/运行时类型确认。

### 完整函数

```cpp
uint32_t
BasicSearcher::visit(const GraphInterfacePtr& graph,
                     const VisitedListPtr& vl,
                     const std::pair<float, uint64_t>& current_node_pair,
                     const FilterPtr& filter,
                     FilterSearchSkipStrategy* skip_strategy,
                     Vector<InnerIdType>& to_be_visited_id,
                     Vector<InnerIdType>& neighbors) const {
    uint32_t count_no_visited = 0;

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
}
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L55 | graph-&gt;GetNeighbors | if_statement@53 (this-&gt;mutex_array_ != nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L57 | graph-&gt;GetNeighbors | if_statement@53 (this-&gt;mutex_array_ != nullptr) [else 分支] | 当前参考未静态绑定；见下方边界说明 |

| L60 | neighbors.size | for_statement@60 i &lt; neighbors.size() | 当前参考未静态绑定；见下方边界说明 |

| L61 | neighbors.size | for_statement@60 i &lt; neighbors.size() → if_statement@61 (i + prefetch_stride_visit_ &lt; neighbors.size()) | 当前参考未静态绑定；见下方边界说明 |

| L62 | vl-&gt;Prefetch | for_statement@60 i &lt; neighbors.size() → if_statement@61 (i + prefetch_stride_visit_ &lt; neighbors.size()) | 当前参考未静态绑定；见下方边界说明 |

| L64 | vl-&gt;Get | for_statement@60 i &lt; neighbors.size() → if_statement@64 (not vl-&gt;Get(neighbors[i])) | 当前参考未静态绑定；见下方边界说明 |

| L65 | vl-&gt;Set | for_statement@60 i &lt; neighbors.size() → if_statement@64 (not vl-&gt;Get(neighbors[i])) | 当前参考未静态绑定；见下方边界说明 |

| L67 | skip_strategy-&gt;ShouldVisit | for_statement@60 i &lt; neighbors.size() → if_statement@64 (not vl-&gt;Get(neighbors[i])) → if_statement@66 (not filter &#124;&#124; count_no_visited == 0 &#124;&#124; skip_strategy == nullptr &#124;&#124; skip_strategy-&gt;ShouldVisit() &#124;&#124; filter-&gt;CheckValid(neighbors[i])) | 当前参考未静态绑定；见下方边界说明 |

| L67 | filter-&gt;CheckValid | for_statement@60 i &lt; neighbors.size() → if_statement@64 (not vl-&gt;Get(neighbors[i])) → if_statement@66 (not filter &#124;&#124; count_no_visited == 0 &#124;&#124; skip_strategy == nullptr &#124;&#124; skip_strategy-&gt;ShouldVisit() &#124;&#124; filter-&gt;CheckValid(neighbors[i])) | 当前参考未静态绑定；见下方边界说明 |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L76"></a>

## `BasicSearcher::Search`

源码位置：`src/impl/searcher/basic_searcher.cpp:76–105`。

先辨认类名：FlatBucketSearcher 整桶算分后过滤；GraphBucketSearcher 先判断图新鲜度；BasicSearcher 负责图遍历。它们同名但输入编号和算法层次不同。

### 完整函数

```cpp
DistHeapPtr
BasicSearcher::Search(const GraphInterfacePtr& graph,
                      const FlattenInterfacePtr& flatten,
                      const VisitedListPtr& vl,
                      const void* query,
                      const InnerSearchParam& inner_search_param,
                      const LabelTablePtr& label_table,
                      QueryContext* ctx,
                      DistanceRecordVector* rabitq_lower_bound_candidates) const {
    if (inner_search_param.search_mode == KNN_SEARCH) {
        return this->search_impl<KNN_SEARCH>(graph,
                                             flatten,
                                             vl,
                                             query,
                                             inner_search_param,
                                             label_table,
                                             ctx,
                                             rabitq_lower_bound_candidates,
                                             nullptr);
    }
    return this->search_impl<RANGE_SEARCH>(graph,
                                           flatten,
                                           vl,
                                           query,
                                           inner_search_param,
                                           label_table,
                                           ctx,
                                           rabitq_lower_bound_candidates,
                                           nullptr);
}
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L86 | this-&gt;search_impl&lt;KNN_SEARCH&gt; | if_statement@85 (inner_search_param.search_mode == KNN_SEARCH) | [BasicSearcher::search_impl · L174](basic_searcher.md#L174)；[BasicSearcher::search_impl · L322](basic_searcher.md#L322)；[BasicSearcher::search_impl · L551](basic_searcher.md#L551) |

| L96 | this-&gt;search_impl&lt;RANGE_SEARCH&gt; | 函数本体；短路求值/提前返回见源码 | [BasicSearcher::search_impl · L174](basic_searcher.md#L174)；[BasicSearcher::search_impl · L322](basic_searcher.md#L322)；[BasicSearcher::search_impl · L551](basic_searcher.md#L551) |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L107"></a>

## `BasicSearcher::SearchWithPresetComputer`

源码位置：`src/impl/searcher/basic_searcher.cpp:107–137`。

先从签名确认输入、返回值和 const/override，再按完整函数体的条件阅读调用点。下表保留了本函数的显式调用以及 lambda 中的调用；进入下层时用“候选实现”定位，未解析的对象由源码静态类型/运行时类型确认。

### 完整函数

```cpp
DistHeapPtr
BasicSearcher::SearchWithPresetComputer(const GraphInterfacePtr& graph,
                                        const FlattenInterfacePtr& flatten,
                                        const VisitedListPtr& vl,
                                        const void* query,
                                        const InnerSearchParam& inner_search_param,
                                        const LabelTablePtr& label_table,
                                        QueryContext* ctx,
                                        DistanceRecordVector* rabitq_lower_bound_candidates,
                                        const ComputerInterfacePtr& preset_computer) const {
    if (inner_search_param.search_mode == KNN_SEARCH) {
        return this->search_impl<KNN_SEARCH>(graph,
                                             flatten,
                                             vl,
                                             query,
                                             inner_search_param,
                                             label_table,
                                             ctx,
                                             rabitq_lower_bound_candidates,
                                             preset_computer);
    }
    return this->search_impl<RANGE_SEARCH>(graph,
                                           flatten,
                                           vl,
                                           query,
                                           inner_search_param,
                                           label_table,
                                           ctx,
                                           rabitq_lower_bound_candidates,
                                           preset_computer);
}
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L118 | this-&gt;search_impl&lt;KNN_SEARCH&gt; | if_statement@117 (inner_search_param.search_mode == KNN_SEARCH) | [BasicSearcher::search_impl · L174](basic_searcher.md#L174)；[BasicSearcher::search_impl · L322](basic_searcher.md#L322)；[BasicSearcher::search_impl · L551](basic_searcher.md#L551) |

| L128 | this-&gt;search_impl&lt;RANGE_SEARCH&gt; | 函数本体；短路求值/提前返回见源码 | [BasicSearcher::search_impl · L174](basic_searcher.md#L174)；[BasicSearcher::search_impl · L322](basic_searcher.md#L322)；[BasicSearcher::search_impl · L551](basic_searcher.md#L551) |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L139"></a>

## `BasicSearcher::Search`

源码位置：`src/impl/searcher/basic_searcher.cpp:139–156`。

先辨认类名：FlatBucketSearcher 整桶算分后过滤；GraphBucketSearcher 先判断图新鲜度；BasicSearcher 负责图遍历。它们同名但输入编号和算法层次不同。

### 完整函数

```cpp
DistHeapPtr
BasicSearcher::Search(const GraphInterfacePtr& graph,
                      const FlattenInterfacePtr& flatten,
                      const VisitedListPtr& vl,
                      const void* query,
                      const InnerSearchParam& inner_search_param,
                      IteratorFilterContext* iter_ctx,
                      QueryContext* ctx,
                      DistanceRecordVector* rabitq_lower_bound_candidates) const {
    return this->search_impl<KNN_SEARCH>(graph,
                                         flatten,
                                         vl,
                                         query,
                                         inner_search_param,
                                         iter_ctx,
                                         ctx,
                                         rabitq_lower_bound_candidates);
}
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L148 | this-&gt;search_impl&lt;KNN_SEARCH&gt; | 函数本体；短路求值/提前返回见源码 | [BasicSearcher::search_impl · L174](basic_searcher.md#L174)；[BasicSearcher::search_impl · L322](basic_searcher.md#L322)；[BasicSearcher::search_impl · L551](basic_searcher.md#L551) |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L158"></a>

## `BasicSearcher::Search`

源码位置：`src/impl/searcher/basic_searcher.cpp:158–171`。

先辨认类名：FlatBucketSearcher 整桶算分后过滤；GraphBucketSearcher 先判断图新鲜度；BasicSearcher 负责图遍历。它们同名但输入编号和算法层次不同。

### 完整函数

```cpp
DistHeapPtr
BasicSearcher::Search(const GraphInterfacePtr& graph,
                      const DistanceProviderForGraph& distance_provider,
                      const VisitedListPtr& vl,
                      const InnerSearchParam& inner_search_param,
                      Filter* attr_filter,
                      QueryContext* ctx) const {
    if (inner_search_param.search_mode == InnerSearchMode::RANGE_SEARCH) {
        return this->search_impl<InnerSearchMode::RANGE_SEARCH>(
            graph, distance_provider, vl, inner_search_param, attr_filter, ctx);
    }
    return this->search_impl<InnerSearchMode::KNN_SEARCH>(
        graph, distance_provider, vl, inner_search_param, attr_filter, ctx);
}
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L166 | this-&gt;search_impl&lt;InnerSearchMode::RANGE_SEARCH&gt; | if_statement@165 (inner_search_param.search_mode == InnerSearchMode::RANGE_SEARCH) | [BasicSearcher::search_impl · L174](basic_searcher.md#L174)；[BasicSearcher::search_impl · L322](basic_searcher.md#L322)；[BasicSearcher::search_impl · L551](basic_searcher.md#L551) |

| L169 | this-&gt;search_impl&lt;InnerSearchMode::KNN_SEARCH&gt; | 函数本体；短路求值/提前返回见源码 | [BasicSearcher::search_impl · L174](basic_searcher.md#L174)；[BasicSearcher::search_impl · L322](basic_searcher.md#L322)；[BasicSearcher::search_impl · L551](basic_searcher.md#L551) |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L174"></a>

## `BasicSearcher::search_impl`

源码位置：`src/impl/searcher/basic_searcher.cpp:174–319`。

先从签名确认输入、返回值和 const/override，再按完整函数体的条件阅读调用点。下表保留了本函数的显式调用以及 lambda 中的调用；进入下层时用“候选实现”定位，未解析的对象由源码静态类型/运行时类型确认。

### 完整函数

```cpp
DistHeapPtr
BasicSearcher::search_impl(const GraphInterfacePtr& graph,
                           const DistanceProviderForGraph& distance_provider,
                           const VisitedListPtr& vl,
                           const InnerSearchParam& inner_search_param,
                           Filter* attr_filter,
                           QueryContext* ctx) const {
    Allocator* alloc = select_query_allocator(ctx, allocator_);
    auto top_candidates = std::make_shared<StandardHeap<true, false>>(alloc, -1);
    auto candidate_set = std::make_shared<StandardHeap<true, false>>(alloc, -1);
    if (not graph or not vl) {
        return top_candidates;
    }
    const auto check_func = [&distance_provider, &inner_search_param, attr_filter](InnerIdType id) {
        const auto original_id = distance_provider.OriginalId(id);
        return distance_provider.IsValid(id) &&
               (inner_search_param.is_inner_id_allowed == nullptr ||
                inner_search_param.is_inner_id_allowed->CheckValid(original_id)) &&
               (attr_filter == nullptr || attr_filter->CheckValid(id));
    };
    const auto ep = inner_search_param.ep;
    const auto ef = inner_search_param.ef;
    auto* reasoning = ctx == nullptr ? nullptr : ctx->reasoning_ctx;
    float dist = distance_provider.QueryDistance(ep, ctx);
    uint32_t hops = 0;
    uint32_t dist_cmp = 1;
    if (reasoning != nullptr) {
        reasoning->RecordVisit(distance_provider.OriginalId(ep), dist, 0);
    }
    if (check_func(ep)) {
        if (is_result_distance_eligible<mode>(dist, inner_search_param)) {
            top_candidates->Push(dist, ep);
        }
    } else if (reasoning != nullptr) {
        reasoning->RecordFilterReject(distance_provider.OriginalId(ep));
    }
    if constexpr (mode == InnerSearchMode::RANGE_SEARCH) {
        if (dist > inner_search_param.radius + THRESHOLD_ERROR && not top_candidates->Empty()) {
            top_candidates->Pop();
        }
    }
    candidate_set->Push(traversal_priority(dist), ep);
    vl->Set(ep);
    auto lower_bound =
        top_candidates->Empty() ? std::numeric_limits<float>::max() : top_candidates->Top().first;
    Vector<InnerIdType> to_be_visited_id(graph->MaximumDegree(), alloc);
    Vector<InnerIdType> neighbors(graph->MaximumDegree(), alloc);
    Vector<float> line_dists(graph->MaximumDegree(), alloc);
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
                continue;
            }
            if (reasoning != nullptr) {
                reasoning->RecordVisit(distance_provider.OriginalId(id), dist, hops);
            }
            if (not is_finite_distance(dist)) {
                candidate_set->Push(traversal_priority(dist), id);
                if (check_func(id) and
                    is_result_distance_eligible<mode>(dist, inner_search_param)) {
                    top_candidates->Push(dist, id);
                    if constexpr (mode == InnerSearchMode::KNN_SEARCH) {
                        if (top_candidates->Size() > ef) {
                            if (reasoning != nullptr) {
                                reasoning->RecordEviction(
                                    distance_provider.OriginalId(top_candidates->Top().second),
                                    hops);
                            }
                            top_candidates->Pop();
                        }
                    } else if (dist > inner_search_param.radius) {
                        top_candidates->Pop();
                    }
                }
                if (not top_candidates->Empty()) {
                    lower_bound = top_candidates->Top().first;
                }
                continue;
            }
            if (top_candidates->Size() < ef || lower_bound > dist ||
                (mode == InnerSearchMode::RANGE_SEARCH &&
                 dist <= inner_search_param.radius + THRESHOLD_ERROR)) {
                candidate_set->Push(-dist, id);
                distance_provider.Prefetch(candidate_set->Top().second);
                if (check_func(id)) {
                    top_candidates->Push(dist, id);
                } else if (reasoning != nullptr) {
                    reasoning->RecordFilterReject(distance_provider.OriginalId(id));
                }
                if constexpr (mode == InnerSearchMode::KNN_SEARCH) {
                    if (top_candidates->Size() > ef) {
                        if (reasoning != nullptr) {
                            reasoning->RecordEviction(
                                distance_provider.OriginalId(top_candidates->Top().second), hops);
                        }
                        top_candidates->Pop();
                    }
                }
                if (not top_candidates->Empty()) {
                    lower_bound = top_candidates->Top().first;
                }
            }
        }
    }
    if constexpr (mode == InnerSearchMode::KNN_SEARCH) {
        while (top_candidates->Size() > inner_search_param.topk) {
            top_candidates->Pop();
        }
    } else {
        if (inner_search_param.range_search_limit_size > 0) {
            while (top_candidates->Size() > inner_search_param.range_search_limit_size) {
                top_candidates->Pop();
            }
        }
        while (not top_candidates->Empty() &&
               top_candidates->Top().first > inner_search_param.radius + THRESHOLD_ERROR) {
            top_candidates->Pop();
        }
    }
    if (ctx != nullptr && ctx->stats != nullptr) {
        ctx->stats->dist_cmp.fetch_add(dist_cmp, std::memory_order_relaxed);
        ctx->stats->hops.fetch_add(hops, std::memory_order_relaxed);
    }
    return top_candidates;
}
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L181 | select_query_allocator | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L182 | std::make_shared&lt;StandardHeap&lt;true, false&gt;&gt; | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L183 | std::make_shared&lt;StandardHeap&lt;true, false&gt;&gt; | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L188 | distance_provider.OriginalId | lambda@187（定义体，执行时间取决于调用/调度） | 当前参考未静态绑定；见下方边界说明 |

| L189 | distance_provider.IsValid | lambda@187（定义体，执行时间取决于调用/调度） | 当前参考未静态绑定；见下方边界说明 |

| L191 | inner_search_param.is_inner_id_allowed-&gt;CheckValid | lambda@187（定义体，执行时间取决于调用/调度） | 当前参考未静态绑定；见下方边界说明 |

| L192 | attr_filter-&gt;CheckValid | lambda@187（定义体，执行时间取决于调用/调度） | 当前参考未静态绑定；见下方边界说明 |

| L197 | distance_provider.QueryDistance | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L201 | reasoning-&gt;RecordVisit | if_statement@200 (reasoning != nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L201 | distance_provider.OriginalId | if_statement@200 (reasoning != nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L203 | check_func | if_statement@203 (check_func(ep)) | 当前参考未静态绑定；见下方边界说明 |

| L204 | is_result_distance_eligible&lt;mode&gt; | if_statement@203 (check_func(ep)) → if_statement@204 (is_result_distance_eligible&lt;mode&gt;(dist, inner_search_param)) | 当前参考未静态绑定；见下方边界说明 |

| L205 | top_candidates-&gt;Push | if_statement@203 (check_func(ep)) → if_statement@204 (is_result_distance_eligible&lt;mode&gt;(dist, inner_search_param)) | 当前参考未静态绑定；见下方边界说明 |

| L208 | reasoning-&gt;RecordFilterReject | if_statement@203 (check_func(ep)) [else 分支] → if_statement@207 (reasoning != nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L208 | distance_provider.OriginalId | if_statement@203 (check_func(ep)) [else 分支] → if_statement@207 (reasoning != nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L211 | top_candidates-&gt;Empty | if_statement@210 (mode == InnerSearchMode::RANGE_SEARCH) → if_statement@211 (dist &gt; inner_search_param.radius + THRESHOLD_ERROR && not top_candidates-&gt;Empty()) | 当前参考未静态绑定；见下方边界说明 |

| L212 | top_candidates-&gt;Pop | if_statement@210 (mode == InnerSearchMode::RANGE_SEARCH) → if_statement@211 (dist &gt; inner_search_param.radius + THRESHOLD_ERROR && not top_candidates-&gt;Empty()) | 当前参考未静态绑定；见下方边界说明 |

| L215 | candidate_set-&gt;Push | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L215 | traversal_priority | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L216 | vl-&gt;Set | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L218 | top_candidates-&gt;Empty | conditional_expression@218 top_candidates-&gt;Empty() | 当前参考未静态绑定；见下方边界说明 |

| L218 | std::numeric_limits&lt;float&gt;::max | conditional_expression@218 top_candidates-&gt;Empty() | 当前参考未静态绑定；见下方边界说明 |

| L218 | top_candidates-&gt;Top | conditional_expression@218 top_candidates-&gt;Empty() | 当前参考未静态绑定；见下方边界说明 |

| L219 | graph-&gt;MaximumDegree | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L220 | graph-&gt;MaximumDegree | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L221 | graph-&gt;MaximumDegree | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L222 | candidate_set-&gt;Empty | while_statement@222 (not candidate_set-&gt;Empty()) | 当前参考未静态绑定；见下方边界说明 |

| L228 | candidate_set-&gt;Top | while_statement@222 (not candidate_set-&gt;Empty()) → if_statement@227 (mode == InnerSearchMode::KNN_SEARCH) → if_statement@228 (-candidate_set-&gt;Top().first &gt; lower_bound && top_candidates-&gt;Size() &gt;= ef) | 当前参考未静态绑定；见下方边界说明 |

| L228 | top_candidates-&gt;Size | while_statement@222 (not candidate_set-&gt;Empty()) → if_statement@227 (mode == InnerSearchMode::KNN_SEARCH) → if_statement@228 (-candidate_set-&gt;Top().first &gt; lower_bound && top_candidates-&gt;Size() &gt;= ef) | 当前参考未静态绑定；见下方边界说明 |

| L232 | candidate_set-&gt;Top | while_statement@222 (not candidate_set-&gt;Empty()) | 当前参考未静态绑定；见下方边界说明 |

| L233 | candidate_set-&gt;Pop | while_statement@222 (not candidate_set-&gt;Empty()) | 当前参考未静态绑定；见下方边界说明 |

| L234 | candidate_set-&gt;Empty | while_statement@222 (not candidate_set-&gt;Empty()) → if_statement@234 (not candidate_set-&gt;Empty()) | 当前参考未静态绑定；见下方边界说明 |

| L235 | graph-&gt;Prefetch | while_statement@222 (not candidate_set-&gt;Empty()) → if_statement@234 (not candidate_set-&gt;Empty()) | 当前参考未静态绑定；见下方边界说明 |

| L235 | candidate_set-&gt;Top | while_statement@222 (not candidate_set-&gt;Empty()) → if_statement@234 (not candidate_set-&gt;Empty()) | 当前参考未静态绑定；见下方边界说明 |

| L238 | visit | while_statement@222 (not candidate_set-&gt;Empty()) | [BasicSearcher::visit · L43](basic_searcher.md#L43) |

| L239 | distance_provider.BatchQueryDistance | while_statement@222 (not candidate_set-&gt;Empty()) | 当前参考未静态绑定；见下方边界说明 |

| L240 | line_dists.data | while_statement@222 (not candidate_set-&gt;Empty()) | 当前参考未静态绑定；见下方边界说明 |

| L240 | to_be_visited_id.data | while_statement@222 (not candidate_set-&gt;Empty()) | 当前参考未静态绑定；见下方边界说明 |

| L245 | distance_provider.IsValid | while_statement@222 (not candidate_set-&gt;Empty()) → for_statement@242 i &lt; count_no_visited → if_statement@245 (not distance_provider.IsValid(id)) | 当前参考未静态绑定；见下方边界说明 |

| L249 | reasoning-&gt;RecordVisit | while_statement@222 (not candidate_set-&gt;Empty()) → for_statement@242 i &lt; count_no_visited → if_statement@248 (reasoning != nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L249 | distance_provider.OriginalId | while_statement@222 (not candidate_set-&gt;Empty()) → for_statement@242 i &lt; count_no_visited → if_statement@248 (reasoning != nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L251 | is_finite_distance | while_statement@222 (not candidate_set-&gt;Empty()) → for_statement@242 i &lt; count_no_visited → if_statement@251 (not is_finite_distance(dist)) | 当前参考未静态绑定；见下方边界说明 |

| L252 | candidate_set-&gt;Push | while_statement@222 (not candidate_set-&gt;Empty()) → for_statement@242 i &lt; count_no_visited → if_statement@251 (not is_finite_distance(dist)) | 当前参考未静态绑定；见下方边界说明 |

| L252 | traversal_priority | while_statement@222 (not candidate_set-&gt;Empty()) → for_statement@242 i &lt; count_no_visited → if_statement@251 (not is_finite_distance(dist)) | 当前参考未静态绑定；见下方边界说明 |

| L253 | check_func | while_statement@222 (not candidate_set-&gt;Empty()) → for_statement@242 i &lt; count_no_visited → if_statement@251 (not is_finite_distance(dist)) → if_statement@253 (check_func(id) and is_result_distance_eligible&lt;mode&gt;(dist, inner_search_param)) | 当前参考未静态绑定；见下方边界说明 |

| L254 | is_result_distance_eligible&lt;mode&gt; | while_statement@222 (not candidate_set-&gt;Empty()) → for_statement@242 i &lt; count_no_visited → if_statement@251 (not is_finite_distance(dist)) → if_statement@253 (check_func(id) and is_result_distance_eligible&lt;mode&gt;(dist, inner_search_param)) | 当前参考未静态绑定；见下方边界说明 |

| L255 | top_candidates-&gt;Push | while_statement@222 (not candidate_set-&gt;Empty()) → for_statement@242 i &lt; count_no_visited → if_statement@251 (not is_finite_distance(dist)) → if_statement@253 (check_func(id) and is_result_distance_eligible&lt;mode&gt;(dist, inner_search_param)) | 当前参考未静态绑定；见下方边界说明 |

| L257 | top_candidates-&gt;Size | while_statement@222 (not candidate_set-&gt;Empty()) → for_statement@242 i &lt; count_no_visited → if_statement@251 (not is_finite_distance(dist)) → if_statement@253 (check_func(id) and is_result_distance_eligible&lt;mode&gt;(dist, inner_search_param)) → if_statement@256 (mode == InnerSearchMode::KNN_SEARCH) → if_statement@257 (top_candidates-&gt;Size() &gt; ef) | 当前参考未静态绑定；见下方边界说明 |

| L259 | reasoning-&gt;RecordEviction | while_statement@222 (not candidate_set-&gt;Empty()) → for_statement@242 i &lt; count_no_visited → if_statement@251 (not is_finite_distance(dist)) → if_statement@253 (check_func(id) and is_result_distance_eligible&lt;mode&gt;(dist, inner_search_param)) → if_statement@256 (mode == InnerSearchMode::KNN_SEARCH) → if_statement@257 (top_candidates-&gt;Size() &gt; ef) → if_statement@258 (reasoning != nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L260 | distance_provider.OriginalId | while_statement@222 (not candidate_set-&gt;Empty()) → for_statement@242 i &lt; count_no_visited → if_statement@251 (not is_finite_distance(dist)) → if_statement@253 (check_func(id) and is_result_distance_eligible&lt;mode&gt;(dist, inner_search_param)) → if_statement@256 (mode == InnerSearchMode::KNN_SEARCH) → if_statement@257 (top_candidates-&gt;Size() &gt; ef) → if_statement@258 (reasoning != nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L260 | top_candidates-&gt;Top | while_statement@222 (not candidate_set-&gt;Empty()) → for_statement@242 i &lt; count_no_visited → if_statement@251 (not is_finite_distance(dist)) → if_statement@253 (check_func(id) and is_result_distance_eligible&lt;mode&gt;(dist, inner_search_param)) → if_statement@256 (mode == InnerSearchMode::KNN_SEARCH) → if_statement@257 (top_candidates-&gt;Size() &gt; ef) → if_statement@258 (reasoning != nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L263 | top_candidates-&gt;Pop | while_statement@222 (not candidate_set-&gt;Empty()) → for_statement@242 i &lt; count_no_visited → if_statement@251 (not is_finite_distance(dist)) → if_statement@253 (check_func(id) and is_result_distance_eligible&lt;mode&gt;(dist, inner_search_param)) → if_statement@256 (mode == InnerSearchMode::KNN_SEARCH) → if_statement@257 (top_candidates-&gt;Size() &gt; ef) | 当前参考未静态绑定；见下方边界说明 |

| L266 | top_candidates-&gt;Pop | while_statement@222 (not candidate_set-&gt;Empty()) → for_statement@242 i &lt; count_no_visited → if_statement@251 (not is_finite_distance(dist)) → if_statement@253 (check_func(id) and is_result_distance_eligible&lt;mode&gt;(dist, inner_search_param)) → if_statement@256 (mode == InnerSearchMode::KNN_SEARCH) [else 分支] → if_statement@265 (dist &gt; inner_search_param.radius) | 当前参考未静态绑定；见下方边界说明 |

| L269 | top_candidates-&gt;Empty | while_statement@222 (not candidate_set-&gt;Empty()) → for_statement@242 i &lt; count_no_visited → if_statement@251 (not is_finite_distance(dist)) → if_statement@269 (not top_candidates-&gt;Empty()) | 当前参考未静态绑定；见下方边界说明 |

| L270 | top_candidates-&gt;Top | while_statement@222 (not candidate_set-&gt;Empty()) → for_statement@242 i &lt; count_no_visited → if_statement@251 (not is_finite_distance(dist)) → if_statement@269 (not top_candidates-&gt;Empty()) | 当前参考未静态绑定；见下方边界说明 |

| L274 | top_candidates-&gt;Size | while_statement@222 (not candidate_set-&gt;Empty()) → for_statement@242 i &lt; count_no_visited → if_statement@274 (top_candidates-&gt;Size() &lt; ef &#124;&#124; lower_bound &gt; dist &#124;&#124; (mode == InnerSearchMode::RANGE_SEARCH && dist &lt;= inner_search_param.radius + THRESHOLD_ERROR)) | 当前参考未静态绑定；见下方边界说明 |

| L277 | candidate_set-&gt;Push | while_statement@222 (not candidate_set-&gt;Empty()) → for_statement@242 i &lt; count_no_visited → if_statement@274 (top_candidates-&gt;Size() &lt; ef &#124;&#124; lower_bound &gt; dist &#124;&#124; (mode == InnerSearchMode::RANGE_SEARCH && dist &lt;= inner_search_param.radius + THRESHOLD_ERROR)) | 当前参考未静态绑定；见下方边界说明 |

| L278 | distance_provider.Prefetch | while_statement@222 (not candidate_set-&gt;Empty()) → for_statement@242 i &lt; count_no_visited → if_statement@274 (top_candidates-&gt;Size() &lt; ef &#124;&#124; lower_bound &gt; dist &#124;&#124; (mode == InnerSearchMode::RANGE_SEARCH && dist &lt;= inner_search_param.radius + THRESHOLD_ERROR)) | 当前参考未静态绑定；见下方边界说明 |

| L278 | candidate_set-&gt;Top | while_statement@222 (not candidate_set-&gt;Empty()) → for_statement@242 i &lt; count_no_visited → if_statement@274 (top_candidates-&gt;Size() &lt; ef &#124;&#124; lower_bound &gt; dist &#124;&#124; (mode == InnerSearchMode::RANGE_SEARCH && dist &lt;= inner_search_param.radius + THRESHOLD_ERROR)) | 当前参考未静态绑定；见下方边界说明 |

| L279 | check_func | while_statement@222 (not candidate_set-&gt;Empty()) → for_statement@242 i &lt; count_no_visited → if_statement@274 (top_candidates-&gt;Size() &lt; ef &#124;&#124; lower_bound &gt; dist &#124;&#124; (mode == InnerSearchMode::RANGE_SEARCH && dist &lt;= inner_search_param.radius + THRESHOLD_ERROR)) → if_statement@279 (check_func(id)) | 当前参考未静态绑定；见下方边界说明 |

| L280 | top_candidates-&gt;Push | while_statement@222 (not candidate_set-&gt;Empty()) → for_statement@242 i &lt; count_no_visited → if_statement@274 (top_candidates-&gt;Size() &lt; ef &#124;&#124; lower_bound &gt; dist &#124;&#124; (mode == InnerSearchMode::RANGE_SEARCH && dist &lt;= inner_search_param.radius + THRESHOLD_ERROR)) → if_statement@279 (check_func(id)) | 当前参考未静态绑定；见下方边界说明 |

| L282 | reasoning-&gt;RecordFilterReject | while_statement@222 (not candidate_set-&gt;Empty()) → for_statement@242 i &lt; count_no_visited → if_statement@274 (top_candidates-&gt;Size() &lt; ef &#124;&#124; lower_bound &gt; dist &#124;&#124; (mode == InnerSearchMode::RANGE_SEARCH && dist &lt;= inner_search_param.radius + THRESHOLD_ERROR)) → if_statement@279 (check_func(id)) [else 分支] → if_statement@281 (reasoning != nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L282 | distance_provider.OriginalId | while_statement@222 (not candidate_set-&gt;Empty()) → for_statement@242 i &lt; count_no_visited → if_statement@274 (top_candidates-&gt;Size() &lt; ef &#124;&#124; lower_bound &gt; dist &#124;&#124; (mode == InnerSearchMode::RANGE_SEARCH && dist &lt;= inner_search_param.radius + THRESHOLD_ERROR)) → if_statement@279 (check_func(id)) [else 分支] → if_statement@281 (reasoning != nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L285 | top_candidates-&gt;Size | while_statement@222 (not candidate_set-&gt;Empty()) → for_statement@242 i &lt; count_no_visited → if_statement@274 (top_candidates-&gt;Size() &lt; ef &#124;&#124; lower_bound &gt; dist &#124;&#124; (mode == InnerSearchMode::RANGE_SEARCH && dist &lt;= inner_search_param.radius + THRESHOLD_ERROR)) → if_statement@284 (mode == InnerSearchMode::KNN_SEARCH) → if_statement@285 (top_candidates-&gt;Size() &gt; ef) | 当前参考未静态绑定；见下方边界说明 |

| L287 | reasoning-&gt;RecordEviction | while_statement@222 (not candidate_set-&gt;Empty()) → for_statement@242 i &lt; count_no_visited → if_statement@274 (top_candidates-&gt;Size() &lt; ef &#124;&#124; lower_bound &gt; dist &#124;&#124; (mode == InnerSearchMode::RANGE_SEARCH && dist &lt;= inner_search_param.radius + THRESHOLD_ERROR)) → if_statement@284 (mode == InnerSearchMode::KNN_SEARCH) → if_statement@285 (top_candidates-&gt;Size() &gt; ef) → if_statement@286 (reasoning != nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L288 | distance_provider.OriginalId | while_statement@222 (not candidate_set-&gt;Empty()) → for_statement@242 i &lt; count_no_visited → if_statement@274 (top_candidates-&gt;Size() &lt; ef &#124;&#124; lower_bound &gt; dist &#124;&#124; (mode == InnerSearchMode::RANGE_SEARCH && dist &lt;= inner_search_param.radius + THRESHOLD_ERROR)) → if_statement@284 (mode == InnerSearchMode::KNN_SEARCH) → if_statement@285 (top_candidates-&gt;Size() &gt; ef) → if_statement@286 (reasoning != nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L288 | top_candidates-&gt;Top | while_statement@222 (not candidate_set-&gt;Empty()) → for_statement@242 i &lt; count_no_visited → if_statement@274 (top_candidates-&gt;Size() &lt; ef &#124;&#124; lower_bound &gt; dist &#124;&#124; (mode == InnerSearchMode::RANGE_SEARCH && dist &lt;= inner_search_param.radius + THRESHOLD_ERROR)) → if_statement@284 (mode == InnerSearchMode::KNN_SEARCH) → if_statement@285 (top_candidates-&gt;Size() &gt; ef) → if_statement@286 (reasoning != nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L290 | top_candidates-&gt;Pop | while_statement@222 (not candidate_set-&gt;Empty()) → for_statement@242 i &lt; count_no_visited → if_statement@274 (top_candidates-&gt;Size() &lt; ef &#124;&#124; lower_bound &gt; dist &#124;&#124; (mode == InnerSearchMode::RANGE_SEARCH && dist &lt;= inner_search_param.radius + THRESHOLD_ERROR)) → if_statement@284 (mode == InnerSearchMode::KNN_SEARCH) → if_statement@285 (top_candidates-&gt;Size() &gt; ef) | 当前参考未静态绑定；见下方边界说明 |

| L293 | top_candidates-&gt;Empty | while_statement@222 (not candidate_set-&gt;Empty()) → for_statement@242 i &lt; count_no_visited → if_statement@274 (top_candidates-&gt;Size() &lt; ef &#124;&#124; lower_bound &gt; dist &#124;&#124; (mode == InnerSearchMode::RANGE_SEARCH && dist &lt;= inner_search_param.radius + THRESHOLD_ERROR)) → if_statement@293 (not top_candidates-&gt;Empty()) | 当前参考未静态绑定；见下方边界说明 |

| L294 | top_candidates-&gt;Top | while_statement@222 (not candidate_set-&gt;Empty()) → for_statement@242 i &lt; count_no_visited → if_statement@274 (top_candidates-&gt;Size() &lt; ef &#124;&#124; lower_bound &gt; dist &#124;&#124; (mode == InnerSearchMode::RANGE_SEARCH && dist &lt;= inner_search_param.radius + THRESHOLD_ERROR)) → if_statement@293 (not top_candidates-&gt;Empty()) | 当前参考未静态绑定；见下方边界说明 |

| L300 | top_candidates-&gt;Size | if_statement@299 (mode == InnerSearchMode::KNN_SEARCH) → while_statement@300 (top_candidates-&gt;Size() &gt; inner_search_param.topk) | 当前参考未静态绑定；见下方边界说明 |

| L301 | top_candidates-&gt;Pop | if_statement@299 (mode == InnerSearchMode::KNN_SEARCH) → while_statement@300 (top_candidates-&gt;Size() &gt; inner_search_param.topk) | 当前参考未静态绑定；见下方边界说明 |

| L305 | top_candidates-&gt;Size | if_statement@299 (mode == InnerSearchMode::KNN_SEARCH) [else 分支] → if_statement@304 (inner_search_param.range_search_limit_size &gt; 0) → while_statement@305 (top_candidates-&gt;Size() &gt; inner_search_param.range_search_limit_size) | 当前参考未静态绑定；见下方边界说明 |

| L306 | top_candidates-&gt;Pop | if_statement@299 (mode == InnerSearchMode::KNN_SEARCH) [else 分支] → if_statement@304 (inner_search_param.range_search_limit_size &gt; 0) → while_statement@305 (top_candidates-&gt;Size() &gt; inner_search_param.range_search_limit_size) | 当前参考未静态绑定；见下方边界说明 |

| L309 | top_candidates-&gt;Empty | if_statement@299 (mode == InnerSearchMode::KNN_SEARCH) [else 分支] → while_statement@309 (not top_candidates-&gt;Empty() && top_candidates-&gt;Top().first &gt; inner_search_param.radius + THRESHOLD_ERROR) | 当前参考未静态绑定；见下方边界说明 |

| L310 | top_candidates-&gt;Top | if_statement@299 (mode == InnerSearchMode::KNN_SEARCH) [else 分支] → while_statement@309 (not top_candidates-&gt;Empty() && top_candidates-&gt;Top().first &gt; inner_search_param.radius + THRESHOLD_ERROR) | 当前参考未静态绑定；见下方边界说明 |

| L311 | top_candidates-&gt;Pop | if_statement@299 (mode == InnerSearchMode::KNN_SEARCH) [else 分支] → while_statement@309 (not top_candidates-&gt;Empty() && top_candidates-&gt;Top().first &gt; inner_search_param.radius + THRESHOLD_ERROR) | 当前参考未静态绑定；见下方边界说明 |

| L315 | ctx-&gt;stats-&gt;dist_cmp.fetch_add | if_statement@314 (ctx != nullptr && ctx-&gt;stats != nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L316 | ctx-&gt;stats-&gt;hops.fetch_add | if_statement@314 (ctx != nullptr && ctx-&gt;stats != nullptr) | 当前参考未静态绑定；见下方边界说明 |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L322"></a>

## `BasicSearcher::search_impl`

源码位置：`src/impl/searcher/basic_searcher.cpp:322–548`。

先从签名确认输入、返回值和 const/override，再按完整函数体的条件阅读调用点。下表保留了本函数的显式调用以及 lambda 中的调用；进入下层时用“候选实现”定位，未解析的对象由源码静态类型/运行时类型确认。

### 完整函数

```cpp
DistHeapPtr
BasicSearcher::search_impl(const GraphInterfacePtr& graph,
                           const FlattenInterfacePtr& flatten,
                           const VisitedListPtr& vl,
                           const void* query,
                           const InnerSearchParam& inner_search_param,
                           IteratorFilterContext* iter_ctx,
                           QueryContext* ctx,
                           DistanceRecordVector* rabitq_lower_bound_candidates) const {
    // set customize query alloctor
    Allocator* alloc = select_query_allocator(ctx, allocator_);

    auto top_candidates = std::make_shared<StandardHeap<true, false>>(alloc, -1);
    auto candidate_set = std::make_shared<StandardHeap<true, false>>(alloc, -1);

    if (not graph or not flatten) {
        return top_candidates;
    }

    auto computer_lease = AcquireQueryComputer(flatten, query, ctx);
    const auto& computer = computer_lease.computer;

    auto is_id_allowed = inner_search_param.is_inner_id_allowed;
    auto ep = inner_search_param.ep;
    auto ef = inner_search_param.ef;
    auto* reasoning = ctx == nullptr ? nullptr : ctx->reasoning_ctx;

    float dist = 0.0F;
    uint64_t ids_cnt = 1;
    auto lower_bound = std::numeric_limits<float>::max();

    uint32_t hops = 0;
    uint32_t dist_cmp = 0;
    uint32_t count_no_visited = 0;
    Vector<InnerIdType> to_be_visited_id(graph->MaximumDegree(), alloc);
    Vector<InnerIdType> neighbors(graph->MaximumDegree(), alloc);
    Vector<float> line_dists(graph->MaximumDegree(), alloc);
    Vector<float> lower_bound_dists(graph->MaximumDegree(), alloc);
    auto skip_strategy = create_filter_search_skip_strategy(
        inner_search_param.skip_strategy_type,
        inner_search_param.is_inner_id_allowed != nullptr
            ? inner_search_param.is_inner_id_allowed->ValidRatio()
            : 1.0F,
        inner_search_param.skip_ratio);
    if (rabitq_lower_bound_candidates != nullptr) {
        rabitq_lower_bound_candidates->clear();
    }

    if (!iter_ctx->IsFirstUsed()) {
        if (iter_ctx->Empty()) {
            return top_candidates;
        }
        while (!iter_ctx->Empty()) {
            uint32_t cur_inner_id = iter_ctx->GetTopID();
            float cur_dist = iter_ctx->GetTopDist();
            vl->Set(cur_inner_id);
            if (iter_ctx->CheckPoint(cur_inner_id)) {
                flatten->Query(&cur_dist, computer, &cur_inner_id, 1, ctx);
                // Sign convention: top_candidates stores positive distances (nearest = smallest);
                // candidate_set is a max-heap, so distances are negated (nearest = largest, popped first).
                if (is_result_distance_eligible<mode>(cur_dist, inner_search_param)) {
                    top_candidates->Push(cur_dist, cur_inner_id);
                }
                candidate_set->Push(traversal_priority(cur_dist), cur_inner_id);
                if constexpr (mode == InnerSearchMode::RANGE_SEARCH) {
                    if (cur_dist > inner_search_param.radius and not top_candidates->Empty()) {
                        top_candidates->Pop();
                    }
                }
            }
            iter_ctx->PopDiscard();
        }
        if constexpr (mode == InnerSearchMode::KNN_SEARCH) {
            while (top_candidates->Size() > ef) {
                auto cur_node_pair = top_candidates->Top();
                if (iter_ctx->CheckPoint(cur_node_pair.second)) {
                    iter_ctx->AddDiscardNode(cur_node_pair.first, cur_node_pair.second);
                }
                top_candidates->Pop();
            }
        }
        if (not top_candidates->Empty()) {
            lower_bound = top_candidates->Top().first;
        }
    } else {
        if (inner_search_param.enable_rabitq_one_bit_search) {
            flatten->QueryWithDistanceLowerBound(&dist, nullptr, computer, &ep, 1, ctx);
        } else {
            flatten->Query(&dist, computer, &ep, 1, ctx);
        }
        if (not is_id_allowed || is_id_allowed->CheckValid(ep)) {
            if (is_result_distance_eligible<mode>(dist, inner_search_param)) {
                top_candidates->Push(dist, ep);
                lower_bound = top_candidates->Top().first;
            }
        }
        candidate_set->Push(traversal_priority(dist), ep);
        vl->Set(ep);
    }

    while (not candidate_set->Empty()) {
        hops++;
        if (hops >= inner_search_param.hops_limit) {
            break;
        }
        auto current_node_pair = candidate_set->Top();

        if constexpr (mode == InnerSearchMode::KNN_SEARCH) {
            if ((-current_node_pair.first) > lower_bound && top_candidates->Size() >= ef) {
                if (reasoning != nullptr) {
                    reasoning->SetTermination(ReasoningContext::kTerminationLowerBoundReached);
                }
                break;
            }
        }
        candidate_set->Pop();

        if (not candidate_set->Empty()) {
            graph->Prefetch(candidate_set->Top().second, 0);
        }

        count_no_visited = visit(graph,
                                 vl,
                                 current_node_pair,
                                 inner_search_param.is_inner_id_allowed,
                                 skip_strategy.get(),
                                 to_be_visited_id,
                                 neighbors);

        dist_cmp += count_no_visited;

        bool collect_rabitq_lower_bound = false;
        if (inner_search_param.enable_rabitq_one_bit_search and top_candidates->Size() == ef and
            rabitq_lower_bound_candidates != nullptr) {
            collect_rabitq_lower_bound = true;
            flatten->QueryWithDistanceLowerBound(line_dists.data(),
                                                 lower_bound_dists.data(),
                                                 computer,
                                                 to_be_visited_id.data(),
                                                 count_no_visited,
                                                 ctx);
        } else if (inner_search_param.enable_rabitq_one_bit_search) {
            flatten->QueryWithDistanceLowerBound(line_dists.data(),
                                                 nullptr,
                                                 computer,
                                                 to_be_visited_id.data(),
                                                 count_no_visited,
                                                 ctx);
        } else {
            flatten->Query(
                line_dists.data(), computer, to_be_visited_id.data(), count_no_visited, ctx);
        }
        for (uint32_t i = 0; i < count_no_visited; i++) {
            dist = line_dists[i];
            const auto cur_id = to_be_visited_id[i];
            if (not is_finite_distance(dist)) {
                if (is_result_distance_eligible<mode>(dist, inner_search_param) and
                    (not is_id_allowed || is_id_allowed->CheckValid(cur_id))) {
                    top_candidates->Push(dist, cur_id);
                    if constexpr (mode == KNN_SEARCH) {
                        if (top_candidates->Size() > ef) {
                            const auto evicted = top_candidates->Top();
                            if (iter_ctx->CheckPoint(evicted.second)) {
                                iter_ctx->AddDiscardNode(evicted.first, evicted.second);
                            }
                            top_candidates->Pop();
                        }
                    } else if (dist > inner_search_param.radius) {
                        top_candidates->Pop();
                    }
                }
                if (iter_ctx->CheckPoint(cur_id)) {
                    candidate_set->Push(traversal_priority(dist), cur_id);
                    flatten->Prefetch(cur_id);
                }
                if (not top_candidates->Empty()) {
                    lower_bound = top_candidates->Top().first;
                }
                continue;
            }
            const bool id_allowed = not is_id_allowed || is_id_allowed->CheckValid(cur_id);
            if constexpr (mode == KNN_SEARCH) {
                if (collect_rabitq_lower_bound and lower_bound_dists[i] < lower_bound and
                    id_allowed and iter_ctx->CheckPoint(cur_id)) {
                    rabitq_lower_bound_candidates->emplace_back(lower_bound_dists[i], cur_id);
                }
            }
            if (top_candidates->Size() < ef || lower_bound > dist ||
                (mode == RANGE_SEARCH && dist <= inner_search_param.radius)) {
                if (!iter_ctx->CheckPoint(cur_id)) {
                    continue;
                }
                candidate_set->Push(-dist, cur_id);
                flatten->Prefetch(candidate_set->Top().second);
                if (id_allowed) {
                    top_candidates->Push(dist, cur_id);
                }

                if constexpr (mode == KNN_SEARCH) {
                    if (top_candidates->Size() > ef) {
                        if (iter_ctx->CheckPoint(top_candidates->Top().second)) {
                            auto cur_node_pair = top_candidates->Top();
                            iter_ctx->AddDiscardNode(cur_node_pair.first, cur_node_pair.second);
                        }
                        top_candidates->Pop();
                    }
                }

                if (not top_candidates->Empty()) {
                    lower_bound = top_candidates->Top().first;
                }
            }
        }
    }

    if constexpr (mode == KNN_SEARCH) {
        while (top_candidates->Size() > inner_search_param.topk) {
            auto cur_node_pair = top_candidates->Top();
            if (iter_ctx->CheckPoint(cur_node_pair.second)) {
                iter_ctx->AddDiscardNode(cur_node_pair.first, cur_node_pair.second);
            }
            top_candidates->Pop();
        }
    }

    return top_candidates;
}
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L332 | select_query_allocator | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L334 | std::make_shared&lt;StandardHeap&lt;true, false&gt;&gt; | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L335 | std::make_shared&lt;StandardHeap&lt;true, false&gt;&gt; | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L341 | AcquireQueryComputer | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L351 | std::numeric_limits&lt;float&gt;::max | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L356 | graph-&gt;MaximumDegree | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L357 | graph-&gt;MaximumDegree | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L358 | graph-&gt;MaximumDegree | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L359 | graph-&gt;MaximumDegree | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L360 | create_filter_search_skip_strategy | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L363 | inner_search_param.is_inner_id_allowed-&gt;ValidRatio | conditional_expression@362 inner_search_param.is_inner_id_allowed != nullptr | 当前参考未静态绑定；见下方边界说明 |

| L367 | rabitq_lower_bound_candidates-&gt;clear | if_statement@366 (rabitq_lower_bound_candidates != nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L370 | iter_ctx-&gt;IsFirstUsed | if_statement@370 (!iter_ctx-&gt;IsFirstUsed()) | 当前参考未静态绑定；见下方边界说明 |

| L371 | iter_ctx-&gt;Empty | if_statement@370 (!iter_ctx-&gt;IsFirstUsed()) → if_statement@371 (iter_ctx-&gt;Empty()) | 当前参考未静态绑定；见下方边界说明 |

| L374 | iter_ctx-&gt;Empty | if_statement@370 (!iter_ctx-&gt;IsFirstUsed()) → while_statement@374 (!iter_ctx-&gt;Empty()) | 当前参考未静态绑定；见下方边界说明 |

| L375 | iter_ctx-&gt;GetTopID | if_statement@370 (!iter_ctx-&gt;IsFirstUsed()) → while_statement@374 (!iter_ctx-&gt;Empty()) | 当前参考未静态绑定；见下方边界说明 |

| L376 | iter_ctx-&gt;GetTopDist | if_statement@370 (!iter_ctx-&gt;IsFirstUsed()) → while_statement@374 (!iter_ctx-&gt;Empty()) | 当前参考未静态绑定；见下方边界说明 |

| L377 | vl-&gt;Set | if_statement@370 (!iter_ctx-&gt;IsFirstUsed()) → while_statement@374 (!iter_ctx-&gt;Empty()) | 当前参考未静态绑定；见下方边界说明 |

| L378 | iter_ctx-&gt;CheckPoint | if_statement@370 (!iter_ctx-&gt;IsFirstUsed()) → while_statement@374 (!iter_ctx-&gt;Empty()) → if_statement@378 (iter_ctx-&gt;CheckPoint(cur_inner_id)) | 当前参考未静态绑定；见下方边界说明 |

| L379 | flatten-&gt;Query | if_statement@370 (!iter_ctx-&gt;IsFirstUsed()) → while_statement@374 (!iter_ctx-&gt;Empty()) → if_statement@378 (iter_ctx-&gt;CheckPoint(cur_inner_id)) | 当前参考未静态绑定；见下方边界说明 |

| L382 | is_result_distance_eligible&lt;mode&gt; | if_statement@370 (!iter_ctx-&gt;IsFirstUsed()) → while_statement@374 (!iter_ctx-&gt;Empty()) → if_statement@378 (iter_ctx-&gt;CheckPoint(cur_inner_id)) → if_statement@382 (is_result_distance_eligible&lt;mode&gt;(cur_dist, inner_search_param)) | 当前参考未静态绑定；见下方边界说明 |

| L383 | top_candidates-&gt;Push | if_statement@370 (!iter_ctx-&gt;IsFirstUsed()) → while_statement@374 (!iter_ctx-&gt;Empty()) → if_statement@378 (iter_ctx-&gt;CheckPoint(cur_inner_id)) → if_statement@382 (is_result_distance_eligible&lt;mode&gt;(cur_dist, inner_search_param)) | 当前参考未静态绑定；见下方边界说明 |

| L385 | candidate_set-&gt;Push | if_statement@370 (!iter_ctx-&gt;IsFirstUsed()) → while_statement@374 (!iter_ctx-&gt;Empty()) → if_statement@378 (iter_ctx-&gt;CheckPoint(cur_inner_id)) | 当前参考未静态绑定；见下方边界说明 |

| L385 | traversal_priority | if_statement@370 (!iter_ctx-&gt;IsFirstUsed()) → while_statement@374 (!iter_ctx-&gt;Empty()) → if_statement@378 (iter_ctx-&gt;CheckPoint(cur_inner_id)) | 当前参考未静态绑定；见下方边界说明 |

| L387 | top_candidates-&gt;Empty | if_statement@370 (!iter_ctx-&gt;IsFirstUsed()) → while_statement@374 (!iter_ctx-&gt;Empty()) → if_statement@378 (iter_ctx-&gt;CheckPoint(cur_inner_id)) → if_statement@386 (mode == InnerSearchMode::RANGE_SEARCH) → if_statement@387 (cur_dist &gt; inner_search_param.radius and not top_candidates-&gt;Empty()) | 当前参考未静态绑定；见下方边界说明 |

| L388 | top_candidates-&gt;Pop | if_statement@370 (!iter_ctx-&gt;IsFirstUsed()) → while_statement@374 (!iter_ctx-&gt;Empty()) → if_statement@378 (iter_ctx-&gt;CheckPoint(cur_inner_id)) → if_statement@386 (mode == InnerSearchMode::RANGE_SEARCH) → if_statement@387 (cur_dist &gt; inner_search_param.radius and not top_candidates-&gt;Empty()) | 当前参考未静态绑定；见下方边界说明 |

| L392 | iter_ctx-&gt;PopDiscard | if_statement@370 (!iter_ctx-&gt;IsFirstUsed()) → while_statement@374 (!iter_ctx-&gt;Empty()) | 当前参考未静态绑定；见下方边界说明 |

| L395 | top_candidates-&gt;Size | if_statement@370 (!iter_ctx-&gt;IsFirstUsed()) → if_statement@394 (mode == InnerSearchMode::KNN_SEARCH) → while_statement@395 (top_candidates-&gt;Size() &gt; ef) | 当前参考未静态绑定；见下方边界说明 |

| L396 | top_candidates-&gt;Top | if_statement@370 (!iter_ctx-&gt;IsFirstUsed()) → if_statement@394 (mode == InnerSearchMode::KNN_SEARCH) → while_statement@395 (top_candidates-&gt;Size() &gt; ef) | 当前参考未静态绑定；见下方边界说明 |

| L397 | iter_ctx-&gt;CheckPoint | if_statement@370 (!iter_ctx-&gt;IsFirstUsed()) → if_statement@394 (mode == InnerSearchMode::KNN_SEARCH) → while_statement@395 (top_candidates-&gt;Size() &gt; ef) → if_statement@397 (iter_ctx-&gt;CheckPoint(cur_node_pair.second)) | 当前参考未静态绑定；见下方边界说明 |

| L398 | iter_ctx-&gt;AddDiscardNode | if_statement@370 (!iter_ctx-&gt;IsFirstUsed()) → if_statement@394 (mode == InnerSearchMode::KNN_SEARCH) → while_statement@395 (top_candidates-&gt;Size() &gt; ef) → if_statement@397 (iter_ctx-&gt;CheckPoint(cur_node_pair.second)) | 当前参考未静态绑定；见下方边界说明 |

| L400 | top_candidates-&gt;Pop | if_statement@370 (!iter_ctx-&gt;IsFirstUsed()) → if_statement@394 (mode == InnerSearchMode::KNN_SEARCH) → while_statement@395 (top_candidates-&gt;Size() &gt; ef) | 当前参考未静态绑定；见下方边界说明 |

| L403 | top_candidates-&gt;Empty | if_statement@370 (!iter_ctx-&gt;IsFirstUsed()) → if_statement@403 (not top_candidates-&gt;Empty()) | 当前参考未静态绑定；见下方边界说明 |

| L404 | top_candidates-&gt;Top | if_statement@370 (!iter_ctx-&gt;IsFirstUsed()) → if_statement@403 (not top_candidates-&gt;Empty()) | 当前参考未静态绑定；见下方边界说明 |

| L408 | flatten-&gt;QueryWithDistanceLowerBound | if_statement@370 (!iter_ctx-&gt;IsFirstUsed()) [else 分支] → if_statement@407 (inner_search_param.enable_rabitq_one_bit_search) | 当前参考未静态绑定；见下方边界说明 |

| L410 | flatten-&gt;Query | if_statement@370 (!iter_ctx-&gt;IsFirstUsed()) [else 分支] → if_statement@407 (inner_search_param.enable_rabitq_one_bit_search) [else 分支] | 当前参考未静态绑定；见下方边界说明 |

| L412 | is_id_allowed-&gt;CheckValid | if_statement@370 (!iter_ctx-&gt;IsFirstUsed()) [else 分支] → if_statement@412 (not is_id_allowed &#124;&#124; is_id_allowed-&gt;CheckValid(ep)) | 当前参考未静态绑定；见下方边界说明 |

| L413 | is_result_distance_eligible&lt;mode&gt; | if_statement@370 (!iter_ctx-&gt;IsFirstUsed()) [else 分支] → if_statement@412 (not is_id_allowed &#124;&#124; is_id_allowed-&gt;CheckValid(ep)) → if_statement@413 (is_result_distance_eligible&lt;mode&gt;(dist, inner_search_param)) | 当前参考未静态绑定；见下方边界说明 |

| L414 | top_candidates-&gt;Push | if_statement@370 (!iter_ctx-&gt;IsFirstUsed()) [else 分支] → if_statement@412 (not is_id_allowed &#124;&#124; is_id_allowed-&gt;CheckValid(ep)) → if_statement@413 (is_result_distance_eligible&lt;mode&gt;(dist, inner_search_param)) | 当前参考未静态绑定；见下方边界说明 |

| L415 | top_candidates-&gt;Top | if_statement@370 (!iter_ctx-&gt;IsFirstUsed()) [else 分支] → if_statement@412 (not is_id_allowed &#124;&#124; is_id_allowed-&gt;CheckValid(ep)) → if_statement@413 (is_result_distance_eligible&lt;mode&gt;(dist, inner_search_param)) | 当前参考未静态绑定；见下方边界说明 |

| L418 | candidate_set-&gt;Push | if_statement@370 (!iter_ctx-&gt;IsFirstUsed()) [else 分支] | 当前参考未静态绑定；见下方边界说明 |

| L418 | traversal_priority | if_statement@370 (!iter_ctx-&gt;IsFirstUsed()) [else 分支] | 当前参考未静态绑定；见下方边界说明 |

| L419 | vl-&gt;Set | if_statement@370 (!iter_ctx-&gt;IsFirstUsed()) [else 分支] | 当前参考未静态绑定；见下方边界说明 |

| L422 | candidate_set-&gt;Empty | while_statement@422 (not candidate_set-&gt;Empty()) | 当前参考未静态绑定；见下方边界说明 |

| L427 | candidate_set-&gt;Top | while_statement@422 (not candidate_set-&gt;Empty()) | 当前参考未静态绑定；见下方边界说明 |

| L430 | top_candidates-&gt;Size | while_statement@422 (not candidate_set-&gt;Empty()) → if_statement@429 (mode == InnerSearchMode::KNN_SEARCH) → if_statement@430 ((-current_node_pair.first) &gt; lower_bound && top_candidates-&gt;Size() &gt;= ef) | 当前参考未静态绑定；见下方边界说明 |

| L432 | reasoning-&gt;SetTermination | while_statement@422 (not candidate_set-&gt;Empty()) → if_statement@429 (mode == InnerSearchMode::KNN_SEARCH) → if_statement@430 ((-current_node_pair.first) &gt; lower_bound && top_candidates-&gt;Size() &gt;= ef) → if_statement@431 (reasoning != nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L437 | candidate_set-&gt;Pop | while_statement@422 (not candidate_set-&gt;Empty()) | 当前参考未静态绑定；见下方边界说明 |

| L439 | candidate_set-&gt;Empty | while_statement@422 (not candidate_set-&gt;Empty()) → if_statement@439 (not candidate_set-&gt;Empty()) | 当前参考未静态绑定；见下方边界说明 |

| L440 | graph-&gt;Prefetch | while_statement@422 (not candidate_set-&gt;Empty()) → if_statement@439 (not candidate_set-&gt;Empty()) | 当前参考未静态绑定；见下方边界说明 |

| L440 | candidate_set-&gt;Top | while_statement@422 (not candidate_set-&gt;Empty()) → if_statement@439 (not candidate_set-&gt;Empty()) | 当前参考未静态绑定；见下方边界说明 |

| L443 | visit | while_statement@422 (not candidate_set-&gt;Empty()) | [BasicSearcher::visit · L43](basic_searcher.md#L43) |

| L447 | skip_strategy.get | while_statement@422 (not candidate_set-&gt;Empty()) | 当前参考未静态绑定；见下方边界说明 |

| L454 | top_candidates-&gt;Size | while_statement@422 (not candidate_set-&gt;Empty()) → if_statement@454 (inner_search_param.enable_rabitq_one_bit_search and top_candidates-&gt;Size() == ef and rabitq_lower_bound_candidates != nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L457 | flatten-&gt;QueryWithDistanceLowerBound | while_statement@422 (not candidate_set-&gt;Empty()) → if_statement@454 (inner_search_param.enable_rabitq_one_bit_search and top_candidates-&gt;Size() == ef and rabitq_lower_bound_candidates != nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L457 | line_dists.data | while_statement@422 (not candidate_set-&gt;Empty()) → if_statement@454 (inner_search_param.enable_rabitq_one_bit_search and top_candidates-&gt;Size() == ef and rabitq_lower_bound_candidates != nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L458 | lower_bound_dists.data | while_statement@422 (not candidate_set-&gt;Empty()) → if_statement@454 (inner_search_param.enable_rabitq_one_bit_search and top_candidates-&gt;Size() == ef and rabitq_lower_bound_candidates != nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L460 | to_be_visited_id.data | while_statement@422 (not candidate_set-&gt;Empty()) → if_statement@454 (inner_search_param.enable_rabitq_one_bit_search and top_candidates-&gt;Size() == ef and rabitq_lower_bound_candidates != nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L464 | flatten-&gt;QueryWithDistanceLowerBound | while_statement@422 (not candidate_set-&gt;Empty()) → if_statement@454 (inner_search_param.enable_rabitq_one_bit_search and top_candidates-&gt;Size() == ef and rabitq_lower_bound_candidates != nullptr) [else 分支] → if_statement@463 (inner_search_param.enable_rabitq_one_bit_search) | 当前参考未静态绑定；见下方边界说明 |

| L464 | line_dists.data | while_statement@422 (not candidate_set-&gt;Empty()) → if_statement@454 (inner_search_param.enable_rabitq_one_bit_search and top_candidates-&gt;Size() == ef and rabitq_lower_bound_candidates != nullptr) [else 分支] → if_statement@463 (inner_search_param.enable_rabitq_one_bit_search) | 当前参考未静态绑定；见下方边界说明 |

| L467 | to_be_visited_id.data | while_statement@422 (not candidate_set-&gt;Empty()) → if_statement@454 (inner_search_param.enable_rabitq_one_bit_search and top_candidates-&gt;Size() == ef and rabitq_lower_bound_candidates != nullptr) [else 分支] → if_statement@463 (inner_search_param.enable_rabitq_one_bit_search) | 当前参考未静态绑定；见下方边界说明 |

| L471 | flatten-&gt;Query | while_statement@422 (not candidate_set-&gt;Empty()) → if_statement@454 (inner_search_param.enable_rabitq_one_bit_search and top_candidates-&gt;Size() == ef and rabitq_lower_bound_candidates != nullptr) [else 分支] → if_statement@463 (inner_search_param.enable_rabitq_one_bit_search) [else 分支] | 当前参考未静态绑定；见下方边界说明 |

| L472 | line_dists.data | while_statement@422 (not candidate_set-&gt;Empty()) → if_statement@454 (inner_search_param.enable_rabitq_one_bit_search and top_candidates-&gt;Size() == ef and rabitq_lower_bound_candidates != nullptr) [else 分支] → if_statement@463 (inner_search_param.enable_rabitq_one_bit_search) [else 分支] | 当前参考未静态绑定；见下方边界说明 |

| L472 | to_be_visited_id.data | while_statement@422 (not candidate_set-&gt;Empty()) → if_statement@454 (inner_search_param.enable_rabitq_one_bit_search and top_candidates-&gt;Size() == ef and rabitq_lower_bound_candidates != nullptr) [else 分支] → if_statement@463 (inner_search_param.enable_rabitq_one_bit_search) [else 分支] | 当前参考未静态绑定；见下方边界说明 |

| L477 | is_finite_distance | while_statement@422 (not candidate_set-&gt;Empty()) → for_statement@474 i &lt; count_no_visited → if_statement@477 (not is_finite_distance(dist)) | 当前参考未静态绑定；见下方边界说明 |

| L478 | is_result_distance_eligible&lt;mode&gt; | while_statement@422 (not candidate_set-&gt;Empty()) → for_statement@474 i &lt; count_no_visited → if_statement@477 (not is_finite_distance(dist)) → if_statement@478 (is_result_distance_eligible&lt;mode&gt;(dist, inner_search_param) and (not is_id_allowed &#124;&#124; is_id_allowed-&gt;CheckValid(cur_id))) | 当前参考未静态绑定；见下方边界说明 |

| L479 | is_id_allowed-&gt;CheckValid | while_statement@422 (not candidate_set-&gt;Empty()) → for_statement@474 i &lt; count_no_visited → if_statement@477 (not is_finite_distance(dist)) → if_statement@478 (is_result_distance_eligible&lt;mode&gt;(dist, inner_search_param) and (not is_id_allowed &#124;&#124; is_id_allowed-&gt;CheckValid(cur_id))) | 当前参考未静态绑定；见下方边界说明 |

| L480 | top_candidates-&gt;Push | while_statement@422 (not candidate_set-&gt;Empty()) → for_statement@474 i &lt; count_no_visited → if_statement@477 (not is_finite_distance(dist)) → if_statement@478 (is_result_distance_eligible&lt;mode&gt;(dist, inner_search_param) and (not is_id_allowed &#124;&#124; is_id_allowed-&gt;CheckValid(cur_id))) | 当前参考未静态绑定；见下方边界说明 |

| L482 | top_candidates-&gt;Size | while_statement@422 (not candidate_set-&gt;Empty()) → for_statement@474 i &lt; count_no_visited → if_statement@477 (not is_finite_distance(dist)) → if_statement@478 (is_result_distance_eligible&lt;mode&gt;(dist, inner_search_param) and (not is_id_allowed &#124;&#124; is_id_allowed-&gt;CheckValid(cur_id))) → if_statement@481 (mode == KNN_SEARCH) → if_statement@482 (top_candidates-&gt;Size() &gt; ef) | 当前参考未静态绑定；见下方边界说明 |

| L483 | top_candidates-&gt;Top | while_statement@422 (not candidate_set-&gt;Empty()) → for_statement@474 i &lt; count_no_visited → if_statement@477 (not is_finite_distance(dist)) → if_statement@478 (is_result_distance_eligible&lt;mode&gt;(dist, inner_search_param) and (not is_id_allowed &#124;&#124; is_id_allowed-&gt;CheckValid(cur_id))) → if_statement@481 (mode == KNN_SEARCH) → if_statement@482 (top_candidates-&gt;Size() &gt; ef) | 当前参考未静态绑定；见下方边界说明 |

| L484 | iter_ctx-&gt;CheckPoint | while_statement@422 (not candidate_set-&gt;Empty()) → for_statement@474 i &lt; count_no_visited → if_statement@477 (not is_finite_distance(dist)) → if_statement@478 (is_result_distance_eligible&lt;mode&gt;(dist, inner_search_param) and (not is_id_allowed &#124;&#124; is_id_allowed-&gt;CheckValid(cur_id))) → if_statement@481 (mode == KNN_SEARCH) → if_statement@482 (top_candidates-&gt;Size() &gt; ef) → if_statement@484 (iter_ctx-&gt;CheckPoint(evicted.second)) | 当前参考未静态绑定；见下方边界说明 |

| L485 | iter_ctx-&gt;AddDiscardNode | while_statement@422 (not candidate_set-&gt;Empty()) → for_statement@474 i &lt; count_no_visited → if_statement@477 (not is_finite_distance(dist)) → if_statement@478 (is_result_distance_eligible&lt;mode&gt;(dist, inner_search_param) and (not is_id_allowed &#124;&#124; is_id_allowed-&gt;CheckValid(cur_id))) → if_statement@481 (mode == KNN_SEARCH) → if_statement@482 (top_candidates-&gt;Size() &gt; ef) → if_statement@484 (iter_ctx-&gt;CheckPoint(evicted.second)) | 当前参考未静态绑定；见下方边界说明 |

| L487 | top_candidates-&gt;Pop | while_statement@422 (not candidate_set-&gt;Empty()) → for_statement@474 i &lt; count_no_visited → if_statement@477 (not is_finite_distance(dist)) → if_statement@478 (is_result_distance_eligible&lt;mode&gt;(dist, inner_search_param) and (not is_id_allowed &#124;&#124; is_id_allowed-&gt;CheckValid(cur_id))) → if_statement@481 (mode == KNN_SEARCH) → if_statement@482 (top_candidates-&gt;Size() &gt; ef) | 当前参考未静态绑定；见下方边界说明 |

| L490 | top_candidates-&gt;Pop | while_statement@422 (not candidate_set-&gt;Empty()) → for_statement@474 i &lt; count_no_visited → if_statement@477 (not is_finite_distance(dist)) → if_statement@478 (is_result_distance_eligible&lt;mode&gt;(dist, inner_search_param) and (not is_id_allowed &#124;&#124; is_id_allowed-&gt;CheckValid(cur_id))) → if_statement@481 (mode == KNN_SEARCH) [else 分支] → if_statement@489 (dist &gt; inner_search_param.radius) | 当前参考未静态绑定；见下方边界说明 |

| L493 | iter_ctx-&gt;CheckPoint | while_statement@422 (not candidate_set-&gt;Empty()) → for_statement@474 i &lt; count_no_visited → if_statement@477 (not is_finite_distance(dist)) → if_statement@493 (iter_ctx-&gt;CheckPoint(cur_id)) | 当前参考未静态绑定；见下方边界说明 |

| L494 | candidate_set-&gt;Push | while_statement@422 (not candidate_set-&gt;Empty()) → for_statement@474 i &lt; count_no_visited → if_statement@477 (not is_finite_distance(dist)) → if_statement@493 (iter_ctx-&gt;CheckPoint(cur_id)) | 当前参考未静态绑定；见下方边界说明 |

| L494 | traversal_priority | while_statement@422 (not candidate_set-&gt;Empty()) → for_statement@474 i &lt; count_no_visited → if_statement@477 (not is_finite_distance(dist)) → if_statement@493 (iter_ctx-&gt;CheckPoint(cur_id)) | 当前参考未静态绑定；见下方边界说明 |

| L495 | flatten-&gt;Prefetch | while_statement@422 (not candidate_set-&gt;Empty()) → for_statement@474 i &lt; count_no_visited → if_statement@477 (not is_finite_distance(dist)) → if_statement@493 (iter_ctx-&gt;CheckPoint(cur_id)) | 当前参考未静态绑定；见下方边界说明 |

| L497 | top_candidates-&gt;Empty | while_statement@422 (not candidate_set-&gt;Empty()) → for_statement@474 i &lt; count_no_visited → if_statement@477 (not is_finite_distance(dist)) → if_statement@497 (not top_candidates-&gt;Empty()) | 当前参考未静态绑定；见下方边界说明 |

| L498 | top_candidates-&gt;Top | while_statement@422 (not candidate_set-&gt;Empty()) → for_statement@474 i &lt; count_no_visited → if_statement@477 (not is_finite_distance(dist)) → if_statement@497 (not top_candidates-&gt;Empty()) | 当前参考未静态绑定；见下方边界说明 |

| L502 | is_id_allowed-&gt;CheckValid | while_statement@422 (not candidate_set-&gt;Empty()) → for_statement@474 i &lt; count_no_visited | 当前参考未静态绑定；见下方边界说明 |

| L505 | iter_ctx-&gt;CheckPoint | while_statement@422 (not candidate_set-&gt;Empty()) → for_statement@474 i &lt; count_no_visited → if_statement@503 (mode == KNN_SEARCH) → if_statement@504 (collect_rabitq_lower_bound and lower_bound_dists[i] &lt; lower_bound and id_allowed and iter_ctx-&gt;CheckPoint(cur_id)) | 当前参考未静态绑定；见下方边界说明 |

| L506 | rabitq_lower_bound_candidates-&gt;emplace_back | while_statement@422 (not candidate_set-&gt;Empty()) → for_statement@474 i &lt; count_no_visited → if_statement@503 (mode == KNN_SEARCH) → if_statement@504 (collect_rabitq_lower_bound and lower_bound_dists[i] &lt; lower_bound and id_allowed and iter_ctx-&gt;CheckPoint(cur_id)) | 当前参考未静态绑定；见下方边界说明 |

| L509 | top_candidates-&gt;Size | while_statement@422 (not candidate_set-&gt;Empty()) → for_statement@474 i &lt; count_no_visited → if_statement@509 (top_candidates-&gt;Size() &lt; ef &#124;&#124; lower_bound &gt; dist &#124;&#124; (mode == RANGE_SEARCH && dist &lt;= inner_search_param.radius)) | 当前参考未静态绑定；见下方边界说明 |

| L511 | iter_ctx-&gt;CheckPoint | while_statement@422 (not candidate_set-&gt;Empty()) → for_statement@474 i &lt; count_no_visited → if_statement@509 (top_candidates-&gt;Size() &lt; ef &#124;&#124; lower_bound &gt; dist &#124;&#124; (mode == RANGE_SEARCH && dist &lt;= inner_search_param.radius)) → if_statement@511 (!iter_ctx-&gt;CheckPoint(cur_id)) | 当前参考未静态绑定；见下方边界说明 |

| L514 | candidate_set-&gt;Push | while_statement@422 (not candidate_set-&gt;Empty()) → for_statement@474 i &lt; count_no_visited → if_statement@509 (top_candidates-&gt;Size() &lt; ef &#124;&#124; lower_bound &gt; dist &#124;&#124; (mode == RANGE_SEARCH && dist &lt;= inner_search_param.radius)) | 当前参考未静态绑定；见下方边界说明 |

| L515 | flatten-&gt;Prefetch | while_statement@422 (not candidate_set-&gt;Empty()) → for_statement@474 i &lt; count_no_visited → if_statement@509 (top_candidates-&gt;Size() &lt; ef &#124;&#124; lower_bound &gt; dist &#124;&#124; (mode == RANGE_SEARCH && dist &lt;= inner_search_param.radius)) | 当前参考未静态绑定；见下方边界说明 |

| L515 | candidate_set-&gt;Top | while_statement@422 (not candidate_set-&gt;Empty()) → for_statement@474 i &lt; count_no_visited → if_statement@509 (top_candidates-&gt;Size() &lt; ef &#124;&#124; lower_bound &gt; dist &#124;&#124; (mode == RANGE_SEARCH && dist &lt;= inner_search_param.radius)) | 当前参考未静态绑定；见下方边界说明 |

| L517 | top_candidates-&gt;Push | while_statement@422 (not candidate_set-&gt;Empty()) → for_statement@474 i &lt; count_no_visited → if_statement@509 (top_candidates-&gt;Size() &lt; ef &#124;&#124; lower_bound &gt; dist &#124;&#124; (mode == RANGE_SEARCH && dist &lt;= inner_search_param.radius)) → if_statement@516 (id_allowed) | 当前参考未静态绑定；见下方边界说明 |

| L521 | top_candidates-&gt;Size | while_statement@422 (not candidate_set-&gt;Empty()) → for_statement@474 i &lt; count_no_visited → if_statement@509 (top_candidates-&gt;Size() &lt; ef &#124;&#124; lower_bound &gt; dist &#124;&#124; (mode == RANGE_SEARCH && dist &lt;= inner_search_param.radius)) → if_statement@520 (mode == KNN_SEARCH) → if_statement@521 (top_candidates-&gt;Size() &gt; ef) | 当前参考未静态绑定；见下方边界说明 |

| L522 | iter_ctx-&gt;CheckPoint | while_statement@422 (not candidate_set-&gt;Empty()) → for_statement@474 i &lt; count_no_visited → if_statement@509 (top_candidates-&gt;Size() &lt; ef &#124;&#124; lower_bound &gt; dist &#124;&#124; (mode == RANGE_SEARCH && dist &lt;= inner_search_param.radius)) → if_statement@520 (mode == KNN_SEARCH) → if_statement@521 (top_candidates-&gt;Size() &gt; ef) → if_statement@522 (iter_ctx-&gt;CheckPoint(top_candidates-&gt;Top().second)) | 当前参考未静态绑定；见下方边界说明 |

| L522 | top_candidates-&gt;Top | while_statement@422 (not candidate_set-&gt;Empty()) → for_statement@474 i &lt; count_no_visited → if_statement@509 (top_candidates-&gt;Size() &lt; ef &#124;&#124; lower_bound &gt; dist &#124;&#124; (mode == RANGE_SEARCH && dist &lt;= inner_search_param.radius)) → if_statement@520 (mode == KNN_SEARCH) → if_statement@521 (top_candidates-&gt;Size() &gt; ef) → if_statement@522 (iter_ctx-&gt;CheckPoint(top_candidates-&gt;Top().second)) | 当前参考未静态绑定；见下方边界说明 |

| L523 | top_candidates-&gt;Top | while_statement@422 (not candidate_set-&gt;Empty()) → for_statement@474 i &lt; count_no_visited → if_statement@509 (top_candidates-&gt;Size() &lt; ef &#124;&#124; lower_bound &gt; dist &#124;&#124; (mode == RANGE_SEARCH && dist &lt;= inner_search_param.radius)) → if_statement@520 (mode == KNN_SEARCH) → if_statement@521 (top_candidates-&gt;Size() &gt; ef) → if_statement@522 (iter_ctx-&gt;CheckPoint(top_candidates-&gt;Top().second)) | 当前参考未静态绑定；见下方边界说明 |

| L524 | iter_ctx-&gt;AddDiscardNode | while_statement@422 (not candidate_set-&gt;Empty()) → for_statement@474 i &lt; count_no_visited → if_statement@509 (top_candidates-&gt;Size() &lt; ef &#124;&#124; lower_bound &gt; dist &#124;&#124; (mode == RANGE_SEARCH && dist &lt;= inner_search_param.radius)) → if_statement@520 (mode == KNN_SEARCH) → if_statement@521 (top_candidates-&gt;Size() &gt; ef) → if_statement@522 (iter_ctx-&gt;CheckPoint(top_candidates-&gt;Top().second)) | 当前参考未静态绑定；见下方边界说明 |

| L526 | top_candidates-&gt;Pop | while_statement@422 (not candidate_set-&gt;Empty()) → for_statement@474 i &lt; count_no_visited → if_statement@509 (top_candidates-&gt;Size() &lt; ef &#124;&#124; lower_bound &gt; dist &#124;&#124; (mode == RANGE_SEARCH && dist &lt;= inner_search_param.radius)) → if_statement@520 (mode == KNN_SEARCH) → if_statement@521 (top_candidates-&gt;Size() &gt; ef) | 当前参考未静态绑定；见下方边界说明 |

| L530 | top_candidates-&gt;Empty | while_statement@422 (not candidate_set-&gt;Empty()) → for_statement@474 i &lt; count_no_visited → if_statement@509 (top_candidates-&gt;Size() &lt; ef &#124;&#124; lower_bound &gt; dist &#124;&#124; (mode == RANGE_SEARCH && dist &lt;= inner_search_param.radius)) → if_statement@530 (not top_candidates-&gt;Empty()) | 当前参考未静态绑定；见下方边界说明 |

| L531 | top_candidates-&gt;Top | while_statement@422 (not candidate_set-&gt;Empty()) → for_statement@474 i &lt; count_no_visited → if_statement@509 (top_candidates-&gt;Size() &lt; ef &#124;&#124; lower_bound &gt; dist &#124;&#124; (mode == RANGE_SEARCH && dist &lt;= inner_search_param.radius)) → if_statement@530 (not top_candidates-&gt;Empty()) | 当前参考未静态绑定；见下方边界说明 |

| L538 | top_candidates-&gt;Size | if_statement@537 (mode == KNN_SEARCH) → while_statement@538 (top_candidates-&gt;Size() &gt; inner_search_param.topk) | 当前参考未静态绑定；见下方边界说明 |

| L539 | top_candidates-&gt;Top | if_statement@537 (mode == KNN_SEARCH) → while_statement@538 (top_candidates-&gt;Size() &gt; inner_search_param.topk) | 当前参考未静态绑定；见下方边界说明 |

| L540 | iter_ctx-&gt;CheckPoint | if_statement@537 (mode == KNN_SEARCH) → while_statement@538 (top_candidates-&gt;Size() &gt; inner_search_param.topk) → if_statement@540 (iter_ctx-&gt;CheckPoint(cur_node_pair.second)) | 当前参考未静态绑定；见下方边界说明 |

| L541 | iter_ctx-&gt;AddDiscardNode | if_statement@537 (mode == KNN_SEARCH) → while_statement@538 (top_candidates-&gt;Size() &gt; inner_search_param.topk) → if_statement@540 (iter_ctx-&gt;CheckPoint(cur_node_pair.second)) | 当前参考未静态绑定；见下方边界说明 |

| L543 | top_candidates-&gt;Pop | if_statement@537 (mode == KNN_SEARCH) → while_statement@538 (top_candidates-&gt;Size() &gt; inner_search_param.topk) | 当前参考未静态绑定；见下方边界说明 |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L551"></a>

## `BasicSearcher::search_impl`

源码位置：`src/impl/searcher/basic_searcher.cpp:551–936`。

先从签名确认输入、返回值和 const/override，再按完整函数体的条件阅读调用点。下表保留了本函数的显式调用以及 lambda 中的调用；进入下层时用“候选实现”定位，未解析的对象由源码静态类型/运行时类型确认。

### 完整函数

```cpp
DistHeapPtr
BasicSearcher::search_impl(const GraphInterfacePtr& graph,
                           const FlattenInterfacePtr& flatten,
                           const VisitedListPtr& vl,
                           const void* query,
                           const InnerSearchParam& inner_search_param,
                           const LabelTablePtr& label_table,
                           QueryContext* ctx,
                           DistanceRecordVector* rabitq_lower_bound_candidates,
                           const ComputerInterfacePtr& preset_computer) const {
    // set customize query alloctor
    Allocator* alloc = select_query_allocator(ctx, allocator_);

    auto top_candidates = std::make_shared<StandardHeap<true, false>>(alloc, -1);
    auto candidate_set = std::make_shared<StandardHeap<true, false>>(alloc, -1);

    const bool use_custom_distance = inner_search_param.distance_batch_func != nullptr;
    if (not graph or (not flatten and not use_custom_distance)) {
        return top_candidates;
    }

    ComputerLease computer_lease;
    ComputerInterfacePtr computer = preset_computer;
    if (not use_custom_distance and computer == nullptr) {
        computer_lease = AcquireQueryComputer(flatten, query, ctx);
        computer = computer_lease.computer;
    }

    auto is_id_allowed = inner_search_param.is_inner_id_allowed;
    auto ep = inner_search_param.ep;
    auto ef = inner_search_param.ef;

    float dist = 0.0F;
    auto lower_bound = std::numeric_limits<float>::max();

    uint32_t hops = 0;
    uint32_t dist_cmp = 0;
    uint32_t count_no_visited = 0;
    Vector<InnerIdType> to_be_visited_id(graph->MaximumDegree(), alloc);
    Vector<InnerIdType> neighbors(graph->MaximumDegree(), alloc);
    Vector<float> line_dists(graph->MaximumDegree(), alloc);
    Vector<float> lower_bound_dists(graph->MaximumDegree(), alloc);
    const uint64_t custom_batch_capacity =
        use_custom_distance
            ? std::max<uint64_t>(1,
                                 std::min<uint64_t>(inner_search_param.distance_batch_size,
                                                    graph->MaximumDegree()))
            : 0;
    Vector<int64_t> custom_labels(custom_batch_capacity, alloc);
    auto skip_strategy = create_filter_search_skip_strategy(
        inner_search_param.skip_strategy_type,
        inner_search_param.is_inner_id_allowed != nullptr
            ? inner_search_param.is_inner_id_allowed->ValidRatio()
            : 1.0F,
        inner_search_param.skip_ratio);
    if (rabitq_lower_bound_candidates != nullptr) {
        rabitq_lower_bound_candidates->clear();
    }

    Filter* attr_ft = nullptr;
    if (not inner_search_param.executors.empty() and inner_search_param.executors[0] != nullptr) {
        inner_search_param.executors[0]->Clear();
        attr_ft = inner_search_param.executors[0]->Run();
    }

    auto check_func = [&is_id_allowed, &attr_ft](InnerIdType id) {
        return (is_id_allowed == nullptr or is_id_allowed->CheckValid(id)) and
               (attr_ft == nullptr or attr_ft->CheckValid(id));
    };
    auto* reasoning = ctx == nullptr ? nullptr : ctx->reasoning_ctx;

    auto score_ids = [&](const InnerIdType* ids, uint64_t count, float* scores) {
        if (not use_custom_distance) {
            flatten->Query(scores, computer, ids, count, ctx);
            return;
        }
        CHECK_ARGUMENT(label_table != nullptr, "custom distance requires a label table");
        CHECK_ARGUMENT(inner_search_param.distance_batch_size > 0,
                       "distance_batch_size must be greater than 0");
        for (uint64_t offset = 0; offset < count;
             offset += inner_search_param.distance_batch_size) {
            const uint64_t batch_count =
                std::min(inner_search_param.distance_batch_size, count - offset);
            for (uint64_t i = 0; i < batch_count; ++i) {
                custom_labels[i] = label_table->GetLabelById(ids[offset + i]);
            }
            inner_search_param.distance_batch_func(
                custom_labels.data(), batch_count, scores + offset);
            if (ctx != nullptr and ctx->stats != nullptr) {
                ctx->stats->AddDistance(
                    ctx->distance_phase, DistanceEvaluationBackend::UNKNOWN, batch_count);
            }
            for (uint64_t i = 0; i < batch_count; ++i) {
                CHECK_ARGUMENT(is_finite_distance(scores[offset + i]),
                               "distance callback must return finite scores");
            }
        }
    };
    auto score_duplicates = [&](const auto& duplicate_ids, uint32_t duplicate_hops) {
        if (not use_custom_distance) {
            return;
        }

        uint64_t duplicate_count = 0;
        auto submit_duplicates = [&]() {
            if (duplicate_count == 0) {
                return;
            }
            score_ids(neighbors.data(), duplicate_count, lower_bound_dists.data());
            dist_cmp += duplicate_count;
            for (uint64_t i = 0; i < duplicate_count; ++i) {
                if (reasoning != nullptr) {
                    reasoning->RecordVisit(neighbors[i], lower_bound_dists[i], duplicate_hops);
                }
                top_candidates->Push(lower_bound_dists[i], neighbors[i]);
            }
            duplicate_count = 0;
        };

        for (const auto& item : duplicate_ids) {
            if (not check_func(item)) {
                continue;
            }
            neighbors[duplicate_count++] = item;
            if (duplicate_count == neighbors.size()) {
                submit_duplicates();
            }
        }
        submit_duplicates();

        if constexpr (mode == KNN_SEARCH) {
            while (top_candidates->Size() > ef) {
                if (reasoning != nullptr) {
                    reasoning->RecordEviction(top_candidates->Top().second, duplicate_hops);
                }
                top_candidates->Pop();
            }
        }
        if (not top_candidates->Empty()) {
            lower_bound = top_candidates->Top().first;
        }
    };

    if (use_custom_distance) {
        score_ids(&ep, 1, &dist);
    } else if (inner_search_param.enable_rabitq_one_bit_search) {
        flatten->QueryWithDistanceLowerBound(&dist, nullptr, computer, &ep, 1, ctx);
    } else {
        flatten->Query(&dist, computer, &ep, 1, ctx);
    }
    ++dist_cmp;
    if (check_func(ep) and is_result_distance_eligible<mode>(dist, inner_search_param)) {
        top_candidates->Push(dist, ep);
    }
    if (not is_finite_distance(dist) and inner_search_param.consider_duplicate and
        not use_custom_distance and is_result_distance_eligible<mode>(dist, inner_search_param)) {
        for (const auto duplicate_id : graph->GetDuplicateIds(ep)) {
            if (check_func(duplicate_id)) {
                top_candidates->Push(dist, duplicate_id);
            }
        }
        if constexpr (mode == KNN_SEARCH) {
            while (top_candidates->Size() > ef) {
                top_candidates->Pop();
            }
        }
    }
    if constexpr (mode == InnerSearchMode::RANGE_SEARCH) {
        while (dist > inner_search_param.radius and not top_candidates->Empty()) {
            top_candidates->Pop();
        }
    }
    if (not top_candidates->Empty()) {
        lower_bound = top_candidates->Top().first;
    }
    if (use_custom_distance and inner_search_param.consider_duplicate) {
        const auto duplicate_ids = graph->GetDuplicateIds(ep);
        score_duplicates(duplicate_ids, hops);
    }
    candidate_set->Push(traversal_priority(dist), ep);
    vl->Set(ep);

    while (not candidate_set->Empty()) {
        ++hops;
        if (hops >= inner_search_param.hops_limit) {
            if (reasoning != nullptr) {
                reasoning->SetTermination(ReasoningContext::kTerminationHopsLimitReached);
            }
            break;
        }
        if (reasoning != nullptr) {
            reasoning->AddSearchHop();
        }
        auto current_node_pair = candidate_set->Top();

        if (inner_search_param.time_cost != nullptr and
            inner_search_param.time_cost->CheckOvertime()) {
            if (ctx != nullptr and ctx->stats != nullptr) {
                ctx->stats->is_timeout.store(true, std::memory_order_relaxed);
            }
            if (reasoning != nullptr) {
                reasoning->SetTermination(ReasoningContext::kTerminationTimeout);
            }
            break;
        }

        if constexpr (mode == InnerSearchMode::KNN_SEARCH) {
            if ((-current_node_pair.first) > lower_bound && top_candidates->Size() >= ef) {
                if (reasoning != nullptr) {
                    reasoning->SetTermination(ReasoningContext::kTerminationLowerBoundReached);
                }
                break;
            }
        }
        candidate_set->Pop();

        if (not candidate_set->Empty()) {
            graph->Prefetch(candidate_set->Top().second, 0);
        }

        count_no_visited = visit(graph,
                                 vl,
                                 current_node_pair,
                                 inner_search_param.is_inner_id_allowed,
                                 skip_strategy.get(),
                                 to_be_visited_id,
                                 neighbors);

        bool collect_rabitq_lower_bound = false;
        if (use_custom_distance) {
            score_ids(to_be_visited_id.data(), count_no_visited, line_dists.data());
        } else if (inner_search_param.enable_rabitq_one_bit_search and
                   top_candidates->Size() == ef and rabitq_lower_bound_candidates != nullptr) {
            collect_rabitq_lower_bound = true;
            flatten->QueryWithDistanceLowerBound(line_dists.data(),
                                                 lower_bound_dists.data(),
                                                 computer,
                                                 to_be_visited_id.data(),
                                                 count_no_visited,
                                                 ctx);
        } else if (inner_search_param.enable_rabitq_one_bit_search) {
            flatten->QueryWithDistanceLowerBound(line_dists.data(),
                                                 nullptr,
                                                 computer,
                                                 to_be_visited_id.data(),
                                                 count_no_visited,
                                                 ctx);
        } else {
            flatten->Query(
                line_dists.data(), computer, to_be_visited_id.data(), count_no_visited, ctx);
        }
        dist_cmp += count_no_visited;

        for (uint32_t i = 0; i < count_no_visited; i++) {
            dist = line_dists[i];
            const auto cur_id = to_be_visited_id[i];
            if (reasoning != nullptr) {
                reasoning->RecordVisit(cur_id, dist, hops);
            }
            if (use_custom_distance and inner_search_param.consider_duplicate) {
                const auto duplicate_ids = graph->GetDuplicateIds(cur_id);
                score_duplicates(duplicate_ids, hops);
            }
            if (not is_finite_distance(dist)) {
                candidate_set->Push(traversal_priority(dist), cur_id);
                auto push_result = [&](InnerIdType result_id) {
                    if (not is_result_distance_eligible<mode>(dist, inner_search_param) or
                        not check_func(result_id)) {
                        return;
                    }
                    top_candidates->Push(dist, result_id);
                    if constexpr (mode == KNN_SEARCH) {
                        while (top_candidates->Size() > ef) {
                            if (reasoning != nullptr) {
                                reasoning->RecordEviction(top_candidates->Top().second, hops);
                            }
                            top_candidates->Pop();
                        }
                    } else if (dist > inner_search_param.radius) {
                        top_candidates->Pop();
                    }
                };
                push_result(cur_id);
                if (inner_search_param.consider_duplicate and not use_custom_distance) {
                    for (const auto duplicate_id : graph->GetDuplicateIds(cur_id)) {
                        push_result(duplicate_id);
                    }
                }
                if (not top_candidates->Empty()) {
                    lower_bound = top_candidates->Top().first;
                }
                continue;
            }
            if constexpr (mode == KNN_SEARCH) {
                if (collect_rabitq_lower_bound and lower_bound_dists[i] < lower_bound and
                    check_func(cur_id)) {
                    rabitq_lower_bound_candidates->emplace_back(lower_bound_dists[i], cur_id);
                }
            }
            if (top_candidates->Size() < ef || lower_bound > dist ||
                (mode == RANGE_SEARCH && dist <= inner_search_param.radius)) {
                candidate_set->Push(-dist, cur_id);
                //                flatten->Prefetch(candidate_set->Top().second);
                if (check_func(cur_id)) {
                    top_candidates->Push(dist, cur_id);
                } else if (reasoning != nullptr) {
                    reasoning->RecordFilterReject(cur_id);
                }
                if (inner_search_param.consider_duplicate and not use_custom_distance) {
                    const auto duplicate_ids = graph->GetDuplicateIds(cur_id);
                    for (const auto& item : duplicate_ids) {
                        if (check_func(item)) {
                            top_candidates->Push(dist, item);
                        }
                    }
                }

                if constexpr (mode == KNN_SEARCH) {
                    if (top_candidates->Size() > ef) {
                        if (reasoning != nullptr) {
                            reasoning->RecordEviction(top_candidates->Top().second, hops);
                        }
                        top_candidates->Pop();
                    }
                }

                if (not top_candidates->Empty()) {
                    lower_bound = top_candidates->Top().first;
                }
            }
        }
    }

    if constexpr (mode == KNN_SEARCH) {
        while (top_candidates->Size() > inner_search_param.topk) {
            top_candidates->Pop();
        }
    } else if constexpr (mode == RANGE_SEARCH) {
        if (inner_search_param.range_search_limit_size > 0) {
            while (top_candidates->Size() > inner_search_param.range_search_limit_size) {
                top_candidates->Pop();
            }
        }
        while (not top_candidates->Empty() &&
               top_candidates->Top().first > inner_search_param.radius + THRESHOLD_ERROR) {
            top_candidates->Pop();
        }
    }

    // set duplicate id for query vector
    if (not use_custom_distance and inner_search_param.find_duplicate and
        not top_candidates->Empty()) {
        const auto* data = top_candidates->GetData();
        auto min_distance = data[0].first;
        auto min_index = data[0].second;
        for (uint32_t i = 1; i < top_candidates->Size(); ++i) {
            if (data[i].first < min_distance) {
                min_distance = data[i].first;
                min_index = data[i].second;
            }
        }
        if (inner_search_param.duplicate_distance_threshold > 0.0F) {
            if (min_distance <= inner_search_param.duplicate_distance_threshold) {
                inner_search_param.duplicate_id = min_index;
            }
        } else {
            const bool has_stored_query =
                inner_search_param.duplicate_query_id < flatten->TotalCount();
            const bool is_duplicate =
                has_stored_query
                    ? flatten->CompareVectors(inner_search_param.duplicate_query_id, min_index)
                    : flatten->CompareRawVectorWithId(query, min_index);
            if (is_duplicate) {
                inner_search_param.duplicate_id = min_index;
            }
        }
    }

    if (ctx != nullptr and ctx->stats != nullptr) {
        auto& stats = *ctx->stats;
        stats.dist_cmp.fetch_add(dist_cmp, std::memory_order_relaxed);
        stats.hops.fetch_add(hops, std::memory_order_relaxed);
    }

    return top_candidates;
}
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L562 | select_query_allocator | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L564 | std::make_shared&lt;StandardHeap&lt;true, false&gt;&gt; | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L565 | std::make_shared&lt;StandardHeap&lt;true, false&gt;&gt; | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L575 | AcquireQueryComputer | if_statement@574 (not use_custom_distance and computer == nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L584 | std::numeric_limits&lt;float&gt;::max | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L589 | graph-&gt;MaximumDegree | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L590 | graph-&gt;MaximumDegree | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L591 | graph-&gt;MaximumDegree | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L592 | graph-&gt;MaximumDegree | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L595 | std::max&lt;uint64_t&gt; | conditional_expression@594 use_custom_distance | 当前参考未静态绑定；见下方边界说明 |

| L596 | std::min&lt;uint64_t&gt; | conditional_expression@594 use_custom_distance | 当前参考未静态绑定；见下方边界说明 |

| L597 | graph-&gt;MaximumDegree | conditional_expression@594 use_custom_distance | 当前参考未静态绑定；见下方边界说明 |

| L600 | create_filter_search_skip_strategy | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L603 | inner_search_param.is_inner_id_allowed-&gt;ValidRatio | conditional_expression@602 inner_search_param.is_inner_id_allowed != nullptr | 当前参考未静态绑定；见下方边界说明 |

| L607 | rabitq_lower_bound_candidates-&gt;clear | if_statement@606 (rabitq_lower_bound_candidates != nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L611 | inner_search_param.executors.empty | if_statement@611 (not inner_search_param.executors.empty() and inner_search_param.executors[0] != nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L612 | inner_search_param.executors[0]-&gt;Clear | if_statement@611 (not inner_search_param.executors.empty() and inner_search_param.executors[0] != nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L613 | inner_search_param.executors[0]-&gt;Run | if_statement@611 (not inner_search_param.executors.empty() and inner_search_param.executors[0] != nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L617 | is_id_allowed-&gt;CheckValid | lambda@616（定义体，执行时间取决于调用/调度） | 当前参考未静态绑定；见下方边界说明 |

| L618 | attr_ft-&gt;CheckValid | lambda@616（定义体，执行时间取决于调用/调度） | 当前参考未静态绑定；见下方边界说明 |

| L624 | flatten-&gt;Query | lambda@622（定义体，执行时间取决于调用/调度） → if_statement@623 (not use_custom_distance) | 当前参考未静态绑定；见下方边界说明 |

| L627 | CHECK_ARGUMENT | lambda@622（定义体，执行时间取决于调用/调度） | 当前参考未静态绑定；见下方边界说明 |

| L628 | CHECK_ARGUMENT | lambda@622（定义体，执行时间取决于调用/调度） | 当前参考未静态绑定；见下方边界说明 |

| L633 | std::min | lambda@622（定义体，执行时间取决于调用/调度） → for_statement@630 offset &lt; count | 当前参考未静态绑定；见下方边界说明 |

| L635 | label_table-&gt;GetLabelById | lambda@622（定义体，执行时间取决于调用/调度） → for_statement@630 offset &lt; count → for_statement@634 i &lt; batch_count | 当前参考未静态绑定；见下方边界说明 |

| L637 | inner_search_param.distance_batch_func | lambda@622（定义体，执行时间取决于调用/调度） → for_statement@630 offset &lt; count | 当前参考未静态绑定；见下方边界说明 |

| L638 | custom_labels.data | lambda@622（定义体，执行时间取决于调用/调度） → for_statement@630 offset &lt; count | 当前参考未静态绑定；见下方边界说明 |

| L640 | ctx-&gt;stats-&gt;AddDistance | lambda@622（定义体，执行时间取决于调用/调度） → for_statement@630 offset &lt; count → if_statement@639 (ctx != nullptr and ctx-&gt;stats != nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L644 | CHECK_ARGUMENT | lambda@622（定义体，执行时间取决于调用/调度） → for_statement@630 offset &lt; count → for_statement@643 i &lt; batch_count | 当前参考未静态绑定；见下方边界说明 |

| L644 | is_finite_distance | lambda@622（定义体，执行时间取决于调用/调度） → for_statement@630 offset &lt; count → for_statement@643 i &lt; batch_count | 当前参考未静态绑定；见下方边界说明 |

| L659 | score_ids | lambda@649（定义体，执行时间取决于调用/调度） → lambda@655（定义体，执行时间取决于调用/调度） | 当前参考未静态绑定；见下方边界说明 |

| L659 | neighbors.data | lambda@649（定义体，执行时间取决于调用/调度） → lambda@655（定义体，执行时间取决于调用/调度） | 当前参考未静态绑定；见下方边界说明 |

| L659 | lower_bound_dists.data | lambda@649（定义体，执行时间取决于调用/调度） → lambda@655（定义体，执行时间取决于调用/调度） | 当前参考未静态绑定；见下方边界说明 |

| L663 | reasoning-&gt;RecordVisit | lambda@649（定义体，执行时间取决于调用/调度） → lambda@655（定义体，执行时间取决于调用/调度） → for_statement@661 i &lt; duplicate_count → if_statement@662 (reasoning != nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L665 | top_candidates-&gt;Push | lambda@649（定义体，执行时间取决于调用/调度） → lambda@655（定义体，执行时间取决于调用/调度） → for_statement@661 i &lt; duplicate_count | 当前参考未静态绑定；见下方边界说明 |

| L671 | check_func | lambda@649（定义体，执行时间取决于调用/调度） → for_range_loop@670 → if_statement@671 (not check_func(item)) | 当前参考未静态绑定；见下方边界说明 |

| L675 | neighbors.size | lambda@649（定义体，执行时间取决于调用/调度） → for_range_loop@670 → if_statement@675 (duplicate_count == neighbors.size()) | 当前参考未静态绑定；见下方边界说明 |

| L676 | submit_duplicates | lambda@649（定义体，执行时间取决于调用/调度） → for_range_loop@670 → if_statement@675 (duplicate_count == neighbors.size()) | 当前参考未静态绑定；见下方边界说明 |

| L679 | submit_duplicates | lambda@649（定义体，执行时间取决于调用/调度） | 当前参考未静态绑定；见下方边界说明 |

| L682 | top_candidates-&gt;Size | lambda@649（定义体，执行时间取决于调用/调度） → if_statement@681 (mode == KNN_SEARCH) → while_statement@682 (top_candidates-&gt;Size() &gt; ef) | 当前参考未静态绑定；见下方边界说明 |

| L684 | reasoning-&gt;RecordEviction | lambda@649（定义体，执行时间取决于调用/调度） → if_statement@681 (mode == KNN_SEARCH) → while_statement@682 (top_candidates-&gt;Size() &gt; ef) → if_statement@683 (reasoning != nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L684 | top_candidates-&gt;Top | lambda@649（定义体，执行时间取决于调用/调度） → if_statement@681 (mode == KNN_SEARCH) → while_statement@682 (top_candidates-&gt;Size() &gt; ef) → if_statement@683 (reasoning != nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L686 | top_candidates-&gt;Pop | lambda@649（定义体，执行时间取决于调用/调度） → if_statement@681 (mode == KNN_SEARCH) → while_statement@682 (top_candidates-&gt;Size() &gt; ef) | 当前参考未静态绑定；见下方边界说明 |

| L689 | top_candidates-&gt;Empty | lambda@649（定义体，执行时间取决于调用/调度） → if_statement@689 (not top_candidates-&gt;Empty()) | 当前参考未静态绑定；见下方边界说明 |

| L690 | top_candidates-&gt;Top | lambda@649（定义体，执行时间取决于调用/调度） → if_statement@689 (not top_candidates-&gt;Empty()) | 当前参考未静态绑定；见下方边界说明 |

| L695 | score_ids | if_statement@694 (use_custom_distance) | 当前参考未静态绑定；见下方边界说明 |

| L697 | flatten-&gt;QueryWithDistanceLowerBound | if_statement@694 (use_custom_distance) [else 分支] → if_statement@696 (inner_search_param.enable_rabitq_one_bit_search) | 当前参考未静态绑定；见下方边界说明 |

| L699 | flatten-&gt;Query | if_statement@694 (use_custom_distance) [else 分支] → if_statement@696 (inner_search_param.enable_rabitq_one_bit_search) [else 分支] | 当前参考未静态绑定；见下方边界说明 |

| L702 | check_func | if_statement@702 (check_func(ep) and is_result_distance_eligible&lt;mode&gt;(dist, inner_search_param)) | 当前参考未静态绑定；见下方边界说明 |

| L702 | is_result_distance_eligible&lt;mode&gt; | if_statement@702 (check_func(ep) and is_result_distance_eligible&lt;mode&gt;(dist, inner_search_param)) | 当前参考未静态绑定；见下方边界说明 |

| L703 | top_candidates-&gt;Push | if_statement@702 (check_func(ep) and is_result_distance_eligible&lt;mode&gt;(dist, inner_search_param)) | 当前参考未静态绑定；见下方边界说明 |

| L705 | is_finite_distance | if_statement@705 (not is_finite_distance(dist) and inner_search_param.consider_duplicate and not use_custom_distance and is_result_distance_eligible&lt;mode&gt;(dist, inner_search_param)) | 当前参考未静态绑定；见下方边界说明 |

| L706 | is_result_distance_eligible&lt;mode&gt; | if_statement@705 (not is_finite_distance(dist) and inner_search_param.consider_duplicate and not use_custom_distance and is_result_distance_eligible&lt;mode&gt;(dist, inner_search_param)) | 当前参考未静态绑定；见下方边界说明 |

| L707 | graph-&gt;GetDuplicateIds | if_statement@705 (not is_finite_distance(dist) and inner_search_param.consider_duplicate and not use_custom_distance and is_result_distance_eligible&lt;mode&gt;(dist, inner_search_param)) → for_range_loop@707 | 当前参考未静态绑定；见下方边界说明 |

| L708 | check_func | if_statement@705 (not is_finite_distance(dist) and inner_search_param.consider_duplicate and not use_custom_distance and is_result_distance_eligible&lt;mode&gt;(dist, inner_search_param)) → for_range_loop@707 → if_statement@708 (check_func(duplicate_id)) | 当前参考未静态绑定；见下方边界说明 |

| L709 | top_candidates-&gt;Push | if_statement@705 (not is_finite_distance(dist) and inner_search_param.consider_duplicate and not use_custom_distance and is_result_distance_eligible&lt;mode&gt;(dist, inner_search_param)) → for_range_loop@707 → if_statement@708 (check_func(duplicate_id)) | 当前参考未静态绑定；见下方边界说明 |

| L713 | top_candidates-&gt;Size | if_statement@705 (not is_finite_distance(dist) and inner_search_param.consider_duplicate and not use_custom_distance and is_result_distance_eligible&lt;mode&gt;(dist, inner_search_param)) → if_statement@712 (mode == KNN_SEARCH) → while_statement@713 (top_candidates-&gt;Size() &gt; ef) | 当前参考未静态绑定；见下方边界说明 |

| L714 | top_candidates-&gt;Pop | if_statement@705 (not is_finite_distance(dist) and inner_search_param.consider_duplicate and not use_custom_distance and is_result_distance_eligible&lt;mode&gt;(dist, inner_search_param)) → if_statement@712 (mode == KNN_SEARCH) → while_statement@713 (top_candidates-&gt;Size() &gt; ef) | 当前参考未静态绑定；见下方边界说明 |

| L719 | top_candidates-&gt;Empty | if_statement@718 (mode == InnerSearchMode::RANGE_SEARCH) → while_statement@719 (dist &gt; inner_search_param.radius and not top_candidates-&gt;Empty()) | 当前参考未静态绑定；见下方边界说明 |

| L720 | top_candidates-&gt;Pop | if_statement@718 (mode == InnerSearchMode::RANGE_SEARCH) → while_statement@719 (dist &gt; inner_search_param.radius and not top_candidates-&gt;Empty()) | 当前参考未静态绑定；见下方边界说明 |

| L723 | top_candidates-&gt;Empty | if_statement@723 (not top_candidates-&gt;Empty()) | 当前参考未静态绑定；见下方边界说明 |

| L724 | top_candidates-&gt;Top | if_statement@723 (not top_candidates-&gt;Empty()) | 当前参考未静态绑定；见下方边界说明 |

| L727 | graph-&gt;GetDuplicateIds | if_statement@726 (use_custom_distance and inner_search_param.consider_duplicate) | 当前参考未静态绑定；见下方边界说明 |

| L728 | score_duplicates | if_statement@726 (use_custom_distance and inner_search_param.consider_duplicate) | 当前参考未静态绑定；见下方边界说明 |

| L730 | candidate_set-&gt;Push | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L730 | traversal_priority | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L731 | vl-&gt;Set | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L733 | candidate_set-&gt;Empty | while_statement@733 (not candidate_set-&gt;Empty()) | 当前参考未静态绑定；见下方边界说明 |

| L737 | reasoning-&gt;SetTermination | while_statement@733 (not candidate_set-&gt;Empty()) → if_statement@735 (hops &gt;= inner_search_param.hops_limit) → if_statement@736 (reasoning != nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L742 | reasoning-&gt;AddSearchHop | while_statement@733 (not candidate_set-&gt;Empty()) → if_statement@741 (reasoning != nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L744 | candidate_set-&gt;Top | while_statement@733 (not candidate_set-&gt;Empty()) | 当前参考未静态绑定；见下方边界说明 |

| L747 | inner_search_param.time_cost-&gt;CheckOvertime | while_statement@733 (not candidate_set-&gt;Empty()) → if_statement@746 (inner_search_param.time_cost != nullptr and inner_search_param.time_cost-&gt;CheckOvertime()) | 当前参考未静态绑定；见下方边界说明 |

| L749 | ctx-&gt;stats-&gt;is_timeout.store | while_statement@733 (not candidate_set-&gt;Empty()) → if_statement@746 (inner_search_param.time_cost != nullptr and inner_search_param.time_cost-&gt;CheckOvertime()) → if_statement@748 (ctx != nullptr and ctx-&gt;stats != nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L752 | reasoning-&gt;SetTermination | while_statement@733 (not candidate_set-&gt;Empty()) → if_statement@746 (inner_search_param.time_cost != nullptr and inner_search_param.time_cost-&gt;CheckOvertime()) → if_statement@751 (reasoning != nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L758 | top_candidates-&gt;Size | while_statement@733 (not candidate_set-&gt;Empty()) → if_statement@757 (mode == InnerSearchMode::KNN_SEARCH) → if_statement@758 ((-current_node_pair.first) &gt; lower_bound && top_candidates-&gt;Size() &gt;= ef) | 当前参考未静态绑定；见下方边界说明 |

| L760 | reasoning-&gt;SetTermination | while_statement@733 (not candidate_set-&gt;Empty()) → if_statement@757 (mode == InnerSearchMode::KNN_SEARCH) → if_statement@758 ((-current_node_pair.first) &gt; lower_bound && top_candidates-&gt;Size() &gt;= ef) → if_statement@759 (reasoning != nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L765 | candidate_set-&gt;Pop | while_statement@733 (not candidate_set-&gt;Empty()) | 当前参考未静态绑定；见下方边界说明 |

| L767 | candidate_set-&gt;Empty | while_statement@733 (not candidate_set-&gt;Empty()) → if_statement@767 (not candidate_set-&gt;Empty()) | 当前参考未静态绑定；见下方边界说明 |

| L768 | graph-&gt;Prefetch | while_statement@733 (not candidate_set-&gt;Empty()) → if_statement@767 (not candidate_set-&gt;Empty()) | 当前参考未静态绑定；见下方边界说明 |

| L768 | candidate_set-&gt;Top | while_statement@733 (not candidate_set-&gt;Empty()) → if_statement@767 (not candidate_set-&gt;Empty()) | 当前参考未静态绑定；见下方边界说明 |

| L771 | visit | while_statement@733 (not candidate_set-&gt;Empty()) | [BasicSearcher::visit · L43](basic_searcher.md#L43) |

| L775 | skip_strategy.get | while_statement@733 (not candidate_set-&gt;Empty()) | 当前参考未静态绑定；见下方边界说明 |

| L781 | score_ids | while_statement@733 (not candidate_set-&gt;Empty()) → if_statement@780 (use_custom_distance) | 当前参考未静态绑定；见下方边界说明 |

| L781 | to_be_visited_id.data | while_statement@733 (not candidate_set-&gt;Empty()) → if_statement@780 (use_custom_distance) | 当前参考未静态绑定；见下方边界说明 |

| L781 | line_dists.data | while_statement@733 (not candidate_set-&gt;Empty()) → if_statement@780 (use_custom_distance) | 当前参考未静态绑定；见下方边界说明 |

| L783 | top_candidates-&gt;Size | while_statement@733 (not candidate_set-&gt;Empty()) → if_statement@780 (use_custom_distance) [else 分支] → if_statement@782 (inner_search_param.enable_rabitq_one_bit_search and top_candidates-&gt;Size() == ef and rabitq_lower_bound_candidates != nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L785 | flatten-&gt;QueryWithDistanceLowerBound | while_statement@733 (not candidate_set-&gt;Empty()) → if_statement@780 (use_custom_distance) [else 分支] → if_statement@782 (inner_search_param.enable_rabitq_one_bit_search and top_candidates-&gt;Size() == ef and rabitq_lower_bound_candidates != nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L785 | line_dists.data | while_statement@733 (not candidate_set-&gt;Empty()) → if_statement@780 (use_custom_distance) [else 分支] → if_statement@782 (inner_search_param.enable_rabitq_one_bit_search and top_candidates-&gt;Size() == ef and rabitq_lower_bound_candidates != nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L786 | lower_bound_dists.data | while_statement@733 (not candidate_set-&gt;Empty()) → if_statement@780 (use_custom_distance) [else 分支] → if_statement@782 (inner_search_param.enable_rabitq_one_bit_search and top_candidates-&gt;Size() == ef and rabitq_lower_bound_candidates != nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L788 | to_be_visited_id.data | while_statement@733 (not candidate_set-&gt;Empty()) → if_statement@780 (use_custom_distance) [else 分支] → if_statement@782 (inner_search_param.enable_rabitq_one_bit_search and top_candidates-&gt;Size() == ef and rabitq_lower_bound_candidates != nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L792 | flatten-&gt;QueryWithDistanceLowerBound | while_statement@733 (not candidate_set-&gt;Empty()) → if_statement@780 (use_custom_distance) [else 分支] → if_statement@782 (inner_search_param.enable_rabitq_one_bit_search and top_candidates-&gt;Size() == ef and rabitq_lower_bound_candidates != nullptr) [else 分支] → if_statement@791 (inner_search_param.enable_rabitq_one_bit_search) | 当前参考未静态绑定；见下方边界说明 |

| L792 | line_dists.data | while_statement@733 (not candidate_set-&gt;Empty()) → if_statement@780 (use_custom_distance) [else 分支] → if_statement@782 (inner_search_param.enable_rabitq_one_bit_search and top_candidates-&gt;Size() == ef and rabitq_lower_bound_candidates != nullptr) [else 分支] → if_statement@791 (inner_search_param.enable_rabitq_one_bit_search) | 当前参考未静态绑定；见下方边界说明 |

| L795 | to_be_visited_id.data | while_statement@733 (not candidate_set-&gt;Empty()) → if_statement@780 (use_custom_distance) [else 分支] → if_statement@782 (inner_search_param.enable_rabitq_one_bit_search and top_candidates-&gt;Size() == ef and rabitq_lower_bound_candidates != nullptr) [else 分支] → if_statement@791 (inner_search_param.enable_rabitq_one_bit_search) | 当前参考未静态绑定；见下方边界说明 |

| L799 | flatten-&gt;Query | while_statement@733 (not candidate_set-&gt;Empty()) → if_statement@780 (use_custom_distance) [else 分支] → if_statement@782 (inner_search_param.enable_rabitq_one_bit_search and top_candidates-&gt;Size() == ef and rabitq_lower_bound_candidates != nullptr) [else 分支] → if_statement@791 (inner_search_param.enable_rabitq_one_bit_search) [else 分支] | 当前参考未静态绑定；见下方边界说明 |

| L800 | line_dists.data | while_statement@733 (not candidate_set-&gt;Empty()) → if_statement@780 (use_custom_distance) [else 分支] → if_statement@782 (inner_search_param.enable_rabitq_one_bit_search and top_candidates-&gt;Size() == ef and rabitq_lower_bound_candidates != nullptr) [else 分支] → if_statement@791 (inner_search_param.enable_rabitq_one_bit_search) [else 分支] | 当前参考未静态绑定；见下方边界说明 |

| L800 | to_be_visited_id.data | while_statement@733 (not candidate_set-&gt;Empty()) → if_statement@780 (use_custom_distance) [else 分支] → if_statement@782 (inner_search_param.enable_rabitq_one_bit_search and top_candidates-&gt;Size() == ef and rabitq_lower_bound_candidates != nullptr) [else 分支] → if_statement@791 (inner_search_param.enable_rabitq_one_bit_search) [else 分支] | 当前参考未静态绑定；见下方边界说明 |

| L808 | reasoning-&gt;RecordVisit | while_statement@733 (not candidate_set-&gt;Empty()) → for_statement@804 i &lt; count_no_visited → if_statement@807 (reasoning != nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L811 | graph-&gt;GetDuplicateIds | while_statement@733 (not candidate_set-&gt;Empty()) → for_statement@804 i &lt; count_no_visited → if_statement@810 (use_custom_distance and inner_search_param.consider_duplicate) | 当前参考未静态绑定；见下方边界说明 |

| L812 | score_duplicates | while_statement@733 (not candidate_set-&gt;Empty()) → for_statement@804 i &lt; count_no_visited → if_statement@810 (use_custom_distance and inner_search_param.consider_duplicate) | 当前参考未静态绑定；见下方边界说明 |

| L814 | is_finite_distance | while_statement@733 (not candidate_set-&gt;Empty()) → for_statement@804 i &lt; count_no_visited → if_statement@814 (not is_finite_distance(dist)) | 当前参考未静态绑定；见下方边界说明 |

| L815 | candidate_set-&gt;Push | while_statement@733 (not candidate_set-&gt;Empty()) → for_statement@804 i &lt; count_no_visited → if_statement@814 (not is_finite_distance(dist)) | 当前参考未静态绑定；见下方边界说明 |

| L815 | traversal_priority | while_statement@733 (not candidate_set-&gt;Empty()) → for_statement@804 i &lt; count_no_visited → if_statement@814 (not is_finite_distance(dist)) | 当前参考未静态绑定；见下方边界说明 |

| L817 | is_result_distance_eligible&lt;mode&gt; | while_statement@733 (not candidate_set-&gt;Empty()) → for_statement@804 i &lt; count_no_visited → if_statement@814 (not is_finite_distance(dist)) → lambda@816（定义体，执行时间取决于调用/调度） → if_statement@817 (not is_result_distance_eligible&lt;mode&gt;(dist, inner_search_param) or not check_func(result_id)) | 当前参考未静态绑定；见下方边界说明 |

| L818 | check_func | while_statement@733 (not candidate_set-&gt;Empty()) → for_statement@804 i &lt; count_no_visited → if_statement@814 (not is_finite_distance(dist)) → lambda@816（定义体，执行时间取决于调用/调度） → if_statement@817 (not is_result_distance_eligible&lt;mode&gt;(dist, inner_search_param) or not check_func(result_id)) | 当前参考未静态绑定；见下方边界说明 |

| L821 | top_candidates-&gt;Push | while_statement@733 (not candidate_set-&gt;Empty()) → for_statement@804 i &lt; count_no_visited → if_statement@814 (not is_finite_distance(dist)) → lambda@816（定义体，执行时间取决于调用/调度） | 当前参考未静态绑定；见下方边界说明 |

| L823 | top_candidates-&gt;Size | while_statement@733 (not candidate_set-&gt;Empty()) → for_statement@804 i &lt; count_no_visited → if_statement@814 (not is_finite_distance(dist)) → lambda@816（定义体，执行时间取决于调用/调度） → if_statement@822 (mode == KNN_SEARCH) → while_statement@823 (top_candidates-&gt;Size() &gt; ef) | 当前参考未静态绑定；见下方边界说明 |

| L825 | reasoning-&gt;RecordEviction | while_statement@733 (not candidate_set-&gt;Empty()) → for_statement@804 i &lt; count_no_visited → if_statement@814 (not is_finite_distance(dist)) → lambda@816（定义体，执行时间取决于调用/调度） → if_statement@822 (mode == KNN_SEARCH) → while_statement@823 (top_candidates-&gt;Size() &gt; ef) → if_statement@824 (reasoning != nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L825 | top_candidates-&gt;Top | while_statement@733 (not candidate_set-&gt;Empty()) → for_statement@804 i &lt; count_no_visited → if_statement@814 (not is_finite_distance(dist)) → lambda@816（定义体，执行时间取决于调用/调度） → if_statement@822 (mode == KNN_SEARCH) → while_statement@823 (top_candidates-&gt;Size() &gt; ef) → if_statement@824 (reasoning != nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L827 | top_candidates-&gt;Pop | while_statement@733 (not candidate_set-&gt;Empty()) → for_statement@804 i &lt; count_no_visited → if_statement@814 (not is_finite_distance(dist)) → lambda@816（定义体，执行时间取决于调用/调度） → if_statement@822 (mode == KNN_SEARCH) → while_statement@823 (top_candidates-&gt;Size() &gt; ef) | 当前参考未静态绑定；见下方边界说明 |

| L830 | top_candidates-&gt;Pop | while_statement@733 (not candidate_set-&gt;Empty()) → for_statement@804 i &lt; count_no_visited → if_statement@814 (not is_finite_distance(dist)) → lambda@816（定义体，执行时间取决于调用/调度） → if_statement@822 (mode == KNN_SEARCH) [else 分支] → if_statement@829 (dist &gt; inner_search_param.radius) | 当前参考未静态绑定；见下方边界说明 |

| L833 | push_result | while_statement@733 (not candidate_set-&gt;Empty()) → for_statement@804 i &lt; count_no_visited → if_statement@814 (not is_finite_distance(dist)) | 当前参考未静态绑定；见下方边界说明 |

| L835 | graph-&gt;GetDuplicateIds | while_statement@733 (not candidate_set-&gt;Empty()) → for_statement@804 i &lt; count_no_visited → if_statement@814 (not is_finite_distance(dist)) → if_statement@834 (inner_search_param.consider_duplicate and not use_custom_distance) → for_range_loop@835 | 当前参考未静态绑定；见下方边界说明 |

| L836 | push_result | while_statement@733 (not candidate_set-&gt;Empty()) → for_statement@804 i &lt; count_no_visited → if_statement@814 (not is_finite_distance(dist)) → if_statement@834 (inner_search_param.consider_duplicate and not use_custom_distance) → for_range_loop@835 | 当前参考未静态绑定；见下方边界说明 |

| L839 | top_candidates-&gt;Empty | while_statement@733 (not candidate_set-&gt;Empty()) → for_statement@804 i &lt; count_no_visited → if_statement@814 (not is_finite_distance(dist)) → if_statement@839 (not top_candidates-&gt;Empty()) | 当前参考未静态绑定；见下方边界说明 |

| L840 | top_candidates-&gt;Top | while_statement@733 (not candidate_set-&gt;Empty()) → for_statement@804 i &lt; count_no_visited → if_statement@814 (not is_finite_distance(dist)) → if_statement@839 (not top_candidates-&gt;Empty()) | 当前参考未静态绑定；见下方边界说明 |

| L846 | check_func | while_statement@733 (not candidate_set-&gt;Empty()) → for_statement@804 i &lt; count_no_visited → if_statement@844 (mode == KNN_SEARCH) → if_statement@845 (collect_rabitq_lower_bound and lower_bound_dists[i] &lt; lower_bound and check_func(cur_id)) | 当前参考未静态绑定；见下方边界说明 |

| L847 | rabitq_lower_bound_candidates-&gt;emplace_back | while_statement@733 (not candidate_set-&gt;Empty()) → for_statement@804 i &lt; count_no_visited → if_statement@844 (mode == KNN_SEARCH) → if_statement@845 (collect_rabitq_lower_bound and lower_bound_dists[i] &lt; lower_bound and check_func(cur_id)) | 当前参考未静态绑定；见下方边界说明 |

| L850 | top_candidates-&gt;Size | while_statement@733 (not candidate_set-&gt;Empty()) → for_statement@804 i &lt; count_no_visited → if_statement@850 (top_candidates-&gt;Size() &lt; ef &#124;&#124; lower_bound &gt; dist &#124;&#124; (mode == RANGE_SEARCH && dist &lt;= inner_search_param.radius)) | 当前参考未静态绑定；见下方边界说明 |

| L852 | candidate_set-&gt;Push | while_statement@733 (not candidate_set-&gt;Empty()) → for_statement@804 i &lt; count_no_visited → if_statement@850 (top_candidates-&gt;Size() &lt; ef &#124;&#124; lower_bound &gt; dist &#124;&#124; (mode == RANGE_SEARCH && dist &lt;= inner_search_param.radius)) | 当前参考未静态绑定；见下方边界说明 |

| L854 | check_func | while_statement@733 (not candidate_set-&gt;Empty()) → for_statement@804 i &lt; count_no_visited → if_statement@850 (top_candidates-&gt;Size() &lt; ef &#124;&#124; lower_bound &gt; dist &#124;&#124; (mode == RANGE_SEARCH && dist &lt;= inner_search_param.radius)) → if_statement@854 (check_func(cur_id)) | 当前参考未静态绑定；见下方边界说明 |

| L855 | top_candidates-&gt;Push | while_statement@733 (not candidate_set-&gt;Empty()) → for_statement@804 i &lt; count_no_visited → if_statement@850 (top_candidates-&gt;Size() &lt; ef &#124;&#124; lower_bound &gt; dist &#124;&#124; (mode == RANGE_SEARCH && dist &lt;= inner_search_param.radius)) → if_statement@854 (check_func(cur_id)) | 当前参考未静态绑定；见下方边界说明 |

| L857 | reasoning-&gt;RecordFilterReject | while_statement@733 (not candidate_set-&gt;Empty()) → for_statement@804 i &lt; count_no_visited → if_statement@850 (top_candidates-&gt;Size() &lt; ef &#124;&#124; lower_bound &gt; dist &#124;&#124; (mode == RANGE_SEARCH && dist &lt;= inner_search_param.radius)) → if_statement@854 (check_func(cur_id)) [else 分支] → if_statement@856 (reasoning != nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L860 | graph-&gt;GetDuplicateIds | while_statement@733 (not candidate_set-&gt;Empty()) → for_statement@804 i &lt; count_no_visited → if_statement@850 (top_candidates-&gt;Size() &lt; ef &#124;&#124; lower_bound &gt; dist &#124;&#124; (mode == RANGE_SEARCH && dist &lt;= inner_search_param.radius)) → if_statement@859 (inner_search_param.consider_duplicate and not use_custom_distance) | 当前参考未静态绑定；见下方边界说明 |

| L862 | check_func | while_statement@733 (not candidate_set-&gt;Empty()) → for_statement@804 i &lt; count_no_visited → if_statement@850 (top_candidates-&gt;Size() &lt; ef &#124;&#124; lower_bound &gt; dist &#124;&#124; (mode == RANGE_SEARCH && dist &lt;= inner_search_param.radius)) → if_statement@859 (inner_search_param.consider_duplicate and not use_custom_distance) → for_range_loop@861 → if_statement@862 (check_func(item)) | 当前参考未静态绑定；见下方边界说明 |

| L863 | top_candidates-&gt;Push | while_statement@733 (not candidate_set-&gt;Empty()) → for_statement@804 i &lt; count_no_visited → if_statement@850 (top_candidates-&gt;Size() &lt; ef &#124;&#124; lower_bound &gt; dist &#124;&#124; (mode == RANGE_SEARCH && dist &lt;= inner_search_param.radius)) → if_statement@859 (inner_search_param.consider_duplicate and not use_custom_distance) → for_range_loop@861 → if_statement@862 (check_func(item)) | 当前参考未静态绑定；见下方边界说明 |

| L869 | top_candidates-&gt;Size | while_statement@733 (not candidate_set-&gt;Empty()) → for_statement@804 i &lt; count_no_visited → if_statement@850 (top_candidates-&gt;Size() &lt; ef &#124;&#124; lower_bound &gt; dist &#124;&#124; (mode == RANGE_SEARCH && dist &lt;= inner_search_param.radius)) → if_statement@868 (mode == KNN_SEARCH) → if_statement@869 (top_candidates-&gt;Size() &gt; ef) | 当前参考未静态绑定；见下方边界说明 |

| L871 | reasoning-&gt;RecordEviction | while_statement@733 (not candidate_set-&gt;Empty()) → for_statement@804 i &lt; count_no_visited → if_statement@850 (top_candidates-&gt;Size() &lt; ef &#124;&#124; lower_bound &gt; dist &#124;&#124; (mode == RANGE_SEARCH && dist &lt;= inner_search_param.radius)) → if_statement@868 (mode == KNN_SEARCH) → if_statement@869 (top_candidates-&gt;Size() &gt; ef) → if_statement@870 (reasoning != nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L871 | top_candidates-&gt;Top | while_statement@733 (not candidate_set-&gt;Empty()) → for_statement@804 i &lt; count_no_visited → if_statement@850 (top_candidates-&gt;Size() &lt; ef &#124;&#124; lower_bound &gt; dist &#124;&#124; (mode == RANGE_SEARCH && dist &lt;= inner_search_param.radius)) → if_statement@868 (mode == KNN_SEARCH) → if_statement@869 (top_candidates-&gt;Size() &gt; ef) → if_statement@870 (reasoning != nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L873 | top_candidates-&gt;Pop | while_statement@733 (not candidate_set-&gt;Empty()) → for_statement@804 i &lt; count_no_visited → if_statement@850 (top_candidates-&gt;Size() &lt; ef &#124;&#124; lower_bound &gt; dist &#124;&#124; (mode == RANGE_SEARCH && dist &lt;= inner_search_param.radius)) → if_statement@868 (mode == KNN_SEARCH) → if_statement@869 (top_candidates-&gt;Size() &gt; ef) | 当前参考未静态绑定；见下方边界说明 |

| L877 | top_candidates-&gt;Empty | while_statement@733 (not candidate_set-&gt;Empty()) → for_statement@804 i &lt; count_no_visited → if_statement@850 (top_candidates-&gt;Size() &lt; ef &#124;&#124; lower_bound &gt; dist &#124;&#124; (mode == RANGE_SEARCH && dist &lt;= inner_search_param.radius)) → if_statement@877 (not top_candidates-&gt;Empty()) | 当前参考未静态绑定；见下方边界说明 |

| L878 | top_candidates-&gt;Top | while_statement@733 (not candidate_set-&gt;Empty()) → for_statement@804 i &lt; count_no_visited → if_statement@850 (top_candidates-&gt;Size() &lt; ef &#124;&#124; lower_bound &gt; dist &#124;&#124; (mode == RANGE_SEARCH && dist &lt;= inner_search_param.radius)) → if_statement@877 (not top_candidates-&gt;Empty()) | 当前参考未静态绑定；见下方边界说明 |

| L885 | top_candidates-&gt;Size | if_statement@884 (mode == KNN_SEARCH) → while_statement@885 (top_candidates-&gt;Size() &gt; inner_search_param.topk) | 当前参考未静态绑定；见下方边界说明 |

| L886 | top_candidates-&gt;Pop | if_statement@884 (mode == KNN_SEARCH) → while_statement@885 (top_candidates-&gt;Size() &gt; inner_search_param.topk) | 当前参考未静态绑定；见下方边界说明 |

| L890 | top_candidates-&gt;Size | if_statement@884 (mode == KNN_SEARCH) [else 分支] → if_statement@888 (mode == RANGE_SEARCH) → if_statement@889 (inner_search_param.range_search_limit_size &gt; 0) → while_statement@890 (top_candidates-&gt;Size() &gt; inner_search_param.range_search_limit_size) | 当前参考未静态绑定；见下方边界说明 |

| L891 | top_candidates-&gt;Pop | if_statement@884 (mode == KNN_SEARCH) [else 分支] → if_statement@888 (mode == RANGE_SEARCH) → if_statement@889 (inner_search_param.range_search_limit_size &gt; 0) → while_statement@890 (top_candidates-&gt;Size() &gt; inner_search_param.range_search_limit_size) | 当前参考未静态绑定；见下方边界说明 |

| L894 | top_candidates-&gt;Empty | if_statement@884 (mode == KNN_SEARCH) [else 分支] → if_statement@888 (mode == RANGE_SEARCH) → while_statement@894 (not top_candidates-&gt;Empty() && top_candidates-&gt;Top().first &gt; inner_search_param.radius + THRESHOLD_ERROR) | 当前参考未静态绑定；见下方边界说明 |

| L895 | top_candidates-&gt;Top | if_statement@884 (mode == KNN_SEARCH) [else 分支] → if_statement@888 (mode == RANGE_SEARCH) → while_statement@894 (not top_candidates-&gt;Empty() && top_candidates-&gt;Top().first &gt; inner_search_param.radius + THRESHOLD_ERROR) | 当前参考未静态绑定；见下方边界说明 |

| L896 | top_candidates-&gt;Pop | if_statement@884 (mode == KNN_SEARCH) [else 分支] → if_statement@888 (mode == RANGE_SEARCH) → while_statement@894 (not top_candidates-&gt;Empty() && top_candidates-&gt;Top().first &gt; inner_search_param.radius + THRESHOLD_ERROR) | 当前参考未静态绑定；见下方边界说明 |

| L902 | top_candidates-&gt;Empty | if_statement@901 (not use_custom_distance and inner_search_param.find_duplicate and not top_candidates-&gt;Empty()) | 当前参考未静态绑定；见下方边界说明 |

| L903 | top_candidates-&gt;GetData | if_statement@901 (not use_custom_distance and inner_search_param.find_duplicate and not top_candidates-&gt;Empty()) | 当前参考未静态绑定；见下方边界说明 |

| L906 | top_candidates-&gt;Size | if_statement@901 (not use_custom_distance and inner_search_param.find_duplicate and not top_candidates-&gt;Empty()) → for_statement@906 i &lt; top_candidates-&gt;Size() | 当前参考未静态绑定；见下方边界说明 |

| L918 | flatten-&gt;TotalCount | if_statement@901 (not use_custom_distance and inner_search_param.find_duplicate and not top_candidates-&gt;Empty()) → if_statement@912 (inner_search_param.duplicate_distance_threshold &gt; 0.0F) [else 分支] | 当前参考未静态绑定；见下方边界说明 |

| L921 | flatten-&gt;CompareVectors | if_statement@901 (not use_custom_distance and inner_search_param.find_duplicate and not top_candidates-&gt;Empty()) → if_statement@912 (inner_search_param.duplicate_distance_threshold &gt; 0.0F) [else 分支] → conditional_expression@920 has_stored_query | 当前参考未静态绑定；见下方边界说明 |

| L922 | flatten-&gt;CompareRawVectorWithId | if_statement@901 (not use_custom_distance and inner_search_param.find_duplicate and not top_candidates-&gt;Empty()) → if_statement@912 (inner_search_param.duplicate_distance_threshold &gt; 0.0F) [else 分支] → conditional_expression@920 has_stored_query | 当前参考未静态绑定；见下方边界说明 |

| L931 | stats.dist_cmp.fetch_add | if_statement@929 (ctx != nullptr and ctx-&gt;stats != nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L932 | stats.hops.fetch_add | if_statement@929 (ctx != nullptr and ctx-&gt;stats != nullptr) | 当前参考未静态绑定；见下方边界说明 |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L938"></a>

## `BasicSearcher::SetRuntimeParameters`

源码位置：`src/impl/searcher/basic_searcher.cpp:938–949`。

先从签名确认输入、返回值和 const/override，再按完整函数体的条件阅读调用点。下表保留了本函数的显式调用以及 lambda 中的调用；进入下层时用“候选实现”定位，未解析的对象由源码静态类型/运行时类型确认。

### 完整函数

```cpp
bool
BasicSearcher::SetRuntimeParameters(const UnorderedMap<std::string, float>& new_params) {
    bool ret = false;
    auto iter = new_params.find(PREFETCH_STRIDE_VISIT);
    if (iter != new_params.end()) {
        prefetch_stride_visit_ = static_cast<uint32_t>(iter->second);
        ret = true;
    }

    ret |= this->mock_flatten_->SetRuntimeParameters(new_params);
    return ret;
}
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L941 | new_params.find | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L942 | new_params.end | if_statement@942 (iter != new_params.end()) | 当前参考未静态绑定；见下方边界说明 |

| L947 | this-&gt;mock_flatten_-&gt;SetRuntimeParameters | 函数本体；短路求值/提前返回见源码 | [BasicSearcher::SetRuntimeParameters · L938](basic_searcher.md#L938) |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L951"></a>

## `BasicSearcher::SetMockParameters`

源码位置：`src/impl/searcher/basic_searcher.cpp:951–964`。

先从签名确认输入、返回值和 const/override，再按完整函数体的条件阅读调用点。下表保留了本函数的显式调用以及 lambda 中的调用；进入下层时用“候选实现”定位，未解析的对象由源码静态类型/运行时类型确认。

### 完整函数

```cpp
void
BasicSearcher::SetMockParameters(const GraphInterfacePtr& graph,
                                 const FlattenInterfacePtr& flatten,
                                 const std::shared_ptr<VisitedListPool>& vl_pool,
                                 const InnerSearchParam& inner_search_param,
                                 const uint64_t dim,
                                 const uint32_t n_trials) {
    mock_graph_ = graph;
    mock_flatten_ = flatten;
    mock_vl_pool_ = vl_pool;
    mock_inner_search_param_ = inner_search_param;
    mock_dim_ = dim;
    mock_n_trials_ = n_trials;
}
```

### 函数内部调用点：不省略标准库和辅助调用

此函数体没有显式函数调用表达式。赋值、成员初始化和隐式操作请看上面的完整源码。


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L966"></a>

## `BasicSearcher::MockRun`

源码位置：`src/impl/searcher/basic_searcher.cpp:966–995`。

先从签名确认输入、返回值和 const/override，再按完整函数体的条件阅读调用点。下表保留了本函数的显式调用以及 lambda 中的调用；进入下层时用“候选实现”定位，未解析的对象由源码静态类型/运行时类型确认。

### 完整函数

```cpp
double
BasicSearcher::MockRun(SearchStatistics& stats) const {
    uint64_t n_trials = std::min(mock_n_trials_, mock_flatten_->TotalCount());

    double time_cost = 0;
    for (uint32_t i = 0; i < n_trials; ++i) {
        // init param
        Vector<uint8_t> codes(mock_flatten_->code_size_, allocator_);
        mock_flatten_->GetCodesById(i, codes.data());

        Vector<float> raw_data(mock_dim_, allocator_);
        mock_flatten_->Decode(codes.data(), raw_data.data());
        auto vl = mock_vl_pool_->TakeOne();

        // mock run
        auto st = std::chrono::high_resolution_clock::now();
        Search(mock_graph_,
               mock_flatten_,
               vl,
               raw_data.data(),
               mock_inner_search_param_,
               (LabelTablePtr) nullptr,
               nullptr);
        auto ed = std::chrono::high_resolution_clock::now();
        time_cost += std::chrono::duration<double>(ed - st).count();

        mock_vl_pool_->ReturnOne(vl);
    }
    return time_cost;
}
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L968 | std::min | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L968 | mock_flatten_-&gt;TotalCount | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L974 | mock_flatten_-&gt;GetCodesById | for_statement@971 i &lt; n_trials | 当前参考未静态绑定；见下方边界说明 |

| L974 | codes.data | for_statement@971 i &lt; n_trials | 当前参考未静态绑定；见下方边界说明 |

| L977 | mock_flatten_-&gt;Decode | for_statement@971 i &lt; n_trials | 当前参考未静态绑定；见下方边界说明 |

| L977 | codes.data | for_statement@971 i &lt; n_trials | 当前参考未静态绑定；见下方边界说明 |

| L977 | raw_data.data | for_statement@971 i &lt; n_trials | 当前参考未静态绑定；见下方边界说明 |

| L978 | mock_vl_pool_-&gt;TakeOne | for_statement@971 i &lt; n_trials | 当前参考未静态绑定；见下方边界说明 |

| L981 | std::chrono::high_resolution_clock::now | for_statement@971 i &lt; n_trials | 当前参考未静态绑定；见下方边界说明 |

| L982 | Search | for_statement@971 i &lt; n_trials | [BasicSearcher::Search · L76](basic_searcher.md#L76)；[BasicSearcher::Search · L139](basic_searcher.md#L139)；[BasicSearcher::Search · L158](basic_searcher.md#L158) |

| L985 | raw_data.data | for_statement@971 i &lt; n_trials | 当前参考未静态绑定；见下方边界说明 |

| L989 | std::chrono::high_resolution_clock::now | for_statement@971 i &lt; n_trials | 当前参考未静态绑定；见下方边界说明 |

| L990 | std::chrono::duration&lt;double&gt;(ed - st).count | for_statement@971 i &lt; n_trials | 当前参考未静态绑定；见下方边界说明 |

| L990 | std::chrono::duration&lt;double&gt; | for_statement@971 i &lt; n_trials | 当前参考未静态绑定；见下方边界说明 |

| L992 | mock_vl_pool_-&gt;ReturnOne | for_statement@971 i &lt; n_trials | 当前参考未静态绑定；见下方边界说明 |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L997"></a>

## `BasicSearcher::SetMutexArray`

源码位置：`src/impl/searcher/basic_searcher.cpp:997–1001`。

先从签名确认输入、返回值和 const/override，再按完整函数体的条件阅读调用点。下表保留了本函数的显式调用以及 lambda 中的调用；进入下层时用“候选实现”定位，未解析的对象由源码静态类型/运行时类型确认。

### 完整函数

```cpp
void
BasicSearcher::SetMutexArray(MutexArrayPtr new_mutex_array) {
    mutex_array_.reset();
    mutex_array_ = std::move(new_mutex_array);
}
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L999 | mutex_array_.reset | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L1000 | std::move | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。
