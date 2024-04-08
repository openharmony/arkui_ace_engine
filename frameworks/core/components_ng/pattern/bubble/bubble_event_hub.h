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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_BUBBLE_BUBBLE_EVENT_HUB_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_BUBBLE_BUBBLE_EVENT_HUB_H

#include <string>

#include "base/memory/ace_type.h"
#include "core/components_ng/event/event_hub.h"
#include "core/components_ng/event/gesture_event_hub.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

using StateChangeEvent = std::function<void(const std::string&)>;

class BubbleEventHub : public EventHub {
    DECLARE_ACE_TYPE(BubbleEventHub, EventHub)

public:
    BubbleEventHub() = default;
    ~BubbleEventHub() override = default;

    void SetOnStateChange(StateChangeEvent&& changeEvent)
    {
        changeEvent_ = std::move(changeEvent);
    }

    void FireChangeEvent(bool isVisible)
    {
        if (changeEvent_) {
            auto json = JsonUtil::Create(true);
            json->Put("isVisible", isVisible);
            changeEvent_(json->ToString());
        }
    }

private:
    StateChangeEvent changeEvent_;
    
    ACE_DISALLOW_COPY_AND_MOVE(BubbleEventHub);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_BUBBLE_BUBBLE_EVENT_HUB_H