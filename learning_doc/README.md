# VSAG 源码学习地图

这套笔记回答三个问题：VSAG 的模块怎样协作；每种索引如何缩小搜索范围；为什么采用这些结构，以及要付出什么代价。

源码基线：`fd363937`（2026-09-10 本地同步的 `origin/main`）。这是基于该版本的学习笔记；后续源码变化时，应重新核对工厂注册、参数映射和能力声明。本文所说的“设计原因”，除明确引用的源码注释外，均是根据实现行为作出的工程分析，不等于维护者的原始设计记录。

**图解入口：** [所有索引的构成图与查询示例](indexes/visual_map.md)。HGraph 可直接从 [遍历路由专章](indexes/hgraph/traversal_walkthrough.md) 开始，跟着双堆和 visited 走完一次搜索。

**深入源码从这里开始：** [分阶段阅读路线](system_architecture/00_deep_reading_roadmap.md) → [公共接口与数据所有权](system_architecture/06_api_factory_dataset.md) → [可运行调试实验](system_architecture/12_debugging_lab.md)。新增详解覆盖请求全链路、存储字节路径、量化与 SIMD、标签与生命周期、HGraph 构图；每章带关键源码摘录、状态解释、断点变量与测试入口。

## 目录

```text
learning_doc/
├── README.md
├── system_architecture/
│   ├── README.md                         系统架构与阅读顺序
│   ├── 00_deep_reading_roadmap.md         分阶段深入阅读路线
│   ├── 01_layers_and_modules.md          分层、模块职责、设计取舍
│   ├── 02_build_and_search_flow.md       创建、构建、查询的调用链
│   ├── 03_storage_quantization_io.md     DataCell、量化、Layout、IO
│   ├── 04_filter_lifecycle_concurrency.md 过滤、更新、持久化与并发
│   ├── 05_source_reading_and_experiments.md 源码阅读与验证方法
│   ├── 06_api_factory_dataset.md         公共接口、工厂与数据所有权
│   ├── 07_query_request_pipeline.md      请求到结果完整实现
│   ├── 08_storage_byte_path.md           编码、Layout 与 IO 字节路径
│   ├── 09_quantization_simd.md           距离定义、量化与 SIMD
│   ├── 10_labels_filters_lifecycle.md    标签、过滤、删除与生命周期
│   ├── 11_hgraph_build_mutation.md       构图、插入、剪枝与发布
│   ├── 12_debugging_lab.md               已运行的本地调试实验
│   └── labs/                            教学程序与观测记录
└── indexes/
    ├── README.md                         索引关系与对比
    ├── visual_map.md                     所有索引的构成图与查询示例
    ├── brute_force/README.md
    ├── hgraph/README.md
    ├── lazy_hgraph/README.md
    ├── ivf/README.md
    ├── pyramid/README.md
    ├── sindi/README.md
    ├── sindi_v2/README.md
    ├── simq/README.md
    ├── warp/README.md
    └── mci/README.md                     HGraph 挂件，并非独立工厂入口
```

## 建议阅读顺序

希望深入实现时，以 [00 深入阅读路线](system_architecture/00_deep_reading_roadmap.md) 的逐站成果为主；下面顺序用于先建立全局架构与索引直觉。

1. [系统分层](system_architecture/01_layers_and_modules.md) → [构建与搜索调用链](system_architecture/02_build_and_search_flow.md)：先找到代码入口。
2. [BruteForce](indexes/brute_force/README.md) → [HGraph](indexes/hgraph/README.md) → [IVF](indexes/ivf/README.md)：从全量打分理解图导航与分桶裁剪。
3. [存储和量化](system_architecture/03_storage_quantization_io.md)：解释同一索引为什么可以有不同精度、内存占用和 IO 行为。
4. [LazyHGraph](indexes/lazy_hgraph/README.md)、[Pyramid](indexes/pyramid/README.md)、[MCI](indexes/mci/README.md)：理解规模、路径和过滤条件怎样改变执行策略。
5. [SINDI](indexes/sindi/README.md) → [SINDI_V2](indexes/sindi_v2/README.md)，以及 [WARP](indexes/warp/README.md) → [SIMQ](indexes/simq/README.md)：分别进入稀疏检索与多向量检索。

各索引子目录均包含 `visual_guide.md` 直观图解、`README.md` 设计说明和 `code_walkthrough.md` 代码逐段导读，建议按这个顺序阅读。图解含类比、主要构成图、逐组件解释、构建与查询过程、可手算的例子；每张新图同时保存 SVG、PNG 和可编辑 Mermaid 源码。HGraph 另有 `traversal_walkthrough.md`，详细演算层间路由、底层双堆、visited 与停止条件。代码导读给出真实摘录、基线行号、关键变量、执行顺序及边界分析；系统架构正文也包含对应源码片段。

## 阅读约定

- “候选没找到”和“候选打分不准”是两种不同误差。增加精排精度，无法找回从未进入候选集的真实近邻。
- API 中存在某方法，不代表每种索引、每种配置都支持它；要结合 `InitFeatures`、`CheckFeature` 和具体实现检查。
- 量化后的全量扫描依然可能相对原始 FP32 有误差；“扫描全部”不等于“原始精度精确”。
- 路径链接均相对当前文档，可直接跳转本地源码。优先按函数名定位，避免源码变更后行号失效。
- 05 中的性能对照表是尚未执行的扩展实验；12 及其观测记录明确区分了本轮已运行的小样本、实际断点与后续建议。小样本成功不等于性能或全配置正确性结论。

工厂依据：[index_creators.cpp](../src/factory/index_creators.cpp)。官方中文文档：[索引目录](../docs/docs/zh/src/indexes/README.md)。部分上游文档保留旧源码路径，本笔记链接按当前实际目录核对。
