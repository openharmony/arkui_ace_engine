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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SCROLLABLE_SCROLL_SNAP_UTILS_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SCROLLABLE_SCROLL_SNAP_UTILS_H

#include <vector>

#include "base/utils/utils.h"
#include "core/components_ng/pattern/scrollable/scrollable_properties.h"

namespace OHOS::Ace::NG {

/**
 * FEAT-029: deterministic item snap target selection shared by List/Grid/WaterFlow.
 *
 * Behavior contract (spec.md R-3 ~ R-7):
 *  - candidates are built only from visible/cached items, one snap offset per item anchor;
 *  - identical offsets are deduplicated, equal-distance ties are resolved by scroll direction first
 *    and smaller item index second;
 *  - low speed release: effective distance < D * threshold snaps back to the current candidate,
 *    >= D * threshold advances to the adjacent candidate (D = distance between adjacent candidates);
 *  - high speed fling: nearest candidate to the predicted landing point, never against the fling
 *    direction;
 *  - the final offset is clamped into the legal scroll range.
 */
class ScrollSnapUtils {
public:
    // Default [0,1] position threshold between adjacent candidates (R-4).
    static constexpr float DEFAULT_SNAP_THRESHOLD = 0.5f;
    // Velocity threshold (px/s) separating threshold selection from fling prediction, aligned with
    // the existing List snap constant SCROLL_SNAP_VELOCITY_TH.
    static constexpr float SNAP_VELOCITY_THRESHOLD = 780.0f;
    // Offsets closer than this epsilon are treated as duplicates (R-6).
    static constexpr float SNAP_OFFSET_EPSILON = 0.5f;

    struct SnapCandidate {
        float offset = 0.0f; // absolute scroll offset aligning this anchor to the snap line
        int32_t index = 0;   // item index, deterministic tie-break (smaller wins)
    };

    struct SnapSelectResult {
        bool found = false;
        float targetOffset = 0.0f;
        int32_t targetIndex = -1;
    };

    // Sort candidates by offset ascending (equal offsets keep the smaller index first) and remove
    // near-duplicate offsets.
    static void NormalizeCandidates(std::vector<SnapCandidate>& candidates);

    // R-4: threshold selection between the current candidate and its neighbor in [forward] direction.
    static SnapSelectResult SelectByThreshold(
        const std::vector<SnapCandidate>& candidates, float currentOffset, float threshold, bool forward);

    // R-5: nearest candidate to the predicted landing offset; the result never moves against the
    // fling direction. Falls back to threshold selection when no candidate lies in the direction.
    static SnapSelectResult SelectByPredictedLanding(const std::vector<SnapCandidate>& candidates,
        float currentOffset, float predictedOffset, bool forward, float threshold);

    // Axis/wheel step: next candidate strictly beyond the current offset in [forward] direction.
    static SnapSelectResult SelectByDirection(
        const std::vector<SnapCandidate>& candidates, float currentOffset, bool forward);

    // Combined entry: |velocity| >= SNAP_VELOCITY_THRESHOLD * velocityScale uses the predicted
    // landing point (currentOffset + predictDelta), otherwise the position threshold. Direction is
    // derived from velocity, or from predictDelta when the velocity is near zero.
    static SnapSelectResult SelectSnapTarget(const std::vector<SnapCandidate>& candidates, float currentOffset,
        float velocity, float predictDelta, float threshold, float velocityScale);

    // R-3/R-7: clamp into the legal scroll range; an inverted range yields minOffset.
    static float ClampSnapOffset(float offset, float minOffset, float maxOffset);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SCROLLABLE_SCROLL_SNAP_UTILS_H
