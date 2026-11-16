# inner_index_interface.cpp：逐函数完整源码与调用点

[主讲解](../code_walkthrough.md) · [函数总目录](README.md)

源码：[ src/algorithm/inner_index_interface.cpp ](../../../../src/algorithm/inner_index_interface.cpp)。基线 `fd363937`。以下源码函数体完整保留；调用点表是语法树中的显式调用表达式，按源码位置排列，不代表 C++ 参数求值顺序。表中“候选实现”需结合类型和参数选分支，不能将同名函数全部视为必经路径。

- [InnerIndexInterface::create_search_filter · L1108](inner_index_interface.md#L1108)

- [InnerIndexInterface::pack_knn_result · L1140](inner_index_interface.md#L1140)

- [InnerIndexInterface::filter_search_result_by_threshold · L1156](inner_index_interface.md#L1156)


<a id="L1108"></a>

## `InnerIndexInterface::create_search_filter`

源码位置：`src/algorithm/inner_index_interface.cpp:1108–1138`。

取得删除过滤器，将用户过滤器包装成内部 ID 语义。只有两者都存在时才组合，保留单个过滤器的能力。

### 完整函数

```cpp
FilterPtr
InnerIndexInterface::create_search_filter(const FilterPtr& user_filter,
                                          bool use_extra_info_filter) const {
    auto deleted_filter = this->label_table_->GetDeletedIdsFilter();
    FilterPtr wrapped_user_filter = nullptr;
    if (user_filter != nullptr) {
        if (use_extra_info_filter && this->extra_infos_ != nullptr) {
            wrapped_user_filter =
                std::make_shared<ExtraInfoWrapperFilter>(user_filter, this->extra_infos_);
        } else {
            wrapped_user_filter =
                std::make_shared<InnerIdWrapperFilter>(user_filter, *this->label_table_);
        }
    }

    // Avoid CombinedFilter when only one filter is present to preserve
    // GetValidIds() / FilterDistribution() capabilities of the inner filter.
    if (deleted_filter == nullptr && wrapped_user_filter == nullptr) {
        return nullptr;
    }
    if (deleted_filter == nullptr) {
        return wrapped_user_filter;
    }
    if (wrapped_user_filter == nullptr) {
        return deleted_filter;
    }
    auto combined_filter = std::make_shared<CombinedFilter>();
    combined_filter->AppendFilter(deleted_filter);
    combined_filter->AppendFilter(wrapped_user_filter);
    return combined_filter;
}
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L1111 | this-&gt;label_table_-&gt;GetDeletedIdsFilter | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L1116 | std::make_shared&lt;ExtraInfoWrapperFilter&gt; | if_statement@1113 (user_filter != nullptr) → if_statement@1114 (use_extra_info_filter && this-&gt;extra_infos_ != nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L1119 | std::make_shared&lt;InnerIdWrapperFilter&gt; | if_statement@1113 (user_filter != nullptr) → if_statement@1114 (use_extra_info_filter && this-&gt;extra_infos_ != nullptr) [else 分支] | 当前参考未静态绑定；见下方边界说明 |

| L1134 | std::make_shared&lt;CombinedFilter&gt; | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L1135 | combined_filter-&gt;AppendFilter | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L1136 | combined_filter-&gt;AppendFilter | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L1140"></a>

## `InnerIndexInterface::pack_knn_result`

源码位置：`src/algorithm/inner_index_interface.cpp:1140–1154`。

输入大顶堆，分配输出 Dataset，倒序写距离，并将堆内 origin ID 转成外部 label。每次 Pop 消耗输入堆；空堆有独立返回路径。

### 完整函数

```cpp
DatasetPtr
InnerIndexInterface::pack_knn_result(DistHeapPtr& heap, Allocator* allocator) const {
    if (heap == nullptr || heap->Empty()) {
        return make_empty_result();
    }
    auto* alloc = allocator != nullptr ? allocator : allocator_;
    auto count = static_cast<int64_t>(heap->Size());
    auto [dataset_results, dists, ids] = create_fast_dataset(count, alloc);
    for (auto j = count - 1; j >= 0; --j) {
        dists[j] = heap->Top().first;
        ids[j] = this->label_table_->GetLabelById(heap->Top().second);
        heap->Pop();
    }
    return std::move(dataset_results);
}
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L1142 | heap-&gt;Empty | if_statement@1142 (heap == nullptr &#124;&#124; heap-&gt;Empty()) | 当前参考未静态绑定；见下方边界说明 |

| L1143 | make_empty_result | if_statement@1142 (heap == nullptr &#124;&#124; heap-&gt;Empty()) | 当前参考未静态绑定；见下方边界说明 |

| L1146 | heap-&gt;Size | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L1147 | create_fast_dataset | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L1149 | heap-&gt;Top | for_statement@1148 j &gt;= 0 | 当前参考未静态绑定；见下方边界说明 |

| L1150 | this-&gt;label_table_-&gt;GetLabelById | for_statement@1148 j &gt;= 0 | 当前参考未静态绑定；见下方边界说明 |

| L1150 | heap-&gt;Top | for_statement@1148 j &gt;= 0 | 当前参考未静态绑定；见下方边界说明 |

| L1151 | heap-&gt;Pop | for_statement@1148 j &gt;= 0 | 当前参考未静态绑定；见下方边界说明 |

| L1153 | std::move | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L1156"></a>

## `InnerIndexInterface::filter_search_result_by_threshold`

源码位置：`src/algorithm/inner_index_interface.cpp:1156–1175`。

先从签名确认输入、返回值和 const/override，再按完整函数体的条件阅读调用点。下表保留了本函数的显式调用以及 lambda 中的调用；进入下层时用“候选实现”定位，未解析的对象由源码静态类型/运行时类型确认。

### 完整函数

```cpp
void
InnerIndexInterface::filter_search_result_by_threshold(DistHeapPtr& result,
                                                       const std::optional<float>& threshold,
                                                       Allocator* allocator) {
    if (not threshold.has_value() or result == nullptr) {
        return;
    }
    DistanceRecordVector valid_records(allocator);
    valid_records.reserve(result->Size());
    while (not result->Empty()) {
        const auto record = result->Top();
        result->Pop();
        if (std::isfinite(record.first) and record.first <= threshold.value()) {
            valid_records.push_back(record);
        }
    }
    for (const auto& record : valid_records) {
        result->Push(record);
    }
}
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L1160 | threshold.has_value | if_statement@1160 (not threshold.has_value() or result == nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L1164 | valid_records.reserve | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L1164 | result-&gt;Size | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L1165 | result-&gt;Empty | while_statement@1165 (not result-&gt;Empty()) | 当前参考未静态绑定；见下方边界说明 |

| L1166 | result-&gt;Top | while_statement@1165 (not result-&gt;Empty()) | 当前参考未静态绑定；见下方边界说明 |

| L1167 | result-&gt;Pop | while_statement@1165 (not result-&gt;Empty()) | 当前参考未静态绑定；见下方边界说明 |

| L1168 | std::isfinite | while_statement@1165 (not result-&gt;Empty()) → if_statement@1168 (std::isfinite(record.first) and record.first &lt;= threshold.value()) | 当前参考未静态绑定；见下方边界说明 |

| L1168 | threshold.value | while_statement@1165 (not result-&gt;Empty()) → if_statement@1168 (std::isfinite(record.first) and record.first &lt;= threshold.value()) | 当前参考未静态绑定；见下方边界说明 |

| L1169 | valid_records.push_back | while_statement@1165 (not result-&gt;Empty()) → if_statement@1168 (std::isfinite(record.first) and record.first &lt;= threshold.value()) | 当前参考未静态绑定；见下方边界说明 |

| L1173 | result-&gt;Push | for_range_loop@1172 | 当前参考未静态绑定；见下方边界说明 |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。
