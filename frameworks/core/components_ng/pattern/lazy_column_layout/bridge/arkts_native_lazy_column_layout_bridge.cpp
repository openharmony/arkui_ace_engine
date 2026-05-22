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

#include "core/components_ng/pattern/lazy_column_layout/bridge/arkts_native_lazy_column_layout_bridge.h"

#include "base/utils/utils.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/lazy_column_layout/lazy_column_layout_model.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t NODE_ARG_INDEX = 0;
constexpr int32_t VALUE_ARG_INDEX = 1;
constexpr int32_t SCROLL_INDEX_PARAM_COUNT = 2;
constexpr Dimension DEFAULT_SPACE = 0.0_vp;

bool IsStackNodeArg(EcmaVM* vm, const Local<JSValueRef>& value)
{
    return vm && !value.IsEmpty() && value->IsBoolean() && value->ToBoolean(vm)->Value();
}

void CallOnVisibleIndexesChange(EcmaVM* vm, panda::Local<panda::FunctionRef> func)
{
    std::function<void(int32_t, int32_t)> callback = [vm, func = panda::CopyableGlobal<panda::FunctionRef>(vm, func)](
                                                         const int32_t start, const int32_t end) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        panda::Local<panda::JSValueRef> params[SCROLL_INDEX_PARAM_COUNT] = {
            panda::NumberRef::New(vm, start),
            panda::NumberRef::New(vm, end),
        };
        func->Call(vm, func.ToLocal(), params, SCROLL_INDEX_PARAM_COUNT);
    };
    LazyColumnLayoutModel::SetOnVisibleIndexesChange(std::move(callback));
}
} // namespace

void LazyColumnLayoutBridge::RegisterLazyColumnLayoutAttributes(
    Local<panda::ObjectRef> object, EcmaVM* vm)
{
    const char* functionNames[] = {
        "create",
        "resetSpace",
        "setSpace",
        "resetAlignItems",
        "setAlignItems",
        "resetOnVisibleIndexesChange",
        "setOnVisibleIndexesChange",
    };
    Local<JSValueRef> funcValues[] = {
        panda::FunctionRef::New(vm, LazyColumnLayoutBridge::Create),
        panda::FunctionRef::New(vm, LazyColumnLayoutBridge::ResetSpace),
        panda::FunctionRef::New(vm, LazyColumnLayoutBridge::SetSpace),
        panda::FunctionRef::New(vm, LazyColumnLayoutBridge::ResetAlignItems),
        panda::FunctionRef::New(vm, LazyColumnLayoutBridge::SetAlignItems),
        panda::FunctionRef::New(vm, LazyColumnLayoutBridge::ResetOnVisibleIndexesChange),
        panda::FunctionRef::New(vm, LazyColumnLayoutBridge::SetOnVisibleIndexesChange),
    };
    auto lazyColumnLayout =
        panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(functionNames), functionNames, funcValues);
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "lazyColumnLayout"), lazyColumnLayout);
}

ArkUINativeModuleValue LazyColumnLayoutBridge::Create(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    GetArkUINodeModifiers()->getLazyColumnLayoutModifier()->create();
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue LazyColumnLayoutBridge::SetSpace(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    auto nodeArg = runtimeCallInfo->GetCallArgRef(NODE_ARG_INDEX);
    auto valueArg = runtimeCallInfo->GetCallArgRef(VALUE_ARG_INDEX);
    struct ArkUIResourceLength space;
    CalcDimension length;
    if (ArkTSUtils::ParseJsLengthMetrics(vm, valueArg, length) && GreatNotEqual(length.Value(), 0.0)) {
        if (length.Unit() == DimensionUnit::CALC) {
            space.string = length.CalcValue().c_str();
            space.value = 0.0;
            space.unit = static_cast<int32_t>(DimensionUnit::CALC);
        } else {
            space.value = length.Value();
            space.unit = static_cast<int32_t>(length.Unit());
        }
    } else {
        length = DEFAULT_SPACE;
        space.value = 0.0;
        space.unit = static_cast<int32_t>(DimensionUnit::VP);
    }
    if (IsStackNodeArg(vm, nodeArg)) {
        LazyColumnLayoutModel::SetSpace(length);
    } else {
        auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
        GetArkUINodeModifiers()->getLazyColumnLayoutModifier()->setSpace(nativeNode, &space);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue LazyColumnLayoutBridge::ResetSpace(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    auto nodeArg = runtimeCallInfo->GetCallArgRef(NODE_ARG_INDEX);
    if (IsStackNodeArg(vm, nodeArg)) {
        LazyColumnLayoutModel::SetSpace(DEFAULT_SPACE);
    } else {
        auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
        GetArkUINodeModifiers()->getLazyColumnLayoutModifier()->resetSpace(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue LazyColumnLayoutBridge::SetAlignItems(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    auto nodeArg = runtimeCallInfo->GetCallArgRef(NODE_ARG_INDEX);
    auto valueArg = runtimeCallInfo->GetCallArgRef(VALUE_ARG_INDEX);
    auto align = static_cast<int32_t>(HorizontalAlign::CENTER);
    if (valueArg->IsNumber()) {
        align = valueArg->Int32Value(vm);
        if (align < static_cast<int32_t>(HorizontalAlign::START) ||
            align > static_cast<int32_t>(HorizontalAlign::END)) {
            align = static_cast<int32_t>(HorizontalAlign::CENTER);
        }
    }
    if (IsStackNodeArg(vm, nodeArg)) {
        LazyColumnLayoutModel::SetAlignItems(static_cast<HorizontalAlign>(align));
    } else {
        auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
        GetArkUINodeModifiers()->getLazyColumnLayoutModifier()->setAlignItems(nativeNode, align);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue LazyColumnLayoutBridge::ResetAlignItems(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    auto nodeArg = runtimeCallInfo->GetCallArgRef(NODE_ARG_INDEX);
    if (IsStackNodeArg(vm, nodeArg)) {
        LazyColumnLayoutModel::SetAlignItems(HorizontalAlign::CENTER);
    } else {
        auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
        GetArkUINodeModifiers()->getLazyColumnLayoutModifier()->resetAlignItems(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue LazyColumnLayoutBridge::SetOnVisibleIndexesChange(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NODE_ARG_INDEX);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(VALUE_ARG_INDEX);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    auto isStackNodeArg = IsStackNodeArg(vm, nodeArg);
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        if (isStackNodeArg) {
            LazyColumnLayoutModel::SetOnVisibleIndexesChange(nullptr);
        } else {
            GetArkUINodeModifiers()->getLazyColumnLayoutModifier()->resetOnVisibleIndexesChange(nativeNode);
        }
        return panda::JSValueRef::Undefined(vm);
    }
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    if (isStackNodeArg) {
        CallOnVisibleIndexesChange(vm, func);
        return panda::JSValueRef::Undefined(vm);
    }
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    std::function<void(int32_t, int32_t)> callback = [vm, node = AceType::WeakClaim(frameNode),
                                                         func = panda::CopyableGlobal<panda::FunctionRef>(vm, func)](
                                                         const int32_t start, const int32_t end) {
            panda::LocalScope pandaScope(vm);
            panda::TryCatch trycatch(vm);
            PipelineContext::SetCallBackNode(node);
            panda::Local<panda::JSValueRef> params[SCROLL_INDEX_PARAM_COUNT] = {
                panda::NumberRef::New(vm, start),
                panda::NumberRef::New(vm, end),
            };
            func->Call(vm, func.ToLocal(), params, SCROLL_INDEX_PARAM_COUNT);
        };
    GetArkUINodeModifiers()->getLazyColumnLayoutModifier()->setOnVisibleIndexesChange(
        nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue LazyColumnLayoutBridge::ResetOnVisibleIndexesChange(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    auto nodeArg = runtimeCallInfo->GetCallArgRef(NODE_ARG_INDEX);
    if (IsStackNodeArg(vm, nodeArg)) {
        LazyColumnLayoutModel::SetOnVisibleIndexesChange(nullptr);
    } else {
        auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
        GetArkUINodeModifiers()->getLazyColumnLayoutModifier()->resetOnVisibleIndexesChange(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}
} // namespace OHOS::Ace::NG
