# 创建、构建与搜索的调用链

## 1. CreateIndex：把外部配置变成组件组合

阅读 [Factory::CreateIndex](../../src/factory/factory.cpp)、[创建器](../../src/factory/index_creators.cpp)、[IndexImpl 构造函数](../../src/index/index_impl.h)。主线可以概括为：

```text
索引名称 + JSON + 公共资源
  → Factory 准备资源并委托 Engine 解析公共参数
  → 注册表找到创建器
  → IndexImpl<T>
  → T::CheckAndMappingExternalParam
  → 内部参数对象
  → 构造 T，初始化 DataCell、Searcher 等组件与能力标志
```

公共参数通常涉及维度、输入类型、距离类型、分配器等；算法参数再决定图度数、分桶策略、量化器和 IO。外部 JSON 是用户理解的配置形态，内部参数更接近组件装配。例如 HGraph 的 `base_quantization_type` 最终要落到基础编码数据单元的参数里。

**为什么不直接到处读 JSON？** 集中映射有利于统一默认值、合法性与组件组合约束，也减少热路径里的动态解释。代价是调试参数时需要追踪“外部字段 → 映射 → 内部字段 → 实际使用点”。

## 2. Build：训练和结构组织是两件事

`IndexImpl<T>::Build` 转发到具体算法。之后不能假设所有索引都有同样的三步：

| 索引 | 训练或准备 | 数据组织 |
| --- | --- | --- |
| BruteForce | 需要训练的量化器先训练 | 保存每条编码及 ID 映射 |
| HGraph | 训练编码器、准备存储与构图参数 | 生成多层导航图和底层邻接关系 |
| IVF | 学习中心、训练所需量化器 | 分类入桶；按配置构建桶内图 |
| SINDI / V2 | 剪枝、词项重映射、可选权重量化 | 形成按窗口计算的倒排结构 |
| SIMQ | 汇总 token、形成簇和代表向量 | 代表图、簇到文档关系、多向量存储 |

训练不只是量化训练。即使 IVF 使用 FP32 存储，也可能需要学习聚类中心。反过来，FP32 BruteForce 不需要训练中心，直接追加就能形成可搜索结构。

Build/Add 的返回结果包含失败 ID；调用者除了检查外层错误，还应判断是否有未成功插入的数据，避免把部分成功当作完整构建。

## 3. HGraph 查询主线

[hgraph_search.cpp](../../src/algorithm/hgraph/hgraph_search.cpp) 中普通 `KnnSearch` 组织 `SearchRequest`，进入 `SearchWithRequest`。可按下面的逻辑读；迭代器等重载存在独立路径。

```text
query + topk + 搜索参数 + filter
  → 校验，建立 QueryContext 与统计
  → 构造外部 ID 到内部 ID 的过滤适配
  → 根据当前配置决定搜索路径
  → 上层图导航，得到底层入口
  → 底层候选扩展、visited 去重、结果堆维护
  → 如启用，做候选重排
  → 内部 ID 映射为外部 label，生成结果 Dataset
```

这里的“决定搜索路径”可能包含按有效比例触发的扫描回退、过滤场景 MCI、RaBitQ 专用路径等，不是每个请求都必然走同一套图遍历。`ef_search` 是搜索候选预算，不等于固定执行这么多次距离计算，也不是最终返回数量。

## 4. 同一个 KnnSearch，在不同索引里换了什么

BruteForce 将全体记录作为待评分集合；IVF 先选桶；Pyramid 先确定路径对应范围；SINDI 访问查询词项命中的 posting；SIMQ 先把查询 token 路由到代表向量对应的文档集合。

这些方法的共同点是最后都要形成候选与排序结果。区别首先发生在“访问哪些数据”，随后才是“怎样计算这些数据的距离”。所以调试召回时，应把候选覆盖率和候选内排序分别检查。

## 5. Dataset 与生命周期

[Dataset 接口](../../include/vsag/dataset.h) 既用于输入也用于返回。稠密向量、稀疏词项、多向量、路径和结果 IDs/Distances 都通过相关字段表达，具体算法只接受其中适用的形态。

`Owner(false)` 的输入由调用者管理内存，不能仅保留一个指向已销毁局部数组的指针。读取示例时要同时看向量维度、元素数量、ID 数组与底层缓冲区生命周期。公共 `dim` 与多向量 token 数量、稀疏词表范围不是同一个概念。

## 6. 调用链阅读入口

- 创建：[factory.cpp](../../src/factory/factory.cpp) → [index_creators.cpp](../../src/factory/index_creators.cpp)。
- 包装：[index_impl.h](../../src/index/index_impl.h) → [inner_index_interface.h](../../src/algorithm/inner_index_interface.h)。
- 请求：[search_request.h](../../include/vsag/search_request.h) → [query_context.h](../../src/query_context.h)。
- 对照查询：[BruteForce](../../src/algorithm/bruteforce/bruteforce.cpp)、[HGraph](../../src/algorithm/hgraph/hgraph_search.cpp)、[IVF](../../src/algorithm/ivf/ivf_search.cpp)。

## 7. 真实调用链：Factory 先委托 Engine

源码：[src/factory/factory.cpp](../../src/factory/factory.cpp)，基线行号 325–337。以下为连续原文摘录，可能是函数的一部分。

```cpp
Factory::CreateIndex(const std::string& origin_name,
                     const std::string& parameters,
                     Allocator* allocator) {
    std::shared_ptr<Resource> resource{nullptr};
    if (allocator == nullptr) {
        resource = std::make_shared<Resource>(Engine::CreateDefaultAllocator(), nullptr);
    } else {
        resource = std::make_shared<Resource>(allocator, nullptr);
    }
    Engine e(resource.get());
    return e.CreateIndex(origin_name, parameters);
}

```

Factory 先按 allocator 准备 Resource，再创建 Engine 并委托。并非这个函数直接解析所有 JSON；真正公共参数检查在下面的 Engine::CreateIndex。阅读资源生命周期时还应跟 ResourceOwnerWrapper 和 IndexCommonParam，不能只看局部 Engine 对象析构。

## 8. Engine 解析公共参数并捕获错误

源码：[src/factory/engine.cpp](../../src/factory/engine.cpp)，基线行号 49–69。以下为连续原文摘录，可能是函数的一部分。

```cpp
tl::expected<std::shared_ptr<Index>, Error>
Engine::CreateIndex(const std::string& origin_name, const std::string& parameters) {
    try {
        register_all_index_creators();
        auto parsed_params = JsonType::Parse(parameters);
        auto index_common_params = IndexCommonParam::CheckAndCreate(parsed_params, this->resource_);
        return create_registered_index(origin_name, parsed_params, index_common_params);
    } catch (const std::invalid_argument& e) {
        LOG_ERROR_AND_RETURNS(
            ErrorType::INVALID_ARGUMENT, "failed to create index(invalid argument): ", e.what());
    } catch (const std::bad_alloc& e) {
        LOG_ERROR_AND_RETURNS(
            ErrorType::NO_ENOUGH_MEMORY, "failed to create index(not enough memory): ", e.what());
    } catch (const vsag::VsagException& e) {
        LOG_ERROR_AND_RETURNS(e.error_.type, "failed to create index: " + e.error_.message);
    } catch (const std::exception& e) {
        LOG_ERROR_AND_RETURNS(
            ErrorType::UNSUPPORTED_INDEX, "failed to create index(unknown error): ", e.what());
    }
}

```

注册内置创建器、解析 JSON、构建 IndexCommonParam、调用注册表是顺序依赖。无效参数、内存不足和内部异常被转换为 expected 的错误结果。调用者不应无条件 value()；示例为缩短展示使用 value() 时，生产调用仍需判断 has_value。

## 9. 查询先转为统一请求

源码：[src/algorithm/hgraph/hgraph_search.cpp](../../src/algorithm/hgraph/hgraph_search.cpp)，基线行号 50–63。以下为连续原文摘录，可能是函数的一部分。

```cpp
HGraph::KnnSearch(const DatasetPtr& query,
                  int64_t k,
                  const std::string& parameters,
                  const FilterPtr& filter,
                  Allocator* allocator) const {
    SearchRequest req;
    req.query_ = query;
    req.topk_ = k;
    req.filter_ = filter;
    req.params_str_ = parameters;
    req.threshold_ = ParseSearchThreshold(parameters);
    req.search_allocator_ = allocator;
    return this->SearchWithRequest(req);
}
```

query、topk、filter、JSON 参数、距离阈值与 allocator 被写入 SearchRequest，再交给 SearchWithRequest。入口重载负责适配调用形态；内部主流程负责执行。迭代器重载是另一路径，不能由这段推断所有 KnnSearch 都完全等价。
