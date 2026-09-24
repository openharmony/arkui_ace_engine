/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TABS_TABS_EVENT_HUB_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TABS_TABS_EVENT_HUB_H

#include <functional>

#include "base/memory/ace_type.h"
#include "core/components_ng/event/event_hub.h"
#include "core/components_ng/pattern/tabs/tabs_declaration.h"

namespace OHOS::Ace::NG {

using OnBarDisplayModeChangeEvent = std::function<void(TabBarDisplayMode)>;

class TabsEventHub : public EventHub {
    DECLARE_ACE_TYPE(TabsEventHub, EventHub);
public:
    TabsEventHub() = default;
    ~TabsEventHub() override = default;

    void SetOnBarDisplayModeChange(OnBarDisplayModeChangeEvent&& event)
    {
        onBarDisplayModeChangeEvent_ = std::move(event);
    }

    void FireBarDisplayModeChangeEvent(TabBarDisplayMode mode)
    {
        if (onBarDisplayModeChangeEvent_) {
            onBarDisplayModeChangeEvent_(mode);
        }
    }

private:
    OnBarDisplayModeChangeEvent onBarDisplayModeChangeEvent_;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TABS_TABS_EVENT_HUB_H
