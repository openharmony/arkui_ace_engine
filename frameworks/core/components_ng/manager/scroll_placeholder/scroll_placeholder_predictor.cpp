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

#include "core/components_ng/manager/scroll_placeholder/scroll_placeholder_predictor.h"

#include <algorithm>

namespace OHOS::Ace::NG {

void ScrollPlaceholderPredictor::RecordBuildCost(const std::string& templateKey, int64_t durationNs)
{
    if (templateKey.empty() || durationNs < 0) {
        return;
    }
    auto& state = costStats_[templateKey];
    if (state.samples <= 0) {
        state.value = static_cast<double>(durationNs);
    } else {
        state.value = EWMA_ALPHA * static_cast<double>(durationNs) + (1.0 - EWMA_ALPHA) * state.value;
    }
    state.samples = std::min(state.samples + 1, std::numeric_limits<int32_t>::max() - 1);
}

ScrollPlaceholderPredictor::Estimate ScrollPlaceholderPredictor::EstimateBuildCost(
    const std::string& templateKey) const
{
    Estimate estimate;
    auto iter = costStats_.find(templateKey);
    if (iter == costStats_.end() || iter->second.samples <= 0) {
        return estimate; // cold start
    }
    estimate.estimateNs = static_cast<int64_t>(iter->second.value);
    estimate.samples = iter->second.samples;
    estimate.warm = iter->second.samples >= WARMUP_SAMPLES;
    return estimate;
}

ScrollPlaceholderDecision ScrollPlaceholderPredictor::Decide(
    int64_t estimatedCostNs, int64_t remainingBudgetNs)
{
    if (remainingBudgetNs <= BUDGET_RESERVED_NS) {
        // Almost no budget left: even the placeholder must be cheap, defer the real build.
        return ScrollPlaceholderDecision::DEFER_WITH_PLACEHOLDER;
    }
    const int64_t usable = remainingBudgetNs - BUDGET_RESERVED_NS;
    const int64_t needed = estimatedCostNs + PLACEHOLDER_COST_NS;
    return (needed > usable) ? ScrollPlaceholderDecision::DEFER_WITH_PLACEHOLDER
                             : ScrollPlaceholderDecision::SYNC_BUILD;
}

void ScrollPlaceholderPredictor::Reset(const std::string& templateKey)
{
    costStats_.erase(templateKey);
}

void ScrollPlaceholderPredictor::ResetAll()
{
    costStats_.clear();
}

} // namespace OHOS::Ace::NG
