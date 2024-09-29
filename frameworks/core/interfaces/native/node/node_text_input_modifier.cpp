/*
 * Copyright (c) 2023-2024 Huawei Device Co., Ltd.
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
#include "core/interfaces/native/node/node_text_input_modifier.h"

#include "core/components/text_field/textfield_theme.h"
#include "core/components_ng/pattern/text_field/text_field_model_ng.h"
#include "bridge/common/utils/utils.h"
#include "core/components/common/properties/text_style_parser.h"
#include "interfaces/native/node/node_model.h"

namespace OHOS::Ace::NG {
namespace {
const uint32_t MAX_LINES = 3;
constexpr uint32_t DEFAULT_CARET_COLOR = 0xFF007DFF;
constexpr uint32_t DEFAULT_CARE_POSITION = 0;
constexpr CopyOptions DEFAULT_TEXT_INPUT_COPY_OPTION = CopyOptions::Local;
constexpr bool DEFAULT_SHOW_PASSWORD_ICON_VALUE = true;
constexpr TextAlign DEFAULT_TEXT_ALIGN_VALUE = TextAlign::START;
constexpr InputStyle DEFAULT_INPUT_STYLE = InputStyle::DEFAULT;
constexpr bool DEFAULT_SELECTION_MENU_HIDDEN = false;
constexpr bool DEFAULT_SHOW_UNDER_LINE = false;
constexpr bool DEFAULT_ENABLE_AUTO_FILL = true;
constexpr bool DEFAULT_REQUEST_KEYBOARD_ON_FOCUS = true;
constexpr DisplayMode DEFAULT_BAR_STATE = DisplayMode::AUTO;
constexpr FontWeight DEFAULT_FONT_WEIGHT = FontWeight::NORMAL;
constexpr Ace::FontStyle DEFAULT_FONT_STYLE = Ace::FontStyle::NORMAL;
constexpr int16_t DEFAULT_ALPHA = 255;
constexpr double DEFAULT_OPACITY = 0.2;
const std::vector<std::string> DEFAULT_FONT_FAMILY = { "HarmonyOS Sans" };
const std::vector<TextAlign> TEXT_ALIGNS = { TextAlign::START, TextAlign::CENTER, TextAlign::END, TextAlign::JUSTIFY };
const uint32_t ERROR_UINT_CODE = -1;
const float ERROR_FLOAT_CODE = -1.0f;
const int32_t ERROR_INT_CODE = -1;
constexpr int CALL_ARG_0 = 0;
constexpr int CALL_ARG_1 = 1;
constexpr int CALL_ARG_2 = 2;
constexpr int CALL_ARG_3 = 3;
constexpr int32_t DEFAULT_GROUP_UNDERLINE_COLOR_VALUES_COUNT = 4;
constexpr int32_t DEFAULT_MARGIN_VALUES_COUNT = 4;
constexpr TextDecoration DEFAULT_TEXT_DECORATION = TextDecoration::NONE;
constexpr Color DEFAULT_DECORATION_COLOR = Color(0xff000000);
constexpr TextDecorationStyle DEFAULT_DECORATION_STYLE = TextDecorationStyle::SOLID;
constexpr bool DEFAULT_SELECT_ALL = false;
constexpr bool DEFAULT_ENABLE_PREVIEW_TEXT_VALUE = true;
std::string g_strValue;

void SetTextInputCaretColor(ArkUINodeHandle node, ArkUI_Uint32 color)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::SetCaretColor(frameNode, Color(color));
}

void ResetTextInputCaretColor(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::SetCaretColor(frameNode, Color(DEFAULT_CARET_COLOR));
}

void SetTextInputType(ArkUINodeHandle node, ArkUI_Int32 value)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::SetType(frameNode, CastToTextInputType(value));
}

void ResetTextInputType(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::SetType(frameNode, TextInputType::UNSPECIFIED);
    return;
}

void SetTextInputMaxLines(ArkUINodeHandle node, ArkUI_Int32 value)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    if (value <= 0) {
        TextFieldModelNG::SetMaxViewLines(frameNode, MAX_LINES);
        return;
    }

    TextFieldModelNG::SetMaxViewLines(frameNode, value);
}

void ResetTextInputMaxLines(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::SetMaxViewLines(frameNode, MAX_LINES);
}

void SetTextInputPlaceholderColor(ArkUINodeHandle node, ArkUI_Uint32 color)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::SetPlaceholderColor(frameNode, Color(color));
}

void ResetTextInputPlaceholderColor(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto pipeline = frameNode->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetThemeManager()->GetTheme<TextFieldTheme>();
    CHECK_NULL_VOID(theme);
    TextFieldModelNG::SetPlaceholderColor(frameNode, theme->GetPlaceholderColor());
}

void SetTextInputCaretPosition(ArkUINodeHandle node, ArkUI_Int32 caretPosition)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::SetCaretPosition(frameNode, caretPosition);
}

void ResetTextInputCaretPosition(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::SetCaretPosition(frameNode, DEFAULT_CARE_POSITION);
}

void SetTextInputCopyOption(ArkUINodeHandle node, ArkUI_Int32 copyOption)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::SetCopyOption(frameNode, static_cast<CopyOptions>(copyOption));
}

void ResetTextInputCopyOption(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::SetCopyOption(frameNode, DEFAULT_TEXT_INPUT_COPY_OPTION);
}

void SetTextInputShowPasswordIcon(ArkUINodeHandle node, ArkUI_Uint32 value)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::SetShowPasswordIcon(frameNode, static_cast<bool>(value));
}

void ResetTextInputShowPasswordIcon(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::SetShowPasswordIcon(frameNode, DEFAULT_SHOW_PASSWORD_ICON_VALUE);
}

void SetTextInputPasswordIcon(ArkUINodeHandle node, const struct ArkUIPasswordIconType* value)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    PasswordIcon passwordIcon;
    if (value->showResult != nullptr && std::string(value->showResult) != "") {
        passwordIcon.showResult = value->showResult;
    } else {
        if (value->showBundleName != nullptr && std::string(value->showBundleName) != "") {
            passwordIcon.showBundleName = value->showBundleName;
        }
        if (value->showModuleName != nullptr && std::string(value->showModuleName) != "") {
            passwordIcon.showModuleName = value->showModuleName;
        }
    }
    if (value->hideResult != nullptr && std::string(value->hideResult) != "") {
        passwordIcon.hideResult = value->hideResult;
    } else {
        if (value->hideBundleName != nullptr && std::string(value->hideBundleName) != "") {
            passwordIcon.hideBundleName = value->hideBundleName;
        }
        if (value->hideModuleName != nullptr && std::string(value->hideModuleName) != "") {
            passwordIcon.hideModuleName = value->hideModuleName;
        }
    }
    TextFieldModelNG::SetPasswordIcon(frameNode, passwordIcon);
}

void ResetTextInputPasswordIcon(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    PasswordIcon passwordIcon;
    passwordIcon.showResult = "";
    passwordIcon.hideResult = "";
    TextFieldModelNG::SetPasswordIcon(frameNode, passwordIcon);
}

void SetTextInputTextAlign(ArkUINodeHandle node, ArkUI_Int32 value)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    if (value >= 0 && value < static_cast<int32_t>(TEXT_ALIGNS.size())) {
        TextFieldModelNG::SetTextAlign(frameNode, TEXT_ALIGNS[value]);
    } else {
        TextFieldModelNG::SetTextAlign(frameNode, DEFAULT_TEXT_ALIGN_VALUE);
    }
}

void ResetTextInputTextAlign(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::SetTextAlign(frameNode, DEFAULT_TEXT_ALIGN_VALUE);
}

void SetTextInputStyle(ArkUINodeHandle node, ArkUI_Int32 style)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::SetInputStyle(frameNode, static_cast<InputStyle>(style));
}

ArkUI_Int32 GetTextInputStyle(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_RETURN(frameNode, 0);
    return static_cast<ArkUI_Int32>(TextFieldModelNG::GetInputStyle(frameNode));
}

void ResetTextInputStyle(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::SetInputStyle(frameNode, DEFAULT_INPUT_STYLE);
}

void GetTextInputContentRect(ArkUINodeHandle node, ArkUI_Float32 (*values)[4])
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto textFieldController = TextFieldModelNG::GetOrCreateController(frameNode);
    auto rect = textFieldController->GetTextContentRect();
    (*values)[CALL_ARG_0] = rect.Left();
    (*values)[CALL_ARG_1] = rect.Top();
    (*values)[CALL_ARG_2] = rect.Width();
    (*values)[CALL_ARG_3] = rect.Height();
}

ArkUI_Int32 GetTextInputContentLinesNum(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_RETURN(frameNode, 0);
    auto textFieldController = TextFieldModelNG::GetOrCreateController(frameNode);
    return static_cast<ArkUI_Int32>(textFieldController->GetTextContentLinesNum());
}

void SetTextInputSelectionMenuHidden(ArkUINodeHandle node, ArkUI_Uint32 menuHiddenValue)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::SetSelectionMenuHidden(frameNode, static_cast<bool>(menuHiddenValue));
}

void ResetTextInputSelectionMenuHidden(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::SetSelectionMenuHidden(frameNode, DEFAULT_SELECTION_MENU_HIDDEN);
}

void SetTextInputShowUnderline(ArkUINodeHandle node, ArkUI_Uint32 showUnderLine)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::SetShowUnderline(frameNode, static_cast<bool>(showUnderLine));
}

void ResetTextInputShowUnderline(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::SetShowUnderline(frameNode, DEFAULT_SHOW_UNDER_LINE);
}

void SetTextInputPasswordRules(ArkUINodeHandle node, ArkUI_CharPtr passwordRules)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    std::string strValue = passwordRules;
    TextFieldModelNG::SetPasswordRules(frameNode, strValue);
}

ArkUI_CharPtr GetTextInputPasswordRules(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_RETURN(frameNode, "");
    g_strValue = TextFieldModelNG::GetPasswordRules(frameNode);
    return g_strValue.c_str();
}

void ResetTextInputPasswordRules(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::SetPasswordRules(frameNode, "");
}

void SetTextInputEnableAutoFill(ArkUINodeHandle node, ArkUI_Uint32 enableAutoFill)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::SetEnableAutoFill(frameNode, static_cast<bool>(enableAutoFill));
}

ArkUI_Int32 GetTextInputEnableAutoFill(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_INT_CODE);
    return static_cast<ArkUI_Int32>(TextFieldModelNG::GetEnableAutoFill(frameNode));
}

void ResetTextInputEnableAutoFill(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::SetEnableAutoFill(frameNode, DEFAULT_ENABLE_AUTO_FILL);
}

ArkUI_Int32 GetTextInputSelectAll(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_INT_CODE);
    return static_cast<ArkUI_Int32>(TextFieldModelNG::GetSelectAllValue(frameNode));
}

void SetTextInputInputFilter(ArkUINodeHandle node, ArkUI_CharPtr inputFilter)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::SetInputFilter(frameNode, inputFilter);
}

ArkUI_CharPtr GetTextInputInputFilter(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_RETURN(frameNode, "");
    g_strValue = TextFieldModelNG::GetInputFilter(frameNode);
    return g_strValue.c_str();
}

void ResetTextInputInputFilter(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::SetInputFilter(frameNode, "");
}

ArkUI_Int32 GetTextInputCaretIndex(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_INT_CODE);
    auto textFieldController = TextFieldModelNG::GetOrCreateController(frameNode);
    return textFieldController->GetCaretIndex();
}

void GetTextInputCaretOffset(ArkUINodeHandle node, ArkUI_Float32 (*values)[2])
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto textFieldController = TextFieldModelNG::GetOrCreateController(frameNode);
    auto offset = textFieldController->GetCaretPosition();
    (*values)[0] = offset.GetX();
    (*values)[1] = offset.GetY();
}

void SetTextInputContentType(ArkUINodeHandle node, ArkUI_Uint32 contentType)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    if (contentType < 0 || contentType > static_cast<ArkUI_Uint32>(TextContentType::END)) {
        contentType = -1;
    }
    TextFieldModelNG::SetContentType(frameNode, static_cast<NG::TextContentType>(contentType));
}

ArkUI_Int32 GetTextInputContentType(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_INT_CODE);
    return static_cast<ArkUI_Int32>(TextFieldModelNG::GetContentType(frameNode));
}

void ResetTextInputContentType(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::SetContentType(frameNode, static_cast<NG::TextContentType>(TextContentType::UNSPECIFIED));
}

void SetTextInputCaretStyle(ArkUINodeHandle node, ArkUI_Float32 value, ArkUI_Int32 unit, ArkUI_Uint32 caretColor)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CaretStyle caretStyle;
    caretStyle.caretWidth = CalcDimension(value, (DimensionUnit)unit);
    TextFieldModelNG::SetCaretStyle(frameNode, caretStyle);
    TextFieldModelNG::SetCaretColor(frameNode, Color(caretColor));
}

void ResetTextInputCaretStyle(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);

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

void SetTextInputEnableKeyboardOnFocus(ArkUINodeHandle node, ArkUI_Uint32 value)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::RequestKeyboardOnFocus(frameNode, static_cast<bool>(value));
}

void ResetTextInputEnableKeyboardOnFocus(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::RequestKeyboardOnFocus(frameNode, DEFAULT_REQUEST_KEYBOARD_ON_FOCUS);
}

void SetTextInputBarState(ArkUINodeHandle node, ArkUI_Int32 value)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::SetBarState(frameNode, static_cast<DisplayMode>(value));
}

void ResetTextInputBarState(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::SetBarState(frameNode, DEFAULT_BAR_STATE);
}

void SetTextInputEnterKeyType(ArkUINodeHandle node, ArkUI_Int32 value)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::SetEnterKeyType(frameNode, static_cast<TextInputAction>(value));
}

void ResetTextInputEnterKeyType(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::SetEnterKeyType(frameNode, TextInputAction::DONE);
}

void SetTextInputFontWeightStr(ArkUINodeHandle node, ArkUI_CharPtr fontWeight)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::SetFontWeight(frameNode, Framework::ConvertStrToFontWeight(fontWeight));
}

void SetTextInputFontWeight(ArkUINodeHandle node, ArkUI_Int32 fontWeight)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::SetFontWeight(frameNode, static_cast<FontWeight>(fontWeight));
}

void ResetTextInputFontWeight(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::SetFontWeight(frameNode, FontWeight::NORMAL);
}

void SetTextInputFontSize(ArkUINodeHandle node, const struct ArkUILengthType *value)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CalcDimension fontSize;
    if (value->string != nullptr) {
        fontSize.SetCalcValue(value->string);
    } else {
        fontSize.SetValue(value->number);
    }
    fontSize.SetUnit(static_cast<DimensionUnit>(value->unit));
    TextFieldModelNG::SetFontSize(frameNode, fontSize);
}

void ResetTextInputFontSize(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto pipeline = frameNode->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetThemeManager()->GetTheme<TextFieldTheme>();
    CHECK_NULL_VOID(theme);
    TextFieldModelNG::SetFontSize(frameNode, theme->GetFontSize());
}

void SetTextInputMaxLength(ArkUINodeHandle node, ArkUI_Uint32 value)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::SetMaxLength(frameNode, value);
}

void ResetTextInputMaxLength(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::ResetMaxLength(frameNode);
}

void SetTextInputSelectedBackgroundColor(ArkUINodeHandle node, ArkUI_Uint32 color)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::SetSelectedBackgroundColor(frameNode, Color(color));
}

void ResetTextInputSelectedBackgroundColor(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    Color selectedColor;
    auto pipeline = frameNode->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetThemeManager()->GetTheme<TextFieldTheme>();
    CHECK_NULL_VOID(theme);
    selectedColor = theme->GetSelectedColor();
    if (selectedColor.GetAlpha() == DEFAULT_ALPHA) {
        // Default setting of 20% opacity
        selectedColor = selectedColor.ChangeOpacity(DEFAULT_OPACITY);
    }
    TextFieldModelNG::SetSelectedBackgroundColor(frameNode, selectedColor);
}

void SetTextInputShowError(ArkUINodeHandle node, ArkUI_CharPtr error, ArkUI_Uint32 visible)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::SetShowError(frameNode, std::string(error), static_cast<bool>(visible));
}

void ResetTextInputShowError(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::SetShowError(frameNode, std::string(""), false);
}

void SetTextInputPlaceholderFont(ArkUINodeHandle node, const struct ArkUIPlaceholderFontType* placeholderFont)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    Font font;
    CalcDimension fontSize;
    if (placeholderFont->size != nullptr) {
        if (placeholderFont->size->string != nullptr) {
            fontSize.SetCalcValue(placeholderFont->size->string);
        } else {
            fontSize.SetValue(placeholderFont->size->number);
        }
        fontSize.SetUnit(static_cast<DimensionUnit>(placeholderFont->size->unit));
    }
    font.fontSize = fontSize;
    if (placeholderFont->weight != nullptr && !std::string(placeholderFont->weight).empty()) {
        font.fontWeight = Framework::ConvertStrToFontWeight(placeholderFont->weight);
    } else if (placeholderFont->weightEnum > -1) {
        font.fontWeight = static_cast<FontWeight>(placeholderFont->weightEnum);
    }
    if (placeholderFont->fontFamilies != nullptr && placeholderFont->length > 0) {
        for (uint32_t i = 0; i < placeholderFont->length; i++) {
            const char* family = *(placeholderFont->fontFamilies + i);
            if (family != nullptr) {
                font.fontFamilies.emplace_back(std::string(family));
            }
        }
    }
    if (placeholderFont->style >= 0) {
        font.fontStyle = static_cast<Ace::FontStyle>(placeholderFont->style);
    }
    TextFieldModelNG::SetPlaceholderFont(frameNode, font);
}

void ResetTextInputPlaceholderFont(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    Font font;
    auto pipeline = frameNode->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetThemeManager()->GetTheme<TextFieldTheme>();
    CHECK_NULL_VOID(theme);
    font.fontSize = theme->GetFontSize();
    font.fontWeight = DEFAULT_FONT_WEIGHT;
    font.fontStyle = DEFAULT_FONT_STYLE;
    TextFieldModelNG::SetPlaceholderFont(frameNode, font);
}

void SetTextInputFontColor(ArkUINodeHandle node, ArkUI_Uint32 color)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::SetTextColor(frameNode, Color(color));
}

void ResetTextInputFontColor(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto pipeline = frameNode->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetThemeManager()->GetTheme<TextFieldTheme>();
    CHECK_NULL_VOID(theme);
    TextFieldModelNG::SetTextColor(frameNode, theme->GetTextColor());
}

void SetTextInputFontStyle(ArkUINodeHandle node, ArkUI_Uint32 value)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::SetFontStyle(frameNode, static_cast<Ace::FontStyle>(value));
}

void ResetTextInputFontStyle(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::SetFontStyle(frameNode, DEFAULT_FONT_STYLE);
}

void SetTextInputFontFamily(ArkUINodeHandle node, ArkUI_CharPtr* fontFamilies, ArkUI_Uint32 length)
{
    CHECK_NULL_VOID(fontFamilies);
    if (length <= 0) {
        return;
    }
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    std::vector<std::string> families;
    for (uint32_t i = 0; i < length; i++) {
        const char* family = *(fontFamilies + i);
        if (family != nullptr) {
            families.emplace_back(std::string(family));
        }
    }
    TextFieldModelNG::SetFontFamily(frameNode, families);
}

void ResetTextInputFontFamily(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::SetFontFamily(frameNode, DEFAULT_FONT_FAMILY);
}

void SetTextInputPlaceholderString(ArkUINodeHandle node, ArkUI_CharPtr value)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    std::string placeholderStr(value);
    TextFieldModelNG::SetTextFieldPlaceHolder(frameNode, placeholderStr);
}

void SetTextInputTextString(ArkUINodeHandle node, ArkUI_CharPtr value)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    std::string textStr(value);
    TextFieldModelNG::SetTextFieldText(frameNode, textStr);
}

void StopTextInputTextEditing(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::StopTextFieldEditing(frameNode);
}

void SetTextInputCancelButton(ArkUINodeHandle node, ArkUI_Int32 style, const struct ArkUISizeType* size,
    ArkUI_Uint32 color, ArkUI_CharPtr src)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::SetCleanNodeStyle(frameNode, static_cast<CleanNodeStyle>(style));
    TextFieldModelNG::SetIsShowCancelButton(frameNode, true);
    TextFieldModelNG::SetCancelButtonSymbol(frameNode, false);
    // set icon size
    CalcDimension iconSize = CalcDimension(size->value, static_cast<DimensionUnit>(size->unit));
    if (LessNotEqual(iconSize.Value(), 0.0)) {
        auto pipeline = frameNode->GetContext();
        CHECK_NULL_VOID(pipeline);
        auto theme = pipeline->GetThemeManager()->GetTheme<TextFieldTheme>();
        iconSize = theme->GetIconSize();
    }
    TextFieldModelNG::SetCancelIconSize(frameNode, iconSize);
    // set icon src
    std::string iconSrc(src);
    TextFieldModelNG::SetCanacelIconSrc(frameNode, iconSrc);
    // set icon color
    Color iconColor(color);
    TextFieldModelNG::SetCancelIconColor(frameNode, iconColor);
}

void resetTextInputCancelButton(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::SetCleanNodeStyle(frameNode, CleanNodeStyle::INPUT);
    TextFieldModelNG::SetIsShowCancelButton(frameNode, false);
    TextFieldModelNG::SetCancelButtonSymbol(frameNode, true);
}

ArkUI_CharPtr GetTextInputPlaceholder(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_RETURN(frameNode, "");
    g_strValue = TextFieldModelNG::GetPlaceholderText(frameNode);
    return g_strValue.c_str();
}

ArkUI_CharPtr GetTextInputText(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_RETURN(frameNode, "");
    g_strValue = TextFieldModelNG::GetTextFieldText(frameNode);
    return g_strValue.c_str();
}

ArkUI_Uint32 GetTextInputCaretColor(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_UINT_CODE);
    return TextFieldModelNG::GetCaretColor(frameNode).GetValue();
}

ArkUI_Float32 GetTextInputCaretStyle(ArkUINodeHandle node, ArkUI_Int32 unit)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_FLOAT_CODE);
    return TextFieldModelNG::GetCaretStyle(frameNode).GetNativeValue(static_cast<DimensionUnit>(unit));
}

ArkUI_Bool GetTextInputShowUnderline(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_INT_CODE);
    return static_cast<ArkUI_Bool>(TextFieldModelNG::GetShowUnderline(frameNode));
}

ArkUI_Uint32 GetTextInputMaxLength(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_UINT_CODE);
    return TextFieldModelNG::GetMaxLength(frameNode);
}

ArkUI_Int32 GetTextInputEnterKeyType(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_INT_CODE);
    return static_cast<ArkUI_Int32>(TextFieldModelNG::GetEnterKeyType(frameNode));
}

ArkUI_Uint32 GetTextInputPlaceholderColor(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_UINT_CODE);
    return TextFieldModelNG::GetPlaceholderColor(frameNode).GetValue();
}

void GetTextInputPlaceholderFont(ArkUINodeHandle node, ArkUITextFont* font)
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

ArkUI_Bool GetTextInputRequestKeyboardOnFocus(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_INT_CODE);
    return static_cast<ArkUI_Bool>(TextFieldModelNG::GetRequestKeyboardOnFocus(frameNode));
}

ArkUI_Int32 GetTextInputType(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_INT_CODE);
    return static_cast<ArkUI_Int32>(TextFieldModelNG::GetType(frameNode));
}

ArkUI_Uint32 GetTextInputSelectedBackgroundColor(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_UINT_CODE);
    return TextFieldModelNG::GetSelectedBackgroundColor(frameNode).GetValue();
}

ArkUI_Bool GetTextInputShowPasswordIcon(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_INT_CODE);
    return TextFieldModelNG::GetShowPasswordIcon(frameNode);
}

ArkUI_Bool GetTextInputEditing(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_INT_CODE);
    return TextFieldModelNG::GetTextFieldEditing(frameNode);
}

ArkUI_Bool GetTextInputShowCancelButton(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_INT_CODE);
    return TextFieldModelNG::GetShowCancelButton(frameNode);
}

ArkUI_Int32 GetTextInputCancelButtonStyle(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_INT_CODE);
    return static_cast<ArkUI_Int32>(TextFieldModelNG::GetCleanNodeStyle(frameNode));
}

ArkUI_Float32 GetTextInputCancelIconSize(ArkUINodeHandle node, ArkUI_Int32 unit)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_FLOAT_CODE);
    return TextFieldModelNG::GetCancelIconSize(frameNode).GetNativeValue(static_cast<DimensionUnit>(unit));
}

ArkUI_CharPtr getTextInputTextCancelIconSrc(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_RETURN(frameNode, "");
    g_strValue = TextFieldModelNG::GetCanacelIconSrc(frameNode);
    return g_strValue.c_str();
}

ArkUI_Uint32 getTextInputTextCancelIconColor(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_UINT_CODE);
    return TextFieldModelNG::GetCancelIconColor(frameNode).GetValue();
}

ArkUI_Int32 GetTextInputTextAlign(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_INT_CODE);
    return static_cast<ArkUI_Int32>(TextFieldModelNG::GetTextAlign(frameNode));
}

ArkUI_Uint32 GetTextInputFontColor(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_UINT_CODE);
    return TextFieldModelNG::GetTextColor(frameNode).GetValue();
}

ArkUI_Int32 GetTextInputFontStyle(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_INT_CODE);
    return static_cast<ArkUI_Int32>(TextFieldModelNG::GetFontStyle(frameNode));
}

ArkUI_Int32 GetTextInputFontWeight(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_INT_CODE);
    return static_cast<ArkUI_Int32>(TextFieldModelNG::GetFontWeight(frameNode));
}

ArkUI_Float32 GetTextInputFontSize(ArkUINodeHandle node, ArkUI_Int32 unit)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_FLOAT_CODE);
    return TextFieldModelNG::GetFontSize(frameNode).GetNativeValue(static_cast<DimensionUnit>(unit));
}

void SetTextInputBackgroundColor(ArkUINodeHandle node, ArkUI_Uint32 color)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::SetBackgroundColor(frameNode, Color(color));
}

void ResetTextInputBackgroundColor(ArkUINodeHandle node)
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

void SetTextInputNormalUnderlineColor(ArkUINodeHandle node, ArkUI_Uint32 normalColor)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::SetNormalUnderlineColor(frameNode, Color(normalColor));
}

void SetTextInputUserUnderlineColor(ArkUINodeHandle node, const ArkUI_Uint32* values,
    const ArkUI_Bool* hasValues, ArkUI_Int32 length)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    UserUnderlineColor userColor = UserUnderlineColor();
    if (length != DEFAULT_GROUP_UNDERLINE_COLOR_VALUES_COUNT) {
        return;
    }
    if (hasValues[CALL_ARG_0]) {
        userColor.typing = Color(values[CALL_ARG_0]);
    }
    if (hasValues[CALL_ARG_1]) {
        userColor.normal = Color(values[CALL_ARG_1]);
    }
    if (hasValues[CALL_ARG_2]) {
        userColor.error = Color(values[CALL_ARG_2]);
    }
    if (hasValues[CALL_ARG_3]) {
        userColor.disable = Color(values[CALL_ARG_3]);
    }
    TextFieldModelNG::SetUserUnderlineColor(frameNode, userColor);
}

void GetTextInputUserUnderlineColor(ArkUINodeHandle node, ArkUI_Uint32 (*values)[4])
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    UserUnderlineColor userColor = TextFieldModelNG::GetUnderLineColor(frameNode);
    (*values)[CALL_ARG_0] = userColor.typing->GetValue();
    (*values)[CALL_ARG_1] = userColor.normal->GetValue();
    (*values)[CALL_ARG_2] = userColor.error->GetValue();
    (*values)[CALL_ARG_3] = userColor.disable->GetValue();
}

void ResetTextInputUserUnderlineColor(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    UserUnderlineColor userColor = UserUnderlineColor();
    TextFieldModelNG::SetUserUnderlineColor(frameNode, userColor);
}

void SetTextInputTextSelection(ArkUINodeHandle node, ArkUI_Int32 start, ArkUI_Int32 end)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::SetTextSelection(frameNode, start, end);
}

ArkUI_Int32 GetTextInputTextSelectionIndex(ArkUINodeHandle node, ArkUI_Bool isEnd)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_INT_CODE);
    return TextFieldModelNG::GetTextSelectionIndex(frameNode, isEnd);
}
void SetTextInputDecoration(ArkUINodeHandle node, ArkUI_Int32 decoration, ArkUI_Uint32 color, ArkUI_Int32 style)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::SetTextDecoration(frameNode, static_cast<TextDecoration>(decoration));
    TextFieldModelNG::SetTextDecorationColor(frameNode, Color(color));
    TextFieldModelNG::SetTextDecorationStyle(frameNode, static_cast<TextDecorationStyle>(style));
}

void ResetTextInputDecoration(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::SetTextDecoration(frameNode, DEFAULT_TEXT_DECORATION);
    TextFieldModelNG::SetTextDecorationColor(frameNode, DEFAULT_DECORATION_COLOR);
    TextFieldModelNG::SetTextDecorationStyle(frameNode, DEFAULT_DECORATION_STYLE);
}

void SetTextInputLetterSpacing(ArkUINodeHandle node, ArkUI_Float32 value, ArkUI_Int32 unit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::SetLetterSpacing(frameNode, CalcDimension(value, (DimensionUnit)unit));
}

void ResetTextInputLetterSpacing(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CalcDimension value;
    value.Reset();
    TextFieldModelNG::SetLetterSpacing(frameNode, value);
}

void SetTextInputLineHeight(ArkUINodeHandle node, ArkUI_Float32 value, ArkUI_Int32 unit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::SetLineHeight(frameNode, CalcDimension(value, (DimensionUnit)unit));
}

void ResetTextInputLineHeight(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CalcDimension value;
    value.Reset();
    TextFieldModelNG::SetLineHeight(frameNode, value);
}

void SetTextInputFontFeature(ArkUINodeHandle node, ArkUI_CharPtr value)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    std::string strValue = value;
    TextFieldModelNG::SetFontFeature(frameNode, ParseFontFeatureSettings(strValue));
}

void ResetTextInputFontFeature(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    std::string strValue = "";
    TextFieldModelNG::SetFontFeature(frameNode, ParseFontFeatureSettings(strValue));
}

void SetTextInputWordBreak(ArkUINodeHandle node, ArkUI_Uint32 wordBreak)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (wordBreak < 0 || wordBreak >= WORD_BREAK_TYPES.size()) {
        wordBreak = 2; // 2 is the default value of WordBreak::BREAK_WORD
    }
    TextFieldModelNG::SetWordBreak(frameNode, WORD_BREAK_TYPES[wordBreak]);
}

ArkUI_Int32 GetTextInputWordBreak(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_INT_CODE);
    return static_cast<ArkUI_Int32>(TextFieldModelNG::GetWordBreak(frameNode));
}

void ResetTextInputWordBreak(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::SetWordBreak(frameNode, WORD_BREAK_TYPES[2]); // 2 is the default value of WordBreak::BREAK_WORD
}

void SetTextInputPadding(ArkUINodeHandle node, const struct ArkUISizeType* top, const struct ArkUISizeType* right,
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

void ResetTextInputPadding(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    TextFieldModelNG::ResetTextInputPadding(frameNode);
}

void SetTextInputAdaptMinFontSize(ArkUINodeHandle node, ArkUI_Float32 value, ArkUI_Int32 unit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::SetAdaptMinFontSize(frameNode, CalcDimension(value, (DimensionUnit)unit));
}

void ResetTextInputAdaptMinFontSize(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto pipelineContext = frameNode->GetContext();
    CHECK_NULL_VOID(pipelineContext);
    auto theme = pipelineContext->GetTheme<TextFieldTheme>();
    CHECK_NULL_VOID(theme);
    CalcDimension minFontSize = theme->GetTextStyle().GetAdaptMinFontSize();
    TextFieldModelNG::SetAdaptMinFontSize(frameNode, minFontSize);
}

void SetTextInputAdaptMaxFontSize(ArkUINodeHandle node, ArkUI_Float32 value, ArkUI_Int32 unit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::SetAdaptMaxFontSize(frameNode, CalcDimension(value, (DimensionUnit)unit));
}

void ResetTextInputAdaptMaxFontSize(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto pipelineContext = frameNode->GetContext();
    CHECK_NULL_VOID(pipelineContext);
    auto theme = pipelineContext->GetTheme<TextFieldTheme>();
    CHECK_NULL_VOID(theme);
    CalcDimension maxFontSize = theme->GetTextStyle().GetAdaptMaxFontSize();
    TextFieldModelNG::SetAdaptMaxFontSize(frameNode, maxFontSize);
}

void SetTextInputHeightAdaptivePolicy(ArkUINodeHandle node, ArkUI_Int32 value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::SetHeightAdaptivePolicy(frameNode, static_cast<Ace::TextHeightAdaptivePolicy>(value));
}

void ResetTextInputHeightAdaptivePolicy(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::SetHeightAdaptivePolicy(frameNode, TextHeightAdaptivePolicy::MAX_LINES_FIRST);
}

ArkUI_Bool GetTextInputSelectionMenuHidden(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_INT_CODE);
    return TextFieldModelNG::GetSelectionMenuHidden(frameNode);
}

void SetTextInputPlaceholderFontEnum(ArkUINodeHandle node, const struct ArkUIResourceLength* size, ArkUI_Int32 weight,
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
        fontFamilies.emplace_back(DEFAULT_FONT_FAMILY[0]);
        font.fontFamilies = fontFamilies;
    }

    if (style >= 0) {
        font.fontStyle = static_cast<Ace::FontStyle>(style);
    } else {
        font.fontStyle = DEFAULT_FONT_STYLE;
    }
    TextFieldModelNG::SetPlaceholderFont(frameNode, font);
}

void SetTextInputTextOverflow(ArkUINodeHandle node, ArkUI_Int32 value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextOverflow valueTextOverflow = static_cast<TextOverflow>(value);
    TextFieldModelNG::SetTextOverflow(frameNode, valueTextOverflow);
}

void ResetTextInputTextOverflow(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::SetTextOverflow(frameNode, TextOverflow::DEFAULT);
}

void SetTextInputTextIndent(ArkUINodeHandle node, ArkUI_Float32 number, ArkUI_Int32 unit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::SetTextIndent(frameNode, Dimension(number, static_cast<DimensionUnit>(unit)));
}

void ResetTextInputTextIndent(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::SetTextIndent(frameNode, CalcDimension(0, DimensionUnit::VP));
}

void SetTextInputShowPassword(ArkUINodeHandle node, ArkUI_Uint32 value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::SetShowPassword(frameNode, static_cast<bool>(value));
}

void ResetTextInputShowPassword(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::SetShowPassword(frameNode, false);
}

ArkUI_Bool GetTextInputShowPassword(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_INT_CODE);
    return TextFieldModelNG::GetShowPassword(frameNode);
}

ArkUI_CharPtr GetTextInputFontFeature(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, nullptr);
    g_strValue = UnParseFontFeatureSetting(TextFieldModelNG::GetFontFeature(frameNode));
    return g_strValue.c_str();
}

ArkUINodeHandle GetTextInputController(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, nullptr);
    auto controller = TextFieldModelNG::GetOrCreateController(frameNode);
    CHECK_NULL_RETURN(controller, nullptr);
    auto nodecontroller = reinterpret_cast<ArkUINodeHandle>(OHOS::Ace::AceType::RawPtr(controller));
    return nodecontroller;
}

ArkUI_Float32 GetTextInputAdaptMinFontSize(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_FLOAT_CODE);
    return TextFieldModelNG::GetAdaptMinFontSize(frameNode).Value();
}

ArkUI_Float32 GetTextInputAdaptMaxFontSize(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_FLOAT_CODE);
    return TextFieldModelNG::GetAdaptMaxFontSize(frameNode).Value();
}

ArkUI_Float32 GetTextInputLineHeight(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_FLOAT_CODE);
    return TextFieldModelNG::GetLineHeight(frameNode).Value();
}

ArkUI_Int32 GetTextInputMaxLines(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_FLOAT_CODE);
    return TextFieldModelNG::GetMaxLines(frameNode);
}

void SetTextInputSelectAll(ArkUINodeHandle node, ArkUI_Uint32 enableSelectAll)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::SetSelectAllValue(frameNode, static_cast<bool>(enableSelectAll));
}

void ResetTextInputSelectAll(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::SetSelectAllValue(frameNode, DEFAULT_SELECT_ALL);
}

void SetTextInputShowCounter(
    ArkUINodeHandle node, ArkUI_Uint32 open, ArkUI_Int32 thresholdPercentage, ArkUI_Uint32 highlightBorder)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::SetShowCounter(frameNode, static_cast<bool>(open));
    TextFieldModelNG::SetCounterType(frameNode, thresholdPercentage);
    TextFieldModelNG::SetShowCounterBorder(frameNode, static_cast<bool>(highlightBorder));
}

void ResetTextInputShowCounter(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::SetShowCounter(frameNode, false);
    TextFieldModelNG::SetCounterType(frameNode, -1);
    TextFieldModelNG::SetShowCounterBorder(frameNode, true);
}

void SetTextInputOnEditChange(ArkUINodeHandle node, void* callback)
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

void ResetTextInputOnEditChange(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::SetOnEditChange(frameNode, nullptr);
}

void SetTextInputFilter(ArkUINodeHandle node, ArkUI_CharPtr value, void* callback)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::string inputFilter(value);
    if (callback) {
        auto onError = reinterpret_cast<std::function<void(const std::string&)>*>(callback);
        TextFieldModelNG::SetInputFilter(frameNode, inputFilter, *onError);
    } else {
        TextFieldModelNG::SetInputFilter(frameNode, inputFilter, nullptr);
    }
}

void ResetTextInputFilter(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::SetInputFilter(frameNode, "", nullptr);
}

void SetTextInputOnSubmitWithEvent(ArkUINodeHandle node, void* callback)
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

void ResetTextInputOnSubmitWithEvent(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::SetOnSubmit(frameNode, nullptr);
}

void SetTextInputOnChange(ArkUINodeHandle node, void* callback)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (callback) {
        auto onChange = reinterpret_cast<std::function<void(const std::string&, PreviewText&)>*>(callback);
        TextFieldModelNG::SetOnChange(frameNode, std::move(*onChange));
    } else {
        TextFieldModelNG::SetOnChange(frameNode, nullptr);
    }
}

void ResetTextInputOnChange(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::SetOnChange(frameNode, nullptr);
}

void SetTextInputOnTextSelectionChange(ArkUINodeHandle node, void* callback)
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

void ResetTextInputOnTextSelectionChange(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::SetOnTextSelectionChange(frameNode, nullptr);
}

void SetTextInputOnContentScroll(ArkUINodeHandle node, void* callback)
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

void ResetTextInputOnContentScroll(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::SetOnContentScroll(frameNode, nullptr);
}

void SetTextInputOnCopy(ArkUINodeHandle node, void* callback)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (callback) {
        auto onCopy = reinterpret_cast<std::function<void(const std::string&)>*>(callback);
        TextFieldModelNG::SetOnCopy(frameNode, std::move(*onCopy));
    } else {
        TextFieldModelNG::SetOnCopy(frameNode, nullptr);
    }
}

void ResetTextInputOnCopy(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::SetOnCopy(frameNode, nullptr);
}

void SetTextInputOnCut(ArkUINodeHandle node, void* callback)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (callback) {
        auto onCut = reinterpret_cast<std::function<void(const std::string&)>*>(callback);
        TextFieldModelNG::SetOnCut(frameNode, std::move(*onCut));
    } else {
        TextFieldModelNG::SetOnCut(frameNode, nullptr);
    }
}

void ResetTextInputOnCut(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::SetOnCut(frameNode, nullptr);
}

void SetTextInputOnPaste(ArkUINodeHandle node, void* callback)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (callback) {
        auto onPasteWithEvent = reinterpret_cast<std::function<void(
                const std::string&, NG::TextCommonEvent&)>*>(callback);
        TextFieldModelNG::SetOnPasteWithEvent(frameNode, std::move(*onPasteWithEvent));
    } else {
        TextFieldModelNG::SetOnPasteWithEvent(frameNode, nullptr);
    }
}

void ResetTextInputOnPaste(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::SetOnPasteWithEvent(frameNode, nullptr);
}

void SetBlurOnSubmit(ArkUINodeHandle node, ArkUI_Bool blurOnSubmit)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::SetBlurOnSubmit(frameNode, blurOnSubmit);
}

ArkUI_Bool GetBlurOnSubmit(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_RETURN(frameNode, true);
    return TextFieldModelNG::GetBlurOnSubmit(frameNode);
}
void SetTextInputCustomKeyboard(ArkUINodeHandle node, ArkUINodeHandle customKeyboard, bool supportAvoidance)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto *customKeyboardNode = reinterpret_cast<FrameNode*>(customKeyboard);
    CHECK_NULL_VOID(customKeyboardNode);
    TextFieldModelNG::SetCustomKeyboard(frameNode, customKeyboardNode, supportAvoidance);
}

ArkUINodeHandle GetTextInputCustomKeyboard(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_RETURN(frameNode, nullptr);
    auto customKeyboard = TextFieldModelNG::GetCustomKeyboard(frameNode);
    CHECK_NULL_RETURN(customKeyboard, nullptr);
    return reinterpret_cast<ArkUINodeHandle>(OHOS::Ace::AceType::RawPtr(customKeyboard));
}

ArkUI_Int32 GetTextInputCustomKeyboardOption(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_RETURN(frameNode, 0);
    return static_cast<ArkUI_Int32>(TextFieldModelNG::GetCustomKeyboardOption(frameNode));
}

void ResetTextInputCustomKeyboard(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::SetCustomKeyboard(frameNode, nullptr, false);
}

void SetTextInputLineBreakStrategy(ArkUINodeHandle node, ArkUI_Uint32 lineBreakStrategy)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (lineBreakStrategy < 0 || lineBreakStrategy >= LINE_BREAK_STRATEGY_TYPES.size()) {
        lineBreakStrategy = 0; // 0 is the default value of lineBreakStrategy::GREEDY
    }
    TextFieldModelNG::SetLineBreakStrategy(frameNode, LINE_BREAK_STRATEGY_TYPES[lineBreakStrategy]);
}

void ResetTextInputLineBreakStrategy(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
     // 0 is the default value of lineBreakStrategy::GREEDY
    TextFieldModelNG::SetLineBreakStrategy(frameNode, LINE_BREAK_STRATEGY_TYPES[0]);
}

void SetTextInputShowKeyBoardOnFocus(ArkUINodeHandle node, ArkUI_Bool value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::SetShowKeyBoardOnFocus(frameNode, value);
}

ArkUI_Bool GetTextInputShowKeyBoardOnFocus(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_RETURN(frameNode, true);
    return static_cast<ArkUI_Bool>(TextFieldModelNG::GetShowKeyBoardOnFocus(frameNode));
}

void ResetTextInputShowKeyBoardOnFocus(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::SetShowKeyBoardOnFocus(frameNode, true);
}

void SetTextInputNumberOfLines(ArkUINodeHandle node, ArkUI_Int32 value)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::SetNumberOfLines(frameNode, value);
}

ArkUI_Int32 GetTextInputNumberOfLines(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_INT_CODE);
    return static_cast<ArkUI_Int32>(TextFieldModelNG::GetNumberOfLines(frameNode));
}

void ResetTextInputNumberOfLines(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::ResetNumberOfLines(frameNode);
}

void SetTextInputMargin(ArkUINodeHandle node, const struct ArkUISizeType* top, const struct ArkUISizeType* right,
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

void ResetTextInputMargin(ArkUINodeHandle node)
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

void SetTextInputCaret(ArkUINodeHandle node, ArkUI_Float32 value, ArkUI_Int32 unit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CaretStyle caretStyle;
    caretStyle.caretWidth = CalcDimension(value, (DimensionUnit)unit);
    TextFieldModelNG::SetCaretStyle(frameNode, caretStyle);
}

void GetTextInputMargin(ArkUINodeHandle node, ArkUI_Float32 (*values)[4], ArkUI_Int32 length, ArkUI_Int32 unit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto margin = TextFieldModelNG::GetMargin(frameNode);
    (*values)[CALL_ARG_0] = margin.top->GetDimension().GetNativeValue(static_cast<DimensionUnit>(unit));
    (*values)[CALL_ARG_1] = margin.right->GetDimension().GetNativeValue(static_cast<DimensionUnit>(unit));
    (*values)[CALL_ARG_2] = margin.bottom->GetDimension().GetNativeValue(static_cast<DimensionUnit>(unit));
    (*values)[CALL_ARG_3] = margin.left->GetDimension().GetNativeValue(static_cast<DimensionUnit>(unit));
    length = DEFAULT_MARGIN_VALUES_COUNT;
}

void SetTextInputEnablePreviewText(ArkUINodeHandle node, ArkUI_Uint32 value)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::SetEnablePreviewText(frameNode, static_cast<bool>(value));
}

void ResetTextInputEnablePreviewText(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::SetEnablePreviewText(frameNode, DEFAULT_ENABLE_PREVIEW_TEXT_VALUE);
}

void SetTextInputSelectionMenuOptions(ArkUINodeHandle node, void* onCreateMenuCallback, void* onMenuItemClickCallback)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NG::OnCreateMenuCallback* onCreateMenu = nullptr;
    NG::OnMenuItemClickCallback* onMenuItemClick = nullptr;
    if (onCreateMenuCallback) {
        onCreateMenu = reinterpret_cast<NG::OnCreateMenuCallback*>(onCreateMenuCallback);
        TextFieldModelNG::OnCreateMenuCallbackUpdate(frameNode, std::move(*onCreateMenu));
    } else {
        TextFieldModelNG::OnCreateMenuCallbackUpdate(frameNode, nullptr);
    }
    if (onMenuItemClickCallback) {
        onMenuItemClick = reinterpret_cast<NG::OnMenuItemClickCallback*>(onMenuItemClickCallback);
        TextFieldModelNG::OnMenuItemClickCallbackUpdate(frameNode, std::move(*onMenuItemClick));
    } else {
        TextFieldModelNG::OnMenuItemClickCallbackUpdate(frameNode, nullptr);
    }
}

void ResetTextInputSelectionMenuOptions(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NG::OnCreateMenuCallback onCreateMenuCallback;
    NG::OnMenuItemClickCallback onMenuItemClick;
    TextFieldModelNG::OnCreateMenuCallbackUpdate(frameNode, std::move(onCreateMenuCallback));
    TextFieldModelNG::OnMenuItemClickCallbackUpdate(frameNode, std::move(onMenuItemClick));
}

void SetTextInputWidth(ArkUINodeHandle node, ArkUI_CharPtr value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto widthValue = std::string(value);
    TextFieldModelNG::SetWidth(frameNode, widthValue);
}

void ResetTextInputWidth(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::ClearWidth(frameNode);
}
} // namespace
namespace NodeModifier {
const ArkUITextInputModifier* GetTextInputModifier()
{
    static const ArkUITextInputModifier modifier = { SetTextInputCaretColor, ResetTextInputCaretColor, SetTextInputType,
        ResetTextInputType, SetTextInputMaxLines, ResetTextInputMaxLines, SetTextInputPlaceholderColor,
        ResetTextInputPlaceholderColor, SetTextInputCaretPosition, ResetTextInputCaretPosition, SetTextInputCopyOption,
        ResetTextInputCopyOption, SetTextInputShowPasswordIcon, ResetTextInputShowPasswordIcon,
        SetTextInputPasswordIcon, ResetTextInputPasswordIcon, SetTextInputTextAlign, ResetTextInputTextAlign,
        SetTextInputStyle, ResetTextInputStyle, SetTextInputSelectionMenuHidden, ResetTextInputSelectionMenuHidden,
        SetTextInputShowUnderline, ResetTextInputShowUnderline, SetTextInputCaretStyle, ResetTextInputCaretStyle,
        SetTextInputEnableKeyboardOnFocus, ResetTextInputEnableKeyboardOnFocus, SetTextInputBarState,
        ResetTextInputBarState, SetTextInputEnterKeyType, ResetTextInputEnterKeyType, SetTextInputFontWeight,
        ResetTextInputFontWeight, SetTextInputFontSize, ResetTextInputFontSize, SetTextInputMaxLength,
        ResetTextInputMaxLength, SetTextInputSelectedBackgroundColor, ResetTextInputSelectedBackgroundColor,
        SetTextInputShowError, ResetTextInputShowError, SetTextInputPlaceholderFont, ResetTextInputPlaceholderFont,
        SetTextInputFontColor, ResetTextInputFontColor, SetTextInputFontStyle, ResetTextInputFontStyle,
        SetTextInputFontFamily, ResetTextInputFontFamily, SetTextInputPlaceholderString, SetTextInputTextString,
        SetTextInputFontWeightStr, StopTextInputTextEditing, SetTextInputCancelButton, resetTextInputCancelButton,
        GetTextInputPlaceholder, GetTextInputText, GetTextInputCaretColor, GetTextInputCaretStyle,
        GetTextInputShowUnderline, GetTextInputMaxLength, GetTextInputEnterKeyType, GetTextInputPlaceholderColor,
        GetTextInputPlaceholderFont, GetTextInputRequestKeyboardOnFocus, GetTextInputType,
        GetTextInputSelectedBackgroundColor, GetTextInputShowPasswordIcon, GetTextInputEditing,
        GetTextInputShowCancelButton, GetTextInputCancelIconSize, getTextInputTextCancelIconSrc,
        getTextInputTextCancelIconColor, GetTextInputTextAlign, GetTextInputFontColor, GetTextInputFontStyle,
        GetTextInputFontWeight, GetTextInputFontSize, GetTextInputCancelButtonStyle, SetTextInputBackgroundColor,
        ResetTextInputBackgroundColor, SetTextInputNormalUnderlineColor, SetTextInputUserUnderlineColor,
        ResetTextInputUserUnderlineColor, SetTextInputTextSelection, GetTextInputTextSelectionIndex,
        SetTextInputDecoration, ResetTextInputDecoration, SetTextInputLetterSpacing, ResetTextInputLetterSpacing,
        SetTextInputLineHeight, ResetTextInputLineHeight, SetTextInputFontFeature, ResetTextInputFontFeature,
        SetTextInputWordBreak, ResetTextInputWordBreak, SetTextInputPasswordRules, ResetTextInputPasswordRules,
        SetTextInputEnableAutoFill, ResetTextInputEnableAutoFill, SetTextInputPadding, ResetTextInputPadding,
        SetTextInputAdaptMinFontSize, ResetTextInputAdaptMinFontSize, SetTextInputAdaptMaxFontSize,
        ResetTextInputAdaptMaxFontSize, SetTextInputHeightAdaptivePolicy, ResetTextInputHeightAdaptivePolicy,
        SetTextInputPlaceholderFontEnum, SetTextInputTextOverflow, ResetTextInputTextOverflow, SetTextInputTextIndent,
        ResetTextInputTextIndent, SetTextInputSelectAll, ResetTextInputSelectAll, SetTextInputShowCounter,
        ResetTextInputShowCounter, SetTextInputOnEditChange, ResetTextInputOnEditChange, SetTextInputFilter,
        ResetTextInputFilter, SetTextInputOnSubmitWithEvent, ResetTextInputOnSubmitWithEvent, SetTextInputOnChange,
        ResetTextInputOnChange, SetTextInputOnTextSelectionChange, ResetTextInputOnTextSelectionChange,
        SetTextInputOnContentScroll, ResetTextInputOnContentScroll, SetTextInputOnCopy, ResetTextInputOnCopy,
        SetTextInputOnCut, ResetTextInputOnCut, SetTextInputOnPaste, ResetTextInputOnPaste,
        GetTextInputSelectionMenuHidden, SetTextInputShowPassword, ResetTextInputShowPassword, GetTextInputShowPassword,
        GetTextInputWordBreak, GetTextInputEnableAutoFill, SetTextInputContentType, ResetTextInputContentType,
        GetTextInputContentType, GetTextInputUserUnderlineColor, GetTextInputPasswordRules, GetTextInputSelectAll,
        SetTextInputInputFilter, GetTextInputInputFilter, ResetTextInputInputFilter, GetTextInputCaretIndex,
        GetTextInputCaretOffset, GetTextInputStyle, GetTextInputContentRect, GetTextInputContentLinesNum,
        SetBlurOnSubmit, GetBlurOnSubmit, GetTextInputAdaptMinFontSize, GetTextInputAdaptMaxFontSize,
        GetTextInputLineHeight, GetTextInputMaxLines, GetTextInputFontFeature, SetTextInputCustomKeyboard,
        GetTextInputCustomKeyboard, GetTextInputCustomKeyboardOption, ResetTextInputCustomKeyboard,
        SetTextInputLineBreakStrategy, ResetTextInputLineBreakStrategy, SetTextInputShowKeyBoardOnFocus,
        GetTextInputShowKeyBoardOnFocus, ResetTextInputShowKeyBoardOnFocus, SetTextInputNumberOfLines,
        GetTextInputNumberOfLines, ResetTextInputNumberOfLines, SetTextInputMargin, ResetTextInputMargin,
        SetTextInputCaret, GetTextInputController, GetTextInputMargin, SetTextInputEnablePreviewText,
        ResetTextInputEnablePreviewText, SetTextInputSelectionMenuOptions, ResetTextInputSelectionMenuOptions,
        SetTextInputWidth, ResetTextInputWidth };
    return &modifier;
}

const CJUITextInputModifier* GetCJUITextInputModifier()
{
    static const CJUITextInputModifier modifier = { SetTextInputCaretColor, ResetTextInputCaretColor, SetTextInputType,
        ResetTextInputType, SetTextInputMaxLines, ResetTextInputMaxLines, SetTextInputPlaceholderColor,
        ResetTextInputPlaceholderColor, SetTextInputCaretPosition, ResetTextInputCaretPosition, SetTextInputCopyOption,
        ResetTextInputCopyOption, SetTextInputShowPasswordIcon, ResetTextInputShowPasswordIcon,
        SetTextInputPasswordIcon, ResetTextInputPasswordIcon, SetTextInputTextAlign, ResetTextInputTextAlign,
        SetTextInputStyle, ResetTextInputStyle, SetTextInputSelectionMenuHidden, ResetTextInputSelectionMenuHidden,
        SetTextInputShowUnderline, ResetTextInputShowUnderline, SetTextInputCaretStyle, ResetTextInputCaretStyle,
        SetTextInputEnableKeyboardOnFocus, ResetTextInputEnableKeyboardOnFocus, SetTextInputBarState,
        ResetTextInputBarState, SetTextInputEnterKeyType, ResetTextInputEnterKeyType, SetTextInputFontWeight,
        ResetTextInputFontWeight, SetTextInputFontSize, ResetTextInputFontSize, SetTextInputMaxLength,
        ResetTextInputMaxLength, SetTextInputSelectedBackgroundColor, ResetTextInputSelectedBackgroundColor,
        SetTextInputShowError, ResetTextInputShowError, SetTextInputPlaceholderFont, ResetTextInputPlaceholderFont,
        SetTextInputFontColor, ResetTextInputFontColor, SetTextInputFontStyle, ResetTextInputFontStyle,
        SetTextInputFontFamily, ResetTextInputFontFamily, SetTextInputPlaceholderString, SetTextInputTextString,
        SetTextInputFontWeightStr, StopTextInputTextEditing, SetTextInputCancelButton, resetTextInputCancelButton,
        GetTextInputPlaceholder, GetTextInputText, GetTextInputCaretColor, GetTextInputCaretStyle,
        GetTextInputShowUnderline, GetTextInputMaxLength, GetTextInputEnterKeyType, GetTextInputPlaceholderColor,
        GetTextInputPlaceholderFont, GetTextInputRequestKeyboardOnFocus, GetTextInputType,
        GetTextInputSelectedBackgroundColor, GetTextInputShowPasswordIcon, GetTextInputEditing,
        GetTextInputShowCancelButton, GetTextInputCancelIconSize, getTextInputTextCancelIconSrc,
        getTextInputTextCancelIconColor, GetTextInputTextAlign, GetTextInputFontColor, GetTextInputFontStyle,
        GetTextInputFontWeight, GetTextInputFontSize, GetTextInputCancelButtonStyle, SetTextInputBackgroundColor,
        ResetTextInputBackgroundColor, SetTextInputTextSelection, GetTextInputTextSelectionIndex,
        SetTextInputPasswordRules, ResetTextInputPasswordRules, SetTextInputEnableAutoFill,
        ResetTextInputEnableAutoFill, SetTextInputPadding, ResetTextInputPadding,
        SetTextInputFontFeature, ResetTextInputFontFeature,
        SetTextInputDecoration, ResetTextInputDecoration, SetTextInputLetterSpacing, ResetTextInputLetterSpacing,
        SetTextInputLineHeight, ResetTextInputLineHeight,
        SetTextInputNormalUnderlineColor, SetTextInputUserUnderlineColor, ResetTextInputUserUnderlineColor,
        SetTextInputWordBreak, ResetTextInputWordBreak, SetTextInputPlaceholderFontEnum,
        SetTextInputAdaptMinFontSize, ResetTextInputAdaptMinFontSize, SetTextInputAdaptMaxFontSize,
        ResetTextInputAdaptMaxFontSize, SetTextInputHeightAdaptivePolicy, ResetTextInputHeightAdaptivePolicy,
        SetTextInputTextOverflow, ResetTextInputTextOverflow, SetTextInputTextIndent, ResetTextInputTextIndent,
        GetTextInputSelectionMenuHidden, GetTextInputWordBreak, GetTextInputEnableAutoFill,
        SetTextInputContentType, ResetTextInputContentType, GetTextInputContentType,
        GetTextInputUserUnderlineColor, GetTextInputPasswordRules, GetTextInputSelectAll,
        SetTextInputInputFilter, GetTextInputInputFilter, ResetTextInputInputFilter, GetTextInputCaretIndex,
        GetTextInputCaretOffset, GetTextInputStyle, GetTextInputContentRect, GetTextInputContentLinesNum,
        SetBlurOnSubmit, GetBlurOnSubmit, GetTextInputAdaptMinFontSize, GetTextInputAdaptMaxFontSize,
        GetTextInputLineHeight, GetTextInputMaxLines, GetTextInputFontFeature,
        SetTextInputCustomKeyboard, GetTextInputCustomKeyboard, GetTextInputCustomKeyboardOption,
        ResetTextInputCustomKeyboard, SetTextInputSelectAll, ResetTextInputSelectAll, SetTextInputShowCounter,
        ResetTextInputShowCounter, SetTextInputOnEditChange, ResetTextInputOnEditChange, SetTextInputFilter,
        ResetTextInputFilter, SetTextInputOnSubmitWithEvent, ResetTextInputOnSubmitWithEvent, SetTextInputOnChange,
        ResetTextInputOnChange, SetTextInputOnTextSelectionChange, ResetTextInputOnTextSelectionChange,
        SetTextInputOnContentScroll, ResetTextInputOnContentScroll, SetTextInputOnCopy, ResetTextInputOnCopy,
        SetTextInputOnCut, ResetTextInputOnCut, SetTextInputOnPaste, ResetTextInputOnPaste,
        SetTextInputShowKeyBoardOnFocus, GetTextInputShowKeyBoardOnFocus, ResetTextInputShowKeyBoardOnFocus,
        SetTextInputNumberOfLines, GetTextInputNumberOfLines, ResetTextInputNumberOfLines,
        SetTextInputShowPassword, ResetTextInputShowPassword, GetTextInputShowPassword, SetTextInputLineBreakStrategy,
        ResetTextInputLineBreakStrategy, SetTextInputMargin, ResetTextInputMargin,
        GetTextInputMargin, SetTextInputCaret, GetTextInputController,
        SetTextInputEnablePreviewText, ResetTextInputEnablePreviewText };

    return &modifier;
}

void SetOnTextInputChange(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto onChange = [node, extraParam](const std::string& str, PreviewText&) {
        ArkUINodeEvent event;
        event.kind = TEXT_INPUT;
        event.extraParam = reinterpret_cast<intptr_t>(extraParam);
        event.textInputEvent.subKind = ON_TEXT_INPUT_CHANGE;
        event.textInputEvent.nativeStringPtr = reinterpret_cast<intptr_t>(str.c_str());
        SendArkUIAsyncEvent(&event);
    };
    TextFieldModelNG::SetOnChange(frameNode, std::move(onChange));
}

void SetTextInputOnSubmit(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto onEvent = [node, extraParam](int32_t value, NG::TextFieldCommonEvent& commonEvent) {
        ArkUINodeEvent event;
        event.kind = COMPONENT_ASYNC_EVENT;
        event.extraParam = reinterpret_cast<intptr_t>(extraParam);
        event.componentAsyncEvent.subKind = ON_TEXT_INPUT_SUBMIT;
        event.componentAsyncEvent.data[0].i32 = value;
        SendArkUIAsyncEvent(&event);
    };
    TextFieldModelNG::SetOnSubmit(frameNode, std::move(onEvent));
}

void SetOnTextInputCut(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto onCut = [node, extraParam](const std::string& str) {
        ArkUINodeEvent event;
        event.kind = TEXT_INPUT;
        event.extraParam = reinterpret_cast<intptr_t>(extraParam);
        event.textInputEvent.subKind = ON_TEXT_INPUT_CUT;
        event.textInputEvent.nativeStringPtr = reinterpret_cast<intptr_t>(str.c_str());
        SendArkUIAsyncEvent(&event);
    };
    TextFieldModelNG::SetOnCut(frameNode, std::move(onCut));
}

void SetOnTextInputPaste(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto onPaste = [node, extraParam](const std::string& str, NG::TextCommonEvent& commonEvent) {
        ArkUINodeEvent event;
        event.kind = TEXT_INPUT;
        event.extraParam = reinterpret_cast<intptr_t>(extraParam);
        event.textInputEvent.subKind = ON_TEXT_INPUT_PASTE;
        event.textInputEvent.nativeStringPtr = reinterpret_cast<intptr_t>(str.c_str());
        SendArkUIAsyncEvent(&event);
    };
    TextFieldModelNG::SetOnPasteWithEvent(frameNode, std::move(onPaste));
}

void SetOnTextInputSelectionChange(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto onSelectionChange = [node, extraParam](int32_t start, int32_t end) {
        ArkUINodeEvent event;
        event.kind = COMPONENT_ASYNC_EVENT;
        event.extraParam = reinterpret_cast<intptr_t>(extraParam);
        event.componentAsyncEvent.subKind = ON_TEXT_INPUT_TEXT_SELECTION_CHANGE;
        event.componentAsyncEvent.data[0].i32 = static_cast<int>(start);
        event.componentAsyncEvent.data[1].i32 = static_cast<int>(end);
        SendArkUIAsyncEvent(&event);
    };
    TextFieldModelNG::SetOnTextSelectionChange(frameNode, std::move(onSelectionChange));
}

void SetOnTextInputEditChange(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto onChange = [node, extraParam](bool isEditing) {
        ArkUINodeEvent event;
        event.kind = COMPONENT_ASYNC_EVENT;
        event.extraParam = reinterpret_cast<intptr_t>(extraParam);
        event.componentAsyncEvent.subKind = ON_TEXT_INPUT_EDIT_CHANGE;
        event.componentAsyncEvent.data[0].i32 = static_cast<int>(isEditing);
        SendArkUIAsyncEvent(&event);
    };
    TextFieldModelNG::SetOnEditChanged(frameNode, std::move(onChange));
}

void SetOnTextInputContentSizeChange(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto onChange = [node, extraParam](float width, float height) {
        ArkUINodeEvent event;
        event.kind = COMPONENT_ASYNC_EVENT;
        event.extraParam = reinterpret_cast<intptr_t>(extraParam);
        event.componentAsyncEvent.subKind = ON_TEXT_INPUT_CONTENT_SIZE_CHANGE;
        bool usePx = NodeModel::UsePXUnit(reinterpret_cast<ArkUI_Node*>(extraParam));
        double density = usePx ? 1 : PipelineBase::GetCurrentDensity();
        //0 width
        event.componentAsyncEvent.data[0].f32 = NearEqual(density, 0.0) ? 0.0f : width / density;
        //1 height
        event.componentAsyncEvent.data[1].f32 = NearEqual(density, 0.0) ? 0.0f : height / density;
        SendArkUIAsyncEvent(&event);
    };
    TextFieldModelNG::SetOnContentSizeChange(frameNode, std::move(onChange));
}

void SetOnTextInputInputFilterError(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto onInputFilterError = [node, extraParam](const std::string& str) {
        ArkUINodeEvent event;
        event.kind = TEXT_INPUT;
        event.extraParam = reinterpret_cast<intptr_t>(extraParam);
        event.textInputEvent.subKind = ON_TEXT_INPUT_INPUT_FILTER_ERROR;
        event.textInputEvent.nativeStringPtr = reinterpret_cast<intptr_t>(str.c_str());
        SendArkUIAsyncEvent(&event);
    };
    TextFieldModelNG::SetInputFilterError(frameNode, std::move(onInputFilterError));
}

void SetTextInputOnTextContentScroll(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto onScroll = [node, extraParam](float totalOffsetX, float totalOffsetY) {
        ArkUINodeEvent event;
        event.kind = COMPONENT_ASYNC_EVENT;
        event.extraParam = reinterpret_cast<intptr_t>(extraParam);
        event.componentAsyncEvent.subKind = ON_TEXT_INPUT_CONTENT_SCROLL;
        event.componentAsyncEvent.data[0].f32 = totalOffsetX;
        event.componentAsyncEvent.data[1].f32 = totalOffsetY;
        SendArkUIAsyncEvent(&event);
    };
    TextFieldModelNG::SetOnContentScroll(frameNode, std::move(onScroll));
}

void SetTextInputOnWillInsert(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto onWillInsert = [node, extraParam](const InsertValueInfo& Info) -> bool {
        ArkUINodeEvent event;
        event.kind = MIXED_EVENT;
        event.extraParam = reinterpret_cast<intptr_t>(extraParam);
        event.mixedEvent.subKind = ON_TEXT_INPUT_WILL_INSERT;
        event.mixedEvent.numberData[0].f32 = Info.insertOffset;
        event.mixedEvent.numberDataLength = 1;
        event.mixedEvent.stringPtrData[0] = reinterpret_cast<intptr_t>(Info.insertValue.c_str());
        event.mixedEvent.stringPtrDataLength = 1;
        SendArkUIAsyncEvent(&event);
        return event.mixedEvent.numberReturnData[0].i32;
    };
    TextFieldModelNG::SetOnWillInsertValueEvent(frameNode, std::move(onWillInsert));
}

void SetTextInputOnDidInsert(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto onDidInsert = [node, extraParam](const InsertValueInfo& Info) {
        ArkUINodeEvent event;
        event.kind = MIXED_EVENT;
        event.extraParam = reinterpret_cast<intptr_t>(extraParam);
        event.mixedEvent.subKind = ON_TEXT_INPUT_DID_INSERT;
        event.mixedEvent.numberData[0].f32 = Info.insertOffset;
        event.mixedEvent.numberDataLength = 1;
        event.mixedEvent.stringPtrData[0] = reinterpret_cast<intptr_t>(Info.insertValue.c_str());
        event.mixedEvent.stringPtrDataLength = 1;
        SendArkUIAsyncEvent(&event);
    };
    TextFieldModelNG::SetOnDidInsertValueEvent(frameNode, std::move(onDidInsert));
}

void SetTextInputOnWillDelete(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto onWillDelete = [node, extraParam](const DeleteValueInfo& Info) -> bool {
        ArkUINodeEvent event;
        event.kind = MIXED_EVENT;
        event.extraParam = reinterpret_cast<intptr_t>(extraParam);
        event.mixedEvent.subKind = ON_TEXT_INPUT_WILL_DELETE;
        event.mixedEvent.numberData[0].f32 = Info.deleteOffset;
        event.mixedEvent.numberData[1].i32 = static_cast<int32_t>(Info.direction);
        event.mixedEvent.numberDataLength = 2;
        event.mixedEvent.stringPtrData[0] = reinterpret_cast<intptr_t>(Info.deleteValue.c_str());
        event.mixedEvent.stringPtrDataLength = 1;
        SendArkUIAsyncEvent(&event);
        return event.mixedEvent.numberReturnData[0].i32;
    };
    TextFieldModelNG::SetOnWillDeleteEvent(frameNode, std::move(onWillDelete));
}

void SetTextInputOnDidDelete(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto onDidDelete = [node, extraParam](const DeleteValueInfo& Info) {
        ArkUINodeEvent event;
        event.kind = MIXED_EVENT;
        event.extraParam = reinterpret_cast<intptr_t>(extraParam);
        event.mixedEvent.subKind = ON_TEXT_INPUT_DID_DELETE;
        event.mixedEvent.numberData[0].f32 = Info.deleteOffset;
        event.mixedEvent.numberData[1].i32 = static_cast<int32_t>(Info.direction);
        event.mixedEvent.numberDataLength = 2;
        event.mixedEvent.stringPtrData[0] = reinterpret_cast<intptr_t>(Info.deleteValue.c_str());
        event.mixedEvent.stringPtrDataLength = 1;
        SendArkUIAsyncEvent(&event);
    };
    TextFieldModelNG::SetOnDidDeleteEvent(frameNode, std::move(onDidDelete));
}

void ResetOnTextInputChange(ArkUINodeHandle node)
{
    GetTextInputModifier()->resetTextInputOnChange(node);
}
void ResetTextInputOnSubmit(ArkUINodeHandle node)
{
    GetTextInputModifier()->resetTextInputOnSubmitWithEvent(node);
}
void ResetOnTextInputCut(ArkUINodeHandle node)
{
    GetTextInputModifier()->resetTextInputOnCut(node);
}
void ResetOnTextInputPaste(ArkUINodeHandle node)
{
    GetTextInputModifier()->resetTextInputOnPaste(node);
}
void ResetOnTextInputSelectionChange(ArkUINodeHandle node)
{
    GetTextInputModifier()->resetTextInputOnTextSelectionChange(node);
}
void ResetOnTextInputEditChange(ArkUINodeHandle node)
{
    GetTextInputModifier()->resetTextInputOnEditChange(node);
}
void ResetOnTextInputContentSizeChange(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::SetOnContentSizeChange(frameNode, nullptr);
}
void ResetOnTextInputInputFilterError(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::SetInputFilterError(frameNode, nullptr);
}
void ResetTextInputOnTextContentScroll(ArkUINodeHandle node)
{
    GetTextInputModifier()->resetTextInputOnContentScroll(node);
}
} // namespace NodeModifier
} // namespace OHOS::Ace::NG
