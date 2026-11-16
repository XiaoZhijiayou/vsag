# ivf_partition_strategy_parameter.cpp：逐函数完整源码与调用点

[主讲解](../code_walkthrough.md) · [函数总目录](README.md)

源码：[ src/algorithm/ivf/ivf_partition_strategy_parameter.cpp ](../../../../src/algorithm/ivf/ivf_partition_strategy_parameter.cpp)。基线 `fd363937`。以下源码函数体完整保留；调用点表是语法树中的显式调用表达式，按源码位置排列，不代表 C++ 参数求值顺序。表中“候选实现”需结合类型和参数选分支，不能将同名函数全部视为必经路径。

- [IVFPartitionStrategyParameters::IVFPartitionStrategyParameters · L28](ivf_partition_strategy_parameter.md#L28)

- [IVFPartitionStrategyParameters::FromJson · L30](ivf_partition_strategy_parameter.md#L30)

- [IVFPartitionStrategyParameters::ToJson · L72](ivf_partition_strategy_parameter.md#L72)

- [IVFPartitionStrategyParameters::CheckCompatibility · L95](ivf_partition_strategy_parameter.md#L95)


<a id="L28"></a>

## `IVFPartitionStrategyParameters::IVFPartitionStrategyParameters`

源码位置：`src/algorithm/ivf/ivf_partition_strategy_parameter.cpp:28–28`。

先从签名确认输入、返回值和 const/override，再按完整函数体的条件阅读调用点。下表保留了本函数的显式调用以及 lambda 中的调用；进入下层时用“候选实现”定位，未解析的对象由源码静态类型/运行时类型确认。

### 完整函数

```cpp
IVFPartitionStrategyParameters::IVFPartitionStrategyParameters() = default;
```

### 函数内部调用点：不省略标准库和辅助调用

此函数体没有显式函数调用表达式。赋值、成员初始化和隐式操作请看上面的完整源码。


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L30"></a>

## `IVFPartitionStrategyParameters::FromJson`

源码位置：`src/algorithm/ivf/ivf_partition_strategy_parameter.cpp:30–70`。

先从签名确认输入、返回值和 const/override，再按完整函数体的条件阅读调用点。下表保留了本函数的显式调用以及 lambda 中的调用；进入下层时用“候选实现”定位，未解析的对象由源码静态类型/运行时类型确认。

### 完整函数

```cpp
void
IVFPartitionStrategyParameters::FromJson(const JsonType& json) {
    if (json[IVF_TRAIN_TYPE_KEY].GetString() == IVF_TRAIN_TYPE_KMEANS) {
        this->partition_train_type = IVFNearestPartitionTrainerType::KMeansTrainer;
    } else if (json[IVF_TRAIN_TYPE_KEY].GetString() == IVF_TRAIN_TYPE_RANDOM) {
        this->partition_train_type = IVFNearestPartitionTrainerType::RandomTrainer;
    }

    if (json[IVF_PARTITION_STRATEGY_TYPE_KEY].GetString() == IVF_PARTITION_STRATEGY_TYPE_NEAREST) {
        this->partition_strategy_type = IVFPartitionStrategyType::IVF;
    } else if (json[IVF_PARTITION_STRATEGY_TYPE_KEY].GetString() ==
               IVF_PARTITION_STRATEGY_TYPE_GNO_IMI) {
        this->partition_strategy_type = IVFPartitionStrategyType::GNO_IMI;
    }
    if (json.Contains(IVF_ROUTE_MAX_DEGREE_KEY)) {
        this->route_max_degree = static_cast<int32_t>(json[IVF_ROUTE_MAX_DEGREE_KEY].GetInt());
        CHECK_ARGUMENT(this->route_max_degree > 0, "route_max_degree must be positive");
    }
    if (json.Contains(IVF_ROUTE_EF_CONSTRUCTION_KEY)) {
        this->route_ef_construction =
            static_cast<int32_t>(json[IVF_ROUTE_EF_CONSTRUCTION_KEY].GetInt());
        CHECK_ARGUMENT(this->route_ef_construction > 0, "route_ef_construction must be positive");
    }
    CHECK_ARGUMENT(this->route_max_degree >= 4, "route_max_degree must be at least 4");
    CHECK_ARGUMENT(this->route_ef_construction >= this->route_max_degree,
                   "route_ef_construction must be no less than route_max_degree");

    if (json.Contains(IVF_USE_ROUTE_GRAPH_KEY)) {
        this->use_route_graph = json[IVF_USE_ROUTE_GRAPH_KEY].GetBool();
    }

    this->gnoimi_param = std::make_shared<GNOIMIParameter>();
    if (this->partition_strategy_type == IVFPartitionStrategyType::GNO_IMI) {
        CHECK_ARGUMENT(
            json.Contains(IVF_PARTITION_STRATEGY_TYPE_GNO_IMI),
            fmt::format("partition strategy parameters must contains {} when strategy type is {}",
                        IVF_PARTITION_STRATEGY_TYPE_GNO_IMI,
                        IVF_PARTITION_STRATEGY_TYPE_GNO_IMI));
        this->gnoimi_param->FromJson(json[IVF_PARTITION_STRATEGY_TYPE_GNO_IMI]);
    }
}
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L32 | json[IVF_TRAIN_TYPE_KEY].GetString | if_statement@32 (json[IVF_TRAIN_TYPE_KEY].GetString() == IVF_TRAIN_TYPE_KMEANS) | 当前参考未静态绑定；见下方边界说明 |

| L34 | json[IVF_TRAIN_TYPE_KEY].GetString | if_statement@32 (json[IVF_TRAIN_TYPE_KEY].GetString() == IVF_TRAIN_TYPE_KMEANS) [else 分支] → if_statement@34 (json[IVF_TRAIN_TYPE_KEY].GetString() == IVF_TRAIN_TYPE_RANDOM) | 当前参考未静态绑定；见下方边界说明 |

| L38 | json[IVF_PARTITION_STRATEGY_TYPE_KEY].GetString | if_statement@38 (json[IVF_PARTITION_STRATEGY_TYPE_KEY].GetString() == IVF_PARTITION_STRATEGY_TYPE_NEAREST) | 当前参考未静态绑定；见下方边界说明 |

| L40 | json[IVF_PARTITION_STRATEGY_TYPE_KEY].GetString | if_statement@38 (json[IVF_PARTITION_STRATEGY_TYPE_KEY].GetString() == IVF_PARTITION_STRATEGY_TYPE_NEAREST) [else 分支] → if_statement@40 (json[IVF_PARTITION_STRATEGY_TYPE_KEY].GetString() == IVF_PARTITION_STRATEGY_TYPE_GNO_IMI) | 当前参考未静态绑定；见下方边界说明 |

| L44 | json.Contains | if_statement@44 (json.Contains(IVF_ROUTE_MAX_DEGREE_KEY)) | 当前参考未静态绑定；见下方边界说明 |

| L45 | json[IVF_ROUTE_MAX_DEGREE_KEY].GetInt | if_statement@44 (json.Contains(IVF_ROUTE_MAX_DEGREE_KEY)) | 当前参考未静态绑定；见下方边界说明 |

| L46 | CHECK_ARGUMENT | if_statement@44 (json.Contains(IVF_ROUTE_MAX_DEGREE_KEY)) | 当前参考未静态绑定；见下方边界说明 |

| L48 | json.Contains | if_statement@48 (json.Contains(IVF_ROUTE_EF_CONSTRUCTION_KEY)) | 当前参考未静态绑定；见下方边界说明 |

| L50 | json[IVF_ROUTE_EF_CONSTRUCTION_KEY].GetInt | if_statement@48 (json.Contains(IVF_ROUTE_EF_CONSTRUCTION_KEY)) | 当前参考未静态绑定；见下方边界说明 |

| L51 | CHECK_ARGUMENT | if_statement@48 (json.Contains(IVF_ROUTE_EF_CONSTRUCTION_KEY)) | 当前参考未静态绑定；见下方边界说明 |

| L53 | CHECK_ARGUMENT | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L54 | CHECK_ARGUMENT | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L57 | json.Contains | if_statement@57 (json.Contains(IVF_USE_ROUTE_GRAPH_KEY)) | 当前参考未静态绑定；见下方边界说明 |

| L58 | json[IVF_USE_ROUTE_GRAPH_KEY].GetBool | if_statement@57 (json.Contains(IVF_USE_ROUTE_GRAPH_KEY)) | 当前参考未静态绑定；见下方边界说明 |

| L61 | std::make_shared&lt;GNOIMIParameter&gt; | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L63 | CHECK_ARGUMENT | if_statement@62 (this-&gt;partition_strategy_type == IVFPartitionStrategyType::GNO_IMI) | 当前参考未静态绑定；见下方边界说明 |

| L64 | json.Contains | if_statement@62 (this-&gt;partition_strategy_type == IVFPartitionStrategyType::GNO_IMI) | 当前参考未静态绑定；见下方边界说明 |

| L65 | fmt::format | if_statement@62 (this-&gt;partition_strategy_type == IVFPartitionStrategyType::GNO_IMI) | 当前参考未静态绑定；见下方边界说明 |

| L68 | this-&gt;gnoimi_param-&gt;FromJson | if_statement@62 (this-&gt;partition_strategy_type == IVFPartitionStrategyType::GNO_IMI) | [IVFPartitionStrategyParameters::FromJson · L30](ivf_partition_strategy_parameter.md#L30) |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L72"></a>

## `IVFPartitionStrategyParameters::ToJson`

源码位置：`src/algorithm/ivf/ivf_partition_strategy_parameter.cpp:72–93`。

先从签名确认输入、返回值和 const/override，再按完整函数体的条件阅读调用点。下表保留了本函数的显式调用以及 lambda 中的调用；进入下层时用“候选实现”定位，未解析的对象由源码静态类型/运行时类型确认。

### 完整函数

```cpp
JsonType
IVFPartitionStrategyParameters::ToJson() const {
    JsonType json;
    if (this->partition_train_type == IVFNearestPartitionTrainerType::KMeansTrainer) {
        json[IVF_TRAIN_TYPE_KEY].SetString(IVF_TRAIN_TYPE_KMEANS);
    } else if (this->partition_train_type == IVFNearestPartitionTrainerType::RandomTrainer) {
        json[IVF_TRAIN_TYPE_KEY].SetString(IVF_TRAIN_TYPE_RANDOM);
    }

    if (this->partition_strategy_type == IVFPartitionStrategyType::IVF) {
        json[IVF_PARTITION_STRATEGY_TYPE_KEY].SetString(IVF_PARTITION_STRATEGY_TYPE_NEAREST);
    } else if (this->partition_strategy_type == IVFPartitionStrategyType::GNO_IMI) {
        json[IVF_PARTITION_STRATEGY_TYPE_KEY].SetString(IVF_PARTITION_STRATEGY_TYPE_GNO_IMI);
    }
    json[IVF_ROUTE_MAX_DEGREE_KEY].SetInt(this->route_max_degree);
    json[IVF_ROUTE_EF_CONSTRUCTION_KEY].SetInt(this->route_ef_construction);
    json[IVF_USE_ROUTE_GRAPH_KEY].SetBool(this->use_route_graph);
    if (this->partition_strategy_type == IVFPartitionStrategyType::GNO_IMI) {
        json[IVF_PARTITION_STRATEGY_TYPE_GNO_IMI].SetJson(this->gnoimi_param->ToJson());
    }
    return json;
}
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L76 | json[IVF_TRAIN_TYPE_KEY].SetString | if_statement@75 (this-&gt;partition_train_type == IVFNearestPartitionTrainerType::KMeansTrainer) | 当前参考未静态绑定；见下方边界说明 |

| L78 | json[IVF_TRAIN_TYPE_KEY].SetString | if_statement@75 (this-&gt;partition_train_type == IVFNearestPartitionTrainerType::KMeansTrainer) [else 分支] → if_statement@77 (this-&gt;partition_train_type == IVFNearestPartitionTrainerType::RandomTrainer) | 当前参考未静态绑定；见下方边界说明 |

| L82 | json[IVF_PARTITION_STRATEGY_TYPE_KEY].SetString | if_statement@81 (this-&gt;partition_strategy_type == IVFPartitionStrategyType::IVF) | 当前参考未静态绑定；见下方边界说明 |

| L84 | json[IVF_PARTITION_STRATEGY_TYPE_KEY].SetString | if_statement@81 (this-&gt;partition_strategy_type == IVFPartitionStrategyType::IVF) [else 分支] → if_statement@83 (this-&gt;partition_strategy_type == IVFPartitionStrategyType::GNO_IMI) | 当前参考未静态绑定；见下方边界说明 |

| L86 | json[IVF_ROUTE_MAX_DEGREE_KEY].SetInt | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L87 | json[IVF_ROUTE_EF_CONSTRUCTION_KEY].SetInt | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L88 | json[IVF_USE_ROUTE_GRAPH_KEY].SetBool | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L90 | json[IVF_PARTITION_STRATEGY_TYPE_GNO_IMI].SetJson | if_statement@89 (this-&gt;partition_strategy_type == IVFPartitionStrategyType::GNO_IMI) | 当前参考未静态绑定；见下方边界说明 |

| L90 | this-&gt;gnoimi_param-&gt;ToJson | if_statement@89 (this-&gt;partition_strategy_type == IVFPartitionStrategyType::GNO_IMI) | [IVFPartitionStrategyParameters::ToJson · L72](ivf_partition_strategy_parameter.md#L72) |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L95"></a>

## `IVFPartitionStrategyParameters::CheckCompatibility`

源码位置：`src/algorithm/ivf/ivf_partition_strategy_parameter.cpp:95–105`。

先从签名确认输入、返回值和 const/override，再按完整函数体的条件阅读调用点。下表保留了本函数的显式调用以及 lambda 中的调用；进入下层时用“候选实现”定位，未解析的对象由源码静态类型/运行时类型确认。

### 完整函数

```cpp
bool
IVFPartitionStrategyParameters::CheckCompatibility(const ParamPtr& other) const {
    PARAM_CAST_OR_RETURN(IVFPartitionStrategyParameters, p, other);
    CHECK_FIELD_EQ(*this, *p, partition_strategy_type);
    CHECK_FIELD_EQ(*this, *p, route_max_degree);
    CHECK_FIELD_EQ(*this, *p, route_ef_construction);
    // use_route_graph selects the layout only when a new index is trained. Serialized partitions
    // are self-describing and must remain loadable by readers created with either setting.
    CHECK_SUB_PARAM(*this, *p, gnoimi_param);
    return true;
}
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L97 | PARAM_CAST_OR_RETURN | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L98 | CHECK_FIELD_EQ | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L99 | CHECK_FIELD_EQ | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L100 | CHECK_FIELD_EQ | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L103 | CHECK_SUB_PARAM | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。
