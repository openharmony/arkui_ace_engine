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
#include "bridge/declarative_frontend/engine/jsi/components/arkts_native_api.h"

namespace OHOS::Ace::NG {
constexpr int NUM_0 = 0;
constexpr int NUM_1 = 1;
constexpr int NUM_2 = 2;
constexpr int NUM_3 = 3;
constexpr int NUM_4 = 4;
constexpr int NUM_5 = 5;
constexpr int NUM_6 = 6;
constexpr int NUM_7 = 7;
constexpr uint32_t COLOR_ALPHA_OFFSET = 24;
constexpr uint32_t COLOR_ALPHA_VALUE = 0xFF000000;
constexpr uint32_t DEFAULT_SIDE_BAR_DIVIDER_COLOR = 0x08000000;
const CalcDimension DEFAULT_MAX_SIDE_BAR_WIDTH(280.0, DimensionUnit::VP);
const CalcDimension DEFAULT_SIDE_BAR_MIN_CONTENT_WIDTH(360.0, DimensionUnit::VP);
static bool ParseJsDimensionNG(const EcmaVM* vm, const Local<JSValueRef>& jsValue, CalcDimension& result,
    DimensionUnit defaultUnit, bool isSupportPercent = true)
{
    if (jsValue->IsNumber()) {
        result = CalcDimension(jsValue->ToNumber(vm)->Value(), defaultUnit);
        return true;
    }
    if (jsValue->IsString()) {
        auto value = jsValue->ToString(vm)->ToString();
        if (value.back() == '%' && !isSupportPercent) {
            return false;
        }
        return StringUtils::StringToCalcDimensionNG(jsValue->ToString(vm)->ToString(), result, false, defaultUnit);
    }
    // resouce ignore by design
    return false;
}

static uint32_t ColorAlphaAdapt(uint32_t origin)
{
    uint32_t result = origin;
    if ((origin >> COLOR_ALPHA_OFFSET) == 0) {
        result = origin | COLOR_ALPHA_VALUE;
    }
    return result;
}

static bool ParseJsColor(const EcmaVM* vm, const Local<JSValueRef>& value, Color& result)
{
    if (value->IsNumber()) {
        result = Color(ColorAlphaAdapt(value->Uint32Value(vm)));
        return true;
    }
    if (value->IsString()) {
        return Color::ParseColorString(value->ToString(vm)->ToString(), result);
    }
    // resouce ignore by design
    return false;
}

ArkUINativeModuleValue SideBarContainerBridge::SetSideBarWidth(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> sideBarWidthArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    void* nativeNode = nativeNodeArg->ToNativePointer(vm)->Value();
    struct StringAndDouble sideBarWidth {
        0.0, nullptr
    };
    if (sideBarWidthArg->IsNumber()) {
        sideBarWidth.value = sideBarWidthArg->ToNumber(vm)->Value();
        GetArkUIInternalNodeAPI()->GetSideBarContainerModifier().SetSideBarWidth(nativeNode, &sideBarWidth);
    } else if (sideBarWidthArg->IsString()) {
        sideBarWidth.valueStr = sideBarWidthArg->ToString(vm)->ToString().c_str();
        GetArkUIInternalNodeAPI()->GetSideBarContainerModifier().SetSideBarWidth(nativeNode, &sideBarWidth);
    } else {
        GetArkUIInternalNodeAPI()->GetSideBarContainerModifier().ResetSideBarWidth(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SideBarContainerBridge::ResetSideBarWidth(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    void* nativeNode = nativeNodeArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetSideBarContainerModifier().ResetSideBarWidth(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SideBarContainerBridge::SetMinSideBarWidth(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> minSideBarWidthArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    void* nativeNode = nativeNodeArg->ToNativePointer(vm)->Value();
    struct StringAndDouble minSideBarWidth {
        0.0, nullptr
    };
    if (minSideBarWidthArg->IsNumber()) {
        minSideBarWidth.value = minSideBarWidthArg->ToNumber(vm)->Value();
        GetArkUIInternalNodeAPI()->GetSideBarContainerModifier().SetMinSideBarWidth(nativeNode, &minSideBarWidth);
    } else if (minSideBarWidthArg->IsString()) {
        minSideBarWidth.valueStr = minSideBarWidthArg->ToString(vm)->ToString().c_str();
        GetArkUIInternalNodeAPI()->GetSideBarContainerModifier().SetMinSideBarWidth(nativeNode, &minSideBarWidth);
    } else {
        GetArkUIInternalNodeAPI()->GetSideBarContainerModifier().ResetMinSideBarWidth(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SideBarContainerBridge::ResetMinSideBarWidth(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    void* nativeNode = nativeNodeArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetSideBarContainerModifier().ResetMinSideBarWidth(nativeNode);
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
    double values[NUM_4];
    struct IconsStruct iconsStruct {
        nullptr, nullptr, nullptr
    };
    void* nativeNode = nativeNodeArg->ToNativePointer(vm)->Value();
    values[NUM_0] = leftArg->ToNumber(vm)->Value();
    values[NUM_1] = topArg->ToNumber(vm)->Value();
    values[NUM_2] = widthArg->ToNumber(vm)->Value();
    values[NUM_3] = heightArg->ToNumber(vm)->Value();
    if (!iconsShownArg->IsString()) {
        iconsStruct.ShowIconInfo = nullptr;
    } else {
        iconsStruct.ShowIconInfo = iconsShownArg->ToString(vm)->ToString().c_str();
    }
    if (!iconsHiddenArg->IsString()) {
        iconsStruct.HiddenIconInfo = nullptr;
    } else {
        iconsStruct.HiddenIconInfo = iconsHiddenArg->ToString(vm)->ToString().c_str();
    }
    if (!iconsSwitchingArg->IsString()) {
        iconsStruct.SwitchingIconInfo = nullptr;
    } else {
        iconsStruct.SwitchingIconInfo = iconsSwitchingArg->ToString(vm)->ToString().c_str();
    }
    GetArkUIInternalNodeAPI()->GetSideBarContainerModifier().SetControlButton(nativeNode, values, &iconsStruct);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SideBarContainerBridge::ResetControlButton(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    void* nativeNode = nativeNodeArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetSideBarContainerModifier().ResetControlButton(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SideBarContainerBridge::SetShowControlButton(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> showControlButtonArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    void* nativeNode = nativeNodeArg->ToNativePointer(vm)->Value();
    bool isShow = true;
    if (showControlButtonArg->IsBoolean()) {
        isShow = showControlButtonArg->ToBoolean(vm)->Value();
        GetArkUIInternalNodeAPI()->GetSideBarContainerModifier().SetShowControlButton(nativeNode, isShow);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SideBarContainerBridge::ResetShowControlButton(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    void* nativeNode = nativeNodeArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetSideBarContainerModifier().ResetShowControlButton(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SideBarContainerBridge::SetAutoHide(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> autoHideArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    void* nativeNode = nativeNodeArg->ToNativePointer(vm)->Value();
    if (autoHideArg->IsBoolean()) {
        uint32_t value = static_cast<uint32_t>(autoHideArg->ToBoolean(vm)->Value());
        GetArkUIInternalNodeAPI()->GetSideBarContainerModifier().SetAutoHide(nativeNode, value);
    } else {
        GetArkUIInternalNodeAPI()->GetSideBarContainerModifier().ResetAutoHide(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SideBarContainerBridge::ResetAutoHide(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    void* nativeNode = nativeNodeArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetSideBarContainerModifier().ResetAutoHide(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SideBarContainerBridge::SetMaxSideBarWidth(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> maxSideBarWidthArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    void* nativeNode = nativeNodeArg->ToNativePointer(vm)->Value();
    CalcDimension maxSideBarWidth(DEFAULT_MAX_SIDE_BAR_WIDTH);
    if (ParseJsDimensionNG(vm, maxSideBarWidthArg, maxSideBarWidth, DimensionUnit::VP, true) &&
        maxSideBarWidth.Value() >= 0) {
        GetArkUIInternalNodeAPI()->GetSideBarContainerModifier().SetSideBarContainerMaxSideBarWidth(
            nativeNode, maxSideBarWidth.Value(), static_cast<int32_t>(maxSideBarWidth.Unit()));
    } else {
        GetArkUIInternalNodeAPI()->GetSideBarContainerModifier().ResetSideBarContainerMaxSideBarWidth(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SideBarContainerBridge::ResetMaxSideBarWidth(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    void* nativeNode = nativeNodeArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetSideBarContainerModifier().ResetSideBarContainerMaxSideBarWidth(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SideBarContainerBridge::SetMinContentWidth(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> minContentWidthArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    void* nativeNode = nativeNodeArg->ToNativePointer(vm)->Value();
    CalcDimension minContentWidth(DEFAULT_SIDE_BAR_MIN_CONTENT_WIDTH);
    if (ParseJsDimensionNG(vm, minContentWidthArg, minContentWidth, DimensionUnit::VP, true) &&
        minContentWidth.Value() >= 0) {
        GetArkUIInternalNodeAPI()->GetSideBarContainerModifier().SetSideBarContainerMinContentWidth(
            nativeNode, minContentWidth.Value(), static_cast<int32_t>(minContentWidth.Unit()));
    } else {
        GetArkUIInternalNodeAPI()->GetSideBarContainerModifier().ResetSideBarContainerMinContentWidth(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SideBarContainerBridge::ResetMinContentWidth(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    void* nativeNode = nativeNodeArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetSideBarContainerModifier().ResetSideBarContainerMinContentWidth(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SideBarContainerBridge::SetSideBarPosition(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> sideBarPositionArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    void* nativeNode = nativeNodeArg->ToNativePointer(vm)->Value();
    int32_t sideBarPosition = static_cast<int32_t>(SideBarPosition::START);
    if (sideBarPositionArg->IsInt()) {
        sideBarPosition = sideBarPositionArg->Int32Value(vm);
    }
    if (sideBarPosition < static_cast<int32_t>(SideBarPosition::START) ||
        sideBarPosition > static_cast<int32_t>(SideBarPosition::END)) {
        GetArkUIInternalNodeAPI()->GetSideBarContainerModifier().SetSideBarPosition(
            nativeNode, static_cast<int32_t>(SideBarPosition::START));
    } else {
        GetArkUIInternalNodeAPI()->GetSideBarContainerModifier().SetSideBarPosition(nativeNode, sideBarPosition);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SideBarContainerBridge::ResetSideBarPosition(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    void* nativeNode = nativeNodeArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetSideBarContainerModifier().ResetSideBarPosition(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SideBarContainerBridge::SetShowSideBar(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> showSideBarArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    void* nativeNode = nativeNodeArg->ToNativePointer(vm)->Value();
    if (showSideBarArg->IsBoolean()) {
        bool isShow = showSideBarArg->ToBoolean(vm)->Value();
        GetArkUIInternalNodeAPI()->GetSideBarContainerModifier().SetShowSideBar(nativeNode, isShow);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SideBarContainerBridge::ResetShowSideBar(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    void* nativeNode = nativeNodeArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetSideBarContainerModifier().ResetShowSideBar(nativeNode);
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
    void* nativeNode = nativeNodeArg->ToNativePointer(vm)->Value();
    struct StringAndDouble strokeWidth {
        0.0, nullptr
    };
    struct StringAndDouble startMargin {
        0.0, nullptr
    };
    struct StringAndDouble endMargin {
        0.0, nullptr
    };
    if (strokeWidthArg->IsNumber()) {
        strokeWidth.value = strokeWidthArg->ToNumber(vm)->Value();
    } else if (strokeWidthArg->IsString()) {
        strokeWidth.valueStr = strokeWidthArg->ToString(vm)->ToString().c_str();
    } else {
        return panda::JSValueRef::Undefined(vm);
    }
    Color color(DEFAULT_SIDE_BAR_DIVIDER_COLOR);
    if (!ParseJsColor(vm, colorArg, color)) {
        color.SetValue(DEFAULT_SIDE_BAR_DIVIDER_COLOR);
    }
    if (startMarginArg->IsNumber()) {
        startMargin.value = startMarginArg->ToNumber(vm)->Value();
    } else if (startMarginArg->IsString()) {
        startMargin.valueStr = startMarginArg->ToString(vm)->ToString().c_str();
    } else {
        startMargin.value = 0.0;
    }
    if (endMarginArg->IsNumber()) {
        endMargin.value = endMarginArg->ToNumber(vm)->Value();
    } else if (endMarginArg->IsString()) {
        endMargin.valueStr = endMarginArg->ToString(vm)->ToString().c_str();
    } else {
        endMargin.value = 0.0;
    }
    GetArkUIInternalNodeAPI()->GetSideBarContainerModifier().SetSideBarContainerDivider(
        nativeNode, &strokeWidth, color.GetValue(), &startMargin, &endMargin);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SideBarContainerBridge::ResetDivider(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    void* nativeNode = nativeNodeArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetSideBarContainerModifier().ResetSideBarContainerDivider(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
} // namespace OHOS::Ace::NG
