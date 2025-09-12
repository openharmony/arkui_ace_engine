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
#include "core/components_ng/pattern/scrollable/scrollable_properties.h"

namespace OHOS::Ace::NG {
class ScrollableEventHub : public EventHub {
    DECLARE_ACE_TYPE(ScrollableEventHub, EventHub);

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

    void SetOnWillStopDragging(OnWillStopDraggingEvent&& onWillStopdragging)
    {
        onWillStopDraggingEvent_ = std::move(onWillStopdragging);
    }

    const OnWillStopDraggingEvent& GetOnWillStopDragging() const
    {
        return onWillStopDraggingEvent_;
    }

    void SetJSFrameNodeOnReachStart(OnReachEvent&& onScroll)
    {
        onJSFrameNodeReachStartEvent_ = std::move(onScroll);
    }

    const OnReachEvent& GetJSFrameNodeOnReachStart() const
    {
        return onJSFrameNodeReachStartEvent_;
    }

    void ClearJSFrameNodeOnReachStart()
    {
        if (onJSFrameNodeReachStartEvent_) {
            onJSFrameNodeReachStartEvent_ = nullptr;
        }
    }

    void SetJSFrameNodeOnReachEnd(OnReachEvent&& onScroll)
    {
        onJSFrameNodeReachEndEvent_ = std::move(onScroll);
    }

    void ClearJSFrameNodeOnReachEnd()
    {
        if (onJSFrameNodeReachEndEvent_) {
            onJSFrameNodeReachEndEvent_ = nullptr;
        }
    }

    const OnReachEvent& GetJSFrameNodeOnReachEnd() const
    {
        return onJSFrameNodeReachEndEvent_;
    }

    void SetJSFrameNodeOnScrollStart(OnScrollStartEvent&& onScroll)
    {
        onJSFrameNodeScrollStartEvent_ = std::move(onScroll);
    }

    void ClearJSFrameNodeOnScrollStart()
    {
        if (onJSFrameNodeScrollStartEvent_) {
            onJSFrameNodeScrollStartEvent_ = nullptr;
        }
    }

    const OnScrollStartEvent& GetJSFrameNodeOnScrollStart() const
    {
        return onJSFrameNodeScrollStartEvent_;
    }

    void SetJSFrameNodeOnScrollStop(OnScrollStopEvent&& onScroll)
    {
        onJSFrameNodeScrollStopEvent_ = std::move(onScroll);
    }

    void ClearJSFrameNodeOnScrollStop()
    {
        if (onJSFrameNodeScrollStopEvent_) {
            onJSFrameNodeScrollStopEvent_ = nullptr;
        }
    }

    const OnScrollStopEvent& GetJSFrameNodeOnScrollStop() const
    {
        return onJSFrameNodeScrollStopEvent_;
    }

    void SetJSFrameNodeOnScrollFrameBegin(OnScrollFrameBeginEvent&& onScroll)
    {
        onJSFrameNodeScrollFrameBeginEvent_ = std::move(onScroll);
    }

    void ClearJSFrameNodeOnScrollFrameBegin()
    {
        if (onJSFrameNodeScrollFrameBeginEvent_) {
            onJSFrameNodeScrollFrameBeginEvent_ = nullptr;
        }
    }

    const OnScrollFrameBeginEvent& GetJSFrameNodeOnScrollFrameBegin() const
    {
        return onJSFrameNodeScrollFrameBeginEvent_;
    }

    void SetJSFrameNodeOnWillScroll(OnWillScrollEvent&& onScroll)
    {
        onJSFrameNodeWillScrollEvent_ = std::move(onScroll);
    }

    void ClearJSFrameNodeOnWillScroll()
    {
        if (onJSFrameNodeWillScrollEvent_) {
            onJSFrameNodeWillScrollEvent_ = nullptr;
        }
    }

    const OnWillScrollEvent& GetJSFrameNodeOnWillScroll() const
    {
        return onJSFrameNodeWillScrollEvent_;
    }

    void SetJSFrameNodeOnDidScroll(OnScrollEvent&& onScroll)
    {
        onJSFrameNodeDidScrollEvent_ = std::move(onScroll);
    }

    void ClearJSFrameNodeOnDidScroll()
    {
        if (onJSFrameNodeDidScrollEvent_) {
            onJSFrameNodeDidScrollEvent_ = nullptr;
        }
    }

    const OnScrollEvent& GetJSFrameNodeOnDidScroll() const
    {
        return onJSFrameNodeDidScrollEvent_;
    }

    void SetOnWillStartDragging(OnWillStartDraggingEvent&& event)
    {
        onWillStartDraggingEvent_ = std::move(event);
    }

    const OnWillStartDraggingEvent& GetOnWillStartDragging() const
    {
        return onWillStartDraggingEvent_;
    }

    void SetOnDidStopDragging(OnDidStopDraggingEvent&& event)
    {
        onDidStopDraggingEvent_ = std::move(event);
    }

    const OnDidStopDraggingEvent& GetOnDidStopDragging() const
    {
        return onDidStopDraggingEvent_;
    }

    void SetOnWillStartFling(OnWillStartFlingEvent&& event)
    {
        onWillStartFlingEvent_ = std::move(event);
    }

    const OnWillStartFlingEvent& GetOnWillStartFling() const
    {
        return onWillStartFlingEvent_;
    }

    void SetOnDidStopFling(OnDidStopFlingEvent&& event)
    {
        onDidStopFlingEvent_ = std::move(event);
    }

    const OnDidStopFlingEvent& GetOnDidStopFling() const
    {
        return onDidStopFlingEvent_;
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
    OnWillStopDraggingEvent onWillStopDraggingEvent_;

    OnReachEvent onJSFrameNodeReachStartEvent_;
    OnReachEvent onJSFrameNodeReachEndEvent_;
    OnScrollStartEvent onJSFrameNodeScrollStartEvent_;
    OnScrollStopEvent onJSFrameNodeScrollStopEvent_;
    OnScrollFrameBeginEvent onJSFrameNodeScrollFrameBeginEvent_;
    OnWillScrollEvent onJSFrameNodeWillScrollEvent_;
    OnScrollEvent onJSFrameNodeDidScrollEvent_;

    OnWillStartDraggingEvent onWillStartDraggingEvent_;
    OnDidStopDraggingEvent onDidStopDraggingEvent_;
    OnWillStartFlingEvent onWillStartFlingEvent_;
    OnDidStopFlingEvent onDidStopFlingEvent_;
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SCROLLABLE_SCROLLABLE_EVENT_HUB_H
