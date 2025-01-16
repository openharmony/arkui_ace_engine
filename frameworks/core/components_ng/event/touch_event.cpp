/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include "core/components_ng/event/touch_event.h"

#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

bool TouchEventActuator::DispatchEvent(const TouchEvent& point)
{
    return true;
}

void TouchEventActuator::OnFlushTouchEventsBegin()
{
    isFlushTouchEventsEnd_ = false;
}

void TouchEventActuator::OnFlushTouchEventsEnd()
{
    isFlushTouchEventsEnd_ = true;
}

bool TouchEventActuator::HandleEvent(const TouchEvent& point)
{
    // if current node is forbidden by monopolize, upper nodes should not response either
    if (!ShouldResponse()) {
        return false;
    }
    return TriggerTouchCallBack(point);
}

bool TouchEventActuator::TriggerTouchCallBack(const TouchEvent& point)
{
    if (point.type == TouchType::DOWN &&
        firstInputTimeWithId_.find(point.id) == firstInputTimeWithId_.end()) {
        firstInputTimeWithId_[point.id] = point.time;
    }
    if (point.type == TouchType::UP &&
        firstInputTimeWithId_.find(point.id) != firstInputTimeWithId_.end()) {
        int64_t overTime = GetSysTimestamp();
        int64_t inputTime = static_cast<int64_t>(firstInputTimeWithId_[point.id].time_since_epoch().count());
        if (SystemProperties::GetTraceInputEventEnabled()) {
            ACE_SCOPED_TRACE("UserEvent InputTime:%lld OverTime:%lld InputType:TouchEvent",
                static_cast<long long>(inputTime), static_cast<long long>(overTime));
        }
        if (SystemProperties::GetTraceInputEventEnabled()) {
            ACE_SCOPED_TRACE("UserEvent InputTime:%lld AcceptTime:%lld InputType:TouchEvent",
                static_cast<long long>(inputTime), static_cast<long long>(overTime));
        }
        firstInputTimeWithId_.erase(point.id);
    }

    if (touchEvents_.empty() && !touchAfterEvents_ && !userCallback_ && !onTouchEventCallback_ &&
        !commonTouchEventCallback_) {
        return true;
    }
    TouchEvent lastPoint;
    if (point.isInterpolated) {
        lastPoint = point;
    } else {
        lastPoint = !point.history.empty() ? point.history.back() : point;
    }
    auto event = CreateTouchEventInfo(lastPoint);
    auto changedInfo = CreateChangedTouchInfo(lastPoint, point);
    event.AddChangedTouchLocationInfo(std::move(changedInfo));
    // all fingers collection
    for (const auto& item : lastPoint.pointers) {
        auto info = CreateTouchItemInfo(item, point, lastPoint.type);
        event.AddTouchLocationInfo(std::move(info));
    }
    for (const auto& item : point.history) {
        auto historyInfo = CreateHistoryTouchItemInfo(item, point);
        event.AddHistoryLocationInfo(std::move(historyInfo));
        event.AddHistoryPointerEvent(item.GetTouchEventPointerEvent());
    }
    TriggerCallBacks(event);
    return !event.IsStopPropagation();
}

bool TouchEventActuator::ShouldResponse()
{
    auto context = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_RETURN(context, true);

    auto eventManager = context->GetEventManager();
    CHECK_NULL_RETURN(eventManager, true);

    auto frameNode = GetAttachedNode();
    auto ctrl = eventManager->GetResponseCtrl();
    CHECK_NULL_RETURN(ctrl, true);
    if (!ctrl->ShouldResponse(frameNode)) {
        return false;
    }
    ctrl->TrySetFirstResponse(frameNode);
    return true;
}

TouchEventInfo TouchEventActuator::CreateTouchEventInfo(const TouchEvent& lastPoint)
{
    TouchEventInfo eventInfo("touchEvent");
    eventInfo.SetTimeStamp(lastPoint.time);
    eventInfo.SetPointerEvent(lastPoint.GetTouchEventPointerEvent());
    eventInfo.SetDeviceId(lastPoint.deviceId);
    eventInfo.SetTarget(GetEventTarget().value_or(EventTarget()));
    auto frameNode = GetAttachedNode().Upgrade();
    std::string patternName = "";
    if (frameNode) {
        patternName = frameNode->GetTag();
    }
    eventInfo.SetPatternName(patternName.c_str());
    eventInfo.SetSourceDevice(lastPoint.sourceType);
    eventInfo.SetForce(lastPoint.force);
    if (lastPoint.tiltX.has_value()) {
        eventInfo.SetTiltX(lastPoint.tiltX.value());
    }
    if (lastPoint.tiltY.has_value()) {
        eventInfo.SetTiltY(lastPoint.tiltY.value());
    }
    eventInfo.SetSourceTool(lastPoint.sourceTool);
    eventInfo.SetPressedKeyCodes(lastPoint.pressedKeyCodes_);
    if (isFlushTouchEventsEnd_) {
        // trigger callback of the last touch event during one vsync period
        eventInfo.SetTouchEventsEnd(true);
        isFlushTouchEventsEnd_ = false;
    }
    eventInfo.SetTargetDisplayId(lastPoint.targetDisplayId);
    return eventInfo;
}

TouchLocationInfo TouchEventActuator::CreateChangedTouchInfo(const TouchEvent& lastPoint, const TouchEvent& event)
{
    TouchLocationInfo changedInfo("onTouch", lastPoint.originalId);
    PointF lastLocalPoint(lastPoint.x, lastPoint.y);
    NGGestureRecognizer::Transform(lastLocalPoint, GetAttachedNode(), false, isPostEventResult_, event.postEventNodeId);
    auto localX = static_cast<float>(lastLocalPoint.GetX());
    auto localY = static_cast<float>(lastLocalPoint.GetY());
    changedInfo.SetLocalLocation(Offset(localX, localY));
    changedInfo.SetGlobalLocation(Offset(lastPoint.x, lastPoint.y));
    changedInfo.SetScreenLocation(Offset(lastPoint.screenX, lastPoint.screenY));
    changedInfo.SetTouchType(lastPoint.type);
    changedInfo.SetForce(lastPoint.force);
    if (lastPoint.tiltX.has_value()) {
        changedInfo.SetTiltX(lastPoint.tiltX.value());
    }
    if (lastPoint.tiltY.has_value()) {
        changedInfo.SetTiltY(lastPoint.tiltY.value());
    }
    changedInfo.SetSourceTool(lastPoint.sourceTool);
    return changedInfo;
}

TouchLocationInfo TouchEventActuator::CreateTouchItemInfo(
    const TouchPoint& pointItem, const TouchEvent& event, TouchType type)
{
    float globalX = pointItem.x;
    float globalY = pointItem.y;
    float screenX = pointItem.screenX;
    float screenY = pointItem.screenY;
    PointF localPoint(globalX, globalY);
    NGGestureRecognizer::Transform(localPoint, GetAttachedNode(), false, isPostEventResult_, event.postEventNodeId);
    auto localX = static_cast<float>(localPoint.GetX());
    auto localY = static_cast<float>(localPoint.GetY());
    TouchLocationInfo info("onTouch", pointItem.originalId);
    info.SetGlobalLocation(Offset(globalX, globalY));
    info.SetLocalLocation(Offset(localX, localY));
    info.SetScreenLocation(Offset(screenX, screenY));
    info.SetTouchType(type);
    info.SetForce(pointItem.force);
    info.SetPressedTime(pointItem.downTime);
    info.SetWidth(pointItem.width);
    info.SetHeight(pointItem.height);
    if (pointItem.tiltX.has_value()) {
        info.SetTiltX(pointItem.tiltX.value());
    }
    if (pointItem.tiltY.has_value()) {
        info.SetTiltY(pointItem.tiltY.value());
    }
    info.SetSourceTool(pointItem.sourceTool);
    return info;
}

TouchLocationInfo TouchEventActuator::CreateHistoryTouchItemInfo(const TouchEvent& eventItem, const TouchEvent& event)
{
    float globalX = eventItem.x;
    float globalY = eventItem.y;
    float screenX = eventItem.screenX;
    float screenY = eventItem.screenY;
    PointF localPoint(globalX, globalY);
    NGGestureRecognizer::Transform(localPoint, GetAttachedNode(), false, isPostEventResult_, event.postEventNodeId);
    auto localX = static_cast<float>(localPoint.GetX());
    auto localY = static_cast<float>(localPoint.GetY());
    TouchLocationInfo historyInfo("onTouch", eventItem.originalId);
    historyInfo.SetTimeStamp(eventItem.time);
    historyInfo.SetGlobalLocation(Offset(globalX, globalY));
    historyInfo.SetLocalLocation(Offset(localX, localY));
    historyInfo.SetScreenLocation(Offset(screenX, screenY));
    historyInfo.SetTouchType(eventItem.type);
    historyInfo.SetForce(eventItem.force);
    if (eventItem.tiltX.has_value()) {
        historyInfo.SetTiltX(eventItem.tiltX.value());
    }
    if (eventItem.tiltY.has_value()) {
        historyInfo.SetTiltY(eventItem.tiltY.value());
    }
    historyInfo.SetSourceTool(eventItem.sourceTool);
    return historyInfo;
}

void TouchEventActuator::TriggerCallBacks(TouchEventInfo& event)
{
    for (auto& impl : touchEvents_) {
        if (impl) {
            (*impl)(event);
        }
    }
    if (userCallback_) {
        // actuator->userCallback_ may be overwritten in its invoke so we copy it first
        auto userCallback = userCallback_;
        (*userCallback)(event);
    }
    if (touchAfterEvents_) {
        auto touchAfterEvents = touchAfterEvents_;
        (*touchAfterEvents)(event);
    }
    if (onTouchEventCallback_) {
        // actuator->onTouchEventCallback_ may be overwritten in its invoke so we copy it first
        auto onTouchEventCallback = onTouchEventCallback_;
        (*onTouchEventCallback)(event);
    }
    if (commonTouchEventCallback_) {
        // actuator->commonTouchEventCallback_ may be overwritten in its invoke so we copy it first
        auto commonTouchEventCallback = commonTouchEventCallback_;
        (*commonTouchEventCallback)(event);
    }
}

} // namespace OHOS::Ace::NG