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

#ifndef FOUNDATION_ACE_FRAMEWORKS_COMPONENTS_NG_PROPERTIES_BORDER_PROPERTY_H
#define FOUNDATION_ACE_FRAMEWORKS_COMPONENTS_NG_PROPERTIES_BORDER_PROPERTY_H

#include <optional>

#include "base/geometry/dimension.h"
#include "base/utils/utils.h"

namespace OHOS::Ace::NG {

template<typename T>
struct BorderRadiusPropertyT {
    std::optional<T> radiusTopLeft;
    std::optional<T> radiusTopRight;
    std::optional<T> radiusBottomLeft;
    std::optional<T> radiusBottomRight;

    void SetRadius(const T& borderRadius)
    {
        radiusTopLeft = borderRadius;
        radiusTopRight = borderRadius;
        radiusBottomLeft = borderRadius;
        radiusBottomRight = borderRadius;
    }

    bool operator==(const BorderRadiusPropertyT& value) const
    {
        return (radiusTopLeft == value.radiusTopLeft) && (radiusTopRight == value.radiusTopRight) &&
               (radiusBottomLeft == value.radiusBottomLeft) && (radiusBottomRight == value.radiusBottomRight);
    }

    bool UpdateWithCheck(const BorderRadiusPropertyT& value)
    {
        bool isModified = false;
        if (value.radiusTopLeft.has_value() && (radiusTopLeft != value.radiusTopLeft)) {
            radiusTopLeft = value.radiusTopLeft;
            isModified = true;
        }
        if (value.radiusTopRight.has_value() && (radiusTopRight != value.radiusTopRight)) {
            radiusTopRight = value.radiusTopRight;
            isModified = true;
        }
        if (value.radiusBottomLeft.has_value() && (radiusBottomLeft != value.radiusBottomLeft)) {
            radiusBottomLeft = value.radiusBottomLeft;
            isModified = true;
        }
        if (value.radiusBottomRight.has_value() && (radiusBottomRight != value.radiusBottomRight)) {
            radiusBottomRight = value.radiusBottomRight;
            isModified = true;
        }
        return isModified;
    }

    std::string ToString() const
    {
        std::string str;
        str.append("radiusTopLeft: [").append(radiusTopLeft.has_value() ? radiusTopLeft->ToString() : "NA").append("]");
        str.append("radiusTopRight: [")
            .append(radiusTopRight.has_value() ? radiusTopRight->ToString() : "NA")
            .append("]");
        str.append("radiusBottomLeft: [")
            .append(radiusBottomLeft.has_value() ? radiusBottomLeft->ToString() : "NA")
            .append("]");
        str.append("radiusBottomRight: [")
            .append(radiusBottomRight.has_value() ? radiusBottomRight->ToString() : "NA")
            .append("]");
        return str;
    }
};

template<>
struct BorderRadiusPropertyT<float> {
    std::optional<float> radiusTopLeft;
    std::optional<float> radiusTopRight;
    std::optional<float> radiusBottomLeft;
    std::optional<float> radiusBottomRight;

    bool operator==(const BorderRadiusPropertyT<float>& value) const
    {
        if (radiusTopLeft.has_value() ^ value.radiusTopLeft.has_value()) {
            return false;
        }
        if (!NearEqual(radiusTopLeft.value_or(0), value.radiusTopLeft.value_or(0))) {
            return false;
        }
        if (radiusTopRight.has_value() ^ value.radiusTopRight.has_value()) {
            return false;
        }
        if (!NearEqual(radiusTopRight.value_or(0), value.radiusTopRight.value_or(0))) {
            return false;
        }
        if (radiusBottomLeft.has_value() ^ value.radiusBottomLeft.has_value()) {
            return false;
        }
        if (!NearEqual(radiusBottomLeft.value_or(0), value.radiusBottomLeft.value_or(0))) {
            return false;
        }
        if (radiusBottomRight.has_value() ^ value.radiusBottomRight.has_value()) {
            return false;
        }
        if (!NearEqual(radiusBottomRight.value_or(0), value.radiusBottomRight.value_or(0))) {
            return false;
        }
        return true;
    }

    std::string ToString() const
    {
        std::string str;
        str.append("radiusTopLeft: [")
            .append(radiusTopLeft.has_value() ? std::to_string(radiusTopLeft.value()) : "NA")
            .append("]");
        str.append("radiusTopRight: [")
            .append(radiusTopRight.has_value() ? std::to_string(radiusTopRight.value()) : "NA")
            .append("]");
        str.append("radiusBottomLeft: [")
            .append(radiusBottomLeft.has_value() ? std::to_string(radiusBottomLeft.value()) : "NA")
            .append("]");
        str.append("radiusBottomRight: [")
            .append(radiusBottomRight.has_value() ? std::to_string(radiusBottomRight.value()) : "NA")
            .append("]");
        return str;
    }
};

using BorderRadiusPropertyF = BorderRadiusPropertyT<float>;
using BorderRadiusProperty = BorderRadiusPropertyT<Dimension>;

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_COMPONENTS_NG_PROPERTIES_BORDER_PROPERTY_H