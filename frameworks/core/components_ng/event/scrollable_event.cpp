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

#include "core/components_ng/event/scrollable_event.h"

#include "base/geometry/offset.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/event/gesture_event_hub.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

ScrollableActuator::ScrollableActuator(const WeakPtr<GestureEventHub>& gestureEventHub)
    : gestureEventHub_(gestureEventHub)
{}

void ScrollableActuator::OnCollectTouchTarget(const OffsetF& coordinateOffset, const TouchRestrict& touchRestrict,
    const GetEventTargetImpl& getEventTargetImpl, TouchTestResult& result)
{
    if (!initialized_) {
        InitializeScrollable();
    }
    for (const auto& [axis, scrollable] : scrollables_) {
        scrollable->SetGetEventTargetImpl(getEventTargetImpl);
        scrollable->SetCoordinateOffset(Offset(coordinateOffset.GetX(), coordinateOffset.GetY()));
        result.emplace_back(scrollable);
    }
}

// runs OnScroll and OnScrollBegin callbacks
void runScrollBeginCallback(const RefPtr<ScrollableEvent>& task, double& offset, bool vertical)
{
    auto dx = (vertical) ? Dimension(0) : Dimension(offset);
    auto dy = (vertical) ? Dimension(offset) : Dimension(0);

    auto onScrollCallback = task->GetOnScrollCallback();
    if (onScrollCallback) {
        onScrollCallback(dx, dy);
    }

    // Modifies offset based on developer's OnScrollBegin callback
    auto scrollBeginCallback = task->GetScrollBeginCallback();
    if (scrollBeginCallback) {
        ScrollInfo info  = scrollBeginCallback(dx, dy);
        // scrollBeginCallback returns dx/dy Remain -- true offset set by developer
        offset = (vertical) ? info.dy.Value() : info.dx.Value();
    }
}

void ScrollableActuator::InitializeScrollable()
{
    if (scrollableEvents_.empty()) {
        return;
    }
    auto gestureEventHub = gestureEventHub_.Upgrade();
    auto host = gestureEventHub ? gestureEventHub->GetFrameNode() : nullptr;
    if (!host) {
        LOGE("the host is nullptr");
        return;
    }
    for (const auto& [axis, events] : scrollableEvents_) {
        auto callback = [weak = WeakClaim(this), axis = axis](double offset, int32_t source) {
            auto actuator = weak.Upgrade();
            if (!actuator) {
                return true;
            }
            bool canScroll = true;
            for (const auto& task : actuator->scrollableEvents_[axis]) {
                // modifies offset
                runScrollBeginCallback(task, offset, (axis == Axis::VERTICAL));
                canScroll = task->GetScrollPositionCallback()(offset, source) && canScroll;
            }
            return canScroll;
        };
        auto scrollable = MakeRefPtr<Scrollable>(std::move(callback), axis);
        scrollable->Initialize(host->GetContext());
        scrollables_[axis] = scrollable;
    }
    initialized_ = true;
}

} // namespace OHOS::Ace::NG