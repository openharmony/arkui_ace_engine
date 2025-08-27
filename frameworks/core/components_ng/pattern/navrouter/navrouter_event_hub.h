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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_NAVROUTER_NAVROUTER_EVENT_HUB_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_NAVROUTER_NAVROUTER_EVENT_HUB_H

#include "base/memory/ace_type.h"
#include "core/components_ng/event/event_hub.h"
#include "core/components_ng/event/gesture_event_hub.h"

namespace OHOS::Ace::NG {

using OnStateChangeEvent = std::function<void(bool)>;
using OnDestinationChangeEvent = std::function<void()>;

class NavRouterEventHub : public EventHub {
    DECLARE_ACE_TYPE(NavRouterEventHub, EventHub);
public:
    void SetOnStateChange(OnStateChangeEvent&& changeEvent)
    {
        onStateChangeEvent_ = changeEvent;
    }

    const OnStateChangeEvent& GetOnStateChange()
    {
        return onStateChangeEvent_;
    }

    void FireChangeEvent(bool isActivated) const
    {
        if (onStateChangeEvent_) {
            onStateChangeEvent_(isActivated);
        }
    }

    void SetOnDestinationChange(OnDestinationChangeEvent&& onDestinationChangeEvent)
    {
        onDestinationChangeEvent_ = onDestinationChangeEvent;
    }

    void FireDestinationChangeEvent() const
    {
        if (onDestinationChangeEvent_) {
            onDestinationChangeEvent_();
        }
    }

private:
    OnStateChangeEvent onStateChangeEvent_;
    OnDestinationChangeEvent onDestinationChangeEvent_;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_NAVROUTER_NAVROUTER_EVENT_HUB_H
