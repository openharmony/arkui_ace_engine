/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_PATTERNLOCK_PATTERNLOCK_EVENT_HUB_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_PATTERNLOCK_PATTERNLOCK_EVENT_HUB_H

#include "base/memory/ace_type.h"
#include "core/components_ng/event/event_hub.h"
#include "core/components_ng/event/gesture_event_hub.h"

namespace OHOS::Ace::NG {

using PatternLockCompleteEvent = std::function<void(const BaseEventInfo* info)>;

class PatternLockEventHub : public EventHub {
    DECLARE_ACE_TYPE(PatternLockEventHub, EventHub)

public:
    PatternLockEventHub() = default;
    ~PatternLockEventHub() override = default;

    void SetOnComplete(PatternLockCompleteEvent&& completeEvent)
    {
        completeEvent_ = std::move(completeEvent);
    }

    void UpdateCompleteEvent(const BaseEventInfo* info) const
    {
        if (completeEvent_) {
            completeEvent_(info);
        }
    }

    void SetOnDotConnect(std::function<void(int32_t)>&& dotConnectEvent)
    {
        dotConnectEvent_ = std::move(dotConnectEvent);
    }

    void UpdateDotConnectEvent(int32_t code) const
    {
        if (dotConnectEvent_) {
            dotConnectEvent_(code);
        }
    }

private:
    PatternLockCompleteEvent completeEvent_;
    std::function<void(int32_t)> dotConnectEvent_;
    ACE_DISALLOW_COPY_AND_MOVE(PatternLockEventHub);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_PATTERNLOCK_PATTERNLOCK_EVENT_HUB_H
