/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_WATERFLOW_WATER_FLOW_EVENT_HUB_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_WATERFLOW_WATER_FLOW_EVENT_HUB_H

#include "core/components_ng/event/event_hub.h"
#include "core/components_ng/pattern/scrollable/scrollable_properties.h"

namespace OHOS::Ace::NG {
class WaterFlowEventHub : public EventHub {
    DECLARE_ACE_TYPE(WaterFlowEventHub, EventHub)

public:
    void SetOnReachStart(OnReachEvent&& onReachStart)
    {
        onReachStartEvent_ = std::move(onReachStart);
    }

    const OnReachEvent& GetOnReachStart() const
    {
        return onReachStartEvent_;
    }

    void SetOnReachEnd(OnReachEvent&& onReachEnd)
    {
        onReachEndEvent_ = std::move(onReachEnd);
    }

    const OnReachEvent& GetOnReachEnd() const
    {
        return onReachEndEvent_;
    }

    void SetOnScrollFrameBegin(OnScrollFrameBeginEvent&& onScrollFrameBegin)
    {
        onScrollFrameBeginEvent_ = std::move(onScrollFrameBegin);
    }

    const OnScrollFrameBeginEvent& GetOnScrollFrameBegin() const
    {
        return onScrollFrameBeginEvent_;
    }

private:
    OnReachEvent onReachStartEvent_;
    OnReachEvent onReachEndEvent_;
    OnScrollFrameBeginEvent onScrollFrameBeginEvent_;
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_WATERFLOW_WATER_FLOW_EVENT_HUB_H