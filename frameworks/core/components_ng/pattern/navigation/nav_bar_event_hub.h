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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_NAVIGATION_NAV_BAR_EVENT_HUB_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_NAVIGATION_NAV_BAR_EVENT_HUB_H

#include "base/memory/ace_type.h"
#include "core/components_ng/event/event_hub.h"
#include "core/components_ng/pattern/navigation/navigation_declaration.h"

namespace OHOS::Ace::NG {
using OnCoordScrollStartAction = std::function<void()>;
using OnCoordScrollUpdateAction = std::function<void(float)>;
using OnCoordScrollEndAction = std::function<void()>;

class NavBarEventHub : public EventHub {
    DECLARE_ACE_TYPE(NavBarEventHub, EventHub)
public:
    void SetOnCoordScrollStartAction(OnCoordScrollStartAction&& action)
    {
        onCoordScrollStartAction_ = std::move(action);
    }
    
    void FireOnCoordScrollStartAction()
    {
        if (onCoordScrollStartAction_) {
            onCoordScrollStartAction_();
        }
    }
    
    bool HasOnCoordScrollStartAction()
    {
        return onCoordScrollStartAction_ ? true : false;
    }
    
    void SetOnCoordScrollUpdateAction(OnCoordScrollUpdateAction&& action)
    {
        onCoordScrollUpdateAction_ = std::move(action);
    }
    
    void FireOnCoordScrollUpdateAction(float currentOffset)
    {
        if (onCoordScrollUpdateAction_) {
            onCoordScrollUpdateAction_(currentOffset);
        }
    }
    
    void SetOnCoordScrollEndAction(OnCoordScrollEndAction&& action)
    {
        onCoordScrollEndAction_ = std::move(action);
    }
    
    void FireOnCoordScrollEndAction()
    {
        if (onCoordScrollEndAction_) {
            onCoordScrollEndAction_();
        }
    }

private:
    OnCoordScrollStartAction onCoordScrollStartAction_;
    OnCoordScrollUpdateAction onCoordScrollUpdateAction_;
    OnCoordScrollEndAction onCoordScrollEndAction_;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_NAVIGATION_NAV_BAR_EVENT_HUB_H