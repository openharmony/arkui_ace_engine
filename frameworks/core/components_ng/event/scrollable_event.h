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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_EVENT_SCROLLABLE_EVENT_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_EVENT_SCROLLABLE_EVENT_H

#include <list>
#include <unordered_map>

#include "base/geometry/axis.h"
#include "base/memory/referenced.h"
#include "core/components/scroll/scrollable.h"
#include "core/components_ng/event/gesture_event_actuator.h"

namespace OHOS::Ace::NG {

class GestureEventHub;

class ScrollableEvent : public Referenced {
public:
    explicit ScrollableEvent(Axis axis) : axis_(axis) {};
    ~ScrollableEvent() override = default;

    void SetScrollPositionCallback(ScrollPositionCallback&& callback)
    {
        if (!callback) {
            return;
        }
        callback_ = std::move(callback);
    }

    const ScrollPositionCallback& GetScrollPositionCallback() const
    {
        return callback_;
    }

    void SetScrollBeginCallback(ScrollBeginCallback&& scrollBeginCallback)
    {
        if (!scrollBeginCallback) {
            return;
        }
        scrollBeginCallback_ = std::move(scrollBeginCallback);
    }

    const ScrollBeginCallback& GetScrollBeginCallback() const
    {
        return scrollBeginCallback_;
    }

    Axis GetAxis() const
    {
        return axis_;
    }

private:
    ScrollPositionCallback callback_;
    ScrollBeginCallback scrollBeginCallback_;
    Axis axis_ = Axis::VERTICAL;
};

class ScrollableActuator : public GestureEventActuator {
    DECLARE_ACE_TYPE(ScrollableActuator, GestureEventActuator)
public:
    explicit ScrollableActuator(const WeakPtr<GestureEventHub>& gestureEventHub);
    ~ScrollableActuator() override = default;

    void AddScrollableEvent(const RefPtr<ScrollableEvent>& scrollableEvent)
    {
        scrollableEvents_[scrollableEvent->GetAxis()].emplace_back(scrollableEvent);
        initialized_ = false;
    }

    void RemoveScrollableEvent(const RefPtr<ScrollableEvent>& scrollableEvent)
    {
        scrollableEvents_[scrollableEvent->GetAxis()].remove(scrollableEvent);
        initialized_ = false;
    }

    void OnCollectTouchTarget(const OffsetF& coordinateOffset, const TouchRestrict& touchRestrict,
        const GetEventTargetImpl& getEventTargetImpl, TouchTestResult& result) override;

private:
    void InitializeScrollable();

    std::unordered_map<Axis, std::list<RefPtr<ScrollableEvent>>> scrollableEvents_;
    std::unordered_map<Axis, RefPtr<Scrollable>> scrollables_;
    WeakPtr<GestureEventHub> gestureEventHub_;
    bool initialized_ = false;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_EVENT_SCROLLABLE_EVENT_HUB_H
