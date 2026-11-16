# bucket_reorder.cpp：逐函数完整源码与调用点

[主讲解](../code_walkthrough.md) · [函数总目录](README.md)

源码：[ src/impl/reorder/bucket_reorder.cpp ](../../../../src/impl/reorder/bucket_reorder.cpp)。基线 `fd363937`。以下源码函数体完整保留；调用点表是语法树中的显式调用表达式，按源码位置排列，不代表 C++ 参数求值顺序。表中“候选实现”需结合类型和参数选分支，不能将同名函数全部视为必经路径。

- [BucketReorder::Reorder · L28](bucket_reorder.md#L28)


<a id="L28"></a>

## `BucketReorder::Reorder`

源码位置：`src/impl/reorder/bucket_reorder.cpp:28–95`。

检查具体精排类。BucketReorder 用 location_resolver 将 origin ID 变成桶/offset，批量 Query 后重建堆。FlattenReorder 使用扁平编码，也包含其他调用方支持的分支；IVF 传参见主讲解。

### 完整函数

```cpp
DistHeapPtr
BucketReorder::Reorder(const DistHeapPtr& input,
                       const void* query,
                       int64_t topk,
                       QueryContext& ctx,
                       IteratorFilterContext* iter_ctx,
                       const DistanceRecordVector* rabitq_lower_bound_candidates,
                       const std::optional<float>& distance_threshold) {
    if (iter_ctx != nullptr) {
        throw VsagException(ErrorType::UNSUPPORTED_INDEX_OPERATION,
                            "BucketReorder does not support iterator filtering");
    }
    if (rabitq_lower_bound_candidates != nullptr) {
        throw VsagException(ErrorType::UNSUPPORTED_INDEX_OPERATION,
                            "BucketReorder does not support RaBitQ lower-bound candidates");
    }

    Allocator* query_allocator = select_query_allocator(ctx.alloc, allocator_);
    const uint64_t candidate_count = input == nullptr ? 0 : input->Size();
    topk = std::min(topk, static_cast<int64_t>(candidate_count));
    auto reorder_heap = std::make_shared<StandardHeap<true, false>>(query_allocator, topk);
    if (candidate_count == 0 or topk == 0) {
        return reorder_heap;
    }

    if (ctx.stats != nullptr) {
        ctx.stats->reorder_distance_count.fetch_add(static_cast<uint32_t>(candidate_count),
                                                    std::memory_order_relaxed);
    }

    auto computer = bucket_->FactoryComputer(query);
    const auto* candidates = input->GetData();
    Vector<BucketIdType> bucket_ids(candidate_count, query_allocator);
    Vector<InnerIdType> offset_ids(candidate_count, query_allocator);
    Vector<float> precise_distances(candidate_count, query_allocator);
    for (uint64_t i = 0; i < candidate_count; ++i) {
        const auto [bucket_id, offset_id] = location_resolver_(candidates[i].second);
        bucket_ids[i] = bucket_id;
        offset_ids[i] = offset_id;
    }
    bucket_->Query(precise_distances.data(),
                   computer,
                   bucket_ids.data(),
                   offset_ids.data(),
                   static_cast<InnerIdType>(candidate_count),
                   &ctx);
    for (uint64_t i = 0; i < candidate_count; ++i) {
        const auto [coarse_distance, inner_id] = candidates[i];
        const auto precise_distance = precise_distances[i];
        if (ctx.reasoning_ctx != nullptr) {
            ctx.reasoning_ctx->RecordReorder(inner_id, coarse_distance, precise_distance);
        }
        if (distance_threshold.has_value() and (not std::isfinite(precise_distance) or
                                                precise_distance > distance_threshold.value())) {
            continue;
        }
        if (reorder_heap->Size() < topk or precise_distance < reorder_heap->Top().first) {
            reorder_heap->Push(precise_distance, inner_id);
            if (reorder_heap->Size() > topk) {
                if (ctx.reasoning_ctx != nullptr) {
                    ctx.reasoning_ctx->RecordReorderEviction(reorder_heap->Top().second, 0);
                }
                reorder_heap->Pop();
            }
        }
    }
    return reorder_heap;
}
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L37 | VsagException | if_statement@36 (iter_ctx != nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L41 | VsagException | if_statement@40 (rabitq_lower_bound_candidates != nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L45 | select_query_allocator | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L46 | input-&gt;Size | conditional_expression@46 input == nullptr | 当前参考未静态绑定；见下方边界说明 |

| L47 | std::min | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L48 | std::make_shared&lt;StandardHeap&lt;true, false&gt;&gt; | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L54 | ctx.stats-&gt;reorder_distance_count.fetch_add | if_statement@53 (ctx.stats != nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L58 | bucket_-&gt;FactoryComputer | 函数本体；短路求值/提前返回见源码 | [BucketDataCell&lt;QuantTmpl, IOTmpl&gt;::FactoryComputer · L566](bucket_datacell_h.md#L566) |

| L59 | input-&gt;GetData | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L64 | location_resolver_ | for_statement@63 i &lt; candidate_count | 当前参考未静态绑定；见下方边界说明 |

| L68 | bucket_-&gt;Query | 函数本体；短路求值/提前返回见源码 | [BucketDataCell::Query · L82](bucket_datacell_h.md#L82) |

| L68 | precise_distances.data | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L70 | bucket_ids.data | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L71 | offset_ids.data | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L78 | ctx.reasoning_ctx-&gt;RecordReorder | for_statement@74 i &lt; candidate_count → if_statement@77 (ctx.reasoning_ctx != nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L80 | distance_threshold.has_value | for_statement@74 i &lt; candidate_count → if_statement@80 (distance_threshold.has_value() and (not std::isfinite(precise_distance) or precise_distance &gt; distance_threshold.value())) | 当前参考未静态绑定；见下方边界说明 |

| L80 | std::isfinite | for_statement@74 i &lt; candidate_count → if_statement@80 (distance_threshold.has_value() and (not std::isfinite(precise_distance) or precise_distance &gt; distance_threshold.value())) | 当前参考未静态绑定；见下方边界说明 |

| L81 | distance_threshold.value | for_statement@74 i &lt; candidate_count → if_statement@80 (distance_threshold.has_value() and (not std::isfinite(precise_distance) or precise_distance &gt; distance_threshold.value())) | 当前参考未静态绑定；见下方边界说明 |

| L84 | reorder_heap-&gt;Size | for_statement@74 i &lt; candidate_count → if_statement@84 (reorder_heap-&gt;Size() &lt; topk or precise_distance &lt; reorder_heap-&gt;Top().first) | 当前参考未静态绑定；见下方边界说明 |

| L84 | reorder_heap-&gt;Top | for_statement@74 i &lt; candidate_count → if_statement@84 (reorder_heap-&gt;Size() &lt; topk or precise_distance &lt; reorder_heap-&gt;Top().first) | 当前参考未静态绑定；见下方边界说明 |

| L85 | reorder_heap-&gt;Push | for_statement@74 i &lt; candidate_count → if_statement@84 (reorder_heap-&gt;Size() &lt; topk or precise_distance &lt; reorder_heap-&gt;Top().first) | 当前参考未静态绑定；见下方边界说明 |

| L86 | reorder_heap-&gt;Size | for_statement@74 i &lt; candidate_count → if_statement@84 (reorder_heap-&gt;Size() &lt; topk or precise_distance &lt; reorder_heap-&gt;Top().first) → if_statement@86 (reorder_heap-&gt;Size() &gt; topk) | 当前参考未静态绑定；见下方边界说明 |

| L88 | ctx.reasoning_ctx-&gt;RecordReorderEviction | for_statement@74 i &lt; candidate_count → if_statement@84 (reorder_heap-&gt;Size() &lt; topk or precise_distance &lt; reorder_heap-&gt;Top().first) → if_statement@86 (reorder_heap-&gt;Size() &gt; topk) → if_statement@87 (ctx.reasoning_ctx != nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L88 | reorder_heap-&gt;Top | for_statement@74 i &lt; candidate_count → if_statement@84 (reorder_heap-&gt;Size() &lt; topk or precise_distance &lt; reorder_heap-&gt;Top().first) → if_statement@86 (reorder_heap-&gt;Size() &gt; topk) → if_statement@87 (ctx.reasoning_ctx != nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L90 | reorder_heap-&gt;Pop | for_statement@74 i &lt; candidate_count → if_statement@84 (reorder_heap-&gt;Size() &lt; topk or precise_distance &lt; reorder_heap-&gt;Top().first) → if_statement@86 (reorder_heap-&gt;Size() &gt; topk) | 当前参考未静态绑定；见下方边界说明 |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。
