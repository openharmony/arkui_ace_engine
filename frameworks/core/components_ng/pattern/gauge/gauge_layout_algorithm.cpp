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

#include "core/common/container.h"
#include "core/components/progress/progress_theme.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/layout/layout_wrapper.h"
#include "core/components_ng/pattern/gauge/gauge_layout_property.h"
#include "core/components_ng/pattern/gauge/gauge_pattern.h"
#include "core/components_ng/pattern/gauge/gauge_theme.h"

namespace OHOS::Ace::NG {
GaugeLayoutAlgorithm::GaugeLayoutAlgorithm() = default;

void GaugeLayoutAlgorithm::OnReset() {}

void GaugeLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    CHECK_NULL_VOID(layoutWrapper);
    auto layoutProperty = layoutWrapper->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    auto geometryNode = layoutWrapper->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    auto constraint = layoutProperty->GetLayoutConstraint();

    const auto idealSize = CreateIdealSizeByPercentRef(constraint.value(), Axis::HORIZONTAL,
        layoutProperty->GetMeasureType(MeasureType::MATCH_PARENT)).ConvertToSizeT();

    if (GreaterOrEqualToInfinity(idealSize.Width()) || GreaterOrEqualToInfinity(idealSize.Height())) {
        LOGW("Size is infinity.");
        geometryNode->SetFrameSize(SizeF());
        return;
    }
    geometryNode->SetFrameSize(idealSize);

    if (!Container::LessThanAPIVersion(PlatformVersion::VERSION_ELEVEN)) {
        MeasureLimitValueText(layoutWrapper, idealSize, true);
        MeasureLimitValueText(layoutWrapper, idealSize, false);
        MeasureDescription(layoutWrapper, idealSize);
        MeasureTitleChild(layoutWrapper, idealSize);
    }
}

std::optional<SizeF> GaugeLayoutAlgorithm::MeasureContent(
    const LayoutConstraintF& contentConstraint, LayoutWrapper* layoutWrapper)
{
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

void GaugeLayoutAlgorithm::MeasureLimitValueText(
    LayoutWrapper* layoutWrapper, const SizeF& parentSize, const bool isMin)
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
    auto width = diameter * LIMIT_VALUE_MIN_OR_MAX_WIDTH_RATIO;
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
    auto index = hostNode->GetChildIndexById(pattern->GetTitleChildId());
    auto titleChildLayoutWrapper = layoutWrapper->GetOrCreateChildByIndex(index);
    CHECK_NULL_VOID(titleChildLayoutWrapper);
    titleChildLayoutWrapper->Measure(childLayoutConstraint);
}

void GaugeLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
{
    if (Container::LessThanAPIVersion(PlatformVersion::VERSION_ELEVEN)) {
        return;
    }
    auto hostNode = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(hostNode);
    auto gaugePattern = hostNode->GetPattern<GaugePattern>();
    CHECK_NULL_VOID(gaugePattern);
    auto layoutGeometryNode = layoutWrapper->GetGeometryNode();
    CHECK_NULL_VOID(layoutGeometryNode);
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
            childOffset = circularOffset + OffsetF(LIMIT_VALUE_MIN_X * diameter, LIMIT_VALUE_Y * diameter);
        } else if (nodeId == gaugePattern->GetMaxValueTextId()) {
            childOffset = circularOffset + OffsetF(LIMIT_VALUE_MAX_X * diameter, LIMIT_VALUE_Y * diameter);
        } else if (nodeId == gaugePattern->GetTitleChildId()) {
            childOffset = circularOffset;
        }

        auto childGeometryNode = child->GetGeometryNode();
        CHECK_NULL_VOID(childGeometryNode);
        childGeometryNode->SetMarginFrameOffset(childOffset);
        child->Layout();
    }
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
} // namespace OHOS::Ace::NG
