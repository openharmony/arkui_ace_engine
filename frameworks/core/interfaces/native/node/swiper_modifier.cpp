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
#include "core/interfaces/native/node/swiper_modifier.h"

#include <vector>

#include "base/log/log_wrapper.h"
#include "base/utils/string_utils.h"
#include "bridge/common/utils/utils.h"
#include "core/animation/curve.h"
#include "core/components/swiper/swiper_indicator_theme.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/swiper/swiper_model_ng.h"
#include "core/pipeline/base/element_register.h"

namespace OHOS::Ace::NG {
constexpr int32_t DEFAULT_INTERVAL = 3000;
constexpr int32_t DEFAULT_DURATION = 400;
constexpr int32_t DEFAULT_CACHED_COUNT = 1;
constexpr int32_t DEFAULT_DISPLAY_COUNT = 1;
constexpr bool DEFAULT_AUTO_PLAY = false;
constexpr bool DEFAULT_LOOP = true;
constexpr bool DEAFULT_DISABLE_SWIPE = false;
constexpr int32_t ARROW_IS_SHOW_BACKGROUND = 1;
constexpr int32_t ARROW_IS_SIDE_BAR_MIDDLE = 2;
constexpr int32_t ARROW_BACKGROUND_SIZE = 3;
constexpr int32_t ARROW_BACKGROUND_COLOR = 4;
constexpr int32_t ARROW_SIZE = 5;
constexpr int32_t ARROW_COLOR = 6;
constexpr int32_t DISPLAY_ARROW_UNDEFINED = 3;
constexpr int32_t DISPLAY_ARROW_OBJECT = 2;
constexpr int32_t DISPLAY_ARROW_TRUE = 1;
constexpr int32_t DISPLAY_ARROW_FALSE = 0;
constexpr int32_t DISPLAY_ARROW_VALUE = 0;
constexpr int32_t DISPLAY_ARROW_IS_HOVER_SHOW_INDEX = 7;
constexpr int32_t DISPLAY_ARROW_IS_HOVER_SHOW_UNDEFINED = 2;
constexpr int32_t INDICATOR_TYPE_INDEX = 0;
constexpr int32_t INDICATOR_VALUE = 1;
constexpr int32_t DIGIT_INDICATOR_FONT_COLOR = 1;
constexpr int32_t DIGIT_INDICATOR_SELECTED_FONT_COLOR = 2;
constexpr int32_t DIGIT_INDICATOR_DIGIT_FONT_SIZE = 3;
constexpr int32_t DIGIT_INDICATOR_DIGIT_FONT_WEIGHT = 4;
constexpr int32_t DIGIT_INDICATOR_SELECTED_DIGIT_FONT_SIZE = 5;
constexpr int32_t DIGIT_INDICATOR_SELECTED_DIGIT_FONT_WEIGHT = 6;
constexpr int32_t DIGIT_INDICATOR_LEFT = 7;
constexpr int32_t DIGIT_INDICATOR_TOP = 8;
constexpr int32_t DIGIT_INDICATOR_RIGHT = 9;
constexpr int32_t DIGIT_INDICATOR_BOTTOM = 10;
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
constexpr float ARROW_SIZE_COEFFICIENT = 0.75f;

const std::vector<SwiperDisplayMode> DISPLAY_MODE = { SwiperDisplayMode::STRETCH, SwiperDisplayMode::AUTO_LINEAR };
const std::vector<EdgeEffect> EDGE_EFFECT = { EdgeEffect::SPRING, EdgeEffect::FADE, EdgeEffect::NONE };
const std::vector<SwiperIndicatorType> INDICATOR_TYPE = { SwiperIndicatorType::DOT, SwiperIndicatorType::DIGIT };

void SetArrowBackgroundInfo(SwiperArrowParameters& swiperArrowParameters,
    RefPtr<SwiperIndicatorTheme>& swiperIndicatorTheme, const std::vector<std::string>& arrowInfo)
{
    auto backgroundSizeValue = arrowInfo[ARROW_BACKGROUND_SIZE] == "-" ? "" : arrowInfo[ARROW_BACKGROUND_SIZE];
    auto backgroundColorValue = arrowInfo[ARROW_BACKGROUND_COLOR] == "-" ? "" : arrowInfo[ARROW_BACKGROUND_COLOR];
    auto arrowSizeValue = arrowInfo[ARROW_SIZE] == "-" ? "" : arrowInfo[ARROW_SIZE];
    auto arrowColorValue = arrowInfo[ARROW_COLOR] == "-" ? "" : arrowInfo[ARROW_COLOR];
    bool parseOk = false;
    CalcDimension dimension;
    Color color;
    if (swiperArrowParameters.isSidebarMiddle.value()) {
        dimension = StringUtils::StringToCalcDimension(backgroundSizeValue, false, DimensionUnit::VP);
        swiperArrowParameters.backgroundSize =
            GreatNotEqual(dimension.ConvertToVp(), 0.0) && !(dimension.Unit() == DimensionUnit::PERCENT)
                ? dimension : swiperIndicatorTheme->GetBigArrowBackgroundSize();
        parseOk = Color::ParseColorString(backgroundColorValue, color);
        swiperArrowParameters.backgroundColor = parseOk ? color : swiperIndicatorTheme->GetBigArrowBackgroundColor();
        if (swiperArrowParameters.isShowBackground.value()) {
            swiperArrowParameters.arrowSize = swiperArrowParameters.backgroundSize.value() * ARROW_SIZE_COEFFICIENT;
        } else {
            parseOk = StringUtils::StringToCalcDimensionNG(arrowSizeValue, dimension, false, DimensionUnit::VP);
            swiperArrowParameters.arrowSize =
                parseOk && GreatNotEqual(dimension.ConvertToVp(), 0.0) && !(dimension.Unit() == DimensionUnit::PERCENT)
                    ? dimension : swiperIndicatorTheme->GetBigArrowSize();
            swiperArrowParameters.backgroundSize = swiperArrowParameters.arrowSize;
        }
        parseOk = Color::ParseColorString(arrowColorValue, color);
        swiperArrowParameters.arrowColor = parseOk ? color : swiperIndicatorTheme->GetBigArrowColor();
    } else {
        dimension = StringUtils::StringToCalcDimension(backgroundSizeValue, false, DimensionUnit::VP);
        swiperArrowParameters.backgroundSize =
            GreatNotEqual(dimension.ConvertToVp(), 0.0) && !(dimension.Unit() == DimensionUnit::PERCENT)
                ? dimension : swiperIndicatorTheme->GetSmallArrowBackgroundSize();
        parseOk = Color::ParseColorString(backgroundColorValue, color);
        swiperArrowParameters.backgroundColor = parseOk ? color : swiperIndicatorTheme->GetSmallArrowBackgroundColor();
        if (swiperArrowParameters.isShowBackground.value()) {
            swiperArrowParameters.arrowSize = swiperArrowParameters.backgroundSize.value() * ARROW_SIZE_COEFFICIENT;
        } else {
            parseOk = StringUtils::StringToCalcDimensionNG(arrowSizeValue, dimension, false, DimensionUnit::VP);
            swiperArrowParameters.arrowSize =
                parseOk && GreatNotEqual(dimension.ConvertToVp(), 0.0) && !(dimension.Unit() == DimensionUnit::PERCENT)
                    ? dimension : swiperIndicatorTheme->GetSmallArrowSize();
            swiperArrowParameters.backgroundSize = swiperArrowParameters.arrowSize;
        }
        parseOk = Color::ParseColorString(arrowColorValue, color);
        swiperArrowParameters.arrowColor = parseOk ? color : swiperIndicatorTheme->GetSmallArrowColor();
    }
}

bool GetArrowInfo(const std::vector<std::string>& arrowInfo, SwiperArrowParameters& swiperArrowParameters)
{
    auto isShowBackgroundValue = arrowInfo[ARROW_IS_SHOW_BACKGROUND];
    auto isSidebarMiddleValue = arrowInfo[ARROW_IS_SIDE_BAR_MIDDLE];

    auto pipelineContext = PipelineBase::GetCurrentContext();
    CHECK_NULL_RETURN(pipelineContext, false);
    auto swiperIndicatorTheme = pipelineContext->GetTheme<SwiperIndicatorTheme>();
    CHECK_NULL_RETURN(swiperIndicatorTheme, false);
    if (isShowBackgroundValue == "2") {
        swiperArrowParameters.isShowBackground = swiperIndicatorTheme->GetIsShowArrowBackground();
    } else {
        swiperArrowParameters.isShowBackground = isShowBackgroundValue == "1" ? true : false;
    }
    if (isSidebarMiddleValue == "2") {
        swiperArrowParameters.isSidebarMiddle = swiperIndicatorTheme->GetIsSidebarMiddle();
    } else {
        swiperArrowParameters.isSidebarMiddle = isSidebarMiddleValue == "1" ? true : false;
    }
    SetArrowBackgroundInfo(swiperArrowParameters, swiperIndicatorTheme, arrowInfo);
    return true;
}

std::string GetInfoFromVectorByIndex(const std::vector<std::string>& dotIndicatorInfo, int32_t index)
{
    auto dotIndicatorInfoSize = dotIndicatorInfo.size();
    return dotIndicatorInfoSize < DOT_INDICATOR_INFO_SIZE
               ? "" : (dotIndicatorInfo[index] == "-" ? "" : dotIndicatorInfo[index]);
}

void SetIndicatorInfo(SwiperParameters& swiperParameters, const std::vector<std::string>& dotIndicatorInfo)
{
    auto leftValue = GetInfoFromVectorByIndex(dotIndicatorInfo, DOT_INDICATOR_LEFT);
    auto topValue = GetInfoFromVectorByIndex(dotIndicatorInfo, DOT_INDICATOR_TOP);
    auto rightValue = GetInfoFromVectorByIndex(dotIndicatorInfo, DOT_INDICATOR_RIGHT);
    auto bottomValue = GetInfoFromVectorByIndex(dotIndicatorInfo, DOT_INDICATOR_BOTTOM);
    CalcDimension dimPosition = StringUtils::StringToCalcDimension(leftValue, false, DimensionUnit::VP);
    swiperParameters.dimLeft = LessNotEqual(dimPosition.ConvertToPx(), 0.0f) ? 0.0_vp : dimPosition;
    dimPosition = StringUtils::StringToCalcDimension(topValue, false, DimensionUnit::VP);
    swiperParameters.dimTop = LessNotEqual(dimPosition.ConvertToPx(), 0.0f) ? 0.0_vp : dimPosition;
    dimPosition = StringUtils::StringToCalcDimension(rightValue, false, DimensionUnit::VP);
    swiperParameters.dimRight = LessNotEqual(dimPosition.ConvertToPx(), 0.0f) ? 0.0_vp : dimPosition;
    dimPosition = StringUtils::StringToCalcDimension(bottomValue, false, DimensionUnit::VP);
    swiperParameters.dimBottom = LessNotEqual(dimPosition.ConvertToPx(), 0.0f) ? 0.0_vp : dimPosition;
}

SwiperParameters GetDotIndicatorInfo(FrameNode* frameNode, const std::vector<std::string>& dotIndicatorInfo)
{
    auto itemWidthValue = GetInfoFromVectorByIndex(dotIndicatorInfo, DOT_INDICATOR_ITEM_WIDTH);
    auto itemHeightValue = GetInfoFromVectorByIndex(dotIndicatorInfo, DOT_INDICATOR_ITEM_HEIGHT);
    auto selectedItemWidthValue = GetInfoFromVectorByIndex(dotIndicatorInfo, DOT_INDICATOR_SELECTED_ITEM_WIDTH);
    auto selectedItemHeightValue = GetInfoFromVectorByIndex(dotIndicatorInfo, DOT_INDICATOR_SELECTED_ITEM_HEIGHT);
    auto maskValue = GetInfoFromVectorByIndex(dotIndicatorInfo, DOT_INDICATOR_MASK);
    auto colorValue = GetInfoFromVectorByIndex(dotIndicatorInfo, DOT_INDICATOR_COLOR);
    auto selectedColorValue = GetInfoFromVectorByIndex(dotIndicatorInfo, DOT_INDICATOR_SELECTED_COLOR);
    auto pipelineContext = PipelineBase::GetCurrentContext();
    CHECK_NULL_RETURN(pipelineContext, SwiperParameters());
    auto swiperIndicatorTheme = pipelineContext->GetTheme<SwiperIndicatorTheme>();
    CHECK_NULL_RETURN(swiperIndicatorTheme, SwiperParameters());
    bool parseOk = false;
    SwiperParameters swiperParameters;
    SetIndicatorInfo(swiperParameters, dotIndicatorInfo);
    CalcDimension dimPosition = StringUtils::StringToCalcDimension(itemWidthValue, false, DimensionUnit::VP);
    auto defaultSize = swiperIndicatorTheme->GetSize();
    bool parseItemWOk = !itemWidthValue.empty() && dimPosition.Unit() != DimensionUnit::PERCENT;
    swiperParameters.itemWidth = (parseItemWOk && (dimPosition > 0.0_vp)) ? dimPosition : defaultSize;
    dimPosition = StringUtils::StringToCalcDimension(itemHeightValue, false, DimensionUnit::VP);
    bool parseItemHOk = !itemHeightValue.empty() && dimPosition.Unit() != DimensionUnit::PERCENT;
    swiperParameters.itemHeight = (parseItemHOk && (dimPosition > 0.0_vp)) ? dimPosition : defaultSize;
    dimPosition = StringUtils::StringToCalcDimension(selectedItemWidthValue, false, DimensionUnit::VP);
    bool parseSeleItemWOk = !selectedItemWidthValue.empty() && dimPosition.Unit() != DimensionUnit::PERCENT;
    swiperParameters.selectedItemWidth = (parseSeleItemWOk && (dimPosition > 0.0_vp)) ? dimPosition : defaultSize;
    dimPosition = StringUtils::StringToCalcDimension(selectedItemHeightValue, false, DimensionUnit::VP);
    bool parseSeleItemHOk = !selectedItemHeightValue.empty() && dimPosition.Unit() != DimensionUnit::PERCENT;
    swiperParameters.selectedItemHeight = (parseSeleItemHOk && (dimPosition > 0.0_vp)) ? dimPosition : defaultSize;
    if (!parseSeleItemWOk && !parseSeleItemHOk && !parseItemWOk && !parseItemHOk) {
        SwiperModelNG::SetIsIndicatorCustomSize(frameNode, false);
    } else {
        SwiperModelNG::SetIsIndicatorCustomSize(frameNode, true);
    }
    if (maskValue != "2") {
        swiperParameters.maskValue = (maskValue == "1" ? true : false);
    }
    Color colorVal;
    parseOk = Color::ParseColorString(colorValue, colorVal);
    swiperParameters.colorVal = parseOk ? colorVal : swiperIndicatorTheme->GetColor();
    parseOk = Color::ParseColorString(selectedColorValue, colorVal);
    swiperParameters.selectedColorVal = parseOk ? colorVal : swiperIndicatorTheme->GetSelectedColor();
    return swiperParameters;
}

void GetFontContent(
    const std::string& size, const std::string& weight, bool isSelected, SwiperDigitalParameters& digitalParameters)
{
    auto pipelineContext = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    auto swiperIndicatorTheme = pipelineContext->GetTheme<SwiperIndicatorTheme>();
    CHECK_NULL_VOID(swiperIndicatorTheme);
    CalcDimension fontSize = StringUtils::StringToCalcDimension(size, false, DimensionUnit::VP);
    if (LessOrEqual(fontSize.Value(), 0.0) || fontSize.Unit() == DimensionUnit::PERCENT) {
        fontSize = swiperIndicatorTheme->GetDigitalIndicatorTextStyle().GetFontSize();
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
            digitalParameters.selectedFontWeight = swiperIndicatorTheme->GetDigitalIndicatorTextStyle().GetFontWeight();
        } else {
            digitalParameters.fontWeight = swiperIndicatorTheme->GetDigitalIndicatorTextStyle().GetFontWeight();
        }
    }
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
                                      ? "" : digitIndicatorInfo[DIGIT_INDICATOR_SELECTED_FONT_COLOR];
    auto digitFontSize = digitIndicatorInfo[DIGIT_INDICATOR_DIGIT_FONT_SIZE] == "-"
                             ? "" : digitIndicatorInfo[DIGIT_INDICATOR_DIGIT_FONT_SIZE];
    auto digitFontWeight = digitIndicatorInfo[DIGIT_INDICATOR_DIGIT_FONT_WEIGHT] == "-"
                               ? "" : digitIndicatorInfo[DIGIT_INDICATOR_DIGIT_FONT_WEIGHT];
    auto selectedDigitFontSize = digitIndicatorInfo[DIGIT_INDICATOR_SELECTED_DIGIT_FONT_SIZE] == "-"
                                     ? "" : digitIndicatorInfo[DIGIT_INDICATOR_SELECTED_DIGIT_FONT_SIZE];
    auto selectedDigitFontWeight = digitIndicatorInfo[DIGIT_INDICATOR_SELECTED_DIGIT_FONT_WEIGHT] == "-"
                                       ? "" : digitIndicatorInfo[DIGIT_INDICATOR_SELECTED_DIGIT_FONT_WEIGHT];
    auto pipelineContext = PipelineBase::GetCurrentContext();
    CHECK_NULL_RETURN(pipelineContext, SwiperDigitalParameters());
    auto swiperIndicatorTheme = pipelineContext->GetTheme<SwiperIndicatorTheme>();
    CHECK_NULL_RETURN(swiperIndicatorTheme, SwiperDigitalParameters());
    bool parseOk = false;
    SwiperDigitalParameters digitalParameters;
    CalcDimension dimPosition = StringUtils::StringToCalcDimension(dotLeftValue, false, DimensionUnit::VP);
    digitalParameters.dimLeft = LessNotEqual(dimPosition.ConvertToPx(), 0.0f) ? 0.0_vp : dimPosition;
    dimPosition = StringUtils::StringToCalcDimension(dotTopValue, false, DimensionUnit::VP);
    digitalParameters.dimTop = LessNotEqual(dimPosition.ConvertToPx(), 0.0f) ? 0.0_vp : dimPosition;
    dimPosition = StringUtils::StringToCalcDimension(dotRightValue, false, DimensionUnit::VP);
    digitalParameters.dimRight = LessNotEqual(dimPosition.ConvertToPx(), 0.0f) ? 0.0_vp : dimPosition;
    dimPosition = StringUtils::StringToCalcDimension(dotBottomValue, false, DimensionUnit::VP);
    digitalParameters.dimBottom = LessNotEqual(dimPosition.ConvertToPx(), 0.0f) ? 0.0_vp : dimPosition;
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

void SetSwiperNextMargin(NodeHandle node, double nextMarginValue, int32_t nextMarginUnit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SwiperModelNG::SetNextMargin(frameNode, CalcDimension(nextMarginValue, (DimensionUnit)nextMarginUnit));
}

void ResetSwiperNextMargin(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CalcDimension value(0.0, DimensionUnit::VP);
    SwiperModelNG::SetNextMargin(frameNode, value);
}

void SetSwiperPrevMargin(NodeHandle node, double prevMarginValue, int32_t prevMarginUnit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SwiperModelNG::SetPreviousMargin(frameNode, CalcDimension(prevMarginValue, (DimensionUnit)prevMarginUnit));
}

void ResetSwiperPrevMargin(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CalcDimension value(0.0, DimensionUnit::VP);
    SwiperModelNG::SetPreviousMargin(frameNode, value);
}

void SetSwiperDisplayCount(NodeHandle node, const char* displayCountChar, const char* displayCountType)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::string displayCountValue = std::string(displayCountChar);
    std::string type = std::string(displayCountType);
    if (type == "string" && displayCountValue == "auto") {
        SwiperModelNG::SetDisplayMode(frameNode, SwiperDisplayMode::AUTO_LINEAR);
        SwiperModelNG::ResetDisplayCount(frameNode);
    } else if (type == "number" && StringUtils::StringToInt(displayCountValue) > 0) {
        SwiperModelNG::SetDisplayCount(frameNode, StringUtils::StringToInt(displayCountValue));
    } else if (type == "object") {
        if (displayCountValue.empty()) {
            return;
        }
        CalcDimension minSizeValue = StringUtils::StringToCalcDimension(displayCountValue, false, DimensionUnit::VP);
        if (LessNotEqual(minSizeValue.Value(), 0.0)) {
            minSizeValue.SetValue(0.0);
        }
        SwiperModelNG::SetMinSize(frameNode, minSizeValue);
    } else {
        SwiperModelNG::SetDisplayCount(frameNode, DEFAULT_DISPLAY_COUNT);
    }
}

void ResetSwiperDisplayCount(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SwiperModelNG::SetDisplayCount(frameNode, DEFAULT_DISPLAY_COUNT);
}

void SetSwiperDisplayArrow(NodeHandle node, const char* displayArrowStr)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::vector<std::string> res;
    std::string displayArrowValues = std::string(displayArrowStr);
    StringUtils::StringSplitter(displayArrowValues, '|', res);
    int32_t displayArrowValue = StringUtils::StringToInt(res[DISPLAY_ARROW_VALUE]);
    if (displayArrowValue == DISPLAY_ARROW_UNDEFINED) {
        SwiperModelNG::SetDisplayArrow(frameNode, false);
        return;
    } else if (displayArrowValue == DISPLAY_ARROW_OBJECT) {
        SwiperArrowParameters swiperArrowParameters;
        if (!GetArrowInfo(res, swiperArrowParameters)) {
            SwiperModelNG::SetDisplayArrow(frameNode, false);
            return;
        }
        SwiperModelNG::SetArrowStyle(frameNode, swiperArrowParameters);
        SwiperModelNG::SetDisplayArrow(frameNode, true);
    } else if (displayArrowValue == DISPLAY_ARROW_TRUE) {
        auto pipelineContext = PipelineBase::GetCurrentContext();
        CHECK_NULL_VOID(pipelineContext);
        auto swiperIndicatorTheme = pipelineContext->GetTheme<SwiperIndicatorTheme>();
        CHECK_NULL_VOID(swiperIndicatorTheme);
        SwiperArrowParameters swiperArrowParameters;
        swiperArrowParameters.isShowBackground = swiperIndicatorTheme->GetIsShowArrowBackground();
        swiperArrowParameters.isSidebarMiddle = swiperIndicatorTheme->GetIsSidebarMiddle();
        swiperArrowParameters.backgroundSize = swiperIndicatorTheme->GetSmallArrowBackgroundSize();
        swiperArrowParameters.backgroundColor = swiperIndicatorTheme->GetSmallArrowBackgroundColor();
        swiperArrowParameters.arrowSize = swiperIndicatorTheme->GetSmallArrowSize();
        swiperArrowParameters.arrowColor = swiperIndicatorTheme->GetSmallArrowColor();
        SwiperModelNG::SetArrowStyle(frameNode, swiperArrowParameters);
        SwiperModelNG::SetDisplayArrow(frameNode, true);
    } else if (displayArrowValue == DISPLAY_ARROW_FALSE) {
        SwiperModelNG::SetDisplayArrow(frameNode, false);
        return;
    } else {
        SwiperModelNG::SetDisplayArrow(frameNode, false);
        return;
    }
    int32_t isHoverShow = StringUtils::StringToInt(res[DISPLAY_ARROW_IS_HOVER_SHOW_INDEX]);
    if (isHoverShow != DISPLAY_ARROW_IS_HOVER_SHOW_UNDEFINED) {
        SwiperModelNG::SetHoverShow(frameNode, isHoverShow == 1 ? true : false);
    } else {
        SwiperModelNG::SetHoverShow(frameNode, false);
    }
}

void ResetSwiperDisplayArrow(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SwiperModelNG::SetDisplayArrow(frameNode, false);
}

void SetSwiperCurve(NodeHandle node, const char* curveChar)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    RefPtr<Curve> curve = Curves::LINEAR;
    curve = Framework::CreateCurve(curveChar);
    SwiperModelNG::SetCurve(frameNode, curve);
}

void ResetSwiperCurve(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    RefPtr<Curve> curve = Curves::LINEAR;
    SwiperModelNG::SetCurve(frameNode, curve);
}

void SetSwiperDisableSwipe(NodeHandle node, bool disableSwipe)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SwiperModelNG::SetDisableSwipe(frameNode, disableSwipe);
}

void ResetSwiperDisableSwipe(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SwiperModelNG::SetDisableSwipe(frameNode, DEAFULT_DISABLE_SWIPE);
}

void SetSwiperEffectMode(NodeHandle node, int32_t edgeEffect)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (edgeEffect < 0 || edgeEffect >= static_cast<int32_t>(EDGE_EFFECT.size())) {
        return;
    }
    SwiperModelNG::SetEdgeEffect(frameNode, EDGE_EFFECT[edgeEffect]);
}

void ResetSwiperEffectMode(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SwiperModelNG::SetEdgeEffect(frameNode, EdgeEffect::SPRING);
}

void SetSwiperCachedCount(NodeHandle node, int32_t cachedCount)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (cachedCount < 0) {
        cachedCount = DEFAULT_CACHED_COUNT;
    }
    SwiperModelNG::SetCachedCount(frameNode, cachedCount);
}

void ResetSwiperCachedCount(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    int32_t value = DEFAULT_CACHED_COUNT;
    SwiperModelNG::SetCachedCount(frameNode, value);
}

void SetSwiperDisplayMode(NodeHandle node, int32_t displayMode)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (displayMode < 0 || displayMode >= static_cast<int32_t>(DISPLAY_MODE.size())) {
        return;
    }
    SwiperModelNG::SetDisplayMode(frameNode, DISPLAY_MODE[displayMode]);
}

void ResetSwiperDisplayMode(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SwiperModelNG::SetDisplayMode(frameNode, SwiperDisplayMode::STRETCH);
}

void SetSwiperItemSpace(NodeHandle node, double itemSpaceValue, int32_t itemSpaceUnit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SwiperModelNG::SetItemSpace(frameNode, CalcDimension(itemSpaceValue, (DimensionUnit)itemSpaceUnit));
}

void ResetSwiperItemSpace(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CalcDimension value(0.0, DimensionUnit::VP);
    SwiperModelNG::SetItemSpace(frameNode, value);
}

void SetSwiperVertical(NodeHandle node, bool isVertical)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SwiperModelNG::SetDirection(frameNode, isVertical ? Axis::VERTICAL : Axis::HORIZONTAL);
}

void ResetSwiperVertical(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SwiperModelNG::SetDirection(frameNode, Axis::HORIZONTAL);
}

void SetSwiperLoop(NodeHandle node, bool loop)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SwiperModelNG::SetLoop(frameNode, loop);
}

void ResetSwiperLoop(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SwiperModelNG::SetLoop(frameNode, DEFAULT_LOOP);
}

void SetSwiperInterval(NodeHandle node, int32_t interval)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (interval < 0) {
        interval = DEFAULT_INTERVAL;
    }
    SwiperModelNG::SetAutoPlayInterval(frameNode, interval);
}

void ResetSwiperInterval(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SwiperModelNG::SetAutoPlayInterval(frameNode, DEFAULT_INTERVAL);
}

void SetSwiperAutoPlay(NodeHandle node, bool autoPlay)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SwiperModelNG::SetAutoPlay(frameNode, autoPlay);
}

void ResetSwiperAutoPlay(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SwiperModelNG::SetAutoPlay(frameNode, DEFAULT_AUTO_PLAY);
}

void SetSwiperIndex(NodeHandle node, int32_t index)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    index = index < 0 ? 0 : index;
    SwiperModelNG::SetIndex(frameNode, index);
}

void ResetSwiperIndex(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    uint32_t value = 0;
    SwiperModelNG::SetIndex(frameNode, value);
}

void SetSwiperIndicator(NodeHandle node, const char* indicatorStr)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::vector<std::string> res;
    std::string indicatorValues = std::string(indicatorStr);
    StringUtils::StringSplitter(indicatorValues, '|', res);
    std::string type = res[INDICATOR_TYPE_INDEX];
    if (type == "ArkDigitIndicator") {
        SwiperModelNG::SetIndicatorIsBoolean(frameNode, false);
        SwiperDigitalParameters digitalParameters = GetDigitIndicatorInfo(res);
        SwiperModelNG::SetDigitIndicatorStyle(frameNode, digitalParameters);
        SwiperModelNG::SetIndicatorType(frameNode, SwiperIndicatorType::DIGIT);
    } else if (type == "ArkDotIndicator") {
        SwiperModelNG::SetIndicatorIsBoolean(frameNode, false);
        SwiperParameters swiperParameters = GetDotIndicatorInfo(frameNode, res);
        SwiperModelNG::SetDotIndicatorStyle(frameNode, swiperParameters);
        SwiperModelNG::SetIndicatorType(frameNode, SwiperIndicatorType::DOT);
    } else {
        SwiperParameters swiperParameters = GetDotIndicatorInfo(frameNode, res);
        SwiperModelNG::SetDotIndicatorStyle(frameNode, swiperParameters);
        SwiperModelNG::SetIndicatorType(frameNode, SwiperIndicatorType::DOT);
    }
    if (type == "boolean") {
        int32_t indicator = StringUtils::StringToInt(res[INDICATOR_VALUE]);
        bool showIndicator = indicator == 1 ? true : false;
        SwiperModelNG::SetShowIndicator(frameNode, showIndicator);
    } else {
        SwiperModelNG::SetShowIndicator(frameNode, true);
    }
}

void ResetSwiperIndicator(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SwiperModelNG::SetShowIndicator(frameNode, true);
}

void SetSwiperDuration(NodeHandle node, int32_t duration)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (duration < 0) {
        duration = DEFAULT_DURATION;
    }
    SwiperModelNG::SetDuration(frameNode, duration);
}

void ResetSwiperDuration(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    uint32_t value = DEFAULT_DURATION;
    SwiperModelNG::SetDuration(frameNode, value);
}

void SetSwiperEnabled(NodeHandle node, bool enabled)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SwiperModelNG::SetEnabled(frameNode, enabled);
}

void ResetSwiperEnabled(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SwiperModelNG::SetEnabled(frameNode, false);
}

ArkUISwiperModifierAPI GetSwiperModifier()
{
    static const ArkUISwiperModifierAPI modifier = { SetSwiperNextMargin, ResetSwiperNextMargin, SetSwiperPrevMargin,
        ResetSwiperPrevMargin, SetSwiperDisplayCount, ResetSwiperDisplayCount, SetSwiperDisplayArrow,
        ResetSwiperDisplayArrow, SetSwiperCurve, ResetSwiperCurve, SetSwiperDisableSwipe, ResetSwiperDisableSwipe,
        SetSwiperEffectMode, ResetSwiperEffectMode, SetSwiperCachedCount, ResetSwiperCachedCount, SetSwiperDisplayMode,
        ResetSwiperDisplayMode, SetSwiperItemSpace, ResetSwiperItemSpace, SetSwiperVertical, ResetSwiperVertical,
        SetSwiperLoop, ResetSwiperLoop, SetSwiperInterval, ResetSwiperInterval, SetSwiperAutoPlay, ResetSwiperAutoPlay,
        SetSwiperIndex, ResetSwiperIndex, SetSwiperIndicator, ResetSwiperIndicator, SetSwiperDuration,
        ResetSwiperDuration, SetSwiperEnabled, ResetSwiperEnabled };
    return modifier;
}
} // namespace OHOS::Ace::NG