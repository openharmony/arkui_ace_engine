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

#include "core/components_ng/gestures/base_gesture_event.h"
#include "core/interfaces/native/implementation/base_event_peer.h"

struct BaseGestureEventPeer
    : public OHOS::Ace::NG::GeneratedModifier::SomeEventPeer<OHOS::Ace::BaseGestureEvent> {
    ~BaseGestureEventPeer() override = default;
};

namespace OHOS::Ace::NG::GeneratedModifier {
template<typename AceGestureInfo>
class SomeGestureEventPeer : public BaseGestureEventPeer {
public:
    ~SomeGestureEventPeer() override = default;

    AceGestureInfo* GetEventInfo()
    {
        CHECK_NULL_RETURN(eventInfo, nullptr);
        return &eventInfo.value();
    }

    void SetEventInfo(const AceGestureInfo& info)
    {
        eventInfo = info;
    }

    void SetFingerList(const std::list<FingerInfo>& fingerList)
    {
        fingerList_ = fingerList;
    }

private:
    std::optional<AceGestureInfo> eventInfo;
    std::list<FingerInfo> fingerList_;
};
} // namespace OHOS::Ace::NG::GeneratedModifier
