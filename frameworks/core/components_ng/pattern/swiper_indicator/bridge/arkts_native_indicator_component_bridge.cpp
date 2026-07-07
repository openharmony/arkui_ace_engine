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
#include "core/components_ng/pattern/swiper_indicator/bridge/arkts_native_indicator_component_bridge.h"
#include "bridge/common/utils/utils.h"
#include "core/components_ng/pattern/swiper/bridge/arkts_native_swiper_bridge.h"

#include "jsnapi_expo.h"

#include "bridge/declarative_frontend/engine/jsi/jsi_types.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"
#include "bridge/declarative_frontend/jsview/js_indicator_controller.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/pattern/swiper/swiper_change_event.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/swiper_indicator/indicator_common/indicator_model.h"

namespace OHOS::Ace::NG {

namespace {
constexpr int32_t CALL_ARG_NODE_INDEX = 0;
constexpr int32_t CALL_ARG_VALUE_INDEX = 1;
constexpr int32_t FUNC_PARAM_LENGTH_1 = 1;
constexpr int32_t DIGIT_INDICATOR_FONT_COLOR = 2;
constexpr int32_t DIGIT_INDICATOR_SELECTED_FONT_COLOR = 3;
constexpr int32_t DIGIT_INDICATOR_DIGIT_FONT_SIZE = 4;
constexpr int32_t DIGIT_INDICATOR_DIGIT_FONT_WEIGHT = 5;
constexpr int32_t DIGIT_INDICATOR_SELECTED_DIGIT_FONT_SIZE = 6;
constexpr int32_t DIGIT_INDICATOR_SELECTED_DIGIT_FONT_WEIGHT = 7;
constexpr int32_t DIGIT_INDICATOR_LEFT = 8;
constexpr int32_t DIGIT_INDICATOR_TOP = 9;
constexpr int32_t DIGIT_INDICATOR_RIGHT = 10;
constexpr int32_t DIGIT_INDICATOR_BOTTOM = 11;
constexpr int32_t DOT_INDICATOR_ITEM_WIDTH = 2;
constexpr int32_t DOT_INDICATOR_ITEM_HEIGHT = 3;
constexpr int32_t DOT_INDICATOR_SELECTED_ITEM_WIDTH = 4;
constexpr int32_t DOT_INDICATOR_SELECTED_ITEM_HEIGHT = 5;
constexpr int32_t DOT_INDICATOR_MASK = 6;
constexpr int32_t DOT_INDICATOR_COLOR = 7;
constexpr int32_t DOT_INDICATOR_SELECTED_COLOR = 8;
constexpr int32_t DOT_INDICATOR_LEFT = 9;
constexpr int32_t DOT_INDICATOR_TOP = 10;
constexpr int32_t DOT_INDICATOR_RIGHT = 11;
constexpr int32_t DOT_INDICATOR_BOTTOM = 12;
constexpr int32_t DOT_INDICATOR_MAX_DISPLAY_COUNT = 13;
constexpr int32_t DOT_INDICATOR_SPACE = 14;
constexpr int32_t DEFAULT_INDICATOR_COUNT = 2;
constexpr int32_t DOT_INDICATOR_RESOURCE_ITEM_WIDTH = 0;
constexpr int32_t DOT_INDICATOR_RESOURCE_ITEM_HEIGHT = 1;
constexpr int32_t DOT_INDICATOR_RESOURCE_SELECTED_ITEM_WIDTH = 2;
constexpr int32_t DOT_INDICATOR_RESOURCE_SELECTED_ITEM_HEIGHT = 3;
constexpr int32_t DOT_INDICATOR_RESOURCE_COLOR = 4;
constexpr int32_t DOT_INDICATOR_RESOURCE_SELECTED_COLOR = 5;
constexpr int32_t INDICATOR_RESOURCE_VECTOR_LENGTH = 6;
constexpr int32_t DIGIT_INDICATOR_RESOURCE_FONT_COLOR = 0;
constexpr int32_t DIGIT_INDICATOR_RESOURCE_FONT_SELECTED_COLOR = 1;
constexpr int32_t DIGIT_INDICATOR_RESOURCE_FONT_SIZE = 2;
constexpr int32_t DIGIT_INDICATOR_RESOURCE_SELECTED_FONT_SIZE = 3;
constexpr double DEFAULT_PERCENT_VALUE = 100.0;

std::string GetDimensionUnitString(DimensionUnit unit)
{
    switch (unit) {
        case DimensionUnit::VP:
            return "vp";
        case DimensionUnit::PX:
            return "px";
        case DimensionUnit::FP:
            return "fp";
        case DimensionUnit::CALC:
            return "calc";
        default:
            return "px";
    }
}

std::string GetStringByValueRef(const EcmaVM* vm, const Local<JSValueRef>& jsValue)
{
    std::string result = "-";
    if (jsValue->IsUndefined()) {
        return result;
    }
    CalcDimension calc;
    result = ArkTSUtils::ParseJsDimension(vm, jsValue, calc, DimensionUnit::VP, true)
                 ? (calc.Unit() == DimensionUnit::PERCENT
                           ? (std::to_string(calc.Value() * DEFAULT_PERCENT_VALUE) + "%")
                           : (std::to_string(calc.Value()) + GetDimensionUnitString(calc.Unit())))
                 : "0.0_vp";
    return result;
}

std::string GetIntStringByValueRef(const EcmaVM* vm, const Local<JSValueRef>& jsValue)
{
    std::string result = "-";
    if (jsValue->IsUndefined()) {
        return result;
    }
    int32_t intValue;
    result = ArkTSUtils::ParseJsInteger(vm, jsValue, intValue) ? std::to_string(intValue) : "0";
    return result;
}

std::string ParseSpace(const EcmaVM* vm, const Local<JSValueRef>& jsValue)
{
    std::string result = "-";
    if (jsValue->IsUndefined()) {
        return result;
    }
    CalcDimension calc;
    bool parseOK =  ArkTSUtils::ParseJsLengthMetrics(vm, jsValue, calc);
    calc = (parseOK && !(calc < 0.0_vp) && calc.Unit() != DimensionUnit::PERCENT) ?
        calc : 8.0_vp;
    return calc.ToString();
}

std::string GetDotIndicator(ArkUIRuntimeCallInfo* runtimeCallInfo, EcmaVM* vm,
    std::vector<RefPtr<ResourceObject>>& resObjs, const NodeInfo& nodeInfo)
{
    Local<JSValueRef> itemWidthArg = runtimeCallInfo->GetCallArgRef(DOT_INDICATOR_ITEM_WIDTH);
    Local<JSValueRef> itemHeightArg = runtimeCallInfo->GetCallArgRef(DOT_INDICATOR_ITEM_HEIGHT);
    Local<JSValueRef> selectedItemWidthArg = runtimeCallInfo->GetCallArgRef(DOT_INDICATOR_SELECTED_ITEM_WIDTH);
    Local<JSValueRef> selectedItemHeightArg = runtimeCallInfo->GetCallArgRef(DOT_INDICATOR_SELECTED_ITEM_HEIGHT);
    Local<JSValueRef> maskArg = runtimeCallInfo->GetCallArgRef(DOT_INDICATOR_MASK);
    Local<JSValueRef> colorArg = runtimeCallInfo->GetCallArgRef(DOT_INDICATOR_COLOR);
    Local<JSValueRef> selectedColorArg = runtimeCallInfo->GetCallArgRef(DOT_INDICATOR_SELECTED_COLOR);
    Local<JSValueRef> leftArg = runtimeCallInfo->GetCallArgRef(DOT_INDICATOR_LEFT);
    Local<JSValueRef> topArg = runtimeCallInfo->GetCallArgRef(DOT_INDICATOR_TOP);
    Local<JSValueRef> rightArg = runtimeCallInfo->GetCallArgRef(DOT_INDICATOR_RIGHT);
    Local<JSValueRef> bottomArg = runtimeCallInfo->GetCallArgRef(DOT_INDICATOR_BOTTOM);
    Local<JSValueRef> spaceArg = runtimeCallInfo->GetCallArgRef(DOT_INDICATOR_SPACE);
    CalcDimension calc;

    std::string itemWidth = ArkTSUtils::ParseJsDimension(vm, itemWidthArg, calc, DimensionUnit::VP,
        resObjs.at(DOT_INDICATOR_RESOURCE_ITEM_WIDTH), false)
        ? std::to_string(calc.Value()) + GetDimensionUnitString(calc.Unit()) : "-";
    std::string itemHeight = ArkTSUtils::ParseJsDimension(vm, itemHeightArg, calc, DimensionUnit::VP,
        resObjs.at(DOT_INDICATOR_RESOURCE_ITEM_HEIGHT), false)
        ? std::to_string(calc.Value()) + GetDimensionUnitString(calc.Unit()) : "-";
    std::string selectedItemWidth = ArkTSUtils::ParseJsDimension(vm, selectedItemWidthArg, calc, DimensionUnit::VP,
        resObjs.at(DOT_INDICATOR_RESOURCE_SELECTED_ITEM_WIDTH), false)
        ? std::to_string(calc.Value()) + GetDimensionUnitString(calc.Unit()) : "-";
    std::string selectedItemHeight = ArkTSUtils::ParseJsDimension(vm, selectedItemHeightArg, calc, DimensionUnit::VP,
        resObjs.at(DOT_INDICATOR_RESOURCE_SELECTED_ITEM_HEIGHT), false)
        ? std::to_string(calc.Value()) + GetDimensionUnitString(calc.Unit()) : "-";
    std::string mask = "2";
    if (!maskArg->IsUndefined()) {
        mask = maskArg->ToBoolean(vm)->Value() ? "1" : "0";
    }
    Color color;
    std::string colorStr = ArkTSUtils::ParseJsColorAlpha(vm, colorArg, color,
        resObjs.at(DOT_INDICATOR_RESOURCE_COLOR), nodeInfo) ? std::to_string(color.GetValue()) : "-";
    std::string selectedColor = ArkTSUtils::ParseJsColorAlpha(vm, selectedColorArg, color,
        resObjs.at(DOT_INDICATOR_RESOURCE_SELECTED_COLOR), nodeInfo) ? std::to_string(color.GetValue()) : "-";
    std::string left = GetStringByValueRef(vm, leftArg);
    std::string top = GetStringByValueRef(vm, topArg);
    std::string right = GetStringByValueRef(vm, rightArg);
    std::string bottom = GetStringByValueRef(vm, bottomArg);
    std::string space = ParseSpace(vm, spaceArg);
    Local<JSValueRef> maxDisplayCountArg = runtimeCallInfo->GetCallArgRef(DOT_INDICATOR_MAX_DISPLAY_COUNT);
    auto maxDisplayCount = GetIntStringByValueRef(vm, maxDisplayCountArg);
    std::string indicatorStr = itemWidth + "|" + itemHeight + "|" + selectedItemWidth + "|" + selectedItemHeight + "|" +
                               mask + "|" + colorStr + "|" + selectedColor + "|" + left + "|" + top + "|" + right +
                               "|" + bottom + "|" + maxDisplayCount + "|" + space;
    return indicatorStr;
}

std::string GetDigitIndicator(ArkUIRuntimeCallInfo* runtimeCallInfo, EcmaVM* vm,
    std::vector<RefPtr<ResourceObject>>& resObjs, const NodeInfo& nodeInfo)
{
    Local<JSValueRef> fontColorArg = runtimeCallInfo->GetCallArgRef(DIGIT_INDICATOR_FONT_COLOR);
    Local<JSValueRef> selectedFontColorArg = runtimeCallInfo->GetCallArgRef(DIGIT_INDICATOR_SELECTED_FONT_COLOR);
    Local<JSValueRef> digitFontSizeArg = runtimeCallInfo->GetCallArgRef(DIGIT_INDICATOR_DIGIT_FONT_SIZE);
    Local<JSValueRef> digitFontWeightArg = runtimeCallInfo->GetCallArgRef(DIGIT_INDICATOR_DIGIT_FONT_WEIGHT);
    Local<JSValueRef> selectedDigitFontSizeArg =
        runtimeCallInfo->GetCallArgRef(DIGIT_INDICATOR_SELECTED_DIGIT_FONT_SIZE);
    Local<JSValueRef> selectedDigitFontWeightArg =
        runtimeCallInfo->GetCallArgRef(DIGIT_INDICATOR_SELECTED_DIGIT_FONT_WEIGHT);
    Local<JSValueRef> leftArg = runtimeCallInfo->GetCallArgRef(DIGIT_INDICATOR_LEFT);
    Local<JSValueRef> topArg = runtimeCallInfo->GetCallArgRef(DIGIT_INDICATOR_TOP);
    Local<JSValueRef> rightArg = runtimeCallInfo->GetCallArgRef(DIGIT_INDICATOR_RIGHT);
    Local<JSValueRef> bottomArg = runtimeCallInfo->GetCallArgRef(DIGIT_INDICATOR_BOTTOM);
    Color color;
    CalcDimension calc;
    std::string fontColor = ArkTSUtils::ParseJsColorAlpha(vm, fontColorArg, color,
        resObjs.at(DIGIT_INDICATOR_RESOURCE_FONT_COLOR), nodeInfo) ? std::to_string(color.GetValue()) : "-";
    std::string selectedFontColor = ArkTSUtils::ParseJsColorAlpha(vm, selectedFontColorArg, color,
        resObjs.at(DIGIT_INDICATOR_RESOURCE_FONT_SELECTED_COLOR), nodeInfo) ? std::to_string(color.GetValue()) : "-";
    std::string digitFontSize = ArkTSUtils::ParseJsDimension(vm, digitFontSizeArg, calc, DimensionUnit::FP,
        resObjs.at(DIGIT_INDICATOR_RESOURCE_FONT_SIZE), false)
        ? std::to_string(calc.Value()) + GetDimensionUnitString(calc.Unit()) : "-";
    std::string digitFontWeight = digitFontWeightArg->ToString(vm)->ToString(vm);
    std::string selectedDigitFontSize = ArkTSUtils::ParseJsDimension(vm, selectedDigitFontSizeArg, calc,
        DimensionUnit::FP, resObjs.at(DIGIT_INDICATOR_RESOURCE_SELECTED_FONT_SIZE), false)
        ? std::to_string(calc.Value()) + GetDimensionUnitString(calc.Unit()) : "-";

    std::string selectedDigitFontWeight = selectedDigitFontWeightArg->ToString(vm)->ToString(vm);
    std::string left = GetStringByValueRef(vm, leftArg);
    std::string top = GetStringByValueRef(vm, topArg);
    std::string right = GetStringByValueRef(vm, rightArg);
    std::string bottom = GetStringByValueRef(vm, bottomArg);
    std::string indicatorStr = fontColor + "|" + selectedFontColor + "|" + digitFontSize + "|" + digitFontWeight + "|" +
                               selectedDigitFontSize + "|" + selectedDigitFontWeight + "|" + left + "|" + top + "|" +
                               right + "|" + bottom;
    return indicatorStr;
}

Local<JSValueRef> GetNamedProperty(EcmaVM* vm, const Local<JSValueRef>& objectArg, const char* name)
{
    CHECK_NULL_RETURN(
        !objectArg.IsNull() && !objectArg->IsUndefined() && objectArg->IsObject(vm), panda::JSValueRef::Undefined(vm));
    return objectArg->ToObject(vm)->Get(vm, panda::StringRef::NewFromUtf8(vm, name));
}

std::optional<Dimension> ParseIndicatorDimension(EcmaVM* vm, const Local<JSValueRef>& value)
{
    std::optional<Dimension> indicatorDimension;
    if (value.IsNull() || value->IsUndefined()) {
        return indicatorDimension;
    }
    CalcDimension dimPosition;
    auto parseOk = ArkTSUtils::ParseJsDimensionVpNG(vm, value, dimPosition);
    indicatorDimension = parseOk && dimPosition.ConvertToPx() >= 0.0f ? dimPosition : 0.0_vp;
    return indicatorDimension;
}

void SetJsViewDotIndicatorInfo(
    EcmaVM* vm, const Local<JSValueRef>& obj, SwiperParameters& swiperParameters, ArkUINodeHandle nativeNode)
{
    auto* frameNode = reinterpret_cast<NG::FrameNode*>(nativeNode);
    CHECK_NULL_VOID(frameNode);
    auto pipelineContext = frameNode->GetContext();
    CHECK_NULL_VOID(pipelineContext);
    auto swiperIndicatorTheme = pipelineContext->GetTheme<SwiperIndicatorTheme>();
    CHECK_NULL_VOID(swiperIndicatorTheme);
    auto maskValue = GetNamedProperty(vm, obj, "maskValue");
    auto colorValue = GetNamedProperty(vm, obj, "colorValue");
    auto selectedColorValue = GetNamedProperty(vm, obj, "selectedColorValue");
    auto maxDisplayCountVal = GetNamedProperty(vm, obj, "maxDisplayCountValue");
    auto spaceValue = GetNamedProperty(vm, obj, "spaceValue");
    if (!maskValue.IsNull() && !maskValue->IsUndefined() && maskValue->IsBoolean()) {
        swiperParameters.maskValue = maskValue->ToBoolean(vm)->Value();
    }
    Color colorVal;
    RefPtr<ResourceObject> resColorObj;
    RefPtr<ResourceObject> resSelectedColorObj;
    auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(nativeNode);
    auto parseOk = !colorValue.IsNull() && !colorValue->IsUndefined() &&
                   ArkTSUtils::ParseJsColorAlpha(vm, colorValue, colorVal, resColorObj, nodeInfo);
    swiperParameters.colorVal =
        parseOk ? (swiperParameters.parametersByUser.insert("colorVal"), colorVal) : swiperIndicatorTheme->GetColor();
    parseOk = !selectedColorValue.IsNull() && !selectedColorValue->IsUndefined() &&
              ArkTSUtils::ParseJsColorAlpha(vm, selectedColorValue, colorVal, resSelectedColorObj, nodeInfo);
    swiperParameters.selectedColorVal = parseOk
                                            ? (swiperParameters.parametersByUser.insert("selectedColorVal"), colorVal)
                                            : swiperIndicatorTheme->GetSelectedColor();
    if (SystemProperties::ConfigChangePerform()) {
        swiperParameters.resourceColorValueObject = resColorObj;
        swiperParameters.resourceSelectedColorValueObject = resSelectedColorObj;
    }
    auto defaultSpace = swiperIndicatorTheme->GetIndicatorDotItemSpace();
    CalcDimension dimSpace;
    auto parseSpaceOk = !spaceValue.IsNull() && !spaceValue->IsUndefined() &&
                        ArkTSUtils::ParseLengthMetricsToDimensionForTabs(vm, spaceValue, dimSpace) &&
                        (dimSpace.Unit() != DimensionUnit::PERCENT);
    swiperParameters.dimSpace = (parseSpaceOk && !(dimSpace < 0.0_vp)) ? dimSpace : defaultSpace;
    if (maxDisplayCountVal.IsNull() || maxDisplayCountVal->IsUndefined()) {
        return;
    }
    uint32_t result = 0;
    auto setMaxDisplayCountVal = !maxDisplayCountVal.IsNull() && !maxDisplayCountVal->IsUndefined() &&
                                 ArkTSUtils::ParseJsInteger(vm, maxDisplayCountVal, result);
    swiperParameters.maxDisplayCountVal = setMaxDisplayCountVal && result > 0 ? result : 0;
}

SwiperParameters GetJsViewDotIndicatorInfo(EcmaVM* vm, const Local<JSValueRef>& obj, ArkUINodeHandle nativeNode)
{
    auto leftValue = GetNamedProperty(vm, obj, "leftValue");
    auto topValue = GetNamedProperty(vm, obj, "topValue");
    auto rightValue = GetNamedProperty(vm, obj, "rightValue");
    auto bottomValue = GetNamedProperty(vm, obj, "bottomValue");
    auto startValue = GetNamedProperty(vm, obj, "startValue");
    auto endValue = GetNamedProperty(vm, obj, "endValue");
    auto itemWidthValue = GetNamedProperty(vm, obj, "itemWidthValue");
    auto itemHeightValue = GetNamedProperty(vm, obj, "itemHeightValue");
    auto selectedItemWidthValue = GetNamedProperty(vm, obj, "selectedItemWidthValue");
    auto selectedItemHeightValue = GetNamedProperty(vm, obj, "selectedItemHeightValue");
    auto* frameNode = reinterpret_cast<NG::FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, SwiperParameters());
    auto pipelineContext = frameNode->GetContext();
    CHECK_NULL_RETURN(pipelineContext, SwiperParameters());
    auto swiperIndicatorTheme = pipelineContext->GetTheme<SwiperIndicatorTheme>();
    CHECK_NULL_RETURN(swiperIndicatorTheme, SwiperParameters());
    SwiperParameters swiperParameters;
    swiperParameters.dimLeft = ParseIndicatorDimension(vm, leftValue);
    swiperParameters.dimTop = ParseIndicatorDimension(vm, topValue);
    swiperParameters.dimRight = ParseIndicatorDimension(vm, rightValue);
    swiperParameters.dimBottom = ParseIndicatorDimension(vm, bottomValue);
    CalcDimension dimStart;
    CalcDimension dimEnd;
    std::optional<Dimension> indicatorDimension;
    swiperParameters.dimStart = !startValue.IsNull() && !startValue->IsUndefined() &&
                                        ArkTSUtils::ParseLengthMetricsToDimensionForTabs(vm, startValue, dimStart)
                                    ? dimStart
                                    : indicatorDimension;
    swiperParameters.dimEnd = !endValue.IsNull() && !endValue->IsUndefined() &&
                                      ArkTSUtils::ParseLengthMetricsToDimensionForTabs(vm, endValue, dimEnd)
                                  ? dimEnd
                                  : indicatorDimension;

    CalcDimension dimPosition;
    RefPtr<ResourceObject> resItemWidthObj;
    RefPtr<ResourceObject> resItemHeightObj;
    RefPtr<ResourceObject> resSelectedItemWidthObj;
    RefPtr<ResourceObject> resSelectedItemHeightObj;
    bool parseItemWOk = !itemWidthValue.IsNull() && !itemWidthValue->IsUndefined() &&
                        ArkTSUtils::ParseJsDimensionVpNG(vm, itemWidthValue, dimPosition, resItemWidthObj) &&
                        (dimPosition.Unit() != DimensionUnit::PERCENT);
    auto defaultSize = swiperIndicatorTheme->GetSize();
    if (parseItemWOk && dimPosition > 0.0_vp) {
        swiperParameters.parametersByUser.insert("itemWidth");
        swiperParameters.itemWidth = dimPosition;
    } else {
        swiperParameters.itemWidth = defaultSize;
    }
    bool parseItemHOk = !itemHeightValue.IsNull() && !itemHeightValue->IsUndefined() &&
                        ArkTSUtils::ParseJsDimensionVpNG(vm, itemHeightValue, dimPosition, resItemHeightObj) &&
                        (dimPosition.Unit() != DimensionUnit::PERCENT);
    if (parseItemHOk && dimPosition > 0.0_vp) {
        swiperParameters.parametersByUser.insert("itemHeight");
        swiperParameters.itemHeight = dimPosition;
    } else {
        swiperParameters.itemHeight = defaultSize;
    }
    bool parseSelectedItemWOk =
        !selectedItemWidthValue.IsNull() && !selectedItemWidthValue->IsUndefined() &&
        ArkTSUtils::ParseJsDimensionVpNG(vm, selectedItemWidthValue, dimPosition, resSelectedItemWidthObj) &&
        (dimPosition.Unit() != DimensionUnit::PERCENT);
    if (parseSelectedItemWOk && dimPosition > 0.0_vp) {
        swiperParameters.parametersByUser.insert("selectedItemWidth");
        swiperParameters.selectedItemWidth = dimPosition;
    } else {
        swiperParameters.selectedItemWidth = defaultSize;
    }
    bool parseSelectedItemHOk =
        !selectedItemHeightValue.IsNull() && !selectedItemHeightValue->IsUndefined() &&
        ArkTSUtils::ParseJsDimensionVpNG(vm, selectedItemHeightValue, dimPosition, resSelectedItemHeightObj) &&
        (dimPosition.Unit() != DimensionUnit::PERCENT);
    if (parseSelectedItemHOk && dimPosition > 0.0_vp) {
        swiperParameters.parametersByUser.insert("selectedItemHeight");
        swiperParameters.selectedItemHeight = dimPosition;
    } else {
        swiperParameters.selectedItemHeight = defaultSize;
    }
    if (SystemProperties::ConfigChangePerform()) {
        swiperParameters.resourceItemWidthValueObject = resItemWidthObj;
        swiperParameters.resourceItemHeightValueObject = resItemHeightObj;
        swiperParameters.resourceSelectedItemWidthValueObject = resSelectedItemWidthObj;
        swiperParameters.resourceSelectedItemHeightValueObject = resSelectedItemHeightObj;
    }
    GetArkUINodeModifiers()->getIndicatorComponentModifier()->setIsIndicatorCustomSize(
        nativeNode, parseSelectedItemWOk || parseSelectedItemHOk || parseItemWOk || parseItemHOk);
    SetJsViewDotIndicatorInfo(vm, obj, swiperParameters, nativeNode);
    return swiperParameters;
}

void GetFontContent(EcmaVM* vm, ArkUINodeHandle nativeNode, const Local<JSValueRef>& font, bool isSelected,
    SwiperDigitalParameters& digitalParameters)
{
    Local<JSValueRef> size;
    Local<JSValueRef> weight;
    if (!font.IsNull() && !font->IsUndefined() && font->IsObject(vm)) {
        auto obj = font->ToObject(vm);
        size = obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "size"));
        weight = obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "weight"));
    }

    auto* frameNode = reinterpret_cast<NG::FrameNode*>(nativeNode);
    CHECK_NULL_VOID(frameNode);
    auto pipelineContext = frameNode->GetContext();
    CHECK_NULL_VOID(pipelineContext);
    auto swiperIndicatorTheme = pipelineContext->GetTheme<SwiperIndicatorTheme>();
    CHECK_NULL_VOID(swiperIndicatorTheme);
    CalcDimension fontSize;
    RefPtr<ResourceObject> resObj;
    if (!size.IsNull() && !size->IsUndefined() && ArkTSUtils::ParseJsDimensionFp(vm, size, fontSize, resObj)) {
        if (LessOrEqual(fontSize.Value(), 0.0) || LessOrEqual(size->ToNumber(vm)->Value(), 0.0) ||
            fontSize.Unit() == DimensionUnit::PERCENT) {
            fontSize = swiperIndicatorTheme->GetDigitalIndicatorTextStyle().GetFontSize();
        }
    } else {
        fontSize = swiperIndicatorTheme->GetDigitalIndicatorTextStyle().GetFontSize();
    }
    if (SystemProperties::ConfigChangePerform()) {
        if (isSelected) {
            digitalParameters.resourceSelectedFontSizeValueObject = resObj;
        } else {
            digitalParameters.resourceFontSizeValueObject = resObj;
        }
    }
    if (isSelected) {
        digitalParameters.selectedFontSize = fontSize;
    } else {
        digitalParameters.fontSize = fontSize;
    }

    if (!weight.IsNull() && !weight->IsUndefined()) {
        std::string weightValue;
        if (weight->IsNumber()) {
            weightValue = std::to_string(weight->Int32Value(vm));
        } else {
            weightValue = weight->ToString(vm)->ToString(vm);
        }
        if (isSelected) {
            digitalParameters.selectedFontWeight = Framework::ConvertStrToFontWeight(weightValue);
        } else {
            digitalParameters.fontWeight = Framework::ConvertStrToFontWeight(weightValue);
        }
    } else {
        if (isSelected) {
            digitalParameters.selectedFontWeight = swiperIndicatorTheme->GetDigitalIndicatorTextStyle().GetFontWeight();
        } else {
            digitalParameters.fontWeight = swiperIndicatorTheme->GetDigitalIndicatorTextStyle().GetFontWeight();
        }
    }
}

SwiperDigitalParameters GetJsViewDigitIndicatorInfo(EcmaVM* vm, const Local<ObjectRef>& obj, ArkUINodeHandle nativeNode)
{
    auto dotLeftValue = obj->Get(vm, "leftValue");
    auto dotTopValue = obj->Get(vm, "topValue");
    auto dotRightValue = obj->Get(vm, "rightValue");
    auto dotBottomValue = obj->Get(vm, "bottomValue");
    auto fontColorValue = obj->Get(vm, "fontColorValue");
    auto selectedFontColorValue = obj->Get(vm, "selectedFontColorValue");
    auto digitFontValue = obj->Get(vm, "digitFontValue");
    auto selectedDigitFontValue = obj->Get(vm, "selectedDigitFontValue");
    auto* frameNode = reinterpret_cast<NG::FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, SwiperDigitalParameters());
    auto pipelineContext = frameNode->GetContext();
    CHECK_NULL_RETURN(pipelineContext, SwiperDigitalParameters());
    auto swiperIndicatorTheme = pipelineContext->GetTheme<SwiperIndicatorTheme>();
    CHECK_NULL_RETURN(swiperIndicatorTheme, SwiperDigitalParameters());
    SwiperDigitalParameters digitalParameters;
    digitalParameters.dimLeft = ParseIndicatorDimension(vm, dotLeftValue);
    digitalParameters.dimTop = ParseIndicatorDimension(vm, dotTopValue);
    digitalParameters.dimRight = ParseIndicatorDimension(vm, dotRightValue);
    digitalParameters.dimBottom = ParseIndicatorDimension(vm, dotBottomValue);
    Color fontColor;
    RefPtr<ResourceObject> resFontColorObj;
    RefPtr<ResourceObject> resSelectedFontColorObj;
    auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(nativeNode);
    auto parseOk = !fontColorValue.IsNull() && !fontColorValue->IsUndefined() &&
                   ArkTSUtils::ParseJsColorAlpha(vm, fontColorValue, fontColor, resFontColorObj, nodeInfo);
    digitalParameters.fontColor = parseOk ? (digitalParameters.parametersByUser.insert("fontColor"), fontColor)
                                          : swiperIndicatorTheme->GetDigitalIndicatorTextStyle().GetTextColor();
    parseOk = !selectedFontColorValue.IsNull() && !selectedFontColorValue->IsUndefined() &&
              ArkTSUtils::ParseJsColorAlpha(vm, selectedFontColorValue, fontColor, resSelectedFontColorObj, nodeInfo);
    digitalParameters.selectedFontColor =
        parseOk ? (digitalParameters.parametersByUser.insert("selectedFontColor"), fontColor)
                : swiperIndicatorTheme->GetDigitalIndicatorTextStyle().GetTextColor();
    if (SystemProperties::ConfigChangePerform()) {
        digitalParameters.resourceFontColorValueObject = resFontColorObj;
        digitalParameters.resourceSelectedFontColorValueObject = resSelectedFontColorObj;
    }
    if (!digitFontValue.IsNull() && !digitFontValue->IsUndefined() && digitFontValue->IsObject(vm)) {
        GetFontContent(vm, nativeNode, digitFontValue, false, digitalParameters);
    }
    if (!selectedDigitFontValue.IsNull() && !selectedDigitFontValue->IsUndefined() &&
        selectedDigitFontValue->IsObject(vm)) {
        GetFontContent(vm, nativeNode, selectedDigitFontValue, true, digitalParameters);
    }
    return digitalParameters;
}
} // namespace

void IndicatorComponentBridge::RegisterIndicatorComponentAttributes(Local<panda::ObjectRef> object, EcmaVM* vm)
{
    const char* functionNames[] = { "create", "setInitialIndex", "resetInitialIndex", "setCount", "resetCount",
        "setStyle", "resetStyle", "setLoop", "resetLoop", "setVertical", "resetVertical", "setOnChange",
        "resetOnChange" };

    Local<panda::JSValueRef> funcValues[] = {
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), IndicatorComponentBridge::Create),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), IndicatorComponentBridge::SetInitialIndex),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), IndicatorComponentBridge::ResetInitialIndex),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), IndicatorComponentBridge::SetCount),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), IndicatorComponentBridge::ResetCount),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), IndicatorComponentBridge::SetStyle),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), IndicatorComponentBridge::ResetStyle),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), IndicatorComponentBridge::SetLoop),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), IndicatorComponentBridge::ResetLoop),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), IndicatorComponentBridge::SetVertical),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), IndicatorComponentBridge::ResetVertical),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), IndicatorComponentBridge::SetOnChange),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), IndicatorComponentBridge::ResetOnChange),
    };
    auto indicatorComponent = panda::ObjectRef::NewWithNamedProperties(
        vm, sizeof(functionNames) / sizeof(functionNames[0]), functionNames, funcValues);
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "indicatorComponent"), indicatorComponent);
}

ArkUINativeModuleValue IndicatorComponentBridge::Create(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    auto indicatorController = AceType::Claim(
        reinterpret_cast<AceType*>(GetArkUINodeModifiers()->getIndicatorComponentModifier()->create()));
    int32_t controllerIndex = 0;
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_NODE_INDEX);
    if (firstArg->IsBoolean() && firstArg->ToBoolean(vm)->Value()) {
        controllerIndex = CALL_ARG_VALUE_INDEX;
    }
    Local<JSValueRef> controllerArg = runtimeCallInfo->GetCallArgRef(controllerIndex);
    if (!controllerArg.IsNull() && !controllerArg->IsUndefined() && controllerArg->IsObject(vm)) {
        auto* jsController = static_cast<Framework::JSIndicatorController*>(
            controllerArg->ToObject(vm)->GetNativePointerField(vm, 0));
        if (jsController) {
            jsController->SetInstanceId(Container::CurrentId());
            auto indicatorNode = AceType::Claim(ViewStackProcessor::GetInstance()->GetMainFrameNode());
            jsController->SetControllerHandle(indicatorController, indicatorNode);
        }
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue IndicatorComponentBridge::SetInitialIndex(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_NODE_INDEX);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, nodeArg, vm), true, panda::JSValueRef::Undefined(vm));
    bool isJsView = ArkTSUtils::IsJsView(nodeArg, vm);
    Local<JSValueRef> valueArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_VALUE_INDEX);
    if (!valueArg.IsNull() && !valueArg->IsUndefined() && valueArg->IsNumber()) {
        int32_t index = valueArg->Int32Value(vm);
        if (isJsView) {
            index = std::max(0, index);
        }
        GetArkUINodeModifiers()->getIndicatorComponentModifier()->setInitialIndex(nativeNode, index);
    } else {
        GetArkUINodeModifiers()->getIndicatorComponentModifier()->resetInitialIndex(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue IndicatorComponentBridge::ResetInitialIndex(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_NODE_INDEX);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getIndicatorComponentModifier()->resetInitialIndex(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue IndicatorComponentBridge::SetCount(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_NODE_INDEX);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, nodeArg, vm), true, panda::JSValueRef::Undefined(vm));

    Local<JSValueRef> valueArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_VALUE_INDEX);
    if (!valueArg.IsNull() && !valueArg->IsUndefined() && valueArg->IsNumber()) {
        int32_t count = std::max(DEFAULT_INDICATOR_COUNT, valueArg->Int32Value(vm));
        GetArkUINodeModifiers()->getIndicatorComponentModifier()->setCount(nativeNode, count);
    } else {
        GetArkUINodeModifiers()->getIndicatorComponentModifier()->resetCount(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue IndicatorComponentBridge::ResetCount(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getIndicatorComponentModifier()->resetCount(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue IndicatorComponentBridge::SetOnChange(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_NODE_INDEX);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, nodeArg, vm), true, panda::JSValueRef::Undefined(vm));
    bool isJsView = ArkTSUtils::IsJsView(nodeArg, vm);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_VALUE_INDEX);
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    if (callbackArg.IsNull() || callbackArg->IsUndefined() || !callbackArg->IsFunction(vm)) {
        if (!isJsView) {
            GetArkUINodeModifiers()->getIndicatorComponentModifier()->resetOnChange(nativeNode);
        }
        return panda::JSValueRef::Undefined(vm);
    }
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<void(const BaseEventInfo* info)> callback = [isJsView, frameWeakNode = AceType::WeakClaim(frameNode),
                                                                  func = panda::CopyableGlobal(vm, func)](
                                                                  const BaseEventInfo* info) {
        auto vm = func.GetEcmaVM();
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        const auto* swiperInfo = TypeInfoHelper::DynamicCast<SwiperChangeEvent>(info);
        if (!swiperInfo) {
            TAG_LOGW(AceLogTag::ACE_INDICATOR, "IndicatorComponent onChange callback execute failed.");
            return;
        }
        PipelineContext::SetCallBackNode(frameWeakNode);
        panda::Local<panda::JSValueRef> params[FUNC_PARAM_LENGTH_1] = { panda::NumberRef::New(
            vm, swiperInfo->GetIndex()) };
        auto result = func->Call(vm, func.ToLocal(), params, FUNC_PARAM_LENGTH_1);
        if (isJsView) {
            ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
        }
    };
    GetArkUINodeModifiers()->getIndicatorComponentModifier()->setOnChange(
        nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue IndicatorComponentBridge::ResetOnChange(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_NODE_INDEX);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getIndicatorComponentModifier()->resetOnChange(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue IndicatorComponentBridge::SetStyle(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_NODE_INDEX);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, nodeArg, vm), true, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> valueArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_VALUE_INDEX);
    std::vector<RefPtr<ResourceObject>> resObjs;
    resObjs.resize(INDICATOR_RESOURCE_VECTOR_LENGTH);
    std::string indicatorStr = "";
    auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(nativeNode);
    bool isJsView = ArkTSUtils::IsJsView(nodeArg, vm);
    if (isJsView) {
        if (!valueArg.IsNull() && !valueArg->IsUndefined() && valueArg->IsObject(vm)) {
            auto typeArg = GetNamedProperty(vm, valueArg, "type");
            if (!typeArg.IsNull() && !typeArg->IsUndefined() && typeArg->IsString(vm) &&
                typeArg->ToString(vm)->ToString(vm) == "DigitIndicator") {
                SwiperDigitalParameters digitalParameters = GetJsViewDigitIndicatorInfo(vm, valueArg, nativeNode);
                GetArkUINodeModifiers()->getIndicatorComponentModifier()->setJsViewStyle(
                    nativeNode, false, &digitalParameters);
            } else {
                SwiperParameters swiperParameters = GetJsViewDotIndicatorInfo(vm, valueArg, nativeNode);
                ParseIndicatorIconList(vm, runtimeCallInfo, swiperParameters.indicatorIconMap);
                GetArkUINodeModifiers()->getIndicatorComponentModifier()->setJsViewStyle(
                    nativeNode, true, &swiperParameters);
            }
        } else {
            Local<JSValueRef> emptyObject = panda::ObjectRef::New(vm);
            SwiperParameters swiperParameters = GetJsViewDotIndicatorInfo(vm, emptyObject, nativeNode);
            ParseIndicatorIconList(vm, runtimeCallInfo, swiperParameters.indicatorIconMap);
            GetArkUINodeModifiers()->getIndicatorComponentModifier()->setJsViewStyle(
                nativeNode, true, &swiperParameters);
        }
        return panda::JSValueRef::Undefined(vm);
    }
    std::string type = valueArg->ToString(vm)->ToString(vm);
    if (type == "ArkDigitIndicator") {
        indicatorStr = type + "|" + GetDigitIndicator(runtimeCallInfo, vm, resObjs, nodeInfo);
    } else {
        indicatorStr = type + "|" + GetDotIndicator(runtimeCallInfo, vm, resObjs, nodeInfo);
    }
    GetArkUINodeModifiers()->getIndicatorComponentModifier()->setStyle(nativeNode, indicatorStr.c_str(),
        static_cast<void*>(&resObjs));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue IndicatorComponentBridge::ResetStyle(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_NODE_INDEX);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getIndicatorComponentModifier()->resetStyle(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue IndicatorComponentBridge::SetLoop(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_NODE_INDEX);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, nodeArg, vm), true, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> valueArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_VALUE_INDEX);
    if (!valueArg.IsNull() && !valueArg->IsUndefined() && valueArg->IsBoolean()) {
        bool loop = valueArg->ToBoolean(vm)->Value();
        GetArkUINodeModifiers()->getIndicatorComponentModifier()->setLoop(nativeNode, loop);
    } else {
        GetArkUINodeModifiers()->getIndicatorComponentModifier()->resetLoop(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue IndicatorComponentBridge::ResetLoop(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_NODE_INDEX);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getIndicatorComponentModifier()->resetLoop(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue IndicatorComponentBridge::SetVertical(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_NODE_INDEX);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, nodeArg, vm), true, panda::JSValueRef::Undefined(vm));

    Local<JSValueRef> valueArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_VALUE_INDEX);
    if (!valueArg.IsNull() && !valueArg->IsUndefined() && valueArg->IsBoolean()) {
        bool isVertical = valueArg->ToBoolean(vm)->Value();
        GetArkUINodeModifiers()->getIndicatorComponentModifier()->setVertical(nativeNode, isVertical);
    } else {
        GetArkUINodeModifiers()->getIndicatorComponentModifier()->resetVertical(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue IndicatorComponentBridge::ResetVertical(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_NODE_INDEX);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getIndicatorComponentModifier()->resetVertical(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

} // namespace OHOS::Ace::NG
