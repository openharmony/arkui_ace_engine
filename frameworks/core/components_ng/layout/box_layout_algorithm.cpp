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

#include "core/pipeline_ng/pipeline_context.h"
#include "core/components_ng/layout/box_layout_algorithm.h"

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/property/measure_utils.h"
#include "core/pipeline/pipeline_base.h"

namespace OHOS::Ace::NG {

void BoxLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    auto layoutConstraint = layoutWrapper->GetLayoutProperty()->CreateChildConstraint();
    auto host = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(host);
    auto pattern = host->GetPattern();
    CHECK_NULL_VOID(pattern);
    bool isEnableChildrenMatchParent = pattern->IsEnableChildrenMatchParent();
    for (auto&& child : layoutWrapper->GetAllChildrenWithBuild()) {
        auto childLayoutProperty = child->GetLayoutProperty();
        CHECK_NULL_CONTINUE(childLayoutProperty);
        auto layoutPolicy = childLayoutProperty->GetLayoutPolicyProperty();
        if (isEnableChildrenMatchParent && layoutPolicy.has_value()) {
            auto widthLayoutPolicy = layoutPolicy.value().widthLayoutPolicy_;
            auto heightLayoutPolicy = layoutPolicy.value().heightLayoutPolicy_;
            if (widthLayoutPolicy.value_or(LayoutCalPolicy::NO_MATCH) != LayoutCalPolicy::NO_MATCH ||
                heightLayoutPolicy.value_or(LayoutCalPolicy::NO_MATCH) != LayoutCalPolicy::NO_MATCH) {
                layoutPolicyChildren_.emplace_back(child);
                continue;
            }
        }
        child->Measure(layoutConstraint);
    }
    PerformMeasureSelf(layoutWrapper);
    if (isEnableChildrenMatchParent) {
        auto frameSize = layoutWrapper->GetGeometryNode()->GetFrameSize();
        MeasureAdaptiveLayoutChildren(layoutWrapper, frameSize);
    }
}

void BoxLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
{
    auto host = layoutWrapper->GetHostNode();
    if (host && !host->GetIgnoreLayoutProcess() && GetNeedPostponeForIgnore()) {
        return;
    }
    PerformLayout(layoutWrapper);
    for (auto&& child : layoutWrapper->GetAllChildrenWithBuild()) {
        child->Layout();
    }
}

std::optional<SizeF> BoxLayoutAlgorithm::MeasureContent(
    const LayoutConstraintF& contentConstraint, LayoutWrapper* layoutWrapper)
{
    return PerformMeasureContent(contentConstraint, layoutWrapper);
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
    bool isEnableMatchParent = layoutWrapper->GetHostNode() && layoutWrapper->GetHostNode()->GetPattern() &&
                               layoutWrapper->GetHostNode()->GetPattern()->IsEnableMatchParent();
    bool isEnableFix = layoutWrapper->GetHostNode() && layoutWrapper->GetHostNode()->GetPattern() &&
                       layoutWrapper->GetHostNode()->GetPattern()->IsEnableFix();
    auto widthLayoutPolicy = LayoutCalPolicy::NO_MATCH;
    auto heightLayoutPolicy = LayoutCalPolicy::NO_MATCH;
    auto layoutPolicy = layoutWrapper->GetLayoutProperty()->GetLayoutPolicyProperty();
    bool isChildComponentContent = false;
    bool isChildColumnLayout = false;
    if (layoutPolicy.has_value()) {
        widthLayoutPolicy = layoutPolicy.value().widthLayoutPolicy_.value_or(LayoutCalPolicy::NO_MATCH);
        heightLayoutPolicy = layoutPolicy.value().heightLayoutPolicy_.value_or(LayoutCalPolicy::NO_MATCH);
        isChildComponentContent = layoutWrapper->GetHostNode() && layoutWrapper->GetHostNode()->GetPattern() &&
                                  layoutWrapper->GetHostNode()->GetPattern()->IsChildComponentContent();
        isChildColumnLayout = layoutWrapper->GetHostNode() && layoutWrapper->GetHostNode()->GetPattern() &&
                              layoutWrapper->GetHostNode()->GetPattern()->IsChildColumnLayout();
    }
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
        auto fixIdealSize = OptionalSizeF();
        if (content && !isChildComponentContent) {
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
                // If the child components are arranged in a Column layout ，isChildColumnLayout is true
                if (!isChildColumnLayout && maxHeight < childSize.Height()) {
                    maxHeight = childSize.Height();
                } else if (isChildColumnLayout && 0 < childSize.Height()) {
                    maxHeight += childSize.Height();
                }
                childFrame.SetSizeT(SizeF { maxWidth, maxHeight });
            }
            AddPaddingToSize(padding, childFrame);
            frameSize.UpdateIllegalSizeWithCheck(childFrame);
            fixIdealSize =
                UpdateOptionSizeByCalcLayoutConstraint(OptionalSizeF(childFrame.Width(), childFrame.Height()),
                    layoutWrapper->GetLayoutProperty()->GetCalcLayoutConstraint(),
                    layoutWrapper->GetLayoutProperty()->GetLayoutConstraint()->percentReference);
        }
        if (layoutConstraint->selfIdealSize.Width()) {
            frameSize.ConstrainFloat(minSize, maxSize, false, version10OrLarger);
        } else if (layoutConstraint->selfIdealSize.Height()) {
            frameSize.ConstrainFloat(minSize, maxSize, true, version10OrLarger);
        } else {
            frameSize.Constrain(minSize, maxSize, version10OrLarger);
        }
        if (isEnableFix) {
            if (widthLayoutPolicy == LayoutCalPolicy::FIX_AT_IDEAL_SIZE) {
                frameSize.SetWidth(fixIdealSize.Width());
            }
            if (heightLayoutPolicy == LayoutCalPolicy::FIX_AT_IDEAL_SIZE) {
                frameSize.SetHeight(fixIdealSize.Height());
            }
        }
        frameSize.UpdateIllegalSizeWithCheck(SizeF { 0.0f, 0.0f });
    } while (false);
    if (isEnableMatchParent && layoutPolicy.has_value()) {
        auto layoutPolicySize = ConstrainIdealSizeByLayoutPolicy(
            layoutConstraint.value(), widthLayoutPolicy, heightLayoutPolicy, Axis::HORIZONTAL)
                                    .ConvertToSizeT();
        auto host = layoutWrapper->GetHostNode();
        CHECK_NULL_VOID(host);
        auto pattern = host->GetPattern();
        CHECK_NULL_VOID(pattern);
        bool isEqualWidthAndHeight = pattern->isEqualWidthAndHeight();
        if (isEqualWidthAndHeight && (layoutPolicySize.Width() != layoutPolicySize.Height())) {
            layoutPolicySize.SetHeight(std::max(layoutPolicySize.Width(), layoutPolicySize.Height()));
            layoutPolicySize.SetWidth(layoutPolicySize.Height());
        }
        frameSize.UpdateSizeWithCheck(layoutPolicySize);
    }
    layoutWrapper->GetGeometryNode()->SetFrameSize(frameSize.ConvertToSizeT());
}

// Called to perform measure current render node.
void BoxLayoutAlgorithm::PerformMeasureSelf(LayoutWrapper* layoutWrapper)
{
    CHECK_NULL_VOID(layoutWrapper);
    PerformMeasureSelfWithChildList(layoutWrapper, layoutWrapper->GetAllChildrenWithBuild());
}

void BoxLayoutAlgorithm::MeasureAdaptiveLayoutChildren(LayoutWrapper* layoutWrapper, SizeF& frameSize)
{
    auto layoutConstraint = layoutWrapper->GetLayoutProperty()->CreateChildConstraint();
    auto padding = layoutWrapper->GetLayoutProperty()->CreatePaddingAndBorder();
    MinusPaddingToNonNegativeSize(padding, frameSize);
    layoutConstraint.parentIdealSize.SetSize(frameSize);
    auto host = layoutWrapper->GetHostNode();
    IgnoreLayoutSafeAreaBundle bundle;
    for (const auto& child : layoutPolicyChildren_) {
        auto childNode = child->GetHostNode();
        if (childNode && childNode->GetLayoutProperty() && childNode->GetLayoutProperty()->IsExpandConstraintNeeded()) {
            bundle.first.emplace_back(childNode);
            child->GetGeometryNode()->SetParentLayoutConstraint(layoutConstraint);
            SetNeedPostponeForIgnore();
            continue;
        }
        child->Measure(layoutConstraint);
    }
    if (host && host->GetContext() && GetNeedPostponeForIgnore()) {
        auto context = host->GetContext();
        bundle.second = host;
        context->AddIgnoreLayoutSafeAreaBundle(std::move(bundle));
    }
}

// Called to perform layout render node and child.
void BoxLayoutAlgorithm::PerformLayout(LayoutWrapper* layoutWrapper)
{
    CHECK_NULL_VOID(layoutWrapper);
    // update child position.
    auto size = layoutWrapper->GetGeometryNode()->GetFrameSize();
    const auto& padding = layoutWrapper->GetLayoutProperty()->CreatePaddingAndBorder();
    MinusPaddingToSize(padding, size);
    auto left = padding.left.value_or(0);
    auto top = padding.top.value_or(0);
    auto paddingOffset = OffsetF(left, top);
    auto align = Alignment::CENTER;
    if (layoutWrapper->GetLayoutProperty()->GetPositionProperty()) {
        auto isMirrorable = layoutWrapper->GetLayoutProperty()->GetPositionProperty()->GetIsMirrorable()
            .value_or(false);
        if (isMirrorable) {
            auto alignment = layoutWrapper->GetLayoutProperty()->GetPositionProperty()->GetLocalizedAlignment()
                .value_or("center");
            align= MapLocalizedToAlignment(alignment);
        } else {
            align = layoutWrapper->GetLayoutProperty()->GetPositionProperty()->GetAlignment().value_or(align);
        }
    }
    // Update child position.
    for (const auto& child : layoutWrapper->GetAllChildrenWithBuild()) {
        SizeF childSize = child->GetGeometryNode()->GetMarginFrameSize();
        auto host = layoutWrapper->GetHostNode();
        auto childNode = child->GetHostNode();
        if (host && childNode && childNode->GetLayoutProperty() &&
            childNode->GetLayoutProperty()->IsIgnoreOptsValid()) {
            IgnoreLayoutSafeAreaOpts& opts = *(childNode->GetLayoutProperty()->GetIgnoreLayoutSafeAreaOpts());
            auto sae = host->GetAccumulatedSafeAreaExpand(true, opts);
            auto adjustSize = size + sae.Size();
            auto translate = Alignment::GetAlignPosition(adjustSize, childSize, align) + paddingOffset;
            translate -= sae.Offset();
            child->GetGeometryNode()->SetMarginFrameOffset(translate);
        } else {
            auto translate = Alignment::GetAlignPosition(size, childSize, align) + paddingOffset;
            child->GetGeometryNode()->SetMarginFrameOffset(translate);
        }
    }
    // Update content position.
    const auto& content = layoutWrapper->GetGeometryNode()->GetContent();
    if (content) {
        auto translate = Alignment::GetAlignPosition(size, content->GetRect().GetSize(), align) + paddingOffset;
        content->SetOffset(translate);
    }
}

std::optional<SizeF> BoxLayoutAlgorithm::PerformMeasureContent(
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

Alignment BoxLayoutAlgorithm::MapLocalizedToAlignment(std::string localizedAlignment)
{
    static const std::unordered_map<std::string, Alignment> alignmentMap = {
        {"top_start", Alignment::TOP_LEFT},
        {"top", Alignment::TOP_CENTER},
        {"top_end", Alignment::TOP_RIGHT},
        {"start", Alignment::CENTER_LEFT},
        {"center", Alignment::CENTER},
        {"end", Alignment::CENTER_RIGHT},
        {"bottom_start", Alignment::BOTTOM_LEFT},
        {"bottom", Alignment::BOTTOM_CENTER},
        {"bottom_end", Alignment::BOTTOM_RIGHT}
    };

    auto it = alignmentMap.find(localizedAlignment);
    if (it != alignmentMap.end()) {
        return it->second;
    }
    return Alignment::CENTER;
}
} // namespace OHOS::Ace::NG
