/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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
#ifndef FOUNDATION_ACE_FRAMEWORKS_COMPONENTS_NG_PROPERTIES_LAYOUT_POLICY_PROPERTY_H
#define FOUNDATION_ACE_FRAMEWORKS_COMPONENTS_NG_PROPERTIES_LAYOUT_POLICY_PROPERTY_H

#include <optional>

#include "core/components/common/layout/constants.h"

namespace OHOS::Ace::NG {
struct LayoutPolicyProperty {
    LayoutPolicyProperty() = default;

    ~LayoutPolicyProperty() = default;

    std::string LayoutCalPolicyToString(LayoutCalPolicy layoutPolicy)
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

    std::string ToString()
    {
        std::string layoutPolicyStr = "";
        if (widthLayoutPolicy_.has_value()) {
            layoutPolicyStr.append("WidthLayoutPolicy: ").append(LayoutCalPolicyToString(widthLayoutPolicy_.value()));
        }
        if (heightLayoutPolicy_.has_value()) {
            layoutPolicyStr.append(layoutPolicyStr.length() == 0 ? "HeightLayoutPolicy: " : " HeightLayoutPolicy: ")
                .append(LayoutCalPolicyToString(heightLayoutPolicy_.value()));
        }
        return layoutPolicyStr;
    }

    std::optional<LayoutCalPolicy> widthLayoutPolicy_;
    std::optional<LayoutCalPolicy> heightLayoutPolicy_;

    bool isWidthAdaptive()
    {
        return widthLayoutPolicy_.has_value() && (widthLayoutPolicy_.value() == LayoutCalPolicy::WRAP_CONTENT ||
                                                     widthLayoutPolicy_.value() == LayoutCalPolicy::FIX_AT_IDEAL_SIZE);
    }
    bool isHeightAdaptive()
    {
        return heightLayoutPolicy_.has_value() &&
               (heightLayoutPolicy_.value() == LayoutCalPolicy::WRAP_CONTENT ||
                   heightLayoutPolicy_.value() == LayoutCalPolicy::FIX_AT_IDEAL_SIZE);
    }
    bool isAdaptive()
    {
        return isWidthAdaptive() || isHeightAdaptive();
    }
    bool isWidthMatch()
    {
        return widthLayoutPolicy_.has_value() && widthLayoutPolicy_.value() == LayoutCalPolicy::MATCH_PARENT;
    }
    bool isHeightMatch()
    {
        return heightLayoutPolicy_.has_value() && heightLayoutPolicy_.value() == LayoutCalPolicy::MATCH_PARENT;
    }
    bool isMatch()
    {
        return isWidthMatch() || isHeightMatch();
    }
    bool isAllMatch()
    {
        return isWidthMatch() && isHeightMatch();
    }
};

} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_COMPONENTS_NG_LAYOUT_POLICY_PROPERTY_H
