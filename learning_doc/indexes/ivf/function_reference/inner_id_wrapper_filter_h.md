# inner_id_wrapper_filter.h：逐函数完整源码与调用点

[主讲解](../code_walkthrough.md) · [函数总目录](README.md)

源码：[ src/impl/filter/inner_id_wrapper_filter.h ](../../../../src/impl/filter/inner_id_wrapper_filter.h)。基线 `fd363937`。以下源码函数体完整保留；调用点表是语法树中的显式调用表达式，按源码位置排列，不代表 C++ 参数求值顺序。表中“候选实现”需结合类型和参数选分支，不能将同名函数全部视为必经路径。

- [InnerIdWrapperFilter::InnerIdWrapperFilter · L25](inner_id_wrapper_filter_h.md#L25)

- [InnerIdWrapperFilter::CheckValid · L28](inner_id_wrapper_filter_h.md#L28)

- [InnerIdWrapperFilter::ValidRatio · L33](inner_id_wrapper_filter_h.md#L33)

- [InnerIdWrapperFilter::FilterDistribution · L38](inner_id_wrapper_filter_h.md#L38)

- [InnerIdWrapperFilter::GetValidIds · L43](inner_id_wrapper_filter_h.md#L43)


<a id="L25"></a>

## `InnerIdWrapperFilter::InnerIdWrapperFilter`

源码位置：`src/impl/filter/inner_id_wrapper_filter.h:25–26`。

先从签名确认输入、返回值和 const/override，再按完整函数体的条件阅读调用点。下表保留了本函数的显式调用以及 lambda 中的调用；进入下层时用“候选实现”定位，未解析的对象由源码静态类型/运行时类型确认。

### 完整函数

```cpp
InnerIdWrapperFilter(const FilterPtr filter_impl, const LabelTable& label_table)
        : filter_impl_(filter_impl), label_table_(label_table){}
```

### 函数内部调用点：不省略标准库和辅助调用

此函数体没有显式函数调用表达式。赋值、成员初始化和隐式操作请看上面的完整源码。


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L28"></a>

## `InnerIdWrapperFilter::CheckValid`

源码位置：`src/impl/filter/inner_id_wrapper_filter.h:28–31`。

先从签名确认输入、返回值和 const/override，再按完整函数体的条件阅读调用点。下表保留了本函数的显式调用以及 lambda 中的调用；进入下层时用“候选实现”定位，未解析的对象由源码静态类型/运行时类型确认。

### 完整函数

```cpp
[[nodiscard]] bool
    CheckValid(int64_t inner_id) const override {
        return filter_impl_->CheckValid(label_table_.GetLabelById(inner_id));
    }
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L30 | filter_impl_-&gt;CheckValid | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L30 | label_table_.GetLabelById | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L33"></a>

## `InnerIdWrapperFilter::ValidRatio`

源码位置：`src/impl/filter/inner_id_wrapper_filter.h:33–36`。

先从签名确认输入、返回值和 const/override，再按完整函数体的条件阅读调用点。下表保留了本函数的显式调用以及 lambda 中的调用；进入下层时用“候选实现”定位，未解析的对象由源码静态类型/运行时类型确认。

### 完整函数

```cpp
[[nodiscard]] float
    ValidRatio() const override {
        return filter_impl_->ValidRatio();
    }
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L35 | filter_impl_-&gt;ValidRatio | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L38"></a>

## `InnerIdWrapperFilter::FilterDistribution`

源码位置：`src/impl/filter/inner_id_wrapper_filter.h:38–41`。

先从签名确认输入、返回值和 const/override，再按完整函数体的条件阅读调用点。下表保留了本函数的显式调用以及 lambda 中的调用；进入下层时用“候选实现”定位，未解析的对象由源码静态类型/运行时类型确认。

### 完整函数

```cpp
[[nodiscard]] Distribution
    FilterDistribution() const override {
        return filter_impl_->FilterDistribution();
    }
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L40 | filter_impl_-&gt;FilterDistribution | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L43"></a>

## `InnerIdWrapperFilter::GetValidIds`

源码位置：`src/impl/filter/inner_id_wrapper_filter.h:43–46`。

先从签名确认输入、返回值和 const/override，再按完整函数体的条件阅读调用点。下表保留了本函数的显式调用以及 lambda 中的调用；进入下层时用“候选实现”定位，未解析的对象由源码静态类型/运行时类型确认。

### 完整函数

```cpp
void
    GetValidIds(const int64_t** valid_ids, int64_t& count) const override {
        filter_impl_->GetValidIds(valid_ids, count);
    }
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L45 | filter_impl_-&gt;GetValidIds | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。
