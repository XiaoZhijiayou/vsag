# gno_imi_partition.cpp：逐函数完整源码与调用点

[主讲解](../code_walkthrough.md) · [函数总目录](README.md)

源码：[ src/algorithm/ivf/gno_imi_partition.cpp ](../../../../src/algorithm/ivf/gno_imi_partition.cpp)。基线 `fd363937`。以下源码函数体完整保留；调用点表是语法树中的显式调用表达式，按源码位置排列，不代表 C++ 参数求值顺序。表中“候选实现”需结合类型和参数选分支，不能将同名函数全部视为必经路径。

- [matmul · L40](gno_imi_partition.md#L40)

- [GNOIMIPartition::GNOIMIPartition · L58](gno_imi_partition.md#L58)

- [GNOIMIPartition::Train · L88](gno_imi_partition.md#L88)

- [GNOIMIPartition::ClassifyDatas · L201](gno_imi_partition.md#L201)

- [GNOIMIPartition::ClassifyDatasForSearch · L221](gno_imi_partition.md#L221)

- [GNOIMIPartition::Serialize · L323](gno_imi_partition.md#L323)

- [GNOIMIPartition::Deserialize · L334](gno_imi_partition.md#L334)

- [GNOIMIPartition::inner_classify_datas · L346](gno_imi_partition.md#L346)

- [GNOIMIPartition::inner_joint_classify_datas · L367](gno_imi_partition.md#L367)

- [GNOIMIPartition::GetCentroid · L440](gno_imi_partition.md#L440)


<a id="L40"></a>

## `matmul`

源码位置：`src/algorithm/ivf/gno_imi_partition.cpp:40–56`。

先从签名确认输入、返回值和 const/override，再按完整函数体的条件阅读调用点。下表保留了本函数的显式调用以及 lambda 中的调用；进入下层时用“候选实现”定位，未解析的对象由源码静态类型/运行时类型确认。

### 完整函数

```cpp
void
matmul(const float* A, const float* B, float* C, int64_t M, int64_t N, int64_t K) {
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

| L42 | BlasFunction::Sgemm | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L58"></a>

## `GNOIMIPartition::GNOIMIPartition`

源码位置：`src/algorithm/ivf/gno_imi_partition.cpp:58–86`。

先从签名确认输入、返回值和 const/override，再按完整函数体的条件阅读调用点。下表保留了本函数的显式调用以及 lambda 中的调用；进入下层时用“候选实现”定位，未解析的对象由源码静态类型/运行时类型确认。

### 完整函数

```cpp
GNOIMIPartition::GNOIMIPartition(const IndexCommonParam& common_param,
                                 const IVFPartitionStrategyParametersPtr& param)
    : IVFPartitionStrategy(common_param,
                           param->gnoimi_param->first_order_buckets_count *
                               param->gnoimi_param->second_order_buckets_count),
      bucket_count_s_(param->gnoimi_param->first_order_buckets_count),
      bucket_count_t_(param->gnoimi_param->second_order_buckets_count),
      data_centroids_s_(allocator_),
      data_centroids_t_(allocator_),
      norms_s_(allocator_),
      norms_t_(allocator_),
      precomputed_terms_st_(allocator_),
      common_param_(common_param) {
    data_centroids_s_.resize(bucket_count_s_ * dim_);
    data_centroids_t_.resize(bucket_count_t_ * dim_);
    norms_s_.resize(bucket_count_s_);
    norms_t_.resize(bucket_count_t_);
    precomputed_terms_st_.resize(static_cast<long>(bucket_count_s_) * bucket_count_t_);

    param_ptr_ = std::make_shared<BruteForceParameter>();
    param_ptr_->base_codes_param = std::make_shared<FlattenDataCellParameter>();
    JsonType memory_json;
    memory_json["type"].SetString(IO_TYPE_VALUE_BLOCK_MEMORY_IO);
    param_ptr_->base_codes_param->io_parameter = IOParameter::GetIOParameterByJson(memory_json);
    JsonType quantizer_json;
    quantizer_json["type"].SetString(QUANTIZATION_TYPE_VALUE_FP32);
    param_ptr_->base_codes_param->quantizer_parameter =
        QuantizerParameter::GetQuantizerParameterByJson(quantizer_json);
}
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L71 | data_centroids_s_.resize | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L72 | data_centroids_t_.resize | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L73 | norms_s_.resize | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L74 | norms_t_.resize | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L75 | precomputed_terms_st_.resize | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L77 | std::make_shared&lt;BruteForceParameter&gt; | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L78 | std::make_shared&lt;FlattenDataCellParameter&gt; | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L80 | memory_json["type"].SetString | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L81 | IOParameter::GetIOParameterByJson | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L83 | quantizer_json["type"].SetString | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L85 | QuantizerParameter::GetQuantizerParameterByJson | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L88"></a>

## `GNOIMIPartition::Train`

源码位置：`src/algorithm/ivf/gno_imi_partition.cpp:88–199`。

这是状态改变函数。先看重复训练的提前返回，再看训练数据是否采样/归一化/变成残差，最后确认状态位在何处设置。分区 Train 与量化器 Train 不是同一个模型。

### 完整函数

```cpp
void
GNOIMIPartition::Train(const DatasetPtr dataset) {
    auto dim = this->dim_;
    auto centroids_s = Dataset::Make();
    auto centroids_t = Dataset::Make();
    const auto* vectors = dataset->GetFloat32Vectors();
    auto num_element = dataset->GetNumElements();
    Vector<float> norm_vectors(allocator_);
    if (metric_type_ == MetricType::METRIC_TYPE_COSINE) {
        norm_vectors.resize(num_element * dim);
        for (int64_t i = 0; i < num_element; ++i) {
            Normalize(vectors + i * dim_, norm_vectors.data() + i * dim_, dim_);
        }
        vectors = norm_vectors.data();
    }

    Vector<LabelType> ids_centroids_s(this->bucket_count_s_, allocator_);
    Vector<LabelType> ids_centroids_t(this->bucket_count_t_, allocator_);
    Vector<float> data_centroids_s_tmp(this->bucket_count_s_ * dim_, allocator_);
    Vector<float> data_centroids_t_tmp(this->bucket_count_t_ * dim_, allocator_);

    std::iota(ids_centroids_s.begin(), ids_centroids_s.end(), 0);
    std::iota(ids_centroids_t.begin(), ids_centroids_t.end(), 0);
    centroids_s->Ids(ids_centroids_s.data())
        ->Dim(dim)
        ->Float32Vectors(data_centroids_s_tmp.data())
        ->NumElements(this->bucket_count_s_)
        ->Owner(false);
    centroids_t->Ids(ids_centroids_t.data())
        ->Dim(dim)
        ->Float32Vectors(data_centroids_t_tmp.data())
        ->NumElements(this->bucket_count_t_)
        ->Owner(false);

    KMeansCluster cls(static_cast<int32_t>(dim), this->allocator_);
    Vector<float> residuals(vectors, vectors + num_element * dim, allocator_);

    auto train_and_get_residual = [&, this](const DatasetPtr& centroids,
                                            float* data_centroids,
                                            double* err) {
        cls.Run(centroids->GetNumElements(), residuals.data(), num_element, 30, err);
        memcpy(data_centroids, cls.k_centroids_, dim * centroids->GetNumElements() * sizeof(float));
        BruteForce route_index(param_ptr_, common_param_);
        auto build_result = route_index.Build(centroids);
        auto assign = this->inner_classify_datas(route_index, residuals.data(), num_element);
        this->GetResidual(num_element, vectors, residuals.data(), data_centroids, assign.data());
    };

    // train loop
    double min_err = std::numeric_limits<double>::max();
    for (uint64_t i = 0; i < 2; ++i) {
        double err_to_s = 0.0;
        double err_to_t = 0.0;
        train_and_get_residual(centroids_s, data_centroids_s_tmp.data(), &err_to_s);
        logger::info("gnoimi train iter: {}, err of centroids_s: {}", i, err_to_s);

        train_and_get_residual(centroids_t, data_centroids_t_tmp.data(), &err_to_t);
        logger::info("gnoimi train iter: {}, err of centroids_t: {}", i, err_to_t);

        if (err_to_t < min_err) {
            min_err = err_to_t;
            std::copy(data_centroids_s_tmp.begin(),
                      data_centroids_s_tmp.end(),
                      data_centroids_s_.begin());
            std::copy(data_centroids_t_tmp.begin(),
                      data_centroids_t_tmp.end(),
                      data_centroids_t_.begin());
        }
    }

    for (BucketIdType i = 0; i < bucket_count_s_; ++i) {
        auto norm_sqr = FP32ComputeIP(
            data_centroids_s_.data() + i * dim_, data_centroids_s_.data() + i * dim_, dim_);
        norms_s_[i] = norm_sqr / 2;
    }

    Vector<std::pair<float, BucketIdType>> norms_t(bucket_count_t_, this->allocator_);
    for (BucketIdType i = 0; i < bucket_count_t_; ++i) {
        auto norm_sqr = FP32ComputeIP(
            data_centroids_t_.data() + i * dim_, data_centroids_t_.data() + i * dim_, dim_);
        norms_t[i].first = norm_sqr / 2;
        norms_t[i].second = i;
    }

    // Rearrange data_centroids_t_ based on ascending order of their norms.
    std::sort(norms_t.begin(), norms_t.end(), std::greater<>());
    std::vector<float> temp_data(bucket_count_t_ * dim_, 0.0);
    for (BucketIdType i = 0; i < bucket_count_t_; ++i) {
        BucketIdType src_idx = norms_t[i].second;
        uint64_t src_offset = src_idx * dim_;
        uint64_t dst_offset = i * dim_;
        std::copy(data_centroids_t_.data() + src_offset,
                  data_centroids_t_.data() + src_offset + dim_,
                  temp_data.data() + dst_offset);
        norms_t_[i] = norms_t[i].first;
    }
    std::copy(temp_data.begin(), temp_data.end(), data_centroids_t_.data());

    Vector<float> ip_st(static_cast<long>(bucket_count_s_) * bucket_count_t_, allocator_);
    matmul(data_centroids_s_.data(),
           data_centroids_t_.data(),
           ip_st.data(),
           bucket_count_s_,
           bucket_count_t_,
           dim_);
    for (BucketIdType i = 0; i < bucket_count_s_ * bucket_count_t_; ++i) {
        BucketIdType cur_bucket_id_t = i % bucket_count_t_;
        precomputed_terms_st_[i] = norms_t_[cur_bucket_id_t] + ip_st[i];
    }

    this->is_trained_ = true;
}
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L91 | Dataset::Make | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L92 | Dataset::Make | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L93 | dataset-&gt;GetFloat32Vectors | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L94 | dataset-&gt;GetNumElements | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L97 | norm_vectors.resize | if_statement@96 (metric_type_ == MetricType::METRIC_TYPE_COSINE) | 当前参考未静态绑定；见下方边界说明 |

| L99 | Normalize | if_statement@96 (metric_type_ == MetricType::METRIC_TYPE_COSINE) → for_statement@98 i &lt; num_element | 当前参考未静态绑定；见下方边界说明 |

| L99 | norm_vectors.data | if_statement@96 (metric_type_ == MetricType::METRIC_TYPE_COSINE) → for_statement@98 i &lt; num_element | 当前参考未静态绑定；见下方边界说明 |

| L101 | norm_vectors.data | if_statement@96 (metric_type_ == MetricType::METRIC_TYPE_COSINE) | 当前参考未静态绑定；见下方边界说明 |

| L109 | std::iota | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L109 | ids_centroids_s.begin | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L109 | ids_centroids_s.end | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L110 | std::iota | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L110 | ids_centroids_t.begin | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L110 | ids_centroids_t.end | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L111 | centroids_s-&gt;Ids(ids_centroids_s.data()) -&gt;Dim(dim) -&gt;Float32Vectors(data_centroids_s_tmp.data()) -&gt;NumElements(this-&gt;bucket_count_s_) -&gt;Owner | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L111 | centroids_s-&gt;Ids(ids_centroids_s.data()) -&gt;Dim(dim) -&gt;Float32Vectors(data_centroids_s_tmp.data()) -&gt;NumElements | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L111 | centroids_s-&gt;Ids(ids_centroids_s.data()) -&gt;Dim(dim) -&gt;Float32Vectors | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L111 | centroids_s-&gt;Ids(ids_centroids_s.data()) -&gt;Dim | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L111 | centroids_s-&gt;Ids | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L111 | ids_centroids_s.data | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L113 | data_centroids_s_tmp.data | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L116 | centroids_t-&gt;Ids(ids_centroids_t.data()) -&gt;Dim(dim) -&gt;Float32Vectors(data_centroids_t_tmp.data()) -&gt;NumElements(this-&gt;bucket_count_t_) -&gt;Owner | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L116 | centroids_t-&gt;Ids(ids_centroids_t.data()) -&gt;Dim(dim) -&gt;Float32Vectors(data_centroids_t_tmp.data()) -&gt;NumElements | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L116 | centroids_t-&gt;Ids(ids_centroids_t.data()) -&gt;Dim(dim) -&gt;Float32Vectors | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L116 | centroids_t-&gt;Ids(ids_centroids_t.data()) -&gt;Dim | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L116 | centroids_t-&gt;Ids | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L116 | ids_centroids_t.data | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L118 | data_centroids_t_tmp.data | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L128 | cls.Run | lambda@125（定义体，执行时间取决于调用/调度） | [KMeansCluster::Run · L48](kmeans_cluster.md#L48) |

| L128 | centroids-&gt;GetNumElements | lambda@125（定义体，执行时间取决于调用/调度） | 当前参考未静态绑定；见下方边界说明 |

| L128 | residuals.data | lambda@125（定义体，执行时间取决于调用/调度） | 当前参考未静态绑定；见下方边界说明 |

| L129 | memcpy | lambda@125（定义体，执行时间取决于调用/调度） | 当前参考未静态绑定；见下方边界说明 |

| L129 | centroids-&gt;GetNumElements | lambda@125（定义体，执行时间取决于调用/调度） | 当前参考未静态绑定；见下方边界说明 |

| L131 | route_index.Build | lambda@125（定义体，执行时间取决于调用/调度） | 当前参考未静态绑定；见下方边界说明 |

| L132 | this-&gt;inner_classify_datas | lambda@125（定义体，执行时间取决于调用/调度） | [GNOIMIPartition::inner_classify_datas · L346](gno_imi_partition.md#L346) |

| L132 | residuals.data | lambda@125（定义体，执行时间取决于调用/调度） | 当前参考未静态绑定；见下方边界说明 |

| L133 | this-&gt;GetResidual | lambda@125（定义体，执行时间取决于调用/调度） | [IVFPartitionStrategy::GetResidual · L22](ivf_partition_strategy.md#L22) |

| L133 | residuals.data | lambda@125（定义体，执行时间取决于调用/调度） | 当前参考未静态绑定；见下方边界说明 |

| L133 | assign.data | lambda@125（定义体，执行时间取决于调用/调度） | 当前参考未静态绑定；见下方边界说明 |

| L137 | std::numeric_limits&lt;double&gt;::max | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L141 | train_and_get_residual | for_statement@138 i &lt; 2 | 当前参考未静态绑定；见下方边界说明 |

| L141 | data_centroids_s_tmp.data | for_statement@138 i &lt; 2 | 当前参考未静态绑定；见下方边界说明 |

| L142 | logger::info | for_statement@138 i &lt; 2 | 当前参考未静态绑定；见下方边界说明 |

| L144 | train_and_get_residual | for_statement@138 i &lt; 2 | 当前参考未静态绑定；见下方边界说明 |

| L144 | data_centroids_t_tmp.data | for_statement@138 i &lt; 2 | 当前参考未静态绑定；见下方边界说明 |

| L145 | logger::info | for_statement@138 i &lt; 2 | 当前参考未静态绑定；见下方边界说明 |

| L149 | std::copy | for_statement@138 i &lt; 2 → if_statement@147 (err_to_t &lt; min_err) | 当前参考未静态绑定；见下方边界说明 |

| L149 | data_centroids_s_tmp.begin | for_statement@138 i &lt; 2 → if_statement@147 (err_to_t &lt; min_err) | 当前参考未静态绑定；见下方边界说明 |

| L150 | data_centroids_s_tmp.end | for_statement@138 i &lt; 2 → if_statement@147 (err_to_t &lt; min_err) | 当前参考未静态绑定；见下方边界说明 |

| L151 | data_centroids_s_.begin | for_statement@138 i &lt; 2 → if_statement@147 (err_to_t &lt; min_err) | 当前参考未静态绑定；见下方边界说明 |

| L152 | std::copy | for_statement@138 i &lt; 2 → if_statement@147 (err_to_t &lt; min_err) | 当前参考未静态绑定；见下方边界说明 |

| L152 | data_centroids_t_tmp.begin | for_statement@138 i &lt; 2 → if_statement@147 (err_to_t &lt; min_err) | 当前参考未静态绑定；见下方边界说明 |

| L153 | data_centroids_t_tmp.end | for_statement@138 i &lt; 2 → if_statement@147 (err_to_t &lt; min_err) | 当前参考未静态绑定；见下方边界说明 |

| L154 | data_centroids_t_.begin | for_statement@138 i &lt; 2 → if_statement@147 (err_to_t &lt; min_err) | 当前参考未静态绑定；见下方边界说明 |

| L159 | FP32ComputeIP | for_statement@158 i &lt; bucket_count_s_ | 当前参考未静态绑定；见下方边界说明 |

| L160 | data_centroids_s_.data | for_statement@158 i &lt; bucket_count_s_ | 当前参考未静态绑定；见下方边界说明 |

| L160 | data_centroids_s_.data | for_statement@158 i &lt; bucket_count_s_ | 当前参考未静态绑定；见下方边界说明 |

| L166 | FP32ComputeIP | for_statement@165 i &lt; bucket_count_t_ | 当前参考未静态绑定；见下方边界说明 |

| L167 | data_centroids_t_.data | for_statement@165 i &lt; bucket_count_t_ | 当前参考未静态绑定；见下方边界说明 |

| L167 | data_centroids_t_.data | for_statement@165 i &lt; bucket_count_t_ | 当前参考未静态绑定；见下方边界说明 |

| L173 | std::sort | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L173 | norms_t.begin | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L173 | norms_t.end | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L173 | std::greater&lt;&gt; | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L179 | std::copy | for_statement@175 i &lt; bucket_count_t_ | 当前参考未静态绑定；见下方边界说明 |

| L179 | data_centroids_t_.data | for_statement@175 i &lt; bucket_count_t_ | 当前参考未静态绑定；见下方边界说明 |

| L180 | data_centroids_t_.data | for_statement@175 i &lt; bucket_count_t_ | 当前参考未静态绑定；见下方边界说明 |

| L181 | temp_data.data | for_statement@175 i &lt; bucket_count_t_ | 当前参考未静态绑定；见下方边界说明 |

| L184 | std::copy | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L184 | temp_data.begin | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L184 | temp_data.end | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L184 | data_centroids_t_.data | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L187 | matmul | 函数本体；短路求值/提前返回见源码 | [matmul · L40](gno_imi_partition.md#L40) |

| L187 | data_centroids_s_.data | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L188 | data_centroids_t_.data | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L189 | ip_st.data | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L201"></a>

## `GNOIMIPartition::ClassifyDatas`

源码位置：`src/algorithm/ivf/gno_imi_partition.cpp:201–219`。

输入 count 条向量，返回 count×buckets_per_data 个 bucket ID。普通 IVF 由 use_route_graph 决定中心图或中心扫描。调用中返回的 IDs 是中心/桶 ID，不是业务数据 ID。

### 完整函数

```cpp
Vector<BucketIdType>
GNOIMIPartition::ClassifyDatas(const void* datas,
                               int64_t count,
                               BucketIdType buckets_per_data,
                               QueryContext* ctx) const {
    Vector<float> norm_vectors(allocator_);
    if (metric_type_ == MetricType::METRIC_TYPE_COSINE) {
        norm_vectors.resize(count * dim_);
        for (int64_t i = 0; i < count; ++i) {
            Normalize(
                static_cast<const float*>(datas) + i * dim_, norm_vectors.data() + i * dim_, dim_);
        }
        datas = norm_vectors.data();
    }
    Vector<BucketIdType> result(buckets_per_data * count, this->allocator_);
    inner_joint_classify_datas(
        reinterpret_cast<const float*>(datas), count, buckets_per_data, result.data(), ctx);
    return result;
}
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L208 | norm_vectors.resize | if_statement@207 (metric_type_ == MetricType::METRIC_TYPE_COSINE) | 当前参考未静态绑定；见下方边界说明 |

| L210 | Normalize | if_statement@207 (metric_type_ == MetricType::METRIC_TYPE_COSINE) → for_statement@209 i &lt; count | 当前参考未静态绑定；见下方边界说明 |

| L211 | norm_vectors.data | if_statement@207 (metric_type_ == MetricType::METRIC_TYPE_COSINE) → for_statement@209 i &lt; count | 当前参考未静态绑定；见下方边界说明 |

| L213 | norm_vectors.data | if_statement@207 (metric_type_ == MetricType::METRIC_TYPE_COSINE) | 当前参考未静态绑定；见下方边界说明 |

| L216 | inner_joint_classify_datas | 函数本体；短路求值/提前返回见源码 | [GNOIMIPartition::inner_joint_classify_datas · L367](gno_imi_partition.md#L367) |

| L217 | result.data | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L221"></a>

## `GNOIMIPartition::ClassifyDatasForSearch`

源码位置：`src/algorithm/ivf/gno_imi_partition.cpp:221–321`。

这是选桶的虚调用入口。普通 IVF 使用基类转发到 ClassifyDatas；GNO-IMI 覆盖此函数，采用两组中心组合。param.scan_bucket_size 决定输出宽度。

### 完整函数

```cpp
Vector<BucketIdType>
GNOIMIPartition::ClassifyDatasForSearch(const void* datas,
                                        int64_t count,
                                        const InnerSearchParam& param,
                                        QueryContext* ctx) {
    Vector<float> norm_vectors(allocator_);
    if (metric_type_ == MetricType::METRIC_TYPE_COSINE) {
        norm_vectors.resize(count * dim_);
        for (int64_t i = 0; i < count; ++i) {
            Normalize(
                static_cast<const float*>(datas) + i * dim_, norm_vectors.data() + i * dim_, dim_);
        }
        datas = norm_vectors.data();
    }
    auto buckets_per_data = param.scan_bucket_size;
    Vector<BucketIdType> result(buckets_per_data * count, this->allocator_);
    std::fill(result.begin(), result.end(), static_cast<BucketIdType>(-1));
    auto candidate_count_s = bucket_count_s_;
    Vector<BucketIdType> candidate_s_id(candidate_count_s, this->allocator_);
    Vector<float> candidate_s_dist(candidate_count_s, this->allocator_);
    Vector<float> dist_to_s(bucket_count_s_ * count, this->allocator_);
    Vector<float> dist_to_t(bucket_count_t_ * count, this->allocator_);
    auto* dist_to_s_data = dist_to_s.data();
    auto* dist_to_t_data = dist_to_t.data();
    auto* candidate_s_id_data = candidate_s_id.data();
    auto* candidate_s_dist_data = candidate_s_dist.data();
    uint64_t distance_evaluations = 0;

    matmul(reinterpret_cast<const float*>(datas),
           data_centroids_s_.data(),
           dist_to_s_data,
           count,
           bucket_count_s_,
           dim_);
    matmul(reinterpret_cast<const float*>(datas),
           data_centroids_t_.data(),
           dist_to_t_data,
           count,
           bucket_count_t_,
           dim_);

    for (uint64_t i = 0; i < count; i++) {
        auto qnorm = FP32ComputeIP(reinterpret_cast<const float*>(datas) + i * dim_,
                                   reinterpret_cast<const float*>(datas) + i * dim_,
                                   dim_) /
                     2;
        MaxHeap heap(this->allocator_);
        for (uint64_t j = 0; j < bucket_count_s_; ++j) {
            auto dist_term_s = norms_s_[j] - dist_to_s_data[i * bucket_count_s_ + j];
            ++distance_evaluations;
            if (heap.size() < candidate_count_s || dist_term_s < heap.top().first) {
                heap.emplace(dist_term_s, j);
            }
            if (heap.size() > candidate_count_s) {
                heap.pop();
            }
        }
        for (auto j = static_cast<int64_t>(candidate_count_s - 1); j >= 0; --j) {
            candidate_s_id_data[j] = static_cast<BucketIdType>(heap.top().second);
            candidate_s_dist_data[j] = heap.top().first;
            heap.pop();
        }
        CHECK_ARGUMENT(heap.empty(), fmt::format("Unexpected non-empty heap after pop candidates"));

        auto scan_bucket_count_s = static_cast<BucketIdType>(
            std::floor(static_cast<float>(bucket_count_s_) * param.first_order_scan_ratio));
        scan_bucket_count_s = std::max(scan_bucket_count_s, 1);
        for (uint64_t j = 0; j < scan_bucket_count_s; ++j) {
            for (uint64_t k = 0; k < bucket_count_t_; ++k) {
                auto cur_bucket_id_s = candidate_s_id_data[j];
                auto cur_bucket_id_t = k;
                float dist_term_st = candidate_s_dist_data[j] +
                                     precomputed_terms_st_[static_cast<unsigned long>(
                                                               cur_bucket_id_s * bucket_count_t_) +
                                                           cur_bucket_id_t] -
                                     dist_to_t_data[i * bucket_count_t_ + cur_bucket_id_t];

                auto cur_bucket_id_global =
                    static_cast<long>(cur_bucket_id_s) * bucket_count_t_ + cur_bucket_id_t;
                ++distance_evaluations;
                if (heap.size() < buckets_per_data || dist_term_st < heap.top().first) {
                    heap.emplace(dist_term_st, cur_bucket_id_global);
                }
                if (heap.size() > buckets_per_data) {
                    heap.pop();
                }
            }
        }
        BucketIdType size = std::min((BucketIdType)heap.size(), buckets_per_data);
        for (auto j = static_cast<int64_t>(size - 1); j >= 0 && !heap.empty(); --j) {
            result[i * buckets_per_data + j] = static_cast<BucketIdType>(heap.top().second);
            heap.pop();
        }
    }
    if (ctx != nullptr and ctx->stats != nullptr) {
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

| L228 | norm_vectors.resize | if_statement@227 (metric_type_ == MetricType::METRIC_TYPE_COSINE) | 当前参考未静态绑定；见下方边界说明 |

| L230 | Normalize | if_statement@227 (metric_type_ == MetricType::METRIC_TYPE_COSINE) → for_statement@229 i &lt; count | 当前参考未静态绑定；见下方边界说明 |

| L231 | norm_vectors.data | if_statement@227 (metric_type_ == MetricType::METRIC_TYPE_COSINE) → for_statement@229 i &lt; count | 当前参考未静态绑定；见下方边界说明 |

| L233 | norm_vectors.data | if_statement@227 (metric_type_ == MetricType::METRIC_TYPE_COSINE) | 当前参考未静态绑定；见下方边界说明 |

| L237 | std::fill | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L237 | result.begin | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L237 | result.end | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L243 | dist_to_s.data | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L244 | dist_to_t.data | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L245 | candidate_s_id.data | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L246 | candidate_s_dist.data | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L249 | matmul | 函数本体；短路求值/提前返回见源码 | [matmul · L40](gno_imi_partition.md#L40) |

| L250 | data_centroids_s_.data | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L255 | matmul | 函数本体；短路求值/提前返回见源码 | [matmul · L40](gno_imi_partition.md#L40) |

| L256 | data_centroids_t_.data | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L263 | FP32ComputeIP | for_statement@262 i &lt; count | 当前参考未静态绑定；见下方边界说明 |

| L271 | heap.size | for_statement@262 i &lt; count → for_statement@268 j &lt; bucket_count_s_ → if_statement@271 (heap.size() &lt; candidate_count_s &#124;&#124; dist_term_s &lt; heap.top().first) | 当前参考未静态绑定；见下方边界说明 |

| L271 | heap.top | for_statement@262 i &lt; count → for_statement@268 j &lt; bucket_count_s_ → if_statement@271 (heap.size() &lt; candidate_count_s &#124;&#124; dist_term_s &lt; heap.top().first) | 当前参考未静态绑定；见下方边界说明 |

| L272 | heap.emplace | for_statement@262 i &lt; count → for_statement@268 j &lt; bucket_count_s_ → if_statement@271 (heap.size() &lt; candidate_count_s &#124;&#124; dist_term_s &lt; heap.top().first) | 当前参考未静态绑定；见下方边界说明 |

| L274 | heap.size | for_statement@262 i &lt; count → for_statement@268 j &lt; bucket_count_s_ → if_statement@274 (heap.size() &gt; candidate_count_s) | 当前参考未静态绑定；见下方边界说明 |

| L275 | heap.pop | for_statement@262 i &lt; count → for_statement@268 j &lt; bucket_count_s_ → if_statement@274 (heap.size() &gt; candidate_count_s) | 当前参考未静态绑定；见下方边界说明 |

| L279 | heap.top | for_statement@262 i &lt; count → for_statement@278 j &gt;= 0 | 当前参考未静态绑定；见下方边界说明 |

| L280 | heap.top | for_statement@262 i &lt; count → for_statement@278 j &gt;= 0 | 当前参考未静态绑定；见下方边界说明 |

| L281 | heap.pop | for_statement@262 i &lt; count → for_statement@278 j &gt;= 0 | 当前参考未静态绑定；见下方边界说明 |

| L283 | CHECK_ARGUMENT | for_statement@262 i &lt; count | 当前参考未静态绑定；见下方边界说明 |

| L283 | heap.empty | for_statement@262 i &lt; count | 当前参考未静态绑定；见下方边界说明 |

| L283 | fmt::format | for_statement@262 i &lt; count | 当前参考未静态绑定；见下方边界说明 |

| L286 | std::floor | for_statement@262 i &lt; count | 当前参考未静态绑定；见下方边界说明 |

| L287 | std::max | for_statement@262 i &lt; count | 当前参考未静态绑定；见下方边界说明 |

| L301 | heap.size | for_statement@262 i &lt; count → for_statement@288 j &lt; scan_bucket_count_s → for_statement@289 k &lt; bucket_count_t_ → if_statement@301 (heap.size() &lt; buckets_per_data &#124;&#124; dist_term_st &lt; heap.top().first) | 当前参考未静态绑定；见下方边界说明 |

| L301 | heap.top | for_statement@262 i &lt; count → for_statement@288 j &lt; scan_bucket_count_s → for_statement@289 k &lt; bucket_count_t_ → if_statement@301 (heap.size() &lt; buckets_per_data &#124;&#124; dist_term_st &lt; heap.top().first) | 当前参考未静态绑定；见下方边界说明 |

| L302 | heap.emplace | for_statement@262 i &lt; count → for_statement@288 j &lt; scan_bucket_count_s → for_statement@289 k &lt; bucket_count_t_ → if_statement@301 (heap.size() &lt; buckets_per_data &#124;&#124; dist_term_st &lt; heap.top().first) | 当前参考未静态绑定；见下方边界说明 |

| L304 | heap.size | for_statement@262 i &lt; count → for_statement@288 j &lt; scan_bucket_count_s → for_statement@289 k &lt; bucket_count_t_ → if_statement@304 (heap.size() &gt; buckets_per_data) | 当前参考未静态绑定；见下方边界说明 |

| L305 | heap.pop | for_statement@262 i &lt; count → for_statement@288 j &lt; scan_bucket_count_s → for_statement@289 k &lt; bucket_count_t_ → if_statement@304 (heap.size() &gt; buckets_per_data) | 当前参考未静态绑定；见下方边界说明 |

| L309 | std::min | for_statement@262 i &lt; count | 当前参考未静态绑定；见下方边界说明 |

| L309 | heap.size | for_statement@262 i &lt; count | 当前参考未静态绑定；见下方边界说明 |

| L310 | heap.empty | for_statement@262 i &lt; count → for_statement@310 j &gt;= 0 && !heap.empty() | 当前参考未静态绑定；见下方边界说明 |

| L311 | heap.top | for_statement@262 i &lt; count → for_statement@310 j &gt;= 0 && !heap.empty() | 当前参考未静态绑定；见下方边界说明 |

| L312 | heap.pop | for_statement@262 i &lt; count → for_statement@310 j &gt;= 0 && !heap.empty() | 当前参考未静态绑定；见下方边界说明 |

| L316 | ctx-&gt;stats-&gt;AddDistance | if_statement@315 (ctx != nullptr and ctx-&gt;stats != nullptr) | 当前参考未静态绑定；见下方边界说明 |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L323"></a>

## `GNOIMIPartition::Serialize`

源码位置：`src/algorithm/ivf/gno_imi_partition.cpp:323–333`。

先从签名确认输入、返回值和 const/override，再按完整函数体的条件阅读调用点。下表保留了本函数的显式调用以及 lambda 中的调用；进入下层时用“候选实现”定位，未解析的对象由源码静态类型/运行时类型确认。

### 完整函数

```cpp
void
GNOIMIPartition::Serialize(StreamWriter& writer) {
    IVFPartitionStrategy::Serialize(writer);
    StreamWriter::WriteObj(writer, this->bucket_count_s_);
    StreamWriter::WriteObj(writer, this->bucket_count_t_);
    StreamWriter::WriteVector(writer, this->data_centroids_s_);
    StreamWriter::WriteVector(writer, this->data_centroids_t_);
    StreamWriter::WriteVector(writer, this->norms_s_);
    StreamWriter::WriteVector(writer, this->norms_t_);
    StreamWriter::WriteVector(writer, this->precomputed_terms_st_);
}
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L325 | IVFPartitionStrategy::Serialize | 函数本体；短路求值/提前返回见源码 | [IVFPartitionStrategy::Serialize · L75](ivf_partition_strategy_h.md#L75) |

| L326 | StreamWriter::WriteObj | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L327 | StreamWriter::WriteObj | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L328 | StreamWriter::WriteVector | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L329 | StreamWriter::WriteVector | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L330 | StreamWriter::WriteVector | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L331 | StreamWriter::WriteVector | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L332 | StreamWriter::WriteVector | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L334"></a>

## `GNOIMIPartition::Deserialize`

源码位置：`src/algorithm/ivf/gno_imi_partition.cpp:334–344`。

先从签名确认输入、返回值和 const/override，再按完整函数体的条件阅读调用点。下表保留了本函数的显式调用以及 lambda 中的调用；进入下层时用“候选实现”定位，未解析的对象由源码静态类型/运行时类型确认。

### 完整函数

```cpp
void
GNOIMIPartition::Deserialize(LvalueOrRvalue<StreamReader> reader) {
    IVFPartitionStrategy::Deserialize(reader);
    StreamReader::ReadObj<BucketIdType>(reader, this->bucket_count_s_);
    StreamReader::ReadObj<BucketIdType>(reader, this->bucket_count_t_);
    StreamReader::ReadVector(reader, this->data_centroids_s_);
    StreamReader::ReadVector(reader, this->data_centroids_t_);
    StreamReader::ReadVector(reader, this->norms_s_);
    StreamReader::ReadVector(reader, this->norms_t_);
    StreamReader::ReadVector(reader, this->precomputed_terms_st_);
}
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L336 | IVFPartitionStrategy::Deserialize | 函数本体；短路求值/提前返回见源码 | [IVFPartitionStrategy::Deserialize · L82](ivf_partition_strategy_h.md#L82) |

| L337 | StreamReader::ReadObj&lt;BucketIdType&gt; | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L338 | StreamReader::ReadObj&lt;BucketIdType&gt; | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L339 | StreamReader::ReadVector | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L340 | StreamReader::ReadVector | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L341 | StreamReader::ReadVector | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L342 | StreamReader::ReadVector | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L343 | StreamReader::ReadVector | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L346"></a>

## `GNOIMIPartition::inner_classify_datas`

源码位置：`src/algorithm/ivf/gno_imi_partition.cpp:346–365`。

先从签名确认输入、返回值和 const/override，再按完整函数体的条件阅读调用点。下表保留了本函数的显式调用以及 lambda 中的调用；进入下层时用“候选实现”定位，未解析的对象由源码静态类型/运行时类型确认。

### 完整函数

```cpp
Vector<BucketIdType>
GNOIMIPartition::inner_classify_datas(BruteForce& route_index, const float* datas, int64_t count) {
    BucketIdType buckets_per_data = 1;
    Vector<BucketIdType> result(buckets_per_data * count, this->allocator_);
    for (int64_t i = 0; i < count; ++i) {
        auto query = Dataset::Make();
        query->Dim(this->dim_)
            ->Float32Vectors(datas + i * this->dim_)
            ->NumElements(1)
            ->Owner(false);
        FilterPtr filter = nullptr;
        auto search_result = route_index.KnnSearch(query, buckets_per_data, "{}", filter);
        const auto* result_ids = search_result->GetIds();

        for (int64_t j = 0; j < buckets_per_data; ++j) {
            result[i * buckets_per_data + j] = static_cast<BucketIdType>(result_ids[j]);
        }
    }
    return result;
}
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L351 | Dataset::Make | for_statement@350 i &lt; count | 当前参考未静态绑定；见下方边界说明 |

| L352 | query-&gt;Dim(this-&gt;dim_) -&gt;Float32Vectors(datas + i * this-&gt;dim_) -&gt;NumElements(1) -&gt;Owner | for_statement@350 i &lt; count | 当前参考未静态绑定；见下方边界说明 |

| L352 | query-&gt;Dim(this-&gt;dim_) -&gt;Float32Vectors(datas + i * this-&gt;dim_) -&gt;NumElements | for_statement@350 i &lt; count | 当前参考未静态绑定；见下方边界说明 |

| L352 | query-&gt;Dim(this-&gt;dim_) -&gt;Float32Vectors | for_statement@350 i &lt; count | 当前参考未静态绑定；见下方边界说明 |

| L352 | query-&gt;Dim | for_statement@350 i &lt; count | 当前参考未静态绑定；见下方边界说明 |

| L357 | route_index.KnnSearch | for_statement@350 i &lt; count | 当前参考未静态绑定；见下方边界说明 |

| L358 | search_result-&gt;GetIds | for_statement@350 i &lt; count | 当前参考未静态绑定；见下方边界说明 |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L367"></a>

## `GNOIMIPartition::inner_joint_classify_datas`

源码位置：`src/algorithm/ivf/gno_imi_partition.cpp:367–438`。

先从签名确认输入、返回值和 const/override，再按完整函数体的条件阅读调用点。下表保留了本函数的显式调用以及 lambda 中的调用；进入下层时用“候选实现”定位，未解析的对象由源码静态类型/运行时类型确认。

### 完整函数

```cpp
void
GNOIMIPartition::inner_joint_classify_datas(const float* datas,
                                            int64_t count,
                                            BucketIdType buckets_per_data,
                                            BucketIdType* result,
                                            QueryContext* ctx) const {
    Vector<float> dist_to_s(bucket_count_s_ * count, this->allocator_);
    Vector<float> dist_to_t(bucket_count_t_ * count, this->allocator_);
    Vector<std::pair<float, BucketIdType>> precomputed_terms_s(bucket_count_s_, this->allocator_);

    matmul(datas, data_centroids_s_.data(), dist_to_s.data(), count, bucket_count_s_, dim_);
    matmul(datas, data_centroids_t_.data(), dist_to_t.data(), count, bucket_count_t_, dim_);
    // |x - s - t|^2 = |x|^2 + |s|^2 + |t|^2 - 2xs - 2xt + 2st
    // precomputed_terms_s: |x - s|^2 = |s|^2 - 2xs + |x|^2
    // precomputed_terms_st: |t|^2 + 2st
    float total_err = 0.0;
    uint32_t dist_cmp = 0;
    uint64_t distance_evaluations = 0;
    for (uint64_t i = 0; i < count; ++i) {
        auto data_norm = FP32ComputeIP(datas + i * dim_, datas + i * dim_, dim_);
        for (BucketIdType j = 0; j < bucket_count_s_; ++j) {
            precomputed_terms_s[j].first =
                norms_s_[j] - dist_to_s[i * bucket_count_s_ + j] + data_norm / 2;
            precomputed_terms_s[j].second = j;
            ++distance_evaluations;
        }
        std::sort(precomputed_terms_s.begin(), precomputed_terms_s.end());

        MaxHeap heap(this->allocator_);
        for (uint64_t j = 0; j < bucket_count_s_; ++j) {
            float cur_precomputed_term_s = precomputed_terms_s[j].first;
            BucketIdType cur_bucket_id_s = precomputed_terms_s[j].second;

            for (BucketIdType k = 0; k < bucket_count_t_; ++k) {
                BucketIdType cur_bucket_id_t = k;
                if (heap.size() >= buckets_per_data &&
                    std::sqrt(cur_precomputed_term_s) - std::sqrt(norms_t_[cur_bucket_id_t]) >
                        std::sqrt(heap.top().first)) {
                    break;
                }

                int cur_bucket_id_global = cur_bucket_id_s * bucket_count_t_ + cur_bucket_id_t;
                float dist = cur_precomputed_term_s - dist_to_t[i * bucket_count_t_ + k] +
                             precomputed_terms_st_[cur_bucket_id_global];
                ++dist_cmp;
                ++distance_evaluations;

                if (heap.size() < buckets_per_data || dist < heap.top().first) {
                    heap.emplace(dist, cur_bucket_id_global);
                }
                if (heap.size() > buckets_per_data) {
                    heap.pop();
                }
            }
        }

        for (auto j = static_cast<int64_t>(buckets_per_data - 1); j >= 0; --j) {
            result[i * buckets_per_data + j] = static_cast<BucketIdType>(heap.top().second);
            if (j == 0) {
                total_err += heap.top().first;
            }
            heap.pop();
        }
    }

    if (ctx != nullptr and ctx->stats != nullptr) {
        ctx->stats->dist_cmp.fetch_add(dist_cmp, std::memory_order_relaxed);
        ctx->stats->AddDistance(SearchStatistics::DistancePhase::ROUTING,
                                DistanceEvaluationBackend::FP32,
                                distance_evaluations);
    }
}
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L377 | matmul | 函数本体；短路求值/提前返回见源码 | [matmul · L40](gno_imi_partition.md#L40) |

| L377 | data_centroids_s_.data | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L377 | dist_to_s.data | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L378 | matmul | 函数本体；短路求值/提前返回见源码 | [matmul · L40](gno_imi_partition.md#L40) |

| L378 | data_centroids_t_.data | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L378 | dist_to_t.data | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L386 | FP32ComputeIP | for_statement@385 i &lt; count | 当前参考未静态绑定；见下方边界说明 |

| L393 | std::sort | for_statement@385 i &lt; count | 当前参考未静态绑定；见下方边界说明 |

| L393 | precomputed_terms_s.begin | for_statement@385 i &lt; count | 当前参考未静态绑定；见下方边界说明 |

| L393 | precomputed_terms_s.end | for_statement@385 i &lt; count | 当前参考未静态绑定；见下方边界说明 |

| L402 | heap.size | for_statement@385 i &lt; count → for_statement@396 j &lt; bucket_count_s_ → for_statement@400 k &lt; bucket_count_t_ → if_statement@402 (heap.size() &gt;= buckets_per_data && std::sqrt(cur_precomputed_term_s) - std::sqrt(norms_t_[cur_bucket_id_t]) &gt; std::sqrt(heap.top().first)) | 当前参考未静态绑定；见下方边界说明 |

| L403 | std::sqrt | for_statement@385 i &lt; count → for_statement@396 j &lt; bucket_count_s_ → for_statement@400 k &lt; bucket_count_t_ → if_statement@402 (heap.size() &gt;= buckets_per_data && std::sqrt(cur_precomputed_term_s) - std::sqrt(norms_t_[cur_bucket_id_t]) &gt; std::sqrt(heap.top().first)) | 当前参考未静态绑定；见下方边界说明 |

| L403 | std::sqrt | for_statement@385 i &lt; count → for_statement@396 j &lt; bucket_count_s_ → for_statement@400 k &lt; bucket_count_t_ → if_statement@402 (heap.size() &gt;= buckets_per_data && std::sqrt(cur_precomputed_term_s) - std::sqrt(norms_t_[cur_bucket_id_t]) &gt; std::sqrt(heap.top().first)) | 当前参考未静态绑定；见下方边界说明 |

| L404 | std::sqrt | for_statement@385 i &lt; count → for_statement@396 j &lt; bucket_count_s_ → for_statement@400 k &lt; bucket_count_t_ → if_statement@402 (heap.size() &gt;= buckets_per_data && std::sqrt(cur_precomputed_term_s) - std::sqrt(norms_t_[cur_bucket_id_t]) &gt; std::sqrt(heap.top().first)) | 当前参考未静态绑定；见下方边界说明 |

| L404 | heap.top | for_statement@385 i &lt; count → for_statement@396 j &lt; bucket_count_s_ → for_statement@400 k &lt; bucket_count_t_ → if_statement@402 (heap.size() &gt;= buckets_per_data && std::sqrt(cur_precomputed_term_s) - std::sqrt(norms_t_[cur_bucket_id_t]) &gt; std::sqrt(heap.top().first)) | 当前参考未静态绑定；见下方边界说明 |

| L414 | heap.size | for_statement@385 i &lt; count → for_statement@396 j &lt; bucket_count_s_ → for_statement@400 k &lt; bucket_count_t_ → if_statement@414 (heap.size() &lt; buckets_per_data &#124;&#124; dist &lt; heap.top().first) | 当前参考未静态绑定；见下方边界说明 |

| L414 | heap.top | for_statement@385 i &lt; count → for_statement@396 j &lt; bucket_count_s_ → for_statement@400 k &lt; bucket_count_t_ → if_statement@414 (heap.size() &lt; buckets_per_data &#124;&#124; dist &lt; heap.top().first) | 当前参考未静态绑定；见下方边界说明 |

| L415 | heap.emplace | for_statement@385 i &lt; count → for_statement@396 j &lt; bucket_count_s_ → for_statement@400 k &lt; bucket_count_t_ → if_statement@414 (heap.size() &lt; buckets_per_data &#124;&#124; dist &lt; heap.top().first) | 当前参考未静态绑定；见下方边界说明 |

| L417 | heap.size | for_statement@385 i &lt; count → for_statement@396 j &lt; bucket_count_s_ → for_statement@400 k &lt; bucket_count_t_ → if_statement@417 (heap.size() &gt; buckets_per_data) | 当前参考未静态绑定；见下方边界说明 |

| L418 | heap.pop | for_statement@385 i &lt; count → for_statement@396 j &lt; bucket_count_s_ → for_statement@400 k &lt; bucket_count_t_ → if_statement@417 (heap.size() &gt; buckets_per_data) | 当前参考未静态绑定；见下方边界说明 |

| L424 | heap.top | for_statement@385 i &lt; count → for_statement@423 j &gt;= 0 | 当前参考未静态绑定；见下方边界说明 |

| L426 | heap.top | for_statement@385 i &lt; count → for_statement@423 j &gt;= 0 → if_statement@425 (j == 0) | 当前参考未静态绑定；见下方边界说明 |

| L428 | heap.pop | for_statement@385 i &lt; count → for_statement@423 j &gt;= 0 | 当前参考未静态绑定；见下方边界说明 |

| L433 | ctx-&gt;stats-&gt;dist_cmp.fetch_add | if_statement@432 (ctx != nullptr and ctx-&gt;stats != nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L434 | ctx-&gt;stats-&gt;AddDistance | if_statement@432 (ctx != nullptr and ctx-&gt;stats != nullptr) | 当前参考未静态绑定；见下方边界说明 |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L440"></a>

## `GNOIMIPartition::GetCentroid`

源码位置：`src/algorithm/ivf/gno_imi_partition.cpp:440–454`。

先从签名确认输入、返回值和 const/override，再按完整函数体的条件阅读调用点。下表保留了本函数的显式调用以及 lambda 中的调用；进入下层时用“候选实现”定位，未解析的对象由源码静态类型/运行时类型确认。

### 完整函数

```cpp
void
GNOIMIPartition::GetCentroid(BucketIdType bucket_id, Vector<float>& centroid) {
    if (!is_trained_) {
        throw VsagException(ErrorType::WRONG_STATUS, "Partition not trained");
    }
    if (bucket_id >= bucket_count_) {
        throw VsagException(ErrorType::INVALID_ARGUMENT, "Invalid bucket_id");
    }
    auto bucket_id_s = bucket_id / bucket_count_t_;
    auto bucket_id_t = bucket_id % bucket_count_t_;
    FP32Add(data_centroids_s_.data() + bucket_id_s * dim_,
            data_centroids_t_.data() + bucket_id_t * dim_,
            centroid.data(),
            dim_);
}
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L443 | VsagException | if_statement@442 (!is_trained_) | 当前参考未静态绑定；见下方边界说明 |

| L446 | VsagException | if_statement@445 (bucket_id &gt;= bucket_count_) | 当前参考未静态绑定；见下方边界说明 |

| L450 | FP32Add | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L450 | data_centroids_s_.data | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L451 | data_centroids_t_.data | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L452 | centroid.data | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。
