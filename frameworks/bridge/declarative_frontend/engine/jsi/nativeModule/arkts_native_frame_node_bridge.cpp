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
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_frame_node_bridge.h"

#include "jsnapi_expo.h"

#include "core/components_ng/base/view_abstract.h"

namespace OHOS::Ace::NG {
ArkUINodeHandle FrameNodeBridge::GetFrameNode(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, nullptr);
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(!firstArg.IsNull(), nullptr);
    auto* nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    return nativeNode;
}

Local<panda::ObjectRef> FrameNodeBridge::CreateEventTargetObject(EcmaVM* vm, const BaseEventInfo& info)
{
    auto target = panda::ObjectRef::New(vm);
    auto area = panda::ObjectRef::New(vm);
    auto offset = panda::ObjectRef::New(vm);
    auto globalOffset = panda::ObjectRef::New(vm);
    const auto& localOffset = info.GetTarget().area.GetOffset();
    const auto& origin = info.GetTarget().origin;
    offset->Set(
        vm, panda::StringRef::NewFromUtf8(vm, "x"), panda::NumberRef::New(vm, localOffset.GetX().ConvertToVp()));
    offset->Set(
        vm, panda::StringRef::NewFromUtf8(vm, "y"), panda::NumberRef::New(vm, localOffset.GetY().ConvertToVp()));
    globalOffset->Set(vm, panda::StringRef::NewFromUtf8(vm, "x"),
        panda::NumberRef::New(vm, origin.GetX().ConvertToVp() + localOffset.GetX().ConvertToVp()));
    globalOffset->Set(vm, panda::StringRef::NewFromUtf8(vm, "y"),
        panda::NumberRef::New(vm, origin.GetY().ConvertToVp() + localOffset.GetY().ConvertToVp()));
    area->Set(vm, panda::StringRef::NewFromUtf8(vm, "position"), offset);
    area->Set(vm, panda::StringRef::NewFromUtf8(vm, "globalPosition"), globalOffset);
    area->Set(vm, panda::StringRef::NewFromUtf8(vm, "width"),
        panda::NumberRef::New(vm, info.GetTarget().area.GetWidth().ConvertToVp()));
    area->Set(vm, panda::StringRef::NewFromUtf8(vm, "height"),
        panda::NumberRef::New(vm, info.GetTarget().area.GetHeight().ConvertToVp()));
    target->Set(vm, panda::StringRef::NewFromUtf8(vm, "area"), area);
    return target;
}

Local<panda::ObjectRef> FrameNodeBridge::CreateTouchInfo(
    EcmaVM* vm, const TouchLocationInfo& touchInfo, TouchEventInfo& info)
{
    auto touchInfoObj = panda::ObjectRef::New(vm);
    touchInfoObj->SetNativePointerFieldCount(vm, 1);
    const Offset& globalOffset = touchInfo.GetGlobalLocation();
    const Offset& localOffset = touchInfo.GetLocalLocation();
    const Offset& screenOffset = touchInfo.GetScreenLocation();
    touchInfoObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "type"),
        panda::NumberRef::New(vm, static_cast<int32_t>(touchInfo.GetTouchType())));
    touchInfoObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "id"), panda::NumberRef::New(vm, touchInfo.GetFingerId()));
    touchInfoObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "displayX"),
        panda::NumberRef::New(vm, PipelineBase::Px2VpWithCurrentDensity(screenOffset.GetX())));
    touchInfoObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "displayY"),
        panda::NumberRef::New(vm, PipelineBase::Px2VpWithCurrentDensity(screenOffset.GetY())));
    touchInfoObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "windowX"),
        panda::NumberRef::New(vm, PipelineBase::Px2VpWithCurrentDensity(globalOffset.GetX())));
    touchInfoObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "windowY"),
        panda::NumberRef::New(vm, PipelineBase::Px2VpWithCurrentDensity(globalOffset.GetY())));
    touchInfoObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "screenX"),
        panda::NumberRef::New(vm, PipelineBase::Px2VpWithCurrentDensity(globalOffset.GetX())));
    touchInfoObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "screenY"),
        panda::NumberRef::New(vm, PipelineBase::Px2VpWithCurrentDensity(globalOffset.GetY())));
    touchInfoObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "x"),
        panda::NumberRef::New(vm, PipelineBase::Px2VpWithCurrentDensity(localOffset.GetX())));
    touchInfoObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "y"),
        panda::NumberRef::New(vm, PipelineBase::Px2VpWithCurrentDensity(localOffset.GetY())));
    touchInfoObj->SetNativePointerField(vm, 0, static_cast<void*>(&info));
    return touchInfoObj;
}

ArkUINativeModuleValue FrameNodeBridge::IsModifiable(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::BooleanRef::New(vm, false));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(!firstArg.IsNull(), panda::BooleanRef::New(vm, false));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto result = GetArkUINodeModifiers()->getFrameNodeModifier()->isModifiable(nativeNode);
    return panda::BooleanRef::New(vm, result);
}
ArkUINativeModuleValue FrameNodeBridge::AppendChild(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::BooleanRef::New(vm, true));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(!firstArg.IsNull(), panda::BooleanRef::New(vm, true));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    auto childNativeNode = nodePtr(secondArg->ToNativePointer(vm)->Value());
    auto result = GetArkUINodeModifiers()->getFrameNodeModifier()->appendChild(nativeNode, childNativeNode);
    return panda::BooleanRef::New(vm, result);
}
ArkUINativeModuleValue FrameNodeBridge::InsertChildAfter(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::BooleanRef::New(vm, true));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(!firstArg.IsNull(), panda::BooleanRef::New(vm, true));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    auto child = nodePtr(secondArg->ToNativePointer(vm)->Value());
    Local<JSValueRef> thirdArg = runtimeCallInfo->GetCallArgRef(2); // 2 : index to get the insert node
    if (thirdArg.IsNull()) {
        GetArkUINodeModifiers()->getFrameNodeModifier()->insertChildAfter(nativeNode, child, nullptr);
        return panda::JSValueRef::Undefined(vm);
    }
    auto sibling = nodePtr(thirdArg->ToNativePointer(vm)->Value());
    auto result = GetArkUINodeModifiers()->getFrameNodeModifier()->insertChildAfter(nativeNode, child, sibling);
    return panda::BooleanRef::New(vm, result);
}
ArkUINativeModuleValue FrameNodeBridge::RemoveChild(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(!firstArg.IsNull(), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    auto childNativeNode = nodePtr(secondArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getFrameNodeModifier()->removeChild(nativeNode, childNativeNode);
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue FrameNodeBridge::ClearChildren(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(!firstArg.IsNull(), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getFrameNodeModifier()->clearChildren(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue FrameNodeBridge::GetChildrenCount(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NumberRef::New(vm, 0));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(!firstArg.IsNull(), panda::NumberRef::New(vm, 0));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto number = GetArkUINodeModifiers()->getFrameNodeModifier()->getChildrenCount(nativeNode);
    return panda::NumberRef::New(vm, number);
}
ArkUINativeModuleValue FrameNodeBridge::GetChild(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(!firstArg.IsNull(), panda::NativePointerRef::New(vm, nullptr));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    int index = secondArg->ToNumber(vm)->Value();
    auto nodePtr = GetArkUINodeModifiers()->getFrameNodeModifier()->getChild(nativeNode, index);
    return panda::NativePointerRef::New(vm, nodePtr);
}
ArkUINativeModuleValue FrameNodeBridge::GetFirst(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(!firstArg.IsNull(), panda::NativePointerRef::New(vm, nullptr));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto nodePtr = GetArkUINodeModifiers()->getFrameNodeModifier()->getFirst(nativeNode);
    return panda::NativePointerRef::New(vm, nodePtr);
}
ArkUINativeModuleValue FrameNodeBridge::GetNextSibling(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(!firstArg.IsNull(), panda::NativePointerRef::New(vm, nullptr));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto nodePtr = GetArkUINodeModifiers()->getFrameNodeModifier()->getNextSibling(nativeNode);
    return panda::NativePointerRef::New(vm, nodePtr);
}
ArkUINativeModuleValue FrameNodeBridge::GetPreviousSibling(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(!firstArg.IsNull(), panda::NativePointerRef::New(vm, nullptr));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto nodePtr = GetArkUINodeModifiers()->getFrameNodeModifier()->getPreviousSibling(nativeNode);
    return panda::NativePointerRef::New(vm, nodePtr);
}
ArkUINativeModuleValue FrameNodeBridge::GetParent(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(!firstArg.IsNull(), panda::NativePointerRef::New(vm, nullptr));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto nodePtr = GetArkUINodeModifiers()->getFrameNodeModifier()->getParent(nativeNode);
    return panda::NativePointerRef::New(vm, nodePtr);
}
ArkUINativeModuleValue FrameNodeBridge::GetIdByNodePtr(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NumberRef::New(vm, -1));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(!firstArg.IsNull(), panda::NumberRef::New(vm, -1));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto nodeId = GetArkUINodeModifiers()->getFrameNodeModifier()->getIdByNodePtr(nativeNode);
    return panda::NumberRef::New(vm, nodeId);
}
ArkUINativeModuleValue FrameNodeBridge::GetPositionToParent(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(!firstArg.IsNull(), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    Local<Framework::ArrayRef> valueArray = Framework::ArrayRef::New(vm, 2);
    auto position = GetArkUINodeModifiers()->getFrameNodeModifier()->getPositionToParent(nativeNode);
    CHECK_NULL_RETURN(position, panda::JSValueRef::Undefined(vm));
    Framework::ArrayRef::SetValueAt(vm, valueArray, 0, panda::NumberRef::New(vm, position[0]));
    Framework::ArrayRef::SetValueAt(vm, valueArray, 1, panda::NumberRef::New(vm, position[1]));
    return valueArray;
}
ArkUINativeModuleValue FrameNodeBridge::GetPositionToWindow(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(!firstArg.IsNull(), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    Local<Framework::ArrayRef> valueArray = Framework::ArrayRef::New(vm, 2);
    auto position = GetArkUINodeModifiers()->getFrameNodeModifier()->getPositionToWindow(nativeNode);
    CHECK_NULL_RETURN(position, panda::JSValueRef::Undefined(vm));
    Framework::ArrayRef::SetValueAt(vm, valueArray, 0, panda::NumberRef::New(vm, position[0]));
    Framework::ArrayRef::SetValueAt(vm, valueArray, 1, panda::NumberRef::New(vm, position[1]));
    return valueArray;
}

Local<panda::ObjectRef> FrameNodeBridge::CreateGestureEventInfo(EcmaVM* vm, GestureEvent& info)
{
    auto obj = panda::ObjectRef::New(vm);
    const Offset& globalOffset = info.GetGlobalLocation();
    const Offset& localOffset = info.GetLocalLocation();
    const Offset& screenOffset = info.GetScreenLocation();
    obj->Set(vm, panda::StringRef::NewFromUtf8(vm, "displayX"),
        panda::NumberRef::New(vm, PipelineBase::Px2VpWithCurrentDensity(screenOffset.GetX())));
    obj->Set(vm, panda::StringRef::NewFromUtf8(vm, "displayY"),
        panda::NumberRef::New(vm, PipelineBase::Px2VpWithCurrentDensity(screenOffset.GetY())));
    obj->Set(vm, panda::StringRef::NewFromUtf8(vm, "windowX"),
        panda::NumberRef::New(vm, PipelineBase::Px2VpWithCurrentDensity(globalOffset.GetX())));
    obj->Set(vm, panda::StringRef::NewFromUtf8(vm, "windowY"),
        panda::NumberRef::New(vm, PipelineBase::Px2VpWithCurrentDensity(globalOffset.GetY())));
    obj->Set(vm, panda::StringRef::NewFromUtf8(vm, "screenX"),
        panda::NumberRef::New(vm, PipelineBase::Px2VpWithCurrentDensity(globalOffset.GetX())));
    obj->Set(vm, panda::StringRef::NewFromUtf8(vm, "screenY"),
        panda::NumberRef::New(vm, PipelineBase::Px2VpWithCurrentDensity(globalOffset.GetY())));
    obj->Set(vm, panda::StringRef::NewFromUtf8(vm, "x"),
        panda::NumberRef::New(vm, PipelineBase::Px2VpWithCurrentDensity(localOffset.GetX())));
    obj->Set(vm, panda::StringRef::NewFromUtf8(vm, "y"),
        panda::NumberRef::New(vm, PipelineBase::Px2VpWithCurrentDensity(localOffset.GetY())));
    obj->Set(vm, panda::StringRef::NewFromUtf8(vm, "timestamp"),
        panda::NumberRef::New(vm, static_cast<double>(info.GetTimeStamp().time_since_epoch().count())));
    obj->Set(vm, panda::StringRef::NewFromUtf8(vm, "source"),
        panda::NumberRef::New(vm, static_cast<int32_t>(info.GetSourceDevice())));
    obj->Set(vm, panda::StringRef::NewFromUtf8(vm, "pressure"), panda::NumberRef::New(vm, info.GetForce()));
    if (info.GetTiltX().has_value()) {
        obj->Set(vm, panda::StringRef::NewFromUtf8(vm, "tiltX"),
            panda::NumberRef::New(vm, static_cast<int32_t>(info.GetTiltX().value())));
    }
    if (info.GetTiltY().has_value()) {
        obj->Set(vm, panda::StringRef::NewFromUtf8(vm, "tiltY"),
            panda::NumberRef::New(vm, static_cast<int32_t>(info.GetTiltY().value())));
    }
    obj->Set(vm, panda::StringRef::NewFromUtf8(vm, "sourceTool"),
        panda::NumberRef::New(vm, static_cast<int32_t>(static_cast<int32_t>(info.GetSourceTool()))));
    auto target = CreateEventTargetObject(vm, info);
    obj->Set(vm, panda::StringRef::NewFromUtf8(vm, "target"), target);

    return obj;
}

ArkUINativeModuleValue FrameNodeBridge::SetOnClick(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    auto* nativeNode = GetFrameNode(runtimeCallInfo);
    CHECK_NULL_RETURN(nativeNode, panda::JSValueRef::Undefined(vm));
    auto* frameNode = reinterpret_cast<NG::FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> secondeArg = runtimeCallInfo->GetCallArgRef(1);
    if (secondeArg->IsUndefined()) {
        NG::ViewAbstract::ClearJSFrameNodeOnClick(frameNode);
        return panda::JSValueRef::Undefined(vm);
    }
    CHECK_NULL_RETURN(secondeArg->IsFunction(), panda::JSValueRef::Undefined(vm));
    auto obj = secondeArg->ToObject(vm);
    auto containerId = Container::CurrentId();
    panda::Local<panda::FunctionRef> func = obj;
    auto onClick = [vm, func = panda::CopyableGlobal(vm, func), node = AceType::WeakClaim(frameNode), containerId](
                       GestureEvent& info) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        ContainerScope scope(containerId);
        PipelineContext::SetCallBackNode(node);
        auto obj = CreateGestureEventInfo(vm, info);
        panda::Local<panda::JSValueRef> params[1] = { obj };
        func->Call(vm, func.ToLocal(), params, 1);
    };
    NG::ViewAbstract::SetJSFrameNodeOnClick(frameNode, std::move(onClick));
    return panda::JSValueRef::Undefined(vm);
}

Local<panda::ObjectRef> FrameNodeBridge::CreateTouchEventInfo(EcmaVM* vm, TouchEventInfo& info)
{
    auto eventObj = panda::ObjectRef::New(vm);
    eventObj->SetNativePointerFieldCount(vm, 1);
    auto touchArr = panda::ArrayRef::New(vm);
    auto changeTouchArr = panda::ArrayRef::New(vm);
    eventObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "source"),
        panda::NumberRef::New(vm, static_cast<int32_t>(info.GetSourceDevice())));
    eventObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "timestamp"),
        panda::NumberRef::New(vm, static_cast<double>(info.GetTimeStamp().time_since_epoch().count())));
    auto target = CreateEventTargetObject(vm, info);
    eventObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "target"), target);
    eventObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "pressure"), panda::NumberRef::New(vm, info.GetForce()));
    if (info.GetTiltX().has_value()) {
        eventObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "tiltX"),
            panda::NumberRef::New(vm, static_cast<int32_t>(info.GetTiltX().value())));
    }
    if (info.GetTiltY().has_value()) {
        eventObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "tiltY"),
            panda::NumberRef::New(vm, static_cast<int32_t>(info.GetTiltY().value())));
    }
    eventObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "sourceTool"),
        panda::NumberRef::New(vm, static_cast<int32_t>(static_cast<int32_t>(info.GetSourceTool()))));

    const std::list<TouchLocationInfo>& touchList = info.GetTouches();
    uint32_t idx = 0;
    for (const TouchLocationInfo& location : touchList) {
        auto element = CreateTouchInfo(vm, location, info);
        panda::ArrayRef::SetValueAt(vm, touchArr, idx++, element);
    }
    eventObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "touches"), touchArr);

    idx = 0; // reset index counter
    const std::list<TouchLocationInfo>& changeTouch = info.GetChangedTouches();
    for (const TouchLocationInfo& change : changeTouch) {
        auto element = CreateTouchInfo(vm, change, info);
        panda::ArrayRef::SetValueAt(vm, changeTouchArr, idx++, element);
    }
    if (changeTouch.size() > 0) {
        eventObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "type"),
            panda::NumberRef::New(vm, static_cast<int32_t>(changeTouch.front().GetTouchType())));
    }
    eventObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "changedTouches"), changeTouchArr);
    eventObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "stopPropagation"),
        panda::FunctionRef::New(vm, Framework::JsStopPropagation));
    eventObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "getHistoricalPoints"),
        panda::FunctionRef::New(vm, Framework::JsGetHistoricalPoints));
    eventObj->SetNativePointerField(vm, 0, static_cast<void*>(&info));

    return eventObj;
}

ArkUINativeModuleValue FrameNodeBridge::SetOnTouch(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    auto* nativeNode = GetFrameNode(runtimeCallInfo);
    CHECK_NULL_RETURN(nativeNode, panda::JSValueRef::Undefined(vm));
    auto* frameNode = reinterpret_cast<NG::FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> secondeArg = runtimeCallInfo->GetCallArgRef(1);
    if (secondeArg->IsUndefined()) {
        NG::ViewAbstract::ClearJSFrameNodeOnTouch(frameNode);
        return panda::JSValueRef::Undefined(vm);
    }
    CHECK_NULL_RETURN(secondeArg->IsFunction(), panda::JSValueRef::Undefined(vm));
    auto obj = secondeArg->ToObject(vm);
    auto containerId = Container::CurrentId();
    panda::Local<panda::FunctionRef> func = obj;
    auto onTouch = [vm, func = panda::CopyableGlobal(vm, func), node = AceType::WeakClaim(frameNode), containerId](
                       TouchEventInfo& info) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        ContainerScope scope(containerId);
        PipelineContext::SetCallBackNode(node);
        auto eventObj = CreateTouchEventInfo(vm, info);
        panda::Local<panda::JSValueRef> params[1] = { eventObj };
        func->Call(vm, func.ToLocal(), params, 1);
    };
    NG::ViewAbstract::SetJSFrameNodeOnTouch(frameNode, std::move(onTouch));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue FrameNodeBridge::SetOnAppear(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    auto* nativeNode = GetFrameNode(runtimeCallInfo);
    CHECK_NULL_RETURN(nativeNode, panda::JSValueRef::Undefined(vm));
    auto* frameNode = reinterpret_cast<NG::FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> secondeArg = runtimeCallInfo->GetCallArgRef(1);
    if (secondeArg->IsUndefined()) {
        NG::ViewAbstract::ClearJSFrameNodeOnAppear(frameNode);
        return panda::JSValueRef::Undefined(vm);
    }
    CHECK_NULL_RETURN(secondeArg->IsFunction(), panda::JSValueRef::Undefined(vm));
    auto obj = secondeArg->ToObject(vm);
    auto containerId = Container::CurrentId();
    panda::Local<panda::FunctionRef> func = obj;
    auto onAppear = [vm, func = panda::CopyableGlobal(vm, func), node = AceType::WeakClaim(frameNode), containerId]() {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        ContainerScope scope(containerId);
        PipelineContext::SetCallBackNode(node);
        func->Call(vm, func.ToLocal(), nullptr, 0);
    };
    NG::ViewAbstract::SetJSFrameNodeOnAppear(frameNode, std::move(onAppear));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue FrameNodeBridge::SetOnDisappear(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    auto* nativeNode = GetFrameNode(runtimeCallInfo);
    CHECK_NULL_RETURN(nativeNode, panda::JSValueRef::Undefined(vm));
    auto* frameNode = reinterpret_cast<NG::FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> secondeArg = runtimeCallInfo->GetCallArgRef(1);
    if (secondeArg->IsUndefined()) {
        NG::ViewAbstract::ClearJSFrameNodeOnDisappear(frameNode);
        return panda::JSValueRef::Undefined(vm);
    }
    CHECK_NULL_RETURN(secondeArg->IsFunction(), panda::JSValueRef::Undefined(vm));
    auto obj = secondeArg->ToObject(vm);
    auto containerId = Container::CurrentId();
    panda::Local<panda::FunctionRef> func = obj;
    auto onDisappear = [vm, func = panda::CopyableGlobal(vm, func), node = AceType::WeakClaim(frameNode),
                           containerId]() {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        ContainerScope scope(containerId);
        PipelineContext::SetCallBackNode(node);
        func->Call(vm, func.ToLocal(), nullptr, 0);
    };
    NG::ViewAbstract::SetJSFrameNodeOnDisappear(frameNode, std::move(onDisappear));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue FrameNodeBridge::SetOnKeyEvent(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    auto* nativeNode = GetFrameNode(runtimeCallInfo);
    CHECK_NULL_RETURN(nativeNode, panda::JSValueRef::Undefined(vm));
    auto* frameNode = reinterpret_cast<NG::FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> secondeArg = runtimeCallInfo->GetCallArgRef(1);
    if (secondeArg->IsUndefined()) {
        NG::ViewAbstract::ClearJSFrameNodeOnKeyCallback(frameNode);
        return panda::JSValueRef::Undefined(vm);
    }
    CHECK_NULL_RETURN(secondeArg->IsFunction(), panda::JSValueRef::Undefined(vm));
    auto obj = secondeArg->ToObject(vm);
    auto containerId = Container::CurrentId();
    panda::Local<panda::FunctionRef> func = obj;
    auto onKeyEvent = [vm, func = panda::CopyableGlobal(vm, func), node = AceType::WeakClaim(frameNode), containerId](
                          KeyEventInfo& info) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        ContainerScope scope(containerId);
        PipelineContext::SetCallBackNode(node);
        auto obj = panda::ObjectRef::New(vm);
        obj->SetNativePointerFieldCount(vm, 1);
        obj->Set(vm, panda::StringRef::NewFromUtf8(vm, "type"),
            panda::NumberRef::New(vm, static_cast<int32_t>(info.GetKeyType())));
        obj->Set(vm, panda::StringRef::NewFromUtf8(vm, "keyCode"),
            panda::NumberRef::New(vm, static_cast<int32_t>(info.GetKeyCode())));
        obj->Set(
            vm, panda::StringRef::NewFromUtf8(vm, "keyText"), panda::StringRef::NewFromUtf8(vm, info.GetKeyText()));
        obj->Set(vm, panda::StringRef::NewFromUtf8(vm, "keySource"),
            panda::NumberRef::New(vm, static_cast<int32_t>(info.GetKeySource())));
        obj->Set(vm, panda::StringRef::NewFromUtf8(vm, "deviceId"), panda::NumberRef::New(vm, info.GetDeviceId()));
        obj->Set(vm, panda::StringRef::NewFromUtf8(vm, "metaKey"), panda::NumberRef::New(vm, info.GetMetaKey()));
        obj->Set(vm, panda::StringRef::NewFromUtf8(vm, "timestamp"),
            panda::NumberRef::New(vm, static_cast<double>(info.GetTimeStamp().time_since_epoch().count())));
        obj->Set(vm, panda::StringRef::NewFromUtf8(vm, "stopPropagation"),
            panda::FunctionRef::New(vm, Framework::JsStopPropagation));
        obj->Set(vm, panda::StringRef::NewFromUtf8(vm, "intentionCode"),
            panda::NumberRef::New(vm, static_cast<int32_t>(info.GetKeyIntention())));
        obj->SetNativePointerField(vm, 0, static_cast<void*>(&info));
        panda::Local<panda::JSValueRef> params[] = { obj };
        func->Call(vm, func.ToLocal(), params, 1);
    };

    NG::ViewAbstract::SetJSFrameNodeOnKeyCallback(frameNode, std::move(onKeyEvent));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue FrameNodeBridge::SetOnFocus(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    auto* nativeNode = GetFrameNode(runtimeCallInfo);
    CHECK_NULL_RETURN(nativeNode, panda::JSValueRef::Undefined(vm));
    auto* frameNode = reinterpret_cast<NG::FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> secondeArg = runtimeCallInfo->GetCallArgRef(1);
    if (secondeArg->IsUndefined()) {
        NG::ViewAbstract::ClearJSFrameNodeOnFocusCallback(frameNode);
        return panda::JSValueRef::Undefined(vm);
    }
    CHECK_NULL_RETURN(secondeArg->IsFunction(), panda::JSValueRef::Undefined(vm));
    auto obj = secondeArg->ToObject(vm);
    auto containerId = Container::CurrentId();
    panda::Local<panda::FunctionRef> func = obj;
    auto onFocus = [vm, func = panda::CopyableGlobal(vm, func), node = AceType::WeakClaim(frameNode), containerId]() {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        ContainerScope scope(containerId);
        PipelineContext::SetCallBackNode(node);
        func->Call(vm, func.ToLocal(), nullptr, 0);
    };
    NG::ViewAbstract::SetJSFrameNodeOnFocusCallback(frameNode, std::move(onFocus));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue FrameNodeBridge::SetOnBlur(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    auto* nativeNode = GetFrameNode(runtimeCallInfo);
    CHECK_NULL_RETURN(nativeNode, panda::JSValueRef::Undefined(vm));
    auto* frameNode = reinterpret_cast<NG::FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> secondeArg = runtimeCallInfo->GetCallArgRef(1);
    if (secondeArg->IsUndefined()) {
        NG::ViewAbstract::ClearJSFrameNodeOnBlurCallback(frameNode);
        return panda::JSValueRef::Undefined(vm);
    }
    CHECK_NULL_RETURN(secondeArg->IsFunction(), panda::JSValueRef::Undefined(vm));
    auto obj = secondeArg->ToObject(vm);
    auto containerId = Container::CurrentId();
    panda::Local<panda::FunctionRef> func = obj;
    auto onBlur = [vm, func = panda::CopyableGlobal(vm, func), node = AceType::WeakClaim(frameNode), containerId]() {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        ContainerScope scope(containerId);
        PipelineContext::SetCallBackNode(node);
        func->Call(vm, func.ToLocal(), nullptr, 0);
    };
    NG::ViewAbstract::SetJSFrameNodeOnBlurCallback(frameNode, std::move(onBlur));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue FrameNodeBridge::SetOnHover(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    auto* nativeNode = GetFrameNode(runtimeCallInfo);
    CHECK_NULL_RETURN(nativeNode, panda::JSValueRef::Undefined(vm));
    auto* frameNode = reinterpret_cast<NG::FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> secondeArg = runtimeCallInfo->GetCallArgRef(1);
    if (secondeArg->IsUndefined()) {
        NG::ViewAbstract::ClearJSFrameNodeOnHover(frameNode);
        return panda::JSValueRef::Undefined(vm);
    }
    CHECK_NULL_RETURN(secondeArg->IsFunction(), panda::JSValueRef::Undefined(vm));
    auto obj = secondeArg->ToObject(vm);
    auto containerId = Container::CurrentId();
    panda::Local<panda::FunctionRef> func = obj;
    auto onHover = [vm, func = panda::CopyableGlobal(vm, func), node = AceType::WeakClaim(frameNode), containerId](
                       bool isHover, HoverInfo& hoverInfo) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        ContainerScope scope(containerId);
        PipelineContext::SetCallBackNode(node);
        auto isHoverParam = panda::BooleanRef::New(vm, isHover);
        auto obj = panda::ObjectRef::New(vm);
        obj->SetNativePointerFieldCount(vm, 1);
        obj->Set(vm, panda::StringRef::NewFromUtf8(vm, "stopPropagation"),
            panda::FunctionRef::New(vm, Framework::JsStopPropagation));
        obj->Set(vm, panda::StringRef::NewFromUtf8(vm, "timestamp"),
            panda::NumberRef::New(vm, static_cast<double>(hoverInfo.GetTimeStamp().time_since_epoch().count())));
        obj->Set(vm, panda::StringRef::NewFromUtf8(vm, "source"),
            panda::NumberRef::New(vm, static_cast<int32_t>(hoverInfo.GetSourceDevice())));
        auto target = CreateEventTargetObject(vm, hoverInfo);
        obj->Set(vm, panda::StringRef::NewFromUtf8(vm, "target"), target);
        obj->SetNativePointerField(vm, 0, static_cast<void*>(&hoverInfo));
        panda::Local<panda::JSValueRef> params[] = { isHoverParam, obj };
        func->Call(vm, func.ToLocal(), params, sizeof(params) / sizeof(params[0]));
    };
    NG::ViewAbstract::SetJSFrameNodeOnHover(frameNode, std::move(onHover));
    return panda::JSValueRef::Undefined(vm);
}

Local<panda::ObjectRef> FrameNodeBridge::CreateMouseInfo(EcmaVM* vm, MouseInfo& info)
{
    auto obj = panda::ObjectRef::New(vm);
    obj->SetNativePointerFieldCount(vm, 1);
    obj->Set(vm, panda::StringRef::NewFromUtf8(vm, "button"),
        panda::NumberRef::New(vm, static_cast<int32_t>(info.GetButton())));
    obj->Set(vm, panda::StringRef::NewFromUtf8(vm, "action"),
        panda::NumberRef::New(vm, static_cast<int32_t>(info.GetAction())));

    const Offset& globalOffset = info.GetGlobalLocation();
    const Offset& localOffset = info.GetLocalLocation();
    const Offset& screenOffset = info.GetScreenLocation();
    obj->Set(vm, panda::StringRef::NewFromUtf8(vm, "displayX"),
        panda::NumberRef::New(vm, PipelineBase::Px2VpWithCurrentDensity(screenOffset.GetX())));
    obj->Set(vm, panda::StringRef::NewFromUtf8(vm, "displayY"),
        panda::NumberRef::New(vm, PipelineBase::Px2VpWithCurrentDensity(screenOffset.GetY())));
    obj->Set(vm, panda::StringRef::NewFromUtf8(vm, "windowX"),
        panda::NumberRef::New(vm, PipelineBase::Px2VpWithCurrentDensity(globalOffset.GetX())));
    obj->Set(vm, panda::StringRef::NewFromUtf8(vm, "windowY"),
        panda::NumberRef::New(vm, PipelineBase::Px2VpWithCurrentDensity(globalOffset.GetY())));
    obj->Set(vm, panda::StringRef::NewFromUtf8(vm, "screenX"),
        panda::NumberRef::New(vm, PipelineBase::Px2VpWithCurrentDensity(globalOffset.GetX())));
    obj->Set(vm, panda::StringRef::NewFromUtf8(vm, "screenY"),
        panda::NumberRef::New(vm, PipelineBase::Px2VpWithCurrentDensity(globalOffset.GetY())));
    obj->Set(vm, panda::StringRef::NewFromUtf8(vm, "x"),
        panda::NumberRef::New(vm, PipelineBase::Px2VpWithCurrentDensity(localOffset.GetX())));
    obj->Set(vm, panda::StringRef::NewFromUtf8(vm, "y"),
        panda::NumberRef::New(vm, PipelineBase::Px2VpWithCurrentDensity(localOffset.GetY())));
    obj->Set(vm, panda::StringRef::NewFromUtf8(vm, "timestamp"),
        panda::NumberRef::New(vm, static_cast<double>(info.GetTimeStamp().time_since_epoch().count())));
    obj->Set(vm, panda::StringRef::NewFromUtf8(vm, "stopPropagation"),
        panda::FunctionRef::New(vm, Framework::JsStopPropagation));
    obj->Set(vm, panda::StringRef::NewFromUtf8(vm, "source"),
        panda::NumberRef::New(vm, static_cast<int32_t>(info.GetSourceDevice())));
    obj->Set(vm, panda::StringRef::NewFromUtf8(vm, "pressure"), panda::NumberRef::New(vm, info.GetForce()));
    if (info.GetTiltX().has_value()) {
        obj->Set(vm, panda::StringRef::NewFromUtf8(vm, "tiltX"),
            panda::NumberRef::New(vm, static_cast<int32_t>(info.GetTiltX().value())));
    }
    if (info.GetTiltY().has_value()) {
        obj->Set(vm, panda::StringRef::NewFromUtf8(vm, "tiltY"),
            panda::NumberRef::New(vm, static_cast<int32_t>(info.GetTiltY().value())));
    }
    obj->Set(vm, panda::StringRef::NewFromUtf8(vm, "sourceTool"),
        panda::NumberRef::New(vm, static_cast<int32_t>(static_cast<int32_t>(info.GetSourceTool()))));
    auto target = CreateEventTargetObject(vm, info);
    obj->Set(vm, panda::StringRef::NewFromUtf8(vm, "target"), target);
    obj->SetNativePointerField(vm, 0, static_cast<void*>(&info));
    return obj;
}

ArkUINativeModuleValue FrameNodeBridge::SetOnMouse(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    auto* nativeNode = GetFrameNode(runtimeCallInfo);
    CHECK_NULL_RETURN(nativeNode, panda::JSValueRef::Undefined(vm));
    auto* frameNode = reinterpret_cast<NG::FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> secondeArg = runtimeCallInfo->GetCallArgRef(1);
    if (secondeArg->IsUndefined()) {
        NG::ViewAbstract::ClearJSFrameNodeOnMouse(frameNode);
        return panda::JSValueRef::Undefined(vm);
    }
    CHECK_NULL_RETURN(secondeArg->IsFunction(), panda::JSValueRef::Undefined(vm));
    auto obj = secondeArg->ToObject(vm);
    auto containerId = Container::CurrentId();
    panda::Local<panda::FunctionRef> func = obj;
    auto onMouse = [vm, func = panda::CopyableGlobal(vm, func), node = AceType::WeakClaim(frameNode), containerId](
                       MouseInfo& info) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        ContainerScope scope(containerId);
        PipelineContext::SetCallBackNode(node);
        auto obj = CreateMouseInfo(vm, info);
        panda::Local<panda::JSValueRef> params[1] = { obj };
        func->Call(vm, func.ToLocal(), params, 1);
    };
    NG::ViewAbstract::SetJSFrameNodeOnMouse(frameNode, std::move(onMouse));
    return panda::JSValueRef::Undefined(vm);
}
} // namespace OHOS::Ace::NG
