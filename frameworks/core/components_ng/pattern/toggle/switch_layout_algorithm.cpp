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

#include "core/components_ng/pattern/toggle/switch_layout_algorithm.h"

#include "core/components_ng/pattern/toggle/switch_pattern.h"

namespace OHOS::Ace::NG {
std::optional<SizeF> SwitchLayoutAlgorithm::MeasureContent(
    const LayoutConstraintF& contentConstraint, LayoutWrapper* layoutWrapper)
{
    auto frameNode = layoutWrapper->GetHostNode();
    CHECK_NULL_RETURN(frameNode, std::nullopt);
    auto pipeline = frameNode->GetContext();
    CHECK_NULL_RETURN(pipeline, std::nullopt);
    auto pattern = frameNode->GetPattern<SwitchPattern>();
    CHECK_NULL_RETURN(pattern, std::nullopt);
    if (pattern->UseContentModifier()) {
        if (frameNode->GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_EIGHTEEN)) {
            frameNode->GetGeometryNode()->ResetContent();
        } else {
            frameNode->GetGeometryNode()->Reset();
        }
        return std::nullopt;
    }
    const auto& layoutProperty = layoutWrapper->GetLayoutProperty();
    CHECK_NULL_RETURN(layoutProperty, std::nullopt);
    float frameHeight = 0.0f;
    float frameWidth = 0.0f;
    auto switchTheme = pipeline->GetTheme<SwitchTheme>();
    CHECK_NULL_RETURN(switchTheme, std::nullopt);
    auto padding = layoutWrapper->GetLayoutProperty()->CreatePaddingAndBorder();
    if (contentConstraint.selfIdealSize.Width().has_value()) {
        frameWidth = contentConstraint.selfIdealSize.Width().value();
    } else {
        auto width = (switchTheme->GetWidth() - switchTheme->GetHotZoneHorizontalPadding() * 2).ConvertToPx();
        frameWidth = static_cast<float>(width) - padding.left.value() - padding.right.value();
        if (frameWidth > contentConstraint.maxSize.Width()) {
            frameWidth = contentConstraint.maxSize.Width();
        }
    }
    if (contentConstraint.selfIdealSize.Height().has_value()) {
        frameHeight = contentConstraint.selfIdealSize.Height().value();
    } else {
        auto height = (switchTheme->GetHeight() - switchTheme->GetHotZoneVerticalPadding() * 2).ConvertToPx();
        frameHeight = static_cast<float>(height) - padding.top.value() - padding.bottom.value();
        if (frameHeight > contentConstraint.maxSize.Height()) {
            frameHeight = contentConstraint.maxSize.Height();
        }
    }

    auto layoutPolicy = layoutProperty->GetLayoutPolicyProperty();

    if (layoutPolicy.has_value() && layoutPolicy->IsMatch()) {
        LayoutPolicyIsMatchParent(contentConstraint, layoutPolicy, frameWidth, frameHeight);
    }
    float width = 0.0f;
    float height = 0.0f;
    CalcHeightAndWidth(frameNode, height, width, frameHeight, frameWidth);

    width_ = width;
    height_ = height;

    return SizeF(width, height);
}

void SwitchLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    auto host = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(host);
    auto pattern = host->GetPattern<SwitchPattern>();
    CHECK_NULL_VOID(pattern);
    if (layoutWrapper->GetHostTag() == V2::TOGGLE_ETS_TAG && !pattern->UseContentModifier()) {
        // Switch does not have child nodes. If a child is added to a toggle, then hide the child.
        for (const auto& child : layoutWrapper->GetAllChildrenWithBuild()) {
            child->GetGeometryNode()->Reset();
            child->GetGeometryNode()->SetContentSize(SizeF());
        }
        PerformMeasureSelf(layoutWrapper);
    } else if (pattern->UseContentModifier()) {
        auto childList = layoutWrapper->GetAllChildrenWithBuild();
        std::list<RefPtr<LayoutWrapper>> builderChildList;
        for (const auto& child : childList) {
            if (child->GetHostNode()->GetId() != pattern->GetBuilderId()) {
                child->GetGeometryNode()->Reset();
                child->GetGeometryNode()->SetContentSize(SizeF());
            } else {
                auto layoutConstraint = layoutWrapper->GetLayoutProperty()->CreateChildConstraint();
                child->Measure(layoutConstraint);
                builderChildList.push_back(child);
            }
        }
        BoxLayoutAlgorithm::PerformMeasureSelfWithChildList(layoutWrapper, builderChildList);
    } else {
        BoxLayoutAlgorithm::Measure(layoutWrapper);
    }
}

void SwitchLayoutAlgorithm::CalcHeightAndWidth(
    const RefPtr<FrameNode>& host, float& height, float& width, float frameHeight, float frameWidth)
{
    CHECK_NULL_VOID(host);
    auto pipeline = host->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto switchTheme = pipeline->GetTheme<SwitchTheme>();
    CHECK_NULL_VOID(switchTheme);
    if (host->GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
        width = frameWidth;
        height = frameHeight;
    } else {
        auto ratio = switchTheme->GetRatio();
        if (frameWidth < (frameHeight * ratio)) {
            width = frameWidth;
            if (ratio == 0) {
                height = 0.0f;
            } else {
                height = NearZero(ratio) ? 0 : width / ratio;
            }
        } else if (frameWidth > (frameHeight * ratio)) {
            height = frameHeight;
            width = height * ratio;
        } else {
            height = frameHeight;
            width = frameWidth;
        }
    }
}

void SwitchLayoutAlgorithm::LayoutPolicyIsMatchParent(const LayoutConstraintF& contentConstraint,
    std::optional<NG::LayoutPolicyProperty> layoutPolicy, float& frameWidth, float& frameHeight)
{
    if (layoutPolicy->IsWidthMatch()) {
        frameWidth = contentConstraint.parentIdealSize.Width().value();
    }
    if (layoutPolicy->IsHeightMatch()) {
        frameHeight = contentConstraint.parentIdealSize.Height().value();
    }
}
} // namespace OHOS::Ace::NG
