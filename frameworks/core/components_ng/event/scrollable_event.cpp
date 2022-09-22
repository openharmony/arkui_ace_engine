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

void ScrollableActuator::InitializeScrollable()
{
    scrollables_.clear();
    if (scrollableEvents_.empty()) {
        return;
    }
    auto gestureEventHub = gestureEventHub_.Upgrade();
    auto host = gestureEventHub ? gestureEventHub->GetFrameNode() : nullptr;
    CHECK_NULL_VOID(host);
    for (const auto& [axis, event] : scrollableEvents_) {
        auto scrollable = MakeRefPtr<Scrollable>(event->GetScrollPositionCallback(), axis);
        scrollable->SetOnScrollBegin(event->GetScrollBeginCallback());
        scrollable->Initialize(host->GetContext());
        scrollables_[axis] = scrollable;
    }
    initialized_ = true;
}

} // namespace OHOS::Ace::NG