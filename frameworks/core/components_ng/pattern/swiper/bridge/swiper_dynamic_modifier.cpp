/*
 * Copyright (c) 2023-2026 Huawei Device Co., Ltd.
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
#include "core/common/container.h"
#include "core/common/dynamic_module_helper.h"
#include "core/common/resource/resource_parse_utils.h"
#include "core/components_ng/pattern/swiper/swiper_model.h"
#include "core/components_ng/pattern/swiper/swiper_model_ng.h"
#include "core/components_ng/pattern/swiper_indicator/indicator_common/indicator_controller.h"
#include "core/interfaces/native/node/node_adapter_impl.h"
#include "core/components_ng/pattern/swiper/swiper_change_event.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "core/components_ng/pattern/swiper/swiper_pattern.h"

namespace OHOS::Ace::NG {
namespace {
typedef void (*ComponentAsyncEventHandler)(ArkUINodeHandle node, void* extraParam);
constexpr int32_t DEFAULT_INTERVAL = 3000;
constexpr int32_t DEFAULT_DURATION = 400;
constexpr int32_t DEFAULT_CACHED_COUNT = 1;
constexpr int32_t DEFAULT_DISPLAY_COUNT = 1;
constexpr bool DEFAULT_SWIPE_BY_GROUP = false;
constexpr bool DEFAULT_CACHED_IS_SHOWN = false;
constexpr bool DEFAULT_CACHED_INDEPENDENT = false;
constexpr bool DEFAULT_AUTO_PLAY = false;
constexpr bool DEFAULT_LOOP = true;
constexpr bool DEAFULT_DISABLE_SWIPE = false;
constexpr int32_t ARROW_IS_SHOW_BACKGROUND = 1;
constexpr int32_t ARROW_IS_SIDE_BAR_MIDDLE = 2;
constexpr int32_t ARROW_BACKGROUND_SIZE = 3;
constexpr int32_t ARROW_BACKGROUND_COLOR = 4;
constexpr int32_t ARROW_SIZE = 5;
constexpr int32_t ARROW_COLOR = 6;
constexpr int32_t ARROW_ISSET_COLOR = 10;
constexpr int32_t ARROW_ISSET_BACKGROUND_COLOR = 11;
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
constexpr int32_t JS_VIEW_DIGIT_INDICATOR_START = 13;
constexpr int32_t JS_VIEW_DIGIT_INDICATOR_END = 14;
constexpr int32_t JS_VIEW_DIGIT_INDICATOR_HAS_FONT = 15;
constexpr int32_t JS_VIEW_DIGIT_INDICATOR_HAS_SELECTED_FONT = 16;
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
constexpr int32_t JS_VIEW_DOT_INDICATOR_START = 16;
constexpr int32_t JS_VIEW_DOT_INDICATOR_END = 17;
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
using SwiperIndicatorIconMap = std::map<int32_t, OHOS::Ace::IndicatorIconParam>;

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

std::string GetInfoFromVectorByIndex(const std::vector<std::string>& values, int32_t index)
{
    if (index < 0 || index >= static_cast<int32_t>(values.size())) {
        return "";
    }
    return values[index] == "-" ? "" : values[index];
}

RefPtr<ResourceObject> GetResourceObjByIndex(const void* resObjs, int32_t index)
{
    if (!resObjs || index < 0) {
        return nullptr;
    }
    const auto& resourceObjs = *(static_cast<const std::vector<RefPtr<ResourceObject>>*>(resObjs));
    if (index >= static_cast<int32_t>(resourceObjs.size())) {
        return nullptr;
    }
    return resourceObjs[index];
}

void SetArrowBackgroundInfo(SwiperArrowParameters& swiperArrowParameters,
    RefPtr<SwiperIndicatorTheme>& swiperIndicatorTheme, const std::vector<std::string>& arrowInfo)
{
    auto backgroundSizeValue = GetInfoFromVectorByIndex(arrowInfo, ARROW_BACKGROUND_SIZE);
    auto backgroundColorValue = GetInfoFromVectorByIndex(arrowInfo, ARROW_BACKGROUND_COLOR);
    auto arrowSizeValue = GetInfoFromVectorByIndex(arrowInfo, ARROW_SIZE);
    auto arrowColorValue = GetInfoFromVectorByIndex(arrowInfo, ARROW_COLOR);
    bool parseOk = false;
    CalcDimension dimension;
    Color color;
    auto arrowBackgroundSize = swiperArrowParameters.isSidebarMiddle.value()
        ? swiperIndicatorTheme->GetBigArrowBackgroundSize() : swiperIndicatorTheme->GetSmallArrowBackgroundSize();
    auto arrowBackgroundColor = swiperArrowParameters.isSidebarMiddle.value()
        ? swiperIndicatorTheme->GetBigArrowBackgroundColor() : swiperIndicatorTheme->GetSmallArrowBackgroundColor();
    auto arrowSize = swiperArrowParameters.isSidebarMiddle.value()
        ? swiperIndicatorTheme->GetBigArrowSize() : swiperIndicatorTheme->GetSmallArrowSize();
    auto arrowColor = swiperArrowParameters.isSidebarMiddle.value()
        ? swiperIndicatorTheme->GetBigArrowColor() : swiperIndicatorTheme->GetSmallArrowColor();
    dimension = StringUtils::StringToCalcDimension(backgroundSizeValue, false, DimensionUnit::VP);
    swiperArrowParameters.backgroundSize =
        GreatNotEqual(dimension.ConvertToVp(), 0.0) && !(dimension.Unit() == DimensionUnit::PERCENT)
            ? dimension : arrowBackgroundSize;
    parseOk = Color::ParseColorString(backgroundColorValue, color) &&
        GetInfoFromVectorByIndex(arrowInfo, ARROW_ISSET_BACKGROUND_COLOR) == "1";
    color = backgroundColorValue != "" ? Color(StringUtils::StringToLongInt(backgroundColorValue)) : color;
    swiperArrowParameters.backgroundColor = parseOk || color == Color(0x00000000)
        ? (swiperArrowParameters.parametersByUser.insert("backgroundColor"), color) : arrowBackgroundColor;
    if (swiperArrowParameters.isShowBackground.value()) {
        swiperArrowParameters.arrowSize = swiperArrowParameters.backgroundSize.value() * ARROW_SIZE_COEFFICIENT;
    } else {
        parseOk = StringUtils::StringToCalcDimensionNG(arrowSizeValue, dimension, false, DimensionUnit::VP);
        swiperArrowParameters.arrowSize =
            parseOk && GreatNotEqual(dimension.ConvertToVp(), 0.0) && !(dimension.Unit() == DimensionUnit::PERCENT)
                ? dimension : arrowSize;
        swiperArrowParameters.backgroundSize = swiperArrowParameters.arrowSize;
    }
    parseOk = Color::ParseColorString(arrowColorValue, color) &&
        GetInfoFromVectorByIndex(arrowInfo, ARROW_ISSET_COLOR) == "1";
    color = arrowColorValue != "" ? Color(StringUtils::StringToLongInt(arrowColorValue)) : color;
    swiperArrowParameters.arrowColor = parseOk || color == Color(0x00000000)
        ? (swiperArrowParameters.parametersByUser.insert("arrowColor"), color) : arrowColor;
}

bool GetArrowInfo(const std::vector<std::string>& arrowInfo, SwiperArrowParameters& swiperArrowParameters,
    const void* resObjs)
{
    auto isShowBackgroundValue = GetInfoFromVectorByIndex(arrowInfo, ARROW_IS_SHOW_BACKGROUND);
    auto isSidebarMiddleValue = GetInfoFromVectorByIndex(arrowInfo, ARROW_IS_SIDE_BAR_MIDDLE);

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
        swiperArrowParameters.resourceBackgroundSizeValueObject =
            GetResourceObjByIndex(resObjs, ARROW_RESOURCE_BACKGROUND_SIZE);
        swiperArrowParameters.resourceBackgroundColorValueObject =
            GetResourceObjByIndex(resObjs, ARROW_RESOURCE_BACKGROUND_COLOR);
        swiperArrowParameters.resourceArrowSizeValueObject = GetResourceObjByIndex(resObjs, ARROW_RESOURCE_SIZE);
        swiperArrowParameters.resourceArrowColorValueObject = GetResourceObjByIndex(resObjs, ARROW_RESOURCE_COLOR);
    }
    return true;
}

void GetSwiperArrowResObj(FrameNode* frameNode, SwiperArrowParameters& swiperArrowParameters,
    const std::vector<std::string>& arrowInfo)
{
    // If the dark and light switch is not turned on,
    // do not need to acquire the resource object.
    if (!SystemProperties::ConfigChangePerform()) {
        return;
    }
    CHECK_NULL_VOID(frameNode);
    auto pipelineContext = frameNode->GetContext();
    CHECK_NULL_VOID(pipelineContext);
    auto swiperIndicatorTheme = pipelineContext->GetTheme<SwiperIndicatorTheme>();
    CHECK_NULL_VOID(swiperIndicatorTheme);

    // Use "backgroundColor" to obtain the corresponding resource object.
    Color backgroundColor =
        swiperArrowParameters.backgroundColor.value_or(
            swiperArrowParameters.isSidebarMiddle.value()
            ? swiperIndicatorTheme->GetBigArrowBackgroundColor()
            : swiperIndicatorTheme->GetSmallArrowBackgroundColor());
    RefPtr<ResourceObject> bgColorResObj;
    if (GetInfoFromVectorByIndex(arrowInfo, ARROW_ISSET_BACKGROUND_COLOR) == "1") {
        ResourceParseUtils::CompleteResourceObjectFromColor(
            bgColorResObj, backgroundColor, ResourceParseUtils::MakeNativeNodeInfo(frameNode));
    }
    swiperArrowParameters.backgroundColor = backgroundColor;
    swiperArrowParameters.resourceBackgroundColorValueObject = bgColorResObj;

    // Use "arrowColor" to obtain the corresponding resource object.
    Color arrowColor =
        swiperArrowParameters.arrowColor.value_or(
            swiperArrowParameters.isSidebarMiddle.value()
            ? swiperIndicatorTheme->GetBigArrowColor()
            : swiperIndicatorTheme->GetSmallArrowColor());
    RefPtr<ResourceObject> arrowColorResObj;
    if (GetInfoFromVectorByIndex(arrowInfo, ARROW_ISSET_COLOR) == "1") {
        ResourceParseUtils::CompleteResourceObjectFromColor(
            arrowColorResObj, arrowColor, ResourceParseUtils::MakeNativeNodeInfo(frameNode));
    }
    swiperArrowParameters.arrowColor = arrowColor;
    swiperArrowParameters.resourceArrowColorValueObject = arrowColorResObj;
}

std::string GetInfoFromVectorByIndexForDot(const std::vector<std::string>& dotIndicatorInfo, int32_t index)
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
    auto maxDisplayCount = GetInfoFromVectorByIndexForDot(dotIndicatorInfo, DOT_INDICATOR_MAX_DISPLAY_COUNT);
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
    auto itemWidthValue = GetInfoFromVectorByIndexForDot(dotIndicatorInfo, DOT_INDICATOR_ITEM_WIDTH);
    auto itemHeightValue = GetInfoFromVectorByIndexForDot(dotIndicatorInfo, DOT_INDICATOR_ITEM_HEIGHT);
    auto selectedItemWidthValue = GetInfoFromVectorByIndexForDot(dotIndicatorInfo, DOT_INDICATOR_SELECTED_ITEM_WIDTH);
    auto selectedItemHeightValue = GetInfoFromVectorByIndexForDot(dotIndicatorInfo, DOT_INDICATOR_SELECTED_ITEM_HEIGHT);
    CalcDimension dimPosition = StringUtils::StringToCalcDimension(itemWidthValue, false, DimensionUnit::VP);
    auto defaultSize = swiperIndicatorTheme->GetSize();
    bool parseItemWOk = !itemWidthValue.empty() && dimPosition.Unit() != DimensionUnit::PERCENT;
    if (parseItemWOk && (dimPosition > 0.0_vp)) {
        swiperParameters.parametersByUser.insert("itemWidth");
        swiperParameters.itemWidth = dimPosition;
    } else {
        swiperParameters.itemWidth = defaultSize;
    }
    dimPosition = StringUtils::StringToCalcDimension(itemHeightValue, false, DimensionUnit::VP);
    bool parseItemHOk = !itemHeightValue.empty() && dimPosition.Unit() != DimensionUnit::PERCENT;
    if (parseItemHOk && (dimPosition > 0.0_vp)) {
        swiperParameters.parametersByUser.insert("itemHeight");
        swiperParameters.itemHeight = dimPosition;
    } else {
        swiperParameters.itemHeight = defaultSize;
    }
    dimPosition = StringUtils::StringToCalcDimension(selectedItemWidthValue, false, DimensionUnit::VP);
    bool parseSeleItemWOk = !selectedItemWidthValue.empty() && dimPosition.Unit() != DimensionUnit::PERCENT;
    if (parseSeleItemWOk && (dimPosition > 0.0_vp)) {
        swiperParameters.parametersByUser.insert("selectedItemWidth");
        swiperParameters.selectedItemWidth = dimPosition;
    } else {
        swiperParameters.selectedItemWidth = defaultSize;
    }
    dimPosition = StringUtils::StringToCalcDimension(selectedItemHeightValue, false, DimensionUnit::VP);
    bool parseSeleItemHOk = !selectedItemHeightValue.empty() && dimPosition.Unit() != DimensionUnit::PERCENT;
    if (parseSeleItemHOk && (dimPosition > 0.0_vp)) {
        swiperParameters.parametersByUser.insert("selectedItemHeight");
        swiperParameters.selectedItemHeight = dimPosition;
    } else {
        swiperParameters.selectedItemHeight = defaultSize;
    }
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
    auto spaceValue = GetInfoFromVectorByIndexForDot(dotIndicatorInfo, DOT_INDICATOR_SPACE);
    auto ignoreSize = GetInfoFromVectorByIndexForDot(dotIndicatorInfo, DOT_INDICATOR_IGNORE_SIZE);
    auto setIgnoreSize = GetInfoFromVectorByIndexForDot(dotIndicatorInfo, DOT_INDICATOR_SET_IGNORE_SIZE);

    CalcDimension dimPosition = StringUtils::StringToCalcDimension(spaceValue, false, DimensionUnit::VP);
    bool parseSpaceOk = !spaceValue.empty() && dimPosition.Unit() != DimensionUnit::PERCENT;
    auto defaultSpaceSize = swiperIndicatorTheme->GetIndicatorDotItemSpace();
    swiperParameters.dimSpace = (parseSpaceOk && !(dimPosition < 0.0_vp)) ? dimPosition : defaultSpaceSize;

    swiperParameters.ignoreSizeValue = (ignoreSize == "1" ? true : false);
    swiperParameters.setIgnoreSizeValue = (setIgnoreSize == "1" ? true : false);
}

void InitIndicatorParametersWithResObj(SwiperParameters& swiperParameters, const void* resObjs)
{
    CHECK_NULL_VOID(SystemProperties::ConfigChangePerform());
    CHECK_NULL_VOID(resObjs);
    swiperParameters.resourceDimLeftValueObject = GetResourceObjByIndex(resObjs, INDICATOR_RESOURCE_LEFT);
    swiperParameters.resourceDimTopValueObject = GetResourceObjByIndex(resObjs, INDICATOR_RESOURCE_TOP);
    swiperParameters.resourceDimRightValueObject = GetResourceObjByIndex(resObjs, INDICATOR_RESOURCE_RIGHT);
    swiperParameters.resourceDimBottomValueObject = GetResourceObjByIndex(resObjs, INDICATOR_RESOURCE_BOTTOM);
    swiperParameters.resourceItemWidthValueObject = GetResourceObjByIndex(resObjs, DOT_INDICATOR_RESOURCE_ITEM_WIDTH);
    swiperParameters.resourceItemHeightValueObject = GetResourceObjByIndex(resObjs, DOT_INDICATOR_RESOURCE_ITEM_HEIGHT);
    swiperParameters.resourceSelectedItemWidthValueObject =
        GetResourceObjByIndex(resObjs, DOT_INDICATOR_RESOURCE_SELECTED_ITEM_WIDTH);
    swiperParameters.resourceSelectedItemHeightValueObject =
        GetResourceObjByIndex(resObjs, DOT_INDICATOR_RESOURCE_SELECTED_ITEM_HEIGHT);
    swiperParameters.resourceColorValueObject = GetResourceObjByIndex(resObjs, DOT_INDICATOR_RESOURCE_COLOR);
    swiperParameters.resourceSelectedColorValueObject =
        GetResourceObjByIndex(resObjs, DOT_INDICATOR_RESOURCE_SELECTED_COLOR);
}

SwiperParameters GetDotIndicatorInfo(FrameNode* frameNode, const std::vector<std::string>& dotIndicatorInfo,
    const void* resObjs)
{
    auto maskValue = GetInfoFromVectorByIndexForDot(dotIndicatorInfo, DOT_INDICATOR_MASK);
    auto colorValue = GetInfoFromVectorByIndexForDot(dotIndicatorInfo, DOT_INDICATOR_COLOR);
    auto selectedColorValue = GetInfoFromVectorByIndexForDot(dotIndicatorInfo, DOT_INDICATOR_SELECTED_COLOR);
    CHECK_NULL_RETURN(frameNode, SwiperParameters());
    auto pipelineContext = frameNode->GetContext();
    CHECK_NULL_RETURN(pipelineContext, SwiperParameters());
    auto swiperIndicatorTheme = pipelineContext->GetTheme<SwiperIndicatorTheme>();
    CHECK_NULL_RETURN(swiperIndicatorTheme, SwiperParameters());
    bool parseOk = false;
    SwiperParameters swiperParameters;
    auto leftValue = GetInfoFromVectorByIndexForDot(dotIndicatorInfo, DOT_INDICATOR_LEFT);
    auto topValue = GetInfoFromVectorByIndexForDot(dotIndicatorInfo, DOT_INDICATOR_TOP);
    auto rightValue = GetInfoFromVectorByIndexForDot(dotIndicatorInfo, DOT_INDICATOR_RIGHT);
    auto bottomValue = GetInfoFromVectorByIndexForDot(dotIndicatorInfo, DOT_INDICATOR_BOTTOM);
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
    InitIndicatorParametersWithResObj(swiperParameters, resObjs);
    return swiperParameters;
}

SwiperParameters GetJsViewDotIndicatorInfo(FrameNode* frameNode, const std::vector<std::string>& dotIndicatorInfo,
    const void* resObjs)
{
    auto swiperParameters = GetDotIndicatorInfo(frameNode, dotIndicatorInfo, resObjs);
    auto startValue = GetInfoFromVectorByIndexForDot(dotIndicatorInfo, JS_VIEW_DOT_INDICATOR_START);
    auto endValue = GetInfoFromVectorByIndexForDot(dotIndicatorInfo, JS_VIEW_DOT_INDICATOR_END);
    swiperParameters.dimStart = ParseIndicatorDimension(startValue);
    swiperParameters.dimEnd = ParseIndicatorDimension(endValue);
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
    swiperParameters.colorVal = indicator->colorValue.isSet == 1
        ? (swiperParameters.parametersByUser.insert("colorVal"), Color(indicator->colorValue.value))
        : swiperIndicatorTheme->GetColor();
    swiperParameters.selectedColorVal = indicator->selectedColorValue.isSet == 1
        ? (swiperParameters.parametersByUser.insert("selectedColorVal"), Color(indicator->selectedColorValue.value))
        : swiperIndicatorTheme->GetSelectedColor();
    swiperParameters.maxDisplayCountVal = indicator->maxDisplayCount.isSet == 1 ?
        indicator->maxDisplayCount.value : NUM_0;
    swiperParameters.ignoreSizeValue = indicator->ignoreSizeValue.value == 1 ? true : false;
    return swiperParameters;
}

void GetSwiperIndicatorResObj(FrameNode* frameNode, SwiperParameters& swiperParameters,
    ArkUISwiperIndicator* indicator)
{
    // If the dark and light switch is not turned on,
    // do not need to acquire the resource object.
    if (!SystemProperties::ConfigChangePerform()) {
        return;
    }
    CHECK_NULL_VOID(frameNode);
    auto pipelineContext = frameNode->GetContext();
    CHECK_NULL_VOID(pipelineContext);
    auto swiperIndicatorTheme = pipelineContext->GetTheme<SwiperIndicatorTheme>();
    CHECK_NULL_VOID(swiperIndicatorTheme);

    // Use "colorVal" to obtain the corresponding resource object.
    Color colorVal =
        swiperParameters.colorVal.value_or(swiperIndicatorTheme->GetColor());
    RefPtr<ResourceObject> colorValResObj;
    if (indicator->colorValue.isSet) {
        ResourceParseUtils::CompleteResourceObjectFromColor(
            colorValResObj, colorVal, ResourceParseUtils::MakeNativeNodeInfo(frameNode));
    }
    swiperParameters.colorVal = colorVal;
    swiperParameters.resourceColorValueObject = colorValResObj;

    // Use "selectedColorVal" to obtain the corresponding resource object.
    Color selectedColorVal =
        swiperParameters.selectedColorVal.value_or(swiperIndicatorTheme->GetSelectedColor());
    RefPtr<ResourceObject> selectedColorResObj;
    if (indicator->selectedColorValue.isSet) {
        ResourceParseUtils::CompleteResourceObjectFromColor(
            selectedColorResObj, selectedColorVal, ResourceParseUtils::MakeNativeNodeInfo(frameNode));
    }
    swiperParameters.selectedColorVal = selectedColorVal;
    swiperParameters.resourceSelectedColorValueObject = selectedColorResObj;
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
        ? (swiperDigitalParameters.parametersByUser.insert("fontColor"), Color(indicator->fontColor.value))
        : swiperIndicatorTheme->GetDigitalIndicatorTextStyle().GetTextColor();
    swiperDigitalParameters.selectedFontColor = indicator->selectedFontColor.isSet == 1
        ? (swiperDigitalParameters.parametersByUser.insert("selectedFontColor"),
            Color(indicator->selectedFontColor.value))
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

void GetSwiperDigitIndicatorResObj(FrameNode* frameNode,
    SwiperDigitalParameters& swiperDigitParameters, ArkUISwiperDigitIndicator* indicator)
{
    // If the dark and light switch is not turned on,
    // do not need to acquire the resource object.
    if (!SystemProperties::ConfigChangePerform()) {
        return;
    }
    CHECK_NULL_VOID(frameNode);
    auto pipelineContext = frameNode->GetContext();
    CHECK_NULL_VOID(pipelineContext);
    auto swiperIndicatorTheme = pipelineContext->GetTheme<SwiperIndicatorTheme>();
    CHECK_NULL_VOID(swiperIndicatorTheme);

    // Use "fontColor" to obtain the corresponding resource object.
    Color fontColor =
        swiperDigitParameters.fontColor.value_or(
            swiperIndicatorTheme->GetDigitalIndicatorTextStyle().GetTextColor());
    RefPtr<ResourceObject> fontColorResObj;
    if (indicator->fontColor.isSet) {
        ResourceParseUtils::CompleteResourceObjectFromColor(
            fontColorResObj, fontColor, ResourceParseUtils::MakeNativeNodeInfo(frameNode));
    }
    swiperDigitParameters.fontColor = fontColor;
    swiperDigitParameters.resourceFontColorValueObject = fontColorResObj;

    // Use "selectedFontColor" to obtain the corresponding resource object.
    Color selectedFontColor =
        swiperDigitParameters.selectedFontColor.value_or(
            swiperIndicatorTheme->GetDigitalIndicatorTextStyle().GetTextColor());
    RefPtr<ResourceObject> selectedFontColorResObj;
    if (indicator->selectedFontColor.isSet) {
        ResourceParseUtils::CompleteResourceObjectFromColor(
            selectedFontColorResObj, selectedFontColor, ResourceParseUtils::MakeNativeNodeInfo(frameNode));
    }
    swiperDigitParameters.selectedFontColor = selectedFontColor;
    swiperDigitParameters.resourceSelectedFontColorValueObject = selectedFontColorResObj;
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
    auto digitBottomValue = GetInfoFromVectorByIndex(digitIndicatorInfo, DIGIT_INDICATOR_BOTTOM);
    auto ignoreSize = GetInfoFromVectorByIndex(digitIndicatorInfo, DIGIT_INDICATOR_IGNORE_SIZE);

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
    auto dotLeftValue = GetInfoFromVectorByIndex(digitIndicatorInfo, DIGIT_INDICATOR_LEFT);
    auto dotTopValue = GetInfoFromVectorByIndex(digitIndicatorInfo, DIGIT_INDICATOR_TOP);
    auto dotRightValue = GetInfoFromVectorByIndex(digitIndicatorInfo, DIGIT_INDICATOR_RIGHT);
    auto fontColorValue = GetInfoFromVectorByIndex(digitIndicatorInfo, DIGIT_INDICATOR_FONT_COLOR);
    auto selectedFontColorValue = GetInfoFromVectorByIndex(digitIndicatorInfo, DIGIT_INDICATOR_SELECTED_FONT_COLOR);
    auto digitFontSize = GetInfoFromVectorByIndex(digitIndicatorInfo, DIGIT_INDICATOR_DIGIT_FONT_SIZE);
    auto digitFontWeight = GetInfoFromVectorByIndex(digitIndicatorInfo, DIGIT_INDICATOR_DIGIT_FONT_WEIGHT);
    auto selectedDigitFontSize = GetInfoFromVectorByIndex(digitIndicatorInfo, DIGIT_INDICATOR_SELECTED_DIGIT_FONT_SIZE);
    auto selectedDigitFontWeight =
        GetInfoFromVectorByIndex(digitIndicatorInfo, DIGIT_INDICATOR_SELECTED_DIGIT_FONT_WEIGHT);

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
        digitalParameters.resourceDimLeftValueObject = GetResourceObjByIndex(resObjs, INDICATOR_RESOURCE_LEFT);
        digitalParameters.resourceDimTopValueObject = GetResourceObjByIndex(resObjs, INDICATOR_RESOURCE_TOP);
        digitalParameters.resourceDimRightValueObject = GetResourceObjByIndex(resObjs, INDICATOR_RESOURCE_RIGHT);
        digitalParameters.resourceDimBottomValueObject = GetResourceObjByIndex(resObjs, INDICATOR_RESOURCE_BOTTOM);
        digitalParameters.resourceFontColorValueObject =
            GetResourceObjByIndex(resObjs, DIGIT_INDICATOR_RESOURCE_FONT_COLOR);
        digitalParameters.resourceSelectedFontColorValueObject =
            GetResourceObjByIndex(resObjs, DIGIT_INDICATOR_RESOURCE_FONT_SELECTED_COLOR);
        digitalParameters.resourceFontSizeValueObject =
            GetResourceObjByIndex(resObjs, DIGIT_INDICATOR_RESOURCE_FONT_SIZE);
        digitalParameters.resourceSelectedFontSizeValueObject =
            GetResourceObjByIndex(resObjs, DIGIT_INDICATOR_RESOURCE_SELECTED_FONT_SIZE);
    }
    return digitalParameters;
}

SwiperDigitalParameters GetJsViewDigitIndicatorInfo(const std::vector<std::string>& digitIndicatorInfo,
    const void* resObjs)
{
    auto digitalParameters = GetDigitIndicatorInfo(digitIndicatorInfo, resObjs);
    auto startValue = GetInfoFromVectorByIndexForDot(digitIndicatorInfo, JS_VIEW_DIGIT_INDICATOR_START);
    auto endValue = GetInfoFromVectorByIndexForDot(digitIndicatorInfo, JS_VIEW_DIGIT_INDICATOR_END);
    digitalParameters.dimStart = ParseIndicatorDimension(startValue);
    digitalParameters.dimEnd = ParseIndicatorDimension(endValue);
    auto ignoreSize = GetInfoFromVectorByIndexForDot(digitIndicatorInfo, DIGIT_INDICATOR_IGNORE_SIZE);
    digitalParameters.ignoreSizeValue = (ignoreSize == "1" ? true : false);

    auto hasDigitFontValue = GetInfoFromVectorByIndexForDot(digitIndicatorInfo, JS_VIEW_DIGIT_INDICATOR_HAS_FONT);
    auto hasSelectedDigitFontValue =
        GetInfoFromVectorByIndexForDot(digitIndicatorInfo, JS_VIEW_DIGIT_INDICATOR_HAS_SELECTED_FONT);
    if (hasDigitFontValue == "0") {
        digitalParameters.fontSize.reset();
        digitalParameters.fontWeight.reset();
        digitalParameters.resourceFontSizeValueObject = nullptr;
    }
    if (hasSelectedDigitFontValue == "0") {
        digitalParameters.selectedFontSize.reset();
        digitalParameters.selectedFontWeight.reset();
        digitalParameters.resourceSelectedFontSizeValueObject = nullptr;
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
    nextMarginValue = LessOrEqual(nextMarginValue, 0.0f) ? 0.0f : nextMarginValue;
    SwiperModelNG::SetNextMargin(
        frameNode, CalcDimension(nextMarginValue, (DimensionUnit)nextMarginUnit), static_cast<bool>(ignoreBlank));
}

void SetSwiperNextMarginRaw(ArkUINodeHandle node, ArkUI_Float32 nextMarginValue, ArkUI_Int32 nextMarginUnit,
    ArkUI_Bool ignoreBlank, void* nextMarginRawPtr)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    nextMarginValue = LessOrEqual(nextMarginValue, 0.0f) ? 0.0f : nextMarginValue;
    SwiperModelNG::SetNextMargin(
        frameNode, CalcDimension(nextMarginValue, (DimensionUnit)nextMarginUnit), static_cast<bool>(ignoreBlank));
    if (SystemProperties::ConfigChangePerform()) {
        auto* nextMargin = reinterpret_cast<ResourceObject*>(nextMarginRawPtr);
        auto nextMarginResObj = AceType::Claim(nextMargin);
        SwiperModelNG::ProcessNextMarginWithResourceObj(frameNode, nextMarginResObj);
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
        SwiperModelNG::ProcessNextMarginWithResourceObj(frameNode, nextMarginResObj);
    }
}

void SetSwiperMinSize(ArkUINodeHandle node, ArkUI_Float32 minSizeValue, ArkUI_Int32 minSizeUnitt)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SwiperModelNG::ResetDisplayCountWithObject(frameNode);
    SwiperModelNG::ResetDisplayMode(frameNode);
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
    prevMarginValue = LessOrEqual(prevMarginValue, 0.0f) ? 0.0f : prevMarginValue;
    SwiperModelNG::SetPreviousMargin(
        frameNode, CalcDimension(prevMarginValue, (DimensionUnit)prevMarginUnit), static_cast<bool>(ignoreBlank));
}

void SetSwiperPrevMarginRaw(ArkUINodeHandle node, ArkUI_Float32 prevMarginValue, ArkUI_Int32 prevMarginUnit,
    ArkUI_Bool ignoreBlank, void* prevMarginRawPtr)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    prevMarginValue = LessOrEqual(prevMarginValue, 0.0f) ? 0.0f : prevMarginValue;
    SwiperModelNG::SetPreviousMargin(
        frameNode, CalcDimension(prevMarginValue, (DimensionUnit)prevMarginUnit), static_cast<bool>(ignoreBlank));
    if (SystemProperties::ConfigChangePerform()) {
        auto* prevMargin = reinterpret_cast<ResourceObject*>(prevMarginRawPtr);
        auto prevMarginResObj = AceType::Claim(prevMargin);
        SwiperModelNG::ProcessPreviousMarginWithResourceObj(frameNode, prevMarginResObj);
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
        SwiperModelNG::ProcessPreviousMarginWithResourceObj(frameNode, prevMarginResObj);
    }
}

void SetSwiperDisplayCount(ArkUINodeHandle node, ArkUI_CharPtr displayCountChar, ArkUI_CharPtr displayCountType)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(displayCountChar);
    CHECK_NULL_VOID(displayCountType);
    SwiperModelNG::ResetDisplayCountWithObject(frameNode);
    SwiperModelNG::ResetDisplayMode(frameNode);
    std::string displayCountValue = std::string(displayCountChar);
    std::string type = std::string(displayCountType);
    if (type == "string" && displayCountValue == "auto") {
        SwiperModelNG::SetDisplayMode(frameNode, SwiperDisplayMode::AUTO_LINEAR);
        SwiperModelNG::ResetDisplayCount(frameNode);
    } else if (type == "number" && StringUtils::StringToInt(displayCountValue) > 0) {
        SwiperModelNG::SetDisplayCount(frameNode, StringUtils::StringToInt(displayCountValue));
    } else if (type == "minSize") {
        if (displayCountValue.empty()) {
            return;
        }
        CalcDimension minSizeValue = StringUtils::StringToCalcDimension(displayCountValue, false, DimensionUnit::VP);
        if (LessNotEqual(minSizeValue.Value(), 0.0)) {
            minSizeValue.SetValue(0.0);
        }
        SwiperModelNG::SetMinSize(frameNode, minSizeValue);
    } else if (type == "fillType") {
        SwiperModelNG::SetFillType(frameNode, StringUtils::StringToInt(displayCountValue));
    } else {
        SwiperModelNG::SetDisplayCount(frameNode, DEFAULT_DISPLAY_COUNT);
    }
}

void ResetSwiperDisplayCount(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SwiperModelNG::ResetDisplayCountWithObject(frameNode);
    SwiperModelNG::ResetDisplayMode(frameNode);
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
    CHECK_NULL_VOID(displayArrowStr);
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
        GetSwiperArrowResObj(frameNode, swiperArrowParameters, res);
        SwiperModelNG::SetArrowStyle(frameNode, swiperArrowParameters);
        SwiperModelNG::SetDisplayArrow(frameNode, true);
    } else if (displayArrowValue == DISPLAY_ARROW_TRUE) {
        if (displayArrowCAPI == 1) {
            SwiperArrowParameters swiperArrowParameters;
            if (!GetArrowInfo(res, swiperArrowParameters, nullptr)) {
                SwiperModelNG::SetDisplayArrow(frameNode, false);
                return;
            }
            GetSwiperArrowResObj(frameNode, swiperArrowParameters, res);
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
    CHECK_NULL_VOID(displayArrowStr);
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

void SetSwiperDisplayArrowForJs(ArkUINodeHandle node, ArkUI_Bool displayArrow)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SwiperModelNG::SetDisplayArrow(frameNode, displayArrow);
}

void SetSwiperHoverShowForJs(ArkUINodeHandle node, ArkUI_Bool hoverShow)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SwiperModelNG::SetHoverShow(frameNode, hoverShow);
}

void SetSwiperCurve(ArkUINodeHandle node, ArkUI_CharPtr curveChar)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    RefPtr<Curve> curve = Curves::LINEAR;
    curve = Framework::CreateCurve(curveChar);
    SwiperModelNG::SetCurve(frameNode, curve);
}

void SetSwiperCurveByCurve(ArkUINodeHandle node, void* curvePtr)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto curve = AceType::Claim(reinterpret_cast<Curve*>(curvePtr));
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

void SetSwiperCachedIndependent(ArkUINodeHandle node, ArkUI_Bool independent)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SwiperModelNG::SetCachedCountIndependent(frameNode, independent);
}

void ResetSwiperCachedIndependent(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SwiperModelNG::SetCachedCountIndependent(frameNode, DEFAULT_CACHED_INDEPENDENT);
}

ArkUI_Int32 GetSwiperCachedIndependent(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, DEFAULT_CACHED_INDEPENDENT);
    return static_cast<ArkUI_Int32>(SwiperModelNG::GetCachedCountIndependent(frameNode));
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

void SetSwiperIndexForJs(ArkUINodeHandle node, ArkUI_Int32 index)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SwiperModelNG::SetIndex(frameNode, index);
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

void SetJsViewSwiperIndicator(ArkUINodeHandle node, ArkUI_CharPtr indicatorStr)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(indicatorStr);
    std::vector<std::string> res;
    std::string indicatorValues = std::string(indicatorStr);
    StringUtils::StringSplitter(indicatorValues, '|', res);
    std::string type = res[INDICATOR_TYPE_INDEX];
    if (type == "showIndicator") {
        int32_t indicator = StringUtils::StringToInt(res[INDICATOR_VALUE]);
        SwiperModelNG::SetShowIndicator(frameNode, indicator == 1);
        return;
    }
    if (type == "ArkDigitIndicator") {
        SwiperDigitalParameters digitalParameters = GetJsViewDigitIndicatorInfo(res, nullptr);
        SwiperModelNG::SetDigitIndicatorStyle(frameNode, digitalParameters);
        SwiperModelNG::SetIndicatorType(frameNode, SwiperIndicatorType::DIGIT);
    } else if (type == "ArkDotIndicator") {
        SwiperParameters swiperParameters = GetJsViewDotIndicatorInfo(frameNode, res, nullptr);
        SwiperModelNG::SetDotIndicatorStyle(frameNode, swiperParameters);
        SwiperModelNG::SetIndicatorType(frameNode, SwiperIndicatorType::DOT);
    } else {
        SwiperParameters swiperParameters = GetDotIndicatorInfo(frameNode, res, nullptr);
        SwiperModelNG::SetDotIndicatorStyle(frameNode, swiperParameters);
        SwiperModelNG::SetIndicatorType(frameNode, SwiperIndicatorType::DOT);
    }
    if (type == "boolean") {
        int32_t indicator = StringUtils::StringToInt(res[INDICATOR_VALUE]);
        SwiperModelNG::SetShowIndicator(frameNode, indicator == 1);
    } else {
        SwiperModelNG::SetShowIndicator(frameNode, true);
    }
}

void SetJsViewSwiperIndicatorRaw(ArkUINodeHandle node, ArkUI_CharPtr indicatorStr, const void* resObjs)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(indicatorStr);
    std::vector<std::string> res;
    std::string indicatorValues = std::string(indicatorStr);
    StringUtils::StringSplitter(indicatorValues, '|', res);
    std::string type = res[INDICATOR_TYPE_INDEX];
    if (type == "showIndicator") {
        int32_t indicator = StringUtils::StringToInt(res[INDICATOR_VALUE]);
        SwiperModelNG::SetShowIndicator(frameNode, indicator == 1);
        return;
    }
    if (type == "ArkDigitIndicator") {
        SwiperDigitalParameters digitalParameters = GetJsViewDigitIndicatorInfo(res, resObjs);
        SwiperModelNG::SetDigitIndicatorStyle(frameNode, digitalParameters);
        SwiperModelNG::SetIndicatorType(frameNode, SwiperIndicatorType::DIGIT);
    } else if (type == "ArkDotIndicator") {
        SwiperParameters swiperParameters = GetJsViewDotIndicatorInfo(frameNode, res, resObjs);
        SwiperModelNG::SetDotIndicatorStyle(frameNode, swiperParameters);
        SwiperModelNG::SetIndicatorType(frameNode, SwiperIndicatorType::DOT);
    } else {
        SwiperParameters swiperParameters = GetDotIndicatorInfo(frameNode, res, resObjs);
        SwiperModelNG::SetDotIndicatorStyle(frameNode, swiperParameters);
        SwiperModelNG::SetIndicatorType(frameNode, SwiperIndicatorType::DOT);
    }
    if (type == "boolean") {
        int32_t indicator = StringUtils::StringToInt(res[INDICATOR_VALUE]);
        SwiperModelNG::SetShowIndicator(frameNode, indicator == 1);
    } else {
        SwiperModelNG::SetShowIndicator(frameNode, true);
    }
}

void SetSwiperIndicatorController(ArkUINodeHandle node, void* controller, void* resetFunc)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto* indicatorController = reinterpret_cast<RefPtr<AceType>*>(controller);
    CHECK_NULL_VOID(indicatorController);
    auto controllerBase = AceType::DynamicCast<JSIndicatorControllerBase>(*indicatorController);
    CHECK_NULL_VOID(controllerBase);

    SwiperModelNG::SetIndicatorController(frameNode, controllerBase);
    auto* resetFuncPtr = reinterpret_cast<std::function<void()>*>(resetFunc);
    if (resetFunc) {
        SwiperModelNG::SetJSIndicatorController(frameNode, *resetFuncPtr);
    }
}

void ResetSwiperIndicatorController(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<SwiperPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->ResetJSIndicatorController();
}

void ResetSwiperIndicatorControllerIfNeeded(ArkUINodeHandle node, void* controller)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<SwiperPattern>();
    CHECK_NULL_VOID(pattern);
    auto currentController = pattern->GetIndicatorController();
    auto* newController = reinterpret_cast<RefPtr<AceType>*>(controller);
    auto newControllerBase = newController ? AceType::DynamicCast<JSIndicatorControllerBase>(*newController) : nullptr;
    if (currentController && (!newControllerBase || currentController != newControllerBase)) {
        pattern->ResetJSIndicatorController();
    }
}

void* GetSwiperIndicatorController(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<SwiperPattern>();
    CHECK_NULL_RETURN(pattern, nullptr);
    auto controller = pattern->GetIndicatorController();
    RefPtr<AceType> controllerBase = controller;
    return AceType::RawPtr(controllerBase);
}

void SetSwiperBindIndicator(ArkUINodeHandle node, ArkUI_Bool bind)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SwiperModelNG::SetBindIndicator(frameNode, bind);
}

void SetSwiperIndicatorIsBoolean(ArkUINodeHandle node, ArkUI_Bool isBoolean)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SwiperModelNG::SetIndicatorIsBoolean(frameNode, isBoolean);
}

void SetSwiperShowIndicator(ArkUINodeHandle node, ArkUI_Bool showIndicator)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SwiperModelNG::SetShowIndicator(frameNode, showIndicator);
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

ArkUI_Int32 GetSwiperCurrentIndex(ArkUINodeHandle node, ArkUI_Bool original)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_INT_CODE);
    auto pattern = frameNode->GetPattern<SwiperPattern>();
    CHECK_NULL_RETURN(pattern, ERROR_INT_CODE);
    return static_cast<ArkUI_Int32>(pattern->GetCurrentIndex(original));
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
    return SwiperModelNG::GetDisplayMode(frameNode) == SwiperDisplayMode::AUTO_LINEAR ? "auto" : "stretch";
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
    CHECK_NULL_VOID(values);
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
    CHECK_NULL_VOID(values);
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
        GetSwiperIndicatorResObj(frameNode, swiperParameters, indicator);
        SwiperModelNG::SetDotIndicatorStyle(frameNode, swiperParameters);
        SwiperModelNG::SetIndicatorType(frameNode, SwiperIndicatorType::DOT);
    }
    SwiperModelNG::SetShowIndicator(frameNode, true);
}

void SetJsViewStyle(ArkUINodeHandle node, ArkUI_Bool isDot, void* swiperParameters)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(swiperParameters);
    if (!isDot) {
        auto* parameters = reinterpret_cast<SwiperDigitalParameters*>(swiperParameters);
        SwiperModelNG::SetDigitIndicatorStyle(frameNode, *parameters);
        SwiperModelNG::SetIndicatorType(frameNode, SwiperIndicatorType::DIGIT);
    } else {
        auto* parameters = reinterpret_cast<SwiperParameters*>(swiperParameters);
        SwiperModelNG::SetDotIndicatorStyle(frameNode, *parameters);
        SwiperModelNG::SetIndicatorType(frameNode, SwiperIndicatorType::DOT);
    }
}

void SetJsShowIndicator(ArkUINodeHandle node, ArkUI_Bool isShow)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SwiperModelNG::SetShowIndicator(frameNode, isShow);
}

void SetSwiperIndicatorStyleByParameters(ArkUINodeHandle node, void* swiperParameters,
    ArkUI_Bool setCustomSize, ArkUI_Bool isCustomSize)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(swiperParameters);
    auto* parameters = reinterpret_cast<SwiperParameters*>(swiperParameters);
    if (setCustomSize) {
        SwiperModelNG::SetIsIndicatorCustomSize(frameNode, isCustomSize);
    }
    SwiperModelNG::SetDotIndicatorStyle(frameNode, *parameters);
}

void SetSwiperIndicatorStyleByArrowParameters(ArkUINodeHandle node, void* arrowParams)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(arrowParams);
    auto* parameters = reinterpret_cast<SwiperArrowParameters*>(arrowParams);
    SwiperModelNG::SetArrowStyle(frameNode, *parameters);
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
        GetSwiperDigitIndicatorResObj(frameNode, swiperDigitParameters, indicator);
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

void SetSwiperCustomContentTransition(ArkUINodeHandle node, void* transition)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SwiperContentAnimatedTransition transitionInfo;
    if (transition) {
        auto customTransition = reinterpret_cast<SwiperContentAnimatedTransition*>(transition);
        transitionInfo = std::move(*customTransition);
    }
    SwiperModelNG::SetCustomContentTransition(frameNode, transitionInfo);
}

void ResetSwiperCustomContentTransition(ArkUINodeHandle node)
{
    SetSwiperCustomContentTransition(node, nullptr);
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

void SetSwiperOnScrollStateChanged(ArkUINodeHandle node, void* callback)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (callback) {
        auto onEvent = reinterpret_cast<std::function<void(const BaseEventInfo*)>*>(callback);
        SwiperModelNG::SetOnScrollStateChanged(frameNode, std::move(*onEvent));
    } else {
        SwiperModelNG::SetOnScrollStateChanged(frameNode, nullptr);
    }
}

void ResetSwiperOnScrollStateChanged(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SwiperModelNG::SetOnScrollStateChanged(frameNode, nullptr);
}

void SetSwiperFinishAnimation(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SwiperModelNG::SetSwiperFinishAnimation(frameNode);
}

void SetSwiperFillType(ArkUINodeHandle node, ArkUI_Int32 fillType)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SwiperModelNG::ResetDisplayCountWithObject(frameNode);
    SwiperModelNG::ResetDisplayMode(frameNode);
    SwiperModelNG::SetFillType(frameNode, fillType);
}

void ResetSwiperFillType(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SwiperModelNG::ResetFillType(frameNode);
    // DisplayCount need to be reset to the default value 1.
    SwiperModelNG::SetDisplayCount(frameNode, 1);
}

ArkUI_Int32 GetSwiperFillType(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_CODE_PARAM_INVALID);
    return SwiperModelNG::GetFillType(frameNode);
}

void CallSwiperStartFakeDrag(ArkUINodeHandle node, bool* isSuccessful)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    *isSuccessful = SwiperModelNG::CallSwiperStartFakeDrag(frameNode);
}

void CallSwiperFakeDragBy(ArkUINodeHandle node, float offset, bool* isConsumedOffset)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    *isConsumedOffset = SwiperModelNG::CallSwiperFakeDragBy(frameNode, offset);
}

void CallSwiperStopFakeDrag(ArkUINodeHandle node, bool* isSuccessful)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    *isSuccessful = SwiperModelNG::CallSwiperStopFakeDrag(frameNode);
}

void CallSwiperIsFakeDragging(ArkUINodeHandle node, bool* isFakeDragging)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    *isFakeDragging = SwiperModelNG::CallSwiperIsFakeDragging(frameNode);
}

void CallSwiperShowPrevious(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SwiperModelNG::CallSwiperShowPrevious(frameNode);
}

void CallSwiperShowNext(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SwiperModelNG::CallSwiperShowNext(frameNode);
}

void SetSwiperOnChangeEvent(ArkUINodeHandle node, void* callback)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (callback) {
        auto onChangeEvent = reinterpret_cast<std::function<void(const BaseEventInfo*)>*>(callback);
        SwiperModelNG::SetOnChangeEvent(frameNode, std::move(*onChangeEvent));
    } else {
        SwiperModelNG::SetOnChangeEvent(frameNode, nullptr);
    }
}
} // namespace

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
    if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_TWENTY_SIX)) {
        auto onEvent = [node, extraParam](int32_t selectedIndex, int32_t index, float position, float mainAxisLength) {
            ArkUINodeEvent event;
            event.kind = COMPONENT_ASYNC_EVENT;
            event.extraParam = reinterpret_cast<intptr_t>(extraParam);
            bool usePx = NodeModel::UsePXUnit(reinterpret_cast<ArkUI_Node*>(extraParam));
            double density = usePx ? PipelineBase::GetCurrentDensity() : 1;
            event.componentAsyncEvent.subKind = ON_SWIPER_DID_CONTENT_SCROLL;
            event.componentAsyncEvent.data[NUM_0].i32 = selectedIndex;
            event.componentAsyncEvent.data[NUM_1].i32 = index;
            event.componentAsyncEvent.data[NUM_2].f32 = position;
            event.componentAsyncEvent.data[NUM_3].f32 = mainAxisLength * density;
            SendArkUISyncEvent(&event);
        };
        SwiperModelNG::SetOnContentDidScroll(frameNode, std::move(onEvent));
    } else {
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

void SetSwiperScrollStateChanged(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto onEvent = [node, extraParam](const BaseEventInfo* info) {
        const auto* scrollStateInfo = TypeInfoHelper::DynamicCast<SwiperChangeEvent>(info);
        if (!scrollStateInfo) {
            LOGE("Swiper OnScrollStateChanged callback execute failed.");
            return;
        }
        int32_t index = scrollStateInfo->GetIndex();
        ArkUINodeEvent event;
        event.kind = COMPONENT_ASYNC_EVENT;
        event.extraParam = reinterpret_cast<intptr_t>(extraParam);
        event.componentAsyncEvent.subKind = ON_SWIPER_SCROLL_STATE_CHANGED;
        event.componentAsyncEvent.data[NUM_0].i32 = index;
        SendArkUISyncEvent(&event);
    };
    SwiperModelNG::SetOnScrollStateChanged(frameNode, std::move(onEvent));
}

void SetSwiperMainSizeWidth() {}

void SetSwiperMainSizeHeight() {}

void* GetAsyncEventHandlers(uint32_t kind)
{
    static const ComponentAsyncEventHandler swiperNodeAsyncEventHandlers[] = {
        SetSwiperChange,
        SetSwiperAnimationStart,
        SetSwiperAnimationEnd,
        SetSwiperGestureSwipe,
        SetSwiperOnContentDidScroll,
        SetSwiperSelected,
        SetSwiperUnselected,
        SetSwiperContentWillScroll,
        SetSwiperScrollStateChanged,
    };
    if (kind >= sizeof(swiperNodeAsyncEventHandlers) / sizeof(ComponentAsyncEventHandler)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "NotifyComponentAsyncEvent kind:%{public}d NOT IMPLEMENT", kind);
        return nullptr;
    }
    return reinterpret_cast<void*>(swiperNodeAsyncEventHandlers[kind]);
}

void* Create(ArkUI_Bool isCreateArc)
{
    auto controller = SwiperModelNG().Create(isCreateArc);
    CHECK_NULL_RETURN(controller, nullptr);
    return AceType::RawPtr(controller);
}

void SetJsSwiperRemoteMessage(ArkUINodeHandle node, ArkUI_VoidPtr remoteMessageFunc)
{
    (void)node;
    (void)remoteMessageFunc;
}

void SetJsSwiperOnClick(ArkUINodeHandle node, ArkUI_VoidPtr clickFunc)
{
    (void)node;
    (void)clickFunc;
}

void ApplySwiperIndicatorWithIcon(
    ArkUINodeHandle node, ArkUI_CharPtr indicatorStr, const void* resObjs, const void* indicatorIconRawPtr)
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
        if (indicatorIconRawPtr) {
            swiperParameters.indicatorIconMap =
                *(static_cast<const SwiperIndicatorIconMap*>(indicatorIconRawPtr));
        }
        SwiperModelNG::SetDotIndicatorStyle(frameNode, swiperParameters);
        SwiperModelNG::SetIndicatorType(frameNode, SwiperIndicatorType::DOT);
    } else {
        SwiperParameters swiperParameters = GetDotIndicatorInfo(frameNode, res, resObjs);
        if (indicatorIconRawPtr) {
            swiperParameters.indicatorIconMap =
                *(static_cast<const SwiperIndicatorIconMap*>(indicatorIconRawPtr));
        }
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

void SetSwiperIndicatorWithIcon(
    ArkUINodeHandle node, ArkUI_CharPtr indicatorStr, const void* resObjs, const void* indicatorIconRawPtr)
{
    ApplySwiperIndicatorWithIcon(node, indicatorStr, resObjs, indicatorIconRawPtr);
}

void SetSwiperIgnoreHiddenItem(ArkUINodeHandle node, ArkUI_Bool value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SwiperModelNG::SetIgnoreHiddenItem(frameNode, value);
}

void ResetSwiperIgnoreHiddenItem(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SwiperModelNG::SetIgnoreHiddenItem(frameNode, false);
}

#ifndef CROSS_PLATFORM
OHOS::Ace::SwiperModel* GetSwiperModelImpl()
{
    static auto loader = DynamicModuleHelper::GetInstance().GetLoaderByName("swiper");
    static OHOS::Ace::SwiperModel* instance =
        loader ? reinterpret_cast<OHOS::Ace::SwiperModel*>(loader->CreateModel()) : nullptr;
    return instance;
}

void* CreateImpl(ArkUI_Bool isCreateArc)
{
    auto swiperModelImpl = GetSwiperModelImpl();
    CHECK_NULL_RETURN(swiperModelImpl, nullptr);
    auto controller = swiperModelImpl->Create(isCreateArc);
    CHECK_NULL_RETURN(controller, nullptr);
    return AceType::RawPtr(controller);
}

void SetSwiperNextMarginImpl(ArkUINodeHandle node, ArkUI_Float32 nextMarginValue, ArkUI_Int32 nextMarginUnit,
    ArkUI_Bool ignoreBlank)
{
    (void)node;
    (void)nextMarginValue;
    (void)nextMarginUnit;
    (void)ignoreBlank;
}

void SetSwiperNextMarginRawImpl(ArkUINodeHandle node, ArkUI_Float32 nextMarginValue, ArkUI_Int32 nextMarginUnit,
    ArkUI_Bool ignoreBlank, void* nextMarginRawPtr)
{
    (void)node;
    (void)nextMarginValue;
    (void)nextMarginUnit;
    (void)ignoreBlank;
    (void)nextMarginRawPtr;
}

void ResetSwiperNextMarginImpl(ArkUINodeHandle node)
{
    (void)node;
}

void SetSwiperPrevMarginImpl(ArkUINodeHandle node, ArkUI_Float32 prevMarginValue, ArkUI_Int32 prevMarginUnit,
    ArkUI_Bool ignoreBlank)
{
    (void)node;
    (void)prevMarginValue;
    (void)prevMarginUnit;
    (void)ignoreBlank;
}

void SetSwiperPrevMarginRawImpl(ArkUINodeHandle node, ArkUI_Float32 prevMarginValue, ArkUI_Int32 prevMarginUnit,
    ArkUI_Bool ignoreBlank, void* prevMarginRawPtr)
{
    (void)node;
    (void)prevMarginValue;
    (void)prevMarginUnit;
    (void)ignoreBlank;
    (void)prevMarginRawPtr;
}

void ResetSwiperPrevMarginImpl(ArkUINodeHandle node)
{
    (void)node;
}

void SetSwiperDisplayCountImpl(ArkUINodeHandle node, ArkUI_CharPtr displayCountChar, ArkUI_CharPtr displayCountType)
{
    (void)node;
    CHECK_NULL_VOID(displayCountChar);
    CHECK_NULL_VOID(displayCountType);
    auto swiperModelImpl = GetSwiperModelImpl();
    CHECK_NULL_VOID(swiperModelImpl);
    std::string displayCountValue = std::string(displayCountChar);
    std::string type = std::string(displayCountType);
    if (type == "string" && displayCountValue == "auto") {
        swiperModelImpl->SetDisplayMode(SwiperDisplayMode::AUTO_LINEAR);
    } else if (type == "number" && StringUtils::StringToInt(displayCountValue) > 0) {
        swiperModelImpl->SetDisplayCount(StringUtils::StringToInt(displayCountValue));
    } else {
        swiperModelImpl->SetDisplayCount(DEFAULT_DISPLAY_COUNT);
    }
}

void ResetSwiperDisplayCountImpl(ArkUINodeHandle node)
{
    (void)node;
    auto swiperModelImpl = GetSwiperModelImpl();
    CHECK_NULL_VOID(swiperModelImpl);
    swiperModelImpl->SetDisplayCount(DEFAULT_DISPLAY_COUNT);
}

void SetSwiperSwipeByGroupImpl(ArkUINodeHandle node, ArkUI_Bool swipeByGroup)
{
    (void)node;
    (void)swipeByGroup;
}

void ResetSwiperSwipeByGroupImpl(ArkUINodeHandle node)
{
    (void)node;
}

void SetSwiperDisplayArrowImpl(ArkUINodeHandle node, ArkUI_CharPtr displayArrowStr)
{
    (void)node;
    (void)displayArrowStr;
}

void SetSwiperDisplayArrowRawImpl(ArkUINodeHandle node, ArkUI_CharPtr displayArrowStr, const void* resObjs)
{
    (void)node;
    (void)displayArrowStr;
    (void)resObjs;
}

void ResetSwiperDisplayArrowImpl(ArkUINodeHandle node)
{
    (void)node;
}

void SetSwiperCurveImpl(ArkUINodeHandle node, ArkUI_CharPtr curveChar)
{
    (void)node;
    auto swiperModelImpl = GetSwiperModelImpl();
    CHECK_NULL_VOID(swiperModelImpl);
    swiperModelImpl->SetCurve(Framework::CreateCurve(curveChar));
}

void SetSwiperCurveByCurveImpl(ArkUINodeHandle node, void* curve)
{
    (void)node;
    auto swiperModelImpl = GetSwiperModelImpl();
    CHECK_NULL_VOID(swiperModelImpl);
    swiperModelImpl->SetCurve(AceType::Claim(reinterpret_cast<Curve*>(curve)));
}

void ResetSwiperCurveImpl(ArkUINodeHandle node)
{
    (void)node;
    auto swiperModelImpl = GetSwiperModelImpl();
    CHECK_NULL_VOID(swiperModelImpl);
    swiperModelImpl->SetCurve(Curves::LINEAR);
}

void SetSwiperDisableSwipeImpl(ArkUINodeHandle node, ArkUI_Bool disableSwipe)
{
    (void)node;
    auto swiperModelImpl = GetSwiperModelImpl();
    CHECK_NULL_VOID(swiperModelImpl);
    swiperModelImpl->SetDisableSwipe(disableSwipe);
}

void ResetSwiperDisableSwipeImpl(ArkUINodeHandle node)
{
    (void)node;
    auto swiperModelImpl = GetSwiperModelImpl();
    CHECK_NULL_VOID(swiperModelImpl);
    swiperModelImpl->SetDisableSwipe(DEAFULT_DISABLE_SWIPE);
}

void SetSwiperEffectModeImpl(ArkUINodeHandle node, ArkUI_Int32 edgeEffect)
{
    (void)node;
    if (edgeEffect < 0 || edgeEffect >= static_cast<int32_t>(EDGE_EFFECT.size())) {
        return;
    }
    auto swiperModelImpl = GetSwiperModelImpl();
    CHECK_NULL_VOID(swiperModelImpl);
    swiperModelImpl->SetEdgeEffect(EDGE_EFFECT[edgeEffect]);
}

void ResetSwiperEffectModeImpl(ArkUINodeHandle node)
{
    (void)node;
    auto swiperModelImpl = GetSwiperModelImpl();
    CHECK_NULL_VOID(swiperModelImpl);
    swiperModelImpl->SetEdgeEffect(EdgeEffect::SPRING);
}

void SetSwiperCachedCountImpl(ArkUINodeHandle node, ArkUI_Int32 cachedCount)
{
    (void)node;
    auto swiperModelImpl = GetSwiperModelImpl();
    CHECK_NULL_VOID(swiperModelImpl);
    swiperModelImpl->SetCachedCount(cachedCount < 0 ? DEFAULT_CACHED_COUNT : cachedCount);
}

void ResetSwiperCachedCountImpl(ArkUINodeHandle node)
{
    (void)node;
    auto swiperModelImpl = GetSwiperModelImpl();
    CHECK_NULL_VOID(swiperModelImpl);
    swiperModelImpl->SetCachedCount(DEFAULT_CACHED_COUNT);
}

void SetSwiperIsShownImpl(ArkUINodeHandle node, ArkUI_Bool isShown)
{
    (void)node;
    (void)isShown;
}

void ResetSwiperIsShownImpl(ArkUINodeHandle node)
{
    (void)node;
}

void SetSwiperDisplayModeImpl(ArkUINodeHandle node, ArkUI_Int32 displayMode)
{
    (void)node;
    if (displayMode < 0 || displayMode >= static_cast<int32_t>(DISPLAY_MODE.size())) {
        return;
    }
    auto swiperModelImpl = GetSwiperModelImpl();
    CHECK_NULL_VOID(swiperModelImpl);
    swiperModelImpl->SetDisplayMode(DISPLAY_MODE[displayMode]);
}

void ResetSwiperDisplayModeImpl(ArkUINodeHandle node)
{
    (void)node;
    auto swiperModelImpl = GetSwiperModelImpl();
    CHECK_NULL_VOID(swiperModelImpl);
    swiperModelImpl->SetDisplayMode(SwiperDisplayMode::STRETCH);
}

void SetSwiperItemSpaceImpl(ArkUINodeHandle node, ArkUI_Float32 itemSpaceValue, ArkUI_Int32 itemSpaceUnit)
{
    (void)node;
    auto swiperModelImpl = GetSwiperModelImpl();
    CHECK_NULL_VOID(swiperModelImpl);
    swiperModelImpl->SetItemSpace(CalcDimension(itemSpaceValue, static_cast<DimensionUnit>(itemSpaceUnit)));
}

void ResetSwiperItemSpaceImpl(ArkUINodeHandle node)
{
    (void)node;
    auto swiperModelImpl = GetSwiperModelImpl();
    CHECK_NULL_VOID(swiperModelImpl);
    swiperModelImpl->SetItemSpace(CalcDimension(0.0, DimensionUnit::VP));
}

void SetSwiperVerticalImpl(ArkUINodeHandle node, ArkUI_Bool isVertical)
{
    (void)node;
    auto swiperModelImpl = GetSwiperModelImpl();
    CHECK_NULL_VOID(swiperModelImpl);
    swiperModelImpl->SetDirection(isVertical ? Axis::VERTICAL : Axis::HORIZONTAL);
}

void ResetSwiperVerticalImpl(ArkUINodeHandle node)
{
    (void)node;
    auto swiperModelImpl = GetSwiperModelImpl();
    CHECK_NULL_VOID(swiperModelImpl);
    swiperModelImpl->SetDirection(Axis::HORIZONTAL);
}

void SetSwiperLoopImpl(ArkUINodeHandle node, ArkUI_Bool loop)
{
    (void)node;
    auto swiperModelImpl = GetSwiperModelImpl();
    CHECK_NULL_VOID(swiperModelImpl);
    swiperModelImpl->SetLoop(loop);
}

void ResetSwiperLoopImpl(ArkUINodeHandle node)
{
    (void)node;
    auto swiperModelImpl = GetSwiperModelImpl();
    CHECK_NULL_VOID(swiperModelImpl);
    swiperModelImpl->SetLoop(DEFAULT_LOOP);
}

void SetSwiperIntervalImpl(ArkUINodeHandle node, ArkUI_Int32 interval)
{
    (void)node;
    auto swiperModelImpl = GetSwiperModelImpl();
    CHECK_NULL_VOID(swiperModelImpl);
    swiperModelImpl->SetAutoPlayInterval(interval < 0 ? DEFAULT_INTERVAL : interval);
}

void ResetSwiperIntervalImpl(ArkUINodeHandle node)
{
    (void)node;
    auto swiperModelImpl = GetSwiperModelImpl();
    CHECK_NULL_VOID(swiperModelImpl);
    swiperModelImpl->SetAutoPlayInterval(DEFAULT_INTERVAL);
}

void SetSwiperAutoPlayImpl(ArkUINodeHandle node, ArkUI_Bool autoPlay)
{
    (void)node;
    auto swiperModelImpl = GetSwiperModelImpl();
    CHECK_NULL_VOID(swiperModelImpl);
    swiperModelImpl->SetAutoPlay(autoPlay);
}

void ResetSwiperAutoPlayImpl(ArkUINodeHandle node)
{
    (void)node;
    auto swiperModelImpl = GetSwiperModelImpl();
    CHECK_NULL_VOID(swiperModelImpl);
    swiperModelImpl->SetAutoPlay(DEFAULT_AUTO_PLAY);
}

void SetSwiperStopWhenTouchedImpl(ArkUINodeHandle node, ArkUI_Bool stopWhenTouched)
{
    (void)node;
    (void)stopWhenTouched;
}

void ResetSwiperStopWhenTouchedImpl(ArkUINodeHandle node)
{
    (void)node;
}

void SetSwiperIndexImpl(ArkUINodeHandle node, ArkUI_Int32 index, ArkUI_Int32 animationMode)
{
    (void)node;
    (void)animationMode;
    auto swiperModelImpl = GetSwiperModelImpl();
    CHECK_NULL_VOID(swiperModelImpl);
    swiperModelImpl->SetIndex(index < 0 ? 0 : static_cast<uint32_t>(index));
}

void ResetSwiperIndexImpl(ArkUINodeHandle node)
{
    (void)node;
    auto swiperModelImpl = GetSwiperModelImpl();
    CHECK_NULL_VOID(swiperModelImpl);
    swiperModelImpl->SetIndex(0);
}

void SetSwiperIndicatorImpl(ArkUINodeHandle node, ArkUI_CharPtr indicatorStr)
{
    (void)node;
    CHECK_NULL_VOID(indicatorStr);
    auto swiperModelImpl = GetSwiperModelImpl();
    CHECK_NULL_VOID(swiperModelImpl);
    std::vector<std::string> res;
    std::string indicatorValues = std::string(indicatorStr);
    StringUtils::StringSplitter(indicatorValues, '|', res);
    if (res.empty()) {
        return;
    }
    std::string type = res[INDICATOR_TYPE_INDEX];
    if (type == "boolean" || type == "showIndicator") {
        int32_t indicator = res.size() > INDICATOR_VALUE ? StringUtils::StringToInt(res[INDICATOR_VALUE]) : 0;
        swiperModelImpl->SetShowIndicator(indicator == 1);
    } else {
        swiperModelImpl->SetShowIndicator(true);
    }
}

void SetSwiperIndicatorRawImpl(ArkUINodeHandle node, ArkUI_CharPtr indicatorStr, const void* resObjs)
{
    (void)resObjs;
    SetSwiperIndicatorImpl(node, indicatorStr);
}

void ResetSwiperIndicatorImpl(ArkUINodeHandle node)
{
    (void)node;
    auto swiperModelImpl = GetSwiperModelImpl();
    CHECK_NULL_VOID(swiperModelImpl);
    swiperModelImpl->SetShowIndicator(true);
}

void SetSwiperDurationImpl(ArkUINodeHandle node, ArkUI_Float32 duration)
{
    (void)node;
    auto swiperModelImpl = GetSwiperModelImpl();
    CHECK_NULL_VOID(swiperModelImpl);
    swiperModelImpl->SetDuration(static_cast<uint32_t>(duration < 0 ? DEFAULT_DURATION : duration));
}

void ResetSwiperDurationImpl(ArkUINodeHandle node)
{
    (void)node;
    auto swiperModelImpl = GetSwiperModelImpl();
    CHECK_NULL_VOID(swiperModelImpl);
    swiperModelImpl->SetDuration(DEFAULT_DURATION);
}

void SetSwiperEnabledImpl(ArkUINodeHandle node, ArkUI_Bool enabled)
{
    (void)node;
    auto swiperModelImpl = GetSwiperModelImpl();
    CHECK_NULL_VOID(swiperModelImpl);
    swiperModelImpl->SetEnabled(enabled);
}

void ResetSwiperEnabledImpl(ArkUINodeHandle node)
{
    (void)node;
    auto swiperModelImpl = GetSwiperModelImpl();
    CHECK_NULL_VOID(swiperModelImpl);
    swiperModelImpl->SetEnabled(false);
}

ArkUI_Int32 GetSwiperIntImpl(ArkUINodeHandle node)
{
    (void)node;
    return 0;
}

ArkUI_Int32 GetSwiperCurrentIndexImpl(ArkUINodeHandle node, ArkUI_Bool original)
{
    (void)node;
    (void)original;
    return 0;
}

ArkUI_Float32 GetSwiperFloatImpl(ArkUINodeHandle node)
{
    (void)node;
    return 0.0f;
}

void SetIndicatorInteractiveImpl(ArkUINodeHandle node, ArkUI_Bool enabled)
{
    (void)node;
    (void)enabled;
}

void ResetIndicatorInteractiveImpl(ArkUINodeHandle node)
{
    (void)node;
}

ArkUI_Int32 SetNodeAdapterImpl(ArkUINodeHandle node, ArkUINodeAdapterHandle handle)
{
    (void)node;
    (void)handle;
    return ERROR_CODE_PARAM_INVALID;
}

void ResetNodeAdapterImpl(ArkUINodeHandle node)
{
    (void)node;
}

ArkUINodeAdapterHandle GetNodeAdapterImpl(ArkUINodeHandle node)
{
    (void)node;
    return nullptr;
}

void SetSwiperNestedScrollImpl(ArkUINodeHandle node, ArkUI_Int32 (*value)[1])
{
    (void)node;
    (void)value;
}

void ResetSwiperNestedScrollImpl(ArkUINodeHandle node)
{
    (void)node;
}

void SetSwiperToIndexImpl(ArkUINodeHandle node, ArkUI_Int32 (*values)[2])
{
    (void)node;
    (void)values;
}

void GetSwiperMarginImpl(ArkUINodeHandle node, ArkUI_Int32 unit, ArkUISwiperMarginOptions* options)
{
    (void)node;
    (void)unit;
    if (options) {
        options->margin = 0.0f;
        options->ignoreBlank = false;
    }
}

void SetSwiperIndicatorStyleImpl(ArkUINodeHandle node, ArkUISwiperIndicator* swiperIndicator)
{
    (void)node;
    CHECK_NULL_VOID(swiperIndicator);
    auto swiperModelImpl = GetSwiperModelImpl();
    CHECK_NULL_VOID(swiperModelImpl);
    if (swiperIndicator->type != ArkUISwiperIndicatorType::DOT) {
        swiperModelImpl->SetShowIndicator(true);
        return;
    }
    DimensionUnit unit = static_cast<DimensionUnit>(swiperIndicator->dimUnit);
    SwiperParameters swiperParameters;
    swiperParameters.dimLeft = ParseIndicatorCommonDimension(swiperIndicator->dimLeft, unit);
    swiperParameters.dimTop = ParseIndicatorCommonDimension(swiperIndicator->dimTop, unit);
    swiperParameters.dimRight = ParseIndicatorCommonDimension(swiperIndicator->dimRight, unit);
    swiperParameters.dimBottom = ParseIndicatorCommonDimension(swiperIndicator->dimBottom, unit);
    if (swiperIndicator->itemWidth.isSet) {
        swiperParameters.itemWidth = Dimension(swiperIndicator->itemWidth.value, unit);
    }
    if (swiperIndicator->itemHeight.isSet) {
        swiperParameters.itemHeight = Dimension(swiperIndicator->itemHeight.value, unit);
    }
    if (swiperIndicator->maskValue.isSet) {
        swiperParameters.maskValue = swiperIndicator->maskValue.value == 1;
    }
    if (swiperIndicator->colorValue.isSet) {
        swiperParameters.colorVal = Color(swiperIndicator->colorValue.value);
    }
    if (swiperIndicator->selectedColorValue.isSet) {
        swiperParameters.selectedColorVal = Color(swiperIndicator->selectedColorValue.value);
    }
    swiperModelImpl->SetIndicatorStyle(swiperParameters);
    swiperModelImpl->SetShowIndicator(true);
}

void GetSwiperIndicatorImpl(ArkUINodeHandle node, ArkUISwiperIndicator* swiperIndicator)
{
    (void)node;
    (void)swiperIndicator;
}

ArkUINodeHandle GetSwiperControllerImpl(ArkUINodeHandle node)
{
    (void)node;
    return nullptr;
}

void SetSwiperCallbackImpl(ArkUINodeHandle node, void* callback)
{
    (void)node;
    (void)callback;
}

void SetSwiperOnChangeImpl(ArkUINodeHandle node, void* callback)
{
    (void)node;
    auto swiperModelImpl = GetSwiperModelImpl();
    CHECK_NULL_VOID(swiperModelImpl);
    if (callback) {
        auto onEvent = reinterpret_cast<std::function<void(const BaseEventInfo*)>*>(callback);
        swiperModelImpl->SetOnChange(std::move(*onEvent));
    } else {
        swiperModelImpl->SetOnChange(nullptr);
    }
}

void ResetSwiperOnChangeImpl(ArkUINodeHandle node)
{
    (void)node;
    auto swiperModelImpl = GetSwiperModelImpl();
    CHECK_NULL_VOID(swiperModelImpl);
    swiperModelImpl->SetOnChange(nullptr);
}

void ResetSwiperCallbackImpl(ArkUINodeHandle node)
{
    (void)node;
}

void SetSwiperCustomContentTransitionImpl(ArkUINodeHandle node, void* transition)
{
    (void)node;
    (void)transition;
}

void ResetSwiperCustomContentTransitionImpl(ArkUINodeHandle node)
{
    (void)node;
}

void SetSwiperPageFlipModeImpl(ArkUINodeHandle node, ArkUI_Int32 pageFlipMode)
{
    (void)node;
    (void)pageFlipMode;
}

void ResetSwiperPageFlipModeImpl(ArkUINodeHandle node)
{
    (void)node;
}

void SetSwiperOnContentWillScrollImpl(ArkUINodeHandle node, bool* callback)
{
    (void)node;
    (void)callback;
}

void SetSwiperMinSizeImpl(ArkUINodeHandle node, ArkUI_Float32 minSizeValue, ArkUI_Int32 minSizeUnit)
{
    (void)node;
    (void)minSizeValue;
    (void)minSizeUnit;
}

void ResetSwiperMinSizeImpl(ArkUINodeHandle node)
{
    (void)node;
}

void SetSwiperDigitIndicatorStyleImpl(ArkUINodeHandle node, ArkUISwiperDigitIndicator* swiperIndicator)
{
    (void)node;
    (void)swiperIndicator;
}

void GetSwiperDigitIndicatorImpl(ArkUINodeHandle node, ArkUISwiperDigitIndicator* swiperIndicator)
{
    (void)node;
    (void)swiperIndicator;
}

ArkUISwiperIndicatorType GetIndicatorTypeImpl(ArkUINodeHandle node)
{
    (void)node;
    return static_cast<ArkUISwiperIndicatorType>(0);
}

ArkUI_CharPtr GetSwiperDisplayModeImpl(ArkUINodeHandle node)
{
    (void)node;
    return nullptr;
}

ArkUISwiperArrowStyle GetSwiperArrowStyleImpl(ArkUINodeHandle node)
{
    (void)node;
    return {};
}

void SetMaintainVisibleContentPositionImpl(ArkUINodeHandle node, ArkUI_Bool value)
{
    (void)node;
    (void)value;
}

void ResetMaintainVisibleContentPositionImpl(ArkUINodeHandle node)
{
    (void)node;
}

void SetSwiperFinishAnimationImpl(ArkUINodeHandle node)
{
    (void)node;
}

void SetSwiperFillTypeImpl(ArkUINodeHandle node, ArkUI_Int32 fillType)
{
    (void)node;
    (void)fillType;
}

void ResetSwiperFillTypeImpl(ArkUINodeHandle node)
{
    (void)node;
}

void CallSwiperStartFakeDragImpl(ArkUINodeHandle node, bool* isSuccessful)
{
    (void)node;
    if (isSuccessful) {
        *isSuccessful = false;
    }
}

void CallSwiperFakeDragByImpl(ArkUINodeHandle node, float offset, bool* isConsumedOffset)
{
    (void)node;
    (void)offset;
    if (isConsumedOffset) {
        *isConsumedOffset = false;
    }
}

void CallSwiperStopFakeDragImpl(ArkUINodeHandle node, bool* isSuccessful)
{
    (void)node;
    if (isSuccessful) {
        *isSuccessful = false;
    }
}

void CallSwiperIsFakeDraggingImpl(ArkUINodeHandle node, bool* isFakeDragging)
{
    (void)node;
    if (isFakeDragging) {
        *isFakeDragging = false;
    }
}

void CallSwiperShowImpl(ArkUINodeHandle node)
{
    (void)node;
}

void SetSwiperCachedIndependentImpl(ArkUINodeHandle node, ArkUI_Bool independent)
{
    (void)node;
    (void)independent;
}

void ResetSwiperCachedIndependentImpl(ArkUINodeHandle node)
{
    (void)node;
}

void SetSwiperIndicatorControllerImpl(ArkUINodeHandle node, void* controller, void* resetFunc)
{
    (void)node;
    (void)controller;
    (void)resetFunc;
}

void ResetSwiperIndicatorControllerImpl(ArkUINodeHandle node)
{
    (void)node;
}

void ResetSwiperIndicatorControllerIfNeededImpl(ArkUINodeHandle node, void* controller)
{
    (void)node;
    (void)controller;
}

void* GetSwiperIndicatorControllerImpl(ArkUINodeHandle node)
{
    (void)node;
    return nullptr;
}

void SetSwiperBindIndicatorImpl(ArkUINodeHandle node, ArkUI_Bool bind)
{
    (void)node;
    (void)bind;
}

void SetSwiperIndicatorIsBooleanImpl(ArkUINodeHandle node, ArkUI_Bool isBoolean)
{
    (void)node;
    (void)isBoolean;
}

void SetSwiperShowIndicatorImpl(ArkUINodeHandle node, ArkUI_Bool showIndicator)
{
    (void)node;
    auto swiperModelImpl = GetSwiperModelImpl();
    CHECK_NULL_VOID(swiperModelImpl);
    swiperModelImpl->SetShowIndicator(showIndicator);
}

void SetJsViewSwiperIndicatorImpl(ArkUINodeHandle node, ArkUI_CharPtr indicatorStr)
{
    SetSwiperIndicatorImpl(node, indicatorStr);
}

void SetJsViewSwiperIndicatorRawImpl(ArkUINodeHandle node, ArkUI_CharPtr indicatorStr, const void* resObjs)
{
    (void)resObjs;
    SetSwiperIndicatorImpl(node, indicatorStr);
}

void SetSwiperIndicatorStyleByParametersImpl(ArkUINodeHandle node, void* swiperParameters,
    ArkUI_Bool setCustomSize, ArkUI_Bool isCustomSize)
{
    (void)node;
    (void)setCustomSize;
    (void)isCustomSize;
    auto swiperModelImpl = GetSwiperModelImpl();
    CHECK_NULL_VOID(swiperModelImpl);
    auto* parameters = reinterpret_cast<SwiperParameters*>(swiperParameters);
    CHECK_NULL_VOID(parameters);
    swiperModelImpl->SetIndicatorStyle(*parameters);
}

void SetSwiperIndicatorStyleByArrowParametersImpl(ArkUINodeHandle node, void* arrowParams)
{
    (void)node;
    (void)arrowParams;
}

void SetSwiperMainSizeWidthImpl()
{
    auto swiperModelImpl = GetSwiperModelImpl();
    CHECK_NULL_VOID(swiperModelImpl);
    swiperModelImpl->SetMainSwiperSizeWidth();
}

void SetSwiperMainSizeHeightImpl()
{
    auto swiperModelImpl = GetSwiperModelImpl();
    CHECK_NULL_VOID(swiperModelImpl);
    swiperModelImpl->SetMainSwiperSizeHeight();
}

void* GetAsyncEventHandlersImpl(uint32_t kind)
{
    (void)kind;
    return nullptr;
}

void SetSwiperDisplayArrowForJsImpl(ArkUINodeHandle node, ArkUI_Bool displayArrow)
{
    auto swiperModelImpl = GetSwiperModelImpl();
    CHECK_NULL_VOID(swiperModelImpl);
    swiperModelImpl->SetDisplayArrow(false);
}

void SetSwiperHoverShowForJsImpl(ArkUINodeHandle node, ArkUI_Bool hoverShow)
{
    auto swiperModelImpl = GetSwiperModelImpl();
    CHECK_NULL_VOID(swiperModelImpl);
    swiperModelImpl->SetHoverShow(false);
}

void SetJsViewStyleImpl(ArkUINodeHandle node, ArkUI_Bool isDot, void* swiperParameters)
{
    (void)node;
    (void)isDot;
    (void)swiperParameters;
}

void SetJsShowIndicatorImpl(ArkUINodeHandle node, ArkUI_Bool isShow)
{
    auto swiperModelImpl = GetSwiperModelImpl();
    CHECK_NULL_VOID(swiperModelImpl);
    swiperModelImpl->SetShowIndicator(isShow);
}

void SetSwiperIndexForJsImpl(ArkUINodeHandle node, ArkUI_Int32 index)
{
    auto swiperModelImpl = GetSwiperModelImpl();
    CHECK_NULL_VOID(swiperModelImpl);
    swiperModelImpl->SetIndex(index);
}

void SetJsSwiperRemoteMessageImpl(ArkUINodeHandle node, ArkUI_VoidPtr remoteMessageFunc)
{
    CHECK_NULL_VOID(remoteMessageFunc);
    auto callback = reinterpret_cast<RemoteCallback*>(remoteMessageFunc);
    auto swiperModelImpl = GetSwiperModelImpl();
    CHECK_NULL_VOID(swiperModelImpl);
    swiperModelImpl->SetRemoteMessageEventId(std::move(*callback));
}

void SetJsSwiperOnClickImpl(ArkUINodeHandle node, ArkUI_VoidPtr clickFunc)
{
    CHECK_NULL_VOID(clickFunc);
    auto callback =
        reinterpret_cast<std::function<void(const BaseEventInfo*, const RefPtr<V2::InspectorFunctionImpl>&)>*>(
            clickFunc);
    auto swiperModelImpl = GetSwiperModelImpl();
    CHECK_NULL_VOID(swiperModelImpl);
    swiperModelImpl->SetOnClick(std::move(*callback));
}

void SetSwiperIndicatorWithIconImpl(
    ArkUINodeHandle node, ArkUI_CharPtr indicatorStr, const void* resObjs, const void* indicatorIconRawPtr)
{}

void SetSwiperIgnoreHiddenItemImpl(ArkUINodeHandle node, ArkUI_Bool value)
{}

void ResetSwiperIgnoreHiddenItemImpl(ArkUINodeHandle node)
{}
#endif

namespace NodeModifier {
const ArkUISwiperModifier* GetSwiperModifier()
{
    static bool isCurrentUseNewPipeline = Container::IsCurrentUseNewPipeline();
    if (isCurrentUseNewPipeline) {
        CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
        static const ArkUISwiperModifier modifier = {
        .setSwiperNextMargin = SetSwiperNextMargin,
        .setSwiperNextMarginRaw = SetSwiperNextMarginRaw,
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
        .setSwiperCurveByCurve = SetSwiperCurveByCurve,
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
        .setSwiperIndicatorWithIcon = SetSwiperIndicatorWithIcon,
        .setSwiperIndicatorController = SetSwiperIndicatorController,
        .resetSwiperIndicatorController = ResetSwiperIndicatorController,
        .resetSwiperIndicatorControllerIfNeeded = ResetSwiperIndicatorControllerIfNeeded,
        .getSwiperIndicatorController = GetSwiperIndicatorController,
        .setSwiperBindIndicator = SetSwiperBindIndicator,
        .setSwiperIndicatorIsBoolean = SetSwiperIndicatorIsBoolean,
        .setSwiperShowIndicator = SetSwiperShowIndicator,
        .setJsViewSwiperIndicator = SetJsViewSwiperIndicator,
        .setJsViewSwiperIndicatorRaw = SetJsViewSwiperIndicatorRaw,
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
        .setSwiperIndicatorStyleByParameters = SetSwiperIndicatorStyleByParameters,
        .setSwiperIndicatorStyleByArrowParameters = SetSwiperIndicatorStyleByArrowParameters,
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
        .setSwiperCustomContentTransition = SetSwiperCustomContentTransition,
        .resetSwiperCustomContentTransition = ResetSwiperCustomContentTransition,
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
        .setSwiperOnScrollStateChanged = SetSwiperOnScrollStateChanged,
        .resetSwiperOnScrollStateChanged = ResetSwiperOnScrollStateChanged,
        .setSwiperFinishAnimation = SetSwiperFinishAnimation,
        .setSwiperFillType = SetSwiperFillType,
        .resetSwiperFillType = ResetSwiperFillType,
        .getSwiperFillType = GetSwiperFillType,
        .callSwiperStartFakeDrag = CallSwiperStartFakeDrag,
        .callSwiperFakeDragBy = CallSwiperFakeDragBy,
        .callSwiperStopFakeDrag = CallSwiperStopFakeDrag,
        .callSwiperIsFakeDragging = CallSwiperIsFakeDragging,
        .callSwiperShowPrevious = CallSwiperShowPrevious,
        .callSwiperShowNext = CallSwiperShowNext,
        .setSwiperCachedIndependent = SetSwiperCachedIndependent,
        .resetSwiperCachedIndependent = ResetSwiperCachedIndependent,
        .getSwiperCachedIndependent = GetSwiperCachedIndependent,
        .getAsyncEventHandlers = GetAsyncEventHandlers,
        .setSwiperOnChangeEvent = SetSwiperOnChangeEvent,
        .setSwiperMainSizeWidth = SetSwiperMainSizeWidth,
        .setSwiperMainSizeHeight = SetSwiperMainSizeHeight,
        .getSwiperCurrentIndex = GetSwiperCurrentIndex,
        .create = Create,
        .setSwiperDisplayArrowForJs = SetSwiperDisplayArrowForJs,
        .setSwiperHoverShowForJs = SetSwiperHoverShowForJs,
        .setJsViewStyle = SetJsViewStyle,
        .setJsShowIndicator = SetJsShowIndicator,
        .setSwiperIndexForJs = SetSwiperIndexForJs,
        .setJsSwiperRemoteMessage = SetJsSwiperRemoteMessage,
        .setJsSwiperOnClick = SetJsSwiperOnClick,
        .setSwiperIgnoreHiddenItem = SetSwiperIgnoreHiddenItem,
        .resetSwiperIgnoreHiddenItem = ResetSwiperIgnoreHiddenItem,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line
    return &modifier;
    }
#ifndef CROSS_PLATFORM
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const ArkUISwiperModifier modifier = {
        .setSwiperNextMargin = SetSwiperNextMarginImpl,
        .setSwiperNextMarginRaw = SetSwiperNextMarginRawImpl,
        .resetSwiperNextMargin = ResetSwiperNextMarginImpl,
        .setSwiperPrevMargin = SetSwiperPrevMarginImpl,
        .setSwiperPrevMarginRaw = SetSwiperPrevMarginRawImpl,
        .resetSwiperPrevMargin = ResetSwiperPrevMarginImpl,
        .setSwiperDisplayCount = SetSwiperDisplayCountImpl,
        .resetSwiperDisplayCount = ResetSwiperDisplayCountImpl,
        .setSwiperSwipeByGroup = SetSwiperSwipeByGroupImpl,
        .resetSwiperSwipeByGroup = ResetSwiperSwipeByGroupImpl,
        .setSwiperDisplayArrow = SetSwiperDisplayArrowImpl,
        .setSwiperDisplayArrowRaw = SetSwiperDisplayArrowRawImpl,
        .resetSwiperDisplayArrow = ResetSwiperDisplayArrowImpl,
        .setSwiperCurve = SetSwiperCurveImpl,
        .setSwiperCurveByCurve = SetSwiperCurveByCurveImpl,
        .resetSwiperCurve = ResetSwiperCurveImpl,
        .setSwiperDisableSwipe = SetSwiperDisableSwipeImpl,
        .resetSwiperDisableSwipe = ResetSwiperDisableSwipeImpl,
        .setSwiperEffectMode = SetSwiperEffectModeImpl,
        .resetSwiperEffectMode = ResetSwiperEffectModeImpl,
        .setSwiperCachedCount = SetSwiperCachedCountImpl,
        .resetSwiperCachedCount = ResetSwiperCachedCountImpl,
        .setSwiperIsShown = SetSwiperIsShownImpl,
        .resetSwiperIsShown = ResetSwiperIsShownImpl,
        .setSwiperDisplayMode = SetSwiperDisplayModeImpl,
        .resetSwiperDisplayMode = ResetSwiperDisplayModeImpl,
        .setSwiperItemSpace = SetSwiperItemSpaceImpl,
        .resetSwiperItemSpace = ResetSwiperItemSpaceImpl,
        .setSwiperVertical = SetSwiperVerticalImpl,
        .resetSwiperVertical = ResetSwiperVerticalImpl,
        .setSwiperLoop = SetSwiperLoopImpl,
        .resetSwiperLoop = ResetSwiperLoopImpl,
        .setSwiperInterval = SetSwiperIntervalImpl,
        .resetSwiperInterval = ResetSwiperIntervalImpl,
        .setSwiperAutoPlay = SetSwiperAutoPlayImpl,
        .resetSwiperAutoPlay = ResetSwiperAutoPlayImpl,
        .setSwiperStopWhenTouched = SetSwiperStopWhenTouchedImpl,
        .resetSwiperStopWhenTouched = ResetSwiperStopWhenTouchedImpl,
        .setSwiperIndex = SetSwiperIndexImpl,
        .resetSwiperIndex = ResetSwiperIndexImpl,
        .setSwiperIndicator = SetSwiperIndicatorImpl,
        .setSwiperIndicatorRaw = SetSwiperIndicatorRawImpl,
        .setSwiperIndicatorWithIcon = SetSwiperIndicatorWithIconImpl,
        .setSwiperIndicatorController = SetSwiperIndicatorControllerImpl,
        .resetSwiperIndicatorController = ResetSwiperIndicatorControllerImpl,
        .resetSwiperIndicatorControllerIfNeeded = ResetSwiperIndicatorControllerIfNeededImpl,
        .getSwiperIndicatorController = GetSwiperIndicatorControllerImpl,
        .setSwiperBindIndicator = SetSwiperBindIndicatorImpl,
        .setSwiperIndicatorIsBoolean = SetSwiperIndicatorIsBooleanImpl,
        .setSwiperShowIndicator = SetSwiperShowIndicatorImpl,
        .setJsViewSwiperIndicator = SetJsViewSwiperIndicatorImpl,
        .setJsViewSwiperIndicatorRaw = SetJsViewSwiperIndicatorRawImpl,
        .resetSwiperIndicator = ResetSwiperIndicatorImpl,
        .setSwiperDuration = SetSwiperDurationImpl,
        .resetSwiperDuration = ResetSwiperDurationImpl,
        .setSwiperEnabled = SetSwiperEnabledImpl,
        .resetSwiperEnabled = ResetSwiperEnabledImpl,
        .getSwiperLoop = GetSwiperIntImpl,
        .getSwiperAutoPlay = GetSwiperIntImpl,
        .getSwiperStopWhenTouched = GetSwiperIntImpl,
        .getSwiperIndex = GetSwiperIntImpl,
        .getSwiperVertical = GetSwiperIntImpl,
        .getSwiperDuration = GetSwiperFloatImpl,
        .getSwiperDisplayCount = GetSwiperIntImpl,
        .getSwiperCachedIsShown = GetSwiperIntImpl,
        .getSwiperInterval = GetSwiperFloatImpl,
        .getSwiperCurve = GetSwiperIntImpl,
        .getSwiperDisableSwipe = GetSwiperIntImpl,
        .getSwiperItemSpace = GetSwiperFloatImpl,
        .getSwiperShowIndicator = GetSwiperIntImpl,
        .getSwiperShowDisplayArrow = GetSwiperIntImpl,
        .getSwiperEffectMode = GetSwiperIntImpl,
        .setIndicatorInteractive = SetIndicatorInteractiveImpl,
        .resetIndicatorInteractive = ResetIndicatorInteractiveImpl,
        .setNodeAdapter = SetNodeAdapterImpl,
        .resetNodeAdapter = ResetNodeAdapterImpl,
        .getNodeAdapter = GetNodeAdapterImpl,
        .getCachedCount = GetSwiperIntImpl,
        .setSwiperNestedScroll = SetSwiperNestedScrollImpl,
        .resetSwiperNestedScroll = ResetSwiperNestedScrollImpl,
        .getSwiperNestedScroll = GetSwiperIntImpl,
        .setSwiperToIndex = SetSwiperToIndexImpl,
        .getSwiperPrevMargin = GetSwiperMarginImpl,
        .getSwiperNextMargin = GetSwiperMarginImpl,
        .setSwiperIndicatorStyle = SetSwiperIndicatorStyleImpl,
        .setSwiperIndicatorStyleByParameters = SetSwiperIndicatorStyleByParametersImpl,
        .setSwiperIndicatorStyleByArrowParameters = SetSwiperIndicatorStyleByArrowParametersImpl,
        .getSwiperIndicator = GetSwiperIndicatorImpl,
        .getSwiperController = GetSwiperControllerImpl,
        .setSwiperOnChange = SetSwiperOnChangeImpl,
        .resetSwiperOnChange = ResetSwiperOnChangeImpl,
        .setSwiperOnUnselected = SetSwiperCallbackImpl,
        .resetSwiperOnUnselected = ResetSwiperCallbackImpl,
        .setSwiperOnAnimationStart = SetSwiperCallbackImpl,
        .resetSwiperOnAnimationStart = ResetSwiperCallbackImpl,
        .setSwiperOnAnimationEnd = SetSwiperCallbackImpl,
        .resetSwiperOnAnimationEnd = ResetSwiperCallbackImpl,
        .setSwiperOnGestureSwipe = SetSwiperCallbackImpl,
        .resetSwiperOnGestureSwipe = ResetSwiperCallbackImpl,
        .setSwiperCustomContentTransition = SetSwiperCustomContentTransitionImpl,
        .resetSwiperCustomContentTransition = ResetSwiperCustomContentTransitionImpl,
        .setSwiperOnContentDidScroll = SetSwiperCallbackImpl,
        .resetSwiperOnContentDidScroll = ResetSwiperCallbackImpl,
        .getIndicatorInteractive = GetSwiperIntImpl,
        .setSwiperPageFlipMode = SetSwiperPageFlipModeImpl,
        .resetSwiperPageFlipMode = ResetSwiperPageFlipModeImpl,
        .getSwiperPageFlipMode = GetSwiperIntImpl,
        .setSwiperOnContentWillScroll = SetSwiperOnContentWillScrollImpl,
        .resetSwiperOnContentWillScroll = ResetSwiperCallbackImpl,
        .setSwiperOnSelected = SetSwiperCallbackImpl,
        .resetSwiperOnSelected = ResetSwiperCallbackImpl,
        .setSwiperMinSize = SetSwiperMinSizeImpl,
        .resetSwiperMinSize = ResetSwiperMinSizeImpl,
        .getSwiperMinSize = GetSwiperFloatImpl,
        .setSwiperDigitIndicatorStyle = SetSwiperDigitIndicatorStyleImpl,
        .getSwiperDigitIndicator = GetSwiperDigitIndicatorImpl,
        .getIndicatorType = GetIndicatorTypeImpl,
        .getSwiperSwipeByGroup = GetSwiperIntImpl,
        .getSwiperDisplayMode = GetSwiperDisplayModeImpl,
        .getSwiperArrowStyle = GetSwiperArrowStyleImpl,
        .setMaintainVisibleContentPosition = SetMaintainVisibleContentPositionImpl,
        .resetMaintainVisibleContentPosition = ResetMaintainVisibleContentPositionImpl,
        .getMaintainVisibleContentPosition = GetSwiperIntImpl,
        .setSwiperOnScrollStateChanged = SetSwiperCallbackImpl,
        .resetSwiperOnScrollStateChanged = ResetSwiperCallbackImpl,
        .setSwiperFinishAnimation = SetSwiperFinishAnimationImpl,
        .setSwiperFillType = SetSwiperFillTypeImpl,
        .resetSwiperFillType = ResetSwiperFillTypeImpl,
        .getSwiperFillType = GetSwiperIntImpl,
        .callSwiperStartFakeDrag = CallSwiperStartFakeDragImpl,
        .callSwiperFakeDragBy = CallSwiperFakeDragByImpl,
        .callSwiperStopFakeDrag = CallSwiperStopFakeDragImpl,
        .callSwiperIsFakeDragging = CallSwiperIsFakeDraggingImpl,
        .callSwiperShowPrevious = CallSwiperShowImpl,
        .callSwiperShowNext = CallSwiperShowImpl,
        .setSwiperCachedIndependent = SetSwiperCachedIndependentImpl,
        .resetSwiperCachedIndependent = ResetSwiperCachedIndependentImpl,
        .getSwiperCachedIndependent = GetSwiperIntImpl,
        .getAsyncEventHandlers = GetAsyncEventHandlersImpl,
        .setSwiperOnChangeEvent = SetSwiperOnChangeImpl,
        .setSwiperMainSizeWidth = SetSwiperMainSizeWidthImpl,
        .setSwiperMainSizeHeight = SetSwiperMainSizeHeightImpl,
        .getSwiperCurrentIndex = GetSwiperCurrentIndexImpl,
        .create = CreateImpl,
        .setSwiperDisplayArrowForJs = SetSwiperDisplayArrowForJsImpl,
        .setSwiperHoverShowForJs = SetSwiperHoverShowForJsImpl,
        .setJsViewStyle = SetJsViewStyleImpl,
        .setJsShowIndicator = SetJsShowIndicatorImpl,
        .setSwiperIndexForJs = SetSwiperIndexForJsImpl,
        .setJsSwiperRemoteMessage = SetJsSwiperRemoteMessageImpl,
        .setJsSwiperOnClick = SetJsSwiperOnClickImpl,
        .setSwiperIgnoreHiddenItem = SetSwiperIgnoreHiddenItemImpl,
        .resetSwiperIgnoreHiddenItem = ResetSwiperIgnoreHiddenItemImpl,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line
    return &modifier;
#else
    return nullptr;
#endif
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

} // namespace NodeModifier
} // namespace OHOS::Ace::NG
