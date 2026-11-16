# 源码阅读与对照实验

新增的 [00 深入阅读路线](00_deep_reading_roadmap.md) 将本章展开为逐站阅读任务；[12 本地调试实验](12_debugging_lab.md) 提供已经运行过的小样本、诊断数字和真实调用栈。以下性能扩展实验仍保留为后续建议。

## 1. 先沿一条最短路径走通

从 [105_index_brute_force.cpp](../../examples/cpp/105_index_brute_force.cpp) 出发，依次读 Factory、IndexImpl、BruteForce 的 Build/Add/SearchWithRequest、DataCell 的 Query 和结果堆。先把数据数量、外部 ID、内部 ID 和距离看懂，再进入更复杂算法。

接着看 [103_index_hgraph.cpp](../../examples/cpp/103_index_hgraph.cpp)，保持 Dataset 和结果读取不变，只追踪多出来的“导航、扩展、visited、邻接表、重排”。最后读 [106_index_ivf.cpp](../../examples/cpp/106_index_ivf.cpp)，用“选桶与桶内扫描”替换图搜索。

## 2. 使用本地编译数据库

当前仓库根目录 [compile_commands.json](../../compile_commands.json) 链接到 `build/compile_commands.json`，对应最近完成的 Debug/Ninja 构建。编辑器可据此找到头文件路径和编译宏。

当前构建未启用测试、工具和示例，所以编译数据库没有自动包含全部测试源文件。这里链接示例是用于阅读，不代表它们已经编译运行。若要执行实验，再按 [构建说明](../../docs/agents/build-and-test.md) 选择所需构建选项。

## 3. 读一个索引时，固定检查六件事

1. `CheckAndMappingExternalParam`：输入类型、默认值、互斥参数和隐式映射。
2. 构造函数：持有哪些图、编码、label、过滤器和线程资源。
3. Build/Add：训练、编码、结构更新与失败 ID 如何处理。
4. KnnSearch/SearchWithRequest：入口校验、候选生成、过滤、精排和结果转换。
5. InitFeatures：本配置声明哪些能力，再与方法实际限制交叉核对。
6. Serialize/Deserialize：哪些状态要保存，加载时怎样保证兼容。

## 4. 建议实验：分别控制候选、精度和访问成本

这些实验尚未执行，目的是帮助验证设计理解；请使用相同数据、查询和距离定义，并记录配置与提交版本。

| 实验 | 固定内容 | 只改变 | 重点观察 |
| --- | --- | --- | --- |
| HGraph 搜索预算 | 同一已建图、同一编码 | `ef_search` | Recall@k、距离计算量、p50/p95 延迟 |
| IVF 桶扫描 | 同一中心与数据 | `scan_buckets_count` | 候选覆盖、桶大小倾斜、扫描量 |
| 量化误差 | 使用全量扫描排除导航漏召回 | FP32 与压缩编码 | 排名变化、内存占用、打分耗时 |
| 精排效果 | 同一批候选 | 是否精排及精排表示 | 候选内排序改善，而非候选覆盖变化 |
| LazyHGraph 切换 | 相同插入批次与查询集 | 阈值上下的数据量 | 切换那次 Add 耗时、峰值内存、查询等待 |
| 稀疏剪枝 | 同一稀疏数据 | doc/query/term 剪枝开关 | 召回、posting 访问量、构建与查询成本 |
| SIMQ 两阶段 | 同一代表图 | `coarse_k` / `rerank_k` 分别改变 | 候选文档覆盖、MaxSim 计算量、IO 耗时 |

Recall@k 可按每个查询的 `|近似结果 ∩ 精确结果| / k` 计算，再对查询求平均；若有效集合不足 k，应预先约定分母。处理距离并列时也要保持一致。稠密 ground truth 可用 FP32 BruteForce；多向量应使用相同 MaxSim 定义的全量基线。稀疏数据需要独立核对剪枝、零得分与负值语义，不能默认一个激进剪枝配置就是精确基准。

## 5. 读测试时优先找边界

源码目录中的 `*_test.cpp` 有助于理解内部状态；[tests](../../tests/) 中的功能测试更适合确认外部 API 行为。特别关注空集合、重复 ID、删除后搜索、序列化往返、过滤后结果不足 k、路径不存在、阶段切换等场景。

## 6. 后续同步代码后怎样维护笔记

先比较 [index_creators.cpp](../../src/factory/index_creators.cpp) 的注册变化，再检查算法参数、能力声明、调用链和存储布局。更新时记录新的 commit。保持“实现事实”“工程推断”“实验结果”三者分明；只有运行过的实验才填写实际数据。

## 7. 用能力代码推导测试组合

源码：[src/algorithm/ivf/ivf_build.cpp](../../src/algorithm/ivf/ivf_build.cpp)，基线行号 62–80。以下为连续原文摘录，可能是函数的一部分。

```cpp
        IndexFeature::SUPPORT_SERIALIZE_FILE,
        IndexFeature::SUPPORT_SERIALIZE_WRITE_FUNC,
    });

    auto name = this->bucket_->GetQuantizerName();
    if (name != QUANTIZATION_TYPE_VALUE_FP32 and name != QUANTIZATION_TYPE_VALUE_BF16 and
        name != QUANTIZATION_TYPE_VALUE_FP16) {
        this->index_feature_list_->SetFeature(IndexFeature::NEED_TRAIN);
    } else {
        this->index_feature_list_->SetFeatures({
            IndexFeature::SUPPORT_RANGE_SEARCH,
            IndexFeature::SUPPORT_RANGE_SEARCH_WITH_ID_FILTER,
        });
    }

    bool has_fp32 = false;
    if (use_reorder_) {
        const auto precise_quantizer_name = precise_bucket_ != nullptr
                                                ? precise_bucket_->GetQuantizerName()
```

先列共同声明的序列化能力，再观察 name 对 NEED_TRAIN 与范围搜索声明的影响。由此可设计不同量化组合的 API 测试，但最终仍需验证实际调用；不能仅断言一个布尔值就认为算法行为已经被覆盖。也要注意这里 NEED_TRAIN 标志针对所检查的编码，不概括全部分区训练。
