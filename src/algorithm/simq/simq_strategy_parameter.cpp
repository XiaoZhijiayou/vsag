
// Copyright 2024-present the vsag project
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "simq_strategy_parameter.h"

#include <fmt/format.h>

#include "inner_string_params.h"
#include "utils/param_compat_macros.h"
#include "vsag/constants.h"

namespace vsag {

static constexpr const char* SIMQ_INIT_CLUSTER_RATIO = "init_cluster_ratio";
static constexpr const char* SIMQ_MAX_CLUSTER_SIZE = "max_cluster_size";
static constexpr const char* SIMQ_SPLIT_START_IDX = "split_start_idx";
static constexpr const char* SIMQ_RANDOM_SEED = "random_seed";
static constexpr const char* SIMQ_COARSE_K = "coarse_k";
static constexpr const char* SIMQ_RERANK_K = "rerank_k";
static constexpr const char* SIMQ_BUILD_HGRAPH_EF_SEARCH = "build_hgraph_ef_search";
static constexpr const char* SIMQ_SEARCH_HGRAPH_EF_SEARCH = "search_hgraph_ef_search";
static constexpr const char* SIMQ_SPLIT_DELAY_SECONDS = "split_delay_seconds";
static constexpr const char* SIMQ_QUANTIZATION_TYPE = "quantization_type";

void
SIMQStrategyParameter::FromJson(const JsonType& json) {
    InnerIndexParameter::FromJson(json);

    if (json.Contains(SIMQ_INIT_CLUSTER_RATIO)) {
        init_cluster_ratio = json[SIMQ_INIT_CLUSTER_RATIO].GetFloat();
    }
    if (json.Contains(SIMQ_MAX_CLUSTER_SIZE)) {
        max_cluster_size = json[SIMQ_MAX_CLUSTER_SIZE].GetInt();
    }
    if (json.Contains(SIMQ_SPLIT_START_IDX)) {
        split_start_idx = json[SIMQ_SPLIT_START_IDX].GetInt();
    }
    if (json.Contains(SIMQ_RANDOM_SEED)) {
        random_seed = json[SIMQ_RANDOM_SEED].GetInt();
    }
    if (json.Contains(SIMQ_COARSE_K)) {
        coarse_k = json[SIMQ_COARSE_K].GetInt();
    }
    if (json.Contains(SIMQ_RERANK_K)) {
        rerank_k = json[SIMQ_RERANK_K].GetInt();
    }
    if (json.Contains(SIMQ_BUILD_HGRAPH_EF_SEARCH)) {
        build_hgraph_ef_search = json[SIMQ_BUILD_HGRAPH_EF_SEARCH].GetInt();
    }
    if (json.Contains(SIMQ_SEARCH_HGRAPH_EF_SEARCH)) {
        search_hgraph_ef_search = json[SIMQ_SEARCH_HGRAPH_EF_SEARCH].GetInt();
    }
    if (json.Contains(SIMQ_SPLIT_DELAY_SECONDS)) {
        split_delay_seconds = json[SIMQ_SPLIT_DELAY_SECONDS].GetFloat();
    }
    if (json.Contains(SIMQ_QUANTIZATION_TYPE)) {
        quantization_type = json[SIMQ_QUANTIZATION_TYPE].GetString();
    }

    if (json.Contains("reassign_after_build")) {
        reassign_after_build = json["reassign_after_build"].GetBool();
    }
    if (json.Contains("rebuild_after_reassign")) {
        rebuild_after_reassign = json["rebuild_after_reassign"].GetBool();
    }
    CHECK_ARGUMENT(not rebuild_after_reassign or reassign_after_build,
                   "simq: rebuild_after_reassign requires reassign_after_build");
    if (json.Contains("update_center_on_insert")) {
        update_center_on_insert = json["update_center_on_insert"].GetBool();
    }
    for (auto entry : {std::make_pair("center_update_interval", &center_update_interval),
                       std::make_pair("clustering_batch_size", &clustering_batch_size),
                       std::make_pair("center_hgraph_mode", &center_hgraph_mode),
                       std::make_pair("final_center_mode", &final_center_mode)}) {
        if (json.Contains(entry.first))
            *entry.second = json[entry.first].GetInt();
    }
    for (auto entry : {std::make_pair("route_window_size", &route_window_size),
                       std::make_pair("route_candidate_count", &route_candidate_count)}) {
        if (json.Contains(entry.first))
            *entry.second = json[entry.first].GetInt();
    }
    CHECK_ARGUMENT(route_window_size >= 0 and route_window_size <= 65536,
                   "simq: route_window_size must be in [0, 65536]");
    CHECK_ARGUMENT(route_candidate_count > 0 and route_candidate_count <= 1024,
                   "simq: route_candidate_count must be in [1, 1024]");
    CHECK_ARGUMENT(
        route_window_size == 0 or (update_center_on_insert and center_update_interval == 1 and
                                   clustering_batch_size == 1 and center_hgraph_mode == 1 and
                                   final_center_mode == 1 and not reassign_after_build),
        "simq: candidate routing requires v2 online mean settings");
    if (json.Contains("fast_online_build")) {
        fast_online_build = json["fast_online_build"].GetBool();
    }
    CHECK_ARGUMENT(
        not fast_online_build or (update_center_on_insert and center_update_interval == 1 and
                                  clustering_batch_size == 1 and center_hgraph_mode == 1 and
                                  final_center_mode == 1 and not reassign_after_build),
        "simq: fast_online_build requires online means, batch/interval=1, graph mode=1, "
        "final mean and no reassignment");
    CHECK_ARGUMENT(center_hgraph_mode >= -1 and center_hgraph_mode <= 5,
                   "simq: center_hgraph_mode must be in [-1, 5]");
    CHECK_ARGUMENT(center_update_interval > 0, "simq: center_update_interval must be positive");
    CHECK_ARGUMENT(clustering_batch_size >= 0, "simq: clustering_batch_size must be nonnegative");
    CHECK_ARGUMENT(final_center_mode >= -1 and final_center_mode <= 1,
                   "simq: final_center_mode must be -1, 0 or 1");
    bool valid_init_cluster_ratio = init_cluster_ratio > 0.0F and init_cluster_ratio <= 1.0F;
    CHECK_ARGUMENT(valid_init_cluster_ratio, "simq: init_cluster_ratio must be in (0, 1]");
    CHECK_ARGUMENT(max_cluster_size > 1, "simq: max_cluster_size must be > 1");
    bool valid_split_start_idx = split_start_idx > 1 and split_start_idx < max_cluster_size;
    CHECK_ARGUMENT(valid_split_start_idx, "simq: split_start_idx must be in (1, max_cluster_size)");
    CHECK_ARGUMENT(coarse_k > 0, "simq: coarse_k must be > 0");
    CHECK_ARGUMENT(rerank_k > 0, "simq: rerank_k must be > 0");
    CHECK_ARGUMENT(build_hgraph_ef_search > 0, "simq: build_hgraph_ef_search must be > 0");
    CHECK_ARGUMENT(search_hgraph_ef_search > 0, "simq: search_hgraph_ef_search must be > 0");
    CHECK_ARGUMENT(split_delay_seconds >= 0.0, "simq: split_delay_seconds must be >= 0");

    CHECK_ARGUMENT(json.Contains(BASE_CODES_KEY),
                   fmt::format("simq parameters must contain {}", BASE_CODES_KEY));

    // Inject quantization_type into base_codes JSON so MultiVectorDataCell
    // picks up the right quantizer (defaults to fp32 if not specified).
    auto base_json = json[BASE_CODES_KEY];
    if (quantization_type != "fp32") {
        JsonType quant_json;
        quant_json[TYPE_KEY].SetString(quantization_type);
        base_json[QUANTIZATION_PARAMS_KEY].SetJson(quant_json);
    }
    base_codes_param = CreateFlattenParam(base_json);
}

JsonType
SIMQStrategyParameter::ToJson() const {
    CHECK_ARGUMENT(base_codes_param != nullptr, "simq: base_codes_param is not initialized");
    JsonType json = InnerIndexParameter::ToJson();
    json[TYPE_KEY].SetString(INDEX_SIMQ);
    json["reassign_after_build"].SetBool(reassign_after_build);
    json["rebuild_after_reassign"].SetBool(rebuild_after_reassign);
    json["update_center_on_insert"].SetBool(update_center_on_insert);
    json["center_update_interval"].SetInt(center_update_interval);
    json["clustering_batch_size"].SetInt(clustering_batch_size);
    json["final_center_mode"].SetInt(final_center_mode);
    json["center_hgraph_mode"].SetInt(center_hgraph_mode);
    json["fast_online_build"].SetBool(fast_online_build);
    json["route_window_size"].SetInt(route_window_size);
    json["route_candidate_count"].SetInt(route_candidate_count);
    json[SIMQ_INIT_CLUSTER_RATIO].SetFloat(init_cluster_ratio);
    json[SIMQ_MAX_CLUSTER_SIZE].SetInt(max_cluster_size);
    json[SIMQ_SPLIT_START_IDX].SetInt(split_start_idx);
    json[SIMQ_RANDOM_SEED].SetInt(random_seed);
    json[SIMQ_COARSE_K].SetInt(coarse_k);
    json[SIMQ_RERANK_K].SetInt(rerank_k);
    json[SIMQ_BUILD_HGRAPH_EF_SEARCH].SetInt(build_hgraph_ef_search);
    json[SIMQ_SEARCH_HGRAPH_EF_SEARCH].SetInt(search_hgraph_ef_search);
    json[SIMQ_SPLIT_DELAY_SECONDS].SetDouble(split_delay_seconds);
    json[SIMQ_QUANTIZATION_TYPE].SetString(quantization_type);
    json[BASE_CODES_KEY].SetJson(base_codes_param->ToJson());
    return json;
}

bool
SIMQStrategyParameter::CheckCompatibility(const vsag::ParamPtr& other) const {
    if (not InnerIndexParameter::CheckCompatibility(other)) {
        return false;
    }
    PARAM_CAST_OR_RETURN(SIMQStrategyParameter, p, other);
    CHECK_SUB_PARAM(*this, *p, base_codes_param);
    return true;
}

SIMQStrategySearchParameters
SIMQStrategySearchParameters::FromJson(const std::string& json_string) {
    SIMQStrategySearchParameters obj;
    if (json_string.empty()) {
        return obj;
    }
    auto params = JsonType::Parse(json_string);
    if (!params.Contains(INDEX_SIMQ)) {
        return obj;
    }
    const auto& simq_params = params[INDEX_SIMQ];
    obj.IndexSearchParameter::FromJson(simq_params);
    if (simq_params.Contains(SIMQ_COARSE_K)) {
        obj.coarse_k = simq_params[SIMQ_COARSE_K].GetInt();
    }
    if (simq_params.Contains(SIMQ_RERANK_K)) {
        obj.rerank_k = simq_params[SIMQ_RERANK_K].GetInt();
    }
    if (simq_params.Contains(SIMQ_SEARCH_HGRAPH_EF_SEARCH)) {
        obj.search_hgraph_ef_search = simq_params[SIMQ_SEARCH_HGRAPH_EF_SEARCH].GetInt();
        CHECK_ARGUMENT(obj.search_hgraph_ef_search > 0,
                       "simq: search_hgraph_ef_search must be > 0");
    }
    return obj;
}

}  // namespace vsag
