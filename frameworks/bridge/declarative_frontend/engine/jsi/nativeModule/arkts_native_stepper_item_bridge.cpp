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
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_stepper_item_bridge.h"

#include "bridge/declarative_frontend/engine/jsi/components/arkts_native_api.h"

namespace OHOS::Ace::NG {
ArkUINativeModuleValue StepperItemBridge::SetNextLabel(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    if (secondArg->IsUndefined()) {
        GetArkUIInternalNodeAPI()->GetStepperItemModifier().ResetNextLabel(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    std::string nextLabel = secondArg->ToString(vm)->ToString();
    GetArkUIInternalNodeAPI()->GetStepperItemModifier().SetNextLabel(nativeNode, nextLabel.c_str());
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue StepperItemBridge::ResetNextLabel(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetStepperItemModifier().ResetNextLabel(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
} // namespace OHOS::Ace::NG