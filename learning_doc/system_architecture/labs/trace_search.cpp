// VSAG learning example: run against the local Debug library at fd363937.
// This is a teaching program, not a replacement for the repository test suite.
#include <vsag/vsag.h>

#include <cmath>
#include <cstdint>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

namespace {

class Exclude305 final : public vsag::Filter {
public:
    bool
    CheckValid(int64_t label) const override {
        // Filter::CheckValid uses true = allowed. The argument is an external label.
        return label != 305;
    }

    float
    ValidRatio() const override {
        return 5.0F / 6.0F;
    }
};

template <typename T>
T
RequireValue(tl::expected<T, vsag::Error> value, const std::string& operation) {
    if (not value.has_value()) {
        throw std::runtime_error(operation + ": " + value.error().message);
    }
    return std::move(value.value());
}

void
CheckResults(const vsag::IndexPtr& index,
             const vsag::SearchRequest& request,
             const std::string& title,
             const std::vector<int64_t>& expected_ids,
             const std::vector<float>& expected_distances,
             bool explain) {
    // Set a breakpoint here, then step into IndexImpl and the concrete algorithm.
    auto result = RequireValue(index->SearchWithRequest(request), title);
    if (result->GetNumElements() != 1 or
        result->GetDim() != static_cast<int64_t>(expected_ids.size())) {
        throw std::runtime_error(title + ": unexpected result shape");
    }
    std::cout << title << " rows=" << result->GetNumElements()
              << " results=" << result->GetDim() << '\n';
    for (uint64_t i = 0; i < expected_ids.size(); ++i) {
        const int64_t label = result->GetIds()[i];
        const float distance = result->GetDistances()[i];
        std::cout << "  label=" << label << " distance=" << distance << '\n';
        if (label != expected_ids[i] or
            std::abs(distance - expected_distances[i]) > 1e-5F) {
            throw std::runtime_error(title + ": answer differs from the hand calculation");
        }
    }
    if (explain) {
        std::cout << "statistics=" << result->GetStatistics() << '\n';
        std::cout << "reasoning=" << result->GetReasoning() << '\n';
    }
}

}  // namespace

int
main(int argc, char** argv) {
    try {
        const std::string name = argc > 1 ? argv[1] : "brute_force";
        const bool explain = argc > 2 and std::string(argv[2]) == "reasoning";
        if (name != "brute_force" and name != "hgraph") {
            throw std::runtime_error("usage: trace_search [brute_force|hgraph] [reasoning]");
        }
        vsag::init();

        // ID values deliberately differ from the storage positions 0, 1, ..., 5.
        std::vector<int64_t> ids = {101, 305, 9001, 42, 77, 880};
        std::vector<float> vectors = {
            0, 0, 0, 0,
            1, 0, 0, 0,
            1, 1, 0, 0,
            3, 1, 0, 0,
            0, 4, 0, 0,
            5, 5, 0, 0,
        };
        std::vector<float> query_vector = {1, 1, 0, 0};
        // Owner(false): these views borrow vector-owned memory throughout main().
        auto base = vsag::Dataset::Make()
                        ->NumElements(static_cast<int64_t>(ids.size()))
                        ->Dim(4)
                        ->Ids(ids.data())
                        ->Float32Vectors(vectors.data())
                        ->Owner(false);
        auto query = vsag::Dataset::Make()
                         ->NumElements(1)
                         ->Dim(4)
                         ->Float32Vectors(query_vector.data())
                         ->Owner(false);

        const std::string build_params = name == "hgraph" ? R"({
            "dtype":"float32", "metric_type":"l2", "dim":4,
            "index_param":{
                "base_quantization_type":"fp32", "use_reorder":false,
                "max_degree":8, "ef_construction":32, "build_thread_count":1
            }
        })" : R"({"dtype":"float32","metric_type":"l2","dim":4})";
        auto index = RequireValue(vsag::Factory::CreateIndex(name, build_params), "CreateIndex");
        auto failed_ids = RequireValue(index->Build(base), "Build");
        if (not failed_ids.empty() or index->GetNumElements() != 6) {
            throw std::runtime_error("Build did not admit every input record");
        }
        std::cout << "index=" << name << " elements=" << index->GetNumElements() << '\n';

        vsag::SearchRequest request;
        request.query_ = query;
        request.topk_ = 3;
        request.params_str_ = name == "hgraph" ? R"({"hgraph":{"ef_search":8}})" : "{}";
        if (explain) {
            request.expected_labels_ = {9001, 305};
        }
        CheckResults(index, request, "plain", {9001, 305, 101}, {0, 1, 2}, explain);

        auto filtered = request;
        filtered.enable_filter_ = true;
        filtered.filter_ = std::make_shared<Exclude305>();
        CheckResults(index, filtered, "exclude-305", {9001, 101, 42}, {0, 2, 4}, explain);

        auto threshold = request;
        threshold.threshold_ = 0.5F;
        CheckResults(index, threshold, "threshold-0.5", {9001}, {0}, explain);

        // Deserialize into a new empty index; the original index remains alive.
        auto binary_set = RequireValue(index->Serialize(), "Serialize");
        auto restored =
            RequireValue(vsag::Factory::CreateIndex(name, build_params), "Restore create");
        auto loaded = restored->Deserialize(binary_set);
        if (not loaded.has_value()) {
            throw std::runtime_error("Deserialize: " + loaded.error().message);
        }
        CheckResults(restored, request, "roundtrip", {9001, 305, 101}, {0, 1, 2}, explain);

        auto invalid = request;
        invalid.topk_ = 0;
        auto rejected = index->SearchWithRequest(invalid);
        if (rejected.has_value()) {
            throw std::runtime_error("topk=0 unexpectedly succeeded");
        }
        std::cout << "topk-0 error_type=" << static_cast<int>(rejected.error().type) << '\n';
        std::cout << "PASS: four answer checks and one error-boundary check\n";
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "FAIL: " << e.what() << '\n';
        return 1;
    }
}
