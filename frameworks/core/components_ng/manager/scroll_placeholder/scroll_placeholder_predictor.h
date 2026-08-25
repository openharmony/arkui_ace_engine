/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_SCROLL_PLACEHOLDER_SCROLL_PLACEHOLDER_PREDICTOR_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_SCROLL_PLACEHOLDER_SCROLL_PLACEHOLDER_PREDICTOR_H

#include <cstdint>
#include <string>
#include <unordered_map>

#include "base/utils/noncopyable.h"
#include "core/components_ng/manager/scroll_placeholder/scroll_placeholder_types.h"

namespace OHOS::Ace::NG {

/**
 * FEAT-005 (P-01): creation-cost sampling and load prediction.
 *
 * Keeps an EWMA of real item build durations per placeholder template key and
 * decides, before a real build, whether the remaining frame budget can absorb
 * the estimated cost. All durations are nanoseconds.
 *
 * The predictor is an internal framework capability: no developer-tunable
 * thresholds, budgets or algorithm parameters are exposed.
 */
class ACE_EXPORT ScrollPlaceholderPredictor final : private NonCopyable {
public:
    /** Smoothing factor of the EWMA. */
    static constexpr double EWMA_ALPHA = 0.3;
    /** Minimum samples before the estimate is considered warm. */
    static constexpr int32_t WARMUP_SAMPLES = 2;
    /** Cold-start assumption when no sample exists yet (5ms per item, per spec baseline). */
    static constexpr int64_t DEFAULT_COLD_COST_NS = 5'000'000;
    /** Cost of creating + mounting one placeholder node, reserved against the frame budget. */
    static constexpr int64_t PLACEHOLDER_COST_NS = 100'000;
    /** Safety margin subtracted from the remaining budget before the decision. */
    static constexpr int64_t BUDGET_RESERVED_NS = 500'000;

    ScrollPlaceholderPredictor() = default;
    ~ScrollPlaceholderPredictor() = default;

    /** Records the duration of one real item build for [templateKey]. UI thread only. */
    void RecordBuildCost(const std::string& templateKey, int64_t durationNs);

    struct Estimate {
        int64_t estimateNs = DEFAULT_COLD_COST_NS;
        bool warm = false;   // at least WARMUP_SAMPLES samples collected
        int32_t samples = 0; // sample count backing this estimate
    };

    /** Returns the current EWMA estimate for [templateKey]. */
    Estimate EstimateBuildCost(const std::string& templateKey) const;

    /**
     * Pure decision core, kept side-effect free for unit testing.
     * Defers when (estimated cost + placeholder cost) does not fit into the
     * remaining budget minus the safety margin.
     */
    static ScrollPlaceholderDecision Decide(int64_t estimatedCostNs, int64_t remainingBudgetNs);

    /** Clears samples for one key (e.g. template re-registered) or all keys. */
    void Reset(const std::string& templateKey);
    void ResetAll();

private:
    struct EWMAState {
        double value = static_cast<double>(DEFAULT_COLD_COST_NS);
        int32_t samples = 0;
    };
    std::unordered_map<std::string, EWMAState> costStats_;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_SCROLL_PLACEHOLDER_SCROLL_PLACEHOLDER_PREDICTOR_H
