/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
#include "core/interfaces/native/node/node_indicator_modifier.h"

#include "base/geometry/calc_dimension.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/pattern/swiper_indicator/indicator_common/indicator_model_ng.h"
#include "core/pipeline/base/element_register.h"

namespace OHOS::Ace::NG {
constexpr int32_t INDICATOR_TYPE_INDEX = 0;
constexpr int32_t DEFAULT_DISPLAY_COUNT = 1;
constexpr int32_t DIGIT_INDICATOR_LEFT = 7;
constexpr int32_t DIGIT_INDICATOR_TOP = 8;
constexpr int32_t DIGIT_INDICATOR_RIGHT = 9;
constexpr int32_t DIGIT_INDICATOR_BOTTOM = 10;
constexpr int32_t DIGIT_INDICATOR_FONT_COLOR = 1;
constexpr int32_t DIGIT_INDICATOR_SELECTED_FONT_COLOR = 2;
constexpr int32_t DIGIT_INDICATOR_DIGIT_FONT_SIZE = 3;
constexpr int32_t DIGIT_INDICATOR_DIGIT_FONT_WEIGHT = 4;
constexpr int32_t DIGIT_INDICATOR_SELECTED_DIGIT_FONT_SIZE = 5;
constexpr int32_t DIGIT_INDICATOR_SELECTED_DIGIT_FONT_WEIGHT = 6;
constexpr int32_t DOT_INDICATOR_ITEM_WIDTH = 1;
constexpr int32_t DOT_INDICATOR_ITEM_HEIGHT = 2;
constexpr int32_t DOT_INDICATOR_SELECTED_ITEM_WIDTH = 3;
constexpr int32_t DOT_INDICATOR_SELECTED_ITEM_HEIGHT = 4;
constexpr int32_t DOT_INDICATOR_MASK = 5;
constexpr int32_t DOT_INDICATOR_COLOR = 6;
constexpr int32_t DOT_INDICATOR_SELECTED_COLOR = 7;
constexpr int32_t DOT_INDICATOR_LEFT = 8;
constexpr int32_t DOT_INDICATOR_TOP = 9;
constexpr int32_t DOT_INDICATOR_RIGHT = 10;
constexpr int32_t DOT_INDICATOR_BOTTOM = 11;
constexpr int32_t DOT_INDICATOR_INFO_SIZE = 11;
constexpr int32_t DOT_INDICATOR_MAX_DISPLAY_COUNT = 12;
namespace {

std::optional<Dimension> ParseIndicatorDimension(const std::string& value)
{
    std::optional<Dimension> indicatorDimension;
    if (value.empty()) {
        return indicatorDimension;
    }
    CalcDimension dimPosition = StringUtils::StringToCalcDimension(value, false, DimensionUnit::VP);
    indicatorDimension = LessNotEqual(dimPosition.ConvertToPx(), 0.0f) ? 0.0_vp : dimPosition;
    return indicatorDimension;
}

void GetFontContent(
    const std::string& size, const std::string& weight, bool isSelected, SwiperDigitalParameters& digitalParameters)
{
    auto pipelineContext = PipelineBase::GetCurrentContextSafely();
    CHECK_NULL_VOID(pipelineContext);
    auto indicatorTheme = pipelineContext->GetTheme<SwiperIndicatorTheme>();
    CHECK_NULL_VOID(indicatorTheme);
    CalcDimension fontSize = StringUtils::StringToCalcDimension(size, false, DimensionUnit::VP);
    if (LessOrEqual(fontSize.Value(), 0.0) || fontSize.Unit() == DimensionUnit::PERCENT) {
        fontSize = indicatorTheme->GetDigitalIndicatorTextStyle().GetFontSize();
    }
    if (isSelected) {
        digitalParameters.selectedFontSize = fontSize;
    } else {
        digitalParameters.fontSize = fontSize;
    }
    if (!weight.empty()) {
        if (isSelected) {
            digitalParameters.selectedFontWeight = StringUtils::StringToFontWeight(weight, FontWeight::NORMAL);
        } else {
            digitalParameters.fontWeight = StringUtils::StringToFontWeight(weight, FontWeight::NORMAL);
        }
    } else {
        if (isSelected) {
            digitalParameters.selectedFontWeight = indicatorTheme->GetDigitalIndicatorTextStyle().GetFontWeight();
        } else {
            digitalParameters.fontWeight = indicatorTheme->GetDigitalIndicatorTextStyle().GetFontWeight();
        }
    }
}

std::string GetInfoFromVectorByIndex(const std::vector<std::string>& dotIndicatorInfo, int32_t index)
{
    auto dotIndicatorInfoSize = dotIndicatorInfo.size();
    return dotIndicatorInfoSize < DOT_INDICATOR_INFO_SIZE
               ? ""
               : (dotIndicatorInfo[index] == "-" ? "" : dotIndicatorInfo[index]);
}

SwiperDigitalParameters GetDigitIndicatorInfo(const std::vector<std::string>& digitIndicatorInfo)
{
    auto dotLeftValue = digitIndicatorInfo[DIGIT_INDICATOR_LEFT] == "-" ? "" : digitIndicatorInfo[DIGIT_INDICATOR_LEFT];
    auto dotTopValue = digitIndicatorInfo[DIGIT_INDICATOR_TOP] == "-" ? "" : digitIndicatorInfo[DIGIT_INDICATOR_TOP];
    auto dotRightValue =
        digitIndicatorInfo[DIGIT_INDICATOR_RIGHT] == "-" ? "" : digitIndicatorInfo[DIGIT_INDICATOR_RIGHT];
    auto dotBottomValue =
        digitIndicatorInfo[DIGIT_INDICATOR_BOTTOM] == "-" ? "" : digitIndicatorInfo[DIGIT_INDICATOR_BOTTOM];
    auto fontColorValue =
        digitIndicatorInfo[DIGIT_INDICATOR_FONT_COLOR] == "-" ? "" : digitIndicatorInfo[DIGIT_INDICATOR_FONT_COLOR];
    auto selectedFontColorValue = digitIndicatorInfo[DIGIT_INDICATOR_SELECTED_FONT_COLOR] == "-"
                                      ? ""
                                      : digitIndicatorInfo[DIGIT_INDICATOR_SELECTED_FONT_COLOR];
    auto digitFontSize = digitIndicatorInfo[DIGIT_INDICATOR_DIGIT_FONT_SIZE] == "-"
                             ? ""
                             : digitIndicatorInfo[DIGIT_INDICATOR_DIGIT_FONT_SIZE];
    auto digitFontWeight = digitIndicatorInfo[DIGIT_INDICATOR_DIGIT_FONT_WEIGHT] == "-"
                               ? ""
                               : digitIndicatorInfo[DIGIT_INDICATOR_DIGIT_FONT_WEIGHT];
    auto selectedDigitFontSize = digitIndicatorInfo[DIGIT_INDICATOR_SELECTED_DIGIT_FONT_SIZE] == "-"
                                     ? ""
                                     : digitIndicatorInfo[DIGIT_INDICATOR_SELECTED_DIGIT_FONT_SIZE];
    auto selectedDigitFontWeight = digitIndicatorInfo[DIGIT_INDICATOR_SELECTED_DIGIT_FONT_WEIGHT] == "-"
                                       ? ""
                                       : digitIndicatorInfo[DIGIT_INDICATOR_SELECTED_DIGIT_FONT_WEIGHT];
    auto pipelineContext = PipelineBase::GetCurrentContextSafely();
    CHECK_NULL_RETURN(pipelineContext, SwiperDigitalParameters());
    auto swiperIndicatorTheme = pipelineContext->GetTheme<SwiperIndicatorTheme>();
    CHECK_NULL_RETURN(swiperIndicatorTheme, SwiperDigitalParameters());
    bool parseOk = false;
    SwiperDigitalParameters digitalParameters;
    digitalParameters.dimLeft = ParseIndicatorDimension(dotLeftValue);
    digitalParameters.dimTop = ParseIndicatorDimension(dotTopValue);
    digitalParameters.dimRight = ParseIndicatorDimension(dotRightValue);
    digitalParameters.dimBottom = ParseIndicatorDimension(dotBottomValue);
    Color fontColor;
    parseOk = Color::ParseColorString(fontColorValue, fontColor);
    digitalParameters.fontColor =
        parseOk ? fontColor : swiperIndicatorTheme->GetDigitalIndicatorTextStyle().GetTextColor();
    parseOk = Color::ParseColorString(selectedFontColorValue, fontColor);
    digitalParameters.selectedFontColor =
        parseOk ? fontColor : swiperIndicatorTheme->GetDigitalIndicatorTextStyle().GetTextColor();
    GetFontContent(digitFontSize, digitFontWeight, false, digitalParameters);
    GetFontContent(selectedDigitFontSize, selectedDigitFontWeight, true, digitalParameters);
    return digitalParameters;
}

void SetItem4GetDotIndicatorInfo(
    SwiperParameters& indicatorParameters, FrameNode* frameNode, const std::vector<std::string>& dotIndicatorInfo)
{
    CHECK_NULL_VOID(frameNode);
    auto pipelineContext = frameNode->GetContext();
    CHECK_NULL_VOID(pipelineContext);
    auto swiperIndicatorTheme = pipelineContext->GetTheme<SwiperIndicatorTheme>();
    CHECK_NULL_VOID(swiperIndicatorTheme);
    auto itemWidthValue = GetInfoFromVectorByIndex(dotIndicatorInfo, DOT_INDICATOR_ITEM_WIDTH);
    auto itemHeightValue = GetInfoFromVectorByIndex(dotIndicatorInfo, DOT_INDICATOR_ITEM_HEIGHT);
    auto selectedItemWidthValue = GetInfoFromVectorByIndex(dotIndicatorInfo, DOT_INDICATOR_SELECTED_ITEM_WIDTH);
    auto selectedItemHeightValue = GetInfoFromVectorByIndex(dotIndicatorInfo, DOT_INDICATOR_SELECTED_ITEM_HEIGHT);
    CalcDimension dimPosition = StringUtils::StringToCalcDimension(itemWidthValue, false, DimensionUnit::VP);
    auto defaultSize = swiperIndicatorTheme->GetSize();
    bool parseItemWOk = !itemWidthValue.empty() && dimPosition.Unit() != DimensionUnit::PERCENT;
    indicatorParameters.itemWidth = (parseItemWOk && (dimPosition > 0.0_vp)) ? dimPosition : defaultSize;
    dimPosition = StringUtils::StringToCalcDimension(itemHeightValue, false, DimensionUnit::VP);
    bool parseItemHOk = !itemHeightValue.empty() && dimPosition.Unit() != DimensionUnit::PERCENT;
    indicatorParameters.itemHeight = (parseItemHOk && (dimPosition > 0.0_vp)) ? dimPosition : defaultSize;
    dimPosition = StringUtils::StringToCalcDimension(selectedItemWidthValue, false, DimensionUnit::VP);
    bool parseSeleItemWOk = !selectedItemWidthValue.empty() && dimPosition.Unit() != DimensionUnit::PERCENT;
    indicatorParameters.selectedItemWidth = (parseSeleItemWOk && (dimPosition > 0.0_vp)) ? dimPosition : defaultSize;
    dimPosition = StringUtils::StringToCalcDimension(selectedItemHeightValue, false, DimensionUnit::VP);
    bool parseSeleItemHOk = !selectedItemHeightValue.empty() && dimPosition.Unit() != DimensionUnit::PERCENT;
    indicatorParameters.selectedItemHeight = (parseSeleItemHOk && (dimPosition > 0.0_vp)) ? dimPosition : defaultSize;
    if (!parseSeleItemWOk && !parseSeleItemHOk && !parseItemWOk && !parseItemHOk) {
        IndicatorModelNG::SetIsIndicatorCustomSize(frameNode, false);
    } else {
        IndicatorModelNG::SetIsIndicatorCustomSize(frameNode, true);
    }
}

SwiperParameters GetDotIndicatorInfo(FrameNode* frameNode, const std::vector<std::string>& dotIndicatorInfo)
{
    auto maskValue = GetInfoFromVectorByIndex(dotIndicatorInfo, DOT_INDICATOR_MASK);
    auto colorValue = GetInfoFromVectorByIndex(dotIndicatorInfo, DOT_INDICATOR_COLOR);
    auto selectedColorValue = GetInfoFromVectorByIndex(dotIndicatorInfo, DOT_INDICATOR_SELECTED_COLOR);
    CHECK_NULL_RETURN(frameNode, SwiperParameters());
    auto pipelineContext = frameNode->GetContext();
    CHECK_NULL_RETURN(pipelineContext, SwiperParameters());
    auto swiperIndicatorTheme = pipelineContext->GetTheme<SwiperIndicatorTheme>();
    CHECK_NULL_RETURN(swiperIndicatorTheme, SwiperParameters());
    bool parseOk = false;
    SwiperParameters indicatorParameters;
    SetItem4GetDotIndicatorInfo(indicatorParameters, frameNode, dotIndicatorInfo);
    auto leftValue = GetInfoFromVectorByIndex(dotIndicatorInfo, DOT_INDICATOR_LEFT);
    auto topValue = GetInfoFromVectorByIndex(dotIndicatorInfo, DOT_INDICATOR_TOP);
    auto rightValue = GetInfoFromVectorByIndex(dotIndicatorInfo, DOT_INDICATOR_RIGHT);
    auto bottomValue = GetInfoFromVectorByIndex(dotIndicatorInfo, DOT_INDICATOR_BOTTOM);
    indicatorParameters.dimLeft = ParseIndicatorDimension(leftValue);
    indicatorParameters.dimTop = ParseIndicatorDimension(topValue);
    indicatorParameters.dimRight = ParseIndicatorDimension(rightValue);
    indicatorParameters.dimBottom = ParseIndicatorDimension(bottomValue);
    if (maskValue != "2") {
        indicatorParameters.maskValue = (maskValue == "1");
    }
    Color colorVal;
    parseOk = Color::ParseColorString(colorValue, colorVal);
    indicatorParameters.colorVal = parseOk ? colorVal : swiperIndicatorTheme->GetColor();
    parseOk = Color::ParseColorString(selectedColorValue, colorVal);
    indicatorParameters.selectedColorVal = parseOk ? colorVal : swiperIndicatorTheme->GetSelectedColor();
    auto maxDisplayCount = GetInfoFromVectorByIndex(dotIndicatorInfo, DOT_INDICATOR_MAX_DISPLAY_COUNT);
    if (!maxDisplayCount.empty()) {
        indicatorParameters.maxDisplayCountVal = StringUtils::StringToInt(maxDisplayCount);
    }
    return indicatorParameters;
}

void SetInitialIndex(ArkUINodeHandle node, ArkUI_Int32 index)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    IndicatorModelNG::SetInitialIndex(frameNode, index);
}

void ResetInitialIndex(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    IndicatorModelNG::SetInitialIndex(frameNode, 0);
}

void SetCount(ArkUINodeHandle node, ArkUI_Int32 count)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (count < 0) {
        count = DEFAULT_CACHED_COUNT;
    }
    IndicatorModelNG::SetCount(frameNode, count);
}

void ResetCount(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    IndicatorModelNG::SetCount(frameNode, DEFAULT_DISPLAY_COUNT);
}

void SetOnChange(ArkUINodeHandle node, void* callback)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (callback) {
        auto onChange = reinterpret_cast<std::function<void(const BaseEventInfo* info)>*>(callback);
        IndicatorModelNG::SetOnChange(frameNode, std::move(*onChange));
    } else {
        IndicatorModelNG::SetOnChange(frameNode, nullptr);
    }
}

void ResetOnChange(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    IndicatorModelNG::SetOnChange(frameNode, nullptr);
}

void SetStyle(ArkUINodeHandle node, ArkUI_CharPtr indicatorStr)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::vector<std::string> res;
    std::string indicatorValues = std::string(indicatorStr);
    StringUtils::StringSplitter(indicatorValues, '|', res);
    std::string type = res[INDICATOR_TYPE_INDEX];
    if (type == "ArkDigitIndicator") {
        SwiperDigitalParameters digitalParameters = GetDigitIndicatorInfo(res);
        IndicatorModelNG::SetDigitIndicatorStyle(frameNode, digitalParameters);
        IndicatorModelNG::SetIndicatorType(frameNode, SwiperIndicatorType::DIGIT);
    } else {
        SwiperParameters indicatorParameters = GetDotIndicatorInfo(frameNode, res);
        IndicatorModelNG::SetDotIndicatorStyle(frameNode, indicatorParameters);
        IndicatorModelNG::SetIndicatorType(frameNode, SwiperIndicatorType::DOT);
    }
}

void ResetStyle(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    IndicatorModelNG::SetIndicatorType(frameNode, SwiperIndicatorType::DOT);
}

void SetLoop(ArkUINodeHandle node, ArkUI_Bool loop)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    IndicatorModelNG::SetLoop(frameNode, loop);
}

void ResetLoop(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    IndicatorModelNG::SetLoop(frameNode, true);
}

void SetVertical(ArkUINodeHandle node, ArkUI_Bool isVertical)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    IndicatorModelNG::SetDirection(frameNode, isVertical ? Axis::VERTICAL : Axis::HORIZONTAL);
}

void ResetVertical(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    IndicatorModelNG::SetDirection(frameNode, Axis::HORIZONTAL);
}
} // namespace
namespace NodeModifier {
const ArkUIIndicatorComponentModifier* GetIndicatorComponentModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const ArkUIIndicatorComponentModifier modifier = {
        .setInitialIndex = SetInitialIndex,
        .resetInitialIndex = ResetInitialIndex,
        .setCount = SetCount,
        .resetCount = ResetCount,
        .setOnChange = SetOnChange,
        .resetOnChange = ResetOnChange,
        .setStyle = SetStyle,
        .resetStyle = ResetStyle,
        .setLoop = SetLoop,
        .resetLoop = ResetLoop,
        .setVertical = SetVertical,
        .resetVertical = ResetVertical
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line
    return &modifier;
};

} // namespace NodeModifier
} // namespace OHOS::Ace::NG
