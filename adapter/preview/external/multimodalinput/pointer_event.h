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

#ifndef FOUNDATION_ACE_ADAPTER_PREVIEW_EXTERNAL_MULTIMODALINPUT_POINTER_EVENT_H
#define FOUNDATION_ACE_ADAPTER_PREVIEW_EXTERNAL_MULTIMODALINPUT_POINTER_EVENT_H

#include <optional>

#include "adapter/preview/external/multimodalinput/common_type.h"

namespace OHOS {
namespace MMI {

enum class TouchType : size_t {
    DOWN = 0,
    UP,
    MOVE,
    CANCEL,
    PULL_DOWN,
    PULL_UP,
    PULL_MOVE,
    PULL_IN_WINDOW,
    PULL_OUT_WINDOW,
    UNKNOWN,
};

struct TouchPoint final {
    int32_t id = 0;
    float x = 0.0f;
    float y = 0.0f;
    float screenX = 0.0f;
    float screenY = 0.0f;
    TimeStamp downTime;
    double size = 0.0;
    float force = 0.0f;
    std::optional<float> tiltX;
    std::optional<float> tiltY;
    SourceTool sourceTool = SourceTool::UNKNOWN;
    bool isPressed = false;
};

class PointerEvent {
public:
    PointerEvent() = default;
    ~PointerEvent() = default;

public:
    int32_t id = 0;
    float x = 0.0f;
    float y = 0.0f;
    float screenX = 0.0f;
    float screenY = 0.0f;
    TouchType type = TouchType::UNKNOWN;
    TouchType pullType = TouchType::UNKNOWN;
    TimeStamp time;
    double size = 0.0;
    float force = 0.0f;
    std::optional<float> tiltX;
    std::optional<float> tiltY;
    int64_t deviceId = 0;
    SourceType sourceType = SourceType::NONE;
    SourceTool sourceTool = SourceTool::UNKNOWN;
    std::vector<TouchPoint> pointers;
};

} // namespace MMI
} // namespace OHOS
#endif // FOUNDATION_ACE_ADAPTER_PREVIEW_EXTERNAL_MULTIMODALINPUT_POINTER_EVENT_H
