# LazyHGraph：代码逐段导读

[直观图解](visual_guide.md)

[返回设计说明](README.md) · [所有索引](../README.md)

源码基线：`fd363937`。下面引用真实源码，不将摘录伪装为独立可编译程序。完整实现还包含未展示的检查和分支，请结合链接阅读。

这是一个可以完整跟踪的状态机：公共操作通过 ActiveIndex 转发，状态转换负责内部对象的一致性。

## 1. ActiveIndex 与 Build 的分支

源码：[src/algorithm/lazy_hgraph/lazy_hgraph.cpp](../../../src/algorithm/lazy_hgraph/lazy_hgraph.cpp)，基线行号 144–165。以下为连续原文摘录，可能是函数的一部分。

```cpp
LazyHGraph::ActiveIndex() const {
    if (phase_.load(std::memory_order_acquire) == Phase::FLAT) {
        return flat_index_.get();
    }
    CHECK_ARGUMENT(graph_index_ != nullptr, "lazy_hgraph graph index is not initialized");
    return graph_index_.get();
}

std::vector<int64_t>
LazyHGraph::Build(const DatasetPtr& data) {
    std::unique_lock lock(this->phase_mutex_);
    CHECK_ARGUMENT(ActiveIndex()->GetNumElements() == 0, "index is not empty");
    if (static_cast<uint64_t>(data->GetNumElements()) < transition_threshold_) {
        phase_.store(Phase::FLAT, std::memory_order_release);
        return flat_index_->Build(data);
    }
    graph_index_ = std::make_shared<HGraph>(graph_param_, this->common_param_);
    graph_index_->InitFeatures();
    auto failed_ids = graph_index_->Build(data);
    phase_.store(Phase::GRAPH, std::memory_order_release);
    flat_index_.reset();
    return failed_ids;
```

1. acquire 读取 phase 与后面的 release 发布形成对应关系，但对象生命周期同时由 phase_mutex_ 保护。
2. Build 数量小于阈值走 flat；达到阈值直接构建图。
3. 只有图 Build 返回后才发布 GRAPH 并释放 flat。注意这个直接 Build 分支返回失败 ID 列表，与迁移分支要求失败列表为空的处理不同。

## 2. Add 如何触发转换

源码：[src/algorithm/lazy_hgraph/lazy_hgraph.cpp](../../../src/algorithm/lazy_hgraph/lazy_hgraph.cpp)，基线行号 169–186。以下为连续原文摘录，可能是函数的一部分。

```cpp
LazyHGraph::Add(const DatasetPtr& data) {
    std::vector<int64_t> failed_ids;
    bool need_transition = false;
    {
        std::shared_lock lock(this->phase_mutex_);
        if (phase_.load(std::memory_order_acquire) == Phase::FLAT) {
            failed_ids = flat_index_->Add(data);
            need_transition =
                static_cast<uint64_t>(flat_index_->GetNumElements()) >= transition_threshold_;
        } else {
            failed_ids = graph_index_->Add(data);
        }
    }
    if (need_transition) {
        TransitionToGraph();
    }
    return failed_ids;
}
```

1. 当前阶段插入在共享阶段锁下执行，底层索引自行协调其写操作。
2. flat 插入完成后依据 GetNumElements 判断阈值。
3. 大括号结束释放共享锁，再调用需要独占锁的 TransitionToGraph。
4. 两个并发 Add 都可能设置 need_transition，所以迁移函数还必须再次判断 phase。

## 3. 迁移先筛选仍有效的数据

源码：[src/algorithm/lazy_hgraph/lazy_hgraph.cpp](../../../src/algorithm/lazy_hgraph/lazy_hgraph.cpp)，基线行号 189–215。以下为连续原文摘录，可能是函数的一部分。

```cpp
LazyHGraph::TransitionToGraph() {
    std::unique_lock lock(this->phase_mutex_);
    if (phase_.load(std::memory_order_acquire) == Phase::GRAPH) {
        return;
    }
    auto id_dataset = flat_index_->ExportIDs();
    if (id_dataset == nullptr) {
        return;
    }
    const auto total = id_dataset->GetNumElements();
    const auto* ids = id_dataset->GetIds();
    if (ids == nullptr) {
        return;
    }
    std::vector<int64_t> valid_ids;
    valid_ids.reserve(static_cast<uint64_t>(total));
    for (int64_t i = 0; i < total; ++i) {
        if (flat_index_->CheckIdExist(ids[i])) {
            valid_ids.emplace_back(ids[i]);
        }
    }
    if (valid_ids.empty()) {
        return;
    }

    CHECK_ARGUMENT(valid_ids.size() <= static_cast<uint64_t>(std::numeric_limits<int64_t>::max()),
                   "lazy_hgraph transition id count is too large");
```

独占锁覆盖整个迁移流程。ExportIDs 后再通过 CheckIdExist 防御性过滤有效记录。应同时看本文件的 Remove：FLAT 阶段固定使用 FORCE_REMOVE，不能仅凭迁移过滤就推断正常路径会保留逻辑删除记录。空指针或空有效集合会提前返回，说明“调用迁移函数”本身不代表阶段已经变为 GRAPH。

## 4. 完整构建后再发布新图

源码：[src/algorithm/lazy_hgraph/lazy_hgraph.cpp](../../../src/algorithm/lazy_hgraph/lazy_hgraph.cpp)，基线行号 217–230。以下为连续原文摘录，可能是函数的一部分。

```cpp

    auto build_data = flat_index_->GetDataByIds(valid_ids.data(), valid_count);
    if (build_data == nullptr) {
        throw VsagException(ErrorType::NO_ENOUGH_MEMORY, "failed to get lazy_hgraph vectors");
    }

    auto new_graph = std::make_shared<HGraph>(graph_param_, this->common_param_);
    new_graph->InitFeatures();
    auto failed_ids = new_graph->Build(build_data);
    CHECK_ARGUMENT(failed_ids.empty(), "lazy_hgraph transition failed to build all ids");
    graph_index_ = new_graph;
    flat_index_.reset();
    phase_.store(Phase::GRAPH, std::memory_order_release);
}
```

1. 根据有效 label 取回 Dataset，检查提取结果。
2. 用局部 new_graph 构建，失败 ID 非空会触发错误。
3. 成功后先保存新对象、释放旧对象，再发布阶段。
4. 迁移构图失败时旧 flat 尚未释放；但之前 Add 的数据可能已经进入 flat，所以并不是整个 Add 的事务回滚。峰值内存包含旧 flat、提取数据及在建图。

## 5. 为什么切换会阻塞查询

源码：[src/algorithm/lazy_hgraph/lazy_hgraph.cpp](../../../src/algorithm/lazy_hgraph/lazy_hgraph.cpp)，基线行号 233–249。以下为连续原文摘录，可能是函数的一部分。

```cpp
LazyHGraph::KnnSearch(const DatasetPtr& query,
                      int64_t k,
                      const std::string& parameters,
                      const FilterPtr& filter) const {
    std::shared_lock lock(this->phase_mutex_);
    return ActiveIndex()->KnnSearch(query, k, parameters, filter);
}

DatasetPtr
LazyHGraph::RangeSearch(const DatasetPtr& query,
                        float radius,
                        const std::string& parameters,
                        const FilterPtr& filter,
                        int64_t limited_size) const {
    std::shared_lock lock(this->phase_mutex_);
    return ActiveIndex()->RangeSearch(query, radius, parameters, filter, limited_size);
}
```

查询持有 phase_mutex_ 的共享锁直到内部搜索返回。迁移持有同一把锁的独占锁，因此两者不会同时进入内部对象操作。这解释了状态一致性，也解释了迁移期间的查询等待。不要把 atomic phase 误认为无需锁的热切换。

## 读完以后应能解释

哪行代码真正发布 GRAPH？哪一个锁保护旧对象不被查询期间释放？为什么需要迁移前后二次判断？若迁移失败，哪些数据可能已经被写入？
