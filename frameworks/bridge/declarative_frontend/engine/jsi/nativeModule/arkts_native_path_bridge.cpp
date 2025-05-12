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
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_path_bridge.h"
#include "frameworks/bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"

namespace OHOS::Ace::NG {
ArkUINativeModuleValue PathBridge::SetPathCommands(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);

    if (!secondArg->IsString(vm) && !secondArg->IsObject(vm)) {
        GetArkUINodeModifiers()->getPathModifier()->resetPathCommands(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }

    std::string commands;
    if (secondArg->IsString(vm)) {
        commands = secondArg->ToString(vm)->ToString(vm);
    } else if (secondArg->IsObject(vm)) {
        ArkTSUtils::ParseJsStringFromResource(vm, secondArg, commands);
    }
    GetArkUINodeModifiers()->getPathModifier()->setPathCommands(nativeNode, commands.c_str());
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue PathBridge::ResetPathCommands(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getPathModifier()->resetPathCommands(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
}
