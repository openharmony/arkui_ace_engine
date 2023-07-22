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
#include "base/utils/utils.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/event/gesture_event_hub.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

ScrollableActuator::ScrollableActuator(const WeakPtr<GestureEventHub>& gestureEventHub)
    : gestureEventHub_(gestureEventHub)
{}

void ScrollableActuator::CollectTouchTarget(const OffsetF& coordinateOffset, const PointF& localPoint,
    const GetEventTargetImpl& getEventTargetImpl, TouchTestResult& result)
{
    for (const auto& [axis, event] : scrollableEvents_) {
        if (!event || !event->GetEnable()) {
            continue;
        }
        auto scrollBar = event->GetScrollBar();
        if (scrollBar && scrollBar->InBarTouchRegion(Point(localPoint.GetX(), localPoint.GetY()))) {
            scrollBar->OnCollectTouchTarget(coordinateOffset, getEventTargetImpl, result);
        } else {
            const auto& scrollable = event->GetScrollable();
            scrollable->SetGetEventTargetImpl(getEventTargetImpl);
            scrollable->SetCoordinateOffset(Offset(coordinateOffset.GetX(), coordinateOffset.GetY()));
            scrollable->OnCollectTouchTarget(result);
        }
    }
}

void ScrollableActuator::InitializeScrollable(RefPtr<ScrollableEvent> event)
{
    auto gestureEventHub = gestureEventHub_.Upgrade();
    auto host = gestureEventHub ? gestureEventHub->GetFrameNode() : nullptr;
    CHECK_NULL_VOID(host);
    auto scrollable = MakeRefPtr<Scrollable>(event->GetScrollPositionCallback(), event->GetAxis());
    scrollable->SetNodeId(host->GetAccessibilityId());
    scrollable->SetOnScrollBegin(event->GetScrollBeginCallback());
    scrollable->SetOnScrollFrameBegin(event->GetScrollFrameBeginCallback());
    scrollable->SetScrollEndCallback(event->GetScrollEndCallback());
    scrollable->Initialize(host->GetContext());
    scrollable->SetUnstaticFriction(event->GetFriction());
    event->SetScrollable(scrollable);
}

void ScrollableActuator::AddScrollEdgeEffect(const Axis& axis, RefPtr<ScrollEdgeEffect>& effect)
{
    CHECK_NULL_VOID_NOLOG(effect);
    auto scrollable = scrollableEvents_[axis];
    CHECK_NULL_VOID_NOLOG(scrollable);
    effect->SetScrollable(scrollable->GetScrollable());
    effect->InitialEdgeEffect();
    scrollEffects_[axis] = effect;
}

bool ScrollableActuator::RemoveScrollEdgeEffect(const RefPtr<ScrollEdgeEffect>& effect)
{
    CHECK_NULL_RETURN_NOLOG(effect, false);
    for (auto iter = scrollEffects_.begin(); iter != scrollEffects_.end(); ++iter) {
        if (effect == iter->second) {
            scrollEffects_.erase(iter);
            return true;
        }
    }
    return false;
}

} // namespace OHOS::Ace::NG