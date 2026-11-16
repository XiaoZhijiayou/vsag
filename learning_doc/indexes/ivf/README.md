# IVF：先缩小到几个桶，再计算桶内候选

[直观图解](visual_guide.md)

配套：[逐层源码讲解](code_walkthrough.md) · [递归调用树](call_trees.md) · [完整函数参考](function_reference/README.md) · [真实运行时调用栈](runtime_stack.md)

建议先看真实栈，理解一次查询如何从 API 走到距离计算；再读逐层源码讲解，补齐构建、路由、过滤、精排和维护。完整函数参考保留整个函数体及 lambda，并按源码行列出所有可识别的显式调用点；虚分派和系统边界单独标明。

## 1. 为什么分桶能减少查询工作

IVF 使用中心或分区模型，把空间组织成若干倒排桶。查询先找到相关桶，再访问桶内记录。它把“所有数据都要评分”改成“先判断哪些区域值得评分”。

若 B 个桶大小近似均匀、每条记录只入一桶、每次扫描 P 个桶，桶内扫描量可粗略理解为 N×P/B。这个估计不包含路由中心的开销；桶倾斜、多桶分配和桶内图搜索也会改变它。

## 2. 核心组件

| 组件 | 职责 |
| --- | --- |
| `partition_strategy_` | 训练分区模型；为构建数据和查询选择桶 |
| `bucket_` | 保存基础编码、桶内记录与相关映射 |
| `precise_bucket_` / `reorder_codes_` | 按配置提供精排表示 |
| Flat / Graph bucket searcher | 决定桶内全量扫描还是图搜索 |
| label、location 等映射 | 关联外部 ID、内部编号和桶内位置 |

`IVFPartitionStrategy` 将路由与桶内容拆开，所以可以切换普通 IVF 和 GNO-IMI 等策略，而不把所有桶存储逻辑重写一遍。

## 3. 构建流程

`Build` 调用 `Train`，再调用 `Add`，按配置构建桶内图，最后更新内存统计。Train 采样训练数据，学习路由模型并训练所需编码器；Add 分类、编码、写桶，同时维护计数和映射。

中心是对数据分布的近似摘要。用样本训练可以减少构建开销，但样本不代表真实分布时可能出现大桶和空桶。持续追加数据也不意味着中心会持续在线重训，分布漂移需要单独评估。

## 4. 查询流程

```text
解析 scan_buckets_count 等参数
  → partition_strategy 分类查询、选桶
  → 对选中桶执行相应桶内搜索
  → 汇总候选并按预算保留
  → 如果启用，精排候选
  → 输出外部 ID 与距离
```

选桶与桶内搜索有两种不同误差：真实邻居可能在未选桶里，也可能在桶内近似搜索中没被找到。精排仅处理已进入候选的记录，不能替代扫描更多桶。

## 5. 为什么大桶可以再加图

纯 IVF 假设桶内扫描已经足够便宜；严重偏斜或桶数量较少时，一个大桶仍可能很贵。当前实现可以根据 `graph_build_threshold` 构建桶内图，形成“粗分桶 + 局部图”的组合。

这使桶内搜索更灵活，也增加图内存、构建与增量维护约束。代码有 fresh Build 检查和 `RebuildBucketGraphs`，说明桶内图状态是需要维护的额外结构，不能认为 Add 之后永远无需关注它。

## 6. 为什么 GNO-IMI 独立为分区策略

它通过两级中心组织更细的组合分区。把所有组合显式作为一次普通中心扫描，可能带来过高路由成本；策略层允许分阶段选择。具体分类和参数约束应读 `gno_imi_partition.cpp`，不要只把它写成“桶数量乘一下”。

## 7. 参数与取舍

| 参数 | 增大或启用的含义 | 代价 / 注意点 |
| --- | --- | --- |
| `buckets_count` | 更细分区 | 训练和路由成本、空桶与小桶管理开销 |
| `scan_buckets_count` | 查询覆盖更多桶 | 更多候选与 IO |
| `factor` | 扩大送入后续评分的候选预算 | 额外精排，不改变已选桶覆盖 |
| `base_quantization_type` | 改变桶内编码 | 表示误差、训练与访存变化 |
| `use_reorder` | 重评候选 | 高精度数据读取与计算 |
| `graph_build_threshold` | 对达到条件的桶建立图 | 多一层近似结构和维护工作 |

## 8. 和 HGraph 怎样比较

HGraph 通过局部连接自适应探索；IVF 首先依赖全局分区。IVF 的批量桶访问较容易组织，但是否比图更快、更省内存取决于桶大小、编码、选桶数与附加图结构。应在同一召回目标下比较，而不是固定一组默认参数直接判断优劣。

当前公开输入按 FP32 Dataset 使用。Add-after-Build 等能力与具体编码组合有关，当前 PQFS 桶路径不声明增量追加支持。

源码：[ivf.h](../../../src/algorithm/ivf/ivf.h)、[ivf_build.cpp](../../../src/algorithm/ivf/ivf_build.cpp)、[ivf_search.cpp](../../../src/algorithm/ivf/ivf_search.cpp)、[ivf_partition_strategy.h](../../../src/algorithm/ivf/ivf_partition_strategy.h)、[gno_imi_partition.cpp](../../../src/algorithm/ivf/gno_imi_partition.cpp)、[graph_bucket_searcher.cpp](../../../src/algorithm/ivf/graph_bucket_searcher.cpp)。
