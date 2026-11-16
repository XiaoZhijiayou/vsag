# IVF：本地实测的完整调用栈

[主讲解](code_walkthrough.md) · [静态递归调用树](call_trees.md) · [完整源码参考](function_reference/README.md)

采集日期：2026-09-10。源码 `fd363937`，macOS arm64，本地 Debug 动态库。使用本目录的 [trace_ivf.cpp](labs/trace_ivf.cpp)。本页是实际运行记录，不是根据函数名字拼出的示意栈。

## 1. 固定这次到底执行了哪一种 IVF

使用 6 条四维 FP32 向量、L2 平方距离、2 个桶。训练方式为 random，中心路由使用扫描，桶内使用平扫，无残差、无精排，查询扫描全部 2 个桶，query 为 `(1,1,0,0)`，k=3。随机选中心可能改变各桶的成员和大小，但扫全部桶时下面的答案保持不变。

`train_sample_count=512` 是合法的采样上限；本例只有 6 条，采样函数使用已有输入，并不会制造 512 条数据。外部 IVF 参数没有加入 `build_thread_count`；内部默认值为 1，查询 `parallelism=1`。

## 2. 从入口到距离函数，14 层都保留

下列保留原始 `bt` 的全部帧编号、函数和源码位置，去掉了随机地址与冗长模板参数。原始输出在 [lldb_stack.txt](labs/lldb_stack.txt)，可查看未简写的模板实参、函数参数、指针和值。

```text
#13 dyld::start
 └─ #12 main                                      trace_ivf.cpp:124
    └─ #11 CheckResults                            trace_ivf.cpp:46
       └─ #10 IndexImpl<IVF>::SearchWithRequest      index_impl.h:560
          └─ #9 IVF::SearchWithRequest              ivf_search.cpp:768
             └─ #8 IVF::search<KNN_SEARCH>          ivf_search.cpp:279
                └─ #7 search_func::operator()       ivf_search.cpp:260
                   └─ #6 FlatBucketSearcher::Search flat_bucket_searcher.cpp:43
                      └─ #5 BucketDataCell<FP32,L2,MemoryIO>::ScanBucketById
                         │                         bucket_datacell.h:68
                         └─ #4 ...::scan_bucket_by_id
                            │                      bucket_datacell.h:538
                            └─ #3 Computer<FP32>::ScanBatchDists
                               │                   computer.h:70
                               └─ #2 Quantizer<FP32>::ScanBatchDists
                                  │                quantizer.h:235
                                  └─ #1 FP32Quantizer<L2>::ScanBatchDistImpl
                                     │             fp32_quantizer.cpp:139
                                     └─ #0 FP32Quantizer<L2>::ComputeDistImpl
                                                   fp32_quantizer.cpp:182
```

`BucketDataCell<FP32,L2,MemoryIO>` 是便于阅读的缩写，实际模板参数是 `BucketDataCell<FP32Quantizer<METRIC_TYPE_L2SQR>, MemoryIO>`。`KNN_SEARCH` 对应原始栈中的 `InnerSearchMode` 数值 1；L2SQR 对应 MetricType 数值 0。

## 3. 每一层到底做什么，怎样把参数交给下一层

| 帧 | 输入、状态与调用理由 | 返回时交给上层什么 |
| --- | --- | --- |
| #13 dyld | 操作系统启动程序，完成动态库装载后进入 main | 进程退出状态；不是 IVF 算法层 |
| #12 main | 创建数据、索引并 Build；准备 SearchRequest | 收集检查结果，最终给出程序退出码 |
| #11 CheckResults | 接收 index、request、期望 IDs/距离；调用统一查询 API | 验证结果形状、顺序和距离；不修改索引 |
| #10 IndexImpl | 公共 Index 接口的 IVF 适配器，先做外层检查，通过 SAFE_CALL 调用内部索引 | 将内部 Dataset/异常适配为公开 expected 返回值 |
| #9 SearchWithRequest | 解析请求、准备参数和统计；本例走单 query 普通 KNN，无精排 | 收到候选堆后阈值处理、封装 Dataset、附统计 |
| #8 search | 已完成路由和 Computer 创建；本例同步调用 `search_func(0)` | 返回整次查询的候选堆；多归属桶时还会去重 |
| #7 lambda | 根据原子桶游标领取桶，传入本线程 heap/dist、query computer、topk | 修改本线程的候选堆，不单独构造最终 Dataset |
| #6 FlatBucketSearcher | 当前桶 ID=0、topk=3、buckets_per_data=1；取桶大小与 posting IDs | 扫描返回后逐条过滤、入堆；返回 void |
| #5 ScanBucketById | 接口接收 ComputerInterfacePtr，将其转换成模板计算器 | 直接转发下层，无额外候选筛选 |
| #4 scan_bucket_by_id | 桶共享锁、offset、code_size；Acquire 编码块，交出字节指针 | 距离写入 result_dists；然后执行必要补偿/空槽处理 |
| #3 Computer | 持有本次 query 预处理缓冲；把 count、codes、dists 交给量化器 | 输出缓冲就地写入，没有创建一组业务结果 |
| #2 Quantizer | CRTP 模板转发，`cast().ScanBatchDistImpl(...)` | 使用实际 FP32 实现完成批算分 |
| #1 FP32 ScanBatchDistImpl | 对 count 条编码循环，按 code_size 移动编码指针，按 1 移动距离指针 | 每条输出槽写入距离，批量返回 void |
| #0 FP32 ComputeDistImpl | 当前编码、computer.buf_ 中的 query、dim；进入 L2SQR 分支 | 调用 FP32ComputeL2Sqr 并将值写入 `*dists` |

这次停在 `#0` 调用 `FP32ComputeL2Sqr` 的源码行，尚未进入该函数，因此原始 `bt` **没有这个更深的帧**。继续 `thread step-in` 才能观察所选 SIMD 实现；不能把预计下一步会执行的函数加进已采集的栈。

本次首个停点 `count=5`、`bucket_id=0`、`thread_id=0`、`topk=3`，`reasoning_ctx=nullptr`。`computer.raw_query_` 为空，与未启用残差的配置一致。另一个桶尚未在这个栈快照中执行。

## 4. 为什么这条栈没有 Train、中心路由和 pack_knn_result

Train 属于之前已完成的 Build。中心路由是在 `search` 进入桶 lambda 前已经返回的调用。结果封装则要等本次搜索返回后才发生。它们都属于完整执行流程，但不同时存在于这张活动栈上。

如果希望观察这些阶段，把断点分别放在 Train、ClassifyDatas、pack_knn_result 中，每次停住后执行 `bt`，会得到不同快照。静态的所有可能调用关系应看 [递归调用树](call_trees.md)，不要把所有分支硬拼成一条运行时栈。

## 5. 可以直接复现的命令

在仓库根目录执行，输出二进制放 `/tmp`：

```bash
clang++ -std=c++17 -O0 -g -Wall -Wextra \
  -mmacosx-version-min=26.3 \
  -isystem /Users/lzh/Desktop/code/vsag/include \
  /Users/lzh/Desktop/code/vsag/learning_doc/indexes/ivf/labs/trace_ivf.cpp \
  -L /Users/lzh/Desktop/code/vsag/build/src -lvsag \
  -Wl,-rpath,/Users/lzh/Desktop/code/vsag/build/src \
  -o /tmp/vsag-trace-ivf

/tmp/vsag-trace-ivf
lldb /tmp/vsag-trace-ivf
```

```lldb
breakpoint set -r 'FP32Quantizer.*ComputeDistImpl'
run
bt
frame variable
```

原始采集使用同一份教学源码在临时目录编译，随后将源码放入当前 `labs` 目录；文档中的上述命令直接使用最终文件路径。原始日志中调试结束后的 `process kill` 是主动结束已停住的教学进程，不是搜索崩溃。正常运行的验证输出另见 [run_results.txt](labs/run_results.txt)。

## 6. 实际答案与边界观察

| 操作 | IDs（按距离升序） | 距离 |
| --- | --- | --- |
| 普通 k=3 | 9001、305、101 | 0、1、2 |
| 排除 label 305 | 9001、101、42 | 0、2、4 |
| threshold=0.5 | 9001 | 0 |
| BinarySet 保存后新对象加载 | 9001、305、101 | 0、1、2 |

这四项由程序实际检查，均通过。另做了 `topk=0` 的边界观察：当前这个普通 IVF SearchWithRequest 路径接受请求并返回 0 个结果。没有将它写成“成功拒绝非法参数”，也没有把 BF/HGraph 示例的行为照搬到 IVF。自定义距离、批查询等分支有自己的正 k 检查，不能由这个单条普通查询结果推断所有分支都接受 0。

本次未修改索引实现；该记录用于解释当前基线各分支的行为，不是对全部配置的功能保证。
