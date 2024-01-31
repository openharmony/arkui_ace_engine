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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_TIMER_EVENT_HUB_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_TIMER_EVENT_HUB_H

#include "base/memory/ace_type.h"
#include "core/components_ng/event/event_hub.h"

namespace OHOS::Ace::NG {

using ChangeEvent = std::function<void(int64_t, int64_t)>;

class TextTimerEventHub : public EventHub {
    DECLARE_ACE_TYPE(TextTimerEventHub, EventHub)

public:
    TextTimerEventHub() = default;
    ~TextTimerEventHub() override = default;

    void SetOnTimer(ChangeEvent&& changeEvent)
    {
        changeEvent_ = std::move(changeEvent);
    }

    void FireChangeEvent(int64_t utc, int64_t elapsedTime) const
    {
        if (changeEvent_) {
            changeEvent_(std::move(utc), std::move(elapsedTime));
        }
    }

private:
    ChangeEvent changeEvent_;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_TIMER_EVENT_HUB_H