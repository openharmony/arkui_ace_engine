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

#include "core/components_ng/pattern/divider/divider_layout_algorithm.h"

#include "core/components/divider/divider_theme.h"
#include "core/components_ng/pattern/divider/divider_layout_property.h"

namespace OHOS::Ace::NG {
namespace {}
DividerLayoutAlgorithm::DividerLayoutAlgorithm() = default;

std::optional<SizeF> DividerLayoutAlgorithm::MeasureContent(
    const LayoutConstraintF& contentConstraint, LayoutWrapper* layoutWrapper)
{
    auto dividerLayoutProperty = DynamicCast<DividerLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_RETURN(dividerLayoutProperty, std::nullopt);

    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, std::nullopt);
    auto theme = pipeline->GetTheme<DividerTheme>();
    CHECK_NULL_RETURN(theme, std::nullopt);
    auto defaultStrokeWidth =
        Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_TEN) ? 1.0_px : theme->GetStokeWidth();
    Dimension strokeWidth = dividerLayoutProperty->GetStrokeWidth().value_or(defaultStrokeWidth);
    constrainStrokeWidth_ = Positive(strokeWidth.ConvertToPx()) ? static_cast<float>(strokeWidth.ConvertToPx())
                                                                : static_cast<float>(defaultStrokeWidth.ConvertToPx());
    vertical_ = dividerLayoutProperty->GetVertical().value_or(false);
    SizeF constrainSize;
    strokeWidthLimitation_ = dividerLayoutProperty->GetStrokeWidthLimitation().value_or(true);
    if (!vertical_) {
        dividerLength_ = (contentConstraint.selfIdealSize.Width()) ? contentConstraint.selfIdealSize.Width().value()
                                                                   : contentConstraint.percentReference.Width();
        if (strokeWidthLimitation_) {
            constrainStrokeWidth_ = std::min(constrainStrokeWidth_, dividerLength_);
        }
        constrainStrokeWidth_ = (contentConstraint.selfIdealSize.Height())
                                    ? std::min(contentConstraint.selfIdealSize.Height().value(), constrainStrokeWidth_)
                                    : constrainStrokeWidth_;
        constrainSize = SizeF(dividerLength_, constrainStrokeWidth_);
        constrainSize.Constrain(contentConstraint.minSize, contentConstraint.maxSize);
        dividerLength_ = constrainSize.Width();
    } else {
        dividerLength_ = (contentConstraint.selfIdealSize.Height()) ? contentConstraint.selfIdealSize.Height().value()
                                                                    : contentConstraint.percentReference.Height();
        if (strokeWidthLimitation_) {
            constrainStrokeWidth_ = std::min(constrainStrokeWidth_, dividerLength_);
        }
        constrainStrokeWidth_ = (contentConstraint.selfIdealSize.Width())
                                    ? std::min(contentConstraint.selfIdealSize.Width().value(), constrainStrokeWidth_)
                                    : constrainStrokeWidth_;
        constrainSize = SizeF(constrainStrokeWidth_, dividerLength_);
        constrainSize.Constrain(contentConstraint.minSize, contentConstraint.maxSize);
        dividerLength_ = constrainSize.Height();
    }
    return constrainSize;
}
float DividerLayoutAlgorithm::GetConstrainStrokeWidth() const
{
    return constrainStrokeWidth_;
}
float DividerLayoutAlgorithm::GetDividerLength() const
{
    return dividerLength_;
}
bool DividerLayoutAlgorithm::GetVertical() const
{
    return vertical_;
}
bool DividerLayoutAlgorithm::GetStrokeWidthLimitation() const
{
    return strokeWidthLimitation_;
}
} // namespace OHOS::Ace::NG
