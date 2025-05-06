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

#ifndef FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_INCLUDE_UI_PROPERTIES_NG_MEASURE_PROPERTY_H
#define FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_INCLUDE_UI_PROPERTIES_NG_MEASURE_PROPERTY_H

#include "json/json_util.h"
#include "ui/base/inspector_filter.h"
#include "ui/properties/ng/calc_length.h"
#include "ui/view/ui_context.h"

namespace OHOS::Ace::NG {
static constexpr int32_t API_VERSION_SIXTEEN = 16;

template<typename T>
struct PaddingPropertyT {
    std::optional<T> left;
    std::optional<T> right;
    std::optional<T> top;
    std::optional<T> bottom;
    std::optional<T> start;
    std::optional<T> end;

    void SetEdges(const T& padding)
    {
        left = padding;
        right = padding;
        top = padding;
        bottom = padding;
    }

    void SetEdges(const T& leftValue, const T& rightValue, const T& topValue, const T& bottomValue)
    {
        left = leftValue;
        right = rightValue;
        top = topValue;
        bottom = bottomValue;
    }

    bool operator==(const PaddingPropertyT& value) const
    {
        return (left == value.left) && (right == value.right) && (top == value.top) && (bottom == value.bottom);
    }

    bool operator!=(const PaddingPropertyT& value) const
    {
        return !(*this == value);
    }

    bool UpdateWithCheck(const PaddingPropertyT& value)
    {
        if (value.start.has_value() || value.end.has_value()) {
            return UpdateLocalizedPadding(value);
        }
        start.reset();
        end.reset();
        if (*this != value) {
            left = value.left;
            right = value.right;
            top = value.top;
            bottom = value.bottom;
            return true;
        }
        return false;
    }

    bool UpdateLocalizedPadding(const PaddingPropertyT& value)
    {
        bool needUpdate = false;
        if (value.start.has_value() && start != value.start) {
            start = value.start;
            needUpdate = true;
        }
        if (value.end.has_value() && end != value.end) {
            end = value.end;
            needUpdate = true;
        }
        if (value.top.has_value() && top != value.top && (value.start.has_value() || value.end.has_value())) {
            top = value.top;
            needUpdate = true;
        }
        if (value.bottom.has_value() && bottom != value.bottom && (value.start.has_value() || value.end.has_value())) {
            bottom = value.bottom;
            needUpdate = true;
        }
        checkNeedReset(value);
        return needUpdate;
    }

    void checkNeedReset(const PaddingPropertyT& value)
    {
        RefPtr<OHOS::Ace::Kit::UIContext> uiContext = OHOS::Ace::Kit::UIContext::Current();
        bool isGreatThanSixteen = false;
        if (uiContext) {
            isGreatThanSixteen = uiContext->GreatOrEqualTargetAPIVersion(API_VERSION_SIXTEEN);
        }

        if (!value.start.has_value() && start.has_value() && isGreatThanSixteen) {
            start.reset();
        }
        if (!value.end.has_value() && end.has_value() && isGreatThanSixteen) {
            end.reset();
        }
        if (!value.top.has_value() && top.has_value() && isGreatThanSixteen) {
            top.reset();
        }
        if (!value.bottom.has_value() && bottom.has_value() && isGreatThanSixteen) {
            bottom.reset();
        }
    }

    std::string ToString() const
    {
        std::string str;
        str.append("[").append(left.has_value() ? left->ToString() : "NA");
        str.append(",").append(right.has_value() ? right->ToString() : "NA");
        str.append(",").append(top.has_value() ? top->ToString() : "NA");
        str.append(",").append(bottom.has_value() ? bottom->ToString() : "NA").append("]");
        return str;
    }
    std::string ToJsonString() const
    {
        if (top == right && right == bottom && bottom == left) {
            if (top.has_value()) {
                return top->ToString();
            }
            return "0.0";
        }
        auto jsonValue = JsonUtil::Create(true);
        jsonValue->Put("top", top.has_value() ? top->ToString().c_str() : T{}.ToString().c_str());
        jsonValue->Put("right", right.has_value() ? right->ToString().c_str() : T{}.ToString().c_str());
        jsonValue->Put("bottom", bottom.has_value() ? bottom->ToString().c_str() : T{}.ToString().c_str());
        jsonValue->Put("left", left.has_value() ? left->ToString().c_str() : T{}.ToString().c_str());
        return jsonValue->ToString();
    }

    static PaddingPropertyT FromJsonString(const std::string& str)
    {
        PaddingPropertyT property;

        if (str.empty()) {
            return property;
        }

        if (str[0] >= '0' && str[0] <= '9') {
            property.top = property.right = property.bottom = property.left = T::FromString(str);
        } else if (str[0] == '{') {
            auto json = JsonUtil::ParseJsonString(str);
            if (!json->IsValid()) {
                return property;
            }
            property.top = T::FromString(json->GetString("top"));
            property.right = T::FromString(json->GetString("right"));
            property.bottom = T::FromString(json->GetString("bottom"));
            property.left = T::FromString(json->GetString("left"));
        }

        return property;
    }
};

using PaddingProperty = PaddingPropertyT<CalcLength>;

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_INCLUDE_UI_PROPERTIES_NG_MEASURE_PROPERTY_H
