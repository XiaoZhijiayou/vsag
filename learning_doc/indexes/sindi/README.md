# SINDI：利用稀疏性，把全维计算变成倒排累加

[直观图解](visual_guide.md)

配套：[代码逐段导读](code_walkthrough.md) · [SINDI_V2](../sindi_v2/README.md)

## 1. 为什么稀疏向量需要不同结构

一条稀疏向量只保存少量 `(term_id, value)`。内积只取共同非零词项的贡献：`score(q,d) = Σ q[t] × d[t]`。若先把它补成巨大稠密向量再逐维计算，会浪费大量零值空间和计算。

倒排表从“文档有哪些词”反向组织为“一个词出现在哪些文档”。查询只沿自己的词项查找 posting，将贡献累加到对应文档。

## 2. 用三篇文档理解计算

```text
d0 = {a: 2, b: 1}
d1 = {b: 3, c: 1}
d2 = {c: 2}
q  = {a: 1, b: 2}

a 的 posting → d0 加 1×2
b 的 posting → d0 加 2×1，d1 加 2×3
得到 score(d0)=4，score(d1)=6，score(d2)=0
```

按当前内积距离约定，距离是 `1 - score`，所以 d1 的距离更小。这个小例子仅演示无剪枝 FP32 累加；零贡献文档是否进入最终结果，还应读具体候选入堆逻辑。

## 3. 为什么引入 window

SINDI 按内部文档 ID 划分固定窗口，每个窗口维护词项 posting。查询可以复用长度为 `window_size` 的临时分数数组，处理完一个窗口再进入下一个，避免为整个大集合分配同样大小的累加数组。

窗口还让局部文档编号更紧凑，便于针对一个工作集进行累加和候选处理。代价是需要遍历窗口并管理每窗元数据；高频词依然可能产生大量 posting 工作。

## 4. 数据结构

| 组件 | 含义 |
| --- | --- |
| `term_datacell_` | 当前可变或不可变倒排结构，通过 QueryWindow 等接口访问 |
| `SparseTermComputer` | 查询词项、剪枝参数及窗口计算相关状态 |
| window 大小的 `dists` | 当前窗口中各文档的累积分数或内部距离表示 |
| `rerank_flat_` 等正排存储 | 按文档读取稀疏向量，对候选重新评分 |
| term mapper | 把稀疏的外部词项编号映射成紧凑内部编号 |
| metadata filter | 结合元数据确定可跳过窗口及有效文档 |

当前实现复用了 `MutableSindiTermDataCell` 与 `ImmutableSindiTermDataCell` 等组件，不应按旧路径寻找已删除的 `sparse_term_datacell.cpp`。

## 5. 构建流程与每个优化的含义

构建读取每篇文档的稀疏项，检查与整理数据，按需剪去贡献较弱的项、映射 term ID、编码权重，再写入倒排结构。若启用重排，还会保存用于重评候选的正排数据。

`doc_prune_ratio` 在构建时删项，之后单靠提高查询预算无法恢复已从基础 posting 删除的信息。量化压缩保存的值，带来评分误差；term 重映射压缩编号空间，它本身与有损权重剪枝不是同一回事。

## 6. 搜索过程

`KnnSearch` 检查单条 sparse query，解析参数和候选上限，处理过滤与元数据路由，按需映射查询 term。`search_impl` 逐窗口调用 `QueryWindow`，通过相应入堆路径提取候选，按配置重排，最后生成外部 ID 和距离。

因此，窗口循环负责调度；倒排计算细节在 DataCell 与 Computer；结果堆负责全局候选预算。阅读时要同时跟这三个位置。

## 7. 三种剪枝不能混为一谈

| 参数类别 | 发生时机 | 为什么可能损失召回 |
| --- | --- | --- |
| doc 剪枝 | 建索引 | 某些文档贡献不再保存在基础倒排里 |
| query 剪枝 | 查询预处理 | 部分查询词项不参与候选计算 |
| term posting 剪枝 | 倒排访问 | 部分词项命中文档不再累加 |
| `n_candidate` | 候选阶段 | 排在候选预算外的文档不进入精排 |

若开启重排，正排表示可能修正候选分数，但无法保证召回被前面剪枝完全排除的文档。带负权重、距离并列等数据时，还要额外核对剪枝假设。

## 8. 输入与范围边界

`dtype` 为 `sparse`，`metric_type` 为 `ip`。当前文档约定 `dim` 为单条稀疏向量允许的最大非零项数，`term_id_limit` 则限定词项 ID 空间，不能把两者都当成稠密维度。

SINDI 与 SINDI_V2 相同的是评分问题和窗口模型，主要区别之一是持久化与 term 访问布局。需要按词项在磁盘或 Reader 上读取时，继续读 V2。

源码：[sindi.cpp](../../../src/algorithm/sindi/sindi.cpp)、[sindi_parameter.cpp](../../../src/algorithm/sindi/sindi_parameter.cpp)、[sparse_term_computer.h](../../../src/quantization/sparse_quantization/sparse_term_computer.h)、[mutable_sindi_term_datacell.cpp](../../../src/datacell/mutable_sindi_term_datacell.cpp)、[sindi_metadata_filter.cpp](../../../src/algorithm/sindi_metadata_filter.cpp)。
