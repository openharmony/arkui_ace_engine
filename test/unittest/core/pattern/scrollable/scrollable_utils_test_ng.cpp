/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
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

#include "scrollable_utils_test_ng.h"

#include "test/mock/core/animation/mock_animation_manager.h"

namespace OHOS::Ace::NG {
void ScrollableUtilsTestNG::DragStart(const RefPtr<FrameNode>& frameNode, Offset startOffset)
{
    dragNode_ = FindScrollableNode(frameNode);
    GestureEvent gesture;
    dragInfo_ = gesture;
    auto pattern = dragNode_->GetPattern<ScrollablePattern>();
    auto scrollable = pattern->GetScrollableEvent()->GetScrollable();
    dragInfo_.SetSourceTool(SourceTool::FINGER);
    dragInfo_.SetInputEventType(InputEventType::TOUCH_SCREEN);
    dragInfo_.SetGlobalPoint(Point() + startOffset);
    dragInfo_.SetGlobalLocation(startOffset);
    dragInfo_.SetLocalLocation(startOffset);
    scrollable->HandleTouchDown();
    scrollable->isDragging_ = true;
    scrollable->HandleDragStart(dragInfo_);
}

void ScrollableUtilsTestNG::DragUpdate(float delta)
{
    auto pattern = dragNode_->GetPattern<ScrollablePattern>();
    auto scrollable = pattern->GetScrollableEvent()->GetScrollable();
    double velocity = delta > 0 ? 200 : -200;
    dragInfo_.SetMainVelocity(velocity);
    dragInfo_.SetMainDelta(delta);
    dragInfo_.SetGlobalPoint(Point(0, delta));
    dragInfo_.SetGlobalLocation(Offset(0, delta));
    dragInfo_.SetLocalLocation(Offset(0, delta));
    scrollable->HandleDragUpdate(dragInfo_);
    FlushUITasks();
}

void ScrollableUtilsTestNG::DragEnd(float velocityDelta)
{
    auto pattern = dragNode_->GetPattern<ScrollablePattern>();
    auto scrollable = pattern->GetScrollableEvent()->GetScrollable();
    float velocity = velocityDelta * FRICTION * -FRICTION_SCALE;
    dragInfo_.SetMainDelta(0);
    dragInfo_.SetMainVelocity(velocity);
    dragInfo_.SetGlobalPoint(dragInfo_.GetGlobalPoint());
    dragInfo_.SetGlobalLocation(dragInfo_.GetGlobalLocation());
    dragInfo_.SetLocalLocation(dragInfo_.GetLocalLocation());
    scrollable->HandleTouchUp();
    scrollable->lastMainDelta_ = 0.0;
    scrollable->HandleDragEnd(dragInfo_);
    scrollable->isDragging_ = false;
    FlushUITasks();
    dragNode_ = nullptr;
}

void ScrollableUtilsTestNG::DragAction(
    const RefPtr<FrameNode>& frameNode, Offset startOffset, float dragDelta, float velocityDelta)
{
    DragStart(frameNode, startOffset);
    DragUpdate(dragDelta);
    DragEnd(velocityDelta);
}

RefPtr<FrameNode> ScrollableUtilsTestNG::FindScrollableNode(const RefPtr<FrameNode>& frameNode)
{
    auto scrollableNode = frameNode;
    while (scrollableNode) {
        if (AceType::InstanceOf<ScrollablePattern>(scrollableNode->GetPattern())) {
            return scrollableNode;
        }
        scrollableNode = AceType::DynamicCast<FrameNode>(scrollableNode->GetParent());
    }
    return scrollableNode;
}

void ScrollableUtilsTestNG::ScrollToIndex(
    int32_t index, bool smooth, ScrollAlign align, std::optional<float> extraOffset)
{
    positionController_->ScrollToIndex(index, smooth, align, extraOffset);
    FlushUITasks();
}

bool ScrollableUtilsTestNG::AnimateTo(
    const Dimension& position, float duration, const RefPtr<Curve>& curve, bool smooth, bool canOverScroll)
{
    bool result = positionController_->AnimateTo(position, duration, curve, smooth, canOverScroll);
    FlushUITasks();
    return result;
}

Offset ScrollableUtilsTestNG::GetCurrentOffset() const
{
    return positionController_->GetCurrentOffset();
}

Axis ScrollableUtilsTestNG::GetScrollDirection() const
{
    return positionController_->GetScrollDirection();
}

void ScrollableUtilsTestNG::ScrollBy(double pixelX, double pixelY, bool /* smooth */)
{
    positionController_->ScrollBy(pixelX, pixelY, false);
    FlushUITasks();
}

void ScrollableUtilsTestNG::ScrollToEdge(ScrollEdgeType scrollEdgeType, float velocity)
{
    positionController_->ScrollToEdge(scrollEdgeType, velocity);
    FlushUITasks();
}

void ScrollableUtilsTestNG::ScrollToEdge(ScrollEdgeType scrollEdgeType, bool smooth)
{
    positionController_->ScrollToEdge(scrollEdgeType, smooth);
    FlushUITasks();
}

void ScrollableUtilsTestNG::Fling(double flingVelocity)
{
    positionController_->Fling(flingVelocity);
    FlushUITasks();
}

void ScrollableUtilsTestNG::ScrollPage(bool reverse, bool smooth)
{
    positionController_->ScrollPage(reverse, smooth);
    FlushUITasks();
}

bool ScrollableUtilsTestNG::IsAtEnd() const
{
    return positionController_->IsAtEnd();
}

Rect ScrollableUtilsTestNG::GetItemRect(int32_t index) const
{
    return positionController_->GetItemRect(index);
}

int32_t ScrollableUtilsTestNG::GetItemIndex(double x, double y) const
{
    return positionController_->GetItemIndex(x, y);
}

void ScrollableUtilsTestNG::StopAnimate()
{
    positionController_->StopAnimate();
}

void ScrollableUtilsTestNG::ScrollTo(float position)
{
    positionController_->AnimateTo(Dimension(position), 0, nullptr, false);
    FlushUITasks();
}

AssertionResult ScrollableUtilsTestNG::Position(const RefPtr<FrameNode>& frameNode, float expectOffset)
{
    auto pattern = frameNode->GetPattern<ScrollablePattern>();
    float actualOffset = -(pattern->GetTotalOffset());
    return IsEqual(actualOffset, expectOffset);
}

AssertionResult ScrollableUtilsTestNG::TickPosition(const RefPtr<FrameNode>& frameNode, float expectOffset)
{
    if (!MockAnimationManager::GetInstance().AllFinished()) {
        MockAnimationManager::GetInstance().Tick();
        FlushUITasks();
    }
    return Position(frameNode, expectOffset);
}

AssertionResult ScrollableUtilsTestNG::TickPosition(
    const RefPtr<FrameNode>& frameNode, float velocity, float expectOffset)
{
    MockAnimationManager::GetInstance().TickByVelocity(velocity);
    FlushUITasks();
    return Position(frameNode, expectOffset);
}

AssertionResult ScrollableUtilsTestNG::Position(float expectOffset)
{
    return Position(frameNode_, expectOffset);
}

AssertionResult ScrollableUtilsTestNG::TickPosition(float expectOffset)
{
    return TickPosition(frameNode_, expectOffset);
}

AssertionResult ScrollableUtilsTestNG::TickPosition(float velocity, float expectOffset)
{
    return TickPosition(frameNode_, velocity, expectOffset);
}
} // namespace OHOS::Ace::NG
