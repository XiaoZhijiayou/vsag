# ivf_nearest_partition.cpp：逐函数完整源码与调用点

[主讲解](../code_walkthrough.md) · [函数总目录](README.md)

源码：[ src/algorithm/ivf/ivf_nearest_partition.cpp ](../../../../src/algorithm/ivf/ivf_nearest_partition.cpp)。基线 `fd363937`。以下源码函数体完整保留；调用点表是语法树中的显式调用表达式，按源码位置排列，不代表 C++ 参数求值顺序。表中“候选实现”需结合类型和参数选分支，不能将同名函数全部视为必经路径。

- [compute_centroid_dots · L51](ivf_nearest_partition.md#L51)

- [IVFNearestPartition::IVFNearestPartition · L79](ivf_nearest_partition.md#L79)

- [IVFNearestPartition::Train · L91](ivf_nearest_partition.md#L91)

- [IVFNearestPartition::ClassifyDatas · L157](ivf_nearest_partition.md#L157)

- [IVFNearestPartition::Serialize · L227](ivf_nearest_partition.md#L227)

- [IVFNearestPartition::Deserialize · L239](ivf_nearest_partition.md#L239)

- [IVFNearestPartition::factory_router_index · L275](ivf_nearest_partition.md#L275)

- [IVFNearestPartition::GetCentroid · L286](ivf_nearest_partition.md#L286)

- [IVFNearestPartition::GetMemoryUsage · L303](ivf_nearest_partition.md#L303)

- [IVFNearestPartition::classify_datas_by_scan · L313](ivf_nearest_partition.md#L313)


<a id="L51"></a>

## `compute_centroid_dots`

源码位置：`src/algorithm/ivf/ivf_nearest_partition.cpp:51–67`。

先从签名确认输入、返回值和 const/override，再按完整函数体的条件阅读调用点。下表保留了本函数的显式调用以及 lambda 中的调用；进入下层时用“候选实现”定位，未解析的对象由源码静态类型/运行时类型确认。

### 完整函数

```cpp
void
compute_centroid_dots(const float* A, const float* B, float* C, int64_t M, int64_t N, int64_t K) {
    BlasFunction::Sgemm(BlasFunction::ColMajor,
                        BlasFunction::Trans,
                        BlasFunction::NoTrans,
                        static_cast<int32_t>(N),
                        static_cast<int32_t>(M),
                        static_cast<int32_t>(K),
                        1.0F,
                        B,
                        static_cast<int32_t>(K),
                        A,
                        static_cast<int32_t>(K),
                        0.0F,
                        C,
                        static_cast<int32_t>(N));
}
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L53 | BlasFunction::Sgemm | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L79"></a>

## `IVFNearestPartition::IVFNearestPartition`

源码位置：`src/algorithm/ivf/ivf_nearest_partition.cpp:79–89`。

先从签名确认输入、返回值和 const/override，再按完整函数体的条件阅读调用点。下表保留了本函数的显式调用以及 lambda 中的调用；进入下层时用“候选实现”定位，未解析的对象由源码静态类型/运行时类型确认。

### 完整函数

```cpp
IVFNearestPartition::IVFNearestPartition(BucketIdType bucket_count,
                                         const IndexCommonParam& common_param,
                                         IVFPartitionStrategyParametersPtr param)
    : IVFPartitionStrategy(common_param, bucket_count),
      ivf_partition_strategy_param_(std::move(param)),
      use_route_graph_(this->ivf_partition_strategy_param_->use_route_graph),
      common_param_(common_param) {
    if (this->use_route_graph_) {
        this->factory_router_index(common_param);
    }
}
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L87 | this-&gt;factory_router_index | if_statement@86 (this-&gt;use_route_graph_) | [IVFNearestPartition::factory_router_index · L275](ivf_nearest_partition.md#L275) |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L91"></a>

## `IVFNearestPartition::Train`

源码位置：`src/algorithm/ivf/ivf_nearest_partition.cpp:91–155`。

这是状态改变函数。先看重复训练的提前返回，再看训练数据是否采样/归一化/变成残差，最后确认状态位在何处设置。分区 Train 与量化器 Train 不是同一个模型。

### 完整函数

```cpp
void
IVFNearestPartition::Train(const DatasetPtr dataset) {
    auto dim = this->dim_;
    auto centroids = Dataset::Make();
    Vector<float> data(bucket_count_ * dim, allocator_);
    Vector<LabelType> ids(this->bucket_count_, allocator_);
    std::iota(ids.begin(), ids.end(), 0);
    centroids->Ids(ids.data())
        ->Dim(dim)
        ->Float32Vectors(data.data())
        ->NumElements(this->bucket_count_)
        ->Owner(false);

    if (ivf_partition_strategy_param_->partition_train_type ==
        IVFNearestPartitionTrainerType::KMeansTrainer) {
        constexpr int32_t kmeans_iter_count = 25;
        KMeansCluster cls(static_cast<int32_t>(dim), this->allocator_, this->thread_pool_);
        cls.Run(this->bucket_count_,
                dataset->GetFloat32Vectors(),
                dataset->GetNumElements(),
                kmeans_iter_count);
        memcpy(data.data(), cls.k_centroids_, dim * this->bucket_count_ * sizeof(float));
    } else if (ivf_partition_strategy_param_->partition_train_type ==
               IVFNearestPartitionTrainerType::RandomTrainer) {
        auto selected = select_k_numbers(dataset->GetNumElements(), this->bucket_count_);
        for (int i = 0; i < bucket_count_; ++i) {
            memcpy(data.data() + i * dim,
                   dataset->GetFloat32Vectors() + selected[i] * dim,
                   dim * sizeof(float));
        }
    }
    if (metric_type_ == MetricType::METRIC_TYPE_COSINE) {
        for (int i = 0; i < bucket_count_; ++i) {
            Normalize(data.data() + i * dim_, data.data() + i * dim_, dim_);
        }
    }

    if (this->use_route_graph_) {
        const auto failed_ids = this->route_index_ptr_->Build(centroids);
        if (not failed_ids.empty()) {
            throw VsagException(ErrorType::INTERNAL_ERROR,
                                "failed to build all IVF routing centroids");
        }
    } else {
        // Persist the trained centroids (normalized for cosine) so the scan routing path can
        // assign buckets without creating a routing HGraph.
        this->centroids_.resize(this->bucket_count_ * this->dim_);
        memcpy(
            this->centroids_.data(), data.data(), this->bucket_count_ * this->dim_ * sizeof(float));
        this->norms_.resize(this->bucket_count_);
        if (metric_type_ == MetricType::METRIC_TYPE_L2SQR) {
            for (int i = 0; i < bucket_count_; ++i) {
                this->norms_[i] = FP32ComputeIP(this->centroids_.data() + i * dim_,
                                                this->centroids_.data() + i * dim_,
                                                dim_) /
                                  2.0F;
            }
        } else {
            // IP/COSINE distances are defined as `1 - dot`; with normalized cosine centroids
            // the constant term is 1.0 for every centroid.
            std::fill(this->norms_.begin(), this->norms_.end(), 1.0F);
        }
    }
    this->is_trained_ = true;
}
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L94 | Dataset::Make | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L97 | std::iota | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L97 | ids.begin | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L97 | ids.end | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L98 | centroids-&gt;Ids(ids.data()) -&gt;Dim(dim) -&gt;Float32Vectors(data.data()) -&gt;NumElements(this-&gt;bucket_count_) -&gt;Owner | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L98 | centroids-&gt;Ids(ids.data()) -&gt;Dim(dim) -&gt;Float32Vectors(data.data()) -&gt;NumElements | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L98 | centroids-&gt;Ids(ids.data()) -&gt;Dim(dim) -&gt;Float32Vectors | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L98 | centroids-&gt;Ids(ids.data()) -&gt;Dim | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L98 | centroids-&gt;Ids | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L98 | ids.data | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L100 | data.data | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L108 | cls.Run | if_statement@104 (ivf_partition_strategy_param_-&gt;partition_train_type == IVFNearestPartitionTrainerType::KMeansTrainer) | [KMeansCluster::Run · L48](kmeans_cluster.md#L48) |

| L109 | dataset-&gt;GetFloat32Vectors | if_statement@104 (ivf_partition_strategy_param_-&gt;partition_train_type == IVFNearestPartitionTrainerType::KMeansTrainer) | 当前参考未静态绑定；见下方边界说明 |

| L110 | dataset-&gt;GetNumElements | if_statement@104 (ivf_partition_strategy_param_-&gt;partition_train_type == IVFNearestPartitionTrainerType::KMeansTrainer) | 当前参考未静态绑定；见下方边界说明 |

| L112 | memcpy | if_statement@104 (ivf_partition_strategy_param_-&gt;partition_train_type == IVFNearestPartitionTrainerType::KMeansTrainer) | 当前参考未静态绑定；见下方边界说明 |

| L112 | data.data | if_statement@104 (ivf_partition_strategy_param_-&gt;partition_train_type == IVFNearestPartitionTrainerType::KMeansTrainer) | 当前参考未静态绑定；见下方边界说明 |

| L115 | select_k_numbers | if_statement@104 (ivf_partition_strategy_param_-&gt;partition_train_type == IVFNearestPartitionTrainerType::KMeansTrainer) [else 分支] → if_statement@113 (ivf_partition_strategy_param_-&gt;partition_train_type == IVFNearestPartitionTrainerType::RandomTrainer) | [select_k_numbers · L43](util_functions.md#L43) |

| L115 | dataset-&gt;GetNumElements | if_statement@104 (ivf_partition_strategy_param_-&gt;partition_train_type == IVFNearestPartitionTrainerType::KMeansTrainer) [else 分支] → if_statement@113 (ivf_partition_strategy_param_-&gt;partition_train_type == IVFNearestPartitionTrainerType::RandomTrainer) | 当前参考未静态绑定；见下方边界说明 |

| L117 | memcpy | if_statement@104 (ivf_partition_strategy_param_-&gt;partition_train_type == IVFNearestPartitionTrainerType::KMeansTrainer) [else 分支] → if_statement@113 (ivf_partition_strategy_param_-&gt;partition_train_type == IVFNearestPartitionTrainerType::RandomTrainer) → for_statement@116 i &lt; bucket_count_ | 当前参考未静态绑定；见下方边界说明 |

| L117 | data.data | if_statement@104 (ivf_partition_strategy_param_-&gt;partition_train_type == IVFNearestPartitionTrainerType::KMeansTrainer) [else 分支] → if_statement@113 (ivf_partition_strategy_param_-&gt;partition_train_type == IVFNearestPartitionTrainerType::RandomTrainer) → for_statement@116 i &lt; bucket_count_ | 当前参考未静态绑定；见下方边界说明 |

| L118 | dataset-&gt;GetFloat32Vectors | if_statement@104 (ivf_partition_strategy_param_-&gt;partition_train_type == IVFNearestPartitionTrainerType::KMeansTrainer) [else 分支] → if_statement@113 (ivf_partition_strategy_param_-&gt;partition_train_type == IVFNearestPartitionTrainerType::RandomTrainer) → for_statement@116 i &lt; bucket_count_ | 当前参考未静态绑定；见下方边界说明 |

| L124 | Normalize | if_statement@122 (metric_type_ == MetricType::METRIC_TYPE_COSINE) → for_statement@123 i &lt; bucket_count_ | 当前参考未静态绑定；见下方边界说明 |

| L124 | data.data | if_statement@122 (metric_type_ == MetricType::METRIC_TYPE_COSINE) → for_statement@123 i &lt; bucket_count_ | 当前参考未静态绑定；见下方边界说明 |

| L124 | data.data | if_statement@122 (metric_type_ == MetricType::METRIC_TYPE_COSINE) → for_statement@123 i &lt; bucket_count_ | 当前参考未静态绑定；见下方边界说明 |

| L129 | this-&gt;route_index_ptr_-&gt;Build | if_statement@128 (this-&gt;use_route_graph_) | 当前参考未静态绑定；见下方边界说明 |

| L130 | failed_ids.empty | if_statement@128 (this-&gt;use_route_graph_) → if_statement@130 (not failed_ids.empty()) | 当前参考未静态绑定；见下方边界说明 |

| L131 | VsagException | if_statement@128 (this-&gt;use_route_graph_) → if_statement@130 (not failed_ids.empty()) | 当前参考未静态绑定；见下方边界说明 |

| L137 | this-&gt;centroids_.resize | if_statement@128 (this-&gt;use_route_graph_) [else 分支] | 当前参考未静态绑定；见下方边界说明 |

| L138 | memcpy | if_statement@128 (this-&gt;use_route_graph_) [else 分支] | 当前参考未静态绑定；见下方边界说明 |

| L139 | this-&gt;centroids_.data | if_statement@128 (this-&gt;use_route_graph_) [else 分支] | 当前参考未静态绑定；见下方边界说明 |

| L139 | data.data | if_statement@128 (this-&gt;use_route_graph_) [else 分支] | 当前参考未静态绑定；见下方边界说明 |

| L140 | this-&gt;norms_.resize | if_statement@128 (this-&gt;use_route_graph_) [else 分支] | 当前参考未静态绑定；见下方边界说明 |

| L143 | FP32ComputeIP | if_statement@128 (this-&gt;use_route_graph_) [else 分支] → if_statement@141 (metric_type_ == MetricType::METRIC_TYPE_L2SQR) → for_statement@142 i &lt; bucket_count_ | 当前参考未静态绑定；见下方边界说明 |

| L143 | this-&gt;centroids_.data | if_statement@128 (this-&gt;use_route_graph_) [else 分支] → if_statement@141 (metric_type_ == MetricType::METRIC_TYPE_L2SQR) → for_statement@142 i &lt; bucket_count_ | 当前参考未静态绑定；见下方边界说明 |

| L144 | this-&gt;centroids_.data | if_statement@128 (this-&gt;use_route_graph_) [else 分支] → if_statement@141 (metric_type_ == MetricType::METRIC_TYPE_L2SQR) → for_statement@142 i &lt; bucket_count_ | 当前参考未静态绑定；见下方边界说明 |

| L151 | std::fill | if_statement@128 (this-&gt;use_route_graph_) [else 分支] → if_statement@141 (metric_type_ == MetricType::METRIC_TYPE_L2SQR) [else 分支] | 当前参考未静态绑定；见下方边界说明 |

| L151 | this-&gt;norms_.begin | if_statement@128 (this-&gt;use_route_graph_) [else 分支] → if_statement@141 (metric_type_ == MetricType::METRIC_TYPE_L2SQR) [else 分支] | 当前参考未静态绑定；见下方边界说明 |

| L151 | this-&gt;norms_.end | if_statement@128 (this-&gt;use_route_graph_) [else 分支] → if_statement@141 (metric_type_ == MetricType::METRIC_TYPE_L2SQR) [else 分支] | 当前参考未静态绑定；见下方边界说明 |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L157"></a>

## `IVFNearestPartition::ClassifyDatas`

源码位置：`src/algorithm/ivf/ivf_nearest_partition.cpp:157–225`。

输入 count 条向量，返回 count×buckets_per_data 个 bucket ID。普通 IVF 由 use_route_graph 决定中心图或中心扫描。调用中返回的 IDs 是中心/桶 ID，不是业务数据 ID。

### 完整函数

```cpp
Vector<BucketIdType>
IVFNearestPartition::ClassifyDatas(const void* datas,
                                   int64_t count,
                                   BucketIdType buckets_per_data,
                                   QueryContext* ctx) const {
    if (not this->use_route_graph_) {
        return this->classify_datas_by_scan(datas, count, buckets_per_data, ctx);
    }
    std::mutex dist_cmp_reduce_mutex;
    uint32_t dist_cmp = 0;
    Vector<BucketIdType> result(buckets_per_data * count, INVALID_BUCKET_ID, this->allocator_);
    auto task = [&](int64_t i) {
        auto query = Dataset::Make();
        query->Dim(this->dim_)
            ->Float32Vectors(reinterpret_cast<const float*>(datas) + i * this->dim_)
            ->NumElements(1)
            ->Owner(false);
        auto search_param =
            fmt::format(SEARCH_PARAM_TEMPLATE_STR,
                        std::max<int64_t>(10, static_cast<int64_t>(buckets_per_data * 1.2)));
        FilterPtr filter = nullptr;
        auto search_result =
            this->route_index_ptr_->KnnSearch(query, buckets_per_data, search_param, filter);
        const auto* result_ids = search_result->GetIds();

        for (int64_t j = 0; j < search_result->GetDim(); ++j) {
            result[i * buckets_per_data + j] = static_cast<BucketIdType>(result_ids[j]);
        }

        if (ctx != nullptr and ctx->stats != nullptr) {
            // GetStatistics re-parses the routing statistics JSON and re-dumps it to strings,
            // which is allocation-heavy; it must not run inside the reduce lock. Only the two
            // integer accumulations below are serialized. The return value always has the same
            // length as the input keys, and atoi("") returns a `0`.
            auto route_stats = search_result->GetStatistics({"dist_cmp", "distance_evaluations"});
            const uint32_t local_dist_cmp = std::atoi(route_stats[0].c_str());
            uint64_t eval_count = 0;
            if (route_stats.size() > 1) {
                eval_count = std::strtoull(route_stats[1].c_str(), nullptr, 10);
            }
            {
                std::scoped_lock lock(dist_cmp_reduce_mutex);
                dist_cmp += local_dist_cmp;
            }
            ctx->stats->AddDistance(SearchStatistics::DistancePhase::ROUTING,
                                    DistanceEvaluationBackend::FP32,
                                    eval_count);
        }
    };
    if (thread_pool_ == nullptr or count == 1) {
        for (int64_t i = 0; i < count; ++i) {
            task(i);
        }
    } else {
        Vector<std::future<void>> futures(allocator_);
        for (int64_t i = 0; i < count; ++i) {
            futures.push_back(thread_pool_->GeneralEnqueue(task, i));
        }
        for (auto& item : futures) {
            item.get();
        }
    }

    if (ctx != nullptr and ctx->stats != nullptr) {
        ctx->stats->dist_cmp.fetch_add(dist_cmp, std::memory_order_relaxed);
    }

    return std::move(result);
}
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L163 | this-&gt;classify_datas_by_scan | if_statement@162 (not this-&gt;use_route_graph_) | [IVFNearestPartition::classify_datas_by_scan · L313](ivf_nearest_partition.md#L313) |

| L169 | Dataset::Make | lambda@168（定义体，执行时间取决于调用/调度） | 当前参考未静态绑定；见下方边界说明 |

| L170 | query-&gt;Dim(this-&gt;dim_) -&gt;Float32Vectors(reinterpret_cast&lt;const float*&gt;(datas) + i * this-&gt;dim_) -&gt;NumElements(1) -&gt;Owner | lambda@168（定义体，执行时间取决于调用/调度） | 当前参考未静态绑定；见下方边界说明 |

| L170 | query-&gt;Dim(this-&gt;dim_) -&gt;Float32Vectors(reinterpret_cast&lt;const float*&gt;(datas) + i * this-&gt;dim_) -&gt;NumElements | lambda@168（定义体，执行时间取决于调用/调度） | 当前参考未静态绑定；见下方边界说明 |

| L170 | query-&gt;Dim(this-&gt;dim_) -&gt;Float32Vectors | lambda@168（定义体，执行时间取决于调用/调度） | 当前参考未静态绑定；见下方边界说明 |

| L170 | query-&gt;Dim | lambda@168（定义体，执行时间取决于调用/调度） | 当前参考未静态绑定；见下方边界说明 |

| L175 | fmt::format | lambda@168（定义体，执行时间取决于调用/调度） | 当前参考未静态绑定；见下方边界说明 |

| L176 | std::max&lt;int64_t&gt; | lambda@168（定义体，执行时间取决于调用/调度） | 当前参考未静态绑定；见下方边界说明 |

| L179 | this-&gt;route_index_ptr_-&gt;KnnSearch | lambda@168（定义体，执行时间取决于调用/调度） | 当前参考未静态绑定；见下方边界说明 |

| L180 | search_result-&gt;GetIds | lambda@168（定义体，执行时间取决于调用/调度） | 当前参考未静态绑定；见下方边界说明 |

| L182 | search_result-&gt;GetDim | lambda@168（定义体，执行时间取决于调用/调度） → for_statement@182 j &lt; search_result-&gt;GetDim() | 当前参考未静态绑定；见下方边界说明 |

| L191 | search_result-&gt;GetStatistics | lambda@168（定义体，执行时间取决于调用/调度） → if_statement@186 (ctx != nullptr and ctx-&gt;stats != nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L192 | std::atoi | lambda@168（定义体，执行时间取决于调用/调度） → if_statement@186 (ctx != nullptr and ctx-&gt;stats != nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L192 | route_stats[0].c_str | lambda@168（定义体，执行时间取决于调用/调度） → if_statement@186 (ctx != nullptr and ctx-&gt;stats != nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L194 | route_stats.size | lambda@168（定义体，执行时间取决于调用/调度） → if_statement@186 (ctx != nullptr and ctx-&gt;stats != nullptr) → if_statement@194 (route_stats.size() &gt; 1) | 当前参考未静态绑定；见下方边界说明 |

| L195 | std::strtoull | lambda@168（定义体，执行时间取决于调用/调度） → if_statement@186 (ctx != nullptr and ctx-&gt;stats != nullptr) → if_statement@194 (route_stats.size() &gt; 1) | 当前参考未静态绑定；见下方边界说明 |

| L195 | route_stats[1].c_str | lambda@168（定义体，执行时间取决于调用/调度） → if_statement@186 (ctx != nullptr and ctx-&gt;stats != nullptr) → if_statement@194 (route_stats.size() &gt; 1) | 当前参考未静态绑定；见下方边界说明 |

| L201 | ctx-&gt;stats-&gt;AddDistance | lambda@168（定义体，执行时间取决于调用/调度） → if_statement@186 (ctx != nullptr and ctx-&gt;stats != nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L208 | task | if_statement@206 (thread_pool_ == nullptr or count == 1) → for_statement@207 i &lt; count | 当前参考未静态绑定；见下方边界说明 |

| L213 | futures.push_back | if_statement@206 (thread_pool_ == nullptr or count == 1) [else 分支] → for_statement@212 i &lt; count | 当前参考未静态绑定；见下方边界说明 |

| L213 | thread_pool_-&gt;GeneralEnqueue | if_statement@206 (thread_pool_ == nullptr or count == 1) [else 分支] → for_statement@212 i &lt; count | 当前参考未静态绑定；见下方边界说明 |

| L216 | item.get | if_statement@206 (thread_pool_ == nullptr or count == 1) [else 分支] → for_range_loop@215 | 当前参考未静态绑定；见下方边界说明 |

| L221 | ctx-&gt;stats-&gt;dist_cmp.fetch_add | if_statement@220 (ctx != nullptr and ctx-&gt;stats != nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L224 | std::move | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L227"></a>

## `IVFNearestPartition::Serialize`

源码位置：`src/algorithm/ivf/ivf_nearest_partition.cpp:227–238`。

先从签名确认输入、返回值和 const/override，再按完整函数体的条件阅读调用点。下表保留了本函数的显式调用以及 lambda 中的调用；进入下层时用“候选实现”定位，未解析的对象由源码静态类型/运行时类型确认。

### 完整函数

```cpp
void
IVFNearestPartition::Serialize(StreamWriter& writer) {
    IVFPartitionStrategy::Serialize(writer);
    if (this->use_route_graph_) {
        // Keep the route-graph layout byte-for-byte compatible with the legacy format.
        this->route_index_ptr_->Serialize(writer);
    } else {
        StreamWriter::WriteObj(writer, K_CENTROID_SCAN_LAYOUT_MARKER);
        StreamWriter::WriteVector(writer, this->centroids_);
        StreamWriter::WriteVector(writer, this->norms_);
    }
}
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L229 | IVFPartitionStrategy::Serialize | 函数本体；短路求值/提前返回见源码 | [IVFPartitionStrategy::Serialize · L75](ivf_partition_strategy_h.md#L75) |

| L232 | this-&gt;route_index_ptr_-&gt;Serialize | if_statement@230 (this-&gt;use_route_graph_) | 当前参考未静态绑定；见下方边界说明 |

| L234 | StreamWriter::WriteObj | if_statement@230 (this-&gt;use_route_graph_) [else 分支] | 当前参考未静态绑定；见下方边界说明 |

| L235 | StreamWriter::WriteVector | if_statement@230 (this-&gt;use_route_graph_) [else 分支] | 当前参考未静态绑定；见下方边界说明 |

| L236 | StreamWriter::WriteVector | if_statement@230 (this-&gt;use_route_graph_) [else 分支] | 当前参考未静态绑定；见下方边界说明 |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L239"></a>

## `IVFNearestPartition::Deserialize`

源码位置：`src/algorithm/ivf/ivf_nearest_partition.cpp:239–274`。

先从签名确认输入、返回值和 const/override，再按完整函数体的条件阅读调用点。下表保留了本函数的显式调用以及 lambda 中的调用；进入下层时用“候选实现”定位，未解析的对象由源码静态类型/运行时类型确认。

### 完整函数

```cpp
void
IVFNearestPartition::Deserialize(LvalueOrRvalue<StreamReader> reader) {
    IVFPartitionStrategy::Deserialize(reader);
    // Peek the layout marker without consuming bytes so legacy (marker-less) route-graph
    // indices remain loadable with any reader configuration.
    const auto cursor = reader->GetCursor();
    uint64_t layout = 0;
    StreamReader::ReadObj(reader, layout);
    reader->Seek(cursor);
    if (layout == K_CENTROID_SCAN_LAYOUT_MARKER) {
        StreamReader::ReadObj(reader, layout);
        StreamReader::ReadVector(reader, this->centroids_);
        StreamReader::ReadVector(reader, this->norms_);
        const bool invalid_trained_layout =
            this->is_trained_ and (this->centroids_.size() != this->bucket_count_ * this->dim_ or
                                   this->norms_.size() != this->bucket_count_);
        const bool invalid_untrained_layout =
            not this->is_trained_ and (not this->centroids_.empty() or not this->norms_.empty());
        if (invalid_trained_layout or invalid_untrained_layout) {
            throw VsagException(ErrorType::INVALID_BINARY,
                                "invalid IVF centroid scan routing layout");
        }
        this->route_index_ptr_.reset();
        this->use_route_graph_ = false;
    } else {
        // Route-graph layout (the legacy marker-less format). Lazily create the routing HGraph
        // when the reader was configured with use_route_graph=false.
        if (this->route_index_ptr_ == nullptr) {
            this->factory_router_index(this->common_param_);
        }
        this->route_index_ptr_->Deserialize(reader);
        this->centroids_.clear();
        this->norms_.clear();
        this->use_route_graph_ = true;
    }
}
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L241 | IVFPartitionStrategy::Deserialize | 函数本体；短路求值/提前返回见源码 | [IVFPartitionStrategy::Deserialize · L82](ivf_partition_strategy_h.md#L82) |

| L244 | reader-&gt;GetCursor | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L246 | StreamReader::ReadObj | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L247 | reader-&gt;Seek | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L249 | StreamReader::ReadObj | if_statement@248 (layout == K_CENTROID_SCAN_LAYOUT_MARKER) | 当前参考未静态绑定；见下方边界说明 |

| L250 | StreamReader::ReadVector | if_statement@248 (layout == K_CENTROID_SCAN_LAYOUT_MARKER) | 当前参考未静态绑定；见下方边界说明 |

| L251 | StreamReader::ReadVector | if_statement@248 (layout == K_CENTROID_SCAN_LAYOUT_MARKER) | 当前参考未静态绑定；见下方边界说明 |

| L253 | this-&gt;centroids_.size | if_statement@248 (layout == K_CENTROID_SCAN_LAYOUT_MARKER) | 当前参考未静态绑定；见下方边界说明 |

| L254 | this-&gt;norms_.size | if_statement@248 (layout == K_CENTROID_SCAN_LAYOUT_MARKER) | 当前参考未静态绑定；见下方边界说明 |

| L256 | this-&gt;centroids_.empty | if_statement@248 (layout == K_CENTROID_SCAN_LAYOUT_MARKER) | 当前参考未静态绑定；见下方边界说明 |

| L256 | this-&gt;norms_.empty | if_statement@248 (layout == K_CENTROID_SCAN_LAYOUT_MARKER) | 当前参考未静态绑定；见下方边界说明 |

| L258 | VsagException | if_statement@248 (layout == K_CENTROID_SCAN_LAYOUT_MARKER) → if_statement@257 (invalid_trained_layout or invalid_untrained_layout) | 当前参考未静态绑定；见下方边界说明 |

| L261 | this-&gt;route_index_ptr_.reset | if_statement@248 (layout == K_CENTROID_SCAN_LAYOUT_MARKER) | 当前参考未静态绑定；见下方边界说明 |

| L267 | this-&gt;factory_router_index | if_statement@248 (layout == K_CENTROID_SCAN_LAYOUT_MARKER) [else 分支] → if_statement@266 (this-&gt;route_index_ptr_ == nullptr) | [IVFNearestPartition::factory_router_index · L275](ivf_nearest_partition.md#L275) |

| L269 | this-&gt;route_index_ptr_-&gt;Deserialize | if_statement@248 (layout == K_CENTROID_SCAN_LAYOUT_MARKER) [else 分支] | 当前参考未静态绑定；见下方边界说明 |

| L270 | this-&gt;centroids_.clear | if_statement@248 (layout == K_CENTROID_SCAN_LAYOUT_MARKER) [else 分支] | 当前参考未静态绑定；见下方边界说明 |

| L271 | this-&gt;norms_.clear | if_statement@248 (layout == K_CENTROID_SCAN_LAYOUT_MARKER) [else 分支] | 当前参考未静态绑定；见下方边界说明 |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L275"></a>

## `IVFNearestPartition::factory_router_index`

源码位置：`src/algorithm/ivf/ivf_nearest_partition.cpp:275–285`。

先从签名确认输入、返回值和 const/override，再按完整函数体的条件阅读调用点。下表保留了本函数的显式调用以及 lambda 中的调用；进入下层时用“候选实现”定位，未解析的对象由源码静态类型/运行时类型确认。

### 完整函数

```cpp
void
IVFNearestPartition::factory_router_index(const IndexCommonParam& common_param) {
    ParamPtr param_ptr;
    JsonType hgraph_json;
    hgraph_json["base_quantization_type"].SetString("fp32");
    hgraph_json["max_degree"].SetInt(ivf_partition_strategy_param_->route_max_degree);
    hgraph_json["ef_construction"].SetInt(ivf_partition_strategy_param_->route_ef_construction);

    param_ptr = HGraph::CheckAndMappingExternalParam(hgraph_json, common_param);
    this->route_index_ptr_ = std::make_shared<HGraph>(param_ptr, common_param);
}
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L279 | hgraph_json["base_quantization_type"].SetString | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L280 | hgraph_json["max_degree"].SetInt | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L281 | hgraph_json["ef_construction"].SetInt | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L283 | HGraph::CheckAndMappingExternalParam | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L284 | std::make_shared&lt;HGraph&gt; | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L286"></a>

## `IVFNearestPartition::GetCentroid`

源码位置：`src/algorithm/ivf/ivf_nearest_partition.cpp:286–301`。

先从签名确认输入、返回值和 const/override，再按完整函数体的条件阅读调用点。下表保留了本函数的显式调用以及 lambda 中的调用；进入下层时用“候选实现”定位，未解析的对象由源码静态类型/运行时类型确认。

### 完整函数

```cpp
void
IVFNearestPartition::GetCentroid(BucketIdType bucket_id, Vector<float>& centroid) {
    if (!is_trained_) {
        throw VsagException(ErrorType::WRONG_STATUS, "Partition not trained");
    }
    if (bucket_id >= bucket_count_) {
        throw VsagException(ErrorType::INVALID_ARGUMENT, "Invalid bucket_id");
    }
    if (this->use_route_graph_) {
        this->route_index_ptr_->GetCodeByInnerId(bucket_id, (uint8_t*)centroid.data());
    } else {
        memcpy(centroid.data(),
               this->centroids_.data() + bucket_id * this->dim_,
               this->dim_ * sizeof(float));
    }
}
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L289 | VsagException | if_statement@288 (!is_trained_) | 当前参考未静态绑定；见下方边界说明 |

| L292 | VsagException | if_statement@291 (bucket_id &gt;= bucket_count_) | 当前参考未静态绑定；见下方边界说明 |

| L295 | this-&gt;route_index_ptr_-&gt;GetCodeByInnerId | if_statement@294 (this-&gt;use_route_graph_) | 当前参考未静态绑定；见下方边界说明 |

| L295 | centroid.data | if_statement@294 (this-&gt;use_route_graph_) | 当前参考未静态绑定；见下方边界说明 |

| L297 | memcpy | if_statement@294 (this-&gt;use_route_graph_) [else 分支] | 当前参考未静态绑定；见下方边界说明 |

| L297 | centroid.data | if_statement@294 (this-&gt;use_route_graph_) [else 分支] | 当前参考未静态绑定；见下方边界说明 |

| L298 | this-&gt;centroids_.data | if_statement@294 (this-&gt;use_route_graph_) [else 分支] | 当前参考未静态绑定；见下方边界说明 |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L303"></a>

## `IVFNearestPartition::GetMemoryUsage`

源码位置：`src/algorithm/ivf/ivf_nearest_partition.cpp:303–312`。

先从签名确认输入、返回值和 const/override，再按完整函数体的条件阅读调用点。下表保留了本函数的显式调用以及 lambda 中的调用；进入下层时用“候选实现”定位，未解析的对象由源码静态类型/运行时类型确认。

### 完整函数

```cpp
[[nodiscard]] uint64_t
IVFNearestPartition::GetMemoryUsage() const {
    auto memory = static_cast<uint64_t>(sizeof(IVFNearestPartition));
    if (this->use_route_graph_) {
        memory += this->route_index_ptr_->GetMemoryUsage();
    }
    memory += this->centroids_.size() * sizeof(float);
    memory += this->norms_.size() * sizeof(float);
    return memory;
}
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L307 | this-&gt;route_index_ptr_-&gt;GetMemoryUsage | if_statement@306 (this-&gt;use_route_graph_) | 当前参考未静态绑定；见下方边界说明 |

| L309 | this-&gt;centroids_.size | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L310 | this-&gt;norms_.size | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L313"></a>

## `IVFNearestPartition::classify_datas_by_scan`

源码位置：`src/algorithm/ivf/ivf_nearest_partition.cpp:313–390`。

先计算 query×centroid 点积，再用 norms-dot 作为路由排序键。堆保留最小 k 个键，倒序弹出得到桶顺序。未训练和零输入直接返回填有无效桶号的数组。

### 完整函数

```cpp
Vector<BucketIdType>
IVFNearestPartition::classify_datas_by_scan(const void* datas,
                                            int64_t count,
                                            BucketIdType buckets_per_data,
                                            QueryContext* ctx) const {
    Vector<BucketIdType> result(buckets_per_data * count, INVALID_BUCKET_ID, this->allocator_);
    // Centroids only exist after Train(). An untrained index must not route: leave every slot
    // at INVALID_BUCKET_ID (mirrors the untrained route-graph behavior).
    if (not this->is_trained_ or this->bucket_count_ == 0 or count == 0) {
        return result;
    }

    const auto k = std::min<BucketIdType>(buckets_per_data, bucket_count_);
    if (k == 0) {
        return result;
    }

    Vector<float> norm_vectors(allocator_);
    const auto* query_data = static_cast<const float*>(datas);
    if (metric_type_ == MetricType::METRIC_TYPE_COSINE) {
        norm_vectors.resize(count * dim_);
        for (int64_t i = 0; i < count; ++i) {
            Normalize(query_data + i * dim_, norm_vectors.data() + i * dim_, dim_);
        }
        query_data = norm_vectors.data();
    }

    // Batch dot products query x centroids^T via Sgemm (same shape as GNOIMIPartition).
    Vector<float> dots(count * bucket_count_, allocator_);
    compute_centroid_dots(
        query_data, this->centroids_.data(), dots.data(), count, bucket_count_, dim_);

    auto task = [&](int64_t i) {
        Vector<std::pair<float, InnerIdType>> heap_storage(this->allocator_);
        heap_storage.reserve(k);
        ScanRouteHeap heap(std::less<>{}, std::move(heap_storage));
        const auto* dots_i = dots.data() + i * bucket_count_;
        for (BucketIdType b = 0; b < bucket_count_; ++b) {
            const std::pair<float, InnerIdType> candidate{this->norms_[b] - dots_i[b],
                                                          static_cast<InnerIdType>(b)};
            if (heap.size() < k || candidate < heap.top()) {
                heap.push(candidate);
            }
            if (heap.size() > k) {
                heap.pop();
            }
        }
        for (BucketIdType j = k; j > 0; --j) {
            result[i * buckets_per_data + j - 1] = static_cast<BucketIdType>(heap.top().second);
            heap.pop();
        }
    };
    if (thread_pool_ == nullptr or count == 1) {
        for (int64_t i = 0; i < count; ++i) {
            task(i);
        }
    } else {
        Vector<std::future<void>> futures(allocator_);
        for (int64_t i = 0; i < count; ++i) {
            futures.push_back(thread_pool_->GeneralEnqueue(task, i));
        }
        for (auto& item : futures) {
            item.get();
        }
    }

    if (ctx != nullptr and ctx->stats != nullptr) {
        const auto distance_evaluations =
            static_cast<uint64_t>(count) * static_cast<uint64_t>(bucket_count_);
        const auto dist_cmp_increment = static_cast<uint32_t>(
            std::min<uint64_t>(distance_evaluations, std::numeric_limits<uint32_t>::max()));
        ctx->stats->dist_cmp.fetch_add(dist_cmp_increment, std::memory_order_relaxed);
        ctx->stats->AddDistance(SearchStatistics::DistancePhase::ROUTING,
                                DistanceEvaluationBackend::FP32,
                                distance_evaluations);
    }
    return result;
}
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L325 | std::min&lt;BucketIdType&gt; | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L333 | norm_vectors.resize | if_statement@332 (metric_type_ == MetricType::METRIC_TYPE_COSINE) | 当前参考未静态绑定；见下方边界说明 |

| L335 | Normalize | if_statement@332 (metric_type_ == MetricType::METRIC_TYPE_COSINE) → for_statement@334 i &lt; count | 当前参考未静态绑定；见下方边界说明 |

| L335 | norm_vectors.data | if_statement@332 (metric_type_ == MetricType::METRIC_TYPE_COSINE) → for_statement@334 i &lt; count | 当前参考未静态绑定；见下方边界说明 |

| L337 | norm_vectors.data | if_statement@332 (metric_type_ == MetricType::METRIC_TYPE_COSINE) | 当前参考未静态绑定；见下方边界说明 |

| L342 | compute_centroid_dots | 函数本体；短路求值/提前返回见源码 | [compute_centroid_dots · L51](ivf_nearest_partition.md#L51) |

| L343 | this-&gt;centroids_.data | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L343 | dots.data | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L347 | heap_storage.reserve | lambda@345（定义体，执行时间取决于调用/调度） | 当前参考未静态绑定；见下方边界说明 |

| L348 | std::move | lambda@345（定义体，执行时间取决于调用/调度） | 当前参考未静态绑定；见下方边界说明 |

| L349 | dots.data | lambda@345（定义体，执行时间取决于调用/调度） | 当前参考未静态绑定；见下方边界说明 |

| L353 | heap.size | lambda@345（定义体，执行时间取决于调用/调度） → for_statement@350 b &lt; bucket_count_ → if_statement@353 (heap.size() &lt; k &#124;&#124; candidate &lt; heap.top()) | 当前参考未静态绑定；见下方边界说明 |

| L353 | heap.top | lambda@345（定义体，执行时间取决于调用/调度） → for_statement@350 b &lt; bucket_count_ → if_statement@353 (heap.size() &lt; k &#124;&#124; candidate &lt; heap.top()) | 当前参考未静态绑定；见下方边界说明 |

| L354 | heap.push | lambda@345（定义体，执行时间取决于调用/调度） → for_statement@350 b &lt; bucket_count_ → if_statement@353 (heap.size() &lt; k &#124;&#124; candidate &lt; heap.top()) | 当前参考未静态绑定；见下方边界说明 |

| L356 | heap.size | lambda@345（定义体，执行时间取决于调用/调度） → for_statement@350 b &lt; bucket_count_ → if_statement@356 (heap.size() &gt; k) | 当前参考未静态绑定；见下方边界说明 |

| L357 | heap.pop | lambda@345（定义体，执行时间取决于调用/调度） → for_statement@350 b &lt; bucket_count_ → if_statement@356 (heap.size() &gt; k) | 当前参考未静态绑定；见下方边界说明 |

| L361 | heap.top | lambda@345（定义体，执行时间取决于调用/调度） → for_statement@360 j &gt; 0 | 当前参考未静态绑定；见下方边界说明 |

| L362 | heap.pop | lambda@345（定义体，执行时间取决于调用/调度） → for_statement@360 j &gt; 0 | 当前参考未静态绑定；见下方边界说明 |

| L367 | task | if_statement@365 (thread_pool_ == nullptr or count == 1) → for_statement@366 i &lt; count | 当前参考未静态绑定；见下方边界说明 |

| L372 | futures.push_back | if_statement@365 (thread_pool_ == nullptr or count == 1) [else 分支] → for_statement@371 i &lt; count | 当前参考未静态绑定；见下方边界说明 |

| L372 | thread_pool_-&gt;GeneralEnqueue | if_statement@365 (thread_pool_ == nullptr or count == 1) [else 分支] → for_statement@371 i &lt; count | 当前参考未静态绑定；见下方边界说明 |

| L375 | item.get | if_statement@365 (thread_pool_ == nullptr or count == 1) [else 分支] → for_range_loop@374 | 当前参考未静态绑定；见下方边界说明 |

| L383 | std::min&lt;uint64_t&gt; | if_statement@379 (ctx != nullptr and ctx-&gt;stats != nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L383 | std::numeric_limits&lt;uint32_t&gt;::max | if_statement@379 (ctx != nullptr and ctx-&gt;stats != nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L384 | ctx-&gt;stats-&gt;dist_cmp.fetch_add | if_statement@379 (ctx != nullptr and ctx-&gt;stats != nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L385 | ctx-&gt;stats-&gt;AddDistance | if_statement@379 (ctx != nullptr and ctx-&gt;stats != nullptr) | 当前参考未静态绑定；见下方边界说明 |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。
