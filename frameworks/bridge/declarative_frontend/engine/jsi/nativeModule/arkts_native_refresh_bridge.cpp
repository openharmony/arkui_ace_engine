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
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_refresh_bridge.h"

#include "frameworks/bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"

namespace OHOS::Ace::NG {
constexpr int32_t CALL_ARG_0 = 0;
constexpr int32_t CALL_ARG_1 = 1;
constexpr int32_t NUM_0 = 0;
constexpr int32_t NUM_1 = 1;
ArkUINativeModuleValue RefreshBridege::SetRefreshOffset(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    Local<JSValueRef> valueArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    CalcDimension value(0.0f);
    if (valueArg->IsNull() || valueArg->IsUndefined() || !ArkTSUtils::ParseJsDimensionVp(vm, valueArg, value)) {
        GetArkUINodeModifiers()->getRefreshModifier()->resetRefreshOffset(nativeNode);
    } else {
        GetArkUINodeModifiers()->getRefreshModifier()->setRefreshOffset(
            nativeNode, value.Value(), static_cast<int>(value.Unit()));
    }

    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue RefreshBridege::ResetRefreshOffset(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getRefreshModifier()->resetRefreshOffset(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue RefreshBridege::SetPullToRefresh(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    Local<JSValueRef> valueArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    if (valueArg->IsBoolean()) {
        bool value = valueArg->ToBoolean(vm)->Value();
        GetArkUINodeModifiers()->getRefreshModifier()->setPullToRefresh(nativeNode, value);
    } else {
        GetArkUINodeModifiers()->getRefreshModifier()->resetPullToRefresh(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue RefreshBridege::ResetPullToRefresh(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getRefreshModifier()->resetPullToRefresh(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue RefreshBridege::SetPullDownRatio(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    Local<JSValueRef> valueArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    if (valueArg->IsNumber()) {
        float value = std::clamp(static_cast<float>(valueArg->ToNumber(vm)->Value()), 0.f, 1.f);
        GetArkUINodeModifiers()->getRefreshModifier()->setPullDownRatio(nativeNode, value);
    } else {
        GetArkUINodeModifiers()->getRefreshModifier()->resetPullDownRatio(nativeNode);
    }

    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue RefreshBridege::ResetPullDownRatio(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getRefreshModifier()->resetPullDownRatio(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue RefreshBridege::SetOnStateChange(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        GetArkUINodeModifiers()->getRefreshModifier()->resetRefreshOnStateChangeCallback(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);

    std::function<void(RefreshStatus)> callback = [vm, frameNode, func = panda::CopyableGlobal(vm, func)](
                                                      RefreshStatus stateChange) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
        panda::Local<panda::JSValueRef> params[NUM_1] = { panda::NumberRef::New(vm, static_cast<int>(stateChange)) };
        func->Call(vm, func.ToLocal(), params, NUM_1);
    };
    GetArkUINodeModifiers()->getRefreshModifier()->setRefreshOnStateChangeCallback(
        nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue RefreshBridege::ResetOnStateChange(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getRefreshModifier()->resetRefreshOnStateChangeCallback(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue RefreshBridege::SetOnRefreshing(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        GetArkUINodeModifiers()->getRefreshModifier()->resetOnRefreshingCallback(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);

    std::function<void()> callback = [vm, frameNode, func = panda::CopyableGlobal(vm, func)]() {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
        func->Call(vm, func.ToLocal(), nullptr, NUM_0);
    };
    GetArkUINodeModifiers()->getRefreshModifier()->setOnRefreshingCallback(
        nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue RefreshBridege::ResetOnRefreshing(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getRefreshModifier()->resetOnRefreshingCallback(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue RefreshBridege::SetOnOffsetChange(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        GetArkUINodeModifiers()->getRefreshModifier()->resetRefreshOnOffsetChangeCallback(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);

    std::function<void(const float)> callback = [vm, frameNode, func = panda::CopyableGlobal(vm, func)](
                                                    const float offsetChange) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
        panda::Local<panda::JSValueRef> params[NUM_1] = { panda::NumberRef::New(vm, offsetChange) };
        func->Call(vm, func.ToLocal(), params, NUM_1);
    };
    GetArkUINodeModifiers()->getRefreshModifier()->setRefreshOnOffsetChangeCallback(
        nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue RefreshBridege::ResetOnOffsetChange(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getRefreshModifier()->resetRefreshOnOffsetChangeCallback(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue RefreshBridege::SetMaxPullDownDistance(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    Local<JSValueRef> valueArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    auto refreshModifier = nodeModifiers->getRefreshModifier();
    CHECK_NULL_RETURN(refreshModifier, panda::JSValueRef::Undefined(vm));
    if (valueArg->IsNumber()) {
        float value = static_cast<float>(valueArg->ToNumber(vm)->Value());
        value = std::max(value, 0.0f);
        refreshModifier->setMaxPullDownDistance(nativeNode, value);
    } else {
        refreshModifier->resetMaxPullDownDistance(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue RefreshBridege::ResetMaxPullDownDistance(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());

    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    auto refreshModifier = nodeModifiers->getRefreshModifier();
    CHECK_NULL_RETURN(refreshModifier, panda::JSValueRef::Undefined(vm));
    refreshModifier->resetMaxPullDownDistance(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
} // namespace OHOS::Ace::NG
