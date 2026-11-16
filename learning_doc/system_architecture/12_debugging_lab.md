# 本地调试实验：用六条向量读通一次真实查询

[深入阅读路线](00_deep_reading_roadmap.md) · [请求全链路](07_query_request_pipeline.md) · [完整教学程序](labs/trace_search.cpp) · [本轮观测结果](labs/observed_results.json)

源码基线：`fd363937`。本章的编译、普通运行、诊断运行，以及 HGraph 查询入口断点均在本轮实际验证。文末进一步下钻的断点和扩展实验是建议步骤，未把它们计为已完成实验。

## 1. 实验范围与要回答的问题

固定 6 条 FP32 向量、4 维、平方 L2，一个 query；分别创建 BruteForce 和 HGraph，检查普通 top-k、过滤、threshold、BinarySet 往返及非法 topk。
HGraph 使用 FP32 基础编码、关闭精排，`max_degree=8`、`ef_construction=32`、`build_thread_count=1`、查询 `ef_search=8`。
这些设置让你把注意力放在请求、ID、距离、过滤与结果上。

这个样本不用于测性能。本轮 HGraph 序列化信息显示 `max_level=0`，说明这次小图没有形成额外的上层导航图；上层路由应结合 [层间路由专章](../indexes/hgraph/traversal_walkthrough.md) 和更大样本阅读，不能从本程序推断每个图都存在三层。

即使本例 HGraph 返回手算的精确结果，也不能推出对任意图、数据规模和预算都有精确保证。

## 2. 输入与手算答案

query 为 `q=(1,1,0,0)`，距离是 `sum((q[d]-x[d])²)`。

| 输入位置 | 外部 label | 向量 | 到 query 的平方 L2 |
| --- | --- | --- | --- |
| 0 | 101 | `(0,0,0,0)` | `1+1=2` |
| 1 | 305 | `(1,0,0,0)` | `0+1=1` |
| 2 | 9001 | `(1,1,0,0)` | `0` |
| 3 | 42 | `(3,1,0,0)` | `4` |
| 4 | 77 | `(0,4,0,0)` | `1+9=10` |
| 5 | 880 | `(5,5,0,0)` | `16+16=32` |

答案不存在并列距离，所以本例可以直接比较有序的 ID 与距离。
向量使用 4 维只是为了让计算简单；它不是 VSAG 只支持 4 的倍数维度的约束。

## 3. 在当前 Mac 上编译与运行

完整程序放在 [labs/trace_search.cpp](labs/trace_search.cpp)。它只调用公共 API，不需要把内部头文件全部加入 include path，也不修改库源码。
当前库已经位于 `build/src/libvsag.1.0.0.dylib`，为 Debug 构建；本机 macOS 是 26.3.2，库的 `CMAKE_OSX_DEPLOYMENT_TARGET` 为 26.3。
下面命令匹配这次已有库的配置：

```bash
cd /Users/lzh/Desktop/code/vsag
clang++ -std=c++17 -O0 -g -Wall -Wextra \
  -mmacosx-version-min=26.3 \
  -isystem /Users/lzh/Desktop/code/vsag/include \
  learning_doc/system_architecture/labs/trace_search.cpp \
  -L /Users/lzh/Desktop/code/vsag/build/src -lvsag \
  -Wl,-rpath,/Users/lzh/Desktop/code/vsag/build/src \
  -o /tmp/vsag-trace-search

/tmp/vsag-trace-search brute_force
/tmp/vsag-trace-search hgraph
/tmp/vsag-trace-search brute_force reasoning
/tmp/vsag-trace-search hgraph reasoning
```

`-g -O0` 为教学程序保留调试信息；库本身也必须带有对应源码的调试信息。
`-isystem` 将依赖公共头文件作为系统头文件处理，减少公共接口默认实现中的 unused-parameter 警告；不会关闭本程序自身的 `-Wall -Wextra` 检查。
rpath 告诉动态加载器从当前库目录寻找 VSAG。部署版本参数是本次本地构建值，移到其他机器或重建库后应与实际构建配置重新核对。

这是一条独立样例编译命令。整库的 [compile_commands.json](../../compile_commands.json) 仍由 CMake 生成；该独立教学程序不是当前 CMake 示例目标的一部分。

## 4. 每次运行会检查五件事

| 检查 | 输入变化 | 期望结果 |
| --- | --- | --- |
| plain | topk=3 | `9001:0、305:1、101:2` |
| exclude-305 | `Filter::CheckValid(305)` 返回 false | `9001:0、101:2、42:4` |
| threshold-0.5 | topk 仍为 3，阈值为 0.5 | 只有 `9001:0` |
| roundtrip | Serialize 为 BinarySet，再恢复到新空索引 | 恢复后仍为 `9001:0、305:1、101:2` |
| topk-0 | 非法 k=0 | `expected` 返回错误，ErrorType 为 INVALID_ARGUMENT |

程序同时检查 Build 返回的失败 ID 列表为空，并确认元素数为 6。
它不只检查 `has_value()`：一次部分成功的批量 Build 可能仍返回值，但值里面含失败 ID。
错误检查若失败，程序会打印 `FAIL` 并返回非零退出码，不会继续把失败结果当正常 Dataset 使用。

## 5. 实际输出摘录与形状解释

两个索引的业务输出均与下面内容一致；为方便阅读，摘录省略库初始化日志、序列化内部日志和诊断 JSON。

```text
plain rows=1 results=3
  label=9001 distance=0
  label=305 distance=1
  label=101 distance=2
exclude-305 rows=1 results=3
  label=9001 distance=0
  label=101 distance=2
  label=42 distance=4
threshold-0.5 rows=1 results=1
  label=9001 distance=0
roundtrip rows=1 results=3
  label=9001 distance=0
  label=305 distance=1
  label=101 distance=2
topk-0 error_type=3
PASS: four answer checks and one error-boundary check
```

`rows=1` 来自结果的 `GetNumElements()`；本例只有一个 query。
`results` 来自结果的 `GetDim()`，在这一结果对象中表示实际返回槽数；它不是原始向量维度 4。
因此遍历结果应使用实际结果形状，不能始终按输入 dim 或请求的 k 读取指针。

`error_type=3` 对应本提交的 `INVALID_ARGUMENT` 枚举。业务代码应比较枚举，而不是把数字 3 当长期不变的协议。

## 6. 先停在 Dataset：指针是谁的

程序用 `std::vector` 保存 IDs 与向量，再用 Dataset 包装它们：

```cpp
auto base = vsag::Dataset::Make()
                ->NumElements(static_cast<int64_t>(ids.size()))
                ->Dim(4)
                ->Ids(ids.data())
                ->Float32Vectors(vectors.data())
                ->Owner(false);
```

这是教学程序的排版摘录。`Owner(false)` 表示 Dataset 不负责释放这些 vector 的 data()，而不是要求索引以后每次查询都从这个外部数组读取。
本程序让这些 vector 在整个 main 期间保持有效，并且不做会使其地址失效的重新分配。
索引 Build 如何编码并保存输入数据，应继续看 [08 的插入字节路径](08_storage_byte_path.md)。

返回的结果 Dataset 有自己的生命周期。只要还要使用 `GetIds()`、`GetDistances()`、`GetReasoning()` 返回的数据，就保持结果对象存活；不要把指针留下后立刻销毁承载对象。

## 7. 再停在 SearchRequest：一次只改变一个条件

普通请求的教学代码是：

```cpp
vsag::SearchRequest request;
request.query_ = query;
request.topk_ = 3;
request.params_str_ = name == "hgraph" ? R"({"hgraph":{"ef_search":8}})" : "{}";
```

`query_` 是借用输入缓冲的 Dataset 对象；`topk_` 描述目标结果数量；`params_str_` 则由具体索引解析。
同样一段外部调用进入 BruteForce 时是全量扫描，进入 HGraph 时是图搜索，不是公共 SearchRequest 自己选择每条图边。

`auto filtered = request` 复制请求字段，用来改变本次请求条件。Dataset 和 Filter 等 shared_ptr 的复制不是深拷贝整份向量；本样例没有并发修改这些共享输入。

## 8. 过滤、阈值与候选是三个不同位置的问题

本例自定义 `Exclude305`，其 `CheckValid` 返回 `label != 305`。
这意味着 true 是“允许返回”。它与一些 Bitset 或函数式过滤包装的布尔约定不能混用，应在适配层核对。
程序也设置 `enable_filter_=true`，但具体实现是否用该 flag 控制传入 Filter，必须跟 [06](06_api_factory_dataset.md) 和 [07](07_query_request_pipeline.md) 的代码读；不能只看接口注释猜执行条件。

在 BF 中，该条非法记录可在正常扫描评分前跳过，所以本轮过滤请求的 `dist_cmp` 是 5。
在 HGraph 中，不允许返回的点仍可能参与导航，本轮过滤请求的 `dist_cmp` 仍为 6；这与“不返回 label 305”并不冲突。

threshold 请求没有设置 Filter。它要求输出距离不超过 0.5，而本例只有一个点满足；请求 k=3 表示至多返回 3 个，不保证补齐不满足阈值的记录。

## 9. 诊断为什么让 6 次看起来变成 8 次

传入第二个参数 `reasoning` 后，程序设置 `expected_labels_={9001,305}` 并打印每次返回 Dataset 中的 statistics 和 reasoning。
下表是这次实际观测，完整结构见 [observed_results.json](labs/observed_results.json)。

| 请求 | BF dist_cmp | BF distance_evaluations | HGraph dist_cmp | HGraph distance_evaluations |
| --- | --- | --- | --- | --- |
| plain | 6 | 8 | 6 | 8 |
| exclude-305 | 5 | 7 | 6 | 8 |
| threshold-0.5 | 6 | 8 | 6 | 8 |
| roundtrip | 6 | 8 | 6 | 8 |

这里两组计数不是同一个概念的重复字段。正常扫描或图搜索之外，诊断初始化还为两个 expected targets 计算参考距离；DataCell 的距离计数记录这些计算，而局部正常搜索 `dist_cmp` 不因此加二。
BF 的具体证据在 [bruteforce.cpp](../../src/algorithm/bruteforce/bruteforce.cpp) 441–479 行：先初始化 expected targets，再调用 `inner_codes_->Query` 计算参考距离，然后才创建后续搜索使用的 `dist_cmp`。
HGraph 的对应初始化位于 [hgraph_search.cpp](../../src/algorithm/hgraph/hgraph_search.cpp) 的 `Setup reasoning context` 分支。

因此，开关诊断后不能直接用一个总距离计数差异认定算法发生了多次重复遍历。还要注意诊断可能改变某些实现的线程执行方式，诊断模式不用于直接比较正常模式性能。

## 10. 怎样读 reasoning，而不是盲信一句 diagnosis

本例普通请求的报告摘要为：

```json
{"expected_analysis":{"missed_targets":[],"summary":"2/2 expected labels found, 0 missed"}}
```

排除 305 后，报告会包含 `label=305`、`diagnosis="filter_rejected"`、`true_distance=1.0`。
这说明目标没有出现在输出里，是过滤使然；它并不是算法漏掉了一个允许返回的目标。
在 BF 的该条诊断中，`quantized_distance` 字段可以是默认值 0.0，不能把默认字段解释成实际评分得到零距离；应结合 `filter_rejected`、参考距离及对应记录分支理解。

本轮 threshold 请求里，305 已访问、参考距离为 1，但报告的 `diagnosis` 是 `unknown`。
原因判断需要结合请求的 threshold=0.5：该点不符合输出约束。诊断分类没有覆盖所有输出约束情形，因此 `unknown` 不能直接解释成“图没有访问到”。

API 的 `GetReasoning()` 返回字符串引用；本实现的报告内容是 JSON 文本。先保证结果 Dataset 存活，再按需要解析，并允许未启用时为空字符串。

## 11. 已验证的 LLDB 入口

本轮已用 LLDB 实际停在 `vsag::HGraph::SearchWithRequest`，读到 `request.topk_=3`，并得到下面的调用链，省略地址和系统启动帧：

```text
HGraph::SearchWithRequest                  hgraph_search.cpp:510
IndexImpl<HGraph>::SearchWithRequest        index_impl.h:560
CheckResults                              trace_search.cpp:46
main                                      trace_search.cpp:125
```

可以在终端执行：

```text
lldb /tmp/vsag-trace-search
(lldb) breakpoint set -n vsag::HGraph::SearchWithRequest
(lldb) run hgraph
(lldb) frame variable request.topk_
(lldb) bt 6
```

此时停在查询入口，Build 已经完成，适合看本次请求的实际对象。
一次运行会先后执行 plain、过滤、threshold、roundtrip 和非法 k，请结合当前调用者的 `title` 字段区分正在观察哪个案例。
需要退出这次调试会话时，使用 `process kill` 结束这个自己启动的教学进程，再 `quit`。

## 12. 接下来逐层下钻，观察哪些变量

下面是下一步建议路线，除上一节入口外，本轮没有逐一执行全部断点。

| 停止位置 | 观察内容 | 要回答的问题 |
| --- | --- | --- |
| `IndexImpl<T>::SearchWithRequest` | request、Filter 包装、inner_index_ | 公共请求有没有被重组或转换 |
| `HGraph::SearchWithRequest` | params、k、entry_point_id_、route_graphs_、ctx | 本次有哪些层，进入哪条底层路径 |
| `HGraph::search_one_graph` 普通重载 | graph、flatten、search_param、vt | 搜索当前层还是下一层，visited 是否重置 |
| `BasicSearcher::search_impl` 普通路径 | ef、candidate_set、top_candidates、lower_bound | 谁待扩展、谁被保留、为何停止 |
| `BasicSearcher::visit` | neighbors、vl、to_be_visited_id | 哪些 ID 被首次发现并交给评分 |
| `FlattenDataCell::Query` | idx、count、codes大小、is_in_memory_ | 一次请求几个编码，怎样取得字节 |
| FP32 量化器和距离核 | query、code、metric、dim | L2 结果怎样累计出来 |
| 结果收尾 | 内部 ID、外部 label、有效数量 | 何时过滤或截断，怎样恢复外部身份 |

在 HGraph 查询入口暂停后，才为 BasicSearcher 增加更细断点，可以避免先被构图过程中使用的搜索器反复打断。
例如按当前基线可以在 `basic_searcher.cpp:757` 观察普通 KNN 停止判断，读取当前帧的 `ef` 和 `lower_bound`；行号应随源码更新重新确认。

模板与重载可能让同一名字解析成多个位置。已实际确认 `search_one_graph` 有普通路径与 iterator 相关路径的符号，不能把所有命中都当成当前执行路径。

## 13. 为什么这个小样本还不足以观察所有优化

BF 默认扫描每条记录时可以向 DataCell 提交单个 ID，未必触发其四条一组的批量分支。
HGraph 展开邻居时可一次收集多个未访问 ID，才可能观察到批量读取和打分。
这解释了为什么同一底层组件有批量优化，却不是每个调用者都走相同分支。

本轮初始化日志确认 NEON 的 `using:Y`、SVE 的 `using:N`，即使编译配置中包含相应支持，也不能推断本机运行了 SVE；这条日志也不证明每个距离函数都必定使用 NEON。具体派发见 [09](09_quantization_simd.md)。

## 14. 可继续做的扩展实验

这些扩展尚未执行，修改样例后应同步修改手算答案与比较方式。

- 增加固定种子数据到数百条，观察 route_graphs_ 和 entry 的实际生成；不要指定一个未经构建保证的固定上层拓扑。
- 固定同一已建 HGraph，只改变 ef_search，并用独立 FP32 全扫描结果判断召回。
- 改为非 SIMD 宽度倍数的维度，例如 6，跟踪尾部元素仍被累计的分支。
- 用显式训练分布切换 SQ8，区分量化前后分数与候选覆盖；不再直接使用 FP32 精确答案断言压缩分数逐项相同。
- 使用真实删除模式另做删除与恢复实验。当前 roundtrip 用的是未删除集合，不为删除标记持久化作保证；相关边界见 [10](10_labels_filters_lifecycle.md)。

每次只加一个因素，并在笔记里写下所用配置、实际分支与观测，不把单个样本的成功外推为所有配置的承诺。
