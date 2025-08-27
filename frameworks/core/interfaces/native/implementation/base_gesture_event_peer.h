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

struct BaseGestureEventPeer : public BaseEventPeer {
protected:
    BaseGestureEventPeer() = default;
    ~BaseGestureEventPeer() override = default;
    friend OHOS::Ace::NG::PeerUtils;

public:
    virtual OHOS::Ace::BaseGestureEvent* GetBaseGestureInfo() = 0;
};

namespace OHOS::Ace::NG::GeneratedModifier {
template<typename AceGestureInfo,
    std::enable_if_t<std::is_base_of_v<BaseEventInfo, AceGestureInfo>, bool> = true,
    std::enable_if_t<std::is_base_of_v<BaseGestureEvent, AceGestureInfo>, bool> = true
>
class SomeGestureEventPeer : public BaseGestureEventPeer {
protected:
    SomeGestureEventPeer() = default;
    ~SomeGestureEventPeer() override = default;

public:
    BaseEventInfo* GetBaseInfo() override
    {
        return GetEventInfo();
    }

    BaseGestureEvent* GetBaseGestureInfo() override
    {
        return GetEventInfo();
    }

    AceGestureInfo* GetEventInfo()
    {
        return eventInfo.get();
    }

    void SetEventInfo(const std::shared_ptr<AceGestureInfo>& info)
    {
        eventInfo = info;
    }

private:
    std::shared_ptr<AceGestureInfo> eventInfo;
};

struct BaseGestureEventPeerImpl : public SomeGestureEventPeer<BaseGestureEvent> {
protected:
    BaseGestureEventPeerImpl() = default;
    ~BaseGestureEventPeerImpl() override = default;
    friend PeerUtils;
};
} // namespace OHOS::Ace::NG::GeneratedModifier
