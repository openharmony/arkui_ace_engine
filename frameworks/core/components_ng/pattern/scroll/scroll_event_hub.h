/*
 * Copyright (c) 2022-2024 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/scrollable/scrollable_event_hub.h"

namespace OHOS::Ace::NG {

// which edge is reached
enum class ScrollEdge {
    TOP = 0,
    LEFT,
    BOTTOM,
    RIGHT,
};

struct TwoDimensionScrollResult {
    Dimension xOffset;
    Dimension yOffset;

    bool operator==(const TwoDimensionScrollResult& scrollRes) const
    {
        return xOffset == scrollRes.xOffset && yOffset == scrollRes.yOffset;
    }
};

using ScrollEvent = std::function<void(Dimension, Dimension)>;
using ScrollEventWithState = std::function<void(Dimension, Dimension, ScrollState)>;
using ScrollEventWithReturn = std::function<TwoDimensionScrollResult(Dimension, Dimension, ScrollState, ScrollSource)>;
using ScrollEdgeEvent = std::function<void(ScrollEdge)>;
using ScrollEndEvent = std::function<void()>;

class ScrollEventHub : public ScrollableEventHub {
    DECLARE_ACE_TYPE(ScrollEventHub, ScrollableEventHub)

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

    const ScrollEventWithReturn& GetOnWillScrollEvent() const
    {
        return onWillScroll_;
    }

    void SetOnWillScrollEvent(ScrollEventWithReturn&& onWillScroll)
    {
        onWillScroll_ = std::move(onWillScroll);
    }

    const ScrollEventWithState& GetOnDidScrollEvent() const
    {
        return onDidScroll_;
    }

    void SetOnDidScrollEvent(ScrollEventWithState&& onDidScroll)
    {
        onDidScroll_ = std::move(onDidScroll);
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

    const OnScrollBeginEvent& GetScrollBeginEvent()
    {
        return onScrollBegin_;
    }

    void SetOnScrollBegin(OnScrollBeginEvent&& event)
    {
        onScrollBegin_ = std::move(event);
    }

    void SetJSFrameNodeOnScrollWillScroll(ScrollEventWithReturn&& onScroll)
    {
        onJSFrameNodeWillScroll_ = std::move(onScroll);
    }

    void ClearJSFrameNodeOnScrollWillScroll()
    {
        if (onJSFrameNodeWillScroll_) {
            onJSFrameNodeWillScroll_ = nullptr;
        }
    }

    const ScrollEventWithReturn& GetJSFrameNodeOnScrollWillScroll()
    {
        return onJSFrameNodeWillScroll_;
    }

    void SetJSFrameNodeOnScrollDidScroll(ScrollEventWithState&& onScroll)
    {
        onJSFrameNodeDidScroll_ = std::move(onScroll);
    }

    void ClearJSFrameNodeOnScrollDidScroll()
    {
        if (onJSFrameNodeDidScroll_) {
            onJSFrameNodeDidScroll_ = nullptr;
        }
    }

    const ScrollEventWithState& GetJSFrameNodeOnScrollDidScroll()
    {
        return onJSFrameNodeDidScroll_;
    }

    void SetOnDidZoom(std::function<void(float)>&& event)
    {
        onDidZoom_ = std::move(event);
    }

    void FireOnDidZoom(float scale)
    {
        if (onDidZoom_) {
            onDidZoom_(scale);
        }
    }

    void SetOnZoomStart(std::function<void()>&& event)
    {
        onZoomStart_ = std::move(event);
    }

    void FireOnZoomStart()
    {
        if (onZoomStart_) {
            onZoomStart_();
        }
    }

    void SetOnZoomStop(std::function<void()>&& event)
    {
        onZoomStop_ = std::move(event);
    }

    void FireOnZoomStop()
    {
        if (onZoomStop_) {
            onZoomStop_();
        }
    }

    void SetOnZoomScaleChange(std::function<void(float)>&& event)
    {
        onZoomScaleChange_ = std::move(event);
    }

    void FireOnZoomScaleChange(float scale)
    {
        if (onZoomScaleChange_) {
            onZoomScaleChange_(scale);
        }
    }

private:
    ScrollEvent onScroll_;
    ScrollEventWithReturn onWillScroll_;
    ScrollEventWithState onDidScroll_;
    ScrollEventWithReturn onJSFrameNodeWillScroll_;
    ScrollEventWithState onJSFrameNodeDidScroll_;
    OnScrollBeginEvent onScrollBegin_;
    ScrollEndEvent onScrollEnd_;
    ScrollEdgeEvent onScrollEdge_;
    std::function<void(float)> onDidZoom_;
    std::function<void()> onZoomStart_;
    std::function<void()> onZoomStop_;
    std::function<void(float)> onZoomScaleChange_;

    ACE_DISALLOW_COPY_AND_MOVE(ScrollEventHub);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SCROLL_SCROLL_EVENT_HUB_H