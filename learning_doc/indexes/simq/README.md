# SIMQ：代表向量图粗排与文档级 MaxSim 精排

[直观图解](visual_guide.md)

配套：[代码逐段导读](code_walkthrough.md) · [WARP 基线](../warp/README.md)

## 1. 解决什么问题

SIMQ 的全名是 Single Index for Multi-vector Query。它处理一篇文档有多个 token 向量的检索：如果每次都对所有文档做完整 MaxSim，计算与读取成本很高。

它首先用较少的代表向量筛出候选文档，再读取这些文档的完整 token 进行评分。两阶段结构的目标是减少昂贵的文档级 MaxSim 次数。

## 2. 持有什么数据

| 成员 | 含义 |
| --- | --- |
| `rep_hgraph_` | 代表 token 向量构成的 HGraph |
| `cluster_lists_` | 每个簇关联哪些文档 |
| `vec_to_cluster_` | token 属于哪个簇 |
| `token_to_doc_` / `token_to_offset_` | token 对应的文档及文档内位置 |
| `token_to_dist_` 等信息 | token 与簇代表的关系，用于维护与分裂 |
| `mv_codes_` | 文档完整 token 存储与 MaxSim 计算 |
| coarse 缓冲区 | 查询间复用的文档分数和去重状态 |

代表图中的节点不是最终返回的文档。图先给出簇，再经 `cluster_lists_` 扩展成文档候选。

## 3. 构建与动态簇维护

Build 汇总所有文档 token，按初始化参数形成簇，建立 token 到簇/文档映射和代表向量图，并保存文档 token。簇过大会扩大后续候选文档范围，所以实现有阈值与分裂机制。

增量 Add 需要同时更新文档存储、token 映射、簇文档集合和代表图。源码中有 pending split、批量准备与执行分裂等逻辑，不是一次静态 k-means 之后永远固定中心。

“代表向量”也不应一律写成算术均值。部分增量分裂路径会选择实际 token 作为新代表，具体见 `execute_split_parallel` 等函数。

## 4. coarse_search 如何近似 MaxSim

每个 query token 独立搜索代表图，得到若干簇及相似度；按相似度从高到低访问这些簇关联的文档。

对于同一个 query token，同一文档可能出现在多个簇中。实现使用 seen 缓冲区，只将第一次遇到的最高簇分数计入该文档；再对不同 query token 的贡献累加。这对应 MaxSim 的“每个 query token 取最优匹配再求和”的结构，但匹配对象由真实 token 近似为代表向量。

粗排不等于精确 MaxSim：代表向量搜索本身近似，簇代表也不能完全代替文档真实 token；某文档还可能根本没有进入被访问的簇集合。

## 5. 精排过程

按粗排分数保留至多 `rerank_k` 个文档，应用该路径的文档过滤，再对保留下来的 IDs 调用 `mv_codes_->Query`。批量 Query 为多文档读取和计算提供机会，最后按文档距离排序返回 top-k。

当前 KnnSearch 的过滤发生在粗排候选截断之后。因此高选择性过滤可能使精排集合缩小，不能认为它一定会从粗排尾部无限补齐合法结果。

IP 模式下完整 token 距离为 `query_token_count - MaxSim`。精排准确度还取决于实际保存的 token 表示；即使候选内打分精确，整个检索依旧受粗排漏召回影响。

## 6. 参数各自影响哪一段

| 参数 | 控制内容 | 取舍 |
| --- | --- | --- |
| `init_cluster_ratio` | 初始化代表数量相关比例 | 更多代表的图成本与更细的候选划分 |
| `max_cluster_size` | 簇维护 / 分裂规模 | 分裂成本、代表数量、候选膨胀 |
| `coarse_k` | 每个 query token 的簇搜索范围 | 候选覆盖与粗排工作量 |
| `rerank_k` | 完整文档评分数量 | MaxSim 与 token IO 成本 |
| `base_io_type` | 文档 token 的存放后端 | 内存占用、冷读与批量访问表现 |

提高 `rerank_k` 无法找回 coarse 阶段从未触及的文档。提高 `coarse_k` 又不保证所有新增文档都会进入固定大小的精排集合，两个预算应分别观察。

## 7. 当前并发边界

`coarse_search` 复用可变分数数组与 dirty/seen 标记；`KnnSearch` 持有 `global_mutex_` 独占锁。内部可并行执行不同 query token 的代表图查询，但这与多个调用者同时运行文档查询是两个层次。

复用数组减少哈希和频繁分配成本，代价是需要保护共享状态。进行吞吐测试时不能只看线程池大小，还要看查询锁范围。

## 8. 代码与验证路线

先读 `Build` 与成员，跟 `coarse_search` 的 token 搜索、seen 去重和分数累加，再读 `KnnSearch` 的截断、过滤、批量精排；最后看 Add 与簇分裂。

源码：[simq.h](../../../src/algorithm/simq/simq.h)、[simq.cpp](../../../src/algorithm/simq/simq.cpp)、[simq_parameter.cpp](../../../src/algorithm/simq/simq_parameter.cpp)、[multi_vector_computer.cpp](../../../src/quantization/multi_vector_computer.cpp)。示例：[114_index_simq.cpp](../../../examples/cpp/114_index_simq.cpp)。
