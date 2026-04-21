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

#include "core/event/touch_event.h"

namespace OHOS::Ace {
void TouchPoint::CovertId()
{
    return;
}

int32_t TouchPoint::GetOriginalReCovertId() const
{
    return originalId;
}

TouchEvent& TouchEvent::SetId(int32_t value)
{
    id = value;
    return *this;
}

TouchEvent& TouchEvent::SetX(float value)
{
    x = value;
    return *this;
}

TouchEvent& TouchEvent::SetY(float value)
{
    y = value;
    return *this;
}

TouchEvent& TouchEvent::SetScreenX(float value)
{
    screenX = value;
    return *this;
}

TouchEvent& TouchEvent::SetScreenY(float value)
{
    screenY = value;
    return *this;
}

TouchEvent& TouchEvent::SetGlobalDisplayX(double value)
{
    globalDisplayX = value;
    return *this;
}

TouchEvent& TouchEvent::SetGlobalDisplayY(double value)
{
    globalDisplayY = value;
    return *this;
}

TouchEvent& TouchEvent::SetTime(TimeStamp value)
{
    time = value;
    return *this;
}

TimeStamp TouchEvent::GetTimeStamp() const
{
    return time;
}

TouchEvent& TouchEvent::SetType(TouchType value)
{
    type = value;
    return *this;
}

TouchEvent& TouchEvent::SetSize(double value)
{
    size = value;
    return *this;
}

TouchEvent& TouchEvent::SetDeviceId(int64_t value)
{
    deviceId = value;
    return *this;
}

TouchEvent& TouchEvent::SetTargetDisplayId(int32_t value)
{
    targetDisplayId = value;
    return *this;
}

TouchEvent& TouchEvent::SetSourceType(SourceType value)
{
    sourceType = value;
    return *this;
}

TouchEvent& TouchEvent::SetSourceTool(SourceTool value)
{
    sourceTool = value;
    return *this;
}

TouchEvent& TouchEvent::SetTouchEventId(int32_t value)
{
    touchEventId = value;
    return *this;
}

TouchEvent& TouchEvent::SetEventHandleId(int32_t value)
{
    eventHandleId = value;
    return *this;
}

TouchEvent& TouchEvent::SetPointerEvent(std::shared_ptr<const MMI::PointerEvent> value)
{
    pointerEvent = std::move(value);
    return *this;
}

TouchEvent& TouchEvent::SetOriginalId(int32_t value)
{
    originalId = value;
    return *this;
}

TouchEvent& TouchEvent::SetIsInjected(bool value)
{
    isInjected = value;
    return *this;
}

TouchEvent& TouchEvent::SetPressedTime(TimeStamp value)
{
    pressedTime = value;
    return *this;
}

TouchEvent& TouchEvent::SetPressedKeyCodes(const std::vector<KeyCode>& value)
{
    pressedKeyCodes_ = value;
    return *this;
}

std::shared_ptr<MMI::PointerEvent> TouchEvent::GetTouchEventPointerEvent() const
{
    return std::const_pointer_cast<MMI::PointerEvent>(pointerEvent);
}

bool TouchEvent::IsPenHoverEvent() const
{
    return sourceTool == SourceTool::PEN &&
           (type == TouchType::LEVITATE_IN_WINDOW || type == TouchType::LEVITATE_MOVE ||
               type == TouchType::LEVITATE_OUT_WINDOW);
}

TouchEvent TouchEvent::CreateScalePoint(float scale) const
{
    (void)scale;
    return *this;
}

TouchEvent TouchEvent::UpdateScalePoint(float scale, float offsetX, float offsetY, int32_t pointId) const
{
    (void)scale;
    (void)offsetX;
    (void)offsetY;
    (void)pointId;
    return *this;
}

Offset TouchEvent::GetOffset() const
{
    return Offset(x, y);
}

Offset TouchEvent::GetScreenOffset() const
{
    return Offset(screenX, screenY);
}

Offset TouchEvent::GetGlobalDisplayOffset() const
{
    return Offset(globalDisplayX, globalDisplayY);
}

int32_t TouchEvent::GetOriginalReCovertId() const
{
    return originalId;
}

void TouchEvent::CovertId()
{
    return;
}

void TouchCallBackInfo::SetScreenX(float value)
{
    screenX_ = value;
}

float TouchCallBackInfo::GetScreenX() const
{
    return screenX_;
}

void TouchCallBackInfo::SetScreenY(float value)
{
    screenY_ = value;
}

float TouchCallBackInfo::GetScreenY() const
{
    return screenY_;
}

void TouchCallBackInfo::SetGlobalDisplayX(double value)
{
    globalDisplayX_ = value;
}

double TouchCallBackInfo::GetGlobalDisplayX() const
{
    return globalDisplayX_;
}

void TouchCallBackInfo::SetGlobalDisplayY(double value)
{
    globalDisplayY_ = value;
}

double TouchCallBackInfo::GetGlobalDisplayY() const
{
    return globalDisplayY_;
}

void TouchCallBackInfo::SetLocalX(float value)
{
    localX_ = value;
}

float TouchCallBackInfo::GetLocalX() const
{
    return localX_;
}

void TouchCallBackInfo::SetLocalY(float value)
{
    localY_ = value;
}

float TouchCallBackInfo::GetLocalY() const
{
    return localY_;
}

void TouchCallBackInfo::SetTouchType(TouchType value)
{
    touchType_ = value;
}

TouchType TouchCallBackInfo::GetTouchType() const
{
    return touchType_;
}

void TouchCallBackInfo::SetTimeStamp(const TimeStamp& value)
{
    time_ = value;
}

TimeStamp TouchCallBackInfo::GetTimeStamp() const
{
    return time_;
}

TouchLocationInfo& TouchLocationInfo::SetGlobalLocation(const Offset& value)
{
    globalLocation_ = value;
    return *this;
}

TouchLocationInfo& TouchLocationInfo::SetLocalLocation(const Offset& value)
{
    localLocation_ = value;
    return *this;
}

TouchLocationInfo& TouchLocationInfo::SetScreenLocation(const Offset& value)
{
    screenLocation_ = value;
    return *this;
}

TouchLocationInfo& TouchLocationInfo::SetGlobalDisplayLocation(const Offset& value)
{
    globalDisplayLocation_ = value;
    return *this;
}

void TouchLocationInfo::SetSize(double value)
{
    size_ = value;
}

double TouchLocationInfo::GetSize() const
{
    return size_;
}

void TouchLocationInfo::SetTouchDeviceId(int64_t value)
{
    touchDeviceId_ = value;
}

int64_t TouchLocationInfo::GetTouchDeviceId() const
{
    return touchDeviceId_;
}

void TouchLocationInfo::SetTouchType(TouchType value)
{
    touchType_ = value;
}

void TouchLocationInfo::SetPressedTime(TimeStamp value)
{
    pressedTime_ = value;
}

TimeStamp TouchLocationInfo::GetPressedTime() const
{
    return pressedTime_;
}

void TouchLocationInfo::SetWidth(int32_t value)
{
    width_ = value;
}

int32_t TouchLocationInfo::GetWidth() const
{
    return width_;
}

void TouchLocationInfo::SetHeight(int32_t value)
{
    height_ = value;
}

int32_t TouchLocationInfo::GetHeight() const
{
    return height_;
}

void TouchEventTarget::SetTouchRestrict(const TouchRestrict& touchRestrict)
{
    touchRestrict_ = touchRestrict;
}

void TouchEventTarget::SetGetEventTargetImpl(const GetEventTargetImpl& getEventTargetImpl)
{
    getEventTargetImpl_ = getEventTargetImpl;
}

std::optional<EventTarget> TouchEventTarget::GetEventTarget() const
{
    if (getEventTargetImpl_) {
        return getEventTargetImpl_();
    }
    return std::nullopt;
}

void TouchEventTarget::SetCoordinateOffset(const Offset& coordinateOffset)
{
    coordinateOffset_ = coordinateOffset;
}

const Offset& TouchEventTarget::GetCoordinateOffset() const
{
    return coordinateOffset_;
}

void TouchEventTarget::SetSubPipelineGlobalOffset(const Offset& subPipelineGlobalOffset, float viewScale)
{
    subPipelineGlobalOffset_ = subPipelineGlobalOffset;
    viewScale_ = viewScale;
}

bool TouchEventTarget::DispatchMultiContainerEvent(const TouchEvent& point)
{
    return DispatchEvent(point);
}

bool TouchEventTarget::HandleMultiContainerEvent(const TouchEvent& point)
{
    return HandleEvent(point);
}

std::string TouchEventTarget::GetNodeName() const
{
    return nodeName_;
}

void TouchEventTarget::SetNodeId(int id)
{
    if (nodeId_ != -1) {
        return;
    }
    nodeId_ = id;
}

int32_t TouchEventTarget::GetNodeId() const
{
    return nodeId_;
}

void TouchEventTarget::AttachFrameNode(const WeakPtr<NG::FrameNode>& node)
{
    node_ = node;
}

WeakPtr<NG::FrameNode> TouchEventTarget::GetAttachedNode() const
{
    return node_;
}

RefPtr<GestureSnapshot> TouchEventTarget::Dump() const
{
    return nullptr;
}

void TouchEventTarget::SetTargetComponent(const RefPtr<NG::TargetComponent>& targetComponent)
{
    if (!targetComponent_) {
        targetComponent_ = targetComponent;
    }
}

RefPtr<NG::TargetComponent> TouchEventTarget::GetTargetComponent()
{
    return targetComponent_;
}

void TouchEventTarget::SetIsPostEventResult(bool isPostEventResult)
{
    isPostEventResult_ = isPostEventResult;
}

bool TouchEventTarget::IsPostEventResult() const
{
    return isPostEventResult_;
}

void TouchEventInfo::AddTouchLocationInfo(TouchLocationInfo&& info)
{
    touches_.emplace_back(info);
}

void TouchEventInfo::AddChangedTouchLocationInfo(TouchLocationInfo&& info)
{
    changedTouches_.emplace_back(info);
}

void TouchEventInfo::AddHistoryLocationInfo(TouchLocationInfo&& info)
{
    history_.emplace_back(std::move(info));
}

const std::list<TouchLocationInfo>& TouchEventInfo::GetHistory() const
{
    return history_;
}

void TouchEventInfo::AddHistoryPointerEvent(const std::shared_ptr<MMI::PointerEvent>& info)
{
    historyPointerEvent_.emplace_back(info);
}

const std::list<std::shared_ptr<MMI::PointerEvent>>& TouchEventInfo::GetHistoryPointerEvent() const
{
    return historyPointerEvent_;
}

void TouchEventInfo::SetPointerEvent(const std::shared_ptr<MMI::PointerEvent>& pointerEvent)
{
    pointerEvent_ = pointerEvent;
}

const std::shared_ptr<MMI::PointerEvent>& TouchEventInfo::GetPointerEvent() const
{
    return pointerEvent_;
}

void TouchEventInfo::SetTouchEventsEnd(bool isTouchEventsEnd)
{
    isTouchEventsEnd_ = isTouchEventsEnd;
}

bool TouchEventInfo::GetTouchEventsEnd() const
{
    return isTouchEventsEnd_;
}

TouchEvent TouchEventInfo::ConvertToTouchEvent() const
{
    TouchEvent touchEvent;
    if (!changedTouches_.empty()) {
        touchEvent.x = static_cast<float>(changedTouches_.front().GetGlobalLocation().GetX());
        touchEvent.y = static_cast<float>(changedTouches_.front().GetGlobalLocation().GetY());
        touchEvent.screenX = static_cast<float>(changedTouches_.front().GetScreenLocation().GetX());
        touchEvent.screenY = static_cast<float>(changedTouches_.front().GetScreenLocation().GetY());
        touchEvent.localX = static_cast<float>(changedTouches_.front().GetLocalLocation().GetX());
        touchEvent.localY = static_cast<float>(changedTouches_.front().GetLocalLocation().GetY());
        touchEvent.globalDisplayX = static_cast<double>(changedTouches_.front().GetGlobalDisplayLocation().GetX());
        touchEvent.globalDisplayY = static_cast<double>(changedTouches_.front().GetGlobalDisplayLocation().GetY());
        touchEvent.id = changedTouches_.front().GetFingerId();
        touchEvent.type = changedTouches_.front().GetTouchType();
        touchEvent.width = changedTouches_.front().GetWidth();
        touchEvent.height = changedTouches_.front().GetHeight();
        touchEvent.pressedTime = changedTouches_.front().GetPressedTime();
        touchEvent.deviceId = changedTouches_.front().GetTouchDeviceId();
    }
    return touchEvent;
}

const std::string& NativeEmbeadTouchInfo::GetEmbedId() const
{
    return embedId_;
}

const TouchEventInfo& NativeEmbeadTouchInfo::GetTouchEventInfo() const
{
    return touchEvent_;
}

const RefPtr<GestureEventResult>& NativeEmbeadTouchInfo::GetResult() const
{
    return result_;
}

void GestureSnapshot::AddProcedure(const std::string& procedure, const std::string& extraInfo,
    const std::string& state, const std::string& disposal, int64_t timestamp)
{
    stateHistory.emplace_back(StateRecord(procedure, extraInfo, state, disposal, timestamp));
}

bool GestureSnapshot::CheckNeedAddMove(const std::string& state, const std::string& disposal)
{
    return stateHistory.empty() || stateHistory.back().state != state || stateHistory.back().disposal != disposal;
}

std::string GestureSnapshot::TransTouchType(TouchType type)
{
    switch (type) {
        case TouchType::DOWN:
            return "TouchDown";
        case TouchType::MOVE:
            return "TouchMove";
        case TouchType::UP:
            return "TouchUp";
        case TouchType::CANCEL:
            return "TouchCancel";
        default:
            return "TouchUnknown";
    }
}

std::string GestureSnapshot::TransAxisType(AxisAction action)
{
    switch (action) {
        case AxisAction::BEGIN:
            return "AxisBegin";
        case AxisAction::UPDATE:
            return "AxisUpdate";
        case AxisAction::END:
            return "AxisEnd";
        case AxisAction::CANCEL:
            return "AxisCancel";
        default:
            return "AxisUnknown";
    }
}
// Intentionally empty: use real touch_event.cpp implementations in this build.
} // namespace OHOS::Ace

namespace OHOS::Ace::Platform {
Offset GetTouchEventOriginOffset(const TouchEvent& event)
{
    return Offset();
}

TimeStamp GetTouchEventOriginTimeStamp(const TouchEvent& event)
{
    return event.time;
}

void UpdatePressedKeyCodes(std::vector<KeyCode>& pressedKeyCodes) {}
} // namespace OHOS::Ace::Platform
