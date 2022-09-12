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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_LIST_LIST_EVENT_HUB_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_LIST_LIST_EVENT_HUB_H

#include "base/memory/ace_type.h"
#include "core/components_ng/event/event_hub.h"
#include "core/components_ng/event/gesture_event_hub.h"
#include "core/components_v2/list/list_component.h"

namespace OHOS::Ace::NG {

using OnScrollEvent = std::function<void(Dimension, V2::ScrollState)>;
using OnScrollBeginEvent = std::function<ScrollInfo(Dimension, Dimension)>;
using OnScrollStopEvent = std::function<void()>;
using OnScrollIndexEvent = std::function<void(int32_t, int32_t)>;
using OnReachEvent = std::function<void()>;

class ListEventHub : public EventHub {
    DECLARE_ACE_TYPE(ListEventHub, EventHub)

public:
    ListEventHub() = default;
    ~ListEventHub() override = default;

    void SetOnScroll(const OnScrollEvent&& onScroll)
    {
        onScrollEvent_ = onScroll;
    }

    const OnScrollEvent& GetOnScroll() const
    {
        return onScrollEvent_;
    }

    void SetOnScrollBegin(const OnScrollBeginEvent&& onScrollBegin)
    {
        onScrollBeginEvent_ = onScrollBegin;
    }

    const OnScrollBeginEvent& GetOnScrollBegin() const
    {
        return onScrollBeginEvent_;
    }

    void SetOnScrollStop(const OnScrollStopEvent&& onScrollStop)
    {
        onScrollStopEvent_ = onScrollStop;
    }

    const OnScrollStopEvent& GetOnScrollStop() const
    {
        return onScrollStopEvent_;
    }

    void SetOnScrollIndex(const OnScrollIndexEvent&& onScrollIndex)
    {
        onScrollIndexEvent_ = onScrollIndex;
    }

    const OnScrollIndexEvent& GetOnScrollIndex() const
    {
        return onScrollIndexEvent_;
    }

    void SetOnReachStart(const OnReachEvent&& onReachStart)
    {
        onReachStartEvent_ = onReachStart;
    }

    const OnReachEvent& GetOnReachStart() const
    {
        return onReachStartEvent_;
    }

    void SetOnReachEnd(const OnReachEvent&& onReachEnd)
    {
        onReachEndEvent_ = onReachEnd;
    }

    const OnReachEvent& GetOnReachEnd() const
    {
        return onReachEndEvent_;
    }

private:
    OnScrollEvent onScrollEvent_;
    OnScrollBeginEvent onScrollBeginEvent_;
    OnScrollStopEvent onScrollStopEvent_;
    OnScrollIndexEvent onScrollIndexEvent_;
    OnReachEvent onReachStartEvent_;
    OnReachEvent onReachEndEvent_;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_LIST_LIST_EVENT_HUB_H