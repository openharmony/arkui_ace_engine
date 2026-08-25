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

#include "core/components_ng/pattern/scrollable/scroll_snap_utils.h"

#include <algorithm>
#include <cmath>

namespace OHOS::Ace::NG {
namespace {
// Index of the first candidate whose offset is greater than [offset].
int32_t UpperBoundIndex(const std::vector<ScrollSnapUtils::SnapCandidate>& candidates, float offset)
{
    return static_cast<int32_t>(std::upper_bound(candidates.begin(), candidates.end(), offset,
        [](float value, const ScrollSnapUtils::SnapCandidate& candidate) { return value < candidate.offset; }) -
        candidates.begin());
}

ScrollSnapUtils::SnapSelectResult MakeResult(const ScrollSnapUtils::SnapCandidate& candidate)
{
    ScrollSnapUtils::SnapSelectResult result;
    result.found = true;
    result.targetOffset = candidate.offset;
    result.targetIndex = candidate.index;
    return result;
}
} // namespace

void ScrollSnapUtils::NormalizeCandidates(std::vector<SnapCandidate>& candidates)
{
    std::sort(candidates.begin(), candidates.end(), [](const SnapCandidate& lhs, const SnapCandidate& rhs) {
        if (NearEqual(lhs.offset, rhs.offset, SNAP_OFFSET_EPSILON)) {
            return lhs.index < rhs.index;
        }
        return lhs.offset < rhs.offset;
    });
    // Same snap offset can come from multiple items (Grid rows / equal-height WaterFlow lanes):
    // keep the first (smallest index) and drop the rest (R-6).
    candidates.erase(std::unique(candidates.begin(), candidates.end(),
        [](const SnapCandidate& lhs, const SnapCandidate& rhs) {
            return NearEqual(lhs.offset, rhs.offset, SNAP_OFFSET_EPSILON);
        }),
        candidates.end());
}

ScrollSnapUtils::SnapSelectResult ScrollSnapUtils::SelectByThreshold(
    const std::vector<SnapCandidate>& candidates, float currentOffset, float threshold, bool forward)
{
    SnapSelectResult result;
    if (candidates.empty()) {
        return result;
    }
    // Clamp threshold into [0, 1]; invalid values fall back to the default (R-4 / R-11).
    float clampedThreshold = std::isfinite(threshold) ? std::clamp(threshold, 0.0f, 1.0f) : DEFAULT_SNAP_THRESHOLD;

    auto upper = UpperBoundIndex(candidates, currentOffset);
    int32_t currentIdx = -1;
    int32_t neighborIdx = -1;
    if (forward) {
        // current candidate: last one at or before the offset; neighbor: the next one.
        currentIdx = upper > 0 ? upper - 1 : 0;
        neighborIdx = upper < static_cast<int32_t>(candidates.size()) ? upper : -1;
    } else {
        currentIdx = upper < static_cast<int32_t>(candidates.size()) ? upper
                                                                      : static_cast<int32_t>(candidates.size()) - 1;
        neighborIdx = upper > 0 ? upper - 1 : -1;
    }
    if (neighborIdx < 0) {
        return MakeResult(candidates[currentIdx]);
    }
    const auto& current = candidates[currentIdx];
    const auto& neighbor = candidates[neighborIdx];
    float distance = std::abs(neighbor.offset - current.offset);
    if (NearZero(distance)) {
        return MakeResult(current);
    }
    float effective = std::abs(currentOffset - current.offset);
    // "< D * T returns to the current candidate; >= D * T enters the adjacent candidate" (R-4).
    return GreatOrEqual(effective, distance * clampedThreshold) ? MakeResult(neighbor) : MakeResult(current);
}

ScrollSnapUtils::SnapSelectResult ScrollSnapUtils::SelectByPredictedLanding(
    const std::vector<SnapCandidate>& candidates, float currentOffset, float predictedOffset, bool forward,
    float threshold)
{
    if (candidates.empty()) {
        return SnapSelectResult();
    }
    // Restrict the search to candidates that do not move against the fling direction (R-5).
    auto upper = UpperBoundIndex(candidates, currentOffset - SNAP_OFFSET_EPSILON);
    int32_t begin = forward ? upper : 0;
    int32_t end = forward ? static_cast<int32_t>(candidates.size()) : upper;
    if (begin >= end) {
        // No candidate in the fling direction: keep the threshold result instead of reversing.
        return SelectByThreshold(candidates, currentOffset, threshold, forward);
    }
    int32_t best = begin;
    float bestDistance = std::abs(candidates[begin].offset - predictedOffset);
    bool equidistant = false;
    for (int32_t i = begin + 1; i < end; ++i) {
        float distance = std::abs(candidates[i].offset - predictedOffset);
        if (NearEqual(distance, bestDistance, SNAP_OFFSET_EPSILON)) {
            equidistant = true;
            continue;
        }
        if (distance < bestDistance) {
            bestDistance = distance;
            best = i;
            equidistant = false;
        }
    }
    if (equidistant) {
        // Equal distance: prefer the candidate in the fling direction (R-6).
        best = forward ? std::min(best + 1, end - 1) : std::max(best - 1, begin);
    }
    return MakeResult(candidates[best]);
}

ScrollSnapUtils::SnapSelectResult ScrollSnapUtils::SelectByDirection(
    const std::vector<SnapCandidate>& candidates, float currentOffset, bool forward)
{
    if (candidates.empty()) {
        return SnapSelectResult();
    }
    auto upper = UpperBoundIndex(candidates, currentOffset + SNAP_OFFSET_EPSILON);
    if (forward) {
        if (upper < static_cast<int32_t>(candidates.size())) {
            return MakeResult(candidates[upper]);
        }
    } else {
        if (upper > 0) {
            return MakeResult(candidates[upper - 1]);
        }
    }
    // Already at the edge: stay on the nearest candidate in that direction.
    return SelectByThreshold(candidates, currentOffset, DEFAULT_SNAP_THRESHOLD, forward);
}

ScrollSnapUtils::SnapSelectResult ScrollSnapUtils::SelectSnapTarget(const std::vector<SnapCandidate>& candidates,
    float currentOffset, float velocity, float predictDelta, float threshold, float velocityScale)
{
    if (candidates.empty()) {
        return SnapSelectResult();
    }
    bool forward = NearZero(velocity) ? predictDelta >= 0.0f : velocity > 0.0f;
    float speedThreshold = SNAP_VELOCITY_THRESHOLD * (NearZero(velocityScale) ? 1.0f : velocityScale);
    if (std::abs(velocity) >= speedThreshold && !NearZero(predictDelta)) {
        float predictedOffset = currentOffset + predictDelta;
        return SelectByPredictedLanding(candidates, currentOffset, predictedOffset, forward, threshold);
    }
    return SelectByThreshold(candidates, currentOffset, threshold, forward);
}

float ScrollSnapUtils::ClampSnapOffset(float offset, float minOffset, float maxOffset)
{
    if (maxOffset < minOffset) {
        return minOffset;
    }
    return std::clamp(offset, minOffset, maxOffset);
}

} // namespace OHOS::Ace::NG
