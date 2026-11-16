# quantizer.h：逐函数完整源码与调用点

[主讲解](../code_walkthrough.md) · [函数总目录](README.md)

源码：[ src/quantization/quantizer.h ](../../../../src/quantization/quantizer.h)。基线 `fd363937`。以下源码函数体完整保留；调用点表是语法树中的显式调用表达式，按源码位置排列，不代表 C++ 参数求值顺序。表中“候选实现”需结合类型和参数选分支，不能将同名函数全部视为必经路径。

- [Quantizer::Quantizer&lt;QuantT&gt; · L37](quantizer_h.md#L37)

- [Quantizer::~Quantizer · L40](quantizer_h.md#L40)

- [Quantizer::Train · L49](quantizer_h.md#L49)

- [Quantizer::ReTrain · L64](quantizer_h.md#L64)

- [Quantizer::EncodeOne · L77](quantizer_h.md#L77)

- [Quantizer::EncodeBatch · L90](quantizer_h.md#L90)

- [Quantizer::EncodeBatchImpl · L99](quantizer_h.md#L99)

- [Quantizer::DecodeOne · L116](quantizer_h.md#L116)

- [Quantizer::DecodeBatch · L129](quantizer_h.md#L129)

- [Quantizer::DecodeBatchImpl · L138](quantizer_h.md#L138)

- [Quantizer::Compute · L156](quantizer_h.md#L156)

- [Quantizer::Serialize · L161](quantizer_h.md#L161)

- [Quantizer::Deserialize · L170](quantizer_h.md#L170)

- [Quantizer::FactoryComputer · L179](quantizer_h.md#L179)

- [Quantizer::ProcessQuery · L184](quantizer_h.md#L184)

- [Quantizer::ComputeDist · L189](quantizer_h.md#L189)

- [Quantizer::ComputeDistWithThreshold · L194](quantizer_h.md#L194)

- [Quantizer::ComputeDistWithLowerBound · L207](quantizer_h.md#L207)

- [Quantizer::ComputeDist · L223](quantizer_h.md#L223)

- [Quantizer::ScanBatchDists · L230](quantizer_h.md#L230)

- [Quantizer::ScanBatchDistsWithThreshold · L238](quantizer_h.md#L238)

- [Quantizer::ComputeDistsBatch4 · L249](quantizer_h.md#L249)

- [Quantizer::ReleaseComputer · L270](quantizer_h.md#L270)

- [Quantizer::ReleaseComputerImpl · L279](quantizer_h.md#L279)

- [Quantizer::ScanBatchDistImpl · L290](quantizer_h.md#L290)

- [Quantizer::Name · L300](quantizer_h.md#L300)

- [Quantizer::Metric · L305](quantizer_h.md#L305)

- [Quantizer::HoldMolds · L309](quantizer_h.md#L309)

- [Quantizer::GetCodeSize · L325](quantizer_h.md#L325)

- [Quantizer::GetQueryCodeSize · L330](quantizer_h.md#L330)

- [Quantizer::GetDim · L340](quantizer_h.md#L340)

- [Quantizer::& cast · L346](quantizer_h.md#L346)

- [Quantizer::& cast · L351](quantizer_h.md#L351)


<a id="L37"></a>

## `Quantizer::Quantizer<QuantT>`

源码位置：`src/quantization/quantizer.h:37–38`。

先从签名确认输入、返回值和 const/override，再按完整函数体的条件阅读调用点。下表保留了本函数的显式调用以及 lambda 中的调用；进入下层时用“候选实现”定位，未解析的对象由源码静态类型/运行时类型确认。

### 完整函数

```cpp
explicit Quantizer<QuantT>(int dim, Allocator* allocator)
        : dim_(dim), code_size_(dim * sizeof(float)), allocator_(allocator){}
```

### 函数内部调用点：不省略标准库和辅助调用

此函数体没有显式函数调用表达式。赋值、成员初始化和隐式操作请看上面的完整源码。


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L40"></a>

## `Quantizer::~Quantizer`

源码位置：`src/quantization/quantizer.h:40–40`。

先从签名确认输入、返回值和 const/override，再按完整函数体的条件阅读调用点。下表保留了本函数的显式调用以及 lambda 中的调用；进入下层时用“候选实现”定位，未解析的对象由源码静态类型/运行时类型确认。

### 完整函数

```cpp
virtual ~Quantizer() = default;
```

### 函数内部调用点：不省略标准库和辅助调用

此函数体没有显式函数调用表达式。赋值、成员初始化和隐式操作请看上面的完整源码。


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L49"></a>

## `Quantizer::Train`

源码位置：`src/quantization/quantizer.h:49–55`。

这是状态改变函数。先看重复训练的提前返回，再看训练数据是否采样/归一化/变成残差，最后确认状态位在何处设置。分区 Train 与量化器 Train 不是同一个模型。

### 完整函数

```cpp
bool
    Train(const float* data, uint64_t count) {
        if (this->is_trained_) {
            return true;
        }
        return cast().TrainImpl(data, count);
    }
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L54 | cast().TrainImpl | 函数本体；短路求值/提前返回见源码 | [FP32Quantizer&lt;metric&gt;::TrainImpl · L50](fp32_quantizer.md#L50) |

| L54 | cast | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L64"></a>

## `Quantizer::ReTrain`

源码位置：`src/quantization/quantizer.h:64–68`。

先从签名确认输入、返回值和 const/override，再按完整函数体的条件阅读调用点。下表保留了本函数的显式调用以及 lambda 中的调用；进入下层时用“候选实现”定位，未解析的对象由源码静态类型/运行时类型确认。

### 完整函数

```cpp
bool
    ReTrain(const float* data, uint64_t count) {
        this->is_trained_ = false;
        return cast().TrainImpl(data, count);
    }
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L67 | cast().TrainImpl | 函数本体；短路求值/提前返回见源码 | [FP32Quantizer&lt;metric&gt;::TrainImpl · L50](fp32_quantizer.md#L50) |

| L67 | cast | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L77"></a>

## `Quantizer::EncodeOne`

源码位置：`src/quantization/quantizer.h:77–80`。

先从签名确认输入、返回值和 const/override，再按完整函数体的条件阅读调用点。下表保留了本函数的显式调用以及 lambda 中的调用；进入下层时用“候选实现”定位，未解析的对象由源码静态类型/运行时类型确认。

### 完整函数

```cpp
bool
    EncodeOne(const float* data, uint8_t* codes) {
        return cast().EncodeOneImpl(data, codes);
    }
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L79 | cast().EncodeOneImpl | 函数本体；短路求值/提前返回见源码 | [FP32Quantizer&lt;metric&gt;::EncodeOneImpl · L57](fp32_quantizer.md#L57) |

| L79 | cast | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L90"></a>

## `Quantizer::EncodeBatch`

源码位置：`src/quantization/quantizer.h:90–93`。

先从签名确认输入、返回值和 const/override，再按完整函数体的条件阅读调用点。下表保留了本函数的显式调用以及 lambda 中的调用；进入下层时用“候选实现”定位，未解析的对象由源码静态类型/运行时类型确认。

### 完整函数

```cpp
bool
    EncodeBatch(const float* data, uint8_t* codes, uint64_t count) {
        return cast().EncodeBatchImpl(data, codes, count);
    }
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L92 | cast().EncodeBatchImpl | 函数本体；短路求值/提前返回见源码 | [Quantizer::EncodeBatchImpl · L99](quantizer_h.md#L99)；[FP32Quantizer&lt;metric&gt;::EncodeBatchImpl · L76](fp32_quantizer.md#L76) |

| L92 | cast | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L99"></a>

## `Quantizer::EncodeBatchImpl`

源码位置：`src/quantization/quantizer.h:99–107`。

先从签名确认输入、返回值和 const/override，再按完整函数体的条件阅读调用点。下表保留了本函数的显式调用以及 lambda 中的调用；进入下层时用“候选实现”定位，未解析的对象由源码静态类型/运行时类型确认。

### 完整函数

```cpp
bool
    EncodeBatchImpl(const float* data, uint8_t* codes, uint64_t count) {
        for (uint64_t i = 0; i < count; ++i) {
            if (!cast().EncodeOneImpl(data + i * dim_, codes + i * code_size_)) {
                return false;
            }
        }
        return true;
    }
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L102 | cast().EncodeOneImpl | for_statement@101 i &lt; count → if_statement@102 (!cast().EncodeOneImpl(data + i * dim_, codes + i * code_size_)) | [FP32Quantizer&lt;metric&gt;::EncodeOneImpl · L57](fp32_quantizer.md#L57) |

| L102 | cast | for_statement@101 i &lt; count → if_statement@102 (!cast().EncodeOneImpl(data + i * dim_, codes + i * code_size_)) | 当前参考未静态绑定；见下方边界说明 |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L116"></a>

## `Quantizer::DecodeOne`

源码位置：`src/quantization/quantizer.h:116–119`。

先从签名确认输入、返回值和 const/override，再按完整函数体的条件阅读调用点。下表保留了本函数的显式调用以及 lambda 中的调用；进入下层时用“候选实现”定位，未解析的对象由源码静态类型/运行时类型确认。

### 完整函数

```cpp
bool
    DecodeOne(const uint8_t* codes, float* data) {
        return cast().DecodeOneImpl(codes, data);
    }
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L118 | cast().DecodeOneImpl | 函数本体；短路求值/提前返回见源码 | [FP32Quantizer&lt;metric&gt;::DecodeOneImpl · L85](fp32_quantizer.md#L85) |

| L118 | cast | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L129"></a>

## `Quantizer::DecodeBatch`

源码位置：`src/quantization/quantizer.h:129–132`。

先从签名确认输入、返回值和 const/override，再按完整函数体的条件阅读调用点。下表保留了本函数的显式调用以及 lambda 中的调用；进入下层时用“候选实现”定位，未解析的对象由源码静态类型/运行时类型确认。

### 完整函数

```cpp
bool
    DecodeBatch(const uint8_t* codes, float* data, uint64_t count) {
        return cast().DecodeBatchImpl(codes, data, count);
    }
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L131 | cast().DecodeBatchImpl | 函数本体；短路求值/提前返回见源码 | [Quantizer::DecodeBatchImpl · L138](quantizer_h.md#L138)；[FP32Quantizer&lt;metric&gt;::DecodeBatchImpl · L92](fp32_quantizer.md#L92) |

| L131 | cast | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L138"></a>

## `Quantizer::DecodeBatchImpl`

源码位置：`src/quantization/quantizer.h:138–146`。

先从签名确认输入、返回值和 const/override，再按完整函数体的条件阅读调用点。下表保留了本函数的显式调用以及 lambda 中的调用；进入下层时用“候选实现”定位，未解析的对象由源码静态类型/运行时类型确认。

### 完整函数

```cpp
bool
    DecodeBatchImpl(const uint8_t* codes, float* data, uint64_t count) {
        for (uint64_t i = 0; i < count; ++i) {
            if (!cast().DecodeOneImpl(codes + i * code_size_, data + i * dim_)) {
                return false;
            }
        }
        return true;
    }
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L141 | cast().DecodeOneImpl | for_statement@140 i &lt; count → if_statement@141 (!cast().DecodeOneImpl(codes + i * code_size_, data + i * dim_)) | [FP32Quantizer&lt;metric&gt;::DecodeOneImpl · L85](fp32_quantizer.md#L85) |

| L141 | cast | for_statement@140 i &lt; count → if_statement@141 (!cast().DecodeOneImpl(codes + i * code_size_, data + i * dim_)) | 当前参考未静态绑定；见下方边界说明 |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L156"></a>

## `Quantizer::Compute`

源码位置：`src/quantization/quantizer.h:156–159`。

先从签名确认输入、返回值和 const/override，再按完整函数体的条件阅读调用点。下表保留了本函数的显式调用以及 lambda 中的调用；进入下层时用“候选实现”定位，未解析的对象由源码静态类型/运行时类型确认。

### 完整函数

```cpp
inline float
    Compute(const uint8_t* codes1, const uint8_t* codes2) {
        return cast().ComputeImpl(codes1, codes2);
    }
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L158 | cast().ComputeImpl | 函数本体；短路求值/提前返回见源码 | [FP32Quantizer&lt;metric&gt;::ComputeImpl · L105](fp32_quantizer.md#L105) |

| L158 | cast | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L161"></a>

## `Quantizer::Serialize`

源码位置：`src/quantization/quantizer.h:161–168`。

先从签名确认输入、返回值和 const/override，再按完整函数体的条件阅读调用点。下表保留了本函数的显式调用以及 lambda 中的调用；进入下层时用“候选实现”定位，未解析的对象由源码静态类型/运行时类型确认。

### 完整函数

```cpp
inline void
    Serialize(StreamWriter& writer) {
        StreamWriter::WriteObj(writer, this->dim_);
        StreamWriter::WriteObj(writer, this->metric_);
        StreamWriter::WriteObj(writer, this->code_size_);
        StreamWriter::WriteObj(writer, this->is_trained_);
        return cast().SerializeImpl(writer);
    }
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L163 | StreamWriter::WriteObj | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L164 | StreamWriter::WriteObj | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L165 | StreamWriter::WriteObj | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L166 | StreamWriter::WriteObj | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L167 | cast().SerializeImpl | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L167 | cast | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L170"></a>

## `Quantizer::Deserialize`

源码位置：`src/quantization/quantizer.h:170–177`。

先从签名确认输入、返回值和 const/override，再按完整函数体的条件阅读调用点。下表保留了本函数的显式调用以及 lambda 中的调用；进入下层时用“候选实现”定位，未解析的对象由源码静态类型/运行时类型确认。

### 完整函数

```cpp
inline void
    Deserialize(StreamReader& reader) {
        StreamReader::ReadObj(reader, this->dim_);
        StreamReader::ReadObj(reader, this->metric_);
        StreamReader::ReadObj(reader, this->code_size_);
        StreamReader::ReadObj(reader, this->is_trained_);
        return cast().DeserializeImpl(reader);
    }
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L172 | StreamReader::ReadObj | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L173 | StreamReader::ReadObj | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L174 | StreamReader::ReadObj | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L175 | StreamReader::ReadObj | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L176 | cast().DeserializeImpl | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L176 | cast | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L179"></a>

## `Quantizer::FactoryComputer`

源码位置：`src/quantization/quantizer.h:179–182`。

返回为当前 query 准备好的距离计算器。继续追踪 SetQuery/ProcessQuery；残差模式还保存 raw_query。创建计算器不等于已经遍历全部候选。

### 完整函数

```cpp
std::shared_ptr<Computer<QuantT>>
    FactoryComputer() {
        return std::make_shared<Computer<QuantT>>(static_cast<QuantT*>(this), allocator_);
    }
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L181 | std::make_shared&lt;Computer&lt;QuantT&gt;&gt; | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L184"></a>

## `Quantizer::ProcessQuery`

源码位置：`src/quantization/quantizer.h:184–187`。

先从签名确认输入、返回值和 const/override，再按完整函数体的条件阅读调用点。下表保留了本函数的显式调用以及 lambda 中的调用；进入下层时用“候选实现”定位，未解析的对象由源码静态类型/运行时类型确认。

### 完整函数

```cpp
inline void
    ProcessQuery(const float* query, Computer<QuantT>& computer) const {
        return cast().ProcessQueryImpl(query, computer);
    }
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L186 | cast().ProcessQueryImpl | 函数本体；短路求值/提前返回见源码 | [FP32Quantizer&lt;metric&gt;::ProcessQueryImpl · L144](fp32_quantizer.md#L144) |

| L186 | cast | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L189"></a>

## `Quantizer::ComputeDist`

源码位置：`src/quantization/quantizer.h:189–192`。

先从签名确认输入、返回值和 const/override，再按完整函数体的条件阅读调用点。下表保留了本函数的显式调用以及 lambda 中的调用；进入下层时用“候选实现”定位，未解析的对象由源码静态类型/运行时类型确认。

### 完整函数

```cpp
inline void
    ComputeDist(Computer<QuantT>& computer, const uint8_t* codes, float* dists) const {
        return cast().ComputeDistImpl(computer, codes, dists);
    }
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L191 | cast().ComputeDistImpl | 函数本体；短路求值/提前返回见源码 | [FP32Quantizer&lt;metric&gt;::ComputeDistImpl · L164](fp32_quantizer.md#L164) |

| L191 | cast | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L194"></a>

## `Quantizer::ComputeDistWithThreshold`

源码位置：`src/quantization/quantizer.h:194–205`。

先从签名确认输入、返回值和 const/override，再按完整函数体的条件阅读调用点。下表保留了本函数的显式调用以及 lambda 中的调用；进入下层时用“候选实现”定位，未解析的对象由源码静态类型/运行时类型确认。

### 完整函数

```cpp
inline bool
    ComputeDistWithThreshold(Computer<QuantT>& computer,
                             const uint8_t* codes,
                             float threshold,
                             float* dists) const {
        if constexpr (HasComputeDistWithThresholdImpl<QuantT>::value) {
            return cast().ComputeDistWithThresholdImpl(computer, codes, threshold, dists);
        } else {
            cast().ComputeDistImpl(computer, codes, dists);
            return false;
        }
    }
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L200 | cast().ComputeDistWithThresholdImpl | if_statement@199 (HasComputeDistWithThresholdImpl&lt;QuantT&gt;::value) | 当前参考未静态绑定；见下方边界说明 |

| L200 | cast | if_statement@199 (HasComputeDistWithThresholdImpl&lt;QuantT&gt;::value) | 当前参考未静态绑定；见下方边界说明 |

| L202 | cast().ComputeDistImpl | if_statement@199 (HasComputeDistWithThresholdImpl&lt;QuantT&gt;::value) [else 分支] | [FP32Quantizer&lt;metric&gt;::ComputeDistImpl · L164](fp32_quantizer.md#L164) |

| L202 | cast | if_statement@199 (HasComputeDistWithThresholdImpl&lt;QuantT&gt;::value) [else 分支] | 当前参考未静态绑定；见下方边界说明 |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L207"></a>

## `Quantizer::ComputeDistWithLowerBound`

源码位置：`src/quantization/quantizer.h:207–221`。

先从签名确认输入、返回值和 const/override，再按完整函数体的条件阅读调用点。下表保留了本函数的显式调用以及 lambda 中的调用；进入下层时用“候选实现”定位，未解析的对象由源码静态类型/运行时类型确认。

### 完整函数

```cpp
inline bool
    ComputeDistWithLowerBound(Computer<QuantT>& computer,
                              const uint8_t* codes,
                              float* dists,
                              float* lower_bound) const {
        if constexpr (HasComputeDistWithLowerBoundImpl<QuantT>::value) {
            return cast().ComputeDistWithLowerBoundImpl(computer, codes, dists, lower_bound);
        } else {
            cast().ComputeDistImpl(computer, codes, dists);
            if (lower_bound != nullptr) {
                *lower_bound = std::numeric_limits<float>::max();
            }
            return false;
        }
    }
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L213 | cast().ComputeDistWithLowerBoundImpl | if_statement@212 (HasComputeDistWithLowerBoundImpl&lt;QuantT&gt;::value) | 当前参考未静态绑定；见下方边界说明 |

| L213 | cast | if_statement@212 (HasComputeDistWithLowerBoundImpl&lt;QuantT&gt;::value) | 当前参考未静态绑定；见下方边界说明 |

| L215 | cast().ComputeDistImpl | if_statement@212 (HasComputeDistWithLowerBoundImpl&lt;QuantT&gt;::value) [else 分支] | [FP32Quantizer&lt;metric&gt;::ComputeDistImpl · L164](fp32_quantizer.md#L164) |

| L215 | cast | if_statement@212 (HasComputeDistWithLowerBoundImpl&lt;QuantT&gt;::value) [else 分支] | 当前参考未静态绑定；见下方边界说明 |

| L217 | std::numeric_limits&lt;float&gt;::max | if_statement@212 (HasComputeDistWithLowerBoundImpl&lt;QuantT&gt;::value) [else 分支] → if_statement@216 (lower_bound != nullptr) | 当前参考未静态绑定；见下方边界说明 |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L223"></a>

## `Quantizer::ComputeDist`

源码位置：`src/quantization/quantizer.h:223–228`。

先从签名确认输入、返回值和 const/override，再按完整函数体的条件阅读调用点。下表保留了本函数的显式调用以及 lambda 中的调用；进入下层时用“候选实现”定位，未解析的对象由源码静态类型/运行时类型确认。

### 完整函数

```cpp
inline float
    ComputeDist(Computer<QuantT>& computer, const uint8_t* codes) const {
        float dist = 0.0F;
        cast().ComputeDistImpl(computer, codes, &dist);
        return dist;
    }
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L226 | cast().ComputeDistImpl | 函数本体；短路求值/提前返回见源码 | [FP32Quantizer&lt;metric&gt;::ComputeDistImpl · L164](fp32_quantizer.md#L164) |

| L226 | cast | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L230"></a>

## `Quantizer::ScanBatchDists`

源码位置：`src/quantization/quantizer.h:230–236`。

先从签名确认输入、返回值和 const/override，再按完整函数体的条件阅读调用点。下表保留了本函数的显式调用以及 lambda 中的调用；进入下层时用“候选实现”定位，未解析的对象由源码静态类型/运行时类型确认。

### 完整函数

```cpp
inline void
    ScanBatchDists(Computer<QuantT>& computer,
                   uint64_t count,
                   const uint8_t* codes,
                   float* dists) const {
        return cast().ScanBatchDistImpl(computer, count, codes, dists);
    }
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L235 | cast().ScanBatchDistImpl | 函数本体；短路求值/提前返回见源码 | [Quantizer::ScanBatchDistImpl · L290](quantizer_h.md#L290)；[FP32Quantizer&lt;metric&gt;::ScanBatchDistImpl · L132](fp32_quantizer.md#L132) |

| L235 | cast | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L238"></a>

## `Quantizer::ScanBatchDistsWithThreshold`

源码位置：`src/quantization/quantizer.h:238–247`。

先从签名确认输入、返回值和 const/override，再按完整函数体的条件阅读调用点。下表保留了本函数的显式调用以及 lambda 中的调用；进入下层时用“候选实现”定位，未解析的对象由源码静态类型/运行时类型确认。

### 完整函数

```cpp
inline void
    ScanBatchDistsWithThreshold(Computer<QuantT>& computer,
                                uint64_t count,
                                const uint8_t* codes,
                                float threshold,
                                float* dists) const {
        for (uint64_t i = 0; i < count; ++i) {
            this->ComputeDistWithThreshold(computer, codes + i * code_size_, threshold, dists + i);
        }
    }
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L245 | this-&gt;ComputeDistWithThreshold | for_statement@244 i &lt; count | [Quantizer::ComputeDistWithThreshold · L194](quantizer_h.md#L194) |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L249"></a>

## `Quantizer::ComputeDistsBatch4`

源码位置：`src/quantization/quantizer.h:249–268`。

先从签名确认输入、返回值和 const/override，再按完整函数体的条件阅读调用点。下表保留了本函数的显式调用以及 lambda 中的调用；进入下层时用“候选实现”定位，未解析的对象由源码静态类型/运行时类型确认。

### 完整函数

```cpp
inline void
    ComputeDistsBatch4(Computer<QuantT>& computer,
                       const uint8_t* codes1,
                       const uint8_t* codes2,
                       const uint8_t* codes3,
                       const uint8_t* codes4,
                       float& dists1,
                       float& dists2,
                       float& dists3,
                       float& dists4) const {
        if constexpr (HasComputeDistsBatch4Impl<QuantT>::value) {
            cast().ComputeDistsBatch4Impl(
                computer, codes1, codes2, codes3, codes4, dists1, dists2, dists3, dists4);
        } else {
            cast().ComputeDistImpl(computer, codes1, &dists1);
            cast().ComputeDistImpl(computer, codes2, &dists2);
            cast().ComputeDistImpl(computer, codes3, &dists3);
            cast().ComputeDistImpl(computer, codes4, &dists4);
        }
    }
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L260 | cast().ComputeDistsBatch4Impl | if_statement@259 (HasComputeDistsBatch4Impl&lt;QuantT&gt;::value) | [FP32Quantizer&lt;metric&gt;::ComputeDistsBatch4Impl · L191](fp32_quantizer.md#L191) |

| L260 | cast | if_statement@259 (HasComputeDistsBatch4Impl&lt;QuantT&gt;::value) | 当前参考未静态绑定；见下方边界说明 |

| L263 | cast().ComputeDistImpl | if_statement@259 (HasComputeDistsBatch4Impl&lt;QuantT&gt;::value) [else 分支] | [FP32Quantizer&lt;metric&gt;::ComputeDistImpl · L164](fp32_quantizer.md#L164) |

| L263 | cast | if_statement@259 (HasComputeDistsBatch4Impl&lt;QuantT&gt;::value) [else 分支] | 当前参考未静态绑定；见下方边界说明 |

| L264 | cast().ComputeDistImpl | if_statement@259 (HasComputeDistsBatch4Impl&lt;QuantT&gt;::value) [else 分支] | [FP32Quantizer&lt;metric&gt;::ComputeDistImpl · L164](fp32_quantizer.md#L164) |

| L264 | cast | if_statement@259 (HasComputeDistsBatch4Impl&lt;QuantT&gt;::value) [else 分支] | 当前参考未静态绑定；见下方边界说明 |

| L265 | cast().ComputeDistImpl | if_statement@259 (HasComputeDistsBatch4Impl&lt;QuantT&gt;::value) [else 分支] | [FP32Quantizer&lt;metric&gt;::ComputeDistImpl · L164](fp32_quantizer.md#L164) |

| L265 | cast | if_statement@259 (HasComputeDistsBatch4Impl&lt;QuantT&gt;::value) [else 分支] | 当前参考未静态绑定；见下方边界说明 |

| L266 | cast().ComputeDistImpl | if_statement@259 (HasComputeDistsBatch4Impl&lt;QuantT&gt;::value) [else 分支] | [FP32Quantizer&lt;metric&gt;::ComputeDistImpl · L164](fp32_quantizer.md#L164) |

| L266 | cast | if_statement@259 (HasComputeDistsBatch4Impl&lt;QuantT&gt;::value) [else 分支] | 当前参考未静态绑定；见下方边界说明 |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L270"></a>

## `Quantizer::ReleaseComputer`

源码位置：`src/quantization/quantizer.h:270–273`。

先从签名确认输入、返回值和 const/override，再按完整函数体的条件阅读调用点。下表保留了本函数的显式调用以及 lambda 中的调用；进入下层时用“候选实现”定位，未解析的对象由源码静态类型/运行时类型确认。

### 完整函数

```cpp
inline void
    ReleaseComputer(Computer<QuantT>& computer) const {
        cast().ReleaseComputerImpl(computer);
    }
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L272 | cast().ReleaseComputerImpl | 函数本体；短路求值/提前返回见源码 | [Quantizer::ReleaseComputerImpl · L279](quantizer_h.md#L279)；[FP32Quantizer&lt;metric&gt;::ReleaseComputerImpl · L261](fp32_quantizer.md#L261) |

| L272 | cast | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L279"></a>

## `Quantizer::ReleaseComputerImpl`

源码位置：`src/quantization/quantizer.h:279–282`。

先从签名确认输入、返回值和 const/override，再按完整函数体的条件阅读调用点。下表保留了本函数的显式调用以及 lambda 中的调用；进入下层时用“候选实现”定位，未解析的对象由源码静态类型/运行时类型确认。

### 完整函数

```cpp
void
    ReleaseComputerImpl(Computer<QuantT>& computer) const {
        allocator_->Deallocate(computer.buf_);
    }
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L281 | allocator_-&gt;Deallocate | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L290"></a>

## `Quantizer::ScanBatchDistImpl`

源码位置：`src/quantization/quantizer.h:290–298`。

先从签名确认输入、返回值和 const/override，再按完整函数体的条件阅读调用点。下表保留了本函数的显式调用以及 lambda 中的调用；进入下层时用“候选实现”定位，未解析的对象由源码静态类型/运行时类型确认。

### 完整函数

```cpp
void
    ScanBatchDistImpl(Computer<QuantT>& computer,
                      uint64_t count,
                      const uint8_t* codes,
                      float* dists) const {
        for (uint64_t i = 0; i < count; ++i) {
            cast().ComputeDistImpl(computer, codes + i * code_size_, dists + i);
        }
    }
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L296 | cast().ComputeDistImpl | for_statement@295 i &lt; count | [FP32Quantizer&lt;metric&gt;::ComputeDistImpl · L164](fp32_quantizer.md#L164) |

| L296 | cast | for_statement@295 i &lt; count | 当前参考未静态绑定；见下方边界说明 |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L300"></a>

## `Quantizer::Name`

源码位置：`src/quantization/quantizer.h:300–303`。

先从签名确认输入、返回值和 const/override，再按完整函数体的条件阅读调用点。下表保留了本函数的显式调用以及 lambda 中的调用；进入下层时用“候选实现”定位，未解析的对象由源码静态类型/运行时类型确认。

### 完整函数

```cpp
[[nodiscard]] virtual std::string
    Name() const {
        return cast().NameImpl();
    }
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L302 | cast().NameImpl | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L302 | cast | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L305"></a>

## `Quantizer::Metric`

源码位置：`src/quantization/quantizer.h:305–308`。

先从签名确认输入、返回值和 const/override，再按完整函数体的条件阅读调用点。下表保留了本函数的显式调用以及 lambda 中的调用；进入下层时用“候选实现”定位，未解析的对象由源码静态类型/运行时类型确认。

### 完整函数

```cpp
[[nodiscard]] MetricType
    Metric() const {
        return this->metric_;
    }
```

### 函数内部调用点：不省略标准库和辅助调用

此函数体没有显式函数调用表达式。赋值、成员初始化和隐式操作请看上面的完整源码。


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L309"></a>

## `Quantizer::HoldMolds`

源码位置：`src/quantization/quantizer.h:309–312`。

先从签名确认输入、返回值和 const/override，再按完整函数体的条件阅读调用点。下表保留了本函数的显式调用以及 lambda 中的调用；进入下层时用“候选实现”定位，未解析的对象由源码静态类型/运行时类型确认。

### 完整函数

```cpp
[[nodiscard]] bool
    HoldMolds() const {
        return this->hold_molds_;
    }
```

### 函数内部调用点：不省略标准库和辅助调用

此函数体没有显式函数调用表达式。赋值、成员初始化和隐式操作请看上面的完整源码。


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L325"></a>

## `Quantizer::GetCodeSize`

源码位置：`src/quantization/quantizer.h:325–328`。

先从签名确认输入、返回值和 const/override，再按完整函数体的条件阅读调用点。下表保留了本函数的显式调用以及 lambda 中的调用；进入下层时用“候选实现”定位，未解析的对象由源码静态类型/运行时类型确认。

### 完整函数

```cpp
inline uint64_t
    GetCodeSize() const {
        return this->code_size_;
    }
```

### 函数内部调用点：不省略标准库和辅助调用

此函数体没有显式函数调用表达式。赋值、成员初始化和隐式操作请看上面的完整源码。


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L330"></a>

## `Quantizer::GetQueryCodeSize`

源码位置：`src/quantization/quantizer.h:330–333`。

先从签名确认输入、返回值和 const/override，再按完整函数体的条件阅读调用点。下表保留了本函数的显式调用以及 lambda 中的调用；进入下层时用“候选实现”定位，未解析的对象由源码静态类型/运行时类型确认。

### 完整函数

```cpp
inline uint64_t
    GetQueryCodeSize() const {
        return this->query_code_size_;
    }
```

### 函数内部调用点：不省略标准库和辅助调用

此函数体没有显式函数调用表达式。赋值、成员初始化和隐式操作请看上面的完整源码。


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L340"></a>

## `Quantizer::GetDim`

源码位置：`src/quantization/quantizer.h:340–343`。

先从签名确认输入、返回值和 const/override，再按完整函数体的条件阅读调用点。下表保留了本函数的显式调用以及 lambda 中的调用；进入下层时用“候选实现”定位，未解析的对象由源码静态类型/运行时类型确认。

### 完整函数

```cpp
inline int
    GetDim() const {
        return this->dim_;
    }
```

### 函数内部调用点：不省略标准库和辅助调用

此函数体没有显式函数调用表达式。赋值、成员初始化和隐式操作请看上面的完整源码。


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L346"></a>

## `Quantizer::& cast`

源码位置：`src/quantization/quantizer.h:346–349`。

先从签名确认输入、返回值和 const/override，再按完整函数体的条件阅读调用点。下表保留了本函数的显式调用以及 lambda 中的调用；进入下层时用“候选实现”定位，未解析的对象由源码静态类型/运行时类型确认。

### 完整函数

```cpp
inline QuantT&
    cast() {
        return static_cast<QuantT&>(*this);
    }
```

### 函数内部调用点：不省略标准库和辅助调用

此函数体没有显式函数调用表达式。赋值、成员初始化和隐式操作请看上面的完整源码。


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L351"></a>

## `Quantizer::& cast`

源码位置：`src/quantization/quantizer.h:351–354`。

先从签名确认输入、返回值和 const/override，再按完整函数体的条件阅读调用点。下表保留了本函数的显式调用以及 lambda 中的调用；进入下层时用“候选实现”定位，未解析的对象由源码静态类型/运行时类型确认。

### 完整函数

```cpp
inline const QuantT&
    cast() const {
        return static_cast<const QuantT&>(*this);
    }
```

### 函数内部调用点：不省略标准库和辅助调用

此函数体没有显式函数调用表达式。赋值、成员初始化和隐式操作请看上面的完整源码。


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。
