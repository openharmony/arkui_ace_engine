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
#include <string>

#include "base/geometry/axis.h"
#include "base/utils/macros.h"
#include "core/components/common/layout/constants.h"

namespace OHOS::Ace::NG {
struct LayoutPolicyProperty {
    LayoutPolicyProperty() = default;

    ~LayoutPolicyProperty() = default;

    std::string LayoutCalPolicyToString(LayoutCalPolicy layoutPolicy) const;

    std::string ToString() const;

    std::optional<LayoutCalPolicy> widthLayoutPolicy_;
    std::optional<LayoutCalPolicy> heightLayoutPolicy_;

    bool IsAllNoMatch()
    {
        return IsWidthNoMatch() && IsHeightNoMatch();
    }
    bool IsWidthNoMatch()
    {
        return !widthLayoutPolicy_.has_value() || widthLayoutPolicy_.value() == LayoutCalPolicy::NO_MATCH;
    }
    bool IsHeightNoMatch()
    {
        return !heightLayoutPolicy_.has_value() || heightLayoutPolicy_.value() == LayoutCalPolicy::NO_MATCH;
    }
    bool IsWidthWrap()
    {
        return widthLayoutPolicy_.has_value() && widthLayoutPolicy_.value() == LayoutCalPolicy::WRAP_CONTENT;
    }
    bool IsHeightWrap()
    {
        return heightLayoutPolicy_.has_value() && heightLayoutPolicy_.value() == LayoutCalPolicy::WRAP_CONTENT;
    }
    bool IsWidthFix()
    {
        return widthLayoutPolicy_.has_value() && widthLayoutPolicy_.value() == LayoutCalPolicy::FIX_AT_IDEAL_SIZE;
    }
    bool IsHeightFix()
    {
        return heightLayoutPolicy_.has_value() && heightLayoutPolicy_.value() == LayoutCalPolicy::FIX_AT_IDEAL_SIZE;
    }
    bool IsWrap()
    {
        return IsWidthWrap() || IsHeightWrap();
    }
    bool IsFix()
    {
        return IsWidthFix() || IsHeightFix();
    }
    bool IsWidthMatch() const
    {
        return widthLayoutPolicy_.has_value() && widthLayoutPolicy_.value() == LayoutCalPolicy::MATCH_PARENT;
    }
    bool IsHeightMatch() const
    {
        return heightLayoutPolicy_.has_value() && heightLayoutPolicy_.value() == LayoutCalPolicy::MATCH_PARENT;
    }
    bool IsMatch() const
    {
        return IsWidthMatch() || IsHeightMatch();
    }
    bool IsAllMatch() const
    {
        return IsWidthMatch() && IsHeightMatch();
    }
    bool IsWidthAdaptive()
    {
        return IsWidthWrap() || IsWidthFix();
    }
    bool IsHeightAdaptive()
    {
        return IsHeightWrap() || IsHeightFix();
    }
    bool IsAdaptive()
    {
        return IsWidthAdaptive() || IsHeightAdaptive();
    }
    bool IsAllAdaptive()
    {
        return IsWidthAdaptive() && IsHeightAdaptive();
    }
    std::optional<LayoutCalPolicy> GetLayoutPolicy(bool isWidth)
    {
        if (isWidth) {
            return widthLayoutPolicy_;
        }
        return heightLayoutPolicy_;
    }
};

struct AxisLayoutPolicy {
    LayoutCalPolicy mainAxisPolicy = LayoutCalPolicy::NO_MATCH;
    LayoutCalPolicy crossAxisPolicy = LayoutCalPolicy::NO_MATCH;

    bool IsMainAxisMatch() const
    {
        return mainAxisPolicy == LayoutCalPolicy::MATCH_PARENT;
    }

    bool IsCrossAxisMatch() const
    {
        return crossAxisPolicy == LayoutCalPolicy::MATCH_PARENT;
    }

    bool IsMainAxisWrap() const
    {
        return mainAxisPolicy == LayoutCalPolicy::WRAP_CONTENT;
    }

    bool IsCrossAxisWrap() const
    {
        return crossAxisPolicy == LayoutCalPolicy::WRAP_CONTENT;
    }

    bool IsMainAxisFix() const
    {
        return mainAxisPolicy == LayoutCalPolicy::FIX_AT_IDEAL_SIZE;
    }

    bool IsCrossAxisFix() const
    {
        return crossAxisPolicy == LayoutCalPolicy::FIX_AT_IDEAL_SIZE;
    }

    bool HasMainAxisPolicy() const
    {
        return mainAxisPolicy != LayoutCalPolicy::NO_MATCH;
    }

    bool HasCrossAxisPolicy() const
    {
        return crossAxisPolicy != LayoutCalPolicy::NO_MATCH;
    }
};

AxisLayoutPolicy CreateAxisLayoutPolicy(const LayoutPolicyProperty& layoutPolicy, Axis axis);

ACE_FORCE_EXPORT AxisLayoutPolicy CreateAxisLayoutPolicy(
    const std::optional<LayoutPolicyProperty>& layoutPolicy, Axis axis);

} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_COMPONENTS_NG_LAYOUT_POLICY_PROPERTY_H
