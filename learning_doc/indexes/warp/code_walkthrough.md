# WARP：代码逐段导读

[直观图解](visual_guide.md)

[返回设计说明](README.md) · [所有索引](../README.md)

源码基线：`fd363937`。下面引用真实源码，不将摘录伪装为独立可编译程序。完整实现还包含未展示的检查和分支，请结合链接阅读。

从工厂开始追踪，可以看清一个独立入口怎样复用另一种算法。评分公式直接从 MultiVectorComputer 的双循环推导。

## 1. 工厂只切换内部模式

源码：[src/factory/index_creators.cpp](../../../src/factory/index_creators.cpp)，基线行号 106–115。以下为连续原文摘录，可能是函数的一部分。

```cpp

tl::expected<std::shared_ptr<Index>, Error>
create_warp_index(JsonType& parsed_params, const IndexCommonParam& index_common_params) {
    // WARP is now implemented as BruteForce with multi-vector data cell
    logger::debug("created a warp index (via BruteForce multi-vector mode)");
    auto index_param = get_index_param_or_empty(parsed_params);
    // Inject a hidden marker so BruteForce::CheckAndMappingExternalParam knows this is WARP
    index_param[WARP_MODE_MARKER].SetBool(true);
    return {std::make_shared<IndexImpl<BruteForce>>(index_param, index_common_params)};
}
```

工厂取得 index_param，注入内部 WARP_MODE_MARKER，再创建 IndexImpl<BruteForce>。具体模式映射稍后才发生。该标记用于内部装配，不需要业务代码自行设置。

## 2. BruteForce 识别并删除标记

源码：[src/algorithm/bruteforce/bruteforce.cpp](../../../src/algorithm/bruteforce/bruteforce.cpp)，基线行号 1189–1224。以下为连续原文摘录，可能是函数的一部分。

```cpp
BruteForce::CheckAndMappingExternalParam(const JsonType& external_param,
                                         const IndexCommonParam& common_param) {
    // Detect if this is a WARP (multi-vector) index request
    bool is_warp = external_param.Contains(WARP_MODE_MARKER);

    if (is_warp) {
        // Remove the marker key before mapping (it would cause "invalid config param" error)
        JsonType warp_external_param = external_param;
        warp_external_param.Erase(WARP_MODE_MARKER);

        if (common_param.data_type_ == DataTypes::DATA_TYPE_INT8) {
            throw VsagException(ErrorType::INVALID_ARGUMENT,
                                fmt::format("WARP not support {} datatype", DATATYPE_INT8));
        }

        auto inner_json = build_default_brute_force_param(warp_external_param, true);
        for (const auto& [key, value] : warp_external_param.GetInnerJson()->items()) {
            (void)value;
            auto field = warp_external_param[key];
            if (key == RESIZE_INCREASE_COUNT_BIT) {
                inner_json[RESIZE_INCREASE_COUNT_BIT].SetJson(field);
            } else if (key == BRUTE_FORCE_BASE_QUANTIZATION_TYPE) {
                inner_json[BASE_CODES_KEY][QUANTIZATION_PARAMS_KEY][TYPE_KEY].SetJson(field);
            } else if (key == BRUTE_FORCE_BASE_IO_TYPE) {
                inner_json[BASE_CODES_KEY][IO_PARAMS_KEY][TYPE_KEY].SetJson(field);
            } else if (key == BRUTE_FORCE_BASE_FILE_PATH) {
                inner_json[BASE_CODES_KEY][IO_PARAMS_KEY][IO_FILE_PATH_KEY].SetJson(field);
            } else {
                throw VsagException(ErrorType::INVALID_ARGUMENT,
                                    fmt::format("invalid config param: {}", key));
            }
        }

        auto brute_force_parameter = std::make_shared<BruteForceParameter>();
        brute_force_parameter->FromJson(inner_json);
        return brute_force_parameter;
```

Contains 检测模式后先复制并 Erase 标记，否则未知参数检查会拒绝它；build_default_brute_force_param(..., true) 选择多向量默认结构。这里 WARP 参数白名单比普通 BruteForce 不同，不能认为其全部选项原样通用。

## 3. 训练收集的是所有 token

源码：[src/algorithm/bruteforce/bruteforce.cpp](../../../src/algorithm/bruteforce/bruteforce.cpp)，基线行号 102–132。以下为连续原文摘录，可能是函数的一部分。

```cpp
BruteForce::train_multi_vector(const DatasetPtr& data) {
    const MultiVector* multi_vectors = data->GetMultiVectors();
    CHECK_ARGUMENT(multi_vectors != nullptr, "data.multi_vectors is nullptr");
    int64_t mv_dim = data->GetMultiVectorDim();
    CHECK_ARGUMENT(
        mv_dim == dim_,
        fmt::format("data.multi_vector_dim({}) must be equal to index.dim({})", mv_dim, dim_));
    int64_t num_elements = data->GetNumElements();
    uint64_t total_vectors = 0;
    for (int64_t i = 0; i < num_elements; ++i) {
        total_vectors += multi_vectors[i].len_;
    }
    Vector<float> buffer(total_vectors * mv_dim, allocator_);
    uint64_t offset = 0;
    for (int64_t i = 0; i < num_elements; ++i) {
        uint64_t num_floats = static_cast<uint64_t>(multi_vectors[i].len_) * mv_dim;
        std::memcpy(buffer.data() + offset, multi_vectors[i].vectors_, num_floats * sizeof(float));
        offset += num_floats;
    }
    this->inner_codes_->Train(buffer.data(), total_vectors);
}

void
BruteForce::Train(const DatasetPtr& data) {
    if (is_multi_vector_) {
        this->train_multi_vector(data);
    } else {
        this->inner_codes_->Train(data->GetFloat32Vectors(), data->GetNumElements());
    }
}

```

遍历文档累加 len_，将每篇文档的 len_×dim 个浮点数拷到训练缓冲。训练样本单位是 token 向量，而最终检索结果单位是文档。数据大时，这个扁平化临时缓冲也会增加峰值内存。

## 4. Computer 由记录类型决定

源码：[src/algorithm/bruteforce/bruteforce.cpp](../../../src/algorithm/bruteforce/bruteforce.cpp)，基线行号 663–670。以下为连续原文摘录，可能是函数的一部分。

```cpp
BruteForce::make_search_computer(const DatasetPtr& query) const {
    if (is_multi_vector_) {
        const MultiVector* query_multi_vectors = query->GetMultiVectors();
        CHECK_ARGUMENT(query_multi_vectors != nullptr, "query.multi_vectors is nullptr");
        return this->inner_codes_->FactoryComputer(&query_multi_vectors[0]);
    }
    return this->inner_codes_->FactoryComputer(query->GetFloat32Vectors());
}
```

多向量查询将第一篇 query 文档的 MultiVector 交给 FactoryComputer，单向量则传 FP32 数组。外层 SearchWithRequest 扫描 ID 与维护堆的代码因此可以复用。

## 5. 从双循环推导 MaxSim 距离

源码：[src/quantization/multi_vector_computer.cpp](../../../src/quantization/multi_vector_computer.cpp)，基线行号 49–89。以下为连续原文摘录，可能是函数的一部分。

```cpp
MultiVectorComputer::ComputeDist(const uint8_t* codes, uint32_t token_count, float* dist) const {
    const auto* doc_tokens = reinterpret_cast<const float*>(codes);
    float total = 0.0F;

    if (metric_ == MetricType::METRIC_TYPE_IP) {
        for (uint32_t q = 0; q < query_token_count_; ++q) {
            const float* q_tok = query_tokens_.data() + static_cast<uint64_t>(q) * dim_;
            float min_dist = std::numeric_limits<float>::max();

            for (uint32_t d = 0; d < token_count; ++d) {
                const float* d_tok = doc_tokens + static_cast<uint64_t>(d) * dim_;
                float dist_val = 1.0F - FP32ComputeIP(q_tok, d_tok, dim_);
                if (dist_val < min_dist) {
                    min_dist = dist_val;
                }
            }

            total += min_dist;
        }
    } else if (metric_ == MetricType::METRIC_TYPE_L2SQR) {
        for (uint32_t q = 0; q < query_token_count_; ++q) {
            const float* q_tok = query_tokens_.data() + static_cast<uint64_t>(q) * dim_;
            float min_dist = std::numeric_limits<float>::max();

            for (uint32_t d = 0; d < token_count; ++d) {
                const float* d_tok = doc_tokens + static_cast<uint64_t>(d) * dim_;
                float dist_val = FP32ComputeL2Sqr(q_tok, d_tok, dim_);
                if (dist_val < min_dist) {
                    min_dist = dist_val;
                }
            }

            total += min_dist;
        }
    } else {
        throw VsagException(ErrorType::INVALID_ARGUMENT,
                            "unsupported metric type for MultiVectorComputer");
    }

    *dist = total;
}
```

IP 分支外层枚举 query token，内层枚举同一文档的 token，并取 `1-IP` 的最小值；之后对 query token 累加。对 m 个 query token，结果是 m-MaxSim，不是 1-MaxSim。L2 分支则累加各 query token 的最小平方 L2 距离，不能继续用 IP 的公式解释。该函数处理编码后的计算视图，调用者仍需保证 token 数和指针合法。

## 读完以后应能解释

WARP 与 BruteForce 在哪里分叉，又在哪里复用？为什么 token 数影响返回距离常数？为什么最终 heap 中存的是文档 ID 而不是 token ID？
