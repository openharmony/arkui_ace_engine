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

namespace OHOS::Ace::NG {
constexpr int32_t CALL_ARG_0 = 0;
constexpr int32_t CALL_ARG_1 = 1;
ArkUINativeModuleValue StepperItemBridge::SetNextLabel(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    Local<JSValueRef> valueArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    if (valueArg->IsUndefined() || valueArg->IsNull()) {
        GetArkUINodeModifiers()->getStepperItemModifier()->resetNextLabel(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    std::string nextLabel = valueArg->ToString(vm)->ToString(vm);
    GetArkUINodeModifiers()->getStepperItemModifier()->setNextLabel(nativeNode, nextLabel.c_str());
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue StepperItemBridge::ResetNextLabel(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getStepperItemModifier()->resetNextLabel(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue StepperItemBridge::SetPrevLabel(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    Local<JSValueRef> valueArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    if (valueArg->IsUndefined() || valueArg->IsNull()) {
        GetArkUINodeModifiers()->getStepperItemModifier()->resetPrevLabel(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    std::string prevLabel = valueArg->ToString(vm)->ToString(vm);
    GetArkUINodeModifiers()->getStepperItemModifier()->setPrevLabel(nativeNode, prevLabel.c_str());
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue StepperItemBridge::ResetPrevLabel(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getStepperItemModifier()->resetPrevLabel(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue StepperItemBridge::SetStatus(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    Local<JSValueRef> valueArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    if (valueArg->IsUndefined() || !valueArg->IsNumber()) {
        GetArkUINodeModifiers()->getStepperItemModifier()->resetStatus(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    const std::array<std::string, 4> statusArray = { "normal", "disabled", "waiting", "skip" };
    std::string status = statusArray[0];
    int32_t index = valueArg->Int32Value(vm);
    if (index > 0 && static_cast<size_t>(index) < statusArray.size()) {
        status = statusArray.at(index);
    }
    GetArkUINodeModifiers()->getStepperItemModifier()->setStatus(nativeNode, status.c_str());
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue StepperItemBridge::ResetStatus(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getStepperItemModifier()->resetStatus(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
} // namespace OHOS::Ace::NG