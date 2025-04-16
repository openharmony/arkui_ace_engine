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

#include "scrollable_test_ng.h"

#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pattern/mock_nestable_scroll_container.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/unittest/core/pattern/scrollable/mock_scrollable.h"
#define protected public
#define private public
#include "core/components_ng/pattern/refresh/refresh_pattern.h"
#include "core/components_ng/pattern/scrollable/scrollable_model_ng.h"
#include "core/components_ng/pattern/scrollable/scrollable_properties.h"
#include "core/components_ng/pattern/scrollable/axis/axis_animator.h"

namespace OHOS::Ace::NG {
#ifdef SUPPORT_DIGITAL_CROWN
constexpr float TEST_ANGULAR_VELOCITY_SLOW = 70.f;
constexpr float TEST_ANGULAR_VELOCITY_MEDIUM = 200.f;
constexpr float TEST_ANGULAR_VELOCITY_FAST = 540.f;
constexpr float TEST_ANGULAR_VELOCITY_VERY_FAST = 850.f;
constexpr float TEST_DISPLAY_CONTROL_RATIO_VERY_SLOW = 0.85f;
constexpr float TEST_DISPLAY_CONTROL_RATIO_SLOW = 1.85f;
constexpr float TEST_DISPLAY_CONTROL_RATIO_MEDIUM = 2.15f;
constexpr float TEST_DISPLAY_CONTROL_RATIO_FAST = 1.35f;
constexpr float TEST_CROWN_SENSITIVITY_LOW = 0.8f;
constexpr float TEST_CROWN_SENSITIVITY_MEDIUM = 1.0f;
constexpr float TEST_CROWN_SENSITIVITY_HIGH = 1.2f;
constexpr int32_t TEST_CROWN_EVENT_NUN_THRESH = 29;
constexpr float TEST_CROWN_VELOCITY = 10.f;
#endif

void ScrollableTestNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto scrollableThemeConstants = CreateThemeConstants(THEME_PATTERN_SCROLLABLE);
    auto scrollableTheme = ScrollableTheme::Builder().Build(scrollableThemeConstants);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(scrollableTheme));
    MockContainer::Current()->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    MockPipelineContext::GetCurrent()->SetUseFlushUITasks(true);
}

void ScrollableTestNg::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

void ScrollableTestNg::SetUp()
{
    InitNestedScrolls();
}

void ScrollableTestNg::TearDown()
{
    scroll_.Reset();
    mockScroll_.Reset();
}

void ScrollableTestNg::InitNestedScrolls()
{
    ResetElmtId();
    ViewStackProcessor::GetInstance()->StartGetAccessRecordingFor(GetElmtId());
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    scroll_ = FrameNode::CreateFrameNode(V2::SCROLL_ETS_TAG, nodeId, AceType::MakeRefPtr<PartiallyMockedScrollable>());
    stack->Push(scroll_);
    mockScroll_ = FrameNode::CreateFrameNode("mockScroll", -1, AceType::MakeRefPtr<MockNestableScrollContainer>());
    scroll_->MountToParent(mockScroll_);
    auto scrollOn = scroll_->GetPattern<PartiallyMockedScrollable>();
    scrollOn->nestedScroll_ = { .forward = NestedScrollMode::PARALLEL, .backward = NestedScrollMode::PARALLEL };
    scrollOn->SetParentScrollable();
    scrollOn->AddScrollEvent();
    scrollOn->SetEdgeEffect();
}

/**
 * @tc.name: HandleScrollVelocity001
 * @tc.desc: Test nested HandleScroll onScrollStart
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, HandleScrollVelocity001, TestSize.Level1)
{
    auto mockOn = AceType::MakeRefPtr<FullyMockedScrollable>();
    mockScroll_->pattern_ = mockOn;
    auto scrollOn = scroll_->GetPattern<PartiallyMockedScrollable>();
    scrollOn->parent_ = mockOn;

    EXPECT_CALL(*mockOn, HandleScrollVelocity).Times(0);
    EXPECT_CALL(*scrollOn, IsAtTop).WillRepeatedly(Return(true));
    scrollOn->scrollEffect_ = AceType::MakeRefPtr<ScrollEdgeEffect>(EdgeEffect::SPRING);
    scrollOn->edgeEffect_ = EdgeEffect::SPRING;
    scrollOn->nestedScroll_ = { .forward = NestedScrollMode::SELF_ONLY, .backward = NestedScrollMode::SELF_ONLY };

    bool res = scrollOn->HandleScrollVelocity(5);
    EXPECT_TRUE(res);

    scrollOn->scrollEffect_ = AceType::MakeRefPtr<ScrollEdgeEffect>(EdgeEffect::NONE);
    scrollOn->edgeEffect_ = EdgeEffect::NONE;
    res = scrollOn->HandleScrollVelocity(5);
    EXPECT_FALSE(res);
}

/**
 * @tc.name: HandleScrollVelocity002
 * @tc.desc: Test nested HandleScroll onScrollStart
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, HandleScrollVelocity002, TestSize.Level1)
{
    auto mockOn = AceType::MakeRefPtr<FullyMockedScrollable>();
    mockScroll_->pattern_ = mockOn;
    auto scrollOn = scroll_->GetPattern<PartiallyMockedScrollable>();
    scrollOn->parent_ = mockOn;

    EXPECT_CALL(*mockOn, OutBoundaryCallback).WillRepeatedly(Return(true));
    EXPECT_CALL(*mockOn, HandleScrollVelocity).Times(1).WillOnce(Return(true));
    EXPECT_CALL(*scrollOn, IsAtTop).WillRepeatedly(Return(true));
    scrollOn->nestedScroll_ = { .forward = NestedScrollMode::SELF_FIRST, .backward = NestedScrollMode::SELF_FIRST };
    bool res = scrollOn->HandleScrollVelocity(5);
    EXPECT_TRUE(res);

    EXPECT_CALL(*mockOn, HandleScrollVelocity).Times(1).WillOnce(Return(true));
    scrollOn->scrollEffect_ = AceType::MakeRefPtr<ScrollEdgeEffect>(EdgeEffect::SPRING);
    scrollOn->edgeEffect_ = EdgeEffect::SPRING;
    res = scrollOn->HandleScrollVelocity(5);
    EXPECT_TRUE(res);
}

/**
 * @tc.name: HandleScrollVelocity003
 * @tc.desc: Test nested HandleScroll onScrollStart
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, HandleScrollVelocity003, TestSize.Level1)
{
    auto mockOn = AceType::MakeRefPtr<FullyMockedScrollable>();
    mockScroll_->pattern_ = mockOn;
    auto scrollOn = scroll_->GetPattern<PartiallyMockedScrollable>();
    scrollOn->parent_ = mockOn;

    EXPECT_CALL(*mockOn, OutBoundaryCallback).WillRepeatedly(Return(true));
    EXPECT_CALL(*mockOn, HandleScrollVelocity).Times(1).WillRepeatedly(Return(true));
    EXPECT_CALL(*scrollOn, IsAtTop).WillRepeatedly(Return(true));
    scrollOn->nestedScroll_ = { .forward = NestedScrollMode::SELF_FIRST, .backward = NestedScrollMode::SELF_FIRST };
    scrollOn->scrollEffect_ = AceType::MakeRefPtr<ScrollEdgeEffect>(EdgeEffect::FADE);
    scrollOn->edgeEffect_ = EdgeEffect::FADE;
    bool res = scrollOn->HandleScrollVelocity(5);
    EXPECT_TRUE(res);
}

/**
 * @tc.name: HandleScrollVelocity004
 * @tc.desc: Test nested HandleScroll onScrollStart
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, HandleScrollVelocity004, TestSize.Level1)
{
    auto mockOn = AceType::MakeRefPtr<FullyMockedScrollable>();
    mockScroll_->pattern_ = mockOn;
    auto scrollOn = scroll_->GetPattern<PartiallyMockedScrollable>();
    scrollOn->parent_ = mockOn;

    EXPECT_CALL(*mockOn, HandleScrollVelocity).Times(0);
    EXPECT_CALL(*scrollOn, IsOutOfBoundary).WillRepeatedly(Return(true));
    EXPECT_CALL(*scrollOn, IsAtTop).WillRepeatedly(Return(true));
    scrollOn->nestedScroll_ = { .forward = NestedScrollMode::PARENT_FIRST, .backward = NestedScrollMode::PARENT_FIRST };
    scrollOn->scrollEffect_ = AceType::MakeRefPtr<ScrollEdgeEffect>(EdgeEffect::SPRING);
    scrollOn->edgeEffect_ = EdgeEffect::SPRING;
    bool res = scrollOn->HandleScrollVelocity(5);
    EXPECT_TRUE(res);
}

/**
 * @tc.name: HandleScrollVelocity005
 * @tc.desc: Test nested HandleScroll with different scroll mode forward/backward
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, HandleScrollVelocity005, TestSize.Level1)
{
    auto mockOn = AceType::MakeRefPtr<FullyMockedScrollable>();
    mockScroll_->pattern_ = mockOn;
    auto scrollOn = scroll_->GetPattern<PartiallyMockedScrollable>();
    scrollOn->parent_ = mockOn;

    EXPECT_CALL(*mockOn, HandleScrollVelocity).Times(0);
    EXPECT_CALL(*scrollOn, IsAtTop).WillRepeatedly(Return(true));
    scrollOn->scrollEffect_ = AceType::MakeRefPtr<ScrollEdgeEffect>(EdgeEffect::SPRING);
    scrollOn->edgeEffect_ = EdgeEffect::SPRING;
    scrollOn->nestedScroll_ = { .forward = NestedScrollMode::PARENT_FIRST, .backward = NestedScrollMode::SELF_ONLY };

    bool res = scrollOn->HandleScrollVelocity(5);
    EXPECT_TRUE(res);

    scrollOn->scrollEffect_ = AceType::MakeRefPtr<ScrollEdgeEffect>(EdgeEffect::NONE);
    scrollOn->edgeEffect_ = EdgeEffect::NONE;
    res = scrollOn->HandleScrollVelocity(5);
    EXPECT_FALSE(res);
}

/**
 * @tc.name: HandleScrollVelocity006
 * @tc.desc: Test HandleScrollVelocity without scrollableEvent, shouldn't crash
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, HandleScrollVelocity006, TestSize.Level1)
{
    auto mockOn = AceType::MakeRefPtr<FullyMockedScrollable>();
    mockScroll_->pattern_ = mockOn;
    auto scrollOn = scroll_->GetPattern<PartiallyMockedScrollable>();
    scrollOn->parent_ = mockOn;

    EXPECT_CALL(*mockOn, HandleScrollVelocity).Times(0);
    EXPECT_CALL(*scrollOn, IsAtTop).WillRepeatedly(Return(false));

    scrollOn->scrollableEvent_.Reset();
    bool res = scrollOn->HandleScrollVelocity(5);
    EXPECT_FALSE(res);
}

/**
 * @tc.name: OnScrollStart001
 * @tc.desc: Test nested HandleScroll onScrollStart
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, OnScrollStart001, TestSize.Level1)
{
    auto scrollOn = scroll_->GetPattern<PartiallyMockedScrollable>();
    auto mockOn = mockScroll_->GetPattern<MockNestableScrollContainer>();
    EXPECT_CALL(*scrollOn, IsAtTop).Times(AtLeast(1));
    EXPECT_CALL(*mockOn, GetAxis).Times(1);

    EXPECT_CALL(*mockOn, OnScrollStartRecursive).Times(1);
    scrollOn->OnScrollStartRecursive(scrollOn, 5.0f);
}

/**
 * @tc.name: OnScrollEnd001
 * @tc.desc: Test nested HandleScroll onScrollEnd
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, OnScrollEnd001, TestSize.Level1)
{
    auto scrollOn = scroll_->GetPattern<PartiallyMockedScrollable>();
    auto mockOn = mockScroll_->GetPattern<MockNestableScrollContainer>();
    EXPECT_CALL(*mockOn, OnScrollEndRecursive).Times(1);
    scrollOn->OnScrollEndRecursive(std::nullopt);
}

HWTEST_F(ScrollableTestNg, IsInHotZone001, TestSize.Level1)
{
    auto scrollOn = scroll_->GetPattern<PartiallyMockedScrollable>();
    auto pipeLine = PipelineBase::GetCurrentContext();
    auto frameNode = scrollOn->GetHost();
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    geometryNode->SetFrameSize(SizeF(700.0, 1200.0));
    frameNode->SetGeometryNode(geometryNode);

    scrollOn->SetAxis(Axis::VERTICAL);
    EXPECT_TRUE(scrollOn->IsInHotZone(PointF(80.0, 250.0)) == 0.0f);
    EXPECT_TRUE(Positive(scrollOn->IsInHotZone(PointF(0.0, 0.0))));
    EXPECT_TRUE(Negative(scrollOn->IsInHotZone(PointF(0.0, 1200.0))));

    scrollOn->SetAxis(Axis::HORIZONTAL);
    EXPECT_TRUE(Positive(scrollOn->IsInHotZone(PointF(0.0, 0.0))));
    EXPECT_TRUE(Negative(scrollOn->IsInHotZone(PointF(700.0, 0.0))));
}

HWTEST_F(ScrollableTestNg, IsVertical, TestSize.Level1)
{
    auto scrollOn = scroll_->GetPattern<PartiallyMockedScrollable>();
    scrollOn->SetAxis(Axis::HORIZONTAL);
    EXPECT_FALSE(scrollOn->isVertical());
    scrollOn->SetAxis(Axis::VERTICAL);
    EXPECT_TRUE(scrollOn->isVertical());
}

HWTEST_F(ScrollableTestNg, HandleMoveEventInComp, TestSize.Level1)
{
    auto scrollOn = scroll_->GetPattern<PartiallyMockedScrollable>();
    EXPECT_CALL(*scrollOn, IsScrollable).Times(1).WillOnce(Return(true));
    auto pt = PointF(0.0, 0.0);
    auto host = scrollOn->GetHost();
    auto geometryNode = host->GetGeometryNode();
    geometryNode->SetFrameWidth(100);
    scrollOn->HandleMoveEventInComp(pt);
    EXPECT_TRUE(scrollOn->velocityMotion_);
    EXPECT_TRUE(scrollOn->animator_);
    pt = PointF(80.0, 250.0);
    scrollOn->HandleMoveEventInComp(pt);
    EXPECT_TRUE(scrollOn->animator_->IsStopped());
}

HWTEST_F(ScrollableTestNg, HotZoneScroll, TestSize.Level1)
{
    auto scrollOn = scroll_->GetPattern<PartiallyMockedScrollable>();
    float offsetPct = 0.5f;
    EXPECT_CALL(*scrollOn, IsScrollable).Times(1).WillOnce(Return(true));
    scrollOn->HotZoneScroll(offsetPct);
    EXPECT_TRUE(scrollOn->animator_);
    EXPECT_TRUE(scrollOn->velocityMotion_);
    EXPECT_TRUE(NearEqual(scrollOn->lastHonezoneOffsetPct_, offsetPct));
}

/**
 * @tc.name: SetCanOverScroll001
 * @tc.desc: Test nested SetCanOverScroll failure status
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, SetCanOverScroll001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize ScrollablePattern type pointer
     * @tc.expected: Pointer is not nullptr.
     */
    auto mockOn = AceType::MakeRefPtr<FullyMockedScrollable>();
    mockScroll_->pattern_ = mockOn;
    auto scrollOn = scroll_->GetPattern<PartiallyMockedScrollable>();
    scrollOn->parent_ = mockOn;

    /**
     * @tc.steps: step2. Set the parameter scrollable to be nullptr
     * @tc.expected: Scrollable is nullptr
     */
    RefPtr<Scrollable> scrollable = nullptr;
    scrollOn->scrollableEvent_ = AceType::MakeRefPtr<ScrollableEvent>(Axis::VERTICAL);
    scrollOn->scrollableEvent_->SetScrollable(scrollable);
    scrollOn->SetCanOverScroll(false);
    EXPECT_EQ(scrollOn->scrollableEvent_->GetScrollable(), nullptr);
}

/**
 * @tc.name: HandleScrollVelocity007
 * @tc.desc: Test nested HandleScrollVelocity for IsAtBottom
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, HandleScrollVelocity007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize ScrollablePattern type pointer
     * @tc.expected: Pointer is not nullptr.
     */
    auto mockOn = AceType::MakeRefPtr<FullyMockedScrollable>();
    mockScroll_->pattern_ = mockOn;
    auto scrollOn = scroll_->GetPattern<PartiallyMockedScrollable>();
    scrollOn->parent_ = mockOn;

    /**
     * @tc.steps: step2. Set the parameter scrollable is true and IsAtBottom is false
     * @tc.expected: Scrollable is not nullptr
     */
    EXPECT_CALL(*scrollOn, IsAtBottom).WillRepeatedly(Return(false));
    scrollOn->scrollableEvent_ = AceType::MakeRefPtr<ScrollableEvent>(Axis::VERTICAL);
    auto scrollable =
        AceType::MakeRefPtr<Scrollable>([](double, int32_t source) -> bool { return true; }, Axis::VERTICAL);
    scrollOn->scrollableEvent_->SetScrollable(scrollable);
    EXPECT_NE(scrollOn->scrollableEvent_->GetScrollable(), nullptr);

    /**
     * @tc.steps: step3. Call the HandleScrollVelocity method
     * @tc.expected: The result is true
     */
    bool res = scrollOn->HandleScrollVelocity(-1.1f);
    EXPECT_TRUE(res);
}

/**
 * @tc.name: IsReverse001
 * @tc.desc: Test nested IsReverse for IsAtBottom
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, IsReverse001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize ScrollablePattern type pointer
     * @tc.expected: Pointer is not nullptr.
     */
    auto mockOn = AceType::MakeRefPtr<FullyMockedScrollable>();
    mockScroll_->pattern_ = mockOn;
    auto scrollOn = scroll_->GetPattern<PartiallyMockedScrollable>();
    scrollOn->parent_ = mockOn;

    /**
     * @tc.steps: step2. Set the parameter scrollable to be nullptr
     * @tc.expected: Scrollable is nullptr
     */
    EXPECT_CALL(*scrollOn, IsAtBottom).WillRepeatedly(Return(false));
    scrollOn->scrollableEvent_ = AceType::MakeRefPtr<ScrollableEvent>(Axis::VERTICAL);
    auto scrollable =
        AceType::MakeRefPtr<Scrollable>([](double, int32_t source) -> bool { return true; }, Axis::VERTICAL);
    scrollOn->scrollableEvent_->SetScrollable(scrollable);
    EXPECT_NE(scrollOn->scrollableEvent_->GetScrollable(), nullptr);

    /**
     * @tc.steps: step3. Call the IsReverse method
     * @tc.expected: The result is false
     */
    bool res = scrollOn->IsReverse();
    EXPECT_NE(res, true);
}

/**
 * @tc.name: GetCanOverScroll001
 * @tc.desc: Test nested GetCanOverScroll
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, GetCanOverScroll001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize ScrollablePattern type pointer
     * @tc.expected: Pointer is not nullptr.
     */
    auto mockOn = AceType::MakeRefPtr<FullyMockedScrollable>();
    mockScroll_->pattern_ = mockOn;
    auto scrollOn = scroll_->GetPattern<PartiallyMockedScrollable>();
    scrollOn->parent_ = mockOn;

    /**
     * @tc.steps: step2. Call the GetCanOverScroll method, Set the parameter scrollable is false
     * @tc.expected: The result is true
     */
    scrollOn->scrollableEvent_ = AceType::MakeRefPtr<ScrollableEvent>(Axis::VERTICAL);
    auto result = scrollOn->GetCanOverScroll();
    EXPECT_TRUE(result);

    /**
     * @tc.steps: step3. Call the GetCanOverScroll method, Set the parameter scrollable is true
     * @tc.expected: The result is true
     */
    auto scrollable =
        AceType::MakeRefPtr<Scrollable>([](double, int32_t source) -> bool { return true; }, Axis::VERTICAL);
    scrollOn->scrollableEvent_->SetScrollable(scrollable);
    result = scrollOn->GetCanOverScroll();
    EXPECT_TRUE(result);
}

/**
 * @tc.name: SelectWithScroll001
 * @tc.desc: Test nested SelectWithScroll
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, SelectWithScroll001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize ScrollablePattern type pointer
     * @tc.expected: Pointer is not nullptr.
     */
    auto mockOn = AceType::MakeRefPtr<FullyMockedScrollable>();
    mockScroll_->pattern_ = mockOn;
    auto scrollOn = scroll_->GetPattern<PartiallyMockedScrollable>();
    scrollOn->parent_ = mockOn;

    /**
     * @tc.steps: step2. Call the SelectWithScroll method, Set the parameter IsScrollable is false
     * @tc.expected: The OutOfScrollableOffset is 0.0
     */
    EXPECT_CALL(*scrollOn, IsScrollable).Times(1).WillOnce(Return(false));
    scrollOn->SelectWithScroll();
    EXPECT_EQ(scrollOn->GetOutOfScrollableOffset(), 0.0f);
}

/**
 * @tc.name: SelectWithScroll002
 * @tc.desc: Test nested SelectWithScroll
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, SelectWithScroll002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize ScrollablePattern type pointer
     * @tc.expected: Pointer is not nullptr.
     */
    auto mockOn = AceType::MakeRefPtr<FullyMockedScrollable>();
    mockScroll_->pattern_ = mockOn;
    auto scrollOn = scroll_->GetPattern<PartiallyMockedScrollable>();
    scrollOn->parent_ = mockOn;

    /**
     * @tc.steps: step2. Call the SelectWithScroll method, Set the parameter IsScrollable is true
     * @tc.expected: The OutOfScrollableOffset is -1.1
     */
    EXPECT_CALL(*scrollOn, IsScrollable).Times(1).WillOnce(Return(true));
    EXPECT_CALL(*scrollOn, IsAtTop).Times(1);
    scrollOn->SetAxis(Axis::VERTICAL);
    Offset localLocation;
    localLocation.SetX(-1.0f);
    localLocation.SetY(-1.1f);
    scrollOn->lastMouseMove_.SetLocalLocation(localLocation);
    scrollOn->SelectWithScroll();
    EXPECT_EQ(scrollOn->lastMouseMove_.GetLocalLocation().GetY(), -1.1f);
}

/**
 * @tc.name: SelectWithScroll003
 * @tc.desc: Test nested SelectWithScroll
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, SelectWithScroll003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize ScrollablePattern type pointer
     * @tc.expected: Pointer is not nullptr.
     */
    auto mockOn = AceType::MakeRefPtr<FullyMockedScrollable>();
    mockScroll_->pattern_ = mockOn;
    auto scrollOn = scroll_->GetPattern<PartiallyMockedScrollable>();
    scrollOn->parent_ = mockOn;

    /**
     * @tc.steps: step2. Call the SelectWithScroll method, Set the parameter IsScrollable is true and deltaY_ is 0
     * @tc.expected: The OutOfScrollableOffset is -1.1
     */
    EXPECT_CALL(*scrollOn, IsScrollable).Times(1).WillOnce(Return(true));
    scrollOn->SetAxis(Axis::VERTICAL);
    Offset localLocation;
    localLocation.SetX(-1.0f);
    localLocation.SetY(0.0f);
    scrollOn->lastMouseMove_.SetLocalLocation(localLocation);
    scrollOn->SelectWithScroll();
    EXPECT_EQ(scrollOn->lastMouseMove_.GetLocalLocation().GetY(), 0.0f);
}

/**
 * @tc.name: SelectWithScroll004
 * @tc.desc: Test nested SelectWithScroll
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, SelectWithScroll004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize ScrollablePattern type pointer
     * @tc.expected: Pointer is not nullptr.
     */
    auto mockOn = AceType::MakeRefPtr<FullyMockedScrollable>();
    mockScroll_->pattern_ = mockOn;
    auto scrollOn = scroll_->GetPattern<PartiallyMockedScrollable>();
    scrollOn->parent_ = mockOn;

    /**
     * @tc.steps: step2. Call the SelectWithScroll method, Set the parameter isAnimationStop_ is false
     * @tc.expected: The OutOfScrollableOffset is -1.1
     */
    EXPECT_CALL(*scrollOn, IsAtTop).Times(1);
    EXPECT_CALL(*scrollOn, IsScrollable).Times(1).WillOnce(Return(true));
    scrollOn->SetAxis(Axis::VERTICAL);
    Offset localLocation;
    localLocation.SetX(-1.0f);
    localLocation.SetY(-1.1f);
    scrollOn->lastMouseMove_.SetLocalLocation(localLocation);
    scrollOn->isAnimationStop_ = false;
    scrollOn->SelectWithScroll();
    EXPECT_EQ(scrollOn->lastMouseMove_.GetLocalLocation().GetY(), -1.1f);
}

/**
 * @tc.name: SelectWithScroll005
 * @tc.desc: Test nested SelectWithScroll
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, SelectWithScroll005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize ScrollablePattern type pointer
     * @tc.expected: Pointer is not nullptr.
     */
    auto mockOn = AceType::MakeRefPtr<FullyMockedScrollable>();
    mockScroll_->pattern_ = mockOn;
    auto scrollOn = scroll_->GetPattern<PartiallyMockedScrollable>();
    scrollOn->parent_ = mockOn;

    /**
     * @tc.steps: step2. Call the SelectWithScroll method, Set the parameter isAnimationStop_ is true
     *   and selectMotion_ is not nullptr
     * @tc.expected: The OutOfScrollableOffset is -1.1
     */
    EXPECT_CALL(*scrollOn, IsAtTop).Times(1);
    EXPECT_CALL(*scrollOn, IsScrollable).Times(1).WillOnce(Return(true));
    scrollOn->SetAxis(Axis::VERTICAL);
    Offset localLocation;
    localLocation.SetX(-1.0f);
    localLocation.SetY(-1.1f);
    scrollOn->lastMouseMove_.SetLocalLocation(localLocation);
    scrollOn->isAnimationStop_ = true;
    scrollOn->selectMotion_ = AceType::MakeRefPtr<SelectMotion>(0.0f, [this]() -> bool { return true; });
    scrollOn->SelectWithScroll();
    EXPECT_EQ(scrollOn->lastMouseMove_.GetLocalLocation().GetY(), -1.1f);
}

/**
 * @tc.name: LimitMouseEndOffset001
 * @tc.desc: Test nested LimitMouseEndOffset
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, LimitMouseEndOffset001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize ScrollablePattern type pointer
     * @tc.expected: Pointer is not nullptr.
     */
    auto mockOn = AceType::MakeRefPtr<FullyMockedScrollable>();
    mockScroll_->pattern_ = mockOn;
    auto scrollOn = scroll_->GetPattern<PartiallyMockedScrollable>();
    scrollOn->parent_ = mockOn;

    /**
     * @tc.steps: step2. Call the LimitMouseEndOffset method, Set the parameter is Axis::HORIZONTAL
     *   and selectMotion_ is not nullptr
     * @tc.expected: The OutOfScrollableOffset is -1.1
     */
    scrollOn->SetAxis(Axis::HORIZONTAL);
    scrollOn->mouseEndOffset_ = OffsetF(-1.0f, -1.1f);
    scrollOn->LimitMouseEndOffset();
    EXPECT_EQ(scrollOn->mouseEndOffset_.GetX(), 0.0f);
    EXPECT_EQ(scrollOn->mouseEndOffset_.GetY(), 0.0f);

    /**
     * @tc.steps: step3. Call the LimitMouseEndOffset method, Set the parameter is Axis::VERTICAL
     *   and selectMotion_ is not nullptr
     * @tc.expected: The OutOfScrollableOffset is -1.1
     */
    scrollOn->SetAxis(Axis::VERTICAL);
    scrollOn->mouseEndOffset_ = OffsetF(1.0f, 1.1f);
    scrollOn->LimitMouseEndOffset();
    EXPECT_EQ(scrollOn->mouseEndOffset_.GetX(), 0.0f);
    EXPECT_EQ(scrollOn->mouseEndOffset_.GetY(), 0.0f);
}

/**
 * @tc.name: HotZoneScroll001
 * @tc.desc: Test nested HotZoneScroll
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, HotZoneScroll001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize ScrollablePattern type pointer
     * @tc.expected: Pointer is not nullptr.
     */
    auto mockOn = AceType::MakeRefPtr<FullyMockedScrollable>();
    mockScroll_->pattern_ = mockOn;
    auto scrollOn = scroll_->GetPattern<PartiallyMockedScrollable>();
    scrollOn->parent_ = mockOn;

    /**
     * @tc.steps: step2. Call the HotZoneScroll method, Set the parameter status of animator is idle
     * @tc.expected: The animator is not nullptr
     */
    float offsetPct = 0.5f;
    scrollOn->animator_ = CREATE_ANIMATOR(PipelineBase::GetCurrentContext());
    scrollOn->animator_->Reverse();
    EXPECT_NE(scrollOn->animator_->GetStatus(), Animator::Status::RUNNING);
    scrollOn->HotZoneScroll(offsetPct);
    EXPECT_NE(scrollOn->animator_, nullptr);

    /**
     * @tc.steps: step3. Call the HotZoneScroll method, Set the parameter is Axis::HORIZONTAL
     *   and selectMotion_ is not nullptr
     * @tc.expected: The offset is
     */
    scrollOn->velocityMotion_ =
        AceType::MakeRefPtr<BezierVariableVelocityMotion>(offsetPct, [](float offset) -> bool { return true; });
    scrollOn->HotZoneScroll(offsetPct);
    EXPECT_EQ(scrollOn->lastHonezoneOffsetPct_, 0.0f);
}

/**
 * @tc.name: CoordinateWithRefresh001
 * @tc.desc: Test nested CoordinateWithRefresh
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, CoordinateWithRefresh001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize ScrollablePattern type pointer
     * @tc.expected: Pointer is not nullptr.
     */
    auto mockOn = AceType::MakeRefPtr<FullyMockedScrollable>();
    mockScroll_->pattern_ = mockOn;
    auto scrollOn = scroll_->GetPattern<PartiallyMockedScrollable>();
    scrollOn->parent_ = mockOn;

    /**
     * @tc.steps: step2. Call the CoordinateWithRefresh method
     * @tc.expected: The result is UNKNOWN
     */
    double offset = 0.2f;
    int32_t source = 1;
    bool isAtTop = true;
    scrollOn->refreshCoordination_ = AceType::MakeRefPtr<RefreshCoordination>(scrollOn->GetHost());
    auto result = scrollOn->CoordinateWithRefresh(offset, source, isAtTop);
    EXPECT_EQ(result, RefreshCoordinationMode::UNKNOWN);
}

/**
 * @tc.name: CoordinateWithRefresh002
 * @tc.desc: Test nested CoordinateWithRefresh on SCROLL_FROM_START
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, CoordinateWithRefresh002, TestSize.Level1)
{
    auto scrollOn = scroll_->GetPattern<PartiallyMockedScrollable>();
    EXPECT_CALL(*scrollOn, IsAtTop).WillRepeatedly(Return(true));
    auto refreshNode = FrameNode::CreateFrameNode("Refresh", -1, AceType::MakeRefPtr<RefreshPattern>());
    scroll_->MountToParent(refreshNode);
    refreshNode->MarkModifyDone();
    /**
     * @tc.steps: step2. Call the CoordinateWithRefresh method
     * @tc.expected: The result is UNKNOWN
     */
    double offset = 5.0f;
    auto result = scrollOn->CoordinateWithRefresh(offset, SCROLL_FROM_START, false);
    EXPECT_EQ(result, RefreshCoordinationMode::UNKNOWN);
    EXPECT_FALSE(scrollOn->refreshCoordination_);
    EXPECT_FALSE(scrollOn->isRefreshInReactive_);
    EXPECT_EQ(offset, 5.0f);

    scrollOn->isRefreshInReactive_ = true;
    result = scrollOn->CoordinateWithRefresh(offset, SCROLL_FROM_START, false);
    EXPECT_EQ(result, RefreshCoordinationMode::UNKNOWN);

    scrollOn->isRefreshInReactive_ = true;
    result = scrollOn->CoordinateWithRefresh(offset, SCROLL_FROM_UPDATE, false);
    EXPECT_TRUE(scrollOn->refreshCoordination_->InCoordination());
    EXPECT_EQ(result, RefreshCoordinationMode::REFRESH_SCROLL);
    EXPECT_EQ(offset, 5.0f);
}

/**
 * @tc.name: SetMaxFlingVelocity001
 * @tc.desc: Test nested SetMaxFlingVelocity
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, SetMaxFlingVelocity001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize ScrollablePattern type pointer
     * @tc.expected: Pointer is not nullptr.
     */
    auto mockOn = AceType::MakeRefPtr<FullyMockedScrollable>();
    mockScroll_->pattern_ = mockOn;
    auto scrollOn = scroll_->GetPattern<PartiallyMockedScrollable>();
    scrollOn->parent_ = mockOn;

    /**
     * @tc.steps: step2. Call the SetMaxFlingVelocity method
     * @tc.expected: The maxFlingVelocity is MAX_VELOCITY or max
     */
    double max = 0.0f;
    scrollOn->SetMaxFlingVelocity(max);
    EXPECT_EQ(scrollOn->maxFlingVelocity_, MAX_VELOCITY);
    max = 0.2f;
    scrollOn->SetMaxFlingVelocity(max);
    EXPECT_EQ(scrollOn->maxFlingVelocity_, 0.2f);
}

/**
 * @tc.name: MarkSelectedItems001
 * @tc.desc: Test nested MarkSelectedItems
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, MarkSelectedItems001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize ScrollablePattern type pointer
     * @tc.expected: Pointer is not nullptr.
     */
    auto mockOn = AceType::MakeRefPtr<FullyMockedScrollable>();
    mockScroll_->pattern_ = mockOn;
    auto scrollOn = scroll_->GetPattern<PartiallyMockedScrollable>();
    scrollOn->parent_ = mockOn;

    /**
     * @tc.steps: step2. Call the MarkSelectedItems method
     * @tc.expected: The IsScrollable is false
     */
    scrollOn->MarkSelectedItems();
    EXPECT_FALSE(scrollOn->IsScrollable());
    scrollOn->multiSelectable_ = true;
    scrollOn->MarkSelectedItems();
    EXPECT_FALSE(scrollOn->IsScrollable());
    scrollOn->mousePressed_ = true;
    scrollOn->MarkSelectedItems();
    EXPECT_FALSE(scrollOn->IsScrollable());
    scrollOn->mouseStartOffset_ = OffsetF(0.0f, 0.0f);
    scrollOn->mouseEndOffset_ = OffsetF(1.0f, 1.0f);
    scrollOn->MarkSelectedItems();
    EXPECT_FALSE(scrollOn->IsScrollable());
}

/**
 * @tc.name: ShouldSelectScrollBeStopped001
 * @tc.desc: Test nested ShouldSelectScrollBeStopped
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, ShouldSelectScrollBeStopped001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize ScrollablePattern type pointer
     * @tc.expected: Pointer is not nullptr.
     */
    auto mockOn = AceType::MakeRefPtr<FullyMockedScrollable>();
    mockScroll_->pattern_ = mockOn;
    auto scrollOn = scroll_->GetPattern<PartiallyMockedScrollable>();

    /**
     * @tc.steps: step2. When lastMouseMove is not nullptr, call the MarkSelectedItems method
     * @tc.expected: The result is false
     */
    scrollOn->GetHost();
    scrollOn->parent_ = mockOn;
    scrollOn->mousePressed_ = true;
    scrollOn->SetAxis(Axis::HORIZONTAL);
    Offset localLocation;
    localLocation.SetX(-1.1f);
    scrollOn->lastMouseMove_.SetLocalLocation(localLocation);
    EXPECT_EQ(scrollOn->lastMouseMove_.GetLocalLocation().GetX(), -1.1f);
    auto result = scrollOn->ShouldSelectScrollBeStopped();
    EXPECT_FALSE(result);

    /**
     * @tc.steps: step3. When selectMotion is not nullptr, call the MarkSelectedItems method
     * @tc.expected: The result is false
     */
    scrollOn->selectMotion_ = AceType::MakeRefPtr<SelectMotion>(0.0f, [this]() -> bool { return true; });
    result = scrollOn->ShouldSelectScrollBeStopped();
    EXPECT_FALSE(result);

    /**
     * @tc.steps: step4. When lastMouseMove is not nullptr, call the MarkSelectedItems method
     * @tc.expected: The result is true
     */
    scrollOn->SetAxis(Axis::VERTICAL);
    localLocation.SetY(0.0f);
    scrollOn->lastMouseMove_.SetLocalLocation(localLocation);
    EXPECT_EQ(scrollOn->lastMouseMove_.GetLocalLocation().GetY(), 0.0f);
    result = scrollOn->ShouldSelectScrollBeStopped();
    EXPECT_TRUE(result);
}

/**
 * @tc.name: ShouldSelectScrollBeStopped002
 * @tc.desc: Test nested ShouldSelectScrollBeStopped
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, ShouldSelectScrollBeStopped002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize ScrollablePattern type pointer and call ShouldSelectScrollBeStopped
     * @tc.expected: Pointer is not nullptr and result is true
     */
    auto scrollOn = scroll_->GetPattern<PartiallyMockedScrollable>();
    auto mockOn = mockScroll_->GetPattern<MockNestableScrollContainer>();
    scrollOn->parent_ = mockOn;
    auto result = scrollOn->ShouldSelectScrollBeStopped();
    EXPECT_TRUE(result);
}

/**
 * @tc.name: ShouldSelectScrollBeStopped003
 * @tc.desc: Test nested ShouldSelectScrollBeStopped
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, ShouldSelectScrollBeStopped003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize ScrollablePattern type pointer
     * @tc.expected: Pointer is not nullptr.
     */
    auto mockOn = AceType::MakeRefPtr<FullyMockedScrollable>();
    mockScroll_->pattern_ = mockOn;
    auto scrollOn = scroll_->GetPattern<PartiallyMockedScrollable>();
    scrollOn->parent_ = mockOn;

    /**
     * @tc.steps: step2. Call the ShouldSelectScrollBeStopped method
     * @tc.expected: The result is false
     */
    scrollOn->mousePressed_ = true;
    scrollOn->SetAxis(Axis::VERTICAL);
    Offset localLocation;
    localLocation.SetY(1.0f);
    scrollOn->lastMouseMove_.SetLocalLocation(localLocation);
    EXPECT_EQ(scrollOn->lastMouseMove_.GetLocalLocation().GetY(), 1.0f);
    auto result = scrollOn->ShouldSelectScrollBeStopped();
    EXPECT_FALSE(result);
}

/**
 * @tc.name: GetOffsetWithLimit001
 * @tc.desc: Test nested GetOffsetWithLimit
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, GetOffsetWithLimit001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize ScrollablePattern type pointer
     * @tc.expected: Pointer is not nullptr.
     */
    auto scrollOn = scroll_->GetPattern<PartiallyMockedScrollable>();
    auto mockOn = mockScroll_->GetPattern<MockNestableScrollContainer>();
    scrollOn->parent_ = mockOn;

    /**
     * @tc.steps: step2. Call the GetOffsetWithLimit method
     * @tc.expected: The result is 0.2
     */
    float offset = 0.2f;
    auto result = scrollOn->GetOffsetWithLimit(offset);
    EXPECT_NE(result, offset);
}

/**
 * @tc.name: GetOffsetWithLimit002
 * @tc.desc: Test nested GetOffsetWithLimit
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, GetOffsetWithLimit002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize ScrollablePattern type pointer
     * @tc.expected: Pointer is not nullptr.
     */
    auto scrollOn = scroll_->GetPattern<PartiallyMockedScrollable>();
    auto mockOn = mockScroll_->GetPattern<MockNestableScrollContainer>();
    scrollOn->parent_ = mockOn;

    /**
     * @tc.steps: step2. Call the GetOffsetWithLimit method
     * @tc.expected: The result is 0.0
     */
    float offset = -0.1f;
    auto result = scrollOn->GetOffsetWithLimit(offset);
    EXPECT_EQ(result, 0.0f);
}

/**
 * @tc.name: GetOffsetWithLimit003
 * @tc.desc: Test nested GetOffsetWithLimit
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, GetOffsetWithLimit003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize ScrollablePattern type pointer
     * @tc.expected: Pointer is not nullptr.
     */
    auto scrollOn = scroll_->GetPattern<PartiallyMockedScrollable>();
    auto mockOn = mockScroll_->GetPattern<MockNestableScrollContainer>();
    scrollOn->parent_ = mockOn;

    /**
     * @tc.steps: step2. Call the GetOffsetWithLimit method
     * @tc.expected: The result is 0.0
     */
    float offset = 0.0f;
    auto result = scrollOn->GetOffsetWithLimit(offset);
    EXPECT_EQ(result, offset);
}

/**
 * @tc.name: OnScrollStop001
 * @tc.desc: Test nested OnScrollStop
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, OnScrollStop001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize ScrollablePattern type pointer
     * @tc.expected: Pointer is not nullptr.
     */
    auto scrollOn = scroll_->GetPattern<PartiallyMockedScrollable>();
    auto mockOn = mockScroll_->GetPattern<MockNestableScrollContainer>();
    scrollOn->parent_ = mockOn;

    /**
     * @tc.steps: step2. Call the OnScrollStop method
     * @tc.expected: The scrollStop is false
     */
    scrollOn->scrollStop_ = true;
    scrollOn->SetScrollAbort(true);
    bool isStopTrigger = false;
    OnScrollStopEvent stopEvent = [&isStopTrigger]() { isStopTrigger = true; };
    scrollOn->OnScrollStop(stopEvent, nullptr);
    EXPECT_FALSE(scrollOn->scrollStop_);
}

/**
 * @tc.name: HandleHotZone001
 * @tc.desc: Test nested HandleHotZone
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, HandleHotZone001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize ScrollablePattern type pointer
     * @tc.expected: Pointer is not nullptr.
     */
    auto scrollOn = scroll_->GetPattern<PartiallyMockedScrollable>();
    auto mockOn = mockScroll_->GetPattern<MockNestableScrollContainer>();
    scrollOn->parent_ = mockOn;

    /**
     * @tc.steps: step2. Call the HandleHotZone method
     * @tc.expected: The scrollable is false
     */
    const RefPtr<NotifyDragEvent> notifyDragEvent = AceType::MakeRefPtr<NotifyDragEvent>();
    notifyDragEvent->SetX(0.1f);
    EXPECT_EQ(notifyDragEvent->GetX(), 0.1f);
    notifyDragEvent->SetY(0.2f);
    EXPECT_EQ(notifyDragEvent->GetY(), 0.2f);
    int32_t minPlatformVersion = 11;
    PipelineBase::GetCurrentContext()->SetMinPlatformVersion(minPlatformVersion);
    scrollOn->HandleHotZone(DragEventType::ENTER, notifyDragEvent);
    scrollOn->HandleHotZone(DragEventType::LEAVE, notifyDragEvent);
    EXPECT_FALSE(scrollOn->IsScrollable());
}

/**
 * @tc.name: HandleHotZone002
 * @tc.desc: Test nested HandleHotZone
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, HandleHotZone002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize ScrollablePattern type pointer
     * @tc.expected: Pointer is not nullptr.
     */
    auto scrollOn = scroll_->GetPattern<PartiallyMockedScrollable>();
    auto mockOn = mockScroll_->GetPattern<MockNestableScrollContainer>();
    scrollOn->parent_ = mockOn;

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
    scrollOn->HandleHotZone(DragEventType::MOVE, notifyDragEvent);
    EXPECT_FALSE(scrollOn->IsScrollable());
}

/**
 * @tc.name: HandleHotZone003
 * @tc.desc: Test nested HandleHotZone
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, HandleHotZone003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize ScrollablePattern type pointer
     * @tc.expected: Pointer is not nullptr.
     */
    auto scrollOn = scroll_->GetPattern<PartiallyMockedScrollable>();
    auto mockOn = mockScroll_->GetPattern<MockNestableScrollContainer>();
    scrollOn->parent_ = mockOn;

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
    scrollOn->HandleHotZone(DragEventType::START, notifyDragEvent);
    EXPECT_FALSE(scrollOn->IsScrollable());
}

/**
 * @tc.name: NeedCoordinateScrollWithNavigation001
 * @tc.desc: Test nested NeedCoordinateScrollWithNavigation
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, NeedCoordinateScrollWithNavigation001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize ScrollablePattern type pointer
     * @tc.expected: Pointer is not nullptr and result is false
     */
    auto scrollOn = scroll_->GetPattern<PartiallyMockedScrollable>();
    scrollOn->navBarPattern_ = nullptr;
    OverScrollOffset overScrollOffset = { 0.0f, 0.5f };
    bool result = scrollOn->NeedCoordinateScrollWithNavigation(0.0f, SCROLL_FROM_ANIMATION_SPRING, overScrollOffset);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: NeedCoordinateScrollWithNavigation002
 * @tc.desc: Test nested NeedCoordinateScrollWithNavigation
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, NeedCoordinateScrollWithNavigation002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize ScrollablePattern type pointer
     * @tc.expected: Pointer is not nullptr.
     */
    auto scrollOn = scroll_->GetPattern<PartiallyMockedScrollable>();
    scrollOn->GetParentNavigation();

    /**
     * @tc.steps: step2. Call the NeedCoordinateScrollWithNavigation method
     * @tc.expected: The scrollable is false
     */
    scrollOn->navBarPattern_ = AceType::MakeRefPtr<NavBarPattern>();
    OverScrollOffset overScrollOffset = { 0.0f, 0.5f };
    bool result = scrollOn->NeedCoordinateScrollWithNavigation(0.0f, SCROLL_FROM_ANIMATION_SPRING, overScrollOffset);
    EXPECT_FALSE(result);

    /**
     * @tc.steps: step3. Call the NeedCoordinateScrollWithNavigation method
     * @tc.expected: The scrollable is false
     */
    overScrollOffset = { 0.1f, 0.5f };
    result = scrollOn->NeedCoordinateScrollWithNavigation(0.0f, SCROLL_FROM_ANIMATION_SPRING, overScrollOffset);
    EXPECT_FALSE(result);

    /**
     * @tc.steps: step4. Call the NeedCoordinateScrollWithNavigation method
     * @tc.expected: The scrollable is false
     */
    scrollOn->SetAxis(Axis::VERTICAL);
    result = scrollOn->NeedCoordinateScrollWithNavigation(0.0f, SCROLL_FROM_ANIMATION_SPRING, overScrollOffset);
    EXPECT_FALSE(result);

    /**
     * @tc.steps: step5. Call the NeedCoordinateScrollWithNavigation method, set source is SCROLL_FROM_CHILD
     * @tc.expected: The scrollable is true
     */
    result = scrollOn->NeedCoordinateScrollWithNavigation(0.0f, SCROLL_FROM_CHILD, overScrollOffset);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: NotifyMoved001
 * @tc.desc: Test nested NotifyMoved failure status
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, NotifyMoved001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize ScrollablePattern type pointer
     * @tc.expected: Pointer is not nullptr.
     */
    auto mockOn = AceType::MakeRefPtr<FullyMockedScrollable>();
    mockScroll_->pattern_ = mockOn;
    auto scrollOn = scroll_->GetPattern<PartiallyMockedScrollable>();
    scrollOn->parent_ = mockOn;

    /**
     * @tc.steps: step2. Call the NotifyMoved method
     * @tc.expected: Scrollable is nullptr
     */
    scrollOn->scrollableEvent_ = AceType::MakeRefPtr<ScrollableEvent>(Axis::VERTICAL);
    scrollOn->NotifyMoved(false);
    EXPECT_FALSE(scrollOn->scrollableEvent_->GetScrollable());

    /**
     * @tc.steps: step3. Call the NotifyMoved method
     * @tc.expected: Scrollable is not nullptr
     */
    auto scrollable =
        AceType::MakeRefPtr<Scrollable>([](double, int32_t source) -> bool { return true; }, Axis::VERTICAL);
    scrollOn->scrollableEvent_->SetScrollable(scrollable);
    scrollOn->NotifyMoved(false);
    EXPECT_TRUE(scrollOn->scrollableEvent_->GetScrollable());
}

/**
 * @tc.name: NeedSplitScroll001
 * @tc.desc: Test nested NeedSplitScroll failure status
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, NeedSplitScroll001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize ScrollablePattern type pointer
     * @tc.expected: Pointer is not nullptr.
     */
    auto mockOn = AceType::MakeRefPtr<FullyMockedScrollable>();
    mockScroll_->pattern_ = mockOn;
    auto scrollOn = scroll_->GetPattern<PartiallyMockedScrollable>();
    scrollOn->parent_ = mockOn;

    /**
     * @tc.steps: step2. Call the NeedSplitScroll method
     * @tc.expected: return false
     */
    OverScrollOffset overScrollOffset = { 0.0f, 0.0f };
    EXPECT_FALSE(scrollOn->NeedSplitScroll(overScrollOffset, SCROLL_FROM_UPDATE));
    overScrollOffset = { 0.0f, 0.1f };
    EXPECT_FALSE(scrollOn->NeedSplitScroll(overScrollOffset, SCROLL_FROM_UPDATE));
    scrollOn->refreshCoordination_ = nullptr;
    EXPECT_FALSE(scrollOn->NeedSplitScroll(overScrollOffset, SCROLL_FROM_UPDATE));
    auto pattern = AceType::MakeRefPtr<Pattern>();
    auto scrollableNode = AceType::MakeRefPtr<FrameNode>("tag", 0, pattern);
    scrollOn->refreshCoordination_ = AceType::MakeRefPtr<RefreshCoordination>(scrollableNode);
    EXPECT_FALSE(scrollOn->NeedSplitScroll(overScrollOffset, SCROLL_FROM_UPDATE));
}

/**
 * @tc.name: Fling001
 * @tc.desc: Test nested Fling
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, Fling001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize ScrollablePattern type pointer
     * @tc.expected: Pointer is not nullptr
     */
    auto scrollOn = scroll_->GetPattern<PartiallyMockedScrollable>();

    /**
     * @tc.steps: step2. Call the Fling method and the flingVelocity is 3000
     * @tc.expected: The values of finalPosition_ and finalPosition are the same
     */
    float correctVelocity = 3000.0f;
    float friction = 0.6f;
    float frictionScale = -4.2f;
    float finalPosition = correctVelocity / (friction * -frictionScale);
    auto scrollableEvent = scrollOn->GetScrollableEvent();
    auto scrollable = scrollableEvent->GetScrollable();
    scrollable->SetUnstaticFriction(friction);
    scrollOn->Fling(correctVelocity);
    float finalPosition_ = scrollable->finalPosition_;
    EXPECT_EQ(finalPosition_, finalPosition);
}

/**
 * @tc.name: FadingEdge001
 * @tc.desc: Test SetFadingEdge
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, FadingEdge001, TestSize.Level1)
{
    /**
     * @tc.cases: SetFadingEdge false
     * @tc.expected: FadingEdge false
     */
    auto scrollOn = scroll_->GetPattern<PartiallyMockedScrollable>();
    auto paintProperty = scrollOn->GetPaintProperty<ScrollablePaintProperty>();
    NG::ScrollableModelNG::SetFadingEdge(Referenced::RawPtr(scroll_), false);
    EXPECT_FALSE(paintProperty->GetFadingEdge().value_or(false));
    /**
     * @tc.cases: SetFadingEdge true and SetFadingEdgeLength
     * @tc.expected: FadingEdge true and FadingEdgeLength is the same as SetFadingEdgeLength
     */
    NG::ScrollableModelNG::SetFadingEdge(Referenced::RawPtr(scroll_), true);
    EXPECT_TRUE(paintProperty->GetFadingEdge().value_or(false));
    EXPECT_EQ(paintProperty->GetFadingEdgeLength().value(), Dimension(32.0f, DimensionUnit::VP)); // default value;
    NG::ScrollableModelNG::SetFadingEdge(Referenced::RawPtr(scroll_), true, Dimension(50.0f, DimensionUnit::PERCENT));
    EXPECT_TRUE(paintProperty->GetFadingEdge().value_or(false));
    EXPECT_EQ(paintProperty->GetFadingEdgeLength().value(), Dimension(50.0f, DimensionUnit::PERCENT));
}

/**
 * @tc.name: HandleClickScroll001
 * @tc.desc: Test scrolling when clicking on the scroll bar
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, HandleClickScroll001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create FullyMockedScrollable, PartiallyMockedScrollable and GestureEvent.
     * @tc.expected: create FullyMockedScrollable, PartiallyMockedScrollable and GestureEvent created successfully.
     */
    auto mockOn = AceType::MakeRefPtr<FullyMockedScrollable>();
    mockScroll_->pattern_ = mockOn;
    auto scrollOn = scroll_->GetPattern<PartiallyMockedScrollable>();
    scrollOn->scrollableEvent_ = AceType::MakeRefPtr<ScrollableEvent>(Axis::VERTICAL);
    scrollOn->parent_ = mockOn;
    scrollOn->scrollBar_ = AceType::MakeRefPtr<ScrollBar>();
    scrollOn->scrollBar_->barRect_ = Rect(0.0f, 0.0f, 30.0f, 500.0f);
    scrollOn->scrollBar_->touchRegion_ = Rect(0.0f, 100.0f, 30.0f, 100.0f);
    scrollOn->isMousePressed_ = true;
    scrollOn->scrollBar_->isScrollable_ = true;
    scrollOn->locationInfo_ = Offset(1.0f, 150.0f);
    // /**
    //  * @tc.steps: step2. Test HandleClickEvent.
    //  * @tc.expect: finalPosition_ equal to expect value.
    //  */
    EXPECT_CALL(*scrollOn, GetMainContentSize).Times(2).WillRepeatedly(Return(50.0f));
    scrollOn->InitScrollBarClickEvent();
    scrollOn->HandleClickEvent();
    EXPECT_EQ(scrollOn->finalPosition_, 0.0f);

    scrollOn->locationInfo_ = Offset(15.0f, 1.0f);
    scrollOn->scrollBar_->touchRegion_ = Rect(0.0f, 100.0f, 30.0f, 100.0f);
    scrollOn->HandleClickEvent();
    EXPECT_EQ(scrollOn->finalPosition_, -50.0f);

    scrollOn->locationInfo_ = Offset(15.0f, 350.0f);
    scrollOn->scrollBar_->touchRegion_ = Rect(0.0f, 100.0f, 30.0f, 100.0f);
    scrollOn->HandleClickEvent();
    EXPECT_EQ(scrollOn->finalPosition_, 50.0f);
}

/**
 * @tc.name: HandleLongPressScroll001
 * @tc.desc: Test long press and hold scrolling when clicking on the scroll bar
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, HandleLongPressScroll001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create FullyMockedScrollable, PartiallyMockedScrollable and ScrollBar.
     * @tc.expected: create FullyMockedScrollable, PartiallyMockedScrollable and ScrollBar created successfully.
     */
    auto mockOn = AceType::MakeRefPtr<FullyMockedScrollable>();
    mockScroll_->pattern_ = mockOn;
    auto scrollOn = scroll_->GetPattern<PartiallyMockedScrollable>();
    scrollOn->scrollableEvent_ = AceType::MakeRefPtr<ScrollableEvent>(Axis::VERTICAL);
    scrollOn->parent_ = mockOn;
    scrollOn->scrollBar_ = AceType::MakeRefPtr<ScrollBar>();
    scrollOn->scrollBar_->barRect_ = Rect(0.0f, 0.0f, 30.0f, 500.0f);
    scrollOn->scrollBar_->touchRegion_ = Rect(0.0f, 100.0f, 30.0f, 100.0f);
    scrollOn->scrollBar_->InitLongPressEvent();
    scrollOn->isMousePressed_ = true;
    scrollOn->scrollBar_->isScrollable_ = true;
    /**
    * @tc.steps: step2. Test HandleClickEvent.
    * @tc.expect: CheckBarDirection equal to equal BarDirection's Value.
    */
    scrollOn->scrollBar_->locationInfo_ = Offset(1.0f, 110.0f);
    scrollOn->scrollBar_->HandleLongPress(true);
    Point point(scrollOn->scrollBar_->locationInfo_.GetX(), scrollOn->scrollBar_->locationInfo_.GetY());
    scrollOn->scrollBar_->CheckBarDirection(point);
    EXPECT_EQ(scrollOn->scrollBar_->CheckBarDirection(point), BarDirection::BAR_NONE);
    scrollOn->scrollBar_->locationInfo_ = Offset(1.0f, 1.0f);
    scrollOn->scrollBar_->touchRegion_ = Rect(0.0f, 100.0f, 30.0f, 100.0f);
    scrollOn->scrollBar_->HandleLongPress(true);
    Point point1(scrollOn->scrollBar_->locationInfo_.GetX(), scrollOn->scrollBar_->locationInfo_.GetY());
    EXPECT_EQ(scrollOn->scrollBar_->CheckBarDirection(point1), BarDirection::PAGE_UP);
    scrollOn->scrollBar_->locationInfo_ = Offset(1.0f, 300.0f);
    scrollOn->scrollBar_->touchRegion_ = Rect(0.0f, 100.0f, 30.0f, 100.0f);
    scrollOn->scrollBar_->HandleLongPress(true);
    Point point2(scrollOn->scrollBar_->locationInfo_.GetX(), scrollOn->scrollBar_->locationInfo_.GetY());
    EXPECT_EQ(scrollOn->scrollBar_->CheckBarDirection(point2), BarDirection::PAGE_DOWN);
}

/**
 * @tc.name: InitMouseEvent001
 * @tc.desc: Test mouse event callback
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, InitMouseEvent001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create FullyMockedScrollable, PartiallyMockedScrollable and MouseInfo.
     * @tc.expected: create CreateScrollBar and MouseInfo created successfully.
     */
    auto mockOn = AceType::MakeRefPtr<FullyMockedScrollable>();
    mockScroll_->pattern_ = mockOn;
    auto scrollOn = scroll_->GetPattern<PartiallyMockedScrollable>();
    scrollOn->scrollBar_ = AceType::MakeRefPtr<ScrollBar>();
    scrollOn->parent_ = mockOn;
    scrollOn->InitScrollBarMouseEvent();
    // /**
    //  * @tc.steps: step2. Test HandleMouseEvent.
    //  * @tc.expect: info's GetButton is LEFT_BUTTON.
    //  */
    MouseInfo info;
    info.SetAction(MouseAction::PRESS);
    info.SetButton(MouseButton::LEFT_BUTTON);
    auto& inputEvents = scrollOn->GetEventHub<EventHub>()
        ->GetOrCreateInputEventHub()->mouseEventActuator_->inputEvents_;
    EXPECT_EQ(inputEvents.size(), 1);
    for (const auto& callback : inputEvents) {
        if (callback) {
            (*callback)(info);
        }
    };
    EXPECT_TRUE(scrollOn->isMousePressed_);
    MouseInfo info1;
    info1.SetAction(MouseAction::RELEASE);
    info1.SetButton(MouseButton::LEFT_BUTTON);
    for (const auto& callback : inputEvents) {
        if (callback) {
            (*callback)(info1);
        }
    };
    EXPECT_FALSE(scrollOn->isMousePressed_);
}

/**
 * @tc.name: InitMouseEvent002
 * @tc.desc: Test multiSelectable event and mouse scroll event
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, InitMouseEvent002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create FullyMockedScrollable, PartiallyMockedScrollable.
     * @tc.expected: create PartiallyMockedScrollable successfully.
     */
    auto mockOn = AceType::MakeRefPtr<FullyMockedScrollable>();
    mockScroll_->pattern_ = mockOn;
    ASSERT_NE(scroll_, nullptr);
    auto scrollOn = scroll_->GetPattern<PartiallyMockedScrollable>();
    ASSERT_NE(scrollOn, nullptr);
    auto gestureHub = scroll_->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureHub, nullptr);
    EXPECT_EQ(gestureHub->panEventActuator_, nullptr);

    /**
     * @tc.steps: step2. execute the InitMouseEbent.
     * @tc.expected: the isExcludedAxis_ of panEventActuator_ is true.
     */
    scrollOn->InitMouseEvent();
    gestureHub = scroll_->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureHub, nullptr);
    ASSERT_NE(gestureHub->panEventActuator_, nullptr);
    EXPECT_TRUE(gestureHub->panEventActuator_->isExcludedAxis_);
}

/**
 * @tc.name: SetEdgeEffect001
 * @tc.desc: Test SetEdgeEffect
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, SetEdgeEffect001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize ScrollablePattern type pointer and set EdgeEffect to Spring.
     * @tc.expected: spring animation is running.
     */
    auto scrollOn = scroll_->GetPattern<PartiallyMockedScrollable>();
    scrollOn->SetEdgeEffect(EdgeEffect::SPRING);
    auto scrollableEvent = scrollOn->GetScrollableEvent();
    auto scrollable = scrollableEvent->GetScrollable();
    scrollable->state_ = Scrollable::AnimationState::SPRING;
    EXPECT_TRUE(scrollable->IsSpringMotionRunning());

    /**
     * @tc.steps: step2. set EdgeEffect to Spring.
     * @tc.expected: spring animation is running.
     */
    scrollOn->SetEdgeEffect(EdgeEffect::SPRING);
    EXPECT_TRUE(scrollable->IsSpringMotionRunning());

    /**
     * @tc.steps: step3. set EdgeEffect to None.
     * @tc.expected: spring animation is stopped.
     */
    scrollOn->SetEdgeEffect(EdgeEffect::NONE);
    EXPECT_FALSE(scrollable->IsSpringMotionRunning());
}

#ifdef SUPPORT_DIGITAL_CROWN
/**
 * @tc.name: ListenDigitalCrownEvent001
 * @tc.desc: Test ListenDigitalCrownEvent
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, ListenDigitalCrownEvent001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize ScrollablePattern type pointer and Scrollable.
     * @tc.expected: Pointer is not nullptr.
     */
    auto scrollOn = scroll_->GetPattern<PartiallyMockedScrollable>();
    ASSERT_NE(scrollOn, nullptr);
    ASSERT_NE(scrollOn->scrollableEvent_, nullptr);
    auto scrollable = scrollOn->scrollableEvent_->GetScrollable();
    ASSERT_NE(scrollable, nullptr);

    scrollable->ListenDigitalCrownEvent(nullptr);
    scrollable->ListenDigitalCrownEvent(scrollable->weakHost_.Upgrade());
    EXPECT_NE(scrollable->weakHost_.Upgrade(), nullptr);
}

/**
 * @tc.name: GetCrownRotatePx001
 * @tc.desc: Test GetCrownRotatePx
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, GetCrownRotatePx001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize ScrollablePattern type pointer and Scrollable.
     * @tc.expected: Pointer is not nullptr.
     */
    auto scrollOn = scroll_->GetPattern<PartiallyMockedScrollable>();
    ASSERT_NE(scrollOn, nullptr);
    ASSERT_NE(scrollOn->scrollableEvent_, nullptr);
    auto scrollable = scrollOn->scrollableEvent_->GetScrollable();
    ASSERT_NE(scrollable, nullptr);

    CrownEvent event = {};
    event.degree = 1.f;

    /**
     * @tc.steps: step2. Very slow rotation speed test.
     * @tc.expected: Rotating pixel points with specific row values.
     */
    event.angularVelocity = TEST_ANGULAR_VELOCITY_SLOW;
    scrollable->SetDigitalCrownSensitivity(CrownSensitivity::LOW);
    double resPx = scrollable->GetCrownRotatePx(event);
    double px = Dimension(TEST_DISPLAY_CONTROL_RATIO_VERY_SLOW, DimensionUnit::VP).ConvertToPx();
    EXPECT_EQ(resPx, px*TEST_CROWN_SENSITIVITY_LOW);

    /**
     * @tc.steps: step3. Medium rotation speed test.
     * @tc.expected: Rotating pixel points with specific row values.
     */
    event.angularVelocity = TEST_ANGULAR_VELOCITY_MEDIUM;
    scrollable->SetDigitalCrownSensitivity(CrownSensitivity::MEDIUM);
    resPx = scrollable->GetCrownRotatePx(event);
    px = Dimension(TEST_DISPLAY_CONTROL_RATIO_SLOW, DimensionUnit::VP).ConvertToPx();
    EXPECT_EQ(resPx, px*TEST_CROWN_SENSITIVITY_MEDIUM);

    /**
     * @tc.steps: step4. Fast rotation speed test.
     * @tc.expected: Rotating pixel points with specific row values.
     */
    event.angularVelocity = TEST_ANGULAR_VELOCITY_FAST;
    scrollable->SetDigitalCrownSensitivity(CrownSensitivity::HIGH);
    resPx = scrollable->GetCrownRotatePx(event);
    px = Dimension(TEST_DISPLAY_CONTROL_RATIO_MEDIUM, DimensionUnit::VP).ConvertToPx();
    EXPECT_EQ(resPx, px*TEST_CROWN_SENSITIVITY_HIGH);

    /**
     * @tc.steps: step5. Other rotation speed test.
     * @tc.expected: Rotating pixel points with specific row values.
     */
    event.angularVelocity = TEST_ANGULAR_VELOCITY_VERY_FAST;
    scrollable->SetDigitalCrownSensitivity((CrownSensitivity)-1);
    resPx = scrollable->GetCrownRotatePx(event);
    px = Dimension(TEST_DISPLAY_CONTROL_RATIO_FAST, DimensionUnit::VP).ConvertToPx();
    EXPECT_EQ(resPx, TEST_DISPLAY_CONTROL_RATIO_FAST);
}

/**
 * @tc.name: UpdateCrownVelocity001
 * @tc.desc: Test UpdateCrownVelocity
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, UpdateCrownVelocity001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize ScrollablePattern type pointer and Scrollable.
     * @tc.expected: Pointer is not nullptr.
     */
    auto scrollOn = scroll_->GetPattern<PartiallyMockedScrollable>();
    ASSERT_NE(scrollOn, nullptr);
    ASSERT_NE(scrollOn->scrollableEvent_, nullptr);
    auto scrollable = scrollOn->scrollableEvent_->GetScrollable();
    ASSERT_NE(scrollable, nullptr);

    TimeStamp ts = std::chrono::high_resolution_clock::now();

    /**
     * @tc.steps: step2. vertical axis test.
     * @tc.expected: Return the correct value after successful setting.
     */
    scrollable->SetAxis(Axis::VERTICAL);
    auto accumulativeCrownPx = scrollable->accumulativeCrownPx_;
    scrollable->UpdateCrownVelocity(ts, TEST_CROWN_VELOCITY, false);
    EXPECT_EQ(scrollable->accumulativeCrownPx_, accumulativeCrownPx+Offset(0, TEST_CROWN_VELOCITY));

    /**
     * @tc.steps: step3. horizontal axis test.
     * @tc.expected: Return the correct value after successful setting.
     */
    scrollable->SetAxis(Axis::HORIZONTAL);
    accumulativeCrownPx = scrollable->accumulativeCrownPx_;
    scrollable->UpdateCrownVelocity(ts, TEST_CROWN_VELOCITY, true);
    EXPECT_EQ(scrollable->accumulativeCrownPx_, accumulativeCrownPx+Offset(TEST_CROWN_VELOCITY, 0));
}

/**
 * @tc.name: HandleCrownEvent001
 * @tc.desc: Test HandleCrownEvent
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, HandleCrownEvent001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize ScrollablePattern type pointer and Scrollable.
     * @tc.expected: Pointer is not nullptr.
     */
    auto scrollOn = scroll_->GetPattern<PartiallyMockedScrollable>();
    ASSERT_NE(scrollOn, nullptr);
    ASSERT_NE(scrollOn->scrollableEvent_, nullptr);
    auto scrollable = scrollOn->scrollableEvent_->GetScrollable();
    ASSERT_NE(scrollable, nullptr);

    /**
     * @tc.steps: step2. Initialize test parameters.
     * @tc.expected: Parameter setting successful.
     */
    CrownEvent event = {};
    event.timeStamp = std::chrono::high_resolution_clock::now();
    event.degree = 1.f;
    event.angularVelocity = TEST_ANGULAR_VELOCITY_SLOW;
    scrollable->SetDigitalCrownSensitivity(CrownSensitivity::LOW);
    double px = Dimension(TEST_DISPLAY_CONTROL_RATIO_VERY_SLOW, DimensionUnit::VP).ConvertToPx();
    px *= TEST_CROWN_SENSITIVITY_LOW;
    OffsetF oft = OffsetF(100.f, 100.f);
    auto fun = [oft](const GestureEvent& info) {
        EXPECT_EQ(oft.GetX(), 100.f);
    };
    scrollable->AddPanActionEndEvent(std::move(fun));

    /**
     * @tc.steps: step3. Begin action test.
     * @tc.expected: Rotating pixel points with specific row values.
     */
    bool dragging = scrollable->GetCrownEventDragging();
    if (dragging) {
        scrollable->SetCrownEventDragging(false);
    }
    event.action = CrownAction::BEGIN;
    scrollable->crownEventNum_ = TEST_CROWN_EVENT_NUN_THRESH;
    scrollable->HandleCrownEvent(event, oft);
    EXPECT_TRUE(scrollable->GetIsDragging());

    /**
     * @tc.steps: step4. Begin action test.
     * @tc.expected: Rotating pixel points with specific row values.
     */
    event.action = CrownAction::BEGIN;
    scrollable->HandleCrownEvent(event, oft);
    EXPECT_TRUE(scrollable->GetIsDragging());

    /**
     * @tc.steps: step5. Update action test.
     * @tc.expected: Rotating pixel points with specific row values.
     */
    auto accumulativeCrownPx = scrollable->accumulativeCrownPx_;
    event.action = CrownAction::UPDATE;
    scrollable->SetAxis(Axis::VERTICAL);
    scrollable->SetCrownEventDragging(!scrollable->GetCrownEventDragging());
    scrollable->HandleCrownEvent(event, oft);
    EXPECT_EQ(scrollable->accumulativeCrownPx_, accumulativeCrownPx+Offset(0, px));

    /**
     * @tc.steps: step6. Unknown action test 01.
     * @tc.expected: Rotating pixel points is 0.
     */
    event.action = CrownAction::UNKNOWN;
    accumulativeCrownPx = scrollable->accumulativeCrownPx_;
    scrollable->HandleCrownEvent(event, oft);
    EXPECT_EQ(scrollable->accumulativeCrownPx_, accumulativeCrownPx);
}

/**
 * @tc.name: HandleCrownEvent002
 * @tc.desc: Test HandleCrownEvent
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, HandleCrownEvent002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize ScrollablePattern type pointer and Scrollable.
     * @tc.expected: Pointer is not nullptr.
     */
    auto scrollOn = scroll_->GetPattern<PartiallyMockedScrollable>();
    ASSERT_NE(scrollOn, nullptr);
    ASSERT_NE(scrollOn->scrollableEvent_, nullptr);
    auto scrollable = scrollOn->scrollableEvent_->GetScrollable();
    ASSERT_NE(scrollable, nullptr);

    /**
     * @tc.steps: step2. Initialize test parameters.
     * @tc.expected: Parameter setting successful.
     */
    CrownEvent event = {};
    event.timeStamp = std::chrono::high_resolution_clock::now();
    event.degree = 1.f;
    event.angularVelocity = TEST_ANGULAR_VELOCITY_SLOW;
    scrollable->SetDigitalCrownSensitivity(CrownSensitivity::LOW);
    double px = Dimension(TEST_DISPLAY_CONTROL_RATIO_VERY_SLOW, DimensionUnit::VP).ConvertToPx();
    px *= TEST_CROWN_SENSITIVITY_LOW;
    OffsetF oft = OffsetF(100.f, 100.f);
    auto fun = [oft](const GestureEvent& info) {
        EXPECT_EQ(oft.GetX(), 100.f);
    };
    scrollable->AddPanActionEndEvent(std::move(fun));

    /**
     * @tc.steps: step3. End action test 01.
     * @tc.expected: isDragging change to false.
     */
    event.action = CrownAction::END;
    scrollable->HandleCrownEvent(event, oft);
    EXPECT_FALSE(scrollable->GetIsDragging());

    /**
     * @tc.steps: step4. End action test 02.
     * @tc.expected: isDragging change to false.
     */
    auto accumulativeCrownPx = scrollable->accumulativeCrownPx_;
    event.angularVelocity = 0.f;
    event.degree = 0.f;
    scrollable->SetAxis(Axis::HORIZONTAL);
    scrollable->HandleCrownEvent(event, oft);
    EXPECT_EQ(scrollable->accumulativeCrownPx_, accumulativeCrownPx);

    /**
     * @tc.steps: step5. Unknown action test 02.
     * @tc.expected: Rotating pixel points is 0.
     */
    event.action = CrownAction::UNKNOWN;
    accumulativeCrownPx = scrollable->accumulativeCrownPx_;
    scrollable->SetDragCancelCallback(nullptr);
    scrollable->HandleCrownEvent(event, oft);
    EXPECT_EQ(scrollable->accumulativeCrownPx_, accumulativeCrownPx);

    /**
     * @tc.steps: step6. Unknown action test 03.
     * @tc.expected: Rotating pixel points is 0.
     */
    event.action = CrownAction::UNKNOWN;
    scrollable->SetDragCancelCallback([&]() {
        EXPECT_EQ(event.degree, 0.f);
    });
    accumulativeCrownPx = scrollable->accumulativeCrownPx_;
    scrollable->panRecognizerNG_ = nullptr;
    scrollable->HandleCrownEvent(event, oft);
    scrollable->panRecognizerNG_ = nullptr;
    scrollable->SetAxis(Axis::NONE);
    EXPECT_EQ(scrollable->accumulativeCrownPx_, accumulativeCrownPx);
}

/**
 * @tc.name: SetVelocityScale001
 * @tc.desc: Test SetVelocityScale
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, SetVelocityScale001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize ScrollablePattern type pointer and Scrollable.
     * @tc.expected: Pointer is not nullptr.
     */
    auto scrollOn = scroll_->GetPattern<PartiallyMockedScrollable>();
    ASSERT_NE(scrollOn, nullptr);
    ASSERT_NE(scrollOn->scrollableEvent_, nullptr);
    auto scrollable = scrollOn->scrollableEvent_->GetScrollable();
    ASSERT_NE(scrollable, nullptr);

    scrollOn->SetVelocityScale(0);
    EXPECT_EQ(scrollOn->velocityScale_, 1);

    scrollOn->scrollableEvent_ = nullptr;
    scrollOn->SetVelocityScale(1);
    EXPECT_EQ(scrollOn->velocityScale_, 1);
}

/**
 * @tc.name: OnTouchDown001
 * @tc.desc: Test OnTouchDown
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, OnTouchDown001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize ScrollablePattern type pointer and Scrollable.
     * @tc.expected: Pointer is not nullptr.
     */
    auto scrollOn = scroll_->GetPattern<PartiallyMockedScrollable>();
    ASSERT_NE(scrollOn, nullptr);

    /**
     * @tc.steps: step2. ScrollablePattern OnTouchDown
     * @tc.expected: Click animation stop
     */
    TouchEventInfo touchEvent = TouchEventInfo("unknown");
    scrollOn->nestedScrollVelocity_ = 0;
    scrollOn->OnTouchDown(touchEvent);
    EXPECT_FALSE(scrollOn->isAnimationStop_);
}
#endif
} // namespace OHOS::Ace::NG
