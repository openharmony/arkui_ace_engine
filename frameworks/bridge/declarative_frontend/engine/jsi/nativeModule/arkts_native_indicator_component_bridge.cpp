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
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_indicator_component_bridge.h"

#include "jsnapi_expo.h"

#include "bridge/declarative_frontend/engine/jsi/jsi_types.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"
#include "core/components/common/layout/constants.h"

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

std::string GetDotIndicator(ArkUIRuntimeCallInfo* runtimeCallInfo, EcmaVM* vm)
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
    CalcDimension calc;

    std::string itemWidth = ArkTSUtils::ParseJsDimension(vm, itemWidthArg, calc, DimensionUnit::VP, false)
                                ? std::to_string(calc.Value()) + GetDimensionUnitString(calc.Unit())
                                : "-";
    std::string itemHeight = ArkTSUtils::ParseJsDimension(vm, itemHeightArg, calc, DimensionUnit::VP, false)
                                 ? std::to_string(calc.Value()) + GetDimensionUnitString(calc.Unit())
                                 : "-";
    std::string selectedItemWidth =
        ArkTSUtils::ParseJsDimension(vm, selectedItemWidthArg, calc, DimensionUnit::VP, false)
            ? std::to_string(calc.Value()) + GetDimensionUnitString(calc.Unit())
            : "-";
    std::string selectedItemHeight =
        ArkTSUtils::ParseJsDimension(vm, selectedItemHeightArg, calc, DimensionUnit::VP, false)
            ? std::to_string(calc.Value()) + GetDimensionUnitString(calc.Unit())
            : "-";
    std::string mask = "2";
    if (!maskArg->IsUndefined()) {
        mask = maskArg->ToBoolean(vm)->Value() ? "1" : "0";
    }
    Color color;
    std::string colorStr = ArkTSUtils::ParseJsColorAlpha(vm, colorArg, color) ? std::to_string(color.GetValue()) : "-";
    std::string selectedColor =
        ArkTSUtils::ParseJsColorAlpha(vm, selectedColorArg, color) ? std::to_string(color.GetValue()) : "-";
    std::string left = GetStringByValueRef(vm, leftArg);
    std::string top = GetStringByValueRef(vm, topArg);
    std::string right = GetStringByValueRef(vm, rightArg);
    std::string bottom = GetStringByValueRef(vm, bottomArg);
    Local<JSValueRef> maxDisplayCountArg = runtimeCallInfo->GetCallArgRef(DOT_INDICATOR_MAX_DISPLAY_COUNT);
    auto maxDisplayCount = GetIntStringByValueRef(vm, maxDisplayCountArg);
    std::string indicatorStr = itemWidth + "|" + itemHeight + "|" + selectedItemWidth + "|" + selectedItemHeight + "|" +
                               mask + "|" + colorStr + "|" + selectedColor + "|" + left + "|" + top + "|" + right +
                               "|" + bottom + "|" + maxDisplayCount;
    return indicatorStr;
}

std::string GetDigitIndicator(ArkUIRuntimeCallInfo* runtimeCallInfo, EcmaVM* vm)
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
    std::string fontColor =
        ArkTSUtils::ParseJsColorAlpha(vm, fontColorArg, color) ? std::to_string(color.GetValue()) : "-";
    std::string selectedFontColor =
        ArkTSUtils::ParseJsColorAlpha(vm, selectedFontColorArg, color) ? std::to_string(color.GetValue()) : "-";
    std::string digitFontSize = ArkTSUtils::ParseJsDimension(vm, digitFontSizeArg, calc, DimensionUnit::FP, false)
                                    ? std::to_string(calc.Value()) + GetDimensionUnitString(calc.Unit())
                                    : "-";
    std::string digitFontWeight = digitFontWeightArg->ToString(vm)->ToString(vm);
    std::string selectedDigitFontSize =
        ArkTSUtils::ParseJsDimension(vm, selectedDigitFontSizeArg, calc, DimensionUnit::FP, false)
            ? std::to_string(calc.Value()) + GetDimensionUnitString(calc.Unit())
            : "-";
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
} // namespace

ArkUINativeModuleValue IndicatorComponentBridge::SetInitialIndex(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_NODE_INDEX);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    Local<JSValueRef> valueArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_VALUE_INDEX);
    if (valueArg->IsNumber()) {
        int32_t index = valueArg->Int32Value(vm);
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
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    Local<JSValueRef> valueArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_VALUE_INDEX);
    if (valueArg->IsNumber()) {
        int32_t count = valueArg->Int32Value(vm);
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
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_VALUE_INDEX);
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        GetArkUINodeModifiers()->getIndicatorComponentModifier()->resetOnChange(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<void(const BaseEventInfo* info)> callback = [vm, frameNode, func = panda::CopyableGlobal(vm, func)](
                                                                  const BaseEventInfo* info) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        const auto* swiperInfo = TypeInfoHelper::DynamicCast<SwiperChangeEvent>(info);
        if (!swiperInfo) {
            TAG_LOGW(AceLogTag::ACE_INDICATOR, "IndicatorComponent onChange callback execute failed.");
            return;
        }
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
        panda::Local<panda::JSValueRef> params[FUNC_PARAM_LENGTH_1] = { panda::NumberRef::New(
            vm, swiperInfo->GetIndex()) };
        func->Call(vm, func.ToLocal(), params, FUNC_PARAM_LENGTH_1);
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
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    Local<JSValueRef> valueArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_VALUE_INDEX);

    std::string type = valueArg->ToString(vm)->ToString(vm);
    std::string indicatorStr = "";
    if (type == "ArkDigitIndicator") {
        indicatorStr = type + "|" + GetDigitIndicator(runtimeCallInfo, vm);
    } else {
        indicatorStr = type + "|" + GetDotIndicator(runtimeCallInfo, vm);
    }
    GetArkUINodeModifiers()->getIndicatorComponentModifier()->setStyle(nativeNode, indicatorStr.c_str());
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
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    Local<JSValueRef> valueArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_VALUE_INDEX);
    if (valueArg->IsBoolean()) {
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
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    Local<JSValueRef> valueArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_VALUE_INDEX);
    if (valueArg->IsBoolean()) {
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
