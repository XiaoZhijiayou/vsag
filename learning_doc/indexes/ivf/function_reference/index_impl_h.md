# index_impl.h：逐函数完整源码与调用点

[主讲解](../code_walkthrough.md) · [函数总目录](README.md)

源码：[ src/index/index_impl.h ](../../../../src/index/index_impl.h)。基线 `fd363937`。以下源码函数体完整保留；调用点表是语法树中的显式调用表达式，按源码位置排列，不代表 C++ 参数求值顺序。表中“候选实现”需结合类型和参数选分支，不能将同名函数全部视为必经路径。

- [IndexImpl::Build · L94](index_impl_h.md#L94)

- [IndexImpl::KnnSearch · L308](index_impl_h.md#L308)

- [IndexImpl::KnnSearch · L324](index_impl_h.md#L324)

- [IndexImpl::KnnSearch · L340](index_impl_h.md#L340)

- [IndexImpl::KnnSearch · L356](index_impl_h.md#L356)

- [IndexImpl::KnnSearch · L380](index_impl_h.md#L380)

- [IndexImpl::SearchWithRequest · L505](index_impl_h.md#L505)


<a id="L94"></a>

## `IndexImpl::Build`

源码位置：`src/index/index_impl.h:94–99`。

输入是基础 Dataset，返回 Add 的失败 ID 列表。先训练，后 Add，再按条件建桶图和统计内存。启用桶图时要求空索引；这些调用是顺序发生的兄弟帧。

### 完整函数

```cpp
tl::expected<std::vector<int64_t>, Error>
    Build(const DatasetPtr& base) override {
        CHECK_IMMUTABLE_INDEX("build");
        CHECK_NONEMPTY_DATASET(base);
        SAFE_CALL(return this->inner_index_->Build(base));
    }
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L96 | CHECK_IMMUTABLE_INDEX | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L97 | CHECK_NONEMPTY_DATASET | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L308"></a>

## `IndexImpl::KnnSearch`

源码位置：`src/index/index_impl.h:308–322`。

先从签名确认输入、返回值和 const/override，再按完整函数体的条件阅读调用点。下表保留了本函数的显式调用以及 lambda 中的调用；进入下层时用“候选实现”定位，未解析的对象由源码静态类型/运行时类型确认。

### 完整函数

```cpp
tl::expected<DatasetPtr, Error>
    KnnSearch(const DatasetPtr& query,
              int64_t k,
              const std::string& parameters,
              BitsetPtr invalid = nullptr) const override {
        auto threshold_validation = ValidateThresholdParameters(parameters);
        if (not threshold_validation.has_value()) {
            return tl::unexpected(threshold_validation.error());
        }
        CHECK_QUERY_RETURN_EMPTY_DATASET(query);
        if (GetNumElements() == 0 && !this->ShouldSkipEmptyCheck(parameters)) {
            return make_empty_search_result();
        }
        SAFE_CALL(return this->inner_index_->KnnSearch(query, k, parameters, invalid));
    }
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L313 | ValidateThresholdParameters | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L314 | threshold_validation.has_value | if_statement@314 (not threshold_validation.has_value()) | 当前参考未静态绑定；见下方边界说明 |

| L315 | tl::unexpected | if_statement@314 (not threshold_validation.has_value()) | 当前参考未静态绑定；见下方边界说明 |

| L315 | threshold_validation.error | if_statement@314 (not threshold_validation.has_value()) | 当前参考未静态绑定；见下方边界说明 |

| L317 | CHECK_QUERY_RETURN_EMPTY_DATASET | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L318 | GetNumElements | if_statement@318 (GetNumElements() == 0 && !this-&gt;ShouldSkipEmptyCheck(parameters)) | [IVF::GetNumElements · L291](ivf.md#L291) |

| L318 | this-&gt;ShouldSkipEmptyCheck | if_statement@318 (GetNumElements() == 0 && !this-&gt;ShouldSkipEmptyCheck(parameters)) | 当前参考未静态绑定；见下方边界说明 |

| L319 | make_empty_search_result | if_statement@318 (GetNumElements() == 0 && !this-&gt;ShouldSkipEmptyCheck(parameters)) | 当前参考未静态绑定；见下方边界说明 |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L324"></a>

## `IndexImpl::KnnSearch`

源码位置：`src/index/index_impl.h:324–338`。

先从签名确认输入、返回值和 const/override，再按完整函数体的条件阅读调用点。下表保留了本函数的显式调用以及 lambda 中的调用；进入下层时用“候选实现”定位，未解析的对象由源码静态类型/运行时类型确认。

### 完整函数

```cpp
tl::expected<DatasetPtr, Error>
    KnnSearch(const DatasetPtr& query,
              int64_t k,
              const std::string& parameters,
              const std::function<bool(int64_t)>& filter) const override {
        auto threshold_validation = ValidateThresholdParameters(parameters);
        if (not threshold_validation.has_value()) {
            return tl::unexpected(threshold_validation.error());
        }
        CHECK_QUERY_RETURN_EMPTY_DATASET(query);
        if (GetNumElements() == 0 && !this->ShouldSkipEmptyCheck(parameters)) {
            return make_empty_search_result();
        }
        SAFE_CALL(return this->inner_index_->KnnSearch(query, k, parameters, filter));
    }
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L329 | ValidateThresholdParameters | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L330 | threshold_validation.has_value | if_statement@330 (not threshold_validation.has_value()) | 当前参考未静态绑定；见下方边界说明 |

| L331 | tl::unexpected | if_statement@330 (not threshold_validation.has_value()) | 当前参考未静态绑定；见下方边界说明 |

| L331 | threshold_validation.error | if_statement@330 (not threshold_validation.has_value()) | 当前参考未静态绑定；见下方边界说明 |

| L333 | CHECK_QUERY_RETURN_EMPTY_DATASET | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L334 | GetNumElements | if_statement@334 (GetNumElements() == 0 && !this-&gt;ShouldSkipEmptyCheck(parameters)) | [IVF::GetNumElements · L291](ivf.md#L291) |

| L334 | this-&gt;ShouldSkipEmptyCheck | if_statement@334 (GetNumElements() == 0 && !this-&gt;ShouldSkipEmptyCheck(parameters)) | 当前参考未静态绑定；见下方边界说明 |

| L335 | make_empty_search_result | if_statement@334 (GetNumElements() == 0 && !this-&gt;ShouldSkipEmptyCheck(parameters)) | 当前参考未静态绑定；见下方边界说明 |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L340"></a>

## `IndexImpl::KnnSearch`

源码位置：`src/index/index_impl.h:340–354`。

先从签名确认输入、返回值和 const/override，再按完整函数体的条件阅读调用点。下表保留了本函数的显式调用以及 lambda 中的调用；进入下层时用“候选实现”定位，未解析的对象由源码静态类型/运行时类型确认。

### 完整函数

```cpp
tl::expected<DatasetPtr, Error>
    KnnSearch(const DatasetPtr& query,
              int64_t k,
              const std::string& parameters,
              const FilterPtr& filter) const override {
        auto threshold_validation = ValidateThresholdParameters(parameters);
        if (not threshold_validation.has_value()) {
            return tl::unexpected(threshold_validation.error());
        }
        CHECK_QUERY_RETURN_EMPTY_DATASET(query);
        if (GetNumElements() == 0 && !this->ShouldSkipEmptyCheck(parameters)) {
            return make_empty_search_result();
        }
        SAFE_CALL(return this->inner_index_->KnnSearch(query, k, parameters, filter));
    }
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L345 | ValidateThresholdParameters | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L346 | threshold_validation.has_value | if_statement@346 (not threshold_validation.has_value()) | 当前参考未静态绑定；见下方边界说明 |

| L347 | tl::unexpected | if_statement@346 (not threshold_validation.has_value()) | 当前参考未静态绑定；见下方边界说明 |

| L347 | threshold_validation.error | if_statement@346 (not threshold_validation.has_value()) | 当前参考未静态绑定；见下方边界说明 |

| L349 | CHECK_QUERY_RETURN_EMPTY_DATASET | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L350 | GetNumElements | if_statement@350 (GetNumElements() == 0 && !this-&gt;ShouldSkipEmptyCheck(parameters)) | [IVF::GetNumElements · L291](ivf.md#L291) |

| L350 | this-&gt;ShouldSkipEmptyCheck | if_statement@350 (GetNumElements() == 0 && !this-&gt;ShouldSkipEmptyCheck(parameters)) | 当前参考未静态绑定；见下方边界说明 |

| L351 | make_empty_search_result | if_statement@350 (GetNumElements() == 0 && !this-&gt;ShouldSkipEmptyCheck(parameters)) | 当前参考未静态绑定；见下方边界说明 |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L356"></a>

## `IndexImpl::KnnSearch`

源码位置：`src/index/index_impl.h:356–622`。

先从签名确认输入、返回值和 const/override，再按完整函数体的条件阅读调用点。下表保留了本函数的显式调用以及 lambda 中的调用；进入下层时用“候选实现”定位，未解析的对象由源码静态类型/运行时类型确认。

### 完整函数

```cpp
tl::expected<DatasetPtr, Error>
    KnnSearch(const DatasetPtr& query, int64_t k, SearchParam& search_param) const override {
        auto threshold_validation = ValidateThresholdParameters(search_param.parameters);
        if (not threshold_validation.has_value()) {
            return tl::unexpected(threshold_validation.error());
        }
        CHECK_QUERY_RETURN_EMPTY_DATASET(query);
        if (GetNumElements() == 0 && !this->ShouldSkipEmptyCheck(search_param.parameters)) {
            return make_empty_search_result();
        }
        if (search_param.is_iter_filter) {
            SAFE_CALL(return this->inner_index_->KnnSearch(query,
                                                           k,
                                                           search_param.parameters,
                                                           search_param.filter,
                                                           search_param.allocator,
                                                           search_param.iter_ctx,
                                                           search_param.is_last_search));
        } else {
            SAFE_CALL(return this->inner_index_->KnnSearch(
                query, k, search_param.parameters, search_param.filter, search_param.allocator));
        }
    }

    tl::expected<DatasetPtr, Error>
    KnnSearch(const DatasetPtr& query,
              int64_t k,
              const std::string& parameters,
              const FilterPtr& filter,
              IteratorContext*& iter_ctx,
              bool is_last_filter) const override {
        auto threshold_validation = ValidateThresholdParameters(parameters);
        if (not threshold_validation.has_value()) {
            return tl::unexpected(threshold_validation.error());
        }
        CHECK_QUERY_RETURN_EMPTY_DATASET(query);
        if (GetNumElements() == 0 && !this->ShouldSkipEmptyCheck(parameters)) {
            return make_empty_search_result();
        }
        SAFE_CALL(return this->inner_index_->KnnSearch(
            query, k, parameters, filter, nullptr, iter_ctx, is_last_filter));
    }

    tl::expected<void, Error>
    Merge(const std::vector<MergeUnit>& merge_units) override {
        CHECK_IMMUTABLE_INDEX("merge");
        SAFE_CALL(this->inner_index_->Merge(merge_units));
    }

    tl::expected<uint32_t, Error>
    Pretrain(const std::vector<int64_t>& base_tag_ids,
             uint32_t k,
             const std::string& parameters) override {
        CHECK_IMMUTABLE_INDEX("pretrain");
        SAFE_CALL(return this->inner_index_->Pretrain(base_tag_ids, k, parameters));
    }

    tl::expected<uint32_t, Error>
    Feedback(const DatasetPtr& query,
             int64_t k,
             const std::string& parameters,
             int64_t global_optimum_tag_id = std::numeric_limits<int64_t>::max()) override {
        CHECK_IMMUTABLE_INDEX("feedback");
        if (query->GetNumElements() == 0) {
            return 0;
        }
        SAFE_CALL(return this->inner_index_->Feedback(query, k, parameters, global_optimum_tag_id));
    }

    [[nodiscard]] tl::expected<DatasetPtr, Error>
    RangeSearch(const DatasetPtr& query,
                float radius,
                const std::string& parameters,
                int64_t limited_size = -1) const override {
        CHECK_QUERY_RETURN_EMPTY_DATASET(query);
        if (GetNumElements() == 0 && !this->ShouldSkipEmptyCheck(parameters)) {
            return make_empty_search_result();
        }
        SAFE_CALL(return this->inner_index_->RangeSearch(query, radius, parameters, limited_size));
    }

    [[nodiscard]] tl::expected<DatasetPtr, Error>
    RangeSearch(const DatasetPtr& query,
                float radius,
                const std::string& parameters,
                BitsetPtr invalid,
                int64_t limited_size = -1) const override {
        CHECK_QUERY_RETURN_EMPTY_DATASET(query);
        if (GetNumElements() == 0 && !this->ShouldSkipEmptyCheck(parameters)) {
            return make_empty_search_result();
        }
        SAFE_CALL(return this->inner_index_->RangeSearch(
            query, radius, parameters, invalid, limited_size));
    }

    tl::expected<DatasetPtr, Error>
    RangeSearch(const DatasetPtr& query,
                float radius,
                const std::string& parameters,
                const std::function<bool(int64_t)>& filter,
                int64_t limited_size = -1) const override {
        CHECK_QUERY_RETURN_EMPTY_DATASET(query);
        if (GetNumElements() == 0 && !this->ShouldSkipEmptyCheck(parameters)) {
            return make_empty_search_result();
        }
        SAFE_CALL(return this->inner_index_->RangeSearch(
            query, radius, parameters, filter, limited_size));
    }

    tl::expected<DatasetPtr, Error>
    RangeSearch(const DatasetPtr& query,
                float radius,
                const std::string& parameters,
                const FilterPtr& filter,
                int64_t limited_size = -1) const override {
        CHECK_QUERY_RETURN_EMPTY_DATASET(query);
        if (GetNumElements() == 0 && !this->ShouldSkipEmptyCheck(parameters)) {
            return make_empty_search_result();
        }
        SAFE_CALL(return this->inner_index_->RangeSearch(
            query, radius, parameters, filter, limited_size));
    }

    tl::expected<uint32_t, Error>
    Remove(const std::vector<int64_t>& ids, RemoveMode mode = RemoveMode::MARK_REMOVE) override {
        CHECK_IMMUTABLE_INDEX("remove");
        SAFE_CALL(return this->inner_index_->Remove(ids, mode));
    }

    [[nodiscard]] tl::expected<BinarySet, Error>
    Serialize() const override {
        SAFE_CALL(return this->inner_index_->Serialize());
    }

    [[nodiscard]] tl::expected<void, Error>
    Serialize(WriteFuncType write_func) const override {
        SAFE_CALL(this->inner_index_->Serialize(write_func));
    }

    tl::expected<void, Error>
    Serialize(std::ostream& out_stream) override {
        SAFE_CALL(this->inner_index_->Serialize(out_stream));
    }

    tl::expected<void, Error>
    SerializeStreaming(std::ostream& out_stream) const override {
        SAFE_CALL(this->inner_index_->SerializeStreaming(out_stream));
    }

    [[nodiscard]] tl::expected<DatasetPtr, Error>
    SearchWithRequest(const SearchRequest& request) const override {
        // Validate bucket_ids_ structural constraints before empty-index early return
        if (not request.bucket_ids_.empty()) {
            if (request.query_ == nullptr) {
                return tl::unexpected(Error(ErrorType::INVALID_ARGUMENT,
                                            "query_ cannot be null when bucket_ids_ is set"));
            }
            if (request.bucket_ids_.size() !=
                static_cast<size_t>(request.query_->GetNumElements())) {
                return tl::unexpected(
                    Error(ErrorType::INVALID_ARGUMENT,
                          "bucket_ids_ size (" + std::to_string(request.bucket_ids_.size()) +
                              ") must match the number of query vectors (" +
                              std::to_string(request.query_->GetNumElements()) + ")"));
            }
            if (this->GetIndexType() != IndexType::IVF && request.bucket_ids_.size() != 1) {
                return tl::unexpected(
                    Error(ErrorType::INVALID_ARGUMENT,
                          "bucket_ids_ supports multiple query vectors only for IVF indexes"));
            }
            for (uint64_t query_idx = 0; query_idx < request.bucket_ids_.size(); ++query_idx) {
                const auto& ids = request.bucket_ids_[query_idx];
                if (ids.empty()) {
                    return tl::unexpected(
                        Error(ErrorType::INVALID_ARGUMENT,
                              "bucket_ids_[" + std::to_string(query_idx) +
                                  "] must not be empty; use an empty outer vector "
                                  "for default routing"));
                }
                std::set<int64_t> seen_ids;
                for (auto id : ids) {
                    if (id < 0) {
                        return tl::unexpected(
                            Error(ErrorType::INVALID_ARGUMENT,
                                  "bucket_id " + std::to_string(id) + " is negative"));
                    }
                    if (not seen_ids.insert(id).second) {
                        return tl::unexpected(Error(ErrorType::INVALID_ARGUMENT,
                                                    "duplicate bucket_id " + std::to_string(id)));
                    }
                }
            }
            try {
                auto json_params = nlohmann::json::parse(request.params_str_);
                if (json_params.contains("ivf") and
                    json_params["ivf"].contains("disable_bucket_scan") and
                    json_params["ivf"]["disable_bucket_scan"].get<bool>()) {
                    return tl::unexpected(
                        Error(ErrorType::INVALID_ARGUMENT,
                              "bucket_ids_ is incompatible with disable_bucket_scan mode"));
                }
            } catch (const nlohmann::json::exception&) {
            }
        }
        SAFE_CALL(ValidateSearchThreshold(request.threshold_);
                  if (GetNumElements() == 0 && !this->ShouldSkipEmptyCheck(request.params_str_)) {
                      return make_empty_search_result();
                  } return this->inner_index_->SearchWithRequest(request));
    }

    tl::expected<void, Error>
    SetImmutable() override {
        SAFE_CALL(this->inner_index_->SetImmutable());
    }

    tl::expected<void, Error>
    Train(const DatasetPtr& data) override {
        CHECK_IMMUTABLE_INDEX("train");
        if (data->GetNumElements() != 0) {
            SAFE_CALL(this->inner_index_->Train(data));
        }
        return {};
    }

    virtual tl::expected<void, Error>
    UpdateAttribute(int64_t id, const AttributeSet& new_attrs) override {
        CHECK_IMMUTABLE_INDEX("update attribute");
        SAFE_CALL(this->inner_index_->UpdateAttribute(id, new_attrs));
    }

    tl::expected<void, Error>
    UpdateAttribute(int64_t id,
                    const AttributeSet& new_attrs,
                    const AttributeSet& origin_attrs) override {
        CHECK_IMMUTABLE_INDEX("update attribute with origin attributes");
        SAFE_CALL(this->inner_index_->UpdateAttribute(id, new_attrs, origin_attrs));
    }

    virtual tl::expected<bool, Error>
    UpdateExtraInfo(const DatasetPtr& new_base) override {
        CHECK_IMMUTABLE_INDEX("update extra info");
        if (new_base->GetNumElements() == 0) {
            return false;
        }
        SAFE_CALL(return this->inner_index_->UpdateExtraInfo(new_base));
    }

    tl::expected<bool, Error>
    UpdateId(int64_t old_id, int64_t new_id) override {
        CHECK_IMMUTABLE_INDEX("update id");
        SAFE_CALL(return this->inner_index_->UpdateId(old_id, new_id));
    }

    tl::expected<bool, Error>
    UpdateVector(int64_t id, const DatasetPtr& new_base, bool force_update = false) override {
        CHECK_IMMUTABLE_INDEX("update vector");
        if (new_base->GetNumElements() == 0) {
            return false;
        }
        SAFE_CALL(return this->inner_index_->UpdateVector(id, new_base, force_update));
    }

public:
    [[nodiscard]] inline InnerIndexPtr
    GetInnerIndex() const {
        return this->inner_index_;
    }
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L358 | ValidateThresholdParameters | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L359 | threshold_validation.has_value | if_statement@359 (not threshold_validation.has_value()) | 当前参考未静态绑定；见下方边界说明 |

| L360 | tl::unexpected | if_statement@359 (not threshold_validation.has_value()) | 当前参考未静态绑定；见下方边界说明 |

| L360 | threshold_validation.error | if_statement@359 (not threshold_validation.has_value()) | 当前参考未静态绑定；见下方边界说明 |

| L362 | CHECK_QUERY_RETURN_EMPTY_DATASET | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L363 | GetNumElements | if_statement@363 (GetNumElements() == 0 && !this-&gt;ShouldSkipEmptyCheck(search_param.parameters)) | [IVF::GetNumElements · L291](ivf.md#L291) |

| L363 | this-&gt;ShouldSkipEmptyCheck | if_statement@363 (GetNumElements() == 0 && !this-&gt;ShouldSkipEmptyCheck(search_param.parameters)) | 当前参考未静态绑定；见下方边界说明 |

| L364 | make_empty_search_result | if_statement@363 (GetNumElements() == 0 && !this-&gt;ShouldSkipEmptyCheck(search_param.parameters)) | 当前参考未静态绑定；见下方边界说明 |

| L387 | ValidateThresholdParameters | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L388 | threshold_validation.has_value | if_statement@388 (not threshold_validation.has_value()) | 当前参考未静态绑定；见下方边界说明 |

| L389 | tl::unexpected | if_statement@388 (not threshold_validation.has_value()) | 当前参考未静态绑定；见下方边界说明 |

| L389 | threshold_validation.error | if_statement@388 (not threshold_validation.has_value()) | 当前参考未静态绑定；见下方边界说明 |

| L391 | CHECK_QUERY_RETURN_EMPTY_DATASET | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L392 | GetNumElements | if_statement@392 (GetNumElements() == 0 && !this-&gt;ShouldSkipEmptyCheck(parameters)) | [IVF::GetNumElements · L291](ivf.md#L291) |

| L392 | this-&gt;ShouldSkipEmptyCheck | if_statement@392 (GetNumElements() == 0 && !this-&gt;ShouldSkipEmptyCheck(parameters)) | 当前参考未静态绑定；见下方边界说明 |

| L393 | make_empty_search_result | if_statement@392 (GetNumElements() == 0 && !this-&gt;ShouldSkipEmptyCheck(parameters)) | 当前参考未静态绑定；见下方边界说明 |

| L401 | CHECK_IMMUTABLE_INDEX | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L402 | SAFE_CALL | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L402 | this-&gt;inner_index_-&gt;Merge | 函数本体；短路求值/提前返回见源码 | [IVF::Merge · L296](ivf.md#L296) |

| L409 | CHECK_IMMUTABLE_INDEX | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L417 | std::numeric_limits&lt;int64_t&gt;::max | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L418 | CHECK_IMMUTABLE_INDEX | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L419 | query-&gt;GetNumElements | if_statement@419 (query-&gt;GetNumElements() == 0) | 当前参考未静态绑定；见下方边界说明 |

| L430 | CHECK_QUERY_RETURN_EMPTY_DATASET | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L431 | GetNumElements | if_statement@431 (GetNumElements() == 0 && !this-&gt;ShouldSkipEmptyCheck(parameters)) | [IVF::GetNumElements · L291](ivf.md#L291) |

| L431 | this-&gt;ShouldSkipEmptyCheck | if_statement@431 (GetNumElements() == 0 && !this-&gt;ShouldSkipEmptyCheck(parameters)) | 当前参考未静态绑定；见下方边界说明 |

| L432 | make_empty_search_result | if_statement@431 (GetNumElements() == 0 && !this-&gt;ShouldSkipEmptyCheck(parameters)) | 当前参考未静态绑定；见下方边界说明 |

| L443 | CHECK_QUERY_RETURN_EMPTY_DATASET | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L444 | GetNumElements | if_statement@444 (GetNumElements() == 0 && !this-&gt;ShouldSkipEmptyCheck(parameters)) | [IVF::GetNumElements · L291](ivf.md#L291) |

| L444 | this-&gt;ShouldSkipEmptyCheck | if_statement@444 (GetNumElements() == 0 && !this-&gt;ShouldSkipEmptyCheck(parameters)) | 当前参考未静态绑定；见下方边界说明 |

| L445 | make_empty_search_result | if_statement@444 (GetNumElements() == 0 && !this-&gt;ShouldSkipEmptyCheck(parameters)) | 当前参考未静态绑定；见下方边界说明 |

| L457 | CHECK_QUERY_RETURN_EMPTY_DATASET | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L458 | GetNumElements | if_statement@458 (GetNumElements() == 0 && !this-&gt;ShouldSkipEmptyCheck(parameters)) | [IVF::GetNumElements · L291](ivf.md#L291) |

| L458 | this-&gt;ShouldSkipEmptyCheck | if_statement@458 (GetNumElements() == 0 && !this-&gt;ShouldSkipEmptyCheck(parameters)) | 当前参考未静态绑定；见下方边界说明 |

| L459 | make_empty_search_result | if_statement@458 (GetNumElements() == 0 && !this-&gt;ShouldSkipEmptyCheck(parameters)) | 当前参考未静态绑定；见下方边界说明 |

| L471 | CHECK_QUERY_RETURN_EMPTY_DATASET | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L472 | GetNumElements | if_statement@472 (GetNumElements() == 0 && !this-&gt;ShouldSkipEmptyCheck(parameters)) | [IVF::GetNumElements · L291](ivf.md#L291) |

| L472 | this-&gt;ShouldSkipEmptyCheck | if_statement@472 (GetNumElements() == 0 && !this-&gt;ShouldSkipEmptyCheck(parameters)) | 当前参考未静态绑定；见下方边界说明 |

| L473 | make_empty_search_result | if_statement@472 (GetNumElements() == 0 && !this-&gt;ShouldSkipEmptyCheck(parameters)) | 当前参考未静态绑定；见下方边界说明 |

| L481 | CHECK_IMMUTABLE_INDEX | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L492 | SAFE_CALL | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L492 | this-&gt;inner_index_-&gt;Serialize | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L497 | SAFE_CALL | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L497 | this-&gt;inner_index_-&gt;Serialize | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L502 | SAFE_CALL | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L502 | this-&gt;inner_index_-&gt;SerializeStreaming | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L508 | request.bucket_ids_.empty | if_statement@508 (not request.bucket_ids_.empty()) | 当前参考未静态绑定；见下方边界说明 |

| L510 | tl::unexpected | if_statement@508 (not request.bucket_ids_.empty()) → if_statement@509 (request.query_ == nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L510 | Error | if_statement@508 (not request.bucket_ids_.empty()) → if_statement@509 (request.query_ == nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L513 | request.bucket_ids_.size | if_statement@508 (not request.bucket_ids_.empty()) → if_statement@513 (request.bucket_ids_.size() != static_cast&lt;size_t&gt;(request.query_-&gt;GetNumElements())) | 当前参考未静态绑定；见下方边界说明 |

| L514 | request.query_-&gt;GetNumElements | if_statement@508 (not request.bucket_ids_.empty()) → if_statement@513 (request.bucket_ids_.size() != static_cast&lt;size_t&gt;(request.query_-&gt;GetNumElements())) | 当前参考未静态绑定；见下方边界说明 |

| L515 | tl::unexpected | if_statement@508 (not request.bucket_ids_.empty()) → if_statement@513 (request.bucket_ids_.size() != static_cast&lt;size_t&gt;(request.query_-&gt;GetNumElements())) | 当前参考未静态绑定；见下方边界说明 |

| L516 | Error | if_statement@508 (not request.bucket_ids_.empty()) → if_statement@513 (request.bucket_ids_.size() != static_cast&lt;size_t&gt;(request.query_-&gt;GetNumElements())) | 当前参考未静态绑定；见下方边界说明 |

| L517 | std::to_string | if_statement@508 (not request.bucket_ids_.empty()) → if_statement@513 (request.bucket_ids_.size() != static_cast&lt;size_t&gt;(request.query_-&gt;GetNumElements())) | 当前参考未静态绑定；见下方边界说明 |

| L517 | request.bucket_ids_.size | if_statement@508 (not request.bucket_ids_.empty()) → if_statement@513 (request.bucket_ids_.size() != static_cast&lt;size_t&gt;(request.query_-&gt;GetNumElements())) | 当前参考未静态绑定；见下方边界说明 |

| L519 | std::to_string | if_statement@508 (not request.bucket_ids_.empty()) → if_statement@513 (request.bucket_ids_.size() != static_cast&lt;size_t&gt;(request.query_-&gt;GetNumElements())) | 当前参考未静态绑定；见下方边界说明 |

| L519 | request.query_-&gt;GetNumElements | if_statement@508 (not request.bucket_ids_.empty()) → if_statement@513 (request.bucket_ids_.size() != static_cast&lt;size_t&gt;(request.query_-&gt;GetNumElements())) | 当前参考未静态绑定；见下方边界说明 |

| L521 | this-&gt;GetIndexType | if_statement@508 (not request.bucket_ids_.empty()) → if_statement@521 (this-&gt;GetIndexType() != IndexType::IVF && request.bucket_ids_.size() != 1) | [IVF::GetIndexType · L121](ivf_h.md#L121) |

| L521 | request.bucket_ids_.size | if_statement@508 (not request.bucket_ids_.empty()) → if_statement@521 (this-&gt;GetIndexType() != IndexType::IVF && request.bucket_ids_.size() != 1) | 当前参考未静态绑定；见下方边界说明 |

| L522 | tl::unexpected | if_statement@508 (not request.bucket_ids_.empty()) → if_statement@521 (this-&gt;GetIndexType() != IndexType::IVF && request.bucket_ids_.size() != 1) | 当前参考未静态绑定；见下方边界说明 |

| L523 | Error | if_statement@508 (not request.bucket_ids_.empty()) → if_statement@521 (this-&gt;GetIndexType() != IndexType::IVF && request.bucket_ids_.size() != 1) | 当前参考未静态绑定；见下方边界说明 |

| L526 | request.bucket_ids_.size | if_statement@508 (not request.bucket_ids_.empty()) → for_statement@526 query_idx &lt; request.bucket_ids_.size() | 当前参考未静态绑定；见下方边界说明 |

| L528 | ids.empty | if_statement@508 (not request.bucket_ids_.empty()) → for_statement@526 query_idx &lt; request.bucket_ids_.size() → if_statement@528 (ids.empty()) | 当前参考未静态绑定；见下方边界说明 |

| L529 | tl::unexpected | if_statement@508 (not request.bucket_ids_.empty()) → for_statement@526 query_idx &lt; request.bucket_ids_.size() → if_statement@528 (ids.empty()) | 当前参考未静态绑定；见下方边界说明 |

| L530 | Error | if_statement@508 (not request.bucket_ids_.empty()) → for_statement@526 query_idx &lt; request.bucket_ids_.size() → if_statement@528 (ids.empty()) | 当前参考未静态绑定；见下方边界说明 |

| L531 | std::to_string | if_statement@508 (not request.bucket_ids_.empty()) → for_statement@526 query_idx &lt; request.bucket_ids_.size() → if_statement@528 (ids.empty()) | 当前参考未静态绑定；见下方边界说明 |

| L538 | tl::unexpected | if_statement@508 (not request.bucket_ids_.empty()) → for_statement@526 query_idx &lt; request.bucket_ids_.size() → for_range_loop@536 → if_statement@537 (id &lt; 0) | 当前参考未静态绑定；见下方边界说明 |

| L539 | Error | if_statement@508 (not request.bucket_ids_.empty()) → for_statement@526 query_idx &lt; request.bucket_ids_.size() → for_range_loop@536 → if_statement@537 (id &lt; 0) | 当前参考未静态绑定；见下方边界说明 |

| L540 | std::to_string | if_statement@508 (not request.bucket_ids_.empty()) → for_statement@526 query_idx &lt; request.bucket_ids_.size() → for_range_loop@536 → if_statement@537 (id &lt; 0) | 当前参考未静态绑定；见下方边界说明 |

| L542 | seen_ids.insert | if_statement@508 (not request.bucket_ids_.empty()) → for_statement@526 query_idx &lt; request.bucket_ids_.size() → for_range_loop@536 → if_statement@542 (not seen_ids.insert(id).second) | 当前参考未静态绑定；见下方边界说明 |

| L543 | tl::unexpected | if_statement@508 (not request.bucket_ids_.empty()) → for_statement@526 query_idx &lt; request.bucket_ids_.size() → for_range_loop@536 → if_statement@542 (not seen_ids.insert(id).second) | 当前参考未静态绑定；见下方边界说明 |

| L543 | Error | if_statement@508 (not request.bucket_ids_.empty()) → for_statement@526 query_idx &lt; request.bucket_ids_.size() → for_range_loop@536 → if_statement@542 (not seen_ids.insert(id).second) | 当前参考未静态绑定；见下方边界说明 |

| L544 | std::to_string | if_statement@508 (not request.bucket_ids_.empty()) → for_statement@526 query_idx &lt; request.bucket_ids_.size() → for_range_loop@536 → if_statement@542 (not seen_ids.insert(id).second) | 当前参考未静态绑定；见下方边界说明 |

| L549 | nlohmann::json::parse | if_statement@508 (not request.bucket_ids_.empty()) | 当前参考未静态绑定；见下方边界说明 |

| L550 | json_params.contains | if_statement@508 (not request.bucket_ids_.empty()) → if_statement@550 (json_params.contains("ivf") and json_params["ivf"].contains("disable_bucket_scan") and json_params["ivf"]["disable_bucket_scan"].get&lt;bool&gt;()) | 当前参考未静态绑定；见下方边界说明 |

| L551 | json_params["ivf"].contains | if_statement@508 (not request.bucket_ids_.empty()) → if_statement@550 (json_params.contains("ivf") and json_params["ivf"].contains("disable_bucket_scan") and json_params["ivf"]["disable_bucket_scan"].get&lt;bool&gt;()) | 当前参考未静态绑定；见下方边界说明 |

| L552 | json_params["ivf"]["disable_bucket_scan"].get&lt;bool&gt; | if_statement@508 (not request.bucket_ids_.empty()) → if_statement@550 (json_params.contains("ivf") and json_params["ivf"].contains("disable_bucket_scan") and json_params["ivf"]["disable_bucket_scan"].get&lt;bool&gt;()) | 当前参考未静态绑定；见下方边界说明 |

| L553 | tl::unexpected | if_statement@508 (not request.bucket_ids_.empty()) → if_statement@550 (json_params.contains("ivf") and json_params["ivf"].contains("disable_bucket_scan") and json_params["ivf"]["disable_bucket_scan"].get&lt;bool&gt;()) | 当前参考未静态绑定；见下方边界说明 |

| L554 | Error | if_statement@508 (not request.bucket_ids_.empty()) → if_statement@550 (json_params.contains("ivf") and json_params["ivf"].contains("disable_bucket_scan") and json_params["ivf"]["disable_bucket_scan"].get&lt;bool&gt;()) | 当前参考未静态绑定；见下方边界说明 |

| L560 | SAFE_CALL | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L560 | ValidateSearchThreshold | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L561 | GetNumElements | if_statement@561 (GetNumElements() == 0 && !this-&gt;ShouldSkipEmptyCheck(request.params_str_)) | [IVF::GetNumElements · L291](ivf.md#L291) |

| L561 | this-&gt;ShouldSkipEmptyCheck | if_statement@561 (GetNumElements() == 0 && !this-&gt;ShouldSkipEmptyCheck(request.params_str_)) | 当前参考未静态绑定；见下方边界说明 |

| L562 | make_empty_search_result | if_statement@561 (GetNumElements() == 0 && !this-&gt;ShouldSkipEmptyCheck(request.params_str_)) | 当前参考未静态绑定；见下方边界说明 |

| L563 | this-&gt;inner_index_-&gt;SearchWithRequest | 函数本体；短路求值/提前返回见源码 | [IndexImpl::SearchWithRequest · L505](index_impl_h.md#L505) |

| L568 | SAFE_CALL | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L568 | this-&gt;inner_index_-&gt;SetImmutable | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L573 | CHECK_IMMUTABLE_INDEX | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L574 | data-&gt;GetNumElements | if_statement@574 (data-&gt;GetNumElements() != 0) | 当前参考未静态绑定；见下方边界说明 |

| L575 | SAFE_CALL | if_statement@574 (data-&gt;GetNumElements() != 0) | 当前参考未静态绑定；见下方边界说明 |

| L575 | this-&gt;inner_index_-&gt;Train | if_statement@574 (data-&gt;GetNumElements() != 0) | 当前参考未静态绑定；见下方边界说明 |

| L582 | CHECK_IMMUTABLE_INDEX | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L583 | SAFE_CALL | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L583 | this-&gt;inner_index_-&gt;UpdateAttribute | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L590 | CHECK_IMMUTABLE_INDEX | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L591 | SAFE_CALL | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L591 | this-&gt;inner_index_-&gt;UpdateAttribute | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L596 | CHECK_IMMUTABLE_INDEX | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L597 | new_base-&gt;GetNumElements | if_statement@597 (new_base-&gt;GetNumElements() == 0) | 当前参考未静态绑定；见下方边界说明 |

| L605 | CHECK_IMMUTABLE_INDEX | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L611 | CHECK_IMMUTABLE_INDEX | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L612 | new_base-&gt;GetNumElements | if_statement@612 (new_base-&gt;GetNumElements() == 0) | 当前参考未静态绑定；见下方边界说明 |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L380"></a>

## `IndexImpl::KnnSearch`

源码位置：`src/index/index_impl.h:380–397`。

先从签名确认输入、返回值和 const/override，再按完整函数体的条件阅读调用点。下表保留了本函数的显式调用以及 lambda 中的调用；进入下层时用“候选实现”定位，未解析的对象由源码静态类型/运行时类型确认。

### 完整函数

```cpp
tl::expected<DatasetPtr, Error>
    KnnSearch(const DatasetPtr& query,
              int64_t k,
              const std::string& parameters,
              const FilterPtr& filter,
              IteratorContext*& iter_ctx,
              bool is_last_filter) const override {
        auto threshold_validation = ValidateThresholdParameters(parameters);
        if (not threshold_validation.has_value()) {
            return tl::unexpected(threshold_validation.error());
        }
        CHECK_QUERY_RETURN_EMPTY_DATASET(query);
        if (GetNumElements() == 0 && !this->ShouldSkipEmptyCheck(parameters)) {
            return make_empty_search_result();
        }
        SAFE_CALL(return this->inner_index_->KnnSearch(
            query, k, parameters, filter, nullptr, iter_ctx, is_last_filter));
    }
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L387 | ValidateThresholdParameters | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L388 | threshold_validation.has_value | if_statement@388 (not threshold_validation.has_value()) | 当前参考未静态绑定；见下方边界说明 |

| L389 | tl::unexpected | if_statement@388 (not threshold_validation.has_value()) | 当前参考未静态绑定；见下方边界说明 |

| L389 | threshold_validation.error | if_statement@388 (not threshold_validation.has_value()) | 当前参考未静态绑定；见下方边界说明 |

| L391 | CHECK_QUERY_RETURN_EMPTY_DATASET | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L392 | GetNumElements | if_statement@392 (GetNumElements() == 0 && !this-&gt;ShouldSkipEmptyCheck(parameters)) | [IVF::GetNumElements · L291](ivf.md#L291) |

| L392 | this-&gt;ShouldSkipEmptyCheck | if_statement@392 (GetNumElements() == 0 && !this-&gt;ShouldSkipEmptyCheck(parameters)) | 当前参考未静态绑定；见下方边界说明 |

| L393 | make_empty_search_result | if_statement@392 (GetNumElements() == 0 && !this-&gt;ShouldSkipEmptyCheck(parameters)) | 当前参考未静态绑定；见下方边界说明 |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L505"></a>

## `IndexImpl::SearchWithRequest`

源码位置：`src/index/index_impl.h:505–564`。

按源码顺序先参数校验，再分离仅路由、批查询、属性/诊断、自定义距离、Range、KNN。每个提前 return 都终止当前分支。批查询的递归请求只有一条 query，不能无限展开成相同状态。

### 完整函数

```cpp
[[nodiscard]] tl::expected<DatasetPtr, Error>
    SearchWithRequest(const SearchRequest& request) const override {
        // Validate bucket_ids_ structural constraints before empty-index early return
        if (not request.bucket_ids_.empty()) {
            if (request.query_ == nullptr) {
                return tl::unexpected(Error(ErrorType::INVALID_ARGUMENT,
                                            "query_ cannot be null when bucket_ids_ is set"));
            }
            if (request.bucket_ids_.size() !=
                static_cast<size_t>(request.query_->GetNumElements())) {
                return tl::unexpected(
                    Error(ErrorType::INVALID_ARGUMENT,
                          "bucket_ids_ size (" + std::to_string(request.bucket_ids_.size()) +
                              ") must match the number of query vectors (" +
                              std::to_string(request.query_->GetNumElements()) + ")"));
            }
            if (this->GetIndexType() != IndexType::IVF && request.bucket_ids_.size() != 1) {
                return tl::unexpected(
                    Error(ErrorType::INVALID_ARGUMENT,
                          "bucket_ids_ supports multiple query vectors only for IVF indexes"));
            }
            for (uint64_t query_idx = 0; query_idx < request.bucket_ids_.size(); ++query_idx) {
                const auto& ids = request.bucket_ids_[query_idx];
                if (ids.empty()) {
                    return tl::unexpected(
                        Error(ErrorType::INVALID_ARGUMENT,
                              "bucket_ids_[" + std::to_string(query_idx) +
                                  "] must not be empty; use an empty outer vector "
                                  "for default routing"));
                }
                std::set<int64_t> seen_ids;
                for (auto id : ids) {
                    if (id < 0) {
                        return tl::unexpected(
                            Error(ErrorType::INVALID_ARGUMENT,
                                  "bucket_id " + std::to_string(id) + " is negative"));
                    }
                    if (not seen_ids.insert(id).second) {
                        return tl::unexpected(Error(ErrorType::INVALID_ARGUMENT,
                                                    "duplicate bucket_id " + std::to_string(id)));
                    }
                }
            }
            try {
                auto json_params = nlohmann::json::parse(request.params_str_);
                if (json_params.contains("ivf") and
                    json_params["ivf"].contains("disable_bucket_scan") and
                    json_params["ivf"]["disable_bucket_scan"].get<bool>()) {
                    return tl::unexpected(
                        Error(ErrorType::INVALID_ARGUMENT,
                              "bucket_ids_ is incompatible with disable_bucket_scan mode"));
                }
            } catch (const nlohmann::json::exception&) {
            }
        }
        SAFE_CALL(ValidateSearchThreshold(request.threshold_);
                  if (GetNumElements() == 0 && !this->ShouldSkipEmptyCheck(request.params_str_)) {
                      return make_empty_search_result();
                  } return this->inner_index_->SearchWithRequest(request));
    }
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L508 | request.bucket_ids_.empty | if_statement@508 (not request.bucket_ids_.empty()) | 当前参考未静态绑定；见下方边界说明 |

| L510 | tl::unexpected | if_statement@508 (not request.bucket_ids_.empty()) → if_statement@509 (request.query_ == nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L510 | Error | if_statement@508 (not request.bucket_ids_.empty()) → if_statement@509 (request.query_ == nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L513 | request.bucket_ids_.size | if_statement@508 (not request.bucket_ids_.empty()) → if_statement@513 (request.bucket_ids_.size() != static_cast&lt;size_t&gt;(request.query_-&gt;GetNumElements())) | 当前参考未静态绑定；见下方边界说明 |

| L514 | request.query_-&gt;GetNumElements | if_statement@508 (not request.bucket_ids_.empty()) → if_statement@513 (request.bucket_ids_.size() != static_cast&lt;size_t&gt;(request.query_-&gt;GetNumElements())) | 当前参考未静态绑定；见下方边界说明 |

| L515 | tl::unexpected | if_statement@508 (not request.bucket_ids_.empty()) → if_statement@513 (request.bucket_ids_.size() != static_cast&lt;size_t&gt;(request.query_-&gt;GetNumElements())) | 当前参考未静态绑定；见下方边界说明 |

| L516 | Error | if_statement@508 (not request.bucket_ids_.empty()) → if_statement@513 (request.bucket_ids_.size() != static_cast&lt;size_t&gt;(request.query_-&gt;GetNumElements())) | 当前参考未静态绑定；见下方边界说明 |

| L517 | std::to_string | if_statement@508 (not request.bucket_ids_.empty()) → if_statement@513 (request.bucket_ids_.size() != static_cast&lt;size_t&gt;(request.query_-&gt;GetNumElements())) | 当前参考未静态绑定；见下方边界说明 |

| L517 | request.bucket_ids_.size | if_statement@508 (not request.bucket_ids_.empty()) → if_statement@513 (request.bucket_ids_.size() != static_cast&lt;size_t&gt;(request.query_-&gt;GetNumElements())) | 当前参考未静态绑定；见下方边界说明 |

| L519 | std::to_string | if_statement@508 (not request.bucket_ids_.empty()) → if_statement@513 (request.bucket_ids_.size() != static_cast&lt;size_t&gt;(request.query_-&gt;GetNumElements())) | 当前参考未静态绑定；见下方边界说明 |

| L519 | request.query_-&gt;GetNumElements | if_statement@508 (not request.bucket_ids_.empty()) → if_statement@513 (request.bucket_ids_.size() != static_cast&lt;size_t&gt;(request.query_-&gt;GetNumElements())) | 当前参考未静态绑定；见下方边界说明 |

| L521 | this-&gt;GetIndexType | if_statement@508 (not request.bucket_ids_.empty()) → if_statement@521 (this-&gt;GetIndexType() != IndexType::IVF && request.bucket_ids_.size() != 1) | [IVF::GetIndexType · L121](ivf_h.md#L121) |

| L521 | request.bucket_ids_.size | if_statement@508 (not request.bucket_ids_.empty()) → if_statement@521 (this-&gt;GetIndexType() != IndexType::IVF && request.bucket_ids_.size() != 1) | 当前参考未静态绑定；见下方边界说明 |

| L522 | tl::unexpected | if_statement@508 (not request.bucket_ids_.empty()) → if_statement@521 (this-&gt;GetIndexType() != IndexType::IVF && request.bucket_ids_.size() != 1) | 当前参考未静态绑定；见下方边界说明 |

| L523 | Error | if_statement@508 (not request.bucket_ids_.empty()) → if_statement@521 (this-&gt;GetIndexType() != IndexType::IVF && request.bucket_ids_.size() != 1) | 当前参考未静态绑定；见下方边界说明 |

| L526 | request.bucket_ids_.size | if_statement@508 (not request.bucket_ids_.empty()) → for_statement@526 query_idx &lt; request.bucket_ids_.size() | 当前参考未静态绑定；见下方边界说明 |

| L528 | ids.empty | if_statement@508 (not request.bucket_ids_.empty()) → for_statement@526 query_idx &lt; request.bucket_ids_.size() → if_statement@528 (ids.empty()) | 当前参考未静态绑定；见下方边界说明 |

| L529 | tl::unexpected | if_statement@508 (not request.bucket_ids_.empty()) → for_statement@526 query_idx &lt; request.bucket_ids_.size() → if_statement@528 (ids.empty()) | 当前参考未静态绑定；见下方边界说明 |

| L530 | Error | if_statement@508 (not request.bucket_ids_.empty()) → for_statement@526 query_idx &lt; request.bucket_ids_.size() → if_statement@528 (ids.empty()) | 当前参考未静态绑定；见下方边界说明 |

| L531 | std::to_string | if_statement@508 (not request.bucket_ids_.empty()) → for_statement@526 query_idx &lt; request.bucket_ids_.size() → if_statement@528 (ids.empty()) | 当前参考未静态绑定；见下方边界说明 |

| L538 | tl::unexpected | if_statement@508 (not request.bucket_ids_.empty()) → for_statement@526 query_idx &lt; request.bucket_ids_.size() → for_range_loop@536 → if_statement@537 (id &lt; 0) | 当前参考未静态绑定；见下方边界说明 |

| L539 | Error | if_statement@508 (not request.bucket_ids_.empty()) → for_statement@526 query_idx &lt; request.bucket_ids_.size() → for_range_loop@536 → if_statement@537 (id &lt; 0) | 当前参考未静态绑定；见下方边界说明 |

| L540 | std::to_string | if_statement@508 (not request.bucket_ids_.empty()) → for_statement@526 query_idx &lt; request.bucket_ids_.size() → for_range_loop@536 → if_statement@537 (id &lt; 0) | 当前参考未静态绑定；见下方边界说明 |

| L542 | seen_ids.insert | if_statement@508 (not request.bucket_ids_.empty()) → for_statement@526 query_idx &lt; request.bucket_ids_.size() → for_range_loop@536 → if_statement@542 (not seen_ids.insert(id).second) | 当前参考未静态绑定；见下方边界说明 |

| L543 | tl::unexpected | if_statement@508 (not request.bucket_ids_.empty()) → for_statement@526 query_idx &lt; request.bucket_ids_.size() → for_range_loop@536 → if_statement@542 (not seen_ids.insert(id).second) | 当前参考未静态绑定；见下方边界说明 |

| L543 | Error | if_statement@508 (not request.bucket_ids_.empty()) → for_statement@526 query_idx &lt; request.bucket_ids_.size() → for_range_loop@536 → if_statement@542 (not seen_ids.insert(id).second) | 当前参考未静态绑定；见下方边界说明 |

| L544 | std::to_string | if_statement@508 (not request.bucket_ids_.empty()) → for_statement@526 query_idx &lt; request.bucket_ids_.size() → for_range_loop@536 → if_statement@542 (not seen_ids.insert(id).second) | 当前参考未静态绑定；见下方边界说明 |

| L549 | nlohmann::json::parse | if_statement@508 (not request.bucket_ids_.empty()) | 当前参考未静态绑定；见下方边界说明 |

| L550 | json_params.contains | if_statement@508 (not request.bucket_ids_.empty()) → if_statement@550 (json_params.contains("ivf") and json_params["ivf"].contains("disable_bucket_scan") and json_params["ivf"]["disable_bucket_scan"].get&lt;bool&gt;()) | 当前参考未静态绑定；见下方边界说明 |

| L551 | json_params["ivf"].contains | if_statement@508 (not request.bucket_ids_.empty()) → if_statement@550 (json_params.contains("ivf") and json_params["ivf"].contains("disable_bucket_scan") and json_params["ivf"]["disable_bucket_scan"].get&lt;bool&gt;()) | 当前参考未静态绑定；见下方边界说明 |

| L552 | json_params["ivf"]["disable_bucket_scan"].get&lt;bool&gt; | if_statement@508 (not request.bucket_ids_.empty()) → if_statement@550 (json_params.contains("ivf") and json_params["ivf"].contains("disable_bucket_scan") and json_params["ivf"]["disable_bucket_scan"].get&lt;bool&gt;()) | 当前参考未静态绑定；见下方边界说明 |

| L553 | tl::unexpected | if_statement@508 (not request.bucket_ids_.empty()) → if_statement@550 (json_params.contains("ivf") and json_params["ivf"].contains("disable_bucket_scan") and json_params["ivf"]["disable_bucket_scan"].get&lt;bool&gt;()) | 当前参考未静态绑定；见下方边界说明 |

| L554 | Error | if_statement@508 (not request.bucket_ids_.empty()) → if_statement@550 (json_params.contains("ivf") and json_params["ivf"].contains("disable_bucket_scan") and json_params["ivf"]["disable_bucket_scan"].get&lt;bool&gt;()) | 当前参考未静态绑定；见下方边界说明 |

| L560 | SAFE_CALL | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L560 | ValidateSearchThreshold | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L561 | GetNumElements | if_statement@561 (GetNumElements() == 0 && !this-&gt;ShouldSkipEmptyCheck(request.params_str_)) | [IVF::GetNumElements · L291](ivf.md#L291) |

| L561 | this-&gt;ShouldSkipEmptyCheck | if_statement@561 (GetNumElements() == 0 && !this-&gt;ShouldSkipEmptyCheck(request.params_str_)) | 当前参考未静态绑定；见下方边界说明 |

| L562 | make_empty_search_result | if_statement@561 (GetNumElements() == 0 && !this-&gt;ShouldSkipEmptyCheck(request.params_str_)) | 当前参考未静态绑定；见下方边界说明 |

| L563 | this-&gt;inner_index_-&gt;SearchWithRequest | 函数本体；短路求值/提前返回见源码 | [IndexImpl::SearchWithRequest · L505](index_impl_h.md#L505) |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。
