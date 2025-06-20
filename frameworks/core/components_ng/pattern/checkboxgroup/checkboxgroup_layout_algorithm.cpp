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

#include "core/components_ng/pattern/checkboxgroup/checkboxgroup_layout_algorithm.h"

#include "core/components/checkable/checkable_theme.h"
#include "core/pipeline/pipeline_base.h"
#include "core/components_ng/property/measure_utils.h"

namespace OHOS::Ace::NG {

std::optional<SizeF> CheckBoxGroupLayoutAlgorithm::MeasureContent(
    const LayoutConstraintF& contentConstraint, LayoutWrapper* layoutWrapper)
{
    auto themeScopeId = layoutWrapper->GetHostNode() ? layoutWrapper->GetHostNode()->GetThemeScopeId() : 0;
    InitializeParam(themeScopeId);
    auto layoutPolicy = layoutWrapper->GetLayoutProperty()->GetLayoutPolicyProperty();
    if (layoutPolicy.has_value() && layoutPolicy->IsMatch()) {
        return LayoutPolicyIsMatchParent(contentConstraint, layoutPolicy, layoutWrapper);
    }

    // Case 1: Width and height are set in the front end.
    if (contentConstraint.selfIdealSize.Width().has_value() && contentConstraint.selfIdealSize.Height().has_value() &&
        contentConstraint.selfIdealSize.IsNonNegative()) {
        auto height = contentConstraint.selfIdealSize.Height().value();
        auto width = contentConstraint.selfIdealSize.Width().value();
        auto length = std::min(width, height);
        return SizeF(length, length);
    }
    // Case 2: The front end only sets either width or height
    // 2.1 Width is set to a value
    if (contentConstraint.selfIdealSize.Width().has_value() &&
        NonNegative(contentConstraint.selfIdealSize.Width().value())) {
        auto width = contentConstraint.selfIdealSize.Width().value();
        return SizeF(width, width);
    }
    // 2.2 Height is set to a value
    if (contentConstraint.selfIdealSize.Height().has_value() &&
        NonNegative(contentConstraint.selfIdealSize.Height().value())) {
        auto height = contentConstraint.selfIdealSize.Height().value();
        return SizeF(height, height);
    }
    // Case 3: Width and height are not set in the front end, so return from the theme
    auto width = defaultWidth_ - 2 * horizontalPadding_;
    auto height = defaultHeight_ - 2 * verticalPadding_;
    auto size = SizeF(width, height);
    size.Constrain(contentConstraint.minSize, contentConstraint.maxSize);
    if (!NearEqual(size.Width(), size.Height())) {
        auto length = std::min(size.Width(), size.Height());
        size.SetWidth(length);
        size.SetHeight(length);
    }
    return size;
}

void CheckBoxGroupLayoutAlgorithm::InitializeParam(uint32_t themeScopeId)
{
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto checkBoxTheme = pipeline->GetTheme<CheckboxTheme>(themeScopeId);
    CHECK_NULL_VOID(checkBoxTheme);
    defaultWidth_ = checkBoxTheme->GetDefaultWidth().ConvertToPx();
    defaultHeight_ = checkBoxTheme->GetDefaultHeight().ConvertToPx();
    if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
        horizontalPadding_ = checkBoxTheme->GetDefaultPaddingSize().ConvertToPx();
        verticalPadding_ = checkBoxTheme->GetDefaultPaddingSize().ConvertToPx();
    } else {
        horizontalPadding_ = checkBoxTheme->GetHotZoneHorizontalPadding().ConvertToPx();
        verticalPadding_ = checkBoxTheme->GetHotZoneVerticalPadding().ConvertToPx();
    }
}

std::optional<SizeF> CheckBoxGroupLayoutAlgorithm::LayoutPolicyIsMatchParent(const LayoutConstraintF& contentConstraint,
    std::optional<NG::LayoutPolicyProperty> layoutPolicy, LayoutWrapper* layoutWrapper)
{
    auto height = contentConstraint.parentIdealSize.Height().value();
    auto width = contentConstraint.parentIdealSize.Width().value();
    if (layoutPolicy->IsAllMatch()) {
        auto length = std::min(width, height);
        return SizeF(length, length);
    } else if (layoutPolicy->IsWidthMatch()) {
        return SizeF(width, width);
    } else if (layoutPolicy->IsHeightMatch()) {
        return SizeF(height, height);
    }
    return SizeF();
}

} // namespace OHOS::Ace::NG
