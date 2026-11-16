# ivf.cpp：逐函数完整源码与调用点

[主讲解](../code_walkthrough.md) · [函数总目录](README.md)

源码：[ src/algorithm/ivf/ivf.cpp ](../../../../src/algorithm/ivf/ivf.cpp)。基线 `fd363937`。以下源码函数体完整保留；调用点表是语法树中的显式调用表达式，按源码位置排列，不代表 C++ 参数求值顺序。表中“候选实现”需结合类型和参数选分支，不能将同名函数全部视为必经路径。

- [make_precise_bucket_param · L49](ivf.md#L49)

- [build_default_ivf_param · L61](ivf.md#L61)

- [IVF::CheckAndMappingExternalParam · L110](ivf.md#L110)

- [IVF::IVF · L221](ivf.md#L221)

- [IVF::GetCodeByInnerId · L285](ivf.md#L285)

- [IVF::GetNumElements · L291](ivf.md#L291)

- [IVF::Merge · L296](ivf.md#L296)

- [IVF::get_location · L312](ivf.md#L312)

- [IVF::ExportModel · L321](ivf.md#L321)

- [IVF::merge_one_unit · L337](ivf.md#L337)

- [IVF::check_merge_illegal · L360](ivf.md#L360)

- [IVF::GetAttributeSetByInnerId · L401](ivf.md#L401)

- [IVF::CalcDistancesById · L407](ivf.md#L407)

- [IVF::CalDistanceById · L415](ivf.md#L415)

- [IVF::CalcDistanceById · L496](ivf.md#L496)

- [IVF::GetVectorByInnerId · L515](ivf.md#L515)

- [calculate_percentile · L521](ivf.md#L521)

- [get_data_stats · L536](ivf.md#L536)

- [IVF::GetStats · L575](ivf.md#L575)

- [IVF::AnalyzeIndexBySearch · L604](ivf.md#L604)

- [IVF::cal_memory_usage · L616](ivf.md#L616)

- [IVF::GetMemoryUsage · L639](ivf.md#L639)


<a id="L49"></a>

## `make_precise_bucket_param`

源码位置：`src/algorithm/ivf/ivf.cpp:49–57`。

先从签名确认输入、返回值和 const/override，再按完整函数体的条件阅读调用点。下表保留了本函数的显式调用以及 lambda 中的调用；进入下层时用“候选实现”定位，未解析的对象由源码静态类型/运行时类型确认。

### 完整函数

```cpp
BucketDataCellParamPtr
make_precise_bucket_param(const IVFParameterPtr& param) {
    auto precise_bucket_param = std::make_shared<BucketDataCellParameter>();
    precise_bucket_param->io_parameter = param->precise_codes_param->io_parameter;
    precise_bucket_param->quantizer_parameter = param->precise_codes_param->quantizer_parameter;
    precise_bucket_param->buckets_count = param->bucket_param->buckets_count;
    precise_bucket_param->use_residual_ = false;
    return precise_bucket_param;
}
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L51 | std::make_shared&lt;BucketDataCellParameter&gt; | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L61"></a>

## `build_default_ivf_param`

源码位置：`src/algorithm/ivf/ivf.cpp:61–108`。

先从签名确认输入、返回值和 const/override，再按完整函数体的条件阅读调用点。下表保留了本函数的显式调用以及 lambda 中的调用；进入下层时用“候选实现”定位，未解析的对象由源码静态类型/运行时类型确认。

### 完整函数

```cpp
JsonType
build_default_ivf_param(const JsonType& external_param) {
    const auto base_quantization_type = external_param.Contains(IVF_BASE_QUANTIZATION_TYPE)
                                            ? external_param[IVF_BASE_QUANTIZATION_TYPE].GetString()
                                            : QUANTIZATION_TYPE_VALUE_FP32;
    const auto base_io_type = external_param.Contains(IVF_BASE_IO_TYPE)
                                  ? external_param[IVF_BASE_IO_TYPE].GetString()
                                  : IO_TYPE_VALUE_MEMORY_IO;
    const auto precise_quantization_type =
        external_param.Contains(IVF_PRECISE_QUANTIZATION_TYPE)
            ? external_param[IVF_PRECISE_QUANTIZATION_TYPE].GetString()
            : QUANTIZATION_TYPE_VALUE_FP32;
    const auto precise_io_type = external_param.Contains(IVF_PRECISE_IO_TYPE)
                                     ? external_param[IVF_PRECISE_IO_TYPE].GetString()
                                     : IO_TYPE_VALUE_BLOCK_MEMORY_IO;
    JsonType json;
    json[TYPE_KEY].SetString(INDEX_TYPE_IVF);
    json[IVF_TRAIN_TYPE_KEY].SetString(IVF_TRAIN_TYPE_KMEANS);
    json[USE_ATTRIBUTE_FILTER_KEY].SetBool(false);
    json[USE_REORDER_KEY].SetBool(false);
    json[BUILD_THREAD_COUNT_KEY].SetInt(1);

    auto bucket =
        BucketDataCellParameter::CreateDefault(base_quantization_type, base_io_type)->ToJson();
    bucket[BUCKETS_COUNT_KEY].SetInt(10);
    bucket[BUCKET_USE_RESIDUAL_KEY].SetBool(false);
    json[BUCKET_PARAMS_KEY].SetJson(bucket);

    JsonType partition;
    partition[IVF_PARTITION_STRATEGY_TYPE_KEY].SetString(IVF_PARTITION_STRATEGY_TYPE_NEAREST);
    partition[IVF_TRAIN_TYPE_KEY].SetString(IVF_TRAIN_TYPE_KMEANS);
    partition[IVF_USE_ROUTE_GRAPH_KEY].SetBool(true);
    partition[IVF_PARTITION_STRATEGY_TYPE_GNO_IMI][GNO_IMI_FIRST_ORDER_BUCKETS_COUNT_KEY].SetInt(
        10);
    partition[IVF_PARTITION_STRATEGY_TYPE_GNO_IMI][GNO_IMI_SECOND_ORDER_BUCKETS_COUNT_KEY].SetInt(
        10);
    json[IVF_PARTITION_STRATEGY_PARAMS_KEY].SetJson(partition);
    json[BUCKET_PER_DATA_KEY].SetInt(1);
    json[PRECISE_CODES_LAYOUT_KEY].SetString(PRECISE_CODES_LAYOUT_VALUE_FLAT);

    auto precise =
        FlattenDataCellParameter::CreateDefault(precise_quantization_type, precise_io_type)
            ->ToJson();
    json[PRECISE_CODES_KEY].SetJson(precise);
    json[ATTR_PARAMS_KEY][ATTR_HAS_BUCKETS_KEY].SetBool(true);
    json[GRAPH_BUILD_THRESHOLD_KEY].SetInt(0);
    return json;
}
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L63 | external_param.Contains | conditional_expression@63 external_param.Contains(IVF_BASE_QUANTIZATION_TYPE) | 当前参考未静态绑定；见下方边界说明 |

| L64 | external_param[IVF_BASE_QUANTIZATION_TYPE].GetString | conditional_expression@63 external_param.Contains(IVF_BASE_QUANTIZATION_TYPE) | 当前参考未静态绑定；见下方边界说明 |

| L66 | external_param.Contains | conditional_expression@66 external_param.Contains(IVF_BASE_IO_TYPE) | 当前参考未静态绑定；见下方边界说明 |

| L67 | external_param[IVF_BASE_IO_TYPE].GetString | conditional_expression@66 external_param.Contains(IVF_BASE_IO_TYPE) | 当前参考未静态绑定；见下方边界说明 |

| L70 | external_param.Contains | conditional_expression@70 external_param.Contains(IVF_PRECISE_QUANTIZATION_TYPE) | 当前参考未静态绑定；见下方边界说明 |

| L71 | external_param[IVF_PRECISE_QUANTIZATION_TYPE].GetString | conditional_expression@70 external_param.Contains(IVF_PRECISE_QUANTIZATION_TYPE) | 当前参考未静态绑定；见下方边界说明 |

| L73 | external_param.Contains | conditional_expression@73 external_param.Contains(IVF_PRECISE_IO_TYPE) | 当前参考未静态绑定；见下方边界说明 |

| L74 | external_param[IVF_PRECISE_IO_TYPE].GetString | conditional_expression@73 external_param.Contains(IVF_PRECISE_IO_TYPE) | 当前参考未静态绑定；见下方边界说明 |

| L77 | json[TYPE_KEY].SetString | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L78 | json[IVF_TRAIN_TYPE_KEY].SetString | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L79 | json[USE_ATTRIBUTE_FILTER_KEY].SetBool | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L80 | json[USE_REORDER_KEY].SetBool | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L81 | json[BUILD_THREAD_COUNT_KEY].SetInt | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L84 | BucketDataCellParameter::CreateDefault(base_quantization_type, base_io_type)-&gt;ToJson | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L84 | BucketDataCellParameter::CreateDefault | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L85 | bucket[BUCKETS_COUNT_KEY].SetInt | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L86 | bucket[BUCKET_USE_RESIDUAL_KEY].SetBool | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L87 | json[BUCKET_PARAMS_KEY].SetJson | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L90 | partition[IVF_PARTITION_STRATEGY_TYPE_KEY].SetString | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L91 | partition[IVF_TRAIN_TYPE_KEY].SetString | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L92 | partition[IVF_USE_ROUTE_GRAPH_KEY].SetBool | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L93 | partition[IVF_PARTITION_STRATEGY_TYPE_GNO_IMI][GNO_IMI_FIRST_ORDER_BUCKETS_COUNT_KEY].SetInt | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L95 | partition[IVF_PARTITION_STRATEGY_TYPE_GNO_IMI][GNO_IMI_SECOND_ORDER_BUCKETS_COUNT_KEY].SetInt | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L97 | json[IVF_PARTITION_STRATEGY_PARAMS_KEY].SetJson | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L98 | json[BUCKET_PER_DATA_KEY].SetInt | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L99 | json[PRECISE_CODES_LAYOUT_KEY].SetString | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L102 | FlattenDataCellParameter::CreateDefault(precise_quantization_type, precise_io_type) -&gt;ToJson | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L102 | FlattenDataCellParameter::CreateDefault | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L104 | json[PRECISE_CODES_KEY].SetJson | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L105 | json[ATTR_PARAMS_KEY][ATTR_HAS_BUCKETS_KEY].SetBool | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L106 | json[GRAPH_BUILD_THRESHOLD_KEY].SetInt | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L110"></a>

## `IVF::CheckAndMappingExternalParam`

源码位置：`src/algorithm/ivf/ivf.cpp:110–219`。

先从签名确认输入、返回值和 const/override，再按完整函数体的条件阅读调用点。下表保留了本函数的显式调用以及 lambda 中的调用；进入下层时用“候选实现”定位，未解析的对象由源码静态类型/运行时类型确认。

### 完整函数

```cpp
ParamPtr
IVF::CheckAndMappingExternalParam(const JsonType& external_param,
                                  const IndexCommonParam& common_param) {
    if (common_param.data_type_ == DataTypes::DATA_TYPE_INT8) {
        throw VsagException(ErrorType::INVALID_ARGUMENT,
                            fmt::format("IVF not support {} datatype", DATATYPE_INT8));
    }

    auto inner_json = build_default_ivf_param(external_param);
    for (const auto& [key, ignored] : external_param.GetInnerJson()->items()) {
        (void)ignored;
        auto value = external_param[key];
        if (key == IVF_BASE_QUANTIZATION_TYPE) {
            inner_json[BUCKET_PARAMS_KEY][QUANTIZATION_PARAMS_KEY][TYPE_KEY].SetJson(value);
        } else if (key == IVF_BASE_IO_TYPE) {
            inner_json[BUCKET_PARAMS_KEY][IO_PARAMS_KEY][TYPE_KEY].SetJson(value);
        } else if (key == IVF_BASE_FILE_PATH) {
            inner_json[BUCKET_PARAMS_KEY][IO_PARAMS_KEY][IO_FILE_PATH_KEY].SetJson(value);
        } else if (key == IVF_BASE_CACHE_TOTAL_SIZE) {
            inner_json[BUCKET_PARAMS_KEY][IO_PARAMS_KEY][READ_CACHE_TOTAL_CACHE_SIZE_KEY].SetJson(
                value);
        } else if (key == IVF_PRECISE_QUANTIZATION_TYPE) {
            inner_json[PRECISE_CODES_KEY][QUANTIZATION_PARAMS_KEY][TYPE_KEY].SetJson(value);
        } else if (key == IVF_PRECISE_IO_TYPE) {
            inner_json[PRECISE_CODES_KEY][IO_PARAMS_KEY][TYPE_KEY].SetJson(value);
        } else if (key == IVF_PRECISE_FILE_PATH) {
            inner_json[PRECISE_CODES_KEY][IO_PARAMS_KEY][IO_FILE_PATH_KEY].SetJson(value);
        } else if (key == IVF_PRECISE_CACHE_TOTAL_SIZE) {
            inner_json[PRECISE_CODES_KEY][IO_PARAMS_KEY][READ_CACHE_TOTAL_CACHE_SIZE_KEY].SetJson(
                value);
        } else if (key == IVF_BUCKETS_COUNT) {
            inner_json[BUCKET_PARAMS_KEY][BUCKETS_COUNT_KEY].SetJson(value);
        } else if (key == IVF_TRAIN_TYPE) {
            inner_json[IVF_PARTITION_STRATEGY_PARAMS_KEY][IVF_TRAIN_TYPE_KEY].SetJson(value);
        } else if (key == IVF_PARTITION_STRATEGY_TYPE_KEY) {
            inner_json[IVF_PARTITION_STRATEGY_PARAMS_KEY][IVF_PARTITION_STRATEGY_TYPE_KEY].SetJson(
                value);
        } else if (key == IVF_USE_ROUTE_GRAPH) {
            inner_json[IVF_PARTITION_STRATEGY_PARAMS_KEY][IVF_USE_ROUTE_GRAPH_KEY].SetJson(value);
        } else if (key == GNO_IMI_FIRST_ORDER_BUCKETS_COUNT) {
            inner_json[IVF_PARTITION_STRATEGY_PARAMS_KEY][IVF_PARTITION_STRATEGY_TYPE_GNO_IMI]
                      [GNO_IMI_FIRST_ORDER_BUCKETS_COUNT_KEY]
                          .SetJson(value);
        } else if (key == GNO_IMI_SECOND_ORDER_BUCKETS_COUNT) {
            inner_json[IVF_PARTITION_STRATEGY_PARAMS_KEY][IVF_PARTITION_STRATEGY_TYPE_GNO_IMI]
                      [GNO_IMI_SECOND_ORDER_BUCKETS_COUNT_KEY]
                          .SetJson(value);
        } else if (key == BUCKET_PER_DATA_KEY) {
            inner_json[BUCKET_PER_DATA_KEY].SetJson(value);
        } else if (key == IVF_USE_REORDER) {
            inner_json[USE_REORDER_KEY].SetJson(value);
        } else if (key == IVF_PRECISE_CODES_LAYOUT) {
            inner_json[PRECISE_CODES_LAYOUT_KEY].SetJson(value);
        } else if (key == IVF_USE_RESIDUAL) {
            inner_json[BUCKET_PARAMS_KEY][BUCKET_USE_RESIDUAL_KEY].SetJson(value);
        } else if (key == USE_ATTRIBUTE_FILTER) {
            inner_json[USE_ATTRIBUTE_FILTER_KEY].SetJson(value);
        } else if (key == IVF_BASE_PQ_DIM) {
            inner_json[BUCKET_PARAMS_KEY][QUANTIZATION_PARAMS_KEY][PRODUCT_QUANTIZATION_DIM_KEY]
                .SetJson(value);
        } else if (key == RABITQ_PCA_DIM) {
            inner_json[BUCKET_PARAMS_KEY][QUANTIZATION_PARAMS_KEY][PCA_DIM_KEY].SetJson(value);
        } else if (key == RABITQ_BITS_PER_DIM_QUERY) {
            inner_json[BUCKET_PARAMS_KEY][QUANTIZATION_PARAMS_KEY]
                      [RABITQ_QUANTIZATION_BITS_PER_DIM_QUERY_KEY]
                          .SetJson(value);
        } else if (key == RABITQ_BITS_PER_DIM_BASE) {
            inner_json[BUCKET_PARAMS_KEY][QUANTIZATION_PARAMS_KEY]
                      [RABITQ_QUANTIZATION_BITS_PER_DIM_BASE_KEY]
                          .SetJson(value);
        } else if (key == RABITQ_VERSION) {
            inner_json[BUCKET_PARAMS_KEY][QUANTIZATION_PARAMS_KEY][RABITQ_QUANTIZATION_VERSION_KEY]
                .SetJson(value);
        } else if (key == RABITQ_ERROR_RATE) {
            inner_json[BUCKET_PARAMS_KEY][QUANTIZATION_PARAMS_KEY]
                      [RABITQ_QUANTIZATION_ERROR_RATE_KEY]
                          .SetJson(value);
        } else if (key == RABITQ_USE_FHT) {
            inner_json[BUCKET_PARAMS_KEY][QUANTIZATION_PARAMS_KEY][USE_FHT_KEY].SetJson(value);
        } else if (key == FAST_ENCODE_RABITQ) {
            inner_json[BUCKET_PARAMS_KEY][QUANTIZATION_PARAMS_KEY][FAST_ENCODE_RABITQ_KEY].SetJson(
                value);
            inner_json[PRECISE_CODES_KEY][QUANTIZATION_PARAMS_KEY][FAST_ENCODE_RABITQ_KEY].SetJson(
                value);
        } else if (key == FAST_ENCODE_RABITQ_ROUNDS) {
            inner_json[BUCKET_PARAMS_KEY][QUANTIZATION_PARAMS_KEY][FAST_ENCODE_RABITQ_ROUNDS_KEY]
                .SetJson(value);
            inner_json[PRECISE_CODES_KEY][QUANTIZATION_PARAMS_KEY][FAST_ENCODE_RABITQ_ROUNDS_KEY]
                .SetJson(value);
        } else if (key == IVF_THREAD_COUNT) {
            inner_json[BUILD_THREAD_COUNT_KEY].SetJson(value);
        } else if (key == TRAIN_SAMPLE_COUNT_KEY) {
            inner_json[TRAIN_SAMPLE_COUNT_KEY].SetJson(value);
        } else if (key == GRAPH_BUILD_THRESHOLD_KEY) {
            inner_json[GRAPH_BUILD_THRESHOLD_KEY].SetJson(value);
        } else if (key == IVF_BASE_ENABLE_READ_CACHE) {
            inner_json[BUCKET_PARAMS_KEY][IO_PARAMS_KEY][READ_CACHE_ENABLED_KEY].SetJson(value);
        } else if (key == IVF_PRECISE_ENABLE_READ_CACHE) {
            inner_json[PRECISE_CODES_KEY][IO_PARAMS_KEY][READ_CACHE_ENABLED_KEY].SetJson(value);
        } else {
            throw VsagException(ErrorType::INVALID_ARGUMENT,
                                fmt::format("invalid config param: {}", key));
        }
    }

    auto ivf_parameter = std::make_shared<IVFParameter>();
    ivf_parameter->FromJson(inner_json);

    return ivf_parameter;
}
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L114 | VsagException | if_statement@113 (common_param.data_type_ == DataTypes::DATA_TYPE_INT8) | 当前参考未静态绑定；见下方边界说明 |

| L115 | fmt::format | if_statement@113 (common_param.data_type_ == DataTypes::DATA_TYPE_INT8) | 当前参考未静态绑定；见下方边界说明 |

| L118 | build_default_ivf_param | 函数本体；短路求值/提前返回见源码 | [build_default_ivf_param · L61](ivf.md#L61) |

| L119 | external_param.GetInnerJson()-&gt;items | for_range_loop@119 | 当前参考未静态绑定；见下方边界说明 |

| L119 | external_param.GetInnerJson | for_range_loop@119 | 当前参考未静态绑定；见下方边界说明 |

| L123 | inner_json[BUCKET_PARAMS_KEY][QUANTIZATION_PARAMS_KEY][TYPE_KEY].SetJson | for_range_loop@119 → if_statement@122 (key == IVF_BASE_QUANTIZATION_TYPE) | 当前参考未静态绑定；见下方边界说明 |

| L125 | inner_json[BUCKET_PARAMS_KEY][IO_PARAMS_KEY][TYPE_KEY].SetJson | for_range_loop@119 → if_statement@122 (key == IVF_BASE_QUANTIZATION_TYPE) [else 分支] → if_statement@124 (key == IVF_BASE_IO_TYPE) | 当前参考未静态绑定；见下方边界说明 |

| L127 | inner_json[BUCKET_PARAMS_KEY][IO_PARAMS_KEY][IO_FILE_PATH_KEY].SetJson | for_range_loop@119 → if_statement@122 (key == IVF_BASE_QUANTIZATION_TYPE) [else 分支] → if_statement@124 (key == IVF_BASE_IO_TYPE) [else 分支] → if_statement@126 (key == IVF_BASE_FILE_PATH) | 当前参考未静态绑定；见下方边界说明 |

| L129 | inner_json[BUCKET_PARAMS_KEY][IO_PARAMS_KEY][READ_CACHE_TOTAL_CACHE_SIZE_KEY].SetJson | for_range_loop@119 → if_statement@122 (key == IVF_BASE_QUANTIZATION_TYPE) [else 分支] → if_statement@124 (key == IVF_BASE_IO_TYPE) [else 分支] → if_statement@126 (key == IVF_BASE_FILE_PATH) [else 分支] → if_statement@128 (key == IVF_BASE_CACHE_TOTAL_SIZE) | 当前参考未静态绑定；见下方边界说明 |

| L132 | inner_json[PRECISE_CODES_KEY][QUANTIZATION_PARAMS_KEY][TYPE_KEY].SetJson | for_range_loop@119 → if_statement@122 (key == IVF_BASE_QUANTIZATION_TYPE) [else 分支] → if_statement@124 (key == IVF_BASE_IO_TYPE) [else 分支] → if_statement@126 (key == IVF_BASE_FILE_PATH) [else 分支] → if_statement@128 (key == IVF_BASE_CACHE_TOTAL_SIZE) [else 分支] → if_statement@131 (key == IVF_PRECISE_QUANTIZATION_TYPE) | 当前参考未静态绑定；见下方边界说明 |

| L134 | inner_json[PRECISE_CODES_KEY][IO_PARAMS_KEY][TYPE_KEY].SetJson | for_range_loop@119 → if_statement@122 (key == IVF_BASE_QUANTIZATION_TYPE) [else 分支] → if_statement@124 (key == IVF_BASE_IO_TYPE) [else 分支] → if_statement@126 (key == IVF_BASE_FILE_PATH) [else 分支] → if_statement@128 (key == IVF_BASE_CACHE_TOTAL_SIZE) [else 分支] → if_statement@131 (key == IVF_PRECISE_QUANTIZATION_TYPE) [else 分支] → if_statement@133 (key == IVF_PRECISE_IO_TYPE) | 当前参考未静态绑定；见下方边界说明 |

| L136 | inner_json[PRECISE_CODES_KEY][IO_PARAMS_KEY][IO_FILE_PATH_KEY].SetJson | for_range_loop@119 → if_statement@122 (key == IVF_BASE_QUANTIZATION_TYPE) [else 分支] → if_statement@124 (key == IVF_BASE_IO_TYPE) [else 分支] → if_statement@126 (key == IVF_BASE_FILE_PATH) [else 分支] → if_statement@128 (key == IVF_BASE_CACHE_TOTAL_SIZE) [else 分支] → if_statement@131 (key == IVF_PRECISE_QUANTIZATION_TYPE) [else 分支] → if_statement@133 (key == IVF_PRECISE_IO_TYPE) [else 分支] → if_statement@135 (key == IVF_PRECISE_FILE_PATH) | 当前参考未静态绑定；见下方边界说明 |

| L138 | inner_json[PRECISE_CODES_KEY][IO_PARAMS_KEY][READ_CACHE_TOTAL_CACHE_SIZE_KEY].SetJson | for_range_loop@119 → if_statement@122 (key == IVF_BASE_QUANTIZATION_TYPE) [else 分支] → if_statement@124 (key == IVF_BASE_IO_TYPE) [else 分支] → if_statement@126 (key == IVF_BASE_FILE_PATH) [else 分支] → if_statement@128 (key == IVF_BASE_CACHE_TOTAL_SIZE) [else 分支] → if_statement@131 (key == IVF_PRECISE_QUANTIZATION_TYPE) [else 分支] → if_statement@133 (key == IVF_PRECISE_IO_TYPE) [else 分支] → if_statement@135 (key == IVF_PRECISE_FILE_PATH) [else 分支] → if_statement@137 (key == IVF_PRECISE_CACHE_TOTAL_SIZE) | 当前参考未静态绑定；见下方边界说明 |

| L141 | inner_json[BUCKET_PARAMS_KEY][BUCKETS_COUNT_KEY].SetJson | for_range_loop@119 → if_statement@122 (key == IVF_BASE_QUANTIZATION_TYPE) [else 分支] → if_statement@124 (key == IVF_BASE_IO_TYPE) [else 分支] → if_statement@126 (key == IVF_BASE_FILE_PATH) [else 分支] → if_statement@128 (key == IVF_BASE_CACHE_TOTAL_SIZE) [else 分支] → if_statement@131 (key == IVF_PRECISE_QUANTIZATION_TYPE) [else 分支] → if_statement@133 (key == IVF_PRECISE_IO_TYPE) [else 分支] → if_statement@135 (key == IVF_PRECISE_FILE_PATH) [else 分支] → if_statement@137 (key == IVF_PRECISE_CACHE_TOTAL_SIZE) [else 分支] → if_statement@140 (key == IVF_BUCKETS_COUNT) | 当前参考未静态绑定；见下方边界说明 |

| L143 | inner_json[IVF_PARTITION_STRATEGY_PARAMS_KEY][IVF_TRAIN_TYPE_KEY].SetJson | for_range_loop@119 → if_statement@122 (key == IVF_BASE_QUANTIZATION_TYPE) [else 分支] → if_statement@124 (key == IVF_BASE_IO_TYPE) [else 分支] → if_statement@126 (key == IVF_BASE_FILE_PATH) [else 分支] → if_statement@128 (key == IVF_BASE_CACHE_TOTAL_SIZE) [else 分支] → if_statement@131 (key == IVF_PRECISE_QUANTIZATION_TYPE) [else 分支] → if_statement@133 (key == IVF_PRECISE_IO_TYPE) [else 分支] → if_statement@135 (key == IVF_PRECISE_FILE_PATH) [else 分支] → if_statement@137 (key == IVF_PRECISE_CACHE_TOTAL_SIZE) [else 分支] → if_statement@140 (key == IVF_BUCKETS_COUNT) [else 分支] → if_statement@142 (key == IVF_TRAIN_TYPE) | 当前参考未静态绑定；见下方边界说明 |

| L145 | inner_json[IVF_PARTITION_STRATEGY_PARAMS_KEY][IVF_PARTITION_STRATEGY_TYPE_KEY].SetJson | for_range_loop@119 → if_statement@122 (key == IVF_BASE_QUANTIZATION_TYPE) [else 分支] → if_statement@124 (key == IVF_BASE_IO_TYPE) [else 分支] → if_statement@126 (key == IVF_BASE_FILE_PATH) [else 分支] → if_statement@128 (key == IVF_BASE_CACHE_TOTAL_SIZE) [else 分支] → if_statement@131 (key == IVF_PRECISE_QUANTIZATION_TYPE) [else 分支] → if_statement@133 (key == IVF_PRECISE_IO_TYPE) [else 分支] → if_statement@135 (key == IVF_PRECISE_FILE_PATH) [else 分支] → if_statement@137 (key == IVF_PRECISE_CACHE_TOTAL_SIZE) [else 分支] → if_statement@140 (key == IVF_BUCKETS_COUNT) [else 分支] → if_statement@142 (key == IVF_TRAIN_TYPE) [else 分支] → if_statement@144 (key == IVF_PARTITION_STRATEGY_TYPE_KEY) | 当前参考未静态绑定；见下方边界说明 |

| L148 | inner_json[IVF_PARTITION_STRATEGY_PARAMS_KEY][IVF_USE_ROUTE_GRAPH_KEY].SetJson | for_range_loop@119 → if_statement@122 (key == IVF_BASE_QUANTIZATION_TYPE) [else 分支] → if_statement@124 (key == IVF_BASE_IO_TYPE) [else 分支] → if_statement@126 (key == IVF_BASE_FILE_PATH) [else 分支] → if_statement@128 (key == IVF_BASE_CACHE_TOTAL_SIZE) [else 分支] → if_statement@131 (key == IVF_PRECISE_QUANTIZATION_TYPE) [else 分支] → if_statement@133 (key == IVF_PRECISE_IO_TYPE) [else 分支] → if_statement@135 (key == IVF_PRECISE_FILE_PATH) [else 分支] → if_statement@137 (key == IVF_PRECISE_CACHE_TOTAL_SIZE) [else 分支] → if_statement@140 (key == IVF_BUCKETS_COUNT) [else 分支] → if_statement@142 (key == IVF_TRAIN_TYPE) [else 分支] → if_statement@144 (key == IVF_PARTITION_STRATEGY_TYPE_KEY) [else 分支] → if_statement@147 (key == IVF_USE_ROUTE_GRAPH) | 当前参考未静态绑定；见下方边界说明 |

| L150 | inner_json[IVF_PARTITION_STRATEGY_PARAMS_KEY][IVF_PARTITION_STRATEGY_TYPE_GNO_IMI] [GNO_IMI_FIRST_ORDER_BUCKETS_COUNT_KEY] .SetJson | for_range_loop@119 → if_statement@122 (key == IVF_BASE_QUANTIZATION_TYPE) [else 分支] → if_statement@124 (key == IVF_BASE_IO_TYPE) [else 分支] → if_statement@126 (key == IVF_BASE_FILE_PATH) [else 分支] → if_statement@128 (key == IVF_BASE_CACHE_TOTAL_SIZE) [else 分支] → if_statement@131 (key == IVF_PRECISE_QUANTIZATION_TYPE) [else 分支] → if_statement@133 (key == IVF_PRECISE_IO_TYPE) [else 分支] → if_statement@135 (key == IVF_PRECISE_FILE_PATH) [else 分支] → if_statement@137 (key == IVF_PRECISE_CACHE_TOTAL_SIZE) [else 分支] → if_statement@140 (key == IVF_BUCKETS_COUNT) [else 分支] → if_statement@142 (key == IVF_TRAIN_TYPE) [else 分支] → if_statement@144 (key == IVF_PARTITION_STRATEGY_TYPE_KEY) [else 分支] → if_statement@147 (key == IVF_USE_ROUTE_GRAPH) [else 分支] → if_statement@149 (key == GNO_IMI_FIRST_ORDER_BUCKETS_COUNT) | 当前参考未静态绑定；见下方边界说明 |

| L154 | inner_json[IVF_PARTITION_STRATEGY_PARAMS_KEY][IVF_PARTITION_STRATEGY_TYPE_GNO_IMI] [GNO_IMI_SECOND_ORDER_BUCKETS_COUNT_KEY] .SetJson | for_range_loop@119 → if_statement@122 (key == IVF_BASE_QUANTIZATION_TYPE) [else 分支] → if_statement@124 (key == IVF_BASE_IO_TYPE) [else 分支] → if_statement@126 (key == IVF_BASE_FILE_PATH) [else 分支] → if_statement@128 (key == IVF_BASE_CACHE_TOTAL_SIZE) [else 分支] → if_statement@131 (key == IVF_PRECISE_QUANTIZATION_TYPE) [else 分支] → if_statement@133 (key == IVF_PRECISE_IO_TYPE) [else 分支] → if_statement@135 (key == IVF_PRECISE_FILE_PATH) [else 分支] → if_statement@137 (key == IVF_PRECISE_CACHE_TOTAL_SIZE) [else 分支] → if_statement@140 (key == IVF_BUCKETS_COUNT) [else 分支] → if_statement@142 (key == IVF_TRAIN_TYPE) [else 分支] → if_statement@144 (key == IVF_PARTITION_STRATEGY_TYPE_KEY) [else 分支] → if_statement@147 (key == IVF_USE_ROUTE_GRAPH) [else 分支] → if_statement@149 (key == GNO_IMI_FIRST_ORDER_BUCKETS_COUNT) [else 分支] → if_statement@153 (key == GNO_IMI_SECOND_ORDER_BUCKETS_COUNT) | 当前参考未静态绑定；见下方边界说明 |

| L158 | inner_json[BUCKET_PER_DATA_KEY].SetJson | for_range_loop@119 → if_statement@122 (key == IVF_BASE_QUANTIZATION_TYPE) [else 分支] → if_statement@124 (key == IVF_BASE_IO_TYPE) [else 分支] → if_statement@126 (key == IVF_BASE_FILE_PATH) [else 分支] → if_statement@128 (key == IVF_BASE_CACHE_TOTAL_SIZE) [else 分支] → if_statement@131 (key == IVF_PRECISE_QUANTIZATION_TYPE) [else 分支] → if_statement@133 (key == IVF_PRECISE_IO_TYPE) [else 分支] → if_statement@135 (key == IVF_PRECISE_FILE_PATH) [else 分支] → if_statement@137 (key == IVF_PRECISE_CACHE_TOTAL_SIZE) [else 分支] → if_statement@140 (key == IVF_BUCKETS_COUNT) [else 分支] → if_statement@142 (key == IVF_TRAIN_TYPE) [else 分支] → if_statement@144 (key == IVF_PARTITION_STRATEGY_TYPE_KEY) [else 分支] → if_statement@147 (key == IVF_USE_ROUTE_GRAPH) [else 分支] → if_statement@149 (key == GNO_IMI_FIRST_ORDER_BUCKETS_COUNT) [else 分支] → if_statement@153 (key == GNO_IMI_SECOND_ORDER_BUCKETS_COUNT) [else 分支] → if_statement@157 (key == BUCKET_PER_DATA_KEY) | 当前参考未静态绑定；见下方边界说明 |

| L160 | inner_json[USE_REORDER_KEY].SetJson | for_range_loop@119 → if_statement@122 (key == IVF_BASE_QUANTIZATION_TYPE) [else 分支] → if_statement@124 (key == IVF_BASE_IO_TYPE) [else 分支] → if_statement@126 (key == IVF_BASE_FILE_PATH) [else 分支] → if_statement@128 (key == IVF_BASE_CACHE_TOTAL_SIZE) [else 分支] → if_statement@131 (key == IVF_PRECISE_QUANTIZATION_TYPE) [else 分支] → if_statement@133 (key == IVF_PRECISE_IO_TYPE) [else 分支] → if_statement@135 (key == IVF_PRECISE_FILE_PATH) [else 分支] → if_statement@137 (key == IVF_PRECISE_CACHE_TOTAL_SIZE) [else 分支] → if_statement@140 (key == IVF_BUCKETS_COUNT) [else 分支] → if_statement@142 (key == IVF_TRAIN_TYPE) [else 分支] → if_statement@144 (key == IVF_PARTITION_STRATEGY_TYPE_KEY) [else 分支] → if_statement@147 (key == IVF_USE_ROUTE_GRAPH) [else 分支] → if_statement@149 (key == GNO_IMI_FIRST_ORDER_BUCKETS_COUNT) [else 分支] → if_statement@153 (key == GNO_IMI_SECOND_ORDER_BUCKETS_COUNT) [else 分支] → if_statement@157 (key == BUCKET_PER_DATA_KEY) [else 分支] → if_statement@159 (key == IVF_USE_REORDER) | 当前参考未静态绑定；见下方边界说明 |

| L162 | inner_json[PRECISE_CODES_LAYOUT_KEY].SetJson | for_range_loop@119 → if_statement@122 (key == IVF_BASE_QUANTIZATION_TYPE) [else 分支] → if_statement@124 (key == IVF_BASE_IO_TYPE) [else 分支] → if_statement@126 (key == IVF_BASE_FILE_PATH) [else 分支] → if_statement@128 (key == IVF_BASE_CACHE_TOTAL_SIZE) [else 分支] → if_statement@131 (key == IVF_PRECISE_QUANTIZATION_TYPE) [else 分支] → if_statement@133 (key == IVF_PRECISE_IO_TYPE) [else 分支] → if_statement@135 (key == IVF_PRECISE_FILE_PATH) [else 分支] → if_statement@137 (key == IVF_PRECISE_CACHE_TOTAL_SIZE) [else 分支] → if_statement@140 (key == IVF_BUCKETS_COUNT) [else 分支] → if_statement@142 (key == IVF_TRAIN_TYPE) [else 分支] → if_statement@144 (key == IVF_PARTITION_STRATEGY_TYPE_KEY) [else 分支] → if_statement@147 (key == IVF_USE_ROUTE_GRAPH) [else 分支] → if_statement@149 (key == GNO_IMI_FIRST_ORDER_BUCKETS_COUNT) [else 分支] → if_statement@153 (key == GNO_IMI_SECOND_ORDER_BUCKETS_COUNT) [else 分支] → if_statement@157 (key == BUCKET_PER_DATA_KEY) [else 分支] → if_statement@159 (key == IVF_USE_REORDER) [else 分支] → if_statement@161 (key == IVF_PRECISE_CODES_LAYOUT) | 当前参考未静态绑定；见下方边界说明 |

| L164 | inner_json[BUCKET_PARAMS_KEY][BUCKET_USE_RESIDUAL_KEY].SetJson | for_range_loop@119 → if_statement@122 (key == IVF_BASE_QUANTIZATION_TYPE) [else 分支] → if_statement@124 (key == IVF_BASE_IO_TYPE) [else 分支] → if_statement@126 (key == IVF_BASE_FILE_PATH) [else 分支] → if_statement@128 (key == IVF_BASE_CACHE_TOTAL_SIZE) [else 分支] → if_statement@131 (key == IVF_PRECISE_QUANTIZATION_TYPE) [else 分支] → if_statement@133 (key == IVF_PRECISE_IO_TYPE) [else 分支] → if_statement@135 (key == IVF_PRECISE_FILE_PATH) [else 分支] → if_statement@137 (key == IVF_PRECISE_CACHE_TOTAL_SIZE) [else 分支] → if_statement@140 (key == IVF_BUCKETS_COUNT) [else 分支] → if_statement@142 (key == IVF_TRAIN_TYPE) [else 分支] → if_statement@144 (key == IVF_PARTITION_STRATEGY_TYPE_KEY) [else 分支] → if_statement@147 (key == IVF_USE_ROUTE_GRAPH) [else 分支] → if_statement@149 (key == GNO_IMI_FIRST_ORDER_BUCKETS_COUNT) [else 分支] → if_statement@153 (key == GNO_IMI_SECOND_ORDER_BUCKETS_COUNT) [else 分支] → if_statement@157 (key == BUCKET_PER_DATA_KEY) [else 分支] → if_statement@159 (key == IVF_USE_REORDER) [else 分支] → if_statement@161 (key == IVF_PRECISE_CODES_LAYOUT) [else 分支] → if_statement@163 (key == IVF_USE_RESIDUAL) | 当前参考未静态绑定；见下方边界说明 |

| L166 | inner_json[USE_ATTRIBUTE_FILTER_KEY].SetJson | for_range_loop@119 → if_statement@122 (key == IVF_BASE_QUANTIZATION_TYPE) [else 分支] → if_statement@124 (key == IVF_BASE_IO_TYPE) [else 分支] → if_statement@126 (key == IVF_BASE_FILE_PATH) [else 分支] → if_statement@128 (key == IVF_BASE_CACHE_TOTAL_SIZE) [else 分支] → if_statement@131 (key == IVF_PRECISE_QUANTIZATION_TYPE) [else 分支] → if_statement@133 (key == IVF_PRECISE_IO_TYPE) [else 分支] → if_statement@135 (key == IVF_PRECISE_FILE_PATH) [else 分支] → if_statement@137 (key == IVF_PRECISE_CACHE_TOTAL_SIZE) [else 分支] → if_statement@140 (key == IVF_BUCKETS_COUNT) [else 分支] → if_statement@142 (key == IVF_TRAIN_TYPE) [else 分支] → if_statement@144 (key == IVF_PARTITION_STRATEGY_TYPE_KEY) [else 分支] → if_statement@147 (key == IVF_USE_ROUTE_GRAPH) [else 分支] → if_statement@149 (key == GNO_IMI_FIRST_ORDER_BUCKETS_COUNT) [else 分支] → if_statement@153 (key == GNO_IMI_SECOND_ORDER_BUCKETS_COUNT) [else 分支] → if_statement@157 (key == BUCKET_PER_DATA_KEY) [else 分支] → if_statement@159 (key == IVF_USE_REORDER) [else 分支] → if_statement@161 (key == IVF_PRECISE_CODES_LAYOUT) [else 分支] → if_statement@163 (key == IVF_USE_RESIDUAL) [else 分支] → if_statement@165 (key == USE_ATTRIBUTE_FILTER) | 当前参考未静态绑定；见下方边界说明 |

| L168 | inner_json[BUCKET_PARAMS_KEY][QUANTIZATION_PARAMS_KEY][PRODUCT_QUANTIZATION_DIM_KEY] .SetJson | for_range_loop@119 → if_statement@122 (key == IVF_BASE_QUANTIZATION_TYPE) [else 分支] → if_statement@124 (key == IVF_BASE_IO_TYPE) [else 分支] → if_statement@126 (key == IVF_BASE_FILE_PATH) [else 分支] → if_statement@128 (key == IVF_BASE_CACHE_TOTAL_SIZE) [else 分支] → if_statement@131 (key == IVF_PRECISE_QUANTIZATION_TYPE) [else 分支] → if_statement@133 (key == IVF_PRECISE_IO_TYPE) [else 分支] → if_statement@135 (key == IVF_PRECISE_FILE_PATH) [else 分支] → if_statement@137 (key == IVF_PRECISE_CACHE_TOTAL_SIZE) [else 分支] → if_statement@140 (key == IVF_BUCKETS_COUNT) [else 分支] → if_statement@142 (key == IVF_TRAIN_TYPE) [else 分支] → if_statement@144 (key == IVF_PARTITION_STRATEGY_TYPE_KEY) [else 分支] → if_statement@147 (key == IVF_USE_ROUTE_GRAPH) [else 分支] → if_statement@149 (key == GNO_IMI_FIRST_ORDER_BUCKETS_COUNT) [else 分支] → if_statement@153 (key == GNO_IMI_SECOND_ORDER_BUCKETS_COUNT) [else 分支] → if_statement@157 (key == BUCKET_PER_DATA_KEY) [else 分支] → if_statement@159 (key == IVF_USE_REORDER) [else 分支] → if_statement@161 (key == IVF_PRECISE_CODES_LAYOUT) [else 分支] → if_statement@163 (key == IVF_USE_RESIDUAL) [else 分支] → if_statement@165 (key == USE_ATTRIBUTE_FILTER) [else 分支] → if_statement@167 (key == IVF_BASE_PQ_DIM) | 当前参考未静态绑定；见下方边界说明 |

| L171 | inner_json[BUCKET_PARAMS_KEY][QUANTIZATION_PARAMS_KEY][PCA_DIM_KEY].SetJson | for_range_loop@119 → if_statement@122 (key == IVF_BASE_QUANTIZATION_TYPE) [else 分支] → if_statement@124 (key == IVF_BASE_IO_TYPE) [else 分支] → if_statement@126 (key == IVF_BASE_FILE_PATH) [else 分支] → if_statement@128 (key == IVF_BASE_CACHE_TOTAL_SIZE) [else 分支] → if_statement@131 (key == IVF_PRECISE_QUANTIZATION_TYPE) [else 分支] → if_statement@133 (key == IVF_PRECISE_IO_TYPE) [else 分支] → if_statement@135 (key == IVF_PRECISE_FILE_PATH) [else 分支] → if_statement@137 (key == IVF_PRECISE_CACHE_TOTAL_SIZE) [else 分支] → if_statement@140 (key == IVF_BUCKETS_COUNT) [else 分支] → if_statement@142 (key == IVF_TRAIN_TYPE) [else 分支] → if_statement@144 (key == IVF_PARTITION_STRATEGY_TYPE_KEY) [else 分支] → if_statement@147 (key == IVF_USE_ROUTE_GRAPH) [else 分支] → if_statement@149 (key == GNO_IMI_FIRST_ORDER_BUCKETS_COUNT) [else 分支] → if_statement@153 (key == GNO_IMI_SECOND_ORDER_BUCKETS_COUNT) [else 分支] → if_statement@157 (key == BUCKET_PER_DATA_KEY) [else 分支] → if_statement@159 (key == IVF_USE_REORDER) [else 分支] → if_statement@161 (key == IVF_PRECISE_CODES_LAYOUT) [else 分支] → if_statement@163 (key == IVF_USE_RESIDUAL) [else 分支] → if_statement@165 (key == USE_ATTRIBUTE_FILTER) [else 分支] → if_statement@167 (key == IVF_BASE_PQ_DIM) [else 分支] → if_statement@170 (key == RABITQ_PCA_DIM) | 当前参考未静态绑定；见下方边界说明 |

| L173 | inner_json[BUCKET_PARAMS_KEY][QUANTIZATION_PARAMS_KEY] [RABITQ_QUANTIZATION_BITS_PER_DIM_QUERY_KEY] .SetJson | for_range_loop@119 → if_statement@122 (key == IVF_BASE_QUANTIZATION_TYPE) [else 分支] → if_statement@124 (key == IVF_BASE_IO_TYPE) [else 分支] → if_statement@126 (key == IVF_BASE_FILE_PATH) [else 分支] → if_statement@128 (key == IVF_BASE_CACHE_TOTAL_SIZE) [else 分支] → if_statement@131 (key == IVF_PRECISE_QUANTIZATION_TYPE) [else 分支] → if_statement@133 (key == IVF_PRECISE_IO_TYPE) [else 分支] → if_statement@135 (key == IVF_PRECISE_FILE_PATH) [else 分支] → if_statement@137 (key == IVF_PRECISE_CACHE_TOTAL_SIZE) [else 分支] → if_statement@140 (key == IVF_BUCKETS_COUNT) [else 分支] → if_statement@142 (key == IVF_TRAIN_TYPE) [else 分支] → if_statement@144 (key == IVF_PARTITION_STRATEGY_TYPE_KEY) [else 分支] → if_statement@147 (key == IVF_USE_ROUTE_GRAPH) [else 分支] → if_statement@149 (key == GNO_IMI_FIRST_ORDER_BUCKETS_COUNT) [else 分支] → if_statement@153 (key == GNO_IMI_SECOND_ORDER_BUCKETS_COUNT) [else 分支] → if_statement@157 (key == BUCKET_PER_DATA_KEY) [else 分支] → if_statement@159 (key == IVF_USE_REORDER) [else 分支] → if_statement@161 (key == IVF_PRECISE_CODES_LAYOUT) [else 分支] → if_statement@163 (key == IVF_USE_RESIDUAL) [else 分支] → if_statement@165 (key == USE_ATTRIBUTE_FILTER) [else 分支] → if_statement@167 (key == IVF_BASE_PQ_DIM) [else 分支] → if_statement@170 (key == RABITQ_PCA_DIM) [else 分支] → if_statement@172 (key == RABITQ_BITS_PER_DIM_QUERY) | 当前参考未静态绑定；见下方边界说明 |

| L177 | inner_json[BUCKET_PARAMS_KEY][QUANTIZATION_PARAMS_KEY] [RABITQ_QUANTIZATION_BITS_PER_DIM_BASE_KEY] .SetJson | for_range_loop@119 → if_statement@122 (key == IVF_BASE_QUANTIZATION_TYPE) [else 分支] → if_statement@124 (key == IVF_BASE_IO_TYPE) [else 分支] → if_statement@126 (key == IVF_BASE_FILE_PATH) [else 分支] → if_statement@128 (key == IVF_BASE_CACHE_TOTAL_SIZE) [else 分支] → if_statement@131 (key == IVF_PRECISE_QUANTIZATION_TYPE) [else 分支] → if_statement@133 (key == IVF_PRECISE_IO_TYPE) [else 分支] → if_statement@135 (key == IVF_PRECISE_FILE_PATH) [else 分支] → if_statement@137 (key == IVF_PRECISE_CACHE_TOTAL_SIZE) [else 分支] → if_statement@140 (key == IVF_BUCKETS_COUNT) [else 分支] → if_statement@142 (key == IVF_TRAIN_TYPE) [else 分支] → if_statement@144 (key == IVF_PARTITION_STRATEGY_TYPE_KEY) [else 分支] → if_statement@147 (key == IVF_USE_ROUTE_GRAPH) [else 分支] → if_statement@149 (key == GNO_IMI_FIRST_ORDER_BUCKETS_COUNT) [else 分支] → if_statement@153 (key == GNO_IMI_SECOND_ORDER_BUCKETS_COUNT) [else 分支] → if_statement@157 (key == BUCKET_PER_DATA_KEY) [else 分支] → if_statement@159 (key == IVF_USE_REORDER) [else 分支] → if_statement@161 (key == IVF_PRECISE_CODES_LAYOUT) [else 分支] → if_statement@163 (key == IVF_USE_RESIDUAL) [else 分支] → if_statement@165 (key == USE_ATTRIBUTE_FILTER) [else 分支] → if_statement@167 (key == IVF_BASE_PQ_DIM) [else 分支] → if_statement@170 (key == RABITQ_PCA_DIM) [else 分支] → if_statement@172 (key == RABITQ_BITS_PER_DIM_QUERY) [else 分支] → if_statement@176 (key == RABITQ_BITS_PER_DIM_BASE) | 当前参考未静态绑定；见下方边界说明 |

| L181 | inner_json[BUCKET_PARAMS_KEY][QUANTIZATION_PARAMS_KEY][RABITQ_QUANTIZATION_VERSION_KEY] .SetJson | for_range_loop@119 → if_statement@122 (key == IVF_BASE_QUANTIZATION_TYPE) [else 分支] → if_statement@124 (key == IVF_BASE_IO_TYPE) [else 分支] → if_statement@126 (key == IVF_BASE_FILE_PATH) [else 分支] → if_statement@128 (key == IVF_BASE_CACHE_TOTAL_SIZE) [else 分支] → if_statement@131 (key == IVF_PRECISE_QUANTIZATION_TYPE) [else 分支] → if_statement@133 (key == IVF_PRECISE_IO_TYPE) [else 分支] → if_statement@135 (key == IVF_PRECISE_FILE_PATH) [else 分支] → if_statement@137 (key == IVF_PRECISE_CACHE_TOTAL_SIZE) [else 分支] → if_statement@140 (key == IVF_BUCKETS_COUNT) [else 分支] → if_statement@142 (key == IVF_TRAIN_TYPE) [else 分支] → if_statement@144 (key == IVF_PARTITION_STRATEGY_TYPE_KEY) [else 分支] → if_statement@147 (key == IVF_USE_ROUTE_GRAPH) [else 分支] → if_statement@149 (key == GNO_IMI_FIRST_ORDER_BUCKETS_COUNT) [else 分支] → if_statement@153 (key == GNO_IMI_SECOND_ORDER_BUCKETS_COUNT) [else 分支] → if_statement@157 (key == BUCKET_PER_DATA_KEY) [else 分支] → if_statement@159 (key == IVF_USE_REORDER) [else 分支] → if_statement@161 (key == IVF_PRECISE_CODES_LAYOUT) [else 分支] → if_statement@163 (key == IVF_USE_RESIDUAL) [else 分支] → if_statement@165 (key == USE_ATTRIBUTE_FILTER) [else 分支] → if_statement@167 (key == IVF_BASE_PQ_DIM) [else 分支] → if_statement@170 (key == RABITQ_PCA_DIM) [else 分支] → if_statement@172 (key == RABITQ_BITS_PER_DIM_QUERY) [else 分支] → if_statement@176 (key == RABITQ_BITS_PER_DIM_BASE) [else 分支] → if_statement@180 (key == RABITQ_VERSION) | 当前参考未静态绑定；见下方边界说明 |

| L184 | inner_json[BUCKET_PARAMS_KEY][QUANTIZATION_PARAMS_KEY] [RABITQ_QUANTIZATION_ERROR_RATE_KEY] .SetJson | for_range_loop@119 → if_statement@122 (key == IVF_BASE_QUANTIZATION_TYPE) [else 分支] → if_statement@124 (key == IVF_BASE_IO_TYPE) [else 分支] → if_statement@126 (key == IVF_BASE_FILE_PATH) [else 分支] → if_statement@128 (key == IVF_BASE_CACHE_TOTAL_SIZE) [else 分支] → if_statement@131 (key == IVF_PRECISE_QUANTIZATION_TYPE) [else 分支] → if_statement@133 (key == IVF_PRECISE_IO_TYPE) [else 分支] → if_statement@135 (key == IVF_PRECISE_FILE_PATH) [else 分支] → if_statement@137 (key == IVF_PRECISE_CACHE_TOTAL_SIZE) [else 分支] → if_statement@140 (key == IVF_BUCKETS_COUNT) [else 分支] → if_statement@142 (key == IVF_TRAIN_TYPE) [else 分支] → if_statement@144 (key == IVF_PARTITION_STRATEGY_TYPE_KEY) [else 分支] → if_statement@147 (key == IVF_USE_ROUTE_GRAPH) [else 分支] → if_statement@149 (key == GNO_IMI_FIRST_ORDER_BUCKETS_COUNT) [else 分支] → if_statement@153 (key == GNO_IMI_SECOND_ORDER_BUCKETS_COUNT) [else 分支] → if_statement@157 (key == BUCKET_PER_DATA_KEY) [else 分支] → if_statement@159 (key == IVF_USE_REORDER) [else 分支] → if_statement@161 (key == IVF_PRECISE_CODES_LAYOUT) [else 分支] → if_statement@163 (key == IVF_USE_RESIDUAL) [else 分支] → if_statement@165 (key == USE_ATTRIBUTE_FILTER) [else 分支] → if_statement@167 (key == IVF_BASE_PQ_DIM) [else 分支] → if_statement@170 (key == RABITQ_PCA_DIM) [else 分支] → if_statement@172 (key == RABITQ_BITS_PER_DIM_QUERY) [else 分支] → if_statement@176 (key == RABITQ_BITS_PER_DIM_BASE) [else 分支] → if_statement@180 (key == RABITQ_VERSION) [else 分支] → if_statement@183 (key == RABITQ_ERROR_RATE) | 当前参考未静态绑定；见下方边界说明 |

| L188 | inner_json[BUCKET_PARAMS_KEY][QUANTIZATION_PARAMS_KEY][USE_FHT_KEY].SetJson | for_range_loop@119 → if_statement@122 (key == IVF_BASE_QUANTIZATION_TYPE) [else 分支] → if_statement@124 (key == IVF_BASE_IO_TYPE) [else 分支] → if_statement@126 (key == IVF_BASE_FILE_PATH) [else 分支] → if_statement@128 (key == IVF_BASE_CACHE_TOTAL_SIZE) [else 分支] → if_statement@131 (key == IVF_PRECISE_QUANTIZATION_TYPE) [else 分支] → if_statement@133 (key == IVF_PRECISE_IO_TYPE) [else 分支] → if_statement@135 (key == IVF_PRECISE_FILE_PATH) [else 分支] → if_statement@137 (key == IVF_PRECISE_CACHE_TOTAL_SIZE) [else 分支] → if_statement@140 (key == IVF_BUCKETS_COUNT) [else 分支] → if_statement@142 (key == IVF_TRAIN_TYPE) [else 分支] → if_statement@144 (key == IVF_PARTITION_STRATEGY_TYPE_KEY) [else 分支] → if_statement@147 (key == IVF_USE_ROUTE_GRAPH) [else 分支] → if_statement@149 (key == GNO_IMI_FIRST_ORDER_BUCKETS_COUNT) [else 分支] → if_statement@153 (key == GNO_IMI_SECOND_ORDER_BUCKETS_COUNT) [else 分支] → if_statement@157 (key == BUCKET_PER_DATA_KEY) [else 分支] → if_statement@159 (key == IVF_USE_REORDER) [else 分支] → if_statement@161 (key == IVF_PRECISE_CODES_LAYOUT) [else 分支] → if_statement@163 (key == IVF_USE_RESIDUAL) [else 分支] → if_statement@165 (key == USE_ATTRIBUTE_FILTER) [else 分支] → if_statement@167 (key == IVF_BASE_PQ_DIM) [else 分支] → if_statement@170 (key == RABITQ_PCA_DIM) [else 分支] → if_statement@172 (key == RABITQ_BITS_PER_DIM_QUERY) [else 分支] → if_statement@176 (key == RABITQ_BITS_PER_DIM_BASE) [else 分支] → if_statement@180 (key == RABITQ_VERSION) [else 分支] → if_statement@183 (key == RABITQ_ERROR_RATE) [else 分支] → if_statement@187 (key == RABITQ_USE_FHT) | 当前参考未静态绑定；见下方边界说明 |

| L190 | inner_json[BUCKET_PARAMS_KEY][QUANTIZATION_PARAMS_KEY][FAST_ENCODE_RABITQ_KEY].SetJson | for_range_loop@119 → if_statement@122 (key == IVF_BASE_QUANTIZATION_TYPE) [else 分支] → if_statement@124 (key == IVF_BASE_IO_TYPE) [else 分支] → if_statement@126 (key == IVF_BASE_FILE_PATH) [else 分支] → if_statement@128 (key == IVF_BASE_CACHE_TOTAL_SIZE) [else 分支] → if_statement@131 (key == IVF_PRECISE_QUANTIZATION_TYPE) [else 分支] → if_statement@133 (key == IVF_PRECISE_IO_TYPE) [else 分支] → if_statement@135 (key == IVF_PRECISE_FILE_PATH) [else 分支] → if_statement@137 (key == IVF_PRECISE_CACHE_TOTAL_SIZE) [else 分支] → if_statement@140 (key == IVF_BUCKETS_COUNT) [else 分支] → if_statement@142 (key == IVF_TRAIN_TYPE) [else 分支] → if_statement@144 (key == IVF_PARTITION_STRATEGY_TYPE_KEY) [else 分支] → if_statement@147 (key == IVF_USE_ROUTE_GRAPH) [else 分支] → if_statement@149 (key == GNO_IMI_FIRST_ORDER_BUCKETS_COUNT) [else 分支] → if_statement@153 (key == GNO_IMI_SECOND_ORDER_BUCKETS_COUNT) [else 分支] → if_statement@157 (key == BUCKET_PER_DATA_KEY) [else 分支] → if_statement@159 (key == IVF_USE_REORDER) [else 分支] → if_statement@161 (key == IVF_PRECISE_CODES_LAYOUT) [else 分支] → if_statement@163 (key == IVF_USE_RESIDUAL) [else 分支] → if_statement@165 (key == USE_ATTRIBUTE_FILTER) [else 分支] → if_statement@167 (key == IVF_BASE_PQ_DIM) [else 分支] → if_statement@170 (key == RABITQ_PCA_DIM) [else 分支] → if_statement@172 (key == RABITQ_BITS_PER_DIM_QUERY) [else 分支] → if_statement@176 (key == RABITQ_BITS_PER_DIM_BASE) [else 分支] → if_statement@180 (key == RABITQ_VERSION) [else 分支] → if_statement@183 (key == RABITQ_ERROR_RATE) [else 分支] → if_statement@187 (key == RABITQ_USE_FHT) [else 分支] → if_statement@189 (key == FAST_ENCODE_RABITQ) | 当前参考未静态绑定；见下方边界说明 |

| L192 | inner_json[PRECISE_CODES_KEY][QUANTIZATION_PARAMS_KEY][FAST_ENCODE_RABITQ_KEY].SetJson | for_range_loop@119 → if_statement@122 (key == IVF_BASE_QUANTIZATION_TYPE) [else 分支] → if_statement@124 (key == IVF_BASE_IO_TYPE) [else 分支] → if_statement@126 (key == IVF_BASE_FILE_PATH) [else 分支] → if_statement@128 (key == IVF_BASE_CACHE_TOTAL_SIZE) [else 分支] → if_statement@131 (key == IVF_PRECISE_QUANTIZATION_TYPE) [else 分支] → if_statement@133 (key == IVF_PRECISE_IO_TYPE) [else 分支] → if_statement@135 (key == IVF_PRECISE_FILE_PATH) [else 分支] → if_statement@137 (key == IVF_PRECISE_CACHE_TOTAL_SIZE) [else 分支] → if_statement@140 (key == IVF_BUCKETS_COUNT) [else 分支] → if_statement@142 (key == IVF_TRAIN_TYPE) [else 分支] → if_statement@144 (key == IVF_PARTITION_STRATEGY_TYPE_KEY) [else 分支] → if_statement@147 (key == IVF_USE_ROUTE_GRAPH) [else 分支] → if_statement@149 (key == GNO_IMI_FIRST_ORDER_BUCKETS_COUNT) [else 分支] → if_statement@153 (key == GNO_IMI_SECOND_ORDER_BUCKETS_COUNT) [else 分支] → if_statement@157 (key == BUCKET_PER_DATA_KEY) [else 分支] → if_statement@159 (key == IVF_USE_REORDER) [else 分支] → if_statement@161 (key == IVF_PRECISE_CODES_LAYOUT) [else 分支] → if_statement@163 (key == IVF_USE_RESIDUAL) [else 分支] → if_statement@165 (key == USE_ATTRIBUTE_FILTER) [else 分支] → if_statement@167 (key == IVF_BASE_PQ_DIM) [else 分支] → if_statement@170 (key == RABITQ_PCA_DIM) [else 分支] → if_statement@172 (key == RABITQ_BITS_PER_DIM_QUERY) [else 分支] → if_statement@176 (key == RABITQ_BITS_PER_DIM_BASE) [else 分支] → if_statement@180 (key == RABITQ_VERSION) [else 分支] → if_statement@183 (key == RABITQ_ERROR_RATE) [else 分支] → if_statement@187 (key == RABITQ_USE_FHT) [else 分支] → if_statement@189 (key == FAST_ENCODE_RABITQ) | 当前参考未静态绑定；见下方边界说明 |

| L195 | inner_json[BUCKET_PARAMS_KEY][QUANTIZATION_PARAMS_KEY][FAST_ENCODE_RABITQ_ROUNDS_KEY] .SetJson | for_range_loop@119 → if_statement@122 (key == IVF_BASE_QUANTIZATION_TYPE) [else 分支] → if_statement@124 (key == IVF_BASE_IO_TYPE) [else 分支] → if_statement@126 (key == IVF_BASE_FILE_PATH) [else 分支] → if_statement@128 (key == IVF_BASE_CACHE_TOTAL_SIZE) [else 分支] → if_statement@131 (key == IVF_PRECISE_QUANTIZATION_TYPE) [else 分支] → if_statement@133 (key == IVF_PRECISE_IO_TYPE) [else 分支] → if_statement@135 (key == IVF_PRECISE_FILE_PATH) [else 分支] → if_statement@137 (key == IVF_PRECISE_CACHE_TOTAL_SIZE) [else 分支] → if_statement@140 (key == IVF_BUCKETS_COUNT) [else 分支] → if_statement@142 (key == IVF_TRAIN_TYPE) [else 分支] → if_statement@144 (key == IVF_PARTITION_STRATEGY_TYPE_KEY) [else 分支] → if_statement@147 (key == IVF_USE_ROUTE_GRAPH) [else 分支] → if_statement@149 (key == GNO_IMI_FIRST_ORDER_BUCKETS_COUNT) [else 分支] → if_statement@153 (key == GNO_IMI_SECOND_ORDER_BUCKETS_COUNT) [else 分支] → if_statement@157 (key == BUCKET_PER_DATA_KEY) [else 分支] → if_statement@159 (key == IVF_USE_REORDER) [else 分支] → if_statement@161 (key == IVF_PRECISE_CODES_LAYOUT) [else 分支] → if_statement@163 (key == IVF_USE_RESIDUAL) [else 分支] → if_statement@165 (key == USE_ATTRIBUTE_FILTER) [else 分支] → if_statement@167 (key == IVF_BASE_PQ_DIM) [else 分支] → if_statement@170 (key == RABITQ_PCA_DIM) [else 分支] → if_statement@172 (key == RABITQ_BITS_PER_DIM_QUERY) [else 分支] → if_statement@176 (key == RABITQ_BITS_PER_DIM_BASE) [else 分支] → if_statement@180 (key == RABITQ_VERSION) [else 分支] → if_statement@183 (key == RABITQ_ERROR_RATE) [else 分支] → if_statement@187 (key == RABITQ_USE_FHT) [else 分支] → if_statement@189 (key == FAST_ENCODE_RABITQ) [else 分支] → if_statement@194 (key == FAST_ENCODE_RABITQ_ROUNDS) | 当前参考未静态绑定；见下方边界说明 |

| L197 | inner_json[PRECISE_CODES_KEY][QUANTIZATION_PARAMS_KEY][FAST_ENCODE_RABITQ_ROUNDS_KEY] .SetJson | for_range_loop@119 → if_statement@122 (key == IVF_BASE_QUANTIZATION_TYPE) [else 分支] → if_statement@124 (key == IVF_BASE_IO_TYPE) [else 分支] → if_statement@126 (key == IVF_BASE_FILE_PATH) [else 分支] → if_statement@128 (key == IVF_BASE_CACHE_TOTAL_SIZE) [else 分支] → if_statement@131 (key == IVF_PRECISE_QUANTIZATION_TYPE) [else 分支] → if_statement@133 (key == IVF_PRECISE_IO_TYPE) [else 分支] → if_statement@135 (key == IVF_PRECISE_FILE_PATH) [else 分支] → if_statement@137 (key == IVF_PRECISE_CACHE_TOTAL_SIZE) [else 分支] → if_statement@140 (key == IVF_BUCKETS_COUNT) [else 分支] → if_statement@142 (key == IVF_TRAIN_TYPE) [else 分支] → if_statement@144 (key == IVF_PARTITION_STRATEGY_TYPE_KEY) [else 分支] → if_statement@147 (key == IVF_USE_ROUTE_GRAPH) [else 分支] → if_statement@149 (key == GNO_IMI_FIRST_ORDER_BUCKETS_COUNT) [else 分支] → if_statement@153 (key == GNO_IMI_SECOND_ORDER_BUCKETS_COUNT) [else 分支] → if_statement@157 (key == BUCKET_PER_DATA_KEY) [else 分支] → if_statement@159 (key == IVF_USE_REORDER) [else 分支] → if_statement@161 (key == IVF_PRECISE_CODES_LAYOUT) [else 分支] → if_statement@163 (key == IVF_USE_RESIDUAL) [else 分支] → if_statement@165 (key == USE_ATTRIBUTE_FILTER) [else 分支] → if_statement@167 (key == IVF_BASE_PQ_DIM) [else 分支] → if_statement@170 (key == RABITQ_PCA_DIM) [else 分支] → if_statement@172 (key == RABITQ_BITS_PER_DIM_QUERY) [else 分支] → if_statement@176 (key == RABITQ_BITS_PER_DIM_BASE) [else 分支] → if_statement@180 (key == RABITQ_VERSION) [else 分支] → if_statement@183 (key == RABITQ_ERROR_RATE) [else 分支] → if_statement@187 (key == RABITQ_USE_FHT) [else 分支] → if_statement@189 (key == FAST_ENCODE_RABITQ) [else 分支] → if_statement@194 (key == FAST_ENCODE_RABITQ_ROUNDS) | 当前参考未静态绑定；见下方边界说明 |

| L200 | inner_json[BUILD_THREAD_COUNT_KEY].SetJson | for_range_loop@119 → if_statement@122 (key == IVF_BASE_QUANTIZATION_TYPE) [else 分支] → if_statement@124 (key == IVF_BASE_IO_TYPE) [else 分支] → if_statement@126 (key == IVF_BASE_FILE_PATH) [else 分支] → if_statement@128 (key == IVF_BASE_CACHE_TOTAL_SIZE) [else 分支] → if_statement@131 (key == IVF_PRECISE_QUANTIZATION_TYPE) [else 分支] → if_statement@133 (key == IVF_PRECISE_IO_TYPE) [else 分支] → if_statement@135 (key == IVF_PRECISE_FILE_PATH) [else 分支] → if_statement@137 (key == IVF_PRECISE_CACHE_TOTAL_SIZE) [else 分支] → if_statement@140 (key == IVF_BUCKETS_COUNT) [else 分支] → if_statement@142 (key == IVF_TRAIN_TYPE) [else 分支] → if_statement@144 (key == IVF_PARTITION_STRATEGY_TYPE_KEY) [else 分支] → if_statement@147 (key == IVF_USE_ROUTE_GRAPH) [else 分支] → if_statement@149 (key == GNO_IMI_FIRST_ORDER_BUCKETS_COUNT) [else 分支] → if_statement@153 (key == GNO_IMI_SECOND_ORDER_BUCKETS_COUNT) [else 分支] → if_statement@157 (key == BUCKET_PER_DATA_KEY) [else 分支] → if_statement@159 (key == IVF_USE_REORDER) [else 分支] → if_statement@161 (key == IVF_PRECISE_CODES_LAYOUT) [else 分支] → if_statement@163 (key == IVF_USE_RESIDUAL) [else 分支] → if_statement@165 (key == USE_ATTRIBUTE_FILTER) [else 分支] → if_statement@167 (key == IVF_BASE_PQ_DIM) [else 分支] → if_statement@170 (key == RABITQ_PCA_DIM) [else 分支] → if_statement@172 (key == RABITQ_BITS_PER_DIM_QUERY) [else 分支] → if_statement@176 (key == RABITQ_BITS_PER_DIM_BASE) [else 分支] → if_statement@180 (key == RABITQ_VERSION) [else 分支] → if_statement@183 (key == RABITQ_ERROR_RATE) [else 分支] → if_statement@187 (key == RABITQ_USE_FHT) [else 分支] → if_statement@189 (key == FAST_ENCODE_RABITQ) [else 分支] → if_statement@194 (key == FAST_ENCODE_RABITQ_ROUNDS) [else 分支] → if_statement@199 (key == IVF_THREAD_COUNT) | 当前参考未静态绑定；见下方边界说明 |

| L202 | inner_json[TRAIN_SAMPLE_COUNT_KEY].SetJson | for_range_loop@119 → if_statement@122 (key == IVF_BASE_QUANTIZATION_TYPE) [else 分支] → if_statement@124 (key == IVF_BASE_IO_TYPE) [else 分支] → if_statement@126 (key == IVF_BASE_FILE_PATH) [else 分支] → if_statement@128 (key == IVF_BASE_CACHE_TOTAL_SIZE) [else 分支] → if_statement@131 (key == IVF_PRECISE_QUANTIZATION_TYPE) [else 分支] → if_statement@133 (key == IVF_PRECISE_IO_TYPE) [else 分支] → if_statement@135 (key == IVF_PRECISE_FILE_PATH) [else 分支] → if_statement@137 (key == IVF_PRECISE_CACHE_TOTAL_SIZE) [else 分支] → if_statement@140 (key == IVF_BUCKETS_COUNT) [else 分支] → if_statement@142 (key == IVF_TRAIN_TYPE) [else 分支] → if_statement@144 (key == IVF_PARTITION_STRATEGY_TYPE_KEY) [else 分支] → if_statement@147 (key == IVF_USE_ROUTE_GRAPH) [else 分支] → if_statement@149 (key == GNO_IMI_FIRST_ORDER_BUCKETS_COUNT) [else 分支] → if_statement@153 (key == GNO_IMI_SECOND_ORDER_BUCKETS_COUNT) [else 分支] → if_statement@157 (key == BUCKET_PER_DATA_KEY) [else 分支] → if_statement@159 (key == IVF_USE_REORDER) [else 分支] → if_statement@161 (key == IVF_PRECISE_CODES_LAYOUT) [else 分支] → if_statement@163 (key == IVF_USE_RESIDUAL) [else 分支] → if_statement@165 (key == USE_ATTRIBUTE_FILTER) [else 分支] → if_statement@167 (key == IVF_BASE_PQ_DIM) [else 分支] → if_statement@170 (key == RABITQ_PCA_DIM) [else 分支] → if_statement@172 (key == RABITQ_BITS_PER_DIM_QUERY) [else 分支] → if_statement@176 (key == RABITQ_BITS_PER_DIM_BASE) [else 分支] → if_statement@180 (key == RABITQ_VERSION) [else 分支] → if_statement@183 (key == RABITQ_ERROR_RATE) [else 分支] → if_statement@187 (key == RABITQ_USE_FHT) [else 分支] → if_statement@189 (key == FAST_ENCODE_RABITQ) [else 分支] → if_statement@194 (key == FAST_ENCODE_RABITQ_ROUNDS) [else 分支] → if_statement@199 (key == IVF_THREAD_COUNT) [else 分支] → if_statement@201 (key == TRAIN_SAMPLE_COUNT_KEY) | 当前参考未静态绑定；见下方边界说明 |

| L204 | inner_json[GRAPH_BUILD_THRESHOLD_KEY].SetJson | for_range_loop@119 → if_statement@122 (key == IVF_BASE_QUANTIZATION_TYPE) [else 分支] → if_statement@124 (key == IVF_BASE_IO_TYPE) [else 分支] → if_statement@126 (key == IVF_BASE_FILE_PATH) [else 分支] → if_statement@128 (key == IVF_BASE_CACHE_TOTAL_SIZE) [else 分支] → if_statement@131 (key == IVF_PRECISE_QUANTIZATION_TYPE) [else 分支] → if_statement@133 (key == IVF_PRECISE_IO_TYPE) [else 分支] → if_statement@135 (key == IVF_PRECISE_FILE_PATH) [else 分支] → if_statement@137 (key == IVF_PRECISE_CACHE_TOTAL_SIZE) [else 分支] → if_statement@140 (key == IVF_BUCKETS_COUNT) [else 分支] → if_statement@142 (key == IVF_TRAIN_TYPE) [else 分支] → if_statement@144 (key == IVF_PARTITION_STRATEGY_TYPE_KEY) [else 分支] → if_statement@147 (key == IVF_USE_ROUTE_GRAPH) [else 分支] → if_statement@149 (key == GNO_IMI_FIRST_ORDER_BUCKETS_COUNT) [else 分支] → if_statement@153 (key == GNO_IMI_SECOND_ORDER_BUCKETS_COUNT) [else 分支] → if_statement@157 (key == BUCKET_PER_DATA_KEY) [else 分支] → if_statement@159 (key == IVF_USE_REORDER) [else 分支] → if_statement@161 (key == IVF_PRECISE_CODES_LAYOUT) [else 分支] → if_statement@163 (key == IVF_USE_RESIDUAL) [else 分支] → if_statement@165 (key == USE_ATTRIBUTE_FILTER) [else 分支] → if_statement@167 (key == IVF_BASE_PQ_DIM) [else 分支] → if_statement@170 (key == RABITQ_PCA_DIM) [else 分支] → if_statement@172 (key == RABITQ_BITS_PER_DIM_QUERY) [else 分支] → if_statement@176 (key == RABITQ_BITS_PER_DIM_BASE) [else 分支] → if_statement@180 (key == RABITQ_VERSION) [else 分支] → if_statement@183 (key == RABITQ_ERROR_RATE) [else 分支] → if_statement@187 (key == RABITQ_USE_FHT) [else 分支] → if_statement@189 (key == FAST_ENCODE_RABITQ) [else 分支] → if_statement@194 (key == FAST_ENCODE_RABITQ_ROUNDS) [else 分支] → if_statement@199 (key == IVF_THREAD_COUNT) [else 分支] → if_statement@201 (key == TRAIN_SAMPLE_COUNT_KEY) [else 分支] → if_statement@203 (key == GRAPH_BUILD_THRESHOLD_KEY) | 当前参考未静态绑定；见下方边界说明 |

| L206 | inner_json[BUCKET_PARAMS_KEY][IO_PARAMS_KEY][READ_CACHE_ENABLED_KEY].SetJson | for_range_loop@119 → if_statement@122 (key == IVF_BASE_QUANTIZATION_TYPE) [else 分支] → if_statement@124 (key == IVF_BASE_IO_TYPE) [else 分支] → if_statement@126 (key == IVF_BASE_FILE_PATH) [else 分支] → if_statement@128 (key == IVF_BASE_CACHE_TOTAL_SIZE) [else 分支] → if_statement@131 (key == IVF_PRECISE_QUANTIZATION_TYPE) [else 分支] → if_statement@133 (key == IVF_PRECISE_IO_TYPE) [else 分支] → if_statement@135 (key == IVF_PRECISE_FILE_PATH) [else 分支] → if_statement@137 (key == IVF_PRECISE_CACHE_TOTAL_SIZE) [else 分支] → if_statement@140 (key == IVF_BUCKETS_COUNT) [else 分支] → if_statement@142 (key == IVF_TRAIN_TYPE) [else 分支] → if_statement@144 (key == IVF_PARTITION_STRATEGY_TYPE_KEY) [else 分支] → if_statement@147 (key == IVF_USE_ROUTE_GRAPH) [else 分支] → if_statement@149 (key == GNO_IMI_FIRST_ORDER_BUCKETS_COUNT) [else 分支] → if_statement@153 (key == GNO_IMI_SECOND_ORDER_BUCKETS_COUNT) [else 分支] → if_statement@157 (key == BUCKET_PER_DATA_KEY) [else 分支] → if_statement@159 (key == IVF_USE_REORDER) [else 分支] → if_statement@161 (key == IVF_PRECISE_CODES_LAYOUT) [else 分支] → if_statement@163 (key == IVF_USE_RESIDUAL) [else 分支] → if_statement@165 (key == USE_ATTRIBUTE_FILTER) [else 分支] → if_statement@167 (key == IVF_BASE_PQ_DIM) [else 分支] → if_statement@170 (key == RABITQ_PCA_DIM) [else 分支] → if_statement@172 (key == RABITQ_BITS_PER_DIM_QUERY) [else 分支] → if_statement@176 (key == RABITQ_BITS_PER_DIM_BASE) [else 分支] → if_statement@180 (key == RABITQ_VERSION) [else 分支] → if_statement@183 (key == RABITQ_ERROR_RATE) [else 分支] → if_statement@187 (key == RABITQ_USE_FHT) [else 分支] → if_statement@189 (key == FAST_ENCODE_RABITQ) [else 分支] → if_statement@194 (key == FAST_ENCODE_RABITQ_ROUNDS) [else 分支] → if_statement@199 (key == IVF_THREAD_COUNT) [else 分支] → if_statement@201 (key == TRAIN_SAMPLE_COUNT_KEY) [else 分支] → if_statement@203 (key == GRAPH_BUILD_THRESHOLD_KEY) [else 分支] → if_statement@205 (key == IVF_BASE_ENABLE_READ_CACHE) | 当前参考未静态绑定；见下方边界说明 |

| L208 | inner_json[PRECISE_CODES_KEY][IO_PARAMS_KEY][READ_CACHE_ENABLED_KEY].SetJson | for_range_loop@119 → if_statement@122 (key == IVF_BASE_QUANTIZATION_TYPE) [else 分支] → if_statement@124 (key == IVF_BASE_IO_TYPE) [else 分支] → if_statement@126 (key == IVF_BASE_FILE_PATH) [else 分支] → if_statement@128 (key == IVF_BASE_CACHE_TOTAL_SIZE) [else 分支] → if_statement@131 (key == IVF_PRECISE_QUANTIZATION_TYPE) [else 分支] → if_statement@133 (key == IVF_PRECISE_IO_TYPE) [else 分支] → if_statement@135 (key == IVF_PRECISE_FILE_PATH) [else 分支] → if_statement@137 (key == IVF_PRECISE_CACHE_TOTAL_SIZE) [else 分支] → if_statement@140 (key == IVF_BUCKETS_COUNT) [else 分支] → if_statement@142 (key == IVF_TRAIN_TYPE) [else 分支] → if_statement@144 (key == IVF_PARTITION_STRATEGY_TYPE_KEY) [else 分支] → if_statement@147 (key == IVF_USE_ROUTE_GRAPH) [else 分支] → if_statement@149 (key == GNO_IMI_FIRST_ORDER_BUCKETS_COUNT) [else 分支] → if_statement@153 (key == GNO_IMI_SECOND_ORDER_BUCKETS_COUNT) [else 分支] → if_statement@157 (key == BUCKET_PER_DATA_KEY) [else 分支] → if_statement@159 (key == IVF_USE_REORDER) [else 分支] → if_statement@161 (key == IVF_PRECISE_CODES_LAYOUT) [else 分支] → if_statement@163 (key == IVF_USE_RESIDUAL) [else 分支] → if_statement@165 (key == USE_ATTRIBUTE_FILTER) [else 分支] → if_statement@167 (key == IVF_BASE_PQ_DIM) [else 分支] → if_statement@170 (key == RABITQ_PCA_DIM) [else 分支] → if_statement@172 (key == RABITQ_BITS_PER_DIM_QUERY) [else 分支] → if_statement@176 (key == RABITQ_BITS_PER_DIM_BASE) [else 分支] → if_statement@180 (key == RABITQ_VERSION) [else 分支] → if_statement@183 (key == RABITQ_ERROR_RATE) [else 分支] → if_statement@187 (key == RABITQ_USE_FHT) [else 分支] → if_statement@189 (key == FAST_ENCODE_RABITQ) [else 分支] → if_statement@194 (key == FAST_ENCODE_RABITQ_ROUNDS) [else 分支] → if_statement@199 (key == IVF_THREAD_COUNT) [else 分支] → if_statement@201 (key == TRAIN_SAMPLE_COUNT_KEY) [else 分支] → if_statement@203 (key == GRAPH_BUILD_THRESHOLD_KEY) [else 分支] → if_statement@205 (key == IVF_BASE_ENABLE_READ_CACHE) [else 分支] → if_statement@207 (key == IVF_PRECISE_ENABLE_READ_CACHE) | 当前参考未静态绑定；见下方边界说明 |

| L210 | VsagException | for_range_loop@119 → if_statement@122 (key == IVF_BASE_QUANTIZATION_TYPE) [else 分支] → if_statement@124 (key == IVF_BASE_IO_TYPE) [else 分支] → if_statement@126 (key == IVF_BASE_FILE_PATH) [else 分支] → if_statement@128 (key == IVF_BASE_CACHE_TOTAL_SIZE) [else 分支] → if_statement@131 (key == IVF_PRECISE_QUANTIZATION_TYPE) [else 分支] → if_statement@133 (key == IVF_PRECISE_IO_TYPE) [else 分支] → if_statement@135 (key == IVF_PRECISE_FILE_PATH) [else 分支] → if_statement@137 (key == IVF_PRECISE_CACHE_TOTAL_SIZE) [else 分支] → if_statement@140 (key == IVF_BUCKETS_COUNT) [else 分支] → if_statement@142 (key == IVF_TRAIN_TYPE) [else 分支] → if_statement@144 (key == IVF_PARTITION_STRATEGY_TYPE_KEY) [else 分支] → if_statement@147 (key == IVF_USE_ROUTE_GRAPH) [else 分支] → if_statement@149 (key == GNO_IMI_FIRST_ORDER_BUCKETS_COUNT) [else 分支] → if_statement@153 (key == GNO_IMI_SECOND_ORDER_BUCKETS_COUNT) [else 分支] → if_statement@157 (key == BUCKET_PER_DATA_KEY) [else 分支] → if_statement@159 (key == IVF_USE_REORDER) [else 分支] → if_statement@161 (key == IVF_PRECISE_CODES_LAYOUT) [else 分支] → if_statement@163 (key == IVF_USE_RESIDUAL) [else 分支] → if_statement@165 (key == USE_ATTRIBUTE_FILTER) [else 分支] → if_statement@167 (key == IVF_BASE_PQ_DIM) [else 分支] → if_statement@170 (key == RABITQ_PCA_DIM) [else 分支] → if_statement@172 (key == RABITQ_BITS_PER_DIM_QUERY) [else 分支] → if_statement@176 (key == RABITQ_BITS_PER_DIM_BASE) [else 分支] → if_statement@180 (key == RABITQ_VERSION) [else 分支] → if_statement@183 (key == RABITQ_ERROR_RATE) [else 分支] → if_statement@187 (key == RABITQ_USE_FHT) [else 分支] → if_statement@189 (key == FAST_ENCODE_RABITQ) [else 分支] → if_statement@194 (key == FAST_ENCODE_RABITQ_ROUNDS) [else 分支] → if_statement@199 (key == IVF_THREAD_COUNT) [else 分支] → if_statement@201 (key == TRAIN_SAMPLE_COUNT_KEY) [else 分支] → if_statement@203 (key == GRAPH_BUILD_THRESHOLD_KEY) [else 分支] → if_statement@205 (key == IVF_BASE_ENABLE_READ_CACHE) [else 分支] → if_statement@207 (key == IVF_PRECISE_ENABLE_READ_CACHE) [else 分支] | 当前参考未静态绑定；见下方边界说明 |

| L211 | fmt::format | for_range_loop@119 → if_statement@122 (key == IVF_BASE_QUANTIZATION_TYPE) [else 分支] → if_statement@124 (key == IVF_BASE_IO_TYPE) [else 分支] → if_statement@126 (key == IVF_BASE_FILE_PATH) [else 分支] → if_statement@128 (key == IVF_BASE_CACHE_TOTAL_SIZE) [else 分支] → if_statement@131 (key == IVF_PRECISE_QUANTIZATION_TYPE) [else 分支] → if_statement@133 (key == IVF_PRECISE_IO_TYPE) [else 分支] → if_statement@135 (key == IVF_PRECISE_FILE_PATH) [else 分支] → if_statement@137 (key == IVF_PRECISE_CACHE_TOTAL_SIZE) [else 分支] → if_statement@140 (key == IVF_BUCKETS_COUNT) [else 分支] → if_statement@142 (key == IVF_TRAIN_TYPE) [else 分支] → if_statement@144 (key == IVF_PARTITION_STRATEGY_TYPE_KEY) [else 分支] → if_statement@147 (key == IVF_USE_ROUTE_GRAPH) [else 分支] → if_statement@149 (key == GNO_IMI_FIRST_ORDER_BUCKETS_COUNT) [else 分支] → if_statement@153 (key == GNO_IMI_SECOND_ORDER_BUCKETS_COUNT) [else 分支] → if_statement@157 (key == BUCKET_PER_DATA_KEY) [else 分支] → if_statement@159 (key == IVF_USE_REORDER) [else 分支] → if_statement@161 (key == IVF_PRECISE_CODES_LAYOUT) [else 分支] → if_statement@163 (key == IVF_USE_RESIDUAL) [else 分支] → if_statement@165 (key == USE_ATTRIBUTE_FILTER) [else 分支] → if_statement@167 (key == IVF_BASE_PQ_DIM) [else 分支] → if_statement@170 (key == RABITQ_PCA_DIM) [else 分支] → if_statement@172 (key == RABITQ_BITS_PER_DIM_QUERY) [else 分支] → if_statement@176 (key == RABITQ_BITS_PER_DIM_BASE) [else 分支] → if_statement@180 (key == RABITQ_VERSION) [else 分支] → if_statement@183 (key == RABITQ_ERROR_RATE) [else 分支] → if_statement@187 (key == RABITQ_USE_FHT) [else 分支] → if_statement@189 (key == FAST_ENCODE_RABITQ) [else 分支] → if_statement@194 (key == FAST_ENCODE_RABITQ_ROUNDS) [else 分支] → if_statement@199 (key == IVF_THREAD_COUNT) [else 分支] → if_statement@201 (key == TRAIN_SAMPLE_COUNT_KEY) [else 分支] → if_statement@203 (key == GRAPH_BUILD_THRESHOLD_KEY) [else 分支] → if_statement@205 (key == IVF_BASE_ENABLE_READ_CACHE) [else 分支] → if_statement@207 (key == IVF_PRECISE_ENABLE_READ_CACHE) [else 分支] | 当前参考未静态绑定；见下方边界说明 |

| L215 | std::make_shared&lt;IVFParameter&gt; | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L216 | ivf_parameter-&gt;FromJson | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L221"></a>

## `IVF::IVF`

源码位置：`src/algorithm/ivf/ivf.cpp:221–283`。

先从签名确认输入、返回值和 const/override，再按完整函数体的条件阅读调用点。下表保留了本函数的显式调用以及 lambda 中的调用；进入下层时用“候选实现”定位，未解析的对象由源码静态类型/运行时类型确认。

### 完整函数

```cpp
IVF::IVF(const IVFParameterPtr& param, const IndexCommonParam& common_param)
    : InnerIndexInterface(param, common_param),
      buckets_per_data_(param->buckets_per_data),
      location_map_(common_param.allocator_.get()),
      bucket_graphs_(common_param.allocator_.get()),
      common_param_(common_param),
      bucket_searcher_(std::make_shared<FlatBucketSearcher>()) {
    this->bucket_ = BucketInterface::MakeInstance(param->bucket_param, common_param);
    if (this->bucket_ == nullptr) {
        throw VsagException(ErrorType::INTERNAL_ERROR, "bucket init error");
    }

    // Initialize thread pool before partition strategy construction
    this->thread_pool_ = common_param.thread_pool_;
    if (param->build_thread_count > 1 and this->thread_pool_ == nullptr) {
        this->thread_pool_ = SafeThreadPool::FactoryDefaultThreadPool();
        this->thread_pool_->SetPoolSize(param->build_thread_count);
    }

    // Create modified common_param with the initialized thread_pool_
    IndexCommonParam modified_common_param = common_param;
    modified_common_param.thread_pool_ = this->thread_pool_;

    if (param->ivf_partition_strategy_parameter->partition_strategy_type ==
        IVFPartitionStrategyType::IVF) {
        this->partition_strategy_ = std::make_shared<IVFNearestPartition>(
            bucket_->bucket_count_, modified_common_param, param->ivf_partition_strategy_parameter);
    } else if (param->ivf_partition_strategy_parameter->partition_strategy_type ==
               IVFPartitionStrategyType::GNO_IMI) {
        this->partition_strategy_ = std::make_shared<GNOIMIPartition>(
            modified_common_param, param->ivf_partition_strategy_parameter);
    }
    if (this->use_reorder_) {
        if (param->precise_codes_layout == PRECISE_CODES_LAYOUT_VALUE_BUCKET) {
            this->precise_bucket_ = BucketInterface::MakeInstance(make_precise_bucket_param(param),
                                                                  modified_common_param);
            CHECK_ARGUMENT(this->precise_bucket_ != nullptr,
                           "unsupported IO or quantizer for IVF precise bucket");
            this->reorder_ = std::make_shared<BucketReorder>(
                this->precise_bucket_,
                [this](InnerIdType inner_id) { return this->get_location(inner_id); },
                allocator_);
        } else {
            this->reorder_codes_ =
                FlattenInterface::MakeInstance(param->precise_codes_param, modified_common_param);
            reorder_ = std::make_shared<FlattenReorder>(this->reorder_codes_, allocator_);
        }
    }
    if (param->bucket_param->use_residual_) {
        this->bucket_->SetStrategy(partition_strategy_);
    }

    this->graph_param_ = param->graph_param;
    this->graph_build_threshold_ = param->graph_build_threshold;
    if (this->graph_build_threshold_ > 0) {
        this->bucket_searcher_ = std::make_shared<GraphBucketSearcher>(
            this->graph_build_threshold_, this->bucket_graphs_, this->allocator_);
    }

    if (bucket_->GetQuantizerName() == QUANTIZATION_TYPE_VALUE_FP32) {
        this->has_raw_vector_ = true;
    }
}
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L228 | BucketInterface::MakeInstance | 函数本体；短路求值/提前返回见源码 | [BucketInterface::MakeInstance · L24](bucket_interface.md#L24) |

| L230 | VsagException | if_statement@229 (this-&gt;bucket_ == nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L236 | SafeThreadPool::FactoryDefaultThreadPool | if_statement@235 (param-&gt;build_thread_count &gt; 1 and this-&gt;thread_pool_ == nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L237 | this-&gt;thread_pool_-&gt;SetPoolSize | if_statement@235 (param-&gt;build_thread_count &gt; 1 and this-&gt;thread_pool_ == nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L246 | std::make_shared&lt;IVFNearestPartition&gt; | if_statement@244 (param-&gt;ivf_partition_strategy_parameter-&gt;partition_strategy_type == IVFPartitionStrategyType::IVF) | 当前参考未静态绑定；见下方边界说明 |

| L250 | std::make_shared&lt;GNOIMIPartition&gt; | if_statement@244 (param-&gt;ivf_partition_strategy_parameter-&gt;partition_strategy_type == IVFPartitionStrategyType::IVF) [else 分支] → if_statement@248 (param-&gt;ivf_partition_strategy_parameter-&gt;partition_strategy_type == IVFPartitionStrategyType::GNO_IMI) | 当前参考未静态绑定；见下方边界说明 |

| L255 | BucketInterface::MakeInstance | if_statement@253 (this-&gt;use_reorder_) → if_statement@254 (param-&gt;precise_codes_layout == PRECISE_CODES_LAYOUT_VALUE_BUCKET) | [BucketInterface::MakeInstance · L24](bucket_interface.md#L24) |

| L255 | make_precise_bucket_param | if_statement@253 (this-&gt;use_reorder_) → if_statement@254 (param-&gt;precise_codes_layout == PRECISE_CODES_LAYOUT_VALUE_BUCKET) | [make_precise_bucket_param · L49](ivf.md#L49) |

| L257 | CHECK_ARGUMENT | if_statement@253 (this-&gt;use_reorder_) → if_statement@254 (param-&gt;precise_codes_layout == PRECISE_CODES_LAYOUT_VALUE_BUCKET) | 当前参考未静态绑定；见下方边界说明 |

| L259 | std::make_shared&lt;BucketReorder&gt; | if_statement@253 (this-&gt;use_reorder_) → if_statement@254 (param-&gt;precise_codes_layout == PRECISE_CODES_LAYOUT_VALUE_BUCKET) | 当前参考未静态绑定；见下方边界说明 |

| L261 | this-&gt;get_location | if_statement@253 (this-&gt;use_reorder_) → if_statement@254 (param-&gt;precise_codes_layout == PRECISE_CODES_LAYOUT_VALUE_BUCKET) → lambda@261（定义体，执行时间取决于调用/调度） | [IVF::get_location · L312](ivf.md#L312) |

| L265 | FlattenInterface::MakeInstance | if_statement@253 (this-&gt;use_reorder_) → if_statement@254 (param-&gt;precise_codes_layout == PRECISE_CODES_LAYOUT_VALUE_BUCKET) [else 分支] | 当前参考未静态绑定；见下方边界说明 |

| L266 | std::make_shared&lt;FlattenReorder&gt; | if_statement@253 (this-&gt;use_reorder_) → if_statement@254 (param-&gt;precise_codes_layout == PRECISE_CODES_LAYOUT_VALUE_BUCKET) [else 分支] | 当前参考未静态绑定；见下方边界说明 |

| L270 | this-&gt;bucket_-&gt;SetStrategy | if_statement@269 (param-&gt;bucket_param-&gt;use_residual_) | 当前参考未静态绑定；见下方边界说明 |

| L276 | std::make_shared&lt;GraphBucketSearcher&gt; | if_statement@275 (this-&gt;graph_build_threshold_ &gt; 0) | 当前参考未静态绑定；见下方边界说明 |

| L280 | bucket_-&gt;GetQuantizerName | if_statement@280 (bucket_-&gt;GetQuantizerName() == QUANTIZATION_TYPE_VALUE_FP32) | [BucketDataCell::GetQuantizerName · L170](bucket_datacell_h.md#L170) |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L285"></a>

## `IVF::GetCodeByInnerId`

源码位置：`src/algorithm/ivf/ivf.cpp:285–289`。

先从签名确认输入、返回值和 const/override，再按完整函数体的条件阅读调用点。下表保留了本函数的显式调用以及 lambda 中的调用；进入下层时用“候选实现”定位，未解析的对象由源码静态类型/运行时类型确认。

### 完整函数

```cpp
void
IVF::GetCodeByInnerId(InnerIdType inner_id, uint8_t* data) const {
    auto [bucket_id, offset_id] = this->get_location(inner_id);
    this->bucket_->GetCodesById(bucket_id, offset_id, data);
}
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L287 | this-&gt;get_location | 函数本体；短路求值/提前返回见源码 | [IVF::get_location · L312](ivf.md#L312) |

| L288 | this-&gt;bucket_-&gt;GetCodesById | 函数本体；短路求值/提前返回见源码 | [BucketDataCell&lt;QuantTmpl, IOTmpl&gt;::GetCodesById · L1017](bucket_datacell_h.md#L1017) |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L291"></a>

## `IVF::GetNumElements`

源码位置：`src/algorithm/ivf/ivf.cpp:291–294`。

先从签名确认输入、返回值和 const/override，再按完整函数体的条件阅读调用点。下表保留了本函数的显式调用以及 lambda 中的调用；进入下层时用“候选实现”定位，未解析的对象由源码静态类型/运行时类型确认。

### 完整函数

```cpp
int64_t
IVF::GetNumElements() const {
    return this->total_elements_ - this->delete_count_;
}
```

### 函数内部调用点：不省略标准库和辅助调用

此函数体没有显式函数调用表达式。赋值、成员初始化和隐式操作请看上面的完整源码。


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L296"></a>

## `IVF::Merge`

源码位置：`src/algorithm/ivf/ivf.cpp:296–310`。

先从签名确认输入、返回值和 const/override，再按完整函数体的条件阅读调用点。下表保留了本函数的显式调用以及 lambda 中的调用；进入下层时用“候选实现”定位，未解析的对象由源码静态类型/运行时类型确认。

### 完整函数

```cpp
void
IVF::Merge(const std::vector<MergeUnit>& merge_units) {
    this->bucket_->Unpack();
    if (precise_bucket_ != nullptr) {
        this->precise_bucket_->Unpack();
    }
    for (const auto& unit : merge_units) {
        this->merge_one_unit(unit);
    }
    this->fill_location_map();
    this->bucket_->Package();
    if (precise_bucket_ != nullptr) {
        this->precise_bucket_->Package();
    }
}
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L298 | this-&gt;bucket_-&gt;Unpack | 函数本体；短路求值/提前返回见源码 | [BucketDataCell::Unpack · L139](bucket_datacell_h.md#L139) |

| L300 | this-&gt;precise_bucket_-&gt;Unpack | if_statement@299 (precise_bucket_ != nullptr) | [BucketDataCell::Unpack · L139](bucket_datacell_h.md#L139) |

| L303 | this-&gt;merge_one_unit | for_range_loop@302 | [IVF::merge_one_unit · L337](ivf.md#L337) |

| L305 | this-&gt;fill_location_map | 函数本体；短路求值/提前返回见源码 | [IVF::fill_location_map · L405](ivf_build.md#L405) |

| L306 | this-&gt;bucket_-&gt;Package | 函数本体；短路求值/提前返回见源码 | [BucketDataCell::Package · L132](bucket_datacell_h.md#L132) |

| L308 | this-&gt;precise_bucket_-&gt;Package | if_statement@307 (precise_bucket_ != nullptr) | [BucketDataCell::Package · L132](bucket_datacell_h.md#L132) |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L312"></a>

## `IVF::get_location`

源码位置：`src/algorithm/ivf/ivf.cpp:312–319`。

从 location_map_ 解包 bucket ID 与 offset。这个定位用于按 ID 读编码和桶精排；输入必须是 origin ID。

### 完整函数

```cpp
std::pair<BucketIdType, InnerIdType>
IVF::get_location(InnerIdType inner_id) const {
    auto loc = this->location_map_[inner_id];
    constexpr uint64_t mask = (1ULL << LOCATION_SPLIT_BIT) - 1ULL;
    auto bucket_id = static_cast<BucketIdType>(loc >> LOCATION_SPLIT_BIT);
    auto offset_id = static_cast<InnerIdType>(loc & mask);
    return {bucket_id, offset_id};
}
```

### 函数内部调用点：不省略标准库和辅助调用

此函数体没有显式函数调用表达式。赋值、成员初始化和隐式操作请看上面的完整源码。


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L321"></a>

## `IVF::ExportModel`

源码位置：`src/algorithm/ivf/ivf.cpp:321–335`。

先从签名确认输入、返回值和 const/override，再按完整函数体的条件阅读调用点。下表保留了本函数的显式调用以及 lambda 中的调用；进入下层时用“候选实现”定位，未解析的对象由源码静态类型/运行时类型确认。

### 完整函数

```cpp
InnerIndexPtr
IVF::ExportModel(const IndexCommonParam& param) const {
    auto index = std::make_shared<IVF>(this->create_param_ptr_, param);
    IVFPartitionStrategy::Clone(this->partition_strategy_, index->partition_strategy_);
    this->bucket_->ExportModel(index->bucket_);
    if (use_reorder_) {
        if (precise_bucket_ != nullptr) {
            this->precise_bucket_->ExportModel(index->precise_bucket_);
        } else {
            this->reorder_codes_->ExportModel(index->reorder_codes_);
        }
    }
    index->is_trained_ = this->is_trained_;
    return index;
}
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L323 | std::make_shared&lt;IVF&gt; | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L324 | IVFPartitionStrategy::Clone | 函数本体；短路求值/提前返回见源码 | [IVFPartitionStrategy::Clone · L37](ivf_partition_strategy_h.md#L37) |

| L325 | this-&gt;bucket_-&gt;ExportModel | 函数本体；短路求值/提前返回见源码 | [BucketDataCell&lt;QuantTmpl, IOTmpl&gt;::ExportModel · L979](bucket_datacell_h.md#L979) |

| L328 | this-&gt;precise_bucket_-&gt;ExportModel | if_statement@326 (use_reorder_) → if_statement@327 (precise_bucket_ != nullptr) | [BucketDataCell&lt;QuantTmpl, IOTmpl&gt;::ExportModel · L979](bucket_datacell_h.md#L979) |

| L330 | this-&gt;reorder_codes_-&gt;ExportModel | if_statement@326 (use_reorder_) → if_statement@327 (precise_bucket_ != nullptr) [else 分支] | [IVF::ExportModel · L321](ivf.md#L321) |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L337"></a>

## `IVF::merge_one_unit`

源码位置：`src/algorithm/ivf/ivf.cpp:337–358`。

先从签名确认输入、返回值和 const/override，再按完整函数体的条件阅读调用点。下表保留了本函数的显式调用以及 lambda 中的调用；进入下层时用“候选实现”定位，未解析的对象由源码静态类型/运行时类型确认。

### 完整函数

```cpp
void
IVF::merge_one_unit(const MergeUnit& unit) {
    check_merge_illegal(unit);
    const auto other_index = std::dynamic_pointer_cast<IVF>(
        std::dynamic_pointer_cast<IndexImpl<IVF>>(unit.index)->GetInnerIndex());
    auto bucket_bias = static_cast<InnerIdType>(this->total_elements_ * this->buckets_per_data_);
    this->label_table_->MergeOther(other_index->label_table_, unit.id_map_func);
    other_index->bucket_->Unpack();
    this->bucket_->MergeOther(other_index->bucket_, bucket_bias);
    other_index->bucket_->Package();

    if (this->use_reorder_) {
        if (precise_bucket_ != nullptr) {
            other_index->precise_bucket_->Unpack();
            this->precise_bucket_->MergeOther(other_index->precise_bucket_, bucket_bias);
            other_index->precise_bucket_->Package();
        } else {
            this->reorder_codes_->MergeOther(other_index->reorder_codes_, this->total_elements_);
        }
    }
    this->total_elements_ += other_index->total_elements_;
}
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L339 | check_merge_illegal | 函数本体；短路求值/提前返回见源码 | [IVF::check_merge_illegal · L360](ivf.md#L360) |

| L340 | std::dynamic_pointer_cast&lt;IVF&gt; | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L341 | std::dynamic_pointer_cast&lt;IndexImpl&lt;IVF&gt;&gt;(unit.index)-&gt;GetInnerIndex | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L341 | std::dynamic_pointer_cast&lt;IndexImpl&lt;IVF&gt;&gt; | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L343 | this-&gt;label_table_-&gt;MergeOther | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L344 | other_index-&gt;bucket_-&gt;Unpack | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L345 | this-&gt;bucket_-&gt;MergeOther | 函数本体；短路求值/提前返回见源码 | [BucketDataCell&lt;QuantTmpl, IOTmpl&gt;::MergeOther · L994](bucket_datacell_h.md#L994) |

| L346 | other_index-&gt;bucket_-&gt;Package | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L350 | other_index-&gt;precise_bucket_-&gt;Unpack | if_statement@348 (this-&gt;use_reorder_) → if_statement@349 (precise_bucket_ != nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L351 | this-&gt;precise_bucket_-&gt;MergeOther | if_statement@348 (this-&gt;use_reorder_) → if_statement@349 (precise_bucket_ != nullptr) | [BucketDataCell&lt;QuantTmpl, IOTmpl&gt;::MergeOther · L994](bucket_datacell_h.md#L994) |

| L352 | other_index-&gt;precise_bucket_-&gt;Package | if_statement@348 (this-&gt;use_reorder_) → if_statement@349 (precise_bucket_ != nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L354 | this-&gt;reorder_codes_-&gt;MergeOther | if_statement@348 (this-&gt;use_reorder_) → if_statement@349 (precise_bucket_ != nullptr) [else 分支] | [BucketDataCell&lt;QuantTmpl, IOTmpl&gt;::MergeOther · L994](bucket_datacell_h.md#L994) |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L360"></a>

## `IVF::check_merge_illegal`

源码位置：`src/algorithm/ivf/ivf.cpp:360–399`。

先从签名确认输入、返回值和 const/override，再按完整函数体的条件阅读调用点。下表保留了本函数的显式调用以及 lambda 中的调用；进入下层时用“候选实现”定位，未解析的对象由源码静态类型/运行时类型确认。

### 完整函数

```cpp
void
IVF::check_merge_illegal(const vsag::MergeUnit& unit) const {
    auto index = std::dynamic_pointer_cast<IndexImpl<IVF>>(unit.index);
    if (index == nullptr) {
        throw VsagException(
            ErrorType::INVALID_ARGUMENT,
            "Merge Failed: index type not match, try to merge a non-ivf index to an IVF index");
    }
    auto other_ivf_index = std::dynamic_pointer_cast<IVF>(
        std::dynamic_pointer_cast<IndexImpl<IVF>>(unit.index)->GetInnerIndex());
    if (other_ivf_index->use_reorder_ != this->use_reorder_) {
        throw VsagException(ErrorType::INVALID_ARGUMENT,
                            fmt::format("Merge Failed: ivf use_reorder not match, current "
                                        "index is {}, other index is {}",
                                        this->use_reorder_,
                                        other_ivf_index->use_reorder_));
    }
    if ((other_ivf_index->precise_bucket_ == nullptr) != (this->precise_bucket_ == nullptr)) {
        throw VsagException(ErrorType::INVALID_ARGUMENT,
                            "Merge Failed: IVF precise codes layout does not match");
    }
    auto cur_model = this->ExportModel(index->GetCommonParam());
    std::stringstream ss1;
    std::stringstream ss2;
    IOStreamWriter writer1(ss1);
    cur_model->Serialize(writer1);

    cur_model.reset();
    auto other_model = other_ivf_index->ExportModel(index->GetCommonParam());
    IOStreamWriter writer2(ss2);
    other_model->Serialize(writer2);

    other_model.reset();

    if (not check_equal_on_string_stream(ss1, ss2)) {
        throw VsagException(
            ErrorType::INVALID_ARGUMENT,
            "Merge Failed: IVF model not match, try to merge a different model ivf index");
    }
}
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L362 | std::dynamic_pointer_cast&lt;IndexImpl&lt;IVF&gt;&gt; | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L364 | VsagException | if_statement@363 (index == nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L368 | std::dynamic_pointer_cast&lt;IVF&gt; | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L369 | std::dynamic_pointer_cast&lt;IndexImpl&lt;IVF&gt;&gt;(unit.index)-&gt;GetInnerIndex | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L369 | std::dynamic_pointer_cast&lt;IndexImpl&lt;IVF&gt;&gt; | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L371 | VsagException | if_statement@370 (other_ivf_index-&gt;use_reorder_ != this-&gt;use_reorder_) | 当前参考未静态绑定；见下方边界说明 |

| L372 | fmt::format | if_statement@370 (other_ivf_index-&gt;use_reorder_ != this-&gt;use_reorder_) | 当前参考未静态绑定；见下方边界说明 |

| L378 | VsagException | if_statement@377 ((other_ivf_index-&gt;precise_bucket_ == nullptr) != (this-&gt;precise_bucket_ == nullptr)) | 当前参考未静态绑定；见下方边界说明 |

| L381 | this-&gt;ExportModel | 函数本体；短路求值/提前返回见源码 | [IVF::ExportModel · L321](ivf.md#L321) |

| L381 | index-&gt;GetCommonParam | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L385 | cur_model-&gt;Serialize | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L387 | cur_model.reset | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L388 | other_ivf_index-&gt;ExportModel | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L388 | index-&gt;GetCommonParam | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L390 | other_model-&gt;Serialize | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L392 | other_model.reset | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L394 | check_equal_on_string_stream | if_statement@394 (not check_equal_on_string_stream(ss1, ss2)) | 当前参考未静态绑定；见下方边界说明 |

| L395 | VsagException | if_statement@394 (not check_equal_on_string_stream(ss1, ss2)) | 当前参考未静态绑定；见下方边界说明 |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L401"></a>

## `IVF::GetAttributeSetByInnerId`

源码位置：`src/algorithm/ivf/ivf.cpp:401–405`。

先从签名确认输入、返回值和 const/override，再按完整函数体的条件阅读调用点。下表保留了本函数的显式调用以及 lambda 中的调用；进入下层时用“候选实现”定位，未解析的对象由源码静态类型/运行时类型确认。

### 完整函数

```cpp
void
IVF::GetAttributeSetByInnerId(InnerIdType inner_id, AttributeSet* attr) const {
    auto [bucket_id, bucket_offset] = this->get_location(inner_id);
    this->attr_filter_index_->GetAttribute(bucket_id, bucket_offset, attr);
}
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L403 | this-&gt;get_location | 函数本体；短路求值/提前返回见源码 | [IVF::get_location · L312](ivf.md#L312) |

| L404 | this-&gt;attr_filter_index_-&gt;GetAttribute | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L407"></a>

## `IVF::CalcDistancesById`

源码位置：`src/algorithm/ivf/ivf.cpp:407–413`。

先从签名确认输入、返回值和 const/override，再按完整函数体的条件阅读调用点。下表保留了本函数的显式调用以及 lambda 中的调用；进入下层时用“候选实现”定位，未解析的对象由源码静态类型/运行时类型确认。

### 完整函数

```cpp
DatasetPtr
IVF::CalcDistancesById(const float* query,
                       const int64_t* ids,
                       int64_t count,
                       bool calculate_precise_distance) const {
    return this->CalDistanceById(query, ids, count, calculate_precise_distance);
}
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L412 | this-&gt;CalDistanceById | 函数本体；短路求值/提前返回见源码 | [IVF::CalDistanceById · L415](ivf.md#L415) |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L415"></a>

## `IVF::CalDistanceById`

源码位置：`src/algorithm/ivf/ivf.cpp:415–494`。

先从签名确认输入、返回值和 const/override，再按完整函数体的条件阅读调用点。下表保留了本函数的显式调用以及 lambda 中的调用；进入下层时用“候选实现”定位，未解析的对象由源码静态类型/运行时类型确认。

### 完整函数

```cpp
DatasetPtr
IVF::CalDistanceById(const float* query,
                     const int64_t* ids,
                     int64_t count,
                     bool calculate_precise_distance,
                     int64_t topk) const {
    CHECK_ARGUMENT(count >= 0, "CalDistanceById count must be non-negative");
    const bool invalid_topk = topk != -1 && topk <= 0;
    CHECK_ARGUMENT(not invalid_topk, "CalDistanceById topk must be -1 or positive");
    if (count > 0) {
        CHECK_ARGUMENT(query != nullptr, "CalDistanceById query must not be null");
        CHECK_ARGUMENT(ids != nullptr, "CalDistanceById ids must not be null");
    }
    const int64_t result_count = (topk == -1) ? count : std::min(topk, count);
    auto result = Dataset::Make();
    result->NumElements(1)->Dim(result_count)->Owner(true, allocator_);
    if (count == 0) {
        return result;
    }
    auto* distances = static_cast<float*>(allocator_->Allocate(sizeof(float) * count));
    result->Distances(distances);
    Vector<InnerIdType> inner_ids(count, 0, allocator_);
    std::vector<bool> validity(count, false);
    {
        std::shared_lock<std::shared_mutex> lock(this->label_lookup_mutex_);
        for (int64_t i = 0; i < count; ++i) {
            auto [success, inner_id] = this->label_table_->TryGetIdByLabel(ids[i]);
            if (success) {
                inner_ids[i] = inner_id;
                validity[i] = true;
            }
        }
    }
    if (this->use_reorder_ && calculate_precise_distance && reorder_codes_ != nullptr) {
        auto computer = this->reorder_codes_->FactoryComputer(query);
        this->reorder_codes_->Query(distances, computer, inner_ids.data(), count);
    } else if (this->use_reorder_ && calculate_precise_distance && precise_bucket_ != nullptr) {
        auto computer = this->precise_bucket_->FactoryComputer(query);
        Vector<BucketIdType> bucket_ids(allocator_);
        Vector<InnerIdType> offset_ids(allocator_);
        Vector<int64_t> result_indices(allocator_);
        bucket_ids.reserve(count);
        offset_ids.reserve(count);
        result_indices.reserve(count);
        for (int64_t i = 0; i < count; ++i) {
            if (validity[i]) {
                auto [bucket_id, offset_id] = this->get_location(inner_ids[i]);
                bucket_ids.emplace_back(bucket_id);
                offset_ids.emplace_back(offset_id);
                result_indices.emplace_back(i);
            }
        }
        Vector<float> valid_distances(result_indices.size(), allocator_);
        this->precise_bucket_->Query(valid_distances.data(),
                                     computer,
                                     bucket_ids.data(),
                                     offset_ids.data(),
                                     static_cast<InnerIdType>(result_indices.size()));
        for (uint64_t i = 0; i < result_indices.size(); ++i) {
            distances[result_indices[i]] = valid_distances[i];
        }
    } else {
        auto computer = this->bucket_->FactoryComputer(query);
        for (int64_t i = 0; i < count; ++i) {
            if (validity[i]) {
                auto [bucket_id, offset_id] = this->get_location(inner_ids[i]);
                distances[i] = this->bucket_->QueryOneById(computer, bucket_id, offset_id);
            }
        }
    }
    for (int64_t i = 0; i < count; ++i) {
        if (not validity[i]) {
            distances[i] = -1.0F;
        }
    }
    if (topk == -1) {
        return result;
    }
    return ApplyTopkWithValidity(distances, ids, count, 1, topk, validity, allocator_);
}
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L421 | CHECK_ARGUMENT | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L423 | CHECK_ARGUMENT | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L425 | CHECK_ARGUMENT | if_statement@424 (count &gt; 0) | 当前参考未静态绑定；见下方边界说明 |

| L426 | CHECK_ARGUMENT | if_statement@424 (count &gt; 0) | 当前参考未静态绑定；见下方边界说明 |

| L428 | std::min | conditional_expression@428 (topk == -1) | 当前参考未静态绑定；见下方边界说明 |

| L429 | Dataset::Make | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L430 | result-&gt;NumElements(1)-&gt;Dim(result_count)-&gt;Owner | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L430 | result-&gt;NumElements(1)-&gt;Dim | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L430 | result-&gt;NumElements | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L434 | allocator_-&gt;Allocate | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L435 | result-&gt;Distances | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L441 | this-&gt;label_table_-&gt;TryGetIdByLabel | for_statement@440 i &lt; count | [LabelTable::TryGetIdByLabel · L96](label_table.md#L96) |

| L449 | this-&gt;reorder_codes_-&gt;FactoryComputer | if_statement@448 (this-&gt;use_reorder_ && calculate_precise_distance && reorder_codes_ != nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L450 | this-&gt;reorder_codes_-&gt;Query | if_statement@448 (this-&gt;use_reorder_ && calculate_precise_distance && reorder_codes_ != nullptr) | [BucketDataCell::Query · L82](bucket_datacell_h.md#L82) |

| L450 | inner_ids.data | if_statement@448 (this-&gt;use_reorder_ && calculate_precise_distance && reorder_codes_ != nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L452 | this-&gt;precise_bucket_-&gt;FactoryComputer | if_statement@448 (this-&gt;use_reorder_ && calculate_precise_distance && reorder_codes_ != nullptr) [else 分支] → if_statement@451 (this-&gt;use_reorder_ && calculate_precise_distance && precise_bucket_ != nullptr) | [BucketDataCell&lt;QuantTmpl, IOTmpl&gt;::FactoryComputer · L566](bucket_datacell_h.md#L566) |

| L456 | bucket_ids.reserve | if_statement@448 (this-&gt;use_reorder_ && calculate_precise_distance && reorder_codes_ != nullptr) [else 分支] → if_statement@451 (this-&gt;use_reorder_ && calculate_precise_distance && precise_bucket_ != nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L457 | offset_ids.reserve | if_statement@448 (this-&gt;use_reorder_ && calculate_precise_distance && reorder_codes_ != nullptr) [else 分支] → if_statement@451 (this-&gt;use_reorder_ && calculate_precise_distance && precise_bucket_ != nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L458 | result_indices.reserve | if_statement@448 (this-&gt;use_reorder_ && calculate_precise_distance && reorder_codes_ != nullptr) [else 分支] → if_statement@451 (this-&gt;use_reorder_ && calculate_precise_distance && precise_bucket_ != nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L461 | this-&gt;get_location | if_statement@448 (this-&gt;use_reorder_ && calculate_precise_distance && reorder_codes_ != nullptr) [else 分支] → if_statement@451 (this-&gt;use_reorder_ && calculate_precise_distance && precise_bucket_ != nullptr) → for_statement@459 i &lt; count → if_statement@460 (validity[i]) | [IVF::get_location · L312](ivf.md#L312) |

| L462 | bucket_ids.emplace_back | if_statement@448 (this-&gt;use_reorder_ && calculate_precise_distance && reorder_codes_ != nullptr) [else 分支] → if_statement@451 (this-&gt;use_reorder_ && calculate_precise_distance && precise_bucket_ != nullptr) → for_statement@459 i &lt; count → if_statement@460 (validity[i]) | 当前参考未静态绑定；见下方边界说明 |

| L463 | offset_ids.emplace_back | if_statement@448 (this-&gt;use_reorder_ && calculate_precise_distance && reorder_codes_ != nullptr) [else 分支] → if_statement@451 (this-&gt;use_reorder_ && calculate_precise_distance && precise_bucket_ != nullptr) → for_statement@459 i &lt; count → if_statement@460 (validity[i]) | 当前参考未静态绑定；见下方边界说明 |

| L464 | result_indices.emplace_back | if_statement@448 (this-&gt;use_reorder_ && calculate_precise_distance && reorder_codes_ != nullptr) [else 分支] → if_statement@451 (this-&gt;use_reorder_ && calculate_precise_distance && precise_bucket_ != nullptr) → for_statement@459 i &lt; count → if_statement@460 (validity[i]) | 当前参考未静态绑定；见下方边界说明 |

| L467 | result_indices.size | if_statement@448 (this-&gt;use_reorder_ && calculate_precise_distance && reorder_codes_ != nullptr) [else 分支] → if_statement@451 (this-&gt;use_reorder_ && calculate_precise_distance && precise_bucket_ != nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L468 | this-&gt;precise_bucket_-&gt;Query | if_statement@448 (this-&gt;use_reorder_ && calculate_precise_distance && reorder_codes_ != nullptr) [else 分支] → if_statement@451 (this-&gt;use_reorder_ && calculate_precise_distance && precise_bucket_ != nullptr) | [BucketDataCell::Query · L82](bucket_datacell_h.md#L82) |

| L468 | valid_distances.data | if_statement@448 (this-&gt;use_reorder_ && calculate_precise_distance && reorder_codes_ != nullptr) [else 分支] → if_statement@451 (this-&gt;use_reorder_ && calculate_precise_distance && precise_bucket_ != nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L470 | bucket_ids.data | if_statement@448 (this-&gt;use_reorder_ && calculate_precise_distance && reorder_codes_ != nullptr) [else 分支] → if_statement@451 (this-&gt;use_reorder_ && calculate_precise_distance && precise_bucket_ != nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L471 | offset_ids.data | if_statement@448 (this-&gt;use_reorder_ && calculate_precise_distance && reorder_codes_ != nullptr) [else 分支] → if_statement@451 (this-&gt;use_reorder_ && calculate_precise_distance && precise_bucket_ != nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L472 | result_indices.size | if_statement@448 (this-&gt;use_reorder_ && calculate_precise_distance && reorder_codes_ != nullptr) [else 分支] → if_statement@451 (this-&gt;use_reorder_ && calculate_precise_distance && precise_bucket_ != nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L473 | result_indices.size | if_statement@448 (this-&gt;use_reorder_ && calculate_precise_distance && reorder_codes_ != nullptr) [else 分支] → if_statement@451 (this-&gt;use_reorder_ && calculate_precise_distance && precise_bucket_ != nullptr) → for_statement@473 i &lt; result_indices.size() | 当前参考未静态绑定；见下方边界说明 |

| L477 | this-&gt;bucket_-&gt;FactoryComputer | if_statement@448 (this-&gt;use_reorder_ && calculate_precise_distance && reorder_codes_ != nullptr) [else 分支] → if_statement@451 (this-&gt;use_reorder_ && calculate_precise_distance && precise_bucket_ != nullptr) [else 分支] | [BucketDataCell&lt;QuantTmpl, IOTmpl&gt;::FactoryComputer · L566](bucket_datacell_h.md#L566) |

| L480 | this-&gt;get_location | if_statement@448 (this-&gt;use_reorder_ && calculate_precise_distance && reorder_codes_ != nullptr) [else 分支] → if_statement@451 (this-&gt;use_reorder_ && calculate_precise_distance && precise_bucket_ != nullptr) [else 分支] → for_statement@478 i &lt; count → if_statement@479 (validity[i]) | [IVF::get_location · L312](ivf.md#L312) |

| L481 | this-&gt;bucket_-&gt;QueryOneById | if_statement@448 (this-&gt;use_reorder_ && calculate_precise_distance && reorder_codes_ != nullptr) [else 分支] → if_statement@451 (this-&gt;use_reorder_ && calculate_precise_distance && precise_bucket_ != nullptr) [else 分支] → for_statement@478 i &lt; count → if_statement@479 (validity[i]) | [BucketDataCell::QueryOneById · L71](bucket_datacell_h.md#L71) |

| L493 | ApplyTopkWithValidity | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L496"></a>

## `IVF::CalcDistanceById`

源码位置：`src/algorithm/ivf/ivf.cpp:496–513`。

先从签名确认输入、返回值和 const/override，再按完整函数体的条件阅读调用点。下表保留了本函数的显式调用以及 lambda 中的调用；进入下层时用“候选实现”定位，未解析的对象由源码静态类型/运行时类型确认。

### 完整函数

```cpp
float
IVF::CalcDistanceById(const float* query, int64_t id, bool calculate_precise_distance) const {
    std::shared_lock<std::shared_mutex> lock(this->label_lookup_mutex_);
    auto [success, inner_id] = this->label_table_->TryGetIdByLabel(id);
    if (not success) {
        return -1.0F;
    }
    if (this->use_reorder_ && calculate_precise_distance && reorder_codes_ != nullptr) {
        float dist = 0.0F;
        auto computer = this->reorder_codes_->FactoryComputer(query);
        this->reorder_codes_->Query(&dist, computer, &inner_id, 1);
        return dist;
    }
    auto codes = this->use_reorder_ && calculate_precise_distance ? precise_bucket_ : bucket_;
    auto computer = codes->FactoryComputer(query);
    auto [bucket_id, offset_id] = this->get_location(inner_id);
    return codes->QueryOneById(computer, bucket_id, offset_id);
}
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L499 | this-&gt;label_table_-&gt;TryGetIdByLabel | 函数本体；短路求值/提前返回见源码 | [LabelTable::TryGetIdByLabel · L96](label_table.md#L96) |

| L505 | this-&gt;reorder_codes_-&gt;FactoryComputer | if_statement@503 (this-&gt;use_reorder_ && calculate_precise_distance && reorder_codes_ != nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L506 | this-&gt;reorder_codes_-&gt;Query | if_statement@503 (this-&gt;use_reorder_ && calculate_precise_distance && reorder_codes_ != nullptr) | [BucketDataCell::Query · L82](bucket_datacell_h.md#L82) |

| L510 | codes-&gt;FactoryComputer | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L511 | this-&gt;get_location | 函数本体；短路求值/提前返回见源码 | [IVF::get_location · L312](ivf.md#L312) |

| L512 | codes-&gt;QueryOneById | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L515"></a>

## `IVF::GetVectorByInnerId`

源码位置：`src/algorithm/ivf/ivf.cpp:515–519`。

先从签名确认输入、返回值和 const/override，再按完整函数体的条件阅读调用点。下表保留了本函数的显式调用以及 lambda 中的调用；进入下层时用“候选实现”定位，未解析的对象由源码静态类型/运行时类型确认。

### 完整函数

```cpp
void
IVF::GetVectorByInnerId(InnerIdType inner_id, float* data) const {
    auto [bucket_id, bucket_offset] = this->get_location(inner_id);
    this->bucket_->GetCodesById(bucket_id, bucket_offset, reinterpret_cast<uint8_t*>(data));
}
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L517 | this-&gt;get_location | 函数本体；短路求值/提前返回见源码 | [IVF::get_location · L312](ivf.md#L312) |

| L518 | this-&gt;bucket_-&gt;GetCodesById | 函数本体；短路求值/提前返回见源码 | [BucketDataCell&lt;QuantTmpl, IOTmpl&gt;::GetCodesById · L1017](bucket_datacell_h.md#L1017) |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L521"></a>

## `calculate_percentile`

源码位置：`src/algorithm/ivf/ivf.cpp:521–534`。

先从签名确认输入、返回值和 const/override，再按完整函数体的条件阅读调用点。下表保留了本函数的显式调用以及 lambda 中的调用；进入下层时用“候选实现”定位，未解析的对象由源码静态类型/运行时类型确认。

### 完整函数

```cpp
float
calculate_percentile(const std::vector<float>& sorted_data, float percentile) {
    uint64_t n = sorted_data.size();
    float index = percentile * static_cast<float>(n - 1);
    auto floor_index = static_cast<uint64_t>(std::floor(index));
    uint64_t ceil_index = floor_index + 1;

    if (ceil_index >= n) {
        return sorted_data[floor_index];
    }

    float fractional = index - static_cast<float>(floor_index);
    return sorted_data[floor_index] * (1.0F - fractional) + sorted_data[ceil_index] * fractional;
}
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L523 | sorted_data.size | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L525 | std::floor | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L536"></a>

## `get_data_stats`

源码位置：`src/algorithm/ivf/ivf.cpp:536–573`。

先从签名确认输入、返回值和 const/override，再按完整函数体的条件阅读调用点。下表保留了本函数的显式调用以及 lambda 中的调用；进入下层时用“候选实现”定位，未解析的对象由源码静态类型/运行时类型确认。

### 完整函数

```cpp
JsonType
get_data_stats(const Vector<float>& data) {
    JsonType json;
    if (data.empty()) {
        throw VsagException(ErrorType::INVALID_ARGUMENT, "Vector cannot be empty.");
    }

    float sum = 0.0;
    for (float val : data) {
        sum += val;
    }
    float mean = sum / static_cast<float>(data.size());
    json["mean"].SetFloat(mean);

    float sq_diff_sum = 0.0;
    for (float val : data) {
        sq_diff_sum += (val - mean) * (val - mean);
    }
    float variance = sq_diff_sum / static_cast<float>(data.size());
    json["std"].SetFloat(std::sqrt(variance));

    float min_val = *std::min_element(data.begin(), data.end());
    json["min"].SetFloat(min_val);
    float max_val = *std::max_element(data.begin(), data.end());
    json["max"].SetFloat(max_val);

    std::vector<float> sorted_data(data.begin(), data.end());
    std::sort(sorted_data.begin(), sorted_data.end());

    float q25 = calculate_percentile(sorted_data, 0.25);
    float q50 = calculate_percentile(sorted_data, 0.5);
    float q75 = calculate_percentile(sorted_data, 0.75);
    json["q25"].SetFloat(q25);
    json["q50"].SetFloat(q50);
    json["q75"].SetFloat(q75);

    return json;
}
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L539 | data.empty | if_statement@539 (data.empty()) | 当前参考未静态绑定；见下方边界说明 |

| L540 | VsagException | if_statement@539 (data.empty()) | 当前参考未静态绑定；见下方边界说明 |

| L547 | data.size | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L548 | json["mean"].SetFloat | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L554 | data.size | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L555 | json["std"].SetFloat | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L555 | std::sqrt | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L557 | std::min_element | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L557 | data.begin | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L557 | data.end | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L558 | json["min"].SetFloat | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L559 | std::max_element | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L559 | data.begin | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L559 | data.end | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L560 | json["max"].SetFloat | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L562 | data.begin | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L562 | data.end | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L563 | std::sort | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L563 | sorted_data.begin | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L563 | sorted_data.end | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L565 | calculate_percentile | 函数本体；短路求值/提前返回见源码 | [calculate_percentile · L521](ivf.md#L521) |

| L566 | calculate_percentile | 函数本体；短路求值/提前返回见源码 | [calculate_percentile · L521](ivf.md#L521) |

| L567 | calculate_percentile | 函数本体；短路求值/提前返回见源码 | [calculate_percentile · L521](ivf.md#L521) |

| L568 | json["q25"].SetFloat | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L569 | json["q50"].SetFloat | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L570 | json["q75"].SetFloat | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L575"></a>

## `IVF::GetStats`

源码位置：`src/algorithm/ivf/ivf.cpp:575–602`。

先从签名确认输入、返回值和 const/override，再按完整函数体的条件阅读调用点。下表保留了本函数的显式调用以及 lambda 中的调用；进入下层时用“候选实现”定位，未解析的对象由源码静态类型/运行时类型确认。

### 完整函数

```cpp
std::string
IVF::GetStats() const {
    JsonType stats;
    // bucket_radius
    stats["bucket_count"].SetInt(this->bucket_->bucket_count_);
    Vector<float> centroids(this->dim_, allocator_);
    Vector<float> bucket_counts(allocator_);
    Vector<float> bucket_radius(allocator_);
    for (int i = 0; i < this->bucket_->bucket_count_; ++i) {
        auto size = bucket_->GetBucketSize(i);
        if (size == 0) {
            bucket_counts.push_back(0);
            continue;
        }
        bucket_counts.push_back(static_cast<float>(size));
        Vector<float> dists(size, allocator_);
        partition_strategy_->GetCentroid(i, centroids);
        auto computer = bucket_->FactoryComputer(centroids.data());
        bucket_->ScanBucketById(dists.data(), computer, i);
        float max_distance = *std::max_element(dists.begin(), dists.end());
        bucket_radius.push_back(max_distance);
    }
    // bucket_count_std
    stats["bucket_num"].SetJson(get_data_stats(bucket_counts));
    // bucket_radius
    stats["bucket_radius"].SetJson(get_data_stats(bucket_radius));
    return stats.Dump(4);
}
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L579 | stats["bucket_count"].SetInt | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L584 | bucket_-&gt;GetBucketSize | for_statement@583 i &lt; this-&gt;bucket_-&gt;bucket_count_ | [BucketDataCell::GetBucketSize · L180](bucket_datacell_h.md#L180) |

| L586 | bucket_counts.push_back | for_statement@583 i &lt; this-&gt;bucket_-&gt;bucket_count_ → if_statement@585 (size == 0) | 当前参考未静态绑定；见下方边界说明 |

| L589 | bucket_counts.push_back | for_statement@583 i &lt; this-&gt;bucket_-&gt;bucket_count_ | 当前参考未静态绑定；见下方边界说明 |

| L591 | partition_strategy_-&gt;GetCentroid | for_statement@583 i &lt; this-&gt;bucket_-&gt;bucket_count_ | [GNOIMIPartition::GetCentroid · L440](gno_imi_partition.md#L440)；[IVFNearestPartition::GetCentroid · L286](ivf_nearest_partition.md#L286) |

| L592 | bucket_-&gt;FactoryComputer | for_statement@583 i &lt; this-&gt;bucket_-&gt;bucket_count_ | [BucketDataCell&lt;QuantTmpl, IOTmpl&gt;::FactoryComputer · L566](bucket_datacell_h.md#L566) |

| L592 | centroids.data | for_statement@583 i &lt; this-&gt;bucket_-&gt;bucket_count_ | 当前参考未静态绑定；见下方边界说明 |

| L593 | bucket_-&gt;ScanBucketById | for_statement@583 i &lt; this-&gt;bucket_-&gt;bucket_count_ | [BucketDataCell::ScanBucketById · L63](bucket_datacell_h.md#L63) |

| L593 | dists.data | for_statement@583 i &lt; this-&gt;bucket_-&gt;bucket_count_ | 当前参考未静态绑定；见下方边界说明 |

| L594 | std::max_element | for_statement@583 i &lt; this-&gt;bucket_-&gt;bucket_count_ | 当前参考未静态绑定；见下方边界说明 |

| L594 | dists.begin | for_statement@583 i &lt; this-&gt;bucket_-&gt;bucket_count_ | 当前参考未静态绑定；见下方边界说明 |

| L594 | dists.end | for_statement@583 i &lt; this-&gt;bucket_-&gt;bucket_count_ | 当前参考未静态绑定；见下方边界说明 |

| L595 | bucket_radius.push_back | for_statement@583 i &lt; this-&gt;bucket_-&gt;bucket_count_ | 当前参考未静态绑定；见下方边界说明 |

| L598 | stats["bucket_num"].SetJson | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L598 | get_data_stats | 函数本体；短路求值/提前返回见源码 | [get_data_stats · L536](ivf.md#L536) |

| L600 | stats["bucket_radius"].SetJson | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L600 | get_data_stats | 函数本体；短路求值/提前返回见源码 | [get_data_stats · L536](ivf.md#L536) |

| L601 | stats.Dump | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L604"></a>

## `IVF::AnalyzeIndexBySearch`

源码位置：`src/algorithm/ivf/ivf.cpp:604–614`。

先从签名确认输入、返回值和 const/override，再按完整函数体的条件阅读调用点。下表保留了本函数的显式调用以及 lambda 中的调用；进入下层时用“候选实现”定位，未解析的对象由源码静态类型/运行时类型确认。

### 完整函数

```cpp
std::string
IVF::AnalyzeIndexBySearch(const SearchRequest& request) {
    JsonType stats;
    auto querys = request.query_;
    auto topk = std::min(request.topk_, GetNumElements());
    auto num_elements = querys->GetNumElements();
    auto param_str = request.params_str_;
    // quantization error
    this->analyze_quantizer(stats, querys->GetFloat32Vectors(), num_elements, topk, param_str);
    return stats.Dump(4);
}
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L608 | std::min | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L608 | GetNumElements | 函数本体；短路求值/提前返回见源码 | [IVF::GetNumElements · L291](ivf.md#L291) |

| L609 | querys-&gt;GetNumElements | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L612 | this-&gt;analyze_quantizer | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L612 | querys-&gt;GetFloat32Vectors | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L613 | stats.Dump | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L616"></a>

## `IVF::cal_memory_usage`

源码位置：`src/algorithm/ivf/ivf.cpp:616–637`。

先从签名确认输入、返回值和 const/override，再按完整函数体的条件阅读调用点。下表保留了本函数的显式调用以及 lambda 中的调用；进入下层时用“候选实现”定位，未解析的对象由源码静态类型/运行时类型确认。

### 完整函数

```cpp
void
IVF::cal_memory_usage() {
    auto memory = sizeof(IVF);
    memory += this->bucket_->GetMemoryUsage();
    if (use_reorder_) {
        memory += precise_bucket_ != nullptr ? precise_bucket_->GetMemoryUsage()
                                             : reorder_codes_->GetMemoryUsage();
    }
    if (this->extra_info_size_ > 0 and this->extra_infos_ != nullptr) {
        memory += this->extra_infos_->GetMemoryUsage();
    }
    memory += this->label_table_->GetMemoryUsage();
    memory += location_map_.size() * sizeof(uint64_t);
    memory += partition_strategy_->GetMemoryUsage();
    for (auto& g : bucket_graphs_) {
        if (g != nullptr) {
            memory += g->GetMemoryUsage();
        }
    }
    std::unique_lock lock(this->memory_usage_mutex_);
    this->current_memory_usage_.store(memory);
}
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L619 | this-&gt;bucket_-&gt;GetMemoryUsage | 函数本体；短路求值/提前返回见源码 | [BucketDataCell::GetMemoryUsage · L189](bucket_datacell_h.md#L189) |

| L621 | precise_bucket_-&gt;GetMemoryUsage | if_statement@620 (use_reorder_) → conditional_expression@621 precise_bucket_ != nullptr | [BucketDataCell::GetMemoryUsage · L189](bucket_datacell_h.md#L189) |

| L622 | reorder_codes_-&gt;GetMemoryUsage | if_statement@620 (use_reorder_) → conditional_expression@621 precise_bucket_ != nullptr | 当前参考未静态绑定；见下方边界说明 |

| L625 | this-&gt;extra_infos_-&gt;GetMemoryUsage | if_statement@624 (this-&gt;extra_info_size_ &gt; 0 and this-&gt;extra_infos_ != nullptr) | [IVF::GetMemoryUsage · L639](ivf.md#L639) |

| L627 | this-&gt;label_table_-&gt;GetMemoryUsage | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L628 | location_map_.size | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L629 | partition_strategy_-&gt;GetMemoryUsage | 函数本体；短路求值/提前返回见源码 | [IVFNearestPartition::GetMemoryUsage · L303](ivf_nearest_partition.md#L303)；[IVFPartitionStrategy::GetMemoryUsage · L93](ivf_partition_strategy_h.md#L93) |

| L632 | g-&gt;GetMemoryUsage | for_range_loop@630 → if_statement@631 (g != nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L636 | this-&gt;current_memory_usage_.store | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L639"></a>

## `IVF::GetMemoryUsage`

源码位置：`src/algorithm/ivf/ivf.cpp:639–650`。

先从签名确认输入、返回值和 const/override，再按完整函数体的条件阅读调用点。下表保留了本函数的显式调用以及 lambda 中的调用；进入下层时用“候选实现”定位，未解析的对象由源码静态类型/运行时类型确认。

### 完整函数

```cpp
uint64_t
IVF::GetMemoryUsage() const {
    uint64_t memory = 0;
    {
        std::shared_lock lock(this->memory_usage_mutex_);
        memory = this->current_memory_usage_.load();
    }
    if (this->attr_filter_index_ != nullptr) {
        memory += this->attr_filter_index_->GetMemoryUsage();
    }
    return memory;
}
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L644 | this-&gt;current_memory_usage_.load | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L647 | this-&gt;attr_filter_index_-&gt;GetMemoryUsage | if_statement@646 (this-&gt;attr_filter_index_ != nullptr) | [IVF::GetMemoryUsage · L639](ivf.md#L639) |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。
