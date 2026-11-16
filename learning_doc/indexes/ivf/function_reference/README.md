# IVF 函数总目录

[主讲解与分支调用树](../code_walkthrough.md) · [IVF 设计](../README.md)

基线 `fd363937`。共收录 **292 个函数定义、2957 个显式调用表达式**。覆盖 `src/algorithm/ivf` 非测试 C++ 文件及头文件中的函数定义，以及下列共享实现。完整函数体用于检查所有控制流；语法树调用点索引用于防止短摘录遗漏嵌套调用。

## 阅读顺序

1. 主讲解先把创建、Build、Train、Add、Search、精排和维护串起来。
2. 在下面进入对应源码页，读完整函数与每个调用点。
3. 遇到虚分派先回主讲解判断实际对象，随后沿候选实现链接下钻。
4. 容器、分配器、I/O 后端、SIMD/BLAS、用户回调是明确边界；本目录不是未经配置就能确定的机器级完整调用图。

## 文件与函数


### [src/algorithm/ivf/flat_bucket_searcher.cpp](flat_bucket_searcher.md)

- [FlatBucketSearcher::Search · L26](flat_bucket_searcher.md#L26)（46 个显式调用点）


### [src/algorithm/ivf/gno_imi_parameter.cpp](gno_imi_parameter.md)

- [GNOIMIParameter::GNOIMIParameter · L25](gno_imi_parameter.md#L25)（0 个显式调用点）

- [GNOIMIParameter::FromJson · L27](gno_imi_parameter.md#L27)（6 个显式调用点）

- [GNOIMIParameter::ToJson · L43](gno_imi_parameter.md#L43)（2 个显式调用点）

- [GNOIMIParameter::CheckCompatibility · L50](gno_imi_parameter.md#L50)（3 个显式调用点）


### [src/algorithm/ivf/gno_imi_partition.cpp](gno_imi_partition.md)

- [matmul · L40](gno_imi_partition.md#L40)（1 个显式调用点）

- [GNOIMIPartition::GNOIMIPartition · L58](gno_imi_partition.md#L58)（11 个显式调用点）

- [GNOIMIPartition::Train · L88](gno_imi_partition.md#L88)（76 个显式调用点）

- [GNOIMIPartition::ClassifyDatas · L201](gno_imi_partition.md#L201)（6 个显式调用点）

- [GNOIMIPartition::ClassifyDatasForSearch · L221](gno_imi_partition.md#L221)（40 个显式调用点）

- [GNOIMIPartition::Serialize · L323](gno_imi_partition.md#L323)（8 个显式调用点）

- [GNOIMIPartition::Deserialize · L334](gno_imi_partition.md#L334)（8 个显式调用点）

- [GNOIMIPartition::inner_classify_datas · L346](gno_imi_partition.md#L346)（7 个显式调用点）

- [GNOIMIPartition::inner_joint_classify_datas · L367](gno_imi_partition.md#L367)（25 个显式调用点）

- [GNOIMIPartition::GetCentroid · L440](gno_imi_partition.md#L440)（6 个显式调用点）


### [src/algorithm/ivf/graph_bucket_searcher.cpp](graph_bucket_searcher.md)

- [GraphBucketSearcher::GraphBucketSearcher · L27](graph_bucket_searcher.md#L27)（0 个显式调用点）

- [GraphBucketSearcher::Search · L36](graph_bucket_searcher.md#L36)（5 个显式调用点）

- [GraphBucketSearcher::search_graph · L77](graph_bucket_searcher.md#L77)（21 个显式调用点）


### [src/algorithm/ivf/ivf.cpp](ivf.md)

- [make_precise_bucket_param · L49](ivf.md#L49)（1 个显式调用点）

- [build_default_ivf_param · L61](ivf.md#L61)（31 个显式调用点）

- [IVF::CheckAndMappingExternalParam · L110](ivf.md#L110)（44 个显式调用点）

- [IVF::IVF · L221](ivf.md#L221)（16 个显式调用点）

- [IVF::GetCodeByInnerId · L285](ivf.md#L285)（2 个显式调用点）

- [IVF::GetNumElements · L291](ivf.md#L291)（0 个显式调用点）

- [IVF::Merge · L296](ivf.md#L296)（6 个显式调用点）

- [IVF::get_location · L312](ivf.md#L312)（0 个显式调用点）

- [IVF::ExportModel · L321](ivf.md#L321)（5 个显式调用点）

- [IVF::merge_one_unit · L337](ivf.md#L337)（12 个显式调用点）

- [IVF::check_merge_illegal · L360](ivf.md#L360)（18 个显式调用点）

- [IVF::GetAttributeSetByInnerId · L401](ivf.md#L401)（2 个显式调用点）

- [IVF::CalcDistancesById · L407](ivf.md#L407)（1 个显式调用点）

- [IVF::CalDistanceById · L415](ivf.md#L415)（34 个显式调用点）

- [IVF::CalcDistanceById · L496](ivf.md#L496)（6 个显式调用点）

- [IVF::GetVectorByInnerId · L515](ivf.md#L515)（2 个显式调用点）

- [calculate_percentile · L521](ivf.md#L521)（2 个显式调用点）

- [get_data_stats · L536](ivf.md#L536)（26 个显式调用点）

- [IVF::GetStats · L575](ivf.md#L575)（18 个显式调用点）

- [IVF::AnalyzeIndexBySearch · L604](ivf.md#L604)（6 个显式调用点）

- [IVF::cal_memory_usage · L616](ivf.md#L616)（9 个显式调用点）

- [IVF::GetMemoryUsage · L639](ivf.md#L639)（2 个显式调用点）


### [src/algorithm/ivf/ivf.h](ivf_h.md)

- [IVF::IVF · L70](ivf_h.md#L70)（0 个显式调用点）

- [IVF::~IVF · L73](ivf_h.md#L73)（0 个显式调用点）

- [IVF::Fork · L110](ivf_h.md#L110)（1 个显式调用点）

- [IVF::GetIndexType · L121](ivf_h.md#L121)（0 个显式调用点）

- [IVF::GetName · L126](ivf_h.md#L126)（0 个显式调用点）

- [IVF::GetNumberRemoved · L134](ivf_h.md#L134)（0 个显式调用点）


### [src/algorithm/ivf/ivf_bucket_searcher.h](ivf_bucket_searcher_h.md)

- [IVFBucketSearcher::~IVFBucketSearcher · L34](ivf_bucket_searcher_h.md#L34)（0 个显式调用点）


### [src/algorithm/ivf/ivf_build.cpp](ivf_build.md)

- [IVF::InitFeatures · L38](ivf_build.md#L38)（17 个显式调用点）

- [IVF::Build · L104](ivf_build.md#L104)（5 个显式调用点）

- [IVF::Train · L120](ivf_build.md#L120)（13 个显式调用点）

- [IVF::Add · L146](ivf_build.md#L146)（37 个显式调用点）

- [PairwiseBucketDistanceProvider::PairwiseBucketDistanceProvider · L284](ivf_build.md#L284)（0 个显式调用点）

- [PairwiseBucketDistanceProvider::QueryDistance · L290](ivf_build.md#L290)（1 个显式调用点）

- [PairwiseBucketDistanceProvider::BatchQueryDistance · L295](ivf_build.md#L295)（1 个显式调用点）

- [PairwiseBucketDistanceProvider::PairwiseDistance · L305](ivf_build.md#L305)（1 个显式调用点）

- [PairwiseBucketDistanceProvider::FactoryComputerById · L312](ivf_build.md#L312)（1 个显式调用点）

- [IVF::build_bucket_graphs · L324](ivf_build.md#L324)（30 个显式调用点）

- [IVF::fill_location_map · L405](ivf_build.md#L405)（11 个显式调用点）

- [IVF::RebuildBucketGraphs · L442](ivf_build.md#L442)（8 个显式调用点）


### [src/algorithm/ivf/ivf_modify.cpp](ivf_modify.md)

- [IVF::Remove · L22](ivf_modify.md#L22)（1 个显式调用点）

- [IVF::UpdateAttribute · L33](ivf_modify.md#L33)（3 个显式调用点）

- [IVF::UpdateAttribute · L40](ivf_modify.md#L40)（3 个显式调用点）


### [src/algorithm/ivf/ivf_nearest_partition.cpp](ivf_nearest_partition.md)

- [compute_centroid_dots · L51](ivf_nearest_partition.md#L51)（1 个显式调用点）

- [IVFNearestPartition::IVFNearestPartition · L79](ivf_nearest_partition.md#L79)（1 个显式调用点）

- [IVFNearestPartition::Train · L91](ivf_nearest_partition.md#L91)（38 个显式调用点）

- [IVFNearestPartition::ClassifyDatas · L157](ivf_nearest_partition.md#L157)（24 个显式调用点）

- [IVFNearestPartition::Serialize · L227](ivf_nearest_partition.md#L227)（5 个显式调用点）

- [IVFNearestPartition::Deserialize · L239](ivf_nearest_partition.md#L239)（17 个显式调用点）

- [IVFNearestPartition::factory_router_index · L275](ivf_nearest_partition.md#L275)（5 个显式调用点）

- [IVFNearestPartition::GetCentroid · L286](ivf_nearest_partition.md#L286)（7 个显式调用点）

- [IVFNearestPartition::GetMemoryUsage · L303](ivf_nearest_partition.md#L303)（3 个显式调用点）

- [IVFNearestPartition::classify_datas_by_scan · L313](ivf_nearest_partition.md#L313)（26 个显式调用点）


### [src/algorithm/ivf/ivf_parameter.cpp](ivf_parameter.md)

- [IVFParameter::FromJson · L28](ivf_parameter.md#L28)（34 个显式调用点）

- [IVFParameter::ToJson · L121](ivf_parameter.md#L121)（9 个显式调用点）

- [IVFParameter::CheckCompatibility · L133](ivf_parameter.md#L133)（8 个显式调用点）

- [IVFSearchParameters::FromJson · L150](ivf_parameter.md#L150)（15 个显式调用点）


### [src/algorithm/ivf/ivf_parameter.h](ivf_parameter_h.md)

- [IVFParameter::IVFParameter · L35](ivf_parameter_h.md#L35)（0 个显式调用点）

- [IVFSearchParameters::IVFSearchParameters · L67](ivf_parameter_h.md#L67)（0 个显式调用点）


### [src/algorithm/ivf/ivf_partition_strategy.cpp](ivf_partition_strategy.md)

- [IVFPartitionStrategy::GetResidual · L22](ivf_partition_strategy.md#L22)（2 个显式调用点）


### [src/algorithm/ivf/ivf_partition_strategy.h](ivf_partition_strategy_h.md)

- [IVFPartitionStrategy::Clone · L37](ivf_partition_strategy_h.md#L37)（3 个显式调用点）

- [IVFPartitionStrategy::IVFPartitionStrategy · L48](ivf_partition_strategy_h.md#L48)（0 个显式调用点）

- [IVFPartitionStrategy::ClassifyDatasForSearch · L64](ivf_partition_strategy_h.md#L64)（2 个显式调用点）

- [IVFPartitionStrategy::Serialize · L75](ivf_partition_strategy_h.md#L75)（3 个显式调用点）

- [IVFPartitionStrategy::Deserialize · L82](ivf_partition_strategy_h.md#L82)（3 个显式调用点）

- [IVFPartitionStrategy::GetMemoryUsage · L93](ivf_partition_strategy_h.md#L93)（0 个显式调用点）


### [src/algorithm/ivf/ivf_partition_strategy_parameter.cpp](ivf_partition_strategy_parameter.md)

- [IVFPartitionStrategyParameters::IVFPartitionStrategyParameters · L28](ivf_partition_strategy_parameter.md#L28)（0 个显式调用点）

- [IVFPartitionStrategyParameters::FromJson · L30](ivf_partition_strategy_parameter.md#L30)（19 个显式调用点）

- [IVFPartitionStrategyParameters::ToJson · L72](ivf_partition_strategy_parameter.md#L72)（9 个显式调用点）

- [IVFPartitionStrategyParameters::CheckCompatibility · L95](ivf_partition_strategy_parameter.md#L95)（5 个显式调用点）


### [src/algorithm/ivf/ivf_search.cpp](ivf_search.md)

- [IVF::KnnSearch · L51](ivf_search.md#L51)（2 个显式调用点）

- [IVF::RangeSearch · L68](ivf_search.md#L68)（1 个显式调用点）

- [IVF::create_search_param · L86](ivf_search.md#L86)（5 个显式调用点）

- [IVF::route_buckets_only · L110](ivf_search.md#L110)（21 个显式调用点）

- [IVF::reorder · L183](ivf_search.md#L183)（2 个显式调用点）

- [IVF::search · L199](ivf_search.md#L199)（43 个显式调用点）

- [IVF::search_with_custom_distance · L334](ivf_search.md#L334)（62 个显式调用点）

- [IVF::SearchWithRequest · L492](ivf_search.md#L492)（189 个显式调用点）

- [IVF::AttachReasoningReport · L799](ivf_search.md#L799)（8 个显式调用点）


### [src/algorithm/ivf/ivf_serialize.cpp](ivf_serialize.md)

- [get_ivf_graph_param · L38](ivf_serialize.md#L38)（11 个显式调用点）

- [serialize_ivf_graph_param · L62](ivf_serialize.md#L62)（2 个显式调用点）

- [has_any_fresh_bucket_graph · L69](ivf_serialize.md#L69)（3 个显式调用点）

- [IVF::Serialize · L88](ivf_serialize.md#L88)（39 个显式调用点）

- [IVF::collect_streaming_header · L156](ivf_serialize.md#L156)（36 个显式调用点）

- [IVF::serialize_streaming_body · L218](ivf_serialize.md#L218)（30 个显式调用点）

- [IVF::deserialize_streaming_body · L279](ivf_serialize.md#L279)（1 个显式调用点）

- [IVF::load_streaming_body · L284](ivf_serialize.md#L284)（1 个显式调用点）

- [IVF::read_streaming_body · L291](ivf_serialize.md#L291)（85 个显式调用点）

- [IVF::Deserialize · L526](ivf_serialize.md#L526)（73 个显式调用点）


### [src/datacell/bucket_datacell.h](bucket_datacell_h.md)

- [AdjustBucketReadCacheParam · L36](bucket_datacell_h.md#L36)（5 个显式调用点）

- [BucketDataCell::ScanBucketById · L63](bucket_datacell_h.md#L63)（2 个显式调用点）

- [BucketDataCell::QueryOneById · L71](bucket_datacell_h.md#L71)（2 个显式调用点）

- [BucketDataCell::Query · L82](bucket_datacell_h.md#L82)（4 个显式调用点）

- [BucketDataCell::GetInnerIds · L120](bucket_datacell_h.md#L120)（2 个显式调用点）

- [BucketDataCell::Prefetch · L126](bucket_datacell_h.md#L126)（2 个显式调用点）

- [BucketDataCell::Package · L132](bucket_datacell_h.md#L132)（2 个显式调用点）

- [BucketDataCell::Unpack · L139](bucket_datacell_h.md#L139)（2 个显式调用点）

- [BucketDataCell::InitIO · L158](bucket_datacell_h.md#L158)（3 个显式调用点）

- [BucketDataCell::GetQuantizerName · L170](bucket_datacell_h.md#L170)（1 个显式调用点）

- [BucketDataCell::GetMetricType · L175](bucket_datacell_h.md#L175)（0 个显式调用点）

- [BucketDataCell::GetBucketSize · L180](bucket_datacell_h.md#L180)（1 个显式调用点）

- [BucketDataCell::GetMemoryUsage · L189](bucket_datacell_h.md#L189)（3 个显式调用点）

- [BucketDataCell::init_shared_read_cache_io · L202](bucket_datacell_h.md#L202)（9 个显式调用点）

- [BucketDataCell::get_page_count · L238](bucket_datacell_h.md#L238)（0 个显式调用点）

- [BucketDataCell::check_valid_bucket_id · L244](bucket_datacell_h.md#L244)（1 个显式调用点）

- [BucketDataCell&lt;QuantTmpl, IOTmpl&gt;::BucketDataCell · L312](bucket_datacell_h.md#L312)（4 个显式调用点）

- [BucketDataCell&lt;QuantTmpl, IOTmpl&gt;::query_one_by_id · L341](bucket_datacell_h.md#L341)（14 个显式调用点）

- [BucketDataCell&lt;QuantTmpl, IOTmpl&gt;::query · L380](bucket_datacell_h.md#L380)（49 个显式调用点）

- [BucketDataCell&lt;QuantTmpl, IOTmpl&gt;::scan_bucket_by_id · L522](bucket_datacell_h.md#L522)（15 个显式调用点）

- [BucketDataCell&lt;QuantTmpl, IOTmpl&gt;::FactoryComputer · L566](bucket_datacell_h.md#L566)（12 个显式调用点）

- [BucketDataCell&lt;QuantTmpl, IOTmpl&gt;::Train · L586](bucket_datacell_h.md#L586)（10 个显式调用点）

- [BucketDataCell&lt;QuantTmpl, IOTmpl&gt;::encode_vector · L613](bucket_datacell_h.md#L613)（25 个显式调用点）

- [BucketDataCell&lt;QuantTmpl, IOTmpl&gt;::check_valid_bucket_capacity · L645](bucket_datacell_h.md#L645)（4 个显式调用点）

- [BucketDataCell&lt;QuantTmpl, IOTmpl&gt;::InsertVector · L660](bucket_datacell_h.md#L660)（12 个显式调用点）

- [BucketDataCell&lt;QuantTmpl, IOTmpl&gt;::BatchInsertVector · L703](bucket_datacell_h.md#L703)（26 个显式调用点）

- [BucketDataCell&lt;QuantTmpl, IOTmpl&gt;::InsertVectorWithOffset · L818](bucket_datacell_h.md#L818)（17 个显式调用点）

- [BucketDataCell&lt;QuantTmpl, IOTmpl&gt;::Serialize · L883](bucket_datacell_h.md#L883)（6 个显式调用点）

- [BucketDataCell&lt;QuantTmpl, IOTmpl&gt;::Deserialize · L898](bucket_datacell_h.md#L898)（15 个显式调用点）

- [BucketDataCell&lt;QuantTmpl, IOTmpl&gt;::package_fastscan · L934](bucket_datacell_h.md#L934)（4 个显式调用点）

- [BucketDataCell&lt;QuantTmpl, IOTmpl&gt;::unpack_fastscan · L958](bucket_datacell_h.md#L958)（4 个显式调用点）

- [BucketDataCell&lt;QuantTmpl, IOTmpl&gt;::ExportModel · L979](bucket_datacell_h.md#L979)（5 个显式调用点）

- [BucketDataCell&lt;QuantTmpl, IOTmpl&gt;::MergeOther · L994](bucket_datacell_h.md#L994)（7 个显式调用点）

- [BucketDataCell&lt;QuantTmpl, IOTmpl&gt;::GetCodesById · L1017](bucket_datacell_h.md#L1017)（5 个显式调用点）

- [BucketDataCell&lt;QuantTmpl, IOTmpl&gt;::ComputePairVectors · L1035](bucket_datacell_h.md#L1035)（12 个显式调用点）


### [src/datacell/bucket_interface.cpp](bucket_interface.md)

- [BucketInterface::MakeInstance · L24](bucket_interface.md#L24)（9 个显式调用点）


### [src/impl/reorder/bucket_reorder.cpp](bucket_reorder.md)

- [BucketReorder::Reorder · L28](bucket_reorder.md#L28)（25 个显式调用点）


### [src/impl/reorder/flatten_reorder.cpp](flatten_reorder.md)

- [FlattenReorder::QueryFusedLowerBound · L34](flatten_reorder.md#L34)（8 个显式调用点）

- [FlattenReorder::QueryFusedFullWithHint · L77](flatten_reorder.md#L77)（11 个显式调用点）

- [add_reorder_distance_count · L130](flatten_reorder.md#L130)（1 个显式调用点）

- [add_reorder_candidate_count · L138](flatten_reorder.md#L138)（1 个显式调用点）

- [add_reorder_lower_bound_probe_count · L146](flatten_reorder.md#L146)（1 个显式调用点）

- [FlattenReorder::Reorder · L156](flatten_reorder.md#L156)（99 个显式调用点）

- [FlattenReorder::ReorderFused · L419](flatten_reorder.md#L419)（106 个显式调用点）


### [src/quantization/computer.h](computer_h.md)

- [ComputerInterface::ComputerInterface · L31](computer_h.md#L31)（0 个显式调用点）

- [ComputerInterface::~ComputerInterface · L33](computer_h.md#L33)（0 个显式调用点）

- [Computer::Computer · L39](computer_h.md#L39)（0 个显式调用点）

- [Computer::~Computer · L42](computer_h.md#L42)（1 个显式调用点）

- [Computer::SetQuery · L48](computer_h.md#L48)（1 个显式调用点）

- [Computer::ComputeDist · L53](computer_h.md#L53)（1 个显式调用点）

- [Computer::ComputeDistWithThreshold · L58](computer_h.md#L58)（1 个显式调用点）

- [Computer::ComputeDistWithLowerBound · L63](computer_h.md#L63)（1 个显式调用点）

- [Computer::ScanBatchDists · L68](computer_h.md#L68)（1 个显式调用点）

- [Computer::ScanBatchDistsWithThreshold · L73](computer_h.md#L73)（1 个显式调用点）

- [Computer::ComputeDistsBatch4 · L81](computer_h.md#L81)（1 个显式调用点）

- [Computer&lt;TransformQuantizer&lt;QuantImpl, metric&gt;&gt;::Computer · L107](computer_h.md#L107)（1 个显式调用点）

- [Computer&lt;TransformQuantizer&lt;QuantImpl, metric&gt;&gt;::~Computer · L115](computer_h.md#L115)（1 个显式调用点）

- [Computer&lt;TransformQuantizer&lt;QuantImpl, metric&gt;&gt;::SetQuery · L122](computer_h.md#L122)（1 个显式调用点）

- [Computer&lt;TransformQuantizer&lt;QuantImpl, metric&gt;&gt;::ComputeDist · L127](computer_h.md#L127)（1 个显式调用点）

- [Computer&lt;TransformQuantizer&lt;QuantImpl, metric&gt;&gt;::ComputeDistWithThreshold · L132](computer_h.md#L132)（1 个显式调用点）

- [Computer&lt;TransformQuantizer&lt;QuantImpl, metric&gt;&gt;::ComputeDistWithLowerBound · L137](computer_h.md#L137)（1 个显式调用点）

- [Computer&lt;TransformQuantizer&lt;QuantImpl, metric&gt;&gt;::ScanBatchDists · L142](computer_h.md#L142)（1 个显式调用点）

- [Computer&lt;TransformQuantizer&lt;QuantImpl, metric&gt;&gt;::ScanBatchDistsWithThreshold · L147](computer_h.md#L147)（1 个显式调用点）

- [Computer&lt;TransformQuantizer&lt;QuantImpl, metric&gt;&gt;::ComputeDistsBatch4 · L155](computer_h.md#L155)（1 个显式调用点）


### [src/quantization/quantizer.h](quantizer_h.md)

- [Quantizer::Quantizer&lt;QuantT&gt; · L37](quantizer_h.md#L37)（0 个显式调用点）

- [Quantizer::~Quantizer · L40](quantizer_h.md#L40)（0 个显式调用点）

- [Quantizer::Train · L49](quantizer_h.md#L49)（2 个显式调用点）

- [Quantizer::ReTrain · L64](quantizer_h.md#L64)（2 个显式调用点）

- [Quantizer::EncodeOne · L77](quantizer_h.md#L77)（2 个显式调用点）

- [Quantizer::EncodeBatch · L90](quantizer_h.md#L90)（2 个显式调用点）

- [Quantizer::EncodeBatchImpl · L99](quantizer_h.md#L99)（2 个显式调用点）

- [Quantizer::DecodeOne · L116](quantizer_h.md#L116)（2 个显式调用点）

- [Quantizer::DecodeBatch · L129](quantizer_h.md#L129)（2 个显式调用点）

- [Quantizer::DecodeBatchImpl · L138](quantizer_h.md#L138)（2 个显式调用点）

- [Quantizer::Compute · L156](quantizer_h.md#L156)（2 个显式调用点）

- [Quantizer::Serialize · L161](quantizer_h.md#L161)（6 个显式调用点）

- [Quantizer::Deserialize · L170](quantizer_h.md#L170)（6 个显式调用点）

- [Quantizer::FactoryComputer · L179](quantizer_h.md#L179)（1 个显式调用点）

- [Quantizer::ProcessQuery · L184](quantizer_h.md#L184)（2 个显式调用点）

- [Quantizer::ComputeDist · L189](quantizer_h.md#L189)（2 个显式调用点）

- [Quantizer::ComputeDistWithThreshold · L194](quantizer_h.md#L194)（4 个显式调用点）

- [Quantizer::ComputeDistWithLowerBound · L207](quantizer_h.md#L207)（5 个显式调用点）

- [Quantizer::ComputeDist · L223](quantizer_h.md#L223)（2 个显式调用点）

- [Quantizer::ScanBatchDists · L230](quantizer_h.md#L230)（2 个显式调用点）

- [Quantizer::ScanBatchDistsWithThreshold · L238](quantizer_h.md#L238)（1 个显式调用点）

- [Quantizer::ComputeDistsBatch4 · L249](quantizer_h.md#L249)（10 个显式调用点）

- [Quantizer::ReleaseComputer · L270](quantizer_h.md#L270)（2 个显式调用点）

- [Quantizer::ReleaseComputerImpl · L279](quantizer_h.md#L279)（1 个显式调用点）

- [Quantizer::ScanBatchDistImpl · L290](quantizer_h.md#L290)（2 个显式调用点）

- [Quantizer::Name · L300](quantizer_h.md#L300)（2 个显式调用点）

- [Quantizer::Metric · L305](quantizer_h.md#L305)（0 个显式调用点）

- [Quantizer::HoldMolds · L309](quantizer_h.md#L309)（0 个显式调用点）

- [Quantizer::GetCodeSize · L325](quantizer_h.md#L325)（0 个显式调用点）

- [Quantizer::GetQueryCodeSize · L330](quantizer_h.md#L330)（0 个显式调用点）

- [Quantizer::GetDim · L340](quantizer_h.md#L340)（0 个显式调用点）

- [Quantizer::& cast · L346](quantizer_h.md#L346)（0 个显式调用点）

- [Quantizer::& cast · L351](quantizer_h.md#L351)（0 个显式调用点）


### [src/quantization/fp32_quantizer.cpp](fp32_quantizer.md)

- [FP32Quantizer&lt;metric&gt;::FP32Quantizer · L25](fp32_quantizer.md#L25)（0 个显式调用点）

- [FP32Quantizer&lt;metric&gt;::FP32Quantizer · L33](fp32_quantizer.md#L33)（0 个显式调用点）

- [FP32Quantizer&lt;metric&gt;::FP32Quantizer · L43](fp32_quantizer.md#L43)（0 个显式调用点）

- [FP32Quantizer&lt;metric&gt;::TrainImpl · L50](fp32_quantizer.md#L50)（0 个显式调用点）

- [FP32Quantizer&lt;metric&gt;::EncodeOneImpl · L57](fp32_quantizer.md#L57)（6 个显式调用点）

- [FP32Quantizer&lt;metric&gt;::EncodeBatchImpl · L76](fp32_quantizer.md#L76)（1 个显式调用点）

- [FP32Quantizer&lt;metric&gt;::DecodeOneImpl · L85](fp32_quantizer.md#L85)（1 个显式调用点）

- [FP32Quantizer&lt;metric&gt;::DecodeBatchImpl · L92](fp32_quantizer.md#L92)（2 个显式调用点）

- [FP32Quantizer&lt;metric&gt;::ComputeImpl · L105](fp32_quantizer.md#L105)（3 个显式调用点）

- [FP32Quantizer&lt;metric&gt;::ScanBatchDistImpl · L132](fp32_quantizer.md#L132)（1 个显式调用点）

- [FP32Quantizer&lt;metric&gt;::ProcessQueryImpl · L144](fp32_quantizer.md#L144)（4 个显式调用点）

- [FP32Quantizer&lt;metric&gt;::ComputeDistImpl · L164](fp32_quantizer.md#L164)（3 个显式调用点）

- [FP32Quantizer&lt;metric&gt;::ComputeDistsBatch4Impl · L191](fp32_quantizer.md#L191)（3 个显式调用点）

- [FP32Quantizer&lt;metric&gt;::ReleaseComputerImpl · L261](fp32_quantizer.md#L261)（1 个显式调用点）


### [src/impl/cluster/kmeans_cluster.cpp](kmeans_cluster.md)

- [KMeansCluster::KMeansCluster · L34](kmeans_cluster.md#L34)（1 个显式调用点）

- [KMeansCluster::~KMeansCluster · L41](kmeans_cluster.md#L41)（1 个显式调用点）

- [KMeansCluster::Run · L48](kmeans_cluster.md#L48)（51 个显式调用点）

- [KMeansCluster::find_nearest_one_with_hgraph · L230](kmeans_cluster.md#L230)（29 个显式调用点）

- [KMeansCluster::select_initial_centroids_random · L290](kmeans_cluster.md#L290)（1 个显式调用点）

- [KMeansCluster::select_initial_centroids_kmeans_plus_plus · L305](kmeans_cluster.md#L305)（5 个显式调用点）


### [src/impl/cluster/nearest_centroid_assign.cpp](nearest_centroid_assign.md)

- [NearestCentroidAssign · L39](nearest_centroid_assign.md#L39)（24 个显式调用点）


### [src/impl/distance_provider_for_graph.h](distance_provider_for_graph_h.md)

- [DistanceProviderForGraph::~DistanceProviderForGraph · L33](distance_provider_for_graph_h.md#L33)（0 个显式调用点）

- [DistanceProviderForGraph::BatchQueryDistance · L38](distance_provider_for_graph_h.md#L38)（1 个显式调用点）

- [DistanceProviderForGraph::SupportsComputerById · L56](distance_provider_for_graph_h.md#L56)（0 个显式调用点）

- [DistanceProviderForGraph::Prefetch · L61](distance_provider_for_graph_h.md#L61)（0 个显式调用点）

- [DistanceProviderForGraph::OriginalId · L65](distance_provider_for_graph_h.md#L65)（0 个显式调用点）

- [DistanceProviderForGraph::IsValid · L70](distance_provider_for_graph_h.md#L70)（0 个显式调用点）

- [FlattenDistanceProvider::FlattenDistanceProvider · L78](distance_provider_for_graph_h.md#L78)（0 个显式调用点）

- [FlattenDistanceProvider::QueryDistance · L82](distance_provider_for_graph_h.md#L82)（1 个显式调用点）

- [FlattenDistanceProvider::BatchQueryDistance · L89](distance_provider_for_graph_h.md#L89)（1 个显式调用点）

- [FlattenDistanceProvider::PairwiseDistance · L97](distance_provider_for_graph_h.md#L97)（1 个显式调用点）

- [FlattenDistanceProvider::FactoryComputerById · L102](distance_provider_for_graph_h.md#L102)（1 个显式调用点）

- [FlattenDistanceProvider::Prefetch · L108](distance_provider_for_graph_h.md#L108)（1 个显式调用点）

- [FlattenIdDistanceProvider::FlattenIdDistanceProvider · L120](distance_provider_for_graph_h.md#L120)（0 个显式调用点）

- [BucketDistanceProvider::SupportsComputerById · L184](distance_provider_for_graph_h.md#L184)（0 个显式调用点）


### [src/impl/searcher/basic_searcher.cpp](basic_searcher.md)

- [BasicSearcher::BasicSearcher · L35](basic_searcher.md#L35)（0 个显式调用点）

- [BasicSearcher::BasicSearcher · L39](basic_searcher.md#L39)（0 个显式调用点）

- [BasicSearcher::visit · L43](basic_searcher.md#L43)（9 个显式调用点）

- [BasicSearcher::Search · L76](basic_searcher.md#L76)（2 个显式调用点）

- [BasicSearcher::SearchWithPresetComputer · L107](basic_searcher.md#L107)（2 个显式调用点）

- [BasicSearcher::Search · L139](basic_searcher.md#L139)（1 个显式调用点）

- [BasicSearcher::Search · L158](basic_searcher.md#L158)（2 个显式调用点）

- [BasicSearcher::search_impl · L174](basic_searcher.md#L174)（79 个显式调用点）

- [BasicSearcher::search_impl · L322](basic_searcher.md#L322)（102 个显式调用点）

- [BasicSearcher::search_impl · L551](basic_searcher.md#L551)（146 个显式调用点）

- [BasicSearcher::SetRuntimeParameters · L938](basic_searcher.md#L938)（3 个显式调用点）

- [BasicSearcher::SetMockParameters · L951](basic_searcher.md#L951)（0 个显式调用点）

- [BasicSearcher::MockRun · L966](basic_searcher.md#L966)（15 个显式调用点）

- [BasicSearcher::SetMutexArray · L997](basic_searcher.md#L997)（2 个显式调用点）


### [src/algorithm/inner_index_interface.cpp](inner_index_interface.md)

- [InnerIndexInterface::create_search_filter · L1108](inner_index_interface.md#L1108)（6 个显式调用点）

- [InnerIndexInterface::pack_knn_result · L1140](inner_index_interface.md#L1140)（9 个显式调用点）

- [InnerIndexInterface::filter_search_result_by_threshold · L1156](inner_index_interface.md#L1156)（10 个显式调用点）


### [src/index/index_impl.h](index_impl_h.md)

- [IndexImpl::Build · L94](index_impl_h.md#L94)（2 个显式调用点）

- [IndexImpl::KnnSearch · L308](index_impl_h.md#L308)（8 个显式调用点）

- [IndexImpl::KnnSearch · L324](index_impl_h.md#L324)（8 个显式调用点）

- [IndexImpl::KnnSearch · L340](index_impl_h.md#L340)（8 个显式调用点）

- [IndexImpl::KnnSearch · L356](index_impl_h.md#L356)（102 个显式调用点）

- [IndexImpl::KnnSearch · L380](index_impl_h.md#L380)（8 个显式调用点）

- [IndexImpl::SearchWithRequest · L505](index_impl_h.md#L505)（39 个显式调用点）


### [src/utils/util_functions.cpp](util_functions.md)

- [select_k_numbers · L43](util_functions.md#L43)（7 个显式调用点）

- [sample_train_data · L234](util_functions.md#L234)（36 个显式调用点）


### [src/impl/pruning_strategy.cpp](pruning_strategy.md)

- [PairwiseDistanceComputer::PairwiseDistanceComputer · L29](pruning_strategy.md#L29)（0 个显式调用点）

- [PairwiseDistanceComputer::PairwiseDistanceComputer · L34](pruning_strategy.md#L34)（0 个显式调用点）

- [PairwiseDistanceComputer::& operator= · L35](pruning_strategy.md#L35)（0 个显式调用点）

- [PairwiseDistanceComputer::PairwiseDistanceComputer · L37](pruning_strategy.md#L37)（0 个显式调用点）

- [PairwiseDistanceComputer::& operator= · L38](pruning_strategy.md#L38)（0 个显式调用点）

- [PairwiseDistanceComputer::PairwiseDistance · L41](pruning_strategy.md#L41)（4 个显式调用点）

- [select_edges_by_heuristic · L61](pruning_strategy.md#L61)（9 个显式调用点）

- [select_edges_by_heuristic · L84](pruning_strategy.md#L84)（14 个显式调用点）

- [mutually_connect_new_element · L129](pruning_strategy.md#L129)（28 个显式调用点）

- [select_edges_by_heuristic · L205](pruning_strategy.md#L205)（1 个显式调用点）

- [select_edges_by_heuristic · L216](pruning_strategy.md#L216)（1 个显式调用点）

- [mutually_connect_new_element · L226](pruning_strategy.md#L226)（1 个显式调用点）


### [src/impl/label_table/label_table.cpp](label_table.md)

- [LabelTable::TryGetIdByLabel · L96](label_table.md#L96)（3 个显式调用点）

- [LabelTable::GetIdByLabel · L116](label_table.md#L116)（3 个显式调用点）

- [LabelTable::MarkRemove · L126](label_table.md#L126)（6 个显式调用点）


### [src/impl/filter/inner_id_wrapper_filter.h](inner_id_wrapper_filter_h.md)

- [InnerIdWrapperFilter::InnerIdWrapperFilter · L25](inner_id_wrapper_filter_h.md#L25)（0 个显式调用点）

- [InnerIdWrapperFilter::CheckValid · L28](inner_id_wrapper_filter_h.md#L28)（2 个显式调用点）

- [InnerIdWrapperFilter::ValidRatio · L33](inner_id_wrapper_filter_h.md#L33)（1 个显式调用点）

- [InnerIdWrapperFilter::FilterDistribution · L38](inner_id_wrapper_filter_h.md#L38)（1 个显式调用点）

- [InnerIdWrapperFilter::GetValidIds · L43](inner_id_wrapper_filter_h.md#L43)（1 个显式调用点）


### [src/impl/filter/combined_filter.h](combined_filter_h.md)

- [CombinedFilter::CombinedFilter · L25](combined_filter_h.md#L25)（0 个显式调用点）

- [CombinedFilter::~CombinedFilter · L27](combined_filter_h.md#L27)（0 个显式调用点）

- [CombinedFilter::AppendFilter · L29](combined_filter_h.md#L29)（1 个显式调用点）

- [CombinedFilter::CheckValid · L37](combined_filter_h.md#L37)（1 个显式调用点）

- [CombinedFilter::ValidRatio · L47](combined_filter_h.md#L47)（1 个显式调用点）

- [CombinedFilter::IsEmpty · L56](combined_filter_h.md#L56)（1 个显式调用点）


## 生成与核对范围

使用 tree-sitter C++ 语法树提取函数定义与 call_expression，未做编译器级重载解析。宏、条件编译、隐式构造/析构不冒充运行时调用栈。命名类型转换（static_cast 等）保留在源码中，不计入函数调用数。函数的原始字节摘要与行号保存在 [核对清单](manifest.json)，以后升级源码可据此检查摘录是否过期。


解析器在以下源码遇到宏/语法恢复节点，完整函数体仍按原始字节保留；这些区域的自动调用点索引不能声称穷尽宏展开结果：

- `src/index/index_impl.h`：行 86, 86, 98, 98, 104, 104, 111, 112, 119, 120, 129, 129, 139, 139, 169, 169, 203, 203, 232, 232, 239, 239, 244, 244, 249, 249, 279, 279, 300, 300, 321, 321, 337, 337, 353, 353, 367, 369, 370, 371, 372, 373, 373, 375, 375, 376, 376, 376, 395, 395, 410, 410, 422, 422, 434, 434, 447, 447, 461, 461, 475, 475, 482, 482, 487, 487, 563, 600, 600, 606, 606, 615, 615, 621, 637, 637, 642, 642, 642
