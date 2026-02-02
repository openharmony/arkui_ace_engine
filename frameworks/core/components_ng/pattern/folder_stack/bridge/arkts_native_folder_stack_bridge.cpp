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
#include "core/components_ng/pattern/folder_stack/bridge/arkts_native_folder_stack_bridge.h"

#include "bridge/declarative_frontend/engine/jsi/jsi_types.h"
#include "core/components_ng/pattern/folder_stack/folder_stack_event_info.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"

namespace OHOS::Ace::NG {
constexpr int NUM_4 = 4;

bool IsJsView(const Local<JSValueRef>& jsVal, panda::ecmascript::EcmaVM* vm)
{
    return jsVal->IsBoolean() && jsVal->ToBoolean(vm)->Value();
}

bool GetNativeNode(ArkUINodeHandle& nativeNode, const Local<JSValueRef>& jsVal, panda::ecmascript::EcmaVM* vm)
{
    if (jsVal->IsNativePointer(vm)) {
        nativeNode = nodePtr(jsVal->ToNativePointer(vm)->Value());
        return true;
    }
    if (IsJsView(jsVal, vm)) {
        nativeNode = nullptr;
        return true;
    }
    return false;
}

bool ParseJsFolderStackUpperId(
    const EcmaVM* vm, const Local<JSValueRef>& jsValue, std::vector<std::string>& result)
{
    result.clear();
    if (!jsValue->IsObject(vm)) {
        return false;
    }
    auto obj = jsValue->ToObject(vm);
    auto upperId = obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "upperItems"));
    if (upperId->IsUndefined() || upperId->IsNull() || !upperId->IsArray(vm)) {
        return false;
    }
    panda::Local<panda::ArrayRef> upperIdParams = panda::Local<panda::ArrayRef>(upperId);
    size_t length = ArkTSUtils::GetArrayLength(vm, upperIdParams);
    for (size_t i = 0; i < length; i++) {
        auto upperItem = panda::ArrayRef::GetValueAt(vm, upperIdParams, i);
        if (upperItem->IsString(vm)) {
            result.emplace_back(upperItem->ToString(vm)->ToString(vm));
        }
    }
    return true;
}

ArkUINativeModuleValue FolderStackBridge::SetEnableAnimation(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    bool isEnableAnimation = true;
    if (secondArg->IsBoolean()) {
        isEnableAnimation = secondArg->ToBoolean(vm)->Value();
    }
    GetArkUINodeModifiers()->getFolderStackModifier()->setEnableAnimation(
        nativeNode, static_cast<int32_t>(isEnableAnimation));
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
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    bool isAutoHalfFold = true;
    if (secondArg->IsBoolean()) {
        isAutoHalfFold = secondArg->ToBoolean(vm)->Value();
    }
    GetArkUINodeModifiers()->getFolderStackModifier()->setAutoHalfFold(
        nativeNode, static_cast<int32_t>(isAutoHalfFold));
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

ArkUINativeModuleValue FolderStackBridge::SetOnFolderStateChange(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    bool isJsView = IsJsView(firstArg, vm);
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        if (!isJsView) {
            GetArkUINodeModifiers()->getFolderStackModifier()->resetOnFolderStateChange(nativeNode);
        }
        return panda::JSValueRef::Undefined(vm);
    }
    FrameNode* frameNode = nullptr;
    if (isJsView) {
        frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    } else {
        frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    }
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<void(FolderEventInfo&)> callback = [vm, isJsView, frameNode, func = panda::CopyableGlobal(vm, func)](
                                                         FolderEventInfo& value) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
        const char* keys[] = { "foldStatus" };
        Local<JSValueRef> values[] = { panda::NumberRef::New(vm, static_cast<int32_t>(value.GetFolderState())) };
        auto eventObject = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(keys), keys, values);
        eventObject->SetNativePointerFieldCount(vm, 1);
        eventObject->SetNativePointerField(vm, 0, static_cast<void*>(&value));
        panda::Local<panda::JSValueRef> params[1] = { eventObject };
        auto result = func->Call(vm, func.ToLocal(), params, 1);
        if (isJsView) {
            ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
        }
    };
    GetArkUINodeModifiers()->getFolderStackModifier()->setOnFolderStateChange(
        nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue FolderStackBridge::ResetOnFolderStateChange(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getFolderStackModifier()->resetOnFolderStateChange(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue FolderStackBridge::SetOnHoverStatusChange(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    bool isJsView = IsJsView(firstArg, vm);
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        if (!isJsView) {
            GetArkUINodeModifiers()->getFolderStackModifier()->resetOnHoverStatusChange(nativeNode);
        }
        return panda::JSValueRef::Undefined(vm);
    }
    FrameNode* frameNode = nullptr;
    if (isJsView) {
        frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    } else {
        frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    }
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<void(FolderEventInfo&)> callback = [vm, isJsView, frameNode, func = panda::CopyableGlobal(vm, func)](
                                                         FolderEventInfo& value) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
        const char* keys[] = { "foldStatus", "isHoverMode", "appRotation", "windowStatusType" };
        Local<JSValueRef> values[] = { panda::NumberRef::New(vm, static_cast<int32_t>(value.GetFolderState())),
            panda::BooleanRef::New(vm, value.IsHoverMode()),
            panda::NumberRef::New(vm, static_cast<int32_t>(value.GetRotation())),
            panda::NumberRef::New(vm, static_cast<int32_t>(value.GetWindowMode())) };
        auto eventObject = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(keys), keys, values);
        eventObject->SetNativePointerFieldCount(vm, 1);
        eventObject->SetNativePointerField(vm, 0, static_cast<void*>(&value));
        panda::Local<panda::JSValueRef> params[1] = { eventObject };
        auto result = func->Call(vm, func.ToLocal(), params, 1);
        if (isJsView) {
            ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
        }
    };
    GetArkUINodeModifiers()->getFolderStackModifier()->setOnHoverStatusChange(
        nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue FolderStackBridge::ResetOnHoverStatusChange(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getFolderStackModifier()->resetOnHoverStatusChange(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue FolderStackBridge::CreateFolderStack(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    std::vector<std::string> upperIdParams;
    if (firstArg->IsNull() || firstArg->IsUndefined() ||
        !ParseJsFolderStackUpperId(vm, firstArg, upperIdParams)) {
        GetArkUINodeModifiers()->getFolderStackModifier()->createFolderStack(0, nullptr);
        return panda::JSValueRef::Undefined(vm);
    }
    std::vector<const char*> upperId;
    for (uint32_t i = 0; i < upperIdParams.size(); i++) {
        upperId.push_back(upperIdParams[i].c_str());
    }
    GetArkUINodeModifiers()->getFolderStackModifier()->createFolderStack(upperIdParams.size(), upperId.data());
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue FolderStackBridge::SetJsAlignContent(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nullptr;
    int32_t align = NUM_4;
    if (secondArg->IsNumber()) {
        align = secondArg->Int32Value(vm);
    }
    GetArkUINodeModifiers()->getFolderStackModifier()->setJsAlignContent(nativeNode, align);
    return panda::JSValueRef::Undefined(vm);
}

void FolderStackBridge::RegisterFolderStackAttributes(Local<panda::ObjectRef> object, EcmaVM* vm)
{
    const char* functionNames[] = { "create", "setEnableAnimation", "resetEnableAnimation",
        "setAutoHalfFold", "resetAutoHalfFold", "setOnFolderStateChange",
        "resetOnFolderStateChange", "setOnHoverStatusChange", "resetOnHoverStatusChange", "setAlignContent" };

    Local<JSValueRef> funcValues[] = {
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), FolderStackBridge::CreateFolderStack),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), FolderStackBridge::SetEnableAnimation),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), FolderStackBridge::ResetEnableAnimation),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), FolderStackBridge::SetAutoHalfFold),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), FolderStackBridge::ResetAutoHalfFold),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), FolderStackBridge::SetOnFolderStateChange),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), FolderStackBridge::ResetOnFolderStateChange),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), FolderStackBridge::SetOnHoverStatusChange),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), FolderStackBridge::ResetOnHoverStatusChange),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), FolderStackBridge::SetJsAlignContent),
    };

    auto folderStack =
        panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(functionNames), functionNames, funcValues);
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "folderStack"), folderStack);
}
} // namespace OHOS::Ace::NG
