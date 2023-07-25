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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_NAVIGATION_NAVIGATION_EVENT_HUB_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_NAVIGATION_NAVIGATION_EVENT_HUB_H

#include "base/memory/ace_type.h"
#include "core/components_ng/pattern/navigation/navigation_declaration.h"
#include "core/components_ng/event/event_hub.h"
#include "core/components_ng/event/gesture_event_hub.h"

namespace OHOS::Ace::NG {

using OnTitleModeChangeEvent = std::function<void(const BaseEventInfo* eventInfo)>;
using OnNavBarStateChangeEvent = std::function<void(bool)>;

class NavigationEventHub : public EventHub {
    DECLARE_ACE_TYPE(NavigationEventHub, EventHub)
public:
    void SetOnTitleModeChange(OnTitleModeChangeEvent&& changeEvent)
    {
        onTitleModeChangeEvent_ = changeEvent;
    }

    void FireChangeEvent(const BaseEventInfo* eventInfo) const
    {
        if (onTitleModeChangeEvent_) {
            onTitleModeChangeEvent_(eventInfo);
        }
    }

    void SetOnNavBarStateChange(OnNavBarStateChangeEvent&& changeEvent)
    {
        onNavBarStateChangeEvent_ = changeEvent;
    }

    void FireNavBarStateChangeEvent(bool isVisible) const
    {
        if (onNavBarStateChangeEvent_) {
            onNavBarStateChangeEvent_(isVisible);
        }
    }

private:
    OnTitleModeChangeEvent onTitleModeChangeEvent_;
    OnNavBarStateChangeEvent onNavBarStateChangeEvent_;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_NAVIGATION_NAVIGATION_EVENT_HUB_H