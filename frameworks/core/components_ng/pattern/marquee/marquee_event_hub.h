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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_MARQUEE_EVENT_HUB_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_MARQUEE_EVENT_HUB_H

#include "core/components_ng/event/event_hub.h"

namespace OHOS::Ace::NG {

using ChangeEvent = std::function<void()>;

class MarqueeEventHub : public EventHub {
    DECLARE_ACE_TYPE(MarqueeEventHub, EventHub)

public:
    MarqueeEventHub() = default;
    ~MarqueeEventHub() override = default;

    void SetOnStart(ChangeEvent&& changeEvent)
    {
        startEvent_ = std::move(changeEvent);
    }

    void SetOnBounce(ChangeEvent&& changeEvent)
    {
        bounceEvent_ = std::move(changeEvent);
    }

    void SetOnFinish(ChangeEvent&& changeEvent)
    {
        finishEvent_ = std::move(changeEvent);
    }

    void FireStartEvent() const
    {
        if (startEvent_) {
            startEvent_();
        }
    }

    void FireBounceEvent()
    {
        if (bounceEvent_) {
            bounceEvent_();
        }
    }

    void FireFinishEvent()
    {
        if (finishEvent_) {
            finishEvent_();
        }
    }

private:
    ChangeEvent startEvent_;
    ChangeEvent bounceEvent_;
    ChangeEvent finishEvent_;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_MARQUEE_EVENT_HUB_H