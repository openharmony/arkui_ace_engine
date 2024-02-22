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
 
#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TABS_TAB_CONTENT_EVENT_HUB_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TABS_TAB_CONTENT_EVENT_HUB_H


#include "base/memory/ace_type.h"
#include "core/components_ng/event/event_hub.h"

namespace OHOS::Ace::NG {
class TabContentEventHub : public EventHub {
    DECLARE_ACE_TYPE(TabContentEventHub, EventHub)
public:
    TabContentEventHub() = default;
    ~TabContentEventHub() override = default;

    void SetOnWillShow(const std::function<void()>& onWillShow)
    {
        onWillShowEvent_ = onWillShow;
    }

    void SetOnWillHide(const std::function<void()>& onWillHide)
    {
        onWillHideEvent_ = onWillHide;
    }

    void FireWillShowEvent()
    {
        if (onWillShowEvent_) {
            onWillShowEvent_();
        }
    }

    void FireWillHideEvent()
    {
        if (onWillHideEvent_) {
            onWillHideEvent_();
        }
    }

private:
    std::function<void()> onWillShowEvent_;
    std::function<void()> onWillHideEvent_;
};
} // namespace OHOS::ACE::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TABS_TAB_CONTENT_EVENT_HUB_H
