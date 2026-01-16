/*
 * Copyright (c) 2025-2026 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/stepper/bridge/arkts_native_stepper_bridge.h"

#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/interfaces/native/node/stepper_modifier.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t NUM_0 = 0;
constexpr int32_t NUM_1 = 1;
constexpr int32_t NUM_2 = 2;

void ParseStepperIndexObject(const EcmaVM* vm, const Local<JSValueRef>& changeEventVal)
{
    CHECK_NULL_VOID(changeEventVal->IsFunction(vm));
    auto targetNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(targetNode);
    panda::Local<panda::FunctionRef> func = changeEventVal->ToObject(vm);
    std::function<void(int32_t)> changeEvent = [vm, node = AceType::WeakClaim(targetNode),
                                                   func = panda::CopyableGlobal(vm, func)](int32_t index) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(node);
        panda::Local<panda::JSValueRef> params[NUM_1] = { panda::NumberRef::New(vm, index) };
        auto result = func->Call(vm, func.ToLocal(), params, NUM_1);
        ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
    };
    GetArkUINodeModifiers()->getStepperModifier()->setStepperOnChangeEvent(
        nodePtr(targetNode), reinterpret_cast<void*>(&changeEvent));
}
} // namespace

void StepperBridge::RegisterStepperAttributes(Local<panda::ObjectRef> object, EcmaVM* vm)
{
    LOGI("Start RegisterStepperAttributes nativeModule");

    const char* functionNames[] = { "create", "setOnFinish", "resetOnFinish", "setOnSkip", "resetOnSkip", "setOnChange",
        "resetOnChange", "setOnNext", "resetOnNext", "setOnPrevious", "resetOnPrevious" };

    Local<JSValueRef> funcValues[] = {
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), StepperBridge::CreateStepper),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), StepperBridge::SetOnFinish),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), StepperBridge::ResetOnFinish),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), StepperBridge::SetOnSkip),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), StepperBridge::ResetOnSkip),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), StepperBridge::SetOnChange),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), StepperBridge::ResetOnChange),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), StepperBridge::SetOnNext),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), StepperBridge::ResetOnNext),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), StepperBridge::SetOnPrevious),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), StepperBridge::ResetOnPrevious),
    };

    auto stepper = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(functionNames), functionNames, funcValues);
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "stepper"), stepper);
    LOGI("Finish RegisterStepperAttributes nativeModule");
}

ArkUINativeModuleValue StepperBridge::CreateStepper(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    uint32_t index = 0;
    Local<panda::JSValueRef> changeEventVal = panda::JSValueRef::Undefined(vm);
    if (runtimeCallInfo->GetArgsNumber() < 1 || !runtimeCallInfo->GetCallArgRef(0)->IsObject(vm)) {
        index = 0;
    } else {
        Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
        auto obj = firstArg->ToObject(vm);
        auto stepperValue = obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "index"));
        if (stepperValue->IsNumber()) {
            auto indexValue = static_cast<int32_t>(stepperValue->ToNumber(vm)->Value());
            index = indexValue <= 0 ? 0 : static_cast<uint32_t>(indexValue);
        } else if (stepperValue->IsObject(vm)) {
            auto stepperObj = stepperValue->ToObject(vm);
            auto stepperValueProperty = stepperObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "value"));
            if (stepperValueProperty->IsNumber()) {
                auto indexValue = static_cast<int32_t>(stepperValueProperty->ToNumber(vm)->Value());
                index = indexValue <= 0 ? 0 : static_cast<uint32_t>(indexValue);
            }
            changeEventVal = stepperObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "changeEvent"));
        }
    }

    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    nodeModifiers->getStepperModifier()->createModel(index);

    if (!changeEventVal->IsUndefined() && !changeEventVal.IsNull() && changeEventVal->IsFunction(vm)) {
        ParseStepperIndexObject(vm, changeEventVal);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue StepperBridge::SetOnFinish(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(vm, nodeArg, nativeNode), true, panda::JSValueRef::Undefined(vm));
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    bool isJsView = ArkTSUtils::IsJsView(vm, nodeArg);
    if (callbackArg->IsNull() || callbackArg->IsUndefined() || !callbackArg->IsFunction(vm)) {
        if (!isJsView) {
            nodeModifiers->getStepperModifier()->resetStepperOnFinish(nativeNode);
        }
        return panda::JSValueRef::Undefined(vm);
    }
    auto frameNode =
        isJsView ? ViewStackProcessor::GetInstance()->GetMainFrameNode() : reinterpret_cast<FrameNode*>(nativeNode);
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<void()> OnFinish = [vm, func = panda::CopyableGlobal(vm, func), frameNode, isJsView]() {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
        auto result = func->Call(vm, func.ToLocal(), nullptr, NUM_0);
        if (isJsView) {
            ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
        }
    };
    nodeModifiers->getStepperModifier()->setStepperOnFinish(nativeNode, reinterpret_cast<void*>(&OnFinish));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue StepperBridge::ResetOnFinish(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(vm, nodeArg, nativeNode), true, panda::JSValueRef::Undefined(vm));
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
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(vm, nodeArg, nativeNode), true, panda::JSValueRef::Undefined(vm));
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    bool isJsView = ArkTSUtils::IsJsView(vm, nodeArg);
    if (callbackArg->IsNull() || callbackArg->IsUndefined() || !callbackArg->IsFunction(vm)) {
        if (!isJsView) {
            nodeModifiers->getStepperModifier()->resetStepperOnSkip(nativeNode);
        }
        return panda::JSValueRef::Undefined(vm);
    }
    auto frameNode =
        isJsView ? ViewStackProcessor::GetInstance()->GetMainFrameNode() : reinterpret_cast<FrameNode*>(nativeNode);
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<void()> OnSkip = [vm, func = panda::CopyableGlobal(vm, func), frameNode, isJsView]() {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
        auto result = func->Call(vm, func.ToLocal(), nullptr, NUM_0);
        if (isJsView) {
            ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
        }
    };
    nodeModifiers->getStepperModifier()->setStepperOnSkip(nativeNode, reinterpret_cast<void*>(&OnSkip));
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue StepperBridge::ResetOnSkip(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(vm, nodeArg, nativeNode), true, panda::JSValueRef::Undefined(vm));
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
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(vm, nodeArg, nativeNode), true, panda::JSValueRef::Undefined(vm));
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    bool isJsView = ArkTSUtils::IsJsView(vm, nodeArg);
    if (callbackArg->IsNull() || callbackArg->IsUndefined() || !callbackArg->IsFunction(vm)) {
        if (!isJsView) {
            nodeModifiers->getStepperModifier()->resetStepperOnChange(nativeNode);
        }
        return panda::JSValueRef::Undefined(vm);
    }
    auto frameNode =
        isJsView ? ViewStackProcessor::GetInstance()->GetMainFrameNode() : reinterpret_cast<FrameNode*>(nativeNode);
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<void(int32_t, int32_t)> OnChange = [vm, func = panda::CopyableGlobal(vm, func), frameNode, isJsView](
                                                         int32_t prevIndex, int32_t index) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));

        panda::Local<panda::NumberRef> prevIndexParam = panda::NumberRef::New(vm, prevIndex);
        panda::Local<panda::NumberRef> indexParam = panda::NumberRef::New(vm, index);
        panda::Local<panda::JSValueRef> params[NUM_2] = { prevIndexParam, indexParam };
        auto result = func->Call(vm, func.ToLocal(), params, NUM_2);
        if (isJsView) {
            ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
        }
    };
    nodeModifiers->getStepperModifier()->setStepperOnChange(nativeNode, reinterpret_cast<void*>(&OnChange));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue StepperBridge::ResetOnChange(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(vm, nodeArg, nativeNode), true, panda::JSValueRef::Undefined(vm));
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
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(vm, nodeArg, nativeNode), true, panda::JSValueRef::Undefined(vm));
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    bool isJsView = ArkTSUtils::IsJsView(vm, nodeArg);
    if (callbackArg->IsNull() || callbackArg->IsUndefined() || !callbackArg->IsFunction(vm)) {
        if (!isJsView) {
            nodeModifiers->getStepperModifier()->resetStepperOnNext(nativeNode);
        }
        return panda::JSValueRef::Undefined(vm);
    }
    auto frameNode =
        isJsView ? ViewStackProcessor::GetInstance()->GetMainFrameNode() : reinterpret_cast<FrameNode*>(nativeNode);
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<void(int32_t, int32_t)> OnNext = [vm, func = panda::CopyableGlobal(vm, func), frameNode, isJsView](
                                                       int32_t index, int32_t pendingIndex) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));

        panda::Local<panda::NumberRef> indexParam = panda::NumberRef::New(vm, index);
        panda::Local<panda::NumberRef> pendingIndexPram = panda::NumberRef::New(vm, pendingIndex);
        panda::Local<panda::JSValueRef> params[NUM_2] = { indexParam, pendingIndexPram };
        auto result = func->Call(vm, func.ToLocal(), params, NUM_2);
        if (isJsView) {
            ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
        }
    };
    nodeModifiers->getStepperModifier()->setStepperOnNext(nativeNode, reinterpret_cast<void*>(&OnNext));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue StepperBridge::ResetOnNext(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(vm, nodeArg, nativeNode), true, panda::JSValueRef::Undefined(vm));
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
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(vm, nodeArg, nativeNode), true, panda::JSValueRef::Undefined(vm));
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    bool isJsView = ArkTSUtils::IsJsView(vm, nodeArg);
    if (callbackArg->IsNull() || callbackArg->IsUndefined() || !callbackArg->IsFunction(vm)) {
        if (!isJsView) {
            nodeModifiers->getStepperModifier()->resetStepperOnPrevious(nativeNode);
        }
        return panda::JSValueRef::Undefined(vm);
    }
    auto frameNode =
        isJsView ? ViewStackProcessor::GetInstance()->GetMainFrameNode() : reinterpret_cast<FrameNode*>(nativeNode);
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<void(int32_t, int32_t)> OnPrevious = [vm, func = panda::CopyableGlobal(vm, func), frameNode,
                                                           isJsView](int32_t index, int32_t pendingIndex) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));

        panda::Local<panda::NumberRef> indexParam = panda::NumberRef::New(vm, index);
        panda::Local<panda::NumberRef> pendingIndexPram = panda::NumberRef::New(vm, pendingIndex);
        panda::Local<panda::JSValueRef> params[NUM_2] = { indexParam, pendingIndexPram };
        auto result = func->Call(vm, func.ToLocal(), params, NUM_2);
        if (isJsView) {
            ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
        }
    };
    nodeModifiers->getStepperModifier()->setStepperOnPrevious(nativeNode, reinterpret_cast<void*>(&OnPrevious));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue StepperBridge::ResetOnPrevious(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(vm, nodeArg, nativeNode), true, panda::JSValueRef::Undefined(vm));
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    nodeModifiers->getStepperModifier()->resetStepperOnPrevious(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
} // namespace OHOS::Ace::NG
