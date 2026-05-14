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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_LAZY_WATERFLOW_LAYOUT_UTILS_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_LAZY_WATERFLOW_LAYOUT_UTILS_H

#include <cstdint>
#include <optional>
#include <string>
#include <vector>

#include "base/memory/referenced.h"
#include "base/utils/utils.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/layout/layout_wrapper.h"
#include "core/components_ng/pattern/lazy_layout/lazy_layout_pattern.h"
#include "core/components_ng/pattern/lazy_layout/lazy_layout_utils.h"
#include "core/components_ng/property/templates_parser.h"

namespace OHOS::Ace::NG {

inline constexpr char DEFAULT_COLUMNS_TEMPLATE[] = "1fr";

// Static helpers split out of LazyWaterFlowLayoutAlgorithm so the main .cpp stays focused on measure / layout.
class LazyWaterFlowLayoutUtils {
public:
    LazyWaterFlowLayoutUtils() = delete;
    ~LazyWaterFlowLayoutUtils() = delete;

    // Reset the measure window to [0, +inf). Used when the parent's ViewPosReference is missing or non-vertical.
    static void ExpandMeasureWindowToFullRange(
        float& viewStart, float& viewEnd, float& cacheStartPos, float& cacheEndPos);

    // Fall back to maxSize, then percentReference when maxSize is +inf.
    static void ResolveContentCrossSize(const LayoutConstraintF& contentConstraint, OptionalSizeF& contentIdealSize);

    // itemFillPolicy > columnsTemplate > DEFAULT_COLUMNS_TEMPLATE.
    template<typename LayoutPropertyT>
    static std::string ResolveColumnsTemplate(const RefPtr<LayoutPropertyT>& layoutProperty, float crossSize,
        const std::optional<LayoutConstraintF>& contentConstraint);

    // Per-lane cross-axis start positions from lane sizes + gap.
    static void BuildLaneCrossPositions(
        const std::vector<double>& laneCrossLens, float crossGap, std::vector<double>& laneCrossPos);

    // Higher-order ReferenceEdge -> START / END (anything else collapses to START).
    static ReferenceEdge ResolveChildReferenceEdge(ReferenceEdge referenceEdge);

    // start anchors at itemStart, end at itemEnd.
    static float ResolveChildReferencePos(float itemStart, float itemEnd, ReferenceEdge referenceEdge);

    static void ShiftMeasureWindow(
        float delta, float& viewStart, float& viewEnd, float& cacheStartPos, float& cacheEndPos);

    static bool IsBusinessItemVisible(int32_t businessIndex, int32_t layoutedStartIndex, int32_t layoutedEndIndex);

    // "auto" -> "1fr" so the downstream parser understands.
    static std::string PreParseWaterFlowTemplate(const std::string& args);

    // padding -> frame -> parent constraint; 0 when no info is available.
    static float ResolveWaterFlowCrossSize(const RefPtr<FrameNode>& waterFlowNode);

    static int32_t ResolveSingleWaterFlowLaneCount(const RefPtr<FrameNode>& waterFlowNode);

    // Currently logs a warning and returns false. Slot reserved for a future single-lane lazy contract.
    static bool NeedFullRangeForDirectWaterFlow(const RefPtr<FrameNode>& frameNode);

    // Drains the AdjustOffset from a nested LazyLayoutPattern descendant (Get + Reset). Empty when none exists.
    static AdjustOffset GetLazyChildAdjustOffset(const RefPtr<LayoutWrapper>& item);
};

template<typename LayoutPropertyT>
std::string LazyWaterFlowLayoutUtils::ResolveColumnsTemplate(const RefPtr<LayoutPropertyT>& layoutProperty,
    float crossSize, const std::optional<LayoutConstraintF>& contentConstraint)
{
    CHECK_NULL_RETURN(layoutProperty, DEFAULT_COLUMNS_TEMPLATE);
    // itemFillPolicy wins because it derives the effective template from runtime width.
    auto itemFillPolicy = layoutProperty->GetItemFillPolicy();
    if (!itemFillPolicy.has_value()) {
        return layoutProperty->GetColumnsTemplate().value_or(DEFAULT_COLUMNS_TEMPLATE);
    }
    auto density = contentConstraint.has_value() ? contentConstraint->scaleProperty.vpScale : 1.0f;
    return BuildItemFillPolicyColumns(itemFillPolicy.value(), crossSize, density)
        .value_or(layoutProperty->GetColumnsTemplate().value_or(DEFAULT_COLUMNS_TEMPLATE));
}

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_LAZY_WATERFLOW_LAYOUT_UTILS_H
