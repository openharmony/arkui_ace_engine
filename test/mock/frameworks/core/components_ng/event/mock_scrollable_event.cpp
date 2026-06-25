/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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
#include "core/components_ng/gestures/recognizers/click_recognizer.h"
#include "core/components_ng/pattern/scroll/scroll_edge_effect.h"
#include "core/components_ng/pattern/scrollable/scrollable.h"

namespace OHOS::Ace::NG {

ScrollableEvent::ScrollableEvent(Axis axis) : axis_(axis) {};
ScrollableEvent::~ScrollableEvent() {};

ScrollableActuator::~ScrollableActuator() {};

ScrollableActuator::ScrollableActuator(const WeakPtr<GestureEventHub>& gestureEventHub)
    : gestureEventHub_(gestureEventHub)
{}

void ScrollableEvent::SetAxis(Axis axis)
{
    axis_ = axis;
}

void ScrollableEvent::SetScrollable(const RefPtr<Scrollable>& scrollable) {}

const RefPtr<Scrollable>& ScrollableEvent::GetScrollable() const
{
    return scrollable_;
}

bool ScrollableEvent::Idle() const
{
    return true;
}

bool ScrollableEvent::IsHitTestBlock(const PointF& localPoint, SourceType source) const
{
    return false;
}

void ScrollableEvent::AddPreviewMenuHandleDragEnd(GestureEventFunc&& actionEnd) {}

void ScrollableActuator::AddScrollEdgeEffect(const Axis& axis, RefPtr<ScrollEdgeEffect>& effect) {}

bool ScrollableActuator::RemoveScrollEdgeEffect(const RefPtr<ScrollEdgeEffect>& effect)
{
    return false;
}

void ScrollableActuator::CollectTouchTarget(const OffsetF& coordinateOffset, const TouchRestrict& touchRestrict,
    const GetEventTargetImpl& getEventTargetImpl, TouchTestResult& result, const PointF& localPoint,
    const RefPtr<FrameNode>& frameNode, const RefPtr<TargetComponent>& targetComponent,
    ResponseLinkResult& responseLinkResult, int32_t touchId)
{}

void ScrollableActuator::AddScrollableEvent(const RefPtr<ScrollableEvent>& scrollableEvent) {}

void ScrollableActuator::RemoveScrollableEvent(const RefPtr<ScrollableEvent>& scrollableEvent) {}

void ScrollableActuator::AddPreviewMenuHandleDragEnd(GestureEventFunc&& actionEnd) {}
} // namespace OHOS::Ace::NG
