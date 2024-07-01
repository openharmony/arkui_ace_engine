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
ArkUINativeModuleValue RefreshBridege::SetRefreshOffset(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    Local<JSValueRef> valueArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
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
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getRefreshModifier()->resetPullDownRatio(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
} // namespace OHOS::Ace::NG