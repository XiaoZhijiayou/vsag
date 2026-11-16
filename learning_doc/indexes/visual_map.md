# 索引图解地图：先看组成，再跟着一次查询走

[返回索引总览](README.md) · [学习地图](../README.md)

这组图解覆盖当前 9 个索引入口及 MCI 挂件。每篇都从直观类比开始，给出主要组成、图中各部分的职责、构建与查询的箭头逻辑，以及能逐步跟踪的小例子。

图是基于 `fd363937` 源码整理的结构示意，不是性能测试结果。图中节点坐标为排版服务，不等价于真实向量坐标；用于演示的距离、集合和缩小后的规模均需结合正文的前提理解。

## 1. 先从 HGraph 入手

如果你现在想回答“图由什么构成，搜索究竟怎么走”，依次读：

1. [HGraph 直观构成图](hgraph/visual_guide.md)：图层、向量编码、标签映射和搜索状态各自是什么。
2. [HGraph 遍历路由专章](hgraph/traversal_walkthrough.md)：跟随 `A → D → F` 下沉，再观察底层候选队列、结果堆、visited 和停止条件的每一步变化。
3. [HGraph 代码导读](hgraph/code_walkthrough.md)：回到真实成员、Build 分支、查询与构图剪枝代码。

读完后，应能画出上层与底层的区别，解释为什么同一个节点在不同层有不同邻居，并且不再把“待探索队列”与“当前结果集合”混为一谈。

## 2. 全部索引的图解入口

| 图解 | 重点看图中的什么 | 查询中最重要的一次转变 |
| --- | --- | --- |
| [BruteForce](brute_force/visual_guide.md) | label、扁平记录、Computer、结果堆 | 全部有效记录 → 距离最小的 k 项 |
| [HGraph](hgraph/visual_guide.md) | 上层导航、底层邻接图、向量编码、两类堆 | 单个入口 → 沿图不断扩展的候选集合 |
| [LazyHGraph](lazy_hgraph/visual_guide.md) | flat/graph 两阶段与切换锁 | 小集合扫描 → 达阈值后同步构图 |
| [IVF](ivf/visual_guide.md) | 中心路由、桶、桶内搜索、精排表示 | 全部桶 → 被选中的少量桶 |
| [Pyramid](pyramid/visual_guide.md) | 业务路径树、节点状态、共享向量编码 | 请求路径 → 对应范围内的图搜或扫描 |
| [SINDI](sindi/visual_guide.md) | 窗口、词项 posting、累加数组、正排 | 查询词项 → 命中文档的累积分数 |
| [SINDI_V2](sindi_v2/visual_guide.md) | term 字典、payload、查询读缓冲、窗口 offset | 查询保留词项 → 只准备所需 posting |
| [WARP](warp/visual_guide.md) | 文档、token 组、MaxSim Computer、文档堆 | token 两两匹配 → 文档级分数 |
| [SIMQ](simq/visual_guide.md) | 代表图、簇到文档表、token 存储、精排 | 查询 token 命中的簇 → 候选文档 |
| [MCI](mci/visual_guide.md) | HGraph 挂件、节点与团的 membership、seed | 过滤条件 → 合法种子与团成员探索 |

## 3. 每篇按同一顺序读

**先分清“长期存什么”与“这次查询临时做什么”。** 图、桶、倒排、向量编码和 label 通常是索引状态；Computer、候选队列、visited、窗口分数数组或 query term buffers 是查询执行中需要的状态。部分实现会复用缓冲，因此其锁与并发边界要结合正文看。

**再逐条看箭头的意义。** 一条箭头可能表示持有关系、ID 映射、读取依赖、构建生成，或查询数据流。每篇提供图例，不应把所有箭头都理解为“底层真的存了一条图边”。只有 HGraph 等具体邻接图示例中标明的边才表达节点连接。

**最后跟一个请求走一遍。** 找到输入从哪里进入、在哪一步缩小候选、在哪一步计算距离、在哪一步过滤、什么时候输出；检查有没有一种未被访问的数据，后续精排无法补救。

## 4. 图解与源码各解决什么

`visual_guide.md` 用结构和小例子建立直觉；`README.md` 展开设计原因与代价；`code_walkthrough.md` 逐段解释真实实现。HGraph 另有 `traversal_walkthrough.md`，专门把层间路由和层内遍历连起来。

每张图同时提供本地 SVG 图片和可编辑 Mermaid 源码。图片用于直接阅读，折叠的图源用于后续跟随代码更新。源码链接以当前仓库路径为准。
