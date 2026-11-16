# flatten_reorder.cpp：逐函数完整源码与调用点

[主讲解](../code_walkthrough.md) · [函数总目录](README.md)

源码：[ src/impl/reorder/flatten_reorder.cpp ](../../../../src/impl/reorder/flatten_reorder.cpp)。基线 `fd363937`。以下源码函数体完整保留；调用点表是语法树中的显式调用表达式，按源码位置排列，不代表 C++ 参数求值顺序。表中“候选实现”需结合类型和参数选分支，不能将同名函数全部视为必经路径。

- [FlattenReorder::QueryFusedLowerBound · L34](flatten_reorder.md#L34)

- [FlattenReorder::QueryFusedFullWithHint · L77](flatten_reorder.md#L77)

- [add_reorder_distance_count · L130](flatten_reorder.md#L130)

- [add_reorder_candidate_count · L138](flatten_reorder.md#L138)

- [add_reorder_lower_bound_probe_count · L146](flatten_reorder.md#L146)

- [FlattenReorder::Reorder · L156](flatten_reorder.md#L156)

- [FlattenReorder::ReorderFused · L419](flatten_reorder.md#L419)


<a id="L34"></a>

## `FlattenReorder::QueryFusedLowerBound`

源码位置：`src/impl/reorder/flatten_reorder.cpp:34–75`。

先从签名确认输入、返回值和 const/override，再按完整函数体的条件阅读调用点。下表保留了本函数的显式调用以及 lambda 中的调用；进入下层时用“候选实现”定位，未解析的对象由源码静态类型/运行时类型确认。

### 完整函数

```cpp
void
FlattenReorder::QueryFusedLowerBound(float* distances,
                                     float* lower_bounds,
                                     float* filter_inner_products,
                                     RaBitQSplitDataCellInterface* split_codes,
                                     const ComputerInterfacePtr& computer,
                                     const InnerIdType* ids,
                                     uint64_t count,
                                     QueryContext* ctx) const {
    uint32_t fallback_count = 0;
    QueryContext rate_context;
    QueryContext* rate_context_ptr = nullptr;
    if (ctx != nullptr) {
        rate_context.rabitq_error_rate = ctx->rabitq_error_rate;
        rate_context_ptr = &rate_context;
    }
    for (uint64_t i = 0; i < count; ++i) {
        const auto code = fused_graph_->GetCodeView(ids[i]);
        if (not split_codes->ComputeFusedOneBitWithFilterIP(computer,
                                                            code.cluster_id,
                                                            code.one_bit_code,
                                                            code.supplement_code,
                                                            distances + i,
                                                            lower_bounds + i,
                                                            filter_inner_products + i,
                                                            rate_context_ptr)) {
            distances[i] = std::numeric_limits<float>::max();
            lower_bounds[i] = std::numeric_limits<float>::max();
            filter_inner_products[i] = std::numeric_limits<float>::quiet_NaN();
            ++fallback_count;
        }
    }
    if (ctx != nullptr and ctx->stats != nullptr) {
        if (ctx->track_distance_evaluations and count > 0) {
            ctx->stats->AddDistance(ctx->distance_phase, DistanceEvaluationBackend::RABITQ, count);
        }
        ctx->stats->rabitq_filter_count.fetch_add(static_cast<uint32_t>(count),
                                                  std::memory_order_relaxed);
        ctx->stats->rabitq_filter_fallback_full_count.fetch_add(fallback_count,
                                                                std::memory_order_relaxed);
    }
}
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L51 | fused_graph_-&gt;GetCodeView | for_statement@50 i &lt; count | 当前参考未静态绑定；见下方边界说明 |

| L52 | split_codes-&gt;ComputeFusedOneBitWithFilterIP | for_statement@50 i &lt; count → if_statement@52 (not split_codes-&gt;ComputeFusedOneBitWithFilterIP(computer, code.cluster_id, code.one_bit_code, code.supplement_code, distances + i, lower_bounds + i, filter_inner_products + i, rate_context_ptr)) | 当前参考未静态绑定；见下方边界说明 |

| L60 | std::numeric_limits&lt;float&gt;::max | for_statement@50 i &lt; count → if_statement@52 (not split_codes-&gt;ComputeFusedOneBitWithFilterIP(computer, code.cluster_id, code.one_bit_code, code.supplement_code, distances + i, lower_bounds + i, filter_inner_products + i, rate_context_ptr)) | 当前参考未静态绑定；见下方边界说明 |

| L61 | std::numeric_limits&lt;float&gt;::max | for_statement@50 i &lt; count → if_statement@52 (not split_codes-&gt;ComputeFusedOneBitWithFilterIP(computer, code.cluster_id, code.one_bit_code, code.supplement_code, distances + i, lower_bounds + i, filter_inner_products + i, rate_context_ptr)) | 当前参考未静态绑定；见下方边界说明 |

| L62 | std::numeric_limits&lt;float&gt;::quiet_NaN | for_statement@50 i &lt; count → if_statement@52 (not split_codes-&gt;ComputeFusedOneBitWithFilterIP(computer, code.cluster_id, code.one_bit_code, code.supplement_code, distances + i, lower_bounds + i, filter_inner_products + i, rate_context_ptr)) | 当前参考未静态绑定；见下方边界说明 |

| L68 | ctx-&gt;stats-&gt;AddDistance | if_statement@66 (ctx != nullptr and ctx-&gt;stats != nullptr) → if_statement@67 (ctx-&gt;track_distance_evaluations and count &gt; 0) | 当前参考未静态绑定；见下方边界说明 |

| L70 | ctx-&gt;stats-&gt;rabitq_filter_count.fetch_add | if_statement@66 (ctx != nullptr and ctx-&gt;stats != nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L72 | ctx-&gt;stats-&gt;rabitq_filter_fallback_full_count.fetch_add | if_statement@66 (ctx != nullptr and ctx-&gt;stats != nullptr) | 当前参考未静态绑定；见下方边界说明 |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L77"></a>

## `FlattenReorder::QueryFusedFullWithHint`

源码位置：`src/impl/reorder/flatten_reorder.cpp:77–126`。

先从签名确认输入、返回值和 const/override，再按完整函数体的条件阅读调用点。下表保留了本函数的显式调用以及 lambda 中的调用；进入下层时用“候选实现”定位，未解析的对象由源码静态类型/运行时类型确认。

### 完整函数

```cpp
void
FlattenReorder::QueryFusedFullWithHint(float* distances,
                                       const float* filter_inner_products,
                                       RaBitQSplitDataCellInterface* split_codes,
                                       const ComputerInterfacePtr& computer,
                                       const InnerIdType* ids,
                                       uint64_t count,
                                       QueryContext* ctx) const {
    uint32_t hint_full_count = 0;
    uint32_t fallback_full_count = 0;
    const bool exact_filter_ip_hint =
        split_codes->FusedFilterBits() >= 2 and not split_codes->UsesLegacyHnswFusedCodec();
    for (uint64_t i = 0; i < count; ++i) {
        const auto code = fused_graph_->GetCodeView(ids[i]);
        bool used_hint = false;
        if (exact_filter_ip_hint and IsFiniteRaBitQValue(filter_inner_products[i])) {
            used_hint = split_codes->ComputeFusedFullWithFilterIP(computer,
                                                                  code.cluster_id,
                                                                  code.one_bit_code,
                                                                  code.supplement_code,
                                                                  filter_inner_products[i],
                                                                  distances + i,
                                                                  nullptr);
        }
        if (used_hint) {
            ++hint_full_count;
        } else {
            ++fallback_full_count;
            if (not split_codes->ComputeFusedFull(computer,
                                                  code.cluster_id,
                                                  code.one_bit_code,
                                                  code.supplement_code,
                                                  distances + i,
                                                  nullptr)) {
                distances[i] = std::numeric_limits<float>::max();
            }
        }
    }
    if (ctx != nullptr and ctx->stats != nullptr) {
        if (ctx->track_distance_evaluations and count > 0) {
            ctx->stats->AddDistance(ctx->distance_phase, DistanceEvaluationBackend::RABITQ, count);
        }
        ctx->stats->rabitq_full_count.fetch_add(static_cast<uint32_t>(count),
                                                std::memory_order_relaxed);
        ctx->stats->rabitq_reorder_hint_full_count.fetch_add(hint_full_count,
                                                             std::memory_order_relaxed);
        ctx->stats->rabitq_reorder_fallback_full_count.fetch_add(fallback_full_count,
                                                                 std::memory_order_relaxed);
    }
}
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L88 | split_codes-&gt;FusedFilterBits | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L88 | split_codes-&gt;UsesLegacyHnswFusedCodec | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L90 | fused_graph_-&gt;GetCodeView | for_statement@89 i &lt; count | 当前参考未静态绑定；见下方边界说明 |

| L92 | IsFiniteRaBitQValue | for_statement@89 i &lt; count → if_statement@92 (exact_filter_ip_hint and IsFiniteRaBitQValue(filter_inner_products[i])) | 当前参考未静态绑定；见下方边界说明 |

| L93 | split_codes-&gt;ComputeFusedFullWithFilterIP | for_statement@89 i &lt; count → if_statement@92 (exact_filter_ip_hint and IsFiniteRaBitQValue(filter_inner_products[i])) | 当前参考未静态绑定；见下方边界说明 |

| L105 | split_codes-&gt;ComputeFusedFull | for_statement@89 i &lt; count → if_statement@101 (used_hint) [else 分支] → if_statement@105 (not split_codes-&gt;ComputeFusedFull(computer, code.cluster_id, code.one_bit_code, code.supplement_code, distances + i, nullptr)) | 当前参考未静态绑定；见下方边界说明 |

| L111 | std::numeric_limits&lt;float&gt;::max | for_statement@89 i &lt; count → if_statement@101 (used_hint) [else 分支] → if_statement@105 (not split_codes-&gt;ComputeFusedFull(computer, code.cluster_id, code.one_bit_code, code.supplement_code, distances + i, nullptr)) | 当前参考未静态绑定；见下方边界说明 |

| L117 | ctx-&gt;stats-&gt;AddDistance | if_statement@115 (ctx != nullptr and ctx-&gt;stats != nullptr) → if_statement@116 (ctx-&gt;track_distance_evaluations and count &gt; 0) | 当前参考未静态绑定；见下方边界说明 |

| L119 | ctx-&gt;stats-&gt;rabitq_full_count.fetch_add | if_statement@115 (ctx != nullptr and ctx-&gt;stats != nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L121 | ctx-&gt;stats-&gt;rabitq_reorder_hint_full_count.fetch_add | if_statement@115 (ctx != nullptr and ctx-&gt;stats != nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L123 | ctx-&gt;stats-&gt;rabitq_reorder_fallback_full_count.fetch_add | if_statement@115 (ctx != nullptr and ctx-&gt;stats != nullptr) | 当前参考未静态绑定；见下方边界说明 |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L130"></a>

## `add_reorder_distance_count`

源码位置：`src/impl/reorder/flatten_reorder.cpp:130–136`。

先从签名确认输入、返回值和 const/override，再按完整函数体的条件阅读调用点。下表保留了本函数的显式调用以及 lambda 中的调用；进入下层时用“候选实现”定位，未解析的对象由源码静态类型/运行时类型确认。

### 完整函数

```cpp
void
add_reorder_distance_count(QueryContext& ctx, uint64_t count) {
    if (ctx.stats != nullptr) {
        ctx.stats->reorder_distance_count.fetch_add(static_cast<uint32_t>(count),
                                                    std::memory_order_relaxed);
    }
}
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L133 | ctx.stats-&gt;reorder_distance_count.fetch_add | if_statement@132 (ctx.stats != nullptr) | 当前参考未静态绑定；见下方边界说明 |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L138"></a>

## `add_reorder_candidate_count`

源码位置：`src/impl/reorder/flatten_reorder.cpp:138–144`。

先从签名确认输入、返回值和 const/override，再按完整函数体的条件阅读调用点。下表保留了本函数的显式调用以及 lambda 中的调用；进入下层时用“候选实现”定位，未解析的对象由源码静态类型/运行时类型确认。

### 完整函数

```cpp
void
add_reorder_candidate_count(QueryContext& ctx, uint64_t count) {
    if (ctx.stats != nullptr) {
        ctx.stats->reorder_candidate_count.fetch_add(static_cast<uint32_t>(count),
                                                     std::memory_order_relaxed);
    }
}
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L141 | ctx.stats-&gt;reorder_candidate_count.fetch_add | if_statement@140 (ctx.stats != nullptr) | 当前参考未静态绑定；见下方边界说明 |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L146"></a>

## `add_reorder_lower_bound_probe_count`

源码位置：`src/impl/reorder/flatten_reorder.cpp:146–152`。

先从签名确认输入、返回值和 const/override，再按完整函数体的条件阅读调用点。下表保留了本函数的显式调用以及 lambda 中的调用；进入下层时用“候选实现”定位，未解析的对象由源码静态类型/运行时类型确认。

### 完整函数

```cpp
void
add_reorder_lower_bound_probe_count(QueryContext& ctx, uint64_t count) {
    if (ctx.stats != nullptr) {
        ctx.stats->reorder_lower_bound_probe_count.fetch_add(static_cast<uint32_t>(count),
                                                             std::memory_order_relaxed);
    }
}
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L149 | ctx.stats-&gt;reorder_lower_bound_probe_count.fetch_add | if_statement@148 (ctx.stats != nullptr) | 当前参考未静态绑定；见下方边界说明 |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L156"></a>

## `FlattenReorder::Reorder`

源码位置：`src/impl/reorder/flatten_reorder.cpp:156–417`。

检查具体精排类。BucketReorder 用 location_resolver 将 origin ID 变成桶/offset，批量 Query 后重建堆。FlattenReorder 使用扁平编码，也包含其他调用方支持的分支；IVF 传参见主讲解。

### 完整函数

```cpp
DistHeapPtr
FlattenReorder::Reorder(const vsag::DistHeapPtr& input,
                        const void* query,
                        int64_t topk,
                        QueryContext& ctx,
                        IteratorFilterContext* iter_ctx,
                        const DistanceRecordVector* rabitq_lower_bound_candidates,
                        const std::optional<float>& distance_threshold) {
    // set query allocator
    Allocator* query_allocator = select_query_allocator(ctx.alloc, allocator_);
    auto is_distance_eligible = [&distance_threshold](float distance) {
        return not distance_threshold.has_value() or
               (IsFiniteRaBitQValue(distance) and distance <= distance_threshold.value());
    };
    auto consume_if_ineligible = [&](float distance, InnerIdType id) {
        if (is_distance_eligible(distance)) {
            return false;
        }
        if (iter_ctx != nullptr) {
            iter_ctx->SetPoint(id);
        }
        return true;
    };
    const uint64_t heap_candidate_size = input == nullptr ? 0 : input->Size();
    if (rabitq_lower_bound_candidates == nullptr) {
        add_reorder_candidate_count(ctx, heap_candidate_size);
        topk = std::min(topk, static_cast<int64_t>(heap_candidate_size));
        auto reorder_heap = std::make_shared<StandardHeap<true, false>>(query_allocator, topk);
        auto computer_lease = AcquireQueryComputer(flatten_, query, &ctx);
        const auto& computer = computer_lease.computer;
        Vector<InnerIdType> ids(heap_candidate_size, query_allocator);
        Vector<float> dists(heap_candidate_size, query_allocator);
        const auto* candidate_result = input == nullptr ? nullptr : input->GetData();
        for (uint64_t i = 0; i < heap_candidate_size; ++i) {
            ids[i] = candidate_result[i].second;
        }
        add_reorder_distance_count(ctx, heap_candidate_size);
        {
            ScopedDistancePhase scoped(ctx, DistanceEvaluationPhase::RERANK);
            flatten_->Query(dists.data(), computer, ids.data(), heap_candidate_size, &ctx);
        }
        for (uint64_t i = 0; i < heap_candidate_size; ++i) {
            if (ctx.reasoning_ctx != nullptr) {
                ctx.reasoning_ctx->RecordReorder(
                    candidate_result[i].second, candidate_result[i].first, dists[i]);
            }
            if (consume_if_ineligible(dists[i], candidate_result[i].second)) {
                continue;
            }
            if (reorder_heap->Size() < topk || dists[i] < reorder_heap->Top().first) {
                reorder_heap->Push(dists[i], candidate_result[i].second);
                if (reorder_heap->Size() > topk) {
                    if (iter_ctx != nullptr) {
                        auto curr = reorder_heap->Top();
                        iter_ctx->AddDiscardNode(curr.first, curr.second);
                    }
                    if (ctx.reasoning_ctx != nullptr) {
                        ctx.reasoning_ctx->RecordReorderEviction(reorder_heap->Top().second, 0);
                    }
                    reorder_heap->Pop();
                }
            }
        }
        return reorder_heap;
    }

    const uint64_t rabitq_candidate_size =
        rabitq_lower_bound_candidates == nullptr ? 0 : rabitq_lower_bound_candidates->size();
    const uint64_t max_candidate_size = heap_candidate_size + rabitq_candidate_size;
    if (topk <= 0) {
        topk = static_cast<int64_t>(max_candidate_size);
    }
    auto computer_lease = AcquireQueryComputer(flatten_, query, &ctx);
    const auto& computer = computer_lease.computer;
    if (topk == 0 || max_candidate_size == 0) {
        return std::make_shared<StandardHeap<true, false>>(query_allocator, 0);
    }

    Vector<InnerIdType> all_ids(max_candidate_size, query_allocator);
    Vector<float> lower_bound_probe_dists(max_candidate_size, query_allocator);
    Vector<float> lower_bounds(max_candidate_size, query_allocator);
    UnorderedSet<InnerIdType> merged_ids(query_allocator);
    merged_ids.reserve(max_candidate_size);

    uint64_t candidate_size = 0;
    const auto* candidate_result = input == nullptr ? nullptr : input->GetData();
    for (uint64_t i = 0; i < heap_candidate_size; ++i) {
        const auto id = candidate_result[i].second;
        if (merged_ids.insert(id).second) {
            all_ids[candidate_size++] = id;
        }
    }
    const uint64_t heap_unique_size = candidate_size;
    if (heap_unique_size > 0) {
        add_reorder_lower_bound_probe_count(ctx, heap_unique_size);
        ScopedDistancePhase scoped_phase(ctx, DistanceEvaluationPhase::RERANK);
        flatten_->QueryWithDistanceLowerBound(lower_bound_probe_dists.data(),
                                              lower_bounds.data(),
                                              computer,
                                              all_ids.data(),
                                              heap_unique_size,
                                              &ctx);
    }

    if (rabitq_lower_bound_candidates != nullptr) {
        for (const auto& item : *rabitq_lower_bound_candidates) {
            if (merged_ids.insert(item.second).second) {
                all_ids[candidate_size] = item.second;
                lower_bound_probe_dists[candidate_size] = item.first;
                lower_bounds[candidate_size] = item.first;
                ++candidate_size;
            }
        }
    }

    add_reorder_candidate_count(ctx, candidate_size);

    topk = std::min(topk, static_cast<int64_t>(candidate_size));
    auto reorder_heap = std::make_shared<StandardHeap<true, false>>(query_allocator, topk);
    if (topk == 0 || candidate_size == 0) {
        return reorder_heap;
    }

    auto has_valid_lower_bound = [](float lower_bound) {
        return IsFiniteRaBitQValue(lower_bound) and lower_bound < std::numeric_limits<float>::max();
    };
    bool lower_bounds_available = true;
    for (uint64_t i = 0; i < candidate_size; ++i) {
        if (not has_valid_lower_bound(lower_bounds[i])) {
            lower_bounds_available = false;
            break;
        }
    }

    if (not lower_bounds_available) {
        add_reorder_distance_count(ctx, candidate_size);
        {
            ScopedDistancePhase scoped(ctx, DistanceEvaluationPhase::RERANK);
            flatten_->Query(
                lower_bound_probe_dists.data(), computer, all_ids.data(), candidate_size, &ctx);
        }
        for (uint64_t i = 0; i < candidate_size; ++i) {
            if (ctx.reasoning_ctx != nullptr) {
                ctx.reasoning_ctx->RecordReorder(
                    all_ids[i], lower_bounds[i], lower_bound_probe_dists[i]);
            }
            if (consume_if_ineligible(lower_bound_probe_dists[i], all_ids[i])) {
                continue;
            }
            if (reorder_heap->Size() < topk or
                lower_bound_probe_dists[i] < reorder_heap->Top().first) {
                reorder_heap->Push(lower_bound_probe_dists[i], all_ids[i]);
                if (reorder_heap->Size() > topk) {
                    if (iter_ctx != nullptr) {
                        auto curr = reorder_heap->Top();
                        iter_ctx->AddDiscardNode(curr.first, curr.second);
                    }
                    if (ctx.reasoning_ctx != nullptr) {
                        ctx.reasoning_ctx->RecordReorderEviction(reorder_heap->Top().second, 0);
                    }
                    reorder_heap->Pop();
                }
            }
        }
        return reorder_heap;
    }

    Vector<uint64_t> order(candidate_size, query_allocator);
    std::iota(order.begin(), order.end(), 0);
    std::sort(order.begin(), order.end(), [&lower_bounds](uint64_t lhs, uint64_t rhs) {
        return lower_bounds[lhs] < lower_bounds[rhs];
    });

    const uint64_t bootstrap_size = std::min<uint64_t>(static_cast<uint64_t>(topk), candidate_size);
    constexpr uint64_t batch_size = 256;
    const auto buffer_size = std::max<uint64_t>(bootstrap_size, batch_size);
    Vector<InnerIdType> ids(buffer_size, query_allocator);
    Vector<float> dists(buffer_size, query_allocator);
    Vector<float> hint_dists(buffer_size, query_allocator);
    Vector<uint64_t> batch_indices(buffer_size, query_allocator);

    for (uint64_t i = 0; i < bootstrap_size; ++i) {
        const auto idx = order[i];
        ids[i] = all_ids[idx];
        hint_dists[i] = idx < heap_unique_size ? lower_bound_probe_dists[idx]
                                               : std::numeric_limits<float>::max();
    }
    add_reorder_distance_count(ctx, bootstrap_size);
    {
        ScopedDistancePhase scoped(ctx, DistanceEvaluationPhase::RERANK);
        flatten_->QueryWithDistanceHint(
            dists.data(), hint_dists.data(), computer, ids.data(), bootstrap_size, &ctx);
    }
    for (uint64_t i = 0; i < bootstrap_size; ++i) {
        if (ctx.reasoning_ctx != nullptr) {
            const auto idx = order[i];
            ctx.reasoning_ctx->RecordReorder(ids[i], lower_bound_probe_dists[idx], dists[i]);
        }
        if (not consume_if_ineligible(dists[i], ids[i])) {
            reorder_heap->Push(dists[i], ids[i]);
        }
    }

    uint64_t cursor = bootstrap_size;
    while (cursor < candidate_size) {
        if (reorder_heap->Size() == topk &&
            lower_bounds[order[cursor]] >= reorder_heap->Top().first) {
            break;
        }

        const auto pruning_threshold = reorder_heap->Size() == topk
                                           ? reorder_heap->Top().first
                                           : std::numeric_limits<float>::max();
        uint64_t batch_count = 0;
        while (cursor < candidate_size && batch_count < batch_size) {
            const auto idx = order[cursor];
            if (lower_bounds[idx] >= pruning_threshold) {
                break;
            }
            ids[batch_count] = all_ids[idx];
            hint_dists[batch_count] = idx < heap_unique_size ? lower_bound_probe_dists[idx]
                                                             : std::numeric_limits<float>::max();
            batch_indices[batch_count] = idx;
            ++batch_count;
            ++cursor;
        }

        if (batch_count == 0) {
            break;
        }

        add_reorder_distance_count(ctx, batch_count);
        {
            ScopedDistancePhase scoped(ctx, DistanceEvaluationPhase::RERANK);
            flatten_->QueryWithDistanceHint(
                dists.data(), hint_dists.data(), computer, ids.data(), batch_count, &ctx);
        }
        for (uint64_t i = 0; i < batch_count; ++i) {
            if (ctx.reasoning_ctx != nullptr) {
                ctx.reasoning_ctx->RecordReorder(
                    ids[i], lower_bound_probe_dists[batch_indices[i]], dists[i]);
            }
            if (consume_if_ineligible(dists[i], ids[i])) {
                continue;
            }
            if (reorder_heap->Size() < topk or dists[i] < reorder_heap->Top().first) {
                reorder_heap->Push(dists[i], ids[i]);
                if (reorder_heap->Size() > topk) {
                    if (iter_ctx != nullptr) {
                        auto curr = reorder_heap->Top();
                        iter_ctx->AddDiscardNode(curr.first, curr.second);
                    }
                    if (ctx.reasoning_ctx != nullptr) {
                        ctx.reasoning_ctx->RecordReorderEviction(reorder_heap->Top().second, 0);
                    }
                    reorder_heap->Pop();
                }
            }
        }
    }
    return reorder_heap;
}
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L165 | select_query_allocator | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L167 | distance_threshold.has_value | lambda@166（定义体，执行时间取决于调用/调度） | 当前参考未静态绑定；见下方边界说明 |

| L168 | IsFiniteRaBitQValue | lambda@166（定义体，执行时间取决于调用/调度） | 当前参考未静态绑定；见下方边界说明 |

| L168 | distance_threshold.value | lambda@166（定义体，执行时间取决于调用/调度） | 当前参考未静态绑定；见下方边界说明 |

| L171 | is_distance_eligible | lambda@170（定义体，执行时间取决于调用/调度） → if_statement@171 (is_distance_eligible(distance)) | 当前参考未静态绑定；见下方边界说明 |

| L175 | iter_ctx-&gt;SetPoint | lambda@170（定义体，执行时间取决于调用/调度） → if_statement@174 (iter_ctx != nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L179 | input-&gt;Size | conditional_expression@179 input == nullptr | 当前参考未静态绑定；见下方边界说明 |

| L181 | add_reorder_candidate_count | if_statement@180 (rabitq_lower_bound_candidates == nullptr) | [add_reorder_candidate_count · L138](flatten_reorder.md#L138) |

| L182 | std::min | if_statement@180 (rabitq_lower_bound_candidates == nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L183 | std::make_shared&lt;StandardHeap&lt;true, false&gt;&gt; | if_statement@180 (rabitq_lower_bound_candidates == nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L184 | AcquireQueryComputer | if_statement@180 (rabitq_lower_bound_candidates == nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L188 | input-&gt;GetData | if_statement@180 (rabitq_lower_bound_candidates == nullptr) → conditional_expression@188 input == nullptr | 当前参考未静态绑定；见下方边界说明 |

| L192 | add_reorder_distance_count | if_statement@180 (rabitq_lower_bound_candidates == nullptr) | [add_reorder_distance_count · L130](flatten_reorder.md#L130) |

| L195 | flatten_-&gt;Query | if_statement@180 (rabitq_lower_bound_candidates == nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L195 | dists.data | if_statement@180 (rabitq_lower_bound_candidates == nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L195 | ids.data | if_statement@180 (rabitq_lower_bound_candidates == nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L199 | ctx.reasoning_ctx-&gt;RecordReorder | if_statement@180 (rabitq_lower_bound_candidates == nullptr) → for_statement@197 i &lt; heap_candidate_size → if_statement@198 (ctx.reasoning_ctx != nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L202 | consume_if_ineligible | if_statement@180 (rabitq_lower_bound_candidates == nullptr) → for_statement@197 i &lt; heap_candidate_size → if_statement@202 (consume_if_ineligible(dists[i], candidate_result[i].second)) | 当前参考未静态绑定；见下方边界说明 |

| L205 | reorder_heap-&gt;Size | if_statement@180 (rabitq_lower_bound_candidates == nullptr) → for_statement@197 i &lt; heap_candidate_size → if_statement@205 (reorder_heap-&gt;Size() &lt; topk &#124;&#124; dists[i] &lt; reorder_heap-&gt;Top().first) | 当前参考未静态绑定；见下方边界说明 |

| L205 | reorder_heap-&gt;Top | if_statement@180 (rabitq_lower_bound_candidates == nullptr) → for_statement@197 i &lt; heap_candidate_size → if_statement@205 (reorder_heap-&gt;Size() &lt; topk &#124;&#124; dists[i] &lt; reorder_heap-&gt;Top().first) | 当前参考未静态绑定；见下方边界说明 |

| L206 | reorder_heap-&gt;Push | if_statement@180 (rabitq_lower_bound_candidates == nullptr) → for_statement@197 i &lt; heap_candidate_size → if_statement@205 (reorder_heap-&gt;Size() &lt; topk &#124;&#124; dists[i] &lt; reorder_heap-&gt;Top().first) | 当前参考未静态绑定；见下方边界说明 |

| L207 | reorder_heap-&gt;Size | if_statement@180 (rabitq_lower_bound_candidates == nullptr) → for_statement@197 i &lt; heap_candidate_size → if_statement@205 (reorder_heap-&gt;Size() &lt; topk &#124;&#124; dists[i] &lt; reorder_heap-&gt;Top().first) → if_statement@207 (reorder_heap-&gt;Size() &gt; topk) | 当前参考未静态绑定；见下方边界说明 |

| L209 | reorder_heap-&gt;Top | if_statement@180 (rabitq_lower_bound_candidates == nullptr) → for_statement@197 i &lt; heap_candidate_size → if_statement@205 (reorder_heap-&gt;Size() &lt; topk &#124;&#124; dists[i] &lt; reorder_heap-&gt;Top().first) → if_statement@207 (reorder_heap-&gt;Size() &gt; topk) → if_statement@208 (iter_ctx != nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L210 | iter_ctx-&gt;AddDiscardNode | if_statement@180 (rabitq_lower_bound_candidates == nullptr) → for_statement@197 i &lt; heap_candidate_size → if_statement@205 (reorder_heap-&gt;Size() &lt; topk &#124;&#124; dists[i] &lt; reorder_heap-&gt;Top().first) → if_statement@207 (reorder_heap-&gt;Size() &gt; topk) → if_statement@208 (iter_ctx != nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L213 | ctx.reasoning_ctx-&gt;RecordReorderEviction | if_statement@180 (rabitq_lower_bound_candidates == nullptr) → for_statement@197 i &lt; heap_candidate_size → if_statement@205 (reorder_heap-&gt;Size() &lt; topk &#124;&#124; dists[i] &lt; reorder_heap-&gt;Top().first) → if_statement@207 (reorder_heap-&gt;Size() &gt; topk) → if_statement@212 (ctx.reasoning_ctx != nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L213 | reorder_heap-&gt;Top | if_statement@180 (rabitq_lower_bound_candidates == nullptr) → for_statement@197 i &lt; heap_candidate_size → if_statement@205 (reorder_heap-&gt;Size() &lt; topk &#124;&#124; dists[i] &lt; reorder_heap-&gt;Top().first) → if_statement@207 (reorder_heap-&gt;Size() &gt; topk) → if_statement@212 (ctx.reasoning_ctx != nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L215 | reorder_heap-&gt;Pop | if_statement@180 (rabitq_lower_bound_candidates == nullptr) → for_statement@197 i &lt; heap_candidate_size → if_statement@205 (reorder_heap-&gt;Size() &lt; topk &#124;&#124; dists[i] &lt; reorder_heap-&gt;Top().first) → if_statement@207 (reorder_heap-&gt;Size() &gt; topk) | 当前参考未静态绑定；见下方边界说明 |

| L223 | rabitq_lower_bound_candidates-&gt;size | conditional_expression@223 rabitq_lower_bound_candidates == nullptr | 当前参考未静态绑定；见下方边界说明 |

| L228 | AcquireQueryComputer | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L231 | std::make_shared&lt;StandardHeap&lt;true, false&gt;&gt; | if_statement@230 (topk == 0 &#124;&#124; max_candidate_size == 0) | 当前参考未静态绑定；见下方边界说明 |

| L238 | merged_ids.reserve | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L241 | input-&gt;GetData | conditional_expression@241 input == nullptr | 当前参考未静态绑定；见下方边界说明 |

| L244 | merged_ids.insert | for_statement@242 i &lt; heap_candidate_size → if_statement@244 (merged_ids.insert(id).second) | 当前参考未静态绑定；见下方边界说明 |

| L250 | add_reorder_lower_bound_probe_count | if_statement@249 (heap_unique_size &gt; 0) | [add_reorder_lower_bound_probe_count · L146](flatten_reorder.md#L146) |

| L252 | flatten_-&gt;QueryWithDistanceLowerBound | if_statement@249 (heap_unique_size &gt; 0) | 当前参考未静态绑定；见下方边界说明 |

| L252 | lower_bound_probe_dists.data | if_statement@249 (heap_unique_size &gt; 0) | 当前参考未静态绑定；见下方边界说明 |

| L253 | lower_bounds.data | if_statement@249 (heap_unique_size &gt; 0) | 当前参考未静态绑定；见下方边界说明 |

| L255 | all_ids.data | if_statement@249 (heap_unique_size &gt; 0) | 当前参考未静态绑定；见下方边界说明 |

| L262 | merged_ids.insert | if_statement@260 (rabitq_lower_bound_candidates != nullptr) → for_range_loop@261 → if_statement@262 (merged_ids.insert(item.second).second) | 当前参考未静态绑定；见下方边界说明 |

| L271 | add_reorder_candidate_count | 函数本体；短路求值/提前返回见源码 | [add_reorder_candidate_count · L138](flatten_reorder.md#L138) |

| L273 | std::min | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L274 | std::make_shared&lt;StandardHeap&lt;true, false&gt;&gt; | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L280 | IsFiniteRaBitQValue | lambda@279（定义体，执行时间取决于调用/调度） | 当前参考未静态绑定；见下方边界说明 |

| L280 | std::numeric_limits&lt;float&gt;::max | lambda@279（定义体，执行时间取决于调用/调度） | 当前参考未静态绑定；见下方边界说明 |

| L284 | has_valid_lower_bound | for_statement@283 i &lt; candidate_size → if_statement@284 (not has_valid_lower_bound(lower_bounds[i])) | 当前参考未静态绑定；见下方边界说明 |

| L291 | add_reorder_distance_count | if_statement@290 (not lower_bounds_available) | [add_reorder_distance_count · L130](flatten_reorder.md#L130) |

| L294 | flatten_-&gt;Query | if_statement@290 (not lower_bounds_available) | 当前参考未静态绑定；见下方边界说明 |

| L295 | lower_bound_probe_dists.data | if_statement@290 (not lower_bounds_available) | 当前参考未静态绑定；见下方边界说明 |

| L295 | all_ids.data | if_statement@290 (not lower_bounds_available) | 当前参考未静态绑定；见下方边界说明 |

| L299 | ctx.reasoning_ctx-&gt;RecordReorder | if_statement@290 (not lower_bounds_available) → for_statement@297 i &lt; candidate_size → if_statement@298 (ctx.reasoning_ctx != nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L302 | consume_if_ineligible | if_statement@290 (not lower_bounds_available) → for_statement@297 i &lt; candidate_size → if_statement@302 (consume_if_ineligible(lower_bound_probe_dists[i], all_ids[i])) | 当前参考未静态绑定；见下方边界说明 |

| L305 | reorder_heap-&gt;Size | if_statement@290 (not lower_bounds_available) → for_statement@297 i &lt; candidate_size → if_statement@305 (reorder_heap-&gt;Size() &lt; topk or lower_bound_probe_dists[i] &lt; reorder_heap-&gt;Top().first) | 当前参考未静态绑定；见下方边界说明 |

| L306 | reorder_heap-&gt;Top | if_statement@290 (not lower_bounds_available) → for_statement@297 i &lt; candidate_size → if_statement@305 (reorder_heap-&gt;Size() &lt; topk or lower_bound_probe_dists[i] &lt; reorder_heap-&gt;Top().first) | 当前参考未静态绑定；见下方边界说明 |

| L307 | reorder_heap-&gt;Push | if_statement@290 (not lower_bounds_available) → for_statement@297 i &lt; candidate_size → if_statement@305 (reorder_heap-&gt;Size() &lt; topk or lower_bound_probe_dists[i] &lt; reorder_heap-&gt;Top().first) | 当前参考未静态绑定；见下方边界说明 |

| L308 | reorder_heap-&gt;Size | if_statement@290 (not lower_bounds_available) → for_statement@297 i &lt; candidate_size → if_statement@305 (reorder_heap-&gt;Size() &lt; topk or lower_bound_probe_dists[i] &lt; reorder_heap-&gt;Top().first) → if_statement@308 (reorder_heap-&gt;Size() &gt; topk) | 当前参考未静态绑定；见下方边界说明 |

| L310 | reorder_heap-&gt;Top | if_statement@290 (not lower_bounds_available) → for_statement@297 i &lt; candidate_size → if_statement@305 (reorder_heap-&gt;Size() &lt; topk or lower_bound_probe_dists[i] &lt; reorder_heap-&gt;Top().first) → if_statement@308 (reorder_heap-&gt;Size() &gt; topk) → if_statement@309 (iter_ctx != nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L311 | iter_ctx-&gt;AddDiscardNode | if_statement@290 (not lower_bounds_available) → for_statement@297 i &lt; candidate_size → if_statement@305 (reorder_heap-&gt;Size() &lt; topk or lower_bound_probe_dists[i] &lt; reorder_heap-&gt;Top().first) → if_statement@308 (reorder_heap-&gt;Size() &gt; topk) → if_statement@309 (iter_ctx != nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L314 | ctx.reasoning_ctx-&gt;RecordReorderEviction | if_statement@290 (not lower_bounds_available) → for_statement@297 i &lt; candidate_size → if_statement@305 (reorder_heap-&gt;Size() &lt; topk or lower_bound_probe_dists[i] &lt; reorder_heap-&gt;Top().first) → if_statement@308 (reorder_heap-&gt;Size() &gt; topk) → if_statement@313 (ctx.reasoning_ctx != nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L314 | reorder_heap-&gt;Top | if_statement@290 (not lower_bounds_available) → for_statement@297 i &lt; candidate_size → if_statement@305 (reorder_heap-&gt;Size() &lt; topk or lower_bound_probe_dists[i] &lt; reorder_heap-&gt;Top().first) → if_statement@308 (reorder_heap-&gt;Size() &gt; topk) → if_statement@313 (ctx.reasoning_ctx != nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L316 | reorder_heap-&gt;Pop | if_statement@290 (not lower_bounds_available) → for_statement@297 i &lt; candidate_size → if_statement@305 (reorder_heap-&gt;Size() &lt; topk or lower_bound_probe_dists[i] &lt; reorder_heap-&gt;Top().first) → if_statement@308 (reorder_heap-&gt;Size() &gt; topk) | 当前参考未静态绑定；见下方边界说明 |

| L324 | std::iota | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L324 | order.begin | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L324 | order.end | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L325 | std::sort | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L325 | order.begin | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L325 | order.end | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L329 | std::min&lt;uint64_t&gt; | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L331 | std::max&lt;uint64_t&gt; | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L341 | std::numeric_limits&lt;float&gt;::max | for_statement@337 i &lt; bootstrap_size → conditional_expression@340 idx &lt; heap_unique_size | 当前参考未静态绑定；见下方边界说明 |

| L343 | add_reorder_distance_count | 函数本体；短路求值/提前返回见源码 | [add_reorder_distance_count · L130](flatten_reorder.md#L130) |

| L346 | flatten_-&gt;QueryWithDistanceHint | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L347 | dists.data | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L347 | hint_dists.data | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L347 | ids.data | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L352 | ctx.reasoning_ctx-&gt;RecordReorder | for_statement@349 i &lt; bootstrap_size → if_statement@350 (ctx.reasoning_ctx != nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L354 | consume_if_ineligible | for_statement@349 i &lt; bootstrap_size → if_statement@354 (not consume_if_ineligible(dists[i], ids[i])) | 当前参考未静态绑定；见下方边界说明 |

| L355 | reorder_heap-&gt;Push | for_statement@349 i &lt; bootstrap_size → if_statement@354 (not consume_if_ineligible(dists[i], ids[i])) | 当前参考未静态绑定；见下方边界说明 |

| L361 | reorder_heap-&gt;Size | while_statement@360 (cursor &lt; candidate_size) → if_statement@361 (reorder_heap-&gt;Size() == topk && lower_bounds[order[cursor]] &gt;= reorder_heap-&gt;Top().first) | 当前参考未静态绑定；见下方边界说明 |

| L362 | reorder_heap-&gt;Top | while_statement@360 (cursor &lt; candidate_size) → if_statement@361 (reorder_heap-&gt;Size() == topk && lower_bounds[order[cursor]] &gt;= reorder_heap-&gt;Top().first) | 当前参考未静态绑定；见下方边界说明 |

| L366 | reorder_heap-&gt;Size | while_statement@360 (cursor &lt; candidate_size) → conditional_expression@366 reorder_heap-&gt;Size() == topk | 当前参考未静态绑定；见下方边界说明 |

| L367 | reorder_heap-&gt;Top | while_statement@360 (cursor &lt; candidate_size) → conditional_expression@366 reorder_heap-&gt;Size() == topk | 当前参考未静态绑定；见下方边界说明 |

| L368 | std::numeric_limits&lt;float&gt;::max | while_statement@360 (cursor &lt; candidate_size) → conditional_expression@366 reorder_heap-&gt;Size() == topk | 当前参考未静态绑定；见下方边界说明 |

| L377 | std::numeric_limits&lt;float&gt;::max | while_statement@360 (cursor &lt; candidate_size) → while_statement@370 (cursor &lt; candidate_size && batch_count &lt; batch_size) → conditional_expression@376 idx &lt; heap_unique_size | 当前参考未静态绑定；见下方边界说明 |

| L387 | add_reorder_distance_count | while_statement@360 (cursor &lt; candidate_size) | [add_reorder_distance_count · L130](flatten_reorder.md#L130) |

| L390 | flatten_-&gt;QueryWithDistanceHint | while_statement@360 (cursor &lt; candidate_size) | 当前参考未静态绑定；见下方边界说明 |

| L391 | dists.data | while_statement@360 (cursor &lt; candidate_size) | 当前参考未静态绑定；见下方边界说明 |

| L391 | hint_dists.data | while_statement@360 (cursor &lt; candidate_size) | 当前参考未静态绑定；见下方边界说明 |

| L391 | ids.data | while_statement@360 (cursor &lt; candidate_size) | 当前参考未静态绑定；见下方边界说明 |

| L395 | ctx.reasoning_ctx-&gt;RecordReorder | while_statement@360 (cursor &lt; candidate_size) → for_statement@393 i &lt; batch_count → if_statement@394 (ctx.reasoning_ctx != nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L398 | consume_if_ineligible | while_statement@360 (cursor &lt; candidate_size) → for_statement@393 i &lt; batch_count → if_statement@398 (consume_if_ineligible(dists[i], ids[i])) | 当前参考未静态绑定；见下方边界说明 |

| L401 | reorder_heap-&gt;Size | while_statement@360 (cursor &lt; candidate_size) → for_statement@393 i &lt; batch_count → if_statement@401 (reorder_heap-&gt;Size() &lt; topk or dists[i] &lt; reorder_heap-&gt;Top().first) | 当前参考未静态绑定；见下方边界说明 |

| L401 | reorder_heap-&gt;Top | while_statement@360 (cursor &lt; candidate_size) → for_statement@393 i &lt; batch_count → if_statement@401 (reorder_heap-&gt;Size() &lt; topk or dists[i] &lt; reorder_heap-&gt;Top().first) | 当前参考未静态绑定；见下方边界说明 |

| L402 | reorder_heap-&gt;Push | while_statement@360 (cursor &lt; candidate_size) → for_statement@393 i &lt; batch_count → if_statement@401 (reorder_heap-&gt;Size() &lt; topk or dists[i] &lt; reorder_heap-&gt;Top().first) | 当前参考未静态绑定；见下方边界说明 |

| L403 | reorder_heap-&gt;Size | while_statement@360 (cursor &lt; candidate_size) → for_statement@393 i &lt; batch_count → if_statement@401 (reorder_heap-&gt;Size() &lt; topk or dists[i] &lt; reorder_heap-&gt;Top().first) → if_statement@403 (reorder_heap-&gt;Size() &gt; topk) | 当前参考未静态绑定；见下方边界说明 |

| L405 | reorder_heap-&gt;Top | while_statement@360 (cursor &lt; candidate_size) → for_statement@393 i &lt; batch_count → if_statement@401 (reorder_heap-&gt;Size() &lt; topk or dists[i] &lt; reorder_heap-&gt;Top().first) → if_statement@403 (reorder_heap-&gt;Size() &gt; topk) → if_statement@404 (iter_ctx != nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L406 | iter_ctx-&gt;AddDiscardNode | while_statement@360 (cursor &lt; candidate_size) → for_statement@393 i &lt; batch_count → if_statement@401 (reorder_heap-&gt;Size() &lt; topk or dists[i] &lt; reorder_heap-&gt;Top().first) → if_statement@403 (reorder_heap-&gt;Size() &gt; topk) → if_statement@404 (iter_ctx != nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L409 | ctx.reasoning_ctx-&gt;RecordReorderEviction | while_statement@360 (cursor &lt; candidate_size) → for_statement@393 i &lt; batch_count → if_statement@401 (reorder_heap-&gt;Size() &lt; topk or dists[i] &lt; reorder_heap-&gt;Top().first) → if_statement@403 (reorder_heap-&gt;Size() &gt; topk) → if_statement@408 (ctx.reasoning_ctx != nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L409 | reorder_heap-&gt;Top | while_statement@360 (cursor &lt; candidate_size) → for_statement@393 i &lt; batch_count → if_statement@401 (reorder_heap-&gt;Size() &lt; topk or dists[i] &lt; reorder_heap-&gt;Top().first) → if_statement@403 (reorder_heap-&gt;Size() &gt; topk) → if_statement@408 (ctx.reasoning_ctx != nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L411 | reorder_heap-&gt;Pop | while_statement@360 (cursor &lt; candidate_size) → for_statement@393 i &lt; batch_count → if_statement@401 (reorder_heap-&gt;Size() &lt; topk or dists[i] &lt; reorder_heap-&gt;Top().first) → if_statement@403 (reorder_heap-&gt;Size() &gt; topk) | 当前参考未静态绑定；见下方边界说明 |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L419"></a>

## `FlattenReorder::ReorderFused`

源码位置：`src/impl/reorder/flatten_reorder.cpp:419–775`。

先从签名确认输入、返回值和 const/override，再按完整函数体的条件阅读调用点。下表保留了本函数的显式调用以及 lambda 中的调用；进入下层时用“候选实现”定位，未解析的对象由源码静态类型/运行时类型确认。

### 完整函数

```cpp
DistHeapPtr
FlattenReorder::ReorderFused(const vsag::DistHeapPtr& input,
                             const void* query,
                             int64_t topk,
                             QueryContext& ctx,
                             IteratorFilterContext* iter_ctx,
                             const RaBitQCandidateVector* rabitq_lower_bound_candidates,
                             const std::optional<float>& distance_threshold) {
    auto* split_codes = dynamic_cast<RaBitQSplitDataCellInterface*>(flatten_.get());
    CHECK_ARGUMENT(  // NOLINT(readability-simplify-boolean-expr)
        fused_graph_ != nullptr and split_codes != nullptr,
        "fused reorder requires fused graph and RaBitQ split codes");
    // set query allocator
    Allocator* query_allocator = select_query_allocator(ctx.alloc, allocator_);
    auto is_distance_eligible = [&distance_threshold](float distance) {
        return not distance_threshold.has_value() or
               (IsFiniteRaBitQValue(distance) and distance <= distance_threshold.value());
    };
    auto consume_if_ineligible = [&](float distance, InnerIdType id) {
        if (is_distance_eligible(distance)) {
            return false;
        }
        if (iter_ctx != nullptr) {
            iter_ctx->SetPoint(id);
        }
        return true;
    };
    const auto has_valid_distance = [](float distance) {
        return IsFiniteRaBitQValue(distance) and distance < std::numeric_limits<float>::max();
    };
    const uint64_t heap_candidate_size = input == nullptr ? 0 : input->Size();
    const auto add_iterator_discard = [iter_ctx](float distance, InnerIdType id) {
        if (iter_ctx != nullptr) {
            iter_ctx->AddDiscardNode(distance, id);
        }
    };
    if (rabitq_lower_bound_candidates == nullptr) {
        topk = std::min(topk, static_cast<int64_t>(heap_candidate_size));
        auto reorder_heap = std::make_shared<StandardHeap<true, false>>(query_allocator, topk);
        auto computer = split_codes->FactoryFusedComputer(query);
        Vector<InnerIdType> ids(heap_candidate_size, query_allocator);
        Vector<float> dists(heap_candidate_size, query_allocator);
        const auto* candidate_result = input == nullptr ? nullptr : input->GetData();
        for (uint64_t i = 0; i < heap_candidate_size; ++i) {
            ids[i] = candidate_result[i].second;
        }
        add_reorder_distance_count(ctx, heap_candidate_size);
        {
            ScopedDistancePhase scoped(ctx, DistanceEvaluationPhase::RERANK);
            for (uint64_t i = 0; i < heap_candidate_size; ++i) {
                const auto code = fused_graph_->GetCodeView(ids[i]);
                if (not split_codes->ComputeFusedFull(computer,
                                                      code.cluster_id,
                                                      code.one_bit_code,
                                                      code.supplement_code,
                                                      dists.data() + i,
                                                      &ctx)) {
                    dists[i] = std::numeric_limits<float>::max();
                }
            }
        }
        for (uint64_t i = 0; i < heap_candidate_size; ++i) {
            if (not has_valid_distance(dists[i])) {
                continue;
            }
            if (ctx.reasoning_ctx != nullptr) {
                ctx.reasoning_ctx->RecordReorder(
                    candidate_result[i].second, candidate_result[i].first, dists[i]);
            }
            if (consume_if_ineligible(dists[i], candidate_result[i].second)) {
                continue;
            }
            if (reorder_heap->Size() < topk || dists[i] < reorder_heap->Top().first) {
                reorder_heap->Push(dists[i], candidate_result[i].second);
                if (reorder_heap->Size() > topk) {
                    const auto curr = reorder_heap->Top();
                    add_iterator_discard(curr.first, curr.second);
                    if (ctx.reasoning_ctx != nullptr) {
                        ctx.reasoning_ctx->RecordReorderEviction(reorder_heap->Top().second, 0);
                    }
                    reorder_heap->Pop();
                }
            } else {
                add_iterator_discard(dists[i], candidate_result[i].second);
            }
        }
        return reorder_heap;
    }

    const uint64_t rabitq_candidate_size = rabitq_lower_bound_candidates->size();
    const uint64_t max_candidate_size = heap_candidate_size + rabitq_candidate_size;
    if (topk <= 0) {
        topk = static_cast<int64_t>(max_candidate_size);
    }
    if (topk == 0 or max_candidate_size == 0) {
        return std::make_shared<StandardHeap<true, false>>(query_allocator, 0);
    }

    Vector<InnerIdType> all_ids(max_candidate_size, query_allocator);
    Vector<float> lower_bound_probe_dists(max_candidate_size, query_allocator);
    Vector<float> lower_bounds(max_candidate_size, query_allocator);
    Vector<float> filter_inner_products(
        max_candidate_size, std::numeric_limits<float>::quiet_NaN(), query_allocator);
    Vector<float> full_distances(
        max_candidate_size, std::numeric_limits<float>::quiet_NaN(), query_allocator);
    UnorderedMap<InnerIdType, uint64_t> merged_ids(query_allocator);
    merged_ids.reserve(max_candidate_size);

    uint64_t candidate_size = 0;
    for (const auto& item : *rabitq_lower_bound_candidates) {
        const auto [iter, inserted] = merged_ids.emplace(item.id, candidate_size);
        if (inserted) {
            all_ids[candidate_size] = item.id;
            lower_bound_probe_dists[candidate_size] = item.lower_bound;
            lower_bounds[candidate_size] = item.lower_bound;
            filter_inner_products[candidate_size] = item.filter_inner_product;
            full_distances[candidate_size] = item.full_distance;
            ++candidate_size;
            continue;
        }

        const auto idx = iter->second;
        if (has_valid_distance(item.lower_bound) and
            (not has_valid_distance(lower_bounds[idx]) or item.lower_bound < lower_bounds[idx])) {
            lower_bound_probe_dists[idx] = item.lower_bound;
            lower_bounds[idx] = item.lower_bound;
        }
        if (not IsFiniteRaBitQValue(filter_inner_products[idx]) and
            IsFiniteRaBitQValue(item.filter_inner_product)) {
            filter_inner_products[idx] = item.filter_inner_product;
        }
        if (not has_valid_distance(full_distances[idx]) and
            has_valid_distance(item.full_distance)) {
            full_distances[idx] = item.full_distance;
        }
    }
    const uint64_t hinted_candidate_size = candidate_size;

    const auto* candidate_result = input == nullptr ? nullptr : input->GetData();
    for (uint64_t i = 0; i < heap_candidate_size; ++i) {
        const auto id = candidate_result[i].second;
        if (merged_ids.emplace(id, candidate_size).second) {
            all_ids[candidate_size++] = id;
        }
    }

    ComputerInterfacePtr computer{nullptr};
    const auto ensure_computer = [&]() -> const ComputerInterfacePtr& {
        if (computer == nullptr) {
            computer = split_codes->FactoryFusedComputer(query);
        }
        return computer;
    };

    const uint64_t unhinted_candidate_size = candidate_size - hinted_candidate_size;
    if (unhinted_candidate_size > 0) {
        add_reorder_lower_bound_probe_count(ctx, unhinted_candidate_size);
        ScopedDistancePhase scoped_phase(ctx, DistanceEvaluationPhase::RERANK);
        QueryFusedLowerBound(lower_bound_probe_dists.data() + hinted_candidate_size,
                             lower_bounds.data() + hinted_candidate_size,
                             filter_inner_products.data() + hinted_candidate_size,
                             split_codes,
                             ensure_computer(),
                             all_ids.data() + hinted_candidate_size,
                             unhinted_candidate_size,
                             &ctx);
    }

    topk = std::min(topk, static_cast<int64_t>(candidate_size));
    auto reorder_heap = std::make_shared<StandardHeap<true, false>>(query_allocator, topk);
    if (topk == 0 or candidate_size == 0) {
        return reorder_heap;
    }

    const auto push_full_distance = [&](uint64_t idx, float distance) {
        if (not has_valid_distance(distance)) {
            return;
        }
        if (ctx.reasoning_ctx != nullptr) {
            ctx.reasoning_ctx->RecordReorder(all_ids[idx], lower_bound_probe_dists[idx], distance);
        }
        if (consume_if_ineligible(distance, all_ids[idx])) {
            return;
        }
        if (reorder_heap->Size() < topk or distance < reorder_heap->Top().first) {
            reorder_heap->Push(distance, all_ids[idx]);
            if (reorder_heap->Size() > topk) {
                const auto curr = reorder_heap->Top();
                add_iterator_discard(curr.first, curr.second);
                if (ctx.reasoning_ctx != nullptr) {
                    ctx.reasoning_ctx->RecordReorderEviction(curr.second, 0);
                }
                reorder_heap->Pop();
            }
        } else {
            add_iterator_discard(distance, all_ids[idx]);
        }
    };

    bool all_full_distances_available = true;
    for (uint64_t i = 0; i < candidate_size; ++i) {
        if (not has_valid_distance(full_distances[i])) {
            all_full_distances_available = false;
            break;
        }
    }
    if (all_full_distances_available) {
        for (uint64_t i = 0; i < candidate_size; ++i) {
            push_full_distance(i, full_distances[i]);
        }
        return reorder_heap;
    }

    bool lower_bounds_available = true;
    for (uint64_t i = 0; i < candidate_size; ++i) {
        if (not has_valid_distance(lower_bounds[i])) {
            lower_bounds_available = false;
            break;
        }
    }

    constexpr uint64_t batch_size = 256;
    const uint64_t missing_buffer_size = lower_bounds_available ? batch_size : candidate_size;
    Vector<InnerIdType> missing_ids(missing_buffer_size, query_allocator);
    Vector<float> missing_hints(missing_buffer_size, query_allocator);
    Vector<float> missing_dists(missing_buffer_size, query_allocator);
    Vector<uint64_t> missing_positions(missing_buffer_size, query_allocator);

    const auto compute_missing_full_distances =
        [&](const uint64_t* indices, uint64_t count, float* output) {
            uint64_t missing_count = 0;
            for (uint64_t i = 0; i < count; ++i) {
                const auto idx = indices == nullptr ? i : indices[i];
                if (has_valid_distance(full_distances[idx])) {
                    output[i] = full_distances[idx];
                    continue;
                }
                missing_ids[missing_count] = all_ids[idx];
                missing_hints[missing_count] = filter_inner_products[idx];
                missing_positions[missing_count] = i;
                ++missing_count;
            }
            if (missing_count == 0) {
                return;
            }
            add_reorder_distance_count(ctx, missing_count);
            {
                ScopedDistancePhase scoped(ctx, DistanceEvaluationPhase::RERANK);
                QueryFusedFullWithHint(missing_dists.data(),
                                       missing_hints.data(),
                                       split_codes,
                                       ensure_computer(),
                                       missing_ids.data(),
                                       missing_count,
                                       &ctx);
            }
            for (uint64_t i = 0; i < missing_count; ++i) {
                const auto position = missing_positions[i];
                const auto idx = indices == nullptr ? position : indices[position];
                output[position] = missing_dists[i];
                full_distances[idx] = missing_dists[i];
            }
        };

    if (not lower_bounds_available) {
        compute_missing_full_distances(nullptr, candidate_size, full_distances.data());
        for (uint64_t i = 0; i < candidate_size; ++i) {
            push_full_distance(i, full_distances[i]);
        }
        return reorder_heap;
    }

    Vector<uint64_t> order(candidate_size, query_allocator);
    std::iota(order.begin(), order.end(), 0);
    std::sort(order.begin(), order.end(), [&lower_bounds](uint64_t lhs, uint64_t rhs) {
        return lower_bounds[lhs] < lower_bounds[rhs];
    });

    Vector<float> batch_dists(batch_size, query_allocator);
    Vector<uint64_t> batch_indices(batch_size, query_allocator);

    // Seed the exact threshold with every full distance produced during traversal.  Missing
    // candidates then load their supplement only while their lower bound can still enter top-k.
    for (uint64_t i = 0; i < candidate_size; ++i) {
        if (has_valid_distance(full_distances[i])) {
            push_full_distance(i, full_distances[i]);
        }
    }

    uint64_t cursor = 0;
    while (cursor < candidate_size) {
        while (cursor < candidate_size and has_valid_distance(full_distances[order[cursor]])) {
            ++cursor;
        }
        if (cursor == candidate_size) {
            break;
        }
        const bool heap_full = reorder_heap->Size() == static_cast<uint64_t>(topk);
        const float threshold =
            heap_full ? reorder_heap->Top().first : std::numeric_limits<float>::max();
        if (heap_full and lower_bounds[order[cursor]] >= threshold) {
            break;
        }
        const uint64_t batch_limit =
            heap_full ? batch_size
                      : std::min<uint64_t>(batch_size,
                                           static_cast<uint64_t>(topk) - reorder_heap->Size());
        uint64_t batch_count = 0;
        while (cursor < candidate_size and batch_count < batch_limit) {
            const auto idx = order[cursor];
            if (has_valid_distance(full_distances[idx])) {
                ++cursor;
                continue;
            }
            if (heap_full and lower_bounds[idx] >= threshold) {
                break;
            }
            batch_indices[batch_count++] = idx;
            ++cursor;
        }

        if (batch_count == 0) {
            break;
        }

        compute_missing_full_distances(batch_indices.data(), batch_count, batch_dists.data());
        for (uint64_t i = 0; i < batch_count; ++i) {
            push_full_distance(batch_indices[i], batch_dists[i]);
        }
    }
    if (iter_ctx != nullptr) {
        // Iterator pages can later expose discard values directly (including on the final drain),
        // so every buffered candidate must carry a full distance rather than a lower bound.
        while (cursor < candidate_size) {
            uint64_t batch_count = 0;
            while (cursor < candidate_size and batch_count < batch_size) {
                const auto idx = order[cursor++];
                if (not has_valid_distance(full_distances[idx])) {
                    batch_indices[batch_count++] = idx;
                }
            }
            if (batch_count == 0) {
                continue;
            }
            compute_missing_full_distances(batch_indices.data(), batch_count, batch_dists.data());
            for (uint64_t i = 0; i < batch_count; ++i) {
                const auto idx = batch_indices[i];
                if (ctx.reasoning_ctx != nullptr) {
                    ctx.reasoning_ctx->RecordReorder(
                        all_ids[idx], lower_bound_probe_dists[idx], batch_dists[i]);
                }
                add_iterator_discard(batch_dists[i], all_ids[idx]);
            }
        }
    }
    return reorder_heap;
}
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L427 | flatten_.get | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L428 | CHECK_ARGUMENT | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L432 | select_query_allocator | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L434 | distance_threshold.has_value | lambda@433（定义体，执行时间取决于调用/调度） | 当前参考未静态绑定；见下方边界说明 |

| L435 | IsFiniteRaBitQValue | lambda@433（定义体，执行时间取决于调用/调度） | 当前参考未静态绑定；见下方边界说明 |

| L435 | distance_threshold.value | lambda@433（定义体，执行时间取决于调用/调度） | 当前参考未静态绑定；见下方边界说明 |

| L438 | is_distance_eligible | lambda@437（定义体，执行时间取决于调用/调度） → if_statement@438 (is_distance_eligible(distance)) | 当前参考未静态绑定；见下方边界说明 |

| L442 | iter_ctx-&gt;SetPoint | lambda@437（定义体，执行时间取决于调用/调度） → if_statement@441 (iter_ctx != nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L447 | IsFiniteRaBitQValue | lambda@446（定义体，执行时间取决于调用/调度） | 当前参考未静态绑定；见下方边界说明 |

| L447 | std::numeric_limits&lt;float&gt;::max | lambda@446（定义体，执行时间取决于调用/调度） | 当前参考未静态绑定；见下方边界说明 |

| L449 | input-&gt;Size | conditional_expression@449 input == nullptr | 当前参考未静态绑定；见下方边界说明 |

| L452 | iter_ctx-&gt;AddDiscardNode | lambda@450（定义体，执行时间取决于调用/调度） → if_statement@451 (iter_ctx != nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L456 | std::min | if_statement@455 (rabitq_lower_bound_candidates == nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L457 | std::make_shared&lt;StandardHeap&lt;true, false&gt;&gt; | if_statement@455 (rabitq_lower_bound_candidates == nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L458 | split_codes-&gt;FactoryFusedComputer | if_statement@455 (rabitq_lower_bound_candidates == nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L461 | input-&gt;GetData | if_statement@455 (rabitq_lower_bound_candidates == nullptr) → conditional_expression@461 input == nullptr | 当前参考未静态绑定；见下方边界说明 |

| L465 | add_reorder_distance_count | if_statement@455 (rabitq_lower_bound_candidates == nullptr) | [add_reorder_distance_count · L130](flatten_reorder.md#L130) |

| L469 | fused_graph_-&gt;GetCodeView | if_statement@455 (rabitq_lower_bound_candidates == nullptr) → for_statement@468 i &lt; heap_candidate_size | 当前参考未静态绑定；见下方边界说明 |

| L470 | split_codes-&gt;ComputeFusedFull | if_statement@455 (rabitq_lower_bound_candidates == nullptr) → for_statement@468 i &lt; heap_candidate_size → if_statement@470 (not split_codes-&gt;ComputeFusedFull(computer, code.cluster_id, code.one_bit_code, code.supplement_code, dists.data() + i, &ctx)) | 当前参考未静态绑定；见下方边界说明 |

| L474 | dists.data | if_statement@455 (rabitq_lower_bound_candidates == nullptr) → for_statement@468 i &lt; heap_candidate_size → if_statement@470 (not split_codes-&gt;ComputeFusedFull(computer, code.cluster_id, code.one_bit_code, code.supplement_code, dists.data() + i, &ctx)) | 当前参考未静态绑定；见下方边界说明 |

| L476 | std::numeric_limits&lt;float&gt;::max | if_statement@455 (rabitq_lower_bound_candidates == nullptr) → for_statement@468 i &lt; heap_candidate_size → if_statement@470 (not split_codes-&gt;ComputeFusedFull(computer, code.cluster_id, code.one_bit_code, code.supplement_code, dists.data() + i, &ctx)) | 当前参考未静态绑定；见下方边界说明 |

| L481 | has_valid_distance | if_statement@455 (rabitq_lower_bound_candidates == nullptr) → for_statement@480 i &lt; heap_candidate_size → if_statement@481 (not has_valid_distance(dists[i])) | 当前参考未静态绑定；见下方边界说明 |

| L485 | ctx.reasoning_ctx-&gt;RecordReorder | if_statement@455 (rabitq_lower_bound_candidates == nullptr) → for_statement@480 i &lt; heap_candidate_size → if_statement@484 (ctx.reasoning_ctx != nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L488 | consume_if_ineligible | if_statement@455 (rabitq_lower_bound_candidates == nullptr) → for_statement@480 i &lt; heap_candidate_size → if_statement@488 (consume_if_ineligible(dists[i], candidate_result[i].second)) | 当前参考未静态绑定；见下方边界说明 |

| L491 | reorder_heap-&gt;Size | if_statement@455 (rabitq_lower_bound_candidates == nullptr) → for_statement@480 i &lt; heap_candidate_size → if_statement@491 (reorder_heap-&gt;Size() &lt; topk &#124;&#124; dists[i] &lt; reorder_heap-&gt;Top().first) | 当前参考未静态绑定；见下方边界说明 |

| L491 | reorder_heap-&gt;Top | if_statement@455 (rabitq_lower_bound_candidates == nullptr) → for_statement@480 i &lt; heap_candidate_size → if_statement@491 (reorder_heap-&gt;Size() &lt; topk &#124;&#124; dists[i] &lt; reorder_heap-&gt;Top().first) | 当前参考未静态绑定；见下方边界说明 |

| L492 | reorder_heap-&gt;Push | if_statement@455 (rabitq_lower_bound_candidates == nullptr) → for_statement@480 i &lt; heap_candidate_size → if_statement@491 (reorder_heap-&gt;Size() &lt; topk &#124;&#124; dists[i] &lt; reorder_heap-&gt;Top().first) | 当前参考未静态绑定；见下方边界说明 |

| L493 | reorder_heap-&gt;Size | if_statement@455 (rabitq_lower_bound_candidates == nullptr) → for_statement@480 i &lt; heap_candidate_size → if_statement@491 (reorder_heap-&gt;Size() &lt; topk &#124;&#124; dists[i] &lt; reorder_heap-&gt;Top().first) → if_statement@493 (reorder_heap-&gt;Size() &gt; topk) | 当前参考未静态绑定；见下方边界说明 |

| L494 | reorder_heap-&gt;Top | if_statement@455 (rabitq_lower_bound_candidates == nullptr) → for_statement@480 i &lt; heap_candidate_size → if_statement@491 (reorder_heap-&gt;Size() &lt; topk &#124;&#124; dists[i] &lt; reorder_heap-&gt;Top().first) → if_statement@493 (reorder_heap-&gt;Size() &gt; topk) | 当前参考未静态绑定；见下方边界说明 |

| L495 | add_iterator_discard | if_statement@455 (rabitq_lower_bound_candidates == nullptr) → for_statement@480 i &lt; heap_candidate_size → if_statement@491 (reorder_heap-&gt;Size() &lt; topk &#124;&#124; dists[i] &lt; reorder_heap-&gt;Top().first) → if_statement@493 (reorder_heap-&gt;Size() &gt; topk) | 当前参考未静态绑定；见下方边界说明 |

| L497 | ctx.reasoning_ctx-&gt;RecordReorderEviction | if_statement@455 (rabitq_lower_bound_candidates == nullptr) → for_statement@480 i &lt; heap_candidate_size → if_statement@491 (reorder_heap-&gt;Size() &lt; topk &#124;&#124; dists[i] &lt; reorder_heap-&gt;Top().first) → if_statement@493 (reorder_heap-&gt;Size() &gt; topk) → if_statement@496 (ctx.reasoning_ctx != nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L497 | reorder_heap-&gt;Top | if_statement@455 (rabitq_lower_bound_candidates == nullptr) → for_statement@480 i &lt; heap_candidate_size → if_statement@491 (reorder_heap-&gt;Size() &lt; topk &#124;&#124; dists[i] &lt; reorder_heap-&gt;Top().first) → if_statement@493 (reorder_heap-&gt;Size() &gt; topk) → if_statement@496 (ctx.reasoning_ctx != nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L499 | reorder_heap-&gt;Pop | if_statement@455 (rabitq_lower_bound_candidates == nullptr) → for_statement@480 i &lt; heap_candidate_size → if_statement@491 (reorder_heap-&gt;Size() &lt; topk &#124;&#124; dists[i] &lt; reorder_heap-&gt;Top().first) → if_statement@493 (reorder_heap-&gt;Size() &gt; topk) | 当前参考未静态绑定；见下方边界说明 |

| L502 | add_iterator_discard | if_statement@455 (rabitq_lower_bound_candidates == nullptr) → for_statement@480 i &lt; heap_candidate_size → if_statement@491 (reorder_heap-&gt;Size() &lt; topk &#124;&#124; dists[i] &lt; reorder_heap-&gt;Top().first) [else 分支] | 当前参考未静态绑定；见下方边界说明 |

| L508 | rabitq_lower_bound_candidates-&gt;size | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L514 | std::make_shared&lt;StandardHeap&lt;true, false&gt;&gt; | if_statement@513 (topk == 0 or max_candidate_size == 0) | 当前参考未静态绑定；见下方边界说明 |

| L525 | merged_ids.reserve | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L529 | merged_ids.emplace | for_range_loop@528 | 当前参考未静态绑定；见下方边界说明 |

| L541 | has_valid_distance | for_range_loop@528 → if_statement@541 (has_valid_distance(item.lower_bound) and (not has_valid_distance(lower_bounds[idx]) or item.lower_bound &lt; lower_bounds[idx])) | 当前参考未静态绑定；见下方边界说明 |

| L542 | has_valid_distance | for_range_loop@528 → if_statement@541 (has_valid_distance(item.lower_bound) and (not has_valid_distance(lower_bounds[idx]) or item.lower_bound &lt; lower_bounds[idx])) | 当前参考未静态绑定；见下方边界说明 |

| L546 | IsFiniteRaBitQValue | for_range_loop@528 → if_statement@546 (not IsFiniteRaBitQValue(filter_inner_products[idx]) and IsFiniteRaBitQValue(item.filter_inner_product)) | 当前参考未静态绑定；见下方边界说明 |

| L547 | IsFiniteRaBitQValue | for_range_loop@528 → if_statement@546 (not IsFiniteRaBitQValue(filter_inner_products[idx]) and IsFiniteRaBitQValue(item.filter_inner_product)) | 当前参考未静态绑定；见下方边界说明 |

| L550 | has_valid_distance | for_range_loop@528 → if_statement@550 (not has_valid_distance(full_distances[idx]) and has_valid_distance(item.full_distance)) | 当前参考未静态绑定；见下方边界说明 |

| L551 | has_valid_distance | for_range_loop@528 → if_statement@550 (not has_valid_distance(full_distances[idx]) and has_valid_distance(item.full_distance)) | 当前参考未静态绑定；见下方边界说明 |

| L557 | input-&gt;GetData | conditional_expression@557 input == nullptr | 当前参考未静态绑定；见下方边界说明 |

| L560 | merged_ids.emplace | for_statement@558 i &lt; heap_candidate_size → if_statement@560 (merged_ids.emplace(id, candidate_size).second) | 当前参考未静态绑定；见下方边界说明 |

| L568 | split_codes-&gt;FactoryFusedComputer | lambda@566（定义体，执行时间取决于调用/调度） → if_statement@567 (computer == nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L575 | add_reorder_lower_bound_probe_count | if_statement@574 (unhinted_candidate_size &gt; 0) | [add_reorder_lower_bound_probe_count · L146](flatten_reorder.md#L146) |

| L577 | QueryFusedLowerBound | if_statement@574 (unhinted_candidate_size &gt; 0) | [FlattenReorder::QueryFusedLowerBound · L34](flatten_reorder.md#L34) |

| L577 | lower_bound_probe_dists.data | if_statement@574 (unhinted_candidate_size &gt; 0) | 当前参考未静态绑定；见下方边界说明 |

| L578 | lower_bounds.data | if_statement@574 (unhinted_candidate_size &gt; 0) | 当前参考未静态绑定；见下方边界说明 |

| L579 | filter_inner_products.data | if_statement@574 (unhinted_candidate_size &gt; 0) | 当前参考未静态绑定；见下方边界说明 |

| L581 | ensure_computer | if_statement@574 (unhinted_candidate_size &gt; 0) | 当前参考未静态绑定；见下方边界说明 |

| L582 | all_ids.data | if_statement@574 (unhinted_candidate_size &gt; 0) | 当前参考未静态绑定；见下方边界说明 |

| L587 | std::min | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L588 | std::make_shared&lt;StandardHeap&lt;true, false&gt;&gt; | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L594 | has_valid_distance | lambda@593（定义体，执行时间取决于调用/调度） → if_statement@594 (not has_valid_distance(distance)) | 当前参考未静态绑定；见下方边界说明 |

| L598 | ctx.reasoning_ctx-&gt;RecordReorder | lambda@593（定义体，执行时间取决于调用/调度） → if_statement@597 (ctx.reasoning_ctx != nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L600 | consume_if_ineligible | lambda@593（定义体，执行时间取决于调用/调度） → if_statement@600 (consume_if_ineligible(distance, all_ids[idx])) | 当前参考未静态绑定；见下方边界说明 |

| L603 | reorder_heap-&gt;Size | lambda@593（定义体，执行时间取决于调用/调度） → if_statement@603 (reorder_heap-&gt;Size() &lt; topk or distance &lt; reorder_heap-&gt;Top().first) | 当前参考未静态绑定；见下方边界说明 |

| L603 | reorder_heap-&gt;Top | lambda@593（定义体，执行时间取决于调用/调度） → if_statement@603 (reorder_heap-&gt;Size() &lt; topk or distance &lt; reorder_heap-&gt;Top().first) | 当前参考未静态绑定；见下方边界说明 |

| L604 | reorder_heap-&gt;Push | lambda@593（定义体，执行时间取决于调用/调度） → if_statement@603 (reorder_heap-&gt;Size() &lt; topk or distance &lt; reorder_heap-&gt;Top().first) | 当前参考未静态绑定；见下方边界说明 |

| L605 | reorder_heap-&gt;Size | lambda@593（定义体，执行时间取决于调用/调度） → if_statement@603 (reorder_heap-&gt;Size() &lt; topk or distance &lt; reorder_heap-&gt;Top().first) → if_statement@605 (reorder_heap-&gt;Size() &gt; topk) | 当前参考未静态绑定；见下方边界说明 |

| L606 | reorder_heap-&gt;Top | lambda@593（定义体，执行时间取决于调用/调度） → if_statement@603 (reorder_heap-&gt;Size() &lt; topk or distance &lt; reorder_heap-&gt;Top().first) → if_statement@605 (reorder_heap-&gt;Size() &gt; topk) | 当前参考未静态绑定；见下方边界说明 |

| L607 | add_iterator_discard | lambda@593（定义体，执行时间取决于调用/调度） → if_statement@603 (reorder_heap-&gt;Size() &lt; topk or distance &lt; reorder_heap-&gt;Top().first) → if_statement@605 (reorder_heap-&gt;Size() &gt; topk) | 当前参考未静态绑定；见下方边界说明 |

| L609 | ctx.reasoning_ctx-&gt;RecordReorderEviction | lambda@593（定义体，执行时间取决于调用/调度） → if_statement@603 (reorder_heap-&gt;Size() &lt; topk or distance &lt; reorder_heap-&gt;Top().first) → if_statement@605 (reorder_heap-&gt;Size() &gt; topk) → if_statement@608 (ctx.reasoning_ctx != nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L611 | reorder_heap-&gt;Pop | lambda@593（定义体，执行时间取决于调用/调度） → if_statement@603 (reorder_heap-&gt;Size() &lt; topk or distance &lt; reorder_heap-&gt;Top().first) → if_statement@605 (reorder_heap-&gt;Size() &gt; topk) | 当前参考未静态绑定；见下方边界说明 |

| L614 | add_iterator_discard | lambda@593（定义体，执行时间取决于调用/调度） → if_statement@603 (reorder_heap-&gt;Size() &lt; topk or distance &lt; reorder_heap-&gt;Top().first) [else 分支] | 当前参考未静态绑定；见下方边界说明 |

| L620 | has_valid_distance | for_statement@619 i &lt; candidate_size → if_statement@620 (not has_valid_distance(full_distances[i])) | 当前参考未静态绑定；见下方边界说明 |

| L627 | push_full_distance | if_statement@625 (all_full_distances_available) → for_statement@626 i &lt; candidate_size | 当前参考未静态绑定；见下方边界说明 |

| L634 | has_valid_distance | for_statement@633 i &lt; candidate_size → if_statement@634 (not has_valid_distance(lower_bounds[i])) | 当前参考未静态绑定；见下方边界说明 |

| L652 | has_valid_distance | lambda@648（定义体，执行时间取决于调用/调度） → for_statement@650 i &lt; count → if_statement@652 (has_valid_distance(full_distances[idx])) | 当前参考未静态绑定；见下方边界说明 |

| L664 | add_reorder_distance_count | lambda@648（定义体，执行时间取决于调用/调度） | [add_reorder_distance_count · L130](flatten_reorder.md#L130) |

| L667 | QueryFusedFullWithHint | lambda@648（定义体，执行时间取决于调用/调度） | [FlattenReorder::QueryFusedFullWithHint · L77](flatten_reorder.md#L77) |

| L667 | missing_dists.data | lambda@648（定义体，执行时间取决于调用/调度） | 当前参考未静态绑定；见下方边界说明 |

| L668 | missing_hints.data | lambda@648（定义体，执行时间取决于调用/调度） | 当前参考未静态绑定；见下方边界说明 |

| L670 | ensure_computer | lambda@648（定义体，执行时间取决于调用/调度） | 当前参考未静态绑定；见下方边界说明 |

| L671 | missing_ids.data | lambda@648（定义体，执行时间取决于调用/调度） | 当前参考未静态绑定；见下方边界说明 |

| L684 | compute_missing_full_distances | if_statement@683 (not lower_bounds_available) | 当前参考未静态绑定；见下方边界说明 |

| L684 | full_distances.data | if_statement@683 (not lower_bounds_available) | 当前参考未静态绑定；见下方边界说明 |

| L686 | push_full_distance | if_statement@683 (not lower_bounds_available) → for_statement@685 i &lt; candidate_size | 当前参考未静态绑定；见下方边界说明 |

| L692 | std::iota | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L692 | order.begin | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L692 | order.end | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L693 | std::sort | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L693 | order.begin | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L693 | order.end | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L703 | has_valid_distance | for_statement@702 i &lt; candidate_size → if_statement@703 (has_valid_distance(full_distances[i])) | 当前参考未静态绑定；见下方边界说明 |

| L704 | push_full_distance | for_statement@702 i &lt; candidate_size → if_statement@703 (has_valid_distance(full_distances[i])) | 当前参考未静态绑定；见下方边界说明 |

| L710 | has_valid_distance | while_statement@709 (cursor &lt; candidate_size) → while_statement@710 (cursor &lt; candidate_size and has_valid_distance(full_distances[order[cursor]])) | 当前参考未静态绑定；见下方边界说明 |

| L716 | reorder_heap-&gt;Size | while_statement@709 (cursor &lt; candidate_size) | 当前参考未静态绑定；见下方边界说明 |

| L718 | reorder_heap-&gt;Top | while_statement@709 (cursor &lt; candidate_size) → conditional_expression@718 heap_full | 当前参考未静态绑定；见下方边界说明 |

| L718 | std::numeric_limits&lt;float&gt;::max | while_statement@709 (cursor &lt; candidate_size) → conditional_expression@718 heap_full | 当前参考未静态绑定；见下方边界说明 |

| L724 | std::min&lt;uint64_t&gt; | while_statement@709 (cursor &lt; candidate_size) → conditional_expression@723 heap_full | 当前参考未静态绑定；见下方边界说明 |

| L725 | reorder_heap-&gt;Size | while_statement@709 (cursor &lt; candidate_size) → conditional_expression@723 heap_full | 当前参考未静态绑定；见下方边界说明 |

| L729 | has_valid_distance | while_statement@709 (cursor &lt; candidate_size) → while_statement@727 (cursor &lt; candidate_size and batch_count &lt; batch_limit) → if_statement@729 (has_valid_distance(full_distances[idx])) | 当前参考未静态绑定；见下方边界说明 |

| L744 | compute_missing_full_distances | while_statement@709 (cursor &lt; candidate_size) | 当前参考未静态绑定；见下方边界说明 |

| L744 | batch_indices.data | while_statement@709 (cursor &lt; candidate_size) | 当前参考未静态绑定；见下方边界说明 |

| L744 | batch_dists.data | while_statement@709 (cursor &lt; candidate_size) | 当前参考未静态绑定；见下方边界说明 |

| L746 | push_full_distance | while_statement@709 (cursor &lt; candidate_size) → for_statement@745 i &lt; batch_count | 当前参考未静态绑定；见下方边界说明 |

| L756 | has_valid_distance | if_statement@749 (iter_ctx != nullptr) → while_statement@752 (cursor &lt; candidate_size) → while_statement@754 (cursor &lt; candidate_size and batch_count &lt; batch_size) → if_statement@756 (not has_valid_distance(full_distances[idx])) | 当前参考未静态绑定；见下方边界说明 |

| L763 | compute_missing_full_distances | if_statement@749 (iter_ctx != nullptr) → while_statement@752 (cursor &lt; candidate_size) | 当前参考未静态绑定；见下方边界说明 |

| L763 | batch_indices.data | if_statement@749 (iter_ctx != nullptr) → while_statement@752 (cursor &lt; candidate_size) | 当前参考未静态绑定；见下方边界说明 |

| L763 | batch_dists.data | if_statement@749 (iter_ctx != nullptr) → while_statement@752 (cursor &lt; candidate_size) | 当前参考未静态绑定；见下方边界说明 |

| L767 | ctx.reasoning_ctx-&gt;RecordReorder | if_statement@749 (iter_ctx != nullptr) → while_statement@752 (cursor &lt; candidate_size) → for_statement@764 i &lt; batch_count → if_statement@766 (ctx.reasoning_ctx != nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L770 | add_iterator_discard | if_statement@749 (iter_ctx != nullptr) → while_statement@752 (cursor &lt; candidate_size) → for_statement@764 i &lt; batch_count | 当前参考未静态绑定；见下方边界说明 |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。
