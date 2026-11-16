# 系统架构

VSAG 是可嵌入应用的向量检索库。这里讨论的是单个库实例内部的结构；集群分片、RPC 服务、租户鉴权与业务事务不是这张架构图中的模块。

先读 [00 深入阅读路线](00_deep_reading_roadmap.md)，按每站的可检查成果推进；运行入口在 [12 调试实验](12_debugging_lab.md)。

| 文档 | 要回答的问题 |
| --- | --- |
| [01 分层与模块](01_layers_and_modules.md) | 外部 API、算法、存储和距离计算怎样分工？ |
| [02 构建与查询](02_build_and_search_flow.md) | 一次 `CreateIndex`、`Build`、`KnnSearch` 最终走到哪里？ |
| [03 存储、量化与 IO](03_storage_quantization_io.md) | 编码、字节布局和介质为什么要分开？ |
| [04 过滤、生命周期与并发](04_filter_lifecycle_concurrency.md) | 删除如何影响图？加载是否等于全部读入内存？并发边界在哪里？ |
| [05 阅读路线与实验](05_source_reading_and_experiments.md) | 怎样用调用链、测试和对照实验验证理解？ |
| [06 接口、工厂与 Dataset](06_api_factory_dataset.md) | 创建如何进入实际类？资源与输入指针归谁管理？ |
| [07 请求完整调用链](07_query_request_pipeline.md) | 参数、过滤、搜索上下文、路由、精排与结果怎样串起？ |
| [08 存储字节路径](08_storage_byte_path.md) | 内部 ID 怎样定位编码并进入一次距离计算？ |
| [09 量化与 SIMD](09_quantization_simd.md) | 距离约定、SQ8 误差、运行派发与尾部计算怎样实现？ |
| [10 标签与生命周期](10_labels_filters_lifecycle.md) | 删除、搬移、过滤、保存与并发保护哪些状态？ |
| [11 HGraph 构图与修改](11_hgraph_build_mutation.md) | 图边如何选出、剪枝、发布，入口怎样更新？ |
| [12 本地调试实验](12_debugging_lab.md) | 怎样用手算答案、实际运行和 LLDB 跟踪真实对象？ |

贯穿全套文档的主线是：**算法决定访问哪些候选；DataCell 提供候选数据与计算接口；量化影响表示和打分；Layout 与 IO 决定这些访问怎样落到内存或文件上。** 实际代码还存在融合实现和专用快路径，分层是职责划分，不意味着每次调用都逐层经过一个虚函数。

06–11 的源码摘录逐段解释实现，00 提供阅读顺序，12 提供可复现的入口。已有索引图解仍在 [索引图解地图](../indexes/visual_map.md)。
