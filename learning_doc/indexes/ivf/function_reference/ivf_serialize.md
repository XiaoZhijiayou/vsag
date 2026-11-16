# ivf_serialize.cpp：逐函数完整源码与调用点

[主讲解](../code_walkthrough.md) · [函数总目录](README.md)

源码：[ src/algorithm/ivf/ivf_serialize.cpp ](../../../../src/algorithm/ivf/ivf_serialize.cpp)。基线 `fd363937`。以下源码函数体完整保留；调用点表是语法树中的显式调用表达式，按源码位置排列，不代表 C++ 参数求值顺序。表中“候选实现”需结合类型和参数选分支，不能将同名函数全部视为必经路径。

- [get_ivf_graph_param · L38](ivf_serialize.md#L38)

- [serialize_ivf_graph_param · L62](ivf_serialize.md#L62)

- [has_any_fresh_bucket_graph · L69](ivf_serialize.md#L69)

- [IVF::Serialize · L88](ivf_serialize.md#L88)

- [IVF::collect_streaming_header · L156](ivf_serialize.md#L156)

- [IVF::serialize_streaming_body · L218](ivf_serialize.md#L218)

- [IVF::deserialize_streaming_body · L279](ivf_serialize.md#L279)

- [IVF::load_streaming_body · L284](ivf_serialize.md#L284)

- [IVF::read_streaming_body · L291](ivf_serialize.md#L291)

- [IVF::Deserialize · L526](ivf_serialize.md#L526)


<a id="L38"></a>

## `get_ivf_graph_param`

源码位置：`src/algorithm/ivf/ivf_serialize.cpp:38–60`。

先从签名确认输入、返回值和 const/override，再按完整函数体的条件阅读调用点。下表保留了本函数的显式调用以及 lambda 中的调用；进入下层时用“候选实现”定位，未解析的对象由源码静态类型/运行时类型确认。

### 完整函数

```cpp
static GraphInterfaceParamPtr
get_ivf_graph_param(const std::string& graph_param_string) {
    auto graph_json = JsonType::Parse(graph_param_string);
    if (!graph_json.Contains(IO_PARAMS_KEY) || !graph_json.Contains(GRAPH_STORAGE_TYPE_KEY) ||
        graph_json[GRAPH_STORAGE_TYPE_KEY].GetString() != GRAPH_STORAGE_TYPE_VALUE_FLAT) {
        throw VsagException(ErrorType::INVALID_BINARY,
                            "bucket graph requires flat storage with memory-backed IO");
    }

    auto param = std::dynamic_pointer_cast<GraphDataCellParameter>(
        GraphInterfaceParameter::GetGraphParameterByJson(
            GraphStorageTypes::GRAPH_STORAGE_TYPE_VALUE_FLAT, graph_json));
    if (param == nullptr || param->io_parameter_ == nullptr || param->support_remove_) {
        throw VsagException(ErrorType::INVALID_BINARY, "invalid bucket graph parameters");
    }

    const auto io_type = param->io_parameter_->GetTypeName();
    if (io_type != IO_TYPE_VALUE_MEMORY_IO && io_type != IO_TYPE_VALUE_BLOCK_MEMORY_IO) {
        throw VsagException(ErrorType::INVALID_BINARY,
                            fmt::format("unsupported bucket graph IO type: {}", io_type));
    }
    return param;
}
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L40 | JsonType::Parse | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L41 | graph_json.Contains | if_statement@41 (!graph_json.Contains(IO_PARAMS_KEY) &#124;&#124; !graph_json.Contains(GRAPH_STORAGE_TYPE_KEY) &#124;&#124; graph_json[GRAPH_STORAGE_TYPE_KEY].GetString() != GRAPH_STORAGE_TYPE_VALUE_FLAT) | 当前参考未静态绑定；见下方边界说明 |

| L41 | graph_json.Contains | if_statement@41 (!graph_json.Contains(IO_PARAMS_KEY) &#124;&#124; !graph_json.Contains(GRAPH_STORAGE_TYPE_KEY) &#124;&#124; graph_json[GRAPH_STORAGE_TYPE_KEY].GetString() != GRAPH_STORAGE_TYPE_VALUE_FLAT) | 当前参考未静态绑定；见下方边界说明 |

| L42 | graph_json[GRAPH_STORAGE_TYPE_KEY].GetString | if_statement@41 (!graph_json.Contains(IO_PARAMS_KEY) &#124;&#124; !graph_json.Contains(GRAPH_STORAGE_TYPE_KEY) &#124;&#124; graph_json[GRAPH_STORAGE_TYPE_KEY].GetString() != GRAPH_STORAGE_TYPE_VALUE_FLAT) | 当前参考未静态绑定；见下方边界说明 |

| L43 | VsagException | if_statement@41 (!graph_json.Contains(IO_PARAMS_KEY) &#124;&#124; !graph_json.Contains(GRAPH_STORAGE_TYPE_KEY) &#124;&#124; graph_json[GRAPH_STORAGE_TYPE_KEY].GetString() != GRAPH_STORAGE_TYPE_VALUE_FLAT) | 当前参考未静态绑定；见下方边界说明 |

| L47 | std::dynamic_pointer_cast&lt;GraphDataCellParameter&gt; | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L48 | GraphInterfaceParameter::GetGraphParameterByJson | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L51 | VsagException | if_statement@50 (param == nullptr &#124;&#124; param-&gt;io_parameter_ == nullptr &#124;&#124; param-&gt;support_remove_) | 当前参考未静态绑定；见下方边界说明 |

| L54 | param-&gt;io_parameter_-&gt;GetTypeName | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L56 | VsagException | if_statement@55 (io_type != IO_TYPE_VALUE_MEMORY_IO && io_type != IO_TYPE_VALUE_BLOCK_MEMORY_IO) | 当前参考未静态绑定；见下方边界说明 |

| L57 | fmt::format | if_statement@55 (io_type != IO_TYPE_VALUE_MEMORY_IO && io_type != IO_TYPE_VALUE_BLOCK_MEMORY_IO) | 当前参考未静态绑定；见下方边界说明 |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L62"></a>

## `serialize_ivf_graph_param`

源码位置：`src/algorithm/ivf/ivf_serialize.cpp:62–67`。

先从签名确认输入、返回值和 const/override，再按完整函数体的条件阅读调用点。下表保留了本函数的显式调用以及 lambda 中的调用；进入下层时用“候选实现”定位，未解析的对象由源码静态类型/运行时类型确认。

### 完整函数

```cpp
static JsonType
serialize_ivf_graph_param(const GraphInterfaceParamPtr& graph_param) {
    auto graph_json = graph_param->ToJson();
    graph_json[GRAPH_STORAGE_TYPE_KEY].SetString(GRAPH_STORAGE_TYPE_VALUE_FLAT);
    return graph_json;
}
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L64 | graph_param-&gt;ToJson | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L65 | graph_json[GRAPH_STORAGE_TYPE_KEY].SetString | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L69"></a>

## `has_any_fresh_bucket_graph`

源码位置：`src/algorithm/ivf/ivf_serialize.cpp:69–79`。

先从签名确认输入、返回值和 const/override，再按完整函数体的条件阅读调用点。下表保留了本函数的显式调用以及 lambda 中的调用；进入下层时用“候选实现”定位，未解析的对象由源码静态类型/运行时类型确认。

### 完整函数

```cpp
static bool
has_any_fresh_bucket_graph(const BucketInterfacePtr& bucket,
                           const Vector<GraphInterfacePtr>& bucket_graphs) {
    for (BucketIdType b = 0; b < static_cast<BucketIdType>(bucket_graphs.size()); ++b) {
        if (bucket_graphs[b] != nullptr &&
            bucket_graphs[b]->TotalCount() == bucket->GetBucketSize(b)) {
            return true;
        }
    }
    return false;
}
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L72 | bucket_graphs.size | for_statement@72 b &lt; static_cast&lt;BucketIdType&gt;(bucket_graphs.size()) | 当前参考未静态绑定；见下方边界说明 |

| L74 | bucket_graphs[b]-&gt;TotalCount | for_statement@72 b &lt; static_cast&lt;BucketIdType&gt;(bucket_graphs.size()) → if_statement@73 (bucket_graphs[b] != nullptr && bucket_graphs[b]-&gt;TotalCount() == bucket-&gt;GetBucketSize(b)) | 当前参考未静态绑定；见下方边界说明 |

| L74 | bucket-&gt;GetBucketSize | for_statement@72 b &lt; static_cast&lt;BucketIdType&gt;(bucket_graphs.size()) → if_statement@73 (bucket_graphs[b] != nullptr && bucket_graphs[b]-&gt;TotalCount() == bucket-&gt;GetBucketSize(b)) | [BucketDataCell::GetBucketSize · L180](bucket_datacell_h.md#L180) |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L88"></a>

## `IVF::Serialize`

源码位置：`src/algorithm/ivf/ivf_serialize.cpp:88–154`。

先从签名确认输入、返回值和 const/override，再按完整函数体的条件阅读调用点。下表保留了本函数的显式调用以及 lambda 中的调用；进入下层时用“候选实现”定位，未解析的对象由源码静态类型/运行时类型确认。

### 完整函数

```cpp
void
IVF::Serialize(StreamWriter& writer) const {
    JsonType datacell_offsets;
    JsonType datacell_sizes;
    uint64_t offset = 0;

    WRITE_DATACELL_WITH_NAME(writer, "bucket", bucket_);
    WRITE_DATACELL_WITH_NAME(writer, "partition_strategy", partition_strategy_);
    WRITE_DATACELL_WITH_NAME(writer, "label_table", label_table_);

    if (use_reorder_) {
        if (precise_bucket_ != nullptr) {
            WRITE_DATACELL_WITH_NAME(writer, "precise_bucket", precise_bucket_);
        } else {
            WRITE_DATACELL_WITH_NAME(writer, "reorder_codes", reorder_codes_);
        }
    }

    if (use_attribute_filter_) {
        WRITE_DATACELL_WITH_NAME(writer, "attr_filter_index", attr_filter_index_);
    }

    if (graph_build_threshold_ > 0 && graph_param_ != nullptr &&
        has_any_fresh_bucket_graph(bucket_, bucket_graphs_)) {
        datacell_offsets["bucket_graphs"].SetInt(offset);
        auto bucket_graphs_start = writer.GetCursor();
        StreamWriter::WriteObj(writer, graph_build_threshold_);
        StreamWriter::WriteString(writer, serialize_ivf_graph_param(graph_param_).Dump());
        int64_t graph_count = 0;
        for (BucketIdType b = 0; b < static_cast<BucketIdType>(bucket_graphs_.size()); ++b) {
            if (bucket_graphs_[b] != nullptr &&
                bucket_graphs_[b]->TotalCount() == bucket_->GetBucketSize(b)) {
                ++graph_count;
            }
        }
        StreamWriter::WriteObj(writer, graph_count);
        for (BucketIdType b = 0; b < static_cast<BucketIdType>(bucket_graphs_.size()); ++b) {
            if (bucket_graphs_[b] != nullptr &&
                bucket_graphs_[b]->TotalCount() == bucket_->GetBucketSize(b)) {
                StreamWriter::WriteObj(writer, b);
                bucket_graphs_[b]->Serialize(writer);
            }
        }
        auto bucket_graphs_size = writer.GetCursor() - bucket_graphs_start;
        datacell_sizes["bucket_graphs"].SetInt(bucket_graphs_size);
        offset += bucket_graphs_size;
    }

    // serialize footer (introduced since v0.15)
    JsonType basic_info;
    basic_info["total_elements"].SetInt(this->total_elements_);
    basic_info["use_reorder"].SetBool(this->use_reorder_);
    basic_info["is_trained"].SetBool(this->is_trained_);
    basic_info[DIM].SetInt(this->dim_);
    basic_info[EXTRA_INFO_SIZE].SetInt(0);
    basic_info[INDEX_PARAM].SetString(this->create_param_ptr_->ToString());
    basic_info["data_type"].SetInt(static_cast<int64_t>(this->data_type_));
    basic_info["metric"].SetInt(static_cast<int64_t>(this->metric_));

    auto metadata = std::make_shared<Metadata>();
    metadata->Set(BASIC_INFO, basic_info);
    metadata->Set("datacell_offsets", datacell_offsets);
    metadata->Set("datacell_sizes", datacell_sizes);

    auto footer = std::make_shared<Footer>(metadata);
    footer->Write(writer);
}
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L94 | WRITE_DATACELL_WITH_NAME | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L95 | WRITE_DATACELL_WITH_NAME | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L96 | WRITE_DATACELL_WITH_NAME | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L100 | WRITE_DATACELL_WITH_NAME | if_statement@98 (use_reorder_) → if_statement@99 (precise_bucket_ != nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L102 | WRITE_DATACELL_WITH_NAME | if_statement@98 (use_reorder_) → if_statement@99 (precise_bucket_ != nullptr) [else 分支] | 当前参考未静态绑定；见下方边界说明 |

| L107 | WRITE_DATACELL_WITH_NAME | if_statement@106 (use_attribute_filter_) | 当前参考未静态绑定；见下方边界说明 |

| L111 | has_any_fresh_bucket_graph | if_statement@110 (graph_build_threshold_ &gt; 0 && graph_param_ != nullptr && has_any_fresh_bucket_graph(bucket_, bucket_graphs_)) | [has_any_fresh_bucket_graph · L69](ivf_serialize.md#L69) |

| L112 | datacell_offsets["bucket_graphs"].SetInt | if_statement@110 (graph_build_threshold_ &gt; 0 && graph_param_ != nullptr && has_any_fresh_bucket_graph(bucket_, bucket_graphs_)) | 当前参考未静态绑定；见下方边界说明 |

| L113 | writer.GetCursor | if_statement@110 (graph_build_threshold_ &gt; 0 && graph_param_ != nullptr && has_any_fresh_bucket_graph(bucket_, bucket_graphs_)) | 当前参考未静态绑定；见下方边界说明 |

| L114 | StreamWriter::WriteObj | if_statement@110 (graph_build_threshold_ &gt; 0 && graph_param_ != nullptr && has_any_fresh_bucket_graph(bucket_, bucket_graphs_)) | 当前参考未静态绑定；见下方边界说明 |

| L115 | StreamWriter::WriteString | if_statement@110 (graph_build_threshold_ &gt; 0 && graph_param_ != nullptr && has_any_fresh_bucket_graph(bucket_, bucket_graphs_)) | 当前参考未静态绑定；见下方边界说明 |

| L115 | serialize_ivf_graph_param(graph_param_).Dump | if_statement@110 (graph_build_threshold_ &gt; 0 && graph_param_ != nullptr && has_any_fresh_bucket_graph(bucket_, bucket_graphs_)) | 当前参考未静态绑定；见下方边界说明 |

| L115 | serialize_ivf_graph_param | if_statement@110 (graph_build_threshold_ &gt; 0 && graph_param_ != nullptr && has_any_fresh_bucket_graph(bucket_, bucket_graphs_)) | [serialize_ivf_graph_param · L62](ivf_serialize.md#L62) |

| L117 | bucket_graphs_.size | if_statement@110 (graph_build_threshold_ &gt; 0 && graph_param_ != nullptr && has_any_fresh_bucket_graph(bucket_, bucket_graphs_)) → for_statement@117 b &lt; static_cast&lt;BucketIdType&gt;(bucket_graphs_.size()) | 当前参考未静态绑定；见下方边界说明 |

| L119 | bucket_graphs_[b]-&gt;TotalCount | if_statement@110 (graph_build_threshold_ &gt; 0 && graph_param_ != nullptr && has_any_fresh_bucket_graph(bucket_, bucket_graphs_)) → for_statement@117 b &lt; static_cast&lt;BucketIdType&gt;(bucket_graphs_.size()) → if_statement@118 (bucket_graphs_[b] != nullptr && bucket_graphs_[b]-&gt;TotalCount() == bucket_-&gt;GetBucketSize(b)) | 当前参考未静态绑定；见下方边界说明 |

| L119 | bucket_-&gt;GetBucketSize | if_statement@110 (graph_build_threshold_ &gt; 0 && graph_param_ != nullptr && has_any_fresh_bucket_graph(bucket_, bucket_graphs_)) → for_statement@117 b &lt; static_cast&lt;BucketIdType&gt;(bucket_graphs_.size()) → if_statement@118 (bucket_graphs_[b] != nullptr && bucket_graphs_[b]-&gt;TotalCount() == bucket_-&gt;GetBucketSize(b)) | [BucketDataCell::GetBucketSize · L180](bucket_datacell_h.md#L180) |

| L123 | StreamWriter::WriteObj | if_statement@110 (graph_build_threshold_ &gt; 0 && graph_param_ != nullptr && has_any_fresh_bucket_graph(bucket_, bucket_graphs_)) | 当前参考未静态绑定；见下方边界说明 |

| L124 | bucket_graphs_.size | if_statement@110 (graph_build_threshold_ &gt; 0 && graph_param_ != nullptr && has_any_fresh_bucket_graph(bucket_, bucket_graphs_)) → for_statement@124 b &lt; static_cast&lt;BucketIdType&gt;(bucket_graphs_.size()) | 当前参考未静态绑定；见下方边界说明 |

| L126 | bucket_graphs_[b]-&gt;TotalCount | if_statement@110 (graph_build_threshold_ &gt; 0 && graph_param_ != nullptr && has_any_fresh_bucket_graph(bucket_, bucket_graphs_)) → for_statement@124 b &lt; static_cast&lt;BucketIdType&gt;(bucket_graphs_.size()) → if_statement@125 (bucket_graphs_[b] != nullptr && bucket_graphs_[b]-&gt;TotalCount() == bucket_-&gt;GetBucketSize(b)) | 当前参考未静态绑定；见下方边界说明 |

| L126 | bucket_-&gt;GetBucketSize | if_statement@110 (graph_build_threshold_ &gt; 0 && graph_param_ != nullptr && has_any_fresh_bucket_graph(bucket_, bucket_graphs_)) → for_statement@124 b &lt; static_cast&lt;BucketIdType&gt;(bucket_graphs_.size()) → if_statement@125 (bucket_graphs_[b] != nullptr && bucket_graphs_[b]-&gt;TotalCount() == bucket_-&gt;GetBucketSize(b)) | [BucketDataCell::GetBucketSize · L180](bucket_datacell_h.md#L180) |

| L127 | StreamWriter::WriteObj | if_statement@110 (graph_build_threshold_ &gt; 0 && graph_param_ != nullptr && has_any_fresh_bucket_graph(bucket_, bucket_graphs_)) → for_statement@124 b &lt; static_cast&lt;BucketIdType&gt;(bucket_graphs_.size()) → if_statement@125 (bucket_graphs_[b] != nullptr && bucket_graphs_[b]-&gt;TotalCount() == bucket_-&gt;GetBucketSize(b)) | 当前参考未静态绑定；见下方边界说明 |

| L128 | bucket_graphs_[b]-&gt;Serialize | if_statement@110 (graph_build_threshold_ &gt; 0 && graph_param_ != nullptr && has_any_fresh_bucket_graph(bucket_, bucket_graphs_)) → for_statement@124 b &lt; static_cast&lt;BucketIdType&gt;(bucket_graphs_.size()) → if_statement@125 (bucket_graphs_[b] != nullptr && bucket_graphs_[b]-&gt;TotalCount() == bucket_-&gt;GetBucketSize(b)) | 当前参考未静态绑定；见下方边界说明 |

| L131 | writer.GetCursor | if_statement@110 (graph_build_threshold_ &gt; 0 && graph_param_ != nullptr && has_any_fresh_bucket_graph(bucket_, bucket_graphs_)) | 当前参考未静态绑定；见下方边界说明 |

| L132 | datacell_sizes["bucket_graphs"].SetInt | if_statement@110 (graph_build_threshold_ &gt; 0 && graph_param_ != nullptr && has_any_fresh_bucket_graph(bucket_, bucket_graphs_)) | 当前参考未静态绑定；见下方边界说明 |

| L138 | basic_info["total_elements"].SetInt | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L139 | basic_info["use_reorder"].SetBool | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L140 | basic_info["is_trained"].SetBool | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L141 | basic_info[DIM].SetInt | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L142 | basic_info[EXTRA_INFO_SIZE].SetInt | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L143 | basic_info[INDEX_PARAM].SetString | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L143 | this-&gt;create_param_ptr_-&gt;ToString | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L144 | basic_info["data_type"].SetInt | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L145 | basic_info["metric"].SetInt | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L147 | std::make_shared&lt;Metadata&gt; | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L148 | metadata-&gt;Set | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L149 | metadata-&gt;Set | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L150 | metadata-&gt;Set | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L152 | std::make_shared&lt;Footer&gt; | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L153 | footer-&gt;Write | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L156"></a>

## `IVF::collect_streaming_header`

源码位置：`src/algorithm/ivf/ivf_serialize.cpp:156–216`。

先从签名确认输入、返回值和 const/override，再按完整函数体的条件阅读调用点。下表保留了本函数的显式调用以及 lambda 中的调用；进入下层时用“候选实现”定位，未解析的对象由源码静态类型/运行时类型确认。

### 完整函数

```cpp
MetadataPtr
IVF::collect_streaming_header() const {
    auto metadata = std::make_shared<Metadata>();
    metadata->Set("format", "vsag_stream_v1");
    metadata->Set("index_name", this->GetName());

    JsonType basic_info;
    basic_info["total_elements"].SetInt(this->total_elements_);
    basic_info["use_reorder"].SetBool(this->use_reorder_);
    basic_info["is_trained"].SetBool(this->is_trained_);
    basic_info[DIM].SetInt(this->dim_);
    basic_info[EXTRA_INFO_SIZE].SetInt(0);
    basic_info[INDEX_PARAM].SetString(this->create_param_ptr_->ToString());
    basic_info["data_type"].SetInt(static_cast<int64_t>(this->data_type_));
    basic_info["metric"].SetInt(static_cast<int64_t>(this->metric_));
    metadata->Set(BASIC_INFO, basic_info);

    JsonType manifest;
    auto bucket_tag = static_cast<uint32_t>(StreamSerializationTag::IVF_BUCKET);
    auto partition_tag = static_cast<uint32_t>(StreamSerializationTag::IVF_PARTITION_STRATEGY);
    auto label_tag = static_cast<uint32_t>(StreamSerializationTag::LABEL_TABLE);
    AppendStreamingManifestBlock(manifest,
                                 bucket_tag,
                                 StreamSerializationBlockCurrentVersion(bucket_tag),
                                 StreamSerializationTagCritical(bucket_tag));
    AppendStreamingManifestBlock(manifest,
                                 partition_tag,
                                 StreamSerializationBlockCurrentVersion(partition_tag),
                                 StreamSerializationTagCritical(partition_tag));
    AppendStreamingManifestBlock(manifest,
                                 label_tag,
                                 StreamSerializationBlockCurrentVersion(label_tag),
                                 StreamSerializationTagCritical(label_tag));
    if (this->use_reorder_) {
        auto tag = static_cast<uint32_t>(precise_bucket_ != nullptr
                                             ? StreamSerializationTag::IVF_PRECISE_BUCKET
                                             : StreamSerializationTag::HIGH_PRECISION_CODES);
        AppendStreamingManifestBlock(manifest,
                                     tag,
                                     StreamSerializationBlockCurrentVersion(tag),
                                     StreamSerializationTagCritical(tag));
    }
    if (this->use_attribute_filter_) {
        auto tag = static_cast<uint32_t>(StreamSerializationTag::ATTRIBUTE_FILTER);
        AppendStreamingManifestBlock(manifest,
                                     tag,
                                     StreamSerializationBlockCurrentVersion(tag),
                                     StreamSerializationTagCritical(tag));
    }
    if (graph_build_threshold_ > 0 && graph_param_ != nullptr &&
        has_any_fresh_bucket_graph(bucket_, bucket_graphs_)) {
        auto tag = static_cast<uint32_t>(StreamSerializationTag::IVF_BUCKET_GRAPH);
        AppendStreamingManifestBlock(manifest,
                                     tag,
                                     StreamSerializationBlockCurrentVersion(tag),
                                     StreamSerializationTagCritical(tag));
    }
    metadata->Set("block_manifest", manifest);
    metadata->SetEmptyIndex(this->GetNumElements() == 0);
    return metadata;
}
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L158 | std::make_shared&lt;Metadata&gt; | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L159 | metadata-&gt;Set | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L160 | metadata-&gt;Set | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L160 | this-&gt;GetName | 函数本体；短路求值/提前返回见源码 | [IVF::GetName · L126](ivf_h.md#L126) |

| L163 | basic_info["total_elements"].SetInt | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L164 | basic_info["use_reorder"].SetBool | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L165 | basic_info["is_trained"].SetBool | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L166 | basic_info[DIM].SetInt | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L167 | basic_info[EXTRA_INFO_SIZE].SetInt | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L168 | basic_info[INDEX_PARAM].SetString | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L168 | this-&gt;create_param_ptr_-&gt;ToString | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L169 | basic_info["data_type"].SetInt | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L170 | basic_info["metric"].SetInt | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L171 | metadata-&gt;Set | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L177 | AppendStreamingManifestBlock | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L179 | StreamSerializationBlockCurrentVersion | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L180 | StreamSerializationTagCritical | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L181 | AppendStreamingManifestBlock | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L183 | StreamSerializationBlockCurrentVersion | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L184 | StreamSerializationTagCritical | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L185 | AppendStreamingManifestBlock | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L187 | StreamSerializationBlockCurrentVersion | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L188 | StreamSerializationTagCritical | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L193 | AppendStreamingManifestBlock | if_statement@189 (this-&gt;use_reorder_) | 当前参考未静态绑定；见下方边界说明 |

| L195 | StreamSerializationBlockCurrentVersion | if_statement@189 (this-&gt;use_reorder_) | 当前参考未静态绑定；见下方边界说明 |

| L196 | StreamSerializationTagCritical | if_statement@189 (this-&gt;use_reorder_) | 当前参考未静态绑定；见下方边界说明 |

| L200 | AppendStreamingManifestBlock | if_statement@198 (this-&gt;use_attribute_filter_) | 当前参考未静态绑定；见下方边界说明 |

| L202 | StreamSerializationBlockCurrentVersion | if_statement@198 (this-&gt;use_attribute_filter_) | 当前参考未静态绑定；见下方边界说明 |

| L203 | StreamSerializationTagCritical | if_statement@198 (this-&gt;use_attribute_filter_) | 当前参考未静态绑定；见下方边界说明 |

| L206 | has_any_fresh_bucket_graph | if_statement@205 (graph_build_threshold_ &gt; 0 && graph_param_ != nullptr && has_any_fresh_bucket_graph(bucket_, bucket_graphs_)) | [has_any_fresh_bucket_graph · L69](ivf_serialize.md#L69) |

| L208 | AppendStreamingManifestBlock | if_statement@205 (graph_build_threshold_ &gt; 0 && graph_param_ != nullptr && has_any_fresh_bucket_graph(bucket_, bucket_graphs_)) | 当前参考未静态绑定；见下方边界说明 |

| L210 | StreamSerializationBlockCurrentVersion | if_statement@205 (graph_build_threshold_ &gt; 0 && graph_param_ != nullptr && has_any_fresh_bucket_graph(bucket_, bucket_graphs_)) | 当前参考未静态绑定；见下方边界说明 |

| L211 | StreamSerializationTagCritical | if_statement@205 (graph_build_threshold_ &gt; 0 && graph_param_ != nullptr && has_any_fresh_bucket_graph(bucket_, bucket_graphs_)) | 当前参考未静态绑定；见下方边界说明 |

| L213 | metadata-&gt;Set | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L214 | metadata-&gt;SetEmptyIndex | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L214 | this-&gt;GetNumElements | 函数本体；短路求值/提前返回见源码 | [IVF::GetNumElements · L291](ivf.md#L291) |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L218"></a>

## `IVF::serialize_streaming_body`

源码位置：`src/algorithm/ivf/ivf_serialize.cpp:218–277`。

先从签名确认输入、返回值和 const/override，再按完整函数体的条件阅读调用点。下表保留了本函数的显式调用以及 lambda 中的调用；进入下层时用“候选实现”定位，未解析的对象由源码静态类型/运行时类型确认。

### 完整函数

```cpp
void
IVF::serialize_streaming_body(StreamWriter& writer) const {
    auto bucket_tag = static_cast<uint32_t>(StreamSerializationTag::IVF_BUCKET);
    auto partition_tag = static_cast<uint32_t>(StreamSerializationTag::IVF_PARTITION_STRATEGY);
    auto label_tag = static_cast<uint32_t>(StreamSerializationTag::LABEL_TABLE);

    WriteStreamingBlock(
        writer, bucket_tag, StreamSerializationTagCritical(bucket_tag), [this](StreamWriter& w) {
            this->bucket_->Serialize(w);
        });
    WriteStreamingBlock(writer,
                        partition_tag,
                        StreamSerializationTagCritical(partition_tag),
                        [this](StreamWriter& w) { this->partition_strategy_->Serialize(w); });
    WriteStreamingBlock(
        writer, label_tag, StreamSerializationTagCritical(label_tag), [this](StreamWriter& w) {
            this->label_table_->Serialize(w);
        });
    if (this->use_reorder_) {
        auto tag = static_cast<uint32_t>(precise_bucket_ != nullptr
                                             ? StreamSerializationTag::IVF_PRECISE_BUCKET
                                             : StreamSerializationTag::HIGH_PRECISION_CODES);
        WriteStreamingBlock(
            writer, tag, StreamSerializationTagCritical(tag), [this](StreamWriter& w) {
                if (this->precise_bucket_ != nullptr) {
                    this->precise_bucket_->Serialize(w);
                } else {
                    this->reorder_codes_->Serialize(w);
                }
            });
    }
    if (this->use_attribute_filter_) {
        auto tag = static_cast<uint32_t>(StreamSerializationTag::ATTRIBUTE_FILTER);
        WriteStreamingBlock(
            writer, tag, StreamSerializationTagCritical(tag), [this](StreamWriter& w) {
                this->attr_filter_index_->Serialize(w);
            });
    }
    if (graph_build_threshold_ > 0 && graph_param_ != nullptr &&
        has_any_fresh_bucket_graph(bucket_, bucket_graphs_)) {
        auto tag = static_cast<uint32_t>(StreamSerializationTag::IVF_BUCKET_GRAPH);
        WriteStreamingBlock(
            writer, tag, StreamSerializationTagCritical(tag), [this](StreamWriter& w) {
                StreamWriter::WriteObj(w, graph_build_threshold_);
                StreamWriter::WriteString(w, serialize_ivf_graph_param(graph_param_).Dump());
                auto graph_count = static_cast<uint64_t>(bucket_graphs_.size());
                StreamWriter::WriteObj(w, graph_count);
                for (uint64_t i = 0; i < graph_count; ++i) {
                    bool has_graph = (bucket_graphs_[i] != nullptr &&
                                      bucket_graphs_[i]->TotalCount() ==
                                          bucket_->GetBucketSize(static_cast<BucketIdType>(i)));
                    StreamWriter::WriteObj(w, has_graph);
                    if (has_graph) {
                        StreamWriter::WriteObj(w, static_cast<BucketIdType>(i));
                        bucket_graphs_[i]->Serialize(w);
                    }
                }
            });
    }
}
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L224 | WriteStreamingBlock | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L225 | StreamSerializationTagCritical | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L226 | this-&gt;bucket_-&gt;Serialize | lambda@225（定义体，执行时间取决于调用/调度） | [BucketDataCell&lt;QuantTmpl, IOTmpl&gt;::Serialize · L883](bucket_datacell_h.md#L883) |

| L228 | WriteStreamingBlock | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L230 | StreamSerializationTagCritical | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L231 | this-&gt;partition_strategy_-&gt;Serialize | lambda@231（定义体，执行时间取决于调用/调度） | [GNOIMIPartition::Serialize · L323](gno_imi_partition.md#L323)；[IVFNearestPartition::Serialize · L227](ivf_nearest_partition.md#L227)；[IVFPartitionStrategy::Serialize · L75](ivf_partition_strategy_h.md#L75) |

| L232 | WriteStreamingBlock | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L233 | StreamSerializationTagCritical | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L234 | this-&gt;label_table_-&gt;Serialize | lambda@233（定义体，执行时间取决于调用/调度） | 当前参考未静态绑定；见下方边界说明 |

| L240 | WriteStreamingBlock | if_statement@236 (this-&gt;use_reorder_) | 当前参考未静态绑定；见下方边界说明 |

| L241 | StreamSerializationTagCritical | if_statement@236 (this-&gt;use_reorder_) | 当前参考未静态绑定；见下方边界说明 |

| L243 | this-&gt;precise_bucket_-&gt;Serialize | if_statement@236 (this-&gt;use_reorder_) → lambda@241（定义体，执行时间取决于调用/调度） → if_statement@242 (this-&gt;precise_bucket_ != nullptr) | [BucketDataCell&lt;QuantTmpl, IOTmpl&gt;::Serialize · L883](bucket_datacell_h.md#L883) |

| L245 | this-&gt;reorder_codes_-&gt;Serialize | if_statement@236 (this-&gt;use_reorder_) → lambda@241（定义体，执行时间取决于调用/调度） → if_statement@242 (this-&gt;precise_bucket_ != nullptr) [else 分支] | [IVF::Serialize · L88](ivf_serialize.md#L88) |

| L251 | WriteStreamingBlock | if_statement@249 (this-&gt;use_attribute_filter_) | 当前参考未静态绑定；见下方边界说明 |

| L252 | StreamSerializationTagCritical | if_statement@249 (this-&gt;use_attribute_filter_) | 当前参考未静态绑定；见下方边界说明 |

| L253 | this-&gt;attr_filter_index_-&gt;Serialize | if_statement@249 (this-&gt;use_attribute_filter_) → lambda@252（定义体，执行时间取决于调用/调度） | [IVF::Serialize · L88](ivf_serialize.md#L88) |

| L257 | has_any_fresh_bucket_graph | if_statement@256 (graph_build_threshold_ &gt; 0 && graph_param_ != nullptr && has_any_fresh_bucket_graph(bucket_, bucket_graphs_)) | [has_any_fresh_bucket_graph · L69](ivf_serialize.md#L69) |

| L259 | WriteStreamingBlock | if_statement@256 (graph_build_threshold_ &gt; 0 && graph_param_ != nullptr && has_any_fresh_bucket_graph(bucket_, bucket_graphs_)) | 当前参考未静态绑定；见下方边界说明 |

| L260 | StreamSerializationTagCritical | if_statement@256 (graph_build_threshold_ &gt; 0 && graph_param_ != nullptr && has_any_fresh_bucket_graph(bucket_, bucket_graphs_)) | 当前参考未静态绑定；见下方边界说明 |

| L261 | StreamWriter::WriteObj | if_statement@256 (graph_build_threshold_ &gt; 0 && graph_param_ != nullptr && has_any_fresh_bucket_graph(bucket_, bucket_graphs_)) → lambda@260（定义体，执行时间取决于调用/调度） | 当前参考未静态绑定；见下方边界说明 |

| L262 | StreamWriter::WriteString | if_statement@256 (graph_build_threshold_ &gt; 0 && graph_param_ != nullptr && has_any_fresh_bucket_graph(bucket_, bucket_graphs_)) → lambda@260（定义体，执行时间取决于调用/调度） | 当前参考未静态绑定；见下方边界说明 |

| L262 | serialize_ivf_graph_param(graph_param_).Dump | if_statement@256 (graph_build_threshold_ &gt; 0 && graph_param_ != nullptr && has_any_fresh_bucket_graph(bucket_, bucket_graphs_)) → lambda@260（定义体，执行时间取决于调用/调度） | 当前参考未静态绑定；见下方边界说明 |

| L262 | serialize_ivf_graph_param | if_statement@256 (graph_build_threshold_ &gt; 0 && graph_param_ != nullptr && has_any_fresh_bucket_graph(bucket_, bucket_graphs_)) → lambda@260（定义体，执行时间取决于调用/调度） | [serialize_ivf_graph_param · L62](ivf_serialize.md#L62) |

| L263 | bucket_graphs_.size | if_statement@256 (graph_build_threshold_ &gt; 0 && graph_param_ != nullptr && has_any_fresh_bucket_graph(bucket_, bucket_graphs_)) → lambda@260（定义体，执行时间取决于调用/调度） | 当前参考未静态绑定；见下方边界说明 |

| L264 | StreamWriter::WriteObj | if_statement@256 (graph_build_threshold_ &gt; 0 && graph_param_ != nullptr && has_any_fresh_bucket_graph(bucket_, bucket_graphs_)) → lambda@260（定义体，执行时间取决于调用/调度） | 当前参考未静态绑定；见下方边界说明 |

| L267 | bucket_graphs_[i]-&gt;TotalCount | if_statement@256 (graph_build_threshold_ &gt; 0 && graph_param_ != nullptr && has_any_fresh_bucket_graph(bucket_, bucket_graphs_)) → lambda@260（定义体，执行时间取决于调用/调度） → for_statement@265 i &lt; graph_count | 当前参考未静态绑定；见下方边界说明 |

| L268 | bucket_-&gt;GetBucketSize | if_statement@256 (graph_build_threshold_ &gt; 0 && graph_param_ != nullptr && has_any_fresh_bucket_graph(bucket_, bucket_graphs_)) → lambda@260（定义体，执行时间取决于调用/调度） → for_statement@265 i &lt; graph_count | [BucketDataCell::GetBucketSize · L180](bucket_datacell_h.md#L180) |

| L269 | StreamWriter::WriteObj | if_statement@256 (graph_build_threshold_ &gt; 0 && graph_param_ != nullptr && has_any_fresh_bucket_graph(bucket_, bucket_graphs_)) → lambda@260（定义体，执行时间取决于调用/调度） → for_statement@265 i &lt; graph_count | 当前参考未静态绑定；见下方边界说明 |

| L271 | StreamWriter::WriteObj | if_statement@256 (graph_build_threshold_ &gt; 0 && graph_param_ != nullptr && has_any_fresh_bucket_graph(bucket_, bucket_graphs_)) → lambda@260（定义体，执行时间取决于调用/调度） → for_statement@265 i &lt; graph_count → if_statement@270 (has_graph) | 当前参考未静态绑定；见下方边界说明 |

| L272 | bucket_graphs_[i]-&gt;Serialize | if_statement@256 (graph_build_threshold_ &gt; 0 && graph_param_ != nullptr && has_any_fresh_bucket_graph(bucket_, bucket_graphs_)) → lambda@260（定义体，执行时间取决于调用/调度） → for_statement@265 i &lt; graph_count → if_statement@270 (has_graph) | 当前参考未静态绑定；见下方边界说明 |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L279"></a>

## `IVF::deserialize_streaming_body`

源码位置：`src/algorithm/ivf/ivf_serialize.cpp:279–282`。

先从签名确认输入、返回值和 const/override，再按完整函数体的条件阅读调用点。下表保留了本函数的显式调用以及 lambda 中的调用；进入下层时用“候选实现”定位，未解析的对象由源码静态类型/运行时类型确认。

### 完整函数

```cpp
void
IVF::deserialize_streaming_body(StreamReader& reader, const MetadataPtr& metadata) {
    this->read_streaming_body(reader, metadata);
}
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L281 | this-&gt;read_streaming_body | 函数本体；短路求值/提前返回见源码 | [IVF::read_streaming_body · L291](ivf_serialize.md#L291) |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L284"></a>

## `IVF::load_streaming_body`

源码位置：`src/algorithm/ivf/ivf_serialize.cpp:284–289`。

先从签名确认输入、返回值和 const/override，再按完整函数体的条件阅读调用点。下表保留了本函数的显式调用以及 lambda 中的调用；进入下层时用“候选实现”定位，未解析的对象由源码静态类型/运行时类型确认。

### 完整函数

```cpp
void
IVF::load_streaming_body(StreamReader& reader,
                         const MetadataPtr& metadata,
                         const LoadParameters& parameters) {
    this->read_streaming_body(reader, metadata, &parameters);
}
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L288 | this-&gt;read_streaming_body | 函数本体；短路求值/提前返回见源码 | [IVF::read_streaming_body · L291](ivf_serialize.md#L291) |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L291"></a>

## `IVF::read_streaming_body`

源码位置：`src/algorithm/ivf/ivf_serialize.cpp:291–519`。

先从签名确认输入、返回值和 const/override，再按完整函数体的条件阅读调用点。下表保留了本函数的显式调用以及 lambda 中的调用；进入下层时用“候选实现”定位，未解析的对象由源码静态类型/运行时类型确认。

### 完整函数

```cpp
void
IVF::read_streaming_body(StreamReader& reader,
                         const MetadataPtr& metadata,
                         const LoadParameters* load_parameters) {
    auto basic_info = metadata->Get(BASIC_INFO);
    this->total_elements_ = basic_info["total_elements"].GetInt();
    this->use_reorder_ = basic_info["use_reorder"].GetBool();
    this->is_trained_ = basic_info["is_trained"].GetBool();
    if (precise_bucket_ != nullptr and not basic_info.Contains(INDEX_PARAM)) {
        throw VsagException(ErrorType::UNSUPPORTED_INDEX_OPERATION,
                            "IVF precise bucket requires persisted index parameters");
    }
    if (basic_info.Contains(INDEX_PARAM)) {
        auto index_param = std::make_shared<IVFParameter>();
        index_param->FromString(basic_info[INDEX_PARAM].GetString());
        if (not this->create_param_ptr_->CheckCompatibility(index_param)) {
            auto message = fmt::format("IVF index parameter not match, current: {}, new: {}",
                                       this->create_param_ptr_->ToString(),
                                       index_param->ToString());
            logger::error(message);
            throw VsagException(ErrorType::INVALID_ARGUMENT, message);
        }
    }

    bool loaded_bucket = false;
    bool loaded_partition = false;
    bool loaded_label_table = false;
    bool loaded_precise_codes = false;
    bool loaded_attribute_filter = false;

    ReaderIOParamPtr precise_reader_param = nullptr;
    auto ivf_param = std::dynamic_pointer_cast<IVFParameter>(create_param_ptr_);
    if (ivf_param != nullptr && ivf_param->precise_codes_param != nullptr &&
        ivf_param->precise_codes_param->io_parameter != nullptr &&
        ivf_param->precise_codes_param->io_parameter->GetTypeName() == IO_TYPE_VALUE_READER_IO) {
        constexpr const char* precise_reader_key = "precise_reader";
        if (load_parameters == nullptr or not load_parameters->HasReader(precise_reader_key)) {
            throw VsagException(ErrorType::INVALID_ARGUMENT,
                                "reader-backed IVF precise codes require precise_reader");
        }
        auto precise_reader = load_parameters->GetReader(precise_reader_key);
        if (precise_reader == nullptr) {
            throw VsagException(ErrorType::INVALID_ARGUMENT, "precise_reader is null");
        }
        precise_reader_param = std::dynamic_pointer_cast<ReaderIOParameter>(
            ivf_param->precise_codes_param->io_parameter);
        if (precise_reader_param == nullptr) {
            throw VsagException(ErrorType::INTERNAL_ERROR,
                                "IVF precise reader IO parameter is invalid");
        }
        precise_reader_param->reader = std::move(precise_reader);
    }

    while (true) {
        auto block_header = StreamBlockHeader::Read(reader);
        if (block_header.IsSectionEnd()) {
            break;
        }
        BoundedForwardReader block_reader(&reader, block_header.value_len);
        if (!StreamSerializationBlockVersionSupported(block_header.tag,
                                                      block_header.block_version)) {
            if (block_header.IsCritical()) {
                throw VsagException(ErrorType::UNSUPPORTED_INDEX_OPERATION,
                                    fmt::format("unsupported IVF streaming block version: tag={}, "
                                                "name={}, version={}, flags={}, value_len={}",
                                                block_header.tag,
                                                StreamSerializationTagName(block_header.tag),
                                                block_header.block_version,
                                                block_header.flags,
                                                block_header.value_len));
            }
            block_reader.SkipRemaining();
            continue;
        }

        auto read_precise_block = [&](const auto& deserialize, const auto& init_io) {
            if (precise_reader_param == nullptr) {
                ReadSeekableBlockPayload(block_reader, block_header, deserialize);
                return;
            }
            block_reader.SkipRemaining();
            ReadExternalBlockPayload(precise_reader_param->reader, block_header, deserialize);
            init_io(precise_reader_param);
        };

        switch (static_cast<StreamSerializationTag>(block_header.tag)) {
            case StreamSerializationTag::IVF_BUCKET:
                ReadSeekableBlockPayload(block_reader, block_header, [this](StreamReader& block) {
                    this->bucket_->Deserialize(block);
                });
                loaded_bucket = true;
                break;
            case StreamSerializationTag::IVF_PARTITION_STRATEGY:
                ReadSeekableBlockPayload(block_reader, block_header, [this](StreamReader& block) {
                    this->partition_strategy_->Deserialize(block);
                });
                loaded_partition = true;
                break;
            case StreamSerializationTag::LABEL_TABLE:
                ReadSeekableBlockPayload(block_reader, block_header, [this](StreamReader& block) {
                    this->label_table_->Deserialize(block);
                });
                loaded_label_table = true;
                break;
            case StreamSerializationTag::HIGH_PRECISION_CODES:
                if (this->use_reorder_ and this->reorder_codes_ != nullptr) {
                    read_precise_block(
                        [this](StreamReader& block) { this->reorder_codes_->Deserialize(block); },
                        [this](const IOParamPtr& io_param) {
                            this->reorder_codes_->InitIO(io_param);
                        });
                    loaded_precise_codes = true;
                }
                break;
            case StreamSerializationTag::IVF_PRECISE_BUCKET:
                if (this->use_reorder_ and this->precise_bucket_ != nullptr) {
                    read_precise_block(
                        [this](StreamReader& block) { this->precise_bucket_->Deserialize(block); },
                        [this](const IOParamPtr& io_param) {
                            this->precise_bucket_->InitIO(io_param);
                        });
                    loaded_precise_codes = true;
                }
                break;
            case StreamSerializationTag::ATTRIBUTE_FILTER:
                if (this->use_attribute_filter_) {
                    ReadSeekableBlockPayload(
                        block_reader, block_header, [this](StreamReader& block) {
                            this->attr_filter_index_->Deserialize(block);
                        });
                    loaded_attribute_filter = true;
                    this->has_attribute_ = true;
                }
                break;
            case StreamSerializationTag::IVF_BUCKET_GRAPH: {
                ReadSeekableBlockPayload(block_reader, block_header, [this](StreamReader& block) {
                    StreamReader::ReadObj(block, this->graph_build_threshold_);
                    this->graph_param_ = get_ivf_graph_param(StreamReader::ReadString(block));
                    uint64_t graph_count = 0;
                    StreamReader::ReadObj(block, graph_count);
                    auto bucket_count = this->bucket_->bucket_count_;
                    if (graph_count > static_cast<uint64_t>(bucket_count)) {
                        throw VsagException(
                            ErrorType::INVALID_BINARY,
                            fmt::format("bucket graph_count {} exceeds bucket_count {}",
                                        graph_count,
                                        bucket_count));
                    }
                    this->bucket_graphs_.resize(bucket_count);
                    for (uint64_t i = 0; i < graph_count; ++i) {
                        bool has_graph = false;
                        StreamReader::ReadObj(block, has_graph);
                        if (has_graph) {
                            BucketIdType bid = 0;
                            StreamReader::ReadObj(block, bid);
                            auto graph = GraphInterface::MakeInstance(this->graph_param_,
                                                                      this->common_param_);
                            graph->Deserialize(block);
                            if (bid >= 0 && bid < static_cast<BucketIdType>(bucket_count)) {
                                const auto total = graph->TotalCount();
                                const auto expected_total = bucket_->GetBucketSize(bid);
                                if (total != expected_total || total > graph->MaxCapacity()) {
                                    throw VsagException(
                                        ErrorType::INVALID_BINARY,
                                        "corrupt bucket graph: invalid total count");
                                }
                                for (InnerIdType nid = 0; nid < total; ++nid) {
                                    if (graph->GetNeighborSize(nid) > graph->MaximumDegree()) {
                                        throw VsagException(ErrorType::INVALID_BINARY,
                                                            "corrupt bucket graph: neighbor count "
                                                            "exceeds maximum degree");
                                    }
                                    Vector<InnerIdType> nbrs(this->allocator_);
                                    graph->GetNeighbors(nid, nbrs);
                                    for (auto nb : nbrs) {
                                        if (nb >= total) {
                                            throw VsagException(
                                                ErrorType::INVALID_BINARY,
                                                "corrupt bucket graph: neighbor ID out of range");
                                        }
                                    }
                                }
                                this->bucket_graphs_[bid] = std::move(graph);
                            }
                        }
                    }
                });
                if (graph_build_threshold_ > 0 && this->bucket_searcher_ != nullptr) {
                    // Replace flat searcher with graph searcher now that graphs are loaded.
                    this->bucket_searcher_ = std::make_shared<GraphBucketSearcher>(
                        graph_build_threshold_, bucket_graphs_, allocator_);
                }
                break;
            }
            default:
                if (block_header.IsCritical()) {
                    throw VsagException(ErrorType::UNSUPPORTED_INDEX_OPERATION,
                                        fmt::format("unknown IVF streaming serialization block: "
                                                    "tag={}, name={}, version={}, flags={}, "
                                                    "value_len={}",
                                                    block_header.tag,
                                                    StreamSerializationTagName(block_header.tag),
                                                    block_header.block_version,
                                                    block_header.flags,
                                                    block_header.value_len));
                }
                break;
        }
        block_reader.SkipRemaining();
    }

    if (!loaded_bucket || !loaded_partition || !loaded_label_table) {
        throw VsagException(ErrorType::READ_ERROR,
                            "IVF streaming serialization required block is missing");
    }
    if (this->use_reorder_ && !loaded_precise_codes) {
        throw VsagException(ErrorType::READ_ERROR,
                            "IVF streaming serialization reorder block is missing");
    }
    if (this->use_attribute_filter_ && !loaded_attribute_filter) {
        throw VsagException(ErrorType::READ_ERROR,
                            "IVF streaming serialization attribute filter block is missing");
    }
    if (this->bucket_->GetQuantizerName() == QUANTIZATION_TYPE_VALUE_FP32) {
        this->has_raw_vector_ = true;
    }
    this->fill_location_map();
    this->cal_memory_usage();
}
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L295 | metadata-&gt;Get | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L296 | basic_info["total_elements"].GetInt | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L297 | basic_info["use_reorder"].GetBool | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L298 | basic_info["is_trained"].GetBool | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L299 | basic_info.Contains | if_statement@299 (precise_bucket_ != nullptr and not basic_info.Contains(INDEX_PARAM)) | 当前参考未静态绑定；见下方边界说明 |

| L300 | VsagException | if_statement@299 (precise_bucket_ != nullptr and not basic_info.Contains(INDEX_PARAM)) | 当前参考未静态绑定；见下方边界说明 |

| L303 | basic_info.Contains | if_statement@303 (basic_info.Contains(INDEX_PARAM)) | 当前参考未静态绑定；见下方边界说明 |

| L304 | std::make_shared&lt;IVFParameter&gt; | if_statement@303 (basic_info.Contains(INDEX_PARAM)) | 当前参考未静态绑定；见下方边界说明 |

| L305 | index_param-&gt;FromString | if_statement@303 (basic_info.Contains(INDEX_PARAM)) | 当前参考未静态绑定；见下方边界说明 |

| L305 | basic_info[INDEX_PARAM].GetString | if_statement@303 (basic_info.Contains(INDEX_PARAM)) | 当前参考未静态绑定；见下方边界说明 |

| L306 | this-&gt;create_param_ptr_-&gt;CheckCompatibility | if_statement@303 (basic_info.Contains(INDEX_PARAM)) → if_statement@306 (not this-&gt;create_param_ptr_-&gt;CheckCompatibility(index_param)) | 当前参考未静态绑定；见下方边界说明 |

| L307 | fmt::format | if_statement@303 (basic_info.Contains(INDEX_PARAM)) → if_statement@306 (not this-&gt;create_param_ptr_-&gt;CheckCompatibility(index_param)) | 当前参考未静态绑定；见下方边界说明 |

| L308 | this-&gt;create_param_ptr_-&gt;ToString | if_statement@303 (basic_info.Contains(INDEX_PARAM)) → if_statement@306 (not this-&gt;create_param_ptr_-&gt;CheckCompatibility(index_param)) | 当前参考未静态绑定；见下方边界说明 |

| L309 | index_param-&gt;ToString | if_statement@303 (basic_info.Contains(INDEX_PARAM)) → if_statement@306 (not this-&gt;create_param_ptr_-&gt;CheckCompatibility(index_param)) | 当前参考未静态绑定；见下方边界说明 |

| L310 | logger::error | if_statement@303 (basic_info.Contains(INDEX_PARAM)) → if_statement@306 (not this-&gt;create_param_ptr_-&gt;CheckCompatibility(index_param)) | 当前参考未静态绑定；见下方边界说明 |

| L311 | VsagException | if_statement@303 (basic_info.Contains(INDEX_PARAM)) → if_statement@306 (not this-&gt;create_param_ptr_-&gt;CheckCompatibility(index_param)) | 当前参考未静态绑定；见下方边界说明 |

| L322 | std::dynamic_pointer_cast&lt;IVFParameter&gt; | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L325 | ivf_param-&gt;precise_codes_param-&gt;io_parameter-&gt;GetTypeName | if_statement@323 (ivf_param != nullptr && ivf_param-&gt;precise_codes_param != nullptr && ivf_param-&gt;precise_codes_param-&gt;io_parameter != nullptr && ivf_param-&gt;precise_codes_param-&gt;io_parameter-&gt;GetTypeName() == IO_TYPE_VALUE_READER_IO) | 当前参考未静态绑定；见下方边界说明 |

| L327 | load_parameters-&gt;HasReader | if_statement@323 (ivf_param != nullptr && ivf_param-&gt;precise_codes_param != nullptr && ivf_param-&gt;precise_codes_param-&gt;io_parameter != nullptr && ivf_param-&gt;precise_codes_param-&gt;io_parameter-&gt;GetTypeName() == IO_TYPE_VALUE_READER_IO) → if_statement@327 (load_parameters == nullptr or not load_parameters-&gt;HasReader(precise_reader_key)) | 当前参考未静态绑定；见下方边界说明 |

| L328 | VsagException | if_statement@323 (ivf_param != nullptr && ivf_param-&gt;precise_codes_param != nullptr && ivf_param-&gt;precise_codes_param-&gt;io_parameter != nullptr && ivf_param-&gt;precise_codes_param-&gt;io_parameter-&gt;GetTypeName() == IO_TYPE_VALUE_READER_IO) → if_statement@327 (load_parameters == nullptr or not load_parameters-&gt;HasReader(precise_reader_key)) | 当前参考未静态绑定；见下方边界说明 |

| L331 | load_parameters-&gt;GetReader | if_statement@323 (ivf_param != nullptr && ivf_param-&gt;precise_codes_param != nullptr && ivf_param-&gt;precise_codes_param-&gt;io_parameter != nullptr && ivf_param-&gt;precise_codes_param-&gt;io_parameter-&gt;GetTypeName() == IO_TYPE_VALUE_READER_IO) | 当前参考未静态绑定；见下方边界说明 |

| L333 | VsagException | if_statement@323 (ivf_param != nullptr && ivf_param-&gt;precise_codes_param != nullptr && ivf_param-&gt;precise_codes_param-&gt;io_parameter != nullptr && ivf_param-&gt;precise_codes_param-&gt;io_parameter-&gt;GetTypeName() == IO_TYPE_VALUE_READER_IO) → if_statement@332 (precise_reader == nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L335 | std::dynamic_pointer_cast&lt;ReaderIOParameter&gt; | if_statement@323 (ivf_param != nullptr && ivf_param-&gt;precise_codes_param != nullptr && ivf_param-&gt;precise_codes_param-&gt;io_parameter != nullptr && ivf_param-&gt;precise_codes_param-&gt;io_parameter-&gt;GetTypeName() == IO_TYPE_VALUE_READER_IO) | 当前参考未静态绑定；见下方边界说明 |

| L338 | VsagException | if_statement@323 (ivf_param != nullptr && ivf_param-&gt;precise_codes_param != nullptr && ivf_param-&gt;precise_codes_param-&gt;io_parameter != nullptr && ivf_param-&gt;precise_codes_param-&gt;io_parameter-&gt;GetTypeName() == IO_TYPE_VALUE_READER_IO) → if_statement@337 (precise_reader_param == nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L341 | std::move | if_statement@323 (ivf_param != nullptr && ivf_param-&gt;precise_codes_param != nullptr && ivf_param-&gt;precise_codes_param-&gt;io_parameter != nullptr && ivf_param-&gt;precise_codes_param-&gt;io_parameter-&gt;GetTypeName() == IO_TYPE_VALUE_READER_IO) | 当前参考未静态绑定；见下方边界说明 |

| L345 | StreamBlockHeader::Read | while_statement@344 (true) | 当前参考未静态绑定；见下方边界说明 |

| L346 | block_header.IsSectionEnd | while_statement@344 (true) → if_statement@346 (block_header.IsSectionEnd()) | 当前参考未静态绑定；见下方边界说明 |

| L350 | StreamSerializationBlockVersionSupported | while_statement@344 (true) → if_statement@350 (!StreamSerializationBlockVersionSupported(block_header.tag, block_header.block_version)) | 当前参考未静态绑定；见下方边界说明 |

| L352 | block_header.IsCritical | while_statement@344 (true) → if_statement@350 (!StreamSerializationBlockVersionSupported(block_header.tag, block_header.block_version)) → if_statement@352 (block_header.IsCritical()) | 当前参考未静态绑定；见下方边界说明 |

| L353 | VsagException | while_statement@344 (true) → if_statement@350 (!StreamSerializationBlockVersionSupported(block_header.tag, block_header.block_version)) → if_statement@352 (block_header.IsCritical()) | 当前参考未静态绑定；见下方边界说明 |

| L354 | fmt::format | while_statement@344 (true) → if_statement@350 (!StreamSerializationBlockVersionSupported(block_header.tag, block_header.block_version)) → if_statement@352 (block_header.IsCritical()) | 当前参考未静态绑定；见下方边界说明 |

| L357 | StreamSerializationTagName | while_statement@344 (true) → if_statement@350 (!StreamSerializationBlockVersionSupported(block_header.tag, block_header.block_version)) → if_statement@352 (block_header.IsCritical()) | 当前参考未静态绑定；见下方边界说明 |

| L362 | block_reader.SkipRemaining | while_statement@344 (true) → if_statement@350 (!StreamSerializationBlockVersionSupported(block_header.tag, block_header.block_version)) | 当前参考未静态绑定；见下方边界说明 |

| L368 | ReadSeekableBlockPayload | while_statement@344 (true) → lambda@366（定义体，执行时间取决于调用/调度） → if_statement@367 (precise_reader_param == nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L371 | block_reader.SkipRemaining | while_statement@344 (true) → lambda@366（定义体，执行时间取决于调用/调度） | 当前参考未静态绑定；见下方边界说明 |

| L372 | ReadExternalBlockPayload | while_statement@344 (true) → lambda@366（定义体，执行时间取决于调用/调度） | 当前参考未静态绑定；见下方边界说明 |

| L373 | init_io | while_statement@344 (true) → lambda@366（定义体，执行时间取决于调用/调度） | 当前参考未静态绑定；见下方边界说明 |

| L378 | ReadSeekableBlockPayload | while_statement@344 (true) → switch_statement@376 (static_cast&lt;StreamSerializationTag&gt;(block_header.tag)) | 当前参考未静态绑定；见下方边界说明 |

| L379 | this-&gt;bucket_-&gt;Deserialize | while_statement@344 (true) → switch_statement@376 (static_cast&lt;StreamSerializationTag&gt;(block_header.tag)) → lambda@378（定义体，执行时间取决于调用/调度） | [BucketDataCell&lt;QuantTmpl, IOTmpl&gt;::Deserialize · L898](bucket_datacell_h.md#L898) |

| L384 | ReadSeekableBlockPayload | while_statement@344 (true) → switch_statement@376 (static_cast&lt;StreamSerializationTag&gt;(block_header.tag)) | 当前参考未静态绑定；见下方边界说明 |

| L385 | this-&gt;partition_strategy_-&gt;Deserialize | while_statement@344 (true) → switch_statement@376 (static_cast&lt;StreamSerializationTag&gt;(block_header.tag)) → lambda@384（定义体，执行时间取决于调用/调度） | [GNOIMIPartition::Deserialize · L334](gno_imi_partition.md#L334)；[IVFNearestPartition::Deserialize · L239](ivf_nearest_partition.md#L239)；[IVFPartitionStrategy::Deserialize · L82](ivf_partition_strategy_h.md#L82) |

| L390 | ReadSeekableBlockPayload | while_statement@344 (true) → switch_statement@376 (static_cast&lt;StreamSerializationTag&gt;(block_header.tag)) | 当前参考未静态绑定；见下方边界说明 |

| L391 | this-&gt;label_table_-&gt;Deserialize | while_statement@344 (true) → switch_statement@376 (static_cast&lt;StreamSerializationTag&gt;(block_header.tag)) → lambda@390（定义体，执行时间取决于调用/调度） | 当前参考未静态绑定；见下方边界说明 |

| L397 | read_precise_block | while_statement@344 (true) → switch_statement@376 (static_cast&lt;StreamSerializationTag&gt;(block_header.tag)) → if_statement@396 (this-&gt;use_reorder_ and this-&gt;reorder_codes_ != nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L398 | this-&gt;reorder_codes_-&gt;Deserialize | while_statement@344 (true) → switch_statement@376 (static_cast&lt;StreamSerializationTag&gt;(block_header.tag)) → if_statement@396 (this-&gt;use_reorder_ and this-&gt;reorder_codes_ != nullptr) → lambda@398（定义体，执行时间取决于调用/调度） | [IVF::Deserialize · L526](ivf_serialize.md#L526) |

| L400 | this-&gt;reorder_codes_-&gt;InitIO | while_statement@344 (true) → switch_statement@376 (static_cast&lt;StreamSerializationTag&gt;(block_header.tag)) → if_statement@396 (this-&gt;use_reorder_ and this-&gt;reorder_codes_ != nullptr) → lambda@399（定义体，执行时间取决于调用/调度） | [BucketDataCell::InitIO · L158](bucket_datacell_h.md#L158) |

| L407 | read_precise_block | while_statement@344 (true) → switch_statement@376 (static_cast&lt;StreamSerializationTag&gt;(block_header.tag)) → if_statement@406 (this-&gt;use_reorder_ and this-&gt;precise_bucket_ != nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L408 | this-&gt;precise_bucket_-&gt;Deserialize | while_statement@344 (true) → switch_statement@376 (static_cast&lt;StreamSerializationTag&gt;(block_header.tag)) → if_statement@406 (this-&gt;use_reorder_ and this-&gt;precise_bucket_ != nullptr) → lambda@408（定义体，执行时间取决于调用/调度） | [BucketDataCell&lt;QuantTmpl, IOTmpl&gt;::Deserialize · L898](bucket_datacell_h.md#L898) |

| L410 | this-&gt;precise_bucket_-&gt;InitIO | while_statement@344 (true) → switch_statement@376 (static_cast&lt;StreamSerializationTag&gt;(block_header.tag)) → if_statement@406 (this-&gt;use_reorder_ and this-&gt;precise_bucket_ != nullptr) → lambda@409（定义体，执行时间取决于调用/调度） | [BucketDataCell::InitIO · L158](bucket_datacell_h.md#L158) |

| L417 | ReadSeekableBlockPayload | while_statement@344 (true) → switch_statement@376 (static_cast&lt;StreamSerializationTag&gt;(block_header.tag)) → if_statement@416 (this-&gt;use_attribute_filter_) | 当前参考未静态绑定；见下方边界说明 |

| L419 | this-&gt;attr_filter_index_-&gt;Deserialize | while_statement@344 (true) → switch_statement@376 (static_cast&lt;StreamSerializationTag&gt;(block_header.tag)) → if_statement@416 (this-&gt;use_attribute_filter_) → lambda@418（定义体，执行时间取决于调用/调度） | [IVF::Deserialize · L526](ivf_serialize.md#L526) |

| L426 | ReadSeekableBlockPayload | while_statement@344 (true) → switch_statement@376 (static_cast&lt;StreamSerializationTag&gt;(block_header.tag)) | 当前参考未静态绑定；见下方边界说明 |

| L427 | StreamReader::ReadObj | while_statement@344 (true) → switch_statement@376 (static_cast&lt;StreamSerializationTag&gt;(block_header.tag)) → lambda@426（定义体，执行时间取决于调用/调度） | 当前参考未静态绑定；见下方边界说明 |

| L428 | get_ivf_graph_param | while_statement@344 (true) → switch_statement@376 (static_cast&lt;StreamSerializationTag&gt;(block_header.tag)) → lambda@426（定义体，执行时间取决于调用/调度） | [get_ivf_graph_param · L38](ivf_serialize.md#L38) |

| L428 | StreamReader::ReadString | while_statement@344 (true) → switch_statement@376 (static_cast&lt;StreamSerializationTag&gt;(block_header.tag)) → lambda@426（定义体，执行时间取决于调用/调度） | 当前参考未静态绑定；见下方边界说明 |

| L430 | StreamReader::ReadObj | while_statement@344 (true) → switch_statement@376 (static_cast&lt;StreamSerializationTag&gt;(block_header.tag)) → lambda@426（定义体，执行时间取决于调用/调度） | 当前参考未静态绑定；见下方边界说明 |

| L433 | VsagException | while_statement@344 (true) → switch_statement@376 (static_cast&lt;StreamSerializationTag&gt;(block_header.tag)) → lambda@426（定义体，执行时间取决于调用/调度） → if_statement@432 (graph_count &gt; static_cast&lt;uint64_t&gt;(bucket_count)) | 当前参考未静态绑定；见下方边界说明 |

| L435 | fmt::format | while_statement@344 (true) → switch_statement@376 (static_cast&lt;StreamSerializationTag&gt;(block_header.tag)) → lambda@426（定义体，执行时间取决于调用/调度） → if_statement@432 (graph_count &gt; static_cast&lt;uint64_t&gt;(bucket_count)) | 当前参考未静态绑定；见下方边界说明 |

| L439 | this-&gt;bucket_graphs_.resize | while_statement@344 (true) → switch_statement@376 (static_cast&lt;StreamSerializationTag&gt;(block_header.tag)) → lambda@426（定义体，执行时间取决于调用/调度） | 当前参考未静态绑定；见下方边界说明 |

| L442 | StreamReader::ReadObj | while_statement@344 (true) → switch_statement@376 (static_cast&lt;StreamSerializationTag&gt;(block_header.tag)) → lambda@426（定义体，执行时间取决于调用/调度） → for_statement@440 i &lt; graph_count | 当前参考未静态绑定；见下方边界说明 |

| L445 | StreamReader::ReadObj | while_statement@344 (true) → switch_statement@376 (static_cast&lt;StreamSerializationTag&gt;(block_header.tag)) → lambda@426（定义体，执行时间取决于调用/调度） → for_statement@440 i &lt; graph_count → if_statement@443 (has_graph) | 当前参考未静态绑定；见下方边界说明 |

| L446 | GraphInterface::MakeInstance | while_statement@344 (true) → switch_statement@376 (static_cast&lt;StreamSerializationTag&gt;(block_header.tag)) → lambda@426（定义体，执行时间取决于调用/调度） → for_statement@440 i &lt; graph_count → if_statement@443 (has_graph) | 当前参考未静态绑定；见下方边界说明 |

| L448 | graph-&gt;Deserialize | while_statement@344 (true) → switch_statement@376 (static_cast&lt;StreamSerializationTag&gt;(block_header.tag)) → lambda@426（定义体，执行时间取决于调用/调度） → for_statement@440 i &lt; graph_count → if_statement@443 (has_graph) | 当前参考未静态绑定；见下方边界说明 |

| L450 | graph-&gt;TotalCount | while_statement@344 (true) → switch_statement@376 (static_cast&lt;StreamSerializationTag&gt;(block_header.tag)) → lambda@426（定义体，执行时间取决于调用/调度） → for_statement@440 i &lt; graph_count → if_statement@443 (has_graph) → if_statement@449 (bid &gt;= 0 && bid &lt; static_cast&lt;BucketIdType&gt;(bucket_count)) | 当前参考未静态绑定；见下方边界说明 |

| L451 | bucket_-&gt;GetBucketSize | while_statement@344 (true) → switch_statement@376 (static_cast&lt;StreamSerializationTag&gt;(block_header.tag)) → lambda@426（定义体，执行时间取决于调用/调度） → for_statement@440 i &lt; graph_count → if_statement@443 (has_graph) → if_statement@449 (bid &gt;= 0 && bid &lt; static_cast&lt;BucketIdType&gt;(bucket_count)) | [BucketDataCell::GetBucketSize · L180](bucket_datacell_h.md#L180) |

| L452 | graph-&gt;MaxCapacity | while_statement@344 (true) → switch_statement@376 (static_cast&lt;StreamSerializationTag&gt;(block_header.tag)) → lambda@426（定义体，执行时间取决于调用/调度） → for_statement@440 i &lt; graph_count → if_statement@443 (has_graph) → if_statement@449 (bid &gt;= 0 && bid &lt; static_cast&lt;BucketIdType&gt;(bucket_count)) → if_statement@452 (total != expected_total &#124;&#124; total &gt; graph-&gt;MaxCapacity()) | 当前参考未静态绑定；见下方边界说明 |

| L453 | VsagException | while_statement@344 (true) → switch_statement@376 (static_cast&lt;StreamSerializationTag&gt;(block_header.tag)) → lambda@426（定义体，执行时间取决于调用/调度） → for_statement@440 i &lt; graph_count → if_statement@443 (has_graph) → if_statement@449 (bid &gt;= 0 && bid &lt; static_cast&lt;BucketIdType&gt;(bucket_count)) → if_statement@452 (total != expected_total &#124;&#124; total &gt; graph-&gt;MaxCapacity()) | 当前参考未静态绑定；见下方边界说明 |

| L458 | graph-&gt;GetNeighborSize | while_statement@344 (true) → switch_statement@376 (static_cast&lt;StreamSerializationTag&gt;(block_header.tag)) → lambda@426（定义体，执行时间取决于调用/调度） → for_statement@440 i &lt; graph_count → if_statement@443 (has_graph) → if_statement@449 (bid &gt;= 0 && bid &lt; static_cast&lt;BucketIdType&gt;(bucket_count)) → for_statement@457 nid &lt; total → if_statement@458 (graph-&gt;GetNeighborSize(nid) &gt; graph-&gt;MaximumDegree()) | 当前参考未静态绑定；见下方边界说明 |

| L458 | graph-&gt;MaximumDegree | while_statement@344 (true) → switch_statement@376 (static_cast&lt;StreamSerializationTag&gt;(block_header.tag)) → lambda@426（定义体，执行时间取决于调用/调度） → for_statement@440 i &lt; graph_count → if_statement@443 (has_graph) → if_statement@449 (bid &gt;= 0 && bid &lt; static_cast&lt;BucketIdType&gt;(bucket_count)) → for_statement@457 nid &lt; total → if_statement@458 (graph-&gt;GetNeighborSize(nid) &gt; graph-&gt;MaximumDegree()) | 当前参考未静态绑定；见下方边界说明 |

| L459 | VsagException | while_statement@344 (true) → switch_statement@376 (static_cast&lt;StreamSerializationTag&gt;(block_header.tag)) → lambda@426（定义体，执行时间取决于调用/调度） → for_statement@440 i &lt; graph_count → if_statement@443 (has_graph) → if_statement@449 (bid &gt;= 0 && bid &lt; static_cast&lt;BucketIdType&gt;(bucket_count)) → for_statement@457 nid &lt; total → if_statement@458 (graph-&gt;GetNeighborSize(nid) &gt; graph-&gt;MaximumDegree()) | 当前参考未静态绑定；见下方边界说明 |

| L464 | graph-&gt;GetNeighbors | while_statement@344 (true) → switch_statement@376 (static_cast&lt;StreamSerializationTag&gt;(block_header.tag)) → lambda@426（定义体，执行时间取决于调用/调度） → for_statement@440 i &lt; graph_count → if_statement@443 (has_graph) → if_statement@449 (bid &gt;= 0 && bid &lt; static_cast&lt;BucketIdType&gt;(bucket_count)) → for_statement@457 nid &lt; total | 当前参考未静态绑定；见下方边界说明 |

| L467 | VsagException | while_statement@344 (true) → switch_statement@376 (static_cast&lt;StreamSerializationTag&gt;(block_header.tag)) → lambda@426（定义体，执行时间取决于调用/调度） → for_statement@440 i &lt; graph_count → if_statement@443 (has_graph) → if_statement@449 (bid &gt;= 0 && bid &lt; static_cast&lt;BucketIdType&gt;(bucket_count)) → for_statement@457 nid &lt; total → for_range_loop@465 → if_statement@466 (nb &gt;= total) | 当前参考未静态绑定；见下方边界说明 |

| L473 | std::move | while_statement@344 (true) → switch_statement@376 (static_cast&lt;StreamSerializationTag&gt;(block_header.tag)) → lambda@426（定义体，执行时间取决于调用/调度） → for_statement@440 i &lt; graph_count → if_statement@443 (has_graph) → if_statement@449 (bid &gt;= 0 && bid &lt; static_cast&lt;BucketIdType&gt;(bucket_count)) | 当前参考未静态绑定；见下方边界说明 |

| L480 | std::make_shared&lt;GraphBucketSearcher&gt; | while_statement@344 (true) → switch_statement@376 (static_cast&lt;StreamSerializationTag&gt;(block_header.tag)) → if_statement@478 (graph_build_threshold_ &gt; 0 && this-&gt;bucket_searcher_ != nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L486 | block_header.IsCritical | while_statement@344 (true) → switch_statement@376 (static_cast&lt;StreamSerializationTag&gt;(block_header.tag)) → if_statement@486 (block_header.IsCritical()) | 当前参考未静态绑定；见下方边界说明 |

| L487 | VsagException | while_statement@344 (true) → switch_statement@376 (static_cast&lt;StreamSerializationTag&gt;(block_header.tag)) → if_statement@486 (block_header.IsCritical()) | 当前参考未静态绑定；见下方边界说明 |

| L488 | fmt::format | while_statement@344 (true) → switch_statement@376 (static_cast&lt;StreamSerializationTag&gt;(block_header.tag)) → if_statement@486 (block_header.IsCritical()) | 当前参考未静态绑定；见下方边界说明 |

| L492 | StreamSerializationTagName | while_statement@344 (true) → switch_statement@376 (static_cast&lt;StreamSerializationTag&gt;(block_header.tag)) → if_statement@486 (block_header.IsCritical()) | 当前参考未静态绑定；见下方边界说明 |

| L499 | block_reader.SkipRemaining | while_statement@344 (true) | 当前参考未静态绑定；见下方边界说明 |

| L503 | VsagException | if_statement@502 (!loaded_bucket &#124;&#124; !loaded_partition &#124;&#124; !loaded_label_table) | 当前参考未静态绑定；见下方边界说明 |

| L507 | VsagException | if_statement@506 (this-&gt;use_reorder_ && !loaded_precise_codes) | 当前参考未静态绑定；见下方边界说明 |

| L511 | VsagException | if_statement@510 (this-&gt;use_attribute_filter_ && !loaded_attribute_filter) | 当前参考未静态绑定；见下方边界说明 |

| L514 | this-&gt;bucket_-&gt;GetQuantizerName | if_statement@514 (this-&gt;bucket_-&gt;GetQuantizerName() == QUANTIZATION_TYPE_VALUE_FP32) | [BucketDataCell::GetQuantizerName · L170](bucket_datacell_h.md#L170) |

| L517 | this-&gt;fill_location_map | 函数本体；短路求值/提前返回见源码 | [IVF::fill_location_map · L405](ivf_build.md#L405) |

| L518 | this-&gt;cal_memory_usage | 函数本体；短路求值/提前返回见源码 | [IVF::cal_memory_usage · L616](ivf.md#L616) |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L526"></a>

## `IVF::Deserialize`

源码位置：`src/algorithm/ivf/ivf_serialize.cpp:526–661`。

先从签名确认输入、返回值和 const/override，再按完整函数体的条件阅读调用点。下表保留了本函数的显式调用以及 lambda 中的调用；进入下层时用“候选实现”定位，未解析的对象由源码静态类型/运行时类型确认。

### 完整函数

```cpp
void
IVF::Deserialize(StreamReader& reader) {
    // try to deserialize footer (only in new version)
    auto footer = Footer::Parse(reader);

    BufferStreamReader buffer_reader(
        &reader, std::numeric_limits<uint64_t>::max(), this->allocator_);

    if (footer == nullptr) {  // old format, DON'T EDIT, remove in the future
        if (precise_bucket_ != nullptr) {
            throw VsagException(ErrorType::UNSUPPORTED_INDEX_OPERATION,
                                "legacy IVF serialization does not support precise bucket");
        }
        logger::debug("parse with v0.14 version format");

        StreamReader::ReadObj(buffer_reader, this->total_elements_);
        StreamReader::ReadObj(buffer_reader, this->use_reorder_);
        StreamReader::ReadObj(buffer_reader, this->is_trained_);

        this->bucket_->Deserialize(buffer_reader);
        this->partition_strategy_->Deserialize(buffer_reader);
        this->label_table_->Deserialize(buffer_reader);
        if (use_reorder_) {
            this->reorder_codes_->Deserialize(buffer_reader);
        }

        if (use_attribute_filter_) {
            this->attr_filter_index_->Deserialize(buffer_reader);
            this->has_attribute_ = true;
        }
    } else {  // create like `else if ( ver in [v0.15, v0.17] )` here if need in the future
        logger::debug("parse with new version format");

        auto metadata = footer->GetMetadata();
        if (metadata->EmptyIndex()) {
            return;
        }

        auto basic_info = metadata->Get(BASIC_INFO);
        this->total_elements_ = basic_info["total_elements"].GetInt();
        this->use_reorder_ = basic_info["use_reorder"].GetBool();
        this->is_trained_ = basic_info["is_trained"].GetBool();
        if (precise_bucket_ != nullptr and not basic_info.Contains(INDEX_PARAM)) {
            throw VsagException(ErrorType::UNSUPPORTED_INDEX_OPERATION,
                                "IVF precise bucket requires persisted index parameters");
        }
        if (basic_info.Contains(INDEX_PARAM)) {
            auto param_str = basic_info[INDEX_PARAM].GetString();
            auto index_param = std::make_shared<IVFParameter>();
            index_param->FromString(param_str);
            if (not this->create_param_ptr_->CheckCompatibility(index_param)) {
                auto message = fmt::format("IVF index parameter not match, current: {}, new: {}",
                                           this->create_param_ptr_->ToString(),
                                           index_param->ToString());
                logger::error(message);
                throw VsagException(ErrorType::INVALID_ARGUMENT, message);
            }
        }

        JsonType datacell_offsets = metadata->Get(DATACELL_OFFSETS);
        logger::debug("datacell_offsets: {}", datacell_offsets.Dump());
        JsonType datacell_sizes = metadata->Get(DATACELL_SIZES);
        logger::debug("datacell_sizes: {}", datacell_sizes.Dump());

        READ_DATACELL_WITH_NAME(buffer_reader, "bucket", this->bucket_);
        READ_DATACELL_WITH_NAME(buffer_reader, "partition_strategy", this->partition_strategy_);
        READ_DATACELL_WITH_NAME(buffer_reader, "label_table", this->label_table_);
        if (use_reorder_) {
            if (precise_bucket_ != nullptr) {
                READ_DATACELL_WITH_NAME(buffer_reader, "precise_bucket", this->precise_bucket_);
            } else {
                READ_DATACELL_WITH_NAME(buffer_reader, "reorder_codes", this->reorder_codes_);
            }
        }
        if (use_attribute_filter_) {
            READ_DATACELL_WITH_NAME(buffer_reader, "attr_filter_index", this->attr_filter_index_);
            this->has_attribute_ = true;
        }
        if (this->bucket_->GetQuantizerName() == QUANTIZATION_TYPE_VALUE_FP32) {
            this->has_raw_vector_ = true;
        }

        if (datacell_offsets.Contains("bucket_graphs")) {
            auto bucket_count = bucket_->bucket_count_;
            bucket_graphs_.resize(bucket_count);
            buffer_reader.PushSeek(datacell_offsets["bucket_graphs"].GetInt());
            auto graph_reader = buffer_reader.Slice(datacell_sizes["bucket_graphs"].GetInt());
            int64_t stored_threshold = 0;
            StreamReader::ReadObj(graph_reader, stored_threshold);
            graph_build_threshold_ = stored_threshold;
            graph_param_ = get_ivf_graph_param(StreamReader::ReadString(graph_reader));
            int64_t graph_count = 0;
            StreamReader::ReadObj(graph_reader, graph_count);
            CHECK_ARGUMENT(graph_count >= 0, "bucket graph_count is negative");
            CHECK_ARGUMENT(graph_count <= bucket_count, "bucket graph_count exceeds bucket_count");
            for (int64_t g = 0; g < graph_count; ++g) {
                BucketIdType bid = 0;
                StreamReader::ReadObj(graph_reader, bid);
                auto graph = GraphInterface::MakeInstance(graph_param_, this->common_param_);
                graph->Deserialize(graph_reader);
                if (bid >= 0 && bid < bucket_count) {
                    const auto total = graph->TotalCount();
                    const auto expected_total = bucket_->GetBucketSize(bid);
                    if (total != expected_total || total > graph->MaxCapacity()) {
                        throw VsagException(ErrorType::INVALID_BINARY,
                                            "corrupt bucket graph: invalid total count");
                    }
                    for (InnerIdType nid = 0; nid < total; ++nid) {
                        if (graph->GetNeighborSize(nid) > graph->MaximumDegree()) {
                            throw VsagException(
                                ErrorType::INVALID_BINARY,
                                "corrupt bucket graph: neighbor count exceeds maximum degree");
                        }
                        Vector<InnerIdType> nbrs(allocator_);
                        graph->GetNeighbors(nid, nbrs);
                        for (auto nb : nbrs) {
                            if (nb >= total) {
                                throw VsagException(
                                    ErrorType::INVALID_BINARY,
                                    "corrupt bucket graph: neighbor ID out of range");
                            }
                        }
                    }
                    bucket_graphs_[bid] = std::move(graph);
                }
            }
            buffer_reader.PopSeek();
            if (graph_build_threshold_ > 0) {
                this->bucket_searcher_ = std::make_shared<GraphBucketSearcher>(
                    graph_build_threshold_, bucket_graphs_, allocator_);
            }
        }
    }
    this->fill_location_map();
    this->cal_memory_usage();
}
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L529 | Footer::Parse | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L532 | std::numeric_limits&lt;uint64_t&gt;::max | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L536 | VsagException | if_statement@534 (footer == nullptr) → if_statement@535 (precise_bucket_ != nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L539 | logger::debug | if_statement@534 (footer == nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L541 | StreamReader::ReadObj | if_statement@534 (footer == nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L542 | StreamReader::ReadObj | if_statement@534 (footer == nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L543 | StreamReader::ReadObj | if_statement@534 (footer == nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L545 | this-&gt;bucket_-&gt;Deserialize | if_statement@534 (footer == nullptr) | [BucketDataCell&lt;QuantTmpl, IOTmpl&gt;::Deserialize · L898](bucket_datacell_h.md#L898) |

| L546 | this-&gt;partition_strategy_-&gt;Deserialize | if_statement@534 (footer == nullptr) | [GNOIMIPartition::Deserialize · L334](gno_imi_partition.md#L334)；[IVFNearestPartition::Deserialize · L239](ivf_nearest_partition.md#L239)；[IVFPartitionStrategy::Deserialize · L82](ivf_partition_strategy_h.md#L82) |

| L547 | this-&gt;label_table_-&gt;Deserialize | if_statement@534 (footer == nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L549 | this-&gt;reorder_codes_-&gt;Deserialize | if_statement@534 (footer == nullptr) → if_statement@548 (use_reorder_) | [IVF::Deserialize · L526](ivf_serialize.md#L526) |

| L553 | this-&gt;attr_filter_index_-&gt;Deserialize | if_statement@534 (footer == nullptr) → if_statement@552 (use_attribute_filter_) | [IVF::Deserialize · L526](ivf_serialize.md#L526) |

| L557 | logger::debug | if_statement@534 (footer == nullptr) [else 分支] | 当前参考未静态绑定；见下方边界说明 |

| L559 | footer-&gt;GetMetadata | if_statement@534 (footer == nullptr) [else 分支] | 当前参考未静态绑定；见下方边界说明 |

| L560 | metadata-&gt;EmptyIndex | if_statement@534 (footer == nullptr) [else 分支] → if_statement@560 (metadata-&gt;EmptyIndex()) | 当前参考未静态绑定；见下方边界说明 |

| L564 | metadata-&gt;Get | if_statement@534 (footer == nullptr) [else 分支] | 当前参考未静态绑定；见下方边界说明 |

| L565 | basic_info["total_elements"].GetInt | if_statement@534 (footer == nullptr) [else 分支] | 当前参考未静态绑定；见下方边界说明 |

| L566 | basic_info["use_reorder"].GetBool | if_statement@534 (footer == nullptr) [else 分支] | 当前参考未静态绑定；见下方边界说明 |

| L567 | basic_info["is_trained"].GetBool | if_statement@534 (footer == nullptr) [else 分支] | 当前参考未静态绑定；见下方边界说明 |

| L568 | basic_info.Contains | if_statement@534 (footer == nullptr) [else 分支] → if_statement@568 (precise_bucket_ != nullptr and not basic_info.Contains(INDEX_PARAM)) | 当前参考未静态绑定；见下方边界说明 |

| L569 | VsagException | if_statement@534 (footer == nullptr) [else 分支] → if_statement@568 (precise_bucket_ != nullptr and not basic_info.Contains(INDEX_PARAM)) | 当前参考未静态绑定；见下方边界说明 |

| L572 | basic_info.Contains | if_statement@534 (footer == nullptr) [else 分支] → if_statement@572 (basic_info.Contains(INDEX_PARAM)) | 当前参考未静态绑定；见下方边界说明 |

| L573 | basic_info[INDEX_PARAM].GetString | if_statement@534 (footer == nullptr) [else 分支] → if_statement@572 (basic_info.Contains(INDEX_PARAM)) | 当前参考未静态绑定；见下方边界说明 |

| L574 | std::make_shared&lt;IVFParameter&gt; | if_statement@534 (footer == nullptr) [else 分支] → if_statement@572 (basic_info.Contains(INDEX_PARAM)) | 当前参考未静态绑定；见下方边界说明 |

| L575 | index_param-&gt;FromString | if_statement@534 (footer == nullptr) [else 分支] → if_statement@572 (basic_info.Contains(INDEX_PARAM)) | 当前参考未静态绑定；见下方边界说明 |

| L576 | this-&gt;create_param_ptr_-&gt;CheckCompatibility | if_statement@534 (footer == nullptr) [else 分支] → if_statement@572 (basic_info.Contains(INDEX_PARAM)) → if_statement@576 (not this-&gt;create_param_ptr_-&gt;CheckCompatibility(index_param)) | 当前参考未静态绑定；见下方边界说明 |

| L577 | fmt::format | if_statement@534 (footer == nullptr) [else 分支] → if_statement@572 (basic_info.Contains(INDEX_PARAM)) → if_statement@576 (not this-&gt;create_param_ptr_-&gt;CheckCompatibility(index_param)) | 当前参考未静态绑定；见下方边界说明 |

| L578 | this-&gt;create_param_ptr_-&gt;ToString | if_statement@534 (footer == nullptr) [else 分支] → if_statement@572 (basic_info.Contains(INDEX_PARAM)) → if_statement@576 (not this-&gt;create_param_ptr_-&gt;CheckCompatibility(index_param)) | 当前参考未静态绑定；见下方边界说明 |

| L579 | index_param-&gt;ToString | if_statement@534 (footer == nullptr) [else 分支] → if_statement@572 (basic_info.Contains(INDEX_PARAM)) → if_statement@576 (not this-&gt;create_param_ptr_-&gt;CheckCompatibility(index_param)) | 当前参考未静态绑定；见下方边界说明 |

| L580 | logger::error | if_statement@534 (footer == nullptr) [else 分支] → if_statement@572 (basic_info.Contains(INDEX_PARAM)) → if_statement@576 (not this-&gt;create_param_ptr_-&gt;CheckCompatibility(index_param)) | 当前参考未静态绑定；见下方边界说明 |

| L581 | VsagException | if_statement@534 (footer == nullptr) [else 分支] → if_statement@572 (basic_info.Contains(INDEX_PARAM)) → if_statement@576 (not this-&gt;create_param_ptr_-&gt;CheckCompatibility(index_param)) | 当前参考未静态绑定；见下方边界说明 |

| L585 | metadata-&gt;Get | if_statement@534 (footer == nullptr) [else 分支] | 当前参考未静态绑定；见下方边界说明 |

| L586 | logger::debug | if_statement@534 (footer == nullptr) [else 分支] | 当前参考未静态绑定；见下方边界说明 |

| L586 | datacell_offsets.Dump | if_statement@534 (footer == nullptr) [else 分支] | 当前参考未静态绑定；见下方边界说明 |

| L587 | metadata-&gt;Get | if_statement@534 (footer == nullptr) [else 分支] | 当前参考未静态绑定；见下方边界说明 |

| L588 | logger::debug | if_statement@534 (footer == nullptr) [else 分支] | 当前参考未静态绑定；见下方边界说明 |

| L588 | datacell_sizes.Dump | if_statement@534 (footer == nullptr) [else 分支] | 当前参考未静态绑定；见下方边界说明 |

| L590 | READ_DATACELL_WITH_NAME | if_statement@534 (footer == nullptr) [else 分支] | 当前参考未静态绑定；见下方边界说明 |

| L591 | READ_DATACELL_WITH_NAME | if_statement@534 (footer == nullptr) [else 分支] | 当前参考未静态绑定；见下方边界说明 |

| L592 | READ_DATACELL_WITH_NAME | if_statement@534 (footer == nullptr) [else 分支] | 当前参考未静态绑定；见下方边界说明 |

| L595 | READ_DATACELL_WITH_NAME | if_statement@534 (footer == nullptr) [else 分支] → if_statement@593 (use_reorder_) → if_statement@594 (precise_bucket_ != nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L597 | READ_DATACELL_WITH_NAME | if_statement@534 (footer == nullptr) [else 分支] → if_statement@593 (use_reorder_) → if_statement@594 (precise_bucket_ != nullptr) [else 分支] | 当前参考未静态绑定；见下方边界说明 |

| L601 | READ_DATACELL_WITH_NAME | if_statement@534 (footer == nullptr) [else 分支] → if_statement@600 (use_attribute_filter_) | 当前参考未静态绑定；见下方边界说明 |

| L604 | this-&gt;bucket_-&gt;GetQuantizerName | if_statement@534 (footer == nullptr) [else 分支] → if_statement@604 (this-&gt;bucket_-&gt;GetQuantizerName() == QUANTIZATION_TYPE_VALUE_FP32) | [BucketDataCell::GetQuantizerName · L170](bucket_datacell_h.md#L170) |

| L608 | datacell_offsets.Contains | if_statement@534 (footer == nullptr) [else 分支] → if_statement@608 (datacell_offsets.Contains("bucket_graphs")) | 当前参考未静态绑定；见下方边界说明 |

| L610 | bucket_graphs_.resize | if_statement@534 (footer == nullptr) [else 分支] → if_statement@608 (datacell_offsets.Contains("bucket_graphs")) | 当前参考未静态绑定；见下方边界说明 |

| L611 | buffer_reader.PushSeek | if_statement@534 (footer == nullptr) [else 分支] → if_statement@608 (datacell_offsets.Contains("bucket_graphs")) | 当前参考未静态绑定；见下方边界说明 |

| L611 | datacell_offsets["bucket_graphs"].GetInt | if_statement@534 (footer == nullptr) [else 分支] → if_statement@608 (datacell_offsets.Contains("bucket_graphs")) | 当前参考未静态绑定；见下方边界说明 |

| L612 | buffer_reader.Slice | if_statement@534 (footer == nullptr) [else 分支] → if_statement@608 (datacell_offsets.Contains("bucket_graphs")) | 当前参考未静态绑定；见下方边界说明 |

| L612 | datacell_sizes["bucket_graphs"].GetInt | if_statement@534 (footer == nullptr) [else 分支] → if_statement@608 (datacell_offsets.Contains("bucket_graphs")) | 当前参考未静态绑定；见下方边界说明 |

| L614 | StreamReader::ReadObj | if_statement@534 (footer == nullptr) [else 分支] → if_statement@608 (datacell_offsets.Contains("bucket_graphs")) | 当前参考未静态绑定；见下方边界说明 |

| L616 | get_ivf_graph_param | if_statement@534 (footer == nullptr) [else 分支] → if_statement@608 (datacell_offsets.Contains("bucket_graphs")) | [get_ivf_graph_param · L38](ivf_serialize.md#L38) |

| L616 | StreamReader::ReadString | if_statement@534 (footer == nullptr) [else 分支] → if_statement@608 (datacell_offsets.Contains("bucket_graphs")) | 当前参考未静态绑定；见下方边界说明 |

| L618 | StreamReader::ReadObj | if_statement@534 (footer == nullptr) [else 分支] → if_statement@608 (datacell_offsets.Contains("bucket_graphs")) | 当前参考未静态绑定；见下方边界说明 |

| L619 | CHECK_ARGUMENT | if_statement@534 (footer == nullptr) [else 分支] → if_statement@608 (datacell_offsets.Contains("bucket_graphs")) | 当前参考未静态绑定；见下方边界说明 |

| L620 | CHECK_ARGUMENT | if_statement@534 (footer == nullptr) [else 分支] → if_statement@608 (datacell_offsets.Contains("bucket_graphs")) | 当前参考未静态绑定；见下方边界说明 |

| L623 | StreamReader::ReadObj | if_statement@534 (footer == nullptr) [else 分支] → if_statement@608 (datacell_offsets.Contains("bucket_graphs")) → for_statement@621 g &lt; graph_count | 当前参考未静态绑定；见下方边界说明 |

| L624 | GraphInterface::MakeInstance | if_statement@534 (footer == nullptr) [else 分支] → if_statement@608 (datacell_offsets.Contains("bucket_graphs")) → for_statement@621 g &lt; graph_count | 当前参考未静态绑定；见下方边界说明 |

| L625 | graph-&gt;Deserialize | if_statement@534 (footer == nullptr) [else 分支] → if_statement@608 (datacell_offsets.Contains("bucket_graphs")) → for_statement@621 g &lt; graph_count | 当前参考未静态绑定；见下方边界说明 |

| L627 | graph-&gt;TotalCount | if_statement@534 (footer == nullptr) [else 分支] → if_statement@608 (datacell_offsets.Contains("bucket_graphs")) → for_statement@621 g &lt; graph_count → if_statement@626 (bid &gt;= 0 && bid &lt; bucket_count) | 当前参考未静态绑定；见下方边界说明 |

| L628 | bucket_-&gt;GetBucketSize | if_statement@534 (footer == nullptr) [else 分支] → if_statement@608 (datacell_offsets.Contains("bucket_graphs")) → for_statement@621 g &lt; graph_count → if_statement@626 (bid &gt;= 0 && bid &lt; bucket_count) | [BucketDataCell::GetBucketSize · L180](bucket_datacell_h.md#L180) |

| L629 | graph-&gt;MaxCapacity | if_statement@534 (footer == nullptr) [else 分支] → if_statement@608 (datacell_offsets.Contains("bucket_graphs")) → for_statement@621 g &lt; graph_count → if_statement@626 (bid &gt;= 0 && bid &lt; bucket_count) → if_statement@629 (total != expected_total &#124;&#124; total &gt; graph-&gt;MaxCapacity()) | 当前参考未静态绑定；见下方边界说明 |

| L630 | VsagException | if_statement@534 (footer == nullptr) [else 分支] → if_statement@608 (datacell_offsets.Contains("bucket_graphs")) → for_statement@621 g &lt; graph_count → if_statement@626 (bid &gt;= 0 && bid &lt; bucket_count) → if_statement@629 (total != expected_total &#124;&#124; total &gt; graph-&gt;MaxCapacity()) | 当前参考未静态绑定；见下方边界说明 |

| L634 | graph-&gt;GetNeighborSize | if_statement@534 (footer == nullptr) [else 分支] → if_statement@608 (datacell_offsets.Contains("bucket_graphs")) → for_statement@621 g &lt; graph_count → if_statement@626 (bid &gt;= 0 && bid &lt; bucket_count) → for_statement@633 nid &lt; total → if_statement@634 (graph-&gt;GetNeighborSize(nid) &gt; graph-&gt;MaximumDegree()) | 当前参考未静态绑定；见下方边界说明 |

| L634 | graph-&gt;MaximumDegree | if_statement@534 (footer == nullptr) [else 分支] → if_statement@608 (datacell_offsets.Contains("bucket_graphs")) → for_statement@621 g &lt; graph_count → if_statement@626 (bid &gt;= 0 && bid &lt; bucket_count) → for_statement@633 nid &lt; total → if_statement@634 (graph-&gt;GetNeighborSize(nid) &gt; graph-&gt;MaximumDegree()) | 当前参考未静态绑定；见下方边界说明 |

| L635 | VsagException | if_statement@534 (footer == nullptr) [else 分支] → if_statement@608 (datacell_offsets.Contains("bucket_graphs")) → for_statement@621 g &lt; graph_count → if_statement@626 (bid &gt;= 0 && bid &lt; bucket_count) → for_statement@633 nid &lt; total → if_statement@634 (graph-&gt;GetNeighborSize(nid) &gt; graph-&gt;MaximumDegree()) | 当前参考未静态绑定；见下方边界说明 |

| L640 | graph-&gt;GetNeighbors | if_statement@534 (footer == nullptr) [else 分支] → if_statement@608 (datacell_offsets.Contains("bucket_graphs")) → for_statement@621 g &lt; graph_count → if_statement@626 (bid &gt;= 0 && bid &lt; bucket_count) → for_statement@633 nid &lt; total | 当前参考未静态绑定；见下方边界说明 |

| L643 | VsagException | if_statement@534 (footer == nullptr) [else 分支] → if_statement@608 (datacell_offsets.Contains("bucket_graphs")) → for_statement@621 g &lt; graph_count → if_statement@626 (bid &gt;= 0 && bid &lt; bucket_count) → for_statement@633 nid &lt; total → for_range_loop@641 → if_statement@642 (nb &gt;= total) | 当前参考未静态绑定；见下方边界说明 |

| L649 | std::move | if_statement@534 (footer == nullptr) [else 分支] → if_statement@608 (datacell_offsets.Contains("bucket_graphs")) → for_statement@621 g &lt; graph_count → if_statement@626 (bid &gt;= 0 && bid &lt; bucket_count) | 当前参考未静态绑定；见下方边界说明 |

| L652 | buffer_reader.PopSeek | if_statement@534 (footer == nullptr) [else 分支] → if_statement@608 (datacell_offsets.Contains("bucket_graphs")) | 当前参考未静态绑定；见下方边界说明 |

| L654 | std::make_shared&lt;GraphBucketSearcher&gt; | if_statement@534 (footer == nullptr) [else 分支] → if_statement@608 (datacell_offsets.Contains("bucket_graphs")) → if_statement@653 (graph_build_threshold_ &gt; 0) | 当前参考未静态绑定；见下方边界说明 |

| L659 | this-&gt;fill_location_map | 函数本体；短路求值/提前返回见源码 | [IVF::fill_location_map · L405](ivf_build.md#L405) |

| L660 | this-&gt;cal_memory_usage | 函数本体；短路求值/提前返回见源码 | [IVF::cal_memory_usage · L616](ivf.md#L616) |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。
