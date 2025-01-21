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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SIDE_BAR_SIDE_BAR_CONTAINER_EVENT_HUB_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SIDE_BAR_SIDE_BAR_CONTAINER_EVENT_HUB_H

#include "core/components_ng/event/event_hub.h"

namespace OHOS::Ace::NG {

using ChangeEvent = std::function<void(const bool)>;
using OnSideBarWidthChangeEvent = std::function<void(const Dimension&)>;

class SideBarContainerEventHub : public EventHub {
    DECLARE_ACE_TYPE(SideBarContainerEventHub, EventHub)

public:
    SideBarContainerEventHub() = default;
    ~SideBarContainerEventHub() override = default;

    void SetOnChange(ChangeEvent&& changeEvent)
    {
        changeEvent_ = std::move(changeEvent);
    }

    void FireChangeEvent(bool isShow)
    {
        if (isShowChangeEvent_) {
            isShowChangeEvent_(isShow);
        }
        if (changeEvent_) {
            changeEvent_(isShow);
        }
    }

    void SetOnChangeEvent(ChangeEvent&& changeEventEvent)
    {
        isShowChangeEvent_ = std::move(changeEventEvent);
    }

    void SetOnSideBarWidthChangeEvent(OnSideBarWidthChangeEvent&& event)
    {
        onSideBarWidthChangeEvent_ = std::move(event);
    }

    void FireSideBarWidthChangeEvent(Dimension& sideBarWidth)
    {
        if (onSideBarWidthChangeEvent_) {
            onSideBarWidthChangeEvent_(sideBarWidth);
        }
    }

private:
    ChangeEvent changeEvent_;
    ChangeEvent isShowChangeEvent_;
    OnSideBarWidthChangeEvent onSideBarWidthChangeEvent_;

    ACE_DISALLOW_COPY_AND_MOVE(SideBarContainerEventHub);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SIDE_BAR_SIDE_BAR_CONTAINER_EVENT_HUB_H
