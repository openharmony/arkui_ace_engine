/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TIME_PICKER_TIME_PICKER_LAYOUT_PROPERTY_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TIME_PICKER_TIME_PICKER_LAYOUT_PROPERTY_H

#include <string>
#include <vector>

#include "base/geometry/dimension.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/base/inspector_filter.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_property.h"
#include "core/components_ng/pattern/picker_utils/picker_layout_property.h"
#include "core/components_ng/pattern/text/text_styles.h"
#include "core/components_ng/pattern/time_picker/timepicker_model_ng.h"
#include "core/components_ng/property/property.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT TimePickerLayoutProperty : public PickerLayoutProperty {
    DECLARE_ACE_TYPE(TimePickerLayoutProperty, PickerLayoutProperty);

public:
    TimePickerLayoutProperty() = default;
    ~TimePickerLayoutProperty() override = default;

    RefPtr<LayoutProperty> Clone() const override
    {
        auto value = MakeRefPtr<TimePickerLayoutProperty>();
        Clone(value);
        value->LayoutProperty::UpdateLayoutProperty(DynamicCast<LayoutProperty>(this));
        value->propLoop_ = CloneLoop();
        return value;
    }

    void Reset() override
    {
        PickerLayoutProperty::Reset();
        ResetLoop();
    }

    void ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const override
    {
        PickerLayoutProperty::ToJsonValue(json, filter);
        json->PutExtAttr("useMilitaryTime",
            V2::ConvertBoolToString(GetIsUseMilitaryTimeValue(false)).c_str(), filter);
        json->PutExtAttr("loop", V2::ConvertBoolToString(GetLoopValue(true)).c_str(), filter);

        auto options = JsonUtil::Create(true);
        options->Put("hour", TimeFormat::GetHourFormat(
            GetPrefixHourValue(0), GetIsUseMilitaryTimeValue(false)).c_str());
        options->Put("minute", TimeFormat::GetMinuteFormat(GetPrefixMinuteValue(0)).c_str());
        if (GetPrefixSecondValue(0) != static_cast<int32_t>(ZeroPrefixType::OFF)) {
            options->Put("second", TimeFormat::GetSecondFormat(GetPrefixSecondValue(0)).c_str());
        }
        json->PutExtAttr("dateTimeOptions", options, filter);
    }

    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(IsUseMilitaryTime, bool, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(Loop, bool, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(PrefixHour, int32_t, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(PrefixMinute, int32_t, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(PrefixSecond, int32_t, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(IsEnableCascade, bool, PROPERTY_UPDATE_MEASURE);

protected:
    void Clone(RefPtr<LayoutProperty> property) const override
    {
        auto value = DynamicCast<TimePickerLayoutProperty>(property);
        CHECK_NULL_VOID(value);
        PickerLayoutProperty::Clone(value);
    }

private:
    ACE_DISALLOW_COPY_AND_MOVE(TimePickerLayoutProperty);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TIME_PICKER_TIME_PICKER_LAYOUT_PROPERTY_H
