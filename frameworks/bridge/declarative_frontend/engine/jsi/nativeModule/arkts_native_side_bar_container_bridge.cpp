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
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_side_bar_container_bridge.h"

#include "base/geometry/calc_dimension.h"
#include "base/geometry/dimension.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"

namespace OHOS::Ace::NG {
constexpr int NUM_0 = 0;
constexpr int NUM_1 = 1;
constexpr int NUM_2 = 2;
constexpr int NUM_3 = 3;
constexpr int NUM_4 = 4;
constexpr int NUM_5 = 5;
constexpr int NUM_6 = 6;
constexpr int NUM_7 = 7;
constexpr uint32_t DEFAULT_SIDE_BAR_DIVIDER_COLOR = 0x08000000;
const CalcDimension DEFAULT_MAX_SIDE_BAR_WIDTH(280.0, DimensionUnit::VP);
const CalcDimension DEFAULT_SIDE_BAR_MIN_CONTENT_WIDTH(360.0, DimensionUnit::VP);
const Dimension DEFAULT_CONTROL_BUTTON_WIDTH = 32.0_vp;
const Dimension DEFAULT_CONTROL_BUTTON_WIDTH_V10 = 24.0_vp;
const Dimension DEFAULT_CONTROL_BUTTON_HEIGHT = 32.0_vp;
const Dimension DEFAULT_CONTROL_BUTTON_HEIGHT_V10 = 24.0_vp;
constexpr Dimension DEFAULT_CONTROL_BUTTON_LEFT = 16.0_vp;
constexpr Dimension DEFAULT_CONTROL_BUTTON_TOP = 48.0_vp;
ArkUINativeModuleValue SideBarContainerBridge::SetSideBarWidth(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> sideBarWidthArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    auto nativeNode = nodePtr(nativeNodeArg->ToNativePointer(vm)->Value());
    CalcDimension sideBarWidth;
    RefPtr<ResourceObject> sideBarWidthResObj;
    if (ArkTSUtils::ParseJsDimensionNG(
        vm, sideBarWidthArg, sideBarWidth, DimensionUnit::VP, sideBarWidthResObj, true) &&
        sideBarWidth.Value() >= 0) {
        auto widthRawPtr = AceType::RawPtr(sideBarWidthResObj);
        GetArkUINodeModifiers()->getSideBarContainerModifier()->setSideBarWidth(
            nativeNode, sideBarWidth.Value(), static_cast<int32_t>(sideBarWidth.Unit()), widthRawPtr);
    } else {
        GetArkUINodeModifiers()->getSideBarContainerModifier()->resetSideBarWidth(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SideBarContainerBridge::ResetSideBarWidth(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(nativeNodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getSideBarContainerModifier()->resetSideBarWidth(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SideBarContainerBridge::SetMinSideBarWidth(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> minSideBarWidthArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    auto nativeNode = nodePtr(nativeNodeArg->ToNativePointer(vm)->Value());
    CalcDimension minSideBarWidth;
    RefPtr<ResourceObject> minSideBarWidthObj;
    if (ArkTSUtils::ParseJsDimensionNG(
        vm, minSideBarWidthArg, minSideBarWidth, DimensionUnit::VP, minSideBarWidthObj, true) &&
        minSideBarWidth.Value() >= 0) {
        auto minWidthRawPtr = AceType::RawPtr(minSideBarWidthObj);
        GetArkUINodeModifiers()->getSideBarContainerModifier()->setMinSideBarWidth(
            nativeNode, minSideBarWidth.Value(), static_cast<int32_t>(minSideBarWidth.Unit()), minWidthRawPtr);
    } else {
        GetArkUINodeModifiers()->getSideBarContainerModifier()->resetMinSideBarWidth(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SideBarContainerBridge::ResetMinSideBarWidth(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(nativeNodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getSideBarContainerModifier()->resetMinSideBarWidth(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SideBarContainerBridge::SetControlButton(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> leftArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> topArg = runtimeCallInfo->GetCallArgRef(NUM_2);
    Local<JSValueRef> widthArg = runtimeCallInfo->GetCallArgRef(NUM_3);
    Local<JSValueRef> heightArg = runtimeCallInfo->GetCallArgRef(NUM_4);
    Local<JSValueRef> iconsShownArg = runtimeCallInfo->GetCallArgRef(NUM_5);
    Local<JSValueRef> iconsHiddenArg = runtimeCallInfo->GetCallArgRef(NUM_6);
    Local<JSValueRef> iconsSwitchingArg = runtimeCallInfo->GetCallArgRef(NUM_7);
    ArkUI_Float32 values[NUM_4];
    auto nativeNode = nodePtr(nativeNodeArg->ToNativePointer(vm)->Value());
    if (leftArg->IsNumber() && leftArg->ToNumber(vm)->Value() >= 0) {
        values[NUM_0] = leftArg->ToNumber(vm)->Value();
    } else {
        values[NUM_0] = DEFAULT_CONTROL_BUTTON_LEFT.Value();
    }
    if (topArg->IsNumber() && topArg->ToNumber(vm)->Value() >= 0) {
        values[NUM_1] = topArg->ToNumber(vm)->Value();
    } else {
        values[NUM_1] = DEFAULT_CONTROL_BUTTON_TOP.Value();
    }
    if (widthArg->IsNumber() && widthArg->ToNumber(vm)->Value() >= 0) {
        values[NUM_2] = widthArg->ToNumber(vm)->Value();
    } else {
        if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_TEN)) {
            values[NUM_2] = DEFAULT_CONTROL_BUTTON_WIDTH_V10.Value();
        } else {
            values[NUM_2] = DEFAULT_CONTROL_BUTTON_WIDTH.Value();
        }
    }
    if (heightArg->IsNumber() && heightArg->ToNumber(vm)->Value() >= 0) {
        values[NUM_3] = heightArg->ToNumber(vm)->Value();
    } else {
        if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_TEN)) {
            values[NUM_3] = DEFAULT_CONTROL_BUTTON_HEIGHT_V10.Value();
        } else {
            values[NUM_3] = DEFAULT_CONTROL_BUTTON_HEIGHT.Value();
        }
    }
    std::string iconsShown;
    std::string iconsHidden;
    std::string iconsSwitching;
    RefPtr<ResourceObject> iconsShownObj;
    RefPtr<ResourceObject> iconsHiddenObj;
    RefPtr<ResourceObject> iconsSwitchingObj;
    struct ArkUIIconsStruct iconsStruct {
        nullptr, nullptr, nullptr
    };
    if (ArkTSUtils::ParseJsMedia(vm, iconsShownArg, iconsShown, iconsShownObj)) {
        iconsStruct.ShowIconInfo = iconsShown.c_str();
    }
    if (ArkTSUtils::ParseJsMedia(vm, iconsHiddenArg, iconsHidden, iconsHiddenObj)) {
        iconsStruct.HiddenIconInfo = iconsHidden.c_str();
    }
    if (ArkTSUtils::ParseJsMedia(vm, iconsSwitchingArg, iconsSwitching, iconsSwitchingObj)) {
        iconsStruct.SwitchingIconInfo = iconsSwitching.c_str();
    }
    auto iconsShownPtr = AceType::RawPtr(iconsShownObj);
    auto iconsHiddenPtr = AceType::RawPtr(iconsHiddenObj);
    auto iconsSwitchingPtr = AceType::RawPtr(iconsSwitchingObj);
    GetArkUINodeModifiers()->getSideBarContainerModifier()->setControlButton(nativeNode, values, NUM_4, &iconsStruct,
        iconsShownPtr, iconsHiddenPtr, iconsSwitchingPtr);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SideBarContainerBridge::ResetControlButton(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(nativeNodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getSideBarContainerModifier()->resetControlButton(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SideBarContainerBridge::SetShowControlButton(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> showControlButtonArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    auto nativeNode = nodePtr(nativeNodeArg->ToNativePointer(vm)->Value());
    bool isShow = true;
    if (showControlButtonArg->IsBoolean()) {
        isShow = showControlButtonArg->ToBoolean(vm)->Value();
        GetArkUINodeModifiers()->getSideBarContainerModifier()->setShowControlButton(nativeNode, isShow);
    } else {
        GetArkUINodeModifiers()->getSideBarContainerModifier()->resetShowControlButton(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SideBarContainerBridge::ResetShowControlButton(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(nativeNodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getSideBarContainerModifier()->resetShowControlButton(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SideBarContainerBridge::SetAutoHide(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> autoHideArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    auto nativeNode = nodePtr(nativeNodeArg->ToNativePointer(vm)->Value());
    if (autoHideArg->IsBoolean()) {
        uint32_t value = static_cast<uint32_t>(autoHideArg->ToBoolean(vm)->Value());
        GetArkUINodeModifiers()->getSideBarContainerModifier()->setAutoHide(nativeNode, value);
    } else {
        GetArkUINodeModifiers()->getSideBarContainerModifier()->resetAutoHide(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SideBarContainerBridge::ResetAutoHide(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(nativeNodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getSideBarContainerModifier()->resetAutoHide(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SideBarContainerBridge::SetMaxSideBarWidth(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> maxSideBarWidthArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    auto nativeNode = nodePtr(nativeNodeArg->ToNativePointer(vm)->Value());
    CalcDimension maxSideBarWidth(DEFAULT_MAX_SIDE_BAR_WIDTH);
    RefPtr<ResourceObject> maxSideBarWidthObj;
    if (ArkTSUtils::ParseJsDimensionNG(
        vm, maxSideBarWidthArg, maxSideBarWidth, DimensionUnit::VP, maxSideBarWidthObj, true) &&
        maxSideBarWidth.Value() >= 0) {
        auto maxSideBarWidthPtr = AceType::RawPtr(maxSideBarWidthObj);
        GetArkUINodeModifiers()->getSideBarContainerModifier()->setSideBarContainerMaxSideBarWidth(
            nativeNode, maxSideBarWidth.Value(), static_cast<int32_t>(maxSideBarWidth.Unit()), maxSideBarWidthPtr);
    } else {
        GetArkUINodeModifiers()->getSideBarContainerModifier()->resetSideBarContainerMaxSideBarWidth(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SideBarContainerBridge::ResetMaxSideBarWidth(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(nativeNodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getSideBarContainerModifier()->resetSideBarContainerMaxSideBarWidth(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SideBarContainerBridge::SetMinContentWidth(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> minContentWidthArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    auto nativeNode = nodePtr(nativeNodeArg->ToNativePointer(vm)->Value());
    CalcDimension minContentWidth(DEFAULT_SIDE_BAR_MIN_CONTENT_WIDTH);
    RefPtr<ResourceObject> minContentWidthObj;
    if (ArkTSUtils::ParseJsDimensionNG(
        vm, minContentWidthArg, minContentWidth, DimensionUnit::VP, minContentWidthObj, true) &&
        minContentWidth.Value() >= 0) {
        auto minContentWidthPtr = AceType::RawPtr(minContentWidthObj);
        GetArkUINodeModifiers()->getSideBarContainerModifier()->setSideBarContainerMinContentWidth(
            nativeNode, minContentWidth.Value(), static_cast<int32_t>(minContentWidth.Unit()), minContentWidthPtr);
    } else {
        GetArkUINodeModifiers()->getSideBarContainerModifier()->resetSideBarContainerMinContentWidth(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SideBarContainerBridge::ResetMinContentWidth(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(nativeNodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getSideBarContainerModifier()->resetSideBarContainerMinContentWidth(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SideBarContainerBridge::SetSideBarPosition(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> sideBarPositionArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    auto nativeNode = nodePtr(nativeNodeArg->ToNativePointer(vm)->Value());
    int32_t sideBarPosition = static_cast<int32_t>(SideBarPosition::START);
    if (sideBarPositionArg->IsInt()) {
        sideBarPosition = sideBarPositionArg->Int32Value(vm);
    }
    if (sideBarPosition < static_cast<int32_t>(SideBarPosition::START) ||
        sideBarPosition > static_cast<int32_t>(SideBarPosition::END)) {
        GetArkUINodeModifiers()->getSideBarContainerModifier()->resetSideBarPosition(nativeNode);
    } else {
        GetArkUINodeModifiers()->getSideBarContainerModifier()->setSideBarPosition(nativeNode, sideBarPosition);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SideBarContainerBridge::ResetSideBarPosition(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(nativeNodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getSideBarContainerModifier()->resetSideBarPosition(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SideBarContainerBridge::SetShowSideBar(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> showSideBarArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    auto nativeNode = nodePtr(nativeNodeArg->ToNativePointer(vm)->Value());
    if (showSideBarArg->IsBoolean()) {
        bool isShow = showSideBarArg->ToBoolean(vm)->Value();
        GetArkUINodeModifiers()->getSideBarContainerModifier()->setShowSideBar(nativeNode, isShow);
    } else {
        GetArkUINodeModifiers()->getSideBarContainerModifier()->resetShowSideBar(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SideBarContainerBridge::ResetShowSideBar(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(nativeNodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getSideBarContainerModifier()->resetShowSideBar(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SideBarContainerBridge::SetDivider(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> strokeWidthArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> colorArg = runtimeCallInfo->GetCallArgRef(NUM_2);
    Local<JSValueRef> startMarginArg = runtimeCallInfo->GetCallArgRef(NUM_3);
    Local<JSValueRef> endMarginArg = runtimeCallInfo->GetCallArgRef(NUM_4);
    auto nativeNode = nodePtr(nativeNodeArg->ToNativePointer(vm)->Value());
    CalcDimension strokeWidth;
    CalcDimension startMargin;
    CalcDimension endMargin;
    RefPtr<ResourceObject> strokeWidthObj;
    RefPtr<ResourceObject> startMarginObj;
    RefPtr<ResourceObject> endMarginObj;
    RefPtr<ResourceObject> colorObj;
    ArkUI_Float32 values[NUM_3] = { 1.0, 0.0, 0.0 };
    int32_t units[NUM_3] = { static_cast<int32_t>(DimensionUnit::VP) };
    if (ArkTSUtils::ParseJsDimensionNG(vm, strokeWidthArg, strokeWidth, DimensionUnit::VP, strokeWidthObj, true) &&
        strokeWidth.Value() >= 0) {
        values[NUM_0] = strokeWidth.Value();
        units[NUM_0] = static_cast<int32_t>(strokeWidth.Unit());
    } else {
        strokeWidth.SetValue(1.0);
        strokeWidth.SetUnit(DimensionUnit::VP);
    }
    if (ArkTSUtils::ParseJsDimensionNG(vm, startMarginArg, startMargin, DimensionUnit::VP, startMarginObj, true) &&
        startMargin.Value() >= 0) {
        values[NUM_1] = startMargin.Value();
        units[NUM_1] = static_cast<int32_t>(startMargin.Unit());
    } else {
        startMargin.SetValue(0.0);
        startMargin.SetUnit(DimensionUnit::VP);
    }
    if (ArkTSUtils::ParseJsDimensionNG(vm, endMarginArg, endMargin, DimensionUnit::VP, endMarginObj, true) &&
        endMargin.Value() >= 0) {
        values[NUM_2] = endMargin.Value();
        units[NUM_2] = static_cast<int32_t>(endMargin.Unit());
    } else {
        endMargin.SetValue(0.0);
        endMargin.SetUnit(DimensionUnit::VP);
    }

    Color color(DEFAULT_SIDE_BAR_DIVIDER_COLOR);
    auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(nativeNode);
    if (!ArkTSUtils::ParseJsColorAlpha(vm, colorArg, color, colorObj, nodeInfo)) {
        color.SetValue(DEFAULT_SIDE_BAR_DIVIDER_COLOR);
    }
    auto strokeWidthPtr = AceType::RawPtr(strokeWidthObj);
    auto startMarginPtr = AceType::RawPtr(startMarginObj);
    auto endMarginPtr = AceType::RawPtr(endMarginObj);
    auto colorPtr = AceType::RawPtr(colorObj);
    GetArkUINodeModifiers()->getSideBarContainerModifier()->setSideBarContainerDivider(
        nativeNode, values, units, NUM_3, color.GetValue(), strokeWidthPtr, startMarginPtr, endMarginPtr, colorPtr);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SideBarContainerBridge::ResetDivider(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(nativeNodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getSideBarContainerModifier()->resetSideBarContainerDivider(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SideBarContainerBridge::SetSideBarOnChange(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::NativePointerRef::New(vm, nullptr));
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::NativePointerRef::New(vm, nullptr));
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        nodeModifiers->getSideBarContainerModifier()->resetSideBarOnChange(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<void(bool)> callback = [vm, frameNode,
        func = panda::CopyableGlobal(vm, func)](bool isOnChange) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
        panda::Local<panda::JSValueRef> params[1] = {
            panda::BooleanRef::New(vm, isOnChange) };
        func->Call(vm, func.ToLocal(), params, 1);
    };
    nodeModifiers->getSideBarContainerModifier()->setSideBarOnChange(
        nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SideBarContainerBridge::ResetSideBarOnChange(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::NativePointerRef::New(vm, nullptr));
    nodeModifiers->getSideBarContainerModifier()->resetSideBarOnChange(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
} // namespace OHOS::Ace::NG
