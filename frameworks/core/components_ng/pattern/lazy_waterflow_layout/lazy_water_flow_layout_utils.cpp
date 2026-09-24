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

#include "core/components_ng/pattern/lazy_waterflow_layout/lazy_water_flow_layout_utils.h"

#include <algorithm>
#include <cmath>
#include <sstream>

#include "base/log/log_wrapper.h"
#include "core/components_ng/pattern/lazy_layout/lazy_layout_pattern.h"
#include "core/components_ng/pattern/lazy_layout/lazy_layout_utils.h"
#include "core/components_ng/pattern/waterflow/water_flow_layout_property.h"
#include "core/components_ng/property/measure_utils.h"

namespace OHOS::Ace::NG {

void LazyWaterFlowLayoutUtils::ExpandMeasureWindowToFullRange(
    float& viewStart, float& viewEnd, float& cacheStartPos, float& cacheEndPos)
{
    viewStart = 0.0f;
    viewEnd = Infinity<float>();
    cacheStartPos = 0.0f;
    cacheEndPos = Infinity<float>();
}

void LazyWaterFlowLayoutUtils::ResolveContentCrossSize(
    const LayoutConstraintF& contentConstraint, OptionalSizeF& contentIdealSize)
{
    if (GetCrossAxisSize(contentIdealSize, Axis::VERTICAL)) {
        return;
    }
    auto maxSize = GetCrossAxisSize(contentConstraint.maxSize, Axis::VERTICAL);
    if (GreaterOrEqualToInfinity(maxSize)) {
        maxSize = GetCrossAxisSize(contentConstraint.percentReference, Axis::VERTICAL);
    }
    contentIdealSize.SetCrossSize(maxSize, Axis::VERTICAL);
}

void LazyWaterFlowLayoutUtils::BuildLaneCrossPositions(
    const std::vector<double>& laneCrossLens, float crossGap, std::vector<double>& laneCrossPos)
{
    laneCrossPos.assign(laneCrossLens.size(), 0.0);
    double laneStart = 0.0;
    for (size_t index = 0; index < laneCrossLens.size(); ++index) {
        laneCrossPos[index] = laneStart;
        laneStart += laneCrossLens[index] + crossGap;
    }
}

ReferenceEdge LazyWaterFlowLayoutUtils::ResolveChildReferenceEdge(ReferenceEdge referenceEdge)
{
    return referenceEdge == ReferenceEdge::END ? ReferenceEdge::END : ReferenceEdge::START;
}

float LazyWaterFlowLayoutUtils::ResolveChildReferencePos(float itemStart, float itemEnd, ReferenceEdge referenceEdge)
{
    return referenceEdge == ReferenceEdge::END ? itemEnd : itemStart;
}

void LazyWaterFlowLayoutUtils::ShiftMeasureWindow(
    float delta, float& viewStart, float& viewEnd, float& cacheStartPos, float& cacheEndPos)
{
    viewStart += delta;
    viewEnd += delta;
    cacheStartPos += delta;
    cacheEndPos += delta;
}

bool LazyWaterFlowLayoutUtils::IsItemVisible(
    int32_t itemIndex, int32_t layoutedStartIndex, int32_t layoutedEndIndex)
{
    return itemIndex >= layoutedStartIndex && itemIndex <= layoutedEndIndex;
}

std::string LazyWaterFlowLayoutUtils::PreParseWaterFlowTemplate(const std::string& args)
{
    static const std::string unitAuto = "auto";
    if (args.empty() || args.find(unitAuto) == std::string::npos) {
        return args;
    }
    std::stringstream stream(args);
    std::string token;
    std::string result;
    while (stream >> token) {
        if (!result.empty()) {
            result += ' ';
        }
        result += token == unitAuto ? "1fr" : token;
    }
    return result;
}

float LazyWaterFlowLayoutUtils::ResolveWaterFlowCrossSize(const RefPtr<FrameNode>& waterFlowNode)
{
    CHECK_NULL_RETURN(waterFlowNode, 0.0f);
    auto geometry = waterFlowNode->GetGeometryNode();
    if (geometry) {
        auto paddingWidth = geometry->GetPaddingSize().Width();
        if (Positive(paddingWidth)) {
            return paddingWidth;
        }
        auto frameWidth = geometry->GetFrameSize().Width();
        if (Positive(frameWidth)) {
            return frameWidth;
        }
        auto constraintOpt = geometry->GetParentLayoutConstraint();
        if (constraintOpt.has_value()) {
            auto percentWidth = constraintOpt.value().percentReference.Width();
            if (Positive(percentWidth)) {
                return percentWidth;
            }
            auto maxWidth = constraintOpt.value().maxSize.Width();
            if (std::isfinite(maxWidth) && Positive(maxWidth)) {
                return maxWidth;
            }
        }
    }
    auto layoutProperty = waterFlowNode->GetLayoutProperty<WaterFlowLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, 0.0f);
    auto contentConstraint = layoutProperty->GetContentLayoutConstraint();
    if (!contentConstraint.has_value()) {
        return 0.0f;
    }
    auto percentWidth = contentConstraint.value().percentReference.Width();
    if (Positive(percentWidth)) {
        return percentWidth;
    }
    auto maxWidth = contentConstraint.value().maxSize.Width();
    if (std::isfinite(maxWidth) && Positive(maxWidth)) {
        return maxWidth;
    }
    return 0.0f;
}

int32_t LazyWaterFlowLayoutUtils::ResolveSingleWaterFlowLaneCount(const RefPtr<FrameNode>& waterFlowNode)
{
    CHECK_NULL_RETURN(waterFlowNode, 1);
    auto layoutProperty = waterFlowNode->GetLayoutProperty<WaterFlowLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, 1);
    auto crossSize = ResolveWaterFlowCrossSize(waterFlowNode);
    if (!Positive(crossSize)) {
        return 1;
    }
    auto contentConstraint = layoutProperty->GetContentLayoutConstraint();
    auto mainPercentRefer =
        contentConstraint.has_value() ? contentConstraint.value().percentReference.Height() : crossSize;
    auto columnGapDim = layoutProperty->GetColumnsGap().value_or(Dimension(0));
    auto columnGap = contentConstraint.has_value()
        ? ConvertToPx(columnGapDim, contentConstraint.value().scaleProperty, mainPercentRefer).value_or(0.0f)
        : 0.0f;
    auto columnsTemplate = ResolveColumnsTemplate(layoutProperty, crossSize, contentConstraint);
    auto lanes = ParseTemplateArgs(PreParseWaterFlowTemplate(columnsTemplate), crossSize, std::max(columnGap, 0.0f), 1)
                     .first;
    return std::max(static_cast<int32_t>(lanes.empty() ? 1 : lanes.size()), 1);
}

bool LazyWaterFlowLayoutUtils::NeedFullRangeForDirectWaterFlow(const RefPtr<FrameNode>& frameNode)
{
    auto ancestorInfoOpt = LazyLayoutUtils::FindWaterFlowAncestorInfo(frameNode);
    if (!ancestorInfoOpt.has_value()) {
        return false;
    }
    auto ancestorInfo = ancestorInfoOpt.value();
    if (!ancestorInfo.node) {
        return false;
    }
    if (ancestorInfo.throughFlowItem) {
        // FlowItem provides its own child reference window; the outer WaterFlow lane count is irrelevant here.
        return false;
    }
    auto laneCount = ResolveSingleWaterFlowLaneCount(ancestorInfo.node);
    if (laneCount > 1) {
        TAG_LOGW(AceLogTag::ACE_LAZY_WATER_FLOW,
            "LazyWaterFlowLayout under direct multi-lane WaterFlow requires a single-lane lazy contract, "
            "lanes: %{public}d",
            laneCount);
    }
    return false;
}

AdjustOffset LazyWaterFlowLayoutUtils::GetLazyChildAdjustOffset(const RefPtr<LayoutWrapper>& item)
{
    AdjustOffset pos;
    RefPtr<UINode> child = AceType::DynamicCast<FrameNode>(item);
    while (child) {
        auto frameNode = AceType::DynamicCast<FrameNode>(child);
        if (!frameNode) {
            child = child->GetFirstChild();
            continue;
        }
        auto layoutProperty = frameNode->GetLayoutProperty();
        if (!layoutProperty || !layoutProperty->GetNeedLazyLayout()) {
            return pos;
        }
        auto pattern = frameNode->GetPattern<LazyLayoutPattern>();
        if (pattern) {
            return pattern->GetAndResetAdjustOffset();
        }
        child = child->GetFirstChild();
    }
    return pos;
}

} // namespace OHOS::Ace::NG
