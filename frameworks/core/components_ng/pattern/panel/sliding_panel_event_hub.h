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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_PANEL_SLIDING_PANEL_EVENT_HUB_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_PANEL_SLIDING_PANEL_EVENT_HUB_H

#include "base/memory/ace_type.h"
#include "core/components_ng/event/event_hub.h"
#include "core/components_ng/event/gesture_event_hub.h"

namespace OHOS::Ace::NG {

using ChangeEvent = std::function<void(const float, const float, PanelMode)>;
using HeightChangeEvent = std::function<void(const float)>;

class SlidingPanelEventHub : public EventHub {
    DECLARE_ACE_TYPE(SlidingPanelEventHub, EventHub)

public:
    SlidingPanelEventHub() = default;
    ~SlidingPanelEventHub() override = default;

    void SetOnChange(ChangeEvent&& changeEvent)
    {
        changeEvent_ = std::move(changeEvent);
    }

    void SetOnHeightChange(HeightChangeEvent&& heightChangeEvent)
    {
        heightChangeEvent_ = std::move(heightChangeEvent);
    }

    void FireSizeChangeEvent(float width, float height, PanelMode mode) const
    {
        if (changeEvent_) {
            changeEvent_(width, height, mode);
        }
    }

    void FireHeightChangeEvent(float currentOffset) const
    {
        if (heightChangeEvent_) {
            heightChangeEvent_(currentOffset);
        }
    }

private:
    ChangeEvent changeEvent_;
    HeightChangeEvent heightChangeEvent_;

    ACE_DISALLOW_COPY_AND_MOVE(SlidingPanelEventHub);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_PANEL_SLIDING_PANEL_EVENT_HUB_H