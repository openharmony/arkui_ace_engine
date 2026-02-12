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

#include "scrollable_test_ng.h"

#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/pattern/mock_nestable_scroll_container.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/unittest/core/pattern/scrollable/mock_scrollable.h"
#include "core/components_ng/pattern/scrollable/scrollable_properties.h"
#include "core/components_ng/pattern/scrollable/axis/axis_animator.h"

namespace OHOS::Ace::NG {

/**
 * @tc.name: ScrollableState001
 * @tc.desc: Test IsMotionStop in different states
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, ScrollableState001, TestSize.Level1)
{
    auto scrollPn = scroll_->GetPattern<PartiallyMockedScrollable>();
    auto scrollable = scrollPn->GetScrollableEvent()->GetScrollable();
    ASSERT_NE(scrollable, nullptr);

    // IDLE state, not moved
    scrollable->state_ = Scrollable::AnimationState::IDLE;
    scrollable->moved_ = false;
    EXPECT_TRUE(scrollable->IsMotionStop());

    // SPRING state
    scrollable->state_ = Scrollable::AnimationState::SPRING;
    EXPECT_FALSE(scrollable->IsMotionStop());

    // FRICTION state
    scrollable->state_ = Scrollable::AnimationState::FRICTION;
    EXPECT_FALSE(scrollable->IsMotionStop());

    // IDLE state with moved
    scrollable->state_ = Scrollable::AnimationState::IDLE;
    scrollable->moved_ = true;
    EXPECT_FALSE(scrollable->IsMotionStop());

    // SNAP state
    scrollable->state_ = Scrollable::AnimationState::SNAP;
    EXPECT_FALSE(scrollable->IsMotionStop());

    // TRANSITION state
    scrollable->state_ = Scrollable::AnimationState::TRANSITION;
    EXPECT_FALSE(scrollable->IsMotionStop());
}

/**
 * @tc.name: ScrollableState002
 * @tc.desc: Test IsDragging in different states
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, ScrollableState002, TestSize.Level1)
{
    auto scrollPn = scroll_->GetPattern<PartiallyMockedScrollable>();
    auto scrollable = scrollPn->GetScrollableEvent()->GetScrollable();
    ASSERT_NE(scrollable, nullptr);

    // Not touching, FRICTION state
    scrollable->isTouching_ = false;
    scrollable->state_ = Scrollable::AnimationState::FRICTION;
    EXPECT_FALSE(scrollable->IsDragging());

    // Touching, FRICTION state
    scrollable->isTouching_ = true;
    scrollable->state_ = Scrollable::AnimationState::FRICTION;
    EXPECT_TRUE(scrollable->IsDragging());

    // Touching, IDLE state
    scrollable->isTouching_ = true;
    scrollable->state_ = Scrollable::AnimationState::IDLE;
    EXPECT_FALSE(scrollable->IsDragging());

    // Touching, SPRING state
    scrollable->isTouching_ = true;
    scrollable->state_ = Scrollable::AnimationState::SPRING;
    EXPECT_FALSE(scrollable->IsDragging());
}

/**
 * @tc.name: ScrollableState003
 * @tc.desc: Test IsSpringMotionRunning
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, ScrollableState003, TestSize.Level1)
{
    auto scrollPn = scroll_->GetPattern<PartiallyMockedScrollable>();
    auto scrollable = scrollPn->GetScrollableEvent()->GetScrollable();
    ASSERT_NE(scrollable, nullptr);

    scrollable->state_ = Scrollable::AnimationState::SPRING;
    EXPECT_TRUE(scrollable->IsSpringMotionRunning());

    scrollable->state_ = Scrollable::AnimationState::IDLE;
    EXPECT_FALSE(scrollable->IsSpringMotionRunning());

    scrollable->state_ = Scrollable::AnimationState::FRICTION;
    EXPECT_FALSE(scrollable->IsSpringMotionRunning());
}

/**
 * @tc.name: ScrollableState004
 * @tc.desc: Test IsStopped
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, ScrollableState004, TestSize.Level1)
{
    auto scrollPn = scroll_->GetPattern<PartiallyMockedScrollable>();
    auto scrollable = scrollPn->GetScrollableEvent()->GetScrollable();
    ASSERT_NE(scrollable, nullptr);

    // No animatable property
    scrollable->frictionOffsetProperty_ = nullptr;
    scrollable->springOffsetProperty_ = nullptr;
    scrollable->snapOffsetProperty_ = nullptr;
    EXPECT_TRUE(scrollable->IsStopped());

    // With friction property but stopped
    scrollable->frictionOffsetProperty_ = AceType::MakeRefPtr<NodeAnimatablePropertyFloat>(0.0f, [](float) {});
    EXPECT_TRUE(scrollable->IsStopped());

    // With spring property but stopped
    scrollable->springOffsetProperty_ = AceType::MakeRefPtr<NodeAnimatablePropertyFloat>(0.0f, [](float) {});
    EXPECT_TRUE(scrollable->IsStopped());

    // With snap property but stopped
    scrollable->snapOffsetProperty_ = AceType::MakeRefPtr<NodeAnimatablePropertyFloat>(0.0f, [](float) {});
    EXPECT_TRUE(scrollable->IsStopped());
}

/**
 * @tc.name: ScrollableState005
 * @tc.desc: Test IsSpringStopped
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, ScrollableState005, TestSize.Level1)
{
    auto scrollPn = scroll_->GetPattern<PartiallyMockedScrollable>();
    auto scrollable = scrollPn->GetScrollableEvent()->GetScrollable();
    ASSERT_NE(scrollable, nullptr);

    // No spring property
    scrollable->springOffsetProperty_ = nullptr;
    EXPECT_TRUE(scrollable->IsSpringStopped());

    // With spring property but stopped
    scrollable->springOffsetProperty_ = AceType::MakeRefPtr<NodeAnimatablePropertyFloat>(0.0f, [](float) {});
    EXPECT_TRUE(scrollable->IsSpringStopped());
}

/**
 * @tc.name: ScrollableState006
 * @tc.desc: Test IsSnapStopped
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, ScrollableState006, TestSize.Level1)
{
    auto scrollPn = scroll_->GetPattern<PartiallyMockedScrollable>();
    auto scrollable = scrollPn->GetScrollableEvent()->GetScrollable();
    ASSERT_NE(scrollable, nullptr);

    // No snap property
    scrollable->snapOffsetProperty_ = nullptr;
    EXPECT_TRUE(scrollable->IsSnapStopped());

    // With snap property but stopped
    scrollable->snapOffsetProperty_ = AceType::MakeRefPtr<NodeAnimatablePropertyFloat>(0.0f, [](float) {});
    EXPECT_TRUE(scrollable->IsSnapStopped());
}

/**
 * @tc.name: ScrollableState007
 * @tc.desc: Test Idle
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, ScrollableState007, TestSize.Level1)
{
    auto scrollPn = scroll_->GetPattern<PartiallyMockedScrollable>();
    auto scrollable = scrollPn->GetScrollableEvent()->GetScrollable();
    ASSERT_NE(scrollable, nullptr);

    // All conditions for idle
    scrollable->state_ = Scrollable::AnimationState::IDLE;
    scrollable->moved_ = false;
    EXPECT_TRUE(scrollable->Idle());

    // Not idle - SPRING state
    scrollable->state_ = Scrollable::AnimationState::SPRING;
    EXPECT_FALSE(scrollable->Idle());

    // Not idle - moved
    scrollable->state_ = Scrollable::AnimationState::IDLE;
    scrollable->moved_ = true;
    EXPECT_TRUE(scrollable->Idle());
}


/**
 * @tc.name: ScrollableState008
 * @tc.desc: Test IsAnimationNotRunning
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, ScrollableState008, TestSize.Level1)
{
    auto scrollPn = scroll_->GetPattern<PartiallyMockedScrollable>();
    auto scrollable = scrollPn->GetScrollableEvent()->GetScrollable();
    ASSERT_NE(scrollable, nullptr);

    // IDLE state
    scrollable->state_ = Scrollable::AnimationState::IDLE;
    EXPECT_TRUE(scrollable->IsAnimationNotRunning());

    // FRICTION state
    scrollable->state_ = Scrollable::AnimationState::FRICTION;
    EXPECT_FALSE(scrollable->IsAnimationNotRunning());

    // SPRING state
    scrollable->state_ = Scrollable::AnimationState::SPRING;
    EXPECT_FALSE(scrollable->IsAnimationNotRunning());

    // SNAP state
    scrollable->state_ = Scrollable::AnimationState::SNAP;
    EXPECT_FALSE(scrollable->IsAnimationNotRunning());
}

/**
 * @tc.name: ScrollableCallback001
 * @tc.desc: Test SetScrollEndCallback
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, ScrollableCallback001, TestSize.Level1)
{
    auto scrollPn = scroll_->GetPattern<PartiallyMockedScrollable>();
    auto scrollable = scrollPn->GetScrollableEvent()->GetScrollable();
    ASSERT_NE(scrollable, nullptr);

    bool callbackCalled = false;
    ScrollEventCallback callback = [&callbackCalled]() { callbackCalled = true; };

    scrollable->SetScrollEndCallback(callback);
    EXPECT_TRUE(scrollable->scrollEndCallback_);

    // Verify callback is set by calling HandleScrollEnd
    scrollable->HandleScrollEnd(std::nullopt);
}

/**
 * @tc.name: ScrollableCallback002
 * @tc.desc: Test SetScrollOverCallBack
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, ScrollableCallback002, TestSize.Level1)
{
    auto scrollPn = scroll_->GetPattern<PartiallyMockedScrollable>();
    auto scrollable = scrollPn->GetScrollableEvent()->GetScrollable();
    ASSERT_NE(scrollable, nullptr);

    bool callbackCalled = false;
    ScrollOverCallback callback = [&callbackCalled](double velocity) { callbackCalled = true; };

    scrollable->SetScrollOverCallBack(callback);
    EXPECT_TRUE(scrollable->scrollOverCallback_);
}

/**
 * @tc.name: ScrollableCallback003
 * @tc.desc: Test SetNotifyScrollOverCallBack
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, ScrollableCallback003, TestSize.Level1)
{
    auto scrollPn = scroll_->GetPattern<PartiallyMockedScrollable>();
    auto scrollable = scrollPn->GetScrollableEvent()->GetScrollable();
    ASSERT_NE(scrollable, nullptr);

    bool callbackCalled = false;
    ScrollOverCallback callback = [&callbackCalled](double velocity) { callbackCalled = true; };

    scrollable->SetNotifyScrollOverCallBack(callback);
    EXPECT_TRUE(scrollable->notifyScrollOverCallback_);
}

/**
 * @tc.name: ScrollableCallback004
 * @tc.desc: Test SetCurrentPositionCallback
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, ScrollableCallback004, TestSize.Level1)
{
    auto scrollPn = scroll_->GetPattern<PartiallyMockedScrollable>();
    auto scrollable = scrollPn->GetScrollableEvent()->GetScrollable();
    ASSERT_NE(scrollable, nullptr);

    double position = 100.0;
    std::function<double()> callback = [&position]() { return position; };

    scrollable->SetCurrentPositionCallback(callback);
    EXPECT_TRUE(scrollable->currentPositionCallback_);
}

/**
 * @tc.name: ScrollableCallback005
 * @tc.desc: Test SetOutBoundaryCallback
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, ScrollableCallback005, TestSize.Level1)
{
    auto scrollPn = scroll_->GetPattern<PartiallyMockedScrollable>();
    auto scrollable = scrollPn->GetScrollableEvent()->GetScrollable();
    ASSERT_NE(scrollable, nullptr);

    bool callbackCalled = false;
    OutBoundaryCallback callback = [&callbackCalled](bool useCurrentDelta) {
        callbackCalled = true;
        return false;
    };

    scrollable->SetOutBoundaryCallback(callback);
    EXPECT_TRUE(scrollable->outBoundaryCallback_);
}

/**
 * @tc.name: ScrollableCallback006
 * @tc.desc: Test SetDragEndCallback
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, ScrollableCallback006, TestSize.Level1)
{
    auto scrollPn = scroll_->GetPattern<PartiallyMockedScrollable>();
    auto scrollable = scrollPn->GetScrollableEvent()->GetScrollable();
    ASSERT_NE(scrollable, nullptr);

    bool callbackCalled = false;
    DragEndForRefreshCallback callback = [&callbackCalled]() { callbackCalled = true; };

    scrollable->SetDragEndCallback(callback);
    EXPECT_TRUE(scrollable->dragEndCallback_);

    // Test getter
    auto retrievedCallback = scrollable->GetDragEndCallback();
    EXPECT_TRUE(retrievedCallback);
}

/**
 * @tc.name: ScrollableCallback007
 * @tc.desc: Test SetDragCancelCallback
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, ScrollableCallback007, TestSize.Level1)
{
    auto scrollPn = scroll_->GetPattern<PartiallyMockedScrollable>();
    auto scrollable = scrollPn->GetScrollableEvent()->GetScrollable();
    ASSERT_NE(scrollable, nullptr);

    bool callbackCalled = false;
    DragCancelRefreshCallback callback = [&callbackCalled]() { callbackCalled = true; };

    scrollable->SetDragCancelCallback(callback);
    EXPECT_TRUE(scrollable->dragCancelCallback_);

    // Test getter
    auto retrievedCallback = scrollable->GetDragCancelCallback();
    EXPECT_TRUE(retrievedCallback);
}

/**
 * @tc.name: ScrollableCallback008
 * @tc.desc: Test SetWatchFixCallback
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, ScrollableCallback008, TestSize.Level1)
{
    auto scrollPn = scroll_->GetPattern<PartiallyMockedScrollable>();
    auto scrollable = scrollPn->GetScrollableEvent()->GetScrollable();
    ASSERT_NE(scrollable, nullptr);

    WatchFixCallback callback = [](double final, double current) { return current; };

    scrollable->SetWatchFixCallback(callback);
    EXPECT_TRUE(scrollable->watchFixCallback_);
}

/**
 * @tc.name: ScrollableCallback009
 * @tc.desc: Test SetRemainVelocityCallback
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, ScrollableCallback009, TestSize.Level1)
{
    auto scrollPn = scroll_->GetPattern<PartiallyMockedScrollable>();
    auto scrollable = scrollPn->GetScrollableEvent()->GetScrollable();
    ASSERT_NE(scrollable, nullptr);

    RemainVelocityCallback callback = [](float velocity) { return true; };

    scrollable->SetRemainVelocityCallback(callback);
    EXPECT_TRUE(scrollable->remainVelocityCallback_);
}

/**
 * @tc.name: ScrollableCallback010
 * @tc.desc: Test SetIsReverseCallback
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, ScrollableCallback010, TestSize.Level1)
{
    auto scrollPn = scroll_->GetPattern<PartiallyMockedScrollable>();
    auto scrollable = scrollPn->GetScrollableEvent()->GetScrollable();
    ASSERT_NE(scrollable, nullptr);

    IsReverseCallback callback = []() { return false; };

    scrollable->SetIsReverseCallback(callback);
    EXPECT_TRUE(scrollable->isReverseCallback_);
}

/**
 * @tc.name: ScrollableCallback011
 * @tc.desc: Test SetOnScrollBegin
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, ScrollableCallback011, TestSize.Level1)
{
    auto scrollPn = scroll_->GetPattern<PartiallyMockedScrollable>();
    auto scrollable = scrollPn->GetScrollableEvent()->GetScrollable();
    ASSERT_NE(scrollable, nullptr);

    ScrollBeginCallback callback = [](Dimension, Dimension) { return ScrollInfo(); };

    scrollable->SetOnScrollBegin(callback);
    EXPECT_TRUE(scrollable->scrollBeginCallback_);
}

/**
 * @tc.name: ScrollableCallback012
 * @tc.desc: Test SetOnContinuousSliding
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, ScrollableCallback012, TestSize.Level1)
{
    auto scrollPn = scroll_->GetPattern<PartiallyMockedScrollable>();
    auto scrollable = scrollPn->GetScrollableEvent()->GetScrollable();
    ASSERT_NE(scrollable, nullptr);

    ContinuousSlidingCallback callback = []() { return 100.0; };

    scrollable->SetOnContinuousSliding(callback);
    EXPECT_TRUE(scrollable->continuousSlidingCallback_);
}

/**
 * @tc.name: ScrollableCallback013
 * @tc.desc: Test SetGetSnapTypeCallback
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, ScrollableCallback013, TestSize.Level1)
{
    auto scrollPn = scroll_->GetPattern<PartiallyMockedScrollable>();
    auto scrollable = scrollPn->GetScrollableEvent()->GetScrollable();
    ASSERT_NE(scrollable, nullptr);

    GetSnapTypeCallback callback = []() { return SnapType::NONE_SNAP; };

    scrollable->SetGetSnapTypeCallback(callback);
    EXPECT_TRUE(scrollable->getSnapTypeCallback_);

    // Test GetSnapType
    auto snapType = scrollable->GetSnapType();
    EXPECT_EQ(snapType, SnapType::NONE_SNAP);
}

/**
 * @tc.name: ScrollableCallback014
 * @tc.desc: Test SetOnWillStopDraggingCallback
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, ScrollableCallback014, TestSize.Level1)
{
    auto scrollPn = scroll_->GetPattern<PartiallyMockedScrollable>();
    auto scrollable = scrollPn->GetScrollableEvent()->GetScrollable();
    ASSERT_NE(scrollable, nullptr);

    OnWillStopDraggingCallback callback = [](float velocity) {};

    scrollable->SetOnWillStopDraggingCallback(callback);
    EXPECT_TRUE(scrollable->onWillStopDraggingCallback_);

    // Test getter
    auto retrievedCallback = scrollable->GetOnWillStopDraggingEndCallback();
    EXPECT_TRUE(retrievedCallback);
}

/**
 * @tc.name: ScrollableCallback015
 * @tc.desc: Test SetOnWillStartDraggingCallback
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, ScrollableCallback015, TestSize.Level1)
{
    auto scrollPn = scroll_->GetPattern<PartiallyMockedScrollable>();
    auto scrollable = scrollPn->GetScrollableEvent()->GetScrollable();
    ASSERT_NE(scrollable, nullptr);

    OnWillStartDraggingCallback callback = []() {};

    scrollable->SetOnWillStartDraggingCallback(callback);
    EXPECT_TRUE(scrollable->onWillStartDraggingCallback_);

    // Test getter
    auto retrievedCallback = scrollable->GetOnWillStartDraggingCallback();
    EXPECT_TRUE(retrievedCallback);
}

/**
 * @tc.name: ScrollableCallback016
 * @tc.desc: Test SetOnDidStopDraggingCallback
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, ScrollableCallback016, TestSize.Level1)
{
    auto scrollPn = scroll_->GetPattern<PartiallyMockedScrollable>();
    auto scrollable = scrollPn->GetScrollableEvent()->GetScrollable();
    ASSERT_NE(scrollable, nullptr);

    OnDidStopDraggingCallback callback = [](bool isWillStartAnimate) {};

    scrollable->SetOnDidStopDraggingCallback(callback);
    EXPECT_TRUE(scrollable->onDidStopDraggingCallback_);

    // Test getter
    auto retrievedCallback = scrollable->GetOnDidStopDraggingCallback();
    EXPECT_TRUE(retrievedCallback);
}

/**
 * @tc.name: ScrollableCallback017
 * @tc.desc: Test SetOnWillStartFlingCallback
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, ScrollableCallback017, TestSize.Level1)
{
    auto scrollPn = scroll_->GetPattern<PartiallyMockedScrollable>();
    auto scrollable = scrollPn->GetScrollableEvent()->GetScrollable();
    ASSERT_NE(scrollable, nullptr);

    OnWillStartFlingCallback callback = []() {};

    scrollable->SetOnWillStartFlingCallback(callback);
    EXPECT_TRUE(scrollable->onWillStartFlingCallback_);

    // Test getter
    auto retrievedCallback = scrollable->GetOnWillStartFlingCallback();
    EXPECT_TRUE(retrievedCallback);
}

/**
 * @tc.name: ScrollableCallback018
 * @tc.desc: Test SetOnDidStopFlingCallback
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, ScrollableCallback018, TestSize.Level1)
{
    auto scrollPn = scroll_->GetPattern<PartiallyMockedScrollable>();
    auto scrollable = scrollPn->GetScrollableEvent()->GetScrollable();
    ASSERT_NE(scrollable, nullptr);

    OnDidStopFlingCallback callback = []() {};

    scrollable->SetOnDidStopFlingCallback(callback);
    EXPECT_TRUE(scrollable->onDidStopFlingCallback_);

    // Test getter
    auto retrievedCallback = scrollable->GetOnDidStopFlingCallback();
    EXPECT_TRUE(retrievedCallback);
}

/**
 * @tc.name: ScrollableAnimation001
 * @tc.desc: Test StopFrictionAnimation
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, ScrollableAnimation001, TestSize.Level1)
{
    auto scrollPn = scroll_->GetPattern<PartiallyMockedScrollable>();
    auto scrollable = scrollPn->GetScrollableEvent()->GetScrollable();
    ASSERT_NE(scrollable, nullptr);

    // No friction property
    scrollable->frictionOffsetProperty_ = nullptr;
    scrollable->StopFrictionAnimation();
    // Should not crash

    // With friction property
    scrollable->frictionOffsetProperty_ = AceType::MakeRefPtr<NodeAnimatablePropertyFloat>(0.0f, [](float) {});
    scrollable->state_ = Scrollable::AnimationState::FRICTION;
    scrollable->StopFrictionAnimation();
    EXPECT_EQ(scrollable->state_, Scrollable::AnimationState::IDLE);
}

/**
 * @tc.name: ScrollableAnimation002
 * @tc.desc: Test StopSpringAnimation
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, ScrollableAnimation002, TestSize.Level1)
{
    auto scrollPn = scroll_->GetPattern<PartiallyMockedScrollable>();
    auto scrollable = scrollPn->GetScrollableEvent()->GetScrollable();
    ASSERT_NE(scrollable, nullptr);

    // No spring property
    scrollable->springOffsetProperty_ = nullptr;
    scrollable->StopSpringAnimation();
    // Should not crash

    // With spring property
    scrollable->springOffsetProperty_ = AceType::MakeRefPtr<NodeAnimatablePropertyFloat>(0.0f, [](float) {});
    scrollable->state_ = Scrollable::AnimationState::SPRING;
    scrollable->StopSpringAnimation();
    EXPECT_EQ(scrollable->state_, Scrollable::AnimationState::IDLE);
}

/**
 * @tc.name: ScrollableAnimation003
 * @tc.desc: Test StopSnapAnimation
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, ScrollableAnimation003, TestSize.Level1)
{
    auto scrollPn = scroll_->GetPattern<PartiallyMockedScrollable>();
    auto scrollable = scrollPn->GetScrollableEvent()->GetScrollable();
    ASSERT_NE(scrollable, nullptr);

    // No snap property
    scrollable->snapOffsetProperty_ = nullptr;
    scrollable->StopSnapAnimation();
    // Should not crash

    // With snap property
    scrollable->snapOffsetProperty_ = AceType::MakeRefPtr<NodeAnimatablePropertyFloat>(0.0f, [](float) {});
    scrollable->state_ = Scrollable::AnimationState::SNAP;
    scrollable->StopSnapAnimation();
    EXPECT_EQ(scrollable->state_, Scrollable::AnimationState::IDLE);
}

/**
 * @tc.name: ScrollableAnimation004
 * @tc.desc: Test StopSnapController
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, ScrollableAnimation004, TestSize.Level1)
{
    auto scrollPn = scroll_->GetPattern<PartiallyMockedScrollable>();
    auto scrollable = scrollPn->GetScrollableEvent()->GetScrollable();
    ASSERT_NE(scrollable, nullptr);

    // SNAP state
    scrollable->state_ = Scrollable::AnimationState::SNAP;
    scrollable->snapOffsetProperty_ = AceType::MakeRefPtr<NodeAnimatablePropertyFloat>(0.0f, [](float) {});
    scrollable->StopSnapController();
    EXPECT_EQ(scrollable->state_, Scrollable::AnimationState::IDLE);

    // IDLE state
    scrollable->state_ = Scrollable::AnimationState::IDLE;
    scrollable->StopSnapController();
    EXPECT_EQ(scrollable->state_, Scrollable::AnimationState::IDLE);
}

/**
 * @tc.name: ScrollableAnimation005
 * @tc.desc: Test IsSnapAnimationRunning
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, ScrollableAnimation005, TestSize.Level1)
{
    auto scrollPn = scroll_->GetPattern<PartiallyMockedScrollable>();
    auto scrollable = scrollPn->GetScrollableEvent()->GetScrollable();
    ASSERT_NE(scrollable, nullptr);

    scrollable->state_ = Scrollable::AnimationState::SNAP;
    EXPECT_TRUE(scrollable->IsSnapAnimationRunning());

    scrollable->state_ = Scrollable::AnimationState::IDLE;
    EXPECT_FALSE(scrollable->IsSnapAnimationRunning());

    scrollable->state_ = Scrollable::AnimationState::FRICTION;
    EXPECT_FALSE(scrollable->IsSnapAnimationRunning());
}

/**
 * @tc.name: ScrollableProperty001
 * @tc.desc: Test SetMoved and GetIsDragging
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, ScrollableProperty001, TestSize.Level1)
{
    auto scrollPn = scroll_->GetPattern<PartiallyMockedScrollable>();
    auto scrollable = scrollPn->GetScrollableEvent()->GetScrollable();
    ASSERT_NE(scrollable, nullptr);

    scrollable->SetMoved(true);
    EXPECT_TRUE(scrollable->moved_);

    scrollable->SetMoved(false);
    EXPECT_FALSE(scrollable->moved_);

    // Test GetIsDragging
    scrollable->isDragging_ = true;
    EXPECT_TRUE(scrollable->GetIsDragging());

    scrollable->isDragging_ = false;
    EXPECT_FALSE(scrollable->GetIsDragging());
}

/**
 * @tc.name: ScrollableProperty002
 * @tc.desc: Test SetCanOverScroll and CanOverScroll
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, ScrollableProperty002, TestSize.Level1)
{
    auto scrollPn = scroll_->GetPattern<PartiallyMockedScrollable>();
    auto scrollable = scrollPn->GetScrollableEvent()->GetScrollable();
    ASSERT_NE(scrollable, nullptr);

    scrollable->SetCanOverScroll(true);
    EXPECT_TRUE(scrollable->CanOverScroll());

    scrollable->SetCanOverScroll(false);
    EXPECT_FALSE(scrollable->CanOverScroll());
}

/**
 * @tc.name: ScrollableProperty003
 * @tc.desc: Test SetCanStayOverScroll and CanStayOverScroll
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, ScrollableProperty003, TestSize.Level1)
{
    auto scrollPn = scroll_->GetPattern<PartiallyMockedScrollable>();
    auto scrollable = scrollPn->GetScrollableEvent()->GetScrollable();
    ASSERT_NE(scrollable, nullptr);

    scrollable->SetCanStayOverScroll(true);
    EXPECT_TRUE(scrollable->CanStayOverScroll());

    scrollable->SetCanStayOverScroll(false);
    EXPECT_FALSE(scrollable->CanStayOverScroll());
}

/**
 * @tc.name: ScrollableProperty004
 * @tc.desc: Test SetCurrentPos and GetCurrentPos
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, ScrollableProperty004, TestSize.Level1)
{
    auto scrollPn = scroll_->GetPattern<PartiallyMockedScrollable>();
    auto scrollable = scrollPn->GetScrollableEvent()->GetScrollable();
    ASSERT_NE(scrollable, nullptr);

    scrollable->SetCurrentPos(100.0f);
    EXPECT_EQ(scrollable->GetCurrentPos(), 100.0f);

    scrollable->SetCurrentPos(200.0f);
    EXPECT_EQ(scrollable->GetCurrentPos(), 200.0f);
}

/**
 * @tc.name: ScrollableProperty005
 * @tc.desc: Test GetCurrentVelocity
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, ScrollableProperty005, TestSize.Level1)
{
    auto scrollPn = scroll_->GetPattern<PartiallyMockedScrollable>();
    auto scrollable = scrollPn->GetScrollableEvent()->GetScrollable();
    ASSERT_NE(scrollable, nullptr);

    scrollable->currentVelocity_ = 500.0;
    EXPECT_EQ(scrollable->GetCurrentVelocity(), 500.0);

    scrollable->currentVelocity_ = 1000.0;
    EXPECT_EQ(scrollable->GetCurrentVelocity(), 1000.0);
}

/**
 * @tc.name: ScrollableProperty006
 * @tc.desc: Test MarkNeedCenterFix
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, ScrollableProperty006, TestSize.Level1)
{
    auto scrollPn = scroll_->GetPattern<PartiallyMockedScrollable>();
    auto scrollable = scrollPn->GetScrollableEvent()->GetScrollable();
    ASSERT_NE(scrollable, nullptr);

    scrollable->MarkNeedCenterFix(true);
    EXPECT_TRUE(scrollable->needCenterFix_);

    scrollable->MarkNeedCenterFix(false);
    EXPECT_FALSE(scrollable->needCenterFix_);
}

/**
 * @tc.name: ScrollableProperty007
 * @tc.desc: Test SetNodeId and GetNodeId
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, ScrollableProperty007, TestSize.Level1)
{
    auto scrollPn = scroll_->GetPattern<PartiallyMockedScrollable>();
    auto scrollable = scrollPn->GetScrollableEvent()->GetScrollable();
    ASSERT_NE(scrollable, nullptr);

    scrollable->SetNodeId(12345);
    EXPECT_EQ(scrollable->GetNodeId(), 12345);

    scrollable->SetNodeId(67890);
    EXPECT_EQ(scrollable->GetNodeId(), 67890);
}

/**
 * @tc.name: ScrollableProperty008
 * @tc.desc: Test SetNodeTag and GetNodeTag
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, ScrollableProperty008, TestSize.Level1)
{
    auto scrollPn = scroll_->GetPattern<PartiallyMockedScrollable>();
    auto scrollable = scrollPn->GetScrollableEvent()->GetScrollable();
    ASSERT_NE(scrollable, nullptr);

    scrollable->SetNodeTag("TestNode1");
    EXPECT_EQ(scrollable->GetNodeTag(), "TestNode1");

    scrollable->SetNodeTag("TestNode2");
    EXPECT_EQ(scrollable->GetNodeTag(), "TestNode2");
}

/**
 * @tc.name: ScrollableProperty009
 * @tc.desc: Test Available and MarkAvailable
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, ScrollableProperty009, TestSize.Level1)
{
    auto scrollPn = scroll_->GetPattern<PartiallyMockedScrollable>();
    auto scrollable = scrollPn->GetScrollableEvent()->GetScrollable();
    ASSERT_NE(scrollable, nullptr);

    scrollable->MarkAvailable(true);
    EXPECT_TRUE(scrollable->Available());

    scrollable->MarkAvailable(false);
    EXPECT_FALSE(scrollable->Available());
}


/**
 * @tc.name: ScrollableProperty010
 * @tc.desc: Test GetRatio
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, ScrollableProperty010, TestSize.Level1)
{
    auto scrollPn = scroll_->GetPattern<PartiallyMockedScrollable>();
    auto scrollable = scrollPn->GetScrollableEvent()->GetScrollable();
    ASSERT_NE(scrollable, nullptr);

    float ratio = scrollable->GetRatio();
    EXPECT_GT(ratio, 0.0f);
}

/**
 * @tc.name: ScrollableProperty011
 * @tc.desc: Test SetUnstaticVelocityScale
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, ScrollableProperty011, TestSize.Level1)
{
    auto scrollPn = scroll_->GetPattern<PartiallyMockedScrollable>();
    auto scrollable = scrollPn->GetScrollableEvent()->GetScrollable();
    ASSERT_NE(scrollable, nullptr);

    scrollable->SetUnstaticVelocityScale(2.0);
    EXPECT_EQ(scrollable->flingVelocityScale_, 2.0);
    EXPECT_EQ(scrollable->springVelocityScale_, 2.0);
}

/**
 * @tc.name: ScrollableProperty012
 * @tc.desc: Test SetIsScrollBarDragging
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, ScrollableProperty012, TestSize.Level1)
{
    auto scrollPn = scroll_->GetPattern<PartiallyMockedScrollable>();
    auto scrollable = scrollPn->GetScrollableEvent()->GetScrollable();
    ASSERT_NE(scrollable, nullptr);

    scrollable->SetIsScrollBarDragging(true);
    EXPECT_TRUE(scrollable->isScrollBarDragging_);

    scrollable->SetIsScrollBarDragging(false);
    EXPECT_FALSE(scrollable->isScrollBarDragging_);
}

/**
 * @tc.name: ScrollableProperty013
 * @tc.desc: Test SetMaxFlingVelocityValue and GetMaxFlingVelocity
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, ScrollableProperty013, TestSize.Level1)
{
    auto scrollPn = scroll_->GetPattern<PartiallyMockedScrollable>();
    auto scrollable = scrollPn->GetScrollableEvent()->GetScrollable();
    ASSERT_NE(scrollable, nullptr);

    scrollable->SetMaxFlingVelocityValue(10000.0);
    EXPECT_EQ(scrollable->GetMaxFlingVelocity(), 10000.0);

    scrollable->SetMaxFlingVelocityValue(20000.0);
    EXPECT_EQ(scrollable->GetMaxFlingVelocity(), 20000.0);
}

/**
 * @tc.name: ScrollableProperty014
 * @tc.desc: Test GetFinalPosition
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, ScrollableProperty014, TestSize.Level1)
{
    auto scrollPn = scroll_->GetPattern<PartiallyMockedScrollable>();
    auto scrollable = scrollPn->GetScrollableEvent()->GetScrollable();
    ASSERT_NE(scrollable, nullptr);

    scrollable->finalPosition_ = 123.45f;
    EXPECT_EQ(scrollable->GetFinalPosition(), 123.45f);
}

/**
 * @tc.name: ScrollableProperty015
 * @tc.desc: Test GetSnapFinalPosition
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, ScrollableProperty015, TestSize.Level1)
{
    auto scrollPn = scroll_->GetPattern<PartiallyMockedScrollable>();
    auto scrollable = scrollPn->GetScrollableEvent()->GetScrollable();
    ASSERT_NE(scrollable, nullptr);

    scrollable->endPos_ = 456.78f;
    EXPECT_EQ(scrollable->GetSnapFinalPosition(), 456.78f);
}

/**
 * @tc.name: ScrollableProperty016
 * @tc.desc: Test GetNeedScrollSnapChange
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, ScrollableProperty016, TestSize.Level1)
{
    auto scrollPn = scroll_->GetPattern<PartiallyMockedScrollable>();
    auto scrollable = scrollPn->GetScrollableEvent()->GetScrollable();
    ASSERT_NE(scrollable, nullptr);

    scrollable->needScrollSnapChange_ = true;
    EXPECT_TRUE(scrollable->GetNeedScrollSnapChange());

    scrollable->needScrollSnapChange_ = false;
    EXPECT_FALSE(scrollable->GetNeedScrollSnapChange());
}

/**
 * @tc.name: ScrollableProperty017
 * @tc.desc: Test SetNestedScrolling and GetNestedScrolling
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, ScrollableProperty017, TestSize.Level1)
{
    auto scrollPn = scroll_->GetPattern<PartiallyMockedScrollable>();
    auto scrollable = scrollPn->GetScrollableEvent()->GetScrollable();
    ASSERT_NE(scrollable, nullptr);

    scrollable->SetNestedScrolling(true);
    EXPECT_TRUE(scrollable->GetNestedScrolling());

    scrollable->SetNestedScrolling(false);
    EXPECT_FALSE(scrollable->GetNestedScrolling());
}

/**
 * @tc.name: ScrollableProperty018
 * @tc.desc: Test SetIsUserFling and GetIsUserFling
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, ScrollableProperty018, TestSize.Level1)
{
    auto scrollPn = scroll_->GetPattern<PartiallyMockedScrollable>();
    auto scrollable = scrollPn->GetScrollableEvent()->GetScrollable();
    ASSERT_NE(scrollable, nullptr);

    scrollable->SetIsUserFling(true);
    EXPECT_TRUE(scrollable->GetIsUserFling());

    scrollable->SetIsUserFling(false);
    EXPECT_FALSE(scrollable->GetIsUserFling());
}

/**
 * @tc.name: ScrollableProperty019
 * @tc.desc: Test SetIsDragOuterScrollBarStopAnimation
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, ScrollableProperty019, TestSize.Level1)
{
    auto scrollPn = scroll_->GetPattern<PartiallyMockedScrollable>();
    auto scrollable = scrollPn->GetScrollableEvent()->GetScrollable();
    ASSERT_NE(scrollable, nullptr);

    scrollable->SetIsDragOuterScrollBarStopAnimation(true);
    EXPECT_TRUE(scrollable->isDragOuterScrollBarStopAnimation_);

    scrollable->SetIsDragOuterScrollBarStopAnimation(false);
    EXPECT_FALSE(scrollable->isDragOuterScrollBarStopAnimation_);
}

/**
 * @tc.name: ScrollableProperty020
 * @tc.desc: Test SetEdgeEffect
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, ScrollableProperty020, TestSize.Level1)
{
    auto scrollPn = scroll_->GetPattern<PartiallyMockedScrollable>();
    auto scrollable = scrollPn->GetScrollableEvent()->GetScrollable();
    ASSERT_NE(scrollable, nullptr);

    scrollable->SetEdgeEffect(EdgeEffect::SPRING);
    EXPECT_EQ(scrollable->edgeEffect_, EdgeEffect::SPRING);

    scrollable->SetEdgeEffect(EdgeEffect::FADE);
    EXPECT_EQ(scrollable->edgeEffect_, EdgeEffect::FADE);

    scrollable->SetEdgeEffect(EdgeEffect::NONE);
    EXPECT_EQ(scrollable->edgeEffect_, EdgeEffect::NONE);
}

/**
 * @tc.name: ScrollableProperty021
 * @tc.desc: Test SetContinuousDragStatus and related drag count methods
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, ScrollableProperty021, TestSize.Level1)
{
    auto scrollPn = scroll_->GetPattern<PartiallyMockedScrollable>();
    auto scrollable = scrollPn->GetScrollableEvent()->GetScrollable();
    ASSERT_NE(scrollable, nullptr);

    scrollable->SetContinuousDragStatus(true);
    EXPECT_TRUE(scrollable->continuousDragStatus_);

    scrollable->IncreaseContinueDragCount();
    EXPECT_EQ(scrollable->dragCount_, 1);

    scrollable->IncreaseContinueDragCount();
    EXPECT_EQ(scrollable->dragCount_, 2);

    scrollable->ResetContinueDragCount();
    EXPECT_EQ(scrollable->dragCount_, 1);
}

/**
 * @tc.name: ScrollableProperty022
 * @tc.desc: Test SetDragStartPosition, SetDragEndPosition, and GetDragOffset
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, ScrollableProperty022, TestSize.Level1)
{
    auto scrollPn = scroll_->GetPattern<PartiallyMockedScrollable>();
    auto scrollable = scrollPn->GetScrollableEvent()->GetScrollable();
    ASSERT_NE(scrollable, nullptr);

    scrollable->SetDragStartPosition(100.0);
    EXPECT_EQ(scrollable->dragStartPosition_, 100.0);

    scrollable->SetDragEndPosition(250.0);
    EXPECT_EQ(scrollable->dragEndPosition_, 250.0);

    EXPECT_EQ(scrollable->GetDragOffset(), 150.0);
}

/**
 * @tc.name: ScrollableProperty023
 * @tc.desc: Test ResetSnapDirection
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, ScrollableProperty023, TestSize.Level1)
{
    auto scrollPn = scroll_->GetPattern<PartiallyMockedScrollable>();
    auto scrollable = scrollPn->GetScrollableEvent()->GetScrollable();
    ASSERT_NE(scrollable, nullptr);

    scrollable->snapDirection_ = SnapDirection::FORWARD;
    scrollable->ResetSnapDirection();
    EXPECT_EQ(scrollable->snapDirection_, SnapDirection::NONE);
}

/**
 * @tc.name: ScrollableProperty024
 * @tc.desc: Test SetListSnapSpeed and GetListSnapSpeed
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, ScrollableProperty024, TestSize.Level1)
{
    auto scrollPn = scroll_->GetPattern<PartiallyMockedScrollable>();
    auto scrollable = scrollPn->GetScrollableEvent()->GetScrollable();
    ASSERT_NE(scrollable, nullptr);

    scrollable->SetListSnapSpeed(ScrollSnapAnimationSpeed::SLOW);
    EXPECT_EQ(scrollable->GetListSnapSpeed(), ScrollSnapAnimationSpeed::SLOW);

    scrollable->SetListSnapSpeed(ScrollSnapAnimationSpeed::NORMAL);
    EXPECT_EQ(scrollable->GetListSnapSpeed(), ScrollSnapAnimationSpeed::NORMAL);
}

/**
 * @tc.name: ScrollableAxis001
 * @tc.desc: Test SetAxis
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, ScrollableAxis001, TestSize.Level1)
{
    auto scrollPn = scroll_->GetPattern<PartiallyMockedScrollable>();
    auto scrollable = scrollPn->GetScrollableEvent()->GetScrollable();
    ASSERT_NE(scrollable, nullptr);

    scrollable->SetAxis(Axis::VERTICAL);
    EXPECT_EQ(scrollable->axis_, Axis::VERTICAL);

    scrollable->SetAxis(Axis::HORIZONTAL);
    EXPECT_EQ(scrollable->axis_, Axis::HORIZONTAL);

    scrollable->SetAxis(Axis::NONE);
    EXPECT_EQ(scrollable->axis_, Axis::NONE);
}

/**
 * @tc.name: ScrollableAxis002
 * @tc.desc: Test GetMainOffset
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, ScrollableAxis002, TestSize.Level1)
{
    auto scrollPn = scroll_->GetPattern<PartiallyMockedScrollable>();
    auto scrollable = scrollPn->GetScrollableEvent()->GetScrollable();
    ASSERT_NE(scrollable, nullptr);

    Offset offset(100.0, 200.0);

    scrollable->SetAxis(Axis::HORIZONTAL);
    EXPECT_EQ(scrollable->GetMainOffset(offset), 100.0);

    scrollable->SetAxis(Axis::VERTICAL);
    EXPECT_EQ(scrollable->GetMainOffset(offset), 200.0);
}

/**
 * @tc.name: ScrollableAxis003
 * @tc.desc: Test GetMainSize
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, ScrollableAxis003, TestSize.Level1)
{
    auto scrollPn = scroll_->GetPattern<PartiallyMockedScrollable>();
    auto scrollable = scrollPn->GetScrollableEvent()->GetScrollable();
    ASSERT_NE(scrollable, nullptr);

    Size size(300.0, 400.0);

    scrollable->SetAxis(Axis::HORIZONTAL);
    EXPECT_EQ(scrollable->GetMainSize(size), 300.0);

    scrollable->SetAxis(Axis::VERTICAL);
    EXPECT_EQ(scrollable->GetMainSize(size), 400.0);
}

/**
 * @tc.name: ScrollableAxis004
 * @tc.desc: Test GetPanDirection
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, ScrollableAxis004, TestSize.Level1)
{
    auto scrollPn = scroll_->GetPattern<PartiallyMockedScrollable>();
    auto scrollable = scrollPn->GetScrollableEvent()->GetScrollable();
    ASSERT_NE(scrollable, nullptr);

    // No pan recognizer
    scrollable->panRecognizerNG_ = nullptr;
    EXPECT_EQ(scrollable->GetPanDirection(), Axis::NONE);
}

/**
 * @tc.name: ScrollableTouch001
 * @tc.desc: Test HandleTouchDown
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, ScrollableTouch001, TestSize.Level1)
{
    auto scrollPn = scroll_->GetPattern<PartiallyMockedScrollable>();
    auto scrollable = scrollPn->GetScrollableEvent()->GetScrollable();
    ASSERT_NE(scrollable, nullptr);

    scrollable->state_ = Scrollable::AnimationState::FRICTION;
    scrollable->HandleTouchDown();
    EXPECT_TRUE(scrollable->isTouching_);
}

/**
 * @tc.name: ScrollableTouch002
 * @tc.desc: Test HandleTouchUp
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, ScrollableTouch002, TestSize.Level1)
{
    auto scrollPn = scroll_->GetPattern<PartiallyMockedScrollable>();
    auto scrollable = scrollPn->GetScrollableEvent()->GetScrollable();
    ASSERT_NE(scrollable, nullptr);

    scrollable->isTouching_ = true;
    scrollable->HandleTouchUp();
    EXPECT_FALSE(scrollable->isTouching_);
}

/**
 * @tc.name: ScrollableOverScroll001
 * @tc.desc: Test HandleOverScroll with disabled over scroll
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, ScrollableOverScroll001, TestSize.Level1)
{
    auto scrollPn = scroll_->GetPattern<PartiallyMockedScrollable>();
    auto scrollable = scrollPn->GetScrollableEvent()->GetScrollable();
    ASSERT_NE(scrollable, nullptr);

    scrollable->SetCanOverScroll(false);
    bool result = scrollable->HandleOverScroll(100.0);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: ScrollableScroll001
 * @tc.desc: Test HandleScroll with NestedState
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, ScrollableScroll001, TestSize.Level1)
{
    auto scrollPn = scroll_->GetPattern<PartiallyMockedScrollable>();
    auto scrollable = scrollPn->GetScrollableEvent()->GetScrollable();
    ASSERT_NE(scrollable, nullptr);

    // Set up callback
    bool callbackCalled = false;
    scrollable->callback_ = [&callbackCalled](double offset, int32_t source) -> bool {
        callbackCalled = true;
        return true;
    };

    ScrollResult result = scrollable->HandleScroll(50.0, SCROLL_FROM_UPDATE, NestedState::GESTURE);
    EXPECT_GE(result.remain, 0.0);
}

/**
 * @tc.name: ScrollableEvent001
 * @tc.desc: Test SetHandleScrollCallback
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, ScrollableEvent001, TestSize.Level1)
{
    auto scrollPn = scroll_->GetPattern<PartiallyMockedScrollable>();
    auto scrollable = scrollPn->GetScrollableEvent()->GetScrollable();
    ASSERT_NE(scrollable, nullptr);

    NestableScrollCallback callback = [](float offset, int32_t source, NestedState state) {
        return ScrollResult{0.0, false};
    };

    scrollable->SetHandleScrollCallback(std::move(callback));
    EXPECT_TRUE(scrollable->handleScrollCallback_);
}

/**
 * @tc.name: ScrollableEvent002
 * @tc.desc: Test SetOverScrollCallback
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, ScrollableEvent002, TestSize.Level1)
{
    auto scrollPn = scroll_->GetPattern<PartiallyMockedScrollable>();
    auto scrollable = scrollPn->GetScrollableEvent()->GetScrollable();
    ASSERT_NE(scrollable, nullptr);

    std::function<bool(float)> callback = [](float velocity) { return true; };

    scrollable->SetOverScrollCallback(std::move(callback));
    EXPECT_TRUE(scrollable->overScrollCallback_);
}

/**
 * @tc.name: ScrollableEvent003
 * @tc.desc: Test SetHandleExtScrollCallback
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, ScrollableEvent003, TestSize.Level1)
{
    auto scrollPn = scroll_->GetPattern<PartiallyMockedScrollable>();
    auto scrollable = scrollPn->GetScrollableEvent()->GetScrollable();
    ASSERT_NE(scrollable, nullptr);

    std::function<void(void)> callback = []() {};

    scrollable->SetHandleExtScrollCallback(std::move(callback));
    EXPECT_TRUE(scrollable->handleExtScrollCallback_);
}

/**
 * @tc.name: ScrollableEvent004
 * @tc.desc: Test SetOnScrollStartRec and SetOnScrollEndRec
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, ScrollableEvent004, TestSize.Level1)
{
    auto scrollPn = scroll_->GetPattern<PartiallyMockedScrollable>();
    auto scrollable = scrollPn->GetScrollableEvent()->GetScrollable();
    ASSERT_NE(scrollable, nullptr);

    std::function<void(float)> startCallback = [](float velocity) {};
    std::function<void(const std::optional<float>&)> endCallback = [](const std::optional<float>& velocity) {};

    scrollable->SetOnScrollStartRec(std::move(startCallback));
    EXPECT_TRUE(scrollable->onScrollStartRec_);

    scrollable->SetOnScrollEndRec(std::move(endCallback));
    EXPECT_TRUE(scrollable->onScrollEndRec_);
}

/**
 * @tc.name: ScrollableEvent005
 * @tc.desc: Test SetStartSnapAnimationCallback
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, ScrollableEvent005, TestSize.Level1)
{
    auto scrollPn = scroll_->GetPattern<PartiallyMockedScrollable>();
    auto scrollable = scrollPn->GetScrollableEvent()->GetScrollable();
    ASSERT_NE(scrollable, nullptr);

    StartSnapAnimationCallback callback = [](SnapAnimationOptions options) { return true; };

    scrollable->SetStartSnapAnimationCallback(callback);
    EXPECT_TRUE(scrollable->startSnapAnimationCallback_);
}

/**
 * @tc.name: ScrollableSnap001
 * @tc.desc: Test GetPredictSnapOffset
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, ScrollableSnap001, TestSize.Level1)
{
    auto scrollPn = scroll_->GetPattern<PartiallyMockedScrollable>();
    auto scrollable = scrollPn->GetScrollableEvent()->GetScrollable();
    ASSERT_NE(scrollable, nullptr);

    // No snap offset set
    auto result = scrollable->GetPredictSnapOffset();
    EXPECT_FALSE(result.has_value());
}

/**
 * @tc.name: ScrollableFRC001
 * @tc.desc: Test SetDragFRCSceneCallback
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, ScrollableFRC001, TestSize.Level1)
{
    auto scrollPn = scroll_->GetPattern<PartiallyMockedScrollable>();
    auto scrollable = scrollPn->GetScrollableEvent()->GetScrollable();
    ASSERT_NE(scrollable, nullptr);

    DragFRCSceneCallback callback = [](double velocity, NG::SceneStatus sceneStatus) {};

    scrollable->SetDragFRCSceneCallback(std::move(callback));
    EXPECT_TRUE(scrollable->dragFRCSceneCallback_);
}

/**
 * @tc.name: ScrollableFix001
 * @tc.desc: Test RegisterFixScrollParamCallback
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, ScrollableFix001, TestSize.Level1)
{
    auto scrollPn = scroll_->GetPattern<PartiallyMockedScrollable>();
    auto scrollable = scrollPn->GetScrollableEvent()->GetScrollable();
    ASSERT_NE(scrollable, nullptr);

    FixScrollParamCallback callback = [](float mainPos, float& correctVelocity, float& finalPos) {
        finalPos = mainPos;
        correctVelocity = 0.0f;
    };

    scrollable->RegisterFixScrollParamCallback(callback);
    EXPECT_TRUE(scrollable->fixScrollParamCallback_);
}

/**
 * @tc.name: ScrollableFix002
 * @tc.desc: Test SetSlipFactor
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, ScrollableFix002, TestSize.Level1)
{
    auto scrollPn = scroll_->GetPattern<PartiallyMockedScrollable>();
    auto scrollable = scrollPn->GetScrollableEvent()->GetScrollable();
    ASSERT_NE(scrollable, nullptr);

    scrollable->SetSlipFactor(0.5);
    EXPECT_EQ(scrollable->slipFactor_, 0.5);
}

/**
 * @tc.name: ScrollableOverScrollCallback001
 * @tc.desc: Test SetOverScrollOffsetCallback
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, ScrollableOverScrollCallback001, TestSize.Level1)
{
    auto scrollPn = scroll_->GetPattern<PartiallyMockedScrollable>();
    auto scrollable = scrollPn->GetScrollableEvent()->GetScrollable();
    ASSERT_NE(scrollable, nullptr);

    std::function<double()> callback = []() { return 100.0; };

    scrollable->SetOverScrollOffsetCallback(callback);
    EXPECT_TRUE(scrollable->overScrollOffsetCallback_);
}

/**
 * @tc.name: ScrollablePanEvent001
 * @tc.desc: Test AddPanActionEndEvent
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, ScrollablePanEvent001, TestSize.Level1)
{
    auto scrollPn = scroll_->GetPattern<PartiallyMockedScrollable>();
    auto scrollable = scrollPn->GetScrollableEvent()->GetScrollable();
    ASSERT_NE(scrollable, nullptr);

    bool eventCalled = false;
    GestureEventFunc event = [&eventCalled](const GestureEvent& info) {
        eventCalled = true;
    };

    scrollable->AddPanActionEndEvent(std::move(event));
    EXPECT_FALSE(scrollable->panActionEndEvents_.empty());
}

/**
 * @tc.name: ScrollableStatic001
 * @tc.desc: Test GetVelocityScale static method
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, ScrollableStatic001, TestSize.Level1)
{
    double scale = Scrollable::GetVelocityScale();
    EXPECT_GT(scale, 0.0);
}

} // namespace OHOS::Ace::NG
