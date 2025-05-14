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
} // namespace OHOS::Ace::NG