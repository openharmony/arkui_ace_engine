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
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_swiper_bridge.h"

#include <string>

#include "base/geometry/calc_dimension.h"
#include "base/geometry/dimension.h"
#include "base/log/log_wrapper.h"
#include "base/utils/utils.h"
#include "base/log/ace_scoring_log.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"
#include "bridge/declarative_frontend/engine/functions/js_swiper_function.h"
#include "bridge/declarative_frontend/jsview/js_indicator.h"
#include "bridge/declarative_frontend/jsview/js_swiper.h"
#include "core/components_ng/pattern/swiper/swiper_model_ng.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t CALL_ARG_NODE_INDEX = 0;
constexpr int32_t CALL_ARG_VALUE_INDEX = 1;
constexpr int32_t CALL_ARG_TYPE_INDEX = 2;
constexpr int32_t DISPLAY_ARROW_VALUE = 1;
constexpr int32_t ARROW_IS_SHOW_BACKGROUND = 2;
constexpr int32_t ARROW_IS_SIDE_BAR_MIDDLE = 3;
constexpr int32_t ARROW_BACKGROUND_SIZE = 4;
constexpr int32_t ARROW_BACKGROUND_COLOR = 5;
constexpr int32_t ARROW_SIZE = 6;
constexpr int32_t ARROW_COLOR = 7;
constexpr int32_t DISPLAY_ARROW_IS_HOVER_SHOW_INDEX = 8;
constexpr int32_t INDICATOR_VALUE_INDEX = 2;
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
constexpr int32_t DIGIT_INDICATOR_IGNORE_SIZE = 12;
constexpr int32_t DIGIT_INDICATOR_SET_IGNORE_SIZE = 13;
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
constexpr int32_t DOT_INDICATOR_IGNORE_SIZE = 15;
constexpr int32_t DOT_INDICATOR_SET_IGNORE_SIZE = 16;
constexpr double DEFAULT_PERCENT_VALUE = 100.0;
constexpr int32_t DEFAULT_ANIMATION_MODE = 0;
constexpr int32_t STOP_WHEN_TOUCHED = 2;
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
constexpr int32_t INDICATOR_RESOURCE_VECTOR_LENGTH = 10;
constexpr int32_t DIGIT_INDICATOR_RESOURCE_FONT_COLOR = 4;
constexpr int32_t DIGIT_INDICATOR_RESOURCE_FONT_SELECTED_COLOR = 5;
constexpr int32_t DIGIT_INDICATOR_RESOURCE_FONT_SIZE = 6;
constexpr int32_t DIGIT_INDICATOR_RESOURCE_SELECTED_FONT_SIZE = 7;
constexpr int32_t ARROW_RESOURCE_BACKGROUND_SIZE = 0;
constexpr int32_t ARROW_RESOURCE_BACKGROUND_COLOR = 1;
constexpr int32_t ARROW_RESOURCE_SIZE = 2;
constexpr int32_t ARROW_RESOURCE_COLOR = 3;
constexpr int32_t ARROW_RESOURCE_VECTOR_LENGTH = 4;
} // namespace

ArkUINativeModuleValue SwiperBridge::SetSwiperInitialize(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_NODE_INDEX);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());

    auto nodePtr = GetArkUINodeModifiers()->getSwiperModifier()->getSwiperController(nativeNode);
    auto node = AceType::Claim(reinterpret_cast<OHOS::Ace::SwiperController*>(nodePtr));

    Framework::JsiCallbackInfo info = Framework::JsiCallbackInfo(runtimeCallInfo);
    Framework::JSSwiperController* jsController =
        Framework::JSRef<Framework::JSObject>::Cast(info[1])->Unwrap<Framework::JSSwiperController>();
    if (jsController) {
        jsController->SetInstanceId(Container::CurrentId());
        jsController->SetController(node);
    }
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue SwiperBridge::ResetSwiperInitialize(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_NODE_INDEX);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getSwiperModifier()->getSwiperController(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue SwiperBridge::SetSwiperNextMargin(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_NODE_INDEX);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    Local<JSValueRef> valueArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_VALUE_INDEX);
    Ace::CalcDimension nextMargin;
    RefPtr<ResourceObject> nextMarginResObj;
    if (valueArg->IsUndefined() || valueArg->IsNull() ||
        !ArkTSUtils::ParseJsDimension(vm, valueArg, nextMargin, DimensionUnit::VP, nextMarginResObj) ||
        LessNotEqual(nextMargin.Value(), 0.0)) {
        nextMargin.SetValue(0.0);
    }
    int32_t nextMarginUnit = static_cast<int32_t>(nextMargin.Unit());
    if (SystemProperties::ConfigChangePerform()) {
        auto nextMarginRawPtr = AceType::RawPtr(nextMarginResObj);
        GetArkUINodeModifiers()->getSwiperModifier()->setSwiperNextMarginRaw(
            nativeNode, nextMargin.Value(), nextMarginUnit, 0, nextMarginRawPtr);
    } else {
        GetArkUINodeModifiers()->getSwiperModifier()->setSwiperNextMargin(
            nativeNode, nextMargin.Value(), nextMarginUnit, 0);
    }
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue SwiperBridge::ResetSwiperNextMargin(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_NODE_INDEX);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getSwiperModifier()->resetSwiperNextMargin(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue SwiperBridge::SetSwiperPrevMargin(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_NODE_INDEX);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    Local<JSValueRef> valueArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_VALUE_INDEX);
    Ace::CalcDimension prevMargin;
    RefPtr<ResourceObject> preMarginResObj;
    if (valueArg->IsUndefined() || valueArg->IsNull() ||
        !ArkTSUtils::ParseJsDimension(vm, valueArg, prevMargin, DimensionUnit::VP, preMarginResObj) ||
        LessNotEqual(prevMargin.Value(), 0.0)) {
        prevMargin.SetValue(0.0);
    }
    int32_t prevMarginUnit = static_cast<int32_t>(prevMargin.Unit());
    if (SystemProperties::ConfigChangePerform()) {
        auto preMarginRawPtr = AceType::RawPtr(preMarginResObj);
        GetArkUINodeModifiers()->getSwiperModifier()->setSwiperPrevMarginRaw(
            nativeNode, prevMargin.Value(), prevMarginUnit, 0, preMarginRawPtr);
    } else {
        GetArkUINodeModifiers()->getSwiperModifier()->setSwiperPrevMargin(
            nativeNode, prevMargin.Value(), prevMarginUnit, 0);
    }
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue SwiperBridge::ResetSwiperPrevMargin(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_NODE_INDEX);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getSwiperModifier()->resetSwiperPrevMargin(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SwiperBridge::SetNestedScroll(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_NODE_INDEX);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    Local<JSValueRef> valueArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_VALUE_INDEX);
    if (valueArg->IsNumber()) {
        int32_t index = valueArg->Int32Value(vm);
        int32_t values[1] = { 0 };
        values[0] = index;
        GetArkUINodeModifiers()->getSwiperModifier()->setSwiperNestedScroll(nativeNode, &values);
    } else {
        GetArkUINodeModifiers()->getSwiperModifier()->resetSwiperNestedScroll(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SwiperBridge::ResetNestedScroll(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_NODE_INDEX);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getSwiperModifier()->resetSwiperNestedScroll(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SwiperBridge::SetIndicatorInteractive(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_NODE_INDEX);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    Local<JSValueRef> valueArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_VALUE_INDEX);
    bool interactive = valueArg->ToBoolean(vm)->Value();
    GetArkUINodeModifiers()->getSwiperModifier()->setIndicatorInteractive(nativeNode, interactive);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SwiperBridge::ResetIndicatorInteractive(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_NODE_INDEX);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getSwiperModifier()->resetIndicatorInteractive(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SwiperBridge::SetSwiperDisplayCount(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_NODE_INDEX);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    Local<JSValueRef> valueArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_VALUE_INDEX);
    if (valueArg->IsNumber() || valueArg->IsString(vm)) {
        Local<JSValueRef> typeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_TYPE_INDEX);
        std::string displayCountValue;
        std::string type = typeArg->ToString(vm)->ToString(vm);
        if (type == "number") {
            displayCountValue = std::to_string(valueArg->Int32Value(vm));
        } else {
            displayCountValue = valueArg->ToString(vm)->ToString(vm);
        }
        GetArkUINodeModifiers()->getSwiperModifier()->setSwiperDisplayCount(
            nativeNode, displayCountValue.c_str(), type.c_str());
    } else {
        GetArkUINodeModifiers()->getSwiperModifier()->resetSwiperDisplayCount(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue SwiperBridge::ResetSwiperDisplayCount(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_NODE_INDEX);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getSwiperModifier()->resetSwiperDisplayCount(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SwiperBridge::SetSwiperSwipeByGroup(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_NODE_INDEX);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    Local<JSValueRef> valueArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_VALUE_INDEX);
    bool swipeByGroup = valueArg->ToBoolean(vm)->Value();
    GetArkUINodeModifiers()->getSwiperModifier()->setSwiperSwipeByGroup(nativeNode, swipeByGroup);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SwiperBridge::ResetSwiperSwipeByGroup(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_NODE_INDEX);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getSwiperModifier()->resetSwiperSwipeByGroup(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
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
ArkUINativeModuleValue SwiperBridge::SetSwiperDisplayArrow(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_NODE_INDEX);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    Local<JSValueRef> displayArrowValue = runtimeCallInfo->GetCallArgRef(DISPLAY_ARROW_VALUE);
    Local<JSValueRef> showBackground = runtimeCallInfo->GetCallArgRef(ARROW_IS_SHOW_BACKGROUND);
    Local<JSValueRef> isSidebarMiddle = runtimeCallInfo->GetCallArgRef(ARROW_IS_SIDE_BAR_MIDDLE);
    Local<JSValueRef> backgroundSize = runtimeCallInfo->GetCallArgRef(ARROW_BACKGROUND_SIZE);
    Local<JSValueRef> backgroundColor = runtimeCallInfo->GetCallArgRef(ARROW_BACKGROUND_COLOR);
    Local<JSValueRef> arrowSize = runtimeCallInfo->GetCallArgRef(ARROW_SIZE);
    Local<JSValueRef> arrowColor = runtimeCallInfo->GetCallArgRef(ARROW_COLOR);
    Local<JSValueRef> isHoverShow = runtimeCallInfo->GetCallArgRef(DISPLAY_ARROW_IS_HOVER_SHOW_INDEX);
    std::string displayArrowValueStr = std::to_string(displayArrowValue->Int32Value(vm));
    std::string showBackgroundStr = "2";
    if (!showBackground->IsUndefined()) {
        showBackgroundStr = showBackground->ToBoolean(vm)->Value() ? "1" : "0";
    }
    std::string isSidebarMiddleStr = "2";
    if (!isSidebarMiddle->IsUndefined()) {
        isSidebarMiddleStr = isSidebarMiddle->ToBoolean(vm)->Value() ? "1" : "0";
    }
    CalcDimension lengthValue;
    Color color;
    std::vector<RefPtr<ResourceObject>> resObjs;
    auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(nativeNode);
    resObjs.resize(ARROW_RESOURCE_VECTOR_LENGTH);
    std::string backgroundSizeStr = ArkTSUtils::ParseJsDimension(vm, backgroundSize, lengthValue, DimensionUnit::VP,
        resObjs.at(ARROW_RESOURCE_BACKGROUND_SIZE), false)
        ? std::to_string(lengthValue.Value()) + GetDimensionUnitString(lengthValue.Unit()) : "-";
    std::string backgroundColorStr = ArkTSUtils::ParseJsColorAlpha(vm, backgroundColor, color,
        resObjs.at(ARROW_RESOURCE_BACKGROUND_COLOR), nodeInfo) ? std::to_string(color.GetValue()) : "-";
    std::string arrowSizeStr = ArkTSUtils::ParseJsDimensionNG(vm, arrowSize, lengthValue, DimensionUnit::VP,
        resObjs.at(ARROW_RESOURCE_SIZE), false)
        ? std::to_string(lengthValue.Value()) + GetDimensionUnitString(lengthValue.Unit()) : "-";
    std::string arrowColorStr = ArkTSUtils::ParseJsColorAlpha(vm, arrowColor, color,
        resObjs.at(ARROW_RESOURCE_COLOR), nodeInfo) ? std::to_string(color.GetValue()) : "-";
    std::string isHoverShowStr = "2";
    if (!isHoverShow->IsUndefined()) {
        isHoverShowStr = isHoverShow->ToBoolean(vm)->Value() ? "1" : "0";
    }
    std::string displayArrowStr = displayArrowValueStr + "|" + showBackgroundStr + "|" + isSidebarMiddleStr + "|" +
                                  backgroundSizeStr + "|" + backgroundColorStr + "|" + arrowSizeStr + "|" +
                                  arrowColorStr + "|" + isHoverShowStr + "|";
    if (SystemProperties::ConfigChangePerform()) {
        GetArkUINodeModifiers()->getSwiperModifier()->setSwiperDisplayArrowRaw(nativeNode, displayArrowStr.c_str(),
            static_cast<void*>(&resObjs));
    } else {
        GetArkUINodeModifiers()->getSwiperModifier()->setSwiperDisplayArrow(nativeNode, displayArrowStr.c_str());
    }
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue SwiperBridge::ResetSwiperDisplayArrow(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_NODE_INDEX);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getSwiperModifier()->resetSwiperDisplayArrow(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue SwiperBridge::SetSwiperCurve(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_NODE_INDEX);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    Local<JSValueRef> valueArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_VALUE_INDEX);
    if (valueArg->IsString(vm)) {
        std::string curve = valueArg->ToString(vm)->ToString(vm);
        GetArkUINodeModifiers()->getSwiperModifier()->setSwiperCurve(nativeNode, curve.c_str());
    } else {
        GetArkUINodeModifiers()->getSwiperModifier()->resetSwiperCurve(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue SwiperBridge::ResetSwiperCurve(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_NODE_INDEX);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getSwiperModifier()->resetSwiperCurve(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue SwiperBridge::SetSwiperDisableSwipe(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_NODE_INDEX);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    Local<JSValueRef> valueArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_VALUE_INDEX);
    if (valueArg->IsBoolean()) {
        bool disableswipe = valueArg->ToBoolean(vm)->Value();
        GetArkUINodeModifiers()->getSwiperModifier()->setSwiperDisableSwipe(nativeNode, disableswipe);
    } else {
        GetArkUINodeModifiers()->getSwiperModifier()->resetSwiperDisableSwipe(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue SwiperBridge::ResetSwiperDisableSwipe(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_NODE_INDEX);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getSwiperModifier()->resetSwiperDisableSwipe(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue SwiperBridge::SetSwiperEffectMode(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_NODE_INDEX);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    Local<JSValueRef> valueArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_VALUE_INDEX);
    if (valueArg->IsNumber()) {
        auto edgeEffect = valueArg->Int32Value(vm);
        GetArkUINodeModifiers()->getSwiperModifier()->setSwiperEffectMode(nativeNode, edgeEffect);
    } else {
        GetArkUINodeModifiers()->getSwiperModifier()->resetSwiperEffectMode(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue SwiperBridge::ResetSwiperEffectMode(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_NODE_INDEX);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getSwiperModifier()->resetSwiperEffectMode(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue SwiperBridge::SetSwiperCachedCount(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_NODE_INDEX);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    Local<JSValueRef> valueArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_VALUE_INDEX);
    if (valueArg->IsNumber()) {
        int32_t cachedCount = valueArg->Int32Value(vm);
        GetArkUINodeModifiers()->getSwiperModifier()->setSwiperCachedCount(nativeNode, cachedCount);
    } else {
        GetArkUINodeModifiers()->getSwiperModifier()->resetSwiperCachedCount(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue SwiperBridge::ResetSwiperCachedCount(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_NODE_INDEX);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getSwiperModifier()->resetSwiperCachedCount(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue SwiperBridge::SetSwiperIsShown(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_NODE_INDEX);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    Local<JSValueRef> valueArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_VALUE_INDEX);
    bool isShown = valueArg->ToBoolean(vm)->Value();
    GetArkUINodeModifiers()->getSwiperModifier()->setSwiperIsShown(nativeNode, isShown);
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue SwiperBridge::ResetSwiperIsShown(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_NODE_INDEX);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getSwiperModifier()->resetSwiperIsShown(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue SwiperBridge::SetSwiperDisplayMode(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_NODE_INDEX);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    Local<JSValueRef> valueArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_VALUE_INDEX);
    if (valueArg->IsNumber()) {
        int32_t index = valueArg->Int32Value(vm);
        GetArkUINodeModifiers()->getSwiperModifier()->setSwiperDisplayMode(nativeNode, index);
    } else {
        GetArkUINodeModifiers()->getSwiperModifier()->resetSwiperDisplayMode(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue SwiperBridge::ResetSwiperDisplayMode(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_NODE_INDEX);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getSwiperModifier()->resetSwiperDisplayMode(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue SwiperBridge::SetSwiperItemSpace(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_NODE_INDEX);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    Local<JSValueRef> valueArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_VALUE_INDEX);
    Ace::CalcDimension itemSpace;
    if (!ArkTSUtils::ParseJsDimensionVpNG(vm, valueArg, itemSpace) || LessNotEqual(itemSpace.Value(), 0.0)) {
        itemSpace.SetValue(0.0);
    }
    int32_t itemSpaceUnit = static_cast<int32_t>(itemSpace.Unit());
    GetArkUINodeModifiers()->getSwiperModifier()->setSwiperItemSpace(nativeNode, itemSpace.Value(), itemSpaceUnit);
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue SwiperBridge::ResetSwiperItemSpace(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_NODE_INDEX);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getSwiperModifier()->resetSwiperItemSpace(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue SwiperBridge::SetSwiperVertical(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_NODE_INDEX);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    Local<JSValueRef> valueArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_VALUE_INDEX);
    if (valueArg->IsBoolean()) {
        bool isVertical = valueArg->ToBoolean(vm)->Value();
        GetArkUINodeModifiers()->getSwiperModifier()->setSwiperVertical(nativeNode, isVertical);
    } else {
        GetArkUINodeModifiers()->getSwiperModifier()->resetSwiperVertical(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue SwiperBridge::ResetSwiperVertical(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_NODE_INDEX);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getSwiperModifier()->resetSwiperVertical(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue SwiperBridge::SetSwiperLoop(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_NODE_INDEX);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    Local<JSValueRef> valueArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_VALUE_INDEX);
    if (valueArg->IsBoolean()) {
        bool loop = valueArg->ToBoolean(vm)->Value();
        GetArkUINodeModifiers()->getSwiperModifier()->setSwiperLoop(nativeNode, loop);
    } else {
        GetArkUINodeModifiers()->getSwiperModifier()->resetSwiperLoop(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue SwiperBridge::ResetSwiperLoop(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_NODE_INDEX);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getSwiperModifier()->resetSwiperLoop(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue SwiperBridge::SetSwiperInterval(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_NODE_INDEX);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    Local<JSValueRef> valueArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_VALUE_INDEX);
    if (valueArg->IsNumber()) {
        int32_t interval = valueArg->Int32Value(vm);
        GetArkUINodeModifiers()->getSwiperModifier()->setSwiperInterval(nativeNode, interval);
    } else {
        GetArkUINodeModifiers()->getSwiperModifier()->resetSwiperInterval(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue SwiperBridge::ResetSwiperInterval(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_NODE_INDEX);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getSwiperModifier()->resetSwiperInterval(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue SwiperBridge::SetSwiperAutoPlay(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_NODE_INDEX);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    Local<JSValueRef> valueArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_VALUE_INDEX);
    if (valueArg->IsBoolean()) {
        bool autoPlay = valueArg->ToBoolean(vm)->Value();
        GetArkUINodeModifiers()->getSwiperModifier()->setSwiperAutoPlay(nativeNode, autoPlay);
    } else {
        GetArkUINodeModifiers()->getSwiperModifier()->resetSwiperAutoPlay(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }

    Local<JSValueRef> jsStopWhenTouchedArg = runtimeCallInfo->GetCallArgRef(STOP_WHEN_TOUCHED);
    bool neddStopWhenTouched = true;
    if (!jsStopWhenTouchedArg->IsNull() && !jsStopWhenTouchedArg->IsUndefined() && jsStopWhenTouchedArg->IsBoolean()) {
        neddStopWhenTouched = jsStopWhenTouchedArg->ToBoolean(vm)->Value();
    }
    GetArkUINodeModifiers()->getSwiperModifier()->setSwiperStopWhenTouched(nativeNode, neddStopWhenTouched);
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue SwiperBridge::ResetSwiperAutoPlay(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_NODE_INDEX);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getSwiperModifier()->resetSwiperAutoPlay(nativeNode);
    GetArkUINodeModifiers()->getSwiperModifier()->resetSwiperStopWhenTouched(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue SwiperBridge::SetSwiperIndex(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_NODE_INDEX);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    Local<JSValueRef> valueArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_VALUE_INDEX);
    if (valueArg->IsNumber()) {
        int32_t index = valueArg->Int32Value(vm);
        GetArkUINodeModifiers()->getSwiperModifier()->setSwiperIndex(nativeNode, index, DEFAULT_ANIMATION_MODE);
    } else {
        GetArkUINodeModifiers()->getSwiperModifier()->resetSwiperIndex(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue SwiperBridge::ResetSwiperIndex(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_NODE_INDEX);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getSwiperModifier()->resetSwiperIndex(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
std::string GetStringByValueRef(const EcmaVM* vm, const Local<JSValueRef>& jsValue, RefPtr<ResourceObject>& resObj)
{
    std::string result = "-";
    if (jsValue->IsUndefined()) {
        return result;
    }
    CalcDimension calc;
    result = ArkTSUtils::ParseJsDimension(vm, jsValue, calc, DimensionUnit::VP, resObj, true)
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

std::string ParseBottom(const EcmaVM* vm, const Local<JSValueRef>& jsValue, bool hasIgnoreSize,
    RefPtr<ResourceObject>& resObj)
{
    std::string bottom = "-";
    if (jsValue->IsUndefined()) {
        return bottom;
    }
    if (hasIgnoreSize) {
        CalcDimension bottomcCalc;
        bool parseOK =  ArkTSUtils::ParseJsLengthMetrics(vm, jsValue, bottomcCalc, resObj);
        if (!parseOK) {
            bottom = GetStringByValueRef(vm, jsValue, resObj);
            return bottom;
        } else {
            bottomcCalc = bottomcCalc > 0.0_vp ? bottomcCalc : 0.0_vp;
            bottom = bottomcCalc.ToString();
            return bottom;
        }
    } else {
        bottom = GetStringByValueRef(vm, jsValue, resObj);
        return bottom;
    }
}

std::optional<bool> ParseIgrnoreSize(const EcmaVM* vm, const Local<JSValueRef>& jsValue, bool hasIgrnoreSize)
{
    std::optional<bool> ignoreSize;
    if (!hasIgrnoreSize) {
        return ignoreSize;
    }
    ignoreSize = false;
    if (!jsValue->IsNull() && !jsValue->IsUndefined() && jsValue->IsBoolean()) {
        ignoreSize = jsValue->ToBoolean(vm)->Value();
    }
    return ignoreSize;
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

void GetSpaceAndBottom(ArkUIRuntimeCallInfo* runtimeCallInfo, EcmaVM* vm, std::string& bottom,
    std::string& spaceAndIgnoreSize, RefPtr<ResourceObject>& resObj)
{
    Local<JSValueRef> bottomArg = runtimeCallInfo->GetCallArgRef(DOT_INDICATOR_BOTTOM);
    Local<JSValueRef> spaceArg = runtimeCallInfo->GetCallArgRef(DOT_INDICATOR_SPACE);
    Local<JSValueRef> ignoreSizeArg = runtimeCallInfo->GetCallArgRef(DOT_INDICATOR_IGNORE_SIZE);
    Local<JSValueRef> setIgnoreSizeArg = runtimeCallInfo->GetCallArgRef(DOT_INDICATOR_SET_IGNORE_SIZE);

    auto hasIgnoreSize = (setIgnoreSizeArg->IsBoolean() && setIgnoreSizeArg->ToBoolean(vm)->Value()) ? true : false;
    std::optional<bool> ignoreSize = ParseIgrnoreSize(vm, ignoreSizeArg, hasIgnoreSize);
    std::string ignoreSizeStr = "-";
    if (ignoreSize.has_value()) {
        ignoreSizeStr = ignoreSize.value()  ? "1" : "0";
    }

    std::string setIgnoreSizeStr = "-";
    if (!setIgnoreSizeArg->IsUndefined()) {
        setIgnoreSizeStr = setIgnoreSizeArg->ToBoolean(vm)->Value() ? "1" : "0";
    }

    bottom = ParseBottom(vm, bottomArg, hasIgnoreSize, resObj);
    std::string space = ParseSpace(vm, spaceArg);
    spaceAndIgnoreSize =  space + "|" + ignoreSizeStr + "|" + setIgnoreSizeStr;
}

std::string GetSwiperDotIndicator(ArkUIRuntimeCallInfo* runtimeCallInfo, EcmaVM* vm,
    std::vector<RefPtr<ResourceObject>>& resObjs, ArkUINodeHandle nativeNode)
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

    CalcDimension calc;
    std::string itemWidth = ArkTSUtils::ParseJsDimension(vm, itemWidthArg, calc, DimensionUnit::VP,
        resObjs.at(DOT_INDICATOR_RESOURCE_ITEM_WIDTH), false)
        ? std::to_string(calc.Value()) + GetDimensionUnitString(calc.Unit()) : "-";
    std::string itemHeight = ArkTSUtils::ParseJsDimension(vm, itemHeightArg, calc, DimensionUnit::VP,
        resObjs.at(DOT_INDICATOR_RESOURCE_ITEM_HEIGHT), false)
        ? std::to_string(calc.Value()) + GetDimensionUnitString(calc.Unit()) : "-";
    std::string selectedItemWidth =
        ArkTSUtils::ParseJsDimension(vm, selectedItemWidthArg, calc, DimensionUnit::VP,
            resObjs.at(DOT_INDICATOR_RESOURCE_SELECTED_ITEM_WIDTH), false)
            ? std::to_string(calc.Value()) + GetDimensionUnitString(calc.Unit()) : "-";
    std::string selectedItemHeight =
        ArkTSUtils::ParseJsDimension(vm, selectedItemHeightArg, calc, DimensionUnit::VP,
            resObjs.at(DOT_INDICATOR_RESOURCE_SELECTED_ITEM_HEIGHT), false)
            ? std::to_string(calc.Value()) + GetDimensionUnitString(calc.Unit()) : "-";
    std::string mask = "2";
    if (!maskArg->IsUndefined()) {
        mask = maskArg->ToBoolean(vm)->Value() ? "1" : "0";
    }
    Color color;
    auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(nativeNode);
    std::string colorStr = ArkTSUtils::ParseJsColorAlpha(vm, colorArg, color,
        resObjs.at(DOT_INDICATOR_RESOURCE_COLOR), nodeInfo) ? std::to_string(color.GetValue()) : "-";
    std::string selectedColor = ArkTSUtils::ParseJsColorAlpha(vm, selectedColorArg, color,
        resObjs.at(DOT_INDICATOR_RESOURCE_SELECTED_COLOR), nodeInfo) ? std::to_string(color.GetValue()) : "-";
    std::string left = GetStringByValueRef(vm, leftArg, resObjs.at(INDICATOR_RESOURCE_LEFT));
    std::string top = GetStringByValueRef(vm, topArg, resObjs.at(INDICATOR_RESOURCE_TOP));
    std::string right = GetStringByValueRef(vm, rightArg, resObjs.at(INDICATOR_RESOURCE_RIGHT));
    Local<JSValueRef> maxDisplayCountArg = runtimeCallInfo->GetCallArgRef(DOT_INDICATOR_MAX_DISPLAY_COUNT);
    auto maxDisplayCount = GetIntStringByValueRef(vm, maxDisplayCountArg);
    std::string bottom = "-";
    std::string spaceAndIgnoreSize = "-";
    GetSpaceAndBottom(runtimeCallInfo, vm, bottom, spaceAndIgnoreSize, resObjs.at(INDICATOR_RESOURCE_BOTTOM));
    std::string indicatorStr = itemWidth + "|" + itemHeight + "|" + selectedItemWidth + "|" +
                               selectedItemHeight + "|" + mask + "|" + colorStr + "|" + selectedColor + "|" + left +
                               "|" + top + "|" + right + "|" + bottom + "|" + maxDisplayCount + "|" +
                               spaceAndIgnoreSize;
    return indicatorStr;
}
std::string GetSwiperDigitIndicator(ArkUIRuntimeCallInfo* runtimeCallInfo, EcmaVM* vm,
    std::vector<RefPtr<ResourceObject>>& resObjs, ArkUINodeHandle nativeNode)
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
    Local<JSValueRef> ignoreSizeArg = runtimeCallInfo->GetCallArgRef(DIGIT_INDICATOR_IGNORE_SIZE);
    Local<JSValueRef> setIgnoreSizeArg = runtimeCallInfo->GetCallArgRef(DIGIT_INDICATOR_SET_IGNORE_SIZE);
    Color color;
    CalcDimension calc;
    auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(nativeNode);
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
    std::string left = GetStringByValueRef(vm, leftArg, resObjs.at(INDICATOR_RESOURCE_LEFT));
    std::string top = GetStringByValueRef(vm, topArg, resObjs.at(INDICATOR_RESOURCE_TOP));
    std::string right = GetStringByValueRef(vm, rightArg, resObjs.at(INDICATOR_RESOURCE_RIGHT));
    
    std::string setIgnoreSize = "-";
    if (!setIgnoreSizeArg->IsUndefined()) {
        setIgnoreSize = setIgnoreSizeArg->ToBoolean(vm)->Value() ? "1" : "0";
    }

    auto hasIgnoreSize = (setIgnoreSizeArg->IsBoolean() && setIgnoreSizeArg->ToBoolean(vm)->Value()) ? true : false;
    std::optional<bool> ignoreSize = ParseIgrnoreSize(vm, ignoreSizeArg, hasIgnoreSize);
    std::string ignoreSizeStr = "-";
    if (ignoreSize.has_value()) {
        ignoreSizeStr = ignoreSize.value()  ? "1" : "0";
    }
    std::string bottom = ParseBottom(vm, bottomArg, hasIgnoreSize, resObjs.at(INDICATOR_RESOURCE_BOTTOM));
    std::string indicatorStr = fontColor + "|" + selectedFontColor + "|" + digitFontSize + "|" + digitFontWeight +
                   "|" + selectedDigitFontSize + "|" + selectedDigitFontWeight + "|" + left + "|" + top + "|" + right +
                   "|" + bottom + "|" + ignoreSizeStr + "|" + setIgnoreSize;
    return indicatorStr;
}
ArkUINativeModuleValue SwiperBridge::SetSwiperIndicator(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_NODE_INDEX);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    Local<JSValueRef> valueArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_VALUE_INDEX);
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));

    std::string type = valueArg->ToString(vm)->ToString(vm);
    std::string indicatorStr = "";
    std::vector<RefPtr<ResourceObject>> resObjs;
    resObjs.resize(INDICATOR_RESOURCE_VECTOR_LENGTH);
    if (type == "boolean") {
        Local<JSValueRef> indicatorArg = runtimeCallInfo->GetCallArgRef(INDICATOR_VALUE_INDEX);
        std::string indicator = indicatorArg->ToBoolean(vm)->Value() ? "1" : "0";
        indicatorStr = type + "|" + indicator;
    } else if (type == "ArkDotIndicator") {
        indicatorStr = type + "|" + GetSwiperDotIndicator(runtimeCallInfo, vm, resObjs, nativeNode);
    } else if (type == "ArkDigitIndicator") {
        indicatorStr = type + "|" + GetSwiperDigitIndicator(runtimeCallInfo, vm, resObjs, nativeNode);
    } else if (type == "IndicatorComponentController") {
        Framework::JsiCallbackInfo info = Framework::JsiCallbackInfo(runtimeCallInfo);
        Framework::JSIndicatorController* jsController =
            Framework::JSRef<Framework::JSObject>::Cast(info[INDICATOR_VALUE_INDEX])
                ->Unwrap<Framework::JSIndicatorController>();
        if (jsController) {
            auto targetNode = AceType::Claim(frameNode);
            jsController->SetSwiperNodeBySwiper(targetNode);
        }
        indicatorStr = "IndicatorComponentController|";
    } else {
        indicatorStr = "boolean|1";
    }
    if (SystemProperties::ConfigChangePerform()) {
        GetArkUINodeModifiers()->getSwiperModifier()->setSwiperIndicatorRaw(nativeNode, indicatorStr.c_str(),
            static_cast<void*>(&resObjs));
    } else {
        GetArkUINodeModifiers()->getSwiperModifier()->setSwiperIndicator(nativeNode, indicatorStr.c_str());
    }
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue SwiperBridge::ResetSwiperIndicator(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_NODE_INDEX);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getSwiperModifier()->resetSwiperIndicator(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue SwiperBridge::SetSwiperDuration(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_NODE_INDEX);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    Local<JSValueRef> valueArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_VALUE_INDEX);
    if (valueArg->IsNumber()) {
        int32_t duration = valueArg->Int32Value(vm);
        GetArkUINodeModifiers()->getSwiperModifier()->setSwiperDuration(nativeNode, duration);
    } else {
        GetArkUINodeModifiers()->getSwiperModifier()->resetSwiperDuration(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SwiperBridge::ResetSwiperDuration(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_NODE_INDEX);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getSwiperModifier()->resetSwiperDuration(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SwiperBridge::SetSwiperEnabled(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_NODE_INDEX);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    Local<JSValueRef> valueArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_VALUE_INDEX);
    if (valueArg->IsBoolean()) {
        bool enabled = valueArg->ToBoolean(vm)->Value();
        GetArkUINodeModifiers()->getCommonModifier()->setEnabled(nativeNode, enabled);
        GetArkUINodeModifiers()->getSwiperModifier()->setSwiperEnabled(nativeNode, enabled);
    } else {
        GetArkUINodeModifiers()->getCommonModifier()->resetEnabled(nativeNode);
        GetArkUINodeModifiers()->getSwiperModifier()->resetSwiperEnabled(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SwiperBridge::ResetSwiperEnabled(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_NODE_INDEX);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getCommonModifier()->resetEnabled(nativeNode);
    GetArkUINodeModifiers()->getSwiperModifier()->resetSwiperEnabled(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SwiperBridge::SetSwiperOnChange(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_NODE_INDEX);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_VALUE_INDEX);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        GetArkUINodeModifiers()->getSwiperModifier()->resetSwiperOnChange(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<void(const BaseEventInfo* info)> callback =
        [vm, frameNode, func = panda::CopyableGlobal(vm, func)](const BaseEventInfo* info) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
        const auto* swiperInfo = TypeInfoHelper::DynamicCast<SwiperChangeEvent>(info);
        if (!swiperInfo) {
            TAG_LOGW(AceLogTag::ACE_SWIPER, "Swiper onChange callback execute failed.");
            return;
        }
        panda::Local<panda::NumberRef> indexParam = panda::NumberRef::New(vm, swiperInfo->GetIndex());
        panda::Local<panda::JSValueRef> params[1] = { indexParam }; // 1: Array length
        func->Call(vm, func.ToLocal(), params, 1); // 1: Array length
    };
    GetArkUINodeModifiers()->getSwiperModifier()->setSwiperOnChange(nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SwiperBridge::ResetSwiperOnChange(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_NODE_INDEX);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getSwiperModifier()->resetSwiperOnChange(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SwiperBridge::SetSwiperOnSelected(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_NODE_INDEX);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_VALUE_INDEX);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        GetArkUINodeModifiers()->getSwiperModifier()->resetSwiperOnSelected(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<void(const BaseEventInfo* info)> callback =
        [vm, frameNode, func = panda::CopyableGlobal(vm, func)](const BaseEventInfo* info) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
        const auto* swiperInfo = TypeInfoHelper::DynamicCast<SwiperChangeEvent>(info);
        if (!swiperInfo) {
            TAG_LOGW(AceLogTag::ACE_SWIPER, "Swiper onSelected callback execute failed.");
            return;
        }
        panda::Local<panda::NumberRef> indexParam = panda::NumberRef::New(vm, swiperInfo->GetIndex());
        panda::Local<panda::JSValueRef> params[1] = { indexParam }; // 1: Array length
        func->Call(vm, func.ToLocal(), params, 1); // 1: Array length
    };
    GetArkUINodeModifiers()->getSwiperModifier()->setSwiperOnSelected(nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SwiperBridge::ResetSwiperOnSelected(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_NODE_INDEX);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getSwiperModifier()->resetSwiperOnSelected(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SwiperBridge::SetSwiperOnAnimationStart(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_NODE_INDEX);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_VALUE_INDEX);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        GetArkUINodeModifiers()->getSwiperModifier()->resetSwiperOnAnimationStart(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<void(int32_t, int32_t, const AnimationCallbackInfo&)> callback =
        [vm, frameNode, func = panda::CopyableGlobal(vm, func)](
        int32_t index, int32_t targetIndex, const AnimationCallbackInfo& extraInfo) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
        panda::Local<panda::NumberRef> indexParam = panda::NumberRef::New(vm, index);
        panda::Local<panda::NumberRef> targetIndexParam = panda::NumberRef::New(vm, targetIndex);
        const char* keys[] = {"currentOffset", "targetOffset", "velocity"};
        Local<JSValueRef> values[] = { panda::NumberRef::New(vm, extraInfo.currentOffset.value_or(0.0f)),
            panda::NumberRef::New(vm, extraInfo.targetOffset.value_or(0.0f)),
            panda::NumberRef::New(vm, extraInfo.velocity.value_or(0.0f)) };
        auto eventObject = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(keys), keys, values);
        panda::Local<panda::JSValueRef> params[3] = { indexParam, targetIndexParam, eventObject }; // 3: Array length
        func->Call(vm, func.ToLocal(), params, 3); // 3: Array length
    };
    GetArkUINodeModifiers()->getSwiperModifier()->setSwiperOnAnimationStart(nativeNode,
        reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SwiperBridge::ResetSwiperOnAnimationStart(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getSwiperModifier()->resetSwiperOnAnimationStart(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SwiperBridge::SetSwiperOnAnimationEnd(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_NODE_INDEX);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_VALUE_INDEX);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        GetArkUINodeModifiers()->getSwiperModifier()->resetSwiperOnAnimationEnd(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<void(int32_t, const AnimationCallbackInfo&)> callback = [vm, frameNode,
        func = panda::CopyableGlobal(vm, func)](int32_t index, const AnimationCallbackInfo& extraInfo) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
        panda::Local<panda::NumberRef> indexParam = panda::NumberRef::New(vm, index);
        const char* keys[] = {"currentOffset", "targetOffset", "velocity"};
        Local<JSValueRef> values[] = { panda::NumberRef::New(vm, extraInfo.currentOffset.value()),
            panda::NumberRef::New(vm, 0),
            panda::NumberRef::New(vm, 0) };
        auto eventObject = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(keys), keys, values);
        panda::Local<panda::JSValueRef> params[2] = { indexParam, eventObject }; // 2: Array length
        func->Call(vm, func.ToLocal(), params, 2); // 2: Array length
    };
    GetArkUINodeModifiers()->getSwiperModifier()->setSwiperOnAnimationEnd(nativeNode,
        reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SwiperBridge::ResetSwiperOnAnimationEnd(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getSwiperModifier()->resetSwiperOnAnimationEnd(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SwiperBridge::SetSwiperOnGestureSwipe(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_NODE_INDEX);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_VALUE_INDEX);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        GetArkUINodeModifiers()->getSwiperModifier()->resetSwiperOnGestureSwipe(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<void(int32_t, const AnimationCallbackInfo&)> callback = [vm, frameNode,
        func = panda::CopyableGlobal(vm, func)](int32_t index, const AnimationCallbackInfo& extraInfo) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
        panda::Local<panda::NumberRef> indexParam = panda::NumberRef::New(vm, index);
        const char* keys[] = {"currentOffset", "targetOffset", "velocity"};
        Local<JSValueRef> values[] = { panda::NumberRef::New(vm, extraInfo.currentOffset.value()),
            panda::NumberRef::New(vm, 0),
            panda::NumberRef::New(vm, 0) };
        auto eventObject = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(keys), keys, values);
        panda::Local<panda::JSValueRef> params[2] = { indexParam, eventObject }; // 2: Array length
        func->Call(vm, func.ToLocal(), params, 2); // 2: Array length
    };
    GetArkUINodeModifiers()->getSwiperModifier()->setSwiperOnGestureSwipe(nativeNode,
        reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SwiperBridge::ResetSwiperOnGestureSwipe(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getSwiperModifier()->resetSwiperOnGestureSwipe(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SwiperBridge::SetSwiperOnUnselected(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_NODE_INDEX);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_VALUE_INDEX);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        GetArkUINodeModifiers()->getSwiperModifier()->resetSwiperOnUnselected(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<void(const BaseEventInfo* info)> callback =
        [vm, frameNode, func = panda::CopyableGlobal(vm, func)](const BaseEventInfo* info) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
        const auto* swiperInfo = TypeInfoHelper::DynamicCast<SwiperChangeEvent>(info);
        if (!swiperInfo) {
            TAG_LOGW(AceLogTag::ACE_SWIPER, "Swiper OnUnselected callback execute failed.");
            return;
        }
        panda::Local<panda::NumberRef> indexParam = panda::NumberRef::New(vm, swiperInfo->GetIndex());
        panda::Local<panda::JSValueRef> params[1] = { indexParam }; // 1: Array length
        func->Call(vm, func.ToLocal(), params, 1); // 1: Array length
    };
    GetArkUINodeModifiers()->getSwiperModifier()->setSwiperOnUnselected(nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SwiperBridge::ResetSwiperOnUnselected(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_NODE_INDEX);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getSwiperModifier()->resetSwiperOnUnselected(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SwiperBridge::SetSwiperCustomContentTransition(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_NODE_INDEX);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto* frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    using namespace OHOS::Ace::Framework;
    JsiCallbackInfo info = JsiCallbackInfo(runtimeCallInfo);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    if (info.Length() < 2 || !info[1]->IsObject()) { // 2: Array length
        return panda::JSValueRef::Undefined(vm);
    }

    SwiperContentAnimatedTransition transitionInfo;
    auto transitionObj = JSRef<JSObject>::Cast(info[1]);
    JSRef<JSVal> timeoutProperty = transitionObj->GetProperty("timeout");
    if (timeoutProperty->IsNumber()) {
        auto timeout = timeoutProperty->ToNumber<int32_t>();
        transitionInfo.timeout = timeout < 0 ? 0 : timeout;
    } else {
        transitionInfo.timeout = 0;
    }

    JSRef<JSVal> transition = transitionObj->GetProperty("transition");
    if (transition->IsFunction()) {
        auto jsOnTransition =
            AceType::MakeRefPtr<JsSwiperFunction>(JSRef<JSFunc>::Cast(transition));
        auto onTransition = [execCtx = info.GetExecutionContext(), func = std::move(jsOnTransition)](
                                const RefPtr<SwiperContentTransitionProxy>& proxy) {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            ACE_SCORING_EVENT("Swiper.customContentTransition");
            func->Execute(proxy);
        };
        transitionInfo.transition = std::move(onTransition);
    }
    SwiperModelNG::SetCustomContentTransition(frameNode, transitionInfo);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SwiperBridge::ResetSwiperCustomContentTransition(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_NODE_INDEX);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto* frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    SwiperContentAnimatedTransition transitionInfo;
    SwiperModelNG::SetCustomContentTransition(frameNode, transitionInfo);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SwiperBridge::SetOnContentDidScroll(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_NODE_INDEX);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_VALUE_INDEX);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        GetArkUINodeModifiers()->getSwiperModifier()->resetSwiperOnContentDidScroll(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<void(int32_t, int32_t, float_t, float_t)> callback = [vm, frameNode,
        func = panda::CopyableGlobal(vm, func)](int32_t selectedIndex, int32_t index,
        float position, float mainAxisLength) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
        panda::Local<panda::NumberRef> selectedIndexParam = panda::NumberRef::New(vm, selectedIndex);
        panda::Local<panda::NumberRef> indexParam = panda::NumberRef::New(vm, index);
        panda::Local<panda::NumberRef> positionParam = panda::NumberRef::New(vm, position);
        panda::Local<panda::NumberRef> mainAxisLengthParam = panda::NumberRef::New(vm, mainAxisLength);
        panda::Local<panda::JSValueRef> params[4] = { selectedIndexParam, indexParam, // 4: Array length
            positionParam, mainAxisLengthParam };
        func->Call(vm, func.ToLocal(), params, 4); // 4: Array length
    };
    GetArkUINodeModifiers()->getSwiperModifier()->setSwiperOnContentDidScroll(nativeNode,
        reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SwiperBridge::ResetOnContentDidScroll(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getSwiperModifier()->resetSwiperOnContentDidScroll(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SwiperBridge::SetSwiperPageFlipMode(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_NODE_INDEX);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    Local<JSValueRef> valueArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_VALUE_INDEX);
    if (valueArg->IsNumber()) {
        int32_t pageFlipMode = valueArg->Int32Value(vm);
        GetArkUINodeModifiers()->getSwiperModifier()->setSwiperPageFlipMode(nativeNode, pageFlipMode);
    } else {
        GetArkUINodeModifiers()->getSwiperModifier()->resetSwiperPageFlipMode(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SwiperBridge::ResetSwiperPageFlipMode(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_NODE_INDEX);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getSwiperModifier()->resetSwiperPageFlipMode(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SwiperBridge::SetSwiperOnContentWillScroll(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_NODE_INDEX);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_VALUE_INDEX);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        GetArkUINodeModifiers()->getSwiperModifier()->resetSwiperOnContentWillScroll(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<bool(const SwiperContentWillScrollResult&)> callback =
        [vm, frameNode, func = panda::CopyableGlobal(vm, func)](const SwiperContentWillScrollResult& result) -> bool {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
        const char* keys[] = { "currentIndex", "comingIndex", "offset" };
        Local<JSValueRef> values[] = { panda::NumberRef::New(vm, result.currentIndex),
            panda::NumberRef::New(vm, result.comingIndex), panda::NumberRef::New(vm, result.offset) };
        auto eventObject = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(keys), keys, values);
        panda::Local<panda::JSValueRef> params[1] = { eventObject };
        auto ret = func->Call(vm, func.ToLocal(), params, 1);
        if (ret->IsBoolean()) {
            return ret->ToBoolean(vm)->Value();
        }
        return true;
    };
    GetArkUINodeModifiers()->getSwiperModifier()->setSwiperOnContentWillScroll(
        nativeNode, reinterpret_cast<bool*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SwiperBridge::ResetSwiperOnContentWillScroll(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getSwiperModifier()->resetSwiperOnContentWillScroll(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SwiperBridge::SetSwiperMaintainVisibleContentPosition(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_NODE_INDEX);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    Local<JSValueRef> valueArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_VALUE_INDEX);
    if (valueArg->IsBoolean()) {
        bool value = valueArg->ToBoolean(vm)->Value();
        GetArkUINodeModifiers()->getSwiperModifier()->setMaintainVisibleContentPosition(nativeNode, value);
    } else {
        GetArkUINodeModifiers()->getSwiperModifier()->resetMaintainVisibleContentPosition(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SwiperBridge::ReSetSwiperMaintainVisibleContentPosition(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_NODE_INDEX);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getSwiperModifier()->resetMaintainVisibleContentPosition(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SwiperBridge::SetSwiperOnScrollStateChanged(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_NODE_INDEX);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_VALUE_INDEX);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (!callbackArg->IsFunction(vm)) {
        GetArkUINodeModifiers()->getSwiperModifier()->resetSwiperOnScrollStateChanged(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<void(const BaseEventInfo* info)> callback =
        [vm, frameNode, func = panda::CopyableGlobal(vm, func)](const BaseEventInfo* info) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
        const auto* scrollStateInfo = TypeInfoHelper::DynamicCast<SwiperChangeEvent>(info);
        if (!scrollStateInfo) {
            TAG_LOGW(AceLogTag::ACE_SWIPER, "scrollStateInfo invalid, OnScrollStateChanged failed.");
            return;
        }
        panda::Local<panda::NumberRef> indexParam = panda::NumberRef::New(vm, scrollStateInfo->GetIndex());
        panda::Local<panda::JSValueRef> params[1] = { indexParam };
        func->Call(vm, func.ToLocal(), params, 1);
    };
    GetArkUINodeModifiers()->getSwiperModifier()->setSwiperOnScrollStateChanged(
        nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SwiperBridge::ResetSwiperOnScrollStateChanged(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_NODE_INDEX);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getSwiperModifier()->resetSwiperOnScrollStateChanged(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
} // namespace OHOS::Ace::NG
