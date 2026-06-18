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
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/loading_progress/bridge/arkts_native_loading_progress_bridge.h"
#include "core/components_ng/pattern/loading_progress/loading_progress_model_ng.h"
#include "core/components_ng/pattern/loading_progress/loading_progress_pattern.h"
#include "bridge/declarative_frontend/ark_theme/theme_apply/js_loading_progress_theme.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"

using namespace OHOS::Ace::Framework;

namespace OHOS::Ace::NG {
namespace {
constexpr int NUM_0 = 0;
constexpr int NUM_1 = 1;
const char* LOADINGPROGRESS_NODEPTR_OF_UINODE = "nodePtr_";
} // namespace

void LoadingProgressBridge::RegisterLoadingProgressAttributes(Local<panda::ObjectRef> object, EcmaVM* vm)
{
    const char* functionNames[] = { "create", "setColor", "resetColor", "setEnableLoading", "resetEnableLoading",
        "setForegroundColor", "resetForegroundColor", "setContentModifierBuilder" };

    Local<JSValueRef> funcValues[] = {
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), LoadingProgressBridge::CreateLoadingProgress),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), LoadingProgressBridge::SetColor),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), LoadingProgressBridge::ResetColor),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), LoadingProgressBridge::SetEnableLoading),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), LoadingProgressBridge::ResetEnableLoading),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), LoadingProgressBridge::SetForegroundColor),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), LoadingProgressBridge::ResetForegroundColor),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), LoadingProgressBridge::SetContentModifierBuilder),

    };

    auto loadingProgress =
        panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(functionNames), functionNames, funcValues);
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "loadingProgress"), loadingProgress);
}

ArkUINativeModuleValue LoadingProgressBridge::CreateLoadingProgress(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    auto loadingProgressModifier = nodeModifiers->getLoadingProgressModifier();
    CHECK_NULL_RETURN(loadingProgressModifier, panda::JSValueRef::Undefined(vm));
    loadingProgressModifier->createLoadingProgress();
    Framework::JSLoadingProgressTheme::ApplyTheme();
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue LoadingProgressBridge::SetColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> colorArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(vm, nodeArg, nativeNode), true, panda::JSValueRef::Undefined(vm));
    bool isJsView = ArkTSUtils::IsJsView(vm, nodeArg);
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    auto loadingProgressModifier = nodeModifiers->getLoadingProgressModifier();
    CHECK_NULL_RETURN(loadingProgressModifier, panda::JSValueRef::Undefined(vm));
    Color color;
    RefPtr<ResourceObject> colorResObj;
    auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(nativeNode);
    if (!ArkTSUtils::ParseJsColorAlpha(vm, colorArg, color, colorResObj, nodeInfo)) {
        loadingProgressModifier->resetColor(nativeNode, isJsView);
    } else {
        auto colorRawPtr = AceType::RawPtr(colorResObj);
        loadingProgressModifier->setColorPtr(nativeNode, color.GetValue(), colorRawPtr);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue LoadingProgressBridge::ResetColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(vm, nodeArg, nativeNode), true, panda::JSValueRef::Undefined(vm));
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    auto loadingProgressModifier = nodeModifiers->getLoadingProgressModifier();
    CHECK_NULL_RETURN(loadingProgressModifier, panda::JSValueRef::Undefined(vm));
    loadingProgressModifier->resetColor(nativeNode, ArkTSUtils::IsJsView(vm, nodeArg));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue LoadingProgressBridge::SetEnableLoading(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> enableLoadingArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(vm, nodeArg, nativeNode), true, panda::JSValueRef::Undefined(vm));
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    auto loadingProgressModifier = nodeModifiers->getLoadingProgressModifier();
    CHECK_NULL_RETURN(loadingProgressModifier, panda::JSValueRef::Undefined(vm));
    bool boolValue = true;
    if (enableLoadingArg->IsBoolean()) {
        boolValue = enableLoadingArg->ToBoolean(vm)->Value();
    }
    loadingProgressModifier->setEnableLoading(nativeNode, boolValue);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue LoadingProgressBridge::ResetEnableLoading(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(vm, nodeArg, nativeNode), true, panda::JSValueRef::Undefined(vm));
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    auto loadingProgressModifier = nodeModifiers->getLoadingProgressModifier();
    CHECK_NULL_RETURN(loadingProgressModifier, panda::JSValueRef::Undefined(vm));
    loadingProgressModifier->resetEnableLoading(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue LoadingProgressBridge::SetForegroundColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    auto colorArg = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(vm, nodeArg, nativeNode), true, panda::JSValueRef::Undefined(vm));
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    auto loadingProgressModifier = nodeModifiers->getLoadingProgressModifier();
    CHECK_NULL_RETURN(loadingProgressModifier, panda::JSValueRef::Undefined(vm));
    bool isJsView = ArkTSUtils::IsJsView(vm, nodeArg);

    ForegroundColorStrategy strategy;
    if (ArkTSUtils::ParseJsColorStrategy(vm, colorArg, strategy)) {
        if (isJsView) {
            ViewAbstractModel::GetInstance()->SetForegroundColorStrategy(strategy);
            return panda::JSValueRef::Undefined(vm);
        }
        auto strategyInt = static_cast<uint32_t>(ForegroundColorStrategy::INVERT);
        GetArkUINodeModifiers()->getCommonModifier()->setForegroundColor(nativeNode, false, strategyInt, nullptr);
        return panda::JSValueRef::Undefined(vm);
    }
    Color foregroundColor;
    RefPtr<ResourceObject> foregroundColorResObj;
    auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(nativeNode);
    if (!ArkTSUtils::ParseJsColorAlpha(vm, colorArg, foregroundColor, foregroundColorResObj, nodeInfo)) {
        auto foregroundColorRawPtr = AceType::RawPtr(foregroundColorResObj);
        loadingProgressModifier->resetForegroundColor(nativeNode, isJsView, foregroundColorRawPtr);
    } else {
        auto foregroundColorRawPtr = AceType::RawPtr(foregroundColorResObj);
        loadingProgressModifier->setForegroundColorPtr(
            nativeNode, foregroundColor.GetValue(), foregroundColorRawPtr, isJsView);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue LoadingProgressBridge::ResetForegroundColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(vm, nodeArg, nativeNode), true, panda::JSValueRef::Undefined(vm));
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    auto loadingProgressModifier = nodeModifiers->getLoadingProgressModifier();
    CHECK_NULL_RETURN(loadingProgressModifier, panda::JSValueRef::Undefined(vm));
    RefPtr<ResourceObject> foregroundColorResObj;
    auto foregroundColorRawPtr = AceType::RawPtr(foregroundColorResObj);
    loadingProgressModifier->resetForegroundColor(nativeNode, ArkTSUtils::IsJsView(vm, nodeArg), foregroundColorRawPtr);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue LoadingProgressBridge::SetContentModifierBuilder(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto* frameNode = reinterpret_cast<FrameNode*>(firstArg->ToNativePointer(vm)->Value());
    if (!secondArg->IsObject(vm)) {
        LoadingProgressModelNG::SetBuilderFunc(frameNode, nullptr);
        return panda::JSValueRef::Undefined(vm);
    }
    panda::CopyableGlobal<panda::ObjectRef> obj(vm, secondArg);
    LoadingProgressModelNG::SetBuilderFunc(frameNode,
        [vm, frameNode, obj = std::move(obj), containerId = Container::CurrentId()](
            LoadingProgressConfiguration config) -> RefPtr<FrameNode> {
            panda::LocalScope pandaScope(vm);
            ContainerScope scope(containerId);
            auto context = ArkTSUtils::GetContext(vm);
            CHECK_EQUAL_RETURN(context->IsUndefined(), true, nullptr);
            const char* keysOfLoadingprogress[] = { "enableLoading", "enabled" };
            Local<JSValueRef> valuesOfLoadingprogress[] = { panda::BooleanRef::New(vm, config.enableloading_),
                panda::BooleanRef::New(vm, config.enabled_) };
            auto loadingprogress = panda::ObjectRef::NewWithNamedProperties(
                vm, ArraySize(keysOfLoadingprogress), keysOfLoadingprogress, valuesOfLoadingprogress);
            loadingprogress->SetNativePointerFieldCount(vm, 1);
            loadingprogress->SetNativePointerField(vm, 0, static_cast<void*>(frameNode));
            panda::Local<panda::JSValueRef> params[2] = { context, loadingprogress };
            panda::TryCatch trycatch(vm);
            auto jsObject = obj.ToLocal();
            auto makeFunc = jsObject->Get(vm, panda::StringRef::NewFromUtf8(vm, "makeContentModifierNode"));
            CHECK_EQUAL_RETURN(makeFunc->IsFunction(vm), false, nullptr);
            panda::Local<panda::FunctionRef> func = makeFunc;
            auto result = func->Call(vm, jsObject, params, 2);
            panda::JSNApi::ExecutePendingJob(vm);
            CHECK_EQUAL_RETURN(result.IsEmpty() || trycatch.HasCaught() || !result->IsObject(vm), true, nullptr);
            auto resultObj = result->ToObject(vm);
            panda::Local<panda::JSValueRef> nodeptr =
                resultObj->Get(vm, panda::StringRef::NewFromUtf8(vm, LOADINGPROGRESS_NODEPTR_OF_UINODE));
            CHECK_EQUAL_RETURN(nodeptr.IsEmpty() || nodeptr->IsUndefined() || nodeptr->IsNull(), true, nullptr);
            CHECK_NULL_RETURN(nodeptr->IsNativePointer(vm), nullptr);
            auto* frameNode = reinterpret_cast<FrameNode*>(nodeptr->ToNativePointer(vm)->Value());
            CHECK_NULL_RETURN(frameNode, nullptr);
            return AceType::Claim(frameNode);
        });
    return panda::JSValueRef::Undefined(vm);
}
} // namespace OHOS::Ace::NG
