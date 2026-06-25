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

#include "core/components_ng/pattern/lazy_grid_layout/bridge/arkts_native_lazy_grid_layout_bridge.h"

#include <memory>
#include <string>

#include "base/log/log_wrapper.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/lazy_grid_layout/lazy_grid_layout_model.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t NODE_ARG_INDEX = 0;
constexpr int32_t VALUE_ARG_INDEX = 1;
constexpr int32_t STICKY_STYLE_NONE = 0;
constexpr int32_t STICKY_STYLE_BOTH = 3;
constexpr int32_t VISIBLE_INDEX_PARAM_COUNT = 2;
constexpr int32_t SCROLL_INDEX_PARAM_COUNT = 2;

CalcDimension ParseLengthMetricsOrDefault(EcmaVM* vm, const Local<JSValueRef>& value)
{
    CalcDimension size;
    if (value.IsEmpty() || value->IsUndefined() || !ArkTSUtils::ParseJsLengthMetrics(vm, value, size) ||
        LessNotEqual(size.Value(), 0.0)) {
        size.SetValue(0.0);
        return size;
    }
    return size;
}

Local<JSValueRef> GetProperty(EcmaVM* vm, const Local<JSValueRef>& object, const char* key)
{
    CHECK_NULL_RETURN(vm, panda::Local<panda::JSValueRef>());
    CHECK_NULL_RETURN(key, panda::JSValueRef::Undefined(vm));
    if (object.IsEmpty() || !object->IsObject(vm)) {
        return panda::JSValueRef::Undefined(vm);
    }
    auto objectRef = object->ToObject(vm);
    if (objectRef.IsEmpty()) {
        return panda::JSValueRef::Undefined(vm);
    }
    return objectRef->Get(vm, panda::StringRef::NewFromUtf8(vm, key));
}

bool TryParseComponentContentNode(EcmaVM* vm, const Local<JSValueRef>& value, ArkUINodeHandle& contentNode)
{
    contentNode = nullptr;
    CHECK_NULL_RETURN(vm, false);
    if (value.IsEmpty() || value->IsUndefined() || value->IsNull() || !value->IsObject(vm)) {
        return false;
    }
    auto builderNode = GetProperty(vm, value, "builderNode_");
    if (builderNode.IsEmpty() || builderNode->IsUndefined() || builderNode->IsNull() || !builderNode->IsObject(vm)) {
        return false;
    }
    auto nodePtrValue = GetProperty(vm, builderNode, "nodePtr_");
    if (nodePtrValue.IsEmpty() || nodePtrValue->IsUndefined() || nodePtrValue->IsNull() ||
        !nodePtrValue->IsNativePointer(vm)) {
        return false;
    }
    auto nativePointer = nodePtrValue->ToNativePointer(vm);
    if (nativePointer.IsEmpty()) {
        return false;
    }
    // ComponentContent owns a BuilderNode internally; the native side only needs the built root node.
    contentNode = nodePtr(nativePointer->Value());
    return contentNode != nullptr;
}

void CallJsFunction(const panda::CopyableGlobal<panda::FunctionRef>& func, bool isJsView)
{
    auto vm = func.GetEcmaVM();
    CHECK_NULL_VOID(vm);
    panda::LocalScope pandaScope(vm);
    panda::TryCatch trycatch(vm);
    auto result = func->Call(vm, func.ToLocal(), nullptr, 0);
    if (isJsView) {
        ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
    }
}

RefPtr<UINode> BuildHeaderFooterNodeFromFunction(EcmaVM* vm, const Local<JSValueRef>& value)
{
    CHECK_NULL_RETURN(vm, nullptr);
    if (value.IsEmpty() || !value->IsFunction(vm)) {
        return nullptr;
    }
    panda::Local<panda::FunctionRef> func = value->ToObject(vm);
    if (func.IsEmpty()) {
        return nullptr;
    }
    auto* stack = ViewStackProcessor::GetInstance();
    CHECK_NULL_RETURN(stack, nullptr);
    auto isBuilderNode = stack->IsBuilderNode();
    auto isExportTexture = stack->IsExportTexture();
    // Run the CustomBuilder on an isolated stack so its nodes never leak into the surrounding component tree.
    ScopedViewStackProcessor builderViewStackProcessor;
    stack = ViewStackProcessor::GetInstance();
    CHECK_NULL_RETURN(stack, nullptr);
    stack->SetIsBuilderNode(isBuilderNode);
    stack->SetIsExportTexture(isExportTexture);
    panda::CopyableGlobal<panda::FunctionRef> globalFunc(vm, func);
    CallJsFunction(globalFunc, false);
    auto builtNode = stack->Finish();
    if (!builtNode) {
        TAG_LOGW(AceLogTag::ACE_LAZY_GRID, "LazyGridLayout header/footer builder produced no node");
    }
    return builtNode;
}

void CallOnVisibleIndexesChange(EcmaVM* vm, panda::Local<panda::FunctionRef> func)
{
    std::function<void(int32_t, int32_t)> callback = [func = panda::CopyableGlobal<panda::FunctionRef>(vm, func)](
                                                         const int32_t start, const int32_t end) {
        auto vm = func.GetEcmaVM();
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        panda::Local<panda::JSValueRef> params[SCROLL_INDEX_PARAM_COUNT] = {
            panda::NumberRef::New(vm, start),
            panda::NumberRef::New(vm, end),
        };
        auto result = func->Call(vm, func.ToLocal(), params, SCROLL_INDEX_PARAM_COUNT);
        ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
    };
    LazyGridLayoutModel::SetOnVisibleIndexesChange(std::move(callback));
}
} // namespace

void RegisterLazyGridLayoutBridgeAttributes(panda::Local<panda::ObjectRef> object, panda::ecmascript::EcmaVM* vm)
{
    LazyGridLayoutBridge::RegisterLazyGridLayoutAttributes(object, vm);
}

void RegisterLazyVGridLayoutBridgeAttributes(panda::Local<panda::ObjectRef> object, panda::ecmascript::EcmaVM* vm)
{
    LazyVGridLayoutBridge::RegisterLazyVGridLayoutAttributes(object, vm);
}

void LazyGridLayoutBridge::RegisterLazyGridLayoutAttributes(Local<panda::ObjectRef> object, EcmaVM* vm)
{
    const char* functionNames[] = {
        "setColumnsGap",
        "resetColumnsGap",
        "setRowsGap",
        "resetRowsGap",
        "setSticky",
        "resetSticky",
        "setHeader",
        "resetHeader",
        "setFooter",
        "resetFooter",
        "setOnVisibleIndexesChange",
        "resetOnVisibleIndexesChange",
    };
    Local<JSValueRef> funcValues[] = {
        panda::FunctionRef::New(vm, LazyGridLayoutBridge::SetColumnsGap),
        panda::FunctionRef::New(vm, LazyGridLayoutBridge::ResetColumnsGap),
        panda::FunctionRef::New(vm, LazyGridLayoutBridge::SetRowsGap),
        panda::FunctionRef::New(vm, LazyGridLayoutBridge::ResetRowsGap),
        panda::FunctionRef::New(vm, LazyGridLayoutBridge::SetSticky),
        panda::FunctionRef::New(vm, LazyGridLayoutBridge::ResetSticky),
        panda::FunctionRef::New(vm, LazyGridLayoutBridge::SetHeader),
        panda::FunctionRef::New(vm, LazyGridLayoutBridge::ResetHeader),
        panda::FunctionRef::New(vm, LazyGridLayoutBridge::SetFooter),
        panda::FunctionRef::New(vm, LazyGridLayoutBridge::ResetFooter),
        panda::FunctionRef::New(vm, LazyGridLayoutBridge::SetOnVisibleIndexesChange),
        panda::FunctionRef::New(vm, LazyGridLayoutBridge::ResetOnVisibleIndexesChange),
    };
    auto lazyGridLayout =
        panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(functionNames), functionNames, funcValues);
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "lazyGridLayout"), lazyGridLayout);
}

ArkUINativeModuleValue LazyGridLayoutBridge::SetColumnsGap(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> node = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> arg_size = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(vm, node, nativeNode), true, panda::JSValueRef::Undefined(vm));

    CalcDimension size;
    if (ArkTSUtils::IsJsView(vm, node)) {
        size = ParseLengthMetricsOrDefault(vm, arg_size);
    } else if (arg_size->IsUndefined() || !ArkTSUtils::ParseJsLengthMetrics(vm, arg_size, size)) {
        GetArkUINodeModifiers()->getLazyGridLayoutModifier()->resetColumnsGap(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }

    std::string calcStr;
    struct ArkUIResourceLength columnGap = { 0.0, 0, nullptr };
    if (size.Unit() == DimensionUnit::CALC) {
        columnGap.unit = static_cast<int32_t>(DimensionUnit::CALC);
        calcStr = size.CalcValue();
        columnGap.string = calcStr.c_str();
    } else {
        columnGap.value = size.Value();
        columnGap.unit = static_cast<int32_t>(size.Unit());
    }
    GetArkUINodeModifiers()->getLazyGridLayoutModifier()->setColumnsGap(nativeNode, &columnGap);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue LazyGridLayoutBridge::ResetColumnsGap(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> node = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(node->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(node->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getLazyGridLayoutModifier()->resetColumnsGap(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue LazyGridLayoutBridge::SetRowsGap(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> node = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> arg_size = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(vm, node, nativeNode), true, panda::JSValueRef::Undefined(vm));

    CalcDimension size;
    if (ArkTSUtils::IsJsView(vm, node)) {
        size = ParseLengthMetricsOrDefault(vm, arg_size);
    } else if (arg_size->IsUndefined() || !ArkTSUtils::ParseJsLengthMetrics(vm, arg_size, size)) {
        GetArkUINodeModifiers()->getLazyGridLayoutModifier()->resetRowsGap(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }

    std::string calcStr;
    struct ArkUIResourceLength rowsGap = { 0.0, 0, nullptr };
    if (size.Unit() == DimensionUnit::CALC) {
        rowsGap.unit = static_cast<int32_t>(DimensionUnit::CALC);
        calcStr = size.CalcValue();
        rowsGap.string = calcStr.c_str();
    } else {
        rowsGap.value = size.Value();
        rowsGap.unit = static_cast<int32_t>(size.Unit());
    }
    GetArkUINodeModifiers()->getLazyGridLayoutModifier()->setRowsGap(nativeNode, &rowsGap);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue LazyGridLayoutBridge::ResetRowsGap(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> node = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(node->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(node->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getLazyGridLayoutModifier()->resetRowsGap(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue LazyGridLayoutBridge::SetSticky(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> node = runtimeCallInfo->GetCallArgRef(NODE_ARG_INDEX);
    Local<JSValueRef> argSticky = runtimeCallInfo->GetCallArgRef(VALUE_ARG_INDEX);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(vm, node, nativeNode), true, panda::JSValueRef::Undefined(vm));

    if (ArkTSUtils::IsJsView(vm, node)) {
        auto stickyStyle = STICKY_STYLE_NONE;
        if (!argSticky.IsEmpty() && !argSticky->IsUndefined() && !argSticky->IsNull() && argSticky->IsNumber()) {
            auto  stickyValue = argSticky->Int32Value(vm);
            if (stickyValue >= STICKY_STYLE_NONE && stickyValue <= STICKY_STYLE_BOTH) {
                stickyStyle = stickyValue;
            }
        }
        GetArkUINodeModifiers()->getLazyGridLayoutModifier()->setSticky(nativeNode, stickyStyle);
        return panda::JSValueRef::Undefined(vm);
    }

    if (argSticky.IsEmpty() || argSticky->IsUndefined() || argSticky->IsNull() || !argSticky->IsNumber()) {
        GetArkUINodeModifiers()->getLazyGridLayoutModifier()->resetSticky(nativeNode);
    } else {
        auto stickyValue = argSticky->Int32Value(vm);
        if (stickyValue < STICKY_STYLE_NONE || stickyValue > STICKY_STYLE_BOTH) {
            stickyValue = STICKY_STYLE_NONE;
        }
        GetArkUINodeModifiers()->getLazyGridLayoutModifier()->setSticky(nativeNode, stickyValue);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue LazyGridLayoutBridge::ResetSticky(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> node = runtimeCallInfo->GetCallArgRef(NODE_ARG_INDEX);
    CHECK_NULL_RETURN(node->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(node->ToNativePointer(vm)->Value());
    auto* modifier = GetArkUINodeModifiers()->getLazyGridLayoutModifier();
    CHECK_NULL_RETURN(modifier, panda::JSValueRef::Undefined(vm));
    modifier->resetSticky(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue LazyGridLayoutBridge::SetHeader(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> node = runtimeCallInfo->GetCallArgRef(NODE_ARG_INDEX);
    Local<JSValueRef> headerArg = runtimeCallInfo->GetCallArgRef(VALUE_ARG_INDEX);
    if (ArkTSUtils::IsJsView(vm, node)) {
        if (!headerArg.IsEmpty() && headerArg->IsFunction(vm)) {
            panda::Local<panda::FunctionRef> func = headerArg->ToObject(vm);
            if (func.IsEmpty()) {
                return panda::JSValueRef::Undefined(vm);
            }
            std::function<void()> headerAction = [func = panda::CopyableGlobal(vm, func)]() {
                CallJsFunction(func, true);
            };
            LazyGridLayoutModel::SetHeader(std::move(headerAction));
        } else {
            LazyGridLayoutModel::RemoveHeader();
        }
        return panda::JSValueRef::Undefined(vm);
    }
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(vm, node, nativeNode), true, panda::JSValueRef::Undefined(vm));
    // h/f/s: ArkLazyGridLayout.ts declares header() as `CustomBuilder | ComponentContent`. Handle the CustomBuilder
    // (function) form first by running it on an isolated stack so its nodes do not leak into the caller tree.
    if (!headerArg.IsEmpty() && headerArg->IsFunction(vm)) {
        auto builtHeaderNode = BuildHeaderFooterNodeFromFunction(vm, headerArg);
        auto* frameNode = reinterpret_cast<FrameNode*>(nativeNode);
        CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
        LazyGridLayoutModel::SetHeader(frameNode, builtHeaderNode);
        return panda::JSValueRef::Undefined(vm);
    }
    ArkUINodeHandle headerNode = nullptr;
    if (TryParseComponentContentNode(vm, headerArg, headerNode)) {
        GetArkUINodeModifiers()->getLazyGridLayoutModifier()->setHeader(nativeNode, headerNode);
    } else {
        GetArkUINodeModifiers()->getLazyGridLayoutModifier()->resetHeader(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue LazyGridLayoutBridge::ResetHeader(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> node = runtimeCallInfo->GetCallArgRef(NODE_ARG_INDEX);
    CHECK_NULL_RETURN(node->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(node->ToNativePointer(vm)->Value());
    auto* modifier = GetArkUINodeModifiers()->getLazyGridLayoutModifier();
    CHECK_NULL_RETURN(modifier, panda::JSValueRef::Undefined(vm));
    modifier->resetHeader(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue LazyGridLayoutBridge::SetFooter(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> node = runtimeCallInfo->GetCallArgRef(NODE_ARG_INDEX);
    Local<JSValueRef> footerArg = runtimeCallInfo->GetCallArgRef(VALUE_ARG_INDEX);
    if (ArkTSUtils::IsJsView(vm, node)) {
        if (!footerArg.IsEmpty() && footerArg->IsFunction(vm)) {
            panda::Local<panda::FunctionRef> func = footerArg->ToObject(vm);
            if (func.IsEmpty()) {
                return panda::JSValueRef::Undefined(vm);
            }
            std::function<void()> footerAction = [func = panda::CopyableGlobal(vm, func)]() {
                CallJsFunction(func, true);
            };
            LazyGridLayoutModel::SetFooter(std::move(footerAction));
        } else {
            LazyGridLayoutModel::RemoveFooter();
        }
        return panda::JSValueRef::Undefined(vm);
    }
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(vm, node, nativeNode), true, panda::JSValueRef::Undefined(vm));
    if (!footerArg.IsEmpty() && footerArg->IsFunction(vm)) {
        auto builtFooterNode = BuildHeaderFooterNodeFromFunction(vm, footerArg);
        auto* frameNode = reinterpret_cast<FrameNode*>(nativeNode);
        CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
        LazyGridLayoutModel::SetFooter(frameNode, builtFooterNode);
        return panda::JSValueRef::Undefined(vm);
    }
    ArkUINodeHandle footerNode = nullptr;
    if (TryParseComponentContentNode(vm, footerArg, footerNode)) {
        GetArkUINodeModifiers()->getLazyGridLayoutModifier()->setFooter(nativeNode, footerNode);
    } else {
        GetArkUINodeModifiers()->getLazyGridLayoutModifier()->resetFooter(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue LazyGridLayoutBridge::ResetFooter(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> node = runtimeCallInfo->GetCallArgRef(NODE_ARG_INDEX);
    CHECK_NULL_RETURN(node->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(node->ToNativePointer(vm)->Value());
    auto* modifier = GetArkUINodeModifiers()->getLazyGridLayoutModifier();
    CHECK_NULL_RETURN(modifier, panda::JSValueRef::Undefined(vm));
    modifier->resetFooter(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue LazyGridLayoutBridge::SetOnVisibleIndexesChange(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> node = runtimeCallInfo->GetCallArgRef(NODE_ARG_INDEX);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(VALUE_ARG_INDEX);
    if (ArkTSUtils::IsJsView(vm, node)) {
        if (!callbackArg.IsEmpty() && !callbackArg->IsUndefined() && !callbackArg->IsNull() &&
            callbackArg->IsFunction(vm)) {
            panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
            CallOnVisibleIndexesChange(vm, func);
        } else {
            LazyGridLayoutModel::SetOnVisibleIndexesChange(nullptr);
        }
        return panda::JSValueRef::Undefined(vm);
    }
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(vm, node, nativeNode), true, panda::JSValueRef::Undefined(vm));
    if (callbackArg.IsEmpty() || callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        GetArkUINodeModifiers()->getLazyGridLayoutModifier()->resetOnVisibleIndexesChange(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }

    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    if (func.IsEmpty()) {
        return panda::JSValueRef::Undefined(vm);
    }
    // Transfer a heap-owned callback object across the C ABI so the modifier can take ownership immediately without
    // relying on a stack address that expires when this bridge call returns.
    auto callback = std::make_unique<std::function<void(int32_t, int32_t)>>(
        [func = panda::CopyableGlobal(vm, func)](const int32_t start, const int32_t end) {
            auto vm = func.GetEcmaVM();
            panda::LocalScope pandaScope(vm);
            panda::TryCatch trycatch(vm);
            panda::Local<panda::NumberRef> startParam = panda::NumberRef::New(vm, start);
            panda::Local<panda::NumberRef> endParam = panda::NumberRef::New(vm, end);
            panda::Local<panda::JSValueRef> params[VISIBLE_INDEX_PARAM_COUNT] = { startParam, endParam };
            func->Call(vm, func.ToLocal(), params, VISIBLE_INDEX_PARAM_COUNT);
        });
    GetArkUINodeModifiers()->getLazyGridLayoutModifier()->setOnVisibleIndexesChange(nativeNode, callback.release());
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue LazyGridLayoutBridge::ResetOnVisibleIndexesChange(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> node = runtimeCallInfo->GetCallArgRef(NODE_ARG_INDEX);
    CHECK_NULL_RETURN(node->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(node->ToNativePointer(vm)->Value());
    auto* modifier = GetArkUINodeModifiers()->getLazyGridLayoutModifier();
    CHECK_NULL_RETURN(modifier, panda::JSValueRef::Undefined(vm));
    modifier->resetOnVisibleIndexesChange(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

void LazyVGridLayoutBridge::RegisterLazyVGridLayoutAttributes(Local<panda::ObjectRef> object, EcmaVM* vm)
{
    const char* functionNames[] = {
        "create",
        "setColumnsTemplate",
        "resetColumnsTemplate",
    };
    Local<JSValueRef> funcValues[] = {
        panda::FunctionRef::New(vm, LazyVGridLayoutBridge::Create),
        panda::FunctionRef::New(vm, LazyVGridLayoutBridge::SetColumnsTemplate),
        panda::FunctionRef::New(vm, LazyVGridLayoutBridge::ResetColumnsTemplate),
    };
    auto lazyVGridLayout =
        panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(functionNames), functionNames, funcValues);
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "lazyVGridLayout"), lazyVGridLayout);
}

ArkUINativeModuleValue LazyVGridLayoutBridge::Create(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    GetArkUINodeModifiers()->getLazyGridLayoutModifier()->create();
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue LazyVGridLayoutBridge::SetColumnsTemplate(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> node = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> arg_columnsTemplate = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(vm, node, nativeNode), true, panda::JSValueRef::Undefined(vm));

    if (ArkTSUtils::IsJsView(vm, node) || arg_columnsTemplate->IsString(vm)) {
        std::string columnsTemplate = arg_columnsTemplate->ToString(vm)->ToString(vm);
        GetArkUINodeModifiers()->getLazyGridLayoutModifier()->setColumnsTemplate(nativeNode, columnsTemplate.c_str());
    } else {
        GetArkUINodeModifiers()->getLazyGridLayoutModifier()->resetColumnsTemplate(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue LazyVGridLayoutBridge::ResetColumnsTemplate(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> node = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(node->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(node->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getLazyGridLayoutModifier()->resetColumnsTemplate(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
} // namespace OHOS::Ace::NG
