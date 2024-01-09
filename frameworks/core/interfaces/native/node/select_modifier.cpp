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
#include "core/components_ng/base/frame_node.h"
#include "core/pipeline/base/element_register.h"
#include "core/components/select/select_theme.h"
#include "core/components/text/text_theme.h"
#include "core/components_ng/pattern/select/select_model_ng.h"

namespace OHOS::Ace::NG {
const char DELIMITER = '|';
const int SIZE_OF_FONT_INFO = 3;
const int POS_0 = 0;
const int POS_1 = 1;
const int POS_2 = 1;
const char* ERR_CODE = "-1";
const int SIZE_OF_TWO = 2;
const int DEFAULT_SELECT = 0;

void SetSpace(NodeHandle node, float value, int unit)
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
    NodeHandle node, const int32_t alignType, const float* values, const int* units, const int32_t size)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    MenuAlign menuAlignObj;
    menuAlignObj.alignType = static_cast<MenuAlignType>(alignType);
    if (values != nullptr && units != nullptr && size == SIZE_OF_TWO) {
        Dimension dx = Dimension(values[POS_0], static_cast<OHOS::Ace::DimensionUnit>(units[POS_0]));
        Dimension dy = Dimension(values[POS_1], static_cast<OHOS::Ace::DimensionUnit>(units[POS_1]));

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

    auto context = frameNode->GetContext();
    CHECK_NULL_VOID(context);
    auto themeManager = context->GetThemeManager();
    CHECK_NULL_VOID(themeManager);

    auto selectTheme = themeManager->GetTheme<SelectTheme>();
    CHECK_NULL_VOID(selectTheme);
    auto textTheme = themeManager->GetTheme<TextTheme>();
    CHECK_NULL_VOID(textTheme);

    CalcDimension fontSize = selectTheme->GetFontSize();
    if (res[POS_0] != ERR_CODE) {
        fontSize = StringUtils::StringToCalcDimension(res[POS_0], false, DimensionUnit::FP);
    }
    SelectModelNG::SetFontSize(frameNode, fontSize);
   
    FontWeight weight = FontWeight::MEDIUM;
    if (res[POS_1] != ERR_CODE) {
        weight = StringUtils::StringToFontWeight(res[POS_1], FontWeight::MEDIUM);
    }
    SelectModelNG::SetFontWeight(frameNode, weight);

    std::vector<std::string> fontFamilies = textTheme->GetTextStyle().GetFontFamilies();
    if (res[POS_2] != ERR_CODE) {
        fontFamilies = Framework::ConvertStrToFontFamilies(res[POS_2]);
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

    auto context = frameNode->GetContext();
    CHECK_NULL_VOID(context);
    auto themeManager = context->GetThemeManager();
    CHECK_NULL_VOID(themeManager);

    auto selectTheme = themeManager->GetTheme<SelectTheme>();
    CHECK_NULL_VOID(selectTheme);
    auto textTheme = themeManager->GetTheme<TextTheme>();
    CHECK_NULL_VOID(textTheme);

    CalcDimension fontSize = selectTheme->GetMenuFontSize();
    if (res[POS_0] != ERR_CODE) {
        fontSize = StringUtils::StringToCalcDimension(res[POS_0], false, DimensionUnit::FP);
    }
    SelectModelNG::SetOptionFontSize(frameNode, fontSize);

    FontWeight weight = textTheme->GetTextStyle().GetFontWeight();
    if (res[POS_1] != ERR_CODE) {
        weight = StringUtils::StringToFontWeight(res[POS_1], FontWeight::REGULAR);
    }
    SelectModelNG::SetOptionFontWeight(frameNode, weight);
    
    std::vector<std::string> fontFamilies = textTheme->GetTextStyle().GetFontFamilies();
    if (res[POS_2] != ERR_CODE) {
        fontFamilies = Framework::ConvertStrToFontFamilies(res[POS_2]);
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
    
    auto context = frameNode->GetContext();
    CHECK_NULL_VOID(context);
    auto themeManager = context->GetThemeManager();
    CHECK_NULL_VOID(themeManager);

    auto selectTheme = themeManager->GetTheme<SelectTheme>();
    CHECK_NULL_VOID(selectTheme);
    auto textTheme = themeManager->GetTheme<TextTheme>();
    CHECK_NULL_VOID(textTheme);

    CalcDimension fontSize = selectTheme->GetFontSize();
    if (res[POS_0] != ERR_CODE) {
        fontSize = StringUtils::StringToCalcDimension(res[POS_0], false, DimensionUnit::FP);
    }
    SelectModelNG::SetSelectedOptionFontSize(frameNode, fontSize);

    FontWeight weight = textTheme->GetTextStyle().GetFontWeight();
    if (res[POS_1] != ERR_CODE) {
        weight = StringUtils::StringToFontWeight(res[POS_1], FontWeight::REGULAR);
    }
    SelectModelNG::SetSelectedOptionFontWeight(frameNode, weight);

    std::vector<std::string> fontFamilies = textTheme->GetTextStyle().GetFontFamilies();
    if (res[POS_2] != ERR_CODE) {
        fontFamilies = Framework::ConvertStrToFontFamilies(res[POS_2]);
    }
    SelectModelNG::SetSelectedOptionFontFamily(frameNode, fontFamilies);

    auto style = static_cast<Ace::FontStyle>(styleVal);
    SelectModelNG::SetSelectedOptionItalicFontStyle(frameNode, style);
}

void ResetSpace(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto context = frameNode->GetContext();
    CHECK_NULL_VOID(context);
    auto themeManager = context->GetThemeManager();
    CHECK_NULL_VOID(themeManager);
    auto selectTheme = themeManager->GetTheme<SelectTheme>();
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
    auto context = frameNode->GetContext();
    CHECK_NULL_VOID(context);
    auto themeManager = context->GetThemeManager();
    CHECK_NULL_VOID(themeManager);
    auto selectTheme = themeManager->GetTheme<SelectTheme>();
    CHECK_NULL_VOID(selectTheme);
    SelectModelNG::SetFontColor(frameNode, selectTheme->GetFontColor());
}

void ResetSelectedOptionBgColor(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto context = frameNode->GetContext();
    CHECK_NULL_VOID(context);
    auto themeManager = context->GetThemeManager();
    CHECK_NULL_VOID(themeManager);
    auto selectTheme = themeManager->GetTheme<SelectTheme>();
    CHECK_NULL_VOID(selectTheme);
    SelectModelNG::SetSelectedOptionBgColor(frameNode, selectTheme->GetSelectedColor());
}

void ResetOptionBgColor(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto context = frameNode->GetContext();
    CHECK_NULL_VOID(context);
    auto themeManager = context->GetThemeManager();
    CHECK_NULL_VOID(themeManager);
    auto selectTheme = themeManager->GetTheme<SelectTheme>();
    CHECK_NULL_VOID(selectTheme);
    SelectModelNG::SetOptionBgColor(frameNode, selectTheme->GetBackgroundColor());
}

void ResetOptionFontColor(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto context = frameNode->GetContext();
    CHECK_NULL_VOID(context);
    auto themeManager = context->GetThemeManager();
    CHECK_NULL_VOID(themeManager);
    auto selectTheme = themeManager->GetTheme<SelectTheme>();
    CHECK_NULL_VOID(selectTheme);
    SelectModelNG::SetOptionFontColor(frameNode, selectTheme->GetMenuFontColor());
}

void ResetSelectedOptionFontColor(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto context = frameNode->GetContext();
    CHECK_NULL_VOID(context);
    auto themeManager = context->GetThemeManager();
    CHECK_NULL_VOID(themeManager);
    auto selectTheme = themeManager->GetTheme<SelectTheme>();
    CHECK_NULL_VOID(selectTheme);
    SelectModelNG::SetSelectedOptionFontColor(frameNode, selectTheme->GetSelectedColorText());
}

void ResetArrowPosition (NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SelectModelNG::SetArrowPosition(frameNode, ArrowPosition::END);
}

void ResetMenuAlign (NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    MenuAlign menuAlignObj;
    SelectModelNG::SetMenuAlign(frameNode, menuAlignObj);
}

void ResetFont (NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto context = frameNode->GetContext();
    CHECK_NULL_VOID(context);
    auto themeManager = context->GetThemeManager();
    CHECK_NULL_VOID(themeManager);

    auto selectTheme = themeManager->GetTheme<SelectTheme>();
    CHECK_NULL_VOID(selectTheme);
    auto textTheme = themeManager->GetTheme<TextTheme>();
    CHECK_NULL_VOID(textTheme);

    SelectModelNG::SetFontSize(frameNode, selectTheme->GetFontSize());
    SelectModelNG::SetFontWeight(frameNode, FontWeight::MEDIUM);
    SelectModelNG::SetFontFamily(frameNode, textTheme->GetTextStyle().GetFontFamilies());
    SelectModelNG::SetItalicFontStyle(frameNode, textTheme->GetTextStyle().GetFontStyle());
}

void ResetOptionFont (NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto context = frameNode->GetContext();
    CHECK_NULL_VOID(context);
    auto themeManager = context->GetThemeManager();
    CHECK_NULL_VOID(themeManager);

    auto selectTheme = themeManager->GetTheme<SelectTheme>();
    CHECK_NULL_VOID(selectTheme);
    auto textTheme = themeManager->GetTheme<TextTheme>();
    CHECK_NULL_VOID(textTheme);

    SelectModelNG::SetOptionFontSize(frameNode, selectTheme->GetMenuFontSize());
    SelectModelNG::SetOptionFontWeight(frameNode, textTheme->GetTextStyle().GetFontWeight());
    SelectModelNG::SetOptionFontFamily(frameNode, textTheme->GetTextStyle().GetFontFamilies());
    SelectModelNG::SetOptionItalicFontStyle(frameNode, textTheme->GetTextStyle().GetFontStyle());
}

void ResetSelectedOptionFont (NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto context = frameNode->GetContext();
    CHECK_NULL_VOID(context);
    auto themeManager = context->GetThemeManager();
    CHECK_NULL_VOID(themeManager);

    auto selectTheme = themeManager->GetTheme<SelectTheme>();
    CHECK_NULL_VOID(selectTheme);
    auto textTheme = themeManager->GetTheme<TextTheme>();
    CHECK_NULL_VOID(textTheme);

    SelectModelNG::SetSelectedOptionFontSize(frameNode, selectTheme->GetFontSize());
    SelectModelNG::SetSelectedOptionFontWeight(frameNode, textTheme->GetTextStyle().GetFontWeight());
    SelectModelNG::SetSelectedOptionFontFamily(frameNode, textTheme->GetTextStyle().GetFontFamilies());
    SelectModelNG::SetSelectedOptionItalicFontStyle(frameNode, textTheme->GetTextStyle().GetFontStyle());
}

ArkUISelectModifierAPI GetSelectModifier()
{
    static const ArkUISelectModifierAPI modifier = {SetSpace, SetValue, SetSelected,
        SetSelectFontColor, SetSelectedOptionBgColor, SetOptionBgColor, SetOptionFontColor,
        SetSelectedOptionFontColor, SetArrowPosition, SetMenuAlign, SetFont, SetOptionFont,
        SetSelectedOptionFont, ResetSpace, ResetValue, ResetSelected,
        ResetSelectFontColor, ResetSelectedOptionBgColor, ResetOptionBgColor, ResetOptionFontColor,
        ResetSelectedOptionFontColor, ResetArrowPosition, ResetMenuAlign, ResetFont, ResetOptionFont,
        ResetSelectedOptionFont };

    return modifier;
}
} // namespace OHOS::Ace::NG