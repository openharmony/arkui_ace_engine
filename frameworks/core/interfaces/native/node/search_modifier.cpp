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
#include "core/interfaces/native/node/search_modifier.h"

#include "base/utils/utf_helper.h"
#include "core/components/search/search_theme.h"
#include "core/components/text_field/textfield_theme.h"
#include "core/components_ng/pattern/search/search_model_ng.h"
#include "core/components/common/properties/text_style_parser.h"

namespace OHOS::Ace::NG {
constexpr uint32_t DEFAULT_SEARCH_COLOR = 0x99182431;
constexpr Dimension DEFAULT_FONT_SIZE = 16.0_fp;
constexpr FontWeight DEFAULT_FONT_WEIGHT = FontWeight::NORMAL;
constexpr Ace::FontStyle DEFAULT_FONT_STYLE = Ace::FontStyle::NORMAL;
const bool DEFAULT_SELECTION_MENU_HIDDEN = false;
constexpr CancelButtonStyle DEFAULT_CANCEL_BUTTON_STYLE = CancelButtonStyle::INPUT;
constexpr Dimension THEME_SEARCH_FONT_SIZE = Dimension(16.0, DimensionUnit::FP);
constexpr Color THEME_SEARCH_TEXT_COLOR = Color(0xe5000000);
constexpr TextDecoration DEFAULT_TEXT_DECORATION = TextDecoration::NONE;
constexpr Color DEFAULT_DECORATION_COLOR = Color(0xff000000);
constexpr TextDecorationStyle DEFAULT_DECORATION_STYLE = TextDecorationStyle::SOLID;
constexpr int16_t DEFAULT_ALPHA = 255;
constexpr double DEFAULT_OPACITY = 0.2;
constexpr bool DEFAULT_ENABLE_PREVIEW_TEXT_VALUE = true;
constexpr int32_t DEFAULT_CARET_POSITION = 0;
constexpr bool DEFAULT_ENABLE_HAPTIC_FEEDBACK_VALUE = true;

void SetSearchTextFont(ArkUINodeHandle node, const struct ArkUIFontStruct* value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    Font font;
    font.fontSize = Dimension(value->fontSizeNumber, static_cast<DimensionUnit>(value->fontSizeUnit));
    font.fontWeight = static_cast<FontWeight>(value->fontWeight);
    font.fontFamilies.assign(value->fontFamilies, value->fontFamilies + value->familyLength);
    font.fontStyle = static_cast<OHOS::Ace::FontStyle>(value->fontStyle);

    SearchModelNG::SetTextFont(frameNode, font);
}

void ResetSearchTextFont(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    Font font;
    font.fontSize = DEFAULT_FONT_SIZE;
    font.fontWeight = DEFAULT_FONT_WEIGHT;
    font.fontStyle = DEFAULT_FONT_STYLE;
    SearchModelNG::SetTextFont(frameNode, font);
}

void SetSearchPlaceholderColor(ArkUINodeHandle node, ArkUI_Uint32 color)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SearchModelNG::SetPlaceholderColor(frameNode, Color(color));
}

void ResetSearchPlaceholderColor(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SearchModelNG::SetPlaceholderColor(frameNode, Color(DEFAULT_SEARCH_COLOR));
}

void SetSearchSelectionMenuHidden(ArkUINodeHandle node, ArkUI_Uint32 selectionMenuHidden)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SearchModelNG::SetSelectionMenuHidden(frameNode, static_cast<bool>(selectionMenuHidden));
}

void ResetSearchSelectionMenuHidden(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SearchModelNG::SetSelectionMenuHidden(frameNode, DEFAULT_SELECTION_MENU_HIDDEN);
}

void SetSearchCaretStyle(ArkUINodeHandle node, const ArkUI_Float32 number, ArkUI_Int32 unit, ArkUI_Uint32 caretColor)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SearchModelNG::SetCaretWidth(frameNode, Dimension(number, static_cast<DimensionUnit>(unit)));
    SearchModelNG::SetCaretColor(frameNode, Color(caretColor));
}

void ResetSearchCaretStyle(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto textFieldTheme = GetTheme<TextFieldTheme>();
    CHECK_NULL_VOID(textFieldTheme);
    CalcDimension caretWidth = textFieldTheme->GetCursorWidth();
    uint32_t caretColor = textFieldTheme->GetCursorColor().GetValue();
    SearchModelNG::SetCaretWidth(frameNode, Dimension(caretWidth.Value(), caretWidth.Unit()));
    SearchModelNG::SetCaretColor(frameNode, Color(caretColor));
}

void SetSearchTextAlign(ArkUINodeHandle node, ArkUI_Int32 value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextAlign value_textAlign = static_cast<TextAlign>(value);
    SearchModelNG::SetTextAlign(frameNode, value_textAlign);
}

void ResetSearchTextAlign(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SearchModelNG::SetTextAlign(frameNode, TextAlign::START);
}

void SetSearchCancelButton(ArkUINodeHandle node,
    ArkUI_Int32 style, const struct ArkUISizeType* size, ArkUI_Uint32 color, ArkUI_CharPtr src)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SearchModelNG::SetCancelButtonStyle(frameNode, static_cast<CancelButtonStyle>(style));
    NG::IconOptions cancelIconOptions = NG::IconOptions(
        Color(color), Dimension(size->value, static_cast<DimensionUnit>(size->unit)), std::string(src), "", "");
    SearchModelNG::SetCancelImageIcon(frameNode, cancelIconOptions);
}

void ResetSearchCancelButton(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SearchModelNG::SetCancelButtonStyle(frameNode, DEFAULT_CANCEL_BUTTON_STYLE);
}

void SetSearchEnableKeyboardOnFocus(ArkUINodeHandle node, ArkUI_Uint32 value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SearchModelNG::RequestKeyboardOnFocus(frameNode, static_cast<bool>(value));
}

void ResetSearchEnableKeyboardOnFocus(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SearchModelNG::RequestKeyboardOnFocus(frameNode, true);
}

void SetSearchPlaceholderFont(ArkUINodeHandle node, const struct ArkUIFontStruct* value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    Font font;
    font.fontSize = Dimension(value->fontSizeNumber, static_cast<DimensionUnit>(value->fontSizeUnit));
    font.fontWeight = static_cast<FontWeight>(value->fontWeight);
    font.fontFamilies.assign(value->fontFamilies, value->fontFamilies + value->familyLength);
    font.fontStyle = static_cast<OHOS::Ace::FontStyle>(value->fontStyle);

    SearchModelNG::SetPlaceholderFont(frameNode, font);
}

void ResetSearchPlaceholderFont(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    Font font;
    font.fontSize = THEME_SEARCH_FONT_SIZE;
    font.fontWeight = DEFAULT_FONT_WEIGHT;
    font.fontStyle = DEFAULT_FONT_STYLE;
    SearchModelNG::SetPlaceholderFont(frameNode, font);
}

void SetSearchSearchIcon(ArkUINodeHandle node, const struct ArkUIIconOptionsStruct* value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    Color iconColor;
    if (value->color != INVALID_COLOR_VALUE) {
        iconColor = Color(value->color);
    }

    NG::IconOptions cancelInconOptions = NG::IconOptions(
        iconColor, Dimension(value->value, static_cast<DimensionUnit>(value->unit)), std::string(value->src), "", "");
    SearchModelNG::SetSearchImageIcon(frameNode, cancelInconOptions);
}

void ResetSearchSearchIcon(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SearchModelNG::SetSearchSrcPath(frameNode, "");
}

void SetSearchSearchButton(ArkUINodeHandle node, const struct ArkUISearchButtonOptionsStruct* value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SearchModelNG::SetSearchButton(frameNode, value->value);
    SearchModelNG::SetSearchButtonFontSize(frameNode, CalcDimension(value->sizeValue,
        static_cast<DimensionUnit>(value->sizeUnit)));
    SearchModelNG::SetSearchButtonFontColor(frameNode, Color(value->fontColor));
    SearchModelNG::SetSearchButtonAutoDisable(frameNode, value->autoDisable);
}

void ResetSearchSearchButton(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SearchModelNG::SetSearchButton(frameNode, "");
}

void SetSearchFontColor(ArkUINodeHandle node, ArkUI_Uint32 value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SearchModelNG::SetTextColor(frameNode, Color(value));
}

void ResetSearchFontColor(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SearchModelNG::SetTextColor(frameNode, THEME_SEARCH_TEXT_COLOR);
}

void SetSearchCopyOption(ArkUINodeHandle node, ArkUI_Uint32 value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto copyOptions = CopyOptions::Local;
    copyOptions = static_cast<CopyOptions>(value);
    SearchModelNG::SetCopyOption(frameNode, copyOptions);
}

void ResetSearchCopyOption(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto copyOptions = CopyOptions::Local;
    SearchModelNG::SetCopyOption(frameNode, copyOptions);
}

void SetSearchEnterKeyType(ArkUINodeHandle node, ArkUI_Int32 value)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    SearchModelNG::SetSearchEnterKeyType(frameNode, CastToTextInputAction(value));
}

void ResetSearchEnterKeyType(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    SearchModelNG::SetSearchEnterKeyType(frameNode, TextInputAction::SEARCH);
}

void SetSearchHeight(ArkUINodeHandle node, ArkUI_Float32 heightValue, ArkUI_Int32 heightUnit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SearchModelNG::SetHeight(frameNode, CalcDimension(heightValue, (DimensionUnit)heightUnit));
}

void ResetSearchHeight(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::ClearWidthOrHeight(frameNode, false);
}

void SetSearchFontFeature(ArkUINodeHandle node, ArkUI_CharPtr value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::string strValue = value;
    SearchModelNG::SetFontFeature(frameNode, ParseFontFeatureSettings(strValue));
}

void ResetSearchFontFeature(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::string strValue = "";
    SearchModelNG::SetFontFeature(frameNode, ParseFontFeatureSettings(strValue));
}

void SetSearchInspectorId(ArkUINodeHandle node, ArkUI_CharPtr key)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SearchModelNG::SetId(frameNode, key);
}

void ResetSearchInspectorId(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SearchModelNG::SetId(frameNode, "");
}

void SetSearchDecoration(ArkUINodeHandle node, ArkUI_Int32 decoration, ArkUI_Uint32 color, ArkUI_Int32 style)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SearchModelNG::SetTextDecoration(frameNode, static_cast<TextDecoration>(decoration));
    SearchModelNG::SetTextDecorationColor(frameNode, Color(color));
    SearchModelNG::SetTextDecorationStyle(frameNode, static_cast<TextDecorationStyle>(style));
}

void ResetSearchDecoration(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SearchModelNG::SetTextDecoration(frameNode, DEFAULT_TEXT_DECORATION);
    SearchModelNG::SetTextDecorationColor(frameNode, DEFAULT_DECORATION_COLOR);
    SearchModelNG::SetTextDecorationStyle(frameNode, DEFAULT_DECORATION_STYLE);
}

void SetSearchLetterSpacing(ArkUINodeHandle node, ArkUI_Float32 value, ArkUI_Int32 unit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SearchModelNG::SetLetterSpacing(frameNode, CalcDimension(value, (DimensionUnit)unit));
}

void ResetSearchLetterSpacing(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CalcDimension value;
    value.Reset();
    SearchModelNG::SetLetterSpacing(frameNode, value);
}
void SetSearchLineHeight(ArkUINodeHandle node, ArkUI_Float32 value, ArkUI_Int32 unit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SearchModelNG::SetLineHeight(frameNode, CalcDimension(value, (DimensionUnit)unit));
}
void ResetSearchLineHeight(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CalcDimension value;
    value.Reset();
    SearchModelNG::SetLineHeight(frameNode, value);
}

void SetSearchAdaptMinFontSize(ArkUINodeHandle node, ArkUI_Float32 value, ArkUI_Int32 unit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SearchModelNG::SetAdaptMinFontSize(frameNode, CalcDimension(value, (DimensionUnit)unit));
}

void ResetSearchAdaptMinFontSize(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto pipelineContext = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    auto theme = pipelineContext->GetTheme<SearchTheme>();
    CHECK_NULL_VOID(theme);
    CalcDimension minFontSize = theme->GetTextStyle().GetAdaptMinFontSize();
    SearchModelNG::SetAdaptMinFontSize(frameNode, minFontSize);
}

void SetSearchAdaptMaxFontSize(ArkUINodeHandle node, ArkUI_Float32 value, ArkUI_Int32 unit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SearchModelNG::SetAdaptMaxFontSize(frameNode, CalcDimension(value, (DimensionUnit)unit));
}

void ResetSearchAdaptMaxFontSize(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto pipelineContext = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    auto theme = pipelineContext->GetTheme<SearchTheme>();
    CHECK_NULL_VOID(theme);
    CalcDimension maxFontSize = theme->GetTextStyle().GetAdaptMaxFontSize();
    SearchModelNG::SetAdaptMaxFontSize(frameNode, maxFontSize);
}

void SetSearchSelectedBackgroundColor(ArkUINodeHandle node, ArkUI_Uint32 color)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    Color selectedColor = Color(color);
    if (selectedColor.GetAlpha() == DEFAULT_ALPHA) {
        // Default setting of 20% opacity
        selectedColor = selectedColor.ChangeOpacity(DEFAULT_OPACITY);
    }
    SearchModelNG::SetSelectedBackgroundColor(frameNode, selectedColor);
}

void ResetSearchSelectedBackgroundColor(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    Color selectedColor;
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<TextFieldTheme>();
    CHECK_NULL_VOID(theme);
    selectedColor = theme->GetSelectedColor();
    if (selectedColor.GetAlpha() == DEFAULT_ALPHA) {
        // Default setting of 20% opacity
        selectedColor = selectedColor.ChangeOpacity(DEFAULT_OPACITY);
    }
    SearchModelNG::SetSelectedBackgroundColor(frameNode, selectedColor);
}

void SetSearchTextIndent(ArkUINodeHandle node, ArkUI_Float32 number, ArkUI_Int32 unit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SearchModelNG::SetTextIndent(frameNode, Dimension(number, static_cast<DimensionUnit>(unit)));
}

void ResetSearchTextIndent(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SearchModelNG::SetTextIndent(frameNode, CalcDimension(0, DimensionUnit::VP));
}

void SetSearchMaxLength(ArkUINodeHandle node, ArkUI_Int32 value)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    SearchModelNG::SetMaxLength(frameNode, value);
}

void ResetSearchMaxLength(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    SearchModelNG::ResetMaxLength(frameNode);
}

void SetSearchType(ArkUINodeHandle node, ArkUI_Int32 value)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    SearchModelNG::SetType(frameNode, CastToTextInputType(value));
}

void ResetSearchType(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    SearchModelNG::SetType(frameNode, Ace::TextInputType::TEXT);
}

void SetSearchOnEditChange(ArkUINodeHandle node, void* callback)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (callback) {
        auto onEditChange = reinterpret_cast<std::function<void(bool)>*>(callback);
        SearchModelNG::SetOnEditChange(frameNode, std::move(*onEditChange));
    } else {
        SearchModelNG::SetOnEditChange(frameNode, nullptr);
    }
}

void ResetSearchOnEditChange(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SearchModelNG::SetOnEditChange(frameNode, nullptr);
}

void SetSearchOnSubmitWithEvent(ArkUINodeHandle node, void* callback)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (callback) {
        auto onSubmit =
            reinterpret_cast<std::function<void(const std::u16string&, NG::TextFieldCommonEvent&)>*>(callback);
        SearchModelNG::SetOnSubmit(frameNode, std::move(*onSubmit));
    } else {
        SearchModelNG::SetOnSubmit(frameNode, nullptr);
    }
}

void ResetSearchOnSubmitWithEvent(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    SearchModelNG::SetOnSubmit(frameNode, nullptr);
}

void SetSearchOnCopy(ArkUINodeHandle node, void* callback)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (callback) {
        auto onCopy = reinterpret_cast<std::function<void(const std::u16string&)>*>(callback);
        SearchModelNG::SetOnCopy(frameNode, std::move(*onCopy));
    } else {
        SearchModelNG::SetOnCopy(frameNode, nullptr);
    }
}

void ResetSearchOnCopy(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    SearchModelNG::SetOnCopy(frameNode, nullptr);
}

void SetSearchOnCut(ArkUINodeHandle node, void* callback)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (callback) {
        auto onCut = reinterpret_cast<std::function<void(const std::u16string&)>*>(callback);
        SearchModelNG::SetOnCut(frameNode, std::move(*onCut));
    } else {
        SearchModelNG::SetOnCut(frameNode, nullptr);
    }
}

void ResetSearchOnCut(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    SearchModelNG::SetOnCut(frameNode, nullptr);
}

void SetSearchOnPaste(ArkUINodeHandle node, void* callback)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (callback) {
        auto onPasteWithEvent = reinterpret_cast<std::function<void(
                const std::u16string&, NG::TextCommonEvent&)>*>(callback);
        SearchModelNG::SetOnPasteWithEvent(frameNode, std::move(*onPasteWithEvent));
    } else {
        SearchModelNG::SetOnPasteWithEvent(frameNode, nullptr);
    }
}

void ResetSearchOnPaste(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    SearchModelNG::SetOnPasteWithEvent(frameNode, nullptr);
}

void SetSearchOnChange(ArkUINodeHandle node, void* callback)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (callback) {
        auto onSubmit = reinterpret_cast<std::function<void(const std::u16string&, PreviewText&)>*>(callback);
        SearchModelNG::SetOnChange(frameNode, std::move(*onSubmit));
    } else {
        SearchModelNG::SetOnChange(frameNode, nullptr);
    }
}

void ResetSearchOnChange(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    SearchModelNG::SetOnChange(frameNode, nullptr);
}

void SetSearchOnTextSelectionChange(ArkUINodeHandle node, void* callback)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (callback) {
        auto onChange = reinterpret_cast<std::function<void(int32_t, int32_t)>*>(callback);
        SearchModelNG::SetOnTextSelectionChange(frameNode, std::move(*onChange));
    } else {
        SearchModelNG::SetOnTextSelectionChange(frameNode, nullptr);
    }
}

void ResetSearchOnTextSelectionChange(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    SearchModelNG::SetOnTextSelectionChange(frameNode, nullptr);
}

void SetSearchOnContentScroll(ArkUINodeHandle node, void* callback)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (callback) {
        auto onScroll = reinterpret_cast<std::function<void(float, float)>*>(callback);
        SearchModelNG::SetOnContentScroll(frameNode, std::move(*onScroll));
    } else {
        SearchModelNG::SetOnContentScroll(frameNode, nullptr);
    }
}

void ResetSearchOnContentScroll(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    SearchModelNG::SetOnContentScroll(frameNode, nullptr);
}

void SetSearchShowCounterOptions(
    ArkUINodeHandle node, ArkUI_Bool open, ArkUI_Int32 thresholdPercentage, ArkUI_Bool highlightBorder)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SearchModelNG::SetShowCounter(frameNode, open);
    SearchModelNG::SetCounterType(frameNode, thresholdPercentage);
    SearchModelNG::SetShowCounterBorder(frameNode, highlightBorder);
}

void ResetSearchShowCounterOptions(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    SearchModelNG::SetShowCounter(frameNode, false);
    SearchModelNG::SetCounterType(frameNode, -1);
    SearchModelNG::SetShowCounterBorder(frameNode, true);
}

ArkUINodeHandle GetSearchController(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, nullptr);
    auto controller = SearchModelNG::GetSearchController(frameNode);
    CHECK_NULL_RETURN(controller, nullptr);
    auto nodecontroller = reinterpret_cast<ArkUINodeHandle>(OHOS::Ace::AceType::RawPtr(controller));
    return nodecontroller;
}

void SetSearchValue(ArkUINodeHandle node, ArkUI_CharPtr value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::optional<std::string> valueNG = value;

    SearchModelNG::SetTextValue(frameNode, valueNG);
}

void ResetSearchValue(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SearchModelNG::SetTextValue(frameNode, "");
}

void SetSearchPlaceholder(ArkUINodeHandle node, ArkUI_CharPtr placeholder)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::optional<std::string> placeholderNG = placeholder;

    SearchModelNG::SetPlaceholder(frameNode, placeholderNG);
}

void ResetSearchPlaceholder(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SearchModelNG::SetPlaceholder(frameNode, "");
}

void SetSearchIcon(ArkUINodeHandle node, ArkUI_CharPtr icon)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::optional<std::string> iconNG = icon;

    SearchModelNG::SetIcon(frameNode, iconNG);
}

void ResetSearchIcon(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SearchModelNG::SetIcon(frameNode, "");
}

void SetSearchOnWillInsert(ArkUINodeHandle node, ArkUI_Int64 callback)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (callback) {
        auto onWillInsert = reinterpret_cast<std::function<bool(const InsertValueInfo&)>*>(callback);
        SearchModelNG::SetOnWillInsertValueEvent(frameNode, std::move(*onWillInsert));
    } else {
        SearchModelNG::SetOnWillInsertValueEvent(frameNode, nullptr);
    }
}

void ResetSearchOnWillInsert(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    SearchModelNG::SetOnWillInsertValueEvent(frameNode, nullptr);
}

void SetSearchOnDidInsert(ArkUINodeHandle node, ArkUI_Int64 callback)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (callback) {
        auto onDidInsert = reinterpret_cast<std::function<void(const InsertValueInfo&)>*>(callback);
        SearchModelNG::SetOnDidInsertValueEvent(frameNode, std::move(*onDidInsert));
    } else {
        SearchModelNG::SetOnDidInsertValueEvent(frameNode, nullptr);
    }
}

void ResetSearchOnDidInsert(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    SearchModelNG::SetOnDidInsertValueEvent(frameNode, nullptr);
}

void SetSearchOnWillDelete(ArkUINodeHandle node, ArkUI_Int64 callback)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (callback) {
        auto onWillDelete = reinterpret_cast<std::function<bool(const DeleteValueInfo&)>*>(callback);
        SearchModelNG::SetOnWillDeleteEvent(frameNode, std::move(*onWillDelete));
    } else {
        SearchModelNG::SetOnWillDeleteEvent(frameNode, nullptr);
    }
}

void ResetSearchOnWillDelete(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    SearchModelNG::SetOnWillDeleteEvent(frameNode, nullptr);
}

void SetSearchOnDidDelete(ArkUINodeHandle node, ArkUI_Int64 callback)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (callback) {
        auto onDidDelete = reinterpret_cast<std::function<void(const DeleteValueInfo&)>*>(callback);
        SearchModelNG::SetOnDidDeleteEvent(frameNode, std::move(*onDidDelete));
    } else {
        SearchModelNG::SetOnDidDeleteEvent(frameNode, nullptr);
    }
}

void ResetSearchOnDidDelete(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    SearchModelNG::SetOnDidDeleteEvent(frameNode, nullptr);
}

void SetSearchEnablePreviewText(ArkUINodeHandle node, ArkUI_Uint32 value)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    SearchModelNG::SetEnablePreviewText(frameNode, static_cast<bool>(value));
}

void ResetSearchEnablePreviewText(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    SearchModelNG::SetEnablePreviewText(frameNode, DEFAULT_ENABLE_PREVIEW_TEXT_VALUE);
}

void SetSearchCaretPosition(ArkUINodeHandle node, ArkUI_Int32 value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);

    SearchModelNG::SetCaretPosition(frameNode, value);
}

void ResetSearchCaretPosition(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);

    SearchModelNG::SetCaretPosition(frameNode, DEFAULT_CARET_POSITION);
}

void SetSearchSelectionMenuOptions(ArkUINodeHandle node, void* onCreateMenuCallback, void* onMenuItemClickCallback)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (onCreateMenuCallback) {
        NG::OnCreateMenuCallback onCreateMenu = *(reinterpret_cast<NG::OnCreateMenuCallback*>(onCreateMenuCallback));
        SearchModelNG::OnCreateMenuCallbackUpdate(frameNode, std::move(onCreateMenu));
    } else {
        SearchModelNG::OnCreateMenuCallbackUpdate(frameNode, nullptr);
    }
    if (onMenuItemClickCallback) {
        NG::OnMenuItemClickCallback onMenuItemClick =
            *(reinterpret_cast<NG::OnMenuItemClickCallback*>(onMenuItemClickCallback));
        SearchModelNG::OnMenuItemClickCallbackUpdate(frameNode, std::move(onMenuItemClick));
    } else {
        SearchModelNG::OnMenuItemClickCallbackUpdate(frameNode, nullptr);
    }
}

void ResetSearchSelectionMenuOptions(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NG::OnCreateMenuCallback onCreateMenuCallback;
    NG::OnMenuItemClickCallback onMenuItemClick;
    SearchModelNG::OnCreateMenuCallbackUpdate(frameNode, std::move(onCreateMenuCallback));
    SearchModelNG::OnMenuItemClickCallbackUpdate(frameNode, std::move(onMenuItemClick));
}

void SetSearchEnableHapticFeedback(ArkUINodeHandle node, ArkUI_Uint32 value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SearchModelNG::SetEnableHapticFeedback(frameNode, static_cast<bool>(value));
}

void ResetSearchEnableHapticFeedback(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SearchModelNG::SetEnableHapticFeedback(frameNode, DEFAULT_ENABLE_HAPTIC_FEEDBACK_VALUE);
}
namespace NodeModifier {
const ArkUISearchModifier* GetSearchModifier()
{
    constexpr auto lineBegin = __LINE__; // don't move this line
    static const ArkUISearchModifier modifier = {
        .setSearchPlaceholderColor = SetSearchPlaceholderColor,
        .resetSearchPlaceholderColor = ResetSearchPlaceholderColor,
        .setSearchTextFont = SetSearchTextFont,
        .resetSearchTextFont = ResetSearchTextFont,
        .setSearchSelectionMenuHidden = SetSearchSelectionMenuHidden,
        .resetSearchSelectionMenuHidden = ResetSearchSelectionMenuHidden,
        .setSearchCaretStyle = SetSearchCaretStyle,
        .resetSearchCaretStyle = ResetSearchCaretStyle,
        .setSearchTextAlign = SetSearchTextAlign,
        .resetSearchTextAlign = ResetSearchTextAlign,
        .setSearchCancelButton = SetSearchCancelButton,
        .resetSearchCancelButton = ResetSearchCancelButton,
        .setSearchEnableKeyboardOnFocus = SetSearchEnableKeyboardOnFocus,
        .resetSearchEnableKeyboardOnFocus = ResetSearchEnableKeyboardOnFocus,
        .setSearchPlaceholderFont = SetSearchPlaceholderFont,
        .resetSearchPlaceholderFont = ResetSearchPlaceholderFont,
        .setSearchSearchIcon = SetSearchSearchIcon,
        .resetSearchSearchIcon = ResetSearchSearchIcon,
        .setSearchSearchButton = SetSearchSearchButton,
        .resetSearchSearchButton = ResetSearchSearchButton,
        .setSearchFontColor = SetSearchFontColor,
        .resetSearchFontColor = ResetSearchFontColor,
        .setSearchCopyOption = SetSearchCopyOption,
        .resetSearchCopyOption = ResetSearchCopyOption,
        .setSearchEnterKeyType = SetSearchEnterKeyType,
        .resetSearchEnterKeyType = ResetSearchEnterKeyType,
        .setSearchHeight = SetSearchHeight,
        .resetSearchHeight = ResetSearchHeight,
        .setSearchInspectorId = SetSearchInspectorId,
        .resetSearchInspectorId = ResetSearchInspectorId,
        .setSearchDecoration = SetSearchDecoration,
        .resetSearchDecoration = ResetSearchDecoration,
        .setSearchLetterSpacing = SetSearchLetterSpacing,
        .resetSearchLetterSpacing = ResetSearchLetterSpacing,
        .setSearchLineHeight = SetSearchLineHeight,
        .resetSearchLineHeight = ResetSearchLineHeight,
        .setSearchFontFeature = SetSearchFontFeature,
        .resetSearchFontFeature = ResetSearchFontFeature,
        .setSearchAdaptMinFontSize = SetSearchAdaptMinFontSize,
        .resetSearchAdaptMinFontSize = ResetSearchAdaptMinFontSize,
        .setSearchAdaptMaxFontSize = SetSearchAdaptMaxFontSize,
        .resetSearchAdaptMaxFontSize = ResetSearchAdaptMaxFontSize,
        .setSearchSelectedBackgroundColor = SetSearchSelectedBackgroundColor,
        .resetSearchSelectedBackgroundColor = ResetSearchSelectedBackgroundColor,
        .setSearchTextIndent = SetSearchTextIndent,
        .resetSearchTextIndent = ResetSearchTextIndent,
        .setSearchValue = SetSearchValue,
        .resetSearchValue = ResetSearchValue,
        .setSearchPlaceholder = SetSearchPlaceholder,
        .resetSearchPlaceholder = ResetSearchPlaceholder,
        .setSearchIcon = SetSearchIcon,
        .resetSearchIcon = ResetSearchIcon,
        .setSearchCaretPosition = SetSearchCaretPosition,
        .resetSearchCaretPosition = ResetSearchCaretPosition,
        .setSearchMaxLength = SetSearchMaxLength,
        .resetSearchMaxLength = ResetSearchMaxLength,
        .setSearchType = SetSearchType,
        .resetSearchType = ResetSearchType,
        .setSearchOnEditChange = SetSearchOnEditChange,
        .resetSearchOnEditChange = ResetSearchOnEditChange,
        .setSearchOnSubmitWithEvent = SetSearchOnSubmitWithEvent,
        .resetSearchOnSubmitWithEvent = ResetSearchOnSubmitWithEvent,
        .setSearchOnCopy = SetSearchOnCopy,
        .resetSearchOnCopy = ResetSearchOnCopy,
        .setSearchOnCut = SetSearchOnCut,
        .resetSearchOnCut = ResetSearchOnCut,
        .setSearchOnPaste = SetSearchOnPaste,
        .resetSearchOnPaste = ResetSearchOnPaste,
        .setSearchOnChange = SetSearchOnChange,
        .resetSearchOnChange = ResetSearchOnChange,
        .setSearchOnTextSelectionChange = SetSearchOnTextSelectionChange,
        .resetSearchOnTextSelectionChange = ResetSearchOnTextSelectionChange,
        .setSearchOnContentScroll = SetSearchOnContentScroll,
        .resetSearchOnContentScroll = ResetSearchOnContentScroll,
        .setSearchShowCounter = SetSearchShowCounterOptions,
        .resetSearchShowCounter = ResetSearchShowCounterOptions,
        .getSearchController = GetSearchController,
        .setSearchOnWillInsert = SetSearchOnWillInsert,
        .resetSearchOnWillInsert = ResetSearchOnWillInsert,
        .setSearchOnDidInsert = SetSearchOnDidInsert,
        .resetSearchOnDidInsert = ResetSearchOnDidInsert,
        .setSearchOnWillDelete = SetSearchOnWillDelete,
        .resetSearchOnWillDelete = ResetSearchOnWillDelete,
        .setSearchOnDidDelete = SetSearchOnDidDelete,
        .resetSearchOnDidDelete = ResetSearchOnDidDelete,
        .setSearchEnablePreviewText = SetSearchEnablePreviewText,
        .resetSearchEnablePreviewText = ResetSearchEnablePreviewText,
        .setSearchSelectionMenuOptions = SetSearchSelectionMenuOptions,
        .resetSearchSelectionMenuOptions = ResetSearchSelectionMenuOptions,
        .setSearchEnableHapticFeedback = SetSearchEnableHapticFeedback,
        .resetSearchEnableHapticFeedback = ResetSearchEnableHapticFeedback,
    };
    constexpr auto lineEnd = __LINE__; // don't move this line
    constexpr auto ifdefOverhead = 4; // don't modify this line
    constexpr auto overHeadLines = 3; // don't modify this line
    constexpr auto blankLines = 0; // modify this line accordingly
    constexpr auto ifdefs = 0; // modify this line accordingly
    constexpr auto initializedFieldLines = lineEnd - lineBegin - ifdefs * ifdefOverhead - overHeadLines - blankLines;
    static_assert(initializedFieldLines == sizeof(modifier) / sizeof(void*),
        "ensure all fields are explicitly initialized");
    return &modifier;
}

const CJUISearchModifier* GetCJUISearchModifier()
{
    constexpr auto lineBegin = __LINE__; // don't move this line
    static const CJUISearchModifier modifier = {
        .setSearchPlaceholderColor = SetSearchPlaceholderColor,
        .resetSearchPlaceholderColor = ResetSearchPlaceholderColor,
        .setSearchTextFont = SetSearchTextFont,
        .resetSearchTextFont = ResetSearchTextFont,
        .setSearchSelectionMenuHidden = SetSearchSelectionMenuHidden,
        .resetSearchSelectionMenuHidden = ResetSearchSelectionMenuHidden,
        .setSearchCaretStyle = SetSearchCaretStyle,
        .resetSearchCaretStyle = ResetSearchCaretStyle,
        .setSearchTextAlign = SetSearchTextAlign,
        .resetSearchTextAlign = ResetSearchTextAlign,
        .setSearchCancelButton = SetSearchCancelButton,
        .resetSearchCancelButton = ResetSearchCancelButton,
        .setSearchEnableKeyboardOnFocus = SetSearchEnableKeyboardOnFocus,
        .resetSearchEnableKeyboardOnFocus = ResetSearchEnableKeyboardOnFocus,
        .setSearchPlaceholderFont = SetSearchPlaceholderFont,
        .resetSearchPlaceholderFont = ResetSearchPlaceholderFont,
        .setSearchSearchIcon = SetSearchSearchIcon,
        .resetSearchSearchIcon = ResetSearchSearchIcon,
        .setSearchSearchButton = SetSearchSearchButton,
        .resetSearchSearchButton = ResetSearchSearchButton,
        .setSearchFontColor = SetSearchFontColor,
        .resetSearchFontColor = ResetSearchFontColor,
        .setSearchCopyOption = SetSearchCopyOption,
        .resetSearchCopyOption = ResetSearchCopyOption,
        .setSearchEnterKeyType = SetSearchEnterKeyType,
        .resetSearchEnterKeyType = ResetSearchEnterKeyType,
        .setSearchHeight = SetSearchHeight,
        .resetSearchHeight = ResetSearchHeight,
        .setSearchFontFeature = SetSearchFontFeature,
        .resetSearchFontFeature = ResetSearchFontFeature,
        .setSearchDecoration = SetSearchDecoration,
        .resetSearchDecoration = ResetSearchDecoration,
        .setSearchLetterSpacing = SetSearchLetterSpacing,
        .resetSearchLetterSpacing = ResetSearchLetterSpacing,
        .setSearchLineHeight = SetSearchLineHeight,
        .resetSearchLineHeight = ResetSearchLineHeight,
        .setSearchAdaptMinFontSize = SetSearchAdaptMinFontSize,
        .resetSearchAdaptMinFontSize = ResetSearchAdaptMinFontSize,
        .setSearchAdaptMaxFontSize = SetSearchAdaptMaxFontSize,
        .resetSearchAdaptMaxFontSize = ResetSearchAdaptMaxFontSize,
        .setSearchSelectedBackgroundColor = SetSearchSelectedBackgroundColor,
        .resetSearchSelectedBackgroundColor = ResetSearchSelectedBackgroundColor,
        .setSearchTextIndent = SetSearchTextIndent,
        .resetSearchTextIndent = ResetSearchTextIndent,
        .setSearchMaxLength = SetSearchMaxLength,
        .resetSearchMaxLength = ResetSearchMaxLength,
        .setSearchType = SetSearchType,
        .resetSearchType = ResetSearchType,
        .setSearchOnEditChange = SetSearchOnEditChange,
        .resetSearchOnEditChange = ResetSearchOnEditChange,
        .setSearchOnSubmitWithEvent = SetSearchOnSubmitWithEvent,
        .resetSearchOnSubmitWithEvent = ResetSearchOnSubmitWithEvent,
        .setSearchOnCopy = SetSearchOnCopy,
        .resetSearchOnCopy = ResetSearchOnCopy,
        .setSearchOnCut = SetSearchOnCut,
        .resetSearchOnCut = ResetSearchOnCut,
        .setSearchOnPaste = SetSearchOnPaste,
        .resetSearchOnPaste = ResetSearchOnPaste,
        .setSearchOnChange = SetSearchOnChange,
        .resetSearchOnChange = ResetSearchOnChange,
        .setSearchOnTextSelectionChange = SetSearchOnTextSelectionChange,
        .resetSearchOnTextSelectionChange = ResetSearchOnTextSelectionChange,
        .setSearchOnContentScroll = SetSearchOnContentScroll,
        .resetSearchOnContentScroll = ResetSearchOnContentScroll,
        .setSearchShowCounter = SetSearchShowCounterOptions,
        .resetSearchShowCounter = ResetSearchShowCounterOptions,
        .getSearchController = GetSearchController,
        .setSearchValue = SetSearchValue,
        .resetSearchValue = ResetSearchValue,
        .setSearchPlaceholder = SetSearchPlaceholder,
        .resetSearchPlaceholder = ResetSearchPlaceholder,
        .setSearchIcon = SetSearchIcon,
        .resetSearchIcon = ResetSearchIcon,
        .setSearchOnWillInsert = SetSearchOnWillInsert,
        .resetSearchOnWillInsert = ResetSearchOnWillInsert,
        .setSearchOnDidInsert = SetSearchOnDidInsert,
        .resetSearchOnDidInsert = ResetSearchOnDidInsert,
        .setSearchOnWillDelete = SetSearchOnWillDelete,
        .resetSearchOnWillDelete = ResetSearchOnWillDelete,
        .setSearchOnDidDelete = SetSearchOnDidDelete,
        .resetSearchOnDidDelete = ResetSearchOnDidDelete,
        .setSearchEnablePreviewText = SetSearchEnablePreviewText,
        .resetSearchEnablePreviewText = ResetSearchEnablePreviewText,
        .setSearchCaretPosition = SetSearchCaretPosition,
        .resetSearchCaretPosition = ResetSearchCaretPosition,
    };
    constexpr auto lineEnd = __LINE__; // don't move this line
    constexpr auto ifdefOverhead = 4; // don't modify this line
    constexpr auto overHeadLines = 3; // don't modify this line
    constexpr auto blankLines = 0; // modify this line accordingly
    constexpr auto ifdefs = 0; // modify this line accordingly
    constexpr auto initializedFieldLines = lineEnd - lineBegin - ifdefs * ifdefOverhead - overHeadLines - blankLines;
    static_assert(initializedFieldLines == sizeof(modifier) / sizeof(void*),
        "ensure all fields are explicitly initialized");
    return &modifier;
}

void SetOnSearchSubmit(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto onEvent = [extraParam](const std::u16string& text, NG::TextFieldCommonEvent& commonEvent) {
        ArkUINodeEvent event;
        std::string utf8Text = UtfUtils::Str16ToStr8(text);
        event.kind = TEXT_INPUT;
        event.extraParam = reinterpret_cast<intptr_t>(extraParam);
        event.textInputEvent.subKind = ON_SEARCH_SUBMIT;
        event.textInputEvent.nativeStringPtr = reinterpret_cast<intptr_t>(utf8Text.c_str());
        SendArkUISyncEvent(&event);
    };
    SearchModelNG::SetOnSubmit(frameNode, std::move(onEvent));
}

void SetOnSearchChange(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto onEvent = [extraParam](const std::u16string& text, PreviewText&) {
        ArkUINodeEvent event;
        std::string utf8Text = UtfUtils::Str16ToStr8(text);
        event.kind = TEXT_INPUT;
        event.extraParam = reinterpret_cast<intptr_t>(extraParam);
        event.textInputEvent.subKind = ON_SEARCH_CHANGE;
        event.textInputEvent.nativeStringPtr = reinterpret_cast<intptr_t>(utf8Text.c_str());
        SendArkUISyncEvent(&event);
    };
    SearchModelNG::SetOnChange(frameNode, std::move(onEvent));
}

void SetOnSearchCopy(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto onEvent = [extraParam](const std::u16string& text) {
        ArkUINodeEvent event;
        std::string utf8Text = UtfUtils::Str16ToStr8(text);
        event.kind = TEXT_INPUT;
        event.extraParam = reinterpret_cast<intptr_t>(extraParam);
        event.textInputEvent.subKind = ON_SEARCH_COPY;
        event.textInputEvent.nativeStringPtr = reinterpret_cast<intptr_t>(utf8Text.c_str());
        SendArkUISyncEvent(&event);
    };
    SearchModelNG::SetOnCopy(frameNode, std::move(onEvent));
}

void SetOnSearchCut(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto onEvent = [extraParam](const std::u16string& text) {
        ArkUINodeEvent event;
        std::string utf8Text = UtfUtils::Str16ToStr8(text);
        event.kind = TEXT_INPUT;
        event.extraParam = reinterpret_cast<intptr_t>(extraParam);
        event.textInputEvent.subKind = ON_SEARCH_CUT;
        event.textInputEvent.nativeStringPtr = reinterpret_cast<intptr_t>(utf8Text.c_str());
        SendArkUISyncEvent(&event);
    };
    SearchModelNG::SetOnCut(frameNode, std::move(onEvent));
}

void SetOnSearchPaste(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto onEvent = [extraParam](const std::u16string& text, NG::TextCommonEvent& textEvent) {
        ArkUINodeEvent event;
        std::string utf8Text = UtfUtils::Str16ToStr8(text);
        event.kind = TEXT_INPUT;
        event.extraParam = reinterpret_cast<intptr_t>(extraParam);
        event.textInputEvent.subKind = ON_SEARCH_PASTE;
        event.textInputEvent.nativeStringPtr = reinterpret_cast<intptr_t>(utf8Text.c_str());
        SendArkUISyncEvent(&event);
    };
    SearchModelNG::SetOnPasteWithEvent(frameNode, std::move(onEvent));
}
}
} // namespace OHOS::Ace::NG
