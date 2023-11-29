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
#include "bridge/declarative_frontend/engine/jsi/components/arkts_native_text_input_modifier.h"

#include "base/geometry/dimension.h"
#include "core/components/common/layout/constants.h"
#include "core/components/text_field/textfield_theme.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/text_field/text_field_model_ng.h"
#include "core/pipeline/base/element_register.h"
#include "bridge/common/utils/utils.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components/common/properties/alignment.h"
#include "core/components/text_field/textfield_theme.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"

namespace OHOS::Ace::NG {
const uint32_t MAX_LINES = 3;
constexpr uint32_t DEFAULT_CARET_COLOR = 0x007DFF;
static constexpr uint32_t THEME_TEXTFIELD_PLACEHOLDER_COLOR = 0x99000000;
constexpr uint32_t DEFAULT_CARE_POSITION = 0;
constexpr CopyOptions DEFAULT_TEXT_INPUT_COPY_OPTION = CopyOptions::Local;
constexpr bool DEFAULT_SHOW_PASSWORD_ICON_VALUE = true;
constexpr TextAlign DAFAULT_TEXT_ALIGN_VALUE = TextAlign::START;
constexpr InputStyle DEFAULT_INPUT_STYLE = InputStyle::DEFAULT;
constexpr bool DEFAULT_SELECTION_MENU_HIDDEN = false;
constexpr bool DEFAULT_SHOW_UNDER_LINE = false;
constexpr bool DEFAULT_REQUEST_KEYBOARD_ON_FOCUS = true;
constexpr DisplayMode DEFAULT_BAR_STATE = DisplayMode::AUTO;
static constexpr Dimension THEME_TEXTFIELD_FONT_SIZE = 16.0_fp;
constexpr uint32_t THEME_TEXTFIELD_TEXT_SELECTED_COLOR = 0x33254FF7;
constexpr Dimension DEFAULT_FONT_SIZE = 16.0_fp;
constexpr FontWeight DEFAULT_FONT_WEIGHT = FontWeight::NORMAL;
constexpr Ace::FontStyle DEFAULT_FONT_STYLE = Ace::FontStyle::NORMAL;
const std::vector<std::string> DEFAULT_FONT_FAMILY = { "HarmonyOS Sans" };
constexpr Color DEFAULT_TEXT_COLOR = Color(0xe5000000);
constexpr Dimension DEFAULT_CARET_STYLE = 1.5_vp;

void SetTextInputCaretColor(NodeHandle node, const struct ArkUIResourceColorType *caretColor)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);

    Color color;
    if (caretColor->string != nullptr) {
        Color::ParseColorString(caretColor->string, color);
    } else {
        color = Color(ArkTSUtils::ColorAlphaAdapt(caretColor->number));
    }
    TextFieldModelNG::SetCaretColor(frameNode, color);
}

void ResetTextInputCaretColor(NodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::SetCaretColor(frameNode, Color(DEFAULT_CARET_COLOR));
}

void SetTextInputType(NodeHandle node, int32_t value)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::SetType(frameNode, static_cast<TextInputType>(value));
}

void ResetTextInputType(NodeHandle node)
{
    return;
}

void SetTextInputMaxLines(NodeHandle node, int32_t value)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);

    if (value <= 0) {
        TextFieldModelNG::SetMaxLines(frameNode, MAX_LINES);
        return;
    }

    TextFieldModelNG::SetMaxLines(frameNode, value);
}

void ResetTextInputMaxLines(NodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::SetMaxLines(frameNode, MAX_LINES);
}

void SetTextInputPlaceholderColor(NodeHandle node, const struct ArkUIResourceColorType *placeholderColor)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);

    Color color;
    if (placeholderColor->string != nullptr) {
        Color::ParseColorString(placeholderColor->string, color);
    } else {
        color = Color(ArkTSUtils::ColorAlphaAdapt(placeholderColor->number));
    }

    TextFieldModelNG::SetPlaceholderColor(frameNode, color);
}

void ResetTextInputPlaceholderColor(NodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::SetPlaceholderColor(frameNode, Color(THEME_TEXTFIELD_PLACEHOLDER_COLOR));
}

void SetTextInputCaretPosition(NodeHandle node, int32_t caretPosition)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::SetCaretPosition(frameNode, caretPosition);
}

void ResetTextInputCaretPosition(NodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::SetCaretPosition(frameNode, DEFAULT_CARE_POSITION);
}

void SetTextInputCopyOption(NodeHandle node, int32_t copyOption)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::SetCopyOption(frameNode, static_cast<CopyOptions>(copyOption));
}

void ResetTextInputCopyOption(NodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::SetCopyOption(frameNode, DEFAULT_TEXT_INPUT_COPY_OPTION);
}

void SetTextInputShowPasswordIcon(NodeHandle node, uint32_t value)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::SetShowPasswordIcon(frameNode, static_cast<bool>(value));
}

void ResetTextInputShowPasswordIcon(NodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::SetShowPasswordIcon(frameNode, DEFAULT_SHOW_PASSWORD_ICON_VALUE);
}

void SetTextInputPasswordIcon(NodeHandle node, const char *onIconSrc, const char *offIconSrc)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    PasswordIcon passwordIcon;
    passwordIcon.showResult = onIconSrc;
    passwordIcon.hideResult = offIconSrc;
    TextFieldModelNG::SetPasswordIcon(frameNode, passwordIcon);
}

void ResetTextInputPasswordIcon(NodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    PasswordIcon passwordIcon;
    passwordIcon.showResult = "";
    passwordIcon.hideResult = "";
    TextFieldModelNG::SetPasswordIcon(frameNode, passwordIcon);
}

void SetTextInputTextAlign(NodeHandle node, int32_t value)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::SetTextAlign(frameNode, static_cast<TextAlign>(value));
}

void ResetTextInputTextAlign(NodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::SetTextAlign(frameNode, DAFAULT_TEXT_ALIGN_VALUE);
}

void SetTextInputStyle(NodeHandle node, int32_t style)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::SetInputStyle(frameNode, static_cast<InputStyle>(style));
}

void ResetTextInputStyle(NodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::SetInputStyle(frameNode, DEFAULT_INPUT_STYLE);
}

void SetTextInputSelectionMenuHidden(NodeHandle node, uint32_t menuHiddenValue)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::SetSelectionMenuHidden(frameNode, static_cast<bool>(menuHiddenValue));
}

void ResetTextInputSelectionMenuHidden(NodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::SetSelectionMenuHidden(frameNode, DEFAULT_SELECTION_MENU_HIDDEN);
}

void SetTextInputShowUnderline(NodeHandle node, uint32_t showUnderLine)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::SetShowUnderline(frameNode, static_cast<bool>(showUnderLine));
}

void ResetTextInputShowUnderline(NodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::SetShowUnderline(frameNode, DEFAULT_SHOW_UNDER_LINE);
}

void SetTextInputCaretStyle(NodeHandle node, const double number, const int8_t unit)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    std::optional<Dimension> caretStyle = Dimension(number, static_cast<DimensionUnit>(unit));
    TextFieldModelNG::SetCaretStyle(frameNode, { caretStyle });
}

void ResetTextInputCaretStyle(NodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CaretStyle caretStyle;
    caretStyle.caretWidth = DEFAULT_CARET_STYLE;
    TextFieldModelNG::SetCaretStyle(frameNode, caretStyle);
}

void SetTextInputEnableKeyboardOnFocus(NodeHandle node, uint32_t value)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::RequestKeyboardOnFocus(frameNode, static_cast<bool>(value));
}

void ResetTextInputEnableKeyboardOnFocus(NodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::RequestKeyboardOnFocus(frameNode, DEFAULT_REQUEST_KEYBOARD_ON_FOCUS);
}

void SetTextInputBarState(NodeHandle node, int32_t value)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::SetBarState(frameNode, static_cast<DisplayMode>(value));
}

void ResetTextInputBarState(NodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::SetBarState(frameNode, DEFAULT_BAR_STATE);
}

void SetTextInputEnterKeyType(NodeHandle node, int32_t value)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::SetEnterKeyType(frameNode, static_cast<TextInputAction>(value));
}

void ResetTextInputEnterKeyType(NodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::SetEnterKeyType(frameNode, TextInputAction::DONE);
}

void SetTextInputFontWeight(NodeHandle node, const char *fontWeight)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::SetFontWeight(frameNode, Framework::ConvertStrToFontWeight(fontWeight));
}

void ResetTextInputFontWeight(NodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::SetFontWeight(frameNode, FontWeight::NORMAL);
}

void SetTextInputFontSize(NodeHandle node, const struct ArkUILengthType *fontSizeStruct)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CalcDimension fontSize;

    if (fontSizeStruct->number == -1) {
        fontSize = THEME_TEXTFIELD_FONT_SIZE;
    } else if (fontSizeStruct->string != nullptr) {
        fontSize = StringUtils::StringToCalcDimension(std::string(fontSizeStruct->string), false, DimensionUnit::FP);
    } else {
        fontSize = CalcDimension(fontSizeStruct->number, DimensionUnit::VP);
    }

    TextFieldModelNG::SetFontSize(frameNode, fontSize);
}

void ResetTextInputFontSize(NodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::SetFontSize(frameNode, THEME_TEXTFIELD_FONT_SIZE);
}

void SetTextInputMaxLength(NodeHandle node, uint32_t value)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::SetMaxLength(frameNode, value);
}

void ResetTextInputMaxLength(NodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::ResetMaxLength(frameNode);
}

void SetTextInputSelectedBackgroundColor(NodeHandle node, const struct ArkUIResourceColorType *backgroundColor)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);

    Color color;
    if (backgroundColor->string != nullptr) {
        Color::ParseColorString(backgroundColor->string, color);
    } else {
        color = Color(ArkTSUtils::ColorAlphaAdapt(backgroundColor->number));
    }

    TextFieldModelNG::SetSelectedBackgroundColor(frameNode, color);
}

void ResetTextInputSelectedBackgroundColor(NodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::SetSelectedBackgroundColor(frameNode, Color(THEME_TEXTFIELD_TEXT_SELECTED_COLOR));
}

void SetTextInputShowError(NodeHandle node, const char *error, uint32_t visible)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::SetShowError(frameNode, std::string(error), static_cast<bool>(visible));
}

void ResetTextInputShowError(NodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::SetShowError(frameNode, std::string(""), false);
}

void SetTextInputPlaceholderFont(NodeHandle node, const struct ArkUILengthType *size, int32_t weight,
    const char *family, int32_t style)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    Font font;
    CalcDimension fontSize;
    if (size->string != nullptr) {
        fontSize = StringUtils::StringToCalcDimension(size->string, true, DimensionUnit::FP);
    } else if (size->number >= 0) {
        fontSize = CalcDimension(size->number, DimensionUnit::FP);
    } else {
        fontSize = DEFAULT_FONT_SIZE;
    }
    if (fontSize.Unit() == DimensionUnit::PERCENT) {
        fontSize = DEFAULT_FONT_SIZE;
    }
    font.fontSize = fontSize;
    if (weight >= 0) {
        font.fontWeight = static_cast<FontWeight>(weight);
    }
    if (family != nullptr) {
        font.fontFamilies = Framework::ConvertStrToFontFamilies(family);
    }
    if (style >= 0) {
        font.fontStyle = static_cast<Ace::FontStyle>(style);
    }
    TextFieldModelNG::SetPlaceholderFont(frameNode, font);
}

void ResetTextInputPlaceholderFont(NodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    Font font;
    font.fontSize = DEFAULT_FONT_SIZE;
    font.fontWeight = DEFAULT_FONT_WEIGHT;
    font.fontStyle = DEFAULT_FONT_STYLE;
    TextFieldModelNG::SetPlaceholderFont(frameNode, font);
}

void SetTextInputFontColor(NodeHandle node, const struct ArkUIResourceColorType *fontColor)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);

    Color color;
    if (fontColor->string != nullptr) {
        Color::ParseColorString(fontColor->string, color);
    } else {
        color = Color(ArkTSUtils::ColorAlphaAdapt(fontColor->number));
    }

    TextFieldModelNG::SetTextColor(frameNode, Color(color));
}

void ResetTextInputFontColor(NodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::SetTextColor(frameNode, DEFAULT_TEXT_COLOR);
}

void SetTextInputFontStyle(NodeHandle node, uint32_t value)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::SetFontStyle(frameNode, static_cast<Ace::FontStyle>(value));
}

void ResetTextInputFontStyle(NodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::SetFontStyle(frameNode, DEFAULT_FONT_STYLE);
}

void SetTextInputFontFamily(NodeHandle node, const char *value)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    std::vector<std::string> families = Framework::ConvertStrToFontFamilies(value);
    TextFieldModelNG::SetFontFamily(frameNode, families);
}

void ResetTextInputFontFamily(NodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::SetFontFamily(frameNode, DEFAULT_FONT_FAMILY);
}
ArkUITextInputModifierAPI GetTextInputModifier()
{
    static const ArkUITextInputModifierAPI modifier = { SetTextInputCaretColor,
                                                        ResetTextInputCaretColor,
                                                        SetTextInputType,
                                                        ResetTextInputType,
                                                        SetTextInputMaxLines,
                                                        ResetTextInputMaxLines,
                                                        SetTextInputPlaceholderColor,
                                                        ResetTextInputPlaceholderColor,
                                                        SetTextInputCaretPosition,
                                                        ResetTextInputCaretPosition,
                                                        SetTextInputCopyOption,
                                                        ResetTextInputCopyOption,
                                                        SetTextInputShowPasswordIcon,
                                                        ResetTextInputShowPasswordIcon,
                                                        SetTextInputPasswordIcon,
                                                        ResetTextInputPasswordIcon,
                                                        SetTextInputTextAlign,
                                                        ResetTextInputTextAlign,
                                                        SetTextInputStyle,
                                                        ResetTextInputStyle,
                                                        SetTextInputSelectionMenuHidden,
                                                        ResetTextInputSelectionMenuHidden,
                                                        SetTextInputShowUnderline,
                                                        ResetTextInputShowUnderline,
                                                        SetTextInputCaretStyle,
                                                        ResetTextInputCaretStyle,
                                                        SetTextInputEnableKeyboardOnFocus,
                                                        ResetTextInputEnableKeyboardOnFocus,
                                                        SetTextInputBarState,
                                                        ResetTextInputBarState,
                                                        SetTextInputEnterKeyType,
                                                        ResetTextInputEnterKeyType,
                                                        SetTextInputFontWeight,
                                                        ResetTextInputFontWeight,
                                                        SetTextInputFontSize,
                                                        ResetTextInputFontSize,
                                                        SetTextInputMaxLength,
                                                        ResetTextInputMaxLength,
                                                        SetTextInputSelectedBackgroundColor,
                                                        ResetTextInputSelectedBackgroundColor,
                                                        SetTextInputShowError,
                                                        ResetTextInputShowError,
                                                        SetTextInputPlaceholderFont,
                                                        ResetTextInputPlaceholderFont,
                                                        SetTextInputFontColor,
                                                        ResetTextInputFontColor,
                                                        SetTextInputFontStyle,
                                                        ResetTextInputFontStyle,
                                                        SetTextInputFontFamily,
                                                        ResetTextInputFontFamily };

    return modifier;
}
}