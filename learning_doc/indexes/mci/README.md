# MCI：HGraph 的过滤搜索挂件

[直观图解](visual_guide.md)

配套：[代码逐段导读](code_walkthrough.md) · [HGraph](../hgraph/README.md)

## 1. 它不是独立工厂索引

当前工厂创建时使用 `hgraph`，由 `use_mci` 或相关构建参数启用 MCI。`src/algorithm/mci` 是团结构的构建相关代码，执行搜索还涉及 `src/impl/searcher/mci_searcher.cpp`。

它复用 HGraph 的向量编码，并额外保存团与成员关系。不要调用 `CreateIndex("mci", ...)`。

## 2. 为什么过滤会改变图搜索难度

普通图主要按向量近邻组织，但过滤可能只留下很小比例的数据。原本有效的搜索路径可能经过很多不可返回的节点；简单禁止访问不合法节点又可能损害连通性。

MCI 将局部相互连接的点组织为团相关结构，提供一条面向过滤负载的搜索路径。其意图是利用较丰富的组内关系探索合法候选，减少对单一原图路径的依赖；这属于从结构与路由行为推导的工程解释，不是无条件性能保证。

## 3. 存储与构建

构建器取得 KNN 图，可从 HGraph 底图派生，也可单独使用 ODescent。随后形成团及成员关系，存入 CliqueDataCell。一个节点可能属于多个团，节点数、团数和总 membership 数是不同的量。

这里的 MCI 名称涉及 maximal clique，但实现还使用规模上限和构建参数，不应把它直接解释成对任意输入图完成无限制的所有极大团枚举。应查看候选图处理、剪枝和上限如何约束实际构建工作。

## 4. 何时走 MCI

HGraph 在适用的过滤查询路径下比较 `Filter::ValidRatio()` 与阈值，并检查 MCI 是否存在及本次是否启用，选择普通 HGraph 或 MCI。

当前源码还要求具备有效 ID 或 bitset seed 来源、没有这条路径不支持的属性 executors，并且挂件覆盖当前数据；RangeSearch 不走该分支。仅设置 use_mci 并提供一个任意 Filter，不保证触发 MCI。

有效比例是搜索规划信息；过滤器估计不准确可能让系统走到成本不合适的路径。提高或降低阈值改变的是“哪些查询使用挂件”，不是直接改变一个固定搜索循环的候选数。

## 5. MCI 搜索中的两个去重集合

搜索需要区分已经访问的节点和已经访问的团。一个节点可以通过多个团遇到，一个团也可以被不同节点引出；若只做一种去重，可能重复扩展或反复计算。

`mci_searcher.cpp` 中有 epoch 标记结构：通过增加 tag 复用 marks 数组，避免每个查询全量清零；tag 溢出时再清空。专用路径使用线程局部存储，复用工作集以减少分配成本。

seed 数量由集合规模和 `mci_seed_ratio` 决定，并受有效点数量限制。增加 seed 提高起点覆盖机会，同时带来更多初始计算。最终候选仍受搜索预算和合法性条件约束。

## 6. 为什么不所有查询都使用它

团关系会消耗额外内存和构建时间；Add 也需要维护挂件。过滤不强时，普通 HGraph 可能已经足够高效，再走额外团结构未必划算。这解释了为什么它是可选挂件并有查询级路由阈值。

向量数据共享不代表总内存几乎不变：应观察团数、总 membership、平均团大小、覆盖率与 MCI 内存，而不只看新增向量数。

## 7. 生命周期与限制

在已有初始索引上追加时，HGraph 可以更新 MCI，尝试把新点加入合适团或创建新团。官方说明不建议把它当成从空索引持续 Add 即可形成完整初始 MCI 的流程。

团信息跟随 HGraph 保存和恢复。验证时应比较加载前后过滤查询结果与挂件统计，不能只验证 HGraph 向量数量相同。

## 8. 参数与阅读顺序

先看 `use_mci`、`mci_knng_source` 的构建分支，再看 `hgraph_valid_ratio_threshold` 的路由，随后进入 `MCISearcher`。`mci_mcs`、`mci_clique_max` 等影响团构建；`mci_seed_ratio` 影响查询起点；两类参数不要混用。

源码：[hgraph_mci.cpp](../../../src/algorithm/hgraph/hgraph_mci.cpp)、[mci_builder.cpp](../../../src/algorithm/mci/mci_builder.cpp)、[mci_searcher.cpp](../../../src/impl/searcher/mci_searcher.cpp)、[clique_datacell.h](../../../src/datacell/clique_datacell.h)。官方说明：[HGraph MCI 挂件](../../../docs/docs/zh/src/advanced/hgraph_mci_companion.md)。
