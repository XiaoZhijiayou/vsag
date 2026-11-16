# nearest_centroid_assign.cpp：逐函数完整源码与调用点

[主讲解](../code_walkthrough.md) · [函数总目录](README.md)

源码：[ src/impl/cluster/nearest_centroid_assign.cpp ](../../../../src/impl/cluster/nearest_centroid_assign.cpp)。基线 `fd363937`。以下源码函数体完整保留；调用点表是语法树中的显式调用表达式，按源码位置排列，不代表 C++ 参数求值顺序。表中“候选实现”需结合类型和参数选分支，不能将同名函数全部视为必经路径。

- [NearestCentroidAssign · L39](nearest_centroid_assign.md#L39)


<a id="L39"></a>

## `NearestCentroidAssign`

源码位置：`src/impl/cluster/nearest_centroid_assign.cpp:39–168`。

先从签名确认输入、返回值和 const/override，再按完整函数体的条件阅读调用点。下表保留了本函数的显式调用以及 lambda 中的调用；进入下层时用“候选实现”定位，未解析的对象由源码静态类型/运行时类型确认。

### 完整函数

```cpp
double
NearestCentroidAssign(const float* centroids,
                      uint64_t centroid_count,
                      const float* queries,
                      uint64_t query_count,
                      uint64_t dim,
                      const SafeThreadPoolPtr& thread_pool,
                      Allocator* allocator,
                      int32_t* labels) {
    double error = 0.0;
    std::mutex error_mutex;
    if (centroids == nullptr || queries == nullptr || labels == nullptr || allocator == nullptr ||
        thread_pool == nullptr || centroid_count == 0 || query_count == 0 || dim == 0 ||
        centroid_count > static_cast<uint64_t>(std::numeric_limits<int32_t>::max()) ||
        dim > static_cast<uint64_t>(std::numeric_limits<int32_t>::max())) {
        throw VsagException(ErrorType::INVALID_ARGUMENT,
                            "invalid nearest-centroid assignment input");
    }
    const auto& thread_pool_ref = thread_pool;
    auto bs = ASSIGN_BS;
    std::vector<std::future<void>> futures;

    auto wait_futures_and_clear = [&]() {
        for (auto& future : futures) {
            future.wait();
        }
        futures.clear();
    };

    const auto distance_batch_size = std::min(QUERY_BS, query_count);
    ByteBuffer y_sqr_buffer(centroid_count * sizeof(float), allocator);
    ByteBuffer distances_buffer(centroid_count * distance_batch_size * sizeof(float), allocator);
    auto* y_sqr = reinterpret_cast<float*>(y_sqr_buffer.data);
    auto* distances = reinterpret_cast<float*>(distances_buffer.data);

    auto compute_ip_func = [&](uint64_t start, uint64_t end) -> void {
        for (uint64_t i = start; i < end; ++i) {
            y_sqr[i] = FP32ComputeIP(centroids + i * dim, centroids + i * dim, dim);
        }
    };
    for (uint64_t i = 0; i < centroid_count; i += bs) {
        futures.emplace_back(
            thread_pool_ref->GeneralEnqueue(compute_ip_func, i, std::min(i + bs, centroid_count)));
    }
    wait_futures_and_clear();

    for (uint64_t i = 0; i < query_count; i += QUERY_BS) {
        auto end = std::min(i + QUERY_BS, query_count);
        auto cur_query_count = end - i;
        auto* cur_label = labels + i;

        // Try the AMX BF16 GEMM fast path first.  It returns false if
        // AMX-BF16 isn't available at runtime; in that case (or when the
        // shape is too small to amortize tile-config / packing overhead)
        // fall back to the BLAS SGEMM path.
        //
        // Math equivalence:
        //   SGEMM(ColMajor, Trans, NoTrans, M=centroid_count, N=cur_query_count, K=dim,
        //         alpha=-2, A=centroids (lda=dim), B=queries+i*dim (ldb=dim),
        //         beta=0, C=distances (ldc=centroid_count))
        //   produces  distances[m + n*centroid_count] = -2 * < centroid_m, query_{i+n} >
        // The AMX kernel takes the same inputs interpreted as row-major
        // (centroid_count x dim) and (cur_query_count x dim) and writes the same
        // column-major output.
        constexpr uint64_t amx_bf16_min_dim = 32;
        constexpr uint64_t amx_bf16_min_m = 16;
        constexpr uint64_t amx_bf16_min_n = 16;
        bool used_amx = false;
        if (dim >= amx_bf16_min_dim && centroid_count >= amx_bf16_min_m &&
            cur_query_count >= amx_bf16_min_n && SimdStatus::SupportAMXBF16()) {
            used_amx = amx::SgemmBF16IPColMajorOut(static_cast<int64_t>(centroid_count),
                                                   static_cast<int64_t>(cur_query_count),
                                                   static_cast<int64_t>(dim),
                                                   -2.0F,
                                                   centroids,
                                                   queries + i * dim,
                                                   distances,
                                                   static_cast<int64_t>(centroid_count));
        }
        if (!used_amx) {
            BlasFunction::Sgemm(BlasFunction::ColMajor,
                                BlasFunction::Trans,
                                BlasFunction::NoTrans,
                                static_cast<int32_t>(centroid_count),
                                static_cast<int32_t>(cur_query_count),
                                static_cast<int32_t>(dim),
                                -2.0F,
                                centroids,
                                static_cast<int32_t>(dim),
                                queries + i * dim,
                                static_cast<int32_t>(dim),
                                0.0F,
                                distances,
                                static_cast<int32_t>(centroid_count));
        }

        auto batch_offset = i;
        auto assign_labels_func = [&, batch_offset](uint64_t start, uint64_t end) -> void {
            omp_set_num_threads(1);
            double thread_local_error = 0.0;
            for (uint64_t j = start; j < end; ++j) {
                BlasFunction::Saxpy(static_cast<int32_t>(centroid_count),
                                    1.0,
                                    y_sqr,
                                    1,
                                    distances + j * centroid_count,
                                    1);
                auto* min_elem = std::min_element(distances + j * centroid_count,
                                                  distances + j * centroid_count + centroid_count);
                auto x_sqr = FP32ComputeIP(
                    queries + (batch_offset + j) * dim, queries + (batch_offset + j) * dim, dim);
                auto min_index = std::distance(distances + j * centroid_count, min_elem);
                thread_local_error += static_cast<double>(*min_elem + x_sqr);
                if (min_index != cur_label[j]) {
                    cur_label[j] = static_cast<int32_t>(min_index);
                }
            }
            {
                std::lock_guard<std::mutex> lock(error_mutex);
                error += thread_local_error;
            }
        };
        for (uint64_t j = 0; j < cur_query_count; j += bs) {
            futures.emplace_back(thread_pool_ref->GeneralEnqueue(
                assign_labels_func, j, std::min(j + bs, cur_query_count)));
        }
        wait_futures_and_clear();
    }
    return error / static_cast<double>(query_count);
}
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L52 | std::numeric_limits&lt;int32_t&gt;::max | if_statement@50 (centroids == nullptr &#124;&#124; queries == nullptr &#124;&#124; labels == nullptr &#124;&#124; allocator == nullptr &#124;&#124; thread_pool == nullptr &#124;&#124; centroid_count == 0 &#124;&#124; query_count == 0 &#124;&#124; dim == 0 &#124;&#124; centroid_count &gt; static_cast&lt;uint64_t&gt;(std::numeric_limits&lt;int32_t&gt;::max()) &#124;&#124; dim &gt; static_cast&lt;uint64_t&gt;(std::numeric_limits&lt;int32_t&gt;::max())) | 当前参考未静态绑定；见下方边界说明 |

| L53 | std::numeric_limits&lt;int32_t&gt;::max | if_statement@50 (centroids == nullptr &#124;&#124; queries == nullptr &#124;&#124; labels == nullptr &#124;&#124; allocator == nullptr &#124;&#124; thread_pool == nullptr &#124;&#124; centroid_count == 0 &#124;&#124; query_count == 0 &#124;&#124; dim == 0 &#124;&#124; centroid_count &gt; static_cast&lt;uint64_t&gt;(std::numeric_limits&lt;int32_t&gt;::max()) &#124;&#124; dim &gt; static_cast&lt;uint64_t&gt;(std::numeric_limits&lt;int32_t&gt;::max())) | 当前参考未静态绑定；见下方边界说明 |

| L54 | VsagException | if_statement@50 (centroids == nullptr &#124;&#124; queries == nullptr &#124;&#124; labels == nullptr &#124;&#124; allocator == nullptr &#124;&#124; thread_pool == nullptr &#124;&#124; centroid_count == 0 &#124;&#124; query_count == 0 &#124;&#124; dim == 0 &#124;&#124; centroid_count &gt; static_cast&lt;uint64_t&gt;(std::numeric_limits&lt;int32_t&gt;::max()) &#124;&#124; dim &gt; static_cast&lt;uint64_t&gt;(std::numeric_limits&lt;int32_t&gt;::max())) | 当前参考未静态绑定；见下方边界说明 |

| L63 | future.wait | lambda@61（定义体，执行时间取决于调用/调度） → for_range_loop@62 | 当前参考未静态绑定；见下方边界说明 |

| L65 | futures.clear | lambda@61（定义体，执行时间取决于调用/调度） | 当前参考未静态绑定；见下方边界说明 |

| L68 | std::min | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L76 | FP32ComputeIP | lambda@74（定义体，执行时间取决于调用/调度） → for_statement@75 i &lt; end | 当前参考未静态绑定；见下方边界说明 |

| L80 | futures.emplace_back | for_statement@79 i &lt; centroid_count | 当前参考未静态绑定；见下方边界说明 |

| L81 | thread_pool_ref-&gt;GeneralEnqueue | for_statement@79 i &lt; centroid_count | 当前参考未静态绑定；见下方边界说明 |

| L81 | std::min | for_statement@79 i &lt; centroid_count | 当前参考未静态绑定；见下方边界说明 |

| L83 | wait_futures_and_clear | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L86 | std::min | for_statement@85 i &lt; query_count | 当前参考未静态绑定；见下方边界说明 |

| L108 | SimdStatus::SupportAMXBF16 | for_statement@85 i &lt; query_count → if_statement@107 (dim &gt;= amx_bf16_min_dim && centroid_count &gt;= amx_bf16_min_m && cur_query_count &gt;= amx_bf16_min_n && SimdStatus::SupportAMXBF16()) | 当前参考未静态绑定；见下方边界说明 |

| L109 | amx::SgemmBF16IPColMajorOut | for_statement@85 i &lt; query_count → if_statement@107 (dim &gt;= amx_bf16_min_dim && centroid_count &gt;= amx_bf16_min_m && cur_query_count &gt;= amx_bf16_min_n && SimdStatus::SupportAMXBF16()) | 当前参考未静态绑定；见下方边界说明 |

| L119 | BlasFunction::Sgemm | for_statement@85 i &lt; query_count → if_statement@118 (!used_amx) | 当前参考未静态绑定；见下方边界说明 |

| L137 | omp_set_num_threads | for_statement@85 i &lt; query_count → lambda@136（定义体，执行时间取决于调用/调度） | 当前参考未静态绑定；见下方边界说明 |

| L140 | BlasFunction::Saxpy | for_statement@85 i &lt; query_count → lambda@136（定义体，执行时间取决于调用/调度） → for_statement@139 j &lt; end | 当前参考未静态绑定；见下方边界说明 |

| L146 | std::min_element | for_statement@85 i &lt; query_count → lambda@136（定义体，执行时间取决于调用/调度） → for_statement@139 j &lt; end | 当前参考未静态绑定；见下方边界说明 |

| L148 | FP32ComputeIP | for_statement@85 i &lt; query_count → lambda@136（定义体，执行时间取决于调用/调度） → for_statement@139 j &lt; end | 当前参考未静态绑定；见下方边界说明 |

| L150 | std::distance | for_statement@85 i &lt; query_count → lambda@136（定义体，执行时间取决于调用/调度） → for_statement@139 j &lt; end | 当前参考未静态绑定；见下方边界说明 |

| L162 | futures.emplace_back | for_statement@85 i &lt; query_count → for_statement@161 j &lt; cur_query_count | 当前参考未静态绑定；见下方边界说明 |

| L162 | thread_pool_ref-&gt;GeneralEnqueue | for_statement@85 i &lt; query_count → for_statement@161 j &lt; cur_query_count | 当前参考未静态绑定；见下方边界说明 |

| L163 | std::min | for_statement@85 i &lt; query_count → for_statement@161 j &lt; cur_query_count | 当前参考未静态绑定；见下方边界说明 |

| L165 | wait_futures_and_clear | for_statement@85 i &lt; query_count | 当前参考未静态绑定；见下方边界说明 |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。
