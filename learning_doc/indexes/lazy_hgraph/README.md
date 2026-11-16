# LazyHGraph：把构图成本推迟到规模需要它时

[直观图解](visual_guide.md)

配套：[代码逐段导读](code_walkthrough.md) · [BruteForce](../brute_force/README.md) · [HGraph](../hgraph/README.md)

## 1. 为什么存在这个索引

一个集合只有几十或几百条数据时，建图、维护边和执行导航本身也有成本。若集合将持续增长，始终暴力扫描又会逐渐变慢。LazyHGraph 用数据量阈值把这两个阶段封装在同一个索引入口中。

它是规模驱动的状态机，不是基于查询延迟持续自学习的优化器。阈值需要结合实际负载选择。

## 2. 状态和持有对象

| 状态 | 有效对象 | 搜索方式 |
| --- | --- | --- |
| `Phase::FLAT` | `flat_index_` | 固定 FP32 BruteForce |
| `Phase::GRAPH` | `graph_index_` | 由配置构建的 HGraph |

`phase_` 记录当前阶段；`phase_mutex_` 保护阶段变化与对象生命周期；`transition_threshold_` 决定切换时机。`ActiveIndex()` 只根据阶段选择内部对象，不重新实现底层搜索。

## 3. Build 和 Add 的不同分支

Build 已经拿到完整数据：若数量小于阈值，直接建 flat；达到阈值则直接构建 HGraph，成功后进入 GRAPH 并释放 flat 对象，不必先拷一遍到 flat。

Add 则先在当前阶段插入。若 flat 的有效数量达到阈值，退出该共享锁范围后调用 `TransitionToGraph`。这样避免持有共享锁时直接尝试升级为独占锁。

## 4. TransitionToGraph 为什么要这样排序

```text
取得阶段独占锁
  → 再次确认尚未切换
  → 导出 flat 的 ID 并筛出仍有效的 ID
  → 取出有效数据
  → 创建临时 new_graph 并完整 Build
  → 检查失败 ID 为空
  → 发布 graph_index_，释放 flat，更新 phase
```

**再次确认状态**是因为多个 Add 都可能观察到达到阈值。**筛有效 ID**再次确认迁移集合有效。当前 `Remove` 在 FLAT 阶段固定向 BruteForce 传入 `FORCE_REMOVE`，所以通常已经物理移除；这里的 `CheckIdExist` 是迁移阶段的防御性检查，不能据此认为 FLAT 默认采用标记删除。GRAPH 阶段才将调用方传入的删除模式转给 HGraph。**先建临时对象再替换**使迁移构图失败时不会先丢掉旧 flat。

但触发迁移的 Add 已经写入 flat；如果随后迁移抛错，不能推断这次 Add 的所有写入都被回滚。这里不是事务式迁移，调用方必须结合返回错误和当前索引状态处理重试。

## 5. 同步切换的代价

当前迁移函数持有独占锁，而查询需要共享同一把锁，所以转换期间查询会等待。构图时旧数据、新图和临时提取数据还可能同时存在，带来峰值内存。

这是以简单、清晰的阶段一致性换取迁移时延。不能将它描述为后台异步构建、双写追平或无停顿热切换。当前也没有按集合缩小自动回退 FLAT 的对应状态转移。

## 6. 精度与参数含义

当前只接受 `dtype: float32`，flat 固定 FP32；进入图阶段后采用 HGraph 的编码和候选策略，因此会发生从全量精确扫描到近似图搜索的语义变化。

`transition_threshold` 控制规模拐点；嵌套 `hgraph` 决定转换后的构图方式。查询参数仍使用 `hgraph` 对象。阈值更高会延后构图，但增加阶段切换前的扫描量；更低则让许多小集合更早支付图成本。

## 7. 怎样验证自己的理解

把阈值设到便于观察的规模，先加入略少于阈值的数据；再用一个 Add 跨过阈值。记录这次 Add 的耗时、内存峰值和同时发生的查询等待，并检查切换前后有效 ID 一致。再加入“flat 阶段删除过记录”的情形，确认不会把删除项迁回图。

源码：[lazy_hgraph.cpp](../../../src/algorithm/lazy_hgraph/lazy_hgraph.cpp)、[lazy_hgraph.h](../../../src/algorithm/lazy_hgraph/lazy_hgraph.h)、[lazy_hgraph_parameter.cpp](../../../src/algorithm/lazy_hgraph/lazy_hgraph_parameter.cpp)。示例：[111_index_lazy_hgraph.cpp](../../../examples/cpp/111_index_lazy_hgraph.cpp)。
