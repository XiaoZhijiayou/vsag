# fp32_quantizer.cpp：逐函数完整源码与调用点

[主讲解](../code_walkthrough.md) · [函数总目录](README.md)

源码：[ src/quantization/fp32_quantizer.cpp ](../../../../src/quantization/fp32_quantizer.cpp)。基线 `fd363937`。以下源码函数体完整保留；调用点表是语法树中的显式调用表达式，按源码位置排列，不代表 C++ 参数求值顺序。表中“候选实现”需结合类型和参数选分支，不能将同名函数全部视为必经路径。

- [FP32Quantizer&lt;metric&gt;::FP32Quantizer · L25](fp32_quantizer.md#L25)

- [FP32Quantizer&lt;metric&gt;::FP32Quantizer · L33](fp32_quantizer.md#L33)

- [FP32Quantizer&lt;metric&gt;::FP32Quantizer · L43](fp32_quantizer.md#L43)

- [FP32Quantizer&lt;metric&gt;::TrainImpl · L50](fp32_quantizer.md#L50)

- [FP32Quantizer&lt;metric&gt;::EncodeOneImpl · L57](fp32_quantizer.md#L57)

- [FP32Quantizer&lt;metric&gt;::EncodeBatchImpl · L76](fp32_quantizer.md#L76)

- [FP32Quantizer&lt;metric&gt;::DecodeOneImpl · L85](fp32_quantizer.md#L85)

- [FP32Quantizer&lt;metric&gt;::DecodeBatchImpl · L92](fp32_quantizer.md#L92)

- [FP32Quantizer&lt;metric&gt;::ComputeImpl · L105](fp32_quantizer.md#L105)

- [FP32Quantizer&lt;metric&gt;::ScanBatchDistImpl · L132](fp32_quantizer.md#L132)

- [FP32Quantizer&lt;metric&gt;::ProcessQueryImpl · L144](fp32_quantizer.md#L144)

- [FP32Quantizer&lt;metric&gt;::ComputeDistImpl · L164](fp32_quantizer.md#L164)

- [FP32Quantizer&lt;metric&gt;::ComputeDistsBatch4Impl · L191](fp32_quantizer.md#L191)

- [FP32Quantizer&lt;metric&gt;::ReleaseComputerImpl · L261](fp32_quantizer.md#L261)


<a id="L25"></a>

## `FP32Quantizer<metric>::FP32Quantizer`

源码位置：`src/quantization/fp32_quantizer.cpp:25–30`。

先从签名确认输入、返回值和 const/override，再按完整函数体的条件阅读调用点。下表保留了本函数的显式调用以及 lambda 中的调用；进入下层时用“候选实现”定位，未解析的对象由源码静态类型/运行时类型确认。

### 完整函数

```cpp
FP32Quantizer<metric>::FP32Quantizer(int dim, Allocator* allocator)
    : Quantizer<FP32Quantizer<metric>>(dim, allocator) {
    this->code_size_ = dim * sizeof(float);
    this->query_code_size_ = this->code_size_;
    this->metric_ = metric;
}
```

### 函数内部调用点：不省略标准库和辅助调用

此函数体没有显式函数调用表达式。赋值、成员初始化和隐式操作请看上面的完整源码。


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L33"></a>

## `FP32Quantizer<metric>::FP32Quantizer`

源码位置：`src/quantization/fp32_quantizer.cpp:33–40`。

先从签名确认输入、返回值和 const/override，再按完整函数体的条件阅读调用点。下表保留了本函数的显式调用以及 lambda 中的调用；进入下层时用“候选实现”定位，未解析的对象由源码静态类型/运行时类型确认。

### 完整函数

```cpp
FP32Quantizer<metric>::FP32Quantizer(const FP32QuantizerParamPtr& param,
                                     const IndexCommonParam& common_param)
    : FP32Quantizer<metric>(common_param.dim_, common_param.allocator_.get()) {
    this->hold_molds_ = param->hold_molds;
    if (metric == MetricType::METRIC_TYPE_COSINE && this->hold_molds_) {
        this->code_size_ += sizeof(float);
    }
}
```

### 函数内部调用点：不省略标准库和辅助调用

此函数体没有显式函数调用表达式。赋值、成员初始化和隐式操作请看上面的完整源码。


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L43"></a>

## `FP32Quantizer<metric>::FP32Quantizer`

源码位置：`src/quantization/fp32_quantizer.cpp:43–47`。

先从签名确认输入、返回值和 const/override，再按完整函数体的条件阅读调用点。下表保留了本函数的显式调用以及 lambda 中的调用；进入下层时用“候选实现”定位，未解析的对象由源码静态类型/运行时类型确认。

### 完整函数

```cpp
FP32Quantizer<metric>::FP32Quantizer(const QuantizerParamPtr& param,
                                     const IndexCommonParam& common_param)
    : FP32Quantizer<metric>(std::dynamic_pointer_cast<FP32QuantizerParameter>(param),
                            common_param) {
}
```

### 函数内部调用点：不省略标准库和辅助调用

此函数体没有显式函数调用表达式。赋值、成员初始化和隐式操作请看上面的完整源码。


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L50"></a>

## `FP32Quantizer<metric>::TrainImpl`

源码位置：`src/quantization/fp32_quantizer.cpp:50–54`。

先从签名确认输入、返回值和 const/override，再按完整函数体的条件阅读调用点。下表保留了本函数的显式调用以及 lambda 中的调用；进入下层时用“候选实现”定位，未解析的对象由源码静态类型/运行时类型确认。

### 完整函数

```cpp
bool
FP32Quantizer<metric>::TrainImpl(const float* data, uint64_t count) {
    this->is_trained_ = true;
    return true;
}
```

### 函数内部调用点：不省略标准库和辅助调用

此函数体没有显式函数调用表达式。赋值、成员初始化和隐式操作请看上面的完整源码。


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L57"></a>

## `FP32Quantizer<metric>::EncodeOneImpl`

源码位置：`src/quantization/fp32_quantizer.cpp:57–73`。

先从签名确认输入、返回值和 const/override，再按完整函数体的条件阅读调用点。下表保留了本函数的显式调用以及 lambda 中的调用；进入下层时用“候选实现”定位，未解析的对象由源码静态类型/运行时类型确认。

### 完整函数

```cpp
bool
FP32Quantizer<metric>::EncodeOneImpl(const float* data, uint8_t* codes) {
    if constexpr (metric == MetricType::METRIC_TYPE_COSINE) {
        if (this->hold_molds_) {
            // Store the mold for cosine similarity
            const auto* data_float = reinterpret_cast<const float*>(data);
            float mold = std::sqrt(FP32ComputeIP(data_float, data_float, this->dim_));
            memcpy(codes, data, this->dim_ * sizeof(float));
            memcpy(codes + this->dim_ * sizeof(float), &mold, sizeof(float));
        } else {
            Normalize(data, reinterpret_cast<float*>(codes), this->dim_);
        }
    } else {
        memcpy(codes, data, this->code_size_);
    }
    return true;
}
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L63 | std::sqrt | if_statement@59 (metric == MetricType::METRIC_TYPE_COSINE) → if_statement@60 (this-&gt;hold_molds_) | 当前参考未静态绑定；见下方边界说明 |

| L63 | FP32ComputeIP | if_statement@59 (metric == MetricType::METRIC_TYPE_COSINE) → if_statement@60 (this-&gt;hold_molds_) | 当前参考未静态绑定；见下方边界说明 |

| L64 | memcpy | if_statement@59 (metric == MetricType::METRIC_TYPE_COSINE) → if_statement@60 (this-&gt;hold_molds_) | 当前参考未静态绑定；见下方边界说明 |

| L65 | memcpy | if_statement@59 (metric == MetricType::METRIC_TYPE_COSINE) → if_statement@60 (this-&gt;hold_molds_) | 当前参考未静态绑定；见下方边界说明 |

| L67 | Normalize | if_statement@59 (metric == MetricType::METRIC_TYPE_COSINE) → if_statement@60 (this-&gt;hold_molds_) [else 分支] | 当前参考未静态绑定；见下方边界说明 |

| L70 | memcpy | if_statement@59 (metric == MetricType::METRIC_TYPE_COSINE) [else 分支] | 当前参考未静态绑定；见下方边界说明 |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L76"></a>

## `FP32Quantizer<metric>::EncodeBatchImpl`

源码位置：`src/quantization/fp32_quantizer.cpp:76–82`。

先从签名确认输入、返回值和 const/override，再按完整函数体的条件阅读调用点。下表保留了本函数的显式调用以及 lambda 中的调用；进入下层时用“候选实现”定位，未解析的对象由源码静态类型/运行时类型确认。

### 完整函数

```cpp
bool
FP32Quantizer<metric>::EncodeBatchImpl(const float* data, uint8_t* codes, uint64_t count) {
    for (uint64_t i = 0; i < count; ++i) {
        EncodeOneImpl(data + i * this->dim_, codes + i * this->code_size_);
    }
    return true;
}
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L79 | EncodeOneImpl | for_statement@78 i &lt; count | [FP32Quantizer&lt;metric&gt;::EncodeOneImpl · L57](fp32_quantizer.md#L57) |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L85"></a>

## `FP32Quantizer<metric>::DecodeOneImpl`

源码位置：`src/quantization/fp32_quantizer.cpp:85–89`。

先从签名确认输入、返回值和 const/override，再按完整函数体的条件阅读调用点。下表保留了本函数的显式调用以及 lambda 中的调用；进入下层时用“候选实现”定位，未解析的对象由源码静态类型/运行时类型确认。

### 完整函数

```cpp
bool
FP32Quantizer<metric>::DecodeOneImpl(const uint8_t* codes, float* data) {
    memcpy(data, codes, this->dim_ * sizeof(float));
    return true;
}
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L87 | memcpy | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L92"></a>

## `FP32Quantizer<metric>::DecodeBatchImpl`

源码位置：`src/quantization/fp32_quantizer.cpp:92–102`。

先从签名确认输入、返回值和 const/override，再按完整函数体的条件阅读调用点。下表保留了本函数的显式调用以及 lambda 中的调用；进入下层时用“候选实现”定位，未解析的对象由源码静态类型/运行时类型确认。

### 完整函数

```cpp
bool
FP32Quantizer<metric>::DecodeBatchImpl(const uint8_t* codes, float* data, uint64_t count) {
    if (this->code_size_ == this->dim_ * sizeof(float)) {
        memcpy(data, codes, count * this->code_size_);
    } else {
        for (uint64_t i = 0; i < count; ++i) {
            memcpy(data + i * this->dim_, codes + i * this->code_size_, this->dim_ * sizeof(float));
        }
    }
    return true;
}
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L95 | memcpy | if_statement@94 (this-&gt;code_size_ == this-&gt;dim_ * sizeof(float)) | 当前参考未静态绑定；见下方边界说明 |

| L98 | memcpy | if_statement@94 (this-&gt;code_size_ == this-&gt;dim_ * sizeof(float)) [else 分支] → for_statement@97 i &lt; count | 当前参考未静态绑定；见下方边界说明 |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L105"></a>

## `FP32Quantizer<metric>::ComputeImpl`

源码位置：`src/quantization/fp32_quantizer.cpp:105–129`。

先从签名确认输入、返回值和 const/override，再按完整函数体的条件阅读调用点。下表保留了本函数的显式调用以及 lambda 中的调用；进入下层时用“候选实现”定位，未解析的对象由源码静态类型/运行时类型确认。

### 完整函数

```cpp
float
FP32Quantizer<metric>::ComputeImpl(const uint8_t* codes1, const uint8_t* codes2) {
    if (metric == MetricType::METRIC_TYPE_IP) {
        return 1.0F - FP32ComputeIP(reinterpret_cast<const float*>(codes1),
                                    reinterpret_cast<const float*>(codes2),
                                    this->dim_);
    }
    if (metric == MetricType::METRIC_TYPE_COSINE) {
        auto similarity = FP32ComputeIP(reinterpret_cast<const float*>(codes1),
                                        reinterpret_cast<const float*>(codes2),
                                        this->dim_);
        if (this->hold_molds_) {
            const auto* mold1 = reinterpret_cast<const float*>(codes1 + this->dim_ * sizeof(float));
            const auto* mold2 = reinterpret_cast<const float*>(codes2 + this->dim_ * sizeof(float));
            similarity /= mold1[0] * mold2[0];
        }
        return 1.0F - similarity;
    }
    if (metric == MetricType::METRIC_TYPE_L2SQR) {
        return FP32ComputeL2Sqr(reinterpret_cast<const float*>(codes1),
                                reinterpret_cast<const float*>(codes2),
                                this->dim_);
    }
    return 0.0F;
}
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L108 | FP32ComputeIP | if_statement@107 (metric == MetricType::METRIC_TYPE_IP) | 当前参考未静态绑定；见下方边界说明 |

| L113 | FP32ComputeIP | if_statement@112 (metric == MetricType::METRIC_TYPE_COSINE) | 当前参考未静态绑定；见下方边界说明 |

| L124 | FP32ComputeL2Sqr | if_statement@123 (metric == MetricType::METRIC_TYPE_L2SQR) | 当前参考未静态绑定；见下方边界说明 |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L132"></a>

## `FP32Quantizer<metric>::ScanBatchDistImpl`

源码位置：`src/quantization/fp32_quantizer.cpp:132–141`。

先从签名确认输入、返回值和 const/override，再按完整函数体的条件阅读调用点。下表保留了本函数的显式调用以及 lambda 中的调用；进入下层时用“候选实现”定位，未解析的对象由源码静态类型/运行时类型确认。

### 完整函数

```cpp
void
FP32Quantizer<metric>::ScanBatchDistImpl(Computer<FP32Quantizer<metric>>& computer,
                                         uint64_t count,
                                         const uint8_t* codes,
                                         float* dists) const {
    // TODO(LHT): Optimize batch for simd
    for (uint64_t i = 0; i < count; ++i) {
        this->ComputeDistImpl(computer, codes + i * this->code_size_, dists + i);
    }
}
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L139 | this-&gt;ComputeDistImpl | for_statement@138 i &lt; count | [FP32Quantizer&lt;metric&gt;::ComputeDistImpl · L164](fp32_quantizer.md#L164) |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L144"></a>

## `FP32Quantizer<metric>::ProcessQueryImpl`

源码位置：`src/quantization/fp32_quantizer.cpp:144–161`。

先从签名确认输入、返回值和 const/override，再按完整函数体的条件阅读调用点。下表保留了本函数的显式调用以及 lambda 中的调用；进入下层时用“候选实现”定位，未解析的对象由源码静态类型/运行时类型确认。

### 完整函数

```cpp
void
FP32Quantizer<metric>::ProcessQueryImpl(const float* query,
                                        Computer<FP32Quantizer<metric>>& computer) const {
    try {
        if (computer.buf_ == nullptr) {
            computer.buf_ =
                reinterpret_cast<uint8_t*>(this->allocator_->Allocate(this->query_code_size_));
        }
    } catch (const std::bad_alloc& e) {
        computer.buf_ = nullptr;
        throw VsagException(ErrorType::NO_ENOUGH_MEMORY, "bad alloc when init computer buf");
    }
    if constexpr (metric == MetricType::METRIC_TYPE_COSINE) {
        Normalize(query, reinterpret_cast<float*>(computer.buf_), this->dim_);
    } else {
        memcpy(computer.buf_, query, this->code_size_);
    }
}
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L150 | this-&gt;allocator_-&gt;Allocate | if_statement@148 (computer.buf_ == nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L154 | VsagException | catch_clause@152 | 当前参考未静态绑定；见下方边界说明 |

| L157 | Normalize | if_statement@156 (metric == MetricType::METRIC_TYPE_COSINE) | 当前参考未静态绑定；见下方边界说明 |

| L159 | memcpy | if_statement@156 (metric == MetricType::METRIC_TYPE_COSINE) [else 分支] | 当前参考未静态绑定；见下方边界说明 |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L164"></a>

## `FP32Quantizer<metric>::ComputeDistImpl`

源码位置：`src/quantization/fp32_quantizer.cpp:164–188`。

先从签名确认输入、返回值和 const/override，再按完整函数体的条件阅读调用点。下表保留了本函数的显式调用以及 lambda 中的调用；进入下层时用“候选实现”定位，未解析的对象由源码静态类型/运行时类型确认。

### 完整函数

```cpp
void
FP32Quantizer<metric>::ComputeDistImpl(Computer<FP32Quantizer<metric>>& computer,
                                       const uint8_t* codes,
                                       float* dists) const {
    if (metric == MetricType::METRIC_TYPE_IP) {
        *dists = 1.0F - FP32ComputeIP(reinterpret_cast<const float*>(codes),
                                      reinterpret_cast<const float*>(computer.buf_),
                                      this->dim_);
    } else if (metric == MetricType::METRIC_TYPE_COSINE) {
        auto similarity = FP32ComputeIP(reinterpret_cast<const float*>(codes),
                                        reinterpret_cast<const float*>(computer.buf_),
                                        this->dim_);
        if (this->hold_molds_) {
            const auto* mold = reinterpret_cast<const float*>(codes + this->dim_ * sizeof(float));
            similarity /= mold[0];
        }
        *dists = 1.0F - similarity;
    } else if (metric == MetricType::METRIC_TYPE_L2SQR) {
        *dists = FP32ComputeL2Sqr(reinterpret_cast<const float*>(codes),
                                  reinterpret_cast<const float*>(computer.buf_),
                                  this->dim_);
    } else {
        *dists = 0.0F;
    }
}
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L169 | FP32ComputeIP | if_statement@168 (metric == MetricType::METRIC_TYPE_IP) | 当前参考未静态绑定；见下方边界说明 |

| L173 | FP32ComputeIP | if_statement@168 (metric == MetricType::METRIC_TYPE_IP) [else 分支] → if_statement@172 (metric == MetricType::METRIC_TYPE_COSINE) | 当前参考未静态绑定；见下方边界说明 |

| L182 | FP32ComputeL2Sqr | if_statement@168 (metric == MetricType::METRIC_TYPE_IP) [else 分支] → if_statement@172 (metric == MetricType::METRIC_TYPE_COSINE) [else 分支] → if_statement@181 (metric == MetricType::METRIC_TYPE_L2SQR) | 当前参考未静态绑定；见下方边界说明 |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L191"></a>

## `FP32Quantizer<metric>::ComputeDistsBatch4Impl`

源码位置：`src/quantization/fp32_quantizer.cpp:191–258`。

先从签名确认输入、返回值和 const/override，再按完整函数体的条件阅读调用点。下表保留了本函数的显式调用以及 lambda 中的调用；进入下层时用“候选实现”定位，未解析的对象由源码静态类型/运行时类型确认。

### 完整函数

```cpp
void
FP32Quantizer<metric>::ComputeDistsBatch4Impl(Computer<FP32Quantizer<metric>>& computer,
                                              const uint8_t* codes1,
                                              const uint8_t* codes2,
                                              const uint8_t* codes3,
                                              const uint8_t* codes4,
                                              float& dists1,
                                              float& dists2,
                                              float& dists3,
                                              float& dists4) const {
    if constexpr (metric == MetricType::METRIC_TYPE_IP) {
        FP32ComputeIPBatch4(reinterpret_cast<const float*>(computer.buf_),
                            this->dim_,
                            reinterpret_cast<const float*>(codes1),
                            reinterpret_cast<const float*>(codes2),
                            reinterpret_cast<const float*>(codes3),
                            reinterpret_cast<const float*>(codes4),
                            dists1,
                            dists2,
                            dists3,
                            dists4);
        dists1 = 1.0F - dists1;
        dists2 = 1.0F - dists2;
        dists3 = 1.0F - dists3;
        dists4 = 1.0F - dists4;
    } else if (metric == MetricType::METRIC_TYPE_COSINE) {
        FP32ComputeIPBatch4(reinterpret_cast<const float*>(computer.buf_),
                            this->dim_,
                            reinterpret_cast<const float*>(codes1),
                            reinterpret_cast<const float*>(codes2),
                            reinterpret_cast<const float*>(codes3),
                            reinterpret_cast<const float*>(codes4),
                            dists1,
                            dists2,
                            dists3,
                            dists4);
        if (this->hold_molds_) {
            const auto* mold1 = reinterpret_cast<const float*>(codes1 + this->dim_ * sizeof(float));
            const auto* mold2 = reinterpret_cast<const float*>(codes2 + this->dim_ * sizeof(float));
            const auto* mold3 = reinterpret_cast<const float*>(codes3 + this->dim_ * sizeof(float));
            const auto* mold4 = reinterpret_cast<const float*>(codes4 + this->dim_ * sizeof(float));
            dists1 /= mold1[0];
            dists2 /= mold2[0];
            dists3 /= mold3[0];
            dists4 /= mold4[0];
        }
        dists1 = 1.0F - dists1;
        dists2 = 1.0F - dists2;
        dists3 = 1.0F - dists3;
        dists4 = 1.0F - dists4;
    } else if constexpr (metric == MetricType::METRIC_TYPE_L2SQR) {
        FP32ComputeL2SqrBatch4(reinterpret_cast<const float*>(computer.buf_),
                               this->dim_,
                               reinterpret_cast<const float*>(codes1),
                               reinterpret_cast<const float*>(codes2),
                               reinterpret_cast<const float*>(codes3),
                               reinterpret_cast<const float*>(codes4),
                               dists1,
                               dists2,
                               dists3,
                               dists4);
    } else {
        dists1 = 0.0F;
        dists2 = 0.0F;
        dists3 = 0.0F;
        dists4 = 0.0F;
    }
}
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L202 | FP32ComputeIPBatch4 | if_statement@201 (metric == MetricType::METRIC_TYPE_IP) | 当前参考未静态绑定；见下方边界说明 |

| L217 | FP32ComputeIPBatch4 | if_statement@201 (metric == MetricType::METRIC_TYPE_IP) [else 分支] → if_statement@216 (metric == MetricType::METRIC_TYPE_COSINE) | 当前参考未静态绑定；见下方边界说明 |

| L242 | FP32ComputeL2SqrBatch4 | if_statement@201 (metric == MetricType::METRIC_TYPE_IP) [else 分支] → if_statement@216 (metric == MetricType::METRIC_TYPE_COSINE) [else 分支] → if_statement@241 (metric == MetricType::METRIC_TYPE_L2SQR) | 当前参考未静态绑定；见下方边界说明 |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L261"></a>

## `FP32Quantizer<metric>::ReleaseComputerImpl`

源码位置：`src/quantization/fp32_quantizer.cpp:261–264`。

先从签名确认输入、返回值和 const/override，再按完整函数体的条件阅读调用点。下表保留了本函数的显式调用以及 lambda 中的调用；进入下层时用“候选实现”定位，未解析的对象由源码静态类型/运行时类型确认。

### 完整函数

```cpp
void
FP32Quantizer<metric>::ReleaseComputerImpl(Computer<FP32Quantizer<metric>>& computer) const {
    this->allocator_->Deallocate(computer.buf_);
}
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L263 | this-&gt;allocator_-&gt;Deallocate | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。
