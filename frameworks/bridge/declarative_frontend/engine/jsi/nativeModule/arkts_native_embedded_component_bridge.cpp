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
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_embedded_component_bridge.h"

#include "bridge/common/utils/engine_helper.h"
#include "frameworks/bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"

namespace OHOS::Ace::NG {
constexpr int NUM_2 = 2;
ArkUINativeModuleValue EmbeddedComponentBridge::SetOnTerminated(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    if (runtimeCallInfo->GetArgsNumber() < NUM_2) {
        return panda::NativePointerRef::New(vm, nullptr);
    }
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(1);
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        nodeModifiers->getEmbeddedComponentModifier()->resetOnTerminated(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    auto instanceId = ContainerScope::CurrentId();
    std::function<void(int32_t, const RefPtr<WantWrap>&)> onTerminated = [vm, func = panda::CopyableGlobal(vm, func),
                                                                             instanceId, frameNode](int32_t code,
                                                                             const RefPtr<WantWrap>& wantWrap) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        ContainerScope scope(instanceId);
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
        auto engine = EngineHelper::GetCurrentEngine();
        CHECK_NULL_VOID(engine);
        NativeEngine* nativeEngine = engine->GetNativeEngine();
        CHECK_NULL_VOID(nativeEngine);
        auto obj = panda::ObjectRef::New(vm);
        obj->Set(vm, panda::StringRef::NewFromUtf8(vm, "code"), panda::NumberRef::New(vm, code));
        if (wantWrap) {
            auto nativeWant =
                WantWrap::ConvertToNativeValue(wantWrap->GetWant(), reinterpret_cast<napi_env>(nativeEngine));
            auto localRef = NapiValueToLocalValue(nativeWant);
            obj->Set(vm, panda::StringRef::NewFromUtf8(vm, "want"), localRef);
        }
        panda::Local<panda::JSValueRef> params[] = { obj };
        func->Call(vm, func.ToLocal(), params, 1);
    };
    nodeModifiers->getEmbeddedComponentModifier()->setOnTerminated(nativeNode, reinterpret_cast<void*>(&onTerminated));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue EmbeddedComponentBridge::ResetOnTerminated(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    if (runtimeCallInfo->GetArgsNumber() < 1) {
        return panda::NativePointerRef::New(vm, nullptr);
    }
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getEmbeddedComponentModifier()->resetOnTerminated(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue EmbeddedComponentBridge::SetOnError(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    if (runtimeCallInfo->GetArgsNumber() < NUM_2) {
        return panda::NativePointerRef::New(vm, nullptr);
    }
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(1);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::NativePointerRef::New(vm, nullptr));
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        nodeModifiers->getEmbeddedComponentModifier()->resetOnError(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    auto instanceId = ContainerScope::CurrentId();
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<void(int32_t, const std::string&, const std::string&)> onError =
        [vm, func = panda::CopyableGlobal(vm, func), instanceId, frameNode](
            int32_t code, const std::string& name, const std::string& message) {
            panda::LocalScope pandaScope(vm);
            panda::TryCatch trycatch(vm);
            ContainerScope scope(instanceId);
            PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));

            const char* keys[] = { "code", "name", "message" };
            Local<JSValueRef> values[] = { panda::NumberRef::New(vm, code),
                panda::StringRef::NewFromUtf8(vm, name.c_str()), panda::StringRef::NewFromUtf8(vm, message.c_str()) };
            auto onErrorObj = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(keys), keys, values);
            panda::Local<panda::JSValueRef> params[] = { onErrorObj };
            func->Call(vm, func.ToLocal(), params, 1);
        };
    nodeModifiers->getEmbeddedComponentModifier()->setOnError(nativeNode, reinterpret_cast<void*>(&onError));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue EmbeddedComponentBridge::ResetOnError(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    if (runtimeCallInfo->GetArgsNumber() < 1) {
        return panda::NativePointerRef::New(vm, nullptr);
    }
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getEmbeddedComponentModifier()->resetOnError(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
}
