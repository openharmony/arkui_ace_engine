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

#include "touch_event_handler.h"

#include <vector>
#include "base/log/log.h"
#include "core/event/touch_event.h"
#include "adapter/preview/entrance/event_dispatcher.h"

namespace OHOS::Ace::Platform {
namespace {
std::mutex lastMouseMutex;
double lastMouseX = 0;
double lastMouseY = 0;
bool lastMousePressed = false;
} // namespace

struct TouchEvent CreateMockTouchEvent(const TouchType &type)
{
    std::lock_guard lock(lastMouseMutex);
    return {
        .id = 1,
        .x = lastMouseX,
        .y = lastMouseY,
        .screenX = 0,
        .screenY = 0,
        .type = type,
        .time = std::chrono::high_resolution_clock::now(),
        .size = 96.0,
        .force = 0,
        .deviceId = 0,
        .sourceType = SourceType::TOUCH,
        .pointers = {},
    };
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

void HandleCursorPos(double x, double y) {
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

void TouchEventHandler::InitialTouchEventCallback(const GlfwController &controller)
{
    controller->OnMouseButton(HandleMouseButton);
    controller->OnCursorPos(HandleCursorPos);
}

} // namespace OHOS::Ace::Platform
