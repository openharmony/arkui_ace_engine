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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_REFRESH_EVENT_HUB_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_REFRESH_EVENT_HUB_H

#include "frameworks/base/memory/ace_type.h"
#include "frameworks/core/components_ng/event/event_hub.h"

namespace OHOS::Ace::NG {

using StateChangeEvent = std::function<void(const int32_t)>;
using RefreshChangeEvent = std::function<void(const std::string)>;
using RefreshingEvent = std::function<void()>;
using OffsetChangeEvent = std::function<void(const float)>;

class RefreshEventHub : public EventHub {
    DECLARE_ACE_TYPE(RefreshEventHub, EventHub)

public:
    RefreshEventHub() = default;
    ~RefreshEventHub() override = default;

    void SetOnStateChange(StateChangeEvent&& stateChange)
    {
        stateChange_ = std::move(stateChange);
    }

    void FireOnStateChange(const int32_t value) const
    {
        if (stateChange_) {
            stateChange_(value);
        }
    }
    void SetOnRefreshing(RefreshingEvent&& refreshing)
    {
        refreshing_ = std::move(refreshing);
    }

    void FireOnRefreshing() const
    {
        if (refreshing_) {
            refreshing_();
        }
    }

    void SetChangeEvent(RefreshChangeEvent&& changeEvent)
    {
        changeEvent_ = std::move(changeEvent);
    }

    void FireChangeEvent(const std::string& value) const
    {
        if (changeEvent_) {
            changeEvent_(value);
        }
    }

    void SetOnOffsetChange(OffsetChangeEvent&& dragOffset)
    {
        offsetChange_ = std::move(dragOffset);
    }

    void SetOnStepOffsetChange(OffsetChangeEvent&& dragOffset)
    {
        stepOffsetChange_ = std::move(dragOffset);
    }

    void ResetOnOffsetChange()
    {
        offsetChange_ = nullptr;
    }

    void FireOnOffsetChange(const float value) const
    {
        if (offsetChange_) {
            offsetChange_(value);
        }
    }

    void FireOnStepOffsetChange(const float value) const
    {
        if (stepOffsetChange_) {
            stepOffsetChange_(value);
        }
    }

private:
    StateChangeEvent stateChange_;
    RefreshingEvent refreshing_;
    OffsetChangeEvent offsetChange_;
    RefreshChangeEvent changeEvent_;
    OffsetChangeEvent stepOffsetChange_;
    ACE_DISALLOW_COPY_AND_MOVE(RefreshEventHub);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_REFRESH_EVENT_HUB_H