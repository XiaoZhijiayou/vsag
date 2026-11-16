# 过滤、生命周期与并发

## 1. 为什么需要外部 label 与内部 ID

业务 ID 可以不连续，图邻接表和数组索引更适合紧凑内部编号。[LabelTable](../../src/impl/label_table/label_table.h) 将两者关联，搜索结束后再把内部 ID 转回用户 ID。

这样便于直接寻址、紧凑存储和 visited 标记；代价是增加映射占用，并要求删除、搬移、重复处理、序列化始终保持映射一致。BruteForce 的强制删除可能搬动末尾记录，外部 ID 的稳定性依赖映射随之修正。

## 2. 过滤是搜索策略的一部分

只在全局 top-k 得到后删除不合法结果，可能返回不足 k 个结果，也可能漏掉合法集合中本应命中的最近邻。图搜索中还要区分“可作为路过的导航节点”和“可作为最终结果的节点”，一刀切阻断无效点可能损害连通性。

VSAG 存在 ID 过滤器适配、属性表达式执行器、Pyramid 路径路由、SINDI 元数据路由、HGraph MCI 等不同机制。它们作用的阶段不同，不能简单归类为同一种 post-filter。

阅读 [Filter 接口](../../include/vsag/filter.h)、[过滤组件](../../src/impl/filter/)、[属性执行器](../../src/attr/executor/)、[sindi_metadata_filter.cpp](../../src/algorithm/sindi_metadata_filter.cpp)。自定义过滤器提供的 `ValidRatio()` 会影响部分搜索规划，估计不准确可能使系统选到不合适的路径。

## 3. 增量维护为什么各不相同

- BruteForce 追加编码和 label；没有邻居选择成本。
- HGraph 插入时还要搜索邻居、连边和剪枝；删除与更新还涉及图结构。
- IVF 将数据分到已学习的桶；是否支持追加受配置约束，例如当前 PQFS 路径不声明 Add-after-Build。
- LazyHGraph 在阈值处构建 HGraph，触发明显的阶段切换成本。
- SINDI_V2 的可写性受 term IO、immutable 与 rerank 配置共同约束。

因此不能从“父接口有 Add”推断每种实例都能安全持续追加，也不能从“允许 Add”推断数据分布漂移后索引质量一直不变。

## 4. 标记删除与物理删除

标记删除通常让搜索忽略该记录，原先存储仍可能保留；物理删除还需要处理槽位和相关结构。BruteForce 比图索引更容易压紧数据，因为它没有指向待移动记录的邻接边需要修复。

分析回收效果时要区分逻辑存活数、索引分配量与进程 RSS：释放完整块或交还给分配器，不保证操作系统看到的 RSS 立即下降。并非每个索引都支持两种删除模式，具体看对应 `Remove` 和 `InitFeatures`。

## 5. 序列化保存的不只是向量

重建查询行为还需要量化模型、图或桶结构、label、配置及可选组件。相关入口位于 [storage](../../src/storage/)、[load_parameters.h](../../include/vsag/load_parameters.h) 和具体算法的 Serialize/Deserialize。

当前代码同时包含历史格式兼容处理、footer 元数据以及 streaming header/body 等路径。不要用一句“统一格式”推断不同索引可以互相加载：SINDI 与 SINDI_V2 的 posting 布局就明确不同。

完整反序列化和按需访问也不同。[ByteIO::Deserialize](../../src/io/core/byte_io.h) 对能绑定序列化区间的后端可记录区间，其他后端则按块读取恢复。即使有 Reader，究竟哪些部分常驻内存、哪些后续读取，仍由该算法和加载计划决定。

## 6. 并发要看锁与配置

| 实现观察 | 含义 |
| --- | --- |
| LazyHGraph `TransitionToGraph` 取得 `phase_mutex_` 独占锁 | 切换期间需要同一把锁的查询会等待；不是后台无停顿切换 |
| SIMQ `KnnSearch` 取得 `global_mutex_` 独占锁 | 当前查询复用可变粗排缓冲，不能把 token 内部并行理解为多请求并行 |
| HGraph 查询根据 immutable / force-remove 配置取得相应锁 | 并发开销与实例配置有关 |
| SINDI/V2 查询使用共享锁，写入路径加锁 | 读写行为需要结合锁范围与内部数据结构检查 |

这些是源码观察，不是独立的线程安全认证。学习时应同时读操作实现、能力声明与并发测试。资源层有线程池，也不意味着每种操作都自动并行。

## 7. 代码：同一 Filter 为什么影响搜索路由

源码：[src/algorithm/hgraph/hgraph_mci.cpp](../../src/algorithm/hgraph/hgraph_mci.cpp)，基线行号 525–546。以下为连续原文摘录，可能是函数的一部分。

```cpp
HGraph::try_mci_search(const SearchRequest& request,
                       const HGraphSearchParameters& params,
                       const FilterPtr& inner_filter,
                       const void* query,
                       const InnerSearchParam& search_param,
                       QueryContext* ctx) const {
    MCIHybridSearchResult result(params, inner_filter);
    const bool bitset_seed_source = has_bitset_source(request.filter_);
    const bool can_use_mci = params.use_mci and this->mci_parameters_.enabled and
                             search_param.executors.empty() and
                             (has_valid_id_source(request.filter_) or bitset_seed_source) and
                             this->mci_cliques_ != nullptr and
                             this->mci_cliques_->HasCliqueIndex(this->total_count_.load());
    if (not can_use_mci) {
        return result;
    }

    result.route = "hgraph";
    if (request.mode_ == SearchMode::RANGE_SEARCH or result.valid_ratio >= result.threshold) {
        return result;
    }

```

MCI 的选择同时取决于当前请求、seed 来源、executor、挂件是否有效及选择率；不是单独一个阈值判断。RangeSearch 在这条路径退出，说明 KNN 与范围搜索不能共享一份未经核对的能力解释。

## 8. 代码：保存参数元数据及校验

源码：[src/storage/serialization.cpp](../../src/storage/serialization.cpp)，基线行号 66–80。以下为连续原文摘录，可能是函数的一部分。

```cpp
    writer.Write(SERIAL_STREAM_MAGIC, 8);
    StreamWriter::WriteObj(writer, SERIAL_STREAM_FORMAT_MAJOR);
    StreamWriter::WriteObj(writer, SERIAL_STREAM_FORMAT_MINOR);

    auto metadata_string = metadata->ToString();
    const uint64_t metadata_len = metadata_string.size();
    if (metadata_len > STREAM_HEADER_MAX_METADATA_LEN) {
        throw VsagException(ErrorType::INVALID_BINARY,
                            "streaming serialization metadata is too large");
    }
    StreamWriter::WriteObj(writer, metadata_len);
    writer.Write(metadata_string.c_str(), metadata_len);
    const uint32_t checksum = StreamHeader::CalculateChecksum(metadata_string);
    StreamWriter::WriteObj(writer, checksum);
}
```

StreamHeader 写入 magic、主次版本、元数据长度、内容和 checksum。长度先受上限约束。这里 checksum 对应这段元数据，不应夸大为“整个索引所有字节都受到这个校验保护”。具体数据块兼容性还要跟随后续格式与算法加载代码。
