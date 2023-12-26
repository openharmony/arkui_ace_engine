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

#include "bridge/declarative_frontend/engine/jsi/components/arkts_native_api.h"

#include "bridge/declarative_frontend/jsview/js_xcomponent.h"
namespace OHOS::Ace::NG {

ArkUINativeModuleValue XComponentNodeBridge::Create(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));

    Framework::XComponentParams params;
    //elmtId
    Local<JSValueRef> arg = runtimeCallInfo->GetCallArgRef(0);
    if (arg->IsNumber()) {
        params.elmtId = arg->Int32Value(vm);
    }

    //options
    arg = runtimeCallInfo->GetCallArgRef(1);
    auto jsOptions = arg->ToObject(vm);
    if (!jsOptions->IsNull()) {
        auto jsIdealSize = jsOptions->Get(vm, panda::StringRef::NewFromUtf8(vm, "selfIdealSize"));
        auto jsRenderType = jsOptions->Get(vm, panda::StringRef::NewFromUtf8(vm, "type"));
        auto jsSurfaceId  = jsOptions->Get(vm, panda::StringRef::NewFromUtf8(vm, "surfaceId"));
        if (jsIdealSize->IsObject()) {
            auto jsSize = jsIdealSize->ToObject(vm);
            auto jsWidth = jsSize->Get(vm, panda::StringRef::NewFromUtf8(vm, "width"));
            auto jsHeight = jsSize->Get(vm, panda::StringRef::NewFromUtf8(vm, "height"));
            if (jsWidth->IsNumber() && jsWidth->IsNumber()) {
                params.width = jsWidth->Int32Value(vm);
                params.height = jsHeight->Int32Value(vm);
            }
        }
        if (jsRenderType->IsNumber()) {
            params.renderType = jsRenderType->Int32Value(vm);
        }
        if (jsSurfaceId->IsString()) {
            params.surfaceId = jsSurfaceId->ToString(vm)->ToString();
        }
    }

    // xcomponent id
    arg = runtimeCallInfo->GetCallArgRef(2);
    if (arg->IsString()) {
        params.xcomponentId = arg->ToString(vm)->ToString();
    }
    // xcomponentType
    arg = runtimeCallInfo->GetCallArgRef(3);
    if (arg->IsNumber()) {
        params.xcomponentType = arg->Int32Value(vm);
    }
    // libraryname
    arg = runtimeCallInfo->GetCallArgRef(4);
    if (arg->IsString()) {
        params.libraryName = arg->ToString(vm)->ToString();
    }

    void* jsXComponent = Framework::JSXComponent::Create(params); // 此处应该返回framenode的强引用，并且与js层的xcomponentNode实例绑定（xcomponent framenode生命周期保持与xcomponentNode实例一致）
    auto nativeModule = panda::NativePointerRef::New(
        vm, reinterpret_cast<void *>(jsXComponent),
        [](void *data, [[maybe_unused]] void *hint) {
            auto jsXComponent = reinterpret_cast<Framework::JSXComponent*>(data);
            delete jsXComponent;
            jsXComponent = nullptr;
        }, nullptr, sizeof(jsXComponent));
    return nativeModule;
}

ArkUINativeModuleValue XComponentNodeBridge::SetRenderType(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue XComponentNodeBridge::GetRenderType(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    return panda::JSValueRef::Undefined(vm);
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
        auto nativeModule =
            panda::NativePointerRef::New(vm, reinterpret_cast<void *>(AccessibilityManager::RawPtr(frameNode)));
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
    if (jsXComponent && secondArg->IsFunction()) {
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
    if (jsXComponent && secondArg->IsFunction()) {
        Framework::JsiExecutionContext execCtx = { vm };
        jsXComponent->RegisterOnDestroy(execCtx, secondArg);
    }
    return panda::JSValueRef::Undefined(vm);
}
} // namespace OHOS::Ace::NG
