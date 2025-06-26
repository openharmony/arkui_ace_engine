/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
#include "test/mock/core/animation/mock_animation_manager.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#define protected public
#define private public
#include "test/unittest/core/pattern/scrollable/mock_scrollable.h"

#include "core/components/scroll/scroll_bar_theme.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/grid/grid_paint_method.h"
#include "core/components_ng/pattern/overlay/sheet_drag_bar_pattern.h"
#include "core/components_ng/pattern/refresh/refresh_pattern.h"
#include "core/components_ng/pattern/root/root_pattern.h"
#include "core/components_ng/pattern/scroll/scroll_pattern.h"
#include "core/components_ng/pattern/scrollable/scrollable_item.h"
#include "core/components_ng/pattern/scrollable/scrollable_item_pool.h"
#include "core/components_ng/pattern/scrollable/scrollable_model_ng.h"
#include "core/components_ng/pattern/scrollable/scrollable_paint_property.h"
#include "core/components_ng/pattern/text/text_pattern.h"

namespace OHOS::Ace::NG {
class ScrollableCoverTestNg : public ScrollableTestNg {
public:
    void SetUp() override;
    void TearDown() override;
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    static void SetUpMockThemeManager();
};

constexpr char BAR_STATE_AUTO[] = "BarState.Auto";
constexpr char BAR_STATE_ON[] = "BarState.On";
constexpr char BAR_STATE_OFF[] = "BarState.Off";
constexpr const char* SCROLLBAR_WIDTH_PX = "5.00px";
constexpr const char* SCROLLBAR_WIDTH_VP = "15.0vp";
constexpr const char* SCROLLBAR_WIDTH_PERCENT = "100%";
constexpr char SCROLLBAR_COLOR_BLUE[] = "#FF0000FF";
constexpr char SCROLLBAR_COLOR_RED[] = "#FF0000";
constexpr double SCROLLBAR_WIDTH_VALUE_PX = 5.0;
constexpr double CAP_COEFFICIENT = 0.45;
constexpr double SCROLLBAR_WIDTH_VALUE_VP = 15.0;
constexpr double SCROLLBAR_WIDTH_VALUE_PERCENT = 1.0;
constexpr double SCROLLBARTHEME_WIDTH_VALUE_PX = 100.0;
constexpr float DEFAULT_THRESHOLD = 0.75f;
constexpr int32_t FIRST_THRESHOLD = 4;

void ScrollableCoverTestNg::SetUpTestSuite()
{
    TestNG::SetUpTestSuite();
}

void ScrollableCoverTestNg::TearDownTestSuite()
{
    TestNG::TearDownTestSuite();
}

void ScrollableCoverTestNg::SetUp()
{
    MockPipelineContext::SetUp();
    InitNestedScrolls();
    ScrollableCoverTestNg::SetUpMockThemeManager();
}

void ScrollableCoverTestNg::TearDown()
{
    scroll_.Reset();
    mockScroll_.Reset();
}

void ScrollableCoverTestNg::SetUpMockThemeManager()
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto themeConstants = CreateThemeConstants(THEME_PATTERN_SCROLL_BAR);
    auto scrollBarTheme = ScrollBarTheme::Builder().Build(themeConstants);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(scrollBarTheme));
    scrollBarTheme->normalWidth_ = Dimension(SCROLLBARTHEME_WIDTH_VALUE_PX, DimensionUnit::VP);
}

/**
 * @tc.name: SetScrollBarModeTest001
 * @tc.desc: Test GetBarStateString and SetScrollBarMode method
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableCoverTestNg, SetScrollBarModeTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set ScrollBarMode to AUTO
     * @tc.expected: ScrollablePaintProperty ScrollBarMode is updated to AUTO
     */
    ScrollableModelNG::SetScrollBarMode(DisplayMode::AUTO);
    auto scrollablePn = scroll_->GetPaintProperty<ScrollablePaintProperty>();
    EXPECT_EQ(scrollablePn->GetBarStateString(), BAR_STATE_AUTO);

    /**
     * @tc.steps: step2. Set ScrollBarMode to ON
     * @tc.expected: ScrollablePaintProperty ScrollBarMode is updated to ON
     */
    ScrollableModelNG::SetScrollBarMode(DisplayMode::ON);
    EXPECT_EQ(scrollablePn->GetBarStateString(), BAR_STATE_ON);

    /**
     * @tc.steps: step3. Set ScrollBarMode to OFF
     * @tc.expected: ScrollablePaintProperty ScrollBarMode is updated to OFF
     */
    ScrollableModelNG::SetScrollBarMode(DisplayMode::OFF);
    EXPECT_EQ(scrollablePn->GetBarStateString(), BAR_STATE_OFF);
}

/**
 * @tc.name: SetScrollBarWidthTest001
 * @tc.desc: Test SetScrollBarWidth and GetBarWidth method
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableCoverTestNg, SetScrollBarWidthTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set ScrollBarWidth to vp width
     * @tc.expected: ScrollablePaintProperty ScrollBarWidth is updated to vp width
     */
    ScrollableModelNG::SetScrollBarWidth(SCROLLBAR_WIDTH_VP);
    auto scrollablePn = scroll_->GetPaintProperty<ScrollablePaintProperty>();
    EXPECT_EQ(scrollablePn->GetBarWidth().Value(), SCROLLBAR_WIDTH_VALUE_VP);
    EXPECT_EQ(scrollablePn->GetBarWidth().Unit(), DimensionUnit::VP);

    /**
     * @tc.steps: step2. Set ScrollBarWidth to px width
     * @tc.expected: ScrollablePaintProperty ScrollBarWidth is updated to px width
     */
    ScrollableModelNG::SetScrollBarWidth(SCROLLBAR_WIDTH_PX);
    EXPECT_EQ(scrollablePn->GetBarWidth().Value(), SCROLLBAR_WIDTH_VALUE_PX);
    EXPECT_EQ(scrollablePn->GetBarWidth().Unit(), DimensionUnit::PX);

    /**
     * @tc.steps: step3. Set ScrollBarWidth to percent width
     * @tc.expected: ScrollablePaintProperty ScrollBarWidth is updated to percent width
     */
    ScrollableModelNG::SetScrollBarWidth(SCROLLBAR_WIDTH_PERCENT);
    EXPECT_EQ(scrollablePn->GetBarWidth().Value(), SCROLLBAR_WIDTH_VALUE_PERCENT);
    EXPECT_EQ(scrollablePn->GetBarWidth().Unit(), DimensionUnit::PERCENT);

    /**
     * @tc.steps: step4. Set ScrollBarWidth to vp width with frameNode
     * @tc.expected: ScrollablePaintProperty ScrollBarWidth is updated to vp width
     */
    ScrollableModelNG::SetScrollBarWidth(&(*scroll_), SCROLLBAR_WIDTH_VP);
    scrollablePn = scroll_->GetPaintProperty<ScrollablePaintProperty>();
    EXPECT_EQ(scrollablePn->GetBarWidth().Value(), SCROLLBAR_WIDTH_VALUE_VP);
    EXPECT_EQ(scrollablePn->GetBarWidth().Unit(), DimensionUnit::VP);
    /**
     * @tc.steps: step5. Set propScrollBarProperty_ nullptr in ScrollablePaintProperty and use defaultScrollBarWidth
     */
    scrollablePn = scroll_->GetPaintProperty<ScrollablePaintProperty>();
    auto themeManager = MockPipelineContext::GetCurrent()->GetThemeManager();
    auto scrollBarTheme = themeManager->GetTheme<ScrollBarTheme>();
    scrollablePn->propScrollBarProperty_ = nullptr;
    EXPECT_EQ(scrollablePn->GetBarWidth().Value(), scrollBarTheme->GetNormalWidth().Value());
    EXPECT_EQ(scrollablePn->GetBarWidth().Unit(), scrollBarTheme->GetNormalWidth().Unit());
}

/**
 * @tc.name: SetScrollBarColorTest001
 * @tc.desc: Test SetScrollBarColor and GetBarColor method
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableCoverTestNg, SetScrollBarColorTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set ScrollBarColor to blue
     * @tc.expected: ScrollablePaintProperty ScrollBarColor is updated to blue
     */
    ScrollableModelNG::SetScrollBarColor(SCROLLBAR_COLOR_BLUE);
    auto scrollablePn = scroll_->GetPaintProperty<ScrollablePaintProperty>();
    EXPECT_EQ(scrollablePn->GetBarColor(), Color::FromString(SCROLLBAR_COLOR_BLUE));

    /**
     * @tc.steps: step2. Set ScrollBarColor to red
     * @tc.expected: ScrollablePaintProperty ScrollBarColor is updated to red
     */
    ScrollableModelNG::SetScrollBarColor(SCROLLBAR_COLOR_RED);
    EXPECT_EQ(scrollablePn->GetBarColor(), Color::FromString(SCROLLBAR_COLOR_RED));

    /**
     * @tc.steps: step3. Set ScrollBarColor to blue with frameNode
     * @tc.expected: ScrollablePaintProperty ScrollBarColor is updated to blue
     */
    ScrollableModelNG::SetScrollBarColor(&(*scroll_), SCROLLBAR_COLOR_BLUE);
    scrollablePn = scroll_->GetPaintProperty<ScrollablePaintProperty>();
    EXPECT_EQ(scrollablePn->GetBarColor(), Color::FromString(SCROLLBAR_COLOR_BLUE));
    /**
     * @tc.steps: step4. Set propScrollBarProperty_ nullptr in ScrollablePaintProperty and use defaultScrollBarColor
     */
    scrollablePn = scroll_->GetPaintProperty<ScrollablePaintProperty>();
    auto themeManager = MockPipelineContext::GetCurrent()->GetThemeManager();
    auto scrollBarTheme = themeManager->GetTheme<ScrollBarTheme>();
    scrollablePn->propScrollBarProperty_ = nullptr;
    EXPECT_EQ(scrollablePn->GetBarColor(), scrollBarTheme->GetForegroundColor());
}

/**
 * @tc.name: ToJsonValueTest001
 * @tc.desc: Test ToJsonValue method of ScrollablePaintProperty
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableCoverTestNg, ToJsonValueTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a ScrollablePaintProperty object and set Property
     */
    ScrollableModelNG::SetScrollBarColor(SCROLLBAR_COLOR_BLUE);
    ScrollableModelNG::SetScrollBarWidth(SCROLLBAR_WIDTH_PX);
    auto scrollablePn = scroll_->GetPaintProperty<ScrollablePaintProperty>();

    /**
     * @tc.steps: step2. Set properties
     */
    scrollablePn->UpdateScrollBarMode(DisplayMode::AUTO);
    /**
     * @tc.steps: step3. Convert to JSON
     */
    auto json = JsonUtil::Create(true);
    InspectorFilter filter;
    scrollablePn->ToJsonValue(json, filter);

    /**
     * @tc.steps: step4. Convert to JSON
     */
    EXPECT_EQ(json->GetString("scrollBar"), BAR_STATE_AUTO);
    EXPECT_EQ(json->GetString("scrollBarColor"), SCROLLBAR_COLOR_BLUE);
    EXPECT_EQ(json->GetString("scrollBarWidth"), SCROLLBAR_WIDTH_PX);
    /**
     * @tc.steps: step5. call tojson when filter.IsFastFilter() true
     */
    filter.AddFilterAttr("id");
    scrollablePn->ToJsonValue(json, filter);
    EXPECT_TRUE(filter.IsFastFilter());
}

/**
 * @tc.name: AllocateTest001
 * @tc.desc: Test Allocate when tag is found and pool is not empty.
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableCoverTestNg, AllocateTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a ScrollableItem object and set ScrollableItemPool
     */
    auto patternCreator = []() -> RefPtr<Pattern> { return AceType::MakeRefPtr<Pattern>(); };
    auto tag = "testTag";
    auto nodeFirst = 1;
    auto nodeSecond = 2;
    auto size = 1;
    auto existingItem = ScrollableItem::GetOrCreateScrollableItem(tag, nodeFirst, patternCreator);
    auto scrollableItemPool = std::make_shared<ScrollableItemPool>(size);
    scrollableItemPool->pool_[tag].push_back(Referenced::RawPtr(existingItem));
    /**
     * @tc.steps: step2. Call Allocate
     */
    auto result = scrollableItemPool->Allocate(tag, nodeSecond, patternCreator);
    /**
     * @tc.steps: step3. Verify that the Allocate function was triggered
     */
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->GetTag(), tag);
    EXPECT_EQ(result->GetId(), nodeSecond);
}

/**
 * @tc.name: DeallocateTest001
 * @tc.desc: Test Deallocate when tag is found.
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableCoverTestNg, DeallocateTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a ScrollableItem object and set ScrollableItemPool
     */
    auto tag = "testTag";
    auto nodeFirst = 1;
    auto nodeSecond = 2;
    auto poolSize = 2;
    auto patternCreator = []() -> RefPtr<Pattern> { return AceType::MakeRefPtr<Pattern>(); };
    auto item1 = ScrollableItem::GetOrCreateScrollableItem(tag, nodeFirst, patternCreator);
    auto item2 = ScrollableItem::GetOrCreateScrollableItem(tag, nodeSecond, patternCreator);
    /**
     * @tc.steps: step2. Call Deallocate
     */
    auto scrollableItemPool = std::make_shared<ScrollableItemPool>(poolSize);
    scrollableItemPool->Deallocate(Referenced::RawPtr(item1));
    scrollableItemPool->Deallocate(Referenced::RawPtr(item2));
    auto size = scrollableItemPool->pool_.size();
    /**
     * @tc.steps: step3. Verify size
     */
    EXPECT_EQ(size, 1);
}

/**
 * @tc.name: InitializeTest001
 * @tc.desc: Test Initialize method of Scrollable class.
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableCoverTestNg, InitializeTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a Scrollable object and initialize it with a PipelineContext.
     * @tc.expected: Verify that all event callbacks are set correctly.
     */
    double isCalled = false;
    const std::function<bool(double, int32_t)> scrollCallback = [&isCalled](double offset, int32_t source) {
        isCalled = true;
        return true;
    };
    auto scrollPn = scroll_->GetPattern<PartiallyMockedScrollable>();
    auto scrollable = AceType::MakeRefPtr<Scrollable>(scrollCallback, scrollPn->GetAxis());
    ASSERT_NE(scrollable, nullptr);
    RefPtr<Container> container = Container::Current();
    ASSERT_NE(container, nullptr);
    container->SetUseNewPipeline();
    EXPECT_EQ(Container::IsCurrentUseNewPipeline(), true);
    scrollable->Initialize(scroll_);

    /**
     * @tc.steps: step2. Verify Scrollable initialize success and event trigger
     * @tc.expected: Verify that all event callbacks are set correctly.
     */
    ASSERT_NE(scrollable->panRecognizerNG_, nullptr);
    scrollable->SetAxis(Axis::VERTICAL);
    GestureEvent gestureEvent;
    scrollable->isDragging_ = false;
    auto panRecognizerNG = scrollable->panRecognizerNG_;
    (*panRecognizerNG->onActionStart_)(gestureEvent);
    EXPECT_TRUE(scrollable->isDragging_);
}

/**
 * @tc.name: HandleTouchCancel001
 * @tc.desc: Test the behavior of the HandleTouchCancel method
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableCoverTestNg, HandleTouchCancel001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a scrollable and set scrollOverCallback and isSpringAnimationStop
     */
    auto scrollable = AceType::MakeRefPtr<Scrollable>();
    bool isCalled = false;
    auto scrollOverCallback = [&isCalled](double velocity) { isCalled = true; };
    scrollable->state_ = Scrollable::AnimationState::IDLE;
    scrollable->scrollOverCallback_ = scrollOverCallback;
    /**
     * @tc.steps: step2. HandleTouchCancel and scrollOverCallback are properly called
     */
    scrollable->HandleTouchCancel();
    EXPECT_TRUE(isCalled);
}

/**
 * @tc.name: ComputeCapTest001
 * @tc.desc: Test the behavior of the ComputeCap method
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableCoverTestNg, ComputeCapTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Test ComputeCap with dragCount less than FIRST_THRESHOLD
     * @tc.expected: The result should be 1.0
     */
    auto scrollable = AceType::MakeRefPtr<Scrollable>();
    int32_t dragCountDown = FIRST_THRESHOLD - 1;
    EXPECT_EQ(scrollable->ComputeCap(dragCountDown), 1.0);

    /**
     * @tc.steps: step2. Test ComputeCap with dragCount equal to FIRST_THRESHOLD
     * @tc.expected: The result should be the expected computed cap value
     */
    double expectedCap = 1.0;
    for (int i = 1; i < FIRST_THRESHOLD; ++i) {
        expectedCap += CAP_COEFFICIENT * (i - 1);
    }
    EXPECT_EQ(scrollable->ComputeCap(FIRST_THRESHOLD), expectedCap);
}

/**
 * @tc.name: GetGainTest001
 * @tc.desc: Test the normal scrolling behavior of the GetGain method
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableCoverTestNg, GetGainTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a Scrollable object and initalizes the parameters
     */
    auto scrollable = AceType::MakeRefPtr<Scrollable>();
    auto continuousSlidingCallback = []() { return 300.0; };
    scrollable->continuousSlidingCallback_ = continuousSlidingCallback;
    scrollable->dragCount_ = 5;
    scrollable->preGain_ = 1.0;
    scrollable->lastPos_ = 100.0f;
    double delta = 150.0;
    /**
     * @tc.steps: step2. Test GetGain with dragCount between FIRST_THRESHOLD and SECOND_THRESHOLD
     * @tc.expected: The result should be the expected gain value
     */
    auto expect = 1.0 + CAP_COEFFICIENT * (4);
    double gain = scrollable->GetGain(delta);
    EXPECT_NEAR(gain, expect, 0.001);
}

/**
 * @tc.name: GetGainTest002
 * @tc.desc: Test GetGain method with sliding reversed
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableCoverTestNg, GetGainTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a Scrollable object and initalizes the parameters
     */
    auto scrollable = AceType::MakeRefPtr<Scrollable>();
    auto continuousSlidingCallback = []() { return 300.0; };
    scrollable->continuousSlidingCallback_ = continuousSlidingCallback;
    scrollable->dragCount_ = 5;
    scrollable->preGain_ = 1.0;
    scrollable->lastPos_ = 100.0f;
    double delta = -150.0;

    /**
     * @tc.steps: step2. Test GetGain with delta negative value
     * @tc.expected: The result should be the expected gain value
     */
    double gain = scrollable->GetGain(delta);
    EXPECT_EQ(gain, 1.0);
}

/**
 * @tc.name: ExecuteScrollBeginTest001
 * @tc.desc: Test the behavior of the ExecuteScrollBegin method
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableCoverTestNg, ExecuteScrollBeginTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a Scrollable object and initalizes the parameters
     */
    auto scrollable = AceType::MakeRefPtr<Scrollable>();
    bool isCalled = false;
    scrollable->scrollBeginCallback_ = nullptr;
    scrollable->axis_ = Axis::VERTICAL;
    double mainDelta = 5.0;
    /**
     * @tc.steps: step2. Test ExecuteScrollBegin with scrollable->context_.Upgrade() nullptr
     */
    scrollable->ExecuteScrollBegin(mainDelta);
    ASSERT_EQ(scrollable->context_.Upgrade(), nullptr);
    scrollable->scrollBeginCallback_ = [&isCalled](Dimension x, Dimension y) {
        ScrollInfo info;
        isCalled = true;
        info.dx = x;
        info.dy = y;
        return info;
    };
    EXPECT_FALSE(isCalled);
    /**
     * @tc.steps: step3. Test ExecuteScrollBegin with scrollBeginCallback_ and context_ in axis_ = Axis::VERTICAL
     */
    scrollable->axis_ = Axis::VERTICAL;
    scrollable->context_ = PipelineContext::GetCurrentContext();
    scrollable->ExecuteScrollBegin(mainDelta);
    EXPECT_TRUE(isCalled);
    /**
     * @tc.steps: step4. Test ExecuteScrollBegin with scrollBeginCallback_ and context_ in axis_ = Axis::HORIZONTAL
     * @tc.expected: The result should be the expected mainDelta value
     */
    isCalled = false;
    scrollable->axis_ = Axis::HORIZONTAL;
    scrollable->ExecuteScrollBegin(mainDelta);
    EXPECT_TRUE(isCalled);
}

/**
 * @tc.name: GetFrictionVelocityByFinalPositionTest001
 * @tc.desc: Test the behavior of the GetFrictionVelocityByFinalPositionTest001 method
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableCoverTestNg, GetFrictionVelocityByFinalPositionTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Test GetFrictionVelocityByFinalPosition
     * @tc.expected: The result should be the expected value
     */
    auto scrollable = AceType::MakeRefPtr<Scrollable>();
    float final = 1.0f;
    float position = 2.0f;
    float friction = 3.0f;
    float signum = 4.0f;
    float threshold = 5.0f;
    auto expect = DEFAULT_THRESHOLD * threshold * signum - (final - position) * friction;
    auto actual = scrollable->GetFrictionVelocityByFinalPosition(final, position, friction, signum, threshold);
    EXPECT_EQ(expect, actual);
}

/**
 * @tc.name: StartScrollSnapAnimationTest001
 * @tc.desc: Test the behavior of the StartScrollSnapAnimation method
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableCoverTestNg, StartScrollSnapAnimationTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a Scrollable object and initalizes the parameters
     */
    auto scrollable = AceType::MakeRefPtr<Scrollable>();
    scrollable->nodeId_ = 1;
    float scrollSnapDelta = 50.0f;
    float scrollSnapVelocity = 10.0f;
    scrollable->currentPos_ = 0.0;

    /**
     * @tc.steps: step2. Call StartScrollSnapAnimation
     */
    scrollable->StartScrollSnapAnimation(scrollSnapDelta, scrollSnapVelocity, false);

    /**
     * @tc.expected: The end position should be initialPos + scrollSnapDelta
     */
    EXPECT_EQ(scrollable->endPos_, scrollable->currentPos_ + scrollSnapDelta);
}

/**
 * @tc.name: UpdateSpringMotionTest001
 * @tc.desc: Test the behavior of the UpdateSpringMotion method
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableCoverTestNg, UpdateSpringMotionTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a Scrollable object and set necessary properties
     */
    auto scrollable = AceType::MakeRefPtr<Scrollable>();
    auto propertyCallback = [](float offset) {};
    scrollable->springOffsetProperty_ =
        AceType::MakeRefPtr<NodeAnimatablePropertyFloat>(0.0, std::move(propertyCallback));
    scrollable->state_ = Scrollable::AnimationState::SPRING;
    scrollable->currentPos_ = 0.0;
    scrollable->finalPosition_ = 100.0;

    ExtentPair extent(0.0, 200.0);
    ExtentPair initExtent(50.0, 200.0);

    /**
     * @tc.steps: step2. Call UpdateSpringMotion with a position greater than initExtent.Trailing()
     * @tc.expected: Verify that the final position is updated correctly
     */
    auto finalPosition = extent.Leading();
    auto expect = finalPosition + (finalPosition - extent.Leading()) - (finalPosition - scrollable->currentPos_);
    scrollable->UpdateSpringMotion(0.0, extent, initExtent);
    EXPECT_EQ(scrollable->finalPosition_, expect);
}

/**
 * @tc.name: ProcessScrollMotionStopTest001
 * @tc.desc: Test the behavior of the ProcessScrollMotionStop method
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableCoverTestNg, ProcessScrollMotionStopTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a Scrollable object and set necessary properties
     */
    auto scrollable = AceType::MakeRefPtr<Scrollable>();
    bool isOverScrollCallbackCalled = false;
    scrollable->currentPos_ = 50.0f;
    scrollable->currentVelocity_ = 10.0f;
    scrollable->needScrollSnapChange_ = true;
    scrollable->isDragUpdateStop_ = false;
    scrollable->scrollPause_ = false;
    scrollable->startSnapAnimationCallback_ = [](SnapAnimationOptions snapAnimationOptions) { return false; };
    scrollable->currentVelocity_ = 10.0f;
    auto propertyCallback = [](float offset) {};
    scrollable->frictionOffsetProperty_ =
        AceType::MakeRefPtr<NodeAnimatablePropertyFloat>(0.0, std::move(propertyCallback));
    /**
     * @tc.steps: step2. Call ProcessScrollMotionStop
     * @tc.expected: Verify that the scroll snap change is processed correctly
     */
    scrollable->ProcessScrollMotionStop();
    EXPECT_EQ(scrollable->currentVelocity_, 0.0);
    EXPECT_FALSE(isOverScrollCallbackCalled);

    /**
     * @tc.steps: step3. Set scrollPause_ to true and call ProcessScrollMotionStop again with out overScrollCallback_
     * @tc.expected: Verify that HandleOverScroll is called is executed
     */
    scrollable->scrollPause_ = true;
    scrollable->edgeEffect_ = EdgeEffect::SPRING;
    scrollable->ProcessScrollMotionStop();
    EXPECT_FALSE(scrollable->scrollPause_);

    /**
     * @tc.steps: step4. Set scrollPause_ to true and call ProcessScrollMotionStop again with overScrollCallback_
     * @tc.expected: Verify that HandleOverScroll is called is executed
     */
    isOverScrollCallbackCalled = false;
    scrollable->edgeEffect_ = EdgeEffect::FADE;
    scrollable->overScrollCallback_ = [&isOverScrollCallbackCalled](float velocity) {
        isOverScrollCallbackCalled = true;
        return 0.0f;
    };
    scrollable->scrollPause_ = true;
    scrollable->ProcessScrollMotionStop();
    EXPECT_TRUE(isOverScrollCallbackCalled);
}

/**
 * @tc.name: ProcessSpringMotionTest001
 * @tc.desc: Test the behavior of the ProcessSpringMotion method
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableCoverTestNg, ProcessSpringMotionTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a Scrollable object and set necessary properties
     */
    auto scrollable = AceType::MakeRefPtr<Scrollable>();
    scrollable->context_ = PipelineContext::GetCurrentContext();
    scrollable->currentPos_ = 0.0;
    scrollable->isFadingAway_ = true;
    auto propertyCallback = [](float offset) {};
    scrollable->springOffsetProperty_ =
        AceType::MakeRefPtr<NodeAnimatablePropertyFloat>(0.0, std::move(propertyCallback));
    scrollable->finalPosition_ = 100.0f;
    bool isVelocityCallbackCalled = false;
    scrollable->remainVelocityCallback_ = [&isVelocityCallbackCalled](float velocity) {
        isVelocityCallbackCalled = true;
        return true;
    };
    /**
     * @tc.steps: step2. Call method with a nearEqual new position and moved is false.
     * @tc.expected: Verify that the scroll motion is processed correctly
     */
    scrollable->state_ = Scrollable::AnimationState::SPRING;
    scrollable->callback_ = [](const double offset, int32_t source) { return false; };
    scrollable->ProcessSpringMotion(0.0);
    EXPECT_EQ(scrollable->currentPos_, 0.0);
    EXPECT_EQ(scrollable->state_, Scrollable::AnimationState::IDLE);
    EXPECT_FALSE(isVelocityCallbackCalled);
    /**
     * @tc.steps: step2. Call method with distance * nextDistance < 0 and has remainVelocityCallback_.
     * @tc.expected: Verify that the scroll motion is processed correctly
     */
    scrollable->state_ = Scrollable::AnimationState::SPRING;
    scrollable->currentPos_ = 0.0;
    scrollable->ProcessSpringMotion(110.0);
    EXPECT_TRUE(isVelocityCallbackCalled);
    EXPECT_TRUE(scrollable->scrollPause_);
    EXPECT_EQ(scrollable->state_, Scrollable::AnimationState::IDLE);
}

/**
 * @tc.name: SetSlipFactorTest001
 * @tc.desc: Test the behavior of the SetSlipFactor method
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableCoverTestNg, SetSlipFactorTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a Scrollable object and set SlipFactor to a value within the range
     */
    auto scrollable = AceType::MakeRefPtr<Scrollable>();
    double validSlipFactor = 150.0;
    scrollable->SetSlipFactor(validSlipFactor);
    /**
     * @tc.expected: The slipFactor_ should be set to the provided value
     */
    EXPECT_EQ(scrollable->slipFactor_, validSlipFactor);
}

/**
 * @tc.name: GetSpringPropertyTest001
 * @tc.desc: Test the behavior of the GetSpringProperty method
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableCoverTestNg, GetSpringPropertyTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a Scrollable object and set necessary properties
     */
    auto scrollable = AceType::MakeRefPtr<Scrollable>();
    scrollable->finalPosition_ = 0.0f;
    scrollable->state_ = Scrollable::AnimationState::SPRING;
    scrollable->currentPos_ = 0.0f;

    /**
     * @tc.steps: step2. Get the callback from springOffsetProperty_
     */
    auto springProperty = scrollable->GetSpringProperty();
    ASSERT_NE(springProperty, nullptr);
    auto propertyBase = springProperty->GetProperty();
    auto animatableProperty = AceType::DynamicCast<AnimatablePropertyFloat>(propertyBase);
    ASSERT_NE(animatableProperty, nullptr);

    auto propertyCallback = animatableProperty->GetUpdateCallback();
    ASSERT_TRUE(propertyCallback);
    /**
     * @tc.steps: step3. Call the callback and verify the expected behavior
     */
    propertyCallback(0.1f);
    EXPECT_EQ(scrollable->state_, Scrollable::AnimationState::IDLE);
}

/**
 * @tc.name: GetSnapPropertyCallbackTest001
 * @tc.desc: Test GetSnapProperty method to ensure callback is correctly set and callable
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableCoverTestNg, GetSnapPropertyCallbackTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a Scrollable object and set necessary properties
     */
    auto scrollable = AceType::MakeRefPtr<Scrollable>();
    scrollable->state_ = Scrollable::AnimationState::SNAP;
    scrollable->context_ = PipelineContext::GetCurrentContext();

    /**
     * @tc.steps: step2. Get the callback from snapOffsetProperty_
     */
    auto snapProperty = scrollable->GetSnapProperty();
    ASSERT_NE(snapProperty, nullptr);
    auto propertyBase = snapProperty->GetProperty();
    auto animatableProperty = AceType::DynamicCast<AnimatablePropertyFloat>(propertyBase);
    ASSERT_NE(animatableProperty, nullptr);

    auto callback = animatableProperty->GetUpdateCallback();
    ASSERT_TRUE(callback);
    /**
     * @tc.steps: step3. Call the callback and verify the expected behavior
     */
    callback(0.0f);
    EXPECT_EQ(scrollable->state_, Scrollable::AnimationState::IDLE);
}

/**
 * @tc.name: OnScrollStartEndTest001
 * @tc.desc: Test both methods of OnScrollStart and OnScrollEnd to ensure callback is correctly set and callable
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableCoverTestNg, OnScrollStartEndTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a refreshCoordination object and set callback
     */
    auto scrollPn = scroll_->GetPattern<PartiallyMockedScrollable>();
    auto refreshNode = FrameNode::CreateFrameNode("Refresh", -1, AceType::MakeRefPtr<RefreshPattern>());
    scroll_->MountToParent(refreshNode);
    refreshNode->MarkModifyDone();
    scrollPn->refreshCoordination_ = AceType::MakeRefPtr<RefreshCoordination>(scrollPn->GetHost());
    bool isDragTest = false;
    float mainVelocityTest = 0.0f;
    auto startCallBack = [&isDragTest, &mainVelocityTest](bool isDrag, float mainVelocity) {
        isDragTest = isDrag;
        mainVelocityTest = mainVelocity;
        return;
    };
    auto endCallBack = [&mainVelocityTest](float mainVelocity) {
        mainVelocityTest = mainVelocity;
        return;
    };
    ASSERT_NE(scrollPn->refreshCoordination_, nullptr);
    auto eventHub = scrollPn->refreshCoordination_->coordinationEvent_;
    ASSERT_NE(eventHub, nullptr);
    eventHub->onScrollStartEvent_ = startCallBack;
    eventHub->onScrollEndEvent_ = endCallBack;
    /**
     * @tc.steps: step2. Call the OnScrollStart and verify the expected behavior
     */
    scrollPn->refreshCoordination_->OnScrollStart(true, 50.0f);
    EXPECT_TRUE(isDragTest);
    EXPECT_EQ(50.0f, mainVelocityTest);

    /**
     * @tc.steps: step3. Call the OnScrollEnd and verify the expected behavior
     */
    scrollPn->refreshCoordination_->OnScrollEnd(70.0f);
    EXPECT_EQ(70.0f, mainVelocityTest);
}

/**
 * @tc.name: IsRefreshInScroll001
 * @tc.desc: Test IsRefreshInScroll method to ensure scrollOffsetValue greatNotEqual 0.0
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableCoverTestNg, IsRefreshInScroll001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a refreshCoordination object and set scrollOffset_
     */
    auto scrollPn = scroll_->GetPattern<PartiallyMockedScrollable>();
    auto refreshNode = FrameNode::CreateFrameNode("Refresh", -1, AceType::MakeRefPtr<RefreshPattern>());
    scroll_->MountToParent(refreshNode);
    refreshNode->MarkModifyDone();
    scrollPn->refreshCoordination_ = AceType::MakeRefPtr<RefreshCoordination>(scrollPn->GetHost());
    auto refreshPn = refreshNode->GetPattern<RefreshPattern>();
    refreshPn->scrollOffset_ = 50.0;
    /**
     * @tc.steps: step2. Call the IsRefreshInScroll and verify the expected behavior
     */
    auto isRefresh = scrollPn->refreshCoordination_->IsRefreshInScroll();
    EXPECT_TRUE(isRefresh);
}

/**
 * @tc.name: ProcessNavBarReactOnStart001
 * @tc.desc: Test ProcessNavBarReactOnStart method and cover coordinateWithNavigation method in SCROLL_FROM_START
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableCoverTestNg, ProcessNavBarReactOnStart001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Get a scrollPn object and set navBarPattern_
     */
    auto scrollPn = scroll_->GetPattern<PartiallyMockedScrollable>();
    scrollPn->navBarPattern_ = AceType::MakeRefPtr<NavBarPattern>();
    double offset = 50.0;
    int32_t source = SCROLL_FROM_START;
    bool isAtTop = true;
    /**
     * @tc.steps: step2. Call the coordinateWithNavigation in SCROLL_FROM_START
     * @tc.expected: isReactInParentMovement_ is true
     */
    scrollPn->CoordinateWithNavigation(offset, source, isAtTop);
    EXPECT_TRUE(scrollPn->isReactInParentMovement_);
}

/**
 * @tc.name: CoordinateWithNavigationt001
 * @tc.desc:  Test the behavior of the CoordinateWithNavigation method Test
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableCoverTestNg, CoordinateWithNavigationt001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Get a scrollPn object and set navBarPattern_
     */
    auto scrollPn = scroll_->GetPattern<PartiallyMockedScrollable>();
    scrollPn->navBarPattern_ = AceType::MakeRefPtr<NavBarPattern>();
    double offset = 50.0;
    int32_t source = SCROLL_FROM_BAR;
    bool isAtTop = true;
    scrollPn->isReactInParentMovement_ = true;

    /**
     * @tc.steps: step2. Call the coordinateWithNavigation  if isReactInParentMovement_ is true
     * @tc.expected: isReactInParentMovement_ is true and ProcessNavBarReactOnUpdate is called
     */
    scrollPn->CoordinateWithNavigation(offset, source, isAtTop);
    EXPECT_TRUE(scrollPn->isReactInParentMovement_);

    /**
     * @tc.steps: step3. Call the method if isReactInParentMovement_ is true and isAtTop is false and offset is neg
     * @tc.expected: isReactInParentMovement_ is false and ProcessNavBarReactOnEnd is called
     */
    isAtTop = false;
    offset = -50.0;
    scrollPn->CoordinateWithNavigation(offset, source, isAtTop);
    EXPECT_FALSE(scrollPn->isReactInParentMovement_);
}

/**
 * @tc.name: OnWindowHide001
 * @tc.desc:  Test the behavior of the OnWindowHide method Test
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableCoverTestNg, OnWindowHide001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Get a scrollPn object and init parameters
     */
    auto scrollPn = scroll_->GetPattern<PartiallyMockedScrollable>();
    auto propertyCallback = [](float offset) {};
    const std::function<bool(double, int32_t)> scrollCallback = [](double offset, int32_t source) { return true; };
    auto scrollable = AceType::MakeRefPtr<Scrollable>(scrollCallback, scrollPn->GetAxis());
    scrollable->frictionOffsetProperty_ =
        AceType::MakeRefPtr<NodeAnimatablePropertyFloat>(0.0, std::move(propertyCallback));
    scrollable->state_ = Scrollable::AnimationState::FRICTION;
    ASSERT_NE(scrollPn->scrollableEvent_, nullptr);
    scrollPn->scrollableEvent_->scrollable_ = scrollable;
    scrollPn->OnWindowHide();
    /**
     * @tc.steps: step2. Get a scrollPn object and call OnWindowHide
     * @tc.expected: the OnWindowHide method run match expectation
     */
    EXPECT_EQ(scrollable->state_, Scrollable::AnimationState::IDLE);
}

/**
 * @tc.name: HandleFadeEffect001
 * @tc.desc:  Test the behavior of the HandleFadeEffect method Test
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableCoverTestNg, HandleFadeEffect001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Get a scrollPn object and init parameters
     */
    auto scrollPn = scroll_->GetPattern<PartiallyMockedScrollable>();
    auto mockEffect = AceType::MakeRefPtr<MockScrollEdgeEffect>();
    scrollPn->scrollEffect_ = mockEffect;
    float offset = 10.0f;
    int32_t source = SCROLL_FROM_UPDATE;
    const SizeF& size = SizeF(10.0f, 100.0f);
    bool flag = false;
    EXPECT_CALL(*mockEffect, HandleOverScroll(_, _, _, _, _))
        .WillOnce(DoAll([&flag](Axis, float, const SizeF&, bool, bool) { flag = true; }));

    /**
     * @tc.steps: step2. Get a scrollPn object and call HandleFadeEffect
     * @tc.expected: the HandleFadeEffect method run match expectation
     */
    scrollPn->HandleFadeEffect(offset, source, size, false);
    EXPECT_TRUE(flag);
}

/**
 * @tc.name: GetScrollDeltaTest001
 * @tc.desc: Test GetScrollDelta method to ensure it calculates the delta correctly
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableCoverTestNg, GetScrollDeltaTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a scrollable and init parameters
     */
    auto scrollPn = scroll_->GetPattern<PartiallyMockedScrollable>();
    float offset = 100.0f;
    bool stopAnimation = false;
    auto lastPosition = 200.0f;
    scrollPn->lastPosition_ = 200.0f;
    scrollPn->finalPosition_ = 50.0f;
    scrollPn->useTotalOffset_ = false;

    /**
     * @tc.steps: step2. Test GetScrollDelta
     * @tc.expected: Verify the delta calculation
     */
    float delta = scrollPn->GetScrollDelta(offset, stopAnimation);
    EXPECT_NEAR(delta, lastPosition - offset, 0.001f);
}

/**
 * @tc.name: PauseAnimation001
 * @tc.desc: Test the behaviour of the PauseAnimation method
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableCoverTestNg, PauseAnimation001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a scrollable and init parameters
     */
    auto scrollPn = scroll_->GetPattern<PartiallyMockedScrollable>();
    std::shared_ptr<AnimationUtils::Animation> animation;
    scrollPn->isAnimationStop_ = false;
    scrollPn->currentVelocity_ = 100.0;

    /**
     * @tc.steps: step2. Test PauseAnimation
     * @tc.expected: Verify the PauseAnimation status
     */
    scrollPn->PauseAnimation(animation);
    EXPECT_EQ(scrollPn->currentVelocity_, 0.0);
    EXPECT_TRUE(scrollPn->isAnimationStop_);
}

/**
 * @tc.name: RemainVelocityToChild001
 * @tc.desc: Test the behaviour of the RemainVelocityToChild method
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableCoverTestNg, RemainVelocityToChild001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a scrollable and init parameters
     */
    auto scrollPn = scroll_->GetPattern<PartiallyMockedScrollable>();
    auto scrollable = AceType::MakeRefPtr<Scrollable>();
    auto propertyCallback = [](float offset) {};
    scrollable->springOffsetProperty_ =
        AceType::MakeRefPtr<NodeAnimatablePropertyFloat>(0.0, std::move(propertyCallback));
    scrollable->state_ = Scrollable::AnimationState::SPRING;
    scrollPn->scrollAbort_ = false;
    ASSERT_NE(scrollPn->scrollableEvent_, nullptr);
    scrollPn->scrollableEvent_->scrollable_ = scrollable;
    float remainVelocity = 150.0f;
    /**
     * @tc.steps: step2. Test RemainVelocityToChild
     * @tc.expected: Verify the scrollAbort_ status
     */
    scrollPn->RemainVelocityToChild(remainVelocity);
    EXPECT_TRUE(scrollPn->scrollAbort_);
}

/**
 * @tc.name: UnRegister2DragDropManager001
 * @tc.desc: Test the behaviour of the UnRegister2DragDropManager method
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableCoverTestNg, UnRegister2DragDropManager001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a scrollable and Register2DragDropManager
     */
    auto scrollPn = scroll_->GetPattern<PartiallyMockedScrollable>();
    scrollPn->Register2DragDropManager();
    auto dragDropManager = MockPipelineContext::GetCurrent()->GetDragDropManager();
    ASSERT_NE(dragDropManager, nullptr);
    /**
     * @tc.expected: step2. Verify that nodesForDragNotify_ contains the nodeId.
     */
    auto it = dragDropManager->nodesForDragNotify_.find(scroll_->GetId());
    EXPECT_TRUE(it != dragDropManager->nodesForDragNotify_.end());
    EXPECT_EQ(it->first, scroll_->GetId());
    EXPECT_EQ(it->second.Upgrade(), scroll_);

    scrollPn->UnRegister2DragDropManager(&(*scroll_));
    /**
     * @tc.expected: step3. Verify that nodesForDragNotify_ dont contains the nodeId.
     */
    it = dragDropManager->nodesForDragNotify_.find(scroll_->GetId());
    EXPECT_TRUE(it == dragDropManager->nodesForDragNotify_.end());
}

/**
 * @tc.name: ScrollPage001
 * @tc.desc: Test the behaviour of the ScrollPage method
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableCoverTestNg, ScrollPage001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a scrollable and init parameters
     */
    auto scrollPn = scroll_->GetPattern<PartiallyMockedScrollable>();
    auto scrollable = AceType::MakeRefPtr<Scrollable>();
    auto propertyCallback = [](float offset) {};
    scrollable->springOffsetProperty_ =
        AceType::MakeRefPtr<NodeAnimatablePropertyFloat>(0.0, std::move(propertyCallback));
    scrollable->state_ = Scrollable::AnimationState::SPRING;
    scrollPn->scrollAbort_ = false;
    ASSERT_NE(scrollPn->scrollableEvent_, nullptr);
    scrollPn->scrollableEvent_->scrollable_ = scrollable;
    /**
     * @tc.steps: step2. Test ScrollPage
     * @tc.expected: Verify the scrollAbort_ status
     */
    scrollPn->ScrollPage(false, true, AccessibilityScrollType::SCROLL_HALF);
    EXPECT_TRUE(scrollPn->scrollAbort_);
}

/**
 * @tc.name: Fling001
 * @tc.desc: Test the behaviour of the Fling method
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableCoverTestNg, Fling001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Get a scrollPn and initializes the parameters of controller and scrollable
     */
    auto scrollPn = scroll_->GetPattern<PartiallyMockedScrollable>();
    auto controller = AceType::MakeRefPtr<ScrollableController>();
    scrollPn->SetPositionController(controller);
    auto scrollable = AceType::MakeRefPtr<Scrollable>();
    auto propertyCallback = [](float offset) {};
    scrollable->springOffsetProperty_ =
        AceType::MakeRefPtr<NodeAnimatablePropertyFloat>(0.0, std::move(propertyCallback));
    scrollable->state_ = Scrollable::AnimationState::SPRING;
    scrollPn->scrollAbort_ = false;
    ASSERT_NE(scrollPn->scrollableEvent_, nullptr);
    scrollPn->scrollableEvent_->scrollable_ = scrollable;

    /**
     * @tc.steps: step2. Test Fling
     * @tc.expected: Verify the scrollAbort_ status
     */
    double flingVelocity = 150.0;
    controller->Fling(flingVelocity);
    EXPECT_TRUE(scrollPn->scrollAbort_);
}

/**
 * @tc.name: SetMaxFlingSpeed001
 * @tc.desc: Test the behavior of the SetMaxFlingSpeed method
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableCoverTestNg, SetMaxFlingSpeed001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Get scrollablePn and set SetMaxFlingSpeed max to 100.0
     * @tc.expected: maxFlingVelocity_ is updated to max * density
     */
    auto scrollPn = scroll_->GetPattern<PartiallyMockedScrollable>();
    ScrollableModelNG::SetMaxFlingSpeed(&(*scroll_), 100.0);
    EXPECT_EQ(scrollPn->maxFlingVelocity_, 100.0);
}

/**
 * @tc.name: GetOrCreateScrollableItemWithParent
 * @tc.desc: Test GetOrCreateScrollableItem method
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableCoverTestNg, GetOrCreateScrollableItemWithParent001, TestSize.Level1)
{
    // Create a pattern creator
    auto patternCreator = []() -> RefPtr<Pattern> { return AceType::MakeRefPtr<Pattern>(); };
    auto tag = "testTag";
    auto nodeId = 1;
    auto parentNode = AceType::MakeRefPtr<ScrollableItem>("parentTag", 0, patternCreator(), false);
    auto childPattern = patternCreator();
    auto childNode = AceType::MakeRefPtr<ScrollableItem>(tag, nodeId, patternCreator(), false);
    parentNode->AddChild(childNode);
    ElementRegister::GetInstance()->AddUINode(childNode);
    ASSERT_EQ(childNode->GetParent(), parentNode);
    /**
     * @tc.steps: step1. Call GetOrCreateScrollableItem when node exists and tag not exists
     * @tc.expected: The existing ScrollableItem is removed from parent node and create a new node
     */
    auto result = ScrollableItem::GetOrCreateScrollableItem("notExistsTag", nodeId, patternCreator);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->GetTag(), "notExistsTag");
    EXPECT_EQ(result->GetId(), nodeId);
    EXPECT_EQ(childNode->GetParent(), nullptr);
}

/**
 * @tc.name: GetOrCreateScrollableItemWithoutParent
 * @tc.desc: Test GetOrCreateScrollableItem method
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableCoverTestNg, GetOrCreateScrollableItemWithParent002, TestSize.Level1)
{
    auto patternCreator = []() -> RefPtr<Pattern> { return AceType::MakeRefPtr<Pattern>(); };
    auto tag = "testTag";
    auto nodeId = 1;
    auto childNode = AceType::MakeRefPtr<ScrollableItem>(tag, nodeId, patternCreator(), false);
    ElementRegister::GetInstance()->AddUINode(childNode);
    ASSERT_EQ(childNode->GetParent(), nullptr);
    /**
     * @tc.steps: step1. Call GetOrCreateScrollableItem when the ScrollableItem does not have a parent
     * @tc.expected: A new ScrollableItem is created and registered
     */
    auto result = ScrollableItem::GetOrCreateScrollableItem("notExistsTag", nodeId, patternCreator);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->GetTag(), "notExistsTag");
    EXPECT_EQ(result->GetId(), nodeId);
}

/**
 * @tc.name: InitializeTest002
 * @tc.desc: Test Initialize method and covering actionUpdate, actionEnd, actionCancel
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableCoverTestNg, InitializeTest002, TestSize.Level1)
{
    const std::function<bool(double, int32_t)> scrollCallback = [](double offset, int32_t source) { return true; };
    auto scrollPn = scroll_->GetPattern<PartiallyMockedScrollable>();
    auto scrollable = AceType::MakeRefPtr<Scrollable>(scrollCallback, scrollPn->GetAxis());
    ASSERT_NE(scrollable, nullptr);
    auto propertyCallback = [](float offset) {};
    scrollable->frictionOffsetProperty_ =
        AceType::MakeRefPtr<NodeAnimatablePropertyFloat>(0.0, std::move(propertyCallback));
    RefPtr<Container> conainer = Container::Current();
    ASSERT_NE(conainer, nullptr);
    conainer->SetUseNewPipeline();
    scrollable->Initialize(scroll_);
    ASSERT_NE(scrollable->panRecognizerNG_, nullptr);
    auto panRecognizerNG = scrollable->panRecognizerNG_;
    GestureEvent gestureEvent;
    scrollable->isDragging_ = true;
    bool isDragCancelCalled = false;
    bool isActionEndCalled = false;
    /**
     * @tc.steps: step1. Trigger onActionUpdate event.
     * @tc.expected: Verify that onActionUpdate executed.
     */
    scrollable->state_ = Scrollable::AnimationState::FRICTION;
    (*panRecognizerNG->onActionUpdate_)(gestureEvent);
    EXPECT_EQ(scrollable->state_, Scrollable::AnimationState::IDLE);
    /**
     * @tc.steps: step2. Trigger actionCancel and onActionEnd without dragCancelCallback_ and actionEnd_.
     * @tc.expected: Verify that actionCancel and onActionEnd is executed.
     */
    scrollable->panActionEndEvents_.clear();
    scrollable->dragCancelCallback_ = nullptr;
    (*panRecognizerNG->onActionEnd_)(gestureEvent);
    (*panRecognizerNG->onActionCancel_)(gestureEvent);
    EXPECT_FALSE(scrollable->isDragging_);

    /**
     * @tc.steps: step3. Trigger actionCancel and onActionEnd with dragCancelCallback_ and actionEnd_.
     * @tc.expected: Verify that actionCancel and onActionEnd is executed.
     */
    scrollable->dragCancelCallback_ = [&isDragCancelCalled]() { isDragCancelCalled = true; };
    scrollable->panActionEndEvents_.emplace_back(
        [&isActionEndCalled](GestureEvent gestureEvent) { isActionEndCalled = true; });
    (*panRecognizerNG->onActionCancel_)(gestureEvent);
    (*panRecognizerNG->onActionEnd_)(gestureEvent);
    EXPECT_TRUE(isDragCancelCalled);
    EXPECT_TRUE(isActionEndCalled);
}

/**
 * @tc.name: HandleTouchDownTest001
 * @tc.desc: Test HandleTouchDown method
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableCoverTestNg, HandleTouchDownTest001, TestSize.Level1)
{
    auto scrollPn = scroll_->GetPattern<PartiallyMockedScrollable>();
    auto scrollable = AceType::MakeRefPtr<Scrollable>([](double, int32_t) { return true; }, scrollPn->GetAxis());
    ASSERT_NE(scrollable, nullptr);
    auto frictionPropertyCallback = [](float offset) {};
    auto snapPropertyCallback = [](float offset) {};
    scrollable->frictionOffsetProperty_ =
        AceType::MakeRefPtr<NodeAnimatablePropertyFloat>(0.0, std::move(frictionPropertyCallback));
    scrollable->snapOffsetProperty_ =
        AceType::MakeRefPtr<NodeAnimatablePropertyFloat>(0.0, std::move(snapPropertyCallback));
    /**
     * @tc.steps: step1. Set isFrictionAnimationStop_ to false
     * @tc.expected: StopFrictionAnimation is executed.
     */
    scrollable->state_ = Scrollable::AnimationState::FRICTION;
    scrollable->HandleTouchDown();
    EXPECT_EQ(scrollable->state_, Scrollable::AnimationState::IDLE);
    /**
     * @tc.steps: step2. Set isSnapAnimationStop_ to false
     * @tc.expected: StopSnapAnimation is executed.
     */
    scrollable->state_ = Scrollable::AnimationState::SNAP;
    scrollable->HandleTouchDown();
    EXPECT_EQ(scrollable->state_, Scrollable::AnimationState::IDLE);
}

/**
 * @tc.name: HandleTouchUpTest001
 * @tc.desc: Test HandleTouchUp method
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableCoverTestNg, HandleTouchUpTest001, TestSize.Level1)
{
    auto scrollPn = scroll_->GetPattern<PartiallyMockedScrollable>();
    auto scrollable = AceType::MakeRefPtr<Scrollable>([](double, int32_t) { return true; }, scrollPn->GetAxis());
    ASSERT_NE(scrollable, nullptr);
    /**
     * @tc.steps: step1. Set nestedScrolling_ to true and isTouching_ to true
     */
    scrollable->isTouching_ = true;
    scrollable->nestedScrolling_ = true;
    scrollable->HandleTouchUp();
    EXPECT_FALSE(scrollable->isTouching_);
    /**
     * @tc.steps: step2. Set nestedScrolling_ to false and outBoundary nullptr and isSnapScrollAnimationStop_ false
     */
    scrollable->isTouching_ = true;
    scrollable->nestedScrolling_ = false;
    scrollable->outBoundaryCallback_ = nullptr;
    scrollable->state_ = Scrollable::AnimationState::SNAP;
    scrollable->nestedScrolling_ = false;
    scrollable->HandleTouchUp();
    EXPECT_FALSE(scrollable->isTouching_);
}

/**
 * @tc.name: HandleTouchUpTest002
 * @tc.desc: Test HandleTouchUp method
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableCoverTestNg, HandleTouchUpTest002, TestSize.Level1)
{
    auto scrollPn = scroll_->GetPattern<PartiallyMockedScrollable>();
    auto scrollable = AceType::MakeRefPtr<Scrollable>([](double, int32_t) { return true; }, scrollPn->GetAxis());
    ASSERT_NE(scrollable, nullptr);
    scrollable->nestedScrolling_ = false;
    /**
     * @tc.steps: step1. Set outBoundary has callback and isSpringAnimationStop_ to false
     */
    bool outBoundaryIsCalled = false;
    scrollable->outBoundaryCallback_ = [&outBoundaryIsCalled]() {
        outBoundaryIsCalled = true;
        return true;
    };
    scrollable->state_ = Scrollable::AnimationState::SPRING;
    scrollable->HandleTouchUp();
    EXPECT_TRUE(outBoundaryIsCalled);
    /**
     * @tc.steps: step2. Set scrollOverCallback_ and onScrollStartRec_ nullptr and executed successfully
     */
    double expectVelocity = 0.0;
    scrollable->state_ = Scrollable::AnimationState::IDLE;
    scrollable->onScrollStartRec_ = nullptr;
    scrollable->scrollOverCallback_ = [&expectVelocity](double velocity) { expectVelocity = 1.0; };
    scrollable->HandleTouchUp();
    EXPECT_EQ(expectVelocity, 1.0);
    /**
     * @tc.steps: step3. Set scrollable has onScrollStartRec_ and executed successfully
     */
    bool isOnScrollStartRec = false;
    scrollable->state_ = Scrollable::AnimationState::IDLE;
    scrollable->onScrollStartRec_ = [&isOnScrollStartRec](float value) { isOnScrollStartRec = true; };
    scrollable->scrollOverCallback_ = [&expectVelocity](double velocity) {};
    scrollable->HandleTouchUp();
    EXPECT_TRUE(isOnScrollStartRec);
}

/**
 * @tc.name: IsAnimationNotRunningTest001
 * @tc.desc: Test IsAnimationNotRunning method of Scrollable class.
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableCoverTestNg, IsAnimationNotRunningTest001, TestSize.Level1)
{
    auto scrollPn = scroll_->GetPattern<PartiallyMockedScrollable>();
    auto scrollable = AceType::MakeRefPtr<Scrollable>([](double, int32_t) { return true; }, scrollPn->GetAxis());
    ASSERT_NE(scrollable, nullptr);
    /**
     * @tc.steps: step1. Set isTouching_ false and others true.
     */
    scrollable->isTouching_ = false;
    EXPECT_TRUE(scrollable->IsAnimationNotRunning());
}

/**
 * @tc.name: StopScrollable001
 * @tc.desc: Test StopScrollable method
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableCoverTestNg, StopScrollable001, TestSize.Level1)
{
    auto scrollPn = scroll_->GetPattern<PartiallyMockedScrollable>();
    auto scrollable = AceType::MakeRefPtr<Scrollable>([](double, int32_t) { return true; }, scrollPn->GetAxis());
    ASSERT_NE(scrollable, nullptr);
    auto propertyCallback = [](float offset) {};
    scrollable->frictionOffsetProperty_ =
        AceType::MakeRefPtr<NodeAnimatablePropertyFloat>(0.0, std::move(propertyCallback));
    /**
     * @tc.steps: step1.Set isFrictionAnimationStop_ false and call StopScrollable.
     */
    scrollable->state_ = Scrollable::AnimationState::FRICTION;
    scrollable->StopScrollable();
    EXPECT_EQ(scrollable->state_, Scrollable::AnimationState::IDLE);
}

/**
 * @tc.name: HandleScrollEnd001
 * @tc.desc: Test HandleScrollEnd method
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableCoverTestNg, HandleScrollEnd001, TestSize.Level1)
{
    auto scrollPn = scroll_->GetPattern<PartiallyMockedScrollable>();
    auto scrollable = AceType::MakeRefPtr<Scrollable>([](double, int32_t) { return true; }, scrollPn->GetAxis());
    ASSERT_NE(scrollable, nullptr);
    bool isCalled = false;
    scrollable->scrollEndCallback_ = [&isCalled]() { isCalled = true; };
    /**
     * @tc.steps: step1.Set scrollEndCallback_ and call HandleScrollEnd.
     */
    scrollable->HandleScrollEnd(1.0f);
    EXPECT_TRUE(isCalled);
}

/**
 * @tc.name: HandleDragUpdate001
 * @tc.desc: Test HandleDragUpdate method
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableCoverTestNg, HandleDragUpdate001, TestSize.Level1)
{
    auto scrollPn = scroll_->GetPattern<PartiallyMockedScrollable>();
    auto scrollable = AceType::MakeRefPtr<Scrollable>([](double, int32_t) { return true; }, scrollPn->GetAxis());
    ASSERT_NE(scrollable, nullptr);
    GestureEvent info;
    info.SetMainVelocity(10.0);
    scrollable->dragCount_ = 5;
    scrollable->lastGestureVelocity_ = -1;
    /**
     * @tc.steps: step1.Set (Negative(lastGestureVelocity_ / info.GetMainVelocity())).
     */
    scrollable->HandleDragUpdate(info);
    EXPECT_EQ(scrollable->dragCount_, 1);
    /**
     * @tc.steps: step2.Set positive(lastGestureVelocity_ / info.GetMainVelocity()) and isFrictionAnimationStop_ false.
     */
    auto propertyCallback = [](float offset) {};
    scrollable->frictionOffsetProperty_ =
        AceType::MakeRefPtr<NodeAnimatablePropertyFloat>(0.0, std::move(propertyCallback));
    scrollable->dragCount_ = 5;
    info.SetMainVelocity(10.0);
    scrollable->lastGestureVelocity_ = 10;
    scrollable->isDragUpdateStop_ = false;
    scrollable->state_ = Scrollable::AnimationState::FRICTION;
    scrollable->HandleDragUpdate(info);
    EXPECT_TRUE(scrollable->isDragUpdateStop_);
    EXPECT_EQ(scrollable->state_, Scrollable::AnimationState::IDLE);
}

/**
 * @tc.name: StartScrollAnimationTest001
 * @tc.desc: Test StartScrollAnimation method
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableCoverTestNg, StartScrollAnimationTest001, TestSize.Level1)
{
    auto scrollPn = scroll_->GetPattern<PartiallyMockedScrollable>();
    auto scrollable = AceType::MakeRefPtr<Scrollable>([](double, int32_t) { return true; }, scrollPn->GetAxis());
    ASSERT_NE(scrollable, nullptr);
    auto propertyCallback = [](float offset) {};
    scrollable->springOffsetProperty_ =
        AceType::MakeRefPtr<NodeAnimatablePropertyFloat>(0.0, std::move(propertyCallback));
    /**
     * @tc.steps: step1. Call StartScrollAnimation and verify StopSpringAnimation is called.
     */
    scrollable->state_ = Scrollable::AnimationState::SPRING;
    scrollable->StartScrollAnimation(100.0f, 241.0f);
    EXPECT_EQ(scrollable->state_, Scrollable::AnimationState::FRICTION);
}

/**
 * @tc.name: GetGainTest003
 * @tc.desc: Test GetGain method
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestNg, GetGainTest003, TestSize.Level1)
{
    auto scrollPn = scroll_->GetPattern<PartiallyMockedScrollable>();
    auto scrollable = AceType::MakeRefPtr<Scrollable>([](double, int32_t) { return true; }, scrollPn->GetAxis());
    ASSERT_NE(scrollable, nullptr);
    /**
     * @tc.steps: step1. Call GetGain with continuousSlidingCallback nullptr.
     */
    scrollable->GetGain(150.0);
    EXPECT_EQ(scrollable->preGain_, 1.0);
    /**
     * @tc.steps: step2. Call GetGain with continuousSlidingCallback has callback.
     */
    scrollable->continuousSlidingCallback_ = []() { return 0.0; };
    scrollable->GetGain(150.0);
    EXPECT_EQ(scrollable->preGain_, 1.0);
    /**
     * @tc.steps: step3. Call GetGain with Negative lastPos_ / delta.
     */
    scrollable->continuousSlidingCallback_ = []() { return 1.0; };
    scrollable->dragCount_ = 6;
    scrollable->lastPos_ = -10;
    scrollable->GetGain(150.0);
    EXPECT_EQ(scrollable->preGain_, 1.0);
    /**
     * @tc.steps: step4. Call GetGain with dragCount_ >= SECOND_THRESHOLD and Negative lastPos_ / delta.
     */
    scrollable->dragCount_ = 10;
    scrollable->lastPos_ = -10;
    scrollable->GetGain(150.0);
    EXPECT_EQ(scrollable->preGain_, 1.0);
    /**
     * @tc.steps: step5 Call GetGain with dragCount_ >= SECOND_THRESHOLD and positive lastPos_ / delta.
     */
    scrollable->continuousSlidingCallback_ = []() { return 1; };
    scrollable->dragCount_ = 10;
    scrollable->lastPos_ = 10;
    scrollable->GetGain(150.0);
    EXPECT_EQ(scrollable->preGain_, 16);
}

/**
 * @tc.name: ProcessSnapMotion001
 * @tc.desc: Test ProcessSnapMotion method
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableCoverTestNg, ProcessSnapMotion001, TestSize.Level1)
{
    auto scrollPn = scroll_->GetPattern<PartiallyMockedScrollable>();
    auto scrollable = AceType::MakeRefPtr<Scrollable>([](double, int32_t) { return true; }, scrollPn->GetAxis());
    ASSERT_NE(scrollable, nullptr);
    auto snapPropertyCallback = [](float offset) {};
    scrollable->snapOffsetProperty_ =
        AceType::MakeRefPtr<NodeAnimatablePropertyFloat>(0.0, std::move(snapPropertyCallback));
    /**
     * @tc.steps: step1. currentPos eq pos and Callback and SnapScrollAnimationStop noraml conditions.
     */
    scrollable->currentPos_ = 0.0;
    scrollable->skipRestartSpring_ = false;
    scrollable->state_ = Scrollable::AnimationState::SNAP;
    scrollable->ProcessListSnapMotion(0.0);
    EXPECT_EQ(scrollable->state_, Scrollable::AnimationState::IDLE);
    EXPECT_TRUE(scrollable->skipRestartSpring_);
    /**
     * @tc.steps: step2. pos gt currentPos and without callback and moved false and SnapScrollAnimationStop false.
     */
    scrollable->moved_ = false;
    scrollable->outBoundaryCallback_ = nullptr;
    scrollable->state_ = Scrollable::AnimationState::SNAP;
    scrollable->ProcessListSnapMotion(100.0);
    EXPECT_EQ(scrollable->state_, Scrollable::AnimationState::SNAP);
}

/**
 * @tc.name: ProcessScrollSnapStop001
 * @tc.desc: Test ProcessScrollSnapStop method
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableCoverTestNg, ProcessScrollSnapStop001, TestSize.Level1)
{
    auto scrollPn = scroll_->GetPattern<PartiallyMockedScrollable>();
    auto scrollable = AceType::MakeRefPtr<Scrollable>([](double, int32_t) { return true; }, scrollPn->GetAxis());
    ASSERT_NE(scrollable, nullptr);
    bool isCalled = false;
    /**
     * @tc.steps: step1. Call scrollPause_ eq true and verify executed successfully.
     */
    scrollable->scrollPause_ = true;
    scrollable->overScrollCallback_ = nullptr;
    scrollable->edgeEffect_ = EdgeEffect::FADE;
    scrollable->scrollEndCallback_ = [&isCalled]() { isCalled = true; };
    scrollable->ProcessScrollSnapStop();
    EXPECT_TRUE(isCalled);
    EXPECT_FALSE(scrollable->scrollPause_);
    /**
     * @tc.steps: step2. Call scrollPause_ eq false and isTouching_ eq true.
     */
    scrollable->moved_ = true;
    scrollable->scrollPause_ = false;
    scrollable->isTouching_ = true;
    scrollable->ProcessScrollSnapStop();
    EXPECT_TRUE(scrollable->moved_);
}

/**
 * @tc.name: UpdateScrollSnapEndWithOffsetTest001
 * @tc.desc: Test the UpdateScrollSnapEndWithOffset method
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableCoverTestNg, UpdateScrollSnapEndWithOffsetTest001, TestSize.Level1)
{
    auto scrollPn = scroll_->GetPattern<PartiallyMockedScrollable>();
    auto scrollable = AceType::MakeRefPtr<Scrollable>([](double, int32_t) { return true; }, scrollPn->GetAxis());
    ASSERT_NE(scrollable, nullptr);
    scrollable->GetSnapProperty();
    /**
     * @tc.steps: step1. Set isSnapScrollAnimationStop_ to false and snapOffsetProperty_ nullptr.
     */
    scrollable->snapOffsetProperty_ = nullptr;
    scrollable->state_ = Scrollable::AnimationState::SNAP;
    scrollable->updateSnapAnimationCount_ = 0;
    scrollable->endPos_ = 200.0;
    scrollable->finalPosition_ = 0.0f;
    scrollable->UpdateScrollSnapEndWithOffset(100.0);
    ASSERT_NE(scrollable->snapOffsetProperty_, nullptr);
    EXPECT_EQ(scrollable->endPos_, 100.0);
    EXPECT_EQ(scrollable->finalPosition_, 100.0);
    /**
     * @tc.steps: step2. Set isSnapScrollAnimationStop_ to false and snapOffsetProperty_ has value.
     */
    scrollable->updateSnapAnimationCount_ = 3;
    auto snapPropertyCallback = [](float offset) {};
    scrollable->snapOffsetProperty_ =
        AceType::MakeRefPtr<NodeAnimatablePropertyFloat>(0.0, std::move(snapPropertyCallback));
    scrollable->UpdateScrollSnapEndWithOffset(50.0);
    EXPECT_EQ(scrollable->endPos_, 50.0);
    EXPECT_EQ(scrollable->finalPosition_, 50.0);
}

/**
 * @tc.name: GetFrictionPropertyTest001
 * @tc.desc: Test the GetFrictionProperty method
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableCoverTestNg, GetFrictionPropertyTest001, TestSize.Level1)
{
    auto scrollable = AceType::MakeRefPtr<Scrollable>();
    scrollable->context_ = PipelineContext::GetCurrentContext();
    auto frictionProperty = scrollable->GetFrictionProperty();
    ASSERT_NE(frictionProperty, nullptr);
    auto propertyCallback = [](float offset) {};
    scrollable->frictionOffsetProperty_ =
        AceType::MakeRefPtr<NodeAnimatablePropertyFloat>(0.0, std::move(propertyCallback));
    /**
     * @tc.steps: step1. call callback with isFrictionAnimationStop_ true.
     */
    scrollable->state_ = Scrollable::AnimationState::IDLE;
    auto property = AceType::DynamicCast<AnimatablePropertyFloat>(frictionProperty->GetProperty());
    auto updateCallback = property->GetUpdateCallback();
    ASSERT_NE(updateCallback, nullptr);
    updateCallback(100.0f);
    /**
     * @tc.steps: step2. call callback with isFrictionAnimationStop_ false and isTouching_ true.
     */
    scrollable->state_ = Scrollable::AnimationState::FRICTION;
    scrollable->isTouching_ = true;
    updateCallback(100.0f);
    /**
     * @tc.steps: step3. call callback with isFrictionAnimationStop_ false and isTouching_ false.
     */
    scrollable->state_ = Scrollable::AnimationState::FRICTION;
    scrollable->isTouching_ = false;
    scrollable->finalPosition_ = 0.0f;
    updateCallback(100.0f);
    EXPECT_EQ(scrollable->lastPosition_, 100.0f);
    /**
     * @tc.steps: step4. call callback with NearEqual(scroll->finalPosition_, position, 1.0).
     */
    scrollable->state_ = Scrollable::AnimationState::FRICTION;
    scrollable->isTouching_ = false;
    scrollable->finalPosition_ = 100.0f;
    updateCallback(100.0f);
    EXPECT_EQ(scrollable->lastPosition_, 100.0f);
    EXPECT_EQ(scrollable->state_, Scrollable::AnimationState::IDLE);
}

/**
 * @tc.name: UpdateFadingEdgeTest001
 * @tc.desc: Test the UpdateFadingEdge method
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableCoverTestNg, UpdateFadingEdgeTest001, TestSize.Level1)
{
    auto scrollPn = scroll_->GetPattern<PartiallyMockedScrollable>();
    EXPECT_CALL(*scrollPn, GetMainContentSize()).WillRepeatedly(Return(100.0f));
    EXPECT_CALL(*scrollPn, IsAtTop()).WillRepeatedly(Return(false));
    auto overlayNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 99, AceType::MakeRefPtr<Pattern>());
    scrollPn->axis_ = Axis::VERTICAL;
    scroll_->overlayNode_ = overlayNode;
    scroll_->GetGeometryNode()->SetFrameSize(SizeF(700.0, 800.0));
    auto paintProperty = scroll_->GetPaintProperty<ScrollablePaintProperty>();
    auto paint = AceType::MakeRefPtr<GridPaintMethod>(false, false, nullptr);
    /**
     * @tc.steps: step1. call UpdateFadingEdge with UpdateFadingEdge false.
     */
    scrollPn->UpdateFadingEdge(paint);
    paintProperty->UpdateFadingEdge(false);
    EXPECT_FALSE(paint->isFadingTop_);
    /**
     * @tc.steps: step2. call UpdateFadingEdge with UpdateFadingEdge true and unit with VP.
     */
    paintProperty->UpdateFadingEdge(true);
    paintProperty->UpdateFadingEdgeLength(Dimension(1000.0f, DimensionUnit::VP));
    scrollPn->UpdateFadingEdge(paint);
    EXPECT_TRUE(paint->isFadingTop_);
    /**
     * @tc.steps: step3. call UpdateFadingEdge with UpdateFadingEdge true and unit with PERCENT.
     */
    paintProperty->UpdateFadingEdge(true);
    paintProperty->UpdateFadingEdgeLength(Dimension(1000.0f, DimensionUnit::PERCENT));
    scrollPn->UpdateFadingEdge(paint);
    EXPECT_TRUE(paint->isFadingTop_);
}

/**
 * @tc.name: CoordinateWithSheetTest001
 * @tc.desc: Test the CoordinateWithSheet method
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableCoverTestNg, CoordinateWithSheetTest001, TestSize.Level1)
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly([](ThemeType type) -> RefPtr<Theme> {
        return AceType::MakeRefPtr<SheetTheme>();
    });
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto targetNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    ViewStackProcessor::GetInstance()->Push(targetNode);
    auto stageNode = FrameNode::CreateFrameNode(
        V2::STAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<StagePattern>());
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    stageNode->MountToParent(rootNode);
    targetNode->MountToParent(stageNode);
    rootNode->MarkDirtyNode();
    auto sheetContentNode = FrameNode::GetOrCreateFrameNode(V2::COLUMN_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() {return AceType::MakeRefPtr<LinearLayoutPattern>(true);});
    auto childFrameNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    sheetContentNode->AddChild(childFrameNode);
    auto buildTitleNodeFunc = []() -> RefPtr<UINode> {
        auto frameNode =
            FrameNode::GetOrCreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
                []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
        auto childFrameNode = FrameNode::GetOrCreateFrameNode(V2::TEXT_ETS_TAG,
            ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextPattern>(); });
        frameNode->AddChild(childFrameNode);
        return frameNode;
    };
    SheetStyle sheetStyle;
    sheetStyle.sheetHeight.sheetMode = SheetMode::MEDIUM;
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    overlayManager->OpenBindSheetByUIContext(sheetContentNode, std::move(buildTitleNodeFunc), sheetStyle, nullptr,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, targetNode);
    auto sheetNode = overlayManager->modalStack_.top().Upgrade();
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    auto scrollNode = sheetPattern->GetSheetScrollNode();
    ASSERT_NE(scrollNode, nullptr);
    auto scrollPattern = scrollNode->GetPattern<ScrollPattern>();
    double offset = 100.0;
    scrollPattern->GetParentModalSheet();
    ASSERT_NE(scrollPattern->sheetPattern_, nullptr);
    auto mode = scrollPattern->CoordinateWithSheet(offset, 1, false);
    EXPECT_EQ(mode, ModalSheetCoordinationMode::SCROLLABLE_SCROLL);
    mode = scrollPattern->CoordinateWithSheet(offset, 10, false);
    scrollPattern->isSheetInReactive_ = false;
    EXPECT_EQ(mode, ModalSheetCoordinationMode::UNKNOWN);
}

/**
 * @tc.name: InitTouchEvent001
 * @tc.desc:  Test the behavior of the InitTouchEvent method Test
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableCoverTestNg, InitTouchEvent001, TestSize.Level1)
{
    auto scrollPn = scroll_->GetPattern<PartiallyMockedScrollable>();
    const std::function<bool(double, int32_t)> scrollCallback = [](double offset, int32_t source) { return true; };
    auto scrollable = AceType::MakeRefPtr<Scrollable>(scrollCallback, scrollPn->GetAxis());
    scrollable->isTouching_ = false;
    scrollPn->scrollableEvent_->scrollable_ = scrollable;
    auto gestureHub = scroll_->GetOrCreateGestureEventHub();
    TouchEventInfo touchEventInfo("default");
    TouchLocationInfo touch(0);
    touch.SetTouchType(TouchType::DOWN);
    touchEventInfo.AddTouchLocationInfo(std::move(touch));
    /**
     * @tc.steps: step1. call callback with TouchType::DOWN.
     */
    auto callback = gestureHub->touchEventActuator_->touchEvents_.front()->GetTouchEventCallback();
    callback(touchEventInfo);
    EXPECT_TRUE(scrollable->isTouching_);
    /**
     * @tc.steps: step2. call callback with TouchType::UP.
     */
    touchEventInfo.touches_.clear();
    touch.SetTouchType(TouchType::UP);
    touchEventInfo.AddTouchLocationInfo(std::move(touch));
    callback(touchEventInfo);
    EXPECT_FALSE(scrollable->isTouching_);
    /**
     * @tc.steps: step3. call callback with TouchType::CANCEL.
     */
    touchEventInfo.touches_.clear();
    scrollable->isTouching_ = true;
    touch.SetTouchType(TouchType::CANCEL);
    touchEventInfo.AddTouchLocationInfo(std::move(touch));
    callback(touchEventInfo);
    EXPECT_FALSE(scrollable->isTouching_);
}

/**
 * @tc.name: InitCurveOffsetPropertyTest001
 * @tc.desc: Test the behavior of the InitCurveOffsetPropert callback method Test
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableCoverTestNg, InitCurveOffsetPropertyTest001, TestSize.Level1)
{
    auto scrollPn = scroll_->GetPattern<PartiallyMockedScrollable>();
    scrollPn->finalPosition_ = 100.0f;
    scrollPn->lastPosition_ = 90.0f;
    scrollPn->isAnimationStop_ = false;
    scrollPn->isAnimateOverScroll_ = true;
    AceType::MakeRefPtr<CubicCurve>(0.2f, 0.0f, 0.1f, 1.0f);
    auto curve = AceType::MakeRefPtr<LinearCurve>();
    MockAnimationManager::Enable(true);
    MockAnimationManager::GetInstance().SetTicks(2);
    scrollPn->AnimateTo(100.0f, 300.0f, curve, false, true, false);
    MockAnimationManager::GetInstance().Tick();
    auto curveOffsetProperty = scrollPn->curveOffsetProperty_;
    float actualValue = curveOffsetProperty->Get();
    EXPECT_NEAR(actualValue, 100.0f, 1.0f);
    EXPECT_TRUE(scrollPn->isAnimationStop_);
}
} // namespace OHOS::Ace::NG
