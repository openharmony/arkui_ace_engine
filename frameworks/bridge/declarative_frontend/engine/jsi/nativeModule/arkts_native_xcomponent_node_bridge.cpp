/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_xcomponent_node_bridge.h"

#include "bridge/declarative_frontend/jsview/js_xcomponent.h"
#include "bridge/declarative_frontend/jsview/js_xcomponent_controller.h"

namespace OHOS::Ace::NG {

Framework::XComponentParams XComponentNodeBridge::SetXComponentNodeParams(
    ArkUIRuntimeCallInfo* runtimeCallInfo, EcmaVM* vm)
{
    Framework::XComponentParams params;

    // elmtId
    Local<JSValueRef> arg = runtimeCallInfo->GetCallArgRef(0);
    if (arg->IsNumber()) {
        params.elmtId = arg->Int32Value(vm);
    }
    // xcomponent id
    arg = runtimeCallInfo->GetCallArgRef(1);
    if (arg->IsString(vm)) {
        params.xcomponentId = arg->ToString(vm)->ToString(vm);
    }
    // xcomponentType
    arg = runtimeCallInfo->GetCallArgRef(2);
    if (arg->IsNumber()) {
        params.xcomponentType = arg->Int32Value(vm);
    }
    // renderType
    arg = runtimeCallInfo->GetCallArgRef(3);
    if (arg->IsNumber()) {
        params.renderType = arg->Int32Value(vm);
    }
    // surfaceId
    arg = runtimeCallInfo->GetCallArgRef(4);
    if (arg->IsString(vm)) {
        params.surfaceId = arg->ToString(vm)->ToString(vm);
    }
    // selfIdealWidth
    arg = runtimeCallInfo->GetCallArgRef(5);
    if (arg->IsNumber()) {
        params.width = arg->Int32Value(vm);
    }
    // selfIdealHeight
    arg = runtimeCallInfo->GetCallArgRef(6);
    if (arg->IsNumber()) {
        params.height = arg->Int32Value(vm);
    }
    // libraryname
    arg = runtimeCallInfo->GetCallArgRef(7);
    if (arg->IsString(vm)) {
        params.libraryName = arg->ToString(vm)->ToString(vm);
    }
    // xComponentController
    arg = runtimeCallInfo->GetCallArgRef(8);
    if (!arg->IsUndefined()) {
        params.controller =
            static_cast<Framework::JSXComponentController*>(Local<panda::ObjectRef>(arg)->GetNativePointerField(
                vm, 0));
    }

    return params;
}

ArkUINativeModuleValue XComponentNodeBridge::Create(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Framework::XComponentParams params = SetXComponentNodeParams(runtimeCallInfo, vm);
    void* jsXComponent = Framework::JSXComponent::Create(params);
    auto nativeModule = panda::NativePointerRef::New(
        vm, reinterpret_cast<void*>(jsXComponent),
        [](void *env, void* data, [[maybe_unused]] void* hint) {
            auto* jsXComponent = reinterpret_cast<Framework::JSXComponent*>(data);
            if (jsXComponent) {
                delete jsXComponent;
                jsXComponent = nullptr;
            }
        },
        reinterpret_cast<void*>(jsXComponent), sizeof(void*));
    return nativeModule;
}

ArkUINativeModuleValue XComponentNodeBridge::GetFrameNode(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Framework::JSXComponent* jsXComponent =
        reinterpret_cast<Framework::JSXComponent*>(firstArg->ToNativePointer(vm)->Value());
    if (jsXComponent) {
        auto frameNode = jsXComponent->GetFrameNode();
        auto nativeModule = panda::NativePointerRef::New(vm, reinterpret_cast<void*>(AceType::RawPtr(frameNode)));
        return nativeModule;
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue XComponentNodeBridge::RegisterOnCreateCallback(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Framework::JSXComponent* jsXComponent =
        reinterpret_cast<Framework::JSXComponent*>(firstArg->ToNativePointer(vm)->Value());
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    if (jsXComponent && secondArg->IsFunction(vm)) {
        Framework::JsiExecutionContext execCtx = { vm };
        jsXComponent->RegisterOnCreate(execCtx, secondArg);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue XComponentNodeBridge::RegisterOnDestroyCallback(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Framework::JSXComponent* jsXComponent =
        reinterpret_cast<Framework::JSXComponent*>(firstArg->ToNativePointer(vm)->Value());
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    if (jsXComponent && secondArg->IsFunction(vm)) {
        Framework::JsiExecutionContext execCtx = { vm };
        jsXComponent->RegisterOnDestroy(execCtx, secondArg);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue XComponentNodeBridge::ChangeRenderType(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    auto defaultNativeModule = panda::BooleanRef::New(vm, false);
    CHECK_NULL_RETURN(vm, defaultNativeModule);
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Framework::JSXComponent* jsXComponent =
        reinterpret_cast<Framework::JSXComponent*>(firstArg->ToNativePointer(vm)->Value());
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    if (jsXComponent && secondArg->IsNumber()) {
        auto ret = jsXComponent->ChangeRenderType(secondArg->Int32Value(vm));
        auto nativeModule = panda::BooleanRef::New(vm, ret);
        return nativeModule;
    }
    return defaultNativeModule;
}
} // namespace OHOS::Ace::NG
