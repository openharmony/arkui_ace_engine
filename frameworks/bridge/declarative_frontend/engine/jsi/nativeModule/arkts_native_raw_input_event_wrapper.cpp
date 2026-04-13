/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_raw_input_event_wrapper.h"

#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_frame_node_bridge.h"

namespace OHOS::Ace::Framework {
namespace {
constexpr int32_t RAW_INPUT_EVENT_NATIVE_FIELD_INDEX = 0;
constexpr int32_t RAW_INPUT_EVENT_NATIVE_FIELD_COUNT = 1;

struct RawInputEventNativeData {
    bool isTouchEvent = false;
    bool isMouseEvent = false;
    bool isKeyEvent = false;
    std::unique_ptr<TouchEventInfo> touchInfo;
    std::unique_ptr<MouseInfo> mouseInfo;
    std::unique_ptr<KeyEventInfo> keyInfo;
};

void ReleaseRawInputEventNativeData(void* env, void* nativePtr, void* data)
{
    auto* nativeData = static_cast<RawInputEventNativeData*>(nativePtr);
    CHECK_NULL_VOID(nativeData);
    delete nativeData;
}

RawInputEventNativeData* GetRawInputEventNativeData(panda::JsiRuntimeCallInfo* runtimeCallInfo)
{
    auto* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, nullptr);
    auto thisArg = runtimeCallInfo->GetThisRef();
    if (thisArg.IsEmpty() || !thisArg->IsObject(vm)) {
        return nullptr;
    }
    auto thisObj = thisArg->ToObject(vm);
    return static_cast<RawInputEventNativeData*>(
        thisObj->GetNativePointerField(vm, RAW_INPUT_EVENT_NATIVE_FIELD_INDEX));
}

panda::Local<panda::JSValueRef> IsTouchEvent(panda::JsiRuntimeCallInfo* runtimeCallInfo)
{
    auto* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::BooleanRef::New(vm, false));
    auto* nativeData = GetRawInputEventNativeData(runtimeCallInfo);
    return panda::BooleanRef::New(vm, nativeData ? nativeData->isTouchEvent : false);
}

panda::Local<panda::JSValueRef> IsMouseEvent(panda::JsiRuntimeCallInfo* runtimeCallInfo)
{
    auto* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::BooleanRef::New(vm, false));
    auto* nativeData = GetRawInputEventNativeData(runtimeCallInfo);
    return panda::BooleanRef::New(vm, nativeData ? nativeData->isMouseEvent : false);
}

panda::Local<panda::JSValueRef> IsKeyEvent(panda::JsiRuntimeCallInfo* runtimeCallInfo)
{
    auto* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::BooleanRef::New(vm, false));
    auto* nativeData = GetRawInputEventNativeData(runtimeCallInfo);
    return panda::BooleanRef::New(vm, nativeData ? nativeData->isKeyEvent : false);
}

panda::Local<panda::JSValueRef> AsTouchEvent(panda::JsiRuntimeCallInfo* runtimeCallInfo)
{
    auto* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    auto* nativeData = GetRawInputEventNativeData(runtimeCallInfo);
    if (!nativeData || !nativeData->isTouchEvent || !nativeData->touchInfo) {
        return panda::JSValueRef::Null(vm);
    }
    auto touchInfoPtr = new TouchEventInfo(*nativeData->touchInfo);
    return NG::FrameNodeBridge::CreateTouchEventInfo(vm, touchInfoPtr);
}

panda::Local<panda::JSValueRef> AsMouseEvent(panda::JsiRuntimeCallInfo* runtimeCallInfo)
{
    auto* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    auto* nativeData = GetRawInputEventNativeData(runtimeCallInfo);
    if (!nativeData || !nativeData->isMouseEvent || !nativeData->mouseInfo) {
        return panda::JSValueRef::Null(vm);
    }
    auto mouseInfoPtr = new MouseInfo(*nativeData->mouseInfo);
    return NG::FrameNodeBridge::CreateMouseInfo(vm, mouseInfoPtr);
}

panda::Local<panda::JSValueRef> AsKeyEvent(panda::JsiRuntimeCallInfo* runtimeCallInfo)
{
    auto* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    auto* nativeData = GetRawInputEventNativeData(runtimeCallInfo);
    if (!nativeData || !nativeData->isKeyEvent || !nativeData->keyInfo) {
        return panda::JSValueRef::Null(vm);
    }
    auto* keyInfo = new KeyEventInfo(*nativeData->keyInfo);
    return NG::FrameNodeBridge::CreateKeyEventInfoObj(vm, keyInfo);
}

TouchEventInfo CreateMonitorTouchObject(const TouchEvent& event)
{
    TouchEventInfo info("touchEvent");
    info.SetTimeStamp(event.time);
    info.SetPointerEvent(event.GetTouchEventPointerEvent());
    info.SetDeviceId(event.deviceId);
    info.SetSourceDevice(event.sourceType);
    info.SetForce(event.force);
    if (event.tiltX.has_value()) {
        info.SetTiltX(event.tiltX.value());
    }
    if (event.tiltY.has_value()) {
        info.SetTiltY(event.tiltY.value());
    }
    if (event.rollAngle.has_value()) {
        info.SetRollAngle(event.rollAngle.value());
    }
    info.SetSourceTool(event.sourceTool);
    info.SetPressedKeyCodes(event.pressedKeyCodes_);
    info.SetOperatingHand(event.operatingHand);
    info.SetEventHandleId(event.eventHandleId);
    info.SetTargetDisplayId(event.targetDisplayId);
    return info;
}

TouchEventInfo CreateMonitorTouchEventInfo(const TouchEvent& event)
{
    TouchLocationInfo changedInfo("onTouch", event.GetOriginalReCovertId());
    changedInfo.SetGlobalLocation(Offset(event.x, event.y));
    changedInfo.SetScreenLocation(Offset(event.screenX, event.screenY));
    changedInfo.SetGlobalDisplayLocation(Offset(event.globalDisplayX, event.globalDisplayY));
    changedInfo.SetTouchType(event.type);
    changedInfo.SetForce(event.force);
    changedInfo.SetPressedTime(event.pressedTime);
    changedInfo.SetWidth(event.width);
    changedInfo.SetHeight(event.height);
    if (event.tiltX.has_value()) {
        changedInfo.SetTiltX(event.tiltX.value());
    }
    if (event.tiltY.has_value()) {
        changedInfo.SetTiltY(event.tiltY.value());
    }
    if (event.rollAngle.has_value()) {
        changedInfo.SetRollAngle(event.rollAngle.value());
    }
    changedInfo.SetSourceTool(event.sourceTool);
    changedInfo.SetOperatingHand(event.operatingHand);

    auto eventInfo = CreateMonitorTouchObject(event);
    eventInfo.AddChangedTouchLocationInfo(std::move(changedInfo));
    for (const auto& item : event.pointers) {
        TouchLocationInfo info("onTouch", item.GetOriginalReCovertId());
        info.SetGlobalLocation(Offset(item.x, item.y));
        info.SetScreenLocation(Offset(item.screenX, item.screenY));
        info.SetGlobalDisplayLocation(Offset(item.globalDisplayX, item.globalDisplayY));
        info.SetTouchType(event.type);
        info.SetForce(item.force);
        info.SetPressedTime(item.downTime);
        info.SetWidth(item.width);
        info.SetHeight(item.height);
        if (item.tiltX.has_value()) {
            info.SetTiltX(item.tiltX.value());
        }
        if (item.tiltY.has_value()) {
            info.SetTiltY(item.tiltY.value());
        }
        if (item.rollAngle.has_value()) {
            info.SetRollAngle(item.rollAngle.value());
        }
        info.SetSourceTool(item.sourceTool);
        info.SetOperatingHand(item.operatingHand);
        eventInfo.AddTouchLocationInfo(std::move(info));
    }
    return eventInfo;
}

MouseInfo CreateMonitorMouseInfo(const MouseEvent& event)
{
    MouseInfo info;
    info.SetPointerEvent(event.GetMouseEventPointerEvent());
    info.SetButton(event.button);
    info.SetAction(event.action);
    info.SetPullAction(event.pullAction);
    info.SetGlobalLocation(event.GetOffset());
    info.SetScreenLocation(event.GetScreenOffset());
    info.SetGlobalDisplayLocation(event.GetGlobalDisplayOffset());
    info.SetTimeStamp(event.time);
    info.SetDeviceId(event.deviceId);
    info.SetTargetDisplayId(event.targetDisplayId);
    info.SetSourceDevice(event.sourceType);
    info.SetSourceTool(event.sourceTool);
    info.SetPressedKeyCodes(event.pressedKeyCodes_);
    info.SetRawDeltaX(event.rawDeltaX);
    info.SetRawDeltaY(event.rawDeltaY);
    info.SetPressedButtons(event.pressedButtonsArray);
    info.SetIsRightButtonEventFromDoulbeTap(event.isRightButtonEventFromDoulbeTap);
    info.SetEventHandleId(event.eventHandleId);
    return info;
}
} // namespace

NG::ArkUINativeModuleValue ArkTSNativeRawInputEventWrapper::Create(const RawInputEventWrapper& wrapper, EcmaVM* vm)
{
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    auto* nativeData = new RawInputEventNativeData();
    nativeData->isTouchEvent = wrapper.IsTouchEvent();
    nativeData->isMouseEvent = wrapper.IsMouseEvent();
    nativeData->isKeyEvent = wrapper.IsKeyEvent();
    if (auto* touchEvent = wrapper.GetTouchEvent()) {
        nativeData->touchInfo = std::make_unique<TouchEventInfo>(CreateMonitorTouchEventInfo(*touchEvent));
    }
    if (auto* mouseEvent = wrapper.GetMouseEvent()) {
        nativeData->mouseInfo = std::make_unique<MouseInfo>(CreateMonitorMouseInfo(*mouseEvent));
    }
    if (auto* keyEvent = wrapper.GetKeyEvent()) {
        nativeData->keyInfo = std::make_unique<KeyEventInfo>(*keyEvent);
    }
    const char* keys[] = {
        "isTouchEvent",
        "isMouseEvent",
        "isKeyEvent",
        "asTouchEvent",
        "asMouseEvent",
        "asKeyEvent"
    };
    panda::Local<panda::JSValueRef> values[] = {
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), IsTouchEvent),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), IsMouseEvent),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), IsKeyEvent),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), AsTouchEvent),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), AsMouseEvent),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), AsKeyEvent)
    };
    auto eventObj = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(keys), keys, values);
    eventObj->SetNativePointerFieldCount(vm, RAW_INPUT_EVENT_NATIVE_FIELD_COUNT);
    eventObj->SetNativePointerField(vm, RAW_INPUT_EVENT_NATIVE_FIELD_INDEX, static_cast<void*>(nativeData),
        ReleaseRawInputEventNativeData, nullptr);
    return eventObj;
}
} // namespace OHOS::Ace::Framework
