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

void ScrollableActuator::OnCollectTouchTarget(const OffsetF& coordinateOffset, const TouchRestrict& /*touchRestrict*/,
    const GetEventTargetImpl& getEventTargetImpl, TouchTestResult& result)
{
    if (!initialized_) {
        InitializeScrollable();
    }
    for (const auto& [axis, event] : scrollableEvents_) {
        if (!event->GetEnable()) {
            continue;
        }
        const auto& scrollable = event->GetScrollable();
        scrollable->SetGetEventTargetImpl(getEventTargetImpl);
        scrollable->SetCoordinateOffset(Offset(coordinateOffset.GetX(), coordinateOffset.GetY()));
        scrollable->OnCollectTouchTarget(result);
    }
}

void ScrollableActuator::InitializeScrollable()
{
    if (scrollableEvents_.empty()) {
        return;
    }
    auto gestureEventHub = gestureEventHub_.Upgrade();
    auto host = gestureEventHub ? gestureEventHub->GetFrameNode() : nullptr;
    CHECK_NULL_VOID(host);
    for (const auto& [axis, event] : scrollableEvents_) {
        auto scrollable = MakeRefPtr<Scrollable>(event->GetScrollPositionCallback(), axis);
        scrollable->SetOnScrollBegin(event->GetScrollBeginCallback());
        scrollable->SetScrollEndCallback(event->GetScrollEndCallback());
        if (scrollEffects_.count(axis)) {
            auto scrollEffect = scrollEffects_[axis];
            scrollEffect->SetScrollable(scrollable);
            scrollEffect->InitialEdgeEffect();
        }
        scrollable->Initialize(host->GetContext());
        event->SetScrollable(scrollable);
    }
    initialized_ = true;
}

void ScrollableActuator::AddScrollEdgeEffect(const Axis& axis, const RefPtr<ScrollEdgeEffect>& effect)
{
    if (!effect) {
        return;
    }
    scrollEffects_[axis] = effect;
    initialized_ = false;
}

bool ScrollableActuator::RemoveScrollEdgeEffect(const RefPtr<ScrollEdgeEffect>& effect)
{
    if (!effect) {
        return false;
    }
    for (auto iter = scrollEffects_.begin(); iter != scrollEffects_.end(); ++iter) {
        if (effect == iter->second) {
            scrollEffects_.erase(iter);
            return true;
        }
    }
    initialized_ = false;
    return false;
}

} // namespace OHOS::Ace::NG