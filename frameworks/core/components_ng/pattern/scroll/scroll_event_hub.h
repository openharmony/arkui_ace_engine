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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SCROLL_SCROLL_EVENT_HUB_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SCROLL_SCROLL_EVENT_HUB_H

#include "base/memory/ace_type.h"
#include "core/components_ng/event/event_hub.h"
#include "core/components_ng/event/gesture_event_hub.h"
#include "core/components_ng/pattern/scrollable/scrollable_properties.h"

namespace OHOS::Ace::NG {

enum class ScrollEventType {
    SCROLL_TOP = 0,
    SCROLL_END,
    SCROLL_EDGE,
};

// which edge is reached
enum class ScrollEdge {
    TOP = 0,
    LEFT,
    BOTTOM,
    RIGHT,
};

using ScrollEvent = std::function<void(Dimension, Dimension)>;
using ScrollEdgeEvent = std::function<void(ScrollEdge)>;
using ScrollEndEvent = std::function<void()>;

class ScrollEventHub : public EventHub {
    DECLARE_ACE_TYPE(ScrollEventHub, EventHub)

public:
    ScrollEventHub() = default;
    ~ScrollEventHub() override = default;

    const ScrollEvent& GetOnScrollEvent()
    {
        return onScroll_;
    }

    void SetOnScroll(ScrollEvent&& onScroll)
    {
        onScroll_ = std::move(onScroll);
    }

    const ScrollEdgeEvent& GetScrollEdgeEvent()
    {
        return onScrollEdge_;
    }

    void SetOnScrollEdge(ScrollEdgeEvent&& event)
    {
        onScrollEdge_ = std::move(event);
    }

    const ScrollEndEvent& GetScrollEndEvent()
    {
        return onScrollEnd_;
    }

    void SetOnScrollEnd(ScrollEndEvent&& event)
    {
        onScrollEnd_ = std::move(event);
    }

    const OnScrollStartEvent& GetScrollStartEvent()
    {
        return onScrollStart_;
    }

    void SetOnScrollStart(OnScrollStartEvent&& event)
    {
        onScrollStart_ = std::move(event);
    }

    const OnScrollStopEvent& GetScrollStopEvent()
    {
        return onScrollStop_;
    }

    void SetOnScrollStop(OnScrollStopEvent&& event)
    {
        onScrollStop_ = std::move(event);
    }

    const OnScrollBeginEvent& GetScrollBeginEvent()
    {
        return onScrollBegin_;
    }

    void SetOnScrollBegin(OnScrollBeginEvent&& event)
    {
        onScrollBegin_ = std::move(event);
    }

    const OnScrollFrameBeginEvent& GetScrollFrameBeginEvent()
    {
        return onScrollFrameBegin_;
    }

    void SetOnScrollFrameBegin(OnScrollFrameBeginEvent&& event)
    {
        onScrollFrameBegin_ = std::move(event);
    }

private:
    ScrollEvent onScroll_;
    OnScrollBeginEvent onScrollBegin_;
    OnScrollFrameBeginEvent onScrollFrameBegin_;
    ScrollEndEvent onScrollEnd_;
    OnScrollStartEvent onScrollStart_;
    OnScrollStopEvent onScrollStop_;
    ScrollEdgeEvent onScrollEdge_;

    ACE_DISALLOW_COPY_AND_MOVE(ScrollEventHub);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SCROLL_SCROLL_EVENT_HUB_H