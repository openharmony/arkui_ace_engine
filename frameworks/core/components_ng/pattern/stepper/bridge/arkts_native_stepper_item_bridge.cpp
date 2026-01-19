/*
 * Copyright (c) 2023-2026 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/stepper/bridge/arkts_native_stepper_item_bridge.h"

#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/interfaces/native/node/stepper_modifier.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t CALL_ARG_0 = 0;
constexpr int32_t CALL_ARG_1 = 1;

ArkUINativeModuleValue JsSetStatus(Local<JSValueRef> nodeArg, Local<JSValueRef> jsVal, panda::ecmascript::EcmaVM* vm)
{
    const std::array<std::string, 4> statusArray = { "normal", "disabled", "waiting", "skip" };
    std::string status = statusArray[0];
    do {
        if (!jsVal->IsNumber()) {
            break;
        }
        auto index = static_cast<uint32_t>(jsVal->ToNumber(vm)->Value());
        if (index < 0 || index >= statusArray.size()) {
            break;
        }
        status = statusArray.at(index);
    } while (false);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(vm, nodeArg, nativeNode), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getStepperItemModifier()->setStatus(nativeNode, status.c_str());
    return panda::JSValueRef::Undefined(vm);
}
} // namespace

void StepperItemBridge::RegisterStepperItemAttributes(Local<panda::ObjectRef> object, EcmaVM* vm)
{
    LOGI("Start RegisterStepperItemAttributes nativeModule");

    const char* functionNames[] = { "create", "setNextLabel", "resetNextLabel", "setPrevLabel", "resetPrevLabel",
        "setStatus", "resetStatus" };

    Local<JSValueRef> funcValues[] = {
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), StepperItemBridge::CreateStepperItem),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), StepperItemBridge::SetNextLabel),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), StepperItemBridge::ResetNextLabel),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), StepperItemBridge::SetPrevLabel),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), StepperItemBridge::ResetPrevLabel),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), StepperItemBridge::SetStatus),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), StepperItemBridge::ResetStatus),
    };

    auto stepper = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(functionNames), functionNames, funcValues);
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "stepperItem"), stepper);
    LOGI("Finish RegisterStepperItemAttributes nativeModule");
}

ArkUINativeModuleValue StepperItemBridge::CreateStepperItem(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    nodeModifiers->getStepperItemModifier()->createModel();
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue StepperItemBridge::SetNextLabel(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    Local<JSValueRef> valueArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(vm, nodeArg, nativeNode), true, panda::JSValueRef::Undefined(vm));
    auto jsView = ArkTSUtils::IsJsView(vm, nodeArg);
    if ((jsView && Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_TEN) &&
            (valueArg->IsUndefined() || valueArg->IsNull())) ||
        (!jsView && (valueArg->IsUndefined() || valueArg->IsNull()))) {
        GetArkUINodeModifiers()->getStepperItemModifier()->resetNextLabel(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    if (jsView && !valueArg->IsString(vm)) {
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
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(vm, nodeArg, nativeNode), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getStepperItemModifier()->resetNextLabel(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue StepperItemBridge::SetPrevLabel(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    Local<JSValueRef> valueArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(vm, nodeArg, nativeNode), true, panda::JSValueRef::Undefined(vm));
    auto jsView = ArkTSUtils::IsJsView(vm, nodeArg);
    if ((jsView && Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_TEN) &&
            (valueArg->IsUndefined() || valueArg->IsNull())) ||
        (!jsView && (valueArg->IsUndefined() || valueArg->IsNull()))) {
        GetArkUINodeModifiers()->getStepperItemModifier()->resetPrevLabel(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    if (jsView && !valueArg->IsString(vm)) {
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
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(vm, nodeArg, nativeNode), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getStepperItemModifier()->resetPrevLabel(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue StepperItemBridge::SetStatus(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    Local<JSValueRef> valueArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    if (ArkTSUtils::IsJsView(vm, nodeArg)) {
        return JsSetStatus(nodeArg, valueArg, vm);
    }
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(vm, nodeArg, nativeNode), true, panda::JSValueRef::Undefined(vm));
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
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(vm, nodeArg, nativeNode), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getStepperItemModifier()->resetStatus(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
} // namespace OHOS::Ace::NG
