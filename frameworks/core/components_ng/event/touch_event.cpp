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
    TouchEventInfo event("touchEvent");
    event.SetTimeStamp(point.time);
    event.SetPointerEvent(point.pointerEvent);
    TouchLocationInfo changedInfo("onTouch", point.id);
    auto localX = static_cast<float>(point.x - coordinateOffset_.GetX());
    auto localY = static_cast<float>(point.y - coordinateOffset_.GetY());
    changedInfo.SetLocalLocation(Offset(localX, localY));
    changedInfo.SetGlobalLocation(Offset(point.x, point.y));
    changedInfo.SetScreenLocation(Offset(point.screenX, point.screenY));
    changedInfo.SetTouchType(point.type);
    changedInfo.SetForce(point.force);
    if (point.tiltX.has_value()) {
        changedInfo.SetTiltX(point.tiltX.value());
    }
    if (point.tiltY.has_value()) {
        changedInfo.SetTiltY(point.tiltY.value());
    }
    changedInfo.SetSourceTool(point.sourceTool);
    event.AddChangedTouchLocationInfo(std::move(changedInfo));
    event.SetTarget(GetEventTarget().value_or(EventTarget()));

    // all fingers collection
    for (const auto& item : point.pointers) {
        float globalX = item.x;
        float globalY = item.y;
        float screenX = item.screenX;
        float screenY = item.screenY;
        auto localX = static_cast<float>(item.x - coordinateOffset_.GetX());
        auto localY = static_cast<float>(item.y - coordinateOffset_.GetY());
        TouchLocationInfo info("onTouch", item.id);
        info.SetGlobalLocation(Offset(globalX, globalY));
        info.SetLocalLocation(Offset(localX, localY));
        info.SetScreenLocation(Offset(screenX, screenY));
        info.SetTouchType(point.type);
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
    event.SetSourceDevice(point.sourceType);
    event.SetForce(point.force);
    if (point.tiltX.has_value()) {
        event.SetTiltX(point.tiltX.value());
    }
    if (point.tiltY.has_value()) {
        event.SetTiltY(point.tiltY.value());
    }
    event.SetSourceTool(point.sourceTool);
    for (auto& impl : touchEvents_) {
        if (impl) {
            (*impl)(event);
        }
    }
    if (userCallback_) {
        (*userCallback_)(event);
        if (event.IsStopPropagation()) {
            return false;
        }
    }
    return true;
}

} // namespace OHOS::Ace::NG