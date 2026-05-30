/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_selection_container_bridge.h"

#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/pattern/selection_container/selection_container_model_ng.h"
#include "core/components_ng/pattern/text_field/text_selector.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "core/components_ng/base/view_stack_processor.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t NUM_0 = 0;
constexpr int32_t NUM_1 = 1;
constexpr int32_t NUM_2 = 2;
constexpr int32_t NUM_3 = 3;
constexpr int32_t NUM_4 = 4;
constexpr int32_t PARAM_ARR_LENGTH_1 = 1;
constexpr int32_t PARAM_ARR_LENGTH_2 = 2;

std::function<void(const std::u16string&)> ParseMenuTextCallback(const EcmaVM* vm, FrameNode* frameNode,
    const Local<panda::ObjectRef>& menuOptions, const std::string& name, bool isJsView)
{
    auto jsValue = menuOptions->Get(vm, panda::StringRef::NewFromUtf8(vm, name.c_str()));
    if (jsValue.IsEmpty() || !jsValue->IsFunction(vm)) {
        return nullptr;
    }
    panda::Local<panda::FunctionRef> func = jsValue->ToObject(vm);
    auto containerId = Container::CurrentId();
    auto callback = [vm, func = panda::CopyableGlobal(vm, func), containerId,
                        node = AceType::WeakClaim(frameNode), isJsView](const std::u16string& selectedText) {
        ContainerScope scope(containerId);
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(node);
        panda::Local<panda::JSValueRef> params[PARAM_ARR_LENGTH_1] = {
            panda::StringRef::NewFromUtf16(vm, selectedText.c_str()) };
        auto ret = func->Call(vm, func.ToLocal(), params, PARAM_ARR_LENGTH_1);
        if (isJsView) {
            ArkTSUtils::HandleCallbackJobs(vm, trycatch, ret);
        }
    };
    return callback;
}

std::function<bool(const NG::MenuItemParam&, const std::u16string&)> ParseMenuItemClickWithText(
    const EcmaVM* vm, FrameNode* frameNode, const Local<panda::ObjectRef>& menuOptions, bool isJsView)
{
    auto jsValue = menuOptions->Get(vm, panda::StringRef::NewFromUtf8(vm, "onMenuItemClick"));
    if (jsValue.IsEmpty() || !jsValue->IsFunction(vm)) {
        return nullptr;
    }
    panda::Local<panda::FunctionRef> func = jsValue->ToObject(vm);
    auto containerId = Container::CurrentId();
    auto callback = [vm, func = panda::CopyableGlobal(vm, func), containerId, isJsView,
                        node = AceType::WeakClaim(frameNode)](
                        const NG::MenuItemParam& menuItemParam,
                        const std::u16string& selectedText) -> bool {
        ContainerScope scope(containerId);
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(node);
        auto menuItemObj = ArkTSUtils::CreateJsTextMenuItem(vm, menuItemParam);
        panda::Local<panda::JSValueRef> params[PARAM_ARR_LENGTH_2] = {
            menuItemObj, panda::StringRef::NewFromUtf16(vm, selectedText.c_str()) };
        auto ret = func->Call(vm, func.ToLocal(), params, PARAM_ARR_LENGTH_2);
        if (isJsView) {
            ArkTSUtils::HandleCallbackJobs(vm, trycatch, ret);
        }
        if (ret->IsBoolean()) {
            return ret->ToBoolean(vm)->Value();
        }
        return false;
    };
    return callback;
}

void ParseMenuParam(const EcmaVM* vm, FrameNode* frameNode,
    const Local<panda::ObjectRef>& menuOptions, NG::SelectMenuParam& menuParam, bool isJsView)
{
    auto containerId = Container::CurrentId();
    auto onAppearValue = menuOptions->Get(vm, panda::StringRef::NewFromUtf8(vm, "onAppear"));
    if (!onAppearValue->IsUndefined() && !onAppearValue->IsNull() && onAppearValue->IsFunction(vm)) {
        panda::Local<panda::FunctionRef> jsOnAppearFunc = onAppearValue->ToObject(vm);
        auto onAppear = [vm, func = panda::CopyableGlobal(vm, jsOnAppearFunc), containerId,
                            node = AceType::WeakClaim(frameNode), isJsView](
                            const std::u16string& selectedText) {
            ContainerScope scope(containerId);
            panda::LocalScope pandaScope(vm);
            panda::TryCatch trycatch(vm);
            PipelineContext::SetCallBackNode(node);
            panda::Local<panda::JSValueRef> params[PARAM_ARR_LENGTH_1] = {
                panda::StringRef::NewFromUtf16(vm, selectedText.c_str()) };
            auto ret = func->Call(vm, func.ToLocal(), params, PARAM_ARR_LENGTH_1);
            if (isJsView) {
                ArkTSUtils::HandleCallbackJobs(vm, trycatch, ret);
            }
        };
        menuParam.onAppearWithText = std::move(onAppear);
    }
    auto onDisappearValue = menuOptions->Get(vm, panda::StringRef::NewFromUtf8(vm, "onDisappear"));
    if (!onDisappearValue->IsUndefined() && !onDisappearValue->IsNull() && onDisappearValue->IsFunction(vm)) {
        panda::Local<panda::FunctionRef> jsOnDisappearFunc = onDisappearValue->ToObject(vm);
        auto onDisappear = [vm, func = panda::CopyableGlobal(vm, jsOnDisappearFunc), containerId,
                               node = AceType::WeakClaim(frameNode), isJsView]() {
            ContainerScope scope(containerId);
            panda::LocalScope pandaScope(vm);
            panda::TryCatch trycatch(vm);
            PipelineContext::SetCallBackNode(node);
            auto ret = func->Call(vm, func.ToLocal(), nullptr, 0);
            if (isJsView) {
                ArkTSUtils::HandleCallbackJobs(vm, trycatch, ret);
            }
        };
        menuParam.onDisappear = std::move(onDisappear);
    }
    menuParam.onMenuShowWithText = ParseMenuTextCallback(vm, frameNode, menuOptions, "onMenuShow", isJsView);
    menuParam.onMenuHideWithText = ParseMenuTextCallback(vm, frameNode, menuOptions, "onMenuHide", isJsView);
}

std::function<void()> ParseBuildFunc(const EcmaVM* vm, FrameNode* frameNode,
    const Local<panda::JSValueRef>& arg, bool isJsView)
{
    if (!arg->IsObject(vm)) {
        return nullptr;
    }
    auto menuObj = arg->ToObject(vm);
    auto builderValue = menuObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "builder"));
    if (!builderValue->IsFunction(vm)) {
        return nullptr;
    }
    auto containerId = Container::CurrentId();
    panda::Local<panda::FunctionRef> func = builderValue->ToObject(vm);
    return [vm, func = panda::CopyableGlobal(vm, func),
               node = AceType::WeakClaim(frameNode), containerId, isJsView]() {
        ContainerScope scope(containerId);
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(node);
        auto ret = func->Call(vm, func.ToLocal(), nullptr, 0);
        if (isJsView) {
            ArkTSUtils::HandleCallbackJobs(vm, trycatch, ret);
        }
    };
}

ArkUINodeHandle GetNativeNodeHandle(Local<panda::JSValueRef> firstArg, EcmaVM* vm)
{
    if (ArkTSUtils::IsJsView(firstArg, vm)) {
        return reinterpret_cast<ArkUINodeHandle>(
            ViewStackProcessor::GetInstance()->GetMainFrameNode());
    }
    ArkUINodeHandle nativeNode = nullptr;
    if (ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm)) {
        return nativeNode;
    }
    return nullptr;
}
} // namespace

ArkUINativeModuleValue SelectionContainerBridge::Create(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getSelectionContainerModifier()->create();
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SelectionContainerBridge::SetCopyOption(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = GetNativeNodeHandle(firstArg, vm);
    Local<JSValueRef> valueArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    if (!valueArg->IsNumber()) {
        GetArkUINodeModifiers()->getSelectionContainerModifier()->resetCopyOption(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    auto enumNumber = valueArg->Int32Value(vm);
    if (enumNumber < static_cast<int32_t>(CopyOptions::None) ||
        enumNumber > static_cast<int32_t>(CopyOptions::Distributed)) {
        GetArkUINodeModifiers()->getSelectionContainerModifier()->resetCopyOption(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    GetArkUINodeModifiers()->getSelectionContainerModifier()->setCopyOption(nativeNode, enumNumber);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SelectionContainerBridge::ResetCopyOption(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = GetNativeNodeHandle(firstArg, vm);
    GetArkUINodeModifiers()->getSelectionContainerModifier()->resetCopyOption(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SelectionContainerBridge::SetEnableHapticFeedback(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = GetNativeNodeHandle(firstArg, vm);
    Local<JSValueRef> valueArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    if (!valueArg->IsBoolean()) {
        GetArkUINodeModifiers()->getSelectionContainerModifier()->resetEnableHapticFeedback(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    GetArkUINodeModifiers()->getSelectionContainerModifier()->setEnableHapticFeedback(
        nativeNode, valueArg->ToBoolean(vm)->Value());
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SelectionContainerBridge::ResetEnableHapticFeedback(
    ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = GetNativeNodeHandle(firstArg, vm);
    GetArkUINodeModifiers()->getSelectionContainerModifier()->resetEnableHapticFeedback(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SelectionContainerBridge::SetTextJoinStyle(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = GetNativeNodeHandle(firstArg, vm);
    Local<JSValueRef> valueArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    if (!valueArg->IsNumber()) {
        GetArkUINodeModifiers()->getSelectionContainerModifier()->resetTextJoinStyle(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    auto enumNumber = valueArg->Int32Value(vm);
    if (enumNumber < static_cast<int32_t>(SelectionContainerTextJoinStyle::NEWLINE) ||
        enumNumber > static_cast<int32_t>(SelectionContainerTextJoinStyle::DIRECT)) {
        GetArkUINodeModifiers()->getSelectionContainerModifier()->resetTextJoinStyle(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    GetArkUINodeModifiers()->getSelectionContainerModifier()->setTextJoinStyle(nativeNode, enumNumber);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SelectionContainerBridge::ResetTextJoinStyle(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = GetNativeNodeHandle(firstArg, vm);
    GetArkUINodeModifiers()->getSelectionContainerModifier()->resetTextJoinStyle(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SelectionContainerBridge::SetCaretColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = GetNativeNodeHandle(firstArg, vm);
    Local<JSValueRef> valueArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(nativeNode);
    Color caretColor;
    RefPtr<ResourceObject> resObj;
    if (!ArkTSUtils::ParseJsColorAlpha(vm, valueArg, caretColor, resObj, nodeInfo)) {
        GetArkUINodeModifiers()->getSelectionContainerModifier()->resetCaretColor(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    GetArkUINodeModifiers()->getSelectionContainerModifier()->setCaretColor(
        nativeNode, caretColor.GetValue(), AceType::RawPtr(resObj));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SelectionContainerBridge::ResetCaretColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = GetNativeNodeHandle(firstArg, vm);
    GetArkUINodeModifiers()->getSelectionContainerModifier()->resetCaretColor(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SelectionContainerBridge::SetSelectedBackgroundColor(
    ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = GetNativeNodeHandle(firstArg, vm);
    Local<JSValueRef> valueArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(nativeNode);
    Color selectedBackgroundColor;
    RefPtr<ResourceObject> resObj;
    if (!ArkTSUtils::ParseJsColorAlpha(vm, valueArg, selectedBackgroundColor, resObj, nodeInfo)) {
        GetArkUINodeModifiers()->getSelectionContainerModifier()->resetSelectedBackgroundColor(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    GetArkUINodeModifiers()->getSelectionContainerModifier()->setSelectedBackgroundColor(
        nativeNode, selectedBackgroundColor.GetValue(), AceType::RawPtr(resObj));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SelectionContainerBridge::ResetSelectedBackgroundColor(
    ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = GetNativeNodeHandle(firstArg, vm);
    GetArkUINodeModifiers()->getSelectionContainerModifier()->resetSelectedBackgroundColor(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

// Callbacks

ArkUINativeModuleValue SelectionContainerBridge::SetOnWillCopy(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = GetNativeNodeHandle(firstArg, vm);
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        GetArkUINodeModifiers()->getSelectionContainerModifier()->resetOnWillCopy(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    auto* frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    bool isJsView = ArkTSUtils::IsJsView(firstArg, vm);
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    auto containerId = Container::CurrentId();
    std::function<bool(const std::u16string&)> callback =
        [vm, func = panda::CopyableGlobal(vm, func), containerId,
            node = AceType::WeakClaim(frameNode), isJsView](const std::u16string& value) -> bool {
        ContainerScope scope(containerId);
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(node);
        panda::Local<panda::JSValueRef> params[PARAM_ARR_LENGTH_1] = {
            panda::StringRef::NewFromUtf16(vm, value.c_str()) };
        auto ret = func->Call(vm, func.ToLocal(), params, PARAM_ARR_LENGTH_1);
        if (isJsView) {
            ArkTSUtils::HandleCallbackJobs(vm, trycatch, ret);
        }
        if (ret->IsBoolean()) {
            return ret->ToBoolean(vm)->Value();
        }
        return true;
    };
    GetArkUINodeModifiers()->getSelectionContainerModifier()->setOnWillCopy(nativeNode,
        reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SelectionContainerBridge::ResetOnWillCopy(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = GetNativeNodeHandle(firstArg, vm);
    GetArkUINodeModifiers()->getSelectionContainerModifier()->resetOnWillCopy(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SelectionContainerBridge::SetOnCopy(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = GetNativeNodeHandle(firstArg, vm);
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        GetArkUINodeModifiers()->getSelectionContainerModifier()->resetOnCopy(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    auto* frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    bool isJsView = ArkTSUtils::IsJsView(firstArg, vm);
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    auto containerId = Container::CurrentId();
    std::function<void(const std::u16string&)> callback =
        [vm, func = panda::CopyableGlobal(vm, func), containerId,
            node = AceType::WeakClaim(frameNode), isJsView](const std::u16string& value) {
        ContainerScope scope(containerId);
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(node);
        panda::Local<panda::JSValueRef> params[PARAM_ARR_LENGTH_1] = {
            panda::StringRef::NewFromUtf16(vm, value.c_str()) };
        auto ret = func->Call(vm, func.ToLocal(), params, PARAM_ARR_LENGTH_1);
        if (isJsView) {
            ArkTSUtils::HandleCallbackJobs(vm, trycatch, ret);
        }
    };
    GetArkUINodeModifiers()->getSelectionContainerModifier()->setOnCopy(nativeNode,
        reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SelectionContainerBridge::ResetOnCopy(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = GetNativeNodeHandle(firstArg, vm);
    GetArkUINodeModifiers()->getSelectionContainerModifier()->resetOnCopy(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SelectionContainerBridge::SetOnTextSelectionChange(
    ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = GetNativeNodeHandle(firstArg, vm);
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        GetArkUINodeModifiers()->getSelectionContainerModifier()->resetOnTextSelectionChange(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    auto* frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    bool isJsView = ArkTSUtils::IsJsView(firstArg, vm);
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    auto containerId = Container::CurrentId();
    std::function<void(const std::vector<std::u16string>&)> callback =
        [vm, func = panda::CopyableGlobal(vm, func), containerId,
            node = AceType::WeakClaim(frameNode), isJsView](const std::vector<std::u16string>& selectedTexts) {
        ContainerScope scope(containerId);
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(node);
        auto arr = panda::ArrayRef::New(vm, selectedTexts.size());
        for (size_t i = 0; i < selectedTexts.size(); ++i) {
            panda::ArrayRef::SetValueAt(vm, arr, i,
                panda::StringRef::NewFromUtf16(vm, selectedTexts[i].c_str()));
        }
        panda::Local<panda::JSValueRef> params[PARAM_ARR_LENGTH_1] = { arr };
        auto ret = func->Call(vm, func.ToLocal(), params, PARAM_ARR_LENGTH_1);
        if (isJsView) {
            ArkTSUtils::HandleCallbackJobs(vm, trycatch, ret);
        }
    };
    GetArkUINodeModifiers()->getSelectionContainerModifier()->setOnTextSelectionChange(nativeNode,
        reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SelectionContainerBridge::ResetOnTextSelectionChange(
    ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = GetNativeNodeHandle(firstArg, vm);
    GetArkUINodeModifiers()->getSelectionContainerModifier()->resetOnTextSelectionChange(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SelectionContainerBridge::SetSelectionMenuOptions(
    ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = GetNativeNodeHandle(firstArg, vm);
    if (!secondArg->IsObject(vm) || secondArg->IsUndefined()) {
        GetArkUINodeModifiers()->getSelectionContainerModifier()->resetSelectionMenuOptions(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    auto* frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    bool isJsView = ArkTSUtils::IsJsView(firstArg, vm);
    auto menuOptionsObject = secondArg->ToObject(vm);

    NG::OnCreateMenuCallback onCreateMenuCallback;
    auto jsValueOnCreateMenu = menuOptionsObject->Get(vm, panda::StringRef::NewFromUtf8(vm, "onCreateMenu"));
    ArkTSUtils::ParseOnCreateMenu(vm, frameNode, jsValueOnCreateMenu, onCreateMenuCallback, isJsView);

    NG::OnPrepareMenuCallback onPrepareMenuCallback;
    auto jsValueOnPrepareMenu = menuOptionsObject->Get(vm, panda::StringRef::NewFromUtf8(vm, "onPrepareMenu"));
    ArkTSUtils::ParseOnPrepareMenu(vm, frameNode, jsValueOnPrepareMenu, onPrepareMenuCallback, isJsView);

    auto onMenuItemClickWithText = ParseMenuItemClickWithText(vm, frameNode, menuOptionsObject, isJsView);

    GetArkUINodeModifiers()->getSelectionContainerModifier()->setSelectionMenuOptions(
        nativeNode, reinterpret_cast<void*>(&onCreateMenuCallback), reinterpret_cast<void*>(&onMenuItemClickWithText),
        reinterpret_cast<void*>(&onPrepareMenuCallback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SelectionContainerBridge::ResetSelectionMenuOptions(
    ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = GetNativeNodeHandle(firstArg, vm);
    GetArkUINodeModifiers()->getSelectionContainerModifier()->resetSelectionMenuOptions(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SelectionContainerBridge::BindSelectionMenu(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = GetNativeNodeHandle(firstArg, vm);
    auto* frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    bool isJsView = ArkTSUtils::IsJsView(firstArg, vm);

    NG::TextSpanType textSpanType = NG::TextSpanType::TEXT;
    bool isValidTextSpanType = true;
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    if (secondArg->IsNumber()) {
        auto spanTypeId = secondArg->Int32Value(vm);
        isValidTextSpanType = NG::TextSpanTypeMapper::GetTextSpanTypeFromJsType(spanTypeId, textSpanType);
    }

    auto buildFunc = ParseBuildFunc(vm, frameNode, runtimeCallInfo->GetCallArgRef(NUM_2), isJsView);

    NG::TextResponseType responseType = NG::TextResponseType::LONG_PRESS;
    Local<JSValueRef> fourthArg = runtimeCallInfo->GetCallArgRef(NUM_3);
    if (fourthArg->IsNumber()) {
        responseType = static_cast<NG::TextResponseType>(fourthArg->Int32Value(vm));
    }

    NG::SelectMenuParam menuParam;
    menuParam.isValid = isValidTextSpanType;
    Local<JSValueRef> fifthArg = runtimeCallInfo->GetCallArgRef(NUM_4);
    if (fifthArg->IsObject(vm)) {
        auto menuOptions = fifthArg->ToObject(vm);
        ParseMenuParam(vm, frameNode, menuOptions, menuParam, isJsView);
    }

    GetArkUINodeModifiers()->getSelectionContainerModifier()->setBindSelectionMenu(
        nativeNode,
        static_cast<ArkUI_Int32>(textSpanType),
        static_cast<ArkUI_Int32>(responseType),
        reinterpret_cast<void*>(&buildFunc), reinterpret_cast<void*>(&menuParam));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SelectionContainerBridge::ResetBindSelectionMenu(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = GetNativeNodeHandle(firstArg, vm);
    NG::TextSpanType textSpanType = NG::TextSpanType::TEXT;
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    if (secondArg->IsNumber()) {
        NG::TextSpanTypeMapper::GetTextSpanTypeFromJsType(secondArg->Int32Value(vm), textSpanType);
    }
    NG::TextResponseType responseType = NG::TextResponseType::LONG_PRESS;
    Local<JSValueRef> thirdArg = runtimeCallInfo->GetCallArgRef(NUM_2);
    if (thirdArg->IsNumber()) {
        responseType = static_cast<NG::TextResponseType>(thirdArg->Int32Value(vm));
    }
    GetArkUINodeModifiers()->getSelectionContainerModifier()->resetBindSelectionMenu(
        nativeNode, static_cast<ArkUI_Int32>(textSpanType),
        static_cast<ArkUI_Int32>(responseType));
    return panda::JSValueRef::Undefined(vm);
}

} // namespace OHOS::Ace::NG
