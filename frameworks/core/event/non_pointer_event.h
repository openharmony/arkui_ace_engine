/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_EVENT_NON_POINTER_EVENT_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_EVENT_NON_POINTER_EVENT_H

#include "core/event/axis_event.h"

namespace OHOS::Ace {

struct NonPointerEvent : public PointerEvent {
    // When the key is held down for a long period of time, it will be accumulated once in a while.
    // Note that In the long press scene, you will receive a DOWN and an extra LONG_PRESS event. If you only want to
    // identify the click event, you can use CLICK event.
    int32_t repeatTime = 0;
    int64_t deviceId = 0;
    SourceType sourceType { SourceType::NONE };
    ~NonPointerEvent() = default;
    NonPointerEvent() {}

    NonPointerEvent& SetRepeatTime(int32_t repeatTime)
    {
        this->repeatTime = repeatTime;
        return *this;
    }

    NonPointerEvent& SetDeviceId(int64_t deviceId)
    {
        this->deviceId = deviceId;
        return *this;
    }

    NonPointerEvent& SetSourceType(SourceType sourceType)
    {
        this->sourceType = sourceType;
        return *this;
    }
};

} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_EVENT_NON_POINTER_EVENT_H
