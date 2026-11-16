# bucket_datacell.h：逐函数完整源码与调用点

[主讲解](../code_walkthrough.md) · [函数总目录](README.md)

源码：[ src/datacell/bucket_datacell.h ](../../../../src/datacell/bucket_datacell.h)。基线 `fd363937`。以下源码函数体完整保留；调用点表是语法树中的显式调用表达式，按源码位置排列，不代表 C++ 参数求值顺序。表中“候选实现”需结合类型和参数选分支，不能将同名函数全部视为必经路径。

- [AdjustBucketReadCacheParam · L36](bucket_datacell_h.md#L36)

- [BucketDataCell::ScanBucketById · L63](bucket_datacell_h.md#L63)

- [BucketDataCell::QueryOneById · L71](bucket_datacell_h.md#L71)

- [BucketDataCell::Query · L82](bucket_datacell_h.md#L82)

- [BucketDataCell::GetInnerIds · L120](bucket_datacell_h.md#L120)

- [BucketDataCell::Prefetch · L126](bucket_datacell_h.md#L126)

- [BucketDataCell::Package · L132](bucket_datacell_h.md#L132)

- [BucketDataCell::Unpack · L139](bucket_datacell_h.md#L139)

- [BucketDataCell::InitIO · L158](bucket_datacell_h.md#L158)

- [BucketDataCell::GetQuantizerName · L170](bucket_datacell_h.md#L170)

- [BucketDataCell::GetMetricType · L175](bucket_datacell_h.md#L175)

- [BucketDataCell::GetBucketSize · L180](bucket_datacell_h.md#L180)

- [BucketDataCell::GetMemoryUsage · L189](bucket_datacell_h.md#L189)

- [BucketDataCell::init_shared_read_cache_io · L202](bucket_datacell_h.md#L202)

- [BucketDataCell::get_page_count · L238](bucket_datacell_h.md#L238)

- [BucketDataCell::check_valid_bucket_id · L244](bucket_datacell_h.md#L244)

- [BucketDataCell&lt;QuantTmpl, IOTmpl&gt;::BucketDataCell · L312](bucket_datacell_h.md#L312)

- [BucketDataCell&lt;QuantTmpl, IOTmpl&gt;::query_one_by_id · L341](bucket_datacell_h.md#L341)

- [BucketDataCell&lt;QuantTmpl, IOTmpl&gt;::query · L380](bucket_datacell_h.md#L380)

- [BucketDataCell&lt;QuantTmpl, IOTmpl&gt;::scan_bucket_by_id · L522](bucket_datacell_h.md#L522)

- [BucketDataCell&lt;QuantTmpl, IOTmpl&gt;::FactoryComputer · L566](bucket_datacell_h.md#L566)

- [BucketDataCell&lt;QuantTmpl, IOTmpl&gt;::Train · L586](bucket_datacell_h.md#L586)

- [BucketDataCell&lt;QuantTmpl, IOTmpl&gt;::encode_vector · L613](bucket_datacell_h.md#L613)

- [BucketDataCell&lt;QuantTmpl, IOTmpl&gt;::check_valid_bucket_capacity · L645](bucket_datacell_h.md#L645)

- [BucketDataCell&lt;QuantTmpl, IOTmpl&gt;::InsertVector · L660](bucket_datacell_h.md#L660)

- [BucketDataCell&lt;QuantTmpl, IOTmpl&gt;::BatchInsertVector · L703](bucket_datacell_h.md#L703)

- [BucketDataCell&lt;QuantTmpl, IOTmpl&gt;::InsertVectorWithOffset · L818](bucket_datacell_h.md#L818)

- [BucketDataCell&lt;QuantTmpl, IOTmpl&gt;::Serialize · L883](bucket_datacell_h.md#L883)

- [BucketDataCell&lt;QuantTmpl, IOTmpl&gt;::Deserialize · L898](bucket_datacell_h.md#L898)

- [BucketDataCell&lt;QuantTmpl, IOTmpl&gt;::package_fastscan · L934](bucket_datacell_h.md#L934)

- [BucketDataCell&lt;QuantTmpl, IOTmpl&gt;::unpack_fastscan · L958](bucket_datacell_h.md#L958)

- [BucketDataCell&lt;QuantTmpl, IOTmpl&gt;::ExportModel · L979](bucket_datacell_h.md#L979)

- [BucketDataCell&lt;QuantTmpl, IOTmpl&gt;::MergeOther · L994](bucket_datacell_h.md#L994)

- [BucketDataCell&lt;QuantTmpl, IOTmpl&gt;::GetCodesById · L1017](bucket_datacell_h.md#L1017)

- [BucketDataCell&lt;QuantTmpl, IOTmpl&gt;::ComputePairVectors · L1035](bucket_datacell_h.md#L1035)


<a id="L36"></a>

## `AdjustBucketReadCacheParam`

源码位置：`src/datacell/bucket_datacell.h:36–52`。

先从签名确认输入、返回值和 const/override，再按完整函数体的条件阅读调用点。下表保留了本函数的显式调用以及 lambda 中的调用；进入下层时用“候选实现”定位，未解析的对象由源码静态类型/运行时类型确认。

### 完整函数

```cpp
inline IOParamPtr
AdjustBucketReadCacheParam(const IOParamPtr& io_param, BucketIdType bucket_count) {
    if (io_param == nullptr or not io_param->enable_read_cache_ or bucket_count == 0) {
        return io_param;
    }
    JsonType json = io_param->ToJson();
    uint64_t total_pages = io_param->read_cache_total_size_ / Page::DEFAULT_PAGE_SIZE;
    uint64_t pages_per_bucket = total_pages / bucket_count;
    json[READ_CACHE_TOTAL_CACHE_SIZE_KEY].SetUint64(pages_per_bucket * Page::DEFAULT_PAGE_SIZE);
    auto adjusted_io_param = IOParameter::GetIOParameterByJson(json);
    auto source_reader_param = std::dynamic_pointer_cast<ReaderIOParameter>(io_param);
    auto adjusted_reader_param = std::dynamic_pointer_cast<ReaderIOParameter>(adjusted_io_param);
    if (source_reader_param != nullptr and adjusted_reader_param != nullptr) {
        adjusted_reader_param->reader = source_reader_param->reader;
    }
    return adjusted_io_param;
}
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L41 | io_param-&gt;ToJson | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L44 | json[READ_CACHE_TOTAL_CACHE_SIZE_KEY].SetUint64 | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L45 | IOParameter::GetIOParameterByJson | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L46 | std::dynamic_pointer_cast&lt;ReaderIOParameter&gt; | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L47 | std::dynamic_pointer_cast&lt;ReaderIOParameter&gt; | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L63"></a>

## `BucketDataCell::ScanBucketById`

源码位置：`src/datacell/bucket_datacell.h:63–69`。

这是接口适配层，转换 Computer 类型后转发 scan_bucket_by_id。不要在这一层停止：下层才有分块 Acquire、ScanBatchDists 和残差补偿。

### 完整函数

```cpp
void
    ScanBucketById(float* result_dists,
                   const ComputerInterfacePtr& computer,
                   const BucketIdType& bucket_id) override {
        auto comp = static_cast<Computer<QuantTmpl>*>(computer.get());
        return this->scan_bucket_by_id(result_dists, comp, bucket_id);
    }
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L67 | computer.get | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L68 | this-&gt;scan_bucket_by_id | 函数本体；短路求值/提前返回见源码 | [BucketDataCell&lt;QuantTmpl, IOTmpl&gt;::scan_bucket_by_id · L522](bucket_datacell_h.md#L522) |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L71"></a>

## `BucketDataCell::QueryOneById`

源码位置：`src/datacell/bucket_datacell.h:71–77`。

先从签名确认输入、返回值和 const/override，再按完整函数体的条件阅读调用点。下表保留了本函数的显式调用以及 lambda 中的调用；进入下层时用“候选实现”定位，未解析的对象由源码静态类型/运行时类型确认。

### 完整函数

```cpp
float
    QueryOneById(const ComputerInterfacePtr& computer,
                 const BucketIdType& bucket_id,
                 const InnerIdType& offset_id) override {
        auto comp = std::static_pointer_cast<Computer<QuantTmpl>>(computer);
        return this->query_one_by_id(comp, bucket_id, offset_id);
    }
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L75 | std::static_pointer_cast&lt;Computer&lt;QuantTmpl&gt;&gt; | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L76 | this-&gt;query_one_by_id | 函数本体；短路求值/提前返回见源码 | [BucketDataCell&lt;QuantTmpl, IOTmpl&gt;::query_one_by_id · L341](bucket_datacell_h.md#L341) |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L82"></a>

## `BucketDataCell::Query`

源码位置：`src/datacell/bucket_datacell.h:82–96`。

先从签名确认输入、返回值和 const/override，再按完整函数体的条件阅读调用点。下表保留了本函数的显式调用以及 lambda 中的调用；进入下层时用“候选实现”定位，未解析的对象由源码静态类型/运行时类型确认。

### 完整函数

```cpp
void
    Query(float* result_dists,
          const ComputerInterfacePtr& computer,
          const BucketIdType* bucket_ids,
          const InnerIdType* offset_ids,
          InnerIdType id_count,
          QueryContext* ctx = nullptr) override {
        if (id_count > 0 and GetQuantizerName() == QUANTIZATION_TYPE_VALUE_PQFS) {
            throw VsagException(ErrorType::INTERNAL_ERROR,
                                "PQFastScan doesn't support ComputeDist, only support "
                                "ComputeBatchDist");
        }
        auto comp = static_cast<Computer<QuantTmpl>*>(computer.get());
        this->query(result_dists, comp, bucket_ids, offset_ids, id_count, ctx);
    }
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L89 | GetQuantizerName | if_statement@89 (id_count &gt; 0 and GetQuantizerName() == QUANTIZATION_TYPE_VALUE_PQFS) | [BucketDataCell::GetQuantizerName · L170](bucket_datacell_h.md#L170) |

| L90 | VsagException | if_statement@89 (id_count &gt; 0 and GetQuantizerName() == QUANTIZATION_TYPE_VALUE_PQFS) | 当前参考未静态绑定；见下方边界说明 |

| L94 | computer.get | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L95 | this-&gt;query | 函数本体；短路求值/提前返回见源码 | [BucketDataCell&lt;QuantTmpl, IOTmpl&gt;::query · L380](bucket_datacell_h.md#L380) |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L120"></a>

## `BucketDataCell::GetInnerIds`

源码位置：`src/datacell/bucket_datacell.h:120–124`。

先从签名确认输入、返回值和 const/override，再按完整函数体的条件阅读调用点。下表保留了本函数的显式调用以及 lambda 中的调用；进入下层时用“候选实现”定位，未解析的对象由源码静态类型/运行时类型确认。

### 完整函数

```cpp
InnerIdType*
    GetInnerIds(BucketIdType bucket_id) override {
        check_valid_bucket_id(bucket_id);
        return this->inner_ids_[bucket_id].data();
    }
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L122 | check_valid_bucket_id | 函数本体；短路求值/提前返回见源码 | [BucketDataCell::check_valid_bucket_id · L244](bucket_datacell_h.md#L244) |

| L123 | this-&gt;inner_ids_[bucket_id].data | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L126"></a>

## `BucketDataCell::Prefetch`

源码位置：`src/datacell/bucket_datacell.h:126–130`。

先从签名确认输入、返回值和 const/override，再按完整函数体的条件阅读调用点。下表保留了本函数的显式调用以及 lambda 中的调用；进入下层时用“候选实现”定位，未解析的对象由源码静态类型/运行时类型确认。

### 完整函数

```cpp
void
    Prefetch(BucketIdType bucket_id, InnerIdType offset_id) override {
        this->check_valid_bucket_id(bucket_id);
        this->datas_[bucket_id].Prefetch(offset_id * code_size_, code_size_);
    }
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L128 | this-&gt;check_valid_bucket_id | 函数本体；短路求值/提前返回见源码 | [BucketDataCell::check_valid_bucket_id · L244](bucket_datacell_h.md#L244) |

| L129 | this-&gt;datas_[bucket_id].Prefetch | 函数本体；短路求值/提前返回见源码 | [BucketDataCell::Prefetch · L126](bucket_datacell_h.md#L126) |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L132"></a>

## `BucketDataCell::Package`

源码位置：`src/datacell/bucket_datacell.h:132–137`。

先从签名确认输入、返回值和 const/override，再按完整函数体的条件阅读调用点。下表保留了本函数的显式调用以及 lambda 中的调用；进入下层时用“候选实现”定位，未解析的对象由源码静态类型/运行时类型确认。

### 完整函数

```cpp
void
    Package() override {
        if (GetQuantizerName() == QUANTIZATION_TYPE_VALUE_PQFS) {
            this->package_fastscan();
        }
    }
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L134 | GetQuantizerName | if_statement@134 (GetQuantizerName() == QUANTIZATION_TYPE_VALUE_PQFS) | [BucketDataCell::GetQuantizerName · L170](bucket_datacell_h.md#L170) |

| L135 | this-&gt;package_fastscan | if_statement@134 (GetQuantizerName() == QUANTIZATION_TYPE_VALUE_PQFS) | [BucketDataCell&lt;QuantTmpl, IOTmpl&gt;::package_fastscan · L934](bucket_datacell_h.md#L934) |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L139"></a>

## `BucketDataCell::Unpack`

源码位置：`src/datacell/bucket_datacell.h:139–144`。

先从签名确认输入、返回值和 const/override，再按完整函数体的条件阅读调用点。下表保留了本函数的显式调用以及 lambda 中的调用；进入下层时用“候选实现”定位，未解析的对象由源码静态类型/运行时类型确认。

### 完整函数

```cpp
void
    Unpack() override {
        if (GetQuantizerName() == QUANTIZATION_TYPE_VALUE_PQFS) {
            this->unpack_fastscan();
        }
    }
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L141 | GetQuantizerName | if_statement@141 (GetQuantizerName() == QUANTIZATION_TYPE_VALUE_PQFS) | [BucketDataCell::GetQuantizerName · L170](bucket_datacell_h.md#L170) |

| L142 | this-&gt;unpack_fastscan | if_statement@141 (GetQuantizerName() == QUANTIZATION_TYPE_VALUE_PQFS) | [BucketDataCell&lt;QuantTmpl, IOTmpl&gt;::unpack_fastscan · L958](bucket_datacell_h.md#L958) |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L158"></a>

## `BucketDataCell::InitIO`

源码位置：`src/datacell/bucket_datacell.h:158–168`。

先从签名确认输入、返回值和 const/override，再按完整函数体的条件阅读调用点。下表保留了本函数的显式调用以及 lambda 中的调用；进入下层时用“候选实现”定位，未解析的对象由源码静态类型/运行时类型确认。

### 完整函数

```cpp
void
    InitIO(const IOParamPtr& io_param) override {
        if constexpr (IOTmpl::SkipDeserialize) {
            this->init_shared_read_cache_io(io_param);
            return;
        }
        auto adjusted_io_param = AdjustBucketReadCacheParam(io_param, this->bucket_count_);
        for (BucketIdType bucket_id = 0; bucket_id < this->bucket_count_; ++bucket_id) {
            this->datas_[bucket_id].InitIO(adjusted_io_param);
        }
    }
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L161 | this-&gt;init_shared_read_cache_io | if_statement@160 (IOTmpl::SkipDeserialize) | [BucketDataCell::init_shared_read_cache_io · L202](bucket_datacell_h.md#L202) |

| L164 | AdjustBucketReadCacheParam | 函数本体；短路求值/提前返回见源码 | [AdjustBucketReadCacheParam · L36](bucket_datacell_h.md#L36) |

| L166 | this-&gt;datas_[bucket_id].InitIO | for_statement@165 bucket_id &lt; this-&gt;bucket_count_ | [BucketDataCell::InitIO · L158](bucket_datacell_h.md#L158) |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L170"></a>

## `BucketDataCell::GetQuantizerName`

源码位置：`src/datacell/bucket_datacell.h:170–173`。

先从签名确认输入、返回值和 const/override，再按完整函数体的条件阅读调用点。下表保留了本函数的显式调用以及 lambda 中的调用；进入下层时用“候选实现”定位，未解析的对象由源码静态类型/运行时类型确认。

### 完整函数

```cpp
[[nodiscard]] std::string
    GetQuantizerName() override {
        return this->quantizer_->Name();
    }
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L172 | this-&gt;quantizer_-&gt;Name | 函数本体；短路求值/提前返回见源码 | [Quantizer::Name · L300](quantizer_h.md#L300) |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L175"></a>

## `BucketDataCell::GetMetricType`

源码位置：`src/datacell/bucket_datacell.h:175–178`。

先从签名确认输入、返回值和 const/override，再按完整函数体的条件阅读调用点。下表保留了本函数的显式调用以及 lambda 中的调用；进入下层时用“候选实现”定位，未解析的对象由源码静态类型/运行时类型确认。

### 完整函数

```cpp
[[nodiscard]] MetricType
    GetMetricType() override {
        return metric_;
    }
```

### 函数内部调用点：不省略标准库和辅助调用

此函数体没有显式函数调用表达式。赋值、成员初始化和隐式操作请看上面的完整源码。


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L180"></a>

## `BucketDataCell::GetBucketSize`

源码位置：`src/datacell/bucket_datacell.h:180–184`。

先从签名确认输入、返回值和 const/override，再按完整函数体的条件阅读调用点。下表保留了本函数的显式调用以及 lambda 中的调用；进入下层时用“候选实现”定位，未解析的对象由源码静态类型/运行时类型确认。

### 完整函数

```cpp
[[nodiscard]] InnerIdType
    GetBucketSize(BucketIdType bucket_id) override {
        check_valid_bucket_id(bucket_id);
        return this->bucket_sizes_[bucket_id];
    }
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L182 | check_valid_bucket_id | 函数本体；短路求值/提前返回见源码 | [BucketDataCell::check_valid_bucket_id · L244](bucket_datacell_h.md#L244) |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L189"></a>

## `BucketDataCell::GetMemoryUsage`

源码位置：`src/datacell/bucket_datacell.h:189–199`。

先从签名确认输入、返回值和 const/override，再按完整函数体的条件阅读调用点。下表保留了本函数的显式调用以及 lambda 中的调用；进入下层时用“候选实现”定位，未解析的对象由源码静态类型/运行时类型确认。

### 完整函数

```cpp
[[nodiscard]] uint64_t
    GetMemoryUsage() const override {
        uint64_t memory = sizeof(BucketDataCell);
        for (BucketIdType bucket_id = 0; bucket_id < this->bucket_count_; bucket_id++) {
            memory += this->datas_[bucket_id].GetMemoryUsage();
            memory += this->inner_ids_[bucket_id].size() * sizeof(InnerIdType);
            memory += this->residual_bias_[bucket_id].size() * sizeof(float);
            memory += sizeof(std::shared_mutex) + sizeof(InnerIdType);
        }
        return memory;
    }
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L193 | this-&gt;datas_[bucket_id].GetMemoryUsage | for_statement@192 bucket_id &lt; this-&gt;bucket_count_ | [BucketDataCell::GetMemoryUsage · L189](bucket_datacell_h.md#L189) |

| L194 | this-&gt;inner_ids_[bucket_id].size | for_statement@192 bucket_id &lt; this-&gt;bucket_count_ | 当前参考未静态绑定；见下方边界说明 |

| L195 | this-&gt;residual_bias_[bucket_id].size | for_statement@192 bucket_id &lt; this-&gt;bucket_count_ | 当前参考未静态绑定；见下方边界说明 |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L202"></a>

## `BucketDataCell::init_shared_read_cache_io`

源码位置：`src/datacell/bucket_datacell.h:202–236`。

先从签名确认输入、返回值和 const/override，再按完整函数体的条件阅读调用点。下表保留了本函数的显式调用以及 lambda 中的调用；进入下层时用“候选实现”定位，未解析的对象由源码静态类型/运行时类型确认。

### 完整函数

```cpp
void
    init_shared_read_cache_io(const IOParamPtr& io_param) {
        for (BucketIdType bucket_id = 0; bucket_id < this->bucket_count_; ++bucket_id) {
            this->datas_[bucket_id].SetReadCache(nullptr);
        }
        for (BucketIdType bucket_id = 0; bucket_id < this->bucket_count_; ++bucket_id) {
            this->datas_[bucket_id].InitIO(io_param);
        }

        if (io_param == nullptr or not io_param->enable_read_cache_) {
            return;
        }
        uint64_t cache_page_count = io_param->read_cache_total_size_ / Page::DEFAULT_PAGE_SIZE;
        if (cache_page_count == 0) {
            return;
        }

        uint64_t page_id_base = 0;
        for (BucketIdType bucket_id = 0; bucket_id < this->bucket_count_; ++bucket_id) {
            uint64_t bucket_page_count = get_page_count(this->datas_[bucket_id].Size());
            if (bucket_page_count > UINT64_MAX - page_id_base) {
                throw VsagException(ErrorType::INVALID_BINARY,
                                    "bucket read cache page id overflow");
            }
            page_id_base += bucket_page_count;
        }

        auto shared_cache = std::make_shared<LRUPageCache>(cache_page_count);
        page_id_base = 0;
        for (BucketIdType bucket_id = 0; bucket_id < this->bucket_count_; ++bucket_id) {
            uint64_t bucket_page_count = get_page_count(this->datas_[bucket_id].Size());
            this->datas_[bucket_id].SetReadCache(shared_cache, page_id_base);
            page_id_base += bucket_page_count;
        }
    }
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L205 | this-&gt;datas_[bucket_id].SetReadCache | for_statement@204 bucket_id &lt; this-&gt;bucket_count_ | 当前参考未静态绑定；见下方边界说明 |

| L208 | this-&gt;datas_[bucket_id].InitIO | for_statement@207 bucket_id &lt; this-&gt;bucket_count_ | [BucketDataCell::InitIO · L158](bucket_datacell_h.md#L158) |

| L221 | get_page_count | for_statement@220 bucket_id &lt; this-&gt;bucket_count_ | [BucketDataCell::get_page_count · L238](bucket_datacell_h.md#L238) |

| L221 | this-&gt;datas_[bucket_id].Size | for_statement@220 bucket_id &lt; this-&gt;bucket_count_ | 当前参考未静态绑定；见下方边界说明 |

| L223 | VsagException | for_statement@220 bucket_id &lt; this-&gt;bucket_count_ → if_statement@222 (bucket_page_count &gt; UINT64_MAX - page_id_base) | 当前参考未静态绑定；见下方边界说明 |

| L229 | std::make_shared&lt;LRUPageCache&gt; | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L232 | get_page_count | for_statement@231 bucket_id &lt; this-&gt;bucket_count_ | [BucketDataCell::get_page_count · L238](bucket_datacell_h.md#L238) |

| L232 | this-&gt;datas_[bucket_id].Size | for_statement@231 bucket_id &lt; this-&gt;bucket_count_ | 当前参考未静态绑定；见下方边界说明 |

| L233 | this-&gt;datas_[bucket_id].SetReadCache | for_statement@231 bucket_id &lt; this-&gt;bucket_count_ | 当前参考未静态绑定；见下方边界说明 |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L238"></a>

## `BucketDataCell::get_page_count`

源码位置：`src/datacell/bucket_datacell.h:238–242`。

先从签名确认输入、返回值和 const/override，再按完整函数体的条件阅读调用点。下表保留了本函数的显式调用以及 lambda 中的调用；进入下层时用“候选实现”定位，未解析的对象由源码静态类型/运行时类型确认。

### 完整函数

```cpp
static uint64_t
    get_page_count(uint64_t data_size) {
        return data_size / Page::DEFAULT_PAGE_SIZE +
               static_cast<uint64_t>(data_size % Page::DEFAULT_PAGE_SIZE != 0);
    }
```

### 函数内部调用点：不省略标准库和辅助调用

此函数体没有显式函数调用表达式。赋值、成员初始化和隐式操作请看上面的完整源码。


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L244"></a>

## `BucketDataCell::check_valid_bucket_id`

源码位置：`src/datacell/bucket_datacell.h:244–249`。

先从签名确认输入、返回值和 const/override，再按完整函数体的条件阅读调用点。下表保留了本函数的显式调用以及 lambda 中的调用；进入下层时用“候选实现”定位，未解析的对象由源码静态类型/运行时类型确认。

### 完整函数

```cpp
inline void
    check_valid_bucket_id(BucketIdType bucket_id) {
        if (bucket_id >= this->bucket_count_ or bucket_id < 0) {
            throw VsagException(ErrorType::INTERNAL_ERROR, "visited invalid bucket id");
        }
    }
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L247 | VsagException | if_statement@246 (bucket_id &gt;= this-&gt;bucket_count_ or bucket_id &lt; 0) | 当前参考未静态绑定；见下方边界说明 |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L312"></a>

## `BucketDataCell<QuantTmpl, IOTmpl>::BucketDataCell`

源码位置：`src/datacell/bucket_datacell.h:312–338`。

先从签名确认输入、返回值和 const/override，再按完整函数体的条件阅读调用点。下表保留了本函数的显式调用以及 lambda 中的调用；进入下层时用“候选实现”定位，未解析的对象由源码静态类型/运行时类型确认。

### 完整函数

```cpp
BucketDataCell<QuantTmpl, IOTmpl>::BucketDataCell(const QuantizerParamPtr& quantization_param,
                                                  const IOParamPtr& io_param,
                                                  const IndexCommonParam& common_param,
                                                  BucketIdType bucket_count,
                                                  bool use_residual)
    : BucketInterface(),
      datas_(common_param.allocator_.get(),
             AdjustBucketReadCacheParam(io_param, bucket_count),
             common_param),
      bucket_sizes_(bucket_count, 0, common_param.allocator_.get()),
      inner_ids_(bucket_count,
                 Vector<InnerIdType>(common_param.allocator_.get()),
                 common_param.allocator_.get()),
      bucket_mutexes_(bucket_count, common_param.allocator_.get()),
      allocator_(common_param.allocator_.get()),
      residual_bias_(bucket_count, Vector<float>(allocator_), allocator_),
      metric_(common_param.metric_),
      input_dim_(common_param.dim_) {
    this->bucket_count_ = bucket_count;
    this->quantizer_ = std::make_shared<QuantTmpl>(quantization_param, common_param);
    this->code_size_ = quantizer_->GetCodeSize();
    this->use_residual_ = use_residual;
    this->backend_ =
        QuantizerDistanceBackend<QuantTmpl>::Get(static_cast<const QuantTmpl&>(*quantizer_));

    datas_.Resize(bucket_count);
}
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L331 | std::make_shared&lt;QuantTmpl&gt; | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L332 | quantizer_-&gt;GetCodeSize | 函数本体；短路求值/提前返回见源码 | [Quantizer::GetCodeSize · L325](quantizer_h.md#L325) |

| L335 | QuantizerDistanceBackend&lt;QuantTmpl&gt;::Get | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L337 | datas_.Resize | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L341"></a>

## `BucketDataCell<QuantTmpl, IOTmpl>::query_one_by_id`

源码位置：`src/datacell/bucket_datacell.h:341–377`。

先从签名确认输入、返回值和 const/override，再按完整函数体的条件阅读调用点。下表保留了本函数的显式调用以及 lambda 中的调用；进入下层时用“候选实现”定位，未解析的对象由源码静态类型/运行时类型确认。

### 完整函数

```cpp
float
BucketDataCell<QuantTmpl, IOTmpl>::query_one_by_id(
    const std::shared_ptr<Computer<QuantTmpl>>& computer,
    const BucketIdType& bucket_id,
    const InnerIdType& offset_id) {
    if (bucket_id >= this->bucket_count_ or bucket_id < 0) {
        throw VsagException(ErrorType::INTERNAL_ERROR, "visited invalid bucket id");
    }
    std::shared_lock lock(this->bucket_mutexes_[bucket_id]);
    this->check_valid_bucket_id(bucket_id);
    if (offset_id >= this->bucket_sizes_[bucket_id]) {
        throw VsagException(ErrorType::INVALID_ARGUMENT, "invalid offset id for bucket");
    }
    if (this->inner_ids_[bucket_id][offset_id] == EMPTY_INNER_ID) {
        throw VsagException(
            ErrorType::INVALID_ARGUMENT,
            fmt::format("visited empty offset in bucket: bucket_id={}, offset_id={}",
                        bucket_id,
                        offset_id));
    }
    float ret;
    auto lease = this->datas_[bucket_id].Acquire(offset_id * code_size_, code_size_);
    computer->ComputeDist(lease.Data(), &ret);

    if (use_residual_) {
        Vector<float> centroid(this->quantizer_->GetDim(), allocator_);
        strategy_->GetCentroid(bucket_id, centroid);
        auto ip_distance =
            FP32ComputeIP(computer->raw_query_.data(), centroid.data(), this->quantizer_->GetDim());
        if (metric_ == MetricType::METRIC_TYPE_L2SQR) {
            ip_distance *= 2;
            ret = ret - residual_bias_[bucket_id][offset_id];
        }
        ret -= ip_distance;
    }
    return ret;
}
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L347 | VsagException | if_statement@346 (bucket_id &gt;= this-&gt;bucket_count_ or bucket_id &lt; 0) | 当前参考未静态绑定；见下方边界说明 |

| L350 | this-&gt;check_valid_bucket_id | 函数本体；短路求值/提前返回见源码 | [BucketDataCell::check_valid_bucket_id · L244](bucket_datacell_h.md#L244) |

| L352 | VsagException | if_statement@351 (offset_id &gt;= this-&gt;bucket_sizes_[bucket_id]) | 当前参考未静态绑定；见下方边界说明 |

| L355 | VsagException | if_statement@354 (this-&gt;inner_ids_[bucket_id][offset_id] == EMPTY_INNER_ID) | 当前参考未静态绑定；见下方边界说明 |

| L357 | fmt::format | if_statement@354 (this-&gt;inner_ids_[bucket_id][offset_id] == EMPTY_INNER_ID) | 当前参考未静态绑定；见下方边界说明 |

| L362 | this-&gt;datas_[bucket_id].Acquire | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L363 | computer-&gt;ComputeDist | 函数本体；短路求值/提前返回见源码 | [Computer::ComputeDist · L53](computer_h.md#L53)；[Computer&lt;TransformQuantizer&lt;QuantImpl, metric&gt;&gt;::ComputeDist · L127](computer_h.md#L127) |

| L363 | lease.Data | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L366 | this-&gt;quantizer_-&gt;GetDim | if_statement@365 (use_residual_) | [Quantizer::GetDim · L340](quantizer_h.md#L340) |

| L367 | strategy_-&gt;GetCentroid | if_statement@365 (use_residual_) | 当前参考未静态绑定；见下方边界说明 |

| L369 | FP32ComputeIP | if_statement@365 (use_residual_) | 当前参考未静态绑定；见下方边界说明 |

| L369 | computer-&gt;raw_query_.data | if_statement@365 (use_residual_) | 当前参考未静态绑定；见下方边界说明 |

| L369 | centroid.data | if_statement@365 (use_residual_) | 当前参考未静态绑定；见下方边界说明 |

| L369 | this-&gt;quantizer_-&gt;GetDim | if_statement@365 (use_residual_) | [Quantizer::GetDim · L340](quantizer_h.md#L340) |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L380"></a>

## `BucketDataCell<QuantTmpl, IOTmpl>::query`

源码位置：`src/datacell/bucket_datacell.h:380–519`。

先从签名确认输入、返回值和 const/override，再按完整函数体的条件阅读调用点。下表保留了本函数的显式调用以及 lambda 中的调用；进入下层时用“候选实现”定位，未解析的对象由源码静态类型/运行时类型确认。

### 完整函数

```cpp
void
BucketDataCell<QuantTmpl, IOTmpl>::query(float* result_dists,
                                         Computer<QuantTmpl>* computer,
                                         const BucketIdType* bucket_ids,
                                         const InnerIdType* offset_ids,
                                         InnerIdType id_count,
                                         QueryContext* ctx) {
    if (id_count == 0) {
        return;
    }

    struct QueryRequest {
        BucketIdType bucket_id;
        InnerIdType offset_id;
        InnerIdType result_index;
    };

    Allocator* search_alloc = select_query_allocator(ctx, allocator_);
    Vector<QueryRequest> requests(search_alloc);
    requests.reserve(id_count);
    for (InnerIdType i = 0; i < id_count; ++i) {
        check_valid_bucket_id(bucket_ids[i]);
        requests.emplace_back(QueryRequest{bucket_ids[i], offset_ids[i], i});
    }
    std::sort(requests.begin(), requests.end(), [](const auto& lhs, const auto& rhs) {
        if (lhs.bucket_id != rhs.bucket_id) {
            return lhs.bucket_id < rhs.bucket_id;
        }
        if (lhs.offset_id != rhs.offset_id) {
            return lhs.offset_id < rhs.offset_id;
        }
        return lhs.result_index < rhs.result_index;
    });

    uint64_t io_count = 0;
    double io_cost_ms = 0.0F;
    Vector<InnerIdType> unique_offsets(search_alloc);
    Vector<uint64_t> read_sizes(search_alloc);
    Vector<uint64_t> read_offsets(search_alloc);
    unique_offsets.reserve(id_count);
    read_sizes.reserve(id_count);
    read_offsets.reserve(id_count);
    ByteBuffer codes(static_cast<uint64_t>(id_count) * code_size_, search_alloc);
    Vector<float> unique_dists(id_count, 0.0F, search_alloc);
    uint64_t group_begin = 0;
    while (group_begin < requests.size()) {
        const auto bucket_id = requests[group_begin].bucket_id;
        uint64_t group_end = group_begin + 1;
        while (group_end < requests.size() and requests[group_end].bucket_id == bucket_id) {
            ++group_end;
        }

        std::shared_lock lock(this->bucket_mutexes_[bucket_id]);
        for (uint64_t i = group_begin; i < group_end; ++i) {
            const auto offset_id = requests[i].offset_id;
            if (offset_id >= this->bucket_sizes_[bucket_id]) {
                throw VsagException(ErrorType::INVALID_ARGUMENT, "invalid offset id for bucket");
            }
            if (this->inner_ids_[bucket_id][offset_id] == EMPTY_INNER_ID) {
                throw VsagException(
                    ErrorType::INVALID_ARGUMENT,
                    fmt::format("visited empty offset in bucket: bucket_id={}, offset_id={}",
                                bucket_id,
                                offset_id));
            }
        }

        unique_offsets.clear();
        for (uint64_t i = group_begin; i < group_end; ++i) {
            const auto offset_id = requests[i].offset_id;
            if (unique_offsets.empty() or unique_offsets.back() != offset_id) {
                unique_offsets.emplace_back(offset_id);
            }
        }

        read_sizes.clear();
        read_offsets.clear();
        for (const auto offset_id : unique_offsets) {
            if (not read_offsets.empty() and
                read_offsets.back() + read_sizes.back() ==
                    static_cast<uint64_t>(offset_id) * code_size_ and
                code_size_ <= static_cast<uint64_t>(std::numeric_limits<int32_t>::max()) and
                read_sizes.back() <=
                    static_cast<uint64_t>(std::numeric_limits<int32_t>::max()) - code_size_) {
                read_sizes.back() += code_size_;
            } else {
                read_sizes.emplace_back(code_size_);
                read_offsets.emplace_back(static_cast<uint64_t>(offset_id) * code_size_);
            }
        }

        bool read_success = false;
        double group_io_cost_ms = 0.0F;
        {
            Timer timer(group_io_cost_ms);
            read_success = this->datas_[bucket_id].MultiRead(
                codes.data, read_sizes.data(), read_offsets.data(), read_sizes.size());
        }
        if (not read_success) {
            throw VsagException(ErrorType::READ_ERROR, "failed to batch read bucket data");
        }
        io_count += read_sizes.size();
        io_cost_ms += group_io_cost_ms;

        computer->ScanBatchDists(unique_offsets.size(), codes.data, unique_dists.data());
        if (use_residual_) {
            Vector<float> centroid(this->quantizer_->GetDim(), search_alloc);
            strategy_->GetCentroid(bucket_id, centroid);
            auto ip_distance = FP32ComputeIP(
                computer->raw_query_.data(), centroid.data(), this->quantizer_->GetDim());
            if (metric_ == MetricType::METRIC_TYPE_L2SQR) {
                ip_distance *= 2;
                for (uint64_t i = 0; i < unique_offsets.size(); ++i) {
                    unique_dists[i] -= residual_bias_[bucket_id][unique_offsets[i]];
                }
            }
            for (uint64_t i = 0; i < unique_offsets.size(); ++i) {
                unique_dists[i] -= ip_distance;
            }
        }

        uint64_t unique_index = 0;
        for (uint64_t i = group_begin; i < group_end; ++i) {
            if (i > group_begin and requests[i].offset_id != requests[i - 1].offset_id) {
                ++unique_index;
            }
            result_dists[requests[i].result_index] = unique_dists[unique_index];
        }
        group_begin = group_end;
    }

    if constexpr (not IOTmpl::InMemory) {
        if (ctx != nullptr and ctx->stats != nullptr) {
            ctx->stats->io_cnt.fetch_add(static_cast<uint32_t>(io_count),
                                         std::memory_order_relaxed);
            ctx->stats->io_time_ms.fetch_add(static_cast<uint32_t>(io_cost_ms),
                                             std::memory_order_relaxed);
        }
    }
}
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L397 | select_query_allocator | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L399 | requests.reserve | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L401 | check_valid_bucket_id | for_statement@400 i &lt; id_count | [BucketDataCell::check_valid_bucket_id · L244](bucket_datacell_h.md#L244) |

| L402 | requests.emplace_back | for_statement@400 i &lt; id_count | 当前参考未静态绑定；见下方边界说明 |

| L404 | std::sort | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L404 | requests.begin | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L404 | requests.end | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L419 | unique_offsets.reserve | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L420 | read_sizes.reserve | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L421 | read_offsets.reserve | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L425 | requests.size | while_statement@425 (group_begin &lt; requests.size()) | 当前参考未静态绑定；见下方边界说明 |

| L428 | requests.size | while_statement@425 (group_begin &lt; requests.size()) → while_statement@428 (group_end &lt; requests.size() and requests[group_end].bucket_id == bucket_id) | 当前参考未静态绑定；见下方边界说明 |

| L436 | VsagException | while_statement@425 (group_begin &lt; requests.size()) → for_statement@433 i &lt; group_end → if_statement@435 (offset_id &gt;= this-&gt;bucket_sizes_[bucket_id]) | 当前参考未静态绑定；见下方边界说明 |

| L439 | VsagException | while_statement@425 (group_begin &lt; requests.size()) → for_statement@433 i &lt; group_end → if_statement@438 (this-&gt;inner_ids_[bucket_id][offset_id] == EMPTY_INNER_ID) | 当前参考未静态绑定；见下方边界说明 |

| L441 | fmt::format | while_statement@425 (group_begin &lt; requests.size()) → for_statement@433 i &lt; group_end → if_statement@438 (this-&gt;inner_ids_[bucket_id][offset_id] == EMPTY_INNER_ID) | 当前参考未静态绑定；见下方边界说明 |

| L447 | unique_offsets.clear | while_statement@425 (group_begin &lt; requests.size()) | 当前参考未静态绑定；见下方边界说明 |

| L450 | unique_offsets.empty | while_statement@425 (group_begin &lt; requests.size()) → for_statement@448 i &lt; group_end → if_statement@450 (unique_offsets.empty() or unique_offsets.back() != offset_id) | 当前参考未静态绑定；见下方边界说明 |

| L450 | unique_offsets.back | while_statement@425 (group_begin &lt; requests.size()) → for_statement@448 i &lt; group_end → if_statement@450 (unique_offsets.empty() or unique_offsets.back() != offset_id) | 当前参考未静态绑定；见下方边界说明 |

| L451 | unique_offsets.emplace_back | while_statement@425 (group_begin &lt; requests.size()) → for_statement@448 i &lt; group_end → if_statement@450 (unique_offsets.empty() or unique_offsets.back() != offset_id) | 当前参考未静态绑定；见下方边界说明 |

| L455 | read_sizes.clear | while_statement@425 (group_begin &lt; requests.size()) | 当前参考未静态绑定；见下方边界说明 |

| L456 | read_offsets.clear | while_statement@425 (group_begin &lt; requests.size()) | 当前参考未静态绑定；见下方边界说明 |

| L458 | read_offsets.empty | while_statement@425 (group_begin &lt; requests.size()) → for_range_loop@457 → if_statement@458 (not read_offsets.empty() and read_offsets.back() + read_sizes.back() == static_cast&lt;uint64_t&gt;(offset_id) * code_size_ and code_size_ &lt;= static_cast&lt;uint64_t&gt;(std::numeric_limits&lt;int32_t&gt;::max()) and read_sizes.back() &lt;= static_cast&lt;uint64_t&gt;(std::numeric_limits&lt;int32_t&gt;::max()) - code_size_) | 当前参考未静态绑定；见下方边界说明 |

| L459 | read_offsets.back | while_statement@425 (group_begin &lt; requests.size()) → for_range_loop@457 → if_statement@458 (not read_offsets.empty() and read_offsets.back() + read_sizes.back() == static_cast&lt;uint64_t&gt;(offset_id) * code_size_ and code_size_ &lt;= static_cast&lt;uint64_t&gt;(std::numeric_limits&lt;int32_t&gt;::max()) and read_sizes.back() &lt;= static_cast&lt;uint64_t&gt;(std::numeric_limits&lt;int32_t&gt;::max()) - code_size_) | 当前参考未静态绑定；见下方边界说明 |

| L459 | read_sizes.back | while_statement@425 (group_begin &lt; requests.size()) → for_range_loop@457 → if_statement@458 (not read_offsets.empty() and read_offsets.back() + read_sizes.back() == static_cast&lt;uint64_t&gt;(offset_id) * code_size_ and code_size_ &lt;= static_cast&lt;uint64_t&gt;(std::numeric_limits&lt;int32_t&gt;::max()) and read_sizes.back() &lt;= static_cast&lt;uint64_t&gt;(std::numeric_limits&lt;int32_t&gt;::max()) - code_size_) | 当前参考未静态绑定；见下方边界说明 |

| L461 | std::numeric_limits&lt;int32_t&gt;::max | while_statement@425 (group_begin &lt; requests.size()) → for_range_loop@457 → if_statement@458 (not read_offsets.empty() and read_offsets.back() + read_sizes.back() == static_cast&lt;uint64_t&gt;(offset_id) * code_size_ and code_size_ &lt;= static_cast&lt;uint64_t&gt;(std::numeric_limits&lt;int32_t&gt;::max()) and read_sizes.back() &lt;= static_cast&lt;uint64_t&gt;(std::numeric_limits&lt;int32_t&gt;::max()) - code_size_) | 当前参考未静态绑定；见下方边界说明 |

| L462 | read_sizes.back | while_statement@425 (group_begin &lt; requests.size()) → for_range_loop@457 → if_statement@458 (not read_offsets.empty() and read_offsets.back() + read_sizes.back() == static_cast&lt;uint64_t&gt;(offset_id) * code_size_ and code_size_ &lt;= static_cast&lt;uint64_t&gt;(std::numeric_limits&lt;int32_t&gt;::max()) and read_sizes.back() &lt;= static_cast&lt;uint64_t&gt;(std::numeric_limits&lt;int32_t&gt;::max()) - code_size_) | 当前参考未静态绑定；见下方边界说明 |

| L463 | std::numeric_limits&lt;int32_t&gt;::max | while_statement@425 (group_begin &lt; requests.size()) → for_range_loop@457 → if_statement@458 (not read_offsets.empty() and read_offsets.back() + read_sizes.back() == static_cast&lt;uint64_t&gt;(offset_id) * code_size_ and code_size_ &lt;= static_cast&lt;uint64_t&gt;(std::numeric_limits&lt;int32_t&gt;::max()) and read_sizes.back() &lt;= static_cast&lt;uint64_t&gt;(std::numeric_limits&lt;int32_t&gt;::max()) - code_size_) | 当前参考未静态绑定；见下方边界说明 |

| L464 | read_sizes.back | while_statement@425 (group_begin &lt; requests.size()) → for_range_loop@457 → if_statement@458 (not read_offsets.empty() and read_offsets.back() + read_sizes.back() == static_cast&lt;uint64_t&gt;(offset_id) * code_size_ and code_size_ &lt;= static_cast&lt;uint64_t&gt;(std::numeric_limits&lt;int32_t&gt;::max()) and read_sizes.back() &lt;= static_cast&lt;uint64_t&gt;(std::numeric_limits&lt;int32_t&gt;::max()) - code_size_) | 当前参考未静态绑定；见下方边界说明 |

| L466 | read_sizes.emplace_back | while_statement@425 (group_begin &lt; requests.size()) → for_range_loop@457 → if_statement@458 (not read_offsets.empty() and read_offsets.back() + read_sizes.back() == static_cast&lt;uint64_t&gt;(offset_id) * code_size_ and code_size_ &lt;= static_cast&lt;uint64_t&gt;(std::numeric_limits&lt;int32_t&gt;::max()) and read_sizes.back() &lt;= static_cast&lt;uint64_t&gt;(std::numeric_limits&lt;int32_t&gt;::max()) - code_size_) [else 分支] | 当前参考未静态绑定；见下方边界说明 |

| L467 | read_offsets.emplace_back | while_statement@425 (group_begin &lt; requests.size()) → for_range_loop@457 → if_statement@458 (not read_offsets.empty() and read_offsets.back() + read_sizes.back() == static_cast&lt;uint64_t&gt;(offset_id) * code_size_ and code_size_ &lt;= static_cast&lt;uint64_t&gt;(std::numeric_limits&lt;int32_t&gt;::max()) and read_sizes.back() &lt;= static_cast&lt;uint64_t&gt;(std::numeric_limits&lt;int32_t&gt;::max()) - code_size_) [else 分支] | 当前参考未静态绑定；见下方边界说明 |

| L475 | this-&gt;datas_[bucket_id].MultiRead | while_statement@425 (group_begin &lt; requests.size()) | 当前参考未静态绑定；见下方边界说明 |

| L476 | read_sizes.data | while_statement@425 (group_begin &lt; requests.size()) | 当前参考未静态绑定；见下方边界说明 |

| L476 | read_offsets.data | while_statement@425 (group_begin &lt; requests.size()) | 当前参考未静态绑定；见下方边界说明 |

| L476 | read_sizes.size | while_statement@425 (group_begin &lt; requests.size()) | 当前参考未静态绑定；见下方边界说明 |

| L479 | VsagException | while_statement@425 (group_begin &lt; requests.size()) → if_statement@478 (not read_success) | 当前参考未静态绑定；见下方边界说明 |

| L481 | read_sizes.size | while_statement@425 (group_begin &lt; requests.size()) | 当前参考未静态绑定；见下方边界说明 |

| L484 | computer-&gt;ScanBatchDists | while_statement@425 (group_begin &lt; requests.size()) | [Computer::ScanBatchDists · L68](computer_h.md#L68)；[Computer&lt;TransformQuantizer&lt;QuantImpl, metric&gt;&gt;::ScanBatchDists · L142](computer_h.md#L142) |

| L484 | unique_offsets.size | while_statement@425 (group_begin &lt; requests.size()) | 当前参考未静态绑定；见下方边界说明 |

| L484 | unique_dists.data | while_statement@425 (group_begin &lt; requests.size()) | 当前参考未静态绑定；见下方边界说明 |

| L486 | this-&gt;quantizer_-&gt;GetDim | while_statement@425 (group_begin &lt; requests.size()) → if_statement@485 (use_residual_) | [Quantizer::GetDim · L340](quantizer_h.md#L340) |

| L487 | strategy_-&gt;GetCentroid | while_statement@425 (group_begin &lt; requests.size()) → if_statement@485 (use_residual_) | 当前参考未静态绑定；见下方边界说明 |

| L488 | FP32ComputeIP | while_statement@425 (group_begin &lt; requests.size()) → if_statement@485 (use_residual_) | 当前参考未静态绑定；见下方边界说明 |

| L489 | computer-&gt;raw_query_.data | while_statement@425 (group_begin &lt; requests.size()) → if_statement@485 (use_residual_) | 当前参考未静态绑定；见下方边界说明 |

| L489 | centroid.data | while_statement@425 (group_begin &lt; requests.size()) → if_statement@485 (use_residual_) | 当前参考未静态绑定；见下方边界说明 |

| L489 | this-&gt;quantizer_-&gt;GetDim | while_statement@425 (group_begin &lt; requests.size()) → if_statement@485 (use_residual_) | [Quantizer::GetDim · L340](quantizer_h.md#L340) |

| L492 | unique_offsets.size | while_statement@425 (group_begin &lt; requests.size()) → if_statement@485 (use_residual_) → if_statement@490 (metric_ == MetricType::METRIC_TYPE_L2SQR) → for_statement@492 i &lt; unique_offsets.size() | 当前参考未静态绑定；见下方边界说明 |

| L496 | unique_offsets.size | while_statement@425 (group_begin &lt; requests.size()) → if_statement@485 (use_residual_) → for_statement@496 i &lt; unique_offsets.size() | 当前参考未静态绑定；见下方边界说明 |

| L513 | ctx-&gt;stats-&gt;io_cnt.fetch_add | if_statement@511 (not IOTmpl::InMemory) → if_statement@512 (ctx != nullptr and ctx-&gt;stats != nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L515 | ctx-&gt;stats-&gt;io_time_ms.fetch_add | if_statement@511 (not IOTmpl::InMemory) → if_statement@512 (ctx != nullptr and ctx-&gt;stats != nullptr) | 当前参考未静态绑定；见下方边界说明 |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L522"></a>

## `BucketDataCell<QuantTmpl, IOTmpl>::scan_bucket_by_id`

源码位置：`src/datacell/bucket_datacell.h:522–563`。

持有桶读锁，每次最多读 32 条编码。Acquire 返回带生命周期的租借对象，Data 提供编码字节；ScanBatchDists 写回对应距离区间。之后执行残差补偿和空 posting 距离处理。

### 完整函数

```cpp
void
BucketDataCell<QuantTmpl, IOTmpl>::scan_bucket_by_id(float* result_dists,
                                                     Computer<QuantTmpl>* computer,
                                                     const BucketIdType& bucket_id) {
    if (bucket_id >= this->bucket_count_ or bucket_id < 0) {
        throw VsagException(ErrorType::INTERNAL_ERROR, "visited invalid bucket id");
    }
    std::shared_lock lock(this->bucket_mutexes_[bucket_id]);
    constexpr InnerIdType scan_block_size = 32;
    InnerIdType offset = 0;
    this->check_valid_bucket_id(bucket_id);
    auto data_count = this->bucket_sizes_[bucket_id];
    while (data_count > 0) {
        auto compute_count = std::min(data_count, scan_block_size);
        auto lease =
            this->datas_[bucket_id].Acquire(offset * code_size_, code_size_ * compute_count);
        computer->ScanBatchDists(compute_count, lease.Data(), result_dists + offset);
        data_count -= compute_count;
        offset += compute_count;
    }

    auto ip_distance = 0.0F;
    Vector<float> centroid(this->quantizer_->GetDim(), allocator_);
    if (use_residual_) {
        strategy_->GetCentroid(bucket_id, centroid);
        ip_distance =
            FP32ComputeIP(computer->raw_query_.data(), centroid.data(), this->quantizer_->GetDim());
        if (metric_ == MetricType::METRIC_TYPE_L2SQR) {
            ip_distance *= 2;
            FP32Sub(result_dists, residual_bias_[bucket_id].data(), result_dists, offset);
        }
        // TODO(inabao): optimize this loop with simd
        for (InnerIdType i = 0; i < offset; ++i) {
            result_dists[i] -= ip_distance;
        }
    }
    for (InnerIdType i = 0; i < offset; ++i) {
        if (this->inner_ids_[bucket_id][i] == EMPTY_INNER_ID) {
            result_dists[i] = std::numeric_limits<float>::max();
        }
    }
}
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L527 | VsagException | if_statement@526 (bucket_id &gt;= this-&gt;bucket_count_ or bucket_id &lt; 0) | 当前参考未静态绑定；见下方边界说明 |

| L532 | this-&gt;check_valid_bucket_id | 函数本体；短路求值/提前返回见源码 | [BucketDataCell::check_valid_bucket_id · L244](bucket_datacell_h.md#L244) |

| L535 | std::min | while_statement@534 (data_count &gt; 0) | 当前参考未静态绑定；见下方边界说明 |

| L537 | this-&gt;datas_[bucket_id].Acquire | while_statement@534 (data_count &gt; 0) | 当前参考未静态绑定；见下方边界说明 |

| L538 | computer-&gt;ScanBatchDists | while_statement@534 (data_count &gt; 0) | [Computer::ScanBatchDists · L68](computer_h.md#L68)；[Computer&lt;TransformQuantizer&lt;QuantImpl, metric&gt;&gt;::ScanBatchDists · L142](computer_h.md#L142) |

| L538 | lease.Data | while_statement@534 (data_count &gt; 0) | 当前参考未静态绑定；见下方边界说明 |

| L544 | this-&gt;quantizer_-&gt;GetDim | 函数本体；短路求值/提前返回见源码 | [Quantizer::GetDim · L340](quantizer_h.md#L340) |

| L546 | strategy_-&gt;GetCentroid | if_statement@545 (use_residual_) | 当前参考未静态绑定；见下方边界说明 |

| L548 | FP32ComputeIP | if_statement@545 (use_residual_) | 当前参考未静态绑定；见下方边界说明 |

| L548 | computer-&gt;raw_query_.data | if_statement@545 (use_residual_) | 当前参考未静态绑定；见下方边界说明 |

| L548 | centroid.data | if_statement@545 (use_residual_) | 当前参考未静态绑定；见下方边界说明 |

| L548 | this-&gt;quantizer_-&gt;GetDim | if_statement@545 (use_residual_) | [Quantizer::GetDim · L340](quantizer_h.md#L340) |

| L551 | FP32Sub | if_statement@545 (use_residual_) → if_statement@549 (metric_ == MetricType::METRIC_TYPE_L2SQR) | 当前参考未静态绑定；见下方边界说明 |

| L551 | residual_bias_[bucket_id].data | if_statement@545 (use_residual_) → if_statement@549 (metric_ == MetricType::METRIC_TYPE_L2SQR) | 当前参考未静态绑定；见下方边界说明 |

| L560 | std::numeric_limits&lt;float&gt;::max | for_statement@558 i &lt; offset → if_statement@559 (this-&gt;inner_ids_[bucket_id][i] == EMPTY_INNER_ID) | 当前参考未静态绑定；见下方边界说明 |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L566"></a>

## `BucketDataCell<QuantTmpl, IOTmpl>::FactoryComputer`

源码位置：`src/datacell/bucket_datacell.h:566–583`。

返回为当前 query 准备好的距离计算器。继续追踪 SetQuery/ProcessQuery；残差模式还保存 raw_query。创建计算器不等于已经遍历全部候选。

### 完整函数

```cpp
ComputerInterfacePtr
BucketDataCell<QuantTmpl, IOTmpl>::FactoryComputer(const void* query) {
    const auto* float_query = reinterpret_cast<const float*>(query);
    auto computer = this->quantizer_->FactoryComputer();
    auto comp = std::static_pointer_cast<Computer<QuantTmpl>>(computer);
    if (use_residual_) {
        comp->raw_query_.resize(this->quantizer_->GetDim());
        if (metric_ == MetricType::METRIC_TYPE_COSINE) {
            Normalize(float_query, comp->raw_query_.data(), this->quantizer_->GetDim());
        } else {
            memcpy(
                comp->raw_query_.data(), float_query, sizeof(float) * this->quantizer_->GetDim());
        }
        float_query = comp->raw_query_.data();
    }
    comp->SetQuery(float_query);
    return computer;
}
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L569 | this-&gt;quantizer_-&gt;FactoryComputer | 函数本体；短路求值/提前返回见源码 | [Quantizer::FactoryComputer · L179](quantizer_h.md#L179) |

| L570 | std::static_pointer_cast&lt;Computer&lt;QuantTmpl&gt;&gt; | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L572 | comp-&gt;raw_query_.resize | if_statement@571 (use_residual_) | 当前参考未静态绑定；见下方边界说明 |

| L572 | this-&gt;quantizer_-&gt;GetDim | if_statement@571 (use_residual_) | [Quantizer::GetDim · L340](quantizer_h.md#L340) |

| L574 | Normalize | if_statement@571 (use_residual_) → if_statement@573 (metric_ == MetricType::METRIC_TYPE_COSINE) | 当前参考未静态绑定；见下方边界说明 |

| L574 | comp-&gt;raw_query_.data | if_statement@571 (use_residual_) → if_statement@573 (metric_ == MetricType::METRIC_TYPE_COSINE) | 当前参考未静态绑定；见下方边界说明 |

| L574 | this-&gt;quantizer_-&gt;GetDim | if_statement@571 (use_residual_) → if_statement@573 (metric_ == MetricType::METRIC_TYPE_COSINE) | [Quantizer::GetDim · L340](quantizer_h.md#L340) |

| L576 | memcpy | if_statement@571 (use_residual_) → if_statement@573 (metric_ == MetricType::METRIC_TYPE_COSINE) [else 分支] | 当前参考未静态绑定；见下方边界说明 |

| L577 | comp-&gt;raw_query_.data | if_statement@571 (use_residual_) → if_statement@573 (metric_ == MetricType::METRIC_TYPE_COSINE) [else 分支] | 当前参考未静态绑定；见下方边界说明 |

| L577 | this-&gt;quantizer_-&gt;GetDim | if_statement@571 (use_residual_) → if_statement@573 (metric_ == MetricType::METRIC_TYPE_COSINE) [else 分支] | [Quantizer::GetDim · L340](quantizer_h.md#L340) |

| L579 | comp-&gt;raw_query_.data | if_statement@571 (use_residual_) | 当前参考未静态绑定；见下方边界说明 |

| L581 | comp-&gt;SetQuery | 函数本体；短路求值/提前返回见源码 | [Computer::SetQuery · L48](computer_h.md#L48)；[Computer&lt;TransformQuantizer&lt;QuantImpl, metric&gt;&gt;::SetQuery · L122](computer_h.md#L122) |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L586"></a>

## `BucketDataCell<QuantTmpl, IOTmpl>::Train`

源码位置：`src/datacell/bucket_datacell.h:586–610`。

这是状态改变函数。先看重复训练的提前返回，再看训练数据是否采样/归一化/变成残差，最后确认状态位在何处设置。分区 Train 与量化器 Train 不是同一个模型。

### 完整函数

```cpp
void
BucketDataCell<QuantTmpl, IOTmpl>::Train(const void* data, uint64_t count) {
    Vector<float> train_data_buffer(allocator_);
    if (use_residual_) {
        auto data_ptr = static_cast<const float*>(data);
        auto dim = this->quantizer_->GetDim();
        train_data_buffer.resize(count * dim);
        if (metric_ == MetricType::METRIC_TYPE_COSINE) {
            for (int i = 0; i < count; ++i) {
                Normalize(data_ptr + i * dim, train_data_buffer.data() + i * dim, dim);
            }
            data_ptr = train_data_buffer.data();
        }
        Vector<float> centroid(this->quantizer_->GetDim(), allocator_);
        auto buckets = strategy_->ClassifyDatas(data_ptr, count, 1, nullptr);
        for (int i = 0; i < count; ++i) {
            strategy_->GetCentroid(buckets[i], centroid);
            for (int j = 0; j < dim; ++j) {
                train_data_buffer[i * dim + j] = data_ptr[i * dim + j] - centroid[j];
            }
        }
        data = train_data_buffer.data();
    }
    this->quantizer_->Train(reinterpret_cast<const float*>(data), count);
}
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L591 | this-&gt;quantizer_-&gt;GetDim | if_statement@589 (use_residual_) | [Quantizer::GetDim · L340](quantizer_h.md#L340) |

| L592 | train_data_buffer.resize | if_statement@589 (use_residual_) | 当前参考未静态绑定；见下方边界说明 |

| L595 | Normalize | if_statement@589 (use_residual_) → if_statement@593 (metric_ == MetricType::METRIC_TYPE_COSINE) → for_statement@594 i &lt; count | 当前参考未静态绑定；见下方边界说明 |

| L595 | train_data_buffer.data | if_statement@589 (use_residual_) → if_statement@593 (metric_ == MetricType::METRIC_TYPE_COSINE) → for_statement@594 i &lt; count | 当前参考未静态绑定；见下方边界说明 |

| L597 | train_data_buffer.data | if_statement@589 (use_residual_) → if_statement@593 (metric_ == MetricType::METRIC_TYPE_COSINE) | 当前参考未静态绑定；见下方边界说明 |

| L599 | this-&gt;quantizer_-&gt;GetDim | if_statement@589 (use_residual_) | [Quantizer::GetDim · L340](quantizer_h.md#L340) |

| L600 | strategy_-&gt;ClassifyDatas | if_statement@589 (use_residual_) | 当前参考未静态绑定；见下方边界说明 |

| L602 | strategy_-&gt;GetCentroid | if_statement@589 (use_residual_) → for_statement@601 i &lt; count | 当前参考未静态绑定；见下方边界说明 |

| L607 | train_data_buffer.data | if_statement@589 (use_residual_) | 当前参考未静态绑定；见下方边界说明 |

| L609 | this-&gt;quantizer_-&gt;Train | 函数本体；短路求值/提前返回见源码 | [Quantizer::Train · L49](quantizer_h.md#L49) |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L613"></a>

## `BucketDataCell<QuantTmpl, IOTmpl>::encode_vector`

源码位置：`src/datacell/bucket_datacell.h:613–642`。

无残差时直接 EncodeOne；残差时取中心、可选归一化、向量减中心再编码。L2 还计算补偿项，查询时必须匹配处理。

### 完整函数

```cpp
void
BucketDataCell<QuantTmpl, IOTmpl>::encode_vector(const void* vector,
                                                 BucketIdType bucket_id,
                                                 uint8_t* codes,
                                                 float& res_score) {
    auto vector_ptr = static_cast<const float*>(vector);
    res_score = 0.0F;
    if (not use_residual_) {
        this->quantizer_->EncodeOne(vector_ptr, codes);
        return;
    }

    Vector<float> centroid(this->quantizer_->GetDim(), this->allocator_);
    Vector<float> sub_data(this->quantizer_->GetDim(), this->allocator_);
    Vector<float> normalize_data(this->quantizer_->GetDim(), this->allocator_);
    strategy_->GetCentroid(bucket_id, centroid);
    if (metric_ == MetricType::METRIC_TYPE_COSINE) {
        Normalize(vector_ptr, normalize_data.data(), quantizer_->GetDim());
        vector_ptr = normalize_data.data();
    }
    FP32Sub(vector_ptr, centroid.data(), sub_data.data(), quantizer_->GetDim());
    vector_ptr = sub_data.data();
    this->quantizer_->EncodeOne(vector_ptr, codes);
    if (metric_ == MetricType::METRIC_TYPE_L2SQR) {
        this->quantizer_->DecodeOne(codes, normalize_data.data());
        res_score =
            -2 * FP32ComputeIP(centroid.data(), normalize_data.data(), this->quantizer_->GetDim()) -
            FP32ComputeIP(centroid.data(), centroid.data(), this->quantizer_->GetDim());
    }
}
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L621 | this-&gt;quantizer_-&gt;EncodeOne | if_statement@620 (not use_residual_) | [Quantizer::EncodeOne · L77](quantizer_h.md#L77) |

| L625 | this-&gt;quantizer_-&gt;GetDim | 函数本体；短路求值/提前返回见源码 | [Quantizer::GetDim · L340](quantizer_h.md#L340) |

| L626 | this-&gt;quantizer_-&gt;GetDim | 函数本体；短路求值/提前返回见源码 | [Quantizer::GetDim · L340](quantizer_h.md#L340) |

| L627 | this-&gt;quantizer_-&gt;GetDim | 函数本体；短路求值/提前返回见源码 | [Quantizer::GetDim · L340](quantizer_h.md#L340) |

| L628 | strategy_-&gt;GetCentroid | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L630 | Normalize | if_statement@629 (metric_ == MetricType::METRIC_TYPE_COSINE) | 当前参考未静态绑定；见下方边界说明 |

| L630 | normalize_data.data | if_statement@629 (metric_ == MetricType::METRIC_TYPE_COSINE) | 当前参考未静态绑定；见下方边界说明 |

| L630 | quantizer_-&gt;GetDim | if_statement@629 (metric_ == MetricType::METRIC_TYPE_COSINE) | [Quantizer::GetDim · L340](quantizer_h.md#L340) |

| L631 | normalize_data.data | if_statement@629 (metric_ == MetricType::METRIC_TYPE_COSINE) | 当前参考未静态绑定；见下方边界说明 |

| L633 | FP32Sub | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L633 | centroid.data | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L633 | sub_data.data | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L633 | quantizer_-&gt;GetDim | 函数本体；短路求值/提前返回见源码 | [Quantizer::GetDim · L340](quantizer_h.md#L340) |

| L634 | sub_data.data | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L635 | this-&gt;quantizer_-&gt;EncodeOne | 函数本体；短路求值/提前返回见源码 | [Quantizer::EncodeOne · L77](quantizer_h.md#L77) |

| L637 | this-&gt;quantizer_-&gt;DecodeOne | if_statement@636 (metric_ == MetricType::METRIC_TYPE_L2SQR) | [Quantizer::DecodeOne · L116](quantizer_h.md#L116) |

| L637 | normalize_data.data | if_statement@636 (metric_ == MetricType::METRIC_TYPE_L2SQR) | 当前参考未静态绑定；见下方边界说明 |

| L639 | FP32ComputeIP | if_statement@636 (metric_ == MetricType::METRIC_TYPE_L2SQR) | 当前参考未静态绑定；见下方边界说明 |

| L639 | centroid.data | if_statement@636 (metric_ == MetricType::METRIC_TYPE_L2SQR) | 当前参考未静态绑定；见下方边界说明 |

| L639 | normalize_data.data | if_statement@636 (metric_ == MetricType::METRIC_TYPE_L2SQR) | 当前参考未静态绑定；见下方边界说明 |

| L639 | this-&gt;quantizer_-&gt;GetDim | if_statement@636 (metric_ == MetricType::METRIC_TYPE_L2SQR) | [Quantizer::GetDim · L340](quantizer_h.md#L340) |

| L640 | FP32ComputeIP | if_statement@636 (metric_ == MetricType::METRIC_TYPE_L2SQR) | 当前参考未静态绑定；见下方边界说明 |

| L640 | centroid.data | if_statement@636 (metric_ == MetricType::METRIC_TYPE_L2SQR) | 当前参考未静态绑定；见下方边界说明 |

| L640 | centroid.data | if_statement@636 (metric_ == MetricType::METRIC_TYPE_L2SQR) | 当前参考未静态绑定；见下方边界说明 |

| L640 | this-&gt;quantizer_-&gt;GetDim | if_statement@636 (metric_ == MetricType::METRIC_TYPE_L2SQR) | [Quantizer::GetDim · L340](quantizer_h.md#L340) |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L645"></a>

## `BucketDataCell<QuantTmpl, IOTmpl>::check_valid_bucket_capacity`

源码位置：`src/datacell/bucket_datacell.h:645–657`。

先从签名确认输入、返回值和 const/override，再按完整函数体的条件阅读调用点。下表保留了本函数的显式调用以及 lambda 中的调用；进入下层时用“候选实现”定位，未解析的对象由源码静态类型/运行时类型确认。

### 完整函数

```cpp
void
BucketDataCell<QuantTmpl, IOTmpl>::check_valid_bucket_capacity(uint64_t next_size,
                                                               bool need_resize) {
    if (need_resize && (next_size > MAX_BUCKET_ENTRIES ||
                        next_size > std::numeric_limits<size_t>::max() / sizeof(InnerIdType) ||
                        (use_residual_ && metric_ == MetricType::METRIC_TYPE_L2SQR &&
                         next_size > std::numeric_limits<size_t>::max() / sizeof(float)) ||
                        ZERO_FILL_BLOCK_ENTRIES > std::numeric_limits<uint64_t>::max() /
                                                      static_cast<uint64_t>(code_size_))) {
        throw VsagException(ErrorType::INVALID_ARGUMENT,
                            "invalid offset id for bucket: exceeds maximum bucket capacity");
    }
}
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L649 | std::numeric_limits&lt;size_t&gt;::max | if_statement@648 (need_resize && (next_size &gt; MAX_BUCKET_ENTRIES &#124;&#124; next_size &gt; std::numeric_limits&lt;size_t&gt;::max() / sizeof(InnerIdType) &#124;&#124; (use_residual_ && metric_ == MetricType::METRIC_TYPE_L2SQR && next_size &gt; std::numeric_limits&lt;size_t&gt;::max() / sizeof(float)) &#124;&#124; ZERO_FILL_BLOCK_ENTRIES &gt; std::numeric_limits&lt;uint64_t&gt;::max() / static_cast&lt;uint64_t&gt;(code_size_))) | 当前参考未静态绑定；见下方边界说明 |

| L651 | std::numeric_limits&lt;size_t&gt;::max | if_statement@648 (need_resize && (next_size &gt; MAX_BUCKET_ENTRIES &#124;&#124; next_size &gt; std::numeric_limits&lt;size_t&gt;::max() / sizeof(InnerIdType) &#124;&#124; (use_residual_ && metric_ == MetricType::METRIC_TYPE_L2SQR && next_size &gt; std::numeric_limits&lt;size_t&gt;::max() / sizeof(float)) &#124;&#124; ZERO_FILL_BLOCK_ENTRIES &gt; std::numeric_limits&lt;uint64_t&gt;::max() / static_cast&lt;uint64_t&gt;(code_size_))) | 当前参考未静态绑定；见下方边界说明 |

| L652 | std::numeric_limits&lt;uint64_t&gt;::max | if_statement@648 (need_resize && (next_size &gt; MAX_BUCKET_ENTRIES &#124;&#124; next_size &gt; std::numeric_limits&lt;size_t&gt;::max() / sizeof(InnerIdType) &#124;&#124; (use_residual_ && metric_ == MetricType::METRIC_TYPE_L2SQR && next_size &gt; std::numeric_limits&lt;size_t&gt;::max() / sizeof(float)) &#124;&#124; ZERO_FILL_BLOCK_ENTRIES &gt; std::numeric_limits&lt;uint64_t&gt;::max() / static_cast&lt;uint64_t&gt;(code_size_))) | 当前参考未静态绑定；见下方边界说明 |

| L654 | VsagException | if_statement@648 (need_resize && (next_size &gt; MAX_BUCKET_ENTRIES &#124;&#124; next_size &gt; std::numeric_limits&lt;size_t&gt;::max() / sizeof(InnerIdType) &#124;&#124; (use_residual_ && metric_ == MetricType::METRIC_TYPE_L2SQR && next_size &gt; std::numeric_limits&lt;size_t&gt;::max() / sizeof(float)) &#124;&#124; ZERO_FILL_BLOCK_ENTRIES &gt; std::numeric_limits&lt;uint64_t&gt;::max() / static_cast&lt;uint64_t&gt;(code_size_))) | 当前参考未静态绑定；见下方边界说明 |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L660"></a>

## `BucketDataCell<QuantTmpl, IOTmpl>::InsertVector`

源码位置：`src/datacell/bucket_datacell.h:660–700`。

先编码再在桶锁内获取追加 offset、检查容量、写编码并发布 posting ID/桶大小。返回的是桶内 offset，不是 origin 或用户 label。

### 完整函数

```cpp
InnerIdType
BucketDataCell<QuantTmpl, IOTmpl>::InsertVector(const void* vector,
                                                BucketIdType bucket_id,
                                                InnerIdType inner_id) {
    check_valid_bucket_id(bucket_id);
    if (inner_id == EMPTY_INNER_ID) {
        throw VsagException(ErrorType::INVALID_ARGUMENT, "invalid inner id for bucket");
    }

    InnerIdType offset_id;
    float res_score = 0.0F;
    ByteBuffer codes(static_cast<uint64_t>(code_size_), this->allocator_);
    encode_vector(vector, bucket_id, codes.data, res_score);
    {
        std::unique_lock lock(this->bucket_mutexes_[bucket_id]);
        offset_id = this->bucket_sizes_[bucket_id];
        if (offset_id >= std::numeric_limits<InnerIdType>::max() ||
            static_cast<uint64_t>(offset_id) >
                std::numeric_limits<uint64_t>::max() / static_cast<uint64_t>(code_size_)) {
            throw VsagException(ErrorType::INVALID_ARGUMENT, "invalid offset id for bucket");
        }
        auto next_size = static_cast<uint64_t>(offset_id) + 1;
        check_valid_bucket_capacity(next_size, this->inner_ids_[bucket_id].size() < next_size);
        this->datas_[bucket_id].Write(
            codes.data,
            code_size_,
            static_cast<uint64_t>(offset_id) * static_cast<uint64_t>(code_size_));
        if (this->inner_ids_[bucket_id].size() < next_size) {
            this->inner_ids_[bucket_id].resize(next_size, EMPTY_INNER_ID);
            if (use_residual_ && metric_ == MetricType::METRIC_TYPE_L2SQR) {
                this->residual_bias_[bucket_id].resize(next_size, 0.0F);
            }
        }
        inner_ids_[bucket_id][offset_id] = inner_id;
        if (use_residual_ && metric_ == MetricType::METRIC_TYPE_L2SQR) {
            residual_bias_[bucket_id][offset_id] = res_score;
        }
        this->bucket_sizes_[bucket_id] = static_cast<InnerIdType>(next_size);
    }
    return offset_id;
}
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L664 | check_valid_bucket_id | 函数本体；短路求值/提前返回见源码 | [BucketDataCell::check_valid_bucket_id · L244](bucket_datacell_h.md#L244) |

| L666 | VsagException | if_statement@665 (inner_id == EMPTY_INNER_ID) | 当前参考未静态绑定；见下方边界说明 |

| L672 | encode_vector | 函数本体；短路求值/提前返回见源码 | [BucketDataCell&lt;QuantTmpl, IOTmpl&gt;::encode_vector · L613](bucket_datacell_h.md#L613) |

| L676 | std::numeric_limits&lt;InnerIdType&gt;::max | if_statement@676 (offset_id &gt;= std::numeric_limits&lt;InnerIdType&gt;::max() &#124;&#124; static_cast&lt;uint64_t&gt;(offset_id) &gt; std::numeric_limits&lt;uint64_t&gt;::max() / static_cast&lt;uint64_t&gt;(code_size_)) | 当前参考未静态绑定；见下方边界说明 |

| L678 | std::numeric_limits&lt;uint64_t&gt;::max | if_statement@676 (offset_id &gt;= std::numeric_limits&lt;InnerIdType&gt;::max() &#124;&#124; static_cast&lt;uint64_t&gt;(offset_id) &gt; std::numeric_limits&lt;uint64_t&gt;::max() / static_cast&lt;uint64_t&gt;(code_size_)) | 当前参考未静态绑定；见下方边界说明 |

| L679 | VsagException | if_statement@676 (offset_id &gt;= std::numeric_limits&lt;InnerIdType&gt;::max() &#124;&#124; static_cast&lt;uint64_t&gt;(offset_id) &gt; std::numeric_limits&lt;uint64_t&gt;::max() / static_cast&lt;uint64_t&gt;(code_size_)) | 当前参考未静态绑定；见下方边界说明 |

| L682 | check_valid_bucket_capacity | 函数本体；短路求值/提前返回见源码 | [BucketDataCell&lt;QuantTmpl, IOTmpl&gt;::check_valid_bucket_capacity · L645](bucket_datacell_h.md#L645) |

| L682 | this-&gt;inner_ids_[bucket_id].size | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L683 | this-&gt;datas_[bucket_id].Write | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L687 | this-&gt;inner_ids_[bucket_id].size | if_statement@687 (this-&gt;inner_ids_[bucket_id].size() &lt; next_size) | 当前参考未静态绑定；见下方边界说明 |

| L688 | this-&gt;inner_ids_[bucket_id].resize | if_statement@687 (this-&gt;inner_ids_[bucket_id].size() &lt; next_size) | 当前参考未静态绑定；见下方边界说明 |

| L690 | this-&gt;residual_bias_[bucket_id].resize | if_statement@687 (this-&gt;inner_ids_[bucket_id].size() &lt; next_size) → if_statement@689 (use_residual_ && metric_ == MetricType::METRIC_TYPE_L2SQR) | 当前参考未静态绑定；见下方边界说明 |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L703"></a>

## `BucketDataCell<QuantTmpl, IOTmpl>::BatchInsertVector`

源码位置：`src/datacell/bucket_datacell.h:703–815`。

先从签名确认输入、返回值和 const/override，再按完整函数体的条件阅读调用点。下表保留了本函数的显式调用以及 lambda 中的调用；进入下层时用“候选实现”定位，未解析的对象由源码静态类型/运行时类型确认。

### 完整函数

```cpp
void
BucketDataCell<QuantTmpl, IOTmpl>::BatchInsertVector(const void* vectors,
                                                     const BucketIdType* bucket_ids,
                                                     const InnerIdType* inner_ids,
                                                     InnerIdType count,
                                                     InnerIdType* out_offsets) {
    if (count == 0) {
        return;
    }
    if (vectors == nullptr or bucket_ids == nullptr or inner_ids == nullptr or
        out_offsets == nullptr) {
        throw VsagException(ErrorType::INVALID_ARGUMENT,
                            "batch bucket insert requires non-null inputs and output");
    }
    if (this->bucket_count_ <= 0 or input_dim_ == 0 or code_size_ == 0 or
        (use_residual_ and strategy_ == nullptr)) {
        throw VsagException(ErrorType::INVALID_ARGUMENT, "invalid batch bucket insert size");
    }
    const auto bucket_count = static_cast<uint64_t>(this->bucket_count_);
    const auto batch_count = static_cast<uint64_t>(count);
    const auto max_allocation_size = std::numeric_limits<size_t>::max();
    if (bucket_count == std::numeric_limits<uint64_t>::max() or
        bucket_count + 1 > max_allocation_size / sizeof(uint64_t) or
        batch_count > max_allocation_size / sizeof(uint64_t) or
        batch_count > max_allocation_size / sizeof(InnerIdType) or
        batch_count > max_allocation_size / sizeof(float) / input_dim_) {
        throw VsagException(ErrorType::INVALID_ARGUMENT, "invalid batch bucket insert size");
    }

    Vector<uint64_t> bucket_counts(bucket_count, 0, this->allocator_);
    for (uint64_t i = 0; i < batch_count; ++i) {
        check_valid_bucket_id(bucket_ids[i]);
        if (inner_ids[i] == EMPTY_INNER_ID) {
            throw VsagException(ErrorType::INVALID_ARGUMENT, "invalid inner id for bucket");
        }
        ++bucket_counts[bucket_ids[i]];
    }

    Vector<uint64_t> bucket_begins(bucket_count + 1, 0, this->allocator_);
    for (uint64_t bucket_id = 0; bucket_id < bucket_count; ++bucket_id) {
        bucket_begins[bucket_id + 1] = bucket_begins[bucket_id] + bucket_counts[bucket_id];
    }
    Vector<uint64_t> next_positions(
        bucket_begins.begin(), bucket_begins.end() - 1, this->allocator_);
    Vector<InnerIdType> order(batch_count, 0, this->allocator_);
    for (uint64_t i = 0; i < batch_count; ++i) {
        const auto position = next_positions[bucket_ids[i]]++;
        order[position] = static_cast<InnerIdType>(i);
    }

    const auto* float_vectors = static_cast<const float*>(vectors);
    for (uint64_t bucket_id = 0; bucket_id < bucket_count; ++bucket_id) {
        const auto bucket_insert_count = bucket_counts[bucket_id];
        if (bucket_insert_count == 0) {
            continue;
        }
        if (bucket_insert_count > max_allocation_size / static_cast<uint64_t>(code_size_)) {
            throw VsagException(ErrorType::INVALID_ARGUMENT, "invalid batch bucket insert size");
        }

        const auto group_begin = bucket_begins[bucket_id];
        ByteBuffer codes(bucket_insert_count * static_cast<uint64_t>(code_size_), this->allocator_);
        Vector<float> residual_scores(this->allocator_);
        if (use_residual_ and metric_ == MetricType::METRIC_TYPE_L2SQR) {
            residual_scores.resize(bucket_insert_count);
        }
        for (uint64_t local_index = 0; local_index < bucket_insert_count; ++local_index) {
            const auto position = group_begin + local_index;
            const auto input_index = order[position];
            float residual_score = 0.0F;
            encode_vector(float_vectors + input_index * input_dim_,
                          static_cast<BucketIdType>(bucket_id),
                          codes.data + local_index * static_cast<uint64_t>(code_size_),
                          residual_score);
            if (not residual_scores.empty()) {
                residual_scores[local_index] = residual_score;
            }
        }

        std::unique_lock lock(this->bucket_mutexes_[bucket_id]);
        const auto append_begin = static_cast<uint64_t>(this->bucket_sizes_[bucket_id]);
        if (bucket_insert_count >
            static_cast<uint64_t>(std::numeric_limits<InnerIdType>::max()) - append_begin) {
            throw VsagException(ErrorType::INVALID_ARGUMENT, "invalid offset id for bucket");
        }
        const auto next_size = append_begin + bucket_insert_count;
        if (next_size > std::numeric_limits<uint64_t>::max() / static_cast<uint64_t>(code_size_)) {
            throw VsagException(ErrorType::INVALID_ARGUMENT, "invalid offset id for bucket");
        }
        check_valid_bucket_capacity(next_size, this->inner_ids_[bucket_id].size() < next_size);
        this->datas_[bucket_id].Write(codes.data,
                                      bucket_insert_count * static_cast<uint64_t>(code_size_),
                                      append_begin * static_cast<uint64_t>(code_size_));
        if (this->inner_ids_[bucket_id].size() < next_size) {
            this->inner_ids_[bucket_id].resize(next_size, EMPTY_INNER_ID);
        }
        if (not residual_scores.empty() and this->residual_bias_[bucket_id].size() < next_size) {
            this->residual_bias_[bucket_id].resize(next_size, 0.0F);
        }
        for (uint64_t local_index = 0; local_index < bucket_insert_count; ++local_index) {
            const auto position = group_begin + local_index;
            const auto input_index = order[position];
            const auto offset = append_begin + local_index;
            this->inner_ids_[bucket_id][offset] = inner_ids[input_index];
            if (not residual_scores.empty()) {
                this->residual_bias_[bucket_id][offset] = residual_scores[local_index];
            }
            out_offsets[input_index] = static_cast<InnerIdType>(offset);
        }
        this->bucket_sizes_[bucket_id] =
            static_cast<InnerIdType>(append_begin + bucket_insert_count);
    }
}
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L714 | VsagException | if_statement@712 (vectors == nullptr or bucket_ids == nullptr or inner_ids == nullptr or out_offsets == nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L719 | VsagException | if_statement@717 (this-&gt;bucket_count_ &lt;= 0 or input_dim_ == 0 or code_size_ == 0 or (use_residual_ and strategy_ == nullptr)) | 当前参考未静态绑定；见下方边界说明 |

| L723 | std::numeric_limits&lt;size_t&gt;::max | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L724 | std::numeric_limits&lt;uint64_t&gt;::max | if_statement@724 (bucket_count == std::numeric_limits&lt;uint64_t&gt;::max() or bucket_count + 1 &gt; max_allocation_size / sizeof(uint64_t) or batch_count &gt; max_allocation_size / sizeof(uint64_t) or batch_count &gt; max_allocation_size / sizeof(InnerIdType) or batch_count &gt; max_allocation_size / sizeof(float) / input_dim_) | 当前参考未静态绑定；见下方边界说明 |

| L729 | VsagException | if_statement@724 (bucket_count == std::numeric_limits&lt;uint64_t&gt;::max() or bucket_count + 1 &gt; max_allocation_size / sizeof(uint64_t) or batch_count &gt; max_allocation_size / sizeof(uint64_t) or batch_count &gt; max_allocation_size / sizeof(InnerIdType) or batch_count &gt; max_allocation_size / sizeof(float) / input_dim_) | 当前参考未静态绑定；见下方边界说明 |

| L734 | check_valid_bucket_id | for_statement@733 i &lt; batch_count | [BucketDataCell::check_valid_bucket_id · L244](bucket_datacell_h.md#L244) |

| L736 | VsagException | for_statement@733 i &lt; batch_count → if_statement@735 (inner_ids[i] == EMPTY_INNER_ID) | 当前参考未静态绑定；见下方边界说明 |

| L746 | bucket_begins.begin | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L746 | bucket_begins.end | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L760 | VsagException | for_statement@754 bucket_id &lt; bucket_count → if_statement@759 (bucket_insert_count &gt; max_allocation_size / static_cast&lt;uint64_t&gt;(code_size_)) | 当前参考未静态绑定；见下方边界说明 |

| L767 | residual_scores.resize | for_statement@754 bucket_id &lt; bucket_count → if_statement@766 (use_residual_ and metric_ == MetricType::METRIC_TYPE_L2SQR) | 当前参考未静态绑定；见下方边界说明 |

| L773 | encode_vector | for_statement@754 bucket_id &lt; bucket_count → for_statement@769 local_index &lt; bucket_insert_count | [BucketDataCell&lt;QuantTmpl, IOTmpl&gt;::encode_vector · L613](bucket_datacell_h.md#L613) |

| L777 | residual_scores.empty | for_statement@754 bucket_id &lt; bucket_count → for_statement@769 local_index &lt; bucket_insert_count → if_statement@777 (not residual_scores.empty()) | 当前参考未静态绑定；见下方边界说明 |

| L785 | std::numeric_limits&lt;InnerIdType&gt;::max | for_statement@754 bucket_id &lt; bucket_count → if_statement@784 (bucket_insert_count &gt; static_cast&lt;uint64_t&gt;(std::numeric_limits&lt;InnerIdType&gt;::max()) - append_begin) | 当前参考未静态绑定；见下方边界说明 |

| L786 | VsagException | for_statement@754 bucket_id &lt; bucket_count → if_statement@784 (bucket_insert_count &gt; static_cast&lt;uint64_t&gt;(std::numeric_limits&lt;InnerIdType&gt;::max()) - append_begin) | 当前参考未静态绑定；见下方边界说明 |

| L789 | std::numeric_limits&lt;uint64_t&gt;::max | for_statement@754 bucket_id &lt; bucket_count → if_statement@789 (next_size &gt; std::numeric_limits&lt;uint64_t&gt;::max() / static_cast&lt;uint64_t&gt;(code_size_)) | 当前参考未静态绑定；见下方边界说明 |

| L790 | VsagException | for_statement@754 bucket_id &lt; bucket_count → if_statement@789 (next_size &gt; std::numeric_limits&lt;uint64_t&gt;::max() / static_cast&lt;uint64_t&gt;(code_size_)) | 当前参考未静态绑定；见下方边界说明 |

| L792 | check_valid_bucket_capacity | for_statement@754 bucket_id &lt; bucket_count | [BucketDataCell&lt;QuantTmpl, IOTmpl&gt;::check_valid_bucket_capacity · L645](bucket_datacell_h.md#L645) |

| L792 | this-&gt;inner_ids_[bucket_id].size | for_statement@754 bucket_id &lt; bucket_count | 当前参考未静态绑定；见下方边界说明 |

| L793 | this-&gt;datas_[bucket_id].Write | for_statement@754 bucket_id &lt; bucket_count | 当前参考未静态绑定；见下方边界说明 |

| L796 | this-&gt;inner_ids_[bucket_id].size | for_statement@754 bucket_id &lt; bucket_count → if_statement@796 (this-&gt;inner_ids_[bucket_id].size() &lt; next_size) | 当前参考未静态绑定；见下方边界说明 |

| L797 | this-&gt;inner_ids_[bucket_id].resize | for_statement@754 bucket_id &lt; bucket_count → if_statement@796 (this-&gt;inner_ids_[bucket_id].size() &lt; next_size) | 当前参考未静态绑定；见下方边界说明 |

| L799 | residual_scores.empty | for_statement@754 bucket_id &lt; bucket_count → if_statement@799 (not residual_scores.empty() and this-&gt;residual_bias_[bucket_id].size() &lt; next_size) | 当前参考未静态绑定；见下方边界说明 |

| L799 | this-&gt;residual_bias_[bucket_id].size | for_statement@754 bucket_id &lt; bucket_count → if_statement@799 (not residual_scores.empty() and this-&gt;residual_bias_[bucket_id].size() &lt; next_size) | 当前参考未静态绑定；见下方边界说明 |

| L800 | this-&gt;residual_bias_[bucket_id].resize | for_statement@754 bucket_id &lt; bucket_count → if_statement@799 (not residual_scores.empty() and this-&gt;residual_bias_[bucket_id].size() &lt; next_size) | 当前参考未静态绑定；见下方边界说明 |

| L807 | residual_scores.empty | for_statement@754 bucket_id &lt; bucket_count → for_statement@802 local_index &lt; bucket_insert_count → if_statement@807 (not residual_scores.empty()) | 当前参考未静态绑定；见下方边界说明 |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L818"></a>

## `BucketDataCell<QuantTmpl, IOTmpl>::InsertVectorWithOffset`

源码位置：`src/datacell/bucket_datacell.h:818–880`。

先从签名确认输入、返回值和 const/override，再按完整函数体的条件阅读调用点。下表保留了本函数的显式调用以及 lambda 中的调用；进入下层时用“候选实现”定位，未解析的对象由源码静态类型/运行时类型确认。

### 完整函数

```cpp
void
BucketDataCell<QuantTmpl, IOTmpl>::InsertVectorWithOffset(const void* vector,
                                                          BucketIdType bucket_id,
                                                          InnerIdType inner_id,
                                                          InnerIdType offset_id) {
    check_valid_bucket_id(bucket_id);
    if (inner_id == EMPTY_INNER_ID) {
        throw VsagException(ErrorType::INVALID_ARGUMENT, "invalid inner id for bucket");
    }
    if constexpr (std::is_signed_v<InnerIdType>) {
        if (offset_id < 0) {
            throw VsagException(ErrorType::INVALID_ARGUMENT, "invalid offset id for bucket");
        }
    }
    if (offset_id >= std::numeric_limits<InnerIdType>::max() ||
        static_cast<uint64_t>(offset_id) >
            std::numeric_limits<uint64_t>::max() / static_cast<uint64_t>(code_size_)) {
        throw VsagException(ErrorType::INVALID_ARGUMENT, "invalid offset id for bucket");
    }

    float res_score = 0.0F;
    ByteBuffer codes(static_cast<uint64_t>(code_size_), this->allocator_);
    encode_vector(vector, bucket_id, codes.data, res_score);
    {
        std::unique_lock lock(this->bucket_mutexes_[bucket_id]);
        auto next_size = static_cast<uint64_t>(offset_id) + 1;
        auto need_resize = this->inner_ids_[bucket_id].size() < next_size;
        check_valid_bucket_capacity(next_size, need_resize);
        if (need_resize) {
            this->inner_ids_[bucket_id].resize(next_size, EMPTY_INNER_ID);
            if (use_residual_ && metric_ == MetricType::METRIC_TYPE_L2SQR) {
                this->residual_bias_[bucket_id].resize(next_size, 0.0F);
            }
        }
        if (offset_id > this->bucket_sizes_[bucket_id]) {
            auto zero_fill_entries = std::min<uint64_t>(
                static_cast<uint64_t>(offset_id - this->bucket_sizes_[bucket_id]),
                ZERO_FILL_BLOCK_ENTRIES);
            auto zero_fill_bytes = zero_fill_entries * static_cast<uint64_t>(code_size_);
            ByteBuffer zero_codes(zero_fill_bytes, this->allocator_);
            std::fill_n(zero_codes.data, zero_fill_bytes, 0);
            for (auto hole_offset = this->bucket_sizes_[bucket_id]; hole_offset < offset_id;) {
                auto fill_entries = std::min<uint64_t>(
                    static_cast<uint64_t>(offset_id - hole_offset), ZERO_FILL_BLOCK_ENTRIES);
                this->datas_[bucket_id].Write(
                    zero_codes.data,
                    fill_entries * static_cast<uint64_t>(code_size_),
                    static_cast<uint64_t>(hole_offset) * static_cast<uint64_t>(code_size_));
                hole_offset += static_cast<InnerIdType>(fill_entries);
            }
        }
        this->datas_[bucket_id].Write(
            codes.data,
            code_size_,
            static_cast<uint64_t>(offset_id) * static_cast<uint64_t>(code_size_));
        this->inner_ids_[bucket_id][offset_id] = inner_id;
        if (use_residual_ && metric_ == MetricType::METRIC_TYPE_L2SQR) {
            this->residual_bias_[bucket_id][offset_id] = res_score;
        }
        this->bucket_sizes_[bucket_id] =
            std::max(this->bucket_sizes_[bucket_id], static_cast<InnerIdType>(next_size));
    }
}
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L823 | check_valid_bucket_id | 函数本体；短路求值/提前返回见源码 | [BucketDataCell::check_valid_bucket_id · L244](bucket_datacell_h.md#L244) |

| L825 | VsagException | if_statement@824 (inner_id == EMPTY_INNER_ID) | 当前参考未静态绑定；见下方边界说明 |

| L829 | VsagException | if_statement@827 (std::is_signed_v&lt;InnerIdType&gt;) → if_statement@828 (offset_id &lt; 0) | 当前参考未静态绑定；见下方边界说明 |

| L832 | std::numeric_limits&lt;InnerIdType&gt;::max | if_statement@832 (offset_id &gt;= std::numeric_limits&lt;InnerIdType&gt;::max() &#124;&#124; static_cast&lt;uint64_t&gt;(offset_id) &gt; std::numeric_limits&lt;uint64_t&gt;::max() / static_cast&lt;uint64_t&gt;(code_size_)) | 当前参考未静态绑定；见下方边界说明 |

| L834 | std::numeric_limits&lt;uint64_t&gt;::max | if_statement@832 (offset_id &gt;= std::numeric_limits&lt;InnerIdType&gt;::max() &#124;&#124; static_cast&lt;uint64_t&gt;(offset_id) &gt; std::numeric_limits&lt;uint64_t&gt;::max() / static_cast&lt;uint64_t&gt;(code_size_)) | 当前参考未静态绑定；见下方边界说明 |

| L835 | VsagException | if_statement@832 (offset_id &gt;= std::numeric_limits&lt;InnerIdType&gt;::max() &#124;&#124; static_cast&lt;uint64_t&gt;(offset_id) &gt; std::numeric_limits&lt;uint64_t&gt;::max() / static_cast&lt;uint64_t&gt;(code_size_)) | 当前参考未静态绑定；见下方边界说明 |

| L840 | encode_vector | 函数本体；短路求值/提前返回见源码 | [BucketDataCell&lt;QuantTmpl, IOTmpl&gt;::encode_vector · L613](bucket_datacell_h.md#L613) |

| L844 | this-&gt;inner_ids_[bucket_id].size | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L845 | check_valid_bucket_capacity | 函数本体；短路求值/提前返回见源码 | [BucketDataCell&lt;QuantTmpl, IOTmpl&gt;::check_valid_bucket_capacity · L645](bucket_datacell_h.md#L645) |

| L847 | this-&gt;inner_ids_[bucket_id].resize | if_statement@846 (need_resize) | 当前参考未静态绑定；见下方边界说明 |

| L849 | this-&gt;residual_bias_[bucket_id].resize | if_statement@846 (need_resize) → if_statement@848 (use_residual_ && metric_ == MetricType::METRIC_TYPE_L2SQR) | 当前参考未静态绑定；见下方边界说明 |

| L853 | std::min&lt;uint64_t&gt; | if_statement@852 (offset_id &gt; this-&gt;bucket_sizes_[bucket_id]) | 当前参考未静态绑定；见下方边界说明 |

| L858 | std::fill_n | if_statement@852 (offset_id &gt; this-&gt;bucket_sizes_[bucket_id]) | 当前参考未静态绑定；见下方边界说明 |

| L860 | std::min&lt;uint64_t&gt; | if_statement@852 (offset_id &gt; this-&gt;bucket_sizes_[bucket_id]) → for_statement@859 hole_offset &lt; offset_id | 当前参考未静态绑定；见下方边界说明 |

| L862 | this-&gt;datas_[bucket_id].Write | if_statement@852 (offset_id &gt; this-&gt;bucket_sizes_[bucket_id]) → for_statement@859 hole_offset &lt; offset_id | 当前参考未静态绑定；见下方边界说明 |

| L869 | this-&gt;datas_[bucket_id].Write | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L878 | std::max | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L883"></a>

## `BucketDataCell<QuantTmpl, IOTmpl>::Serialize`

源码位置：`src/datacell/bucket_datacell.h:883–895`。

先从签名确认输入、返回值和 const/override，再按完整函数体的条件阅读调用点。下表保留了本函数的显式调用以及 lambda 中的调用；进入下层时用“候选实现”定位，未解析的对象由源码静态类型/运行时类型确认。

### 完整函数

```cpp
void
BucketDataCell<QuantTmpl, IOTmpl>::Serialize(StreamWriter& writer) {
    BucketInterface::Serialize(writer);
    quantizer_->Serialize(writer);
    for (BucketIdType i = 0; i < this->bucket_count_; ++i) {
        datas_[i].Serialize(writer);
        StreamWriter::WriteVector(writer, inner_ids_[i]);
        if (use_residual_) {
            StreamWriter::WriteVector(writer, residual_bias_[i]);
        }
    }
    StreamWriter::WriteVector(writer, this->bucket_sizes_);
}
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L885 | BucketInterface::Serialize | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L886 | quantizer_-&gt;Serialize | 函数本体；短路求值/提前返回见源码 | [Quantizer::Serialize · L161](quantizer_h.md#L161) |

| L888 | datas_[i].Serialize | for_statement@887 i &lt; this-&gt;bucket_count_ | 当前参考未静态绑定；见下方边界说明 |

| L889 | StreamWriter::WriteVector | for_statement@887 i &lt; this-&gt;bucket_count_ | 当前参考未静态绑定；见下方边界说明 |

| L891 | StreamWriter::WriteVector | for_statement@887 i &lt; this-&gt;bucket_count_ → if_statement@890 (use_residual_) | 当前参考未静态绑定；见下方边界说明 |

| L894 | StreamWriter::WriteVector | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L898"></a>

## `BucketDataCell<QuantTmpl, IOTmpl>::Deserialize`

源码位置：`src/datacell/bucket_datacell.h:898–931`。

先从签名确认输入、返回值和 const/override，再按完整函数体的条件阅读调用点。下表保留了本函数的显式调用以及 lambda 中的调用；进入下层时用“候选实现”定位，未解析的对象由源码静态类型/运行时类型确认。

### 完整函数

```cpp
void
BucketDataCell<QuantTmpl, IOTmpl>::Deserialize(LvalueOrRvalue<StreamReader> reader) {
    BucketInterface::Deserialize(reader);
    quantizer_->Deserialize(reader);
    this->backend_ =
        QuantizerDistanceBackend<QuantTmpl>::Get(static_cast<const QuantTmpl&>(*quantizer_));
    for (BucketIdType i = 0; i < this->bucket_count_; ++i) {
        datas_[i].Deserialize(reader);
        StreamReader::ReadVector(reader, inner_ids_[i]);
        if (use_residual_) {
            StreamReader::ReadVector(reader, residual_bias_[i]);
        }
    }
    StreamReader::ReadVector(reader, this->bucket_sizes_);
    if (this->bucket_sizes_.size() != static_cast<uint64_t>(this->bucket_count_)) {
        throw VsagException(ErrorType::INVALID_BINARY,
                            "serialized bucket size vector does not match bucket count");
    }
    for (BucketIdType i = 0; i < this->bucket_count_; ++i) {
        const auto bucket_size = static_cast<uint64_t>(this->bucket_sizes_[i]);
        if (this->inner_ids_[i].size() < bucket_size) {
            throw VsagException(
                ErrorType::INVALID_BINARY,
                fmt::format("serialized bucket {} inner id count is smaller than bucket size", i));
        }
        if (this->use_residual_ and this->metric_ == MetricType::METRIC_TYPE_L2SQR and
            this->residual_bias_[i].size() < bucket_size) {
            throw VsagException(
                ErrorType::INVALID_BINARY,
                fmt::format("serialized bucket {} residual bias count is smaller than bucket size",
                            i));
        }
    }
}
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L900 | BucketInterface::Deserialize | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L901 | quantizer_-&gt;Deserialize | 函数本体；短路求值/提前返回见源码 | [Quantizer::Deserialize · L170](quantizer_h.md#L170) |

| L903 | QuantizerDistanceBackend&lt;QuantTmpl&gt;::Get | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L905 | datas_[i].Deserialize | for_statement@904 i &lt; this-&gt;bucket_count_ | 当前参考未静态绑定；见下方边界说明 |

| L906 | StreamReader::ReadVector | for_statement@904 i &lt; this-&gt;bucket_count_ | 当前参考未静态绑定；见下方边界说明 |

| L908 | StreamReader::ReadVector | for_statement@904 i &lt; this-&gt;bucket_count_ → if_statement@907 (use_residual_) | 当前参考未静态绑定；见下方边界说明 |

| L911 | StreamReader::ReadVector | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L912 | this-&gt;bucket_sizes_.size | if_statement@912 (this-&gt;bucket_sizes_.size() != static_cast&lt;uint64_t&gt;(this-&gt;bucket_count_)) | 当前参考未静态绑定；见下方边界说明 |

| L913 | VsagException | if_statement@912 (this-&gt;bucket_sizes_.size() != static_cast&lt;uint64_t&gt;(this-&gt;bucket_count_)) | 当前参考未静态绑定；见下方边界说明 |

| L918 | this-&gt;inner_ids_[i].size | for_statement@916 i &lt; this-&gt;bucket_count_ → if_statement@918 (this-&gt;inner_ids_[i].size() &lt; bucket_size) | 当前参考未静态绑定；见下方边界说明 |

| L919 | VsagException | for_statement@916 i &lt; this-&gt;bucket_count_ → if_statement@918 (this-&gt;inner_ids_[i].size() &lt; bucket_size) | 当前参考未静态绑定；见下方边界说明 |

| L921 | fmt::format | for_statement@916 i &lt; this-&gt;bucket_count_ → if_statement@918 (this-&gt;inner_ids_[i].size() &lt; bucket_size) | 当前参考未静态绑定；见下方边界说明 |

| L924 | this-&gt;residual_bias_[i].size | for_statement@916 i &lt; this-&gt;bucket_count_ → if_statement@923 (this-&gt;use_residual_ and this-&gt;metric_ == MetricType::METRIC_TYPE_L2SQR and this-&gt;residual_bias_[i].size() &lt; bucket_size) | 当前参考未静态绑定；见下方边界说明 |

| L925 | VsagException | for_statement@916 i &lt; this-&gt;bucket_count_ → if_statement@923 (this-&gt;use_residual_ and this-&gt;metric_ == MetricType::METRIC_TYPE_L2SQR and this-&gt;residual_bias_[i].size() &lt; bucket_size) | 当前参考未静态绑定；见下方边界说明 |

| L927 | fmt::format | for_statement@916 i &lt; this-&gt;bucket_count_ → if_statement@923 (this-&gt;use_residual_ and this-&gt;metric_ == MetricType::METRIC_TYPE_L2SQR and this-&gt;residual_bias_[i].size() &lt; bucket_size) | 当前参考未静态绑定；见下方边界说明 |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L934"></a>

## `BucketDataCell<QuantTmpl, IOTmpl>::package_fastscan`

源码位置：`src/datacell/bucket_datacell.h:934–955`。

先从签名确认输入、返回值和 const/override，再按完整函数体的条件阅读调用点。下表保留了本函数的显式调用以及 lambda 中的调用；进入下层时用“候选实现”定位，未解析的对象由源码静态类型/运行时类型确认。

### 完整函数

```cpp
void
BucketDataCell<QuantTmpl, IOTmpl>::package_fastscan() {
    ByteBuffer buffer(code_size_ * 32, this->allocator_);
    for (int64_t i = 0; i < this->bucket_count_; ++i) {
        auto bucket_size = this->bucket_sizes_[i];
        if (bucket_size == 0) {
            continue;
        }
        auto lease = this->datas_[i].Acquire(0, code_size_ * bucket_size);
        const auto* codes = lease.Data();
        InnerIdType begin = 0;
        while (begin < bucket_size) {
            auto valid_size = bucket_size - begin;
            if (valid_size > 32) {
                valid_size = 32;
            }
            quantizer_->Package32(codes + begin * code_size_, buffer.data, valid_size);
            this->datas_[i].Write(buffer.data, code_size_ * 32, begin * code_size_);
            begin += 32;
        }
    }
}
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L942 | this-&gt;datas_[i].Acquire | for_statement@937 i &lt; this-&gt;bucket_count_ | 当前参考未静态绑定；见下方边界说明 |

| L943 | lease.Data | for_statement@937 i &lt; this-&gt;bucket_count_ | 当前参考未静态绑定；见下方边界说明 |

| L950 | quantizer_-&gt;Package32 | for_statement@937 i &lt; this-&gt;bucket_count_ → while_statement@945 (begin &lt; bucket_size) | 当前参考未静态绑定；见下方边界说明 |

| L951 | this-&gt;datas_[i].Write | for_statement@937 i &lt; this-&gt;bucket_count_ → while_statement@945 (begin &lt; bucket_size) | 当前参考未静态绑定；见下方边界说明 |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L958"></a>

## `BucketDataCell<QuantTmpl, IOTmpl>::unpack_fastscan`

源码位置：`src/datacell/bucket_datacell.h:958–976`。

先从签名确认输入、返回值和 const/override，再按完整函数体的条件阅读调用点。下表保留了本函数的显式调用以及 lambda 中的调用；进入下层时用“候选实现”定位，未解析的对象由源码静态类型/运行时类型确认。

### 完整函数

```cpp
void
BucketDataCell<QuantTmpl, IOTmpl>::unpack_fastscan() {
    ByteBuffer buffer(code_size_ * 32, this->allocator_);
    for (int64_t i = 0; i < this->bucket_count_; ++i) {
        auto bucket_size = (this->bucket_sizes_[i] + 31) / 32 * 32;
        if (bucket_size == 0) {
            continue;
        }
        auto lease = this->datas_[i].Acquire(0, code_size_ * bucket_size);
        const auto* codes = lease.Data();
        InnerIdType begin = 0;
        while (begin < bucket_size) {
            const uint8_t* src_block = codes + begin * code_size_;
            quantizer_->Unpack32(src_block, buffer.data);
            this->datas_[i].Write(buffer.data, code_size_ * 32, begin * code_size_);
            begin += 32;
        }
    }
}
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L966 | this-&gt;datas_[i].Acquire | for_statement@961 i &lt; this-&gt;bucket_count_ | 当前参考未静态绑定；见下方边界说明 |

| L967 | lease.Data | for_statement@961 i &lt; this-&gt;bucket_count_ | 当前参考未静态绑定；见下方边界说明 |

| L971 | quantizer_-&gt;Unpack32 | for_statement@961 i &lt; this-&gt;bucket_count_ → while_statement@969 (begin &lt; bucket_size) | 当前参考未静态绑定；见下方边界说明 |

| L972 | this-&gt;datas_[i].Write | for_statement@961 i &lt; this-&gt;bucket_count_ → while_statement@969 (begin &lt; bucket_size) | 当前参考未静态绑定；见下方边界说明 |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L979"></a>

## `BucketDataCell<QuantTmpl, IOTmpl>::ExportModel`

源码位置：`src/datacell/bucket_datacell.h:979–991`。

先从签名确认输入、返回值和 const/override，再按完整函数体的条件阅读调用点。下表保留了本函数的显式调用以及 lambda 中的调用；进入下层时用“候选实现”定位，未解析的对象由源码静态类型/运行时类型确认。

### 完整函数

```cpp
void
BucketDataCell<QuantTmpl, IOTmpl>::ExportModel(const BucketInterfacePtr& other) const {
    std::stringstream ss;
    IOStreamWriter writer(ss);
    this->quantizer_->Serialize(writer);
    ss.seekg(0, std::ios::beg);
    IOStreamReader reader(ss);
    auto ptr = std::dynamic_pointer_cast<BucketDataCell<QuantTmpl, IOTmpl>>(other);
    if (ptr == nullptr) {
        throw VsagException(ErrorType::INTERNAL_ERROR, "Export model's bucket datacell failed");
    }
    ptr->quantizer_->Deserialize(reader);
}
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L983 | this-&gt;quantizer_-&gt;Serialize | 函数本体；短路求值/提前返回见源码 | [Quantizer::Serialize · L161](quantizer_h.md#L161) |

| L984 | ss.seekg | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L986 | std::dynamic_pointer_cast&lt;BucketDataCell&lt;QuantTmpl, IOTmpl&gt;&gt; | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L988 | VsagException | if_statement@987 (ptr == nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L990 | ptr-&gt;quantizer_-&gt;Deserialize | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L994"></a>

## `BucketDataCell<QuantTmpl, IOTmpl>::MergeOther`

源码位置：`src/datacell/bucket_datacell.h:994–1014`。

先从签名确认输入、返回值和 const/override，再按完整函数体的条件阅读调用点。下表保留了本函数的显式调用以及 lambda 中的调用；进入下层时用“候选实现”定位，未解析的对象由源码静态类型/运行时类型确认。

### 完整函数

```cpp
void
BucketDataCell<QuantTmpl, IOTmpl>::MergeOther(const BucketInterfacePtr& other, InnerIdType bias) {
    auto ptr = std::dynamic_pointer_cast<BucketDataCell<QuantTmpl, IOTmpl>>(other);
    if (ptr == nullptr) {
        throw VsagException(ErrorType::INTERNAL_ERROR, "Merge other's bucket datacell failed");
    }
    for (int i = 0; i < ptr->bucket_count_; ++i) {
        if (ptr->bucket_sizes_[i] == 0) {
            continue;
        }
        auto lease = ptr->datas_[i].Acquire(0, ptr->bucket_sizes_[i] * this->code_size_);
        this->datas_[i].Write(lease.Data(),
                              ptr->bucket_sizes_[i] * this->code_size_,
                              this->bucket_sizes_[i] * this->code_size_);
        this->bucket_sizes_[i] += ptr->bucket_sizes_[i];
        this->inner_ids_[i].reserve(this->bucket_sizes_[i]);
        for (auto id : ptr->inner_ids_[i]) {
            this->inner_ids_[i].emplace_back(id == EMPTY_INNER_ID ? EMPTY_INNER_ID : id + bias);
        }
    }
}
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L996 | std::dynamic_pointer_cast&lt;BucketDataCell&lt;QuantTmpl, IOTmpl&gt;&gt; | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L998 | VsagException | if_statement@997 (ptr == nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L1004 | ptr-&gt;datas_[i].Acquire | for_statement@1000 i &lt; ptr-&gt;bucket_count_ | 当前参考未静态绑定；见下方边界说明 |

| L1005 | this-&gt;datas_[i].Write | for_statement@1000 i &lt; ptr-&gt;bucket_count_ | 当前参考未静态绑定；见下方边界说明 |

| L1005 | lease.Data | for_statement@1000 i &lt; ptr-&gt;bucket_count_ | 当前参考未静态绑定；见下方边界说明 |

| L1009 | this-&gt;inner_ids_[i].reserve | for_statement@1000 i &lt; ptr-&gt;bucket_count_ | 当前参考未静态绑定；见下方边界说明 |

| L1011 | this-&gt;inner_ids_[i].emplace_back | for_statement@1000 i &lt; ptr-&gt;bucket_count_ → for_range_loop@1010 | 当前参考未静态绑定；见下方边界说明 |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L1017"></a>

## `BucketDataCell<QuantTmpl, IOTmpl>::GetCodesById`

源码位置：`src/datacell/bucket_datacell.h:1017–1032`。

先从签名确认输入、返回值和 const/override，再按完整函数体的条件阅读调用点。下表保留了本函数的显式调用以及 lambda 中的调用；进入下层时用“候选实现”定位，未解析的对象由源码静态类型/运行时类型确认。

### 完整函数

```cpp
void
BucketDataCell<QuantTmpl, IOTmpl>::GetCodesById(BucketIdType bucket_id,
                                                InnerIdType offset_id,
                                                uint8_t* data) const {
    if (bucket_id >= this->bucket_count_) {
        throw VsagException(
            ErrorType::INTERNAL_ERROR,
            fmt::format("Get code by inner id failed: bucket id ({}) is invalid", bucket_id));
    }
    if (offset_id >= this->bucket_sizes_[bucket_id]) {
        throw VsagException(
            ErrorType::INTERNAL_ERROR,
            fmt::format("Get code by inner id failed: offset id ({}) is invalid", offset_id));
    }
    this->datas_[bucket_id].Read(this->code_size_, offset_id * this->code_size_, data);
}
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L1022 | VsagException | if_statement@1021 (bucket_id &gt;= this-&gt;bucket_count_) | 当前参考未静态绑定；见下方边界说明 |

| L1024 | fmt::format | if_statement@1021 (bucket_id &gt;= this-&gt;bucket_count_) | 当前参考未静态绑定；见下方边界说明 |

| L1027 | VsagException | if_statement@1026 (offset_id &gt;= this-&gt;bucket_sizes_[bucket_id]) | 当前参考未静态绑定；见下方边界说明 |

| L1029 | fmt::format | if_statement@1026 (offset_id &gt;= this-&gt;bucket_sizes_[bucket_id]) | 当前参考未静态绑定；见下方边界说明 |

| L1031 | this-&gt;datas_[bucket_id].Read | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L1035"></a>

## `BucketDataCell<QuantTmpl, IOTmpl>::ComputePairVectors`

源码位置：`src/datacell/bucket_datacell.h:1035–1075`。

先从签名确认输入、返回值和 const/override，再按完整函数体的条件阅读调用点。下表保留了本函数的显式调用以及 lambda 中的调用；进入下层时用“候选实现”定位，未解析的对象由源码静态类型/运行时类型确认。

### 完整函数

```cpp
float
BucketDataCell<QuantTmpl, IOTmpl>::ComputePairVectors(BucketIdType bucket_id,
                                                      InnerIdType id1,
                                                      InnerIdType id2) {
    if (bucket_id >= this->bucket_count_) {
        throw VsagException(
            ErrorType::INTERNAL_ERROR,
            fmt::format("ComputePairVectors failed: bucket id ({}) is invalid", bucket_id));
    }
    if (id1 >= this->bucket_sizes_[bucket_id] || id2 >= this->bucket_sizes_[bucket_id]) {
        throw VsagException(ErrorType::INTERNAL_ERROR,
                            fmt::format("ComputePairVectors failed: offset id is invalid"));
    }
    if (this->inner_ids_[bucket_id][id1] == EMPTY_INNER_ID ||
        this->inner_ids_[bucket_id][id2] == EMPTY_INNER_ID) {
        throw VsagException(
            ErrorType::INTERNAL_ERROR,
            "ComputePairVectors failed: cannot compute distance for deleted vector");
    }
    std::shared_lock lock(this->bucket_mutexes_[bucket_id]);
    constexpr size_t kStackThreshold = 256;
    uint8_t stack_buf1[kStackThreshold];
    uint8_t stack_buf2[kStackThreshold];

    uint8_t *code1_ptr, *code2_ptr;
    std::vector<uint8_t> heap_buf1, heap_buf2;

    if (this->code_size_ <= kStackThreshold) {
        code1_ptr = stack_buf1;
        code2_ptr = stack_buf2;
    } else {
        heap_buf1.resize(this->code_size_);
        heap_buf2.resize(this->code_size_);
        code1_ptr = heap_buf1.data();
        code2_ptr = heap_buf2.data();
    }

    this->datas_[bucket_id].Read(this->code_size_, id1 * this->code_size_, code1_ptr);
    this->datas_[bucket_id].Read(this->code_size_, id2 * this->code_size_, code2_ptr);
    return this->quantizer_->Compute(code1_ptr, code2_ptr);
}
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L1040 | VsagException | if_statement@1039 (bucket_id &gt;= this-&gt;bucket_count_) | 当前参考未静态绑定；见下方边界说明 |

| L1042 | fmt::format | if_statement@1039 (bucket_id &gt;= this-&gt;bucket_count_) | 当前参考未静态绑定；见下方边界说明 |

| L1045 | VsagException | if_statement@1044 (id1 &gt;= this-&gt;bucket_sizes_[bucket_id] &#124;&#124; id2 &gt;= this-&gt;bucket_sizes_[bucket_id]) | 当前参考未静态绑定；见下方边界说明 |

| L1046 | fmt::format | if_statement@1044 (id1 &gt;= this-&gt;bucket_sizes_[bucket_id] &#124;&#124; id2 &gt;= this-&gt;bucket_sizes_[bucket_id]) | 当前参考未静态绑定；见下方边界说明 |

| L1050 | VsagException | if_statement@1048 (this-&gt;inner_ids_[bucket_id][id1] == EMPTY_INNER_ID &#124;&#124; this-&gt;inner_ids_[bucket_id][id2] == EMPTY_INNER_ID) | 当前参考未静态绑定；见下方边界说明 |

| L1066 | heap_buf1.resize | if_statement@1062 (this-&gt;code_size_ &lt;= kStackThreshold) [else 分支] | 当前参考未静态绑定；见下方边界说明 |

| L1067 | heap_buf2.resize | if_statement@1062 (this-&gt;code_size_ &lt;= kStackThreshold) [else 分支] | 当前参考未静态绑定；见下方边界说明 |

| L1068 | heap_buf1.data | if_statement@1062 (this-&gt;code_size_ &lt;= kStackThreshold) [else 分支] | 当前参考未静态绑定；见下方边界说明 |

| L1069 | heap_buf2.data | if_statement@1062 (this-&gt;code_size_ &lt;= kStackThreshold) [else 分支] | 当前参考未静态绑定；见下方边界说明 |

| L1072 | this-&gt;datas_[bucket_id].Read | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L1073 | this-&gt;datas_[bucket_id].Read | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L1074 | this-&gt;quantizer_-&gt;Compute | 函数本体；短路求值/提前返回见源码 | [Quantizer::Compute · L156](quantizer_h.md#L156) |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。
