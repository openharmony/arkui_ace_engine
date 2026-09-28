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
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_stack_bridge.h"

namespace OHOS::Ace::NG {
constexpr int NUM_4 = 4;

ArkUINativeModuleValue StackBridge::SetAlignContent(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    int32_t align = NUM_4;
    if (secondArg->IsNumber()) {
        align = secondArg->Int32Value(vm);
    }
    GetArkUINodeModifiers()->getStackModifier()->setAlignContent(nativeNode, align);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue StackBridge::ResetAlignContent(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getStackModifier()->resetAlignContent(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue StackBridge::SetSyncLoad(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> node = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> argSyncLoad = runtimeCallInfo->GetCallArgRef(1);

    CHECK_NULL_RETURN(node->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(node->ToNativePointer(vm)->Value());
    bool syncLoad = true;
    if (!argSyncLoad->IsUndefined() && !argSyncLoad->IsNull()) {
        syncLoad = argSyncLoad->BooleaValue(vm);
    }

    GetArkUINodeModifiers()->getStackModifier()->setSyncLoad(nativeNode, syncLoad);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue StackBridge::ResetSyncLoad(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> node = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(node->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(node->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getStackModifier()->resetSyncLoad(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
}
