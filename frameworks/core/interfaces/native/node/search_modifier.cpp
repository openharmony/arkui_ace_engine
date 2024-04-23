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

#include "base/geometry/dimension.h"
#include "base/utils/utils.h"
#include "bridge/common/utils/utils.h"
#include "core/components/common/properties/color.h"
#include "core/components/common/properties/text_style.h"
#include "core/components/search/search_theme.h"
#include "core/components/text_field/textfield_theme.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/search/search_model_ng.h"
#include "core/components/common/layout/constants.h"
#include "core/pipeline/base/element_register.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components/common/properties/alignment.h"
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
    SearchModelNG::SetCancelIconSize(frameNode,
        Dimension(size->value, static_cast<DimensionUnit>(size->unit)));
    SearchModelNG::SetCancelIconColor(frameNode, Color(color));
    std::string srcStr = std::string(src);
    SearchModelNG::SetRightIconSrcPath(frameNode, srcStr);
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
    SearchModelNG::SetSearchSrcPath(frameNode, value->src);
    SearchModelNG::SetSearchIconSize(frameNode, Dimension(value->value, static_cast<DimensionUnit>(value->unit)));
    if (value->color != INVALID_COLOR_VALUE) {
        SearchModelNG::SetSearchIconColor(frameNode, Color(value->color));
    }
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

namespace NodeModifier {
const ArkUISearchModifier* GetSearchModifier()
{
    static const ArkUISearchModifier modifier = { SetSearchPlaceholderColor, ResetSearchPlaceholderColor,
        SetSearchTextFont, ResetSearchTextFont, SetSearchSelectionMenuHidden, ResetSearchSelectionMenuHidden,
        SetSearchCaretStyle, ResetSearchCaretStyle, SetSearchTextAlign, ResetSearchTextAlign, SetSearchCancelButton,
        ResetSearchCancelButton, SetSearchEnableKeyboardOnFocus, ResetSearchEnableKeyboardOnFocus,
        SetSearchPlaceholderFont, ResetSearchPlaceholderFont, SetSearchSearchIcon, ResetSearchSearchIcon,
        SetSearchSearchButton, ResetSearchSearchButton, SetSearchFontColor, ResetSearchFontColor, SetSearchCopyOption,
        ResetSearchCopyOption, SetSearchEnterKeyType, ResetSearchEnterKeyType, SetSearchHeight, ResetSearchHeight,
        SetSearchInspectorId, ResetSearchInspectorId, SetSearchDecoration, ResetSearchDecoration,
        SetSearchLetterSpacing, ResetSearchLetterSpacing, SetSearchLineHeight, ResetSearchLineHeight,
        SetSearchFontFeature, ResetSearchFontFeature, SetSearchAdaptMinFontSize,
        ResetSearchAdaptMinFontSize, SetSearchAdaptMaxFontSize, ResetSearchAdaptMaxFontSize,
        SetSearchSelectedBackgroundColor, ResetSearchSelectedBackgroundColor, SetSearchTextIndent,
        ResetSearchTextIndent };
    return &modifier;
}
}
} // namespace OHOS::Ace::NG