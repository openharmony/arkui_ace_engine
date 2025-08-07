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
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_list_item_bridge.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_list_item.h"
using namespace OHOS::Ace::Framework;

namespace OHOS::Ace::NG {
constexpr int32_t NUM_0 = 0;
constexpr int32_t NUM_1 = 1;

ArkUINativeModuleValue ListItemBridge::SetListItemSelected(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());

    bool selected = false;
    if (secondArg->IsBoolean()) {
        selected = secondArg->ToBoolean(vm)->Value();
    }
    GetArkUINodeModifiers()->getListItemModifier()->setListItemSelected(nativeNode, selected);

    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ListItemBridge::ResetListItemSelected(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getListItemModifier()->resetListItemSelected(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ListItemBridge::SetSelectable(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (!secondArg->IsUndefined() && secondArg->IsBoolean()) {
        bool selectable = secondArg->ToBoolean(vm)->Value();
        GetArkUINodeModifiers()->getListItemModifier()->setSelectable(nativeNode, selectable);
    }

    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ListItemBridge::ResetSelectable(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getListItemModifier()->resetSelectable(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ListItemBridge::SetSwipeAction(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Framework::JsiCallbackInfo info = Framework::JsiCallbackInfo(runtimeCallInfo);
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::NativePointerRef::New(vm, nullptr));
    // 2: argument count.
    if (info.Length() != 2 || !(info[1]->IsObject())) {
        GetArkUINodeModifiers()->getListItemModifier()->resetListItemSwipeAction(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    JSListItem::ParseSwiperAction(Framework::JSRef<Framework::JSObject>::Cast(info[1]),
        info.GetExecutionContext(), frameNode);

    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ListItemBridge::ResetSwipeAction(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getListItemModifier()->resetListItemSwipeAction(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ListItemBridge::SetOnSelect(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        GetArkUINodeModifiers()->getListItemModifier()->resetListItemOnSelectCallback(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);

    std::function<void(bool)> callback = [vm, frameNode, func = panda::CopyableGlobal(vm, func)](bool isSelected) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
        panda::Local<panda::JSValueRef> params[NUM_1] = { panda::BooleanRef::New(vm, isSelected) };
        func->Call(vm, func.ToLocal(), params, NUM_1);
    };
    GetArkUINodeModifiers()->getListItemModifier()->setListItemOnSelectCallback(
        nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ListItemBridge::ResetOnSelect(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getListItemModifier()->resetListItemOnSelectCallback(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ListItemBridge::SetListItemInitialize(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> styleArg = runtimeCallInfo->GetCallArgRef(1); // 1 is index of style
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());

    if (styleArg->IsUndefined() || styleArg->IsNull() || !styleArg->IsNumber()) {
        GetArkUINodeModifiers()->getListItemModifier()->resetListItemStyle(nativeNode);
    } else {
        uint32_t style = styleArg->Uint32Value(vm);
        if (style < static_cast<uint32_t>(V2::ListItemStyle::NONE) ||
            style > static_cast<uint32_t>(V2::ListItemStyle::CARD)) {
            style = static_cast<uint32_t>(V2::ListItemStyle::NONE);
        }
        GetArkUINodeModifiers()->getListItemModifier()->setListItemStyle(nativeNode, style);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ListItemBridge::ResetListItemInitialize(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getListItemModifier()->resetListItemStyle(nativeNode);

    return panda::JSValueRef::Undefined(vm);
}
} // namespace OHOS::Ace::NG