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
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_gauge_bridge.h"

#include "bridge/declarative_frontend/engine/jsi/components/arkts_native_api.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"
#include "core/components_ng/pattern/gauge/gauge_theme.h"

namespace OHOS::Ace::NG {
ArkUINativeModuleValue GaugeBridge::SetGaugeVaule(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    float vaule = static_cast<float>(secondArg->ToNumber(vm)->Value());
    GetArkUIInternalNodeAPI()->GetGaugeModifier().SetGaugeVaule(nativeNode, vaule);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GaugeBridge::ResetGaugeVaule(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetGaugeModifier().ResetGaugeVaule(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GaugeBridge::SetGaugeStartAngle(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    float vaule = static_cast<float>(secondArg->ToNumber(vm)->Value());
    GetArkUIInternalNodeAPI()->GetGaugeModifier().SetGaugeStartAngle(nativeNode, vaule);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GaugeBridge::ResetGaugeStartAngle(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetGaugeModifier().ResetGaugeStartAngle(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GaugeBridge::SetGaugeEndAngle(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    float vaule = static_cast<float>(secondArg->ToNumber(vm)->Value());
    GetArkUIInternalNodeAPI()->GetGaugeModifier().SetGaugeEndAngle(nativeNode, vaule);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GaugeBridge::ResetGaugeEndAngle(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetGaugeModifier().ResetGaugeEndAngle(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GaugeBridge::SetGaugeStrokeWidth(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    Local<JSValueRef> jsValue = runtimeCallInfo->GetCallArgRef(1);

    CalcDimension strokeWidth;
    if (!ArkTSUtils::ParseJsDimensionVpNG(vm, jsValue, strokeWidth) || strokeWidth.Unit() == DimensionUnit::PERCENT) {
        strokeWidth = CalcDimension(0);
    }
    GetArkUIInternalNodeAPI()->GetGaugeModifier().SetGaugeStrokeWidth(
        nativeNode, strokeWidth.Value(), static_cast<int>(strokeWidth.Unit()));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GaugeBridge::ResetGaugeStrokeWidth(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetGaugeModifier().ResetGaugeStrokeWidth(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GaugeBridge::SetGaugeTrackShadow(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    Local<JSValueRef> jsValue = runtimeCallInfo->GetCallArgRef(1);
    auto radiusArg = runtimeCallInfo->GetCallArgRef(2);
    auto offsetXArg = runtimeCallInfo->GetCallArgRef(3);
    auto offsetYArg = runtimeCallInfo->GetCallArgRef(4);

    if (jsValue->IsNull()) {
        GetArkUIInternalNodeAPI()->GetGaugeModifier().SetShadowOptions(nativeNode, DEFAULT_GAUGE_SHADOW_RADIUS,
            DEFAULT_GAUGE_SHADOW_OFFSETX, DEFAULT_GAUGE_SHADOW_OFFSETY, false);
        return panda::JSValueRef::Undefined(vm);
    }

    if (!jsValue->IsObject()) {
        GetArkUIInternalNodeAPI()->GetGaugeModifier().ResetShadowOptions(nativeNode);
        GetArkUIInternalNodeAPI()->GetGaugeModifier().SetIsShowIndicator(nativeNode, true);
        return panda::JSValueRef::Undefined(vm);
    }

    double radius = 0.0;
    if (!ArkTSUtils::ParseJsDouble(vm, radiusArg, radius)) {
        radius = DEFAULT_GAUGE_SHADOW_RADIUS;
    }

    if (NonPositive(radius)) {
        radius = DEFAULT_GAUGE_SHADOW_RADIUS;
    }

    double offsetX = 0.0;
    if (!ArkTSUtils::ParseJsDouble(vm, offsetXArg, offsetX)) {
        offsetX = DEFAULT_GAUGE_SHADOW_OFFSETX;
    }

    double offsetY = 0.0;
    if (!ArkTSUtils::ParseJsDouble(vm, offsetYArg, offsetY)) {
        offsetY = DEFAULT_GAUGE_SHADOW_OFFSETY;
    }

    GetArkUIInternalNodeAPI()->GetGaugeModifier().SetShadowOptions(nativeNode, radius, offsetX, offsetY, true);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GaugeBridge::ResetGaugeTrackShadow(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetGaugeModifier().ResetShadowOptions(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GaugeBridge::SetGaugeIndicator(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto iconArg = runtimeCallInfo->GetCallArgRef(1);
    auto spaceArg = runtimeCallInfo->GetCallArgRef(2);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    if (iconArg->IsNull() && iconArg->IsNull()) {
        GetArkUIInternalNodeAPI()->GetGaugeModifier().SetIsShowIndicator(nativeNode, false);
        return panda::JSValueRef::Undefined(vm);
    }
    if (iconArg->IsUndefined() && iconArg->IsUndefined()) {
        GetArkUIInternalNodeAPI()->GetGaugeModifier().ResetIndicatorIconPath(nativeNode);
        GetArkUIInternalNodeAPI()->GetGaugeModifier().ResetIndicatorSpace(nativeNode);
        GetArkUIInternalNodeAPI()->GetGaugeModifier().SetIsShowIndicator(nativeNode, true);
        return panda::JSValueRef::Undefined(vm);
    }
    GetArkUIInternalNodeAPI()->GetGaugeModifier().SetIsShowIndicator(nativeNode, true);
    std::string iconPath;
    if (ArkTSUtils::ParseJsMedia(vm, iconArg, iconPath)) {
        std::string bundleName;
        std::string moduleName;
        ArkTSUtils::GetJsMediaBundleInfo(vm, iconArg, bundleName, moduleName);
        GetArkUIInternalNodeAPI()->GetGaugeModifier().SetIndicatorIconPath(nativeNode,
            iconPath.c_str(), bundleName.c_str(), moduleName.c_str());
    } else {
        GetArkUIInternalNodeAPI()->GetGaugeModifier().ResetIndicatorIconPath(nativeNode);
    }
    CalcDimension space;
    if (!ArkTSUtils::ParseJsDimensionVpNG(vm, spaceArg, space, false)) {
        space = NG::INDICATOR_DISTANCE_TO_TOP;
    }
    if (space.IsNegative()) {
        space = NG::INDICATOR_DISTANCE_TO_TOP;
    }
    GetArkUIInternalNodeAPI()->GetGaugeModifier().SetIndicatorSpace(nativeNode,
        space.CalcValue().c_str(), space.Value(), static_cast<int32_t>(space.Unit()));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GaugeBridge::ResetGaugeIndicator(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto valueArg = runtimeCallInfo->GetCallArgRef(1);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    if (valueArg->IsNull()) {
        GetArkUIInternalNodeAPI()->GetGaugeModifier().SetIsShowIndicator(nativeNode, false);
    } else if (valueArg->IsUndefined() || (!valueArg->IsObject())) {
        GetArkUIInternalNodeAPI()->GetGaugeModifier().ResetIndicatorIconPath(nativeNode);
        GetArkUIInternalNodeAPI()->GetGaugeModifier().ResetIndicatorSpace(nativeNode);
        GetArkUIInternalNodeAPI()->GetGaugeModifier().SetIsShowIndicator(nativeNode, true);
    }
    return panda::JSValueRef::Undefined(vm);
}
} // namespace OHOS::Ace::NG
