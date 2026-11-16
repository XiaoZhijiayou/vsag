# ivf_build.cpp：逐函数完整源码与调用点

[主讲解](../code_walkthrough.md) · [函数总目录](README.md)

源码：[ src/algorithm/ivf/ivf_build.cpp ](../../../../src/algorithm/ivf/ivf_build.cpp)。基线 `fd363937`。以下源码函数体完整保留；调用点表是语法树中的显式调用表达式，按源码位置排列，不代表 C++ 参数求值顺序。表中“候选实现”需结合类型和参数选分支，不能将同名函数全部视为必经路径。

- [IVF::InitFeatures · L38](ivf_build.md#L38)

- [IVF::Build · L104](ivf_build.md#L104)

- [IVF::Train · L120](ivf_build.md#L120)

- [IVF::Add · L146](ivf_build.md#L146)

- [PairwiseBucketDistanceProvider::PairwiseBucketDistanceProvider · L284](ivf_build.md#L284)

- [PairwiseBucketDistanceProvider::QueryDistance · L290](ivf_build.md#L290)

- [PairwiseBucketDistanceProvider::BatchQueryDistance · L295](ivf_build.md#L295)

- [PairwiseBucketDistanceProvider::PairwiseDistance · L305](ivf_build.md#L305)

- [PairwiseBucketDistanceProvider::FactoryComputerById · L312](ivf_build.md#L312)

- [IVF::build_bucket_graphs · L324](ivf_build.md#L324)

- [IVF::fill_location_map · L405](ivf_build.md#L405)

- [IVF::RebuildBucketGraphs · L442](ivf_build.md#L442)


<a id="L38"></a>

## `IVF::InitFeatures`

源码位置：`src/algorithm/ivf/ivf_build.cpp:38–102`。

先从签名确认输入、返回值和 const/override，再按完整函数体的条件阅读调用点。下表保留了本函数的显式调用以及 lambda 中的调用；进入下层时用“候选实现”定位，未解析的对象由源码静态类型/运行时类型确认。

### 完整函数

```cpp
void
IVF::InitFeatures() {
    // Common Init
    // Build & Add
    this->index_feature_list_->SetFeatures({
        IndexFeature::SUPPORT_BUILD,
        IndexFeature::SUPPORT_ADD_AFTER_BUILD,
        IndexFeature::SUPPORT_ADD_CONCURRENT,
    });

    // search
    this->index_feature_list_->SetFeatures({
        IndexFeature::SUPPORT_KNN_SEARCH,
        IndexFeature::SUPPORT_KNN_SEARCH_WITH_ID_FILTER,
    });
    // concurrency
    this->index_feature_list_->SetFeature(IndexFeature::SUPPORT_SEARCH_CONCURRENT);

    // serialize
    this->index_feature_list_->SetFeatures({
        IndexFeature::SUPPORT_DESERIALIZE_BINARY_SET,
        IndexFeature::SUPPORT_DESERIALIZE_FILE,
        IndexFeature::SUPPORT_DESERIALIZE_READER_SET,
        IndexFeature::SUPPORT_SERIALIZE_BINARY_SET,
        IndexFeature::SUPPORT_SERIALIZE_FILE,
        IndexFeature::SUPPORT_SERIALIZE_WRITE_FUNC,
    });

    auto name = this->bucket_->GetQuantizerName();
    if (name != QUANTIZATION_TYPE_VALUE_FP32 and name != QUANTIZATION_TYPE_VALUE_BF16 and
        name != QUANTIZATION_TYPE_VALUE_FP16) {
        this->index_feature_list_->SetFeature(IndexFeature::NEED_TRAIN);
    } else {
        this->index_feature_list_->SetFeatures({
            IndexFeature::SUPPORT_RANGE_SEARCH,
            IndexFeature::SUPPORT_RANGE_SEARCH_WITH_ID_FILTER,
        });
    }

    bool has_fp32 = false;
    if (use_reorder_) {
        const auto precise_quantizer_name = precise_bucket_ != nullptr
                                                ? precise_bucket_->GetQuantizerName()
                                                : reorder_codes_->GetQuantizerName();
        has_fp32 = precise_quantizer_name == QUANTIZATION_TYPE_VALUE_FP32;
    }
    if (name == QUANTIZATION_TYPE_VALUE_FP32 or has_fp32) {
        this->index_feature_list_->SetFeature(IndexFeature::SUPPORT_CAL_DISTANCE_BY_ID);
        this->index_feature_list_->SetFeature(IndexFeature::SUPPORT_BATCH_CALC_DISTANCE_BY_ID);
    }

    if (name == QUANTIZATION_TYPE_VALUE_FP32 and
        this->bucket_->GetMetricType() != MetricType::METRIC_TYPE_COSINE and
        not bucket_->UseResidual()) {
        this->index_feature_list_->SetFeature(IndexFeature::SUPPORT_GET_DATA_BY_IDS);
    }

    this->index_feature_list_->SetFeatures({IndexFeature::SUPPORT_CLONE,
                                            IndexFeature::SUPPORT_EXPORT_MODEL,
                                            IndexFeature::SUPPORT_GET_MEMORY_USAGE,
                                            IndexFeature::SUPPORT_MERGE_INDEX});
    if (this->bucket_->GetQuantizerName() == QUANTIZATION_TYPE_VALUE_PQFS) {
        this->index_feature_list_->SetFeature(IndexFeature::SUPPORT_ADD_AFTER_BUILD, false);
    }
}
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L42 | this-&gt;index_feature_list_-&gt;SetFeatures | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L49 | this-&gt;index_feature_list_-&gt;SetFeatures | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L54 | this-&gt;index_feature_list_-&gt;SetFeature | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L57 | this-&gt;index_feature_list_-&gt;SetFeatures | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L66 | this-&gt;bucket_-&gt;GetQuantizerName | 函数本体；短路求值/提前返回见源码 | [BucketDataCell::GetQuantizerName · L170](bucket_datacell_h.md#L170) |

| L69 | this-&gt;index_feature_list_-&gt;SetFeature | if_statement@67 (name != QUANTIZATION_TYPE_VALUE_FP32 and name != QUANTIZATION_TYPE_VALUE_BF16 and name != QUANTIZATION_TYPE_VALUE_FP16) | 当前参考未静态绑定；见下方边界说明 |

| L71 | this-&gt;index_feature_list_-&gt;SetFeatures | if_statement@67 (name != QUANTIZATION_TYPE_VALUE_FP32 and name != QUANTIZATION_TYPE_VALUE_BF16 and name != QUANTIZATION_TYPE_VALUE_FP16) [else 分支] | 当前参考未静态绑定；见下方边界说明 |

| L80 | precise_bucket_-&gt;GetQuantizerName | if_statement@78 (use_reorder_) → conditional_expression@79 precise_bucket_ != nullptr | [BucketDataCell::GetQuantizerName · L170](bucket_datacell_h.md#L170) |

| L81 | reorder_codes_-&gt;GetQuantizerName | if_statement@78 (use_reorder_) → conditional_expression@79 precise_bucket_ != nullptr | 当前参考未静态绑定；见下方边界说明 |

| L85 | this-&gt;index_feature_list_-&gt;SetFeature | if_statement@84 (name == QUANTIZATION_TYPE_VALUE_FP32 or has_fp32) | 当前参考未静态绑定；见下方边界说明 |

| L86 | this-&gt;index_feature_list_-&gt;SetFeature | if_statement@84 (name == QUANTIZATION_TYPE_VALUE_FP32 or has_fp32) | 当前参考未静态绑定；见下方边界说明 |

| L90 | this-&gt;bucket_-&gt;GetMetricType | if_statement@89 (name == QUANTIZATION_TYPE_VALUE_FP32 and this-&gt;bucket_-&gt;GetMetricType() != MetricType::METRIC_TYPE_COSINE and not bucket_-&gt;UseResidual()) | [BucketDataCell::GetMetricType · L175](bucket_datacell_h.md#L175) |

| L91 | bucket_-&gt;UseResidual | if_statement@89 (name == QUANTIZATION_TYPE_VALUE_FP32 and this-&gt;bucket_-&gt;GetMetricType() != MetricType::METRIC_TYPE_COSINE and not bucket_-&gt;UseResidual()) | 当前参考未静态绑定；见下方边界说明 |

| L92 | this-&gt;index_feature_list_-&gt;SetFeature | if_statement@89 (name == QUANTIZATION_TYPE_VALUE_FP32 and this-&gt;bucket_-&gt;GetMetricType() != MetricType::METRIC_TYPE_COSINE and not bucket_-&gt;UseResidual()) | 当前参考未静态绑定；见下方边界说明 |

| L95 | this-&gt;index_feature_list_-&gt;SetFeatures | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L99 | this-&gt;bucket_-&gt;GetQuantizerName | if_statement@99 (this-&gt;bucket_-&gt;GetQuantizerName() == QUANTIZATION_TYPE_VALUE_PQFS) | [BucketDataCell::GetQuantizerName · L170](bucket_datacell_h.md#L170) |

| L100 | this-&gt;index_feature_list_-&gt;SetFeature | if_statement@99 (this-&gt;bucket_-&gt;GetQuantizerName() == QUANTIZATION_TYPE_VALUE_PQFS) | 当前参考未静态绑定；见下方边界说明 |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L104"></a>

## `IVF::Build`

源码位置：`src/algorithm/ivf/ivf_build.cpp:104–118`。

输入是基础 Dataset，返回 Add 的失败 ID 列表。先训练，后 Add，再按条件建桶图和统计内存。启用桶图时要求空索引；这些调用是顺序发生的兄弟帧。

### 完整函数

```cpp
std::vector<int64_t>
IVF::Build(const DatasetPtr& base) {
    if (graph_build_threshold_ > 0) {
        CHECK_ARGUMENT(this->total_elements_ == 0,
                       "graph bucket searcher requires a fresh Build with no prior data");
    }
    this->Train(base);
    // TODO(LHT): duplicate
    auto result = this->Add(base);
    if (graph_build_threshold_ > 0) {
        this->build_bucket_graphs();
    }
    this->cal_memory_usage();
    return result;
}
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L107 | CHECK_ARGUMENT | if_statement@106 (graph_build_threshold_ &gt; 0) | 当前参考未静态绑定；见下方边界说明 |

| L110 | this-&gt;Train | 函数本体；短路求值/提前返回见源码 | [IVF::Train · L120](ivf_build.md#L120) |

| L112 | this-&gt;Add | 函数本体；短路求值/提前返回见源码 | [IVF::Add · L146](ivf_build.md#L146) |

| L114 | this-&gt;build_bucket_graphs | if_statement@113 (graph_build_threshold_ &gt; 0) | [IVF::build_bucket_graphs · L324](ivf_build.md#L324) |

| L116 | this-&gt;cal_memory_usage | 函数本体；短路求值/提前返回见源码 | [IVF::cal_memory_usage · L616](ivf.md#L616) |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L120"></a>

## `IVF::Train`

源码位置：`src/algorithm/ivf/ivf_build.cpp:120–144`。

这是状态改变函数。先看重复训练的提前返回，再看训练数据是否采样/归一化/变成残差，最后确认状态位在何处设置。分区 Train 与量化器 Train 不是同一个模型。

### 完整函数

```cpp
void
IVF::Train(const DatasetPtr& data) {
    if (this->is_trained_) {
        return;
    }

    int64_t total_elements = data->GetNumElements();
    int64_t dim = data->GetDim();
    DatasetPtr train_data =
        vsag::sample_train_data(data, total_elements, dim, train_sample_count_, allocator_);
    int64_t sample_count = train_data->GetNumElements();

    partition_strategy_->Train(train_data);

    const auto* data_ptr = train_data->GetFloat32Vectors();
    this->bucket_->Train(data_ptr, sample_count);
    if (use_reorder_) {
        if (precise_bucket_ != nullptr) {
            this->precise_bucket_->Train(data->GetFloat32Vectors(), data->GetNumElements());
        } else {
            this->reorder_codes_->Train(data->GetFloat32Vectors(), data->GetNumElements());
        }
    }
    this->is_trained_ = true;
}
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L126 | data-&gt;GetNumElements | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L127 | data-&gt;GetDim | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L129 | vsag::sample_train_data | 函数本体；短路求值/提前返回见源码 | [sample_train_data · L234](util_functions.md#L234) |

| L130 | train_data-&gt;GetNumElements | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L132 | partition_strategy_-&gt;Train | 函数本体；短路求值/提前返回见源码 | [GNOIMIPartition::Train · L88](gno_imi_partition.md#L88)；[IVFNearestPartition::Train · L91](ivf_nearest_partition.md#L91) |

| L134 | train_data-&gt;GetFloat32Vectors | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L135 | this-&gt;bucket_-&gt;Train | 函数本体；短路求值/提前返回见源码 | [BucketDataCell&lt;QuantTmpl, IOTmpl&gt;::Train · L586](bucket_datacell_h.md#L586) |

| L138 | this-&gt;precise_bucket_-&gt;Train | if_statement@136 (use_reorder_) → if_statement@137 (precise_bucket_ != nullptr) | [BucketDataCell&lt;QuantTmpl, IOTmpl&gt;::Train · L586](bucket_datacell_h.md#L586) |

| L138 | data-&gt;GetFloat32Vectors | if_statement@136 (use_reorder_) → if_statement@137 (precise_bucket_ != nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L138 | data-&gt;GetNumElements | if_statement@136 (use_reorder_) → if_statement@137 (precise_bucket_ != nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L140 | this-&gt;reorder_codes_-&gt;Train | if_statement@136 (use_reorder_) → if_statement@137 (precise_bucket_ != nullptr) [else 分支] | [IVF::Train · L120](ivf_build.md#L120) |

| L140 | data-&gt;GetFloat32Vectors | if_statement@136 (use_reorder_) → if_statement@137 (precise_bucket_ != nullptr) [else 分支] | 当前参考未静态绑定；见下方边界说明 |

| L140 | data-&gt;GetNumElements | if_statement@136 (use_reorder_) → if_statement@137 (precise_bucket_ != nullptr) [else 分支] | 当前参考未静态绑定；见下方边界说明 |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L146"></a>

## `IVF::Add`

源码位置：`src/algorithm/ivf/ivf_build.cpp:146–280`。

输入向量先分类，再分配 origin ID、写精排存储和基础 posting。重点追踪 add_func 捕获变量、异步任务的等待、异常再抛出以及 Package 的位置。详解见主讲解第 7 节。

### 完整函数

```cpp
std::vector<int64_t>
IVF::Add(const DatasetPtr& base) {
    // TODO(LHT): duplicate
    if (not partition_strategy_->is_trained_) {
        throw VsagException(ErrorType::INTERNAL_ERROR, "ivf index add without train error");
    }
    this->bucket_->Unpack();
    if (precise_bucket_ != nullptr) {
        this->precise_bucket_->Unpack();
    }
    auto num_element = base->GetNumElements();
    const auto* ids = base->GetIds();
    const auto* vectors = base->GetFloat32Vectors();
    const auto* attr_sets = base->GetAttributeSets();
    const auto* extra_info = base->GetExtraInfos();
    const auto extra_info_size = base->GetExtraInfoSize();
    auto buckets =
        partition_strategy_->ClassifyDatas(vectors, num_element, buckets_per_data_, nullptr);

    int64_t current_num;
    bool need_cal_memory_usage = false;
    {
        std::lock_guard lock(label_lookup_mutex_);
        current_num = this->total_elements_;
        if (precise_bucket_ != nullptr) {
            if (num_element < 0 or current_num < 0) {
                throw VsagException(ErrorType::INVALID_ARGUMENT,
                                    "invalid IVF precise bucket element count");
            }
            const auto posting_count = static_cast<uint64_t>(num_element);
            const auto current_count = static_cast<uint64_t>(current_num);
            const auto max_inner_id =
                static_cast<uint64_t>(std::numeric_limits<InnerIdType>::max());
            if (posting_count > max_inner_id or current_count > max_inner_id - posting_count) {
                throw VsagException(ErrorType::INVALID_ARGUMENT,
                                    "IVF precise bucket batch exceeds inner id capacity");
            }
        }
        if (use_reorder_ and precise_bucket_ == nullptr) {
            this->reorder_codes_->BatchInsertVector(base->GetFloat32Vectors(),
                                                    base->GetNumElements());
        }
        for (int64_t i = 0; i < num_element; ++i) {
            this->label_table_->Insert(i + total_elements_, ids[i]);
        }
        this->total_elements_ += num_element;
        if (this->total_elements_ - last_cal_memory_element_ >= cal_memory_element_interval_) {
            need_cal_memory_usage = true;
            last_cal_memory_element_ = this->total_elements_;
        }
        location_map_.resize(this->total_elements_);
    }

    Vector<InnerIdType> precise_offsets(allocator_);
    if (precise_bucket_ != nullptr) {
        const auto posting_count = static_cast<uint64_t>(num_element);
        Vector<InnerIdType> posting_ids(posting_count, allocator_);
        precise_offsets.resize(posting_count);
        for (uint64_t i = 0; i < posting_count; ++i) {
            posting_ids[i] = static_cast<InnerIdType>(i + static_cast<uint64_t>(current_num));
        }
        precise_bucket_->BatchInsertVector(vectors,
                                           buckets.data(),
                                           posting_ids.data(),
                                           static_cast<InnerIdType>(posting_count),
                                           precise_offsets.data());
    }

    auto add_func = [&](int64_t i) -> void {
        for (int64_t j = 0; j < buckets_per_data_; ++j) {
            const auto* data_ptr = vectors + i * dim_;
            auto idx = i * buckets_per_data_ + j;
            auto posting_id = static_cast<InnerIdType>(idx + current_num * buckets_per_data_);
            InnerIdType offset_id;
            if (precise_bucket_ != nullptr) {
                // Publish the basic posting only after its precise mirror is ready.
                offset_id = precise_offsets[idx];
                bucket_->InsertVectorWithOffset(data_ptr, buckets[idx], posting_id, offset_id);
            } else {
                offset_id = bucket_->InsertVector(data_ptr, buckets[idx], posting_id);
            }
            if (j == 0) {
                std::lock_guard lock(label_lookup_mutex_);
                location_map_[i + current_num] =
                    (static_cast<uint64_t>(buckets[idx]) << LOCATION_SPLIT_BIT) |
                    static_cast<uint64_t>(offset_id);
            }
            if (use_attribute_filter_ and this->attr_filter_index_ != nullptr and
                attr_sets != nullptr) {
                const auto& attr_set = attr_sets[i];
                this->attr_filter_index_->Insert(attr_set, offset_id, buckets[idx]);
            }
            if (extra_info_size > 0) {
                this->extra_infos_->InsertExtraInfo(extra_info + i * extra_info_size,
                                                    i + current_num);
            }
        }
    };
    std::vector<std::future<void>> futures;
    std::exception_ptr first_exception = nullptr;
    try {
        for (int64_t i = 0; i < num_element; ++i) {
            if (this->thread_pool_ != nullptr) {
                futures.emplace_back(thread_pool_->GeneralEnqueue(add_func, i));
            } else {
                add_func(i);
            }
        }
    } catch (...) {
        first_exception = std::current_exception();
    }

    if (this->thread_pool_ != nullptr) {
        for (auto& future : futures) {
            try {
                future.get();
            } catch (...) {
                if (first_exception == nullptr) {
                    first_exception = std::current_exception();
                }
            }
        }
    }
    if (first_exception != nullptr) {
        std::rethrow_exception(first_exception);
    }
    this->bucket_->Package();
    if (precise_bucket_ != nullptr) {
        this->precise_bucket_->Package();
    }
    if (need_cal_memory_usage) {
        this->cal_memory_usage();
    }
    return {};
}
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L150 | VsagException | if_statement@149 (not partition_strategy_-&gt;is_trained_) | 当前参考未静态绑定；见下方边界说明 |

| L152 | this-&gt;bucket_-&gt;Unpack | 函数本体；短路求值/提前返回见源码 | [BucketDataCell::Unpack · L139](bucket_datacell_h.md#L139) |

| L154 | this-&gt;precise_bucket_-&gt;Unpack | if_statement@153 (precise_bucket_ != nullptr) | [BucketDataCell::Unpack · L139](bucket_datacell_h.md#L139) |

| L156 | base-&gt;GetNumElements | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L157 | base-&gt;GetIds | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L158 | base-&gt;GetFloat32Vectors | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L159 | base-&gt;GetAttributeSets | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L160 | base-&gt;GetExtraInfos | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L161 | base-&gt;GetExtraInfoSize | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L163 | partition_strategy_-&gt;ClassifyDatas | 函数本体；短路求值/提前返回见源码 | [GNOIMIPartition::ClassifyDatas · L201](gno_imi_partition.md#L201)；[IVFNearestPartition::ClassifyDatas · L157](ivf_nearest_partition.md#L157) |

| L172 | VsagException | if_statement@170 (precise_bucket_ != nullptr) → if_statement@171 (num_element &lt; 0 or current_num &lt; 0) | 当前参考未静态绑定；见下方边界说明 |

| L178 | std::numeric_limits&lt;InnerIdType&gt;::max | if_statement@170 (precise_bucket_ != nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L180 | VsagException | if_statement@170 (precise_bucket_ != nullptr) → if_statement@179 (posting_count &gt; max_inner_id or current_count &gt; max_inner_id - posting_count) | 当前参考未静态绑定；见下方边界说明 |

| L185 | this-&gt;reorder_codes_-&gt;BatchInsertVector | if_statement@184 (use_reorder_ and precise_bucket_ == nullptr) | [BucketDataCell&lt;QuantTmpl, IOTmpl&gt;::BatchInsertVector · L703](bucket_datacell_h.md#L703) |

| L185 | base-&gt;GetFloat32Vectors | if_statement@184 (use_reorder_ and precise_bucket_ == nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L186 | base-&gt;GetNumElements | if_statement@184 (use_reorder_ and precise_bucket_ == nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L189 | this-&gt;label_table_-&gt;Insert | for_statement@188 i &lt; num_element | 当前参考未静态绑定；见下方边界说明 |

| L196 | location_map_.resize | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L203 | precise_offsets.resize | if_statement@200 (precise_bucket_ != nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L207 | precise_bucket_-&gt;BatchInsertVector | if_statement@200 (precise_bucket_ != nullptr) | [BucketDataCell&lt;QuantTmpl, IOTmpl&gt;::BatchInsertVector · L703](bucket_datacell_h.md#L703) |

| L208 | buckets.data | if_statement@200 (precise_bucket_ != nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L209 | posting_ids.data | if_statement@200 (precise_bucket_ != nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L211 | precise_offsets.data | if_statement@200 (precise_bucket_ != nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L223 | bucket_-&gt;InsertVectorWithOffset | lambda@214（定义体，执行时间取决于调用/调度） → for_statement@215 j &lt; buckets_per_data_ → if_statement@220 (precise_bucket_ != nullptr) | [BucketDataCell&lt;QuantTmpl, IOTmpl&gt;::InsertVectorWithOffset · L818](bucket_datacell_h.md#L818) |

| L225 | bucket_-&gt;InsertVector | lambda@214（定义体，执行时间取决于调用/调度） → for_statement@215 j &lt; buckets_per_data_ → if_statement@220 (precise_bucket_ != nullptr) [else 分支] | [BucketDataCell&lt;QuantTmpl, IOTmpl&gt;::InsertVector · L660](bucket_datacell_h.md#L660) |

| L236 | this-&gt;attr_filter_index_-&gt;Insert | lambda@214（定义体，执行时间取决于调用/调度） → for_statement@215 j &lt; buckets_per_data_ → if_statement@233 (use_attribute_filter_ and this-&gt;attr_filter_index_ != nullptr and attr_sets != nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L239 | this-&gt;extra_infos_-&gt;InsertExtraInfo | lambda@214（定义体，执行时间取决于调用/调度） → for_statement@215 j &lt; buckets_per_data_ → if_statement@238 (extra_info_size &gt; 0) | 当前参考未静态绑定；见下方边界说明 |

| L249 | futures.emplace_back | for_statement@247 i &lt; num_element → if_statement@248 (this-&gt;thread_pool_ != nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L249 | thread_pool_-&gt;GeneralEnqueue | for_statement@247 i &lt; num_element → if_statement@248 (this-&gt;thread_pool_ != nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L251 | add_func | for_statement@247 i &lt; num_element → if_statement@248 (this-&gt;thread_pool_ != nullptr) [else 分支] | 当前参考未静态绑定；见下方边界说明 |

| L255 | std::current_exception | catch_clause@254 | 当前参考未静态绑定；见下方边界说明 |

| L261 | future.get | if_statement@258 (this-&gt;thread_pool_ != nullptr) → for_range_loop@259 | 当前参考未静态绑定；见下方边界说明 |

| L264 | std::current_exception | if_statement@258 (this-&gt;thread_pool_ != nullptr) → for_range_loop@259 → catch_clause@262 → if_statement@263 (first_exception == nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L270 | std::rethrow_exception | if_statement@269 (first_exception != nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L272 | this-&gt;bucket_-&gt;Package | 函数本体；短路求值/提前返回见源码 | [BucketDataCell::Package · L132](bucket_datacell_h.md#L132) |

| L274 | this-&gt;precise_bucket_-&gt;Package | if_statement@273 (precise_bucket_ != nullptr) | [BucketDataCell::Package · L132](bucket_datacell_h.md#L132) |

| L277 | this-&gt;cal_memory_usage | if_statement@276 (need_cal_memory_usage) | [IVF::cal_memory_usage · L616](ivf.md#L616) |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L284"></a>

## `PairwiseBucketDistanceProvider::PairwiseBucketDistanceProvider`

源码位置：`src/algorithm/ivf/ivf_build.cpp:284–288`。

先从签名确认输入、返回值和 const/override，再按完整函数体的条件阅读调用点。下表保留了本函数的显式调用以及 lambda 中的调用；进入下层时用“候选实现”定位，未解析的对象由源码静态类型/运行时类型确认。

### 完整函数

```cpp
PairwiseBucketDistanceProvider(std::shared_ptr<BucketInterface> bucket,
                                   BucketIdType bucket_id,
                                   InnerIdType query_id)
        : bucket_(std::move(bucket)), bucket_id_(bucket_id), query_id_(query_id) {
    }
```

### 函数内部调用点：不省略标准库和辅助调用

此函数体没有显式函数调用表达式。赋值、成员初始化和隐式操作请看上面的完整源码。


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L290"></a>

## `PairwiseBucketDistanceProvider::QueryDistance`

源码位置：`src/algorithm/ivf/ivf_build.cpp:290–293`。

先从签名确认输入、返回值和 const/override，再按完整函数体的条件阅读调用点。下表保留了本函数的显式调用以及 lambda 中的调用；进入下层时用“候选实现”定位，未解析的对象由源码静态类型/运行时类型确认。

### 完整函数

```cpp
[[nodiscard]] float
    QueryDistance(InnerIdType id, QueryContext* ctx = nullptr) const override {
        return bucket_->ComputePairVectors(bucket_id_, query_id_, id);
    }
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L292 | bucket_-&gt;ComputePairVectors | 函数本体；短路求值/提前返回见源码 | [BucketDataCell&lt;QuantTmpl, IOTmpl&gt;::ComputePairVectors · L1035](bucket_datacell_h.md#L1035) |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L295"></a>

## `PairwiseBucketDistanceProvider::BatchQueryDistance`

源码位置：`src/algorithm/ivf/ivf_build.cpp:295–303`。

先从签名确认输入、返回值和 const/override，再按完整函数体的条件阅读调用点。下表保留了本函数的显式调用以及 lambda 中的调用；进入下层时用“候选实现”定位，未解析的对象由源码静态类型/运行时类型确认。

### 完整函数

```cpp
void
    BatchQueryDistance(float* distances,
                       const InnerIdType* ids,
                       InnerIdType count,
                       QueryContext* ctx = nullptr) const override {
        for (InnerIdType i = 0; i < count; ++i) {
            distances[i] = bucket_->ComputePairVectors(bucket_id_, query_id_, ids[i]);
        }
    }
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L301 | bucket_-&gt;ComputePairVectors | for_statement@300 i &lt; count | [BucketDataCell&lt;QuantTmpl, IOTmpl&gt;::ComputePairVectors · L1035](bucket_datacell_h.md#L1035) |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L305"></a>

## `PairwiseBucketDistanceProvider::PairwiseDistance`

源码位置：`src/algorithm/ivf/ivf_build.cpp:305–310`。

先从签名确认输入、返回值和 const/override，再按完整函数体的条件阅读调用点。下表保留了本函数的显式调用以及 lambda 中的调用；进入下层时用“候选实现”定位，未解析的对象由源码静态类型/运行时类型确认。

### 完整函数

```cpp
[[nodiscard]] float
    PairwiseDistance(InnerIdType id1,
                     InnerIdType id2,
                     const ComputerInterfacePtr& computer = nullptr) const override {
        return bucket_->ComputePairVectors(bucket_id_, id1, id2);
    }
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L309 | bucket_-&gt;ComputePairVectors | 函数本体；短路求值/提前返回见源码 | [BucketDataCell&lt;QuantTmpl, IOTmpl&gt;::ComputePairVectors · L1035](bucket_datacell_h.md#L1035) |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L312"></a>

## `PairwiseBucketDistanceProvider::FactoryComputerById`

源码位置：`src/algorithm/ivf/ivf_build.cpp:312–316`。

先从签名确认输入、返回值和 const/override，再按完整函数体的条件阅读调用点。下表保留了本函数的显式调用以及 lambda 中的调用；进入下层时用“候选实现”定位，未解析的对象由源码静态类型/运行时类型确认。

### 完整函数

```cpp
[[nodiscard]] ComputerInterfacePtr
    FactoryComputerById(InnerIdType id) const override {
        throw VsagException(ErrorType::UNSUPPORTED_INDEX_OPERATION,
                            "PairwiseBucketDistanceProvider does not support FactoryComputerById");
    }
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L314 | VsagException | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L324"></a>

## `IVF::build_bucket_graphs`

源码位置：`src/algorithm/ivf/ivf_build.cpp:324–404`。

以桶为独立任务，收集有效 local IDs。逐节点搜已有图并互连，节点间距离由 PairwiseBucketDistanceProvider 提供。没有达到阈值的桶不建图。

### 完整函数

```cpp
void
IVF::build_bucket_graphs() {
    if (graph_build_threshold_ <= 0) {
        return;
    }
    if (graph_param_ == nullptr) {
        graph_param_ = std::make_shared<GraphDataCellParameter>();
    }

    constexpr int64_t max_degree = 64;
    constexpr uint64_t ef_construction = 300;
    const auto bucket_count = bucket_->bucket_count_;
    bucket_graphs_.resize(bucket_count);

    auto build_one_bucket = [&](BucketIdType b) {
        const auto bucket_size = bucket_->GetBucketSize(b);
        if (bucket_size < graph_build_threshold_) {
            return;
        }

        const auto* inner_ids = bucket_->GetInnerIds(b);
        Vector<InnerIdType> valid_ids(allocator_);
        valid_ids.reserve(bucket_size);
        for (InnerIdType i = 0; i < static_cast<InnerIdType>(bucket_size); ++i) {
            if (inner_ids[i] != std::numeric_limits<InnerIdType>::max()) {
                valid_ids.push_back(i);
            }
        }
        if (valid_ids.size() < static_cast<uint64_t>(graph_build_threshold_)) {
            return;
        }

        const auto effective_degree =
            std::min(max_degree, static_cast<int64_t>(valid_ids.size()) - 1);
        if (effective_degree <= 0) {
            return;
        }

        auto graph = GraphInterface::MakeInstance(graph_param_, this->common_param_);
        graph->Resize(bucket_size);
        graph->SetTotalCount(bucket_size);
        graph->SetMaximumDegree(static_cast<uint32_t>(effective_degree));

        auto mutexes = std::make_shared<EmptyMutex>();
        BasicSearcher searcher(common_param_);

        const auto entry = valid_ids.front();
        graph->InsertNeighborsById(entry, Vector<InnerIdType>(allocator_));
        auto visited = std::make_shared<VisitedList>(bucket_size, allocator_);
        for (uint64_t node_pos = 1; node_pos < valid_ids.size(); ++node_pos) {
            const auto node = valid_ids[node_pos];
            InnerSearchParam search_param;
            search_param.ep = entry;
            search_param.ef = std::min(ef_construction, node_pos);
            search_param.topk = static_cast<int64_t>(search_param.ef);
            PairwiseBucketDistanceProvider distance_provider(bucket_, b, node);
            visited->Reset();
            auto candidates =
                searcher.Search(graph, distance_provider, visited, search_param, nullptr, nullptr);
            mutually_connect_new_element(
                node, candidates, graph, distance_provider, mutexes, allocator_);
        }

        bucket_graphs_[b] = std::move(graph);
    };

    if (this->thread_pool_ != nullptr) {
        std::vector<std::future<void>> futures;
        futures.reserve(bucket_count);
        for (BucketIdType b = 0; b < bucket_count; ++b) {
            futures.emplace_back(this->thread_pool_->GeneralEnqueue(build_one_bucket, b));
        }
        for (auto& future : futures) {
            future.get();
        }
    } else {
        for (BucketIdType b = 0; b < bucket_count; ++b) {
            build_one_bucket(b);
        }
    }
}
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L330 | std::make_shared&lt;GraphDataCellParameter&gt; | if_statement@329 (graph_param_ == nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L336 | bucket_graphs_.resize | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L339 | bucket_-&gt;GetBucketSize | lambda@338（定义体，执行时间取决于调用/调度） | [BucketDataCell::GetBucketSize · L180](bucket_datacell_h.md#L180) |

| L344 | bucket_-&gt;GetInnerIds | lambda@338（定义体，执行时间取决于调用/调度） | [BucketDataCell::GetInnerIds · L120](bucket_datacell_h.md#L120) |

| L346 | valid_ids.reserve | lambda@338（定义体，执行时间取决于调用/调度） | 当前参考未静态绑定；见下方边界说明 |

| L348 | std::numeric_limits&lt;InnerIdType&gt;::max | lambda@338（定义体，执行时间取决于调用/调度） → for_statement@347 i &lt; static_cast&lt;InnerIdType&gt;(bucket_size) → if_statement@348 (inner_ids[i] != std::numeric_limits&lt;InnerIdType&gt;::max()) | 当前参考未静态绑定；见下方边界说明 |

| L349 | valid_ids.push_back | lambda@338（定义体，执行时间取决于调用/调度） → for_statement@347 i &lt; static_cast&lt;InnerIdType&gt;(bucket_size) → if_statement@348 (inner_ids[i] != std::numeric_limits&lt;InnerIdType&gt;::max()) | 当前参考未静态绑定；见下方边界说明 |

| L352 | valid_ids.size | lambda@338（定义体，执行时间取决于调用/调度） → if_statement@352 (valid_ids.size() &lt; static_cast&lt;uint64_t&gt;(graph_build_threshold_)) | 当前参考未静态绑定；见下方边界说明 |

| L357 | std::min | lambda@338（定义体，执行时间取决于调用/调度） | 当前参考未静态绑定；见下方边界说明 |

| L357 | valid_ids.size | lambda@338（定义体，执行时间取决于调用/调度） | 当前参考未静态绑定；见下方边界说明 |

| L362 | GraphInterface::MakeInstance | lambda@338（定义体，执行时间取决于调用/调度） | 当前参考未静态绑定；见下方边界说明 |

| L363 | graph-&gt;Resize | lambda@338（定义体，执行时间取决于调用/调度） | 当前参考未静态绑定；见下方边界说明 |

| L364 | graph-&gt;SetTotalCount | lambda@338（定义体，执行时间取决于调用/调度） | 当前参考未静态绑定；见下方边界说明 |

| L365 | graph-&gt;SetMaximumDegree | lambda@338（定义体，执行时间取决于调用/调度） | 当前参考未静态绑定；见下方边界说明 |

| L367 | std::make_shared&lt;EmptyMutex&gt; | lambda@338（定义体，执行时间取决于调用/调度） | 当前参考未静态绑定；见下方边界说明 |

| L370 | valid_ids.front | lambda@338（定义体，执行时间取决于调用/调度） | 当前参考未静态绑定；见下方边界说明 |

| L371 | graph-&gt;InsertNeighborsById | lambda@338（定义体，执行时间取决于调用/调度） | 当前参考未静态绑定；见下方边界说明 |

| L371 | Vector&lt;InnerIdType&gt; | lambda@338（定义体，执行时间取决于调用/调度） | 当前参考未静态绑定；见下方边界说明 |

| L372 | std::make_shared&lt;VisitedList&gt; | lambda@338（定义体，执行时间取决于调用/调度） | 当前参考未静态绑定；见下方边界说明 |

| L373 | valid_ids.size | lambda@338（定义体，执行时间取决于调用/调度） → for_statement@373 node_pos &lt; valid_ids.size() | 当前参考未静态绑定；见下方边界说明 |

| L377 | std::min | lambda@338（定义体，执行时间取决于调用/调度） → for_statement@373 node_pos &lt; valid_ids.size() | 当前参考未静态绑定；见下方边界说明 |

| L380 | visited-&gt;Reset | lambda@338（定义体，执行时间取决于调用/调度） → for_statement@373 node_pos &lt; valid_ids.size() | 当前参考未静态绑定；见下方边界说明 |

| L382 | searcher.Search | lambda@338（定义体，执行时间取决于调用/调度） → for_statement@373 node_pos &lt; valid_ids.size() | [BasicSearcher::Search · L76](basic_searcher.md#L76)；[BasicSearcher::Search · L139](basic_searcher.md#L139)；[BasicSearcher::Search · L158](basic_searcher.md#L158) |

| L383 | mutually_connect_new_element | lambda@338（定义体，执行时间取决于调用/调度） → for_statement@373 node_pos &lt; valid_ids.size() | 当前参考未静态绑定；见下方边界说明 |

| L387 | std::move | lambda@338（定义体，执行时间取决于调用/调度） | 当前参考未静态绑定；见下方边界说明 |

| L392 | futures.reserve | if_statement@390 (this-&gt;thread_pool_ != nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L394 | futures.emplace_back | if_statement@390 (this-&gt;thread_pool_ != nullptr) → for_statement@393 b &lt; bucket_count | 当前参考未静态绑定；见下方边界说明 |

| L394 | this-&gt;thread_pool_-&gt;GeneralEnqueue | if_statement@390 (this-&gt;thread_pool_ != nullptr) → for_statement@393 b &lt; bucket_count | 当前参考未静态绑定；见下方边界说明 |

| L397 | future.get | if_statement@390 (this-&gt;thread_pool_ != nullptr) → for_range_loop@396 | 当前参考未静态绑定；见下方边界说明 |

| L401 | build_one_bucket | if_statement@390 (this-&gt;thread_pool_ != nullptr) [else 分支] → for_statement@400 b &lt; bucket_count | 当前参考未静态绑定；见下方边界说明 |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L405"></a>

## `IVF::fill_location_map`

源码位置：`src/algorithm/ivf/ivf_build.cpp:405–440`。

通过桶 posting 数组重建 origin→bucket/offset 映射，并校验基础/精排桶镜像的一致性。跳过无效 posting，不能把空槽当作记录。

### 完整函数

```cpp
void
IVF::fill_location_map() {
    this->location_map_.resize(this->total_elements_ * buckets_per_data_);
    auto bucket_count = this->bucket_->bucket_count_;
    if (precise_bucket_ != nullptr and precise_bucket_->GetBucketCount() != bucket_count) {
        throw VsagException(ErrorType::INTERNAL_ERROR,
                            "basic and precise bucket counts do not match");
    }
    for (BucketIdType i = 0; i < bucket_count; ++i) {
        auto* ids = this->bucket_->GetInnerIds(i);
        auto bucket_size = this->bucket_->GetBucketSize(i);
        InnerIdType* precise_ids = nullptr;
        if (precise_bucket_ != nullptr) {
            auto precise_bucket_size = precise_bucket_->GetBucketSize(i);
            if (precise_bucket_size != bucket_size) {
                throw VsagException(ErrorType::INTERNAL_ERROR,
                                    "basic and precise bucket sizes do not match");
            }
            precise_ids = precise_bucket_->GetInnerIds(i);
        }
        for (uint64_t j = 0; j < bucket_size; ++j) {
            if (precise_ids != nullptr and precise_ids[j] != ids[j]) {
                throw VsagException(ErrorType::INTERNAL_ERROR,
                                    "basic and precise bucket inner ids do not match");
            }
            if (ids[j] == std::numeric_limits<InnerIdType>::max()) {
                continue;
            }
            if (ids[j] >= this->total_elements_ * buckets_per_data_) {
                throw VsagException(ErrorType::INTERNAL_ERROR, "invalid inner_id");
            }
            this->location_map_[ids[j] / buckets_per_data_] =
                (static_cast<uint64_t>(i) << LOCATION_SPLIT_BIT) | static_cast<uint64_t>(j);
        }
    }
}
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L407 | this-&gt;location_map_.resize | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L409 | precise_bucket_-&gt;GetBucketCount | if_statement@409 (precise_bucket_ != nullptr and precise_bucket_-&gt;GetBucketCount() != bucket_count) | 当前参考未静态绑定；见下方边界说明 |

| L410 | VsagException | if_statement@409 (precise_bucket_ != nullptr and precise_bucket_-&gt;GetBucketCount() != bucket_count) | 当前参考未静态绑定；见下方边界说明 |

| L414 | this-&gt;bucket_-&gt;GetInnerIds | for_statement@413 i &lt; bucket_count | [BucketDataCell::GetInnerIds · L120](bucket_datacell_h.md#L120) |

| L415 | this-&gt;bucket_-&gt;GetBucketSize | for_statement@413 i &lt; bucket_count | [BucketDataCell::GetBucketSize · L180](bucket_datacell_h.md#L180) |

| L418 | precise_bucket_-&gt;GetBucketSize | for_statement@413 i &lt; bucket_count → if_statement@417 (precise_bucket_ != nullptr) | [BucketDataCell::GetBucketSize · L180](bucket_datacell_h.md#L180) |

| L420 | VsagException | for_statement@413 i &lt; bucket_count → if_statement@417 (precise_bucket_ != nullptr) → if_statement@419 (precise_bucket_size != bucket_size) | 当前参考未静态绑定；见下方边界说明 |

| L423 | precise_bucket_-&gt;GetInnerIds | for_statement@413 i &lt; bucket_count → if_statement@417 (precise_bucket_ != nullptr) | [BucketDataCell::GetInnerIds · L120](bucket_datacell_h.md#L120) |

| L427 | VsagException | for_statement@413 i &lt; bucket_count → for_statement@425 j &lt; bucket_size → if_statement@426 (precise_ids != nullptr and precise_ids[j] != ids[j]) | 当前参考未静态绑定；见下方边界说明 |

| L430 | std::numeric_limits&lt;InnerIdType&gt;::max | for_statement@413 i &lt; bucket_count → for_statement@425 j &lt; bucket_size → if_statement@430 (ids[j] == std::numeric_limits&lt;InnerIdType&gt;::max()) | 当前参考未静态绑定；见下方边界说明 |

| L434 | VsagException | for_statement@413 i &lt; bucket_count → for_statement@425 j &lt; bucket_size → if_statement@433 (ids[j] &gt;= this-&gt;total_elements_ * buckets_per_data_) | 当前参考未静态绑定；见下方边界说明 |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L442"></a>

## `IVF::RebuildBucketGraphs`

源码位置：`src/algorithm/ivf/ivf_build.cpp:442–466`。

检查特性和数据类型，然后暂存旧图，创建新图。异常分支恢复旧图容器并重新抛出；这是明确存在的恢复逻辑，不能推广为 Add 的事务保证。

### 完整函数

```cpp
void
IVF::RebuildBucketGraphs() {
    if (graph_build_threshold_ <= 0) {
        throw VsagException(
            ErrorType::UNSUPPORTED_INDEX_OPERATION,
            "RebuildIVFBucketGraphs: index was not configured with graph_build_threshold > 0");
    }
    if (common_param_.data_type_ != DataTypes::DATA_TYPE_FLOAT) {
        throw VsagException(ErrorType::UNSUPPORTED_INDEX_OPERATION,
                            "RebuildIVFBucketGraphs: only supports float32 data type");
    }

    // Build new graphs in temp storage first (exception safety)
    auto old_graphs = std::move(bucket_graphs_);
    bucket_graphs_.resize(old_graphs.size(), nullptr);

    try {
        this->build_bucket_graphs();
        this->cal_memory_usage();
    } catch (...) {
        // Restore old graphs on failure
        bucket_graphs_ = std::move(old_graphs);
        throw;
    }
}
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L445 | VsagException | if_statement@444 (graph_build_threshold_ &lt;= 0) | 当前参考未静态绑定；见下方边界说明 |

| L450 | VsagException | if_statement@449 (common_param_.data_type_ != DataTypes::DATA_TYPE_FLOAT) | 当前参考未静态绑定；见下方边界说明 |

| L455 | std::move | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L456 | bucket_graphs_.resize | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L456 | old_graphs.size | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L459 | this-&gt;build_bucket_graphs | 函数本体；短路求值/提前返回见源码 | [IVF::build_bucket_graphs · L324](ivf_build.md#L324) |

| L460 | this-&gt;cal_memory_usage | 函数本体；短路求值/提前返回见源码 | [IVF::cal_memory_usage · L616](ivf.md#L616) |

| L463 | std::move | catch_clause@461 | 当前参考未静态绑定；见下方边界说明 |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。
