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
#include "core/common/container.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/pattern/swiper_indicator/indicator_common/indicator_model_ng.h"
#include "core/components_ng/token_theme/token_theme_storage.h"
#include "core/pipeline/base/element_register.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
constexpr int32_t INDICATOR_TYPE_INDEX = 0;
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
constexpr int32_t DOT_INDICATOR_SPACE = 13;
constexpr int32_t DEFAULT_INDICATOR_COUNT = 2;
constexpr int32_t DOT_INDICATOR_RESOURCE_ITEM_WIDTH = 0;
constexpr int32_t DOT_INDICATOR_RESOURCE_ITEM_HEIGHT = 1;
constexpr int32_t DOT_INDICATOR_RESOURCE_SELECTED_ITEM_WIDTH = 2;
constexpr int32_t DOT_INDICATOR_RESOURCE_SELECTED_ITEM_HEIGHT = 3;
constexpr int32_t DOT_INDICATOR_RESOURCE_COLOR = 4;
constexpr int32_t DOT_INDICATOR_RESOURCE_SELECTED_COLOR = 5;
constexpr int32_t DIGIT_INDICATOR_RESOURCE_FONT_COLOR = 0;
constexpr int32_t DIGIT_INDICATOR_RESOURCE_FONT_SELECTED_COLOR = 1;
constexpr int32_t DIGIT_INDICATOR_RESOURCE_FONT_SIZE = 2;
constexpr int32_t DIGIT_INDICATOR_RESOURCE_SELECTED_FONT_SIZE = 3;
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

std::string GetInfoFromVectorByIndexForDot(const std::vector<std::string>& dotIndicatorInfo, int32_t index)
{
    auto dotIndicatorInfoSize = dotIndicatorInfo.size();
    return dotIndicatorInfoSize < DOT_INDICATOR_INFO_SIZE
               ? ""
               : (dotIndicatorInfo[index] == "-" ? "" : dotIndicatorInfo[index]);
}

std::string GetInfoFromVectorByIndex(const std::vector<std::string>& dotIndicatorInfo, int32_t index)
{
    if (index < 0 || index >= static_cast<int32_t>(dotIndicatorInfo.size())) {
        return "";
    }
    return dotIndicatorInfo[index] == "-" ? "" : dotIndicatorInfo[index];
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

SwiperDigitalParameters GetDigitIndicatorInfo(const std::vector<std::string>& digitIndicatorInfo, const void* resObjs)
{
    auto dotLeftValue = GetInfoFromVectorByIndex(digitIndicatorInfo, DIGIT_INDICATOR_LEFT);
    auto dotTopValue = GetInfoFromVectorByIndex(digitIndicatorInfo, DIGIT_INDICATOR_TOP);
    auto dotRightValue = GetInfoFromVectorByIndex(digitIndicatorInfo, DIGIT_INDICATOR_RIGHT);
    auto dotBottomValue = GetInfoFromVectorByIndex(digitIndicatorInfo, DIGIT_INDICATOR_BOTTOM);
    auto fontColorValue = GetInfoFromVectorByIndex(digitIndicatorInfo, DIGIT_INDICATOR_FONT_COLOR);
    auto selectedFontColorValue = GetInfoFromVectorByIndex(digitIndicatorInfo, DIGIT_INDICATOR_SELECTED_FONT_COLOR);
    auto digitFontSize = GetInfoFromVectorByIndex(digitIndicatorInfo, DIGIT_INDICATOR_DIGIT_FONT_SIZE);
    auto digitFontWeight = GetInfoFromVectorByIndex(digitIndicatorInfo, DIGIT_INDICATOR_DIGIT_FONT_WEIGHT);
    auto selectedDigitFontSize =
        GetInfoFromVectorByIndex(digitIndicatorInfo, DIGIT_INDICATOR_SELECTED_DIGIT_FONT_SIZE);
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
    digitalParameters.dimBottom = ParseIndicatorDimension(dotBottomValue);
    Color fontColor;
    parseOk = Color::ParseColorString(fontColorValue, fontColor);
    digitalParameters.fontColor =
        parseOk ? (digitalParameters.parametersByUser.insert("fontColor"), fontColor)
        : swiperIndicatorTheme->GetDigitalIndicatorTextStyle().GetTextColor();
    parseOk = Color::ParseColorString(selectedFontColorValue, fontColor);
    digitalParameters.selectedFontColor =
        parseOk ? (digitalParameters.parametersByUser.insert("selectedFontColor"), fontColor)
        : swiperIndicatorTheme->GetDigitalIndicatorTextStyle().GetTextColor();
    GetFontContent(digitFontSize, digitFontWeight, false, digitalParameters);
    GetFontContent(selectedDigitFontSize, selectedDigitFontWeight, true, digitalParameters);
    if (SystemProperties::ConfigChangePerform() && resObjs) {
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

void SetItem4GetDotIndicatorInfo(
    SwiperParameters& indicatorParameters, FrameNode* frameNode, const std::vector<std::string>& dotIndicatorInfo)
{
    CHECK_NULL_VOID(frameNode);
    auto pipelineContext = frameNode->GetContext();
    CHECK_NULL_VOID(pipelineContext);
    auto swiperIndicatorTheme = pipelineContext->GetTheme<SwiperIndicatorTheme>();
    CHECK_NULL_VOID(swiperIndicatorTheme);
    auto itemWidthValue = GetInfoFromVectorByIndexForDot(dotIndicatorInfo, DOT_INDICATOR_ITEM_WIDTH);
    auto itemHeightValue = GetInfoFromVectorByIndexForDot(dotIndicatorInfo, DOT_INDICATOR_ITEM_HEIGHT);
    auto selectedItemWidthValue = GetInfoFromVectorByIndexForDot(dotIndicatorInfo, DOT_INDICATOR_SELECTED_ITEM_WIDTH);
    auto selectedItemHeightValue = GetInfoFromVectorByIndexForDot(dotIndicatorInfo, DOT_INDICATOR_SELECTED_ITEM_HEIGHT);
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

void SetIsIndicatorCustomSize(ArkUINodeHandle node, ArkUI_Bool isCustomSize)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    IndicatorModelNG::SetIsIndicatorCustomSize(frameNode, isCustomSize);
}

void InitIndicatorParametersWithResObj(SwiperParameters& indicatorParameters, const void* resObjs)
{
    CHECK_NULL_VOID(SystemProperties::ConfigChangePerform());
    CHECK_NULL_VOID(resObjs);
    indicatorParameters.resourceItemWidthValueObject =
        GetResourceObjByIndex(resObjs, DOT_INDICATOR_RESOURCE_ITEM_WIDTH);
    indicatorParameters.resourceItemHeightValueObject =
        GetResourceObjByIndex(resObjs, DOT_INDICATOR_RESOURCE_ITEM_HEIGHT);
    indicatorParameters.resourceSelectedItemWidthValueObject =
        GetResourceObjByIndex(resObjs, DOT_INDICATOR_RESOURCE_SELECTED_ITEM_WIDTH);
    indicatorParameters.resourceSelectedItemHeightValueObject =
        GetResourceObjByIndex(resObjs, DOT_INDICATOR_RESOURCE_SELECTED_ITEM_HEIGHT);
    indicatorParameters.resourceColorValueObject = GetResourceObjByIndex(resObjs, DOT_INDICATOR_RESOURCE_COLOR);
    indicatorParameters.resourceSelectedColorValueObject =
        GetResourceObjByIndex(resObjs, DOT_INDICATOR_RESOURCE_SELECTED_COLOR);
}

SwiperParameters GetDotIndicatorInfo(FrameNode* frameNode, const std::vector<std::string>& dotIndicatorInfo,
    const void* resObjs)
{
    auto maskValue = GetInfoFromVectorByIndexForDot(dotIndicatorInfo, DOT_INDICATOR_MASK);
    auto colorValue = GetInfoFromVectorByIndexForDot(dotIndicatorInfo, DOT_INDICATOR_COLOR);
    auto selectedColorValue = GetInfoFromVectorByIndexForDot(dotIndicatorInfo, DOT_INDICATOR_SELECTED_COLOR);
    auto spaceValue = GetInfoFromVectorByIndexForDot(dotIndicatorInfo, DOT_INDICATOR_SPACE);
    CHECK_NULL_RETURN(frameNode, SwiperParameters());
    auto pipelineContext = frameNode->GetContext();
    CHECK_NULL_RETURN(pipelineContext, SwiperParameters());
    auto swiperIndicatorTheme = pipelineContext->GetTheme<SwiperIndicatorTheme>();
    CHECK_NULL_RETURN(swiperIndicatorTheme, SwiperParameters());
    bool parseOk = false;
    SwiperParameters indicatorParameters;
    SetItem4GetDotIndicatorInfo(indicatorParameters, frameNode, dotIndicatorInfo);
    auto leftValue = GetInfoFromVectorByIndexForDot(dotIndicatorInfo, DOT_INDICATOR_LEFT);
    auto topValue = GetInfoFromVectorByIndexForDot(dotIndicatorInfo, DOT_INDICATOR_TOP);
    auto rightValue = GetInfoFromVectorByIndexForDot(dotIndicatorInfo, DOT_INDICATOR_RIGHT);
    auto bottomValue = GetInfoFromVectorByIndexForDot(dotIndicatorInfo, DOT_INDICATOR_BOTTOM);
    indicatorParameters.dimLeft = ParseIndicatorDimension(leftValue);
    indicatorParameters.dimTop = ParseIndicatorDimension(topValue);
    indicatorParameters.dimRight = ParseIndicatorDimension(rightValue);
    indicatorParameters.dimBottom = ParseIndicatorDimension(bottomValue);
    if (maskValue != "2") {
        indicatorParameters.maskValue = (maskValue == "1");
    }
    Color colorVal;
    parseOk = Color::ParseColorString(colorValue, colorVal);
    indicatorParameters.colorVal = parseOk ? (indicatorParameters.parametersByUser.insert("colorVal"), colorVal)
        : swiperIndicatorTheme->GetColor();
    parseOk = Color::ParseColorString(selectedColorValue, colorVal);
    indicatorParameters.selectedColorVal = parseOk
        ? (indicatorParameters.parametersByUser.insert("selectedColorVal"), colorVal)
        : swiperIndicatorTheme->GetSelectedColor();
    auto maxDisplayCount = GetInfoFromVectorByIndexForDot(dotIndicatorInfo, DOT_INDICATOR_MAX_DISPLAY_COUNT);
    if (!maxDisplayCount.empty()) {
        indicatorParameters.maxDisplayCountVal = StringUtils::StringToInt(maxDisplayCount);
    }
    auto space = StringUtils::StringToCalcDimension(spaceValue, false, DimensionUnit::VP);
    bool parseSpaceOk = !spaceValue.empty() && space.Unit() != DimensionUnit::PERCENT;
    auto defaultSpaceSize = swiperIndicatorTheme->GetIndicatorDotItemSpace();
    indicatorParameters.dimSpace = (parseSpaceOk && !(space < 0.0_vp)) ? space : defaultSpaceSize;
    InitIndicatorParametersWithResObj(indicatorParameters, resObjs);
    return indicatorParameters;
}

void SetInitialIndex(ArkUINodeHandle node, ArkUI_Int32 index)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    index = index < 0 ? 0 : index;
    IndicatorModelNG::SetInitialIndex(frameNode, index);
}

void ResetInitialIndex(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    IndicatorModelNG::SetInitialIndex(frameNode, 0);
}

void* Create()
{
    auto controller = IndicatorModelNG().Create();
    CHECK_NULL_RETURN(controller, nullptr);
    return AceType::RawPtr(controller);
}

void SetCount(ArkUINodeHandle node, ArkUI_Int32 count)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (count < 0) {
        count = DEFAULT_INDICATOR_COUNT;
    }
    IndicatorModelNG::SetCount(frameNode, count);
}

void ResetCount(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    IndicatorModelNG::SetCount(frameNode, DEFAULT_INDICATOR_COUNT);
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

void SetStyle(ArkUINodeHandle node, ArkUI_CharPtr indicatorStr, const void* resObjs)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(indicatorStr);
    std::vector<std::string> res;
    std::string indicatorValues = std::string(indicatorStr);
    StringUtils::StringSplitter(indicatorValues, '|', res);
    std::string type = res[INDICATOR_TYPE_INDEX];
    if (type == "ArkDigitIndicator") {
        SwiperDigitalParameters digitalParameters = GetDigitIndicatorInfo(res, resObjs);
        IndicatorModelNG::SetDigitIndicatorStyle(frameNode, digitalParameters);
        IndicatorModelNG::SetIndicatorType(frameNode, SwiperIndicatorType::DIGIT);
    } else {
        SwiperParameters indicatorParameters = GetDotIndicatorInfo(frameNode, res, resObjs);
        IndicatorModelNG::SetDotIndicatorStyle(frameNode, indicatorParameters);
        IndicatorModelNG::SetIndicatorType(frameNode, SwiperIndicatorType::DOT);
    }
}

void SetJsViewStyle(ArkUINodeHandle node, ArkUI_Bool isDot, void* swiperParameters)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(swiperParameters);
    if (!isDot) {
        auto* parameters = reinterpret_cast<SwiperDigitalParameters*>(swiperParameters);
        IndicatorModelNG::SetDigitIndicatorStyle(frameNode, *parameters);
        IndicatorModelNG::SetIndicatorType(frameNode, SwiperIndicatorType::DIGIT);
    } else {
        auto* parameters = reinterpret_cast<SwiperParameters*>(swiperParameters);
        IndicatorModelNG::SetDotIndicatorStyle(frameNode, *parameters);
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

#ifndef CROSS_PLATFORM
void* CreateImpl()
{
    return nullptr;
}

void SetInitialIndexImpl(ArkUINodeHandle node, ArkUI_Int32 index)
{
    (void)node;
    (void)index;
}

void ResetInitialIndexImpl(ArkUINodeHandle node)
{
    (void)node;
}

void SetCountImpl(ArkUINodeHandle node, ArkUI_Int32 count)
{
    (void)node;
    (void)count;
}

void ResetCountImpl(ArkUINodeHandle node)
{
    (void)node;
}

void SetOnChangeImpl(ArkUINodeHandle node, void* callback)
{
    (void)node;
    (void)callback;
}

void ResetOnChangeImpl(ArkUINodeHandle node)
{
    (void)node;
}

void SetStyleImpl(ArkUINodeHandle node, ArkUI_CharPtr indicatorStr, const void* resObjs)
{
    (void)node;
    (void)indicatorStr;
    (void)resObjs;
}

void SetJsViewStyleImpl(ArkUINodeHandle node, ArkUI_Bool isDot, void* swiperParameters)
{
    (void)node;
    (void)isDot;
    (void)swiperParameters;
}

void ResetStyleImpl(ArkUINodeHandle node)
{
    (void)node;
}

void SetLoopImpl(ArkUINodeHandle node, ArkUI_Bool loop)
{
    (void)node;
    (void)loop;
}

void ResetLoopImpl(ArkUINodeHandle node)
{
    (void)node;
}

void SetVerticalImpl(ArkUINodeHandle node, ArkUI_Bool isVertical)
{
    (void)node;
    (void)isVertical;
}

void ResetVerticalImpl(ArkUINodeHandle node)
{
    (void)node;
}

void SetIsIndicatorCustomSizeImpl(ArkUINodeHandle node, ArkUI_Bool isCustomSize)
{
    (void)node;
    (void)isCustomSize;
}
#endif
} // namespace
namespace NodeModifier {
const ArkUIIndicatorComponentModifier* GetIndicatorComponentModifier()
{
    static bool isCurrentUseNewPipeline = Container::IsCurrentUseNewPipeline();
    if (isCurrentUseNewPipeline) {
        CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
        static const ArkUIIndicatorComponentModifier modifier = {
            .setInitialIndex = SetInitialIndex,
            .resetInitialIndex = ResetInitialIndex,
            .setCount = SetCount,
            .resetCount = ResetCount,
            .setOnChange = SetOnChange,
            .resetOnChange = ResetOnChange,
            .setStyle = SetStyle,
            .setJsViewStyle = SetJsViewStyle,
            .resetStyle = ResetStyle,
            .setLoop = SetLoop,
            .resetLoop = ResetLoop,
            .setVertical = SetVertical,
            .resetVertical = ResetVertical,
            .create = Create,
            .setIsIndicatorCustomSize = SetIsIndicatorCustomSize,
        };
        CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line
        return &modifier;
    }
#ifndef CROSS_PLATFORM
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const ArkUIIndicatorComponentModifier modifier = {
        .setInitialIndex = SetInitialIndexImpl,
        .resetInitialIndex = ResetInitialIndexImpl,
        .setCount = SetCountImpl,
        .resetCount = ResetCountImpl,
        .setOnChange = SetOnChangeImpl,
        .resetOnChange = ResetOnChangeImpl,
        .setStyle = SetStyleImpl,
        .setJsViewStyle = SetJsViewStyleImpl,
        .resetStyle = ResetStyleImpl,
        .setLoop = SetLoopImpl,
        .resetLoop = ResetLoopImpl,
        .setVertical = SetVerticalImpl,
        .resetVertical = ResetVerticalImpl,
        .create = CreateImpl,
        .setIsIndicatorCustomSize = SetIsIndicatorCustomSizeImpl,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line
    return &modifier;
#else
    return nullptr;
#endif
};

} // namespace NodeModifier
} // namespace OHOS::Ace::NG
