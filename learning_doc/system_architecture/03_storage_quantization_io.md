# DataCell、量化、Layout 与 IO

## 1. 四个不同问题

| 抽象 | 回答的问题 | 例子 |
| --- | --- | --- |
| DataCell | 记录是什么，如何写入和参与计算？ | 稠密向量、邻接表、桶内向量、稀疏 posting、多向量文档 |
| Quantizer / Computer | 怎样编码，怎样对一个 query 打分？ | FP32、SQ、PQ、RaBitQ；查询专属计算状态 |
| Layout | 记录 ID 对应哪个字节区间？ | 固定长度记录、可变长度记录 |
| IO | 字节怎样读取，谁拥有读取结果？ | 内存访问、文件读取、mmap、缓存、Reader |

[FlattenDataCell](../../src/datacell/flatten_datacell.h) 是阅读稠密编码的起点；[MultiVectorDataCell](../../src/datacell/multi_vector_datacell.h) 用于对照一条记录包含多个 token 的情况。

## 2. 为什么把 Quantizer 和查询 Computer 分开

量化器持有训练后模型和编码规则，供整个索引复用；查询计算器持有当前 query 所需的数据。例如查询变换、查表和其他预计算，不应为每个候选都重复创建。

这让算法通过 `FactoryComputer` 与批量 `Query` 等接口打分，而不必自己展开每种量化格式。HGraph 还使用 [QueryComputerPool](../../src/impl/query_computer_pool.h) 在适用路径复用查询侧状态。

代价是要明确计算器生命周期与线程共享规则：共享只读模型和共享可变 query 缓冲区不是一回事。SIMQ 还存在索引级可复用粗排缓冲区，查询因此使用独占锁，详见其专章。

## 3. 压缩节省什么，损失什么

以下仅估计每条维度为 D 的向量的主要编码大小，不含范数、码本、对齐、图边、label、缓存等额外成本。

| 表示 | 主要编码体积直觉 | 代价 |
| --- | --- | --- |
| FP32 | 约 4D 字节 | 占用和内存带宽较高 |
| FP16 / BF16 | 约 2D 字节 | 精度变化可能改变近距离候选排序 |
| SQ8 / SQ4 | 约 D / D÷2 字节 | 标量离散化误差及训练分布适配问题 |
| PQ | 用子空间码替换原向量 | 需要训练码本，误差取决于子空间划分与数据 |
| RaBitQ 及 split 变体 | 按位编码，另带辅助数据 | 有特定的变换、估计和重排实现约束 |

量化往往减少内存访问，但增加解码或查询预处理；更小的表示不必然在所有维度和硬件上更快。内部编码类型也不能反推外部 API 的输入类型，例如 FP16 编码配置不自动意味着接受 FP16 输入 Dataset。

## 4. 基础编码、精排表示与原始向量

基础编码用于大量候选的低成本评分；精排对小候选集用更准确的表示重算；原始向量存储服务于保留原始输入等需求。三者可能共用数据，也可能分别占用空间，要查当前参数映射。

HGraph 的 RaBitQ split 有从 base 进行重排的配置，不能认为 `use_reorder` 一定多存一份 FP32。`store_raw_vector` 也不等价于所有算法都会开放原始向量读取能力。

**设计原因：** 用少量昂贵计算弥补大量廉价计算的误差。**边界：** 精排只能重排已有候选，找不回未搜索的图区域、未扫描的桶或被剪掉的文档。

## 5. Layout：记录 ID 不等于字节地址

[FixedLayout](../../src/layout/fixed_layout.h) 明确把 ID 映射为 `[id × code_size, (id+1) × code_size)`，并检查大小和偏移溢出；它把内容当作不透明字节。可变记录的职责见 [variable_record_layout.h](../../src/layout/variable_record_layout.h)。

同一条文档的 token 数、某词项 posting 长度都可能不同，不能套用固定长度公式。把寻址独立出来有利于统一读写、批量访问和范围检查，同时避免算法自行复制复杂偏移计算。

## 6. ByteIO：后端、缓存与读结果生命周期

[ByteIO](../../src/io/core/byte_io.h) 组合 `Backend` 与 `CachePolicy`，提供 `ReadAt`、`ReadMany`、`SubmitReads`、`Acquire` 等操作。Backend 负责具体介质；缓存策略负责命中、失效和读缓冲等行为。

`Acquire` 返回的 Lease 描述所读数据的有效生命周期。内存后端可以借用已有地址，文件后端可能需要额外缓冲；上层不能假定指针永远有效。源码还保留 `Read/Release` 兼容接口，读旧调用点时需要检查释放约定。

`WriteAt` 在后端写入后发布逻辑大小并使相关缓存失效。这里的原子大小发布不是“任意操作都线程安全”的证明，整体并发仍依赖索引、后端和具体操作的同步协议。

## 7. 从访问模式理解 IO 选择

图搜索常有不规则跳转；IVF 桶内扫描适合批量顺序读取；SINDI_V2 按查询词项选择 posting；SIMQ 精排可批量读候选文档 token。IO 优化应该围绕这些访问形态，而不是只把 `memory_io` 改成某个磁盘名字。

当前本机是 macOS arm64；前次构建关闭了 libaio 与 io_uring。源码中存在 Linux 异步后端，不代表本地这份二进制已启用它们。学习本地文件读取可先看 `buffer_io`、`mmap_io` 与 Reader 路径。

## 8. 代码：固定记录的部分写入

源码：[src/layout/fixed_layout.h](../../src/layout/fixed_layout.h)，基线行号 68–86。以下为连续原文摘录，可能是函数的一部分。

```cpp
    SetIO(std::shared_ptr<IOTmpl> io) {
        io_ = std::move(io);
    }

    void
    Write(InnerIdType id, const uint8_t* code) {
        io_->Write(code, code_size_, GetOffset(id));
    }

    void
    WriteAt(InnerIdType id, uint64_t offset_in_record, const uint8_t* data, uint64_t length) {
        io_->Write(data, length, GetOffsetAt(id, offset_in_record, length));
    }

    void
    WriteRange(InnerIdType begin_id, const uint8_t* codes, uint64_t count) {
        io_->Write(codes, GetByteSize(count), GetOffset(begin_id));
    }

```

Write 用记录 ID 得到偏移；WriteAt 还携带记录内部偏移；WriteRange 连写多个完整 code。寻址由 Layout 负责，实际 Write 仍交给 IO。GetOffsetAt 会检查部分访问没有越过记录边界，DataCell 不必重复实现同样偏移算术。

## 9. 代码：读取租约与写后发布

源码：[src/io/core/byte_io.h](../../src/io/core/byte_io.h)，基线行号 98–125。以下为连续原文摘录，可能是函数的一部分。

```cpp
    [[nodiscard]] Operation
    SubmitReads(const ReadRequest* requests, uint64_t count) const {
        const auto published_size = Size();
        if (not ValidateRequests(requests, count, published_size)) {
            return Operation(false);
        }
        return cache_.SubmitReads(backend_, published_size, requests, count);
    }

    [[nodiscard]] Lease
    Acquire(uint64_t offset, uint64_t size) const {
        const auto published_size = Size();
        if (not IsValidRange(offset, size, published_size)) {
            return Lease{};
        }
        return cache_.Acquire(backend_, published_size, offset, size);
    }

    void
    WriteAt(uint64_t offset, const uint8_t* source, uint64_t size) {
        if (size > 0 and source == nullptr) {
            throw VsagException(ErrorType::INVALID_ARGUMENT, "IO write source is null");
        }
        uint64_t end = CheckedEnd(offset, size);
        backend_.WriteAt(offset, source, size);
        PublishSize(end);
        cache_.Invalidate(backend_, offset, size);
    }
```

SubmitReads 先验证请求区间再交给缓存策略；Acquire 返回 Lease 表示读取生命周期。WriteAt 先写 backend，再 PublishSize，再失效缓存。这些顺序服务于可见性和缓存一致性，但不替代索引外层对所有写操作的同步。Resize/Shrink 是另外的修改语义。
