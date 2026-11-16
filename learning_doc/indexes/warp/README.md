# WARP：复用 BruteForce 的多向量全量检索

[直观图解](visual_guide.md)

配套：[代码逐段导读](code_walkthrough.md) · [SIMQ](../simq/README.md)

## 1. 先确定当前实现是什么

工厂中的 `create_warp_index` 给配置加入内部 `_warp_mode` 标记，然后创建 `IndexImpl<BruteForce>`。BruteForce 的参数映射据此选择多向量 DataCell。

因此，当前 `warp` 是多向量扫描入口，不应因为名称与外部算法相似，就套用某篇论文中不同的压缩、路由或剪枝流程。仓库也没有单独的 `src/algorithm/warp` 实现目录。

## 2. 一条文档为什么有多个向量

单向量模型把整篇文档压成一个向量；多向量模型保留若干 token 级表示，让不同查询 token 能分别匹配不同文档 token。文档长度是 token 数，`dim` 是每个 token 向量的维度，两者必须区分。

设查询 token 为 q₁…qₘ，文档 token 为 d₁…dₙ，MaxSim 相似度为：

```text
MaxSim(Q,D) = Σ_i max_j inner_product(q_i, d_j)
```

当前 `MultiVectorComputer` 在 IP 下累加每个 query token 的最小距离：

```text
distance(Q,D) = Σ_i min_j [1 - inner_product(q_i, d_j)]
              = m - MaxSim(Q,D)
```

所以返回值不是 `1 - MaxSim`。固定同一 query 时，两者排序一致，但距离阈值和跨 query 分数比较不能忽略 m。该公式针对非空 token 集合，边界行为仍应看调用校验。

## 3. 数据结构与构建

外部通过 `MultiVector` 提供 `len_` 和 token 数组，Dataset 还带文档 IDs 和 MultiVectorDim。BruteForce 多向量模式训练对应编码器，把整篇文档作为一个逻辑记录写入 `MultiVectorDataCell`，维护文档 ID 到存储记录的关系。

变长文档不能简单用 `doc_id × D` 定位；需要保存长度与字节区间等信息。内部 token 编码则决定一个 token 如何还原或参与计算。

## 4. 查询过程

扫描每个有效文档，取其 token 表示，计算 query token 对文档 token 的匹配，再用文档级结果堆保留 top-k。输出 ID 是文档 ID，不是单个 token 的 ID。

设每个查询有 m 个 token，文档平均 n 个 token，token 维度为 D，N 篇文档的朴素 MaxSim 工作量约 O(NmnD)。这解释了为什么全量多向量检索通常比单向量扫描昂贵，也解释了 SIMQ 为什么先做文档候选筛选。

## 5. 为什么复用 BruteForce

遍历文档 ID、过滤、堆维护、label 转换和持久化的大部分职责与单向量扫描相同；差异主要是“一条记录的编码和评分”。把差异放入 DataCell 与 Computer，可避免维护另一份几乎相同的扫描算法。

代价是同一个 BruteForce 类有多向量分支；单向量与多向量的删除、原始数据读取和训练行为也不完全相同。阅读时要追踪 `is_multi_vector_`，不能直接沿用单向量能力表。

## 6. 精确性与使用边界

FP32 token 上的全量匹配可作为同一距离定义下的多向量基线。若配置改变 token 表示精度，应重新判断相对原始输入的误差。当前多向量强制删除有额外限制，不能因为 BruteForce 单向量支持 FORCE_REMOVE 就推断 WARP 支持。

如果需要大规模多向量候选加速，可比较 SIMQ；比较时要固定相同文档 token、query token、ID 集合及距离公式。不能拿单向量 BruteForce 的结果作为 MaxSim 真值。

## 7. 源码路线

1. [index_creators.cpp](../../../src/factory/index_creators.cpp)：查看 `_warp_mode` 注入。
2. [bruteforce.cpp](../../../src/algorithm/bruteforce/bruteforce.cpp)：看参数映射、`train_multi_vector`、`add_multi_vector`、`make_search_computer`。
3. [multi_vector_datacell.h](../../../src/datacell/multi_vector_datacell.h)：看变长记录读写和批量 Query。
4. [multi_vector_computer.cpp](../../../src/quantization/multi_vector_computer.cpp)：核对 token 双循环与距离公式。

应能回答：文档 ID 与 token ID 哪里分开？为什么 query token 数会影响返回距离常数？哪些外层代码完全无需知道 MaxSim 细节？
