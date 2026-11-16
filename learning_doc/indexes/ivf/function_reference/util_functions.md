# util_functions.cpp：逐函数完整源码与调用点

[主讲解](../code_walkthrough.md) · [函数总目录](README.md)

源码：[ src/utils/util_functions.cpp ](../../../../src/utils/util_functions.cpp)。基线 `fd363937`。以下源码函数体完整保留；调用点表是语法树中的显式调用表达式，按源码位置排列，不代表 C++ 参数求值顺序。表中“候选实现”需结合类型和参数选分支，不能将同名函数全部视为必经路径。

- [select_k_numbers · L43](util_functions.md#L43)

- [sample_train_data · L234](util_functions.md#L234)


<a id="L43"></a>

## `select_k_numbers`

源码位置：`src/utils/util_functions.cpp:43–60`。

先从签名确认输入、返回值和 const/override，再按完整函数体的条件阅读调用点。下表保留了本函数的显式调用以及 lambda 中的调用；进入下层时用“候选实现”定位，未解析的对象由源码静态类型/运行时类型确认。

### 完整函数

```cpp
std::vector<int>
select_k_numbers(int64_t n, int k) {
    if (k > n || k <= 0) {
        throw VsagException(ErrorType::INVALID_ARGUMENT, "Invalid values for N or K");
    }

    std::vector<int> numbers(n);
    std::iota(numbers.begin(), numbers.end(), 0);

    std::random_device rd;
    std::mt19937 gen(rd());
    for (int i = 0; i < k; ++i) {
        std::uniform_int_distribution<> dist(i, static_cast<int>(n - 1));
        std::swap(numbers[i], numbers[dist(gen)]);
    }
    numbers.resize(k);
    return numbers;
}
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L46 | VsagException | if_statement@45 (k &gt; n &#124;&#124; k &lt;= 0) | 当前参考未静态绑定；见下方边界说明 |

| L50 | std::iota | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L50 | numbers.begin | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L50 | numbers.end | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L56 | std::swap | for_statement@54 i &lt; k | 当前参考未静态绑定；见下方边界说明 |

| L56 | dist | for_statement@54 i &lt; k | 当前参考未静态绑定；见下方边界说明 |

| L58 | numbers.resize | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。


<a id="L234"></a>

## `sample_train_data`

源码位置：`src/utils/util_functions.cpp:234–307`。

先从签名确认输入、返回值和 const/override，再按完整函数体的条件阅读调用点。下表保留了本函数的显式调用以及 lambda 中的调用；进入下层时用“候选实现”定位，未解析的对象由源码静态类型/运行时类型确认。

### 完整函数

```cpp
DatasetPtr
sample_train_data(const vsag::DatasetPtr& data,
                  int64_t total_elements,
                  int64_t dim,
                  int64_t train_sample_count,
                  Allocator* allocator,
                  std::optional<uint64_t> random_seed) {
    const int64_t min_train_size = 512;

    int64_t sample_count = std::min(total_elements, std::max(min_train_size, train_sample_count));

    // If no sampling is needed, return the original dataset
    if (sample_count >= total_elements) {
        return data;
    }

    // If the allocator is null, use the default allocator
    std::shared_ptr<Allocator> owned_allocator;
    Allocator* safe_allocator;
    if (allocator != nullptr) {
        safe_allocator = allocator;
    } else {
        owned_allocator = vsag::SafeAllocator::FactoryDefaultAllocator();
        safe_allocator = owned_allocator.get();
    }

    vsag::Vector<float> sampled_data_buffer(safe_allocator);
    vsag::Vector<int64_t> sampled_ids(safe_allocator);
    vsag::Vector<int64_t> sampled_indices(safe_allocator);
    sampled_indices.reserve(sample_count);

    int64_t actual_size = std::min(sample_count, total_elements);
    sampled_indices.resize(actual_size);
    std::iota(sampled_indices.begin(), sampled_indices.end(), 0);
    std::random_device rd;
    std::mt19937_64 gen(random_seed.has_value() ? *random_seed : rd());
    for (int64_t i = sample_count; i < total_elements; ++i) {
        std::uniform_int_distribution<int64_t> dist(0, i);
        int64_t j = dist(gen);
        if (j < sample_count) {
            sampled_indices[j] = i;
        }
    }
    sampled_data_buffer.resize(sample_count * dim);
    const auto* original_data = data->GetFloat32Vectors();
    for (int64_t i = 0; i < sample_count; ++i) {
        std::copy(original_data + sampled_indices[i] * dim,
                  original_data + (sampled_indices[i] + 1) * dim,
                  sampled_data_buffer.data() + i * dim);
    }
    auto* new_data_buffer =
        static_cast<float*>(safe_allocator->Allocate(sample_count * dim * sizeof(float)));
    std::copy(sampled_data_buffer.begin(), sampled_data_buffer.end(), new_data_buffer);

    auto sampled_dataset = std::make_shared<DatasetImpl>();
    sampled_dataset->NumElements(sample_count)
        ->Dim(dim)
        ->Float32Vectors(new_data_buffer)
        ->Owner(true, safe_allocator);
    if (data->GetIds() != nullptr) {
        sampled_ids.reserve(sample_count);
        const auto* original_ids = data->GetIds();
        for (int64_t i = 0; i < sample_count; ++i) {
            sampled_ids.push_back(original_ids[sampled_indices[i]]);
        }

        auto* new_ids_buffer =
            static_cast<int64_t*>(safe_allocator->Allocate(sample_count * sizeof(int64_t)));
        std::copy(sampled_ids.begin(), sampled_ids.end(), new_ids_buffer);

        sampled_dataset->Ids(new_ids_buffer)->Owner(true, safe_allocator);
    }
    return sampled_dataset;
}
```

### 函数内部调用点：不省略标准库和辅助调用

| 调用位置 | 被调表达式 | 外围控制流 | 继续展开 |
| --- | --- | --- | --- |

| L243 | std::min | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L243 | std::max | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L256 | vsag::SafeAllocator::FactoryDefaultAllocator | if_statement@253 (allocator != nullptr) [else 分支] | 当前参考未静态绑定；见下方边界说明 |

| L257 | owned_allocator.get | if_statement@253 (allocator != nullptr) [else 分支] | 当前参考未静态绑定；见下方边界说明 |

| L263 | sampled_indices.reserve | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L265 | std::min | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L266 | sampled_indices.resize | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L267 | std::iota | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L267 | sampled_indices.begin | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L267 | sampled_indices.end | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L269 | random_seed.has_value | conditional_expression@269 random_seed.has_value() | 当前参考未静态绑定；见下方边界说明 |

| L269 | rd | conditional_expression@269 random_seed.has_value() | 当前参考未静态绑定；见下方边界说明 |

| L272 | dist | for_statement@270 i &lt; total_elements | 当前参考未静态绑定；见下方边界说明 |

| L277 | sampled_data_buffer.resize | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L278 | data-&gt;GetFloat32Vectors | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L280 | std::copy | for_statement@279 i &lt; sample_count | 当前参考未静态绑定；见下方边界说明 |

| L282 | sampled_data_buffer.data | for_statement@279 i &lt; sample_count | 当前参考未静态绑定；见下方边界说明 |

| L285 | safe_allocator-&gt;Allocate | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L286 | std::copy | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L286 | sampled_data_buffer.begin | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L286 | sampled_data_buffer.end | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L288 | std::make_shared&lt;DatasetImpl&gt; | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L289 | sampled_dataset-&gt;NumElements(sample_count) -&gt;Dim(dim) -&gt;Float32Vectors(new_data_buffer) -&gt;Owner | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L289 | sampled_dataset-&gt;NumElements(sample_count) -&gt;Dim(dim) -&gt;Float32Vectors | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L289 | sampled_dataset-&gt;NumElements(sample_count) -&gt;Dim | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L289 | sampled_dataset-&gt;NumElements | 函数本体；短路求值/提前返回见源码 | 当前参考未静态绑定；见下方边界说明 |

| L293 | data-&gt;GetIds | if_statement@293 (data-&gt;GetIds() != nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L294 | sampled_ids.reserve | if_statement@293 (data-&gt;GetIds() != nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L295 | data-&gt;GetIds | if_statement@293 (data-&gt;GetIds() != nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L297 | sampled_ids.push_back | if_statement@293 (data-&gt;GetIds() != nullptr) → for_statement@296 i &lt; sample_count | 当前参考未静态绑定；见下方边界说明 |

| L301 | safe_allocator-&gt;Allocate | if_statement@293 (data-&gt;GetIds() != nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L302 | std::copy | if_statement@293 (data-&gt;GetIds() != nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L302 | sampled_ids.begin | if_statement@293 (data-&gt;GetIds() != nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L302 | sampled_ids.end | if_statement@293 (data-&gt;GetIds() != nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L304 | sampled_dataset-&gt;Ids(new_ids_buffer)-&gt;Owner | if_statement@293 (data-&gt;GetIds() != nullptr) | 当前参考未静态绑定；见下方边界说明 |

| L304 | sampled_dataset-&gt;Ids | if_statement@293 (data-&gt;GetIds() != nullptr) | 当前参考未静态绑定；见下方边界说明 |


边界说明：标准库/容器/getter 保留调用点而不展开其 ABI；虚对象、函数指针和模板需要具体类型才能确定实现。未绑定项不表示没有下层调用。对核心业务分派，请对照主讲解的具名分支；需要实际活动帧时用 LLDB 的 `bt`。
