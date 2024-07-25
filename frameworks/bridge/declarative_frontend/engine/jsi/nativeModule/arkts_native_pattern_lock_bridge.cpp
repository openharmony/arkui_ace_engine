/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_pattern_lock_bridge.h"

#include "base/geometry/dimension.h"
#include "base/utils/utils.h"
#include "core/components/common/layout/constants.h"
#include "core/pipeline/pipeline_base.h"
#include "frameworks/bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"


namespace OHOS::Ace::NG {
constexpr int NUM_0 = 0;
constexpr int NUM_1 = 1;

ArkUINativeModuleValue PatternLockBridge::SetSideLength(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    CalcDimension sideLength;
    if (!(ArkTSUtils::ParseJsDimensionVp(vm, secondArg, sideLength))) {
        GetArkUINodeModifiers()->getPatternLockModifier()->resetPatternLockSideLength(nativeNode);
    }
    GetArkUINodeModifiers()->getPatternLockModifier()->setPatternLockSideLength(
        nativeNode, sideLength.Value(), static_cast<int8_t>(sideLength.Unit()));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue PatternLockBridge::ResetSideLength(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getPatternLockModifier()->resetPatternLockSideLength(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue PatternLockBridge::SetAutoReset(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    uint32_t value = 1;
    if (secondArg->IsBoolean()) {
        value = static_cast<uint32_t>(secondArg->ToBoolean(vm)->Value());
    }
    GetArkUINodeModifiers()->getPatternLockModifier()->setPatternLockAutoReset(nativeNode, value);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue PatternLockBridge::ResetAutoReset(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getPatternLockModifier()->resetPatternLockAutoReset(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue PatternLockBridge::SetPathStrokeWidth(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    CalcDimension strokeWidth;
    if (!(ArkTSUtils::ParseJsDimensionVp(vm, secondArg, strokeWidth))) {
        GetArkUINodeModifiers()->getPatternLockModifier()->resetPatternLockPathStrokeWidth(nativeNode);
    }
    GetArkUINodeModifiers()->getPatternLockModifier()->setPatternLockPathStrokeWidth(
        nativeNode, strokeWidth.Value(), static_cast<int8_t>(strokeWidth.Unit()));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue PatternLockBridge::ResetPathStrokeWidth(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getPatternLockModifier()->resetPatternLockPathStrokeWidth(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue PatternLockBridge::SetRegularColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    Color color;
    if (!ArkTSUtils::ParseJsColorAlpha(vm, secondArg, color)) {
        GetArkUINodeModifiers()->getPatternLockModifier()->resetPatternLockRegularColor(nativeNode);
    } else {
        GetArkUINodeModifiers()->getPatternLockModifier()->setPatternLockRegularColor(nativeNode, color.GetValue());
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue PatternLockBridge::ResetRegularColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getPatternLockModifier()->resetPatternLockRegularColor(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue PatternLockBridge::SetPathColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    Color color;
    if (!ArkTSUtils::ParseJsColorAlpha(vm, secondArg, color)) {
        GetArkUINodeModifiers()->getPatternLockModifier()->resetPatternLockPathColor(nativeNode);
    } else {
        GetArkUINodeModifiers()->getPatternLockModifier()->setPatternLockPathColor(nativeNode, color.GetValue());
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue PatternLockBridge::ResetPathColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getPatternLockModifier()->resetPatternLockPathColor(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue PatternLockBridge::SetPatternLockActiveColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    Color color;
    if (!ArkTSUtils::ParseJsColorAlpha(vm, secondArg, color)) {
        GetArkUINodeModifiers()->getPatternLockModifier()->resetPatternLockActiveColor(nativeNode);
    } else {
        GetArkUINodeModifiers()->getPatternLockModifier()->setPatternLockActiveColor(nativeNode, color.GetValue());
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue PatternLockBridge::ResetPatternLockActiveColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getPatternLockModifier()->resetPatternLockActiveColor(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue PatternLockBridge::SetPatternLockCircleRadius(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    CalcDimension circleRadius;
    if (ArkTSUtils::ParseJsDimensionVp(vm, secondArg, circleRadius) && !(circleRadius.IsNonPositive())) {
        GetArkUINodeModifiers()->getPatternLockModifier()->setPatternLockCircleRadius(
            nativeNode, circleRadius.Value(), static_cast<int8_t>(circleRadius.Unit()));
    } else {
        GetArkUINodeModifiers()->getPatternLockModifier()->resetPatternLockCircleRadius(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue PatternLockBridge::ResetPatternLockCircleRadius(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getPatternLockModifier()->resetPatternLockCircleRadius(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue PatternLockBridge::SetPatternLockSelectedColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    Color color;
    if (!ArkTSUtils::ParseJsColorAlpha(vm, secondArg, color)) {
        GetArkUINodeModifiers()->getPatternLockModifier()->resetPatternLockSelectedColor(nativeNode);
    } else {
        GetArkUINodeModifiers()->getPatternLockModifier()->setPatternLockSelectedColor(nativeNode, color.GetValue());
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue PatternLockBridge::ResetPatternLockSelectedColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getPatternLockModifier()->resetPatternLockSelectedColor(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue PatternLockBridge::SetPatternLockActivateCircleStyle(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (!secondArg->IsObject(vm)) {
        GetArkUINodeModifiers()->getPatternLockModifier()->resetPatternLockActiveCircleColor(nativeNode);
        GetArkUINodeModifiers()->getPatternLockModifier()->resetPatternLockActiveCircleRadius(nativeNode);
        GetArkUINodeModifiers()->getPatternLockModifier()->resetPatternLockEnableWaveEffect(nativeNode);
    } else {
        auto obj = secondArg->ToObject(vm);
        auto jsColor = obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "color"));
        auto jsRadius = obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "radius"));
        auto jsEnable = obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "enableWaveEffect"));
        Color color;
        if (!ArkTSUtils::ParseJsColorAlpha(vm, jsColor, color)) {
            GetArkUINodeModifiers()->getPatternLockModifier()->resetPatternLockActiveCircleColor(nativeNode);
        } else {
            GetArkUINodeModifiers()->getPatternLockModifier()->setPatternLockActiveCircleColor(
                nativeNode, color.GetValue());
        }
        CalcDimension circleRadius;
        if (jsRadius->IsObject(vm) && ArkTSUtils::ParseJsLengthMetrics(vm, jsRadius, circleRadius) &&
            !(circleRadius.IsNonPositive())) {
            GetArkUINodeModifiers()->getPatternLockModifier()->setPatternLockActiveCircleRadius(
                nativeNode, circleRadius.Value(), static_cast<int8_t>(circleRadius.Unit()));
        } else {
            GetArkUINodeModifiers()->getPatternLockModifier()->resetPatternLockActiveCircleRadius(nativeNode);
        }
        uint32_t value = 1;
        if (jsEnable->IsBoolean()) {
            value = static_cast<uint32_t>(jsEnable->ToBoolean(vm)->Value());
        }
        GetArkUINodeModifiers()->getPatternLockModifier()->setPatternLockEnableWaveEffect(nativeNode, value);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue PatternLockBridge::ResetPatternLockActivateCircleStyle(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getPatternLockModifier()->resetPatternLockActiveCircleColor(nativeNode);
    GetArkUINodeModifiers()->getPatternLockModifier()->resetPatternLockActiveCircleRadius(nativeNode);
    GetArkUINodeModifiers()->getPatternLockModifier()->resetPatternLockEnableWaveEffect(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
} // namespace OHOS::Ace::NG
