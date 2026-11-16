# label_table.cpp：逐函数完整源码与调用点

[主讲解](../code_walkthrough.md) · [函数总目录](README.md)

源码：[ src/impl/label_table/label_table.cpp ](../../../../src/impl/label_table/label_table.cpp)。基线 `fd363937`。以下源码函数体完整保留；调用点表是语法树中的显式调用表达式，按源码位置排列，不代表 C++ 参数求值顺序。表中“候选实现”需结合类型和参数选分支，不能将同名函数全部视为必经路径。

- [LabelTable::TryGetIdByLabel · L96](label_table.md#L96)

- [LabelTable::GetIdByLabel · L116](label_table.md#L116)

- [LabelTable::MarkRemove · L126](label_table.md#L126)


<a id="L96"></a>

## `LabelTable::TryGetIdByLabel`

源码位置：`src/impl/label_table/label_table.cpp:96–114`。

先从签名确认输入、返回值和 const/override，再按完整函数体的条件阅读调用点。下表保留了本函数的显式调用以及 lambda 中的调用；进入下层时用“候选实现”定位，未解析的对象由源码静态类型/运行时类型确认。

### 完整函数

```cpp
std::pair<bool, InnerIdType>
LabelTable::TryGetIdByLabel(LabelType label, bool return_even_removed) const noexcept {
    InnerIdType id;
    if (use_reverse_map_) {
        id = this->get_id_by_label_with_reverse_map(label);
    } else {
        id = this->get_id_by_label_with_label_table(label);
    }
    if (id == INVALID_ID) {
        return {false, 0};
    }
    if (not return_even_removed) {
        std::shared_lock rlock(delete_ids_mutex_);
        if (this->deleted_ids_.count(id) > 0) {
            return {false, 0};
        }
    }
    return {true, id};
}
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L100 | this-&gt;get_id_by_label_with_reverse_map | if_statement@99 (use_reverse_map_) | 当前参考未静态绑定；见下方边界说明 |

| L102 | this-&gt;get_id_by_label_with_label_table | if_statement@99 (use_reverse_map_) [else 分支] | 当前参考未静态绑定；见下方边界说明 |

| L109 | this-&gt;deleted_ids_.count | if_statement@107 (not return_even_removed) → if_statement@109 (this-&gt;deleted_ids_.count(id) &gt; 0) | 当前参考未静态绑定；见下方边界说明 |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L116"></a>

## `LabelTable::GetIdByLabel`

源码位置：`src/impl/label_table/label_table.cpp:116–124`。

先从签名确认输入、返回值和 const/override，再按完整函数体的条件阅读调用点。下表保留了本函数的显式调用以及 lambda 中的调用；进入下层时用“候选实现”定位，未解析的对象由源码静态类型/运行时类型确认。

### 完整函数

```cpp
InnerIdType
LabelTable::GetIdByLabel(LabelType label, bool return_even_removed) const {
    auto [success, inner_id] = TryGetIdByLabel(label, return_even_removed);
    if (not success) {
        throw VsagException(ErrorType::INTERNAL_ERROR,
                            fmt::format("label {} does not exist or is removed", label));
    }
    return inner_id;
}
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L118 | TryGetIdByLabel | 函数本体；短路求值/提前返回见源码 | [LabelTable::TryGetIdByLabel · L96](label_table.md#L96) |

| L120 | VsagException | if_statement@119 (not success) | 当前参考未静态绑定；见下方边界说明 |

| L121 | fmt::format | if_statement@119 (not success) | 当前参考未静态绑定；见下方边界说明 |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L126"></a>

## `LabelTable::MarkRemove`

源码位置：`src/impl/label_table/label_table.cpp:126–149`。

先从签名确认输入、返回值和 const/override，再按完整函数体的条件阅读调用点。下表保留了本函数的显式调用以及 lambda 中的调用；进入下层时用“候选实现”定位，未解析的对象由源码静态类型/运行时类型确认。

### 完整函数

```cpp
uint32_t
LabelTable::MarkRemove(const std::vector<LabelType>& labels) {
    std::vector<InnerIdType> ids;
    ids.reserve(labels.size());
    for (const auto& label : labels) {
        InnerIdType id;
        if (this->use_reverse_map_) {
            id = this->get_id_by_label_with_reverse_map(label);
        } else {
            id = this->get_id_by_label_with_label_table(label);
        }
        if (id != INVALID_ID) {
            ids.push_back(id);
        }
    }
    uint32_t removed_count = 0;
    std::scoped_lock wlock(delete_ids_mutex_);
    for (const auto& id : ids) {
        if (this->deleted_ids_.insert(id).second) {
            ++removed_count;
        }
    }
    return removed_count;
}
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L129 | ids.reserve | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L129 | labels.size | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L133 | this-&gt;get_id_by_label_with_reverse_map | for_range_loop@130 → if_statement@132 (this-&gt;use_reverse_map_) | 当前参考未静态绑定；见下方边界说明 |

| L135 | this-&gt;get_id_by_label_with_label_table | for_range_loop@130 → if_statement@132 (this-&gt;use_reverse_map_) [else 分支] | 当前参考未静态绑定；见下方边界说明 |

| L138 | ids.push_back | for_range_loop@130 → if_statement@137 (id != INVALID_ID) | 当前参考未静态绑定；见下方边界说明 |

| L144 | this-&gt;deleted_ids_.insert | for_range_loop@143 → if_statement@144 (this-&gt;deleted_ids_.insert(id).second) | 当前参考未静态绑定；见下方边界说明 |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。
