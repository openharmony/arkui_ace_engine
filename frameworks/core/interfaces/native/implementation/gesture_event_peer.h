/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once

#include "core/gestures/gesture_event.h"
#include "core/interfaces/native/implementation/base_gesture_event_peer.h"

struct GestureEventPeer : public BaseGestureEventPeer {
    ~GestureEventPeer() override = default;

    using GestureEventInfoPtr = std::shared_ptr<OHOS::Ace::GestureEvent>;

    const GestureEventInfoPtr& GetGestureEventInfo() const
    {
        return eventInfo;
    }

    void SetGestureEventInfo(const GestureEventInfoPtr& info)
    {
        SetBaseInfo(info);
        eventInfo = info;
    }

private:
    GestureEventInfoPtr eventInfo;
};
