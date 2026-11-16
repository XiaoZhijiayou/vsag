# kmeans_cluster.cpp：逐函数完整源码与调用点

[主讲解](../code_walkthrough.md) · [函数总目录](README.md)

源码：[ src/impl/cluster/kmeans_cluster.cpp ](../../../../src/impl/cluster/kmeans_cluster.cpp)。基线 `fd363937`。以下源码函数体完整保留；调用点表是语法树中的显式调用表达式，按源码位置排列，不代表 C++ 参数求值顺序。表中“候选实现”需结合类型和参数选分支，不能将同名函数全部视为必经路径。

- [KMeansCluster::KMeansCluster · L34](kmeans_cluster.md#L34)

- [KMeansCluster::~KMeansCluster · L41](kmeans_cluster.md#L41)

- [KMeansCluster::Run · L48](kmeans_cluster.md#L48)

- [KMeansCluster::find_nearest_one_with_hgraph · L230](kmeans_cluster.md#L230)

- [KMeansCluster::select_initial_centroids_random · L290](kmeans_cluster.md#L290)

- [KMeansCluster::select_initial_centroids_kmeans_plus_plus · L305](kmeans_cluster.md#L305)


<a id="L34"></a>

## `KMeansCluster::KMeansCluster`

源码位置：`src/impl/cluster/kmeans_cluster.cpp:34–39`。

先从签名确认输入、返回值和 const/override，再按完整函数体的条件阅读调用点。下表保留了本函数的显式调用以及 lambda 中的调用；进入下层时用“候选实现”定位，未解析的对象由源码静态类型/运行时类型确认。

### 完整函数

```cpp
KMeansCluster::KMeansCluster(int32_t dim, Allocator* allocator, SafeThreadPoolPtr thread_pool)
    : dim_(dim), allocator_(allocator), thread_pool_(std::move(thread_pool)) {
    if (thread_pool_ == nullptr) {
        this->thread_pool_ = SafeThreadPool::FactoryDefaultThreadPool();
    }
}
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L37 | SafeThreadPool::FactoryDefaultThreadPool | if_statement@36 (thread_pool_ == nullptr) | 当前参考未静态绑定；见下方边界说明 |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L41"></a>

## `KMeansCluster::~KMeansCluster`

源码位置：`src/impl/cluster/kmeans_cluster.cpp:41–46`。

先从签名确认输入、返回值和 const/override，再按完整函数体的条件阅读调用点。下表保留了本函数的显式调用以及 lambda 中的调用；进入下层时用“候选实现”定位，未解析的对象由源码静态类型/运行时类型确认。

### 完整函数

```cpp
KMeansCluster::~KMeansCluster() {
    if (k_centroids_ != nullptr) {
        allocator_->Deallocate(k_centroids_);
        k_centroids_ = nullptr;
    }
}
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L43 | allocator_-&gt;Deallocate | if_statement@42 (k_centroids_ != nullptr) | 当前参考未静态绑定；见下方边界说明 |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L48"></a>

## `KMeansCluster::Run`

源码位置：`src/impl/cluster/kmeans_cluster.cpp:48–228`。

KMeans 输入 k、样本、轮数等，输出分配标签并更新成员中心数组。每轮分配样本、分块累加、归并、取均值、处理空簇，再判断收敛。线程池提交与 future 等待是控制流的一部分。

### 完整函数

```cpp
Vector<int>
KMeansCluster::Run(uint32_t k,
                   const float* datas,
                   uint64_t count,
                   int iter,
                   double* err,
                   bool use_mse_for_convergence,
                   float threshold,
                   KMeansInitMethod init_method,
                   std::optional<uint32_t> random_seed,
                   bool deterministic_reduction) {
    if (k == 0) {
        throw VsagException(ErrorType::INVALID_ARGUMENT, "k must be positive");
    }
    if (count == 0) {
        throw VsagException(ErrorType::INVALID_ARGUMENT, "count must be positive");
    }
    if (datas == nullptr) {
        throw VsagException(ErrorType::INVALID_ARGUMENT, "datas cannot be null");
    }
    if (k > count) {
        throw VsagException(ErrorType::INVALID_ARGUMENT, "k cannot be larger than count");
    }

    if (k_centroids_ != nullptr) {
        allocator_->Deallocate(k_centroids_);
        k_centroids_ = nullptr;
    }
    uint64_t size = static_cast<uint64_t>(k) * static_cast<uint64_t>(dim_) * sizeof(float);
    k_centroids_ = static_cast<float*>(allocator_->Allocate(size));

    std::random_device rd;
    std::mt19937 gen(random_seed.has_value() ? *random_seed : rd());

    if (init_method == KMeansInitMethod::KMEANS_PLUS_PLUS) {
        select_initial_centroids_kmeans_plus_plus(datas, count, k, gen);
    } else {
        select_initial_centroids_random(datas, count, k, gen);
    }

    double total_err = std::numeric_limits<double>::max();
    double last_err = std::numeric_limits<double>::max();
    Vector<int32_t> labels(count, -1, this->allocator_);
    std::vector<std::future<void>> futures;

    logger::trace("KMeansCluster::Run k: {}, count: {}, iter: {}", k, count, iter);
    if (k < THRESHOLD_FOR_HGRAPH) {
        logger::trace("KMeansCluster::Run use blas");
    } else {
        logger::trace("KMeansCluster::Run use hgraph");
    }

    for (int it = 0; it < iter; ++it) {
        if (k < THRESHOLD_FOR_HGRAPH) {
            total_err = NearestCentroidAssign(k_centroids_,
                                              k,
                                              datas,
                                              count,
                                              static_cast<uint64_t>(dim_),
                                              thread_pool_,
                                              allocator_,
                                              labels.data());
        } else {
            total_err = this->find_nearest_one_with_hgraph(datas, count, k, labels);
        }
        constexpr uint64_t bs = 1024;

        Vector<int> counts(k, 0, allocator_);
        Vector<float> new_centroids(static_cast<uint64_t>(k) * dim_, 0.0F, allocator_);
        const uint64_t block_count = (count + bs - 1) / bs;
        const uint64_t centroid_values = static_cast<uint64_t>(k) * dim_;
        Vector<int> block_counts(allocator_);
        Vector<float> block_centroids(allocator_);
        if (deterministic_reduction) {
            block_counts.resize(block_count * k, 0);
            block_centroids.resize(block_count * centroid_values, 0.0F);
        }
        std::mutex merge_mutex;

        auto update_centroids_func = [&](uint64_t block_id, uint64_t start, uint64_t end) {
            omp_set_num_threads(1);
            Vector<int> local_counts(k, 0, allocator_);
            Vector<float> local_centroids(centroid_values, 0.0F, allocator_);

            for (uint64_t i = start; i < end; ++i) {
                int32_t label = labels[i];
                if (label >= 0 && label < static_cast<int32_t>(k)) {
                    local_counts[label]++;
                    BlasFunction::Saxpy(
                        dim_,
                        1.0F,
                        datas + i * dim_,
                        1,
                        local_centroids.data() + label * static_cast<uint64_t>(dim_),
                        1);
                }
            }

            if (deterministic_reduction) {
                std::copy(
                    local_counts.begin(), local_counts.end(), block_counts.data() + block_id * k);
                std::copy(local_centroids.begin(),
                          local_centroids.end(),
                          block_centroids.data() + block_id * centroid_values);
            } else {
                std::lock_guard<std::mutex> lock(merge_mutex);
                for (uint32_t j = 0; j < k; ++j) {
                    if (local_counts[j] > 0) {
                        counts[j] += local_counts[j];
                        BlasFunction::Saxpy(
                            dim_,
                            1.0F,
                            local_centroids.data() + j * static_cast<uint64_t>(dim_),
                            1,
                            new_centroids.data() + j * static_cast<uint64_t>(dim_),
                            1);
                    }
                }
            }
        };
        for (uint64_t i = 0; i < count; i += bs) {
            futures.emplace_back(thread_pool_->GeneralEnqueue(
                update_centroids_func, i / bs, i, std::min(i + bs, count)));
        }
        for (auto& future : futures) {
            future.wait();
        }
        futures.clear();
        if (deterministic_reduction) {
            for (uint64_t block_id = 0; block_id < block_count; ++block_id) {
                for (uint32_t j = 0; j < k; ++j) {
                    const auto count_offset = block_id * k + j;
                    if (block_counts[count_offset] > 0) {
                        counts[j] += block_counts[count_offset];
                        BlasFunction::Saxpy(dim_,
                                            1.0F,
                                            block_centroids.data() + block_id * centroid_values +
                                                static_cast<uint64_t>(j) * dim_,
                                            1,
                                            new_centroids.data() + static_cast<uint64_t>(j) * dim_,
                                            1);
                    }
                }
            }
        }

        std::uniform_int_distribution<uint64_t> dis(0, count - 1);
        for (int j = 0; j < k; ++j) {
            if (counts[j] > 0) {
                BlasFunction::Sscal(dim_,
                                    1.0F / static_cast<float>(counts[j]),
                                    new_centroids.data() + j * static_cast<uint64_t>(dim_),
                                    1);
                std::copy(new_centroids.data() + j * static_cast<uint64_t>(dim_),
                          new_centroids.data() + (j + 1) * static_cast<uint64_t>(dim_),
                          k_centroids_ + j * static_cast<uint64_t>(dim_));
            } else {
                auto index = dis(gen);
                for (int s = 0; s < dim_; ++s) {
                    k_centroids_[j * dim_ + s] = datas[index * dim_ + s];
                }
            }
        }

        logger::trace("[{}] KMeansCluster::Run iter: {}/{} finished, cur loss is {}",
                      get_current_time(),
                      static_cast<int>(it),
                      static_cast<int>(iter),
                      static_cast<double>(total_err));
        if (it > 0 && use_mse_for_convergence &&
            std::fabs(last_err - total_err) / static_cast<double>(count) < threshold) {
            break;
        }

        last_err = total_err;
    }
    if (err != nullptr) {
        *err = total_err;
    }
    return labels;
}
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L60 | VsagException | if_statement@59 (k == 0) | 当前参考未静态绑定；见下方边界说明 |

| L63 | VsagException | if_statement@62 (count == 0) | 当前参考未静态绑定；见下方边界说明 |

| L66 | VsagException | if_statement@65 (datas == nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L69 | VsagException | if_statement@68 (k &gt; count) | 当前参考未静态绑定；见下方边界说明 |

| L73 | allocator_-&gt;Deallocate | if_statement@72 (k_centroids_ != nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L77 | allocator_-&gt;Allocate | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L80 | random_seed.has_value | conditional_expression@80 random_seed.has_value() | 当前参考未静态绑定；见下方边界说明 |

| L80 | rd | conditional_expression@80 random_seed.has_value() | 当前参考未静态绑定；见下方边界说明 |

| L83 | select_initial_centroids_kmeans_plus_plus | if_statement@82 (init_method == KMeansInitMethod::KMEANS_PLUS_PLUS) | [KMeansCluster::select_initial_centroids_kmeans_plus_plus · L305](kmeans_cluster.md#L305) |

| L85 | select_initial_centroids_random | if_statement@82 (init_method == KMeansInitMethod::KMEANS_PLUS_PLUS) [else 分支] | [KMeansCluster::select_initial_centroids_random · L290](kmeans_cluster.md#L290) |

| L88 | std::numeric_limits&lt;double&gt;::max | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L89 | std::numeric_limits&lt;double&gt;::max | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L93 | logger::trace | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L95 | logger::trace | if_statement@94 (k &lt; THRESHOLD_FOR_HGRAPH) | 当前参考未静态绑定；见下方边界说明 |

| L97 | logger::trace | if_statement@94 (k &lt; THRESHOLD_FOR_HGRAPH) [else 分支] | 当前参考未静态绑定；见下方边界说明 |

| L102 | NearestCentroidAssign | for_statement@100 it &lt; iter → if_statement@101 (k &lt; THRESHOLD_FOR_HGRAPH) | [NearestCentroidAssign · L39](nearest_centroid_assign.md#L39) |

| L109 | labels.data | for_statement@100 it &lt; iter → if_statement@101 (k &lt; THRESHOLD_FOR_HGRAPH) | 当前参考未静态绑定；见下方边界说明 |

| L111 | this-&gt;find_nearest_one_with_hgraph | for_statement@100 it &lt; iter → if_statement@101 (k &lt; THRESHOLD_FOR_HGRAPH) [else 分支] | [KMeansCluster::find_nearest_one_with_hgraph · L230](kmeans_cluster.md#L230) |

| L122 | block_counts.resize | for_statement@100 it &lt; iter → if_statement@121 (deterministic_reduction) | 当前参考未静态绑定；见下方边界说明 |

| L123 | block_centroids.resize | for_statement@100 it &lt; iter → if_statement@121 (deterministic_reduction) | 当前参考未静态绑定；见下方边界说明 |

| L128 | omp_set_num_threads | for_statement@100 it &lt; iter → lambda@127（定义体，执行时间取决于调用/调度） | 当前参考未静态绑定；见下方边界说明 |

| L136 | BlasFunction::Saxpy | for_statement@100 it &lt; iter → lambda@127（定义体，执行时间取决于调用/调度） → for_statement@132 i &lt; end → if_statement@134 (label &gt;= 0 && label &lt; static_cast&lt;int32_t&gt;(k)) | 当前参考未静态绑定；见下方边界说明 |

| L141 | local_centroids.data | for_statement@100 it &lt; iter → lambda@127（定义体，执行时间取决于调用/调度） → for_statement@132 i &lt; end → if_statement@134 (label &gt;= 0 && label &lt; static_cast&lt;int32_t&gt;(k)) | 当前参考未静态绑定；见下方边界说明 |

| L147 | std::copy | for_statement@100 it &lt; iter → lambda@127（定义体，执行时间取决于调用/调度） → if_statement@146 (deterministic_reduction) | 当前参考未静态绑定；见下方边界说明 |

| L148 | local_counts.begin | for_statement@100 it &lt; iter → lambda@127（定义体，执行时间取决于调用/调度） → if_statement@146 (deterministic_reduction) | 当前参考未静态绑定；见下方边界说明 |

| L148 | local_counts.end | for_statement@100 it &lt; iter → lambda@127（定义体，执行时间取决于调用/调度） → if_statement@146 (deterministic_reduction) | 当前参考未静态绑定；见下方边界说明 |

| L148 | block_counts.data | for_statement@100 it &lt; iter → lambda@127（定义体，执行时间取决于调用/调度） → if_statement@146 (deterministic_reduction) | 当前参考未静态绑定；见下方边界说明 |

| L149 | std::copy | for_statement@100 it &lt; iter → lambda@127（定义体，执行时间取决于调用/调度） → if_statement@146 (deterministic_reduction) | 当前参考未静态绑定；见下方边界说明 |

| L149 | local_centroids.begin | for_statement@100 it &lt; iter → lambda@127（定义体，执行时间取决于调用/调度） → if_statement@146 (deterministic_reduction) | 当前参考未静态绑定；见下方边界说明 |

| L150 | local_centroids.end | for_statement@100 it &lt; iter → lambda@127（定义体，执行时间取决于调用/调度） → if_statement@146 (deterministic_reduction) | 当前参考未静态绑定；见下方边界说明 |

| L151 | block_centroids.data | for_statement@100 it &lt; iter → lambda@127（定义体，执行时间取决于调用/调度） → if_statement@146 (deterministic_reduction) | 当前参考未静态绑定；见下方边界说明 |

| L157 | BlasFunction::Saxpy | for_statement@100 it &lt; iter → lambda@127（定义体，执行时间取决于调用/调度） → if_statement@146 (deterministic_reduction) [else 分支] → for_statement@154 j &lt; k → if_statement@155 (local_counts[j] &gt; 0) | 当前参考未静态绑定；见下方边界说明 |

| L160 | local_centroids.data | for_statement@100 it &lt; iter → lambda@127（定义体，执行时间取决于调用/调度） → if_statement@146 (deterministic_reduction) [else 分支] → for_statement@154 j &lt; k → if_statement@155 (local_counts[j] &gt; 0) | 当前参考未静态绑定；见下方边界说明 |

| L162 | new_centroids.data | for_statement@100 it &lt; iter → lambda@127（定义体，执行时间取决于调用/调度） → if_statement@146 (deterministic_reduction) [else 分支] → for_statement@154 j &lt; k → if_statement@155 (local_counts[j] &gt; 0) | 当前参考未静态绑定；见下方边界说明 |

| L169 | futures.emplace_back | for_statement@100 it &lt; iter → for_statement@168 i &lt; count | 当前参考未静态绑定；见下方边界说明 |

| L169 | thread_pool_-&gt;GeneralEnqueue | for_statement@100 it &lt; iter → for_statement@168 i &lt; count | 当前参考未静态绑定；见下方边界说明 |

| L170 | std::min | for_statement@100 it &lt; iter → for_statement@168 i &lt; count | 当前参考未静态绑定；见下方边界说明 |

| L173 | future.wait | for_statement@100 it &lt; iter → for_range_loop@172 | 当前参考未静态绑定；见下方边界说明 |

| L175 | futures.clear | for_statement@100 it &lt; iter | 当前参考未静态绑定；见下方边界说明 |

| L182 | BlasFunction::Saxpy | for_statement@100 it &lt; iter → if_statement@176 (deterministic_reduction) → for_statement@177 block_id &lt; block_count → for_statement@178 j &lt; k → if_statement@180 (block_counts[count_offset] &gt; 0) | 当前参考未静态绑定；见下方边界说明 |

| L184 | block_centroids.data | for_statement@100 it &lt; iter → if_statement@176 (deterministic_reduction) → for_statement@177 block_id &lt; block_count → for_statement@178 j &lt; k → if_statement@180 (block_counts[count_offset] &gt; 0) | 当前参考未静态绑定；见下方边界说明 |

| L187 | new_centroids.data | for_statement@100 it &lt; iter → if_statement@176 (deterministic_reduction) → for_statement@177 block_id &lt; block_count → for_statement@178 j &lt; k → if_statement@180 (block_counts[count_offset] &gt; 0) | 当前参考未静态绑定；见下方边界说明 |

| L197 | BlasFunction::Sscal | for_statement@100 it &lt; iter → for_statement@195 j &lt; k → if_statement@196 (counts[j] &gt; 0) | 当前参考未静态绑定；见下方边界说明 |

| L199 | new_centroids.data | for_statement@100 it &lt; iter → for_statement@195 j &lt; k → if_statement@196 (counts[j] &gt; 0) | 当前参考未静态绑定；见下方边界说明 |

| L201 | std::copy | for_statement@100 it &lt; iter → for_statement@195 j &lt; k → if_statement@196 (counts[j] &gt; 0) | 当前参考未静态绑定；见下方边界说明 |

| L201 | new_centroids.data | for_statement@100 it &lt; iter → for_statement@195 j &lt; k → if_statement@196 (counts[j] &gt; 0) | 当前参考未静态绑定；见下方边界说明 |

| L202 | new_centroids.data | for_statement@100 it &lt; iter → for_statement@195 j &lt; k → if_statement@196 (counts[j] &gt; 0) | 当前参考未静态绑定；见下方边界说明 |

| L205 | dis | for_statement@100 it &lt; iter → for_statement@195 j &lt; k → if_statement@196 (counts[j] &gt; 0) [else 分支] | 当前参考未静态绑定；见下方边界说明 |

| L212 | logger::trace | for_statement@100 it &lt; iter | 当前参考未静态绑定；见下方边界说明 |

| L213 | get_current_time | for_statement@100 it &lt; iter | 当前参考未静态绑定；见下方边界说明 |

| L218 | std::fabs | for_statement@100 it &lt; iter → if_statement@217 (it &gt; 0 && use_mse_for_convergence && std::fabs(last_err - total_err) / static_cast&lt;double&gt;(count) &lt; threshold) | 当前参考未静态绑定；见下方边界说明 |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L230"></a>

## `KMeansCluster::find_nearest_one_with_hgraph`

源码位置：`src/impl/cluster/kmeans_cluster.cpp:230–288`。

先从签名确认输入、返回值和 const/override，再按完整函数体的条件阅读调用点。下表保留了本函数的显式调用以及 lambda 中的调用；进入下层时用“候选实现”定位，未解析的对象由源码静态类型/运行时类型确认。

### 完整函数

```cpp
double
KMeansCluster::find_nearest_one_with_hgraph(const float* query,
                                            const uint64_t query_count,
                                            const uint64_t k,
                                            Vector<int32_t>& labels) {
    if (k_centroids_ == nullptr) {
        throw VsagException(ErrorType::INTERNAL_ERROR, "k_centroids_ is nullptr");
    }
    double error = 0.0;
    std::mutex error_mutex;

    IndexCommonParam param;
    param.dim_ = dim_;
    param.allocator_ = std::make_shared<SafeAllocator>(this->allocator_);
    param.thread_pool_ = this->thread_pool_;
    param.metric_ = MetricType::METRIC_TYPE_L2SQR;
    auto max_degree = std::max(32, dim_ / 8);

    auto hgraph =
        InnerIndexInterface::FastCreateIndex(fmt::format("hgraph|{}|fp32", max_degree), param);
    auto base = Dataset::Make();
    Vector<int64_t> ids(k, allocator_);
    std::iota(ids.begin(), ids.end(), 0);
    base->Dim(dim_)
        ->NumElements(static_cast<int64_t>(k))
        ->Float32Vectors(this->k_centroids_)
        ->Ids(ids.data())
        ->Owner(false);
    hgraph->Build(base);
    hgraph->SetImmutable();
    FilterPtr filter = nullptr;
    constexpr const char* search_param = R"({"hgraph":{"ef_search":10}})";
    auto func = [&](const uint64_t begin, const uint64_t end) -> void {
        double thread_local_error = 0.0;
        for (uint64_t j = begin; j < end; ++j) {
            auto q = Dataset::Make();
            q->Owner(false)
                ->Float32Vectors(query + j * this->dim_)
                ->NumElements(1)
                ->Dim(this->dim_);
            auto ret = hgraph->KnnSearch(q, 1, search_param, filter);
            labels[j] = static_cast<int32_t>(ret->GetIds()[0]);
            thread_local_error += static_cast<double>(ret->GetDistances()[0]);
        }
        {
            std::lock_guard<std::mutex> lock(error_mutex);
            error += thread_local_error;
        }
    };
    std::vector<std::future<void>> futures;
    for (uint64_t i = 0; i < query_count; i += QUERY_BS) {
        futures.emplace_back(
            thread_pool_->GeneralEnqueue(func, i, std::min(i + QUERY_BS, query_count)));
    }
    for (auto& future : futures) {
        future.wait();
    }
    return error / static_cast<float>(query_count);
}
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L236 | VsagException | if_statement@235 (k_centroids_ == nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L243 | std::make_shared&lt;SafeAllocator&gt; | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L246 | std::max | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L249 | InnerIndexInterface::FastCreateIndex | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L249 | fmt::format | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L250 | Dataset::Make | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L252 | std::iota | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L252 | ids.begin | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L252 | ids.end | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L253 | base-&gt;Dim(dim_) -&gt;NumElements(static_cast&lt;int64_t&gt;(k)) -&gt;Float32Vectors(this-&gt;k_centroids_) -&gt;Ids(ids.data()) -&gt;Owner | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L253 | base-&gt;Dim(dim_) -&gt;NumElements(static_cast&lt;int64_t&gt;(k)) -&gt;Float32Vectors(this-&gt;k_centroids_) -&gt;Ids | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L253 | base-&gt;Dim(dim_) -&gt;NumElements(static_cast&lt;int64_t&gt;(k)) -&gt;Float32Vectors | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L253 | base-&gt;Dim(dim_) -&gt;NumElements | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L253 | base-&gt;Dim | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L256 | ids.data | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L258 | hgraph-&gt;Build | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L259 | hgraph-&gt;SetImmutable | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L265 | Dataset::Make | lambda@262（定义体，执行时间取决于调用/调度） → for_statement@264 j &lt; end | 当前参考未静态绑定；见下方边界说明 |

| L266 | q-&gt;Owner(false) -&gt;Float32Vectors(query + j * this-&gt;dim_) -&gt;NumElements(1) -&gt;Dim | lambda@262（定义体，执行时间取决于调用/调度） → for_statement@264 j &lt; end | 当前参考未静态绑定；见下方边界说明 |

| L266 | q-&gt;Owner(false) -&gt;Float32Vectors(query + j * this-&gt;dim_) -&gt;NumElements | lambda@262（定义体，执行时间取决于调用/调度） → for_statement@264 j &lt; end | 当前参考未静态绑定；见下方边界说明 |

| L266 | q-&gt;Owner(false) -&gt;Float32Vectors | lambda@262（定义体，执行时间取决于调用/调度） → for_statement@264 j &lt; end | 当前参考未静态绑定；见下方边界说明 |

| L266 | q-&gt;Owner | lambda@262（定义体，执行时间取决于调用/调度） → for_statement@264 j &lt; end | 当前参考未静态绑定；见下方边界说明 |

| L270 | hgraph-&gt;KnnSearch | lambda@262（定义体，执行时间取决于调用/调度） → for_statement@264 j &lt; end | 当前参考未静态绑定；见下方边界说明 |

| L271 | ret-&gt;GetIds | lambda@262（定义体，执行时间取决于调用/调度） → for_statement@264 j &lt; end | 当前参考未静态绑定；见下方边界说明 |

| L272 | ret-&gt;GetDistances | lambda@262（定义体，执行时间取决于调用/调度） → for_statement@264 j &lt; end | 当前参考未静态绑定；见下方边界说明 |

| L281 | futures.emplace_back | for_statement@280 i &lt; query_count | 当前参考未静态绑定；见下方边界说明 |

| L282 | thread_pool_-&gt;GeneralEnqueue | for_statement@280 i &lt; query_count | 当前参考未静态绑定；见下方边界说明 |

| L282 | std::min | for_statement@280 i &lt; query_count | 当前参考未静态绑定；见下方边界说明 |

| L285 | future.wait | for_range_loop@284 | 当前参考未静态绑定；见下方边界说明 |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L290"></a>

## `KMeansCluster::select_initial_centroids_random`

源码位置：`src/impl/cluster/kmeans_cluster.cpp:290–303`。

先从签名确认输入、返回值和 const/override，再按完整函数体的条件阅读调用点。下表保留了本函数的显式调用以及 lambda 中的调用；进入下层时用“候选实现”定位，未解析的对象由源码静态类型/运行时类型确认。

### 完整函数

```cpp
void
// NOLINTNEXTLINE(readability-make-member-function-const)
KMeansCluster::select_initial_centroids_random(const float* datas,
                                               uint64_t count,
                                               uint32_t k,
                                               std::mt19937& gen) {
    std::uniform_int_distribution<uint64_t> dis(0, count - 1);
    for (uint32_t i = 0; i < k; ++i) {
        auto index = dis(gen);
        for (int32_t j = 0; j < dim_; ++j) {
            k_centroids_[i * dim_ + j] = datas[index * dim_ + j];
        }
    }
}
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L298 | dis | for_statement@297 i &lt; k | 当前参考未静态绑定；见下方边界说明 |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L305"></a>

## `KMeansCluster::select_initial_centroids_kmeans_plus_plus`

源码位置：`src/impl/cluster/kmeans_cluster.cpp:305–358`。

先从签名确认输入、返回值和 const/override，再按完整函数体的条件阅读调用点。下表保留了本函数的显式调用以及 lambda 中的调用；进入下层时用“候选实现”定位，未解析的对象由源码静态类型/运行时类型确认。

### 完整函数

```cpp
void
KMeansCluster::select_initial_centroids_kmeans_plus_plus(const float* datas,
                                                         uint64_t count,
                                                         uint32_t k,
                                                         std::mt19937& gen) {
    std::uniform_int_distribution<uint64_t> first_dis(0, count - 1);
    uint64_t first_idx = first_dis(gen);
    for (int32_t j = 0; j < dim_; ++j) {
        k_centroids_[j] = datas[first_idx * dim_ + j];
    }

    Vector<float> min_distances(count, std::numeric_limits<float>::max(), allocator_);

    for (uint32_t c = 1; c < k; ++c) {
        const float* centroid =
            k_centroids_ + static_cast<uint64_t>(c - 1) * static_cast<uint64_t>(dim_);

        for (uint64_t i = 0; i < count; ++i) {
            float dist = FP32ComputeL2Sqr(datas + i * dim_, centroid, dim_);
            min_distances[i] = std::min(min_distances[i], dist);
        }

        double total_weight = 0.0;
        for (uint64_t i = 0; i < count; ++i) {
            total_weight += min_distances[i];
        }

        if (total_weight <= 0.0) {
            std::uniform_int_distribution<uint64_t> dis(0, count - 1);
            uint64_t idx = dis(gen);
            for (int32_t j = 0; j < dim_; ++j) {
                k_centroids_[c * dim_ + j] = datas[idx * dim_ + j];
            }
            continue;
        }

        std::uniform_real_distribution<double> prob_dis(0.0, total_weight);
        double threshold = prob_dis(gen);
        double cumulative = 0.0;
        uint64_t selected_idx = count - 1;

        for (uint64_t i = 0; i < count; ++i) {
            cumulative += min_distances[i];
            if (cumulative >= threshold) {
                selected_idx = i;
                break;
            }
        }

        for (int32_t j = 0; j < dim_; ++j) {
            k_centroids_[c * dim_ + j] = datas[selected_idx * dim_ + j];
        }
    }
}
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L311 | first_dis | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L323 | FP32ComputeL2Sqr | for_statement@318 c &lt; k → for_statement@322 i &lt; count | 当前参考未静态绑定；见下方边界说明 |

| L324 | std::min | for_statement@318 c &lt; k → for_statement@322 i &lt; count | 当前参考未静态绑定；见下方边界说明 |

| L334 | dis | for_statement@318 c &lt; k → if_statement@332 (total_weight &lt;= 0.0) | 当前参考未静态绑定；见下方边界说明 |

| L342 | prob_dis | for_statement@318 c &lt; k | 当前参考未静态绑定；见下方边界说明 |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。
