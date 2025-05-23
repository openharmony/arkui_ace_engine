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
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_web_bridge.h"

#include "base/log/log.h"
#include "base/utils/string_utils.h"
#include "base/utils/utils.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"
#include "bridge/declarative_frontend/jsview/js_web.h"
#include "core/components_ng/pattern/web/web_model_ng.h"

namespace OHOS::Ace::NG {
constexpr int32_t CALL_ARG_0 = 0;
constexpr int32_t CALL_ARG_1 = 1;
constexpr int32_t CALL_ARG_2 = 2;

ArkUINativeModuleValue WebBridge::SetJavaScriptAccess(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (secondArg->IsBoolean()) {
        bool enable = secondArg->ToBoolean(vm)->Value();
        GetArkUINodeModifiers()->getWebModifier()->setJavaScriptAccess(nativeNode, enable);
    } else {
        GetArkUINodeModifiers()->getWebModifier()->resetJavaScriptAccess(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WebBridge::ResetJavaScriptAccess(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getWebModifier()->resetJavaScriptAccess(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WebBridge::SetFileAccessEnabled(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (secondArg->IsBoolean()) {
        bool enable = secondArg->ToBoolean(vm)->Value();
        GetArkUINodeModifiers()->getWebModifier()->setFileAccessEnabled(nativeNode, enable);
    } else {
        GetArkUINodeModifiers()->getWebModifier()->resetFileAccessEnabled(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WebBridge::ResetFileAccessEnabled(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getWebModifier()->resetFileAccessEnabled(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WebBridge::SetDomStorageAccessEnabled(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (secondArg->IsBoolean()) {
        bool enable = secondArg->ToBoolean(vm)->Value();
        GetArkUINodeModifiers()->getWebModifier()->setDomStorageAccessEnabled(nativeNode, enable);
    } else {
        GetArkUINodeModifiers()->getWebModifier()->resetDomStorageAccessEnabled(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WebBridge::ResetDomStorageAccessEnabled(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getWebModifier()->resetDomStorageAccessEnabled(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WebBridge::SetMixedMode(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    int mode = secondArg->Int32Value(vm);
    GetArkUINodeModifiers()->getWebModifier()->setMixedMode(nativeNode, mode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WebBridge::ResetMixedMode(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getWebModifier()->resetMixedMode(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WebBridge::SetZoomAccessEnabled(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (secondArg->IsBoolean()) {
        bool enable = secondArg->ToBoolean(vm)->Value();
        GetArkUINodeModifiers()->getWebModifier()->setZoomAccessEnabled(nativeNode, enable);
    } else {
        GetArkUINodeModifiers()->getWebModifier()->resetZoomAccessEnabled(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WebBridge::ResetZoomAccessEnabled(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getWebModifier()->resetZoomAccessEnabled(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WebBridge::SetCacheMode(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    int mode = secondArg->Int32Value(vm);
    GetArkUINodeModifiers()->getWebModifier()->setCacheMode(nativeNode, mode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WebBridge::ResetCacheMode(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getWebModifier()->resetCacheMode(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WebBridge::SetDarkMode(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    int mode = secondArg->Int32Value(vm);
    GetArkUINodeModifiers()->getWebModifier()->setDarkMode(nativeNode, mode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WebBridge::ResetDarkMode(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getWebModifier()->resetDarkMode(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WebBridge::SetMultiWindowAccessEnabled(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (secondArg->IsBoolean()) {
        bool enable = secondArg->ToBoolean(vm)->Value();
        GetArkUINodeModifiers()->getWebModifier()->setMultiWindowAccessEnabled(nativeNode, enable);
    } else {
        GetArkUINodeModifiers()->getWebModifier()->resetMultiWindowAccessEnabled(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WebBridge::ResetMultiWindowAccessEnabled(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getWebModifier()->resetMultiWindowAccessEnabled(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WebBridge::SetAllowWindowOpenMethod(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (secondArg->IsBoolean()) {
        bool enable = secondArg->ToBoolean(vm)->Value();
        GetArkUINodeModifiers()->getWebModifier()->setAllowWindowOpenMethod(nativeNode, enable);
    } else {
        GetArkUINodeModifiers()->getWebModifier()->resetAllowWindowOpenMethod(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WebBridge::ResetAllowWindowOpenMethod(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getWebModifier()->resetAllowWindowOpenMethod(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WebBridge::SetKeyboardAvoidMode(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    int mode = secondArg->Int32Value(vm);
    GetArkUINodeModifiers()->getWebModifier()->setKeyboardAvoidMode(nativeNode, mode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WebBridge::ResetKeyboardAvoidMode(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getWebModifier()->resetKeyboardAvoidMode(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WebBridge::SetOnControllerAttached(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        GetArkUINodeModifiers()->getWebModifier()->resetOnControllerAttached(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::NativePointerRef::New(vm, nullptr));
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);

    std::function<void()> callback = [vm, frameNode, func = panda::CopyableGlobal(vm, func)]() {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
        func->Call(vm, func.ToLocal(), nullptr, CALL_ARG_0);
    };
    GetArkUINodeModifiers()->getWebModifier()->setOnControllerAttached(nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WebBridge::ResetOnControllerAttached(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getWebModifier()->resetOnControllerAttached(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WebBridge::SetVerticalScrollBarAccessEnabled(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (secondArg->IsBoolean()) {
        bool enable = secondArg->ToBoolean(vm)->Value();
        GetArkUINodeModifiers()->getWebModifier()->setVerticalScrollBarAccessEnabled(nativeNode, enable);
    } else {
        GetArkUINodeModifiers()->getWebModifier()->resetVerticalScrollBarAccessEnabled(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WebBridge::ResetVerticalScrollBarAccessEnabled(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getWebModifier()->resetVerticalScrollBarAccessEnabled(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WebBridge::SetHorizontalScrollBarAccessEnabled(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (secondArg->IsBoolean()) {
        bool enable = secondArg->ToBoolean(vm)->Value();
        GetArkUINodeModifiers()->getWebModifier()->setHorizontalScrollBarAccessEnabled(nativeNode, enable);
    } else {
        GetArkUINodeModifiers()->getWebModifier()->resetHorizontalScrollBarAccessEnabled(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WebBridge::ResetHorizontalScrollBarAccessEnabled(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getWebModifier()->resetHorizontalScrollBarAccessEnabled(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WebBridge::SetTextZoomRatio(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    int mode = secondArg->Int32Value(vm);
    GetArkUINodeModifiers()->getWebModifier()->setTextZoomRatio(nativeNode, mode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WebBridge::ResetTextZoomRatio(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getWebModifier()->resetTextZoomRatio(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WebBridge::SetInitialScale(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (secondArg->IsNumber()) {
        float value = static_cast<float>(secondArg->ToNumber(vm)->Value());
        GetArkUINodeModifiers()->getWebModifier()->setInitialScale(nativeNode, value);
    } else {
        GetArkUINodeModifiers()->getWebModifier()->resetInitialScale(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WebBridge::ResetInitialScale(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getWebModifier()->resetInitialScale(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WebBridge::SetOnScroll(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(1);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        GetArkUINodeModifiers()->getWebModifier()->resetOnScrollCallBack(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);

    std::function<void(WebOnScrollEvent&)> callback = [vm, frameNode, func = panda::CopyableGlobal(vm, func)](
                                                          WebOnScrollEvent& event) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));

        const char* keys[] = { "xOffset", "yOffset" };
        Local<JSValueRef> values[] = { panda::NumberRef::New(vm, event.GetX()),
            panda::NumberRef::New(vm, event.GetY()) };
        auto eventObject = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(keys), keys, values);
        eventObject->SetNativePointerFieldCount(vm, 1);
        eventObject->SetNativePointerField(vm, 0, static_cast<void*>(&event));
        panda::Local<panda::JSValueRef> params[1] = { eventObject };
        func->Call(vm, func.ToLocal(), params, 1);
    };
    GetArkUINodeModifiers()->getWebModifier()->setOnScrollCallBack(nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WebBridge::ResetOnScroll(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getWebModifier()->resetOnScrollCallBack(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WebBridge::SetOnOverScroll(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(1);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        GetArkUINodeModifiers()->getWebModifier()->resetOnOverScrollCallBack(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);

    std::function<void(WebOnOverScrollEvent&)> callback = [vm, frameNode, func = panda::CopyableGlobal(vm, func)](
                                                              WebOnOverScrollEvent& event) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));

        const char* keys[] = { "xOffset", "yOffset" };
        Local<JSValueRef> values[] = { panda::NumberRef::New(vm, event.GetX()),
            panda::NumberRef::New(vm, event.GetY()) };
        auto eventObject = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(keys), keys, values);
        eventObject->SetNativePointerFieldCount(vm, 1);
        eventObject->SetNativePointerField(vm, 0, static_cast<void*>(&event));
        panda::Local<panda::JSValueRef> params[1] = { eventObject };
        func->Call(vm, func.ToLocal(), params, 1);
    };
    GetArkUINodeModifiers()->getWebModifier()->setOnOverScrollCallBack(nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WebBridge::ResetOnOverScroll(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getWebModifier()->resetOnOverScrollCallBack(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WebBridge::SetOnRequestSelected(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(1);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        GetArkUINodeModifiers()->getWebModifier()->resetOnRequestSelectedCallBack(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);

    std::function<void()> callback = [vm, frameNode, func = panda::CopyableGlobal(vm, func)]() {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
        func->Call(vm, func.ToLocal(), nullptr, 0);
    };
    GetArkUINodeModifiers()->getWebModifier()->setOnRequestSelectedCallBack(
        nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WebBridge::RetsetOnRequestSelected(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getWebModifier()->resetOnRequestSelectedCallBack(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WebBridge::SetOnScaleChange(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(1);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        GetArkUINodeModifiers()->getWebModifier()->resetOnScaleChangeCallBack(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);

    std::function<void(ScaleChangeEvent&)> callback = [vm, frameNode, func = panda::CopyableGlobal(vm, func)](
                                                          ScaleChangeEvent& event) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
        const char* keys[] = { "oldScale", "newScale" };
        Local<JSValueRef> values[] = { panda::NumberRef::New(vm, event.GetOnScaleChangeOldScale()),
            panda::NumberRef::New(vm, event.GetOnScaleChangeNewScale()) };
        auto eventObject = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(keys), keys, values);
        eventObject->SetNativePointerFieldCount(vm, 1);
        eventObject->SetNativePointerField(vm, 0, static_cast<void*>(&event));
        panda::Local<panda::JSValueRef> params[1] = { eventObject };
        func->Call(vm, func.ToLocal(), params, 1);
    };
    GetArkUINodeModifiers()->getWebModifier()->setOnScaleChangeCallBack(nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WebBridge::ResetOnScaleChange(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getWebModifier()->resetOnScaleChangeCallBack(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WebBridge::SetOnContextMenuHide(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(1);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        GetArkUINodeModifiers()->getWebModifier()->resetOnContextMenuHideCallBack(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);

    std::function<void()> callback = [vm, frameNode, func = panda::CopyableGlobal(vm, func)]() {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
        func->Call(vm, func.ToLocal(), nullptr, 0);
    };
    GetArkUINodeModifiers()->getWebModifier()->setOnContextMenuHideCallBack(
        nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WebBridge::ResetOnContextMenuHide(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getWebModifier()->resetOnContextMenuHideCallBack(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue WebBridge::SetGeolocationAccess(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (secondArg->IsBoolean()) {
        bool enable = secondArg->ToBoolean(vm)->Value();
        GetArkUINodeModifiers()->getWebModifier()->setGeolocationAccess(nativeNode, enable);
    } else {
        GetArkUINodeModifiers()->getWebModifier()->resetGeolocationAccess(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WebBridge::ResetGeolocationAccess(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getWebModifier()->resetGeolocationAccess(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WebBridge::SetDatabaseAccess(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (secondArg->IsBoolean()) {
        bool enable = secondArg->ToBoolean(vm)->Value();
        GetArkUINodeModifiers()->getWebModifier()->setDatabaseAccess(nativeNode, enable);
    } else {
        GetArkUINodeModifiers()->getWebModifier()->resetDatabaseAccess(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WebBridge::ResetDatabaseAccess(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getWebModifier()->resetDatabaseAccess(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WebBridge::SetOverviewModeAccess(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (secondArg->IsBoolean()) {
        bool enable = secondArg->ToBoolean(vm)->Value();
        GetArkUINodeModifiers()->getWebModifier()->setOverviewModeAccess(nativeNode, enable);
    } else {
        GetArkUINodeModifiers()->getWebModifier()->resetOverviewModeAccess(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WebBridge::ResetOverviewModeAccess(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getWebModifier()->resetOverviewModeAccess(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WebBridge::SetForceDarkAccess(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (secondArg->IsBoolean()) {
        bool enable = secondArg->ToBoolean(vm)->Value();
        GetArkUINodeModifiers()->getWebModifier()->setForceDarkAccess(nativeNode, enable);
    } else {
        GetArkUINodeModifiers()->getWebModifier()->resetForceDarkAccess(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WebBridge::ResetForceDarkAccess(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getWebModifier()->resetForceDarkAccess(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WebBridge::SetPinchSmooth(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (secondArg->IsBoolean()) {
        bool enable = secondArg->ToBoolean(vm)->Value();
        GetArkUINodeModifiers()->getWebModifier()->setPinchSmooth(nativeNode, enable);
    } else {
        GetArkUINodeModifiers()->getWebModifier()->resetPinchSmooth(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WebBridge::ResetPinchSmooth(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getWebModifier()->resetPinchSmooth(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WebBridge::SetMetaViewport(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (secondArg->IsBoolean()) {
        bool enable = secondArg->ToBoolean(vm)->Value();
        GetArkUINodeModifiers()->getWebModifier()->setMetaViewport(nativeNode, enable);
    } else {
        GetArkUINodeModifiers()->getWebModifier()->resetMetaViewport(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WebBridge::ResetMetaViewport(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getWebModifier()->resetMetaViewport(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WebBridge::SetEnableFollowSystemFontWeight(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (secondArg->IsBoolean()) {
        bool enable = secondArg->ToBoolean(vm)->Value();
        GetArkUINodeModifiers()->getWebModifier()->setEnableFollowSystemFontWeight(nativeNode, enable);
    } else {
        GetArkUINodeModifiers()->getWebModifier()->resetEnableFollowSystemFontWeight(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WebBridge::ResetEnableFollowSystemFontWeight(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getWebModifier()->resetEnableFollowSystemFontWeight(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WebBridge::SetEnableNativeEmbedMode(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (secondArg->IsBoolean()) {
        bool enable = secondArg->ToBoolean(vm)->Value();
        GetArkUINodeModifiers()->getWebModifier()->setEnableNativeEmbedMode(nativeNode, enable);
    } else {
        GetArkUINodeModifiers()->getWebModifier()->resetEnableNativeEmbedMode(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WebBridge::ResetEnableNativeEmbedMode(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getWebModifier()->resetEnableNativeEmbedMode(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WebBridge::SetMinFontSize(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (secondArg->IsNumber()) {
        int mode = secondArg->Int32Value(vm);
        GetArkUINodeModifiers()->getWebModifier()->setMinFontSize(nativeNode, mode);
    } else {
        GetArkUINodeModifiers()->getWebModifier()->resetMinFontSize(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WebBridge::ResetMinFontSize(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getWebModifier()->resetMinFontSize(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WebBridge::SetDefaultFontSize(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (secondArg->IsNumber()) {
        int mode = secondArg->Int32Value(vm);
        GetArkUINodeModifiers()->getWebModifier()->setDefaultFontSize(nativeNode, mode);
    } else {
        GetArkUINodeModifiers()->getWebModifier()->resetDefaultFontSize(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WebBridge::ResetDefaultFontSize(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getWebModifier()->resetDefaultFontSize(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WebBridge::SetDefaultFixedFontSize(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (secondArg->IsNumber()) {
        int mode = secondArg->Int32Value(vm);
        GetArkUINodeModifiers()->getWebModifier()->setDefaultFixedFontSize(nativeNode, mode);
    } else {
        GetArkUINodeModifiers()->getWebModifier()->resetDefaultFixedFontSize(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WebBridge::ResetDefaultFixedFontSize(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getWebModifier()->resetDefaultFixedFontSize(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WebBridge::SetMinLogicalFontSize(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (secondArg->IsNumber()) {
        int mode = secondArg->Int32Value(vm);
        GetArkUINodeModifiers()->getWebModifier()->setMinLogicalFontSize(nativeNode, mode);
    } else {
        GetArkUINodeModifiers()->getWebModifier()->resetMinLogicalFontSize(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WebBridge::ResetMinLogicalFontSize(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getWebModifier()->resetMinLogicalFontSize(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WebBridge::SetWebStandardFont(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (secondArg->IsString(vm)) {
        auto mode = secondArg->ToString(vm)->ToString(vm);
        GetArkUINodeModifiers()->getWebModifier()->setWebStandardFont(nativeNode, mode.c_str());
    } else {
        GetArkUINodeModifiers()->getWebModifier()->resetWebStandardFont(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WebBridge::ResetWebStandardFont(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getWebModifier()->resetWebStandardFont(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WebBridge::SetWebSerifFont(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (secondArg->IsString(vm)) {
        auto mode = secondArg->ToString(vm)->ToString(vm);
        GetArkUINodeModifiers()->getWebModifier()->setWebSerifFont(nativeNode, mode.c_str());
    } else {
        GetArkUINodeModifiers()->getWebModifier()->resetWebSerifFont(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WebBridge::ResetWebSerifFont(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getWebModifier()->resetWebSerifFont(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WebBridge::SetWebSansSerifFont(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (secondArg->IsString(vm)) {
        auto mode = secondArg->ToString(vm)->ToString(vm);
        GetArkUINodeModifiers()->getWebModifier()->setWebSansSerifFont(nativeNode, mode.c_str());
    } else {
        GetArkUINodeModifiers()->getWebModifier()->resetWebSansSerifFont(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WebBridge::ResetWebSansSerifFont(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getWebModifier()->resetWebSansSerifFont(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WebBridge::SetWebFixedFont(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto mode = secondArg->ToString(vm)->ToString(vm);
    GetArkUINodeModifiers()->getWebModifier()->setWebFixedFont(nativeNode, mode.c_str());
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WebBridge::ResetWebFixedFont(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getWebModifier()->resetWebFixedFont(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WebBridge::SetWebFantasyFont(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (secondArg->IsString(vm)) {
        auto mode = secondArg->ToString(vm)->ToString(vm);
        GetArkUINodeModifiers()->getWebModifier()->setWebFantasyFont(nativeNode, mode.c_str());
    } else {
        GetArkUINodeModifiers()->getWebModifier()->resetWebFantasyFont(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WebBridge::ResetWebFantasyFont(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getWebModifier()->resetWebFantasyFont(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WebBridge::SetWebCursiveFont(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto mode = secondArg->ToString(vm)->ToString(vm);
    GetArkUINodeModifiers()->getWebModifier()->setWebCursiveFont(nativeNode, mode.c_str());
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WebBridge::ResetWebCursiveFont(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getWebModifier()->resetWebCursiveFont(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WebBridge::SetLayoutMode(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    int mode = secondArg->Int32Value(vm);
    GetArkUINodeModifiers()->getWebModifier()->setLayoutMode(nativeNode, mode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WebBridge::ResetLayoutMode(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getWebModifier()->resetLayoutMode(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WebBridge::SetOnNativeEmbedLifecycleChange(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto obj = secondArg->ToObject(vm);
    panda::Local<panda::FunctionRef> func = obj;
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::NativePointerRef::Undefined(vm));
    std::function<void(NativeEmbedDataInfo&)> callback = [vm, frameNode, func = panda::CopyableGlobal(vm, func)](
                                                             NativeEmbedDataInfo& event) -> void {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
        const char* keyPosition[] = { "x", "y" };
        Local<JSValueRef> valuesPosition[] = { panda::NumberRef::New(vm, static_cast<int32_t>(event.GetEmebdInfo().x)),
            panda::NumberRef::New(vm, static_cast<int32_t>(event.GetEmebdInfo().y)) };
        auto positionObject =
            panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(keyPosition), keyPosition, valuesPosition);
        const char* keysInfo[] = { "id", "type", "src", "tag", "width", "height", "url", "position", "params" };
        auto paramsObject = panda::ObjectRef::New(vm);
        for (const auto& item : event.GetEmebdInfo().params) {
            paramsObject->Set(vm, panda::StringRef::NewFromUtf8(vm, item.first.c_str()),
                panda::StringRef::NewFromUtf8(vm, item.second.c_str()));
        }
        Local<JSValueRef> valuesInfo[] = { panda::StringRef::NewFromUtf8(vm, event.GetEmebdInfo().id.c_str()),
            panda::StringRef::NewFromUtf8(vm, event.GetEmebdInfo().type.c_str()),
            panda::StringRef::NewFromUtf8(vm, event.GetEmebdInfo().src.c_str()),
            panda::StringRef::NewFromUtf8(vm, event.GetEmebdInfo().tag.c_str()),
            panda::NumberRef::New(vm, static_cast<int32_t>(event.GetEmebdInfo().width)),
            panda::NumberRef::New(vm, static_cast<int32_t>(event.GetEmebdInfo().height)),
            panda::StringRef::NewFromUtf8(vm, event.GetEmebdInfo().url.c_str()), positionObject, paramsObject };
        auto resultObj = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(keysInfo), keysInfo, valuesInfo);
        const char* keysEvent[] = { "status", "surfaceId", "embedId", "info" };
        Local<JSValueRef> valuesEvent[] = { panda::NumberRef::New(vm, static_cast<int32_t>(event.GetStatus())),
            panda::StringRef::NewFromUtf8(vm, event.GetSurfaceId().c_str()),
            panda::StringRef::NewFromUtf8(vm, event.GetEmbedId().c_str()), resultObj };
        auto eventObject = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(keysEvent), keysEvent, valuesEvent);
        eventObject->SetNativePointerFieldCount(vm, CALL_ARG_1);
        eventObject->SetNativePointerField(vm, CALL_ARG_0, static_cast<void*>(&event));
        panda::Local<panda::JSValueRef> params[CALL_ARG_1] = { eventObject };
        func->Call(vm, func.ToLocal(), params, CALL_ARG_1);
    };
    GetArkUINodeModifiers()->getWebModifier()->setOnNativeEmbedLifecycleChange(
        nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WebBridge::ResetOnNativeEmbedLifecycleChange(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getWebModifier()->resetOnNativeEmbedLifecycleChange(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WebBridge::SetRegisterNativeEmbedRule(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    Local<JSValueRef> tagArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    Local<JSValueRef> typeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_2);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    std::string tag;
    std::string type;
    if (tagArg->IsString(vm) && typeArg->IsString(vm)) {
        tag = tagArg->ToString(vm)->ToString(vm);
        type = typeArg->ToString(vm)->ToString(vm);
    }
    GetArkUINodeModifiers()->getWebModifier()->setRegisterNativeEmbedRule(nativeNode, tag.c_str(), type.c_str());
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WebBridge::ResetRegisterNativeEmbedRule(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getWebModifier()->resetRegisterNativeEmbedRule(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WebBridge::SetNativeEmbedOptions(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (secondArg->IsBoolean()) {
        bool enable = secondArg->ToBoolean(vm)->Value();
        GetArkUINodeModifiers()->getWebModifier()->setNativeEmbedOptions(nativeNode, enable);
    } else {
        GetArkUINodeModifiers()->getWebModifier()->resetNativeEmbedOptions(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WebBridge::ResetNativeEmbedOptions(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getWebModifier()->resetNativeEmbedOptions(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WebBridge::SetOnFirstContentfulPaint(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        GetArkUINodeModifiers()->getWebModifier()->resetOnFirstContentfulPaint(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::NativePointerRef::Undefined(vm));
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<void(FirstContentfulPaintEvent&)> callback = [vm, frameNode, func = panda::CopyableGlobal(vm, func)](
                                                                   FirstContentfulPaintEvent& event) -> void {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
        const char* keys[] = { "navigationStartTick", "firstContentfulPaintMs" };
        Local<JSValueRef> values[] = { panda::NumberRef::New(vm, static_cast<int64_t>(event.GetNavigationStartTick())),
            panda::NumberRef::New(vm, static_cast<int64_t>(event.GetFirstContentfulPaintMs())) };
        auto eventObject = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(keys), keys, values);
        eventObject->SetNativePointerFieldCount(vm, CALL_ARG_1);
        eventObject->SetNativePointerField(vm, CALL_ARG_0, static_cast<void*>(&event));
        panda::Local<panda::JSValueRef> params[1] = { eventObject };
        func->Call(vm, func.ToLocal(), params, CALL_ARG_1);
    };
    GetArkUINodeModifiers()->getWebModifier()->setOnFirstContentfulPaint(
        nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WebBridge::ResetOnFirstContentfulPaint(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getWebModifier()->resetOnFirstContentfulPaint(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WebBridge::SetOnAudioStateChanged(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    auto nativeNode = nodePtr(nativeNodeArg->ToNativePointer(vm)->Value());
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::NativePointerRef::New(vm, nullptr));
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        GetArkUINodeModifiers()->getWebModifier()->resetOnAudioStateChanged(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<void(AudioStateChangedEvent&)> callback = [vm, frameNode, func = panda::CopyableGlobal(vm, func)](
                                                                AudioStateChangedEvent& event) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
        const char* keys[] = { "playing" };
        Local<JSValueRef> values[] = {
            panda::BooleanRef::New(vm, event.IsPlaying()),
        };
        auto eventObject = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(keys), keys, values);
        eventObject->SetNativePointerFieldCount(vm, CALL_ARG_1);
        eventObject->SetNativePointerField(vm, CALL_ARG_0, static_cast<void*>(&event));
        panda::Local<panda::JSValueRef> params[1] = { eventObject };
        func->Call(vm, func.ToLocal(), params, CALL_ARG_1);
    };
    GetArkUINodeModifiers()->getWebModifier()->setOnAudioStateChanged(nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WebBridge::ResetOnAudioStateChanged(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getWebModifier()->resetOnAudioStateChanged(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WebBridge::SetOnFullScreenExit(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    auto nativeNode = nodePtr(nativeNodeArg->ToNativePointer(vm)->Value());
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        GetArkUINodeModifiers()->getWebModifier()->resetOnFullScreenExit(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::NativePointerRef::New(vm, nullptr));
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<void()> callback = [vm, frameNode, func = panda::CopyableGlobal(vm, func)]() {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
        func->Call(vm, func.ToLocal(), nullptr, CALL_ARG_0);
    };
    GetArkUINodeModifiers()->getWebModifier()->setOnFullScreenExit(nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WebBridge::ResetOnFullScreenExit(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getWebModifier()->resetOnFullScreenExit(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WebBridge::SetImageAccess(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (secondArg->IsBoolean()) {
        bool enable = secondArg->ToBoolean(vm)->Value();
        GetArkUINodeModifiers()->getWebModifier()->setImageAccess(nativeNode, enable);
    } else {
        GetArkUINodeModifiers()->getWebModifier()->resetImageAccess(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WebBridge::ResetImageAccess(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getWebModifier()->resetImageAccess(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WebBridge::SetOnlineImageAccess(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (secondArg->IsBoolean()) {
        bool enable = secondArg->ToBoolean(vm)->Value();
        GetArkUINodeModifiers()->getWebModifier()->setOnlineImageAccess(nativeNode, enable);
    } else {
        GetArkUINodeModifiers()->getWebModifier()->resetOnlineImageAccess(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WebBridge::ResetOnlineImageAccess(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getWebModifier()->resetOnlineImageAccess(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WebBridge::SetMediaPlayGestureAccess(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (secondArg->IsBoolean()) {
        bool enable = secondArg->ToBoolean(vm)->Value();
        GetArkUINodeModifiers()->getWebModifier()->setMediaPlayGestureAccess(nativeNode, enable);
    } else {
        GetArkUINodeModifiers()->getWebModifier()->resetMediaPlayGestureAccess(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WebBridge::ResetMediaPlayGestureAccess(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getWebModifier()->resetMediaPlayGestureAccess(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WebBridge::SetMediaOptions(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    Local<JSValueRef> thirdArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_2);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (!secondArg->IsNumber()) {
        return panda::JSValueRef::Undefined(vm);
    }
    if (!thirdArg->IsBoolean()) {
        return panda::JSValueRef::Undefined(vm);
    }
    int mode = secondArg->Int32Value(vm);
    bool enable = thirdArg->ToBoolean(vm)->Value();
    GetArkUINodeModifiers()->getWebModifier()->setMediaOptions(nativeNode, mode, enable);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WebBridge::ResetMediaOptions(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getWebModifier()->resetMediaOptions(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
} // namespace OHOS::Ace::NG