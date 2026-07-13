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

#include "core/components_ng/pattern/xcomponent/bridge/arkts_native_xcomponent_node_bridge.h"

#include "bridge/declarative_frontend/jsview/js_xcomponent.h"
#include "bridge/declarative_frontend/jsview/js_xcomponent_controller.h"

namespace OHOS::Ace::NG {

void XComponentNodeBridge::RegisterXComponentNodeAttributes(Local<panda::ObjectRef> object, EcmaVM* vm)
{
    auto xcomponentNode = panda::ObjectRef::New(vm);
    xcomponentNode->Set(vm, panda::StringRef::NewFromUtf8(vm, "create"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), XComponentNodeBridge::Create));
    xcomponentNode->Set(vm, panda::StringRef::NewFromUtf8(vm, "getFrameNode"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), XComponentNodeBridge::GetFrameNode));
    xcomponentNode->Set(vm, panda::StringRef::NewFromUtf8(vm, "registerOnCreateCallback"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), XComponentNodeBridge::RegisterOnCreateCallback));
    xcomponentNode->Set(vm, panda::StringRef::NewFromUtf8(vm, "registerOnDestroyCallback"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), XComponentNodeBridge::RegisterOnDestroyCallback));
    xcomponentNode->Set(vm, panda::StringRef::NewFromUtf8(vm, "changeRenderType"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), XComponentNodeBridge::ChangeRenderType));
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "xcomponentNode"), xcomponentNode);
}

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
            static_cast<Framework::JSXComponentController*>(Local<panda::ObjectRef>(arg)->GetNativePointerField(vm, 0));
    }

    return params;
}

ArkUINativeModuleValue XComponentNodeBridge::Create(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Framework::XComponentParams params = SetXComponentNodeParams(runtimeCallInfo, vm);
    void* xcomponentNode = Framework::XComponentNode::Create(params);
    ACE_UINODE_TRACE(xcomponentNode ? AceType::DynamicCast<FrameNode>(
                                          reinterpret_cast<Framework::XComponentNode*>(xcomponentNode)->GetFrameNode())
                                    : nullptr);
    auto nativeModule = panda::NativePointerRef::New(
        vm, reinterpret_cast<void*>(xcomponentNode),
        [](void* env, void* data, [[maybe_unused]] void* hint) {
            auto* xcomponentNode = reinterpret_cast<Framework::XComponentNode*>(data);
            if (xcomponentNode) {
                delete xcomponentNode;
                xcomponentNode = nullptr;
            }
        },
        reinterpret_cast<void*>(xcomponentNode), sizeof(void*));
    return nativeModule;
}

ArkUINativeModuleValue XComponentNodeBridge::GetFrameNode(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    if (!firstArg->IsNativePointer(vm)) {
        return panda::JSValueRef::Undefined(vm);
    }
    Framework::XComponentNode* xcomponentNode =
        reinterpret_cast<Framework::XComponentNode*>(firstArg->ToNativePointer(vm)->Value());
    if (xcomponentNode) {
        auto frameNode = xcomponentNode->GetFrameNode();
        ACE_UINODE_TRACE(AceType::DynamicCast<FrameNode>(frameNode));
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
    if (!firstArg->IsNativePointer(vm)) {
        return panda::JSValueRef::Undefined(vm);
    }
    Framework::XComponentNode* xcomponentNode =
        reinterpret_cast<Framework::XComponentNode*>(firstArg->ToNativePointer(vm)->Value());
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    if (xcomponentNode && secondArg->IsFunction(vm)) {
        ACE_UINODE_TRACE(AceType::DynamicCast<FrameNode>(xcomponentNode->GetFrameNode()));
        xcomponentNode->RegisterOnCreate(runtimeCallInfo, secondArg);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue XComponentNodeBridge::RegisterOnDestroyCallback(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    if (!firstArg->IsNativePointer(vm)) {
        return panda::JSValueRef::Undefined(vm);
    }
    Framework::XComponentNode* xcomponentNode =
        reinterpret_cast<Framework::XComponentNode*>(firstArg->ToNativePointer(vm)->Value());
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    if (xcomponentNode && secondArg->IsFunction(vm)) {
        ACE_UINODE_TRACE(AceType::DynamicCast<FrameNode>(xcomponentNode->GetFrameNode()));
        xcomponentNode->RegisterOnDestroy(runtimeCallInfo, secondArg);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue XComponentNodeBridge::ChangeRenderType(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    auto defaultNativeModule = panda::BooleanRef::New(vm, false);
    CHECK_NULL_RETURN(vm, defaultNativeModule);
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    if (!firstArg->IsNativePointer(vm)) {
        return defaultNativeModule;
    }
    Framework::XComponentNode* xcomponentNode =
        reinterpret_cast<Framework::XComponentNode*>(firstArg->ToNativePointer(vm)->Value());
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    if (xcomponentNode && secondArg->IsNumber()) {
        ACE_UINODE_TRACE(AceType::DynamicCast<FrameNode>(xcomponentNode->GetFrameNode()));
        auto ret = xcomponentNode->ChangeRenderType(secondArg->Int32Value(vm));
        auto nativeModule = panda::BooleanRef::New(vm, ret);
        return nativeModule;
    }
    return defaultNativeModule;
}
} // namespace OHOS::Ace::NG
