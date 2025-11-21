/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_INCLUDE_EVENT_AXIS_EVENT_H
#define FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_INCLUDE_EVENT_AXIS_EVENT_H

#include <list>
#include <utility>

#include "ui/base/geometry/offset.h"
#include "ui/base/ace_type.h"
#include "ui/event/event_constants.h"
#include "ui/event/ace_events.h"

namespace OHOS::Ace {
struct UIInputEvent {
    virtual ~UIInputEvent() = default;
    TimeStamp time;
    ConvertInfo convertInfo = { UIInputEventType::NONE, UIInputEventType::NONE };
    UIInputEventType eventType = UIInputEventType::NONE;
};

struct PointerEvent : public UIInputEvent {
    virtual ~PointerEvent() = default;
    explicit PointerEvent(float x = {}, float y = {}, float screenX = {}, float screenY = {},
        double globalDisplayX = {}, double globalDisplayY = {}, TimeStamp time = {})
        : globalDisplayX(globalDisplayX), globalDisplayY(globalDisplayY), x(x), y(y), screenX(screenX), screenY(screenY)
    {
        this->time = time;
    }
    double globalDisplayX = {};
    double globalDisplayY = {};
    float x = {};
    float y = {};
    float screenX = {};
    float screenY = {};
    // ID of the node to which this event is being explicitly posted (not necessarily the original target)
    int32_t postEventNodeId = {};
    bool passThrough = {};
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_INCLUDE_EVENT_AXIS_EVENT_H
