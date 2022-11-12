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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TEXT_PICKER_TEXT_PICKER_LAYOUT_PROPERTY_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TEXT_PICKER_TEXT_PICKER_LAYOUT_PROPERTY_H

#include "base/geometry/dimension.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_property.h"
#include "core/components_ng/property/property.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT TextPickerLayoutProperty : public LinearLayoutProperty {
    DECLARE_ACE_TYPE(TextPickerLayoutProperty, LinearLayoutProperty);

public:
    TextPickerLayoutProperty() : LinearLayoutProperty(true) {};
    ~TextPickerLayoutProperty() override = default;

    RefPtr<LayoutProperty> Clone() const override
    {
        auto value = MakeRefPtr<TextPickerLayoutProperty>();
        value->LayoutProperty::UpdateLayoutProperty(DynamicCast<LayoutProperty>(this));
        value->propDefaultPickerItemHeight_ = CloneDefaultPickerItemHeight();
        value->propSelected_ = CloneSelected();
        value->propRange_ = CloneRange();
        return value;
    }

    void Reset() override
    {
        LinearLayoutProperty::Reset();
        ResetDefaultPickerItemHeight();
        ResetSelected();
        ResetRange();
    }

    void ToJsonValue(std::unique_ptr<JsonValue>& json) const override
    {
        LayoutProperty::ToJsonValue(json);

        json->Put("defaultPickerItemHeight", GetDefaultPickerItemHeightValue(Dimension(0)).ToString().c_str());
        json->Put("selected", std::to_string(GetSelectedValue(0)).c_str());
        json->Put("range", GetTextRange().c_str());
    }

    std::string GetTextRange() const
    {
        if (HasRange()) {
            auto range = GetRange();
            std::string result = "[";
            for (const auto& item : *range) {
                result += "\"";
                result += item;
                result += "\"";
                result += ",";
            }
            result = result.substr(0, result.size() - 1);
            result += "]";
            return result;
        }
        return "";
    }

    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(DefaultPickerItemHeight, Dimension, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(Selected, uint32_t, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(Range, std::vector<std::string>, PROPERTY_UPDATE_MEASURE);

private:
    ACE_DISALLOW_COPY_AND_MOVE(TextPickerLayoutProperty);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TEXT_PICKER_TEXT_PICKER_LAYOUT_PROPERTY_H
