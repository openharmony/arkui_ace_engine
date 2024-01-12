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
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_counter_bridge.h"

#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"
#include "core/interfaces/native/node/api.h"

namespace OHOS::Ace::NG {
ArkUINativeModuleValue CounterBridge::SetEnableInc(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> flagArg = runtimeCallInfo->GetCallArgRef(1);
    void* nativeNode = nodeArg->ToNativePointer(vm)->Value();
    if (flagArg->IsUndefined() || !flagArg->IsBoolean()) {
        GetArkUIInternalNodeAPI()->GetCounterModifier().resetEnableInc(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    bool flag = flagArg->ToBoolean(vm)->Value();
    GetArkUIInternalNodeAPI()->GetCounterModifier().SetEnableInc(nativeNode, flag);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CounterBridge::ResetEnableInc(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetCounterModifier().resetEnableInc(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CounterBridge::SetEnableDec(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> flagArg = runtimeCallInfo->GetCallArgRef(1);
    void* nativeNode = nodeArg->ToNativePointer(vm)->Value();
    if (flagArg->IsUndefined() || !flagArg->IsBoolean()) {
        GetArkUIInternalNodeAPI()->GetCounterModifier().resetEnableDec(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    bool flag = flagArg->ToBoolean(vm)->Value();
    GetArkUIInternalNodeAPI()->GetCounterModifier().SetEnableDec(nativeNode, flag);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CounterBridge::ResetEnableDec(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetCounterModifier().resetEnableDec(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CounterBridge::SetCounterHeight(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> heightValue = runtimeCallInfo->GetCallArgRef(1);
    void* nativeNode = nodeArg->ToNativePointer(vm)->Value();

    CalcDimension height;
    ArkTSUtils::ParseJsDimensionVp(vm, heightValue, height, false);
    if (LessNotEqual(height.Value(), 0.0)) {
        GetArkUIInternalNodeAPI()->GetCounterModifier().ResetCounterHeight(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    GetArkUIInternalNodeAPI()->GetCounterModifier().SetCounterHeight(
        nativeNode, height.Value(), static_cast<int>(height.Unit()));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CounterBridge::ResetCounterHeight(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = nodeArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetCounterModifier().ResetCounterHeight(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CounterBridge::SetCounterWidth(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> widthValue = runtimeCallInfo->GetCallArgRef(1);
    void* nativeNode = nodeArg->ToNativePointer(vm)->Value();

    CalcDimension width;
    ArkTSUtils::ParseJsDimensionVp(vm, widthValue, width, false);
    if (LessNotEqual(width.Value(), 0.0)) {
        GetArkUIInternalNodeAPI()->GetCounterModifier().ResetCounterWidth(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }

    GetArkUIInternalNodeAPI()->GetCounterModifier().SetCounterWidth(
        nativeNode, width.Value(), static_cast<int>(width.Unit()));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CounterBridge::ResetCounterWidth(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = nodeArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetCounterModifier().ResetCounterWidth(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CounterBridge::SetCounterBackgroundColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    void* nativeNode = nodeArg->ToNativePointer(vm)->Value();
    Color color;
    if (!ArkTSUtils::ParseJsColorAlpha(vm, secondArg, color)) {
        GetArkUIInternalNodeAPI()->GetCounterModifier().ResetCounterBackgroundColor(nativeNode);
    } else {
        GetArkUIInternalNodeAPI()->GetCounterModifier().SetCounterBackgroundColor(nativeNode, color.GetValue());
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CounterBridge::ResetCounterBackgroundColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = nodeArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetCounterModifier().ResetCounterBackgroundColor(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CounterBridge::SetCounterSize(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = nodeArg->ToNativePointer(vm)->Value();
    Local<JSValueRef> widthValue = runtimeCallInfo->GetCallArgRef(1); // 1: width Value
    Local<JSValueRef> heightValue = runtimeCallInfo->GetCallArgRef(2); // 2: height Value
    CalcDimension width;
    ArkTSUtils::ParseJsDimensionVp(vm, widthValue, width, false);
    if (GreatNotEqual(width.Value(), 0.0)) {
        GetArkUIInternalNodeAPI()->GetCounterModifier().SetCounterWidth(
            nativeNode, width.Value(), static_cast<int>(width.Unit()));
    }
    CalcDimension height;
    ArkTSUtils::ParseJsDimensionVp(vm, heightValue, height, false);
    if (GreatNotEqual(height.Value(), 0.0)) {
        GetArkUIInternalNodeAPI()->GetCounterModifier().SetCounterHeight(
            nativeNode, height.Value(), static_cast<int>(height.Unit()));
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue CounterBridge::ResetCounterSize(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = nodeArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetCounterModifier().ResetCounterWidth(nativeNode);
    GetArkUIInternalNodeAPI()->GetCounterModifier().ResetCounterHeight(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
} // namespace OHOS::Ace::NG
