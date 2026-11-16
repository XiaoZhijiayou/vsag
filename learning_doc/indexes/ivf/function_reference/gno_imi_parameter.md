# gno_imi_parameter.cpp：逐函数完整源码与调用点

[主讲解](../code_walkthrough.md) · [函数总目录](README.md)

源码：[ src/algorithm/ivf/gno_imi_parameter.cpp ](../../../../src/algorithm/ivf/gno_imi_parameter.cpp)。基线 `fd363937`。以下源码函数体完整保留；调用点表是语法树中的显式调用表达式，按源码位置排列，不代表 C++ 参数求值顺序。表中“候选实现”需结合类型和参数选分支，不能将同名函数全部视为必经路径。

- [GNOIMIParameter::GNOIMIParameter · L25](gno_imi_parameter.md#L25)

- [GNOIMIParameter::FromJson · L27](gno_imi_parameter.md#L27)

- [GNOIMIParameter::ToJson · L43](gno_imi_parameter.md#L43)

- [GNOIMIParameter::CheckCompatibility · L50](gno_imi_parameter.md#L50)


<a id="L25"></a>

## `GNOIMIParameter::GNOIMIParameter`

源码位置：`src/algorithm/ivf/gno_imi_parameter.cpp:25–25`。

先从签名确认输入、返回值和 const/override，再按完整函数体的条件阅读调用点。下表保留了本函数的显式调用以及 lambda 中的调用；进入下层时用“候选实现”定位，未解析的对象由源码静态类型/运行时类型确认。

### 完整函数

```cpp
GNOIMIParameter::GNOIMIParameter() = default;
```

### 函数内部调用点：不省略标准库和辅助调用

此函数体没有显式函数调用表达式。赋值、成员初始化和隐式操作请看上面的完整源码。


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L27"></a>

## `GNOIMIParameter::FromJson`

源码位置：`src/algorithm/ivf/gno_imi_parameter.cpp:27–41`。

先从签名确认输入、返回值和 const/override，再按完整函数体的条件阅读调用点。下表保留了本函数的显式调用以及 lambda 中的调用；进入下层时用“候选实现”定位，未解析的对象由源码静态类型/运行时类型确认。

### 完整函数

```cpp
void
GNOIMIParameter::FromJson(const JsonType& json) {
    CHECK_ARGUMENT(
        json.Contains(GNO_IMI_FIRST_ORDER_BUCKETS_COUNT_KEY),
        fmt::format("ivf parameters must contains {}", GNO_IMI_FIRST_ORDER_BUCKETS_COUNT_KEY));
    this->first_order_buckets_count =
        static_cast<int32_t>(json[GNO_IMI_FIRST_ORDER_BUCKETS_COUNT_KEY].GetInt());

    if (json.Contains(GNO_IMI_SECOND_ORDER_BUCKETS_COUNT_KEY)) {
        this->second_order_buckets_count =
            static_cast<int32_t>(json[GNO_IMI_SECOND_ORDER_BUCKETS_COUNT_KEY].GetInt());
    } else {
        this->second_order_buckets_count = this->first_order_buckets_count;
    }
}
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L29 | CHECK_ARGUMENT | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L30 | json.Contains | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L31 | fmt::format | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L33 | json[GNO_IMI_FIRST_ORDER_BUCKETS_COUNT_KEY].GetInt | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L35 | json.Contains | if_statement@35 (json.Contains(GNO_IMI_SECOND_ORDER_BUCKETS_COUNT_KEY)) | 当前参考未静态绑定；见下方边界说明 |

| L37 | json[GNO_IMI_SECOND_ORDER_BUCKETS_COUNT_KEY].GetInt | if_statement@35 (json.Contains(GNO_IMI_SECOND_ORDER_BUCKETS_COUNT_KEY)) | 当前参考未静态绑定；见下方边界说明 |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L43"></a>

## `GNOIMIParameter::ToJson`

源码位置：`src/algorithm/ivf/gno_imi_parameter.cpp:43–49`。

先从签名确认输入、返回值和 const/override，再按完整函数体的条件阅读调用点。下表保留了本函数的显式调用以及 lambda 中的调用；进入下层时用“候选实现”定位，未解析的对象由源码静态类型/运行时类型确认。

### 完整函数

```cpp
JsonType
GNOIMIParameter::ToJson() const {
    JsonType json;
    json[GNO_IMI_FIRST_ORDER_BUCKETS_COUNT_KEY].SetInt(this->first_order_buckets_count);
    json[GNO_IMI_SECOND_ORDER_BUCKETS_COUNT_KEY].SetInt(this->second_order_buckets_count);
    return json;
}
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L46 | json[GNO_IMI_FIRST_ORDER_BUCKETS_COUNT_KEY].SetInt | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L47 | json[GNO_IMI_SECOND_ORDER_BUCKETS_COUNT_KEY].SetInt | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L50"></a>

## `GNOIMIParameter::CheckCompatibility`

源码位置：`src/algorithm/ivf/gno_imi_parameter.cpp:50–56`。

先从签名确认输入、返回值和 const/override，再按完整函数体的条件阅读调用点。下表保留了本函数的显式调用以及 lambda 中的调用；进入下层时用“候选实现”定位，未解析的对象由源码静态类型/运行时类型确认。

### 完整函数

```cpp
bool
GNOIMIParameter::CheckCompatibility(const ParamPtr& other) const {
    PARAM_CAST_OR_RETURN(GNOIMIParameter, p, other);
    CHECK_FIELD_EQ(*this, *p, first_order_buckets_count);
    CHECK_FIELD_EQ(*this, *p, second_order_buckets_count);
    return true;
}
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L52 | PARAM_CAST_OR_RETURN | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L53 | CHECK_FIELD_EQ | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L54 | CHECK_FIELD_EQ | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。
