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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_EVENT_OVERFLOW_SCROLL_EVENT_HUB_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_EVENT_OVERFLOW_SCROLL_EVENT_HUB_H

#include "base/memory/ace_type.h"
#include "core/components_ng/event/event_hub.h"

namespace OHOS::Ace::NG {

using OverflowScrollEvent = std::function<void(int32_t, float)>;

class ACE_EXPORT OverflowScrollEventHub : public EventHub {
    DECLARE_ACE_TYPE(OverflowScrollEventHub, EventHub);

public:
    void SetOverflowScrollEvent(OverflowScrollEvent&& overflowScrollEvent)
    {
        overflowScrollEvent_ = std::move(overflowScrollEvent);
    }

    void FireOverflowScrollEvent(int32_t nodeId, float offset) const
    {
        if (overflowScrollEvent_) {
            overflowScrollEvent_(nodeId, offset);
        }
    }

    void ClearOverflowScrollEvent()
    {
        if (overflowScrollEvent_) {
            overflowScrollEvent_ = nullptr;
        }
    }

private:
    OverflowScrollEvent overflowScrollEvent_;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_EVENT_OVERFLOW_SCROLL_EVENT_HUB_H