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
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/alignment.h"
#include "core/components/common/properties/text_style.h"
#include "core/components/text_field/textfield_theme.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/pattern/text_field/text_field_model.h"
#include "core/components_ng/pattern/text_field/text_field_model_ng.h"
#include "core/interfaces/arkoala/arkoala_api.h"
#include "core/pipeline/base/element_register.h"
#include "core/interfaces/native/node/node_api.h"
#include "core/components/common/properties/text_style_parser.h"

namespace OHOS::Ace::NG {
namespace {
constexpr InputStyle DEFAULT_TEXT_AREA_STYLE = InputStyle::DEFAULT;
constexpr bool DEFAULT_SELECTION_MENU_HIDDEN = false;
constexpr uint32_t DEFAULT_MAX_VIEW_LINE = 3;
constexpr CopyOptions DEFAULT_COPY_OPTIONS_VALUE = CopyOptions::Local;
constexpr FontWeight DEFAULT_FONT_WEIGHT = FontWeight::NORMAL;
constexpr Ace::FontStyle DEFAULT_FONT_STYLE = Ace::FontStyle::NORMAL;
constexpr DisplayMode DEFAULT_BAR_STATE_VALUE = DisplayMode::AUTO;
constexpr bool DEFAULT_KEY_BOARD_VALUE = true;
constexpr char DEFAULT_FONT_FAMILY[] = "HarmonyOS Sans";
const uint32_t ERROR_UINT_CODE = -1;
const int32_t ERROR_INT_CODE = -1;
constexpr TextDecoration DEFAULT_TEXT_DECORATION = TextDecoration::NONE;
constexpr Color DEFAULT_DECORATION_COLOR = Color(0xff000000);
constexpr TextDecorationStyle DEFAULT_DECORATION_STYLE = TextDecorationStyle::SOLID;
std::string g_strValue;

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
    auto pipeline = PipelineBase::GetCurrentContext();
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
        auto pipeline = PipelineBase::GetCurrentContext();
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
        auto pipeline = PipelineBase::GetCurrentContext();
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
    auto pipeline = PipelineBase::GetCurrentContext();
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
    auto pipeline = PipelineBase::GetCurrentContextSafely();
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
    auto pipeline = PipelineBase::GetCurrentContextSafely();
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
    auto pipeline = PipelineBase::GetCurrentContext();
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
    TextFieldModelNG::SetTextFieldPlaceHolder(frameNode, placeholderStr);
}

void SetTextAreaTextString(ArkUINodeHandle node, ArkUI_CharPtr value)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    std::string textStr(value);
    TextFieldModelNG::SetTextFieldText(frameNode, textStr);
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
    g_strValue = TextFieldModelNG::GetPlaceholderText(frameNode);
    return g_strValue.c_str();
}

ArkUI_CharPtr GetTextAreaText(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_RETURN(frameNode, "");
    g_strValue = TextFieldModelNG::GetTextFieldText(frameNode);
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
        font->fontSize = value.fontSize.value().Value();
    }
    if (value.fontWeight.has_value()) {
        font->fontWeight = static_cast<ArkUI_Int32>(value.fontWeight.value());
    }
    if (!value.fontFamilies.empty()) {
        std::string families;
        int index = 0;
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
    auto pipeline = PipelineBase::GetCurrentContextSafely();
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
    TextFieldModelNG::SetType(frameNode, static_cast<Ace::TextInputType>(type));
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
        ResetTextAreaShowCounterOptions, GetTextAreaShowCounterOptions, SetTextAreaDecoration,
        ResetTextAreaDecoration, SetTextAreaLetterSpacing, ResetTextAreaLetterSpacing, SetTextAreaLineHeight,
        ResetTextAreaLineHeight, SetTextAreaFontFeature, ResetTextAreaFontFeature };
    return &modifier;
}

void SetOnTextAreaChange(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto onChange = [node, extraParam](const std::string& str) {
        ArkUINodeEvent event;
        event.kind = TEXT_INPUT;
        event.extraParam = reinterpret_cast<intptr_t>(extraParam);
        event.textInputEvent.subKind = ON_TEXTAREA_CHANGE;
        event.textInputEvent.nativeStringPtr = reinterpret_cast<intptr_t>(str.c_str());
        SendArkUIAsyncEvent(&event);
    };
    TextFieldModelNG::SetOnChange(frameNode, std::move(onChange));
}

void SetOnTextAreaPaste(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto onPaste = [node, extraParam](const std::string& str, NG::TextCommonEvent& commonEvent) {
        ArkUINodeEvent event;
        event.kind = TEXT_INPUT;
        event.extraParam = reinterpret_cast<intptr_t>(extraParam);
        event.textInputEvent.subKind = ON_TEXTAREA_PASTE;
        event.textInputEvent.nativeStringPtr = reinterpret_cast<intptr_t>(str.c_str());
        SendArkUIAsyncEvent(&event);
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
        SendArkUIAsyncEvent(&event);
    };
    TextFieldModelNG::SetOnTextSelectionChange(frameNode, std::move(onSelectionChange));
}
} // namespace NodeModifier
} // namespace OHOS::Ace::NG
