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

#include <string>

#include "core/components_ng/property/layout_policy_property.h"

namespace OHOS::Ace::NG {
std::string LayoutPolicyProperty::LayoutCalPolicyToString(LayoutCalPolicy layoutPolicy) const
{
    switch (layoutPolicy) {
        case LayoutCalPolicy::NO_MATCH:
            return "NA";
        case LayoutCalPolicy::MATCH_PARENT:
            return "MATCH";
        case LayoutCalPolicy::WRAP_CONTENT:
            return "WRAP";
        case LayoutCalPolicy::FIX_AT_IDEAL_SIZE:
            return "FIXED";
        default:
            return "Unknown";
    }
}

std::string LayoutPolicyProperty::ToString() const
{
    std::string layoutPolicyStr;
    if (widthLayoutPolicy_.has_value()) {
        layoutPolicyStr.append("WidthLayoutPolicy: ").append(LayoutCalPolicyToString(widthLayoutPolicy_.value()));
    }
    if (heightLayoutPolicy_.has_value()) {
        layoutPolicyStr.append(layoutPolicyStr.empty() ? "HeightLayoutPolicy: " : " HeightLayoutPolicy: ")
            .append(LayoutCalPolicyToString(heightLayoutPolicy_.value()));
    }
    return layoutPolicyStr;
}

AxisLayoutPolicy CreateAxisLayoutPolicy(const LayoutPolicyProperty& layoutPolicy, Axis axis)
{
    const bool isVertical = axis == Axis::VERTICAL;
    AxisLayoutPolicy axisLayoutPolicy;
    axisLayoutPolicy.mainAxisPolicy =
        isVertical ? layoutPolicy.heightLayoutPolicy_.value_or(LayoutCalPolicy::NO_MATCH)
            : layoutPolicy.widthLayoutPolicy_.value_or(LayoutCalPolicy::NO_MATCH);
    axisLayoutPolicy.crossAxisPolicy =
        isVertical ? layoutPolicy.widthLayoutPolicy_.value_or(LayoutCalPolicy::NO_MATCH)
            : layoutPolicy.heightLayoutPolicy_.value_or(LayoutCalPolicy::NO_MATCH);
    return axisLayoutPolicy;
}

AxisLayoutPolicy CreateAxisLayoutPolicy(const std::optional<LayoutPolicyProperty>& layoutPolicy, Axis axis)
{
    return layoutPolicy.has_value() ? CreateAxisLayoutPolicy(layoutPolicy.value(), axis) : AxisLayoutPolicy {};
}
} // namespace OHOS::Ace::NG
