/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include "core/components_ng/layout/box_layout_algorithm.h"

#include "core/components_ng/base/frame_node.h"

namespace OHOS::Ace::NG {

void BoxLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    auto layoutConstraint = layoutWrapper->GetLayoutProperty()->CreateChildConstraint();
    for (auto&& child : layoutWrapper->GetAllChildrenWithBuild()) {
        child->Measure(layoutConstraint);
    }
    PerformMeasureSelf(layoutWrapper);
}

void BoxLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
{
    PerformLayout(layoutWrapper);
    for (auto&& child : layoutWrapper->GetAllChildrenWithBuild()) {
        child->Layout();
    }
}

std::optional<SizeF> BoxLayoutAlgorithm::MeasureContent(
    const LayoutConstraintF& contentConstraint, LayoutWrapper* layoutWrapper)
{
    auto host = layoutWrapper->GetHostNode();
    CHECK_NULL_RETURN(host, std::nullopt);
    if (!host->IsAtomicNode()) {
        return std::nullopt;
    }
    const auto& layoutProperty = layoutWrapper->GetLayoutProperty();
    auto measureType = layoutProperty->GetMeasureType(MeasureType::MATCH_CONTENT);
    OptionalSizeF contentSize;
    do {
        // Use idea size first if it is valid.
        contentSize.UpdateSizeWithCheck(contentConstraint.selfIdealSize);
        if (contentSize.IsValid()) {
            break;
        }

        if (measureType == MeasureType::MATCH_PARENT) {
            contentSize.UpdateIllegalSizeWithCheck(contentConstraint.parentIdealSize);
            // use max is parent ideal size is invalid.
            contentSize.UpdateIllegalSizeWithCheck(contentConstraint.percentReference);
            break;
        }

        // wrap content case use min size default.
        contentSize.UpdateIllegalSizeWithCheck(contentConstraint.minSize);
    } while (false);
    return contentSize.ConvertToSizeT();
}

void BoxLayoutAlgorithm::PerformMeasureSelfWithChildList(
    LayoutWrapper* layoutWrapper, const std::list<RefPtr<LayoutWrapper>>& childList)
{
    const auto& layoutConstraint = layoutWrapper->GetLayoutProperty()->GetLayoutConstraint();
    const auto& minSize = layoutConstraint->minSize;
    const auto& maxSize = layoutConstraint->maxSize;
    const auto& padding = layoutWrapper->GetLayoutProperty()->CreatePaddingAndBorder();
    auto measureType = layoutWrapper->GetLayoutProperty()->GetMeasureType();
    OptionalSizeF frameSize;
    auto version10OrLarger =
        PipelineBase::GetCurrentContext() && PipelineBase::GetCurrentContext()->GetMinPlatformVersion() > 9;
    do {
        // Use idea size first if it is valid.
        frameSize.UpdateSizeWithCheck(layoutConstraint->selfIdealSize);
        if (frameSize.IsValid()) {
            break;
        }

        if (measureType == MeasureType::MATCH_PARENT) {
            frameSize.UpdateIllegalSizeWithCheck(layoutConstraint->parentIdealSize);
            if (frameSize.IsValid()) {
                frameSize.Constrain(minSize, maxSize, version10OrLarger);
                break;
            }
        }

        const auto& content = layoutWrapper->GetGeometryNode()->GetContent();
        if (content) {
            // use content size.
            auto contentSize = content->GetRect().GetSize();
            AddPaddingToSize(padding, contentSize);
            frameSize.UpdateIllegalSizeWithCheck(contentSize);
        } else {
            // use the max child size.
            auto childFrame = SizeF();
            float maxWidth = 0.0f;
            float maxHeight = 0.0f;
            for (const auto& child : childList) {
                if (!child) {
                    continue;
                }
                auto layoutProperty = child->GetLayoutProperty();
                if (layoutProperty && layoutProperty->GetVisibilityValue(VisibleType::VISIBLE) == VisibleType::GONE) {
                    continue;
                }
                auto childSize = child->GetGeometryNode()->GetMarginFrameSize();
                if (maxWidth < childSize.Width()) {
                    maxWidth = childSize.Width();
                }
                if (maxHeight < childSize.Height()) {
                    maxHeight = childSize.Height();
                }
                childFrame.SetSizeT(SizeF { maxWidth, maxHeight });
            }
            AddPaddingToSize(padding, childFrame);
            frameSize.UpdateIllegalSizeWithCheck(childFrame);
        }
        if (layoutConstraint->selfIdealSize.Width()) {
            frameSize.ConstrainFloat(minSize, maxSize, false, version10OrLarger);
        } else if (layoutConstraint->selfIdealSize.Height()) {
            frameSize.ConstrainFloat(minSize, maxSize, true, version10OrLarger);
        } else {
            frameSize.Constrain(minSize, maxSize, version10OrLarger);
        }
        frameSize.UpdateIllegalSizeWithCheck(SizeF { 0.0f, 0.0f });
    } while (false);
    layoutWrapper->GetGeometryNode()->SetFrameSize(frameSize.ConvertToSizeT());
}

// Called to perform measure current render node.
void BoxLayoutAlgorithm::PerformMeasureSelf(LayoutWrapper* layoutWrapper)
{
    PerformMeasureSelfWithChildList(layoutWrapper, layoutWrapper->GetAllChildrenWithBuild());
}

// Called to perform layout render node and child.
void BoxLayoutAlgorithm::PerformLayout(LayoutWrapper* layoutWrapper)
{
    // update child position.
    auto size = layoutWrapper->GetGeometryNode()->GetFrameSize();
    const auto& padding = layoutWrapper->GetLayoutProperty()->CreatePaddingAndBorder();
    MinusPaddingToSize(padding, size);
    auto left = padding.left.value_or(0);
    auto top = padding.top.value_or(0);
    auto paddingOffset = OffsetF(left, top);
    auto layoutDirection = layoutWrapper->GetLayoutProperty()->GetLayoutDirection();
    if (layoutDirection == TextDirection::AUTO) {
        layoutDirection = AceApplicationInfo::GetInstance().IsRightToLeft() ? TextDirection::RTL : TextDirection::LTR;
    }
    auto align = Alignment::CENTER;
    if (layoutWrapper->GetLayoutProperty()->GetPositionProperty()) {
        auto rawAlign = layoutWrapper->GetLayoutProperty()->GetPositionProperty()->GetAlignment().value_or(align);
        align = Alignment::GetAlignment(layoutDirection, rawAlign.GetAlignmentStr(TextDirection::AUTO));
    }
    // Update child position.
    for (const auto& child : layoutWrapper->GetAllChildrenWithBuild()) {
        SizeF childSize = child->GetGeometryNode()->GetMarginFrameSize();
        auto translate = Alignment::GetAlignPosition(size, childSize, align) + paddingOffset;
        child->GetGeometryNode()->SetMarginFrameOffset(translate);
    }
    // Update content position.
    const auto& content = layoutWrapper->GetGeometryNode()->GetContent();
    if (content) {
        auto translate = Alignment::GetAlignPosition(size, content->GetRect().GetSize(), align) + paddingOffset;
        content->SetOffset(translate);
    }
}
} // namespace OHOS::Ace::NG
