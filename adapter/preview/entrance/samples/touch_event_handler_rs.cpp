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

#include <vector>

#include "touch_event_handler.h"

#include "adapter/preview/entrance/event_dispatcher.h"
#include "adapter/preview/external/multimodalinput/pointer_event.h"
#include "base/log/log.h"

using OHOS::MMI::PointerEvent;
using OHOS::MMI::SourceTool;
using OHOS::MMI::SourceType;
using OHOS::MMI::TouchPoint;
using OHOS::MMI::TouchType;

namespace OHOS::Ace::Platform {
namespace {
std::mutex lastMouseMutex;
double lastMouseX = 0;
double lastMouseY = 0;
bool lastMousePressed = false;
} // namespace

std::shared_ptr<PointerEvent> CreateMockTouchEvent(const TouchType& type)
{
    std::shared_ptr<PointerEvent> event = std::make_shared<PointerEvent>();
    std::lock_guard lock(lastMouseMutex);
    event->id = 1;
    event->x = lastMouseX;
    event->y = lastMouseY;
    event->screenX = 0;
    event->screenY = 0;
    event->type = type;
    event->time = std::chrono::high_resolution_clock::now();
    event->size = sizeof(PointerEvent);
    event->force = 0;
    event->deviceId = 0;
    event->sourceType = SourceType::TOUCH;
    event->pointers = {};
    return event;
}

void HandleMouseButton(int button, bool pressed, int mods)
{
    {
        std::lock_guard lock(lastMouseMutex);
        lastMousePressed = pressed;
    }

    auto event = CreateMockTouchEvent(pressed ? TouchType::DOWN : TouchType::UP);
    EventDispatcher::GetInstance().DispatchTouchEvent(event);
}

void HandleCursorPos(double x, double y)
{
    {
        std::lock_guard lock(lastMouseMutex);
        lastMouseX = x;
        lastMouseY = y;
    }

    if (lastMousePressed) {
        auto event = CreateMockTouchEvent(TouchType::MOVE);
        EventDispatcher::GetInstance().DispatchTouchEvent(event);
    }
}

void TouchEventHandler::InitialTouchEventCallback(const GlfwController& controller)
{
    controller->OnMouseButton(HandleMouseButton);
    controller->OnCursorPos(HandleCursorPos);
}
} // namespace OHOS::Ace::Platform
