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

#include "gtest/gtest.h"
#include "gtest/hwext/gtest-ext.h"

#define protected public
#define private public
#include "scrollable_fling_test_ng.h"
#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/pattern/mock_nestable_scroll_container.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/unittest/core/pattern/scrollable/mock_scrollable.h"

#include "core/components_ng/pattern/refresh/refresh_pattern.h"
#include "core/components_ng/pattern/scrollable/scrollable_properties.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {

void ScrollableFlingTestNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
    MockContainer::Current()->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
}

void ScrollableFlingTestNg::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

void ScrollableFlingTestNg::SetUp()
{
    InitNestedScrolls();
}

void ScrollableFlingTestNg::TearDown()
{
    scroll_.Reset();
    mockScroll_.Reset();
}

void ScrollableFlingTestNg::InitNestedScrolls()
{
    scroll_ = FrameNode::CreateFrameNode("scroll", -1, AceType::MakeRefPtr<PartiallyMockedScrollable>());
    mockScroll_ = FrameNode::CreateFrameNode("mockScroll", -1, AceType::MakeRefPtr<MockNestableScrollContainer>());
    scroll_->MountToParent(mockScroll_);

    auto scrollPn = scroll_->GetPattern<PartiallyMockedScrollable>();
    // to enable need parent
    scrollPn->nestedScroll_ = { .forward = NestedScrollMode::PARALLEL, .backward = NestedScrollMode::PARALLEL };
    EXPECT_CALL(*(mockScroll_->GetPattern<MockNestableScrollContainer>()), GetAxis).Times(AtMost(1));

    scrollPn->AddScrollEvent();
    scrollPn->SetEdgeEffect();
}


/**
 * @tc.name: Fling001
 * @tc.desc: Test nested Fling
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableFlingTestNg, Fling001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize ScrollablePattern type pointer
     * @tc.expected: Pointer is not nullptr
     */
    auto scrollPn = scroll_->GetPattern<PartiallyMockedScrollable>();
    EXPECT_TRUE(scrollPn);

    /**
     * @tc.steps: step2. Set the correctVelocity is 3000
     * Set the friction is 0.6
     * Set the frictionScale is -4.2
     * Calculate the position finalPosition that should be scrolled to through a formula
     * Get object scrollable and Call the SetFriction method
     * Call the Fling method and pass the correctVelocity parameter
     * Obtain the actual scrolling position finalPosition_
     * @tc.expected: The values of finalPosition_ and finalPosition are the same
     */
    float correctVelocity = 3000.0f;
    float friction = 0.6f;
    float frictionScale = -4.2f;
    float finalPosition = correctVelocity / (friction * -frictionScale);
    auto scrollableEvent = scrollPn->GetScrollableEvent();
    auto scrollable = scrollableEvent->GetScrollable();
    scrollable->SetFriction(friction);
    scrollPn->Fling(correctVelocity);
    float finalPosition_ = scrollable->finalPosition_;
    EXPECT_EQ(finalPosition_, finalPosition);
}

/**
 * @tc.name: Fling002
 * @tc.desc: Test nested Fling
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableFlingTestNg, Fling002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize ScrollablePattern type pointer
     * @tc.expected: Pointer is not nullptr.
     */
    auto mockPn = AceType::MakeRefPtr<FullyMockedScrollable>();
    mockScroll_->pattern_ = mockPn;
    auto scrollPn = scroll_->GetPattern<PartiallyMockedScrollable>();
    EXPECT_TRUE(scrollPn);
    scrollPn->parent_ = mockPn;

    /**
     * @tc.steps: step2. Set the parameter scrollable to be nullptr
     * @tc.expected: Scrollable is nullptr
     */
    RefPtr<Scrollable> scrollable = nullptr;
    scrollPn->scrollableEvent_ = AceType::MakeRefPtr<ScrollableEvent>(Axis::VERTICAL);
    scrollPn->scrollableEvent_->SetScrollable(scrollable);
    scrollPn->SetCanOverScroll(false);
    EXPECT_EQ(scrollPn->scrollableEvent_->GetScrollable(), nullptr);

    /**
     * @tc.steps: step3. Set the parameter scrollable is true and IsAtBottom is false
     * @tc.expected: Scrollable is not nullptr
     */
    EXPECT_CALL(*scrollPn, IsAtBottom).WillRepeatedly(Return(false));
    scrollPn->scrollableEvent_ = AceType::MakeRefPtr<ScrollableEvent>(Axis::VERTICAL);
    scrollable =
        AceType::MakeRefPtr<Scrollable>([](double, int32_t source) -> bool { return true; }, Axis::VERTICAL);
    scrollPn->scrollableEvent_->SetScrollable(scrollable);
    EXPECT_NE(scrollPn->scrollableEvent_->GetScrollable(), nullptr);

    /**
     * @tc.steps: step4. Call the HandleScrollVelocity method
     * @tc.expected: The result is true
     */
    bool res = scrollPn->HandleScrollVelocity(-1.1f);
    EXPECT_TRUE(res);

    /**
     * @tc.steps: step5. Call the GetCanOverScroll method, Set the parameter scrollable is false
     * @tc.expected: The result is true
     */
    scrollPn->scrollableEvent_ = AceType::MakeRefPtr<ScrollableEvent>(Axis::VERTICAL);
    auto result = scrollPn->GetCanOverScroll();
    EXPECT_TRUE(result);

    /**
     * @tc.steps: step6. Call the GetCanOverScroll method, Set the parameter scrollable is true
     * @tc.expected: The result is true
     */
    scrollable =
        AceType::MakeRefPtr<Scrollable>([](double, int32_t source) -> bool { return true; }, Axis::VERTICAL);
    scrollPn->scrollableEvent_->SetScrollable(scrollable);
    result = scrollPn->GetCanOverScroll();
    EXPECT_TRUE(result);

    /**
     * @tc.steps: step7. Set the correctVelocity is 3000
     * Set the friction is 0.6
     * Set the frictionScale is -4.2
     * Calculate the position finalPosition that should be scrolled to through a formula
     * Get object scrollable and Call the SetFriction method
     * Call the Fling method and pass the correctVelocity parameter
     * Obtain the actual scrolling position finalPosition_
     * @tc.expected: The values of finalPosition_ and finalPosition are the same
     */
    float correctVelocity = 3000.0f;
    float friction = 0.6f;
    float frictionScale = -4.2f;
    float finalPosition = correctVelocity / (friction * -frictionScale);
    auto scrollableEvent = scrollPn->GetScrollableEvent();
    scrollable = scrollableEvent->GetScrollable();
    scrollable->SetFriction(friction);
    scrollPn->Fling(correctVelocity);
    float finalPosition_ = scrollable->finalPosition_;
    EXPECT_EQ(finalPosition_, finalPosition);
}

/**
 * @tc.name: Fling003
 * @tc.desc: Test nested Fling
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableFlingTestNg, Fling003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize ScrollablePattern type pointer
     * @tc.expected: Pointer is not nullptr.
     */
    auto mockPn = AceType::MakeRefPtr<FullyMockedScrollable>();
    mockScroll_->pattern_ = mockPn;
    auto scrollPn = scroll_->GetPattern<PartiallyMockedScrollable>();
    EXPECT_TRUE(scrollPn);
    scrollPn->parent_ = mockPn;

    /**
     * @tc.steps: step2. Call the SelectWithScroll method, Set the parameter IsScrollable is false
     * @tc.expected: The OutOfScrollableOffset is 0.0
     */
    EXPECT_CALL(*scrollPn, IsScrollable).Times(1).WillOnce(Return(false));
    scrollPn->SelectWithScroll();
    EXPECT_EQ(scrollPn->GetOutOfScrollableOffset(), 0.0f);

    /**
     * @tc.steps: step3. Call the SelectWithScroll method, Set the parameter IsScrollable is true
     * @tc.expected: The OutOfScrollableOffset is -1.1
     */
    EXPECT_CALL(*scrollPn, IsScrollable).Times(1).WillOnce(Return(true));
    EXPECT_CALL(*scrollPn, IsAtTop).Times(1);
    scrollPn->SetAxis(Axis::VERTICAL);
    Offset localLocation;
    localLocation.SetX(-1.0f);
    localLocation.SetY(-1.1f);
    scrollPn->lastMouseMove_.SetLocalLocation(localLocation);
    scrollPn->SelectWithScroll();
    EXPECT_EQ(scrollPn->lastMouseMove_.GetLocalLocation().GetY(), -1.1f);

    /**
     * @tc.steps: step4. Call the SelectWithScroll method, Set the parameter IsScrollable is true and deltaY_ is 0
     * @tc.expected: The OutOfScrollableOffset is -1.1
     */
    EXPECT_CALL(*scrollPn, IsScrollable).Times(1).WillOnce(Return(true));
    scrollPn->SetAxis(Axis::VERTICAL);
    localLocation.SetX(-1.0f);
    localLocation.SetY(-0.0f);
    scrollPn->lastMouseMove_.SetLocalLocation(localLocation);
    scrollPn->SelectWithScroll();
    EXPECT_EQ(scrollPn->lastMouseMove_.GetLocalLocation().GetY(), -0.0f);

    /**
     * @tc.steps: step5. Call the SelectWithScroll method, Set the parameter isAnimationStop_ is false
     * @tc.expected: The OutOfScrollableOffset is -1.1
     */
    EXPECT_CALL(*scrollPn, IsAtTop).Times(AtLeast(1));
    EXPECT_CALL(*scrollPn, IsScrollable).Times(1).WillOnce(Return(true));
    scrollPn->SetAxis(Axis::VERTICAL);
    localLocation.SetX(-1.0f);
    localLocation.SetY(-1.1f);
    scrollPn->lastMouseMove_.SetLocalLocation(localLocation);
    scrollPn->isAnimationStop_ = false;
    scrollPn->SelectWithScroll();
    EXPECT_EQ(scrollPn->lastMouseMove_.GetLocalLocation().GetY(), -1.1f);

    /**
     * @tc.steps: step6. Set the correctVelocity is 3000
     * Set the friction is 0.6
     * Set the frictionScale is -4.2
     * Calculate the position finalPosition that should be scrolled to through a formula
     * Get object scrollable and Call the SetFriction method
     * Call the Fling method and pass the correctVelocity parameter
     * Obtain the actual scrolling position finalPosition_
     * @tc.expected: The values of finalPosition_ and finalPosition are the same
     */
    float correctVelocity = 3000.0f;
    float friction = 0.6f;
    float frictionScale = -4.2f;
    float finalPosition = correctVelocity / (friction * -frictionScale);
    auto scrollableEvent = scrollPn->GetScrollableEvent();
    auto scrollable = scrollableEvent->GetScrollable();
    scrollable->SetFriction(friction);
    scrollPn->Fling(correctVelocity);
    float finalPosition_ = scrollable->finalPosition_;
    EXPECT_EQ(finalPosition_, finalPosition);
}

/**
 * @tc.name: Fling004
 * @tc.desc: Test nested Fling
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableFlingTestNg, Fling004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize ScrollablePattern type pointer
     * @tc.expected: Pointer is not nullptr.
     */
    auto mockPn = AceType::MakeRefPtr<FullyMockedScrollable>();
    mockScroll_->pattern_ = mockPn;
    auto scrollPn = scroll_->GetPattern<PartiallyMockedScrollable>();
    EXPECT_TRUE(scrollPn);
    scrollPn->parent_ = mockPn;

    /**
     * @tc.steps: step2. Call the SelectWithScroll method, Set the parameter isAnimationStop_ is true
     *   and selectMotion_ is not nullptr
     * @tc.expected: The OutOfScrollableOffset is -1.1
     */
    scrollPn->SetAxis(Axis::VERTICAL);
    Offset localLocation;
    localLocation.SetX(-1.0f);
    localLocation.SetY(-1.1f);
    scrollPn->lastMouseMove_.SetLocalLocation(localLocation);
    scrollPn->isAnimationStop_ = true;
    scrollPn->selectMotion_ = AceType::MakeRefPtr<SelectMotion>(0.0f, [this]() -> bool { return true; });
    scrollPn->SelectWithScroll();
    EXPECT_EQ(scrollPn->lastMouseMove_.GetLocalLocation().GetY(), -1.1f);

    /**
     * @tc.steps: step3. Call the LimitMouseEndOffset method, Set the parameter is Axis::HORIZONTAL
     *   and selectMotion_ is not nullptr
     * @tc.expected: The OutOfScrollableOffset is -1.1
     */
    scrollPn->SetAxis(Axis::HORIZONTAL);
    scrollPn->mouseEndOffset_ = OffsetF(-1.0f, -1.1f);
    scrollPn->LimitMouseEndOffset();
    EXPECT_EQ(scrollPn->mouseEndOffset_.GetX(), 0.0f);
    EXPECT_EQ(scrollPn->mouseEndOffset_.GetY(), 0.0f);

    /**
     * @tc.steps: step4. Call the LimitMouseEndOffset method, Set the parameter is Axis::VERTICAL
     *   and selectMotion_ is not nullptr
     * @tc.expected: The OutOfScrollableOffset is -1.1
     */
    scrollPn->SetAxis(Axis::VERTICAL);
    scrollPn->mouseEndOffset_ = OffsetF(1.0f, 1.1f);
    scrollPn->LimitMouseEndOffset();
    EXPECT_EQ(scrollPn->mouseEndOffset_.GetX(), 0.0f);
    EXPECT_EQ(scrollPn->mouseEndOffset_.GetY(), 0.0f);

    /**
     * @tc.steps: step5. Call the HotZoneScroll method, Set the parameter status of animator is idle
     * @tc.expected: The animator is not nullptr
     */
    float offsetPct = 0.5f;
    scrollPn->animator_ = CREATE_ANIMATOR(PipelineBase::GetCurrentContext());
    scrollPn->animator_->Reverse();
    EXPECT_NE(scrollPn->animator_->GetStatus(), Animator::Status::RUNNING);
    scrollPn->HotZoneScroll(offsetPct);
    EXPECT_NE(scrollPn->animator_, nullptr);

    /**
     * @tc.steps: step6. Call the HotZoneScroll method, Set the parameter is Axis::HORIZONTAL
     *   and selectMotion_ is not nullptr
     * @tc.expected: The offset is
     */
    scrollPn->velocityMotion_ =
        AceType::MakeRefPtr<BezierVariableVelocityMotion>(offsetPct, [](float offset) -> bool { return true; });
    scrollPn->HotZoneScroll(offsetPct);
    EXPECT_EQ(scrollPn->lastHonezoneOffsetPct_, 0.0f);

    /**
     * @tc.steps: step7. Set the correctVelocity is 3000
     * Set the friction is 0.6
     * Set the frictionScale is -4.2
     * Calculate the position finalPosition that should be scrolled to through a formula
     * Get object scrollable and Call the SetFriction method
     * Call the Fling method and pass the correctVelocity parameter
     * Obtain the actual scrolling position finalPosition_
     * @tc.expected: The values of finalPosition_ and finalPosition are the same
     */
    float correctVelocity = 3000.0f;
    float friction = 0.6f;
    float frictionScale = -4.2f;
    float finalPosition = correctVelocity / (friction * -frictionScale);
    auto scrollableEvent = scrollPn->GetScrollableEvent();
    auto scrollable = scrollableEvent->GetScrollable();
    scrollable->SetFriction(friction);
    scrollPn->Fling(correctVelocity);
    float finalPosition_ = scrollable->finalPosition_;
    EXPECT_EQ(finalPosition_, finalPosition);
}

/**
 * @tc.name: Fling005
 * @tc.desc: Test nested Fling
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableFlingTestNg, Fling005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize ScrollablePattern type pointer
     * @tc.expected: Pointer is not nullptr.
     */
    auto mockPn = AceType::MakeRefPtr<FullyMockedScrollable>();
    mockScroll_->pattern_ = mockPn;
    auto scrollPn = scroll_->GetPattern<PartiallyMockedScrollable>();
    EXPECT_TRUE(scrollPn);
    scrollPn->parent_ = mockPn;

    /**
     * @tc.steps: step2. Call the CoordinateWithRefresh method
     * @tc.expected: The result is UNKNOWN
     */
    double offset = 0.2f;
    int32_t source = 1;
    bool isAtTop = true;
    scrollPn->refreshCoordination_ = AceType::MakeRefPtr<RefreshCoordination>(scrollPn->GetHost());
    auto result = scrollPn->CoordinateWithRefresh(offset, source, isAtTop);
    EXPECT_EQ(result, RefreshCoordinationMode::UNKNOWN);

    EXPECT_CALL(*scrollPn, IsAtTop).WillRepeatedly(Return(true));
    auto refreshNode = FrameNode::CreateFrameNode("Refresh", -1, AceType::MakeRefPtr<RefreshPattern>());
    scroll_->MountToParent(refreshNode);
    refreshNode->MarkModifyDone();

    /**
     * @tc.steps: step3. Call the CoordinateWithRefresh method
     * @tc.expected: The result is UNKNOWN
     */
    offset = 5.0f;
    result = scrollPn->CoordinateWithRefresh(offset, SCROLL_FROM_START, false);
    EXPECT_EQ(result, RefreshCoordinationMode::UNKNOWN);
    EXPECT_TRUE(scrollPn->refreshCoordination_);
    EXPECT_FALSE(scrollPn->isRefreshInReactive_);
    EXPECT_EQ(offset, 5.0f);

    scrollPn->isRefreshInReactive_ = true;
    result = scrollPn->CoordinateWithRefresh(offset, SCROLL_FROM_START, false);
    EXPECT_EQ(result, RefreshCoordinationMode::UNKNOWN);

    scrollPn->isRefreshInReactive_ = true;
    result = scrollPn->CoordinateWithRefresh(offset, SCROLL_FROM_UPDATE, false);
    EXPECT_FALSE(scrollPn->refreshCoordination_->InCoordination());
    EXPECT_NE(result, RefreshCoordinationMode::REFRESH_SCROLL);
    EXPECT_EQ(offset, 5.0f);

    /**
     * @tc.steps: step4. Call the SetMaxFlingVelocity method
     * @tc.expected: The maxFlingVelocity is MAX_VELOCITY or max
     */
    double max = 0.0f;
    scrollPn->SetMaxFlingVelocity(max);
    EXPECT_EQ(scrollPn->maxFlingVelocity_, MAX_VELOCITY);
    max = 0.2f;
    scrollPn->SetMaxFlingVelocity(max);
    EXPECT_EQ(scrollPn->maxFlingVelocity_, 0.2f);

    /**
     * @tc.steps: step5. Set the correctVelocity is 3000
     * Set the friction is 0.6
     * Set the frictionScale is -4.2
     * Calculate the position finalPosition that should be scrolled to through a formula
     * Get object scrollable and Call the SetFriction method
     * Call the Fling method and pass the correctVelocity parameter
     * Obtain the actual scrolling position finalPosition_
     * @tc.expected: The values of finalPosition_ and finalPosition are the same
     */
    float correctVelocity = 3000.0f;
    float friction = 0.6f;
    float frictionScale = -4.2f;
    float finalPosition = correctVelocity / (friction * -frictionScale);
    auto scrollableEvent = scrollPn->GetScrollableEvent();
    auto scrollable = scrollableEvent->GetScrollable();
    scrollable->SetFriction(friction);
    scrollPn->Fling(correctVelocity);
    float finalPosition_ = scrollable->finalPosition_;
    EXPECT_EQ(finalPosition_, finalPosition);
}

/**
 * @tc.name: Fling006
 * @tc.desc: Test nested Fling
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableFlingTestNg, Fling006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize ScrollablePattern type pointer
     * @tc.expected: Pointer is not nullptr.
     */
    auto mockPn = AceType::MakeRefPtr<FullyMockedScrollable>();
    mockScroll_->pattern_ = mockPn;
    auto scrollPn = scroll_->GetPattern<PartiallyMockedScrollable>();
    EXPECT_TRUE(scrollPn);
    scrollPn->parent_ = mockPn;

    /**
     * @tc.steps: step2. Call the MarkSelectedItems method
     * @tc.expected: The IsScrollable is false
     */
    scrollPn->MarkSelectedItems();
    EXPECT_FALSE(scrollPn->IsScrollable());
    scrollPn->multiSelectable_ = true;
    scrollPn->MarkSelectedItems();
    EXPECT_FALSE(scrollPn->IsScrollable());
    scrollPn->mousePressed_ = true;
    scrollPn->MarkSelectedItems();
    EXPECT_FALSE(scrollPn->IsScrollable());
    scrollPn->mouseStartOffset_ = OffsetF(0.0f, 0.0f);
    scrollPn->mouseEndOffset_ = OffsetF(1.0f, 1.0f);
    scrollPn->MarkSelectedItems();
    EXPECT_FALSE(scrollPn->IsScrollable());

    /**
     * @tc.steps: step3. When lastMouseMove is not nullptr, call the MarkSelectedItems method
     * @tc.expected: The result is false
     */
    scrollPn->GetHost();
    scrollPn->parent_ = mockPn;
    scrollPn->mousePressed_ = true;
    scrollPn->SetAxis(Axis::HORIZONTAL);
    Offset localLocation;
    localLocation.SetX(-1.1f);
    scrollPn->lastMouseMove_.SetLocalLocation(localLocation);
    EXPECT_EQ(scrollPn->lastMouseMove_.GetLocalLocation().GetX(), -1.1f);
    auto result = scrollPn->ShouldSelectScrollBeStopped();
    EXPECT_FALSE(result);

    /**
     * @tc.steps: step4. When selectMotion is not nullptr, call the MarkSelectedItems method
     * @tc.expected: The result is false
     */
    scrollPn->selectMotion_ = AceType::MakeRefPtr<SelectMotion>(0.0f, [this]() -> bool { return true; });
    result = scrollPn->ShouldSelectScrollBeStopped();
    EXPECT_FALSE(result);

    /**
     * @tc.steps: step5. When lastMouseMove is not nullptr, call the MarkSelectedItems method
     * @tc.expected: The result is true
     */
    scrollPn->SetAxis(Axis::VERTICAL);
    localLocation.SetY(-0.0f);
    scrollPn->lastMouseMove_.SetLocalLocation(localLocation);
    EXPECT_EQ(scrollPn->lastMouseMove_.GetLocalLocation().GetY(), -0.0f);
    result = scrollPn->ShouldSelectScrollBeStopped();
    EXPECT_TRUE(result);

    /**
     * @tc.steps: step6. Set the correctVelocity is 3000
     * Set the friction is 0.6
     * Set the frictionScale is -4.2
     * Calculate the position finalPosition that should be scrolled to through a formula
     * Get object scrollable and Call the SetFriction method
     * Call the Fling method and pass the correctVelocity parameter
     * Obtain the actual scrolling position finalPosition_
     * @tc.expected: The values of finalPosition_ and finalPosition are the same
     */
    float correctVelocity = 3000.0f;
    float friction = 0.6f;
    float frictionScale = -4.2f;
    float finalPosition = correctVelocity / (friction * -frictionScale);
    auto scrollableEvent = scrollPn->GetScrollableEvent();
    auto scrollable = scrollableEvent->GetScrollable();
    scrollable->SetFriction(friction);
    scrollPn->Fling(correctVelocity);
    float finalPosition_ = scrollable->finalPosition_;
    EXPECT_EQ(finalPosition_, finalPosition);
}

/**
 * @tc.name: Fling007
 * @tc.desc: Test nested Fling
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableFlingTestNg, Fling007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize ScrollablePattern type pointer
     * @tc.expected: Pointer is not nullptr.
     */
    auto mockPn = AceType::MakeRefPtr<FullyMockedScrollable>();
    mockScroll_->pattern_ = mockPn;
    auto scrollPn = scroll_->GetPattern<PartiallyMockedScrollable>();
    EXPECT_TRUE(scrollPn);
    scrollPn->parent_ = mockPn;

    /**
     * @tc.steps: step2. Set the parameter scrollable to be nullptr
     * @tc.expected: Scrollable is nullptr
     */
    RefPtr<Scrollable> scrollable = nullptr;
    scrollPn->scrollableEvent_ = AceType::MakeRefPtr<ScrollableEvent>(Axis::VERTICAL);
    scrollPn->scrollableEvent_->SetScrollable(scrollable);
    scrollPn->SetCanOverScroll(false);
    EXPECT_EQ(scrollPn->scrollableEvent_->GetScrollable(), nullptr);

    /**
     * @tc.steps: step3. Set the parameter scrollable is true and IsAtBottom is false
     * @tc.expected: Scrollable is not nullptr
     */
    EXPECT_CALL(*scrollPn, IsAtBottom).WillRepeatedly(Return(false));
    scrollPn->scrollableEvent_ = AceType::MakeRefPtr<ScrollableEvent>(Axis::VERTICAL);
    scrollable =
        AceType::MakeRefPtr<Scrollable>([](double, int32_t source) -> bool { return true; }, Axis::VERTICAL);
    scrollPn->scrollableEvent_->SetScrollable(scrollable);
    EXPECT_NE(scrollPn->scrollableEvent_->GetScrollable(), nullptr);

    /**
     * @tc.steps: step5. Call the GetCanOverScroll method, Set the parameter scrollable is false
     * @tc.expected: The result is true
     */
    scrollPn->scrollableEvent_ = AceType::MakeRefPtr<ScrollableEvent>(Axis::VERTICAL);
    auto result = scrollPn->GetCanOverScroll();
    EXPECT_TRUE(result);

    /**
     * @tc.steps: step6. Call the GetCanOverScroll method, Set the parameter scrollable is true
     * @tc.expected: The result is true
     */
    scrollable =
        AceType::MakeRefPtr<Scrollable>([](double, int32_t source) -> bool { return true; }, Axis::VERTICAL);
    scrollPn->scrollableEvent_->SetScrollable(scrollable);
    result = scrollPn->GetCanOverScroll();
    EXPECT_TRUE(result);

    /**
     * @tc.steps: step7. Set the correctVelocity is 5000
     * Set the friction is 0.6
     * Set the frictionScale is -4.2
     * Calculate the position finalPosition that should be scrolled to through a formula
     * Get object scrollable and Call the SetFriction method
     * Call the Fling method and pass the correctVelocity parameter
     * Obtain the actual scrolling position finalPosition_
     * @tc.expected: The values of finalPosition_ and finalPosition are the same
     */
    float correctVelocity = 5000.0f;
    float friction = 0.6f;
    float frictionScale = -4.2f;
    float finalPosition = correctVelocity / (friction * -frictionScale);
    auto scrollableEvent = scrollPn->GetScrollableEvent();
    scrollable = scrollableEvent->GetScrollable();
    scrollable->SetFriction(friction);
    scrollPn->Fling(correctVelocity);
    float finalPosition_ = scrollable->finalPosition_;
    EXPECT_EQ(finalPosition_, finalPosition);
}

/**
 * @tc.name: Fling008
 * @tc.desc: Test nested Fling
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableFlingTestNg, Fling008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize ScrollablePattern type pointer
     * @tc.expected: Pointer is not nullptr.
     */
    auto scrollPn = scroll_->GetPattern<PartiallyMockedScrollable>();
    EXPECT_TRUE(scrollPn);
    auto mockPn = mockScroll_->GetPattern<MockNestableScrollContainer>();
    EXPECT_TRUE(mockPn);
    scrollPn->parent_ = mockPn;
    auto result = scrollPn->ShouldSelectScrollBeStopped();
    EXPECT_TRUE(result);

    /**
     * @tc.steps: step2. Call the OnScrollStop method
     * @tc.expected: The scrollStop is false
     */
    scrollPn->scrollStop_ = true;
    scrollPn->SetScrollAbort(true);
    bool isStopTrigger = false;
    OnScrollStopEvent stopEvent = [&isStopTrigger]() { isStopTrigger = true; };
    scrollPn->OnScrollStop(stopEvent);
    EXPECT_FALSE(scrollPn->scrollStop_);

    /**
     * @tc.steps: step3. Call the HandleHotZone method
     * @tc.expected: The scrollable is false
     */
    RefPtr<NotifyDragEvent> notifyDragEvent = AceType::MakeRefPtr<NotifyDragEvent>();
    notifyDragEvent->SetX(0.1f);
    EXPECT_EQ(notifyDragEvent->GetX(), 0.1f);
    notifyDragEvent->SetY(0.2f);
    EXPECT_EQ(notifyDragEvent->GetY(), 0.2f);
    int32_t minPlatformVersion = 11;
    PipelineBase::GetCurrentContext()->SetMinPlatformVersion(minPlatformVersion);
    scrollPn->HandleHotZone(DragEventType::ENTER, notifyDragEvent);
    scrollPn->HandleHotZone(DragEventType::LEAVE, notifyDragEvent);
    EXPECT_FALSE(scrollPn->IsScrollable());

    /**
     * @tc.steps: step4. Call the HandleHotZone method
     * @tc.expected: The scrollable is false
     */
    notifyDragEvent = AceType::MakeRefPtr<NotifyDragEvent>();
    notifyDragEvent->SetX(0.1f);
    EXPECT_EQ(notifyDragEvent->GetX(), 0.1f);
    notifyDragEvent->SetY(0.2f);
    EXPECT_EQ(notifyDragEvent->GetY(), 0.2f);
    minPlatformVersion = 12;
    PipelineBase::GetCurrentContext()->SetMinPlatformVersion(minPlatformVersion);
    scrollPn->HandleHotZone(DragEventType::MOVE, notifyDragEvent);
    EXPECT_FALSE(scrollPn->IsScrollable());

    /**
     * @tc.steps: step5. Initialize ScrollablePattern type pointer
     * @tc.expected: Pointer is not nullptr and result is false
     */
    scrollPn->navBarPattern_ = nullptr;
    OverScrollOffset overScrollOffset = { 0.0f, 0.5f };
    result = scrollPn->NeedCoordinateScrollWithNavigation(0.0f, SCROLL_FROM_ANIMATION_SPRING, overScrollOffset);
    EXPECT_FALSE(result);

    /**
     * @tc.steps: step6. Set the correctVelocity is 3000
     * Set the friction is 0.6
     * Set the frictionScale is -4.2
     * Calculate the position finalPosition that should be scrolled to through a formula
     * Get object scrollable and Call the SetFriction method
     * Call the Fling method and pass the correctVelocity parameter
     * Obtain the actual scrolling position finalPosition_
     * @tc.expected: The values of finalPosition_ and finalPosition are the same
     */
    float correctVelocity = 3000.0f;
    float friction = 0.6f;
    float frictionScale = -4.2f;
    float finalPosition = correctVelocity / (friction * -frictionScale);
    auto scrollableEvent = scrollPn->GetScrollableEvent();
    auto scrollable = scrollableEvent->GetScrollable();
    scrollable->SetFriction(friction);
    scrollPn->Fling(correctVelocity);
    float finalPosition_ = scrollable->finalPosition_;
    EXPECT_EQ(finalPosition_, finalPosition);
}

/**
 * @tc.name: Fling009
 * @tc.desc: Test nested Fling
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableFlingTestNg, Fling009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize ScrollablePattern type pointer
     * @tc.expected: Pointer is not nullptr.
     */
    auto scrollPn = scroll_->GetPattern<PartiallyMockedScrollable>();
    EXPECT_TRUE(scrollPn);
    auto mockPn = mockScroll_->GetPattern<MockNestableScrollContainer>();
    EXPECT_TRUE(mockPn);
    scrollPn->parent_ = mockPn;
    auto result = scrollPn->ShouldSelectScrollBeStopped();
    EXPECT_TRUE(result);

    /**
     * @tc.steps: step2. Call the HandleHotZone method
     * @tc.expected: The scrollable is false
     */
    const RefPtr<NotifyDragEvent> notifyDragEvent = AceType::MakeRefPtr<NotifyDragEvent>();
    notifyDragEvent->SetX(0.1f);
    EXPECT_EQ(notifyDragEvent->GetX(), 0.1f);
    notifyDragEvent->SetY(0.2f);
    EXPECT_EQ(notifyDragEvent->GetY(), 0.2f);
    int32_t minPlatformVersion = 12;
    PipelineBase::GetCurrentContext()->SetMinPlatformVersion(minPlatformVersion);
    scrollPn->HandleHotZone(DragEventType::START, notifyDragEvent);
    EXPECT_FALSE(scrollPn->IsScrollable());

    /**
     * @tc.steps: step3. Call the NeedCoordinateScrollWithNavigation method
     * @tc.expected: The scrollable is false
     */
    scrollPn->GetParentNavigation();
    scrollPn->navBarPattern_ = AceType::MakeRefPtr<NavBarPattern>();
    OverScrollOffset overScrollOffset = { 0.0f, 0.5f };
    result = scrollPn->NeedCoordinateScrollWithNavigation(0.0f, SCROLL_FROM_ANIMATION_SPRING, overScrollOffset);
    EXPECT_FALSE(result);

    /**
     * @tc.steps: step4. Call the NeedCoordinateScrollWithNavigation method
     * @tc.expected: The scrollable is false
     */
    overScrollOffset = { 0.1f, 0.5f };
    result = scrollPn->NeedCoordinateScrollWithNavigation(0.0f, SCROLL_FROM_ANIMATION_SPRING, overScrollOffset);
    EXPECT_FALSE(result);

    /**
     * @tc.steps: step5. Call the NeedCoordinateScrollWithNavigation method
     * @tc.expected: The scrollable is false
     */
    scrollPn->SetAxis(Axis::VERTICAL);
    result = scrollPn->NeedCoordinateScrollWithNavigation(0.0f, SCROLL_FROM_ANIMATION_SPRING, overScrollOffset);
    EXPECT_FALSE(result);

    /**
     * @tc.steps: step6. Call the NeedCoordinateScrollWithNavigation method, set source is SCROLL_FROM_CHILD
     * @tc.expected: The scrollable is true
     */
    result = scrollPn->NeedCoordinateScrollWithNavigation(0.0f, SCROLL_FROM_CHILD, overScrollOffset);
    EXPECT_TRUE(result);

    /**
     * @tc.steps: step7. Set the correctVelocity is 3000
     * Set the friction is 0.6
     * Set the frictionScale is -4.2
     * Calculate the position finalPosition that should be scrolled to through a formula
     * Get object scrollable and Call the SetFriction method
     * Call the Fling method and pass the correctVelocity parameter
     * Obtain the actual scrolling position finalPosition_
     * @tc.expected: The values of finalPosition_ and finalPosition are the same
     */
    float correctVelocity = 3000.0f;
    float friction = 0.6f;
    float frictionScale = -4.2f;
    float finalPosition = correctVelocity / (friction * -frictionScale);
    auto scrollableEvent = scrollPn->GetScrollableEvent();
    auto scrollable = scrollableEvent->GetScrollable();
    scrollable->SetFriction(friction);
    scrollPn->Fling(correctVelocity);
    float finalPosition_ = scrollable->finalPosition_;
    EXPECT_EQ(finalPosition_, finalPosition);
}

/**
 * @tc.name: Fling010
 * @tc.desc: Test nested Fling
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableFlingTestNg, Fling010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize ScrollablePattern type pointer
     * @tc.expected: Pointer is not nullptr.
     */
    auto scrollPn = scroll_->GetPattern<PartiallyMockedScrollable>();
    EXPECT_TRUE(scrollPn);
    auto mockPn = mockScroll_->GetPattern<MockNestableScrollContainer>();
    EXPECT_TRUE(mockPn);
    scrollPn->parent_ = mockPn;
    auto result = scrollPn->ShouldSelectScrollBeStopped();
    EXPECT_TRUE(result);

    /**
     * @tc.steps: step2. Call the NeedCoordinateScrollWithNavigation method
     * @tc.expected: The scrollable is false
     */
    scrollPn->GetParentNavigation();
    scrollPn->navBarPattern_ = AceType::MakeRefPtr<NavBarPattern>();
    OverScrollOffset overScrollOffset = { 0.0f, 0.5f };
    result = scrollPn->NeedCoordinateScrollWithNavigation(0.0f, SCROLL_FROM_ANIMATION_SPRING, overScrollOffset);
    EXPECT_FALSE(result);

    /**
     * @tc.steps: step3. Call the NeedCoordinateScrollWithNavigation method
     * @tc.expected: The scrollable is false
     */
    overScrollOffset = { 0.1f, 0.5f };
    result = scrollPn->NeedCoordinateScrollWithNavigation(0.0f, SCROLL_FROM_ANIMATION_SPRING, overScrollOffset);
    EXPECT_FALSE(result);

    /**
     * @tc.steps: step4. Call the NotifyMoved method
     * @tc.expected: Scrollable is nullptr
     */
    scrollPn->scrollableEvent_ = AceType::MakeRefPtr<ScrollableEvent>(Axis::VERTICAL);
    scrollPn->NotifyMoved(false);
    EXPECT_FALSE(scrollPn->scrollableEvent_->GetScrollable());

    /**
     * @tc.steps: step5. Call the NotifyMoved method
     * @tc.expected: Scrollable is not nullptr
     */
    auto scrollable =
        AceType::MakeRefPtr<Scrollable>([](double, int32_t source) -> bool { return true; }, Axis::VERTICAL);
    scrollPn->scrollableEvent_->SetScrollable(scrollable);
    scrollPn->NotifyMoved(false);
    EXPECT_TRUE(scrollPn->scrollableEvent_->GetScrollable());

    /**
     * @tc.steps: step6. Call the NeedSplitScroll method
     * @tc.expected: return false
     */
    overScrollOffset = { 0.0f, 0.0f };
    EXPECT_FALSE(scrollPn->NeedSplitScroll(overScrollOffset, SCROLL_FROM_UPDATE));
    overScrollOffset = { 0.0f, 0.1f };
    EXPECT_FALSE(scrollPn->NeedSplitScroll(overScrollOffset, SCROLL_FROM_UPDATE));
    scrollPn->refreshCoordination_ = nullptr;
    EXPECT_FALSE(scrollPn->NeedSplitScroll(overScrollOffset, SCROLL_FROM_UPDATE));
    auto pattern = AceType::MakeRefPtr<Pattern>();
    auto scrollableNode = AceType::MakeRefPtr<FrameNode>("tag", 0, pattern);
    scrollPn->refreshCoordination_ = AceType::MakeRefPtr<RefreshCoordination>(scrollableNode);
    EXPECT_FALSE(scrollPn->NeedSplitScroll(overScrollOffset, SCROLL_FROM_UPDATE));

    /**
     * @tc.steps: step7. Set the correctVelocity is 3000
     * Set the friction is 0.6
     * Set the frictionScale is -4.2
     * Calculate the position finalPosition that should be scrolled to through a formula
     * Get object scrollable and Call the SetFriction method
     * Call the Fling method and pass the correctVelocity parameter
     * Obtain the actual scrolling position finalPosition_
     * @tc.expected: The values of finalPosition_ and finalPosition are the same
     */
    float correctVelocity = 3000.0f;
    float friction = 0.6f;
    float frictionScale = -4.2f;
    float finalPosition = correctVelocity / (friction * -frictionScale);
    auto scrollableEvent = scrollPn->GetScrollableEvent();
    auto scrollable_ = scrollableEvent->GetScrollable();
    scrollable_->SetFriction(friction);
    scrollPn->Fling(correctVelocity);
    float finalPosition_ = scrollable_->finalPosition_;
    EXPECT_EQ(finalPosition_, finalPosition);
}

/**
 * @tc.name: Fling011
 * @tc.desc: Test nested Fling
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableFlingTestNg, Fling011, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize ScrollablePattern type pointer
     * @tc.expected: Pointer is not nullptr.
     */
    auto mockPn = AceType::MakeRefPtr<FullyMockedScrollable>();
    mockScroll_->pattern_ = mockPn;
    auto scrollPn = scroll_->GetPattern<PartiallyMockedScrollable>();
    EXPECT_TRUE(scrollPn);
    scrollPn->parent_ = mockPn;

    /**
     * @tc.steps: step2. Set the parameter scrollable to be nullptr
     * @tc.expected: Scrollable is nullptr
     */
    RefPtr<Scrollable> scrollable = nullptr;
    scrollPn->scrollableEvent_ = AceType::MakeRefPtr<ScrollableEvent>(Axis::VERTICAL);
    scrollPn->scrollableEvent_->SetScrollable(scrollable);
    scrollPn->SetCanOverScroll(false);
    EXPECT_EQ(scrollPn->scrollableEvent_->GetScrollable(), nullptr);

    /**
     * @tc.steps: step3. Set the parameter scrollable is true and IsAtBottom is false
     * @tc.expected: Scrollable is not nullptr
     */
    EXPECT_CALL(*scrollPn, IsAtBottom).WillRepeatedly(Return(false));
    scrollPn->scrollableEvent_ = AceType::MakeRefPtr<ScrollableEvent>(Axis::VERTICAL);
    scrollable =
        AceType::MakeRefPtr<Scrollable>([](double, int32_t source) -> bool { return true; }, Axis::VERTICAL);
    scrollPn->scrollableEvent_->SetScrollable(scrollable);
    EXPECT_NE(scrollPn->scrollableEvent_->GetScrollable(), nullptr);

    /**
     * @tc.steps: step4. Call the HandleScrollVelocity method
     * @tc.expected: The result is true
     */
    bool res = scrollPn->HandleScrollVelocity(-1.1f);
    EXPECT_TRUE(res);

    /**
     * @tc.steps: step5. Call the GetCanOverScroll method, Set the parameter scrollable is false
     * @tc.expected: The result is true
     */
    scrollPn->scrollableEvent_ = AceType::MakeRefPtr<ScrollableEvent>(Axis::VERTICAL);
    auto result = scrollPn->GetCanOverScroll();
    EXPECT_TRUE(result);

    /**
     * @tc.steps: step6. Call the GetCanOverScroll method, Set the parameter scrollable is true
     * @tc.expected: The result is true
     */
    scrollable =
        AceType::MakeRefPtr<Scrollable>([](double, int32_t source) -> bool { return true; }, Axis::VERTICAL);
    scrollPn->scrollableEvent_->SetScrollable(scrollable);
    result = scrollPn->GetCanOverScroll();
    EXPECT_TRUE(result);

    /**
     * @tc.steps: step7. Set the correctVelocity is -3000
     * Set the friction is 0.9
     * Set the frictionScale is -4.2
     * Calculate the position finalPosition that should be scrolled to through a formula
     * Get object scrollable and Call the SetFriction method
     * Call the Fling method and pass the correctVelocity parameter
     * Obtain the actual scrolling position finalPosition_
     * @tc.expected: The values of finalPosition_ and finalPosition are the same
     */
    float correctVelocity = -3000.0f;
    float friction = 0.9f;
    float frictionScale = -4.2f;
    float finalPosition = correctVelocity / (friction * -frictionScale);
    auto scrollableEvent = scrollPn->GetScrollableEvent();
    scrollable = scrollableEvent->GetScrollable();
    scrollable->SetFriction(friction);
    scrollPn->Fling(correctVelocity);
    float finalPosition_ = scrollable->finalPosition_;
    EXPECT_EQ(finalPosition_, finalPosition);
}

/**
 * @tc.name: Fling012
 * @tc.desc: Test nested Fling
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableFlingTestNg, Fling012, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize ScrollablePattern type pointer
     * @tc.expected: Pointer is not nullptr
     */
    auto scrollPn = scroll_->GetPattern<PartiallyMockedScrollable>();
    EXPECT_TRUE(scrollPn);

    /**
     * @tc.steps: step2. Set the correctVelocity is -3000
     * Set the friction is 0.9
     * Set the frictionScale is -4.2
     * Calculate the position finalPosition that should be scrolled to through a formula
     * Get object scrollable and Call the SetFriction method
     * Call the Fling method and pass the correctVelocity parameter
     * Obtain the actual scrolling position finalPosition_
     * @tc.expected: The values of finalPosition_ and finalPosition are the same
     */
    float correctVelocity = -3000.0f;
    float friction = 0.9f;
    float frictionScale = -4.2f;
    float finalPosition = correctVelocity / (friction * -frictionScale);
    auto scrollableEvent = scrollPn->GetScrollableEvent();
    auto scrollable = scrollableEvent->GetScrollable();
    scrollable->SetFriction(friction);
    scrollPn->Fling(correctVelocity);
    float finalPosition_ = scrollable->finalPosition_;
    EXPECT_EQ(finalPosition_, finalPosition);
}

/**
 * @tc.name: Fling013
 * @tc.desc: Test nested Fling
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableFlingTestNg, Fling013, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize ScrollablePattern type pointer
     * @tc.expected: Pointer is not nullptr.
     */
    auto mockPn = AceType::MakeRefPtr<FullyMockedScrollable>();
    mockScroll_->pattern_ = mockPn;
    auto scrollPn = scroll_->GetPattern<PartiallyMockedScrollable>();
    EXPECT_TRUE(scrollPn);
    scrollPn->parent_ = mockPn;

    /**
     * @tc.steps: step2. Set the parameter scrollable to be nullptr
     * @tc.expected: Scrollable is nullptr
     */
    RefPtr<Scrollable> scrollable = nullptr;
    scrollPn->scrollableEvent_ = AceType::MakeRefPtr<ScrollableEvent>(Axis::VERTICAL);
    scrollPn->scrollableEvent_->SetScrollable(scrollable);
    scrollPn->SetCanOverScroll(false);
    EXPECT_EQ(scrollPn->scrollableEvent_->GetScrollable(), nullptr);

    /**
     * @tc.steps: step3. Set the parameter scrollable is true and IsAtBottom is false
     * @tc.expected: Scrollable is not nullptr
     */
    EXPECT_CALL(*scrollPn, IsAtBottom).WillRepeatedly(Return(false));
    scrollPn->scrollableEvent_ = AceType::MakeRefPtr<ScrollableEvent>(Axis::VERTICAL);
    scrollable =
        AceType::MakeRefPtr<Scrollable>([](double, int32_t source) -> bool { return true; }, Axis::VERTICAL);
    scrollPn->scrollableEvent_->SetScrollable(scrollable);
    EXPECT_NE(scrollPn->scrollableEvent_->GetScrollable(), nullptr);

    /**
     * @tc.steps: step4. Call the HandleScrollVelocity method
     * @tc.expected: The result is true
     */
    bool res = scrollPn->HandleScrollVelocity(-1.1f);
    EXPECT_TRUE(res);

    /**
     * @tc.steps: step5. Call the GetCanOverScroll method, Set the parameter scrollable is false
     * @tc.expected: The result is true
     */
    scrollPn->scrollableEvent_ = AceType::MakeRefPtr<ScrollableEvent>(Axis::VERTICAL);
    auto result = scrollPn->GetCanOverScroll();
    EXPECT_TRUE(result);

    /**
     * @tc.steps: step6. Call the GetCanOverScroll method, Set the parameter scrollable is true
     * @tc.expected: The result is true
     */
    scrollable =
        AceType::MakeRefPtr<Scrollable>([](double, int32_t source) -> bool { return true; }, Axis::VERTICAL);
    scrollPn->scrollableEvent_->SetScrollable(scrollable);
    result = scrollPn->GetCanOverScroll();
    EXPECT_TRUE(result);

    /**
     * @tc.steps: step7. Set the correctVelocity is -3000
     * Set the friction is 0.9
     * Set the frictionScale is -4.2
     * Calculate the position finalPosition that should be scrolled to through a formula
     * Get object scrollable and Call the SetFriction method
     * Call the Fling method and pass the correctVelocity parameter
     * Obtain the actual scrolling position finalPosition_
     * @tc.expected: The values of finalPosition_ and finalPosition are the same
     */
    float correctVelocity = -3000.0f;
    float friction = 0.9f;
    float frictionScale = -4.2f;
    float finalPosition = correctVelocity / (friction * -frictionScale);
    auto scrollableEvent = scrollPn->GetScrollableEvent();
    scrollable = scrollableEvent->GetScrollable();
    scrollable->SetFriction(friction);
    scrollPn->Fling(correctVelocity);
    float finalPosition_ = scrollable->finalPosition_;
    EXPECT_EQ(finalPosition_, finalPosition);
}

/**
 * @tc.name: Fling014
 * @tc.desc: Test nested Fling
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableFlingTestNg, Fling014, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize ScrollablePattern type pointer
     * @tc.expected: Pointer is not nullptr.
     */
    auto mockPn = AceType::MakeRefPtr<FullyMockedScrollable>();
    mockScroll_->pattern_ = mockPn;
    auto scrollPn = scroll_->GetPattern<PartiallyMockedScrollable>();
    EXPECT_TRUE(scrollPn);
    scrollPn->parent_ = mockPn;

    /**
     * @tc.steps: step2. Call the SelectWithScroll method, Set the parameter IsScrollable is false
     * @tc.expected: The OutOfScrollableOffset is 0.0
     */
    EXPECT_CALL(*scrollPn, IsScrollable).Times(1).WillOnce(Return(false));
    scrollPn->SelectWithScroll();
    EXPECT_EQ(scrollPn->GetOutOfScrollableOffset(), 0.0f);

    /**
     * @tc.steps: step3. Call the SelectWithScroll method, Set the parameter IsScrollable is true
     * @tc.expected: The OutOfScrollableOffset is -1.1
     */
    EXPECT_CALL(*scrollPn, IsScrollable).Times(1).WillOnce(Return(true));
    EXPECT_CALL(*scrollPn, IsAtTop).Times(1);
    scrollPn->SetAxis(Axis::VERTICAL);
    Offset localLocation;
    localLocation.SetX(-1.0f);
    localLocation.SetY(-1.1f);
    scrollPn->lastMouseMove_.SetLocalLocation(localLocation);
    scrollPn->SelectWithScroll();
    EXPECT_EQ(scrollPn->lastMouseMove_.GetLocalLocation().GetY(), -1.1f);

    /**
     * @tc.steps: step4. Call the SelectWithScroll method, Set the parameter IsScrollable is true and deltaY_ is 0
     * @tc.expected: The OutOfScrollableOffset is -1.1
     */
    EXPECT_CALL(*scrollPn, IsScrollable).Times(1).WillOnce(Return(true));
    scrollPn->SetAxis(Axis::VERTICAL);
    localLocation.SetX(-1.0f);
    localLocation.SetY(-0.0f);
    scrollPn->lastMouseMove_.SetLocalLocation(localLocation);
    scrollPn->SelectWithScroll();
    EXPECT_EQ(scrollPn->lastMouseMove_.GetLocalLocation().GetY(), -0.0f);

    /**
     * @tc.steps: step5. Call the SelectWithScroll method, Set the parameter isAnimationStop_ is false
     * @tc.expected: The OutOfScrollableOffset is -1.1
     */
    EXPECT_CALL(*scrollPn, IsAtTop).Times(AtLeast(1));
    EXPECT_CALL(*scrollPn, IsScrollable).Times(1).WillOnce(Return(true));
    scrollPn->SetAxis(Axis::VERTICAL);
    localLocation.SetX(-1.0f);
    localLocation.SetY(-1.1f);
    scrollPn->lastMouseMove_.SetLocalLocation(localLocation);
    scrollPn->isAnimationStop_ = false;
    scrollPn->SelectWithScroll();
    EXPECT_EQ(scrollPn->lastMouseMove_.GetLocalLocation().GetY(), -1.1f);

    /**
     * @tc.steps: step6. Set the correctVelocity is -3000
     * Set the friction is 0.9
     * Set the frictionScale is -4.2
     * Calculate the position finalPosition that should be scrolled to through a formula
     * Get object scrollable and Call the SetFriction method
     * Call the Fling method and pass the correctVelocity parameter
     * Obtain the actual scrolling position finalPosition_
     * @tc.expected: The values of finalPosition_ and finalPosition are the same
     */
    float correctVelocity = -3000.0f;
    float friction = 0.9f;
    float frictionScale = -4.2f;
    float finalPosition = correctVelocity / (friction * -frictionScale);
    auto scrollableEvent = scrollPn->GetScrollableEvent();
    auto scrollable = scrollableEvent->GetScrollable();
    scrollable->SetFriction(friction);
    scrollPn->Fling(correctVelocity);
    float finalPosition_ = scrollable->finalPosition_;
    EXPECT_EQ(finalPosition_, finalPosition);
}

/**
 * @tc.name: Fling015
 * @tc.desc: Test nested Fling
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableFlingTestNg, Fling015, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize ScrollablePattern type pointer
     * @tc.expected: Pointer is not nullptr.
     */
    auto mockPn = AceType::MakeRefPtr<FullyMockedScrollable>();
    mockScroll_->pattern_ = mockPn;
    auto scrollPn = scroll_->GetPattern<PartiallyMockedScrollable>();
    EXPECT_TRUE(scrollPn);
    scrollPn->parent_ = mockPn;

    /**
     * @tc.steps: step2. Call the SelectWithScroll method, Set the parameter isAnimationStop_ is true
     *   and selectMotion_ is not nullptr
     * @tc.expected: The OutOfScrollableOffset is -1.1
     */
    scrollPn->SetAxis(Axis::VERTICAL);
    Offset localLocation;
    localLocation.SetX(-1.0f);
    localLocation.SetY(-1.1f);
    scrollPn->lastMouseMove_.SetLocalLocation(localLocation);
    scrollPn->isAnimationStop_ = true;
    scrollPn->selectMotion_ = AceType::MakeRefPtr<SelectMotion>(0.0f, [this]() -> bool { return true; });
    scrollPn->SelectWithScroll();
    EXPECT_EQ(scrollPn->lastMouseMove_.GetLocalLocation().GetY(), -1.1f);

    /**
     * @tc.steps: step3. Call the LimitMouseEndOffset method, Set the parameter is Axis::HORIZONTAL
     *   and selectMotion_ is not nullptr
     * @tc.expected: The OutOfScrollableOffset is -1.1
     */
    scrollPn->SetAxis(Axis::HORIZONTAL);
    scrollPn->mouseEndOffset_ = OffsetF(-1.0f, -1.1f);
    scrollPn->LimitMouseEndOffset();
    EXPECT_EQ(scrollPn->mouseEndOffset_.GetX(), 0.0f);
    EXPECT_EQ(scrollPn->mouseEndOffset_.GetY(), 0.0f);

    /**
     * @tc.steps: step4. Call the LimitMouseEndOffset method, Set the parameter is Axis::VERTICAL
     *   and selectMotion_ is not nullptr
     * @tc.expected: The OutOfScrollableOffset is -1.1
     */
    scrollPn->SetAxis(Axis::VERTICAL);
    scrollPn->mouseEndOffset_ = OffsetF(1.0f, 1.1f);
    scrollPn->LimitMouseEndOffset();
    EXPECT_EQ(scrollPn->mouseEndOffset_.GetX(), 0.0f);
    EXPECT_EQ(scrollPn->mouseEndOffset_.GetY(), 0.0f);

    /**
     * @tc.steps: step5. Call the HotZoneScroll method, Set the parameter status of animator is idle
     * @tc.expected: The animator is not nullptr
     */
    float offsetPct = 0.5f;
    scrollPn->animator_ = CREATE_ANIMATOR(PipelineBase::GetCurrentContext());
    scrollPn->animator_->Reverse();
    EXPECT_NE(scrollPn->animator_->GetStatus(), Animator::Status::RUNNING);
    scrollPn->HotZoneScroll(offsetPct);
    EXPECT_NE(scrollPn->animator_, nullptr);

    /**
     * @tc.steps: step6. Call the HotZoneScroll method, Set the parameter is Axis::HORIZONTAL
     *   and selectMotion_ is not nullptr
     * @tc.expected: The offset is
     */
    scrollPn->velocityMotion_ =
        AceType::MakeRefPtr<BezierVariableVelocityMotion>(offsetPct, [](float offset) -> bool { return true; });
    scrollPn->HotZoneScroll(offsetPct);
    EXPECT_EQ(scrollPn->lastHonezoneOffsetPct_, 0.0f);

    /**
     * @tc.steps: step7. Set the correctVelocity is -3000
     * Set the friction is 0.9
     * Set the frictionScale is -4.2
     * Calculate the position finalPosition that should be scrolled to through a formula
     * Get object scrollable and Call the SetFriction method
     * Call the Fling method and pass the correctVelocity parameter
     * Obtain the actual scrolling position finalPosition_
     * @tc.expected: The values of finalPosition_ and finalPosition are the same
     */
    float correctVelocity = -3000.0f;
    float friction = 0.9f;
    float frictionScale = -4.2f;
    float finalPosition = correctVelocity / (friction * -frictionScale);
    auto scrollableEvent = scrollPn->GetScrollableEvent();
    auto scrollable = scrollableEvent->GetScrollable();
    scrollable->SetFriction(friction);
    scrollPn->Fling(correctVelocity);
    float finalPosition_ = scrollable->finalPosition_;
    EXPECT_EQ(finalPosition_, finalPosition);
}

/**
 * @tc.name: Fling016
 * @tc.desc: Test nested Fling
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableFlingTestNg, Fling016, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize ScrollablePattern type pointer
     * @tc.expected: Pointer is not nullptr.
     */
    auto mockPn = AceType::MakeRefPtr<FullyMockedScrollable>();
    mockScroll_->pattern_ = mockPn;
    auto scrollPn = scroll_->GetPattern<PartiallyMockedScrollable>();
    EXPECT_TRUE(scrollPn);
    scrollPn->parent_ = mockPn;

    /**
     * @tc.steps: step2. Call the CoordinateWithRefresh method
     * @tc.expected: The result is UNKNOWN
     */
    double offset = 0.2f;
    int32_t source = 1;
    bool isAtTop = true;
    scrollPn->refreshCoordination_ = AceType::MakeRefPtr<RefreshCoordination>(scrollPn->GetHost());
    auto result = scrollPn->CoordinateWithRefresh(offset, source, isAtTop);
    EXPECT_EQ(result, RefreshCoordinationMode::UNKNOWN);

    EXPECT_CALL(*scrollPn, IsAtTop).WillRepeatedly(Return(true));
    auto refreshNode = FrameNode::CreateFrameNode("Refresh", -1, AceType::MakeRefPtr<RefreshPattern>());
    scroll_->MountToParent(refreshNode);
    refreshNode->MarkModifyDone();

    /**
     * @tc.steps: step3. Call the CoordinateWithRefresh method
     * @tc.expected: The result is UNKNOWN
     */
    offset = 5.0f;
    result = scrollPn->CoordinateWithRefresh(offset, SCROLL_FROM_START, false);
    EXPECT_EQ(result, RefreshCoordinationMode::UNKNOWN);
    EXPECT_TRUE(scrollPn->refreshCoordination_);
    EXPECT_FALSE(scrollPn->isRefreshInReactive_);
    EXPECT_EQ(offset, 5.0f);

    scrollPn->isRefreshInReactive_ = true;
    result = scrollPn->CoordinateWithRefresh(offset, SCROLL_FROM_START, false);
    EXPECT_EQ(result, RefreshCoordinationMode::UNKNOWN);

    scrollPn->isRefreshInReactive_ = true;
    result = scrollPn->CoordinateWithRefresh(offset, SCROLL_FROM_UPDATE, false);
    EXPECT_FALSE(scrollPn->refreshCoordination_->InCoordination());
    EXPECT_NE(result, RefreshCoordinationMode::REFRESH_SCROLL);
    EXPECT_EQ(offset, 5.0f);

    /**
     * @tc.steps: step4. Call the SetMaxFlingVelocity method
     * @tc.expected: The maxFlingVelocity is MAX_VELOCITY or max
     */
    double max = 0.0f;
    scrollPn->SetMaxFlingVelocity(max);
    EXPECT_EQ(scrollPn->maxFlingVelocity_, MAX_VELOCITY);
    max = 0.2f;
    scrollPn->SetMaxFlingVelocity(max);
    EXPECT_EQ(scrollPn->maxFlingVelocity_, 0.2f);

    /**
     * @tc.steps: step5. Set the correctVelocity is -3000
     * Set the friction is 0.9
     * Set the frictionScale is -4.2
     * Calculate the position finalPosition that should be scrolled to through a formula
     * Get object scrollable and Call the SetFriction method
     * Call the Fling method and pass the correctVelocity parameter
     * Obtain the actual scrolling position finalPosition_
     * @tc.expected: The values of finalPosition_ and finalPosition are the same
     */
    float correctVelocity = -3000.0f;
    float friction = 0.9f;
    float frictionScale = -4.2f;
    float finalPosition = correctVelocity / (friction * -frictionScale);
    auto scrollableEvent = scrollPn->GetScrollableEvent();
    auto scrollable = scrollableEvent->GetScrollable();
    scrollable->SetFriction(friction);
    scrollPn->Fling(correctVelocity);
    float finalPosition_ = scrollable->finalPosition_;
    EXPECT_EQ(finalPosition_, finalPosition);
}

/**
 * @tc.name: Fling017
 * @tc.desc: Test nested Fling
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableFlingTestNg, Fling017, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize ScrollablePattern type pointer
     * @tc.expected: Pointer is not nullptr.
     */
    auto mockPn = AceType::MakeRefPtr<FullyMockedScrollable>();
    mockScroll_->pattern_ = mockPn;
    auto scrollPn = scroll_->GetPattern<PartiallyMockedScrollable>();
    EXPECT_TRUE(scrollPn);
    scrollPn->parent_ = mockPn;

    /**
     * @tc.steps: step2. Call the MarkSelectedItems method
     * @tc.expected: The IsScrollable is false
     */
    scrollPn->MarkSelectedItems();
    EXPECT_FALSE(scrollPn->IsScrollable());
    scrollPn->multiSelectable_ = true;
    scrollPn->MarkSelectedItems();
    EXPECT_FALSE(scrollPn->IsScrollable());
    scrollPn->mousePressed_ = true;
    scrollPn->MarkSelectedItems();
    EXPECT_FALSE(scrollPn->IsScrollable());
    scrollPn->mouseStartOffset_ = OffsetF(0.0f, 0.0f);
    scrollPn->mouseEndOffset_ = OffsetF(1.0f, 1.0f);
    scrollPn->MarkSelectedItems();
    EXPECT_FALSE(scrollPn->IsScrollable());

    /**
     * @tc.steps: step3. When lastMouseMove is not nullptr, call the MarkSelectedItems method
     * @tc.expected: The result is false
     */
    scrollPn->GetHost();
    scrollPn->parent_ = mockPn;
    scrollPn->mousePressed_ = true;
    scrollPn->SetAxis(Axis::HORIZONTAL);
    Offset localLocation;
    localLocation.SetX(-1.1f);
    scrollPn->lastMouseMove_.SetLocalLocation(localLocation);
    EXPECT_EQ(scrollPn->lastMouseMove_.GetLocalLocation().GetX(), -1.1f);
    auto result = scrollPn->ShouldSelectScrollBeStopped();
    EXPECT_FALSE(result);

    /**
     * @tc.steps: step4. When selectMotion is not nullptr, call the MarkSelectedItems method
     * @tc.expected: The result is false
     */
    scrollPn->selectMotion_ = AceType::MakeRefPtr<SelectMotion>(0.0f, [this]() -> bool { return true; });
    result = scrollPn->ShouldSelectScrollBeStopped();
    EXPECT_FALSE(result);

    /**
     * @tc.steps: step5. When lastMouseMove is not nullptr, call the MarkSelectedItems method
     * @tc.expected: The result is true
     */
    scrollPn->SetAxis(Axis::VERTICAL);
    localLocation.SetY(-0.0f);
    scrollPn->lastMouseMove_.SetLocalLocation(localLocation);
    EXPECT_EQ(scrollPn->lastMouseMove_.GetLocalLocation().GetY(), -0.0f);
    result = scrollPn->ShouldSelectScrollBeStopped();
    EXPECT_TRUE(result);

    /**
     * @tc.steps: step6. Set the correctVelocity is -3000
     * Set the friction is 0.9
     * Set the frictionScale is -4.2
     * Calculate the position finalPosition that should be scrolled to through a formula
     * Get object scrollable and Call the SetFriction method
     * Call the Fling method and pass the correctVelocity parameter
     * Obtain the actual scrolling position finalPosition_
     * @tc.expected: The values of finalPosition_ and finalPosition are the same
     */
    float correctVelocity = -3000.0f;
    float friction = 0.9f;
    float frictionScale = -4.2f;
    float finalPosition = correctVelocity / (friction * -frictionScale);
    auto scrollableEvent = scrollPn->GetScrollableEvent();
    auto scrollable = scrollableEvent->GetScrollable();
    scrollable->SetFriction(friction);
    scrollPn->Fling(correctVelocity);
    float finalPosition_ = scrollable->finalPosition_;
    EXPECT_EQ(finalPosition_, finalPosition);
}

/**
 * @tc.name: Fling018
 * @tc.desc: Test nested Fling
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableFlingTestNg, Fling018, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize ScrollablePattern type pointer
     * @tc.expected: Pointer is not nullptr.
     */
    auto mockPn = AceType::MakeRefPtr<FullyMockedScrollable>();
    mockScroll_->pattern_ = mockPn;
    auto scrollPn = scroll_->GetPattern<PartiallyMockedScrollable>();
    EXPECT_TRUE(scrollPn);
    scrollPn->parent_ = mockPn;

    /**
     * @tc.steps: step2. Set the parameter scrollable to be nullptr
     * @tc.expected: Scrollable is nullptr
     */
    RefPtr<Scrollable> scrollable = nullptr;
    scrollPn->scrollableEvent_ = AceType::MakeRefPtr<ScrollableEvent>(Axis::VERTICAL);
    scrollPn->scrollableEvent_->SetScrollable(scrollable);
    scrollPn->SetCanOverScroll(false);
    EXPECT_EQ(scrollPn->scrollableEvent_->GetScrollable(), nullptr);

    /**
     * @tc.steps: step3. Set the parameter scrollable is true and IsAtBottom is false
     * @tc.expected: Scrollable is not nullptr
     */
    EXPECT_CALL(*scrollPn, IsAtBottom).WillRepeatedly(Return(false));
    scrollPn->scrollableEvent_ = AceType::MakeRefPtr<ScrollableEvent>(Axis::VERTICAL);
    scrollable =
        AceType::MakeRefPtr<Scrollable>([](double, int32_t source) -> bool { return true; }, Axis::VERTICAL);
    scrollPn->scrollableEvent_->SetScrollable(scrollable);
    EXPECT_NE(scrollPn->scrollableEvent_->GetScrollable(), nullptr);

    /**
     * @tc.steps: step5. Call the GetCanOverScroll method, Set the parameter scrollable is false
     * @tc.expected: The result is true
     */
    scrollPn->scrollableEvent_ = AceType::MakeRefPtr<ScrollableEvent>(Axis::VERTICAL);
    auto result = scrollPn->GetCanOverScroll();
    EXPECT_TRUE(result);

    /**
     * @tc.steps: step6. Call the GetCanOverScroll method, Set the parameter scrollable is true
     * @tc.expected: The result is true
     */
    scrollable =
        AceType::MakeRefPtr<Scrollable>([](double, int32_t source) -> bool { return true; }, Axis::VERTICAL);
    scrollPn->scrollableEvent_->SetScrollable(scrollable);
    result = scrollPn->GetCanOverScroll();
    EXPECT_TRUE(result);

    /**
     * @tc.steps: step7. Set the correctVelocity is -5000
     * Set the friction is 0.6
     * Set the frictionScale is -4.2
     * Calculate the position finalPosition that should be scrolled to through a formula
     * Get object scrollable and Call the SetFriction method
     * Call the Fling method and pass the correctVelocity parameter
     * Obtain the actual scrolling position finalPosition_
     * @tc.expected: The values of finalPosition_ and finalPosition are the same
     */
    float correctVelocity = -5000.0f;
    float friction = 0.6f;
    float frictionScale = -4.2f;
    float finalPosition = correctVelocity / (friction * -frictionScale);
    auto scrollableEvent = scrollPn->GetScrollableEvent();
    scrollable = scrollableEvent->GetScrollable();
    scrollable->SetFriction(friction);
    scrollPn->Fling(correctVelocity);
    float finalPosition_ = scrollable->finalPosition_;
    EXPECT_EQ(finalPosition_, finalPosition);
}

/**
 * @tc.name: CreateCoordinationEvent001
 * @tc.desc: Test CreateCoordinationEvent without OnScrollStart OnScrollEnd
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableFlingTestNg, CreateCoordinationEvent001, TestSize.Level1)
{
    auto scrollPn = scroll_->GetPattern<PartiallyMockedScrollable>();
    auto refreshNode = FrameNode::CreateFrameNode("Refresh", -1, AceType::MakeRefPtr<RefreshPattern>());
    scroll_->MountToParent(refreshNode);
    refreshNode->MarkModifyDone();
    scrollPn->refreshCoordination_ = AceType::MakeRefPtr<RefreshCoordination>(scrollPn->GetHost());
    auto refreshCoordination = scrollPn->refreshCoordination_;
    ASSERT_NE(refreshCoordination->coordinationEvent_, nullptr);
    bool isEndCalled = false;
    bool isStartCalled = false;
    auto scollEndCallback = [&isEndCalled](float mainVelocity) {
        isEndCalled = true;
        return;
    };
    auto scollstartCallback = [&isStartCalled](bool isDrag, float mainVelocity) {
        isStartCalled = true;
        return;
    };
    /**
     * @tc.steps: step1. Call the CreateCoordinationEvent when coordinationEvent_ exists
     */
    refreshCoordination->CreateCoordinationEvent();
    /**
     * @tc.steps: step2. Call methods when callback not exists
     */
    refreshCoordination->coordinationEvent_->SetOnScrollStartEvent(scollstartCallback);
    refreshCoordination->coordinationEvent_->SetOnScrollEndEvent(scollEndCallback);
    refreshCoordination->coordinationEvent_->onScrollStartEvent_ = nullptr;
    ASSERT_EQ(refreshCoordination->coordinationEvent_->GetOnScrollStartEvent(), nullptr);
    refreshCoordination->coordinationEvent_->onScrollEndEvent_ = nullptr;
    ASSERT_EQ(refreshCoordination->coordinationEvent_->GetOnScrollEndEvent(), nullptr);
    refreshCoordination->OnScrollStart(true, 1.0f);
    refreshCoordination->OnScrollEnd(2.0f);
    EXPECT_FALSE(isEndCalled);
    EXPECT_FALSE(isStartCalled);
}
} // namespace OHOS::Ace::NG
