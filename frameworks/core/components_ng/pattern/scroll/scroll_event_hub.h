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

using OnScrollEvent = std::function<void(Dimension, Dimension)>;
using ScrollBeginEvent = std::function<ScrollInfo(Dimension, Dimension)>;
using ScrollEdgeEvent = std::function<void(ScrollEdge)>;
using ScrollEndEvent = std::function<void()>;

class ScrollEventHub : public EventHub {
    DECLARE_ACE_TYPE(ScrollEventHub, EventHub)

public:
    ScrollEventHub() = default;
    ~ScrollEventHub() override = default;

    OnScrollEvent GetOnScrollEvent()
    {
        return onScroll_;
    }

    void SetOnScroll(OnScrollEvent&& onScroll)
    {
        onScroll_ = std::move(onScroll);
    }

    ScrollEdgeEvent GetScrollEdgeEvent()
    {
        return onScrollEdge_;
    }

    void SetOnScrollEdge(ScrollEdgeEvent&& event)
    {
        onScrollEdge_ = std::move(event);
    }

    ScrollEndEvent GetScrollEndEvent()
    {
        return onScrollEnd_;
    }

    void SetOnScrollEnd(ScrollEndEvent&& event)
    {
        onScrollEnd_ = std::move(event);
    }

    ScrollBeginEvent GetScrollBeginEvent()
    {
        return onScrollBegin_;
    }

    void SetOnScrollBegin(ScrollBeginEvent&& event)
    {
        onScrollBegin_ = std::move(event);
    }

private:
    OnScrollEvent onScroll_;
    ScrollBeginEvent onScrollBegin_;
    ScrollEndEvent onScrollEnd_;
    ScrollEdgeEvent onScrollEdge_;

    ACE_DISALLOW_COPY_AND_MOVE(ScrollEventHub);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SCROLL_SCROLL_EVENT_HUB_H