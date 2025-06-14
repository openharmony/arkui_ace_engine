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
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_node_adapter_bridge.h"

#include "jsnapi_expo.h"

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "base/utils/utils.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_frame_node_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_utils_bridge.h"
#include "core/interfaces/arkoala/arkoala_api.h"
#include "frameworks/core/interfaces/native/node/node_adapter_impl.h"

namespace OHOS::Ace::NG {

UINodeAdapter* GetNodeAdapter(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, nullptr);
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(!firstArg.IsNull(), nullptr);
    auto* adapter = reinterpret_cast<UINodeAdapter*>(firstArg->ToNativePointer(vm)->Value());
    return adapter;
}

void SetAttachCallback(EcmaVM* vm, UINodeAdapter* adapter, const panda::Local<panda::JSValueRef>& argRef,
    const panda::Local<panda::JSValueRef>& thisRef)
{
    CHECK_NULL_VOID(adapter);
    CHECK_NULL_VOID(!argRef->IsUndefined());
    CHECK_NULL_VOID(argRef->IsFunction(vm));
    auto attachObj = argRef->ToObject(vm);
    panda::Local<panda::FunctionRef> attachFunc = attachObj;
    auto onAttachToNode = [vm, func = JsWeak(panda::CopyableGlobal(vm, attachFunc)),
                              thisRef = JsWeak(panda::CopyableGlobal(vm, thisRef))](ArkUINodeHandle node) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        auto function = func.Lock();
        CHECK_NULL_VOID(!function.IsEmpty());
        CHECK_NULL_VOID(function->IsFunction(vm));
        panda::Local<panda::JSValueRef> params[1] = { FrameNodeBridge::MakeFrameNodeInfo(vm, node) };
        function->Call(vm, thisRef.Lock().ToLocal(), params, 1);
    };
    adapter->SetOnAttachToNodeFunc(std::move(onAttachToNode));
}

void SetDetachCallback(EcmaVM* vm, UINodeAdapter* adapter, const panda::Local<panda::JSValueRef>& argRef,
    const panda::Local<panda::JSValueRef>& thisRef)
{
    CHECK_NULL_VOID(adapter);
    CHECK_NULL_VOID(!argRef->IsUndefined());
    CHECK_NULL_VOID(argRef->IsFunction(vm));
    auto detachObj = argRef->ToObject(vm);
    panda::Local<panda::FunctionRef> detachFunc = detachObj;
    auto onDetachFromNode = [vm, func = JsWeak(panda::CopyableGlobal(vm, detachFunc)),
                                thisRef = JsWeak(panda::CopyableGlobal(vm, thisRef))]() {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        auto function = func.Lock();
        CHECK_NULL_VOID(!function.IsEmpty());
        CHECK_NULL_VOID(function->IsFunction(vm));
        function->Call(vm, thisRef.Lock().ToLocal(), {}, 0);
    };
    adapter->SetOnDetachFromNodeFunc(std::move(onDetachFromNode));
}

void SetGetIdCallback(EcmaVM* vm, UINodeAdapter* adapter, const panda::Local<panda::JSValueRef>& argRef,
    const panda::Local<panda::JSValueRef>& thisRef)
{
    CHECK_NULL_VOID(adapter);
    CHECK_NULL_VOID(!argRef->IsUndefined());
    CHECK_NULL_VOID(argRef->IsFunction(vm));
    auto getIdObj = argRef->ToObject(vm);
    panda::Local<panda::FunctionRef> getIdFunc = getIdObj;
    auto onGetId = [vm, func = JsWeak(panda::CopyableGlobal(vm, getIdFunc)),
                       thisRef = JsWeak(panda::CopyableGlobal(vm, thisRef))](uint32_t index) -> int32_t {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        auto function = func.Lock();
        CHECK_NULL_RETURN(!function.IsEmpty(), index);
        CHECK_NULL_RETURN(function->IsFunction(vm), index);
        panda::Local<panda::JSValueRef> params[1] = { panda::NumberRef::New(vm, index) };
        auto result = function->Call(vm, thisRef.Lock().ToLocal(), params, 1);
        CHECK_NULL_RETURN(result->IsNumber(), index);
        return result->Int32Value(vm);
    };
    adapter->SetOnGetChildIdFunc(std::move(onGetId));
}

void SetCreateNewChildCallback(EcmaVM* vm, UINodeAdapter* adapter, const panda::Local<panda::JSValueRef>& argRef,
    const panda::Local<panda::JSValueRef>& thisRef)
{
    CHECK_NULL_VOID(adapter);
    CHECK_NULL_VOID(!argRef->IsUndefined());
    CHECK_NULL_VOID(argRef->IsFunction(vm));
    auto createChildObj = argRef->ToObject(vm);
    panda::Local<panda::FunctionRef> createChildFunc = createChildObj;
    auto onCreateChild = [vm, func = JsWeak(panda::CopyableGlobal(vm, createChildFunc)),
                             thisRef = JsWeak(panda::CopyableGlobal(vm, thisRef))](uint32_t index) -> ArkUINodeHandle {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        auto function = func.Lock();
        CHECK_NULL_RETURN(!function.IsEmpty(), nullptr);
        CHECK_NULL_RETURN(function->IsFunction(vm), nullptr);
        panda::Local<panda::JSValueRef> params[1] = { panda::NumberRef::New(vm, index) };
        auto result = function->Call(vm, thisRef.Lock().ToLocal(), params, 1);
        CHECK_NULL_RETURN(result->IsNativePointer(vm), nullptr);
        auto node = nodePtr(result->ToNativePointer(vm)->Value());
        auto* currentNode = reinterpret_cast<UINode*>(node);
        CHECK_NULL_RETURN(currentNode, node);
        currentNode->SetNodeAdapter(true);
        return node;
    };
    adapter->SetOnCreateNewChild(std::move(onCreateChild));
}

void SetDisposeChildCallback(EcmaVM* vm, UINodeAdapter* adapter, const panda::Local<panda::JSValueRef>& argRef,
    const panda::Local<panda::JSValueRef>& thisRef)
{
    CHECK_NULL_VOID(adapter);
    CHECK_NULL_VOID(!argRef->IsUndefined());
    CHECK_NULL_VOID(argRef->IsFunction(vm));
    auto disposeChildObj = argRef->ToObject(vm);
    panda::Local<panda::FunctionRef> disposeChildFunc = disposeChildObj;
    auto onDisposeChild = [vm, func = JsWeak(panda::CopyableGlobal(vm, disposeChildFunc)),
                              thisRef = JsWeak(panda::CopyableGlobal(vm, thisRef))](ArkUINodeHandle node, int32_t id) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        auto function = func.Lock();
        CHECK_NULL_VOID(!function.IsEmpty());
        CHECK_NULL_VOID(function->IsFunction(vm));
        panda::Local<panda::JSValueRef> params[2] = { panda::NumberRef::New(vm, id),
            FrameNodeBridge::MakeFrameNodeInfo(vm, node) };
        auto* currentNode = reinterpret_cast<UINode*>(node);
        CHECK_NULL_VOID(currentNode);
        currentNode->SetNodeAdapter(true);
        function->Call(vm, thisRef.Lock().ToLocal(), params, 2);
    };
    adapter->SetOnDisposeChild(std::move(onDisposeChild));
}

void SetUpdateChildCallback(EcmaVM* vm, UINodeAdapter* adapter, const panda::Local<panda::JSValueRef>& argRef,
    const panda::Local<panda::JSValueRef>& thisRef)
{
    CHECK_NULL_VOID(adapter);
    CHECK_NULL_VOID(!argRef->IsUndefined());
    CHECK_NULL_VOID(argRef->IsFunction(vm));
    auto updateChildObj = argRef->ToObject(vm);
    panda::Local<panda::FunctionRef> updateChildFunc = updateChildObj;
    auto onUpdateChild = [vm, func = JsWeak(panda::CopyableGlobal(vm, updateChildFunc)),
                              thisRef = JsWeak(panda::CopyableGlobal(vm, thisRef))](ArkUINodeHandle node, int32_t id) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        auto function = func.Lock();
        CHECK_NULL_VOID(!function.IsEmpty());
        CHECK_NULL_VOID(function->IsFunction(vm));
        panda::Local<panda::JSValueRef> params[2] = { panda::NumberRef::New(vm, id),
            FrameNodeBridge::MakeFrameNodeInfo(vm, node) };
        function->Call(vm, thisRef.Lock().ToLocal(), params, 2);
    };
    adapter->SetOnUpdateChind(std::move(onUpdateChild));
}

ArkUINativeModuleValue NodeAdapterBridge::CreateNodeAdapter(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    auto* handle = GetArkUIFullNodeAPI()->getNodeAdapterAPI()->create();
    CHECK_NULL_RETURN(handle, panda::JSValueRef::Undefined(vm));
    auto ref = AceType::MakeRefPtr<UINodeAdapter>(handle);
    auto nativeRef = NativeUtilsBridge::CreateStrongRef(vm, ref);
    return nativeRef;
}

ArkUINativeModuleValue NodeAdapterBridge::SetCallbacks(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    auto* adapter = GetNodeAdapter(runtimeCallInfo);
    CHECK_NULL_RETURN(adapter, panda::JSValueRef::Undefined(vm));
    auto thisRef = runtimeCallInfo->GetCallArgRef(1);
    SetAttachCallback(vm, adapter, runtimeCallInfo->GetCallArgRef(2), thisRef);
    SetDetachCallback(vm, adapter, runtimeCallInfo->GetCallArgRef(3), thisRef);
    SetGetIdCallback(vm, adapter, runtimeCallInfo->GetCallArgRef(4), thisRef);
    SetCreateNewChildCallback(vm, adapter, runtimeCallInfo->GetCallArgRef(5), thisRef);
    SetDisposeChildCallback(vm, adapter, runtimeCallInfo->GetCallArgRef(6), thisRef);
    SetUpdateChildCallback(vm, adapter, runtimeCallInfo->GetCallArgRef(7), thisRef);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue NodeAdapterBridge::SetTotalNodeCount(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    auto* adapter = GetNodeAdapter(runtimeCallInfo);
    CHECK_NULL_RETURN(adapter, panda::JSValueRef::Undefined(vm));
    auto countArg = runtimeCallInfo->GetCallArgRef(1);
    CHECK_NULL_RETURN(countArg->IsNumber(), panda::JSValueRef::Undefined(vm));
    adapter->SetTotalNodeCount(countArg->Uint32Value(vm));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue NodeAdapterBridge::GetTotalNodeCount(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    auto* adapter = GetNodeAdapter(runtimeCallInfo);
    CHECK_NULL_RETURN(adapter, panda::JSValueRef::Undefined(vm));
    uint32_t count = adapter->GetTotalNodeCount();
    return panda::NumberRef::New(vm, count);
}

ArkUINativeModuleValue NodeAdapterBridge::NotifyItemReloaded(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    auto* adapter = GetNodeAdapter(runtimeCallInfo);
    CHECK_NULL_RETURN(adapter, panda::JSValueRef::Undefined(vm));
    adapter->NotifyItemReloaded();
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue NodeAdapterBridge::NotifyItemChanged(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    auto* adapter = GetNodeAdapter(runtimeCallInfo);
    CHECK_NULL_RETURN(adapter, panda::JSValueRef::Undefined(vm));
    auto startArg = runtimeCallInfo->GetCallArgRef(1);
    CHECK_NULL_RETURN(startArg->IsNumber(), panda::JSValueRef::Undefined(vm));
    auto countArg = runtimeCallInfo->GetCallArgRef(2);
    CHECK_NULL_RETURN(countArg->IsNumber(), panda::JSValueRef::Undefined(vm));
    adapter->NotifyItemChanged(startArg->Uint32Value(vm), countArg->Uint32Value(vm));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue NodeAdapterBridge::NotifyItemRemoved(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    auto* adapter = GetNodeAdapter(runtimeCallInfo);
    CHECK_NULL_RETURN(adapter, panda::JSValueRef::Undefined(vm));
    auto startArg = runtimeCallInfo->GetCallArgRef(1);
    CHECK_NULL_RETURN(startArg->IsNumber(), panda::JSValueRef::Undefined(vm));
    auto countArg = runtimeCallInfo->GetCallArgRef(2);
    CHECK_NULL_RETURN(countArg->IsNumber(), panda::JSValueRef::Undefined(vm));
    adapter->NotifyItemRemoved(startArg->Uint32Value(vm), countArg->Uint32Value(vm));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue NodeAdapterBridge::NotifyItemInserted(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    auto* adapter = GetNodeAdapter(runtimeCallInfo);
    CHECK_NULL_RETURN(adapter, panda::JSValueRef::Undefined(vm));
    auto startArg = runtimeCallInfo->GetCallArgRef(1);
    CHECK_NULL_RETURN(startArg->IsNumber(), panda::JSValueRef::Undefined(vm));
    auto countArg = runtimeCallInfo->GetCallArgRef(2);
    CHECK_NULL_RETURN(countArg->IsNumber(), panda::JSValueRef::Undefined(vm));
    adapter->NotifyItemInserted(startArg->Uint32Value(vm), countArg->Uint32Value(vm));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue NodeAdapterBridge::NotifyItemMoved(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    auto* adapter = GetNodeAdapter(runtimeCallInfo);
    CHECK_NULL_RETURN(adapter, panda::JSValueRef::Undefined(vm));
    auto fromArg = runtimeCallInfo->GetCallArgRef(1);
    CHECK_NULL_RETURN(fromArg->IsNumber(), panda::JSValueRef::Undefined(vm));
    auto toArg = runtimeCallInfo->GetCallArgRef(2);
    CHECK_NULL_RETURN(toArg->IsNumber(), panda::JSValueRef::Undefined(vm));
    adapter->NotifyItemMoved(fromArg->Uint32Value(vm), toArg->Uint32Value(vm));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue NodeAdapterBridge::GetAllItems(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    auto* adapter = GetNodeAdapter(runtimeCallInfo);
    CHECK_NULL_RETURN(adapter, panda::JSValueRef::Undefined(vm));
    const auto& items = adapter->GetAllItems();
    Local<panda::ArrayRef> array = panda::ArrayRef::New(vm, items.size());
    for (uint32_t i = 0; i < items.size(); i++) {
        panda::ArrayRef::SetValueAt(vm, array, i, FrameNodeBridge::MakeFrameNodeInfo(vm, items[i]));
    }
    return array;
}

ArkUINativeModuleValue NodeAdapterBridge::AttachNodeAdapter(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    auto* adapter = GetNodeAdapter(runtimeCallInfo);
    CHECK_NULL_RETURN(adapter, panda::BooleanRef::New(vm, false));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(1);
    CHECK_NULL_RETURN(!nodeArg.IsNull(), panda::BooleanRef::New(vm, false));
    auto* frameNode = reinterpret_cast<FrameNode*>(nodeArg->ToNativePointer(vm)->Value());
    CHECK_NULL_RETURN(frameNode, panda::BooleanRef::New(vm, false));
    auto* nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    bool ret = GetArkUIFullNodeAPI()->getNodeAdapterAPI()->attachHostNode(adapter->GetHandle(), nativeNode);
    return panda::BooleanRef::New(vm, ret);
}

ArkUINativeModuleValue NodeAdapterBridge::DetachNodeAdapter(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(!nodeArg.IsNull(), panda::JSValueRef::Undefined(vm));
    auto* nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUIFullNodeAPI()->getNodeAdapterAPI()->detachHostNode(nativeNode);
    GetArkUIFullNodeAPI()->getBasicAPI()->markDirty(nativeNode, ARKUI_DIRTY_FLAG_MEASURE_SELF_AND_PARENT);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue NodeAdapterBridge::FireArkUIObjectLifecycleCallback(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    auto defaultReturnValue = panda::JSValueRef::Undefined(vm);
    CHECK_NULL_RETURN(vm, defaultReturnValue);
    Local<JSValueRef> arg = runtimeCallInfo->GetCallArgRef(3);
    CHECK_NULL_RETURN(!arg.IsNull() && arg->IsNativePointer(vm), defaultReturnValue);
    auto* nativeNode = nodePtr(arg->ToNativePointer(vm)->Value());
    CHECK_NULL_RETURN(nativeNode, defaultReturnValue);
    auto* frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, defaultReturnValue);
    auto context = frameNode->GetContext();
    CHECK_NULL_RETURN(context, defaultReturnValue);
    void* data = static_cast<void*>(runtimeCallInfo);
    context->FireArkUIObjectLifecycleCallback(data);
    return defaultReturnValue;
}

ArkUINativeModuleValue NodeAdapterBridge::GetNodeType(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::StringRef::NewFromUtf8(vm, ""));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(!firstArg.IsNull(), panda::StringRef::NewFromUtf8(vm, ""));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto nodeType = GetArkUIFullNodeAPI()->getNodeAdapterAPI()->getNodeType(nativeNode);
    return panda::StringRef::NewFromUtf8(vm, nodeType);
}
} // namespace OHOS::Ace::NG
