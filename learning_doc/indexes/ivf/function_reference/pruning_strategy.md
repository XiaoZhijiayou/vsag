# pruning_strategy.cpp：逐函数完整源码与调用点

[主讲解](../code_walkthrough.md) · [函数总目录](README.md)

源码：[ src/impl/pruning_strategy.cpp ](../../../../src/impl/pruning_strategy.cpp)。基线 `fd363937`。以下源码函数体完整保留；调用点表是语法树中的显式调用表达式，按源码位置排列，不代表 C++ 参数求值顺序。表中“候选实现”需结合类型和参数选分支，不能将同名函数全部视为必经路径。

- [PairwiseDistanceComputer::PairwiseDistanceComputer · L29](pruning_strategy.md#L29)

- [PairwiseDistanceComputer::PairwiseDistanceComputer · L34](pruning_strategy.md#L34)

- [PairwiseDistanceComputer::& operator= · L35](pruning_strategy.md#L35)

- [PairwiseDistanceComputer::PairwiseDistanceComputer · L37](pruning_strategy.md#L37)

- [PairwiseDistanceComputer::& operator= · L38](pruning_strategy.md#L38)

- [PairwiseDistanceComputer::PairwiseDistance · L41](pruning_strategy.md#L41)

- [select_edges_by_heuristic · L61](pruning_strategy.md#L61)

- [select_edges_by_heuristic · L84](pruning_strategy.md#L84)

- [mutually_connect_new_element · L129](pruning_strategy.md#L129)

- [select_edges_by_heuristic · L205](pruning_strategy.md#L205)

- [select_edges_by_heuristic · L216](pruning_strategy.md#L216)

- [mutually_connect_new_element · L226](pruning_strategy.md#L226)


<a id="L29"></a>

## `PairwiseDistanceComputer::PairwiseDistanceComputer`

源码位置：`src/impl/pruning_strategy.cpp:29–32`。

先从签名确认输入、返回值和 const/override，再按完整函数体的条件阅读调用点。下表保留了本函数的显式调用以及 lambda 中的调用；进入下层时用“候选实现”定位，未解析的对象由源码静态类型/运行时类型确认。

### 完整函数

```cpp
PairwiseDistanceComputer(const DistanceProviderForGraph& distance_provider,
                             Allocator* allocator)
        : distance_provider_(distance_provider), computers_(allocator) {
    }
```

### 函数内部调用点：不省略标准库和辅助调用

此函数体没有显式函数调用表达式。赋值、成员初始化和隐式操作请看上面的完整源码。


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L34"></a>

## `PairwiseDistanceComputer::PairwiseDistanceComputer`

源码位置：`src/impl/pruning_strategy.cpp:34–34`。

先从签名确认输入、返回值和 const/override，再按完整函数体的条件阅读调用点。下表保留了本函数的显式调用以及 lambda 中的调用；进入下层时用“候选实现”定位，未解析的对象由源码静态类型/运行时类型确认。

### 完整函数

```cpp
PairwiseDistanceComputer(const PairwiseDistanceComputer&) = delete;
```

### 函数内部调用点：不省略标准库和辅助调用

此函数体没有显式函数调用表达式。赋值、成员初始化和隐式操作请看上面的完整源码。


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L35"></a>

## `PairwiseDistanceComputer::& operator=`

源码位置：`src/impl/pruning_strategy.cpp:35–36`。

先从签名确认输入、返回值和 const/override，再按完整函数体的条件阅读调用点。下表保留了本函数的显式调用以及 lambda 中的调用；进入下层时用“候选实现”定位，未解析的对象由源码静态类型/运行时类型确认。

### 完整函数

```cpp
PairwiseDistanceComputer&
    operator=(const PairwiseDistanceComputer&) = delete;
```

### 函数内部调用点：不省略标准库和辅助调用

此函数体没有显式函数调用表达式。赋值、成员初始化和隐式操作请看上面的完整源码。


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L37"></a>

## `PairwiseDistanceComputer::PairwiseDistanceComputer`

源码位置：`src/impl/pruning_strategy.cpp:37–37`。

先从签名确认输入、返回值和 const/override，再按完整函数体的条件阅读调用点。下表保留了本函数的显式调用以及 lambda 中的调用；进入下层时用“候选实现”定位，未解析的对象由源码静态类型/运行时类型确认。

### 完整函数

```cpp
PairwiseDistanceComputer(PairwiseDistanceComputer&&) = delete;
```

### 函数内部调用点：不省略标准库和辅助调用

此函数体没有显式函数调用表达式。赋值、成员初始化和隐式操作请看上面的完整源码。


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L38"></a>

## `PairwiseDistanceComputer::& operator=`

源码位置：`src/impl/pruning_strategy.cpp:38–39`。

先从签名确认输入、返回值和 const/override，再按完整函数体的条件阅读调用点。下表保留了本函数的显式调用以及 lambda 中的调用；进入下层时用“候选实现”定位，未解析的对象由源码静态类型/运行时类型确认。

### 完整函数

```cpp
PairwiseDistanceComputer&
    operator=(PairwiseDistanceComputer&&) = delete;
```

### 函数内部调用点：不省略标准库和辅助调用

此函数体没有显式函数调用表达式。赋值、成员初始化和隐式操作请看上面的完整源码。


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L41"></a>

## `PairwiseDistanceComputer::PairwiseDistance`

源码位置：`src/impl/pruning_strategy.cpp:41–51`。

先从签名确认输入、返回值和 const/override，再按完整函数体的条件阅读调用点。下表保留了本函数的显式调用以及 lambda 中的调用；进入下层时用“候选实现”定位，未解析的对象由源码静态类型/运行时类型确认。

### 完整函数

```cpp
float
    PairwiseDistance(InnerIdType id1, InnerIdType id2) {
        if (not distance_provider_.SupportsComputerById()) {
            return distance_provider_.PairwiseDistance(id1, id2);
        }
        auto& computer = computers_[id1];
        if (computer == nullptr) {
            computer = distance_provider_.FactoryComputerById(id1);
        }
        return distance_provider_.PairwiseDistance(id1, id2, computer);
    }
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L43 | distance_provider_.SupportsComputerById | if_statement@43 (not distance_provider_.SupportsComputerById()) | 当前参考未静态绑定；见下方边界说明 |

| L44 | distance_provider_.PairwiseDistance | if_statement@43 (not distance_provider_.SupportsComputerById()) | 当前参考未静态绑定；见下方边界说明 |

| L48 | distance_provider_.FactoryComputerById | if_statement@47 (computer == nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L50 | distance_provider_.PairwiseDistance | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L61"></a>

## `select_edges_by_heuristic`

源码位置：`src/impl/pruning_strategy.cpp:61–82`。

先从签名确认输入、返回值和 const/override，再按完整函数体的条件阅读调用点。下表保留了本函数的显式调用以及 lambda 中的调用；进入下层时用“候选实现”定位，未解析的对象由源码静态类型/运行时类型确认。

### 完整函数

```cpp
void
select_edges_by_heuristic(Vector<InnerIdType>& neighbors,
                          InnerIdType node_id,
                          uint64_t max_size,
                          const DistanceProviderForGraph& distance_provider,
                          Allocator* allocator,
                          float alpha) {
    PairwiseDistanceComputer pairwise_distance(distance_provider, allocator);
    auto edges = std::make_shared<StandardHeap<true, false>>(allocator, -1);
    for (const auto& neighbor : neighbors) {
        float dist = pairwise_distance.PairwiseDistance(node_id, neighbor);
        edges->Push(dist, neighbor);
    }

    select_edges_by_heuristic(edges, max_size, distance_provider, allocator, alpha);

    neighbors.clear();
    while (not edges->Empty()) {
        neighbors.emplace_back(edges->Top().second);
        edges->Pop();
    }
}
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L69 | std::make_shared&lt;StandardHeap&lt;true, false&gt;&gt; | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L71 | pairwise_distance.PairwiseDistance | for_range_loop@70 | 当前参考未静态绑定；见下方边界说明 |

| L72 | edges-&gt;Push | for_range_loop@70 | 当前参考未静态绑定；见下方边界说明 |

| L75 | select_edges_by_heuristic | 函数本体；短路求值/提前返回见源码 | [select_edges_by_heuristic · L61](pruning_strategy.md#L61)；[select_edges_by_heuristic · L84](pruning_strategy.md#L84)；[select_edges_by_heuristic · L205](pruning_strategy.md#L205)；[select_edges_by_heuristic · L216](pruning_strategy.md#L216) |

| L77 | neighbors.clear | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L78 | edges-&gt;Empty | while_statement@78 (not edges-&gt;Empty()) | 当前参考未静态绑定；见下方边界说明 |

| L79 | neighbors.emplace_back | while_statement@78 (not edges-&gt;Empty()) | 当前参考未静态绑定；见下方边界说明 |

| L79 | edges-&gt;Top | while_statement@78 (not edges-&gt;Empty()) | 当前参考未静态绑定；见下方边界说明 |

| L80 | edges-&gt;Pop | while_statement@78 (not edges-&gt;Empty()) | 当前参考未静态绑定；见下方边界说明 |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L84"></a>

## `select_edges_by_heuristic`

源码位置：`src/impl/pruning_strategy.cpp:84–127`。

先从签名确认输入、返回值和 const/override，再按完整函数体的条件阅读调用点。下表保留了本函数的显式调用以及 lambda 中的调用；进入下层时用“候选实现”定位，未解析的对象由源码静态类型/运行时类型确认。

### 完整函数

```cpp
void
select_edges_by_heuristic(const DistHeapPtr& edges,
                          uint64_t max_size,
                          const DistanceProviderForGraph& distance_provider,
                          Allocator* allocator,
                          float alpha) {
    if (edges->Size() < max_size) {
        return;
    }

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

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L90 | edges-&gt;Size | if_statement@90 (edges-&gt;Size() &lt; max_size) | 当前参考未静态绑定；见下方边界说明 |

| L94 | std::make_shared&lt;StandardHeap&lt;true, false&gt;&gt; | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L97 | edges-&gt;Empty | while_statement@97 (not edges-&gt;Empty()) | 当前参考未静态绑定；见下方边界说明 |

| L98 | queue_closest-&gt;Push | while_statement@97 (not edges-&gt;Empty()) | 当前参考未静态绑定；见下方边界说明 |

| L98 | edges-&gt;Top | while_statement@97 (not edges-&gt;Empty()) | 当前参考未静态绑定；见下方边界说明 |

| L98 | edges-&gt;Top | while_statement@97 (not edges-&gt;Empty()) | 当前参考未静态绑定；见下方边界说明 |

| L99 | edges-&gt;Pop | while_statement@97 (not edges-&gt;Empty()) | 当前参考未静态绑定；见下方边界说明 |

| L102 | queue_closest-&gt;Empty | while_statement@102 (not queue_closest-&gt;Empty()) | 当前参考未静态绑定；见下方边界说明 |

| L103 | return_list.size | while_statement@102 (not queue_closest-&gt;Empty()) → if_statement@103 (return_list.size() &gt;= max_size) | 当前参考未静态绑定；见下方边界说明 |

| L106 | queue_closest-&gt;Top | while_statement@102 (not queue_closest-&gt;Empty()) | 当前参考未静态绑定；见下方边界说明 |

| L108 | queue_closest-&gt;Pop | while_statement@102 (not queue_closest-&gt;Empty()) | 当前参考未静态绑定；见下方边界说明 |

| L113 | pairwise_distance.PairwiseDistance | while_statement@102 (not queue_closest-&gt;Empty()) → for_range_loop@111 | 当前参考未静态绑定；见下方边界说明 |

| L120 | return_list.emplace_back | while_statement@102 (not queue_closest-&gt;Empty()) → if_statement@119 (good) | 当前参考未静态绑定；见下方边界说明 |

| L125 | edges-&gt;Push | for_range_loop@124 | 当前参考未静态绑定；见下方边界说明 |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L129"></a>

## `mutually_connect_new_element`

源码位置：`src/impl/pruning_strategy.cpp:129–203`。

先从签名确认输入、返回值和 const/override，再按完整函数体的条件阅读调用点。下表保留了本函数的显式调用以及 lambda 中的调用；进入下层时用“候选实现”定位，未解析的对象由源码静态类型/运行时类型确认。

### 完整函数

```cpp
InnerIdType
mutually_connect_new_element(InnerIdType cur_c,
                             const DistHeapPtr& top_candidates,
                             const GraphInterfacePtr& graph,
                             const DistanceProviderForGraph& distance_provider,
                             const MutexArrayPtr& neighbors_mutexes,
                             Allocator* allocator,
                             float alpha) {
    PairwiseDistanceComputer pairwise_distance(distance_provider, allocator);
    const uint64_t max_size = graph->MaximumDegree();
    select_edges_by_heuristic(top_candidates, max_size, distance_provider, allocator, alpha);
    if (top_candidates->Size() > max_size) {
        throw VsagException(
            ErrorType::INTERNAL_ERROR,
            "Should be not be more than max_size candidates returned by the heuristic");
    }

    Vector<InnerIdType> selected_neighbors(allocator);
    selected_neighbors.reserve(max_size);
    while (not top_candidates->Empty()) {
        selected_neighbors.emplace_back(top_candidates->Top().second);
        top_candidates->Pop();
    }

    InnerIdType next_closest_entry_point = selected_neighbors.back();

    graph->InsertNeighborsById(cur_c, selected_neighbors);

    for (auto selected_neighbor : selected_neighbors) {
        if (selected_neighbor == cur_c) {
            throw VsagException(ErrorType::INTERNAL_ERROR,
                                "Trying to connect an element to itself");
        }

        LockGuard lock(neighbors_mutexes, selected_neighbor);

        Vector<InnerIdType> neighbors(allocator);
        graph->GetNeighbors(selected_neighbor, neighbors);

        uint64_t sz_link_list_other = neighbors.size();

        if (sz_link_list_other > max_size) {
            throw VsagException(ErrorType::INTERNAL_ERROR, "Bad value of sz_link_list_other");
        }
        // If cur_c is already present in the neighboring connections of `selected_neighbors[idx]` then no need to modify any connections or run the heuristics.
        if (sz_link_list_other < max_size) {
            neighbors.emplace_back(cur_c);
            graph->InsertNeighborsById(selected_neighbor, neighbors);
        } else {
            // finding the "weakest" element to replace it with the new one
            float d_max = pairwise_distance.PairwiseDistance(selected_neighbor, cur_c);

            auto candidates = std::make_shared<StandardHeap<true, false>>(allocator, -1);
            candidates->Push(d_max, cur_c);

            for (uint64_t j = 0; j < sz_link_list_other; j++) {
                candidates->Push(
                    pairwise_distance.PairwiseDistance(selected_neighbor, neighbors[j]),
                    neighbors[j]);
            }

            select_edges_by_heuristic(candidates, max_size, distance_provider, allocator, alpha);

            Vector<InnerIdType> cand_neighbors(allocator);
            while (not candidates->Empty()) {
                cand_neighbors.emplace_back(candidates->Top().second);
                candidates->Pop();
            }

            graph->InsertNeighborsById(selected_neighbor, cand_neighbors);
        }
    }

    return next_closest_entry_point;
}
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L138 | graph-&gt;MaximumDegree | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L139 | select_edges_by_heuristic | 函数本体；短路求值/提前返回见源码 | [select_edges_by_heuristic · L61](pruning_strategy.md#L61)；[select_edges_by_heuristic · L84](pruning_strategy.md#L84)；[select_edges_by_heuristic · L205](pruning_strategy.md#L205)；[select_edges_by_heuristic · L216](pruning_strategy.md#L216) |

| L140 | top_candidates-&gt;Size | if_statement@140 (top_candidates-&gt;Size() &gt; max_size) | 当前参考未静态绑定；见下方边界说明 |

| L141 | VsagException | if_statement@140 (top_candidates-&gt;Size() &gt; max_size) | 当前参考未静态绑定；见下方边界说明 |

| L147 | selected_neighbors.reserve | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L148 | top_candidates-&gt;Empty | while_statement@148 (not top_candidates-&gt;Empty()) | 当前参考未静态绑定；见下方边界说明 |

| L149 | selected_neighbors.emplace_back | while_statement@148 (not top_candidates-&gt;Empty()) | 当前参考未静态绑定；见下方边界说明 |

| L149 | top_candidates-&gt;Top | while_statement@148 (not top_candidates-&gt;Empty()) | 当前参考未静态绑定；见下方边界说明 |

| L150 | top_candidates-&gt;Pop | while_statement@148 (not top_candidates-&gt;Empty()) | 当前参考未静态绑定；见下方边界说明 |

| L153 | selected_neighbors.back | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L155 | graph-&gt;InsertNeighborsById | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L159 | VsagException | for_range_loop@157 → if_statement@158 (selected_neighbor == cur_c) | 当前参考未静态绑定；见下方边界说明 |

| L166 | graph-&gt;GetNeighbors | for_range_loop@157 | 当前参考未静态绑定；见下方边界说明 |

| L168 | neighbors.size | for_range_loop@157 | 当前参考未静态绑定；见下方边界说明 |

| L171 | VsagException | for_range_loop@157 → if_statement@170 (sz_link_list_other &gt; max_size) | 当前参考未静态绑定；见下方边界说明 |

| L175 | neighbors.emplace_back | for_range_loop@157 → if_statement@174 (sz_link_list_other &lt; max_size) | 当前参考未静态绑定；见下方边界说明 |

| L176 | graph-&gt;InsertNeighborsById | for_range_loop@157 → if_statement@174 (sz_link_list_other &lt; max_size) | 当前参考未静态绑定；见下方边界说明 |

| L179 | pairwise_distance.PairwiseDistance | for_range_loop@157 → if_statement@174 (sz_link_list_other &lt; max_size) [else 分支] | 当前参考未静态绑定；见下方边界说明 |

| L181 | std::make_shared&lt;StandardHeap&lt;true, false&gt;&gt; | for_range_loop@157 → if_statement@174 (sz_link_list_other &lt; max_size) [else 分支] | 当前参考未静态绑定；见下方边界说明 |

| L182 | candidates-&gt;Push | for_range_loop@157 → if_statement@174 (sz_link_list_other &lt; max_size) [else 分支] | 当前参考未静态绑定；见下方边界说明 |

| L185 | candidates-&gt;Push | for_range_loop@157 → if_statement@174 (sz_link_list_other &lt; max_size) [else 分支] → for_statement@184 j &lt; sz_link_list_other | 当前参考未静态绑定；见下方边界说明 |

| L186 | pairwise_distance.PairwiseDistance | for_range_loop@157 → if_statement@174 (sz_link_list_other &lt; max_size) [else 分支] → for_statement@184 j &lt; sz_link_list_other | 当前参考未静态绑定；见下方边界说明 |

| L190 | select_edges_by_heuristic | for_range_loop@157 → if_statement@174 (sz_link_list_other &lt; max_size) [else 分支] | [select_edges_by_heuristic · L61](pruning_strategy.md#L61)；[select_edges_by_heuristic · L84](pruning_strategy.md#L84)；[select_edges_by_heuristic · L205](pruning_strategy.md#L205)；[select_edges_by_heuristic · L216](pruning_strategy.md#L216) |

| L193 | candidates-&gt;Empty | for_range_loop@157 → if_statement@174 (sz_link_list_other &lt; max_size) [else 分支] → while_statement@193 (not candidates-&gt;Empty()) | 当前参考未静态绑定；见下方边界说明 |

| L194 | cand_neighbors.emplace_back | for_range_loop@157 → if_statement@174 (sz_link_list_other &lt; max_size) [else 分支] → while_statement@193 (not candidates-&gt;Empty()) | 当前参考未静态绑定；见下方边界说明 |

| L194 | candidates-&gt;Top | for_range_loop@157 → if_statement@174 (sz_link_list_other &lt; max_size) [else 分支] → while_statement@193 (not candidates-&gt;Empty()) | 当前参考未静态绑定；见下方边界说明 |

| L195 | candidates-&gt;Pop | for_range_loop@157 → if_statement@174 (sz_link_list_other &lt; max_size) [else 分支] → while_statement@193 (not candidates-&gt;Empty()) | 当前参考未静态绑定；见下方边界说明 |

| L198 | graph-&gt;InsertNeighborsById | for_range_loop@157 → if_statement@174 (sz_link_list_other &lt; max_size) [else 分支] | 当前参考未静态绑定；见下方边界说明 |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L205"></a>

## `select_edges_by_heuristic`

源码位置：`src/impl/pruning_strategy.cpp:205–214`。

先从签名确认输入、返回值和 const/override，再按完整函数体的条件阅读调用点。下表保留了本函数的显式调用以及 lambda 中的调用；进入下层时用“候选实现”定位，未解析的对象由源码静态类型/运行时类型确认。

### 完整函数

```cpp
void
select_edges_by_heuristic(Vector<InnerIdType>& neighbors,
                          InnerIdType node_id,
                          uint64_t max_size,
                          const FlattenInterfacePtr& flatten,
                          Allocator* allocator,
                          float alpha) {
    FlattenDistanceProvider distance_provider(flatten, nullptr);
    select_edges_by_heuristic(neighbors, node_id, max_size, distance_provider, allocator, alpha);
}
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L213 | select_edges_by_heuristic | 函数本体；短路求值/提前返回见源码 | [select_edges_by_heuristic · L61](pruning_strategy.md#L61)；[select_edges_by_heuristic · L84](pruning_strategy.md#L84)；[select_edges_by_heuristic · L205](pruning_strategy.md#L205)；[select_edges_by_heuristic · L216](pruning_strategy.md#L216) |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L216"></a>

## `select_edges_by_heuristic`

源码位置：`src/impl/pruning_strategy.cpp:216–224`。

先从签名确认输入、返回值和 const/override，再按完整函数体的条件阅读调用点。下表保留了本函数的显式调用以及 lambda 中的调用；进入下层时用“候选实现”定位，未解析的对象由源码静态类型/运行时类型确认。

### 完整函数

```cpp
void
select_edges_by_heuristic(const DistHeapPtr& edges,
                          uint64_t max_size,
                          const FlattenInterfacePtr& flatten,
                          Allocator* allocator,
                          float alpha) {
    FlattenDistanceProvider distance_provider(flatten, nullptr);
    select_edges_by_heuristic(edges, max_size, distance_provider, allocator, alpha);
}
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L223 | select_edges_by_heuristic | 函数本体；短路求值/提前返回见源码 | [select_edges_by_heuristic · L61](pruning_strategy.md#L61)；[select_edges_by_heuristic · L84](pruning_strategy.md#L84)；[select_edges_by_heuristic · L205](pruning_strategy.md#L205)；[select_edges_by_heuristic · L216](pruning_strategy.md#L216) |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L226"></a>

## `mutually_connect_new_element`

源码位置：`src/impl/pruning_strategy.cpp:226–237`。

先从签名确认输入、返回值和 const/override，再按完整函数体的条件阅读调用点。下表保留了本函数的显式调用以及 lambda 中的调用；进入下层时用“候选实现”定位，未解析的对象由源码静态类型/运行时类型确认。

### 完整函数

```cpp
InnerIdType
mutually_connect_new_element(InnerIdType cur_c,
                             const DistHeapPtr& top_candidates,
                             const GraphInterfacePtr& graph,
                             const FlattenInterfacePtr& flatten,
                             const MutexArrayPtr& neighbors_mutexes,
                             Allocator* allocator,
                             float alpha) {
    FlattenDistanceProvider distance_provider(flatten, nullptr);
    return mutually_connect_new_element(
        cur_c, top_candidates, graph, distance_provider, neighbors_mutexes, allocator, alpha);
}
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L235 | mutually_connect_new_element | 函数本体；短路求值/提前返回见源码 | [mutually_connect_new_element · L129](pruning_strategy.md#L129)；[mutually_connect_new_element · L226](pruning_strategy.md#L226) |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。
