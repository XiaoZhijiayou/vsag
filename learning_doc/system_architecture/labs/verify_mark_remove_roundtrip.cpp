// Reproduce the observed MARK_REMOVE + BinarySet behavior at fd363937.
// Exit 0 means operations completed, not that the observed semantics are correct.
#include <vsag/vsag.h>

#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

namespace {

template <typename T>
T
RequireValue(tl::expected<T, vsag::Error> result) {
    if (not result.has_value()) {
        throw std::runtime_error(result.error().message);
    }
    return std::move(result.value());
}

void
Report(const std::string& name,
       const std::string& phase,
       const vsag::IndexPtr& index,
       const vsag::DatasetPtr& query) {
    vsag::SearchRequest request;
    request.query_ = query;
    request.topk_ = 3;
    request.params_str_ = name == "hgraph" ? R"({"hgraph":{"ef_search":8}})" : "{}";
    auto result = RequireValue(index->SearchWithRequest(request));
    std::cout << name << " " << phase << " count=" << index->GetNumElements()
              << " removed=" << index->GetNumberRemoved()
              << " exists9007=" << index->CheckIdExist(9007) << " results=";
    for (int64_t j = 0; j < result->GetDim(); ++j) {
        std::cout << result->GetIds()[j] << ":" << result->GetDistances()[j] << ",";
    }
    std::cout << '\n';
}

}  // namespace

int
main() {
    try {
        vsag::init();
        std::vector<int64_t> ids = {101, 9007, 205};
        std::vector<float> vectors = {0, 0, 0, 0, 1, 0, 0, 0, 3, 0, 0, 0};
        std::vector<float> query_vector = {1, 0, 0, 0};
        auto base = vsag::Dataset::Make()
                        ->NumElements(3)
                        ->Dim(4)
                        ->Ids(ids.data())
                        ->Float32Vectors(vectors.data())
                        ->Owner(false);
        auto query = vsag::Dataset::Make()
                         ->NumElements(1)
                         ->Dim(4)
                         ->Float32Vectors(query_vector.data())
                         ->Owner(false);
        for (const std::string name : {"brute_force", "hgraph"}) {
            const std::string params = name == "hgraph" ? R"({
                "dtype":"float32", "metric_type":"l2", "dim":4,
                "index_param":{
                    "base_quantization_type":"fp32", "use_reorder":false,
                    "max_degree":8, "ef_construction":32, "build_thread_count":1
                }
            })" : R"({"dtype":"float32","metric_type":"l2","dim":4})";
            auto index = RequireValue(vsag::Factory::CreateIndex(name, params));
            if (not RequireValue(index->Build(base)).empty()) {
                throw std::runtime_error("Build returned failed IDs");
            }
            if (RequireValue(index->Remove(9007, vsag::RemoveMode::MARK_REMOVE)) != 1) {
                throw std::runtime_error("Unexpected Remove count");
            }
            Report(name, "marked", index, query);
            auto binary_set = RequireValue(index->Serialize());
            auto restored = RequireValue(vsag::Factory::CreateIndex(name, params));
            auto loaded = restored->Deserialize(binary_set);
            if (not loaded.has_value()) {
                throw std::runtime_error(loaded.error().message);
            }
            Report(name, "restored", restored, query);
        }
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "ERROR: " << e.what() << '\n';
        return 1;
    }
}
