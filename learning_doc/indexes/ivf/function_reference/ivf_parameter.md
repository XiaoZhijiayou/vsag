# ivf_parameter.cpp：逐函数完整源码与调用点

[主讲解](../code_walkthrough.md) · [函数总目录](README.md)

源码：[ src/algorithm/ivf/ivf_parameter.cpp ](../../../../src/algorithm/ivf/ivf_parameter.cpp)。基线 `fd363937`。以下源码函数体完整保留；调用点表是语法树中的显式调用表达式，按源码位置排列，不代表 C++ 参数求值顺序。表中“候选实现”需结合类型和参数选分支，不能将同名函数全部视为必经路径。

- [IVFParameter::FromJson · L28](ivf_parameter.md#L28)

- [IVFParameter::ToJson · L121](ivf_parameter.md#L121)

- [IVFParameter::CheckCompatibility · L133](ivf_parameter.md#L133)

- [IVFSearchParameters::FromJson · L150](ivf_parameter.md#L150)


<a id="L28"></a>

## `IVFParameter::FromJson`

源码位置：`src/algorithm/ivf/ivf_parameter.cpp:28–119`。

先从签名确认输入、返回值和 const/override，再按完整函数体的条件阅读调用点。下表保留了本函数的显式调用以及 lambda 中的调用；进入下层时用“候选实现”定位，未解析的对象由源码静态类型/运行时类型确认。

### 完整函数

```cpp
void
IVFParameter::FromJson(const JsonType& json) {
    InnerIndexParameter::FromJson(json);

    this->precise_codes_layout = PRECISE_CODES_LAYOUT_VALUE_FLAT;
    if (json.Contains(PRECISE_CODES_LAYOUT_KEY)) {
        this->precise_codes_layout = json[PRECISE_CODES_LAYOUT_KEY].GetString();
    }
    CHECK_ARGUMENT(
        this->precise_codes_layout == PRECISE_CODES_LAYOUT_VALUE_FLAT ||
            this->precise_codes_layout == PRECISE_CODES_LAYOUT_VALUE_BUCKET,
        fmt::format("invalid precise_codes_layout: {}, supported values are \"{}\" and \"{}\"",
                    this->precise_codes_layout,
                    PRECISE_CODES_LAYOUT_VALUE_FLAT,
                    PRECISE_CODES_LAYOUT_VALUE_BUCKET));

    if (json.Contains(BUCKET_PER_DATA_KEY)) {
        this->buckets_per_data = static_cast<BucketIdType>(json[BUCKET_PER_DATA_KEY].GetInt());
    }

    if (this->precise_codes_layout == PRECISE_CODES_LAYOUT_VALUE_BUCKET) {
        CHECK_ARGUMENT(this->use_reorder, "precise_codes_layout=bucket requires use_reorder=true");
        CHECK_ARGUMENT(this->buckets_per_data == 1,
                       "precise_codes_layout=bucket requires buckets_per_data=1");
        CHECK_ARGUMENT(this->reorder_source == HGRAPH_REORDER_SOURCE_PRECISE,
                       "precise_codes_layout=bucket requires reorder_source=precise");
        CHECK_ARGUMENT(this->precise_codes_param != nullptr &&
                           this->precise_codes_param->name == FLATTEN_DATA_CELL,
                       "precise_codes_layout=bucket requires ordinary flatten precise_codes");
        CHECK_ARGUMENT(this->precise_codes_param->quantizer_parameter->GetTypeName() !=
                           QUANTIZATION_TYPE_VALUE_PQFS,
                       "precise_codes_layout=bucket does not support pqfs precise quantization");
        CHECK_ARGUMENT(
            this->precise_codes_param->io_parameter == nullptr ||
                this->precise_codes_param->io_parameter->GetTypeName() != IO_TYPE_VALUE_MMAP_IO,
            "precise_codes_layout=bucket does not support mmap_io");
    }

    this->bucket_param = std::make_shared<BucketDataCellParameter>();

    CHECK_ARGUMENT(json.Contains(BUCKET_PARAMS_KEY),
                   fmt::format("ivf parameters must contains {}", BUCKET_PARAMS_KEY));

    this->bucket_param->FromJson(json[BUCKET_PARAMS_KEY]);
    CHECK_ARGUMENT(this->bucket_param->io_parameter == nullptr ||
                       this->bucket_param->io_parameter->GetTypeName() != IO_TYPE_VALUE_READER_IO,
                   "IVF base codes do not support reader_io");

    this->ivf_partition_strategy_parameter = std::make_shared<IVFPartitionStrategyParameters>();
    if (json.Contains(IVF_PARTITION_STRATEGY_PARAMS_KEY)) {
        this->ivf_partition_strategy_parameter->FromJson(json[IVF_PARTITION_STRATEGY_PARAMS_KEY]);
    }

    if (this->ivf_partition_strategy_parameter->partition_strategy_type ==
        IVFPartitionStrategyType::GNO_IMI) {
        this->bucket_param->buckets_count = static_cast<BucketIdType>(
            this->ivf_partition_strategy_parameter->gnoimi_param->first_order_buckets_count *
            this->ivf_partition_strategy_parameter->gnoimi_param->second_order_buckets_count);
    }

    // Automatically scale train_sample_count based on buckets_count if not explicitly set
    if (not json.Contains(TRAIN_SAMPLE_COUNT_KEY)) {
        constexpr int64_t samples_per_bucket = 64;
        const auto max_train_sample_count = std::numeric_limits<int64_t>::max();
        const auto bucket_sample_count =
            this->bucket_param->buckets_count > max_train_sample_count / samples_per_bucket
                ? max_train_sample_count
                : this->bucket_param->buckets_count * samples_per_bucket;
        this->train_sample_count =
            std::max(static_cast<int64_t>(MAX_TRAIN_COUNT), bucket_sample_count);
    }

    if (json.Contains(GRAPH_BUILD_THRESHOLD_KEY)) {
        this->graph_build_threshold = json[GRAPH_BUILD_THRESHOLD_KEY].GetInt();
        if (this->graph_build_threshold < 0) {
            throw VsagException(ErrorType::INVALID_ARGUMENT,
                                fmt::format("graph_build_threshold must be non-negative, got {}",
                                            this->graph_build_threshold));
        }
        if (this->graph_build_threshold > 0) {
            auto graph_json = JsonType::Parse(R"({
                "io_params": {"type": "memory_io"},
                "graph_storage_type": "flat",
                "max_degree": 64,
                "init_capacity": 100,
                "support_remove": false
            })");
            this->graph_param = GraphInterfaceParameter::GetGraphParameterByJson(
                GraphStorageTypes::GRAPH_STORAGE_TYPE_VALUE_FLAT, graph_json);
        }
    }
}
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L30 | InnerIndexParameter::FromJson | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L33 | json.Contains | if_statement@33 (json.Contains(PRECISE_CODES_LAYOUT_KEY)) | 当前参考未静态绑定；见下方边界说明 |

| L34 | json[PRECISE_CODES_LAYOUT_KEY].GetString | if_statement@33 (json.Contains(PRECISE_CODES_LAYOUT_KEY)) | 当前参考未静态绑定；见下方边界说明 |

| L36 | CHECK_ARGUMENT | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L39 | fmt::format | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L44 | json.Contains | if_statement@44 (json.Contains(BUCKET_PER_DATA_KEY)) | 当前参考未静态绑定；见下方边界说明 |

| L45 | json[BUCKET_PER_DATA_KEY].GetInt | if_statement@44 (json.Contains(BUCKET_PER_DATA_KEY)) | 当前参考未静态绑定；见下方边界说明 |

| L49 | CHECK_ARGUMENT | if_statement@48 (this-&gt;precise_codes_layout == PRECISE_CODES_LAYOUT_VALUE_BUCKET) | 当前参考未静态绑定；见下方边界说明 |

| L50 | CHECK_ARGUMENT | if_statement@48 (this-&gt;precise_codes_layout == PRECISE_CODES_LAYOUT_VALUE_BUCKET) | 当前参考未静态绑定；见下方边界说明 |

| L52 | CHECK_ARGUMENT | if_statement@48 (this-&gt;precise_codes_layout == PRECISE_CODES_LAYOUT_VALUE_BUCKET) | 当前参考未静态绑定；见下方边界说明 |

| L54 | CHECK_ARGUMENT | if_statement@48 (this-&gt;precise_codes_layout == PRECISE_CODES_LAYOUT_VALUE_BUCKET) | 当前参考未静态绑定；见下方边界说明 |

| L57 | CHECK_ARGUMENT | if_statement@48 (this-&gt;precise_codes_layout == PRECISE_CODES_LAYOUT_VALUE_BUCKET) | 当前参考未静态绑定；见下方边界说明 |

| L57 | this-&gt;precise_codes_param-&gt;quantizer_parameter-&gt;GetTypeName | if_statement@48 (this-&gt;precise_codes_layout == PRECISE_CODES_LAYOUT_VALUE_BUCKET) | 当前参考未静态绑定；见下方边界说明 |

| L60 | CHECK_ARGUMENT | if_statement@48 (this-&gt;precise_codes_layout == PRECISE_CODES_LAYOUT_VALUE_BUCKET) | 当前参考未静态绑定；见下方边界说明 |

| L62 | this-&gt;precise_codes_param-&gt;io_parameter-&gt;GetTypeName | if_statement@48 (this-&gt;precise_codes_layout == PRECISE_CODES_LAYOUT_VALUE_BUCKET) | 当前参考未静态绑定；见下方边界说明 |

| L66 | std::make_shared&lt;BucketDataCellParameter&gt; | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L68 | CHECK_ARGUMENT | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L68 | json.Contains | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L69 | fmt::format | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L71 | this-&gt;bucket_param-&gt;FromJson | 函数本体；短路求值/提前返回见源码 | [IVFParameter::FromJson · L28](ivf_parameter.md#L28) |

| L72 | CHECK_ARGUMENT | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L73 | this-&gt;bucket_param-&gt;io_parameter-&gt;GetTypeName | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L76 | std::make_shared&lt;IVFPartitionStrategyParameters&gt; | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L77 | json.Contains | if_statement@77 (json.Contains(IVF_PARTITION_STRATEGY_PARAMS_KEY)) | 当前参考未静态绑定；见下方边界说明 |

| L78 | this-&gt;ivf_partition_strategy_parameter-&gt;FromJson | if_statement@77 (json.Contains(IVF_PARTITION_STRATEGY_PARAMS_KEY)) | [IVFParameter::FromJson · L28](ivf_parameter.md#L28) |

| L89 | json.Contains | if_statement@89 (not json.Contains(TRAIN_SAMPLE_COUNT_KEY)) | 当前参考未静态绑定；见下方边界说明 |

| L91 | std::numeric_limits&lt;int64_t&gt;::max | if_statement@89 (not json.Contains(TRAIN_SAMPLE_COUNT_KEY)) | 当前参考未静态绑定；见下方边界说明 |

| L97 | std::max | if_statement@89 (not json.Contains(TRAIN_SAMPLE_COUNT_KEY)) | 当前参考未静态绑定；见下方边界说明 |

| L100 | json.Contains | if_statement@100 (json.Contains(GRAPH_BUILD_THRESHOLD_KEY)) | 当前参考未静态绑定；见下方边界说明 |

| L101 | json[GRAPH_BUILD_THRESHOLD_KEY].GetInt | if_statement@100 (json.Contains(GRAPH_BUILD_THRESHOLD_KEY)) | 当前参考未静态绑定；见下方边界说明 |

| L103 | VsagException | if_statement@100 (json.Contains(GRAPH_BUILD_THRESHOLD_KEY)) → if_statement@102 (this-&gt;graph_build_threshold &lt; 0) | 当前参考未静态绑定；见下方边界说明 |

| L104 | fmt::format | if_statement@100 (json.Contains(GRAPH_BUILD_THRESHOLD_KEY)) → if_statement@102 (this-&gt;graph_build_threshold &lt; 0) | 当前参考未静态绑定；见下方边界说明 |

| L108 | JsonType::Parse | if_statement@100 (json.Contains(GRAPH_BUILD_THRESHOLD_KEY)) → if_statement@107 (this-&gt;graph_build_threshold &gt; 0) | 当前参考未静态绑定；见下方边界说明 |

| L115 | GraphInterfaceParameter::GetGraphParameterByJson | if_statement@100 (json.Contains(GRAPH_BUILD_THRESHOLD_KEY)) → if_statement@107 (this-&gt;graph_build_threshold &gt; 0) | 当前参考未静态绑定；见下方边界说明 |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L121"></a>

## `IVFParameter::ToJson`

源码位置：`src/algorithm/ivf/ivf_parameter.cpp:121–132`。

先从签名确认输入、返回值和 const/override，再按完整函数体的条件阅读调用点。下表保留了本函数的显式调用以及 lambda 中的调用；进入下层时用“候选实现”定位，未解析的对象由源码静态类型/运行时类型确认。

### 完整函数

```cpp
JsonType
IVFParameter::ToJson() const {
    JsonType json = InnerIndexParameter::ToJson();
    json[TYPE_KEY].SetString(INDEX_IVF);
    json[BUCKET_PARAMS_KEY].SetJson(this->bucket_param->ToJson());
    json[IVF_PARTITION_STRATEGY_PARAMS_KEY].SetJson(
        this->ivf_partition_strategy_parameter->ToJson());
    json[PRECISE_CODES_LAYOUT_KEY].SetString(this->precise_codes_layout);
    json[BUCKET_PER_DATA_KEY].SetInt(this->buckets_per_data);
    json[GRAPH_BUILD_THRESHOLD_KEY].SetInt(this->graph_build_threshold);
    return json;
}
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L123 | InnerIndexParameter::ToJson | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L124 | json[TYPE_KEY].SetString | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L125 | json[BUCKET_PARAMS_KEY].SetJson | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L125 | this-&gt;bucket_param-&gt;ToJson | 函数本体；短路求值/提前返回见源码 | [IVFParameter::ToJson · L121](ivf_parameter.md#L121) |

| L126 | json[IVF_PARTITION_STRATEGY_PARAMS_KEY].SetJson | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L127 | this-&gt;ivf_partition_strategy_parameter-&gt;ToJson | 函数本体；短路求值/提前返回见源码 | [IVFParameter::ToJson · L121](ivf_parameter.md#L121) |

| L128 | json[PRECISE_CODES_LAYOUT_KEY].SetString | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L129 | json[BUCKET_PER_DATA_KEY].SetInt | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L130 | json[GRAPH_BUILD_THRESHOLD_KEY].SetInt | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L133"></a>

## `IVFParameter::CheckCompatibility`

源码位置：`src/algorithm/ivf/ivf_parameter.cpp:133–148`。

先从签名确认输入、返回值和 const/override，再按完整函数体的条件阅读调用点。下表保留了本函数的显式调用以及 lambda 中的调用；进入下层时用“候选实现”定位，未解析的对象由源码静态类型/运行时类型确认。

### 完整函数

```cpp
bool
IVFParameter::CheckCompatibility(const ParamPtr& other) const {
    if (not InnerIndexParameter::CheckCompatibility(other)) {
        return false;
    }
    PARAM_CAST_OR_RETURN(IVFParameter, p, other);
    CHECK_FIELD_EQ(*this, *p, precise_codes_layout);
    CHECK_FIELD_EQ(*this, *p, buckets_per_data);
    CHECK_FIELD_EQ(*this, *p, graph_build_threshold);
    CHECK_SUB_PARAM(*this, *p, bucket_param);
    CHECK_SUB_PARAM(*this, *p, ivf_partition_strategy_parameter);
    if (this->graph_build_threshold > 0) {
        CHECK_SUB_PARAM(*this, *p, graph_param);
    }
    return true;
}
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L135 | InnerIndexParameter::CheckCompatibility | if_statement@135 (not InnerIndexParameter::CheckCompatibility(other)) | 当前参考未静态绑定；见下方边界说明 |

| L138 | PARAM_CAST_OR_RETURN | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L139 | CHECK_FIELD_EQ | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L140 | CHECK_FIELD_EQ | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L141 | CHECK_FIELD_EQ | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L142 | CHECK_SUB_PARAM | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L143 | CHECK_SUB_PARAM | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L145 | CHECK_SUB_PARAM | if_statement@144 (this-&gt;graph_build_threshold &gt; 0) | 当前参考未静态绑定；见下方边界说明 |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L150"></a>

## `IVFSearchParameters::FromJson`

源码位置：`src/algorithm/ivf/ivf_parameter.cpp:150–187`。

先从签名确认输入、返回值和 const/override，再按完整函数体的条件阅读调用点。下表保留了本函数的显式调用以及 lambda 中的调用；进入下层时用“候选实现”定位，未解析的对象由源码静态类型/运行时类型确认。

### 完整函数

```cpp
IVFSearchParameters
IVFSearchParameters::FromJson(const std::string& json_string) {
    JsonType params = JsonType::Parse(json_string);

    IVFSearchParameters obj;

    CHECK_ARGUMENT(params.Contains(INDEX_TYPE_IVF),
                   fmt::format("parameters must contains {}", INDEX_TYPE_IVF));

    obj.IndexSearchParameter::FromJson(params[INDEX_TYPE_IVF]);

    // set obj.scan_buckets_count
    CHECK_ARGUMENT(params[INDEX_TYPE_IVF].Contains(IVF_SEARCH_PARAM_SCAN_BUCKETS_COUNT),
                   fmt::format("parameters[{}] must contains {}",
                               INDEX_TYPE_IVF,
                               IVF_SEARCH_PARAM_SCAN_BUCKETS_COUNT));
    obj.scan_buckets_count = params[INDEX_TYPE_IVF][IVF_SEARCH_PARAM_SCAN_BUCKETS_COUNT].GetInt();

    if (params[INDEX_TYPE_IVF].Contains(IVF_SEARCH_PARAM_DISABLE_BUCKET_SCAN)) {
        obj.disable_bucket_scan =
            params[INDEX_TYPE_IVF][IVF_SEARCH_PARAM_DISABLE_BUCKET_SCAN].GetBool();
    }

    // set obj.first_order_scan_ratio
    if (params[INDEX_TYPE_IVF].Contains(GNO_IMI_SEARCH_PARAM_FIRST_ORDER_SCAN_RATIO)) {
        obj.first_order_scan_ratio =
            params[INDEX_TYPE_IVF][GNO_IMI_SEARCH_PARAM_FIRST_ORDER_SCAN_RATIO].GetFloat();
    }

    if (params[INDEX_TYPE_IVF].Contains(IVF_SEARCH_PARAM_EF_SEARCH)) {
        auto ef_val = params[INDEX_TYPE_IVF][IVF_SEARCH_PARAM_EF_SEARCH].GetInt();
        if (ef_val > 0) {
            obj.ef_search = ef_val;
        }
    }

    return obj;
}
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L152 | JsonType::Parse | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L156 | CHECK_ARGUMENT | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L156 | params.Contains | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L157 | fmt::format | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L159 | obj.IndexSearchParameter::FromJson | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L162 | CHECK_ARGUMENT | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L162 | params[INDEX_TYPE_IVF].Contains | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L163 | fmt::format | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L166 | params[INDEX_TYPE_IVF][IVF_SEARCH_PARAM_SCAN_BUCKETS_COUNT].GetInt | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L168 | params[INDEX_TYPE_IVF].Contains | if_statement@168 (params[INDEX_TYPE_IVF].Contains(IVF_SEARCH_PARAM_DISABLE_BUCKET_SCAN)) | 当前参考未静态绑定；见下方边界说明 |

| L170 | params[INDEX_TYPE_IVF][IVF_SEARCH_PARAM_DISABLE_BUCKET_SCAN].GetBool | if_statement@168 (params[INDEX_TYPE_IVF].Contains(IVF_SEARCH_PARAM_DISABLE_BUCKET_SCAN)) | 当前参考未静态绑定；见下方边界说明 |

| L174 | params[INDEX_TYPE_IVF].Contains | if_statement@174 (params[INDEX_TYPE_IVF].Contains(GNO_IMI_SEARCH_PARAM_FIRST_ORDER_SCAN_RATIO)) | 当前参考未静态绑定；见下方边界说明 |

| L176 | params[INDEX_TYPE_IVF][GNO_IMI_SEARCH_PARAM_FIRST_ORDER_SCAN_RATIO].GetFloat | if_statement@174 (params[INDEX_TYPE_IVF].Contains(GNO_IMI_SEARCH_PARAM_FIRST_ORDER_SCAN_RATIO)) | 当前参考未静态绑定；见下方边界说明 |

| L179 | params[INDEX_TYPE_IVF].Contains | if_statement@179 (params[INDEX_TYPE_IVF].Contains(IVF_SEARCH_PARAM_EF_SEARCH)) | 当前参考未静态绑定；见下方边界说明 |

| L180 | params[INDEX_TYPE_IVF][IVF_SEARCH_PARAM_EF_SEARCH].GetInt | if_statement@179 (params[INDEX_TYPE_IVF].Contains(IVF_SEARCH_PARAM_EF_SEARCH)) | 当前参考未静态绑定；见下方边界说明 |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。
