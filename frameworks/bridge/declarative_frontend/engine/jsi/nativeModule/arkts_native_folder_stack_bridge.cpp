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
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_folder_stack_bridge.h"

namespace OHOS::Ace::NG {

ArkUINativeModuleValue FolderStackBridge::SetEnableAnimation(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    bool isEnableAnimation = true;
    if (secondArg->IsBoolean()) {
        isEnableAnimation = secondArg->ToBoolean(vm)->Value();
    }
    GetArkUINodeModifiers()->getFolderStackModifier()->setEnableAnimation(nativeNode,
        static_cast<int32_t>(isEnableAnimation));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue FolderStackBridge::ResetEnableAnimation(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getFolderStackModifier()->resetEnableAnimation(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue FolderStackBridge::SetAutoHalfFold(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    bool isAutoHalfFold = true;
    if (secondArg->IsBoolean()) {
        isAutoHalfFold = secondArg->ToBoolean(vm)->Value();
    }
    GetArkUINodeModifiers()->getFolderStackModifier()->setAutoHalfFold(nativeNode,
        static_cast<int32_t>(isAutoHalfFold));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue FolderStackBridge::ResetAutoHalfFold(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getFolderStackModifier()->resetAutoHalfFold(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
}
