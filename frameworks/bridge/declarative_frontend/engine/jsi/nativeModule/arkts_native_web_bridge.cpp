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
constexpr int32_t CALL_ARG_3 = 3;
constexpr int32_t CALL_ARG_4 = 4;
constexpr char END_CHAR = '\0';

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
    if (secondArg->IsString(vm)) {
        auto mode = secondArg->ToString(vm)->ToString(vm);
        GetArkUINodeModifiers()->getWebModifier()->setWebFixedFont(nativeNode, mode.c_str());
    } else {
        GetArkUINodeModifiers()->getWebModifier()->resetWebFixedFont(nativeNode);
    }
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

Local<panda::ObjectRef> WebBridge::CreateEventTargetObject(EcmaVM* vm, const BaseEventInfo& info)
{
    const auto& localOffset = info.GetTarget().area.GetOffset();
    const auto& origin = info.GetTarget().origin;
    const char* keysOfOffset[] = { "x", "y" };
    Local<JSValueRef> valuesOfOffset[] = { panda::NumberRef::New(vm, localOffset.GetX().ConvertToVp()),
        panda::NumberRef::New(vm, localOffset.GetY().ConvertToVp()) };
    auto offset = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(keysOfOffset), keysOfOffset, valuesOfOffset);

    const char* keysOfGlobalOffset[] = { "x", "y" };
    Local<JSValueRef> valuesOfGlobalOffset[] = { panda::NumberRef::New(
        vm, (origin.GetX() + localOffset.GetX()).ConvertToVp()),
        panda::NumberRef::New(vm, (origin.GetY() + localOffset.GetY()).ConvertToVp()) };
    auto globalOffset = panda::ObjectRef::NewWithNamedProperties(
        vm, ArraySize(keysOfGlobalOffset), keysOfGlobalOffset, valuesOfGlobalOffset);
    const char* keysOfArea[] = { "position", "globalPosition", "width", "height" };
    Local<JSValueRef> valuesOfArea[] = { offset, globalOffset,
        panda::NumberRef::New(vm, info.GetTarget().area.GetWidth().ConvertToVp()),
        panda::NumberRef::New(vm, info.GetTarget().area.GetHeight().ConvertToVp()) };
    auto area = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(keysOfArea), keysOfArea, valuesOfArea);
    auto target = panda::ObjectRef::New(vm);
    target->Set(vm, panda::StringRef::NewFromUtf8(vm, "area"), area);
    if (info.GetTarget().id.empty()) {
        target->Set(vm, panda::StringRef::NewFromUtf8(vm, "id"), panda::JSValueRef().Undefined(vm));
    } else {
        target->Set(vm, panda::StringRef::NewFromUtf8(vm, "id"),
            panda::StringRef::NewFromUtf8(vm, info.GetTarget().id.c_str()));
    }
    return target;
}

Local<panda::ObjectRef> WebBridge::CreateTouchEventInfoObj(EcmaVM* vm, TouchEventInfo& info)
{
    const char* keys[] = { "source", "timestamp", "target", "pressure", "sourceTool", "targetDisplayId", "deviceId" };
    Local<JSValueRef> values[] = { panda::NumberRef::New(vm, static_cast<int32_t>(info.GetSourceDevice())),
        panda::NumberRef::New(vm, static_cast<double>(info.GetTimeStamp().time_since_epoch().count())),
        CreateEventTargetObject(vm, info), panda::NumberRef::New(vm, info.GetForce()),
        panda::NumberRef::New(vm, static_cast<int32_t>(info.GetSourceTool())),
        panda::NumberRef::New(vm, static_cast<int32_t>(info.GetTargetDisplayId())),
        panda::NumberRef::New(vm, info.GetDeviceId()) };

    return panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(keys), keys, values);
}

Local<panda::ObjectRef> WebBridge::CreateTouchInfo(EcmaVM* vm, const TouchLocationInfo& touchInfo, TouchEventInfo& info)
{
    const Offset& globalOffset = touchInfo.GetGlobalLocation();
    const Offset& localOffset = touchInfo.GetLocalLocation();
    const Offset& screenOffset = touchInfo.GetScreenLocation();
    const char* keys[] = { "type", "id", "displayX", "displayY", "windowX", "windowY", "screenX", "screenY", "x", "y" };
    Local<JSValueRef> values[] = { panda::NumberRef::New(vm, static_cast<int32_t>(touchInfo.GetTouchType())),
        panda::NumberRef::New(vm, touchInfo.GetFingerId()), panda::NumberRef::New(vm, screenOffset.GetX()),
        panda::NumberRef::New(vm, screenOffset.GetY()), panda::NumberRef::New(vm, globalOffset.GetX()),
        panda::NumberRef::New(vm, globalOffset.GetY()), panda::NumberRef::New(vm, globalOffset.GetX()),
        panda::NumberRef::New(vm, globalOffset.GetY()), panda::NumberRef::New(vm, localOffset.GetX()),
        panda::NumberRef::New(vm, localOffset.GetY()) };
    auto touchInfoObj = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(keys), keys, values);
    touchInfoObj->SetNativePointerFieldCount(vm, 1);
    touchInfoObj->SetNativePointerField(vm, 0, static_cast<void*>(&info));
    return touchInfoObj;
}

Local<panda::ObjectRef> WebBridge::CreateTouchEventInfo(EcmaVM* vm, TouchEventInfo& info)
{
    auto eventObj = CreateTouchEventInfoObj(vm, info);
    eventObj->SetNativePointerFieldCount(vm, 1);
    auto touchArr = panda::ArrayRef::New(vm);
    const std::list<TouchLocationInfo>& touchList = info.GetTouches();
    uint32_t idx = 0;
    for (const TouchLocationInfo& location : touchList) {
        panda::ArrayRef::SetValueAt(vm, touchArr, idx++, CreateTouchInfo(vm, location, info));
    }
    eventObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "touches"), touchArr);
    auto changeTouchArr = panda::ArrayRef::New(vm);
    idx = 0;
    const std::list<TouchLocationInfo>& changeTouch = info.GetChangedTouches();
    for (const TouchLocationInfo& change : changeTouch) {
        panda::ArrayRef::SetValueAt(vm, changeTouchArr, idx++, CreateTouchInfo(vm, change, info));
    }
    if (changeTouch.size() > 0) {
        eventObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "type"),
            panda::NumberRef::New(vm, static_cast<int32_t>(changeTouch.front().GetTouchType())));
    }
    eventObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "changedTouches"), changeTouchArr);

    eventObj->SetNativePointerField(vm, 0, static_cast<void*>(&info));
    return eventObj;
}

ArkUINativeModuleValue WebBridge::SetOnNativeEmbedGestureEvent(ArkUIRuntimeCallInfo* runtimeCallInfo)
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
    CHECK_NULL_RETURN(frameNode, panda::NativePointerRef::New(vm, nullptr));
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);

    std::function<void(NativeEmbeadTouchInfo&)> callback = [vm, frameNode, func = panda::CopyableGlobal(vm, func)](
                                                               NativeEmbeadTouchInfo& event) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
        auto info = event.GetTouchEventInfo();
        auto touchEventObject = CreateTouchEventInfo(vm, info);

        const char* keysFinal[] = { "embedId", "touchEvent", "result" };
        Framework::JSRef<Framework::JSObject> handlerObj = Framework::JSWeb::CreateNativeEmbedGestureHandler(event);
        Local<JSValueRef> valuesFinal[] = { panda::StringRef::NewFromUtf8(vm, event.GetEmbedId().c_str()),
            touchEventObject, handlerObj->GetLocalHandle() };

        auto eventObject = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(keysFinal), keysFinal, valuesFinal);
        eventObject->SetNativePointerFieldCount(vm, CALL_ARG_1);
        eventObject->SetNativePointerField(vm, CALL_ARG_0, static_cast<void*>(&event));
        panda::Local<panda::JSValueRef> params[1] = { eventObject };
        func->Call(vm, func.ToLocal(), params, CALL_ARG_1);
    };
    GetArkUINodeModifiers()->getWebModifier()->setOnNativeEmbedGestureEvent(
        nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WebBridge::ResetOnNativeEmbedGestureEvent(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getWebModifier()->resetOnNativeEmbedGestureEvent(nativeNode);
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
    if (!tagArg->IsNull() && !tagArg->IsUndefined() && tagArg->IsString(vm)) {
        tag = tagArg->ToString(vm)->ToString(vm);
    }
    if (!typeArg->IsNull() && !typeArg->IsUndefined() && typeArg->IsString(vm)) {
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
    bool enable = secondArg->ToBoolean(vm)->Value();
    GetArkUINodeModifiers()->getWebModifier()->setNativeEmbedOptions(nativeNode, enable);
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

ArkUINativeModuleValue WebBridge::SetOnPageEnd(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    CHECK_NULL_RETURN(nativeNodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nativeNodeArg->ToNativePointer(vm)->Value());
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::NativePointerRef::New(vm, nullptr));
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        GetArkUINodeModifiers()->getWebModifier()->resetOnPageEnd(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<void(LoadWebPageFinishEvent&)> callback = [vm, frameNode, func = panda::CopyableGlobal(vm, func)](
                                                                            LoadWebPageFinishEvent& event) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
        const char* keys[] = { "url" };
        Local<JSValueRef> values[] = {
            panda::StringRef::NewFromUtf8(vm, event.GetLoadedUrl().c_str()),
        };
        auto eventObject = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(keys), keys, values);
        eventObject->SetNativePointerFieldCount(vm, CALL_ARG_1);
        eventObject->SetNativePointerField(vm, CALL_ARG_0, static_cast<void*>(&event));
        panda::Local<panda::JSValueRef> params[1] = { eventObject };
        func->Call(vm, func.ToLocal(), params, CALL_ARG_1);
    };
    GetArkUINodeModifiers()->getWebModifier()->setOnPageEnd(nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WebBridge::ResetOnPageEnd(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getWebModifier()->resetOnPageEnd(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WebBridge::SetOnPageBegin(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    CHECK_NULL_RETURN(nativeNodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nativeNodeArg->ToNativePointer(vm)->Value());
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::NativePointerRef::New(vm, nullptr));
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        GetArkUINodeModifiers()->getWebModifier()->resetOnPageBegin(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<void(LoadWebPageStartEvent&)> callback = [vm, frameNode, func = panda::CopyableGlobal(vm, func)](
                                                                            LoadWebPageStartEvent& event) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
        const char* keys[] = { "url" };
        Local<JSValueRef> values[] = {
            panda::StringRef::NewFromUtf8(vm, event.GetLoadedUrl().c_str()),
        };
        auto eventObject = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(keys), keys, values);
        eventObject->SetNativePointerFieldCount(vm, CALL_ARG_1);
        eventObject->SetNativePointerField(vm, CALL_ARG_0, static_cast<void*>(&event));
        panda::Local<panda::JSValueRef> params[1] = { eventObject };
        func->Call(vm, func.ToLocal(), params, CALL_ARG_1);
    };
    GetArkUINodeModifiers()->getWebModifier()->setOnPageBegin(nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WebBridge::ResetOnPageBegin(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getWebModifier()->resetOnPageBegin(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WebBridge::SetOnProgressChange(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    CHECK_NULL_RETURN(nativeNodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nativeNodeArg->ToNativePointer(vm)->Value());
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::NativePointerRef::New(vm, nullptr));
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        GetArkUINodeModifiers()->getWebModifier()->resetOnProgressChange(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<void(LoadWebProgressChangeEvent&)> callback = [vm, frameNode, func = panda::CopyableGlobal(vm, func)](
                                                                            LoadWebProgressChangeEvent& event) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
        const char* keys[] = { "newProgress" };
        Local<JSValueRef> values[] = {
            panda::NumberRef::New(vm, event.GetNewProgress()),
        };
        auto eventObject = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(keys), keys, values);
        eventObject->SetNativePointerFieldCount(vm, CALL_ARG_1);
        eventObject->SetNativePointerField(vm, CALL_ARG_0, static_cast<void*>(&event));
        panda::Local<panda::JSValueRef> params[1] = { eventObject };
        func->Call(vm, func.ToLocal(), params, CALL_ARG_1);
    };
    GetArkUINodeModifiers()->getWebModifier()->setOnProgressChange(nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WebBridge::ResetOnProgressChange(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getWebModifier()->resetOnProgressChange(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WebBridge::SetOnTitleReceive(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    CHECK_NULL_RETURN(nativeNodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nativeNodeArg->ToNativePointer(vm)->Value());
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::NativePointerRef::New(vm, nullptr));
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        GetArkUINodeModifiers()->getWebModifier()->resetOnTitleReceive(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<void(LoadWebTitleReceiveEvent&)> callback = [vm, frameNode, func = panda::CopyableGlobal(vm, func)](
                                                                            LoadWebTitleReceiveEvent& event) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
        const char* keys[] = { "title" };
        Local<JSValueRef> values[] = {
            panda::StringRef::NewFromUtf8(vm, event.GetTitle().c_str()),
        };
        auto eventObject = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(keys), keys, values);
        eventObject->SetNativePointerFieldCount(vm, CALL_ARG_1);
        eventObject->SetNativePointerField(vm, CALL_ARG_0, static_cast<void*>(&event));
        panda::Local<panda::JSValueRef> params[1] = { eventObject };
        func->Call(vm, func.ToLocal(), params, CALL_ARG_1);
    };
    GetArkUINodeModifiers()->getWebModifier()->setOnTitleReceive(nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WebBridge::ResetOnTitleReceive(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getWebModifier()->resetOnTitleReceive(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WebBridge::SetOnDownloadStart(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    CHECK_NULL_RETURN(nativeNodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nativeNodeArg->ToNativePointer(vm)->Value());
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::NativePointerRef::New(vm, nullptr));
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        GetArkUINodeModifiers()->getWebModifier()->resetOnTitleReceive(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<void(DownloadStartEvent&)> callback = [vm, frameNode, func = panda::CopyableGlobal(vm, func)](
                                                                            DownloadStartEvent& event) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
        const char* keys[] = { "url", "userAgent", "contentDisposition", "mimetype", "contentLength" };
        Local<JSValueRef> values[] = {
            panda::StringRef::NewFromUtf8(vm, event.GetUrl().c_str()),
            panda::StringRef::NewFromUtf8(vm, event.GetUserAgent().c_str()),
            panda::StringRef::NewFromUtf8(vm, event.GetContentDisposition().c_str()),
            panda::StringRef::NewFromUtf8(vm, event.GetMimetype().c_str()),
            panda::NumberRef::New(vm, static_cast<double>(event.GetContentLength())),
        };
        auto eventObject = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(keys), keys, values);
        eventObject->SetNativePointerFieldCount(vm, CALL_ARG_1);
        eventObject->SetNativePointerField(vm, CALL_ARG_0, static_cast<void*>(&event));
        panda::Local<panda::JSValueRef> params[1] = { eventObject };
        func->Call(vm, func.ToLocal(), params, CALL_ARG_1);
    };
    GetArkUINodeModifiers()->getWebModifier()->setOnDownloadStart(nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WebBridge::ResetOnDownloadStart(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getWebModifier()->resetOnDownloadStart(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUI_CharPtr ParseStringToCharPtr(std::string str)
{
    char* script = static_cast<char*>(malloc((str.length() + 1) * sizeof(char)));
    CHECK_NULL_RETURN(script, nullptr);
    str.copy(script, str.length());
    script[str.length()] = END_CHAR;
    return script;
}

void ParseReferencedId(EcmaVM* vm, int32_t scriptRuleSize,
    const panda::Local<panda::ArrayRef>& array, std::vector<ArkUI_CharPtr>& scriptRules)
{
    for (int32_t i = 0; i < scriptRuleSize; i++) {
        Local<JSValueRef> scriptRule = panda::ArrayRef::GetValueAt(vm, array, i);
        if (scriptRule->IsString(vm)) {
            std::string str = scriptRule->ToString(vm)->ToString(vm);
            scriptRules.push_back(ParseStringToCharPtr(str));
        }
    }
}

void FreeScriptItemCharPtr(ArkUI_ScriptItemArray* values, ArkUI_Int32 size)
{
    for (int32_t i = 0; i < size; ++i) {
        free(const_cast<char*>(values[i].script));
        values[i].script = nullptr;
        auto referencedIdChar = values[i].scriptRules;
        auto referencedIdSize = values[i].scriptRulesSize;
        for (int32_t j = 0; j < referencedIdSize; ++j) {
            free(const_cast<char*>(referencedIdChar[j]));
            referencedIdChar[j] = nullptr;
        }
    }
}

ArkUINativeModuleValue WebBridge::SetJavaScriptOnDocumentStart(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    Local<JSValueRef> scriptsArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    Local<JSValueRef> scriptRulesArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_2);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (!scriptsArg->IsArray(vm) || !scriptRulesArg->IsArray(vm)) {
        GetArkUINodeModifiers()->getWebModifier()->resetJavaScriptOnDocumentStart(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    std::vector<ArkUI_ScriptItemArray> scrpitinfos;
    auto scriptsArr = panda::Local<panda::ArrayRef>(scriptsArg);
    auto scriptRulesArr = panda::Local<panda::ArrayRef>(scriptRulesArg);
    int32_t size = static_cast<int32_t>(scriptsArr->Length(vm));
    std::vector<ArkUI_CharPtr> scriptRules;
    for (int32_t i = 0; i < size; i++) {
        ArkUI_ScriptItemArray info;
        Local<JSValueRef> scriptVal = panda::ArrayRef::GetValueAt(vm, scriptsArr, i);
        Local<JSValueRef> scriptRulesVal = panda::ArrayRef::GetValueAt(vm, scriptRulesArr, i);
        if (scriptVal->IsString(vm)) {
            std::string str = scriptVal->ToString(vm)->ToString(vm);
            info.script = ParseStringToCharPtr(str);
        }
        if (scriptRulesVal->IsArray(vm)) {
            auto array = panda::Local<panda::ArrayRef>(scriptRulesVal);
            uint32_t scriptRuleSize = array->Length(vm);
            ParseReferencedId(vm, static_cast<int32_t>(scriptRuleSize), array, scriptRules);
            info.scriptRules = scriptRules.data();
            info.scriptRulesSize = static_cast<int32_t>(scriptRules.size());
            scriptRules.clear();
        } else {
            info.scriptRulesSize = 0;
        }
        scrpitinfos.push_back(info);
    }
    ArkUI_ScriptItemArray* values = scrpitinfos.data();
    GetArkUINodeModifiers()->getWebModifier()->setJavaScriptOnDocumentStart(nativeNode, values, size);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WebBridge::ResetJavaScriptOnDocumentStart(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getWebModifier()->resetJavaScriptOnDocumentStart(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WebBridge::SetJavaScriptOnDocumentEnd(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    Local<JSValueRef> scriptsArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    Local<JSValueRef> scriptRulesArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_2);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (!scriptsArg->IsArray(vm) || !scriptRulesArg->IsArray(vm)) {
        GetArkUINodeModifiers()->getWebModifier()->resetJavaScriptOnDocumentEnd(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    std::vector<ArkUI_ScriptItemArray> scrpitinfos;
    auto scriptsArr = panda::Local<panda::ArrayRef>(scriptsArg);
    auto scriptRulesArr = panda::Local<panda::ArrayRef>(scriptRulesArg);
    int32_t size = static_cast<int32_t>(scriptsArr->Length(vm));
    std::vector<ArkUI_CharPtr> scriptRules;
    for (int32_t i = 0; i < size; i++) {
        ArkUI_ScriptItemArray info;
        Local<JSValueRef> scriptVal = panda::ArrayRef::GetValueAt(vm, scriptsArr, i);
        Local<JSValueRef> scriptRulesVal = panda::ArrayRef::GetValueAt(vm, scriptRulesArr, i);
        if (scriptVal->IsString(vm)) {
            std::string str = scriptVal->ToString(vm)->ToString(vm);
            info.script = ParseStringToCharPtr(str);
        }
        if (scriptRulesVal->IsArray(vm)) {
            auto array = panda::Local<panda::ArrayRef>(scriptRulesVal);
            uint32_t scriptRuleSize = array->Length(vm);
            ParseReferencedId(vm, static_cast<int32_t>(scriptRuleSize), array, scriptRules);
            info.scriptRules = scriptRules.data();
            info.scriptRulesSize = static_cast<int32_t>(scriptRules.size());
            scriptRules.clear();
        } else {
            info.scriptRulesSize = 0;
        }
        scrpitinfos.push_back(info);
    }
    ArkUI_ScriptItemArray* values = scrpitinfos.data();
    GetArkUINodeModifiers()->getWebModifier()->setJavaScriptOnDocumentEnd(nativeNode, values, size);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WebBridge::ResetJavaScriptOnDocumentEnd(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getWebModifier()->resetJavaScriptOnDocumentEnd(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WebBridge::SetCopyOptionMode(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto copyOptions = CopyOptions::Local;
    uint32_t value = static_cast<uint32_t>(copyOptions);
    if (secondArg->IsNumber()) {
        value = secondArg->Uint32Value(vm);
    } else if (!secondArg->IsNumber() && !secondArg->IsUndefined()) {
        copyOptions = CopyOptions::Local;
        value = static_cast<uint32_t>(copyOptions);
    }
    GetArkUINodeModifiers()->getWebModifier()->setCopyOptionMode(nativeNode, value);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WebBridge::ResetCopyOptionMode(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getWebModifier()->resetCopyOptionMode(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WebBridge::SetOnRenderProcessNotResponding(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    auto nativeNode = nodePtr(nativeNodeArg->ToNativePointer(vm)->Value());
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::NativePointerRef::New(vm, nullptr));
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        GetArkUINodeModifiers()->getWebModifier()->resetRenderProcessNotResponding(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<void(RenderProcessNotRespondingEvent&)> callback = [vm, frameNode, func = panda::CopyableGlobal(vm, func)](
                                                                            RenderProcessNotRespondingEvent& event) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
        const char* keys[] = { "jsStack", "pid", "reason"};
        Local<JSValueRef> values[] = {
            panda::StringRef::NewFromUtf8(vm, event.GetJsStack().c_str()),
            panda::NumberRef::New(vm, event.GetPid()),
            panda::NumberRef::New(vm, event.GetReason()),
        };
        auto eventObject = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(keys), keys, values);
        eventObject->SetNativePointerFieldCount(vm, CALL_ARG_1);
        eventObject->SetNativePointerField(vm, CALL_ARG_0, static_cast<void*>(&event));
        panda::Local<panda::JSValueRef> params[1] = { eventObject };
        func->Call(vm, func.ToLocal(), params, CALL_ARG_1);
    };
    GetArkUINodeModifiers()->getWebModifier()->setRenderProcessNotResponding(nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WebBridge::ResetOnRenderProcessNotResponding(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getWebModifier()->resetRenderProcessNotResponding(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WebBridge::SetOnPageVisible(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(1);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        GetArkUINodeModifiers()->getWebModifier()->resetOnPageVisibleCallBack(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);

    std::function<void(PageVisibleEvent&)> callback = [vm, frameNode, func = panda::CopyableGlobal(vm, func)](
                                                          PageVisibleEvent& event) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
        auto eventObject = panda::ObjectRef::New(vm);
        eventObject->Set(
            vm, panda::StringRef::NewFromUtf8(vm, "url"), panda::StringRef::NewFromUtf8(vm, event.GetUrl().c_str()));
        panda::Local<panda::JSValueRef> params[1] = { eventObject };
        func->Call(vm, func.ToLocal(), params, 1);
    };
    GetArkUINodeModifiers()->getWebModifier()->setOnPageVisibleCallBack(nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WebBridge::ResetOnPageVisible(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getWebModifier()->resetOnPageVisibleCallBack(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WebBridge::SetOnRenderExited(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(1);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        GetArkUINodeModifiers()->getWebModifier()->resetOnRenderExitedCallBack(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);

    std::function<void(RenderExitedEvent&)> callback = [vm, frameNode, func = panda::CopyableGlobal(vm, func)](
                                                           RenderExitedEvent& event) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
        const char* keys[] = { "renderExitReason" };
        Local<JSValueRef> values[] = { panda::NumberRef::New(vm, event.GetExitedReason()) };
        auto eventObject = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(keys), keys, values);
        eventObject->SetNativePointerFieldCount(vm, 1);
        eventObject->SetNativePointerField(vm, 0, static_cast<void*>(&event));
        panda::Local<panda::JSValueRef> params[1] = { eventObject };
        func->Call(vm, func.ToLocal(), params, 1);
    };
    GetArkUINodeModifiers()->getWebModifier()->setOnRenderExitedCallBack(
        nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WebBridge::ResetOnRenderExited(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getWebModifier()->resetOnRenderExitedCallBack(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WebBridge::SetBlockNetwork(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (secondArg->IsBoolean()) {
        bool enable = secondArg->ToBoolean(vm)->Value();
        GetArkUINodeModifiers()->getWebModifier()->setBlockNetwork(nativeNode, enable);
    } else {
        GetArkUINodeModifiers()->getWebModifier()->resetBlockNetwork(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WebBridge::ResetBlockNetwork(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getWebModifier()->resetBlockNetwork(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WebBridge::SetOnResourceLoad(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(1);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        GetArkUINodeModifiers()->getWebModifier()->resetOnResourceLoadCallBack(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);

    std::function<void(ResourceLoadEvent&)> callback = [vm, frameNode, func = panda::CopyableGlobal(vm, func)](
                                                           ResourceLoadEvent& event) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
        auto eventObject = panda::ObjectRef::New(vm);
        eventObject->Set(vm, panda::StringRef::NewFromUtf8(vm, "url"),
            panda::StringRef::NewFromUtf8(vm, event.GetOnResourceLoadUrl().c_str()));
        panda::Local<panda::JSValueRef> params[1] = { eventObject };
        func->Call(vm, func.ToLocal(), params, 1);
    };
    GetArkUINodeModifiers()->getWebModifier()->setOnResourceLoadCallBack(
        nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WebBridge::ResetOnResourceLoad(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getWebModifier()->resetOnResourceLoadCallBack(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WebBridge::SetOnRefreshAccessedHistory(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(1);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        GetArkUINodeModifiers()->getWebModifier()->resetOnRefreshAccessedHistoryCallBack(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);

    std::function<void(RefreshAccessedHistoryEvent&)> callback =
        [vm, frameNode, func = panda::CopyableGlobal(vm, func)](RefreshAccessedHistoryEvent& event) {
            panda::LocalScope pandaScope(vm);
            panda::TryCatch trycatch(vm);
            PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
            const char* keys[] = { "url", "isRefreshed" };
            Local<JSValueRef> values[] = { panda::StringRef::NewFromUtf8(vm, event.GetVisitedUrl().c_str()),
                panda::BooleanRef::New(vm, event.IsRefreshed()) };
            auto eventObject = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(keys), keys, values);
            eventObject->SetNativePointerFieldCount(vm, 1);
            eventObject->SetNativePointerField(vm, 0, static_cast<void*>(&event));
            panda::Local<panda::JSValueRef> params[1] = { eventObject };
            func->Call(vm, func.ToLocal(), params, 1);
        };
    GetArkUINodeModifiers()->getWebModifier()->setOnRefreshAccessedHistoryCallBack(
        nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WebBridge::ResetOnRefreshAccessedHistory(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getWebModifier()->resetOnRefreshAccessedHistoryCallBack(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WebBridge::SetOnNavigationEntryCommitted(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(1);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        GetArkUINodeModifiers()->getWebModifier()->resetOnNavigationEntryCommittedCallBack(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);

    std::function<void(NavigationEntryCommittedEvent&)> callback =
        [vm, frameNode, func = panda::CopyableGlobal(vm, func)](NavigationEntryCommittedEvent& event) {
            panda::LocalScope pandaScope(vm);
            panda::TryCatch trycatch(vm);
            PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
            const char* keys[] = { "isMainFrame", "isSameDocument", "didReplaceEntry", "navigationType", "url" };
            Local<JSValueRef> values[] = { panda::BooleanRef::New(vm, event.IsMainFrame()),
                panda::BooleanRef::New(vm, event.IsSameDocument()), panda::BooleanRef::New(vm, event.DidReplaceEntry()),
                panda::NumberRef::New(vm, static_cast<int>(event.GetNavigationType())),
                panda::StringRef::NewFromUtf8(vm, event.GetUrl().c_str()) };
            auto eventObject = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(keys), keys, values);
            eventObject->SetNativePointerFieldCount(vm, 1);
            eventObject->SetNativePointerField(vm, 0, static_cast<void*>(&event));
            panda::Local<panda::JSValueRef> params[1] = { eventObject };
            func->Call(vm, func.ToLocal(), params, 1);
        };
    GetArkUINodeModifiers()->getWebModifier()->setOnNavigationEntryCommittedCallBack(
        nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WebBridge::ResetOnNavigationEntryCommitted(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getWebModifier()->resetOnNavigationEntryCommittedCallBack(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WebBridge::SetOnSearchResultReceive(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(1);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        GetArkUINodeModifiers()->getWebModifier()->resetOnSearchResultReceiveCallBack(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);

    std::function<void(SearchResultReceiveEvent&)> callback = [vm, frameNode, func = panda::CopyableGlobal(vm, func)](
                                                                  SearchResultReceiveEvent& event) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
        const char* keys[] = { "activeMatchOrdinal", "numberOfMatches", "isDoneCounting" };
        Local<JSValueRef> values[] = { panda::NumberRef::New(vm, event.GetActiveMatchOrdinal()),
            panda::NumberRef::New(vm, event.GetNumberOfMatches()),
            panda::BooleanRef::New(vm, event.GetIsDoneCounting()) };
        auto eventObject = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(keys), keys, values);
        panda::Local<panda::JSValueRef> params[1] = { eventObject };
        func->Call(vm, func.ToLocal(), params, 1);
    };
    GetArkUINodeModifiers()->getWebModifier()->setOnSearchResultReceiveCallBack(
        nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WebBridge::ResetOnSearchResultReceive(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getWebModifier()->resetOnSearchResultReceiveCallBack(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WebBridge::SetOverScrollMode(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    int mode = secondArg->Int32Value(vm);
    GetArkUINodeModifiers()->getWebModifier()->setOverScrollMode(nativeNode, mode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WebBridge::ResetOverScrollMode(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getWebModifier()->resetOverScrollMode(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WebBridge::SetOnTouchIconUrlReceived(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(1);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        GetArkUINodeModifiers()->getWebModifier()->resetOnTouchIconUrlReceivedCallBack(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);

    std::function<void(TouchIconUrlEvent&)> callback = [vm, frameNode, func = panda::CopyableGlobal(vm, func)](
                                                           TouchIconUrlEvent& event) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
        const char* keys[] = { "url", "precomposed" };
        Local<JSValueRef> values[] = { panda::StringRef::NewFromUtf8(vm, event.GetUrl().c_str()),
            panda::BooleanRef::New(vm, event.GetPreComposed()) };
        auto eventObject = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(keys), keys, values);
        eventObject->SetNativePointerFieldCount(vm, 1);
        eventObject->SetNativePointerField(vm, 0, static_cast<void*>(&event));
        panda::Local<panda::JSValueRef> params[1] = { eventObject };
        func->Call(vm, func.ToLocal(), params, 1);
    };
    GetArkUINodeModifiers()->getWebModifier()->setOnTouchIconUrlReceivedCallBack(
        nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WebBridge::ResetOnTouchIconUrlReceived(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getWebModifier()->resetOnTouchIconUrlReceivedCallBack(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WebBridge::SetOnRenderProcessResponding(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(1);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        GetArkUINodeModifiers()->getWebModifier()->resetOnRenderProcessRespondingCallBack(nativeNode);
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
    GetArkUINodeModifiers()->getWebModifier()->setOnRenderProcessRespondingCallBack(
        nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WebBridge::ResetOnRenderProcessResponding(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getWebModifier()->resetOnRenderProcessRespondingCallBack(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WebBridge::SetOnWindowNew(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    auto nativeNode = nodePtr(nativeNodeArg->ToNativePointer(vm)->Value());
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        GetArkUINodeModifiers()->getWebModifier()->resetOnWindowNew(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::NativePointerRef::New(vm, nullptr));
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<void(WebWindowNewEvent&)> callback = [vm, frameNode, func = panda::CopyableGlobal(vm, func)](
                                                           WebWindowNewEvent& event) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
        const char* keys[] = { "isAlert", "isUserTrigger", "targeturl", "handler" };
        Framework::JSRef<Framework::JSObject> handlerObj = Framework::JSWeb::CreateJSWindowNewHandler(event);
        Local<JSValueRef> values[] = { panda::BooleanRef::New(vm, event.IsAlert()),
                                       panda::BooleanRef::New(vm, event.IsUserTrigger()),
                                       panda::StringRef::NewFromUtf8(vm, event.GetTargetUrl().c_str()),
                                       handlerObj->GetLocalHandle() };
        auto eventObject = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(keys), keys, values);
        eventObject->SetNativePointerFieldCount(vm, CALL_ARG_1);
        eventObject->SetNativePointerField(vm, CALL_ARG_0, static_cast<void*>(&event));
        panda::Local<panda::JSValueRef> params[1] = { eventObject };
        func->Call(vm, func.ToLocal(), params, CALL_ARG_1);
    };
    GetArkUINodeModifiers()->getWebModifier()->setOnWindowNew(nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WebBridge::ResetOnWindowNew(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getWebModifier()->resetOnWindowNew(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WebBridge::SetOnGeolocationShow(ArkUIRuntimeCallInfo* runtimeCallInfo)
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
    CHECK_NULL_RETURN(frameNode, panda::NativePointerRef::New(vm, nullptr));
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);

    std::function<void(LoadWebGeolocationShowEvent&)> callback =
        [vm, frameNode, func = panda::CopyableGlobal(vm, func)](LoadWebGeolocationShowEvent& event) {
            panda::LocalScope pandaScope(vm);
            panda::TryCatch trycatch(vm);
            PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
            const char* keys[] = { "origin", "geolocation" };

            Framework::JSRef<Framework::JSObject> handlerObj = Framework::JSWeb::CreateGeolocationShowHandler(event);
            Local<JSValueRef> values[] = { panda::StringRef::NewFromUtf8(vm, event.GetOrigin().c_str()),
                handlerObj->GetLocalHandle() };
            auto eventObject = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(keys), keys, values);
            eventObject->SetNativePointerFieldCount(vm, CALL_ARG_1);
            eventObject->SetNativePointerField(vm, CALL_ARG_0, static_cast<void*>(&event));
            panda::Local<panda::JSValueRef> params[1] = { eventObject };
            func->Call(vm, func.ToLocal(), params, CALL_ARG_1);
        };
    GetArkUINodeModifiers()->getWebModifier()->setOnGeolocationShow(nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WebBridge::ResetOnGeolocationShow(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getWebModifier()->resetOnGeolocationShow(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WebBridge::SetOnPermissionRequest(ArkUIRuntimeCallInfo* runtimeCallInfo)
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
    CHECK_NULL_RETURN(frameNode, panda::NativePointerRef::New(vm, nullptr));
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);

    std::function<void(WebPermissionRequestEvent&)> callback = [vm, frameNode, func = panda::CopyableGlobal(vm, func)](
                                                                   WebPermissionRequestEvent& event) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
        const char* keys[] = { "request" };

        Framework::JSRef<Framework::JSObject> handlerObj = Framework::JSWeb::CreatePermissionRequestHandler(event);
        Local<JSValueRef> values[] = { handlerObj->GetLocalHandle() };
        auto eventObject = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(keys), keys, values);
        eventObject->SetNativePointerFieldCount(vm, CALL_ARG_1);
        eventObject->SetNativePointerField(vm, CALL_ARG_0, static_cast<void*>(&event));
        panda::Local<panda::JSValueRef> params[1] = { eventObject };
        func->Call(vm, func.ToLocal(), params, CALL_ARG_1);
    };
    GetArkUINodeModifiers()->getWebModifier()->setOnPermissionRequest(nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WebBridge::ResetOnPermissionRequest(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getWebModifier()->resetOnPermissionRequest(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WebBridge::SetOnScreenCaptureRequest(ArkUIRuntimeCallInfo* runtimeCallInfo)
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
    CHECK_NULL_RETURN(frameNode, panda::NativePointerRef::New(vm, nullptr));
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);

    std::function<void(WebScreenCaptureRequestEvent&)> callback =
        [vm, frameNode, func = panda::CopyableGlobal(vm, func)](WebScreenCaptureRequestEvent& event) {
            panda::LocalScope pandaScope(vm);
            panda::TryCatch trycatch(vm);
            PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
            const char* keys[] = { "handler" };

            Framework::JSRef<Framework::JSObject> handlerObj = Framework::JSWeb::CreateScreenCaptureHandler(event);
            Local<JSValueRef> values[] = { handlerObj->GetLocalHandle() };
            auto eventObject = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(keys), keys, values);
            eventObject->SetNativePointerFieldCount(vm, CALL_ARG_1);
            eventObject->SetNativePointerField(vm, CALL_ARG_0, static_cast<void*>(&event));
            panda::Local<panda::JSValueRef> params[1] = { eventObject };
            func->Call(vm, func.ToLocal(), params, CALL_ARG_1);
        };
    GetArkUINodeModifiers()->getWebModifier()->setOnScreenCaptureRequest(
        nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WebBridge::ResetOnScreenCaptureRequest(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getWebModifier()->resetOnScreenCaptureRequest(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WebBridge::SetOnFullScreenEnter(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    auto nativeNode = nodePtr(nativeNodeArg->ToNativePointer(vm)->Value());
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        GetArkUINodeModifiers()->getWebModifier()->resetOnFullScreenEnter(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::NativePointerRef::New(vm, nullptr));
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<void(FullScreenEnterEvent&)> callback = [vm, frameNode, func = panda::CopyableGlobal(vm, func)](
                                                              FullScreenEnterEvent& event) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
        const char* keys[] = { "videoWidth", "videoHeight", "handler" };
        Framework::JSRef<Framework::JSObject> handlerObj = Framework::JSWeb::CreateFullScreenEnterHandler(event);
        Local<JSValueRef> values[] = { panda::NumberRef::New(vm, static_cast<int64_t>(event.GetVideoNaturalWidth())),
            panda::NumberRef::New(vm, static_cast<int64_t>(event.GetVideoNaturalHeight())),
            handlerObj->GetLocalHandle() };

        auto eventObject = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(keys), keys, values);
        eventObject->SetNativePointerFieldCount(vm, CALL_ARG_1);
        eventObject->SetNativePointerField(vm, CALL_ARG_0, static_cast<void*>(&event));
        panda::Local<panda::JSValueRef> params[1] = { eventObject };
        func->Call(vm, func.ToLocal(), params, CALL_ARG_1);
    };
    GetArkUINodeModifiers()->getWebModifier()->setOnFullScreenEnter(nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WebBridge::ResetOnFullScreenEnter(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getWebModifier()->resetOnFullScreenEnter(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WebBridge::SetOnWindowExit(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    auto nativeNode = nodePtr(nativeNodeArg->ToNativePointer(vm)->Value());
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        GetArkUINodeModifiers()->getWebModifier()->resetOnWindowExit(nativeNode);
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
    GetArkUINodeModifiers()->getWebModifier()->setOnWindowExit(nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WebBridge::ResetOnWindowExit(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getWebModifier()->resetOnWindowExit(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WebBridge::SetOnAlert(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(1);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        GetArkUINodeModifiers()->getWebModifier()->resetOnAlertlCallBack(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);

    std::function<bool(WebDialogEvent&)> callback = [vm, frameNode, func = panda::CopyableGlobal(vm, func)](
                                                        WebDialogEvent& event) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
        const char* keys[] = { "url", "message", "result" };
        Framework::JSRef<Framework::JSObject> handlerObj = Framework::JSWeb::CreateCommonDialogResultHandler(event);
        Local<JSValueRef> values[] = { panda::StringRef::NewFromUtf8(vm, event.GetUrl().c_str()),
            panda::StringRef::NewFromUtf8(vm, event.GetMessage().c_str()), handlerObj->GetLocalHandle() };
        auto eventObject = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(keys), keys, values);
        eventObject->SetNativePointerFieldCount(vm, 1);
        eventObject->SetNativePointerField(vm, 0, static_cast<void*>(&event));
        panda::Local<panda::JSValueRef> params[1] = { eventObject };
        auto ret = func->Call(vm, func.ToLocal(), params, 1);
        if (ret->IsBoolean()) {
            return ret->ToBoolean(vm)->Value();
        }
        return false;
    };

    GetArkUINodeModifiers()->getWebModifier()->setOnAlertlCallBack(nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WebBridge::ResetOnAlert(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getWebModifier()->resetOnAlertlCallBack(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WebBridge::SetOnConfirm(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(1);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        GetArkUINodeModifiers()->getWebModifier()->resetOnConfirmCallBack(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);

    std::function<bool(WebDialogEvent&)> callback = [vm, frameNode, func = panda::CopyableGlobal(vm, func)](
                                                        WebDialogEvent& event) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
        const char* keys[] = { "url", "message", "result" };
        Framework::JSRef<Framework::JSObject> handlerObj = Framework::JSWeb::CreateCommonDialogResultHandler(event);
        Local<JSValueRef> values[] = { panda::StringRef::NewFromUtf8(vm, event.GetUrl().c_str()),
            panda::StringRef::NewFromUtf8(vm, event.GetMessage().c_str()), handlerObj->GetLocalHandle() };
        auto eventObject = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(keys), keys, values);
        eventObject->SetNativePointerFieldCount(vm, 1);
        eventObject->SetNativePointerField(vm, 0, static_cast<void*>(&event));
        panda::Local<panda::JSValueRef> params[1] = { eventObject };
        auto ret = func->Call(vm, func.ToLocal(), params, 1);
        if (ret->IsBoolean()) {
            return ret->ToBoolean(vm)->Value();
        }
        return false;
    };

    GetArkUINodeModifiers()->getWebModifier()->setOnConfirmCallBack(nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WebBridge::ResetOnConfirm(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getWebModifier()->resetOnConfirmCallBack(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WebBridge::SetOnPrompt(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(1);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        GetArkUINodeModifiers()->getWebModifier()->resetOnPromptCallBack(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<bool(WebDialogEvent&)> callback = [vm, frameNode, func = panda::CopyableGlobal(vm, func)](
                                                        WebDialogEvent& event) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
        const char* keys[] = { "url", "message", "value", "result" };
        Framework::JSRef<Framework::JSObject> handlerObj = Framework::JSWeb::CreateCommonDialogResultHandler(event);
        Local<JSValueRef> values[] = { panda::StringRef::NewFromUtf8(vm, event.GetUrl().c_str()),
            panda::StringRef::NewFromUtf8(vm, event.GetMessage().c_str()),
            panda::StringRef::NewFromUtf8(vm, event.GetValue().c_str()), handlerObj->GetLocalHandle() };
        auto eventObject = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(keys), keys, values);
        eventObject->SetNativePointerFieldCount(vm, 1);
        eventObject->SetNativePointerField(vm, 0, static_cast<void*>(&event));
        panda::Local<panda::JSValueRef> params[1] = { eventObject };
        auto ret = func->Call(vm, func.ToLocal(), params, 1);
        if (ret->IsBoolean()) {
            return ret->ToBoolean(vm)->Value();
        }
        return false;
    };
    GetArkUINodeModifiers()->getWebModifier()->setOnPromptCallBack(nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WebBridge::ResetOnPrompt(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getWebModifier()->resetOnPromptCallBack(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WebBridge::SetOnShowFileSelector(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    CHECK_NULL_RETURN(nativeNodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nativeNodeArg->ToNativePointer(vm)->Value());
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        GetArkUINodeModifiers()->getWebModifier()->resetOnShowFileSelector(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::NativePointerRef::New(vm, nullptr));
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<bool(FileSelectorEvent&)> callback = [vm, frameNode, func = panda::CopyableGlobal(vm, func)](
                                                           FileSelectorEvent& event) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
        const char* keys[] = { "fileSelector", "result" };
        Framework::JSRef<Framework::JSObject> handlerParamObj = Framework::JSWeb::CreateFileSelectorParamHandler(event);
        Framework::JSRef<Framework::JSObject> handlerresultObj =
            Framework::JSWeb::CreateFileSelectorResultHandler(event);
        Local<JSValueRef> values[] = { handlerParamObj->GetLocalHandle(), handlerresultObj->GetLocalHandle() };

        auto eventObject = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(keys), keys, values);
        eventObject->SetNativePointerFieldCount(vm, CALL_ARG_1);
        eventObject->SetNativePointerField(vm, CALL_ARG_0, static_cast<void*>(&event));
        panda::Local<panda::JSValueRef> params[1] = { eventObject };
        auto ret = func->Call(vm, func.ToLocal(), params, CALL_ARG_1);
        return ret->IsBoolean() && ret->ToBoolean(vm)->Value();
    };
    GetArkUINodeModifiers()->getWebModifier()->setOnShowFileSelector(nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WebBridge::ResetOnShowFileSelector(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getWebModifier()->resetOnShowFileSelector(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WebBridge::SetOnContextMenuShow(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    CHECK_NULL_RETURN(nativeNodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nativeNodeArg->ToNativePointer(vm)->Value());
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        GetArkUINodeModifiers()->getWebModifier()->resetOnContextMenuShow(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::NativePointerRef::New(vm, nullptr));
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<bool(ContextMenuEvent&)> callback = [vm, frameNode, func = panda::CopyableGlobal(vm, func)](
                                                          ContextMenuEvent& event) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
        const char* keys[] = { "param", "result" };
        Framework::JSRef<Framework::JSObject> handlerParamObj = Framework::JSWeb::CreateContextMenuParamHandler(event);
        Framework::JSRef<Framework::JSObject> handlerResultObj =
            Framework::JSWeb::CreateContextMenuResultHandler(event);
        Local<JSValueRef> values[] = { handlerParamObj->GetLocalHandle(), handlerResultObj->GetLocalHandle() };
        auto eventObject = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(keys), keys, values);
        eventObject->SetNativePointerFieldCount(vm, CALL_ARG_1);
        eventObject->SetNativePointerField(vm, CALL_ARG_0, static_cast<void*>(&event));
        panda::Local<panda::JSValueRef> params[1] = { eventObject };
        auto ret = func->Call(vm, func.ToLocal(), params, CALL_ARG_1);
        return ret->IsBoolean() && ret->ToBoolean(vm)->Value();
    };
    GetArkUINodeModifiers()->getWebModifier()->setOnContextMenuShow(nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WebBridge::ResetOnContextMenuShow(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getWebModifier()->resetOnContextMenuShow(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WebBridge::SetOnSafeBrowsingCheckResult(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(1);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        GetArkUINodeModifiers()->getWebModifier()->resetOnSafeBrowsingCheckResultCallBack(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);

    std::function<void(SafeBrowsingCheckResultEvent&)> callback =
        [vm, frameNode, func = panda::CopyableGlobal(vm, func)](SafeBrowsingCheckResultEvent& event) {
            panda::LocalScope pandaScope(vm);
            panda::TryCatch trycatch(vm);
            PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
            auto eventObject = panda::ObjectRef::New(vm);
            eventObject->Set(
                vm, panda::StringRef::NewFromUtf8(vm, "threatType"), panda::NumberRef::New(vm, event.GetThreatType()));
            panda::Local<panda::JSValueRef> params[1] = { eventObject };
            func->Call(vm, func.ToLocal(), params, 1);
        };
    GetArkUINodeModifiers()->getWebModifier()->setOnSafeBrowsingCheckResultCallBack(
        nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WebBridge::ResetOnSafeBrowsingCheckResult(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getWebModifier()->resetOnSafeBrowsingCheckResultCallBack(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WebBridge::SetNestedScroll(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    Local<JSValueRef> scrollUpValue = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    Local<JSValueRef> scrollDownValue = runtimeCallInfo->GetCallArgRef(CALL_ARG_2);
    Local<JSValueRef> scrollLeftValue = runtimeCallInfo->GetCallArgRef(CALL_ARG_3);
    Local<JSValueRef> scrollRightValue = runtimeCallInfo->GetCallArgRef(CALL_ARG_4);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    int32_t up = static_cast<int32_t>(NestedScrollMode::SELF_ONLY);
    int32_t down = static_cast<int32_t>(NestedScrollMode::SELF_ONLY);
    int32_t left = static_cast<int32_t>(NestedScrollMode::SELF_ONLY);
    int32_t right = static_cast<int32_t>(NestedScrollMode::SELF_ONLY);
    ArkTSUtils::ParseJsInteger(vm, scrollUpValue, up);
    if (up < static_cast<int32_t>(NestedScrollMode::SELF_ONLY) ||
        up > static_cast<int32_t>(NestedScrollMode::PARALLEL)) {
        up = static_cast<int32_t>(NestedScrollMode::SELF_FIRST);
    }
    ArkTSUtils::ParseJsInteger(vm, scrollDownValue, down);
    if (down < static_cast<int32_t>(NestedScrollMode::SELF_ONLY) ||
        down > static_cast<int32_t>(NestedScrollMode::PARALLEL)) {
        down = static_cast<int32_t>(NestedScrollMode::SELF_FIRST);
    }
    ArkTSUtils::ParseJsInteger(vm, scrollLeftValue, left);
    if (left < static_cast<int32_t>(NestedScrollMode::SELF_ONLY) ||
        left > static_cast<int32_t>(NestedScrollMode::PARALLEL)) {
        left = static_cast<int32_t>(NestedScrollMode::SELF_FIRST);
    }
    ArkTSUtils::ParseJsInteger(vm, scrollRightValue, right);
    if (right < static_cast<int32_t>(NestedScrollMode::SELF_ONLY) ||
        right > static_cast<int32_t>(NestedScrollMode::PARALLEL)) {
        right = static_cast<int32_t>(NestedScrollMode::SELF_FIRST);
    }
    GetArkUINodeModifiers()->getWebModifier()->setWebNestedScrollExt(nativeNode, up, down, left, right);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WebBridge::ResetNestedScroll(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getWebModifier()->resetWebNestedScrollExt(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WebBridge::SetOnInterceptKeyEvent(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(1);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        GetArkUINodeModifiers()->getWebModifier()->resetOnInterceptKeyEventCallBack(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);

    std::function<bool(KeyEventInfo&)> onKeyEvent = [vm, frameNode, func = panda::CopyableGlobal(vm, func)](
                                                        KeyEventInfo& info) -> bool {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
        const char* keys[] = { "type", "keyCode", "keyText", "keySource", "deviceId", "metaKey", "unicode", "timestamp",
            "stopPropagation", "getModifierKeyState", "intentionCode", "isNumLockOn", "isCapsLockOn",
            "isScrollLockOn" };
        Local<JSValueRef> values[] = { panda::NumberRef::New(vm, static_cast<int32_t>(info.GetKeyType())),
            panda::NumberRef::New(vm, static_cast<int32_t>(info.GetKeyCode())),
            panda::StringRef::NewFromUtf8(vm, info.GetKeyText()),
            panda::NumberRef::New(vm, static_cast<int32_t>(info.GetKeySource())),
            panda::NumberRef::New(vm, info.GetDeviceId()), panda::NumberRef::New(vm, info.GetMetaKey()),
            panda::NumberRef::New(vm, info.GetUnicode()),
            panda::NumberRef::New(vm, static_cast<double>(info.GetTimeStamp().time_since_epoch().count())),
            panda::FunctionRef::New(vm, Framework::JsStopPropagation),
            panda::FunctionRef::New(vm, ArkTSUtils::JsGetModifierKeyState),
            panda::NumberRef::New(vm, static_cast<int32_t>(info.GetKeyIntention())),
            panda::BooleanRef::New(vm, info.GetNumLock()), panda::BooleanRef::New(vm, info.GetCapsLock()),
            panda::BooleanRef::New(vm, info.GetScrollLock()) };
        auto obj = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(keys), keys, values);
        obj->SetNativePointerFieldCount(vm, 1);
        obj->SetNativePointerField(vm, 0, static_cast<void*>(&info));
        panda::Local<panda::JSValueRef> params[1] = { obj };
        auto ret = func->Call(vm, func.ToLocal(), params, 1);
        if (ret->IsBoolean()) {
            return ret->ToBoolean(vm)->Value();
        }
        return false;
    };
    GetArkUINodeModifiers()->getWebModifier()->setOnInterceptKeyEventCallBack(
        nativeNode, reinterpret_cast<void*>(&onKeyEvent));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WebBridge::ResetOnInterceptKeyEvent(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getWebModifier()->resetOnInterceptKeyEventCallBack(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WebBridge::SetOnErrorReceive(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    CHECK_NULL_RETURN(nativeNodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nativeNodeArg->ToNativePointer(vm)->Value());
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        GetArkUINodeModifiers()->getWebModifier()->resetOnErrorReceive(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::NativePointerRef::New(vm, nullptr));
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<void(ReceivedErrorEvent&)> callback = [vm, frameNode, func = panda::CopyableGlobal(vm, func)](
                                                            ReceivedErrorEvent& event) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
        const char* keys[] = { "request", "error" };
        Framework::JSRef<Framework::JSObject> handlerRequestObj =
            Framework::JSWeb::CreateErrorReceiveRequestHandler(event);
        Framework::JSRef<Framework::JSObject> handlerErrorObj = Framework::JSWeb::CreateErrorReceiveErrorHandler(event);
        Local<JSValueRef> values[] = { handlerRequestObj->GetLocalHandle(), handlerErrorObj->GetLocalHandle() };

        auto eventObject = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(keys), keys, values);
        eventObject->SetNativePointerFieldCount(vm, CALL_ARG_1);
        eventObject->SetNativePointerField(vm, CALL_ARG_0, static_cast<void*>(&event));
        panda::Local<panda::JSValueRef> params[1] = { eventObject };
        func->Call(vm, func.ToLocal(), params, CALL_ARG_1);
    };
    GetArkUINodeModifiers()->getWebModifier()->setOnErrorReceive(nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WebBridge::ResetOnErrorReceive(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getWebModifier()->resetOnErrorReceive(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WebBridge::SetOnLoadIntercept(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    CHECK_NULL_RETURN(nativeNodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nativeNodeArg->ToNativePointer(vm)->Value());
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        GetArkUINodeModifiers()->getWebModifier()->resetOnLoadIntercept(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::NativePointerRef::New(vm, nullptr));
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<bool(LoadInterceptEvent&)> callback = [vm, frameNode, func = panda::CopyableGlobal(vm, func)](
                                                            LoadInterceptEvent& event) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
        const char* keys[] = { "data" };
        Framework::JSRef<Framework::JSObject> handlerObj = Framework::JSWeb::CreateLoadInterceptHandler(event);
        Local<JSValueRef> values[] = { handlerObj->GetLocalHandle() };

        auto eventObject = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(keys), keys, values);
        eventObject->SetNativePointerFieldCount(vm, CALL_ARG_1);
        eventObject->SetNativePointerField(vm, CALL_ARG_0, static_cast<void*>(&event));
        panda::Local<panda::JSValueRef> params[1] = { eventObject };
        auto ret = func->Call(vm, func.ToLocal(), params, CALL_ARG_1);
        return ret->IsBoolean() && ret->ToBoolean(vm)->Value();
    };
    GetArkUINodeModifiers()->getWebModifier()->setOnLoadIntercept(nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WebBridge::ResetOnLoadIntercept(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getWebModifier()->resetOnLoadIntercept(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WebBridge::SetOnHttpErrorReceive(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    CHECK_NULL_RETURN(nativeNodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nativeNodeArg->ToNativePointer(vm)->Value());
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        GetArkUINodeModifiers()->getWebModifier()->resetOnHttpErrorReceive(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::NativePointerRef::New(vm, nullptr));
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<void(ReceivedHttpErrorEvent&)> callback = [vm, frameNode, func = panda::CopyableGlobal(vm, func)](
                                                                ReceivedHttpErrorEvent& event) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
        const char* keys[] = { "request", "response" };
        Framework::JSRef<Framework::JSObject> handlerRequestObj =
            Framework::JSWeb::CreateHttpErrorReceiveRequestHandler(event);
        Framework::JSRef<Framework::JSObject> handlerResponseObj =
            Framework::JSWeb::CreateHttpErrorReceiveResponseHandler(event);
        Local<JSValueRef> values[] = { handlerRequestObj->GetLocalHandle(), handlerResponseObj->GetLocalHandle() };

        auto eventObject = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(keys), keys, values);
        eventObject->SetNativePointerFieldCount(vm, CALL_ARG_1);
        eventObject->SetNativePointerField(vm, CALL_ARG_0, static_cast<void*>(&event));
        panda::Local<panda::JSValueRef> params[1] = { eventObject };
        func->Call(vm, func.ToLocal(), params, CALL_ARG_1);
    };
    GetArkUINodeModifiers()->getWebModifier()->setOnHttpErrorReceive(nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WebBridge::ResetOnHttpErrorReceive(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getWebModifier()->resetOnHttpErrorReceive(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WebBridge::SetOnOverrideUrlLoading(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    CHECK_NULL_RETURN(nativeNodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nativeNodeArg->ToNativePointer(vm)->Value());
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        GetArkUINodeModifiers()->getWebModifier()->resetOnOverrideUrlLoading(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::NativePointerRef::New(vm, nullptr));
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<bool(LoadOverrideEvent&)> callback = [vm, frameNode, func = panda::CopyableGlobal(vm, func)](
                                                           LoadOverrideEvent& event) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
        Framework::JSRef<Framework::JSObject> handlerObj = Framework::JSWeb::CreateOverrideUrlLoadingHandler(event);
        panda::Local<panda::JSValueRef> params[1] = { handlerObj->GetLocalHandle() };
        auto ret = func->Call(vm, func.ToLocal(), params, CALL_ARG_1);
        return ret->IsBoolean() && ret->ToBoolean(vm)->Value();
    };
    GetArkUINodeModifiers()->getWebModifier()->setOnOverrideUrlLoading(nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WebBridge::ResetOnOverrideUrlLoading(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getWebModifier()->resetOnOverrideUrlLoading(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WebBridge::SetOnHttpAuthRequest(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    CHECK_NULL_RETURN(nativeNodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nativeNodeArg->ToNativePointer(vm)->Value());
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        GetArkUINodeModifiers()->getWebModifier()->resetOnHttpAuthRequest(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::NativePointerRef::New(vm, nullptr));
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<bool(WebHttpAuthEvent&)> callback = [vm, frameNode, func = panda::CopyableGlobal(vm, func)](
                                                          WebHttpAuthEvent& event) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
        const char* keys[] = { "host", "realm", "handler" };
        Framework::JSRef<Framework::JSObject> handlerObj = Framework::JSWeb::CreateHttpAuthRequestHandler(event);
        Local<JSValueRef> values[] = { panda::StringRef::NewFromUtf8(vm, event.GetHost().c_str()),
            panda::StringRef::NewFromUtf8(vm, event.GetRealm().c_str()), handlerObj->GetLocalHandle() };

        auto eventObject = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(keys), keys, values);
        eventObject->SetNativePointerFieldCount(vm, CALL_ARG_1);
        eventObject->SetNativePointerField(vm, CALL_ARG_0, static_cast<void*>(&event));
        panda::Local<panda::JSValueRef> params[1] = { eventObject };
        auto ret = func->Call(vm, func.ToLocal(), params, CALL_ARG_1);
        return ret->IsBoolean() && ret->ToBoolean(vm)->Value();
    };
    GetArkUINodeModifiers()->getWebModifier()->setOnHttpAuthRequest(nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WebBridge::ResetOnHttpAuthRequest(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getWebModifier()->resetOnHttpAuthRequest(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WebBridge::SetOnConsole(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(1);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        GetArkUINodeModifiers()->getWebModifier()->resetOnConsole(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<bool(LoadWebConsoleLogEvent&)> callback = [vm, frameNode, func = panda::CopyableGlobal(vm, func)](
                                                                LoadWebConsoleLogEvent& event) -> bool {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
        Framework::JSRef<Framework::JSObject> handlerObj = Framework::JSWeb::CreateConsoleHandler(event);
        auto eventObject = panda::ObjectRef::New(vm);
        eventObject->Set(vm, panda::StringRef::NewFromUtf8(vm, "message"), handlerObj->GetLocalHandle());
        eventObject->SetNativePointerFieldCount(vm, 1);
        eventObject->SetNativePointerField(vm, 0, static_cast<void*>(&event));
        panda::Local<panda::JSValueRef> params[1] = { eventObject };
        auto ret = func->Call(vm, func.ToLocal(), params, 1);
        return ret->IsBoolean() && ret->ToBoolean(vm)->Value();
    };
    GetArkUINodeModifiers()->getWebModifier()->setOnConsole(nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WebBridge::ResetOnConsole(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getWebModifier()->resetOnConsole(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WebBridge::SetOnSslErrorEvent(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(1);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        GetArkUINodeModifiers()->getWebModifier()->resetOnSslErrorEvent(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<void(WebAllSslErrorEvent&)> callback = [vm, frameNode, func = panda::CopyableGlobal(vm, func)](
                                                             WebAllSslErrorEvent& event) -> void {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
        const char* keys[] = { "handler", "error", "url", "originalUrl", "referrer", "isFatalError", "isMainFrame" };
        Framework::JSRef<Framework::JSObject> handlerObj = Framework::JSWeb::CreateSslErrorEventHandler(event);
        Local<JSValueRef> values[] = { handlerObj->GetLocalHandle(), panda::NumberRef::New(vm, event.GetError()),
            panda::StringRef::NewFromUtf8(vm, event.GetUrl().c_str()),
            panda::StringRef::NewFromUtf8(vm, event.GetOriginalUrl().c_str()),
            panda::StringRef::NewFromUtf8(vm, event.GetReferrer().c_str()),
            panda::BooleanRef::New(vm, event.GetIsFatalError()), panda::BooleanRef::New(vm, event.GetIsMainFrame()) };
        auto eventObject = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(keys), keys, values);
        eventObject->SetNativePointerFieldCount(vm, 1);
        eventObject->SetNativePointerField(vm, 0, static_cast<void*>(&event));
        panda::Local<panda::JSValueRef> params[1] = { eventObject };
        func->Call(vm, func.ToLocal(), params, 1);
    };
    GetArkUINodeModifiers()->getWebModifier()->setOnSslErrorEvent(nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WebBridge::ResetOnSslErrorEvent(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getWebModifier()->resetOnSslErrorEvent(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WebBridge::SetOnDataResubmitted(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(1);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        GetArkUINodeModifiers()->getWebModifier()->resetOnDataResubmitted(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<void(DataResubmittedEvent&)> callback = [vm, frameNode, func = panda::CopyableGlobal(vm, func)](
                                                              DataResubmittedEvent& event) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
        Framework::JSRef<Framework::JSObject> handlerObj = Framework::JSWeb::CreateDataResubmittedHandler(event);
        auto eventObject = panda::ObjectRef::New(vm);
        eventObject->Set(vm, panda::StringRef::NewFromUtf8(vm, "handler"), handlerObj->GetLocalHandle());
        eventObject->SetNativePointerFieldCount(vm, 1);
        eventObject->SetNativePointerField(vm, 0, static_cast<void*>(&event));
        panda::Local<panda::JSValueRef> params[1] = { eventObject };
        func->Call(vm, func.ToLocal(), params, 1);
    };
    GetArkUINodeModifiers()->getWebModifier()->setOnDataResubmitted(nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WebBridge::ResetOnDataResubmitted(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getWebModifier()->resetOnDataResubmitted(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WebBridge::SetGestureFocusMode(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    int mode = secondArg->Int32Value(vm);
    GetArkUINodeModifiers()->getWebModifier()->setGestureFocusMode(nativeNode, mode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue WebBridge::ResetGestureFocusMode(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getWebModifier()->resetGestureFocusMode(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
} // namespace OHOS::Ace::NG
