/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_DATE_PICKER_DATE_PICKER_ROW_LAYOUT_PROPERTY_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_DATE_PICKER_DATE_PICKER_ROW_LAYOUT_PROPERTY_H

#include <string>
#include <vector>

#include "base/geometry/dimension.h"
#include "base/i18n/localization.h"
#include "base/json/json_util.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/base/inspector_filter.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_property.h"
#include "core/components_ng/pattern/picker_utils/picker_layout_property.h"
#include "core/components_ng/pattern/text/text_styles.h"
#include "core/components_ng/property/property.h"
#include "core/components_v2/inspector/utils.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT DataPickerRowLayoutProperty : public PickerLayoutProperty {
    DECLARE_ACE_TYPE(DataPickerRowLayoutProperty, PickerLayoutProperty);

public:
    DataPickerRowLayoutProperty() = default;
    ~DataPickerRowLayoutProperty() override = default;

    RefPtr<LayoutProperty> Clone() const override
    {
        auto value = MakeRefPtr<DataPickerRowLayoutProperty>();
        Clone(value);
        value->LayoutProperty::UpdateLayoutProperty(DynamicCast<LayoutProperty>(this));
        value->propSelectedDate_ = CloneSelectedDate();
        value->propLunar_ = CloneLunar();
        value->propCanLoop_ = CloneCanLoop();
        value->propStartDate_ = CloneStartDate();
        value->propEndDate_ = CloneEndDate();
        value->propMode_ = CloneMode();
        return value;
    }

    void Reset() override
    {
        PickerLayoutProperty::Reset();
        ResetSelectedDate();
        ResetStartDate();
        ResetEndDate();
        ResetMode();
        ResetLunar();
        ResetCanLoop();
    }

    void ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const override
    {
        PickerLayoutProperty::ToJsonValue(json, filter);
        json->PutExtAttr("lunar", V2::ConvertBoolToString(GetLunar().value_or(false)).c_str(), filter);
        json->PutExtAttr("canLoop", V2::ConvertBoolToString(GetCanLoopValue(true)).c_str(), filter);
    }

    std::string GetDateStart() const
    {
        if (HasStartDate()) {
            std::string startDate;
            startDate += std::to_string(GetStartDate()->year);
            startDate += "-";
            startDate += std::to_string(GetStartDate()->month);
            startDate += "-";
            startDate += std::to_string(GetStartDate()->day);
            return startDate;
        }
        return "1970-1-1";
    }

    std::string GetDateEnd() const
    {
        if (HasEndDate()) {
            std::string endDate;
            endDate += std::to_string(GetEndDate()->year);
            endDate += "-";
            endDate += std::to_string(GetEndDate()->month);
            endDate += "-";
            endDate += std::to_string(GetEndDate()->day);
            return endDate;
        }
        return "2100-12-31";
    }

    std::string GetDateSelected() const
    {
        if (HasSelectedDate()) {
            std::string selectedDate;
            selectedDate += std::to_string(GetSelectedDate()->year);
            selectedDate += "-";
            selectedDate += std::to_string(GetSelectedDate()->month);
            selectedDate += "-";
            selectedDate += std::to_string(GetSelectedDate()->day);
            return selectedDate;
        }
        return "";
    }

    std::string GetDatePickerMode() const
    {
        std::string mode = "";
        if (HasMode()) {
            if (GetMode() == DatePickerMode::DATE) {
                mode = "DatePickerMode.DATE";
            } else if (GetMode() == DatePickerMode::YEAR_AND_MONTH) {
                mode = "DatePickerMode.YEAR_AND_MONTH";
            } else if (GetMode() == DatePickerMode::MONTH_AND_DAY) {
                mode = "DatePickerMode.MONTH_AND_DAY";
            }
        }
        return mode;
    }

    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(SelectedDate, LunarDate, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(Lunar, bool, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(StartDate, LunarDate, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(EndDate, LunarDate, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(Mode, DatePickerMode, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(CanLoop, bool, PROPERTY_UPDATE_MEASURE);

protected:
    void Clone(RefPtr<LayoutProperty> property) const override
    {
        auto value = DynamicCast<DataPickerRowLayoutProperty>(property);
        CHECK_NULL_VOID(value);
        PickerLayoutProperty::Clone(value);
    }

private:
    ACE_DISALLOW_COPY_AND_MOVE(DataPickerRowLayoutProperty);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_DATE_PICKER_DATE_PICKER_ROW_LAYOUT_PROPERTY_H
