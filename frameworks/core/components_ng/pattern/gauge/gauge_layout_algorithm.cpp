/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/gauge/gauge_layout_algorithm.h"

#include "core/components/progress/progress_theme.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/gauge/gauge_pattern.h"
#include "core/components_ng/pattern/text/text_layout_algorithm.h"

namespace OHOS::Ace::NG {
namespace {
constexpr float HALF_CIRCLE = 180.0f;
constexpr float QUARTER_CIRCLE = 90.0f;
} // namespace

GaugeLayoutAlgorithm::GaugeLayoutAlgorithm() = default;

void GaugeLayoutAlgorithm::OnReset() {}

void GaugeLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    CHECK_NULL_VOID(layoutWrapper);
    auto host = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(host);
    auto pattern = host->GetPattern<GaugePattern>();
    CHECK_NULL_VOID(pattern);
    if (pattern->UseContentModifier()) {
        auto childList = layoutWrapper->GetAllChildrenWithBuild();
        std::list<RefPtr<LayoutWrapper>> list;
        for (const auto& child : childList) {
            if (pattern->GetContentModifierNode()->GetId() != child->GetHostNode()->GetId()) {
                child->GetGeometryNode()->SetContentSize(SizeF());
            } else {
                auto layoutConstraint = layoutWrapper->GetLayoutProperty()->CreateChildConstraint();
                child->Measure(layoutConstraint);
                list.push_back(child);
            }
        }
        BoxLayoutAlgorithm::PerformMeasureSelfWithChildList(layoutWrapper, list);
        return;
    }
    BoxLayoutAlgorithm::Measure(layoutWrapper);
    if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_ELEVEN)) {
        MeasureLimitValueTextWidth(layoutWrapper);
        auto geometryNode = layoutWrapper->GetGeometryNode();
        CHECK_NULL_VOID(geometryNode);
        auto idealSize = geometryNode->GetContentSize();
        MeasureLimitValueText(layoutWrapper, idealSize, true);
        MeasureLimitValueText(layoutWrapper, idealSize, false);
        MeasureFontSize(layoutWrapper);
        MeasureDescription(layoutWrapper, idealSize);
        MeasureTitleChild(layoutWrapper, idealSize);
    }
}

std::optional<SizeF> GaugeLayoutAlgorithm::MeasureContent(
    const LayoutConstraintF& contentConstraint, LayoutWrapper* layoutWrapper)
{
    auto host = layoutWrapper->GetHostNode();
    CHECK_NULL_RETURN(host, std::nullopt);
    auto pattern = host->GetPattern<GaugePattern>();
    CHECK_NULL_RETURN(pattern, std::nullopt);
    if (pattern->UseContentModifier()) {
        if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_FOURTEEN)) {
            host->GetGeometryNode()->ResetContent();
        } else {
            host->GetGeometryNode()->Reset();
        }
        return std::nullopt;
    }
    if (contentConstraint.selfIdealSize.IsValid()) {
        auto len =
            std::min(contentConstraint.selfIdealSize.Height().value(), contentConstraint.selfIdealSize.Width().value());
        return SizeF(len, len);
    }
    if (contentConstraint.selfIdealSize.Width().has_value() &&
        NonNegative(contentConstraint.selfIdealSize.Width().value())) {
        auto width = contentConstraint.selfIdealSize.Width().value();
        return SizeF(width, width);
    }
    if (contentConstraint.selfIdealSize.Height().has_value() &&
        NonNegative(contentConstraint.selfIdealSize.Height().value())) {
        auto height = contentConstraint.selfIdealSize.Height().value();
        return SizeF(height, height);
    }
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, std::nullopt);
    auto gaugeTheme = pipeline->GetTheme<ProgressTheme>();
    CHECK_NULL_RETURN(gaugeTheme, std::nullopt);
    auto defaultThickness = gaugeTheme->GetTrackWidth().ConvertToPx();
    auto size = SizeF(defaultThickness, defaultThickness);
    auto layoutConstraint = layoutWrapper->GetLayoutProperty()->GetLayoutConstraint();
    size.Constrain(layoutConstraint->minSize, layoutConstraint->maxSize);
    auto padding = layoutWrapper->GetLayoutProperty()->CreatePaddingAndBorder();
    MinusPaddingToSize(padding, size);
    if (!NearEqual(size.Width(), size.Height())) {
        auto length = std::min(size.Width(), size.Height());
        size.SetWidth(length);
        size.SetHeight(length);
    }
    return size;
}

void GaugeLayoutAlgorithm::MeasureLimitValueTextWidth(LayoutWrapper* layoutWrapper)
{
    CHECK_NULL_VOID(layoutWrapper);
    auto hostNode = AceType::DynamicCast<FrameNode>(layoutWrapper->GetHostNode());
    CHECK_NULL_VOID(hostNode);
    auto pattern = hostNode->GetPattern<GaugePattern>();
    CHECK_NULL_VOID(pattern);
    auto hasLimitValueNode = pattern->HasMinValueTextNode();
    CHECK_NULL_VOID(hasLimitValueNode);
    auto geometryNode = layoutWrapper->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);

    auto offset = geometryNode->GetContentOffset();
    auto paddingSize = geometryNode->GetPaddingSize();
    auto left = 0.0f;
    auto top = 0.0f;
    if (geometryNode->GetPadding()) {
        left = geometryNode->GetPadding()->left.value_or(0.0f);
        top = geometryNode->GetPadding()->top.value_or(0.0f);
    }
    auto radius = std::min(paddingSize.Width(), paddingSize.Height()) / 2.0f;
    auto center = Offset(offset.GetX() + left + radius, offset.GetY() + top + radius);
    auto layoutProperty = AceType::DynamicCast<GaugeLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(layoutProperty);
    auto startAngle = layoutProperty->GetStartAngleValue(DEFAULT_START_DEGREE);
    auto endAngle = layoutProperty->GetEndAngleValue(DEFAULT_END_DEGREE);

    auto pipelineContext = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    auto theme = pipelineContext->GetTheme<GaugeTheme>();
    CHECK_NULL_VOID(theme);
    auto strokeWidthValue = layoutProperty->GetStrokeWidthValue(theme->GetTrackThickness()).ConvertToPx();
    if (Negative(strokeWidthValue)) {
        strokeWidthValue = theme->GetTrackThickness().ConvertToPx();
    }

    startAngle -= QUARTER_CIRCLE;
    endAngle -= QUARTER_CIRCLE;
    auto startDegree = startAngle * M_PI / HALF_CIRCLE;
    auto endDegree = endAngle * M_PI / HALF_CIRCLE;
    startAngleOffsetX_ = center.GetX() + (radius - strokeWidthValue) * std::cos(startDegree);
    endAngleOffsetX_ = center.GetX() + (radius - strokeWidthValue) * std::cos(endDegree);
    auto diameter = radius * 2.0f;
    auto textSafeDistance = LIMIT_VALUE_MIN_SAFE_DISTANCE_RATIO * diameter +
                            LIMIT_VALUE_MAX_SAFE_DISTANCE_RATIO * diameter +
                            LIMIT_VALUE_SPACE_SAFE_DISTANCE_RATIO * diameter;
    limitValueTextWidth_ = (endAngleOffsetX_ - startAngleOffsetX_ - textSafeDistance) * 0.5f;
}

void GaugeLayoutAlgorithm::MeasureLimitValueText(LayoutWrapper* layoutWrapper, const SizeF& parentSize, bool isMin)
{
    auto hostNode = AceType::DynamicCast<FrameNode>(layoutWrapper->GetHostNode());
    CHECK_NULL_VOID(hostNode);
    auto pattern = hostNode->GetPattern<GaugePattern>();
    CHECK_NULL_VOID(pattern);
    auto hasLimitValueNode = isMin ? pattern->HasMinValueTextNode() : pattern->HasMaxValueTextNode();
    CHECK_NULL_VOID(hasLimitValueNode);
    auto layoutProperty = AceType::DynamicCast<GaugeLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(layoutProperty);
    auto childLayoutConstraint = layoutProperty->CreateChildConstraint();
    childLayoutConstraint.parentIdealSize = OptionalSizeF(parentSize);
    auto layoutGeometryNode = layoutWrapper->GetGeometryNode();
    CHECK_NULL_VOID(layoutGeometryNode);
    auto paddingSize = layoutGeometryNode->GetPaddingSize();
    auto diameter = std::min(paddingSize.Width(), paddingSize.Height());
    auto width = limitValueTextWidth_;
    auto height = diameter * LIMIT_VALUE_MIN_OR_MAX_HEIGHT_RATIO;
    if (!layoutProperty->GetIsShowLimitValueValue(false)) {
        width = 0.0f;
        height = 0.0f;
    }
    childLayoutConstraint.selfIdealSize = { width, height };

    auto hasLimitValueNodeId = isMin ? pattern->GetMinValueTextId() : pattern->GetMaxValueTextId();
    auto index = hostNode->GetChildIndexById(hasLimitValueNodeId);
    auto limitValueTextWrapper = layoutWrapper->GetOrCreateChildByIndex(index);
    CHECK_NULL_VOID(limitValueTextWrapper);
    limitValueTextWrapper->Measure(childLayoutConstraint);
}

void GaugeLayoutAlgorithm::MeasureDescription(LayoutWrapper* layoutWrapper, const SizeF& parentSize)
{
    auto hostNode = AceType::DynamicCast<FrameNode>(layoutWrapper->GetHostNode());
    CHECK_NULL_VOID(hostNode);
    auto pattern = hostNode->GetPattern<GaugePattern>();
    CHECK_NULL_VOID(pattern);
    CHECK_NULL_VOID(pattern->HasDescriptionNode());
    auto layoutGeometryNode = layoutWrapper->GetGeometryNode();
    CHECK_NULL_VOID(layoutGeometryNode);
    auto layoutProperty = AceType::DynamicCast<GaugeLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(layoutProperty);
    auto childLayoutConstraint = layoutProperty->CreateChildConstraint();
    childLayoutConstraint.parentIdealSize = OptionalSizeF(parentSize);
    auto paddingSize = layoutGeometryNode->GetPaddingSize();
    auto diameter = std::min(paddingSize.Width(), paddingSize.Height());
    auto width = diameter * DESCRIPTION_NODE_WIDTH_RATIO;
    auto height = diameter * DESCRIPTION_NODE_HEIGHT_RATIO;

    auto index = hostNode->GetChildIndexById(pattern->GetDescriptionNodeId());
    auto descriptionLayoutWrapper = layoutWrapper->GetOrCreateChildByIndex(index);
    CHECK_NULL_VOID(descriptionLayoutWrapper);

    if (CheckDescriptionIsImageNode(descriptionLayoutWrapper)) {
        width = diameter * DESCRIPTION_IMAGE_NODE_WIDTH_RATIO;
        height = diameter * DESCRIPTION_IMAGE_NODE_HEIGHT_RATIO;
    }
    if (!layoutProperty->GetIsShowDescriptionValue(false)) {
        width = 0.0f;
        height = 0.0f;
    }
    childLayoutConstraint.selfIdealSize = { width, height };
    descriptionLayoutWrapper->Measure(childLayoutConstraint);
}

void GaugeLayoutAlgorithm::MeasureTitleChild(LayoutWrapper* layoutWrapper, const SizeF& parentSize)
{
    auto hostNode = AceType::DynamicCast<FrameNode>(layoutWrapper->GetHostNode());
    CHECK_NULL_VOID(hostNode);
    auto pattern = hostNode->GetPattern<GaugePattern>();
    CHECK_NULL_VOID(pattern);
    CHECK_NULL_VOID(pattern->HasTitleChildNode());
    auto layoutGeometryNode = layoutWrapper->GetGeometryNode();
    CHECK_NULL_VOID(layoutGeometryNode);
    auto layoutProperty = layoutWrapper->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    auto childLayoutConstraint = layoutProperty->CreateChildConstraint();
    childLayoutConstraint.parentIdealSize = OptionalSizeF(parentSize);
    auto paddingSize = layoutGeometryNode->GetPaddingSize();
    auto diameter = std::min(paddingSize.Width(), paddingSize.Height());
    childLayoutConstraint.minSize = { 0.0f, 0.0f };
    childLayoutConstraint.maxSize = { diameter, diameter };
    childLayoutConstraint.selfIdealSize = { diameter, diameter };
    auto index = hostNode->GetChildIndexById(pattern->GetTitleChildId());
    auto titleChildLayoutWrapper = layoutWrapper->GetOrCreateChildByIndex(index);
    CHECK_NULL_VOID(titleChildLayoutWrapper);
    titleChildLayoutWrapper->Measure(childLayoutConstraint);
}

void GaugeLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
{
    if (Container::LessThanAPIVersion(PlatformVersion::VERSION_ELEVEN)) {
        BoxLayoutAlgorithm::Layout(layoutWrapper);
        return;
    }
    auto hostNode = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(hostNode);
    auto gaugePattern = hostNode->GetPattern<GaugePattern>();
    CHECK_NULL_VOID(gaugePattern);
    if (gaugePattern->UseContentModifier()) {
        BoxLayoutAlgorithm::Layout(layoutWrapper);
        return;
    }
    auto layoutGeometryNode = layoutWrapper->GetGeometryNode();
    CHECK_NULL_VOID(layoutGeometryNode);
    CHECK_NULL_VOID(layoutGeometryNode->GetPadding());
    auto paddingSize = layoutGeometryNode->GetPaddingSize();
    auto left = layoutGeometryNode->GetPadding()->left.value_or(0.0f);
    auto top = layoutGeometryNode->GetPadding()->top.value_or(0.0f);
    auto diameter = std::min(paddingSize.Width(), paddingSize.Height());
    auto offset = layoutGeometryNode->GetContentOffset();
    OffsetF circularOffset = offset + OffsetF(left, top);
    auto allChildrenWrapperList = layoutWrapper->GetAllChildrenWithBuild();
    for (const auto& child : allChildrenWrapperList) {
        auto childNode = child->GetHostNode();
        CHECK_NULL_VOID(childNode);
        auto nodeId = childNode->GetId();
        OffsetF childOffset;
        if (nodeId == gaugePattern->GetDescriptionNodeId()) {
            if (CheckDescriptionIsImageNode(child)) {
                childOffset = circularOffset + OffsetF(DESCRIPTION_IMAGE_X * diameter, DESCRIPTION_IMAGE_Y * diameter);
            } else {
                childOffset = circularOffset + OffsetF(DESCRIPTION_X * diameter, DESCRIPTION_Y * diameter);
            }
        } else if (nodeId == gaugePattern->GetMinValueTextId()) {
            childOffset =
                circularOffset + OffsetF(startAngleOffsetX_ + LIMIT_VALUE_MIN_SAFE_DISTANCE_RATIO * diameter - left,
                                         LIMIT_VALUE_Y * diameter);
        } else if (nodeId == gaugePattern->GetMaxValueTextId()) {
            childOffset = circularOffset + OffsetF(endAngleOffsetX_ - limitValueTextWidth_ -
                                                   LIMIT_VALUE_MAX_SAFE_DISTANCE_RATIO * diameter - left,
                                                   LIMIT_VALUE_Y * diameter);
        } else if (nodeId == gaugePattern->GetTitleChildId()) {
            childOffset = circularOffset;
        }

        auto childGeometryNode = child->GetGeometryNode();
        CHECK_NULL_VOID(childGeometryNode);
        childGeometryNode->SetMarginFrameOffset(childOffset);
        child->Layout();
    }
    CHECK_NULL_VOID(indicatorIconLoadingCtx_);
    indicatorIconLoadingCtx_->MakeCanvasImage(
        SizeF(INDICATOR_WIDTH_RADIO * diameter, INDICATOR_HEIGHT_RADIO * diameter), true, ImageFit::FILL);
}

bool GaugeLayoutAlgorithm::CheckDescriptionIsImageNode(const RefPtr<LayoutWrapper>& layoutWrapper) const
{
    if (layoutWrapper->GetTotalChildCount() <= 0) {
        return false;
    }
    auto childLayoutWrapper = layoutWrapper->GetChildByIndex(0);
    CHECK_NULL_RETURN(childLayoutWrapper, false);
    return childLayoutWrapper->GetHostTag() == V2::IMAGE_ETS_TAG;
}

void GaugeLayoutAlgorithm::MeasureFontSize(LayoutWrapper* layoutWrapper)
{
    Dimension minFontSize;
    auto hasMinFontSize = GetLimitFontSize(layoutWrapper, true, minFontSize);
    Dimension maxFontSize;
    auto hasMaxFontSize = GetLimitFontSize(layoutWrapper, false, maxFontSize);

    if (hasMinFontSize && hasMaxFontSize) {
        auto fontSize = minFontSize < maxFontSize ? minFontSize : maxFontSize;
        SetLimitFontSize(layoutWrapper, true, fontSize);
        SetLimitFontSize(layoutWrapper, false, fontSize);
    }
}

bool GaugeLayoutAlgorithm::GetLimitFontSize(LayoutWrapper* layoutWrapper, bool isMin, Dimension& fontSize)
{
    CHECK_NULL_RETURN(layoutWrapper, false);
    auto hostNode = AceType::DynamicCast<FrameNode>(layoutWrapper->GetHostNode());
    CHECK_NULL_RETURN(hostNode, false);
    auto pattern = hostNode->GetPattern<GaugePattern>();
    CHECK_NULL_RETURN(pattern, false);
    auto hasLimitValueNode = isMin ? pattern->HasMinValueTextNode() : pattern->HasMaxValueTextNode();
    CHECK_NULL_RETURN(hasLimitValueNode, false);
    auto hasLimitValueNodeId = isMin ? pattern->GetMinValueTextId() : pattern->GetMaxValueTextId();
    auto index = hostNode->GetChildIndexById(hasLimitValueNodeId);
    auto limitValueTextWrapper = layoutWrapper->GetOrCreateChildByIndex(index);
    CHECK_NULL_RETURN(limitValueTextWrapper, false);
    auto textLayoutTextWrapper = limitValueTextWrapper->GetLayoutAlgorithm();
    CHECK_NULL_RETURN(textLayoutTextWrapper, false);
    auto textLayoutAlgorithm = DynamicCast<TextLayoutAlgorithm>(textLayoutTextWrapper->GetLayoutAlgorithm());
    CHECK_NULL_RETURN(textLayoutAlgorithm, false);
    auto limitTextStyle = textLayoutAlgorithm->GetTextStyle();
    if (!limitTextStyle.has_value()) {
        return false;
    }
    fontSize = limitTextStyle->GetFontSize();
    return true;
}

void GaugeLayoutAlgorithm::SetLimitFontSize(LayoutWrapper* layoutWrapper, bool isMin, const Dimension& fontSize)
{
    CHECK_NULL_VOID(layoutWrapper);
    auto hostNode = AceType::DynamicCast<FrameNode>(layoutWrapper->GetHostNode());
    CHECK_NULL_VOID(hostNode);
    auto pattern = hostNode->GetPattern<GaugePattern>();
    CHECK_NULL_VOID(pattern);
    auto hasLimitValueNode = isMin ? pattern->HasMinValueTextNode() : pattern->HasMaxValueTextNode();
    CHECK_NULL_VOID(hasLimitValueNode);
    auto hasLimitValueNodeId = isMin ? pattern->GetMinValueTextId() : pattern->GetMaxValueTextId();
    auto index = hostNode->GetChildIndexById(hasLimitValueNodeId);
    auto limitValueTextWrapper = layoutWrapper->GetOrCreateChildByIndex(index);
    CHECK_NULL_VOID(limitValueTextWrapper);
    auto textLayoutProperty = AceType::DynamicCast<TextLayoutProperty>(limitValueTextWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(textLayoutProperty);
    auto layoutConstraint = textLayoutProperty->GetLayoutConstraint();
    CHECK_NULL_VOID(layoutConstraint);
    textLayoutProperty->UpdateAdaptMaxFontSize(fontSize);
    limitValueTextWrapper->Measure(layoutConstraint);
}
} // namespace OHOS::Ace::NG
