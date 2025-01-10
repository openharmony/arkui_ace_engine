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
#include "core/components_ng/pattern/text/text_styles.h"
#include "core/components_ng/pattern/time_picker/timepicker_model_ng.h"
#include "core/components_ng/property/property.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT TimePickerLayoutProperty : public LinearLayoutProperty {
    DECLARE_ACE_TYPE(TimePickerLayoutProperty, LinearLayoutProperty);

public:
    TimePickerLayoutProperty() : LinearLayoutProperty(false) {};
    ~TimePickerLayoutProperty() override = default;

    RefPtr<LayoutProperty> Clone() const override
    {
        auto value = MakeRefPtr<TimePickerLayoutProperty>();
        value->LayoutProperty::UpdateLayoutProperty(DynamicCast<LayoutProperty>(this));
        value->propLoop_= CloneLoop();
        value->propDisappearTextStyle_ = CloneDisappearTextStyle();
        value->propTextStyle_ = CloneTextStyle();
        value->propSelectedTextStyle_ = CloneSelectedTextStyle();
        return value;
    }

    void Reset() override
    {
        LinearLayoutProperty::Reset();
        ResetLoop();
        ResetDisappearTextStyle();
        ResetTextStyle();
        ResetSelectedTextStyle();
    }

    void ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const override
    {
        LayoutProperty::ToJsonValue(json, filter);
        /* no fixed attr below, just return */
        if (filter.IsFastFilter()) {
            return;
        }
        json->PutExtAttr("useMilitaryTime",
            V2::ConvertBoolToString(GetIsUseMilitaryTimeValue(false)).c_str(), filter);
        json->PutExtAttr("loop", V2::ConvertBoolToString(GetLoopValue(true)).c_str(), filter);
        auto disappearFont = JsonUtil::Create(true);
        disappearFont->Put("size", GetDisappearFontSizeValue(Dimension(0)).ToString().c_str());
        disappearFont->Put("weight", V2::ConvertWrapFontWeightToStirng(
            GetDisappearWeight().value_or(FontWeight::NORMAL)).c_str());
        auto disappearTextStyle = JsonUtil::Create(true);
        disappearTextStyle->Put("color", GetDisappearColor().value_or(Color::BLACK).ColorToString().c_str());
        disappearTextStyle->Put("font", disappearFont);
        json->PutExtAttr("disappearTextStyle", disappearTextStyle, filter);

        auto normalFont = JsonUtil::Create(true);
        normalFont->Put("size", GetFontSizeValue(Dimension(0)).ToString().c_str());
        normalFont->Put("weight", V2::ConvertWrapFontWeightToStirng(GetWeight().value_or(FontWeight::NORMAL)).c_str());
        auto normalTextStyle = JsonUtil::Create(true);
        normalTextStyle->Put("color", GetColor().value_or(Color::BLACK).ColorToString().c_str());
        normalTextStyle->Put("font", normalFont);
        json->PutExtAttr("textStyle", normalTextStyle, filter);

        auto selectedFont = JsonUtil::Create(true);
        selectedFont->Put("size", GetSelectedFontSizeValue(Dimension(0)).ToString().c_str());
        selectedFont->Put("weight", V2::ConvertWrapFontWeightToStirng(
            GetSelectedWeight().value_or(FontWeight::NORMAL)).c_str());
        auto selectedTextStyle = JsonUtil::Create(true);
        selectedTextStyle->Put("color", GetSelectedColor().value_or(Color::BLACK).ColorToString().c_str());
        selectedTextStyle->Put("font", selectedFont);
        json->PutExtAttr("selectedTextStyle", selectedTextStyle, filter);
        json->PutExtAttr("enableCascade",
            V2::ConvertBoolToString(GetIsEnableCascade().value_or(false)).c_str(), filter);

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
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP_ITEM(TextStyle, FontSize, FontSize, Dimension, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP_ITEM(TextStyle, TextColor, Color, Color, PROPERTY_UPDATE_MEASURE_SELF);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP_ITEM(TextStyle, FontWeight, Weight, FontWeight, PROPERTY_UPDATE_MEASURE);
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

private:
    ACE_DISALLOW_COPY_AND_MOVE(TimePickerLayoutProperty);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TIME_PICKER_TIME_PICKER_LAYOUT_PROPERTY_H
