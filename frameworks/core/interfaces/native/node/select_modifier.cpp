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
#include "core/interfaces/native/node/select_modifier.h"

#include "core/components/common/layout/constants.h"
#include "core/components/select/select_theme.h"
#include "core/components/text/text_theme.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_abstract_model_ng.h"
#include "core/components_ng/pattern/select/select_model_ng.h"
#include "core/pipeline/base/element_register.h"

namespace OHOS::Ace::NG {
const char DELIMITER = '|';
const char* ERR_CODE = "-1";
const int32_t SIZE_OF_FONT_INFO = 3;
const int32_t SIZE_OF_TWO = 2;
const int32_t DEFAULT_SELECT = 0;

void SetSpace(NodeHandle node, float value, int32_t unit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    Dimension space = Dimension(value, static_cast<DimensionUnit>(unit));
    SelectModelNG::SetSpace(frameNode, space);
}

void SetValue(NodeHandle node, const char* value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SelectModelNG::SetValue(frameNode, value);
}

void SetSelected(NodeHandle node, int32_t idx)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (idx < -1) {
        idx = -1;
    }
    SelectModelNG::SetSelected(frameNode, idx);
}

void SetSelectFontColor(NodeHandle node, const uint32_t color)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SelectModelNG::SetFontColor(frameNode, Color(color));
}

void SetSelectedOptionBgColor(NodeHandle node, const uint32_t color)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SelectModelNG::SetSelectedOptionBgColor(frameNode, Color(color));
}

void SetOptionBgColor(NodeHandle node, const uint32_t color)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SelectModelNG::SetOptionBgColor(frameNode, Color(color));
}

void SetOptionFontColor(NodeHandle node, const uint32_t color)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SelectModelNG::SetOptionFontColor(frameNode, Color(color));
}

void SetSelectedOptionFontColor(NodeHandle node, const uint32_t color)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SelectModelNG::SetSelectedOptionFontColor(frameNode, Color(color));
}

void SetArrowPosition(NodeHandle node, const int32_t arrowPosition)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SelectModelNG::SetArrowPosition(frameNode, static_cast<ArrowPosition>(arrowPosition));
}

void SetMenuAlign(
    NodeHandle node, const int32_t alignType, const float* values, const int32_t* units, const int32_t size)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    MenuAlign menuAlignObj;
    menuAlignObj.alignType = static_cast<MenuAlignType>(alignType);
    if (values != nullptr && units != nullptr && size == SIZE_OF_TWO) {
        Dimension dx = Dimension(values[0], static_cast<OHOS::Ace::DimensionUnit>(units[0]));
        Dimension dy = Dimension(values[1], static_cast<OHOS::Ace::DimensionUnit>(units[1]));

        menuAlignObj.offset = DimensionOffset(dx, dy);
    }
    SelectModelNG::SetMenuAlign(frameNode, menuAlignObj);
}

void SetFont(NodeHandle node, const char* fontInfo, int32_t styleVal)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);

    std::vector<std::string> res;
    std::string fontValues = std::string(fontInfo);
    StringUtils::StringSplitter(fontValues, DELIMITER, res);
    if (res.size() != SIZE_OF_FONT_INFO) {
        return;
    }

    auto selectTheme = GetTheme<SelectTheme>();
    CHECK_NULL_VOID(selectTheme);
    auto textTheme = GetTheme<TextTheme>();
    CHECK_NULL_VOID(textTheme);

    CalcDimension fontSize = selectTheme->GetFontSize();
    if (res[0] != ERR_CODE) { // 0: index of font size data
        fontSize = StringUtils::StringToCalcDimension(res[0], false, DimensionUnit::FP);
    }
    SelectModelNG::SetFontSize(frameNode, fontSize);

    FontWeight weight = FontWeight::MEDIUM;
    if (res[1] != ERR_CODE) { // 1: index of font weight data
        weight = StringUtils::StringToFontWeight(res[1], FontWeight::MEDIUM);
    }
    SelectModelNG::SetFontWeight(frameNode, weight);

    std::vector<std::string> fontFamilies = textTheme->GetTextStyle().GetFontFamilies();
    if (res[2] != ERR_CODE) { // 2: index of font family data
        fontFamilies = Framework::ConvertStrToFontFamilies(res[2]);
    }
    SelectModelNG::SetFontFamily(frameNode, fontFamilies);

    auto style = static_cast<Ace::FontStyle>(styleVal);
    SelectModelNG::SetItalicFontStyle(frameNode, style);
}

void SetOptionFont(NodeHandle node, const char* fontInfo, int32_t styleVal)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::vector<std::string> res;
    std::string fontValues = std::string(fontInfo);
    StringUtils::StringSplitter(fontValues, DELIMITER, res);
    if (res.size() != SIZE_OF_FONT_INFO) {
        return;
    }

    auto selectTheme = GetTheme<SelectTheme>();
    CHECK_NULL_VOID(selectTheme);
    auto textTheme = GetTheme<TextTheme>();
    CHECK_NULL_VOID(textTheme);

    CalcDimension fontSize = selectTheme->GetMenuFontSize();
    if (res[0] != ERR_CODE) { // 0: index of font size data
        fontSize = StringUtils::StringToCalcDimension(res[0], false, DimensionUnit::FP);
    }
    SelectModelNG::SetOptionFontSize(frameNode, fontSize);

    FontWeight weight = textTheme->GetTextStyle().GetFontWeight();
    if (res[1] != ERR_CODE) { // 1: index of font weight data
        weight = StringUtils::StringToFontWeight(res[1], FontWeight::REGULAR);
    }
    SelectModelNG::SetOptionFontWeight(frameNode, weight);

    std::vector<std::string> fontFamilies = textTheme->GetTextStyle().GetFontFamilies();
    if (res[2] != ERR_CODE) { // 2: index of font family data
        fontFamilies = Framework::ConvertStrToFontFamilies(res[2]);
    }
    SelectModelNG::SetOptionFontFamily(frameNode, fontFamilies);

    auto style = static_cast<Ace::FontStyle>(styleVal);
    SelectModelNG::SetOptionItalicFontStyle(frameNode, style);
}

void SetSelectedOptionFont(NodeHandle node, const char* fontInfo, int32_t styleVal)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::vector<std::string> res;
    std::string fontValues = std::string(fontInfo);
    StringUtils::StringSplitter(fontValues, DELIMITER, res);
    if (res.size() != SIZE_OF_FONT_INFO) {
        return;
    }

    auto selectTheme = GetTheme<SelectTheme>();
    CHECK_NULL_VOID(selectTheme);
    auto textTheme = GetTheme<TextTheme>();
    CHECK_NULL_VOID(textTheme);

    CalcDimension fontSize = selectTheme->GetFontSize();
    if (res[0] != ERR_CODE) { // 0: index of font size data
        fontSize = StringUtils::StringToCalcDimension(res[0], false, DimensionUnit::FP);
    }
    SelectModelNG::SetSelectedOptionFontSize(frameNode, fontSize);

    FontWeight weight = textTheme->GetTextStyle().GetFontWeight();
    if (res[1] != ERR_CODE) { // 1: index of font weight data
        weight = StringUtils::StringToFontWeight(res[1], FontWeight::REGULAR);
    }
    SelectModelNG::SetSelectedOptionFontWeight(frameNode, weight);

    std::vector<std::string> fontFamilies = textTheme->GetTextStyle().GetFontFamilies();
    if (res[2] != ERR_CODE) { // 2: index of font family data
        fontFamilies = Framework::ConvertStrToFontFamilies(res[2]);
    }
    SelectModelNG::SetSelectedOptionFontFamily(frameNode, fontFamilies);

    auto style = static_cast<Ace::FontStyle>(styleVal);
    SelectModelNG::SetSelectedOptionItalicFontStyle(frameNode, style);
}

void ResetSpace(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto selectTheme = GetTheme<SelectTheme>();
    CHECK_NULL_VOID(selectTheme);
    Dimension space = selectTheme->GetContentSpinnerPadding();
    SelectModelNG::SetSpace(frameNode, space);
}

void ResetValue(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SelectModelNG::SetValue(frameNode, "");
}

void ResetSelected(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SelectModelNG::SetSelected(frameNode, DEFAULT_SELECT);
}

void ResetSelectFontColor(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto selectTheme = GetTheme<SelectTheme>();
    CHECK_NULL_VOID(selectTheme);
    SelectModelNG::SetFontColor(frameNode, selectTheme->GetFontColor());
}

void ResetSelectedOptionBgColor(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto selectTheme = GetTheme<SelectTheme>();
    CHECK_NULL_VOID(selectTheme);
    SelectModelNG::SetSelectedOptionBgColor(frameNode, selectTheme->GetSelectedColor());
}

void ResetOptionBgColor(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto selectTheme = GetTheme<SelectTheme>();
    CHECK_NULL_VOID(selectTheme);
    SelectModelNG::SetOptionBgColor(frameNode, selectTheme->GetBackgroundColor());
}

void ResetOptionFontColor(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto selectTheme = GetTheme<SelectTheme>();
    CHECK_NULL_VOID(selectTheme);
    SelectModelNG::SetOptionFontColor(frameNode, selectTheme->GetMenuFontColor());
}

void ResetSelectedOptionFontColor(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto selectTheme = GetTheme<SelectTheme>();
    CHECK_NULL_VOID(selectTheme);
    SelectModelNG::SetSelectedOptionFontColor(frameNode, selectTheme->GetSelectedColorText());
}

void ResetArrowPosition(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SelectModelNG::SetArrowPosition(frameNode, ArrowPosition::END);
}

void ResetMenuAlign(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    MenuAlign menuAlignObj;
    SelectModelNG::SetMenuAlign(frameNode, menuAlignObj);
}

void ResetFont(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);

    auto selectTheme = GetTheme<SelectTheme>();
    CHECK_NULL_VOID(selectTheme);
    auto textTheme = GetTheme<TextTheme>();
    CHECK_NULL_VOID(textTheme);

    SelectModelNG::SetFontSize(frameNode, selectTheme->GetFontSize());
    SelectModelNG::SetFontWeight(frameNode, FontWeight::MEDIUM);
    SelectModelNG::SetFontFamily(frameNode, textTheme->GetTextStyle().GetFontFamilies());
    SelectModelNG::SetItalicFontStyle(frameNode, textTheme->GetTextStyle().GetFontStyle());
}

void ResetOptionFont(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);

    auto selectTheme = GetTheme<SelectTheme>();
    CHECK_NULL_VOID(selectTheme);
    auto textTheme = GetTheme<TextTheme>();
    CHECK_NULL_VOID(textTheme);

    SelectModelNG::SetOptionFontSize(frameNode, selectTheme->GetMenuFontSize());
    SelectModelNG::SetOptionFontWeight(frameNode, textTheme->GetTextStyle().GetFontWeight());
    SelectModelNG::SetOptionFontFamily(frameNode, textTheme->GetTextStyle().GetFontFamilies());
    SelectModelNG::SetOptionItalicFontStyle(frameNode, textTheme->GetTextStyle().GetFontStyle());
}

void ResetSelectedOptionFont(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);

    auto selectTheme = GetTheme<SelectTheme>();
    CHECK_NULL_VOID(selectTheme);
    auto textTheme = GetTheme<TextTheme>();
    CHECK_NULL_VOID(textTheme);

    SelectModelNG::SetSelectedOptionFontSize(frameNode, selectTheme->GetFontSize());
    SelectModelNG::SetSelectedOptionFontWeight(frameNode, textTheme->GetTextStyle().GetFontWeight());
    SelectModelNG::SetSelectedOptionFontFamily(frameNode, textTheme->GetTextStyle().GetFontFamilies());
    SelectModelNG::SetSelectedOptionItalicFontStyle(frameNode, textTheme->GetTextStyle().GetFontStyle());
}

void SetSelectOptionWidthFitTrigger(NodeHandle node, bool trigger)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SelectModelNG::SetOptionWidthFitTrigger(frameNode, trigger);
}

void SetSelectOptionWidth(NodeHandle node, const char* width)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    Dimension optionHeight = Dimension::FromString(std::string(width));
    SelectModelNG::SetOptionWidth(frameNode, optionHeight);
}

void ResetSelectOptionWidth(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    Dimension optionHeight;
    SelectModelNG::SetOptionWidth(frameNode, optionHeight);
}

void SetSelectOptionHeight(NodeHandle node, const char* height)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    Dimension optionHeight = Dimension::FromString(std::string(height));
    SelectModelNG::SetOptionHeight(frameNode, optionHeight);
}

void ResetSelectOptionHeight(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    Dimension optionHeight;
    SelectModelNG::SetOptionHeight(frameNode, optionHeight);
}

void SetSelectWidth(NodeHandle node, double value, int32_t unit, const char* calcVlaue)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto unitEnum = static_cast<OHOS::Ace::DimensionUnit>(unit);
    if (unitEnum == DimensionUnit::CALC) {
        ViewAbstract::SetWidth(
            frameNode, CalcLength(CalcLength(std::string(calcVlaue))));
    } else {
        ViewAbstract::SetWidth(frameNode, CalcLength(value, unitEnum));
    }
}

void ResetSelectWidth(NodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::ClearWidthOrHeight(frameNode, true);
}

void SetSelectHeight(NodeHandle node, double value, int32_t unit, const char* calcVlaue)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto unitEnum = static_cast<OHOS::Ace::DimensionUnit>(unit);
    if (unitEnum == DimensionUnit::CALC) {
        ViewAbstract::SetHeight(
            frameNode, CalcLength(CalcLength(std::string(calcVlaue))));
    } else {
        ViewAbstract::SetHeight(frameNode, CalcLength(value, unitEnum));
    }
}

void ResetSelectHeight(NodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::ClearWidthOrHeight(frameNode, false);
}

void SetSelectSize(NodeHandle node, const double* number, const int8_t* unit, const char** calc)
{
    CHECK_NULL_VOID(number);
    CHECK_NULL_VOID(unit);
    int32_t widthIndex = 0;
    int32_t heightIndex = 1;
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (*(unit + widthIndex) == static_cast<int8_t>(DimensionUnit::CALC) && *(calc + widthIndex) != nullptr) {
        ViewAbstract::SetWidth(frameNode, CalcLength(std::string(*(calc + widthIndex))));
    } else {
        ViewAbstract::SetWidth(
            frameNode, CalcLength(*(number + widthIndex), static_cast<DimensionUnit>(*(unit + widthIndex))));
    }
    if (*(unit + heightIndex) == static_cast<int8_t>(DimensionUnit::CALC) && *(calc + heightIndex) != nullptr) {
        ViewAbstract::SetHeight(frameNode, CalcLength(std::string(*(calc + heightIndex))));
    } else {
        ViewAbstract::SetHeight(
            frameNode, CalcLength(*(number + heightIndex), static_cast<DimensionUnit>(*(unit + heightIndex))));
    }
}

void ResetSelectSize(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::SetWidth(frameNode, CalcLength(0.0));
    ViewAbstract::SetHeight(frameNode, CalcLength(0.0));
}

ArkUISelectModifierAPI GetSelectModifier()
{
    static const ArkUISelectModifierAPI modifier = { SetSpace, SetValue, SetSelected, SetSelectFontColor,
        SetSelectedOptionBgColor, SetOptionBgColor, SetOptionFontColor, SetSelectedOptionFontColor, SetArrowPosition,
        SetMenuAlign, SetFont, SetOptionFont, SetSelectedOptionFont, ResetSpace, ResetValue, ResetSelected,
        ResetSelectFontColor, ResetSelectedOptionBgColor, ResetOptionBgColor, ResetOptionFontColor,
        ResetSelectedOptionFontColor, ResetArrowPosition, ResetMenuAlign, ResetFont, ResetOptionFont,
        ResetSelectedOptionFont, SetSelectWidth, ResetSelectWidth, SetSelectHeight, ResetSelectHeight, SetSelectSize,
        ResetSelectSize, SetSelectOptionWidthFitTrigger, SetSelectOptionWidth, ResetSelectOptionWidth,
        SetSelectOptionHeight, ResetSelectOptionHeight };

    return modifier;
}
} // namespace OHOS::Ace::NG