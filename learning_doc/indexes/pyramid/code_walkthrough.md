# Pyramid：代码逐段导读

[直观图解](visual_guide.md)

[返回设计说明](README.md) · [所有索引](../README.md)

源码基线：`fd363937`。下面引用真实源码，不将摘录伪装为独立可编译程序。完整实现还包含未展示的检查和分支，请结合链接阅读。

重点跟踪业务路径解析、树节点状态，以及节点搜索如何复用同一份向量编码。

## 1. 节点 Build 根据状态决定是否构图

源码：[src/algorithm/pyramid/pyramid_index_node.cpp](../../../src/algorithm/pyramid/pyramid_index_node.cpp)，基线行号 66–82。以下为连续原文摘录，可能是函数的一部分。

```cpp
IndexNode::Build(ODescent& odescent) {
    std::unique_lock lock(mutex_);
    // Build an index when the level corresponding to the current node requires indexing
    if (not ids_.empty()) {
        Init();
    }
    if (status_ == Status::GRAPH) {
        entry_point_ = ids_[0];
        odescent.SetMaxDegree(static_cast<int32_t>(graph_param_->max_degree_));
        odescent.Build(ids_);
        odescent.SaveGraph(graph_);
        Vector<InnerIdType>(allocator_).swap(ids_);
    }
    for (const auto& item : children_) {
        item.second->Build(odescent);
    }
}
```

非空 ids_ 先 Init，让节点确定状态；GRAPH 节点使用 ODescent 构图并保存 graph_，随后释放这份构图用 ID 向量，再递归处理子节点。这里的 graph_ 是节点图，不是一个完整 HGraph 实例。释放 IDs 不代表向量数据被删除，向量由外层共享数据单元管理。

## 2. 路径按段定位，不做模糊回退

源码：[src/algorithm/pyramid/pyramid.cpp](../../../src/algorithm/pyramid/pyramid.cpp)，基线行号 2304–2330。以下为连续原文摘录，可能是函数的一部分。

```cpp
Pyramid::search_hierarchy(const Hierarchy& h,
                          const SearchFunc& search_func,
                          const VisitedListPtr& vl,
                          DistHeapPtr& search_result,
                          const std::string& path,
                          const InnerSearchParam& search_param,
                          ReasoningContext* reasoning_ctx) const {
    std::vector<std::future<void>> futures;
    auto parsed_path = parse_path(path);
    Vector<DistHeapPtr> search_result_lists(parsed_path.size(), allocator_);
    for (uint32_t i = 0; i < parsed_path.size(); ++i) {
        const auto& one_path = parsed_path[i];
        search_result_lists[i] = std::make_shared<StandardHeap<true, false>>(allocator_, -1);
        IndexNode* node = h.root.get();
        bool valid = true;
        for (const auto& item : one_path) {
            node = node->GetChild(item, false);
            if (node == nullptr) {
                valid = false;
                break;
            }
        }
        if (valid) {
            if (thread_pool_ != nullptr && search_param.parallel_search_thread_count > 1) {
                futures.push_back(thread_pool_->GeneralEnqueue([&, node, i]() -> void {
                    VisitedListGuard vl_guard(pool_.get());
                    const VisitedListPtr& local_vl = vl_guard.get();
```

1. parse_path 先拆请求中的多条路径。
2. 每条路径都从当前 hierarchy 的 root 出发。
3. GetChild 的 false 表示查询不创建缺失节点。
4. 任一段不存在时 valid=false，该条路径不会调用 Search。不存在的租户路径不会自动退回更宽的根范围。

## 3. 路径语法拆分

源码：[src/algorithm/pyramid/pyramid.cpp](../../../src/algorithm/pyramid/pyramid.cpp)，基线行号 2358–2366。以下为连续原文摘录，可能是函数的一部分。

```cpp
Pyramid::parse_path(const std::string& path) {
    auto multi_paths = split(path, PART_BAR);
    std::vector<std::vector<std::string>> parsed_paths;
    parsed_paths.reserve(multi_paths.size());
    for (const auto& single_path : multi_paths) {
        parsed_paths.push_back(split(single_path, PART_SLASH));
    }
    return parsed_paths;
}
```

先按 PART_BAR 分离多条路径，再按 PART_SLASH 分离层级段。它们承担两个不同维度的分隔职责。完整多 hierarchy 条件组合和结果合并不在这几行中，不能仅由这个字符串解析函数推出所有查询布尔语义。

## 4. FLAT 节点直接批量计算自己的 ID 集合

源码：[src/algorithm/pyramid/pyramid.cpp](../../../src/algorithm/pyramid/pyramid.cpp)，基线行号 2380–2410。以下为连续原文摘录，可能是函数的一部分。

```cpp
    const auto computer = codes->FactoryComputer(query_vector);

    if (node->status_ == IndexNode::Status::FLAT) {
        results = std::make_shared<StandardHeap<true, false>>(ctx.alloc, -1);
        if (search_param.time_cost != nullptr and search_param.time_cost->CheckOvertime() and
            ctx.stats != nullptr) {
            ctx.stats->is_timeout.store(true, std::memory_order_relaxed);
            return results;
        }
        const auto* ids_ptr = node->ids_.data();
        auto id_count = node->ids_.size();
        Vector<InnerIdType> valid_ids(ctx.alloc);

        if (search_param.is_inner_id_allowed != nullptr) {
            const auto& inner_filter = search_param.is_inner_id_allowed;
            valid_ids.reserve(node->ids_.size());
            for (uint64_t i = 0; i < id_count; ++i) {
                if (inner_filter->CheckValid(ids_ptr[i])) {
                    valid_ids.push_back(ids_ptr[i]);
                } else if (ctx.reasoning_ctx != nullptr) {
                    ctx.reasoning_ctx->RecordFilterReject(ids_ptr[i]);
                }
            }
            ids_ptr = valid_ids.data();
            id_count = valid_ids.size();
        }

        Vector<float> dists(id_count, ctx.alloc);
        codes->Query(dists.data(), computer, ids_ptr, id_count, &ctx);

        for (uint64_t i = 0; i < id_count; ++i) {
```

1. 当前节点状态为 FLAT 时，从 node->ids_ 取得该范围内记录。
2. 如有过滤器，先收集 valid_ids，而不是先对整个全局集合计算。
3. codes->Query 的 count 是该批有效 ID 数量，这里确实使用批量接口。
4. 共享的 codes 提供相同向量编码，节点只负责给出搜索范围。

## 5. GRAPH 节点准备入口与候选参数

源码：[src/algorithm/pyramid/pyramid.cpp](../../../src/algorithm/pyramid/pyramid.cpp)，基线行号 2428–2451。以下为连续原文摘录，可能是函数的一部分。

```cpp
    } else if (node->status_ == IndexNode::Status::GRAPH) {
        InnerSearchParam modified_param = search_param;
        modified_param.ep =
            resolve_entry_point(*node, vl, query_vector, codes, computer, search_param, ctx);
        if (node->level_ != 0) {
            if (search_param.search_mode == KNN_SEARCH) {
                modified_param.ef = std::min(
                    modified_param.ef,
                    get_suitable_ef_search(
                        search_param.topk, node->graph_->TotalCount(), subindex_ef_search));
            }
        }
        modified_param.topk = static_cast<int64_t>(modified_param.ef);
        results = searcher_->SearchWithPresetComputer(node->graph_,
                                                      codes,
                                                      vl,
                                                      query_vector,
                                                      modified_param,
                                                      label_table_,
                                                      &ctx,
                                                      rabitq_lower_bound_candidates,
                                                      computer);
    }

```

GRAPH 分支通过 resolve_entry_point 找入口；非根节点可根据子索引规模调整 ef。然后把图、codes、visited 和预创建 Computer 一起交给 searcher。业务树路径决定节点，图入口决定该节点内的导航起点，两者应分开理解。

## 读完以后应能解释

查询不存在路径时为什么不能扩大搜索范围？FLAT 与 GRAPH 节点各自持有什么？为什么共享向量编码不等于没有多层图内存？路径层级与近邻导航层级的职责区别是什么？
