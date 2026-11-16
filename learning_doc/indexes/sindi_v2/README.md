# SINDI_V2：让 posting 布局服从按词项读取的查询

[直观图解](visual_guide.md)

配套：[代码逐段导读](code_walkthrough.md) · [SINDI](../sindi/README.md)

## 1. 要解决的变化

SINDI 已经利用窗口控制计算工作集；当 posting 不能全部常驻内存时，还需要让文件布局对应“本次 query 实际访问哪些词项”。SINDI_V2 的 term-first 持久化结构把一个词项的数据组织在一起，减少与查询无关的数据读取。

这不是把名字加一个 V2，也不是让所有搜索都改成只遍历词项、不再使用窗口。它改变的是持久化和读取组织，同时保留窗口化累加模型。

## 2. term payload 的结构

```text
一个 term 的 payload
  non_empty_window_count
  有序 { window_id, posting_count } 列表
  local_doc_ids 数组
  对齐填充
  encoded_values 数组
```

只保存非空窗口，避免为某个稀有 term 写入大量空窗项。查询时根据这些元数据展开窗口 offset，使后续按窗口计算仍可快速定位该 term 的文档与权重。

**为什么 ID 和 value 分开？** 这种数组布局便于批量处理和对齐后的值解码；其具体收益取决于量化格式和访问内核。**代价：** 元数据解释和 offset 构建仍需要计算与内存，不是零开销随机读取。

## 3. 可变、不可变、磁盘是不同能力组合

`term_datacell_` 提供查询接口，构建和加载根据配置选用可变内存、紧凑不可变内存或磁盘 term DataCell。正排 `rerank_io` 又是独立选择。

不能因为支持文件 Build 就推断支持在文件结构上持续 Add。当前 `InitFeatures` 仅在非 immutable、非 DMQ8 rerank、term 后端为 `memory_io` 的组合声明 `SUPPORT_ADD_AFTER_BUILD`。`UpdateVector` 当前直接报告不支持。

## 4. 构建主线

检查 sparse 输入、ID 与权重，进行文档剪枝、term 映射与可选量化；选择对应构建形态，写入 posting；如需重排，另写正排；记录元数据与标签关系。SQ8 的范围估计会考虑实际保留的值，目的是让量化参数服务于最终编码的数据，而不是被丢弃项主导。

加载路径则需要恢复 term 字典、posting 布局、编码参数、label 和正排访问方式。两种过程可能选择不同后端，实际可写能力以加载后配置和能力声明为准。

## 5. 查询主线

```text
解析查询与候选预算
  → ID 过滤 / metadata 路由
  → 查询 term 映射与剪枝
  → 准备所需 term 数据及窗口定位信息
  → 对相关窗口累加并更新候选
  → 可选读取 rerank 数据重新打分
  → 返回外部 ID 与距离
```

term-first 的收益在“只读所需 posting”，但高频词的 posting 本身可能很大。查询词项越多、精排候选越多，IO 优势也可能被更多实际读取抵消。

## 6. 参数如何改变成本

| 参数 | 作用 | 要关注的代价 |
| --- | --- | --- |
| `term_io` | posting 介质与访问方式 | 冷读、缓存、随机 / 批量访问 |
| `rerank_io` | 正排表示存放位置 | 候选精排的数据读取量 |
| `immutable` | 紧凑只读构建形态 | 增量能力受限 |
| `n_candidate` | 保留候选数量 | 精排工作量和候选覆盖 |
| doc/query/term 剪枝 | 减少存储或 posting 访问 | 不同阶段的漏召回 |
| `rerank_type` | FP32 或压缩正排等配置 | 内存、评分精度与 Add 限制 |

当前 V2 对 `n_candidate == 0` 有专门处理，按内部放大系数导出候选预算，不表示“没有候选”。普通正数也受 k 倍数上限检查，应读代码而非照搬其他索引参数。

## 7. 为什么不能直接加载 SINDI 文件

SINDI 是 window-first 格式，V2 是 term-first 布局；同一批词项和权重不代表字节协议一样。改变工厂名字不会把一种布局转换为另一种。迁移应以当前支持的导出或原始数据重建流程为依据。

## 8. 代码阅读重点

先比较两版 KnnSearch 的共同部分，再看 V2 的 term 准备、磁盘 DataCell、Serialize/Deserialize，最后看 immutable 构建分支。不要一开始就把全部文件后端并行展开。

源码：[sindi_v2.cpp](../../../src/algorithm/sindi_v2/sindi_v2.cpp)、[sindi_v2_parameter.cpp](../../../src/algorithm/sindi_v2/sindi_v2_parameter.cpp)、[disk_sindi_term_datacell.h](../../../src/datacell/disk_sindi_term_datacell.h)、[disk_sindi_term_datacell.inl](../../../src/datacell/disk_sindi_term_datacell.inl)、[immutable_sindi_term_datacell.cpp](../../../src/datacell/immutable_sindi_term_datacell.cpp)。
