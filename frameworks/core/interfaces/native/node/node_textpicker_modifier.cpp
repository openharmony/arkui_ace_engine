/*
 * Copyright (c) 2023-2024 Huawei Device Co., Ltd.
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
#include "core/interfaces/native/node/node_textpicker_modifier.h"
#include "native_type.h"

#include "bridge/common/utils/utils.h"
#include "core/components_ng/pattern/tabs/tabs_model.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "core/components_ng/pattern/text_picker/textpicker_model_ng.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t SIZE_OF_THREE = 3;
constexpr int32_t POS_0 = 0;
constexpr int32_t POS_1 = 1;
constexpr int32_t POS_2 = 2;
constexpr int NUM_3 = 3;
constexpr int32_t DEFAULT_GROUP_DIVIDER_VALUES_COUNT = 3;
const char DEFAULT_DELIMITER = '|';
const int32_t ERROR_INT_CODE = -1;
constexpr uint32_t MAX_SIZE = 12;
constexpr float MAX_PERCENT = 100.0f;
constexpr bool DEFAULT_ENABLE_HAPTIC_FEEDBACK = true;
thread_local std::string g_strValue;
const std::vector<OHOS::Ace::FontStyle> FONT_STYLES = { OHOS::Ace::FontStyle::NORMAL, OHOS::Ace::FontStyle::ITALIC };
const std::vector<TextOverflow> TEXT_OVERFLOWS = { TextOverflow::NONE, TextOverflow::CLIP, TextOverflow::ELLIPSIS,
    TextOverflow::MARQUEE };

void SetTextPickerBackgroundColor(ArkUINodeHandle node, ArkUI_Uint32 color)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextPickerModelNG::SetBackgroundColor(frameNode, Color(color));
}

void ResetTextPickerBackgroundColor(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto pipeline = frameNode->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<DialogTheme>();
    CHECK_NULL_VOID(theme);
    TextPickerModelNG::SetBackgroundColor(frameNode, theme->GetBackgroundColor());
}

ArkUI_Int32 GetTextPickerCanLoop(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, 1);
    return TextPickerModelNG::GetCanLoop(frameNode);
}

void SetTextPickerCanLoop(ArkUINodeHandle node, int canLoop)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextPickerModelNG::SetCanLoop(frameNode, canLoop);
}

void ResetTextPickerCanLoop(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto context = frameNode->GetContext();
    CHECK_NULL_VOID(context);
    auto themeManager = context->GetThemeManager();
    CHECK_NULL_VOID(themeManager);
    auto pickerTheme = themeManager->GetTheme<PickerTheme>();
    TextPickerModelNG::SetCanLoop(frameNode, true);
}

void SetTextPickerDigitalCrownSensitivity(ArkUINodeHandle node, int32_t CrownSensitivity)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextPickerModelNG::SetDigitalCrownSensitivity(frameNode, CrownSensitivity);
}

void ResetTextPickerDigitalCrownSensitivity(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextPickerModelNG::SetDigitalCrownSensitivity(frameNode, DEFAULT_CROWNSENSITIVITY);
}

void GetTextPickerSelectedIndex(ArkUINodeHandle node, ArkUI_Uint32* values, ArkUI_Int32 size)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (TextPickerModelNG::IsSingle(frameNode)) {
        auto selectedValue = static_cast<ArkUI_Uint32>(TextPickerModelNG::getTextPickerSelectedIndex(frameNode));
        values[0] = selectedValue;
    } else {
        auto selectedValue = TextPickerModelNG::getTextPickerSelecteds(frameNode);
        if (static_cast<ArkUI_Uint32>(size) != selectedValue.size()) {
            return;
        }
        for (int i = 0; i < size; i++) {
            values[i] = selectedValue[i];
        }
    }
}

void SetTextPickerSelectedIndex(ArkUINodeHandle node, ArkUI_Uint32* values, ArkUI_Int32 size)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);

    if (TextPickerModelNG::IsSingle(frameNode)) {
        NodeModifier::SetSelectedIndexSingle(frameNode, values, size);
    } else {
        NodeModifier::SetSelectedIndexMulti(frameNode, values, size);
    }
}

void ResetTextPickerSelectedIndex(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::vector<uint32_t> selectedValues;
    selectedValues.emplace_back(0);
    if (TextPickerModelNG::IsSingle(frameNode)) {
        NodeModifier::SetSelectedIndexSingle(frameNode, selectedValues.data(), selectedValues.size());
    } else {
        NodeModifier::SetSelectedIndexMulti(frameNode, selectedValues.data(), selectedValues.size());
    }
}

void SetTextPickerTextStyle(ArkUINodeHandle node, ArkUI_Uint32 color, ArkUI_CharPtr fontInfo, ArkUI_Int32 style)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto pipeline = frameNode->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto themeManager = pipeline->GetThemeManager();
    CHECK_NULL_VOID(themeManager);
    auto theme = themeManager->GetTheme<PickerTheme>();
    CHECK_NULL_VOID(theme);
 
    NG::PickerTextStyle textStyle;
    std::vector<std::string> res;
    std::string fontValues = std::string(fontInfo);
    StringUtils::StringSplitter(fontValues, DEFAULT_DELIMITER, res);
    if (res.size() != NUM_3) {
        return;
    }
    textStyle.fontSize = StringUtils::StringToCalcDimension(res[POS_0], false, DimensionUnit::FP);
    if (style >= 0 && style < static_cast<int32_t>(FONT_STYLES.size())) {
        textStyle.fontStyle = FONT_STYLES[style];
    } else {
        textStyle.fontStyle = FONT_STYLES[0];
    }
    textStyle.fontFamily = Framework::ConvertStrToFontFamilies(res[POS_2]);
    textStyle.fontWeight = StringUtils::StringToFontWeight(res[POS_1]);
    textStyle.textColor = Color(color);
    TextPickerModelNG::SetNormalTextStyle(frameNode, theme, textStyle);
}

void ResetTextPickerTextStyle(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NG::PickerTextStyle pickerTextStyle;
    auto context = frameNode->GetContext();
    CHECK_NULL_VOID(context);
    auto themeManager = context->GetThemeManager();
    CHECK_NULL_VOID(themeManager);
    auto pickerTheme = themeManager->GetTheme<PickerTheme>();
    TextPickerModelNG::SetNormalTextStyle(frameNode, pickerTheme, pickerTextStyle);
}

void SetTextPickerSelectedTextStyle(ArkUINodeHandle node, ArkUI_Uint32 color, ArkUI_CharPtr fontInfo, ArkUI_Int32 style)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto pipeline = frameNode->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto themeManager = pipeline->GetThemeManager();
    CHECK_NULL_VOID(themeManager);
    auto theme = themeManager->GetTheme<PickerTheme>();
    CHECK_NULL_VOID(theme);

    NG::PickerTextStyle textStyle;
    std::vector<std::string> res;
    std::string fontValues = std::string(fontInfo);
    StringUtils::StringSplitter(fontValues, DEFAULT_DELIMITER, res);
    if (res.size() != NUM_3) {
        return;
    }
    textStyle.fontSize = StringUtils::StringToCalcDimension(res[POS_0], false, DimensionUnit::FP);
    if (style >= 0 && style < static_cast<int32_t>(FONT_STYLES.size())) {
        textStyle.fontStyle = FONT_STYLES[style];
    } else {
        textStyle.fontStyle = FONT_STYLES[0];
    }
    textStyle.fontFamily = Framework::ConvertStrToFontFamilies(res[POS_2]);
    textStyle.fontWeight = StringUtils::StringToFontWeight(res[POS_1]);
    textStyle.textColor = Color(color);
    TextPickerModelNG::SetSelectedTextStyle(frameNode, theme, textStyle);
}

void ResetTextPickerSelectedTextStyle(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NG::PickerTextStyle pickerTextStyle;
    auto context = frameNode->GetContext();
    CHECK_NULL_VOID(context);
    auto themeManager = context->GetThemeManager();
    CHECK_NULL_VOID(themeManager);
    auto pickerTheme = themeManager->GetTheme<PickerTheme>();
    TextPickerModelNG::SetSelectedTextStyle(frameNode, pickerTheme, pickerTextStyle);
}

void SetTextPickerDisappearTextStyle(
    ArkUINodeHandle node, ArkUI_Uint32 color, ArkUI_CharPtr fontInfo, ArkUI_Int32 style)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto pipeline = frameNode->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto themeManager = pipeline->GetThemeManager();
    CHECK_NULL_VOID(themeManager);
    auto theme = themeManager->GetTheme<PickerTheme>();
    CHECK_NULL_VOID(theme);

    NG::PickerTextStyle textStyle;
    std::vector<std::string> res;
    std::string fontValues = std::string(fontInfo);
    StringUtils::StringSplitter(fontValues, DEFAULT_DELIMITER, res);
    if (res.size() != NUM_3) {
        return;
    }
    textStyle.fontSize = StringUtils::StringToCalcDimension(res[POS_0], false, DimensionUnit::FP);
    if (style >= 0 && style < static_cast<int32_t>(FONT_STYLES.size())) {
        textStyle.fontStyle = FONT_STYLES[style];
    } else {
        textStyle.fontStyle = FONT_STYLES[0];
    }
    textStyle.fontFamily = Framework::ConvertStrToFontFamilies(res[POS_2]);
    textStyle.fontWeight = StringUtils::StringToFontWeight(res[POS_1]);
    textStyle.textColor = Color(color);
    TextPickerModelNG::SetDisappearTextStyle(frameNode, theme, textStyle);
}

void ResetTextPickerDisappearTextStyle(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NG::PickerTextStyle pickerTextStyle;
    auto context = frameNode->GetContext();
    CHECK_NULL_VOID(context);
    auto themeManager = context->GetThemeManager();
    CHECK_NULL_VOID(themeManager);
    auto pickerTheme = themeManager->GetTheme<PickerTheme>();
    TextPickerModelNG::SetDisappearTextStyle(frameNode, pickerTheme, pickerTextStyle);
}

ArkUI_Float32 GetTextPickerDefaultPickerItemHeight(ArkUINodeHandle node, ArkUI_Int32 dUnit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, -1.0f);
    return TextPickerModelNG::GetDefaultPickerItemHeight(frameNode).GetNativeValue(static_cast<DimensionUnit>(dUnit));
}

void SetTextPickerDefaultPickerItemHeight(ArkUINodeHandle node, float dVal, ArkUI_Int32 dUnit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextPickerModelNG::SetDefaultPickerItemHeight(frameNode, Dimension(dVal, static_cast<DimensionUnit>(dUnit)));
}

void ResetTextPickerDefaultPickerItemHeight(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto height = Dimension(0.0);
    TextPickerModelNG::SetDefaultPickerItemHeight(frameNode, height);
}

ArkUI_CharPtr GetTextPickerRangeStr(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, "");
    g_strValue = TextPickerModelNG::getTextPickerRange(frameNode);
    return g_strValue.c_str();
}

ArkUI_Int32 GetTextPickerSingleRange(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_INT_CODE);
    return TextPickerModelNG::GetTextPickerRangeType(frameNode);
}

void SetTextCascadePickChildrenRangeContent(
    std::vector<NG::TextCascadePickerOptions>& multiResult, ArkUITextCascadePickerRangeContentArray arry)
{
    for (int index = 0; index < arry->rangeContentArraySize; index++) {
        NG::TextCascadePickerOptions option;
        if (arry[index].text == nullptr) {
            continue;
        }
        option.rangeResult.push_back(arry[index].text);

        if (arry[index].children != nullptr) {
            SetTextCascadePickChildrenRangeContent(option.children, arry[index].children);
        }
        multiResult.push_back(option);
    }
}

void SetTextCascadePickRangeContent(
    ArkUINodeHandle node, ArkUITextCascadePickerRangeContentArray arry, ArkUI_Int32 rangeType)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::vector<NG::TextCascadePickerOptions> multiResult;

    SetTextCascadePickChildrenRangeContent(multiResult, arry);
    TextPickerModelNG::SetHasSelectAttr(frameNode, true);
    TextPickerModelNG::SetIsCascade(frameNode, true);
    TextPickerModelNG::SetColumns(frameNode, multiResult);

    std::vector<std::string> values;
    for (int index = 0; index < arry->rangeContentArraySize; index++) {
        if (arry[index].text == nullptr) {
            continue;
        }
        values.emplace_back(arry[index].text);
    }
    TextPickerModelNG::SetValues(frameNode, values);
    TextPickerModelNG::SetTextPickerRangeType(frameNode, rangeType);
}

void SetTextPickerIconRangeStr(
    ArkUINodeHandle node, ArkUITextPickerRangeContentArray arry, ArkUI_Bool isSingleRange, ArkUI_Int32 rangeType)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextPickerModelNG::SetTextPickerSingeRange(static_cast<bool>(isSingleRange));
    std::vector<NG::RangeContent> result;
    for (int i = 0; i < arry->rangeContentArraySize; i++) {
        NG::RangeContent content;
        if (arry->rangeContent[i].text != nullptr) {
            content.text_ = arry->rangeContent[i].text;
        }
        if (arry->rangeContent[i].icon != nullptr) {
            content.icon_ = arry->rangeContent[i].icon;
        }
        result.emplace_back(content);
    }
    TextPickerModelNG::SetColumnKind(frameNode, MIXTURE);
    TextPickerModelNG::SetRange(frameNode, result);
    TextPickerModelNG::SetTextPickerRangeType(frameNode, rangeType);
}

void SetTextPickerRangeStr(
    ArkUINodeHandle node, ArkUI_CharPtr rangeStr, ArkUI_Bool isSingleRange, ArkUI_Int32 rangeType)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextPickerModelNG::SetTextPickerSingeRange(static_cast<bool>(isSingleRange));
    std::vector<std::string> getRangeVector;
    StringUtils::StringSplitter(std::string(rangeStr), ';', getRangeVector);
    if (isSingleRange) {
        std::vector<NG::RangeContent> result;
        for (const auto& text : getRangeVector) {
            NG::RangeContent content;
            content.icon_ = "";
            content.text_ = text;
            result.emplace_back(content);
        }
        TextPickerModelNG::SetColumnKind(frameNode, TEXT);
        TextPickerModelNG::SetRange(frameNode, result);
    } else {
        std::vector<NG::TextCascadePickerOptions> multiResult;
        for (const auto& text : getRangeVector) {
            NG::TextCascadePickerOptions option;
            StringUtils::StringSplitter(std::string(text), ',', option.rangeResult);
            multiResult.emplace_back(option);
        }
        TextPickerModelNG::SetColumns(frameNode, multiResult);
    }
    TextPickerModelNG::SetTextPickerRangeType(frameNode, rangeType);
}

ArkUI_CharPtr GetTextPickerValue(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, "");
    if (TextPickerModelNG::IsSingle(frameNode)) {
        g_strValue = TextPickerModelNG::getTextPickerValue(frameNode);
    } else {
        g_strValue = TextPickerModelNG::getTextPickerValues(frameNode);
    }
    return g_strValue.c_str();
}

void SetTextPickerValue(ArkUINodeHandle node, ArkUI_CharPtr valueStr)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::vector<std::string> getValueVector;
    StringUtils::StringSplitter(std::string(valueStr), ';', getValueVector);
    if (TextPickerModelNG::GetTextPickerSingeRange()) {
        TextPickerModelNG::SetValue(frameNode, valueStr);
    } else {
        TextPickerModelNG::SetValues(frameNode, getValueVector);
    }
}

void SetTextPickerColumnWidths(ArkUINodeHandle node, ArkUI_Float32* values, ArkUI_Int32 size)
{
    std::vector<Dimension> widths;
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    for (ArkUI_Int32 i = 0; i < size; i++) {
        widths.emplace_back(Dimension(values[i] * MAX_PERCENT, DimensionUnit::PERCENT));
    }
    TextPickerModelNG::SetColumnWidths(frameNode, widths);
}

void ResetTextPickerColumnWidths(ArkUINodeHandle node)
{
    std::vector<Dimension> widths;
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto childCount =  frameNode->GetChildren().size();
    for (size_t i = 0; i < childCount; i++) {
        widths.emplace_back(Dimension(MAX_PERCENT / static_cast<float>(childCount), DimensionUnit::PERCENT));
    }
    TextPickerModelNG::SetColumnWidths(frameNode, widths);
}

ArkUI_Int32 GetTextPickerColumnWidthsSize(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, 0);
    return TextPickerModelNG::GetColumnWidthsSize(frameNode);
}

void GetTextPickerColumnWidths(ArkUINodeHandle node, ArkUI_Float32* values)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto size = GetTextPickerColumnWidthsSize(node);
    std::vector<Dimension> widths = TextPickerModelNG::GetColumnWidths(frameNode);
    for (int32_t i = 0; i < size; i++) {
        values[i] = widths[i].Value() / MAX_PERCENT;
    }
}

ArkUI_CharPtr GetTextPickerSelectedTextStyle(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, "");
    PickerTextStyle pickerTextStyle = TextPickerModelNG::getSelectedTextStyle(frameNode);
    std::vector<std::string> fontFamilies = pickerTextStyle.fontFamily.value_or(std::vector<std::string>());
    std::string families;
    if (fontFamilies.size() == 0) {
        fontFamilies.emplace_back("HarmonyOS Sans");
    }
    //set index start
    int index = 0;
    for (auto& family : fontFamilies) {
        families += family;
        if (index != static_cast<int>(fontFamilies.size()) - 1) {
            families += ",";
        }
        index++;
    }
    g_strValue = pickerTextStyle.textColor->ColorToString() + ";";
    g_strValue = g_strValue + std::to_string(static_cast<int>(pickerTextStyle.fontSize->ConvertToFp())) + ";";
    g_strValue = g_strValue + StringUtils::ToString(pickerTextStyle.fontWeight.value_or(FontWeight::W100)) + ";";
    g_strValue = g_strValue + families + ";";
    g_strValue =
        g_strValue + StringUtils::ToStringNDK(pickerTextStyle.fontStyle.value_or(OHOS::Ace::FontStyle::NORMAL));
    return g_strValue.c_str();
}

ArkUI_CharPtr GetTextPickerTextStyle(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, "");
    PickerTextStyle pickerTextStyle = TextPickerModelNG::getNormalTextStyle(frameNode);
    std::vector<std::string> fontFamilies = pickerTextStyle.fontFamily.value_or(std::vector<std::string>());
    std::string families;
    if (fontFamilies.size() == 0) {
        fontFamilies.emplace_back("HarmonyOS Sans");
    }
    //set index start
    int index = 0;
    for (auto& family : fontFamilies) {
        families += family;
        if (index != static_cast<int>(fontFamilies.size()) - 1) {
            families += ",";
        }
        index++;
    }
    g_strValue = pickerTextStyle.textColor->ColorToString() + ";";
    g_strValue = g_strValue + std::to_string(static_cast<int>(pickerTextStyle.fontSize->ConvertToFp())) + ";";
    g_strValue = g_strValue + StringUtils::ToString(pickerTextStyle.fontWeight.value_or(FontWeight::W100)) + ";";
    g_strValue = g_strValue + families + ";";
    g_strValue =
        g_strValue + StringUtils::ToStringNDK(pickerTextStyle.fontStyle.value_or(OHOS::Ace::FontStyle::NORMAL));
    return g_strValue.c_str();
}

ArkUI_CharPtr GetTextPickerDisappearTextStyle(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, "");
    PickerTextStyle pickerTextStyle = TextPickerModelNG::getDisappearTextStyle(frameNode);
    std::vector<std::string> fontFamilies = pickerTextStyle.fontFamily.value_or(std::vector<std::string>());
    std::string families;
    if (fontFamilies.size() == 0) {
        fontFamilies.emplace_back("HarmonyOS Sans");
    }
    //set index start
    int index = 0;
    for (auto& family : fontFamilies) {
        families += family;
        if (index != static_cast<int>(fontFamilies.size()) - 1) {
            families += ",";
        }
        index++;
    }
    g_strValue = pickerTextStyle.textColor->ColorToString() + ";";
    g_strValue = g_strValue + std::to_string(static_cast<int>(pickerTextStyle.fontSize->ConvertToFp())) + ";";
    g_strValue = g_strValue + StringUtils::ToString(pickerTextStyle.fontWeight.value_or(FontWeight::W100)) + ";";
    g_strValue = g_strValue + families + ";";
    g_strValue =
        g_strValue + StringUtils::ToStringNDK(pickerTextStyle.fontStyle.value_or(OHOS::Ace::FontStyle::NORMAL));
    return g_strValue.c_str();
}

void SetTextPickerDivider(
    ArkUINodeHandle node, ArkUI_Uint32 color, const ArkUI_Float32* values, const ArkUI_Int32* units, ArkUI_Int32 length)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);

    if (length != DEFAULT_GROUP_DIVIDER_VALUES_COUNT) {
        return;
    }

    NG::ItemDivider divider;
    divider.color = Color(color);
    divider.strokeWidth = Dimension(values[POS_0], static_cast<OHOS::Ace::DimensionUnit>(units[POS_0]));
    divider.startMargin = Dimension(values[POS_1], static_cast<OHOS::Ace::DimensionUnit>(units[POS_1]));
    divider.endMargin = Dimension(values[POS_2], static_cast<OHOS::Ace::DimensionUnit>(units[POS_2]));

    TextPickerModelNG::SetDivider(frameNode, divider);
}

void ResetTextPickerDivider(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto context = frameNode->GetContext();
    CHECK_NULL_VOID(context);
    auto themeManager = context->GetThemeManager();
    CHECK_NULL_VOID(themeManager);
    auto pickerTheme = themeManager->GetTheme<PickerTheme>();
    NG::ItemDivider divider;
    Dimension defaultStrokeWidth = 0.0_vp;
    Color defaultColor = Color::TRANSPARENT;
    if (pickerTheme) {
        defaultStrokeWidth = pickerTheme->GetDividerThickness();
        defaultColor = pickerTheme->GetDividerColor();
        divider.strokeWidth = defaultStrokeWidth;
        divider.color = defaultColor;
    }
    TextPickerModelNG::SetDivider(frameNode, divider);
}

void ResetTextPickerDividerNull(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NG::ItemDivider divider;
    TextPickerModelNG::SetDivider(frameNode, divider);
}

void SetTextPickerGradientHeight(ArkUINodeHandle node, ArkUI_Float32 dVal, ArkUI_Int32 dUnit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextPickerModelNG::SetGradientHeight(frameNode, Dimension(dVal, static_cast<DimensionUnit>(dUnit)));
}

void ResetTextPickerGradientHeight(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);

    auto pipeline = frameNode->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto themeManager = pipeline->GetThemeManager();
    CHECK_NULL_VOID(themeManager);
    auto pickerTheme = themeManager->GetTheme<PickerTheme>();
    CHECK_NULL_VOID(pickerTheme);

    CalcDimension height;
    if (pickerTheme) {
        height = pickerTheme->GetGradientHeight();
    } else {
        height = 0.0_vp;
    }

    TextPickerModelNG::SetGradientHeight(frameNode, height);
}

void SetTextPickerDisableTextStyleAnimation(ArkUINodeHandle node, int disableTextStyleAnimation)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextPickerModelNG::SetDisableTextStyleAnimation(frameNode, disableTextStyleAnimation);
}

void ResetTextPickerDisableTextStyleAnimation(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextPickerModelNG::SetDisableTextStyleAnimation(frameNode, false);
}

void SetTextPickerDefaultTextStyle(ArkUINodeHandle node, ArkUI_Uint32 color, ArkUI_CharPtr fontInfo, ArkUI_Int32 style,
    ArkUI_CharPtr minFontSize, ArkUI_CharPtr maxFontSize, ArkUI_Int32 overflow)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto pipeline = frameNode->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto themeManager = pipeline->GetThemeManager();
    CHECK_NULL_VOID(themeManager);
    auto theme = themeManager->GetTheme<TextTheme>();
    CHECK_NULL_VOID(theme);
 
    NG::PickerTextStyle textStyle;
    std::vector<std::string> res;
    std::string fontValues = std::string(fontInfo);
    StringUtils::StringSplitter(fontValues, DEFAULT_DELIMITER, res);
    if (res.size() != NUM_3) {
        return;
    }
    textStyle.fontSize = StringUtils::StringToCalcDimension(res[POS_0], false, DimensionUnit::FP);
    if (style >= 0 && style < static_cast<int32_t>(FONT_STYLES.size())) {
        textStyle.fontStyle = FONT_STYLES[style];
    } else {
        textStyle.fontStyle = FONT_STYLES[0];
    }
    textStyle.fontFamily = Framework::ConvertStrToFontFamilies(res[POS_2]);
    textStyle.fontWeight = StringUtils::StringToFontWeight(res[POS_1]);
    textStyle.textColor = Color(color);
    textStyle.minFontSize = StringUtils::StringToCalcDimension(minFontSize, false, DimensionUnit::FP);
    textStyle.maxFontSize = StringUtils::StringToCalcDimension(maxFontSize, false, DimensionUnit::FP);
    if (overflow >= 0 && overflow < static_cast<int32_t>(TEXT_OVERFLOWS.size())) {
        textStyle.textOverflow = TEXT_OVERFLOWS[overflow];
    } else {
        textStyle.textOverflow = TEXT_OVERFLOWS[0];
    }

    TextPickerModelNG::SetDefaultTextStyle(frameNode, theme, textStyle);
}

void ResetTextPickerDefaultTextStyle(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto pipeline = frameNode->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto themeManager = pipeline->GetThemeManager();
    CHECK_NULL_VOID(themeManager);
    auto theme = themeManager->GetTheme<TextTheme>();
    CHECK_NULL_VOID(theme);
    NG::PickerTextStyle pickerTextStyle;
    TextPickerModelNG::SetDefaultTextStyle(frameNode, theme, pickerTextStyle);
}

ArkUI_Int32 GetTextPickerSelectedSize(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, 0);
    if (TextPickerModelNG::IsSingle(frameNode)) {
        return 1;
    }
    return TextPickerModelNG::GetSelectedSize(frameNode);
}
void SetTextPickerOnChangeExt(ArkUINodeHandle node, void* callback)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto onChange =
        reinterpret_cast<std::function<void(const std::vector<std::string>&, const std::vector<double>&)>*>(callback);
    TextPickerModelNG::SetOnCascadeChange(frameNode, std::move(*onChange));
}
void ResetTextPickerOnChange(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextPickerModelNG::SetOnCascadeChange(frameNode, nullptr);
}
void SetTextPickerOnScrollStopExt(ArkUINodeHandle node, void* callback)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto onChange =
        reinterpret_cast<std::function<void(const std::vector<std::string>&, const std::vector<double>&)>*>(callback);
    TextPickerModelNG::SetOnScrollStop(frameNode, std::move(*onChange));
}
void ResetTextPickerOnScrollStop(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextPickerModelNG::SetOnScrollStop(frameNode, nullptr);
}
} // namespace

namespace NodeModifier {
const ArkUITextPickerModifier* GetTextPickerModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const ArkUITextPickerModifier modifier = {
        .setTextPickerBackgroundColor = SetTextPickerBackgroundColor,
        .setTextPickerCanLoop = SetTextPickerCanLoop,
        .getTextPickerSelectedIndex = GetTextPickerSelectedIndex,
        .setTextPickerSelectedIndex = SetTextPickerSelectedIndex,
        .getTextPickerTextStyle = GetTextPickerTextStyle,
        .setTextPickerTextStyle = SetTextPickerTextStyle,
        .getTextPickerSelectedTextStyle = GetTextPickerSelectedTextStyle,
        .setTextPickerSelectedTextStyle = SetTextPickerSelectedTextStyle,
        .getTextPickerDisappearTextStyle = GetTextPickerDisappearTextStyle,
        .setTextPickerDisappearTextStyle = SetTextPickerDisappearTextStyle,
        .setTextPickerDefaultPickerItemHeight = SetTextPickerDefaultPickerItemHeight,
        .resetTextPickerCanLoop = ResetTextPickerCanLoop,
        .resetTextPickerSelectedIndex = ResetTextPickerSelectedIndex,
        .resetTextPickerTextStyle = ResetTextPickerTextStyle,
        .resetTextPickerSelectedTextStyle = ResetTextPickerSelectedTextStyle,
        .resetTextPickerDisappearTextStyle = ResetTextPickerDisappearTextStyle,
        .resetTextPickerDefaultPickerItemHeight = ResetTextPickerDefaultPickerItemHeight,
        .resetTextPickerBackgroundColor = ResetTextPickerBackgroundColor,
        .getTextPickerRangeStr = GetTextPickerRangeStr,
        .getTextPickerSingleRange = GetTextPickerSingleRange,
        .setTextPickerRangeStr = SetTextPickerRangeStr,
        .getTextPickerValue = GetTextPickerValue,
        .setTextPickerValue = SetTextPickerValue,
        .setTextPickerColumnWidths = SetTextPickerColumnWidths,
        .resetTextPickerColumnWidths = ResetTextPickerColumnWidths,
        .getTextPickerColumnWidths = GetTextPickerColumnWidths,
        .getTextPickerColumnWidthsSize = GetTextPickerColumnWidthsSize,
        .setTextPickerDivider = SetTextPickerDivider,
        .resetTextPickerDivider = ResetTextPickerDivider,
        .setTextPickerGradientHeight = SetTextPickerGradientHeight,
        .resetTextPickerGradientHeight = ResetTextPickerGradientHeight,
        .getTextPickerSelectedSize = GetTextPickerSelectedSize,
        .getTextPickerCanLoop = GetTextPickerCanLoop,
        .getTextPickerDefaultPickerItemHeight = GetTextPickerDefaultPickerItemHeight,
        .resetTextPickerDividerNull = ResetTextPickerDividerNull,
        .setTextPickerDisableTextStyleAnimation = SetTextPickerDisableTextStyleAnimation,
        .resetTextPickerDisableTextStyleAnimation = ResetTextPickerDisableTextStyleAnimation,
        .setTextPickerDefaultTextStyle = SetTextPickerDefaultTextStyle,
        .resetTextPickerDefaultTextStyle = ResetTextPickerDefaultTextStyle,
        .getTextPickerEnableHapticFeedback = GetTextPickerEnableHapticFeedback,
        .setTextPickerEnableHapticFeedback = SetTextPickerEnableHapticFeedback,
        .resetTextPickerEnableHapticFeedback = ResetTextPickerEnableHapticFeedback,
        .setTextPickerDigitalCrownSensitivity = SetTextPickerDigitalCrownSensitivity,
        .resetTextPickerDigitalCrownSensitivity = ResetTextPickerDigitalCrownSensitivity,
        .setTextPickerOnChange = SetTextPickerOnChangeExt,
        .resetTextPickerOnChange = ResetTextPickerOnChange,
        .setTextPickerOnScrollStop = SetTextPickerOnScrollStopExt,
        .resetTextPickerOnScrollStop = ResetTextPickerOnScrollStop,
        .setTextPickerIconRangeStr = SetTextPickerIconRangeStr,
        .setTextCascadePickRangeContent = SetTextCascadePickRangeContent,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line

    return &modifier;
}

const CJUITextPickerModifier* GetCJUITextPickerModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const CJUITextPickerModifier modifier = {
        .setTextPickerBackgroundColor = SetTextPickerBackgroundColor,
        .setTextPickerCanLoop = SetTextPickerCanLoop,
        .getTextPickerSelectedIndex = GetTextPickerSelectedIndex,
        .setTextPickerSelectedIndex = SetTextPickerSelectedIndex,
        .getTextPickerTextStyle = GetTextPickerTextStyle,
        .setTextPickerTextStyle = SetTextPickerTextStyle,
        .getTextPickerSelectedTextStyle = GetTextPickerSelectedTextStyle,
        .setTextPickerSelectedTextStyle = SetTextPickerSelectedTextStyle,
        .getTextPickerDisappearTextStyle = GetTextPickerDisappearTextStyle,
        .setTextPickerDisappearTextStyle = SetTextPickerDisappearTextStyle,
        .setTextPickerDefaultPickerItemHeight = SetTextPickerDefaultPickerItemHeight,
        .resetTextPickerCanLoop = ResetTextPickerCanLoop,
        .resetTextPickerSelectedIndex = ResetTextPickerSelectedIndex,
        .resetTextPickerTextStyle = ResetTextPickerTextStyle,
        .resetTextPickerSelectedTextStyle = ResetTextPickerSelectedTextStyle,
        .resetTextPickerDisappearTextStyle = ResetTextPickerDisappearTextStyle,
        .resetTextPickerDefaultPickerItemHeight = ResetTextPickerDefaultPickerItemHeight,
        .resetTextPickerBackgroundColor = ResetTextPickerBackgroundColor,
        .getTextPickerRangeStr = GetTextPickerRangeStr,
        .getTextPickerSingleRange = GetTextPickerSingleRange,
        .setTextPickerRangeStr = SetTextPickerRangeStr,
        .getTextPickerValue = GetTextPickerValue,
        .setTextPickerValue = SetTextPickerValue,
        .setTextPickerDivider = SetTextPickerDivider,
        .resetTextPickerDivider = ResetTextPickerDivider,
        .setTextPickerGradientHeight = SetTextPickerGradientHeight,
        .resetTextPickerGradientHeight = ResetTextPickerGradientHeight,
        .getTextPickerSelectedSize = GetTextPickerSelectedSize,
        .getTextPickerCanLoop = GetTextPickerCanLoop,
        .getTextPickerDefaultPickerItemHeight = GetTextPickerDefaultPickerItemHeight,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line

    return &modifier;
}

void GetPickerTextStyle(uint32_t color, ArkUI_CharPtr fontInfo, int32_t styleVal, NG::PickerTextStyle& textStyle)
{
    textStyle.textColor = Color(color);

    std::vector<std::string> res;
    std::string fontValues = std::string(fontInfo);
    StringUtils::StringSplitter(fontValues, DEFAULT_DELIMITER, res);

    if (res.size() != SIZE_OF_THREE) {
        return;
    }

    if (res[POS_0] != "-1") {
        textStyle.fontSize = StringUtils::StringToCalcDimension(res[POS_0], false, DimensionUnit::FP);
    } else {
        textStyle.fontSize = Dimension(-1);
    }

    if (res[POS_1] != "-1") {
        textStyle.fontWeight = StringUtils::StringToFontWeight(res[POS_1], FontWeight::NORMAL);
    }

    if (res[POS_2] != "-1") {
        textStyle.fontFamily = Framework::ConvertStrToFontFamilies(res[POS_2]);
    }
    textStyle.fontStyle = static_cast<Ace::FontStyle>(styleVal);
}

void SetSelectedIndexSingle(FrameNode* frameNode, uint32_t* selectedValues, const int32_t size)
{
    std::vector<NG::RangeContent> rangeResult;
    TextPickerModelNG::GetSingleRange(frameNode, rangeResult);
    if (selectedValues[0] >= rangeResult.size()) {
        TextPickerModelNG::SetSelected(frameNode, 0);
    } else {
        TextPickerModelNG::SetSelected(frameNode, selectedValues[0]);
    }
}

void SetSelectedIndexMultiInternal(FrameNode* frameNode, uint32_t count,
    std::vector<NG::TextCascadePickerOptions>& options, std::vector<uint32_t>& selectedValues)
{
    if (!TextPickerModelNG::IsCascade(frameNode)) {
        NodeModifier::SetSelectedInternal(count, options, selectedValues);
    } else {
        TextPickerModelNG::SetHasSelectAttr(frameNode, true);
        NodeModifier::ProcessCascadeSelected(options, 0, selectedValues);
        uint32_t maxCount = TextPickerModelNG::GetMaxCount(frameNode);
        if (selectedValues.size() < maxCount) {
            auto differ = maxCount - selectedValues.size();
            for (uint32_t i = 0; i < differ; i++) {
                selectedValues.emplace_back(0);
            }
        }
    }
}

void SetSelectedIndexSingleInternal(const std::vector<NG::TextCascadePickerOptions>& options, uint32_t count,
    uint32_t& selectedValue, std::vector<uint32_t>& selectedValues)
{
    if (options.size() > 0) {
        if (selectedValue >= options[0].rangeResult.size()) {
            selectedValue = 0;
        }
        selectedValues.emplace_back(selectedValue);
        for (uint32_t i = 1; i < count; i++) {
            selectedValues.emplace_back(0);
        }
    } else {
        for (uint32_t i = 0; i < count; i++) {
            selectedValues.emplace_back(0);
        }
    }
}

void SetSelectedInternal(
    uint32_t count, std::vector<NG::TextCascadePickerOptions>& options, std::vector<uint32_t>& selectedValues)
{
    for (uint32_t i = 0; i < count; i++) {
        uint32_t val = selectedValues.size() > 0 ? selectedValues.size() - 1 : 0;
        if (i > val) {
            selectedValues.emplace_back(0);
        } else {
            if (selectedValues[i] >= options[i].rangeResult.size()) {
                selectedValues[i] = 0;
            }
        }
    }
}

void SetSelectedIndexMulti(FrameNode* frameNode, uint32_t* inputs, const int32_t size)
{
    std::vector<NG::TextCascadePickerOptions> options;
    TextPickerModelNG::GetMultiOptions(frameNode, options);

    auto count = TextPickerModelNG::IsCascade(frameNode) ? TextPickerModelNG::GetMaxCount(frameNode) : options.size();
    std::vector<uint32_t> selectedValues;

    if (size >= 0) {
        selectedValues.assign(inputs, inputs + size);
        SetSelectedIndexMultiInternal(frameNode, count, options, selectedValues);
    } else {
        TextPickerModelNG::SetHasSelectAttr(frameNode, true);
        SetSelectedIndexSingleInternal(options, count, inputs[0], selectedValues);
    }
    TextPickerModelNG::SetSelecteds(frameNode, selectedValues);
}

void ProcessCascadeSelected(
    const std::vector<NG::TextCascadePickerOptions>& options, uint32_t index, std::vector<uint32_t>& selectedValues)
{
    const size_t size = options.size();
    if (size == 0) {
        return;
    }
    std::vector<std::string> rangeResultValue;
    for (size_t i = 0; i < size; i++) {
        rangeResultValue.emplace_back(options[i].rangeResult[0]);
    }
    uint32_t val = selectedValues.size() > 0 ? selectedValues.size() - 1 : 0;
    if (index > val) {
        selectedValues.emplace_back(0);
    }
    if (selectedValues[index] >= rangeResultValue.size()) {
        selectedValues[index] = 0;
    }
    if ((selectedValues[index] <= size - 1) && (options[selectedValues[index]].children.size() > 0)) {
        ProcessCascadeSelected(options[selectedValues[index]].children, index + 1, selectedValues);
    }
}

void SetTextPickerOnChange(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto onChangeEvent = [node, extraParam](
                             const std::vector<std::string>& value, const std::vector<double>& indexVector) {
        ArkUINodeEvent event;
        event.kind = COMPONENT_ASYNC_EVENT;
        event.extraParam = reinterpret_cast<intptr_t>(extraParam);
        event.componentAsyncEvent.subKind = ON_TEXT_PICKER_CHANGE;
        for (size_t i = 0; i < indexVector.size() && i < MAX_SIZE; i++) {
            event.componentAsyncEvent.data[i].i32 = static_cast<int32_t>(indexVector[i]);
        }
        SendArkUISyncEvent(&event);
    };
    TextPickerModelNG::SetOnCascadeChange(frameNode, std::move(onChangeEvent));
}

void SetTextPickerOnScrollStop(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto onScrollStopEvent = [node, extraParam](
                             const std::vector<std::string>& value, const std::vector<double>& indexVector) {
        ArkUINodeEvent event;
        event.kind = COMPONENT_ASYNC_EVENT;
        event.extraParam = reinterpret_cast<intptr_t>(extraParam);
        event.componentAsyncEvent.subKind = ON_TEXT_PICKER_SCROLL_STOP;
        for (size_t i = 0; i < indexVector.size() && i < MAX_SIZE; i++) {
            event.componentAsyncEvent.data[i].i32 = static_cast<int32_t>(indexVector[i]);
        }
        SendArkUISyncEvent(&event);
    };
    TextPickerModelNG::SetOnScrollStop(frameNode, std::move(onScrollStopEvent));
}

void SetTextPickerEnableHapticFeedback(ArkUINodeHandle node, ArkUI_Bool isEnableHapticFeedback)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextPickerModelNG::SetEnableHapticFeedback(frameNode, isEnableHapticFeedback);
}

void ResetTextPickerEnableHapticFeedback(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextPickerModelNG::SetEnableHapticFeedback(frameNode, DEFAULT_ENABLE_HAPTIC_FEEDBACK);
}

ArkUI_Bool GetTextPickerEnableHapticFeedback(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_INT_CODE);
    return static_cast<ArkUI_Bool>(TextPickerModelNG::GetEnableHapticFeedback(frameNode));
}
} // namespace NodeModifier
} // namespace OHOS::Ace::NG
