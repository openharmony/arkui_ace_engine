/*
 * Copyright (c) 2023-2024 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SCROLLABLE_SCROLLABLE_EVENT_HUB_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SCROLLABLE_SCROLLABLE_EVENT_HUB_H

#include "core/components_ng/event/event_hub.h"

namespace OHOS::Ace::NG {
class ScrollableEventHub : public EventHub {
    DECLARE_ACE_TYPE(ScrollableEventHub, EventHub)

public:
    ScrollableEventHub() = default;
    ~ScrollableEventHub() override = default;

    void SetOnScroll(OnScrollEvent&& onScroll)
    {
        onScrollEvent_ = std::move(onScroll);
    }

    const OnScrollEvent& GetOnScroll() const
    {
        return onScrollEvent_;
    }

    void SetOnWillScroll(OnWillScrollEvent&& onScroll)
    {
        onWillScrollEvent_ = std::move(onScroll);
    }

    const OnWillScrollEvent& GetOnWillScroll() const
    {
        return onWillScrollEvent_;
    }

    void SetOnDidScroll(OnScrollEvent&& onScroll)
    {
        onDidScrollEvent_ = std::move(onScroll);
    }

    const OnScrollEvent& GetOnDidScroll() const
    {
        return onDidScrollEvent_;
    }

    void SetOnScrollFrameBegin(OnScrollFrameBeginEvent&& onScrollFrameBegin)
    {
        onScrollFrameBeginEvent_ = std::move(onScrollFrameBegin);
    }

    const OnScrollFrameBeginEvent& GetOnScrollFrameBegin() const
    {
        return onScrollFrameBeginEvent_;
    }

    void SetOnScrollStart(OnScrollStartEvent&& onScrollStart)
    {
        onScrollStartEvent_ = std::move(onScrollStart);
    }

    const OnScrollStartEvent& GetOnScrollStart() const
    {
        return onScrollStartEvent_;
    }

    void SetOnScrollStop(OnScrollStopEvent&& onScrollStop)
    {
        onScrollStopEvent_ = std::move(onScrollStop);
    }

    const OnScrollStopEvent& GetOnScrollStop() const
    {
        return onScrollStopEvent_;
    }

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

private:
    OnScrollEvent onScrollEvent_;
    OnWillScrollEvent onWillScrollEvent_;
    OnScrollEvent onDidScrollEvent_;
    OnScrollStartEvent onScrollStartEvent_;
    OnScrollStopEvent onScrollStopEvent_;
    OnScrollFrameBeginEvent onScrollFrameBeginEvent_;
    OnReachEvent onReachStartEvent_;
    OnReachEvent onReachEndEvent_;
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SCROLLABLE_SCROLLABLE_EVENT_HUB_H
