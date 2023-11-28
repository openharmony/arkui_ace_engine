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
#include "bridge/declarative_frontend/engine/jsi/components/arkts_native_search_modifier.h"

#include "base/geometry/dimension.h"
#include "base/utils/utils.h"
#include "bridge/common/utils/utils.h"
#include "bridge/declarative_frontend/jsview/js_view_abstract.h"
#include "core/components/common/properties/color.h"
#include "core/components/common/properties/text_style.h"
#include "core/components/text_field/textfield_theme.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/search/search_model_ng.h"
#include "core/components/common/layout/constants.h"
#include "core/pipeline/base/element_register.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components/common/properties/alignment.h"

namespace OHOS::Ace::NG {
constexpr uint32_t DEFAULT_SEARCH_COLOR = 0x99182431;
constexpr Dimension DEFAULT_FONT_SIZE = 16.0_fp;
constexpr FontWeight DEFAULT_FONT_WEIGHT = FontWeight::NORMAL;
constexpr Ace::FontStyle DEFAULT_FONT_STYLE = Ace::FontStyle::NORMAL;
const bool DEFAULT_SELECTION_MENU_HIDDEN = false;
constexpr CancelButtonStyle DEFAULT_CANCELBUTTON_STYLE = CancelButtonStyle::INPUT;
constexpr Dimension THEME_SEARCH_FONT_SIZE = Dimension(16.0, DimensionUnit::FP);
constexpr Color THEME_SEARCH_TEXT_COLOR = Color(0xe5000000);

bool StringToCalcDimensionNoPercent(std::string value, CalcDimension& result, DimensionUnit defaultUnit)
{
    if (value.back() == '%') {
        return false;
    }
    
    result = StringUtils::StringToCalcDimension(value, true, defaultUnit);
    if (result.Unit() == DimensionUnit::PERCENT) {
        return false;
    }
    return true;
}

void SetSearchTextFont(NodeHandle node, const struct FontStruct* value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    Font font;

    if (value->size == nullptr) {
        font.fontSize = DEFAULT_FONT_SIZE;
    } else if (value->size->valueStr != nullptr) {
        CalcDimension fontSize;
        if (StringToCalcDimensionNoPercent(value->size->valueStr, fontSize, DimensionUnit::FP)) {
            font.fontSize = fontSize;
        } else {
            font.fontSize = DEFAULT_FONT_SIZE;
        }
    } else {
        font.fontSize = CalcDimension(value->size->value, DimensionUnit::FP);
    }

    if (value->weight != nullptr) {
        std::string weightVal;
        if (value->weight->valueStr != nullptr) {
            weightVal = value->weight->valueStr;
        } else {
            weightVal = std::to_string(value->weight->value);
        }
        font.fontWeight = OHOS::Ace::Framework::ConvertStrToFontWeight(weightVal);
    } else {
        font.fontWeight = DEFAULT_FONT_WEIGHT;
    }

    if (value->family != nullptr) {
        font.fontFamilies = OHOS::Ace::Framework::ConvertStrToFontFamilies(value->family);
    }

    if (value->style != INVALID_FONT_STYLE) {
        OHOS::Ace::FontStyle styleVal = static_cast<OHOS::Ace::FontStyle>(value->style);
        font.fontStyle = styleVal;
    } else {
        font.fontStyle = DEFAULT_FONT_STYLE;
    }
    SearchModelNG::SetTextFont(frameNode, font);
}

void ResetSearchTextFont(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    Font font;
    font.fontSize = DEFAULT_FONT_SIZE;
    font.fontWeight = DEFAULT_FONT_WEIGHT;
    font.fontStyle = DEFAULT_FONT_STYLE;
    SearchModelNG::SetTextFont(frameNode, font);
}

void SetSearchPlaceholderColor(NodeHandle node, uint32_t color)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SearchModelNG::SetPlaceholderColor(frameNode, Color(color));
}

void ResetSearchPlaceholderColor(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SearchModelNG::SetPlaceholderColor(frameNode, Color(DEFAULT_SEARCH_COLOR));
}

void SetSearchSelectionMenuHidden(NodeHandle node, uint32_t selectionMenuHidden)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SearchModelNG::SetSelectionMenuHidden(frameNode, static_cast<bool>(selectionMenuHidden));
}

void ResetSearchSelectionMenuHidden(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SearchModelNG::SetSelectionMenuHidden(frameNode, DEFAULT_SELECTION_MENU_HIDDEN);
}

void SetSearchCaretStyle(NodeHandle node, const double number, const int8_t unit, uint32_t caretColor)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SearchModelNG::SetCaretWidth(frameNode, Dimension(number, static_cast<DimensionUnit>(unit)));
    SearchModelNG::SetCaretColor(frameNode, Color(caretColor));
}

void ResetSearchCaretStyle(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto textFieldTheme = Framework::JSViewAbstract::GetTheme<TextFieldTheme>();
    CHECK_NULL_VOID(textFieldTheme);
    CalcDimension caretWidth = textFieldTheme->GetCursorWidth();
    uint32_t caretColor = textFieldTheme->GetCursorColor().GetValue();
    SearchModelNG::SetCaretWidth(frameNode, Dimension(caretWidth.Value(), caretWidth.Unit()));
    SearchModelNG::SetCaretColor(frameNode, Color(caretColor));
}

void SetSearchTextAlign(NodeHandle node, int32_t value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextAlign value_textAlign = static_cast<TextAlign>(value);
    SearchModelNG::SetTextAlign(frameNode, value_textAlign);
}

void ResetSearchTextAlign(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SearchModelNG::SetTextAlign(frameNode, TextAlign::START);
}

void SetSearchCancelButton(NodeHandle node,
    int32_t style, const struct StringAndDouble* size, uint32_t color, const char* src)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SearchModelNG::SetCancelButtonStyle(frameNode, static_cast<CancelButtonStyle>(style));
    Dimension result;
    if (size->valueStr != nullptr) {
        result = StringUtils::StringToDimensionWithUnit(std::string(size->valueStr), DimensionUnit::VP);
        if (result.Unit() == DimensionUnit::PERCENT) {
            result.SetUnit(DimensionUnit::AUTO);
        }
        if (!LessNotEqual(result.Value(), 0.0)) {
            SearchModelNG::SetCancelIconSize(frameNode, result);
        }
    } else {
        result = CalcDimension(size->value, DimensionUnit::VP);
        SearchModelNG::SetCancelIconSize(frameNode, result);
    }
    if (color != INVALID_COLOR_VALUE) {
        SearchModelNG::SetCancelIconColor(frameNode, Color(color));
    }
    std::string srcStr = std::string(src);
    SearchModelNG::SetRightIconSrcPath(frameNode, srcStr);
}

void ResetSearchCancelButton(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SearchModelNG::SetCancelButtonStyle(frameNode, DEFAULT_CANCELBUTTON_STYLE);
}

void SetSearchEnableKeyboardOnFocus(NodeHandle node, uint32_t value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SearchModelNG::RequestKeyboardOnFocus(frameNode, static_cast<bool>(value));
}

void ResetSearchEnableKeyboardOnFocus(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SearchModelNG::RequestKeyboardOnFocus(frameNode, true);
}

void SetSearchPlaceholderFont(NodeHandle node, const struct FontStruct* value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    Font font;

    if (value->size == nullptr) {
        font.fontSize = THEME_SEARCH_FONT_SIZE;
    } else if (value->size->valueStr != nullptr) {
        CalcDimension fontSize;
        if (StringToCalcDimensionNoPercent(value->size->valueStr, fontSize, DimensionUnit::FP)) {
            font.fontSize = fontSize;
        } else {
            font.fontSize = THEME_SEARCH_FONT_SIZE;
        }
    } else {
        font.fontSize = CalcDimension(value->size->value, DimensionUnit::FP);
    }

    if (value->weight != nullptr) {
        std::string weightVal;
        if (value->weight->valueStr != nullptr) {
            weightVal = value->weight->valueStr;
        } else {
            weightVal = std::to_string(value->weight->value);
        }
        font.fontWeight = OHOS::Ace::Framework::ConvertStrToFontWeight(weightVal);
    }

    if (value->family != nullptr) {
        font.fontFamilies = OHOS::Ace::Framework::ConvertStrToFontFamilies(value->family);
    }

    if (value->style != INVALID_FONT_STYLE) {
        OHOS::Ace::FontStyle styleVal = static_cast<OHOS::Ace::FontStyle>(value->style);
        font.fontStyle = styleVal;
    }

    SearchModelNG::SetPlaceholderFont(frameNode, font);
}

void ResetSearchPlaceholderFont(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    Font font;
    font.fontSize = THEME_SEARCH_FONT_SIZE;
    SearchModelNG::SetPlaceholderFont(frameNode, font);
}

void SetSearchSearchIcon(NodeHandle node, const struct IconOptionsStruct* value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);

    CalcDimension iconSize;
    if (value->size != nullptr) {
        if (value->size->valueStr != nullptr) {
            StringToCalcDimensionNoPercent(value->size->valueStr, iconSize, DimensionUnit::FP);
        } else {
            iconSize = CalcDimension(value->size->value, DimensionUnit::VP);
        }
        SearchModelNG::SetSearchIconSize(frameNode, iconSize);
    }

    if (value->color != INVALID_COLOR_VALUE) {
        SearchModelNG::SetSearchIconColor(frameNode, Color(value->color));
    }

    if (value->src != nullptr) {
        SearchModelNG::SetSearchSrcPath(frameNode, value->src);
    } else {
        SearchModelNG::SetSearchSrcPath(frameNode, "");
    }
}

void ResetSearchSearchIcon(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SearchModelNG::SetSearchSrcPath(frameNode, "");
}

void SetSearchSearchButton(NodeHandle node, const struct SearchButtonOptionsStruct* value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);

    SearchModelNG::SetSearchButton(frameNode, value->value);

    CalcDimension fontSize;
    if (value->fontSize != nullptr) {
        if (value->fontSize->valueStr != nullptr &&
            StringToCalcDimensionNoPercent(value->fontSize->valueStr, fontSize, DimensionUnit::FP) &&
            GreatOrEqual(fontSize.Value(), 0.0)) {
            SearchModelNG::SetSearchButtonFontSize(frameNode, fontSize);
        } else {
            fontSize = CalcDimension(value->fontSize->value, DimensionUnit::FP);
            SearchModelNG::SetSearchButtonFontSize(frameNode, fontSize);
        }
    } else {
        SearchModelNG::SetSearchButtonFontSize(frameNode, THEME_SEARCH_FONT_SIZE);
    }

    if (value->fontColor != INVALID_COLOR_VALUE) {
        SearchModelNG::SetSearchButtonFontColor(frameNode, Color(value->fontColor));
    }
}

void ResetSearchSearchButton(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SearchModelNG::SetSearchButton(frameNode, "");
}

void SetSearchFontColor(NodeHandle node, uint32_t value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SearchModelNG::SetTextColor(frameNode, Color(value));
}

void ResetSearchFontColor(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SearchModelNG::SetTextColor(frameNode, THEME_SEARCH_TEXT_COLOR);
}

void SetSearchCopyOption(NodeHandle node, uint32_t value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto copyOptions = CopyOptions::None;
    copyOptions = static_cast<CopyOptions>(value);
    SearchModelNG::SetCopyOption(frameNode, copyOptions);
}

void ResetSearchCopyOption(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto copyOptions = CopyOptions::None;
    SearchModelNG::SetCopyOption(frameNode, copyOptions);
}

ArkUISearchModifierAPI GetSearchModifier()
{
    static const ArkUISearchModifierAPI modifier = {
        SetSearchPlaceholderColor,
        ResetSearchPlaceholderColor,
        SetSearchTextFont,
        ResetSearchTextFont,
        SetSearchSelectionMenuHidden,
        ResetSearchSelectionMenuHidden,
        SetSearchCaretStyle,
        ResetSearchCaretStyle,
        SetSearchTextAlign,
        ResetSearchTextAlign,
        SetSearchCancelButton,
        ResetSearchCancelButton,
        SetSearchEnableKeyboardOnFocus,
        ResetSearchEnableKeyboardOnFocus,
        SetSearchPlaceholderFont,
        ResetSearchPlaceholderFont,
        SetSearchSearchIcon,
        ResetSearchSearchIcon,
        SetSearchSearchButton,
        ResetSearchSearchButton,
        SetSearchFontColor,
        ResetSearchFontColor,
        SetSearchCopyOption,
        ResetSearchCopyOption
    };

    return modifier;
}
} // namespace OHOS::Ace::NG