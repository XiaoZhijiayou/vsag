# IVF：主函数递归调用树

[主讲解](code_walkthrough.md) · [逐函数源码](function_reference/README.md)
以下按显式调用表达式递归展开已绑定的仓库实现。每个节点带文件与行号；同一实现再次出现时保留引用编号，避免递归和公共函数导致无限重复。条件见每个调用后的标注与完整源码；文本顺序是源码顺序，不是函数参数的求值承诺。虚分派候选用“候选”标出，未绑定项用“边界”标出，绝不把未解析调用伪装成叶子实现。

## IVF::Build

[完整函数与全部调用点](function_reference/ivf_build.md#L104)

```text
#1 IVF::Build [src/algorithm/ivf/ivf_build.cpp:104]
  ├─ CHECK_ARGUMENT  [L107] if_statement@106 (graph_build_threshold_ > 0)
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ this->Train  [L110] 函数本体；短路求值/提前返回见源码
  │  #2 IVF::Train [src/algorithm/ivf/ivf_build.cpp:120]
  │    ├─ data->GetNumElements  [L126] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ data->GetDim  [L127] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ vsag::sample_train_data  [L129] 函数本体；短路求值/提前返回见源码
  │    │  #3 sample_train_data [src/utils/util_functions.cpp:234]
  │    │    ├─ std::min  [L243] 函数本体；短路求值/提前返回见源码
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ std::max  [L243] 函数本体；短路求值/提前返回见源码
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ vsag::SafeAllocator::FactoryDefaultAllocator  [L256] if_statement@253 (allocator != nullptr) [else 分支]
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ owned_allocator.get  [L257] if_statement@253 (allocator != nullptr) [else 分支]
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ sampled_indices.reserve  [L263] 函数本体；短路求值/提前返回见源码
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ std::min  [L265] 函数本体；短路求值/提前返回见源码
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ sampled_indices.resize  [L266] 函数本体；短路求值/提前返回见源码
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ std::iota  [L267] 函数本体；短路求值/提前返回见源码
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ sampled_indices.begin  [L267] 函数本体；短路求值/提前返回见源码
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ sampled_indices.end  [L267] 函数本体；短路求值/提前返回见源码
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ random_seed.has_value  [L269] conditional_expression@269 random_seed.has_value()
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ rd  [L269] conditional_expression@269 random_seed.has_value()
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ dist  [L272] for_statement@270 i < total_elements
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ sampled_data_buffer.resize  [L277] 函数本体；短路求值/提前返回见源码
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ data->GetFloat32Vectors  [L278] 函数本体；短路求值/提前返回见源码
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ std::copy  [L280] for_statement@279 i < sample_count
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ sampled_data_buffer.data  [L282] for_statement@279 i < sample_count
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ safe_allocator->Allocate  [L285] 函数本体；短路求值/提前返回见源码
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ std::copy  [L286] 函数本体；短路求值/提前返回见源码
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ sampled_data_buffer.begin  [L286] 函数本体；短路求值/提前返回见源码
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ sampled_data_buffer.end  [L286] 函数本体；短路求值/提前返回见源码
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ std::make_shared<DatasetImpl>  [L288] 函数本体；短路求值/提前返回见源码
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ sampled_dataset->NumElements(sample_count) ->Dim(dim) ->Float32Vectors(new_data_buffer) ->Owner  [L289] 函数本体；短路求值/提前返回见源码
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ sampled_dataset->NumElements(sample_count) ->Dim(dim) ->Float32Vectors  [L289] 函数本体；短路求值/提前返回见源码
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ sampled_dataset->NumElements(sample_count) ->Dim  [L289] 函数本体；短路求值/提前返回见源码
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ sampled_dataset->NumElements  [L289] 函数本体；短路求值/提前返回见源码
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ data->GetIds  [L293] if_statement@293 (data->GetIds() != nullptr)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ sampled_ids.reserve  [L294] if_statement@293 (data->GetIds() != nullptr)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ data->GetIds  [L295] if_statement@293 (data->GetIds() != nullptr)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ sampled_ids.push_back  [L297] if_statement@293 (data->GetIds() != nullptr) → for_statement@296 i < sample_count
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ safe_allocator->Allocate  [L301] if_statement@293 (data->GetIds() != nullptr)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ std::copy  [L302] if_statement@293 (data->GetIds() != nullptr)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ sampled_ids.begin  [L302] if_statement@293 (data->GetIds() != nullptr)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ sampled_ids.end  [L302] if_statement@293 (data->GetIds() != nullptr)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ sampled_dataset->Ids(new_ids_buffer)->Owner  [L304] if_statement@293 (data->GetIds() != nullptr)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ sampled_dataset->Ids  [L304] if_statement@293 (data->GetIds() != nullptr)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ train_data->GetNumElements  [L130] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ partition_strategy_->Train  [L132] 函数本体；短路求值/提前返回见源码
  │    │  ├─ 以下为分派/重载候选，并非全部依次执行
  │    │  #4 GNOIMIPartition::Train [src/algorithm/ivf/gno_imi_partition.cpp:88]
  │    │    ├─ Dataset::Make  [L91] 函数本体；短路求值/提前返回见源码
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ Dataset::Make  [L92] 函数本体；短路求值/提前返回见源码
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ dataset->GetFloat32Vectors  [L93] 函数本体；短路求值/提前返回见源码
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ dataset->GetNumElements  [L94] 函数本体；短路求值/提前返回见源码
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ norm_vectors.resize  [L97] if_statement@96 (metric_type_ == MetricType::METRIC_TYPE_COSINE)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ Normalize  [L99] if_statement@96 (metric_type_ == MetricType::METRIC_TYPE_COSINE) → for_statement@98 i < num_element
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ norm_vectors.data  [L99] if_statement@96 (metric_type_ == MetricType::METRIC_TYPE_COSINE) → for_statement@98 i < num_element
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ norm_vectors.data  [L101] if_statement@96 (metric_type_ == MetricType::METRIC_TYPE_COSINE)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ std::iota  [L109] 函数本体；短路求值/提前返回见源码
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ ids_centroids_s.begin  [L109] 函数本体；短路求值/提前返回见源码
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ ids_centroids_s.end  [L109] 函数本体；短路求值/提前返回见源码
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ std::iota  [L110] 函数本体；短路求值/提前返回见源码
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ ids_centroids_t.begin  [L110] 函数本体；短路求值/提前返回见源码
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ ids_centroids_t.end  [L110] 函数本体；短路求值/提前返回见源码
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ centroids_s->Ids(ids_centroids_s.data()) ->Dim(dim) ->Float32Vectors(data_centroids_s_tmp.data()) ->NumElements(this->bucket_count_s_) ->Owner  [L111] 函数本体；短路求值/提前返回见源码
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ centroids_s->Ids(ids_centroids_s.data()) ->Dim(dim) ->Float32Vectors(data_centroids_s_tmp.data()) ->NumElements  [L111] 函数本体；短路求值/提前返回见源码
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ centroids_s->Ids(ids_centroids_s.data()) ->Dim(dim) ->Float32Vectors  [L111] 函数本体；短路求值/提前返回见源码
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ centroids_s->Ids(ids_centroids_s.data()) ->Dim  [L111] 函数本体；短路求值/提前返回见源码
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ centroids_s->Ids  [L111] 函数本体；短路求值/提前返回见源码
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ ids_centroids_s.data  [L111] 函数本体；短路求值/提前返回见源码
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ data_centroids_s_tmp.data  [L113] 函数本体；短路求值/提前返回见源码
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ centroids_t->Ids(ids_centroids_t.data()) ->Dim(dim) ->Float32Vectors(data_centroids_t_tmp.data()) ->NumElements(this->bucket_count_t_) ->Owner  [L116] 函数本体；短路求值/提前返回见源码
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ centroids_t->Ids(ids_centroids_t.data()) ->Dim(dim) ->Float32Vectors(data_centroids_t_tmp.data()) ->NumElements  [L116] 函数本体；短路求值/提前返回见源码
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ centroids_t->Ids(ids_centroids_t.data()) ->Dim(dim) ->Float32Vectors  [L116] 函数本体；短路求值/提前返回见源码
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ centroids_t->Ids(ids_centroids_t.data()) ->Dim  [L116] 函数本体；短路求值/提前返回见源码
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ centroids_t->Ids  [L116] 函数本体；短路求值/提前返回见源码
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ ids_centroids_t.data  [L116] 函数本体；短路求值/提前返回见源码
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ data_centroids_t_tmp.data  [L118] 函数本体；短路求值/提前返回见源码
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ cls.Run  [L128] lambda@125（定义体，执行时间取决于调用/调度）
  │    │    │  #5 KMeansCluster::Run [src/impl/cluster/kmeans_cluster.cpp:48]
  │    │    │    ├─ VsagException  [L60] if_statement@59 (k == 0)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ VsagException  [L63] if_statement@62 (count == 0)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ VsagException  [L66] if_statement@65 (datas == nullptr)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ VsagException  [L69] if_statement@68 (k > count)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ allocator_->Deallocate  [L73] if_statement@72 (k_centroids_ != nullptr)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ allocator_->Allocate  [L77] 函数本体；短路求值/提前返回见源码
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ random_seed.has_value  [L80] conditional_expression@80 random_seed.has_value()
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ rd  [L80] conditional_expression@80 random_seed.has_value()
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ select_initial_centroids_kmeans_plus_plus  [L83] if_statement@82 (init_method == KMeansInitMethod::KMEANS_PLUS_PLUS)
  │    │    │    │  #6 KMeansCluster::select_initial_centroids_kmeans_plus_plus [src/impl/cluster/kmeans_cluster.cpp:305]
  │    │    │    │    ├─ first_dis  [L311] 函数本体；短路求值/提前返回见源码
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ FP32ComputeL2Sqr  [L323] for_statement@318 c < k → for_statement@322 i < count
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ std::min  [L324] for_statement@318 c < k → for_statement@322 i < count
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ dis  [L334] for_statement@318 c < k → if_statement@332 (total_weight <= 0.0)
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ prob_dis  [L342] for_statement@318 c < k
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ select_initial_centroids_random  [L85] if_statement@82 (init_method == KMeansInitMethod::KMEANS_PLUS_PLUS) [else 分支]
  │    │    │    │  #7 KMeansCluster::select_initial_centroids_random [src/impl/cluster/kmeans_cluster.cpp:290]
  │    │    │    │    ├─ dis  [L298] for_statement@297 i < k
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ std::numeric_limits<double>::max  [L88] 函数本体；短路求值/提前返回见源码
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ std::numeric_limits<double>::max  [L89] 函数本体；短路求值/提前返回见源码
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ logger::trace  [L93] 函数本体；短路求值/提前返回见源码
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ logger::trace  [L95] if_statement@94 (k < THRESHOLD_FOR_HGRAPH)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ logger::trace  [L97] if_statement@94 (k < THRESHOLD_FOR_HGRAPH) [else 分支]
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ NearestCentroidAssign  [L102] for_statement@100 it < iter → if_statement@101 (k < THRESHOLD_FOR_HGRAPH)
  │    │    │    │  #8 NearestCentroidAssign [src/impl/cluster/nearest_centroid_assign.cpp:39]
  │    │    │    │    ├─ std::numeric_limits<int32_t>::max  [L52] if_statement@50 (centroids == nullptr || queries == nullptr || labels == nullptr || allocator == nullptr || thread_pool == nullptr || centroid_count == 0 || query_count == 0 || dim == 0 || centroid_count > static_cast<uint64_t>(std::numeric_limits<int32_t>::max()) || dim > static_cast<uint64_t>(std::numeric_limits<int32_t>::max()))
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ std::numeric_limits<int32_t>::max  [L53] if_statement@50 (centroids == nullptr || queries == nullptr || labels == nullptr || allocator == nullptr || thread_pool == nullptr || centroid_count == 0 || query_count == 0 || dim == 0 || centroid_count > static_cast<uint64_t>(std::numeric_limits<int32_t>::max()) || dim > static_cast<uint64_t>(std::numeric_limits<int32_t>::max()))
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ VsagException  [L54] if_statement@50 (centroids == nullptr || queries == nullptr || labels == nullptr || allocator == nullptr || thread_pool == nullptr || centroid_count == 0 || query_count == 0 || dim == 0 || centroid_count > static_cast<uint64_t>(std::numeric_limits<int32_t>::max()) || dim > static_cast<uint64_t>(std::numeric_limits<int32_t>::max()))
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ future.wait  [L63] lambda@61（定义体，执行时间取决于调用/调度） → for_range_loop@62
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ futures.clear  [L65] lambda@61（定义体，执行时间取决于调用/调度）
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ std::min  [L68] 函数本体；短路求值/提前返回见源码
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ FP32ComputeIP  [L76] lambda@74（定义体，执行时间取决于调用/调度） → for_statement@75 i < end
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ futures.emplace_back  [L80] for_statement@79 i < centroid_count
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ thread_pool_ref->GeneralEnqueue  [L81] for_statement@79 i < centroid_count
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ std::min  [L81] for_statement@79 i < centroid_count
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ wait_futures_and_clear  [L83] 函数本体；短路求值/提前返回见源码
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ std::min  [L86] for_statement@85 i < query_count
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ SimdStatus::SupportAMXBF16  [L108] for_statement@85 i < query_count → if_statement@107 (dim >= amx_bf16_min_dim && centroid_count >= amx_bf16_min_m && cur_query_count >= amx_bf16_min_n && SimdStatus::SupportAMXBF16())
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ amx::SgemmBF16IPColMajorOut  [L109] for_statement@85 i < query_count → if_statement@107 (dim >= amx_bf16_min_dim && centroid_count >= amx_bf16_min_m && cur_query_count >= amx_bf16_min_n && SimdStatus::SupportAMXBF16())
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ BlasFunction::Sgemm  [L119] for_statement@85 i < query_count → if_statement@118 (!used_amx)
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ omp_set_num_threads  [L137] for_statement@85 i < query_count → lambda@136（定义体，执行时间取决于调用/调度）
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ BlasFunction::Saxpy  [L140] for_statement@85 i < query_count → lambda@136（定义体，执行时间取决于调用/调度） → for_statement@139 j < end
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ std::min_element  [L146] for_statement@85 i < query_count → lambda@136（定义体，执行时间取决于调用/调度） → for_statement@139 j < end
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ FP32ComputeIP  [L148] for_statement@85 i < query_count → lambda@136（定义体，执行时间取决于调用/调度） → for_statement@139 j < end
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ std::distance  [L150] for_statement@85 i < query_count → lambda@136（定义体，执行时间取决于调用/调度） → for_statement@139 j < end
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ futures.emplace_back  [L162] for_statement@85 i < query_count → for_statement@161 j < cur_query_count
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ thread_pool_ref->GeneralEnqueue  [L162] for_statement@85 i < query_count → for_statement@161 j < cur_query_count
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ std::min  [L163] for_statement@85 i < query_count → for_statement@161 j < cur_query_count
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ wait_futures_and_clear  [L165] for_statement@85 i < query_count
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ labels.data  [L109] for_statement@100 it < iter → if_statement@101 (k < THRESHOLD_FOR_HGRAPH)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ this->find_nearest_one_with_hgraph  [L111] for_statement@100 it < iter → if_statement@101 (k < THRESHOLD_FOR_HGRAPH) [else 分支]
  │    │    │    │  #9 KMeansCluster::find_nearest_one_with_hgraph [src/impl/cluster/kmeans_cluster.cpp:230]
  │    │    │    │    ├─ VsagException  [L236] if_statement@235 (k_centroids_ == nullptr)
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ std::make_shared<SafeAllocator>  [L243] 函数本体；短路求值/提前返回见源码
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ std::max  [L246] 函数本体；短路求值/提前返回见源码
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ InnerIndexInterface::FastCreateIndex  [L249] 函数本体；短路求值/提前返回见源码
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ fmt::format  [L249] 函数本体；短路求值/提前返回见源码
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ Dataset::Make  [L250] 函数本体；短路求值/提前返回见源码
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ std::iota  [L252] 函数本体；短路求值/提前返回见源码
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ ids.begin  [L252] 函数本体；短路求值/提前返回见源码
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ ids.end  [L252] 函数本体；短路求值/提前返回见源码
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ base->Dim(dim_) ->NumElements(static_cast<int64_t>(k)) ->Float32Vectors(this->k_centroids_) ->Ids(ids.data()) ->Owner  [L253] 函数本体；短路求值/提前返回见源码
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ base->Dim(dim_) ->NumElements(static_cast<int64_t>(k)) ->Float32Vectors(this->k_centroids_) ->Ids  [L253] 函数本体；短路求值/提前返回见源码
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ base->Dim(dim_) ->NumElements(static_cast<int64_t>(k)) ->Float32Vectors  [L253] 函数本体；短路求值/提前返回见源码
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ base->Dim(dim_) ->NumElements  [L253] 函数本体；短路求值/提前返回见源码
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ base->Dim  [L253] 函数本体；短路求值/提前返回见源码
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ ids.data  [L256] 函数本体；短路求值/提前返回见源码
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ hgraph->Build  [L258] 函数本体；短路求值/提前返回见源码
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ hgraph->SetImmutable  [L259] 函数本体；短路求值/提前返回见源码
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ Dataset::Make  [L265] lambda@262（定义体，执行时间取决于调用/调度） → for_statement@264 j < end
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ q->Owner(false) ->Float32Vectors(query + j * this->dim_) ->NumElements(1) ->Dim  [L266] lambda@262（定义体，执行时间取决于调用/调度） → for_statement@264 j < end
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ q->Owner(false) ->Float32Vectors(query + j * this->dim_) ->NumElements  [L266] lambda@262（定义体，执行时间取决于调用/调度） → for_statement@264 j < end
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ q->Owner(false) ->Float32Vectors  [L266] lambda@262（定义体，执行时间取决于调用/调度） → for_statement@264 j < end
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ q->Owner  [L266] lambda@262（定义体，执行时间取决于调用/调度） → for_statement@264 j < end
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ hgraph->KnnSearch  [L270] lambda@262（定义体，执行时间取决于调用/调度） → for_statement@264 j < end
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ ret->GetIds  [L271] lambda@262（定义体，执行时间取决于调用/调度） → for_statement@264 j < end
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ ret->GetDistances  [L272] lambda@262（定义体，执行时间取决于调用/调度） → for_statement@264 j < end
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ futures.emplace_back  [L281] for_statement@280 i < query_count
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ thread_pool_->GeneralEnqueue  [L282] for_statement@280 i < query_count
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ std::min  [L282] for_statement@280 i < query_count
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ future.wait  [L285] for_range_loop@284
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ block_counts.resize  [L122] for_statement@100 it < iter → if_statement@121 (deterministic_reduction)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ block_centroids.resize  [L123] for_statement@100 it < iter → if_statement@121 (deterministic_reduction)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ omp_set_num_threads  [L128] for_statement@100 it < iter → lambda@127（定义体，执行时间取决于调用/调度）
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ BlasFunction::Saxpy  [L136] for_statement@100 it < iter → lambda@127（定义体，执行时间取决于调用/调度） → for_statement@132 i < end → if_statement@134 (label >= 0 && label < static_cast<int32_t>(k))
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ local_centroids.data  [L141] for_statement@100 it < iter → lambda@127（定义体，执行时间取决于调用/调度） → for_statement@132 i < end → if_statement@134 (label >= 0 && label < static_cast<int32_t>(k))
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ std::copy  [L147] for_statement@100 it < iter → lambda@127（定义体，执行时间取决于调用/调度） → if_statement@146 (deterministic_reduction)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ local_counts.begin  [L148] for_statement@100 it < iter → lambda@127（定义体，执行时间取决于调用/调度） → if_statement@146 (deterministic_reduction)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ local_counts.end  [L148] for_statement@100 it < iter → lambda@127（定义体，执行时间取决于调用/调度） → if_statement@146 (deterministic_reduction)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ block_counts.data  [L148] for_statement@100 it < iter → lambda@127（定义体，执行时间取决于调用/调度） → if_statement@146 (deterministic_reduction)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ std::copy  [L149] for_statement@100 it < iter → lambda@127（定义体，执行时间取决于调用/调度） → if_statement@146 (deterministic_reduction)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ local_centroids.begin  [L149] for_statement@100 it < iter → lambda@127（定义体，执行时间取决于调用/调度） → if_statement@146 (deterministic_reduction)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ local_centroids.end  [L150] for_statement@100 it < iter → lambda@127（定义体，执行时间取决于调用/调度） → if_statement@146 (deterministic_reduction)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ block_centroids.data  [L151] for_statement@100 it < iter → lambda@127（定义体，执行时间取决于调用/调度） → if_statement@146 (deterministic_reduction)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ BlasFunction::Saxpy  [L157] for_statement@100 it < iter → lambda@127（定义体，执行时间取决于调用/调度） → if_statement@146 (deterministic_reduction) [else 分支] → for_statement@154 j < k → if_statement@155 (local_counts[j] > 0)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ local_centroids.data  [L160] for_statement@100 it < iter → lambda@127（定义体，执行时间取决于调用/调度） → if_statement@146 (deterministic_reduction) [else 分支] → for_statement@154 j < k → if_statement@155 (local_counts[j] > 0)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ new_centroids.data  [L162] for_statement@100 it < iter → lambda@127（定义体，执行时间取决于调用/调度） → if_statement@146 (deterministic_reduction) [else 分支] → for_statement@154 j < k → if_statement@155 (local_counts[j] > 0)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ futures.emplace_back  [L169] for_statement@100 it < iter → for_statement@168 i < count
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ thread_pool_->GeneralEnqueue  [L169] for_statement@100 it < iter → for_statement@168 i < count
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ std::min  [L170] for_statement@100 it < iter → for_statement@168 i < count
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ future.wait  [L173] for_statement@100 it < iter → for_range_loop@172
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ futures.clear  [L175] for_statement@100 it < iter
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ BlasFunction::Saxpy  [L182] for_statement@100 it < iter → if_statement@176 (deterministic_reduction) → for_statement@177 block_id < block_count → for_statement@178 j < k → if_statement@180 (block_counts[count_offset] > 0)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ block_centroids.data  [L184] for_statement@100 it < iter → if_statement@176 (deterministic_reduction) → for_statement@177 block_id < block_count → for_statement@178 j < k → if_statement@180 (block_counts[count_offset] > 0)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ new_centroids.data  [L187] for_statement@100 it < iter → if_statement@176 (deterministic_reduction) → for_statement@177 block_id < block_count → for_statement@178 j < k → if_statement@180 (block_counts[count_offset] > 0)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ BlasFunction::Sscal  [L197] for_statement@100 it < iter → for_statement@195 j < k → if_statement@196 (counts[j] > 0)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ new_centroids.data  [L199] for_statement@100 it < iter → for_statement@195 j < k → if_statement@196 (counts[j] > 0)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ std::copy  [L201] for_statement@100 it < iter → for_statement@195 j < k → if_statement@196 (counts[j] > 0)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ new_centroids.data  [L201] for_statement@100 it < iter → for_statement@195 j < k → if_statement@196 (counts[j] > 0)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ new_centroids.data  [L202] for_statement@100 it < iter → for_statement@195 j < k → if_statement@196 (counts[j] > 0)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ dis  [L205] for_statement@100 it < iter → for_statement@195 j < k → if_statement@196 (counts[j] > 0) [else 分支]
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ logger::trace  [L212] for_statement@100 it < iter
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ get_current_time  [L213] for_statement@100 it < iter
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ std::fabs  [L218] for_statement@100 it < iter → if_statement@217 (it > 0 && use_mse_for_convergence && std::fabs(last_err - total_err) / static_cast<double>(count) < threshold)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ centroids->GetNumElements  [L128] lambda@125（定义体，执行时间取决于调用/调度）
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ residuals.data  [L128] lambda@125（定义体，执行时间取决于调用/调度）
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ memcpy  [L129] lambda@125（定义体，执行时间取决于调用/调度）
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ centroids->GetNumElements  [L129] lambda@125（定义体，执行时间取决于调用/调度）
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ route_index.Build  [L131] lambda@125（定义体，执行时间取决于调用/调度）
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ this->inner_classify_datas  [L132] lambda@125（定义体，执行时间取决于调用/调度）
  │    │    │  #10 GNOIMIPartition::inner_classify_datas [src/algorithm/ivf/gno_imi_partition.cpp:346]
  │    │    │    ├─ Dataset::Make  [L351] for_statement@350 i < count
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ query->Dim(this->dim_) ->Float32Vectors(datas + i * this->dim_) ->NumElements(1) ->Owner  [L352] for_statement@350 i < count
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ query->Dim(this->dim_) ->Float32Vectors(datas + i * this->dim_) ->NumElements  [L352] for_statement@350 i < count
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ query->Dim(this->dim_) ->Float32Vectors  [L352] for_statement@350 i < count
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ query->Dim  [L352] for_statement@350 i < count
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ route_index.KnnSearch  [L357] for_statement@350 i < count
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ search_result->GetIds  [L358] for_statement@350 i < count
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ residuals.data  [L132] lambda@125（定义体，执行时间取决于调用/调度）
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ this->GetResidual  [L133] lambda@125（定义体，执行时间取决于调用/调度）
  │    │    │  #11 IVFPartitionStrategy::GetResidual [src/algorithm/ivf/ivf_partition_strategy.cpp:22]
  │    │    │    ├─ memcpy  [L26] 函数本体；短路求值/提前返回见源码
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ BlasFunction::Saxpy  [L29] for_statement@27 i < n
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ residuals.data  [L133] lambda@125（定义体，执行时间取决于调用/调度）
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ assign.data  [L133] lambda@125（定义体，执行时间取决于调用/调度）
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ std::numeric_limits<double>::max  [L137] 函数本体；短路求值/提前返回见源码
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ train_and_get_residual  [L141] for_statement@138 i < 2
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ data_centroids_s_tmp.data  [L141] for_statement@138 i < 2
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ logger::info  [L142] for_statement@138 i < 2
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ train_and_get_residual  [L144] for_statement@138 i < 2
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ data_centroids_t_tmp.data  [L144] for_statement@138 i < 2
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ logger::info  [L145] for_statement@138 i < 2
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ std::copy  [L149] for_statement@138 i < 2 → if_statement@147 (err_to_t < min_err)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ data_centroids_s_tmp.begin  [L149] for_statement@138 i < 2 → if_statement@147 (err_to_t < min_err)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ data_centroids_s_tmp.end  [L150] for_statement@138 i < 2 → if_statement@147 (err_to_t < min_err)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ data_centroids_s_.begin  [L151] for_statement@138 i < 2 → if_statement@147 (err_to_t < min_err)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ std::copy  [L152] for_statement@138 i < 2 → if_statement@147 (err_to_t < min_err)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ data_centroids_t_tmp.begin  [L152] for_statement@138 i < 2 → if_statement@147 (err_to_t < min_err)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ data_centroids_t_tmp.end  [L153] for_statement@138 i < 2 → if_statement@147 (err_to_t < min_err)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ data_centroids_t_.begin  [L154] for_statement@138 i < 2 → if_statement@147 (err_to_t < min_err)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ FP32ComputeIP  [L159] for_statement@158 i < bucket_count_s_
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ data_centroids_s_.data  [L160] for_statement@158 i < bucket_count_s_
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ data_centroids_s_.data  [L160] for_statement@158 i < bucket_count_s_
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ FP32ComputeIP  [L166] for_statement@165 i < bucket_count_t_
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ data_centroids_t_.data  [L167] for_statement@165 i < bucket_count_t_
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ data_centroids_t_.data  [L167] for_statement@165 i < bucket_count_t_
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ std::sort  [L173] 函数本体；短路求值/提前返回见源码
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ norms_t.begin  [L173] 函数本体；短路求值/提前返回见源码
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ norms_t.end  [L173] 函数本体；短路求值/提前返回见源码
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ std::greater<>  [L173] 函数本体；短路求值/提前返回见源码
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ std::copy  [L179] for_statement@175 i < bucket_count_t_
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ data_centroids_t_.data  [L179] for_statement@175 i < bucket_count_t_
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ data_centroids_t_.data  [L180] for_statement@175 i < bucket_count_t_
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ temp_data.data  [L181] for_statement@175 i < bucket_count_t_
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ std::copy  [L184] 函数本体；短路求值/提前返回见源码
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ temp_data.begin  [L184] 函数本体；短路求值/提前返回见源码
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ temp_data.end  [L184] 函数本体；短路求值/提前返回见源码
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ data_centroids_t_.data  [L184] 函数本体；短路求值/提前返回见源码
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ matmul  [L187] 函数本体；短路求值/提前返回见源码
  │    │    │  #12 matmul [src/algorithm/ivf/gno_imi_partition.cpp:40]
  │    │    │    ├─ BlasFunction::Sgemm  [L42] 函数本体；短路求值/提前返回见源码
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ data_centroids_s_.data  [L187] 函数本体；短路求值/提前返回见源码
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ data_centroids_t_.data  [L188] 函数本体；短路求值/提前返回见源码
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ ip_st.data  [L189] 函数本体；短路求值/提前返回见源码
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │  #13 IVFNearestPartition::Train [src/algorithm/ivf/ivf_nearest_partition.cpp:91]
  │    │    ├─ Dataset::Make  [L94] 函数本体；短路求值/提前返回见源码
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ std::iota  [L97] 函数本体；短路求值/提前返回见源码
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ ids.begin  [L97] 函数本体；短路求值/提前返回见源码
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ ids.end  [L97] 函数本体；短路求值/提前返回见源码
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ centroids->Ids(ids.data()) ->Dim(dim) ->Float32Vectors(data.data()) ->NumElements(this->bucket_count_) ->Owner  [L98] 函数本体；短路求值/提前返回见源码
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ centroids->Ids(ids.data()) ->Dim(dim) ->Float32Vectors(data.data()) ->NumElements  [L98] 函数本体；短路求值/提前返回见源码
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ centroids->Ids(ids.data()) ->Dim(dim) ->Float32Vectors  [L98] 函数本体；短路求值/提前返回见源码
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ centroids->Ids(ids.data()) ->Dim  [L98] 函数本体；短路求值/提前返回见源码
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ centroids->Ids  [L98] 函数本体；短路求值/提前返回见源码
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ ids.data  [L98] 函数本体；短路求值/提前返回见源码
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ data.data  [L100] 函数本体；短路求值/提前返回见源码
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ cls.Run  [L108] if_statement@104 (ivf_partition_strategy_param_->partition_train_type == IVFNearestPartitionTrainerType::KMeansTrainer)
  │    │    │  ↳ 复用节点 #5 KMeansCluster::Run（本树前文已展开）
  │    │    ├─ dataset->GetFloat32Vectors  [L109] if_statement@104 (ivf_partition_strategy_param_->partition_train_type == IVFNearestPartitionTrainerType::KMeansTrainer)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ dataset->GetNumElements  [L110] if_statement@104 (ivf_partition_strategy_param_->partition_train_type == IVFNearestPartitionTrainerType::KMeansTrainer)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ memcpy  [L112] if_statement@104 (ivf_partition_strategy_param_->partition_train_type == IVFNearestPartitionTrainerType::KMeansTrainer)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ data.data  [L112] if_statement@104 (ivf_partition_strategy_param_->partition_train_type == IVFNearestPartitionTrainerType::KMeansTrainer)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ select_k_numbers  [L115] if_statement@104 (ivf_partition_strategy_param_->partition_train_type == IVFNearestPartitionTrainerType::KMeansTrainer) [else 分支] → if_statement@113 (ivf_partition_strategy_param_->partition_train_type == IVFNearestPartitionTrainerType::RandomTrainer)
  │    │    │  #14 select_k_numbers [src/utils/util_functions.cpp:43]
  │    │    │    ├─ VsagException  [L46] if_statement@45 (k > n || k <= 0)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ std::iota  [L50] 函数本体；短路求值/提前返回见源码
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ numbers.begin  [L50] 函数本体；短路求值/提前返回见源码
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ numbers.end  [L50] 函数本体；短路求值/提前返回见源码
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ std::swap  [L56] for_statement@54 i < k
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ dist  [L56] for_statement@54 i < k
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ numbers.resize  [L58] 函数本体；短路求值/提前返回见源码
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ dataset->GetNumElements  [L115] if_statement@104 (ivf_partition_strategy_param_->partition_train_type == IVFNearestPartitionTrainerType::KMeansTrainer) [else 分支] → if_statement@113 (ivf_partition_strategy_param_->partition_train_type == IVFNearestPartitionTrainerType::RandomTrainer)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ memcpy  [L117] if_statement@104 (ivf_partition_strategy_param_->partition_train_type == IVFNearestPartitionTrainerType::KMeansTrainer) [else 分支] → if_statement@113 (ivf_partition_strategy_param_->partition_train_type == IVFNearestPartitionTrainerType::RandomTrainer) → for_statement@116 i < bucket_count_
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ data.data  [L117] if_statement@104 (ivf_partition_strategy_param_->partition_train_type == IVFNearestPartitionTrainerType::KMeansTrainer) [else 分支] → if_statement@113 (ivf_partition_strategy_param_->partition_train_type == IVFNearestPartitionTrainerType::RandomTrainer) → for_statement@116 i < bucket_count_
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ dataset->GetFloat32Vectors  [L118] if_statement@104 (ivf_partition_strategy_param_->partition_train_type == IVFNearestPartitionTrainerType::KMeansTrainer) [else 分支] → if_statement@113 (ivf_partition_strategy_param_->partition_train_type == IVFNearestPartitionTrainerType::RandomTrainer) → for_statement@116 i < bucket_count_
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ Normalize  [L124] if_statement@122 (metric_type_ == MetricType::METRIC_TYPE_COSINE) → for_statement@123 i < bucket_count_
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ data.data  [L124] if_statement@122 (metric_type_ == MetricType::METRIC_TYPE_COSINE) → for_statement@123 i < bucket_count_
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ data.data  [L124] if_statement@122 (metric_type_ == MetricType::METRIC_TYPE_COSINE) → for_statement@123 i < bucket_count_
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ this->route_index_ptr_->Build  [L129] if_statement@128 (this->use_route_graph_)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ failed_ids.empty  [L130] if_statement@128 (this->use_route_graph_) → if_statement@130 (not failed_ids.empty())
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ VsagException  [L131] if_statement@128 (this->use_route_graph_) → if_statement@130 (not failed_ids.empty())
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ this->centroids_.resize  [L137] if_statement@128 (this->use_route_graph_) [else 分支]
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ memcpy  [L138] if_statement@128 (this->use_route_graph_) [else 分支]
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ this->centroids_.data  [L139] if_statement@128 (this->use_route_graph_) [else 分支]
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ data.data  [L139] if_statement@128 (this->use_route_graph_) [else 分支]
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ this->norms_.resize  [L140] if_statement@128 (this->use_route_graph_) [else 分支]
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ FP32ComputeIP  [L143] if_statement@128 (this->use_route_graph_) [else 分支] → if_statement@141 (metric_type_ == MetricType::METRIC_TYPE_L2SQR) → for_statement@142 i < bucket_count_
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ this->centroids_.data  [L143] if_statement@128 (this->use_route_graph_) [else 分支] → if_statement@141 (metric_type_ == MetricType::METRIC_TYPE_L2SQR) → for_statement@142 i < bucket_count_
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ this->centroids_.data  [L144] if_statement@128 (this->use_route_graph_) [else 分支] → if_statement@141 (metric_type_ == MetricType::METRIC_TYPE_L2SQR) → for_statement@142 i < bucket_count_
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ std::fill  [L151] if_statement@128 (this->use_route_graph_) [else 分支] → if_statement@141 (metric_type_ == MetricType::METRIC_TYPE_L2SQR) [else 分支]
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ this->norms_.begin  [L151] if_statement@128 (this->use_route_graph_) [else 分支] → if_statement@141 (metric_type_ == MetricType::METRIC_TYPE_L2SQR) [else 分支]
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ this->norms_.end  [L151] if_statement@128 (this->use_route_graph_) [else 分支] → if_statement@141 (metric_type_ == MetricType::METRIC_TYPE_L2SQR) [else 分支]
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ train_data->GetFloat32Vectors  [L134] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ this->bucket_->Train  [L135] 函数本体；短路求值/提前返回见源码
  │    │  #15 BucketDataCell<QuantTmpl, IOTmpl>::Train [src/datacell/bucket_datacell.h:586]
  │    │    ├─ this->quantizer_->GetDim  [L591] if_statement@589 (use_residual_)
  │    │    │  #16 Quantizer::GetDim [src/quantization/quantizer.h:340]
  │    │    ├─ train_data_buffer.resize  [L592] if_statement@589 (use_residual_)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ Normalize  [L595] if_statement@589 (use_residual_) → if_statement@593 (metric_ == MetricType::METRIC_TYPE_COSINE) → for_statement@594 i < count
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ train_data_buffer.data  [L595] if_statement@589 (use_residual_) → if_statement@593 (metric_ == MetricType::METRIC_TYPE_COSINE) → for_statement@594 i < count
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ train_data_buffer.data  [L597] if_statement@589 (use_residual_) → if_statement@593 (metric_ == MetricType::METRIC_TYPE_COSINE)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ this->quantizer_->GetDim  [L599] if_statement@589 (use_residual_)
  │    │    │  ↳ 复用节点 #16 Quantizer::GetDim（本树前文已展开）
  │    │    ├─ strategy_->ClassifyDatas  [L600] if_statement@589 (use_residual_)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ strategy_->GetCentroid  [L602] if_statement@589 (use_residual_) → for_statement@601 i < count
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ train_data_buffer.data  [L607] if_statement@589 (use_residual_)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ this->quantizer_->Train  [L609] 函数本体；短路求值/提前返回见源码
  │    │    │  #17 Quantizer::Train [src/quantization/quantizer.h:49]
  │    │    │    ├─ cast().TrainImpl  [L54] 函数本体；短路求值/提前返回见源码
  │    │    │    │  #18 FP32Quantizer<metric>::TrainImpl [src/quantization/fp32_quantizer.cpp:50]
  │    │    │    ├─ cast  [L54] 函数本体；短路求值/提前返回见源码
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ this->precise_bucket_->Train  [L138] if_statement@136 (use_reorder_) → if_statement@137 (precise_bucket_ != nullptr)
  │    │  ↳ 复用节点 #15 BucketDataCell<QuantTmpl, IOTmpl>::Train（本树前文已展开）
  │    ├─ data->GetFloat32Vectors  [L138] if_statement@136 (use_reorder_) → if_statement@137 (precise_bucket_ != nullptr)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ data->GetNumElements  [L138] if_statement@136 (use_reorder_) → if_statement@137 (precise_bucket_ != nullptr)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ this->reorder_codes_->Train  [L140] if_statement@136 (use_reorder_) → if_statement@137 (precise_bucket_ != nullptr) [else 分支]
  │    │  ↳ 复用节点 #2 IVF::Train（本树前文已展开）
  │    ├─ data->GetFloat32Vectors  [L140] if_statement@136 (use_reorder_) → if_statement@137 (precise_bucket_ != nullptr) [else 分支]
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ data->GetNumElements  [L140] if_statement@136 (use_reorder_) → if_statement@137 (precise_bucket_ != nullptr) [else 分支]
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ this->Add  [L112] 函数本体；短路求值/提前返回见源码
  │  #19 IVF::Add [src/algorithm/ivf/ivf_build.cpp:146]
  │    ├─ VsagException  [L150] if_statement@149 (not partition_strategy_->is_trained_)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ this->bucket_->Unpack  [L152] 函数本体；短路求值/提前返回见源码
  │    │  #20 BucketDataCell::Unpack [src/datacell/bucket_datacell.h:139]
  │    │    ├─ GetQuantizerName  [L141] if_statement@141 (GetQuantizerName() == QUANTIZATION_TYPE_VALUE_PQFS)
  │    │    │  #21 BucketDataCell::GetQuantizerName [src/datacell/bucket_datacell.h:170]
  │    │    │    ├─ this->quantizer_->Name  [L172] 函数本体；短路求值/提前返回见源码
  │    │    │    │  #22 Quantizer::Name [src/quantization/quantizer.h:300]
  │    │    │    │    ├─ cast().NameImpl  [L302] 函数本体；短路求值/提前返回见源码
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ cast  [L302] 函数本体；短路求值/提前返回见源码
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ this->unpack_fastscan  [L142] if_statement@141 (GetQuantizerName() == QUANTIZATION_TYPE_VALUE_PQFS)
  │    │    │  #23 BucketDataCell<QuantTmpl, IOTmpl>::unpack_fastscan [src/datacell/bucket_datacell.h:958]
  │    │    │    ├─ this->datas_[i].Acquire  [L966] for_statement@961 i < this->bucket_count_
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ lease.Data  [L967] for_statement@961 i < this->bucket_count_
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ quantizer_->Unpack32  [L971] for_statement@961 i < this->bucket_count_ → while_statement@969 (begin < bucket_size)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ this->datas_[i].Write  [L972] for_statement@961 i < this->bucket_count_ → while_statement@969 (begin < bucket_size)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ this->precise_bucket_->Unpack  [L154] if_statement@153 (precise_bucket_ != nullptr)
  │    │  ↳ 复用节点 #20 BucketDataCell::Unpack（本树前文已展开）
  │    ├─ base->GetNumElements  [L156] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ base->GetIds  [L157] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ base->GetFloat32Vectors  [L158] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ base->GetAttributeSets  [L159] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ base->GetExtraInfos  [L160] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ base->GetExtraInfoSize  [L161] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ partition_strategy_->ClassifyDatas  [L163] 函数本体；短路求值/提前返回见源码
  │    │  ├─ 以下为分派/重载候选，并非全部依次执行
  │    │  #24 GNOIMIPartition::ClassifyDatas [src/algorithm/ivf/gno_imi_partition.cpp:201]
  │    │    ├─ norm_vectors.resize  [L208] if_statement@207 (metric_type_ == MetricType::METRIC_TYPE_COSINE)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ Normalize  [L210] if_statement@207 (metric_type_ == MetricType::METRIC_TYPE_COSINE) → for_statement@209 i < count
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ norm_vectors.data  [L211] if_statement@207 (metric_type_ == MetricType::METRIC_TYPE_COSINE) → for_statement@209 i < count
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ norm_vectors.data  [L213] if_statement@207 (metric_type_ == MetricType::METRIC_TYPE_COSINE)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ inner_joint_classify_datas  [L216] 函数本体；短路求值/提前返回见源码
  │    │    │  #25 GNOIMIPartition::inner_joint_classify_datas [src/algorithm/ivf/gno_imi_partition.cpp:367]
  │    │    │    ├─ matmul  [L377] 函数本体；短路求值/提前返回见源码
  │    │    │    │  ↳ 复用节点 #12 matmul（本树前文已展开）
  │    │    │    ├─ data_centroids_s_.data  [L377] 函数本体；短路求值/提前返回见源码
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ dist_to_s.data  [L377] 函数本体；短路求值/提前返回见源码
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ matmul  [L378] 函数本体；短路求值/提前返回见源码
  │    │    │    │  ↳ 复用节点 #12 matmul（本树前文已展开）
  │    │    │    ├─ data_centroids_t_.data  [L378] 函数本体；短路求值/提前返回见源码
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ dist_to_t.data  [L378] 函数本体；短路求值/提前返回见源码
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ FP32ComputeIP  [L386] for_statement@385 i < count
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ std::sort  [L393] for_statement@385 i < count
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ precomputed_terms_s.begin  [L393] for_statement@385 i < count
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ precomputed_terms_s.end  [L393] for_statement@385 i < count
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ heap.size  [L402] for_statement@385 i < count → for_statement@396 j < bucket_count_s_ → for_statement@400 k < bucket_count_t_ → if_statement@402 (heap.size() >= buckets_per_data && std::sqrt(cur_precomputed_term_s) - std::sqrt(norms_t_[cur_bucket_id_t]) > std::sqrt(heap.top().first))
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ std::sqrt  [L403] for_statement@385 i < count → for_statement@396 j < bucket_count_s_ → for_statement@400 k < bucket_count_t_ → if_statement@402 (heap.size() >= buckets_per_data && std::sqrt(cur_precomputed_term_s) - std::sqrt(norms_t_[cur_bucket_id_t]) > std::sqrt(heap.top().first))
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ std::sqrt  [L403] for_statement@385 i < count → for_statement@396 j < bucket_count_s_ → for_statement@400 k < bucket_count_t_ → if_statement@402 (heap.size() >= buckets_per_data && std::sqrt(cur_precomputed_term_s) - std::sqrt(norms_t_[cur_bucket_id_t]) > std::sqrt(heap.top().first))
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ std::sqrt  [L404] for_statement@385 i < count → for_statement@396 j < bucket_count_s_ → for_statement@400 k < bucket_count_t_ → if_statement@402 (heap.size() >= buckets_per_data && std::sqrt(cur_precomputed_term_s) - std::sqrt(norms_t_[cur_bucket_id_t]) > std::sqrt(heap.top().first))
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ heap.top  [L404] for_statement@385 i < count → for_statement@396 j < bucket_count_s_ → for_statement@400 k < bucket_count_t_ → if_statement@402 (heap.size() >= buckets_per_data && std::sqrt(cur_precomputed_term_s) - std::sqrt(norms_t_[cur_bucket_id_t]) > std::sqrt(heap.top().first))
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ heap.size  [L414] for_statement@385 i < count → for_statement@396 j < bucket_count_s_ → for_statement@400 k < bucket_count_t_ → if_statement@414 (heap.size() < buckets_per_data || dist < heap.top().first)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ heap.top  [L414] for_statement@385 i < count → for_statement@396 j < bucket_count_s_ → for_statement@400 k < bucket_count_t_ → if_statement@414 (heap.size() < buckets_per_data || dist < heap.top().first)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ heap.emplace  [L415] for_statement@385 i < count → for_statement@396 j < bucket_count_s_ → for_statement@400 k < bucket_count_t_ → if_statement@414 (heap.size() < buckets_per_data || dist < heap.top().first)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ heap.size  [L417] for_statement@385 i < count → for_statement@396 j < bucket_count_s_ → for_statement@400 k < bucket_count_t_ → if_statement@417 (heap.size() > buckets_per_data)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ heap.pop  [L418] for_statement@385 i < count → for_statement@396 j < bucket_count_s_ → for_statement@400 k < bucket_count_t_ → if_statement@417 (heap.size() > buckets_per_data)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ heap.top  [L424] for_statement@385 i < count → for_statement@423 j >= 0
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ heap.top  [L426] for_statement@385 i < count → for_statement@423 j >= 0 → if_statement@425 (j == 0)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ heap.pop  [L428] for_statement@385 i < count → for_statement@423 j >= 0
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ ctx->stats->dist_cmp.fetch_add  [L433] if_statement@432 (ctx != nullptr and ctx->stats != nullptr)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ ctx->stats->AddDistance  [L434] if_statement@432 (ctx != nullptr and ctx->stats != nullptr)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ result.data  [L217] 函数本体；短路求值/提前返回见源码
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │  #26 IVFNearestPartition::ClassifyDatas [src/algorithm/ivf/ivf_nearest_partition.cpp:157]
  │    │    ├─ this->classify_datas_by_scan  [L163] if_statement@162 (not this->use_route_graph_)
  │    │    │  #27 IVFNearestPartition::classify_datas_by_scan [src/algorithm/ivf/ivf_nearest_partition.cpp:313]
  │    │    │    ├─ std::min<BucketIdType>  [L325] 函数本体；短路求值/提前返回见源码
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ norm_vectors.resize  [L333] if_statement@332 (metric_type_ == MetricType::METRIC_TYPE_COSINE)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ Normalize  [L335] if_statement@332 (metric_type_ == MetricType::METRIC_TYPE_COSINE) → for_statement@334 i < count
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ norm_vectors.data  [L335] if_statement@332 (metric_type_ == MetricType::METRIC_TYPE_COSINE) → for_statement@334 i < count
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ norm_vectors.data  [L337] if_statement@332 (metric_type_ == MetricType::METRIC_TYPE_COSINE)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ compute_centroid_dots  [L342] 函数本体；短路求值/提前返回见源码
  │    │    │    │  #28 compute_centroid_dots [src/algorithm/ivf/ivf_nearest_partition.cpp:51]
  │    │    │    │    ├─ BlasFunction::Sgemm  [L53] 函数本体；短路求值/提前返回见源码
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ this->centroids_.data  [L343] 函数本体；短路求值/提前返回见源码
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ dots.data  [L343] 函数本体；短路求值/提前返回见源码
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ heap_storage.reserve  [L347] lambda@345（定义体，执行时间取决于调用/调度）
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ std::move  [L348] lambda@345（定义体，执行时间取决于调用/调度）
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ dots.data  [L349] lambda@345（定义体，执行时间取决于调用/调度）
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ heap.size  [L353] lambda@345（定义体，执行时间取决于调用/调度） → for_statement@350 b < bucket_count_ → if_statement@353 (heap.size() < k || candidate < heap.top())
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ heap.top  [L353] lambda@345（定义体，执行时间取决于调用/调度） → for_statement@350 b < bucket_count_ → if_statement@353 (heap.size() < k || candidate < heap.top())
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ heap.push  [L354] lambda@345（定义体，执行时间取决于调用/调度） → for_statement@350 b < bucket_count_ → if_statement@353 (heap.size() < k || candidate < heap.top())
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ heap.size  [L356] lambda@345（定义体，执行时间取决于调用/调度） → for_statement@350 b < bucket_count_ → if_statement@356 (heap.size() > k)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ heap.pop  [L357] lambda@345（定义体，执行时间取决于调用/调度） → for_statement@350 b < bucket_count_ → if_statement@356 (heap.size() > k)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ heap.top  [L361] lambda@345（定义体，执行时间取决于调用/调度） → for_statement@360 j > 0
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ heap.pop  [L362] lambda@345（定义体，执行时间取决于调用/调度） → for_statement@360 j > 0
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ task  [L367] if_statement@365 (thread_pool_ == nullptr or count == 1) → for_statement@366 i < count
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ futures.push_back  [L372] if_statement@365 (thread_pool_ == nullptr or count == 1) [else 分支] → for_statement@371 i < count
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ thread_pool_->GeneralEnqueue  [L372] if_statement@365 (thread_pool_ == nullptr or count == 1) [else 分支] → for_statement@371 i < count
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ item.get  [L375] if_statement@365 (thread_pool_ == nullptr or count == 1) [else 分支] → for_range_loop@374
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ std::min<uint64_t>  [L383] if_statement@379 (ctx != nullptr and ctx->stats != nullptr)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ std::numeric_limits<uint32_t>::max  [L383] if_statement@379 (ctx != nullptr and ctx->stats != nullptr)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ ctx->stats->dist_cmp.fetch_add  [L384] if_statement@379 (ctx != nullptr and ctx->stats != nullptr)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ ctx->stats->AddDistance  [L385] if_statement@379 (ctx != nullptr and ctx->stats != nullptr)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ Dataset::Make  [L169] lambda@168（定义体，执行时间取决于调用/调度）
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ query->Dim(this->dim_) ->Float32Vectors(reinterpret_cast<const float*>(datas) + i * this->dim_) ->NumElements(1) ->Owner  [L170] lambda@168（定义体，执行时间取决于调用/调度）
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ query->Dim(this->dim_) ->Float32Vectors(reinterpret_cast<const float*>(datas) + i * this->dim_) ->NumElements  [L170] lambda@168（定义体，执行时间取决于调用/调度）
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ query->Dim(this->dim_) ->Float32Vectors  [L170] lambda@168（定义体，执行时间取决于调用/调度）
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ query->Dim  [L170] lambda@168（定义体，执行时间取决于调用/调度）
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ fmt::format  [L175] lambda@168（定义体，执行时间取决于调用/调度）
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ std::max<int64_t>  [L176] lambda@168（定义体，执行时间取决于调用/调度）
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ this->route_index_ptr_->KnnSearch  [L179] lambda@168（定义体，执行时间取决于调用/调度）
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ search_result->GetIds  [L180] lambda@168（定义体，执行时间取决于调用/调度）
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ search_result->GetDim  [L182] lambda@168（定义体，执行时间取决于调用/调度） → for_statement@182 j < search_result->GetDim()
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ search_result->GetStatistics  [L191] lambda@168（定义体，执行时间取决于调用/调度） → if_statement@186 (ctx != nullptr and ctx->stats != nullptr)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ std::atoi  [L192] lambda@168（定义体，执行时间取决于调用/调度） → if_statement@186 (ctx != nullptr and ctx->stats != nullptr)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ route_stats[0].c_str  [L192] lambda@168（定义体，执行时间取决于调用/调度） → if_statement@186 (ctx != nullptr and ctx->stats != nullptr)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ route_stats.size  [L194] lambda@168（定义体，执行时间取决于调用/调度） → if_statement@186 (ctx != nullptr and ctx->stats != nullptr) → if_statement@194 (route_stats.size() > 1)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ std::strtoull  [L195] lambda@168（定义体，执行时间取决于调用/调度） → if_statement@186 (ctx != nullptr and ctx->stats != nullptr) → if_statement@194 (route_stats.size() > 1)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ route_stats[1].c_str  [L195] lambda@168（定义体，执行时间取决于调用/调度） → if_statement@186 (ctx != nullptr and ctx->stats != nullptr) → if_statement@194 (route_stats.size() > 1)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ ctx->stats->AddDistance  [L201] lambda@168（定义体，执行时间取决于调用/调度） → if_statement@186 (ctx != nullptr and ctx->stats != nullptr)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ task  [L208] if_statement@206 (thread_pool_ == nullptr or count == 1) → for_statement@207 i < count
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ futures.push_back  [L213] if_statement@206 (thread_pool_ == nullptr or count == 1) [else 分支] → for_statement@212 i < count
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ thread_pool_->GeneralEnqueue  [L213] if_statement@206 (thread_pool_ == nullptr or count == 1) [else 分支] → for_statement@212 i < count
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ item.get  [L216] if_statement@206 (thread_pool_ == nullptr or count == 1) [else 分支] → for_range_loop@215
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ ctx->stats->dist_cmp.fetch_add  [L221] if_statement@220 (ctx != nullptr and ctx->stats != nullptr)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ std::move  [L224] 函数本体；短路求值/提前返回见源码
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ VsagException  [L172] if_statement@170 (precise_bucket_ != nullptr) → if_statement@171 (num_element < 0 or current_num < 0)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ std::numeric_limits<InnerIdType>::max  [L178] if_statement@170 (precise_bucket_ != nullptr)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ VsagException  [L180] if_statement@170 (precise_bucket_ != nullptr) → if_statement@179 (posting_count > max_inner_id or current_count > max_inner_id - posting_count)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ this->reorder_codes_->BatchInsertVector  [L185] if_statement@184 (use_reorder_ and precise_bucket_ == nullptr)
  │    │  #29 BucketDataCell<QuantTmpl, IOTmpl>::BatchInsertVector [src/datacell/bucket_datacell.h:703]
  │    │    ├─ VsagException  [L714] if_statement@712 (vectors == nullptr or bucket_ids == nullptr or inner_ids == nullptr or out_offsets == nullptr)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ VsagException  [L719] if_statement@717 (this->bucket_count_ <= 0 or input_dim_ == 0 or code_size_ == 0 or (use_residual_ and strategy_ == nullptr))
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ std::numeric_limits<size_t>::max  [L723] 函数本体；短路求值/提前返回见源码
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ std::numeric_limits<uint64_t>::max  [L724] if_statement@724 (bucket_count == std::numeric_limits<uint64_t>::max() or bucket_count + 1 > max_allocation_size / sizeof(uint64_t) or batch_count > max_allocation_size / sizeof(uint64_t) or batch_count > max_allocation_size / sizeof(InnerIdType) or batch_count > max_allocation_size / sizeof(float) / input_dim_)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ VsagException  [L729] if_statement@724 (bucket_count == std::numeric_limits<uint64_t>::max() or bucket_count + 1 > max_allocation_size / sizeof(uint64_t) or batch_count > max_allocation_size / sizeof(uint64_t) or batch_count > max_allocation_size / sizeof(InnerIdType) or batch_count > max_allocation_size / sizeof(float) / input_dim_)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ check_valid_bucket_id  [L734] for_statement@733 i < batch_count
  │    │    │  #30 BucketDataCell::check_valid_bucket_id [src/datacell/bucket_datacell.h:244]
  │    │    │    ├─ VsagException  [L247] if_statement@246 (bucket_id >= this->bucket_count_ or bucket_id < 0)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ VsagException  [L736] for_statement@733 i < batch_count → if_statement@735 (inner_ids[i] == EMPTY_INNER_ID)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ bucket_begins.begin  [L746] 函数本体；短路求值/提前返回见源码
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ bucket_begins.end  [L746] 函数本体；短路求值/提前返回见源码
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ VsagException  [L760] for_statement@754 bucket_id < bucket_count → if_statement@759 (bucket_insert_count > max_allocation_size / static_cast<uint64_t>(code_size_))
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ residual_scores.resize  [L767] for_statement@754 bucket_id < bucket_count → if_statement@766 (use_residual_ and metric_ == MetricType::METRIC_TYPE_L2SQR)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ encode_vector  [L773] for_statement@754 bucket_id < bucket_count → for_statement@769 local_index < bucket_insert_count
  │    │    │  #31 BucketDataCell<QuantTmpl, IOTmpl>::encode_vector [src/datacell/bucket_datacell.h:613]
  │    │    │    ├─ this->quantizer_->EncodeOne  [L621] if_statement@620 (not use_residual_)
  │    │    │    │  #32 Quantizer::EncodeOne [src/quantization/quantizer.h:77]
  │    │    │    │    ├─ cast().EncodeOneImpl  [L79] 函数本体；短路求值/提前返回见源码
  │    │    │    │    │  #33 FP32Quantizer<metric>::EncodeOneImpl [src/quantization/fp32_quantizer.cpp:57]
  │    │    │    │    │    ├─ std::sqrt  [L63] if_statement@59 (metric == MetricType::METRIC_TYPE_COSINE) → if_statement@60 (this->hold_molds_)
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ FP32ComputeIP  [L63] if_statement@59 (metric == MetricType::METRIC_TYPE_COSINE) → if_statement@60 (this->hold_molds_)
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ memcpy  [L64] if_statement@59 (metric == MetricType::METRIC_TYPE_COSINE) → if_statement@60 (this->hold_molds_)
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ memcpy  [L65] if_statement@59 (metric == MetricType::METRIC_TYPE_COSINE) → if_statement@60 (this->hold_molds_)
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ Normalize  [L67] if_statement@59 (metric == MetricType::METRIC_TYPE_COSINE) → if_statement@60 (this->hold_molds_) [else 分支]
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ memcpy  [L70] if_statement@59 (metric == MetricType::METRIC_TYPE_COSINE) [else 分支]
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ cast  [L79] 函数本体；短路求值/提前返回见源码
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ this->quantizer_->GetDim  [L625] 函数本体；短路求值/提前返回见源码
  │    │    │    │  ↳ 复用节点 #16 Quantizer::GetDim（本树前文已展开）
  │    │    │    ├─ this->quantizer_->GetDim  [L626] 函数本体；短路求值/提前返回见源码
  │    │    │    │  ↳ 复用节点 #16 Quantizer::GetDim（本树前文已展开）
  │    │    │    ├─ this->quantizer_->GetDim  [L627] 函数本体；短路求值/提前返回见源码
  │    │    │    │  ↳ 复用节点 #16 Quantizer::GetDim（本树前文已展开）
  │    │    │    ├─ strategy_->GetCentroid  [L628] 函数本体；短路求值/提前返回见源码
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ Normalize  [L630] if_statement@629 (metric_ == MetricType::METRIC_TYPE_COSINE)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ normalize_data.data  [L630] if_statement@629 (metric_ == MetricType::METRIC_TYPE_COSINE)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ quantizer_->GetDim  [L630] if_statement@629 (metric_ == MetricType::METRIC_TYPE_COSINE)
  │    │    │    │  ↳ 复用节点 #16 Quantizer::GetDim（本树前文已展开）
  │    │    │    ├─ normalize_data.data  [L631] if_statement@629 (metric_ == MetricType::METRIC_TYPE_COSINE)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ FP32Sub  [L633] 函数本体；短路求值/提前返回见源码
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ centroid.data  [L633] 函数本体；短路求值/提前返回见源码
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ sub_data.data  [L633] 函数本体；短路求值/提前返回见源码
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ quantizer_->GetDim  [L633] 函数本体；短路求值/提前返回见源码
  │    │    │    │  ↳ 复用节点 #16 Quantizer::GetDim（本树前文已展开）
  │    │    │    ├─ sub_data.data  [L634] 函数本体；短路求值/提前返回见源码
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ this->quantizer_->EncodeOne  [L635] 函数本体；短路求值/提前返回见源码
  │    │    │    │  ↳ 复用节点 #32 Quantizer::EncodeOne（本树前文已展开）
  │    │    │    ├─ this->quantizer_->DecodeOne  [L637] if_statement@636 (metric_ == MetricType::METRIC_TYPE_L2SQR)
  │    │    │    │  #34 Quantizer::DecodeOne [src/quantization/quantizer.h:116]
  │    │    │    │    ├─ cast().DecodeOneImpl  [L118] 函数本体；短路求值/提前返回见源码
  │    │    │    │    │  #35 FP32Quantizer<metric>::DecodeOneImpl [src/quantization/fp32_quantizer.cpp:85]
  │    │    │    │    │    ├─ memcpy  [L87] 函数本体；短路求值/提前返回见源码
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ cast  [L118] 函数本体；短路求值/提前返回见源码
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ normalize_data.data  [L637] if_statement@636 (metric_ == MetricType::METRIC_TYPE_L2SQR)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ FP32ComputeIP  [L639] if_statement@636 (metric_ == MetricType::METRIC_TYPE_L2SQR)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ centroid.data  [L639] if_statement@636 (metric_ == MetricType::METRIC_TYPE_L2SQR)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ normalize_data.data  [L639] if_statement@636 (metric_ == MetricType::METRIC_TYPE_L2SQR)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ this->quantizer_->GetDim  [L639] if_statement@636 (metric_ == MetricType::METRIC_TYPE_L2SQR)
  │    │    │    │  ↳ 复用节点 #16 Quantizer::GetDim（本树前文已展开）
  │    │    │    ├─ FP32ComputeIP  [L640] if_statement@636 (metric_ == MetricType::METRIC_TYPE_L2SQR)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ centroid.data  [L640] if_statement@636 (metric_ == MetricType::METRIC_TYPE_L2SQR)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ centroid.data  [L640] if_statement@636 (metric_ == MetricType::METRIC_TYPE_L2SQR)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ this->quantizer_->GetDim  [L640] if_statement@636 (metric_ == MetricType::METRIC_TYPE_L2SQR)
  │    │    │    │  ↳ 复用节点 #16 Quantizer::GetDim（本树前文已展开）
  │    │    ├─ residual_scores.empty  [L777] for_statement@754 bucket_id < bucket_count → for_statement@769 local_index < bucket_insert_count → if_statement@777 (not residual_scores.empty())
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ std::numeric_limits<InnerIdType>::max  [L785] for_statement@754 bucket_id < bucket_count → if_statement@784 (bucket_insert_count > static_cast<uint64_t>(std::numeric_limits<InnerIdType>::max()) - append_begin)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ VsagException  [L786] for_statement@754 bucket_id < bucket_count → if_statement@784 (bucket_insert_count > static_cast<uint64_t>(std::numeric_limits<InnerIdType>::max()) - append_begin)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ std::numeric_limits<uint64_t>::max  [L789] for_statement@754 bucket_id < bucket_count → if_statement@789 (next_size > std::numeric_limits<uint64_t>::max() / static_cast<uint64_t>(code_size_))
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ VsagException  [L790] for_statement@754 bucket_id < bucket_count → if_statement@789 (next_size > std::numeric_limits<uint64_t>::max() / static_cast<uint64_t>(code_size_))
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ check_valid_bucket_capacity  [L792] for_statement@754 bucket_id < bucket_count
  │    │    │  #36 BucketDataCell<QuantTmpl, IOTmpl>::check_valid_bucket_capacity [src/datacell/bucket_datacell.h:645]
  │    │    │    ├─ std::numeric_limits<size_t>::max  [L649] if_statement@648 (need_resize && (next_size > MAX_BUCKET_ENTRIES || next_size > std::numeric_limits<size_t>::max() / sizeof(InnerIdType) || (use_residual_ && metric_ == MetricType::METRIC_TYPE_L2SQR && next_size > std::numeric_limits<size_t>::max() / sizeof(float)) || ZERO_FILL_BLOCK_ENTRIES > std::numeric_limits<uint64_t>::max() / static_cast<uint64_t>(code_size_)))
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ std::numeric_limits<size_t>::max  [L651] if_statement@648 (need_resize && (next_size > MAX_BUCKET_ENTRIES || next_size > std::numeric_limits<size_t>::max() / sizeof(InnerIdType) || (use_residual_ && metric_ == MetricType::METRIC_TYPE_L2SQR && next_size > std::numeric_limits<size_t>::max() / sizeof(float)) || ZERO_FILL_BLOCK_ENTRIES > std::numeric_limits<uint64_t>::max() / static_cast<uint64_t>(code_size_)))
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ std::numeric_limits<uint64_t>::max  [L652] if_statement@648 (need_resize && (next_size > MAX_BUCKET_ENTRIES || next_size > std::numeric_limits<size_t>::max() / sizeof(InnerIdType) || (use_residual_ && metric_ == MetricType::METRIC_TYPE_L2SQR && next_size > std::numeric_limits<size_t>::max() / sizeof(float)) || ZERO_FILL_BLOCK_ENTRIES > std::numeric_limits<uint64_t>::max() / static_cast<uint64_t>(code_size_)))
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ VsagException  [L654] if_statement@648 (need_resize && (next_size > MAX_BUCKET_ENTRIES || next_size > std::numeric_limits<size_t>::max() / sizeof(InnerIdType) || (use_residual_ && metric_ == MetricType::METRIC_TYPE_L2SQR && next_size > std::numeric_limits<size_t>::max() / sizeof(float)) || ZERO_FILL_BLOCK_ENTRIES > std::numeric_limits<uint64_t>::max() / static_cast<uint64_t>(code_size_)))
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ this->inner_ids_[bucket_id].size  [L792] for_statement@754 bucket_id < bucket_count
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ this->datas_[bucket_id].Write  [L793] for_statement@754 bucket_id < bucket_count
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ this->inner_ids_[bucket_id].size  [L796] for_statement@754 bucket_id < bucket_count → if_statement@796 (this->inner_ids_[bucket_id].size() < next_size)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ this->inner_ids_[bucket_id].resize  [L797] for_statement@754 bucket_id < bucket_count → if_statement@796 (this->inner_ids_[bucket_id].size() < next_size)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ residual_scores.empty  [L799] for_statement@754 bucket_id < bucket_count → if_statement@799 (not residual_scores.empty() and this->residual_bias_[bucket_id].size() < next_size)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ this->residual_bias_[bucket_id].size  [L799] for_statement@754 bucket_id < bucket_count → if_statement@799 (not residual_scores.empty() and this->residual_bias_[bucket_id].size() < next_size)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ this->residual_bias_[bucket_id].resize  [L800] for_statement@754 bucket_id < bucket_count → if_statement@799 (not residual_scores.empty() and this->residual_bias_[bucket_id].size() < next_size)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ residual_scores.empty  [L807] for_statement@754 bucket_id < bucket_count → for_statement@802 local_index < bucket_insert_count → if_statement@807 (not residual_scores.empty())
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ base->GetFloat32Vectors  [L185] if_statement@184 (use_reorder_ and precise_bucket_ == nullptr)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ base->GetNumElements  [L186] if_statement@184 (use_reorder_ and precise_bucket_ == nullptr)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ this->label_table_->Insert  [L189] for_statement@188 i < num_element
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ location_map_.resize  [L196] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ precise_offsets.resize  [L203] if_statement@200 (precise_bucket_ != nullptr)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ precise_bucket_->BatchInsertVector  [L207] if_statement@200 (precise_bucket_ != nullptr)
  │    │  ↳ 复用节点 #29 BucketDataCell<QuantTmpl, IOTmpl>::BatchInsertVector（本树前文已展开）
  │    ├─ buckets.data  [L208] if_statement@200 (precise_bucket_ != nullptr)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ posting_ids.data  [L209] if_statement@200 (precise_bucket_ != nullptr)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ precise_offsets.data  [L211] if_statement@200 (precise_bucket_ != nullptr)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ bucket_->InsertVectorWithOffset  [L223] lambda@214（定义体，执行时间取决于调用/调度） → for_statement@215 j < buckets_per_data_ → if_statement@220 (precise_bucket_ != nullptr)
  │    │  #37 BucketDataCell<QuantTmpl, IOTmpl>::InsertVectorWithOffset [src/datacell/bucket_datacell.h:818]
  │    │    ├─ check_valid_bucket_id  [L823] 函数本体；短路求值/提前返回见源码
  │    │    │  ↳ 复用节点 #30 BucketDataCell::check_valid_bucket_id（本树前文已展开）
  │    │    ├─ VsagException  [L825] if_statement@824 (inner_id == EMPTY_INNER_ID)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ VsagException  [L829] if_statement@827 (std::is_signed_v<InnerIdType>) → if_statement@828 (offset_id < 0)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ std::numeric_limits<InnerIdType>::max  [L832] if_statement@832 (offset_id >= std::numeric_limits<InnerIdType>::max() || static_cast<uint64_t>(offset_id) > std::numeric_limits<uint64_t>::max() / static_cast<uint64_t>(code_size_))
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ std::numeric_limits<uint64_t>::max  [L834] if_statement@832 (offset_id >= std::numeric_limits<InnerIdType>::max() || static_cast<uint64_t>(offset_id) > std::numeric_limits<uint64_t>::max() / static_cast<uint64_t>(code_size_))
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ VsagException  [L835] if_statement@832 (offset_id >= std::numeric_limits<InnerIdType>::max() || static_cast<uint64_t>(offset_id) > std::numeric_limits<uint64_t>::max() / static_cast<uint64_t>(code_size_))
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ encode_vector  [L840] 函数本体；短路求值/提前返回见源码
  │    │    │  ↳ 复用节点 #31 BucketDataCell<QuantTmpl, IOTmpl>::encode_vector（本树前文已展开）
  │    │    ├─ this->inner_ids_[bucket_id].size  [L844] 函数本体；短路求值/提前返回见源码
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ check_valid_bucket_capacity  [L845] 函数本体；短路求值/提前返回见源码
  │    │    │  ↳ 复用节点 #36 BucketDataCell<QuantTmpl, IOTmpl>::check_valid_bucket_capacity（本树前文已展开）
  │    │    ├─ this->inner_ids_[bucket_id].resize  [L847] if_statement@846 (need_resize)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ this->residual_bias_[bucket_id].resize  [L849] if_statement@846 (need_resize) → if_statement@848 (use_residual_ && metric_ == MetricType::METRIC_TYPE_L2SQR)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ std::min<uint64_t>  [L853] if_statement@852 (offset_id > this->bucket_sizes_[bucket_id])
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ std::fill_n  [L858] if_statement@852 (offset_id > this->bucket_sizes_[bucket_id])
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ std::min<uint64_t>  [L860] if_statement@852 (offset_id > this->bucket_sizes_[bucket_id]) → for_statement@859 hole_offset < offset_id
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ this->datas_[bucket_id].Write  [L862] if_statement@852 (offset_id > this->bucket_sizes_[bucket_id]) → for_statement@859 hole_offset < offset_id
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ this->datas_[bucket_id].Write  [L869] 函数本体；短路求值/提前返回见源码
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ std::max  [L878] 函数本体；短路求值/提前返回见源码
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ bucket_->InsertVector  [L225] lambda@214（定义体，执行时间取决于调用/调度） → for_statement@215 j < buckets_per_data_ → if_statement@220 (precise_bucket_ != nullptr) [else 分支]
  │    │  #38 BucketDataCell<QuantTmpl, IOTmpl>::InsertVector [src/datacell/bucket_datacell.h:660]
  │    │    ├─ check_valid_bucket_id  [L664] 函数本体；短路求值/提前返回见源码
  │    │    │  ↳ 复用节点 #30 BucketDataCell::check_valid_bucket_id（本树前文已展开）
  │    │    ├─ VsagException  [L666] if_statement@665 (inner_id == EMPTY_INNER_ID)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ encode_vector  [L672] 函数本体；短路求值/提前返回见源码
  │    │    │  ↳ 复用节点 #31 BucketDataCell<QuantTmpl, IOTmpl>::encode_vector（本树前文已展开）
  │    │    ├─ std::numeric_limits<InnerIdType>::max  [L676] if_statement@676 (offset_id >= std::numeric_limits<InnerIdType>::max() || static_cast<uint64_t>(offset_id) > std::numeric_limits<uint64_t>::max() / static_cast<uint64_t>(code_size_))
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ std::numeric_limits<uint64_t>::max  [L678] if_statement@676 (offset_id >= std::numeric_limits<InnerIdType>::max() || static_cast<uint64_t>(offset_id) > std::numeric_limits<uint64_t>::max() / static_cast<uint64_t>(code_size_))
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ VsagException  [L679] if_statement@676 (offset_id >= std::numeric_limits<InnerIdType>::max() || static_cast<uint64_t>(offset_id) > std::numeric_limits<uint64_t>::max() / static_cast<uint64_t>(code_size_))
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ check_valid_bucket_capacity  [L682] 函数本体；短路求值/提前返回见源码
  │    │    │  ↳ 复用节点 #36 BucketDataCell<QuantTmpl, IOTmpl>::check_valid_bucket_capacity（本树前文已展开）
  │    │    ├─ this->inner_ids_[bucket_id].size  [L682] 函数本体；短路求值/提前返回见源码
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ this->datas_[bucket_id].Write  [L683] 函数本体；短路求值/提前返回见源码
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ this->inner_ids_[bucket_id].size  [L687] if_statement@687 (this->inner_ids_[bucket_id].size() < next_size)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ this->inner_ids_[bucket_id].resize  [L688] if_statement@687 (this->inner_ids_[bucket_id].size() < next_size)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ this->residual_bias_[bucket_id].resize  [L690] if_statement@687 (this->inner_ids_[bucket_id].size() < next_size) → if_statement@689 (use_residual_ && metric_ == MetricType::METRIC_TYPE_L2SQR)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ this->attr_filter_index_->Insert  [L236] lambda@214（定义体，执行时间取决于调用/调度） → for_statement@215 j < buckets_per_data_ → if_statement@233 (use_attribute_filter_ and this->attr_filter_index_ != nullptr and attr_sets != nullptr)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ this->extra_infos_->InsertExtraInfo  [L239] lambda@214（定义体，执行时间取决于调用/调度） → for_statement@215 j < buckets_per_data_ → if_statement@238 (extra_info_size > 0)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ futures.emplace_back  [L249] for_statement@247 i < num_element → if_statement@248 (this->thread_pool_ != nullptr)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ thread_pool_->GeneralEnqueue  [L249] for_statement@247 i < num_element → if_statement@248 (this->thread_pool_ != nullptr)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ add_func  [L251] for_statement@247 i < num_element → if_statement@248 (this->thread_pool_ != nullptr) [else 分支]
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ std::current_exception  [L255] catch_clause@254
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ future.get  [L261] if_statement@258 (this->thread_pool_ != nullptr) → for_range_loop@259
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ std::current_exception  [L264] if_statement@258 (this->thread_pool_ != nullptr) → for_range_loop@259 → catch_clause@262 → if_statement@263 (first_exception == nullptr)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ std::rethrow_exception  [L270] if_statement@269 (first_exception != nullptr)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ this->bucket_->Package  [L272] 函数本体；短路求值/提前返回见源码
  │    │  #39 BucketDataCell::Package [src/datacell/bucket_datacell.h:132]
  │    │    ├─ GetQuantizerName  [L134] if_statement@134 (GetQuantizerName() == QUANTIZATION_TYPE_VALUE_PQFS)
  │    │    │  ↳ 复用节点 #21 BucketDataCell::GetQuantizerName（本树前文已展开）
  │    │    ├─ this->package_fastscan  [L135] if_statement@134 (GetQuantizerName() == QUANTIZATION_TYPE_VALUE_PQFS)
  │    │    │  #40 BucketDataCell<QuantTmpl, IOTmpl>::package_fastscan [src/datacell/bucket_datacell.h:934]
  │    │    │    ├─ this->datas_[i].Acquire  [L942] for_statement@937 i < this->bucket_count_
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ lease.Data  [L943] for_statement@937 i < this->bucket_count_
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ quantizer_->Package32  [L950] for_statement@937 i < this->bucket_count_ → while_statement@945 (begin < bucket_size)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ this->datas_[i].Write  [L951] for_statement@937 i < this->bucket_count_ → while_statement@945 (begin < bucket_size)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ this->precise_bucket_->Package  [L274] if_statement@273 (precise_bucket_ != nullptr)
  │    │  ↳ 复用节点 #39 BucketDataCell::Package（本树前文已展开）
  │    ├─ this->cal_memory_usage  [L277] if_statement@276 (need_cal_memory_usage)
  │    │  #41 IVF::cal_memory_usage [src/algorithm/ivf/ivf.cpp:616]
  │    │    ├─ this->bucket_->GetMemoryUsage  [L619] 函数本体；短路求值/提前返回见源码
  │    │    │  #42 BucketDataCell::GetMemoryUsage [src/datacell/bucket_datacell.h:189]
  │    │    │    ├─ this->datas_[bucket_id].GetMemoryUsage  [L193] for_statement@192 bucket_id < this->bucket_count_
  │    │    │    │  ↳ 复用节点 #42 BucketDataCell::GetMemoryUsage（本树前文已展开）
  │    │    │    ├─ this->inner_ids_[bucket_id].size  [L194] for_statement@192 bucket_id < this->bucket_count_
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ this->residual_bias_[bucket_id].size  [L195] for_statement@192 bucket_id < this->bucket_count_
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ precise_bucket_->GetMemoryUsage  [L621] if_statement@620 (use_reorder_) → conditional_expression@621 precise_bucket_ != nullptr
  │    │    │  ↳ 复用节点 #42 BucketDataCell::GetMemoryUsage（本树前文已展开）
  │    │    ├─ reorder_codes_->GetMemoryUsage  [L622] if_statement@620 (use_reorder_) → conditional_expression@621 precise_bucket_ != nullptr
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ this->extra_infos_->GetMemoryUsage  [L625] if_statement@624 (this->extra_info_size_ > 0 and this->extra_infos_ != nullptr)
  │    │    │  #43 IVF::GetMemoryUsage [src/algorithm/ivf/ivf.cpp:639]
  │    │    │    ├─ this->current_memory_usage_.load  [L644] 函数本体；短路求值/提前返回见源码
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ this->attr_filter_index_->GetMemoryUsage  [L647] if_statement@646 (this->attr_filter_index_ != nullptr)
  │    │    │    │  ↳ 复用节点 #43 IVF::GetMemoryUsage（本树前文已展开）
  │    │    ├─ this->label_table_->GetMemoryUsage  [L627] 函数本体；短路求值/提前返回见源码
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ location_map_.size  [L628] 函数本体；短路求值/提前返回见源码
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ partition_strategy_->GetMemoryUsage  [L629] 函数本体；短路求值/提前返回见源码
  │    │    │  ├─ 以下为分派/重载候选，并非全部依次执行
  │    │    │  #44 IVFNearestPartition::GetMemoryUsage [src/algorithm/ivf/ivf_nearest_partition.cpp:303]
  │    │    │    ├─ this->route_index_ptr_->GetMemoryUsage  [L307] if_statement@306 (this->use_route_graph_)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ this->centroids_.size  [L309] 函数本体；短路求值/提前返回见源码
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ this->norms_.size  [L310] 函数本体；短路求值/提前返回见源码
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │  #45 IVFPartitionStrategy::GetMemoryUsage [src/algorithm/ivf/ivf_partition_strategy.h:93]
  │    │    ├─ g->GetMemoryUsage  [L632] for_range_loop@630 → if_statement@631 (g != nullptr)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ this->current_memory_usage_.store  [L636] 函数本体；短路求值/提前返回见源码
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ this->build_bucket_graphs  [L114] if_statement@113 (graph_build_threshold_ > 0)
  │  #46 IVF::build_bucket_graphs [src/algorithm/ivf/ivf_build.cpp:324]
  │    ├─ std::make_shared<GraphDataCellParameter>  [L330] if_statement@329 (graph_param_ == nullptr)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ bucket_graphs_.resize  [L336] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ bucket_->GetBucketSize  [L339] lambda@338（定义体，执行时间取决于调用/调度）
  │    │  #47 BucketDataCell::GetBucketSize [src/datacell/bucket_datacell.h:180]
  │    │    ├─ check_valid_bucket_id  [L182] 函数本体；短路求值/提前返回见源码
  │    │    │  ↳ 复用节点 #30 BucketDataCell::check_valid_bucket_id（本树前文已展开）
  │    ├─ bucket_->GetInnerIds  [L344] lambda@338（定义体，执行时间取决于调用/调度）
  │    │  #48 BucketDataCell::GetInnerIds [src/datacell/bucket_datacell.h:120]
  │    │    ├─ check_valid_bucket_id  [L122] 函数本体；短路求值/提前返回见源码
  │    │    │  ↳ 复用节点 #30 BucketDataCell::check_valid_bucket_id（本树前文已展开）
  │    │    ├─ this->inner_ids_[bucket_id].data  [L123] 函数本体；短路求值/提前返回见源码
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ valid_ids.reserve  [L346] lambda@338（定义体，执行时间取决于调用/调度）
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ std::numeric_limits<InnerIdType>::max  [L348] lambda@338（定义体，执行时间取决于调用/调度） → for_statement@347 i < static_cast<InnerIdType>(bucket_size) → if_statement@348 (inner_ids[i] != std::numeric_limits<InnerIdType>::max())
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ valid_ids.push_back  [L349] lambda@338（定义体，执行时间取决于调用/调度） → for_statement@347 i < static_cast<InnerIdType>(bucket_size) → if_statement@348 (inner_ids[i] != std::numeric_limits<InnerIdType>::max())
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ valid_ids.size  [L352] lambda@338（定义体，执行时间取决于调用/调度） → if_statement@352 (valid_ids.size() < static_cast<uint64_t>(graph_build_threshold_))
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ std::min  [L357] lambda@338（定义体，执行时间取决于调用/调度）
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ valid_ids.size  [L357] lambda@338（定义体，执行时间取决于调用/调度）
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ GraphInterface::MakeInstance  [L362] lambda@338（定义体，执行时间取决于调用/调度）
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ graph->Resize  [L363] lambda@338（定义体，执行时间取决于调用/调度）
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ graph->SetTotalCount  [L364] lambda@338（定义体，执行时间取决于调用/调度）
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ graph->SetMaximumDegree  [L365] lambda@338（定义体，执行时间取决于调用/调度）
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ std::make_shared<EmptyMutex>  [L367] lambda@338（定义体，执行时间取决于调用/调度）
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ valid_ids.front  [L370] lambda@338（定义体，执行时间取决于调用/调度）
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ graph->InsertNeighborsById  [L371] lambda@338（定义体，执行时间取决于调用/调度）
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ Vector<InnerIdType>  [L371] lambda@338（定义体，执行时间取决于调用/调度）
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ std::make_shared<VisitedList>  [L372] lambda@338（定义体，执行时间取决于调用/调度）
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ valid_ids.size  [L373] lambda@338（定义体，执行时间取决于调用/调度） → for_statement@373 node_pos < valid_ids.size()
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ std::min  [L377] lambda@338（定义体，执行时间取决于调用/调度） → for_statement@373 node_pos < valid_ids.size()
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ visited->Reset  [L380] lambda@338（定义体，执行时间取决于调用/调度） → for_statement@373 node_pos < valid_ids.size()
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ searcher.Search  [L382] lambda@338（定义体，执行时间取决于调用/调度） → for_statement@373 node_pos < valid_ids.size()
  │    │  ├─ 以下为分派/重载候选，并非全部依次执行
  │    │  #49 BasicSearcher::Search [src/impl/searcher/basic_searcher.cpp:76]
  │    │    ├─ this->search_impl<KNN_SEARCH>  [L86] if_statement@85 (inner_search_param.search_mode == KNN_SEARCH)
  │    │    │  ├─ 以下为分派/重载候选，并非全部依次执行
  │    │    │  #50 BasicSearcher::search_impl [src/impl/searcher/basic_searcher.cpp:174]
  │    │    │    ├─ select_query_allocator  [L181] 函数本体；短路求值/提前返回见源码
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ std::make_shared<StandardHeap<true, false>>  [L182] 函数本体；短路求值/提前返回见源码
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ std::make_shared<StandardHeap<true, false>>  [L183] 函数本体；短路求值/提前返回见源码
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ distance_provider.OriginalId  [L188] lambda@187（定义体，执行时间取决于调用/调度）
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ distance_provider.IsValid  [L189] lambda@187（定义体，执行时间取决于调用/调度）
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ inner_search_param.is_inner_id_allowed->CheckValid  [L191] lambda@187（定义体，执行时间取决于调用/调度）
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ attr_filter->CheckValid  [L192] lambda@187（定义体，执行时间取决于调用/调度）
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ distance_provider.QueryDistance  [L197] 函数本体；短路求值/提前返回见源码
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ reasoning->RecordVisit  [L201] if_statement@200 (reasoning != nullptr)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ distance_provider.OriginalId  [L201] if_statement@200 (reasoning != nullptr)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ check_func  [L203] if_statement@203 (check_func(ep))
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ is_result_distance_eligible<mode>  [L204] if_statement@203 (check_func(ep)) → if_statement@204 (is_result_distance_eligible<mode>(dist, inner_search_param))
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ top_candidates->Push  [L205] if_statement@203 (check_func(ep)) → if_statement@204 (is_result_distance_eligible<mode>(dist, inner_search_param))
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ reasoning->RecordFilterReject  [L208] if_statement@203 (check_func(ep)) [else 分支] → if_statement@207 (reasoning != nullptr)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ distance_provider.OriginalId  [L208] if_statement@203 (check_func(ep)) [else 分支] → if_statement@207 (reasoning != nullptr)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ top_candidates->Empty  [L211] if_statement@210 (mode == InnerSearchMode::RANGE_SEARCH) → if_statement@211 (dist > inner_search_param.radius + THRESHOLD_ERROR && not top_candidates->Empty())
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ top_candidates->Pop  [L212] if_statement@210 (mode == InnerSearchMode::RANGE_SEARCH) → if_statement@211 (dist > inner_search_param.radius + THRESHOLD_ERROR && not top_candidates->Empty())
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ candidate_set->Push  [L215] 函数本体；短路求值/提前返回见源码
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ traversal_priority  [L215] 函数本体；短路求值/提前返回见源码
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ vl->Set  [L216] 函数本体；短路求值/提前返回见源码
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ top_candidates->Empty  [L218] conditional_expression@218 top_candidates->Empty()
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ std::numeric_limits<float>::max  [L218] conditional_expression@218 top_candidates->Empty()
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ top_candidates->Top  [L218] conditional_expression@218 top_candidates->Empty()
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ graph->MaximumDegree  [L219] 函数本体；短路求值/提前返回见源码
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ graph->MaximumDegree  [L220] 函数本体；短路求值/提前返回见源码
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ graph->MaximumDegree  [L221] 函数本体；短路求值/提前返回见源码
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ candidate_set->Empty  [L222] while_statement@222 (not candidate_set->Empty())
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ candidate_set->Top  [L228] while_statement@222 (not candidate_set->Empty()) → if_statement@227 (mode == InnerSearchMode::KNN_SEARCH) → if_statement@228 (-candidate_set->Top().first > lower_bound && top_candidates->Size() >= ef)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ top_candidates->Size  [L228] while_statement@222 (not candidate_set->Empty()) → if_statement@227 (mode == InnerSearchMode::KNN_SEARCH) → if_statement@228 (-candidate_set->Top().first > lower_bound && top_candidates->Size() >= ef)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ candidate_set->Top  [L232] while_statement@222 (not candidate_set->Empty())
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ candidate_set->Pop  [L233] while_statement@222 (not candidate_set->Empty())
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ candidate_set->Empty  [L234] while_statement@222 (not candidate_set->Empty()) → if_statement@234 (not candidate_set->Empty())
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ graph->Prefetch  [L235] while_statement@222 (not candidate_set->Empty()) → if_statement@234 (not candidate_set->Empty())
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ candidate_set->Top  [L235] while_statement@222 (not candidate_set->Empty()) → if_statement@234 (not candidate_set->Empty())
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ visit  [L238] while_statement@222 (not candidate_set->Empty())
  │    │    │    │  #51 BasicSearcher::visit [src/impl/searcher/basic_searcher.cpp:43]
  │    │    │    │    ├─ graph->GetNeighbors  [L55] if_statement@53 (this->mutex_array_ != nullptr)
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ graph->GetNeighbors  [L57] if_statement@53 (this->mutex_array_ != nullptr) [else 分支]
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ neighbors.size  [L60] for_statement@60 i < neighbors.size()
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ neighbors.size  [L61] for_statement@60 i < neighbors.size() → if_statement@61 (i + prefetch_stride_visit_ < neighbors.size())
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ vl->Prefetch  [L62] for_statement@60 i < neighbors.size() → if_statement@61 (i + prefetch_stride_visit_ < neighbors.size())
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ vl->Get  [L64] for_statement@60 i < neighbors.size() → if_statement@64 (not vl->Get(neighbors[i]))
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ vl->Set  [L65] for_statement@60 i < neighbors.size() → if_statement@64 (not vl->Get(neighbors[i]))
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ skip_strategy->ShouldVisit  [L67] for_statement@60 i < neighbors.size() → if_statement@64 (not vl->Get(neighbors[i])) → if_statement@66 (not filter || count_no_visited == 0 || skip_strategy == nullptr || skip_strategy->ShouldVisit() || filter->CheckValid(neighbors[i]))
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ filter->CheckValid  [L67] for_statement@60 i < neighbors.size() → if_statement@64 (not vl->Get(neighbors[i])) → if_statement@66 (not filter || count_no_visited == 0 || skip_strategy == nullptr || skip_strategy->ShouldVisit() || filter->CheckValid(neighbors[i]))
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ distance_provider.BatchQueryDistance  [L239] while_statement@222 (not candidate_set->Empty())
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ line_dists.data  [L240] while_statement@222 (not candidate_set->Empty())
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ to_be_visited_id.data  [L240] while_statement@222 (not candidate_set->Empty())
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ distance_provider.IsValid  [L245] while_statement@222 (not candidate_set->Empty()) → for_statement@242 i < count_no_visited → if_statement@245 (not distance_provider.IsValid(id))
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ reasoning->RecordVisit  [L249] while_statement@222 (not candidate_set->Empty()) → for_statement@242 i < count_no_visited → if_statement@248 (reasoning != nullptr)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ distance_provider.OriginalId  [L249] while_statement@222 (not candidate_set->Empty()) → for_statement@242 i < count_no_visited → if_statement@248 (reasoning != nullptr)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ is_finite_distance  [L251] while_statement@222 (not candidate_set->Empty()) → for_statement@242 i < count_no_visited → if_statement@251 (not is_finite_distance(dist))
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ candidate_set->Push  [L252] while_statement@222 (not candidate_set->Empty()) → for_statement@242 i < count_no_visited → if_statement@251 (not is_finite_distance(dist))
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ traversal_priority  [L252] while_statement@222 (not candidate_set->Empty()) → for_statement@242 i < count_no_visited → if_statement@251 (not is_finite_distance(dist))
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ check_func  [L253] while_statement@222 (not candidate_set->Empty()) → for_statement@242 i < count_no_visited → if_statement@251 (not is_finite_distance(dist)) → if_statement@253 (check_func(id) and is_result_distance_eligible<mode>(dist, inner_search_param))
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ is_result_distance_eligible<mode>  [L254] while_statement@222 (not candidate_set->Empty()) → for_statement@242 i < count_no_visited → if_statement@251 (not is_finite_distance(dist)) → if_statement@253 (check_func(id) and is_result_distance_eligible<mode>(dist, inner_search_param))
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ top_candidates->Push  [L255] while_statement@222 (not candidate_set->Empty()) → for_statement@242 i < count_no_visited → if_statement@251 (not is_finite_distance(dist)) → if_statement@253 (check_func(id) and is_result_distance_eligible<mode>(dist, inner_search_param))
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ top_candidates->Size  [L257] while_statement@222 (not candidate_set->Empty()) → for_statement@242 i < count_no_visited → if_statement@251 (not is_finite_distance(dist)) → if_statement@253 (check_func(id) and is_result_distance_eligible<mode>(dist, inner_search_param)) → if_statement@256 (mode == InnerSearchMode::KNN_SEARCH) → if_statement@257 (top_candidates->Size() > ef)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ reasoning->RecordEviction  [L259] while_statement@222 (not candidate_set->Empty()) → for_statement@242 i < count_no_visited → if_statement@251 (not is_finite_distance(dist)) → if_statement@253 (check_func(id) and is_result_distance_eligible<mode>(dist, inner_search_param)) → if_statement@256 (mode == InnerSearchMode::KNN_SEARCH) → if_statement@257 (top_candidates->Size() > ef) → if_statement@258 (reasoning != nullptr)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ distance_provider.OriginalId  [L260] while_statement@222 (not candidate_set->Empty()) → for_statement@242 i < count_no_visited → if_statement@251 (not is_finite_distance(dist)) → if_statement@253 (check_func(id) and is_result_distance_eligible<mode>(dist, inner_search_param)) → if_statement@256 (mode == InnerSearchMode::KNN_SEARCH) → if_statement@257 (top_candidates->Size() > ef) → if_statement@258 (reasoning != nullptr)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ top_candidates->Top  [L260] while_statement@222 (not candidate_set->Empty()) → for_statement@242 i < count_no_visited → if_statement@251 (not is_finite_distance(dist)) → if_statement@253 (check_func(id) and is_result_distance_eligible<mode>(dist, inner_search_param)) → if_statement@256 (mode == InnerSearchMode::KNN_SEARCH) → if_statement@257 (top_candidates->Size() > ef) → if_statement@258 (reasoning != nullptr)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ top_candidates->Pop  [L263] while_statement@222 (not candidate_set->Empty()) → for_statement@242 i < count_no_visited → if_statement@251 (not is_finite_distance(dist)) → if_statement@253 (check_func(id) and is_result_distance_eligible<mode>(dist, inner_search_param)) → if_statement@256 (mode == InnerSearchMode::KNN_SEARCH) → if_statement@257 (top_candidates->Size() > ef)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ top_candidates->Pop  [L266] while_statement@222 (not candidate_set->Empty()) → for_statement@242 i < count_no_visited → if_statement@251 (not is_finite_distance(dist)) → if_statement@253 (check_func(id) and is_result_distance_eligible<mode>(dist, inner_search_param)) → if_statement@256 (mode == InnerSearchMode::KNN_SEARCH) [else 分支] → if_statement@265 (dist > inner_search_param.radius)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ top_candidates->Empty  [L269] while_statement@222 (not candidate_set->Empty()) → for_statement@242 i < count_no_visited → if_statement@251 (not is_finite_distance(dist)) → if_statement@269 (not top_candidates->Empty())
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ top_candidates->Top  [L270] while_statement@222 (not candidate_set->Empty()) → for_statement@242 i < count_no_visited → if_statement@251 (not is_finite_distance(dist)) → if_statement@269 (not top_candidates->Empty())
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ top_candidates->Size  [L274] while_statement@222 (not candidate_set->Empty()) → for_statement@242 i < count_no_visited → if_statement@274 (top_candidates->Size() < ef || lower_bound > dist || (mode == InnerSearchMode::RANGE_SEARCH && dist <= inner_search_param.radius + THRESHOLD_ERROR))
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ candidate_set->Push  [L277] while_statement@222 (not candidate_set->Empty()) → for_statement@242 i < count_no_visited → if_statement@274 (top_candidates->Size() < ef || lower_bound > dist || (mode == InnerSearchMode::RANGE_SEARCH && dist <= inner_search_param.radius + THRESHOLD_ERROR))
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ distance_provider.Prefetch  [L278] while_statement@222 (not candidate_set->Empty()) → for_statement@242 i < count_no_visited → if_statement@274 (top_candidates->Size() < ef || lower_bound > dist || (mode == InnerSearchMode::RANGE_SEARCH && dist <= inner_search_param.radius + THRESHOLD_ERROR))
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ candidate_set->Top  [L278] while_statement@222 (not candidate_set->Empty()) → for_statement@242 i < count_no_visited → if_statement@274 (top_candidates->Size() < ef || lower_bound > dist || (mode == InnerSearchMode::RANGE_SEARCH && dist <= inner_search_param.radius + THRESHOLD_ERROR))
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ check_func  [L279] while_statement@222 (not candidate_set->Empty()) → for_statement@242 i < count_no_visited → if_statement@274 (top_candidates->Size() < ef || lower_bound > dist || (mode == InnerSearchMode::RANGE_SEARCH && dist <= inner_search_param.radius + THRESHOLD_ERROR)) → if_statement@279 (check_func(id))
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ top_candidates->Push  [L280] while_statement@222 (not candidate_set->Empty()) → for_statement@242 i < count_no_visited → if_statement@274 (top_candidates->Size() < ef || lower_bound > dist || (mode == InnerSearchMode::RANGE_SEARCH && dist <= inner_search_param.radius + THRESHOLD_ERROR)) → if_statement@279 (check_func(id))
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ reasoning->RecordFilterReject  [L282] while_statement@222 (not candidate_set->Empty()) → for_statement@242 i < count_no_visited → if_statement@274 (top_candidates->Size() < ef || lower_bound > dist || (mode == InnerSearchMode::RANGE_SEARCH && dist <= inner_search_param.radius + THRESHOLD_ERROR)) → if_statement@279 (check_func(id)) [else 分支] → if_statement@281 (reasoning != nullptr)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ distance_provider.OriginalId  [L282] while_statement@222 (not candidate_set->Empty()) → for_statement@242 i < count_no_visited → if_statement@274 (top_candidates->Size() < ef || lower_bound > dist || (mode == InnerSearchMode::RANGE_SEARCH && dist <= inner_search_param.radius + THRESHOLD_ERROR)) → if_statement@279 (check_func(id)) [else 分支] → if_statement@281 (reasoning != nullptr)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ top_candidates->Size  [L285] while_statement@222 (not candidate_set->Empty()) → for_statement@242 i < count_no_visited → if_statement@274 (top_candidates->Size() < ef || lower_bound > dist || (mode == InnerSearchMode::RANGE_SEARCH && dist <= inner_search_param.radius + THRESHOLD_ERROR)) → if_statement@284 (mode == InnerSearchMode::KNN_SEARCH) → if_statement@285 (top_candidates->Size() > ef)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ reasoning->RecordEviction  [L287] while_statement@222 (not candidate_set->Empty()) → for_statement@242 i < count_no_visited → if_statement@274 (top_candidates->Size() < ef || lower_bound > dist || (mode == InnerSearchMode::RANGE_SEARCH && dist <= inner_search_param.radius + THRESHOLD_ERROR)) → if_statement@284 (mode == InnerSearchMode::KNN_SEARCH) → if_statement@285 (top_candidates->Size() > ef) → if_statement@286 (reasoning != nullptr)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ distance_provider.OriginalId  [L288] while_statement@222 (not candidate_set->Empty()) → for_statement@242 i < count_no_visited → if_statement@274 (top_candidates->Size() < ef || lower_bound > dist || (mode == InnerSearchMode::RANGE_SEARCH && dist <= inner_search_param.radius + THRESHOLD_ERROR)) → if_statement@284 (mode == InnerSearchMode::KNN_SEARCH) → if_statement@285 (top_candidates->Size() > ef) → if_statement@286 (reasoning != nullptr)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ top_candidates->Top  [L288] while_statement@222 (not candidate_set->Empty()) → for_statement@242 i < count_no_visited → if_statement@274 (top_candidates->Size() < ef || lower_bound > dist || (mode == InnerSearchMode::RANGE_SEARCH && dist <= inner_search_param.radius + THRESHOLD_ERROR)) → if_statement@284 (mode == InnerSearchMode::KNN_SEARCH) → if_statement@285 (top_candidates->Size() > ef) → if_statement@286 (reasoning != nullptr)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ top_candidates->Pop  [L290] while_statement@222 (not candidate_set->Empty()) → for_statement@242 i < count_no_visited → if_statement@274 (top_candidates->Size() < ef || lower_bound > dist || (mode == InnerSearchMode::RANGE_SEARCH && dist <= inner_search_param.radius + THRESHOLD_ERROR)) → if_statement@284 (mode == InnerSearchMode::KNN_SEARCH) → if_statement@285 (top_candidates->Size() > ef)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ top_candidates->Empty  [L293] while_statement@222 (not candidate_set->Empty()) → for_statement@242 i < count_no_visited → if_statement@274 (top_candidates->Size() < ef || lower_bound > dist || (mode == InnerSearchMode::RANGE_SEARCH && dist <= inner_search_param.radius + THRESHOLD_ERROR)) → if_statement@293 (not top_candidates->Empty())
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ top_candidates->Top  [L294] while_statement@222 (not candidate_set->Empty()) → for_statement@242 i < count_no_visited → if_statement@274 (top_candidates->Size() < ef || lower_bound > dist || (mode == InnerSearchMode::RANGE_SEARCH && dist <= inner_search_param.radius + THRESHOLD_ERROR)) → if_statement@293 (not top_candidates->Empty())
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ top_candidates->Size  [L300] if_statement@299 (mode == InnerSearchMode::KNN_SEARCH) → while_statement@300 (top_candidates->Size() > inner_search_param.topk)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ top_candidates->Pop  [L301] if_statement@299 (mode == InnerSearchMode::KNN_SEARCH) → while_statement@300 (top_candidates->Size() > inner_search_param.topk)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ top_candidates->Size  [L305] if_statement@299 (mode == InnerSearchMode::KNN_SEARCH) [else 分支] → if_statement@304 (inner_search_param.range_search_limit_size > 0) → while_statement@305 (top_candidates->Size() > inner_search_param.range_search_limit_size)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ top_candidates->Pop  [L306] if_statement@299 (mode == InnerSearchMode::KNN_SEARCH) [else 分支] → if_statement@304 (inner_search_param.range_search_limit_size > 0) → while_statement@305 (top_candidates->Size() > inner_search_param.range_search_limit_size)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ top_candidates->Empty  [L309] if_statement@299 (mode == InnerSearchMode::KNN_SEARCH) [else 分支] → while_statement@309 (not top_candidates->Empty() && top_candidates->Top().first > inner_search_param.radius + THRESHOLD_ERROR)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ top_candidates->Top  [L310] if_statement@299 (mode == InnerSearchMode::KNN_SEARCH) [else 分支] → while_statement@309 (not top_candidates->Empty() && top_candidates->Top().first > inner_search_param.radius + THRESHOLD_ERROR)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ top_candidates->Pop  [L311] if_statement@299 (mode == InnerSearchMode::KNN_SEARCH) [else 分支] → while_statement@309 (not top_candidates->Empty() && top_candidates->Top().first > inner_search_param.radius + THRESHOLD_ERROR)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ ctx->stats->dist_cmp.fetch_add  [L315] if_statement@314 (ctx != nullptr && ctx->stats != nullptr)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ ctx->stats->hops.fetch_add  [L316] if_statement@314 (ctx != nullptr && ctx->stats != nullptr)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │  #52 BasicSearcher::search_impl [src/impl/searcher/basic_searcher.cpp:322]
  │    │    │    ├─ select_query_allocator  [L332] 函数本体；短路求值/提前返回见源码
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ std::make_shared<StandardHeap<true, false>>  [L334] 函数本体；短路求值/提前返回见源码
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ std::make_shared<StandardHeap<true, false>>  [L335] 函数本体；短路求值/提前返回见源码
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ AcquireQueryComputer  [L341] 函数本体；短路求值/提前返回见源码
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ std::numeric_limits<float>::max  [L351] 函数本体；短路求值/提前返回见源码
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ graph->MaximumDegree  [L356] 函数本体；短路求值/提前返回见源码
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ graph->MaximumDegree  [L357] 函数本体；短路求值/提前返回见源码
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ graph->MaximumDegree  [L358] 函数本体；短路求值/提前返回见源码
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ graph->MaximumDegree  [L359] 函数本体；短路求值/提前返回见源码
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ create_filter_search_skip_strategy  [L360] 函数本体；短路求值/提前返回见源码
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ inner_search_param.is_inner_id_allowed->ValidRatio  [L363] conditional_expression@362 inner_search_param.is_inner_id_allowed != nullptr
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ rabitq_lower_bound_candidates->clear  [L367] if_statement@366 (rabitq_lower_bound_candidates != nullptr)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ iter_ctx->IsFirstUsed  [L370] if_statement@370 (!iter_ctx->IsFirstUsed())
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ iter_ctx->Empty  [L371] if_statement@370 (!iter_ctx->IsFirstUsed()) → if_statement@371 (iter_ctx->Empty())
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ iter_ctx->Empty  [L374] if_statement@370 (!iter_ctx->IsFirstUsed()) → while_statement@374 (!iter_ctx->Empty())
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ iter_ctx->GetTopID  [L375] if_statement@370 (!iter_ctx->IsFirstUsed()) → while_statement@374 (!iter_ctx->Empty())
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ iter_ctx->GetTopDist  [L376] if_statement@370 (!iter_ctx->IsFirstUsed()) → while_statement@374 (!iter_ctx->Empty())
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ vl->Set  [L377] if_statement@370 (!iter_ctx->IsFirstUsed()) → while_statement@374 (!iter_ctx->Empty())
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ iter_ctx->CheckPoint  [L378] if_statement@370 (!iter_ctx->IsFirstUsed()) → while_statement@374 (!iter_ctx->Empty()) → if_statement@378 (iter_ctx->CheckPoint(cur_inner_id))
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ flatten->Query  [L379] if_statement@370 (!iter_ctx->IsFirstUsed()) → while_statement@374 (!iter_ctx->Empty()) → if_statement@378 (iter_ctx->CheckPoint(cur_inner_id))
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ is_result_distance_eligible<mode>  [L382] if_statement@370 (!iter_ctx->IsFirstUsed()) → while_statement@374 (!iter_ctx->Empty()) → if_statement@378 (iter_ctx->CheckPoint(cur_inner_id)) → if_statement@382 (is_result_distance_eligible<mode>(cur_dist, inner_search_param))
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ top_candidates->Push  [L383] if_statement@370 (!iter_ctx->IsFirstUsed()) → while_statement@374 (!iter_ctx->Empty()) → if_statement@378 (iter_ctx->CheckPoint(cur_inner_id)) → if_statement@382 (is_result_distance_eligible<mode>(cur_dist, inner_search_param))
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ candidate_set->Push  [L385] if_statement@370 (!iter_ctx->IsFirstUsed()) → while_statement@374 (!iter_ctx->Empty()) → if_statement@378 (iter_ctx->CheckPoint(cur_inner_id))
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ traversal_priority  [L385] if_statement@370 (!iter_ctx->IsFirstUsed()) → while_statement@374 (!iter_ctx->Empty()) → if_statement@378 (iter_ctx->CheckPoint(cur_inner_id))
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ top_candidates->Empty  [L387] if_statement@370 (!iter_ctx->IsFirstUsed()) → while_statement@374 (!iter_ctx->Empty()) → if_statement@378 (iter_ctx->CheckPoint(cur_inner_id)) → if_statement@386 (mode == InnerSearchMode::RANGE_SEARCH) → if_statement@387 (cur_dist > inner_search_param.radius and not top_candidates->Empty())
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ top_candidates->Pop  [L388] if_statement@370 (!iter_ctx->IsFirstUsed()) → while_statement@374 (!iter_ctx->Empty()) → if_statement@378 (iter_ctx->CheckPoint(cur_inner_id)) → if_statement@386 (mode == InnerSearchMode::RANGE_SEARCH) → if_statement@387 (cur_dist > inner_search_param.radius and not top_candidates->Empty())
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ iter_ctx->PopDiscard  [L392] if_statement@370 (!iter_ctx->IsFirstUsed()) → while_statement@374 (!iter_ctx->Empty())
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ top_candidates->Size  [L395] if_statement@370 (!iter_ctx->IsFirstUsed()) → if_statement@394 (mode == InnerSearchMode::KNN_SEARCH) → while_statement@395 (top_candidates->Size() > ef)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ top_candidates->Top  [L396] if_statement@370 (!iter_ctx->IsFirstUsed()) → if_statement@394 (mode == InnerSearchMode::KNN_SEARCH) → while_statement@395 (top_candidates->Size() > ef)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ iter_ctx->CheckPoint  [L397] if_statement@370 (!iter_ctx->IsFirstUsed()) → if_statement@394 (mode == InnerSearchMode::KNN_SEARCH) → while_statement@395 (top_candidates->Size() > ef) → if_statement@397 (iter_ctx->CheckPoint(cur_node_pair.second))
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ iter_ctx->AddDiscardNode  [L398] if_statement@370 (!iter_ctx->IsFirstUsed()) → if_statement@394 (mode == InnerSearchMode::KNN_SEARCH) → while_statement@395 (top_candidates->Size() > ef) → if_statement@397 (iter_ctx->CheckPoint(cur_node_pair.second))
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ top_candidates->Pop  [L400] if_statement@370 (!iter_ctx->IsFirstUsed()) → if_statement@394 (mode == InnerSearchMode::KNN_SEARCH) → while_statement@395 (top_candidates->Size() > ef)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ top_candidates->Empty  [L403] if_statement@370 (!iter_ctx->IsFirstUsed()) → if_statement@403 (not top_candidates->Empty())
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ top_candidates->Top  [L404] if_statement@370 (!iter_ctx->IsFirstUsed()) → if_statement@403 (not top_candidates->Empty())
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ flatten->QueryWithDistanceLowerBound  [L408] if_statement@370 (!iter_ctx->IsFirstUsed()) [else 分支] → if_statement@407 (inner_search_param.enable_rabitq_one_bit_search)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ flatten->Query  [L410] if_statement@370 (!iter_ctx->IsFirstUsed()) [else 分支] → if_statement@407 (inner_search_param.enable_rabitq_one_bit_search) [else 分支]
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ is_id_allowed->CheckValid  [L412] if_statement@370 (!iter_ctx->IsFirstUsed()) [else 分支] → if_statement@412 (not is_id_allowed || is_id_allowed->CheckValid(ep))
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ is_result_distance_eligible<mode>  [L413] if_statement@370 (!iter_ctx->IsFirstUsed()) [else 分支] → if_statement@412 (not is_id_allowed || is_id_allowed->CheckValid(ep)) → if_statement@413 (is_result_distance_eligible<mode>(dist, inner_search_param))
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ top_candidates->Push  [L414] if_statement@370 (!iter_ctx->IsFirstUsed()) [else 分支] → if_statement@412 (not is_id_allowed || is_id_allowed->CheckValid(ep)) → if_statement@413 (is_result_distance_eligible<mode>(dist, inner_search_param))
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ top_candidates->Top  [L415] if_statement@370 (!iter_ctx->IsFirstUsed()) [else 分支] → if_statement@412 (not is_id_allowed || is_id_allowed->CheckValid(ep)) → if_statement@413 (is_result_distance_eligible<mode>(dist, inner_search_param))
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ candidate_set->Push  [L418] if_statement@370 (!iter_ctx->IsFirstUsed()) [else 分支]
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ traversal_priority  [L418] if_statement@370 (!iter_ctx->IsFirstUsed()) [else 分支]
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ vl->Set  [L419] if_statement@370 (!iter_ctx->IsFirstUsed()) [else 分支]
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ candidate_set->Empty  [L422] while_statement@422 (not candidate_set->Empty())
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ candidate_set->Top  [L427] while_statement@422 (not candidate_set->Empty())
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ top_candidates->Size  [L430] while_statement@422 (not candidate_set->Empty()) → if_statement@429 (mode == InnerSearchMode::KNN_SEARCH) → if_statement@430 ((-current_node_pair.first) > lower_bound && top_candidates->Size() >= ef)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ reasoning->SetTermination  [L432] while_statement@422 (not candidate_set->Empty()) → if_statement@429 (mode == InnerSearchMode::KNN_SEARCH) → if_statement@430 ((-current_node_pair.first) > lower_bound && top_candidates->Size() >= ef) → if_statement@431 (reasoning != nullptr)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ candidate_set->Pop  [L437] while_statement@422 (not candidate_set->Empty())
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ candidate_set->Empty  [L439] while_statement@422 (not candidate_set->Empty()) → if_statement@439 (not candidate_set->Empty())
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ graph->Prefetch  [L440] while_statement@422 (not candidate_set->Empty()) → if_statement@439 (not candidate_set->Empty())
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ candidate_set->Top  [L440] while_statement@422 (not candidate_set->Empty()) → if_statement@439 (not candidate_set->Empty())
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ visit  [L443] while_statement@422 (not candidate_set->Empty())
  │    │    │    │  ↳ 复用节点 #51 BasicSearcher::visit（本树前文已展开）
  │    │    │    ├─ skip_strategy.get  [L447] while_statement@422 (not candidate_set->Empty())
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ top_candidates->Size  [L454] while_statement@422 (not candidate_set->Empty()) → if_statement@454 (inner_search_param.enable_rabitq_one_bit_search and top_candidates->Size() == ef and rabitq_lower_bound_candidates != nullptr)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ flatten->QueryWithDistanceLowerBound  [L457] while_statement@422 (not candidate_set->Empty()) → if_statement@454 (inner_search_param.enable_rabitq_one_bit_search and top_candidates->Size() == ef and rabitq_lower_bound_candidates != nullptr)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ line_dists.data  [L457] while_statement@422 (not candidate_set->Empty()) → if_statement@454 (inner_search_param.enable_rabitq_one_bit_search and top_candidates->Size() == ef and rabitq_lower_bound_candidates != nullptr)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ lower_bound_dists.data  [L458] while_statement@422 (not candidate_set->Empty()) → if_statement@454 (inner_search_param.enable_rabitq_one_bit_search and top_candidates->Size() == ef and rabitq_lower_bound_candidates != nullptr)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ to_be_visited_id.data  [L460] while_statement@422 (not candidate_set->Empty()) → if_statement@454 (inner_search_param.enable_rabitq_one_bit_search and top_candidates->Size() == ef and rabitq_lower_bound_candidates != nullptr)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ flatten->QueryWithDistanceLowerBound  [L464] while_statement@422 (not candidate_set->Empty()) → if_statement@454 (inner_search_param.enable_rabitq_one_bit_search and top_candidates->Size() == ef and rabitq_lower_bound_candidates != nullptr) [else 分支] → if_statement@463 (inner_search_param.enable_rabitq_one_bit_search)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ line_dists.data  [L464] while_statement@422 (not candidate_set->Empty()) → if_statement@454 (inner_search_param.enable_rabitq_one_bit_search and top_candidates->Size() == ef and rabitq_lower_bound_candidates != nullptr) [else 分支] → if_statement@463 (inner_search_param.enable_rabitq_one_bit_search)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ to_be_visited_id.data  [L467] while_statement@422 (not candidate_set->Empty()) → if_statement@454 (inner_search_param.enable_rabitq_one_bit_search and top_candidates->Size() == ef and rabitq_lower_bound_candidates != nullptr) [else 分支] → if_statement@463 (inner_search_param.enable_rabitq_one_bit_search)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ flatten->Query  [L471] while_statement@422 (not candidate_set->Empty()) → if_statement@454 (inner_search_param.enable_rabitq_one_bit_search and top_candidates->Size() == ef and rabitq_lower_bound_candidates != nullptr) [else 分支] → if_statement@463 (inner_search_param.enable_rabitq_one_bit_search) [else 分支]
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ line_dists.data  [L472] while_statement@422 (not candidate_set->Empty()) → if_statement@454 (inner_search_param.enable_rabitq_one_bit_search and top_candidates->Size() == ef and rabitq_lower_bound_candidates != nullptr) [else 分支] → if_statement@463 (inner_search_param.enable_rabitq_one_bit_search) [else 分支]
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ to_be_visited_id.data  [L472] while_statement@422 (not candidate_set->Empty()) → if_statement@454 (inner_search_param.enable_rabitq_one_bit_search and top_candidates->Size() == ef and rabitq_lower_bound_candidates != nullptr) [else 分支] → if_statement@463 (inner_search_param.enable_rabitq_one_bit_search) [else 分支]
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ is_finite_distance  [L477] while_statement@422 (not candidate_set->Empty()) → for_statement@474 i < count_no_visited → if_statement@477 (not is_finite_distance(dist))
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ is_result_distance_eligible<mode>  [L478] while_statement@422 (not candidate_set->Empty()) → for_statement@474 i < count_no_visited → if_statement@477 (not is_finite_distance(dist)) → if_statement@478 (is_result_distance_eligible<mode>(dist, inner_search_param) and (not is_id_allowed || is_id_allowed->CheckValid(cur_id)))
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ is_id_allowed->CheckValid  [L479] while_statement@422 (not candidate_set->Empty()) → for_statement@474 i < count_no_visited → if_statement@477 (not is_finite_distance(dist)) → if_statement@478 (is_result_distance_eligible<mode>(dist, inner_search_param) and (not is_id_allowed || is_id_allowed->CheckValid(cur_id)))
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ top_candidates->Push  [L480] while_statement@422 (not candidate_set->Empty()) → for_statement@474 i < count_no_visited → if_statement@477 (not is_finite_distance(dist)) → if_statement@478 (is_result_distance_eligible<mode>(dist, inner_search_param) and (not is_id_allowed || is_id_allowed->CheckValid(cur_id)))
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ top_candidates->Size  [L482] while_statement@422 (not candidate_set->Empty()) → for_statement@474 i < count_no_visited → if_statement@477 (not is_finite_distance(dist)) → if_statement@478 (is_result_distance_eligible<mode>(dist, inner_search_param) and (not is_id_allowed || is_id_allowed->CheckValid(cur_id))) → if_statement@481 (mode == KNN_SEARCH) → if_statement@482 (top_candidates->Size() > ef)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ top_candidates->Top  [L483] while_statement@422 (not candidate_set->Empty()) → for_statement@474 i < count_no_visited → if_statement@477 (not is_finite_distance(dist)) → if_statement@478 (is_result_distance_eligible<mode>(dist, inner_search_param) and (not is_id_allowed || is_id_allowed->CheckValid(cur_id))) → if_statement@481 (mode == KNN_SEARCH) → if_statement@482 (top_candidates->Size() > ef)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ iter_ctx->CheckPoint  [L484] while_statement@422 (not candidate_set->Empty()) → for_statement@474 i < count_no_visited → if_statement@477 (not is_finite_distance(dist)) → if_statement@478 (is_result_distance_eligible<mode>(dist, inner_search_param) and (not is_id_allowed || is_id_allowed->CheckValid(cur_id))) → if_statement@481 (mode == KNN_SEARCH) → if_statement@482 (top_candidates->Size() > ef) → if_statement@484 (iter_ctx->CheckPoint(evicted.second))
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ iter_ctx->AddDiscardNode  [L485] while_statement@422 (not candidate_set->Empty()) → for_statement@474 i < count_no_visited → if_statement@477 (not is_finite_distance(dist)) → if_statement@478 (is_result_distance_eligible<mode>(dist, inner_search_param) and (not is_id_allowed || is_id_allowed->CheckValid(cur_id))) → if_statement@481 (mode == KNN_SEARCH) → if_statement@482 (top_candidates->Size() > ef) → if_statement@484 (iter_ctx->CheckPoint(evicted.second))
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ top_candidates->Pop  [L487] while_statement@422 (not candidate_set->Empty()) → for_statement@474 i < count_no_visited → if_statement@477 (not is_finite_distance(dist)) → if_statement@478 (is_result_distance_eligible<mode>(dist, inner_search_param) and (not is_id_allowed || is_id_allowed->CheckValid(cur_id))) → if_statement@481 (mode == KNN_SEARCH) → if_statement@482 (top_candidates->Size() > ef)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ top_candidates->Pop  [L490] while_statement@422 (not candidate_set->Empty()) → for_statement@474 i < count_no_visited → if_statement@477 (not is_finite_distance(dist)) → if_statement@478 (is_result_distance_eligible<mode>(dist, inner_search_param) and (not is_id_allowed || is_id_allowed->CheckValid(cur_id))) → if_statement@481 (mode == KNN_SEARCH) [else 分支] → if_statement@489 (dist > inner_search_param.radius)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ iter_ctx->CheckPoint  [L493] while_statement@422 (not candidate_set->Empty()) → for_statement@474 i < count_no_visited → if_statement@477 (not is_finite_distance(dist)) → if_statement@493 (iter_ctx->CheckPoint(cur_id))
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ candidate_set->Push  [L494] while_statement@422 (not candidate_set->Empty()) → for_statement@474 i < count_no_visited → if_statement@477 (not is_finite_distance(dist)) → if_statement@493 (iter_ctx->CheckPoint(cur_id))
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ traversal_priority  [L494] while_statement@422 (not candidate_set->Empty()) → for_statement@474 i < count_no_visited → if_statement@477 (not is_finite_distance(dist)) → if_statement@493 (iter_ctx->CheckPoint(cur_id))
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ flatten->Prefetch  [L495] while_statement@422 (not candidate_set->Empty()) → for_statement@474 i < count_no_visited → if_statement@477 (not is_finite_distance(dist)) → if_statement@493 (iter_ctx->CheckPoint(cur_id))
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ top_candidates->Empty  [L497] while_statement@422 (not candidate_set->Empty()) → for_statement@474 i < count_no_visited → if_statement@477 (not is_finite_distance(dist)) → if_statement@497 (not top_candidates->Empty())
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ top_candidates->Top  [L498] while_statement@422 (not candidate_set->Empty()) → for_statement@474 i < count_no_visited → if_statement@477 (not is_finite_distance(dist)) → if_statement@497 (not top_candidates->Empty())
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ is_id_allowed->CheckValid  [L502] while_statement@422 (not candidate_set->Empty()) → for_statement@474 i < count_no_visited
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ iter_ctx->CheckPoint  [L505] while_statement@422 (not candidate_set->Empty()) → for_statement@474 i < count_no_visited → if_statement@503 (mode == KNN_SEARCH) → if_statement@504 (collect_rabitq_lower_bound and lower_bound_dists[i] < lower_bound and id_allowed and iter_ctx->CheckPoint(cur_id))
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ rabitq_lower_bound_candidates->emplace_back  [L506] while_statement@422 (not candidate_set->Empty()) → for_statement@474 i < count_no_visited → if_statement@503 (mode == KNN_SEARCH) → if_statement@504 (collect_rabitq_lower_bound and lower_bound_dists[i] < lower_bound and id_allowed and iter_ctx->CheckPoint(cur_id))
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ top_candidates->Size  [L509] while_statement@422 (not candidate_set->Empty()) → for_statement@474 i < count_no_visited → if_statement@509 (top_candidates->Size() < ef || lower_bound > dist || (mode == RANGE_SEARCH && dist <= inner_search_param.radius))
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ iter_ctx->CheckPoint  [L511] while_statement@422 (not candidate_set->Empty()) → for_statement@474 i < count_no_visited → if_statement@509 (top_candidates->Size() < ef || lower_bound > dist || (mode == RANGE_SEARCH && dist <= inner_search_param.radius)) → if_statement@511 (!iter_ctx->CheckPoint(cur_id))
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ candidate_set->Push  [L514] while_statement@422 (not candidate_set->Empty()) → for_statement@474 i < count_no_visited → if_statement@509 (top_candidates->Size() < ef || lower_bound > dist || (mode == RANGE_SEARCH && dist <= inner_search_param.radius))
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ flatten->Prefetch  [L515] while_statement@422 (not candidate_set->Empty()) → for_statement@474 i < count_no_visited → if_statement@509 (top_candidates->Size() < ef || lower_bound > dist || (mode == RANGE_SEARCH && dist <= inner_search_param.radius))
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ candidate_set->Top  [L515] while_statement@422 (not candidate_set->Empty()) → for_statement@474 i < count_no_visited → if_statement@509 (top_candidates->Size() < ef || lower_bound > dist || (mode == RANGE_SEARCH && dist <= inner_search_param.radius))
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ top_candidates->Push  [L517] while_statement@422 (not candidate_set->Empty()) → for_statement@474 i < count_no_visited → if_statement@509 (top_candidates->Size() < ef || lower_bound > dist || (mode == RANGE_SEARCH && dist <= inner_search_param.radius)) → if_statement@516 (id_allowed)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ top_candidates->Size  [L521] while_statement@422 (not candidate_set->Empty()) → for_statement@474 i < count_no_visited → if_statement@509 (top_candidates->Size() < ef || lower_bound > dist || (mode == RANGE_SEARCH && dist <= inner_search_param.radius)) → if_statement@520 (mode == KNN_SEARCH) → if_statement@521 (top_candidates->Size() > ef)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ iter_ctx->CheckPoint  [L522] while_statement@422 (not candidate_set->Empty()) → for_statement@474 i < count_no_visited → if_statement@509 (top_candidates->Size() < ef || lower_bound > dist || (mode == RANGE_SEARCH && dist <= inner_search_param.radius)) → if_statement@520 (mode == KNN_SEARCH) → if_statement@521 (top_candidates->Size() > ef) → if_statement@522 (iter_ctx->CheckPoint(top_candidates->Top().second))
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ top_candidates->Top  [L522] while_statement@422 (not candidate_set->Empty()) → for_statement@474 i < count_no_visited → if_statement@509 (top_candidates->Size() < ef || lower_bound > dist || (mode == RANGE_SEARCH && dist <= inner_search_param.radius)) → if_statement@520 (mode == KNN_SEARCH) → if_statement@521 (top_candidates->Size() > ef) → if_statement@522 (iter_ctx->CheckPoint(top_candidates->Top().second))
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ top_candidates->Top  [L523] while_statement@422 (not candidate_set->Empty()) → for_statement@474 i < count_no_visited → if_statement@509 (top_candidates->Size() < ef || lower_bound > dist || (mode == RANGE_SEARCH && dist <= inner_search_param.radius)) → if_statement@520 (mode == KNN_SEARCH) → if_statement@521 (top_candidates->Size() > ef) → if_statement@522 (iter_ctx->CheckPoint(top_candidates->Top().second))
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ iter_ctx->AddDiscardNode  [L524] while_statement@422 (not candidate_set->Empty()) → for_statement@474 i < count_no_visited → if_statement@509 (top_candidates->Size() < ef || lower_bound > dist || (mode == RANGE_SEARCH && dist <= inner_search_param.radius)) → if_statement@520 (mode == KNN_SEARCH) → if_statement@521 (top_candidates->Size() > ef) → if_statement@522 (iter_ctx->CheckPoint(top_candidates->Top().second))
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ top_candidates->Pop  [L526] while_statement@422 (not candidate_set->Empty()) → for_statement@474 i < count_no_visited → if_statement@509 (top_candidates->Size() < ef || lower_bound > dist || (mode == RANGE_SEARCH && dist <= inner_search_param.radius)) → if_statement@520 (mode == KNN_SEARCH) → if_statement@521 (top_candidates->Size() > ef)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ top_candidates->Empty  [L530] while_statement@422 (not candidate_set->Empty()) → for_statement@474 i < count_no_visited → if_statement@509 (top_candidates->Size() < ef || lower_bound > dist || (mode == RANGE_SEARCH && dist <= inner_search_param.radius)) → if_statement@530 (not top_candidates->Empty())
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ top_candidates->Top  [L531] while_statement@422 (not candidate_set->Empty()) → for_statement@474 i < count_no_visited → if_statement@509 (top_candidates->Size() < ef || lower_bound > dist || (mode == RANGE_SEARCH && dist <= inner_search_param.radius)) → if_statement@530 (not top_candidates->Empty())
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ top_candidates->Size  [L538] if_statement@537 (mode == KNN_SEARCH) → while_statement@538 (top_candidates->Size() > inner_search_param.topk)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ top_candidates->Top  [L539] if_statement@537 (mode == KNN_SEARCH) → while_statement@538 (top_candidates->Size() > inner_search_param.topk)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ iter_ctx->CheckPoint  [L540] if_statement@537 (mode == KNN_SEARCH) → while_statement@538 (top_candidates->Size() > inner_search_param.topk) → if_statement@540 (iter_ctx->CheckPoint(cur_node_pair.second))
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ iter_ctx->AddDiscardNode  [L541] if_statement@537 (mode == KNN_SEARCH) → while_statement@538 (top_candidates->Size() > inner_search_param.topk) → if_statement@540 (iter_ctx->CheckPoint(cur_node_pair.second))
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ top_candidates->Pop  [L543] if_statement@537 (mode == KNN_SEARCH) → while_statement@538 (top_candidates->Size() > inner_search_param.topk)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │  #53 BasicSearcher::search_impl [src/impl/searcher/basic_searcher.cpp:551]
  │    │    │    ├─ select_query_allocator  [L562] 函数本体；短路求值/提前返回见源码
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ std::make_shared<StandardHeap<true, false>>  [L564] 函数本体；短路求值/提前返回见源码
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ std::make_shared<StandardHeap<true, false>>  [L565] 函数本体；短路求值/提前返回见源码
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ AcquireQueryComputer  [L575] if_statement@574 (not use_custom_distance and computer == nullptr)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ std::numeric_limits<float>::max  [L584] 函数本体；短路求值/提前返回见源码
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ graph->MaximumDegree  [L589] 函数本体；短路求值/提前返回见源码
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ graph->MaximumDegree  [L590] 函数本体；短路求值/提前返回见源码
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ graph->MaximumDegree  [L591] 函数本体；短路求值/提前返回见源码
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ graph->MaximumDegree  [L592] 函数本体；短路求值/提前返回见源码
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ std::max<uint64_t>  [L595] conditional_expression@594 use_custom_distance
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ std::min<uint64_t>  [L596] conditional_expression@594 use_custom_distance
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ graph->MaximumDegree  [L597] conditional_expression@594 use_custom_distance
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ create_filter_search_skip_strategy  [L600] 函数本体；短路求值/提前返回见源码
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ inner_search_param.is_inner_id_allowed->ValidRatio  [L603] conditional_expression@602 inner_search_param.is_inner_id_allowed != nullptr
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ rabitq_lower_bound_candidates->clear  [L607] if_statement@606 (rabitq_lower_bound_candidates != nullptr)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ inner_search_param.executors.empty  [L611] if_statement@611 (not inner_search_param.executors.empty() and inner_search_param.executors[0] != nullptr)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ inner_search_param.executors[0]->Clear  [L612] if_statement@611 (not inner_search_param.executors.empty() and inner_search_param.executors[0] != nullptr)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ inner_search_param.executors[0]->Run  [L613] if_statement@611 (not inner_search_param.executors.empty() and inner_search_param.executors[0] != nullptr)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ is_id_allowed->CheckValid  [L617] lambda@616（定义体，执行时间取决于调用/调度）
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ attr_ft->CheckValid  [L618] lambda@616（定义体，执行时间取决于调用/调度）
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ flatten->Query  [L624] lambda@622（定义体，执行时间取决于调用/调度） → if_statement@623 (not use_custom_distance)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ CHECK_ARGUMENT  [L627] lambda@622（定义体，执行时间取决于调用/调度）
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ CHECK_ARGUMENT  [L628] lambda@622（定义体，执行时间取决于调用/调度）
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ std::min  [L633] lambda@622（定义体，执行时间取决于调用/调度） → for_statement@630 offset < count
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ label_table->GetLabelById  [L635] lambda@622（定义体，执行时间取决于调用/调度） → for_statement@630 offset < count → for_statement@634 i < batch_count
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ inner_search_param.distance_batch_func  [L637] lambda@622（定义体，执行时间取决于调用/调度） → for_statement@630 offset < count
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ custom_labels.data  [L638] lambda@622（定义体，执行时间取决于调用/调度） → for_statement@630 offset < count
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ ctx->stats->AddDistance  [L640] lambda@622（定义体，执行时间取决于调用/调度） → for_statement@630 offset < count → if_statement@639 (ctx != nullptr and ctx->stats != nullptr)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ CHECK_ARGUMENT  [L644] lambda@622（定义体，执行时间取决于调用/调度） → for_statement@630 offset < count → for_statement@643 i < batch_count
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ is_finite_distance  [L644] lambda@622（定义体，执行时间取决于调用/调度） → for_statement@630 offset < count → for_statement@643 i < batch_count
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ score_ids  [L659] lambda@649（定义体，执行时间取决于调用/调度） → lambda@655（定义体，执行时间取决于调用/调度）
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ neighbors.data  [L659] lambda@649（定义体，执行时间取决于调用/调度） → lambda@655（定义体，执行时间取决于调用/调度）
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ lower_bound_dists.data  [L659] lambda@649（定义体，执行时间取决于调用/调度） → lambda@655（定义体，执行时间取决于调用/调度）
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ reasoning->RecordVisit  [L663] lambda@649（定义体，执行时间取决于调用/调度） → lambda@655（定义体，执行时间取决于调用/调度） → for_statement@661 i < duplicate_count → if_statement@662 (reasoning != nullptr)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ top_candidates->Push  [L665] lambda@649（定义体，执行时间取决于调用/调度） → lambda@655（定义体，执行时间取决于调用/调度） → for_statement@661 i < duplicate_count
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ check_func  [L671] lambda@649（定义体，执行时间取决于调用/调度） → for_range_loop@670 → if_statement@671 (not check_func(item))
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ neighbors.size  [L675] lambda@649（定义体，执行时间取决于调用/调度） → for_range_loop@670 → if_statement@675 (duplicate_count == neighbors.size())
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ submit_duplicates  [L676] lambda@649（定义体，执行时间取决于调用/调度） → for_range_loop@670 → if_statement@675 (duplicate_count == neighbors.size())
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ submit_duplicates  [L679] lambda@649（定义体，执行时间取决于调用/调度）
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ top_candidates->Size  [L682] lambda@649（定义体，执行时间取决于调用/调度） → if_statement@681 (mode == KNN_SEARCH) → while_statement@682 (top_candidates->Size() > ef)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ reasoning->RecordEviction  [L684] lambda@649（定义体，执行时间取决于调用/调度） → if_statement@681 (mode == KNN_SEARCH) → while_statement@682 (top_candidates->Size() > ef) → if_statement@683 (reasoning != nullptr)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ top_candidates->Top  [L684] lambda@649（定义体，执行时间取决于调用/调度） → if_statement@681 (mode == KNN_SEARCH) → while_statement@682 (top_candidates->Size() > ef) → if_statement@683 (reasoning != nullptr)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ top_candidates->Pop  [L686] lambda@649（定义体，执行时间取决于调用/调度） → if_statement@681 (mode == KNN_SEARCH) → while_statement@682 (top_candidates->Size() > ef)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ top_candidates->Empty  [L689] lambda@649（定义体，执行时间取决于调用/调度） → if_statement@689 (not top_candidates->Empty())
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ top_candidates->Top  [L690] lambda@649（定义体，执行时间取决于调用/调度） → if_statement@689 (not top_candidates->Empty())
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ score_ids  [L695] if_statement@694 (use_custom_distance)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ flatten->QueryWithDistanceLowerBound  [L697] if_statement@694 (use_custom_distance) [else 分支] → if_statement@696 (inner_search_param.enable_rabitq_one_bit_search)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ flatten->Query  [L699] if_statement@694 (use_custom_distance) [else 分支] → if_statement@696 (inner_search_param.enable_rabitq_one_bit_search) [else 分支]
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ check_func  [L702] if_statement@702 (check_func(ep) and is_result_distance_eligible<mode>(dist, inner_search_param))
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ is_result_distance_eligible<mode>  [L702] if_statement@702 (check_func(ep) and is_result_distance_eligible<mode>(dist, inner_search_param))
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ top_candidates->Push  [L703] if_statement@702 (check_func(ep) and is_result_distance_eligible<mode>(dist, inner_search_param))
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ is_finite_distance  [L705] if_statement@705 (not is_finite_distance(dist) and inner_search_param.consider_duplicate and not use_custom_distance and is_result_distance_eligible<mode>(dist, inner_search_param))
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ is_result_distance_eligible<mode>  [L706] if_statement@705 (not is_finite_distance(dist) and inner_search_param.consider_duplicate and not use_custom_distance and is_result_distance_eligible<mode>(dist, inner_search_param))
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ graph->GetDuplicateIds  [L707] if_statement@705 (not is_finite_distance(dist) and inner_search_param.consider_duplicate and not use_custom_distance and is_result_distance_eligible<mode>(dist, inner_search_param)) → for_range_loop@707
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ check_func  [L708] if_statement@705 (not is_finite_distance(dist) and inner_search_param.consider_duplicate and not use_custom_distance and is_result_distance_eligible<mode>(dist, inner_search_param)) → for_range_loop@707 → if_statement@708 (check_func(duplicate_id))
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ top_candidates->Push  [L709] if_statement@705 (not is_finite_distance(dist) and inner_search_param.consider_duplicate and not use_custom_distance and is_result_distance_eligible<mode>(dist, inner_search_param)) → for_range_loop@707 → if_statement@708 (check_func(duplicate_id))
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ top_candidates->Size  [L713] if_statement@705 (not is_finite_distance(dist) and inner_search_param.consider_duplicate and not use_custom_distance and is_result_distance_eligible<mode>(dist, inner_search_param)) → if_statement@712 (mode == KNN_SEARCH) → while_statement@713 (top_candidates->Size() > ef)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ top_candidates->Pop  [L714] if_statement@705 (not is_finite_distance(dist) and inner_search_param.consider_duplicate and not use_custom_distance and is_result_distance_eligible<mode>(dist, inner_search_param)) → if_statement@712 (mode == KNN_SEARCH) → while_statement@713 (top_candidates->Size() > ef)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ top_candidates->Empty  [L719] if_statement@718 (mode == InnerSearchMode::RANGE_SEARCH) → while_statement@719 (dist > inner_search_param.radius and not top_candidates->Empty())
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ top_candidates->Pop  [L720] if_statement@718 (mode == InnerSearchMode::RANGE_SEARCH) → while_statement@719 (dist > inner_search_param.radius and not top_candidates->Empty())
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ top_candidates->Empty  [L723] if_statement@723 (not top_candidates->Empty())
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ top_candidates->Top  [L724] if_statement@723 (not top_candidates->Empty())
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ graph->GetDuplicateIds  [L727] if_statement@726 (use_custom_distance and inner_search_param.consider_duplicate)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ score_duplicates  [L728] if_statement@726 (use_custom_distance and inner_search_param.consider_duplicate)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ candidate_set->Push  [L730] 函数本体；短路求值/提前返回见源码
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ traversal_priority  [L730] 函数本体；短路求值/提前返回见源码
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ vl->Set  [L731] 函数本体；短路求值/提前返回见源码
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ candidate_set->Empty  [L733] while_statement@733 (not candidate_set->Empty())
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ reasoning->SetTermination  [L737] while_statement@733 (not candidate_set->Empty()) → if_statement@735 (hops >= inner_search_param.hops_limit) → if_statement@736 (reasoning != nullptr)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ reasoning->AddSearchHop  [L742] while_statement@733 (not candidate_set->Empty()) → if_statement@741 (reasoning != nullptr)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ candidate_set->Top  [L744] while_statement@733 (not candidate_set->Empty())
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ inner_search_param.time_cost->CheckOvertime  [L747] while_statement@733 (not candidate_set->Empty()) → if_statement@746 (inner_search_param.time_cost != nullptr and inner_search_param.time_cost->CheckOvertime())
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ ctx->stats->is_timeout.store  [L749] while_statement@733 (not candidate_set->Empty()) → if_statement@746 (inner_search_param.time_cost != nullptr and inner_search_param.time_cost->CheckOvertime()) → if_statement@748 (ctx != nullptr and ctx->stats != nullptr)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ reasoning->SetTermination  [L752] while_statement@733 (not candidate_set->Empty()) → if_statement@746 (inner_search_param.time_cost != nullptr and inner_search_param.time_cost->CheckOvertime()) → if_statement@751 (reasoning != nullptr)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ top_candidates->Size  [L758] while_statement@733 (not candidate_set->Empty()) → if_statement@757 (mode == InnerSearchMode::KNN_SEARCH) → if_statement@758 ((-current_node_pair.first) > lower_bound && top_candidates->Size() >= ef)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ reasoning->SetTermination  [L760] while_statement@733 (not candidate_set->Empty()) → if_statement@757 (mode == InnerSearchMode::KNN_SEARCH) → if_statement@758 ((-current_node_pair.first) > lower_bound && top_candidates->Size() >= ef) → if_statement@759 (reasoning != nullptr)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ candidate_set->Pop  [L765] while_statement@733 (not candidate_set->Empty())
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ candidate_set->Empty  [L767] while_statement@733 (not candidate_set->Empty()) → if_statement@767 (not candidate_set->Empty())
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ graph->Prefetch  [L768] while_statement@733 (not candidate_set->Empty()) → if_statement@767 (not candidate_set->Empty())
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ candidate_set->Top  [L768] while_statement@733 (not candidate_set->Empty()) → if_statement@767 (not candidate_set->Empty())
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ visit  [L771] while_statement@733 (not candidate_set->Empty())
  │    │    │    │  ↳ 复用节点 #51 BasicSearcher::visit（本树前文已展开）
  │    │    │    ├─ skip_strategy.get  [L775] while_statement@733 (not candidate_set->Empty())
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ score_ids  [L781] while_statement@733 (not candidate_set->Empty()) → if_statement@780 (use_custom_distance)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ to_be_visited_id.data  [L781] while_statement@733 (not candidate_set->Empty()) → if_statement@780 (use_custom_distance)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ line_dists.data  [L781] while_statement@733 (not candidate_set->Empty()) → if_statement@780 (use_custom_distance)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ top_candidates->Size  [L783] while_statement@733 (not candidate_set->Empty()) → if_statement@780 (use_custom_distance) [else 分支] → if_statement@782 (inner_search_param.enable_rabitq_one_bit_search and top_candidates->Size() == ef and rabitq_lower_bound_candidates != nullptr)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ flatten->QueryWithDistanceLowerBound  [L785] while_statement@733 (not candidate_set->Empty()) → if_statement@780 (use_custom_distance) [else 分支] → if_statement@782 (inner_search_param.enable_rabitq_one_bit_search and top_candidates->Size() == ef and rabitq_lower_bound_candidates != nullptr)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ line_dists.data  [L785] while_statement@733 (not candidate_set->Empty()) → if_statement@780 (use_custom_distance) [else 分支] → if_statement@782 (inner_search_param.enable_rabitq_one_bit_search and top_candidates->Size() == ef and rabitq_lower_bound_candidates != nullptr)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ lower_bound_dists.data  [L786] while_statement@733 (not candidate_set->Empty()) → if_statement@780 (use_custom_distance) [else 分支] → if_statement@782 (inner_search_param.enable_rabitq_one_bit_search and top_candidates->Size() == ef and rabitq_lower_bound_candidates != nullptr)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ to_be_visited_id.data  [L788] while_statement@733 (not candidate_set->Empty()) → if_statement@780 (use_custom_distance) [else 分支] → if_statement@782 (inner_search_param.enable_rabitq_one_bit_search and top_candidates->Size() == ef and rabitq_lower_bound_candidates != nullptr)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ flatten->QueryWithDistanceLowerBound  [L792] while_statement@733 (not candidate_set->Empty()) → if_statement@780 (use_custom_distance) [else 分支] → if_statement@782 (inner_search_param.enable_rabitq_one_bit_search and top_candidates->Size() == ef and rabitq_lower_bound_candidates != nullptr) [else 分支] → if_statement@791 (inner_search_param.enable_rabitq_one_bit_search)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ line_dists.data  [L792] while_statement@733 (not candidate_set->Empty()) → if_statement@780 (use_custom_distance) [else 分支] → if_statement@782 (inner_search_param.enable_rabitq_one_bit_search and top_candidates->Size() == ef and rabitq_lower_bound_candidates != nullptr) [else 分支] → if_statement@791 (inner_search_param.enable_rabitq_one_bit_search)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ to_be_visited_id.data  [L795] while_statement@733 (not candidate_set->Empty()) → if_statement@780 (use_custom_distance) [else 分支] → if_statement@782 (inner_search_param.enable_rabitq_one_bit_search and top_candidates->Size() == ef and rabitq_lower_bound_candidates != nullptr) [else 分支] → if_statement@791 (inner_search_param.enable_rabitq_one_bit_search)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ flatten->Query  [L799] while_statement@733 (not candidate_set->Empty()) → if_statement@780 (use_custom_distance) [else 分支] → if_statement@782 (inner_search_param.enable_rabitq_one_bit_search and top_candidates->Size() == ef and rabitq_lower_bound_candidates != nullptr) [else 分支] → if_statement@791 (inner_search_param.enable_rabitq_one_bit_search) [else 分支]
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ line_dists.data  [L800] while_statement@733 (not candidate_set->Empty()) → if_statement@780 (use_custom_distance) [else 分支] → if_statement@782 (inner_search_param.enable_rabitq_one_bit_search and top_candidates->Size() == ef and rabitq_lower_bound_candidates != nullptr) [else 分支] → if_statement@791 (inner_search_param.enable_rabitq_one_bit_search) [else 分支]
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ to_be_visited_id.data  [L800] while_statement@733 (not candidate_set->Empty()) → if_statement@780 (use_custom_distance) [else 分支] → if_statement@782 (inner_search_param.enable_rabitq_one_bit_search and top_candidates->Size() == ef and rabitq_lower_bound_candidates != nullptr) [else 分支] → if_statement@791 (inner_search_param.enable_rabitq_one_bit_search) [else 分支]
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ reasoning->RecordVisit  [L808] while_statement@733 (not candidate_set->Empty()) → for_statement@804 i < count_no_visited → if_statement@807 (reasoning != nullptr)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ graph->GetDuplicateIds  [L811] while_statement@733 (not candidate_set->Empty()) → for_statement@804 i < count_no_visited → if_statement@810 (use_custom_distance and inner_search_param.consider_duplicate)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ score_duplicates  [L812] while_statement@733 (not candidate_set->Empty()) → for_statement@804 i < count_no_visited → if_statement@810 (use_custom_distance and inner_search_param.consider_duplicate)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ is_finite_distance  [L814] while_statement@733 (not candidate_set->Empty()) → for_statement@804 i < count_no_visited → if_statement@814 (not is_finite_distance(dist))
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ candidate_set->Push  [L815] while_statement@733 (not candidate_set->Empty()) → for_statement@804 i < count_no_visited → if_statement@814 (not is_finite_distance(dist))
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ traversal_priority  [L815] while_statement@733 (not candidate_set->Empty()) → for_statement@804 i < count_no_visited → if_statement@814 (not is_finite_distance(dist))
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ is_result_distance_eligible<mode>  [L817] while_statement@733 (not candidate_set->Empty()) → for_statement@804 i < count_no_visited → if_statement@814 (not is_finite_distance(dist)) → lambda@816（定义体，执行时间取决于调用/调度） → if_statement@817 (not is_result_distance_eligible<mode>(dist, inner_search_param) or not check_func(result_id))
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ check_func  [L818] while_statement@733 (not candidate_set->Empty()) → for_statement@804 i < count_no_visited → if_statement@814 (not is_finite_distance(dist)) → lambda@816（定义体，执行时间取决于调用/调度） → if_statement@817 (not is_result_distance_eligible<mode>(dist, inner_search_param) or not check_func(result_id))
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ top_candidates->Push  [L821] while_statement@733 (not candidate_set->Empty()) → for_statement@804 i < count_no_visited → if_statement@814 (not is_finite_distance(dist)) → lambda@816（定义体，执行时间取决于调用/调度）
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ top_candidates->Size  [L823] while_statement@733 (not candidate_set->Empty()) → for_statement@804 i < count_no_visited → if_statement@814 (not is_finite_distance(dist)) → lambda@816（定义体，执行时间取决于调用/调度） → if_statement@822 (mode == KNN_SEARCH) → while_statement@823 (top_candidates->Size() > ef)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ reasoning->RecordEviction  [L825] while_statement@733 (not candidate_set->Empty()) → for_statement@804 i < count_no_visited → if_statement@814 (not is_finite_distance(dist)) → lambda@816（定义体，执行时间取决于调用/调度） → if_statement@822 (mode == KNN_SEARCH) → while_statement@823 (top_candidates->Size() > ef) → if_statement@824 (reasoning != nullptr)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ top_candidates->Top  [L825] while_statement@733 (not candidate_set->Empty()) → for_statement@804 i < count_no_visited → if_statement@814 (not is_finite_distance(dist)) → lambda@816（定义体，执行时间取决于调用/调度） → if_statement@822 (mode == KNN_SEARCH) → while_statement@823 (top_candidates->Size() > ef) → if_statement@824 (reasoning != nullptr)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ top_candidates->Pop  [L827] while_statement@733 (not candidate_set->Empty()) → for_statement@804 i < count_no_visited → if_statement@814 (not is_finite_distance(dist)) → lambda@816（定义体，执行时间取决于调用/调度） → if_statement@822 (mode == KNN_SEARCH) → while_statement@823 (top_candidates->Size() > ef)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ top_candidates->Pop  [L830] while_statement@733 (not candidate_set->Empty()) → for_statement@804 i < count_no_visited → if_statement@814 (not is_finite_distance(dist)) → lambda@816（定义体，执行时间取决于调用/调度） → if_statement@822 (mode == KNN_SEARCH) [else 分支] → if_statement@829 (dist > inner_search_param.radius)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ push_result  [L833] while_statement@733 (not candidate_set->Empty()) → for_statement@804 i < count_no_visited → if_statement@814 (not is_finite_distance(dist))
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ graph->GetDuplicateIds  [L835] while_statement@733 (not candidate_set->Empty()) → for_statement@804 i < count_no_visited → if_statement@814 (not is_finite_distance(dist)) → if_statement@834 (inner_search_param.consider_duplicate and not use_custom_distance) → for_range_loop@835
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ push_result  [L836] while_statement@733 (not candidate_set->Empty()) → for_statement@804 i < count_no_visited → if_statement@814 (not is_finite_distance(dist)) → if_statement@834 (inner_search_param.consider_duplicate and not use_custom_distance) → for_range_loop@835
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ top_candidates->Empty  [L839] while_statement@733 (not candidate_set->Empty()) → for_statement@804 i < count_no_visited → if_statement@814 (not is_finite_distance(dist)) → if_statement@839 (not top_candidates->Empty())
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ top_candidates->Top  [L840] while_statement@733 (not candidate_set->Empty()) → for_statement@804 i < count_no_visited → if_statement@814 (not is_finite_distance(dist)) → if_statement@839 (not top_candidates->Empty())
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ check_func  [L846] while_statement@733 (not candidate_set->Empty()) → for_statement@804 i < count_no_visited → if_statement@844 (mode == KNN_SEARCH) → if_statement@845 (collect_rabitq_lower_bound and lower_bound_dists[i] < lower_bound and check_func(cur_id))
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ rabitq_lower_bound_candidates->emplace_back  [L847] while_statement@733 (not candidate_set->Empty()) → for_statement@804 i < count_no_visited → if_statement@844 (mode == KNN_SEARCH) → if_statement@845 (collect_rabitq_lower_bound and lower_bound_dists[i] < lower_bound and check_func(cur_id))
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ top_candidates->Size  [L850] while_statement@733 (not candidate_set->Empty()) → for_statement@804 i < count_no_visited → if_statement@850 (top_candidates->Size() < ef || lower_bound > dist || (mode == RANGE_SEARCH && dist <= inner_search_param.radius))
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ candidate_set->Push  [L852] while_statement@733 (not candidate_set->Empty()) → for_statement@804 i < count_no_visited → if_statement@850 (top_candidates->Size() < ef || lower_bound > dist || (mode == RANGE_SEARCH && dist <= inner_search_param.radius))
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ check_func  [L854] while_statement@733 (not candidate_set->Empty()) → for_statement@804 i < count_no_visited → if_statement@850 (top_candidates->Size() < ef || lower_bound > dist || (mode == RANGE_SEARCH && dist <= inner_search_param.radius)) → if_statement@854 (check_func(cur_id))
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ top_candidates->Push  [L855] while_statement@733 (not candidate_set->Empty()) → for_statement@804 i < count_no_visited → if_statement@850 (top_candidates->Size() < ef || lower_bound > dist || (mode == RANGE_SEARCH && dist <= inner_search_param.radius)) → if_statement@854 (check_func(cur_id))
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ reasoning->RecordFilterReject  [L857] while_statement@733 (not candidate_set->Empty()) → for_statement@804 i < count_no_visited → if_statement@850 (top_candidates->Size() < ef || lower_bound > dist || (mode == RANGE_SEARCH && dist <= inner_search_param.radius)) → if_statement@854 (check_func(cur_id)) [else 分支] → if_statement@856 (reasoning != nullptr)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ graph->GetDuplicateIds  [L860] while_statement@733 (not candidate_set->Empty()) → for_statement@804 i < count_no_visited → if_statement@850 (top_candidates->Size() < ef || lower_bound > dist || (mode == RANGE_SEARCH && dist <= inner_search_param.radius)) → if_statement@859 (inner_search_param.consider_duplicate and not use_custom_distance)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ check_func  [L862] while_statement@733 (not candidate_set->Empty()) → for_statement@804 i < count_no_visited → if_statement@850 (top_candidates->Size() < ef || lower_bound > dist || (mode == RANGE_SEARCH && dist <= inner_search_param.radius)) → if_statement@859 (inner_search_param.consider_duplicate and not use_custom_distance) → for_range_loop@861 → if_statement@862 (check_func(item))
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ top_candidates->Push  [L863] while_statement@733 (not candidate_set->Empty()) → for_statement@804 i < count_no_visited → if_statement@850 (top_candidates->Size() < ef || lower_bound > dist || (mode == RANGE_SEARCH && dist <= inner_search_param.radius)) → if_statement@859 (inner_search_param.consider_duplicate and not use_custom_distance) → for_range_loop@861 → if_statement@862 (check_func(item))
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ top_candidates->Size  [L869] while_statement@733 (not candidate_set->Empty()) → for_statement@804 i < count_no_visited → if_statement@850 (top_candidates->Size() < ef || lower_bound > dist || (mode == RANGE_SEARCH && dist <= inner_search_param.radius)) → if_statement@868 (mode == KNN_SEARCH) → if_statement@869 (top_candidates->Size() > ef)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ reasoning->RecordEviction  [L871] while_statement@733 (not candidate_set->Empty()) → for_statement@804 i < count_no_visited → if_statement@850 (top_candidates->Size() < ef || lower_bound > dist || (mode == RANGE_SEARCH && dist <= inner_search_param.radius)) → if_statement@868 (mode == KNN_SEARCH) → if_statement@869 (top_candidates->Size() > ef) → if_statement@870 (reasoning != nullptr)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ top_candidates->Top  [L871] while_statement@733 (not candidate_set->Empty()) → for_statement@804 i < count_no_visited → if_statement@850 (top_candidates->Size() < ef || lower_bound > dist || (mode == RANGE_SEARCH && dist <= inner_search_param.radius)) → if_statement@868 (mode == KNN_SEARCH) → if_statement@869 (top_candidates->Size() > ef) → if_statement@870 (reasoning != nullptr)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ top_candidates->Pop  [L873] while_statement@733 (not candidate_set->Empty()) → for_statement@804 i < count_no_visited → if_statement@850 (top_candidates->Size() < ef || lower_bound > dist || (mode == RANGE_SEARCH && dist <= inner_search_param.radius)) → if_statement@868 (mode == KNN_SEARCH) → if_statement@869 (top_candidates->Size() > ef)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ top_candidates->Empty  [L877] while_statement@733 (not candidate_set->Empty()) → for_statement@804 i < count_no_visited → if_statement@850 (top_candidates->Size() < ef || lower_bound > dist || (mode == RANGE_SEARCH && dist <= inner_search_param.radius)) → if_statement@877 (not top_candidates->Empty())
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ top_candidates->Top  [L878] while_statement@733 (not candidate_set->Empty()) → for_statement@804 i < count_no_visited → if_statement@850 (top_candidates->Size() < ef || lower_bound > dist || (mode == RANGE_SEARCH && dist <= inner_search_param.radius)) → if_statement@877 (not top_candidates->Empty())
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ top_candidates->Size  [L885] if_statement@884 (mode == KNN_SEARCH) → while_statement@885 (top_candidates->Size() > inner_search_param.topk)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ top_candidates->Pop  [L886] if_statement@884 (mode == KNN_SEARCH) → while_statement@885 (top_candidates->Size() > inner_search_param.topk)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ top_candidates->Size  [L890] if_statement@884 (mode == KNN_SEARCH) [else 分支] → if_statement@888 (mode == RANGE_SEARCH) → if_statement@889 (inner_search_param.range_search_limit_size > 0) → while_statement@890 (top_candidates->Size() > inner_search_param.range_search_limit_size)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ top_candidates->Pop  [L891] if_statement@884 (mode == KNN_SEARCH) [else 分支] → if_statement@888 (mode == RANGE_SEARCH) → if_statement@889 (inner_search_param.range_search_limit_size > 0) → while_statement@890 (top_candidates->Size() > inner_search_param.range_search_limit_size)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ top_candidates->Empty  [L894] if_statement@884 (mode == KNN_SEARCH) [else 分支] → if_statement@888 (mode == RANGE_SEARCH) → while_statement@894 (not top_candidates->Empty() && top_candidates->Top().first > inner_search_param.radius + THRESHOLD_ERROR)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ top_candidates->Top  [L895] if_statement@884 (mode == KNN_SEARCH) [else 分支] → if_statement@888 (mode == RANGE_SEARCH) → while_statement@894 (not top_candidates->Empty() && top_candidates->Top().first > inner_search_param.radius + THRESHOLD_ERROR)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ top_candidates->Pop  [L896] if_statement@884 (mode == KNN_SEARCH) [else 分支] → if_statement@888 (mode == RANGE_SEARCH) → while_statement@894 (not top_candidates->Empty() && top_candidates->Top().first > inner_search_param.radius + THRESHOLD_ERROR)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ top_candidates->Empty  [L902] if_statement@901 (not use_custom_distance and inner_search_param.find_duplicate and not top_candidates->Empty())
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ top_candidates->GetData  [L903] if_statement@901 (not use_custom_distance and inner_search_param.find_duplicate and not top_candidates->Empty())
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ top_candidates->Size  [L906] if_statement@901 (not use_custom_distance and inner_search_param.find_duplicate and not top_candidates->Empty()) → for_statement@906 i < top_candidates->Size()
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ flatten->TotalCount  [L918] if_statement@901 (not use_custom_distance and inner_search_param.find_duplicate and not top_candidates->Empty()) → if_statement@912 (inner_search_param.duplicate_distance_threshold > 0.0F) [else 分支]
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ flatten->CompareVectors  [L921] if_statement@901 (not use_custom_distance and inner_search_param.find_duplicate and not top_candidates->Empty()) → if_statement@912 (inner_search_param.duplicate_distance_threshold > 0.0F) [else 分支] → conditional_expression@920 has_stored_query
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ flatten->CompareRawVectorWithId  [L922] if_statement@901 (not use_custom_distance and inner_search_param.find_duplicate and not top_candidates->Empty()) → if_statement@912 (inner_search_param.duplicate_distance_threshold > 0.0F) [else 分支] → conditional_expression@920 has_stored_query
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ stats.dist_cmp.fetch_add  [L931] if_statement@929 (ctx != nullptr and ctx->stats != nullptr)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ stats.hops.fetch_add  [L932] if_statement@929 (ctx != nullptr and ctx->stats != nullptr)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ this->search_impl<RANGE_SEARCH>  [L96] 函数本体；短路求值/提前返回见源码
  │    │    │  ├─ 以下为分派/重载候选，并非全部依次执行
  │    │    │  ↳ 复用节点 #50 BasicSearcher::search_impl（本树前文已展开）
  │    │    │  ↳ 复用节点 #52 BasicSearcher::search_impl（本树前文已展开）
  │    │    │  ↳ 复用节点 #53 BasicSearcher::search_impl（本树前文已展开）
  │    │  #54 BasicSearcher::Search [src/impl/searcher/basic_searcher.cpp:139]
  │    │    ├─ this->search_impl<KNN_SEARCH>  [L148] 函数本体；短路求值/提前返回见源码
  │    │    │  ├─ 以下为分派/重载候选，并非全部依次执行
  │    │    │  ↳ 复用节点 #50 BasicSearcher::search_impl（本树前文已展开）
  │    │    │  ↳ 复用节点 #52 BasicSearcher::search_impl（本树前文已展开）
  │    │    │  ↳ 复用节点 #53 BasicSearcher::search_impl（本树前文已展开）
  │    │  #55 BasicSearcher::Search [src/impl/searcher/basic_searcher.cpp:158]
  │    │    ├─ this->search_impl<InnerSearchMode::RANGE_SEARCH>  [L166] if_statement@165 (inner_search_param.search_mode == InnerSearchMode::RANGE_SEARCH)
  │    │    │  ├─ 以下为分派/重载候选，并非全部依次执行
  │    │    │  ↳ 复用节点 #50 BasicSearcher::search_impl（本树前文已展开）
  │    │    │  ↳ 复用节点 #52 BasicSearcher::search_impl（本树前文已展开）
  │    │    │  ↳ 复用节点 #53 BasicSearcher::search_impl（本树前文已展开）
  │    │    ├─ this->search_impl<InnerSearchMode::KNN_SEARCH>  [L169] 函数本体；短路求值/提前返回见源码
  │    │    │  ├─ 以下为分派/重载候选，并非全部依次执行
  │    │    │  ↳ 复用节点 #50 BasicSearcher::search_impl（本树前文已展开）
  │    │    │  ↳ 复用节点 #52 BasicSearcher::search_impl（本树前文已展开）
  │    │    │  ↳ 复用节点 #53 BasicSearcher::search_impl（本树前文已展开）
  │    ├─ mutually_connect_new_element  [L383] lambda@338（定义体，执行时间取决于调用/调度） → for_statement@373 node_pos < valid_ids.size()
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ std::move  [L387] lambda@338（定义体，执行时间取决于调用/调度）
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ futures.reserve  [L392] if_statement@390 (this->thread_pool_ != nullptr)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ futures.emplace_back  [L394] if_statement@390 (this->thread_pool_ != nullptr) → for_statement@393 b < bucket_count
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ this->thread_pool_->GeneralEnqueue  [L394] if_statement@390 (this->thread_pool_ != nullptr) → for_statement@393 b < bucket_count
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ future.get  [L397] if_statement@390 (this->thread_pool_ != nullptr) → for_range_loop@396
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ build_one_bucket  [L401] if_statement@390 (this->thread_pool_ != nullptr) [else 分支] → for_statement@400 b < bucket_count
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ this->cal_memory_usage  [L116] 函数本体；短路求值/提前返回见源码
  │  ↳ 复用节点 #41 IVF::cal_memory_usage（本树前文已展开）
```

## IVF::Train

[完整函数与全部调用点](function_reference/ivf_build.md#L120)

```text
#1 IVF::Train [src/algorithm/ivf/ivf_build.cpp:120]
  ├─ data->GetNumElements  [L126] 函数本体；短路求值/提前返回见源码
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ data->GetDim  [L127] 函数本体；短路求值/提前返回见源码
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ vsag::sample_train_data  [L129] 函数本体；短路求值/提前返回见源码
  │  #2 sample_train_data [src/utils/util_functions.cpp:234]
  │    ├─ std::min  [L243] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ std::max  [L243] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ vsag::SafeAllocator::FactoryDefaultAllocator  [L256] if_statement@253 (allocator != nullptr) [else 分支]
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ owned_allocator.get  [L257] if_statement@253 (allocator != nullptr) [else 分支]
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ sampled_indices.reserve  [L263] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ std::min  [L265] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ sampled_indices.resize  [L266] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ std::iota  [L267] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ sampled_indices.begin  [L267] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ sampled_indices.end  [L267] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ random_seed.has_value  [L269] conditional_expression@269 random_seed.has_value()
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ rd  [L269] conditional_expression@269 random_seed.has_value()
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ dist  [L272] for_statement@270 i < total_elements
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ sampled_data_buffer.resize  [L277] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ data->GetFloat32Vectors  [L278] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ std::copy  [L280] for_statement@279 i < sample_count
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ sampled_data_buffer.data  [L282] for_statement@279 i < sample_count
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ safe_allocator->Allocate  [L285] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ std::copy  [L286] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ sampled_data_buffer.begin  [L286] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ sampled_data_buffer.end  [L286] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ std::make_shared<DatasetImpl>  [L288] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ sampled_dataset->NumElements(sample_count) ->Dim(dim) ->Float32Vectors(new_data_buffer) ->Owner  [L289] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ sampled_dataset->NumElements(sample_count) ->Dim(dim) ->Float32Vectors  [L289] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ sampled_dataset->NumElements(sample_count) ->Dim  [L289] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ sampled_dataset->NumElements  [L289] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ data->GetIds  [L293] if_statement@293 (data->GetIds() != nullptr)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ sampled_ids.reserve  [L294] if_statement@293 (data->GetIds() != nullptr)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ data->GetIds  [L295] if_statement@293 (data->GetIds() != nullptr)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ sampled_ids.push_back  [L297] if_statement@293 (data->GetIds() != nullptr) → for_statement@296 i < sample_count
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ safe_allocator->Allocate  [L301] if_statement@293 (data->GetIds() != nullptr)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ std::copy  [L302] if_statement@293 (data->GetIds() != nullptr)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ sampled_ids.begin  [L302] if_statement@293 (data->GetIds() != nullptr)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ sampled_ids.end  [L302] if_statement@293 (data->GetIds() != nullptr)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ sampled_dataset->Ids(new_ids_buffer)->Owner  [L304] if_statement@293 (data->GetIds() != nullptr)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ sampled_dataset->Ids  [L304] if_statement@293 (data->GetIds() != nullptr)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ train_data->GetNumElements  [L130] 函数本体；短路求值/提前返回见源码
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ partition_strategy_->Train  [L132] 函数本体；短路求值/提前返回见源码
  │  ├─ 以下为分派/重载候选，并非全部依次执行
  │  #3 GNOIMIPartition::Train [src/algorithm/ivf/gno_imi_partition.cpp:88]
  │    ├─ Dataset::Make  [L91] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ Dataset::Make  [L92] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ dataset->GetFloat32Vectors  [L93] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ dataset->GetNumElements  [L94] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ norm_vectors.resize  [L97] if_statement@96 (metric_type_ == MetricType::METRIC_TYPE_COSINE)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ Normalize  [L99] if_statement@96 (metric_type_ == MetricType::METRIC_TYPE_COSINE) → for_statement@98 i < num_element
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ norm_vectors.data  [L99] if_statement@96 (metric_type_ == MetricType::METRIC_TYPE_COSINE) → for_statement@98 i < num_element
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ norm_vectors.data  [L101] if_statement@96 (metric_type_ == MetricType::METRIC_TYPE_COSINE)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ std::iota  [L109] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ ids_centroids_s.begin  [L109] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ ids_centroids_s.end  [L109] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ std::iota  [L110] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ ids_centroids_t.begin  [L110] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ ids_centroids_t.end  [L110] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ centroids_s->Ids(ids_centroids_s.data()) ->Dim(dim) ->Float32Vectors(data_centroids_s_tmp.data()) ->NumElements(this->bucket_count_s_) ->Owner  [L111] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ centroids_s->Ids(ids_centroids_s.data()) ->Dim(dim) ->Float32Vectors(data_centroids_s_tmp.data()) ->NumElements  [L111] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ centroids_s->Ids(ids_centroids_s.data()) ->Dim(dim) ->Float32Vectors  [L111] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ centroids_s->Ids(ids_centroids_s.data()) ->Dim  [L111] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ centroids_s->Ids  [L111] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ ids_centroids_s.data  [L111] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ data_centroids_s_tmp.data  [L113] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ centroids_t->Ids(ids_centroids_t.data()) ->Dim(dim) ->Float32Vectors(data_centroids_t_tmp.data()) ->NumElements(this->bucket_count_t_) ->Owner  [L116] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ centroids_t->Ids(ids_centroids_t.data()) ->Dim(dim) ->Float32Vectors(data_centroids_t_tmp.data()) ->NumElements  [L116] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ centroids_t->Ids(ids_centroids_t.data()) ->Dim(dim) ->Float32Vectors  [L116] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ centroids_t->Ids(ids_centroids_t.data()) ->Dim  [L116] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ centroids_t->Ids  [L116] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ ids_centroids_t.data  [L116] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ data_centroids_t_tmp.data  [L118] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ cls.Run  [L128] lambda@125（定义体，执行时间取决于调用/调度）
  │    │  #4 KMeansCluster::Run [src/impl/cluster/kmeans_cluster.cpp:48]
  │    │    ├─ VsagException  [L60] if_statement@59 (k == 0)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ VsagException  [L63] if_statement@62 (count == 0)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ VsagException  [L66] if_statement@65 (datas == nullptr)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ VsagException  [L69] if_statement@68 (k > count)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ allocator_->Deallocate  [L73] if_statement@72 (k_centroids_ != nullptr)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ allocator_->Allocate  [L77] 函数本体；短路求值/提前返回见源码
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ random_seed.has_value  [L80] conditional_expression@80 random_seed.has_value()
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ rd  [L80] conditional_expression@80 random_seed.has_value()
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ select_initial_centroids_kmeans_plus_plus  [L83] if_statement@82 (init_method == KMeansInitMethod::KMEANS_PLUS_PLUS)
  │    │    │  #5 KMeansCluster::select_initial_centroids_kmeans_plus_plus [src/impl/cluster/kmeans_cluster.cpp:305]
  │    │    │    ├─ first_dis  [L311] 函数本体；短路求值/提前返回见源码
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ FP32ComputeL2Sqr  [L323] for_statement@318 c < k → for_statement@322 i < count
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ std::min  [L324] for_statement@318 c < k → for_statement@322 i < count
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ dis  [L334] for_statement@318 c < k → if_statement@332 (total_weight <= 0.0)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ prob_dis  [L342] for_statement@318 c < k
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ select_initial_centroids_random  [L85] if_statement@82 (init_method == KMeansInitMethod::KMEANS_PLUS_PLUS) [else 分支]
  │    │    │  #6 KMeansCluster::select_initial_centroids_random [src/impl/cluster/kmeans_cluster.cpp:290]
  │    │    │    ├─ dis  [L298] for_statement@297 i < k
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ std::numeric_limits<double>::max  [L88] 函数本体；短路求值/提前返回见源码
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ std::numeric_limits<double>::max  [L89] 函数本体；短路求值/提前返回见源码
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ logger::trace  [L93] 函数本体；短路求值/提前返回见源码
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ logger::trace  [L95] if_statement@94 (k < THRESHOLD_FOR_HGRAPH)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ logger::trace  [L97] if_statement@94 (k < THRESHOLD_FOR_HGRAPH) [else 分支]
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ NearestCentroidAssign  [L102] for_statement@100 it < iter → if_statement@101 (k < THRESHOLD_FOR_HGRAPH)
  │    │    │  #7 NearestCentroidAssign [src/impl/cluster/nearest_centroid_assign.cpp:39]
  │    │    │    ├─ std::numeric_limits<int32_t>::max  [L52] if_statement@50 (centroids == nullptr || queries == nullptr || labels == nullptr || allocator == nullptr || thread_pool == nullptr || centroid_count == 0 || query_count == 0 || dim == 0 || centroid_count > static_cast<uint64_t>(std::numeric_limits<int32_t>::max()) || dim > static_cast<uint64_t>(std::numeric_limits<int32_t>::max()))
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ std::numeric_limits<int32_t>::max  [L53] if_statement@50 (centroids == nullptr || queries == nullptr || labels == nullptr || allocator == nullptr || thread_pool == nullptr || centroid_count == 0 || query_count == 0 || dim == 0 || centroid_count > static_cast<uint64_t>(std::numeric_limits<int32_t>::max()) || dim > static_cast<uint64_t>(std::numeric_limits<int32_t>::max()))
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ VsagException  [L54] if_statement@50 (centroids == nullptr || queries == nullptr || labels == nullptr || allocator == nullptr || thread_pool == nullptr || centroid_count == 0 || query_count == 0 || dim == 0 || centroid_count > static_cast<uint64_t>(std::numeric_limits<int32_t>::max()) || dim > static_cast<uint64_t>(std::numeric_limits<int32_t>::max()))
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ future.wait  [L63] lambda@61（定义体，执行时间取决于调用/调度） → for_range_loop@62
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ futures.clear  [L65] lambda@61（定义体，执行时间取决于调用/调度）
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ std::min  [L68] 函数本体；短路求值/提前返回见源码
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ FP32ComputeIP  [L76] lambda@74（定义体，执行时间取决于调用/调度） → for_statement@75 i < end
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ futures.emplace_back  [L80] for_statement@79 i < centroid_count
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ thread_pool_ref->GeneralEnqueue  [L81] for_statement@79 i < centroid_count
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ std::min  [L81] for_statement@79 i < centroid_count
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ wait_futures_and_clear  [L83] 函数本体；短路求值/提前返回见源码
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ std::min  [L86] for_statement@85 i < query_count
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ SimdStatus::SupportAMXBF16  [L108] for_statement@85 i < query_count → if_statement@107 (dim >= amx_bf16_min_dim && centroid_count >= amx_bf16_min_m && cur_query_count >= amx_bf16_min_n && SimdStatus::SupportAMXBF16())
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ amx::SgemmBF16IPColMajorOut  [L109] for_statement@85 i < query_count → if_statement@107 (dim >= amx_bf16_min_dim && centroid_count >= amx_bf16_min_m && cur_query_count >= amx_bf16_min_n && SimdStatus::SupportAMXBF16())
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ BlasFunction::Sgemm  [L119] for_statement@85 i < query_count → if_statement@118 (!used_amx)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ omp_set_num_threads  [L137] for_statement@85 i < query_count → lambda@136（定义体，执行时间取决于调用/调度）
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ BlasFunction::Saxpy  [L140] for_statement@85 i < query_count → lambda@136（定义体，执行时间取决于调用/调度） → for_statement@139 j < end
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ std::min_element  [L146] for_statement@85 i < query_count → lambda@136（定义体，执行时间取决于调用/调度） → for_statement@139 j < end
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ FP32ComputeIP  [L148] for_statement@85 i < query_count → lambda@136（定义体，执行时间取决于调用/调度） → for_statement@139 j < end
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ std::distance  [L150] for_statement@85 i < query_count → lambda@136（定义体，执行时间取决于调用/调度） → for_statement@139 j < end
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ futures.emplace_back  [L162] for_statement@85 i < query_count → for_statement@161 j < cur_query_count
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ thread_pool_ref->GeneralEnqueue  [L162] for_statement@85 i < query_count → for_statement@161 j < cur_query_count
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ std::min  [L163] for_statement@85 i < query_count → for_statement@161 j < cur_query_count
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ wait_futures_and_clear  [L165] for_statement@85 i < query_count
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ labels.data  [L109] for_statement@100 it < iter → if_statement@101 (k < THRESHOLD_FOR_HGRAPH)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ this->find_nearest_one_with_hgraph  [L111] for_statement@100 it < iter → if_statement@101 (k < THRESHOLD_FOR_HGRAPH) [else 分支]
  │    │    │  #8 KMeansCluster::find_nearest_one_with_hgraph [src/impl/cluster/kmeans_cluster.cpp:230]
  │    │    │    ├─ VsagException  [L236] if_statement@235 (k_centroids_ == nullptr)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ std::make_shared<SafeAllocator>  [L243] 函数本体；短路求值/提前返回见源码
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ std::max  [L246] 函数本体；短路求值/提前返回见源码
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ InnerIndexInterface::FastCreateIndex  [L249] 函数本体；短路求值/提前返回见源码
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ fmt::format  [L249] 函数本体；短路求值/提前返回见源码
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ Dataset::Make  [L250] 函数本体；短路求值/提前返回见源码
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ std::iota  [L252] 函数本体；短路求值/提前返回见源码
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ ids.begin  [L252] 函数本体；短路求值/提前返回见源码
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ ids.end  [L252] 函数本体；短路求值/提前返回见源码
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ base->Dim(dim_) ->NumElements(static_cast<int64_t>(k)) ->Float32Vectors(this->k_centroids_) ->Ids(ids.data()) ->Owner  [L253] 函数本体；短路求值/提前返回见源码
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ base->Dim(dim_) ->NumElements(static_cast<int64_t>(k)) ->Float32Vectors(this->k_centroids_) ->Ids  [L253] 函数本体；短路求值/提前返回见源码
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ base->Dim(dim_) ->NumElements(static_cast<int64_t>(k)) ->Float32Vectors  [L253] 函数本体；短路求值/提前返回见源码
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ base->Dim(dim_) ->NumElements  [L253] 函数本体；短路求值/提前返回见源码
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ base->Dim  [L253] 函数本体；短路求值/提前返回见源码
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ ids.data  [L256] 函数本体；短路求值/提前返回见源码
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ hgraph->Build  [L258] 函数本体；短路求值/提前返回见源码
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ hgraph->SetImmutable  [L259] 函数本体；短路求值/提前返回见源码
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ Dataset::Make  [L265] lambda@262（定义体，执行时间取决于调用/调度） → for_statement@264 j < end
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ q->Owner(false) ->Float32Vectors(query + j * this->dim_) ->NumElements(1) ->Dim  [L266] lambda@262（定义体，执行时间取决于调用/调度） → for_statement@264 j < end
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ q->Owner(false) ->Float32Vectors(query + j * this->dim_) ->NumElements  [L266] lambda@262（定义体，执行时间取决于调用/调度） → for_statement@264 j < end
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ q->Owner(false) ->Float32Vectors  [L266] lambda@262（定义体，执行时间取决于调用/调度） → for_statement@264 j < end
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ q->Owner  [L266] lambda@262（定义体，执行时间取决于调用/调度） → for_statement@264 j < end
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ hgraph->KnnSearch  [L270] lambda@262（定义体，执行时间取决于调用/调度） → for_statement@264 j < end
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ ret->GetIds  [L271] lambda@262（定义体，执行时间取决于调用/调度） → for_statement@264 j < end
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ ret->GetDistances  [L272] lambda@262（定义体，执行时间取决于调用/调度） → for_statement@264 j < end
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ futures.emplace_back  [L281] for_statement@280 i < query_count
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ thread_pool_->GeneralEnqueue  [L282] for_statement@280 i < query_count
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ std::min  [L282] for_statement@280 i < query_count
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ future.wait  [L285] for_range_loop@284
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ block_counts.resize  [L122] for_statement@100 it < iter → if_statement@121 (deterministic_reduction)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ block_centroids.resize  [L123] for_statement@100 it < iter → if_statement@121 (deterministic_reduction)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ omp_set_num_threads  [L128] for_statement@100 it < iter → lambda@127（定义体，执行时间取决于调用/调度）
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ BlasFunction::Saxpy  [L136] for_statement@100 it < iter → lambda@127（定义体，执行时间取决于调用/调度） → for_statement@132 i < end → if_statement@134 (label >= 0 && label < static_cast<int32_t>(k))
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ local_centroids.data  [L141] for_statement@100 it < iter → lambda@127（定义体，执行时间取决于调用/调度） → for_statement@132 i < end → if_statement@134 (label >= 0 && label < static_cast<int32_t>(k))
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ std::copy  [L147] for_statement@100 it < iter → lambda@127（定义体，执行时间取决于调用/调度） → if_statement@146 (deterministic_reduction)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ local_counts.begin  [L148] for_statement@100 it < iter → lambda@127（定义体，执行时间取决于调用/调度） → if_statement@146 (deterministic_reduction)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ local_counts.end  [L148] for_statement@100 it < iter → lambda@127（定义体，执行时间取决于调用/调度） → if_statement@146 (deterministic_reduction)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ block_counts.data  [L148] for_statement@100 it < iter → lambda@127（定义体，执行时间取决于调用/调度） → if_statement@146 (deterministic_reduction)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ std::copy  [L149] for_statement@100 it < iter → lambda@127（定义体，执行时间取决于调用/调度） → if_statement@146 (deterministic_reduction)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ local_centroids.begin  [L149] for_statement@100 it < iter → lambda@127（定义体，执行时间取决于调用/调度） → if_statement@146 (deterministic_reduction)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ local_centroids.end  [L150] for_statement@100 it < iter → lambda@127（定义体，执行时间取决于调用/调度） → if_statement@146 (deterministic_reduction)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ block_centroids.data  [L151] for_statement@100 it < iter → lambda@127（定义体，执行时间取决于调用/调度） → if_statement@146 (deterministic_reduction)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ BlasFunction::Saxpy  [L157] for_statement@100 it < iter → lambda@127（定义体，执行时间取决于调用/调度） → if_statement@146 (deterministic_reduction) [else 分支] → for_statement@154 j < k → if_statement@155 (local_counts[j] > 0)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ local_centroids.data  [L160] for_statement@100 it < iter → lambda@127（定义体，执行时间取决于调用/调度） → if_statement@146 (deterministic_reduction) [else 分支] → for_statement@154 j < k → if_statement@155 (local_counts[j] > 0)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ new_centroids.data  [L162] for_statement@100 it < iter → lambda@127（定义体，执行时间取决于调用/调度） → if_statement@146 (deterministic_reduction) [else 分支] → for_statement@154 j < k → if_statement@155 (local_counts[j] > 0)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ futures.emplace_back  [L169] for_statement@100 it < iter → for_statement@168 i < count
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ thread_pool_->GeneralEnqueue  [L169] for_statement@100 it < iter → for_statement@168 i < count
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ std::min  [L170] for_statement@100 it < iter → for_statement@168 i < count
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ future.wait  [L173] for_statement@100 it < iter → for_range_loop@172
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ futures.clear  [L175] for_statement@100 it < iter
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ BlasFunction::Saxpy  [L182] for_statement@100 it < iter → if_statement@176 (deterministic_reduction) → for_statement@177 block_id < block_count → for_statement@178 j < k → if_statement@180 (block_counts[count_offset] > 0)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ block_centroids.data  [L184] for_statement@100 it < iter → if_statement@176 (deterministic_reduction) → for_statement@177 block_id < block_count → for_statement@178 j < k → if_statement@180 (block_counts[count_offset] > 0)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ new_centroids.data  [L187] for_statement@100 it < iter → if_statement@176 (deterministic_reduction) → for_statement@177 block_id < block_count → for_statement@178 j < k → if_statement@180 (block_counts[count_offset] > 0)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ BlasFunction::Sscal  [L197] for_statement@100 it < iter → for_statement@195 j < k → if_statement@196 (counts[j] > 0)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ new_centroids.data  [L199] for_statement@100 it < iter → for_statement@195 j < k → if_statement@196 (counts[j] > 0)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ std::copy  [L201] for_statement@100 it < iter → for_statement@195 j < k → if_statement@196 (counts[j] > 0)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ new_centroids.data  [L201] for_statement@100 it < iter → for_statement@195 j < k → if_statement@196 (counts[j] > 0)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ new_centroids.data  [L202] for_statement@100 it < iter → for_statement@195 j < k → if_statement@196 (counts[j] > 0)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ dis  [L205] for_statement@100 it < iter → for_statement@195 j < k → if_statement@196 (counts[j] > 0) [else 分支]
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ logger::trace  [L212] for_statement@100 it < iter
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ get_current_time  [L213] for_statement@100 it < iter
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ std::fabs  [L218] for_statement@100 it < iter → if_statement@217 (it > 0 && use_mse_for_convergence && std::fabs(last_err - total_err) / static_cast<double>(count) < threshold)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ centroids->GetNumElements  [L128] lambda@125（定义体，执行时间取决于调用/调度）
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ residuals.data  [L128] lambda@125（定义体，执行时间取决于调用/调度）
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ memcpy  [L129] lambda@125（定义体，执行时间取决于调用/调度）
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ centroids->GetNumElements  [L129] lambda@125（定义体，执行时间取决于调用/调度）
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ route_index.Build  [L131] lambda@125（定义体，执行时间取决于调用/调度）
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ this->inner_classify_datas  [L132] lambda@125（定义体，执行时间取决于调用/调度）
  │    │  #9 GNOIMIPartition::inner_classify_datas [src/algorithm/ivf/gno_imi_partition.cpp:346]
  │    │    ├─ Dataset::Make  [L351] for_statement@350 i < count
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ query->Dim(this->dim_) ->Float32Vectors(datas + i * this->dim_) ->NumElements(1) ->Owner  [L352] for_statement@350 i < count
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ query->Dim(this->dim_) ->Float32Vectors(datas + i * this->dim_) ->NumElements  [L352] for_statement@350 i < count
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ query->Dim(this->dim_) ->Float32Vectors  [L352] for_statement@350 i < count
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ query->Dim  [L352] for_statement@350 i < count
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ route_index.KnnSearch  [L357] for_statement@350 i < count
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ search_result->GetIds  [L358] for_statement@350 i < count
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ residuals.data  [L132] lambda@125（定义体，执行时间取决于调用/调度）
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ this->GetResidual  [L133] lambda@125（定义体，执行时间取决于调用/调度）
  │    │  #10 IVFPartitionStrategy::GetResidual [src/algorithm/ivf/ivf_partition_strategy.cpp:22]
  │    │    ├─ memcpy  [L26] 函数本体；短路求值/提前返回见源码
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ BlasFunction::Saxpy  [L29] for_statement@27 i < n
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ residuals.data  [L133] lambda@125（定义体，执行时间取决于调用/调度）
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ assign.data  [L133] lambda@125（定义体，执行时间取决于调用/调度）
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ std::numeric_limits<double>::max  [L137] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ train_and_get_residual  [L141] for_statement@138 i < 2
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ data_centroids_s_tmp.data  [L141] for_statement@138 i < 2
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ logger::info  [L142] for_statement@138 i < 2
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ train_and_get_residual  [L144] for_statement@138 i < 2
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ data_centroids_t_tmp.data  [L144] for_statement@138 i < 2
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ logger::info  [L145] for_statement@138 i < 2
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ std::copy  [L149] for_statement@138 i < 2 → if_statement@147 (err_to_t < min_err)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ data_centroids_s_tmp.begin  [L149] for_statement@138 i < 2 → if_statement@147 (err_to_t < min_err)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ data_centroids_s_tmp.end  [L150] for_statement@138 i < 2 → if_statement@147 (err_to_t < min_err)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ data_centroids_s_.begin  [L151] for_statement@138 i < 2 → if_statement@147 (err_to_t < min_err)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ std::copy  [L152] for_statement@138 i < 2 → if_statement@147 (err_to_t < min_err)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ data_centroids_t_tmp.begin  [L152] for_statement@138 i < 2 → if_statement@147 (err_to_t < min_err)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ data_centroids_t_tmp.end  [L153] for_statement@138 i < 2 → if_statement@147 (err_to_t < min_err)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ data_centroids_t_.begin  [L154] for_statement@138 i < 2 → if_statement@147 (err_to_t < min_err)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ FP32ComputeIP  [L159] for_statement@158 i < bucket_count_s_
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ data_centroids_s_.data  [L160] for_statement@158 i < bucket_count_s_
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ data_centroids_s_.data  [L160] for_statement@158 i < bucket_count_s_
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ FP32ComputeIP  [L166] for_statement@165 i < bucket_count_t_
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ data_centroids_t_.data  [L167] for_statement@165 i < bucket_count_t_
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ data_centroids_t_.data  [L167] for_statement@165 i < bucket_count_t_
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ std::sort  [L173] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ norms_t.begin  [L173] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ norms_t.end  [L173] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ std::greater<>  [L173] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ std::copy  [L179] for_statement@175 i < bucket_count_t_
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ data_centroids_t_.data  [L179] for_statement@175 i < bucket_count_t_
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ data_centroids_t_.data  [L180] for_statement@175 i < bucket_count_t_
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ temp_data.data  [L181] for_statement@175 i < bucket_count_t_
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ std::copy  [L184] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ temp_data.begin  [L184] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ temp_data.end  [L184] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ data_centroids_t_.data  [L184] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ matmul  [L187] 函数本体；短路求值/提前返回见源码
  │    │  #11 matmul [src/algorithm/ivf/gno_imi_partition.cpp:40]
  │    │    ├─ BlasFunction::Sgemm  [L42] 函数本体；短路求值/提前返回见源码
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ data_centroids_s_.data  [L187] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ data_centroids_t_.data  [L188] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ ip_st.data  [L189] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │  #12 IVFNearestPartition::Train [src/algorithm/ivf/ivf_nearest_partition.cpp:91]
  │    ├─ Dataset::Make  [L94] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ std::iota  [L97] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ ids.begin  [L97] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ ids.end  [L97] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ centroids->Ids(ids.data()) ->Dim(dim) ->Float32Vectors(data.data()) ->NumElements(this->bucket_count_) ->Owner  [L98] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ centroids->Ids(ids.data()) ->Dim(dim) ->Float32Vectors(data.data()) ->NumElements  [L98] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ centroids->Ids(ids.data()) ->Dim(dim) ->Float32Vectors  [L98] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ centroids->Ids(ids.data()) ->Dim  [L98] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ centroids->Ids  [L98] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ ids.data  [L98] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ data.data  [L100] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ cls.Run  [L108] if_statement@104 (ivf_partition_strategy_param_->partition_train_type == IVFNearestPartitionTrainerType::KMeansTrainer)
  │    │  ↳ 复用节点 #4 KMeansCluster::Run（本树前文已展开）
  │    ├─ dataset->GetFloat32Vectors  [L109] if_statement@104 (ivf_partition_strategy_param_->partition_train_type == IVFNearestPartitionTrainerType::KMeansTrainer)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ dataset->GetNumElements  [L110] if_statement@104 (ivf_partition_strategy_param_->partition_train_type == IVFNearestPartitionTrainerType::KMeansTrainer)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ memcpy  [L112] if_statement@104 (ivf_partition_strategy_param_->partition_train_type == IVFNearestPartitionTrainerType::KMeansTrainer)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ data.data  [L112] if_statement@104 (ivf_partition_strategy_param_->partition_train_type == IVFNearestPartitionTrainerType::KMeansTrainer)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ select_k_numbers  [L115] if_statement@104 (ivf_partition_strategy_param_->partition_train_type == IVFNearestPartitionTrainerType::KMeansTrainer) [else 分支] → if_statement@113 (ivf_partition_strategy_param_->partition_train_type == IVFNearestPartitionTrainerType::RandomTrainer)
  │    │  #13 select_k_numbers [src/utils/util_functions.cpp:43]
  │    │    ├─ VsagException  [L46] if_statement@45 (k > n || k <= 0)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ std::iota  [L50] 函数本体；短路求值/提前返回见源码
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ numbers.begin  [L50] 函数本体；短路求值/提前返回见源码
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ numbers.end  [L50] 函数本体；短路求值/提前返回见源码
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ std::swap  [L56] for_statement@54 i < k
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ dist  [L56] for_statement@54 i < k
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ numbers.resize  [L58] 函数本体；短路求值/提前返回见源码
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ dataset->GetNumElements  [L115] if_statement@104 (ivf_partition_strategy_param_->partition_train_type == IVFNearestPartitionTrainerType::KMeansTrainer) [else 分支] → if_statement@113 (ivf_partition_strategy_param_->partition_train_type == IVFNearestPartitionTrainerType::RandomTrainer)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ memcpy  [L117] if_statement@104 (ivf_partition_strategy_param_->partition_train_type == IVFNearestPartitionTrainerType::KMeansTrainer) [else 分支] → if_statement@113 (ivf_partition_strategy_param_->partition_train_type == IVFNearestPartitionTrainerType::RandomTrainer) → for_statement@116 i < bucket_count_
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ data.data  [L117] if_statement@104 (ivf_partition_strategy_param_->partition_train_type == IVFNearestPartitionTrainerType::KMeansTrainer) [else 分支] → if_statement@113 (ivf_partition_strategy_param_->partition_train_type == IVFNearestPartitionTrainerType::RandomTrainer) → for_statement@116 i < bucket_count_
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ dataset->GetFloat32Vectors  [L118] if_statement@104 (ivf_partition_strategy_param_->partition_train_type == IVFNearestPartitionTrainerType::KMeansTrainer) [else 分支] → if_statement@113 (ivf_partition_strategy_param_->partition_train_type == IVFNearestPartitionTrainerType::RandomTrainer) → for_statement@116 i < bucket_count_
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ Normalize  [L124] if_statement@122 (metric_type_ == MetricType::METRIC_TYPE_COSINE) → for_statement@123 i < bucket_count_
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ data.data  [L124] if_statement@122 (metric_type_ == MetricType::METRIC_TYPE_COSINE) → for_statement@123 i < bucket_count_
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ data.data  [L124] if_statement@122 (metric_type_ == MetricType::METRIC_TYPE_COSINE) → for_statement@123 i < bucket_count_
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ this->route_index_ptr_->Build  [L129] if_statement@128 (this->use_route_graph_)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ failed_ids.empty  [L130] if_statement@128 (this->use_route_graph_) → if_statement@130 (not failed_ids.empty())
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ VsagException  [L131] if_statement@128 (this->use_route_graph_) → if_statement@130 (not failed_ids.empty())
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ this->centroids_.resize  [L137] if_statement@128 (this->use_route_graph_) [else 分支]
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ memcpy  [L138] if_statement@128 (this->use_route_graph_) [else 分支]
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ this->centroids_.data  [L139] if_statement@128 (this->use_route_graph_) [else 分支]
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ data.data  [L139] if_statement@128 (this->use_route_graph_) [else 分支]
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ this->norms_.resize  [L140] if_statement@128 (this->use_route_graph_) [else 分支]
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ FP32ComputeIP  [L143] if_statement@128 (this->use_route_graph_) [else 分支] → if_statement@141 (metric_type_ == MetricType::METRIC_TYPE_L2SQR) → for_statement@142 i < bucket_count_
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ this->centroids_.data  [L143] if_statement@128 (this->use_route_graph_) [else 分支] → if_statement@141 (metric_type_ == MetricType::METRIC_TYPE_L2SQR) → for_statement@142 i < bucket_count_
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ this->centroids_.data  [L144] if_statement@128 (this->use_route_graph_) [else 分支] → if_statement@141 (metric_type_ == MetricType::METRIC_TYPE_L2SQR) → for_statement@142 i < bucket_count_
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ std::fill  [L151] if_statement@128 (this->use_route_graph_) [else 分支] → if_statement@141 (metric_type_ == MetricType::METRIC_TYPE_L2SQR) [else 分支]
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ this->norms_.begin  [L151] if_statement@128 (this->use_route_graph_) [else 分支] → if_statement@141 (metric_type_ == MetricType::METRIC_TYPE_L2SQR) [else 分支]
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ this->norms_.end  [L151] if_statement@128 (this->use_route_graph_) [else 分支] → if_statement@141 (metric_type_ == MetricType::METRIC_TYPE_L2SQR) [else 分支]
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ train_data->GetFloat32Vectors  [L134] 函数本体；短路求值/提前返回见源码
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ this->bucket_->Train  [L135] 函数本体；短路求值/提前返回见源码
  │  #14 BucketDataCell<QuantTmpl, IOTmpl>::Train [src/datacell/bucket_datacell.h:586]
  │    ├─ this->quantizer_->GetDim  [L591] if_statement@589 (use_residual_)
  │    │  #15 Quantizer::GetDim [src/quantization/quantizer.h:340]
  │    ├─ train_data_buffer.resize  [L592] if_statement@589 (use_residual_)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ Normalize  [L595] if_statement@589 (use_residual_) → if_statement@593 (metric_ == MetricType::METRIC_TYPE_COSINE) → for_statement@594 i < count
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ train_data_buffer.data  [L595] if_statement@589 (use_residual_) → if_statement@593 (metric_ == MetricType::METRIC_TYPE_COSINE) → for_statement@594 i < count
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ train_data_buffer.data  [L597] if_statement@589 (use_residual_) → if_statement@593 (metric_ == MetricType::METRIC_TYPE_COSINE)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ this->quantizer_->GetDim  [L599] if_statement@589 (use_residual_)
  │    │  ↳ 复用节点 #15 Quantizer::GetDim（本树前文已展开）
  │    ├─ strategy_->ClassifyDatas  [L600] if_statement@589 (use_residual_)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ strategy_->GetCentroid  [L602] if_statement@589 (use_residual_) → for_statement@601 i < count
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ train_data_buffer.data  [L607] if_statement@589 (use_residual_)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ this->quantizer_->Train  [L609] 函数本体；短路求值/提前返回见源码
  │    │  #16 Quantizer::Train [src/quantization/quantizer.h:49]
  │    │    ├─ cast().TrainImpl  [L54] 函数本体；短路求值/提前返回见源码
  │    │    │  #17 FP32Quantizer<metric>::TrainImpl [src/quantization/fp32_quantizer.cpp:50]
  │    │    ├─ cast  [L54] 函数本体；短路求值/提前返回见源码
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ this->precise_bucket_->Train  [L138] if_statement@136 (use_reorder_) → if_statement@137 (precise_bucket_ != nullptr)
  │  ↳ 复用节点 #14 BucketDataCell<QuantTmpl, IOTmpl>::Train（本树前文已展开）
  ├─ data->GetFloat32Vectors  [L138] if_statement@136 (use_reorder_) → if_statement@137 (precise_bucket_ != nullptr)
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ data->GetNumElements  [L138] if_statement@136 (use_reorder_) → if_statement@137 (precise_bucket_ != nullptr)
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ this->reorder_codes_->Train  [L140] if_statement@136 (use_reorder_) → if_statement@137 (precise_bucket_ != nullptr) [else 分支]
  │  ↳ 复用节点 #1 IVF::Train（本树前文已展开）
  ├─ data->GetFloat32Vectors  [L140] if_statement@136 (use_reorder_) → if_statement@137 (precise_bucket_ != nullptr) [else 分支]
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ data->GetNumElements  [L140] if_statement@136 (use_reorder_) → if_statement@137 (precise_bucket_ != nullptr) [else 分支]
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
```

## IVF::Add

[完整函数与全部调用点](function_reference/ivf_build.md#L146)

```text
#1 IVF::Add [src/algorithm/ivf/ivf_build.cpp:146]
  ├─ VsagException  [L150] if_statement@149 (not partition_strategy_->is_trained_)
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ this->bucket_->Unpack  [L152] 函数本体；短路求值/提前返回见源码
  │  #2 BucketDataCell::Unpack [src/datacell/bucket_datacell.h:139]
  │    ├─ GetQuantizerName  [L141] if_statement@141 (GetQuantizerName() == QUANTIZATION_TYPE_VALUE_PQFS)
  │    │  #3 BucketDataCell::GetQuantizerName [src/datacell/bucket_datacell.h:170]
  │    │    ├─ this->quantizer_->Name  [L172] 函数本体；短路求值/提前返回见源码
  │    │    │  #4 Quantizer::Name [src/quantization/quantizer.h:300]
  │    │    │    ├─ cast().NameImpl  [L302] 函数本体；短路求值/提前返回见源码
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ cast  [L302] 函数本体；短路求值/提前返回见源码
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ this->unpack_fastscan  [L142] if_statement@141 (GetQuantizerName() == QUANTIZATION_TYPE_VALUE_PQFS)
  │    │  #5 BucketDataCell<QuantTmpl, IOTmpl>::unpack_fastscan [src/datacell/bucket_datacell.h:958]
  │    │    ├─ this->datas_[i].Acquire  [L966] for_statement@961 i < this->bucket_count_
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ lease.Data  [L967] for_statement@961 i < this->bucket_count_
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ quantizer_->Unpack32  [L971] for_statement@961 i < this->bucket_count_ → while_statement@969 (begin < bucket_size)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ this->datas_[i].Write  [L972] for_statement@961 i < this->bucket_count_ → while_statement@969 (begin < bucket_size)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ this->precise_bucket_->Unpack  [L154] if_statement@153 (precise_bucket_ != nullptr)
  │  ↳ 复用节点 #2 BucketDataCell::Unpack（本树前文已展开）
  ├─ base->GetNumElements  [L156] 函数本体；短路求值/提前返回见源码
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ base->GetIds  [L157] 函数本体；短路求值/提前返回见源码
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ base->GetFloat32Vectors  [L158] 函数本体；短路求值/提前返回见源码
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ base->GetAttributeSets  [L159] 函数本体；短路求值/提前返回见源码
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ base->GetExtraInfos  [L160] 函数本体；短路求值/提前返回见源码
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ base->GetExtraInfoSize  [L161] 函数本体；短路求值/提前返回见源码
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ partition_strategy_->ClassifyDatas  [L163] 函数本体；短路求值/提前返回见源码
  │  ├─ 以下为分派/重载候选，并非全部依次执行
  │  #6 GNOIMIPartition::ClassifyDatas [src/algorithm/ivf/gno_imi_partition.cpp:201]
  │    ├─ norm_vectors.resize  [L208] if_statement@207 (metric_type_ == MetricType::METRIC_TYPE_COSINE)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ Normalize  [L210] if_statement@207 (metric_type_ == MetricType::METRIC_TYPE_COSINE) → for_statement@209 i < count
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ norm_vectors.data  [L211] if_statement@207 (metric_type_ == MetricType::METRIC_TYPE_COSINE) → for_statement@209 i < count
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ norm_vectors.data  [L213] if_statement@207 (metric_type_ == MetricType::METRIC_TYPE_COSINE)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ inner_joint_classify_datas  [L216] 函数本体；短路求值/提前返回见源码
  │    │  #7 GNOIMIPartition::inner_joint_classify_datas [src/algorithm/ivf/gno_imi_partition.cpp:367]
  │    │    ├─ matmul  [L377] 函数本体；短路求值/提前返回见源码
  │    │    │  #8 matmul [src/algorithm/ivf/gno_imi_partition.cpp:40]
  │    │    │    ├─ BlasFunction::Sgemm  [L42] 函数本体；短路求值/提前返回见源码
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ data_centroids_s_.data  [L377] 函数本体；短路求值/提前返回见源码
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ dist_to_s.data  [L377] 函数本体；短路求值/提前返回见源码
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ matmul  [L378] 函数本体；短路求值/提前返回见源码
  │    │    │  ↳ 复用节点 #8 matmul（本树前文已展开）
  │    │    ├─ data_centroids_t_.data  [L378] 函数本体；短路求值/提前返回见源码
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ dist_to_t.data  [L378] 函数本体；短路求值/提前返回见源码
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ FP32ComputeIP  [L386] for_statement@385 i < count
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ std::sort  [L393] for_statement@385 i < count
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ precomputed_terms_s.begin  [L393] for_statement@385 i < count
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ precomputed_terms_s.end  [L393] for_statement@385 i < count
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ heap.size  [L402] for_statement@385 i < count → for_statement@396 j < bucket_count_s_ → for_statement@400 k < bucket_count_t_ → if_statement@402 (heap.size() >= buckets_per_data && std::sqrt(cur_precomputed_term_s) - std::sqrt(norms_t_[cur_bucket_id_t]) > std::sqrt(heap.top().first))
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ std::sqrt  [L403] for_statement@385 i < count → for_statement@396 j < bucket_count_s_ → for_statement@400 k < bucket_count_t_ → if_statement@402 (heap.size() >= buckets_per_data && std::sqrt(cur_precomputed_term_s) - std::sqrt(norms_t_[cur_bucket_id_t]) > std::sqrt(heap.top().first))
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ std::sqrt  [L403] for_statement@385 i < count → for_statement@396 j < bucket_count_s_ → for_statement@400 k < bucket_count_t_ → if_statement@402 (heap.size() >= buckets_per_data && std::sqrt(cur_precomputed_term_s) - std::sqrt(norms_t_[cur_bucket_id_t]) > std::sqrt(heap.top().first))
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ std::sqrt  [L404] for_statement@385 i < count → for_statement@396 j < bucket_count_s_ → for_statement@400 k < bucket_count_t_ → if_statement@402 (heap.size() >= buckets_per_data && std::sqrt(cur_precomputed_term_s) - std::sqrt(norms_t_[cur_bucket_id_t]) > std::sqrt(heap.top().first))
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ heap.top  [L404] for_statement@385 i < count → for_statement@396 j < bucket_count_s_ → for_statement@400 k < bucket_count_t_ → if_statement@402 (heap.size() >= buckets_per_data && std::sqrt(cur_precomputed_term_s) - std::sqrt(norms_t_[cur_bucket_id_t]) > std::sqrt(heap.top().first))
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ heap.size  [L414] for_statement@385 i < count → for_statement@396 j < bucket_count_s_ → for_statement@400 k < bucket_count_t_ → if_statement@414 (heap.size() < buckets_per_data || dist < heap.top().first)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ heap.top  [L414] for_statement@385 i < count → for_statement@396 j < bucket_count_s_ → for_statement@400 k < bucket_count_t_ → if_statement@414 (heap.size() < buckets_per_data || dist < heap.top().first)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ heap.emplace  [L415] for_statement@385 i < count → for_statement@396 j < bucket_count_s_ → for_statement@400 k < bucket_count_t_ → if_statement@414 (heap.size() < buckets_per_data || dist < heap.top().first)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ heap.size  [L417] for_statement@385 i < count → for_statement@396 j < bucket_count_s_ → for_statement@400 k < bucket_count_t_ → if_statement@417 (heap.size() > buckets_per_data)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ heap.pop  [L418] for_statement@385 i < count → for_statement@396 j < bucket_count_s_ → for_statement@400 k < bucket_count_t_ → if_statement@417 (heap.size() > buckets_per_data)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ heap.top  [L424] for_statement@385 i < count → for_statement@423 j >= 0
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ heap.top  [L426] for_statement@385 i < count → for_statement@423 j >= 0 → if_statement@425 (j == 0)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ heap.pop  [L428] for_statement@385 i < count → for_statement@423 j >= 0
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ ctx->stats->dist_cmp.fetch_add  [L433] if_statement@432 (ctx != nullptr and ctx->stats != nullptr)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ ctx->stats->AddDistance  [L434] if_statement@432 (ctx != nullptr and ctx->stats != nullptr)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ result.data  [L217] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │  #9 IVFNearestPartition::ClassifyDatas [src/algorithm/ivf/ivf_nearest_partition.cpp:157]
  │    ├─ this->classify_datas_by_scan  [L163] if_statement@162 (not this->use_route_graph_)
  │    │  #10 IVFNearestPartition::classify_datas_by_scan [src/algorithm/ivf/ivf_nearest_partition.cpp:313]
  │    │    ├─ std::min<BucketIdType>  [L325] 函数本体；短路求值/提前返回见源码
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ norm_vectors.resize  [L333] if_statement@332 (metric_type_ == MetricType::METRIC_TYPE_COSINE)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ Normalize  [L335] if_statement@332 (metric_type_ == MetricType::METRIC_TYPE_COSINE) → for_statement@334 i < count
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ norm_vectors.data  [L335] if_statement@332 (metric_type_ == MetricType::METRIC_TYPE_COSINE) → for_statement@334 i < count
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ norm_vectors.data  [L337] if_statement@332 (metric_type_ == MetricType::METRIC_TYPE_COSINE)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ compute_centroid_dots  [L342] 函数本体；短路求值/提前返回见源码
  │    │    │  #11 compute_centroid_dots [src/algorithm/ivf/ivf_nearest_partition.cpp:51]
  │    │    │    ├─ BlasFunction::Sgemm  [L53] 函数本体；短路求值/提前返回见源码
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ this->centroids_.data  [L343] 函数本体；短路求值/提前返回见源码
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ dots.data  [L343] 函数本体；短路求值/提前返回见源码
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ heap_storage.reserve  [L347] lambda@345（定义体，执行时间取决于调用/调度）
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ std::move  [L348] lambda@345（定义体，执行时间取决于调用/调度）
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ dots.data  [L349] lambda@345（定义体，执行时间取决于调用/调度）
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ heap.size  [L353] lambda@345（定义体，执行时间取决于调用/调度） → for_statement@350 b < bucket_count_ → if_statement@353 (heap.size() < k || candidate < heap.top())
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ heap.top  [L353] lambda@345（定义体，执行时间取决于调用/调度） → for_statement@350 b < bucket_count_ → if_statement@353 (heap.size() < k || candidate < heap.top())
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ heap.push  [L354] lambda@345（定义体，执行时间取决于调用/调度） → for_statement@350 b < bucket_count_ → if_statement@353 (heap.size() < k || candidate < heap.top())
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ heap.size  [L356] lambda@345（定义体，执行时间取决于调用/调度） → for_statement@350 b < bucket_count_ → if_statement@356 (heap.size() > k)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ heap.pop  [L357] lambda@345（定义体，执行时间取决于调用/调度） → for_statement@350 b < bucket_count_ → if_statement@356 (heap.size() > k)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ heap.top  [L361] lambda@345（定义体，执行时间取决于调用/调度） → for_statement@360 j > 0
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ heap.pop  [L362] lambda@345（定义体，执行时间取决于调用/调度） → for_statement@360 j > 0
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ task  [L367] if_statement@365 (thread_pool_ == nullptr or count == 1) → for_statement@366 i < count
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ futures.push_back  [L372] if_statement@365 (thread_pool_ == nullptr or count == 1) [else 分支] → for_statement@371 i < count
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ thread_pool_->GeneralEnqueue  [L372] if_statement@365 (thread_pool_ == nullptr or count == 1) [else 分支] → for_statement@371 i < count
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ item.get  [L375] if_statement@365 (thread_pool_ == nullptr or count == 1) [else 分支] → for_range_loop@374
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ std::min<uint64_t>  [L383] if_statement@379 (ctx != nullptr and ctx->stats != nullptr)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ std::numeric_limits<uint32_t>::max  [L383] if_statement@379 (ctx != nullptr and ctx->stats != nullptr)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ ctx->stats->dist_cmp.fetch_add  [L384] if_statement@379 (ctx != nullptr and ctx->stats != nullptr)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ ctx->stats->AddDistance  [L385] if_statement@379 (ctx != nullptr and ctx->stats != nullptr)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ Dataset::Make  [L169] lambda@168（定义体，执行时间取决于调用/调度）
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ query->Dim(this->dim_) ->Float32Vectors(reinterpret_cast<const float*>(datas) + i * this->dim_) ->NumElements(1) ->Owner  [L170] lambda@168（定义体，执行时间取决于调用/调度）
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ query->Dim(this->dim_) ->Float32Vectors(reinterpret_cast<const float*>(datas) + i * this->dim_) ->NumElements  [L170] lambda@168（定义体，执行时间取决于调用/调度）
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ query->Dim(this->dim_) ->Float32Vectors  [L170] lambda@168（定义体，执行时间取决于调用/调度）
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ query->Dim  [L170] lambda@168（定义体，执行时间取决于调用/调度）
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ fmt::format  [L175] lambda@168（定义体，执行时间取决于调用/调度）
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ std::max<int64_t>  [L176] lambda@168（定义体，执行时间取决于调用/调度）
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ this->route_index_ptr_->KnnSearch  [L179] lambda@168（定义体，执行时间取决于调用/调度）
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ search_result->GetIds  [L180] lambda@168（定义体，执行时间取决于调用/调度）
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ search_result->GetDim  [L182] lambda@168（定义体，执行时间取决于调用/调度） → for_statement@182 j < search_result->GetDim()
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ search_result->GetStatistics  [L191] lambda@168（定义体，执行时间取决于调用/调度） → if_statement@186 (ctx != nullptr and ctx->stats != nullptr)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ std::atoi  [L192] lambda@168（定义体，执行时间取决于调用/调度） → if_statement@186 (ctx != nullptr and ctx->stats != nullptr)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ route_stats[0].c_str  [L192] lambda@168（定义体，执行时间取决于调用/调度） → if_statement@186 (ctx != nullptr and ctx->stats != nullptr)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ route_stats.size  [L194] lambda@168（定义体，执行时间取决于调用/调度） → if_statement@186 (ctx != nullptr and ctx->stats != nullptr) → if_statement@194 (route_stats.size() > 1)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ std::strtoull  [L195] lambda@168（定义体，执行时间取决于调用/调度） → if_statement@186 (ctx != nullptr and ctx->stats != nullptr) → if_statement@194 (route_stats.size() > 1)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ route_stats[1].c_str  [L195] lambda@168（定义体，执行时间取决于调用/调度） → if_statement@186 (ctx != nullptr and ctx->stats != nullptr) → if_statement@194 (route_stats.size() > 1)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ ctx->stats->AddDistance  [L201] lambda@168（定义体，执行时间取决于调用/调度） → if_statement@186 (ctx != nullptr and ctx->stats != nullptr)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ task  [L208] if_statement@206 (thread_pool_ == nullptr or count == 1) → for_statement@207 i < count
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ futures.push_back  [L213] if_statement@206 (thread_pool_ == nullptr or count == 1) [else 分支] → for_statement@212 i < count
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ thread_pool_->GeneralEnqueue  [L213] if_statement@206 (thread_pool_ == nullptr or count == 1) [else 分支] → for_statement@212 i < count
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ item.get  [L216] if_statement@206 (thread_pool_ == nullptr or count == 1) [else 分支] → for_range_loop@215
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ ctx->stats->dist_cmp.fetch_add  [L221] if_statement@220 (ctx != nullptr and ctx->stats != nullptr)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ std::move  [L224] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ VsagException  [L172] if_statement@170 (precise_bucket_ != nullptr) → if_statement@171 (num_element < 0 or current_num < 0)
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ std::numeric_limits<InnerIdType>::max  [L178] if_statement@170 (precise_bucket_ != nullptr)
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ VsagException  [L180] if_statement@170 (precise_bucket_ != nullptr) → if_statement@179 (posting_count > max_inner_id or current_count > max_inner_id - posting_count)
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ this->reorder_codes_->BatchInsertVector  [L185] if_statement@184 (use_reorder_ and precise_bucket_ == nullptr)
  │  #12 BucketDataCell<QuantTmpl, IOTmpl>::BatchInsertVector [src/datacell/bucket_datacell.h:703]
  │    ├─ VsagException  [L714] if_statement@712 (vectors == nullptr or bucket_ids == nullptr or inner_ids == nullptr or out_offsets == nullptr)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ VsagException  [L719] if_statement@717 (this->bucket_count_ <= 0 or input_dim_ == 0 or code_size_ == 0 or (use_residual_ and strategy_ == nullptr))
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ std::numeric_limits<size_t>::max  [L723] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ std::numeric_limits<uint64_t>::max  [L724] if_statement@724 (bucket_count == std::numeric_limits<uint64_t>::max() or bucket_count + 1 > max_allocation_size / sizeof(uint64_t) or batch_count > max_allocation_size / sizeof(uint64_t) or batch_count > max_allocation_size / sizeof(InnerIdType) or batch_count > max_allocation_size / sizeof(float) / input_dim_)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ VsagException  [L729] if_statement@724 (bucket_count == std::numeric_limits<uint64_t>::max() or bucket_count + 1 > max_allocation_size / sizeof(uint64_t) or batch_count > max_allocation_size / sizeof(uint64_t) or batch_count > max_allocation_size / sizeof(InnerIdType) or batch_count > max_allocation_size / sizeof(float) / input_dim_)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ check_valid_bucket_id  [L734] for_statement@733 i < batch_count
  │    │  #13 BucketDataCell::check_valid_bucket_id [src/datacell/bucket_datacell.h:244]
  │    │    ├─ VsagException  [L247] if_statement@246 (bucket_id >= this->bucket_count_ or bucket_id < 0)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ VsagException  [L736] for_statement@733 i < batch_count → if_statement@735 (inner_ids[i] == EMPTY_INNER_ID)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ bucket_begins.begin  [L746] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ bucket_begins.end  [L746] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ VsagException  [L760] for_statement@754 bucket_id < bucket_count → if_statement@759 (bucket_insert_count > max_allocation_size / static_cast<uint64_t>(code_size_))
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ residual_scores.resize  [L767] for_statement@754 bucket_id < bucket_count → if_statement@766 (use_residual_ and metric_ == MetricType::METRIC_TYPE_L2SQR)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ encode_vector  [L773] for_statement@754 bucket_id < bucket_count → for_statement@769 local_index < bucket_insert_count
  │    │  #14 BucketDataCell<QuantTmpl, IOTmpl>::encode_vector [src/datacell/bucket_datacell.h:613]
  │    │    ├─ this->quantizer_->EncodeOne  [L621] if_statement@620 (not use_residual_)
  │    │    │  #15 Quantizer::EncodeOne [src/quantization/quantizer.h:77]
  │    │    │    ├─ cast().EncodeOneImpl  [L79] 函数本体；短路求值/提前返回见源码
  │    │    │    │  #16 FP32Quantizer<metric>::EncodeOneImpl [src/quantization/fp32_quantizer.cpp:57]
  │    │    │    │    ├─ std::sqrt  [L63] if_statement@59 (metric == MetricType::METRIC_TYPE_COSINE) → if_statement@60 (this->hold_molds_)
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ FP32ComputeIP  [L63] if_statement@59 (metric == MetricType::METRIC_TYPE_COSINE) → if_statement@60 (this->hold_molds_)
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ memcpy  [L64] if_statement@59 (metric == MetricType::METRIC_TYPE_COSINE) → if_statement@60 (this->hold_molds_)
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ memcpy  [L65] if_statement@59 (metric == MetricType::METRIC_TYPE_COSINE) → if_statement@60 (this->hold_molds_)
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ Normalize  [L67] if_statement@59 (metric == MetricType::METRIC_TYPE_COSINE) → if_statement@60 (this->hold_molds_) [else 分支]
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ memcpy  [L70] if_statement@59 (metric == MetricType::METRIC_TYPE_COSINE) [else 分支]
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ cast  [L79] 函数本体；短路求值/提前返回见源码
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ this->quantizer_->GetDim  [L625] 函数本体；短路求值/提前返回见源码
  │    │    │  #17 Quantizer::GetDim [src/quantization/quantizer.h:340]
  │    │    ├─ this->quantizer_->GetDim  [L626] 函数本体；短路求值/提前返回见源码
  │    │    │  ↳ 复用节点 #17 Quantizer::GetDim（本树前文已展开）
  │    │    ├─ this->quantizer_->GetDim  [L627] 函数本体；短路求值/提前返回见源码
  │    │    │  ↳ 复用节点 #17 Quantizer::GetDim（本树前文已展开）
  │    │    ├─ strategy_->GetCentroid  [L628] 函数本体；短路求值/提前返回见源码
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ Normalize  [L630] if_statement@629 (metric_ == MetricType::METRIC_TYPE_COSINE)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ normalize_data.data  [L630] if_statement@629 (metric_ == MetricType::METRIC_TYPE_COSINE)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ quantizer_->GetDim  [L630] if_statement@629 (metric_ == MetricType::METRIC_TYPE_COSINE)
  │    │    │  ↳ 复用节点 #17 Quantizer::GetDim（本树前文已展开）
  │    │    ├─ normalize_data.data  [L631] if_statement@629 (metric_ == MetricType::METRIC_TYPE_COSINE)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ FP32Sub  [L633] 函数本体；短路求值/提前返回见源码
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ centroid.data  [L633] 函数本体；短路求值/提前返回见源码
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ sub_data.data  [L633] 函数本体；短路求值/提前返回见源码
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ quantizer_->GetDim  [L633] 函数本体；短路求值/提前返回见源码
  │    │    │  ↳ 复用节点 #17 Quantizer::GetDim（本树前文已展开）
  │    │    ├─ sub_data.data  [L634] 函数本体；短路求值/提前返回见源码
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ this->quantizer_->EncodeOne  [L635] 函数本体；短路求值/提前返回见源码
  │    │    │  ↳ 复用节点 #15 Quantizer::EncodeOne（本树前文已展开）
  │    │    ├─ this->quantizer_->DecodeOne  [L637] if_statement@636 (metric_ == MetricType::METRIC_TYPE_L2SQR)
  │    │    │  #18 Quantizer::DecodeOne [src/quantization/quantizer.h:116]
  │    │    │    ├─ cast().DecodeOneImpl  [L118] 函数本体；短路求值/提前返回见源码
  │    │    │    │  #19 FP32Quantizer<metric>::DecodeOneImpl [src/quantization/fp32_quantizer.cpp:85]
  │    │    │    │    ├─ memcpy  [L87] 函数本体；短路求值/提前返回见源码
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ cast  [L118] 函数本体；短路求值/提前返回见源码
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ normalize_data.data  [L637] if_statement@636 (metric_ == MetricType::METRIC_TYPE_L2SQR)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ FP32ComputeIP  [L639] if_statement@636 (metric_ == MetricType::METRIC_TYPE_L2SQR)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ centroid.data  [L639] if_statement@636 (metric_ == MetricType::METRIC_TYPE_L2SQR)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ normalize_data.data  [L639] if_statement@636 (metric_ == MetricType::METRIC_TYPE_L2SQR)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ this->quantizer_->GetDim  [L639] if_statement@636 (metric_ == MetricType::METRIC_TYPE_L2SQR)
  │    │    │  ↳ 复用节点 #17 Quantizer::GetDim（本树前文已展开）
  │    │    ├─ FP32ComputeIP  [L640] if_statement@636 (metric_ == MetricType::METRIC_TYPE_L2SQR)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ centroid.data  [L640] if_statement@636 (metric_ == MetricType::METRIC_TYPE_L2SQR)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ centroid.data  [L640] if_statement@636 (metric_ == MetricType::METRIC_TYPE_L2SQR)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ this->quantizer_->GetDim  [L640] if_statement@636 (metric_ == MetricType::METRIC_TYPE_L2SQR)
  │    │    │  ↳ 复用节点 #17 Quantizer::GetDim（本树前文已展开）
  │    ├─ residual_scores.empty  [L777] for_statement@754 bucket_id < bucket_count → for_statement@769 local_index < bucket_insert_count → if_statement@777 (not residual_scores.empty())
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ std::numeric_limits<InnerIdType>::max  [L785] for_statement@754 bucket_id < bucket_count → if_statement@784 (bucket_insert_count > static_cast<uint64_t>(std::numeric_limits<InnerIdType>::max()) - append_begin)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ VsagException  [L786] for_statement@754 bucket_id < bucket_count → if_statement@784 (bucket_insert_count > static_cast<uint64_t>(std::numeric_limits<InnerIdType>::max()) - append_begin)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ std::numeric_limits<uint64_t>::max  [L789] for_statement@754 bucket_id < bucket_count → if_statement@789 (next_size > std::numeric_limits<uint64_t>::max() / static_cast<uint64_t>(code_size_))
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ VsagException  [L790] for_statement@754 bucket_id < bucket_count → if_statement@789 (next_size > std::numeric_limits<uint64_t>::max() / static_cast<uint64_t>(code_size_))
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ check_valid_bucket_capacity  [L792] for_statement@754 bucket_id < bucket_count
  │    │  #20 BucketDataCell<QuantTmpl, IOTmpl>::check_valid_bucket_capacity [src/datacell/bucket_datacell.h:645]
  │    │    ├─ std::numeric_limits<size_t>::max  [L649] if_statement@648 (need_resize && (next_size > MAX_BUCKET_ENTRIES || next_size > std::numeric_limits<size_t>::max() / sizeof(InnerIdType) || (use_residual_ && metric_ == MetricType::METRIC_TYPE_L2SQR && next_size > std::numeric_limits<size_t>::max() / sizeof(float)) || ZERO_FILL_BLOCK_ENTRIES > std::numeric_limits<uint64_t>::max() / static_cast<uint64_t>(code_size_)))
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ std::numeric_limits<size_t>::max  [L651] if_statement@648 (need_resize && (next_size > MAX_BUCKET_ENTRIES || next_size > std::numeric_limits<size_t>::max() / sizeof(InnerIdType) || (use_residual_ && metric_ == MetricType::METRIC_TYPE_L2SQR && next_size > std::numeric_limits<size_t>::max() / sizeof(float)) || ZERO_FILL_BLOCK_ENTRIES > std::numeric_limits<uint64_t>::max() / static_cast<uint64_t>(code_size_)))
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ std::numeric_limits<uint64_t>::max  [L652] if_statement@648 (need_resize && (next_size > MAX_BUCKET_ENTRIES || next_size > std::numeric_limits<size_t>::max() / sizeof(InnerIdType) || (use_residual_ && metric_ == MetricType::METRIC_TYPE_L2SQR && next_size > std::numeric_limits<size_t>::max() / sizeof(float)) || ZERO_FILL_BLOCK_ENTRIES > std::numeric_limits<uint64_t>::max() / static_cast<uint64_t>(code_size_)))
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ VsagException  [L654] if_statement@648 (need_resize && (next_size > MAX_BUCKET_ENTRIES || next_size > std::numeric_limits<size_t>::max() / sizeof(InnerIdType) || (use_residual_ && metric_ == MetricType::METRIC_TYPE_L2SQR && next_size > std::numeric_limits<size_t>::max() / sizeof(float)) || ZERO_FILL_BLOCK_ENTRIES > std::numeric_limits<uint64_t>::max() / static_cast<uint64_t>(code_size_)))
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ this->inner_ids_[bucket_id].size  [L792] for_statement@754 bucket_id < bucket_count
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ this->datas_[bucket_id].Write  [L793] for_statement@754 bucket_id < bucket_count
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ this->inner_ids_[bucket_id].size  [L796] for_statement@754 bucket_id < bucket_count → if_statement@796 (this->inner_ids_[bucket_id].size() < next_size)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ this->inner_ids_[bucket_id].resize  [L797] for_statement@754 bucket_id < bucket_count → if_statement@796 (this->inner_ids_[bucket_id].size() < next_size)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ residual_scores.empty  [L799] for_statement@754 bucket_id < bucket_count → if_statement@799 (not residual_scores.empty() and this->residual_bias_[bucket_id].size() < next_size)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ this->residual_bias_[bucket_id].size  [L799] for_statement@754 bucket_id < bucket_count → if_statement@799 (not residual_scores.empty() and this->residual_bias_[bucket_id].size() < next_size)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ this->residual_bias_[bucket_id].resize  [L800] for_statement@754 bucket_id < bucket_count → if_statement@799 (not residual_scores.empty() and this->residual_bias_[bucket_id].size() < next_size)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ residual_scores.empty  [L807] for_statement@754 bucket_id < bucket_count → for_statement@802 local_index < bucket_insert_count → if_statement@807 (not residual_scores.empty())
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ base->GetFloat32Vectors  [L185] if_statement@184 (use_reorder_ and precise_bucket_ == nullptr)
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ base->GetNumElements  [L186] if_statement@184 (use_reorder_ and precise_bucket_ == nullptr)
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ this->label_table_->Insert  [L189] for_statement@188 i < num_element
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ location_map_.resize  [L196] 函数本体；短路求值/提前返回见源码
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ precise_offsets.resize  [L203] if_statement@200 (precise_bucket_ != nullptr)
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ precise_bucket_->BatchInsertVector  [L207] if_statement@200 (precise_bucket_ != nullptr)
  │  ↳ 复用节点 #12 BucketDataCell<QuantTmpl, IOTmpl>::BatchInsertVector（本树前文已展开）
  ├─ buckets.data  [L208] if_statement@200 (precise_bucket_ != nullptr)
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ posting_ids.data  [L209] if_statement@200 (precise_bucket_ != nullptr)
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ precise_offsets.data  [L211] if_statement@200 (precise_bucket_ != nullptr)
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ bucket_->InsertVectorWithOffset  [L223] lambda@214（定义体，执行时间取决于调用/调度） → for_statement@215 j < buckets_per_data_ → if_statement@220 (precise_bucket_ != nullptr)
  │  #21 BucketDataCell<QuantTmpl, IOTmpl>::InsertVectorWithOffset [src/datacell/bucket_datacell.h:818]
  │    ├─ check_valid_bucket_id  [L823] 函数本体；短路求值/提前返回见源码
  │    │  ↳ 复用节点 #13 BucketDataCell::check_valid_bucket_id（本树前文已展开）
  │    ├─ VsagException  [L825] if_statement@824 (inner_id == EMPTY_INNER_ID)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ VsagException  [L829] if_statement@827 (std::is_signed_v<InnerIdType>) → if_statement@828 (offset_id < 0)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ std::numeric_limits<InnerIdType>::max  [L832] if_statement@832 (offset_id >= std::numeric_limits<InnerIdType>::max() || static_cast<uint64_t>(offset_id) > std::numeric_limits<uint64_t>::max() / static_cast<uint64_t>(code_size_))
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ std::numeric_limits<uint64_t>::max  [L834] if_statement@832 (offset_id >= std::numeric_limits<InnerIdType>::max() || static_cast<uint64_t>(offset_id) > std::numeric_limits<uint64_t>::max() / static_cast<uint64_t>(code_size_))
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ VsagException  [L835] if_statement@832 (offset_id >= std::numeric_limits<InnerIdType>::max() || static_cast<uint64_t>(offset_id) > std::numeric_limits<uint64_t>::max() / static_cast<uint64_t>(code_size_))
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ encode_vector  [L840] 函数本体；短路求值/提前返回见源码
  │    │  ↳ 复用节点 #14 BucketDataCell<QuantTmpl, IOTmpl>::encode_vector（本树前文已展开）
  │    ├─ this->inner_ids_[bucket_id].size  [L844] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ check_valid_bucket_capacity  [L845] 函数本体；短路求值/提前返回见源码
  │    │  ↳ 复用节点 #20 BucketDataCell<QuantTmpl, IOTmpl>::check_valid_bucket_capacity（本树前文已展开）
  │    ├─ this->inner_ids_[bucket_id].resize  [L847] if_statement@846 (need_resize)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ this->residual_bias_[bucket_id].resize  [L849] if_statement@846 (need_resize) → if_statement@848 (use_residual_ && metric_ == MetricType::METRIC_TYPE_L2SQR)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ std::min<uint64_t>  [L853] if_statement@852 (offset_id > this->bucket_sizes_[bucket_id])
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ std::fill_n  [L858] if_statement@852 (offset_id > this->bucket_sizes_[bucket_id])
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ std::min<uint64_t>  [L860] if_statement@852 (offset_id > this->bucket_sizes_[bucket_id]) → for_statement@859 hole_offset < offset_id
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ this->datas_[bucket_id].Write  [L862] if_statement@852 (offset_id > this->bucket_sizes_[bucket_id]) → for_statement@859 hole_offset < offset_id
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ this->datas_[bucket_id].Write  [L869] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ std::max  [L878] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ bucket_->InsertVector  [L225] lambda@214（定义体，执行时间取决于调用/调度） → for_statement@215 j < buckets_per_data_ → if_statement@220 (precise_bucket_ != nullptr) [else 分支]
  │  #22 BucketDataCell<QuantTmpl, IOTmpl>::InsertVector [src/datacell/bucket_datacell.h:660]
  │    ├─ check_valid_bucket_id  [L664] 函数本体；短路求值/提前返回见源码
  │    │  ↳ 复用节点 #13 BucketDataCell::check_valid_bucket_id（本树前文已展开）
  │    ├─ VsagException  [L666] if_statement@665 (inner_id == EMPTY_INNER_ID)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ encode_vector  [L672] 函数本体；短路求值/提前返回见源码
  │    │  ↳ 复用节点 #14 BucketDataCell<QuantTmpl, IOTmpl>::encode_vector（本树前文已展开）
  │    ├─ std::numeric_limits<InnerIdType>::max  [L676] if_statement@676 (offset_id >= std::numeric_limits<InnerIdType>::max() || static_cast<uint64_t>(offset_id) > std::numeric_limits<uint64_t>::max() / static_cast<uint64_t>(code_size_))
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ std::numeric_limits<uint64_t>::max  [L678] if_statement@676 (offset_id >= std::numeric_limits<InnerIdType>::max() || static_cast<uint64_t>(offset_id) > std::numeric_limits<uint64_t>::max() / static_cast<uint64_t>(code_size_))
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ VsagException  [L679] if_statement@676 (offset_id >= std::numeric_limits<InnerIdType>::max() || static_cast<uint64_t>(offset_id) > std::numeric_limits<uint64_t>::max() / static_cast<uint64_t>(code_size_))
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ check_valid_bucket_capacity  [L682] 函数本体；短路求值/提前返回见源码
  │    │  ↳ 复用节点 #20 BucketDataCell<QuantTmpl, IOTmpl>::check_valid_bucket_capacity（本树前文已展开）
  │    ├─ this->inner_ids_[bucket_id].size  [L682] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ this->datas_[bucket_id].Write  [L683] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ this->inner_ids_[bucket_id].size  [L687] if_statement@687 (this->inner_ids_[bucket_id].size() < next_size)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ this->inner_ids_[bucket_id].resize  [L688] if_statement@687 (this->inner_ids_[bucket_id].size() < next_size)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ this->residual_bias_[bucket_id].resize  [L690] if_statement@687 (this->inner_ids_[bucket_id].size() < next_size) → if_statement@689 (use_residual_ && metric_ == MetricType::METRIC_TYPE_L2SQR)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ this->attr_filter_index_->Insert  [L236] lambda@214（定义体，执行时间取决于调用/调度） → for_statement@215 j < buckets_per_data_ → if_statement@233 (use_attribute_filter_ and this->attr_filter_index_ != nullptr and attr_sets != nullptr)
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ this->extra_infos_->InsertExtraInfo  [L239] lambda@214（定义体，执行时间取决于调用/调度） → for_statement@215 j < buckets_per_data_ → if_statement@238 (extra_info_size > 0)
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ futures.emplace_back  [L249] for_statement@247 i < num_element → if_statement@248 (this->thread_pool_ != nullptr)
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ thread_pool_->GeneralEnqueue  [L249] for_statement@247 i < num_element → if_statement@248 (this->thread_pool_ != nullptr)
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ add_func  [L251] for_statement@247 i < num_element → if_statement@248 (this->thread_pool_ != nullptr) [else 分支]
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ std::current_exception  [L255] catch_clause@254
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ future.get  [L261] if_statement@258 (this->thread_pool_ != nullptr) → for_range_loop@259
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ std::current_exception  [L264] if_statement@258 (this->thread_pool_ != nullptr) → for_range_loop@259 → catch_clause@262 → if_statement@263 (first_exception == nullptr)
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ std::rethrow_exception  [L270] if_statement@269 (first_exception != nullptr)
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ this->bucket_->Package  [L272] 函数本体；短路求值/提前返回见源码
  │  #23 BucketDataCell::Package [src/datacell/bucket_datacell.h:132]
  │    ├─ GetQuantizerName  [L134] if_statement@134 (GetQuantizerName() == QUANTIZATION_TYPE_VALUE_PQFS)
  │    │  ↳ 复用节点 #3 BucketDataCell::GetQuantizerName（本树前文已展开）
  │    ├─ this->package_fastscan  [L135] if_statement@134 (GetQuantizerName() == QUANTIZATION_TYPE_VALUE_PQFS)
  │    │  #24 BucketDataCell<QuantTmpl, IOTmpl>::package_fastscan [src/datacell/bucket_datacell.h:934]
  │    │    ├─ this->datas_[i].Acquire  [L942] for_statement@937 i < this->bucket_count_
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ lease.Data  [L943] for_statement@937 i < this->bucket_count_
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ quantizer_->Package32  [L950] for_statement@937 i < this->bucket_count_ → while_statement@945 (begin < bucket_size)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ this->datas_[i].Write  [L951] for_statement@937 i < this->bucket_count_ → while_statement@945 (begin < bucket_size)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ this->precise_bucket_->Package  [L274] if_statement@273 (precise_bucket_ != nullptr)
  │  ↳ 复用节点 #23 BucketDataCell::Package（本树前文已展开）
  ├─ this->cal_memory_usage  [L277] if_statement@276 (need_cal_memory_usage)
  │  #25 IVF::cal_memory_usage [src/algorithm/ivf/ivf.cpp:616]
  │    ├─ this->bucket_->GetMemoryUsage  [L619] 函数本体；短路求值/提前返回见源码
  │    │  #26 BucketDataCell::GetMemoryUsage [src/datacell/bucket_datacell.h:189]
  │    │    ├─ this->datas_[bucket_id].GetMemoryUsage  [L193] for_statement@192 bucket_id < this->bucket_count_
  │    │    │  ↳ 复用节点 #26 BucketDataCell::GetMemoryUsage（本树前文已展开）
  │    │    ├─ this->inner_ids_[bucket_id].size  [L194] for_statement@192 bucket_id < this->bucket_count_
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ this->residual_bias_[bucket_id].size  [L195] for_statement@192 bucket_id < this->bucket_count_
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ precise_bucket_->GetMemoryUsage  [L621] if_statement@620 (use_reorder_) → conditional_expression@621 precise_bucket_ != nullptr
  │    │  ↳ 复用节点 #26 BucketDataCell::GetMemoryUsage（本树前文已展开）
  │    ├─ reorder_codes_->GetMemoryUsage  [L622] if_statement@620 (use_reorder_) → conditional_expression@621 precise_bucket_ != nullptr
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ this->extra_infos_->GetMemoryUsage  [L625] if_statement@624 (this->extra_info_size_ > 0 and this->extra_infos_ != nullptr)
  │    │  #27 IVF::GetMemoryUsage [src/algorithm/ivf/ivf.cpp:639]
  │    │    ├─ this->current_memory_usage_.load  [L644] 函数本体；短路求值/提前返回见源码
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ this->attr_filter_index_->GetMemoryUsage  [L647] if_statement@646 (this->attr_filter_index_ != nullptr)
  │    │    │  ↳ 复用节点 #27 IVF::GetMemoryUsage（本树前文已展开）
  │    ├─ this->label_table_->GetMemoryUsage  [L627] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ location_map_.size  [L628] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ partition_strategy_->GetMemoryUsage  [L629] 函数本体；短路求值/提前返回见源码
  │    │  ├─ 以下为分派/重载候选，并非全部依次执行
  │    │  #28 IVFNearestPartition::GetMemoryUsage [src/algorithm/ivf/ivf_nearest_partition.cpp:303]
  │    │    ├─ this->route_index_ptr_->GetMemoryUsage  [L307] if_statement@306 (this->use_route_graph_)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ this->centroids_.size  [L309] 函数本体；短路求值/提前返回见源码
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ this->norms_.size  [L310] 函数本体；短路求值/提前返回见源码
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │  #29 IVFPartitionStrategy::GetMemoryUsage [src/algorithm/ivf/ivf_partition_strategy.h:93]
  │    ├─ g->GetMemoryUsage  [L632] for_range_loop@630 → if_statement@631 (g != nullptr)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ this->current_memory_usage_.store  [L636] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
```

## IVF::create_search_param

[完整函数与全部调用点](function_reference/ivf_search.md#L86)

```text
#1 IVF::create_search_param [src/algorithm/ivf/ivf_search.cpp:86]
  ├─ this->create_search_filter  [L89] 函数本体；短路求值/提前返回见源码
  │  #2 InnerIndexInterface::create_search_filter [src/algorithm/inner_index_interface.cpp:1108]
  │    ├─ this->label_table_->GetDeletedIdsFilter  [L1111] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ std::make_shared<ExtraInfoWrapperFilter>  [L1116] if_statement@1113 (user_filter != nullptr) → if_statement@1114 (use_extra_info_filter && this->extra_infos_ != nullptr)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ std::make_shared<InnerIdWrapperFilter>  [L1119] if_statement@1113 (user_filter != nullptr) → if_statement@1114 (use_extra_info_filter && this->extra_infos_ != nullptr) [else 分支]
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ std::make_shared<CombinedFilter>  [L1134] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ combined_filter->AppendFilter  [L1135] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ combined_filter->AppendFilter  [L1136] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ IVFSearchParameters::FromJson  [L90] 函数本体；短路求值/提前返回见源码
  │  #3 IVFSearchParameters::FromJson [src/algorithm/ivf/ivf_parameter.cpp:150]
  │    ├─ JsonType::Parse  [L152] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ CHECK_ARGUMENT  [L156] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ params.Contains  [L156] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ fmt::format  [L157] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ obj.IndexSearchParameter::FromJson  [L159] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ CHECK_ARGUMENT  [L162] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ params[INDEX_TYPE_IVF].Contains  [L162] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ fmt::format  [L163] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ params[INDEX_TYPE_IVF][IVF_SEARCH_PARAM_SCAN_BUCKETS_COUNT].GetInt  [L166] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ params[INDEX_TYPE_IVF].Contains  [L168] if_statement@168 (params[INDEX_TYPE_IVF].Contains(IVF_SEARCH_PARAM_DISABLE_BUCKET_SCAN))
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ params[INDEX_TYPE_IVF][IVF_SEARCH_PARAM_DISABLE_BUCKET_SCAN].GetBool  [L170] if_statement@168 (params[INDEX_TYPE_IVF].Contains(IVF_SEARCH_PARAM_DISABLE_BUCKET_SCAN))
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ params[INDEX_TYPE_IVF].Contains  [L174] if_statement@174 (params[INDEX_TYPE_IVF].Contains(GNO_IMI_SEARCH_PARAM_FIRST_ORDER_SCAN_RATIO))
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ params[INDEX_TYPE_IVF][GNO_IMI_SEARCH_PARAM_FIRST_ORDER_SCAN_RATIO].GetFloat  [L176] if_statement@174 (params[INDEX_TYPE_IVF].Contains(GNO_IMI_SEARCH_PARAM_FIRST_ORDER_SCAN_RATIO))
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ params[INDEX_TYPE_IVF].Contains  [L179] if_statement@179 (params[INDEX_TYPE_IVF].Contains(IVF_SEARCH_PARAM_EF_SEARCH))
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ params[INDEX_TYPE_IVF][IVF_SEARCH_PARAM_EF_SEARCH].GetInt  [L180] if_statement@179 (params[INDEX_TYPE_IVF].Contains(IVF_SEARCH_PARAM_EF_SEARCH))
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ std::min  [L94] if_statement@91 (search_param.disable_bucket_scan) [else 分支]
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ std::make_shared<Timer>  [L104] if_statement@103 (search_param.enable_time_record)
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ param.time_cost->SetThreshold  [L105] if_statement@103 (search_param.enable_time_record)
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
```

## IVF::SearchWithRequest

[完整函数与全部调用点](function_reference/ivf_search.md#L492)

```text
#1 IVF::SearchWithRequest [src/algorithm/ivf/ivf_search.cpp:492]
  ├─ ValidateSearchThreshold  [L494] 函数本体；短路求值/提前返回见源码
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ this->create_search_param  [L500] 函数本体；短路求值/提前返回见源码
  │  #2 IVF::create_search_param [src/algorithm/ivf/ivf_search.cpp:86]
  │    ├─ this->create_search_filter  [L89] 函数本体；短路求值/提前返回见源码
  │    │  #3 InnerIndexInterface::create_search_filter [src/algorithm/inner_index_interface.cpp:1108]
  │    │    ├─ this->label_table_->GetDeletedIdsFilter  [L1111] 函数本体；短路求值/提前返回见源码
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ std::make_shared<ExtraInfoWrapperFilter>  [L1116] if_statement@1113 (user_filter != nullptr) → if_statement@1114 (use_extra_info_filter && this->extra_infos_ != nullptr)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ std::make_shared<InnerIdWrapperFilter>  [L1119] if_statement@1113 (user_filter != nullptr) → if_statement@1114 (use_extra_info_filter && this->extra_infos_ != nullptr) [else 分支]
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ std::make_shared<CombinedFilter>  [L1134] 函数本体；短路求值/提前返回见源码
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ combined_filter->AppendFilter  [L1135] 函数本体；短路求值/提前返回见源码
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ combined_filter->AppendFilter  [L1136] 函数本体；短路求值/提前返回见源码
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ IVFSearchParameters::FromJson  [L90] 函数本体；短路求值/提前返回见源码
  │    │  #4 IVFSearchParameters::FromJson [src/algorithm/ivf/ivf_parameter.cpp:150]
  │    │    ├─ JsonType::Parse  [L152] 函数本体；短路求值/提前返回见源码
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ CHECK_ARGUMENT  [L156] 函数本体；短路求值/提前返回见源码
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ params.Contains  [L156] 函数本体；短路求值/提前返回见源码
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ fmt::format  [L157] 函数本体；短路求值/提前返回见源码
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ obj.IndexSearchParameter::FromJson  [L159] 函数本体；短路求值/提前返回见源码
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ CHECK_ARGUMENT  [L162] 函数本体；短路求值/提前返回见源码
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ params[INDEX_TYPE_IVF].Contains  [L162] 函数本体；短路求值/提前返回见源码
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ fmt::format  [L163] 函数本体；短路求值/提前返回见源码
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ params[INDEX_TYPE_IVF][IVF_SEARCH_PARAM_SCAN_BUCKETS_COUNT].GetInt  [L166] 函数本体；短路求值/提前返回见源码
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ params[INDEX_TYPE_IVF].Contains  [L168] if_statement@168 (params[INDEX_TYPE_IVF].Contains(IVF_SEARCH_PARAM_DISABLE_BUCKET_SCAN))
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ params[INDEX_TYPE_IVF][IVF_SEARCH_PARAM_DISABLE_BUCKET_SCAN].GetBool  [L170] if_statement@168 (params[INDEX_TYPE_IVF].Contains(IVF_SEARCH_PARAM_DISABLE_BUCKET_SCAN))
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ params[INDEX_TYPE_IVF].Contains  [L174] if_statement@174 (params[INDEX_TYPE_IVF].Contains(GNO_IMI_SEARCH_PARAM_FIRST_ORDER_SCAN_RATIO))
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ params[INDEX_TYPE_IVF][GNO_IMI_SEARCH_PARAM_FIRST_ORDER_SCAN_RATIO].GetFloat  [L176] if_statement@174 (params[INDEX_TYPE_IVF].Contains(GNO_IMI_SEARCH_PARAM_FIRST_ORDER_SCAN_RATIO))
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ params[INDEX_TYPE_IVF].Contains  [L179] if_statement@179 (params[INDEX_TYPE_IVF].Contains(IVF_SEARCH_PARAM_EF_SEARCH))
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ params[INDEX_TYPE_IVF][IVF_SEARCH_PARAM_EF_SEARCH].GetInt  [L180] if_statement@179 (params[INDEX_TYPE_IVF].Contains(IVF_SEARCH_PARAM_EF_SEARCH))
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ std::min  [L94] if_statement@91 (search_param.disable_bucket_scan) [else 分支]
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ std::make_shared<Timer>  [L104] if_statement@103 (search_param.enable_time_record)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ param.time_cost->SetThreshold  [L105] if_statement@103 (search_param.enable_time_record)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ CHECK_ARGUMENT  [L503] if_statement@502 (use_custom_distance)
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ CHECK_ARGUMENT  [L505] if_statement@502 (use_custom_distance)
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ CHECK_ARGUMENT  [L506] if_statement@502 (use_custom_distance)
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ CHECK_ARGUMENT  [L508] if_statement@502 (use_custom_distance)
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ CHECK_ARGUMENT  [L509] if_statement@502 (use_custom_distance)
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ request.bucket_ids_.empty  [L515] if_statement@515 (not request.bucket_ids_.empty())
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ CHECK_ARGUMENT  [L517] if_statement@515 (not request.bucket_ids_.empty())
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ CHECK_ARGUMENT  [L518] if_statement@515 (not request.bucket_ids_.empty())
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ request.bucket_ids_.size  [L518] if_statement@515 (not request.bucket_ids_.empty())
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ query_check->GetNumElements  [L518] if_statement@515 (not request.bucket_ids_.empty())
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ fmt::format  [L519] if_statement@515 (not request.bucket_ids_.empty())
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ request.bucket_ids_.size  [L521] if_statement@515 (not request.bucket_ids_.empty())
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ query_check->GetNumElements  [L522] if_statement@515 (not request.bucket_ids_.empty())
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ CHECK_ARGUMENT  [L523] if_statement@515 (not request.bucket_ids_.empty())
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ query_check->GetFloat32Vectors  [L523] if_statement@515 (not request.bucket_ids_.empty())
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ CHECK_ARGUMENT  [L525] if_statement@515 (not request.bucket_ids_.empty())
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ query_check->GetDim  [L525] if_statement@515 (not request.bucket_ids_.empty())
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ CHECK_ARGUMENT  [L527] if_statement@515 (not request.bucket_ids_.empty())
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ request.bucket_ids_.size  [L529] if_statement@515 (not request.bucket_ids_.empty()) → for_statement@529 query_idx < request.bucket_ids_.size()
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ CHECK_ARGUMENT  [L531] if_statement@515 (not request.bucket_ids_.empty()) → for_statement@529 query_idx < request.bucket_ids_.size()
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ ids.empty  [L531] if_statement@515 (not request.bucket_ids_.empty()) → for_statement@529 query_idx < request.bucket_ids_.size()
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ fmt::format  [L532] if_statement@515 (not request.bucket_ids_.empty()) → for_statement@529 query_idx < request.bucket_ids_.size()
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ CHECK_ARGUMENT  [L537] if_statement@515 (not request.bucket_ids_.empty()) → for_statement@529 query_idx < request.bucket_ids_.size() → for_range_loop@536
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ fmt::format  [L539] if_statement@515 (not request.bucket_ids_.empty()) → for_statement@529 query_idx < request.bucket_ids_.size() → for_range_loop@536
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ CHECK_ARGUMENT  [L541] if_statement@515 (not request.bucket_ids_.empty()) → for_statement@529 query_idx < request.bucket_ids_.size() → for_range_loop@536
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ fmt::format  [L543] if_statement@515 (not request.bucket_ids_.empty()) → for_statement@529 query_idx < request.bucket_ids_.size() → for_range_loop@536
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ CHECK_ARGUMENT  [L545] if_statement@515 (not request.bucket_ids_.empty()) → for_statement@529 query_idx < request.bucket_ids_.size() → for_range_loop@536
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ seen_ids.insert  [L545] if_statement@515 (not request.bucket_ids_.empty()) → for_statement@529 query_idx < request.bucket_ids_.size() → for_range_loop@536
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ fmt::format  [L546] if_statement@515 (not request.bucket_ids_.empty()) → for_statement@529 query_idx < request.bucket_ids_.size() → for_range_loop@536
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ query_check->GetNumElements  [L549] if_statement@515 (not request.bucket_ids_.empty()) → if_statement@549 (query_check->GetNumElements() == 1)
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ param.bucket_ids.assign  [L550] if_statement@515 (not request.bucket_ids_.empty()) → if_statement@549 (query_check->GetNumElements() == 1)
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ request.bucket_ids_[0].begin  [L550] if_statement@515 (not request.bucket_ids_.empty()) → if_statement@549 (query_check->GetNumElements() == 1)
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ request.bucket_ids_[0].end  [L550] if_statement@515 (not request.bucket_ids_.empty()) → if_statement@549 (query_check->GetNumElements() == 1)
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ CHECK_ARGUMENT  [L556] if_statement@555 (use_custom_distance)
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ CHECK_ARGUMENT  [L557] if_statement@555 (use_custom_distance)
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ query->GetNumElements  [L557] if_statement@555 (use_custom_distance)
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ CHECK_ARGUMENT  [L559] if_statement@555 (use_custom_distance)
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ query->GetFloat32Vectors  [L559] if_statement@555 (use_custom_distance)
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ CHECK_ARGUMENT  [L561] if_statement@555 (use_custom_distance)
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ query->GetDim  [L561] if_statement@555 (use_custom_distance)
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ CHECK_ARGUMENT  [L564] if_statement@563 (param.disable_bucket_scan)
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ CHECK_ARGUMENT  [L565] if_statement@563 (param.disable_bucket_scan)
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ query->GetNumElements  [L565] if_statement@563 (param.disable_bucket_scan)
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ CHECK_ARGUMENT  [L567] if_statement@563 (param.disable_bucket_scan)
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ query->GetFloat32Vectors  [L567] if_statement@563 (param.disable_bucket_scan)
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ CHECK_ARGUMENT  [L569] if_statement@563 (param.disable_bucket_scan)
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ query->GetDim  [L569] if_statement@563 (param.disable_bucket_scan)
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ CHECK_ARGUMENT  [L570] if_statement@563 (param.disable_bucket_scan)
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ request.threshold_.has_value  [L570] if_statement@563 (param.disable_bucket_scan)
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ this->route_buckets_only  [L572] if_statement@563 (param.disable_bucket_scan)
  │  #5 IVF::route_buckets_only [src/algorithm/ivf/ivf_search.cpp:110]
  │    ├─ query->GetNumElements  [L114] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ query->GetFloat32Vectors  [L115] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ partition_strategy_->ClassifyDatasForSearch  [L118] 函数本体；短路求值/提前返回见源码
  │    │  ├─ 以下为分派/重载候选，并非全部依次执行
  │    │  #6 GNOIMIPartition::ClassifyDatasForSearch [src/algorithm/ivf/gno_imi_partition.cpp:221]
  │    │    ├─ norm_vectors.resize  [L228] if_statement@227 (metric_type_ == MetricType::METRIC_TYPE_COSINE)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ Normalize  [L230] if_statement@227 (metric_type_ == MetricType::METRIC_TYPE_COSINE) → for_statement@229 i < count
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ norm_vectors.data  [L231] if_statement@227 (metric_type_ == MetricType::METRIC_TYPE_COSINE) → for_statement@229 i < count
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ norm_vectors.data  [L233] if_statement@227 (metric_type_ == MetricType::METRIC_TYPE_COSINE)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ std::fill  [L237] 函数本体；短路求值/提前返回见源码
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ result.begin  [L237] 函数本体；短路求值/提前返回见源码
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ result.end  [L237] 函数本体；短路求值/提前返回见源码
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ dist_to_s.data  [L243] 函数本体；短路求值/提前返回见源码
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ dist_to_t.data  [L244] 函数本体；短路求值/提前返回见源码
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ candidate_s_id.data  [L245] 函数本体；短路求值/提前返回见源码
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ candidate_s_dist.data  [L246] 函数本体；短路求值/提前返回见源码
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ matmul  [L249] 函数本体；短路求值/提前返回见源码
  │    │    │  #7 matmul [src/algorithm/ivf/gno_imi_partition.cpp:40]
  │    │    │    ├─ BlasFunction::Sgemm  [L42] 函数本体；短路求值/提前返回见源码
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ data_centroids_s_.data  [L250] 函数本体；短路求值/提前返回见源码
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ matmul  [L255] 函数本体；短路求值/提前返回见源码
  │    │    │  ↳ 复用节点 #7 matmul（本树前文已展开）
  │    │    ├─ data_centroids_t_.data  [L256] 函数本体；短路求值/提前返回见源码
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ FP32ComputeIP  [L263] for_statement@262 i < count
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ heap.size  [L271] for_statement@262 i < count → for_statement@268 j < bucket_count_s_ → if_statement@271 (heap.size() < candidate_count_s || dist_term_s < heap.top().first)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ heap.top  [L271] for_statement@262 i < count → for_statement@268 j < bucket_count_s_ → if_statement@271 (heap.size() < candidate_count_s || dist_term_s < heap.top().first)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ heap.emplace  [L272] for_statement@262 i < count → for_statement@268 j < bucket_count_s_ → if_statement@271 (heap.size() < candidate_count_s || dist_term_s < heap.top().first)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ heap.size  [L274] for_statement@262 i < count → for_statement@268 j < bucket_count_s_ → if_statement@274 (heap.size() > candidate_count_s)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ heap.pop  [L275] for_statement@262 i < count → for_statement@268 j < bucket_count_s_ → if_statement@274 (heap.size() > candidate_count_s)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ heap.top  [L279] for_statement@262 i < count → for_statement@278 j >= 0
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ heap.top  [L280] for_statement@262 i < count → for_statement@278 j >= 0
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ heap.pop  [L281] for_statement@262 i < count → for_statement@278 j >= 0
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ CHECK_ARGUMENT  [L283] for_statement@262 i < count
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ heap.empty  [L283] for_statement@262 i < count
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ fmt::format  [L283] for_statement@262 i < count
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ std::floor  [L286] for_statement@262 i < count
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ std::max  [L287] for_statement@262 i < count
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ heap.size  [L301] for_statement@262 i < count → for_statement@288 j < scan_bucket_count_s → for_statement@289 k < bucket_count_t_ → if_statement@301 (heap.size() < buckets_per_data || dist_term_st < heap.top().first)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ heap.top  [L301] for_statement@262 i < count → for_statement@288 j < scan_bucket_count_s → for_statement@289 k < bucket_count_t_ → if_statement@301 (heap.size() < buckets_per_data || dist_term_st < heap.top().first)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ heap.emplace  [L302] for_statement@262 i < count → for_statement@288 j < scan_bucket_count_s → for_statement@289 k < bucket_count_t_ → if_statement@301 (heap.size() < buckets_per_data || dist_term_st < heap.top().first)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ heap.size  [L304] for_statement@262 i < count → for_statement@288 j < scan_bucket_count_s → for_statement@289 k < bucket_count_t_ → if_statement@304 (heap.size() > buckets_per_data)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ heap.pop  [L305] for_statement@262 i < count → for_statement@288 j < scan_bucket_count_s → for_statement@289 k < bucket_count_t_ → if_statement@304 (heap.size() > buckets_per_data)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ std::min  [L309] for_statement@262 i < count
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ heap.size  [L309] for_statement@262 i < count
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ heap.empty  [L310] for_statement@262 i < count → for_statement@310 j >= 0 && !heap.empty()
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ heap.top  [L311] for_statement@262 i < count → for_statement@310 j >= 0 && !heap.empty()
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ heap.pop  [L312] for_statement@262 i < count → for_statement@310 j >= 0 && !heap.empty()
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ ctx->stats->AddDistance  [L316] if_statement@315 (ctx != nullptr and ctx->stats != nullptr)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │  #8 IVFPartitionStrategy::ClassifyDatasForSearch [src/algorithm/ivf/ivf_partition_strategy.h:64]
  │    │    ├─ std::move  [L69] 函数本体；短路求值/提前返回见源码
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ ClassifyDatas  [L69] 函数本体；短路求值/提前返回见源码
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ Dataset::Make  [L120] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ result->NumElements(0)->Dim  [L122] if_statement@121 (num_queries == 0 || buckets_per_query == 0)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ result->NumElements  [L122] if_statement@121 (num_queries == 0 || buckets_per_query == 0)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ alloc->Allocate  [L127] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ alloc->Allocate  [L128] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ Normalize  [L138] for_statement@135 q < num_queries → if_statement@137 (metric == MetricType::METRIC_TYPE_COSINE)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ norm_query.data  [L138] for_statement@135 q < num_queries → if_statement@137 (metric == MetricType::METRIC_TYPE_COSINE)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ std::numeric_limits<float>::infinity  [L145] for_statement@135 q < num_queries → for_statement@140 b < buckets_per_query → if_statement@143 (bucket_id == INVALID_BUCKET_ID)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ partition_strategy_->GetCentroid  [L148] for_statement@135 q < num_queries → for_statement@140 b < buckets_per_query
  │    │  ├─ 以下为分派/重载候选，并非全部依次执行
  │    │  #9 GNOIMIPartition::GetCentroid [src/algorithm/ivf/gno_imi_partition.cpp:440]
  │    │    ├─ VsagException  [L443] if_statement@442 (!is_trained_)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ VsagException  [L446] if_statement@445 (bucket_id >= bucket_count_)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ FP32Add  [L450] 函数本体；短路求值/提前返回见源码
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ data_centroids_s_.data  [L450] 函数本体；短路求值/提前返回见源码
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ data_centroids_t_.data  [L451] 函数本体；短路求值/提前返回见源码
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ centroid.data  [L452] 函数本体；短路求值/提前返回见源码
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │  #10 IVFNearestPartition::GetCentroid [src/algorithm/ivf/ivf_nearest_partition.cpp:286]
  │    │    ├─ VsagException  [L289] if_statement@288 (!is_trained_)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ VsagException  [L292] if_statement@291 (bucket_id >= bucket_count_)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ this->route_index_ptr_->GetCodeByInnerId  [L295] if_statement@294 (this->use_route_graph_)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ centroid.data  [L295] if_statement@294 (this->use_route_graph_)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ memcpy  [L297] if_statement@294 (this->use_route_graph_) [else 分支]
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ centroid.data  [L297] if_statement@294 (this->use_route_graph_) [else 分支]
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ this->centroids_.data  [L298] if_statement@294 (this->use_route_graph_) [else 分支]
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ Normalize  [L156] for_statement@135 q < num_queries → for_statement@140 b < buckets_per_query → if_statement@150 (metric == MetricType::METRIC_TYPE_L2SQR) [else 分支] → if_statement@155 (metric == MetricType::METRIC_TYPE_COSINE)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ centroid.data  [L156] for_statement@135 q < num_queries → for_statement@140 b < buckets_per_query → if_statement@150 (metric == MetricType::METRIC_TYPE_L2SQR) [else 分支] → if_statement@155 (metric == MetricType::METRIC_TYPE_COSINE)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ norm_centroid.data  [L156] for_statement@135 q < num_queries → for_statement@140 b < buckets_per_query → if_statement@150 (metric == MetricType::METRIC_TYPE_L2SQR) [else 分支] → if_statement@155 (metric == MetricType::METRIC_TYPE_COSINE)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ ctx.stats->AddDistance  [L170] for_statement@135 q < num_queries → for_statement@140 b < buckets_per_query → if_statement@169 (ctx.stats != nullptr)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ result->NumElements(num_queries) ->Dim(buckets_per_query) ->Ids(ids) ->Distances(distances) ->Owner  [L176] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ result->NumElements(num_queries) ->Dim(buckets_per_query) ->Ids(ids) ->Distances  [L176] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ result->NumElements(num_queries) ->Dim(buckets_per_query) ->Ids  [L176] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ result->NumElements(num_queries) ->Dim  [L176] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ result->NumElements  [L176] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ result->Statistics  [L573] if_statement@563 (param.disable_bucket_scan)
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ stats.Dump  [L573] if_statement@563 (param.disable_bucket_scan)
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ query->GetNumElements  [L577] if_statement@577 (query != nullptr && query->GetNumElements() > 1)
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ CHECK_ARGUMENT  [L578] if_statement@577 (query != nullptr && query->GetNumElements() > 1)
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ CHECK_ARGUMENT  [L579] if_statement@577 (query != nullptr && query->GetNumElements() > 1)
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ CHECK_ARGUMENT  [L581] if_statement@577 (query != nullptr && query->GetNumElements() > 1)
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ request.expected_labels_.empty  [L581] if_statement@577 (query != nullptr && query->GetNumElements() > 1)
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ CHECK_ARGUMENT  [L583] if_statement@577 (query != nullptr && query->GetNumElements() > 1)
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ CHECK_ARGUMENT  [L584] if_statement@577 (query != nullptr && query->GetNumElements() > 1)
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ query->GetFloat32Vectors  [L584] if_statement@577 (query != nullptr && query->GetNumElements() > 1)
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ CHECK_ARGUMENT  [L586] if_statement@577 (query != nullptr && query->GetNumElements() > 1)
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ query->GetDim  [L586] if_statement@577 (query != nullptr && query->GetNumElements() > 1)
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ query->GetNumElements  [L588] if_statement@577 (query != nullptr && query->GetNumElements() > 1)
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ select_query_allocator  [L590] if_statement@577 (query != nullptr && query->GetNumElements() > 1)
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ alloc->Allocate  [L591] if_statement@577 (query != nullptr && query->GetNumElements() > 1)
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ alloc->Allocate  [L592] if_statement@577 (query != nullptr && query->GetNumElements() > 1)
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ std::fill_n  [L593] if_statement@577 (query != nullptr && query->GetNumElements() > 1)
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ std::fill_n  [L594] if_statement@577 (query != nullptr && query->GetNumElements() > 1)
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ std::numeric_limits<float>::infinity  [L594] if_statement@577 (query != nullptr && query->GetNumElements() > 1)
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ query->GetFloat32Vectors  [L596] if_statement@577 (query != nullptr && query->GetNumElements() > 1)
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ base_request.expected_labels_.clear  [L598] if_statement@577 (query != nullptr && query->GetNumElements() > 1)
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ request.bucket_ids_.empty  [L599] if_statement@577 (query != nullptr && query->GetNumElements() > 1) → if_statement@599 (not request.bucket_ids_.empty())
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ base_request.bucket_ids_.clear  [L600] if_statement@577 (query != nullptr && query->GetNumElements() > 1) → if_statement@599 (not request.bucket_ids_.empty())
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ Dataset::Make  [L603] if_statement@577 (query != nullptr && query->GetNumElements() > 1) → lambda@602（定义体，执行时间取决于调用/调度）
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ one_query->NumElements(1) ->Dim(query->GetDim()) ->Float32Vectors(query_data + query_idx * query->GetDim()) ->Owner  [L604] if_statement@577 (query != nullptr && query->GetNumElements() > 1) → lambda@602（定义体，执行时间取决于调用/调度）
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ one_query->NumElements(1) ->Dim(query->GetDim()) ->Float32Vectors  [L604] if_statement@577 (query != nullptr && query->GetNumElements() > 1) → lambda@602（定义体，执行时间取决于调用/调度）
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ one_query->NumElements(1) ->Dim  [L604] if_statement@577 (query != nullptr && query->GetNumElements() > 1) → lambda@602（定义体，执行时间取决于调用/调度）
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ one_query->NumElements  [L604] if_statement@577 (query != nullptr && query->GetNumElements() > 1) → lambda@602（定义体，执行时间取决于调用/调度）
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ query->GetDim  [L605] if_statement@577 (query != nullptr && query->GetNumElements() > 1) → lambda@602（定义体，执行时间取决于调用/调度）
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ query->GetDim  [L606] if_statement@577 (query != nullptr && query->GetNumElements() > 1) → lambda@602（定义体，执行时间取决于调用/调度）
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ request.bucket_ids_.empty  [L611] if_statement@577 (query != nullptr && query->GetNumElements() > 1) → lambda@602（定义体，执行时间取决于调用/调度） → if_statement@611 (not request.bucket_ids_.empty())
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ JsonType::Parse  [L614] if_statement@577 (query != nullptr && query->GetNumElements() > 1) → lambda@602（定义体，执行时间取决于调用/调度）
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ json.Contains  [L615] if_statement@577 (query != nullptr && query->GetNumElements() > 1) → lambda@602（定义体，执行时间取决于调用/调度） → if_statement@615 (json.Contains("ivf"))
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ json["ivf"]["parallelism"].SetInt64  [L616] if_statement@577 (query != nullptr && query->GetNumElements() > 1) → lambda@602（定义体，执行时间取决于调用/调度） → if_statement@615 (json.Contains("ivf"))
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ json.Dump  [L618] if_statement@577 (query != nullptr && query->GetNumElements() > 1) → lambda@602（定义体，执行时间取决于调用/调度）
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ this->SearchWithRequest  [L619] if_statement@577 (query != nullptr && query->GetNumElements() > 1) → lambda@602（定义体，执行时间取决于调用/调度）
  │  ↳ 复用节点 #1 IVF::SearchWithRequest（本树前文已展开）
  ├─ std::min  [L620] if_statement@577 (query != nullptr && query->GetNumElements() > 1) → lambda@602（定义体，执行时间取决于调用/调度）
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ one_result->GetDim  [L620] if_statement@577 (query != nullptr && query->GetNumElements() > 1) → lambda@602（定义体，执行时间取决于调用/调度）
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ std::copy_n  [L622] if_statement@577 (query != nullptr && query->GetNumElements() > 1) → lambda@602（定义体，执行时间取决于调用/调度） → if_statement@621 (count > 0)
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ one_result->GetIds  [L622] if_statement@577 (query != nullptr && query->GetNumElements() > 1) → lambda@602（定义体，执行时间取决于调用/调度） → if_statement@621 (count > 0)
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ std::copy_n  [L623] if_statement@577 (query != nullptr && query->GetNumElements() > 1) → lambda@602（定义体，执行时间取决于调用/调度） → if_statement@621 (count > 0)
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ one_result->GetDistances  [L624] if_statement@577 (query != nullptr && query->GetNumElements() > 1) → lambda@602（定义体，执行时间取决于调用/调度） → if_statement@621 (count > 0)
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ this->thread_pool_->GeneralEnqueue  [L631] if_statement@577 (query != nullptr && query->GetNumElements() > 1) → if_statement@628 (this->thread_pool_ != nullptr and param.parallel_search_thread_count > 1) → for_statement@630 query_idx < num_queries
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ futures.emplace_back  [L632] if_statement@577 (query != nullptr && query->GetNumElements() > 1) → if_statement@628 (this->thread_pool_ != nullptr and param.parallel_search_thread_count > 1) → for_statement@630 query_idx < num_queries
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ std::move  [L632] if_statement@577 (query != nullptr && query->GetNumElements() > 1) → if_statement@628 (this->thread_pool_ != nullptr and param.parallel_search_thread_count > 1) → for_statement@630 query_idx < num_queries
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ future.get  [L635] if_statement@577 (query != nullptr && query->GetNumElements() > 1) → if_statement@628 (this->thread_pool_ != nullptr and param.parallel_search_thread_count > 1) → for_range_loop@634
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ search_func  [L639] if_statement@577 (query != nullptr && query->GetNumElements() > 1) → if_statement@628 (this->thread_pool_ != nullptr and param.parallel_search_thread_count > 1) [else 分支] → for_statement@638 query_idx < num_queries
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ Dataset::Make() ->NumElements(num_queries) ->Dim(request.topk_) ->Ids(ids) ->Distances(distances) ->Owner  [L642] if_statement@577 (query != nullptr && query->GetNumElements() > 1)
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ Dataset::Make() ->NumElements(num_queries) ->Dim(request.topk_) ->Ids(ids) ->Distances  [L642] if_statement@577 (query != nullptr && query->GetNumElements() > 1)
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ Dataset::Make() ->NumElements(num_queries) ->Dim(request.topk_) ->Ids  [L642] if_statement@577 (query != nullptr && query->GetNumElements() > 1)
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ Dataset::Make() ->NumElements(num_queries) ->Dim  [L642] if_statement@577 (query != nullptr && query->GetNumElements() > 1)
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ Dataset::Make() ->NumElements  [L642] if_statement@577 (query != nullptr && query->GetNumElements() > 1)
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ Dataset::Make  [L642] if_statement@577 (query != nullptr && query->GetNumElements() > 1)
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ result->Statistics  [L648] if_statement@577 (query != nullptr && query->GetNumElements() > 1)
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ stats.Dump  [L648] if_statement@577 (query != nullptr && query->GetNumElements() > 1)
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ AstParse  [L656] if_statement@652 (request.enable_attribute_filter_ and this->attr_filter_index_ != nullptr) → if_statement@654 (expression == nullptr)
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ Executor::MakeInstance  [L660] if_statement@652 (request.enable_attribute_filter_ and this->attr_filter_index_ != nullptr) → for_statement@658 i < param.parallel_search_thread_count
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ executor->Init  [L661] if_statement@652 (request.enable_attribute_filter_ and this->attr_filter_index_ != nullptr) → for_statement@658 i < param.parallel_search_thread_count
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ param.executors.emplace_back  [L662] if_statement@652 (request.enable_attribute_filter_ and this->attr_filter_index_ != nullptr) → for_statement@658 i < param.parallel_search_thread_count
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ request.expected_labels_.empty  [L666] if_statement@666 (not request.expected_labels_.empty())
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ std::make_shared<ReasoningContext>  [L667] if_statement@666 (not request.expected_labels_.empty())
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ reasoning_ctx->SetSearchParams  [L668] if_statement@666 (not request.expected_labels_.empty())
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ locations.reserve  [L675] if_statement@666 (not request.expected_labels_.empty())
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ request.expected_labels_.size  [L675] if_statement@666 (not request.expected_labels_.empty())
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ this->label_table_->TryGetIdByLabel  [L677] if_statement@666 (not request.expected_labels_.empty()) → for_range_loop@676
  │  #11 LabelTable::TryGetIdByLabel [src/impl/label_table/label_table.cpp:96]
  │    ├─ this->get_id_by_label_with_reverse_map  [L100] if_statement@99 (use_reverse_map_)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ this->get_id_by_label_with_label_table  [L102] if_statement@99 (use_reverse_map_) [else 分支]
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ this->deleted_ids_.count  [L109] if_statement@107 (not return_even_removed) → if_statement@109 (this->deleted_ids_.count(id) > 0)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ this->get_location  [L680] if_statement@666 (not request.expected_labels_.empty()) → for_range_loop@676 → if_statement@678 (success)
  │  #12 IVF::get_location [src/algorithm/ivf/ivf.cpp:312]
  ├─ locations.emplace_back  [L681] if_statement@666 (not request.expected_labels_.empty()) → for_range_loop@676 → if_statement@678 (success)
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ expected_labels_vec.reserve  [L687] if_statement@666 (not request.expected_labels_.empty())
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ request.expected_labels_.size  [L687] if_statement@666 (not request.expected_labels_.empty())
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ expected_labels_vec.push_back  [L689] if_statement@666 (not request.expected_labels_.empty()) → for_range_loop@688
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ reasoning_ctx->InitializeExpectedTargets  [L691] if_statement@666 (not request.expected_labels_.empty())
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ query->GetFloat32Vectors  [L693] if_statement@666 (not request.expected_labels_.empty())
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ this->bucket_->FactoryComputer  [L694] if_statement@666 (not request.expected_labels_.empty())
  │  #13 BucketDataCell<QuantTmpl, IOTmpl>::FactoryComputer [src/datacell/bucket_datacell.h:566]
  │    ├─ this->quantizer_->FactoryComputer  [L569] 函数本体；短路求值/提前返回见源码
  │    │  #14 Quantizer::FactoryComputer [src/quantization/quantizer.h:179]
  │    │    ├─ std::make_shared<Computer<QuantT>>  [L181] 函数本体；短路求值/提前返回见源码
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ std::static_pointer_cast<Computer<QuantTmpl>>  [L570] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ comp->raw_query_.resize  [L572] if_statement@571 (use_residual_)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ this->quantizer_->GetDim  [L572] if_statement@571 (use_residual_)
  │    │  #15 Quantizer::GetDim [src/quantization/quantizer.h:340]
  │    ├─ Normalize  [L574] if_statement@571 (use_residual_) → if_statement@573 (metric_ == MetricType::METRIC_TYPE_COSINE)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ comp->raw_query_.data  [L574] if_statement@571 (use_residual_) → if_statement@573 (metric_ == MetricType::METRIC_TYPE_COSINE)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ this->quantizer_->GetDim  [L574] if_statement@571 (use_residual_) → if_statement@573 (metric_ == MetricType::METRIC_TYPE_COSINE)
  │    │  ↳ 复用节点 #15 Quantizer::GetDim（本树前文已展开）
  │    ├─ memcpy  [L576] if_statement@571 (use_residual_) → if_statement@573 (metric_ == MetricType::METRIC_TYPE_COSINE) [else 分支]
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ comp->raw_query_.data  [L577] if_statement@571 (use_residual_) → if_statement@573 (metric_ == MetricType::METRIC_TYPE_COSINE) [else 分支]
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ this->quantizer_->GetDim  [L577] if_statement@571 (use_residual_) → if_statement@573 (metric_ == MetricType::METRIC_TYPE_COSINE) [else 分支]
  │    │  ↳ 复用节点 #15 Quantizer::GetDim（本树前文已展开）
  │    ├─ comp->raw_query_.data  [L579] if_statement@571 (use_residual_)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ comp->SetQuery  [L581] 函数本体；短路求值/提前返回见源码
  │    │  ├─ 以下为分派/重载候选，并非全部依次执行
  │    │  #16 Computer::SetQuery [src/quantization/computer.h:48]
  │    │    ├─ quantizer_->ProcessQuery  [L50] 函数本体；短路求值/提前返回见源码
  │    │    │  #17 Quantizer::ProcessQuery [src/quantization/quantizer.h:184]
  │    │    │    ├─ cast().ProcessQueryImpl  [L186] 函数本体；短路求值/提前返回见源码
  │    │    │    │  #18 FP32Quantizer<metric>::ProcessQueryImpl [src/quantization/fp32_quantizer.cpp:144]
  │    │    │    │    ├─ this->allocator_->Allocate  [L150] if_statement@148 (computer.buf_ == nullptr)
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ VsagException  [L154] catch_clause@152
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ Normalize  [L157] if_statement@156 (metric == MetricType::METRIC_TYPE_COSINE)
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ memcpy  [L159] if_statement@156 (metric == MetricType::METRIC_TYPE_COSINE) [else 分支]
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ cast  [L186] 函数本体；短路求值/提前返回见源码
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │  #19 Computer<TransformQuantizer<QuantImpl, metric>>::SetQuery [src/quantization/computer.h:122]
  │    │    ├─ quantizer_->ProcessQuery  [L124] 函数本体；短路求值/提前返回见源码
  │    │    │  ↳ 复用节点 #17 Quantizer::ProcessQuery（本树前文已展开）
  ├─ this->bucket_->QueryOneById  [L696] if_statement@666 (not request.expected_labels_.empty()) → for_range_loop@695
  │  #20 BucketDataCell::QueryOneById [src/datacell/bucket_datacell.h:71]
  │    ├─ std::static_pointer_cast<Computer<QuantTmpl>>  [L75] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ this->query_one_by_id  [L76] 函数本体；短路求值/提前返回见源码
  │    │  #21 BucketDataCell<QuantTmpl, IOTmpl>::query_one_by_id [src/datacell/bucket_datacell.h:341]
  │    │    ├─ VsagException  [L347] if_statement@346 (bucket_id >= this->bucket_count_ or bucket_id < 0)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ this->check_valid_bucket_id  [L350] 函数本体；短路求值/提前返回见源码
  │    │    │  #22 BucketDataCell::check_valid_bucket_id [src/datacell/bucket_datacell.h:244]
  │    │    │    ├─ VsagException  [L247] if_statement@246 (bucket_id >= this->bucket_count_ or bucket_id < 0)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ VsagException  [L352] if_statement@351 (offset_id >= this->bucket_sizes_[bucket_id])
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ VsagException  [L355] if_statement@354 (this->inner_ids_[bucket_id][offset_id] == EMPTY_INNER_ID)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ fmt::format  [L357] if_statement@354 (this->inner_ids_[bucket_id][offset_id] == EMPTY_INNER_ID)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ this->datas_[bucket_id].Acquire  [L362] 函数本体；短路求值/提前返回见源码
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ computer->ComputeDist  [L363] 函数本体；短路求值/提前返回见源码
  │    │    │  ├─ 以下为分派/重载候选，并非全部依次执行
  │    │    │  #23 Computer::ComputeDist [src/quantization/computer.h:53]
  │    │    │    ├─ quantizer_->ComputeDist  [L55] 函数本体；短路求值/提前返回见源码
  │    │    │    │  ├─ 以下为分派/重载候选，并非全部依次执行
  │    │    │    │  #24 Quantizer::ComputeDist [src/quantization/quantizer.h:189]
  │    │    │    │    ├─ cast().ComputeDistImpl  [L191] 函数本体；短路求值/提前返回见源码
  │    │    │    │    │  #25 FP32Quantizer<metric>::ComputeDistImpl [src/quantization/fp32_quantizer.cpp:164]
  │    │    │    │    │    ├─ FP32ComputeIP  [L169] if_statement@168 (metric == MetricType::METRIC_TYPE_IP)
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ FP32ComputeIP  [L173] if_statement@168 (metric == MetricType::METRIC_TYPE_IP) [else 分支] → if_statement@172 (metric == MetricType::METRIC_TYPE_COSINE)
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ FP32ComputeL2Sqr  [L182] if_statement@168 (metric == MetricType::METRIC_TYPE_IP) [else 分支] → if_statement@172 (metric == MetricType::METRIC_TYPE_COSINE) [else 分支] → if_statement@181 (metric == MetricType::METRIC_TYPE_L2SQR)
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ cast  [L191] 函数本体；短路求值/提前返回见源码
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │  #26 Quantizer::ComputeDist [src/quantization/quantizer.h:223]
  │    │    │    │    ├─ cast().ComputeDistImpl  [L226] 函数本体；短路求值/提前返回见源码
  │    │    │    │    │  ↳ 复用节点 #25 FP32Quantizer<metric>::ComputeDistImpl（本树前文已展开）
  │    │    │    │    ├─ cast  [L226] 函数本体；短路求值/提前返回见源码
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │  #27 Computer<TransformQuantizer<QuantImpl, metric>>::ComputeDist [src/quantization/computer.h:127]
  │    │    │    ├─ quantizer_->ComputeDist  [L129] 函数本体；短路求值/提前返回见源码
  │    │    │    │  ├─ 以下为分派/重载候选，并非全部依次执行
  │    │    │    │  ↳ 复用节点 #24 Quantizer::ComputeDist（本树前文已展开）
  │    │    │    │  ↳ 复用节点 #26 Quantizer::ComputeDist（本树前文已展开）
  │    │    ├─ lease.Data  [L363] 函数本体；短路求值/提前返回见源码
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ this->quantizer_->GetDim  [L366] if_statement@365 (use_residual_)
  │    │    │  ↳ 复用节点 #15 Quantizer::GetDim（本树前文已展开）
  │    │    ├─ strategy_->GetCentroid  [L367] if_statement@365 (use_residual_)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ FP32ComputeIP  [L369] if_statement@365 (use_residual_)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ computer->raw_query_.data  [L369] if_statement@365 (use_residual_)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ centroid.data  [L369] if_statement@365 (use_residual_)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ this->quantizer_->GetDim  [L369] if_statement@365 (use_residual_)
  │    │    │  ↳ 复用节点 #15 Quantizer::GetDim（本树前文已展开）
  ├─ ctx.stats->AddDistance  [L698] if_statement@666 (not request.expected_labels_.empty()) → for_range_loop@695 → if_statement@697 (ctx.stats != nullptr)
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ reasoning_ctx->SetTrueDistance  [L701] if_statement@666 (not request.expected_labels_.empty()) → for_range_loop@695
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ reasoning_ctx.get  [L703] if_statement@666 (not request.expected_labels_.empty())
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ search_with_custom_distance  [L710] if_statement@706 (use_custom_distance)
  │  #28 IVF::search_with_custom_distance [src/algorithm/ivf/ivf_search.cpp:334]
  │    ├─ query->GetFloat32Vectors  [L340] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ param.bucket_ids.empty  [L342] if_statement@342 (not param.bucket_ids.empty())
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ candidate_buckets.reserve  [L343] if_statement@342 (not param.bucket_ids.empty())
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ param.bucket_ids.size  [L343] if_statement@342 (not param.bucket_ids.empty())
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ candidate_buckets.push_back  [L345] if_statement@342 (not param.bucket_ids.empty()) → for_range_loop@344
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ partition_strategy_->ClassifyDatasForSearch  [L348] if_statement@342 (not param.bucket_ids.empty()) [else 分支]
  │    │  ├─ 以下为分派/重载候选，并非全部依次执行
  │    │  ↳ 复用节点 #6 GNOIMIPartition::ClassifyDatasForSearch（本树前文已展开）
  │    │  ↳ 复用节点 #8 IVFPartitionStrategy::ClassifyDatasForSearch（本树前文已展开）
  │    ├─ reasoning_ctx->RecordBucketSelection  [L351] if_statement@350 (reasoning_ctx != nullptr)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ CHECK_ARGUMENT  [L357] if_statement@356 (buckets_per_data_ > 1)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ std::numeric_limits<int64_t>::max  [L357] if_statement@356 (buckets_per_data_ > 1)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ DistanceHeap::MakeInstanceBySize<true, false>  [L362] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ std::min<uint64_t>  [L369] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ std::max<uint64_t>  [L370] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ this->GetNumElements  [L370] 函数本体；短路求值/提前返回见源码
  │    │  #29 IVF::GetNumElements [src/algorithm/ivf/ivf.cpp:291]
  │    ├─ candidate_ids.reserve  [L371] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ candidate_labels.reserve  [L372] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ scores.resize  [L373] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ param.time_cost->CheckOvertime  [L376] lambda@375（定义体，执行时间取决于调用/调度） → if_statement@376 (param.time_cost == nullptr or not param.time_cost->CheckOvertime())
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ ctx.stats->is_timeout.store  [L380] lambda@375（定义体，执行时间取决于调用/调度） → if_statement@379 (ctx.stats != nullptr)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ candidate_ids.empty  [L386] lambda@385（定义体，执行时间取决于调用/调度） → if_statement@386 (candidate_ids.empty())
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ is_timed_out  [L389] lambda@385（定义体，执行时间取决于调用/调度） → if_statement@389 (is_timed_out())
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ request.distance_batch_func_  [L392] lambda@385（定义体，执行时间取决于调用/调度）
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ candidate_labels.data  [L393] lambda@385（定义体，执行时间取决于调用/调度）
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ candidate_labels.size  [L393] lambda@385（定义体，执行时间取决于调用/调度）
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ scores.data  [L393] lambda@385（定义体，执行时间取决于调用/调度）
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ ctx.stats->AddDistance  [L395] lambda@385（定义体，执行时间取决于调用/调度） → if_statement@394 (ctx.stats != nullptr)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ candidate_ids.size  [L397] lambda@385（定义体，执行时间取决于调用/调度） → if_statement@394 (ctx.stats != nullptr)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ candidate_ids.size  [L399] lambda@385（定义体，执行时间取决于调用/调度） → for_statement@399 i < candidate_ids.size()
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ CHECK_ARGUMENT  [L400] lambda@385（定义体，执行时间取决于调用/调度） → for_statement@399 i < candidate_ids.size()
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ std::isfinite  [L400] lambda@385（定义体，执行时间取决于调用/调度） → for_statement@399 i < candidate_ids.size()
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ filter->CheckValid  [L403] lambda@385（定义体，执行时间取决于调用/调度） → for_statement@399 i < candidate_ids.size() → if_statement@403 (filter != nullptr and not filter->CheckValid(origin_id))
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ reasoning_ctx->RecordFilterReject  [L405] lambda@385（定义体，执行时间取决于调用/调度） → for_statement@399 i < candidate_ids.size() → if_statement@403 (filter != nullptr and not filter->CheckValid(origin_id)) → if_statement@404 (reasoning_ctx != nullptr)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ reasoning_ctx->RecordVisit  [L410] lambda@385（定义体，执行时间取决于调用/调度） → for_statement@399 i < candidate_ids.size() → if_statement@409 (reasoning_ctx != nullptr)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ search_result->Push  [L412] lambda@385（定义体，执行时间取决于调用/调度） → for_statement@399 i < candidate_ids.size()
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ search_result->Size  [L413] lambda@385（定义体，执行时间取决于调用/调度） → for_statement@399 i < candidate_ids.size() → while_statement@413 (search_result->Size() > static_cast<uint64_t>(topk))
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ reasoning_ctx->RecordEviction  [L415] lambda@385（定义体，执行时间取决于调用/调度） → for_statement@399 i < candidate_ids.size() → while_statement@413 (search_result->Size() > static_cast<uint64_t>(topk)) → if_statement@414 (reasoning_ctx != nullptr)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ search_result->Top  [L415] lambda@385（定义体，执行时间取决于调用/调度） → for_statement@399 i < candidate_ids.size() → while_statement@413 (search_result->Size() > static_cast<uint64_t>(topk)) → if_statement@414 (reasoning_ctx != nullptr)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ search_result->Pop  [L418] lambda@385（定义体，执行时间取决于调用/调度） → for_statement@399 i < candidate_ids.size() → while_statement@413 (search_result->Size() > static_cast<uint64_t>(topk))
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ candidate_ids.clear  [L421] lambda@385（定义体，执行时间取决于调用/调度）
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ candidate_labels.clear  [L422] lambda@385（定义体，执行时间取决于调用/调度）
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ is_timed_out  [L428] for_range_loop@427 → if_statement@428 (is_timed_out())
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ param.executors.empty  [L435] for_range_loop@427 → if_statement@435 (not param.executors.empty())
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ param.executors[0]->Clear  [L436] for_range_loop@427 → if_statement@435 (not param.executors.empty())
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ param.executors[0]->Run  [L437] for_range_loop@427 → if_statement@435 (not param.executors.empty())
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ bucket_->GetBucketSize  [L439] for_range_loop@427
  │    │  #30 BucketDataCell::GetBucketSize [src/datacell/bucket_datacell.h:180]
  │    │    ├─ check_valid_bucket_id  [L182] 函数本体；短路求值/提前返回见源码
  │    │    │  ↳ 复用节点 #22 BucketDataCell::check_valid_bucket_id（本树前文已展开）
  │    ├─ bucket_->GetInnerIds  [L440] for_range_loop@427
  │    │  #31 BucketDataCell::GetInnerIds [src/datacell/bucket_datacell.h:120]
  │    │    ├─ check_valid_bucket_id  [L122] 函数本体；短路求值/提前返回见源码
  │    │    │  ↳ 复用节点 #22 BucketDataCell::check_valid_bucket_id（本树前文已展开）
  │    │    ├─ this->inner_ids_[bucket_id].data  [L123] 函数本体；短路求值/提前返回见源码
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ std::numeric_limits<InnerIdType>::max  [L443] for_range_loop@427 → for_statement@441 offset < bucket_size → if_statement@443 (inner_id == std::numeric_limits<InnerIdType>::max())
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ attr_filter->CheckValid  [L447] for_range_loop@427 → for_statement@441 offset < bucket_size → if_statement@447 (attr_filter != nullptr and not attr_filter->CheckValid(offset))
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ reasoning_ctx->RecordFilterReject  [L449] for_range_loop@427 → for_statement@441 offset < bucket_size → if_statement@447 (attr_filter != nullptr and not attr_filter->CheckValid(offset)) → if_statement@448 (reasoning_ctx != nullptr)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ candidate_ids.push_back  [L453] for_range_loop@427 → for_statement@441 offset < bucket_size
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ candidate_labels.push_back  [L454] for_range_loop@427 → for_statement@441 offset < bucket_size
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ label_table_->GetLabelById  [L454] for_range_loop@427 → for_statement@441 offset < bucket_size
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ candidate_ids.size  [L455] for_range_loop@427 → for_statement@441 offset < bucket_size → if_statement@455 (candidate_ids.size() == batch_capacity and not submit_batch())
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ submit_batch  [L455] for_range_loop@427 → for_statement@441 offset < bucket_size → if_statement@455 (candidate_ids.size() == batch_capacity and not submit_batch())
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ submit_batch  [L465] if_statement@464 (not timed_out)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ search_result->Empty  [L473] while_statement@473 (not search_result->Empty())
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ search_result->Top  [L474] while_statement@473 (not search_result->Empty())
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ id_to_min_score.find  [L476] while_statement@473 (not search_result->Empty())
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ id_to_min_score.end  [L477] while_statement@473 (not search_result->Empty()) → if_statement@477 (iter == id_to_min_score.end() or score < iter->second)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ search_result->Pop  [L480] while_statement@473 (not search_result->Empty())
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ search_result->Push  [L484] for_range_loop@483
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ search_result->Size  [L485] for_range_loop@483 → if_statement@485 (search_result->Size() > static_cast<uint64_t>(origin_topk))
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ search_result->Pop  [L486] for_range_loop@483 → if_statement@485 (search_result->Size() > static_cast<uint64_t>(origin_topk))
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ reasoning_ctx.get  [L710] if_statement@706 (use_custom_distance)
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ filter_search_result_by_threshold  [L711] if_statement@706 (use_custom_distance)
  │  #32 InnerIndexInterface::filter_search_result_by_threshold [src/algorithm/inner_index_interface.cpp:1156]
  │    ├─ threshold.has_value  [L1160] if_statement@1160 (not threshold.has_value() or result == nullptr)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ valid_records.reserve  [L1164] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ result->Size  [L1164] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ result->Empty  [L1165] while_statement@1165 (not result->Empty())
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ result->Top  [L1166] while_statement@1165 (not result->Empty())
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ result->Pop  [L1167] while_statement@1165 (not result->Empty())
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ std::isfinite  [L1168] while_statement@1165 (not result->Empty()) → if_statement@1168 (std::isfinite(record.first) and record.first <= threshold.value())
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ threshold.value  [L1168] while_statement@1165 (not result->Empty()) → if_statement@1168 (std::isfinite(record.first) and record.first <= threshold.value())
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ valid_records.push_back  [L1169] while_statement@1165 (not result->Empty()) → if_statement@1168 (std::isfinite(record.first) and record.first <= threshold.value())
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ result->Push  [L1173] for_range_loop@1172
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ select_query_allocator  [L712] if_statement@706 (use_custom_distance)
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ search_result->Empty  [L713] if_statement@706 (use_custom_distance) → if_statement@713 (search_result == nullptr || search_result->Empty())
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ DatasetImpl::MakeEmptyDataset  [L714] if_statement@706 (use_custom_distance) → if_statement@713 (search_result == nullptr || search_result->Empty())
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ this->AttachReasoningReport  [L715] if_statement@706 (use_custom_distance) → if_statement@713 (search_result == nullptr || search_result->Empty())
  │  #33 IVF::AttachReasoningReport [src/algorithm/ivf/ivf_search.cpp:799]
  │    ├─ dataset_results->GetDim  [L805] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ dataset_results->GetIds  [L806] if_statement@806 (count > 0 and dataset_results->GetIds() != nullptr)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ this->label_table_->GetIdByLabel  [L812] if_statement@806 (count > 0 and dataset_results->GetIds() != nullptr) → for_statement@810 i < count
  │    │  #34 LabelTable::GetIdByLabel [src/impl/label_table/label_table.cpp:116]
  │    │    ├─ TryGetIdByLabel  [L118] 函数本体；短路求值/提前返回见源码
  │    │    │  ↳ 复用节点 #11 LabelTable::TryGetIdByLabel（本树前文已展开）
  │    │    ├─ VsagException  [L120] if_statement@119 (not success)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ fmt::format  [L121] if_statement@119 (not success)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ dataset_results->GetIds  [L812] if_statement@806 (count > 0 and dataset_results->GetIds() != nullptr) → for_statement@810 i < count
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ reasoning_ctx->MarkResult  [L815] if_statement@806 (count > 0 and dataset_results->GetIds() != nullptr)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ reasoning_ctx->DiagnoseExpectedTargets  [L817] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ dataset_results->Reasoning  [L818] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ reasoning_ctx->GenerateReport  [L818] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ reasoning_ctx.get  [L715] if_statement@706 (use_custom_distance) → if_statement@713 (search_result == nullptr || search_result->Empty())
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ dataset_results->Statistics  [L716] if_statement@706 (use_custom_distance) → if_statement@713 (search_result == nullptr || search_result->Empty())
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ stats.Dump  [L716] if_statement@706 (use_custom_distance) → if_statement@713 (search_result == nullptr || search_result->Empty())
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ this->pack_knn_result  [L719] if_statement@706 (use_custom_distance)
  │  #35 InnerIndexInterface::pack_knn_result [src/algorithm/inner_index_interface.cpp:1140]
  │    ├─ heap->Empty  [L1142] if_statement@1142 (heap == nullptr || heap->Empty())
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ make_empty_result  [L1143] if_statement@1142 (heap == nullptr || heap->Empty())
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ heap->Size  [L1146] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ create_fast_dataset  [L1147] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ heap->Top  [L1149] for_statement@1148 j >= 0
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ this->label_table_->GetLabelById  [L1150] for_statement@1148 j >= 0
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ heap->Top  [L1150] for_statement@1148 j >= 0
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ heap->Pop  [L1151] for_statement@1148 j >= 0
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ std::move  [L1153] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ this->AttachReasoningReport  [L720] if_statement@706 (use_custom_distance)
  │  ↳ 复用节点 #33 IVF::AttachReasoningReport（本树前文已展开）
  ├─ reasoning_ctx.get  [L720] if_statement@706 (use_custom_distance)
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ dataset_results->Statistics  [L721] if_statement@706 (use_custom_distance)
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ stats.Dump  [L721] if_statement@706 (use_custom_distance)
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ CHECK_ARGUMENT  [L730] if_statement@725 (is_range) → if_statement@729 (use_reorder_ and param.enable_reorder and request.limited_size_ > 0)
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ fmt::format  [L731] if_statement@725 (is_range) → if_statement@729 (use_reorder_ and param.enable_reorder and request.limited_size_ > 0)
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ this->search<RANGE_SEARCH>  [L736] if_statement@725 (is_range)
  │  #36 IVF::search [src/algorithm/ivf/ivf_search.cpp:199]
  │    ├─ query->GetFloat32Vectors  [L204] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ param.bucket_ids.empty  [L206] if_statement@206 (not param.bucket_ids.empty())
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ candidate_buckets.reserve  [L207] if_statement@206 (not param.bucket_ids.empty())
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ param.bucket_ids.size  [L207] if_statement@206 (not param.bucket_ids.empty())
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ candidate_buckets.push_back  [L209] if_statement@206 (not param.bucket_ids.empty()) → for_range_loop@208
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ partition_strategy_->ClassifyDatasForSearch  [L212] if_statement@206 (not param.bucket_ids.empty()) [else 分支]
  │    │  ├─ 以下为分派/重载候选，并非全部依次执行
  │    │  ↳ 复用节点 #6 GNOIMIPartition::ClassifyDatasForSearch（本树前文已展开）
  │    │  ↳ 复用节点 #8 IVFPartitionStrategy::ClassifyDatasForSearch（本树前文已展开）
  │    ├─ reasoning_ctx->RecordBucketSelection  [L215] if_statement@214 (reasoning_ctx != nullptr)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ bucket_->FactoryComputer  [L217] 函数本体；短路求值/提前返回见源码
  │    │  ↳ 复用节点 #13 BucketDataCell<QuantTmpl, IOTmpl>::FactoryComputer（本树前文已展开）
  │    ├─ this->GetNumElements  [L223] if_statement@220 (mode == RANGE_SEARCH) → if_statement@222 (topk < 0)
  │    │  ↳ 复用节点 #29 IVF::GetNumElements（本树前文已展开）
  │    ├─ std::numeric_limits<int64_t>::max  [L229] if_statement@228 (buckets_per_data_ > 1) → if_statement@229 (topk <= std::numeric_limits<int64_t>::max() / buckets_per_data_)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ std::numeric_limits<int64_t>::max  [L232] if_statement@228 (buckets_per_data_ > 1) → if_statement@229 (topk <= std::numeric_limits<int64_t>::max() / buckets_per_data_) [else 分支]
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ candidate_buckets.size  [L238] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ DistanceHeap::MakeInstanceBySize<true, false>  [L246] lambda@245（定义体，执行时间取决于调用/调度）
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ cur_bucket_num.fetch_add  [L249] lambda@245（定义体，执行时间取决于调用/调度）
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ cur_bucket_num.fetch_add  [L250] lambda@245（定义体，执行时间取决于调用/调度） → for_statement@250 i < bucket_count
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ param.time_cost->CheckOvertime  [L251] lambda@245（定义体，执行时间取决于调用/调度） → for_statement@250 i < bucket_count → if_statement@251 (param.time_cost != nullptr and param.time_cost->CheckOvertime() and ctx.stats != nullptr)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ ctx.stats->is_timeout.store  [L253] lambda@245（定义体，执行时间取决于调用/调度） → for_statement@250 i < bucket_count → if_statement@251 (param.time_cost != nullptr and param.time_cost->CheckOvertime() and ctx.stats != nullptr)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ bucket_searcher_->Search  [L260] lambda@245（定义体，执行时间取决于调用/调度） → for_statement@250 i < bucket_count
  │    │  ├─ 以下为分派/重载候选，并非全部依次执行
  │    │  #37 FlatBucketSearcher::Search [src/algorithm/ivf/flat_bucket_searcher.cpp:26]
  │    │    ├─ bucket->GetBucketSize  [L37] 函数本体；短路求值/提前返回见源码
  │    │    │  ↳ 复用节点 #30 BucketDataCell::GetBucketSize（本树前文已展开）
  │    │    ├─ bucket->GetInnerIds  [L38] 函数本体；短路求值/提前返回见源码
  │    │    │  ↳ 复用节点 #31 BucketDataCell::GetInnerIds（本树前文已展开）
  │    │    ├─ dist.size  [L39] if_statement@39 (bucket_size > static_cast<int64_t>(dist.size()))
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ dist.resize  [L40] if_statement@39 (bucket_size > static_cast<int64_t>(dist.size()))
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ bucket->ScanBucketById  [L43] 函数本体；短路求值/提前返回见源码
  │    │    │  #38 BucketDataCell::ScanBucketById [src/datacell/bucket_datacell.h:63]
  │    │    │    ├─ computer.get  [L67] 函数本体；短路求值/提前返回见源码
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ this->scan_bucket_by_id  [L68] 函数本体；短路求值/提前返回见源码
  │    │    │    │  #39 BucketDataCell<QuantTmpl, IOTmpl>::scan_bucket_by_id [src/datacell/bucket_datacell.h:522]
  │    │    │    │    ├─ VsagException  [L527] if_statement@526 (bucket_id >= this->bucket_count_ or bucket_id < 0)
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ this->check_valid_bucket_id  [L532] 函数本体；短路求值/提前返回见源码
  │    │    │    │    │  ↳ 复用节点 #22 BucketDataCell::check_valid_bucket_id（本树前文已展开）
  │    │    │    │    ├─ std::min  [L535] while_statement@534 (data_count > 0)
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ this->datas_[bucket_id].Acquire  [L537] while_statement@534 (data_count > 0)
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ computer->ScanBatchDists  [L538] while_statement@534 (data_count > 0)
  │    │    │    │    │  ├─ 以下为分派/重载候选，并非全部依次执行
  │    │    │    │    │  #40 Computer::ScanBatchDists [src/quantization/computer.h:68]
  │    │    │    │    │    ├─ quantizer_->ScanBatchDists  [L70] 函数本体；短路求值/提前返回见源码
  │    │    │    │    │    │  #41 Quantizer::ScanBatchDists [src/quantization/quantizer.h:230]
  │    │    │    │    │    │    ├─ cast().ScanBatchDistImpl  [L235] 函数本体；短路求值/提前返回见源码
  │    │    │    │    │    │    │  ├─ 以下为分派/重载候选，并非全部依次执行
  │    │    │    │    │    │    │  #42 Quantizer::ScanBatchDistImpl [src/quantization/quantizer.h:290]
  │    │    │    │    │    │    │    ├─ cast().ComputeDistImpl  [L296] for_statement@295 i < count
  │    │    │    │    │    │    │    │  ↳ 复用节点 #25 FP32Quantizer<metric>::ComputeDistImpl（本树前文已展开）
  │    │    │    │    │    │    │    ├─ cast  [L296] for_statement@295 i < count
  │    │    │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    │    │  #43 FP32Quantizer<metric>::ScanBatchDistImpl [src/quantization/fp32_quantizer.cpp:132]
  │    │    │    │    │    │    │    ├─ this->ComputeDistImpl  [L139] for_statement@138 i < count
  │    │    │    │    │    │    │    │  ↳ 复用节点 #25 FP32Quantizer<metric>::ComputeDistImpl（本树前文已展开）
  │    │    │    │    │    │    ├─ cast  [L235] 函数本体；短路求值/提前返回见源码
  │    │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │  #44 Computer<TransformQuantizer<QuantImpl, metric>>::ScanBatchDists [src/quantization/computer.h:142]
  │    │    │    │    │    ├─ quantizer_->ScanBatchDists  [L144] 函数本体；短路求值/提前返回见源码
  │    │    │    │    │    │  ↳ 复用节点 #41 Quantizer::ScanBatchDists（本树前文已展开）
  │    │    │    │    ├─ lease.Data  [L538] while_statement@534 (data_count > 0)
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ this->quantizer_->GetDim  [L544] 函数本体；短路求值/提前返回见源码
  │    │    │    │    │  ↳ 复用节点 #15 Quantizer::GetDim（本树前文已展开）
  │    │    │    │    ├─ strategy_->GetCentroid  [L546] if_statement@545 (use_residual_)
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ FP32ComputeIP  [L548] if_statement@545 (use_residual_)
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ computer->raw_query_.data  [L548] if_statement@545 (use_residual_)
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ centroid.data  [L548] if_statement@545 (use_residual_)
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ this->quantizer_->GetDim  [L548] if_statement@545 (use_residual_)
  │    │    │    │    │  ↳ 复用节点 #15 Quantizer::GetDim（本树前文已展开）
  │    │    │    │    ├─ FP32Sub  [L551] if_statement@545 (use_residual_) → if_statement@549 (metric_ == MetricType::METRIC_TYPE_L2SQR)
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ residual_bias_[bucket_id].data  [L551] if_statement@545 (use_residual_) → if_statement@549 (metric_ == MetricType::METRIC_TYPE_L2SQR)
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ std::numeric_limits<float>::max  [L560] for_statement@558 i < offset → if_statement@559 (this->inner_ids_[bucket_id][i] == EMPTY_INNER_ID)
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ dist.data  [L43] 函数本体；短路求值/提前返回见源码
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ param.query_context->stats->AddDistance  [L46] if_statement@44 (param.query_context != nullptr and param.query_context->stats != nullptr and bucket_size > 0)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ param.executors.size  [L53] if_statement@53 (thread_id >= 0 and param.executors.size() > static_cast<uint64_t>(thread_id))
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ param.executors[tid]->Clear  [L56] if_statement@53 (thread_id >= 0 and param.executors.size() > static_cast<uint64_t>(thread_id)) → if_statement@55 (param.executors[tid] != nullptr)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ param.executors[tid]->Run  [L57] if_statement@53 (thread_id >= 0 and param.executors.size() > static_cast<uint64_t>(thread_id)) → if_statement@55 (param.executors[tid] != nullptr)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ std::numeric_limits<float>::max  [L63] 函数本体；短路求值/提前返回见源码
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ heap->Empty  [L64] if_statement@64 (not heap->Empty() and heap->Size() == topk_u)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ heap->Size  [L64] if_statement@64 (not heap->Empty() and heap->Size() == topk_u)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ heap->Top  [L65] if_statement@64 (not heap->Empty() and heap->Size() == topk_u)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ std::numeric_limits<InnerIdType>::max  [L70] if_statement@68 (param.search_mode == KNN_SEARCH) → for_statement@69 j < bucket_size → if_statement@70 (ids[j] == std::numeric_limits<InnerIdType>::max())
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ reasoning_ctx->RecordVisit  [L75] if_statement@68 (param.search_mode == KNN_SEARCH) → for_statement@69 j < bucket_size → if_statement@74 (reasoning_ctx != nullptr)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ param.distance_threshold.has_value  [L77] if_statement@68 (param.search_mode == KNN_SEARCH) → for_statement@69 j < bucket_size → if_statement@77 (param.distance_threshold.has_value() and (not std::isfinite(dist[j]) or (not param.enable_reorder and dist[j] > param.distance_threshold.value())))
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ std::isfinite  [L78] if_statement@68 (param.search_mode == KNN_SEARCH) → for_statement@69 j < bucket_size → if_statement@77 (param.distance_threshold.has_value() and (not std::isfinite(dist[j]) or (not param.enable_reorder and dist[j] > param.distance_threshold.value())))
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ param.distance_threshold.value  [L79] if_statement@68 (param.search_mode == KNN_SEARCH) → for_statement@69 j < bucket_size → if_statement@77 (param.distance_threshold.has_value() and (not std::isfinite(dist[j]) or (not param.enable_reorder and dist[j] > param.distance_threshold.value())))
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ attr_ft->CheckValid  [L82] if_statement@68 (param.search_mode == KNN_SEARCH) → for_statement@69 j < bucket_size → if_statement@82 (attr_ft != nullptr and not attr_ft->CheckValid(j))
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ reasoning_ctx->RecordFilterReject  [L84] if_statement@68 (param.search_mode == KNN_SEARCH) → for_statement@69 j < bucket_size → if_statement@82 (attr_ft != nullptr and not attr_ft->CheckValid(j)) → if_statement@83 (reasoning_ctx != nullptr)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ ft->CheckValid  [L88] if_statement@68 (param.search_mode == KNN_SEARCH) → for_statement@69 j < bucket_size → if_statement@88 (ft == nullptr or ft->CheckValid(origin_id))
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ heap->Size  [L89] if_statement@68 (param.search_mode == KNN_SEARCH) → for_statement@69 j < bucket_size → if_statement@88 (ft == nullptr or ft->CheckValid(origin_id)) → if_statement@89 (heap->Size() < topk_u or dist[j] < cur_heap_top)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ heap->Push  [L90] if_statement@68 (param.search_mode == KNN_SEARCH) → for_statement@69 j < bucket_size → if_statement@88 (ft == nullptr or ft->CheckValid(origin_id)) → if_statement@89 (heap->Size() < topk_u or dist[j] < cur_heap_top)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ heap->Size  [L92] if_statement@68 (param.search_mode == KNN_SEARCH) → for_statement@69 j < bucket_size → if_statement@88 (ft == nullptr or ft->CheckValid(origin_id)) → while_statement@92 (heap->Size() > topk_u)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ reasoning_ctx->RecordEviction  [L94] if_statement@68 (param.search_mode == KNN_SEARCH) → for_statement@69 j < bucket_size → if_statement@88 (ft == nullptr or ft->CheckValid(origin_id)) → while_statement@92 (heap->Size() > topk_u) → if_statement@93 (reasoning_ctx != nullptr)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ heap->Top  [L94] if_statement@68 (param.search_mode == KNN_SEARCH) → for_statement@69 j < bucket_size → if_statement@88 (ft == nullptr or ft->CheckValid(origin_id)) → while_statement@92 (heap->Size() > topk_u) → if_statement@93 (reasoning_ctx != nullptr)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ heap->Pop  [L96] if_statement@68 (param.search_mode == KNN_SEARCH) → for_statement@69 j < bucket_size → if_statement@88 (ft == nullptr or ft->CheckValid(origin_id)) → while_statement@92 (heap->Size() > topk_u)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ heap->Empty  [L98] if_statement@68 (param.search_mode == KNN_SEARCH) → for_statement@69 j < bucket_size → if_statement@88 (ft == nullptr or ft->CheckValid(origin_id)) → if_statement@98 (not heap->Empty() and heap->Size() == topk_u)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ heap->Size  [L98] if_statement@68 (param.search_mode == KNN_SEARCH) → for_statement@69 j < bucket_size → if_statement@88 (ft == nullptr or ft->CheckValid(origin_id)) → if_statement@98 (not heap->Empty() and heap->Size() == topk_u)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ heap->Top  [L99] if_statement@68 (param.search_mode == KNN_SEARCH) → for_statement@69 j < bucket_size → if_statement@88 (ft == nullptr or ft->CheckValid(origin_id)) → if_statement@98 (not heap->Empty() and heap->Size() == topk_u)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ reasoning_ctx->RecordFilterReject  [L102] if_statement@68 (param.search_mode == KNN_SEARCH) → for_statement@69 j < bucket_size → if_statement@88 (ft == nullptr or ft->CheckValid(origin_id)) [else 分支] → if_statement@101 (reasoning_ctx != nullptr)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ std::numeric_limits<InnerIdType>::max  [L107] if_statement@68 (param.search_mode == KNN_SEARCH) [else 分支] → for_statement@106 j < bucket_size → if_statement@107 (ids[j] == std::numeric_limits<InnerIdType>::max())
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ reasoning_ctx->RecordVisit  [L112] if_statement@68 (param.search_mode == KNN_SEARCH) [else 分支] → for_statement@106 j < bucket_size → if_statement@111 (reasoning_ctx != nullptr)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ attr_ft->CheckValid  [L114] if_statement@68 (param.search_mode == KNN_SEARCH) [else 分支] → for_statement@106 j < bucket_size → if_statement@114 (attr_ft != nullptr and not attr_ft->CheckValid(j))
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ reasoning_ctx->RecordFilterReject  [L116] if_statement@68 (param.search_mode == KNN_SEARCH) [else 分支] → for_statement@106 j < bucket_size → if_statement@114 (attr_ft != nullptr and not attr_ft->CheckValid(j)) → if_statement@115 (reasoning_ctx != nullptr)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ ft->CheckValid  [L120] if_statement@68 (param.search_mode == KNN_SEARCH) [else 分支] → for_statement@106 j < bucket_size → if_statement@120 (ft == nullptr or ft->CheckValid(origin_id))
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ heap->Push  [L122] if_statement@68 (param.search_mode == KNN_SEARCH) [else 分支] → for_statement@106 j < bucket_size → if_statement@120 (ft == nullptr or ft->CheckValid(origin_id)) → if_statement@121 (dist[j] <= param.radius + THRESHOLD_ERROR and dist[j] < cur_heap_top)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ heap->Size  [L124] if_statement@68 (param.search_mode == KNN_SEARCH) [else 分支] → for_statement@106 j < bucket_size → if_statement@120 (ft == nullptr or ft->CheckValid(origin_id)) → while_statement@124 (heap->Size() > topk_u)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ reasoning_ctx->RecordEviction  [L126] if_statement@68 (param.search_mode == KNN_SEARCH) [else 分支] → for_statement@106 j < bucket_size → if_statement@120 (ft == nullptr or ft->CheckValid(origin_id)) → while_statement@124 (heap->Size() > topk_u) → if_statement@125 (reasoning_ctx != nullptr)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ heap->Top  [L126] if_statement@68 (param.search_mode == KNN_SEARCH) [else 分支] → for_statement@106 j < bucket_size → if_statement@120 (ft == nullptr or ft->CheckValid(origin_id)) → while_statement@124 (heap->Size() > topk_u) → if_statement@125 (reasoning_ctx != nullptr)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ heap->Pop  [L128] if_statement@68 (param.search_mode == KNN_SEARCH) [else 分支] → for_statement@106 j < bucket_size → if_statement@120 (ft == nullptr or ft->CheckValid(origin_id)) → while_statement@124 (heap->Size() > topk_u)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ heap->Empty  [L130] if_statement@68 (param.search_mode == KNN_SEARCH) [else 分支] → for_statement@106 j < bucket_size → if_statement@120 (ft == nullptr or ft->CheckValid(origin_id)) → if_statement@130 (not heap->Empty() and heap->Size() == topk_u)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ heap->Size  [L130] if_statement@68 (param.search_mode == KNN_SEARCH) [else 分支] → for_statement@106 j < bucket_size → if_statement@120 (ft == nullptr or ft->CheckValid(origin_id)) → if_statement@130 (not heap->Empty() and heap->Size() == topk_u)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ heap->Top  [L131] if_statement@68 (param.search_mode == KNN_SEARCH) [else 分支] → for_statement@106 j < bucket_size → if_statement@120 (ft == nullptr or ft->CheckValid(origin_id)) → if_statement@130 (not heap->Empty() and heap->Size() == topk_u)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ reasoning_ctx->RecordFilterReject  [L134] if_statement@68 (param.search_mode == KNN_SEARCH) [else 分支] → for_statement@106 j < bucket_size → if_statement@120 (ft == nullptr or ft->CheckValid(origin_id)) [else 分支] → if_statement@133 (reasoning_ctx != nullptr)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │  #45 GraphBucketSearcher::Search [src/algorithm/ivf/graph_bucket_searcher.cpp:36]
  │    │    ├─ bucket->GetBucketSize  [L47] 函数本体；短路求值/提前返回见源码
  │    │    │  ↳ 复用节点 #30 BucketDataCell::GetBucketSize（本树前文已展开）
  │    │    ├─ bucket_graphs_.size  [L48] 函数本体；短路求值/提前返回见源码
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ bucket_graphs_[bucket_id]->TotalCount  [L51] 函数本体；短路求值/提前返回见源码
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ search_graph  [L54] if_statement@53 (graph_fresh && bucket_size >= graph_build_threshold_)
  │    │    │  #46 GraphBucketSearcher::search_graph [src/algorithm/ivf/graph_bucket_searcher.cpp:77]
  │    │    │    ├─ bucket->GetBucketSize  [L87] 函数本体；短路求值/提前返回见源码
  │    │    │    │  ↳ 复用节点 #30 BucketDataCell::GetBucketSize（本树前文已展开）
  │    │    │    ├─ bucket->GetInnerIds  [L92] 函数本体；短路求值/提前返回见源码
  │    │    │    │  ↳ 复用节点 #31 BucketDataCell::GetInnerIds（本树前文已展开）
  │    │    │    ├─ std::numeric_limits<InnerIdType>::max  [L94] while_statement@94 (entry < bucket_size && ids[entry] == std::numeric_limits<InnerIdType>::max())
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ param.executors.empty  [L102] if_statement@102 (not param.executors.empty() && static_cast<uint64_t>(thread_id) < param.executors.size() && param.executors[thread_id] != nullptr)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ param.executors.size  [L102] if_statement@102 (not param.executors.empty() && static_cast<uint64_t>(thread_id) < param.executors.size() && param.executors[thread_id] != nullptr)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ param.executors[thread_id]->Clear  [L104] if_statement@102 (not param.executors.empty() && static_cast<uint64_t>(thread_id) < param.executors.size() && param.executors[thread_id] != nullptr)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ param.executors[thread_id]->Run  [L105] if_statement@102 (not param.executors.empty() && static_cast<uint64_t>(thread_id) < param.executors.size() && param.executors[thread_id] != nullptr)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ std::numeric_limits<uint64_t>::max  [L109] 函数本体；短路求值/提前返回见源码
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ CHECK_ARGUMENT  [L111] if_statement@110 (search_param.search_mode == KNN_SEARCH)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ std::max  [L113] if_statement@110 (search_param.search_mode == KNN_SEARCH)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ std::min<uint64_t>  [L117] 函数本体；短路求值/提前返回见源码
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ std::min<int64_t>  [L123] if_statement@119 (search_param.search_mode == RANGE_SEARCH) → conditional_expression@123 topk > 0
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ std::numeric_limits<int>::max  [L123] if_statement@119 (search_param.search_mode == RANGE_SEARCH) → conditional_expression@123 topk > 0
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ std::make_shared<VisitedList>  [L130] 函数本体；短路求值/提前返回见源码
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ searcher.Search  [L135] 函数本体；短路求值/提前返回见源码
  │    │    │    │  ├─ 以下为分派/重载候选，并非全部依次执行
  │    │    │    │  #47 BasicSearcher::Search [src/impl/searcher/basic_searcher.cpp:76]
  │    │    │    │    ├─ this->search_impl<KNN_SEARCH>  [L86] if_statement@85 (inner_search_param.search_mode == KNN_SEARCH)
  │    │    │    │    │  ├─ 以下为分派/重载候选，并非全部依次执行
  │    │    │    │    │  #48 BasicSearcher::search_impl [src/impl/searcher/basic_searcher.cpp:174]
  │    │    │    │    │    ├─ select_query_allocator  [L181] 函数本体；短路求值/提前返回见源码
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ std::make_shared<StandardHeap<true, false>>  [L182] 函数本体；短路求值/提前返回见源码
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ std::make_shared<StandardHeap<true, false>>  [L183] 函数本体；短路求值/提前返回见源码
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ distance_provider.OriginalId  [L188] lambda@187（定义体，执行时间取决于调用/调度）
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ distance_provider.IsValid  [L189] lambda@187（定义体，执行时间取决于调用/调度）
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ inner_search_param.is_inner_id_allowed->CheckValid  [L191] lambda@187（定义体，执行时间取决于调用/调度）
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ attr_filter->CheckValid  [L192] lambda@187（定义体，执行时间取决于调用/调度）
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ distance_provider.QueryDistance  [L197] 函数本体；短路求值/提前返回见源码
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ reasoning->RecordVisit  [L201] if_statement@200 (reasoning != nullptr)
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ distance_provider.OriginalId  [L201] if_statement@200 (reasoning != nullptr)
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ check_func  [L203] if_statement@203 (check_func(ep))
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ is_result_distance_eligible<mode>  [L204] if_statement@203 (check_func(ep)) → if_statement@204 (is_result_distance_eligible<mode>(dist, inner_search_param))
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ top_candidates->Push  [L205] if_statement@203 (check_func(ep)) → if_statement@204 (is_result_distance_eligible<mode>(dist, inner_search_param))
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ reasoning->RecordFilterReject  [L208] if_statement@203 (check_func(ep)) [else 分支] → if_statement@207 (reasoning != nullptr)
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ distance_provider.OriginalId  [L208] if_statement@203 (check_func(ep)) [else 分支] → if_statement@207 (reasoning != nullptr)
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ top_candidates->Empty  [L211] if_statement@210 (mode == InnerSearchMode::RANGE_SEARCH) → if_statement@211 (dist > inner_search_param.radius + THRESHOLD_ERROR && not top_candidates->Empty())
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ top_candidates->Pop  [L212] if_statement@210 (mode == InnerSearchMode::RANGE_SEARCH) → if_statement@211 (dist > inner_search_param.radius + THRESHOLD_ERROR && not top_candidates->Empty())
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ candidate_set->Push  [L215] 函数本体；短路求值/提前返回见源码
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ traversal_priority  [L215] 函数本体；短路求值/提前返回见源码
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ vl->Set  [L216] 函数本体；短路求值/提前返回见源码
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ top_candidates->Empty  [L218] conditional_expression@218 top_candidates->Empty()
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ std::numeric_limits<float>::max  [L218] conditional_expression@218 top_candidates->Empty()
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ top_candidates->Top  [L218] conditional_expression@218 top_candidates->Empty()
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ graph->MaximumDegree  [L219] 函数本体；短路求值/提前返回见源码
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ graph->MaximumDegree  [L220] 函数本体；短路求值/提前返回见源码
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ graph->MaximumDegree  [L221] 函数本体；短路求值/提前返回见源码
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ candidate_set->Empty  [L222] while_statement@222 (not candidate_set->Empty())
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ candidate_set->Top  [L228] while_statement@222 (not candidate_set->Empty()) → if_statement@227 (mode == InnerSearchMode::KNN_SEARCH) → if_statement@228 (-candidate_set->Top().first > lower_bound && top_candidates->Size() >= ef)
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ top_candidates->Size  [L228] while_statement@222 (not candidate_set->Empty()) → if_statement@227 (mode == InnerSearchMode::KNN_SEARCH) → if_statement@228 (-candidate_set->Top().first > lower_bound && top_candidates->Size() >= ef)
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ candidate_set->Top  [L232] while_statement@222 (not candidate_set->Empty())
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ candidate_set->Pop  [L233] while_statement@222 (not candidate_set->Empty())
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ candidate_set->Empty  [L234] while_statement@222 (not candidate_set->Empty()) → if_statement@234 (not candidate_set->Empty())
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ graph->Prefetch  [L235] while_statement@222 (not candidate_set->Empty()) → if_statement@234 (not candidate_set->Empty())
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ candidate_set->Top  [L235] while_statement@222 (not candidate_set->Empty()) → if_statement@234 (not candidate_set->Empty())
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ visit  [L238] while_statement@222 (not candidate_set->Empty())
  │    │    │    │    │    │  #49 BasicSearcher::visit [src/impl/searcher/basic_searcher.cpp:43]
  │    │    │    │    │    │    ├─ graph->GetNeighbors  [L55] if_statement@53 (this->mutex_array_ != nullptr)
  │    │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    │    ├─ graph->GetNeighbors  [L57] if_statement@53 (this->mutex_array_ != nullptr) [else 分支]
  │    │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    │    ├─ neighbors.size  [L60] for_statement@60 i < neighbors.size()
  │    │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    │    ├─ neighbors.size  [L61] for_statement@60 i < neighbors.size() → if_statement@61 (i + prefetch_stride_visit_ < neighbors.size())
  │    │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    │    ├─ vl->Prefetch  [L62] for_statement@60 i < neighbors.size() → if_statement@61 (i + prefetch_stride_visit_ < neighbors.size())
  │    │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    │    ├─ vl->Get  [L64] for_statement@60 i < neighbors.size() → if_statement@64 (not vl->Get(neighbors[i]))
  │    │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    │    ├─ vl->Set  [L65] for_statement@60 i < neighbors.size() → if_statement@64 (not vl->Get(neighbors[i]))
  │    │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    │    ├─ skip_strategy->ShouldVisit  [L67] for_statement@60 i < neighbors.size() → if_statement@64 (not vl->Get(neighbors[i])) → if_statement@66 (not filter || count_no_visited == 0 || skip_strategy == nullptr || skip_strategy->ShouldVisit() || filter->CheckValid(neighbors[i]))
  │    │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    │    ├─ filter->CheckValid  [L67] for_statement@60 i < neighbors.size() → if_statement@64 (not vl->Get(neighbors[i])) → if_statement@66 (not filter || count_no_visited == 0 || skip_strategy == nullptr || skip_strategy->ShouldVisit() || filter->CheckValid(neighbors[i]))
  │    │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ distance_provider.BatchQueryDistance  [L239] while_statement@222 (not candidate_set->Empty())
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ line_dists.data  [L240] while_statement@222 (not candidate_set->Empty())
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ to_be_visited_id.data  [L240] while_statement@222 (not candidate_set->Empty())
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ distance_provider.IsValid  [L245] while_statement@222 (not candidate_set->Empty()) → for_statement@242 i < count_no_visited → if_statement@245 (not distance_provider.IsValid(id))
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ reasoning->RecordVisit  [L249] while_statement@222 (not candidate_set->Empty()) → for_statement@242 i < count_no_visited → if_statement@248 (reasoning != nullptr)
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ distance_provider.OriginalId  [L249] while_statement@222 (not candidate_set->Empty()) → for_statement@242 i < count_no_visited → if_statement@248 (reasoning != nullptr)
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ is_finite_distance  [L251] while_statement@222 (not candidate_set->Empty()) → for_statement@242 i < count_no_visited → if_statement@251 (not is_finite_distance(dist))
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ candidate_set->Push  [L252] while_statement@222 (not candidate_set->Empty()) → for_statement@242 i < count_no_visited → if_statement@251 (not is_finite_distance(dist))
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ traversal_priority  [L252] while_statement@222 (not candidate_set->Empty()) → for_statement@242 i < count_no_visited → if_statement@251 (not is_finite_distance(dist))
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ check_func  [L253] while_statement@222 (not candidate_set->Empty()) → for_statement@242 i < count_no_visited → if_statement@251 (not is_finite_distance(dist)) → if_statement@253 (check_func(id) and is_result_distance_eligible<mode>(dist, inner_search_param))
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ is_result_distance_eligible<mode>  [L254] while_statement@222 (not candidate_set->Empty()) → for_statement@242 i < count_no_visited → if_statement@251 (not is_finite_distance(dist)) → if_statement@253 (check_func(id) and is_result_distance_eligible<mode>(dist, inner_search_param))
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ top_candidates->Push  [L255] while_statement@222 (not candidate_set->Empty()) → for_statement@242 i < count_no_visited → if_statement@251 (not is_finite_distance(dist)) → if_statement@253 (check_func(id) and is_result_distance_eligible<mode>(dist, inner_search_param))
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ top_candidates->Size  [L257] while_statement@222 (not candidate_set->Empty()) → for_statement@242 i < count_no_visited → if_statement@251 (not is_finite_distance(dist)) → if_statement@253 (check_func(id) and is_result_distance_eligible<mode>(dist, inner_search_param)) → if_statement@256 (mode == InnerSearchMode::KNN_SEARCH) → if_statement@257 (top_candidates->Size() > ef)
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ reasoning->RecordEviction  [L259] while_statement@222 (not candidate_set->Empty()) → for_statement@242 i < count_no_visited → if_statement@251 (not is_finite_distance(dist)) → if_statement@253 (check_func(id) and is_result_distance_eligible<mode>(dist, inner_search_param)) → if_statement@256 (mode == InnerSearchMode::KNN_SEARCH) → if_statement@257 (top_candidates->Size() > ef) → if_statement@258 (reasoning != nullptr)
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ distance_provider.OriginalId  [L260] while_statement@222 (not candidate_set->Empty()) → for_statement@242 i < count_no_visited → if_statement@251 (not is_finite_distance(dist)) → if_statement@253 (check_func(id) and is_result_distance_eligible<mode>(dist, inner_search_param)) → if_statement@256 (mode == InnerSearchMode::KNN_SEARCH) → if_statement@257 (top_candidates->Size() > ef) → if_statement@258 (reasoning != nullptr)
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ top_candidates->Top  [L260] while_statement@222 (not candidate_set->Empty()) → for_statement@242 i < count_no_visited → if_statement@251 (not is_finite_distance(dist)) → if_statement@253 (check_func(id) and is_result_distance_eligible<mode>(dist, inner_search_param)) → if_statement@256 (mode == InnerSearchMode::KNN_SEARCH) → if_statement@257 (top_candidates->Size() > ef) → if_statement@258 (reasoning != nullptr)
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ top_candidates->Pop  [L263] while_statement@222 (not candidate_set->Empty()) → for_statement@242 i < count_no_visited → if_statement@251 (not is_finite_distance(dist)) → if_statement@253 (check_func(id) and is_result_distance_eligible<mode>(dist, inner_search_param)) → if_statement@256 (mode == InnerSearchMode::KNN_SEARCH) → if_statement@257 (top_candidates->Size() > ef)
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ top_candidates->Pop  [L266] while_statement@222 (not candidate_set->Empty()) → for_statement@242 i < count_no_visited → if_statement@251 (not is_finite_distance(dist)) → if_statement@253 (check_func(id) and is_result_distance_eligible<mode>(dist, inner_search_param)) → if_statement@256 (mode == InnerSearchMode::KNN_SEARCH) [else 分支] → if_statement@265 (dist > inner_search_param.radius)
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ top_candidates->Empty  [L269] while_statement@222 (not candidate_set->Empty()) → for_statement@242 i < count_no_visited → if_statement@251 (not is_finite_distance(dist)) → if_statement@269 (not top_candidates->Empty())
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ top_candidates->Top  [L270] while_statement@222 (not candidate_set->Empty()) → for_statement@242 i < count_no_visited → if_statement@251 (not is_finite_distance(dist)) → if_statement@269 (not top_candidates->Empty())
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ top_candidates->Size  [L274] while_statement@222 (not candidate_set->Empty()) → for_statement@242 i < count_no_visited → if_statement@274 (top_candidates->Size() < ef || lower_bound > dist || (mode == InnerSearchMode::RANGE_SEARCH && dist <= inner_search_param.radius + THRESHOLD_ERROR))
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ candidate_set->Push  [L277] while_statement@222 (not candidate_set->Empty()) → for_statement@242 i < count_no_visited → if_statement@274 (top_candidates->Size() < ef || lower_bound > dist || (mode == InnerSearchMode::RANGE_SEARCH && dist <= inner_search_param.radius + THRESHOLD_ERROR))
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ distance_provider.Prefetch  [L278] while_statement@222 (not candidate_set->Empty()) → for_statement@242 i < count_no_visited → if_statement@274 (top_candidates->Size() < ef || lower_bound > dist || (mode == InnerSearchMode::RANGE_SEARCH && dist <= inner_search_param.radius + THRESHOLD_ERROR))
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ candidate_set->Top  [L278] while_statement@222 (not candidate_set->Empty()) → for_statement@242 i < count_no_visited → if_statement@274 (top_candidates->Size() < ef || lower_bound > dist || (mode == InnerSearchMode::RANGE_SEARCH && dist <= inner_search_param.radius + THRESHOLD_ERROR))
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ check_func  [L279] while_statement@222 (not candidate_set->Empty()) → for_statement@242 i < count_no_visited → if_statement@274 (top_candidates->Size() < ef || lower_bound > dist || (mode == InnerSearchMode::RANGE_SEARCH && dist <= inner_search_param.radius + THRESHOLD_ERROR)) → if_statement@279 (check_func(id))
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ top_candidates->Push  [L280] while_statement@222 (not candidate_set->Empty()) → for_statement@242 i < count_no_visited → if_statement@274 (top_candidates->Size() < ef || lower_bound > dist || (mode == InnerSearchMode::RANGE_SEARCH && dist <= inner_search_param.radius + THRESHOLD_ERROR)) → if_statement@279 (check_func(id))
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ reasoning->RecordFilterReject  [L282] while_statement@222 (not candidate_set->Empty()) → for_statement@242 i < count_no_visited → if_statement@274 (top_candidates->Size() < ef || lower_bound > dist || (mode == InnerSearchMode::RANGE_SEARCH && dist <= inner_search_param.radius + THRESHOLD_ERROR)) → if_statement@279 (check_func(id)) [else 分支] → if_statement@281 (reasoning != nullptr)
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ distance_provider.OriginalId  [L282] while_statement@222 (not candidate_set->Empty()) → for_statement@242 i < count_no_visited → if_statement@274 (top_candidates->Size() < ef || lower_bound > dist || (mode == InnerSearchMode::RANGE_SEARCH && dist <= inner_search_param.radius + THRESHOLD_ERROR)) → if_statement@279 (check_func(id)) [else 分支] → if_statement@281 (reasoning != nullptr)
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ top_candidates->Size  [L285] while_statement@222 (not candidate_set->Empty()) → for_statement@242 i < count_no_visited → if_statement@274 (top_candidates->Size() < ef || lower_bound > dist || (mode == InnerSearchMode::RANGE_SEARCH && dist <= inner_search_param.radius + THRESHOLD_ERROR)) → if_statement@284 (mode == InnerSearchMode::KNN_SEARCH) → if_statement@285 (top_candidates->Size() > ef)
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ reasoning->RecordEviction  [L287] while_statement@222 (not candidate_set->Empty()) → for_statement@242 i < count_no_visited → if_statement@274 (top_candidates->Size() < ef || lower_bound > dist || (mode == InnerSearchMode::RANGE_SEARCH && dist <= inner_search_param.radius + THRESHOLD_ERROR)) → if_statement@284 (mode == InnerSearchMode::KNN_SEARCH) → if_statement@285 (top_candidates->Size() > ef) → if_statement@286 (reasoning != nullptr)
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ distance_provider.OriginalId  [L288] while_statement@222 (not candidate_set->Empty()) → for_statement@242 i < count_no_visited → if_statement@274 (top_candidates->Size() < ef || lower_bound > dist || (mode == InnerSearchMode::RANGE_SEARCH && dist <= inner_search_param.radius + THRESHOLD_ERROR)) → if_statement@284 (mode == InnerSearchMode::KNN_SEARCH) → if_statement@285 (top_candidates->Size() > ef) → if_statement@286 (reasoning != nullptr)
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ top_candidates->Top  [L288] while_statement@222 (not candidate_set->Empty()) → for_statement@242 i < count_no_visited → if_statement@274 (top_candidates->Size() < ef || lower_bound > dist || (mode == InnerSearchMode::RANGE_SEARCH && dist <= inner_search_param.radius + THRESHOLD_ERROR)) → if_statement@284 (mode == InnerSearchMode::KNN_SEARCH) → if_statement@285 (top_candidates->Size() > ef) → if_statement@286 (reasoning != nullptr)
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ top_candidates->Pop  [L290] while_statement@222 (not candidate_set->Empty()) → for_statement@242 i < count_no_visited → if_statement@274 (top_candidates->Size() < ef || lower_bound > dist || (mode == InnerSearchMode::RANGE_SEARCH && dist <= inner_search_param.radius + THRESHOLD_ERROR)) → if_statement@284 (mode == InnerSearchMode::KNN_SEARCH) → if_statement@285 (top_candidates->Size() > ef)
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ top_candidates->Empty  [L293] while_statement@222 (not candidate_set->Empty()) → for_statement@242 i < count_no_visited → if_statement@274 (top_candidates->Size() < ef || lower_bound > dist || (mode == InnerSearchMode::RANGE_SEARCH && dist <= inner_search_param.radius + THRESHOLD_ERROR)) → if_statement@293 (not top_candidates->Empty())
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ top_candidates->Top  [L294] while_statement@222 (not candidate_set->Empty()) → for_statement@242 i < count_no_visited → if_statement@274 (top_candidates->Size() < ef || lower_bound > dist || (mode == InnerSearchMode::RANGE_SEARCH && dist <= inner_search_param.radius + THRESHOLD_ERROR)) → if_statement@293 (not top_candidates->Empty())
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ top_candidates->Size  [L300] if_statement@299 (mode == InnerSearchMode::KNN_SEARCH) → while_statement@300 (top_candidates->Size() > inner_search_param.topk)
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ top_candidates->Pop  [L301] if_statement@299 (mode == InnerSearchMode::KNN_SEARCH) → while_statement@300 (top_candidates->Size() > inner_search_param.topk)
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ top_candidates->Size  [L305] if_statement@299 (mode == InnerSearchMode::KNN_SEARCH) [else 分支] → if_statement@304 (inner_search_param.range_search_limit_size > 0) → while_statement@305 (top_candidates->Size() > inner_search_param.range_search_limit_size)
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ top_candidates->Pop  [L306] if_statement@299 (mode == InnerSearchMode::KNN_SEARCH) [else 分支] → if_statement@304 (inner_search_param.range_search_limit_size > 0) → while_statement@305 (top_candidates->Size() > inner_search_param.range_search_limit_size)
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ top_candidates->Empty  [L309] if_statement@299 (mode == InnerSearchMode::KNN_SEARCH) [else 分支] → while_statement@309 (not top_candidates->Empty() && top_candidates->Top().first > inner_search_param.radius + THRESHOLD_ERROR)
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ top_candidates->Top  [L310] if_statement@299 (mode == InnerSearchMode::KNN_SEARCH) [else 分支] → while_statement@309 (not top_candidates->Empty() && top_candidates->Top().first > inner_search_param.radius + THRESHOLD_ERROR)
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ top_candidates->Pop  [L311] if_statement@299 (mode == InnerSearchMode::KNN_SEARCH) [else 分支] → while_statement@309 (not top_candidates->Empty() && top_candidates->Top().first > inner_search_param.radius + THRESHOLD_ERROR)
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ ctx->stats->dist_cmp.fetch_add  [L315] if_statement@314 (ctx != nullptr && ctx->stats != nullptr)
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ ctx->stats->hops.fetch_add  [L316] if_statement@314 (ctx != nullptr && ctx->stats != nullptr)
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │  #50 BasicSearcher::search_impl [src/impl/searcher/basic_searcher.cpp:322]
  │    │    │    │    │    ├─ select_query_allocator  [L332] 函数本体；短路求值/提前返回见源码
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ std::make_shared<StandardHeap<true, false>>  [L334] 函数本体；短路求值/提前返回见源码
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ std::make_shared<StandardHeap<true, false>>  [L335] 函数本体；短路求值/提前返回见源码
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ AcquireQueryComputer  [L341] 函数本体；短路求值/提前返回见源码
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ std::numeric_limits<float>::max  [L351] 函数本体；短路求值/提前返回见源码
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ graph->MaximumDegree  [L356] 函数本体；短路求值/提前返回见源码
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ graph->MaximumDegree  [L357] 函数本体；短路求值/提前返回见源码
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ graph->MaximumDegree  [L358] 函数本体；短路求值/提前返回见源码
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ graph->MaximumDegree  [L359] 函数本体；短路求值/提前返回见源码
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ create_filter_search_skip_strategy  [L360] 函数本体；短路求值/提前返回见源码
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ inner_search_param.is_inner_id_allowed->ValidRatio  [L363] conditional_expression@362 inner_search_param.is_inner_id_allowed != nullptr
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ rabitq_lower_bound_candidates->clear  [L367] if_statement@366 (rabitq_lower_bound_candidates != nullptr)
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ iter_ctx->IsFirstUsed  [L370] if_statement@370 (!iter_ctx->IsFirstUsed())
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ iter_ctx->Empty  [L371] if_statement@370 (!iter_ctx->IsFirstUsed()) → if_statement@371 (iter_ctx->Empty())
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ iter_ctx->Empty  [L374] if_statement@370 (!iter_ctx->IsFirstUsed()) → while_statement@374 (!iter_ctx->Empty())
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ iter_ctx->GetTopID  [L375] if_statement@370 (!iter_ctx->IsFirstUsed()) → while_statement@374 (!iter_ctx->Empty())
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ iter_ctx->GetTopDist  [L376] if_statement@370 (!iter_ctx->IsFirstUsed()) → while_statement@374 (!iter_ctx->Empty())
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ vl->Set  [L377] if_statement@370 (!iter_ctx->IsFirstUsed()) → while_statement@374 (!iter_ctx->Empty())
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ iter_ctx->CheckPoint  [L378] if_statement@370 (!iter_ctx->IsFirstUsed()) → while_statement@374 (!iter_ctx->Empty()) → if_statement@378 (iter_ctx->CheckPoint(cur_inner_id))
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ flatten->Query  [L379] if_statement@370 (!iter_ctx->IsFirstUsed()) → while_statement@374 (!iter_ctx->Empty()) → if_statement@378 (iter_ctx->CheckPoint(cur_inner_id))
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ is_result_distance_eligible<mode>  [L382] if_statement@370 (!iter_ctx->IsFirstUsed()) → while_statement@374 (!iter_ctx->Empty()) → if_statement@378 (iter_ctx->CheckPoint(cur_inner_id)) → if_statement@382 (is_result_distance_eligible<mode>(cur_dist, inner_search_param))
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ top_candidates->Push  [L383] if_statement@370 (!iter_ctx->IsFirstUsed()) → while_statement@374 (!iter_ctx->Empty()) → if_statement@378 (iter_ctx->CheckPoint(cur_inner_id)) → if_statement@382 (is_result_distance_eligible<mode>(cur_dist, inner_search_param))
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ candidate_set->Push  [L385] if_statement@370 (!iter_ctx->IsFirstUsed()) → while_statement@374 (!iter_ctx->Empty()) → if_statement@378 (iter_ctx->CheckPoint(cur_inner_id))
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ traversal_priority  [L385] if_statement@370 (!iter_ctx->IsFirstUsed()) → while_statement@374 (!iter_ctx->Empty()) → if_statement@378 (iter_ctx->CheckPoint(cur_inner_id))
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ top_candidates->Empty  [L387] if_statement@370 (!iter_ctx->IsFirstUsed()) → while_statement@374 (!iter_ctx->Empty()) → if_statement@378 (iter_ctx->CheckPoint(cur_inner_id)) → if_statement@386 (mode == InnerSearchMode::RANGE_SEARCH) → if_statement@387 (cur_dist > inner_search_param.radius and not top_candidates->Empty())
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ top_candidates->Pop  [L388] if_statement@370 (!iter_ctx->IsFirstUsed()) → while_statement@374 (!iter_ctx->Empty()) → if_statement@378 (iter_ctx->CheckPoint(cur_inner_id)) → if_statement@386 (mode == InnerSearchMode::RANGE_SEARCH) → if_statement@387 (cur_dist > inner_search_param.radius and not top_candidates->Empty())
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ iter_ctx->PopDiscard  [L392] if_statement@370 (!iter_ctx->IsFirstUsed()) → while_statement@374 (!iter_ctx->Empty())
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ top_candidates->Size  [L395] if_statement@370 (!iter_ctx->IsFirstUsed()) → if_statement@394 (mode == InnerSearchMode::KNN_SEARCH) → while_statement@395 (top_candidates->Size() > ef)
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ top_candidates->Top  [L396] if_statement@370 (!iter_ctx->IsFirstUsed()) → if_statement@394 (mode == InnerSearchMode::KNN_SEARCH) → while_statement@395 (top_candidates->Size() > ef)
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ iter_ctx->CheckPoint  [L397] if_statement@370 (!iter_ctx->IsFirstUsed()) → if_statement@394 (mode == InnerSearchMode::KNN_SEARCH) → while_statement@395 (top_candidates->Size() > ef) → if_statement@397 (iter_ctx->CheckPoint(cur_node_pair.second))
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ iter_ctx->AddDiscardNode  [L398] if_statement@370 (!iter_ctx->IsFirstUsed()) → if_statement@394 (mode == InnerSearchMode::KNN_SEARCH) → while_statement@395 (top_candidates->Size() > ef) → if_statement@397 (iter_ctx->CheckPoint(cur_node_pair.second))
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ top_candidates->Pop  [L400] if_statement@370 (!iter_ctx->IsFirstUsed()) → if_statement@394 (mode == InnerSearchMode::KNN_SEARCH) → while_statement@395 (top_candidates->Size() > ef)
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ top_candidates->Empty  [L403] if_statement@370 (!iter_ctx->IsFirstUsed()) → if_statement@403 (not top_candidates->Empty())
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ top_candidates->Top  [L404] if_statement@370 (!iter_ctx->IsFirstUsed()) → if_statement@403 (not top_candidates->Empty())
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ flatten->QueryWithDistanceLowerBound  [L408] if_statement@370 (!iter_ctx->IsFirstUsed()) [else 分支] → if_statement@407 (inner_search_param.enable_rabitq_one_bit_search)
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ flatten->Query  [L410] if_statement@370 (!iter_ctx->IsFirstUsed()) [else 分支] → if_statement@407 (inner_search_param.enable_rabitq_one_bit_search) [else 分支]
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ is_id_allowed->CheckValid  [L412] if_statement@370 (!iter_ctx->IsFirstUsed()) [else 分支] → if_statement@412 (not is_id_allowed || is_id_allowed->CheckValid(ep))
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ is_result_distance_eligible<mode>  [L413] if_statement@370 (!iter_ctx->IsFirstUsed()) [else 分支] → if_statement@412 (not is_id_allowed || is_id_allowed->CheckValid(ep)) → if_statement@413 (is_result_distance_eligible<mode>(dist, inner_search_param))
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ top_candidates->Push  [L414] if_statement@370 (!iter_ctx->IsFirstUsed()) [else 分支] → if_statement@412 (not is_id_allowed || is_id_allowed->CheckValid(ep)) → if_statement@413 (is_result_distance_eligible<mode>(dist, inner_search_param))
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ top_candidates->Top  [L415] if_statement@370 (!iter_ctx->IsFirstUsed()) [else 分支] → if_statement@412 (not is_id_allowed || is_id_allowed->CheckValid(ep)) → if_statement@413 (is_result_distance_eligible<mode>(dist, inner_search_param))
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ candidate_set->Push  [L418] if_statement@370 (!iter_ctx->IsFirstUsed()) [else 分支]
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ traversal_priority  [L418] if_statement@370 (!iter_ctx->IsFirstUsed()) [else 分支]
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ vl->Set  [L419] if_statement@370 (!iter_ctx->IsFirstUsed()) [else 分支]
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ candidate_set->Empty  [L422] while_statement@422 (not candidate_set->Empty())
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ candidate_set->Top  [L427] while_statement@422 (not candidate_set->Empty())
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ top_candidates->Size  [L430] while_statement@422 (not candidate_set->Empty()) → if_statement@429 (mode == InnerSearchMode::KNN_SEARCH) → if_statement@430 ((-current_node_pair.first) > lower_bound && top_candidates->Size() >= ef)
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ reasoning->SetTermination  [L432] while_statement@422 (not candidate_set->Empty()) → if_statement@429 (mode == InnerSearchMode::KNN_SEARCH) → if_statement@430 ((-current_node_pair.first) > lower_bound && top_candidates->Size() >= ef) → if_statement@431 (reasoning != nullptr)
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ candidate_set->Pop  [L437] while_statement@422 (not candidate_set->Empty())
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ candidate_set->Empty  [L439] while_statement@422 (not candidate_set->Empty()) → if_statement@439 (not candidate_set->Empty())
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ graph->Prefetch  [L440] while_statement@422 (not candidate_set->Empty()) → if_statement@439 (not candidate_set->Empty())
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ candidate_set->Top  [L440] while_statement@422 (not candidate_set->Empty()) → if_statement@439 (not candidate_set->Empty())
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ visit  [L443] while_statement@422 (not candidate_set->Empty())
  │    │    │    │    │    │  ↳ 复用节点 #49 BasicSearcher::visit（本树前文已展开）
  │    │    │    │    │    ├─ skip_strategy.get  [L447] while_statement@422 (not candidate_set->Empty())
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ top_candidates->Size  [L454] while_statement@422 (not candidate_set->Empty()) → if_statement@454 (inner_search_param.enable_rabitq_one_bit_search and top_candidates->Size() == ef and rabitq_lower_bound_candidates != nullptr)
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ flatten->QueryWithDistanceLowerBound  [L457] while_statement@422 (not candidate_set->Empty()) → if_statement@454 (inner_search_param.enable_rabitq_one_bit_search and top_candidates->Size() == ef and rabitq_lower_bound_candidates != nullptr)
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ line_dists.data  [L457] while_statement@422 (not candidate_set->Empty()) → if_statement@454 (inner_search_param.enable_rabitq_one_bit_search and top_candidates->Size() == ef and rabitq_lower_bound_candidates != nullptr)
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ lower_bound_dists.data  [L458] while_statement@422 (not candidate_set->Empty()) → if_statement@454 (inner_search_param.enable_rabitq_one_bit_search and top_candidates->Size() == ef and rabitq_lower_bound_candidates != nullptr)
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ to_be_visited_id.data  [L460] while_statement@422 (not candidate_set->Empty()) → if_statement@454 (inner_search_param.enable_rabitq_one_bit_search and top_candidates->Size() == ef and rabitq_lower_bound_candidates != nullptr)
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ flatten->QueryWithDistanceLowerBound  [L464] while_statement@422 (not candidate_set->Empty()) → if_statement@454 (inner_search_param.enable_rabitq_one_bit_search and top_candidates->Size() == ef and rabitq_lower_bound_candidates != nullptr) [else 分支] → if_statement@463 (inner_search_param.enable_rabitq_one_bit_search)
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ line_dists.data  [L464] while_statement@422 (not candidate_set->Empty()) → if_statement@454 (inner_search_param.enable_rabitq_one_bit_search and top_candidates->Size() == ef and rabitq_lower_bound_candidates != nullptr) [else 分支] → if_statement@463 (inner_search_param.enable_rabitq_one_bit_search)
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ to_be_visited_id.data  [L467] while_statement@422 (not candidate_set->Empty()) → if_statement@454 (inner_search_param.enable_rabitq_one_bit_search and top_candidates->Size() == ef and rabitq_lower_bound_candidates != nullptr) [else 分支] → if_statement@463 (inner_search_param.enable_rabitq_one_bit_search)
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ flatten->Query  [L471] while_statement@422 (not candidate_set->Empty()) → if_statement@454 (inner_search_param.enable_rabitq_one_bit_search and top_candidates->Size() == ef and rabitq_lower_bound_candidates != nullptr) [else 分支] → if_statement@463 (inner_search_param.enable_rabitq_one_bit_search) [else 分支]
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ line_dists.data  [L472] while_statement@422 (not candidate_set->Empty()) → if_statement@454 (inner_search_param.enable_rabitq_one_bit_search and top_candidates->Size() == ef and rabitq_lower_bound_candidates != nullptr) [else 分支] → if_statement@463 (inner_search_param.enable_rabitq_one_bit_search) [else 分支]
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ to_be_visited_id.data  [L472] while_statement@422 (not candidate_set->Empty()) → if_statement@454 (inner_search_param.enable_rabitq_one_bit_search and top_candidates->Size() == ef and rabitq_lower_bound_candidates != nullptr) [else 分支] → if_statement@463 (inner_search_param.enable_rabitq_one_bit_search) [else 分支]
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ is_finite_distance  [L477] while_statement@422 (not candidate_set->Empty()) → for_statement@474 i < count_no_visited → if_statement@477 (not is_finite_distance(dist))
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ is_result_distance_eligible<mode>  [L478] while_statement@422 (not candidate_set->Empty()) → for_statement@474 i < count_no_visited → if_statement@477 (not is_finite_distance(dist)) → if_statement@478 (is_result_distance_eligible<mode>(dist, inner_search_param) and (not is_id_allowed || is_id_allowed->CheckValid(cur_id)))
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ is_id_allowed->CheckValid  [L479] while_statement@422 (not candidate_set->Empty()) → for_statement@474 i < count_no_visited → if_statement@477 (not is_finite_distance(dist)) → if_statement@478 (is_result_distance_eligible<mode>(dist, inner_search_param) and (not is_id_allowed || is_id_allowed->CheckValid(cur_id)))
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ top_candidates->Push  [L480] while_statement@422 (not candidate_set->Empty()) → for_statement@474 i < count_no_visited → if_statement@477 (not is_finite_distance(dist)) → if_statement@478 (is_result_distance_eligible<mode>(dist, inner_search_param) and (not is_id_allowed || is_id_allowed->CheckValid(cur_id)))
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ top_candidates->Size  [L482] while_statement@422 (not candidate_set->Empty()) → for_statement@474 i < count_no_visited → if_statement@477 (not is_finite_distance(dist)) → if_statement@478 (is_result_distance_eligible<mode>(dist, inner_search_param) and (not is_id_allowed || is_id_allowed->CheckValid(cur_id))) → if_statement@481 (mode == KNN_SEARCH) → if_statement@482 (top_candidates->Size() > ef)
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ top_candidates->Top  [L483] while_statement@422 (not candidate_set->Empty()) → for_statement@474 i < count_no_visited → if_statement@477 (not is_finite_distance(dist)) → if_statement@478 (is_result_distance_eligible<mode>(dist, inner_search_param) and (not is_id_allowed || is_id_allowed->CheckValid(cur_id))) → if_statement@481 (mode == KNN_SEARCH) → if_statement@482 (top_candidates->Size() > ef)
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ iter_ctx->CheckPoint  [L484] while_statement@422 (not candidate_set->Empty()) → for_statement@474 i < count_no_visited → if_statement@477 (not is_finite_distance(dist)) → if_statement@478 (is_result_distance_eligible<mode>(dist, inner_search_param) and (not is_id_allowed || is_id_allowed->CheckValid(cur_id))) → if_statement@481 (mode == KNN_SEARCH) → if_statement@482 (top_candidates->Size() > ef) → if_statement@484 (iter_ctx->CheckPoint(evicted.second))
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ iter_ctx->AddDiscardNode  [L485] while_statement@422 (not candidate_set->Empty()) → for_statement@474 i < count_no_visited → if_statement@477 (not is_finite_distance(dist)) → if_statement@478 (is_result_distance_eligible<mode>(dist, inner_search_param) and (not is_id_allowed || is_id_allowed->CheckValid(cur_id))) → if_statement@481 (mode == KNN_SEARCH) → if_statement@482 (top_candidates->Size() > ef) → if_statement@484 (iter_ctx->CheckPoint(evicted.second))
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ top_candidates->Pop  [L487] while_statement@422 (not candidate_set->Empty()) → for_statement@474 i < count_no_visited → if_statement@477 (not is_finite_distance(dist)) → if_statement@478 (is_result_distance_eligible<mode>(dist, inner_search_param) and (not is_id_allowed || is_id_allowed->CheckValid(cur_id))) → if_statement@481 (mode == KNN_SEARCH) → if_statement@482 (top_candidates->Size() > ef)
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ top_candidates->Pop  [L490] while_statement@422 (not candidate_set->Empty()) → for_statement@474 i < count_no_visited → if_statement@477 (not is_finite_distance(dist)) → if_statement@478 (is_result_distance_eligible<mode>(dist, inner_search_param) and (not is_id_allowed || is_id_allowed->CheckValid(cur_id))) → if_statement@481 (mode == KNN_SEARCH) [else 分支] → if_statement@489 (dist > inner_search_param.radius)
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ iter_ctx->CheckPoint  [L493] while_statement@422 (not candidate_set->Empty()) → for_statement@474 i < count_no_visited → if_statement@477 (not is_finite_distance(dist)) → if_statement@493 (iter_ctx->CheckPoint(cur_id))
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ candidate_set->Push  [L494] while_statement@422 (not candidate_set->Empty()) → for_statement@474 i < count_no_visited → if_statement@477 (not is_finite_distance(dist)) → if_statement@493 (iter_ctx->CheckPoint(cur_id))
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ traversal_priority  [L494] while_statement@422 (not candidate_set->Empty()) → for_statement@474 i < count_no_visited → if_statement@477 (not is_finite_distance(dist)) → if_statement@493 (iter_ctx->CheckPoint(cur_id))
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ flatten->Prefetch  [L495] while_statement@422 (not candidate_set->Empty()) → for_statement@474 i < count_no_visited → if_statement@477 (not is_finite_distance(dist)) → if_statement@493 (iter_ctx->CheckPoint(cur_id))
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ top_candidates->Empty  [L497] while_statement@422 (not candidate_set->Empty()) → for_statement@474 i < count_no_visited → if_statement@477 (not is_finite_distance(dist)) → if_statement@497 (not top_candidates->Empty())
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ top_candidates->Top  [L498] while_statement@422 (not candidate_set->Empty()) → for_statement@474 i < count_no_visited → if_statement@477 (not is_finite_distance(dist)) → if_statement@497 (not top_candidates->Empty())
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ is_id_allowed->CheckValid  [L502] while_statement@422 (not candidate_set->Empty()) → for_statement@474 i < count_no_visited
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ iter_ctx->CheckPoint  [L505] while_statement@422 (not candidate_set->Empty()) → for_statement@474 i < count_no_visited → if_statement@503 (mode == KNN_SEARCH) → if_statement@504 (collect_rabitq_lower_bound and lower_bound_dists[i] < lower_bound and id_allowed and iter_ctx->CheckPoint(cur_id))
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ rabitq_lower_bound_candidates->emplace_back  [L506] while_statement@422 (not candidate_set->Empty()) → for_statement@474 i < count_no_visited → if_statement@503 (mode == KNN_SEARCH) → if_statement@504 (collect_rabitq_lower_bound and lower_bound_dists[i] < lower_bound and id_allowed and iter_ctx->CheckPoint(cur_id))
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ top_candidates->Size  [L509] while_statement@422 (not candidate_set->Empty()) → for_statement@474 i < count_no_visited → if_statement@509 (top_candidates->Size() < ef || lower_bound > dist || (mode == RANGE_SEARCH && dist <= inner_search_param.radius))
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ iter_ctx->CheckPoint  [L511] while_statement@422 (not candidate_set->Empty()) → for_statement@474 i < count_no_visited → if_statement@509 (top_candidates->Size() < ef || lower_bound > dist || (mode == RANGE_SEARCH && dist <= inner_search_param.radius)) → if_statement@511 (!iter_ctx->CheckPoint(cur_id))
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ candidate_set->Push  [L514] while_statement@422 (not candidate_set->Empty()) → for_statement@474 i < count_no_visited → if_statement@509 (top_candidates->Size() < ef || lower_bound > dist || (mode == RANGE_SEARCH && dist <= inner_search_param.radius))
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ flatten->Prefetch  [L515] while_statement@422 (not candidate_set->Empty()) → for_statement@474 i < count_no_visited → if_statement@509 (top_candidates->Size() < ef || lower_bound > dist || (mode == RANGE_SEARCH && dist <= inner_search_param.radius))
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ candidate_set->Top  [L515] while_statement@422 (not candidate_set->Empty()) → for_statement@474 i < count_no_visited → if_statement@509 (top_candidates->Size() < ef || lower_bound > dist || (mode == RANGE_SEARCH && dist <= inner_search_param.radius))
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ top_candidates->Push  [L517] while_statement@422 (not candidate_set->Empty()) → for_statement@474 i < count_no_visited → if_statement@509 (top_candidates->Size() < ef || lower_bound > dist || (mode == RANGE_SEARCH && dist <= inner_search_param.radius)) → if_statement@516 (id_allowed)
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ top_candidates->Size  [L521] while_statement@422 (not candidate_set->Empty()) → for_statement@474 i < count_no_visited → if_statement@509 (top_candidates->Size() < ef || lower_bound > dist || (mode == RANGE_SEARCH && dist <= inner_search_param.radius)) → if_statement@520 (mode == KNN_SEARCH) → if_statement@521 (top_candidates->Size() > ef)
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ iter_ctx->CheckPoint  [L522] while_statement@422 (not candidate_set->Empty()) → for_statement@474 i < count_no_visited → if_statement@509 (top_candidates->Size() < ef || lower_bound > dist || (mode == RANGE_SEARCH && dist <= inner_search_param.radius)) → if_statement@520 (mode == KNN_SEARCH) → if_statement@521 (top_candidates->Size() > ef) → if_statement@522 (iter_ctx->CheckPoint(top_candidates->Top().second))
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ top_candidates->Top  [L522] while_statement@422 (not candidate_set->Empty()) → for_statement@474 i < count_no_visited → if_statement@509 (top_candidates->Size() < ef || lower_bound > dist || (mode == RANGE_SEARCH && dist <= inner_search_param.radius)) → if_statement@520 (mode == KNN_SEARCH) → if_statement@521 (top_candidates->Size() > ef) → if_statement@522 (iter_ctx->CheckPoint(top_candidates->Top().second))
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ top_candidates->Top  [L523] while_statement@422 (not candidate_set->Empty()) → for_statement@474 i < count_no_visited → if_statement@509 (top_candidates->Size() < ef || lower_bound > dist || (mode == RANGE_SEARCH && dist <= inner_search_param.radius)) → if_statement@520 (mode == KNN_SEARCH) → if_statement@521 (top_candidates->Size() > ef) → if_statement@522 (iter_ctx->CheckPoint(top_candidates->Top().second))
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ iter_ctx->AddDiscardNode  [L524] while_statement@422 (not candidate_set->Empty()) → for_statement@474 i < count_no_visited → if_statement@509 (top_candidates->Size() < ef || lower_bound > dist || (mode == RANGE_SEARCH && dist <= inner_search_param.radius)) → if_statement@520 (mode == KNN_SEARCH) → if_statement@521 (top_candidates->Size() > ef) → if_statement@522 (iter_ctx->CheckPoint(top_candidates->Top().second))
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ top_candidates->Pop  [L526] while_statement@422 (not candidate_set->Empty()) → for_statement@474 i < count_no_visited → if_statement@509 (top_candidates->Size() < ef || lower_bound > dist || (mode == RANGE_SEARCH && dist <= inner_search_param.radius)) → if_statement@520 (mode == KNN_SEARCH) → if_statement@521 (top_candidates->Size() > ef)
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ top_candidates->Empty  [L530] while_statement@422 (not candidate_set->Empty()) → for_statement@474 i < count_no_visited → if_statement@509 (top_candidates->Size() < ef || lower_bound > dist || (mode == RANGE_SEARCH && dist <= inner_search_param.radius)) → if_statement@530 (not top_candidates->Empty())
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ top_candidates->Top  [L531] while_statement@422 (not candidate_set->Empty()) → for_statement@474 i < count_no_visited → if_statement@509 (top_candidates->Size() < ef || lower_bound > dist || (mode == RANGE_SEARCH && dist <= inner_search_param.radius)) → if_statement@530 (not top_candidates->Empty())
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ top_candidates->Size  [L538] if_statement@537 (mode == KNN_SEARCH) → while_statement@538 (top_candidates->Size() > inner_search_param.topk)
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ top_candidates->Top  [L539] if_statement@537 (mode == KNN_SEARCH) → while_statement@538 (top_candidates->Size() > inner_search_param.topk)
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ iter_ctx->CheckPoint  [L540] if_statement@537 (mode == KNN_SEARCH) → while_statement@538 (top_candidates->Size() > inner_search_param.topk) → if_statement@540 (iter_ctx->CheckPoint(cur_node_pair.second))
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ iter_ctx->AddDiscardNode  [L541] if_statement@537 (mode == KNN_SEARCH) → while_statement@538 (top_candidates->Size() > inner_search_param.topk) → if_statement@540 (iter_ctx->CheckPoint(cur_node_pair.second))
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ top_candidates->Pop  [L543] if_statement@537 (mode == KNN_SEARCH) → while_statement@538 (top_candidates->Size() > inner_search_param.topk)
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │  #51 BasicSearcher::search_impl [src/impl/searcher/basic_searcher.cpp:551]
  │    │    │    │    │    ├─ select_query_allocator  [L562] 函数本体；短路求值/提前返回见源码
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ std::make_shared<StandardHeap<true, false>>  [L564] 函数本体；短路求值/提前返回见源码
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ std::make_shared<StandardHeap<true, false>>  [L565] 函数本体；短路求值/提前返回见源码
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ AcquireQueryComputer  [L575] if_statement@574 (not use_custom_distance and computer == nullptr)
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ std::numeric_limits<float>::max  [L584] 函数本体；短路求值/提前返回见源码
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ graph->MaximumDegree  [L589] 函数本体；短路求值/提前返回见源码
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ graph->MaximumDegree  [L590] 函数本体；短路求值/提前返回见源码
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ graph->MaximumDegree  [L591] 函数本体；短路求值/提前返回见源码
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ graph->MaximumDegree  [L592] 函数本体；短路求值/提前返回见源码
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ std::max<uint64_t>  [L595] conditional_expression@594 use_custom_distance
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ std::min<uint64_t>  [L596] conditional_expression@594 use_custom_distance
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ graph->MaximumDegree  [L597] conditional_expression@594 use_custom_distance
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ create_filter_search_skip_strategy  [L600] 函数本体；短路求值/提前返回见源码
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ inner_search_param.is_inner_id_allowed->ValidRatio  [L603] conditional_expression@602 inner_search_param.is_inner_id_allowed != nullptr
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ rabitq_lower_bound_candidates->clear  [L607] if_statement@606 (rabitq_lower_bound_candidates != nullptr)
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ inner_search_param.executors.empty  [L611] if_statement@611 (not inner_search_param.executors.empty() and inner_search_param.executors[0] != nullptr)
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ inner_search_param.executors[0]->Clear  [L612] if_statement@611 (not inner_search_param.executors.empty() and inner_search_param.executors[0] != nullptr)
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ inner_search_param.executors[0]->Run  [L613] if_statement@611 (not inner_search_param.executors.empty() and inner_search_param.executors[0] != nullptr)
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ is_id_allowed->CheckValid  [L617] lambda@616（定义体，执行时间取决于调用/调度）
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ attr_ft->CheckValid  [L618] lambda@616（定义体，执行时间取决于调用/调度）
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ flatten->Query  [L624] lambda@622（定义体，执行时间取决于调用/调度） → if_statement@623 (not use_custom_distance)
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ CHECK_ARGUMENT  [L627] lambda@622（定义体，执行时间取决于调用/调度）
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ CHECK_ARGUMENT  [L628] lambda@622（定义体，执行时间取决于调用/调度）
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ std::min  [L633] lambda@622（定义体，执行时间取决于调用/调度） → for_statement@630 offset < count
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ label_table->GetLabelById  [L635] lambda@622（定义体，执行时间取决于调用/调度） → for_statement@630 offset < count → for_statement@634 i < batch_count
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ inner_search_param.distance_batch_func  [L637] lambda@622（定义体，执行时间取决于调用/调度） → for_statement@630 offset < count
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ custom_labels.data  [L638] lambda@622（定义体，执行时间取决于调用/调度） → for_statement@630 offset < count
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ ctx->stats->AddDistance  [L640] lambda@622（定义体，执行时间取决于调用/调度） → for_statement@630 offset < count → if_statement@639 (ctx != nullptr and ctx->stats != nullptr)
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ CHECK_ARGUMENT  [L644] lambda@622（定义体，执行时间取决于调用/调度） → for_statement@630 offset < count → for_statement@643 i < batch_count
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ is_finite_distance  [L644] lambda@622（定义体，执行时间取决于调用/调度） → for_statement@630 offset < count → for_statement@643 i < batch_count
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ score_ids  [L659] lambda@649（定义体，执行时间取决于调用/调度） → lambda@655（定义体，执行时间取决于调用/调度）
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ neighbors.data  [L659] lambda@649（定义体，执行时间取决于调用/调度） → lambda@655（定义体，执行时间取决于调用/调度）
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ lower_bound_dists.data  [L659] lambda@649（定义体，执行时间取决于调用/调度） → lambda@655（定义体，执行时间取决于调用/调度）
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ reasoning->RecordVisit  [L663] lambda@649（定义体，执行时间取决于调用/调度） → lambda@655（定义体，执行时间取决于调用/调度） → for_statement@661 i < duplicate_count → if_statement@662 (reasoning != nullptr)
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ top_candidates->Push  [L665] lambda@649（定义体，执行时间取决于调用/调度） → lambda@655（定义体，执行时间取决于调用/调度） → for_statement@661 i < duplicate_count
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ check_func  [L671] lambda@649（定义体，执行时间取决于调用/调度） → for_range_loop@670 → if_statement@671 (not check_func(item))
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ neighbors.size  [L675] lambda@649（定义体，执行时间取决于调用/调度） → for_range_loop@670 → if_statement@675 (duplicate_count == neighbors.size())
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ submit_duplicates  [L676] lambda@649（定义体，执行时间取决于调用/调度） → for_range_loop@670 → if_statement@675 (duplicate_count == neighbors.size())
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ submit_duplicates  [L679] lambda@649（定义体，执行时间取决于调用/调度）
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ top_candidates->Size  [L682] lambda@649（定义体，执行时间取决于调用/调度） → if_statement@681 (mode == KNN_SEARCH) → while_statement@682 (top_candidates->Size() > ef)
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ reasoning->RecordEviction  [L684] lambda@649（定义体，执行时间取决于调用/调度） → if_statement@681 (mode == KNN_SEARCH) → while_statement@682 (top_candidates->Size() > ef) → if_statement@683 (reasoning != nullptr)
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ top_candidates->Top  [L684] lambda@649（定义体，执行时间取决于调用/调度） → if_statement@681 (mode == KNN_SEARCH) → while_statement@682 (top_candidates->Size() > ef) → if_statement@683 (reasoning != nullptr)
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ top_candidates->Pop  [L686] lambda@649（定义体，执行时间取决于调用/调度） → if_statement@681 (mode == KNN_SEARCH) → while_statement@682 (top_candidates->Size() > ef)
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ top_candidates->Empty  [L689] lambda@649（定义体，执行时间取决于调用/调度） → if_statement@689 (not top_candidates->Empty())
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ top_candidates->Top  [L690] lambda@649（定义体，执行时间取决于调用/调度） → if_statement@689 (not top_candidates->Empty())
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ score_ids  [L695] if_statement@694 (use_custom_distance)
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ flatten->QueryWithDistanceLowerBound  [L697] if_statement@694 (use_custom_distance) [else 分支] → if_statement@696 (inner_search_param.enable_rabitq_one_bit_search)
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ flatten->Query  [L699] if_statement@694 (use_custom_distance) [else 分支] → if_statement@696 (inner_search_param.enable_rabitq_one_bit_search) [else 分支]
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ check_func  [L702] if_statement@702 (check_func(ep) and is_result_distance_eligible<mode>(dist, inner_search_param))
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ is_result_distance_eligible<mode>  [L702] if_statement@702 (check_func(ep) and is_result_distance_eligible<mode>(dist, inner_search_param))
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ top_candidates->Push  [L703] if_statement@702 (check_func(ep) and is_result_distance_eligible<mode>(dist, inner_search_param))
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ is_finite_distance  [L705] if_statement@705 (not is_finite_distance(dist) and inner_search_param.consider_duplicate and not use_custom_distance and is_result_distance_eligible<mode>(dist, inner_search_param))
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ is_result_distance_eligible<mode>  [L706] if_statement@705 (not is_finite_distance(dist) and inner_search_param.consider_duplicate and not use_custom_distance and is_result_distance_eligible<mode>(dist, inner_search_param))
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ graph->GetDuplicateIds  [L707] if_statement@705 (not is_finite_distance(dist) and inner_search_param.consider_duplicate and not use_custom_distance and is_result_distance_eligible<mode>(dist, inner_search_param)) → for_range_loop@707
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ check_func  [L708] if_statement@705 (not is_finite_distance(dist) and inner_search_param.consider_duplicate and not use_custom_distance and is_result_distance_eligible<mode>(dist, inner_search_param)) → for_range_loop@707 → if_statement@708 (check_func(duplicate_id))
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ top_candidates->Push  [L709] if_statement@705 (not is_finite_distance(dist) and inner_search_param.consider_duplicate and not use_custom_distance and is_result_distance_eligible<mode>(dist, inner_search_param)) → for_range_loop@707 → if_statement@708 (check_func(duplicate_id))
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ top_candidates->Size  [L713] if_statement@705 (not is_finite_distance(dist) and inner_search_param.consider_duplicate and not use_custom_distance and is_result_distance_eligible<mode>(dist, inner_search_param)) → if_statement@712 (mode == KNN_SEARCH) → while_statement@713 (top_candidates->Size() > ef)
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ top_candidates->Pop  [L714] if_statement@705 (not is_finite_distance(dist) and inner_search_param.consider_duplicate and not use_custom_distance and is_result_distance_eligible<mode>(dist, inner_search_param)) → if_statement@712 (mode == KNN_SEARCH) → while_statement@713 (top_candidates->Size() > ef)
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ top_candidates->Empty  [L719] if_statement@718 (mode == InnerSearchMode::RANGE_SEARCH) → while_statement@719 (dist > inner_search_param.radius and not top_candidates->Empty())
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ top_candidates->Pop  [L720] if_statement@718 (mode == InnerSearchMode::RANGE_SEARCH) → while_statement@719 (dist > inner_search_param.radius and not top_candidates->Empty())
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ top_candidates->Empty  [L723] if_statement@723 (not top_candidates->Empty())
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ top_candidates->Top  [L724] if_statement@723 (not top_candidates->Empty())
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ graph->GetDuplicateIds  [L727] if_statement@726 (use_custom_distance and inner_search_param.consider_duplicate)
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ score_duplicates  [L728] if_statement@726 (use_custom_distance and inner_search_param.consider_duplicate)
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ candidate_set->Push  [L730] 函数本体；短路求值/提前返回见源码
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ traversal_priority  [L730] 函数本体；短路求值/提前返回见源码
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ vl->Set  [L731] 函数本体；短路求值/提前返回见源码
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ candidate_set->Empty  [L733] while_statement@733 (not candidate_set->Empty())
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ reasoning->SetTermination  [L737] while_statement@733 (not candidate_set->Empty()) → if_statement@735 (hops >= inner_search_param.hops_limit) → if_statement@736 (reasoning != nullptr)
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ reasoning->AddSearchHop  [L742] while_statement@733 (not candidate_set->Empty()) → if_statement@741 (reasoning != nullptr)
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ candidate_set->Top  [L744] while_statement@733 (not candidate_set->Empty())
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ inner_search_param.time_cost->CheckOvertime  [L747] while_statement@733 (not candidate_set->Empty()) → if_statement@746 (inner_search_param.time_cost != nullptr and inner_search_param.time_cost->CheckOvertime())
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ ctx->stats->is_timeout.store  [L749] while_statement@733 (not candidate_set->Empty()) → if_statement@746 (inner_search_param.time_cost != nullptr and inner_search_param.time_cost->CheckOvertime()) → if_statement@748 (ctx != nullptr and ctx->stats != nullptr)
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ reasoning->SetTermination  [L752] while_statement@733 (not candidate_set->Empty()) → if_statement@746 (inner_search_param.time_cost != nullptr and inner_search_param.time_cost->CheckOvertime()) → if_statement@751 (reasoning != nullptr)
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ top_candidates->Size  [L758] while_statement@733 (not candidate_set->Empty()) → if_statement@757 (mode == InnerSearchMode::KNN_SEARCH) → if_statement@758 ((-current_node_pair.first) > lower_bound && top_candidates->Size() >= ef)
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ reasoning->SetTermination  [L760] while_statement@733 (not candidate_set->Empty()) → if_statement@757 (mode == InnerSearchMode::KNN_SEARCH) → if_statement@758 ((-current_node_pair.first) > lower_bound && top_candidates->Size() >= ef) → if_statement@759 (reasoning != nullptr)
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ candidate_set->Pop  [L765] while_statement@733 (not candidate_set->Empty())
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ candidate_set->Empty  [L767] while_statement@733 (not candidate_set->Empty()) → if_statement@767 (not candidate_set->Empty())
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ graph->Prefetch  [L768] while_statement@733 (not candidate_set->Empty()) → if_statement@767 (not candidate_set->Empty())
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ candidate_set->Top  [L768] while_statement@733 (not candidate_set->Empty()) → if_statement@767 (not candidate_set->Empty())
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ visit  [L771] while_statement@733 (not candidate_set->Empty())
  │    │    │    │    │    │  ↳ 复用节点 #49 BasicSearcher::visit（本树前文已展开）
  │    │    │    │    │    ├─ skip_strategy.get  [L775] while_statement@733 (not candidate_set->Empty())
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ score_ids  [L781] while_statement@733 (not candidate_set->Empty()) → if_statement@780 (use_custom_distance)
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ to_be_visited_id.data  [L781] while_statement@733 (not candidate_set->Empty()) → if_statement@780 (use_custom_distance)
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ line_dists.data  [L781] while_statement@733 (not candidate_set->Empty()) → if_statement@780 (use_custom_distance)
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ top_candidates->Size  [L783] while_statement@733 (not candidate_set->Empty()) → if_statement@780 (use_custom_distance) [else 分支] → if_statement@782 (inner_search_param.enable_rabitq_one_bit_search and top_candidates->Size() == ef and rabitq_lower_bound_candidates != nullptr)
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ flatten->QueryWithDistanceLowerBound  [L785] while_statement@733 (not candidate_set->Empty()) → if_statement@780 (use_custom_distance) [else 分支] → if_statement@782 (inner_search_param.enable_rabitq_one_bit_search and top_candidates->Size() == ef and rabitq_lower_bound_candidates != nullptr)
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ line_dists.data  [L785] while_statement@733 (not candidate_set->Empty()) → if_statement@780 (use_custom_distance) [else 分支] → if_statement@782 (inner_search_param.enable_rabitq_one_bit_search and top_candidates->Size() == ef and rabitq_lower_bound_candidates != nullptr)
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ lower_bound_dists.data  [L786] while_statement@733 (not candidate_set->Empty()) → if_statement@780 (use_custom_distance) [else 分支] → if_statement@782 (inner_search_param.enable_rabitq_one_bit_search and top_candidates->Size() == ef and rabitq_lower_bound_candidates != nullptr)
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ to_be_visited_id.data  [L788] while_statement@733 (not candidate_set->Empty()) → if_statement@780 (use_custom_distance) [else 分支] → if_statement@782 (inner_search_param.enable_rabitq_one_bit_search and top_candidates->Size() == ef and rabitq_lower_bound_candidates != nullptr)
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ flatten->QueryWithDistanceLowerBound  [L792] while_statement@733 (not candidate_set->Empty()) → if_statement@780 (use_custom_distance) [else 分支] → if_statement@782 (inner_search_param.enable_rabitq_one_bit_search and top_candidates->Size() == ef and rabitq_lower_bound_candidates != nullptr) [else 分支] → if_statement@791 (inner_search_param.enable_rabitq_one_bit_search)
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ line_dists.data  [L792] while_statement@733 (not candidate_set->Empty()) → if_statement@780 (use_custom_distance) [else 分支] → if_statement@782 (inner_search_param.enable_rabitq_one_bit_search and top_candidates->Size() == ef and rabitq_lower_bound_candidates != nullptr) [else 分支] → if_statement@791 (inner_search_param.enable_rabitq_one_bit_search)
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ to_be_visited_id.data  [L795] while_statement@733 (not candidate_set->Empty()) → if_statement@780 (use_custom_distance) [else 分支] → if_statement@782 (inner_search_param.enable_rabitq_one_bit_search and top_candidates->Size() == ef and rabitq_lower_bound_candidates != nullptr) [else 分支] → if_statement@791 (inner_search_param.enable_rabitq_one_bit_search)
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ flatten->Query  [L799] while_statement@733 (not candidate_set->Empty()) → if_statement@780 (use_custom_distance) [else 分支] → if_statement@782 (inner_search_param.enable_rabitq_one_bit_search and top_candidates->Size() == ef and rabitq_lower_bound_candidates != nullptr) [else 分支] → if_statement@791 (inner_search_param.enable_rabitq_one_bit_search) [else 分支]
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ line_dists.data  [L800] while_statement@733 (not candidate_set->Empty()) → if_statement@780 (use_custom_distance) [else 分支] → if_statement@782 (inner_search_param.enable_rabitq_one_bit_search and top_candidates->Size() == ef and rabitq_lower_bound_candidates != nullptr) [else 分支] → if_statement@791 (inner_search_param.enable_rabitq_one_bit_search) [else 分支]
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ to_be_visited_id.data  [L800] while_statement@733 (not candidate_set->Empty()) → if_statement@780 (use_custom_distance) [else 分支] → if_statement@782 (inner_search_param.enable_rabitq_one_bit_search and top_candidates->Size() == ef and rabitq_lower_bound_candidates != nullptr) [else 分支] → if_statement@791 (inner_search_param.enable_rabitq_one_bit_search) [else 分支]
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ reasoning->RecordVisit  [L808] while_statement@733 (not candidate_set->Empty()) → for_statement@804 i < count_no_visited → if_statement@807 (reasoning != nullptr)
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ graph->GetDuplicateIds  [L811] while_statement@733 (not candidate_set->Empty()) → for_statement@804 i < count_no_visited → if_statement@810 (use_custom_distance and inner_search_param.consider_duplicate)
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ score_duplicates  [L812] while_statement@733 (not candidate_set->Empty()) → for_statement@804 i < count_no_visited → if_statement@810 (use_custom_distance and inner_search_param.consider_duplicate)
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ is_finite_distance  [L814] while_statement@733 (not candidate_set->Empty()) → for_statement@804 i < count_no_visited → if_statement@814 (not is_finite_distance(dist))
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ candidate_set->Push  [L815] while_statement@733 (not candidate_set->Empty()) → for_statement@804 i < count_no_visited → if_statement@814 (not is_finite_distance(dist))
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ traversal_priority  [L815] while_statement@733 (not candidate_set->Empty()) → for_statement@804 i < count_no_visited → if_statement@814 (not is_finite_distance(dist))
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ is_result_distance_eligible<mode>  [L817] while_statement@733 (not candidate_set->Empty()) → for_statement@804 i < count_no_visited → if_statement@814 (not is_finite_distance(dist)) → lambda@816（定义体，执行时间取决于调用/调度） → if_statement@817 (not is_result_distance_eligible<mode>(dist, inner_search_param) or not check_func(result_id))
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ check_func  [L818] while_statement@733 (not candidate_set->Empty()) → for_statement@804 i < count_no_visited → if_statement@814 (not is_finite_distance(dist)) → lambda@816（定义体，执行时间取决于调用/调度） → if_statement@817 (not is_result_distance_eligible<mode>(dist, inner_search_param) or not check_func(result_id))
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ top_candidates->Push  [L821] while_statement@733 (not candidate_set->Empty()) → for_statement@804 i < count_no_visited → if_statement@814 (not is_finite_distance(dist)) → lambda@816（定义体，执行时间取决于调用/调度）
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ top_candidates->Size  [L823] while_statement@733 (not candidate_set->Empty()) → for_statement@804 i < count_no_visited → if_statement@814 (not is_finite_distance(dist)) → lambda@816（定义体，执行时间取决于调用/调度） → if_statement@822 (mode == KNN_SEARCH) → while_statement@823 (top_candidates->Size() > ef)
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ reasoning->RecordEviction  [L825] while_statement@733 (not candidate_set->Empty()) → for_statement@804 i < count_no_visited → if_statement@814 (not is_finite_distance(dist)) → lambda@816（定义体，执行时间取决于调用/调度） → if_statement@822 (mode == KNN_SEARCH) → while_statement@823 (top_candidates->Size() > ef) → if_statement@824 (reasoning != nullptr)
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ top_candidates->Top  [L825] while_statement@733 (not candidate_set->Empty()) → for_statement@804 i < count_no_visited → if_statement@814 (not is_finite_distance(dist)) → lambda@816（定义体，执行时间取决于调用/调度） → if_statement@822 (mode == KNN_SEARCH) → while_statement@823 (top_candidates->Size() > ef) → if_statement@824 (reasoning != nullptr)
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ top_candidates->Pop  [L827] while_statement@733 (not candidate_set->Empty()) → for_statement@804 i < count_no_visited → if_statement@814 (not is_finite_distance(dist)) → lambda@816（定义体，执行时间取决于调用/调度） → if_statement@822 (mode == KNN_SEARCH) → while_statement@823 (top_candidates->Size() > ef)
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ top_candidates->Pop  [L830] while_statement@733 (not candidate_set->Empty()) → for_statement@804 i < count_no_visited → if_statement@814 (not is_finite_distance(dist)) → lambda@816（定义体，执行时间取决于调用/调度） → if_statement@822 (mode == KNN_SEARCH) [else 分支] → if_statement@829 (dist > inner_search_param.radius)
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ push_result  [L833] while_statement@733 (not candidate_set->Empty()) → for_statement@804 i < count_no_visited → if_statement@814 (not is_finite_distance(dist))
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ graph->GetDuplicateIds  [L835] while_statement@733 (not candidate_set->Empty()) → for_statement@804 i < count_no_visited → if_statement@814 (not is_finite_distance(dist)) → if_statement@834 (inner_search_param.consider_duplicate and not use_custom_distance) → for_range_loop@835
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ push_result  [L836] while_statement@733 (not candidate_set->Empty()) → for_statement@804 i < count_no_visited → if_statement@814 (not is_finite_distance(dist)) → if_statement@834 (inner_search_param.consider_duplicate and not use_custom_distance) → for_range_loop@835
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ top_candidates->Empty  [L839] while_statement@733 (not candidate_set->Empty()) → for_statement@804 i < count_no_visited → if_statement@814 (not is_finite_distance(dist)) → if_statement@839 (not top_candidates->Empty())
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ top_candidates->Top  [L840] while_statement@733 (not candidate_set->Empty()) → for_statement@804 i < count_no_visited → if_statement@814 (not is_finite_distance(dist)) → if_statement@839 (not top_candidates->Empty())
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ check_func  [L846] while_statement@733 (not candidate_set->Empty()) → for_statement@804 i < count_no_visited → if_statement@844 (mode == KNN_SEARCH) → if_statement@845 (collect_rabitq_lower_bound and lower_bound_dists[i] < lower_bound and check_func(cur_id))
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ rabitq_lower_bound_candidates->emplace_back  [L847] while_statement@733 (not candidate_set->Empty()) → for_statement@804 i < count_no_visited → if_statement@844 (mode == KNN_SEARCH) → if_statement@845 (collect_rabitq_lower_bound and lower_bound_dists[i] < lower_bound and check_func(cur_id))
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ top_candidates->Size  [L850] while_statement@733 (not candidate_set->Empty()) → for_statement@804 i < count_no_visited → if_statement@850 (top_candidates->Size() < ef || lower_bound > dist || (mode == RANGE_SEARCH && dist <= inner_search_param.radius))
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ candidate_set->Push  [L852] while_statement@733 (not candidate_set->Empty()) → for_statement@804 i < count_no_visited → if_statement@850 (top_candidates->Size() < ef || lower_bound > dist || (mode == RANGE_SEARCH && dist <= inner_search_param.radius))
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ check_func  [L854] while_statement@733 (not candidate_set->Empty()) → for_statement@804 i < count_no_visited → if_statement@850 (top_candidates->Size() < ef || lower_bound > dist || (mode == RANGE_SEARCH && dist <= inner_search_param.radius)) → if_statement@854 (check_func(cur_id))
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ top_candidates->Push  [L855] while_statement@733 (not candidate_set->Empty()) → for_statement@804 i < count_no_visited → if_statement@850 (top_candidates->Size() < ef || lower_bound > dist || (mode == RANGE_SEARCH && dist <= inner_search_param.radius)) → if_statement@854 (check_func(cur_id))
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ reasoning->RecordFilterReject  [L857] while_statement@733 (not candidate_set->Empty()) → for_statement@804 i < count_no_visited → if_statement@850 (top_candidates->Size() < ef || lower_bound > dist || (mode == RANGE_SEARCH && dist <= inner_search_param.radius)) → if_statement@854 (check_func(cur_id)) [else 分支] → if_statement@856 (reasoning != nullptr)
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ graph->GetDuplicateIds  [L860] while_statement@733 (not candidate_set->Empty()) → for_statement@804 i < count_no_visited → if_statement@850 (top_candidates->Size() < ef || lower_bound > dist || (mode == RANGE_SEARCH && dist <= inner_search_param.radius)) → if_statement@859 (inner_search_param.consider_duplicate and not use_custom_distance)
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ check_func  [L862] while_statement@733 (not candidate_set->Empty()) → for_statement@804 i < count_no_visited → if_statement@850 (top_candidates->Size() < ef || lower_bound > dist || (mode == RANGE_SEARCH && dist <= inner_search_param.radius)) → if_statement@859 (inner_search_param.consider_duplicate and not use_custom_distance) → for_range_loop@861 → if_statement@862 (check_func(item))
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ top_candidates->Push  [L863] while_statement@733 (not candidate_set->Empty()) → for_statement@804 i < count_no_visited → if_statement@850 (top_candidates->Size() < ef || lower_bound > dist || (mode == RANGE_SEARCH && dist <= inner_search_param.radius)) → if_statement@859 (inner_search_param.consider_duplicate and not use_custom_distance) → for_range_loop@861 → if_statement@862 (check_func(item))
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ top_candidates->Size  [L869] while_statement@733 (not candidate_set->Empty()) → for_statement@804 i < count_no_visited → if_statement@850 (top_candidates->Size() < ef || lower_bound > dist || (mode == RANGE_SEARCH && dist <= inner_search_param.radius)) → if_statement@868 (mode == KNN_SEARCH) → if_statement@869 (top_candidates->Size() > ef)
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ reasoning->RecordEviction  [L871] while_statement@733 (not candidate_set->Empty()) → for_statement@804 i < count_no_visited → if_statement@850 (top_candidates->Size() < ef || lower_bound > dist || (mode == RANGE_SEARCH && dist <= inner_search_param.radius)) → if_statement@868 (mode == KNN_SEARCH) → if_statement@869 (top_candidates->Size() > ef) → if_statement@870 (reasoning != nullptr)
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ top_candidates->Top  [L871] while_statement@733 (not candidate_set->Empty()) → for_statement@804 i < count_no_visited → if_statement@850 (top_candidates->Size() < ef || lower_bound > dist || (mode == RANGE_SEARCH && dist <= inner_search_param.radius)) → if_statement@868 (mode == KNN_SEARCH) → if_statement@869 (top_candidates->Size() > ef) → if_statement@870 (reasoning != nullptr)
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ top_candidates->Pop  [L873] while_statement@733 (not candidate_set->Empty()) → for_statement@804 i < count_no_visited → if_statement@850 (top_candidates->Size() < ef || lower_bound > dist || (mode == RANGE_SEARCH && dist <= inner_search_param.radius)) → if_statement@868 (mode == KNN_SEARCH) → if_statement@869 (top_candidates->Size() > ef)
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ top_candidates->Empty  [L877] while_statement@733 (not candidate_set->Empty()) → for_statement@804 i < count_no_visited → if_statement@850 (top_candidates->Size() < ef || lower_bound > dist || (mode == RANGE_SEARCH && dist <= inner_search_param.radius)) → if_statement@877 (not top_candidates->Empty())
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ top_candidates->Top  [L878] while_statement@733 (not candidate_set->Empty()) → for_statement@804 i < count_no_visited → if_statement@850 (top_candidates->Size() < ef || lower_bound > dist || (mode == RANGE_SEARCH && dist <= inner_search_param.radius)) → if_statement@877 (not top_candidates->Empty())
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ top_candidates->Size  [L885] if_statement@884 (mode == KNN_SEARCH) → while_statement@885 (top_candidates->Size() > inner_search_param.topk)
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ top_candidates->Pop  [L886] if_statement@884 (mode == KNN_SEARCH) → while_statement@885 (top_candidates->Size() > inner_search_param.topk)
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ top_candidates->Size  [L890] if_statement@884 (mode == KNN_SEARCH) [else 分支] → if_statement@888 (mode == RANGE_SEARCH) → if_statement@889 (inner_search_param.range_search_limit_size > 0) → while_statement@890 (top_candidates->Size() > inner_search_param.range_search_limit_size)
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ top_candidates->Pop  [L891] if_statement@884 (mode == KNN_SEARCH) [else 分支] → if_statement@888 (mode == RANGE_SEARCH) → if_statement@889 (inner_search_param.range_search_limit_size > 0) → while_statement@890 (top_candidates->Size() > inner_search_param.range_search_limit_size)
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ top_candidates->Empty  [L894] if_statement@884 (mode == KNN_SEARCH) [else 分支] → if_statement@888 (mode == RANGE_SEARCH) → while_statement@894 (not top_candidates->Empty() && top_candidates->Top().first > inner_search_param.radius + THRESHOLD_ERROR)
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ top_candidates->Top  [L895] if_statement@884 (mode == KNN_SEARCH) [else 分支] → if_statement@888 (mode == RANGE_SEARCH) → while_statement@894 (not top_candidates->Empty() && top_candidates->Top().first > inner_search_param.radius + THRESHOLD_ERROR)
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ top_candidates->Pop  [L896] if_statement@884 (mode == KNN_SEARCH) [else 分支] → if_statement@888 (mode == RANGE_SEARCH) → while_statement@894 (not top_candidates->Empty() && top_candidates->Top().first > inner_search_param.radius + THRESHOLD_ERROR)
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ top_candidates->Empty  [L902] if_statement@901 (not use_custom_distance and inner_search_param.find_duplicate and not top_candidates->Empty())
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ top_candidates->GetData  [L903] if_statement@901 (not use_custom_distance and inner_search_param.find_duplicate and not top_candidates->Empty())
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ top_candidates->Size  [L906] if_statement@901 (not use_custom_distance and inner_search_param.find_duplicate and not top_candidates->Empty()) → for_statement@906 i < top_candidates->Size()
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ flatten->TotalCount  [L918] if_statement@901 (not use_custom_distance and inner_search_param.find_duplicate and not top_candidates->Empty()) → if_statement@912 (inner_search_param.duplicate_distance_threshold > 0.0F) [else 分支]
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ flatten->CompareVectors  [L921] if_statement@901 (not use_custom_distance and inner_search_param.find_duplicate and not top_candidates->Empty()) → if_statement@912 (inner_search_param.duplicate_distance_threshold > 0.0F) [else 分支] → conditional_expression@920 has_stored_query
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ flatten->CompareRawVectorWithId  [L922] if_statement@901 (not use_custom_distance and inner_search_param.find_duplicate and not top_candidates->Empty()) → if_statement@912 (inner_search_param.duplicate_distance_threshold > 0.0F) [else 分支] → conditional_expression@920 has_stored_query
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ stats.dist_cmp.fetch_add  [L931] if_statement@929 (ctx != nullptr and ctx->stats != nullptr)
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ stats.hops.fetch_add  [L932] if_statement@929 (ctx != nullptr and ctx->stats != nullptr)
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ this->search_impl<RANGE_SEARCH>  [L96] 函数本体；短路求值/提前返回见源码
  │    │    │    │    │  ├─ 以下为分派/重载候选，并非全部依次执行
  │    │    │    │    │  ↳ 复用节点 #48 BasicSearcher::search_impl（本树前文已展开）
  │    │    │    │    │  ↳ 复用节点 #50 BasicSearcher::search_impl（本树前文已展开）
  │    │    │    │    │  ↳ 复用节点 #51 BasicSearcher::search_impl（本树前文已展开）
  │    │    │    │  #52 BasicSearcher::Search [src/impl/searcher/basic_searcher.cpp:139]
  │    │    │    │    ├─ this->search_impl<KNN_SEARCH>  [L148] 函数本体；短路求值/提前返回见源码
  │    │    │    │    │  ├─ 以下为分派/重载候选，并非全部依次执行
  │    │    │    │    │  ↳ 复用节点 #48 BasicSearcher::search_impl（本树前文已展开）
  │    │    │    │    │  ↳ 复用节点 #50 BasicSearcher::search_impl（本树前文已展开）
  │    │    │    │    │  ↳ 复用节点 #51 BasicSearcher::search_impl（本树前文已展开）
  │    │    │    │  #53 BasicSearcher::Search [src/impl/searcher/basic_searcher.cpp:158]
  │    │    │    │    ├─ this->search_impl<InnerSearchMode::RANGE_SEARCH>  [L166] if_statement@165 (inner_search_param.search_mode == InnerSearchMode::RANGE_SEARCH)
  │    │    │    │    │  ├─ 以下为分派/重载候选，并非全部依次执行
  │    │    │    │    │  ↳ 复用节点 #48 BasicSearcher::search_impl（本树前文已展开）
  │    │    │    │    │  ↳ 复用节点 #50 BasicSearcher::search_impl（本树前文已展开）
  │    │    │    │    │  ↳ 复用节点 #51 BasicSearcher::search_impl（本树前文已展开）
  │    │    │    │    ├─ this->search_impl<InnerSearchMode::KNN_SEARCH>  [L169] 函数本体；短路求值/提前返回见源码
  │    │    │    │    │  ├─ 以下为分派/重载候选，并非全部依次执行
  │    │    │    │    │  ↳ 复用节点 #48 BasicSearcher::search_impl（本树前文已展开）
  │    │    │    │    │  ↳ 复用节点 #50 BasicSearcher::search_impl（本树前文已展开）
  │    │    │    │    │  ↳ 复用节点 #51 BasicSearcher::search_impl（本树前文已展开）
  │    │    │    ├─ top_candidates->Empty  [L137] while_statement@137 (not top_candidates->Empty())
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ top_candidates->Top  [L138] while_statement@137 (not top_candidates->Empty())
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ heap->Push  [L139] while_statement@137 (not top_candidates->Empty())
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ top_candidates->Pop  [L140] while_statement@137 (not top_candidates->Empty())
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ heap->Size  [L142] while_statement@142 (heap->Size() > result_limit)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ heap->Pop  [L143] while_statement@142 (heap->Size() > result_limit)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ flat_searcher_->Search  [L64] if_statement@53 (graph_fresh && bucket_size >= graph_build_threshold_) [else 分支]
  │    │    │  ↳ 复用节点 #37 FlatBucketSearcher::Search（本树前文已展开）
  │    ├─ this->thread_pool_->GeneralEnqueue  [L275] if_statement@273 (this->thread_pool_ != nullptr and search_thread_count > 1) → for_statement@274 thread_id < search_thread_count
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ futures.emplace_back  [L276] if_statement@273 (this->thread_pool_ != nullptr and search_thread_count > 1) → for_statement@274 thread_id < search_thread_count
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ std::move  [L276] if_statement@273 (this->thread_pool_ != nullptr and search_thread_count > 1) → for_statement@274 thread_id < search_thread_count
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ search_func  [L279] if_statement@273 (this->thread_pool_ != nullptr and search_thread_count > 1) [else 分支]
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ future.get  [L285] if_statement@283 (this->thread_pool_ != nullptr and search_thread_count > 1) → for_range_loop@284
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ DistanceHeap::MakeInstanceBySize<true, true>  [L287] if_statement@283 (this->thread_pool_ != nullptr and search_thread_count > 1)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ heap->Size  [L289] if_statement@283 (this->thread_pool_ != nullptr and search_thread_count > 1) → for_range_loop@288
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ heap->GetData  [L290] if_statement@283 (this->thread_pool_ != nullptr and search_thread_count > 1) → for_range_loop@288
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ search_result->Size  [L293] if_statement@283 (this->thread_pool_ != nullptr and search_thread_count > 1) → for_range_loop@288 → for_statement@291 i < size → if_statement@292 (reasoning_ctx != nullptr and search_result->Size() >= static_cast<uint64_t>(topk) and data[i].first < search_result->Top().first)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ search_result->Top  [L294] if_statement@283 (this->thread_pool_ != nullptr and search_thread_count > 1) → for_range_loop@288 → for_statement@291 i < size → if_statement@292 (reasoning_ctx != nullptr and search_result->Size() >= static_cast<uint64_t>(topk) and data[i].first < search_result->Top().first)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ reasoning_ctx->RecordEviction  [L295] if_statement@283 (this->thread_pool_ != nullptr and search_thread_count > 1) → for_range_loop@288 → for_statement@291 i < size → if_statement@292 (reasoning_ctx != nullptr and search_result->Size() >= static_cast<uint64_t>(topk) and data[i].first < search_result->Top().first)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ search_result->Top  [L295] if_statement@283 (this->thread_pool_ != nullptr and search_thread_count > 1) → for_range_loop@288 → for_statement@291 i < size → if_statement@292 (reasoning_ctx != nullptr and search_result->Size() >= static_cast<uint64_t>(topk) and data[i].first < search_result->Top().first)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ search_result->Push  [L298] if_statement@283 (this->thread_pool_ != nullptr and search_thread_count > 1) → for_range_loop@288 → for_statement@291 i < size
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ search_result->Empty  [L306] if_statement@304 (buckets_per_data_ > 1) → while_statement@306 (!search_result->Empty())
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ search_result->Top  [L307] if_statement@304 (buckets_per_data_ > 1) → while_statement@306 (!search_result->Empty())
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ id_to_min_dist.find  [L310] if_statement@304 (buckets_per_data_ > 1) → while_statement@306 (!search_result->Empty()) → if_statement@310 (id_to_min_dist.find(origin_id) == id_to_min_dist.end() || dist_val < id_to_min_dist[origin_id])
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ id_to_min_dist.end  [L310] if_statement@304 (buckets_per_data_ > 1) → while_statement@306 (!search_result->Empty()) → if_statement@310 (id_to_min_dist.find(origin_id) == id_to_min_dist.end() || dist_val < id_to_min_dist[origin_id])
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ search_result->Pop  [L314] if_statement@304 (buckets_per_data_ > 1) → while_statement@306 (!search_result->Empty())
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ std::numeric_limits<float>::max  [L317] if_statement@304 (buckets_per_data_ > 1)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ search_result->Push  [L320] if_statement@304 (buckets_per_data_ > 1) → for_range_loop@318 → if_statement@319 (dist_val < cur_heap_top2)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ search_result->Size  [L322] if_statement@304 (buckets_per_data_ > 1) → for_range_loop@318 → if_statement@322 (search_result->Size() > origin_topk)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ search_result->Pop  [L323] if_statement@304 (buckets_per_data_ > 1) → for_range_loop@318 → if_statement@322 (search_result->Size() > origin_topk)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ search_result->Empty  [L325] if_statement@304 (buckets_per_data_ > 1) → for_range_loop@318 → if_statement@325 (not search_result->Empty() and search_result->Size() == origin_topk)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ search_result->Size  [L325] if_statement@304 (buckets_per_data_ > 1) → for_range_loop@318 → if_statement@325 (not search_result->Empty() and search_result->Size() == origin_topk)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ search_result->Top  [L326] if_statement@304 (buckets_per_data_ > 1) → for_range_loop@318 → if_statement@325 (not search_result->Empty() and search_result->Size() == origin_topk)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ reasoning_ctx.get  [L736] if_statement@725 (is_range)
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ search_result->Size  [L739] if_statement@725 (is_range) → if_statement@737 (use_reorder_ and param.enable_reorder) → conditional_expression@738 (request.limited_size_ > 0)
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ reorder  [L740] if_statement@725 (is_range) → if_statement@737 (use_reorder_ and param.enable_reorder)
  │  #54 IVF::reorder [src/algorithm/ivf/ivf_search.cpp:183]
  │    ├─ reorder_->Reorder  [L192] 函数本体；短路求值/提前返回见源码
  │    │  ├─ 以下为分派/重载候选，并非全部依次执行
  │    │  #55 BucketReorder::Reorder [src/impl/reorder/bucket_reorder.cpp:28]
  │    │    ├─ VsagException  [L37] if_statement@36 (iter_ctx != nullptr)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ VsagException  [L41] if_statement@40 (rabitq_lower_bound_candidates != nullptr)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ select_query_allocator  [L45] 函数本体；短路求值/提前返回见源码
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ input->Size  [L46] conditional_expression@46 input == nullptr
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ std::min  [L47] 函数本体；短路求值/提前返回见源码
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ std::make_shared<StandardHeap<true, false>>  [L48] 函数本体；短路求值/提前返回见源码
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ ctx.stats->reorder_distance_count.fetch_add  [L54] if_statement@53 (ctx.stats != nullptr)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ bucket_->FactoryComputer  [L58] 函数本体；短路求值/提前返回见源码
  │    │    │  ↳ 复用节点 #13 BucketDataCell<QuantTmpl, IOTmpl>::FactoryComputer（本树前文已展开）
  │    │    ├─ input->GetData  [L59] 函数本体；短路求值/提前返回见源码
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ location_resolver_  [L64] for_statement@63 i < candidate_count
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ bucket_->Query  [L68] 函数本体；短路求值/提前返回见源码
  │    │    │  #56 BucketDataCell::Query [src/datacell/bucket_datacell.h:82]
  │    │    │    ├─ GetQuantizerName  [L89] if_statement@89 (id_count > 0 and GetQuantizerName() == QUANTIZATION_TYPE_VALUE_PQFS)
  │    │    │    │  #57 BucketDataCell::GetQuantizerName [src/datacell/bucket_datacell.h:170]
  │    │    │    │    ├─ this->quantizer_->Name  [L172] 函数本体；短路求值/提前返回见源码
  │    │    │    │    │  #58 Quantizer::Name [src/quantization/quantizer.h:300]
  │    │    │    │    │    ├─ cast().NameImpl  [L302] 函数本体；短路求值/提前返回见源码
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ cast  [L302] 函数本体；短路求值/提前返回见源码
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ VsagException  [L90] if_statement@89 (id_count > 0 and GetQuantizerName() == QUANTIZATION_TYPE_VALUE_PQFS)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ computer.get  [L94] 函数本体；短路求值/提前返回见源码
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ this->query  [L95] 函数本体；短路求值/提前返回见源码
  │    │    │    │  #59 BucketDataCell<QuantTmpl, IOTmpl>::query [src/datacell/bucket_datacell.h:380]
  │    │    │    │    ├─ select_query_allocator  [L397] 函数本体；短路求值/提前返回见源码
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ requests.reserve  [L399] 函数本体；短路求值/提前返回见源码
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ check_valid_bucket_id  [L401] for_statement@400 i < id_count
  │    │    │    │    │  ↳ 复用节点 #22 BucketDataCell::check_valid_bucket_id（本树前文已展开）
  │    │    │    │    ├─ requests.emplace_back  [L402] for_statement@400 i < id_count
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ std::sort  [L404] 函数本体；短路求值/提前返回见源码
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ requests.begin  [L404] 函数本体；短路求值/提前返回见源码
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ requests.end  [L404] 函数本体；短路求值/提前返回见源码
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ unique_offsets.reserve  [L419] 函数本体；短路求值/提前返回见源码
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ read_sizes.reserve  [L420] 函数本体；短路求值/提前返回见源码
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ read_offsets.reserve  [L421] 函数本体；短路求值/提前返回见源码
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ requests.size  [L425] while_statement@425 (group_begin < requests.size())
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ requests.size  [L428] while_statement@425 (group_begin < requests.size()) → while_statement@428 (group_end < requests.size() and requests[group_end].bucket_id == bucket_id)
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ VsagException  [L436] while_statement@425 (group_begin < requests.size()) → for_statement@433 i < group_end → if_statement@435 (offset_id >= this->bucket_sizes_[bucket_id])
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ VsagException  [L439] while_statement@425 (group_begin < requests.size()) → for_statement@433 i < group_end → if_statement@438 (this->inner_ids_[bucket_id][offset_id] == EMPTY_INNER_ID)
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ fmt::format  [L441] while_statement@425 (group_begin < requests.size()) → for_statement@433 i < group_end → if_statement@438 (this->inner_ids_[bucket_id][offset_id] == EMPTY_INNER_ID)
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ unique_offsets.clear  [L447] while_statement@425 (group_begin < requests.size())
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ unique_offsets.empty  [L450] while_statement@425 (group_begin < requests.size()) → for_statement@448 i < group_end → if_statement@450 (unique_offsets.empty() or unique_offsets.back() != offset_id)
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ unique_offsets.back  [L450] while_statement@425 (group_begin < requests.size()) → for_statement@448 i < group_end → if_statement@450 (unique_offsets.empty() or unique_offsets.back() != offset_id)
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ unique_offsets.emplace_back  [L451] while_statement@425 (group_begin < requests.size()) → for_statement@448 i < group_end → if_statement@450 (unique_offsets.empty() or unique_offsets.back() != offset_id)
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ read_sizes.clear  [L455] while_statement@425 (group_begin < requests.size())
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ read_offsets.clear  [L456] while_statement@425 (group_begin < requests.size())
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ read_offsets.empty  [L458] while_statement@425 (group_begin < requests.size()) → for_range_loop@457 → if_statement@458 (not read_offsets.empty() and read_offsets.back() + read_sizes.back() == static_cast<uint64_t>(offset_id) * code_size_ and code_size_ <= static_cast<uint64_t>(std::numeric_limits<int32_t>::max()) and read_sizes.back() <= static_cast<uint64_t>(std::numeric_limits<int32_t>::max()) - code_size_)
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ read_offsets.back  [L459] while_statement@425 (group_begin < requests.size()) → for_range_loop@457 → if_statement@458 (not read_offsets.empty() and read_offsets.back() + read_sizes.back() == static_cast<uint64_t>(offset_id) * code_size_ and code_size_ <= static_cast<uint64_t>(std::numeric_limits<int32_t>::max()) and read_sizes.back() <= static_cast<uint64_t>(std::numeric_limits<int32_t>::max()) - code_size_)
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ read_sizes.back  [L459] while_statement@425 (group_begin < requests.size()) → for_range_loop@457 → if_statement@458 (not read_offsets.empty() and read_offsets.back() + read_sizes.back() == static_cast<uint64_t>(offset_id) * code_size_ and code_size_ <= static_cast<uint64_t>(std::numeric_limits<int32_t>::max()) and read_sizes.back() <= static_cast<uint64_t>(std::numeric_limits<int32_t>::max()) - code_size_)
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ std::numeric_limits<int32_t>::max  [L461] while_statement@425 (group_begin < requests.size()) → for_range_loop@457 → if_statement@458 (not read_offsets.empty() and read_offsets.back() + read_sizes.back() == static_cast<uint64_t>(offset_id) * code_size_ and code_size_ <= static_cast<uint64_t>(std::numeric_limits<int32_t>::max()) and read_sizes.back() <= static_cast<uint64_t>(std::numeric_limits<int32_t>::max()) - code_size_)
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ read_sizes.back  [L462] while_statement@425 (group_begin < requests.size()) → for_range_loop@457 → if_statement@458 (not read_offsets.empty() and read_offsets.back() + read_sizes.back() == static_cast<uint64_t>(offset_id) * code_size_ and code_size_ <= static_cast<uint64_t>(std::numeric_limits<int32_t>::max()) and read_sizes.back() <= static_cast<uint64_t>(std::numeric_limits<int32_t>::max()) - code_size_)
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ std::numeric_limits<int32_t>::max  [L463] while_statement@425 (group_begin < requests.size()) → for_range_loop@457 → if_statement@458 (not read_offsets.empty() and read_offsets.back() + read_sizes.back() == static_cast<uint64_t>(offset_id) * code_size_ and code_size_ <= static_cast<uint64_t>(std::numeric_limits<int32_t>::max()) and read_sizes.back() <= static_cast<uint64_t>(std::numeric_limits<int32_t>::max()) - code_size_)
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ read_sizes.back  [L464] while_statement@425 (group_begin < requests.size()) → for_range_loop@457 → if_statement@458 (not read_offsets.empty() and read_offsets.back() + read_sizes.back() == static_cast<uint64_t>(offset_id) * code_size_ and code_size_ <= static_cast<uint64_t>(std::numeric_limits<int32_t>::max()) and read_sizes.back() <= static_cast<uint64_t>(std::numeric_limits<int32_t>::max()) - code_size_)
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ read_sizes.emplace_back  [L466] while_statement@425 (group_begin < requests.size()) → for_range_loop@457 → if_statement@458 (not read_offsets.empty() and read_offsets.back() + read_sizes.back() == static_cast<uint64_t>(offset_id) * code_size_ and code_size_ <= static_cast<uint64_t>(std::numeric_limits<int32_t>::max()) and read_sizes.back() <= static_cast<uint64_t>(std::numeric_limits<int32_t>::max()) - code_size_) [else 分支]
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ read_offsets.emplace_back  [L467] while_statement@425 (group_begin < requests.size()) → for_range_loop@457 → if_statement@458 (not read_offsets.empty() and read_offsets.back() + read_sizes.back() == static_cast<uint64_t>(offset_id) * code_size_ and code_size_ <= static_cast<uint64_t>(std::numeric_limits<int32_t>::max()) and read_sizes.back() <= static_cast<uint64_t>(std::numeric_limits<int32_t>::max()) - code_size_) [else 分支]
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ this->datas_[bucket_id].MultiRead  [L475] while_statement@425 (group_begin < requests.size())
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ read_sizes.data  [L476] while_statement@425 (group_begin < requests.size())
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ read_offsets.data  [L476] while_statement@425 (group_begin < requests.size())
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ read_sizes.size  [L476] while_statement@425 (group_begin < requests.size())
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ VsagException  [L479] while_statement@425 (group_begin < requests.size()) → if_statement@478 (not read_success)
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ read_sizes.size  [L481] while_statement@425 (group_begin < requests.size())
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ computer->ScanBatchDists  [L484] while_statement@425 (group_begin < requests.size())
  │    │    │    │    │  ├─ 以下为分派/重载候选，并非全部依次执行
  │    │    │    │    │  ↳ 复用节点 #40 Computer::ScanBatchDists（本树前文已展开）
  │    │    │    │    │  ↳ 复用节点 #44 Computer<TransformQuantizer<QuantImpl, metric>>::ScanBatchDists（本树前文已展开）
  │    │    │    │    ├─ unique_offsets.size  [L484] while_statement@425 (group_begin < requests.size())
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ unique_dists.data  [L484] while_statement@425 (group_begin < requests.size())
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ this->quantizer_->GetDim  [L486] while_statement@425 (group_begin < requests.size()) → if_statement@485 (use_residual_)
  │    │    │    │    │  ↳ 复用节点 #15 Quantizer::GetDim（本树前文已展开）
  │    │    │    │    ├─ strategy_->GetCentroid  [L487] while_statement@425 (group_begin < requests.size()) → if_statement@485 (use_residual_)
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ FP32ComputeIP  [L488] while_statement@425 (group_begin < requests.size()) → if_statement@485 (use_residual_)
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ computer->raw_query_.data  [L489] while_statement@425 (group_begin < requests.size()) → if_statement@485 (use_residual_)
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ centroid.data  [L489] while_statement@425 (group_begin < requests.size()) → if_statement@485 (use_residual_)
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ this->quantizer_->GetDim  [L489] while_statement@425 (group_begin < requests.size()) → if_statement@485 (use_residual_)
  │    │    │    │    │  ↳ 复用节点 #15 Quantizer::GetDim（本树前文已展开）
  │    │    │    │    ├─ unique_offsets.size  [L492] while_statement@425 (group_begin < requests.size()) → if_statement@485 (use_residual_) → if_statement@490 (metric_ == MetricType::METRIC_TYPE_L2SQR) → for_statement@492 i < unique_offsets.size()
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ unique_offsets.size  [L496] while_statement@425 (group_begin < requests.size()) → if_statement@485 (use_residual_) → for_statement@496 i < unique_offsets.size()
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ ctx->stats->io_cnt.fetch_add  [L513] if_statement@511 (not IOTmpl::InMemory) → if_statement@512 (ctx != nullptr and ctx->stats != nullptr)
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ ctx->stats->io_time_ms.fetch_add  [L515] if_statement@511 (not IOTmpl::InMemory) → if_statement@512 (ctx != nullptr and ctx->stats != nullptr)
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ precise_distances.data  [L68] 函数本体；短路求值/提前返回见源码
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ bucket_ids.data  [L70] 函数本体；短路求值/提前返回见源码
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ offset_ids.data  [L71] 函数本体；短路求值/提前返回见源码
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ ctx.reasoning_ctx->RecordReorder  [L78] for_statement@74 i < candidate_count → if_statement@77 (ctx.reasoning_ctx != nullptr)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ distance_threshold.has_value  [L80] for_statement@74 i < candidate_count → if_statement@80 (distance_threshold.has_value() and (not std::isfinite(precise_distance) or precise_distance > distance_threshold.value()))
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ std::isfinite  [L80] for_statement@74 i < candidate_count → if_statement@80 (distance_threshold.has_value() and (not std::isfinite(precise_distance) or precise_distance > distance_threshold.value()))
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ distance_threshold.value  [L81] for_statement@74 i < candidate_count → if_statement@80 (distance_threshold.has_value() and (not std::isfinite(precise_distance) or precise_distance > distance_threshold.value()))
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ reorder_heap->Size  [L84] for_statement@74 i < candidate_count → if_statement@84 (reorder_heap->Size() < topk or precise_distance < reorder_heap->Top().first)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ reorder_heap->Top  [L84] for_statement@74 i < candidate_count → if_statement@84 (reorder_heap->Size() < topk or precise_distance < reorder_heap->Top().first)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ reorder_heap->Push  [L85] for_statement@74 i < candidate_count → if_statement@84 (reorder_heap->Size() < topk or precise_distance < reorder_heap->Top().first)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ reorder_heap->Size  [L86] for_statement@74 i < candidate_count → if_statement@84 (reorder_heap->Size() < topk or precise_distance < reorder_heap->Top().first) → if_statement@86 (reorder_heap->Size() > topk)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ ctx.reasoning_ctx->RecordReorderEviction  [L88] for_statement@74 i < candidate_count → if_statement@84 (reorder_heap->Size() < topk or precise_distance < reorder_heap->Top().first) → if_statement@86 (reorder_heap->Size() > topk) → if_statement@87 (ctx.reasoning_ctx != nullptr)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ reorder_heap->Top  [L88] for_statement@74 i < candidate_count → if_statement@84 (reorder_heap->Size() < topk or precise_distance < reorder_heap->Top().first) → if_statement@86 (reorder_heap->Size() > topk) → if_statement@87 (ctx.reasoning_ctx != nullptr)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ reorder_heap->Pop  [L90] for_statement@74 i < candidate_count → if_statement@84 (reorder_heap->Size() < topk or precise_distance < reorder_heap->Top().first) → if_statement@86 (reorder_heap->Size() > topk)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │  #60 FlattenReorder::Reorder [src/impl/reorder/flatten_reorder.cpp:156]
  │    │    ├─ select_query_allocator  [L165] 函数本体；短路求值/提前返回见源码
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ distance_threshold.has_value  [L167] lambda@166（定义体，执行时间取决于调用/调度）
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ IsFiniteRaBitQValue  [L168] lambda@166（定义体，执行时间取决于调用/调度）
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ distance_threshold.value  [L168] lambda@166（定义体，执行时间取决于调用/调度）
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ is_distance_eligible  [L171] lambda@170（定义体，执行时间取决于调用/调度） → if_statement@171 (is_distance_eligible(distance))
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ iter_ctx->SetPoint  [L175] lambda@170（定义体，执行时间取决于调用/调度） → if_statement@174 (iter_ctx != nullptr)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ input->Size  [L179] conditional_expression@179 input == nullptr
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ add_reorder_candidate_count  [L181] if_statement@180 (rabitq_lower_bound_candidates == nullptr)
  │    │    │  #61 add_reorder_candidate_count [src/impl/reorder/flatten_reorder.cpp:138]
  │    │    │    ├─ ctx.stats->reorder_candidate_count.fetch_add  [L141] if_statement@140 (ctx.stats != nullptr)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ std::min  [L182] if_statement@180 (rabitq_lower_bound_candidates == nullptr)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ std::make_shared<StandardHeap<true, false>>  [L183] if_statement@180 (rabitq_lower_bound_candidates == nullptr)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ AcquireQueryComputer  [L184] if_statement@180 (rabitq_lower_bound_candidates == nullptr)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ input->GetData  [L188] if_statement@180 (rabitq_lower_bound_candidates == nullptr) → conditional_expression@188 input == nullptr
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ add_reorder_distance_count  [L192] if_statement@180 (rabitq_lower_bound_candidates == nullptr)
  │    │    │  #62 add_reorder_distance_count [src/impl/reorder/flatten_reorder.cpp:130]
  │    │    │    ├─ ctx.stats->reorder_distance_count.fetch_add  [L133] if_statement@132 (ctx.stats != nullptr)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ flatten_->Query  [L195] if_statement@180 (rabitq_lower_bound_candidates == nullptr)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ dists.data  [L195] if_statement@180 (rabitq_lower_bound_candidates == nullptr)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ ids.data  [L195] if_statement@180 (rabitq_lower_bound_candidates == nullptr)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ ctx.reasoning_ctx->RecordReorder  [L199] if_statement@180 (rabitq_lower_bound_candidates == nullptr) → for_statement@197 i < heap_candidate_size → if_statement@198 (ctx.reasoning_ctx != nullptr)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ consume_if_ineligible  [L202] if_statement@180 (rabitq_lower_bound_candidates == nullptr) → for_statement@197 i < heap_candidate_size → if_statement@202 (consume_if_ineligible(dists[i], candidate_result[i].second))
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ reorder_heap->Size  [L205] if_statement@180 (rabitq_lower_bound_candidates == nullptr) → for_statement@197 i < heap_candidate_size → if_statement@205 (reorder_heap->Size() < topk || dists[i] < reorder_heap->Top().first)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ reorder_heap->Top  [L205] if_statement@180 (rabitq_lower_bound_candidates == nullptr) → for_statement@197 i < heap_candidate_size → if_statement@205 (reorder_heap->Size() < topk || dists[i] < reorder_heap->Top().first)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ reorder_heap->Push  [L206] if_statement@180 (rabitq_lower_bound_candidates == nullptr) → for_statement@197 i < heap_candidate_size → if_statement@205 (reorder_heap->Size() < topk || dists[i] < reorder_heap->Top().first)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ reorder_heap->Size  [L207] if_statement@180 (rabitq_lower_bound_candidates == nullptr) → for_statement@197 i < heap_candidate_size → if_statement@205 (reorder_heap->Size() < topk || dists[i] < reorder_heap->Top().first) → if_statement@207 (reorder_heap->Size() > topk)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ reorder_heap->Top  [L209] if_statement@180 (rabitq_lower_bound_candidates == nullptr) → for_statement@197 i < heap_candidate_size → if_statement@205 (reorder_heap->Size() < topk || dists[i] < reorder_heap->Top().first) → if_statement@207 (reorder_heap->Size() > topk) → if_statement@208 (iter_ctx != nullptr)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ iter_ctx->AddDiscardNode  [L210] if_statement@180 (rabitq_lower_bound_candidates == nullptr) → for_statement@197 i < heap_candidate_size → if_statement@205 (reorder_heap->Size() < topk || dists[i] < reorder_heap->Top().first) → if_statement@207 (reorder_heap->Size() > topk) → if_statement@208 (iter_ctx != nullptr)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ ctx.reasoning_ctx->RecordReorderEviction  [L213] if_statement@180 (rabitq_lower_bound_candidates == nullptr) → for_statement@197 i < heap_candidate_size → if_statement@205 (reorder_heap->Size() < topk || dists[i] < reorder_heap->Top().first) → if_statement@207 (reorder_heap->Size() > topk) → if_statement@212 (ctx.reasoning_ctx != nullptr)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ reorder_heap->Top  [L213] if_statement@180 (rabitq_lower_bound_candidates == nullptr) → for_statement@197 i < heap_candidate_size → if_statement@205 (reorder_heap->Size() < topk || dists[i] < reorder_heap->Top().first) → if_statement@207 (reorder_heap->Size() > topk) → if_statement@212 (ctx.reasoning_ctx != nullptr)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ reorder_heap->Pop  [L215] if_statement@180 (rabitq_lower_bound_candidates == nullptr) → for_statement@197 i < heap_candidate_size → if_statement@205 (reorder_heap->Size() < topk || dists[i] < reorder_heap->Top().first) → if_statement@207 (reorder_heap->Size() > topk)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ rabitq_lower_bound_candidates->size  [L223] conditional_expression@223 rabitq_lower_bound_candidates == nullptr
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ AcquireQueryComputer  [L228] 函数本体；短路求值/提前返回见源码
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ std::make_shared<StandardHeap<true, false>>  [L231] if_statement@230 (topk == 0 || max_candidate_size == 0)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ merged_ids.reserve  [L238] 函数本体；短路求值/提前返回见源码
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ input->GetData  [L241] conditional_expression@241 input == nullptr
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ merged_ids.insert  [L244] for_statement@242 i < heap_candidate_size → if_statement@244 (merged_ids.insert(id).second)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ add_reorder_lower_bound_probe_count  [L250] if_statement@249 (heap_unique_size > 0)
  │    │    │  #63 add_reorder_lower_bound_probe_count [src/impl/reorder/flatten_reorder.cpp:146]
  │    │    │    ├─ ctx.stats->reorder_lower_bound_probe_count.fetch_add  [L149] if_statement@148 (ctx.stats != nullptr)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ flatten_->QueryWithDistanceLowerBound  [L252] if_statement@249 (heap_unique_size > 0)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ lower_bound_probe_dists.data  [L252] if_statement@249 (heap_unique_size > 0)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ lower_bounds.data  [L253] if_statement@249 (heap_unique_size > 0)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ all_ids.data  [L255] if_statement@249 (heap_unique_size > 0)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ merged_ids.insert  [L262] if_statement@260 (rabitq_lower_bound_candidates != nullptr) → for_range_loop@261 → if_statement@262 (merged_ids.insert(item.second).second)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ add_reorder_candidate_count  [L271] 函数本体；短路求值/提前返回见源码
  │    │    │  ↳ 复用节点 #61 add_reorder_candidate_count（本树前文已展开）
  │    │    ├─ std::min  [L273] 函数本体；短路求值/提前返回见源码
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ std::make_shared<StandardHeap<true, false>>  [L274] 函数本体；短路求值/提前返回见源码
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ IsFiniteRaBitQValue  [L280] lambda@279（定义体，执行时间取决于调用/调度）
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ std::numeric_limits<float>::max  [L280] lambda@279（定义体，执行时间取决于调用/调度）
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ has_valid_lower_bound  [L284] for_statement@283 i < candidate_size → if_statement@284 (not has_valid_lower_bound(lower_bounds[i]))
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ add_reorder_distance_count  [L291] if_statement@290 (not lower_bounds_available)
  │    │    │  ↳ 复用节点 #62 add_reorder_distance_count（本树前文已展开）
  │    │    ├─ flatten_->Query  [L294] if_statement@290 (not lower_bounds_available)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ lower_bound_probe_dists.data  [L295] if_statement@290 (not lower_bounds_available)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ all_ids.data  [L295] if_statement@290 (not lower_bounds_available)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ ctx.reasoning_ctx->RecordReorder  [L299] if_statement@290 (not lower_bounds_available) → for_statement@297 i < candidate_size → if_statement@298 (ctx.reasoning_ctx != nullptr)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ consume_if_ineligible  [L302] if_statement@290 (not lower_bounds_available) → for_statement@297 i < candidate_size → if_statement@302 (consume_if_ineligible(lower_bound_probe_dists[i], all_ids[i]))
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ reorder_heap->Size  [L305] if_statement@290 (not lower_bounds_available) → for_statement@297 i < candidate_size → if_statement@305 (reorder_heap->Size() < topk or lower_bound_probe_dists[i] < reorder_heap->Top().first)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ reorder_heap->Top  [L306] if_statement@290 (not lower_bounds_available) → for_statement@297 i < candidate_size → if_statement@305 (reorder_heap->Size() < topk or lower_bound_probe_dists[i] < reorder_heap->Top().first)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ reorder_heap->Push  [L307] if_statement@290 (not lower_bounds_available) → for_statement@297 i < candidate_size → if_statement@305 (reorder_heap->Size() < topk or lower_bound_probe_dists[i] < reorder_heap->Top().first)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ reorder_heap->Size  [L308] if_statement@290 (not lower_bounds_available) → for_statement@297 i < candidate_size → if_statement@305 (reorder_heap->Size() < topk or lower_bound_probe_dists[i] < reorder_heap->Top().first) → if_statement@308 (reorder_heap->Size() > topk)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ reorder_heap->Top  [L310] if_statement@290 (not lower_bounds_available) → for_statement@297 i < candidate_size → if_statement@305 (reorder_heap->Size() < topk or lower_bound_probe_dists[i] < reorder_heap->Top().first) → if_statement@308 (reorder_heap->Size() > topk) → if_statement@309 (iter_ctx != nullptr)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ iter_ctx->AddDiscardNode  [L311] if_statement@290 (not lower_bounds_available) → for_statement@297 i < candidate_size → if_statement@305 (reorder_heap->Size() < topk or lower_bound_probe_dists[i] < reorder_heap->Top().first) → if_statement@308 (reorder_heap->Size() > topk) → if_statement@309 (iter_ctx != nullptr)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ ctx.reasoning_ctx->RecordReorderEviction  [L314] if_statement@290 (not lower_bounds_available) → for_statement@297 i < candidate_size → if_statement@305 (reorder_heap->Size() < topk or lower_bound_probe_dists[i] < reorder_heap->Top().first) → if_statement@308 (reorder_heap->Size() > topk) → if_statement@313 (ctx.reasoning_ctx != nullptr)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ reorder_heap->Top  [L314] if_statement@290 (not lower_bounds_available) → for_statement@297 i < candidate_size → if_statement@305 (reorder_heap->Size() < topk or lower_bound_probe_dists[i] < reorder_heap->Top().first) → if_statement@308 (reorder_heap->Size() > topk) → if_statement@313 (ctx.reasoning_ctx != nullptr)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ reorder_heap->Pop  [L316] if_statement@290 (not lower_bounds_available) → for_statement@297 i < candidate_size → if_statement@305 (reorder_heap->Size() < topk or lower_bound_probe_dists[i] < reorder_heap->Top().first) → if_statement@308 (reorder_heap->Size() > topk)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ std::iota  [L324] 函数本体；短路求值/提前返回见源码
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ order.begin  [L324] 函数本体；短路求值/提前返回见源码
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ order.end  [L324] 函数本体；短路求值/提前返回见源码
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ std::sort  [L325] 函数本体；短路求值/提前返回见源码
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ order.begin  [L325] 函数本体；短路求值/提前返回见源码
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ order.end  [L325] 函数本体；短路求值/提前返回见源码
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ std::min<uint64_t>  [L329] 函数本体；短路求值/提前返回见源码
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ std::max<uint64_t>  [L331] 函数本体；短路求值/提前返回见源码
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ std::numeric_limits<float>::max  [L341] for_statement@337 i < bootstrap_size → conditional_expression@340 idx < heap_unique_size
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ add_reorder_distance_count  [L343] 函数本体；短路求值/提前返回见源码
  │    │    │  ↳ 复用节点 #62 add_reorder_distance_count（本树前文已展开）
  │    │    ├─ flatten_->QueryWithDistanceHint  [L346] 函数本体；短路求值/提前返回见源码
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ dists.data  [L347] 函数本体；短路求值/提前返回见源码
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ hint_dists.data  [L347] 函数本体；短路求值/提前返回见源码
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ ids.data  [L347] 函数本体；短路求值/提前返回见源码
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ ctx.reasoning_ctx->RecordReorder  [L352] for_statement@349 i < bootstrap_size → if_statement@350 (ctx.reasoning_ctx != nullptr)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ consume_if_ineligible  [L354] for_statement@349 i < bootstrap_size → if_statement@354 (not consume_if_ineligible(dists[i], ids[i]))
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ reorder_heap->Push  [L355] for_statement@349 i < bootstrap_size → if_statement@354 (not consume_if_ineligible(dists[i], ids[i]))
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ reorder_heap->Size  [L361] while_statement@360 (cursor < candidate_size) → if_statement@361 (reorder_heap->Size() == topk && lower_bounds[order[cursor]] >= reorder_heap->Top().first)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ reorder_heap->Top  [L362] while_statement@360 (cursor < candidate_size) → if_statement@361 (reorder_heap->Size() == topk && lower_bounds[order[cursor]] >= reorder_heap->Top().first)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ reorder_heap->Size  [L366] while_statement@360 (cursor < candidate_size) → conditional_expression@366 reorder_heap->Size() == topk
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ reorder_heap->Top  [L367] while_statement@360 (cursor < candidate_size) → conditional_expression@366 reorder_heap->Size() == topk
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ std::numeric_limits<float>::max  [L368] while_statement@360 (cursor < candidate_size) → conditional_expression@366 reorder_heap->Size() == topk
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ std::numeric_limits<float>::max  [L377] while_statement@360 (cursor < candidate_size) → while_statement@370 (cursor < candidate_size && batch_count < batch_size) → conditional_expression@376 idx < heap_unique_size
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ add_reorder_distance_count  [L387] while_statement@360 (cursor < candidate_size)
  │    │    │  ↳ 复用节点 #62 add_reorder_distance_count（本树前文已展开）
  │    │    ├─ flatten_->QueryWithDistanceHint  [L390] while_statement@360 (cursor < candidate_size)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ dists.data  [L391] while_statement@360 (cursor < candidate_size)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ hint_dists.data  [L391] while_statement@360 (cursor < candidate_size)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ ids.data  [L391] while_statement@360 (cursor < candidate_size)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ ctx.reasoning_ctx->RecordReorder  [L395] while_statement@360 (cursor < candidate_size) → for_statement@393 i < batch_count → if_statement@394 (ctx.reasoning_ctx != nullptr)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ consume_if_ineligible  [L398] while_statement@360 (cursor < candidate_size) → for_statement@393 i < batch_count → if_statement@398 (consume_if_ineligible(dists[i], ids[i]))
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ reorder_heap->Size  [L401] while_statement@360 (cursor < candidate_size) → for_statement@393 i < batch_count → if_statement@401 (reorder_heap->Size() < topk or dists[i] < reorder_heap->Top().first)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ reorder_heap->Top  [L401] while_statement@360 (cursor < candidate_size) → for_statement@393 i < batch_count → if_statement@401 (reorder_heap->Size() < topk or dists[i] < reorder_heap->Top().first)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ reorder_heap->Push  [L402] while_statement@360 (cursor < candidate_size) → for_statement@393 i < batch_count → if_statement@401 (reorder_heap->Size() < topk or dists[i] < reorder_heap->Top().first)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ reorder_heap->Size  [L403] while_statement@360 (cursor < candidate_size) → for_statement@393 i < batch_count → if_statement@401 (reorder_heap->Size() < topk or dists[i] < reorder_heap->Top().first) → if_statement@403 (reorder_heap->Size() > topk)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ reorder_heap->Top  [L405] while_statement@360 (cursor < candidate_size) → for_statement@393 i < batch_count → if_statement@401 (reorder_heap->Size() < topk or dists[i] < reorder_heap->Top().first) → if_statement@403 (reorder_heap->Size() > topk) → if_statement@404 (iter_ctx != nullptr)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ iter_ctx->AddDiscardNode  [L406] while_statement@360 (cursor < candidate_size) → for_statement@393 i < batch_count → if_statement@401 (reorder_heap->Size() < topk or dists[i] < reorder_heap->Top().first) → if_statement@403 (reorder_heap->Size() > topk) → if_statement@404 (iter_ctx != nullptr)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ ctx.reasoning_ctx->RecordReorderEviction  [L409] while_statement@360 (cursor < candidate_size) → for_statement@393 i < batch_count → if_statement@401 (reorder_heap->Size() < topk or dists[i] < reorder_heap->Top().first) → if_statement@403 (reorder_heap->Size() > topk) → if_statement@408 (ctx.reasoning_ctx != nullptr)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ reorder_heap->Top  [L409] while_statement@360 (cursor < candidate_size) → for_statement@393 i < batch_count → if_statement@401 (reorder_heap->Size() < topk or dists[i] < reorder_heap->Top().first) → if_statement@403 (reorder_heap->Size() > topk) → if_statement@408 (ctx.reasoning_ctx != nullptr)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ reorder_heap->Pop  [L411] while_statement@360 (cursor < candidate_size) → for_statement@393 i < batch_count → if_statement@401 (reorder_heap->Size() < topk or dists[i] < reorder_heap->Top().first) → if_statement@403 (reorder_heap->Size() > topk)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ this->pack_knn_result  [L193] 函数本体；短路求值/提前返回见源码
  │    │  ↳ 复用节点 #35 InnerIndexInterface::pack_knn_result（本树前文已展开）
  ├─ query->GetFloat32Vectors  [L741] if_statement@725 (is_range) → if_statement@737 (use_reorder_ and param.enable_reorder)
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ reasoning_ctx.get  [L741] if_statement@725 (is_range) → if_statement@737 (use_reorder_ and param.enable_reorder)
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ result->Statistics  [L742] if_statement@725 (is_range) → if_statement@737 (use_reorder_ and param.enable_reorder)
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ stats.Dump  [L742] if_statement@725 (is_range) → if_statement@737 (use_reorder_ and param.enable_reorder)
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ this->AttachReasoningReport  [L743] if_statement@725 (is_range) → if_statement@737 (use_reorder_ and param.enable_reorder)
  │  ↳ 复用节点 #33 IVF::AttachReasoningReport（本树前文已展开）
  ├─ reasoning_ctx.get  [L743] if_statement@725 (is_range) → if_statement@737 (use_reorder_ and param.enable_reorder)
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ this->pack_knn_result  [L746] if_statement@725 (is_range)
  │  ↳ 复用节点 #35 InnerIndexInterface::pack_knn_result（本树前文已展开）
  ├─ dataset_results->Statistics  [L747] if_statement@725 (is_range)
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ stats.Dump  [L747] if_statement@725 (is_range)
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ this->AttachReasoningReport  [L748] if_statement@725 (is_range)
  │  ↳ 复用节点 #33 IVF::AttachReasoningReport（本树前文已展开）
  ├─ reasoning_ctx.get  [L748] if_statement@725 (is_range)
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ CHECK_ARGUMENT  [L756] if_statement@755 (use_reorder_ and param.enable_reorder)
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ fmt::format  [L758] if_statement@755 (use_reorder_ and param.enable_reorder)
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ request.threshold_.has_value  [L760] if_statement@755 (use_reorder_ and param.enable_reorder) → if_statement@760 (request.threshold_.has_value())
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ std::max  [L761] if_statement@755 (use_reorder_ and param.enable_reorder) → if_statement@760 (request.threshold_.has_value())
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ this->search<KNN_SEARCH>  [L768] 函数本体；短路求值/提前返回见源码
  │  ↳ 复用节点 #36 IVF::search（本树前文已展开）
  ├─ reasoning_ctx.get  [L768] 函数本体；短路求值/提前返回见源码
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ reorder  [L770] if_statement@769 (reorder_enabled)
  │  ↳ 复用节点 #54 IVF::reorder（本树前文已展开）
  ├─ request.threshold_.has_value  [L770] if_statement@769 (reorder_enabled) → conditional_expression@770 request.threshold_.has_value()
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ query->GetFloat32Vectors  [L772] if_statement@769 (reorder_enabled)
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ reasoning_ctx.get  [L775] if_statement@769 (reorder_enabled)
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ FilterDatasetByThreshold  [L777] if_statement@769 (reorder_enabled)
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ AttachReasoningReport  [L778] if_statement@769 (reorder_enabled)
  │  ↳ 复用节点 #33 IVF::AttachReasoningReport（本树前文已展开）
  ├─ reasoning_ctx.get  [L778] if_statement@769 (reorder_enabled)
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ result->Statistics  [L779] if_statement@769 (reorder_enabled)
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ stats.Dump  [L779] if_statement@769 (reorder_enabled)
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ filter_search_result_by_threshold  [L782] 函数本体；短路求值/提前返回见源码
  │  ↳ 复用节点 #32 InnerIndexInterface::filter_search_result_by_threshold（本树前文已展开）
  ├─ select_query_allocator  [L783] 函数本体；短路求值/提前返回见源码
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ search_result->Empty  [L784] if_statement@784 (search_result == nullptr || search_result->Empty())
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ DatasetImpl::MakeEmptyDataset  [L785] if_statement@784 (search_result == nullptr || search_result->Empty())
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ this->AttachReasoningReport  [L786] if_statement@784 (search_result == nullptr || search_result->Empty())
  │  ↳ 复用节点 #33 IVF::AttachReasoningReport（本树前文已展开）
  ├─ reasoning_ctx.get  [L786] if_statement@784 (search_result == nullptr || search_result->Empty())
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ dataset_results->Statistics  [L787] if_statement@784 (search_result == nullptr || search_result->Empty())
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ stats.Dump  [L787] if_statement@784 (search_result == nullptr || search_result->Empty())
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ this->pack_knn_result  [L791] 函数本体；短路求值/提前返回见源码
  │  ↳ 复用节点 #35 InnerIndexInterface::pack_knn_result（本树前文已展开）
  ├─ dataset_results->Statistics  [L792] 函数本体；短路求值/提前返回见源码
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ stats.Dump  [L792] 函数本体；短路求值/提前返回见源码
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ this->AttachReasoningReport  [L794] 函数本体；短路求值/提前返回见源码
  │  ↳ 复用节点 #33 IVF::AttachReasoningReport（本树前文已展开）
  ├─ reasoning_ctx.get  [L794] 函数本体；短路求值/提前返回见源码
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
```

## IVF::search

[完整函数与全部调用点](function_reference/ivf_search.md#L199)

```text
#1 IVF::search [src/algorithm/ivf/ivf_search.cpp:199]
  ├─ query->GetFloat32Vectors  [L204] 函数本体；短路求值/提前返回见源码
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ param.bucket_ids.empty  [L206] if_statement@206 (not param.bucket_ids.empty())
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ candidate_buckets.reserve  [L207] if_statement@206 (not param.bucket_ids.empty())
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ param.bucket_ids.size  [L207] if_statement@206 (not param.bucket_ids.empty())
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ candidate_buckets.push_back  [L209] if_statement@206 (not param.bucket_ids.empty()) → for_range_loop@208
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ partition_strategy_->ClassifyDatasForSearch  [L212] if_statement@206 (not param.bucket_ids.empty()) [else 分支]
  │  ├─ 以下为分派/重载候选，并非全部依次执行
  │  #2 GNOIMIPartition::ClassifyDatasForSearch [src/algorithm/ivf/gno_imi_partition.cpp:221]
  │    ├─ norm_vectors.resize  [L228] if_statement@227 (metric_type_ == MetricType::METRIC_TYPE_COSINE)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ Normalize  [L230] if_statement@227 (metric_type_ == MetricType::METRIC_TYPE_COSINE) → for_statement@229 i < count
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ norm_vectors.data  [L231] if_statement@227 (metric_type_ == MetricType::METRIC_TYPE_COSINE) → for_statement@229 i < count
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ norm_vectors.data  [L233] if_statement@227 (metric_type_ == MetricType::METRIC_TYPE_COSINE)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ std::fill  [L237] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ result.begin  [L237] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ result.end  [L237] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ dist_to_s.data  [L243] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ dist_to_t.data  [L244] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ candidate_s_id.data  [L245] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ candidate_s_dist.data  [L246] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ matmul  [L249] 函数本体；短路求值/提前返回见源码
  │    │  #3 matmul [src/algorithm/ivf/gno_imi_partition.cpp:40]
  │    │    ├─ BlasFunction::Sgemm  [L42] 函数本体；短路求值/提前返回见源码
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ data_centroids_s_.data  [L250] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ matmul  [L255] 函数本体；短路求值/提前返回见源码
  │    │  ↳ 复用节点 #3 matmul（本树前文已展开）
  │    ├─ data_centroids_t_.data  [L256] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ FP32ComputeIP  [L263] for_statement@262 i < count
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ heap.size  [L271] for_statement@262 i < count → for_statement@268 j < bucket_count_s_ → if_statement@271 (heap.size() < candidate_count_s || dist_term_s < heap.top().first)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ heap.top  [L271] for_statement@262 i < count → for_statement@268 j < bucket_count_s_ → if_statement@271 (heap.size() < candidate_count_s || dist_term_s < heap.top().first)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ heap.emplace  [L272] for_statement@262 i < count → for_statement@268 j < bucket_count_s_ → if_statement@271 (heap.size() < candidate_count_s || dist_term_s < heap.top().first)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ heap.size  [L274] for_statement@262 i < count → for_statement@268 j < bucket_count_s_ → if_statement@274 (heap.size() > candidate_count_s)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ heap.pop  [L275] for_statement@262 i < count → for_statement@268 j < bucket_count_s_ → if_statement@274 (heap.size() > candidate_count_s)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ heap.top  [L279] for_statement@262 i < count → for_statement@278 j >= 0
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ heap.top  [L280] for_statement@262 i < count → for_statement@278 j >= 0
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ heap.pop  [L281] for_statement@262 i < count → for_statement@278 j >= 0
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ CHECK_ARGUMENT  [L283] for_statement@262 i < count
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ heap.empty  [L283] for_statement@262 i < count
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ fmt::format  [L283] for_statement@262 i < count
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ std::floor  [L286] for_statement@262 i < count
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ std::max  [L287] for_statement@262 i < count
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ heap.size  [L301] for_statement@262 i < count → for_statement@288 j < scan_bucket_count_s → for_statement@289 k < bucket_count_t_ → if_statement@301 (heap.size() < buckets_per_data || dist_term_st < heap.top().first)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ heap.top  [L301] for_statement@262 i < count → for_statement@288 j < scan_bucket_count_s → for_statement@289 k < bucket_count_t_ → if_statement@301 (heap.size() < buckets_per_data || dist_term_st < heap.top().first)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ heap.emplace  [L302] for_statement@262 i < count → for_statement@288 j < scan_bucket_count_s → for_statement@289 k < bucket_count_t_ → if_statement@301 (heap.size() < buckets_per_data || dist_term_st < heap.top().first)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ heap.size  [L304] for_statement@262 i < count → for_statement@288 j < scan_bucket_count_s → for_statement@289 k < bucket_count_t_ → if_statement@304 (heap.size() > buckets_per_data)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ heap.pop  [L305] for_statement@262 i < count → for_statement@288 j < scan_bucket_count_s → for_statement@289 k < bucket_count_t_ → if_statement@304 (heap.size() > buckets_per_data)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ std::min  [L309] for_statement@262 i < count
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ heap.size  [L309] for_statement@262 i < count
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ heap.empty  [L310] for_statement@262 i < count → for_statement@310 j >= 0 && !heap.empty()
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ heap.top  [L311] for_statement@262 i < count → for_statement@310 j >= 0 && !heap.empty()
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ heap.pop  [L312] for_statement@262 i < count → for_statement@310 j >= 0 && !heap.empty()
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ ctx->stats->AddDistance  [L316] if_statement@315 (ctx != nullptr and ctx->stats != nullptr)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │  #4 IVFPartitionStrategy::ClassifyDatasForSearch [src/algorithm/ivf/ivf_partition_strategy.h:64]
  │    ├─ std::move  [L69] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ ClassifyDatas  [L69] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ reasoning_ctx->RecordBucketSelection  [L215] if_statement@214 (reasoning_ctx != nullptr)
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ bucket_->FactoryComputer  [L217] 函数本体；短路求值/提前返回见源码
  │  #5 BucketDataCell<QuantTmpl, IOTmpl>::FactoryComputer [src/datacell/bucket_datacell.h:566]
  │    ├─ this->quantizer_->FactoryComputer  [L569] 函数本体；短路求值/提前返回见源码
  │    │  #6 Quantizer::FactoryComputer [src/quantization/quantizer.h:179]
  │    │    ├─ std::make_shared<Computer<QuantT>>  [L181] 函数本体；短路求值/提前返回见源码
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ std::static_pointer_cast<Computer<QuantTmpl>>  [L570] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ comp->raw_query_.resize  [L572] if_statement@571 (use_residual_)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ this->quantizer_->GetDim  [L572] if_statement@571 (use_residual_)
  │    │  #7 Quantizer::GetDim [src/quantization/quantizer.h:340]
  │    ├─ Normalize  [L574] if_statement@571 (use_residual_) → if_statement@573 (metric_ == MetricType::METRIC_TYPE_COSINE)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ comp->raw_query_.data  [L574] if_statement@571 (use_residual_) → if_statement@573 (metric_ == MetricType::METRIC_TYPE_COSINE)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ this->quantizer_->GetDim  [L574] if_statement@571 (use_residual_) → if_statement@573 (metric_ == MetricType::METRIC_TYPE_COSINE)
  │    │  ↳ 复用节点 #7 Quantizer::GetDim（本树前文已展开）
  │    ├─ memcpy  [L576] if_statement@571 (use_residual_) → if_statement@573 (metric_ == MetricType::METRIC_TYPE_COSINE) [else 分支]
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ comp->raw_query_.data  [L577] if_statement@571 (use_residual_) → if_statement@573 (metric_ == MetricType::METRIC_TYPE_COSINE) [else 分支]
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ this->quantizer_->GetDim  [L577] if_statement@571 (use_residual_) → if_statement@573 (metric_ == MetricType::METRIC_TYPE_COSINE) [else 分支]
  │    │  ↳ 复用节点 #7 Quantizer::GetDim（本树前文已展开）
  │    ├─ comp->raw_query_.data  [L579] if_statement@571 (use_residual_)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ comp->SetQuery  [L581] 函数本体；短路求值/提前返回见源码
  │    │  ├─ 以下为分派/重载候选，并非全部依次执行
  │    │  #8 Computer::SetQuery [src/quantization/computer.h:48]
  │    │    ├─ quantizer_->ProcessQuery  [L50] 函数本体；短路求值/提前返回见源码
  │    │    │  #9 Quantizer::ProcessQuery [src/quantization/quantizer.h:184]
  │    │    │    ├─ cast().ProcessQueryImpl  [L186] 函数本体；短路求值/提前返回见源码
  │    │    │    │  #10 FP32Quantizer<metric>::ProcessQueryImpl [src/quantization/fp32_quantizer.cpp:144]
  │    │    │    │    ├─ this->allocator_->Allocate  [L150] if_statement@148 (computer.buf_ == nullptr)
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ VsagException  [L154] catch_clause@152
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ Normalize  [L157] if_statement@156 (metric == MetricType::METRIC_TYPE_COSINE)
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ memcpy  [L159] if_statement@156 (metric == MetricType::METRIC_TYPE_COSINE) [else 分支]
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ cast  [L186] 函数本体；短路求值/提前返回见源码
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │  #11 Computer<TransformQuantizer<QuantImpl, metric>>::SetQuery [src/quantization/computer.h:122]
  │    │    ├─ quantizer_->ProcessQuery  [L124] 函数本体；短路求值/提前返回见源码
  │    │    │  ↳ 复用节点 #9 Quantizer::ProcessQuery（本树前文已展开）
  ├─ this->GetNumElements  [L223] if_statement@220 (mode == RANGE_SEARCH) → if_statement@222 (topk < 0)
  │  #12 IVF::GetNumElements [src/algorithm/ivf/ivf.cpp:291]
  ├─ std::numeric_limits<int64_t>::max  [L229] if_statement@228 (buckets_per_data_ > 1) → if_statement@229 (topk <= std::numeric_limits<int64_t>::max() / buckets_per_data_)
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ std::numeric_limits<int64_t>::max  [L232] if_statement@228 (buckets_per_data_ > 1) → if_statement@229 (topk <= std::numeric_limits<int64_t>::max() / buckets_per_data_) [else 分支]
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ candidate_buckets.size  [L238] 函数本体；短路求值/提前返回见源码
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ DistanceHeap::MakeInstanceBySize<true, false>  [L246] lambda@245（定义体，执行时间取决于调用/调度）
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ cur_bucket_num.fetch_add  [L249] lambda@245（定义体，执行时间取决于调用/调度）
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ cur_bucket_num.fetch_add  [L250] lambda@245（定义体，执行时间取决于调用/调度） → for_statement@250 i < bucket_count
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ param.time_cost->CheckOvertime  [L251] lambda@245（定义体，执行时间取决于调用/调度） → for_statement@250 i < bucket_count → if_statement@251 (param.time_cost != nullptr and param.time_cost->CheckOvertime() and ctx.stats != nullptr)
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ ctx.stats->is_timeout.store  [L253] lambda@245（定义体，执行时间取决于调用/调度） → for_statement@250 i < bucket_count → if_statement@251 (param.time_cost != nullptr and param.time_cost->CheckOvertime() and ctx.stats != nullptr)
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ bucket_searcher_->Search  [L260] lambda@245（定义体，执行时间取决于调用/调度） → for_statement@250 i < bucket_count
  │  ├─ 以下为分派/重载候选，并非全部依次执行
  │  #13 FlatBucketSearcher::Search [src/algorithm/ivf/flat_bucket_searcher.cpp:26]
  │    ├─ bucket->GetBucketSize  [L37] 函数本体；短路求值/提前返回见源码
  │    │  #14 BucketDataCell::GetBucketSize [src/datacell/bucket_datacell.h:180]
  │    │    ├─ check_valid_bucket_id  [L182] 函数本体；短路求值/提前返回见源码
  │    │    │  #15 BucketDataCell::check_valid_bucket_id [src/datacell/bucket_datacell.h:244]
  │    │    │    ├─ VsagException  [L247] if_statement@246 (bucket_id >= this->bucket_count_ or bucket_id < 0)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ bucket->GetInnerIds  [L38] 函数本体；短路求值/提前返回见源码
  │    │  #16 BucketDataCell::GetInnerIds [src/datacell/bucket_datacell.h:120]
  │    │    ├─ check_valid_bucket_id  [L122] 函数本体；短路求值/提前返回见源码
  │    │    │  ↳ 复用节点 #15 BucketDataCell::check_valid_bucket_id（本树前文已展开）
  │    │    ├─ this->inner_ids_[bucket_id].data  [L123] 函数本体；短路求值/提前返回见源码
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ dist.size  [L39] if_statement@39 (bucket_size > static_cast<int64_t>(dist.size()))
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ dist.resize  [L40] if_statement@39 (bucket_size > static_cast<int64_t>(dist.size()))
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ bucket->ScanBucketById  [L43] 函数本体；短路求值/提前返回见源码
  │    │  #17 BucketDataCell::ScanBucketById [src/datacell/bucket_datacell.h:63]
  │    │    ├─ computer.get  [L67] 函数本体；短路求值/提前返回见源码
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ this->scan_bucket_by_id  [L68] 函数本体；短路求值/提前返回见源码
  │    │    │  #18 BucketDataCell<QuantTmpl, IOTmpl>::scan_bucket_by_id [src/datacell/bucket_datacell.h:522]
  │    │    │    ├─ VsagException  [L527] if_statement@526 (bucket_id >= this->bucket_count_ or bucket_id < 0)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ this->check_valid_bucket_id  [L532] 函数本体；短路求值/提前返回见源码
  │    │    │    │  ↳ 复用节点 #15 BucketDataCell::check_valid_bucket_id（本树前文已展开）
  │    │    │    ├─ std::min  [L535] while_statement@534 (data_count > 0)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ this->datas_[bucket_id].Acquire  [L537] while_statement@534 (data_count > 0)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ computer->ScanBatchDists  [L538] while_statement@534 (data_count > 0)
  │    │    │    │  ├─ 以下为分派/重载候选，并非全部依次执行
  │    │    │    │  #19 Computer::ScanBatchDists [src/quantization/computer.h:68]
  │    │    │    │    ├─ quantizer_->ScanBatchDists  [L70] 函数本体；短路求值/提前返回见源码
  │    │    │    │    │  #20 Quantizer::ScanBatchDists [src/quantization/quantizer.h:230]
  │    │    │    │    │    ├─ cast().ScanBatchDistImpl  [L235] 函数本体；短路求值/提前返回见源码
  │    │    │    │    │    │  ├─ 以下为分派/重载候选，并非全部依次执行
  │    │    │    │    │    │  #21 Quantizer::ScanBatchDistImpl [src/quantization/quantizer.h:290]
  │    │    │    │    │    │    ├─ cast().ComputeDistImpl  [L296] for_statement@295 i < count
  │    │    │    │    │    │    │  #22 FP32Quantizer<metric>::ComputeDistImpl [src/quantization/fp32_quantizer.cpp:164]
  │    │    │    │    │    │    │    ├─ FP32ComputeIP  [L169] if_statement@168 (metric == MetricType::METRIC_TYPE_IP)
  │    │    │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    │    │    ├─ FP32ComputeIP  [L173] if_statement@168 (metric == MetricType::METRIC_TYPE_IP) [else 分支] → if_statement@172 (metric == MetricType::METRIC_TYPE_COSINE)
  │    │    │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    │    │    ├─ FP32ComputeL2Sqr  [L182] if_statement@168 (metric == MetricType::METRIC_TYPE_IP) [else 分支] → if_statement@172 (metric == MetricType::METRIC_TYPE_COSINE) [else 分支] → if_statement@181 (metric == MetricType::METRIC_TYPE_L2SQR)
  │    │    │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    │    ├─ cast  [L296] for_statement@295 i < count
  │    │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    │  #23 FP32Quantizer<metric>::ScanBatchDistImpl [src/quantization/fp32_quantizer.cpp:132]
  │    │    │    │    │    │    ├─ this->ComputeDistImpl  [L139] for_statement@138 i < count
  │    │    │    │    │    │    │  ↳ 复用节点 #22 FP32Quantizer<metric>::ComputeDistImpl（本树前文已展开）
  │    │    │    │    │    ├─ cast  [L235] 函数本体；短路求值/提前返回见源码
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │  #24 Computer<TransformQuantizer<QuantImpl, metric>>::ScanBatchDists [src/quantization/computer.h:142]
  │    │    │    │    ├─ quantizer_->ScanBatchDists  [L144] 函数本体；短路求值/提前返回见源码
  │    │    │    │    │  ↳ 复用节点 #20 Quantizer::ScanBatchDists（本树前文已展开）
  │    │    │    ├─ lease.Data  [L538] while_statement@534 (data_count > 0)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ this->quantizer_->GetDim  [L544] 函数本体；短路求值/提前返回见源码
  │    │    │    │  ↳ 复用节点 #7 Quantizer::GetDim（本树前文已展开）
  │    │    │    ├─ strategy_->GetCentroid  [L546] if_statement@545 (use_residual_)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ FP32ComputeIP  [L548] if_statement@545 (use_residual_)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ computer->raw_query_.data  [L548] if_statement@545 (use_residual_)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ centroid.data  [L548] if_statement@545 (use_residual_)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ this->quantizer_->GetDim  [L548] if_statement@545 (use_residual_)
  │    │    │    │  ↳ 复用节点 #7 Quantizer::GetDim（本树前文已展开）
  │    │    │    ├─ FP32Sub  [L551] if_statement@545 (use_residual_) → if_statement@549 (metric_ == MetricType::METRIC_TYPE_L2SQR)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ residual_bias_[bucket_id].data  [L551] if_statement@545 (use_residual_) → if_statement@549 (metric_ == MetricType::METRIC_TYPE_L2SQR)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ std::numeric_limits<float>::max  [L560] for_statement@558 i < offset → if_statement@559 (this->inner_ids_[bucket_id][i] == EMPTY_INNER_ID)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ dist.data  [L43] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ param.query_context->stats->AddDistance  [L46] if_statement@44 (param.query_context != nullptr and param.query_context->stats != nullptr and bucket_size > 0)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ param.executors.size  [L53] if_statement@53 (thread_id >= 0 and param.executors.size() > static_cast<uint64_t>(thread_id))
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ param.executors[tid]->Clear  [L56] if_statement@53 (thread_id >= 0 and param.executors.size() > static_cast<uint64_t>(thread_id)) → if_statement@55 (param.executors[tid] != nullptr)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ param.executors[tid]->Run  [L57] if_statement@53 (thread_id >= 0 and param.executors.size() > static_cast<uint64_t>(thread_id)) → if_statement@55 (param.executors[tid] != nullptr)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ std::numeric_limits<float>::max  [L63] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ heap->Empty  [L64] if_statement@64 (not heap->Empty() and heap->Size() == topk_u)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ heap->Size  [L64] if_statement@64 (not heap->Empty() and heap->Size() == topk_u)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ heap->Top  [L65] if_statement@64 (not heap->Empty() and heap->Size() == topk_u)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ std::numeric_limits<InnerIdType>::max  [L70] if_statement@68 (param.search_mode == KNN_SEARCH) → for_statement@69 j < bucket_size → if_statement@70 (ids[j] == std::numeric_limits<InnerIdType>::max())
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ reasoning_ctx->RecordVisit  [L75] if_statement@68 (param.search_mode == KNN_SEARCH) → for_statement@69 j < bucket_size → if_statement@74 (reasoning_ctx != nullptr)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ param.distance_threshold.has_value  [L77] if_statement@68 (param.search_mode == KNN_SEARCH) → for_statement@69 j < bucket_size → if_statement@77 (param.distance_threshold.has_value() and (not std::isfinite(dist[j]) or (not param.enable_reorder and dist[j] > param.distance_threshold.value())))
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ std::isfinite  [L78] if_statement@68 (param.search_mode == KNN_SEARCH) → for_statement@69 j < bucket_size → if_statement@77 (param.distance_threshold.has_value() and (not std::isfinite(dist[j]) or (not param.enable_reorder and dist[j] > param.distance_threshold.value())))
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ param.distance_threshold.value  [L79] if_statement@68 (param.search_mode == KNN_SEARCH) → for_statement@69 j < bucket_size → if_statement@77 (param.distance_threshold.has_value() and (not std::isfinite(dist[j]) or (not param.enable_reorder and dist[j] > param.distance_threshold.value())))
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ attr_ft->CheckValid  [L82] if_statement@68 (param.search_mode == KNN_SEARCH) → for_statement@69 j < bucket_size → if_statement@82 (attr_ft != nullptr and not attr_ft->CheckValid(j))
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ reasoning_ctx->RecordFilterReject  [L84] if_statement@68 (param.search_mode == KNN_SEARCH) → for_statement@69 j < bucket_size → if_statement@82 (attr_ft != nullptr and not attr_ft->CheckValid(j)) → if_statement@83 (reasoning_ctx != nullptr)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ ft->CheckValid  [L88] if_statement@68 (param.search_mode == KNN_SEARCH) → for_statement@69 j < bucket_size → if_statement@88 (ft == nullptr or ft->CheckValid(origin_id))
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ heap->Size  [L89] if_statement@68 (param.search_mode == KNN_SEARCH) → for_statement@69 j < bucket_size → if_statement@88 (ft == nullptr or ft->CheckValid(origin_id)) → if_statement@89 (heap->Size() < topk_u or dist[j] < cur_heap_top)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ heap->Push  [L90] if_statement@68 (param.search_mode == KNN_SEARCH) → for_statement@69 j < bucket_size → if_statement@88 (ft == nullptr or ft->CheckValid(origin_id)) → if_statement@89 (heap->Size() < topk_u or dist[j] < cur_heap_top)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ heap->Size  [L92] if_statement@68 (param.search_mode == KNN_SEARCH) → for_statement@69 j < bucket_size → if_statement@88 (ft == nullptr or ft->CheckValid(origin_id)) → while_statement@92 (heap->Size() > topk_u)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ reasoning_ctx->RecordEviction  [L94] if_statement@68 (param.search_mode == KNN_SEARCH) → for_statement@69 j < bucket_size → if_statement@88 (ft == nullptr or ft->CheckValid(origin_id)) → while_statement@92 (heap->Size() > topk_u) → if_statement@93 (reasoning_ctx != nullptr)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ heap->Top  [L94] if_statement@68 (param.search_mode == KNN_SEARCH) → for_statement@69 j < bucket_size → if_statement@88 (ft == nullptr or ft->CheckValid(origin_id)) → while_statement@92 (heap->Size() > topk_u) → if_statement@93 (reasoning_ctx != nullptr)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ heap->Pop  [L96] if_statement@68 (param.search_mode == KNN_SEARCH) → for_statement@69 j < bucket_size → if_statement@88 (ft == nullptr or ft->CheckValid(origin_id)) → while_statement@92 (heap->Size() > topk_u)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ heap->Empty  [L98] if_statement@68 (param.search_mode == KNN_SEARCH) → for_statement@69 j < bucket_size → if_statement@88 (ft == nullptr or ft->CheckValid(origin_id)) → if_statement@98 (not heap->Empty() and heap->Size() == topk_u)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ heap->Size  [L98] if_statement@68 (param.search_mode == KNN_SEARCH) → for_statement@69 j < bucket_size → if_statement@88 (ft == nullptr or ft->CheckValid(origin_id)) → if_statement@98 (not heap->Empty() and heap->Size() == topk_u)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ heap->Top  [L99] if_statement@68 (param.search_mode == KNN_SEARCH) → for_statement@69 j < bucket_size → if_statement@88 (ft == nullptr or ft->CheckValid(origin_id)) → if_statement@98 (not heap->Empty() and heap->Size() == topk_u)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ reasoning_ctx->RecordFilterReject  [L102] if_statement@68 (param.search_mode == KNN_SEARCH) → for_statement@69 j < bucket_size → if_statement@88 (ft == nullptr or ft->CheckValid(origin_id)) [else 分支] → if_statement@101 (reasoning_ctx != nullptr)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ std::numeric_limits<InnerIdType>::max  [L107] if_statement@68 (param.search_mode == KNN_SEARCH) [else 分支] → for_statement@106 j < bucket_size → if_statement@107 (ids[j] == std::numeric_limits<InnerIdType>::max())
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ reasoning_ctx->RecordVisit  [L112] if_statement@68 (param.search_mode == KNN_SEARCH) [else 分支] → for_statement@106 j < bucket_size → if_statement@111 (reasoning_ctx != nullptr)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ attr_ft->CheckValid  [L114] if_statement@68 (param.search_mode == KNN_SEARCH) [else 分支] → for_statement@106 j < bucket_size → if_statement@114 (attr_ft != nullptr and not attr_ft->CheckValid(j))
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ reasoning_ctx->RecordFilterReject  [L116] if_statement@68 (param.search_mode == KNN_SEARCH) [else 分支] → for_statement@106 j < bucket_size → if_statement@114 (attr_ft != nullptr and not attr_ft->CheckValid(j)) → if_statement@115 (reasoning_ctx != nullptr)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ ft->CheckValid  [L120] if_statement@68 (param.search_mode == KNN_SEARCH) [else 分支] → for_statement@106 j < bucket_size → if_statement@120 (ft == nullptr or ft->CheckValid(origin_id))
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ heap->Push  [L122] if_statement@68 (param.search_mode == KNN_SEARCH) [else 分支] → for_statement@106 j < bucket_size → if_statement@120 (ft == nullptr or ft->CheckValid(origin_id)) → if_statement@121 (dist[j] <= param.radius + THRESHOLD_ERROR and dist[j] < cur_heap_top)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ heap->Size  [L124] if_statement@68 (param.search_mode == KNN_SEARCH) [else 分支] → for_statement@106 j < bucket_size → if_statement@120 (ft == nullptr or ft->CheckValid(origin_id)) → while_statement@124 (heap->Size() > topk_u)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ reasoning_ctx->RecordEviction  [L126] if_statement@68 (param.search_mode == KNN_SEARCH) [else 分支] → for_statement@106 j < bucket_size → if_statement@120 (ft == nullptr or ft->CheckValid(origin_id)) → while_statement@124 (heap->Size() > topk_u) → if_statement@125 (reasoning_ctx != nullptr)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ heap->Top  [L126] if_statement@68 (param.search_mode == KNN_SEARCH) [else 分支] → for_statement@106 j < bucket_size → if_statement@120 (ft == nullptr or ft->CheckValid(origin_id)) → while_statement@124 (heap->Size() > topk_u) → if_statement@125 (reasoning_ctx != nullptr)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ heap->Pop  [L128] if_statement@68 (param.search_mode == KNN_SEARCH) [else 分支] → for_statement@106 j < bucket_size → if_statement@120 (ft == nullptr or ft->CheckValid(origin_id)) → while_statement@124 (heap->Size() > topk_u)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ heap->Empty  [L130] if_statement@68 (param.search_mode == KNN_SEARCH) [else 分支] → for_statement@106 j < bucket_size → if_statement@120 (ft == nullptr or ft->CheckValid(origin_id)) → if_statement@130 (not heap->Empty() and heap->Size() == topk_u)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ heap->Size  [L130] if_statement@68 (param.search_mode == KNN_SEARCH) [else 分支] → for_statement@106 j < bucket_size → if_statement@120 (ft == nullptr or ft->CheckValid(origin_id)) → if_statement@130 (not heap->Empty() and heap->Size() == topk_u)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ heap->Top  [L131] if_statement@68 (param.search_mode == KNN_SEARCH) [else 分支] → for_statement@106 j < bucket_size → if_statement@120 (ft == nullptr or ft->CheckValid(origin_id)) → if_statement@130 (not heap->Empty() and heap->Size() == topk_u)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ reasoning_ctx->RecordFilterReject  [L134] if_statement@68 (param.search_mode == KNN_SEARCH) [else 分支] → for_statement@106 j < bucket_size → if_statement@120 (ft == nullptr or ft->CheckValid(origin_id)) [else 分支] → if_statement@133 (reasoning_ctx != nullptr)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │  #25 GraphBucketSearcher::Search [src/algorithm/ivf/graph_bucket_searcher.cpp:36]
  │    ├─ bucket->GetBucketSize  [L47] 函数本体；短路求值/提前返回见源码
  │    │  ↳ 复用节点 #14 BucketDataCell::GetBucketSize（本树前文已展开）
  │    ├─ bucket_graphs_.size  [L48] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ bucket_graphs_[bucket_id]->TotalCount  [L51] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ search_graph  [L54] if_statement@53 (graph_fresh && bucket_size >= graph_build_threshold_)
  │    │  #26 GraphBucketSearcher::search_graph [src/algorithm/ivf/graph_bucket_searcher.cpp:77]
  │    │    ├─ bucket->GetBucketSize  [L87] 函数本体；短路求值/提前返回见源码
  │    │    │  ↳ 复用节点 #14 BucketDataCell::GetBucketSize（本树前文已展开）
  │    │    ├─ bucket->GetInnerIds  [L92] 函数本体；短路求值/提前返回见源码
  │    │    │  ↳ 复用节点 #16 BucketDataCell::GetInnerIds（本树前文已展开）
  │    │    ├─ std::numeric_limits<InnerIdType>::max  [L94] while_statement@94 (entry < bucket_size && ids[entry] == std::numeric_limits<InnerIdType>::max())
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ param.executors.empty  [L102] if_statement@102 (not param.executors.empty() && static_cast<uint64_t>(thread_id) < param.executors.size() && param.executors[thread_id] != nullptr)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ param.executors.size  [L102] if_statement@102 (not param.executors.empty() && static_cast<uint64_t>(thread_id) < param.executors.size() && param.executors[thread_id] != nullptr)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ param.executors[thread_id]->Clear  [L104] if_statement@102 (not param.executors.empty() && static_cast<uint64_t>(thread_id) < param.executors.size() && param.executors[thread_id] != nullptr)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ param.executors[thread_id]->Run  [L105] if_statement@102 (not param.executors.empty() && static_cast<uint64_t>(thread_id) < param.executors.size() && param.executors[thread_id] != nullptr)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ std::numeric_limits<uint64_t>::max  [L109] 函数本体；短路求值/提前返回见源码
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ CHECK_ARGUMENT  [L111] if_statement@110 (search_param.search_mode == KNN_SEARCH)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ std::max  [L113] if_statement@110 (search_param.search_mode == KNN_SEARCH)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ std::min<uint64_t>  [L117] 函数本体；短路求值/提前返回见源码
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ std::min<int64_t>  [L123] if_statement@119 (search_param.search_mode == RANGE_SEARCH) → conditional_expression@123 topk > 0
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ std::numeric_limits<int>::max  [L123] if_statement@119 (search_param.search_mode == RANGE_SEARCH) → conditional_expression@123 topk > 0
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ std::make_shared<VisitedList>  [L130] 函数本体；短路求值/提前返回见源码
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ searcher.Search  [L135] 函数本体；短路求值/提前返回见源码
  │    │    │  ├─ 以下为分派/重载候选，并非全部依次执行
  │    │    │  #27 BasicSearcher::Search [src/impl/searcher/basic_searcher.cpp:76]
  │    │    │    ├─ this->search_impl<KNN_SEARCH>  [L86] if_statement@85 (inner_search_param.search_mode == KNN_SEARCH)
  │    │    │    │  ├─ 以下为分派/重载候选，并非全部依次执行
  │    │    │    │  #28 BasicSearcher::search_impl [src/impl/searcher/basic_searcher.cpp:174]
  │    │    │    │    ├─ select_query_allocator  [L181] 函数本体；短路求值/提前返回见源码
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ std::make_shared<StandardHeap<true, false>>  [L182] 函数本体；短路求值/提前返回见源码
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ std::make_shared<StandardHeap<true, false>>  [L183] 函数本体；短路求值/提前返回见源码
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ distance_provider.OriginalId  [L188] lambda@187（定义体，执行时间取决于调用/调度）
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ distance_provider.IsValid  [L189] lambda@187（定义体，执行时间取决于调用/调度）
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ inner_search_param.is_inner_id_allowed->CheckValid  [L191] lambda@187（定义体，执行时间取决于调用/调度）
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ attr_filter->CheckValid  [L192] lambda@187（定义体，执行时间取决于调用/调度）
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ distance_provider.QueryDistance  [L197] 函数本体；短路求值/提前返回见源码
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ reasoning->RecordVisit  [L201] if_statement@200 (reasoning != nullptr)
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ distance_provider.OriginalId  [L201] if_statement@200 (reasoning != nullptr)
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ check_func  [L203] if_statement@203 (check_func(ep))
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ is_result_distance_eligible<mode>  [L204] if_statement@203 (check_func(ep)) → if_statement@204 (is_result_distance_eligible<mode>(dist, inner_search_param))
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ top_candidates->Push  [L205] if_statement@203 (check_func(ep)) → if_statement@204 (is_result_distance_eligible<mode>(dist, inner_search_param))
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ reasoning->RecordFilterReject  [L208] if_statement@203 (check_func(ep)) [else 分支] → if_statement@207 (reasoning != nullptr)
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ distance_provider.OriginalId  [L208] if_statement@203 (check_func(ep)) [else 分支] → if_statement@207 (reasoning != nullptr)
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ top_candidates->Empty  [L211] if_statement@210 (mode == InnerSearchMode::RANGE_SEARCH) → if_statement@211 (dist > inner_search_param.radius + THRESHOLD_ERROR && not top_candidates->Empty())
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ top_candidates->Pop  [L212] if_statement@210 (mode == InnerSearchMode::RANGE_SEARCH) → if_statement@211 (dist > inner_search_param.radius + THRESHOLD_ERROR && not top_candidates->Empty())
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ candidate_set->Push  [L215] 函数本体；短路求值/提前返回见源码
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ traversal_priority  [L215] 函数本体；短路求值/提前返回见源码
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ vl->Set  [L216] 函数本体；短路求值/提前返回见源码
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ top_candidates->Empty  [L218] conditional_expression@218 top_candidates->Empty()
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ std::numeric_limits<float>::max  [L218] conditional_expression@218 top_candidates->Empty()
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ top_candidates->Top  [L218] conditional_expression@218 top_candidates->Empty()
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ graph->MaximumDegree  [L219] 函数本体；短路求值/提前返回见源码
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ graph->MaximumDegree  [L220] 函数本体；短路求值/提前返回见源码
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ graph->MaximumDegree  [L221] 函数本体；短路求值/提前返回见源码
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ candidate_set->Empty  [L222] while_statement@222 (not candidate_set->Empty())
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ candidate_set->Top  [L228] while_statement@222 (not candidate_set->Empty()) → if_statement@227 (mode == InnerSearchMode::KNN_SEARCH) → if_statement@228 (-candidate_set->Top().first > lower_bound && top_candidates->Size() >= ef)
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ top_candidates->Size  [L228] while_statement@222 (not candidate_set->Empty()) → if_statement@227 (mode == InnerSearchMode::KNN_SEARCH) → if_statement@228 (-candidate_set->Top().first > lower_bound && top_candidates->Size() >= ef)
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ candidate_set->Top  [L232] while_statement@222 (not candidate_set->Empty())
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ candidate_set->Pop  [L233] while_statement@222 (not candidate_set->Empty())
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ candidate_set->Empty  [L234] while_statement@222 (not candidate_set->Empty()) → if_statement@234 (not candidate_set->Empty())
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ graph->Prefetch  [L235] while_statement@222 (not candidate_set->Empty()) → if_statement@234 (not candidate_set->Empty())
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ candidate_set->Top  [L235] while_statement@222 (not candidate_set->Empty()) → if_statement@234 (not candidate_set->Empty())
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ visit  [L238] while_statement@222 (not candidate_set->Empty())
  │    │    │    │    │  #29 BasicSearcher::visit [src/impl/searcher/basic_searcher.cpp:43]
  │    │    │    │    │    ├─ graph->GetNeighbors  [L55] if_statement@53 (this->mutex_array_ != nullptr)
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ graph->GetNeighbors  [L57] if_statement@53 (this->mutex_array_ != nullptr) [else 分支]
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ neighbors.size  [L60] for_statement@60 i < neighbors.size()
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ neighbors.size  [L61] for_statement@60 i < neighbors.size() → if_statement@61 (i + prefetch_stride_visit_ < neighbors.size())
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ vl->Prefetch  [L62] for_statement@60 i < neighbors.size() → if_statement@61 (i + prefetch_stride_visit_ < neighbors.size())
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ vl->Get  [L64] for_statement@60 i < neighbors.size() → if_statement@64 (not vl->Get(neighbors[i]))
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ vl->Set  [L65] for_statement@60 i < neighbors.size() → if_statement@64 (not vl->Get(neighbors[i]))
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ skip_strategy->ShouldVisit  [L67] for_statement@60 i < neighbors.size() → if_statement@64 (not vl->Get(neighbors[i])) → if_statement@66 (not filter || count_no_visited == 0 || skip_strategy == nullptr || skip_strategy->ShouldVisit() || filter->CheckValid(neighbors[i]))
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ filter->CheckValid  [L67] for_statement@60 i < neighbors.size() → if_statement@64 (not vl->Get(neighbors[i])) → if_statement@66 (not filter || count_no_visited == 0 || skip_strategy == nullptr || skip_strategy->ShouldVisit() || filter->CheckValid(neighbors[i]))
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ distance_provider.BatchQueryDistance  [L239] while_statement@222 (not candidate_set->Empty())
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ line_dists.data  [L240] while_statement@222 (not candidate_set->Empty())
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ to_be_visited_id.data  [L240] while_statement@222 (not candidate_set->Empty())
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ distance_provider.IsValid  [L245] while_statement@222 (not candidate_set->Empty()) → for_statement@242 i < count_no_visited → if_statement@245 (not distance_provider.IsValid(id))
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ reasoning->RecordVisit  [L249] while_statement@222 (not candidate_set->Empty()) → for_statement@242 i < count_no_visited → if_statement@248 (reasoning != nullptr)
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ distance_provider.OriginalId  [L249] while_statement@222 (not candidate_set->Empty()) → for_statement@242 i < count_no_visited → if_statement@248 (reasoning != nullptr)
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ is_finite_distance  [L251] while_statement@222 (not candidate_set->Empty()) → for_statement@242 i < count_no_visited → if_statement@251 (not is_finite_distance(dist))
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ candidate_set->Push  [L252] while_statement@222 (not candidate_set->Empty()) → for_statement@242 i < count_no_visited → if_statement@251 (not is_finite_distance(dist))
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ traversal_priority  [L252] while_statement@222 (not candidate_set->Empty()) → for_statement@242 i < count_no_visited → if_statement@251 (not is_finite_distance(dist))
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ check_func  [L253] while_statement@222 (not candidate_set->Empty()) → for_statement@242 i < count_no_visited → if_statement@251 (not is_finite_distance(dist)) → if_statement@253 (check_func(id) and is_result_distance_eligible<mode>(dist, inner_search_param))
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ is_result_distance_eligible<mode>  [L254] while_statement@222 (not candidate_set->Empty()) → for_statement@242 i < count_no_visited → if_statement@251 (not is_finite_distance(dist)) → if_statement@253 (check_func(id) and is_result_distance_eligible<mode>(dist, inner_search_param))
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ top_candidates->Push  [L255] while_statement@222 (not candidate_set->Empty()) → for_statement@242 i < count_no_visited → if_statement@251 (not is_finite_distance(dist)) → if_statement@253 (check_func(id) and is_result_distance_eligible<mode>(dist, inner_search_param))
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ top_candidates->Size  [L257] while_statement@222 (not candidate_set->Empty()) → for_statement@242 i < count_no_visited → if_statement@251 (not is_finite_distance(dist)) → if_statement@253 (check_func(id) and is_result_distance_eligible<mode>(dist, inner_search_param)) → if_statement@256 (mode == InnerSearchMode::KNN_SEARCH) → if_statement@257 (top_candidates->Size() > ef)
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ reasoning->RecordEviction  [L259] while_statement@222 (not candidate_set->Empty()) → for_statement@242 i < count_no_visited → if_statement@251 (not is_finite_distance(dist)) → if_statement@253 (check_func(id) and is_result_distance_eligible<mode>(dist, inner_search_param)) → if_statement@256 (mode == InnerSearchMode::KNN_SEARCH) → if_statement@257 (top_candidates->Size() > ef) → if_statement@258 (reasoning != nullptr)
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ distance_provider.OriginalId  [L260] while_statement@222 (not candidate_set->Empty()) → for_statement@242 i < count_no_visited → if_statement@251 (not is_finite_distance(dist)) → if_statement@253 (check_func(id) and is_result_distance_eligible<mode>(dist, inner_search_param)) → if_statement@256 (mode == InnerSearchMode::KNN_SEARCH) → if_statement@257 (top_candidates->Size() > ef) → if_statement@258 (reasoning != nullptr)
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ top_candidates->Top  [L260] while_statement@222 (not candidate_set->Empty()) → for_statement@242 i < count_no_visited → if_statement@251 (not is_finite_distance(dist)) → if_statement@253 (check_func(id) and is_result_distance_eligible<mode>(dist, inner_search_param)) → if_statement@256 (mode == InnerSearchMode::KNN_SEARCH) → if_statement@257 (top_candidates->Size() > ef) → if_statement@258 (reasoning != nullptr)
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ top_candidates->Pop  [L263] while_statement@222 (not candidate_set->Empty()) → for_statement@242 i < count_no_visited → if_statement@251 (not is_finite_distance(dist)) → if_statement@253 (check_func(id) and is_result_distance_eligible<mode>(dist, inner_search_param)) → if_statement@256 (mode == InnerSearchMode::KNN_SEARCH) → if_statement@257 (top_candidates->Size() > ef)
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ top_candidates->Pop  [L266] while_statement@222 (not candidate_set->Empty()) → for_statement@242 i < count_no_visited → if_statement@251 (not is_finite_distance(dist)) → if_statement@253 (check_func(id) and is_result_distance_eligible<mode>(dist, inner_search_param)) → if_statement@256 (mode == InnerSearchMode::KNN_SEARCH) [else 分支] → if_statement@265 (dist > inner_search_param.radius)
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ top_candidates->Empty  [L269] while_statement@222 (not candidate_set->Empty()) → for_statement@242 i < count_no_visited → if_statement@251 (not is_finite_distance(dist)) → if_statement@269 (not top_candidates->Empty())
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ top_candidates->Top  [L270] while_statement@222 (not candidate_set->Empty()) → for_statement@242 i < count_no_visited → if_statement@251 (not is_finite_distance(dist)) → if_statement@269 (not top_candidates->Empty())
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ top_candidates->Size  [L274] while_statement@222 (not candidate_set->Empty()) → for_statement@242 i < count_no_visited → if_statement@274 (top_candidates->Size() < ef || lower_bound > dist || (mode == InnerSearchMode::RANGE_SEARCH && dist <= inner_search_param.radius + THRESHOLD_ERROR))
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ candidate_set->Push  [L277] while_statement@222 (not candidate_set->Empty()) → for_statement@242 i < count_no_visited → if_statement@274 (top_candidates->Size() < ef || lower_bound > dist || (mode == InnerSearchMode::RANGE_SEARCH && dist <= inner_search_param.radius + THRESHOLD_ERROR))
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ distance_provider.Prefetch  [L278] while_statement@222 (not candidate_set->Empty()) → for_statement@242 i < count_no_visited → if_statement@274 (top_candidates->Size() < ef || lower_bound > dist || (mode == InnerSearchMode::RANGE_SEARCH && dist <= inner_search_param.radius + THRESHOLD_ERROR))
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ candidate_set->Top  [L278] while_statement@222 (not candidate_set->Empty()) → for_statement@242 i < count_no_visited → if_statement@274 (top_candidates->Size() < ef || lower_bound > dist || (mode == InnerSearchMode::RANGE_SEARCH && dist <= inner_search_param.radius + THRESHOLD_ERROR))
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ check_func  [L279] while_statement@222 (not candidate_set->Empty()) → for_statement@242 i < count_no_visited → if_statement@274 (top_candidates->Size() < ef || lower_bound > dist || (mode == InnerSearchMode::RANGE_SEARCH && dist <= inner_search_param.radius + THRESHOLD_ERROR)) → if_statement@279 (check_func(id))
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ top_candidates->Push  [L280] while_statement@222 (not candidate_set->Empty()) → for_statement@242 i < count_no_visited → if_statement@274 (top_candidates->Size() < ef || lower_bound > dist || (mode == InnerSearchMode::RANGE_SEARCH && dist <= inner_search_param.radius + THRESHOLD_ERROR)) → if_statement@279 (check_func(id))
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ reasoning->RecordFilterReject  [L282] while_statement@222 (not candidate_set->Empty()) → for_statement@242 i < count_no_visited → if_statement@274 (top_candidates->Size() < ef || lower_bound > dist || (mode == InnerSearchMode::RANGE_SEARCH && dist <= inner_search_param.radius + THRESHOLD_ERROR)) → if_statement@279 (check_func(id)) [else 分支] → if_statement@281 (reasoning != nullptr)
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ distance_provider.OriginalId  [L282] while_statement@222 (not candidate_set->Empty()) → for_statement@242 i < count_no_visited → if_statement@274 (top_candidates->Size() < ef || lower_bound > dist || (mode == InnerSearchMode::RANGE_SEARCH && dist <= inner_search_param.radius + THRESHOLD_ERROR)) → if_statement@279 (check_func(id)) [else 分支] → if_statement@281 (reasoning != nullptr)
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ top_candidates->Size  [L285] while_statement@222 (not candidate_set->Empty()) → for_statement@242 i < count_no_visited → if_statement@274 (top_candidates->Size() < ef || lower_bound > dist || (mode == InnerSearchMode::RANGE_SEARCH && dist <= inner_search_param.radius + THRESHOLD_ERROR)) → if_statement@284 (mode == InnerSearchMode::KNN_SEARCH) → if_statement@285 (top_candidates->Size() > ef)
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ reasoning->RecordEviction  [L287] while_statement@222 (not candidate_set->Empty()) → for_statement@242 i < count_no_visited → if_statement@274 (top_candidates->Size() < ef || lower_bound > dist || (mode == InnerSearchMode::RANGE_SEARCH && dist <= inner_search_param.radius + THRESHOLD_ERROR)) → if_statement@284 (mode == InnerSearchMode::KNN_SEARCH) → if_statement@285 (top_candidates->Size() > ef) → if_statement@286 (reasoning != nullptr)
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ distance_provider.OriginalId  [L288] while_statement@222 (not candidate_set->Empty()) → for_statement@242 i < count_no_visited → if_statement@274 (top_candidates->Size() < ef || lower_bound > dist || (mode == InnerSearchMode::RANGE_SEARCH && dist <= inner_search_param.radius + THRESHOLD_ERROR)) → if_statement@284 (mode == InnerSearchMode::KNN_SEARCH) → if_statement@285 (top_candidates->Size() > ef) → if_statement@286 (reasoning != nullptr)
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ top_candidates->Top  [L288] while_statement@222 (not candidate_set->Empty()) → for_statement@242 i < count_no_visited → if_statement@274 (top_candidates->Size() < ef || lower_bound > dist || (mode == InnerSearchMode::RANGE_SEARCH && dist <= inner_search_param.radius + THRESHOLD_ERROR)) → if_statement@284 (mode == InnerSearchMode::KNN_SEARCH) → if_statement@285 (top_candidates->Size() > ef) → if_statement@286 (reasoning != nullptr)
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ top_candidates->Pop  [L290] while_statement@222 (not candidate_set->Empty()) → for_statement@242 i < count_no_visited → if_statement@274 (top_candidates->Size() < ef || lower_bound > dist || (mode == InnerSearchMode::RANGE_SEARCH && dist <= inner_search_param.radius + THRESHOLD_ERROR)) → if_statement@284 (mode == InnerSearchMode::KNN_SEARCH) → if_statement@285 (top_candidates->Size() > ef)
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ top_candidates->Empty  [L293] while_statement@222 (not candidate_set->Empty()) → for_statement@242 i < count_no_visited → if_statement@274 (top_candidates->Size() < ef || lower_bound > dist || (mode == InnerSearchMode::RANGE_SEARCH && dist <= inner_search_param.radius + THRESHOLD_ERROR)) → if_statement@293 (not top_candidates->Empty())
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ top_candidates->Top  [L294] while_statement@222 (not candidate_set->Empty()) → for_statement@242 i < count_no_visited → if_statement@274 (top_candidates->Size() < ef || lower_bound > dist || (mode == InnerSearchMode::RANGE_SEARCH && dist <= inner_search_param.radius + THRESHOLD_ERROR)) → if_statement@293 (not top_candidates->Empty())
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ top_candidates->Size  [L300] if_statement@299 (mode == InnerSearchMode::KNN_SEARCH) → while_statement@300 (top_candidates->Size() > inner_search_param.topk)
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ top_candidates->Pop  [L301] if_statement@299 (mode == InnerSearchMode::KNN_SEARCH) → while_statement@300 (top_candidates->Size() > inner_search_param.topk)
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ top_candidates->Size  [L305] if_statement@299 (mode == InnerSearchMode::KNN_SEARCH) [else 分支] → if_statement@304 (inner_search_param.range_search_limit_size > 0) → while_statement@305 (top_candidates->Size() > inner_search_param.range_search_limit_size)
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ top_candidates->Pop  [L306] if_statement@299 (mode == InnerSearchMode::KNN_SEARCH) [else 分支] → if_statement@304 (inner_search_param.range_search_limit_size > 0) → while_statement@305 (top_candidates->Size() > inner_search_param.range_search_limit_size)
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ top_candidates->Empty  [L309] if_statement@299 (mode == InnerSearchMode::KNN_SEARCH) [else 分支] → while_statement@309 (not top_candidates->Empty() && top_candidates->Top().first > inner_search_param.radius + THRESHOLD_ERROR)
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ top_candidates->Top  [L310] if_statement@299 (mode == InnerSearchMode::KNN_SEARCH) [else 分支] → while_statement@309 (not top_candidates->Empty() && top_candidates->Top().first > inner_search_param.radius + THRESHOLD_ERROR)
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ top_candidates->Pop  [L311] if_statement@299 (mode == InnerSearchMode::KNN_SEARCH) [else 分支] → while_statement@309 (not top_candidates->Empty() && top_candidates->Top().first > inner_search_param.radius + THRESHOLD_ERROR)
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ ctx->stats->dist_cmp.fetch_add  [L315] if_statement@314 (ctx != nullptr && ctx->stats != nullptr)
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ ctx->stats->hops.fetch_add  [L316] if_statement@314 (ctx != nullptr && ctx->stats != nullptr)
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │  #30 BasicSearcher::search_impl [src/impl/searcher/basic_searcher.cpp:322]
  │    │    │    │    ├─ select_query_allocator  [L332] 函数本体；短路求值/提前返回见源码
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ std::make_shared<StandardHeap<true, false>>  [L334] 函数本体；短路求值/提前返回见源码
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ std::make_shared<StandardHeap<true, false>>  [L335] 函数本体；短路求值/提前返回见源码
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ AcquireQueryComputer  [L341] 函数本体；短路求值/提前返回见源码
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ std::numeric_limits<float>::max  [L351] 函数本体；短路求值/提前返回见源码
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ graph->MaximumDegree  [L356] 函数本体；短路求值/提前返回见源码
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ graph->MaximumDegree  [L357] 函数本体；短路求值/提前返回见源码
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ graph->MaximumDegree  [L358] 函数本体；短路求值/提前返回见源码
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ graph->MaximumDegree  [L359] 函数本体；短路求值/提前返回见源码
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ create_filter_search_skip_strategy  [L360] 函数本体；短路求值/提前返回见源码
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ inner_search_param.is_inner_id_allowed->ValidRatio  [L363] conditional_expression@362 inner_search_param.is_inner_id_allowed != nullptr
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ rabitq_lower_bound_candidates->clear  [L367] if_statement@366 (rabitq_lower_bound_candidates != nullptr)
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ iter_ctx->IsFirstUsed  [L370] if_statement@370 (!iter_ctx->IsFirstUsed())
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ iter_ctx->Empty  [L371] if_statement@370 (!iter_ctx->IsFirstUsed()) → if_statement@371 (iter_ctx->Empty())
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ iter_ctx->Empty  [L374] if_statement@370 (!iter_ctx->IsFirstUsed()) → while_statement@374 (!iter_ctx->Empty())
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ iter_ctx->GetTopID  [L375] if_statement@370 (!iter_ctx->IsFirstUsed()) → while_statement@374 (!iter_ctx->Empty())
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ iter_ctx->GetTopDist  [L376] if_statement@370 (!iter_ctx->IsFirstUsed()) → while_statement@374 (!iter_ctx->Empty())
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ vl->Set  [L377] if_statement@370 (!iter_ctx->IsFirstUsed()) → while_statement@374 (!iter_ctx->Empty())
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ iter_ctx->CheckPoint  [L378] if_statement@370 (!iter_ctx->IsFirstUsed()) → while_statement@374 (!iter_ctx->Empty()) → if_statement@378 (iter_ctx->CheckPoint(cur_inner_id))
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ flatten->Query  [L379] if_statement@370 (!iter_ctx->IsFirstUsed()) → while_statement@374 (!iter_ctx->Empty()) → if_statement@378 (iter_ctx->CheckPoint(cur_inner_id))
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ is_result_distance_eligible<mode>  [L382] if_statement@370 (!iter_ctx->IsFirstUsed()) → while_statement@374 (!iter_ctx->Empty()) → if_statement@378 (iter_ctx->CheckPoint(cur_inner_id)) → if_statement@382 (is_result_distance_eligible<mode>(cur_dist, inner_search_param))
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ top_candidates->Push  [L383] if_statement@370 (!iter_ctx->IsFirstUsed()) → while_statement@374 (!iter_ctx->Empty()) → if_statement@378 (iter_ctx->CheckPoint(cur_inner_id)) → if_statement@382 (is_result_distance_eligible<mode>(cur_dist, inner_search_param))
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ candidate_set->Push  [L385] if_statement@370 (!iter_ctx->IsFirstUsed()) → while_statement@374 (!iter_ctx->Empty()) → if_statement@378 (iter_ctx->CheckPoint(cur_inner_id))
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ traversal_priority  [L385] if_statement@370 (!iter_ctx->IsFirstUsed()) → while_statement@374 (!iter_ctx->Empty()) → if_statement@378 (iter_ctx->CheckPoint(cur_inner_id))
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ top_candidates->Empty  [L387] if_statement@370 (!iter_ctx->IsFirstUsed()) → while_statement@374 (!iter_ctx->Empty()) → if_statement@378 (iter_ctx->CheckPoint(cur_inner_id)) → if_statement@386 (mode == InnerSearchMode::RANGE_SEARCH) → if_statement@387 (cur_dist > inner_search_param.radius and not top_candidates->Empty())
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ top_candidates->Pop  [L388] if_statement@370 (!iter_ctx->IsFirstUsed()) → while_statement@374 (!iter_ctx->Empty()) → if_statement@378 (iter_ctx->CheckPoint(cur_inner_id)) → if_statement@386 (mode == InnerSearchMode::RANGE_SEARCH) → if_statement@387 (cur_dist > inner_search_param.radius and not top_candidates->Empty())
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ iter_ctx->PopDiscard  [L392] if_statement@370 (!iter_ctx->IsFirstUsed()) → while_statement@374 (!iter_ctx->Empty())
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ top_candidates->Size  [L395] if_statement@370 (!iter_ctx->IsFirstUsed()) → if_statement@394 (mode == InnerSearchMode::KNN_SEARCH) → while_statement@395 (top_candidates->Size() > ef)
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ top_candidates->Top  [L396] if_statement@370 (!iter_ctx->IsFirstUsed()) → if_statement@394 (mode == InnerSearchMode::KNN_SEARCH) → while_statement@395 (top_candidates->Size() > ef)
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ iter_ctx->CheckPoint  [L397] if_statement@370 (!iter_ctx->IsFirstUsed()) → if_statement@394 (mode == InnerSearchMode::KNN_SEARCH) → while_statement@395 (top_candidates->Size() > ef) → if_statement@397 (iter_ctx->CheckPoint(cur_node_pair.second))
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ iter_ctx->AddDiscardNode  [L398] if_statement@370 (!iter_ctx->IsFirstUsed()) → if_statement@394 (mode == InnerSearchMode::KNN_SEARCH) → while_statement@395 (top_candidates->Size() > ef) → if_statement@397 (iter_ctx->CheckPoint(cur_node_pair.second))
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ top_candidates->Pop  [L400] if_statement@370 (!iter_ctx->IsFirstUsed()) → if_statement@394 (mode == InnerSearchMode::KNN_SEARCH) → while_statement@395 (top_candidates->Size() > ef)
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ top_candidates->Empty  [L403] if_statement@370 (!iter_ctx->IsFirstUsed()) → if_statement@403 (not top_candidates->Empty())
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ top_candidates->Top  [L404] if_statement@370 (!iter_ctx->IsFirstUsed()) → if_statement@403 (not top_candidates->Empty())
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ flatten->QueryWithDistanceLowerBound  [L408] if_statement@370 (!iter_ctx->IsFirstUsed()) [else 分支] → if_statement@407 (inner_search_param.enable_rabitq_one_bit_search)
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ flatten->Query  [L410] if_statement@370 (!iter_ctx->IsFirstUsed()) [else 分支] → if_statement@407 (inner_search_param.enable_rabitq_one_bit_search) [else 分支]
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ is_id_allowed->CheckValid  [L412] if_statement@370 (!iter_ctx->IsFirstUsed()) [else 分支] → if_statement@412 (not is_id_allowed || is_id_allowed->CheckValid(ep))
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ is_result_distance_eligible<mode>  [L413] if_statement@370 (!iter_ctx->IsFirstUsed()) [else 分支] → if_statement@412 (not is_id_allowed || is_id_allowed->CheckValid(ep)) → if_statement@413 (is_result_distance_eligible<mode>(dist, inner_search_param))
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ top_candidates->Push  [L414] if_statement@370 (!iter_ctx->IsFirstUsed()) [else 分支] → if_statement@412 (not is_id_allowed || is_id_allowed->CheckValid(ep)) → if_statement@413 (is_result_distance_eligible<mode>(dist, inner_search_param))
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ top_candidates->Top  [L415] if_statement@370 (!iter_ctx->IsFirstUsed()) [else 分支] → if_statement@412 (not is_id_allowed || is_id_allowed->CheckValid(ep)) → if_statement@413 (is_result_distance_eligible<mode>(dist, inner_search_param))
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ candidate_set->Push  [L418] if_statement@370 (!iter_ctx->IsFirstUsed()) [else 分支]
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ traversal_priority  [L418] if_statement@370 (!iter_ctx->IsFirstUsed()) [else 分支]
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ vl->Set  [L419] if_statement@370 (!iter_ctx->IsFirstUsed()) [else 分支]
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ candidate_set->Empty  [L422] while_statement@422 (not candidate_set->Empty())
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ candidate_set->Top  [L427] while_statement@422 (not candidate_set->Empty())
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ top_candidates->Size  [L430] while_statement@422 (not candidate_set->Empty()) → if_statement@429 (mode == InnerSearchMode::KNN_SEARCH) → if_statement@430 ((-current_node_pair.first) > lower_bound && top_candidates->Size() >= ef)
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ reasoning->SetTermination  [L432] while_statement@422 (not candidate_set->Empty()) → if_statement@429 (mode == InnerSearchMode::KNN_SEARCH) → if_statement@430 ((-current_node_pair.first) > lower_bound && top_candidates->Size() >= ef) → if_statement@431 (reasoning != nullptr)
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ candidate_set->Pop  [L437] while_statement@422 (not candidate_set->Empty())
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ candidate_set->Empty  [L439] while_statement@422 (not candidate_set->Empty()) → if_statement@439 (not candidate_set->Empty())
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ graph->Prefetch  [L440] while_statement@422 (not candidate_set->Empty()) → if_statement@439 (not candidate_set->Empty())
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ candidate_set->Top  [L440] while_statement@422 (not candidate_set->Empty()) → if_statement@439 (not candidate_set->Empty())
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ visit  [L443] while_statement@422 (not candidate_set->Empty())
  │    │    │    │    │  ↳ 复用节点 #29 BasicSearcher::visit（本树前文已展开）
  │    │    │    │    ├─ skip_strategy.get  [L447] while_statement@422 (not candidate_set->Empty())
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ top_candidates->Size  [L454] while_statement@422 (not candidate_set->Empty()) → if_statement@454 (inner_search_param.enable_rabitq_one_bit_search and top_candidates->Size() == ef and rabitq_lower_bound_candidates != nullptr)
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ flatten->QueryWithDistanceLowerBound  [L457] while_statement@422 (not candidate_set->Empty()) → if_statement@454 (inner_search_param.enable_rabitq_one_bit_search and top_candidates->Size() == ef and rabitq_lower_bound_candidates != nullptr)
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ line_dists.data  [L457] while_statement@422 (not candidate_set->Empty()) → if_statement@454 (inner_search_param.enable_rabitq_one_bit_search and top_candidates->Size() == ef and rabitq_lower_bound_candidates != nullptr)
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ lower_bound_dists.data  [L458] while_statement@422 (not candidate_set->Empty()) → if_statement@454 (inner_search_param.enable_rabitq_one_bit_search and top_candidates->Size() == ef and rabitq_lower_bound_candidates != nullptr)
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ to_be_visited_id.data  [L460] while_statement@422 (not candidate_set->Empty()) → if_statement@454 (inner_search_param.enable_rabitq_one_bit_search and top_candidates->Size() == ef and rabitq_lower_bound_candidates != nullptr)
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ flatten->QueryWithDistanceLowerBound  [L464] while_statement@422 (not candidate_set->Empty()) → if_statement@454 (inner_search_param.enable_rabitq_one_bit_search and top_candidates->Size() == ef and rabitq_lower_bound_candidates != nullptr) [else 分支] → if_statement@463 (inner_search_param.enable_rabitq_one_bit_search)
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ line_dists.data  [L464] while_statement@422 (not candidate_set->Empty()) → if_statement@454 (inner_search_param.enable_rabitq_one_bit_search and top_candidates->Size() == ef and rabitq_lower_bound_candidates != nullptr) [else 分支] → if_statement@463 (inner_search_param.enable_rabitq_one_bit_search)
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ to_be_visited_id.data  [L467] while_statement@422 (not candidate_set->Empty()) → if_statement@454 (inner_search_param.enable_rabitq_one_bit_search and top_candidates->Size() == ef and rabitq_lower_bound_candidates != nullptr) [else 分支] → if_statement@463 (inner_search_param.enable_rabitq_one_bit_search)
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ flatten->Query  [L471] while_statement@422 (not candidate_set->Empty()) → if_statement@454 (inner_search_param.enable_rabitq_one_bit_search and top_candidates->Size() == ef and rabitq_lower_bound_candidates != nullptr) [else 分支] → if_statement@463 (inner_search_param.enable_rabitq_one_bit_search) [else 分支]
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ line_dists.data  [L472] while_statement@422 (not candidate_set->Empty()) → if_statement@454 (inner_search_param.enable_rabitq_one_bit_search and top_candidates->Size() == ef and rabitq_lower_bound_candidates != nullptr) [else 分支] → if_statement@463 (inner_search_param.enable_rabitq_one_bit_search) [else 分支]
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ to_be_visited_id.data  [L472] while_statement@422 (not candidate_set->Empty()) → if_statement@454 (inner_search_param.enable_rabitq_one_bit_search and top_candidates->Size() == ef and rabitq_lower_bound_candidates != nullptr) [else 分支] → if_statement@463 (inner_search_param.enable_rabitq_one_bit_search) [else 分支]
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ is_finite_distance  [L477] while_statement@422 (not candidate_set->Empty()) → for_statement@474 i < count_no_visited → if_statement@477 (not is_finite_distance(dist))
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ is_result_distance_eligible<mode>  [L478] while_statement@422 (not candidate_set->Empty()) → for_statement@474 i < count_no_visited → if_statement@477 (not is_finite_distance(dist)) → if_statement@478 (is_result_distance_eligible<mode>(dist, inner_search_param) and (not is_id_allowed || is_id_allowed->CheckValid(cur_id)))
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ is_id_allowed->CheckValid  [L479] while_statement@422 (not candidate_set->Empty()) → for_statement@474 i < count_no_visited → if_statement@477 (not is_finite_distance(dist)) → if_statement@478 (is_result_distance_eligible<mode>(dist, inner_search_param) and (not is_id_allowed || is_id_allowed->CheckValid(cur_id)))
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ top_candidates->Push  [L480] while_statement@422 (not candidate_set->Empty()) → for_statement@474 i < count_no_visited → if_statement@477 (not is_finite_distance(dist)) → if_statement@478 (is_result_distance_eligible<mode>(dist, inner_search_param) and (not is_id_allowed || is_id_allowed->CheckValid(cur_id)))
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ top_candidates->Size  [L482] while_statement@422 (not candidate_set->Empty()) → for_statement@474 i < count_no_visited → if_statement@477 (not is_finite_distance(dist)) → if_statement@478 (is_result_distance_eligible<mode>(dist, inner_search_param) and (not is_id_allowed || is_id_allowed->CheckValid(cur_id))) → if_statement@481 (mode == KNN_SEARCH) → if_statement@482 (top_candidates->Size() > ef)
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ top_candidates->Top  [L483] while_statement@422 (not candidate_set->Empty()) → for_statement@474 i < count_no_visited → if_statement@477 (not is_finite_distance(dist)) → if_statement@478 (is_result_distance_eligible<mode>(dist, inner_search_param) and (not is_id_allowed || is_id_allowed->CheckValid(cur_id))) → if_statement@481 (mode == KNN_SEARCH) → if_statement@482 (top_candidates->Size() > ef)
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ iter_ctx->CheckPoint  [L484] while_statement@422 (not candidate_set->Empty()) → for_statement@474 i < count_no_visited → if_statement@477 (not is_finite_distance(dist)) → if_statement@478 (is_result_distance_eligible<mode>(dist, inner_search_param) and (not is_id_allowed || is_id_allowed->CheckValid(cur_id))) → if_statement@481 (mode == KNN_SEARCH) → if_statement@482 (top_candidates->Size() > ef) → if_statement@484 (iter_ctx->CheckPoint(evicted.second))
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ iter_ctx->AddDiscardNode  [L485] while_statement@422 (not candidate_set->Empty()) → for_statement@474 i < count_no_visited → if_statement@477 (not is_finite_distance(dist)) → if_statement@478 (is_result_distance_eligible<mode>(dist, inner_search_param) and (not is_id_allowed || is_id_allowed->CheckValid(cur_id))) → if_statement@481 (mode == KNN_SEARCH) → if_statement@482 (top_candidates->Size() > ef) → if_statement@484 (iter_ctx->CheckPoint(evicted.second))
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ top_candidates->Pop  [L487] while_statement@422 (not candidate_set->Empty()) → for_statement@474 i < count_no_visited → if_statement@477 (not is_finite_distance(dist)) → if_statement@478 (is_result_distance_eligible<mode>(dist, inner_search_param) and (not is_id_allowed || is_id_allowed->CheckValid(cur_id))) → if_statement@481 (mode == KNN_SEARCH) → if_statement@482 (top_candidates->Size() > ef)
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ top_candidates->Pop  [L490] while_statement@422 (not candidate_set->Empty()) → for_statement@474 i < count_no_visited → if_statement@477 (not is_finite_distance(dist)) → if_statement@478 (is_result_distance_eligible<mode>(dist, inner_search_param) and (not is_id_allowed || is_id_allowed->CheckValid(cur_id))) → if_statement@481 (mode == KNN_SEARCH) [else 分支] → if_statement@489 (dist > inner_search_param.radius)
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ iter_ctx->CheckPoint  [L493] while_statement@422 (not candidate_set->Empty()) → for_statement@474 i < count_no_visited → if_statement@477 (not is_finite_distance(dist)) → if_statement@493 (iter_ctx->CheckPoint(cur_id))
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ candidate_set->Push  [L494] while_statement@422 (not candidate_set->Empty()) → for_statement@474 i < count_no_visited → if_statement@477 (not is_finite_distance(dist)) → if_statement@493 (iter_ctx->CheckPoint(cur_id))
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ traversal_priority  [L494] while_statement@422 (not candidate_set->Empty()) → for_statement@474 i < count_no_visited → if_statement@477 (not is_finite_distance(dist)) → if_statement@493 (iter_ctx->CheckPoint(cur_id))
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ flatten->Prefetch  [L495] while_statement@422 (not candidate_set->Empty()) → for_statement@474 i < count_no_visited → if_statement@477 (not is_finite_distance(dist)) → if_statement@493 (iter_ctx->CheckPoint(cur_id))
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ top_candidates->Empty  [L497] while_statement@422 (not candidate_set->Empty()) → for_statement@474 i < count_no_visited → if_statement@477 (not is_finite_distance(dist)) → if_statement@497 (not top_candidates->Empty())
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ top_candidates->Top  [L498] while_statement@422 (not candidate_set->Empty()) → for_statement@474 i < count_no_visited → if_statement@477 (not is_finite_distance(dist)) → if_statement@497 (not top_candidates->Empty())
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ is_id_allowed->CheckValid  [L502] while_statement@422 (not candidate_set->Empty()) → for_statement@474 i < count_no_visited
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ iter_ctx->CheckPoint  [L505] while_statement@422 (not candidate_set->Empty()) → for_statement@474 i < count_no_visited → if_statement@503 (mode == KNN_SEARCH) → if_statement@504 (collect_rabitq_lower_bound and lower_bound_dists[i] < lower_bound and id_allowed and iter_ctx->CheckPoint(cur_id))
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ rabitq_lower_bound_candidates->emplace_back  [L506] while_statement@422 (not candidate_set->Empty()) → for_statement@474 i < count_no_visited → if_statement@503 (mode == KNN_SEARCH) → if_statement@504 (collect_rabitq_lower_bound and lower_bound_dists[i] < lower_bound and id_allowed and iter_ctx->CheckPoint(cur_id))
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ top_candidates->Size  [L509] while_statement@422 (not candidate_set->Empty()) → for_statement@474 i < count_no_visited → if_statement@509 (top_candidates->Size() < ef || lower_bound > dist || (mode == RANGE_SEARCH && dist <= inner_search_param.radius))
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ iter_ctx->CheckPoint  [L511] while_statement@422 (not candidate_set->Empty()) → for_statement@474 i < count_no_visited → if_statement@509 (top_candidates->Size() < ef || lower_bound > dist || (mode == RANGE_SEARCH && dist <= inner_search_param.radius)) → if_statement@511 (!iter_ctx->CheckPoint(cur_id))
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ candidate_set->Push  [L514] while_statement@422 (not candidate_set->Empty()) → for_statement@474 i < count_no_visited → if_statement@509 (top_candidates->Size() < ef || lower_bound > dist || (mode == RANGE_SEARCH && dist <= inner_search_param.radius))
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ flatten->Prefetch  [L515] while_statement@422 (not candidate_set->Empty()) → for_statement@474 i < count_no_visited → if_statement@509 (top_candidates->Size() < ef || lower_bound > dist || (mode == RANGE_SEARCH && dist <= inner_search_param.radius))
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ candidate_set->Top  [L515] while_statement@422 (not candidate_set->Empty()) → for_statement@474 i < count_no_visited → if_statement@509 (top_candidates->Size() < ef || lower_bound > dist || (mode == RANGE_SEARCH && dist <= inner_search_param.radius))
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ top_candidates->Push  [L517] while_statement@422 (not candidate_set->Empty()) → for_statement@474 i < count_no_visited → if_statement@509 (top_candidates->Size() < ef || lower_bound > dist || (mode == RANGE_SEARCH && dist <= inner_search_param.radius)) → if_statement@516 (id_allowed)
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ top_candidates->Size  [L521] while_statement@422 (not candidate_set->Empty()) → for_statement@474 i < count_no_visited → if_statement@509 (top_candidates->Size() < ef || lower_bound > dist || (mode == RANGE_SEARCH && dist <= inner_search_param.radius)) → if_statement@520 (mode == KNN_SEARCH) → if_statement@521 (top_candidates->Size() > ef)
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ iter_ctx->CheckPoint  [L522] while_statement@422 (not candidate_set->Empty()) → for_statement@474 i < count_no_visited → if_statement@509 (top_candidates->Size() < ef || lower_bound > dist || (mode == RANGE_SEARCH && dist <= inner_search_param.radius)) → if_statement@520 (mode == KNN_SEARCH) → if_statement@521 (top_candidates->Size() > ef) → if_statement@522 (iter_ctx->CheckPoint(top_candidates->Top().second))
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ top_candidates->Top  [L522] while_statement@422 (not candidate_set->Empty()) → for_statement@474 i < count_no_visited → if_statement@509 (top_candidates->Size() < ef || lower_bound > dist || (mode == RANGE_SEARCH && dist <= inner_search_param.radius)) → if_statement@520 (mode == KNN_SEARCH) → if_statement@521 (top_candidates->Size() > ef) → if_statement@522 (iter_ctx->CheckPoint(top_candidates->Top().second))
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ top_candidates->Top  [L523] while_statement@422 (not candidate_set->Empty()) → for_statement@474 i < count_no_visited → if_statement@509 (top_candidates->Size() < ef || lower_bound > dist || (mode == RANGE_SEARCH && dist <= inner_search_param.radius)) → if_statement@520 (mode == KNN_SEARCH) → if_statement@521 (top_candidates->Size() > ef) → if_statement@522 (iter_ctx->CheckPoint(top_candidates->Top().second))
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ iter_ctx->AddDiscardNode  [L524] while_statement@422 (not candidate_set->Empty()) → for_statement@474 i < count_no_visited → if_statement@509 (top_candidates->Size() < ef || lower_bound > dist || (mode == RANGE_SEARCH && dist <= inner_search_param.radius)) → if_statement@520 (mode == KNN_SEARCH) → if_statement@521 (top_candidates->Size() > ef) → if_statement@522 (iter_ctx->CheckPoint(top_candidates->Top().second))
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ top_candidates->Pop  [L526] while_statement@422 (not candidate_set->Empty()) → for_statement@474 i < count_no_visited → if_statement@509 (top_candidates->Size() < ef || lower_bound > dist || (mode == RANGE_SEARCH && dist <= inner_search_param.radius)) → if_statement@520 (mode == KNN_SEARCH) → if_statement@521 (top_candidates->Size() > ef)
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ top_candidates->Empty  [L530] while_statement@422 (not candidate_set->Empty()) → for_statement@474 i < count_no_visited → if_statement@509 (top_candidates->Size() < ef || lower_bound > dist || (mode == RANGE_SEARCH && dist <= inner_search_param.radius)) → if_statement@530 (not top_candidates->Empty())
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ top_candidates->Top  [L531] while_statement@422 (not candidate_set->Empty()) → for_statement@474 i < count_no_visited → if_statement@509 (top_candidates->Size() < ef || lower_bound > dist || (mode == RANGE_SEARCH && dist <= inner_search_param.radius)) → if_statement@530 (not top_candidates->Empty())
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ top_candidates->Size  [L538] if_statement@537 (mode == KNN_SEARCH) → while_statement@538 (top_candidates->Size() > inner_search_param.topk)
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ top_candidates->Top  [L539] if_statement@537 (mode == KNN_SEARCH) → while_statement@538 (top_candidates->Size() > inner_search_param.topk)
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ iter_ctx->CheckPoint  [L540] if_statement@537 (mode == KNN_SEARCH) → while_statement@538 (top_candidates->Size() > inner_search_param.topk) → if_statement@540 (iter_ctx->CheckPoint(cur_node_pair.second))
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ iter_ctx->AddDiscardNode  [L541] if_statement@537 (mode == KNN_SEARCH) → while_statement@538 (top_candidates->Size() > inner_search_param.topk) → if_statement@540 (iter_ctx->CheckPoint(cur_node_pair.second))
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ top_candidates->Pop  [L543] if_statement@537 (mode == KNN_SEARCH) → while_statement@538 (top_candidates->Size() > inner_search_param.topk)
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │  #31 BasicSearcher::search_impl [src/impl/searcher/basic_searcher.cpp:551]
  │    │    │    │    ├─ select_query_allocator  [L562] 函数本体；短路求值/提前返回见源码
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ std::make_shared<StandardHeap<true, false>>  [L564] 函数本体；短路求值/提前返回见源码
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ std::make_shared<StandardHeap<true, false>>  [L565] 函数本体；短路求值/提前返回见源码
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ AcquireQueryComputer  [L575] if_statement@574 (not use_custom_distance and computer == nullptr)
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ std::numeric_limits<float>::max  [L584] 函数本体；短路求值/提前返回见源码
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ graph->MaximumDegree  [L589] 函数本体；短路求值/提前返回见源码
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ graph->MaximumDegree  [L590] 函数本体；短路求值/提前返回见源码
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ graph->MaximumDegree  [L591] 函数本体；短路求值/提前返回见源码
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ graph->MaximumDegree  [L592] 函数本体；短路求值/提前返回见源码
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ std::max<uint64_t>  [L595] conditional_expression@594 use_custom_distance
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ std::min<uint64_t>  [L596] conditional_expression@594 use_custom_distance
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ graph->MaximumDegree  [L597] conditional_expression@594 use_custom_distance
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ create_filter_search_skip_strategy  [L600] 函数本体；短路求值/提前返回见源码
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ inner_search_param.is_inner_id_allowed->ValidRatio  [L603] conditional_expression@602 inner_search_param.is_inner_id_allowed != nullptr
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ rabitq_lower_bound_candidates->clear  [L607] if_statement@606 (rabitq_lower_bound_candidates != nullptr)
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ inner_search_param.executors.empty  [L611] if_statement@611 (not inner_search_param.executors.empty() and inner_search_param.executors[0] != nullptr)
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ inner_search_param.executors[0]->Clear  [L612] if_statement@611 (not inner_search_param.executors.empty() and inner_search_param.executors[0] != nullptr)
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ inner_search_param.executors[0]->Run  [L613] if_statement@611 (not inner_search_param.executors.empty() and inner_search_param.executors[0] != nullptr)
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ is_id_allowed->CheckValid  [L617] lambda@616（定义体，执行时间取决于调用/调度）
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ attr_ft->CheckValid  [L618] lambda@616（定义体，执行时间取决于调用/调度）
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ flatten->Query  [L624] lambda@622（定义体，执行时间取决于调用/调度） → if_statement@623 (not use_custom_distance)
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ CHECK_ARGUMENT  [L627] lambda@622（定义体，执行时间取决于调用/调度）
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ CHECK_ARGUMENT  [L628] lambda@622（定义体，执行时间取决于调用/调度）
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ std::min  [L633] lambda@622（定义体，执行时间取决于调用/调度） → for_statement@630 offset < count
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ label_table->GetLabelById  [L635] lambda@622（定义体，执行时间取决于调用/调度） → for_statement@630 offset < count → for_statement@634 i < batch_count
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ inner_search_param.distance_batch_func  [L637] lambda@622（定义体，执行时间取决于调用/调度） → for_statement@630 offset < count
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ custom_labels.data  [L638] lambda@622（定义体，执行时间取决于调用/调度） → for_statement@630 offset < count
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ ctx->stats->AddDistance  [L640] lambda@622（定义体，执行时间取决于调用/调度） → for_statement@630 offset < count → if_statement@639 (ctx != nullptr and ctx->stats != nullptr)
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ CHECK_ARGUMENT  [L644] lambda@622（定义体，执行时间取决于调用/调度） → for_statement@630 offset < count → for_statement@643 i < batch_count
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ is_finite_distance  [L644] lambda@622（定义体，执行时间取决于调用/调度） → for_statement@630 offset < count → for_statement@643 i < batch_count
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ score_ids  [L659] lambda@649（定义体，执行时间取决于调用/调度） → lambda@655（定义体，执行时间取决于调用/调度）
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ neighbors.data  [L659] lambda@649（定义体，执行时间取决于调用/调度） → lambda@655（定义体，执行时间取决于调用/调度）
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ lower_bound_dists.data  [L659] lambda@649（定义体，执行时间取决于调用/调度） → lambda@655（定义体，执行时间取决于调用/调度）
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ reasoning->RecordVisit  [L663] lambda@649（定义体，执行时间取决于调用/调度） → lambda@655（定义体，执行时间取决于调用/调度） → for_statement@661 i < duplicate_count → if_statement@662 (reasoning != nullptr)
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ top_candidates->Push  [L665] lambda@649（定义体，执行时间取决于调用/调度） → lambda@655（定义体，执行时间取决于调用/调度） → for_statement@661 i < duplicate_count
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ check_func  [L671] lambda@649（定义体，执行时间取决于调用/调度） → for_range_loop@670 → if_statement@671 (not check_func(item))
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ neighbors.size  [L675] lambda@649（定义体，执行时间取决于调用/调度） → for_range_loop@670 → if_statement@675 (duplicate_count == neighbors.size())
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ submit_duplicates  [L676] lambda@649（定义体，执行时间取决于调用/调度） → for_range_loop@670 → if_statement@675 (duplicate_count == neighbors.size())
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ submit_duplicates  [L679] lambda@649（定义体，执行时间取决于调用/调度）
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ top_candidates->Size  [L682] lambda@649（定义体，执行时间取决于调用/调度） → if_statement@681 (mode == KNN_SEARCH) → while_statement@682 (top_candidates->Size() > ef)
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ reasoning->RecordEviction  [L684] lambda@649（定义体，执行时间取决于调用/调度） → if_statement@681 (mode == KNN_SEARCH) → while_statement@682 (top_candidates->Size() > ef) → if_statement@683 (reasoning != nullptr)
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ top_candidates->Top  [L684] lambda@649（定义体，执行时间取决于调用/调度） → if_statement@681 (mode == KNN_SEARCH) → while_statement@682 (top_candidates->Size() > ef) → if_statement@683 (reasoning != nullptr)
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ top_candidates->Pop  [L686] lambda@649（定义体，执行时间取决于调用/调度） → if_statement@681 (mode == KNN_SEARCH) → while_statement@682 (top_candidates->Size() > ef)
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ top_candidates->Empty  [L689] lambda@649（定义体，执行时间取决于调用/调度） → if_statement@689 (not top_candidates->Empty())
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ top_candidates->Top  [L690] lambda@649（定义体，执行时间取决于调用/调度） → if_statement@689 (not top_candidates->Empty())
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ score_ids  [L695] if_statement@694 (use_custom_distance)
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ flatten->QueryWithDistanceLowerBound  [L697] if_statement@694 (use_custom_distance) [else 分支] → if_statement@696 (inner_search_param.enable_rabitq_one_bit_search)
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ flatten->Query  [L699] if_statement@694 (use_custom_distance) [else 分支] → if_statement@696 (inner_search_param.enable_rabitq_one_bit_search) [else 分支]
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ check_func  [L702] if_statement@702 (check_func(ep) and is_result_distance_eligible<mode>(dist, inner_search_param))
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ is_result_distance_eligible<mode>  [L702] if_statement@702 (check_func(ep) and is_result_distance_eligible<mode>(dist, inner_search_param))
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ top_candidates->Push  [L703] if_statement@702 (check_func(ep) and is_result_distance_eligible<mode>(dist, inner_search_param))
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ is_finite_distance  [L705] if_statement@705 (not is_finite_distance(dist) and inner_search_param.consider_duplicate and not use_custom_distance and is_result_distance_eligible<mode>(dist, inner_search_param))
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ is_result_distance_eligible<mode>  [L706] if_statement@705 (not is_finite_distance(dist) and inner_search_param.consider_duplicate and not use_custom_distance and is_result_distance_eligible<mode>(dist, inner_search_param))
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ graph->GetDuplicateIds  [L707] if_statement@705 (not is_finite_distance(dist) and inner_search_param.consider_duplicate and not use_custom_distance and is_result_distance_eligible<mode>(dist, inner_search_param)) → for_range_loop@707
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ check_func  [L708] if_statement@705 (not is_finite_distance(dist) and inner_search_param.consider_duplicate and not use_custom_distance and is_result_distance_eligible<mode>(dist, inner_search_param)) → for_range_loop@707 → if_statement@708 (check_func(duplicate_id))
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ top_candidates->Push  [L709] if_statement@705 (not is_finite_distance(dist) and inner_search_param.consider_duplicate and not use_custom_distance and is_result_distance_eligible<mode>(dist, inner_search_param)) → for_range_loop@707 → if_statement@708 (check_func(duplicate_id))
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ top_candidates->Size  [L713] if_statement@705 (not is_finite_distance(dist) and inner_search_param.consider_duplicate and not use_custom_distance and is_result_distance_eligible<mode>(dist, inner_search_param)) → if_statement@712 (mode == KNN_SEARCH) → while_statement@713 (top_candidates->Size() > ef)
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ top_candidates->Pop  [L714] if_statement@705 (not is_finite_distance(dist) and inner_search_param.consider_duplicate and not use_custom_distance and is_result_distance_eligible<mode>(dist, inner_search_param)) → if_statement@712 (mode == KNN_SEARCH) → while_statement@713 (top_candidates->Size() > ef)
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ top_candidates->Empty  [L719] if_statement@718 (mode == InnerSearchMode::RANGE_SEARCH) → while_statement@719 (dist > inner_search_param.radius and not top_candidates->Empty())
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ top_candidates->Pop  [L720] if_statement@718 (mode == InnerSearchMode::RANGE_SEARCH) → while_statement@719 (dist > inner_search_param.radius and not top_candidates->Empty())
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ top_candidates->Empty  [L723] if_statement@723 (not top_candidates->Empty())
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ top_candidates->Top  [L724] if_statement@723 (not top_candidates->Empty())
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ graph->GetDuplicateIds  [L727] if_statement@726 (use_custom_distance and inner_search_param.consider_duplicate)
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ score_duplicates  [L728] if_statement@726 (use_custom_distance and inner_search_param.consider_duplicate)
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ candidate_set->Push  [L730] 函数本体；短路求值/提前返回见源码
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ traversal_priority  [L730] 函数本体；短路求值/提前返回见源码
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ vl->Set  [L731] 函数本体；短路求值/提前返回见源码
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ candidate_set->Empty  [L733] while_statement@733 (not candidate_set->Empty())
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ reasoning->SetTermination  [L737] while_statement@733 (not candidate_set->Empty()) → if_statement@735 (hops >= inner_search_param.hops_limit) → if_statement@736 (reasoning != nullptr)
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ reasoning->AddSearchHop  [L742] while_statement@733 (not candidate_set->Empty()) → if_statement@741 (reasoning != nullptr)
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ candidate_set->Top  [L744] while_statement@733 (not candidate_set->Empty())
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ inner_search_param.time_cost->CheckOvertime  [L747] while_statement@733 (not candidate_set->Empty()) → if_statement@746 (inner_search_param.time_cost != nullptr and inner_search_param.time_cost->CheckOvertime())
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ ctx->stats->is_timeout.store  [L749] while_statement@733 (not candidate_set->Empty()) → if_statement@746 (inner_search_param.time_cost != nullptr and inner_search_param.time_cost->CheckOvertime()) → if_statement@748 (ctx != nullptr and ctx->stats != nullptr)
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ reasoning->SetTermination  [L752] while_statement@733 (not candidate_set->Empty()) → if_statement@746 (inner_search_param.time_cost != nullptr and inner_search_param.time_cost->CheckOvertime()) → if_statement@751 (reasoning != nullptr)
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ top_candidates->Size  [L758] while_statement@733 (not candidate_set->Empty()) → if_statement@757 (mode == InnerSearchMode::KNN_SEARCH) → if_statement@758 ((-current_node_pair.first) > lower_bound && top_candidates->Size() >= ef)
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ reasoning->SetTermination  [L760] while_statement@733 (not candidate_set->Empty()) → if_statement@757 (mode == InnerSearchMode::KNN_SEARCH) → if_statement@758 ((-current_node_pair.first) > lower_bound && top_candidates->Size() >= ef) → if_statement@759 (reasoning != nullptr)
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ candidate_set->Pop  [L765] while_statement@733 (not candidate_set->Empty())
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ candidate_set->Empty  [L767] while_statement@733 (not candidate_set->Empty()) → if_statement@767 (not candidate_set->Empty())
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ graph->Prefetch  [L768] while_statement@733 (not candidate_set->Empty()) → if_statement@767 (not candidate_set->Empty())
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ candidate_set->Top  [L768] while_statement@733 (not candidate_set->Empty()) → if_statement@767 (not candidate_set->Empty())
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ visit  [L771] while_statement@733 (not candidate_set->Empty())
  │    │    │    │    │  ↳ 复用节点 #29 BasicSearcher::visit（本树前文已展开）
  │    │    │    │    ├─ skip_strategy.get  [L775] while_statement@733 (not candidate_set->Empty())
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ score_ids  [L781] while_statement@733 (not candidate_set->Empty()) → if_statement@780 (use_custom_distance)
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ to_be_visited_id.data  [L781] while_statement@733 (not candidate_set->Empty()) → if_statement@780 (use_custom_distance)
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ line_dists.data  [L781] while_statement@733 (not candidate_set->Empty()) → if_statement@780 (use_custom_distance)
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ top_candidates->Size  [L783] while_statement@733 (not candidate_set->Empty()) → if_statement@780 (use_custom_distance) [else 分支] → if_statement@782 (inner_search_param.enable_rabitq_one_bit_search and top_candidates->Size() == ef and rabitq_lower_bound_candidates != nullptr)
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ flatten->QueryWithDistanceLowerBound  [L785] while_statement@733 (not candidate_set->Empty()) → if_statement@780 (use_custom_distance) [else 分支] → if_statement@782 (inner_search_param.enable_rabitq_one_bit_search and top_candidates->Size() == ef and rabitq_lower_bound_candidates != nullptr)
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ line_dists.data  [L785] while_statement@733 (not candidate_set->Empty()) → if_statement@780 (use_custom_distance) [else 分支] → if_statement@782 (inner_search_param.enable_rabitq_one_bit_search and top_candidates->Size() == ef and rabitq_lower_bound_candidates != nullptr)
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ lower_bound_dists.data  [L786] while_statement@733 (not candidate_set->Empty()) → if_statement@780 (use_custom_distance) [else 分支] → if_statement@782 (inner_search_param.enable_rabitq_one_bit_search and top_candidates->Size() == ef and rabitq_lower_bound_candidates != nullptr)
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ to_be_visited_id.data  [L788] while_statement@733 (not candidate_set->Empty()) → if_statement@780 (use_custom_distance) [else 分支] → if_statement@782 (inner_search_param.enable_rabitq_one_bit_search and top_candidates->Size() == ef and rabitq_lower_bound_candidates != nullptr)
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ flatten->QueryWithDistanceLowerBound  [L792] while_statement@733 (not candidate_set->Empty()) → if_statement@780 (use_custom_distance) [else 分支] → if_statement@782 (inner_search_param.enable_rabitq_one_bit_search and top_candidates->Size() == ef and rabitq_lower_bound_candidates != nullptr) [else 分支] → if_statement@791 (inner_search_param.enable_rabitq_one_bit_search)
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ line_dists.data  [L792] while_statement@733 (not candidate_set->Empty()) → if_statement@780 (use_custom_distance) [else 分支] → if_statement@782 (inner_search_param.enable_rabitq_one_bit_search and top_candidates->Size() == ef and rabitq_lower_bound_candidates != nullptr) [else 分支] → if_statement@791 (inner_search_param.enable_rabitq_one_bit_search)
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ to_be_visited_id.data  [L795] while_statement@733 (not candidate_set->Empty()) → if_statement@780 (use_custom_distance) [else 分支] → if_statement@782 (inner_search_param.enable_rabitq_one_bit_search and top_candidates->Size() == ef and rabitq_lower_bound_candidates != nullptr) [else 分支] → if_statement@791 (inner_search_param.enable_rabitq_one_bit_search)
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ flatten->Query  [L799] while_statement@733 (not candidate_set->Empty()) → if_statement@780 (use_custom_distance) [else 分支] → if_statement@782 (inner_search_param.enable_rabitq_one_bit_search and top_candidates->Size() == ef and rabitq_lower_bound_candidates != nullptr) [else 分支] → if_statement@791 (inner_search_param.enable_rabitq_one_bit_search) [else 分支]
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ line_dists.data  [L800] while_statement@733 (not candidate_set->Empty()) → if_statement@780 (use_custom_distance) [else 分支] → if_statement@782 (inner_search_param.enable_rabitq_one_bit_search and top_candidates->Size() == ef and rabitq_lower_bound_candidates != nullptr) [else 分支] → if_statement@791 (inner_search_param.enable_rabitq_one_bit_search) [else 分支]
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ to_be_visited_id.data  [L800] while_statement@733 (not candidate_set->Empty()) → if_statement@780 (use_custom_distance) [else 分支] → if_statement@782 (inner_search_param.enable_rabitq_one_bit_search and top_candidates->Size() == ef and rabitq_lower_bound_candidates != nullptr) [else 分支] → if_statement@791 (inner_search_param.enable_rabitq_one_bit_search) [else 分支]
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ reasoning->RecordVisit  [L808] while_statement@733 (not candidate_set->Empty()) → for_statement@804 i < count_no_visited → if_statement@807 (reasoning != nullptr)
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ graph->GetDuplicateIds  [L811] while_statement@733 (not candidate_set->Empty()) → for_statement@804 i < count_no_visited → if_statement@810 (use_custom_distance and inner_search_param.consider_duplicate)
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ score_duplicates  [L812] while_statement@733 (not candidate_set->Empty()) → for_statement@804 i < count_no_visited → if_statement@810 (use_custom_distance and inner_search_param.consider_duplicate)
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ is_finite_distance  [L814] while_statement@733 (not candidate_set->Empty()) → for_statement@804 i < count_no_visited → if_statement@814 (not is_finite_distance(dist))
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ candidate_set->Push  [L815] while_statement@733 (not candidate_set->Empty()) → for_statement@804 i < count_no_visited → if_statement@814 (not is_finite_distance(dist))
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ traversal_priority  [L815] while_statement@733 (not candidate_set->Empty()) → for_statement@804 i < count_no_visited → if_statement@814 (not is_finite_distance(dist))
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ is_result_distance_eligible<mode>  [L817] while_statement@733 (not candidate_set->Empty()) → for_statement@804 i < count_no_visited → if_statement@814 (not is_finite_distance(dist)) → lambda@816（定义体，执行时间取决于调用/调度） → if_statement@817 (not is_result_distance_eligible<mode>(dist, inner_search_param) or not check_func(result_id))
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ check_func  [L818] while_statement@733 (not candidate_set->Empty()) → for_statement@804 i < count_no_visited → if_statement@814 (not is_finite_distance(dist)) → lambda@816（定义体，执行时间取决于调用/调度） → if_statement@817 (not is_result_distance_eligible<mode>(dist, inner_search_param) or not check_func(result_id))
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ top_candidates->Push  [L821] while_statement@733 (not candidate_set->Empty()) → for_statement@804 i < count_no_visited → if_statement@814 (not is_finite_distance(dist)) → lambda@816（定义体，执行时间取决于调用/调度）
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ top_candidates->Size  [L823] while_statement@733 (not candidate_set->Empty()) → for_statement@804 i < count_no_visited → if_statement@814 (not is_finite_distance(dist)) → lambda@816（定义体，执行时间取决于调用/调度） → if_statement@822 (mode == KNN_SEARCH) → while_statement@823 (top_candidates->Size() > ef)
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ reasoning->RecordEviction  [L825] while_statement@733 (not candidate_set->Empty()) → for_statement@804 i < count_no_visited → if_statement@814 (not is_finite_distance(dist)) → lambda@816（定义体，执行时间取决于调用/调度） → if_statement@822 (mode == KNN_SEARCH) → while_statement@823 (top_candidates->Size() > ef) → if_statement@824 (reasoning != nullptr)
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ top_candidates->Top  [L825] while_statement@733 (not candidate_set->Empty()) → for_statement@804 i < count_no_visited → if_statement@814 (not is_finite_distance(dist)) → lambda@816（定义体，执行时间取决于调用/调度） → if_statement@822 (mode == KNN_SEARCH) → while_statement@823 (top_candidates->Size() > ef) → if_statement@824 (reasoning != nullptr)
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ top_candidates->Pop  [L827] while_statement@733 (not candidate_set->Empty()) → for_statement@804 i < count_no_visited → if_statement@814 (not is_finite_distance(dist)) → lambda@816（定义体，执行时间取决于调用/调度） → if_statement@822 (mode == KNN_SEARCH) → while_statement@823 (top_candidates->Size() > ef)
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ top_candidates->Pop  [L830] while_statement@733 (not candidate_set->Empty()) → for_statement@804 i < count_no_visited → if_statement@814 (not is_finite_distance(dist)) → lambda@816（定义体，执行时间取决于调用/调度） → if_statement@822 (mode == KNN_SEARCH) [else 分支] → if_statement@829 (dist > inner_search_param.radius)
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ push_result  [L833] while_statement@733 (not candidate_set->Empty()) → for_statement@804 i < count_no_visited → if_statement@814 (not is_finite_distance(dist))
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ graph->GetDuplicateIds  [L835] while_statement@733 (not candidate_set->Empty()) → for_statement@804 i < count_no_visited → if_statement@814 (not is_finite_distance(dist)) → if_statement@834 (inner_search_param.consider_duplicate and not use_custom_distance) → for_range_loop@835
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ push_result  [L836] while_statement@733 (not candidate_set->Empty()) → for_statement@804 i < count_no_visited → if_statement@814 (not is_finite_distance(dist)) → if_statement@834 (inner_search_param.consider_duplicate and not use_custom_distance) → for_range_loop@835
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ top_candidates->Empty  [L839] while_statement@733 (not candidate_set->Empty()) → for_statement@804 i < count_no_visited → if_statement@814 (not is_finite_distance(dist)) → if_statement@839 (not top_candidates->Empty())
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ top_candidates->Top  [L840] while_statement@733 (not candidate_set->Empty()) → for_statement@804 i < count_no_visited → if_statement@814 (not is_finite_distance(dist)) → if_statement@839 (not top_candidates->Empty())
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ check_func  [L846] while_statement@733 (not candidate_set->Empty()) → for_statement@804 i < count_no_visited → if_statement@844 (mode == KNN_SEARCH) → if_statement@845 (collect_rabitq_lower_bound and lower_bound_dists[i] < lower_bound and check_func(cur_id))
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ rabitq_lower_bound_candidates->emplace_back  [L847] while_statement@733 (not candidate_set->Empty()) → for_statement@804 i < count_no_visited → if_statement@844 (mode == KNN_SEARCH) → if_statement@845 (collect_rabitq_lower_bound and lower_bound_dists[i] < lower_bound and check_func(cur_id))
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ top_candidates->Size  [L850] while_statement@733 (not candidate_set->Empty()) → for_statement@804 i < count_no_visited → if_statement@850 (top_candidates->Size() < ef || lower_bound > dist || (mode == RANGE_SEARCH && dist <= inner_search_param.radius))
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ candidate_set->Push  [L852] while_statement@733 (not candidate_set->Empty()) → for_statement@804 i < count_no_visited → if_statement@850 (top_candidates->Size() < ef || lower_bound > dist || (mode == RANGE_SEARCH && dist <= inner_search_param.radius))
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ check_func  [L854] while_statement@733 (not candidate_set->Empty()) → for_statement@804 i < count_no_visited → if_statement@850 (top_candidates->Size() < ef || lower_bound > dist || (mode == RANGE_SEARCH && dist <= inner_search_param.radius)) → if_statement@854 (check_func(cur_id))
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ top_candidates->Push  [L855] while_statement@733 (not candidate_set->Empty()) → for_statement@804 i < count_no_visited → if_statement@850 (top_candidates->Size() < ef || lower_bound > dist || (mode == RANGE_SEARCH && dist <= inner_search_param.radius)) → if_statement@854 (check_func(cur_id))
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ reasoning->RecordFilterReject  [L857] while_statement@733 (not candidate_set->Empty()) → for_statement@804 i < count_no_visited → if_statement@850 (top_candidates->Size() < ef || lower_bound > dist || (mode == RANGE_SEARCH && dist <= inner_search_param.radius)) → if_statement@854 (check_func(cur_id)) [else 分支] → if_statement@856 (reasoning != nullptr)
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ graph->GetDuplicateIds  [L860] while_statement@733 (not candidate_set->Empty()) → for_statement@804 i < count_no_visited → if_statement@850 (top_candidates->Size() < ef || lower_bound > dist || (mode == RANGE_SEARCH && dist <= inner_search_param.radius)) → if_statement@859 (inner_search_param.consider_duplicate and not use_custom_distance)
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ check_func  [L862] while_statement@733 (not candidate_set->Empty()) → for_statement@804 i < count_no_visited → if_statement@850 (top_candidates->Size() < ef || lower_bound > dist || (mode == RANGE_SEARCH && dist <= inner_search_param.radius)) → if_statement@859 (inner_search_param.consider_duplicate and not use_custom_distance) → for_range_loop@861 → if_statement@862 (check_func(item))
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ top_candidates->Push  [L863] while_statement@733 (not candidate_set->Empty()) → for_statement@804 i < count_no_visited → if_statement@850 (top_candidates->Size() < ef || lower_bound > dist || (mode == RANGE_SEARCH && dist <= inner_search_param.radius)) → if_statement@859 (inner_search_param.consider_duplicate and not use_custom_distance) → for_range_loop@861 → if_statement@862 (check_func(item))
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ top_candidates->Size  [L869] while_statement@733 (not candidate_set->Empty()) → for_statement@804 i < count_no_visited → if_statement@850 (top_candidates->Size() < ef || lower_bound > dist || (mode == RANGE_SEARCH && dist <= inner_search_param.radius)) → if_statement@868 (mode == KNN_SEARCH) → if_statement@869 (top_candidates->Size() > ef)
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ reasoning->RecordEviction  [L871] while_statement@733 (not candidate_set->Empty()) → for_statement@804 i < count_no_visited → if_statement@850 (top_candidates->Size() < ef || lower_bound > dist || (mode == RANGE_SEARCH && dist <= inner_search_param.radius)) → if_statement@868 (mode == KNN_SEARCH) → if_statement@869 (top_candidates->Size() > ef) → if_statement@870 (reasoning != nullptr)
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ top_candidates->Top  [L871] while_statement@733 (not candidate_set->Empty()) → for_statement@804 i < count_no_visited → if_statement@850 (top_candidates->Size() < ef || lower_bound > dist || (mode == RANGE_SEARCH && dist <= inner_search_param.radius)) → if_statement@868 (mode == KNN_SEARCH) → if_statement@869 (top_candidates->Size() > ef) → if_statement@870 (reasoning != nullptr)
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ top_candidates->Pop  [L873] while_statement@733 (not candidate_set->Empty()) → for_statement@804 i < count_no_visited → if_statement@850 (top_candidates->Size() < ef || lower_bound > dist || (mode == RANGE_SEARCH && dist <= inner_search_param.radius)) → if_statement@868 (mode == KNN_SEARCH) → if_statement@869 (top_candidates->Size() > ef)
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ top_candidates->Empty  [L877] while_statement@733 (not candidate_set->Empty()) → for_statement@804 i < count_no_visited → if_statement@850 (top_candidates->Size() < ef || lower_bound > dist || (mode == RANGE_SEARCH && dist <= inner_search_param.radius)) → if_statement@877 (not top_candidates->Empty())
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ top_candidates->Top  [L878] while_statement@733 (not candidate_set->Empty()) → for_statement@804 i < count_no_visited → if_statement@850 (top_candidates->Size() < ef || lower_bound > dist || (mode == RANGE_SEARCH && dist <= inner_search_param.radius)) → if_statement@877 (not top_candidates->Empty())
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ top_candidates->Size  [L885] if_statement@884 (mode == KNN_SEARCH) → while_statement@885 (top_candidates->Size() > inner_search_param.topk)
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ top_candidates->Pop  [L886] if_statement@884 (mode == KNN_SEARCH) → while_statement@885 (top_candidates->Size() > inner_search_param.topk)
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ top_candidates->Size  [L890] if_statement@884 (mode == KNN_SEARCH) [else 分支] → if_statement@888 (mode == RANGE_SEARCH) → if_statement@889 (inner_search_param.range_search_limit_size > 0) → while_statement@890 (top_candidates->Size() > inner_search_param.range_search_limit_size)
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ top_candidates->Pop  [L891] if_statement@884 (mode == KNN_SEARCH) [else 分支] → if_statement@888 (mode == RANGE_SEARCH) → if_statement@889 (inner_search_param.range_search_limit_size > 0) → while_statement@890 (top_candidates->Size() > inner_search_param.range_search_limit_size)
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ top_candidates->Empty  [L894] if_statement@884 (mode == KNN_SEARCH) [else 分支] → if_statement@888 (mode == RANGE_SEARCH) → while_statement@894 (not top_candidates->Empty() && top_candidates->Top().first > inner_search_param.radius + THRESHOLD_ERROR)
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ top_candidates->Top  [L895] if_statement@884 (mode == KNN_SEARCH) [else 分支] → if_statement@888 (mode == RANGE_SEARCH) → while_statement@894 (not top_candidates->Empty() && top_candidates->Top().first > inner_search_param.radius + THRESHOLD_ERROR)
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ top_candidates->Pop  [L896] if_statement@884 (mode == KNN_SEARCH) [else 分支] → if_statement@888 (mode == RANGE_SEARCH) → while_statement@894 (not top_candidates->Empty() && top_candidates->Top().first > inner_search_param.radius + THRESHOLD_ERROR)
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ top_candidates->Empty  [L902] if_statement@901 (not use_custom_distance and inner_search_param.find_duplicate and not top_candidates->Empty())
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ top_candidates->GetData  [L903] if_statement@901 (not use_custom_distance and inner_search_param.find_duplicate and not top_candidates->Empty())
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ top_candidates->Size  [L906] if_statement@901 (not use_custom_distance and inner_search_param.find_duplicate and not top_candidates->Empty()) → for_statement@906 i < top_candidates->Size()
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ flatten->TotalCount  [L918] if_statement@901 (not use_custom_distance and inner_search_param.find_duplicate and not top_candidates->Empty()) → if_statement@912 (inner_search_param.duplicate_distance_threshold > 0.0F) [else 分支]
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ flatten->CompareVectors  [L921] if_statement@901 (not use_custom_distance and inner_search_param.find_duplicate and not top_candidates->Empty()) → if_statement@912 (inner_search_param.duplicate_distance_threshold > 0.0F) [else 分支] → conditional_expression@920 has_stored_query
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ flatten->CompareRawVectorWithId  [L922] if_statement@901 (not use_custom_distance and inner_search_param.find_duplicate and not top_candidates->Empty()) → if_statement@912 (inner_search_param.duplicate_distance_threshold > 0.0F) [else 分支] → conditional_expression@920 has_stored_query
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ stats.dist_cmp.fetch_add  [L931] if_statement@929 (ctx != nullptr and ctx->stats != nullptr)
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ stats.hops.fetch_add  [L932] if_statement@929 (ctx != nullptr and ctx->stats != nullptr)
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ this->search_impl<RANGE_SEARCH>  [L96] 函数本体；短路求值/提前返回见源码
  │    │    │    │  ├─ 以下为分派/重载候选，并非全部依次执行
  │    │    │    │  ↳ 复用节点 #28 BasicSearcher::search_impl（本树前文已展开）
  │    │    │    │  ↳ 复用节点 #30 BasicSearcher::search_impl（本树前文已展开）
  │    │    │    │  ↳ 复用节点 #31 BasicSearcher::search_impl（本树前文已展开）
  │    │    │  #32 BasicSearcher::Search [src/impl/searcher/basic_searcher.cpp:139]
  │    │    │    ├─ this->search_impl<KNN_SEARCH>  [L148] 函数本体；短路求值/提前返回见源码
  │    │    │    │  ├─ 以下为分派/重载候选，并非全部依次执行
  │    │    │    │  ↳ 复用节点 #28 BasicSearcher::search_impl（本树前文已展开）
  │    │    │    │  ↳ 复用节点 #30 BasicSearcher::search_impl（本树前文已展开）
  │    │    │    │  ↳ 复用节点 #31 BasicSearcher::search_impl（本树前文已展开）
  │    │    │  #33 BasicSearcher::Search [src/impl/searcher/basic_searcher.cpp:158]
  │    │    │    ├─ this->search_impl<InnerSearchMode::RANGE_SEARCH>  [L166] if_statement@165 (inner_search_param.search_mode == InnerSearchMode::RANGE_SEARCH)
  │    │    │    │  ├─ 以下为分派/重载候选，并非全部依次执行
  │    │    │    │  ↳ 复用节点 #28 BasicSearcher::search_impl（本树前文已展开）
  │    │    │    │  ↳ 复用节点 #30 BasicSearcher::search_impl（本树前文已展开）
  │    │    │    │  ↳ 复用节点 #31 BasicSearcher::search_impl（本树前文已展开）
  │    │    │    ├─ this->search_impl<InnerSearchMode::KNN_SEARCH>  [L169] 函数本体；短路求值/提前返回见源码
  │    │    │    │  ├─ 以下为分派/重载候选，并非全部依次执行
  │    │    │    │  ↳ 复用节点 #28 BasicSearcher::search_impl（本树前文已展开）
  │    │    │    │  ↳ 复用节点 #30 BasicSearcher::search_impl（本树前文已展开）
  │    │    │    │  ↳ 复用节点 #31 BasicSearcher::search_impl（本树前文已展开）
  │    │    ├─ top_candidates->Empty  [L137] while_statement@137 (not top_candidates->Empty())
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ top_candidates->Top  [L138] while_statement@137 (not top_candidates->Empty())
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ heap->Push  [L139] while_statement@137 (not top_candidates->Empty())
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ top_candidates->Pop  [L140] while_statement@137 (not top_candidates->Empty())
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ heap->Size  [L142] while_statement@142 (heap->Size() > result_limit)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ heap->Pop  [L143] while_statement@142 (heap->Size() > result_limit)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ flat_searcher_->Search  [L64] if_statement@53 (graph_fresh && bucket_size >= graph_build_threshold_) [else 分支]
  │    │  ↳ 复用节点 #13 FlatBucketSearcher::Search（本树前文已展开）
  ├─ this->thread_pool_->GeneralEnqueue  [L275] if_statement@273 (this->thread_pool_ != nullptr and search_thread_count > 1) → for_statement@274 thread_id < search_thread_count
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ futures.emplace_back  [L276] if_statement@273 (this->thread_pool_ != nullptr and search_thread_count > 1) → for_statement@274 thread_id < search_thread_count
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ std::move  [L276] if_statement@273 (this->thread_pool_ != nullptr and search_thread_count > 1) → for_statement@274 thread_id < search_thread_count
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ search_func  [L279] if_statement@273 (this->thread_pool_ != nullptr and search_thread_count > 1) [else 分支]
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ future.get  [L285] if_statement@283 (this->thread_pool_ != nullptr and search_thread_count > 1) → for_range_loop@284
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ DistanceHeap::MakeInstanceBySize<true, true>  [L287] if_statement@283 (this->thread_pool_ != nullptr and search_thread_count > 1)
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ heap->Size  [L289] if_statement@283 (this->thread_pool_ != nullptr and search_thread_count > 1) → for_range_loop@288
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ heap->GetData  [L290] if_statement@283 (this->thread_pool_ != nullptr and search_thread_count > 1) → for_range_loop@288
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ search_result->Size  [L293] if_statement@283 (this->thread_pool_ != nullptr and search_thread_count > 1) → for_range_loop@288 → for_statement@291 i < size → if_statement@292 (reasoning_ctx != nullptr and search_result->Size() >= static_cast<uint64_t>(topk) and data[i].first < search_result->Top().first)
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ search_result->Top  [L294] if_statement@283 (this->thread_pool_ != nullptr and search_thread_count > 1) → for_range_loop@288 → for_statement@291 i < size → if_statement@292 (reasoning_ctx != nullptr and search_result->Size() >= static_cast<uint64_t>(topk) and data[i].first < search_result->Top().first)
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ reasoning_ctx->RecordEviction  [L295] if_statement@283 (this->thread_pool_ != nullptr and search_thread_count > 1) → for_range_loop@288 → for_statement@291 i < size → if_statement@292 (reasoning_ctx != nullptr and search_result->Size() >= static_cast<uint64_t>(topk) and data[i].first < search_result->Top().first)
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ search_result->Top  [L295] if_statement@283 (this->thread_pool_ != nullptr and search_thread_count > 1) → for_range_loop@288 → for_statement@291 i < size → if_statement@292 (reasoning_ctx != nullptr and search_result->Size() >= static_cast<uint64_t>(topk) and data[i].first < search_result->Top().first)
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ search_result->Push  [L298] if_statement@283 (this->thread_pool_ != nullptr and search_thread_count > 1) → for_range_loop@288 → for_statement@291 i < size
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ search_result->Empty  [L306] if_statement@304 (buckets_per_data_ > 1) → while_statement@306 (!search_result->Empty())
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ search_result->Top  [L307] if_statement@304 (buckets_per_data_ > 1) → while_statement@306 (!search_result->Empty())
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ id_to_min_dist.find  [L310] if_statement@304 (buckets_per_data_ > 1) → while_statement@306 (!search_result->Empty()) → if_statement@310 (id_to_min_dist.find(origin_id) == id_to_min_dist.end() || dist_val < id_to_min_dist[origin_id])
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ id_to_min_dist.end  [L310] if_statement@304 (buckets_per_data_ > 1) → while_statement@306 (!search_result->Empty()) → if_statement@310 (id_to_min_dist.find(origin_id) == id_to_min_dist.end() || dist_val < id_to_min_dist[origin_id])
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ search_result->Pop  [L314] if_statement@304 (buckets_per_data_ > 1) → while_statement@306 (!search_result->Empty())
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ std::numeric_limits<float>::max  [L317] if_statement@304 (buckets_per_data_ > 1)
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ search_result->Push  [L320] if_statement@304 (buckets_per_data_ > 1) → for_range_loop@318 → if_statement@319 (dist_val < cur_heap_top2)
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ search_result->Size  [L322] if_statement@304 (buckets_per_data_ > 1) → for_range_loop@318 → if_statement@322 (search_result->Size() > origin_topk)
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ search_result->Pop  [L323] if_statement@304 (buckets_per_data_ > 1) → for_range_loop@318 → if_statement@322 (search_result->Size() > origin_topk)
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ search_result->Empty  [L325] if_statement@304 (buckets_per_data_ > 1) → for_range_loop@318 → if_statement@325 (not search_result->Empty() and search_result->Size() == origin_topk)
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ search_result->Size  [L325] if_statement@304 (buckets_per_data_ > 1) → for_range_loop@318 → if_statement@325 (not search_result->Empty() and search_result->Size() == origin_topk)
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ search_result->Top  [L326] if_statement@304 (buckets_per_data_ > 1) → for_range_loop@318 → if_statement@325 (not search_result->Empty() and search_result->Size() == origin_topk)
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
```

## IVFNearestPartition::Train

[完整函数与全部调用点](function_reference/ivf_nearest_partition.md#L91)

```text
#1 IVFNearestPartition::Train [src/algorithm/ivf/ivf_nearest_partition.cpp:91]
  ├─ Dataset::Make  [L94] 函数本体；短路求值/提前返回见源码
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ std::iota  [L97] 函数本体；短路求值/提前返回见源码
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ ids.begin  [L97] 函数本体；短路求值/提前返回见源码
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ ids.end  [L97] 函数本体；短路求值/提前返回见源码
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ centroids->Ids(ids.data()) ->Dim(dim) ->Float32Vectors(data.data()) ->NumElements(this->bucket_count_) ->Owner  [L98] 函数本体；短路求值/提前返回见源码
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ centroids->Ids(ids.data()) ->Dim(dim) ->Float32Vectors(data.data()) ->NumElements  [L98] 函数本体；短路求值/提前返回见源码
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ centroids->Ids(ids.data()) ->Dim(dim) ->Float32Vectors  [L98] 函数本体；短路求值/提前返回见源码
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ centroids->Ids(ids.data()) ->Dim  [L98] 函数本体；短路求值/提前返回见源码
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ centroids->Ids  [L98] 函数本体；短路求值/提前返回见源码
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ ids.data  [L98] 函数本体；短路求值/提前返回见源码
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ data.data  [L100] 函数本体；短路求值/提前返回见源码
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ cls.Run  [L108] if_statement@104 (ivf_partition_strategy_param_->partition_train_type == IVFNearestPartitionTrainerType::KMeansTrainer)
  │  #2 KMeansCluster::Run [src/impl/cluster/kmeans_cluster.cpp:48]
  │    ├─ VsagException  [L60] if_statement@59 (k == 0)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ VsagException  [L63] if_statement@62 (count == 0)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ VsagException  [L66] if_statement@65 (datas == nullptr)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ VsagException  [L69] if_statement@68 (k > count)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ allocator_->Deallocate  [L73] if_statement@72 (k_centroids_ != nullptr)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ allocator_->Allocate  [L77] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ random_seed.has_value  [L80] conditional_expression@80 random_seed.has_value()
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ rd  [L80] conditional_expression@80 random_seed.has_value()
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ select_initial_centroids_kmeans_plus_plus  [L83] if_statement@82 (init_method == KMeansInitMethod::KMEANS_PLUS_PLUS)
  │    │  #3 KMeansCluster::select_initial_centroids_kmeans_plus_plus [src/impl/cluster/kmeans_cluster.cpp:305]
  │    │    ├─ first_dis  [L311] 函数本体；短路求值/提前返回见源码
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ FP32ComputeL2Sqr  [L323] for_statement@318 c < k → for_statement@322 i < count
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ std::min  [L324] for_statement@318 c < k → for_statement@322 i < count
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ dis  [L334] for_statement@318 c < k → if_statement@332 (total_weight <= 0.0)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ prob_dis  [L342] for_statement@318 c < k
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ select_initial_centroids_random  [L85] if_statement@82 (init_method == KMeansInitMethod::KMEANS_PLUS_PLUS) [else 分支]
  │    │  #4 KMeansCluster::select_initial_centroids_random [src/impl/cluster/kmeans_cluster.cpp:290]
  │    │    ├─ dis  [L298] for_statement@297 i < k
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ std::numeric_limits<double>::max  [L88] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ std::numeric_limits<double>::max  [L89] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ logger::trace  [L93] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ logger::trace  [L95] if_statement@94 (k < THRESHOLD_FOR_HGRAPH)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ logger::trace  [L97] if_statement@94 (k < THRESHOLD_FOR_HGRAPH) [else 分支]
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ NearestCentroidAssign  [L102] for_statement@100 it < iter → if_statement@101 (k < THRESHOLD_FOR_HGRAPH)
  │    │  #5 NearestCentroidAssign [src/impl/cluster/nearest_centroid_assign.cpp:39]
  │    │    ├─ std::numeric_limits<int32_t>::max  [L52] if_statement@50 (centroids == nullptr || queries == nullptr || labels == nullptr || allocator == nullptr || thread_pool == nullptr || centroid_count == 0 || query_count == 0 || dim == 0 || centroid_count > static_cast<uint64_t>(std::numeric_limits<int32_t>::max()) || dim > static_cast<uint64_t>(std::numeric_limits<int32_t>::max()))
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ std::numeric_limits<int32_t>::max  [L53] if_statement@50 (centroids == nullptr || queries == nullptr || labels == nullptr || allocator == nullptr || thread_pool == nullptr || centroid_count == 0 || query_count == 0 || dim == 0 || centroid_count > static_cast<uint64_t>(std::numeric_limits<int32_t>::max()) || dim > static_cast<uint64_t>(std::numeric_limits<int32_t>::max()))
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ VsagException  [L54] if_statement@50 (centroids == nullptr || queries == nullptr || labels == nullptr || allocator == nullptr || thread_pool == nullptr || centroid_count == 0 || query_count == 0 || dim == 0 || centroid_count > static_cast<uint64_t>(std::numeric_limits<int32_t>::max()) || dim > static_cast<uint64_t>(std::numeric_limits<int32_t>::max()))
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ future.wait  [L63] lambda@61（定义体，执行时间取决于调用/调度） → for_range_loop@62
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ futures.clear  [L65] lambda@61（定义体，执行时间取决于调用/调度）
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ std::min  [L68] 函数本体；短路求值/提前返回见源码
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ FP32ComputeIP  [L76] lambda@74（定义体，执行时间取决于调用/调度） → for_statement@75 i < end
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ futures.emplace_back  [L80] for_statement@79 i < centroid_count
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ thread_pool_ref->GeneralEnqueue  [L81] for_statement@79 i < centroid_count
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ std::min  [L81] for_statement@79 i < centroid_count
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ wait_futures_and_clear  [L83] 函数本体；短路求值/提前返回见源码
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ std::min  [L86] for_statement@85 i < query_count
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ SimdStatus::SupportAMXBF16  [L108] for_statement@85 i < query_count → if_statement@107 (dim >= amx_bf16_min_dim && centroid_count >= amx_bf16_min_m && cur_query_count >= amx_bf16_min_n && SimdStatus::SupportAMXBF16())
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ amx::SgemmBF16IPColMajorOut  [L109] for_statement@85 i < query_count → if_statement@107 (dim >= amx_bf16_min_dim && centroid_count >= amx_bf16_min_m && cur_query_count >= amx_bf16_min_n && SimdStatus::SupportAMXBF16())
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ BlasFunction::Sgemm  [L119] for_statement@85 i < query_count → if_statement@118 (!used_amx)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ omp_set_num_threads  [L137] for_statement@85 i < query_count → lambda@136（定义体，执行时间取决于调用/调度）
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ BlasFunction::Saxpy  [L140] for_statement@85 i < query_count → lambda@136（定义体，执行时间取决于调用/调度） → for_statement@139 j < end
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ std::min_element  [L146] for_statement@85 i < query_count → lambda@136（定义体，执行时间取决于调用/调度） → for_statement@139 j < end
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ FP32ComputeIP  [L148] for_statement@85 i < query_count → lambda@136（定义体，执行时间取决于调用/调度） → for_statement@139 j < end
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ std::distance  [L150] for_statement@85 i < query_count → lambda@136（定义体，执行时间取决于调用/调度） → for_statement@139 j < end
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ futures.emplace_back  [L162] for_statement@85 i < query_count → for_statement@161 j < cur_query_count
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ thread_pool_ref->GeneralEnqueue  [L162] for_statement@85 i < query_count → for_statement@161 j < cur_query_count
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ std::min  [L163] for_statement@85 i < query_count → for_statement@161 j < cur_query_count
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ wait_futures_and_clear  [L165] for_statement@85 i < query_count
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ labels.data  [L109] for_statement@100 it < iter → if_statement@101 (k < THRESHOLD_FOR_HGRAPH)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ this->find_nearest_one_with_hgraph  [L111] for_statement@100 it < iter → if_statement@101 (k < THRESHOLD_FOR_HGRAPH) [else 分支]
  │    │  #6 KMeansCluster::find_nearest_one_with_hgraph [src/impl/cluster/kmeans_cluster.cpp:230]
  │    │    ├─ VsagException  [L236] if_statement@235 (k_centroids_ == nullptr)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ std::make_shared<SafeAllocator>  [L243] 函数本体；短路求值/提前返回见源码
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ std::max  [L246] 函数本体；短路求值/提前返回见源码
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ InnerIndexInterface::FastCreateIndex  [L249] 函数本体；短路求值/提前返回见源码
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ fmt::format  [L249] 函数本体；短路求值/提前返回见源码
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ Dataset::Make  [L250] 函数本体；短路求值/提前返回见源码
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ std::iota  [L252] 函数本体；短路求值/提前返回见源码
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ ids.begin  [L252] 函数本体；短路求值/提前返回见源码
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ ids.end  [L252] 函数本体；短路求值/提前返回见源码
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ base->Dim(dim_) ->NumElements(static_cast<int64_t>(k)) ->Float32Vectors(this->k_centroids_) ->Ids(ids.data()) ->Owner  [L253] 函数本体；短路求值/提前返回见源码
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ base->Dim(dim_) ->NumElements(static_cast<int64_t>(k)) ->Float32Vectors(this->k_centroids_) ->Ids  [L253] 函数本体；短路求值/提前返回见源码
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ base->Dim(dim_) ->NumElements(static_cast<int64_t>(k)) ->Float32Vectors  [L253] 函数本体；短路求值/提前返回见源码
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ base->Dim(dim_) ->NumElements  [L253] 函数本体；短路求值/提前返回见源码
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ base->Dim  [L253] 函数本体；短路求值/提前返回见源码
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ ids.data  [L256] 函数本体；短路求值/提前返回见源码
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ hgraph->Build  [L258] 函数本体；短路求值/提前返回见源码
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ hgraph->SetImmutable  [L259] 函数本体；短路求值/提前返回见源码
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ Dataset::Make  [L265] lambda@262（定义体，执行时间取决于调用/调度） → for_statement@264 j < end
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ q->Owner(false) ->Float32Vectors(query + j * this->dim_) ->NumElements(1) ->Dim  [L266] lambda@262（定义体，执行时间取决于调用/调度） → for_statement@264 j < end
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ q->Owner(false) ->Float32Vectors(query + j * this->dim_) ->NumElements  [L266] lambda@262（定义体，执行时间取决于调用/调度） → for_statement@264 j < end
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ q->Owner(false) ->Float32Vectors  [L266] lambda@262（定义体，执行时间取决于调用/调度） → for_statement@264 j < end
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ q->Owner  [L266] lambda@262（定义体，执行时间取决于调用/调度） → for_statement@264 j < end
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ hgraph->KnnSearch  [L270] lambda@262（定义体，执行时间取决于调用/调度） → for_statement@264 j < end
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ ret->GetIds  [L271] lambda@262（定义体，执行时间取决于调用/调度） → for_statement@264 j < end
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ ret->GetDistances  [L272] lambda@262（定义体，执行时间取决于调用/调度） → for_statement@264 j < end
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ futures.emplace_back  [L281] for_statement@280 i < query_count
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ thread_pool_->GeneralEnqueue  [L282] for_statement@280 i < query_count
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ std::min  [L282] for_statement@280 i < query_count
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ future.wait  [L285] for_range_loop@284
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ block_counts.resize  [L122] for_statement@100 it < iter → if_statement@121 (deterministic_reduction)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ block_centroids.resize  [L123] for_statement@100 it < iter → if_statement@121 (deterministic_reduction)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ omp_set_num_threads  [L128] for_statement@100 it < iter → lambda@127（定义体，执行时间取决于调用/调度）
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ BlasFunction::Saxpy  [L136] for_statement@100 it < iter → lambda@127（定义体，执行时间取决于调用/调度） → for_statement@132 i < end → if_statement@134 (label >= 0 && label < static_cast<int32_t>(k))
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ local_centroids.data  [L141] for_statement@100 it < iter → lambda@127（定义体，执行时间取决于调用/调度） → for_statement@132 i < end → if_statement@134 (label >= 0 && label < static_cast<int32_t>(k))
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ std::copy  [L147] for_statement@100 it < iter → lambda@127（定义体，执行时间取决于调用/调度） → if_statement@146 (deterministic_reduction)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ local_counts.begin  [L148] for_statement@100 it < iter → lambda@127（定义体，执行时间取决于调用/调度） → if_statement@146 (deterministic_reduction)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ local_counts.end  [L148] for_statement@100 it < iter → lambda@127（定义体，执行时间取决于调用/调度） → if_statement@146 (deterministic_reduction)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ block_counts.data  [L148] for_statement@100 it < iter → lambda@127（定义体，执行时间取决于调用/调度） → if_statement@146 (deterministic_reduction)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ std::copy  [L149] for_statement@100 it < iter → lambda@127（定义体，执行时间取决于调用/调度） → if_statement@146 (deterministic_reduction)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ local_centroids.begin  [L149] for_statement@100 it < iter → lambda@127（定义体，执行时间取决于调用/调度） → if_statement@146 (deterministic_reduction)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ local_centroids.end  [L150] for_statement@100 it < iter → lambda@127（定义体，执行时间取决于调用/调度） → if_statement@146 (deterministic_reduction)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ block_centroids.data  [L151] for_statement@100 it < iter → lambda@127（定义体，执行时间取决于调用/调度） → if_statement@146 (deterministic_reduction)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ BlasFunction::Saxpy  [L157] for_statement@100 it < iter → lambda@127（定义体，执行时间取决于调用/调度） → if_statement@146 (deterministic_reduction) [else 分支] → for_statement@154 j < k → if_statement@155 (local_counts[j] > 0)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ local_centroids.data  [L160] for_statement@100 it < iter → lambda@127（定义体，执行时间取决于调用/调度） → if_statement@146 (deterministic_reduction) [else 分支] → for_statement@154 j < k → if_statement@155 (local_counts[j] > 0)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ new_centroids.data  [L162] for_statement@100 it < iter → lambda@127（定义体，执行时间取决于调用/调度） → if_statement@146 (deterministic_reduction) [else 分支] → for_statement@154 j < k → if_statement@155 (local_counts[j] > 0)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ futures.emplace_back  [L169] for_statement@100 it < iter → for_statement@168 i < count
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ thread_pool_->GeneralEnqueue  [L169] for_statement@100 it < iter → for_statement@168 i < count
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ std::min  [L170] for_statement@100 it < iter → for_statement@168 i < count
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ future.wait  [L173] for_statement@100 it < iter → for_range_loop@172
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ futures.clear  [L175] for_statement@100 it < iter
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ BlasFunction::Saxpy  [L182] for_statement@100 it < iter → if_statement@176 (deterministic_reduction) → for_statement@177 block_id < block_count → for_statement@178 j < k → if_statement@180 (block_counts[count_offset] > 0)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ block_centroids.data  [L184] for_statement@100 it < iter → if_statement@176 (deterministic_reduction) → for_statement@177 block_id < block_count → for_statement@178 j < k → if_statement@180 (block_counts[count_offset] > 0)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ new_centroids.data  [L187] for_statement@100 it < iter → if_statement@176 (deterministic_reduction) → for_statement@177 block_id < block_count → for_statement@178 j < k → if_statement@180 (block_counts[count_offset] > 0)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ BlasFunction::Sscal  [L197] for_statement@100 it < iter → for_statement@195 j < k → if_statement@196 (counts[j] > 0)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ new_centroids.data  [L199] for_statement@100 it < iter → for_statement@195 j < k → if_statement@196 (counts[j] > 0)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ std::copy  [L201] for_statement@100 it < iter → for_statement@195 j < k → if_statement@196 (counts[j] > 0)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ new_centroids.data  [L201] for_statement@100 it < iter → for_statement@195 j < k → if_statement@196 (counts[j] > 0)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ new_centroids.data  [L202] for_statement@100 it < iter → for_statement@195 j < k → if_statement@196 (counts[j] > 0)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ dis  [L205] for_statement@100 it < iter → for_statement@195 j < k → if_statement@196 (counts[j] > 0) [else 分支]
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ logger::trace  [L212] for_statement@100 it < iter
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ get_current_time  [L213] for_statement@100 it < iter
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ std::fabs  [L218] for_statement@100 it < iter → if_statement@217 (it > 0 && use_mse_for_convergence && std::fabs(last_err - total_err) / static_cast<double>(count) < threshold)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ dataset->GetFloat32Vectors  [L109] if_statement@104 (ivf_partition_strategy_param_->partition_train_type == IVFNearestPartitionTrainerType::KMeansTrainer)
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ dataset->GetNumElements  [L110] if_statement@104 (ivf_partition_strategy_param_->partition_train_type == IVFNearestPartitionTrainerType::KMeansTrainer)
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ memcpy  [L112] if_statement@104 (ivf_partition_strategy_param_->partition_train_type == IVFNearestPartitionTrainerType::KMeansTrainer)
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ data.data  [L112] if_statement@104 (ivf_partition_strategy_param_->partition_train_type == IVFNearestPartitionTrainerType::KMeansTrainer)
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ select_k_numbers  [L115] if_statement@104 (ivf_partition_strategy_param_->partition_train_type == IVFNearestPartitionTrainerType::KMeansTrainer) [else 分支] → if_statement@113 (ivf_partition_strategy_param_->partition_train_type == IVFNearestPartitionTrainerType::RandomTrainer)
  │  #7 select_k_numbers [src/utils/util_functions.cpp:43]
  │    ├─ VsagException  [L46] if_statement@45 (k > n || k <= 0)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ std::iota  [L50] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ numbers.begin  [L50] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ numbers.end  [L50] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ std::swap  [L56] for_statement@54 i < k
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ dist  [L56] for_statement@54 i < k
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ numbers.resize  [L58] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ dataset->GetNumElements  [L115] if_statement@104 (ivf_partition_strategy_param_->partition_train_type == IVFNearestPartitionTrainerType::KMeansTrainer) [else 分支] → if_statement@113 (ivf_partition_strategy_param_->partition_train_type == IVFNearestPartitionTrainerType::RandomTrainer)
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ memcpy  [L117] if_statement@104 (ivf_partition_strategy_param_->partition_train_type == IVFNearestPartitionTrainerType::KMeansTrainer) [else 分支] → if_statement@113 (ivf_partition_strategy_param_->partition_train_type == IVFNearestPartitionTrainerType::RandomTrainer) → for_statement@116 i < bucket_count_
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ data.data  [L117] if_statement@104 (ivf_partition_strategy_param_->partition_train_type == IVFNearestPartitionTrainerType::KMeansTrainer) [else 分支] → if_statement@113 (ivf_partition_strategy_param_->partition_train_type == IVFNearestPartitionTrainerType::RandomTrainer) → for_statement@116 i < bucket_count_
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ dataset->GetFloat32Vectors  [L118] if_statement@104 (ivf_partition_strategy_param_->partition_train_type == IVFNearestPartitionTrainerType::KMeansTrainer) [else 分支] → if_statement@113 (ivf_partition_strategy_param_->partition_train_type == IVFNearestPartitionTrainerType::RandomTrainer) → for_statement@116 i < bucket_count_
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ Normalize  [L124] if_statement@122 (metric_type_ == MetricType::METRIC_TYPE_COSINE) → for_statement@123 i < bucket_count_
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ data.data  [L124] if_statement@122 (metric_type_ == MetricType::METRIC_TYPE_COSINE) → for_statement@123 i < bucket_count_
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ data.data  [L124] if_statement@122 (metric_type_ == MetricType::METRIC_TYPE_COSINE) → for_statement@123 i < bucket_count_
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ this->route_index_ptr_->Build  [L129] if_statement@128 (this->use_route_graph_)
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ failed_ids.empty  [L130] if_statement@128 (this->use_route_graph_) → if_statement@130 (not failed_ids.empty())
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ VsagException  [L131] if_statement@128 (this->use_route_graph_) → if_statement@130 (not failed_ids.empty())
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ this->centroids_.resize  [L137] if_statement@128 (this->use_route_graph_) [else 分支]
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ memcpy  [L138] if_statement@128 (this->use_route_graph_) [else 分支]
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ this->centroids_.data  [L139] if_statement@128 (this->use_route_graph_) [else 分支]
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ data.data  [L139] if_statement@128 (this->use_route_graph_) [else 分支]
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ this->norms_.resize  [L140] if_statement@128 (this->use_route_graph_) [else 分支]
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ FP32ComputeIP  [L143] if_statement@128 (this->use_route_graph_) [else 分支] → if_statement@141 (metric_type_ == MetricType::METRIC_TYPE_L2SQR) → for_statement@142 i < bucket_count_
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ this->centroids_.data  [L143] if_statement@128 (this->use_route_graph_) [else 分支] → if_statement@141 (metric_type_ == MetricType::METRIC_TYPE_L2SQR) → for_statement@142 i < bucket_count_
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ this->centroids_.data  [L144] if_statement@128 (this->use_route_graph_) [else 分支] → if_statement@141 (metric_type_ == MetricType::METRIC_TYPE_L2SQR) → for_statement@142 i < bucket_count_
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ std::fill  [L151] if_statement@128 (this->use_route_graph_) [else 分支] → if_statement@141 (metric_type_ == MetricType::METRIC_TYPE_L2SQR) [else 分支]
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ this->norms_.begin  [L151] if_statement@128 (this->use_route_graph_) [else 分支] → if_statement@141 (metric_type_ == MetricType::METRIC_TYPE_L2SQR) [else 分支]
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ this->norms_.end  [L151] if_statement@128 (this->use_route_graph_) [else 分支] → if_statement@141 (metric_type_ == MetricType::METRIC_TYPE_L2SQR) [else 分支]
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
```

## IVFNearestPartition::ClassifyDatas

[完整函数与全部调用点](function_reference/ivf_nearest_partition.md#L157)

```text
#1 IVFNearestPartition::ClassifyDatas [src/algorithm/ivf/ivf_nearest_partition.cpp:157]
  ├─ this->classify_datas_by_scan  [L163] if_statement@162 (not this->use_route_graph_)
  │  #2 IVFNearestPartition::classify_datas_by_scan [src/algorithm/ivf/ivf_nearest_partition.cpp:313]
  │    ├─ std::min<BucketIdType>  [L325] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ norm_vectors.resize  [L333] if_statement@332 (metric_type_ == MetricType::METRIC_TYPE_COSINE)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ Normalize  [L335] if_statement@332 (metric_type_ == MetricType::METRIC_TYPE_COSINE) → for_statement@334 i < count
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ norm_vectors.data  [L335] if_statement@332 (metric_type_ == MetricType::METRIC_TYPE_COSINE) → for_statement@334 i < count
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ norm_vectors.data  [L337] if_statement@332 (metric_type_ == MetricType::METRIC_TYPE_COSINE)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ compute_centroid_dots  [L342] 函数本体；短路求值/提前返回见源码
  │    │  #3 compute_centroid_dots [src/algorithm/ivf/ivf_nearest_partition.cpp:51]
  │    │    ├─ BlasFunction::Sgemm  [L53] 函数本体；短路求值/提前返回见源码
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ this->centroids_.data  [L343] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ dots.data  [L343] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ heap_storage.reserve  [L347] lambda@345（定义体，执行时间取决于调用/调度）
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ std::move  [L348] lambda@345（定义体，执行时间取决于调用/调度）
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ dots.data  [L349] lambda@345（定义体，执行时间取决于调用/调度）
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ heap.size  [L353] lambda@345（定义体，执行时间取决于调用/调度） → for_statement@350 b < bucket_count_ → if_statement@353 (heap.size() < k || candidate < heap.top())
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ heap.top  [L353] lambda@345（定义体，执行时间取决于调用/调度） → for_statement@350 b < bucket_count_ → if_statement@353 (heap.size() < k || candidate < heap.top())
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ heap.push  [L354] lambda@345（定义体，执行时间取决于调用/调度） → for_statement@350 b < bucket_count_ → if_statement@353 (heap.size() < k || candidate < heap.top())
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ heap.size  [L356] lambda@345（定义体，执行时间取决于调用/调度） → for_statement@350 b < bucket_count_ → if_statement@356 (heap.size() > k)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ heap.pop  [L357] lambda@345（定义体，执行时间取决于调用/调度） → for_statement@350 b < bucket_count_ → if_statement@356 (heap.size() > k)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ heap.top  [L361] lambda@345（定义体，执行时间取决于调用/调度） → for_statement@360 j > 0
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ heap.pop  [L362] lambda@345（定义体，执行时间取决于调用/调度） → for_statement@360 j > 0
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ task  [L367] if_statement@365 (thread_pool_ == nullptr or count == 1) → for_statement@366 i < count
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ futures.push_back  [L372] if_statement@365 (thread_pool_ == nullptr or count == 1) [else 分支] → for_statement@371 i < count
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ thread_pool_->GeneralEnqueue  [L372] if_statement@365 (thread_pool_ == nullptr or count == 1) [else 分支] → for_statement@371 i < count
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ item.get  [L375] if_statement@365 (thread_pool_ == nullptr or count == 1) [else 分支] → for_range_loop@374
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ std::min<uint64_t>  [L383] if_statement@379 (ctx != nullptr and ctx->stats != nullptr)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ std::numeric_limits<uint32_t>::max  [L383] if_statement@379 (ctx != nullptr and ctx->stats != nullptr)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ ctx->stats->dist_cmp.fetch_add  [L384] if_statement@379 (ctx != nullptr and ctx->stats != nullptr)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ ctx->stats->AddDistance  [L385] if_statement@379 (ctx != nullptr and ctx->stats != nullptr)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ Dataset::Make  [L169] lambda@168（定义体，执行时间取决于调用/调度）
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ query->Dim(this->dim_) ->Float32Vectors(reinterpret_cast<const float*>(datas) + i * this->dim_) ->NumElements(1) ->Owner  [L170] lambda@168（定义体，执行时间取决于调用/调度）
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ query->Dim(this->dim_) ->Float32Vectors(reinterpret_cast<const float*>(datas) + i * this->dim_) ->NumElements  [L170] lambda@168（定义体，执行时间取决于调用/调度）
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ query->Dim(this->dim_) ->Float32Vectors  [L170] lambda@168（定义体，执行时间取决于调用/调度）
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ query->Dim  [L170] lambda@168（定义体，执行时间取决于调用/调度）
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ fmt::format  [L175] lambda@168（定义体，执行时间取决于调用/调度）
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ std::max<int64_t>  [L176] lambda@168（定义体，执行时间取决于调用/调度）
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ this->route_index_ptr_->KnnSearch  [L179] lambda@168（定义体，执行时间取决于调用/调度）
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ search_result->GetIds  [L180] lambda@168（定义体，执行时间取决于调用/调度）
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ search_result->GetDim  [L182] lambda@168（定义体，执行时间取决于调用/调度） → for_statement@182 j < search_result->GetDim()
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ search_result->GetStatistics  [L191] lambda@168（定义体，执行时间取决于调用/调度） → if_statement@186 (ctx != nullptr and ctx->stats != nullptr)
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ std::atoi  [L192] lambda@168（定义体，执行时间取决于调用/调度） → if_statement@186 (ctx != nullptr and ctx->stats != nullptr)
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ route_stats[0].c_str  [L192] lambda@168（定义体，执行时间取决于调用/调度） → if_statement@186 (ctx != nullptr and ctx->stats != nullptr)
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ route_stats.size  [L194] lambda@168（定义体，执行时间取决于调用/调度） → if_statement@186 (ctx != nullptr and ctx->stats != nullptr) → if_statement@194 (route_stats.size() > 1)
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ std::strtoull  [L195] lambda@168（定义体，执行时间取决于调用/调度） → if_statement@186 (ctx != nullptr and ctx->stats != nullptr) → if_statement@194 (route_stats.size() > 1)
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ route_stats[1].c_str  [L195] lambda@168（定义体，执行时间取决于调用/调度） → if_statement@186 (ctx != nullptr and ctx->stats != nullptr) → if_statement@194 (route_stats.size() > 1)
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ ctx->stats->AddDistance  [L201] lambda@168（定义体，执行时间取决于调用/调度） → if_statement@186 (ctx != nullptr and ctx->stats != nullptr)
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ task  [L208] if_statement@206 (thread_pool_ == nullptr or count == 1) → for_statement@207 i < count
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ futures.push_back  [L213] if_statement@206 (thread_pool_ == nullptr or count == 1) [else 分支] → for_statement@212 i < count
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ thread_pool_->GeneralEnqueue  [L213] if_statement@206 (thread_pool_ == nullptr or count == 1) [else 分支] → for_statement@212 i < count
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ item.get  [L216] if_statement@206 (thread_pool_ == nullptr or count == 1) [else 分支] → for_range_loop@215
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ ctx->stats->dist_cmp.fetch_add  [L221] if_statement@220 (ctx != nullptr and ctx->stats != nullptr)
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ std::move  [L224] 函数本体；短路求值/提前返回见源码
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
```

## FlatBucketSearcher::Search

[完整函数与全部调用点](function_reference/flat_bucket_searcher.md#L26)

```text
#1 FlatBucketSearcher::Search [src/algorithm/ivf/flat_bucket_searcher.cpp:26]
  ├─ bucket->GetBucketSize  [L37] 函数本体；短路求值/提前返回见源码
  │  #2 BucketDataCell::GetBucketSize [src/datacell/bucket_datacell.h:180]
  │    ├─ check_valid_bucket_id  [L182] 函数本体；短路求值/提前返回见源码
  │    │  #3 BucketDataCell::check_valid_bucket_id [src/datacell/bucket_datacell.h:244]
  │    │    ├─ VsagException  [L247] if_statement@246 (bucket_id >= this->bucket_count_ or bucket_id < 0)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ bucket->GetInnerIds  [L38] 函数本体；短路求值/提前返回见源码
  │  #4 BucketDataCell::GetInnerIds [src/datacell/bucket_datacell.h:120]
  │    ├─ check_valid_bucket_id  [L122] 函数本体；短路求值/提前返回见源码
  │    │  ↳ 复用节点 #3 BucketDataCell::check_valid_bucket_id（本树前文已展开）
  │    ├─ this->inner_ids_[bucket_id].data  [L123] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ dist.size  [L39] if_statement@39 (bucket_size > static_cast<int64_t>(dist.size()))
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ dist.resize  [L40] if_statement@39 (bucket_size > static_cast<int64_t>(dist.size()))
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ bucket->ScanBucketById  [L43] 函数本体；短路求值/提前返回见源码
  │  #5 BucketDataCell::ScanBucketById [src/datacell/bucket_datacell.h:63]
  │    ├─ computer.get  [L67] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ this->scan_bucket_by_id  [L68] 函数本体；短路求值/提前返回见源码
  │    │  #6 BucketDataCell<QuantTmpl, IOTmpl>::scan_bucket_by_id [src/datacell/bucket_datacell.h:522]
  │    │    ├─ VsagException  [L527] if_statement@526 (bucket_id >= this->bucket_count_ or bucket_id < 0)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ this->check_valid_bucket_id  [L532] 函数本体；短路求值/提前返回见源码
  │    │    │  ↳ 复用节点 #3 BucketDataCell::check_valid_bucket_id（本树前文已展开）
  │    │    ├─ std::min  [L535] while_statement@534 (data_count > 0)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ this->datas_[bucket_id].Acquire  [L537] while_statement@534 (data_count > 0)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ computer->ScanBatchDists  [L538] while_statement@534 (data_count > 0)
  │    │    │  ├─ 以下为分派/重载候选，并非全部依次执行
  │    │    │  #7 Computer::ScanBatchDists [src/quantization/computer.h:68]
  │    │    │    ├─ quantizer_->ScanBatchDists  [L70] 函数本体；短路求值/提前返回见源码
  │    │    │    │  #8 Quantizer::ScanBatchDists [src/quantization/quantizer.h:230]
  │    │    │    │    ├─ cast().ScanBatchDistImpl  [L235] 函数本体；短路求值/提前返回见源码
  │    │    │    │    │  ├─ 以下为分派/重载候选，并非全部依次执行
  │    │    │    │    │  #9 Quantizer::ScanBatchDistImpl [src/quantization/quantizer.h:290]
  │    │    │    │    │    ├─ cast().ComputeDistImpl  [L296] for_statement@295 i < count
  │    │    │    │    │    │  #10 FP32Quantizer<metric>::ComputeDistImpl [src/quantization/fp32_quantizer.cpp:164]
  │    │    │    │    │    │    ├─ FP32ComputeIP  [L169] if_statement@168 (metric == MetricType::METRIC_TYPE_IP)
  │    │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    │    ├─ FP32ComputeIP  [L173] if_statement@168 (metric == MetricType::METRIC_TYPE_IP) [else 分支] → if_statement@172 (metric == MetricType::METRIC_TYPE_COSINE)
  │    │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    │    ├─ FP32ComputeL2Sqr  [L182] if_statement@168 (metric == MetricType::METRIC_TYPE_IP) [else 分支] → if_statement@172 (metric == MetricType::METRIC_TYPE_COSINE) [else 分支] → if_statement@181 (metric == MetricType::METRIC_TYPE_L2SQR)
  │    │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ cast  [L296] for_statement@295 i < count
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │  #11 FP32Quantizer<metric>::ScanBatchDistImpl [src/quantization/fp32_quantizer.cpp:132]
  │    │    │    │    │    ├─ this->ComputeDistImpl  [L139] for_statement@138 i < count
  │    │    │    │    │    │  ↳ 复用节点 #10 FP32Quantizer<metric>::ComputeDistImpl（本树前文已展开）
  │    │    │    │    ├─ cast  [L235] 函数本体；短路求值/提前返回见源码
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │  #12 Computer<TransformQuantizer<QuantImpl, metric>>::ScanBatchDists [src/quantization/computer.h:142]
  │    │    │    ├─ quantizer_->ScanBatchDists  [L144] 函数本体；短路求值/提前返回见源码
  │    │    │    │  ↳ 复用节点 #8 Quantizer::ScanBatchDists（本树前文已展开）
  │    │    ├─ lease.Data  [L538] while_statement@534 (data_count > 0)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ this->quantizer_->GetDim  [L544] 函数本体；短路求值/提前返回见源码
  │    │    │  #13 Quantizer::GetDim [src/quantization/quantizer.h:340]
  │    │    ├─ strategy_->GetCentroid  [L546] if_statement@545 (use_residual_)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ FP32ComputeIP  [L548] if_statement@545 (use_residual_)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ computer->raw_query_.data  [L548] if_statement@545 (use_residual_)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ centroid.data  [L548] if_statement@545 (use_residual_)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ this->quantizer_->GetDim  [L548] if_statement@545 (use_residual_)
  │    │    │  ↳ 复用节点 #13 Quantizer::GetDim（本树前文已展开）
  │    │    ├─ FP32Sub  [L551] if_statement@545 (use_residual_) → if_statement@549 (metric_ == MetricType::METRIC_TYPE_L2SQR)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ residual_bias_[bucket_id].data  [L551] if_statement@545 (use_residual_) → if_statement@549 (metric_ == MetricType::METRIC_TYPE_L2SQR)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ std::numeric_limits<float>::max  [L560] for_statement@558 i < offset → if_statement@559 (this->inner_ids_[bucket_id][i] == EMPTY_INNER_ID)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ dist.data  [L43] 函数本体；短路求值/提前返回见源码
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ param.query_context->stats->AddDistance  [L46] if_statement@44 (param.query_context != nullptr and param.query_context->stats != nullptr and bucket_size > 0)
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ param.executors.size  [L53] if_statement@53 (thread_id >= 0 and param.executors.size() > static_cast<uint64_t>(thread_id))
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ param.executors[tid]->Clear  [L56] if_statement@53 (thread_id >= 0 and param.executors.size() > static_cast<uint64_t>(thread_id)) → if_statement@55 (param.executors[tid] != nullptr)
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ param.executors[tid]->Run  [L57] if_statement@53 (thread_id >= 0 and param.executors.size() > static_cast<uint64_t>(thread_id)) → if_statement@55 (param.executors[tid] != nullptr)
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ std::numeric_limits<float>::max  [L63] 函数本体；短路求值/提前返回见源码
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ heap->Empty  [L64] if_statement@64 (not heap->Empty() and heap->Size() == topk_u)
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ heap->Size  [L64] if_statement@64 (not heap->Empty() and heap->Size() == topk_u)
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ heap->Top  [L65] if_statement@64 (not heap->Empty() and heap->Size() == topk_u)
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ std::numeric_limits<InnerIdType>::max  [L70] if_statement@68 (param.search_mode == KNN_SEARCH) → for_statement@69 j < bucket_size → if_statement@70 (ids[j] == std::numeric_limits<InnerIdType>::max())
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ reasoning_ctx->RecordVisit  [L75] if_statement@68 (param.search_mode == KNN_SEARCH) → for_statement@69 j < bucket_size → if_statement@74 (reasoning_ctx != nullptr)
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ param.distance_threshold.has_value  [L77] if_statement@68 (param.search_mode == KNN_SEARCH) → for_statement@69 j < bucket_size → if_statement@77 (param.distance_threshold.has_value() and (not std::isfinite(dist[j]) or (not param.enable_reorder and dist[j] > param.distance_threshold.value())))
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ std::isfinite  [L78] if_statement@68 (param.search_mode == KNN_SEARCH) → for_statement@69 j < bucket_size → if_statement@77 (param.distance_threshold.has_value() and (not std::isfinite(dist[j]) or (not param.enable_reorder and dist[j] > param.distance_threshold.value())))
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ param.distance_threshold.value  [L79] if_statement@68 (param.search_mode == KNN_SEARCH) → for_statement@69 j < bucket_size → if_statement@77 (param.distance_threshold.has_value() and (not std::isfinite(dist[j]) or (not param.enable_reorder and dist[j] > param.distance_threshold.value())))
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ attr_ft->CheckValid  [L82] if_statement@68 (param.search_mode == KNN_SEARCH) → for_statement@69 j < bucket_size → if_statement@82 (attr_ft != nullptr and not attr_ft->CheckValid(j))
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ reasoning_ctx->RecordFilterReject  [L84] if_statement@68 (param.search_mode == KNN_SEARCH) → for_statement@69 j < bucket_size → if_statement@82 (attr_ft != nullptr and not attr_ft->CheckValid(j)) → if_statement@83 (reasoning_ctx != nullptr)
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ ft->CheckValid  [L88] if_statement@68 (param.search_mode == KNN_SEARCH) → for_statement@69 j < bucket_size → if_statement@88 (ft == nullptr or ft->CheckValid(origin_id))
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ heap->Size  [L89] if_statement@68 (param.search_mode == KNN_SEARCH) → for_statement@69 j < bucket_size → if_statement@88 (ft == nullptr or ft->CheckValid(origin_id)) → if_statement@89 (heap->Size() < topk_u or dist[j] < cur_heap_top)
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ heap->Push  [L90] if_statement@68 (param.search_mode == KNN_SEARCH) → for_statement@69 j < bucket_size → if_statement@88 (ft == nullptr or ft->CheckValid(origin_id)) → if_statement@89 (heap->Size() < topk_u or dist[j] < cur_heap_top)
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ heap->Size  [L92] if_statement@68 (param.search_mode == KNN_SEARCH) → for_statement@69 j < bucket_size → if_statement@88 (ft == nullptr or ft->CheckValid(origin_id)) → while_statement@92 (heap->Size() > topk_u)
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ reasoning_ctx->RecordEviction  [L94] if_statement@68 (param.search_mode == KNN_SEARCH) → for_statement@69 j < bucket_size → if_statement@88 (ft == nullptr or ft->CheckValid(origin_id)) → while_statement@92 (heap->Size() > topk_u) → if_statement@93 (reasoning_ctx != nullptr)
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ heap->Top  [L94] if_statement@68 (param.search_mode == KNN_SEARCH) → for_statement@69 j < bucket_size → if_statement@88 (ft == nullptr or ft->CheckValid(origin_id)) → while_statement@92 (heap->Size() > topk_u) → if_statement@93 (reasoning_ctx != nullptr)
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ heap->Pop  [L96] if_statement@68 (param.search_mode == KNN_SEARCH) → for_statement@69 j < bucket_size → if_statement@88 (ft == nullptr or ft->CheckValid(origin_id)) → while_statement@92 (heap->Size() > topk_u)
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ heap->Empty  [L98] if_statement@68 (param.search_mode == KNN_SEARCH) → for_statement@69 j < bucket_size → if_statement@88 (ft == nullptr or ft->CheckValid(origin_id)) → if_statement@98 (not heap->Empty() and heap->Size() == topk_u)
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ heap->Size  [L98] if_statement@68 (param.search_mode == KNN_SEARCH) → for_statement@69 j < bucket_size → if_statement@88 (ft == nullptr or ft->CheckValid(origin_id)) → if_statement@98 (not heap->Empty() and heap->Size() == topk_u)
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ heap->Top  [L99] if_statement@68 (param.search_mode == KNN_SEARCH) → for_statement@69 j < bucket_size → if_statement@88 (ft == nullptr or ft->CheckValid(origin_id)) → if_statement@98 (not heap->Empty() and heap->Size() == topk_u)
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ reasoning_ctx->RecordFilterReject  [L102] if_statement@68 (param.search_mode == KNN_SEARCH) → for_statement@69 j < bucket_size → if_statement@88 (ft == nullptr or ft->CheckValid(origin_id)) [else 分支] → if_statement@101 (reasoning_ctx != nullptr)
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ std::numeric_limits<InnerIdType>::max  [L107] if_statement@68 (param.search_mode == KNN_SEARCH) [else 分支] → for_statement@106 j < bucket_size → if_statement@107 (ids[j] == std::numeric_limits<InnerIdType>::max())
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ reasoning_ctx->RecordVisit  [L112] if_statement@68 (param.search_mode == KNN_SEARCH) [else 分支] → for_statement@106 j < bucket_size → if_statement@111 (reasoning_ctx != nullptr)
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ attr_ft->CheckValid  [L114] if_statement@68 (param.search_mode == KNN_SEARCH) [else 分支] → for_statement@106 j < bucket_size → if_statement@114 (attr_ft != nullptr and not attr_ft->CheckValid(j))
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ reasoning_ctx->RecordFilterReject  [L116] if_statement@68 (param.search_mode == KNN_SEARCH) [else 分支] → for_statement@106 j < bucket_size → if_statement@114 (attr_ft != nullptr and not attr_ft->CheckValid(j)) → if_statement@115 (reasoning_ctx != nullptr)
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ ft->CheckValid  [L120] if_statement@68 (param.search_mode == KNN_SEARCH) [else 分支] → for_statement@106 j < bucket_size → if_statement@120 (ft == nullptr or ft->CheckValid(origin_id))
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ heap->Push  [L122] if_statement@68 (param.search_mode == KNN_SEARCH) [else 分支] → for_statement@106 j < bucket_size → if_statement@120 (ft == nullptr or ft->CheckValid(origin_id)) → if_statement@121 (dist[j] <= param.radius + THRESHOLD_ERROR and dist[j] < cur_heap_top)
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ heap->Size  [L124] if_statement@68 (param.search_mode == KNN_SEARCH) [else 分支] → for_statement@106 j < bucket_size → if_statement@120 (ft == nullptr or ft->CheckValid(origin_id)) → while_statement@124 (heap->Size() > topk_u)
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ reasoning_ctx->RecordEviction  [L126] if_statement@68 (param.search_mode == KNN_SEARCH) [else 分支] → for_statement@106 j < bucket_size → if_statement@120 (ft == nullptr or ft->CheckValid(origin_id)) → while_statement@124 (heap->Size() > topk_u) → if_statement@125 (reasoning_ctx != nullptr)
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ heap->Top  [L126] if_statement@68 (param.search_mode == KNN_SEARCH) [else 分支] → for_statement@106 j < bucket_size → if_statement@120 (ft == nullptr or ft->CheckValid(origin_id)) → while_statement@124 (heap->Size() > topk_u) → if_statement@125 (reasoning_ctx != nullptr)
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ heap->Pop  [L128] if_statement@68 (param.search_mode == KNN_SEARCH) [else 分支] → for_statement@106 j < bucket_size → if_statement@120 (ft == nullptr or ft->CheckValid(origin_id)) → while_statement@124 (heap->Size() > topk_u)
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ heap->Empty  [L130] if_statement@68 (param.search_mode == KNN_SEARCH) [else 分支] → for_statement@106 j < bucket_size → if_statement@120 (ft == nullptr or ft->CheckValid(origin_id)) → if_statement@130 (not heap->Empty() and heap->Size() == topk_u)
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ heap->Size  [L130] if_statement@68 (param.search_mode == KNN_SEARCH) [else 分支] → for_statement@106 j < bucket_size → if_statement@120 (ft == nullptr or ft->CheckValid(origin_id)) → if_statement@130 (not heap->Empty() and heap->Size() == topk_u)
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ heap->Top  [L131] if_statement@68 (param.search_mode == KNN_SEARCH) [else 分支] → for_statement@106 j < bucket_size → if_statement@120 (ft == nullptr or ft->CheckValid(origin_id)) → if_statement@130 (not heap->Empty() and heap->Size() == topk_u)
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ reasoning_ctx->RecordFilterReject  [L134] if_statement@68 (param.search_mode == KNN_SEARCH) [else 分支] → for_statement@106 j < bucket_size → if_statement@120 (ft == nullptr or ft->CheckValid(origin_id)) [else 分支] → if_statement@133 (reasoning_ctx != nullptr)
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
```

## GraphBucketSearcher::Search

[完整函数与全部调用点](function_reference/graph_bucket_searcher.md#L36)

```text
#1 GraphBucketSearcher::Search [src/algorithm/ivf/graph_bucket_searcher.cpp:36]
  ├─ bucket->GetBucketSize  [L47] 函数本体；短路求值/提前返回见源码
  │  #2 BucketDataCell::GetBucketSize [src/datacell/bucket_datacell.h:180]
  │    ├─ check_valid_bucket_id  [L182] 函数本体；短路求值/提前返回见源码
  │    │  #3 BucketDataCell::check_valid_bucket_id [src/datacell/bucket_datacell.h:244]
  │    │    ├─ VsagException  [L247] if_statement@246 (bucket_id >= this->bucket_count_ or bucket_id < 0)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ bucket_graphs_.size  [L48] 函数本体；短路求值/提前返回见源码
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ bucket_graphs_[bucket_id]->TotalCount  [L51] 函数本体；短路求值/提前返回见源码
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ search_graph  [L54] if_statement@53 (graph_fresh && bucket_size >= graph_build_threshold_)
  │  #4 GraphBucketSearcher::search_graph [src/algorithm/ivf/graph_bucket_searcher.cpp:77]
  │    ├─ bucket->GetBucketSize  [L87] 函数本体；短路求值/提前返回见源码
  │    │  ↳ 复用节点 #2 BucketDataCell::GetBucketSize（本树前文已展开）
  │    ├─ bucket->GetInnerIds  [L92] 函数本体；短路求值/提前返回见源码
  │    │  #5 BucketDataCell::GetInnerIds [src/datacell/bucket_datacell.h:120]
  │    │    ├─ check_valid_bucket_id  [L122] 函数本体；短路求值/提前返回见源码
  │    │    │  ↳ 复用节点 #3 BucketDataCell::check_valid_bucket_id（本树前文已展开）
  │    │    ├─ this->inner_ids_[bucket_id].data  [L123] 函数本体；短路求值/提前返回见源码
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ std::numeric_limits<InnerIdType>::max  [L94] while_statement@94 (entry < bucket_size && ids[entry] == std::numeric_limits<InnerIdType>::max())
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ param.executors.empty  [L102] if_statement@102 (not param.executors.empty() && static_cast<uint64_t>(thread_id) < param.executors.size() && param.executors[thread_id] != nullptr)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ param.executors.size  [L102] if_statement@102 (not param.executors.empty() && static_cast<uint64_t>(thread_id) < param.executors.size() && param.executors[thread_id] != nullptr)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ param.executors[thread_id]->Clear  [L104] if_statement@102 (not param.executors.empty() && static_cast<uint64_t>(thread_id) < param.executors.size() && param.executors[thread_id] != nullptr)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ param.executors[thread_id]->Run  [L105] if_statement@102 (not param.executors.empty() && static_cast<uint64_t>(thread_id) < param.executors.size() && param.executors[thread_id] != nullptr)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ std::numeric_limits<uint64_t>::max  [L109] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ CHECK_ARGUMENT  [L111] if_statement@110 (search_param.search_mode == KNN_SEARCH)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ std::max  [L113] if_statement@110 (search_param.search_mode == KNN_SEARCH)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ std::min<uint64_t>  [L117] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ std::min<int64_t>  [L123] if_statement@119 (search_param.search_mode == RANGE_SEARCH) → conditional_expression@123 topk > 0
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ std::numeric_limits<int>::max  [L123] if_statement@119 (search_param.search_mode == RANGE_SEARCH) → conditional_expression@123 topk > 0
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ std::make_shared<VisitedList>  [L130] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ searcher.Search  [L135] 函数本体；短路求值/提前返回见源码
  │    │  ├─ 以下为分派/重载候选，并非全部依次执行
  │    │  #6 BasicSearcher::Search [src/impl/searcher/basic_searcher.cpp:76]
  │    │    ├─ this->search_impl<KNN_SEARCH>  [L86] if_statement@85 (inner_search_param.search_mode == KNN_SEARCH)
  │    │    │  ├─ 以下为分派/重载候选，并非全部依次执行
  │    │    │  #7 BasicSearcher::search_impl [src/impl/searcher/basic_searcher.cpp:174]
  │    │    │    ├─ select_query_allocator  [L181] 函数本体；短路求值/提前返回见源码
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ std::make_shared<StandardHeap<true, false>>  [L182] 函数本体；短路求值/提前返回见源码
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ std::make_shared<StandardHeap<true, false>>  [L183] 函数本体；短路求值/提前返回见源码
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ distance_provider.OriginalId  [L188] lambda@187（定义体，执行时间取决于调用/调度）
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ distance_provider.IsValid  [L189] lambda@187（定义体，执行时间取决于调用/调度）
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ inner_search_param.is_inner_id_allowed->CheckValid  [L191] lambda@187（定义体，执行时间取决于调用/调度）
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ attr_filter->CheckValid  [L192] lambda@187（定义体，执行时间取决于调用/调度）
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ distance_provider.QueryDistance  [L197] 函数本体；短路求值/提前返回见源码
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ reasoning->RecordVisit  [L201] if_statement@200 (reasoning != nullptr)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ distance_provider.OriginalId  [L201] if_statement@200 (reasoning != nullptr)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ check_func  [L203] if_statement@203 (check_func(ep))
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ is_result_distance_eligible<mode>  [L204] if_statement@203 (check_func(ep)) → if_statement@204 (is_result_distance_eligible<mode>(dist, inner_search_param))
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ top_candidates->Push  [L205] if_statement@203 (check_func(ep)) → if_statement@204 (is_result_distance_eligible<mode>(dist, inner_search_param))
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ reasoning->RecordFilterReject  [L208] if_statement@203 (check_func(ep)) [else 分支] → if_statement@207 (reasoning != nullptr)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ distance_provider.OriginalId  [L208] if_statement@203 (check_func(ep)) [else 分支] → if_statement@207 (reasoning != nullptr)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ top_candidates->Empty  [L211] if_statement@210 (mode == InnerSearchMode::RANGE_SEARCH) → if_statement@211 (dist > inner_search_param.radius + THRESHOLD_ERROR && not top_candidates->Empty())
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ top_candidates->Pop  [L212] if_statement@210 (mode == InnerSearchMode::RANGE_SEARCH) → if_statement@211 (dist > inner_search_param.radius + THRESHOLD_ERROR && not top_candidates->Empty())
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ candidate_set->Push  [L215] 函数本体；短路求值/提前返回见源码
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ traversal_priority  [L215] 函数本体；短路求值/提前返回见源码
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ vl->Set  [L216] 函数本体；短路求值/提前返回见源码
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ top_candidates->Empty  [L218] conditional_expression@218 top_candidates->Empty()
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ std::numeric_limits<float>::max  [L218] conditional_expression@218 top_candidates->Empty()
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ top_candidates->Top  [L218] conditional_expression@218 top_candidates->Empty()
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ graph->MaximumDegree  [L219] 函数本体；短路求值/提前返回见源码
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ graph->MaximumDegree  [L220] 函数本体；短路求值/提前返回见源码
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ graph->MaximumDegree  [L221] 函数本体；短路求值/提前返回见源码
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ candidate_set->Empty  [L222] while_statement@222 (not candidate_set->Empty())
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ candidate_set->Top  [L228] while_statement@222 (not candidate_set->Empty()) → if_statement@227 (mode == InnerSearchMode::KNN_SEARCH) → if_statement@228 (-candidate_set->Top().first > lower_bound && top_candidates->Size() >= ef)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ top_candidates->Size  [L228] while_statement@222 (not candidate_set->Empty()) → if_statement@227 (mode == InnerSearchMode::KNN_SEARCH) → if_statement@228 (-candidate_set->Top().first > lower_bound && top_candidates->Size() >= ef)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ candidate_set->Top  [L232] while_statement@222 (not candidate_set->Empty())
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ candidate_set->Pop  [L233] while_statement@222 (not candidate_set->Empty())
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ candidate_set->Empty  [L234] while_statement@222 (not candidate_set->Empty()) → if_statement@234 (not candidate_set->Empty())
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ graph->Prefetch  [L235] while_statement@222 (not candidate_set->Empty()) → if_statement@234 (not candidate_set->Empty())
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ candidate_set->Top  [L235] while_statement@222 (not candidate_set->Empty()) → if_statement@234 (not candidate_set->Empty())
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ visit  [L238] while_statement@222 (not candidate_set->Empty())
  │    │    │    │  #8 BasicSearcher::visit [src/impl/searcher/basic_searcher.cpp:43]
  │    │    │    │    ├─ graph->GetNeighbors  [L55] if_statement@53 (this->mutex_array_ != nullptr)
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ graph->GetNeighbors  [L57] if_statement@53 (this->mutex_array_ != nullptr) [else 分支]
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ neighbors.size  [L60] for_statement@60 i < neighbors.size()
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ neighbors.size  [L61] for_statement@60 i < neighbors.size() → if_statement@61 (i + prefetch_stride_visit_ < neighbors.size())
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ vl->Prefetch  [L62] for_statement@60 i < neighbors.size() → if_statement@61 (i + prefetch_stride_visit_ < neighbors.size())
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ vl->Get  [L64] for_statement@60 i < neighbors.size() → if_statement@64 (not vl->Get(neighbors[i]))
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ vl->Set  [L65] for_statement@60 i < neighbors.size() → if_statement@64 (not vl->Get(neighbors[i]))
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ skip_strategy->ShouldVisit  [L67] for_statement@60 i < neighbors.size() → if_statement@64 (not vl->Get(neighbors[i])) → if_statement@66 (not filter || count_no_visited == 0 || skip_strategy == nullptr || skip_strategy->ShouldVisit() || filter->CheckValid(neighbors[i]))
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ filter->CheckValid  [L67] for_statement@60 i < neighbors.size() → if_statement@64 (not vl->Get(neighbors[i])) → if_statement@66 (not filter || count_no_visited == 0 || skip_strategy == nullptr || skip_strategy->ShouldVisit() || filter->CheckValid(neighbors[i]))
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ distance_provider.BatchQueryDistance  [L239] while_statement@222 (not candidate_set->Empty())
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ line_dists.data  [L240] while_statement@222 (not candidate_set->Empty())
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ to_be_visited_id.data  [L240] while_statement@222 (not candidate_set->Empty())
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ distance_provider.IsValid  [L245] while_statement@222 (not candidate_set->Empty()) → for_statement@242 i < count_no_visited → if_statement@245 (not distance_provider.IsValid(id))
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ reasoning->RecordVisit  [L249] while_statement@222 (not candidate_set->Empty()) → for_statement@242 i < count_no_visited → if_statement@248 (reasoning != nullptr)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ distance_provider.OriginalId  [L249] while_statement@222 (not candidate_set->Empty()) → for_statement@242 i < count_no_visited → if_statement@248 (reasoning != nullptr)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ is_finite_distance  [L251] while_statement@222 (not candidate_set->Empty()) → for_statement@242 i < count_no_visited → if_statement@251 (not is_finite_distance(dist))
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ candidate_set->Push  [L252] while_statement@222 (not candidate_set->Empty()) → for_statement@242 i < count_no_visited → if_statement@251 (not is_finite_distance(dist))
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ traversal_priority  [L252] while_statement@222 (not candidate_set->Empty()) → for_statement@242 i < count_no_visited → if_statement@251 (not is_finite_distance(dist))
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ check_func  [L253] while_statement@222 (not candidate_set->Empty()) → for_statement@242 i < count_no_visited → if_statement@251 (not is_finite_distance(dist)) → if_statement@253 (check_func(id) and is_result_distance_eligible<mode>(dist, inner_search_param))
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ is_result_distance_eligible<mode>  [L254] while_statement@222 (not candidate_set->Empty()) → for_statement@242 i < count_no_visited → if_statement@251 (not is_finite_distance(dist)) → if_statement@253 (check_func(id) and is_result_distance_eligible<mode>(dist, inner_search_param))
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ top_candidates->Push  [L255] while_statement@222 (not candidate_set->Empty()) → for_statement@242 i < count_no_visited → if_statement@251 (not is_finite_distance(dist)) → if_statement@253 (check_func(id) and is_result_distance_eligible<mode>(dist, inner_search_param))
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ top_candidates->Size  [L257] while_statement@222 (not candidate_set->Empty()) → for_statement@242 i < count_no_visited → if_statement@251 (not is_finite_distance(dist)) → if_statement@253 (check_func(id) and is_result_distance_eligible<mode>(dist, inner_search_param)) → if_statement@256 (mode == InnerSearchMode::KNN_SEARCH) → if_statement@257 (top_candidates->Size() > ef)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ reasoning->RecordEviction  [L259] while_statement@222 (not candidate_set->Empty()) → for_statement@242 i < count_no_visited → if_statement@251 (not is_finite_distance(dist)) → if_statement@253 (check_func(id) and is_result_distance_eligible<mode>(dist, inner_search_param)) → if_statement@256 (mode == InnerSearchMode::KNN_SEARCH) → if_statement@257 (top_candidates->Size() > ef) → if_statement@258 (reasoning != nullptr)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ distance_provider.OriginalId  [L260] while_statement@222 (not candidate_set->Empty()) → for_statement@242 i < count_no_visited → if_statement@251 (not is_finite_distance(dist)) → if_statement@253 (check_func(id) and is_result_distance_eligible<mode>(dist, inner_search_param)) → if_statement@256 (mode == InnerSearchMode::KNN_SEARCH) → if_statement@257 (top_candidates->Size() > ef) → if_statement@258 (reasoning != nullptr)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ top_candidates->Top  [L260] while_statement@222 (not candidate_set->Empty()) → for_statement@242 i < count_no_visited → if_statement@251 (not is_finite_distance(dist)) → if_statement@253 (check_func(id) and is_result_distance_eligible<mode>(dist, inner_search_param)) → if_statement@256 (mode == InnerSearchMode::KNN_SEARCH) → if_statement@257 (top_candidates->Size() > ef) → if_statement@258 (reasoning != nullptr)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ top_candidates->Pop  [L263] while_statement@222 (not candidate_set->Empty()) → for_statement@242 i < count_no_visited → if_statement@251 (not is_finite_distance(dist)) → if_statement@253 (check_func(id) and is_result_distance_eligible<mode>(dist, inner_search_param)) → if_statement@256 (mode == InnerSearchMode::KNN_SEARCH) → if_statement@257 (top_candidates->Size() > ef)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ top_candidates->Pop  [L266] while_statement@222 (not candidate_set->Empty()) → for_statement@242 i < count_no_visited → if_statement@251 (not is_finite_distance(dist)) → if_statement@253 (check_func(id) and is_result_distance_eligible<mode>(dist, inner_search_param)) → if_statement@256 (mode == InnerSearchMode::KNN_SEARCH) [else 分支] → if_statement@265 (dist > inner_search_param.radius)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ top_candidates->Empty  [L269] while_statement@222 (not candidate_set->Empty()) → for_statement@242 i < count_no_visited → if_statement@251 (not is_finite_distance(dist)) → if_statement@269 (not top_candidates->Empty())
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ top_candidates->Top  [L270] while_statement@222 (not candidate_set->Empty()) → for_statement@242 i < count_no_visited → if_statement@251 (not is_finite_distance(dist)) → if_statement@269 (not top_candidates->Empty())
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ top_candidates->Size  [L274] while_statement@222 (not candidate_set->Empty()) → for_statement@242 i < count_no_visited → if_statement@274 (top_candidates->Size() < ef || lower_bound > dist || (mode == InnerSearchMode::RANGE_SEARCH && dist <= inner_search_param.radius + THRESHOLD_ERROR))
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ candidate_set->Push  [L277] while_statement@222 (not candidate_set->Empty()) → for_statement@242 i < count_no_visited → if_statement@274 (top_candidates->Size() < ef || lower_bound > dist || (mode == InnerSearchMode::RANGE_SEARCH && dist <= inner_search_param.radius + THRESHOLD_ERROR))
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ distance_provider.Prefetch  [L278] while_statement@222 (not candidate_set->Empty()) → for_statement@242 i < count_no_visited → if_statement@274 (top_candidates->Size() < ef || lower_bound > dist || (mode == InnerSearchMode::RANGE_SEARCH && dist <= inner_search_param.radius + THRESHOLD_ERROR))
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ candidate_set->Top  [L278] while_statement@222 (not candidate_set->Empty()) → for_statement@242 i < count_no_visited → if_statement@274 (top_candidates->Size() < ef || lower_bound > dist || (mode == InnerSearchMode::RANGE_SEARCH && dist <= inner_search_param.radius + THRESHOLD_ERROR))
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ check_func  [L279] while_statement@222 (not candidate_set->Empty()) → for_statement@242 i < count_no_visited → if_statement@274 (top_candidates->Size() < ef || lower_bound > dist || (mode == InnerSearchMode::RANGE_SEARCH && dist <= inner_search_param.radius + THRESHOLD_ERROR)) → if_statement@279 (check_func(id))
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ top_candidates->Push  [L280] while_statement@222 (not candidate_set->Empty()) → for_statement@242 i < count_no_visited → if_statement@274 (top_candidates->Size() < ef || lower_bound > dist || (mode == InnerSearchMode::RANGE_SEARCH && dist <= inner_search_param.radius + THRESHOLD_ERROR)) → if_statement@279 (check_func(id))
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ reasoning->RecordFilterReject  [L282] while_statement@222 (not candidate_set->Empty()) → for_statement@242 i < count_no_visited → if_statement@274 (top_candidates->Size() < ef || lower_bound > dist || (mode == InnerSearchMode::RANGE_SEARCH && dist <= inner_search_param.radius + THRESHOLD_ERROR)) → if_statement@279 (check_func(id)) [else 分支] → if_statement@281 (reasoning != nullptr)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ distance_provider.OriginalId  [L282] while_statement@222 (not candidate_set->Empty()) → for_statement@242 i < count_no_visited → if_statement@274 (top_candidates->Size() < ef || lower_bound > dist || (mode == InnerSearchMode::RANGE_SEARCH && dist <= inner_search_param.radius + THRESHOLD_ERROR)) → if_statement@279 (check_func(id)) [else 分支] → if_statement@281 (reasoning != nullptr)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ top_candidates->Size  [L285] while_statement@222 (not candidate_set->Empty()) → for_statement@242 i < count_no_visited → if_statement@274 (top_candidates->Size() < ef || lower_bound > dist || (mode == InnerSearchMode::RANGE_SEARCH && dist <= inner_search_param.radius + THRESHOLD_ERROR)) → if_statement@284 (mode == InnerSearchMode::KNN_SEARCH) → if_statement@285 (top_candidates->Size() > ef)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ reasoning->RecordEviction  [L287] while_statement@222 (not candidate_set->Empty()) → for_statement@242 i < count_no_visited → if_statement@274 (top_candidates->Size() < ef || lower_bound > dist || (mode == InnerSearchMode::RANGE_SEARCH && dist <= inner_search_param.radius + THRESHOLD_ERROR)) → if_statement@284 (mode == InnerSearchMode::KNN_SEARCH) → if_statement@285 (top_candidates->Size() > ef) → if_statement@286 (reasoning != nullptr)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ distance_provider.OriginalId  [L288] while_statement@222 (not candidate_set->Empty()) → for_statement@242 i < count_no_visited → if_statement@274 (top_candidates->Size() < ef || lower_bound > dist || (mode == InnerSearchMode::RANGE_SEARCH && dist <= inner_search_param.radius + THRESHOLD_ERROR)) → if_statement@284 (mode == InnerSearchMode::KNN_SEARCH) → if_statement@285 (top_candidates->Size() > ef) → if_statement@286 (reasoning != nullptr)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ top_candidates->Top  [L288] while_statement@222 (not candidate_set->Empty()) → for_statement@242 i < count_no_visited → if_statement@274 (top_candidates->Size() < ef || lower_bound > dist || (mode == InnerSearchMode::RANGE_SEARCH && dist <= inner_search_param.radius + THRESHOLD_ERROR)) → if_statement@284 (mode == InnerSearchMode::KNN_SEARCH) → if_statement@285 (top_candidates->Size() > ef) → if_statement@286 (reasoning != nullptr)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ top_candidates->Pop  [L290] while_statement@222 (not candidate_set->Empty()) → for_statement@242 i < count_no_visited → if_statement@274 (top_candidates->Size() < ef || lower_bound > dist || (mode == InnerSearchMode::RANGE_SEARCH && dist <= inner_search_param.radius + THRESHOLD_ERROR)) → if_statement@284 (mode == InnerSearchMode::KNN_SEARCH) → if_statement@285 (top_candidates->Size() > ef)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ top_candidates->Empty  [L293] while_statement@222 (not candidate_set->Empty()) → for_statement@242 i < count_no_visited → if_statement@274 (top_candidates->Size() < ef || lower_bound > dist || (mode == InnerSearchMode::RANGE_SEARCH && dist <= inner_search_param.radius + THRESHOLD_ERROR)) → if_statement@293 (not top_candidates->Empty())
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ top_candidates->Top  [L294] while_statement@222 (not candidate_set->Empty()) → for_statement@242 i < count_no_visited → if_statement@274 (top_candidates->Size() < ef || lower_bound > dist || (mode == InnerSearchMode::RANGE_SEARCH && dist <= inner_search_param.radius + THRESHOLD_ERROR)) → if_statement@293 (not top_candidates->Empty())
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ top_candidates->Size  [L300] if_statement@299 (mode == InnerSearchMode::KNN_SEARCH) → while_statement@300 (top_candidates->Size() > inner_search_param.topk)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ top_candidates->Pop  [L301] if_statement@299 (mode == InnerSearchMode::KNN_SEARCH) → while_statement@300 (top_candidates->Size() > inner_search_param.topk)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ top_candidates->Size  [L305] if_statement@299 (mode == InnerSearchMode::KNN_SEARCH) [else 分支] → if_statement@304 (inner_search_param.range_search_limit_size > 0) → while_statement@305 (top_candidates->Size() > inner_search_param.range_search_limit_size)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ top_candidates->Pop  [L306] if_statement@299 (mode == InnerSearchMode::KNN_SEARCH) [else 分支] → if_statement@304 (inner_search_param.range_search_limit_size > 0) → while_statement@305 (top_candidates->Size() > inner_search_param.range_search_limit_size)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ top_candidates->Empty  [L309] if_statement@299 (mode == InnerSearchMode::KNN_SEARCH) [else 分支] → while_statement@309 (not top_candidates->Empty() && top_candidates->Top().first > inner_search_param.radius + THRESHOLD_ERROR)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ top_candidates->Top  [L310] if_statement@299 (mode == InnerSearchMode::KNN_SEARCH) [else 分支] → while_statement@309 (not top_candidates->Empty() && top_candidates->Top().first > inner_search_param.radius + THRESHOLD_ERROR)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ top_candidates->Pop  [L311] if_statement@299 (mode == InnerSearchMode::KNN_SEARCH) [else 分支] → while_statement@309 (not top_candidates->Empty() && top_candidates->Top().first > inner_search_param.radius + THRESHOLD_ERROR)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ ctx->stats->dist_cmp.fetch_add  [L315] if_statement@314 (ctx != nullptr && ctx->stats != nullptr)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ ctx->stats->hops.fetch_add  [L316] if_statement@314 (ctx != nullptr && ctx->stats != nullptr)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │  #9 BasicSearcher::search_impl [src/impl/searcher/basic_searcher.cpp:322]
  │    │    │    ├─ select_query_allocator  [L332] 函数本体；短路求值/提前返回见源码
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ std::make_shared<StandardHeap<true, false>>  [L334] 函数本体；短路求值/提前返回见源码
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ std::make_shared<StandardHeap<true, false>>  [L335] 函数本体；短路求值/提前返回见源码
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ AcquireQueryComputer  [L341] 函数本体；短路求值/提前返回见源码
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ std::numeric_limits<float>::max  [L351] 函数本体；短路求值/提前返回见源码
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ graph->MaximumDegree  [L356] 函数本体；短路求值/提前返回见源码
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ graph->MaximumDegree  [L357] 函数本体；短路求值/提前返回见源码
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ graph->MaximumDegree  [L358] 函数本体；短路求值/提前返回见源码
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ graph->MaximumDegree  [L359] 函数本体；短路求值/提前返回见源码
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ create_filter_search_skip_strategy  [L360] 函数本体；短路求值/提前返回见源码
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ inner_search_param.is_inner_id_allowed->ValidRatio  [L363] conditional_expression@362 inner_search_param.is_inner_id_allowed != nullptr
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ rabitq_lower_bound_candidates->clear  [L367] if_statement@366 (rabitq_lower_bound_candidates != nullptr)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ iter_ctx->IsFirstUsed  [L370] if_statement@370 (!iter_ctx->IsFirstUsed())
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ iter_ctx->Empty  [L371] if_statement@370 (!iter_ctx->IsFirstUsed()) → if_statement@371 (iter_ctx->Empty())
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ iter_ctx->Empty  [L374] if_statement@370 (!iter_ctx->IsFirstUsed()) → while_statement@374 (!iter_ctx->Empty())
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ iter_ctx->GetTopID  [L375] if_statement@370 (!iter_ctx->IsFirstUsed()) → while_statement@374 (!iter_ctx->Empty())
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ iter_ctx->GetTopDist  [L376] if_statement@370 (!iter_ctx->IsFirstUsed()) → while_statement@374 (!iter_ctx->Empty())
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ vl->Set  [L377] if_statement@370 (!iter_ctx->IsFirstUsed()) → while_statement@374 (!iter_ctx->Empty())
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ iter_ctx->CheckPoint  [L378] if_statement@370 (!iter_ctx->IsFirstUsed()) → while_statement@374 (!iter_ctx->Empty()) → if_statement@378 (iter_ctx->CheckPoint(cur_inner_id))
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ flatten->Query  [L379] if_statement@370 (!iter_ctx->IsFirstUsed()) → while_statement@374 (!iter_ctx->Empty()) → if_statement@378 (iter_ctx->CheckPoint(cur_inner_id))
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ is_result_distance_eligible<mode>  [L382] if_statement@370 (!iter_ctx->IsFirstUsed()) → while_statement@374 (!iter_ctx->Empty()) → if_statement@378 (iter_ctx->CheckPoint(cur_inner_id)) → if_statement@382 (is_result_distance_eligible<mode>(cur_dist, inner_search_param))
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ top_candidates->Push  [L383] if_statement@370 (!iter_ctx->IsFirstUsed()) → while_statement@374 (!iter_ctx->Empty()) → if_statement@378 (iter_ctx->CheckPoint(cur_inner_id)) → if_statement@382 (is_result_distance_eligible<mode>(cur_dist, inner_search_param))
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ candidate_set->Push  [L385] if_statement@370 (!iter_ctx->IsFirstUsed()) → while_statement@374 (!iter_ctx->Empty()) → if_statement@378 (iter_ctx->CheckPoint(cur_inner_id))
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ traversal_priority  [L385] if_statement@370 (!iter_ctx->IsFirstUsed()) → while_statement@374 (!iter_ctx->Empty()) → if_statement@378 (iter_ctx->CheckPoint(cur_inner_id))
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ top_candidates->Empty  [L387] if_statement@370 (!iter_ctx->IsFirstUsed()) → while_statement@374 (!iter_ctx->Empty()) → if_statement@378 (iter_ctx->CheckPoint(cur_inner_id)) → if_statement@386 (mode == InnerSearchMode::RANGE_SEARCH) → if_statement@387 (cur_dist > inner_search_param.radius and not top_candidates->Empty())
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ top_candidates->Pop  [L388] if_statement@370 (!iter_ctx->IsFirstUsed()) → while_statement@374 (!iter_ctx->Empty()) → if_statement@378 (iter_ctx->CheckPoint(cur_inner_id)) → if_statement@386 (mode == InnerSearchMode::RANGE_SEARCH) → if_statement@387 (cur_dist > inner_search_param.radius and not top_candidates->Empty())
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ iter_ctx->PopDiscard  [L392] if_statement@370 (!iter_ctx->IsFirstUsed()) → while_statement@374 (!iter_ctx->Empty())
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ top_candidates->Size  [L395] if_statement@370 (!iter_ctx->IsFirstUsed()) → if_statement@394 (mode == InnerSearchMode::KNN_SEARCH) → while_statement@395 (top_candidates->Size() > ef)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ top_candidates->Top  [L396] if_statement@370 (!iter_ctx->IsFirstUsed()) → if_statement@394 (mode == InnerSearchMode::KNN_SEARCH) → while_statement@395 (top_candidates->Size() > ef)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ iter_ctx->CheckPoint  [L397] if_statement@370 (!iter_ctx->IsFirstUsed()) → if_statement@394 (mode == InnerSearchMode::KNN_SEARCH) → while_statement@395 (top_candidates->Size() > ef) → if_statement@397 (iter_ctx->CheckPoint(cur_node_pair.second))
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ iter_ctx->AddDiscardNode  [L398] if_statement@370 (!iter_ctx->IsFirstUsed()) → if_statement@394 (mode == InnerSearchMode::KNN_SEARCH) → while_statement@395 (top_candidates->Size() > ef) → if_statement@397 (iter_ctx->CheckPoint(cur_node_pair.second))
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ top_candidates->Pop  [L400] if_statement@370 (!iter_ctx->IsFirstUsed()) → if_statement@394 (mode == InnerSearchMode::KNN_SEARCH) → while_statement@395 (top_candidates->Size() > ef)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ top_candidates->Empty  [L403] if_statement@370 (!iter_ctx->IsFirstUsed()) → if_statement@403 (not top_candidates->Empty())
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ top_candidates->Top  [L404] if_statement@370 (!iter_ctx->IsFirstUsed()) → if_statement@403 (not top_candidates->Empty())
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ flatten->QueryWithDistanceLowerBound  [L408] if_statement@370 (!iter_ctx->IsFirstUsed()) [else 分支] → if_statement@407 (inner_search_param.enable_rabitq_one_bit_search)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ flatten->Query  [L410] if_statement@370 (!iter_ctx->IsFirstUsed()) [else 分支] → if_statement@407 (inner_search_param.enable_rabitq_one_bit_search) [else 分支]
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ is_id_allowed->CheckValid  [L412] if_statement@370 (!iter_ctx->IsFirstUsed()) [else 分支] → if_statement@412 (not is_id_allowed || is_id_allowed->CheckValid(ep))
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ is_result_distance_eligible<mode>  [L413] if_statement@370 (!iter_ctx->IsFirstUsed()) [else 分支] → if_statement@412 (not is_id_allowed || is_id_allowed->CheckValid(ep)) → if_statement@413 (is_result_distance_eligible<mode>(dist, inner_search_param))
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ top_candidates->Push  [L414] if_statement@370 (!iter_ctx->IsFirstUsed()) [else 分支] → if_statement@412 (not is_id_allowed || is_id_allowed->CheckValid(ep)) → if_statement@413 (is_result_distance_eligible<mode>(dist, inner_search_param))
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ top_candidates->Top  [L415] if_statement@370 (!iter_ctx->IsFirstUsed()) [else 分支] → if_statement@412 (not is_id_allowed || is_id_allowed->CheckValid(ep)) → if_statement@413 (is_result_distance_eligible<mode>(dist, inner_search_param))
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ candidate_set->Push  [L418] if_statement@370 (!iter_ctx->IsFirstUsed()) [else 分支]
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ traversal_priority  [L418] if_statement@370 (!iter_ctx->IsFirstUsed()) [else 分支]
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ vl->Set  [L419] if_statement@370 (!iter_ctx->IsFirstUsed()) [else 分支]
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ candidate_set->Empty  [L422] while_statement@422 (not candidate_set->Empty())
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ candidate_set->Top  [L427] while_statement@422 (not candidate_set->Empty())
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ top_candidates->Size  [L430] while_statement@422 (not candidate_set->Empty()) → if_statement@429 (mode == InnerSearchMode::KNN_SEARCH) → if_statement@430 ((-current_node_pair.first) > lower_bound && top_candidates->Size() >= ef)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ reasoning->SetTermination  [L432] while_statement@422 (not candidate_set->Empty()) → if_statement@429 (mode == InnerSearchMode::KNN_SEARCH) → if_statement@430 ((-current_node_pair.first) > lower_bound && top_candidates->Size() >= ef) → if_statement@431 (reasoning != nullptr)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ candidate_set->Pop  [L437] while_statement@422 (not candidate_set->Empty())
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ candidate_set->Empty  [L439] while_statement@422 (not candidate_set->Empty()) → if_statement@439 (not candidate_set->Empty())
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ graph->Prefetch  [L440] while_statement@422 (not candidate_set->Empty()) → if_statement@439 (not candidate_set->Empty())
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ candidate_set->Top  [L440] while_statement@422 (not candidate_set->Empty()) → if_statement@439 (not candidate_set->Empty())
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ visit  [L443] while_statement@422 (not candidate_set->Empty())
  │    │    │    │  ↳ 复用节点 #8 BasicSearcher::visit（本树前文已展开）
  │    │    │    ├─ skip_strategy.get  [L447] while_statement@422 (not candidate_set->Empty())
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ top_candidates->Size  [L454] while_statement@422 (not candidate_set->Empty()) → if_statement@454 (inner_search_param.enable_rabitq_one_bit_search and top_candidates->Size() == ef and rabitq_lower_bound_candidates != nullptr)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ flatten->QueryWithDistanceLowerBound  [L457] while_statement@422 (not candidate_set->Empty()) → if_statement@454 (inner_search_param.enable_rabitq_one_bit_search and top_candidates->Size() == ef and rabitq_lower_bound_candidates != nullptr)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ line_dists.data  [L457] while_statement@422 (not candidate_set->Empty()) → if_statement@454 (inner_search_param.enable_rabitq_one_bit_search and top_candidates->Size() == ef and rabitq_lower_bound_candidates != nullptr)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ lower_bound_dists.data  [L458] while_statement@422 (not candidate_set->Empty()) → if_statement@454 (inner_search_param.enable_rabitq_one_bit_search and top_candidates->Size() == ef and rabitq_lower_bound_candidates != nullptr)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ to_be_visited_id.data  [L460] while_statement@422 (not candidate_set->Empty()) → if_statement@454 (inner_search_param.enable_rabitq_one_bit_search and top_candidates->Size() == ef and rabitq_lower_bound_candidates != nullptr)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ flatten->QueryWithDistanceLowerBound  [L464] while_statement@422 (not candidate_set->Empty()) → if_statement@454 (inner_search_param.enable_rabitq_one_bit_search and top_candidates->Size() == ef and rabitq_lower_bound_candidates != nullptr) [else 分支] → if_statement@463 (inner_search_param.enable_rabitq_one_bit_search)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ line_dists.data  [L464] while_statement@422 (not candidate_set->Empty()) → if_statement@454 (inner_search_param.enable_rabitq_one_bit_search and top_candidates->Size() == ef and rabitq_lower_bound_candidates != nullptr) [else 分支] → if_statement@463 (inner_search_param.enable_rabitq_one_bit_search)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ to_be_visited_id.data  [L467] while_statement@422 (not candidate_set->Empty()) → if_statement@454 (inner_search_param.enable_rabitq_one_bit_search and top_candidates->Size() == ef and rabitq_lower_bound_candidates != nullptr) [else 分支] → if_statement@463 (inner_search_param.enable_rabitq_one_bit_search)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ flatten->Query  [L471] while_statement@422 (not candidate_set->Empty()) → if_statement@454 (inner_search_param.enable_rabitq_one_bit_search and top_candidates->Size() == ef and rabitq_lower_bound_candidates != nullptr) [else 分支] → if_statement@463 (inner_search_param.enable_rabitq_one_bit_search) [else 分支]
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ line_dists.data  [L472] while_statement@422 (not candidate_set->Empty()) → if_statement@454 (inner_search_param.enable_rabitq_one_bit_search and top_candidates->Size() == ef and rabitq_lower_bound_candidates != nullptr) [else 分支] → if_statement@463 (inner_search_param.enable_rabitq_one_bit_search) [else 分支]
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ to_be_visited_id.data  [L472] while_statement@422 (not candidate_set->Empty()) → if_statement@454 (inner_search_param.enable_rabitq_one_bit_search and top_candidates->Size() == ef and rabitq_lower_bound_candidates != nullptr) [else 分支] → if_statement@463 (inner_search_param.enable_rabitq_one_bit_search) [else 分支]
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ is_finite_distance  [L477] while_statement@422 (not candidate_set->Empty()) → for_statement@474 i < count_no_visited → if_statement@477 (not is_finite_distance(dist))
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ is_result_distance_eligible<mode>  [L478] while_statement@422 (not candidate_set->Empty()) → for_statement@474 i < count_no_visited → if_statement@477 (not is_finite_distance(dist)) → if_statement@478 (is_result_distance_eligible<mode>(dist, inner_search_param) and (not is_id_allowed || is_id_allowed->CheckValid(cur_id)))
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ is_id_allowed->CheckValid  [L479] while_statement@422 (not candidate_set->Empty()) → for_statement@474 i < count_no_visited → if_statement@477 (not is_finite_distance(dist)) → if_statement@478 (is_result_distance_eligible<mode>(dist, inner_search_param) and (not is_id_allowed || is_id_allowed->CheckValid(cur_id)))
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ top_candidates->Push  [L480] while_statement@422 (not candidate_set->Empty()) → for_statement@474 i < count_no_visited → if_statement@477 (not is_finite_distance(dist)) → if_statement@478 (is_result_distance_eligible<mode>(dist, inner_search_param) and (not is_id_allowed || is_id_allowed->CheckValid(cur_id)))
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ top_candidates->Size  [L482] while_statement@422 (not candidate_set->Empty()) → for_statement@474 i < count_no_visited → if_statement@477 (not is_finite_distance(dist)) → if_statement@478 (is_result_distance_eligible<mode>(dist, inner_search_param) and (not is_id_allowed || is_id_allowed->CheckValid(cur_id))) → if_statement@481 (mode == KNN_SEARCH) → if_statement@482 (top_candidates->Size() > ef)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ top_candidates->Top  [L483] while_statement@422 (not candidate_set->Empty()) → for_statement@474 i < count_no_visited → if_statement@477 (not is_finite_distance(dist)) → if_statement@478 (is_result_distance_eligible<mode>(dist, inner_search_param) and (not is_id_allowed || is_id_allowed->CheckValid(cur_id))) → if_statement@481 (mode == KNN_SEARCH) → if_statement@482 (top_candidates->Size() > ef)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ iter_ctx->CheckPoint  [L484] while_statement@422 (not candidate_set->Empty()) → for_statement@474 i < count_no_visited → if_statement@477 (not is_finite_distance(dist)) → if_statement@478 (is_result_distance_eligible<mode>(dist, inner_search_param) and (not is_id_allowed || is_id_allowed->CheckValid(cur_id))) → if_statement@481 (mode == KNN_SEARCH) → if_statement@482 (top_candidates->Size() > ef) → if_statement@484 (iter_ctx->CheckPoint(evicted.second))
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ iter_ctx->AddDiscardNode  [L485] while_statement@422 (not candidate_set->Empty()) → for_statement@474 i < count_no_visited → if_statement@477 (not is_finite_distance(dist)) → if_statement@478 (is_result_distance_eligible<mode>(dist, inner_search_param) and (not is_id_allowed || is_id_allowed->CheckValid(cur_id))) → if_statement@481 (mode == KNN_SEARCH) → if_statement@482 (top_candidates->Size() > ef) → if_statement@484 (iter_ctx->CheckPoint(evicted.second))
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ top_candidates->Pop  [L487] while_statement@422 (not candidate_set->Empty()) → for_statement@474 i < count_no_visited → if_statement@477 (not is_finite_distance(dist)) → if_statement@478 (is_result_distance_eligible<mode>(dist, inner_search_param) and (not is_id_allowed || is_id_allowed->CheckValid(cur_id))) → if_statement@481 (mode == KNN_SEARCH) → if_statement@482 (top_candidates->Size() > ef)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ top_candidates->Pop  [L490] while_statement@422 (not candidate_set->Empty()) → for_statement@474 i < count_no_visited → if_statement@477 (not is_finite_distance(dist)) → if_statement@478 (is_result_distance_eligible<mode>(dist, inner_search_param) and (not is_id_allowed || is_id_allowed->CheckValid(cur_id))) → if_statement@481 (mode == KNN_SEARCH) [else 分支] → if_statement@489 (dist > inner_search_param.radius)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ iter_ctx->CheckPoint  [L493] while_statement@422 (not candidate_set->Empty()) → for_statement@474 i < count_no_visited → if_statement@477 (not is_finite_distance(dist)) → if_statement@493 (iter_ctx->CheckPoint(cur_id))
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ candidate_set->Push  [L494] while_statement@422 (not candidate_set->Empty()) → for_statement@474 i < count_no_visited → if_statement@477 (not is_finite_distance(dist)) → if_statement@493 (iter_ctx->CheckPoint(cur_id))
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ traversal_priority  [L494] while_statement@422 (not candidate_set->Empty()) → for_statement@474 i < count_no_visited → if_statement@477 (not is_finite_distance(dist)) → if_statement@493 (iter_ctx->CheckPoint(cur_id))
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ flatten->Prefetch  [L495] while_statement@422 (not candidate_set->Empty()) → for_statement@474 i < count_no_visited → if_statement@477 (not is_finite_distance(dist)) → if_statement@493 (iter_ctx->CheckPoint(cur_id))
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ top_candidates->Empty  [L497] while_statement@422 (not candidate_set->Empty()) → for_statement@474 i < count_no_visited → if_statement@477 (not is_finite_distance(dist)) → if_statement@497 (not top_candidates->Empty())
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ top_candidates->Top  [L498] while_statement@422 (not candidate_set->Empty()) → for_statement@474 i < count_no_visited → if_statement@477 (not is_finite_distance(dist)) → if_statement@497 (not top_candidates->Empty())
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ is_id_allowed->CheckValid  [L502] while_statement@422 (not candidate_set->Empty()) → for_statement@474 i < count_no_visited
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ iter_ctx->CheckPoint  [L505] while_statement@422 (not candidate_set->Empty()) → for_statement@474 i < count_no_visited → if_statement@503 (mode == KNN_SEARCH) → if_statement@504 (collect_rabitq_lower_bound and lower_bound_dists[i] < lower_bound and id_allowed and iter_ctx->CheckPoint(cur_id))
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ rabitq_lower_bound_candidates->emplace_back  [L506] while_statement@422 (not candidate_set->Empty()) → for_statement@474 i < count_no_visited → if_statement@503 (mode == KNN_SEARCH) → if_statement@504 (collect_rabitq_lower_bound and lower_bound_dists[i] < lower_bound and id_allowed and iter_ctx->CheckPoint(cur_id))
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ top_candidates->Size  [L509] while_statement@422 (not candidate_set->Empty()) → for_statement@474 i < count_no_visited → if_statement@509 (top_candidates->Size() < ef || lower_bound > dist || (mode == RANGE_SEARCH && dist <= inner_search_param.radius))
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ iter_ctx->CheckPoint  [L511] while_statement@422 (not candidate_set->Empty()) → for_statement@474 i < count_no_visited → if_statement@509 (top_candidates->Size() < ef || lower_bound > dist || (mode == RANGE_SEARCH && dist <= inner_search_param.radius)) → if_statement@511 (!iter_ctx->CheckPoint(cur_id))
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ candidate_set->Push  [L514] while_statement@422 (not candidate_set->Empty()) → for_statement@474 i < count_no_visited → if_statement@509 (top_candidates->Size() < ef || lower_bound > dist || (mode == RANGE_SEARCH && dist <= inner_search_param.radius))
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ flatten->Prefetch  [L515] while_statement@422 (not candidate_set->Empty()) → for_statement@474 i < count_no_visited → if_statement@509 (top_candidates->Size() < ef || lower_bound > dist || (mode == RANGE_SEARCH && dist <= inner_search_param.radius))
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ candidate_set->Top  [L515] while_statement@422 (not candidate_set->Empty()) → for_statement@474 i < count_no_visited → if_statement@509 (top_candidates->Size() < ef || lower_bound > dist || (mode == RANGE_SEARCH && dist <= inner_search_param.radius))
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ top_candidates->Push  [L517] while_statement@422 (not candidate_set->Empty()) → for_statement@474 i < count_no_visited → if_statement@509 (top_candidates->Size() < ef || lower_bound > dist || (mode == RANGE_SEARCH && dist <= inner_search_param.radius)) → if_statement@516 (id_allowed)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ top_candidates->Size  [L521] while_statement@422 (not candidate_set->Empty()) → for_statement@474 i < count_no_visited → if_statement@509 (top_candidates->Size() < ef || lower_bound > dist || (mode == RANGE_SEARCH && dist <= inner_search_param.radius)) → if_statement@520 (mode == KNN_SEARCH) → if_statement@521 (top_candidates->Size() > ef)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ iter_ctx->CheckPoint  [L522] while_statement@422 (not candidate_set->Empty()) → for_statement@474 i < count_no_visited → if_statement@509 (top_candidates->Size() < ef || lower_bound > dist || (mode == RANGE_SEARCH && dist <= inner_search_param.radius)) → if_statement@520 (mode == KNN_SEARCH) → if_statement@521 (top_candidates->Size() > ef) → if_statement@522 (iter_ctx->CheckPoint(top_candidates->Top().second))
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ top_candidates->Top  [L522] while_statement@422 (not candidate_set->Empty()) → for_statement@474 i < count_no_visited → if_statement@509 (top_candidates->Size() < ef || lower_bound > dist || (mode == RANGE_SEARCH && dist <= inner_search_param.radius)) → if_statement@520 (mode == KNN_SEARCH) → if_statement@521 (top_candidates->Size() > ef) → if_statement@522 (iter_ctx->CheckPoint(top_candidates->Top().second))
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ top_candidates->Top  [L523] while_statement@422 (not candidate_set->Empty()) → for_statement@474 i < count_no_visited → if_statement@509 (top_candidates->Size() < ef || lower_bound > dist || (mode == RANGE_SEARCH && dist <= inner_search_param.radius)) → if_statement@520 (mode == KNN_SEARCH) → if_statement@521 (top_candidates->Size() > ef) → if_statement@522 (iter_ctx->CheckPoint(top_candidates->Top().second))
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ iter_ctx->AddDiscardNode  [L524] while_statement@422 (not candidate_set->Empty()) → for_statement@474 i < count_no_visited → if_statement@509 (top_candidates->Size() < ef || lower_bound > dist || (mode == RANGE_SEARCH && dist <= inner_search_param.radius)) → if_statement@520 (mode == KNN_SEARCH) → if_statement@521 (top_candidates->Size() > ef) → if_statement@522 (iter_ctx->CheckPoint(top_candidates->Top().second))
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ top_candidates->Pop  [L526] while_statement@422 (not candidate_set->Empty()) → for_statement@474 i < count_no_visited → if_statement@509 (top_candidates->Size() < ef || lower_bound > dist || (mode == RANGE_SEARCH && dist <= inner_search_param.radius)) → if_statement@520 (mode == KNN_SEARCH) → if_statement@521 (top_candidates->Size() > ef)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ top_candidates->Empty  [L530] while_statement@422 (not candidate_set->Empty()) → for_statement@474 i < count_no_visited → if_statement@509 (top_candidates->Size() < ef || lower_bound > dist || (mode == RANGE_SEARCH && dist <= inner_search_param.radius)) → if_statement@530 (not top_candidates->Empty())
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ top_candidates->Top  [L531] while_statement@422 (not candidate_set->Empty()) → for_statement@474 i < count_no_visited → if_statement@509 (top_candidates->Size() < ef || lower_bound > dist || (mode == RANGE_SEARCH && dist <= inner_search_param.radius)) → if_statement@530 (not top_candidates->Empty())
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ top_candidates->Size  [L538] if_statement@537 (mode == KNN_SEARCH) → while_statement@538 (top_candidates->Size() > inner_search_param.topk)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ top_candidates->Top  [L539] if_statement@537 (mode == KNN_SEARCH) → while_statement@538 (top_candidates->Size() > inner_search_param.topk)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ iter_ctx->CheckPoint  [L540] if_statement@537 (mode == KNN_SEARCH) → while_statement@538 (top_candidates->Size() > inner_search_param.topk) → if_statement@540 (iter_ctx->CheckPoint(cur_node_pair.second))
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ iter_ctx->AddDiscardNode  [L541] if_statement@537 (mode == KNN_SEARCH) → while_statement@538 (top_candidates->Size() > inner_search_param.topk) → if_statement@540 (iter_ctx->CheckPoint(cur_node_pair.second))
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ top_candidates->Pop  [L543] if_statement@537 (mode == KNN_SEARCH) → while_statement@538 (top_candidates->Size() > inner_search_param.topk)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │  #10 BasicSearcher::search_impl [src/impl/searcher/basic_searcher.cpp:551]
  │    │    │    ├─ select_query_allocator  [L562] 函数本体；短路求值/提前返回见源码
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ std::make_shared<StandardHeap<true, false>>  [L564] 函数本体；短路求值/提前返回见源码
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ std::make_shared<StandardHeap<true, false>>  [L565] 函数本体；短路求值/提前返回见源码
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ AcquireQueryComputer  [L575] if_statement@574 (not use_custom_distance and computer == nullptr)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ std::numeric_limits<float>::max  [L584] 函数本体；短路求值/提前返回见源码
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ graph->MaximumDegree  [L589] 函数本体；短路求值/提前返回见源码
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ graph->MaximumDegree  [L590] 函数本体；短路求值/提前返回见源码
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ graph->MaximumDegree  [L591] 函数本体；短路求值/提前返回见源码
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ graph->MaximumDegree  [L592] 函数本体；短路求值/提前返回见源码
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ std::max<uint64_t>  [L595] conditional_expression@594 use_custom_distance
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ std::min<uint64_t>  [L596] conditional_expression@594 use_custom_distance
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ graph->MaximumDegree  [L597] conditional_expression@594 use_custom_distance
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ create_filter_search_skip_strategy  [L600] 函数本体；短路求值/提前返回见源码
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ inner_search_param.is_inner_id_allowed->ValidRatio  [L603] conditional_expression@602 inner_search_param.is_inner_id_allowed != nullptr
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ rabitq_lower_bound_candidates->clear  [L607] if_statement@606 (rabitq_lower_bound_candidates != nullptr)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ inner_search_param.executors.empty  [L611] if_statement@611 (not inner_search_param.executors.empty() and inner_search_param.executors[0] != nullptr)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ inner_search_param.executors[0]->Clear  [L612] if_statement@611 (not inner_search_param.executors.empty() and inner_search_param.executors[0] != nullptr)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ inner_search_param.executors[0]->Run  [L613] if_statement@611 (not inner_search_param.executors.empty() and inner_search_param.executors[0] != nullptr)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ is_id_allowed->CheckValid  [L617] lambda@616（定义体，执行时间取决于调用/调度）
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ attr_ft->CheckValid  [L618] lambda@616（定义体，执行时间取决于调用/调度）
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ flatten->Query  [L624] lambda@622（定义体，执行时间取决于调用/调度） → if_statement@623 (not use_custom_distance)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ CHECK_ARGUMENT  [L627] lambda@622（定义体，执行时间取决于调用/调度）
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ CHECK_ARGUMENT  [L628] lambda@622（定义体，执行时间取决于调用/调度）
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ std::min  [L633] lambda@622（定义体，执行时间取决于调用/调度） → for_statement@630 offset < count
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ label_table->GetLabelById  [L635] lambda@622（定义体，执行时间取决于调用/调度） → for_statement@630 offset < count → for_statement@634 i < batch_count
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ inner_search_param.distance_batch_func  [L637] lambda@622（定义体，执行时间取决于调用/调度） → for_statement@630 offset < count
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ custom_labels.data  [L638] lambda@622（定义体，执行时间取决于调用/调度） → for_statement@630 offset < count
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ ctx->stats->AddDistance  [L640] lambda@622（定义体，执行时间取决于调用/调度） → for_statement@630 offset < count → if_statement@639 (ctx != nullptr and ctx->stats != nullptr)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ CHECK_ARGUMENT  [L644] lambda@622（定义体，执行时间取决于调用/调度） → for_statement@630 offset < count → for_statement@643 i < batch_count
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ is_finite_distance  [L644] lambda@622（定义体，执行时间取决于调用/调度） → for_statement@630 offset < count → for_statement@643 i < batch_count
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ score_ids  [L659] lambda@649（定义体，执行时间取决于调用/调度） → lambda@655（定义体，执行时间取决于调用/调度）
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ neighbors.data  [L659] lambda@649（定义体，执行时间取决于调用/调度） → lambda@655（定义体，执行时间取决于调用/调度）
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ lower_bound_dists.data  [L659] lambda@649（定义体，执行时间取决于调用/调度） → lambda@655（定义体，执行时间取决于调用/调度）
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ reasoning->RecordVisit  [L663] lambda@649（定义体，执行时间取决于调用/调度） → lambda@655（定义体，执行时间取决于调用/调度） → for_statement@661 i < duplicate_count → if_statement@662 (reasoning != nullptr)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ top_candidates->Push  [L665] lambda@649（定义体，执行时间取决于调用/调度） → lambda@655（定义体，执行时间取决于调用/调度） → for_statement@661 i < duplicate_count
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ check_func  [L671] lambda@649（定义体，执行时间取决于调用/调度） → for_range_loop@670 → if_statement@671 (not check_func(item))
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ neighbors.size  [L675] lambda@649（定义体，执行时间取决于调用/调度） → for_range_loop@670 → if_statement@675 (duplicate_count == neighbors.size())
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ submit_duplicates  [L676] lambda@649（定义体，执行时间取决于调用/调度） → for_range_loop@670 → if_statement@675 (duplicate_count == neighbors.size())
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ submit_duplicates  [L679] lambda@649（定义体，执行时间取决于调用/调度）
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ top_candidates->Size  [L682] lambda@649（定义体，执行时间取决于调用/调度） → if_statement@681 (mode == KNN_SEARCH) → while_statement@682 (top_candidates->Size() > ef)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ reasoning->RecordEviction  [L684] lambda@649（定义体，执行时间取决于调用/调度） → if_statement@681 (mode == KNN_SEARCH) → while_statement@682 (top_candidates->Size() > ef) → if_statement@683 (reasoning != nullptr)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ top_candidates->Top  [L684] lambda@649（定义体，执行时间取决于调用/调度） → if_statement@681 (mode == KNN_SEARCH) → while_statement@682 (top_candidates->Size() > ef) → if_statement@683 (reasoning != nullptr)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ top_candidates->Pop  [L686] lambda@649（定义体，执行时间取决于调用/调度） → if_statement@681 (mode == KNN_SEARCH) → while_statement@682 (top_candidates->Size() > ef)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ top_candidates->Empty  [L689] lambda@649（定义体，执行时间取决于调用/调度） → if_statement@689 (not top_candidates->Empty())
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ top_candidates->Top  [L690] lambda@649（定义体，执行时间取决于调用/调度） → if_statement@689 (not top_candidates->Empty())
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ score_ids  [L695] if_statement@694 (use_custom_distance)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ flatten->QueryWithDistanceLowerBound  [L697] if_statement@694 (use_custom_distance) [else 分支] → if_statement@696 (inner_search_param.enable_rabitq_one_bit_search)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ flatten->Query  [L699] if_statement@694 (use_custom_distance) [else 分支] → if_statement@696 (inner_search_param.enable_rabitq_one_bit_search) [else 分支]
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ check_func  [L702] if_statement@702 (check_func(ep) and is_result_distance_eligible<mode>(dist, inner_search_param))
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ is_result_distance_eligible<mode>  [L702] if_statement@702 (check_func(ep) and is_result_distance_eligible<mode>(dist, inner_search_param))
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ top_candidates->Push  [L703] if_statement@702 (check_func(ep) and is_result_distance_eligible<mode>(dist, inner_search_param))
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ is_finite_distance  [L705] if_statement@705 (not is_finite_distance(dist) and inner_search_param.consider_duplicate and not use_custom_distance and is_result_distance_eligible<mode>(dist, inner_search_param))
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ is_result_distance_eligible<mode>  [L706] if_statement@705 (not is_finite_distance(dist) and inner_search_param.consider_duplicate and not use_custom_distance and is_result_distance_eligible<mode>(dist, inner_search_param))
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ graph->GetDuplicateIds  [L707] if_statement@705 (not is_finite_distance(dist) and inner_search_param.consider_duplicate and not use_custom_distance and is_result_distance_eligible<mode>(dist, inner_search_param)) → for_range_loop@707
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ check_func  [L708] if_statement@705 (not is_finite_distance(dist) and inner_search_param.consider_duplicate and not use_custom_distance and is_result_distance_eligible<mode>(dist, inner_search_param)) → for_range_loop@707 → if_statement@708 (check_func(duplicate_id))
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ top_candidates->Push  [L709] if_statement@705 (not is_finite_distance(dist) and inner_search_param.consider_duplicate and not use_custom_distance and is_result_distance_eligible<mode>(dist, inner_search_param)) → for_range_loop@707 → if_statement@708 (check_func(duplicate_id))
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ top_candidates->Size  [L713] if_statement@705 (not is_finite_distance(dist) and inner_search_param.consider_duplicate and not use_custom_distance and is_result_distance_eligible<mode>(dist, inner_search_param)) → if_statement@712 (mode == KNN_SEARCH) → while_statement@713 (top_candidates->Size() > ef)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ top_candidates->Pop  [L714] if_statement@705 (not is_finite_distance(dist) and inner_search_param.consider_duplicate and not use_custom_distance and is_result_distance_eligible<mode>(dist, inner_search_param)) → if_statement@712 (mode == KNN_SEARCH) → while_statement@713 (top_candidates->Size() > ef)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ top_candidates->Empty  [L719] if_statement@718 (mode == InnerSearchMode::RANGE_SEARCH) → while_statement@719 (dist > inner_search_param.radius and not top_candidates->Empty())
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ top_candidates->Pop  [L720] if_statement@718 (mode == InnerSearchMode::RANGE_SEARCH) → while_statement@719 (dist > inner_search_param.radius and not top_candidates->Empty())
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ top_candidates->Empty  [L723] if_statement@723 (not top_candidates->Empty())
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ top_candidates->Top  [L724] if_statement@723 (not top_candidates->Empty())
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ graph->GetDuplicateIds  [L727] if_statement@726 (use_custom_distance and inner_search_param.consider_duplicate)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ score_duplicates  [L728] if_statement@726 (use_custom_distance and inner_search_param.consider_duplicate)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ candidate_set->Push  [L730] 函数本体；短路求值/提前返回见源码
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ traversal_priority  [L730] 函数本体；短路求值/提前返回见源码
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ vl->Set  [L731] 函数本体；短路求值/提前返回见源码
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ candidate_set->Empty  [L733] while_statement@733 (not candidate_set->Empty())
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ reasoning->SetTermination  [L737] while_statement@733 (not candidate_set->Empty()) → if_statement@735 (hops >= inner_search_param.hops_limit) → if_statement@736 (reasoning != nullptr)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ reasoning->AddSearchHop  [L742] while_statement@733 (not candidate_set->Empty()) → if_statement@741 (reasoning != nullptr)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ candidate_set->Top  [L744] while_statement@733 (not candidate_set->Empty())
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ inner_search_param.time_cost->CheckOvertime  [L747] while_statement@733 (not candidate_set->Empty()) → if_statement@746 (inner_search_param.time_cost != nullptr and inner_search_param.time_cost->CheckOvertime())
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ ctx->stats->is_timeout.store  [L749] while_statement@733 (not candidate_set->Empty()) → if_statement@746 (inner_search_param.time_cost != nullptr and inner_search_param.time_cost->CheckOvertime()) → if_statement@748 (ctx != nullptr and ctx->stats != nullptr)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ reasoning->SetTermination  [L752] while_statement@733 (not candidate_set->Empty()) → if_statement@746 (inner_search_param.time_cost != nullptr and inner_search_param.time_cost->CheckOvertime()) → if_statement@751 (reasoning != nullptr)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ top_candidates->Size  [L758] while_statement@733 (not candidate_set->Empty()) → if_statement@757 (mode == InnerSearchMode::KNN_SEARCH) → if_statement@758 ((-current_node_pair.first) > lower_bound && top_candidates->Size() >= ef)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ reasoning->SetTermination  [L760] while_statement@733 (not candidate_set->Empty()) → if_statement@757 (mode == InnerSearchMode::KNN_SEARCH) → if_statement@758 ((-current_node_pair.first) > lower_bound && top_candidates->Size() >= ef) → if_statement@759 (reasoning != nullptr)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ candidate_set->Pop  [L765] while_statement@733 (not candidate_set->Empty())
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ candidate_set->Empty  [L767] while_statement@733 (not candidate_set->Empty()) → if_statement@767 (not candidate_set->Empty())
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ graph->Prefetch  [L768] while_statement@733 (not candidate_set->Empty()) → if_statement@767 (not candidate_set->Empty())
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ candidate_set->Top  [L768] while_statement@733 (not candidate_set->Empty()) → if_statement@767 (not candidate_set->Empty())
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ visit  [L771] while_statement@733 (not candidate_set->Empty())
  │    │    │    │  ↳ 复用节点 #8 BasicSearcher::visit（本树前文已展开）
  │    │    │    ├─ skip_strategy.get  [L775] while_statement@733 (not candidate_set->Empty())
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ score_ids  [L781] while_statement@733 (not candidate_set->Empty()) → if_statement@780 (use_custom_distance)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ to_be_visited_id.data  [L781] while_statement@733 (not candidate_set->Empty()) → if_statement@780 (use_custom_distance)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ line_dists.data  [L781] while_statement@733 (not candidate_set->Empty()) → if_statement@780 (use_custom_distance)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ top_candidates->Size  [L783] while_statement@733 (not candidate_set->Empty()) → if_statement@780 (use_custom_distance) [else 分支] → if_statement@782 (inner_search_param.enable_rabitq_one_bit_search and top_candidates->Size() == ef and rabitq_lower_bound_candidates != nullptr)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ flatten->QueryWithDistanceLowerBound  [L785] while_statement@733 (not candidate_set->Empty()) → if_statement@780 (use_custom_distance) [else 分支] → if_statement@782 (inner_search_param.enable_rabitq_one_bit_search and top_candidates->Size() == ef and rabitq_lower_bound_candidates != nullptr)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ line_dists.data  [L785] while_statement@733 (not candidate_set->Empty()) → if_statement@780 (use_custom_distance) [else 分支] → if_statement@782 (inner_search_param.enable_rabitq_one_bit_search and top_candidates->Size() == ef and rabitq_lower_bound_candidates != nullptr)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ lower_bound_dists.data  [L786] while_statement@733 (not candidate_set->Empty()) → if_statement@780 (use_custom_distance) [else 分支] → if_statement@782 (inner_search_param.enable_rabitq_one_bit_search and top_candidates->Size() == ef and rabitq_lower_bound_candidates != nullptr)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ to_be_visited_id.data  [L788] while_statement@733 (not candidate_set->Empty()) → if_statement@780 (use_custom_distance) [else 分支] → if_statement@782 (inner_search_param.enable_rabitq_one_bit_search and top_candidates->Size() == ef and rabitq_lower_bound_candidates != nullptr)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ flatten->QueryWithDistanceLowerBound  [L792] while_statement@733 (not candidate_set->Empty()) → if_statement@780 (use_custom_distance) [else 分支] → if_statement@782 (inner_search_param.enable_rabitq_one_bit_search and top_candidates->Size() == ef and rabitq_lower_bound_candidates != nullptr) [else 分支] → if_statement@791 (inner_search_param.enable_rabitq_one_bit_search)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ line_dists.data  [L792] while_statement@733 (not candidate_set->Empty()) → if_statement@780 (use_custom_distance) [else 分支] → if_statement@782 (inner_search_param.enable_rabitq_one_bit_search and top_candidates->Size() == ef and rabitq_lower_bound_candidates != nullptr) [else 分支] → if_statement@791 (inner_search_param.enable_rabitq_one_bit_search)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ to_be_visited_id.data  [L795] while_statement@733 (not candidate_set->Empty()) → if_statement@780 (use_custom_distance) [else 分支] → if_statement@782 (inner_search_param.enable_rabitq_one_bit_search and top_candidates->Size() == ef and rabitq_lower_bound_candidates != nullptr) [else 分支] → if_statement@791 (inner_search_param.enable_rabitq_one_bit_search)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ flatten->Query  [L799] while_statement@733 (not candidate_set->Empty()) → if_statement@780 (use_custom_distance) [else 分支] → if_statement@782 (inner_search_param.enable_rabitq_one_bit_search and top_candidates->Size() == ef and rabitq_lower_bound_candidates != nullptr) [else 分支] → if_statement@791 (inner_search_param.enable_rabitq_one_bit_search) [else 分支]
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ line_dists.data  [L800] while_statement@733 (not candidate_set->Empty()) → if_statement@780 (use_custom_distance) [else 分支] → if_statement@782 (inner_search_param.enable_rabitq_one_bit_search and top_candidates->Size() == ef and rabitq_lower_bound_candidates != nullptr) [else 分支] → if_statement@791 (inner_search_param.enable_rabitq_one_bit_search) [else 分支]
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ to_be_visited_id.data  [L800] while_statement@733 (not candidate_set->Empty()) → if_statement@780 (use_custom_distance) [else 分支] → if_statement@782 (inner_search_param.enable_rabitq_one_bit_search and top_candidates->Size() == ef and rabitq_lower_bound_candidates != nullptr) [else 分支] → if_statement@791 (inner_search_param.enable_rabitq_one_bit_search) [else 分支]
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ reasoning->RecordVisit  [L808] while_statement@733 (not candidate_set->Empty()) → for_statement@804 i < count_no_visited → if_statement@807 (reasoning != nullptr)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ graph->GetDuplicateIds  [L811] while_statement@733 (not candidate_set->Empty()) → for_statement@804 i < count_no_visited → if_statement@810 (use_custom_distance and inner_search_param.consider_duplicate)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ score_duplicates  [L812] while_statement@733 (not candidate_set->Empty()) → for_statement@804 i < count_no_visited → if_statement@810 (use_custom_distance and inner_search_param.consider_duplicate)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ is_finite_distance  [L814] while_statement@733 (not candidate_set->Empty()) → for_statement@804 i < count_no_visited → if_statement@814 (not is_finite_distance(dist))
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ candidate_set->Push  [L815] while_statement@733 (not candidate_set->Empty()) → for_statement@804 i < count_no_visited → if_statement@814 (not is_finite_distance(dist))
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ traversal_priority  [L815] while_statement@733 (not candidate_set->Empty()) → for_statement@804 i < count_no_visited → if_statement@814 (not is_finite_distance(dist))
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ is_result_distance_eligible<mode>  [L817] while_statement@733 (not candidate_set->Empty()) → for_statement@804 i < count_no_visited → if_statement@814 (not is_finite_distance(dist)) → lambda@816（定义体，执行时间取决于调用/调度） → if_statement@817 (not is_result_distance_eligible<mode>(dist, inner_search_param) or not check_func(result_id))
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ check_func  [L818] while_statement@733 (not candidate_set->Empty()) → for_statement@804 i < count_no_visited → if_statement@814 (not is_finite_distance(dist)) → lambda@816（定义体，执行时间取决于调用/调度） → if_statement@817 (not is_result_distance_eligible<mode>(dist, inner_search_param) or not check_func(result_id))
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ top_candidates->Push  [L821] while_statement@733 (not candidate_set->Empty()) → for_statement@804 i < count_no_visited → if_statement@814 (not is_finite_distance(dist)) → lambda@816（定义体，执行时间取决于调用/调度）
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ top_candidates->Size  [L823] while_statement@733 (not candidate_set->Empty()) → for_statement@804 i < count_no_visited → if_statement@814 (not is_finite_distance(dist)) → lambda@816（定义体，执行时间取决于调用/调度） → if_statement@822 (mode == KNN_SEARCH) → while_statement@823 (top_candidates->Size() > ef)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ reasoning->RecordEviction  [L825] while_statement@733 (not candidate_set->Empty()) → for_statement@804 i < count_no_visited → if_statement@814 (not is_finite_distance(dist)) → lambda@816（定义体，执行时间取决于调用/调度） → if_statement@822 (mode == KNN_SEARCH) → while_statement@823 (top_candidates->Size() > ef) → if_statement@824 (reasoning != nullptr)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ top_candidates->Top  [L825] while_statement@733 (not candidate_set->Empty()) → for_statement@804 i < count_no_visited → if_statement@814 (not is_finite_distance(dist)) → lambda@816（定义体，执行时间取决于调用/调度） → if_statement@822 (mode == KNN_SEARCH) → while_statement@823 (top_candidates->Size() > ef) → if_statement@824 (reasoning != nullptr)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ top_candidates->Pop  [L827] while_statement@733 (not candidate_set->Empty()) → for_statement@804 i < count_no_visited → if_statement@814 (not is_finite_distance(dist)) → lambda@816（定义体，执行时间取决于调用/调度） → if_statement@822 (mode == KNN_SEARCH) → while_statement@823 (top_candidates->Size() > ef)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ top_candidates->Pop  [L830] while_statement@733 (not candidate_set->Empty()) → for_statement@804 i < count_no_visited → if_statement@814 (not is_finite_distance(dist)) → lambda@816（定义体，执行时间取决于调用/调度） → if_statement@822 (mode == KNN_SEARCH) [else 分支] → if_statement@829 (dist > inner_search_param.radius)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ push_result  [L833] while_statement@733 (not candidate_set->Empty()) → for_statement@804 i < count_no_visited → if_statement@814 (not is_finite_distance(dist))
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ graph->GetDuplicateIds  [L835] while_statement@733 (not candidate_set->Empty()) → for_statement@804 i < count_no_visited → if_statement@814 (not is_finite_distance(dist)) → if_statement@834 (inner_search_param.consider_duplicate and not use_custom_distance) → for_range_loop@835
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ push_result  [L836] while_statement@733 (not candidate_set->Empty()) → for_statement@804 i < count_no_visited → if_statement@814 (not is_finite_distance(dist)) → if_statement@834 (inner_search_param.consider_duplicate and not use_custom_distance) → for_range_loop@835
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ top_candidates->Empty  [L839] while_statement@733 (not candidate_set->Empty()) → for_statement@804 i < count_no_visited → if_statement@814 (not is_finite_distance(dist)) → if_statement@839 (not top_candidates->Empty())
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ top_candidates->Top  [L840] while_statement@733 (not candidate_set->Empty()) → for_statement@804 i < count_no_visited → if_statement@814 (not is_finite_distance(dist)) → if_statement@839 (not top_candidates->Empty())
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ check_func  [L846] while_statement@733 (not candidate_set->Empty()) → for_statement@804 i < count_no_visited → if_statement@844 (mode == KNN_SEARCH) → if_statement@845 (collect_rabitq_lower_bound and lower_bound_dists[i] < lower_bound and check_func(cur_id))
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ rabitq_lower_bound_candidates->emplace_back  [L847] while_statement@733 (not candidate_set->Empty()) → for_statement@804 i < count_no_visited → if_statement@844 (mode == KNN_SEARCH) → if_statement@845 (collect_rabitq_lower_bound and lower_bound_dists[i] < lower_bound and check_func(cur_id))
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ top_candidates->Size  [L850] while_statement@733 (not candidate_set->Empty()) → for_statement@804 i < count_no_visited → if_statement@850 (top_candidates->Size() < ef || lower_bound > dist || (mode == RANGE_SEARCH && dist <= inner_search_param.radius))
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ candidate_set->Push  [L852] while_statement@733 (not candidate_set->Empty()) → for_statement@804 i < count_no_visited → if_statement@850 (top_candidates->Size() < ef || lower_bound > dist || (mode == RANGE_SEARCH && dist <= inner_search_param.radius))
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ check_func  [L854] while_statement@733 (not candidate_set->Empty()) → for_statement@804 i < count_no_visited → if_statement@850 (top_candidates->Size() < ef || lower_bound > dist || (mode == RANGE_SEARCH && dist <= inner_search_param.radius)) → if_statement@854 (check_func(cur_id))
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ top_candidates->Push  [L855] while_statement@733 (not candidate_set->Empty()) → for_statement@804 i < count_no_visited → if_statement@850 (top_candidates->Size() < ef || lower_bound > dist || (mode == RANGE_SEARCH && dist <= inner_search_param.radius)) → if_statement@854 (check_func(cur_id))
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ reasoning->RecordFilterReject  [L857] while_statement@733 (not candidate_set->Empty()) → for_statement@804 i < count_no_visited → if_statement@850 (top_candidates->Size() < ef || lower_bound > dist || (mode == RANGE_SEARCH && dist <= inner_search_param.radius)) → if_statement@854 (check_func(cur_id)) [else 分支] → if_statement@856 (reasoning != nullptr)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ graph->GetDuplicateIds  [L860] while_statement@733 (not candidate_set->Empty()) → for_statement@804 i < count_no_visited → if_statement@850 (top_candidates->Size() < ef || lower_bound > dist || (mode == RANGE_SEARCH && dist <= inner_search_param.radius)) → if_statement@859 (inner_search_param.consider_duplicate and not use_custom_distance)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ check_func  [L862] while_statement@733 (not candidate_set->Empty()) → for_statement@804 i < count_no_visited → if_statement@850 (top_candidates->Size() < ef || lower_bound > dist || (mode == RANGE_SEARCH && dist <= inner_search_param.radius)) → if_statement@859 (inner_search_param.consider_duplicate and not use_custom_distance) → for_range_loop@861 → if_statement@862 (check_func(item))
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ top_candidates->Push  [L863] while_statement@733 (not candidate_set->Empty()) → for_statement@804 i < count_no_visited → if_statement@850 (top_candidates->Size() < ef || lower_bound > dist || (mode == RANGE_SEARCH && dist <= inner_search_param.radius)) → if_statement@859 (inner_search_param.consider_duplicate and not use_custom_distance) → for_range_loop@861 → if_statement@862 (check_func(item))
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ top_candidates->Size  [L869] while_statement@733 (not candidate_set->Empty()) → for_statement@804 i < count_no_visited → if_statement@850 (top_candidates->Size() < ef || lower_bound > dist || (mode == RANGE_SEARCH && dist <= inner_search_param.radius)) → if_statement@868 (mode == KNN_SEARCH) → if_statement@869 (top_candidates->Size() > ef)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ reasoning->RecordEviction  [L871] while_statement@733 (not candidate_set->Empty()) → for_statement@804 i < count_no_visited → if_statement@850 (top_candidates->Size() < ef || lower_bound > dist || (mode == RANGE_SEARCH && dist <= inner_search_param.radius)) → if_statement@868 (mode == KNN_SEARCH) → if_statement@869 (top_candidates->Size() > ef) → if_statement@870 (reasoning != nullptr)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ top_candidates->Top  [L871] while_statement@733 (not candidate_set->Empty()) → for_statement@804 i < count_no_visited → if_statement@850 (top_candidates->Size() < ef || lower_bound > dist || (mode == RANGE_SEARCH && dist <= inner_search_param.radius)) → if_statement@868 (mode == KNN_SEARCH) → if_statement@869 (top_candidates->Size() > ef) → if_statement@870 (reasoning != nullptr)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ top_candidates->Pop  [L873] while_statement@733 (not candidate_set->Empty()) → for_statement@804 i < count_no_visited → if_statement@850 (top_candidates->Size() < ef || lower_bound > dist || (mode == RANGE_SEARCH && dist <= inner_search_param.radius)) → if_statement@868 (mode == KNN_SEARCH) → if_statement@869 (top_candidates->Size() > ef)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ top_candidates->Empty  [L877] while_statement@733 (not candidate_set->Empty()) → for_statement@804 i < count_no_visited → if_statement@850 (top_candidates->Size() < ef || lower_bound > dist || (mode == RANGE_SEARCH && dist <= inner_search_param.radius)) → if_statement@877 (not top_candidates->Empty())
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ top_candidates->Top  [L878] while_statement@733 (not candidate_set->Empty()) → for_statement@804 i < count_no_visited → if_statement@850 (top_candidates->Size() < ef || lower_bound > dist || (mode == RANGE_SEARCH && dist <= inner_search_param.radius)) → if_statement@877 (not top_candidates->Empty())
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ top_candidates->Size  [L885] if_statement@884 (mode == KNN_SEARCH) → while_statement@885 (top_candidates->Size() > inner_search_param.topk)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ top_candidates->Pop  [L886] if_statement@884 (mode == KNN_SEARCH) → while_statement@885 (top_candidates->Size() > inner_search_param.topk)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ top_candidates->Size  [L890] if_statement@884 (mode == KNN_SEARCH) [else 分支] → if_statement@888 (mode == RANGE_SEARCH) → if_statement@889 (inner_search_param.range_search_limit_size > 0) → while_statement@890 (top_candidates->Size() > inner_search_param.range_search_limit_size)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ top_candidates->Pop  [L891] if_statement@884 (mode == KNN_SEARCH) [else 分支] → if_statement@888 (mode == RANGE_SEARCH) → if_statement@889 (inner_search_param.range_search_limit_size > 0) → while_statement@890 (top_candidates->Size() > inner_search_param.range_search_limit_size)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ top_candidates->Empty  [L894] if_statement@884 (mode == KNN_SEARCH) [else 分支] → if_statement@888 (mode == RANGE_SEARCH) → while_statement@894 (not top_candidates->Empty() && top_candidates->Top().first > inner_search_param.radius + THRESHOLD_ERROR)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ top_candidates->Top  [L895] if_statement@884 (mode == KNN_SEARCH) [else 分支] → if_statement@888 (mode == RANGE_SEARCH) → while_statement@894 (not top_candidates->Empty() && top_candidates->Top().first > inner_search_param.radius + THRESHOLD_ERROR)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ top_candidates->Pop  [L896] if_statement@884 (mode == KNN_SEARCH) [else 分支] → if_statement@888 (mode == RANGE_SEARCH) → while_statement@894 (not top_candidates->Empty() && top_candidates->Top().first > inner_search_param.radius + THRESHOLD_ERROR)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ top_candidates->Empty  [L902] if_statement@901 (not use_custom_distance and inner_search_param.find_duplicate and not top_candidates->Empty())
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ top_candidates->GetData  [L903] if_statement@901 (not use_custom_distance and inner_search_param.find_duplicate and not top_candidates->Empty())
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ top_candidates->Size  [L906] if_statement@901 (not use_custom_distance and inner_search_param.find_duplicate and not top_candidates->Empty()) → for_statement@906 i < top_candidates->Size()
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ flatten->TotalCount  [L918] if_statement@901 (not use_custom_distance and inner_search_param.find_duplicate and not top_candidates->Empty()) → if_statement@912 (inner_search_param.duplicate_distance_threshold > 0.0F) [else 分支]
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ flatten->CompareVectors  [L921] if_statement@901 (not use_custom_distance and inner_search_param.find_duplicate and not top_candidates->Empty()) → if_statement@912 (inner_search_param.duplicate_distance_threshold > 0.0F) [else 分支] → conditional_expression@920 has_stored_query
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ flatten->CompareRawVectorWithId  [L922] if_statement@901 (not use_custom_distance and inner_search_param.find_duplicate and not top_candidates->Empty()) → if_statement@912 (inner_search_param.duplicate_distance_threshold > 0.0F) [else 分支] → conditional_expression@920 has_stored_query
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ stats.dist_cmp.fetch_add  [L931] if_statement@929 (ctx != nullptr and ctx->stats != nullptr)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ stats.hops.fetch_add  [L932] if_statement@929 (ctx != nullptr and ctx->stats != nullptr)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ this->search_impl<RANGE_SEARCH>  [L96] 函数本体；短路求值/提前返回见源码
  │    │    │  ├─ 以下为分派/重载候选，并非全部依次执行
  │    │    │  ↳ 复用节点 #7 BasicSearcher::search_impl（本树前文已展开）
  │    │    │  ↳ 复用节点 #9 BasicSearcher::search_impl（本树前文已展开）
  │    │    │  ↳ 复用节点 #10 BasicSearcher::search_impl（本树前文已展开）
  │    │  #11 BasicSearcher::Search [src/impl/searcher/basic_searcher.cpp:139]
  │    │    ├─ this->search_impl<KNN_SEARCH>  [L148] 函数本体；短路求值/提前返回见源码
  │    │    │  ├─ 以下为分派/重载候选，并非全部依次执行
  │    │    │  ↳ 复用节点 #7 BasicSearcher::search_impl（本树前文已展开）
  │    │    │  ↳ 复用节点 #9 BasicSearcher::search_impl（本树前文已展开）
  │    │    │  ↳ 复用节点 #10 BasicSearcher::search_impl（本树前文已展开）
  │    │  #12 BasicSearcher::Search [src/impl/searcher/basic_searcher.cpp:158]
  │    │    ├─ this->search_impl<InnerSearchMode::RANGE_SEARCH>  [L166] if_statement@165 (inner_search_param.search_mode == InnerSearchMode::RANGE_SEARCH)
  │    │    │  ├─ 以下为分派/重载候选，并非全部依次执行
  │    │    │  ↳ 复用节点 #7 BasicSearcher::search_impl（本树前文已展开）
  │    │    │  ↳ 复用节点 #9 BasicSearcher::search_impl（本树前文已展开）
  │    │    │  ↳ 复用节点 #10 BasicSearcher::search_impl（本树前文已展开）
  │    │    ├─ this->search_impl<InnerSearchMode::KNN_SEARCH>  [L169] 函数本体；短路求值/提前返回见源码
  │    │    │  ├─ 以下为分派/重载候选，并非全部依次执行
  │    │    │  ↳ 复用节点 #7 BasicSearcher::search_impl（本树前文已展开）
  │    │    │  ↳ 复用节点 #9 BasicSearcher::search_impl（本树前文已展开）
  │    │    │  ↳ 复用节点 #10 BasicSearcher::search_impl（本树前文已展开）
  │    ├─ top_candidates->Empty  [L137] while_statement@137 (not top_candidates->Empty())
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ top_candidates->Top  [L138] while_statement@137 (not top_candidates->Empty())
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ heap->Push  [L139] while_statement@137 (not top_candidates->Empty())
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ top_candidates->Pop  [L140] while_statement@137 (not top_candidates->Empty())
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ heap->Size  [L142] while_statement@142 (heap->Size() > result_limit)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ heap->Pop  [L143] while_statement@142 (heap->Size() > result_limit)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ flat_searcher_->Search  [L64] if_statement@53 (graph_fresh && bucket_size >= graph_build_threshold_) [else 分支]
  │  #13 FlatBucketSearcher::Search [src/algorithm/ivf/flat_bucket_searcher.cpp:26]
  │    ├─ bucket->GetBucketSize  [L37] 函数本体；短路求值/提前返回见源码
  │    │  ↳ 复用节点 #2 BucketDataCell::GetBucketSize（本树前文已展开）
  │    ├─ bucket->GetInnerIds  [L38] 函数本体；短路求值/提前返回见源码
  │    │  ↳ 复用节点 #5 BucketDataCell::GetInnerIds（本树前文已展开）
  │    ├─ dist.size  [L39] if_statement@39 (bucket_size > static_cast<int64_t>(dist.size()))
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ dist.resize  [L40] if_statement@39 (bucket_size > static_cast<int64_t>(dist.size()))
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ bucket->ScanBucketById  [L43] 函数本体；短路求值/提前返回见源码
  │    │  #14 BucketDataCell::ScanBucketById [src/datacell/bucket_datacell.h:63]
  │    │    ├─ computer.get  [L67] 函数本体；短路求值/提前返回见源码
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ this->scan_bucket_by_id  [L68] 函数本体；短路求值/提前返回见源码
  │    │    │  #15 BucketDataCell<QuantTmpl, IOTmpl>::scan_bucket_by_id [src/datacell/bucket_datacell.h:522]
  │    │    │    ├─ VsagException  [L527] if_statement@526 (bucket_id >= this->bucket_count_ or bucket_id < 0)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ this->check_valid_bucket_id  [L532] 函数本体；短路求值/提前返回见源码
  │    │    │    │  ↳ 复用节点 #3 BucketDataCell::check_valid_bucket_id（本树前文已展开）
  │    │    │    ├─ std::min  [L535] while_statement@534 (data_count > 0)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ this->datas_[bucket_id].Acquire  [L537] while_statement@534 (data_count > 0)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ computer->ScanBatchDists  [L538] while_statement@534 (data_count > 0)
  │    │    │    │  ├─ 以下为分派/重载候选，并非全部依次执行
  │    │    │    │  #16 Computer::ScanBatchDists [src/quantization/computer.h:68]
  │    │    │    │    ├─ quantizer_->ScanBatchDists  [L70] 函数本体；短路求值/提前返回见源码
  │    │    │    │    │  #17 Quantizer::ScanBatchDists [src/quantization/quantizer.h:230]
  │    │    │    │    │    ├─ cast().ScanBatchDistImpl  [L235] 函数本体；短路求值/提前返回见源码
  │    │    │    │    │    │  ├─ 以下为分派/重载候选，并非全部依次执行
  │    │    │    │    │    │  #18 Quantizer::ScanBatchDistImpl [src/quantization/quantizer.h:290]
  │    │    │    │    │    │    ├─ cast().ComputeDistImpl  [L296] for_statement@295 i < count
  │    │    │    │    │    │    │  #19 FP32Quantizer<metric>::ComputeDistImpl [src/quantization/fp32_quantizer.cpp:164]
  │    │    │    │    │    │    │    ├─ FP32ComputeIP  [L169] if_statement@168 (metric == MetricType::METRIC_TYPE_IP)
  │    │    │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    │    │    ├─ FP32ComputeIP  [L173] if_statement@168 (metric == MetricType::METRIC_TYPE_IP) [else 分支] → if_statement@172 (metric == MetricType::METRIC_TYPE_COSINE)
  │    │    │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    │    │    ├─ FP32ComputeL2Sqr  [L182] if_statement@168 (metric == MetricType::METRIC_TYPE_IP) [else 分支] → if_statement@172 (metric == MetricType::METRIC_TYPE_COSINE) [else 分支] → if_statement@181 (metric == MetricType::METRIC_TYPE_L2SQR)
  │    │    │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    │    ├─ cast  [L296] for_statement@295 i < count
  │    │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    │  #20 FP32Quantizer<metric>::ScanBatchDistImpl [src/quantization/fp32_quantizer.cpp:132]
  │    │    │    │    │    │    ├─ this->ComputeDistImpl  [L139] for_statement@138 i < count
  │    │    │    │    │    │    │  ↳ 复用节点 #19 FP32Quantizer<metric>::ComputeDistImpl（本树前文已展开）
  │    │    │    │    │    ├─ cast  [L235] 函数本体；短路求值/提前返回见源码
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │  #21 Computer<TransformQuantizer<QuantImpl, metric>>::ScanBatchDists [src/quantization/computer.h:142]
  │    │    │    │    ├─ quantizer_->ScanBatchDists  [L144] 函数本体；短路求值/提前返回见源码
  │    │    │    │    │  ↳ 复用节点 #17 Quantizer::ScanBatchDists（本树前文已展开）
  │    │    │    ├─ lease.Data  [L538] while_statement@534 (data_count > 0)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ this->quantizer_->GetDim  [L544] 函数本体；短路求值/提前返回见源码
  │    │    │    │  #22 Quantizer::GetDim [src/quantization/quantizer.h:340]
  │    │    │    ├─ strategy_->GetCentroid  [L546] if_statement@545 (use_residual_)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ FP32ComputeIP  [L548] if_statement@545 (use_residual_)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ computer->raw_query_.data  [L548] if_statement@545 (use_residual_)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ centroid.data  [L548] if_statement@545 (use_residual_)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ this->quantizer_->GetDim  [L548] if_statement@545 (use_residual_)
  │    │    │    │  ↳ 复用节点 #22 Quantizer::GetDim（本树前文已展开）
  │    │    │    ├─ FP32Sub  [L551] if_statement@545 (use_residual_) → if_statement@549 (metric_ == MetricType::METRIC_TYPE_L2SQR)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ residual_bias_[bucket_id].data  [L551] if_statement@545 (use_residual_) → if_statement@549 (metric_ == MetricType::METRIC_TYPE_L2SQR)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ std::numeric_limits<float>::max  [L560] for_statement@558 i < offset → if_statement@559 (this->inner_ids_[bucket_id][i] == EMPTY_INNER_ID)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ dist.data  [L43] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ param.query_context->stats->AddDistance  [L46] if_statement@44 (param.query_context != nullptr and param.query_context->stats != nullptr and bucket_size > 0)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ param.executors.size  [L53] if_statement@53 (thread_id >= 0 and param.executors.size() > static_cast<uint64_t>(thread_id))
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ param.executors[tid]->Clear  [L56] if_statement@53 (thread_id >= 0 and param.executors.size() > static_cast<uint64_t>(thread_id)) → if_statement@55 (param.executors[tid] != nullptr)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ param.executors[tid]->Run  [L57] if_statement@53 (thread_id >= 0 and param.executors.size() > static_cast<uint64_t>(thread_id)) → if_statement@55 (param.executors[tid] != nullptr)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ std::numeric_limits<float>::max  [L63] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ heap->Empty  [L64] if_statement@64 (not heap->Empty() and heap->Size() == topk_u)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ heap->Size  [L64] if_statement@64 (not heap->Empty() and heap->Size() == topk_u)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ heap->Top  [L65] if_statement@64 (not heap->Empty() and heap->Size() == topk_u)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ std::numeric_limits<InnerIdType>::max  [L70] if_statement@68 (param.search_mode == KNN_SEARCH) → for_statement@69 j < bucket_size → if_statement@70 (ids[j] == std::numeric_limits<InnerIdType>::max())
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ reasoning_ctx->RecordVisit  [L75] if_statement@68 (param.search_mode == KNN_SEARCH) → for_statement@69 j < bucket_size → if_statement@74 (reasoning_ctx != nullptr)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ param.distance_threshold.has_value  [L77] if_statement@68 (param.search_mode == KNN_SEARCH) → for_statement@69 j < bucket_size → if_statement@77 (param.distance_threshold.has_value() and (not std::isfinite(dist[j]) or (not param.enable_reorder and dist[j] > param.distance_threshold.value())))
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ std::isfinite  [L78] if_statement@68 (param.search_mode == KNN_SEARCH) → for_statement@69 j < bucket_size → if_statement@77 (param.distance_threshold.has_value() and (not std::isfinite(dist[j]) or (not param.enable_reorder and dist[j] > param.distance_threshold.value())))
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ param.distance_threshold.value  [L79] if_statement@68 (param.search_mode == KNN_SEARCH) → for_statement@69 j < bucket_size → if_statement@77 (param.distance_threshold.has_value() and (not std::isfinite(dist[j]) or (not param.enable_reorder and dist[j] > param.distance_threshold.value())))
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ attr_ft->CheckValid  [L82] if_statement@68 (param.search_mode == KNN_SEARCH) → for_statement@69 j < bucket_size → if_statement@82 (attr_ft != nullptr and not attr_ft->CheckValid(j))
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ reasoning_ctx->RecordFilterReject  [L84] if_statement@68 (param.search_mode == KNN_SEARCH) → for_statement@69 j < bucket_size → if_statement@82 (attr_ft != nullptr and not attr_ft->CheckValid(j)) → if_statement@83 (reasoning_ctx != nullptr)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ ft->CheckValid  [L88] if_statement@68 (param.search_mode == KNN_SEARCH) → for_statement@69 j < bucket_size → if_statement@88 (ft == nullptr or ft->CheckValid(origin_id))
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ heap->Size  [L89] if_statement@68 (param.search_mode == KNN_SEARCH) → for_statement@69 j < bucket_size → if_statement@88 (ft == nullptr or ft->CheckValid(origin_id)) → if_statement@89 (heap->Size() < topk_u or dist[j] < cur_heap_top)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ heap->Push  [L90] if_statement@68 (param.search_mode == KNN_SEARCH) → for_statement@69 j < bucket_size → if_statement@88 (ft == nullptr or ft->CheckValid(origin_id)) → if_statement@89 (heap->Size() < topk_u or dist[j] < cur_heap_top)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ heap->Size  [L92] if_statement@68 (param.search_mode == KNN_SEARCH) → for_statement@69 j < bucket_size → if_statement@88 (ft == nullptr or ft->CheckValid(origin_id)) → while_statement@92 (heap->Size() > topk_u)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ reasoning_ctx->RecordEviction  [L94] if_statement@68 (param.search_mode == KNN_SEARCH) → for_statement@69 j < bucket_size → if_statement@88 (ft == nullptr or ft->CheckValid(origin_id)) → while_statement@92 (heap->Size() > topk_u) → if_statement@93 (reasoning_ctx != nullptr)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ heap->Top  [L94] if_statement@68 (param.search_mode == KNN_SEARCH) → for_statement@69 j < bucket_size → if_statement@88 (ft == nullptr or ft->CheckValid(origin_id)) → while_statement@92 (heap->Size() > topk_u) → if_statement@93 (reasoning_ctx != nullptr)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ heap->Pop  [L96] if_statement@68 (param.search_mode == KNN_SEARCH) → for_statement@69 j < bucket_size → if_statement@88 (ft == nullptr or ft->CheckValid(origin_id)) → while_statement@92 (heap->Size() > topk_u)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ heap->Empty  [L98] if_statement@68 (param.search_mode == KNN_SEARCH) → for_statement@69 j < bucket_size → if_statement@88 (ft == nullptr or ft->CheckValid(origin_id)) → if_statement@98 (not heap->Empty() and heap->Size() == topk_u)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ heap->Size  [L98] if_statement@68 (param.search_mode == KNN_SEARCH) → for_statement@69 j < bucket_size → if_statement@88 (ft == nullptr or ft->CheckValid(origin_id)) → if_statement@98 (not heap->Empty() and heap->Size() == topk_u)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ heap->Top  [L99] if_statement@68 (param.search_mode == KNN_SEARCH) → for_statement@69 j < bucket_size → if_statement@88 (ft == nullptr or ft->CheckValid(origin_id)) → if_statement@98 (not heap->Empty() and heap->Size() == topk_u)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ reasoning_ctx->RecordFilterReject  [L102] if_statement@68 (param.search_mode == KNN_SEARCH) → for_statement@69 j < bucket_size → if_statement@88 (ft == nullptr or ft->CheckValid(origin_id)) [else 分支] → if_statement@101 (reasoning_ctx != nullptr)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ std::numeric_limits<InnerIdType>::max  [L107] if_statement@68 (param.search_mode == KNN_SEARCH) [else 分支] → for_statement@106 j < bucket_size → if_statement@107 (ids[j] == std::numeric_limits<InnerIdType>::max())
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ reasoning_ctx->RecordVisit  [L112] if_statement@68 (param.search_mode == KNN_SEARCH) [else 分支] → for_statement@106 j < bucket_size → if_statement@111 (reasoning_ctx != nullptr)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ attr_ft->CheckValid  [L114] if_statement@68 (param.search_mode == KNN_SEARCH) [else 分支] → for_statement@106 j < bucket_size → if_statement@114 (attr_ft != nullptr and not attr_ft->CheckValid(j))
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ reasoning_ctx->RecordFilterReject  [L116] if_statement@68 (param.search_mode == KNN_SEARCH) [else 分支] → for_statement@106 j < bucket_size → if_statement@114 (attr_ft != nullptr and not attr_ft->CheckValid(j)) → if_statement@115 (reasoning_ctx != nullptr)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ ft->CheckValid  [L120] if_statement@68 (param.search_mode == KNN_SEARCH) [else 分支] → for_statement@106 j < bucket_size → if_statement@120 (ft == nullptr or ft->CheckValid(origin_id))
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ heap->Push  [L122] if_statement@68 (param.search_mode == KNN_SEARCH) [else 分支] → for_statement@106 j < bucket_size → if_statement@120 (ft == nullptr or ft->CheckValid(origin_id)) → if_statement@121 (dist[j] <= param.radius + THRESHOLD_ERROR and dist[j] < cur_heap_top)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ heap->Size  [L124] if_statement@68 (param.search_mode == KNN_SEARCH) [else 分支] → for_statement@106 j < bucket_size → if_statement@120 (ft == nullptr or ft->CheckValid(origin_id)) → while_statement@124 (heap->Size() > topk_u)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ reasoning_ctx->RecordEviction  [L126] if_statement@68 (param.search_mode == KNN_SEARCH) [else 分支] → for_statement@106 j < bucket_size → if_statement@120 (ft == nullptr or ft->CheckValid(origin_id)) → while_statement@124 (heap->Size() > topk_u) → if_statement@125 (reasoning_ctx != nullptr)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ heap->Top  [L126] if_statement@68 (param.search_mode == KNN_SEARCH) [else 分支] → for_statement@106 j < bucket_size → if_statement@120 (ft == nullptr or ft->CheckValid(origin_id)) → while_statement@124 (heap->Size() > topk_u) → if_statement@125 (reasoning_ctx != nullptr)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ heap->Pop  [L128] if_statement@68 (param.search_mode == KNN_SEARCH) [else 分支] → for_statement@106 j < bucket_size → if_statement@120 (ft == nullptr or ft->CheckValid(origin_id)) → while_statement@124 (heap->Size() > topk_u)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ heap->Empty  [L130] if_statement@68 (param.search_mode == KNN_SEARCH) [else 分支] → for_statement@106 j < bucket_size → if_statement@120 (ft == nullptr or ft->CheckValid(origin_id)) → if_statement@130 (not heap->Empty() and heap->Size() == topk_u)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ heap->Size  [L130] if_statement@68 (param.search_mode == KNN_SEARCH) [else 分支] → for_statement@106 j < bucket_size → if_statement@120 (ft == nullptr or ft->CheckValid(origin_id)) → if_statement@130 (not heap->Empty() and heap->Size() == topk_u)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ heap->Top  [L131] if_statement@68 (param.search_mode == KNN_SEARCH) [else 分支] → for_statement@106 j < bucket_size → if_statement@120 (ft == nullptr or ft->CheckValid(origin_id)) → if_statement@130 (not heap->Empty() and heap->Size() == topk_u)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ reasoning_ctx->RecordFilterReject  [L134] if_statement@68 (param.search_mode == KNN_SEARCH) [else 分支] → for_statement@106 j < bucket_size → if_statement@120 (ft == nullptr or ft->CheckValid(origin_id)) [else 分支] → if_statement@133 (reasoning_ctx != nullptr)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
```

## IVF::reorder

[完整函数与全部调用点](function_reference/ivf_search.md#L183)

```text
#1 IVF::reorder [src/algorithm/ivf/ivf_search.cpp:183]
  ├─ reorder_->Reorder  [L192] 函数本体；短路求值/提前返回见源码
  │  ├─ 以下为分派/重载候选，并非全部依次执行
  │  #2 BucketReorder::Reorder [src/impl/reorder/bucket_reorder.cpp:28]
  │    ├─ VsagException  [L37] if_statement@36 (iter_ctx != nullptr)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ VsagException  [L41] if_statement@40 (rabitq_lower_bound_candidates != nullptr)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ select_query_allocator  [L45] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ input->Size  [L46] conditional_expression@46 input == nullptr
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ std::min  [L47] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ std::make_shared<StandardHeap<true, false>>  [L48] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ ctx.stats->reorder_distance_count.fetch_add  [L54] if_statement@53 (ctx.stats != nullptr)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ bucket_->FactoryComputer  [L58] 函数本体；短路求值/提前返回见源码
  │    │  #3 BucketDataCell<QuantTmpl, IOTmpl>::FactoryComputer [src/datacell/bucket_datacell.h:566]
  │    │    ├─ this->quantizer_->FactoryComputer  [L569] 函数本体；短路求值/提前返回见源码
  │    │    │  #4 Quantizer::FactoryComputer [src/quantization/quantizer.h:179]
  │    │    │    ├─ std::make_shared<Computer<QuantT>>  [L181] 函数本体；短路求值/提前返回见源码
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ std::static_pointer_cast<Computer<QuantTmpl>>  [L570] 函数本体；短路求值/提前返回见源码
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ comp->raw_query_.resize  [L572] if_statement@571 (use_residual_)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ this->quantizer_->GetDim  [L572] if_statement@571 (use_residual_)
  │    │    │  #5 Quantizer::GetDim [src/quantization/quantizer.h:340]
  │    │    ├─ Normalize  [L574] if_statement@571 (use_residual_) → if_statement@573 (metric_ == MetricType::METRIC_TYPE_COSINE)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ comp->raw_query_.data  [L574] if_statement@571 (use_residual_) → if_statement@573 (metric_ == MetricType::METRIC_TYPE_COSINE)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ this->quantizer_->GetDim  [L574] if_statement@571 (use_residual_) → if_statement@573 (metric_ == MetricType::METRIC_TYPE_COSINE)
  │    │    │  ↳ 复用节点 #5 Quantizer::GetDim（本树前文已展开）
  │    │    ├─ memcpy  [L576] if_statement@571 (use_residual_) → if_statement@573 (metric_ == MetricType::METRIC_TYPE_COSINE) [else 分支]
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ comp->raw_query_.data  [L577] if_statement@571 (use_residual_) → if_statement@573 (metric_ == MetricType::METRIC_TYPE_COSINE) [else 分支]
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ this->quantizer_->GetDim  [L577] if_statement@571 (use_residual_) → if_statement@573 (metric_ == MetricType::METRIC_TYPE_COSINE) [else 分支]
  │    │    │  ↳ 复用节点 #5 Quantizer::GetDim（本树前文已展开）
  │    │    ├─ comp->raw_query_.data  [L579] if_statement@571 (use_residual_)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ comp->SetQuery  [L581] 函数本体；短路求值/提前返回见源码
  │    │    │  ├─ 以下为分派/重载候选，并非全部依次执行
  │    │    │  #6 Computer::SetQuery [src/quantization/computer.h:48]
  │    │    │    ├─ quantizer_->ProcessQuery  [L50] 函数本体；短路求值/提前返回见源码
  │    │    │    │  #7 Quantizer::ProcessQuery [src/quantization/quantizer.h:184]
  │    │    │    │    ├─ cast().ProcessQueryImpl  [L186] 函数本体；短路求值/提前返回见源码
  │    │    │    │    │  #8 FP32Quantizer<metric>::ProcessQueryImpl [src/quantization/fp32_quantizer.cpp:144]
  │    │    │    │    │    ├─ this->allocator_->Allocate  [L150] if_statement@148 (computer.buf_ == nullptr)
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ VsagException  [L154] catch_clause@152
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ Normalize  [L157] if_statement@156 (metric == MetricType::METRIC_TYPE_COSINE)
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    ├─ memcpy  [L159] if_statement@156 (metric == MetricType::METRIC_TYPE_COSINE) [else 分支]
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ cast  [L186] 函数本体；短路求值/提前返回见源码
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │  #9 Computer<TransformQuantizer<QuantImpl, metric>>::SetQuery [src/quantization/computer.h:122]
  │    │    │    ├─ quantizer_->ProcessQuery  [L124] 函数本体；短路求值/提前返回见源码
  │    │    │    │  ↳ 复用节点 #7 Quantizer::ProcessQuery（本树前文已展开）
  │    ├─ input->GetData  [L59] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ location_resolver_  [L64] for_statement@63 i < candidate_count
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ bucket_->Query  [L68] 函数本体；短路求值/提前返回见源码
  │    │  #10 BucketDataCell::Query [src/datacell/bucket_datacell.h:82]
  │    │    ├─ GetQuantizerName  [L89] if_statement@89 (id_count > 0 and GetQuantizerName() == QUANTIZATION_TYPE_VALUE_PQFS)
  │    │    │  #11 BucketDataCell::GetQuantizerName [src/datacell/bucket_datacell.h:170]
  │    │    │    ├─ this->quantizer_->Name  [L172] 函数本体；短路求值/提前返回见源码
  │    │    │    │  #12 Quantizer::Name [src/quantization/quantizer.h:300]
  │    │    │    │    ├─ cast().NameImpl  [L302] 函数本体；短路求值/提前返回见源码
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    ├─ cast  [L302] 函数本体；短路求值/提前返回见源码
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ VsagException  [L90] if_statement@89 (id_count > 0 and GetQuantizerName() == QUANTIZATION_TYPE_VALUE_PQFS)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ computer.get  [L94] 函数本体；短路求值/提前返回见源码
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    ├─ this->query  [L95] 函数本体；短路求值/提前返回见源码
  │    │    │  #13 BucketDataCell<QuantTmpl, IOTmpl>::query [src/datacell/bucket_datacell.h:380]
  │    │    │    ├─ select_query_allocator  [L397] 函数本体；短路求值/提前返回见源码
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ requests.reserve  [L399] 函数本体；短路求值/提前返回见源码
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ check_valid_bucket_id  [L401] for_statement@400 i < id_count
  │    │    │    │  #14 BucketDataCell::check_valid_bucket_id [src/datacell/bucket_datacell.h:244]
  │    │    │    │    ├─ VsagException  [L247] if_statement@246 (bucket_id >= this->bucket_count_ or bucket_id < 0)
  │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ requests.emplace_back  [L402] for_statement@400 i < id_count
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ std::sort  [L404] 函数本体；短路求值/提前返回见源码
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ requests.begin  [L404] 函数本体；短路求值/提前返回见源码
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ requests.end  [L404] 函数本体；短路求值/提前返回见源码
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ unique_offsets.reserve  [L419] 函数本体；短路求值/提前返回见源码
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ read_sizes.reserve  [L420] 函数本体；短路求值/提前返回见源码
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ read_offsets.reserve  [L421] 函数本体；短路求值/提前返回见源码
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ requests.size  [L425] while_statement@425 (group_begin < requests.size())
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ requests.size  [L428] while_statement@425 (group_begin < requests.size()) → while_statement@428 (group_end < requests.size() and requests[group_end].bucket_id == bucket_id)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ VsagException  [L436] while_statement@425 (group_begin < requests.size()) → for_statement@433 i < group_end → if_statement@435 (offset_id >= this->bucket_sizes_[bucket_id])
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ VsagException  [L439] while_statement@425 (group_begin < requests.size()) → for_statement@433 i < group_end → if_statement@438 (this->inner_ids_[bucket_id][offset_id] == EMPTY_INNER_ID)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ fmt::format  [L441] while_statement@425 (group_begin < requests.size()) → for_statement@433 i < group_end → if_statement@438 (this->inner_ids_[bucket_id][offset_id] == EMPTY_INNER_ID)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ unique_offsets.clear  [L447] while_statement@425 (group_begin < requests.size())
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ unique_offsets.empty  [L450] while_statement@425 (group_begin < requests.size()) → for_statement@448 i < group_end → if_statement@450 (unique_offsets.empty() or unique_offsets.back() != offset_id)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ unique_offsets.back  [L450] while_statement@425 (group_begin < requests.size()) → for_statement@448 i < group_end → if_statement@450 (unique_offsets.empty() or unique_offsets.back() != offset_id)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ unique_offsets.emplace_back  [L451] while_statement@425 (group_begin < requests.size()) → for_statement@448 i < group_end → if_statement@450 (unique_offsets.empty() or unique_offsets.back() != offset_id)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ read_sizes.clear  [L455] while_statement@425 (group_begin < requests.size())
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ read_offsets.clear  [L456] while_statement@425 (group_begin < requests.size())
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ read_offsets.empty  [L458] while_statement@425 (group_begin < requests.size()) → for_range_loop@457 → if_statement@458 (not read_offsets.empty() and read_offsets.back() + read_sizes.back() == static_cast<uint64_t>(offset_id) * code_size_ and code_size_ <= static_cast<uint64_t>(std::numeric_limits<int32_t>::max()) and read_sizes.back() <= static_cast<uint64_t>(std::numeric_limits<int32_t>::max()) - code_size_)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ read_offsets.back  [L459] while_statement@425 (group_begin < requests.size()) → for_range_loop@457 → if_statement@458 (not read_offsets.empty() and read_offsets.back() + read_sizes.back() == static_cast<uint64_t>(offset_id) * code_size_ and code_size_ <= static_cast<uint64_t>(std::numeric_limits<int32_t>::max()) and read_sizes.back() <= static_cast<uint64_t>(std::numeric_limits<int32_t>::max()) - code_size_)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ read_sizes.back  [L459] while_statement@425 (group_begin < requests.size()) → for_range_loop@457 → if_statement@458 (not read_offsets.empty() and read_offsets.back() + read_sizes.back() == static_cast<uint64_t>(offset_id) * code_size_ and code_size_ <= static_cast<uint64_t>(std::numeric_limits<int32_t>::max()) and read_sizes.back() <= static_cast<uint64_t>(std::numeric_limits<int32_t>::max()) - code_size_)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ std::numeric_limits<int32_t>::max  [L461] while_statement@425 (group_begin < requests.size()) → for_range_loop@457 → if_statement@458 (not read_offsets.empty() and read_offsets.back() + read_sizes.back() == static_cast<uint64_t>(offset_id) * code_size_ and code_size_ <= static_cast<uint64_t>(std::numeric_limits<int32_t>::max()) and read_sizes.back() <= static_cast<uint64_t>(std::numeric_limits<int32_t>::max()) - code_size_)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ read_sizes.back  [L462] while_statement@425 (group_begin < requests.size()) → for_range_loop@457 → if_statement@458 (not read_offsets.empty() and read_offsets.back() + read_sizes.back() == static_cast<uint64_t>(offset_id) * code_size_ and code_size_ <= static_cast<uint64_t>(std::numeric_limits<int32_t>::max()) and read_sizes.back() <= static_cast<uint64_t>(std::numeric_limits<int32_t>::max()) - code_size_)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ std::numeric_limits<int32_t>::max  [L463] while_statement@425 (group_begin < requests.size()) → for_range_loop@457 → if_statement@458 (not read_offsets.empty() and read_offsets.back() + read_sizes.back() == static_cast<uint64_t>(offset_id) * code_size_ and code_size_ <= static_cast<uint64_t>(std::numeric_limits<int32_t>::max()) and read_sizes.back() <= static_cast<uint64_t>(std::numeric_limits<int32_t>::max()) - code_size_)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ read_sizes.back  [L464] while_statement@425 (group_begin < requests.size()) → for_range_loop@457 → if_statement@458 (not read_offsets.empty() and read_offsets.back() + read_sizes.back() == static_cast<uint64_t>(offset_id) * code_size_ and code_size_ <= static_cast<uint64_t>(std::numeric_limits<int32_t>::max()) and read_sizes.back() <= static_cast<uint64_t>(std::numeric_limits<int32_t>::max()) - code_size_)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ read_sizes.emplace_back  [L466] while_statement@425 (group_begin < requests.size()) → for_range_loop@457 → if_statement@458 (not read_offsets.empty() and read_offsets.back() + read_sizes.back() == static_cast<uint64_t>(offset_id) * code_size_ and code_size_ <= static_cast<uint64_t>(std::numeric_limits<int32_t>::max()) and read_sizes.back() <= static_cast<uint64_t>(std::numeric_limits<int32_t>::max()) - code_size_) [else 分支]
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ read_offsets.emplace_back  [L467] while_statement@425 (group_begin < requests.size()) → for_range_loop@457 → if_statement@458 (not read_offsets.empty() and read_offsets.back() + read_sizes.back() == static_cast<uint64_t>(offset_id) * code_size_ and code_size_ <= static_cast<uint64_t>(std::numeric_limits<int32_t>::max()) and read_sizes.back() <= static_cast<uint64_t>(std::numeric_limits<int32_t>::max()) - code_size_) [else 分支]
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ this->datas_[bucket_id].MultiRead  [L475] while_statement@425 (group_begin < requests.size())
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ read_sizes.data  [L476] while_statement@425 (group_begin < requests.size())
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ read_offsets.data  [L476] while_statement@425 (group_begin < requests.size())
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ read_sizes.size  [L476] while_statement@425 (group_begin < requests.size())
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ VsagException  [L479] while_statement@425 (group_begin < requests.size()) → if_statement@478 (not read_success)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ read_sizes.size  [L481] while_statement@425 (group_begin < requests.size())
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ computer->ScanBatchDists  [L484] while_statement@425 (group_begin < requests.size())
  │    │    │    │  ├─ 以下为分派/重载候选，并非全部依次执行
  │    │    │    │  #15 Computer::ScanBatchDists [src/quantization/computer.h:68]
  │    │    │    │    ├─ quantizer_->ScanBatchDists  [L70] 函数本体；短路求值/提前返回见源码
  │    │    │    │    │  #16 Quantizer::ScanBatchDists [src/quantization/quantizer.h:230]
  │    │    │    │    │    ├─ cast().ScanBatchDistImpl  [L235] 函数本体；短路求值/提前返回见源码
  │    │    │    │    │    │  ├─ 以下为分派/重载候选，并非全部依次执行
  │    │    │    │    │    │  #17 Quantizer::ScanBatchDistImpl [src/quantization/quantizer.h:290]
  │    │    │    │    │    │    ├─ cast().ComputeDistImpl  [L296] for_statement@295 i < count
  │    │    │    │    │    │    │  #18 FP32Quantizer<metric>::ComputeDistImpl [src/quantization/fp32_quantizer.cpp:164]
  │    │    │    │    │    │    │    ├─ FP32ComputeIP  [L169] if_statement@168 (metric == MetricType::METRIC_TYPE_IP)
  │    │    │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    │    │    ├─ FP32ComputeIP  [L173] if_statement@168 (metric == MetricType::METRIC_TYPE_IP) [else 分支] → if_statement@172 (metric == MetricType::METRIC_TYPE_COSINE)
  │    │    │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    │    │    ├─ FP32ComputeL2Sqr  [L182] if_statement@168 (metric == MetricType::METRIC_TYPE_IP) [else 分支] → if_statement@172 (metric == MetricType::METRIC_TYPE_COSINE) [else 分支] → if_statement@181 (metric == MetricType::METRIC_TYPE_L2SQR)
  │    │    │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    │    ├─ cast  [L296] for_statement@295 i < count
  │    │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │    │    │  #19 FP32Quantizer<metric>::ScanBatchDistImpl [src/quantization/fp32_quantizer.cpp:132]
  │    │    │    │    │    │    ├─ this->ComputeDistImpl  [L139] for_statement@138 i < count
  │    │    │    │    │    │    │  ↳ 复用节点 #18 FP32Quantizer<metric>::ComputeDistImpl（本树前文已展开）
  │    │    │    │    │    ├─ cast  [L235] 函数本体；短路求值/提前返回见源码
  │    │    │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    │  #20 Computer<TransformQuantizer<QuantImpl, metric>>::ScanBatchDists [src/quantization/computer.h:142]
  │    │    │    │    ├─ quantizer_->ScanBatchDists  [L144] 函数本体；短路求值/提前返回见源码
  │    │    │    │    │  ↳ 复用节点 #16 Quantizer::ScanBatchDists（本树前文已展开）
  │    │    │    ├─ unique_offsets.size  [L484] while_statement@425 (group_begin < requests.size())
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ unique_dists.data  [L484] while_statement@425 (group_begin < requests.size())
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ this->quantizer_->GetDim  [L486] while_statement@425 (group_begin < requests.size()) → if_statement@485 (use_residual_)
  │    │    │    │  ↳ 复用节点 #5 Quantizer::GetDim（本树前文已展开）
  │    │    │    ├─ strategy_->GetCentroid  [L487] while_statement@425 (group_begin < requests.size()) → if_statement@485 (use_residual_)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ FP32ComputeIP  [L488] while_statement@425 (group_begin < requests.size()) → if_statement@485 (use_residual_)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ computer->raw_query_.data  [L489] while_statement@425 (group_begin < requests.size()) → if_statement@485 (use_residual_)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ centroid.data  [L489] while_statement@425 (group_begin < requests.size()) → if_statement@485 (use_residual_)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ this->quantizer_->GetDim  [L489] while_statement@425 (group_begin < requests.size()) → if_statement@485 (use_residual_)
  │    │    │    │  ↳ 复用节点 #5 Quantizer::GetDim（本树前文已展开）
  │    │    │    ├─ unique_offsets.size  [L492] while_statement@425 (group_begin < requests.size()) → if_statement@485 (use_residual_) → if_statement@490 (metric_ == MetricType::METRIC_TYPE_L2SQR) → for_statement@492 i < unique_offsets.size()
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ unique_offsets.size  [L496] while_statement@425 (group_begin < requests.size()) → if_statement@485 (use_residual_) → for_statement@496 i < unique_offsets.size()
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ ctx->stats->io_cnt.fetch_add  [L513] if_statement@511 (not IOTmpl::InMemory) → if_statement@512 (ctx != nullptr and ctx->stats != nullptr)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    │    │    ├─ ctx->stats->io_time_ms.fetch_add  [L515] if_statement@511 (not IOTmpl::InMemory) → if_statement@512 (ctx != nullptr and ctx->stats != nullptr)
  │    │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ precise_distances.data  [L68] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ bucket_ids.data  [L70] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ offset_ids.data  [L71] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ ctx.reasoning_ctx->RecordReorder  [L78] for_statement@74 i < candidate_count → if_statement@77 (ctx.reasoning_ctx != nullptr)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ distance_threshold.has_value  [L80] for_statement@74 i < candidate_count → if_statement@80 (distance_threshold.has_value() and (not std::isfinite(precise_distance) or precise_distance > distance_threshold.value()))
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ std::isfinite  [L80] for_statement@74 i < candidate_count → if_statement@80 (distance_threshold.has_value() and (not std::isfinite(precise_distance) or precise_distance > distance_threshold.value()))
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ distance_threshold.value  [L81] for_statement@74 i < candidate_count → if_statement@80 (distance_threshold.has_value() and (not std::isfinite(precise_distance) or precise_distance > distance_threshold.value()))
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ reorder_heap->Size  [L84] for_statement@74 i < candidate_count → if_statement@84 (reorder_heap->Size() < topk or precise_distance < reorder_heap->Top().first)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ reorder_heap->Top  [L84] for_statement@74 i < candidate_count → if_statement@84 (reorder_heap->Size() < topk or precise_distance < reorder_heap->Top().first)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ reorder_heap->Push  [L85] for_statement@74 i < candidate_count → if_statement@84 (reorder_heap->Size() < topk or precise_distance < reorder_heap->Top().first)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ reorder_heap->Size  [L86] for_statement@74 i < candidate_count → if_statement@84 (reorder_heap->Size() < topk or precise_distance < reorder_heap->Top().first) → if_statement@86 (reorder_heap->Size() > topk)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ ctx.reasoning_ctx->RecordReorderEviction  [L88] for_statement@74 i < candidate_count → if_statement@84 (reorder_heap->Size() < topk or precise_distance < reorder_heap->Top().first) → if_statement@86 (reorder_heap->Size() > topk) → if_statement@87 (ctx.reasoning_ctx != nullptr)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ reorder_heap->Top  [L88] for_statement@74 i < candidate_count → if_statement@84 (reorder_heap->Size() < topk or precise_distance < reorder_heap->Top().first) → if_statement@86 (reorder_heap->Size() > topk) → if_statement@87 (ctx.reasoning_ctx != nullptr)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ reorder_heap->Pop  [L90] for_statement@74 i < candidate_count → if_statement@84 (reorder_heap->Size() < topk or precise_distance < reorder_heap->Top().first) → if_statement@86 (reorder_heap->Size() > topk)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │  #21 FlattenReorder::Reorder [src/impl/reorder/flatten_reorder.cpp:156]
  │    ├─ select_query_allocator  [L165] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ distance_threshold.has_value  [L167] lambda@166（定义体，执行时间取决于调用/调度）
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ IsFiniteRaBitQValue  [L168] lambda@166（定义体，执行时间取决于调用/调度）
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ distance_threshold.value  [L168] lambda@166（定义体，执行时间取决于调用/调度）
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ is_distance_eligible  [L171] lambda@170（定义体，执行时间取决于调用/调度） → if_statement@171 (is_distance_eligible(distance))
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ iter_ctx->SetPoint  [L175] lambda@170（定义体，执行时间取决于调用/调度） → if_statement@174 (iter_ctx != nullptr)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ input->Size  [L179] conditional_expression@179 input == nullptr
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ add_reorder_candidate_count  [L181] if_statement@180 (rabitq_lower_bound_candidates == nullptr)
  │    │  #22 add_reorder_candidate_count [src/impl/reorder/flatten_reorder.cpp:138]
  │    │    ├─ ctx.stats->reorder_candidate_count.fetch_add  [L141] if_statement@140 (ctx.stats != nullptr)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ std::min  [L182] if_statement@180 (rabitq_lower_bound_candidates == nullptr)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ std::make_shared<StandardHeap<true, false>>  [L183] if_statement@180 (rabitq_lower_bound_candidates == nullptr)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ AcquireQueryComputer  [L184] if_statement@180 (rabitq_lower_bound_candidates == nullptr)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ input->GetData  [L188] if_statement@180 (rabitq_lower_bound_candidates == nullptr) → conditional_expression@188 input == nullptr
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ add_reorder_distance_count  [L192] if_statement@180 (rabitq_lower_bound_candidates == nullptr)
  │    │  #23 add_reorder_distance_count [src/impl/reorder/flatten_reorder.cpp:130]
  │    │    ├─ ctx.stats->reorder_distance_count.fetch_add  [L133] if_statement@132 (ctx.stats != nullptr)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ flatten_->Query  [L195] if_statement@180 (rabitq_lower_bound_candidates == nullptr)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ dists.data  [L195] if_statement@180 (rabitq_lower_bound_candidates == nullptr)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ ids.data  [L195] if_statement@180 (rabitq_lower_bound_candidates == nullptr)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ ctx.reasoning_ctx->RecordReorder  [L199] if_statement@180 (rabitq_lower_bound_candidates == nullptr) → for_statement@197 i < heap_candidate_size → if_statement@198 (ctx.reasoning_ctx != nullptr)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ consume_if_ineligible  [L202] if_statement@180 (rabitq_lower_bound_candidates == nullptr) → for_statement@197 i < heap_candidate_size → if_statement@202 (consume_if_ineligible(dists[i], candidate_result[i].second))
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ reorder_heap->Size  [L205] if_statement@180 (rabitq_lower_bound_candidates == nullptr) → for_statement@197 i < heap_candidate_size → if_statement@205 (reorder_heap->Size() < topk || dists[i] < reorder_heap->Top().first)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ reorder_heap->Top  [L205] if_statement@180 (rabitq_lower_bound_candidates == nullptr) → for_statement@197 i < heap_candidate_size → if_statement@205 (reorder_heap->Size() < topk || dists[i] < reorder_heap->Top().first)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ reorder_heap->Push  [L206] if_statement@180 (rabitq_lower_bound_candidates == nullptr) → for_statement@197 i < heap_candidate_size → if_statement@205 (reorder_heap->Size() < topk || dists[i] < reorder_heap->Top().first)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ reorder_heap->Size  [L207] if_statement@180 (rabitq_lower_bound_candidates == nullptr) → for_statement@197 i < heap_candidate_size → if_statement@205 (reorder_heap->Size() < topk || dists[i] < reorder_heap->Top().first) → if_statement@207 (reorder_heap->Size() > topk)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ reorder_heap->Top  [L209] if_statement@180 (rabitq_lower_bound_candidates == nullptr) → for_statement@197 i < heap_candidate_size → if_statement@205 (reorder_heap->Size() < topk || dists[i] < reorder_heap->Top().first) → if_statement@207 (reorder_heap->Size() > topk) → if_statement@208 (iter_ctx != nullptr)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ iter_ctx->AddDiscardNode  [L210] if_statement@180 (rabitq_lower_bound_candidates == nullptr) → for_statement@197 i < heap_candidate_size → if_statement@205 (reorder_heap->Size() < topk || dists[i] < reorder_heap->Top().first) → if_statement@207 (reorder_heap->Size() > topk) → if_statement@208 (iter_ctx != nullptr)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ ctx.reasoning_ctx->RecordReorderEviction  [L213] if_statement@180 (rabitq_lower_bound_candidates == nullptr) → for_statement@197 i < heap_candidate_size → if_statement@205 (reorder_heap->Size() < topk || dists[i] < reorder_heap->Top().first) → if_statement@207 (reorder_heap->Size() > topk) → if_statement@212 (ctx.reasoning_ctx != nullptr)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ reorder_heap->Top  [L213] if_statement@180 (rabitq_lower_bound_candidates == nullptr) → for_statement@197 i < heap_candidate_size → if_statement@205 (reorder_heap->Size() < topk || dists[i] < reorder_heap->Top().first) → if_statement@207 (reorder_heap->Size() > topk) → if_statement@212 (ctx.reasoning_ctx != nullptr)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ reorder_heap->Pop  [L215] if_statement@180 (rabitq_lower_bound_candidates == nullptr) → for_statement@197 i < heap_candidate_size → if_statement@205 (reorder_heap->Size() < topk || dists[i] < reorder_heap->Top().first) → if_statement@207 (reorder_heap->Size() > topk)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ rabitq_lower_bound_candidates->size  [L223] conditional_expression@223 rabitq_lower_bound_candidates == nullptr
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ AcquireQueryComputer  [L228] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ std::make_shared<StandardHeap<true, false>>  [L231] if_statement@230 (topk == 0 || max_candidate_size == 0)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ merged_ids.reserve  [L238] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ input->GetData  [L241] conditional_expression@241 input == nullptr
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ merged_ids.insert  [L244] for_statement@242 i < heap_candidate_size → if_statement@244 (merged_ids.insert(id).second)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ add_reorder_lower_bound_probe_count  [L250] if_statement@249 (heap_unique_size > 0)
  │    │  #24 add_reorder_lower_bound_probe_count [src/impl/reorder/flatten_reorder.cpp:146]
  │    │    ├─ ctx.stats->reorder_lower_bound_probe_count.fetch_add  [L149] if_statement@148 (ctx.stats != nullptr)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ flatten_->QueryWithDistanceLowerBound  [L252] if_statement@249 (heap_unique_size > 0)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ lower_bound_probe_dists.data  [L252] if_statement@249 (heap_unique_size > 0)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ lower_bounds.data  [L253] if_statement@249 (heap_unique_size > 0)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ all_ids.data  [L255] if_statement@249 (heap_unique_size > 0)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ merged_ids.insert  [L262] if_statement@260 (rabitq_lower_bound_candidates != nullptr) → for_range_loop@261 → if_statement@262 (merged_ids.insert(item.second).second)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ add_reorder_candidate_count  [L271] 函数本体；短路求值/提前返回见源码
  │    │  ↳ 复用节点 #22 add_reorder_candidate_count（本树前文已展开）
  │    ├─ std::min  [L273] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ std::make_shared<StandardHeap<true, false>>  [L274] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ IsFiniteRaBitQValue  [L280] lambda@279（定义体，执行时间取决于调用/调度）
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ std::numeric_limits<float>::max  [L280] lambda@279（定义体，执行时间取决于调用/调度）
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ has_valid_lower_bound  [L284] for_statement@283 i < candidate_size → if_statement@284 (not has_valid_lower_bound(lower_bounds[i]))
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ add_reorder_distance_count  [L291] if_statement@290 (not lower_bounds_available)
  │    │  ↳ 复用节点 #23 add_reorder_distance_count（本树前文已展开）
  │    ├─ flatten_->Query  [L294] if_statement@290 (not lower_bounds_available)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ lower_bound_probe_dists.data  [L295] if_statement@290 (not lower_bounds_available)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ all_ids.data  [L295] if_statement@290 (not lower_bounds_available)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ ctx.reasoning_ctx->RecordReorder  [L299] if_statement@290 (not lower_bounds_available) → for_statement@297 i < candidate_size → if_statement@298 (ctx.reasoning_ctx != nullptr)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ consume_if_ineligible  [L302] if_statement@290 (not lower_bounds_available) → for_statement@297 i < candidate_size → if_statement@302 (consume_if_ineligible(lower_bound_probe_dists[i], all_ids[i]))
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ reorder_heap->Size  [L305] if_statement@290 (not lower_bounds_available) → for_statement@297 i < candidate_size → if_statement@305 (reorder_heap->Size() < topk or lower_bound_probe_dists[i] < reorder_heap->Top().first)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ reorder_heap->Top  [L306] if_statement@290 (not lower_bounds_available) → for_statement@297 i < candidate_size → if_statement@305 (reorder_heap->Size() < topk or lower_bound_probe_dists[i] < reorder_heap->Top().first)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ reorder_heap->Push  [L307] if_statement@290 (not lower_bounds_available) → for_statement@297 i < candidate_size → if_statement@305 (reorder_heap->Size() < topk or lower_bound_probe_dists[i] < reorder_heap->Top().first)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ reorder_heap->Size  [L308] if_statement@290 (not lower_bounds_available) → for_statement@297 i < candidate_size → if_statement@305 (reorder_heap->Size() < topk or lower_bound_probe_dists[i] < reorder_heap->Top().first) → if_statement@308 (reorder_heap->Size() > topk)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ reorder_heap->Top  [L310] if_statement@290 (not lower_bounds_available) → for_statement@297 i < candidate_size → if_statement@305 (reorder_heap->Size() < topk or lower_bound_probe_dists[i] < reorder_heap->Top().first) → if_statement@308 (reorder_heap->Size() > topk) → if_statement@309 (iter_ctx != nullptr)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ iter_ctx->AddDiscardNode  [L311] if_statement@290 (not lower_bounds_available) → for_statement@297 i < candidate_size → if_statement@305 (reorder_heap->Size() < topk or lower_bound_probe_dists[i] < reorder_heap->Top().first) → if_statement@308 (reorder_heap->Size() > topk) → if_statement@309 (iter_ctx != nullptr)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ ctx.reasoning_ctx->RecordReorderEviction  [L314] if_statement@290 (not lower_bounds_available) → for_statement@297 i < candidate_size → if_statement@305 (reorder_heap->Size() < topk or lower_bound_probe_dists[i] < reorder_heap->Top().first) → if_statement@308 (reorder_heap->Size() > topk) → if_statement@313 (ctx.reasoning_ctx != nullptr)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ reorder_heap->Top  [L314] if_statement@290 (not lower_bounds_available) → for_statement@297 i < candidate_size → if_statement@305 (reorder_heap->Size() < topk or lower_bound_probe_dists[i] < reorder_heap->Top().first) → if_statement@308 (reorder_heap->Size() > topk) → if_statement@313 (ctx.reasoning_ctx != nullptr)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ reorder_heap->Pop  [L316] if_statement@290 (not lower_bounds_available) → for_statement@297 i < candidate_size → if_statement@305 (reorder_heap->Size() < topk or lower_bound_probe_dists[i] < reorder_heap->Top().first) → if_statement@308 (reorder_heap->Size() > topk)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ std::iota  [L324] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ order.begin  [L324] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ order.end  [L324] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ std::sort  [L325] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ order.begin  [L325] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ order.end  [L325] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ std::min<uint64_t>  [L329] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ std::max<uint64_t>  [L331] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ std::numeric_limits<float>::max  [L341] for_statement@337 i < bootstrap_size → conditional_expression@340 idx < heap_unique_size
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ add_reorder_distance_count  [L343] 函数本体；短路求值/提前返回见源码
  │    │  ↳ 复用节点 #23 add_reorder_distance_count（本树前文已展开）
  │    ├─ flatten_->QueryWithDistanceHint  [L346] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ dists.data  [L347] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ hint_dists.data  [L347] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ ids.data  [L347] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ ctx.reasoning_ctx->RecordReorder  [L352] for_statement@349 i < bootstrap_size → if_statement@350 (ctx.reasoning_ctx != nullptr)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ consume_if_ineligible  [L354] for_statement@349 i < bootstrap_size → if_statement@354 (not consume_if_ineligible(dists[i], ids[i]))
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ reorder_heap->Push  [L355] for_statement@349 i < bootstrap_size → if_statement@354 (not consume_if_ineligible(dists[i], ids[i]))
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ reorder_heap->Size  [L361] while_statement@360 (cursor < candidate_size) → if_statement@361 (reorder_heap->Size() == topk && lower_bounds[order[cursor]] >= reorder_heap->Top().first)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ reorder_heap->Top  [L362] while_statement@360 (cursor < candidate_size) → if_statement@361 (reorder_heap->Size() == topk && lower_bounds[order[cursor]] >= reorder_heap->Top().first)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ reorder_heap->Size  [L366] while_statement@360 (cursor < candidate_size) → conditional_expression@366 reorder_heap->Size() == topk
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ reorder_heap->Top  [L367] while_statement@360 (cursor < candidate_size) → conditional_expression@366 reorder_heap->Size() == topk
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ std::numeric_limits<float>::max  [L368] while_statement@360 (cursor < candidate_size) → conditional_expression@366 reorder_heap->Size() == topk
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ std::numeric_limits<float>::max  [L377] while_statement@360 (cursor < candidate_size) → while_statement@370 (cursor < candidate_size && batch_count < batch_size) → conditional_expression@376 idx < heap_unique_size
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ add_reorder_distance_count  [L387] while_statement@360 (cursor < candidate_size)
  │    │  ↳ 复用节点 #23 add_reorder_distance_count（本树前文已展开）
  │    ├─ flatten_->QueryWithDistanceHint  [L390] while_statement@360 (cursor < candidate_size)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ dists.data  [L391] while_statement@360 (cursor < candidate_size)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ hint_dists.data  [L391] while_statement@360 (cursor < candidate_size)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ ids.data  [L391] while_statement@360 (cursor < candidate_size)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ ctx.reasoning_ctx->RecordReorder  [L395] while_statement@360 (cursor < candidate_size) → for_statement@393 i < batch_count → if_statement@394 (ctx.reasoning_ctx != nullptr)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ consume_if_ineligible  [L398] while_statement@360 (cursor < candidate_size) → for_statement@393 i < batch_count → if_statement@398 (consume_if_ineligible(dists[i], ids[i]))
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ reorder_heap->Size  [L401] while_statement@360 (cursor < candidate_size) → for_statement@393 i < batch_count → if_statement@401 (reorder_heap->Size() < topk or dists[i] < reorder_heap->Top().first)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ reorder_heap->Top  [L401] while_statement@360 (cursor < candidate_size) → for_statement@393 i < batch_count → if_statement@401 (reorder_heap->Size() < topk or dists[i] < reorder_heap->Top().first)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ reorder_heap->Push  [L402] while_statement@360 (cursor < candidate_size) → for_statement@393 i < batch_count → if_statement@401 (reorder_heap->Size() < topk or dists[i] < reorder_heap->Top().first)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ reorder_heap->Size  [L403] while_statement@360 (cursor < candidate_size) → for_statement@393 i < batch_count → if_statement@401 (reorder_heap->Size() < topk or dists[i] < reorder_heap->Top().first) → if_statement@403 (reorder_heap->Size() > topk)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ reorder_heap->Top  [L405] while_statement@360 (cursor < candidate_size) → for_statement@393 i < batch_count → if_statement@401 (reorder_heap->Size() < topk or dists[i] < reorder_heap->Top().first) → if_statement@403 (reorder_heap->Size() > topk) → if_statement@404 (iter_ctx != nullptr)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ iter_ctx->AddDiscardNode  [L406] while_statement@360 (cursor < candidate_size) → for_statement@393 i < batch_count → if_statement@401 (reorder_heap->Size() < topk or dists[i] < reorder_heap->Top().first) → if_statement@403 (reorder_heap->Size() > topk) → if_statement@404 (iter_ctx != nullptr)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ ctx.reasoning_ctx->RecordReorderEviction  [L409] while_statement@360 (cursor < candidate_size) → for_statement@393 i < batch_count → if_statement@401 (reorder_heap->Size() < topk or dists[i] < reorder_heap->Top().first) → if_statement@403 (reorder_heap->Size() > topk) → if_statement@408 (ctx.reasoning_ctx != nullptr)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ reorder_heap->Top  [L409] while_statement@360 (cursor < candidate_size) → for_statement@393 i < batch_count → if_statement@401 (reorder_heap->Size() < topk or dists[i] < reorder_heap->Top().first) → if_statement@403 (reorder_heap->Size() > topk) → if_statement@408 (ctx.reasoning_ctx != nullptr)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ reorder_heap->Pop  [L411] while_statement@360 (cursor < candidate_size) → for_statement@393 i < batch_count → if_statement@401 (reorder_heap->Size() < topk or dists[i] < reorder_heap->Top().first) → if_statement@403 (reorder_heap->Size() > topk)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ this->pack_knn_result  [L193] 函数本体；短路求值/提前返回见源码
  │  #25 InnerIndexInterface::pack_knn_result [src/algorithm/inner_index_interface.cpp:1140]
  │    ├─ heap->Empty  [L1142] if_statement@1142 (heap == nullptr || heap->Empty())
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ make_empty_result  [L1143] if_statement@1142 (heap == nullptr || heap->Empty())
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ heap->Size  [L1146] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ create_fast_dataset  [L1147] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ heap->Top  [L1149] for_statement@1148 j >= 0
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ this->label_table_->GetLabelById  [L1150] for_statement@1148 j >= 0
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ heap->Top  [L1150] for_statement@1148 j >= 0
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ heap->Pop  [L1151] for_statement@1148 j >= 0
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ std::move  [L1153] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
```

## IVF::search_with_custom_distance

[完整函数与全部调用点](function_reference/ivf_search.md#L334)

```text
#1 IVF::search_with_custom_distance [src/algorithm/ivf/ivf_search.cpp:334]
  ├─ query->GetFloat32Vectors  [L340] 函数本体；短路求值/提前返回见源码
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ param.bucket_ids.empty  [L342] if_statement@342 (not param.bucket_ids.empty())
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ candidate_buckets.reserve  [L343] if_statement@342 (not param.bucket_ids.empty())
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ param.bucket_ids.size  [L343] if_statement@342 (not param.bucket_ids.empty())
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ candidate_buckets.push_back  [L345] if_statement@342 (not param.bucket_ids.empty()) → for_range_loop@344
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ partition_strategy_->ClassifyDatasForSearch  [L348] if_statement@342 (not param.bucket_ids.empty()) [else 分支]
  │  ├─ 以下为分派/重载候选，并非全部依次执行
  │  #2 GNOIMIPartition::ClassifyDatasForSearch [src/algorithm/ivf/gno_imi_partition.cpp:221]
  │    ├─ norm_vectors.resize  [L228] if_statement@227 (metric_type_ == MetricType::METRIC_TYPE_COSINE)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ Normalize  [L230] if_statement@227 (metric_type_ == MetricType::METRIC_TYPE_COSINE) → for_statement@229 i < count
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ norm_vectors.data  [L231] if_statement@227 (metric_type_ == MetricType::METRIC_TYPE_COSINE) → for_statement@229 i < count
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ norm_vectors.data  [L233] if_statement@227 (metric_type_ == MetricType::METRIC_TYPE_COSINE)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ std::fill  [L237] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ result.begin  [L237] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ result.end  [L237] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ dist_to_s.data  [L243] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ dist_to_t.data  [L244] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ candidate_s_id.data  [L245] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ candidate_s_dist.data  [L246] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ matmul  [L249] 函数本体；短路求值/提前返回见源码
  │    │  #3 matmul [src/algorithm/ivf/gno_imi_partition.cpp:40]
  │    │    ├─ BlasFunction::Sgemm  [L42] 函数本体；短路求值/提前返回见源码
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ data_centroids_s_.data  [L250] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ matmul  [L255] 函数本体；短路求值/提前返回见源码
  │    │  ↳ 复用节点 #3 matmul（本树前文已展开）
  │    ├─ data_centroids_t_.data  [L256] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ FP32ComputeIP  [L263] for_statement@262 i < count
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ heap.size  [L271] for_statement@262 i < count → for_statement@268 j < bucket_count_s_ → if_statement@271 (heap.size() < candidate_count_s || dist_term_s < heap.top().first)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ heap.top  [L271] for_statement@262 i < count → for_statement@268 j < bucket_count_s_ → if_statement@271 (heap.size() < candidate_count_s || dist_term_s < heap.top().first)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ heap.emplace  [L272] for_statement@262 i < count → for_statement@268 j < bucket_count_s_ → if_statement@271 (heap.size() < candidate_count_s || dist_term_s < heap.top().first)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ heap.size  [L274] for_statement@262 i < count → for_statement@268 j < bucket_count_s_ → if_statement@274 (heap.size() > candidate_count_s)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ heap.pop  [L275] for_statement@262 i < count → for_statement@268 j < bucket_count_s_ → if_statement@274 (heap.size() > candidate_count_s)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ heap.top  [L279] for_statement@262 i < count → for_statement@278 j >= 0
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ heap.top  [L280] for_statement@262 i < count → for_statement@278 j >= 0
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ heap.pop  [L281] for_statement@262 i < count → for_statement@278 j >= 0
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ CHECK_ARGUMENT  [L283] for_statement@262 i < count
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ heap.empty  [L283] for_statement@262 i < count
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ fmt::format  [L283] for_statement@262 i < count
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ std::floor  [L286] for_statement@262 i < count
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ std::max  [L287] for_statement@262 i < count
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ heap.size  [L301] for_statement@262 i < count → for_statement@288 j < scan_bucket_count_s → for_statement@289 k < bucket_count_t_ → if_statement@301 (heap.size() < buckets_per_data || dist_term_st < heap.top().first)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ heap.top  [L301] for_statement@262 i < count → for_statement@288 j < scan_bucket_count_s → for_statement@289 k < bucket_count_t_ → if_statement@301 (heap.size() < buckets_per_data || dist_term_st < heap.top().first)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ heap.emplace  [L302] for_statement@262 i < count → for_statement@288 j < scan_bucket_count_s → for_statement@289 k < bucket_count_t_ → if_statement@301 (heap.size() < buckets_per_data || dist_term_st < heap.top().first)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ heap.size  [L304] for_statement@262 i < count → for_statement@288 j < scan_bucket_count_s → for_statement@289 k < bucket_count_t_ → if_statement@304 (heap.size() > buckets_per_data)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ heap.pop  [L305] for_statement@262 i < count → for_statement@288 j < scan_bucket_count_s → for_statement@289 k < bucket_count_t_ → if_statement@304 (heap.size() > buckets_per_data)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ std::min  [L309] for_statement@262 i < count
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ heap.size  [L309] for_statement@262 i < count
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ heap.empty  [L310] for_statement@262 i < count → for_statement@310 j >= 0 && !heap.empty()
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ heap.top  [L311] for_statement@262 i < count → for_statement@310 j >= 0 && !heap.empty()
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ heap.pop  [L312] for_statement@262 i < count → for_statement@310 j >= 0 && !heap.empty()
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ ctx->stats->AddDistance  [L316] if_statement@315 (ctx != nullptr and ctx->stats != nullptr)
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │  #4 IVFPartitionStrategy::ClassifyDatasForSearch [src/algorithm/ivf/ivf_partition_strategy.h:64]
  │    ├─ std::move  [L69] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  │    ├─ ClassifyDatas  [L69] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ reasoning_ctx->RecordBucketSelection  [L351] if_statement@350 (reasoning_ctx != nullptr)
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ CHECK_ARGUMENT  [L357] if_statement@356 (buckets_per_data_ > 1)
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ std::numeric_limits<int64_t>::max  [L357] if_statement@356 (buckets_per_data_ > 1)
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ DistanceHeap::MakeInstanceBySize<true, false>  [L362] 函数本体；短路求值/提前返回见源码
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ std::min<uint64_t>  [L369] 函数本体；短路求值/提前返回见源码
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ std::max<uint64_t>  [L370] 函数本体；短路求值/提前返回见源码
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ this->GetNumElements  [L370] 函数本体；短路求值/提前返回见源码
  │  #5 IVF::GetNumElements [src/algorithm/ivf/ivf.cpp:291]
  ├─ candidate_ids.reserve  [L371] 函数本体；短路求值/提前返回见源码
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ candidate_labels.reserve  [L372] 函数本体；短路求值/提前返回见源码
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ scores.resize  [L373] 函数本体；短路求值/提前返回见源码
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ param.time_cost->CheckOvertime  [L376] lambda@375（定义体，执行时间取决于调用/调度） → if_statement@376 (param.time_cost == nullptr or not param.time_cost->CheckOvertime())
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ ctx.stats->is_timeout.store  [L380] lambda@375（定义体，执行时间取决于调用/调度） → if_statement@379 (ctx.stats != nullptr)
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ candidate_ids.empty  [L386] lambda@385（定义体，执行时间取决于调用/调度） → if_statement@386 (candidate_ids.empty())
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ is_timed_out  [L389] lambda@385（定义体，执行时间取决于调用/调度） → if_statement@389 (is_timed_out())
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ request.distance_batch_func_  [L392] lambda@385（定义体，执行时间取决于调用/调度）
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ candidate_labels.data  [L393] lambda@385（定义体，执行时间取决于调用/调度）
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ candidate_labels.size  [L393] lambda@385（定义体，执行时间取决于调用/调度）
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ scores.data  [L393] lambda@385（定义体，执行时间取决于调用/调度）
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ ctx.stats->AddDistance  [L395] lambda@385（定义体，执行时间取决于调用/调度） → if_statement@394 (ctx.stats != nullptr)
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ candidate_ids.size  [L397] lambda@385（定义体，执行时间取决于调用/调度） → if_statement@394 (ctx.stats != nullptr)
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ candidate_ids.size  [L399] lambda@385（定义体，执行时间取决于调用/调度） → for_statement@399 i < candidate_ids.size()
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ CHECK_ARGUMENT  [L400] lambda@385（定义体，执行时间取决于调用/调度） → for_statement@399 i < candidate_ids.size()
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ std::isfinite  [L400] lambda@385（定义体，执行时间取决于调用/调度） → for_statement@399 i < candidate_ids.size()
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ filter->CheckValid  [L403] lambda@385（定义体，执行时间取决于调用/调度） → for_statement@399 i < candidate_ids.size() → if_statement@403 (filter != nullptr and not filter->CheckValid(origin_id))
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ reasoning_ctx->RecordFilterReject  [L405] lambda@385（定义体，执行时间取决于调用/调度） → for_statement@399 i < candidate_ids.size() → if_statement@403 (filter != nullptr and not filter->CheckValid(origin_id)) → if_statement@404 (reasoning_ctx != nullptr)
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ reasoning_ctx->RecordVisit  [L410] lambda@385（定义体，执行时间取决于调用/调度） → for_statement@399 i < candidate_ids.size() → if_statement@409 (reasoning_ctx != nullptr)
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ search_result->Push  [L412] lambda@385（定义体，执行时间取决于调用/调度） → for_statement@399 i < candidate_ids.size()
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ search_result->Size  [L413] lambda@385（定义体，执行时间取决于调用/调度） → for_statement@399 i < candidate_ids.size() → while_statement@413 (search_result->Size() > static_cast<uint64_t>(topk))
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ reasoning_ctx->RecordEviction  [L415] lambda@385（定义体，执行时间取决于调用/调度） → for_statement@399 i < candidate_ids.size() → while_statement@413 (search_result->Size() > static_cast<uint64_t>(topk)) → if_statement@414 (reasoning_ctx != nullptr)
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ search_result->Top  [L415] lambda@385（定义体，执行时间取决于调用/调度） → for_statement@399 i < candidate_ids.size() → while_statement@413 (search_result->Size() > static_cast<uint64_t>(topk)) → if_statement@414 (reasoning_ctx != nullptr)
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ search_result->Pop  [L418] lambda@385（定义体，执行时间取决于调用/调度） → for_statement@399 i < candidate_ids.size() → while_statement@413 (search_result->Size() > static_cast<uint64_t>(topk))
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ candidate_ids.clear  [L421] lambda@385（定义体，执行时间取决于调用/调度）
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ candidate_labels.clear  [L422] lambda@385（定义体，执行时间取决于调用/调度）
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ is_timed_out  [L428] for_range_loop@427 → if_statement@428 (is_timed_out())
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ param.executors.empty  [L435] for_range_loop@427 → if_statement@435 (not param.executors.empty())
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ param.executors[0]->Clear  [L436] for_range_loop@427 → if_statement@435 (not param.executors.empty())
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ param.executors[0]->Run  [L437] for_range_loop@427 → if_statement@435 (not param.executors.empty())
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ bucket_->GetBucketSize  [L439] for_range_loop@427
  │  #6 BucketDataCell::GetBucketSize [src/datacell/bucket_datacell.h:180]
  │    ├─ check_valid_bucket_id  [L182] 函数本体；短路求值/提前返回见源码
  │    │  #7 BucketDataCell::check_valid_bucket_id [src/datacell/bucket_datacell.h:244]
  │    │    ├─ VsagException  [L247] if_statement@246 (bucket_id >= this->bucket_count_ or bucket_id < 0)
  │    │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ bucket_->GetInnerIds  [L440] for_range_loop@427
  │  #8 BucketDataCell::GetInnerIds [src/datacell/bucket_datacell.h:120]
  │    ├─ check_valid_bucket_id  [L122] 函数本体；短路求值/提前返回见源码
  │    │  ↳ 复用节点 #7 BucketDataCell::check_valid_bucket_id（本树前文已展开）
  │    ├─ this->inner_ids_[bucket_id].data  [L123] 函数本体；短路求值/提前返回见源码
  │    │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ std::numeric_limits<InnerIdType>::max  [L443] for_range_loop@427 → for_statement@441 offset < bucket_size → if_statement@443 (inner_id == std::numeric_limits<InnerIdType>::max())
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ attr_filter->CheckValid  [L447] for_range_loop@427 → for_statement@441 offset < bucket_size → if_statement@447 (attr_filter != nullptr and not attr_filter->CheckValid(offset))
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ reasoning_ctx->RecordFilterReject  [L449] for_range_loop@427 → for_statement@441 offset < bucket_size → if_statement@447 (attr_filter != nullptr and not attr_filter->CheckValid(offset)) → if_statement@448 (reasoning_ctx != nullptr)
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ candidate_ids.push_back  [L453] for_range_loop@427 → for_statement@441 offset < bucket_size
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ candidate_labels.push_back  [L454] for_range_loop@427 → for_statement@441 offset < bucket_size
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ label_table_->GetLabelById  [L454] for_range_loop@427 → for_statement@441 offset < bucket_size
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ candidate_ids.size  [L455] for_range_loop@427 → for_statement@441 offset < bucket_size → if_statement@455 (candidate_ids.size() == batch_capacity and not submit_batch())
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ submit_batch  [L455] for_range_loop@427 → for_statement@441 offset < bucket_size → if_statement@455 (candidate_ids.size() == batch_capacity and not submit_batch())
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ submit_batch  [L465] if_statement@464 (not timed_out)
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ search_result->Empty  [L473] while_statement@473 (not search_result->Empty())
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ search_result->Top  [L474] while_statement@473 (not search_result->Empty())
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ id_to_min_score.find  [L476] while_statement@473 (not search_result->Empty())
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ id_to_min_score.end  [L477] while_statement@473 (not search_result->Empty()) → if_statement@477 (iter == id_to_min_score.end() or score < iter->second)
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ search_result->Pop  [L480] while_statement@473 (not search_result->Empty())
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ search_result->Push  [L484] for_range_loop@483
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ search_result->Size  [L485] for_range_loop@483 → if_statement@485 (search_result->Size() > static_cast<uint64_t>(origin_topk))
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
  ├─ search_result->Pop  [L486] for_range_loop@483 → if_statement@485 (search_result->Size() > static_cast<uint64_t>(origin_topk))
  │  └─ 边界：具体类型/宏/标准库/外部实现见源码与主讲解
```
