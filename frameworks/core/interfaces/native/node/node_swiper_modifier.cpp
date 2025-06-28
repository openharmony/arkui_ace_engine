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
#include "core/interfaces/native/node/node_swiper_modifier.h"

#include "node_model.h"

#include "bridge/common/utils/utils.h"
#include "core/components/swiper/swiper_component.h"
#include "core/components_ng/pattern/swiper/swiper_model_ng.h"
#include "core/interfaces/native/node/node_adapter_impl.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t DEFAULT_INTERVAL = 3000;
constexpr int32_t DEFAULT_DURATION = 400;
constexpr int32_t DEFAULT_CACHED_COUNT = 1;
constexpr int32_t DEFAULT_DISPLAY_COUNT = 1;
constexpr bool DEFAULT_SWIPE_BY_GROUP = false;
constexpr bool DEFAULT_CACHED_IS_SHOWN = false;
constexpr bool DEFAULT_AUTO_PLAY = false;
constexpr bool DEFAULT_LOOP = true;
constexpr bool DEAFULT_DISABLE_SWIPE = false;
constexpr int32_t ARROW_IS_SHOW_BACKGROUND = 1;
constexpr int32_t ARROW_IS_SIDE_BAR_MIDDLE = 2;
constexpr int32_t ARROW_BACKGROUND_SIZE = 3;
constexpr int32_t ARROW_BACKGROUND_COLOR = 4;
constexpr int32_t ARROW_SIZE = 5;
constexpr int32_t ARROW_COLOR = 6;
constexpr int32_t DISPLAY_ARROW_OBJECT = 2;
constexpr int32_t DISPLAY_ARROW_TRUE = 1;
constexpr int32_t DISPLAY_ARROW_VALUE = 0;
constexpr int32_t DISPLAY_ARROW_IS_HOVER_SHOW_INDEX = 7;
constexpr int32_t DISPLAY_ARROW_CAPI = 8;
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
constexpr int32_t DIGIT_INDICATOR_IGNORE_SIZE = 11;
constexpr int32_t DIGIT_INDICATOR_SET_IGNORE_SIZE = 12;
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
constexpr int32_t DOT_INDICATOR_MAX_DISPLAY_COUNT = 12;
constexpr int32_t DOT_INDICATOR_INFO_SIZE = 12;
constexpr int32_t DOT_INDICATOR_SPACE = 13;
constexpr int32_t DOT_INDICATOR_IGNORE_SIZE = 14;
constexpr int32_t DOT_INDICATOR_SET_IGNORE_SIZE = 15;
constexpr int32_t NUM_0 = 0;
constexpr int32_t NUM_1 = 1;
constexpr int32_t NUM_2 = 2;
constexpr int32_t NUM_3 = 3;
constexpr int32_t NUM_4 = 4;
constexpr float ANIMATION_INFO_DEFAULT = 0.0f;
constexpr float ARROW_SIZE_COEFFICIENT = 0.75f;
const int32_t ERROR_INT_CODE = -1;
constexpr float ZERO_F = 0.0f;
constexpr bool DEFAULT_STOP_WHEN_TOUCHED = true;
constexpr int32_t INDICATOR_RESOURCE_LEFT = 0;
constexpr int32_t INDICATOR_RESOURCE_TOP = 1;
constexpr int32_t INDICATOR_RESOURCE_RIGHT = 2;
constexpr int32_t INDICATOR_RESOURCE_BOTTOM = 3;
constexpr int32_t DOT_INDICATOR_RESOURCE_ITEM_WIDTH = 4;
constexpr int32_t DOT_INDICATOR_RESOURCE_ITEM_HEIGHT = 5;
constexpr int32_t DOT_INDICATOR_RESOURCE_SELECTED_ITEM_WIDTH = 6;
constexpr int32_t DOT_INDICATOR_RESOURCE_SELECTED_ITEM_HEIGHT = 7;
constexpr int32_t DOT_INDICATOR_RESOURCE_COLOR = 8;
constexpr int32_t DOT_INDICATOR_RESOURCE_SELECTED_COLOR = 9;
constexpr int32_t DIGIT_INDICATOR_RESOURCE_FONT_COLOR = 4;
constexpr int32_t DIGIT_INDICATOR_RESOURCE_FONT_SELECTED_COLOR = 5;
constexpr int32_t DIGIT_INDICATOR_RESOURCE_FONT_SIZE = 6;
constexpr int32_t DIGIT_INDICATOR_RESOURCE_SELECTED_FONT_SIZE = 7;
constexpr int32_t ARROW_RESOURCE_BACKGROUND_SIZE = 0;
constexpr int32_t ARROW_RESOURCE_BACKGROUND_COLOR = 1;
constexpr int32_t ARROW_RESOURCE_SIZE = 2;
constexpr int32_t ARROW_RESOURCE_COLOR = 3;

const std::vector<SwiperDisplayMode> DISPLAY_MODE = { SwiperDisplayMode::STRETCH, SwiperDisplayMode::AUTO_LINEAR };
const std::vector<EdgeEffect> EDGE_EFFECT = { EdgeEffect::SPRING, EdgeEffect::FADE, EdgeEffect::NONE };
const std::vector<SwiperIndicatorType> INDICATOR_TYPE = { SwiperIndicatorType::DOT, SwiperIndicatorType::DIGIT };
const std::vector<SwiperAnimationMode> ANIMATION_MODE = { SwiperAnimationMode::NO_ANIMATION,
    SwiperAnimationMode::DEFAULT_ANIMATION, SwiperAnimationMode::FAST_ANIMATION };
const std::vector<OHOS::Ace::RefPtr<OHOS::Ace::Curve>> CURVES = {
    OHOS::Ace::Curves::LINEAR,
    OHOS::Ace::Curves::EASE,
    OHOS::Ace::Curves::EASE_IN,
    OHOS::Ace::Curves::EASE_OUT,
    OHOS::Ace::Curves::EASE_IN_OUT,
    OHOS::Ace::Curves::FAST_OUT_SLOW_IN,
    OHOS::Ace::Curves::LINEAR_OUT_SLOW_IN,
    OHOS::Ace::Curves::FAST_OUT_LINEAR_IN,
    OHOS::Ace::Curves::EXTREME_DECELERATION,
    OHOS::Ace::Curves::SHARP,
    OHOS::Ace::Curves::RHYTHM,
    OHOS::Ace::Curves::SMOOTH,
    OHOS::Ace::Curves::FRICTION,
};
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
                ? dimension
                : swiperIndicatorTheme->GetBigArrowBackgroundSize();
        parseOk = Color::ParseColorString(backgroundColorValue, color);
        swiperArrowParameters.backgroundColor = parseOk
            ? (swiperArrowParameters.parametersByUser.insert("backgroundColor"), color)
            : swiperIndicatorTheme->GetBigArrowBackgroundColor();
        if (swiperArrowParameters.isShowBackground.value()) {
            swiperArrowParameters.arrowSize = swiperArrowParameters.backgroundSize.value() * ARROW_SIZE_COEFFICIENT;
        } else {
            parseOk = StringUtils::StringToCalcDimensionNG(arrowSizeValue, dimension, false, DimensionUnit::VP);
            swiperArrowParameters.arrowSize =
                parseOk && GreatNotEqual(dimension.ConvertToVp(), 0.0) && !(dimension.Unit() == DimensionUnit::PERCENT)
                    ? dimension
                    : swiperIndicatorTheme->GetBigArrowSize();
            swiperArrowParameters.backgroundSize = swiperArrowParameters.arrowSize;
        }
        parseOk = Color::ParseColorString(arrowColorValue, color);
        swiperArrowParameters.arrowColor = parseOk
            ? (swiperArrowParameters.parametersByUser.insert("arrowColor"), color)
            : swiperIndicatorTheme->GetBigArrowColor();
    } else {
        dimension = StringUtils::StringToCalcDimension(backgroundSizeValue, false, DimensionUnit::VP);
        swiperArrowParameters.backgroundSize =
            GreatNotEqual(dimension.ConvertToVp(), 0.0) && !(dimension.Unit() == DimensionUnit::PERCENT)
                ? dimension
                : swiperIndicatorTheme->GetSmallArrowBackgroundSize();
        parseOk = Color::ParseColorString(backgroundColorValue, color);
        swiperArrowParameters.backgroundColor = parseOk
            ? (swiperArrowParameters.parametersByUser.insert("backgroundColor"), color)
            : swiperIndicatorTheme->GetSmallArrowBackgroundColor();
        if (swiperArrowParameters.isShowBackground.value()) {
            swiperArrowParameters.arrowSize = swiperArrowParameters.backgroundSize.value() * ARROW_SIZE_COEFFICIENT;
        } else {
            parseOk = StringUtils::StringToCalcDimensionNG(arrowSizeValue, dimension, false, DimensionUnit::VP);
            swiperArrowParameters.arrowSize =
                parseOk && GreatNotEqual(dimension.ConvertToVp(), 0.0) && !(dimension.Unit() == DimensionUnit::PERCENT)
                    ? dimension
                    : swiperIndicatorTheme->GetSmallArrowSize();
            swiperArrowParameters.backgroundSize = swiperArrowParameters.arrowSize;
        }
        parseOk = Color::ParseColorString(arrowColorValue, color);
        swiperArrowParameters.arrowColor = parseOk
        ? (swiperArrowParameters.parametersByUser.insert("arrowColor"), color)
        : swiperIndicatorTheme->GetSmallArrowColor();
    }
}

bool GetArrowInfo(const std::vector<std::string>& arrowInfo, SwiperArrowParameters& swiperArrowParameters,
    const void* resObjs)
{
    auto isShowBackgroundValue = arrowInfo[ARROW_IS_SHOW_BACKGROUND];
    auto isSidebarMiddleValue = arrowInfo[ARROW_IS_SIDE_BAR_MIDDLE];

    auto pipelineContext = PipelineBase::GetCurrentContextSafely();
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
    if (SystemProperties::ConfigChangePerform() && resObjs) {
        auto resourceObjs = *(static_cast<const std::vector<RefPtr<ResourceObject>>*>(resObjs));
        swiperArrowParameters.resourceBackgroundSizeValueObject = resourceObjs.at(ARROW_RESOURCE_BACKGROUND_SIZE);
        swiperArrowParameters.resourceBackgroundColorValueObject =  resourceObjs.at(ARROW_RESOURCE_BACKGROUND_COLOR);
        swiperArrowParameters.resourceArrowSizeValueObject = resourceObjs.at(ARROW_RESOURCE_SIZE);
        swiperArrowParameters.resourceArrowColorValueObject = resourceObjs.at(ARROW_RESOURCE_COLOR);
    }
    return true;
}

std::string GetInfoFromVectorByIndex(const std::vector<std::string>& dotIndicatorInfo, int32_t index)
{
    auto dotIndicatorInfoSize = dotIndicatorInfo.size();
    return dotIndicatorInfoSize < DOT_INDICATOR_INFO_SIZE
               ? ""
               : (dotIndicatorInfo[index] == "-" ? "" : dotIndicatorInfo[index]);
}

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

void ParseMaxDisplayCount(const std::vector<std::string>& dotIndicatorInfo, SwiperParameters& swiperParameters)
{
    auto maxDisplayCount = GetInfoFromVectorByIndex(dotIndicatorInfo, DOT_INDICATOR_MAX_DISPLAY_COUNT);
    if (maxDisplayCount.empty()) {
        return;
    }

    swiperParameters.maxDisplayCountVal = StringUtils::StringToInt(maxDisplayCount);
}

void ParseDotIndicatorSize(FrameNode* frameNode, const std::vector<std::string>& dotIndicatorInfo,
    const RefPtr<SwiperIndicatorTheme>& swiperIndicatorTheme, SwiperParameters& swiperParameters)
{
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(swiperIndicatorTheme);
    auto itemWidthValue = GetInfoFromVectorByIndex(dotIndicatorInfo, DOT_INDICATOR_ITEM_WIDTH);
    auto itemHeightValue = GetInfoFromVectorByIndex(dotIndicatorInfo, DOT_INDICATOR_ITEM_HEIGHT);
    auto selectedItemWidthValue = GetInfoFromVectorByIndex(dotIndicatorInfo, DOT_INDICATOR_SELECTED_ITEM_WIDTH);
    auto selectedItemHeightValue = GetInfoFromVectorByIndex(dotIndicatorInfo, DOT_INDICATOR_SELECTED_ITEM_HEIGHT);
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
}

void GetDotIndicatorSpaceAndIgnoreSize(const std::vector<std::string>& dotIndicatorInfo,
    const RefPtr<SwiperIndicatorTheme>& swiperIndicatorTheme, SwiperParameters& swiperParameters)
{
    CHECK_NULL_VOID(swiperIndicatorTheme);
    auto spaceValue = GetInfoFromVectorByIndex(dotIndicatorInfo, DOT_INDICATOR_SPACE);
    auto ignoreSize = GetInfoFromVectorByIndex(dotIndicatorInfo, DOT_INDICATOR_IGNORE_SIZE);
    auto setIgnoreSize = GetInfoFromVectorByIndex(dotIndicatorInfo, DOT_INDICATOR_SET_IGNORE_SIZE);

    CalcDimension dimPosition = StringUtils::StringToCalcDimension(spaceValue, false, DimensionUnit::VP);
    bool parseSpaceOk = !spaceValue.empty() && dimPosition.Unit() != DimensionUnit::PERCENT;
    auto defaultSpaceSize = swiperIndicatorTheme->GetIndicatorDotItemSpace();
    swiperParameters.dimSpace = (parseSpaceOk && !(dimPosition < 0.0_vp)) ? dimPosition : defaultSpaceSize;

    swiperParameters.ignoreSizeValue = (ignoreSize == "1" ? true : false);
    swiperParameters.setIgnoreSizeValue = (setIgnoreSize == "1" ? true : false);
}

SwiperParameters GetDotIndicatorInfo(FrameNode* frameNode, const std::vector<std::string>& dotIndicatorInfo,
    const void* resObjs)
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
    SwiperParameters swiperParameters;
    auto leftValue = GetInfoFromVectorByIndex(dotIndicatorInfo, DOT_INDICATOR_LEFT);
    auto topValue = GetInfoFromVectorByIndex(dotIndicatorInfo, DOT_INDICATOR_TOP);
    auto rightValue = GetInfoFromVectorByIndex(dotIndicatorInfo, DOT_INDICATOR_RIGHT);
    auto bottomValue = GetInfoFromVectorByIndex(dotIndicatorInfo, DOT_INDICATOR_BOTTOM);
    swiperParameters.dimLeft = ParseIndicatorDimension(leftValue);
    swiperParameters.dimTop = ParseIndicatorDimension(topValue);
    swiperParameters.dimRight = ParseIndicatorDimension(rightValue);
    swiperParameters.dimBottom = ParseIndicatorDimension(bottomValue);
    if (maskValue != "2") {
        swiperParameters.maskValue = (maskValue == "1" ? true : false);
    }
    Color colorVal;
    parseOk = Color::ParseColorString(colorValue, colorVal);
    swiperParameters.colorVal = parseOk ? (swiperParameters.parametersByUser.insert("colorVal"), colorVal)
        : swiperIndicatorTheme->GetColor();
    parseOk = Color::ParseColorString(selectedColorValue, colorVal);
    swiperParameters.selectedColorVal = parseOk
        ? (swiperParameters.parametersByUser.insert("selectedColorVal"), colorVal)
        : swiperIndicatorTheme->GetSelectedColor();
    ParseDotIndicatorSize(frameNode, dotIndicatorInfo, swiperIndicatorTheme, swiperParameters);
    GetDotIndicatorSpaceAndIgnoreSize(dotIndicatorInfo, swiperIndicatorTheme, swiperParameters);
    ParseMaxDisplayCount(dotIndicatorInfo, swiperParameters);
    if (SystemProperties::ConfigChangePerform() && resObjs) {
        auto resourceObjs = *(static_cast<const std::vector<RefPtr<ResourceObject>>*>(resObjs));
        swiperParameters.resourceDimLeftValueObject = resourceObjs.at(INDICATOR_RESOURCE_LEFT);
        swiperParameters.resourceDimTopValueObject = resourceObjs.at(INDICATOR_RESOURCE_TOP);
        swiperParameters.resourceDimRightValueObject = resourceObjs.at(INDICATOR_RESOURCE_RIGHT);
        swiperParameters.resourceDimBottomValueObject = resourceObjs.at(INDICATOR_RESOURCE_BOTTOM);
        swiperParameters.resourceItemWidthValueObject = resourceObjs.at(DOT_INDICATOR_RESOURCE_ITEM_WIDTH);
        swiperParameters.resourceItemHeightValueObject = resourceObjs.at(DOT_INDICATOR_RESOURCE_ITEM_HEIGHT);
        swiperParameters.resourceSelectedItemWidthValueObject =
            resourceObjs.at(DOT_INDICATOR_RESOURCE_SELECTED_ITEM_WIDTH);
        swiperParameters.resourceSelectedItemHeightValueObject =
        resourceObjs.at(DOT_INDICATOR_RESOURCE_SELECTED_ITEM_HEIGHT);
        swiperParameters.resourceColorValueObject = resourceObjs.at(DOT_INDICATOR_RESOURCE_COLOR);
        swiperParameters.resourceSelectedColorValueObject = resourceObjs.at(DOT_INDICATOR_RESOURCE_SELECTED_COLOR);
    }
    swiperParameters.parametersByUser.insert("dotIndicator");
    return swiperParameters;
}

std::optional<Dimension> ParseIndicatorCommonDimension(const ArkUIOptionalFloat attribute, DimensionUnit unit)
{
    std::optional<Dimension> indicatorDimension;
    if (!attribute.isSet) {
        return indicatorDimension;
    }
    CalcDimension dimPosition = CalcDimension(attribute.value, unit);
    indicatorDimension = LessNotEqual(dimPosition.ConvertToPx(), 0.0f) ? 0.0_vp : dimPosition;
    return indicatorDimension;
}


void ParseIndicatorAttribute(std::optional<Dimension> dim, bool& hasValue, float& value)
{
    hasValue = dim.has_value();
    if (hasValue) {
        value = dim.value().Value();
    } else {
        value = ZERO_F;
    }
}

SwiperParameters GetDotIndicatorProps(FrameNode* frameNode, ArkUISwiperIndicator* indicator)
{
    CHECK_NULL_RETURN(frameNode, SwiperParameters());
    auto pipelineContext = frameNode->GetContext();
    CHECK_NULL_RETURN(pipelineContext, SwiperParameters());
    auto swiperIndicatorTheme = pipelineContext->GetTheme<SwiperIndicatorTheme>();
    CHECK_NULL_RETURN(swiperIndicatorTheme, SwiperParameters());
    SwiperParameters swiperParameters;
    DimensionUnit unit = static_cast<DimensionUnit>(indicator->dimUnit);
    swiperParameters.dimLeft = ParseIndicatorCommonDimension(indicator->dimLeft, unit);
    swiperParameters.dimTop = ParseIndicatorCommonDimension(indicator->dimTop, unit);
    swiperParameters.dimRight = ParseIndicatorCommonDimension(indicator->dimRight, unit);
    swiperParameters.dimBottom = ParseIndicatorCommonDimension(indicator->dimBottom, unit);
    auto defaultSize = swiperIndicatorTheme->GetSize();

    CalcDimension dimPosition = Dimension(indicator->itemWidth.value, unit);
    bool parseItemWOk = indicator->itemWidth.isSet && dimPosition.Unit() != DimensionUnit::PERCENT;
    swiperParameters.itemWidth = (parseItemWOk && (dimPosition > 0.0_vp)) ? dimPosition : defaultSize;
    dimPosition = Dimension(indicator->itemHeight.value, unit);
    bool parseItemHOk = indicator->itemHeight.isSet && dimPosition.Unit() != DimensionUnit::PERCENT;
    swiperParameters.itemHeight = (parseItemHOk && (dimPosition > 0.0_vp)) ? dimPosition : defaultSize;
    dimPosition = Dimension(indicator->selectedItemWidth.value, unit);
    bool parseSelectedItemWOk = indicator->selectedItemWidth.isSet && dimPosition.Unit() != DimensionUnit::PERCENT;
    swiperParameters.selectedItemWidth = (parseSelectedItemWOk && (dimPosition > 0.0_vp)) ? dimPosition : defaultSize;
    dimPosition = Dimension(indicator->selectedItemHeight.value, unit);
    bool parseSelectedItemHOk = indicator->selectedItemHeight.isSet && dimPosition.Unit() != DimensionUnit::PERCENT;
    swiperParameters.selectedItemHeight = (parseSelectedItemHOk && (dimPosition > 0.0_vp)) ? dimPosition : defaultSize;

    auto defaultSpace = swiperIndicatorTheme->GetIndicatorDotItemSpace();
    dimPosition = Dimension(indicator->dimSpace.value, unit);
    bool parseSpaceOk = indicator->dimSpace.isSet && dimPosition.Unit() != DimensionUnit::PERCENT;
    swiperParameters.dimSpace = (parseSpaceOk && !(dimPosition < 0.0_vp)) ? dimPosition : defaultSpace;

    if (!parseSelectedItemWOk && !parseSelectedItemHOk && !parseItemWOk && !parseItemHOk) {
        SwiperModelNG::SetIsIndicatorCustomSize(frameNode, false);
    } else {
        SwiperModelNG::SetIsIndicatorCustomSize(frameNode, true);
    }
    swiperParameters.maskValue = indicator->maskValue.value == 1 ? true : false;
    swiperParameters.colorVal =
        indicator->colorValue.isSet == 1 ? Color(indicator->colorValue.value) : swiperIndicatorTheme->GetColor();
    swiperParameters.selectedColorVal = indicator->selectedColorValue.isSet == 1 ?
        Color(indicator->selectedColorValue.value) : swiperIndicatorTheme->GetSelectedColor();
    swiperParameters.maxDisplayCountVal = indicator->maxDisplayCount.isSet == 1 ?
        indicator->maxDisplayCount.value : NUM_0;
    swiperParameters.ignoreSizeValue = indicator->ignoreSizeValue.value == 1 ? true : false;
    return swiperParameters;
}

SwiperDigitalParameters GetDigitIndicatorProps(FrameNode* frameNode, ArkUISwiperDigitIndicator* indicator)
{
    CHECK_NULL_RETURN(frameNode, SwiperDigitalParameters());
    auto pipelineContext = frameNode->GetContext();
    CHECK_NULL_RETURN(pipelineContext, SwiperDigitalParameters());
    auto swiperIndicatorTheme = pipelineContext->GetTheme<SwiperIndicatorTheme>();
    CHECK_NULL_RETURN(swiperIndicatorTheme, SwiperDigitalParameters());
    SwiperDigitalParameters swiperDigitalParameters;
    DimensionUnit unit = static_cast<DimensionUnit>(indicator->dimUnit);
    swiperDigitalParameters.dimLeft = ParseIndicatorCommonDimension(indicator->dimLeft, unit);
    swiperDigitalParameters.dimTop = ParseIndicatorCommonDimension(indicator->dimTop, unit);
    swiperDigitalParameters.dimRight = ParseIndicatorCommonDimension(indicator->dimRight, unit);
    swiperDigitalParameters.dimBottom = ParseIndicatorCommonDimension(indicator->dimBottom, unit);

    swiperDigitalParameters.fontColor = indicator->fontColor.isSet == 1
                                            ? Color(indicator->fontColor.value)
                                            : swiperIndicatorTheme->GetDigitalIndicatorTextStyle().GetTextColor();
    swiperDigitalParameters.selectedFontColor =
        indicator->selectedFontColor.isSet == 1 ? Color(indicator->selectedFontColor.value)
                                                : swiperIndicatorTheme->GetDigitalIndicatorTextStyle().GetTextColor();
    auto digitFontSize = ParseIndicatorCommonDimension(indicator->fontSize, unit);
    swiperDigitalParameters.fontSize = indicator->fontSize.isSet == 1 && (digitFontSize > 0.0_vp)
                                           ? digitFontSize
                                           : swiperIndicatorTheme->GetDigitalIndicatorTextStyle().GetFontSize();

    auto digitSelectedFontSize = ParseIndicatorCommonDimension(indicator->selectedFontSize, unit);
    swiperDigitalParameters.selectedFontSize =
        indicator->selectedFontSize.isSet == 1 && (digitSelectedFontSize > 0.0_vp)
            ? digitSelectedFontSize
            : swiperIndicatorTheme->GetDigitalIndicatorTextStyle().GetFontSize();

    swiperDigitalParameters.fontWeight = indicator->fontWeight.isSet == 1
                                             ? FontWeight(indicator->fontWeight.value)
                                             : swiperIndicatorTheme->GetDigitalIndicatorTextStyle().GetFontWeight();
    swiperDigitalParameters.selectedFontWeight =
        indicator->selectedFontWeight.isSet == 1 ? FontWeight(indicator->selectedFontWeight.value)
                                                 : swiperIndicatorTheme->GetDigitalIndicatorTextStyle().GetFontWeight();
    swiperDigitalParameters.ignoreSizeValue = indicator->ignoreSizeValue.value == 1 ? true : false;
    return swiperDigitalParameters;
}

void GetFontContent(
    const std::string& size, const std::string& weight, bool isSelected, SwiperDigitalParameters& digitalParameters)
{
    auto pipelineContext = PipelineBase::GetCurrentContextSafely();
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

void ParseDigitIndicatorBottomAndIgnoreSize(const std::vector<std::string>& digitIndicatorInfo,
    SwiperDigitalParameters& digitalParameters)
{
    auto digitBottomValue =
        digitIndicatorInfo[DIGIT_INDICATOR_BOTTOM] == "-" ? "" : digitIndicatorInfo[DIGIT_INDICATOR_BOTTOM];
    auto ignoreSize = digitIndicatorInfo[DIGIT_INDICATOR_IGNORE_SIZE] == "-" ? "" :
        digitIndicatorInfo[DIGIT_INDICATOR_IGNORE_SIZE];
    
    auto setIgnoreSize = digitIndicatorInfo[DIGIT_INDICATOR_SET_IGNORE_SIZE] == "-" ? "" :
        digitIndicatorInfo[DIGIT_INDICATOR_SET_IGNORE_SIZE];

    auto bottom = ParseIndicatorDimension(digitBottomValue);
    digitalParameters.dimBottom = bottom;
    if (!bottom.has_value() || (bottom.has_value() && (bottom.value() == 0.0_vp))) {
        digitalParameters.ignoreSizeValue = (ignoreSize == "1" ? true : false);
    } else {
        digitalParameters.ignoreSizeValue = false;
    }
}

SwiperDigitalParameters GetDigitIndicatorInfo(const std::vector<std::string>& digitIndicatorInfo, const void* resObjs)
{
    auto dotLeftValue = digitIndicatorInfo[DIGIT_INDICATOR_LEFT] == "-" ? "" : digitIndicatorInfo[DIGIT_INDICATOR_LEFT];
    auto dotTopValue = digitIndicatorInfo[DIGIT_INDICATOR_TOP] == "-" ? "" : digitIndicatorInfo[DIGIT_INDICATOR_TOP];
    auto dotRightValue =
        digitIndicatorInfo[DIGIT_INDICATOR_RIGHT] == "-" ? "" : digitIndicatorInfo[DIGIT_INDICATOR_RIGHT];
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

    auto pipelineContext = PipelineBase::GetCurrentContextSafely();
    CHECK_NULL_RETURN(pipelineContext, SwiperDigitalParameters());
    auto swiperIndicatorTheme = pipelineContext->GetTheme<SwiperIndicatorTheme>();
    CHECK_NULL_RETURN(swiperIndicatorTheme, SwiperDigitalParameters());
    bool parseOk = false;
    SwiperDigitalParameters digitalParameters;
    digitalParameters.dimLeft = ParseIndicatorDimension(dotLeftValue);
    digitalParameters.dimTop = ParseIndicatorDimension(dotTopValue);
    digitalParameters.dimRight = ParseIndicatorDimension(dotRightValue);

    Color fontColor;
    parseOk = Color::ParseColorString(fontColorValue, fontColor);
    digitalParameters.fontColor =
        parseOk ? (digitalParameters.parametersByUser.insert("fontColor"), fontColor)
        : swiperIndicatorTheme->GetDigitalIndicatorTextStyle().GetTextColor();
    parseOk = Color::ParseColorString(selectedFontColorValue, fontColor);
    digitalParameters.selectedFontColor =
        parseOk ? (digitalParameters.parametersByUser.insert("selectedFontColor"), fontColor)
        : swiperIndicatorTheme->GetDigitalIndicatorTextStyle().GetTextColor();
    ParseDigitIndicatorBottomAndIgnoreSize(digitIndicatorInfo, digitalParameters);
    GetFontContent(digitFontSize, digitFontWeight, false, digitalParameters);
    GetFontContent(selectedDigitFontSize, selectedDigitFontWeight, true, digitalParameters);
    if (SystemProperties::ConfigChangePerform() && resObjs) {
        auto resourceObjs = *(static_cast<const std::vector<RefPtr<ResourceObject>>*>(resObjs));
        digitalParameters.resourceDimLeftValueObject = resourceObjs.at(INDICATOR_RESOURCE_LEFT);
        digitalParameters.resourceDimTopValueObject = resourceObjs.at(INDICATOR_RESOURCE_TOP);
        digitalParameters.resourceDimRightValueObject = resourceObjs.at(INDICATOR_RESOURCE_RIGHT);
        digitalParameters.resourceDimBottomValueObject = resourceObjs.at(INDICATOR_RESOURCE_BOTTOM);
        digitalParameters.resourceFontColorValueObject = resourceObjs.at(DIGIT_INDICATOR_RESOURCE_FONT_COLOR);
        digitalParameters.resourceSelectedFontColorValueObject =
            resourceObjs.at(DIGIT_INDICATOR_RESOURCE_FONT_SELECTED_COLOR);
        digitalParameters.resourceFontSizeValueObject = resourceObjs.at(DIGIT_INDICATOR_RESOURCE_FONT_SIZE);
        digitalParameters.resourceSelectedFontSizeValueObject =
            resourceObjs.at(DIGIT_INDICATOR_RESOURCE_SELECTED_FONT_SIZE);
    }
    return digitalParameters;
}

void SetIndicatorInteractive(ArkUINodeHandle node, ArkUI_Bool value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SwiperModelNG::SetIndicatorInteractive(frameNode, static_cast<bool>(value));
}

void ResetIndicatorInteractive(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SwiperModelNG::SetIndicatorInteractive(frameNode, true);
}

ArkUI_Int32 GetIndicatorInteractive(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_INT_CODE);
    return static_cast<ArkUI_Int32>(SwiperModelNG::GetIndicatorInteractive(frameNode));
}

void SetSwiperNextMargin(ArkUINodeHandle node, ArkUI_Float32 nextMarginValue, ArkUI_Int32 nextMarginUnit,
    ArkUI_Bool ignoreBlank)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SwiperModelNG::SetNextMargin(
        frameNode, CalcDimension(nextMarginValue, (DimensionUnit)nextMarginUnit), static_cast<bool>(ignoreBlank));
}

void SetSwiperNextMarginRAw(ArkUINodeHandle node, ArkUI_Float32 nextMarginValue, ArkUI_Int32 nextMarginUnit,
    ArkUI_Bool ignoreBlank, void* nextMarginRawPtr)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SwiperModelNG::SetNextMargin(
        frameNode, CalcDimension(nextMarginValue, (DimensionUnit)nextMarginUnit), static_cast<bool>(ignoreBlank));
    if (SystemProperties::ConfigChangePerform()) {
        auto* nextMargin = reinterpret_cast<ResourceObject*>(nextMarginRawPtr);
        auto nextMarginResObj = AceType::Claim(nextMargin);
        SwiperModel::GetInstance()->ProcessNextMarginwithResourceObj(nextMarginResObj);
    }
}

void ResetSwiperNextMargin(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CalcDimension value(0.0, DimensionUnit::VP);
    SwiperModelNG::SetNextMargin(frameNode, value);
    if (SystemProperties::ConfigChangePerform()) {
        auto nextMarginResObj = AceType::MakeRefPtr<ResourceObject>();
        SwiperModel::GetInstance()->ProcessNextMarginwithResourceObj(nextMarginResObj);
    }
}

void SetSwiperMinSize(ArkUINodeHandle node, ArkUI_Float32 minSizeValue, ArkUI_Int32 minSizeUnitt)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SwiperModelNG::SetMinSize(frameNode, CalcDimension(minSizeValue, (DimensionUnit)minSizeUnitt));
}

void ResetSwiperMinSize(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CalcDimension value(0.0, DimensionUnit::VP);
    SwiperModelNG::SetMinSize(frameNode, value);
}

void SetSwiperPrevMargin(ArkUINodeHandle node, ArkUI_Float32 prevMarginValue, ArkUI_Int32 prevMarginUnit,
    ArkUI_Bool ignoreBlank)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SwiperModelNG::SetPreviousMargin(
        frameNode, CalcDimension(prevMarginValue, (DimensionUnit)prevMarginUnit), static_cast<bool>(ignoreBlank));
}

void SetSwiperPrevMarginRaw(ArkUINodeHandle node, ArkUI_Float32 prevMarginValue, ArkUI_Int32 prevMarginUnit,
    ArkUI_Bool ignoreBlank, void* prevMarginRawPtr)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SwiperModelNG::SetPreviousMargin(
        frameNode, CalcDimension(prevMarginValue, (DimensionUnit)prevMarginUnit), static_cast<bool>(ignoreBlank));
    if (SystemProperties::ConfigChangePerform()) {
        auto* prevMargin = reinterpret_cast<ResourceObject*>(prevMarginRawPtr);
        auto prevMarginResObj = AceType::Claim(prevMargin);
        SwiperModel::GetInstance()->ProcessPreviousMarginwithResourceObj(prevMarginResObj);
    }
}

void ResetSwiperPrevMargin(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CalcDimension value(0.0, DimensionUnit::VP);
    SwiperModelNG::SetPreviousMargin(frameNode, value);
    if (SystemProperties::ConfigChangePerform()) {
        auto prevMarginResObj = AceType::MakeRefPtr<ResourceObject>();
        SwiperModel::GetInstance()->ProcessPreviousMarginwithResourceObj(prevMarginResObj);
    }
}

void SetSwiperDisplayCount(ArkUINodeHandle node, ArkUI_CharPtr displayCountChar, ArkUI_CharPtr displayCountType)
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

void ResetSwiperDisplayCount(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SwiperModelNG::SetDisplayCount(frameNode, DEFAULT_DISPLAY_COUNT);
}

void SetSwiperSwipeByGroup(ArkUINodeHandle node, ArkUI_Bool swipeByGroup)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SwiperModelNG::SetSwipeByGroup(frameNode, swipeByGroup);
}

void ResetSwiperSwipeByGroup(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SwiperModelNG::SetSwipeByGroup(frameNode, DEFAULT_SWIPE_BY_GROUP);
}

void InitSwiperArrowParameters(
    SwiperArrowParameters& swiperArrowParameters, RefPtr<SwiperIndicatorTheme> swiperIndicatorTheme)
{
    swiperArrowParameters.isShowBackground = swiperIndicatorTheme->GetIsShowArrowBackground();
    swiperArrowParameters.isSidebarMiddle = swiperIndicatorTheme->GetIsSidebarMiddle();
    swiperArrowParameters.backgroundSize = swiperIndicatorTheme->GetSmallArrowBackgroundSize();
    swiperArrowParameters.backgroundColor = swiperIndicatorTheme->GetSmallArrowBackgroundColor();
    swiperArrowParameters.arrowSize = swiperIndicatorTheme->GetSmallArrowSize();
    swiperArrowParameters.arrowColor = swiperIndicatorTheme->GetSmallArrowColor();
}

int32_t VectorStringToInt(std::vector<std::string>& vectorStr, int32_t index)
{
    int32_t value = 0;
    if (index < static_cast<int32_t>(vectorStr.size())) {
        value = StringUtils::StringToInt(vectorStr[index]);
    }
    return value;
}

void SetSwiperDisplayArrow(ArkUINodeHandle node, ArkUI_CharPtr displayArrowStr)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::vector<std::string> res;
    std::string displayArrowValues = std::string(displayArrowStr);
    StringUtils::StringSplitter(displayArrowValues, '|', res);
    int32_t displayArrowValue = VectorStringToInt(res, DISPLAY_ARROW_VALUE);
    int32_t displayArrowCAPI = VectorStringToInt(res, DISPLAY_ARROW_CAPI);
    if (displayArrowValue == DISPLAY_ARROW_OBJECT) {
        SwiperArrowParameters swiperArrowParameters;
        if (!GetArrowInfo(res, swiperArrowParameters, nullptr)) {
            SwiperModelNG::SetDisplayArrow(frameNode, false);
            return;
        }
        SwiperModelNG::SetArrowStyle(frameNode, swiperArrowParameters);
        SwiperModelNG::SetDisplayArrow(frameNode, true);
    } else if (displayArrowValue == DISPLAY_ARROW_TRUE) {
        if (displayArrowCAPI == 1) {
            SwiperArrowParameters swiperArrowParameters;
            if (!GetArrowInfo(res, swiperArrowParameters, nullptr)) {
                SwiperModelNG::SetDisplayArrow(frameNode, false);
                return;
            }
            SwiperModelNG::SetArrowStyle(frameNode, swiperArrowParameters);
            SwiperModelNG::SetDisplayArrow(frameNode, true);
        } else {
            auto pipelineContext = frameNode->GetContext();
            CHECK_NULL_VOID(pipelineContext);
            auto swiperIndicatorTheme = pipelineContext->GetTheme<SwiperIndicatorTheme>();
            CHECK_NULL_VOID(swiperIndicatorTheme);
            SwiperArrowParameters swiperArrowParameters;
            InitSwiperArrowParameters(swiperArrowParameters, swiperIndicatorTheme);
            SwiperModelNG::SetArrowStyle(frameNode, swiperArrowParameters);
            SwiperModelNG::SetDisplayArrow(frameNode, true);
        }
    } else {
        SwiperModelNG::SetDisplayArrow(frameNode, false);
        return;
    }
    int32_t isHoverShow = VectorStringToInt(res, DISPLAY_ARROW_IS_HOVER_SHOW_INDEX);
    if (isHoverShow != DISPLAY_ARROW_IS_HOVER_SHOW_UNDEFINED) {
        SwiperModelNG::SetHoverShow(frameNode, isHoverShow == 1 ? true : false);
    } else {
        SwiperModelNG::SetHoverShow(frameNode, false);
    }
}

void SetSwiperDisplayArrowRaw(ArkUINodeHandle node, ArkUI_CharPtr displayArrowStr, const void* resObjs)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::vector<std::string> res;
    std::string displayArrowValues = std::string(displayArrowStr);
    StringUtils::StringSplitter(displayArrowValues, '|', res);
    int32_t displayArrowValue = VectorStringToInt(res, DISPLAY_ARROW_VALUE);
    int32_t displayArrowCAPI = VectorStringToInt(res, DISPLAY_ARROW_CAPI);
    if (displayArrowValue == DISPLAY_ARROW_OBJECT) {
        SwiperArrowParameters swiperArrowParameters;
        if (!GetArrowInfo(res, swiperArrowParameters, resObjs)) {
            SwiperModelNG::SetDisplayArrow(frameNode, false);
            return;
        }
        SwiperModelNG::SetArrowStyle(frameNode, swiperArrowParameters);
        SwiperModelNG::SetDisplayArrow(frameNode, true);
    } else if (displayArrowValue == DISPLAY_ARROW_TRUE) {
        if (displayArrowCAPI == 1) {
            SwiperArrowParameters swiperArrowParameters;
            if (!GetArrowInfo(res, swiperArrowParameters, resObjs)) {
                SwiperModelNG::SetDisplayArrow(frameNode, false);
                return;
            }
            SwiperModelNG::SetArrowStyle(frameNode, swiperArrowParameters);
            SwiperModelNG::SetDisplayArrow(frameNode, true);
        } else {
            auto pipelineContext = frameNode->GetContext();
            CHECK_NULL_VOID(pipelineContext);
            auto swiperIndicatorTheme = pipelineContext->GetTheme<SwiperIndicatorTheme>();
            CHECK_NULL_VOID(swiperIndicatorTheme);
            SwiperArrowParameters swiperArrowParameters;
            InitSwiperArrowParameters(swiperArrowParameters, swiperIndicatorTheme);
            SwiperModelNG::SetArrowStyle(frameNode, swiperArrowParameters);
            SwiperModelNG::SetDisplayArrow(frameNode, true);
        }
    } else {
        SwiperModelNG::SetDisplayArrow(frameNode, false);
        return;
    }
    int32_t isHoverShow = VectorStringToInt(res, DISPLAY_ARROW_IS_HOVER_SHOW_INDEX);
    if (isHoverShow != DISPLAY_ARROW_IS_HOVER_SHOW_UNDEFINED) {
        SwiperModelNG::SetHoverShow(frameNode, isHoverShow == 1 ? true : false);
    } else {
        SwiperModelNG::SetHoverShow(frameNode, false);
    }
}

void ResetSwiperDisplayArrow(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SwiperModelNG::ResetArrowStyle(frameNode);
    SwiperModelNG::SetDisplayArrow(frameNode, false);
}

void SetSwiperCurve(ArkUINodeHandle node, ArkUI_CharPtr curveChar)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    RefPtr<Curve> curve = Curves::LINEAR;
    curve = Framework::CreateCurve(curveChar);
    SwiperModelNG::SetCurve(frameNode, curve);
}

void ResetSwiperCurve(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    RefPtr<Curve> curve = Curves::LINEAR;
    SwiperModelNG::SetCurve(frameNode, curve);
}

void SetSwiperDisableSwipe(ArkUINodeHandle node, ArkUI_Bool disableSwipe)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SwiperModelNG::SetDisableSwipe(frameNode, disableSwipe);
}

void ResetSwiperDisableSwipe(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SwiperModelNG::SetDisableSwipe(frameNode, DEAFULT_DISABLE_SWIPE);
}

void SetSwiperEffectMode(ArkUINodeHandle node, ArkUI_Int32 edgeEffect)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (edgeEffect < 0 || edgeEffect >= static_cast<int32_t>(EDGE_EFFECT.size())) {
        return;
    }
    SwiperModelNG::SetEdgeEffect(frameNode, EDGE_EFFECT[edgeEffect]);
}

void ResetSwiperEffectMode(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SwiperModelNG::SetEdgeEffect(frameNode, EdgeEffect::SPRING);
}

void SetSwiperCachedCount(ArkUINodeHandle node, ArkUI_Int32 cachedCount)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (cachedCount < 0) {
        cachedCount = DEFAULT_CACHED_COUNT;
    }
    SwiperModelNG::SetCachedCount(frameNode, cachedCount);
}

void ResetSwiperCachedCount(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    int32_t value = DEFAULT_CACHED_COUNT;
    SwiperModelNG::SetCachedCount(frameNode, value);
}

void SetSwiperIsShown(ArkUINodeHandle node, ArkUI_Bool isShown)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SwiperModelNG::SetCachedIsShown(frameNode, isShown);
}

void ResetSwiperIsShown(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SwiperModelNG::SetCachedIsShown(frameNode, DEFAULT_CACHED_IS_SHOWN);
}

ArkUI_Int32 GetSwiperCachedIsShown(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_INT_CODE);
    return static_cast<ArkUI_Int32>(SwiperModelNG::GetCachedIsShown(frameNode));
}

void SetSwiperDisplayMode(ArkUINodeHandle node, ArkUI_Int32 displayMode)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (displayMode < 0 || displayMode >= static_cast<int32_t>(DISPLAY_MODE.size())) {
        return;
    }
    SwiperModelNG::SetDisplayMode(frameNode, DISPLAY_MODE[displayMode]);
}

void ResetSwiperDisplayMode(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SwiperModelNG::SetDisplayMode(frameNode, SwiperDisplayMode::STRETCH);
}

void SetSwiperItemSpace(ArkUINodeHandle node, ArkUI_Float32 itemSpaceValue, ArkUI_Int32 itemSpaceUnit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SwiperModelNG::SetItemSpace(frameNode, CalcDimension(itemSpaceValue, (DimensionUnit)itemSpaceUnit));
}

void ResetSwiperItemSpace(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CalcDimension value(0.0, DimensionUnit::VP);
    SwiperModelNG::SetItemSpace(frameNode, value);
}

void SetSwiperVertical(ArkUINodeHandle node, ArkUI_Bool isVertical)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SwiperModelNG::SetDirection(frameNode, isVertical ? Axis::VERTICAL : Axis::HORIZONTAL);
}

void ResetSwiperVertical(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SwiperModelNG::SetDirection(frameNode, Axis::HORIZONTAL);
}

void SetSwiperLoop(ArkUINodeHandle node, ArkUI_Bool loop)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SwiperModelNG::SetLoop(frameNode, loop);
}

void ResetSwiperLoop(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SwiperModelNG::SetLoop(frameNode, DEFAULT_LOOP);
}

void SetSwiperInterval(ArkUINodeHandle node, ArkUI_Int32 interval)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (interval < 0) {
        interval = DEFAULT_INTERVAL;
    }
    SwiperModelNG::SetAutoPlayInterval(frameNode, interval);
}

void ResetSwiperInterval(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SwiperModelNG::SetAutoPlayInterval(frameNode, DEFAULT_INTERVAL);
}

void SetSwiperAutoPlay(ArkUINodeHandle node, ArkUI_Bool autoPlay)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SwiperModelNG::SetAutoPlay(frameNode, autoPlay);
}

void ResetSwiperAutoPlay(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SwiperModelNG::SetAutoPlay(frameNode, DEFAULT_AUTO_PLAY);
}

void SetSwiperStopWhenTouched(ArkUINodeHandle node, ArkUI_Bool stopWhenTouched)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);

    SwiperAutoPlayOptions swiperAutoPlayOptions;
    swiperAutoPlayOptions.stopWhenTouched = stopWhenTouched;
    SwiperModelNG::SetAutoPlayOptions(frameNode, swiperAutoPlayOptions);
}

void ResetSwiperStopWhenTouched(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SwiperAutoPlayOptions swiperAutoPlayOptions;
    swiperAutoPlayOptions.stopWhenTouched = DEFAULT_STOP_WHEN_TOUCHED;
    SwiperModelNG::SetAutoPlayOptions(frameNode, swiperAutoPlayOptions);
}

void SetSwiperIndex(ArkUINodeHandle node, ArkUI_Int32 index, ArkUI_Int32 animationMode)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    index = index < 0 ? 0 : index;
    if (animationMode <= static_cast<int32_t>(SwiperAnimationMode::NO_ANIMATION) ||
        animationMode >= static_cast<int32_t>(ANIMATION_MODE.size())) {
        SwiperModelNG::SetIndex(frameNode, index);
        return;
    }
    SwiperModelNG::SetSwiperToIndex(frameNode, index, static_cast<SwiperAnimationMode>(animationMode));
}

void ResetSwiperIndex(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    uint32_t value = 0;
    SwiperModelNG::SetIndex(frameNode, value);
}

void SetSwiperIndicator(ArkUINodeHandle node, ArkUI_CharPtr indicatorStr)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::vector<std::string> res;
    std::string indicatorValues = std::string(indicatorStr);
    StringUtils::StringSplitter(indicatorValues, '|', res);
    std::string type = res[INDICATOR_TYPE_INDEX];
    if (type == "IndicatorComponentController") {
        SwiperModelNG::SetBindIndicator(frameNode, true);
        return;
    }
    if (type == "ArkDigitIndicator") {
        SwiperModelNG::SetIndicatorIsBoolean(frameNode, false);
        SwiperDigitalParameters digitalParameters = GetDigitIndicatorInfo(res, nullptr);
        SwiperModelNG::SetDigitIndicatorStyle(frameNode, digitalParameters);
        SwiperModelNG::SetIndicatorType(frameNode, SwiperIndicatorType::DIGIT);
    } else if (type == "ArkDotIndicator") {
        SwiperModelNG::SetIndicatorIsBoolean(frameNode, false);
        SwiperParameters swiperParameters = GetDotIndicatorInfo(frameNode, res, nullptr);
        SwiperModelNG::SetDotIndicatorStyle(frameNode, swiperParameters);
        SwiperModelNG::SetIndicatorType(frameNode, SwiperIndicatorType::DOT);
    } else {
        SwiperParameters swiperParameters = GetDotIndicatorInfo(frameNode, res, nullptr);
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

void SetSwiperIndicatorRaw(ArkUINodeHandle node, ArkUI_CharPtr indicatorStr, const void* resObjs)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::vector<std::string> res;
    std::string indicatorValues = std::string(indicatorStr);
    StringUtils::StringSplitter(indicatorValues, '|', res);
    std::string type = res[INDICATOR_TYPE_INDEX];
    if (type == "IndicatorComponentController") {
        SwiperModelNG::SetBindIndicator(frameNode, true);
        return;
    }
    if (type == "ArkDigitIndicator") {
        SwiperModelNG::SetIndicatorIsBoolean(frameNode, false);
        SwiperDigitalParameters digitalParameters = GetDigitIndicatorInfo(res, resObjs);
        SwiperModelNG::SetDigitIndicatorStyle(frameNode, digitalParameters);
        SwiperModelNG::SetIndicatorType(frameNode, SwiperIndicatorType::DIGIT);
    } else if (type == "ArkDotIndicator") {
        SwiperModelNG::SetIndicatorIsBoolean(frameNode, false);
        SwiperParameters swiperParameters = GetDotIndicatorInfo(frameNode, res, resObjs);
        SwiperModelNG::SetDotIndicatorStyle(frameNode, swiperParameters);
        SwiperModelNG::SetIndicatorType(frameNode, SwiperIndicatorType::DOT);
    } else {
        SwiperParameters swiperParameters = GetDotIndicatorInfo(frameNode, res, resObjs);
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

void ResetSwiperIndicator(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SwiperModelNG::ResetIndicatorStyle(frameNode);
    SwiperModelNG::SetShowIndicator(frameNode, true);
}

void SetSwiperDuration(ArkUINodeHandle node, ArkUI_Float32 duration)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (duration < 0) {
        duration = DEFAULT_DURATION;
    }
    SwiperModelNG::SetDuration(frameNode, duration);
}

void ResetSwiperDuration(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    uint32_t value = DEFAULT_DURATION;
    SwiperModelNG::SetDuration(frameNode, value);
}

void SetSwiperEnabled(ArkUINodeHandle node, ArkUI_Bool enabled)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SwiperModelNG::SetEnabled(frameNode, enabled);
}

void ResetSwiperEnabled(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SwiperModelNG::SetEnabled(frameNode, false);
}

ArkUI_Int32 GetSwiperLoop(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_INT_CODE);
    return static_cast<ArkUI_Int32>(SwiperModelNG::GetLoop(frameNode));
}

ArkUI_Int32 GetSwiperAutoPlay(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_INT_CODE);
    return static_cast<ArkUI_Int32>(SwiperModelNG::GetAutoPlay(frameNode));
}

ArkUI_Int32 GetSwiperStopWhenTouched(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_INT_CODE);
    return static_cast<ArkUI_Int32>(SwiperModelNG::GetAutoPlayOptions(frameNode).stopWhenTouched);
}

ArkUI_Int32 GetSwiperIndex(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_INT_CODE);
    return static_cast<ArkUI_Int32>(SwiperModelNG::GetIndex(frameNode));
}

ArkUI_Int32 GetSwiperVertical(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_INT_CODE);
    return static_cast<ArkUI_Int32>(SwiperModelNG::GetDirection(frameNode) == Axis::VERTICAL ? true : false);
}

ArkUI_Float32 GetSwiperDuration(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_INT_CODE);
    return static_cast<ArkUI_Float32>(SwiperModelNG::GetDuration(frameNode));
}

ArkUI_Int32 GetSwiperDisplayCount(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_INT_CODE);
    return SwiperModelNG::GetDisplayCount(frameNode);
}

ArkUI_Int32 GetSwiperSwipeByGroup(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_INT_CODE);
    return static_cast<ArkUI_Int32>(SwiperModelNG::GetSwipeByGroup(frameNode));
}

ArkUI_Float32 GetSwiperInterval(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_INT_CODE);
    return static_cast<ArkUI_Float32>(SwiperModelNG::GetAutoPlayInterval(frameNode));
}

int32_t findCurveIndex(const RefPtr<Curve> curve)
{
    CHECK_NULL_RETURN(curve, 0);
    auto iterator = std::find(CURVES.begin(), CURVES.end(), curve);
    if (iterator == CURVES.end()) {
        return 0;
    }
    return iterator - CURVES.begin();
}

ArkUI_Int32 GetSwiperCurve(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_INT_CODE);
    return findCurveIndex(SwiperModelNG::GetCurve(frameNode));
}

ArkUI_Int32 GetSwiperDisableSwipe(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_INT_CODE);
    return static_cast<ArkUI_Int32>(SwiperModelNG::GetDisableSwipe(frameNode));
}

ArkUI_Float32 GetSwiperItemSpace(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_INT_CODE);
    return SwiperModelNG::GetItemSpace(frameNode);
}

ArkUI_Int32 GetSwiperShowIndicator(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_INT_CODE);
    return static_cast<ArkUI_Int32>(SwiperModelNG::GetShowIndicator(frameNode));
}

ArkUI_Int32 GetSwiperShowDisplayArrow(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_INT_CODE);
    return static_cast<ArkUI_Int32>(SwiperModelNG::GetShowDisplayArrow(frameNode));
}

void SetSwiperArrowStyle(ArkUISwiperArrowStyle& arrowStyle, SwiperArrowParameters& swiperArrowParameters,
    RefPtr<SwiperIndicatorTheme> swiperIndicatorTheme)
{
    Dimension defaultBackGroundSize;
    Color defaultBackGroundColor;
    Dimension defaultArrowSize;
    if (arrowStyle.showSidebarMiddle.value) {
        defaultBackGroundSize = swiperIndicatorTheme->GetBigArrowBackgroundSize();
        defaultBackGroundColor = swiperIndicatorTheme->GetBigArrowBackgroundColor();
        defaultArrowSize = swiperIndicatorTheme->GetBigArrowSize();
    } else {
        defaultBackGroundSize = swiperIndicatorTheme->GetSmallArrowBackgroundSize();
        defaultBackGroundColor = swiperIndicatorTheme->GetSmallArrowBackgroundColor();
        defaultArrowSize = swiperIndicatorTheme->GetSmallArrowSize();
    }
    if (swiperArrowParameters.backgroundSize.has_value()) {
        arrowStyle.backgroundSize.value = swiperArrowParameters.backgroundSize.value().Value();
        arrowStyle.backgroundSize.isSet = 1;
    } else {
        arrowStyle.backgroundSize.value = defaultBackGroundSize.Value();
    }
    if (swiperArrowParameters.backgroundColor.has_value()) {
        arrowStyle.backgroundColor.value = swiperArrowParameters.backgroundColor.value().GetValue();
        arrowStyle.backgroundColor.isSet = 1;
    } else {
        arrowStyle.backgroundColor.value = defaultBackGroundColor.GetValue();
    }
    if (swiperArrowParameters.arrowSize.has_value()) {
        arrowStyle.arrowSize.value = swiperArrowParameters.arrowSize.value().Value();
        arrowStyle.arrowSize.isSet = 1;
    } else {
        arrowStyle.arrowSize.value = defaultArrowSize.Value();
    }
    if (swiperArrowParameters.arrowColor.has_value()) {
        arrowStyle.arrowColor.value = swiperArrowParameters.arrowColor.value().GetValue();
        arrowStyle.arrowColor.isSet = 1;
    } else {
        arrowStyle.arrowColor.value = 0x00182431;
    }
}

ArkUISwiperArrowStyle GetSwiperArrowStyle(ArkUINodeHandle node)
{
    ArkUISwiperArrowStyle arrowStyle;
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, arrowStyle);
    SwiperArrowParameters swiperArrowParameters = SwiperModelNG::GetArrowStyle(frameNode);
    auto pipelineContext = PipelineBase::GetCurrentContext();
    CHECK_NULL_RETURN(pipelineContext, arrowStyle);
    auto swiperIndicatorTheme = pipelineContext->GetTheme<SwiperIndicatorTheme>();
    CHECK_NULL_RETURN(swiperIndicatorTheme, arrowStyle);
    if (swiperArrowParameters.isShowBackground.has_value()) {
        arrowStyle.showBackground.value = swiperArrowParameters.isShowBackground.value();
        arrowStyle.showBackground.isSet = 1;
    } else {
        arrowStyle.showBackground.value = 0;
    }
    if (swiperArrowParameters.isSidebarMiddle.has_value()) {
        arrowStyle.showSidebarMiddle.value = swiperArrowParameters.isSidebarMiddle.value();
        arrowStyle.showSidebarMiddle.isSet = 1;
    } else {
        arrowStyle.showSidebarMiddle.value = 0;
    }

    SetSwiperArrowStyle(arrowStyle, swiperArrowParameters, swiperIndicatorTheme);
    return arrowStyle;
}

ArkUI_Int32 GetSwiperEffectMode(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_INT_CODE);
    return static_cast<ArkUI_Int32>(SwiperModelNG::GetEffectMode(frameNode));
}

ArkUI_CharPtr GetSwiperDisplayMode(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, "");
    auto type = "";
    if (SwiperModelNG::GetDisplayMode(frameNode) == SwiperDisplayMode::AUTO_LINEAR) {
        type = "auto";
    }
 
    return type;
}

ArkUI_Int32 SetNodeAdapter(ArkUINodeHandle node, ArkUINodeAdapterHandle handle)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_CODE_PARAM_INVALID);
    auto totalChildCount = SwiperModelNG::RealTotalCount(frameNode);
    if (totalChildCount > 0) {
        return ERROR_CODE_NATIVE_IMPL_NODE_ADAPTER_CHILD_NODE_EXIST;
    }
    NodeAdapter::GetNodeAdapterAPI()->attachHostNode(handle, node);
    return ERROR_CODE_NO_ERROR;
}

void ResetNodeAdapter(ArkUINodeHandle node)
{
    NodeAdapter::GetNodeAdapterAPI()->detachHostNode(node);
}

ArkUINodeAdapterHandle GetNodeAdapter(ArkUINodeHandle node)
{
    return NodeAdapter::GetNodeAdapterAPI()->getNodeAdapter(node);
}

ArkUI_Int32 GetCachedCount(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, 1);
    return SwiperModelNG::GetCachedCount(frameNode);
}

void SetSwiperNestedScroll(ArkUINodeHandle node, ArkUI_Int32 (*values)[1])
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SwiperModelNG::SetNestedScroll(frameNode, (*values)[0]);
}

void ResetSwiperNestedScroll(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SwiperModelNG::SetNestedScroll(frameNode, 0);
}

ArkUI_Int32 GetSwiperNestedScroll(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_CODE_PARAM_INVALID);
    return SwiperModelNG::GetNestedScroll(frameNode);
}

void SetSwiperToIndex(ArkUINodeHandle node, ArkUI_Int32 (*values)[2])
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SwiperModelNG::SetSwiperToIndex(frameNode, (*values)[0], (*values)[1]);
}

void GetSwiperPrevMargin(ArkUINodeHandle node, ArkUI_Int32 unit, ArkUISwiperMarginOptions* options)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(options);
    SwiperMarginOptions marginOptions;
    SwiperModelNG::GetPreviousMargin(frameNode, unit, &marginOptions);
    options->margin = static_cast<ArkUI_Float32>(marginOptions.margin);
    options->ignoreBlank = static_cast<ArkUI_Bool>(marginOptions.ignoreBlank);
}

ArkUI_Float32 GetSwiperMinSize(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_INT_CODE);
    return SwiperModelNG::GetMinSize(frameNode);
}

void GetSwiperNextMargin(ArkUINodeHandle node, ArkUI_Int32 unit, ArkUISwiperMarginOptions* options)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(options);
    SwiperMarginOptions marginOptions;
    SwiperModelNG::GetNextMargin(frameNode, unit, &marginOptions);
    options->margin = static_cast<ArkUI_Float32>(marginOptions.margin);
    options->ignoreBlank = static_cast<ArkUI_Bool>(marginOptions.ignoreBlank);
}

void SetSwiperIndicatorStyle(ArkUINodeHandle node, ArkUISwiperIndicator* indicator)
{
    CHECK_NULL_VOID(indicator);
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (indicator->type == ArkUISwiperIndicatorType::DOT) {
        SwiperModelNG::SetIndicatorIsBoolean(frameNode, false);
        SwiperParameters swiperParameters = GetDotIndicatorProps(frameNode, indicator);
        SwiperModelNG::SetDotIndicatorStyle(frameNode, swiperParameters);
        SwiperModelNG::SetIndicatorType(frameNode, SwiperIndicatorType::DOT);
    }
    SwiperModelNG::SetShowIndicator(frameNode, true);
}

void GetSwiperIndicator(ArkUINodeHandle node, ArkUISwiperIndicator* props)
{
    CHECK_NULL_VOID(props);
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    int32_t type = SwiperModelNG::GetIndicatorType(frameNode);
    props->type = static_cast<ArkUISwiperIndicatorType>(type);
    auto params = SwiperModelNG::GetDotIndicator(frameNode);
    CHECK_NULL_VOID(params);
    bool hasValue = false;
    float value = ZERO_F;
    ParseIndicatorAttribute(params->dimLeft, hasValue, value);
    props->dimLeft = ArkUIOptionalFloat { hasValue, value };
    ParseIndicatorAttribute(params->dimTop, hasValue, value);
    props->dimTop = ArkUIOptionalFloat { hasValue, value };
    ParseIndicatorAttribute(params->dimRight, hasValue, value);
    props->dimRight = ArkUIOptionalFloat { hasValue, value };
    ParseIndicatorAttribute(params->dimBottom, hasValue, value);
    props->dimBottom = ArkUIOptionalFloat { hasValue, value };
    props->ignoreSizeValue = ArkUIOptionalInt { 1, params->ignoreSizeValue.value_or(0) };
    if (props->type == ArkUISwiperIndicatorType::DOT) {
        props->type = ArkUISwiperIndicatorType::DOT;
        ParseIndicatorAttribute(params->itemWidth, hasValue, value);
        props->itemWidth = ArkUIOptionalFloat { hasValue, value };
        ParseIndicatorAttribute(params->itemHeight, hasValue, value);
        props->itemHeight = ArkUIOptionalFloat { hasValue, value };
        ParseIndicatorAttribute(params->selectedItemWidth, hasValue, value);
        props->selectedItemWidth = ArkUIOptionalFloat { hasValue, value };
        ParseIndicatorAttribute(params->selectedItemHeight, hasValue, value);
        props->selectedItemHeight = ArkUIOptionalFloat { hasValue, value };
        props->maskValue = ArkUIOptionalInt { 1, params->maskValue.value_or(0) };
        props->colorValue = ArkUIOptionalUint { 1, params->colorVal.value().GetValue() };
        props->selectedColorValue = ArkUIOptionalUint { 1, params->selectedColorVal.value().GetValue() };
        props->maxDisplayCount = ArkUIOptionalInt { 1, params->maxDisplayCountVal.value() };
        ParseIndicatorAttribute(params->dimSpace, hasValue, value);
        props->dimSpace = ArkUIOptionalFloat { hasValue, value };
    }
}

void SetSwiperDigitIndicatorStyle(ArkUINodeHandle node, ArkUISwiperDigitIndicator* indicator)
{
    CHECK_NULL_VOID(indicator);
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (indicator->type == ArkUISwiperIndicatorType::DIGIT) {
        SwiperModelNG::SetIndicatorIsBoolean(frameNode, false);
        SwiperDigitalParameters swiperDigitParameters = GetDigitIndicatorProps(frameNode, indicator);
        SwiperModelNG::SetDigitIndicatorStyle(frameNode, swiperDigitParameters);
        SwiperModelNG::SetIndicatorType(frameNode, SwiperIndicatorType::DIGIT);
    }
    SwiperModelNG::SetShowIndicator(frameNode, true);
}

void GetSwiperDigitIndicator(ArkUINodeHandle node, ArkUISwiperDigitIndicator* props)
{
    CHECK_NULL_VOID(props);
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    int32_t type = SwiperModelNG::GetIndicatorType(frameNode);
    props->type = static_cast<ArkUISwiperIndicatorType>(type);
    auto params = SwiperModelNG::GetDigitIndicator(frameNode);
    CHECK_NULL_VOID(params);
    bool hasValue = false;
    float value = ZERO_F;
    ParseIndicatorAttribute(params->dimLeft, hasValue, value);
    props->dimLeft = ArkUIOptionalFloat { hasValue, value };
    ParseIndicatorAttribute(params->dimTop, hasValue, value);
    props->dimTop = ArkUIOptionalFloat { hasValue, value };
    ParseIndicatorAttribute(params->dimRight, hasValue, value);
    props->dimRight = ArkUIOptionalFloat { hasValue, value };
    ParseIndicatorAttribute(params->dimBottom, hasValue, value);
    props->dimBottom = ArkUIOptionalFloat { hasValue, value };
    props->ignoreSizeValue = ArkUIOptionalInt { 1, params->ignoreSizeValue.value_or(0) };
    if (props->type == ArkUISwiperIndicatorType::DIGIT) {
        props->fontColor = ArkUIOptionalUint { 1, params->fontColor.value().GetValue() };
        props->selectedFontColor = ArkUIOptionalUint { 1, params->selectedFontColor.value().GetValue() };
        ParseIndicatorAttribute(params->fontSize, hasValue, value);
        props->fontSize = ArkUIOptionalFloat { hasValue, value };
        ParseIndicatorAttribute(params->selectedFontSize, hasValue, value);
        props->selectedFontSize = ArkUIOptionalFloat { hasValue, value };
        props->fontWeight = ArkUIOptionalUint { 1, static_cast<ArkUI_Uint32>(params->fontWeight.value()) };
        props->selectedFontWeight =
            ArkUIOptionalUint { 1, static_cast<ArkUI_Uint32>(params->selectedFontWeight.value()) };
    }
}

ArkUINodeHandle GetSwiperController(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, nullptr);
    auto controller = SwiperModelNG::GetSwiperController(frameNode);
    CHECK_NULL_RETURN(controller, nullptr);
    auto nodecontroller = reinterpret_cast<ArkUINodeHandle>(OHOS::Ace::AceType::RawPtr(controller));
    return nodecontroller;
}

void SetSwiperOnChange(ArkUINodeHandle node, void* callback)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (callback) {
        auto onEvent = reinterpret_cast<std::function<void(const BaseEventInfo*)>*>(callback);
        SwiperModelNG::SetOnChange(frameNode, std::move(*onEvent));
    } else {
        SwiperModelNG::SetOnChange(frameNode, nullptr);
    }
}

void ResetSwiperOnChange(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SwiperModelNG::SetOnChange(frameNode, nullptr);
}

void SetSwiperOnSelected(ArkUINodeHandle node, void* callback)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (callback) {
        auto onEvent = reinterpret_cast<std::function<void(const BaseEventInfo*)>*>(callback);
        SwiperModelNG::SetOnSelected(frameNode, std::move(*onEvent));
    } else {
        SwiperModelNG::SetOnSelected(frameNode, nullptr);
    }
}

void ResetSwiperOnSelected(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SwiperModelNG::SetOnSelected(frameNode, nullptr);
}

void SetSwiperOnUnselected(ArkUINodeHandle node, void* callback)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (callback) {
        auto onEvent = reinterpret_cast<std::function<void(const BaseEventInfo*)>*>(callback);
        SwiperModelNG::SetOnUnselected(frameNode, std::move(*onEvent));
    } else {
        SwiperModelNG::SetOnUnselected(frameNode, nullptr);
    }
}

void ResetSwiperOnUnselected(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SwiperModelNG::SetOnUnselected(frameNode, nullptr);
}

void SetSwiperOnAnimationStart(ArkUINodeHandle node, void* callback)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (callback) {
        auto onEvent = reinterpret_cast<std::function<void(int32_t, int32_t, const AnimationCallbackInfo&)>*>(callback);
        SwiperModelNG::SetOnAnimationStart(frameNode, std::move(*onEvent));
    } else {
        SwiperModelNG::SetOnAnimationStart(frameNode, nullptr);
    }
}

void ResetSwiperOnAnimationStart(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SwiperModelNG::SetOnAnimationStart(frameNode, nullptr);
}

void SetSwiperOnAnimationEnd(ArkUINodeHandle node, void* callback)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (callback) {
        auto onEvent = reinterpret_cast<std::function<void(int32_t, const AnimationCallbackInfo&)>*>(callback);
        SwiperModelNG::SetOnAnimationEnd(frameNode, std::move(*onEvent));
    } else {
        SwiperModelNG::SetOnAnimationEnd(frameNode, nullptr);
    }
}

void ResetSwiperOnAnimationEnd(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SwiperModelNG::SetOnAnimationEnd(frameNode, nullptr);
}

void SetSwiperOnGestureSwipe(ArkUINodeHandle node, void* callback)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (callback) {
        auto onEvent = reinterpret_cast<std::function<void(int32_t, const AnimationCallbackInfo&)>*>(callback);
        SwiperModelNG::SetOnGestureSwipe(frameNode, std::move(*onEvent));
    } else {
        SwiperModelNG::SetOnGestureSwipe(frameNode, nullptr);
    }
}

void ResetSwiperOnGestureSwipe(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SwiperModelNG::SetOnGestureSwipe(frameNode, nullptr);
}

void SetOnContentDidScroll(ArkUINodeHandle node, void* callback)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (callback) {
        auto onEvent = reinterpret_cast<std::function<void(int32_t, int32_t, float, float)>*>(callback);
        SwiperModelNG::SetOnContentDidScroll(frameNode, std::move(*onEvent));
    } else {
        SwiperModelNG::SetOnContentDidScroll(frameNode, nullptr);
    }
}

void ResetOnContentDidScroll(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SwiperModelNG::SetOnContentDidScroll(frameNode, nullptr);
}

void SetSwiperPageFlipMode(ArkUINodeHandle node, ArkUI_Int32 pageFlipMode)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SwiperModelNG::SetPageFlipMode(frameNode, pageFlipMode);
}

void ResetSwiperPageFlipMode(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SwiperModelNG::SetPageFlipMode(frameNode, NUM_0);
}

ArkUI_Int32 GetSwiperSwiperPageFlipMode(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_CODE_PARAM_INVALID);
    return SwiperModelNG::GetPageFlipMode(frameNode);
}

void SetSwiperOnContentWillScroll(ArkUINodeHandle node, bool* callback)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (callback) {
        auto onEvent = reinterpret_cast<std::function<bool(const SwiperContentWillScrollResult&)>*>(callback);
        SwiperModelNG::SetOnContentWillScroll(frameNode, std::move(*onEvent));
    } else {
        SwiperModelNG::SetOnContentWillScroll(frameNode, nullptr);
    }
}

void ResetSwiperOnContentWillScroll(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SwiperModelNG::SetOnContentWillScroll(frameNode, nullptr);
}

ArkUISwiperIndicatorType GetIndicatorType(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, ArkUISwiperIndicatorType::DOT);
    return static_cast<ArkUISwiperIndicatorType>(SwiperModelNG::GetIndicatorType(frameNode));
}

void SetMaintainVisibleContentPosition(ArkUINodeHandle node, ArkUI_Bool value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SwiperModelNG::SetMaintainVisibleContentPosition(frameNode, value);
}

void ResetMaintainVisibleContentPosition(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SwiperModelNG::SetMaintainVisibleContentPosition(frameNode, false);
}

ArkUI_Int32 GetMaintainVisibleContentPosition(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_CODE_PARAM_INVALID);
    return SwiperModelNG::GetMaintainVisibleContentPosition(frameNode);
}
} // namespace

namespace NodeModifier {
const ArkUISwiperModifier* GetSwiperModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const ArkUISwiperModifier modifier = {
        .setSwiperNextMargin = SetSwiperNextMargin,
        .setSwiperNextMarginRaw = SetSwiperNextMarginRAw,
        .resetSwiperNextMargin = ResetSwiperNextMargin,
        .setSwiperPrevMargin = SetSwiperPrevMargin,
        .setSwiperPrevMarginRaw = SetSwiperPrevMarginRaw,
        .resetSwiperPrevMargin = ResetSwiperPrevMargin,
        .setSwiperDisplayCount = SetSwiperDisplayCount,
        .resetSwiperDisplayCount = ResetSwiperDisplayCount,
        .setSwiperSwipeByGroup = SetSwiperSwipeByGroup,
        .resetSwiperSwipeByGroup = ResetSwiperSwipeByGroup,
        .setSwiperDisplayArrow = SetSwiperDisplayArrow,
        .setSwiperDisplayArrowRaw = SetSwiperDisplayArrowRaw,
        .resetSwiperDisplayArrow = ResetSwiperDisplayArrow,
        .setSwiperCurve = SetSwiperCurve,
        .resetSwiperCurve = ResetSwiperCurve,
        .setSwiperDisableSwipe = SetSwiperDisableSwipe,
        .resetSwiperDisableSwipe = ResetSwiperDisableSwipe,
        .setSwiperEffectMode = SetSwiperEffectMode,
        .resetSwiperEffectMode = ResetSwiperEffectMode,
        .setSwiperCachedCount = SetSwiperCachedCount,
        .resetSwiperCachedCount = ResetSwiperCachedCount,
        .setSwiperIsShown = SetSwiperIsShown,
        .resetSwiperIsShown = ResetSwiperIsShown,
        .setSwiperDisplayMode = SetSwiperDisplayMode,
        .resetSwiperDisplayMode = ResetSwiperDisplayMode,
        .setSwiperItemSpace = SetSwiperItemSpace,
        .resetSwiperItemSpace = ResetSwiperItemSpace,
        .setSwiperVertical = SetSwiperVertical,
        .resetSwiperVertical = ResetSwiperVertical,
        .setSwiperLoop = SetSwiperLoop,
        .resetSwiperLoop = ResetSwiperLoop,
        .setSwiperInterval = SetSwiperInterval,
        .resetSwiperInterval = ResetSwiperInterval,
        .setSwiperAutoPlay = SetSwiperAutoPlay,
        .resetSwiperAutoPlay = ResetSwiperAutoPlay,
        .setSwiperStopWhenTouched = SetSwiperStopWhenTouched,
        .resetSwiperStopWhenTouched = ResetSwiperStopWhenTouched,
        .setSwiperIndex = SetSwiperIndex,
        .resetSwiperIndex = ResetSwiperIndex,
        .setSwiperIndicator = SetSwiperIndicator,
        .setSwiperIndicatorRaw = SetSwiperIndicatorRaw,
        .resetSwiperIndicator = ResetSwiperIndicator,
        .setSwiperDuration = SetSwiperDuration,
        .resetSwiperDuration = ResetSwiperDuration,
        .setSwiperEnabled = SetSwiperEnabled,
        .resetSwiperEnabled = ResetSwiperEnabled,
        .getSwiperLoop = GetSwiperLoop,
        .getSwiperAutoPlay = GetSwiperAutoPlay,
        .getSwiperStopWhenTouched = GetSwiperStopWhenTouched,
        .getSwiperIndex = GetSwiperIndex,
        .getSwiperVertical = GetSwiperVertical,
        .getSwiperDuration = GetSwiperDuration,
        .getSwiperDisplayCount = GetSwiperDisplayCount,
        .getSwiperCachedIsShown = GetSwiperCachedIsShown,
        .getSwiperInterval = GetSwiperInterval,
        .getSwiperCurve = GetSwiperCurve,
        .getSwiperDisableSwipe = GetSwiperDisableSwipe,
        .getSwiperItemSpace = GetSwiperItemSpace,
        .getSwiperShowIndicator = GetSwiperShowIndicator,
        .getSwiperShowDisplayArrow = GetSwiperShowDisplayArrow,
        .getSwiperEffectMode = GetSwiperEffectMode,
        .setIndicatorInteractive = SetIndicatorInteractive,
        .resetIndicatorInteractive = ResetIndicatorInteractive,
        .setNodeAdapter = SetNodeAdapter,
        .resetNodeAdapter = ResetNodeAdapter,
        .getNodeAdapter = GetNodeAdapter,
        .getCachedCount = GetCachedCount,
        .setSwiperNestedScroll = SetSwiperNestedScroll,
        .resetSwiperNestedScroll = ResetSwiperNestedScroll,
        .getSwiperNestedScroll = GetSwiperNestedScroll,
        .setSwiperToIndex = SetSwiperToIndex,
        .getSwiperPrevMargin = GetSwiperPrevMargin,
        .getSwiperNextMargin = GetSwiperNextMargin,
        .setSwiperIndicatorStyle = SetSwiperIndicatorStyle,
        .getSwiperIndicator = GetSwiperIndicator,
        .getSwiperController = GetSwiperController,
        .setSwiperOnChange = SetSwiperOnChange,
        .resetSwiperOnChange = ResetSwiperOnChange,
        .setSwiperOnUnselected = SetSwiperOnUnselected,
        .resetSwiperOnUnselected = ResetSwiperOnUnselected,
        .setSwiperOnAnimationStart = SetSwiperOnAnimationStart,
        .resetSwiperOnAnimationStart = ResetSwiperOnAnimationStart,
        .setSwiperOnAnimationEnd = SetSwiperOnAnimationEnd,
        .resetSwiperOnAnimationEnd = ResetSwiperOnAnimationEnd,
        .setSwiperOnGestureSwipe = SetSwiperOnGestureSwipe,
        .resetSwiperOnGestureSwipe = ResetSwiperOnGestureSwipe,
        .setSwiperOnContentDidScroll = SetOnContentDidScroll,
        .resetSwiperOnContentDidScroll = ResetOnContentDidScroll,
        .getIndicatorInteractive = GetIndicatorInteractive,
        .setSwiperPageFlipMode = SetSwiperPageFlipMode,
        .resetSwiperPageFlipMode = ResetSwiperPageFlipMode,
        .getSwiperPageFlipMode = GetSwiperSwiperPageFlipMode,
        .setSwiperOnContentWillScroll = SetSwiperOnContentWillScroll,
        .resetSwiperOnContentWillScroll = ResetSwiperOnContentWillScroll,
        .setSwiperOnSelected = SetSwiperOnSelected,
        .resetSwiperOnSelected = ResetSwiperOnSelected,
        .setSwiperMinSize = SetSwiperMinSize,
        .resetSwiperMinSize = ResetSwiperMinSize,
        .getSwiperMinSize = GetSwiperMinSize,
        .setSwiperDigitIndicatorStyle = SetSwiperDigitIndicatorStyle,
        .getSwiperDigitIndicator = GetSwiperDigitIndicator,
        .getIndicatorType = GetIndicatorType,
        .getSwiperSwipeByGroup = GetSwiperSwipeByGroup,
        .getSwiperDisplayMode = GetSwiperDisplayMode,
        .getSwiperArrowStyle = GetSwiperArrowStyle,
        .setMaintainVisibleContentPosition = SetMaintainVisibleContentPosition,
        .resetMaintainVisibleContentPosition = ResetMaintainVisibleContentPosition,
        .getMaintainVisibleContentPosition = GetMaintainVisibleContentPosition,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line
    return &modifier;
}

const CJUISwiperModifier* GetCJUISwiperModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const CJUISwiperModifier modifier = {
        .setSwiperNextMargin = SetSwiperNextMargin,
        .resetSwiperNextMargin = ResetSwiperNextMargin,
        .setSwiperPrevMargin = SetSwiperPrevMargin,
        .resetSwiperPrevMargin = ResetSwiperPrevMargin,
        .setSwiperDisplayCount = SetSwiperDisplayCount,
        .resetSwiperDisplayCount = ResetSwiperDisplayCount,
        .setSwiperSwipeByGroup = SetSwiperSwipeByGroup,
        .resetSwiperSwipeByGroup = ResetSwiperSwipeByGroup,
        .setSwiperDisplayArrow = SetSwiperDisplayArrow,
        .resetSwiperDisplayArrow = ResetSwiperDisplayArrow,
        .setSwiperCurve = SetSwiperCurve,
        .resetSwiperCurve = ResetSwiperCurve,
        .setSwiperDisableSwipe = SetSwiperDisableSwipe,
        .resetSwiperDisableSwipe = ResetSwiperDisableSwipe,
        .setSwiperEffectMode = SetSwiperEffectMode,
        .resetSwiperEffectMode = ResetSwiperEffectMode,
        .setSwiperCachedCount = SetSwiperCachedCount,
        .resetSwiperCachedCount = ResetSwiperCachedCount,
        .setSwiperDisplayMode = SetSwiperDisplayMode,
        .resetSwiperDisplayMode = ResetSwiperDisplayMode,
        .setSwiperItemSpace = SetSwiperItemSpace,
        .resetSwiperItemSpace = ResetSwiperItemSpace,
        .setSwiperVertical = SetSwiperVertical,
        .resetSwiperVertical = ResetSwiperVertical,
        .setSwiperLoop = SetSwiperLoop,
        .resetSwiperLoop = ResetSwiperLoop,
        .setSwiperInterval = SetSwiperInterval,
        .resetSwiperInterval = ResetSwiperInterval,
        .setSwiperAutoPlay = SetSwiperAutoPlay,
        .resetSwiperAutoPlay = ResetSwiperAutoPlay,
        .setSwiperStopWhenTouched = SetSwiperStopWhenTouched,
        .resetSwiperStopWhenTouched = ResetSwiperStopWhenTouched,
        .setSwiperIndex = SetSwiperIndex,
        .resetSwiperIndex = ResetSwiperIndex,
        .setSwiperIndicator = SetSwiperIndicator,
        .resetSwiperIndicator = ResetSwiperIndicator,
        .setSwiperDuration = SetSwiperDuration,
        .resetSwiperDuration = ResetSwiperDuration,
        .setSwiperEnabled = SetSwiperEnabled,
        .resetSwiperEnabled = ResetSwiperEnabled,
        .getSwiperLoop = GetSwiperLoop,
        .getSwiperAutoPlay = GetSwiperAutoPlay,
        .getSwiperStopWhenTouched = GetSwiperStopWhenTouched,
        .getSwiperIndex = GetSwiperIndex,
        .getSwiperVertical = GetSwiperVertical,
        .getSwiperDuration = GetSwiperDuration,
        .getSwiperDisplayCount = GetSwiperDisplayCount,
        .getSwiperInterval = GetSwiperInterval,
        .getSwiperCurve = GetSwiperCurve,
        .getSwiperDisableSwipe = GetSwiperDisableSwipe,
        .getSwiperItemSpace = GetSwiperItemSpace,
        .getSwiperShowIndicator = GetSwiperShowIndicator,
        .getSwiperShowDisplayArrow = GetSwiperShowDisplayArrow,
        .getSwiperEffectMode = GetSwiperEffectMode,
        .setIndicatorInteractive = SetIndicatorInteractive,
        .resetIndicatorInteractive = ResetIndicatorInteractive,
        .setNodeAdapter = SetNodeAdapter,
        .resetNodeAdapter = ResetNodeAdapter,
        .getNodeAdapter = GetNodeAdapter,
        .getCachedCount = GetCachedCount,
        .setSwiperNestedScroll = SetSwiperNestedScroll,
        .resetSwiperNestedScroll = ResetSwiperNestedScroll,
        .getSwiperNestedScroll = GetSwiperNestedScroll,
        .setSwiperToIndex = SetSwiperToIndex,
        .getSwiperPrevMargin = GetSwiperPrevMargin,
        .getSwiperNextMargin = GetSwiperNextMargin,
        .setSwiperIndicatorStyle = SetSwiperIndicatorStyle,
        .getSwiperIndicator = GetSwiperIndicator,
        .getSwiperController = GetSwiperController,
        .setSwiperOnChange = SetSwiperOnChange,
        .resetSwiperOnChange = ResetSwiperOnChange,
        .setSwiperOnAnimationStart = SetSwiperOnAnimationStart,
        .resetSwiperOnAnimationStart = ResetSwiperOnAnimationStart,
        .setSwiperOnAnimationEnd = SetSwiperOnAnimationEnd,
        .resetSwiperOnAnimationEnd = ResetSwiperOnAnimationEnd,
        .setSwiperOnGestureSwipe = SetSwiperOnGestureSwipe,
        .resetSwiperOnGestureSwipe = ResetSwiperOnGestureSwipe,
        .setSwiperOnSelected = SetSwiperOnSelected,
        .resetSwiperOnSelected = ResetSwiperOnSelected,
        .setSwiperMinSize = SetSwiperMinSize,
        .resetSwiperMinSize = ResetSwiperMinSize,
        .getSwiperMinSize = GetSwiperMinSize,
        .setSwiperDigitIndicatorStyle = SetSwiperDigitIndicatorStyle,
        .getSwiperDigitIndicator = GetSwiperDigitIndicator,
        .getIndicatorType = GetIndicatorType,
        .getSwiperSwipeByGroup = GetSwiperSwipeByGroup,
        .getSwiperDisplayMode = GetSwiperDisplayMode,
        .getSwiperArrowStyle = GetSwiperArrowStyle,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line
    return &modifier;
}

void SetSwiperChange(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto onEvent = [node, extraParam](const BaseEventInfo* info) {
        const auto* swiperInfo = TypeInfoHelper::DynamicCast<SwiperChangeEvent>(info);
        if (!swiperInfo) {
            LOGE("Swiper onChange callback execute failed.");
            return;
        }
        int32_t index = swiperInfo->GetIndex();
        ArkUINodeEvent event;
        event.kind = COMPONENT_ASYNC_EVENT;
        event.extraParam = reinterpret_cast<intptr_t>(extraParam);
        event.componentAsyncEvent.subKind = ON_SWIPER_CHANGE;
        event.componentAsyncEvent.data[NUM_0].i32 = index;
        SendArkUISyncEvent(&event);
    };
    SwiperModelNG::SetOnChange(frameNode, std::move(onEvent));
}

void SetSwiperSelected(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto onEvent = [node, extraParam](const BaseEventInfo* info) {
        const auto* swiperInfo = TypeInfoHelper::DynamicCast<SwiperChangeEvent>(info);
        if (!swiperInfo) {
            LOGE("Swiper onSelected callback execute failed.");
            return;
        }
        int32_t index = swiperInfo->GetIndex();
        ArkUINodeEvent event;
        event.kind = COMPONENT_ASYNC_EVENT;
        event.extraParam = reinterpret_cast<intptr_t>(extraParam);
        event.componentAsyncEvent.subKind = ON_SWIPER_SELECTED;
        event.componentAsyncEvent.data[NUM_0].i32 = index;
        SendArkUISyncEvent(&event);
    };
    SwiperModelNG::SetOnSelected(frameNode, std::move(onEvent));
}

void SetSwiperAnimationStart(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto onEvent = [node, extraParam](int32_t index, int32_t targetIndex, const AnimationCallbackInfo& info) {
        ArkUINodeEvent event;
        event.kind = COMPONENT_ASYNC_EVENT;
        event.extraParam = reinterpret_cast<intptr_t>(extraParam);
        event.componentAsyncEvent.subKind = ON_SWIPER_ANIMATION_START;
        event.componentAsyncEvent.data[NUM_0].i32 = index;
        event.componentAsyncEvent.data[NUM_1].i32 = targetIndex;
        event.componentAsyncEvent.data[NUM_2].f32 = info.currentOffset.value_or(ANIMATION_INFO_DEFAULT);
        event.componentAsyncEvent.data[NUM_3].f32 = info.targetOffset.value_or(ANIMATION_INFO_DEFAULT);
        event.componentAsyncEvent.data[NUM_4].f32 = info.velocity.value_or(ANIMATION_INFO_DEFAULT);
        SendArkUISyncEvent(&event);
    };
    SwiperModelNG::SetOnAnimationStart(frameNode, std::move(onEvent));
}

void SetSwiperAnimationEnd(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto onEvent = [node, extraParam](int32_t index, const AnimationCallbackInfo& info) {
        ArkUINodeEvent event;
        event.kind = COMPONENT_ASYNC_EVENT;
        event.extraParam = reinterpret_cast<intptr_t>(extraParam);
        event.componentAsyncEvent.subKind = ON_SWIPER_ANIMATION_END;
        event.componentAsyncEvent.data[NUM_0].i32 = index;
        event.componentAsyncEvent.data[NUM_1].f32 = info.currentOffset.value_or(ANIMATION_INFO_DEFAULT);
        SendArkUISyncEvent(&event);
    };
    SwiperModelNG::SetOnAnimationEnd(frameNode, std::move(onEvent));
}

void SetSwiperGestureSwipe(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto onEvent = [node, extraParam](int32_t index, const AnimationCallbackInfo& info) {
        ArkUINodeEvent event;
        event.kind = COMPONENT_ASYNC_EVENT;
        event.extraParam = reinterpret_cast<intptr_t>(extraParam);
        event.componentAsyncEvent.subKind = ON_SWIPER_GESTURE_SWIPE;
        event.componentAsyncEvent.data[NUM_0].i32 = index;
        event.componentAsyncEvent.data[NUM_1].f32 = info.currentOffset.value_or(ANIMATION_INFO_DEFAULT);
        SendArkUISyncEvent(&event);
    };
    SwiperModelNG::SetOnGestureSwipe(frameNode, std::move(onEvent));
}

void SetSwiperOnContentDidScroll(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto onEvent = [node, extraParam](int32_t selectedIndex, int32_t index, float position, float mainAxisLength) {
        ArkUINodeEvent event;
        event.kind = COMPONENT_ASYNC_EVENT;
        event.extraParam = reinterpret_cast<intptr_t>(extraParam);
        bool usePx = NodeModel::UsePXUnit(reinterpret_cast<ArkUI_Node*>(extraParam));
        double density = usePx ? 1 : PipelineBase::GetCurrentDensity();
        event.componentAsyncEvent.subKind = ON_SWIPER_DID_CONTENT_SCROLL;
        event.componentAsyncEvent.data[NUM_0].i32 = selectedIndex;
        event.componentAsyncEvent.data[NUM_1].i32 = index;
        event.componentAsyncEvent.data[NUM_2].f32 = position;
        event.componentAsyncEvent.data[NUM_3].f32 = mainAxisLength / density;
        SendArkUISyncEvent(&event);
    };
    SwiperModelNG::SetOnContentDidScroll(frameNode, std::move(onEvent));
}

void SetSwiperUnselected(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto onEvent = [node, extraParam](const BaseEventInfo* info) {
        const auto* swiperInfo = TypeInfoHelper::DynamicCast<SwiperChangeEvent>(info);
        if (!swiperInfo) {
            LOGE("Swiper onUnselected callback execute failed.");
            return;
        }
        int32_t index = swiperInfo->GetIndex();
        ArkUINodeEvent event;
        event.kind = COMPONENT_ASYNC_EVENT;
        event.extraParam = reinterpret_cast<intptr_t>(extraParam);
        event.componentAsyncEvent.subKind = ON_SWIPER_UNSELECTED;
        event.componentAsyncEvent.data[NUM_0].i32 = index;
        SendArkUISyncEvent(&event);
    };
    SwiperModelNG::SetOnUnselected(frameNode, std::move(onEvent));
}

void SetSwiperContentWillScroll(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto onEvent = [node, extraParam](const SwiperContentWillScrollResult& result) -> bool {
        ArkUINodeEvent event;
        event.kind = COMPONENT_ASYNC_EVENT;
        event.extraParam = reinterpret_cast<intptr_t>(extraParam);
        event.componentAsyncEvent.subKind = ON_SWIPER_CONTENT_WILL_SCROLL;
        event.componentAsyncEvent.data[NUM_0].i32 = result.currentIndex;
        event.componentAsyncEvent.data[NUM_1].i32 = result.comingIndex;
        event.componentAsyncEvent.data[NUM_2].f32 = result.offset;
        SendArkUISyncEvent(&event);
        auto ret = event.componentAsyncEvent.data[0].i32;
        if (ret == 0) {
            return false;
        }
        return true;
    };
    SwiperModelNG::SetOnContentWillScroll(frameNode, std::move(onEvent));
}
} // namespace NodeModifier
} // namespace OHOS::Ace::NG
