/*
 * Copyright (c) 2022-2024 Huawei Device Co., Ltd.
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
#include "core/components_ng/base/inspector_filter.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_property.h"
#include "core/components_ng/pattern/text/text_styles.h"
#include "core/components_ng/pattern/text_picker/textpicker_layout_property.h"
#include "core/components_ng/pattern/text_picker/textpicker_properties.h"
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
        value->propGradientHeight_ = CloneGradientHeight();
        value->propSelected_ = CloneSelected();
        value->propValue_ = CloneValue();
        value->propSelecteds_ = CloneSelecteds();
        value->propValues_ = CloneValues();
        value->propSelectedIndex_ = CloneSelectedIndex();
        value->propDisappearTextStyle_ = CloneDisappearTextStyle();
        value->propTextStyle_ = CloneTextStyle();
        value->propSelectedTextStyle_ = CloneSelectedTextStyle();
        value->propCanLoop_ = CloneCanLoop();
        value->propDivider_ = CloneDivider();
        value->propDisableTextStyleAnimation_ = CloneDisableTextStyleAnimation();
        value->propDefaultTextStyle_ = CloneDefaultTextStyle();
        value->propDefaultTextOverflow_ = CloneDefaultTextOverflow();
        value->propDigitalCrownSensitivity_ = CloneDigitalCrownSensitivity();
        return value;
    }

    void Reset() override
    {
        LinearLayoutProperty::Reset();
        ResetDefaultPickerItemHeight();
        ResetGradientHeight();
        ResetSelected();
        ResetValue();
        ResetSelecteds();
        ResetValues();
        ResetSelectedIndex();
        ResetDisappearTextStyle();
        ResetTextStyle();
        ResetSelectedTextStyle();
        ResetCanLoop();
        ResetDivider();
        ResetDisableTextStyleAnimation();
        ResetDefaultTextStyle();
        ResetDefaultTextOverflow();
        ResetDigitalCrownSensitivity();
    }

    void ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const override
    {
        LayoutProperty::ToJsonValue(json, filter);
        /* no fixed attr below, just return */
        if (filter.IsFastFilter()) {
            return;
        }
        json->PutExtAttr("defaultPickerItemHeight",
            GetDefaultPickerItemHeightValue(Dimension(0)).ToString().c_str(), filter);
        json->PutExtAttr("gradientHeight", GetGradientHeightValue(Dimension(0)).ToString().c_str(), filter);
        json->PutExtAttr("selected", std::to_string(GetSelectedValue(0)).c_str(), filter);
        json->PutExtAttr("value", GetValueValue("").c_str(), filter);
        Color defaultDisappearColor = Color::BLACK;
        Color defaultNormalColor = Color::BLACK;
        Color defaultSelectColor = Color::BLACK;
        Color defaultSelectedBgColor = Color(0x0C182431);
        Dimension defaultSelectedBorderRadius = 24.0_vp;
        auto pipeline = PipelineBase::GetCurrentContext();
        auto frameNode = GetHost();
        if (pipeline && frameNode) {
            auto pickerTheme = pipeline->GetTheme<PickerTheme>(frameNode->GetThemeScopeId());
            if (pickerTheme) {
                defaultDisappearColor = pickerTheme->GetDisappearOptionStyle().GetTextColor();
                defaultNormalColor = pickerTheme->GetOptionStyle(false, false).GetTextColor();
                defaultSelectColor = pickerTheme->GetOptionStyle(true, false).GetTextColor();
                defaultSelectedBgColor = pickerTheme->GetSelectedBackgroundColor();
                defaultSelectedBorderRadius = *pickerTheme->GetSelectedBorderRadius().radiusTopLeft;
            }
        }
        if (propDivider_.has_value()) {
            auto divider = JsonUtil::Create(true);
            divider->Put("strokeWidth", propDivider_.value().strokeWidth.ToString().c_str());
            divider->Put("startMargin", propDivider_.value().startMargin.ToString().c_str());
            divider->Put("endMargin", propDivider_.value().endMargin.ToString().c_str());
            divider->Put("color", propDivider_.value().color.ColorToString().c_str());
            json->PutExtAttr("divider", divider, filter);
        } else {
            auto divider = JsonUtil::Create(true);
            json->PutExtAttr("divider", divider, filter);
        }

        auto jsonArraySelected = JsonUtil::CreateArray(true);
        auto arraySelected = CloneSelecteds().value_or(std::vector<uint32_t>());
        for (uint32_t i = 0; i < arraySelected.size(); i++) {
            auto index = std::to_string(i);
            jsonArraySelected->Put(index.c_str(), std::to_string(arraySelected[i]).c_str());
        }
        json->PutExtAttr("selecteds", jsonArraySelected, filter);

        auto jsonArraySelectedIndex = JsonUtil::CreateArray(true);
        auto arraySelectedIndex = CloneSelecteds().value_or(std::vector<uint32_t>());
        for (uint32_t i = 0; i < arraySelectedIndex.size(); i++) {
            auto index = std::to_string(i);
            jsonArraySelectedIndex->Put(index.c_str(), std::to_string(arraySelectedIndex[i]).c_str());
        }
        json->PutExtAttr("selectedIndex", jsonArraySelectedIndex, filter);

        auto jsonArrayValue = JsonUtil::CreateArray(true);
        auto arrayValue = CloneValues().value_or(std::vector<std::string>());
        for (uint32_t i = 0; i < arrayValue.size(); i++) {
            auto index = std::to_string(i);
            jsonArrayValue->Put(index.c_str(), arrayValue[i].c_str());
        }
        json->PutExtAttr("values", jsonArrayValue, filter);

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
        auto canLoop = GetCanLoopValue();
        json->PutExtAttr("canLoop", canLoop ? "true" : "false", filter);

        auto isDisableTextStyleAnimation = GetDisableTextStyleAnimation().value_or(false);
        json->PutExtAttr("disableTextStyleAnimation", isDisableTextStyleAnimation ? "true" : "false", filter);

        auto defaultFont = JsonUtil::Create(true);
        defaultFont->Put("size", GetDefaultFontSizeValue(Dimension(0)).ToString().c_str());
        defaultFont->Put("weight", V2::ConvertWrapFontWeightToStirng(
            GetDefaultWeight().value_or(FontWeight::NORMAL)).c_str());
        auto defaultTextStyle = JsonUtil::Create(true);
        defaultTextStyle->Put("color", GetDefaultColor().value_or(Color::BLACK).ColorToString().c_str());
        defaultTextStyle->Put("minFontSize", GetDefaultMinFontSize().value_or(Dimension()).ToString().c_str());
        defaultTextStyle->Put("maxFontSize", GetDefaultMaxFontSize().value_or(Dimension()).ToString().c_str());
        defaultTextStyle->Put("overflow",
            V2::ConvertWrapTextOverflowToString(GetDefaultTextOverflow().value_or(TextOverflow::CLIP)).c_str());
        defaultTextStyle->Put("font", defaultFont);
        json->PutExtAttr("defaultTextStyle", defaultTextStyle, filter);
        auto crownSensitivity = GetDigitalCrownSensitivity();
        json->PutExtAttr("digitalCrownSensitivity",
            std::to_string(crownSensitivity.value_or(DEFAULT_CROWNSENSITIVITY)).c_str(), filter);
        auto selectedBackgroundStyle = JsonUtil::Create(true);
        selectedBackgroundStyle->Put("color", GetSelectedBackgroundColor().value_or(
            defaultSelectedBgColor).ColorToString().c_str());
        selectedBackgroundStyle->Put("borderRadius", GetSelectedBorderRadius().value_or(
        NG::BorderRadiusProperty(defaultSelectedBorderRadius)).ToString().c_str());
        json->PutExtAttr("selectedBackgroundStyle", selectedBackgroundStyle, filter);
    }

    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(DefaultPickerItemHeight, Dimension, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(GradientHeight, Dimension, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(CanLoop, bool, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(DigitalCrownSensitivity, int32_t, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(Selected, uint32_t, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(Value, std::string, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(Selecteds, std::vector<uint32_t>, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(Values, std::vector<std::string>, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(SelectedIndex, std::vector<uint32_t>, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(Divider, ItemDivider, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(DisableTextStyleAnimation, bool, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(SelectedBackgroundColor, Color, PROPERTY_UPDATE_MEASURE_SELF);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(SelectedBorderRadius, NG::BorderRadiusProperty, PROPERTY_UPDATE_MEASURE);

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

    ACE_DEFINE_PROPERTY_GROUP(DefaultTextStyle, FontStyle);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP_ITEM(
        DefaultTextStyle, FontSize, DefaultFontSize, Dimension, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP_ITEM(
        DefaultTextStyle, TextColor, DefaultColor, Color, PROPERTY_UPDATE_MEASURE_SELF);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP_ITEM(
        DefaultTextStyle, FontWeight, DefaultWeight, FontWeight, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP_ITEM(
        DefaultTextStyle, FontFamily, DefaultFontFamily, std::vector<std::string>, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP_ITEM(
        DefaultTextStyle, ItalicFontStyle, DefaultFontStyle, Ace::FontStyle, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP_ITEM(
        DefaultTextStyle, AdaptMinFontSize, DefaultMinFontSize, Dimension, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP_ITEM(
        DefaultTextStyle, AdaptMaxFontSize, DefaultMaxFontSize, Dimension, PROPERTY_UPDATE_MEASURE);

    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(DefaultTextOverflow, TextOverflow, PROPERTY_UPDATE_MEASURE);
private:
    ACE_DISALLOW_COPY_AND_MOVE(TextPickerLayoutProperty);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TEXT_PICKER_TEXT_PICKER_LAYOUT_PROPERTY_H
