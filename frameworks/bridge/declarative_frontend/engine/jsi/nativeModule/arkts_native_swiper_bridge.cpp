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
#include "bridge/declarative_frontend/engine/jsi/components/arkts_native_api.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"
#include "bridge/declarative_frontend/jsview/models/swiper_model_impl.h"

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
constexpr double DEFAULT_PERCENT_VALUE = 100.0;
} // namespace

ArkUINativeModuleValue SwiperBridge::SetSwiperNextMargin(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_NODE_INDEX);
    void* nativeNode = nodeArg->ToNativePointer(vm)->Value();
    Local<JSValueRef> valueArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_VALUE_INDEX);
    Ace::CalcDimension nextMargin;
    if (!ArkTSUtils::ParseJsDimension(vm, valueArg, nextMargin, DimensionUnit::VP) || valueArg->IsNull() ||
        valueArg->IsUndefined() || LessNotEqual(nextMargin.Value(), 0.0)) {
        nextMargin.SetValue(0.0);
    }
    int32_t nextMarginUnit = static_cast<int32_t>(nextMargin.Unit());
    GetArkUIInternalNodeAPI()->GetSwiperModifier().SetSwiperNextMargin(nativeNode, nextMargin.Value(), nextMarginUnit);
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue SwiperBridge::ResetSwiperNextMargin(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_NODE_INDEX);
    void* nativeNode = nodeArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetSwiperModifier().ResetSwiperNextMargin(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue SwiperBridge::SetSwiperPrevMargin(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_NODE_INDEX);
    void* nativeNode = nodeArg->ToNativePointer(vm)->Value();
    Local<JSValueRef> valueArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_VALUE_INDEX);
    Ace::CalcDimension prevMargin;
    if (!ArkTSUtils::ParseJsDimension(vm, valueArg, prevMargin, DimensionUnit::VP) || valueArg->IsNull() ||
        valueArg->IsUndefined() || LessNotEqual(prevMargin.Value(), 0.0)) {
        prevMargin.SetValue(0.0);
    }
    int32_t prevMarginUnit = static_cast<int32_t>(prevMargin.Unit());
    GetArkUIInternalNodeAPI()->GetSwiperModifier().SetSwiperPrevMargin(nativeNode, prevMargin.Value(), prevMarginUnit);
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue SwiperBridge::ResetSwiperPrevMargin(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_NODE_INDEX);
    void* nativeNode = nodeArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetSwiperModifier().ResetSwiperPrevMargin(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue SwiperBridge::SetSwiperDisplayCount(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_NODE_INDEX);
    void* nativeNode = nodeArg->ToNativePointer(vm)->Value();
    Local<JSValueRef> valueArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_VALUE_INDEX);
    Local<JSValueRef> typeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_TYPE_INDEX);
    std::string displayCountValue;
    std::string type = typeArg->ToString(vm)->ToString();
    if (type == "number") {
        displayCountValue = std::to_string(valueArg->Int32Value(vm));
    } else {
        displayCountValue = valueArg->ToString(vm)->ToString();
    }
    GetArkUIInternalNodeAPI()->GetSwiperModifier().SetSwiperDisplayCount(
        nativeNode, displayCountValue.c_str(), type.c_str());
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue SwiperBridge::ResetSwiperDisplayCount(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_NODE_INDEX);
    void* nativeNode = nodeArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetSwiperModifier().ResetSwiperDisplayCount(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue SwiperBridge::SetSwiperDisplayArrow(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_NODE_INDEX);
    void* nativeNode = nodeArg->ToNativePointer(vm)->Value();
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
    std::string backgroundSizeStr =
        ArkTSUtils::ParseJsDimension(vm, backgroundSize, lengthValue, DimensionUnit::VP, false)
            ? std::to_string(lengthValue.Value()) + "vp" : "-";
    std::string backgroundColorStr =
        ArkTSUtils::ParseJsColorAlpha(vm, backgroundColor, color) ? std::to_string(color.GetValue()) : "-";
    std::string arrowSizeStr = ArkTSUtils::ParseJsDimension(vm, arrowSize, lengthValue, DimensionUnit::VP, false)
                                   ? std::to_string(lengthValue.Value()) + "vp" : "-";
    std::string arrowColorStr =
        ArkTSUtils::ParseJsColorAlpha(vm, arrowColor, color) ? std::to_string(color.GetValue()) : "-";
    std::string isHoverShowStr = "2";
    if (!isHoverShow->IsUndefined()) {
        isHoverShowStr = isHoverShow->ToBoolean(vm)->Value() ? "1" : "0";
    }
    std::string displayArrowStr = displayArrowValueStr + "|" + showBackgroundStr + "|" + isSidebarMiddleStr + "|" +
                                  backgroundSizeStr + "|" + backgroundColorStr + "|" + arrowSizeStr + "|" +
                                  arrowColorStr + "|" + isHoverShowStr + "|";
    GetArkUIInternalNodeAPI()->GetSwiperModifier().SetSwiperDisplayArrow(nativeNode, displayArrowStr.c_str());
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue SwiperBridge::ResetSwiperDisplayArrow(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_NODE_INDEX);
    void* nativeNode = nodeArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetSwiperModifier().ResetSwiperDisplayArrow(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue SwiperBridge::SetSwiperCurve(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_NODE_INDEX);
    void* nativeNode = nodeArg->ToNativePointer(vm)->Value();
    Local<JSValueRef> valueArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_VALUE_INDEX);
    std::string curve = valueArg->ToString(vm)->ToString();
    GetArkUIInternalNodeAPI()->GetSwiperModifier().SetSwiperCurve(nativeNode, curve.c_str());
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue SwiperBridge::ResetSwiperCurve(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_NODE_INDEX);
    void* nativeNode = nodeArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetSwiperModifier().ResetSwiperCurve(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue SwiperBridge::SetSwiperDisableSwipe(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_NODE_INDEX);
    void* nativeNode = nodeArg->ToNativePointer(vm)->Value();
    Local<JSValueRef> valueArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_VALUE_INDEX);
    bool disableswipe = valueArg->ToBoolean(vm)->Value();
    GetArkUIInternalNodeAPI()->GetSwiperModifier().SetSwiperDisableSwipe(nativeNode, disableswipe);
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue SwiperBridge::ResetSwiperDisableSwipe(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_NODE_INDEX);
    void* nativeNode = nodeArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetSwiperModifier().ResetSwiperDisableSwipe(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue SwiperBridge::SetSwiperEffectMode(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_NODE_INDEX);
    void* nativeNode = nodeArg->ToNativePointer(vm)->Value();
    Local<JSValueRef> valueArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_VALUE_INDEX);
    auto edgeEffect = valueArg->Int32Value(vm);
    GetArkUIInternalNodeAPI()->GetSwiperModifier().SetSwiperEffectMode(nativeNode, edgeEffect);
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue SwiperBridge::ResetSwiperEffectMode(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_NODE_INDEX);
    void* nativeNode = nodeArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetSwiperModifier().ResetSwiperEffectMode(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue SwiperBridge::SetSwiperCachedCount(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_NODE_INDEX);
    void* nativeNode = nodeArg->ToNativePointer(vm)->Value();
    Local<JSValueRef> valueArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_VALUE_INDEX);
    int32_t cachedCount = valueArg->Int32Value(vm);
    GetArkUIInternalNodeAPI()->GetSwiperModifier().SetSwiperCachedCount(nativeNode, cachedCount);
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue SwiperBridge::ResetSwiperCachedCount(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_NODE_INDEX);
    void* nativeNode = nodeArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetSwiperModifier().ResetSwiperCachedCount(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue SwiperBridge::SetSwiperDisplayMode(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_NODE_INDEX);
    void* nativeNode = nodeArg->ToNativePointer(vm)->Value();
    Local<JSValueRef> valueArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_VALUE_INDEX);
    int32_t index = valueArg->Int32Value(vm);
    GetArkUIInternalNodeAPI()->GetSwiperModifier().SetSwiperDisplayMode(nativeNode, index);
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue SwiperBridge::ResetSwiperDisplayMode(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_NODE_INDEX);
    void* nativeNode = nodeArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetSwiperModifier().ResetSwiperDisplayMode(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue SwiperBridge::SetSwiperItemSpace(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_NODE_INDEX);
    void* nativeNode = nodeArg->ToNativePointer(vm)->Value();
    Local<JSValueRef> valueArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_VALUE_INDEX);
    Ace::CalcDimension itemSpace;
    if (!ArkTSUtils::ParseJsDimensionVpNG(vm, valueArg, itemSpace) || LessNotEqual(itemSpace.Value(), 0.0)) {
        itemSpace.SetValue(0.0);
    }
    int32_t itemSpaceUnit = static_cast<int32_t>(itemSpace.Unit());
    GetArkUIInternalNodeAPI()->GetSwiperModifier().SetSwiperItemSpace(nativeNode, itemSpace.Value(), itemSpaceUnit);
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue SwiperBridge::ResetSwiperItemSpace(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_NODE_INDEX);
    void* nativeNode = nodeArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetSwiperModifier().ResetSwiperItemSpace(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue SwiperBridge::SetSwiperVertical(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_NODE_INDEX);
    void* nativeNode = nodeArg->ToNativePointer(vm)->Value();
    Local<JSValueRef> valueArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_VALUE_INDEX);
    bool isVertical = valueArg->ToBoolean(vm)->Value();
    GetArkUIInternalNodeAPI()->GetSwiperModifier().SetSwiperVertical(nativeNode, isVertical);
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue SwiperBridge::ResetSwiperVertical(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_NODE_INDEX);
    void* nativeNode = nodeArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetSwiperModifier().ResetSwiperVertical(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue SwiperBridge::SetSwiperLoop(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_NODE_INDEX);
    void* nativeNode = nodeArg->ToNativePointer(vm)->Value();
    Local<JSValueRef> valueArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_VALUE_INDEX);
    bool loop = valueArg->ToBoolean(vm)->Value();
    GetArkUIInternalNodeAPI()->GetSwiperModifier().SetSwiperLoop(nativeNode, loop);
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue SwiperBridge::ResetSwiperLoop(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_NODE_INDEX);
    void* nativeNode = nodeArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetSwiperModifier().ResetSwiperLoop(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue SwiperBridge::SetSwiperInterval(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_NODE_INDEX);
    void* nativeNode = nodeArg->ToNativePointer(vm)->Value();
    Local<JSValueRef> valueArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_VALUE_INDEX);
    int32_t interval = valueArg->Int32Value(vm);
    GetArkUIInternalNodeAPI()->GetSwiperModifier().SetSwiperInterval(nativeNode, interval);
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue SwiperBridge::ResetSwiperInterval(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_NODE_INDEX);
    void* nativeNode = nodeArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetSwiperModifier().ResetSwiperInterval(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue SwiperBridge::SetSwiperAutoPlay(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_NODE_INDEX);
    void* nativeNode = nodeArg->ToNativePointer(vm)->Value();
    Local<JSValueRef> valueArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_VALUE_INDEX);
    bool autoPlay = valueArg->ToBoolean(vm)->Value();
    GetArkUIInternalNodeAPI()->GetSwiperModifier().SetSwiperAutoPlay(nativeNode, autoPlay);
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue SwiperBridge::ResetSwiperAutoPlay(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_NODE_INDEX);
    void* nativeNode = nodeArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetSwiperModifier().ResetSwiperAutoPlay(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue SwiperBridge::SetSwiperIndex(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_NODE_INDEX);
    void* nativeNode = nodeArg->ToNativePointer(vm)->Value();
    Local<JSValueRef> valueArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_VALUE_INDEX);
    int32_t index = valueArg->Int32Value(vm);
    GetArkUIInternalNodeAPI()->GetSwiperModifier().SetSwiperIndex(nativeNode, index);
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue SwiperBridge::ResetSwiperIndex(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_NODE_INDEX);
    void* nativeNode = nodeArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetSwiperModifier().ResetSwiperIndex(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
std::string GetStringByValueRef(const EcmaVM* vm, const Local<JSValueRef>& jsValue)
{
    CalcDimension calc;
    std::string result =
        ArkTSUtils::ParseJsDimension(vm, jsValue, calc, DimensionUnit::VP, true)
            ? (calc.Unit() == DimensionUnit::PERCENT ? (std::to_string(calc.Value() * DEFAULT_PERCENT_VALUE) + "%")
                                                     : (std::to_string(calc.Value()) + "vp")) : "-";
    return result;
}
std::string GetSwiperDotIndicator(ArkUIRuntimeCallInfo* runtimeCallInfo, EcmaVM* vm)
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
                                ? std::to_string(calc.Value()) + "vp" : "-";
    std::string itemHeight = ArkTSUtils::ParseJsDimension(vm, itemHeightArg, calc, DimensionUnit::VP, false)
                                 ? std::to_string(calc.Value()) + "vp" : "-";
    std::string selectedItemWidth =
        ArkTSUtils::ParseJsDimension(vm, selectedItemWidthArg, calc, DimensionUnit::VP, false)
            ? std::to_string(calc.Value()) + "vp" : "-";
    std::string selectedItemHeight =
        ArkTSUtils::ParseJsDimension(vm, selectedItemHeightArg, calc, DimensionUnit::VP, false)
            ? std::to_string(calc.Value()) + "vp" : "-";
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
    std::string indicatorStr = itemWidth + "|" + itemHeight + "|" + selectedItemWidth + "|" +
                               selectedItemHeight + "|" + mask + "|" + colorStr + "|" + selectedColor + "|" + left +
                               "|" + top + "|" + right + "|" + bottom;
    return indicatorStr;
}
std::string GetSwiperDigitIndicator(ArkUIRuntimeCallInfo* runtimeCallInfo, EcmaVM* vm)
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
    std::string digitFontSize = ArkTSUtils::ParseJsDimension(vm, digitFontSizeArg, calc, DimensionUnit::VP, false)
                                    ? std::to_string(calc.Value()) + "vp" : "-";
    std::string digitFontWeight = digitFontWeightArg->ToString(vm)->ToString();
    std::string selectedDigitFontSize =
        ArkTSUtils::ParseJsDimension(vm, selectedDigitFontSizeArg, calc, DimensionUnit::VP, false)
            ? std::to_string(calc.Value()) + "vp" : "-";
    std::string selectedDigitFontWeight = selectedDigitFontWeightArg->ToString(vm)->ToString();
    std::string left = GetStringByValueRef(vm, leftArg);
    std::string top = GetStringByValueRef(vm, topArg);
    std::string right = GetStringByValueRef(vm, rightArg);
    std::string bottom = GetStringByValueRef(vm, bottomArg);
    std::string indicatorStr = fontColor + "|" + selectedFontColor + "|" + digitFontSize + "|" + digitFontWeight +
                   "|" + selectedDigitFontSize + "|" + selectedDigitFontWeight + "|" + left + "|" + top + "|" + right +
                   "|" + bottom;
    return indicatorStr;
}
ArkUINativeModuleValue SwiperBridge::SetSwiperIndicator(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_NODE_INDEX);
    void* nativeNode = nodeArg->ToNativePointer(vm)->Value();
    Local<JSValueRef> valueArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_VALUE_INDEX);

    std::string type = valueArg->ToString(vm)->ToString();
    std::string indicatorStr = "";
    if (type == "boolean") {
        Local<JSValueRef> indicatorArg = runtimeCallInfo->GetCallArgRef(INDICATOR_VALUE_INDEX);
        std::string indicator = indicatorArg->ToBoolean(vm)->Value() ? "1" : "0";
        indicatorStr = type + "|" + indicator;
    } else if (type == "ArkDotIndicator") {
        indicatorStr = type + "|" + GetSwiperDotIndicator(runtimeCallInfo, vm);
    } else {
        indicatorStr = type + "|" + GetSwiperDigitIndicator(runtimeCallInfo, vm);
    }
    GetArkUIInternalNodeAPI()->GetSwiperModifier().SetSwiperIndicator(nativeNode, indicatorStr.c_str());
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue SwiperBridge::ResetSwiperIndicator(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_NODE_INDEX);
    void* nativeNode = nodeArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetSwiperModifier().ResetSwiperIndicator(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue SwiperBridge::SetSwiperDuration(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_NODE_INDEX);
    void* nativeNode = nodeArg->ToNativePointer(vm)->Value();
    Local<JSValueRef> valueArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_VALUE_INDEX);
    int32_t duration = valueArg->Int32Value(vm);
    GetArkUIInternalNodeAPI()->GetSwiperModifier().SetSwiperDuration(nativeNode, duration);
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue SwiperBridge::ResetSwiperDuration(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_NODE_INDEX);
    void* nativeNode = nodeArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetSwiperModifier().ResetSwiperDuration(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
} // namespace OHOS::Ace::NG