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
#include "core/components_ng/gestures/recognizers/gesture_recognizer.h"

namespace OHOS::Ace::NG {

bool TouchEventActuator::DispatchEvent(const TouchEvent& point)
{
    return true;
}

bool TouchEventActuator::HandleEvent(const TouchEvent& point)
{
    return TriggerTouchCallBack(point);
}

bool TouchEventActuator::TriggerTouchCallBack(const TouchEvent& point)
{
    if (touchEvents_.empty() && !userCallback_) {
        return true;
    }
    auto lastPoint = point.history.size() > 0 ? point.history.back() : point;
    TouchEventInfo event("touchEvent");
    event.SetTimeStamp(lastPoint.time);
    event.SetPointerEvent(lastPoint.pointerEvent);
    TouchLocationInfo changedInfo("onTouch", lastPoint.id);
    PointF lastLocalPoint(lastPoint.x, lastPoint.y);
    NGGestureRecognizer::Transform(lastLocalPoint, GetNodeId());
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
    event.AddChangedTouchLocationInfo(std::move(changedInfo));
    event.SetTarget(GetEventTarget().value_or(EventTarget()));

    // all fingers collection
    for (const auto& item : lastPoint.pointers) {
        float globalX = item.x;
        float globalY = item.y;
        float screenX = item.screenX;
        float screenY = item.screenY;
        PointF localPoint(globalX, globalY);
        NGGestureRecognizer::Transform(localPoint, GetNodeId());
        auto localX = static_cast<float>(localPoint.GetX());
        auto localY = static_cast<float>(localPoint.GetY());
        TouchLocationInfo info("onTouch", item.id);
        info.SetGlobalLocation(Offset(globalX, globalY));
        info.SetLocalLocation(Offset(localX, localY));
        info.SetScreenLocation(Offset(screenX, screenY));
        info.SetTouchType(lastPoint.type);
        info.SetForce(item.force);
        if (item.tiltX.has_value()) {
            info.SetTiltX(item.tiltX.value());
        }
        if (item.tiltY.has_value()) {
            info.SetTiltY(item.tiltY.value());
        }
        info.SetSourceTool(item.sourceTool);
        event.AddTouchLocationInfo(std::move(info));
    }
    event.SetSourceDevice(lastPoint.sourceType);
    event.SetForce(lastPoint.force);
    for (const auto& item : point.history) {
        float globalX = item.x;
        float globalY = item.y;
        float screenX = item.screenX;
        float screenY = item.screenY;
        PointF localPoint(globalX, globalY);
        NGGestureRecognizer::Transform(localPoint, GetNodeId());
        auto localX = static_cast<float>(localPoint.GetX());
        auto localY = static_cast<float>(localPoint.GetY());
        TouchLocationInfo historyInfo("onTouch", item.id);
        historyInfo.SetTimeStamp(item.time);
        historyInfo.SetGlobalLocation(Offset(globalX, globalY));
        historyInfo.SetLocalLocation(Offset(localX, localY));
        historyInfo.SetScreenLocation(Offset(screenX, screenY));
        historyInfo.SetTouchType(item.type);
        historyInfo.SetForce(item.force);
        if (item.tiltX.has_value()) {
            historyInfo.SetTiltX(item.tiltX.value());
        }
        if (item.tiltY.has_value()) {
            historyInfo.SetTiltY(item.tiltY.value());
        }
        historyInfo.SetSourceTool(item.sourceTool);
        event.AddHistoryLocationInfo(std::move(historyInfo));
    }
    if (lastPoint.tiltX.has_value()) {
        event.SetTiltX(lastPoint.tiltX.value());
    }
    if (lastPoint.tiltY.has_value()) {
        event.SetTiltY(lastPoint.tiltY.value());
    }
    event.SetSourceTool(lastPoint.sourceTool);
    for (auto& impl : touchEvents_) {
        if (impl) {
            (*impl)(event);
        }
    }
    if (userCallback_) {
        // actuator->userCallback_ may be overwritten in its invoke so we copy it first
        auto userCallback = userCallback_;
        (*userCallback)(event);
        if (event.IsStopPropagation()) {
            return false;
        }
    }
    return true;
}

} // namespace OHOS::Ace::NG