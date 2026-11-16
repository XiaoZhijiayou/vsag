# BruteForce：代码逐段导读

[直观图解](visual_guide.md)

[返回设计说明](README.md) · [所有索引](../README.md)

源码基线：`fd363937`。下面引用真实源码，不将摘录伪装为独立可编译程序。完整实现还包含未展示的检查和分支，请结合链接阅读。

主线是 Build → Train/Add → SearchWithRequest → DataCell::Query → 结果堆。特别注意普通扫描与自定义距离回调的批量行为不同。

## 1. Build 为什么只有两步

源码：[src/algorithm/bruteforce/bruteforce.cpp](../../../src/algorithm/bruteforce/bruteforce.cpp)，基线行号 96–101。以下为连续原文摘录，可能是函数的一部分。

```cpp
BruteForce::Build(const vsag::DatasetPtr& data) {
    this->Train(data);
    return this->Add(data);
}

void
```

第一步 Train 准备当前编码所需的模型，第二步 Add 才写入记录。返回 Add 的失败 ID 列表，说明 Build 的成功状态还包括逐条记录处理结果。这里没有构图或聚类中心训练，不能把其他索引的 Build 流程套过来。

## 2. 查询入口准备哪些状态

源码：[src/algorithm/bruteforce/bruteforce.cpp](../../../src/algorithm/bruteforce/bruteforce.cpp)，基线行号 375–410。以下为连续原文摘录，可能是函数的一部分。

```cpp
BruteForce::SearchWithRequest(const SearchRequest& request) const {
    ValidateSearchThreshold(request.threshold_);
    std::shared_lock read_lock(this->global_mutex_);
    SearchStatistics statistics;
    QueryContext query_context{.stats = &statistics};

    const bool use_custom_distance = request.distance_batch_func_ != nullptr;
    if (use_custom_distance) {
        CHECK_ARGUMENT(request.distance_batch_size_ > 0,
                       "distance_batch_size must be greater than 0");
    }

    ComputerInterfacePtr computer = nullptr;
    if (not use_custom_distance) {
        computer = this->make_search_computer(request.query_);
    }

    bool is_range = (request.mode_ == SearchMode::RANGE_SEARCH);
    if (is_range) {
        if (use_custom_distance) {
            CHECK_ARGUMENT(std::isfinite(request.radius_), "radius must be finite");
            CHECK_ARGUMENT(request.radius_ >= 0.0F, "radius must be non-negative");
            CHECK_ARGUMENT(request.limited_size_ != 0, "limited_size must not be 0");
        } else if (not is_multi_vector_) {
            this->validate_range_args(request.query_, request.radius_, request.limited_size_);
        }
    } else {
        if (use_custom_distance) {
            CHECK_ARGUMENT(request.topk_ > 0, "topk must be greater than 0");
        } else if (not is_multi_vector_) {
            this->validate_knn_args(request.query_, request.topk_);
        }
    }

    auto heap_size = is_range ? request.limited_size_ : request.topk_;
    if (heap_size < 0) {
```

1. 首先校验阈值并持有全局共享锁，保护扫描看到的记录状态。
2. `use_custom_distance` 区分外部回调与内部编码打分；只有后者创建查询 Computer。
3. 范围搜索与 KNN 使用不同边界；多向量的输入检查不能简单沿用单向量路径。
4. QueryContext 是这次搜索的统计上下文，不能把它当作持久化索引数据。

## 3. 真正的记录扫描循环

源码：[src/algorithm/bruteforce/bruteforce.cpp](../../../src/algorithm/bruteforce/bruteforce.cpp)，基线行号 525–557。以下为连续原文摘录，可能是函数的一部分。

```cpp
        for (InnerIdType i = start; i < end; ++i) {
            if (attr_filter != nullptr and not attr_filter->CheckValid(i)) {
                if (reasoning != nullptr) {
                    reasoning->RecordFilterReject(i);
                }
                continue;
            }
            if (ft == nullptr or ft->CheckValid(i)) {
                if (use_custom_distance) {
                    custom_inner_ids.push_back(i);
                    custom_labels.push_back(this->label_table_->GetLabelById(i));
                    if (custom_inner_ids.size() == request.distance_batch_size_) {
                        flush_custom_batch();
                    }
                } else {
                    float dist = 0.0F;
                    inner_codes_->Query(&dist, computer, &i, 1, &local_query_context);
                    ++dist_cmp_local;
                    if (reasoning != nullptr) {
                        reasoning->RecordVisit(i, dist, 0);
                    }
                    if (is_range and dist > radius) {
                        continue;
                    }
                    if (is_range or not request.threshold_.has_value() or std::isfinite(dist)) {
                        cur_heap->Push(dist, i);
                    }
                }
            } else {
                if (reasoning != nullptr) {
                    reasoning->RecordFilterReject(i);
                }
            }
```

1. `i` 是内部槽位，属性过滤与普通过滤都在进入正常距离计算前检查。
2. 自定义距离分支先收集内部 ID 和外部 label，达到配置批次后调用回调。
3. 普通分支实际调用 `Query(..., &i, 1, ...)`，每次处理一个记录；不能因为 DataCell 支持批量接口就把这个循环描述成批量 SIMD 跨记录扫描。
4. 距离核本身仍可能在向量维度上使用 SIMD。范围限制通过比较 radius 排除不合格记录。

## 4. 单查询扫描怎样分给线程

源码：[src/algorithm/bruteforce/bruteforce.cpp](../../../src/algorithm/bruteforce/bruteforce.cpp)，基线行号 571–594。以下为连续原文摘录，可能是函数的一部分。

```cpp
    // throughput.
    if (parallel_count == 1 || this->thread_pool_ == nullptr || reasoning != nullptr) {
        search_func(0, count, heaps[0]);
        heap = heaps[0];
    } else {
        std::vector<std::future<void>> futures;
        auto chunk_size = (count + parallel_count - 1) / parallel_count;
        for (auto i = 0; i < parallel_count; ++i) {
            auto start = i * chunk_size;
            auto end = std::min(start + chunk_size, count);
            if (start >= end) {
                continue;
            }
            auto future = this->thread_pool_->GeneralEnqueue(search_func, start, end, heaps[i]);
            futures.emplace_back(std::move(future));
        }
        std::exception_ptr first_error = nullptr;
        for (auto& future : futures) {
            try {
                future.get();
            } catch (...) {
                if (first_error == nullptr) {
                    first_error = std::current_exception();
                }
```

1. `chunk_size` 按记录数量划分区间，尾区间通过 min 截断。
2. 每个任务使用自己的结果堆，完成后由后续代码合并，避免每次 Push 争抢同一把堆锁。
3. reasoning 启用时强制串行，因为该诊断上下文不是线程安全的；这说明观测功能可能改变执行成本。
4. 异常通过 future 回传，后续代码收集任务错误；不能把提交任务理解为已完成查询。

## 5. 物理删除为何必须维护映射

源码：[src/algorithm/bruteforce/bruteforce.cpp](../../../src/algorithm/bruteforce/bruteforce.cpp)，基线行号 300–344。以下为连续原文摘录，可能是函数的一部分。

```cpp
BruteForce::Remove(const std::vector<int64_t>& ids, RemoveMode mode) {
    if (is_multi_vector_ && mode != RemoveMode::MARK_REMOVE) {
        throw VsagException(ErrorType::INVALID_ARGUMENT,
                            "multi-vector mode only supports MARK_REMOVE");
    }
    if (not is_multi_vector_) {
        CHECK_ARGUMENT(not use_attribute_filter_,
                       "remove is not supported when use_attribute_filter is true");
    }

    uint32_t delete_count = 0;
    if (mode == RemoveMode::MARK_REMOVE) {
        std::scoped_lock label_lock(this->label_lookup_mutex_);
        delete_count = this->label_table_->MarkRemove(ids);
        delete_count_.fetch_add(delete_count, std::memory_order_relaxed);
        return delete_count;
    }

    std::scoped_lock add_label_lock(this->add_mutex_, this->label_lookup_mutex_);
    std::unique_lock global_lock(this->global_mutex_);
    for (auto label : ids) {
        InnerIdType inner_id;
        bool found = false;
        std::tie(found, inner_id) = this->label_table_->TryGetIdByLabel(label, true);
        auto current_total = this->total_count_.load();
        if (not found or inner_id >= current_total) {
            continue;
        }

        const auto last_inner_id = static_cast<InnerIdType>(current_total - 1);
        Vector<float> data(allocator_);
        if (inner_id < last_inner_id) {
            data.resize(dim_);
            GetVectorByInnerId(last_inner_id, data.data());
        }
        bool was_mark_removed = this->label_table_->IsRemoved(inner_id);
        this->label_table_->ForceRemove(label, inner_id);

        if (inner_id < last_inner_id) {
            this->inner_codes_->InsertVector(data.data(), inner_id);
            this->label_table_->Move(last_inner_id, inner_id);
            if (this->extra_infos_ != nullptr) {
                this->extra_infos_->Move(last_inner_id, inner_id);
            }
        }
```

1. 多向量模式只允许 MARK_REMOVE；单向量属性过滤模式也有显式限制。
2. 标记删除只更新 LabelTable 与删除计数，快速返回。
3. 强制删除同时协调追加、label 和全局搜索，先找到真实槽位。
4. 如果删除的不是末尾槽位，读取末尾向量后覆盖目标槽位，并移动 label 与额外信息。仅移动向量而不更新映射会使外部 ID 对错数据。

## 读完以后应能解释

普通扫描中哪个 ID 是槽位，哪个 ID 是业务 label？为什么多线程需要多个堆？为什么 Query 的 count=1 不意味着距离核没有 SIMD？物理删除与标记删除各自改了哪些状态？
