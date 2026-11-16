# Pyramid：把业务路径变成搜索范围

[直观图解](visual_guide.md)

配套：[代码逐段导读](code_walkthrough.md) · [过滤与生命周期](../../system_architecture/04_filter_lifecycle_concurrency.md)

## 1. 为什么全局图加过滤不总是合适

假设所有向量混在一张图中，但每次查询只允许访问某个租户、语言或类别。过滤后有效集合很小时，全局近邻关系可能并不适合该集合，搜索大量无效点也会浪费工作。

Pyramid 把路径显式组织成树，让查询先到对应范围，再执行该范围内的图搜索或扫描。路径来自业务数据，不是向量聚类得到的几何区域。

## 2. 一个例子

```text
root
├── tenant_a
│   ├── zh
│   │   ├── news
│   │   └── wiki
│   └── en
└── tenant_b
```

查询 `tenant_a/zh` 的意图是限定在这个前缀覆盖的数据中。不能把 `tenant_a` 与 `tenant_ab` 当成字符串前缀关系直接匹配，实现按路径段查找子节点。

这是检索范围组织，不是应用鉴权。调用者仍需负责决定用户能传入哪个租户路径。

## 3. 数据结构为什么分成树节点与共享向量存储

`Hierarchy` 持有路径树；`IndexNode` 维护子节点、当前节点 ID 集合或图、节点状态和锁；向量编码由 Pyramid 持有并供节点搜索使用。这样不必为每个路径层级复制完整的向量数据和全套 HGraph 对象。

共享编码节省重复向量存储，但一条向量仍可能参与多个祖先层级或多套 hierarchy 的图/ID 结构，图关系与路径元数据仍有额外成本。

## 4. 构建过程

先解析数据路径形成树，再准备编码和节点数据。节点是否构图受层级、数据量及参数影响；可选 NSW 插入或 ODescent 构建。`IndexNode` 存在 FLAT 与 GRAPH 等执行状态，不能把树上的每个节点都理解成一张已建成的图。

小节点直接扫描可以避免图的固定开销；大节点构图可减少查询访问。`no_build_levels` 则允许跳过不值得付出构图成本的层级，并由节点状态和递归搜索逻辑决定实际处理方式。

## 5. 查询过程

```text
读取 query 的路径或 hierarchy 条件
  → 按路径段查找目标节点
  → 对有效目标调用节点搜索
  → FLAT 节点计算其 ID 集合，GRAPH 节点走图搜索
  → 汇总相关路径候选
  → 按配置精排，转换外部 ID
```

`search_hierarchy` 对每条请求路径从 root 出发，调用 `GetChild(..., false)`；某个路径段不存在时，该路径不继续搜索，不会默默退回全局根搜索。多个路径结果会在后面合并；最终的去重、预算与多 hierarchy 语义应继续跟进外层查询逻辑。

## 6. 与 HGraph 层级有什么本质区别

HGraph 的上层图为向量导航服务；Pyramid 的树层级表达业务范围。Pyramid 节点内部也可能有导航结构，所以需要区分“先选哪个业务节点”和“在该节点的数据中怎样接近 query”。

这种组合让稳定路径过滤更直接。代价是业务路径变动会牵涉路径存储和相关节点结构，不能只修改一个展示标签；任意复杂布尔条件也不能自动等价为一条路径。

## 7. 参数的设计意义

- `no_build_levels`：控制在哪些业务层级支付构图成本。
- `max_degree`、`graph_type`、ODescent 相关参数：决定节点图的质量与构建成本。
- `ef_search`、`subindex_ef_search`：控制不同搜索层次的候选预算。
- `use_reorder` 与编码参数：控制共享向量评分精度。

如果路径极深、叶子极多但每个叶子很小，树和图的管理开销可能很显著；如果只有很少宽泛路径，收益也可能有限。要结合真实路径分布估计结构大小。

## 8. 验证重点

为多个租户和语言准备数据，分别查询中间前缀、叶子、不存在路径和多个路径。确认返回范围、重复 ID 处理、路径序列化恢复一致，再比较 FLAT 与 GRAPH 节点的成本。路径正确性应先于召回和延迟优化。

源码：[pyramid.h](../../../src/algorithm/pyramid/pyramid.h)、[pyramid.cpp](../../../src/algorithm/pyramid/pyramid.cpp)、[pyramid_index_node.cpp](../../../src/algorithm/pyramid/pyramid_index_node.cpp)、[pyramid_path_store.cpp](../../../src/algorithm/pyramid/pyramid_path_store.cpp)、[pyramid_paths.cpp](../../../src/algorithm/pyramid/pyramid_paths.cpp)。
