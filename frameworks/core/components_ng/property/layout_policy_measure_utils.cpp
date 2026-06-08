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

#include "core/components_ng/property/measure_utils.h"

namespace OHOS::Ace::NG {
OptionalSizeF ConstrainIdealSizeByLayoutPolicy(const LayoutConstraintF& layoutConstraint,
    LayoutCalPolicy widthLayoutPolicy, LayoutCalPolicy heightLayoutPolicy, Axis axis)
{
    bool isHorizontal = axis == Axis::HORIZONTAL;
    bool mainAxisMatchParent = (isHorizontal ? widthLayoutPolicy : heightLayoutPolicy) == LayoutCalPolicy::MATCH_PARENT;
    bool crossAxisMatchParent =
        (isHorizontal ? heightLayoutPolicy : widthLayoutPolicy) == LayoutCalPolicy::MATCH_PARENT;
    OptionalSizeF idealSize;
    if (mainAxisMatchParent) {
        auto parentMainSize = layoutConstraint.parentIdealSize.MainSize(axis);
        if (parentMainSize) {
            idealSize.SetMainSize(parentMainSize.value(), axis);
        }
    }
    if (crossAxisMatchParent) {
        auto parentCrossSize = layoutConstraint.parentIdealSize.CrossSize(axis);
        if (parentCrossSize) {
            idealSize.SetCrossSize(parentCrossSize.value(), axis);
        }
    }
    return idealSize;
}

OptionalSizeF ConstrainIdealSizeByLayoutPolicy(
    const LayoutConstraintF& layoutConstraint, const std::optional<NG::LayoutPolicyProperty>& layoutPolicy, Axis axis)
{
    if (!layoutPolicy.has_value()) {
        return {};
    }
    return ConstrainIdealSizeByLayoutPolicy(layoutConstraint,
        layoutPolicy->widthLayoutPolicy_.value_or(LayoutCalPolicy::NO_MATCH),
        layoutPolicy->heightLayoutPolicy_.value_or(LayoutCalPolicy::NO_MATCH), axis);
}

void ApplyMainAxisExtentByLayoutPolicy(OptionalSizeF& contentIdealSize, const LayoutConstraintF& layoutConstraint,
    const std::optional<NG::LayoutPolicyProperty>& layoutPolicy, Axis axis, float mainAxisExtent)
{
    if (layoutPolicy.has_value()) {
        auto axisLayoutPolicy = CreateAxisLayoutPolicy(layoutPolicy, axis);
        auto layoutPolicySize = ConstrainIdealSizeByLayoutPolicy(layoutConstraint, layoutPolicy, axis);
        contentIdealSize.UpdateIllegalSizeWithCheck(layoutPolicySize.ConvertToSizeT());
        if (axisLayoutPolicy.IsMainAxisWrap()) {
            contentIdealSize.SetMainSize(mainAxisExtent, axis);
            contentIdealSize.Constrain(layoutConstraint.minSize, layoutConstraint.maxSize);
        } else if (axisLayoutPolicy.IsMainAxisFix() || !axisLayoutPolicy.HasMainAxisPolicy()) {
            contentIdealSize.SetMainSize(mainAxisExtent, axis);
        }
        return;
    }
    contentIdealSize.SetMainSize(mainAxisExtent, axis);
}

bool ShouldMatchChildrenByLayoutPolicy(
    float mainAxisSize, const std::optional<NG::LayoutPolicyProperty>& layoutPolicy, Axis axis)
{
    return GreaterOrEqualToInfinity(mainAxisSize) || CreateAxisLayoutPolicy(layoutPolicy, axis).IsMainAxisWrap();
}

void ApplyMatchParentIdealSizeByLayoutPolicy(OptionalSizeF& contentIdealSize, const LayoutConstraintF& layoutConstraint,
    const std::optional<NG::LayoutPolicyProperty>& layoutPolicy, Axis axis, bool includeMainAxis, bool includeCrossAxis)
{
    if (!layoutPolicy.has_value()) {
        return;
    }
    auto axisLayoutPolicy = CreateAxisLayoutPolicy(layoutPolicy, axis);
    if ((!includeMainAxis || !axisLayoutPolicy.IsMainAxisMatch()) &&
        (!includeCrossAxis || !axisLayoutPolicy.IsCrossAxisMatch())) {
        return;
    }

    LayoutPolicyProperty filteredPolicy = layoutPolicy.value();
    if (!includeMainAxis && axis == Axis::VERTICAL) {
        filteredPolicy.heightLayoutPolicy_ = LayoutCalPolicy::NO_MATCH;
    } else if (!includeMainAxis) {
        filteredPolicy.widthLayoutPolicy_ = LayoutCalPolicy::NO_MATCH;
    }
    if (!includeCrossAxis && axis == Axis::VERTICAL) {
        filteredPolicy.widthLayoutPolicy_ = LayoutCalPolicy::NO_MATCH;
    } else if (!includeCrossAxis) {
        filteredPolicy.heightLayoutPolicy_ = LayoutCalPolicy::NO_MATCH;
    }
    contentIdealSize.UpdateIllegalSizeWithCheck(
        ConstrainIdealSizeByLayoutPolicy(layoutConstraint, std::make_optional(filteredPolicy), axis));
}
} // namespace OHOS::Ace::NG
