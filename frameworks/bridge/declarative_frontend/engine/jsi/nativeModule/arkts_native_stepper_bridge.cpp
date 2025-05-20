/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_stepper_bridge.h"

namespace OHOS::Ace::NG {
constexpr int32_t NUM_0 = 0;
constexpr int32_t NUM_1 = 1;
constexpr int32_t NUM_2 = 2;
ArkUINativeModuleValue StepperBridge::SetOnFinish(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    if (callbackArg->IsNull() || callbackArg->IsUndefined() || !callbackArg->IsFunction(vm)) {
        nodeModifiers->getStepperModifier()->resetStepperOnFinish(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<void()> OnFinish = [vm, func = panda::CopyableGlobal(vm, func), frameNode]() {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
        func->Call(vm, func.ToLocal(), nullptr, NUM_0);
    };
    nodeModifiers->getStepperModifier()->setStepperOnFinish(nativeNode, reinterpret_cast<void*>(&OnFinish));
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue StepperBridge::ResetOnFinish(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    nodeModifiers->getStepperModifier()->resetStepperOnFinish(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue StepperBridge::SetOnSkip(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    if (callbackArg->IsNull() || callbackArg->IsUndefined() || !callbackArg->IsFunction(vm)) {
        nodeModifiers->getStepperModifier()->resetStepperOnSkip(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<void()> OnSkip = [vm, func = panda::CopyableGlobal(vm, func), frameNode]() {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
        func->Call(vm, func.ToLocal(), nullptr, NUM_0);
    };
    nodeModifiers->getStepperModifier()->setStepperOnSkip(nativeNode, reinterpret_cast<void*>(&OnSkip));
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue StepperBridge::ResetOnSkip(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    nodeModifiers->getStepperModifier()->resetStepperOnSkip(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue StepperBridge::SetOnChange(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    if (callbackArg->IsNull() || callbackArg->IsUndefined() || !callbackArg->IsFunction(vm)) {
        nodeModifiers->getStepperModifier()->resetStepperOnChange(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<void(int32_t, int32_t)> OnChange = [vm, func = panda::CopyableGlobal(vm, func), frameNode](
                                                         int32_t prevIndex, int32_t index) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));

        panda::Local<panda::NumberRef> prevIndexParam = panda::NumberRef::New(vm, prevIndex);
        panda::Local<panda::NumberRef> indexParam = panda::NumberRef::New(vm, index);
        panda::Local<panda::JSValueRef> params[NUM_2] = { prevIndexParam, indexParam };
        func->Call(vm, func.ToLocal(), params, NUM_2);
    };
    nodeModifiers->getStepperModifier()->setStepperOnChange(nativeNode, reinterpret_cast<void*>(&OnChange));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue StepperBridge::ResetOnChange(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    nodeModifiers->getStepperModifier()->resetStepperOnChange(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue StepperBridge::SetOnNext(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    if (callbackArg->IsNull() || callbackArg->IsUndefined() || !callbackArg->IsFunction(vm)) {
        nodeModifiers->getStepperModifier()->resetStepperOnNext(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<void(int32_t, int32_t)> OnNext = [vm, func = panda::CopyableGlobal(vm, func), frameNode](
                                                       int32_t index, int32_t pendingIndex) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));

        panda::Local<panda::NumberRef> indexParam = panda::NumberRef::New(vm, index);
        panda::Local<panda::NumberRef> pendingIndexPram = panda::NumberRef::New(vm, pendingIndex);
        panda::Local<panda::JSValueRef> params[NUM_2] = { indexParam, pendingIndexPram };
        func->Call(vm, func.ToLocal(), params, NUM_2);
    };
    nodeModifiers->getStepperModifier()->setStepperOnNext(nativeNode, reinterpret_cast<void*>(&OnNext));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue StepperBridge::ResetOnNext(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    nodeModifiers->getStepperModifier()->resetStepperOnNext(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue StepperBridge::SetOnPrevious(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    if (callbackArg->IsNull() || callbackArg->IsUndefined() || !callbackArg->IsFunction(vm)) {
        nodeModifiers->getStepperModifier()->resetStepperOnPrevious(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<void(int32_t, int32_t)> OnPrevious = [vm, func = panda::CopyableGlobal(vm, func), frameNode](
                                                           int32_t index, int32_t pendingIndex) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));

        panda::Local<panda::NumberRef> indexParam = panda::NumberRef::New(vm, index);
        panda::Local<panda::NumberRef> pendingIndexPram = panda::NumberRef::New(vm, pendingIndex);
        panda::Local<panda::JSValueRef> params[NUM_2] = { indexParam, pendingIndexPram };
        func->Call(vm, func.ToLocal(), params, NUM_2);
    };
    nodeModifiers->getStepperModifier()->setStepperOnPrevious(
        nativeNode, reinterpret_cast<void*>(&OnPrevious));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue StepperBridge::ResetOnPrevious(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    nodeModifiers->getStepperModifier()->resetStepperOnPrevious(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
} // namespace OHOS::Ace::NG