/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#include "touch_event_handler.h"

#include <vector>
#include "base/log/log.h"
#include "core/event/touch_event.h"
#include "flutter/shell/platform/glfw/public/flutter_glfw.h"
#include "flutter/shell/platform/embedder/embedder.h"
#include "core/pipeline/layers/flutter_scene_builder.h"
#include "adapter/preview/entrance/event_dispatcher.h"

namespace OHOS::Ace::Platform {
namespace {

TouchPoint ConvertTouchPoint(flutter::PointerData* pointerItem)
{
    TouchPoint touchPoint;
    // just get the max of width and height
    touchPoint.size = pointerItem->size;
    touchPoint.id = pointerItem->device;
    touchPoint.force = pointerItem->pressure;
    touchPoint.x = pointerItem->physical_x;
    touchPoint.y = pointerItem->physical_y;
    touchPoint.screenX = pointerItem->physical_x;
    touchPoint.screenY = pointerItem->physical_y;
    return touchPoint;
}

void ConvertTouchEvent(const std::vector<uint8_t>& data, std::vector<TouchEvent>& events)
{
    constexpr int32_t DEFAULT_ACTION_ID = 0;
    const auto* origin = reinterpret_cast<const flutter::PointerData*>(data.data());
    size_t size = data.size() / sizeof(flutter::PointerData);
    auto current = const_cast<flutter::PointerData*>(origin);
    auto end = current + size;

    while (current < end) {
        std::chrono::microseconds micros(current->time_stamp);
        TimeStamp time(micros);
        TouchEvent point {
            static_cast<int32_t>(DEFAULT_ACTION_ID), static_cast<float>(current->physical_x),
            static_cast<float>(current->physical_y), static_cast<float>(current->physical_x),
            static_cast<float>(current->physical_y), TouchType::UNKNOWN, time, current->size,
            static_cast<float>(current->pressure), static_cast<int64_t>(current->device)
        };
        point.pointers.emplace_back(ConvertTouchPoint(current));
        switch (current->change) {
            case flutter::PointerData::Change::kCancel:
                point.type = TouchType::CANCEL;
                events.push_back(point);
                break;
            case flutter::PointerData::Change::kAdd:
            case flutter::PointerData::Change::kRemove:
            case flutter::PointerData::Change::kHover:
                break;
            case flutter::PointerData::Change::kDown:
                point.type = TouchType::DOWN;
                events.push_back(point);
                break;
            case flutter::PointerData::Change::kMove:
                point.type = TouchType::MOVE;
                events.push_back(point);
                break;
            case flutter::PointerData::Change::kUp:
                point.type = TouchType::UP;
                events.push_back(point);
                break;
        }
        current++;
    }
}

bool HandleTouchEvent(const std::vector<uint8_t>& data)
{
    std::vector<TouchEvent> touchEvents;
    ConvertTouchEvent(data, touchEvents);
    for (const auto& event : touchEvents) {
        EventDispatcher::GetInstance().DispatchTouchEvent(event);
    }
    return true;
}

}

void TouchEventHandler::InitialTouchEventCallback(const GlfwController &controller)
{
    LOGI("Initial callback function of touch event.");
    auto touchEventCallback = [](std::unique_ptr<flutter::PointerDataPacket>& packet)->bool {
        return packet && HandleTouchEvent(packet->data());
    };
    FlutterEngineRegisterHandleTouchEventCallback(std::move(touchEventCallback));
}

} // namespace OHOS::Ace::Platform
