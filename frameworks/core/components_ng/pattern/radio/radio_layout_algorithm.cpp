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

#include "core/components_ng/pattern/radio/radio_layout_algorithm.h"

#include "base/geometry/axis.h"
#include "base/geometry/ng/offset_t.h"
#include "base/geometry/ng/size_t.h"
#include "base/log/ace_trace.h"
#include "base/utils/utils.h"
#include "core/components/checkable/checkable_theme.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/layout/layout_algorithm.h"
#include "core/components_ng/property/layout_constraint.h"
#include "core/components_ng/property/measure_property.h"
#include "core/components_ng/property/measure_utils.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

std::optional<SizeF> RadioLayoutAlgorithm::MeasureContent(
    const LayoutConstraintF& contentConstraint, LayoutWrapper* layoutWrapper)
{
    // Case 1: Width and height are set in the front end.
    if (contentConstraint.selfIdealSize.IsValid() && contentConstraint.selfIdealSize.IsNonNegative()) {
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
    const auto& layoutProperty = layoutWrapper->GetLayoutProperty();
    CHECK_NULL_RETURN(layoutProperty, SizeF());
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, SizeF());
    auto radioTheme = pipeline->GetTheme<RadioTheme>();
    CHECK_NULL_RETURN(radioTheme, SizeF());
    const auto& padding = layoutProperty->GetPaddingProperty();
    auto topPadding = padding->top.value_or(CalcLength(0.0_vp)).GetDimension().ConvertToPx();
    auto bottomPadding = padding->bottom.value_or(CalcLength(0.0_vp)).GetDimension().ConvertToPx();
    auto leftPadding = padding->left.value_or(CalcLength(0.0_vp)).GetDimension().ConvertToPx();
    auto rightPadding = padding->right.value_or(CalcLength(0.0_vp)).GetDimension().ConvertToPx();
    auto width = std::max(radioTheme->GetWidth().ConvertToPx() - leftPadding - rightPadding, 0.0);
    auto height = std::max(radioTheme->GetHeight().ConvertToPx() - topPadding - bottomPadding, 0.0);
    auto size = SizeF(width, height);
    size.Constrain(contentConstraint.minSize, contentConstraint.maxSize);
    auto length = std::min(size.Width(), size.Height());
    size.SetWidth(length);
    size.SetHeight(length);
    return size;
}
} // namespace OHOS::Ace::NG
