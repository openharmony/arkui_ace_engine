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
#include "bridge/declarative_frontend/engine/jsi/components/arkts_native_button_modifier.h"

#include <unordered_map>

#include "bridge/common/utils/utils.h"
#include "core/components/button/button_theme.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/text_style.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/pattern/button/button_model_ng.h"
#include "core/components_ng/pattern/button/button_request_data.h"
#include "core/pipeline/base/element_register.h"

namespace OHOS::Ace::NG {
constexpr int DEFAULT_BUTTON_TYPE = (int)ButtonType::CAPSULE;
constexpr bool DEFAULT_STATE_EFFECT = true;
constexpr Ace::FontWeight DEFAULT_FONT_WEIGHT = Ace::FontWeight::NORMAL;
constexpr Ace::FontStyle DEFAULT_FONT_STYLE = Ace::FontStyle::NORMAL;
constexpr int INDEX_TEXT_OVERFLOW_0 = 0;
constexpr int INDEX_MAX_LINES_1 = 1;
constexpr int INDEX_ADAPT_HEIGHT_2 = 2;
constexpr int INDEX_FONT_WEIGHT_3 = 3;
constexpr int INDEX_FONT_STYLE_4 = 4;
constexpr int INDEX_MIN_FONT_SIZE_0 = 0;
constexpr int INDEX_MAX_FONT_SIZE_1 = 1;
constexpr int INDEX_FONT_SIZE_2 = 2;
const std::string DEFAULT_FONT_FAMILY = "cursive";
const std::vector<TextOverflow> TEXT_OVERFLOWS = { TextOverflow::NONE, TextOverflow::CLIP, TextOverflow::ELLIPSIS,
    TextOverflow::MARQUEE };
const std::vector<Ace::FontStyle> FONT_STYLES = { Ace::FontStyle::NORMAL, Ace::FontStyle::ITALIC };
const std::vector<TextHeightAdaptivePolicy> HEIGHT_ADAPTIVE_POLICY = { TextHeightAdaptivePolicy::MAX_LINES_FIRST,
    TextHeightAdaptivePolicy::MIN_FONT_SIZE_FIRST, TextHeightAdaptivePolicy::LAYOUT_CONSTRAINT_FIRST };
const double PLACE_HOLDER_ARRAY = -10001;

const std::unordered_map<int, DimensionUnit> DIMENSION_UNIT_MAP = {
    { -2, DimensionUnit::INVALID },
    { -1, DimensionUnit::NONE },
    { 0, DimensionUnit::PX },
    { 1, DimensionUnit::VP },
    { 2, DimensionUnit::FP },
    { 3, DimensionUnit::PERCENT },
    { 4, DimensionUnit::LPX },
    { 5, DimensionUnit::AUTO },
    { 6, DimensionUnit::CALC },
};

const std::vector<FontWeight> BUTTON_FONT_WEIGHTS = {
    FontWeight::W100,
    FontWeight::W200,
    FontWeight::W300,
    FontWeight::W400,
    FontWeight::W500,
    FontWeight::W600,
    FontWeight::W700,
    FontWeight::W800,
    FontWeight::W900,
    FontWeight::BOLD,
    FontWeight::BOLDER,
    FontWeight::LIGHTER,
    FontWeight::MEDIUM,
    FontWeight::NORMAL,
    FontWeight::REGULAR,
};

void SetButtonType(NodeHandle node, int type)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if ((ButtonType)type == ButtonType::CAPSULE || (ButtonType)type == ButtonType::CIRCLE ||
        (ButtonType)type == ButtonType::ARC || (ButtonType)type == ButtonType::NORMAL) {
        ButtonModelNG::SetType(frameNode, type);
    }
}

void ResetButtonType(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ButtonModelNG::SetType(frameNode, DEFAULT_BUTTON_TYPE);
    return;
}

void SetButtonStateEffect(NodeHandle node, bool stateEffect)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ButtonModelNG::SetStateEffect(frameNode, stateEffect);
}

void ResetButtonStateEffect(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ButtonModelNG::SetStateEffect(frameNode, DEFAULT_STATE_EFFECT);
}

void SetButtonFontColor(NodeHandle node, uint32_t fontColor)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ButtonModelNG::SetFontColor(frameNode, Color(fontColor));
}

void ResetButtonFontColor(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto buttonTheme = pipeline->GetTheme<ButtonTheme>();
    CHECK_NULL_VOID(buttonTheme);
    Color textColor = buttonTheme->GetTextStyle().GetTextColor();
    ButtonModelNG::SetFontColor(frameNode, textColor);
}

void SetButtonFontSize(NodeHandle node, double fontSizeValue, int fontSizeUnit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ButtonModelNG::SetFontSize(frameNode, CalcDimension(fontSizeValue, (DimensionUnit)fontSizeUnit));
}

void ResetButtonFontSize(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto buttonTheme = pipeline->GetTheme<ButtonTheme>();
    CHECK_NULL_VOID(buttonTheme);
    CalcDimension fontSize = buttonTheme->GetTextStyle().GetFontSize();
    ButtonModelNG::SetFontSize(frameNode, fontSize);
}

void SetButtonFontWeight(NodeHandle node, const char* fontWeight)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::string fontWeightStr = fontWeight;
    ButtonModelNG::SetFontWeight(frameNode, Framework::ConvertStrToFontWeight(fontWeightStr));
}

void ResetButtonFontWeight(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ButtonModelNG::SetFontWeight(frameNode, DEFAULT_FONT_WEIGHT);
}

void SetButtonFontStyle(NodeHandle node, int32_t fontStyle)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ButtonModelNG::SetFontStyle(frameNode, FONT_STYLES[fontStyle]);
}

void ResetButtonFontStyle(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ButtonModelNG::SetFontStyle(frameNode, DEFAULT_FONT_STYLE);
}

void SetButtonFontFamily(NodeHandle node, const char* fontFamily)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::string familiesStr = fontFamily;
    std::vector<std::string> fontFamilyResult = Framework::ConvertStrToFontFamilies(familiesStr);
    ButtonModelNG::SetFontFamily(frameNode, fontFamilyResult);
}

void ResetButtonFontFamily(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::string familiesStr = DEFAULT_FONT_FAMILY;
    std::vector<std::string> fontFamilyResult = Framework::ConvertStrToFontFamilies(familiesStr);
    ButtonModelNG::SetFontFamily(frameNode, fontFamilyResult);
}

void ButtonCompleteParameters(ButtonParameters& buttonParameters)
{
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto buttonTheme = pipeline->GetTheme<ButtonTheme>();
    if (!buttonTheme) {
        return;
    }
    auto textStyle = buttonTheme->GetTextStyle();
    if (!buttonParameters.textOverflow.has_value()) {
        buttonParameters.textOverflow = TextOverflow::CLIP;
    }
    if (!buttonParameters.maxLines.has_value()) {
        buttonParameters.maxLines = buttonTheme->GetTextMaxLines();
    }
    if (!buttonParameters.minFontSize.has_value()) {
        buttonParameters.minFontSize = buttonTheme->GetMinFontSize();
    }
    if (!buttonParameters.maxFontSize.has_value()) {
        buttonParameters.maxFontSize = buttonTheme->GetMaxFontSize();
    }
    if (!buttonParameters.fontSize.has_value()) {
        buttonParameters.fontSize = textStyle.GetFontSize();
    }
    if (!buttonParameters.fontWeight.has_value()) {
        buttonParameters.fontWeight = textStyle.GetFontWeight();
    }
    if (!buttonParameters.fontStyle.has_value()) {
        buttonParameters.fontStyle = textStyle.GetFontStyle();
    }
    if (!buttonParameters.heightAdaptivePolicy.has_value()) {
        buttonParameters.heightAdaptivePolicy = TextHeightAdaptivePolicy::MAX_LINES_FIRST;
    }
}

void SetButtonLabelStyle(NodeHandle node, const char* fontFamily, const double* valueArray,
    const double* dimensionValueArray, const int* dimensionUnitArray)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ButtonParameters buttonParameters;
    if (valueArray != nullptr) {
        if (valueArray[INDEX_TEXT_OVERFLOW_0] != PLACE_HOLDER_ARRAY) {
            int index = valueArray[INDEX_TEXT_OVERFLOW_0];
            buttonParameters.textOverflow = TEXT_OVERFLOWS[index];
        }
        if (valueArray[INDEX_MAX_LINES_1] != PLACE_HOLDER_ARRAY) {
            buttonParameters.maxLines = valueArray[INDEX_MAX_LINES_1];
        }
        if (valueArray[INDEX_ADAPT_HEIGHT_2] != PLACE_HOLDER_ARRAY) {
            int index = valueArray[INDEX_ADAPT_HEIGHT_2];
            buttonParameters.heightAdaptivePolicy = HEIGHT_ADAPTIVE_POLICY[index];
        }
        if (valueArray[INDEX_FONT_WEIGHT_3] != PLACE_HOLDER_ARRAY) {
            int index = valueArray[INDEX_FONT_WEIGHT_3];
            buttonParameters.fontWeight = BUTTON_FONT_WEIGHTS[index];
        }
        if (valueArray[INDEX_FONT_STYLE_4] != PLACE_HOLDER_ARRAY) {
            int index = valueArray[INDEX_FONT_STYLE_4];
            buttonParameters.fontStyle = FONT_STYLES[index];
        }
    }
    if (dimensionValueArray != nullptr && dimensionUnitArray != nullptr) {
        if (dimensionValueArray[INDEX_MIN_FONT_SIZE_0] != PLACE_HOLDER_ARRAY) {
            buttonParameters.minFontSize = Dimension(dimensionValueArray[INDEX_MIN_FONT_SIZE_0],
                DIMENSION_UNIT_MAP.find(dimensionUnitArray[INDEX_MIN_FONT_SIZE_0])->second);
        }
        if (dimensionValueArray[INDEX_MAX_FONT_SIZE_1] != PLACE_HOLDER_ARRAY) {
            buttonParameters.maxFontSize = Dimension(dimensionValueArray[INDEX_MAX_FONT_SIZE_1],
                DIMENSION_UNIT_MAP.find(dimensionUnitArray[INDEX_MAX_FONT_SIZE_1])->second);
        }
        if (dimensionValueArray[INDEX_FONT_SIZE_2] != PLACE_HOLDER_ARRAY) {
            buttonParameters.fontSize = Dimension(dimensionValueArray[INDEX_FONT_SIZE_2],
                DIMENSION_UNIT_MAP.find(dimensionUnitArray[INDEX_FONT_SIZE_2])->second);
        }
    }
    std::string familiesStr = fontFamily;
    buttonParameters.fontFamily = Framework::ConvertStrToFontFamilies(familiesStr);
    ButtonModelNG::SetLableStyle(frameNode, buttonParameters);
}

void ResetButtonLabelStyle(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto buttonTheme = pipeline->GetTheme<ButtonTheme>();
    if (!buttonTheme) {
        return;
    }
    auto textStyle = buttonTheme->GetTextStyle();
    Ace::ButtonParameters buttonParameters;
    ButtonCompleteParameters(buttonParameters);
    ButtonModelNG::SetLableStyle(frameNode, buttonParameters);
}

ArkUIButtonModifierAPI GetButtonModifier()
{
    static const ArkUIButtonModifierAPI modifier = { SetButtonType, ResetButtonType, SetButtonStateEffect,
        ResetButtonStateEffect, SetButtonFontColor, ResetButtonFontColor, SetButtonFontSize, ResetButtonFontSize,
        SetButtonFontWeight, ResetButtonFontWeight, SetButtonFontStyle, ResetButtonFontStyle, SetButtonFontFamily,
        ResetButtonFontFamily, SetButtonLabelStyle, ResetButtonLabelStyle };

    return modifier;
}
} // namespace OHOS::Ace::NG