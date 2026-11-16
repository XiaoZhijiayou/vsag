# IVF：从入口逐层展开函数调用

[返回 IVF 设计](README.md) · [构成图与手算](visual_guide.md) · [逐函数完整源码与调用点](function_reference/README.md) · [递归调用树](call_trees.md) · [真实 14 层调用栈](runtime_stack.md)

源码基线：`fd363937`。本文替代原来的短摘录版。先读下列调用树，再沿函数参考中的链接进入每一个被调函数。

## 1. 怎样读这里的“调用栈”

这里同时展示两种信息：**静态调用树**列出源码允许发生的分支；**运行时栈**是某个线程停在某个时刻的活动函数。`Train()` 已返回后，`Add()` 才执行，所以两者是 Build 下的兄弟调用，不能同时放在一条运行时栈上。

约定：`[条件]` 表示条件成立才执行；`[循环]` 表示反复调用；`[工作线程]` 表示由线程池调度；`[返回]` 表示值回到父函数。虚函数列出实际实现的分派依据。标准库、分配器、系统 I/O、BLAS/SIMD 是边界，调用点保留，具体机器实现由编译和运行环境决定。用户传入的过滤器、距离回调，其实现不在 VSAG 仓库内。

**完整保留函数体，避免短摘录隐藏调用。** [函数参考](function_reference/README.md)保留完整函数体，并逐一列出显式调用表达式的源码位置、外围条件和可继续阅读的实现。构造、析构、运算符重载、宏展开后的隐式调用不能仅凭静态文本当作真实运行帧；需要第 12 节的 LLDB 方法确认。

## 2. 先把参与调用的对象分开

| 成员 | 职责与编号 | 构造阶段决定什么 |
| --- | --- | --- |
| `partition_strategy_` | 输入向量，输出 bucket ID | IVFNearestPartition 或 GNOIMIPartition |
| `route_index_ptr_` | 普通 IVF 可选的中心 HGraph；节点是中心 | `use_route_graph` 决定中心图/中心扫描 |
| `bucket_` | 每桶存放编码、posting ID、桶内 offset | 量化类型、I/O、残差模式 |
| `bucket_graphs_` | 可选的桶内图；节点是桶内 offset | `graph_build_threshold` 决定是否构建 |
| `bucket_searcher_` | 搜索一个已选定的桶 | FlatBucketSearcher 或 GraphBucketSearcher |
| `reorder_` | 粗候选重新算分 | BucketReorder 或 FlattenReorder |
| `label_table_` | origin ID 与用户 label 的映射、删除过滤 | 对外身份与内部数组位置分离 |
| `location_map_` | origin ID → 打包后的 bucket/offset | 按 ID 找编码、精排定位 |

中心图与桶内图是两个独立开关。查询可能“扫描中心＋桶内图”，也可能“中心图＋平扫桶”。不能见到 HGraph 就认为最终数据都在一张图里。

## 3. 创建索引：先决定后面的虚调用会进入谁

完整实现：[IVF 构造与其他成员](function_reference/ivf.md)。

```text
IVF::IVF(param, common_param)
├─ InnerIndexInterface(param, common_param) [基类状态]
├─ BucketInterface::MakeInstance(bucket_param, common_param)
│  └─ 按量化类型、I/O 类型实例化 BucketDataCell<QuantTmpl, IOTmpl>
├─ [需要独立线程池] FactoryDefaultThreadPool → SetPoolSize
├─ [partition_strategy_type == IVF] IVFNearestPartition(...)
│  └─ [use_route_graph] factory_router_index(...)
│     ├─ HGraph::CheckAndMappingExternalParam(...)
│     └─ 构造 HGraph，中心编码为 FP32
├─ [partition_strategy_type == GNO_IMI] GNOIMIPartition(...)
├─ [use_reorder && precise_codes_layout == bucket]
│  ├─ BucketInterface::MakeInstance(精排桶参数)
│  └─ BucketReorder(precise_bucket, location_resolver)
│     └─ 保存回调：inner_id → IVF::get_location(inner_id)
├─ [use_reorder && 其他精排布局]
│  ├─ FlattenInterface::MakeInstance(...)
│  └─ FlattenReorder(reorder_codes, allocator)
├─ [use_residual] bucket_->SetStrategy(partition_strategy_)
└─ [graph_build_threshold > 0] GraphBucketSearcher(...)
   [否则保留初始化列表中的 FlatBucketSearcher]
```

构造阶段主要建立对象依赖，尚未把业务数据写入桶。`location_resolver` 是保存起来以后调用的 lambda；构造 BucketReorder 的时刻不会查询每个候选的位置。

## 4. Build：训练、写入、建桶图的完整主干

完整函数与所有直接调用：[ivf_build](function_reference/ivf_build.md)。

```text
IVF::Build(base)
├─ [启用桶图] CHECK_ARGUMENT(total_elements_ == 0)
├─ IVF::Train(base)
│  ├─ [is_trained_] return
│  ├─ Dataset::GetNumElements / GetDim
│  ├─ sample_train_data(data, N, dim, train_sample_count_, allocator_)
│  │  └─ [返回] 用于训练的 Dataset
│  ├─ partition_strategy_->Train(train_data) → 第 5 节
│  ├─ bucket_->Train(sample_vectors, sample_count) → 第 6 节
│  ├─ [use_reorder && precise_bucket] precise_bucket_->Train(全量数据)
│  ├─ [use_reorder && 无 precise_bucket] reorder_codes_->Train(全量数据)
│  └─ is_trained_ = true
├─ IVF::Add(base) → 第 7 节
├─ [graph_build_threshold_ > 0] IVF::build_bucket_graphs() → 第 9 节
├─ IVF::cal_memory_usage()
└─ [返回] Add 返回的 failed-ID 列表
```

这里至少有两种训练：中心训练决定向量落哪个桶，编码训练决定向量怎样存和算分。FP32 编码训练可以很轻，中心训练依然存在。`Train` 的状态位在最后设置；Add 不负责自动补一次训练，未训练会抛错。

`Build` 不是数据库事务。某个后续阶段抛异常，不代表前面修改过的所有成员都自动回滚。尤其 Add 写 label、精排数据、桶数据的时序，要逐行看第 7 节。

## 5. 分区训练和路由：再向下展开一层

完整实现：[普通分区](function_reference/ivf_nearest_partition.md)、[分区基类](function_reference/ivf_partition_strategy_h.md)、[GNO-IMI](function_reference/gno_imi_partition.md)、[KMeans](function_reference/kmeans_cluster.md)。

### 5.1 普通 IVF 的 Train

```text
IVFNearestPartition::Train(dataset)
├─ Dataset::Make → Ids / Dim / Float32Vectors / NumElements / Owner(false)
│  └─ 中心 ID = 0..bucket_count-1，也就是 bucket ID
├─ [KMeansTrainer] KMeansCluster::Run(k, vectors, N, 25)
│  ├─ 检查 k、N、数据指针、k <= N
│  ├─ allocator_->Deallocate / Allocate [旧中心释放、新中心分配]
│  ├─ [初始化方法] select_initial_centroids_random / ...kmeans_plus_plus
│  └─ [每轮迭代]
│     ├─ [k 小] NearestCentroidAssign(..., labels)
│     ├─ [k 大] find_nearest_one_with_hgraph(..., labels)
│     ├─ [每个数据块] GeneralEnqueue(update_centroids_func, ...)
│     │  ├─ BlasFunction::Saxpy [累加向量]
│     │  └─ [归并方式] 固定块缓冲 / 加锁归并
│     ├─ future.wait [等待工作完成]
│     ├─ BlasFunction::Sscal [按成员数取均值]
│     ├─ [空簇] 随机样本补中心
│     └─ [满足收敛条件] break
│  [返回] labels；中心保存在 cls.k_centroids_
├─ [RandomTrainer] select_k_numbers → memcpy [样本直接充当中心]
├─ [cosine] Normalize [逐中心归一化]
├─ [use_route_graph] route_index_ptr_->Build(centroids)
│  └─ HGraph 构建的是中心图；失败中心列表非空则抛错
└─ [中心扫描] 保存 centroids_；准备 norms_
   ├─ [L2] FP32ComputeIP(c,c,dim) / 2
   └─ [IP/cosine] norms_ 填 1
```

不要把 `KMeansCluster::Run` 中为训练加速临时使用的 HGraph，与最终中心路由图混为一谈。它们在不同阶段解决不同问题。25 是传入的迭代上限，提前收敛可使实际轮数更少。

### 5.2 普通 IVF 的 ClassifyDatasForSearch

```text
IVFPartitionStrategy::ClassifyDatasForSearch(datas, count, param, ctx)
└─ 虚调用 ClassifyDatas(datas, count, param.scan_bucket_size, ctx)
   └─ IVFNearestPartition::ClassifyDatas(...)
      ├─ [无中心图] classify_datas_by_scan(...)
      │  ├─ [未训练/空输入/k=0] 返回 INVALID_BUCKET_ID 填充的数组
      │  ├─ [cosine] Normalize(query)
      │  ├─ compute_centroid_dots(query, centroids, dots, count, B, dim)
      │  │  └─ BlasFunction::Sgemm [query × centroids 转置]
      │  ├─ [每 query、每中心] candidate = (norms_[b]-dots[b], b)
      │  ├─ heap.push/top/pop [保留最小 k 个排序键]
      │  └─ [返回] 有序 bucket IDs
      └─ [有中心图] 每条输入构造单查询 Dataset
         ├─ fmt::format [中心图 ef=max(10, buckets_per_data*1.2)]
         ├─ route_index_ptr_->KnnSearch(query, 桶数, params, nullptr)
         │  └─ HGraph 查询 → 返回中心 labels
         ├─ GetIds / GetDim → 拷入 bucket ID 数组
         └─ [有 ctx.stats] 汇总路由统计
```

对固定 query，L2 的排序键 `||c||²/2-q·c` 与真实平方距离同序，因为乘 2 后只差与中心无关的 `||q||²`。这个键可以用来选桶，但不能直接作为最终业务向量距离返回。`route_buckets_only` 会重新计算中心距离。

### 5.3 GNO-IMI 有自己的覆盖实现

`GNOIMIPartition::ClassifyDatasForSearch` 覆盖基类实现，不会沿上一节直接进入普通中心图。

```text
GNOIMIPartition::ClassifyDatasForSearch
├─ [cosine] Normalize
├─ matmul(query, data_centroids_s_) → S 组点积
├─ matmul(query, data_centroids_t_) → T 组点积
├─ [每个 query] norms_s - dot_s → 堆排序 S 候选
├─ floor(Bs * first_order_scan_ratio)，至少取 1 个 S 中心
├─ [选中的 S × 全部 T]
│  ├─ 使用 precomputed_terms_st_ 与 dot_t 计算联合排序键
│  ├─ global_bucket_id = s_id * Bt + t_id
│  └─ heap.emplace/pop [保留 scan_bucket_size 个联合桶]
└─ [返回] bucket ID 数组；更新 ROUTING 统计
```

第一阶比例控制考察哪些组合；最终桶数控制保留多少组合。两个参数作用在不同循环，调大最终桶数不能恢复根本没有考察的 S 分支。

## 6. 从 Bucket::Train 继续到编码与计算器

完整实现：[BucketDataCell](function_reference/bucket_datacell_h.md)、[Computer](function_reference/computer_h.md)、[量化接口](function_reference/quantizer_h.md)、[FP32](function_reference/fp32_quantizer.md)。

```text
BucketDataCell::Train(data, count)
├─ [use_residual]
│  ├─ [cosine] Normalize
│  ├─ strategy_->ClassifyDatas(data, count, 1, nullptr)
│  ├─ [每条数据] strategy_->GetCentroid(bucket_id, centroid)
│  └─ train_data_buffer = vector - centroid
└─ quantizer_->Train(data 或 residual, count)
   └─ 量化器模板的 TrainImpl；具体模型由 QuantTmpl 决定

BucketDataCell::FactoryComputer(query)
├─ quantizer_->FactoryComputer()
├─ [use_residual] 保留 raw_query_，cosine 时 Normalize
├─ Computer<QuantTmpl>::SetQuery(query)
│  └─ quantizer_->ProcessQuery(query, computer)
│     └─ 对应量化器的 ProcessQueryImpl
└─ [返回] 绑定了本次 query 的计算器

BucketDataCell::encode_vector(vector, bucket_id, codes, res_score)
├─ [无残差] quantizer_->EncodeOne(vector,codes) → return
└─ [残差]
   ├─ strategy_->GetCentroid(bucket_id,...)
   ├─ [cosine] Normalize
   ├─ FP32Sub(vector,centroid,sub_data)
   ├─ quantizer_->EncodeOne(sub_data,codes)
   └─ [L2] DecodeOne + FP32ComputeIP → 残差距离补偿项
```

训练与编码必须使用同一语义空间。如果训练的是残差、写入却编码原向量，量化范围和查询补偿都会错。`FactoryComputer` 把 query 的预处理移到扫桶前；一个 query 扫很多条编码时可以复用准备好的计算器。

## 7. Add：每个嵌套调用怎样改变存储

```text
IVF::Add(base)
├─ [分区未训练] throw VsagException
├─ bucket_->Unpack [需要时恢复可追加布局]
├─ [precise_bucket] precise_bucket_->Unpack
├─ Dataset getters [N、IDs、vectors、attributes、extra_info]
├─ partition_strategy_->ClassifyDatas(vectors,N,buckets_per_data_,nullptr)
├─ [label_lookup_mutex_ 临界区]
│  ├─ 记录 current_num，检查精排桶 ID 容量
│  ├─ [扁平精排] reorder_codes_->BatchInsertVector
│  ├─ [每条] label_table_->Insert(i+total_elements_, ids[i])
│  ├─ total_elements_ += N
│  └─ location_map_.resize
├─ [精排桶] precise_bucket_->BatchInsertVector(..., precise_offsets)
├─ [每条数据 i] GeneralEnqueue(add_func,i) / 直接 add_func(i)
│  └─ [每个归属桶 j]
│     ├─ posting_id = (i+current_num)*buckets_per_data_ + j
│     ├─ [精排桶] bucket_->InsertVectorWithOffset(..., precise_offsets[idx])
│     ├─ [其他] bucket_->InsertVector(...) → offset_id
│     │  └─ encode_vector → quantizer EncodeOne；写桶编码、posting ID
│     ├─ [j == 0] 更新 location_map_[origin_id]
│     ├─ [属性输入存在] attr_filter_index_->Insert(attr,offset,bucket)
│     └─ [extra_info_size > 0] extra_infos_->InsertExtraInfo(...,origin_id)
├─ [线程池] 对所有已提交任务 future.get
├─ [收集到异常] rethrow_exception
├─ bucket_->Package；[精排桶] precise_bucket_->Package
├─ [到统计间隔] cal_memory_usage
└─ return {}
```

精排桶模式先写精排镜像，再发布基础 posting，保证基础候选可见时能定位到相应精排数据。它不是所有布局都通用的操作次序；扁平精排在更早的临界区批量写入。

四套编号必须分别记：例如 origin ID=7，`buckets_per_data=2`，其 posting ID 是 14、15。14 可以在桶 3 的 offset 5，15 可以在桶 9 的 offset 1。桶图搜索返回的是 5/1，先查桶的 `ids[offset]` 得到 14/15，再除以 2 得到 7，最后查 label 表得到用户 ID。不能用 offset 直接除以 2。

`Add` 等待已提交任务完成后再重抛首个异常，可以避免任务仍引用已退出作用域的局部数据；但源码没有整体撤销之前 label/桶写入的事务代码。

## 8. SearchWithRequest：所有一级分支和返回位置

完整源码：[ivf_search](function_reference/ivf_search.md)。这个函数较长，参考页展示整个函数，而不是只截选桶前的几十行。

```text
IVF::KnnSearch
├─ ParseSearchThreshold(parameters)
└─ IVF::SearchWithRequest(req)
   ├─ ValidateSearchThreshold
   ├─ create_search_param
   │  ├─ create_search_filter → 删除过滤 + InnerIdWrapperFilter + 可选 CombinedFilter
   │  ├─ IVFSearchParameters::FromJson
   │  └─ [计时开启] Timer::SetThreshold
   ├─ [custom distance] 检查批大小、KNN、单线程等；关闭精排
   ├─ [显式 bucket_ids] 检查 query 数、dim、桶范围、重复项
   ├─ [disable_bucket_scan]
   │  └─ route_buckets_only → Statistics → return [返回桶，不返回业务记录]
   ├─ [query 数 > 1]
   │  ├─ 分配固定 query_count × topk 输出，填 -1/+inf
   │  ├─ 每条构造 one_request，内部 parallelism 置 1
   │  ├─ [工作线程或同步] SearchWithRequest(one_request) [递归]
   │  └─ 拷贝每条结果 → Statistics → return
   ├─ [属性过滤] AstParse / 使用现成 expression
   │  └─ 每个线程 Executor::MakeInstance → Init
   ├─ [expected_labels] 初始化 ReasoningContext
   │  ├─ TryGetIdByLabel → get_location
   │  ├─ bucket_->FactoryComputer → QueryOneById
   │  └─ SetTrueDistance [额外诊断算分]
   ├─ [custom distance]
   │  └─ search_with_custom_distance → threshold过滤 → pack/empty → return
   ├─ [Range]
   │  ├─ search<RANGE_SEARCH>
   │  └─ reorder 或 pack_knn_result → Statistics/Reasoning → return
   └─ [KNN]
      ├─ [精排] param.topk = factor × request.topk_
      ├─ search<KNN_SEARCH> → 第 9 节
      ├─ [精排] reorder → FilterDatasetByThreshold → return
      └─ [无精排] filter_search_result_by_threshold
         └─ pack_knn_result / empty → Statistics/Reasoning → return
```

批查询是一次公开请求里再次执行单条查询；并行任务拥有不同调用栈。普通 Search 的桶任务也是另一层并发，因此批量分支把子请求的桶并行度压成 1。

`factor` 是候选预算，`scan_buckets_count` 是路由覆盖，`ef_search` 是桶内图探索预算。它们分别作用在三个阶段。把 factor 调大不会自动多访问几个桶。

## 9. search 到桶内图/平扫：全部主干

```text
IVF::search<mode>(query,param,ctx,reasoning)
├─ [显式桶] 复制 param.bucket_ids
├─ [默认路由] partition_strategy_->ClassifyDatasForSearch → 第 5 节
├─ [reasoning] RecordBucketSelection
├─ bucket_->FactoryComputer(query_data) → 第 6 节
├─ 计算 topk；[多归属桶] 乘 buckets_per_data_，检查溢出
├─ 每线程创建结果 heap、dist 缓冲
├─ [工作线程或同步] search_func(thread_id)
│  └─ [fetch_add 动态领取每个桶]
│     ├─ [超时/无效桶] break
│     └─ bucket_searcher_->Search(...)
│        ├─ FlatBucketSearcher::Search → 9.1
│        └─ GraphBucketSearcher::Search → 9.2
├─ [并行] future.get → 合并各线程 heap
├─ [多归属桶] posting_id / buckets_per_data_ → origin_id
│  └─ 相同 origin 保留最小距离；裁剪回 origin_topk
└─ [返回] 由 origin ID 标识的候选堆
```

### 9.1 平扫一直展开到算距离

```text
FlatBucketSearcher::Search
├─ bucket->GetBucketSize / GetInnerIds
├─ dist.resize [空间不足时]
├─ bucket->ScanBucketById(dist,computer,bucket_id)
│  └─ BucketDataCell::scan_bucket_by_id
│     ├─ check_valid_bucket_id；持有桶共享锁
│     ├─ [每批最多 32 条]
│     │  ├─ datas_[bucket_id].Acquire(offset*code_size, count*code_size)
│     │  ├─ lease.Data → 当前编码字节
│     │  └─ Computer::ScanBatchDists(count,codes,out)
│     │     └─ Quantizer::ScanBatchDists
│     │        └─ FP32Quantizer::ScanBatchDistImpl [FP32 配置]
│     │           └─ [逐编码] ComputeDistImpl → FP32ComputeL2Sqr / FP32ComputeIP
│     ├─ [残差] GetCentroid / FP32ComputeIP / FP32Sub → 距离补偿
│     └─ [空 posting] 对应距离设为最大值
├─ stats->AddDistance [本桶实际扫描条数]
├─ [属性过滤] executors[thread_id]->Clear → Run(bucket_id)
├─ [每条 offset]
│  ├─ 跳过 EMPTY posting；posting → origin
│  ├─ [reasoning] RecordVisit
│  ├─ [KNN threshold] 剔除非有限值，按精排状态决定有限阈值判断
│  ├─ attr_filter->CheckValid(offset)
│  ├─ is_inner_id_allowed->CheckValid(origin)
│  │  └─ 包装过滤器将 origin 转换成外部 label 后调用用户过滤器
│  ├─ [KNN 候选更好 / Range 半径内] heap->Push
│  └─ heap->Pop / Top [控制容量、更新最差保留距离]
└─ [返回 void] 修改传入 heap、dist、统计
```

顺序非常关键：这里是**先算整个桶的距离，再逐条过滤**。用户过滤掉 90% 的结果，不代表能减少 90% 的桶扫描距离计算。属性过滤用 offset；普通过滤用 origin；包装器再负责 label 转换。

### 9.2 桶内图的入口和回退

```text
GraphBucketSearcher::Search
├─ GetBucketSize
├─ 检查图存在、图 TotalCount == bucket_size、达到建图阈值
├─ [全部满足] search_graph
│  ├─ GetInnerIds → 找首个非空 offset 作为 entry
│  ├─ [没有有效节点] return
│  ├─ [属性] Executor::Clear → Run(bucket_id)
│  ├─ KNN: ef=max(ef,topk)，再 min(ef,bucket_size)
│  ├─ BucketDistanceProvider(bucket,bucket_id,computer,ids,buckets_per_data)
│  ├─ VisitedList(bucket_size)；BasicSearcher(allocator)
│  ├─ BasicSearcher::Search(graph,provider,visited,search_param,attr_filter,ctx)
│  │  └─ 图邻居展开、visited、候选堆、结果堆
│  │     └─ provider 的 query distance 调用桶编码距离接口
│  ├─ [每个候选] local_id → ids[local_id] → heap->Push
│  └─ heap->Pop [裁剪到本次结果上限]
└─ [任一不满足] flat_searcher_->Search → 9.1
```

Add 后桶大小可能大于旧图节点数，此时平扫回退保证新 posting 不会因旧图覆盖不足而被直接排除。`RebuildBucketGraphs` 显式重建；不是每次查询自动重建。

### 9.3 桶内图是怎样建出来的

```text
IVF::build_bucket_graphs
├─ [阈值未开启] return
├─ [缺少参数] 构造 GraphDataCellParameter
├─ bucket_graphs_.resize(bucket_count)
└─ [每个桶] build_one_bucket(b) [可在线程池运行]
   ├─ GetBucketSize / GetInnerIds
   ├─ 收集有效 local IDs；不足阈值 return
   ├─ effective_degree=min(64,有效数-1)；非正 return
   ├─ GraphInterface::MakeInstance → Resize / SetTotalCount / SetMaximumDegree
   ├─ 首节点 InsertNeighborsById(空邻接表)
   └─ [逐个后续节点 node]
      ├─ ef=min(300,已插入数)，ep=首节点
      ├─ PairwiseBucketDistanceProvider(bucket,b,node)
      ├─ VisitedList::Reset
      ├─ BasicSearcher::Search → 候选旧节点
      │  └─ ComputePairVectors(bucket,node,other_local_id)
      └─ mutually_connect_new_element → 邻居筛选、双向连接
   [完成] bucket_graphs_[b] = 新图
```

建图需要节点对节点距离，查询需要 query 对节点距离，所以使用不同的 distance provider。两者都以桶内 local ID 工作，不能直接换成全局 label。

## 10. 重排和结果封装，继续追到 label

```text
IVF::reorder(topk,input,query,param,ctx,...)
├─ reorder_->Reorder(input,query,topk,ctx,...,threshold)
│  ├─ [BucketReorder]
│  │  ├─ select_query_allocator；限制 topk <= candidate_count
│  │  ├─ precise_bucket->FactoryComputer(query)
│  │  ├─ [每个 origin] location_resolver_(origin)
│  │  │  └─ IVF::get_location → 解包 bucket_id、offset_id
│  │  ├─ precise_bucket->Query(dist,computer,bucket_ids,offset_ids,count,&ctx)
│  │  └─ [每个精确分] threshold / heap Push、Pop / reasoning
│  └─ [FlattenReorder]
│     └─ 以 origin ID 在扁平精排编码中查询，重建距离堆
├─ InnerIndexInterface::pack_knn_result(heap,alloc)
│  ├─ [空堆] make_empty_result
│  ├─ create_fast_dataset(count,alloc)
│  └─ [j 从 count-1 递减到 0]
│     ├─ dists[j] = heap->Top().first
│     ├─ ids[j] = label_table_->GetLabelById(heap->Top().second)
│     └─ heap->Pop
└─ [返回] Dataset，距离从小到大，ID 已恢复为业务 label
```

大顶堆先弹最差候选，所以倒着填输出数组。`pack_knn_result` 会消耗输入堆；调试时在它返回后再看堆为空，是正常结果。

精排只重新计算已有候选。目标所在桶没有被选中，或者目标已被粗排预算淘汰，精排不会凭空找回来。使用 threshold 时要区分粗距离的非有限值排除与最终精确距离阈值。

## 11. 自定义距离、持久化和维护也不能跳过

`search_with_custom_distance` 的完整体在 [ivf_search](function_reference/ivf_search.md)：选桶后收集 posting → 属性过滤 offset → posting 转 label → 满批调用 `request.distance_batch_func_` → 检查分数 → 普通过滤 origin → 入堆 → 多桶去重。其 `submit_batch` 和 `is_timed_out` 两个 lambda 都在参考页中保留。普通过滤发生在回调打分之后，不能照搬“先过滤再评分”的假设。

持久化完整实现见 [ivf_serialize](function_reference/ivf_serialize.md)。需要同时读 `Serialize`、`collect_streaming_header`、`serialize_streaming_body`、`read_streaming_body`、`Deserialize`，区分头部元数据与实际数组/编码的字节流。每个函数的调用点索引可以继续进入被序列化的分区和 BucketDataCell。不能只保存中心就宣称整个 IVF 保存成功。

维护完整实现见 [ivf_modify](function_reference/ivf_modify.md) 和 [ivf_build](function_reference/ivf_build.md)：

```text
IVF::Remove(ids,mode)
└─ [MARK_REMOVE] label_table_->MarkRemove(ids) → 更新 delete_count_
   [其他 mode] 此实现返回初始的 0

IVF::UpdateAttribute(id,...)
├─ label_table_->GetIdByLabel(id)
├─ get_location(inner_id)
└─ attr_filter_index_->UpdateBitsetsByAttr(...,offset,bucket)

IVF::RebuildBucketGraphs
├─ 检查开启桶图、float32 类型
├─ 保存 old_graphs，准备新图容器
├─ build_bucket_graphs → cal_memory_usage
└─ [异常] 恢复 old_graphs 后重新抛出

IVF::fill_location_map
├─ 检查基础桶与精排桶数量、长度及同位置 ID 一致
├─ [每个有效 posting] 检查 ID 范围
└─ location_map_[posting/buckets_per_data] = bucket/offset
```

`Remove` 标记的是记录有效性，不会从每个桶的编码数组中立刻擦除字节。`RebuildBucketGraphs` 对图容器有显式异常恢复；不能据此推断整个 Build/Add 都提供同样保证。

## 12. 怎样得到真正的运行时调用栈

下列为通用断点说明；本次已实际采集的 14 层完整栈另见 [运行时栈与复现](runtime_stack.md)。使用 Debug 构建的 IVF 示例或自己的程序，先选单 query、单线程、FP32、无精排，避免一开始就混入所有分支。

```lldb
(lldb) breakpoint set -n 'vsag::IVF::Build'
(lldb) breakpoint set -n 'vsag::IVF::Train'
(lldb) breakpoint set -n 'vsag::IVF::Add'
(lldb) breakpoint set -n 'vsag::IVF::SearchWithRequest'
(lldb) breakpoint set -n 'vsag::FlatBucketSearcher::Search'
(lldb) breakpoint set -n 'vsag::GraphBucketSearcher::search_graph'
(lldb) run
(lldb) bt
(lldb) frame variable
(lldb) thread step-in
(lldb) thread backtrace all
```

如果函数重载或模板使名字匹配不明确，使用函数参考给出的源文件和行号：`breakpoint set --file ivf_search.cpp --line <对应行>`。在工作线程中停住时，`bt` 会显示线程池入口，不会把已提交任务的主线程伪装成它的调用者；使用 `thread backtrace all` 查看两边，再用 task 参数联系起来。

| 停点 | 必看变量 | 要回答的问题 |
| --- | --- | --- |
| Train 结束前 | `is_trained_`、分区中心、量化器类型 | 中心和编码都准备好了吗？ |
| Add 的 `add_func` | `i,j,idx,posting_id,offset_id,current_num` | 四套编号如何对应？ |
| search 路由完成 | `candidate_buckets,param.topk,buckets_per_data_` | 探索多少桶，保留多少 posting？ |
| FlatBucketSearcher 扫描后 | `bucket_size,ids,dist` | 哪些数据已被算分？ |
| GraphBucketSearcher 分派前 | `has_graph,graph_fresh,bucket_size` | 实际图搜还是回退平扫？ |
| pack_knn_result | `heap->Top()`、输出 `ids[j]` | 内部 ID 何时恢复为 label？ |

最后做三组对照：只增大扫描桶数；只增大 factor；只增大桶图 ef。分别记录命中的分支、距离计算数和最终结果。这样才能把源码里的三个预算与实际行为一一对应。
