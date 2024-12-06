/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include "core/interfaces/native/node/node_text_area_modifier.h"

#include "bridge/common/utils/utils.h"
#include "base/utils/utf_helper.h"
#include "core/components/text_field/textfield_theme.h"
#include "core/components_ng/pattern/text_field/text_field_model_ng.h"
#include "core/components/common/properties/text_style_parser.h"
#include "interfaces/native/node/node_model.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int NUM_0 = 0;
constexpr int NUM_1 = 1;
constexpr int NUM_2 = 2;
constexpr int NUM_3 = 3;
constexpr int NUM_4 = 4;
constexpr int NUM_16 = 16;
constexpr int NUM_24 = 24;
constexpr int DEFAULT_LENGTH = 4;
constexpr InputStyle DEFAULT_TEXT_AREA_STYLE = InputStyle::DEFAULT;
constexpr bool DEFAULT_SELECTION_MENU_HIDDEN = false;
constexpr uint32_t DEFAULT_MAX_VIEW_LINE = 3;
constexpr CopyOptions DEFAULT_COPY_OPTIONS_VALUE = CopyOptions::Local;
constexpr FontWeight DEFAULT_FONT_WEIGHT = FontWeight::NORMAL;
constexpr Ace::FontStyle DEFAULT_FONT_STYLE = Ace::FontStyle::NORMAL;
constexpr DisplayMode DEFAULT_BAR_STATE_VALUE = DisplayMode::AUTO;
constexpr bool DEFAULT_KEY_BOARD_VALUE = true;
constexpr bool DEFAULT_ENABLE_AUTO_FILL = true;
constexpr char DEFAULT_FONT_FAMILY[] = "HarmonyOS Sans";
const uint32_t ERROR_UINT_CODE = -1;
const int32_t ERROR_INT_CODE = -1;
constexpr TextDecoration DEFAULT_TEXT_DECORATION = TextDecoration::NONE;
constexpr Color DEFAULT_DECORATION_COLOR = Color(0xff000000);
constexpr TextDecorationStyle DEFAULT_DECORATION_STYLE = TextDecorationStyle::SOLID;
constexpr int16_t DEFAULT_ALPHA = 255;
constexpr double DEFAULT_OPACITY = 0.2;
const float ERROR_FLOAT_CODE = -1.0f;
std::string g_strValue;
constexpr bool DEFAULT_ENABLE_PREVIEW_TEXT_VALUE = true;
constexpr bool DEFAULT_ENABLE_HAPTIC_FEEDBACK_VALUE = true;

void SetTextAreaStyle(ArkUINodeHandle node, ArkUI_Int32 style)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::SetInputStyle(frameNode, static_cast<InputStyle>(style));
}

void ResetTextAreaStyle(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::SetInputStyle(frameNode, DEFAULT_TEXT_AREA_STYLE);
}

void SetTextAreaSelectionMenuHidden(ArkUINodeHandle node, ArkUI_Uint32 contextMenuHidden)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::SetSelectionMenuHidden(frameNode, static_cast<bool>(contextMenuHidden));
}

void ResetTextAreaSelectionMenuHidden(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::SetSelectionMenuHidden(frameNode, DEFAULT_SELECTION_MENU_HIDDEN);
}

void SetTextAreaMaxLines(ArkUINodeHandle node, ArkUI_Uint32 maxLine)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::SetMaxViewLines(frameNode, maxLine);
    TextFieldModelNG::SetNormalMaxViewLines(frameNode, maxLine);
}

void ResetTextAreaMaxLines(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::SetMaxViewLines(frameNode, DEFAULT_MAX_VIEW_LINE);
    TextFieldModelNG::SetNormalMaxViewLines(frameNode, Infinity<uint32_t>());
}

void SetTextAreaCopyOption(ArkUINodeHandle node, ArkUI_Int32 value)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::SetCopyOption(frameNode, static_cast<CopyOptions>(value));
}

void ResetTextAreaCopyOption(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::SetCopyOption(frameNode, DEFAULT_COPY_OPTIONS_VALUE);
}

void SetTextAreaPlaceholderColor(ArkUINodeHandle node, ArkUI_Uint32 color)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::SetPlaceholderColor(frameNode, Color(color));
}

void ResetTextAreaPlaceholderColor(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto pipeline = frameNode->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetThemeManager()->GetTheme<TextFieldTheme>();
    CHECK_NULL_VOID(theme);
    uint32_t color = theme->GetPlaceholderColor().GetValue();
    TextFieldModelNG::SetPlaceholderColor(frameNode, Color(color));
}

void SetTextAreaTextAlign(ArkUINodeHandle node, ArkUI_Int32 value)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextAlign value_textAlign = static_cast<TextAlign>(value);
    TextFieldModelNG::SetTextAlign(frameNode, value_textAlign);
}

void ResetTextAreaTextAlign(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::SetTextAlign(frameNode, TextAlign::START);
}

void SetTextAreaPlaceholderFont(ArkUINodeHandle node, const struct ArkUIResourceLength *size, ArkUI_CharPtr weight,
    ArkUI_CharPtr family, ArkUI_Int32 style)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    Font font;
    auto unitEnum = static_cast<OHOS::Ace::DimensionUnit>(size->unit);
    if (size->unit >= 0) {
        if (unitEnum == DimensionUnit::CALC) {
            font.fontSize = CalcDimension(size->string, DimensionUnit::CALC);
        } else {
            font.fontSize = CalcDimension(size->value, unitEnum);
        }
    } else {
        auto pipeline = frameNode->GetContext();
        CHECK_NULL_VOID(pipeline);
        auto theme = pipeline->GetThemeManager()->GetTheme<TextFieldTheme>();
        CHECK_NULL_VOID(theme);
        font.fontSize = theme->GetFontSize();
    }

    if (weight != nullptr) {
        font.fontWeight = Framework::ConvertStrToFontWeight(weight);
    } else {
        font.fontWeight = DEFAULT_FONT_WEIGHT;
    }

    if (family != nullptr) {
        font.fontFamilies = Framework::ConvertStrToFontFamilies(std::string(family));
    } else {
        std::vector<std::string> fontFamilies;
        fontFamilies.emplace_back(std::string(DEFAULT_FONT_FAMILY));
        font.fontFamilies = fontFamilies;
    }

    if (style >= 0) {
        font.fontStyle = static_cast<Ace::FontStyle>(style);
    } else {
        font.fontStyle = DEFAULT_FONT_STYLE;
    }
    TextFieldModelNG::SetPlaceholderFont(frameNode, font);
}

void SetTextAreaPlaceholderFontEnum(ArkUINodeHandle node, const struct ArkUIResourceLength* size, ArkUI_Int32 weight,
    ArkUI_CharPtr family, ArkUI_Int32 style)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    Font font;
    auto unitEnum = static_cast<OHOS::Ace::DimensionUnit>(size->unit);
    if (size->unit >= 0) {
        if (unitEnum == DimensionUnit::CALC) {
            font.fontSize = CalcDimension(size->string, DimensionUnit::CALC);
        } else {
            font.fontSize = CalcDimension(size->value, unitEnum);
        }
    } else {
        auto pipeline = frameNode->GetContext();
        CHECK_NULL_VOID(pipeline);
        auto theme = pipeline->GetThemeManager()->GetTheme<TextFieldTheme>();
        CHECK_NULL_VOID(theme);
        font.fontSize = theme->GetFontSize();
    }

    if (weight > -1) {
        font.fontWeight = static_cast<FontWeight>(weight);
    } else {
        font.fontWeight = DEFAULT_FONT_WEIGHT;
    }

    if (family != nullptr) {
        font.fontFamilies = Framework::ConvertStrToFontFamilies(std::string(family));
    } else {
        std::vector<std::string> fontFamilies;
        fontFamilies.emplace_back(std::string(DEFAULT_FONT_FAMILY));
        font.fontFamilies = fontFamilies;
    }

    if (style >= 0) {
        font.fontStyle = static_cast<Ace::FontStyle>(style);
    } else {
        font.fontStyle = DEFAULT_FONT_STYLE;
    }
    TextFieldModelNG::SetPlaceholderFont(frameNode, font);
}

void ResetTextAreaPlaceholderFont(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto pipeline = frameNode->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetThemeManager()->GetTheme<TextFieldTheme>();
    CHECK_NULL_VOID(theme);
    Font font;
    font.fontSize = theme->GetFontSize();
    font.fontWeight = DEFAULT_FONT_WEIGHT;
    font.fontStyle = DEFAULT_FONT_STYLE;
    std::vector<std::string> fontFamilies;
    fontFamilies.emplace_back(std::string(DEFAULT_FONT_FAMILY));
    font.fontFamilies = fontFamilies;
    TextFieldModelNG::SetPlaceholderFont(frameNode, font);
}

void SetTextAreaBarState(ArkUINodeHandle node, ArkUI_Uint32 barStateValue)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    DisplayMode displayMode = static_cast<DisplayMode>(barStateValue);
    TextFieldModelNG::SetBarState(frameNode, displayMode);
}

void ResetTextAreaBarState(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::SetBarState(frameNode, DEFAULT_BAR_STATE_VALUE);
}

void SetTextAreaEnableKeyboardOnFocus(ArkUINodeHandle node, ArkUI_Uint32 keyboardOnFocusValue)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::RequestKeyboardOnFocus(frameNode, static_cast<bool>(keyboardOnFocusValue));
}

void ResetTextAreaEnableKeyboardOnFocus(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::RequestKeyboardOnFocus(frameNode, DEFAULT_KEY_BOARD_VALUE);
}

void SetTextAreaFontFamily(ArkUINodeHandle node, ArkUI_CharPtr fontFamily)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    std::vector<std::string> fontFamilies;
    fontFamilies = Framework::ConvertStrToFontFamilies(std::string(fontFamily));
    TextFieldModelNG::SetFontFamily(frameNode, fontFamilies);
}

void ResetTextAreaFontFamily(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    std::vector<std::string> fontFamilies;
    fontFamilies.emplace_back(std::string(DEFAULT_FONT_FAMILY));
    TextFieldModelNG::SetFontFamily(frameNode, fontFamilies);
}

void SetTextAreaShowCounter(ArkUINodeHandle node, ArkUI_Uint32 value)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::SetShowCounter(frameNode, static_cast<bool>(value));
}

void ResetTextAreaShowCounter(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::SetShowCounter(frameNode, false);
}

void SetTextAreaCaretColor(ArkUINodeHandle node, ArkUI_Uint32 color)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::SetCaretColor(frameNode, Color(color));
}

void ResetTextAreaCaretColor(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto pipeline = frameNode->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetThemeManager()->GetTheme<TextFieldTheme>();
    CHECK_NULL_VOID(theme);
    auto caretColor = static_cast<int32_t>(theme->GetCursorColor().GetValue());
    TextFieldModelNG::SetCaretColor(frameNode, Color(caretColor));
}

void SetTextAreaMaxLength(ArkUINodeHandle node, ArkUI_Int32 value)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::SetMaxLength(frameNode, value);
}

void ResetTextAreaMaxLength(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::ResetMaxLength(frameNode);
}

void SetTextAreaFontColor(ArkUINodeHandle node, ArkUI_Uint32 color)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::SetTextColor(frameNode, Color(color));
}

void ResetTextAreaFontColor(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    int32_t textColor = 0;
    auto pipeline = frameNode->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetThemeManager()->GetTheme<TextFieldTheme>();
    textColor = static_cast<int32_t>(theme->GetTextColor().GetValue());
    TextFieldModelNG::SetTextColor(frameNode, Color(textColor));
}

void SetTextAreaFontStyle(ArkUINodeHandle node, ArkUI_Uint32 value)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::SetFontStyle(frameNode, static_cast<Ace::FontStyle>(value));
}

void ResetTextAreaFontStyle(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::SetFontStyle(frameNode, OHOS::Ace::FontStyle::NORMAL);
}

void SetTextAreaFontWeightStr(ArkUINodeHandle node, ArkUI_CharPtr fontWeight)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::SetFontWeight(frameNode, Framework::ConvertStrToFontWeight(fontWeight));
}

void SetTextAreaFontWeight(ArkUINodeHandle node, ArkUI_Int32 fontWeight)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::SetFontWeight(frameNode, static_cast<FontWeight>(fontWeight));
}

void ResetTextAreaFontWeight(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::SetFontWeight(frameNode, OHOS::Ace::FontWeight::NORMAL);
}

void SetTextAreaFontSize(ArkUINodeHandle node, const struct ArkUIResourceLength *size)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto unitEnum = static_cast<OHOS::Ace::DimensionUnit>(size->unit);
    if (unitEnum == DimensionUnit::CALC) {
        TextFieldModelNG::SetFontSize(frameNode, CalcDimension(size->string, DimensionUnit::CALC));
    } else {
        TextFieldModelNG::SetFontSize(frameNode, CalcDimension(size->value, unitEnum));
    }
}

void ResetTextAreaFontSize(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto pipeline = frameNode->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetThemeManager()->GetTheme<TextFieldTheme>();
    CHECK_NULL_VOID(theme);
    TextFieldModelNG::SetFontSize(frameNode, Dimension(theme->GetFontSize()));
}

void SetCounterType(ArkUINodeHandle node, ArkUI_Int32 value)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::SetCounterType(frameNode, value);
}

void SetTextAreaPlaceholderString(ArkUINodeHandle node, ArkUI_CharPtr value)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    std::string placeholderStr(value);
    TextFieldModelNG::SetTextFieldPlaceHolder(frameNode, UtfUtils::Str8ToStr16(placeholderStr));
}

void SetTextAreaTextString(ArkUINodeHandle node, ArkUI_CharPtr value)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    std::string textStr(value);
    TextFieldModelNG::SetTextFieldText(frameNode, UtfUtils::Str8ToStr16(textStr));
}

void StopTextAreaTextEditing(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::StopTextFieldEditing(frameNode);
}

ArkUI_CharPtr GetTextAreaPlaceholder(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_RETURN(frameNode, "");
    g_strValue = UtfUtils::Str16ToStr8(TextFieldModelNG::GetPlaceholderText(frameNode));
    return g_strValue.c_str();
}

ArkUI_CharPtr GetTextAreaText(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_RETURN(frameNode, "");
    g_strValue = UtfUtils::Str16ToStr8(TextFieldModelNG::GetTextFieldText(frameNode));
    return g_strValue.c_str();
}

ArkUI_Uint32 GetTextAreaCaretColor(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_UINT_CODE);
    return TextFieldModelNG::GetCaretColor(frameNode).GetValue();
}

ArkUI_Uint32 GetTextAreaMaxLength(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_UINT_CODE);
    return TextFieldModelNG::GetMaxLength(frameNode);
}

ArkUI_Uint32 GetTextAreaPlaceholderColor(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_UINT_CODE);
    return TextFieldModelNG::GetPlaceholderColor(frameNode).GetValue();
}

void GetTextAreaPlaceholderFont(ArkUINodeHandle node, ArkUITextFont* font)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    Font value = TextFieldModelNG::GetPlaceholderFont(frameNode);
    if (value.fontSize.has_value()) {
        font->fontSize = value.fontSize.value().GetNativeValue(static_cast<DimensionUnit>(font->fontSizeUnit));
    }
    if (value.fontWeight.has_value()) {
        font->fontWeight = static_cast<ArkUI_Int32>(value.fontWeight.value());
    }
    if (!value.fontFamilies.empty()) {
        std::string families;
        uint32_t index = 0;
        for (auto& family : value.fontFamilies) {
            families += family;
            if (index != value.fontFamilies.size() - 1) {
                families += ",";
            }
            index ++;
        }
        g_strValue = families;
        font->fontFamilies = g_strValue.c_str();
    }
    if (value.fontStyle.has_value()) {
        font->fontStyle = static_cast<ArkUI_Int32>(value.fontStyle.value());
    }
}

ArkUI_Bool GetTextAreaEditing(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_INT_CODE);
    return TextFieldModelNG::GetTextFieldEditing(frameNode);
}

void SetTextAreaBackgroundColor(ArkUINodeHandle node, uint32_t color)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::SetBackgroundColor(frameNode, Color(color));
}

void ResetTextAreaBackgroundColor(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    Color backgroundColor;
    auto pipeline = frameNode->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto buttonTheme = pipeline->GetTheme<TextFieldTheme>();
    CHECK_NULL_VOID(buttonTheme);
    backgroundColor = buttonTheme->GetBgColor();
    TextFieldModelNG::SetBackgroundColor(frameNode, backgroundColor);
}

void SetTextAreaType(ArkUINodeHandle node, ArkUI_Int32 type)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::SetType(frameNode, CastToTextInputType(type));
}

void ResetTextAreaType(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::SetType(frameNode, Ace::TextInputType::TEXT);
}

ArkUI_Int32 GetTextAreaType(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_UINT_CODE);
    return static_cast<ArkUI_Int32>(TextFieldModelNG::GetType(frameNode));
}

ArkUI_Int32 GetTextAreaTextAlign(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_INT_CODE);
    return static_cast<ArkUI_Int32>(TextFieldModelNG::GetTextAlign(frameNode));
}

void SetTextAreaShowCounterOptions(
    ArkUINodeHandle node, ArkUI_Bool open, ArkUI_Int32 thresholdPercentage, ArkUI_Bool highlightBorder)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::SetShowCounter(frameNode, open);
    TextFieldModelNG::SetCounterType(frameNode, thresholdPercentage);
    TextFieldModelNG::SetShowCounterBorder(frameNode, highlightBorder);
}

void ResetTextAreaShowCounterOptions(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::SetShowCounter(frameNode, false);
    TextFieldModelNG::SetCounterType(frameNode, -1);
    TextFieldModelNG::SetShowCounterBorder(frameNode, true);
}

void GetTextAreaShowCounterOptions(ArkUINodeHandle node, ArkUIShowCountOptions* options)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    options->open = TextFieldModelNG::GetShowCounter(frameNode);
    options->thresholdPercentage = TextFieldModelNG::GetCounterType(frameNode);
    options->highlightBorder = TextFieldModelNG::GetShowCounterBorder(frameNode);
}
void SetTextAreaDecoration(ArkUINodeHandle node, ArkUI_Int32 decoration, ArkUI_Uint32 color, ArkUI_Int32 style)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::SetTextDecoration(frameNode, static_cast<TextDecoration>(decoration));
    TextFieldModelNG::SetTextDecorationColor(frameNode, Color(color));
    TextFieldModelNG::SetTextDecorationStyle(frameNode, static_cast<TextDecorationStyle>(style));
}

void ResetTextAreaDecoration(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::SetTextDecoration(frameNode, DEFAULT_TEXT_DECORATION);
    TextFieldModelNG::SetTextDecorationColor(frameNode, DEFAULT_DECORATION_COLOR);
    TextFieldModelNG::SetTextDecorationStyle(frameNode, DEFAULT_DECORATION_STYLE);
}

void SetTextAreaLetterSpacing(ArkUINodeHandle node, ArkUI_Float32 value, ArkUI_Int32 unit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::SetLetterSpacing(frameNode, CalcDimension(value, (DimensionUnit)unit));
}

void ResetTextAreaLetterSpacing(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CalcDimension value;
    value.Reset();
    TextFieldModelNG::SetLetterSpacing(frameNode, value);
}

void SetTextAreaLineHeight(ArkUINodeHandle node, ArkUI_Float32 value, ArkUI_Int32 unit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::SetLineHeight(frameNode, CalcDimension(value, (DimensionUnit)unit));
}

void ResetTextAreaLineHeight(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CalcDimension value;
    value.Reset();
    TextFieldModelNG::SetLineHeight(frameNode, value);
}

void SetTextAreaFontFeature(ArkUINodeHandle node, ArkUI_CharPtr value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::string strValue = value;
    TextFieldModelNG::SetFontFeature(frameNode, ParseFontFeatureSettings(strValue));
}

void ResetTextAreaFontFeature(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    std::string strValue = "";
    TextFieldModelNG::SetFontFeature(frameNode, ParseFontFeatureSettings(strValue));
}

void SetTextAreaWordBreak(ArkUINodeHandle node, ArkUI_Uint32 wordBreak)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (wordBreak < 0 || wordBreak >= WORD_BREAK_TYPES.size()) {
        wordBreak = 2; // 2 is the default value of WordBreak::BREAK_WORD
    }
    TextFieldModelNG::SetWordBreak(frameNode, WORD_BREAK_TYPES[wordBreak]);
}

void ResetTextAreaWordBreak(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::SetWordBreak(frameNode, WORD_BREAK_TYPES[2]); // 2 is the default value of WordBreak::BREAK_WORD
}

void SetTextAreaAdaptMinFontSize(ArkUINodeHandle node, ArkUI_Float32 value, ArkUI_Int32 unit)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::SetAdaptMinFontSize(frameNode, CalcDimension(value, (DimensionUnit)unit));
}

void ResetTextAreaAdaptMinFontSize(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto pipelineContext = frameNode->GetContext();
    CHECK_NULL_VOID(pipelineContext);
    auto theme = pipelineContext->GetTheme<TextFieldTheme>();
    CHECK_NULL_VOID(theme);
    CalcDimension minFontSize = theme->GetTextStyle().GetAdaptMinFontSize();
    TextFieldModelNG::SetAdaptMinFontSize(frameNode, minFontSize);
}

void SetTextAreaAdaptMaxFontSize(ArkUINodeHandle node, ArkUI_Float32 value, ArkUI_Int32 unit)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::SetAdaptMaxFontSize(frameNode, CalcDimension(value, (DimensionUnit)unit));
}

void ResetTextAreaAdaptMaxFontSize(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto pipelineContext = frameNode->GetContext();
    CHECK_NULL_VOID(pipelineContext);
    auto theme = pipelineContext->GetTheme<TextFieldTheme>();
    CHECK_NULL_VOID(theme);
    CalcDimension maxFontSize = theme->GetTextStyle().GetAdaptMaxFontSize();
    TextFieldModelNG::SetAdaptMaxFontSize(frameNode, maxFontSize);
}

void SetTextAreaHeightAdaptivePolicy(ArkUINodeHandle node, ArkUI_Int32 value)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::SetHeightAdaptivePolicy(frameNode, static_cast<Ace::TextHeightAdaptivePolicy>(value));
}

void ResetTextAreaHeightAdaptivePolicy(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::SetHeightAdaptivePolicy(frameNode, TextHeightAdaptivePolicy::MAX_LINES_FIRST);
}

ArkUI_Bool GetTextAreaSelectionMenuHidden(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_INT_CODE);
    return TextFieldModelNG::GetSelectionMenuHidden(frameNode);
}

void SetTextAreaSelectedBackgroundColor(ArkUINodeHandle node, ArkUI_Uint32 color)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    Color selectedColor = Color(color);
    if (selectedColor.GetAlpha() == DEFAULT_ALPHA) {
        // Default setting of 20% opacity
        selectedColor = selectedColor.ChangeOpacity(DEFAULT_OPACITY);
    }
    TextFieldModelNG::SetSelectedBackgroundColor(frameNode, Color(color));
}

void ResetTextAreaSelectedBackgroundColor(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    Color selectedColor;
    auto pipeline = frameNode->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<TextFieldTheme>();
    CHECK_NULL_VOID(theme);
    selectedColor = theme->GetSelectedColor();
    if (selectedColor.GetAlpha() == DEFAULT_ALPHA) {
        // Default setting of 20% opacity
        selectedColor = selectedColor.ChangeOpacity(DEFAULT_OPACITY);
    }
    TextFieldModelNG::SetSelectedBackgroundColor(frameNode, selectedColor);
}

void SetTextAreaCaret(ArkUINodeHandle node, ArkUI_Float32 value, ArkUI_Int32 unit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CaretStyle caretStyle;
    caretStyle.caretWidth = CalcDimension(value, (DimensionUnit)unit);
    TextFieldModelNG::SetCaretStyle(frameNode, caretStyle);
}

void SetTextAreaCaretStyle(ArkUINodeHandle node, ArkUI_Float32 value, ArkUI_Int32 unit, ArkUI_Uint32 caretColor)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CaretStyle caretStyle;
    caretStyle.caretWidth = CalcDimension(value, (DimensionUnit)unit);
    TextFieldModelNG::SetCaretStyle(frameNode, caretStyle);
    TextFieldModelNG::SetCaretColor(frameNode, Color(caretColor));
}

void ResetTextAreaCaretStyle(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    auto pipeline = frameNode->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetThemeManager()->GetTheme<TextFieldTheme>();
    CHECK_NULL_VOID(theme);
    CaretStyle caretStyle;
    caretStyle.caretWidth = theme->GetCursorWidth();
    uint32_t caretColor = theme->GetCursorColor().GetValue();
    TextFieldModelNG::SetCaretStyle(frameNode, caretStyle);
    TextFieldModelNG::SetCaretColor(frameNode, Color(caretColor));
}

void SetTextAreaTextOverflow(ArkUINodeHandle node, ArkUI_Int32 value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextOverflow valueTextOverflow = static_cast<TextOverflow>(value);
    TextFieldModelNG::SetTextOverflow(frameNode, valueTextOverflow);
}

void ResetTextAreaTextOverflow(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::SetTextOverflow(frameNode, TextOverflow::DEFAULT);
}

void SetTextAreaTextIndent(ArkUINodeHandle node, ArkUI_Float32 number, ArkUI_Int32 unit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::SetTextIndent(frameNode, Dimension(number, static_cast<DimensionUnit>(unit)));
}

void ResetTextAreaTextIndent(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::SetTextIndent(frameNode, CalcDimension(0, DimensionUnit::VP));
}

void SetTextAreaLineSpacing(ArkUINodeHandle node, ArkUI_Float32 value, ArkUI_Int32 unit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::SetLineSpacing(frameNode, CalcDimension(value, (DimensionUnit)unit));
}

void ResetTextAreaLineSpacing(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CalcDimension value;
    value.Reset();
    TextFieldModelNG::SetLineSpacing(frameNode, value);
}

ArkUI_CharPtr GetTextAreaFontFeature(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, nullptr);
    g_strValue = UnParseFontFeatureSetting(TextFieldModelNG::GetFontFeature(frameNode));
    return g_strValue.c_str();
}

ArkUI_Float32 GetTextAreaAdaptMinFontSize(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_FLOAT_CODE);
    return TextFieldModelNG::GetAdaptMinFontSize(frameNode).Value();
}

ArkUI_Float32 GetTextAreaAdaptMaxFontSize(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_FLOAT_CODE);
    return TextFieldModelNG::GetAdaptMaxFontSize(frameNode).Value();
}

ArkUI_Float32 GetTextAreaLineHeight(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_FLOAT_CODE);
    return TextFieldModelNG::GetLineHeight(frameNode).Value();
}

ArkUI_Int32 GetgetTextAreaMaxLines(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_FLOAT_CODE);
    return TextFieldModelNG::GetMaxLines(frameNode);
}
void SetTextAreaPadding(ArkUINodeHandle node, const struct ArkUISizeType* top, const struct ArkUISizeType* right,
    const struct ArkUISizeType* bottom, const struct ArkUISizeType* left)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CalcLength topDimen;
    CalcLength rightDimen;
    CalcLength bottomDimen;
    CalcLength leftDimen;
    if (top->string != nullptr) {
        topDimen = CalcLength(top->string);
    } else {
        topDimen = CalcLength(top->value, static_cast<DimensionUnit>(top->unit));
    }
    if (right->string != nullptr) {
        rightDimen = CalcLength(right->string);
    } else {
        rightDimen = CalcLength(right->value, static_cast<DimensionUnit>(right->unit));
    }
    if (bottom->string != nullptr) {
        bottomDimen = CalcLength(bottom->string);
    } else {
        bottomDimen = CalcLength(bottom->value, static_cast<DimensionUnit>(bottom->unit));
    }
    if (left->string != nullptr) {
        leftDimen = CalcLength(left->string);
    } else {
        leftDimen = CalcLength(left->value, static_cast<DimensionUnit>(left->unit));
    }
    NG::PaddingProperty paddings;
    paddings.top = std::optional<CalcLength>(topDimen);
    paddings.bottom = std::optional<CalcLength>(bottomDimen);
    paddings.left = std::optional<CalcLength>(leftDimen);
    paddings.right = std::optional<CalcLength>(rightDimen);
    TextFieldModelNG::SetPadding(frameNode, paddings);
}

void ResetTextAreaPadding(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto pipeline = frameNode->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetThemeManager()->GetTheme<TextFieldTheme>();
    CHECK_NULL_VOID(theme);
    auto textFieldPadding = theme->GetPadding();
    NG::PaddingProperty paddings;
    paddings.top = NG::CalcLength(textFieldPadding.Top());
    paddings.bottom = NG::CalcLength(textFieldPadding.Bottom());
    paddings.left = NG::CalcLength(textFieldPadding.Left());
    paddings.right = NG::CalcLength(textFieldPadding.Right());
    TextFieldModelNG::SetPadding(frameNode, paddings);
}

void SetTextAreaOnChange(ArkUINodeHandle node, void* callback)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (callback) {
        auto onChange = reinterpret_cast<std::function<void(const std::u16string&, PreviewText&)>*>(callback);
        TextFieldModelNG::SetOnChange(frameNode, std::move(*onChange));
    } else {
        TextFieldModelNG::SetOnChange(frameNode, nullptr);
    }
}

void ResetTextAreaOnChange(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::SetOnChange(frameNode, nullptr);
}

void SetTextAreaEnterKeyType(ArkUINodeHandle node, ArkUI_Int32 value)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::SetEnterKeyType(frameNode, CastToTextInputAction(value));
}

void ResetTextAreaEnterKeyType(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::SetEnterKeyType(frameNode, TextInputAction::NEW_LINE);
}

void SetTextAreaInputFilter(ArkUINodeHandle node, ArkUI_CharPtr value, void* callback)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::string inputFilter(value);
    if (callback) {
        auto onError = reinterpret_cast<std::function<void(const std::u16string&)>*>(callback);
        TextFieldModelNG::SetInputFilter(frameNode, inputFilter, *onError);
    } else {
        TextFieldModelNG::SetInputFilter(frameNode, inputFilter, nullptr);
    }
}

void ResetTextAreaInputFilter(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::SetInputFilter(frameNode, "", nullptr);
}

void SetTextAreaOnTextSelectionChange(ArkUINodeHandle node, void* callback)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (callback) {
        auto onChange = reinterpret_cast<std::function<void(int32_t, int32_t)>*>(callback);
        TextFieldModelNG::SetOnTextSelectionChange(frameNode, std::move(*onChange));
    } else {
        TextFieldModelNG::SetOnTextSelectionChange(frameNode, nullptr);
    }
}

void ResetTextAreaOnTextSelectionChange(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::SetOnTextSelectionChange(frameNode, nullptr);
}

void SetTextAreaOnContentScroll(ArkUINodeHandle node, void* callback)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (callback) {
        auto onScroll = reinterpret_cast<std::function<void(float, float)>*>(callback);
        TextFieldModelNG::SetOnContentScroll(frameNode, std::move(*onScroll));
    } else {
        TextFieldModelNG::SetOnContentScroll(frameNode, nullptr);
    }
}

void ResetTextAreaOnContentScroll(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::SetOnContentScroll(frameNode, nullptr);
}

void SetTextAreaOnEditChange(ArkUINodeHandle node, void* callback)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (callback) {
        auto onEditChange = reinterpret_cast<std::function<void(bool)>*>(callback);
        TextFieldModelNG::SetOnEditChange(frameNode, std::move(*onEditChange));
    } else {
        TextFieldModelNG::SetOnEditChange(frameNode, nullptr);
    }
}

void ResetTextAreaOnEditChange(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::SetOnEditChange(frameNode, nullptr);
}

void SetTextAreaOnCopy(ArkUINodeHandle node, void* callback)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (callback) {
        auto onCopy = reinterpret_cast<std::function<void(const std::u16string&)>*>(callback);
        TextFieldModelNG::SetOnCopy(frameNode, std::move(*onCopy));
    } else {
        TextFieldModelNG::SetOnCopy(frameNode, nullptr);
    }
}

void ResetTextAreaOnCopy(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::SetOnCopy(frameNode, nullptr);
}

void SetTextAreaOnCut(ArkUINodeHandle node, void* callback)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (callback) {
        auto onCut = reinterpret_cast<std::function<void(const std::u16string&)>*>(callback);
        TextFieldModelNG::SetOnCut(frameNode, std::move(*onCut));
    } else {
        TextFieldModelNG::SetOnCut(frameNode, nullptr);
    }
}

void ResetTextAreaOnCut(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::SetOnCut(frameNode, nullptr);
}

void SetTextAreaOnPaste(ArkUINodeHandle node, void* callback)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (callback) {
        auto onPasteWithEvent = reinterpret_cast<std::function<void(
                const std::u16string&, NG::TextCommonEvent&)>*>(callback);
        TextFieldModelNG::SetOnPasteWithEvent(frameNode, std::move(*onPasteWithEvent));
    } else {
        TextFieldModelNG::SetOnPasteWithEvent(frameNode, nullptr);
    }
}

void ResetTextAreaOnPaste(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::SetOnPasteWithEvent(frameNode, nullptr);
}

void SetTextAreaLineBreakStrategy(ArkUINodeHandle node, ArkUI_Uint32 lineBreakStrategy)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (lineBreakStrategy < 0 || lineBreakStrategy >= LINE_BREAK_STRATEGY_TYPES.size()) {
        lineBreakStrategy = 0; // 0 is the default value of LineBreakStrategy::GREEDY
    }
    TextFieldModelNG::SetLineBreakStrategy(frameNode, LINE_BREAK_STRATEGY_TYPES[lineBreakStrategy]);
}

void ResetTextAreaLineBreakStrategy(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    // 0 is the default value of LineBreakStrategy::GREEDY
    TextFieldModelNG::SetLineBreakStrategy(frameNode, LINE_BREAK_STRATEGY_TYPES[0]);
}

void SetTextAreaOnSubmitWithEvent(ArkUINodeHandle node, void* callback)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (callback) {
        auto onSubmit = reinterpret_cast<std::function<void(int32_t, NG::TextFieldCommonEvent&)>*>(callback);
        TextFieldModelNG::SetOnSubmit(frameNode, std::move(*onSubmit));
    } else {
        TextFieldModelNG::SetOnSubmit(frameNode, nullptr);
    }
}

void ResetTextAreaOnSubmitWithEvent(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::SetOnSubmit(frameNode, nullptr);
}

void SetTextAreaContentType(ArkUINodeHandle node, ArkUI_Int32 contentType)
{
    auto *frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (contentType < 0 || contentType > static_cast<ArkUI_Int32>(TextContentType::END)) {
        contentType = -1;
    }
    TextFieldModelNG::SetContentType(frameNode, static_cast<NG::TextContentType>(contentType));
}

void ResetTextAreaContentType(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::SetContentType(frameNode, static_cast<NG::TextContentType>(TextContentType::UNSPECIFIED));
}

void SetTextAreaEnableAutoFill(ArkUINodeHandle node, ArkUI_Uint32 enableAutoFill)
{
    auto *frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::SetEnableAutoFill(frameNode, static_cast<bool>(enableAutoFill));
}

void ResetTextAreaEnableAutoFill(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::SetEnableAutoFill(frameNode, DEFAULT_ENABLE_AUTO_FILL);
}

BorderStyle ConvertBorderStyle(int32_t value)
{
    auto style = static_cast<BorderStyle>(value);
    if (style < BorderStyle::SOLID || style > BorderStyle::NONE) {
        style = BorderStyle::SOLID;
    }
    return style;
}

void SetOptionalBorder(std::optional<Dimension>& optionalDimension, const ArkUI_Float32* values, ArkUI_Int32 valuesSize,
    ArkUI_Int32& offset)
{
    bool hasValue = static_cast<bool>(values[offset]);
    if (hasValue) {
        optionalDimension =
            Dimension(values[offset + NUM_1], static_cast<OHOS::Ace::DimensionUnit>(values[offset + NUM_2]));
    }
    offset = offset + NUM_3;
}

void SetAllWidthOptionalBorder(NG::BorderWidthProperty& borderWidth, const ArkUI_Float32* values,
    ArkUI_Int32 valuesSize, ArkUI_Int32& offset)
{
    SetOptionalBorder(borderWidth.leftDimen, values, valuesSize, offset);
    SetOptionalBorder(borderWidth.rightDimen, values, valuesSize, offset);
    SetOptionalBorder(borderWidth.topDimen, values, valuesSize, offset);
    SetOptionalBorder(borderWidth.bottomDimen, values, valuesSize, offset);
}

void SetAllRadiusOptionalBorder(NG::BorderRadiusProperty& borderRadius, const ArkUI_Float32* values,
    ArkUI_Int32 valuesSize, ArkUI_Int32& offset)
{
    SetOptionalBorder(borderRadius.radiusTopLeft, values, valuesSize, offset);
    SetOptionalBorder(borderRadius.radiusTopRight, values, valuesSize, offset);
    SetOptionalBorder(borderRadius.radiusBottomLeft, values, valuesSize, offset);
    SetOptionalBorder(borderRadius.radiusBottomRight, values, valuesSize, offset);
}

void SetOptionalBorderColor(
    std::optional<Color>& optionalColor, const uint32_t* values, ArkUI_Int32 valuesSize, ArkUI_Int32& offset)
{
    auto hasValue = values[offset];
    if (static_cast<bool>(hasValue)) {
        optionalColor = Color(values[offset + NUM_1]);
    }
    offset = offset + NUM_2;
}

void SetAllOptionalBorderColor(
    NG::BorderColorProperty& borderColors, const uint32_t* values, ArkUI_Int32 valuesSize, ArkUI_Int32& offset)
{
    SetOptionalBorderColor(borderColors.leftColor, values, valuesSize, offset);
    SetOptionalBorderColor(borderColors.rightColor, values, valuesSize, offset);
    SetOptionalBorderColor(borderColors.topColor, values, valuesSize, offset);
    SetOptionalBorderColor(borderColors.bottomColor, values, valuesSize, offset);
}

void SetOptionalBorderStyle(
    std::optional<BorderStyle>& optionalStyle, const uint32_t* values, ArkUI_Int32 valuesSize, ArkUI_Int32& offset)
{
    auto hasValue = values[offset];
    if (static_cast<bool>(hasValue)) {
        optionalStyle = ConvertBorderStyle(values[offset + NUM_1]);
    }
    offset = offset + NUM_2;
}

void SetAllOptionalBorderStyle(
    NG::BorderStyleProperty& borderStyles, const uint32_t* values, ArkUI_Int32 valuesSize, ArkUI_Int32& offset)
{
    SetOptionalBorderStyle(borderStyles.styleLeft, values, valuesSize, offset);
    SetOptionalBorderStyle(borderStyles.styleRight, values, valuesSize, offset);
    SetOptionalBorderStyle(borderStyles.styleTop, values, valuesSize, offset);
    SetOptionalBorderStyle(borderStyles.styleBottom, values, valuesSize, offset);
}

void SetTextAreaBorder(ArkUINodeHandle node, const ArkUI_Float32* values, ArkUI_Int32 valuesSize,
    const uint32_t* colorAndStyle, int32_t colorAndStyleSize)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if ((values == nullptr) || (valuesSize != NUM_24) || (colorAndStyle == nullptr) || colorAndStyleSize != NUM_16) {
        return;
    }

    int32_t offset = NUM_0;
    NG::BorderWidthProperty borderWidth;
    SetAllWidthOptionalBorder(borderWidth, values, valuesSize, offset);
    borderWidth.multiValued = true;
    if (borderWidth.leftDimen.has_value() || borderWidth.rightDimen.has_value() || borderWidth.topDimen.has_value() ||
        borderWidth.bottomDimen.has_value()) {
        TextFieldModelNG::SetBorderWidth(frameNode, borderWidth);
    }

    NG::BorderRadiusProperty borderRadius;
    SetAllRadiusOptionalBorder(borderRadius, values, valuesSize, offset);
    borderRadius.multiValued = true;
    if (borderRadius.radiusTopLeft.has_value() || borderRadius.radiusTopRight.has_value() ||
        borderRadius.radiusBottomLeft.has_value() || borderRadius.radiusBottomRight.has_value()) {
        TextFieldModelNG::SetBorderRadius(frameNode, borderRadius);
    }

    int32_t colorAndStyleOffset = NUM_0;
    NG::BorderColorProperty borderColors;
    SetAllOptionalBorderColor(borderColors, colorAndStyle,
        colorAndStyleSize, colorAndStyleOffset);
    borderColors.multiValued = true;
    TextFieldModelNG::SetBorderColor(frameNode, borderColors);

    NG::BorderStyleProperty borderStyles;
    SetAllOptionalBorderStyle(borderStyles, colorAndStyle,
        colorAndStyleSize, colorAndStyleOffset);
    borderStyles.multiValued = true;
    TextFieldModelNG::SetBorderStyle(frameNode, borderStyles);
}

void ResetTextAreaBorder(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    BorderWidthProperty borderWidth;
    borderWidth.SetBorderWidth(Dimension(0));
    TextFieldModelNG::SetBorderWidth(frameNode, borderWidth);

    BorderRadiusProperty borderRadius;
    borderRadius.SetRadius(Dimension(0));
    TextFieldModelNG::SetBorderRadius(frameNode, borderRadius);

    BorderColorProperty borderColor;
    borderColor.SetColor(Color::BLACK);
    TextFieldModelNG::SetBorderColor(frameNode, borderColor);

    BorderStyleProperty borderStyle;
    borderStyle.SetBorderStyle(BorderStyle::SOLID);
    TextFieldModelNG::SetBorderStyle(frameNode, borderStyle);
}

void SetTextAreaBorderWidth(ArkUINodeHandle node, const ArkUI_Float32* values,
    const ArkUI_Int32* units, ArkUI_Int32 length)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (length != DEFAULT_LENGTH) {
        return;
    }
    std::optional<CalcDimension> topDimen;
    std::optional<CalcDimension> rightDimen;
    std::optional<CalcDimension> bottomDimen;
    std::optional<CalcDimension> leftDimen;

    if (values[NUM_0] != -1 &&
        static_cast<OHOS::Ace::DimensionUnit>(units[NUM_0]) != OHOS::Ace::DimensionUnit::INVALID) {
        topDimen = Dimension(values[NUM_0], static_cast<OHOS::Ace::DimensionUnit>(units[NUM_0]));
    }
    if (values[NUM_1] != -1 &&
        static_cast<OHOS::Ace::DimensionUnit>(units[NUM_1]) != OHOS::Ace::DimensionUnit::INVALID) {
        rightDimen = Dimension(values[NUM_1], static_cast<OHOS::Ace::DimensionUnit>(units[NUM_1]));
    }
    if (values[NUM_2] != -1 &&
        static_cast<OHOS::Ace::DimensionUnit>(units[NUM_2]) != OHOS::Ace::DimensionUnit::INVALID) {
        bottomDimen = Dimension(values[NUM_2], static_cast<OHOS::Ace::DimensionUnit>(units[NUM_2]));
    }
    if (values[NUM_3] != -1 &&
        static_cast<OHOS::Ace::DimensionUnit>(units[NUM_3]) != OHOS::Ace::DimensionUnit::INVALID) {
        leftDimen = Dimension(values[NUM_3], static_cast<OHOS::Ace::DimensionUnit>(units[NUM_3]));
    }

    NG::BorderWidthProperty borderWidth;
    borderWidth.leftDimen = leftDimen;
    borderWidth.rightDimen = rightDimen;
    borderWidth.topDimen = topDimen;
    borderWidth.bottomDimen = bottomDimen;
    borderWidth.multiValued = true;
    TextFieldModelNG::SetBorderWidth(frameNode, borderWidth);
}

void ResetTextAreaBorderWidth(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    BorderWidthProperty borderWidth;
    borderWidth.SetBorderWidth(Dimension(0));
    TextFieldModelNG::SetBorderWidth(frameNode, borderWidth);
}

void SetTextAreaBorderColor(ArkUINodeHandle node, uint32_t topColorInt,
    uint32_t rightColorInt, uint32_t bottomColorInt, uint32_t leftColorInt)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NG::BorderColorProperty borderColors;
    borderColors.topColor = Color(topColorInt);
    borderColors.rightColor = Color(rightColorInt);
    borderColors.bottomColor = Color(bottomColorInt);
    borderColors.leftColor = Color(leftColorInt);
    borderColors.multiValued = true;
    TextFieldModelNG::SetBorderColor(frameNode, borderColors);
}

void ResetTextAreaBorderColor(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    BorderColorProperty borderColor;
    borderColor.SetColor(Color::BLACK);
    TextFieldModelNG::SetBorderColor(frameNode, borderColor);
}

void SetTextAreaBorderStyle(ArkUINodeHandle node, const ArkUI_Int32* styles, ArkUI_Int32 length)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (length == NUM_1) {
        BorderStyleProperty borderStyle;
        borderStyle.SetBorderStyle(ConvertBorderStyle(styles[NUM_0]));
        TextFieldModelNG::SetBorderStyle(frameNode, borderStyle);
        return;
    }
    if (length == NUM_4) {
        NG::BorderStyleProperty borderStyles;
        borderStyles.styleLeft = ConvertBorderStyle(styles[NUM_3]);
        borderStyles.styleRight = ConvertBorderStyle(styles[NUM_1]);
        borderStyles.styleTop = ConvertBorderStyle(styles[NUM_0]);
        borderStyles.styleBottom = ConvertBorderStyle(styles[NUM_2]);
        borderStyles.multiValued = true;
        TextFieldModelNG::SetBorderStyle(frameNode, borderStyles);
    }
}

void ResetTextAreaBorderStyle(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    BorderStyleProperty borderStyle;
    borderStyle.SetBorderStyle(BorderStyle::SOLID);
    TextFieldModelNG::SetBorderStyle(frameNode, borderStyle);
}

void SetTextAreaBorderRadius(ArkUINodeHandle node, const ArkUI_Float32* values,
    const ArkUI_Int32* units, ArkUI_Int32 length)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (length != DEFAULT_LENGTH) {
        return;
    }
    NG::BorderRadiusProperty borderRadius;
    borderRadius.radiusTopLeft = Dimension(values[NUM_0], static_cast<OHOS::Ace::DimensionUnit>(units[NUM_0]));
    borderRadius.radiusTopRight = Dimension(values[NUM_1], static_cast<OHOS::Ace::DimensionUnit>(units[NUM_1]));
    borderRadius.radiusBottomLeft = Dimension(values[NUM_2], static_cast<OHOS::Ace::DimensionUnit>(units[NUM_2]));
    borderRadius.radiusBottomRight = Dimension(values[NUM_3], static_cast<OHOS::Ace::DimensionUnit>(units[NUM_3]));
    borderRadius.multiValued = true;
    TextFieldModelNG::SetBorderRadius(frameNode, borderRadius);
}

void ResetTextAreaBorderRadius(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    BorderRadiusProperty borderRadius;
    borderRadius.SetRadius(Dimension(0));
    TextFieldModelNG::SetBorderRadius(frameNode, borderRadius);
}

void SetTextAreaMargin(ArkUINodeHandle node, const struct ArkUISizeType* top, const struct ArkUISizeType* right,
    const struct ArkUISizeType* bottom, const struct ArkUISizeType* left)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CalcLength topDimen;
    CalcLength rightDimen;
    CalcLength bottomDimen;
    CalcLength leftDimen;
    if (top->string != nullptr) {
        topDimen = CalcLength(top->string);
    } else {
        topDimen = CalcLength(top->value, static_cast<DimensionUnit>(top->unit));
    }
    if (right->string != nullptr) {
        rightDimen = CalcLength(right->string);
    } else {
        rightDimen = CalcLength(right->value, static_cast<DimensionUnit>(right->unit));
    }
    if (bottom->string != nullptr) {
        bottomDimen = CalcLength(bottom->string);
    } else {
        bottomDimen = CalcLength(bottom->value, static_cast<DimensionUnit>(bottom->unit));
    }
    if (left->string != nullptr) {
        leftDimen = CalcLength(left->string);
    } else {
        leftDimen = CalcLength(left->value, static_cast<DimensionUnit>(left->unit));
    }
    NG::PaddingProperty paddings;
    paddings.top = std::optional<CalcLength>(topDimen);
    paddings.bottom = std::optional<CalcLength>(bottomDimen);
    paddings.left = std::optional<CalcLength>(leftDimen);
    paddings.right = std::optional<CalcLength>(rightDimen);
    TextFieldModelNG::SetMargin(frameNode, paddings);
}

void ResetTextAreaMargin(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NG::PaddingProperty paddings;
    paddings.top = NG::CalcLength(0.0);
    paddings.bottom = NG::CalcLength(0.0);
    paddings.left = NG::CalcLength(0.0);
    paddings.right = NG::CalcLength(0.0);
    TextFieldModelNG::SetMargin(frameNode, paddings);
}

void GetTextAreaMargin(ArkUINodeHandle node, ArkUI_Float32 (*values)[4], ArkUI_Int32 length, ArkUI_Int32 unit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto margin = TextFieldModelNG::GetMargin(frameNode);
    (*values)[NUM_0] = margin.top->GetDimension().GetNativeValue(static_cast<DimensionUnit>(unit));
    (*values)[NUM_1] = margin.right->GetDimension().GetNativeValue(static_cast<DimensionUnit>(unit));
    (*values)[NUM_2] = margin.bottom->GetDimension().GetNativeValue(static_cast<DimensionUnit>(unit));
    (*values)[NUM_3] = margin.left->GetDimension().GetNativeValue(static_cast<DimensionUnit>(unit));
    length = NUM_4;
}

void SetTextAreaOnWillInsert(ArkUINodeHandle node, ArkUI_Int64 callback)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (callback) {
        auto onWillInsert = reinterpret_cast<std::function<bool(const InsertValueInfo&)>*>(callback);
        TextFieldModelNG::SetOnWillInsertValueEvent(frameNode, std::move(*onWillInsert));
    } else {
        TextFieldModelNG::SetOnWillInsertValueEvent(frameNode, nullptr);
    }
}

void ResetTextAreaOnWillInsert(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::SetOnWillInsertValueEvent(frameNode, nullptr);
}

void SetTextAreaOnDidInsert(ArkUINodeHandle node, ArkUI_Int64 callback)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (callback) {
        auto onDidInsert = reinterpret_cast<std::function<void(const InsertValueInfo&)>*>(callback);
        TextFieldModelNG::SetOnDidInsertValueEvent(frameNode, std::move(*onDidInsert));
    } else {
        TextFieldModelNG::SetOnDidInsertValueEvent(frameNode, nullptr);
    }
}

void ResetTextAreaOnDidInsert(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::SetOnDidInsertValueEvent(frameNode, nullptr);
}

void SetTextAreaOnWillDelete(ArkUINodeHandle node, ArkUI_Int64 callback)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (callback) {
        auto onWillDelete = reinterpret_cast<std::function<bool(const DeleteValueInfo&)>*>(callback);
        TextFieldModelNG::SetOnWillDeleteEvent(frameNode, std::move(*onWillDelete));
    } else {
        TextFieldModelNG::SetOnWillDeleteEvent(frameNode, nullptr);
    }
}

void ResetTextAreaOnWillDelete(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::SetOnWillDeleteEvent(frameNode, nullptr);
}

void SetTextAreaOnDidDelete(ArkUINodeHandle node, ArkUI_Int64 callback)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (callback) {
        auto onDidDelete = reinterpret_cast<std::function<void(const DeleteValueInfo&)>*>(callback);
        TextFieldModelNG::SetOnDidDeleteEvent(frameNode, std::move(*onDidDelete));
    } else {
        TextFieldModelNG::SetOnDidDeleteEvent(frameNode, nullptr);
    }
}

void ResetTextAreaOnDidDelete(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::SetOnDidDeleteEvent(frameNode, nullptr);
}

void SetTextAreaEnablePreviewText(ArkUINodeHandle node, ArkUI_Uint32 value)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::SetEnablePreviewText(frameNode, static_cast<bool>(value));
}

void ResetTextAreaEnablePreviewText(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::SetEnablePreviewText(frameNode, DEFAULT_ENABLE_PREVIEW_TEXT_VALUE);
}

void GetTextAreaPadding(ArkUINodeHandle node, ArkUI_Float32 (*values)[4], ArkUI_Int32 length, ArkUI_Int32 unit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto padding = TextFieldModelNG::GetPadding(frameNode);
    (*values)[NUM_0] = padding.top->GetDimensionContainsNegative().GetNativeValue(static_cast<DimensionUnit>(unit));
    (*values)[NUM_1] = padding.right->GetDimensionContainsNegative().GetNativeValue(static_cast<DimensionUnit>(unit));
    (*values)[NUM_2] = padding.bottom->GetDimensionContainsNegative().GetNativeValue(static_cast<DimensionUnit>(unit));
    (*values)[NUM_3] = padding.left->GetDimensionContainsNegative().GetNativeValue(static_cast<DimensionUnit>(unit));
    length = NUM_4;
}

void SetTextAreaSelectionMenuOptions(ArkUINodeHandle node, void* onCreateMenuCallback, void* onMenuItemClickCallback)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (onCreateMenuCallback) {
        NG::OnCreateMenuCallback onCreateMenu = *(reinterpret_cast<NG::OnCreateMenuCallback*>(onCreateMenuCallback));
        TextFieldModelNG::OnCreateMenuCallbackUpdate(frameNode, std::move(onCreateMenu));
    } else {
        TextFieldModelNG::OnCreateMenuCallbackUpdate(frameNode, nullptr);
    }
    if (onMenuItemClickCallback) {
        NG::OnMenuItemClickCallback onMenuItemClick =
            *(reinterpret_cast<NG::OnMenuItemClickCallback*>(onMenuItemClickCallback));
        TextFieldModelNG::OnMenuItemClickCallbackUpdate(frameNode, std::move(onMenuItemClick));
    } else {
        TextFieldModelNG::OnMenuItemClickCallbackUpdate(frameNode, nullptr);
    }
}

void ResetTextAreaSelectionMenuOptions(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NG::OnCreateMenuCallback onCreateMenuCallback;
    NG::OnMenuItemClickCallback onMenuItemClick;
    TextFieldModelNG::OnCreateMenuCallbackUpdate(frameNode, std::move(onCreateMenuCallback));
    TextFieldModelNG::OnMenuItemClickCallbackUpdate(frameNode, std::move(onMenuItemClick));
}

void SetTextAreaWidth(ArkUINodeHandle node, ArkUI_CharPtr value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto widthValue = std::string(value);
    TextFieldModelNG::SetWidth(frameNode, widthValue);
}

void ResetTextAreaWidth(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::ClearWidth(frameNode);
}

void SetTextAreaEnableHapticFeedback(ArkUINodeHandle node, ArkUI_Uint32 value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::SetEnableHapticFeedback(frameNode, static_cast<bool>(value));
}

void ResetTextAreaEnableHapticFeedback(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::SetEnableHapticFeedback(frameNode, DEFAULT_ENABLE_HAPTIC_FEEDBACK_VALUE);
}
} // namespace

namespace NodeModifier {
const ArkUITextAreaModifier* GetTextAreaModifier()
{
    static const ArkUITextAreaModifier modifier = { SetTextAreaStyle, ResetTextAreaStyle,
        SetTextAreaSelectionMenuHidden, ResetTextAreaSelectionMenuHidden, SetTextAreaMaxLines, ResetTextAreaMaxLines,
        SetTextAreaCopyOption, ResetTextAreaCopyOption, SetTextAreaPlaceholderColor, ResetTextAreaPlaceholderColor,
        SetTextAreaTextAlign, ResetTextAreaTextAlign, SetTextAreaPlaceholderFont, ResetTextAreaPlaceholderFont,
        SetTextAreaBarState, ResetTextAreaBarState, SetTextAreaEnableKeyboardOnFocus,
        ResetTextAreaEnableKeyboardOnFocus, SetTextAreaFontFamily, ResetTextAreaFontFamily, SetTextAreaShowCounter,
        ResetTextAreaShowCounter, SetTextAreaCaretColor, ResetTextAreaCaretColor, SetTextAreaMaxLength,
        ResetTextAreaMaxLength, SetTextAreaFontColor, ResetTextAreaFontColor, SetTextAreaFontStyle,
        ResetTextAreaFontStyle, SetTextAreaFontWeight, ResetTextAreaFontWeight, SetTextAreaFontSize,
        ResetTextAreaFontSize, SetCounterType, SetTextAreaPlaceholderString, SetTextAreaTextString,
        StopTextAreaTextEditing, SetTextAreaFontWeightStr, SetTextAreaPlaceholderFontEnum, GetTextAreaPlaceholder,
        GetTextAreaText, GetTextAreaCaretColor, GetTextAreaMaxLength, GetTextAreaPlaceholderColor,
        GetTextAreaPlaceholderFont, GetTextAreaEditing, SetTextAreaBackgroundColor, ResetTextAreaBackgroundColor,
        SetTextAreaType, ResetTextAreaType, GetTextAreaType, GetTextAreaTextAlign, SetTextAreaShowCounterOptions,
        ResetTextAreaShowCounterOptions, GetTextAreaShowCounterOptions, SetTextAreaDecoration, ResetTextAreaDecoration,
        SetTextAreaLetterSpacing, ResetTextAreaLetterSpacing, SetTextAreaLineHeight, ResetTextAreaLineHeight,
        SetTextAreaFontFeature, ResetTextAreaFontFeature, SetTextAreaWordBreak, ResetTextAreaWordBreak,
        SetTextAreaAdaptMinFontSize, ResetTextAreaAdaptMinFontSize, SetTextAreaAdaptMaxFontSize,
        ResetTextAreaAdaptMaxFontSize, SetTextAreaHeightAdaptivePolicy, ResetTextAreaHeightAdaptivePolicy,
        SetTextAreaSelectedBackgroundColor, ResetTextAreaSelectedBackgroundColor, SetTextAreaCaretStyle,
        ResetTextAreaCaretStyle, SetTextAreaTextOverflow, ResetTextAreaTextOverflow, SetTextAreaTextIndent,
        ResetTextAreaTextIndent, SetTextAreaLineSpacing, ResetTextAreaLineSpacing, GetTextAreaSelectionMenuHidden,
        GetTextAreaAdaptMinFontSize, GetTextAreaAdaptMaxFontSize, GetTextAreaLineHeight, GetgetTextAreaMaxLines,
        SetTextAreaPadding, ResetTextAreaPadding, GetTextAreaFontFeature, SetTextAreaOnChange, ResetTextAreaOnChange,
        SetTextAreaEnterKeyType, ResetTextAreaEnterKeyType, SetTextAreaInputFilter, ResetTextAreaInputFilter,
        SetTextAreaOnTextSelectionChange, ResetTextAreaOnTextSelectionChange, SetTextAreaOnContentScroll,
        ResetTextAreaOnContentScroll, SetTextAreaOnEditChange, ResetTextAreaOnEditChange, SetTextAreaOnCopy,
        ResetTextAreaOnCopy, SetTextAreaOnCut, ResetTextAreaOnCut, SetTextAreaOnPaste, ResetTextAreaOnPaste,
        SetTextAreaLineBreakStrategy, ResetTextAreaLineBreakStrategy, SetTextAreaOnSubmitWithEvent,
        ResetTextAreaOnSubmitWithEvent, SetTextAreaContentType, ResetTextAreaContentType, SetTextAreaEnableAutoFill,
        ResetTextAreaEnableAutoFill, SetTextAreaBorder, ResetTextAreaBorder, SetTextAreaBorderWidth,
        ResetTextAreaBorderWidth, SetTextAreaBorderColor, ResetTextAreaBorderColor, SetTextAreaBorderStyle,
        ResetTextAreaBorderStyle, SetTextAreaBorderRadius, ResetTextAreaBorderRadius, SetTextAreaMargin,
        ResetTextAreaMargin, SetTextAreaCaret, GetTextAreaMargin, SetTextAreaOnWillInsert, ResetTextAreaOnWillInsert,
        SetTextAreaOnDidInsert, ResetTextAreaOnDidInsert, SetTextAreaOnWillDelete, ResetTextAreaOnWillDelete,
        SetTextAreaOnDidDelete, ResetTextAreaOnDidDelete, SetTextAreaEnablePreviewText, ResetTextAreaEnablePreviewText,
        GetTextAreaPadding, SetTextAreaSelectionMenuOptions, ResetTextAreaSelectionMenuOptions, SetTextAreaWidth,
        ResetTextAreaWidth, SetTextAreaEnableHapticFeedback, ResetTextAreaEnableHapticFeedback };
    return &modifier;
}

const CJUITextAreaModifier* GetCJUITextAreaModifier()
{
    static const CJUITextAreaModifier modifier = { SetTextAreaStyle, ResetTextAreaStyle,
        SetTextAreaSelectionMenuHidden, ResetTextAreaSelectionMenuHidden, SetTextAreaMaxLines, ResetTextAreaMaxLines,
        SetTextAreaCopyOption, ResetTextAreaCopyOption, SetTextAreaPlaceholderColor, ResetTextAreaPlaceholderColor,
        SetTextAreaTextAlign, ResetTextAreaTextAlign, SetTextAreaPlaceholderFont, ResetTextAreaPlaceholderFont,
        SetTextAreaBarState, ResetTextAreaBarState, SetTextAreaEnableKeyboardOnFocus,
        ResetTextAreaEnableKeyboardOnFocus, SetTextAreaFontFamily, ResetTextAreaFontFamily, SetTextAreaShowCounter,
        ResetTextAreaShowCounter, SetTextAreaCaretColor, ResetTextAreaCaretColor, SetTextAreaMaxLength,
        ResetTextAreaMaxLength, SetTextAreaFontColor, ResetTextAreaFontColor, SetTextAreaFontStyle,
        ResetTextAreaFontStyle, SetTextAreaFontWeight, ResetTextAreaFontWeight, SetTextAreaFontSize,
        ResetTextAreaFontSize, SetCounterType, SetTextAreaPlaceholderString, SetTextAreaTextString,
        StopTextAreaTextEditing, SetTextAreaFontWeightStr, SetTextAreaPlaceholderFontEnum, GetTextAreaPlaceholder,
        GetTextAreaText, GetTextAreaCaretColor, GetTextAreaMaxLength, GetTextAreaPlaceholderColor,
        GetTextAreaPlaceholderFont, GetTextAreaEditing, SetTextAreaBackgroundColor, ResetTextAreaBackgroundColor,
        SetTextAreaType, ResetTextAreaType, GetTextAreaType, GetTextAreaTextAlign, SetTextAreaShowCounterOptions,
        ResetTextAreaShowCounterOptions, GetTextAreaShowCounterOptions, SetTextAreaDecoration, ResetTextAreaDecoration,
        SetTextAreaLetterSpacing, ResetTextAreaLetterSpacing, SetTextAreaLineHeight, ResetTextAreaLineHeight,
        SetTextAreaFontFeature, ResetTextAreaFontFeature, SetTextAreaWordBreak, ResetTextAreaWordBreak,
        SetTextAreaAdaptMinFontSize, ResetTextAreaAdaptMinFontSize, SetTextAreaAdaptMaxFontSize,
        ResetTextAreaAdaptMaxFontSize, SetTextAreaHeightAdaptivePolicy, ResetTextAreaHeightAdaptivePolicy,
        SetTextAreaSelectedBackgroundColor, ResetTextAreaSelectedBackgroundColor, SetTextAreaCaretStyle,
        ResetTextAreaCaretStyle, SetTextAreaTextOverflow, ResetTextAreaTextOverflow, SetTextAreaTextIndent,
        ResetTextAreaTextIndent, SetTextAreaLineSpacing, ResetTextAreaLineSpacing, GetTextAreaSelectionMenuHidden,
        GetTextAreaAdaptMinFontSize, GetTextAreaAdaptMaxFontSize, GetTextAreaLineHeight, GetgetTextAreaMaxLines,
        SetTextAreaPadding, ResetTextAreaPadding, GetTextAreaFontFeature,
        SetTextAreaOnChange, ResetTextAreaOnChange,
        SetTextAreaEnterKeyType, ResetTextAreaEnterKeyType, SetTextAreaInputFilter, ResetTextAreaInputFilter,
        SetTextAreaOnTextSelectionChange, ResetTextAreaOnTextSelectionChange,
        SetTextAreaOnContentScroll, ResetTextAreaOnContentScroll,
        SetTextAreaOnEditChange, ResetTextAreaOnEditChange, SetTextAreaOnCopy, ResetTextAreaOnCopy,
        SetTextAreaOnCut, ResetTextAreaOnCut, SetTextAreaOnPaste, ResetTextAreaOnPaste,
        SetTextAreaLineBreakStrategy, ResetTextAreaLineBreakStrategy,
        SetTextAreaOnSubmitWithEvent, ResetTextAreaOnSubmitWithEvent,
        SetTextAreaContentType, ResetTextAreaContentType, SetTextAreaEnableAutoFill, ResetTextAreaEnableAutoFill,
        SetTextAreaBorder, ResetTextAreaBorder, SetTextAreaBorderWidth, ResetTextAreaBorderWidth,
        SetTextAreaBorderColor, ResetTextAreaBorderColor, SetTextAreaBorderStyle, ResetTextAreaBorderStyle,
        SetTextAreaBorderRadius, ResetTextAreaBorderRadius, SetTextAreaMargin, ResetTextAreaMargin,
        GetTextAreaMargin, SetTextAreaCaret,
        SetTextAreaOnWillInsert, ResetTextAreaOnWillInsert,
        SetTextAreaOnDidInsert, ResetTextAreaOnDidInsert,
        SetTextAreaOnWillDelete, ResetTextAreaOnWillDelete,
        SetTextAreaOnDidDelete, ResetTextAreaOnDidDelete,
        SetTextAreaEnablePreviewText, ResetTextAreaEnablePreviewText, GetTextAreaPadding };
    return &modifier;
}

void SetOnTextAreaChange(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto onChange = [node, extraParam](const std::u16string& str, PreviewText&) {
        ArkUINodeEvent event;
        std::string utf8Str = UtfUtils::Str16ToStr8(str);
        event.kind = TEXT_INPUT;
        event.extraParam = reinterpret_cast<intptr_t>(extraParam);
        event.textInputEvent.subKind = ON_TEXTAREA_CHANGE;
        event.textInputEvent.nativeStringPtr = reinterpret_cast<intptr_t>(utf8Str.c_str());
        SendArkUISyncEvent(&event);
    };
    TextFieldModelNG::SetOnChange(frameNode, std::move(onChange));
}

void SetOnTextAreaPaste(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto onPaste = [node, extraParam](const std::u16string& str, NG::TextCommonEvent& commonEvent) {
        ArkUINodeEvent event;
        std::string utf8Str = UtfUtils::Str16ToStr8(str);
        event.kind = TEXT_INPUT;
        event.extraParam = reinterpret_cast<intptr_t>(extraParam);
        event.textInputEvent.subKind = ON_TEXTAREA_PASTE;
        event.textInputEvent.nativeStringPtr = reinterpret_cast<intptr_t>(utf8Str.c_str());
        SendArkUISyncEvent(&event);
    };
    TextFieldModelNG::SetOnPasteWithEvent(frameNode, std::move(onPaste));
}

void SetOnTextAreaSelectionChange(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto onSelectionChange = [node, extraParam](int start, int end) {
        ArkUINodeEvent event;
        event.kind = COMPONENT_ASYNC_EVENT;
        event.extraParam = reinterpret_cast<intptr_t>(extraParam);
        event.componentAsyncEvent.subKind = ON_TEXTAREA_TEXT_SELECTION_CHANGE;
        event.componentAsyncEvent.data[0].i32 = static_cast<int>(start);
        event.componentAsyncEvent.data[1].i32 = static_cast<int>(end);
        SendArkUISyncEvent(&event);
    };
    TextFieldModelNG::SetOnTextSelectionChange(frameNode, std::move(onSelectionChange));
}

void SetOnTextAreaEditChange(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto onChange = [node, extraParam](bool isEditing) {
        ArkUINodeEvent event;
        event.kind = COMPONENT_ASYNC_EVENT;
        event.extraParam = reinterpret_cast<intptr_t>(extraParam);
        event.componentAsyncEvent.subKind = ON_TEXTAREA_EDIT_CHANGE;
        event.componentAsyncEvent.data[0].i32 = static_cast<int32_t>(isEditing);
        SendArkUISyncEvent(&event);
    };
    TextFieldModelNG::SetOnEditChanged(frameNode, std::move(onChange));
}

void SetOnTextAreaContentSizeChange(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto onChange = [node, extraParam](float width, float height) {
        ArkUINodeEvent event;
        event.kind = COMPONENT_ASYNC_EVENT;
        event.extraParam = reinterpret_cast<intptr_t>(extraParam);
        event.componentAsyncEvent.subKind = ON_TEXTAREA_CONTENT_SIZE_CHANGE;
        bool usePx = NodeModel::UsePXUnit(reinterpret_cast<ArkUI_Node*>(extraParam));
        double density = usePx ? 1 : PipelineBase::GetCurrentDensity();
        //0 width
        event.componentAsyncEvent.data[0].f32 = NearEqual(density, 0.0) ? 0.0f : width / density;
        //1 height
        event.componentAsyncEvent.data[1].f32 = NearEqual(density, 0.0) ? 0.0f : height / density;
        SendArkUISyncEvent(&event);
    };
    TextFieldModelNG::SetOnContentSizeChange(frameNode, std::move(onChange));
}

void SetOnTextAreaInputFilterError(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto onInputFilterError = [node, extraParam](const std::u16string& str) {
        ArkUINodeEvent event;
        std::string utf8Str = UtfUtils::Str16ToStr8(str);
        event.kind = TEXT_INPUT;
        event.extraParam = reinterpret_cast<intptr_t>(extraParam);
        event.textInputEvent.subKind = ON_TEXT_AREA_INPUT_FILTER_ERROR;
        event.textInputEvent.nativeStringPtr = reinterpret_cast<intptr_t>(utf8Str.c_str());
        SendArkUISyncEvent(&event);
    };
    TextFieldModelNG::SetInputFilterError(frameNode, std::move(onInputFilterError));
}

void SetTextAreaOnTextContentScroll(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto onScroll = [node, extraParam](float totalOffsetX, float totalOffsetY) {
        ArkUINodeEvent event;
        event.kind = COMPONENT_ASYNC_EVENT;
        event.extraParam = reinterpret_cast<intptr_t>(extraParam);
        event.componentAsyncEvent.subKind = ON_TEXT_AREA_CONTENT_SCROLL;
        event.componentAsyncEvent.data[0].f32 = totalOffsetX;
        event.componentAsyncEvent.data[1].f32 = totalOffsetY;
        SendArkUISyncEvent(&event);
    };
    TextFieldModelNG::SetOnContentScroll(frameNode, std::move(onScroll));
}

void SetTextAreaOnSubmit(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto onEvent = [node, extraParam](int32_t value, NG::TextFieldCommonEvent& commonEvent) {
        ArkUINodeEvent event;
        event.kind = COMPONENT_ASYNC_EVENT;
        event.extraParam = reinterpret_cast<intptr_t>(extraParam);
        event.componentAsyncEvent.subKind = ON_TEXTAREA_ON_SUBMIT;
        event.componentAsyncEvent.data[0].i32 = value;
        SendArkUISyncEvent(&event);
    };
    TextFieldModelNG::SetOnSubmit(frameNode, std::move(onEvent));
}

void SetTextAreaOnWillInsertValue(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::function<bool(const InsertValueInfo&)> onWillInsert = [node, extraParam](
        const InsertValueInfo& Info) -> bool {
        ArkUINodeEvent event;
        std::string insertValueUtf8 = UtfUtils::Str16ToStr8(Info.insertValue);
        event.kind = MIXED_EVENT;
        event.extraParam = reinterpret_cast<intptr_t>(extraParam);
        event.mixedEvent.subKind = ON_TEXT_AREA_WILL_INSERT;
        event.mixedEvent.numberData[0].f32 = Info.insertOffset;
        event.mixedEvent.numberDataLength = 1;
        event.mixedEvent.stringPtrData[0] = reinterpret_cast<intptr_t>(insertValueUtf8.c_str());
        event.mixedEvent.stringPtrDataLength = 1;
        SendArkUISyncEvent(&event);
        return event.mixedEvent.numberReturnData[0].i32;
    };
    TextFieldModelNG::SetOnWillInsertValueEvent(frameNode, std::move(onWillInsert));
}

void SetTextAreaOnDidInsertValue(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto onDidInsert = [node, extraParam](const InsertValueInfo& Info) {
        ArkUINodeEvent event;
        std::string insertValueUtf8 = UtfUtils::Str16ToStr8(Info.insertValue);
        event.kind = MIXED_EVENT;
        event.extraParam = reinterpret_cast<intptr_t>(extraParam);
        event.mixedEvent.subKind = ON_TEXT_AREA_DID_INSERT;
        event.mixedEvent.numberData[0].f32 = Info.insertOffset;
        event.mixedEvent.numberDataLength = 1;
        event.mixedEvent.stringPtrData[0] = reinterpret_cast<intptr_t>(insertValueUtf8.c_str());
        event.mixedEvent.stringPtrDataLength = 1;
        SendArkUISyncEvent(&event);
    };
    TextFieldModelNG::SetOnDidInsertValueEvent(frameNode, std::move(onDidInsert));
}

void SetTextAreaOnWillDeleteValue(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto onWillDelete = [node, extraParam](const DeleteValueInfo& Info) -> bool {
        ArkUINodeEvent event;
        std::string deleteValueUtf8 = UtfUtils::Str16ToStr8(Info.deleteValue);
        event.kind = MIXED_EVENT;
        event.extraParam = reinterpret_cast<intptr_t>(extraParam);
        event.mixedEvent.subKind = ON_TEXT_AREA_WILL_DELETE;
        event.mixedEvent.numberData[0].f32 = Info.deleteOffset;
        event.mixedEvent.numberData[1].i32 = static_cast<int32_t>(Info.direction);
        event.mixedEvent.numberDataLength = 2;
        event.mixedEvent.stringPtrData[0] = reinterpret_cast<intptr_t>(deleteValueUtf8.c_str());
        event.mixedEvent.stringPtrDataLength = 1;
        SendArkUISyncEvent(&event);
        return event.mixedEvent.numberReturnData[0].i32;
    };
    TextFieldModelNG::SetOnWillDeleteEvent(frameNode, std::move(onWillDelete));
}

void SetTextAreaOnDidDeleteValue(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto onDidDelete = [node, extraParam](const DeleteValueInfo& Info) {
        ArkUINodeEvent event;
        std::string deleteValueUtf8 = UtfUtils::Str16ToStr8(Info.deleteValue);
        event.kind = MIXED_EVENT;
        event.extraParam = reinterpret_cast<intptr_t>(extraParam);
        event.mixedEvent.subKind = ON_TEXT_AREA_DID_DELETE;
        event.mixedEvent.numberData[0].f32 = Info.deleteOffset;
        event.mixedEvent.numberData[1].i32 = static_cast<int32_t>(Info.direction);
        event.mixedEvent.numberDataLength = 2;
        event.mixedEvent.stringPtrData[0] = reinterpret_cast<intptr_t>(deleteValueUtf8.c_str());
        event.mixedEvent.stringPtrDataLength = 1;
        SendArkUISyncEvent(&event);
    };
    TextFieldModelNG::SetOnDidDeleteEvent(frameNode, std::move(onDidDelete));
}

void ResetOnTextAreaChange(ArkUINodeHandle node)
{
    GetTextAreaModifier()->resetTextAreaOnChange(node);
}
void ResetOnTextAreaPaste(ArkUINodeHandle node)
{
    GetTextAreaModifier()->resetTextAreaOnPaste(node);
}
void ResetOnTextAreaSelectionChange(ArkUINodeHandle node)
{
    GetTextAreaModifier()->resetTextAreaOnTextSelectionChange(node);
}
void ResetOnTextAreaEditChange(ArkUINodeHandle node)
{
    GetTextAreaModifier()->resetTextAreaOnEditChange(node);
}
void ResetOnTextAreaContentSizeChange(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::SetOnContentSizeChange(frameNode, nullptr);
}
void ResetOnTextAreaInputFilterError(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::SetInputFilterError(frameNode, nullptr);
}
void ResetTextAreaOnTextContentScroll(ArkUINodeHandle node)
{
    GetTextAreaModifier()->resetTextAreaOnContentScroll(node);
}
void ResetTextAreaOnSubmit(ArkUINodeHandle node)
{
    GetTextAreaModifier()->resetTextAreaOnSubmitWithEvent(node);
}
} // namespace NodeModifier
} // namespace OHOS::Ace::NG
