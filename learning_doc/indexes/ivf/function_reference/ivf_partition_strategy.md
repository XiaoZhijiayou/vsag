# ivf_partition_strategy.cpp：逐函数完整源码与调用点

[主讲解](../code_walkthrough.md) · [函数总目录](README.md)

源码：[ src/algorithm/ivf/ivf_partition_strategy.cpp ](../../../../src/algorithm/ivf/ivf_partition_strategy.cpp)。基线 `fd363937`。以下源码函数体完整保留；调用点表是语法树中的显式调用表达式，按源码位置排列，不代表 C++ 参数求值顺序。表中“候选实现”需结合类型和参数选分支，不能将同名函数全部视为必经路径。

- [IVFPartitionStrategy::GetResidual · L22](ivf_partition_strategy.md#L22)


<a id="L22"></a>

## `IVFPartitionStrategy::GetResidual`

源码位置：`src/algorithm/ivf/ivf_partition_strategy.cpp:22–36`。

先从签名确认输入、返回值和 const/override，再按完整函数体的条件阅读调用点。下表保留了本函数的显式调用以及 lambda 中的调用；进入下层时用“候选实现”定位，未解析的对象由源码静态类型/运行时类型确认。

### 完整函数

```cpp
void
IVFPartitionStrategy::GetResidual(
    uint64_t n, const float* x, float* residuals, float* centroids, BucketIdType* assign) {
    // TODO: Directly implement c = a - b.
    memcpy(residuals, x, sizeof(float) * n * dim_);
    for (uint64_t i = 0; i < n; ++i) {
        BucketIdType bucket_id = assign[i];
        BlasFunction::Saxpy(static_cast<int32_t>(dim_),
                            -1.0,
                            centroids + bucket_id * dim_,
                            1,
                            residuals + i * dim_,
                            1);
    }
}
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L26 | memcpy | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L29 | BlasFunction::Saxpy | for_statement@27 i &lt; n | 当前参考未静态绑定；见下方边界说明 |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。
