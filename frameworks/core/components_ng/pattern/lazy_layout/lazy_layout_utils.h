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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_LAZY_LAYOUT_LAZY_LAYOUT_UTILS_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_LAZY_LAYOUT_LAZY_LAYOUT_UTILS_H

#include <algorithm>
#include <optional>
#include <vector>

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/property/layout_constraint.h"

namespace OHOS::Ace::NG {

class LazyLayoutPattern;

// Ancestor WaterFlow + whether the path crosses a FlowItem (a path through FlowItem makes the WaterFlow's
// lane count irrelevant to the lazy contract).
struct WaterFlowAncestorInfo {
    RefPtr<FrameNode> node;
    bool throughFlowItem = false;
};

struct LazyLayoutViewRange {
    float start = 0.0f;
    float end = 0.0f;
};

enum class LazyLayoutMeasureMode {
    NORMAL,
    ESTIMATE,
    SKIP,
};

struct ACE_FORCE_EXPORT LazyLayoutUtils {
    static bool IsAllowedIntermediateNode(const RefPtr<UINode>& node);
    static bool IsVerticalScrollableParent(const RefPtr<UINode>& node);
    static bool IsScrollableParent(const RefPtr<UINode>& node, Axis axis);
    // FEAT-027: true when the node owns a scroll context (ScrollablePattern) or is tagged as one of the lazy
    // scroll containers (Scroll/List/WaterFlow). The lazy ancestor search treats such nodes as hard boundaries.
    static bool IsScrollableBoundary(const RefPtr<UINode>& node);
    static void ValidateLazyLayoutParent(const RefPtr<FrameNode>& host, const std::string& componentName);
    static void ValidateLazyLayoutParentWithAxis(
        const RefPtr<FrameNode>& host, const std::string& componentName, Axis axis);
    static bool ValidateAndSetLazyLayoutParent(const RefPtr<FrameNode>& host, Axis axis);
    // Cached LazyForEach hosts can be measured before they acquire a UI-tree parent. In that state the early
    // needLazyLayout marker is the only reliable identity; once a parent exists, keep validating the real chain.
    static bool ShouldEstimateDetachedLazyLayout(const RefPtr<FrameNode>& host, Axis axis);
    // Resolve how a lazy host without a complete parent-driven layout should be measured. A fresh detached host is
    // sampled to establish a height estimate, while a detached host with a persistent baseline keeps that baseline.
    // Parent-driven forward prediction estimates only fresh hosts that intersect the predictive range.
    static LazyLayoutMeasureMode ResolveMeasureMode(const RefPtr<FrameNode>& host, Axis axis,
        const std::optional<ViewPosReference>& viewPosRef, int32_t totalItemCount, int32_t lanes,
        bool hasMeasuredBaseline);
    // Sample at most two complete layout lines. A line is one item for LazyColumn and one lane set for grid/waterflow.
    static int32_t CalculateEstimateSampleCount(int32_t totalItemCount, int32_t lanes);
    // Extrapolate sampled item/line size across the full count, including uniform gaps between entries.
    static float EstimateTotalMainSize(float averageMainSize, int32_t itemCount, float space);
    // Create the canonical synthetic estimate viewport consumed by all lazy layout algorithms.
    static ViewPosReference CreateEstimateViewPosReference(Axis axis);
    static std::optional<ViewPosReference> GetViewPosReference(
        const RefPtr<FrameNode>& frameNode,
        const std::vector<std::string>& extraAllowedTags = {});
    // Find the first LazyLayoutPattern through a proxy chain whose FrameNodes were explicitly marked as
    // participating in lazy layout. Ordinary wrapper/content FrameNodes are traversal boundaries.
    static RefPtr<LazyLayoutPattern> GetLazyLayoutPattern(const RefPtr<UINode>& node);

    static LazyLayoutViewRange CalculateViewRange(const ViewPosReference& viewPosRef, float mainSize)
    {
        constexpr float PREDICT_CACHE_RATIO = 0.5f;
        const float viewSize = std::max(viewPosRef.viewPosEnd - viewPosRef.viewPosStart, 0.0f);
        const float predictCacheExtent =
            viewPosRef.deadline.has_value() ? viewSize * PREDICT_CACHE_RATIO : 0.0f;
        float viewStart = viewPosRef.viewPosStart - viewPosRef.viewExtStart - predictCacheExtent;
        float viewEnd = viewPosRef.viewPosEnd + viewPosRef.viewExtEnd + predictCacheExtent;
        const float referencePos = viewPosRef.referenceEdge == ReferenceEdge::START
            ? viewPosRef.referencePos
            : viewPosRef.referencePos - mainSize;
        return { viewStart - referencePos, viewEnd - referencePos };
    }

    // Forward parent-reserved insets through the child layout constraint, so contentOffset changes are visible
    // to constraint comparison and trigger a fresh child lazy layout.
    // Header-inline so callers don't need to link lazy_layout_utils.cpp.
    static void SetStickyInsets(LayoutConstraintF& constraint, float stickyInsetStart, float stickyInsetEnd)
    {
        if (!constraint.viewPosRef.has_value()) {
            return;
        }
        constraint.viewPosRef->stickyInsetStart = stickyInsetStart;
        constraint.viewPosRef->stickyInsetEnd = stickyInsetEnd;
    }

    // True iff a WaterFlow ancestor exists WITHOUT crossing a FlowItem.
    static bool HasDirectWaterFlowAncestor(const RefPtr<FrameNode>& frameNode);

    static std::optional<WaterFlowAncestorInfo> FindWaterFlowAncestorInfo(const RefPtr<FrameNode>& frameNode);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_LAZY_LAYOUT_LAZY_LAYOUT_UTILS_H
