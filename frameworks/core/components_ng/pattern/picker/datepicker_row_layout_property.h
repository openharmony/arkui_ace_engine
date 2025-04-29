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
#include "core/components_ng/pattern/text/text_styles.h"
#include "core/components_ng/property/property.h"
#include "core/components_v2/inspector/utils.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT DataPickerRowLayoutProperty : public LinearLayoutProperty {
    DECLARE_ACE_TYPE(DataPickerRowLayoutProperty, LinearLayoutProperty);

public:
    DataPickerRowLayoutProperty() : LinearLayoutProperty(false) {};
    ~DataPickerRowLayoutProperty() override = default;

    RefPtr<LayoutProperty> Clone() const override
    {
        auto value = MakeRefPtr<DataPickerRowLayoutProperty>();
        value->LayoutProperty::UpdateLayoutProperty(DynamicCast<LayoutProperty>(this));
        value->propSelectedDate_ = CloneSelectedDate();
        value->propLunar_ = CloneLunar();
        value->propStartDate_ = CloneStartDate();
        value->propEndDate_ = CloneEndDate();
        value->propMode_ = CloneMode();
        value->propDisappearTextStyle_ = CloneDisappearTextStyle();
        value->propTextStyle_ = CloneTextStyle();
        value->propSelectedTextStyle_ = CloneSelectedTextStyle();
        value->propDigitalCrownSensitivity_ = CloneDigitalCrownSensitivity();
        return value;
    }

    void Reset() override
    {
        LinearLayoutProperty::Reset();
        ResetSelectedDate();
        ResetStartDate();
        ResetEndDate();
        ResetMode();
        ResetLunar();
        ResetDisappearTextStyle();
        ResetTextStyle();
        ResetSelectedTextStyle();
        ResetDigitalCrownSensitivity();
    }

    void ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const override
    {
        LayoutProperty::ToJsonValue(json, filter);
        /* no fixed attr below, just return */
        if (filter.IsFastFilter()) {
            return;
        }
        json->PutExtAttr("lunar", V2::ConvertBoolToString(GetLunar().value_or(false)).c_str(), filter);
        Color defaultDisappearColor = Color::BLACK;
        Color defaultNormalColor = Color::BLACK;
        Color defaultSelectColor = Color::BLACK;
        auto pipeline = PipelineBase::GetCurrentContext();
        auto frameNode = GetHost();
        if (pipeline && frameNode) {
            auto pickerTheme = pipeline->GetTheme<PickerTheme>(frameNode->GetThemeScopeId());
            if (pickerTheme) {
                defaultDisappearColor = pickerTheme->GetDisappearOptionStyle().GetTextColor();
                defaultNormalColor = pickerTheme->GetOptionStyle(false, false).GetTextColor();
                defaultSelectColor = pickerTheme->GetOptionStyle(true, false).GetTextColor();
            }
        }
        auto disappearFont = JsonUtil::Create(true);
        disappearFont->Put("size", GetDisappearFontSizeValue(Dimension(0)).ToString().c_str());
        disappearFont->Put("weight", V2::ConvertWrapFontWeightToStirng(
            GetDisappearWeight().value_or(FontWeight::NORMAL)).c_str());
        auto disappearTextStyle = JsonUtil::Create(true);
        disappearTextStyle->Put("color", GetDisappearColor().value_or(defaultDisappearColor).ColorToString().c_str());
        disappearTextStyle->Put("font", disappearFont);
        json->PutExtAttr("disappearTextStyle", disappearTextStyle, filter);

        auto normalFont = JsonUtil::Create(true);
        normalFont->Put("size", GetFontSizeValue(Dimension(0)).ToString().c_str());
        normalFont->Put("weight", V2::ConvertWrapFontWeightToStirng(GetWeight().value_or(FontWeight::NORMAL)).c_str());
        auto normalTextStyle = JsonUtil::Create(true);
        normalTextStyle->Put("color", GetColor().value_or(defaultNormalColor).ColorToString().c_str());
        normalTextStyle->Put("font", normalFont);
        json->PutExtAttr("textStyle", normalTextStyle, filter);

        auto selectedFont = JsonUtil::Create(true);
        selectedFont->Put("size", GetSelectedFontSizeValue(Dimension(0)).ToString().c_str());
        selectedFont->Put("weight", V2::ConvertWrapFontWeightToStirng(
            GetSelectedWeight().value_or(FontWeight::NORMAL)).c_str());
        auto selectedTextStyle = JsonUtil::Create(true);
        selectedTextStyle->Put("color", GetSelectedColor().value_or(defaultSelectColor).ColorToString().c_str());
        selectedTextStyle->Put("font", selectedFont);
        json->PutExtAttr("selectedTextStyle", selectedTextStyle, filter);
        auto crownSensitivity = GetDigitalCrownSensitivity();
        json->PutExtAttr("digitalCrownSensitivity",
            std::to_string(crownSensitivity.value_or(DEFAULT_CROWNSENSITIVITY)).c_str(), filter);
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

    ACE_DEFINE_PROPERTY_GROUP(DisappearTextStyle, FontStyle);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP_ITEM(
        DisappearTextStyle, FontSize, DisappearFontSize, Dimension, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP_ITEM(
        DisappearTextStyle, TextColor, DisappearColor, Color, PROPERTY_UPDATE_MEASURE_SELF);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP_ITEM(
        DisappearTextStyle, FontWeight, DisappearWeight, FontWeight, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP_ITEM(
        DisappearTextStyle, FontFamily, DisappearFontFamily, std::vector<std::string>, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP_ITEM(
        DisappearTextStyle, ItalicFontStyle, DisappearFontStyle, Ace::FontStyle, PROPERTY_UPDATE_MEASURE);

    ACE_DEFINE_PROPERTY_GROUP(TextStyle, FontStyle);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP_ITEM(
        TextStyle, FontSize, FontSize, Dimension, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP_ITEM(
        TextStyle, TextColor, Color, Color, PROPERTY_UPDATE_MEASURE_SELF);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP_ITEM(
        TextStyle, FontWeight, Weight, FontWeight, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP_ITEM(
        TextStyle, FontFamily, FontFamily, std::vector<std::string>, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP_ITEM(
        TextStyle, ItalicFontStyle, FontStyle, Ace::FontStyle, PROPERTY_UPDATE_MEASURE);

    ACE_DEFINE_PROPERTY_GROUP(SelectedTextStyle, FontStyle);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP_ITEM(
        SelectedTextStyle, FontSize, SelectedFontSize, Dimension, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP_ITEM(
        SelectedTextStyle, TextColor, SelectedColor, Color, PROPERTY_UPDATE_MEASURE_SELF);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP_ITEM(
        SelectedTextStyle, FontWeight, SelectedWeight, FontWeight, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP_ITEM(
        SelectedTextStyle, FontFamily, SelectedFontFamily, std::vector<std::string>, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP_ITEM(
        SelectedTextStyle, ItalicFontStyle, SelectedFontStyle, Ace::FontStyle, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(DigitalCrownSensitivity, int32_t, PROPERTY_UPDATE_MEASURE);
private:
    ACE_DISALLOW_COPY_AND_MOVE(DataPickerRowLayoutProperty);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_DATE_PICKER_DATE_PICKER_ROW_LAYOUT_PROPERTY_H
