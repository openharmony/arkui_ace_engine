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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TEXT_PICKER_TEXT_PICKER_LAYOUT_PROPERTY_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TEXT_PICKER_TEXT_PICKER_LAYOUT_PROPERTY_H

#include "base/geometry/dimension.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_property.h"
#include "core/components_ng/pattern/text/text_styles.h"
#include "core/components_ng/property/property.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT TextPickerLayoutProperty : public LinearLayoutProperty {
    DECLARE_ACE_TYPE(TextPickerLayoutProperty, LinearLayoutProperty);

public:
    TextPickerLayoutProperty() : LinearLayoutProperty(false) {};
    ~TextPickerLayoutProperty() override = default;

    RefPtr<LayoutProperty> Clone() const override
    {
        auto value = MakeRefPtr<TextPickerLayoutProperty>();
        value->LayoutProperty::UpdateLayoutProperty(DynamicCast<LayoutProperty>(this));
        value->propDefaultPickerItemHeight_ = CloneDefaultPickerItemHeight();
        value->propSelected_ = CloneSelected();
        value->propValue_ = CloneValue();
        value->propSelecteds_ = CloneSelecteds();
        value->propValues_ = CloneValues();
        value->propSelectedIndex_ = CloneSelectedIndex();
        value->propDisappearTextStyle_ = CloneDisappearTextStyle();
        value->propTextStyle_ = CloneTextStyle();
        value->propSelectedTextStyle_ = CloneSelectedTextStyle();
        value->propCanLoop_ = CloneCanLoop();
        return value;
    }

    void Reset() override
    {
        LinearLayoutProperty::Reset();
        ResetDefaultPickerItemHeight();
        ResetSelected();
        ResetValue();
        ResetSelecteds();
        ResetValues();
        ResetSelectedIndex();
        ResetDisappearTextStyle();
        ResetTextStyle();
        ResetSelectedTextStyle();
        ResetCanLoop();
    }

    void ToJsonValue(std::unique_ptr<JsonValue>& json) const override
    {
        LayoutProperty::ToJsonValue(json);

        json->Put("defaultPickerItemHeight", GetDefaultPickerItemHeightValue(Dimension(0)).ToString().c_str());
        json->Put("selected", std::to_string(GetSelectedValue(0)).c_str());
        json->Put("value", GetValueValue("").c_str());

        auto jsonArraySelected = JsonUtil::CreateArray(true);
        auto arraySelected = CloneSelecteds().value_or(std::vector<uint32_t>());
        for (uint32_t i = 0; i < arraySelected.size(); i++) {
            auto index = std::to_string(i);
            jsonArraySelected->Put(index.c_str(), std::to_string(arraySelected[i]).c_str());
        }
        json->Put("selecteds", jsonArraySelected);

        auto jsonArraySelectedIndex = JsonUtil::CreateArray(true);
        auto arraySelectedIndex = CloneSelecteds().value_or(std::vector<uint32_t>());
        for (uint32_t i = 0; i < arraySelectedIndex.size(); i++) {
            auto index = std::to_string(i);
            jsonArraySelectedIndex->Put(index.c_str(), std::to_string(arraySelectedIndex[i]).c_str());
        }
        json->Put("selectedIndex", jsonArraySelectedIndex);

        auto jsonArrayValue = JsonUtil::CreateArray(true);
        auto arrayValue = CloneValues().value_or(std::vector<std::string>());
        for (uint32_t i = 0; i < arrayValue.size(); i++) {
            auto index = std::to_string(i);
            jsonArrayValue->Put(index.c_str(), arrayValue[i].c_str());
        }
        json->Put("values", jsonArrayValue);

        auto disappearFont = JsonUtil::Create(true);
        disappearFont->Put("size", GetDisappearFontSizeValue(Dimension(0)).ToString().c_str());
        disappearFont->Put("weight", V2::ConvertWrapFontWeightToStirng(
            GetDisappearWeight().value_or(FontWeight::NORMAL)).c_str());
        auto disappearTextStyle = JsonUtil::Create(true);
        disappearTextStyle->Put("color", GetDisappearColor().value_or(Color::BLACK).ColorToString().c_str());
        disappearTextStyle->Put("font", disappearFont);
        json->Put("disappearTextStyle", disappearTextStyle);

        auto normalFont = JsonUtil::Create(true);
        normalFont->Put("size", GetFontSizeValue(Dimension(0)).ToString().c_str());
        normalFont->Put("weight", V2::ConvertWrapFontWeightToStirng(GetWeight().value_or(FontWeight::NORMAL)).c_str());
        auto normalTextStyle = JsonUtil::Create(true);
        normalTextStyle->Put("color", GetColor().value_or(Color::BLACK).ColorToString().c_str());
        normalTextStyle->Put("font", normalFont);
        json->Put("textStyle", normalTextStyle);

        auto selectedFont = JsonUtil::Create(true);
        selectedFont->Put("size", GetSelectedFontSizeValue(Dimension(0)).ToString().c_str());
        selectedFont->Put("weight", V2::ConvertWrapFontWeightToStirng(
            GetSelectedWeight().value_or(FontWeight::NORMAL)).c_str());
        auto selectedTextStyle = JsonUtil::Create(true);
        selectedTextStyle->Put("color", GetSelectedColor().value_or(Color::BLACK).ColorToString().c_str());
        selectedTextStyle->Put("font", selectedFont);
        json->Put("selectedTextStyle", selectedTextStyle);
        auto canLoop = GetCanLoopValue();
        json->Put("canLoop", canLoop ? "true" : "false");
    }

    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(DefaultPickerItemHeight, Dimension, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(CanLoop, bool, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(Selected, uint32_t, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(Value, std::string, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(Selecteds, std::vector<uint32_t>, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(Values, std::vector<std::string>, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(SelectedIndex, std::vector<uint32_t>, PROPERTY_UPDATE_MEASURE);
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
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP_ITEM(TextStyle, FontFamily, FontFamily, std::vector<std::string>, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP_ITEM(TextStyle, ItalicFontStyle, FontStyle, Ace::FontStyle, PROPERTY_UPDATE_MEASURE);

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
    ACE_DISALLOW_COPY_AND_MOVE(TextPickerLayoutProperty);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TEXT_PICKER_TEXT_PICKER_LAYOUT_PROPERTY_H
