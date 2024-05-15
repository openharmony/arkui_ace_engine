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

#include <algorithm>

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

namespace OHOS::Ace::NG {

std::optional<SizeF> CheckBoxGroupLayoutAlgorithm::MeasureContent(
    const LayoutConstraintF& contentConstraint, LayoutWrapper* layoutWrapper)
{
    auto size = CalcCheckboxContentSize(contentConstraint, layoutWrapper);
    size.Constrain(contentConstraint.minSize, contentConstraint.maxSize);
    if (!NearEqual(size.Width(), size.Height())) {
        auto length = std::min(size.Width(), size.Height());
        size.SetWidth(length);
        size.SetHeight(length);
    }
    return size;
}

SizeF CheckBoxGroupLayoutAlgorithm::CalcCheckboxContentSize(
    const LayoutConstraintF& contentConstraint, LayoutWrapper* layoutWrapper)
{
    if (contentConstraint.selfIdealSize.Width().has_value() && contentConstraint.selfIdealSize.Height().has_value() &&
        contentConstraint.selfIdealSize.IsNonNegative()) {
        auto height = contentConstraint.selfIdealSize.Height().value();
        auto width = contentConstraint.selfIdealSize.Width().value();
        auto length = std::min(width, height);
        return SizeF(length, length);
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
    CHECK_NULL_RETURN(pipeline, SizeF());
    auto checkBoxTheme = pipeline->GetTheme<CheckboxTheme>();
    CHECK_NULL_RETURN(checkBoxTheme, SizeF());
    auto defaultLength = checkBoxTheme->GetDefaultWidthNG().ConvertToPx() -
                         checkBoxTheme->GetDefaultPaddingSize().ConvertToPx() * 2.0;
    return SizeF(defaultLength, defaultLength);
}

} // namespace OHOS::Ace::NG
