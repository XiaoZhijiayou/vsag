# ivf_modify.cpp：逐函数完整源码与调用点

[主讲解](../code_walkthrough.md) · [函数总目录](README.md)

源码：[ src/algorithm/ivf/ivf_modify.cpp ](../../../../src/algorithm/ivf/ivf_modify.cpp)。基线 `fd363937`。以下源码函数体完整保留；调用点表是语法树中的显式调用表达式，按源码位置排列，不代表 C++ 参数求值顺序。表中“候选实现”需结合类型和参数选分支，不能将同名函数全部视为必经路径。

- [IVF::Remove · L22](ivf_modify.md#L22)

- [IVF::UpdateAttribute · L33](ivf_modify.md#L33)

- [IVF::UpdateAttribute · L40](ivf_modify.md#L40)


<a id="L22"></a>

## `IVF::Remove`

源码位置：`src/algorithm/ivf/ivf_modify.cpp:22–31`。

本 IVF 实现只在 MARK_REMOVE 分支调用 label_table_->MarkRemove 并累加删除数；其他模式返回 0。是否支持调用还要看外层特性检查。

### 完整函数

```cpp
uint32_t
IVF::Remove(const std::vector<int64_t>& ids, RemoveMode mode) {
    uint32_t delete_count = 0;
    if (mode == RemoveMode::MARK_REMOVE) {
        std::scoped_lock label_lock(this->label_lookup_mutex_);
        delete_count = this->label_table_->MarkRemove(ids);
        delete_count_ += delete_count;
    }
    return delete_count;
}
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L27 | this-&gt;label_table_-&gt;MarkRemove | if_statement@25 (mode == RemoveMode::MARK_REMOVE) | [LabelTable::MarkRemove · L126](label_table.md#L126) |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L33"></a>

## `IVF::UpdateAttribute`

源码位置：`src/algorithm/ivf/ivf_modify.cpp:33–38`。

外部 label 先映射为 origin，再定位桶内 offset，最后更新该位置的属性位图；重载版本还携带旧属性。

### 完整函数

```cpp
void
IVF::UpdateAttribute(int64_t id, const AttributeSet& new_attrs) {
    auto inner_id = this->label_table_->GetIdByLabel(id);
    auto [bucket_id, offset_id] = this->get_location(inner_id);
    this->attr_filter_index_->UpdateBitsetsByAttr(new_attrs, offset_id, bucket_id);
}
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L35 | this-&gt;label_table_-&gt;GetIdByLabel | 函数本体；短路求值/提前返回见源码 | [LabelTable::GetIdByLabel · L116](label_table.md#L116) |

| L36 | this-&gt;get_location | 函数本体；短路求值/提前返回见源码 | [IVF::get_location · L312](ivf.md#L312) |

| L37 | this-&gt;attr_filter_index_-&gt;UpdateBitsetsByAttr | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L40"></a>

## `IVF::UpdateAttribute`

源码位置：`src/algorithm/ivf/ivf_modify.cpp:40–45`。

外部 label 先映射为 origin，再定位桶内 offset，最后更新该位置的属性位图；重载版本还携带旧属性。

### 完整函数

```cpp
void
IVF::UpdateAttribute(int64_t id, const AttributeSet& new_attrs, const AttributeSet& origin_attrs) {
    auto inner_id = this->label_table_->GetIdByLabel(id);
    auto [bucket_id, offset_id] = this->get_location(inner_id);
    this->attr_filter_index_->UpdateBitsetsByAttr(new_attrs, offset_id, bucket_id, origin_attrs);
}
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L42 | this-&gt;label_table_-&gt;GetIdByLabel | 函数本体；短路求值/提前返回见源码 | [LabelTable::GetIdByLabel · L116](label_table.md#L116) |

| L43 | this-&gt;get_location | 函数本体；短路求值/提前返回见源码 | [IVF::get_location · L312](ivf.md#L312) |

| L44 | this-&gt;attr_filter_index_-&gt;UpdateBitsetsByAttr | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。
