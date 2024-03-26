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

#include "swiper_test_ng.h"

#include "test/mock/core/rosen/mock_canvas.h"

namespace OHOS::Ace::NG {
void SwiperTestNg::SetUpTestSuite()
{
    TestNG::SetUpTestSuite();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    auto pipeline = MockPipelineContext::GetCurrent();
    pipeline->SetThemeManager(themeManager);
    auto swiperIndicatorTheme = AceType::MakeRefPtr<SwiperIndicatorTheme>();
    swiperIndicatorTheme->color_ = Color::FromString("#182431");
    swiperIndicatorTheme->selectedColor_ = Color::FromString("#007DFF");
    swiperIndicatorTheme->size_ = Dimension(6.f);
    TextStyle textStyle;
    textStyle.SetTextColor(Color::FromString("#ff182431"));
    textStyle.SetFontSize(Dimension(14.f));
    textStyle.SetFontWeight(FontWeight::W800);
    swiperIndicatorTheme->digitalIndicatorTextStyle_ = textStyle;
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(swiperIndicatorTheme));
    MockPipelineContext::GetCurrentContext()->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
}

void SwiperTestNg::TearDownTestSuite()
{
    TestNG::TearDownTestSuite();
}

void SwiperTestNg::SetUp() {}

void SwiperTestNg::TearDown()
{
    frameNode_ = nullptr;
    pattern_ = nullptr;
    eventHub_ = nullptr;
    layoutProperty_ = nullptr;
    paintProperty_ = nullptr;
    accessibilityProperty_ = nullptr;
}

void SwiperTestNg::GetInstance()
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    frameNode_ = AceType::DynamicCast<FrameNode>(element);
    pattern_ = frameNode_->GetPattern<SwiperPattern>();
    eventHub_ = frameNode_->GetEventHub<SwiperEventHub>();
    layoutProperty_ = frameNode_->GetLayoutProperty<SwiperLayoutProperty>();
    paintProperty_ = frameNode_->GetPaintProperty<SwiperPaintProperty>();
    accessibilityProperty_ = frameNode_->GetAccessibilityProperty<SwiperAccessibilityProperty>();
    controller_ = pattern_->GetSwiperController();
}

void SwiperTestNg::Create(const std::function<void(SwiperModelNG)>& callback)
{
    SwiperModelNG model;
    model.Create();
    ViewAbstract::SetWidth(CalcLength(SWIPER_WIDTH));
    ViewAbstract::SetHeight(CalcLength(SWIPER_HEIGHT));
    if (callback) {
        callback(model);
    }
    GetInstance();
    FlushLayoutTask(frameNode_);
}

void SwiperTestNg::CreateWithItem(const std::function<void(SwiperModelNG)>& callback, int32_t itemNumber)
{
    Create([callback, itemNumber](SwiperModelNG model) {
        if (callback) {
            callback(model);
        }
        CreateItem(itemNumber);
    });
}

void SwiperTestNg::CreateItem(int32_t itemNumber)
{
    for (int32_t index = 0; index < itemNumber; index++) {
        TextModelNG model;
        model.Create("text");
        ViewStackProcessor::GetInstance()->Pop();
    }
}

/**
 * @tc.name: SwiperEvent001
 * @tc.desc: HandleTouchDown
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperEvent001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    TouchLocationInfo touchLocationInfo("down", 0);
    touchLocationInfo.SetTouchType(TouchType::DOWN);
    std::list<TouchLocationInfo> infoSwiper;
    infoSwiper.emplace_back(touchLocationInfo);
    TouchEventInfo touchEventInfo("down");
    touchEventInfo.touches_ = infoSwiper;
    pattern_->HandleTouchEvent(touchEventInfo);
    EXPECT_FALSE(pattern_->indicatorDoingAnimation_);
    const char* name = "HandleTouchDown";
    pattern_->controller_ = CREATE_ANIMATOR(name);
    pattern_->controller_->status_ = Animator::Status::RUNNING;
    pattern_->HandleTouchEvent(touchEventInfo);
    EXPECT_FALSE(pattern_->indicatorDoingAnimation_);

    touchEventInfo.touches_.begin()->SetTouchType(TouchType::UP);
    pattern_->HandleTouchEvent(touchEventInfo);
    pattern_->controller_ = nullptr;
    touchEventInfo.touches_.begin()->SetTouchType(TouchType::CANCEL);
    pattern_->HandleTouchEvent(touchEventInfo);
    touchEventInfo.touches_.begin()->SetTouchType(TouchType::MOVE);
    touchLocationInfo.SetTouchType(TouchType::CANCEL);
    pattern_->HandleTouchEvent(touchEventInfo);
    EXPECT_FALSE(pattern_->indicatorDoingAnimation_);
}

/**
 * @tc.name: SwiperEvent002
 * @tc.desc: HandleTouchDown
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperEvent002, TestSize.Level1)
{
    EXPECT_CALL(*MockPipelineContext::pipeline_, FlushUITasks).Times(8);
    CreateWithItem([](SwiperModelNG model) {});
    auto gestureEventHub = AceType::MakeRefPtr<GestureEventHub>(AceType::WeakClaim(AceType::RawPtr(eventHub_)));

    auto pipeline = MockPipelineContext::GetCurrent();
    pipeline->restoreNodeInfo_.emplace(std::make_pair(1, "testFlushUITasks"));
    pattern_->InitPanEvent(gestureEventHub);
    EXPECT_EQ(pattern_->direction_, Axis::HORIZONTAL);
    pattern_->touchEvent_ = nullptr;
    pattern_->InitTouchEvent(gestureEventHub);
    TouchEventFunc callback = [](TouchEventInfo& info) {};
    pattern_->touchEvent_ = AceType::MakeRefPtr<TouchEventImpl>(std::move(callback));
    pattern_->InitTouchEvent(gestureEventHub);
    EXPECT_TRUE(pattern_->touchEvent_);
    EXPECT_TRUE(pattern_->panEvent_);

    GestureEvent gestureEvent = GestureEvent();
    gestureEvent.inputEventType_ = InputEventType::AXIS;
    pattern_->panEvent_->actionStart_(gestureEvent);
    pattern_->panEvent_->actionUpdate_(gestureEvent);
    pattern_->panEvent_->actionEnd_(gestureEvent);
    gestureEvent.inputEventType_ = InputEventType::TOUCH_SCREEN;
    CommonFunc func = []() {};
    pattern_->swiperController_->SetTabBarFinishCallback(func);
    pattern_->panEvent_->actionStart_(gestureEvent);
    pattern_->panEvent_->actionEnd_(gestureEvent);
    pattern_->swiperController_->SetRemoveSwiperEventCallback(func);
    pattern_->panEvent_->actionStart_(gestureEvent);
    pattern_->panEvent_->actionEnd_(gestureEvent);
    pattern_->panEvent_->actionCancel_();
    EXPECT_TRUE(pattern_->swiperController_->tabBarFinishCallback_);
    EXPECT_TRUE(pattern_->swiperController_->removeSwiperEventCallback_);
}

/**
 * @tc.name: SwiperPatternSpringAnimation001
 * @tc.desc: Swiper spring animation is playing
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternSpringAnimation001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    double dragVelocity = 2000.0;
    pattern_->springAnimation_ = nullptr;
    pattern_->currentOffset_ = 1;
    pattern_->contentMainSize_ = 1.0f;
    struct SwiperItemInfo swiperItemInfo;
    swiperItemInfo.startPos = -1.0f;
    swiperItemInfo.endPos = -1.0f;
    pattern_->itemPosition_.emplace(std::make_pair(1, swiperItemInfo));
    pattern_->PlaySpringAnimation(dragVelocity);
    EXPECT_FALSE(pattern_->springAnimationIsRunning_);
}

/**
 * @tc.name: SwiperPatternSpringAnimation002
 * @tc.desc: StopAndResetSpringAnimation
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternSpringAnimation002, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    double dragVelocity = 2000.0;
    pattern_->springAnimation_ = nullptr;
    pattern_->currentOffset_ = 1;
    pattern_->contentMainSize_ = 1.0f;
    struct SwiperItemInfo swiperItemInfo;
    swiperItemInfo.startPos = -1.0f;
    swiperItemInfo.endPos = -1.0f;
    pattern_->itemPosition_.emplace(std::make_pair(1, swiperItemInfo));
    pattern_->PlaySpringAnimation(dragVelocity);
    pattern_->StopAndResetSpringAnimation();
    EXPECT_FALSE(pattern_->springAnimationIsRunning_);
}

/**
 * @tc.name: SwiperPatternSpringAnimation003
 * @tc.desc: StopSpringAnimationAndFlushImmediately
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternSpringAnimation003, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    double dragVelocity = 2000.0;
    pattern_->springAnimation_ = nullptr;
    pattern_->currentOffset_ = 1;
    pattern_->contentMainSize_ = 1.0f;
    struct SwiperItemInfo swiperItemInfo;
    swiperItemInfo.startPos = -1.0f;
    swiperItemInfo.endPos = -1.0f;
    pattern_->itemPosition_.emplace(std::make_pair(1, swiperItemInfo));
    pattern_->PlaySpringAnimation(dragVelocity);
    pattern_->StopSpringAnimationAndFlushImmediately();
    EXPECT_FALSE(pattern_->springAnimationIsRunning_);
}

/**
 * @tc.name: SwiperPatternSpringAnimation004
 * @tc.desc: StopSpringAnimation
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternSpringAnimation004, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    double dragVelocity = 2000.0;
    pattern_->springAnimation_ = nullptr;
    pattern_->currentOffset_ = 1;
    pattern_->contentMainSize_ = 1.0f;
    struct SwiperItemInfo swiperItemInfo;
    swiperItemInfo.startPos = -1.0f;
    swiperItemInfo.endPos = -1.0f;
    pattern_->itemPosition_.emplace(std::make_pair(1, swiperItemInfo));
    pattern_->PlaySpringAnimation(dragVelocity);
    pattern_->StopSpringAnimation();
    EXPECT_FALSE(pattern_->springAnimationIsRunning_);
}

/**
 * @tc.name: SwiperPatternSpringAnimation005
 * @tc.desc: Swiper spring animation is playing, handle touch down to break playing animation,
 *           and handle touch up to continue playing animation
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternSpringAnimation005, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    double dragVelocity = 2000.0;
    pattern_->springAnimation_ = nullptr;
    pattern_->currentOffset_ = 1;
    pattern_->contentMainSize_ = 1.0f;
    struct SwiperItemInfo swiperItemInfo;
    swiperItemInfo.startPos = -1.0f;
    swiperItemInfo.endPos = -1.0f;
    pattern_->itemPosition_.emplace(std::make_pair(1, swiperItemInfo));
    pattern_->PlaySpringAnimation(dragVelocity);

    TouchLocationInfo touchLocationInfo("down", 0);
    touchLocationInfo.SetTouchType(TouchType::DOWN);
    pattern_->HandleTouchDown(touchLocationInfo);
    EXPECT_FALSE(pattern_->springAnimationIsRunning_);
}

/**
 * @tc.name: SwiperUtilsTest001
 * @tc.desc: Test Swiper measure and layout function, set prevMargin and nextMargin property is 50_px.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperUtilsTest001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    LayoutConstraintF layoutConstraint;
    layoutConstraint.Reset();
    layoutConstraint.selfIdealSize = OptionalSize(SizeF(720.f, 1200.f));
    layoutProperty_->UpdateLayoutConstraint(layoutConstraint);
    layoutProperty_->UpdateContentConstraint();
    int32_t displaycount = 3;
    layoutProperty_->UpdateItemSpace(Dimension(20));
    layoutProperty_->UpdateCachedCount(1);
    layoutProperty_->UpdateDirection(Axis::HORIZONTAL);
    layoutProperty_->UpdateDisplayCount(displaycount);
    layoutProperty_->UpdatePrevMargin(Dimension(50));
    layoutProperty_->UpdateNextMargin(Dimension(50));
    layoutProperty_->UpdateShowIndicator(false);
    layoutProperty_->UpdateLoop(false);
    auto swiperLayoutAlgorithm = AceType::DynamicCast<SwiperLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    swiperLayoutAlgorithm->currentIndex_ = 1;
    for (int32_t index = 0; index < 4; index++) {
        auto childLayout = frameNode_->GetOrCreateChildByIndex(index);
        ASSERT_NE(childLayout, nullptr);
    }
}

/**
 * @tc.name: SwiperUtilsTest002
 * @tc.desc: Verify the CreateChildConstraint function when DisplayCount is -1.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperUtilsTest002, TestSize.Level2)
{
    CreateWithItem([](SwiperModelNG model) {});
    layoutProperty_->UpdateDisplayCount(-1);
    auto getAutoFill = pattern_->IsAutoFill();
    EXPECT_FALSE(getAutoFill);

    OptionalSizeF setSize = OptionalSize(SizeF(720.f, 1200.f));
    auto result = SwiperUtils::CreateChildConstraint(layoutProperty_, setSize, getAutoFill);
    EXPECT_EQ(result.parentIdealSize, setSize);
}

/**
 * @tc.name: SwiperUtilsTest003
 * @tc.desc: Verify the CreateChildConstraint function when DisplayMode is AUTO_LINEAR.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperUtilsTest003, TestSize.Level2)
{
    CreateWithItem([](SwiperModelNG model) { model.SetDisplayMode(SwiperDisplayMode::AUTO_LINEAR); });
    auto getAutoFill = pattern_->IsAutoFill();
    EXPECT_FALSE(getAutoFill);
    OptionalSizeF setSize = OptionalSize(SizeF(720.f, 1200.f));
    auto result = SwiperUtils::CreateChildConstraint(layoutProperty_, setSize, getAutoFill);
    EXPECT_EQ(result.parentIdealSize, setSize);
}

/**
 * @tc.name: SwiperUtilsTest004
 * @tc.desc: Verify the CreateChildConstraint function when NextMargin is normal and abnormal.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperUtilsTest004, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    auto getAutoFill = pattern_->IsAutoFill();
    EXPECT_FALSE(getAutoFill);
    layoutProperty_->UpdateIndex(1);
    layoutProperty_->UpdateItemSpace(Dimension(20));
    layoutProperty_->UpdateCachedCount(1);
    layoutProperty_->UpdateDirection(Axis::HORIZONTAL);
    layoutProperty_->UpdateDisplayCount(3);
    layoutProperty_->UpdatePrevMargin(Dimension(50));
    layoutProperty_->UpdateNextMargin(Dimension(50));

    OptionalSizeF setSize = OptionalSize(SizeF(720.f, 1200.f));
    auto result = SwiperUtils::CreateChildConstraint(layoutProperty_, setSize, getAutoFill);
    EXPECT_EQ(result.parentIdealSize, setSize);

    layoutProperty_->UpdateNextMargin(Dimension(600));
    result = SwiperUtils::CreateChildConstraint(layoutProperty_, setSize, getAutoFill);
    EXPECT_EQ(result.parentIdealSize, setSize);
}

/**
 * @tc.name: SwiperUtilsTest005
 * @tc.desc: Verify the CreateChildConstraint function does not set a value for setSize.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperUtilsTest005, TestSize.Level2)
{
    CreateWithItem([](SwiperModelNG model) {});
    layoutProperty_->UpdateIndex(1);
    layoutProperty_->UpdateItemSpace(Dimension(20));
    layoutProperty_->UpdateCachedCount(1);
    layoutProperty_->UpdateDirection(Axis::HORIZONTAL);
    layoutProperty_->UpdateDisplayCount(3);
    layoutProperty_->UpdatePrevMargin(Dimension(50));
    layoutProperty_->UpdateNextMargin(Dimension(50));
    auto getAutoFill = pattern_->IsAutoFill();
    EXPECT_FALSE(getAutoFill);

    OptionalSizeF setSize;
    auto result = SwiperUtils::CreateChildConstraint(layoutProperty_, setSize, getAutoFill);
    EXPECT_EQ(result.parentIdealSize, setSize);
}

/**
 * @tc.name: SwiperUtilsTest006
 * @tc.desc: Verify the CreateChildConstraint function when Direction is VERTICAL.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperUtilsTest006, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    auto getAutoFill = pattern_->IsAutoFill();
    EXPECT_FALSE(getAutoFill);
    layoutProperty_->UpdateIndex(1);
    layoutProperty_->UpdateItemSpace(Dimension(20));
    layoutProperty_->UpdateCachedCount(1);
    layoutProperty_->UpdateDirection(Axis::VERTICAL);
    layoutProperty_->UpdateDisplayCount(3);
    layoutProperty_->UpdatePrevMargin(Dimension(50));
    layoutProperty_->UpdateNextMargin(Dimension(50));

    OptionalSizeF setSize = OptionalSize(SizeF(720.f, 1200.f));
    auto result = SwiperUtils::CreateChildConstraint(layoutProperty_, setSize, getAutoFill);
    EXPECT_EQ(result.parentIdealSize, setSize);

    layoutProperty_->UpdateNextMargin(Dimension(600));
    result = SwiperUtils::CreateChildConstraint(layoutProperty_, setSize, getAutoFill);
    EXPECT_EQ(result.parentIdealSize, setSize);
}

/**
 * @tc.name: SwiperUtilsTest007
 * @tc.desc: Verify the CreateChildConstraint function when Direction is VERTICAL and does not set value for setSize.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperUtilsTest007, TestSize.Level2)
{
    CreateWithItem([](SwiperModelNG model) {});
    layoutProperty_->UpdateIndex(1);
    layoutProperty_->UpdateItemSpace(Dimension(20));
    layoutProperty_->UpdateCachedCount(1);
    layoutProperty_->UpdateDirection(Axis::VERTICAL);
    layoutProperty_->UpdateDisplayCount(3);
    layoutProperty_->UpdatePrevMargin(Dimension(50));
    layoutProperty_->UpdateNextMargin(Dimension(50));
    auto getAutoFill = pattern_->IsAutoFill();
    EXPECT_FALSE(getAutoFill);

    OptionalSizeF setSize;
    auto result = SwiperUtils::CreateChildConstraint(layoutProperty_, setSize, getAutoFill);
    EXPECT_EQ(result.parentIdealSize, setSize);
}

/**
 * @tc.name: SwiperUtilsTest008
 * @tc.desc: Verify the CreateChildConstraint function when Direction is FREE.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperUtilsTest008, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    layoutProperty_->UpdateIndex(1);
    layoutProperty_->UpdateItemSpace(Dimension(20));
    layoutProperty_->UpdateCachedCount(1);
    layoutProperty_->UpdateDirection(Axis::FREE);
    layoutProperty_->UpdateDisplayCount(3);
    layoutProperty_->UpdatePrevMargin(Dimension(50));
    layoutProperty_->UpdateNextMargin(Dimension(50));
    auto getAutoFill = pattern_->IsAutoFill();
    EXPECT_FALSE(getAutoFill);

    OptionalSizeF setSize = OptionalSize(SizeF(720.f, 1200.f));
    auto result = SwiperUtils::CreateChildConstraint(layoutProperty_, setSize, getAutoFill);
    EXPECT_EQ(result.parentIdealSize, setSize);
}

/**
 * @tc.name: SwiperInit001
 * @tc.desc: InitIndicator
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperInit001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    EXPECT_EQ(frameNode_->children_.size(), 5);
}

/**
 * @tc.name: SwiperInit002
 * @tc.desc: InitOnKeyEvent
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperInit002, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    RefPtr<FocusHub> focusHub = AceType::MakeRefPtr<FocusHub>(eventHub_, FocusType::DISABLE, false);
    pattern_->InitOnKeyEvent(focusHub);
    KeyEvent event = KeyEvent();
    event.action = KeyAction::DOWN;
    EXPECT_FALSE(focusHub->ProcessOnKeyEventInternal(event));
}

/**
 * @tc.name: SwiperFunc001
 * @tc.desc: OnKeyEvent
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperFunc001, TestSize.Level1)
{
    EXPECT_CALL(*MockPipelineContext::pipeline_, FlushUITasks).Times(2);
    CreateWithItem([](SwiperModelNG model) {});
    KeyEvent event = KeyEvent();
    event.action = KeyAction::CLICK;
    EXPECT_FALSE(pattern_->OnKeyEvent(event));
    event.action = KeyAction::DOWN;
    EXPECT_FALSE(pattern_->OnKeyEvent(event));
    event.code = KeyCode::KEY_DPAD_LEFT;
    EXPECT_TRUE(pattern_->OnKeyEvent(event));
    event.code = KeyCode::KEY_DPAD_RIGHT;
    EXPECT_TRUE(pattern_->OnKeyEvent(event));
}

/**
 * @tc.name: SwiperFunc002
 * @tc.desc: OnVisibleChange
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperFunc002, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    bool isVisible = false;
    pattern_->OnVisibleChange(isVisible);
    pattern_->isInit_ = false;
    pattern_->OnWindowHide();
    pattern_->OnVisibleChange(isVisible);
    EXPECT_FALSE(pattern_->isVisible_);
    isVisible = true;
    pattern_->OnWindowShow();
    pattern_->OnVisibleChange(isVisible);
    EXPECT_TRUE(pattern_->isVisible_);
    pattern_->isVisibleArea_ = true;
    pattern_->OnWindowShow();
}

/**
 * @tc.name: SwiperFunc003
 * @tc.desc: OnIndexChange
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperFunc003, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    EXPECT_EQ(pattern_->TotalCount(), 4);
}

/**
 * @tc.name: SwiperFunc004
 * @tc.desc: HandleDragUpdate
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperFunc004, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    struct SwiperItemInfo swiperItemInfo1;
    swiperItemInfo1.startPos = -1.0f;
    swiperItemInfo1.endPos = -1.0f;
    pattern_->itemPosition_.emplace(std::make_pair(1, swiperItemInfo1));

    frameNode_->geometryNode_->frame_.SetOffset(OffsetF(0, 0));
    GestureEvent gestureEvent = GestureEvent();
    gestureEvent.SetMainDelta(20.0);
    gestureEvent.SetLocalLocation(Offset(0, 0));
    gestureEvent.inputEventType_ = InputEventType::TOUCH_SCREEN;
    pattern_->panEvent_->actionUpdate_(gestureEvent);
    EXPECT_EQ(pattern_->currentOffset_, 0.0);

    layoutProperty_->propLoop_ = false;
    frameNode_->geometryNode_->frame_.SetSize(SizeF(10.f, 10.f));
    EXPECT_TRUE(pattern_->IsOutOfBoundary(20.0));
    // Swiper has reached boundary.
    frameNode_->geometryNode_->frame_.SetSize(SizeF(0, 0));
    pattern_->panEvent_->actionUpdate_(gestureEvent);
    pattern_->currentOffset_ = 20.0;
    paintProperty_->propEdgeEffect_ = EdgeEffect::FADE;
    pattern_->panEvent_->actionUpdate_(gestureEvent);
    pattern_->currentOffset_ = 20.0;
    paintProperty_->propEdgeEffect_ = EdgeEffect::NONE;
    pattern_->panEvent_->actionUpdate_(gestureEvent);
}

/**
 * @tc.name: SwiperModelNg001
 * @tc.desc: Swiper Model NG.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperModelNg001, TestSize.Level1)
{
    SwiperModelNG model;
    model.Create();
    ViewAbstract::SetWidth(CalcLength(SWIPER_WIDTH));
    ViewAbstract::SetHeight(CalcLength(SWIPER_HEIGHT));
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto pattern = frameNode->GetPattern<SwiperPattern>();
    auto layoutProperty = frameNode->GetLayoutProperty<SwiperLayoutProperty>();
    auto paintProperty = frameNode->GetPaintProperty<SwiperPaintProperty>();

    /**
     * @tc.steps: step3.1. Test SetIndex function.
     * @tc.expected: layoutProperty->GetIndex() is equal to 1.
     */
    model.SetIndex(1);
    EXPECT_EQ(layoutProperty->GetIndex(), 1);

    /**
     * @tc.steps: step3.2. Test SetDisplayMode function.
     * @tc.expected: layoutProperty->GetDisplayMode() is equal to swiperDisplayMode.
     */
    model.SetDisplayMode(SwiperDisplayMode::STRETCH);
    EXPECT_EQ(layoutProperty->GetDisplayMode(), SwiperDisplayMode::STRETCH);

    /**
     * @tc.steps: step3.3. Test SetShowIndicator function.
     * @tc.expected: layoutProperty->GetIndex() is equal to 1.
     */
    model.SetShowIndicator(true);
    EXPECT_TRUE(layoutProperty->GetShowIndicator());

    /**
     * @tc.steps: step3.4. Test SetItemSpace function.
     * @tc.expected: layoutProperty->GetItemSpace() is equal to dimension.
     */
    auto dimension = Dimension(-1.0);
    model.SetItemSpace(dimension);
    EXPECT_EQ(layoutProperty->GetItemSpace(), dimension);

    /**
     * @tc.steps: step3.5. Test SetCachedCount function.
     * @tc.expected:DisplayCount = -1 layoutProperty->SetCachedCount() is equal to 1.
     * @tc.expected:DisplayCount = 1 layoutProperty->SetCachedCount() is equal to 1.
     */
    model.SetCachedCount(-1);
    model.SetCachedCount(1);
    EXPECT_EQ(layoutProperty->GetCachedCount(), 1);

    /**
     * @tc.steps: step3.6. Test SetIsIndicatorCustomSize function.
     * @tc.expected: pattern->IsIndicatorCustomSize() is equal to true.
     */
    model.SetIsIndicatorCustomSize(true);
    EXPECT_TRUE(pattern->IsIndicatorCustomSize());

    /**
     * @tc.steps: step3.7. Test SetAutoPlay function.
     * @tc.expected: SwiperPaintProperty->GetAutoPlay() is equal to true.
     */
    model.SetAutoPlay(true);
    EXPECT_TRUE(paintProperty->GetAutoPlay());

    /**
     * @tc.steps: step3.8. Test SetAutoPlayInterval function.
     * @tc.expected: SwiperPaintProperty->GetAutoPlayInterval() is equal to 1.
     */
    model.SetAutoPlayInterval(1);
    EXPECT_EQ(paintProperty->GetAutoPlayInterval(), 1);

    /**
     * @tc.steps: step3.9. Test SetDuration function.
     * @tc.expected: SwiperPaintProperty->GetDuration() is equal to 1.
     */
    model.SetDuration(1);
    EXPECT_EQ(paintProperty->GetDuration(), 1);
}

/**
 * @tc.name: SwiperModelNg002
 * @tc.desc: Swiper Model NG.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperModelNg002, TestSize.Level1)
{
    SwiperModelNG model;
    model.Create();
    ViewAbstract::SetWidth(CalcLength(SWIPER_WIDTH));
    ViewAbstract::SetHeight(CalcLength(SWIPER_HEIGHT));
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto pattern = frameNode->GetPattern<SwiperPattern>();
    auto layoutProperty = frameNode->GetLayoutProperty<SwiperLayoutProperty>();
    auto paintProperty = frameNode->GetPaintProperty<SwiperPaintProperty>();
    auto eventHub = frameNode->GetEventHub<SwiperEventHub>();

    /**
     * @tc.steps: step3.1. Test SetLoop function.
     * @tc.expected: SwiperPaintProperty->GetLoop() is true.
     */
    model.SetLoop(true);
    EXPECT_TRUE(layoutProperty->GetLoop());

    /**
     * @tc.steps: step3.2. Test SetEnabled function.
     * @tc.expected: SwiperPaintProperty->GetEnabled() is true.
     */
    model.SetEnabled(true);
    EXPECT_TRUE(paintProperty->GetEnabled());

    /**
     * @tc.steps: step3.3. Test SetDisableSwipe function.
     * @tc.expected: layoutProperty->GetDisableSwipe() is true.
     */
    model.SetDisableSwipe(true);
    EXPECT_TRUE(layoutProperty->GetDisableSwipe());

    /**
     * @tc.steps: step3.4. Test SetEdgeEffect function.
     * @tc.expected: SwiperPaintProperty->GetEdgeEffect() is true.
     */
    model.SetEdgeEffect(EdgeEffect::FADE);
    EXPECT_EQ(paintProperty->GetEdgeEffect(), EdgeEffect::FADE);

    /**
     * @tc.steps: step3.5. Test SetOnChange function.
     * @tc.expected:pattern->changeEvent_ not null.
     */
    auto onChange = [](const BaseEventInfo* info) {};
    model.SetOnChange(std::move(onChange));
    EXPECT_NE(pattern->changeEvent_, nullptr);

    /**
     * @tc.steps: step3.6. Test SetOnAnimationStart function.
     * @tc.expected:pattern->animationStartEvent_ not null.
     */
    auto onAnimationStart = [](int32_t index, int32_t targetIndex, const AnimationCallbackInfo& info) {};
    model.SetOnAnimationStart(std::move(onAnimationStart));
    EXPECT_NE(pattern->animationStartEvent_, nullptr);

    /**
     * @tc.steps: step3.7. Test SetOnAnimationEnd function.
     * @tc.expected:pattern->animationEndEvent_ not null.
     */
    auto onAnimationEnd = [](int32_t index, const AnimationCallbackInfo& info) {};
    model.SetOnAnimationEnd(std::move(onAnimationEnd));
    EXPECT_NE(pattern->animationEndEvent_, nullptr);
}

/**
 * @tc.name: SwiperModelNg003
 * @tc.desc: Swiper Model NG.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperModelNg003, TestSize.Level1)
{
    SwiperModelNG model;
    model.Create();
    ViewAbstract::SetWidth(CalcLength(SWIPER_WIDTH));
    ViewAbstract::SetHeight(CalcLength(SWIPER_HEIGHT));
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto pattern = frameNode->GetPattern<SwiperPattern>();
    auto layoutProperty = frameNode->GetLayoutProperty<SwiperLayoutProperty>();
    auto paintProperty = frameNode->GetPaintProperty<SwiperPaintProperty>();

    /**
     * @tc.steps: step3.1. Test SetIndicatorStyle function.
     * @tc.expected: SwiperPaintProperty->swiperParameters_->colorVal is swiperParameters.colorVal.
     */
    SwiperParameters swiperParameters;
    swiperParameters.colorVal = Color(Color::BLUE);
    model.SetIndicatorStyle(swiperParameters);
    EXPECT_EQ(pattern->swiperParameters_->colorVal, swiperParameters.colorVal);

    /**
     * @tc.steps: step3.2. Test SetPreviousMargin function.
     * @tc.expected: paintProperty->GetPrevMargin() is equal to dimension.
     */
    auto dimension = Dimension(-1.0);
    model.SetPreviousMargin(dimension);
    EXPECT_EQ(layoutProperty->GetPrevMargin(), dimension);

    /**
     * @tc.steps: step3.3. Test SetNextMargin function.
     * @tc.expected: paintProperty->GetNextMargin() is equal to dimension.
     */
    model.SetNextMargin(dimension);
    EXPECT_EQ(layoutProperty->GetNextMargin(), dimension);

    /**
     * @tc.steps: step3.4. Test SetOnChangeEvent function.
     * @tc.expected: pattern->onIndexChangeEvent_ is not null.
     */
    auto onChangeEvent = [](const BaseEventInfo* info) {};
    model.SetOnChangeEvent(std::move(onChangeEvent));
    EXPECT_NE(pattern->onIndexChangeEvent_, nullptr);

    /**
     * @tc.steps: step3.5. Test SetIndicatorIsBoolean function.
     * @tc.expected: pattern->indicatorIsBoolean_ is true.
     */
    model.SetIndicatorIsBoolean(true);
    EXPECT_TRUE(pattern->indicatorIsBoolean_);

    /**
     * @tc.steps: step3.6. Test SetArrowStyle function.
     * @tc.expected: before set swiperArrowParameters, all result is null.
     */
    SwiperArrowParameters swiperArrowParameters;
    model.SetArrowStyle(swiperArrowParameters);

    /**
     * @tc.steps: step3.7. Test SetArrowStyle function.
     * @tc.expected: after set swiperArrowParameters, layoutProperty->IsShowBoard is true.
     */
    swiperArrowParameters.isShowBackground = true;
    swiperArrowParameters.backgroundSize = dimension;
    swiperArrowParameters.backgroundColor = Color(Color::BLUE);
    swiperArrowParameters.arrowSize = dimension;
    swiperArrowParameters.arrowColor = Color(Color::RED);
    swiperArrowParameters.isSidebarMiddle = true;
    model.SetArrowStyle(swiperArrowParameters);
    EXPECT_TRUE(layoutProperty->GetIsShowBackground());
    EXPECT_EQ(layoutProperty->GetBackgroundSize(), dimension);
    EXPECT_EQ(layoutProperty->GetBackgroundColor(), Color(Color::BLUE));
    EXPECT_EQ(layoutProperty->GetArrowSize(), dimension);
    EXPECT_EQ(layoutProperty->GetArrowColor(), Color(Color::RED));
    EXPECT_TRUE(layoutProperty->GetIsSidebarMiddle());

    /**
     * @tc.steps: step3.8. Test SetDisplayArrow function.
     * @tc.expected: layoutProperty->GetDisplayArrow() is true.
     */
    model.SetDisplayArrow(true);
    EXPECT_TRUE(layoutProperty->GetDisplayArrow());

    /**
     * @tc.steps: step3.9. Test SetHoverShow function.
     * @tc.expected: layoutProperty->GetHoverShow() is true.
     */
    model.SetHoverShow(true);
    EXPECT_TRUE(layoutProperty->GetHoverShow());
}

/**
 * @tc.name: SwiperPaintProperty001
 * @tc.desc: Swiper Paint Property.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPaintProperty001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});

    /**
     * @tc.steps: step1. Test ToJsonValue function.
     * @tc.expected: Check the swiper property value
     */
    auto json = JsonUtil::Create(true);
    paintProperty_->ToJsonValue(json);
    EXPECT_EQ(json->GetString("autoPlay"), "false");

    /**
     * @tc.steps: step2. call UpdateCalcLayoutProperty, push constraint is null.
     * @tc.expected: Return expected results.
     */
    MeasureProperty constraint;
    layoutProperty_->UpdateCalcLayoutProperty(std::move(constraint));
    EXPECT_EQ(layoutProperty_->propertyChangeFlag_, 1);

    /**
     * @tc.steps: step3. Test FromJson function.
     * @tc.expected: Check the swiper property value
     */
    auto jsonFrom = JsonUtil::Create(true);
    paintProperty_->FromJson(jsonFrom);
    EXPECT_TRUE(jsonFrom);
}

/**
 * @tc.name: SwiperPattern001
 * @tc.desc: Swiper Paint Property.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPattern001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});

    /**
     * @tc.steps: step1. Test DumpAdvanceInfo function.
     * @tc.expected: SwiperIndicatorType::DOT.
     */
    pattern_->lastSwiperIndicatorType_ = SwiperIndicatorType::DOT;
    pattern_->DumpAdvanceInfo();
    EXPECT_EQ(pattern_->lastSwiperIndicatorType_, SwiperIndicatorType::DOT);

    /**
     * @tc.steps: step2. Test DumpAdvanceInfo function.
     * @tc.expected: SwiperIndicatorType::DIGIT.
     */
    pattern_->lastSwiperIndicatorType_ = SwiperIndicatorType::DIGIT;
    pattern_->DumpAdvanceInfo();
    EXPECT_EQ(pattern_->lastSwiperIndicatorType_, SwiperIndicatorType::DIGIT);

    /**
     * @tc.steps: step3. Test DumpAdvanceInfo function.
     * @tc.expected: PanDirection::NONE.
     */
    pattern_->panDirection_.type = PanDirection::NONE;
    pattern_->DumpAdvanceInfo();
    EXPECT_EQ(pattern_->panDirection_.type, PanDirection::NONE);

    pattern_->panDirection_.type = PanDirection::LEFT;
    pattern_->DumpAdvanceInfo();
    EXPECT_EQ(pattern_->panDirection_.type, PanDirection::LEFT);

    pattern_->panDirection_.type = PanDirection::RIGHT;
    pattern_->DumpAdvanceInfo();
    EXPECT_EQ(pattern_->panDirection_.type, PanDirection::RIGHT);

    pattern_->panDirection_.type = PanDirection::HORIZONTAL;
    pattern_->DumpAdvanceInfo();
    EXPECT_EQ(pattern_->panDirection_.type, PanDirection::HORIZONTAL);

    pattern_->panDirection_.type = PanDirection::UP;
    pattern_->DumpAdvanceInfo();
    EXPECT_EQ(pattern_->panDirection_.type, PanDirection::UP);

    pattern_->panDirection_.type = PanDirection::DOWN;
    pattern_->DumpAdvanceInfo();
    EXPECT_EQ(pattern_->panDirection_.type, PanDirection::DOWN);

    pattern_->panDirection_.type = PanDirection::VERTICAL;
    pattern_->DumpAdvanceInfo();
    EXPECT_EQ(pattern_->panDirection_.type, PanDirection::VERTICAL);

    pattern_->panDirection_.type = PanDirection::ALL;
    pattern_->DumpAdvanceInfo();
    EXPECT_EQ(pattern_->panDirection_.type, PanDirection::ALL);
}

/**
 * @tc.name: SwiperPattern002
 * @tc.desc: Swiper Paint Property.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPattern002, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});

    pattern_->direction_ = Axis::NONE;
    pattern_->DumpAdvanceInfo();
    EXPECT_EQ(pattern_->direction_, Axis::NONE);

    pattern_->direction_ = Axis::HORIZONTAL;
    pattern_->DumpAdvanceInfo();
    EXPECT_EQ(pattern_->direction_, Axis::HORIZONTAL);

    pattern_->direction_ = Axis::FREE;
    pattern_->DumpAdvanceInfo();
    EXPECT_EQ(pattern_->direction_, Axis::FREE);

    pattern_->direction_ = Axis::VERTICAL;
    pattern_->DumpAdvanceInfo();
    ASSERT_EQ(pattern_->direction_, Axis::VERTICAL);
}

/**
 * @tc.name: SwiperFlushFocus001
 * @tc.desc: Swiper FlushFocus.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperFlushFocus001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});

    /**
     * @tc.steps: step2. Create curShowFrameNode, addChild to frameNode.
     */
    auto curShowFrame = AceType::MakeRefPtr<FrameNode>(V2::ROW_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    auto child = AceType::MakeRefPtr<FrameNode>(V2::BUTTON_ETS_TAG, -1, AceType::MakeRefPtr<SwiperPattern>());
    auto child2 = AceType::MakeRefPtr<FrameNode>(V2::BUTTON_ETS_TAG, -1, AceType::MakeRefPtr<SwiperPattern>());
    child->GetOrCreateFocusHub();
    child2->GetOrCreateFocusHub();
    curShowFrame->AddChild(child);
    frameNode_->AddChild(child2);

    eventHub_->AttachHost(frameNode_);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(eventHub_);

    /**
     * @tc.steps: step3. test FlushFocus with IsShowIndicator() is false.
     * @tc.expected: curShowFrame->GetFirstFocusHubChild()->lastWeakFocusNode_ is not null.
     */
    layoutProperty_->UpdateShowIndicator(false);
    pattern_->isLastIndicatorFocused_ = true;
    EXPECT_FALSE(pattern_->IsShowIndicator());
    pattern_->FlushFocus(curShowFrame);
    EXPECT_FALSE(curShowFrame->GetFirstFocusHubChild()->currentFocus_);
    pattern_->isLastIndicatorFocused_ = false;
    pattern_->FlushFocus(curShowFrame);
    EXPECT_EQ(pattern_->lastWeakShowNode_, AceType::WeakClaim(AceType::RawPtr(curShowFrame)));

    /**
     * @tc.steps: step4. test FlushFocus with IsShowIndicator() is true and hasLeftButton and hasRightButton.
     * @tc.expected: curShowFrame->GetFirstFocusHubChild()->currentFocus_ is false.
     */
    layoutProperty_->UpdateShowIndicator(true);
    pattern_->GetLeftButtonId();
    pattern_->GetRightButtonId();
    EXPECT_TRUE(layoutProperty_->GetShowIndicatorValue(true));
    EXPECT_TRUE(pattern_->IsShowIndicator());
    focusHub->currentFocus_ = true;
    pattern_->FlushFocus(curShowFrame);
    EXPECT_FALSE(curShowFrame->GetFirstFocusHubChild()->currentFocus_);
    pattern_->isLastIndicatorFocused_ = false;
    pattern_->FlushFocus(curShowFrame);
}

/**
 * @tc.name: SwiperIndicatorLayoutAlgorithmMeasure001
 * @tc.desc: Test for measure method of SwiperIndicatorLayoutAlgorithm.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperIndicatorLayoutAlgorithmMeasure001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    auto indicatorNode = GetChildFrameNode(frameNode_, 4);
    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    RefPtr<NodePaintMethod> nodePaintMethod = indicatorPattern->CreateNodePaintMethod();
    auto algorithm = indicatorPattern->CreateLayoutAlgorithm();
    auto paintProperty = indicatorNode->GetPaintProperty<DotIndicatorPaintProperty>();
    paintProperty->UpdateSize(Dimension(-1.0, DimensionUnit::PX));

    /**
     * @tc.steps: step3. userSize is less not equal 0.
     */
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(indicatorNode, geometryNode, indicatorNode->GetLayoutProperty());
    algorithm->Measure(&layoutWrapper);
}

/**
 * @tc.name: SwiperIndicatorLayoutAlgorithmMeasure002
 * @tc.desc: Test for measure method of SwiperIndicatorLayoutAlgorithm.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperIndicatorLayoutAlgorithmMeasure002, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {
        model.SetDirection(Axis::VERTICAL);
    });
    layoutProperty_->UpdateDirection(Axis::VERTICAL);
    auto indicatorNode = GetChildFrameNode(frameNode_, 4);
    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    auto algorithm = indicatorPattern->CreateLayoutAlgorithm();
    auto paintProperty = indicatorNode->GetPaintProperty<DotIndicatorPaintProperty>();
    paintProperty->UpdateSize(Dimension(-1000.0, DimensionUnit::PX));

    /**
     * @tc.steps: step3. userSize is great then 0.
     */
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(indicatorNode, geometryNode, indicatorNode->GetLayoutProperty());
    algorithm->Measure(&layoutWrapper);
}

/**
 * @tc.name: SwiperIndicatorLayoutAlgorithmLayout001
 * @tc.desc: Test for layout method of SwiperIndicatorLayoutAlgorithm.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperIndicatorLayoutAlgorithmLayout001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {
        model.SetDirection(Axis::VERTICAL);
    });
    auto indicatorNode = GetChildFrameNode(frameNode_, 4);
    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    auto algorithm = indicatorPattern->CreateLayoutAlgorithm();
    auto layoutProperty = indicatorNode->GetLayoutProperty<SwiperIndicatorLayoutProperty>();
    layoutProperty->UpdateLeft(Dimension(100.0, DimensionUnit::PX));

    /**
     * @tc.steps: step3. layoutProperty is avaible.
     */
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode layoutWrapper = LayoutWrapperNode(indicatorNode, geometryNode, layoutProperty);

    LayoutConstraintF layoutConstraint;
    layoutConstraint.maxSize = SizeF(720.f, 1136.f);
    layoutConstraint.percentReference = SizeF(720.f, 1136.f);
    layoutConstraint.parentIdealSize.SetSize(SizeF(720.f, 1136.f));
    ASSERT_NE(layoutWrapper.layoutProperty_, nullptr);
    layoutWrapper.GetLayoutProperty()->UpdateLayoutConstraint(layoutConstraint);
    algorithm->Layout(&layoutWrapper);
    EXPECT_TRUE(IsEqual(layoutWrapper.GetGeometryNode()->GetMarginFrameOffset(), OffsetF(100.00, 568.00)));
    layoutProperty->Reset();
    ASSERT_NE(layoutProperty->Clone(), nullptr);
}

/**
 * @tc.name: SwiperIndicatorLayoutAlgorithmLayout002
 * @tc.desc: Test for layout method of SwiperIndicatorLayoutAlgorithm.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperIndicatorLayoutAlgorithmLayout002, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    auto indicatorNode = GetChildFrameNode(frameNode_, 4);
    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    auto algorithm = indicatorPattern->CreateLayoutAlgorithm();
    auto layoutProperty = indicatorNode->GetLayoutProperty<SwiperIndicatorLayoutProperty>();
    layoutProperty->UpdateRight(Dimension(100.0, DimensionUnit::PX));

    /**
     * @tc.steps: step3. layoutProperty right is avaible.
     */
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode layoutWrapper = LayoutWrapperNode(indicatorNode, geometryNode, layoutProperty);
    LayoutConstraintF layoutConstraint;
    layoutConstraint.maxSize = SizeF(720.f, 1136.f);
    layoutConstraint.percentReference = SizeF(720.f, 1136.f);
    layoutConstraint.parentIdealSize.SetSize(SizeF(720.f, 1136.f));
    ASSERT_NE(layoutWrapper.layoutProperty_, nullptr);
    layoutWrapper.GetLayoutProperty()->UpdateLayoutConstraint(layoutConstraint);

    algorithm->Layout(&layoutWrapper);
    EXPECT_TRUE(IsEqual(layoutWrapper.GetGeometryNode()->GetMarginFrameOffset(), OffsetF(620.00, 1136.00)));
}

/**
 * @tc.name: SwiperIndicatorLayoutAlgorithmLayout003
 * @tc.desc: Test for layout method of SwiperIndicatorLayoutAlgorithm.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperIndicatorLayoutAlgorithmLayout003, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    auto indicatorNode = GetChildFrameNode(frameNode_, 4);
    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    auto algorithm = indicatorPattern->CreateLayoutAlgorithm();
    auto layoutProperty = indicatorNode->GetLayoutProperty<SwiperIndicatorLayoutProperty>();
    layoutProperty->UpdateRight(Dimension(100.0, DimensionUnit::PX));

    /**
     * @tc.steps: step3. layoutProperty is default.
     */
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode layoutWrapper = LayoutWrapperNode(indicatorNode, geometryNode, layoutProperty);
    LayoutConstraintF layoutConstraint;
    layoutConstraint.maxSize = SizeF(720.f, 1136.f);
    layoutConstraint.percentReference = SizeF(720.f, 1136.f);
    layoutConstraint.parentIdealSize.SetSize(SizeF(720.f, 1136.f));
    ASSERT_NE(layoutWrapper.layoutProperty_, nullptr);
    layoutWrapper.GetLayoutProperty()->UpdateLayoutConstraint(layoutConstraint);

    algorithm->Layout(&layoutWrapper);
    EXPECT_TRUE(IsEqual(layoutWrapper.GetGeometryNode()->GetMarginFrameOffset(), OffsetF(620.00, 1136.00)));
}

/**
 * @tc.name: SwiperIndicatorLayoutAlgorithmLayout004
 * @tc.desc: Test for layout method of SwiperIndicatorLayoutAlgorithm.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperIndicatorLayoutAlgorithmLayout004, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {
        model.SetDirection(Axis::VERTICAL);
    });
    auto indicatorNode = GetChildFrameNode(frameNode_, 4);
    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    auto algorithm = indicatorPattern->CreateLayoutAlgorithm();
    auto layoutProperty = indicatorNode->GetLayoutProperty<SwiperIndicatorLayoutProperty>();
    layoutProperty->UpdateTop(Dimension(100.0, DimensionUnit::PX));

    /**
     * @tc.steps: step3. layoutProperty top is avaible.
     */
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode layoutWrapper = LayoutWrapperNode(indicatorNode, geometryNode, layoutProperty);
    LayoutConstraintF layoutConstraint;
    layoutConstraint.maxSize = SizeF(720.f, 1136.f);
    layoutConstraint.percentReference = SizeF(720.f, 1136.f);
    layoutConstraint.parentIdealSize.SetSize(SizeF(720.f, 1136.f));
    ASSERT_NE(layoutWrapper.layoutProperty_, nullptr);
    layoutWrapper.GetLayoutProperty()->UpdateLayoutConstraint(layoutConstraint);
    algorithm->Layout(&layoutWrapper);
    EXPECT_TRUE(IsEqual(layoutWrapper.GetGeometryNode()->GetMarginFrameOffset(), OffsetF(720.00, 100.00)));
}

/**
 * @tc.name: SwiperIndicatorLayoutAlgorithmLayout005
 * @tc.desc: Test for layout method of SwiperIndicatorLayoutAlgorithm.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperIndicatorLayoutAlgorithmLayout005, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {
        model.SetDirection(Axis::VERTICAL);
    });
    auto indicatorNode = GetChildFrameNode(frameNode_, 4);
    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    auto algorithm = indicatorPattern->CreateLayoutAlgorithm();
    auto layoutProperty = indicatorNode->GetLayoutProperty<SwiperIndicatorLayoutProperty>();
    layoutProperty->UpdateBottom(Dimension(100.0, DimensionUnit::PX));

    /**
     * @tc.steps: step3. layoutProperty bottom is avaible.
     */
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode layoutWrapper = LayoutWrapperNode(indicatorNode, geometryNode, layoutProperty);
    LayoutConstraintF layoutConstraint;
    layoutConstraint.maxSize = SizeF(720.f, 1136.f);
    layoutConstraint.percentReference = SizeF(720.f, 1136.f);
    layoutConstraint.parentIdealSize.SetSize(SizeF(720.f, 1136.f));
    ASSERT_NE(layoutWrapper.layoutProperty_, nullptr);
    layoutWrapper.GetLayoutProperty()->UpdateLayoutConstraint(layoutConstraint);
    algorithm->Layout(&layoutWrapper);
    EXPECT_TRUE(IsEqual(layoutWrapper.GetGeometryNode()->GetMarginFrameOffset(), OffsetF(720.00, 1036.00)));
}

/**
 * @tc.name: SwiperIndicatorLayoutAlgorithmLayout006
 * @tc.desc: Test for layout method of SwiperIndicatorLayoutAlgorithm.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperIndicatorLayoutAlgorithmLayout006, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {
        model.SetDirection(Axis::VERTICAL);
    });
    auto indicatorNode = GetChildFrameNode(frameNode_, 4);
    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    auto algorithm = indicatorPattern->CreateLayoutAlgorithm();
    auto layoutProperty = indicatorNode->GetLayoutProperty<SwiperIndicatorLayoutProperty>();

    /**
     * @tc.steps: step3. layoutProperty is default.
     */
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode layoutWrapper = LayoutWrapperNode(indicatorNode, geometryNode, layoutProperty);
    LayoutConstraintF layoutConstraint;
    layoutConstraint.maxSize = SizeF(720.f, 1136.f);
    layoutConstraint.percentReference = SizeF(720.f, 1136.f);
    layoutConstraint.parentIdealSize.SetSize(SizeF(720.f, 1136.f));
    ASSERT_NE(layoutWrapper.layoutProperty_, nullptr);
    layoutWrapper.GetLayoutProperty()->UpdateLayoutConstraint(layoutConstraint);
    algorithm->Layout(&layoutWrapper);
    EXPECT_TRUE(IsEqual(layoutWrapper.GetGeometryNode()->GetMarginFrameOffset(), OffsetF(720.00, 568.00)));
}

/**
 * @tc.name: SwiperPattern0010
 * @tc.desc: Test pattern SetIsIndicatorCustomSize.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPattern0010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Default value
     */
    CreateWithItem([](SwiperModelNG model) {});
    bool isCustomSize = true;
    pattern_->SetIsIndicatorCustomSize(isCustomSize);
    EXPECT_TRUE(pattern_->IsCustomSize_);
}

/**
 * @tc.name: SwiperPattern0009
 * @tc.desc: Test pattern StopAndResetSpringAnimation.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPattern0009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Default value
     */
    CreateWithItem([](SwiperModelNG model) {});
    pattern_->springAnimationIsRunning_ = true;
    pattern_->StopAndResetSpringAnimation();
    EXPECT_FALSE(pattern_->springAnimationIsRunning_);
}

/**
 * @tc.name: SwiperPatternOnVisibleChange003
 * @tc.desc: OnVisibleChange
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternOnVisibleChange003, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    pattern_->isWindowShow_ = false;

    /**
     * @tc.cases: call OnVisibleChange.
     * @tc.expected: Related function runs ok.
     */
    pattern_->isInit_ = true;
    pattern_->OnVisibleChange(true);
    EXPECT_TRUE(pattern_->isInit_);
}

/**
 * @tc.name: SwiperPatternHandleTouchEvent002
 * @tc.desc: HandleTouchDown
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternHandleTouchEvent002, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    TouchLocationInfo touchLocationInfo("down", 0);
    touchLocationInfo.SetTouchType(TouchType::DOWN);
    std::list<TouchLocationInfo> infoSwiper;
    infoSwiper.emplace_back(touchLocationInfo);
    TouchEventInfo touchEventInfo("down");
    touchEventInfo.touches_ = infoSwiper;
    pattern_->HandleTouchEvent(touchEventInfo);
    EXPECT_FALSE(pattern_->indicatorDoingAnimation_);
    const char* name = "HandleTouchDown";
    pattern_->controller_ = CREATE_ANIMATOR(name);
    pattern_->controller_->status_ = Animator::Status::RUNNING;
    pattern_->HandleTouchEvent(touchEventInfo);
    touchEventInfo.touches_.clear();
    EXPECT_TRUE(touchEventInfo.touches_.empty());
}

/**
 * @tc.name: SwiperPatternHandleTouchUp003
 * @tc.desc: HandleTouchUp
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternHandleTouchUp003, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    pattern_->controller_ = AceType::MakeRefPtr<Animator>();
    pattern_->controller_->status_ = Animator::Status::PAUSED;

    /**
     * @tc.steps: step1. call HandleTouchUp.
     * @tc.expected: Related function runs ok.
     */
    pattern_->springAnimationIsRunning_ = false;
    pattern_->isTouchDownSpringAnimation_ = true;
    pattern_->HandleTouchUp();
    EXPECT_FALSE(pattern_->isTouchDownSpringAnimation_);
    EXPECT_TRUE(pattern_->springAnimationIsRunning_);
}

/**
 * @tc.name: SwiperPatternStopAnimationOnScrollStart001
 * @tc.desc: HandleTouchUp
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternStopAnimationOnScrollStart001, TestSize.Level1)
{
    EXPECT_CALL(*MockPipelineContext::pipeline_, FlushUITasks).Times(1);
    CreateWithItem([](SwiperModelNG model) {});
    /**
     * @tc.steps: step1. Set usePropertyAnimation_ To be true
     * @tc.expected: Pattern_->UsePropertyAnimation_ Condition is true
     */
    pattern_->usePropertyAnimation_ = true;
    pattern_->StopAnimationOnScrollStart(true);
    EXPECT_FALSE(pattern_->usePropertyAnimation_);
}

/**
 * @tc.name: SwiperPatternHandleDragEnd006
 * @tc.desc: HandleDragEnd
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternHandleDragEnd006, TestSize.Level1)
{
    EXPECT_CALL(*MockPipelineContext::pipeline_, FlushUITasks).Times(1);
    CreateWithItem([](SwiperModelNG model) {});
    EXPECT_NE(frameNode_->GetLayoutProperty<SwiperLayoutProperty>(), nullptr);
    layoutProperty_->UpdateLoop(false);
    layoutProperty_->ResetDisplayCount();
    layoutProperty_->ResetMinSize();
    layoutProperty_->UpdateDisplayMode(SwiperDisplayMode::AUTO_LINEAR);
    pattern_->leftButtonId_.reset();
    pattern_->rightButtonId_.reset();
    layoutProperty_->UpdateShowIndicator(false);
    pattern_->itemPosition_.emplace(std::make_pair(1, SwiperItemInfo { 1.0f, 2.0f }));
    pattern_->itemPosition_.emplace(std::make_pair(0, SwiperItemInfo { 1.0f, 2.0f }));
    double dragVelocity = 0.1;
    pattern_->fadeOffset_ = 1.0f;
    frameNode_->GetPaintProperty<SwiperPaintProperty>()->UpdateEdgeEffect(EdgeEffect::NONE);
    pattern_->currentIndex_ = 2;

    /**
     * @tc.steps: step1. call HandleDragEnd.
     * @tc.expected: Related function runs ok.
     */
    pattern_->swiperController_->SetAddTabBarEventCallback([] { return; });
    pattern_->itemPosition_.clear();
    pattern_->HandleDragEnd(dragVelocity);
    EXPECT_TRUE(pattern_->itemPosition_.empty());
}

/**
 * @tc.name: SwiperIndicatorLayoutAlgorithmGetValidEdgeLength001
 * @tc.desc: Test for layout method of SwiperIndicatorLayoutAlgorithmGetValidEdgeLength001.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperIndicatorLayoutAlgorithmGetValidEdgeLength001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {
        model.SetDirection(Axis::VERTICAL);
    });
    auto indicatorNode = GetChildFrameNode(frameNode_, 4);
    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    RefPtr<DotIndicatorLayoutAlgorithm> algorithm =
        AceType::DynamicCast<DotIndicatorLayoutAlgorithm>(indicatorPattern->CreateLayoutAlgorithm());

    /**
     * @tc.steps: step3. layoutProperty is default.
     */
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(indicatorNode, geometryNode, indicatorNode->GetLayoutProperty());
    EXPECT_EQ(algorithm->GetValidEdgeLength(100.0, 40.0, Dimension(0.7, DimensionUnit::PERCENT)), 60.0);
    EXPECT_EQ(algorithm->GetValidEdgeLength(100.0, 40.0, Dimension(0.5, DimensionUnit::PERCENT)), 50.0);
    EXPECT_EQ(algorithm->GetValidEdgeLength(100.0, 20.0, Dimension(0.0, DimensionUnit::PERCENT)), 0.0);
    EXPECT_EQ(algorithm->GetValidEdgeLength(100.0, 40.0, Dimension(70.0, DimensionUnit::PX)), 60.0);
    EXPECT_EQ(algorithm->GetValidEdgeLength(-10.0, 40.0, Dimension(-20.0, DimensionUnit::PX)), 0.0);
}

/**
 * @tc.name: SwiperIndicatorOnAttachToFrameNodeTest001
 * @tc.desc: Test SwiperIndicator OnAttachToFrameNode
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperIndicatorOnAttachToFrameNodeTest001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {
        model.SetDirection(Axis::VERTICAL);
    });
    auto indicatorNode = GetChildFrameNode(frameNode_, 4);

    RefPtr<SwiperIndicatorPattern> indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    indicatorPattern->OnAttachToFrameNode();
    auto swiperEventHub = pattern_->GetEventHub<SwiperEventHub>();
    swiperEventHub->FireIndicatorChangeEvent(0);
}

/**
 * @tc.name: SwiperIndicatorOnModifyDone001
 * @tc.desc: Test SwiperIndicator OnModifyDone
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperIndicatorOnModifyDone001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {
        model.SetDirection(Axis::VERTICAL);
    });
    auto indicatorNode = GetChildFrameNode(frameNode_, 4);

    RefPtr<SwiperIndicatorPattern> indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    indicatorPattern->OnModifyDone();
    DirtySwapConfig config;
    config.frameSizeChange = false;
    EXPECT_FALSE(indicatorPattern->OnDirtyLayoutWrapperSwap(nullptr, config));
    config.frameSizeChange = true;
    EXPECT_TRUE(indicatorPattern->OnDirtyLayoutWrapperSwap(nullptr, config));
}

/**
 * @tc.name: SwiperIndicatorHandleClick001
 * @tc.desc: Test SwiperIndicator HandleClick
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperIndicatorHandleClick001, TestSize.Level1)
{
    EXPECT_CALL(*MockPipelineContext::pipeline_, FlushUITasks).Times(1);
    CreateWithItem([](SwiperModelNG model) {
        model.SetDirection(Axis::VERTICAL);
    });
    auto indicatorNode = GetChildFrameNode(frameNode_, 4);
    RefPtr<SwiperIndicatorPattern> indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    GestureEvent info;
    auto paintProperty = indicatorNode->GetPaintProperty<DotIndicatorPaintProperty>();
    paintProperty->UpdateSize(Dimension(-1.0, DimensionUnit::PX));
    indicatorPattern->HandleClick(info);
}

/**
 * @tc.name: SwiperIndicatorGetContentModifier001
 * @tc.desc: Test SwiperIndicator GetContentModifier
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperIndicatorGetContentModifier001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {
        model.SetDirection(Axis::VERTICAL);
    });
    auto indicatorNode = GetChildFrameNode(frameNode_, 4);
    RefPtr<DotIndicatorModifier> modifier = AceType::MakeRefPtr<DotIndicatorModifier>();
    RefPtr<DotIndicatorPaintMethod> paintMethod = AceType::MakeRefPtr<DotIndicatorPaintMethod>(modifier);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto paintProperty = AceType::MakeRefPtr<DotIndicatorPaintProperty>();
    paintProperty->Clone();
    paintProperty->Reset();
    paintProperty->UpdateColor(Color::RED);
    auto renderContext = frameNode_->GetRenderContext();
    PaintWrapper paintWrapper(renderContext, geometryNode, paintProperty);
    /**
     * @tc.steps: step3. call GetContentModifier.
     */
    EXPECT_FALSE(paintMethod->GetContentModifier(nullptr) == nullptr);
    paintMethod->UpdateContentModifier(&paintWrapper);
    RefPtr<Modifier> ptrModifier = paintMethod->GetContentModifier(&paintWrapper);
    ASSERT_NE(ptrModifier, nullptr);
}

/**
 * @tc.name: SelectedFontSize001
 * @tc.desc: Test SwiperIndicator SelectedFontSize
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SelectedFontSize001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {
        model.SetDirection(Axis::VERTICAL);
        model.SetIndicatorType(SwiperIndicatorType::DIGIT);
    });
    auto indicatorNode = GetChildFrameNode(frameNode_, 4);
    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    indicatorPattern->OnModifyDone();
    auto algorithm = indicatorPattern->CreateLayoutAlgorithm();

    /**
     * @tc.steps: step3. SelectedFontSize is 14.
     */
    auto swiperEventHub = pattern_->GetEventHub<SwiperEventHub>();
    swiperEventHub->FireIndicatorChangeEvent(0);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(indicatorNode, geometryNode, indicatorNode->GetLayoutProperty());
    algorithm->Measure(&layoutWrapper);
    auto frontTextFrameNode = AceType::DynamicCast<FrameNode>(indicatorNode->GetFirstChild());
    auto frontTextLayoutProperty = AceType::DynamicCast<TextLayoutProperty>(frontTextFrameNode->GetLayoutProperty());
    EXPECT_EQ(frontTextLayoutProperty->GetFontSize()->ConvertToPx(), 14);

    /**
     * @tc.steps: step4. SelectedFontSize is 60.
     */
    auto layoutProperty = indicatorNode->GetLayoutProperty<SwiperIndicatorLayoutProperty>();
    Dimension fontSize = 60.0_px;
    layoutProperty->UpdateSelectedFontSize(fontSize);
    indicatorPattern->OnModifyDone();
    EXPECT_EQ(frontTextLayoutProperty->GetFontSize()->ConvertToPx(), 60);
}

/**
 * @tc.name: SelectedFontSize002
 * @tc.desc: Test SwiperIndicator SelectedFontSize
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SelectedFontSize002, TestSize.Level2)
{
    CreateWithItem([](SwiperModelNG model) {
        model.SetDirection(Axis::VERTICAL);
        model.SetIndicatorType(SwiperIndicatorType::DIGIT);
    });
    auto indicatorNode = GetChildFrameNode(frameNode_, 4);
    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    indicatorPattern->OnModifyDone();
    auto algorithm = indicatorPattern->CreateLayoutAlgorithm();
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(indicatorNode, geometryNode, indicatorNode->GetLayoutProperty());
    algorithm->Measure(&layoutWrapper);
    auto frontTextFrameNode = AceType::DynamicCast<FrameNode>(indicatorNode->GetFirstChild());
    auto frontTextLayoutProperty = AceType::DynamicCast<TextLayoutProperty>(frontTextFrameNode->GetLayoutProperty());

    /**
     * @tc.steps: step4. SelectedFontSize is -1.
     */
    auto layoutProperty = indicatorNode->GetLayoutProperty<SwiperIndicatorLayoutProperty>();
    Dimension fontSize = -1.0_px;
    layoutProperty->UpdateSelectedFontSize(fontSize);
    indicatorPattern->OnModifyDone();
    EXPECT_EQ(frontTextLayoutProperty->GetFontSize()->ConvertToPx(), 14);
}

/**
 * @tc.name: FontSize001
 * @tc.desc: Test SwiperIndicator FontSize
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, FontSize001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {
        model.SetDirection(Axis::VERTICAL);
        model.SetIndicatorType(SwiperIndicatorType::DIGIT);
    });
    auto indicatorNode = GetChildFrameNode(frameNode_, 4);
    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    indicatorPattern->OnModifyDone();
    auto algorithm = indicatorPattern->CreateLayoutAlgorithm();

    /**
     * @tc.steps: step3. FontSize is 14.
     */
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(indicatorNode, geometryNode, indicatorNode->GetLayoutProperty());
    algorithm->Measure(&layoutWrapper);

    auto backTextFrameNode = AceType::DynamicCast<FrameNode>(indicatorNode->GetLastChild());
    auto backTextLayoutProperty = AceType::DynamicCast<TextLayoutProperty>(backTextFrameNode->GetLayoutProperty());
    EXPECT_EQ(backTextLayoutProperty->GetFontSize()->ConvertToPx(), 14);

    /**
     * @tc.steps: step3. FontSize is 30.
     */
    auto layoutProperty = indicatorNode->GetLayoutProperty<SwiperIndicatorLayoutProperty>();
    Dimension fontSize = 30.0_px;
    layoutProperty->UpdateFontSize(fontSize);
    auto swiperEventHub = pattern_->GetEventHub<SwiperEventHub>();
    swiperEventHub->FireIndicatorChangeEvent(0);
    EXPECT_EQ(backTextLayoutProperty->GetFontSize()->ConvertToPx(), 30);
}

/**
 * @tc.name: FontSize002
 * @tc.desc: Test SwiperIndicator FontSize
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, FontSize002, TestSize.Level2)
{
    CreateWithItem([](SwiperModelNG model) {
        model.SetIndicatorType(SwiperIndicatorType::DIGIT);
    });
    auto indicatorNode = GetChildFrameNode(frameNode_, 4);
    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    indicatorPattern->OnModifyDone();
    auto algorithm = indicatorPattern->CreateLayoutAlgorithm();
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(indicatorNode, geometryNode, indicatorNode->GetLayoutProperty());
    algorithm->Measure(&layoutWrapper);
    auto backTextFrameNode = AceType::DynamicCast<FrameNode>(indicatorNode->GetLastChild());
    auto backTextLayoutProperty = AceType::DynamicCast<TextLayoutProperty>(backTextFrameNode->GetLayoutProperty());

    /**
     * @tc.steps: step3. FontSize is -10.
     */
    auto layoutProperty = indicatorNode->GetLayoutProperty<SwiperIndicatorLayoutProperty>();
    Dimension fontSize = -10.0_px;
    layoutProperty->UpdateFontSize(fontSize);
    auto swiperEventHub = pattern_->GetEventHub<SwiperEventHub>();
    swiperEventHub->FireIndicatorChangeEvent(0);
    EXPECT_EQ(backTextLayoutProperty->GetFontSize()->ConvertToPx(), 14);
}

/**
 * @tc.name: FontColor001
 * @tc.desc: Test SwiperIndicator FontColor
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, FontColor001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {
        model.SetIndicatorType(SwiperIndicatorType::DIGIT);
    });
    auto indicatorNode = GetChildFrameNode(frameNode_, 4);
    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    indicatorPattern->OnModifyDone();
    auto algorithm = indicatorPattern->CreateLayoutAlgorithm();

    /**
     * @tc.steps: step3. FontColor is 0xff000000.
     */
    auto swiperEventHub = pattern_->GetEventHub<SwiperEventHub>();
    swiperEventHub->FireIndicatorChangeEvent(0);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(indicatorNode, geometryNode, indicatorNode->GetLayoutProperty());
    algorithm->Measure(&layoutWrapper);
    auto backTextFrameNode = AceType::DynamicCast<FrameNode>(indicatorNode->GetLastChild());
    auto backTextLayoutProperty = AceType::DynamicCast<TextLayoutProperty>(backTextFrameNode->GetLayoutProperty());
    EXPECT_EQ(backTextLayoutProperty->GetTextColor(), Color::FromString("#ff182431"));

    /**
     * @tc.steps: step3. FontColor is WHITE.
     */
    auto layoutProperty = indicatorNode->GetLayoutProperty<SwiperIndicatorLayoutProperty>();
    layoutProperty->UpdateFontColor(Color::WHITE);
    swiperEventHub->FireIndicatorChangeEvent(0);
    EXPECT_EQ(backTextLayoutProperty->GetTextColor()->GetValue(), 0xffffffff);
}

/**
 * @tc.name: FontColor002
 * @tc.desc: Test SwiperIndicator FontColor
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, FontColor002, TestSize.Level2)
{
    CreateWithItem([](SwiperModelNG model) {
        model.SetIndicatorType(SwiperIndicatorType::DIGIT);
    });
    auto indicatorNode = GetChildFrameNode(frameNode_, 4);
    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    indicatorPattern->OnModifyDone();
    auto algorithm = indicatorPattern->CreateLayoutAlgorithm();
    auto swiperEventHub = pattern_->GetEventHub<SwiperEventHub>();
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(indicatorNode, geometryNode, indicatorNode->GetLayoutProperty());
    algorithm->Measure(&layoutWrapper);
    auto backTextFrameNode = AceType::DynamicCast<FrameNode>(indicatorNode->GetLastChild());
    auto backTextLayoutProperty = AceType::DynamicCast<TextLayoutProperty>(backTextFrameNode->GetLayoutProperty());

    /**
     * @tc.steps: step3. FontColor is 0xff00ff00.
     */
    auto layoutProperty = indicatorNode->GetLayoutProperty<SwiperIndicatorLayoutProperty>();
    layoutProperty->UpdateFontColor(Color());
    swiperEventHub->FireIndicatorChangeEvent(0);
    EXPECT_EQ(backTextLayoutProperty->GetTextColor()->GetValue(), 0xff000000);
}

/**
 * @tc.name: SelectedFontColor001
 * @tc.desc: Test SwiperIndicator SelectedFontColor
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SelectedFontColor001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {
        model.SetIndicatorType(SwiperIndicatorType::DIGIT);
    });
    auto indicatorNode = GetChildFrameNode(frameNode_, 4);
    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    indicatorPattern->OnModifyDone();
    auto algorithm = indicatorPattern->CreateLayoutAlgorithm();

    /**
     * @tc.steps: step3. SelectedFontColor001 is 0xff000000.
     */
    auto swiperEventHub = pattern_->GetEventHub<SwiperEventHub>();
    swiperEventHub->FireIndicatorChangeEvent(0);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(indicatorNode, geometryNode, indicatorNode->GetLayoutProperty());
    algorithm->Measure(&layoutWrapper);
    auto frontTextFrameNode = AceType::DynamicCast<FrameNode>(indicatorNode->GetFirstChild());
    auto frontTextLayoutProperty = AceType::DynamicCast<TextLayoutProperty>(frontTextFrameNode->GetLayoutProperty());
    EXPECT_EQ(frontTextLayoutProperty->GetTextColor(), Color::FromString("#ff182431"));

    /**
     * @tc.steps: step4. SelectedFontColor is WHITE.
     */
    auto layoutProperty = indicatorNode->GetLayoutProperty<SwiperIndicatorLayoutProperty>();
    layoutProperty->UpdateSelectedFontColor(Color::WHITE);
    swiperEventHub->FireIndicatorChangeEvent(0);
    EXPECT_EQ(frontTextLayoutProperty->GetTextColor()->GetValue(), 0xffffffff);
}

/**
 * @tc.name: SelectedFontColor002
 * @tc.desc: Test SwiperIndicator SelectedFontColor
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SelectedFontColor002, TestSize.Level2)
{
    CreateWithItem([](SwiperModelNG model) {
        model.SetIndicatorType(SwiperIndicatorType::DIGIT);
    });
    auto indicatorNode = GetChildFrameNode(frameNode_, 4);
    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    indicatorPattern->OnModifyDone();
    auto algorithm = indicatorPattern->CreateLayoutAlgorithm();
    auto layoutProperty = indicatorNode->GetLayoutProperty<SwiperIndicatorLayoutProperty>();
    auto swiperEventHub = pattern_->GetEventHub<SwiperEventHub>();
    swiperEventHub->FireIndicatorChangeEvent(0);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(indicatorNode, geometryNode, indicatorNode->GetLayoutProperty());
    algorithm->Measure(&layoutWrapper);
    auto frontTextFrameNode = AceType::DynamicCast<FrameNode>(indicatorNode->GetFirstChild());
    auto frontTextLayoutProperty = AceType::DynamicCast<TextLayoutProperty>(frontTextFrameNode->GetLayoutProperty());
    /**
     * @tc.steps: step3. SelectedFontColor is Color().
     */
    layoutProperty->UpdateSelectedFontColor(Color());
    swiperEventHub->FireIndicatorChangeEvent(0);
    EXPECT_EQ(frontTextLayoutProperty->GetTextColor()->GetValue(), 0xff000000);
}

/**
 * @tc.name: FontWeight001
 * @tc.desc: Test SwiperIndicator FontWeight
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, FontWeight001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {
        model.SetIndicatorType(SwiperIndicatorType::DIGIT);
    });
    auto indicatorNode = GetChildFrameNode(frameNode_, 4);
    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    indicatorPattern->OnModifyDone();
    auto algorithm = indicatorPattern->CreateLayoutAlgorithm();

    /**
     * @tc.steps: step3. FontWeight is NORMAL.
     */
    auto swiperEventHub = pattern_->GetEventHub<SwiperEventHub>();
    swiperEventHub->FireIndicatorChangeEvent(0);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(indicatorNode, geometryNode, indicatorNode->GetLayoutProperty());
    algorithm->Measure(&layoutWrapper);
    auto backTextFrameNode = AceType::DynamicCast<FrameNode>(indicatorNode->GetLastChild());
    auto backTextLayoutProperty = AceType::DynamicCast<TextLayoutProperty>(backTextFrameNode->GetLayoutProperty());
    EXPECT_EQ(backTextLayoutProperty->GetFontWeight(), FontWeight::W800);
    /**
     * @tc.steps: step3. FontWeight is BOLDER.
     */
    auto layoutProperty = indicatorNode->GetLayoutProperty<SwiperIndicatorLayoutProperty>();
    layoutProperty->UpdateFontWeight(FontWeight::BOLDER);
    swiperEventHub->FireIndicatorChangeEvent(0);
    EXPECT_EQ(backTextLayoutProperty->GetFontWeight(), FontWeight::BOLDER);
}

/**
 * @tc.name: SelectedFontWeight001
 * @tc.desc: Test SwiperIndicator SelectedFontWeight
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SelectedFontWeight001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {
        model.SetIndicatorType(SwiperIndicatorType::DIGIT);
    });
    auto indicatorNode = GetChildFrameNode(frameNode_, 4);
    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    indicatorPattern->OnModifyDone();
    auto algorithm = indicatorPattern->CreateLayoutAlgorithm();

    /**
     * @tc.steps: step3. SelectedFontWeight is NORMAL.
     */
    auto swiperEventHub = pattern_->GetEventHub<SwiperEventHub>();
    swiperEventHub->FireIndicatorChangeEvent(0);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(indicatorNode, geometryNode, indicatorNode->GetLayoutProperty());
    algorithm->Measure(&layoutWrapper);
    auto frontTextFrameNode = AceType::DynamicCast<FrameNode>(indicatorNode->GetFirstChild());
    auto frontTextLayoutProperty = AceType::DynamicCast<TextLayoutProperty>(frontTextFrameNode->GetLayoutProperty());
    EXPECT_EQ(frontTextLayoutProperty->GetFontWeight(), FontWeight::W800);
    /**
     * @tc.steps: step3. SelectedFontWeight is MEDIUM.
     */
    auto layoutProperty = indicatorNode->GetLayoutProperty<SwiperIndicatorLayoutProperty>();
    layoutProperty->UpdateSelectedFontWeight(FontWeight::MEDIUM);
    swiperEventHub->FireIndicatorChangeEvent(0);
    EXPECT_EQ(frontTextLayoutProperty->GetFontWeight(), FontWeight::MEDIUM);
}

/**
 * @tc.name: ItemWidth001
 * @tc.desc: Test SwiperIndicator ItemWidth
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, ItemWidth001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    auto indicatorNode = GetChildFrameNode(frameNode_, 4);
    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    RefPtr<NodePaintMethod> nodePaintMethod = indicatorPattern->CreateNodePaintMethod();
    auto algorithm = indicatorPattern->CreateLayoutAlgorithm();
    auto paintProperty = indicatorNode->GetPaintProperty<DotIndicatorPaintProperty>();
    paintProperty->UpdateItemWidth(Dimension(-1.0, DimensionUnit::PX));

    /**
     * @tc.steps: step3. userSize is less not equal 0.
     */
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(indicatorNode, geometryNode, indicatorNode->GetLayoutProperty());
    algorithm->Measure(&layoutWrapper);
}

/**
 * @tc.name: ItemWidth002
 * @tc.desc: Test SwiperIndicator ItemWidth
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, ItemWidth002, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {
        model.SetDirection(Axis::VERTICAL);
    });
    auto indicatorNode = GetChildFrameNode(frameNode_, 4);
    layoutProperty_->UpdateDirection(Axis::VERTICAL);
    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    auto algorithm = indicatorPattern->CreateLayoutAlgorithm();
    auto paintProperty = indicatorNode->GetPaintProperty<DotIndicatorPaintProperty>();
    paintProperty->UpdateItemWidth(Dimension(-1000.0, DimensionUnit::PX));

    /**
     * @tc.steps: step3. ItemWidth is great then 0.
     */
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(indicatorNode, geometryNode, indicatorNode->GetLayoutProperty());
    algorithm->Measure(&layoutWrapper);
}

/**
 * @tc.name: ItemHeight001
 * @tc.desc: Test SwiperIndicator ItemHeight
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, ItemHeight001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    auto indicatorNode = GetChildFrameNode(frameNode_, 4);
    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    RefPtr<NodePaintMethod> nodePaintMethod = indicatorPattern->CreateNodePaintMethod();
    auto algorithm = indicatorPattern->CreateLayoutAlgorithm();
    auto paintProperty = indicatorNode->GetPaintProperty<DotIndicatorPaintProperty>();
    paintProperty->UpdateItemHeight(Dimension(-1.0, DimensionUnit::PX));

    /**
     * @tc.steps: step3. ItemHeight is less not equal 0.
     */
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(indicatorNode, geometryNode, indicatorNode->GetLayoutProperty());
    algorithm->Measure(&layoutWrapper);
}

/**
 * @tc.name: ItemHeight002
 * @tc.desc: Test SwiperIndicator ItemHeight
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, ItemHeight002, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {
        model.SetDirection(Axis::VERTICAL);
    });
    auto indicatorNode = GetChildFrameNode(frameNode_, 4);
    layoutProperty_->UpdateDirection(Axis::VERTICAL);
    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    auto algorithm = indicatorPattern->CreateLayoutAlgorithm();
    auto paintProperty = indicatorNode->GetPaintProperty<DotIndicatorPaintProperty>();
    paintProperty->UpdateItemHeight(Dimension(-1000.0, DimensionUnit::PX));

    /**
     * @tc.steps: step3. ItemHeight is great then 0.
     */
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(indicatorNode, geometryNode, indicatorNode->GetLayoutProperty());
    algorithm->Measure(&layoutWrapper);
}

/**
 * @tc.name: SelectedItemWidth001
 * @tc.desc: Test SwiperIndicator SelectedItemWidth
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SelectedItemWidth001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    auto indicatorNode = GetChildFrameNode(frameNode_, 4);
    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    RefPtr<NodePaintMethod> nodePaintMethod = indicatorPattern->CreateNodePaintMethod();
    auto algorithm = indicatorPattern->CreateLayoutAlgorithm();
    auto paintProperty = indicatorNode->GetPaintProperty<DotIndicatorPaintProperty>();
    paintProperty->UpdateSelectedItemWidth(Dimension(-1.0, DimensionUnit::PX));

    /**
     * @tc.steps: step3. SelectedItemWidth is less not equal 0.
     */
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(indicatorNode, geometryNode, indicatorNode->GetLayoutProperty());
    algorithm->Measure(&layoutWrapper);
}

/**
 * @tc.name: SelectedItemWidth002
 * @tc.desc: Test SwiperIndicator SelectedItemWidth
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SelectedItemWidth002, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {
        model.SetDirection(Axis::VERTICAL);
    });
    auto indicatorNode = GetChildFrameNode(frameNode_, 4);
    layoutProperty_->UpdateDirection(Axis::VERTICAL);
    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    auto algorithm = indicatorPattern->CreateLayoutAlgorithm();
    auto paintProperty = indicatorNode->GetPaintProperty<DotIndicatorPaintProperty>();
    paintProperty->UpdateSelectedItemWidth(Dimension(-1000.0, DimensionUnit::PX));

    /**
     * @tc.steps: step3. SelectedItemWidth is great then 0.
     */
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(indicatorNode, geometryNode, indicatorNode->GetLayoutProperty());
    algorithm->Measure(&layoutWrapper);
}

/**
 * @tc.name: SelectedItemHeight001
 * @tc.desc: Test SwiperIndicator SelectedItemHeight
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SelectedItemHeight001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    auto indicatorNode = GetChildFrameNode(frameNode_, 4);
    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    RefPtr<NodePaintMethod> nodePaintMethod = indicatorPattern->CreateNodePaintMethod();
    auto algorithm = indicatorPattern->CreateLayoutAlgorithm();
    auto paintProperty = indicatorNode->GetPaintProperty<DotIndicatorPaintProperty>();
    paintProperty->UpdateSelectedItemHeight(Dimension(-1.0, DimensionUnit::PX));

    /**
     * @tc.steps: step3. SelectedItemHeight is less not equal 0.
     */
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(indicatorNode, geometryNode, indicatorNode->GetLayoutProperty());
    algorithm->Measure(&layoutWrapper);
}

/**
 * @tc.name: SelectedItemHeight002
 * @tc.desc: Test SwiperIndicator SelectedItemHeight
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SelectedItemHeight002, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {
        model.SetDirection(Axis::VERTICAL);
    });
    auto indicatorNode = GetChildFrameNode(frameNode_, 4);
    layoutProperty_->UpdateDirection(Axis::VERTICAL);
    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    auto algorithm = indicatorPattern->CreateLayoutAlgorithm();
    auto paintProperty = indicatorNode->GetPaintProperty<DotIndicatorPaintProperty>();
    paintProperty->UpdateSelectedItemHeight(Dimension(-1000.0, DimensionUnit::PX));

    /**
     * @tc.steps: step3. SelectedItemHeight is great then 0.
     */
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(indicatorNode, geometryNode, indicatorNode->GetLayoutProperty());
    algorithm->Measure(&layoutWrapper);
}

/**
 * @tc.name: SwiperLayoutAlgorithmLayout001
 * @tc.desc: Test SwiperLayoutAlgorithm SwiperLayoutAlgorithmLayout
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperLayoutAlgorithmLayout001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {
        model.SetIndicatorType(SwiperIndicatorType::DIGIT);
    });
    auto indicatorNode = GetChildFrameNode(frameNode_, 4);
    EXPECT_TRUE(IsEqual(indicatorNode->GetGeometryNode()->GetMarginFrameOffset(), OffsetF(232.0, 800.0)));
}

/**
 * @tc.name: SwiperLayoutAlgorithmLayout002
 * @tc.desc: Test SwiperLayoutAlgorithm SwiperLayoutAlgorithmLayout
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperLayoutAlgorithmLayout002, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {
        model.SetDirection(Axis::VERTICAL);
        model.SetIndicatorType(SwiperIndicatorType::DIGIT);
    });
    auto indicatorNode = GetChildFrameNode(frameNode_, 4);
    EXPECT_TRUE(IsEqual(indicatorNode->GetGeometryNode()->GetMarginFrameOffset(), OffsetF(464.0, 400.0)));
}

/**
 * @tc.name: SwiperLayoutAlgorithmLayout003
 * @tc.desc: Test SwiperLayoutAlgorithm SwiperLayoutAlgorithmLayout
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperLayoutAlgorithmLayout003, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {
        model.SetIndicatorType(SwiperIndicatorType::DIGIT);
    });
    Dimension dimension = 20.0_vp;
    layoutProperty_->UpdateLeft(dimension);
    layoutProperty_->UpdateTop(dimension);
    layoutProperty_->UpdateDirection(Axis::HORIZONTAL);

    /**
     * @tc.steps: step3. call Layout.
     * @tc.expected: indicatorNodeWrapper MarginFrameOffset is 20.0, 20.0 .
     */
}

/**
 * @tc.name: SwiperLayoutAlgorithmLayout004
 * @tc.desc: Test SwiperLayoutAlgorithm SwiperLayoutAlgorithmLayout
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperLayoutAlgorithmLayout004, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {
        model.SetIndicatorType(SwiperIndicatorType::DIGIT);
    });
    Dimension dimension = 20.0_vp;
    layoutProperty_->UpdateRight(dimension);
    layoutProperty_->UpdateBottom(dimension);
    layoutProperty_->UpdateDirection(Axis::VERTICAL);

    /**
     * @tc.steps: step3. call Layout.
     * @tc.expected: indicatorNodeWrapper MarginFrameOffset is 634.0, 1086.0 .
     */
}

/**
 * @tc.name: SwiperLayoutAlgorithmLayout005
 * @tc.desc: Test SwiperLayoutAlgorithm Layout with arrow
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperLayoutAlgorithmLayout005, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {
        model.SetDisplayArrow(true); // show arrow
        model.SetHoverShow(false);
        model.SetArrowStyle(ARROW_PARAMETERS);
    });
    auto indicatorNode = GetChildFrameNode(frameNode_, 4);
    auto leftArrowNode = GetChildFrameNode(frameNode_, 5);
    auto rightArrowNode = GetChildFrameNode(frameNode_, 6);
    auto indicatorGeometryNode = indicatorNode->GetGeometryNode();
    auto leftArrowGeometryNode = leftArrowNode->GetGeometryNode();
    auto rightArrowGeometryNode = rightArrowNode->GetGeometryNode();

    /**
     * @tc.cases: case1. Axis is HORIZONTAL, arrow is in the switch.
     */
    indicatorGeometryNode->SetFrameOffset(OffsetF(250.0f, 190.0f));
    indicatorGeometryNode->SetFrameSize(SizeF(144.0f, 48.0f));
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(IsEqual(leftArrowGeometryNode->GetMarginFrameOffset(), OffsetF(0.0f, 388.0f)));
    EXPECT_TRUE(IsEqual(rightArrowGeometryNode->GetMarginFrameOffset(), OffsetF(456.0f, 388.0f)));

    /**
     * @tc.cases: case2. Axis is HORIZONTAL, arrow is outside the switch.
     */
    indicatorGeometryNode->SetFrameOffset(OffsetF(15.0f, 240.0f));
    indicatorGeometryNode->SetFrameSize(SizeF(625.0f, 48.0f));
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(IsEqual(leftArrowGeometryNode->GetMarginFrameOffset(), OffsetF(0.0f, 388.0f)));
    EXPECT_TRUE(IsEqual(rightArrowGeometryNode->GetMarginFrameOffset(), OffsetF(456.0f, 388.0f)));

    /**
     * @tc.cases: case3. Axis is HORIZONTAL, arrow is in the switch, not show indicator.
     */
    layoutProperty_->UpdateShowIndicator(false);
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(IsEqual(leftArrowGeometryNode->GetMarginFrameOffset(), OffsetF(0.0f, 388.0f)));
    EXPECT_TRUE(IsEqual(rightArrowGeometryNode->GetMarginFrameOffset(), OffsetF(456.0f, 388.0f)));

    /**
     * @tc.cases: case4. Axis is VERTICAL, arrow is in the switch.
     */
    layoutProperty_->UpdateDirection(Axis::VERTICAL);
    layoutProperty_->UpdateShowIndicator(true);
    indicatorGeometryNode->SetFrameOffset(OffsetF(20.0f, 50.0f));
    indicatorGeometryNode->SetFrameSize(SizeF(20.0f, 100.0f));
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(IsEqual(leftArrowGeometryNode->GetMarginFrameOffset(), OffsetF(228.0f, 0.0f)));
    EXPECT_TRUE(IsEqual(rightArrowGeometryNode->GetMarginFrameOffset(), OffsetF(228.0f, 456.0f)));

    /**
     * @tc.cases: case5. Axis is VERTICAL, arrow is outside the switch.
     */
    indicatorGeometryNode->SetFrameOffset(OffsetF(20.0f, 15.0f));
    indicatorGeometryNode->SetFrameSize(SizeF(20.0f, 220.0f));
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(IsEqual(leftArrowGeometryNode->GetMarginFrameOffset(), OffsetF(228.0f, 0.0f)));
    EXPECT_TRUE(IsEqual(rightArrowGeometryNode->GetMarginFrameOffset(), OffsetF(228.0f, 456.0f)));

    /**
     * @tc.cases: case6. Axis is VERTICAL, arrow is in the switch, not show indicator.
     */
    layoutProperty_->UpdateShowIndicator(false);
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(IsEqual(leftArrowGeometryNode->GetMarginFrameOffset(), OffsetF(228.0f, 0.0f)));
    EXPECT_TRUE(IsEqual(rightArrowGeometryNode->GetMarginFrameOffset(), OffsetF(228.0f, 456.0f)));
}

/**
 * @tc.name: SwiperLayoutAlgorithmMeasure001
 * @tc.desc: Test SwiperLayoutAlgorithm Measure with arrow
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperLayoutAlgorithmMeasure001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {
        model.SetDisplayArrow(true); // show arrow
        model.SetHoverShow(false);
        model.SetArrowStyle(ARROW_PARAMETERS);
    });
    auto leftArrowNode = GetChildFrameNode(frameNode_, 5);
    auto rightArrowNode = GetChildFrameNode(frameNode_, 6);

    /**
     * @tc.steps: step4. call Measure.
     * @tc.expected: Return button measure, SizeF(3.0f, 3.0f).
     */
    layoutProperty_->UpdateBackgroundSize(3.0_vp);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(leftArrowNode->GetGeometryNode()->GetFrameSize(), SizeF(3.0f, 3.0f));
    EXPECT_EQ(rightArrowNode->GetGeometryNode()->GetFrameSize(), SizeF(3.0f, 3.0f));
}

/**
 * @tc.name: SwiperIndicatorUpdateContentModifier001
 * @tc.desc: Test DotIndicatorPaintMethod UpdateContentModifier
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperIndicatorUpdateContentModifier001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {
        model.SetDirection(Axis::VERTICAL);
    });
    auto indicatorNode = GetChildFrameNode(frameNode_, 4);
    RefPtr<DotIndicatorModifier> modifier = AceType::MakeRefPtr<DotIndicatorModifier>();
    RefPtr<DotIndicatorPaintMethod> paintMethod = AceType::MakeRefPtr<DotIndicatorPaintMethod>(modifier);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto paintProperty = AceType::MakeRefPtr<DotIndicatorPaintProperty>();
    paintProperty->Clone();
    paintProperty->Reset();
    auto renderContext = frameNode_->GetRenderContext();
    PaintWrapper paintWrapper(renderContext, geometryNode, paintProperty);
    EXPECT_FALSE(paintMethod->GetContentModifier(nullptr) == nullptr);
    paintMethod->isPressed_ = true;

    /**
     * @tc.steps: step3. call GetContentModifier.
     * @tc.expected: dotIndicatorModifier_->isPressed_ is true.
     */
    paintMethod->UpdateContentModifier(&paintWrapper);
    ASSERT_NE(paintMethod->dotIndicatorModifier_, nullptr);
    EXPECT_TRUE(paintMethod->dotIndicatorModifier_->GetIsPressed());
}

/**
 * @tc.name: SwiperIndicatorUpdateContentModifier002
 * @tc.desc: Test DotIndicatorPaintMethod SwiperIndicatorUpdateContentModifier
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperIndicatorUpdateContentModifier002, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {
        model.SetDirection(Axis::VERTICAL);
    });
    auto indicatorNode = GetChildFrameNode(frameNode_, 4);
    RefPtr<DotIndicatorModifier> modifier = AceType::MakeRefPtr<DotIndicatorModifier>();
    RefPtr<DotIndicatorPaintMethod> paintMethod = AceType::MakeRefPtr<DotIndicatorPaintMethod>(modifier);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto paintProperty = AceType::MakeRefPtr<DotIndicatorPaintProperty>();
    paintProperty->Clone();
    paintProperty->Reset();
    auto renderContext = frameNode_->GetRenderContext();
    PaintWrapper paintWrapper(renderContext, geometryNode, paintProperty);
    EXPECT_FALSE(paintMethod->GetContentModifier(nullptr) == nullptr);
    paintMethod->isHover_ = true;

    /**
     * @tc.steps: step3. call GetContentModifier.
     * @tc.expected: dotIndicatorModifier_->isHover_ is true.
     */
    paintMethod->UpdateContentModifier(&paintWrapper);
    ASSERT_NE(paintMethod->dotIndicatorModifier_, nullptr);
    EXPECT_TRUE(paintMethod->dotIndicatorModifier_->GetIsHover());
}

/**
 * @tc.name: SwiperIndicatorUpdateContentModifier003
 * @tc.desc: Test DotIndicatorPaintMethod SwiperIndicatorUpdateContentModifier
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperIndicatorUpdateContentModifier003, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {
        model.SetDirection(Axis::VERTICAL);
    });
    auto indicatorNode = GetChildFrameNode(frameNode_, 4);
    RefPtr<DotIndicatorModifier> modifier = AceType::MakeRefPtr<DotIndicatorModifier>();
    RefPtr<DotIndicatorPaintMethod> paintMethod = AceType::MakeRefPtr<DotIndicatorPaintMethod>(modifier);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto paintProperty = AceType::MakeRefPtr<DotIndicatorPaintProperty>();
    paintProperty->Clone();
    paintProperty->Reset();
    auto renderContext = frameNode_->GetRenderContext();
    PaintWrapper paintWrapper(renderContext, geometryNode, paintProperty);
    EXPECT_FALSE(paintMethod->GetContentModifier(nullptr) == nullptr);
    paintMethod->isHover_ = true;
    paintMethod->touchBottomType_ = TouchBottomType::START;

    /**
     * @tc.steps: step3. call GetContentModifier.
     * @tc.expected: dotIndicatorModifier_->isHover_ is true.
     */
    paintMethod->UpdateContentModifier(&paintWrapper);
    ASSERT_NE(paintMethod->dotIndicatorModifier_, nullptr);
    EXPECT_FALSE(paintMethod->dotIndicatorModifier_->GetIsHover());
}

/**
 * @tc.name: SwiperIndicatorCalculateNormalMargin001
 * @tc.desc: Test DotIndicatorPaintMethod SwiperIndicatorCalculateNormalMargin
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperIndicatorCalculateNormalMargin001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {
        model.SetDirection(Axis::VERTICAL);
    });
    auto indicatorNode = GetChildFrameNode(frameNode_, 4);
    RefPtr<DotIndicatorModifier> modifier = AceType::MakeRefPtr<DotIndicatorModifier>();
    RefPtr<DotIndicatorPaintMethod> paintMethod = AceType::MakeRefPtr<DotIndicatorPaintMethod>(modifier);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    geometryNode->SetFrameSize(SizeF(720.f, 1136.f));
    auto paintProperty = AceType::MakeRefPtr<DotIndicatorPaintProperty>();
    paintProperty->Clone();
    paintProperty->Reset();
    paintProperty->UpdateItemWidth(Dimension(20.f, DimensionUnit::PX));
    paintProperty->UpdateItemHeight(Dimension(10.f, DimensionUnit::PX));
    paintProperty->UpdateSelectedItemWidth(Dimension(30.f, DimensionUnit::PX));
    paintProperty->UpdateSelectedItemHeight(Dimension(15.f, DimensionUnit::PX));
    auto renderContext = frameNode_->GetRenderContext();
    PaintWrapper paintWrapper(renderContext, geometryNode, paintProperty);
    paintMethod->dotIndicatorModifier_->SetIsHover(true);
    ASSERT_NE(paintMethod->dotIndicatorModifier_, nullptr);
    paintMethod->IsCustomSizeValue_ = true;
    /**
     * @tc.steps: step3. call PaintNormalIndicator.
     * @tc.expected: run success
     */
    paintMethod->PaintNormalIndicator(&paintWrapper);

    EXPECT_EQ(paintMethod->normalMargin_.GetX(), 347.0);
    EXPECT_EQ(paintMethod->normalMargin_.GetY(), 548.5);
}

/**
 * @tc.name: SwiperIndicatorCalculatePointCenterX001
 * @tc.desc: Test DotIndicatorPaintMethod CalculatePointCenterX
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperIndicatorCalculatePointCenterX001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {
        model.SetDirection(Axis::VERTICAL);
    });
    auto indicatorNode = GetChildFrameNode(frameNode_, 4);
    RefPtr<DotIndicatorModifier> modifier = AceType::MakeRefPtr<DotIndicatorModifier>();
    RefPtr<DotIndicatorPaintMethod> paintMethod = AceType::MakeRefPtr<DotIndicatorPaintMethod>(modifier);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    geometryNode->SetFrameSize(SizeF(720.f, 1136.f));
    auto paintProperty = AceType::MakeRefPtr<DotIndicatorPaintProperty>();
    paintProperty->Clone();
    paintProperty->Reset();
    paintProperty->UpdateItemWidth(Dimension(20.f, DimensionUnit::PX));
    paintProperty->UpdateItemHeight(Dimension(10.f, DimensionUnit::PX));
    paintProperty->UpdateSelectedItemWidth(Dimension(30.f, DimensionUnit::PX));
    paintProperty->UpdateSelectedItemHeight(Dimension(15.f, DimensionUnit::PX));
    LinearVector<float> vectorBlackPointCenterX;
    auto renderContext = frameNode_->GetRenderContext();
    PaintWrapper paintWrapper(renderContext, geometryNode, paintProperty);
    paintMethod->dotIndicatorModifier_->SetIsHover(true);
    ASSERT_NE(paintMethod->dotIndicatorModifier_, nullptr);
    paintMethod->IsCustomSizeValue_ = true;
    paintMethod->turnPageRate_ = 1.0;
    /**
     * @tc.steps: step3. call CalculatePointCenterX.
     * @tc.expected: run success
     */
    vectorBlackPointCenterX.push_back(20.0f);
    vectorBlackPointCenterX.push_back(20.0f);
    vectorBlackPointCenterX.push_back(20.0f);
    vectorBlackPointCenterX.push_back(20.0f);
    vectorBlackPointCenterX.push_back(20.0f);
    vectorBlackPointCenterX.push_back(20.0f);
    paintMethod->CalculatePointCenterX(vectorBlackPointCenterX, 0.0, 0.0, 0.0, 0);
    paintMethod->turnPageRate_ = 1.0;
    paintMethod->CalculatePointCenterX(vectorBlackPointCenterX, 0.0, 0.0, 0.0, 0);
    EXPECT_EQ(paintMethod->normalMargin_.GetX(), 0);
    EXPECT_EQ(paintMethod->normalMargin_.GetY(), 0);
}

/**
 * @tc.name: SwiperIndicatorUpdateBackgroundX001
 * @tc.desc: Test DotIndicatorPaintMethod UpdateBackground
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperIndicatorUpdateBackgroundX001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {
        model.SetDirection(Axis::VERTICAL);
    });
    auto indicatorNode = GetChildFrameNode(frameNode_, 4);
    RefPtr<DotIndicatorModifier> modifier = AceType::MakeRefPtr<DotIndicatorModifier>();
    RefPtr<DotIndicatorPaintMethod> paintMethod = AceType::MakeRefPtr<DotIndicatorPaintMethod>(modifier);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    geometryNode->SetFrameSize(SizeF(720.f, 1136.f));
    auto paintProperty = AceType::MakeRefPtr<DotIndicatorPaintProperty>();
    paintProperty->Clone();
    paintProperty->Reset();
    paintProperty->UpdateItemWidth(Dimension(20.f, DimensionUnit::PX));
    paintProperty->UpdateItemHeight(Dimension(10.f, DimensionUnit::PX));
    paintProperty->UpdateSelectedItemWidth(Dimension(30.f, DimensionUnit::PX));
    paintProperty->UpdateSelectedItemHeight(Dimension(15.f, DimensionUnit::PX));
    LinearVector<float> vectorBlackPointCenterX;
    auto renderContext = frameNode_->GetRenderContext();
    PaintWrapper paintWrapper(renderContext, geometryNode, paintProperty);
    paintMethod->dotIndicatorModifier_->SetIsHover(true);
    ASSERT_NE(paintMethod->dotIndicatorModifier_, nullptr);
    paintMethod->IsCustomSizeValue_ = true;
    paintMethod->turnPageRate_ = 1.0;
    paintMethod->touchBottomType_ = TouchBottomType::START;
    /**
     * @tc.steps: step3. call UpdateBackground.
     * @tc.expected: run success
     */
    paintMethod->UpdateBackground(&paintWrapper);
}

/**
 * @tc.name: SwiperIndicatorPaintNormalIndicator001
 * @tc.desc: Test DotIndicatorPaintMethod SwiperIndicatorPaintNormalIndicator
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperIndicatorPaintNormalIndicator001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {
        model.SetDirection(Axis::VERTICAL);
    });
    auto indicatorNode = GetChildFrameNode(frameNode_, 4);
    RefPtr<DotIndicatorModifier> modifier = AceType::MakeRefPtr<DotIndicatorModifier>();
    RefPtr<DotIndicatorPaintMethod> paintMethod = AceType::MakeRefPtr<DotIndicatorPaintMethod>(modifier);

    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    geometryNode->SetFrameSize(SizeF(720.f, 1136.f));
    auto paintProperty = AceType::MakeRefPtr<DotIndicatorPaintProperty>();
    paintProperty->Clone();
    paintProperty->Reset();
    paintProperty->UpdateItemWidth(Dimension(20.f, DimensionUnit::PX));
    paintProperty->UpdateItemHeight(Dimension(10.f, DimensionUnit::PX));
    paintProperty->UpdateSelectedItemWidth(Dimension(30.f, DimensionUnit::PX));
    paintProperty->UpdateSelectedItemHeight(Dimension(15.f, DimensionUnit::PX));
    auto renderContext = frameNode_->GetRenderContext();
    PaintWrapper paintWrapper(renderContext, geometryNode, paintProperty);
    paintMethod->dotIndicatorModifier_->SetIsHover(true);
    ASSERT_NE(paintMethod->dotIndicatorModifier_, nullptr);

    /**
     * @tc.steps: step3. call PaintNormalIndicator.
     * @tc.expected: paintMethod->normalMargin_.X is 342.0
     *               paintMethod->normalMargin_.Y is 548.5
     */
    paintMethod->PaintNormalIndicator(&paintWrapper);
    EXPECT_EQ(paintMethod->normalMargin_.GetX(), 342.0);
    EXPECT_EQ(paintMethod->normalMargin_.GetY(), 548.5);
}

/**
 * @tc.name: SwiperIndicatorPaintNormalIndicator002
 * @tc.desc: Test DotIndicatorPaintMethod SwiperIndicatorPaintNormalIndicator
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperIndicatorPaintNormalIndicator002, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {
        model.SetDirection(Axis::VERTICAL);
    });
    auto indicatorNode = GetChildFrameNode(frameNode_, 4);
    RefPtr<DotIndicatorModifier> modifier = AceType::MakeRefPtr<DotIndicatorModifier>();
    RefPtr<DotIndicatorPaintMethod> paintMethod = AceType::MakeRefPtr<DotIndicatorPaintMethod>(modifier);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    geometryNode->SetFrameSize(SizeF(720.f, 1136.f));
    auto paintProperty = AceType::MakeRefPtr<DotIndicatorPaintProperty>();
    paintProperty->Clone();
    paintProperty->Reset();
    paintProperty->UpdateItemWidth(Dimension(20.f, DimensionUnit::PX));
    paintProperty->UpdateItemHeight(Dimension(10.f, DimensionUnit::PX));
    paintProperty->UpdateSelectedItemWidth(Dimension(30.f, DimensionUnit::PX));
    paintProperty->UpdateSelectedItemHeight(Dimension(15.f, DimensionUnit::PX));
    auto renderContext = frameNode_->GetRenderContext();
    PaintWrapper paintWrapper(renderContext, geometryNode, paintProperty);
    ASSERT_NE(paintMethod->dotIndicatorModifier_, nullptr);
    paintMethod->dotIndicatorModifier_->SetIsPressed(true);
    paintMethod->itemCount_ = 10;

    /**
     * @tc.steps: step3. call PaintNormalIndicator.
     * @tc.expected: paintMethod->normalMargin_.X is 202.0
     *               paintMethod->normalMargin_.Y is 548.5
     */
    paintMethod->PaintNormalIndicator(&paintWrapper);
    EXPECT_EQ(paintMethod->normalMargin_.GetX(), 202.0);
    EXPECT_EQ(paintMethod->normalMargin_.GetY(), 548.5);
}

/**
 * @tc.name: SwiperIndicatorPaintPressIndicator001
 * @tc.desc: Test DotIndicatorPaintMethod SwiperIndicatorPaintPressIndicator
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperIndicatorPaintPressIndicator001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {
        model.SetDirection(Axis::VERTICAL);
    });
    auto indicatorNode = GetChildFrameNode(frameNode_, 4);
    RefPtr<DotIndicatorModifier> modifier = AceType::MakeRefPtr<DotIndicatorModifier>();
    RefPtr<DotIndicatorPaintMethod> paintMethod = AceType::MakeRefPtr<DotIndicatorPaintMethod>(modifier);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto paintProperty = AceType::MakeRefPtr<DotIndicatorPaintProperty>();
    paintProperty->Clone();
    paintProperty->Reset();
    paintProperty->UpdateColor(Color::RED);
    auto renderContext = frameNode_->GetRenderContext();
    PaintWrapper paintWrapper(renderContext, geometryNode, paintProperty);
    ASSERT_NE(paintMethod->dotIndicatorModifier_, nullptr);
    paintMethod->dotIndicatorModifier_->SetIsHover(true);

    /**
     * @tc.steps: step3. call PaintPressIndicator.
     * @tc.expected: paintMethod->dotIndicatorModifier_ is true.
     */
    paintMethod->PaintPressIndicator(&paintWrapper);
    EXPECT_TRUE(paintMethod->dotIndicatorModifier_->GetIsPressed());
    paintMethod->IsCustomSizeValue_ = true;
    paintMethod->PaintPressIndicator(&paintWrapper);
    EXPECT_TRUE(paintMethod->dotIndicatorModifier_->GetIsPressed());
}

/**
 * @tc.name: SwiperIndicatorPaintPressIndicator002
 * @tc.desc: Test DotIndicatorPaintMethod SwiperIndicatorPaintPressIndicator
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperIndicatorPaintPressIndicator002, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {
        model.SetDirection(Axis::VERTICAL);
    });
    auto indicatorNode = GetChildFrameNode(frameNode_, 4);
    RefPtr<DotIndicatorModifier> modifier = AceType::MakeRefPtr<DotIndicatorModifier>();
    RefPtr<DotIndicatorPaintMethod> paintMethod = AceType::MakeRefPtr<DotIndicatorPaintMethod>(modifier);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto paintProperty = AceType::MakeRefPtr<DotIndicatorPaintProperty>();
    paintProperty->Clone();
    paintProperty->Reset();
    paintProperty->UpdateColor(Color::RED);
    paintProperty->UpdateItemHeight(Dimension(10.f, DimensionUnit::PX));
    auto renderContext = frameNode_->GetRenderContext();
    PaintWrapper paintWrapper(renderContext, geometryNode, paintProperty);
    ASSERT_NE(paintMethod->dotIndicatorModifier_, nullptr);
    paintMethod->dotIndicatorModifier_->SetIsPressed(true);
    paintMethod->itemCount_ = 10;

    /**
     * @tc.steps: step3. call PaintPressIndicator.
     * @tc.expected: itemHalfSizes_->Get()[1] is 6.65 .
     */
    paintMethod->PaintPressIndicator(&paintWrapper);
    EXPECT_TRUE(NearEqual(paintMethod->dotIndicatorModifier_->itemHalfSizes_->Get()[1], 10.f * 0.5 * 1.33f));
    paintMethod->IsCustomSizeValue_ = true;
    paintMethod->PaintPressIndicator(&paintWrapper);
}

/**
 * @tc.name: SwiperIndicatorPaintHoverIndicator001
 * @tc.desc: Test DotIndicatorPaintMethod SwiperIndicatorPaintHoverIndicator
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperIndicatorPaintHoverIndicator001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {
        model.SetDirection(Axis::VERTICAL);
    });
    auto indicatorNode = GetChildFrameNode(frameNode_, 4);
    RefPtr<DotIndicatorModifier> modifier = AceType::MakeRefPtr<DotIndicatorModifier>();
    RefPtr<DotIndicatorPaintMethod> paintMethod = AceType::MakeRefPtr<DotIndicatorPaintMethod>(modifier);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto paintProperty = AceType::MakeRefPtr<DotIndicatorPaintProperty>();
    paintProperty->Clone();
    paintProperty->Reset();
    paintProperty->UpdateColor(Color::RED);
    auto renderContext = frameNode_->GetRenderContext();
    PaintWrapper paintWrapper(renderContext, geometryNode, paintProperty);
    paintMethod->hoverIndex_ = 10;
    paintMethod->currentIndex_ = 10;
    paintMethod->mouseClickIndex_ = 5;
    ASSERT_NE(paintMethod->dotIndicatorModifier_, nullptr);
    paintMethod->dotIndicatorModifier_->SetNormalToHoverIndex(5);
    paintMethod->dotIndicatorModifier_->SetIsPressed(true);

    /**
     * @tc.steps: step3. call PaintHoverIndicator.
     * @tc.expected: dotIndicatorModifier_->GetIsPressed is false.
     */
    paintMethod->PaintHoverIndicator(&paintWrapper);
    EXPECT_FALSE(paintMethod->dotIndicatorModifier_->GetIsPressed());
}

/**
 * @tc.name: SwiperIndicatorPaintHoverIndicator002
 * @tc.desc: Test DotIndicatorPaintMethod SwiperIndicatorPaintHoverIndicator
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperIndicatorPaintHoverIndicator002, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {
        model.SetDirection(Axis::VERTICAL);
    });
    auto indicatorNode = GetChildFrameNode(frameNode_, 4);
    RefPtr<DotIndicatorModifier> modifier = AceType::MakeRefPtr<DotIndicatorModifier>();
    RefPtr<DotIndicatorPaintMethod> paintMethod = AceType::MakeRefPtr<DotIndicatorPaintMethod>(modifier);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto paintProperty = AceType::MakeRefPtr<DotIndicatorPaintProperty>();
    paintProperty->Clone();
    paintProperty->Reset();
    paintProperty->UpdateColor(Color::RED);
    paintProperty->UpdateItemWidth(Dimension(20.f, DimensionUnit::PX));
    auto renderContext = frameNode_->GetRenderContext();
    PaintWrapper paintWrapper(renderContext, geometryNode, paintProperty);
    ASSERT_NE(paintMethod->dotIndicatorModifier_, nullptr);
    paintMethod->dotIndicatorModifier_->SetIsHover(true);

    /**
     * @tc.steps: step3. call PaintHoverIndicator.
     * @tc.expected: itemHalfSizes_->Get()[0] is 13.30 .
     */
    paintMethod->PaintHoverIndicator(&paintWrapper);
    EXPECT_TRUE(NearEqual(paintMethod->dotIndicatorModifier_->itemHalfSizes_->Get()[0], 20.f * 0.5 * 1.33f));
}

/**
 * @tc.name: SwiperDigitIndicatorLayoutAlgorithmMeasure001
 * @tc.desc: Test LayoutWrapper SwiperDigitIndicatorLayoutAlgorithmMeasure
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperDigitIndicatorLayoutAlgorithmMeasure001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {
        model.SetDirection(Axis::VERTICAL);
        model.SetIndicatorType(SwiperIndicatorType::DIGIT);
    });
    auto indicatorNode = GetChildFrameNode(frameNode_, 4);
    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    indicatorPattern->OnModifyDone();
    auto algorithm = indicatorPattern->CreateLayoutAlgorithm();
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(indicatorNode, geometryNode, indicatorNode->GetLayoutProperty());
    auto firstChild = AccessibilityManager::DynamicCast<FrameNode>(indicatorNode);
    RefPtr<GeometryNode> firstGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    firstGeometryNode->Reset();
    firstGeometryNode->SetFrameSize(SizeF(20.0, 20.0));
    RefPtr<LayoutWrapperNode> firstLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(firstChild, firstGeometryNode, firstChild->GetLayoutProperty());
    layoutWrapper.AppendChild(firstLayoutWrapper);
    auto lastChild = AccessibilityManager::DynamicCast<FrameNode>(indicatorNode);
    RefPtr<GeometryNode> lastGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    lastGeometryNode->Reset();
    lastGeometryNode->SetFrameSize(SizeF(30.0, 30.0));
    RefPtr<LayoutWrapperNode> lastLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(lastChild, lastGeometryNode, lastChild->GetLayoutProperty());
    layoutWrapper.AppendChild(lastLayoutWrapper);

    /**
     * @tc.steps: step3. call Measure.
     * @tc.expected: layoutWrapper MarginFrameSize is 66.00, 30.00
     */
    algorithm->Measure(&layoutWrapper);
    EXPECT_EQ(layoutWrapper.GetGeometryNode()->GetMarginFrameSize(), SizeF(66.00, 30.00));
}

/**
 * @tc.name: SwiperDigitIndicatorLayoutAlgorithmLayout002
 * @tc.desc: Test TxtParagraph SwiperDigitIndicatorLayoutAlgorithmLayout
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperDigitIndicatorLayoutAlgorithmLayout002, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {
        model.SetDirection(Axis::VERTICAL);
        model.SetIndicatorType(SwiperIndicatorType::DIGIT);
    });
    auto indicatorNode = GetChildFrameNode(frameNode_, 4);
    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    indicatorPattern->OnModifyDone();
    auto algorithm = indicatorPattern->CreateLayoutAlgorithm();
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    geometryNode->SetFrameSize(SizeF(720.f, 1136.f));
    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(indicatorNode, geometryNode, indicatorNode->GetLayoutProperty());
    auto firstChild = AccessibilityManager::DynamicCast<FrameNode>(indicatorNode);
    RefPtr<GeometryNode> firstGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    firstGeometryNode->Reset();
    firstGeometryNode->SetFrameSize(SizeF(20.0, 20.0));
    RefPtr<LayoutWrapperNode> firstLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(firstChild, firstGeometryNode, firstChild->GetLayoutProperty());
    layoutWrapper.AppendChild(firstLayoutWrapper);
    auto lastChild = AccessibilityManager::DynamicCast<FrameNode>(indicatorNode);
    RefPtr<GeometryNode> lastGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    lastGeometryNode->Reset();
    lastGeometryNode->SetFrameSize(SizeF(30.0, 30.0));
    RefPtr<LayoutWrapperNode> lastLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(lastChild, lastGeometryNode, lastChild->GetLayoutProperty());
    layoutWrapper.AppendChild(lastLayoutWrapper);

    /**
     * @tc.steps: step3. call Layout.
     * @tc.expected: firstLayoutWrapper MarginFrameOffset is 8.00, 558.00
     *               lastLayoutWrapper MarginFrameOffset is 682.00, 553.00
     */
    algorithm->Layout(&layoutWrapper);
    EXPECT_TRUE(IsEqual(firstLayoutWrapper->GetGeometryNode()->GetMarginFrameOffset(), OffsetF(8.00, 558.00)));
    EXPECT_TRUE(IsEqual(lastLayoutWrapper->GetGeometryNode()->GetMarginFrameOffset(), OffsetF(682.00, 553.00)));
}

/**
 * @tc.name: SwiperIndicatorHandleClick002
 * @tc.desc: Test SwiperIndicatorPattern SwiperIndicatorHandleClick
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperIndicatorHandleClick002, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {
        model.SetDirection(Axis::VERTICAL);
    });
    auto indicatorNode = GetChildFrameNode(frameNode_, 4);
    RefPtr<SwiperIndicatorPattern> indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    GestureEvent info;
    info.SetSourceDevice(SourceType::MOUSE);
    auto paintProperty = indicatorNode->GetPaintProperty<DotIndicatorPaintProperty>();
    paintProperty->UpdateItemWidth(Dimension(10, DimensionUnit::PX));
    paintProperty->UpdateItemHeight(Dimension(10, DimensionUnit::PX));
    indicatorPattern->mouseClickIndex_ = 5;
    pattern_->indicatorDoingAnimation_ = false;
    pattern_->currentIndex_ = 10;
    indicatorPattern->hoverPoint_.SetX(5.0);
    indicatorPattern->hoverPoint_.SetY(15.0);

    /**
     * @tc.steps: step3. call HandleClick.
     * @tc.expected: pattern_->indicatorDoingAnimation_ is true.
     */
    indicatorPattern->HandleClick(info);
    EXPECT_FALSE(pattern_->indicatorDoingAnimation_);
}

/**
 * @tc.name: SwiperIndicatorHandleClick003
 * @tc.desc: Test SwiperIndicatorPattern SwiperIndicatorHandleClick
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperIndicatorHandleClick003, TestSize.Level1)
{
    EXPECT_CALL(*MockPipelineContext::pipeline_, FlushUITasks).Times(1);
    CreateWithItem([](SwiperModelNG model) {
        model.SetDirection(Axis::VERTICAL);
    });
    auto indicatorNode = GetChildFrameNode(frameNode_, 4);
    RefPtr<SwiperIndicatorPattern> indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    GestureEvent info;
    info.SetSourceDevice(SourceType::TOUCH);
    auto paintProperty = indicatorNode->GetPaintProperty<DotIndicatorPaintProperty>();
    paintProperty->UpdateSize(Dimension(-1.0, DimensionUnit::PX));
    paintProperty->UpdateItemWidth(Dimension(-1.0, DimensionUnit::PX));
    pattern_->indicatorDoingAnimation_ = true;

    /**
     * @tc.steps: step3. call HandleClick.
     * @tc.expected: pattern_->indicatorDoingAnimation_ is false.
     */
    indicatorPattern->HandleClick(info);
    EXPECT_FALSE(pattern_->indicatorDoingAnimation_);
}

/**
 * @tc.name: SwiperInitIndicator001
 * @tc.desc: Test SwiperPattern SwiperInitIndicator
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperInitIndicator001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {
        model.SetDirection(Axis::VERTICAL);
    });
    auto indicatorNode = GetChildFrameNode(frameNode_, 4);

    /**
     * @tc.steps: step3. call InitIndicator.
     * @tc.expected: frameNode_ lastChild is SWIPER_INDICATOR_ETS_TAG
     */
    pattern_->InitIndicator();
    ASSERT_EQ(frameNode_->GetLastChild()->GetTag(), V2::SWIPER_INDICATOR_ETS_TAG);
}

/**
 * @tc.name: SwiperInitIndicator002
 * @tc.desc: Test SwiperPattern SwiperInitIndicator
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperInitIndicator002, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {
        model.SetDirection(Axis::VERTICAL);
    });
    auto indicatorNode = GetChildFrameNode(frameNode_, 4);
    auto layoutProperty = pattern_->GetLayoutProperty<SwiperLayoutProperty>();
    layoutProperty->UpdateShowIndicator(false);

    /**
     * @tc.steps: step3. call InitIndicator.
     * @tc.expected: frameNode_->GetLastChild is 1.
     */
    pattern_->InitIndicator();
    ASSERT_EQ(frameNode_->GetLastChild(), 1);
}

/**
 * @tc.name: SwiperInitIndicator005
 * @tc.desc: Test SwiperPattern SwiperInitIndicator
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperInitIndicator005, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {
        model.SetDirection(Axis::VERTICAL);
        model.SetIndicatorType(SwiperIndicatorType::DIGIT);
    });
    auto indicatorNode = GetChildFrameNode(frameNode_, 4);

    /**
     * @tc.steps: step3. call InitIndicator.
     * @tc.expected: frameNode_ lastChild is SWIPER_INDICATOR_ETS_TAG
     */
    pattern_->InitIndicator();
    ASSERT_EQ(frameNode_->GetLastChild()->GetTag(), V2::SWIPER_INDICATOR_ETS_TAG);
}

/**
 * @tc.name: SetDotIndicatorStyle001
 * @tc.desc: Test SwiperModelNG SetDotIndicatorStyle
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SetDotIndicatorStyle001, TestSize.Level1)
{
    SwiperParameters swiperParameters;
    swiperParameters.colorVal = Color(Color::BLUE);
    CreateWithItem([swiperParameters](SwiperModelNG model) { model.SetDotIndicatorStyle(swiperParameters); });
    ASSERT_EQ(pattern_->swiperParameters_->colorVal, swiperParameters.colorVal);
}

/**
 * @tc.name: SetDigitIndicatorStyle001
 * @tc.desc: Test SwiperModelNG SetDigitIndicatorStyle
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SetDigitIndicatorStyle001, TestSize.Level1)
{
    SwiperDigitalParameters digitalParameters;
    digitalParameters.fontColor = Color(Color::GREEN);
    CreateWithItem([digitalParameters](SwiperModelNG model) { model.SetDigitIndicatorStyle(digitalParameters); });
    ASSERT_EQ(pattern_->swiperDigitalParameters_->fontColor, digitalParameters.fontColor);
}

/**
 * @tc.name: SwiperDigitIndicatorLayoutAlgorithmLayout001
 * @tc.desc: Test DigitIndicatorLayoutAlgorithm SwiperDigitIndicatorLayoutAlgorithmLayout
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperDigitIndicatorLayoutAlgorithmLayout001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {
        model.SetDirection(Axis::VERTICAL);
        model.SetIndicatorType(SwiperIndicatorType::DIGIT);
    });
    auto indicatorNode = GetChildFrameNode(frameNode_, 4);
    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    auto algorithm = indicatorPattern->CreateLayoutAlgorithm();
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(indicatorNode, geometryNode, indicatorNode->GetLayoutProperty());

    /**
     * @tc.steps: step3. call Layout.
     * @tc.expected: indicatorNode children is empty.
     */
    algorithm->Layout(&layoutWrapper);
    auto hostNode = layoutWrapper.GetHostNode();
    auto children = hostNode->GetChildren();
    EXPECT_FALSE(children.empty());
}

/**
 * @tc.name: DotIndicatorModifier001
 * @tc.desc: Test DotIndicatorModifier
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, DotIndicatorModifier001, TestSize.Level1)
{
    DotIndicatorModifier dotIndicatorModifier;
    Testing::MockCanvas canvas;
    DrawingContext context { canvas, 100.f, 100.f };
    EXPECT_CALL(canvas, AttachBrush(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachBrush()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DrawRoundRect(_)).Times(AnyNumber());
    dotIndicatorModifier.indicatorMask_ = true;
    dotIndicatorModifier.currentIndex_ = 1.0;
    dotIndicatorModifier.normalToHoverIndex_ = 0.0;
    dotIndicatorModifier.hoverToNormalIndex_ = 0.0;
    dotIndicatorModifier.UpdateBackgroundColor(Color::BLUE);
    EXPECT_EQ(dotIndicatorModifier.backgroundColor_->Get().ToColor(), Color::BLUE);

    LinearVector<float> vectorBlackPointCenterX;
    vectorBlackPointCenterX.emplace_back(20.f);
    LinearVector<float> normalItemHalfSizes;
    // ITEM_HALF_WIDTH == SELECTED_ITEM_HALF_WIDTH, ITEM_HALF_HEIGHT == SELECTED_ITEM_HALF_HEIGHT.
    normalItemHalfSizes.emplace_back(20.f);
    normalItemHalfSizes.emplace_back(20.f);
    normalItemHalfSizes.emplace_back(20.f);
    normalItemHalfSizes.emplace_back(20.f);

    dotIndicatorModifier.UpdateShrinkPaintProperty(
        OffsetF(50.0, 60.0), normalItemHalfSizes, vectorBlackPointCenterX, { 0.f, 0.f });
    dotIndicatorModifier.onDraw(context);

    /**
     * @tc.expected: itemHalfSizes_->Get()[0] is 20.f.
     *               itemHalfSizes_->Get()[1] is 20.f.
     *               itemHalfSizes_->Get()[2] is 20.f.
     *               itemHalfSizes_->Get()[3] is 20.f.
     */
    EXPECT_EQ(dotIndicatorModifier.itemHalfSizes_->Get()[0], 20.f);
    EXPECT_EQ(dotIndicatorModifier.itemHalfSizes_->Get()[1], 20.f);
    EXPECT_EQ(dotIndicatorModifier.itemHalfSizes_->Get()[2], 20.f);
    EXPECT_EQ(dotIndicatorModifier.itemHalfSizes_->Get()[3], 20.f);

    // ITEM_HALF_WIDTH == SELECTED_ITEM_HALF_WIDTH, ITEM_HALF_HEIGHT < SELECTED_ITEM_HALF_HEIGHT.
    dotIndicatorModifier.normalToHoverIndex_ = 1.0;
    dotIndicatorModifier.hoverToNormalIndex_ = 0.0;
    LinearVector<float> normalItemHalfSizesSecond;
    normalItemHalfSizesSecond.emplace_back(20.f);
    normalItemHalfSizesSecond.emplace_back(25.f);
    normalItemHalfSizesSecond.emplace_back(20.f);
    normalItemHalfSizesSecond.emplace_back(15.f);
    dotIndicatorModifier.UpdateShrinkPaintProperty(
        OffsetF(50.0, 60.0), normalItemHalfSizesSecond, vectorBlackPointCenterX, { 0.f, 0.f });
    dotIndicatorModifier.onDraw(context);

    /**
     * @tc.expected: itemHalfSizes_->Get()[0] is 20.f.
     *               itemHalfSizes_->Get()[1] is 25.f.
     *               itemHalfSizes_->Get()[2] is 20.f.
     *               itemHalfSizes_->Get()[3] is 15.f.
     */
    EXPECT_EQ(dotIndicatorModifier.itemHalfSizes_->Get()[0], 20.f);
    EXPECT_EQ(dotIndicatorModifier.itemHalfSizes_->Get()[1], 25.f);
    EXPECT_EQ(dotIndicatorModifier.itemHalfSizes_->Get()[2], 20.f);
    EXPECT_EQ(dotIndicatorModifier.itemHalfSizes_->Get()[3], 15.f);
}

/**
 * @tc.name: DotIndicatorModifier002
 * @tc.desc: Test DotIndicatorModifier
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, DotIndicatorModifier002, TestSize.Level1)
{
    DotIndicatorModifier dotIndicatorModifier;
    Testing::MockCanvas canvas;
    DrawingContext context { canvas, 100.f, 100.f };
    EXPECT_CALL(canvas, AttachBrush(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachBrush()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DrawRoundRect(_)).Times(AnyNumber());
    dotIndicatorModifier.indicatorMask_ = true;
    dotIndicatorModifier.currentIndex_ = 1.0;
    dotIndicatorModifier.normalToHoverIndex_ = 0.0;
    dotIndicatorModifier.hoverToNormalIndex_ = 0.0;
    dotIndicatorModifier.UpdateBackgroundColor(Color::BLUE);
    EXPECT_EQ(dotIndicatorModifier.backgroundColor_->Get().ToColor(), Color::BLUE);
    LinearVector<float> vectorBlackPointCenterX;
    vectorBlackPointCenterX.emplace_back(20.f);

    // ITEM_HALF_WIDTH != SELECTED_ITEM_HALF_WIDTH, ITEM_HALF_HEIGHT > SELECTED_ITEM_HALF_HEIGHT.
    dotIndicatorModifier.normalToHoverIndex_ = 1.0;
    dotIndicatorModifier.hoverToNormalIndex_ = 1.0;
    LinearVector<float> normalItemHalfSizesThird;
    normalItemHalfSizesThird.emplace_back(20.f);
    normalItemHalfSizesThird.emplace_back(10.f);
    normalItemHalfSizesThird.emplace_back(30.f);
    normalItemHalfSizesThird.emplace_back(35.f);
    dotIndicatorModifier.UpdateShrinkPaintProperty(
        OffsetF(50.0, 60.0), normalItemHalfSizesThird, vectorBlackPointCenterX, { 0.f, 0.f });
    dotIndicatorModifier.onDraw(context);

    /**
     * @tc.expected: itemHalfSizes_->Get()[0] is 20.f.
     *               itemHalfSizes_->Get()[1] is 10.f.
     *               itemHalfSizes_->Get()[2] is 30.f.
     *               itemHalfSizes_->Get()[3] is 35.f.
     */
    EXPECT_EQ(dotIndicatorModifier.itemHalfSizes_->Get()[0], 20.f);
    EXPECT_EQ(dotIndicatorModifier.itemHalfSizes_->Get()[1], 10.f);
    EXPECT_EQ(dotIndicatorModifier.itemHalfSizes_->Get()[2], 30.f);
    EXPECT_EQ(dotIndicatorModifier.itemHalfSizes_->Get()[3], 35.f);
}

/**
 * @tc.name: DotIndicatorModifier003
 * @tc.desc: Test DotIndicatorModifier
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, DotIndicatorModifier003, TestSize.Level1)
{
    DotIndicatorModifier dotIndicatorModifier;
    Testing::MockCanvas canvas;
    DrawingContext context { canvas, 100.f, 100.f };
    EXPECT_CALL(canvas, AttachBrush(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachBrush()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DrawRoundRect(_)).Times(AnyNumber());
    dotIndicatorModifier.indicatorMask_ = true;
    dotIndicatorModifier.currentIndex_ = 1.0;
    dotIndicatorModifier.normalToHoverIndex_ = 0.0;
    dotIndicatorModifier.hoverToNormalIndex_ = 0.0;
    dotIndicatorModifier.UpdateBackgroundColor(Color::BLUE);
    EXPECT_EQ(dotIndicatorModifier.backgroundColor_->Get().ToColor(), Color::BLUE);

    LinearVector<float> vectorBlackPointCenterX;
    vectorBlackPointCenterX.emplace_back(20.f);
    // call the UpdateDilatePaintProperty to set property.
    dotIndicatorModifier.normalToHoverIndex_ = 1.0;
    dotIndicatorModifier.hoverToNormalIndex_ = 1.0;
    LinearVector<float> itemHalfSizes;
    itemHalfSizes.emplace_back(20.f);
    itemHalfSizes.emplace_back(10.f);
    itemHalfSizes.emplace_back(30.f);
    itemHalfSizes.emplace_back(35.f);
    dotIndicatorModifier.UpdatePressPaintProperty(itemHalfSizes, vectorBlackPointCenterX, { 0.f, 0.f });
    dotIndicatorModifier.onDraw(context);

    /**
     * @tc.expected: itemHalfSizes_->Get()[0] is 20.f.
     *               itemHalfSizes_->Get()[1] is 10.f.
     *               itemHalfSizes_->Get()[2] is 30.f.
     *               itemHalfSizes_->Get()[3] is 35.f.
     */
    EXPECT_EQ(dotIndicatorModifier.itemHalfSizes_->Get()[0], 20.f);
    EXPECT_EQ(dotIndicatorModifier.itemHalfSizes_->Get()[1], 10.f);
    EXPECT_EQ(dotIndicatorModifier.itemHalfSizes_->Get()[2], 30.f);
    EXPECT_EQ(dotIndicatorModifier.itemHalfSizes_->Get()[3], 35.f);
    // call the UpdateHoverPaintProperty to set property.
    dotIndicatorModifier.UpdateHoverPaintProperty(itemHalfSizes, vectorBlackPointCenterX, { 0.f, 0.f });
    dotIndicatorModifier.onDraw(context);

    /**
     * @tc.expected: itemHalfSizes_->Get()[0] is 20.f.
     *               itemHalfSizes_->Get()[1] is 10.f.
     *               itemHalfSizes_->Get()[2] is 30.f.
     *               itemHalfSizes_->Get()[3] is 35.f.
     */
    EXPECT_EQ(dotIndicatorModifier.itemHalfSizes_->Get()[0], 20.f);
    EXPECT_EQ(dotIndicatorModifier.itemHalfSizes_->Get()[1], 10.f);
    EXPECT_EQ(dotIndicatorModifier.itemHalfSizes_->Get()[2], 30.f);
    EXPECT_EQ(dotIndicatorModifier.itemHalfSizes_->Get()[3], 35.f);
}

/**
 * @tc.name: DotIndicatorModifier004
 * @tc.desc: Test PaintMask
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, DotIndicatorModifier004, TestSize.Level1)
{
    DotIndicatorModifier dotIndicatorModifier;
    Testing::MockCanvas canvas;
    DrawingContext context { canvas, 100.f, 100.f };
    EXPECT_CALL(canvas, AttachBrush(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachBrush()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DrawRoundRect(_)).Times(AnyNumber());
    EXPECT_CALL(canvas, Save()).Times(AnyNumber());
    EXPECT_CALL(canvas, DrawRect(_)).Times(AnyNumber());
    dotIndicatorModifier.indicatorMask_ = true;
    dotIndicatorModifier.currentIndex_ = 1.0;
    dotIndicatorModifier.normalToHoverIndex_ = 0.0;
    dotIndicatorModifier.hoverToNormalIndex_ = 0.0;
    dotIndicatorModifier.UpdateBackgroundColor(Color::BLUE);
    EXPECT_EQ(dotIndicatorModifier.backgroundColor_->Get().ToColor(), Color::BLUE);

    LinearVector<float> vectorBlackPointCenterX;
    vectorBlackPointCenterX.emplace_back(20.f);
    // call the UpdateDilatePaintProperty to set property.
    dotIndicatorModifier.normalToHoverIndex_ = 1.0;
    dotIndicatorModifier.hoverToNormalIndex_ = 1.0;
    LinearVector<float> itemHalfSizes;
    itemHalfSizes.emplace_back(20.f);
    itemHalfSizes.emplace_back(10.f);
    itemHalfSizes.emplace_back(30.f);
    itemHalfSizes.emplace_back(35.f);
    dotIndicatorModifier.UpdatePressPaintProperty(itemHalfSizes, vectorBlackPointCenterX, { 0.f, 0.f });
    dotIndicatorModifier.onDraw(context);
    dotIndicatorModifier.PaintMask(context);
}

/**
 * @tc.name: DotIndicatorModifier005
 * @tc.desc: Test PaintMask
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, DotIndicatorModifier005, TestSize.Level1)
{
    DotIndicatorModifier dotIndicatorModifier;
    Testing::MockCanvas canvas;
    DrawingContext context { canvas, 100.f, 100.f };
    EXPECT_CALL(canvas, AttachBrush(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachBrush()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DrawRoundRect(_)).Times(AnyNumber());
    dotIndicatorModifier.indicatorMask_ = true;
    dotIndicatorModifier.currentIndex_ = 1.0;
    dotIndicatorModifier.normalToHoverIndex_ = 0.0;
    dotIndicatorModifier.hoverToNormalIndex_ = 0.0;
    dotIndicatorModifier.UpdateBackgroundColor(Color::BLUE);
    EXPECT_EQ(dotIndicatorModifier.backgroundColor_->Get().ToColor(), Color::BLUE);

    LinearVector<float> vectorBlackPointCenterX;
    vectorBlackPointCenterX.emplace_back(20.f);
    // call the UpdateDilatePaintProperty to set property.
    dotIndicatorModifier.normalToHoverIndex_ = 1.0;
    dotIndicatorModifier.hoverToNormalIndex_ = 1.0;
    LinearVector<float> itemHalfSizes;
    itemHalfSizes.emplace_back(20.f);
    itemHalfSizes.emplace_back(10.f);
    itemHalfSizes.emplace_back(30.f);
    itemHalfSizes.emplace_back(35.f);
    dotIndicatorModifier.UpdatePressPaintProperty(itemHalfSizes, vectorBlackPointCenterX, { 0.f, 0.f });
    dotIndicatorModifier.isCustomSize_ = true;
    dotIndicatorModifier.onDraw(context);
    dotIndicatorModifier.isCustomSize_ = true;
    dotIndicatorModifier.axis_ = Axis::VERTICAL;
    dotIndicatorModifier.touchBottomType_ = TouchBottomType::START;
    dotIndicatorModifier.onDraw(context);
    dotIndicatorModifier.axis_ = Axis::VERTICAL;
    dotIndicatorModifier.touchBottomType_ = TouchBottomType::END;
    dotIndicatorModifier.onDraw(context);
}

/**
 * @tc.name: SwiperDistributedTest001
 * @tc.desc: Test the distributed capability of Swiper
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperDistributedTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and get pattern_.
     */
    CreateWithItem([](SwiperModelNG model) {});

    /**
     * @tc.steps: step2. Set Index.
     * @tc.expected: Function ProvideRestoreInfo is called.
     */
    layoutProperty_->UpdateIndex(1);
    std::string ret = pattern_->ProvideRestoreInfo();
    EXPECT_TRUE(ret == R"({"Index":1})");

    /**
     * @tc.steps: step3. Function OnRestoreInfo is called.
     * @tc.expected: Passing invalid & valid JSON format.
     */
    std::string restoreInfo_ = R"({"Index":1})";
    pattern_->OnRestoreInfo(restoreInfo_);
    EXPECT_EQ(layoutProperty_->GetIndexValue(0), 1);
    restoreInfo_ = R"({"Index":0})";
    pattern_->OnRestoreInfo(restoreInfo_);
    EXPECT_EQ(layoutProperty_->GetIndexValue(0), 0);
    restoreInfo_ = "invalid_json_string";
    pattern_->OnRestoreInfo(restoreInfo_);
    EXPECT_EQ(layoutProperty_->GetIndexValue(0), 0);
}

/**
 * @tc.name: ArrowOnModifyDone001
 * @tc.desc: Test ArrowOnModifyDone
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, ArrowOnModifyDone001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {
        model.SetDirection(Axis::VERTICAL);
        model.SetIndicatorType(SwiperIndicatorType::DIGIT);
        model.SetDisplayArrow(true); // show arrow
        model.SetHoverShow(false);
        model.SetArrowStyle(ARROW_PARAMETERS);
    });
    auto leftArrowNode = GetChildFrameNode(frameNode_, 5);
    auto leftArrowPattern = leftArrowNode->GetPattern<SwiperArrowPattern>();
    auto leftSwiperArrowLayoutProperty =
        AceType::DynamicCast<SwiperArrowLayoutProperty>(leftArrowPattern->GetSwiperArrowLayoutProperty());
    leftSwiperArrowLayoutProperty->UpdateBackgroundSize(3.0_vp);
    leftSwiperArrowLayoutProperty->UpdateArrowColor(Color::BLACK);
    leftSwiperArrowLayoutProperty->UpdateArrowSize(10.0_vp);
    /**
     * @tc.steps: step3. call OnModifyDone.
     * @tc.expected: leftArrowPattern->isFirstCreate_ is false.
     */
    auto buttonNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId() + 1, []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    leftArrowPattern->OnModifyDone();
    EXPECT_FALSE(leftArrowPattern->isFirstCreate_);
}

/**
 * @tc.name: ArrowOnModifyDone002
 * @tc.desc: Test ArrowOnModifyDone
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, ArrowOnModifyDone002, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {
        model.SetDirection(Axis::VERTICAL);
        model.SetIndicatorType(SwiperIndicatorType::DIGIT);
        model.SetDisplayArrow(true); // show arrow
        model.SetHoverShow(false);
        model.SetArrowStyle(ARROW_PARAMETERS);
    });
    auto leftArrowNode = GetChildFrameNode(frameNode_, 5);
    auto leftArrowPattern = leftArrowNode->GetPattern<SwiperArrowPattern>();
    auto leftSwiperArrowLayoutProperty =
        AceType::DynamicCast<SwiperArrowLayoutProperty>(leftArrowPattern->GetSwiperArrowLayoutProperty());
    leftSwiperArrowLayoutProperty->UpdateBackgroundSize(3.0_vp);
    leftSwiperArrowLayoutProperty->UpdateArrowColor(Color::BLACK);
    leftSwiperArrowLayoutProperty->UpdateArrowSize(10.0_vp);
    leftSwiperArrowLayoutProperty->UpdateIsShowBackground(true);
    leftSwiperArrowLayoutProperty->UpdateEnabled(false);
    leftSwiperArrowLayoutProperty->UpdateDirection(Axis::VERTICAL);
    /**
     * @tc.steps: step3. call OnModifyDone.
     * @tc.expected: imageSourceInfo->GetResourceId() is InternalResource::ResourceId::IC_PUBLIC_ARROW_UP_SVG.
     */
    auto buttonNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId() + 1, []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    leftArrowPattern->OnModifyDone();
    EXPECT_FALSE(leftArrowPattern->isFirstCreate_);

    leftArrowPattern->OnModifyDone();
    auto firstChild = AceType::DynamicCast<FrameNode>(leftArrowNode->GetFirstChild());
    EXPECT_NE(firstChild, nullptr);
    auto imageNode = AceType::DynamicCast<FrameNode>(firstChild->GetFirstChild());
    EXPECT_NE(imageNode, nullptr);
    auto imageSourceInfo = imageNode->GetLayoutProperty<ImageLayoutProperty>()->GetImageSourceInfo();
    EXPECT_NE(imageSourceInfo, std::nullopt);
    EXPECT_EQ(InternalResource::ResourceId::IC_PUBLIC_ARROW_UP_SVG, imageSourceInfo->GetResourceId());
}

/**
 * @tc.name: UpdateArrowContent001
 * @tc.desc: Test UpdateArrowContent
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, UpdateArrowContent001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {
        model.SetDirection(Axis::VERTICAL);
        model.SetIndicatorType(SwiperIndicatorType::DIGIT);
        model.SetDisplayArrow(true); // show arrow
        model.SetHoverShow(false);
        model.SetArrowStyle(ARROW_PARAMETERS);
    });
    auto leftArrowNode = GetChildFrameNode(frameNode_, 5);
    auto leftArrowPattern = leftArrowNode->GetPattern<SwiperArrowPattern>();
    auto leftSwiperArrowLayoutProperty =
        AceType::DynamicCast<SwiperArrowLayoutProperty>(leftArrowPattern->GetSwiperArrowLayoutProperty());
    leftSwiperArrowLayoutProperty->UpdateBackgroundSize(3.0_vp);
    leftSwiperArrowLayoutProperty->UpdateArrowColor(Color::BLACK);
    leftSwiperArrowLayoutProperty->UpdateArrowSize(10.0_vp);
    leftArrowPattern->OnModifyDone();
    EXPECT_FALSE(leftArrowPattern->isFirstCreate_);

    /**
     * @tc.steps: step3. call UpdateArrowContent.
     * @tc.expected: imageSourceInfo->GetResourceId() is InternalResource::ResourceId::IC_PUBLIC_ARROW_LEFT_SVG.
     */
    leftArrowPattern->UpdateArrowContent();
    auto firstChild = AceType::DynamicCast<FrameNode>(leftArrowNode->GetFirstChild());
    EXPECT_NE(firstChild, nullptr);
    auto imageNode = AceType::DynamicCast<FrameNode>(firstChild->GetFirstChild());
    EXPECT_NE(imageNode, nullptr);
    auto imageSourceInfo = imageNode->GetLayoutProperty<ImageLayoutProperty>()->GetImageSourceInfo();
    EXPECT_NE(imageSourceInfo, std::nullopt);
}

/**
 * @tc.name: UpdateArrowContent002
 * @tc.desc: Test UpdateArrowContent
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, UpdateArrowContent002, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {
        model.SetDirection(Axis::VERTICAL);
        model.SetIndicatorType(SwiperIndicatorType::DIGIT);
        model.SetDisplayArrow(true); // show arrow
        model.SetHoverShow(false);
        model.SetArrowStyle(ARROW_PARAMETERS);
    });
    auto rightArrowNode = GetChildFrameNode(frameNode_, 6);
    auto rightArrowPattern = rightArrowNode->GetPattern<SwiperArrowPattern>();
    EXPECT_NE(rightArrowPattern, nullptr);
    auto rightSwiperArrowLayoutProperty =
        AceType::DynamicCast<SwiperArrowLayoutProperty>(rightArrowPattern->GetSwiperArrowLayoutProperty());

    EXPECT_NE(rightSwiperArrowLayoutProperty, nullptr);
    rightSwiperArrowLayoutProperty->UpdateBackgroundSize(3.0_vp);
    rightSwiperArrowLayoutProperty->UpdateArrowColor(Color::BLACK);
    rightSwiperArrowLayoutProperty->UpdateArrowSize(10.0_vp);
    rightSwiperArrowLayoutProperty->UpdateDirection(Axis::VERTICAL);

    auto buttonNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId() + 1, []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    rightArrowPattern->OnModifyDone();
    EXPECT_FALSE(rightArrowPattern->isFirstCreate_);

    /**
     * @tc.steps: step3. call UpdateArrowContent.
     * @tc.expected: imageSourceInfo->GetResourceId() is InternalResource::ResourceId::IC_PUBLIC_ARROW_DOWN_SVG.
     */
    rightArrowPattern->UpdateArrowContent();
    auto firstChild = AceType::DynamicCast<FrameNode>(rightArrowNode->GetFirstChild());
    EXPECT_NE(firstChild, nullptr);
    auto imageNode = AceType::DynamicCast<FrameNode>(firstChild->GetFirstChild());
    EXPECT_NE(imageNode, nullptr);
    auto imageSourceInfo = imageNode->GetLayoutProperty<ImageLayoutProperty>()->GetImageSourceInfo();
    EXPECT_NE(imageSourceInfo, std::nullopt);
    EXPECT_EQ(InternalResource::ResourceId::IC_PUBLIC_ARROW_DOWN_SVG, imageSourceInfo->GetResourceId());
}

/**
 * @tc.name: SetButtonVisible001
 * @tc.desc: Test SetButtonVisible
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SetButtonVisible001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {
        model.SetDisplayArrow(true); // show arrow
        model.SetHoverShow(false);
        model.SetArrowStyle(ARROW_PARAMETERS);
    });
    auto leftArrowNode = GetChildFrameNode(frameNode_, 5);
    auto leftArrowPattern = leftArrowNode->GetPattern<SwiperArrowPattern>();
    auto leftSwiperArrowLayoutProperty = leftArrowPattern->GetSwiperArrowLayoutProperty();
    leftSwiperArrowLayoutProperty->UpdateBackgroundSize(3.0_vp);
    leftSwiperArrowLayoutProperty->UpdateArrowColor(Color::BLACK);
    leftSwiperArrowLayoutProperty->UpdateArrowSize(10.0_vp);
    auto buttonNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId() + 1, []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    leftArrowPattern->OnModifyDone();
    EXPECT_FALSE(leftArrowPattern->isFirstCreate_);

    /**
     * @tc.cases: case3.1 Selected point is not at both ends and RenderContext.SetVisible() will be called.
     */
    leftArrowPattern->index_ = 1;
    leftSwiperArrowLayoutProperty->UpdateHoverShow(true);
    leftArrowPattern->SetButtonVisible(false);

    /**
     * @tc.cases: case3.2 Selected point is not at both ends and RenderContext.SetVisible() will be called.
     */
    leftSwiperArrowLayoutProperty->UpdateHoverShow(false);
    leftArrowPattern->SetButtonVisible(false);

    /**
     * @tc.cases: case3.3 Selected point is first point and loop value is false RenderContext.SetVisible() will be
     * called..
     */
    leftArrowPattern->index_ = 0;
    leftSwiperArrowLayoutProperty->UpdateLoop(false);
    leftArrowPattern->SetButtonVisible(true);

    /**
     * @tc.cases: case3.4 Selected point is first point and loop value is true RenderContext.SetVisible() will be
     * called.
     */
    leftSwiperArrowLayoutProperty->UpdateLoop(true);
    leftArrowPattern->SetButtonVisible(false);
}

/**
 * @tc.name: ButtonOnHover001
 * @tc.desc: Test ButtonOnHover
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, ButtonOnHover001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {
        model.SetDisplayArrow(true); // show arrow
        model.SetHoverShow(false);
        model.SetArrowStyle(ARROW_PARAMETERS);
    });
    auto leftArrowNode = GetChildFrameNode(frameNode_, 5);
    auto leftArrowPattern = leftArrowNode->GetPattern<SwiperArrowPattern>();
    auto leftSwiperArrowLayoutProperty = leftArrowPattern->GetSwiperArrowLayoutProperty();
    leftSwiperArrowLayoutProperty->UpdateBackgroundSize(3.0_vp);
    leftSwiperArrowLayoutProperty->UpdateArrowColor(Color::BLACK);
    leftSwiperArrowLayoutProperty->UpdateArrowSize(10.0_vp);

    auto buttonNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId() + 1, []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    leftArrowPattern->OnModifyDone();
    ASSERT_NE(leftArrowPattern->isFirstCreate_, true);

    /**
     * @tc.cases: case3.1 isHover is true, RenderContext.BlendBgColor() will be called.
     */
    leftArrowPattern->isTouch_ = true;
    leftArrowPattern->ButtonOnHover(buttonNode, true);

    /**
     * @tc.cases: case3.2 isHover is true, isTouch is false, RenderContext.BlendBgColor() will be called.
     */
    leftArrowPattern->isTouch_ = false;
    leftArrowPattern->ButtonOnHover(buttonNode, true);

    /**
     * @tc.cases: case3.3 isHover is false, isTouch is true, RenderContext.BlendBgColor() will be called.
     */
    leftArrowPattern->isTouch_ = true;
    leftArrowPattern->ButtonOnHover(buttonNode, false);

    /**
     * @tc.cases: case3.4 isHover is false, isTouch is false, RenderContext.BlendBgColor() will be called.
     */
    leftArrowPattern->isTouch_ = false;
    leftArrowPattern->ButtonOnHover(buttonNode, false);
}

/**
 * @tc.name: ButtonTouchEvent001
 * @tc.desc: Test ButtonTouchEvent
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, ButtonTouchEvent001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {
        model.SetDisplayArrow(true); // show arrow
        model.SetHoverShow(false);
        model.SetArrowStyle(ARROW_PARAMETERS);
    });
    auto leftArrowNode = GetChildFrameNode(frameNode_, 5);
    auto leftArrowPattern = leftArrowNode->GetPattern<SwiperArrowPattern>();
    auto leftSwiperArrowLayoutProperty = leftArrowPattern->GetSwiperArrowLayoutProperty();
    leftSwiperArrowLayoutProperty->UpdateBackgroundSize(3.0_vp);
    leftSwiperArrowLayoutProperty->UpdateArrowColor(Color::BLACK);
    leftSwiperArrowLayoutProperty->UpdateArrowSize(10.0_vp);

    auto buttonNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId() + 1, []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    leftArrowPattern->OnModifyDone();
    ASSERT_NE(leftArrowPattern->isFirstCreate_, true);

    /**
     * @tc.cases: case3.1 isHover is true, isTouch is true, RenderContext.BlendBgColor() will be called.
     */
    leftArrowPattern->isHover_ = true;
    leftArrowPattern->ButtonTouchEvent(buttonNode, TouchType::DOWN);

    /**
     * @tc.cases: case3.2 isHover is true, isTouch is false, RenderContext.BlendBgColor() will be called.
     */
    leftArrowPattern->isHover_ = false;
    leftArrowPattern->ButtonTouchEvent(buttonNode, TouchType::DOWN);

    /**
     * @tc.cases: case3.3 isHover is false, isTouch is true, RenderContext.BlendBgColor() will be called.
     */
    leftArrowPattern->isHover_ = true;
    leftArrowPattern->ButtonTouchEvent(buttonNode, TouchType::UP);

    /**
     * @tc.cases: case3.4 isHover is false, isTouch is false, RenderContext.BlendBgColor() will be called.
     */
    leftArrowPattern->isHover_ = false;
    leftArrowPattern->ButtonTouchEvent(buttonNode, TouchType::CANCEL);
}

/**
 * @tc.name: SwiperArrowPatternButtonClickEvent001
 * @tc.desc: Test SwiperArrowPattern ButtonClickEvent
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperArrowPatternButtonClickEvent001, TestSize.Level2)
{
    CreateWithItem([](SwiperModelNG model) {
        model.SetDirection(Axis::VERTICAL);
        model.SetIndicatorType(SwiperIndicatorType::DIGIT);
        model.SetDisplayArrow(true); // show arrow
        model.SetHoverShow(false);
        model.SetArrowStyle(ARROW_PARAMETERS);
    });
    auto leftArrowNode = GetChildFrameNode(frameNode_, 5);
    auto rightArrowNode = GetChildFrameNode(frameNode_, 6);
    auto leftArrowPattern = leftArrowNode->GetPattern<SwiperArrowPattern>();
    auto rightArrowPattern = rightArrowNode->GetPattern<SwiperArrowPattern>();

    /**
     * @tc.steps: step3. call ButtonClickEvent.
     * @tc.expected: isOnButtonClick is true.
     */
    auto swiperController = pattern_->GetSwiperController();
    auto isOnButtonClick = false;
    swiperController->SetShowPrevImpl([&isOnButtonClick]() { isOnButtonClick = true; });
    leftArrowPattern->ButtonClickEvent();
    EXPECT_TRUE(isOnButtonClick);

    isOnButtonClick = false;
    swiperController->SetShowNextImpl([&isOnButtonClick]() { isOnButtonClick = true; });
    rightArrowPattern->ButtonClickEvent();
    EXPECT_TRUE(isOnButtonClick);
}

/**
 * @tc.name: SwiperPatternCreateLayoutAlgorithm001
 * @tc.desc: CreateLayoutAlgorithm
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternCreateLayoutAlgorithm001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    pattern_->jumpIndex_ = 0;
    pattern_->targetIndex_ = 1;
    layoutProperty_->UpdateLoop(true);
    struct SwiperItemInfo swiperItemInfo;
    swiperItemInfo.startPos = 1.0f;

    /**
     * @tc.steps: step3. call CreateLayoutAlgorithm.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            pattern_->CreateLayoutAlgorithm();
            layoutProperty_->UpdateLoop(false);
        }
        pattern_->itemPosition_.emplace(std::make_pair(1, swiperItemInfo));
    }
}

/**
 * @tc.name: SwiperPatternOnIndexChange001
 * @tc.desc: OnIndexChange
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternOnIndexChange001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {
        model.SetDisplayArrow(true); // show arrow
        model.SetHoverShow(false);
        model.SetArrowStyle(ARROW_PARAMETERS);
    });
    layoutProperty_->UpdateShowIndicator(false);
    pattern_->leftButtonId_.reset();
    ASSERT_EQ(pattern_->TotalCount(), 6);
    pattern_->oldIndex_ = 1;
    layoutProperty_->UpdateIndex(2);

    /**
     * @tc.steps: step3. call OnIndexChange.
     * @tc.expected: Related function runs ok.
     */
    pattern_->OnIndexChange();
}

/**
 * @tc.name: SwiperPatternGetLoopIndex001
 * @tc.desc: GetLoopIndex
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternGetLoopIndex001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {
        model.SetDisplayArrow(true); // show arrow
        model.SetHoverShow(false);
        model.SetArrowStyle(ARROW_PARAMETERS);
    });

    /**
     * @tc.steps: step3. call GetLoopIndex.
     * @tc.expected: Related function runs ok.
     */
    int32_t originalIndex = -1;
    pattern_->GetLoopIndex(originalIndex);
}

/**
 * @tc.name: SwiperPatternOnDirtyLayoutWrapperSwap001
 * @tc.desc: OnDirtyLayoutWrapperSwap
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternOnDirtyLayoutWrapperSwap001, TestSize.Level1)
{
    EXPECT_CALL(*MockPipelineContext::pipeline_, FlushUITasks).Times(3);
    CreateWithItem([](SwiperModelNG model) {
        model.SetDisplayArrow(true); // show arrow
        model.SetHoverShow(false);
        model.SetArrowStyle(ARROW_PARAMETERS);
    });
    auto indicatorNode = GetChildFrameNode(frameNode_, 4);
    auto firstChild = AccessibilityManager::DynamicCast<FrameNode>(indicatorNode);
    RefPtr<GeometryNode> firstGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    firstGeometryNode->Reset();
    firstGeometryNode->SetFrameSize(SizeF(20.0, 20.0));
    auto dirty = AceType::MakeRefPtr<LayoutWrapperNode>(firstChild, firstGeometryNode, firstChild->GetLayoutProperty());
    struct DirtySwapConfig config;
    pattern_->isInit_ = true;
    config.skipMeasure = true;
    config.skipLayout = true;

    /**
     * @tc.steps: step2. call OnDirtyLayoutWrapperSwap.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            pattern_->OnDirtyLayoutWrapperSwap(dirty, config);
            pattern_->isInit_ = false;
            if (i == 1) {
                config.skipLayout = false;
                continue;
            }
            config.skipLayout = true;
        }
        config.skipMeasure = false;
    }
    struct SwiperItemInfo swiperItemInfo1;
    struct SwiperItemInfo swiperItemInfo2;
    struct SwiperItemInfo swiperItemInfo3;
    struct SwiperItemInfo swiperItemInfo4;
    swiperItemInfo1.startPos = -1.0f;
    swiperItemInfo1.endPos = -1.0f;
    swiperItemInfo2.startPos = 1.0f;
    swiperItemInfo2.endPos = -1.0f;
    swiperItemInfo3.startPos = -1.0f;
    swiperItemInfo3.endPos = 0.0f;
    swiperItemInfo4.startPos = 1.0f;
    swiperItemInfo4.endPos = 1.0f;

    auto swiperLayoutAlgorithm = AceType::DynamicCast<SwiperLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    dirty->layoutAlgorithm_ = AceType::MakeRefPtr<LayoutAlgorithmWrapper>(swiperLayoutAlgorithm);
    dirty->layoutAlgorithm_->layoutAlgorithm_ = AceType::MakeRefPtr<SwiperLayoutAlgorithm>();
    ASSERT_NE(dirty->GetLayoutAlgorithm(), nullptr);
    ASSERT_NE(AceType::DynamicCast<SwiperLayoutAlgorithm>(dirty->GetLayoutAlgorithm()->GetLayoutAlgorithm()), nullptr);
    AceType::DynamicCast<SwiperLayoutAlgorithm>(dirty->GetLayoutAlgorithm()->GetLayoutAlgorithm())
        ->itemPosition_.emplace(std::make_pair(1, swiperItemInfo1));
    AceType::DynamicCast<SwiperLayoutAlgorithm>(dirty->GetLayoutAlgorithm()->GetLayoutAlgorithm())
        ->itemPosition_.emplace(std::make_pair(2, swiperItemInfo2));
    AceType::DynamicCast<SwiperLayoutAlgorithm>(dirty->GetLayoutAlgorithm()->GetLayoutAlgorithm())
        ->itemPosition_.emplace(std::make_pair(3, swiperItemInfo3));
    AceType::DynamicCast<SwiperLayoutAlgorithm>(dirty->GetLayoutAlgorithm()->GetLayoutAlgorithm())
        ->itemPosition_.emplace(std::make_pair(4, swiperItemInfo4));
    pattern_->OnDirtyLayoutWrapperSwap(dirty, config);
    pattern_->indicatorDoingAnimation_ = false;
    pattern_->jumpIndex_ = 1;

    for (int i = 0; i <= 1; i++) {
        pattern_->OnDirtyLayoutWrapperSwap(dirty, config);
        pattern_->indicatorDoingAnimation_ = true;
        pattern_->targetIndex_ = 1;
        AceType::DynamicCast<SwiperLayoutAlgorithm>(dirty->GetLayoutAlgorithm()->GetLayoutAlgorithm())
            ->itemPosition_.emplace(std::make_pair(1, swiperItemInfo1));
    }

    AceType::DynamicCast<SwiperPaintProperty>(frameNode_->paintProperty_)->UpdateEdgeEffect(EdgeEffect::SPRING);
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            pattern_->OnDirtyLayoutWrapperSwap(dirty, config);
            if (i == 1) {
                AceType::DynamicCast<SwiperPaintProperty>(frameNode_->paintProperty_)
                    ->UpdateEdgeEffect(EdgeEffect::FADE);
                continue;
            }
            AceType::DynamicCast<SwiperPaintProperty>(frameNode_->paintProperty_)->UpdateEdgeEffect(EdgeEffect::SPRING);
        }
        AceType::DynamicCast<SwiperLayoutProperty>(frameNode_->layoutProperty_)->padding_ =
            std::make_unique<PaddingProperty>();
    }
}

/**
 * @tc.name: SwiperPatternSwipeTo001
 * @tc.desc: SwipeTo
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternSwipeTo001, TestSize.Level1)
{
    EXPECT_CALL(*MockPipelineContext::pipeline_, FlushUITasks).Times(2);
    CreateWithItem([](SwiperModelNG model) {
        model.SetDisplayArrow(true); // show arrow
        model.SetHoverShow(false);
        model.SetArrowStyle(ARROW_PARAMETERS);
    });
    int32_t index = -1;
    layoutProperty_->UpdateLoop(true);
    pattern_->currentIndex_ = 1;
    pattern_->leftButtonId_.reset();
    pattern_->rightButtonId_.reset();
    pattern_->GetLayoutProperty<SwiperLayoutProperty>()->UpdateShowIndicator(false);
    layoutProperty_->UpdateMinSize(Dimension(1));
    layoutProperty_->UpdateDisplayMode(SwiperDisplayMode::AUTO_LINEAR);

    /**
     * @tc.steps: step2. call SwipeTo.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            pattern_->SwipeTo(index);
            if (i == 1) {
                frameNode_->GetPaintProperty<SwiperPaintProperty>()->UpdateDuration(0);
                continue;
            }
            pattern_->itemPosition_.emplace(std::make_pair(1, SwiperItemInfo { 1, 2 }));
            pattern_->itemPosition_.emplace(std::make_pair(-2, SwiperItemInfo { 1, 2 }));
            frameNode_->GetPaintProperty<SwiperPaintProperty>()->UpdateDuration(400);
        }
        pattern_->isVisible_ = true;
    }

    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            pattern_->SwipeTo(index);
            if (i == 1) {
                            pattern_->rightButtonId_ = 1;
                continue;
            }
            pattern_->SwipeTo(index);
            index = 2;
        }
        index = -1;
    }

    pattern_->rightButtonId_.reset();
    pattern_->GetLayoutProperty<SwiperLayoutProperty>()->UpdateDisplayCount(1);
    pattern_->GetLayoutProperty<SwiperLayoutProperty>()->UpdateLoop(false);
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            pattern_->SwipeTo(index);
            if (i == 1) {
                break;
            }
            pattern_->GetLayoutProperty<SwiperLayoutProperty>()->UpdateLoop(true);
            pattern_->currentIndex_ = 0;
        }
        pattern_->currentIndex_ = 1;
    }

    pattern_->usePropertyAnimation_ = true;
    pattern_->SwipeTo(index);
    layoutProperty_->UpdateIsCustomAnimation(true);
    pattern_->SwipeTo(1);
    pattern_->TriggerCustomContentTransitionEvent(0, 1);
    pattern_->OnCustomAnimationFinish(0, 1, false);
}

/**
 * @tc.name: SwiperPatternShowNext001
 * @tc.desc: ShowNext
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternShowNext001, TestSize.Level1)
{
    EXPECT_CALL(*MockPipelineContext::pipeline_, FlushUITasks).Times(12);
    CreateWithItem([](SwiperModelNG model) {
        model.SetDisplayArrow(true); // show arrow
        model.SetHoverShow(false);
        model.SetArrowStyle(ARROW_PARAMETERS);
    });
    ASSERT_EQ(pattern_->TotalCount(), 4);
    layoutProperty_->UpdateLoop(true);
    layoutProperty_->UpdateDisplayCount(-1);
    layoutProperty_->UpdateMinSize(Dimension(-1));
    layoutProperty_->UpdateDisplayMode(SwiperDisplayMode::AUTO_LINEAR);
    pattern_->currentIndex_ = 1;
    pattern_->preTargetIndex_ = -1;
    layoutProperty_->UpdateShowIndicator(false);
    pattern_->leftButtonId_.reset();

    /**
     * @tc.steps: step2. call ShowNext.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            pattern_->ShowNext();
            if (i == 1) {
                pattern_->preTargetIndex_ = 0;
                ASSERT_EQ(pattern_->GetLoopIndex(pattern_->preTargetIndex_.value()), 0);
                continue;
            }
            pattern_->itemPosition_.emplace(std::make_pair(1, SwiperItemInfo { 1, 2 }));
            pattern_->itemPosition_.emplace(std::make_pair(-3, SwiperItemInfo { 1, 2 }));
            pattern_->preTargetIndex_ = -1;
            EXPECT_EQ(pattern_->TotalCount(), 6);
            EXPECT_EQ(pattern_->GetLoopIndex(pattern_->preTargetIndex_.value()), 5);
        }
        layoutProperty_->UpdateLoop(false);
        ASSERT_FALSE(pattern_->IsLoop());
    }

    pattern_->preTargetIndex_.reset();
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            pattern_->ShowNext();
            if (i == 1) {
                pattern_->currentIndex_ = 5;
                continue;
            }
            pattern_->currentIndex_ = 1;
        }
        layoutProperty_->UpdateLoop(false);
        ASSERT_FALSE(pattern_->IsLoop());
    }
    layoutProperty_->UpdateLoop(true);
    pattern_->rightButtonId_.reset();
    layoutProperty_->UpdateDisplayCount(1);
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            pattern_->ShowNext();
            if (i == 1) {
                layoutProperty_->UpdateDisplayCount(1);
                continue;
            }
            layoutProperty_->UpdateDisplayCount(0);
        }
        }
    for (int i = 0; i <= 1; i++) {
        pattern_->ShowNext();
        pattern_->isVisible_ = false;
    }
}

/**
 * @tc.name: SwiperPatternShowPrevious001
 * @tc.desc: ShowPrevious
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternShowPrevious001, TestSize.Level1)
{
    EXPECT_CALL(*MockPipelineContext::pipeline_, FlushUITasks).Times(75);
    CreateWithItem([](SwiperModelNG model) {});
    layoutProperty_->UpdateShowIndicator(false);
    pattern_->currentIndex_ = 0;
    pattern_->preTargetIndex_ = -1;

    layoutProperty_->UpdateLoop(true);
    layoutProperty_->UpdateDisplayCount(-3);
    layoutProperty_->UpdateMinSize(Dimension(-1));
    layoutProperty_->UpdateDisplayMode(SwiperDisplayMode::AUTO_LINEAR);
    EXPECT_EQ(pattern_->TotalDisPlayCount(), 1);
    EXPECT_TRUE(pattern_->IsLoop());

    /**
     * @tc.steps: step2. call ShowPrevious.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            pattern_->ShowPrevious();
            if (i == 1) {
                pattern_->preTargetIndex_ = 0;
                ASSERT_EQ(pattern_->GetLoopIndex(pattern_->preTargetIndex_.value()), 0);
                continue;
            }
            pattern_->itemPosition_.emplace(std::make_pair(1, SwiperItemInfo { 1, 2 }));
            pattern_->itemPosition_.emplace(std::make_pair(-3, SwiperItemInfo { 1, 2 }));
            pattern_->preTargetIndex_ = 1;
            EXPECT_EQ(pattern_->GetLoopIndex(pattern_->preTargetIndex_.value()), 1);
        }
        layoutProperty_->UpdateLoop(false);
        ASSERT_FALSE(pattern_->IsLoop());
    }

    pattern_->preTargetIndex_.reset();
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            pattern_->ShowPrevious();
            if (i == 1) {
                pattern_->currentIndex_ = 1;
                continue;
            }
            pattern_->currentIndex_ = 0;
        }
        layoutProperty_->UpdateLoop(false);
        ASSERT_FALSE(pattern_->IsLoop());
    }

    pattern_->preTargetIndex_ = 1;
    layoutProperty_->UpdateLoop(true);
    pattern_->GetLayoutProperty<SwiperLayoutProperty>()->UpdateDisplayCount(1);
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            pattern_->ShowPrevious();
            pattern_->preTargetIndex_.reset();
        }
        pattern_->isVisible_ = false;
    }

    layoutProperty_->UpdateLoop(true);
    pattern_->rightButtonId_.reset();
    pattern_->leftButtonId_.reset();
    layoutProperty_->UpdateDisplayCount(1);
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            pattern_->ShowPrevious();
            if (i == 1) {
                layoutProperty_->UpdateDisplayCount(1);
                continue;
            }
            layoutProperty_->UpdateDisplayCount(0);
        }
        }
}

/**
 * @tc.name: SwiperPatternFinishAnimation001
 * @tc.desc: FinishAnimation
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternFinishAnimation001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});

    /**
     * @tc.steps: step2. call FinishAnimation.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            pattern_->FinishAnimation();
            pattern_->usePropertyAnimation_ = true;
            pattern_->isUserFinish_ = true;
        }
        pattern_->swiperController_->SetFinishCallback([]() {});
    }
}

/**
 * @tc.name: SwiperPatternInitSwiperController001
 * @tc.desc: InitSwiperController
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternInitSwiperController001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    pattern_->swiperController_->showPrevImpl_ = nullptr;

    /**
     * @tc.steps: step2. call InitSwiperController.
     * @tc.expected: Related function runs ok.
     */
    pattern_->InitSwiperController();
    pattern_->swiperController_->swipeToImpl_(0, true);
    pattern_->swiperController_->swipeToWithoutAnimationImpl_(0);
    pattern_->swiperController_->showNextImpl_();
    pattern_->swiperController_->showPrevImpl_();
    pattern_->swiperController_->changeIndexImpl_(0, true);
    pattern_->swiperController_->finishImpl_();
    std::set<int32_t> indexSet;
    pattern_->swiperController_->preloadItemsImpl_(indexSet);
    indexSet.insert(1);
    pattern_->swiperController_->preloadItemsImpl_(indexSet);
}

/**
 * @tc.name: SwiperPatternAutoPlay001
 * @tc.desc: StopAutoPlay and StartAutoPlay
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternAutoPlay001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    frameNode_->GetPaintProperty<SwiperPaintProperty>()->UpdateAutoPlay(true);
    layoutProperty_->UpdateLoop(true);
    pattern_->isVisible_ = true;

    /**
     * @tc.steps: step2. call InitTouchEvent.
     * @tc.expected: Related function runs ok.
     */
    pattern_->StopAutoPlay();
    pattern_->StartAutoPlay();
}

/**
 * @tc.name: SwiperPatternHandleTouchUp001
 * @tc.desc: HandleTouchUp
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternHandleTouchUp001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    pattern_->controller_ = AceType::MakeRefPtr<Animator>();
    ASSERT_NE(pattern_->controller_, nullptr);
    pattern_->controller_->status_ = Animator::Status::PAUSED;

    /**
     * @tc.steps: step2. call HandleTouchUp.
     * @tc.expected: Related function runs ok.
     */
    pattern_->HandleTouchUp();
}

/**
 * @tc.name: SwiperPatternOnVisibleChange001
 * @tc.desc: OnVisibleChange
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternOnVisibleChange001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    pattern_->isInit_ = false;
    pattern_->isWindowShow_ = false;

    /**
     * @tc.steps: step2. call OnVisibleChange.
     * @tc.expected: Related function runs ok.
     */
    pattern_->OnVisibleChange(true);
}

/**
 * @tc.name: SwiperPatternPlayFadeAnimation001
 * @tc.desc: PlayFadeAnimation
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternPlayFadeAnimation001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    pattern_->fadeOffset_ = 0.0f;
    pattern_->fadeAnimationIsRunning_ = true;
    pattern_->PlayFadeAnimation();
    EXPECT_FALSE(pattern_->fadeAnimationIsRunning_);
}

/**
 * @tc.name: SwiperPatternPlayFadeAnimation002
 * @tc.desc: PlayFadeAnimation
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternPlayFadeAnimation002, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    pattern_->fadeOffset_ = 100.0f;
    pattern_->fadeAnimationIsRunning_ = true;
    pattern_->PlayFadeAnimation();
    EXPECT_FALSE(pattern_->fadeAnimationIsRunning_);
    pattern_->fadeOffset_ = -100.0f;
    pattern_->fadeAnimationIsRunning_ = true;
    pattern_->PlayFadeAnimation();
    EXPECT_FALSE(pattern_->fadeAnimationIsRunning_);
}

/**
 * @tc.name: SwiperPatternStopFadeAnimation001
 * @tc.desc: StopFadeAnimation
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternStopFadeAnimation001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    pattern_->fadeAnimationIsRunning_ = true;
    pattern_->StopFadeAnimation();
    EXPECT_FALSE(pattern_->fadeAnimationIsRunning_);
}

/**
 * @tc.name: SwiperPatternPlayPropertyTranslateAnimation001
 * @tc.desc: PlayPropertyTranslateAnimation
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternPlayPropertyTranslateAnimation001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    layoutProperty_->UpdateDirection(Axis::HORIZONTAL);
    float translate = 0.1f;
    int32_t nextIndex = 1;
    float velocity = 0.2f;
    struct SwiperItemInfo swiperItemInfo1;
    swiperItemInfo1.startPos = -1.0f;
    swiperItemInfo1.endPos = -1.0f;
    swiperItemInfo1.node = nullptr;
    struct SwiperItemInfo swiperItemInfo2;
    swiperItemInfo2.startPos = -1.0f;
    swiperItemInfo2.endPos = -1.0f;
    swiperItemInfo2.node =
        FrameNode::GetOrCreateFrameNode("Swiper", 0, []() { return AceType::MakeRefPtr<SwiperPattern>(); });
    pattern_->itemPosition_.emplace(std::make_pair(1, swiperItemInfo1));
    pattern_->itemPosition_.emplace(std::make_pair(2, swiperItemInfo2));

    /**
     * @tc.steps: step2. call PlayPropertyTranslateAnimation.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        pattern_->PlayPropertyTranslateAnimation(translate, nextIndex, velocity);
        layoutProperty_->UpdateDirection(Axis::VERTICAL);
    }
}

/**
 * @tc.name: SwiperPatternUpdateOffsetAfterPropertyAnimation001
 * @tc.desc: UpdateOffsetAfterPropertyAnimation
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternUpdateOffsetAfterPropertyAnimation001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    float offset = 0.1f;

    /**
     * @tc.steps: step2. call UpdateOffsetAfterPropertyAnimation.
     * @tc.expected: Related function runs ok.
     */
    pattern_->UpdateOffsetAfterPropertyAnimation(offset);
}

/**
 * @tc.name: SwiperPatternOnPropertyTranslateAnimationFinish001
 * @tc.desc: OnPropertyTranslateAnimationFinish
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternOnPropertyTranslateAnimationFinish001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    auto offset = OffsetF(0.1f, 0.2f);
    pattern_->usePropertyAnimation_ = false;
    struct SwiperItemInfo swiperItemInfo1;
    swiperItemInfo1.startPos = -1.0f;
    swiperItemInfo1.endPos = -1.0f;
    swiperItemInfo1.node = nullptr;
    struct SwiperItemInfo swiperItemInfo2;
    swiperItemInfo2.startPos = -1.0f;
    swiperItemInfo2.endPos = -1.0f;
    swiperItemInfo2.node =
        FrameNode::GetOrCreateFrameNode("Swiper", 0, []() { return AceType::MakeRefPtr<SwiperPattern>(); });
    pattern_->itemPosition_.emplace(std::make_pair(1, swiperItemInfo1));
    pattern_->itemPosition_.emplace(std::make_pair(2, swiperItemInfo2));
    ASSERT_NE(pattern_->itemPosition_.rbegin()->second.node, nullptr);

    /**
     * @tc.steps: step2. call OnPropertyTranslateAnimationFinish.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        pattern_->OnPropertyTranslateAnimationFinish(offset);
        pattern_->usePropertyAnimation_ = true;
    }
}

/**
 * @tc.name: SwiperPatternStopPropertyTranslateAnimation001
 * @tc.desc: StopPropertyTranslateAnimation
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternStopPropertyTranslateAnimation001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    pattern_->usePropertyAnimation_ = false;
    struct SwiperItemInfo swiperItemInfo1;
    swiperItemInfo1.startPos = -1.0f;
    swiperItemInfo1.endPos = -1.0f;
    swiperItemInfo1.node = nullptr;
    struct SwiperItemInfo swiperItemInfo2;
    swiperItemInfo2.startPos = -1.0f;
    swiperItemInfo2.endPos = -1.0f;
    swiperItemInfo2.node =
        FrameNode::GetOrCreateFrameNode("Swiper", 0, []() { return AceType::MakeRefPtr<SwiperPattern>(); });
    pattern_->itemPosition_.emplace(std::make_pair(1, swiperItemInfo1));
    pattern_->itemPosition_.emplace(std::make_pair(2, swiperItemInfo2));
    ASSERT_NE(pattern_->itemPosition_.rbegin()->second.node, nullptr);

    /**
     * @tc.steps: step2. call StopPropertyTranslateAnimation.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        pattern_->StopPropertyTranslateAnimation(false);
        pattern_->usePropertyAnimation_ = true;
    }
}

/**
 * @tc.name: SwiperPatternGetCurveIncludeMotion001
 * @tc.desc: GetCurveIncludeMotion
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternGetCurveIncludeMotion001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    frameNode_->GetPaintProperty<SwiperPaintProperty>()->UpdateCurve(nullptr);
    float velocity = 0.1f;
    float mass = 0.1f;
    float stiffness = 0.2f;
    float damping = 0.3f;
    auto curve1 = AceType::MakeRefPtr<SpringCurve>(velocity, mass, stiffness, damping);
    auto curve2 = AceType::MakeRefPtr<InterpolatingSpring>(velocity, mass, stiffness, damping);

    /**
     * @tc.steps: step2. call GetCurveIncludeMotion.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            for (int k = 0; k <= 1; k++) {
                pattern_->GetCurveIncludeMotion();
                if (i == 1) {
                    curve2->UpdateVelocity(-0.1f);
                    continue;
                }
                frameNode_->GetPaintProperty<SwiperPaintProperty>()->UpdateCurve(curve1);
                curve1->UpdateVelocity(-0.1f);
            }
            curve1->UpdateVelocity(0.1f);
        }
        frameNode_->GetPaintProperty<SwiperPaintProperty>()->UpdateCurve(curve2);
        curve2->UpdateVelocity(0.1f);
    }
}

/**
 * @tc.name: SwiperPatternPlayIndicatorTranslateAnimation001
 * @tc.desc: PlayIndicatorTranslateAnimation
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternPlayIndicatorTranslateAnimation001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    pattern_->indicatorId_.reset();
    float translate = 0.1f;

    /**
     * @tc.steps: step2. call PlayIndicatorTranslateAnimation.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            pattern_->PlayIndicatorTranslateAnimation(translate);
            if (i == 1) {
                break;
            }
            pattern_->indicatorId_ = 1;
        }
    }
}

/**
 * @tc.name: SwiperPatternPlayTranslateAnimation001
 * @tc.desc: PlayTranslateAnimation
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternPlayTranslateAnimation001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    float startPos = 0.1f;
    float endPos = 0.2f;
    int32_t nextIndex = 1;
    bool restartAutoPlay = true;
    float velocity = 0.1f;
    float mass = 0.1f;
    float stiffness = 0.2f;
    float damping = 0.3f;
    pattern_->controller_ = nullptr;
    auto curve1 = AceType::MakeRefPtr<SpringCurve>(velocity, mass, stiffness, damping);

    /**
     * @tc.steps: step2. call PlayTranslateAnimation.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        pattern_->PlayTranslateAnimation(startPos, endPos, nextIndex, restartAutoPlay, velocity);
        pattern_->controller_ = AceType::MakeRefPtr<Animator>();
        frameNode_->GetPaintProperty<SwiperPaintProperty>()->UpdateCurve(curve1);
    }
}

/**
 * @tc.name: SwiperPatternGetRemainingOffset001
 * @tc.desc: GetRemainingOffset
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternGetRemainingOffset001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    layoutProperty_->UpdateLoop(true);
    struct SwiperItemInfo swiperItemInfo1;
    swiperItemInfo1.startPos = -1.0f;
    swiperItemInfo1.endPos = -1.0f;
    pattern_->itemPosition_.emplace(std::make_pair(1, swiperItemInfo1));

    /**
     * @tc.steps: step2. call GetRemainingOffset.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            pattern_->GetDistanceToEdge();
            if (i == 1) {
                pattern_->itemPosition_.emplace(std::make_pair(0, swiperItemInfo1));
                continue;
            }
            pattern_->itemPosition_.clear();
        }
        layoutProperty_->UpdateLoop(false);
    }
    pattern_->itemPosition_.emplace(std::make_pair(1, swiperItemInfo1));
    pattern_->GetDistanceToEdge();
}

/**
 * @tc.name: SwiperPatternCalculateDisplayCount001
 * @tc.desc: CalculateDisplayCount
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternCalculateDisplayCount001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    auto dimension = Dimension(1);
    layoutProperty_->UpdateMinSize(dimension);

    /**
     * @tc.steps: step2. call CalculateDisplayCount.
     * @tc.expected: Related function runs ok.
     */
    pattern_->CalculateDisplayCount();
}

/**
 * @tc.name: SwiperPatternOnTouchTestHit001
 * @tc.desc: OnTouchTestHit
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternOnTouchTestHit001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});

    /**
     * @tc.steps: step2. call OnTouchTestHit.
     * @tc.expected: Related function runs ok.
     */
    CommonFunc callback = [] {};
    pattern_->isTouchDown_ = false;
    pattern_->swiperController_->SetRemoveTabBarEventCallback(callback);
    pattern_->OnTouchTestHit(SourceType::TOUCH);
    EXPECT_NE(pattern_->swiperController_->GetRemoveTabBarEventCallback(), nullptr);
}

/**
 * @tc.name: SwiperPatternPlayIndicatorTranslateAnimation002
 * @tc.desc: PlayIndicatorTranslateAnimation
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternPlayIndicatorTranslateAnimation002, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});

    /**
     * @tc.steps: step2. call PlayIndicatorTranslateAnimation.
     * @tc.expected: Related function runs ok.
     */
    TurnPageRateFunc callback = [](const int32_t i, float f) {};
    pattern_->swiperController_->SetTurnPageRateCallback(callback);
    pattern_->PlayIndicatorTranslateAnimation(0.1f);
    EXPECT_NE(pattern_->swiperController_->GetTurnPageRateCallback(), nullptr);
}

/**
 * @tc.name: SwiperPatternOnDirtyLayoutWrapperSwap002
 * @tc.desc: OnDirtyLayoutWrapperSwap
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternOnDirtyLayoutWrapperSwap002, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {
        model.SetDisplayArrow(true); // show arrow
        model.SetHoverShow(false);
        model.SetArrowStyle(ARROW_PARAMETERS);
    });
    auto indicatorNode = GetChildFrameNode(frameNode_, 4);
    auto firstChild = AccessibilityManager::DynamicCast<FrameNode>(indicatorNode);
    RefPtr<GeometryNode> firstGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    firstGeometryNode->Reset();
    firstGeometryNode->SetFrameSize(SizeF(20.0, 20.0));
    auto firstLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(firstChild, firstGeometryNode, firstChild->GetLayoutProperty());
    auto dirty = AceType::MakeRefPtr<LayoutWrapperNode>(firstChild, firstGeometryNode, firstChild->GetLayoutProperty());
    dirty->AppendChild(firstLayoutWrapper);
    struct DirtySwapConfig config;
    pattern_->isInit_ = true;
    config.skipMeasure = false;
    config.skipLayout = false;

    /**
     * @tc.steps: step2. call OnDirtyLayoutWrapperSwap.
     * @tc.expected: Related function runs ok.
     */
    TurnPageRateFunc callback = [](const int32_t i, float f) {};
    pattern_->swiperController_->SetTurnPageRateCallback(callback);
    struct SwiperItemInfo swiperItemInfo1;
    swiperItemInfo1.startPos = -1.0f;
    swiperItemInfo1.endPos = -1.0f;

    auto swiperLayoutAlgorithm = AceType::DynamicCast<SwiperLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    dirty->layoutAlgorithm_ = AceType::MakeRefPtr<LayoutAlgorithmWrapper>(swiperLayoutAlgorithm);
    dirty->layoutAlgorithm_->layoutAlgorithm_ = AceType::MakeRefPtr<SwiperLayoutAlgorithm>();
    ASSERT_NE(dirty->GetLayoutAlgorithm(), nullptr);
    ASSERT_NE(AceType::DynamicCast<SwiperLayoutAlgorithm>(dirty->GetLayoutAlgorithm()->GetLayoutAlgorithm()), nullptr);
    AceType::DynamicCast<SwiperLayoutAlgorithm>(dirty->GetLayoutAlgorithm()->GetLayoutAlgorithm())
        ->itemPosition_.emplace(std::make_pair(1, swiperItemInfo1));
    pattern_->isDragging_ = true;
    pattern_->OnDirtyLayoutWrapperSwap(dirty, config);
    EXPECT_NE(pattern_->swiperController_->GetTurnPageRateCallback(), nullptr);
}

/**
 * @tc.name: SwiperPatternGetDisplayCount002
 * @tc.desc: GetDisplayCount
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternGetDisplayCount002, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    layoutProperty_->UpdateShowIndicator(false);
    pattern_->leftButtonId_.reset();

    LayoutConstraintF layoutConstraint;
    layoutConstraint.maxSize = SizeF(720.f, 1136.f);
    layoutConstraint.percentReference = SizeF(720.f, 1136.f);
    layoutConstraint.parentIdealSize.SetSize(SizeF(720.f, 1136.f));
    layoutConstraint.selfIdealSize = OptionalSize(SizeF(720.f, 1200.f));
    layoutProperty_->UpdateLayoutConstraint(layoutConstraint);
    layoutProperty_->UpdateContentConstraint();

    /**
     * @tc.steps: step2. Set the FrameSize of the model.
     */
    frameNode_->GetGeometryNode()->SetFrameSize(SizeF(720.f, 1136.f));
    Dimension SWIPER_MINSIZE = 50.0_vp;

    for (int i = 0; i < 4; i++) {
        /**
         * @tc.steps: step3. Update the MinSize of one swiper item.
         * @tc.expected: Related function runs ok.
         */
        layoutProperty_->UpdateMinSize(SWIPER_MINSIZE);
        EXPECT_EQ(layoutProperty_->GetMinSize().value_or(Dimension(0.0, DimensionUnit::VP)), SWIPER_MINSIZE);

        /**
         * @tc.steps: step4. Call GetDisplayCount.
         * @tc.expected: The return value is correct.
         */
        float displaycount = static_cast<int32_t>(
            floor((SizeF(720.f, 1136.f).Width() - 2 * 16.f + 16.f) / (SWIPER_MINSIZE.ConvertToPx() + 16.f)));
        displaycount = displaycount > 0 ? displaycount : 1;
        displaycount = displaycount > pattern_->TotalCount() ? pattern_->TotalCount() : displaycount;
        EXPECT_EQ(pattern_->GetDisplayCount(), displaycount);

        constexpr Dimension delta = 200.0_vp;
        SWIPER_MINSIZE += delta;
    }
}

/**
 * @tc.name: SwiperLayoutAlgorithmLayoutBackwardItem001
 * @tc.desc: LayoutBackwardItem
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperLayoutAlgorithmLayoutBackwardItem001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper = LayoutWrapperNode(indicatorNode, geometryNode, indicatorNode->GetLayoutProperty());
    LayoutConstraintF layoutConstraint;
    layoutConstraint.maxSize = SizeF(720.f, 1136.f);
    layoutConstraint.percentReference = SizeF(720.f, 1136.f);
    layoutConstraint.parentIdealSize.SetSize(SizeF(720.f, 1136.f));
    ASSERT_NE(layoutWrapper.layoutProperty_, nullptr);
    layoutWrapper.GetLayoutProperty()->UpdateLayoutConstraint(layoutConstraint);
    Axis axis = Axis::HORIZONTAL;
    int32_t currentIndex = 1;
    float endPos = 0.1f;
    float startPos = 0.2f;
    auto swiperLayoutAlgorithm = AceType::DynamicCast<SwiperLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    swiperLayoutAlgorithm->isLoop_ = true;
    auto firstLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(indicatorNode, geometryNode, indicatorNode->GetLayoutProperty());
    layoutWrapper.AppendChild(firstLayoutWrapper);

    /**
     * @tc.steps: step2. call LayoutBackwardItem.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            swiperLayoutAlgorithm->LayoutBackwardItem(
                &layoutWrapper, layoutConstraint, axis, currentIndex, endPos, startPos);
            if (i == 1) {
                swiperLayoutAlgorithm->isLoop_ = true;
                continue;
            }
            swiperLayoutAlgorithm->isLoop_ = false;
        }
        currentIndex = 0;
    }

    currentIndex = 1;
    indicatorNode->tag_ = V2::SWIPER_LEFT_ARROW_ETS_TAG;
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            swiperLayoutAlgorithm->LayoutBackwardItem(
                &layoutWrapper, layoutConstraint, axis, currentIndex, endPos, startPos);
            if (i == 1) {
                indicatorNode->tag_ = V2::SWIPER_RIGHT_ARROW_ETS_TAG;
                continue;
            }
            indicatorNode->tag_ = V2::SWIPER_INDICATOR_ETS_TAG;
        }
        indicatorNode->tag_ = V2::SWIPER_ETS_TAG;
    }
}

/**
 * @tc.name: SwiperPatternUpdateAnimationProperty001
 * @tc.desc: UpdateAnimationProperty
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternUpdateAnimationProperty001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    struct SwiperItemInfo swiperItemInfo1 {
        0.1f, 0.2f
    };
    pattern_->isDragging_ = true;
    float velocity = 0.1f;

    /**
     * @tc.steps: step2. call UpdateAnimationProperty.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j >= 1; j++) {
            for (int k = 0; k <= 1; k++) {
                pattern_->UpdateAnimationProperty(velocity);
                pattern_->itemPosition_.emplace(std::make_pair(1, swiperItemInfo1));
                if (i == 1) {
                    velocity = -1300;
                    continue;
                }
                if (i == 1 && j == 1) {
                    break;
                }
                velocity = 0.0f;
            }
            if (i == 1) {
                pattern_->isDragging_ = false;
                continue;
            }
            velocity = 0.1f;
        }
        velocity = 1300;
    }
}

/**
 * @tc.name: SwiperPatternGetFirstItemInfoInVisibleArea001
 * @tc.desc: GetFirstItemInfoInVisibleArea
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternGetFirstItemInfoInVisibleArea001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    struct SwiperItemInfo swiperItemInfo1 {
        0.1f, 0.2f
    }, swiperItemInfo2 { -0.1f, -0.2f }, swiperItemInfo3 { -0.1f, 0.2f }, swiperItemInfo4 { 0.1f, -0.2f };
    pattern_->itemPosition_.clear();
    auto dimension = Dimension(1);

    /**
     * @tc.steps: step2. call GetFirstItemInfoInVisibleArea.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            pattern_->GetFirstItemInfoInVisibleArea();
            if (i == 1) {
                break;
            }
            pattern_->itemPosition_.emplace(std::make_pair(1, swiperItemInfo1));
            pattern_->itemPosition_.emplace(std::make_pair(2, swiperItemInfo2));
            pattern_->itemPosition_.emplace(std::make_pair(3, swiperItemInfo3));
            pattern_->itemPosition_.emplace(std::make_pair(4, swiperItemInfo4));
            layoutProperty_->UpdatePrevMargin(dimension);
            layoutProperty_->layoutConstraint_->scaleProperty = ScaleProperty { 1.0f, 1.0f, 1.0f };
        }
        layoutProperty_->ResetPrevMargin();
        layoutProperty_->layoutConstraint_->scaleProperty = ScaleProperty { 0.0f, 0.0f, 0.0f };
    }
}

/**
 * @tc.name: SwiperPatternGetTranslateLength001
 * @tc.desc: GetTranslateLength
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternGetTranslateLength001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    pattern_->itemPosition_.clear();

    /**
     * @tc.steps: step2. call GetTranslateLength.
     * @tc.expected: Related function runs ok.
     */
    pattern_->GetTranslateLength();
}

/**
 * @tc.name: SwiperPatternGetSecondItemInfoInVisibleArea001
 * @tc.desc: GetSecondItemInfoInVisibleArea
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternGetSecondItemInfoInVisibleArea001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    struct SwiperItemInfo swiperItemInfo1 {
        0.1f, 0.2f
    }, swiperItemInfo2 { -0.1f, -0.2f }, swiperItemInfo3 { -0.1f, 0.2f }, swiperItemInfo4 { 0.1f, -0.2f };
    pattern_->itemPosition_.clear();
    auto dimension = Dimension(1);

    /**
     * @tc.steps: step2. call GetSecondItemInfoInVisibleArea.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            pattern_->GetSecondItemInfoInVisibleArea();
            if (i == 1) {
                break;
            }
            pattern_->itemPosition_.emplace(std::make_pair(1, swiperItemInfo1));
            pattern_->itemPosition_.emplace(std::make_pair(2, swiperItemInfo2));
            pattern_->itemPosition_.emplace(std::make_pair(3, swiperItemInfo3));
            pattern_->itemPosition_.emplace(std::make_pair(4, swiperItemInfo4));
            layoutProperty_->UpdatePrevMargin(dimension);
            layoutProperty_->layoutConstraint_->scaleProperty = ScaleProperty { 1.0f, 1.0f, 1.0f };
        }
        layoutProperty_->ResetPrevMargin();
        layoutProperty_->layoutConstraint_->scaleProperty = ScaleProperty { 0.0f, 0.0f, 0.0f };
    }
    pattern_->itemPosition_.erase(2);
    pattern_->GetSecondItemInfoInVisibleArea();
}

/**
 * @tc.name: PostTranslateTask001
 * @tc.desc: PostTranslateTask
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, PostTranslateTask001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Call PostTranslateTask
     * @tc.expected: Swipe to next
     */
    CreateWithItem([](SwiperModelNG model) {});
    pattern_->PostTranslateTask(DEFAULT_INTERVAL);
    EXPECT_EQ(pattern_->targetIndex_, 1);
}

/**
 * @tc.name: PostTranslateTask002
 * @tc.desc: PostTranslateTask
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, PostTranslateTask002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. loop is false, index is last item index
     * @tc.expected: Can not swipe to next
     */
    CreateWithItem([](SwiperModelNG model) {
        model.SetLoop(false);
        model.SetIndex(2);
    });

    /**
     * @tc.steps: step2. Call PostTranslateTask
     * @tc.expected: Can swipe to next
     */
    pattern_->PostTranslateTask(DEFAULT_INTERVAL);
    EXPECT_EQ(pattern_->targetIndex_, 3);

    /**
     * @tc.steps: step3. Swipe to last item and call PostTranslateTask
     * @tc.expected: Can not swipe to next
     */
    controller_->SwipeToWithoutAnimation(3);
    FlushLayoutTask(frameNode_);
    pattern_->PostTranslateTask(DEFAULT_INTERVAL);
    EXPECT_FALSE(pattern_->targetIndex_.has_value());
}

/**
 * @tc.name: PostTranslateTask003
 * @tc.desc: PostTranslateTask
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, PostTranslateTask003, TestSize.Level1)
{
    Create([](SwiperModelNG model) {});
    pattern_->itemPosition_.clear();
    pattern_->PostTranslateTask(DEFAULT_INTERVAL);
    EXPECT_FALSE(pattern_->targetIndex_.has_value());

    layoutProperty_->UpdateDisplayCount(0);
    pattern_->PostTranslateTask(DEFAULT_INTERVAL);
    EXPECT_FALSE(pattern_->targetIndex_.has_value());
}

/**
 * @tc.name: SwiperPatternRegisterVisibleAreaChange001
 * @tc.desc: RegisterVisibleAreaChange
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternRegisterVisibleAreaChange001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});

    /**
     * @tc.steps: step2. call RegisterVisibleAreaChange.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            pattern_->RegisterVisibleAreaChange();
            if (i == 1) {
                pattern_->hasVisibleChangeRegistered_ = false;
            }
            pattern_->hasVisibleChangeRegistered_ = true;
        }
        frameNode_->GetPaintProperty<SwiperPaintProperty>()->UpdateAutoPlay(true);
    }

    pattern_->isWindowShow_ = false;
    for (int i = 0; i <= 1; i++) {
        pattern_->RegisterVisibleAreaChange();
        pattern_->isWindowShow_ = true;
        pattern_->isVisibleArea_ = true;
        pattern_->isVisible_ = true;
    }
}

/**
 * @tc.name: SwiperPatternTriggerEventOnFinish001
 * @tc.desc: TriggerEventOnFinish
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternTriggerEventOnFinish001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    int32_t nextIndex = 1;
    pattern_->preTargetIndex_ = 1;
    pattern_->currentIndex_ = 1;

    /**
     * @tc.steps: step2. call TriggerEventOnFinish.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            pattern_->TriggerEventOnFinish(nextIndex);
            if (i == 1) {
                break;
            }
            nextIndex = 2;
            pattern_->isFinishAnimation_ = true;
        }
        pattern_->isFinishAnimation_ = false;
    }
}

/**
 * @tc.name: SwiperPatternArrowHover001
 * @tc.desc: ArrowHover
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternArrowHover001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    bool hoverFlag = true;
    pattern_->leftButtonId_.reset();
    pattern_->rightButtonId_.reset();

    /**
     * @tc.steps: step2. call ArrowHover.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            pattern_->ArrowHover(hoverFlag);
            if (i == 1) {
                pattern_->leftButtonId_.reset();
            }
            pattern_->leftButtonId_ = 1;
        }
        pattern_->rightButtonId_ = 1;
    }
}

/**
 * @tc.name: SwiperPatternTriggerAnimationEndOnSwipeToLeft001
 * @tc.desc: TriggerAnimationEndOnSwipeToLeft
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternTriggerAnimationEndOnSwipeToLeft001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    pattern_->itemPosition_.clear();

    /**
     * @tc.steps: step2. call TriggerAnimationEndOnSwipeToLeft.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        pattern_->TriggerAnimationEndOnSwipeToLeft();
        pattern_->itemPosition_.emplace(std::make_pair(1, SwiperItemInfo { 1, 4 }));
    }
}

/**
 * @tc.name: SwiperPatternTriggerAnimationEndOnSwipeToRight001
 * @tc.desc: TriggerAnimationEndOnSwipeToRight
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternTriggerAnimationEndOnSwipeToRight001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    pattern_->itemPosition_.clear();

    /**
     * @tc.steps: step2. call TriggerAnimationEndOnSwipeToRight.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        pattern_->TriggerAnimationEndOnSwipeToRight();
        pattern_->itemPosition_.emplace(std::make_pair(1, SwiperItemInfo { 1, 4 }));
    }
}

/**
 * @tc.name: SwiperPatternOnTranslateFinish001
 * @tc.desc: OnTranslateFinish
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternOnTranslateFinish001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {
        model.SetDisplayArrow(true); // show arrow
        model.SetHoverShow(false);
        model.SetArrowStyle(ARROW_PARAMETERS);
    });
    auto indicatorNode = GetChildFrameNode(frameNode_, 4);
    auto leftArrowNode = GetChildFrameNode(frameNode_, 5);
    int32_t nextIndex = 1;
    bool restartAutoPlay = true;
    bool forceStop = true;

    /**
     * @tc.steps: step2. call OnTranslateFinish.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            pattern_->OnTranslateFinish(nextIndex, restartAutoPlay, pattern_->isFinishAnimation_, forceStop);
            if (i == 1) {
                pattern_->isFinishAnimation_ = false;
                continue;
            }
            pattern_->isFinishAnimation_ = true;
            frameNode_->AddChild(indicatorNode);
            pattern_->isVisible_ = false;
        }
            frameNode_->AddChild(leftArrowNode);
        frameNode_->AddChild(indicatorNode);
        forceStop = false;
        pattern_->isVisible_ = true;
        frameNode_->GetPaintProperty<SwiperPaintProperty>()->UpdateAutoPlay(true);
        layoutProperty_->UpdateLoop(true);
    }
}

/**
 * @tc.name: SwiperPatternCheckAndSetArrowHoverState001
 * @tc.desc: CheckAndSetArrowHoverState
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternCheckAndSetArrowHoverState001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {
        model.SetDisplayArrow(true); // show arrow
        model.SetHoverShow(false);
        model.SetArrowStyle(ARROW_PARAMETERS);
    });
    auto indicatorNode = GetChildFrameNode(frameNode_, 4);
    auto leftArrowNode = GetChildFrameNode(frameNode_, 5);
    auto rightArrowNode = GetChildFrameNode(frameNode_, 6);
    pattern_->currentIndex_ = 1;
    pattern_->leftButtonId_ = 1;
    pattern_->rightButtonId_ = 1;
    pattern_->indicatorId_ = 1;
    layoutProperty_->UpdateShowIndicator(false);
    auto mousePoint = PointF(0.0f, 0.0f);
   
    /**
     * @tc.steps: step2. call CheckAndSetArrowHoverState.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            for (int k = 0; k <= 1; k++) {
                pattern_->CheckAndSetArrowHoverState(mousePoint);
                if (j == 1) {
                    pattern_->leftButtonId_ = 1;
                    continue;
                }
                pattern_->leftButtonId_.reset();
            }
            pattern_->rightButtonId_.reset();
        }
        pattern_->indicatorId_.reset();
    }

    pattern_->leftButtonId_ = 1;
    pattern_->rightButtonId_ = 1;
    pattern_->indicatorId_ = 1;
    frameNode_->AddChild(leftArrowNode);
    frameNode_->AddChild(indicatorNode);
    frameNode_->AddChild(rightArrowNode);
    frameNode_->AddChild(indicatorNode);
    layoutProperty_->UpdateIsSidebarMiddle(true);
    pattern_->CheckAndSetArrowHoverState(mousePoint);
    layoutProperty_->UpdateIsSidebarMiddle(false);
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            pattern_->CheckAndSetArrowHoverState(mousePoint);
            if (i == 1) {
                pattern_->currentIndex_ = 1;
            }
            pattern_->currentIndex_ = 0;
        }
        layoutProperty_->UpdateLoop(false);
    }
    layoutProperty_->UpdateDirection(Axis::HORIZONTAL);
    for (int i = 0; i <= 1; i++) {
        pattern_->CheckAndSetArrowHoverState(mousePoint);
        layoutProperty_->UpdateDirection(Axis::VERTICAL);
    }
}

/**
 * @tc.name: SwiperPatternHandleMouseEvent001
 * @tc.desc: HandleMouseEvent
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternHandleMouseEvent001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    auto info = MouseInfo();
    layoutProperty_->UpdateShowIndicator(true);

    /**
     * @tc.steps: step2. call HandleMouseEvent.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        pattern_->HandleMouseEvent(info);
        layoutProperty_->UpdateShowIndicator(false);
    }
}

/**
 * @tc.name: SwiperPatternGetCustomPropertyOffset001
 * @tc.desc: GetCustomPropertyOffset
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternGetCustomPropertyOffset001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    layoutProperty_->UpdateDirection(Axis::HORIZONTAL);
    layoutProperty_->ResetPrevMargin();

    /**
     * @tc.steps: step2. call GetCustomPropertyOffset.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            pattern_->GetCustomPropertyOffset();
            if (i == 1) {
                break;
            }
            layoutProperty_->UpdateDirection(Axis::VERTICAL);
            layoutProperty_->UpdatePrevMargin(Dimension(0));
        }
        layoutProperty_->UpdatePrevMargin(Dimension(1));
    }
}

/**
 * @tc.name: SwiperPatternGetCurrentFirstIndexStartPos001
 * @tc.desc: GetCurrentFirstIndexStartPos
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternGetCurrentFirstIndexStartPos001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    pattern_->itemPosition_.clear();

    /**
     * @tc.steps: step2. call GetCurrentFirstIndexStartPos.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        ASSERT_EQ(pattern_->GetCurrentFirstIndexStartPos(), i == 0 ? 0.0 : 1);
        pattern_->itemPosition_.emplace(std::make_pair(1, SwiperItemInfo { 1, 1 }));
    }
}

/**
 * @tc.name: SwiperPatternOnSpringAnimationStart001
 * @tc.desc: OnSpringAnimationStart
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternOnSpringAnimationStart001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {
        model.SetDisplayArrow(true); // show arrow
        model.SetHoverShow(false);
        model.SetArrowStyle(ARROW_PARAMETERS);
    });
    layoutProperty_->UpdateShowIndicator(false);
    pattern_->leftButtonId_.reset();
    pattern_->rightButtonId_.reset();
    float velocity = 200.0f;
    pattern_->itemPosition_.emplace(std::make_pair(-1, SwiperItemInfo { -1, 1 }));
    pattern_->currentIndex_ = 1;

    /**
     * @tc.steps: step2. call OnSpringAnimationStart.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        pattern_->OnSpringAnimationStart(velocity);
        pattern_->currentIndex_ = 0;
    }
}

/**
 * @tc.name: SwiperPatternOnSpringAndFadeAnimationFinish001
 * @tc.desc: OnSpringAndFadeAnimationFinish
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternOnSpringAndFadeAnimationFinish001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {
        model.SetDisplayArrow(true); // show arrow
        model.SetHoverShow(false);
        model.SetArrowStyle(ARROW_PARAMETERS);
    });
    pattern_->itemPosition_.emplace(std::make_pair(0, SwiperItemInfo { -1, 1 }));
    pattern_->currentIndex_ = 1;

    /**
     * @tc.steps: step2. call OnSpringAndFadeAnimationFinish.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        pattern_->fadeAnimationIsRunning_ = true;
        pattern_->OnSpringAndFadeAnimationFinish();
        EXPECT_FALSE(pattern_->fadeAnimationIsRunning_);
        pattern_->currentIndex_ = 0;
    }
}

/**
 * @tc.name: SwiperPatternOnFadeAnimationStart001
 * @tc.desc: OnFadeAnimationStart
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternOnFadeAnimationStart001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {
        model.SetDisplayArrow(true); // show arrow
        model.SetHoverShow(false);
        model.SetArrowStyle(ARROW_PARAMETERS);
    });
    pattern_->itemPosition_.emplace(std::make_pair(0, SwiperItemInfo { -1, 1 }));
    pattern_->currentIndex_ = 1;

    /**
     * @tc.steps: step2. call OnFadeAnimationStart.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        pattern_->fadeAnimationIsRunning_ = false;
        pattern_->OnFadeAnimationStart();
        EXPECT_TRUE(pattern_->fadeAnimationIsRunning_);
        pattern_->currentIndex_ = 0;
    }
}

/**
 * @tc.name: SwiperPatternComputeNextIndexByVelocity001
 * @tc.desc: ComputeNextIndexByVelocity
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternComputeNextIndexByVelocity001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    float velocity = 0.1f;
    pattern_->itemPosition_.emplace(std::make_pair(0, SwiperItemInfo { 2, 1 }));

    /**
     * @tc.steps: step2. call ComputeNextIndexByVelocity.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            pattern_->ComputeNextIndexByVelocity(velocity);
            if (i == 1) {
                continue;
            }
            pattern_->itemPosition_.clear();
            pattern_->itemPosition_.emplace(std::make_pair(0, SwiperItemInfo { 2, 1 }));
            velocity = 0;
        }
        velocity = 200;
    }
}

/**
 * @tc.name: SwiperLayoutAlgorithmLayoutForward001
 * @tc.desc: LayoutForward
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperLayoutAlgorithmLayoutForward001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    auto swiperLayoutAlgorithm = AceType::DynamicCast<SwiperLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper = LayoutWrapperNode(indicatorNode, geometryNode, indicatorNode->GetLayoutProperty());
    LayoutConstraintF layoutConstraint;
    layoutConstraint.maxSize = SizeF(720.f, 1136.f);
    layoutConstraint.percentReference = SizeF(720.f, 1136.f);
    layoutConstraint.parentIdealSize.SetSize(SizeF(720.f, 1136.f));
    ASSERT_NE(layoutWrapper.layoutProperty_, nullptr);
    layoutWrapper.GetLayoutProperty()->UpdateLayoutConstraint(layoutConstraint);
    Axis axis = Axis::HORIZONTAL;
    int32_t startIndex = 1;
    float startPos = 0.0f;
    swiperLayoutAlgorithm->targetIndex_ = 1;

    /**
     * @tc.steps: step2. call LayoutForward.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        swiperLayoutAlgorithm->LayoutForward(&layoutWrapper, layoutConstraint, axis, startIndex, startPos);
        swiperLayoutAlgorithm->targetIndex_ = 0;
    }
}

/**
 * @tc.name: SwiperLayoutAlgorithmLayoutBackward001
 * @tc.desc: LayoutBackward
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperLayoutAlgorithmLayoutBackward001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    auto swiperLayoutAlgorithm = AceType::DynamicCast<SwiperLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper = LayoutWrapperNode(indicatorNode, geometryNode, indicatorNode->GetLayoutProperty());
    LayoutConstraintF layoutConstraint;
    layoutConstraint.maxSize = SizeF(720.f, 1136.f);
    layoutConstraint.percentReference = SizeF(720.f, 1136.f);
    layoutConstraint.parentIdealSize.SetSize(SizeF(720.f, 1136.f));
    ASSERT_NE(layoutWrapper.layoutProperty_, nullptr);
    layoutWrapper.GetLayoutProperty()->UpdateLayoutConstraint(layoutConstraint);
    Axis axis = Axis::HORIZONTAL;
    int32_t endIndex = 1;
    float endPos = 0.0f;
    swiperLayoutAlgorithm->targetIndex_ = 1;

    /**
     * @tc.steps: step2. call LayoutBackward.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        swiperLayoutAlgorithm->LayoutBackward(&layoutWrapper, layoutConstraint, axis, endIndex, endPos);
        swiperLayoutAlgorithm->targetIndex_ = 0;
    }
}

/**
 * @tc.name: SwiperLayoutAlgorithmSetInactive001
 * @tc.desc: SetInactive
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperLayoutAlgorithmSetInactive001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    auto swiperLayoutAlgorithm = AceType::DynamicCast<SwiperLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    CreateWithItem([](SwiperModelNG model) {});
    auto layoutWrapper = LayoutWrapperNode(indicatorNode, geometryNode, layoutProperty_);
    float startMainPos = 0.1f;
    float endMainPos = 0.0f;
    int32_t targetIndex = 1;
    swiperLayoutAlgorithm->itemPosition_.emplace(std::make_pair(1, SwiperItemInfo { 1, 2 }));
    swiperLayoutAlgorithm->itemPosition_.emplace(std::make_pair(2, SwiperItemInfo { 1, 2 }));
    swiperLayoutAlgorithm->prevMargin_ = 0.0;
    swiperLayoutAlgorithm->nextMargin_ = 0.0;

    /**
     * @tc.steps: step2. call SetInactive.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            swiperLayoutAlgorithm->SetInactive(&layoutWrapper, startMainPos, endMainPos, targetIndex);
            startMainPos = 3;
        }
        swiperLayoutAlgorithm->prevMargin_ = 1.0;
    }

    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            swiperLayoutAlgorithm->SetInactive(&layoutWrapper, startMainPos, endMainPos, targetIndex);
            endMainPos = 3;
        }
        swiperLayoutAlgorithm->nextMargin_ = 1.0;
    }
}

/**
 * @tc.name: SwiperLayoutAlgorithmLayoutForward002
 * @tc.desc: LayoutForward
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperLayoutAlgorithmLayoutForward002, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    auto swiperLayoutAlgorithm = AceType::DynamicCast<SwiperLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper = LayoutWrapperNode(indicatorNode, geometryNode, indicatorNode->GetLayoutProperty());
    auto indicatorNode_test = FrameNode::GetOrCreateFrameNode(V2::SWIPER_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    layoutWrapper.currentChildCount_ = 2;
    layoutWrapper.childrenMap_.emplace(std::make_pair(1,
        AceType::MakeRefPtr<LayoutWrapperNode>(indicatorNode_test, geometryNode, indicatorNode->GetLayoutProperty())));
    LayoutConstraintF layoutConstraint;
    layoutConstraint.maxSize = SizeF(720.f, 1136.f);
    layoutConstraint.percentReference = SizeF(720.f, 1136.f);
    layoutConstraint.parentIdealSize.SetSize(SizeF(720.f, 1136.f));
    layoutWrapper.layoutProperty_ = AceType::MakeRefPtr<SwiperLayoutProperty>();
    ASSERT_NE(layoutWrapper.layoutProperty_, nullptr);
    layoutWrapper.GetLayoutProperty()->UpdateLayoutConstraint(layoutConstraint);
    Axis axis = Axis::HORIZONTAL;
    int32_t startIndex = 1;
    float startPos = 0.0f;
    swiperLayoutAlgorithm->targetIndex_ = 1;
    swiperLayoutAlgorithm->SetTotalItemCount(1);
    swiperLayoutAlgorithm->SetIsLoop(false);

    /**
     * @tc.steps: step2. call LayoutForward.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            swiperLayoutAlgorithm->LayoutForward(&layoutWrapper, layoutConstraint, axis, startIndex, startPos);
            if (i == 1) {
                break;
            }
            swiperLayoutAlgorithm->SetIsLoop(true);
            AceType::DynamicCast<SwiperLayoutProperty>(layoutWrapper.layoutProperty_)->UpdateMinSize(Dimension(1));
            AceType::DynamicCast<SwiperLayoutProperty>(layoutWrapper.layoutProperty_)->UpdatePrevMargin(Dimension(1));
            AceType::DynamicCast<SwiperLayoutProperty>(layoutWrapper.layoutProperty_)->UpdateNextMargin(Dimension(1));
            AceType::DynamicCast<SwiperLayoutProperty>(layoutWrapper.layoutProperty_)->UpdateDisplayCount(1);
        }
        AceType::DynamicCast<SwiperLayoutProperty>(layoutWrapper.layoutProperty_)->UpdateMinSize(Dimension(-1));
        AceType::DynamicCast<SwiperLayoutProperty>(layoutWrapper.layoutProperty_)->UpdatePrevMargin(Dimension(-1));
        AceType::DynamicCast<SwiperLayoutProperty>(layoutWrapper.layoutProperty_)->UpdateNextMargin(Dimension(1));
        AceType::DynamicCast<SwiperLayoutProperty>(layoutWrapper.layoutProperty_)->UpdateDisplayCount(0);
    }

    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            swiperLayoutAlgorithm->LayoutForward(&layoutWrapper, layoutConstraint, axis, startIndex, startPos);
            if (i == 1) {
                swiperLayoutAlgorithm->overScrollFeature_ = false;
            }
            swiperLayoutAlgorithm->overScrollFeature_ = true;
        }
        swiperLayoutAlgorithm->canOverScroll_ = true;
    }
}

/**
 * @tc.name: SwiperLayoutAlgorithmLayoutBackward002
 * @tc.desc: LayoutBackward
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperLayoutAlgorithmLayoutBackward002, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    auto swiperLayoutAlgorithm = AceType::DynamicCast<SwiperLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper = LayoutWrapperNode(indicatorNode, geometryNode, indicatorNode->GetLayoutProperty());
    LayoutConstraintF layoutConstraint;
    layoutConstraint.maxSize = SizeF(720.f, 1136.f);
    layoutConstraint.percentReference = SizeF(720.f, 1136.f);
    layoutConstraint.parentIdealSize.SetSize(SizeF(720.f, 1136.f));
    layoutWrapper.layoutProperty_ = AceType::MakeRefPtr<SwiperLayoutProperty>();
    ASSERT_NE(layoutWrapper.layoutProperty_, nullptr);
    layoutWrapper.GetLayoutProperty()->UpdateLayoutConstraint(layoutConstraint);
    Axis axis = Axis::HORIZONTAL;
    int32_t endIndex = -1;
    float endPos = 0.0f;
    swiperLayoutAlgorithm->targetIndex_ = 1;
    swiperLayoutAlgorithm->SetIsLoop(false);
    swiperLayoutAlgorithm->totalItemCount_ = 2;
    swiperLayoutAlgorithm->itemPosition_.clear();
    layoutWrapper.currentChildCount_ = 2;

    /**
     * @tc.steps: step2. call LayoutBackward.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            swiperLayoutAlgorithm->LayoutBackward(&layoutWrapper, layoutConstraint, axis, endIndex, endPos);
            if (i == 1) {
                endIndex = 1;
                auto indicatorNode_test =
                    FrameNode::GetOrCreateFrameNode(V2::SWIPER_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
                        []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
                layoutWrapper.childrenMap_.emplace(
                    std::make_pair(1, AceType::MakeRefPtr<LayoutWrapperNode>(
                                          indicatorNode_test, geometryNode, indicatorNode->GetLayoutProperty())));
                continue;
            }
            swiperLayoutAlgorithm->SetIsLoop(true);
        }
        swiperLayoutAlgorithm->SetIsLoop(false);
        swiperLayoutAlgorithm->itemPosition_.emplace(std::make_pair(1, SwiperItemInfo { 1, 2 }));
        swiperLayoutAlgorithm->overScrollFeature_ = true;
    }
}

/**
 * @tc.name: SwiperLayoutAlgorithmPlaceDigitChild001
 * @tc.desc: PlaceDigitChild
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperLayoutAlgorithmPlaceDigitChild001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    auto indicatorNode = GetChildFrameNode(frameNode_, 4);
    auto swiperLayoutAlgorithm = AceType::DynamicCast<SwiperLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto indicatorWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(indicatorNode, geometryNode, indicatorNode->GetLayoutProperty());
    auto layoutProperty = AceType::MakeRefPtr<SwiperLayoutProperty>();
    auto firstChild = AccessibilityManager::DynamicCast<FrameNode>(indicatorNode);
    RefPtr<GeometryNode> firstGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    firstGeometryNode->Reset();
    firstGeometryNode->SetFrameSize(SizeF(20.0, 20.0));
    RefPtr<LayoutWrapperNode> firstLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(firstChild, firstGeometryNode, firstChild->GetLayoutProperty());
    indicatorWrapper->AppendChild(firstLayoutWrapper);
    auto lastChild = AccessibilityManager::DynamicCast<FrameNode>(indicatorNode);
    RefPtr<GeometryNode> lastGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    lastGeometryNode->Reset();
    lastGeometryNode->SetFrameSize(SizeF(30.0, 30.0));
    RefPtr<LayoutWrapperNode> lastLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(lastChild, lastGeometryNode, lastChild->GetLayoutProperty());
    indicatorWrapper->AppendChild(lastLayoutWrapper);
    layoutProperty->UpdateLeft(Dimension(1));
    layoutProperty->UpdateTop(Dimension(1));
    indicatorWrapper->layoutProperty_ = AceType::MakeRefPtr<LayoutProperty>();
    LayoutConstraintF layoutConstraintF;
    layoutConstraintF.parentIdealSize = OptionalSizeF(0.1f, 0.2f);
    indicatorWrapper->GetLayoutProperty()->layoutConstraint_ = layoutConstraintF;
    indicatorWrapper->currentChildCount_ = 1;

    /**
     * @tc.steps: step2. call PlaceDigitChild.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            swiperLayoutAlgorithm->PlaceDigitChild(indicatorWrapper, layoutProperty);
            if (i == 1) {
                layoutProperty->UpdateDirection(Axis::VERTICAL);
                continue;
            }
            indicatorWrapper->currentChildCount_ = 2;
            layoutProperty->padding_ = std::make_unique<PaddingProperty>();
            layoutProperty->UpdateLeft(Dimension(0));
            layoutProperty->UpdateRight(Dimension(1));
            layoutProperty->UpdateTop(Dimension(0));
            layoutProperty->UpdateBottom(Dimension(1));
        }
        layoutProperty->UpdateRight(Dimension(0));
        layoutProperty->UpdateBottom(Dimension(0));
    }
}

/**
 * @tc.name: SwiperLayoutAlgorithmGetNodeLayoutWrapperByTag001
 * @tc.desc: GetNodeLayoutWrapperByTag
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperLayoutAlgorithmGetNodeLayoutWrapperByTag001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    auto swiperLayoutAlgorithm = AceType::DynamicCast<SwiperLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper = LayoutWrapperNode(indicatorNode, geometryNode, indicatorNode->GetLayoutProperty());
    string tagName = V2::SWIPER_INDICATOR_ETS_TAG;
    layoutWrapper.currentChildCount_ = 0;
    indicatorNode->pattern_ = AceType::MakeRefPtr<SwiperPattern>();
    ASSERT_NE(indicatorNode->pattern_, nullptr);
    AceType::DynamicCast<SwiperPattern>(indicatorNode->pattern_)->indicatorId_ = 1;
    AceType::DynamicCast<SwiperPattern>(indicatorNode->pattern_)->leftButtonId_ = 1;
    AceType::DynamicCast<SwiperPattern>(indicatorNode->pattern_)->rightButtonId_ = 1;

    /**
     * @tc.steps: step2. call GetNodeLayoutWrapperByTag.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            if (i == 1 && j == 1) {
                AceType::DynamicCast<SwiperPattern>(indicatorNode->pattern_)->indicatorId_.reset();
                AceType::DynamicCast<SwiperPattern>(indicatorNode->pattern_)->leftButtonId_ = 1;
            }
            for (int k = 0; k <= 1; k++) {
                swiperLayoutAlgorithm->GetNodeLayoutWrapperByTag(&layoutWrapper, tagName);
                if (i == 0 && j == 1) {
                    AceType::DynamicCast<SwiperPattern>(indicatorNode->pattern_)->leftButtonId_.reset();
                    continue;
                } else if (i == 1 && j == 0) {
                    AceType::DynamicCast<SwiperPattern>(indicatorNode->pattern_)->indicatorId_ = 1;
                    continue;
                } else if (i == 1 && j == 1) {
                    break;
                }
                layoutWrapper.currentChildCount_ = 1;
            }
            AceType::DynamicCast<SwiperPattern>(indicatorNode->pattern_)->indicatorId_.reset();
        }
        AceType::DynamicCast<SwiperPattern>(indicatorNode->pattern_)->rightButtonId_.reset();
    }
    AceType::DynamicCast<SwiperPattern>(indicatorNode->pattern_)->leftButtonId_.reset();
    swiperLayoutAlgorithm->GetNodeLayoutWrapperByTag(&layoutWrapper, tagName);
}

/**
 * @tc.name: SwiperLayoutAlgorithmGetChildMaxSize001
 * @tc.desc: GetChildMaxSize
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperLayoutAlgorithmGetChildMaxSize001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    auto swiperLayoutAlgorithm = AceType::DynamicCast<SwiperLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper = LayoutWrapperNode(indicatorNode, geometryNode, indicatorNode->GetLayoutProperty());
    layoutWrapper.currentChildCount_ = 2;
    layoutWrapper.childrenMap_.emplace(std::make_pair(
        0, AceType::MakeRefPtr<LayoutWrapperNode>(indicatorNode, geometryNode, indicatorNode->GetLayoutProperty())));
    layoutWrapper.childrenMap_.emplace(std::make_pair(
        1, AceType::MakeRefPtr<LayoutWrapperNode>(indicatorNode, nullptr, indicatorNode->GetLayoutProperty())));
    LayoutConstraintF layoutConstraint;
    layoutConstraint.maxSize = SizeF(720.f, 1136.f);
    layoutConstraint.percentReference = SizeF(720.f, 1136.f);
    layoutConstraint.parentIdealSize.SetSize(SizeF(720.f, 1136.f));
    ASSERT_NE(layoutWrapper.layoutProperty_, nullptr);
    layoutWrapper.GetLayoutProperty()->UpdateLayoutConstraint(layoutConstraint);
    Axis axis = Axis::HORIZONTAL;
    bool isMainAxis = true;
    swiperLayoutAlgorithm->totalItemCount_ = 3;

    /**
     * @tc.steps: step2. call GetChildMaxSize.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        swiperLayoutAlgorithm->GetChildMaxSize(&layoutWrapper, axis, isMainAxis);
        swiperLayoutAlgorithm->itemPosition_.emplace(std::make_pair(1, SwiperItemInfo { 1, 2 }));
        swiperLayoutAlgorithm->itemPosition_.emplace(std::make_pair(0, SwiperItemInfo { 1, 2 }));
        swiperLayoutAlgorithm->itemPosition_.emplace(std::make_pair(2, SwiperItemInfo { 1, 2 }));
        isMainAxis = false;
    }
}

/**
 * @tc.name: SwiperLayoutAlgorithmMeasureSwiper001
 * @tc.desc: MeasureSwiper
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperLayoutAlgorithmMeasureSwiper001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    auto swiperLayoutAlgorithm = AceType::DynamicCast<SwiperLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper = LayoutWrapperNode(indicatorNode, geometryNode, indicatorNode->GetLayoutProperty());
    layoutWrapper.currentChildCount_ = 2;
    LayoutConstraintF layoutConstraint;
    layoutConstraint.maxSize = SizeF(720.f, 1136.f);
    layoutConstraint.percentReference = SizeF(720.f, 1136.f);
    layoutConstraint.parentIdealSize.SetSize(SizeF(720.f, 1136.f));
    ASSERT_NE(layoutWrapper.layoutProperty_, nullptr);
    layoutWrapper.GetLayoutProperty()->UpdateLayoutConstraint(layoutConstraint);
    Axis axis = Axis::HORIZONTAL;
    swiperLayoutAlgorithm->totalItemCount_ = 2;

    /**
     * @tc.steps: step2. call MeasureSwiper
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            swiperLayoutAlgorithm->MeasureSwiper(&layoutWrapper, layoutConstraint, axis);
            if (i == 1) {
                int32_t targetIndex_test = 1;
                swiperLayoutAlgorithm->SetTargetIndex(targetIndex_test);
                continue;
            }
            swiperLayoutAlgorithm->prevMargin_ = 1.0f;
            swiperLayoutAlgorithm->itemPosition_.emplace(std::make_pair(0, SwiperItemInfo { 1, 1 }));
            swiperLayoutAlgorithm->itemPosition_.emplace(std::make_pair(1, SwiperItemInfo { 1, -1 }));
        }
        swiperLayoutAlgorithm->isLoop_ = false;
    }

    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            for (int k = 0; k <= 1; k++) {
                swiperLayoutAlgorithm->MeasureSwiper(&layoutWrapper, layoutConstraint, axis);
                if (j == 1) {
                    swiperLayoutAlgorithm->startMainPos_ = -1.0f;
                    continue;
                }
                if (i == 1) {
                    break;
                }
                swiperLayoutAlgorithm->jumpIndex_ = 1;
                swiperLayoutAlgorithm->startMainPos_ = 1.0f;
            }
            if (i == 1) {
                break;
            }
            swiperLayoutAlgorithm->jumpIndex_ = 0;
        }
        swiperLayoutAlgorithm->jumpIndex_ = 1;
        swiperLayoutAlgorithm->startMainPos_ = -1.0f;
    }

    swiperLayoutAlgorithm->startMainPos_ = -1.0f;
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            for (int k = 0; k <= 1; k++) {
                swiperLayoutAlgorithm->MeasureSwiper(&layoutWrapper, layoutConstraint, axis);
                if (j == 1) {
                    swiperLayoutAlgorithm->startMainPos_ = -1.0f;
                    swiperLayoutAlgorithm->spaceWidth_ = 0.0f;
                    continue;
                }
                if (i == 1 && j == 1) {
                    break;
                }
                swiperLayoutAlgorithm->startMainPos_ = 2.0f;
                swiperLayoutAlgorithm->spaceWidth_ = -2.0f;
            }
            if (i == 1) {
                swiperLayoutAlgorithm->isLoop_ = true;
                continue;
            }
            if (i == 1 && j == 1) {
                break;
            }
            swiperLayoutAlgorithm->isLoop_ = false;
        }
        swiperLayoutAlgorithm->prevMargin_ = -1.0f;
    }

    swiperLayoutAlgorithm->jumpIndex_.reset();
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            for (int k = 0; k <= 1; k++) {
                swiperLayoutAlgorithm->MeasureSwiper(&layoutWrapper, layoutConstraint, axis);
                if (i == 1 && j == 0) {
                    swiperLayoutAlgorithm->endMainPos_ = -2.0f;
                    continue;
                }
                if (i == 1 && j == 1) {
                    swiperLayoutAlgorithm->prevMargin_ = 1.0f;
                    continue;
                }
                if (i == 1 && j == 1 && k == 1) {
                    break;
                }
                swiperLayoutAlgorithm->targetIndex_ = 1;
                swiperLayoutAlgorithm->itemPosition_.clear();
            }
            if (i == 1) {
                swiperLayoutAlgorithm->targetIndex_ = 0;
                continue;
            }
            swiperLayoutAlgorithm->startMainPos_ = 2.0f;
        }
        swiperLayoutAlgorithm->targetIndex_ = -1.0f;
    }

    swiperLayoutAlgorithm->targetIndex_.reset();
    swiperLayoutAlgorithm->itemPosition_.emplace(std::make_pair(0, SwiperItemInfo { 1, 1 }));
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            for (int k = 0; k <= 1; k++) {
                swiperLayoutAlgorithm->MeasureSwiper(&layoutWrapper, layoutConstraint, axis);
                if (j == 1) {
                    swiperLayoutAlgorithm->itemPosition_.clear();
                    swiperLayoutAlgorithm->itemPosition_.emplace(std::make_pair(1, SwiperItemInfo { 1, 1 }));
                    continue;
                }
                swiperLayoutAlgorithm->itemPosition_.clear();
                swiperLayoutAlgorithm->itemPosition_.emplace(std::make_pair(0, SwiperItemInfo { 3, 1 }));
                swiperLayoutAlgorithm->currentOffset_ = -1.0f;
            }
            swiperLayoutAlgorithm->itemPosition_.clear();
            swiperLayoutAlgorithm->itemPosition_.emplace(std::make_pair(1, SwiperItemInfo { 3, 1 }));
        }
        swiperLayoutAlgorithm->overScrollFeature_ = true;
    }

    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            swiperLayoutAlgorithm->MeasureSwiper(&layoutWrapper, layoutConstraint, axis);
            if (i == 1) {
                swiperLayoutAlgorithm->endMainPos_ = 1.0f;
                continue;
            }
            swiperLayoutAlgorithm->endMainPos_ = 2.0f;
        }
        swiperLayoutAlgorithm->itemPosition_.emplace(std::make_pair(-1, SwiperItemInfo { 3, 1 }));
    }
    swiperLayoutAlgorithm->overScrollFeature_ = false;
    swiperLayoutAlgorithm->currentOffset_ = 0;
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            swiperLayoutAlgorithm->MeasureSwiper(&layoutWrapper, layoutConstraint, axis);
            if (i == 1) {
                swiperLayoutAlgorithm->startMainPos_ = 0;
                continue;
            }
            swiperLayoutAlgorithm->startMainPos_ = 4;
        }
        swiperLayoutAlgorithm->itemPosition_.clear();
        swiperLayoutAlgorithm->itemPosition_.emplace(std::make_pair(-1, SwiperItemInfo { 1, 1 }));
    }
}

/**
 * @tc.name: SwiperPatternHandleDragEnd001
 * @tc.desc: HandleDragEnd
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternHandleDragEnd001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {
        model.SetDisplayArrow(true); // show arrow
        model.SetHoverShow(false);
        model.SetArrowStyle(ARROW_PARAMETERS);
    });
    auto dimension = Dimension(1);
    layoutProperty_->UpdateMinSize(dimension);
    double dragVelocity = 0.1;
    pattern_->leftButtonId_.reset();
    pattern_->rightButtonId_.reset();
    pattern_->GetLayoutProperty<SwiperLayoutProperty>()->UpdateShowIndicator(false);
    pattern_->itemPosition_.clear();

    /**
     * @tc.steps: step2. call HandleDragEnd.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            pattern_->HandleDragEnd(dragVelocity);
            if (i == 1) {
                break;
            }
            pattern_->itemPosition_.emplace(std::make_pair(1, SwiperItemInfo { 1, 2 }));
            pattern_->itemPosition_.emplace(std::make_pair(0, SwiperItemInfo { 1, 2 }));
        }
        pattern_->swiperController_->removeSwiperEventCallback_ = []() {};
        ASSERT_NE(&(pattern_->swiperController_->removeSwiperEventCallback_), nullptr);
    }
}

/**
 * @tc.name: UpdateCurrentOffset001
 * @tc.desc: UpdateCurrentOffset
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, UpdateCurrentOffset001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    pattern_->UpdateCurrentOffset(10.f);
    EXPECT_EQ(pattern_->currentDelta_, -10.f);
}

/**
 * @tc.name: UpdateCurrentOffset002
 * @tc.desc: UpdateCurrentOffset
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, UpdateCurrentOffset002, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {
        model.SetLoop(false);
    });
    EXPECT_EQ(pattern_->GetEdgeEffect(), EdgeEffect::SPRING);
    pattern_->childScrolling_ = true;
    pattern_->UpdateCurrentOffset(10.f);
    EXPECT_EQ(pattern_->currentDelta_, -10.f);
    pattern_->UpdateCurrentOffset(-20.f);
    EXPECT_EQ(pattern_->currentDelta_, 10.f);
}

/**
 * @tc.name: UpdateCurrentOffset003
 * @tc.desc: UpdateCurrentOffset
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, UpdateCurrentOffset003, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {
        model.SetLoop(false);
        model.SetEdgeEffect(EdgeEffect::FADE);
    });
    EXPECT_EQ(pattern_->GetEdgeEffect(), EdgeEffect::FADE);
    pattern_->childScrolling_ = true;
    pattern_->UpdateCurrentOffset(10.f);
    EXPECT_EQ(pattern_->currentDelta_, -10.f);
    pattern_->UpdateCurrentOffset(-20.f);
    EXPECT_EQ(pattern_->currentDelta_, 10.f);
}

/**
 * @tc.name: UpdateCurrentOffset004
 * @tc.desc: UpdateCurrentOffset
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, UpdateCurrentOffset004, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {
        model.SetLoop(false);
        model.SetEdgeEffect(EdgeEffect::NONE);
    });
    EXPECT_EQ(pattern_->GetEdgeEffect(), EdgeEffect::NONE);
    pattern_->childScrolling_ = true;
    pattern_->UpdateCurrentOffset(10.f);
    EXPECT_EQ(pattern_->currentDelta_, -10.f);
    pattern_->UpdateCurrentOffset(-20.f);
    EXPECT_EQ(pattern_->currentDelta_, 10.f);
}

/**
 * @tc.name: UpdateCurrentOffset005
 * @tc.desc: UpdateCurrentOffset
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, UpdateCurrentOffset005, TestSize.Level1)
{
    Create([](SwiperModelNG model) {});
    pattern_->UpdateCurrentOffset(10.f);
    EXPECT_EQ(pattern_->currentDelta_, 0.f);
}

/**
 * @tc.name: PanEvent001
 * @tc.desc: PanEvent
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, PanEvent001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    auto actionStart = pattern_->panEvent_->GetActionStartEventFunc();
    auto actionUpdate = pattern_->panEvent_->GetActionUpdateEventFunc();
    auto actionEnd = pattern_->panEvent_->GetActionEndEventFunc();
    auto actionCancel = pattern_->panEvent_->GetActionCancelEventFunc();

    GestureEvent info;
    info.SetInputEventType(InputEventType::AXIS);
    info.SetSourceTool(SourceTool::MOUSE);
    info.SetMainDelta(10.f);
    actionStart(info);
    actionUpdate(info);
    actionEnd(info);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetCurrentIndex(), 3);

    info.SetMainDelta(-10.f);
    actionStart(info);
    actionUpdate(info);
    EXPECT_EQ(pattern_->GetCurrentIndex(), 3);
    actionEnd(info);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetCurrentIndex(), 0);
}

/**
 * @tc.name: PanEvent002
 * @tc.desc: PanEvent, test HandleDrag
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, PanEvent002, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    auto actionStart = pattern_->panEvent_->GetActionStartEventFunc();
    auto actionUpdate = pattern_->panEvent_->GetActionUpdateEventFunc();
    auto actionEnd = pattern_->panEvent_->GetActionEndEventFunc();
    auto actionCancel = pattern_->panEvent_->GetActionCancelEventFunc();

    GestureEvent info;
    info.SetMainDelta(10.f);
    info.SetMainVelocity(1200.f);
    info.SetGlobalLocation(Offset(100.f, 100.f));
    actionStart(info);
    actionUpdate(info);
    actionEnd(info);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetCurrentIndex(), 0);
}

/**
 * @tc.name: SwiperPatternBeforeCreateLayoutWrapper001
 * @tc.desc: BeforeCreateLayoutWrapper
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternBeforeCreateLayoutWrapper001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {
        model.SetDisplayArrow(true); // show arrow
        model.SetHoverShow(false);
        model.SetArrowStyle(ARROW_PARAMETERS);
    });
    auto leftArrowNode = GetChildFrameNode(frameNode_, 5);
    auto rightArrowNode = GetChildFrameNode(frameNode_, 6);
    pattern_->leftButtonId_.reset();
    pattern_->rightButtonId_ = 1;
    pattern_->GetLayoutProperty<SwiperLayoutProperty>()->UpdateShowIndicator(true);
    pattern_->GetLayoutProperty<SwiperLayoutProperty>()->UpdateIndex(-1);

    /**
     * @tc.steps: step2. call BeforeCreateLayoutWrapper.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            pattern_->BeforeCreateLayoutWrapper();
            if (i == 1) {
                frameNode_->AddChild(leftArrowNode);
                continue;
            }
            pattern_->rightButtonId_.reset();
            pattern_->GetLayoutProperty<SwiperLayoutProperty>()->UpdateShowIndicator(false);
        }
        pattern_->GetLayoutProperty<SwiperLayoutProperty>()->UpdateIndex(0);
    }

    frameNode_->AddChild(rightArrowNode);
    pattern_->currentIndex_ = 0;
    pattern_->oldIndex_ = 0;
    for (int i = 0; i <= 1; i++) {
        pattern_->BeforeCreateLayoutWrapper();
        pattern_->currentIndex_ = 1;
    }
    pattern_->jumpIndex_.reset();
    pattern_->leftButtonId_.reset();
    pattern_->rightButtonId_ = 1;
    pattern_->GetLayoutProperty<SwiperLayoutProperty>()->UpdateShowIndicator(true);
    pattern_->GetLayoutProperty<SwiperLayoutProperty>()->UpdateLoop(true);
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            for (int k = 0; k <= 1; k++) {
                pattern_->BeforeCreateLayoutWrapper();
                if (i == 1 && j == 0) {
                    pattern_->jumpIndex_ = 0;
                    continue;
                }
                if (i == 1 && j == 1) {
                    pattern_->jumpIndex_ = 10;
                    continue;
                }
                pattern_->jumpIndex_ = -1;
                pattern_->usePropertyAnimation_ = true;
            }
            pattern_->jumpIndex_ = 10;
            pattern_->rightButtonId_.reset();
            pattern_->GetLayoutProperty<SwiperLayoutProperty>()->UpdateShowIndicator(false);
            frameNode_->AddChild(leftArrowNode);
            frameNode_->AddChild(rightArrowNode);
        }
        pattern_->GetLayoutProperty<SwiperLayoutProperty>()->UpdateLoop(false);
        pattern_->jumpIndex_ = -1;
    }
}

/**
 * @tc.name: SwiperPatternTriggerAnimationEndOnForceStop001
 * @tc.desc: TriggerAnimationEndOnForceStop
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternTriggerAnimationEndOnForceStop001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {
        model.SetDisplayArrow(true); // show arrow
        model.SetHoverShow(false);
        model.SetArrowStyle(ARROW_PARAMETERS);
    });
    auto rightArrowNode = GetChildFrameNode(frameNode_, 6);
    pattern_->UpdateIndexOnSwipePageStop(1);
    pattern_->currentIndex_ = 0;
    pattern_->pauseTargetIndex_ = 2;
    pattern_->itemPosition_.clear();

    /**
     * @tc.steps: step2. call TriggerAnimationEndOnForceStop.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            pattern_->TriggerAnimationEndOnForceStop();
            pattern_->currentIndex_ = 1;
        }
            frameNode_->AddChild(rightArrowNode);
        pattern_->currentIndex_ = 0;
    }
}

/**
 * @tc.name: SwiperPatternIsVisibleChildrenSizeLessThanSwiper001
 * @tc.desc: IsVisibleChildrenSizeLessThanSwiper
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternIsVisibleChildrenSizeLessThanSwiper001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {
        model.SetDisplayArrow(true); // show arrow
        model.SetHoverShow(false);
        model.SetArrowStyle(ARROW_PARAMETERS);
    });
    auto leftArrowNode = GetChildFrameNode(frameNode_, 5);
    auto rightArrowNode = GetChildFrameNode(frameNode_, 6);
    layoutProperty_->UpdateDisplayCount(5);
    pattern_->IsVisibleChildrenSizeLessThanSwiper();
    pattern_->leftButtonId_.reset();
    pattern_->rightButtonId_.reset();
    pattern_->GetLayoutProperty<SwiperLayoutProperty>()->UpdateShowIndicator(false);
    pattern_->itemPosition_.clear();
    auto dimension = Dimension(1);
    layoutProperty_->UpdateMinSize(dimension);
    EXPECT_EQ(static_cast<int32_t>(pattern_->itemPosition_.size()), 0);

    /**
     * @tc.steps: step2. call IsVisibleChildrenSizeLessThanSwiper.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            pattern_->IsVisibleChildrenSizeLessThanSwiper();
            if (i == 1) {
                pattern_->itemPosition_.emplace(std::make_pair(2, SwiperItemInfo { 1, 2 }));
                continue;
            }
            pattern_->itemPosition_.emplace(std::make_pair(1, SwiperItemInfo { 1, 2 }));
            pattern_->itemPosition_.emplace(std::make_pair(0, SwiperItemInfo { 1, 2 }));
        }
        pattern_->itemPosition_.clear();
        pattern_->itemPosition_.emplace(std::make_pair(0, SwiperItemInfo { 1, 2 }));
        pattern_->itemPosition_.emplace(std::make_pair(1, SwiperItemInfo { 1, 1 }));
    }

    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            pattern_->IsVisibleChildrenSizeLessThanSwiper();
            pattern_->itemPosition_.clear();
            pattern_->itemPosition_.emplace(std::make_pair(0, SwiperItemInfo { 1, 2 }));
            pattern_->itemPosition_.emplace(std::make_pair(2, SwiperItemInfo { 1, 2 }));
        }
    }
}

/**
 * @tc.name: SwiperPatternSwipeToWithoutAnimation001
 * @tc.desc: SwipeToWithoutAnimation
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternSwipeToWithoutAnimation001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {
        model.SetDisplayArrow(true); // show arrow
        model.SetHoverShow(false);
        model.SetArrowStyle(ARROW_PARAMETERS);
    });
    int32_t index = 1;
    pattern_->leftButtonId_.reset();
    pattern_->rightButtonId_.reset();
    pattern_->GetLayoutProperty<SwiperLayoutProperty>()->UpdateShowIndicator(false);
    pattern_->itemPosition_.emplace(std::make_pair(1, SwiperItemInfo { 1, 2 }));
    pattern_->itemPosition_.emplace(std::make_pair(0, SwiperItemInfo { 1, 2 }));

    /**
     * @tc.steps: step2. call SwipeToWithoutAnimation.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        pattern_->SwipeToWithoutAnimation(index);
        pattern_->usePropertyAnimation_ = true;
    }
}

/**
 * @tc.name: SwiperPatternGetLastItemInfoInVisibleArea001
 * @tc.desc: GetLastItemInfoInVisibleArea
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternGetLastItemInfoInVisibleArea001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    pattern_->itemPosition_.clear();

    /**
     * @tc.steps: step2. call GetLastItemInfoInVisibleArea.
     * @tc.expected: Related function runs ok.
     */
    pattern_->GetLastItemInfoInVisibleArea();
}

/**
 * @tc.name: SwiperPatternHandleDragUpdate001
 * @tc.desc: HandleDragUpdate
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternHandleDragUpdate001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    auto info = GestureEvent();
    auto localLocation = Offset(-1.0, 1.0);
    info.SetLocalLocation(localLocation);
    frameNode_->geometryNode_ = AceType::MakeRefPtr<GeometryNode>();
    frameNode_->geometryNode_->SetFrameOffset(OffsetF(1.0f, 2.0f));
    auto indicatorNode = GetChildFrameNode(frameNode_, 4);
    indicatorNode->geometryNode_ = AceType::MakeRefPtr<GeometryNode>();
    indicatorNode->geometryNode_->SetFrameOffset(OffsetF(1.0f, 2.0f));

    /**
     * @tc.steps: step2. call HandleDragUpdate.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        pattern_->HandleDragUpdate(info);
        info.SetLocalLocation(Offset(1.0, 2.0));
        frameNode_->geometryNode_->SetFrameSize(SizeF(2.0f, 3.0f));
        pattern_->indicatorId_ = 1;
        pattern_->GetLayoutProperty<SwiperLayoutProperty>()->UpdateShowIndicator(true);
        pattern_->GetLayoutProperty<SwiperLayoutProperty>()->UpdateIndicatorType(SwiperIndicatorType::DOT);
        indicatorNode->geometryNode_->SetFrameSize(SizeF(2.0f, 3.0f));
    }
}

/**
 * @tc.name: SwiperPatternHandleDragUpdate002
 * @tc.desc: HandleDragUpdate
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternHandleDragUpdate002, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    auto info = GestureEvent();
    auto localLocation = Offset(-1.0, 1.0);
    info.SetLocalLocation(localLocation);
    frameNode_->geometryNode_ = AceType::MakeRefPtr<GeometryNode>();
    frameNode_->geometryNode_->SetFrameOffset(OffsetF(1.0f, 2.0f));
    auto indicatorNode = GetChildFrameNode(frameNode_, 4);
    indicatorNode->geometryNode_ = AceType::MakeRefPtr<GeometryNode>();
    indicatorNode->geometryNode_->SetFrameOffset(OffsetF(1.0f, 2.0f));
    auto dragPoint =
        PointF(static_cast<float>(info.GetLocalLocation().GetX()), static_cast<float>(info.GetLocalLocation().GetY()));

    /**
     * @tc.steps: step2. call HandleDragUpdate.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        pattern_->HandleDragUpdate(info);
        info.SetLocalLocation(Offset(1.0, 2.0));
        frameNode_->geometryNode_->SetFrameSize(SizeF(2.0f, 3.0f));
        pattern_->indicatorId_ = 1;
        pattern_->GetLayoutProperty<SwiperLayoutProperty>()->UpdateShowIndicator(true);
        pattern_->GetLayoutProperty<SwiperLayoutProperty>()->UpdateIndicatorType(SwiperIndicatorType::DOT);
        indicatorNode->geometryNode_->SetFrameSize(SizeF(2.0f, 3.0f));
    }
}

/**
 * @tc.name: SwiperPatternBeforeCreateLayoutWrapper002
 * @tc.desc: BeforeCreateLayoutWrapper
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternBeforeCreateLayoutWrapper002, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});

    /**
     * @tc.steps: step2. call BeforeCreateLayoutWrapper.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            pattern_->BeforeCreateLayoutWrapper();
            if (i == 1) {
                pattern_->mainSizeIsMeasured_ = false;
                continue;
            }
            pattern_->mainSizeIsMeasured_ = true;
        }
        pattern_->isNeedResetPrevMarginAndNextMargin_ = true;
    }
}

/**
 * @tc.name: SwiperPatternBeforeCreateLayoutWrapper003
 * @tc.desc: BeforeCreateLayoutWrapper
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternBeforeCreateLayoutWrapper003, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    pattern_->itemPosition_.clear();
    pattern_->isVoluntarilyClear_ = false;

    /**
     * @tc.steps: step2. call BeforeCreateLayoutWrapper.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        pattern_->BeforeCreateLayoutWrapper();
        pattern_->GetPaintProperty<SwiperPaintProperty>()->UpdateAutoPlay(true);
    }
}

/**
 * @tc.name: SwiperPatternIsVisibleChildrenSizeLessThanSwiper002
 * @tc.desc: IsVisibleChildrenSizeLessThanSwiper
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternIsVisibleChildrenSizeLessThanSwiper002, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {
        model.SetDisplayArrow(true); // show arrow
        model.SetHoverShow(false);
        model.SetArrowStyle(ARROW_PARAMETERS);
    });
    pattern_->GetLayoutProperty<SwiperLayoutProperty>()->UpdateShowIndicator(false);
    pattern_->itemPosition_.clear();
    pattern_->leftButtonId_.reset();
    pattern_->rightButtonId_.reset();
    auto dimension = Dimension(1);
    layoutProperty_->UpdateMinSize(dimension);
    pattern_->itemPosition_.emplace(std::make_pair(0, SwiperItemInfo { 1, 2 }));
    pattern_->itemPosition_.emplace(std::make_pair(1, SwiperItemInfo { 1, 3 }));

    /**
     * @tc.steps: step2. call IsVisibleChildrenSizeLessThanSwiper.
     * @tc.expected: Related function runs ok.
     */
    pattern_->IsVisibleChildrenSizeLessThanSwiper();
}

/**
 * @tc.name: SwiperPatternHandleDragEnd002
 * @tc.desc: HandleDragEnd
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternHandleDragEnd002, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {
        model.SetDisplayArrow(true); // show arrow
        model.SetHoverShow(false);
        model.SetArrowStyle(ARROW_PARAMETERS);
    });
    auto dimension = Dimension(1);
    layoutProperty_->UpdateMinSize(dimension);
    double dragVelocity = 0.1;
    pattern_->GetLayoutProperty<SwiperLayoutProperty>()->UpdateShowIndicator(false);
    pattern_->itemPosition_.clear();
    pattern_->leftButtonId_.reset();
    pattern_->rightButtonId_.reset();
    pattern_->itemPosition_.emplace(std::make_pair(1, SwiperItemInfo { 1, 2 }));
    pattern_->itemPosition_.emplace(std::make_pair(0, SwiperItemInfo { 1, 2 }));
    layoutProperty_->UpdateLoop(false);
    layoutProperty_->UpdateDisplayCount(0);
    layoutProperty_->UpdateMinSize(Dimension(-1));
    layoutProperty_->UpdateDisplayMode(SwiperDisplayMode::AUTO_LINEAR);
    pattern_->fadeOffset_ = 1.0f;

    /**
     * @tc.steps: step2. call HandleDragEnd.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            pattern_->HandleDragEnd(dragVelocity);
            if (i == 1) {
                break;
            }
            pattern_->itemPosition_.clear();
            pattern_->itemPosition_.emplace(std::make_pair(0, SwiperItemInfo { 1, 2 }));
            pattern_->itemPosition_.emplace(std::make_pair(-1, SwiperItemInfo { 1, 2 }));
            pattern_->GetPaintProperty<SwiperPaintProperty>()->UpdateEdgeEffect(EdgeEffect::NONE);
        }
        pattern_->itemPosition_.clear();
        pattern_->itemPosition_.emplace(std::make_pair(2, SwiperItemInfo { 1, 2 }));
        pattern_->itemPosition_.emplace(std::make_pair(1, SwiperItemInfo { 1, 2 }));
        pattern_->GetPaintProperty<SwiperPaintProperty>()->UpdateEdgeEffect(EdgeEffect::FADE);
    }
}

/**
 * @tc.name: SwiperPatternShowPrevious002
 * @tc.desc: ShowPrevious
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternShowPrevious002, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    layoutProperty_->UpdateShowIndicator(false);
    ASSERT_EQ(pattern_->TotalCount(), 5);
    pattern_->currentIndex_ = 0;
    pattern_->preTargetIndex_ = -1;

    layoutProperty_->UpdateLoop(true);
    layoutProperty_->UpdateDisplayCount(-3);
    layoutProperty_->UpdateMinSize(Dimension(-1));
    layoutProperty_->UpdateDisplayMode(SwiperDisplayMode::AUTO_LINEAR);
    EXPECT_EQ(pattern_->TotalDisPlayCount(), 1);
    EXPECT_TRUE(pattern_->IsLoop());
    pattern_->leftButtonId_.reset();
    pattern_->rightButtonId_.reset();
    pattern_->itemPosition_.emplace(std::make_pair(1, SwiperItemInfo { 1, 2 }));
    pattern_->itemPosition_.emplace(std::make_pair(0, SwiperItemInfo { 1, 2 }));

    /**
     * @tc.steps: step2. call ShowPrevious.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            pattern_->ShowPrevious();
            if (i == 1) {
                layoutProperty_->UpdateDisplayCount(-3);
                continue;
            }
            layoutProperty_->UpdateDisplayCount(0);
        }
        }

    for (int i = 0; i <= 1; i++) {
        pattern_->ShowPrevious();
        pattern_->isVisible_ = false;
        pattern_->preTargetIndex_ = 0;
    }
}

/**
 * @tc.name: SwiperLayoutAlgorithmMeasureSwiper002
 * @tc.desc: MeasureSwiper
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperLayoutAlgorithmMeasureSwiper002, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    auto swiperLayoutAlgorithm = AceType::DynamicCast<SwiperLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper = LayoutWrapperNode(indicatorNode, geometryNode, indicatorNode->GetLayoutProperty());
    layoutWrapper.currentChildCount_ = 2;
    LayoutConstraintF layoutConstraint;
    layoutConstraint.maxSize = SizeF(720.f, 1136.f);
    layoutConstraint.percentReference = SizeF(720.f, 1136.f);
    layoutConstraint.parentIdealSize.SetSize(SizeF(720.f, 1136.f));
    ASSERT_NE(layoutWrapper.layoutProperty_, nullptr);
    layoutWrapper.GetLayoutProperty()->UpdateLayoutConstraint(layoutConstraint);
    Axis axis = Axis::HORIZONTAL;
    swiperLayoutAlgorithm->totalItemCount_ = 2;
    swiperLayoutAlgorithm->itemPosition_.emplace(std::make_pair(0, SwiperItemInfo { 1.0f, 2.0f }));
    swiperLayoutAlgorithm->isLoop_ = false;
    swiperLayoutAlgorithm->targetIndex_ = 1;

    /**
     * @tc.steps: step2. call MeasureSwiper
     * @tc.expected: Related function runs ok.
     */
    swiperLayoutAlgorithm->MeasureSwiper(&layoutWrapper, layoutConstraint, axis);
}

/**
 * @tc.name: SwiperInitIndicator006
 * @tc.desc: Test SwiperPattern SwiperInitIndicator
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperInitIndicator006, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    layoutProperty_->UpdateShowIndicator(true);
    layoutProperty_->UpdateIndicatorType(SwiperIndicatorType::DIGIT);
    pattern_->lastSwiperIndicatorType_ = SwiperIndicatorType::DOT;

    /**
     * @tc.steps: step2. call InitIndicator.
     * @tc.expected: frameNode_ lastChild is SWIPER_INDICATOR_ETS_TAG
     */
    pattern_->InitIndicator();
    ASSERT_EQ(frameNode_->GetLastChild()->GetTag(), V2::SWIPER_INDICATOR_ETS_TAG);
}

/**
 * @tc.name: SwiperPatternAutoPlay002
 * @tc.desc: StartAutoPlay
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternAutoPlay002, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {
        model.SetDisplayArrow(true); // show arrow
        model.SetHoverShow(false);
        model.SetArrowStyle(ARROW_PARAMETERS);
    });
    frameNode_->GetPaintProperty<SwiperPaintProperty>()->UpdateAutoPlay(true);
    layoutProperty_->UpdateLoop(true);
    layoutProperty_->ResetDisplayCount();
    layoutProperty_->ResetMinSize();
    layoutProperty_->UpdateDisplayMode(SwiperDisplayMode::AUTO_LINEAR);
    pattern_->isVisible_ = true;
    pattern_->isIndicatorLongPress_ = false;
    pattern_->leftButtonId_.reset();
    pattern_->rightButtonId_.reset();
    layoutProperty_->UpdateShowIndicator(false);

    /**
     * @tc.steps: step2. call StartAutoPlay.
     * @tc.expected: Related functions run ok.
     */
    pattern_->StartAutoPlay();
}

/**
 * @tc.name: SwiperPatternCreateLayoutAlgorithm002
 * @tc.desc: CreateLayoutAlgorithm
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternCreateLayoutAlgorithm002, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    pattern_->jumpIndex_.reset();
    pattern_->targetIndex_ = 1;

    /**
     * @tc.steps: step2. call CreateLayoutAlgorithm.
     * @tc.expected: Related function runs ok.
     */
    pattern_->CreateLayoutAlgorithm();
}

/**
 * @tc.name: SwiperPatternCreateLayoutAlgorithm003
 * @tc.desc: CreateLayoutAlgorithm
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternCreateLayoutAlgorithm003, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    float velocity = 0.1f;

    /**
     * @tc.steps: step2. call CreateLayoutAlgorithm.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        pattern_->UpdateAnimationProperty(velocity);
        pattern_->isDragging_ = true;
    }
}

/**
 * @tc.name: SwiperPatternOnTouchTestHit002
 * @tc.desc: OnTouchTestHit
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternOnTouchTestHit002, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    auto hitTestType = SourceType::MOUSE;

    /**
     * @tc.steps: step2. call OnTouchTestHit.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        pattern_->OnTouchTestHit(hitTestType);
        pattern_->isTouchDown_ = true;
    }
}

/**
 * @tc.name: SwiperPatternHandleTouchDown001
 * @tc.desc: HandleTouchDown
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternHandleTouchDown001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    pattern_->usePropertyAnimation_ = true;

    /**
     * @tc.steps: step2. call HandleTouchDown.
     * @tc.expected: Related function runs ok.
     */
    TouchLocationInfo touchLocationInfo("down", 0);
    touchLocationInfo.SetTouchType(TouchType::DOWN);
    pattern_->HandleTouchDown(touchLocationInfo);
}

/**
 * @tc.name: SwiperPatternPlayPropertyTranslateAnimation002
 * @tc.desc: PlayPropertyTranslateAnimation
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternPlayPropertyTranslateAnimation002, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    pattern_->usePropertyAnimation_ = true;
    float translate = 0.1f;
    int32_t nextIndex = 1;
    float velocity = 0.1f;
    pattern_->usePropertyAnimation_ = true;
    pattern_->itemPositionInAnimation_.clear();
    pattern_->targetIndex_ = 1;

    /**
     * @tc.steps: step2. call HandleTouchDown.
     * @tc.expected: Related function runs ok.
     */
    pattern_->PlayPropertyTranslateAnimation(translate, nextIndex, velocity);
}

/**
 * @tc.name: SwiperIndicatorPatternTestNg001
 * @tc.desc: HandleMouseEvent
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperIndicatorPatternTestNg001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {
        model.SetDirection(Axis::VERTICAL);
    });
    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    auto info = MouseInfo();
    indicatorPattern->HandleMouseEvent(info);
}

/**
 * @tc.name: SwiperIndicatorPatternTestNg002
 * @tc.desc: HandleTouchEvent
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperIndicatorPatternTestNg002, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {
        model.SetDirection(Axis::VERTICAL);
    });
    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    TouchLocationInfo touchLocationInfo("down", 0);
    touchLocationInfo.SetTouchType(TouchType::DOWN);
    std::list<TouchLocationInfo> infoSwiper;
    infoSwiper.emplace_back(touchLocationInfo);
    TouchEventInfo touchEventInfo("down");
    touchEventInfo.touches_ = infoSwiper;
    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    touchEventInfo.touches_.begin()->SetTouchType(TouchType::UP);
    indicatorPattern->HandleTouchEvent(touchEventInfo);
    touchEventInfo.touches_.begin()->SetTouchType(TouchType::CANCEL);
    indicatorPattern->HandleTouchEvent(touchEventInfo);
    touchEventInfo.touches_.begin()->SetTouchType(TouchType::MOVE);
    indicatorPattern->isPressed_ = true;
    indicatorPattern->HandleTouchEvent(touchEventInfo);
}

/**
 * @tc.name: SwiperIndicatorPatternTestNg003
 * @tc.desc: HandleLongPress
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperIndicatorPatternTestNg003, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {
        model.SetDirection(Axis::VERTICAL);
    });
    auto indicatorNode = GetChildFrameNode(frameNode_, 4);
    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    auto info = GestureEvent();
    indicatorPattern->HandleLongPress(info);
}

/**
 * @tc.name: SwiperIndicatorPatternTestNg004
 * @tc.desc: HandleHoverEvent
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperIndicatorPatternTestNg004, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {
        model.SetDirection(Axis::VERTICAL);
    });
    auto indicatorNode = GetChildFrameNode(frameNode_, 4);
    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    indicatorPattern->HandleHoverEvent(true);
    indicatorPattern->HandleHoverEvent(false);
}

/**
 * @tc.name: SwiperInitArrow001
 * @tc.desc: Test SwiperPattern SwiperInitArrow
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperInitArrow001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {
        model.SetDisplayArrow(true); // show arrow
        model.SetHoverShow(false);
        model.SetArrowStyle(ARROW_PARAMETERS);
    });
    pattern_->leftButtonId_.reset();
    pattern_->rightButtonId_.reset();

    layoutProperty_->UpdateDisplayArrow(true);
    layoutProperty_->UpdateHoverShow(true);
    layoutProperty_->UpdateIsShowBackground(true);
    layoutProperty_->UpdateBackgroundSize(Dimension(1));
    layoutProperty_->UpdateBackgroundColor(Color(1));
    layoutProperty_->UpdateArrowSize(Dimension(1));
    layoutProperty_->UpdateArrowColor(Color(1));
    layoutProperty_->UpdateIsSidebarMiddle(true);

    /**
     * @tc.steps: step3. call InitArrow.
     * @tc.expected: frameNode_ lastChild is SWIPER_INDICATOR_ETS_TAG
     */
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            pattern_->InitArrow();
            if (i == 1) {
                break;
            }
            pattern_->leftButtonId_ = 1;
        }
        layoutProperty_->UpdateDisplayArrow(false);
    }

    pattern_->leftButtonId_ = 1;
    pattern_->rightButtonId_ = 1;
    pattern_->InitArrow();
    EXPECT_TRUE(pattern_->HasLeftButtonNode());
    EXPECT_TRUE(pattern_->HasRightButtonNode());
}

/**
 * @tc.name: SwiperModelNGSetDisplayCount001
 * @tc.desc: Test SetDisplayCount
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperModelNGSetDisplayCount001, TestSize.Level1)
{
    SwiperModelNG mode;
    auto controller = mode.Create();
    ViewAbstract::SetWidth(CalcLength(SWIPER_WIDTH));
    ViewAbstract::SetHeight(CalcLength(SWIPER_HEIGHT));
    ASSERT_NE(controller, nullptr);
    int32_t displayCount = 0;

    /**
     * @tc.steps: step3. call SetDisplayCount.
     * @tc.expected: the related function runs ok.
     */
    mode.SetDisplayCount(displayCount);
}

/**
 * @tc.name: SwiperLayoutAlgorithmMeasureSwiper003
 * @tc.desc: MeasureSwiper
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperLayoutAlgorithmMeasureSwiper003, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    auto swiperLayoutAlgorithm = AceType::DynamicCast<SwiperLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper = LayoutWrapperNode(indicatorNode, geometryNode, indicatorNode->GetLayoutProperty());
    layoutWrapper.currentChildCount_ = 2;
    LayoutConstraintF layoutConstraint;
    layoutConstraint.maxSize = SizeF(720.f, 1136.f);
    layoutConstraint.percentReference = SizeF(720.f, 1136.f);
    layoutConstraint.parentIdealSize.SetSize(SizeF(720.f, 1136.f));
    ASSERT_NE(layoutWrapper.layoutProperty_, nullptr);
    layoutWrapper.GetLayoutProperty()->UpdateLayoutConstraint(layoutConstraint);
    Axis axis = Axis::HORIZONTAL;
    swiperLayoutAlgorithm->itemPosition_.emplace(std::make_pair(0, SwiperItemInfo { 1.0f, 0.0f }));
    swiperLayoutAlgorithm->prevMargin_ = -1.0f;

    /**
     * @tc.steps: step2. call MeasureSwiper
     * @tc.expected: Related function runs ok.
     */
    swiperLayoutAlgorithm->MeasureSwiper(&layoutWrapper, layoutConstraint, axis);
}

/**
 * @tc.name: SwiperLayoutAlgorithmLayoutForwardItem001
 * @tc.desc: LayoutForwardItem
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperLayoutAlgorithmLayoutForwardItem001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper = LayoutWrapperNode(frameNode_, geometryNode, frameNode_->GetLayoutProperty());
    LayoutConstraintF layoutConstraint;
    layoutConstraint.maxSize = SizeF(720.f, 1136.f);
    layoutConstraint.percentReference = SizeF(720.f, 1136.f);
    layoutConstraint.parentIdealSize.SetSize(SizeF(720.f, 1136.f));
    ASSERT_NE(layoutWrapper.layoutProperty_, nullptr);
    layoutWrapper.GetLayoutProperty()->UpdateLayoutConstraint(layoutConstraint);
    Axis axis = Axis::HORIZONTAL;
    int32_t currentIndex = 0;
    float endPos = 0.1f;
    float startPos = 0.2f;
    auto swiperLayoutAlgorithm = AceType::DynamicCast<SwiperLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    swiperLayoutAlgorithm->isLoop_ = true;
    auto firstLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(indicatorNode, geometryNode, indicatorNode->GetLayoutProperty());
    layoutWrapper.currentChildCount_ = 1;
    layoutWrapper.AppendChild(firstLayoutWrapper);
    swiperLayoutAlgorithm->totalItemCount_ = 2;
    indicatorNode->layoutProperty_ = AceType::MakeRefPtr<SwiperLayoutProperty>();
    AceType::DynamicCast<SwiperLayoutProperty>(layoutWrapper.GetLayoutProperty())->ResetDisplayCount();
    AceType::DynamicCast<SwiperLayoutProperty>(layoutWrapper.GetLayoutProperty())
        ->UpdateDisplayMode(SwiperDisplayMode::AUTO_LINEAR);

    /**
     * @tc.steps: step2. call LayoutForwardItem.
     * @tc.expected: Related function runs ok.
     */
    swiperLayoutAlgorithm->LayoutForwardItem(&layoutWrapper, layoutConstraint, axis, currentIndex, endPos, startPos);
}

/**
 * @tc.name: SwiperFlushFocus002
 * @tc.desc: Swiper FlushFocus.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperFlushFocus002, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    eventHub_->AttachHost(frameNode_);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(eventHub_);
    focusHub->currentFocus_ = true;
    focusHub->currentFocus_ = true;

    /**
     * @tc.steps: step2. Create curShowFrameNode, addChild to frameNode.
     */
    auto curShowFrame = AceType::MakeRefPtr<FrameNode>(V2::ROW_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    auto child = AceType::MakeRefPtr<FrameNode>(V2::BUTTON_ETS_TAG, -1, AceType::MakeRefPtr<SwiperPattern>());
    auto child1 = AceType::MakeRefPtr<FrameNode>(V2::BUTTON_ETS_TAG, -1, AceType::MakeRefPtr<SwiperPattern>());
    child->GetOrCreateFocusHub();
    child1->GetOrCreateFocusHub();
    curShowFrame->AddChild(child);
    frameNode_->AddChild(child1);
    auto eventHub1 = AceType::MakeRefPtr<EventHub>();
    eventHub1->AttachHost(child);
    auto focusHub1 = AceType::MakeRefPtr<FocusHub>(eventHub1);
    auto eventHub2 = AceType::MakeRefPtr<EventHub>();
    eventHub2->AttachHost(child1);
    auto focusHub2 = AceType::MakeRefPtr<FocusHub>(eventHub2);

    /**
     * @tc.steps: step3. test FlushFocus with IsShowIndicator() is true.
     * @tc.expected: the related function runs ok.
     */
    layoutProperty_->UpdateShowIndicator(true);
    pattern_->isLastIndicatorFocused_ = true;
    pattern_->FlushFocus(curShowFrame);
}

/**
 * @tc.name: SwiperPatternShowPrevious003
 * @tc.desc: ShowPrevious
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternShowPrevious003, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {
        model.SetDisplayArrow(true); // show arrow
        model.SetHoverShow(false);
        model.SetArrowStyle(ARROW_PARAMETERS);
    });
    pattern_->currentIndex_ = 0;
    pattern_->preTargetIndex_ = 1;

    layoutProperty_->UpdateLoop(true);
    layoutProperty_->ResetDisplayCount();
    layoutProperty_->ResetMinSize();
    layoutProperty_->UpdateDisplayMode(SwiperDisplayMode::AUTO_LINEAR);
    pattern_->leftButtonId_.reset();
    pattern_->rightButtonId_.reset();
    layoutProperty_->UpdateShowIndicator(false);
    pattern_->itemPosition_.emplace(std::make_pair(1, SwiperItemInfo { 1.0f, 2.0f }));
    pattern_->itemPosition_.emplace(std::make_pair(0, SwiperItemInfo { 1.0f, 2.0f }));
    EXPECT_FALSE(pattern_->IsVisibleChildrenSizeLessThanSwiper());
    EXPECT_TRUE(pattern_->preTargetIndex_.has_value());
    EXPECT_TRUE(pattern_->IsLoop());
    EXPECT_EQ(pattern_->TotalCount(), 7);
    EXPECT_EQ(pattern_->GetDisplayCount(), 1);
    pattern_->targetIndex_ = 2;
    EXPECT_FALSE(pattern_->GetLoopIndex(pattern_->preTargetIndex_.value()) <= 0 && !pattern_->IsLoop());
    EXPECT_FALSE(pattern_->IsVisibleChildrenSizeLessThanSwiper());

    /**
     * @tc.steps: step2. call ShowPrevious.
     * @tc.expected: Related function runs ok.
     */
    pattern_->ShowPrevious();
    EXPECT_EQ(pattern_->preTargetIndex_.value(), -1);
    pattern_->isVisible_ = false;
    pattern_->preTargetIndex_ = 0;
    pattern_->isUserFinish_ = true;
    pattern_->ShowPrevious();
    EXPECT_EQ(pattern_->preTargetIndex_.value(), 0);
}

/**
 * @tc.name: SwiperOnLoopChange001
 * @tc.desc: Swiper OnLoopChange.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperOnLoopChange001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    pattern_->preLoop_ = true;
    layoutProperty_->UpdateLoop(false);
    layoutProperty_->ResetPrevMargin();
    layoutProperty_->ResetNextMargin();

    /**
     * @tc.steps: step2. call OnLoopChange.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            pattern_->OnLoopChange();
            if (i == 1) {
                layoutProperty_->ResetPrevMargin();
                continue;
            }
            layoutProperty_->UpdatePrevMargin(Dimension(1));
        }
        layoutProperty_->UpdateNextMargin(Dimension(1));
    }
}

/**
 * @tc.name: SwiperPatternInitPanEvent001
 * @tc.desc: Test InitPanEvent
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternInitPanEvent001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {
        model.SetDirection(Axis::VERTICAL);
    });

    /**
     * @tc.steps: step2. test InitPanEvent.
     * @tc.expected: Related function runs ok.
     */
    RefPtr<SwiperPattern> indicatorPattern = frameNode_->GetPattern<SwiperPattern>();
    auto gestureHub = AceType::MakeRefPtr<GestureEventHub>(eventHub_);
    indicatorPattern->direction_ = Axis::HORIZONTAL;
    indicatorPattern->GetLayoutProperty<SwiperLayoutProperty>()->UpdateDirection(Axis::VERTICAL);
    indicatorPattern->InitPanEvent(gestureHub);
    auto info = GestureEvent();
    info.SetInputEventType(InputEventType::AXIS);
    info.SetSourceTool(SourceTool::MOUSE);
    indicatorPattern->panEvent_->actionStart_(info);
    indicatorPattern->panEvent_->actionEnd_(info);
    info.SetMainDelta(1);
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            indicatorPattern->InitPanEvent(gestureHub);
            indicatorPattern->panEvent_->actionUpdate_(info);
            if (i == 1) {
                info.SetInputEventType(InputEventType::AXIS);
                continue;
            }
            info.SetInputEventType(InputEventType::MOUSE_BUTTON);
        }
        info.SetSourceTool(SourceTool::TOUCHPAD);
    }
    info.SetSourceTool(SourceTool::MOUSE);
    info.SetMainDelta(-1);
    indicatorPattern->InitPanEvent(gestureHub);
    indicatorPattern->panEvent_->actionUpdate_(info);
}

/**
 * @tc.name: SwiperPatternCheckMarkDirtyNodeForRenderIndicator001
 * @tc.desc: Test CheckMarkDirtyNodeForRenderIndicator
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternCheckMarkDirtyNodeForRenderIndicator001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    RefPtr<SwiperPattern> indicatorPattern = frameNode_->GetPattern<SwiperPattern>();

    /**
     * @tc.steps: step2. test CheckMarkDirtyNodeForRenderIndicator.
     * @tc.expected: Related function runs ok.
     */
    indicatorPattern->indicatorId_.reset();
    float additionalOffset = 0.1f;
    indicatorPattern->CheckMarkDirtyNodeForRenderIndicator(additionalOffset);
    indicatorPattern->indicatorId_ = 1;
    indicatorPattern->CheckMarkDirtyNodeForRenderIndicator(additionalOffset);
}

/**
 * @tc.name: SwiperIndicatorPatternHandleLongDragUpdate001
 * @tc.desc: HandleLongDragUpdate
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperIndicatorPatternHandleLongDragUpdate001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    auto indicatorNode = GetChildFrameNode(frameNode_, 4);
    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    TouchLocationInfo touchLocationInfo("down", 0);
    touchLocationInfo.SetTouchType(TouchType::DOWN);
    std::list<TouchLocationInfo> infoSwiper;
    infoSwiper.emplace_back(touchLocationInfo);
    TouchEventInfo touchEventInfo("down");
    touchEventInfo.touches_ = infoSwiper;
    pattern_->leftButtonId_.reset();
    pattern_->rightButtonId_.reset();
    pattern_->GetLayoutProperty<SwiperLayoutProperty>()->UpdateShowIndicator(false);
    layoutProperty_->UpdateDisplayCount(10);
    indicatorPattern->HandleLongDragUpdate(touchEventInfo.GetTouches().front());
}

/**
 * @tc.name: SwiperIndicatorPatternCheckIsTouchBottom001
 * @tc.desc: CheckIsTouchBottom
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperIndicatorPatternCheckIsTouchBottom001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    auto indicatorNode = GetChildFrameNode(frameNode_, 4);
    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    GestureEvent info;
    TouchLocationInfo touchLocationInfo("down", 0);
    touchLocationInfo.SetTouchType(TouchType::DOWN);
    std::list<TouchLocationInfo> infoSwiper;
    infoSwiper.emplace_back(touchLocationInfo);
    TouchEventInfo touchEventInfo("down");
    touchEventInfo.touches_ = infoSwiper;
    pattern_->currentIndex_ = -5;
    layoutProperty_->UpdateLoop(false);
    pattern_->leftButtonId_.reset();
    pattern_->rightButtonId_.reset();
    pattern_->GetLayoutProperty<SwiperLayoutProperty>()->UpdateShowIndicator(false);
    EXPECT_TRUE(indicatorPattern->CheckIsTouchBottom(info));
    EXPECT_TRUE(indicatorPattern->CheckIsTouchBottom(touchEventInfo.GetTouches().front()));
}

/**
 * @tc.name: SwiperPatternHandleTouchUp002
 * @tc.desc: HandleTouchUp
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternHandleTouchUp002, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    pattern_->isDragging_ = false;
    pattern_->itemPosition_.emplace(std::make_pair(0, SwiperItemInfo { 1.0f, 2.0f }));
    pattern_->velocity_ = 1.0f;

    /**
     * @tc.steps: step2. call HandleTouchUp.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            pattern_->HandleTouchUp();
            if (i == 1) {
                pattern_->isDragging_ = false;
                continue;
            }
            pattern_->isDragging_ = true;
        }
        pattern_->itemPosition_.clear();
        pattern_->itemPosition_.emplace(std::make_pair(0, SwiperItemInfo { 0.0f, 2.0f }));
    }
    EXPECT_FLOAT_EQ(pattern_->velocity_.value(), 1.f);
}

/**
 * @tc.name: SwiperPatternPlayIndicatorTranslateAnimation003
 * @tc.desc: PlayIndicatorTranslateAnimation
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternPlayIndicatorTranslateAnimation003, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    pattern_->stopIndicatorAnimation_ = false;
    pattern_->itemPosition_.clear();
    float translate = 0.1f;

    /**
     * @tc.steps: step2. call PlayIndicatorTranslateAnimation.
     * @tc.expected: Related function runs ok.
     */
    pattern_->PlayIndicatorTranslateAnimation(translate);
    pattern_->stopIndicatorAnimation_ = true;
    pattern_->indicatorId_ = 1;
    pattern_->PlayIndicatorTranslateAnimation(translate);
}

/**
 * @tc.name: SwiperPatternPlaySpringAnimation001
 * @tc.desc: PlaySpringAnimation
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternPlaySpringAnimation001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    pattern_->contentMainSize_ = 1.0f;
    pattern_->itemPosition_.clear();
    layoutProperty_->UpdatePrevMargin(Dimension(0.0f));
    layoutProperty_->UpdateNextMargin(Dimension(0.0f));
    double dragVelocity = 0.1f;

    /**
     * @tc.steps: step2. call PlaySpringAnimation.
     * @tc.expected: Related function runs ok.
     */
    pattern_->PlaySpringAnimation(dragVelocity);
}

/**
 * @tc.name: SwiperPatternHandleDragEnd003
 * @tc.desc: HandleDragEnd
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternHandleDragEnd003, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {
        model.SetDisplayArrow(true); // show arrow
        model.SetHoverShow(false);
        model.SetArrowStyle(ARROW_PARAMETERS);
    });
    EXPECT_NE(frameNode_->GetLayoutProperty<SwiperLayoutProperty>(), nullptr);
    layoutProperty_->UpdateLoop(false);
    layoutProperty_->ResetDisplayCount();
    layoutProperty_->ResetMinSize();
    layoutProperty_->UpdateDisplayMode(SwiperDisplayMode::AUTO_LINEAR);
    pattern_->leftButtonId_.reset();
    pattern_->rightButtonId_.reset();
    layoutProperty_->UpdateShowIndicator(false);
    pattern_->itemPosition_.emplace(std::make_pair(1, SwiperItemInfo { 1.0f, 2.0f }));
    pattern_->itemPosition_.emplace(std::make_pair(0, SwiperItemInfo { 1.0f, 2.0f }));
    double dragVelocity = 0.1;
    pattern_->fadeOffset_ = 1.0f;
    frameNode_->GetPaintProperty<SwiperPaintProperty>()->UpdateEdgeEffect(EdgeEffect::NONE);
    pattern_->currentIndex_ = 2;

    /**
     * @tc.steps: step2. call HandleDragEnd.
     * @tc.expected: Related function runs ok.
     */
    pattern_->swiperController_->SetAddTabBarEventCallback([] { return; });
    pattern_->HandleDragEnd(dragVelocity);
}

/**
 * @tc.name: SwiperIndicatorPatternHandleLongDrag001
 * @tc.desc: HandleLongDragUpdate
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperIndicatorPatternHandleLongDrag001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    auto indicatorNode = GetChildFrameNode(frameNode_, 4);
    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    TouchLocationInfo touchLocationInfo("down", 0);
    touchLocationInfo.SetTouchType(TouchType::DOWN);
    std::list<TouchLocationInfo> infoSwiper;
    infoSwiper.emplace_back(touchLocationInfo);
    TouchEventInfo touchEventInfo("down");
    touchEventInfo.touches_ = infoSwiper;
    pattern_->leftButtonId_.reset();
    pattern_->rightButtonId_.reset();
    pattern_->GetLayoutProperty<SwiperLayoutProperty>()->UpdateShowIndicator(false);
    indicatorPattern->HandleLongDragUpdate(touchEventInfo.GetTouches().front());
    layoutProperty_->UpdateDisplayCount(10);
    indicatorPattern->HandleLongDragUpdate(touchEventInfo.GetTouches().front());
}

/**
 * @tc.name: SwiperIndicatorPatternTouchBottom001
 * @tc.desc: CheckIsTouchBottom
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperIndicatorPatternTouchBottom001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {
        model.SetDirection(Axis::VERTICAL);
    });
    auto indicatorNode = AceType::DynamicCast<FrameNode>(frameNode_->GetChildAtIndex(4));
    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();

    GestureEvent info;
    info.mainDelta_ = 1.0f;
    TouchLocationInfo touchLocationInfo("down", 0);
    touchLocationInfo.SetTouchType(TouchType::DOWN);
    EXPECT_FALSE(indicatorPattern->CheckIsTouchBottom(info));
    EXPECT_TRUE(indicatorPattern->CheckIsTouchBottom(touchLocationInfo));

    pattern_->currentIndex_ = 0;
    layoutProperty_->UpdateLoop(false);
    pattern_->leftButtonId_ = 1;
    pattern_->rightButtonId_ = 1;
    pattern_->GetLayoutProperty<SwiperLayoutProperty>()->UpdateShowIndicator(true);
    EXPECT_TRUE(indicatorPattern->CheckIsTouchBottom(info));
    EXPECT_TRUE(indicatorPattern->CheckIsTouchBottom(touchLocationInfo));
}

/**
 * @tc.name: SwiperIndicatorPatternHandleDragEnd001
 * @tc.desc: HandleDragEnd
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperIndicatorPatternHandleDragEnd001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    auto indicatorNode = GetChildFrameNode(frameNode_, 4);
    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    auto paintProperty_ = pattern_->GetPaintProperty<SwiperPaintProperty>();
    CHECK_NULL_VOID(paintProperty_);
    indicatorPattern->HandleDragEnd(1.0f);
    paintProperty_->UpdateAutoPlay(true);
    indicatorPattern->HandleDragEnd(1.0f);
    ASSERT_TRUE(paintProperty_->GetAutoPlay().value_or(false));
}

/**
 * @tc.name: SwiperIndicatorGetMouseClickIndex001
 * @tc.desc: Test GetMouseClickIndex
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperIndicatorGetMouseClickIndex001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {
        model.SetDirection(Axis::VERTICAL);
    });
    auto indicatorNode = GetChildFrameNode(frameNode_, 4);
    RefPtr<SwiperIndicatorPattern> indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    auto paintProperty = indicatorNode->GetPaintProperty<DotIndicatorPaintProperty>();
    indicatorPattern->GetMouseClickIndex();
    paintProperty->UpdateIsCustomSize(true);
    indicatorPattern->GetMouseClickIndex();
    ASSERT_TRUE(paintProperty->GetIsCustomSizeValue(false));
}

/**
 * @tc.name: SwiperIndicatorPatternTestNg0010
 * @tc.desc: HandleLongPress
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperIndicatorPatternTestNg0010, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    auto indicatorNode = GetChildFrameNode(frameNode_, 4);
    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    auto paintProperty_ = pattern_->GetPaintProperty<SwiperPaintProperty>();
    CHECK_NULL_VOID(paintProperty_);
    paintProperty_->UpdateAutoPlay(true);
    auto info = GestureEvent();
    indicatorPattern->HandleLongPress(info);
    ASSERT_TRUE(paintProperty_->GetAutoPlay().value_or(false));
}

/**
 * @tc.name: SwiperIndicatorPatternTestNg0011
 * @tc.desc: HandleLongDragUpdate
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperIndicatorPatternTestNg0011, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    auto indicatorNode = GetChildFrameNode(frameNode_, 4);
    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    TouchLocationInfo touchLocationInfo("down", 0);
    touchLocationInfo.SetTouchType(TouchType::DOWN);
    std::list<TouchLocationInfo> infoSwiper;
    infoSwiper.emplace_back(touchLocationInfo);
    TouchEventInfo touchEventInfo("down");
    touchEventInfo.touches_ = infoSwiper;
    pattern_->leftButtonId_.reset();
    pattern_->rightButtonId_.reset();
    pattern_->GetLayoutProperty<SwiperLayoutProperty>()->UpdateShowIndicator(false);
    layoutProperty_->UpdateDisplayCount(10);
    touchEventInfo.touches_.front().localLocation_.SetX(50.0f);
    layoutProperty_->UpdateDirection(Axis::HORIZONTAL);
    indicatorPattern->HandleLongDragUpdate(touchEventInfo.GetTouches().front());
    pattern_->currentIndex_ = 0;
    layoutProperty_->UpdateLoop(false);
    indicatorPattern->HandleLongDragUpdate(touchEventInfo.GetTouches().front());
    indicatorPattern->HandleLongDragUpdate(touchEventInfo.GetTouches().front());
}

/**
 * @tc.name: SwiperIndicatorPatternTestNg0012
 * @tc.desc: HandleMouseEvent
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperIndicatorPatternTestNg0012, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {
        model.SetDirection(Axis::VERTICAL);
    });
    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    auto info = MouseInfo();
    info.SetSourceDevice(SourceType::TOUCH);
    indicatorPattern->HandleMouseEvent(info);
    info.action_ = MouseAction::PRESS;
    indicatorPattern->isClicked_ = true;
    indicatorPattern->hoverPoint_.SetX(5.0);
    indicatorPattern->hoverPoint_.SetY(15.0);
    info.localLocation_.SetX(5.0);
    info.localLocation_.SetY(15.0);
    indicatorPattern->HandleMouseEvent(info);
}

/**
 * @tc.name: SwiperIndicatorPatternTestNg0013
 * @tc.desc: InitHoverMouseEvent
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperIndicatorPatternTestNg0013, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    auto indicatorNode = GetChildFrameNode(frameNode_, 4);
    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    auto paintProperty_ = pattern_->GetPaintProperty<SwiperPaintProperty>();
    CHECK_NULL_VOID(paintProperty_);
    auto info = HoverInfo();
    auto info1 = MouseInfo();
    indicatorPattern->hoverEvent_ = nullptr;
    info.SetSourceDevice(SourceType::NONE);
    indicatorPattern->InitHoverMouseEvent();
    indicatorPattern->hoverEvent_->onHoverEventCallback_(true, info);
    indicatorPattern->mouseEvent_->onMouseCallback_(info1);
    indicatorPattern->hoverEvent_ = nullptr;
    info.SetSourceDevice(SourceType::TOUCH);
    indicatorPattern->InitHoverMouseEvent();
    indicatorPattern->hoverEvent_->onHoverEventCallback_(true, info);
}

/**
 * @tc.name: SwiperIndicatorPatternTestNg0014
 * @tc.desc: HandleMouseClick
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperIndicatorPatternTestNg0014, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    auto indicatorNode = GetChildFrameNode(frameNode_, 4);
    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    auto paintProperty_ = pattern_->GetPaintProperty<SwiperPaintProperty>();
    CHECK_NULL_VOID(paintProperty_);
    indicatorPattern->isRepeatClicked_ = true;
    auto info = GestureEvent();
    indicatorPattern->HandleMouseClick(info);
}

/**
 * @tc.name: SwiperIndicatorPatternTestNg0015
 * @tc.desc: HandleHoverEvent
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperIndicatorPatternTestNg0015, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {
        model.SetDirection(Axis::VERTICAL);
    });
    auto indicatorNode = GetChildFrameNode(frameNode_, 4);
    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    indicatorPattern->isHover_ = true;
    layoutProperty_->UpdateHoverShow(true);
    pattern_->isAtHotRegion_ = false;
    indicatorPattern->HandleHoverEvent(true);
    indicatorPattern->HandleHoverEvent(false);
}

/**
 * @tc.name: SwiperIndicatorPatternTestNg0016
 * @tc.desc: HandleLongDragUpdate
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperIndicatorPatternTestNg0016, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    auto indicatorNode = GetChildFrameNode(frameNode_, 4);
    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    TouchLocationInfo touchLocationInfo("down", 0);
    touchLocationInfo.SetTouchType(TouchType::DOWN);
    std::list<TouchLocationInfo> infoSwiper;
    infoSwiper.emplace_back(touchLocationInfo);
    TouchEventInfo touchEventInfo("down");
    touchEventInfo.touches_ = infoSwiper;
    pattern_->leftButtonId_.reset();
    pattern_->rightButtonId_.reset();
    pattern_->GetLayoutProperty<SwiperLayoutProperty>()->UpdateShowIndicator(false);
    layoutProperty_->UpdateDisplayCount(10);
    touchEventInfo.touches_.front().localLocation_.SetX(50.0f);
    layoutProperty_->UpdateDirection(Axis::HORIZONTAL);
    touchEventInfo.touches_.front().localLocation_.SetX(1.0f);
    indicatorPattern->dragStartPoint_.SetX(20.0f);
    indicatorPattern->HandleLongDragUpdate(touchEventInfo.GetTouches().front());
    touchEventInfo.touches_.front().localLocation_.SetX(1.0f);
    indicatorPattern->dragStartPoint_.SetX(10.0f);
    indicatorPattern->HandleLongDragUpdate(touchEventInfo.GetTouches().front());
}

/**
 * @tc.name: SwiperIndicatorPatternTestNg0017
 * @tc.desc: InitTouchEvent
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperIndicatorPatternTestNg0017, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    auto indicatorNode = GetChildFrameNode(frameNode_, 4);
    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    auto paintProperty_ = pattern_->GetPaintProperty<SwiperPaintProperty>();
    CHECK_NULL_VOID(paintProperty_);
    TouchEventInfo touchEventInfo("down");
    indicatorPattern->touchEvent_ = nullptr;
    auto gestureHub = frameNode_->GetOrCreateGestureEventHub();
    indicatorPattern->InitTouchEvent(gestureHub);
    indicatorPattern->touchEvent_->callback_(touchEventInfo);
}

/**
 * @tc.name: SwiperPatternCheckMarkDirtyNodeForRenderIndicator002
 * @tc.desc: Test CheckMarkDirtyNodeForRenderIndicator
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternCheckMarkDirtyNodeForRenderIndicator002, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    RefPtr<SwiperPattern> indicatorPattern = frameNode_->GetPattern<SwiperPattern>();
    float additionalOffset = -1.0f;
    indicatorPattern->itemPosition_.emplace(std::make_pair(0, SwiperItemInfo { 0.0f, 0.0f }));
    indicatorPattern->itemPosition_.emplace(std::make_pair(3, SwiperItemInfo { 1.0f, 0.0f }));
    indicatorPattern->itemPosition_.emplace(std::make_pair(1, SwiperItemInfo { 0.0f, 2.0f }));
    indicatorPattern->itemPosition_.emplace(std::make_pair(2, SwiperItemInfo { 1.0f, 2.0f }));

    /**
     * @tc.steps: step2. test CheckMarkDirtyNodeForRenderIndicator.
     * @tc.expected: Related function runs ok.
     */
    indicatorPattern->indicatorId_ = 1;
    indicatorPattern->CheckMarkDirtyNodeForRenderIndicator(additionalOffset);
}

/**
 * @tc.name: SwiperPatternPlayIndicatorTranslateAnimation004
 * @tc.desc: PlayIndicatorTranslateAnimation
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternPlayIndicatorTranslateAnimation004, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    pattern_->stopIndicatorAnimation_ = false;
    pattern_->itemPosition_.emplace(std::make_pair(0, SwiperItemInfo { 0.0f, 0.0f }));
    float translate = 0.1f;
    pattern_->swiperController_->SetTurnPageRateCallback(nullptr);

    /**
     * @tc.steps: step2. call PlayIndicatorTranslateAnimation.
     * @tc.expected: Related function runs ok.
     */
    pattern_->stopIndicatorAnimation_ = true;
    pattern_->indicatorId_ = 1;
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            pattern_->PlayIndicatorTranslateAnimation(translate);
            if (i == 1) {
                pattern_->swiperController_->SetTurnPageRateCallback(nullptr);
                continue;
            }
            pattern_->swiperController_->SetTurnPageRateCallback([](int32_t, float) {});
        }
        pattern_->itemPosition_.clear();
        pattern_->itemPosition_.emplace(std::make_pair(0, SwiperItemInfo { 1.0f, 2.0f }));
    }
}

/**
 * @tc.name: SwiperPatternInitHoverMouseEvent001
 * @tc.desc: InitHoverMouseEvent
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternInitHoverMouseEvent001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    eventHub_->AttachHost(frameNode_);
    pattern_->hoverEvent_ = nullptr;
    auto info = MouseInfo();

    /**
     * @tc.steps: step2. call PlayIndicatorTranslateAnimation.
     * @tc.expected: Related function runs ok.
     */
    pattern_->InitHoverMouseEvent();
    pattern_->hoverEvent_->onHoverCallback_(true);
    pattern_->mouseEvent_->onMouseCallback_(info);
    layoutProperty_->UpdateShowIndicator(false);
    pattern_->InitHoverMouseEvent();
    pattern_->hoverEvent_->onHoverCallback_(true);
}

/**
 * @tc.name: SwiperLayoutAlgorithmLayoutBackward004
 * @tc.desc: LayoutBackward
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperLayoutAlgorithmLayoutBackward004, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    auto swiperLayoutAlgorithm = AceType::DynamicCast<SwiperLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    indicatorNode->layoutProperty_ = AceType::MakeRefPtr<SwiperLayoutProperty>();
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper = LayoutWrapperNode(indicatorNode, geometryNode, indicatorNode->GetLayoutProperty());
    LayoutConstraintF layoutConstraint;
    layoutConstraint.maxSize = SizeF(720.f, 1136.f);
    layoutConstraint.percentReference = SizeF(720.f, 1136.f);
    layoutConstraint.parentIdealSize.SetSize(SizeF(720.f, 1136.f));
    ASSERT_NE(layoutWrapper.layoutProperty_, nullptr);
    layoutWrapper.GetLayoutProperty()->UpdateLayoutConstraint(layoutConstraint);
    Axis axis = Axis::HORIZONTAL;
    int32_t endIndex = -1;
    float endPos = 2.0f;
    swiperLayoutAlgorithm->targetIndex_ = 1;
    swiperLayoutAlgorithm->isLoop_ = false;
    swiperLayoutAlgorithm->startMainPos_ = 0.0f;
    swiperLayoutAlgorithm->itemPosition_.emplace(std::make_pair(0, SwiperItemInfo { 0.0f, 2.0f }));
    swiperLayoutAlgorithm->totalItemCount_ = 1;
    swiperLayoutAlgorithm->nextMargin_ = 0.0f;
    swiperLayoutAlgorithm->endMainPos_ = 1.0f;
    swiperLayoutAlgorithm->spaceWidth_ = 0.0f;
    swiperLayoutAlgorithm->overScrollFeature_ = false;
    int32_t currentIndex = 0;
    EXPECT_FALSE(
        swiperLayoutAlgorithm->LayoutBackwardItem(&layoutWrapper, layoutConstraint, axis, currentIndex, 0.0f, endPos));
    EXPECT_FLOAT_EQ(endPos, 2.0f);
    swiperLayoutAlgorithm->contentMainSize_ = 1.0f;

    /**
     * @tc.steps: step2. call LayoutBackward.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            swiperLayoutAlgorithm->LayoutBackward(&layoutWrapper, layoutConstraint, axis, endIndex, endPos);
            swiperLayoutAlgorithm->startMainPos_ = 0.0f;
            if (i == 1) {
                swiperLayoutAlgorithm->canOverScroll_ = false;
                continue;
            }
            swiperLayoutAlgorithm->canOverScroll_ = true;
        }
        swiperLayoutAlgorithm->jumpIndex_ = 1;
    }
    EXPECT_FLOAT_EQ(swiperLayoutAlgorithm->startMainPos_, 0.0f);
    EXPECT_TRUE(GreatNotEqual(endPos, swiperLayoutAlgorithm->startMainPos_));
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            swiperLayoutAlgorithm->LayoutBackward(&layoutWrapper, layoutConstraint, axis, endIndex, endPos);
            swiperLayoutAlgorithm->startMainPos_ = 0.0f;
            if (i == 1) {
                swiperLayoutAlgorithm->itemPosition_.emplace(std::make_pair(1, SwiperItemInfo { 2.0f, 2.0f }));
                swiperLayoutAlgorithm->mainSizeIsDefined_ = false;
                continue;
            }
            swiperLayoutAlgorithm->itemPosition_.emplace(std::make_pair(0, SwiperItemInfo { 0.0f, 2.0f }));
            swiperLayoutAlgorithm->mainSizeIsDefined_ = true;
        }
        swiperLayoutAlgorithm->itemPosition_.emplace(std::make_pair(1, SwiperItemInfo { 2.0f, 2.0f }));
    }
    EXPECT_FLOAT_EQ(swiperLayoutAlgorithm->contentMainSize_, 1.0f);
}

/**
 * @tc.name: SwiperLayoutAlgorithmLayoutForward003
 * @tc.desc: LayoutForward
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperLayoutAlgorithmLayoutForward003, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    auto swiperLayoutAlgorithm = AceType::DynamicCast<SwiperLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper = LayoutWrapperNode(indicatorNode, geometryNode, indicatorNode->GetLayoutProperty());
    auto indicatorNode_test = FrameNode::GetOrCreateFrameNode(V2::SWIPER_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    layoutWrapper.currentChildCount_ = 2;
    layoutWrapper.childrenMap_.emplace(std::make_pair(1,
        AceType::MakeRefPtr<LayoutWrapperNode>(indicatorNode_test, geometryNode, indicatorNode->GetLayoutProperty())));
    LayoutConstraintF layoutConstraint;
    layoutConstraint.maxSize = SizeF(720.f, 1136.f);
    layoutConstraint.percentReference = SizeF(720.f, 1136.f);
    layoutConstraint.parentIdealSize.SetSize(SizeF(720.f, 1136.f));
    layoutWrapper.layoutProperty_ = AceType::MakeRefPtr<SwiperLayoutProperty>();
    ASSERT_NE(layoutWrapper.layoutProperty_, nullptr);
    layoutWrapper.GetLayoutProperty()->UpdateLayoutConstraint(layoutConstraint);
    Axis axis = Axis::HORIZONTAL;
    int32_t startIndex = 1;
    float startPos = 0.0f;
    swiperLayoutAlgorithm->targetIndex_ = 1;
    swiperLayoutAlgorithm->SetTotalItemCount(2);
    swiperLayoutAlgorithm->SetIsLoop(true);
    auto layoutProperty_ = AceType::DynamicCast<SwiperLayoutProperty>(layoutWrapper.GetLayoutProperty());
    layoutProperty_->UpdateMinSize(Dimension(1));
    layoutProperty_->UpdateDisplayCount(1);
    layoutProperty_->UpdateDisplayMode(SwiperDisplayMode::STRETCH);

    /**
     * @tc.steps: step2. call LayoutForward.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        swiperLayoutAlgorithm->LayoutForward(&layoutWrapper, layoutConstraint, axis, startIndex, startPos);
        layoutProperty_->UpdateMinSize(Dimension(0));
        layoutProperty_->UpdateDisplayCount(0);
        layoutProperty_->UpdateDisplayMode(SwiperDisplayMode::AUTO_LINEAR);
    }
}

/**
 * @tc.name: SwiperLayoutAlgorithmLayoutForward004
 * @tc.desc: LayoutForward
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperLayoutAlgorithmLayoutForward004, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    auto swiperLayoutAlgorithm = AceType::DynamicCast<SwiperLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper = LayoutWrapperNode(indicatorNode, geometryNode, indicatorNode->GetLayoutProperty());
    auto indicatorNode_test = FrameNode::GetOrCreateFrameNode(V2::SWIPER_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    layoutWrapper.currentChildCount_ = 2;
    layoutWrapper.childrenMap_.emplace(std::make_pair(1,
        AceType::MakeRefPtr<LayoutWrapperNode>(indicatorNode_test, geometryNode, indicatorNode->GetLayoutProperty())));
    LayoutConstraintF layoutConstraint;
    layoutConstraint.maxSize = SizeF(720.f, 1136.f);
    layoutConstraint.percentReference = SizeF(720.f, 1136.f);
    layoutConstraint.parentIdealSize.SetSize(SizeF(720.f, 1136.f));
    layoutWrapper.layoutProperty_ = AceType::MakeRefPtr<SwiperLayoutProperty>();
    ASSERT_NE(layoutWrapper.layoutProperty_, nullptr);
    layoutWrapper.GetLayoutProperty()->UpdateLayoutConstraint(layoutConstraint);
    Axis axis = Axis::HORIZONTAL;
    int32_t startIndex = 1;
    float startPos = 0.0f;
    swiperLayoutAlgorithm->targetIndex_ = 1;
    swiperLayoutAlgorithm->SetTotalItemCount(2);
    swiperLayoutAlgorithm->SetIsLoop(true);
    swiperLayoutAlgorithm->SetCanOverScroll(false);
    auto layoutProperty_ = AceType::DynamicCast<SwiperLayoutProperty>(layoutWrapper.GetLayoutProperty());
    layoutProperty_->UpdateMinSize(Dimension(0));
    layoutProperty_->UpdateDisplayCount(1);
    layoutProperty_->UpdatePrevMargin(Dimension(0));
    layoutProperty_->UpdateNextMargin(Dimension(0));
    swiperLayoutAlgorithm->itemPosition_.emplace(std::make_pair(0, SwiperItemInfo { 0.0f, 1.0f }));

    /**
     * @tc.steps: step2. call LayoutForward.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            swiperLayoutAlgorithm->LayoutForward(&layoutWrapper, layoutConstraint, axis, startIndex, startPos);
            if (i == 1) {
                swiperLayoutAlgorithm->mainSizeIsDefined_ = false;
                continue;
            }
            swiperLayoutAlgorithm->mainSizeIsDefined_ = true;
        }
        layoutProperty_->UpdateMinSize(Dimension(1));
    }
    EXPECT_FLOAT_EQ(swiperLayoutAlgorithm->endMainPos_, 480.0f);
}

/**
 * @tc.name: SwiperLayoutAlgorithmLayoutForward005
 * @tc.desc: LayoutForward
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperLayoutAlgorithmLayoutForward005, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    auto swiperLayoutAlgorithm = AceType::DynamicCast<SwiperLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper = LayoutWrapperNode(indicatorNode, geometryNode, indicatorNode->GetLayoutProperty());
    auto indicatorNode_test = FrameNode::GetOrCreateFrameNode(V2::SWIPER_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    layoutWrapper.currentChildCount_ = 2;
    layoutWrapper.childrenMap_.emplace(std::make_pair(1,
        AceType::MakeRefPtr<LayoutWrapperNode>(indicatorNode_test, geometryNode, indicatorNode->GetLayoutProperty())));
    LayoutConstraintF layoutConstraint;
    layoutConstraint.maxSize = SizeF(720.f, 1136.f);
    layoutConstraint.percentReference = SizeF(720.f, 1136.f);
    layoutConstraint.parentIdealSize.SetSize(SizeF(720.f, 1136.f));
    layoutWrapper.layoutProperty_ = AceType::MakeRefPtr<SwiperLayoutProperty>();
    ASSERT_NE(layoutWrapper.layoutProperty_, nullptr);
    layoutWrapper.GetLayoutProperty()->UpdateLayoutConstraint(layoutConstraint);
    Axis axis = Axis::HORIZONTAL;
    int32_t startIndex = 1;
    float startPos = 0.0f;
    swiperLayoutAlgorithm->targetIndex_ = 1;
    swiperLayoutAlgorithm->SetTotalItemCount(2);
    swiperLayoutAlgorithm->SetIsLoop(true);
    auto layoutProperty_ = AceType::DynamicCast<SwiperLayoutProperty>(layoutWrapper.GetLayoutProperty());
    layoutProperty_->UpdateMinSize(Dimension(1));
    layoutProperty_->UpdateDisplayCount(1);
    layoutProperty_->UpdateDisplayMode(SwiperDisplayMode::STRETCH);
    float currentEndPos = startPos;
    float currentStartPos = 0.0f;
    auto currentIndex = startIndex - 1;
    auto result = swiperLayoutAlgorithm->LayoutForwardItem(
        &layoutWrapper, layoutConstraint, axis, currentIndex, currentStartPos, currentEndPos);
    EXPECT_TRUE(result);

    /**
     * @tc.steps: step2. call LayoutForward.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        swiperLayoutAlgorithm->LayoutForward(&layoutWrapper, layoutConstraint, axis, startIndex, startPos);
        startIndex = 2;
    }
}

/**
 * @tc.name: SwiperLayoutAlgorithmLayoutForward006
 * @tc.desc: LayoutForward
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperLayoutAlgorithmLayoutForward006, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    auto swiperLayoutAlgorithm = AceType::DynamicCast<SwiperLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper = LayoutWrapperNode(indicatorNode, geometryNode, indicatorNode->GetLayoutProperty());
    auto indicatorNode_test = FrameNode::GetOrCreateFrameNode(V2::SWIPER_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    layoutWrapper.currentChildCount_ = 2;
    layoutWrapper.childrenMap_.emplace(std::make_pair(1,
        AceType::MakeRefPtr<LayoutWrapperNode>(indicatorNode_test, geometryNode, indicatorNode->GetLayoutProperty())));
    LayoutConstraintF layoutConstraint;
    layoutConstraint.maxSize = SizeF(720.f, 1136.f);
    layoutConstraint.percentReference = SizeF(720.f, 1136.f);
    layoutConstraint.parentIdealSize.SetSize(SizeF(720.f, 1136.f));
    layoutWrapper.layoutProperty_ = AceType::MakeRefPtr<SwiperLayoutProperty>();
    ASSERT_NE(layoutWrapper.layoutProperty_, nullptr);
    layoutWrapper.GetLayoutProperty()->UpdateLayoutConstraint(layoutConstraint);
    Axis axis = Axis::HORIZONTAL;
    int32_t startIndex = 1;
    float startPos = 0.0f;
    swiperLayoutAlgorithm->targetIndex_ = 1;
    swiperLayoutAlgorithm->SetTotalItemCount(1);
    swiperLayoutAlgorithm->SetIsLoop(true);
    auto layoutProperty_ = AceType::DynamicCast<SwiperLayoutProperty>(layoutWrapper.GetLayoutProperty());
    layoutProperty_->UpdateMinSize(Dimension(1));
    layoutProperty_->UpdateDisplayCount(1);
    layoutProperty_->UpdateDisplayMode(SwiperDisplayMode::STRETCH);
    swiperLayoutAlgorithm->jumpIndex_ = 1;
    swiperLayoutAlgorithm->itemPosition_.emplace(std::make_pair(1, SwiperItemInfo { 0.0f, 1.0f }));
    swiperLayoutAlgorithm->endMainPos_ = 1.0f;

    /**
     * @tc.steps: step2. call LayoutForward.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            swiperLayoutAlgorithm->LayoutForward(&layoutWrapper, layoutConstraint, axis, startIndex, startPos);
            swiperLayoutAlgorithm->endMainPos_ = 1.0f;
            if (i == 1) {
                swiperLayoutAlgorithm->canOverScroll_ = false;
                continue;
            }
            swiperLayoutAlgorithm->canOverScroll_ = true;
        }
        swiperLayoutAlgorithm->jumpIndex_.reset();
    }
}

/**
 * @tc.name: SwiperLayoutAlgorithmLayoutForward007
 * @tc.desc: LayoutForward
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperLayoutAlgorithmLayoutForward007, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    auto swiperLayoutAlgorithm = AceType::DynamicCast<SwiperLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper = LayoutWrapperNode(indicatorNode, geometryNode, indicatorNode->GetLayoutProperty());
    auto indicatorNode_test = FrameNode::GetOrCreateFrameNode(V2::SWIPER_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    layoutWrapper.currentChildCount_ = 2;
    layoutWrapper.childrenMap_.emplace(std::make_pair(1,
        AceType::MakeRefPtr<LayoutWrapperNode>(indicatorNode_test, geometryNode, indicatorNode->GetLayoutProperty())));
    LayoutConstraintF layoutConstraint;
    layoutConstraint.maxSize = SizeF(720.f, 1136.f);
    layoutConstraint.percentReference = SizeF(720.f, 1136.f);
    layoutConstraint.parentIdealSize.SetSize(SizeF(720.f, 1136.f));
    layoutWrapper.layoutProperty_ = AceType::MakeRefPtr<SwiperLayoutProperty>();
    ASSERT_NE(layoutWrapper.layoutProperty_, nullptr);
    layoutWrapper.GetLayoutProperty()->UpdateLayoutConstraint(layoutConstraint);
    Axis axis = Axis::HORIZONTAL;
    int32_t startIndex = 1;
    float startPos = 0.0f;
    swiperLayoutAlgorithm->targetIndex_ = 1;
    swiperLayoutAlgorithm->SetTotalItemCount(1);
    swiperLayoutAlgorithm->SetIsLoop(true);
    auto layoutProperty_ = AceType::DynamicCast<SwiperLayoutProperty>(layoutWrapper.GetLayoutProperty());
    layoutProperty_->UpdateMinSize(Dimension(1));
    layoutProperty_->UpdateDisplayCount(1);
    layoutProperty_->UpdateDisplayMode(SwiperDisplayMode::STRETCH);
    swiperLayoutAlgorithm->jumpIndex_ = 1;
    swiperLayoutAlgorithm->itemPosition_.emplace(std::make_pair(1, SwiperItemInfo { 0.0f, 0.0f }));
    swiperLayoutAlgorithm->prevMargin_ = 0.0f;
    swiperLayoutAlgorithm->contentMainSize_ = 0.0f;

    /**
     * @tc.steps: step2. call LayoutForward.
     * @tc.expected: Related function runs ok.
     */
    swiperLayoutAlgorithm->LayoutForward(&layoutWrapper, layoutConstraint, axis, startIndex, startPos);
    EXPECT_FALSE(swiperLayoutAlgorithm->itemPosition_.empty());
}

/**
 * @tc.name: SwiperPatternOnTranslateFinish002
 * @tc.desc: OnTranslateFinish
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternOnTranslateFinish002, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {
        model.SetDisplayArrow(true); // show arrow
        model.SetHoverShow(false);
        model.SetArrowStyle(ARROW_PARAMETERS);
    });
    auto indicatorNode = GetChildFrameNode(frameNode_, 4);
    int32_t nextIndex = 1;
    bool restartAutoPlay = true;
    bool forceStop = true;
    layoutProperty_->UpdateLoop(true);
    layoutProperty_->ResetDisplayCount();
    layoutProperty_->ResetMinSize();
    layoutProperty_->UpdateDisplayMode(SwiperDisplayMode::AUTO_LINEAR);
    pattern_->currentIndex_ = 1;
    pattern_->leftButtonId_.reset();
    pattern_->rightButtonId_.reset();
    pattern_->GetLayoutProperty<SwiperLayoutProperty>()->UpdateShowIndicator(false);
    pattern_->isVisible_ = true;
    pattern_->GetPaintProperty<SwiperPaintProperty>()->UpdateAutoPlay(true);
    pattern_->isIndicatorLongPress_ = false;
    EXPECT_EQ(frameNode_->GetChildren().size(), 7);

    /**
     * @tc.steps: step2. call OnTranslateFinish.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            pattern_->OnTranslateFinish(nextIndex, restartAutoPlay, pattern_->isFinishAnimation_, forceStop);
            if (i == 1) {
                pattern_->isUserFinish_ = true;
                continue;
            }
            pattern_->isUserFinish_ = false;
        }
        pattern_->isVisible_ = false;
    }
}

/**
 * @tc.name: SwiperIndicatorPatternTestNg0018
 * @tc.desc: HandleTouchClick
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperIndicatorPatternTestNg0018, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    auto indicatorNode = GetChildFrameNode(frameNode_, 4);
    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    auto paintProperty_ = pattern_->GetPaintProperty<SwiperPaintProperty>();
    CHECK_NULL_VOID(paintProperty_);
    auto info = GestureEvent();
    layoutProperty_->UpdateDirection(Axis::NONE);
    info.localLocation_.SetX(5.0f);
    indicatorPattern->HandleTouchClick(info);
    layoutProperty_->UpdateDirection(Axis::NONE);
    info.localLocation_.SetX(500.0f);
    indicatorPattern->HandleTouchClick(info);
}

/**
 * @tc.name: SwiperIndicatorPatternTestNg0019
 * @tc.desc: UpdateTextContentSub
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperIndicatorPatternTestNg0019, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    auto indicatorNode = GetChildFrameNode(frameNode_, 4);
    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    auto layoutProperty = indicatorNode->GetLayoutProperty<SwiperIndicatorLayoutProperty>();
    auto paintProperty_ = pattern_->GetPaintProperty<SwiperPaintProperty>();
    CHECK_NULL_VOID(paintProperty_);

    auto firstTextNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    auto lastTextNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    pattern_->currentFirstIndex_ = -2;
    layoutProperty_->UpdateIndex(1);
    indicatorPattern->UpdateTextContentSub(layoutProperty, firstTextNode, lastTextNode);
}

/**
 * @tc.name: SwiperIndicatorPatternTestNg0020
 * @tc.desc: CheckIsTouchBottom
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperIndicatorPatternTestNg0020, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    auto indicatorNode = GetChildFrameNode(frameNode_, 4);
    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    GestureEvent info;
    info.mainDelta_ = 1.0f;
    TouchLocationInfo touchLocationInfo("down", 0);
    touchLocationInfo.SetTouchType(TouchType::DOWN);
    std::list<TouchLocationInfo> infoSwiper;
    infoSwiper.emplace_back(touchLocationInfo);
    TouchEventInfo touchEventInfo("down");
    touchEventInfo.touches_ = infoSwiper;
    pattern_->currentIndex_ = 0;
    EXPECT_TRUE(indicatorPattern->CheckIsTouchBottom(touchEventInfo.GetTouches().front()));
    layoutProperty_->UpdateLoop(false);
    ASSERT_FALSE(layoutProperty_->GetLoop().value_or(true));
    pattern_->leftButtonId_ = 1;
    pattern_->rightButtonId_ = 1;
    pattern_->GetLayoutProperty<SwiperLayoutProperty>()->UpdateShowIndicator(true);
    layoutProperty_->UpdateDirection(Axis::HORIZONTAL);
    touchEventInfo.touches_.front().localLocation_.SetX(2.0f);
    indicatorPattern->dragStartPoint_.SetX(1.0f);
    EXPECT_FALSE(indicatorPattern->CheckIsTouchBottom(touchEventInfo.GetTouches().front()));
}

/**
 * @tc.name: SwiperIndicatorPatternTestNg0021
 * @tc.desc: HandleMouseEvent
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperIndicatorPatternTestNg0021, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {
        model.SetDirection(Axis::VERTICAL);
    });
    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    auto info = MouseInfo();
    info.SetSourceDevice(SourceType::MOUSE);
    info.action_ = MouseAction::PRESS;
    indicatorPattern->isClicked_ = true;
    indicatorPattern->hoverPoint_.SetX(5.0);
    indicatorPattern->hoverPoint_.SetY(15.0);
    info.localLocation_.SetX(5.0);
    info.localLocation_.SetY(15.0);
    indicatorPattern->HandleMouseEvent(info);
}

/**
 * @tc.name: SwiperPatternOnModifyDone002
 * @tc.desc: Test OnModifyDone
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternOnModifyDone002, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {
        model.SetDirection(Axis::VERTICAL);
    });
    RefPtr<SwiperPattern> indicatorPattern = frameNode_->GetPattern<SwiperPattern>();
    indicatorPattern->OnModifyDone();
    indicatorPattern->swiperController_->removeSwiperEventCallback_();
    indicatorPattern->swiperController_->addSwiperEventCallback_();
    pattern_->OnAfterModifyDone();
    EXPECT_NE(indicatorPattern, nullptr);
}

/**
 * @tc.name: SwiperPaintMethodClipPadding001
 * @tc.desc: ClipPadding
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPaintMethodClipPadding001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    SwiperPaintMethod swiperPaintMethod1(Axis::VERTICAL, 0.0f);
    auto indicatorNode = GetChildFrameNode(frameNode_, 4);
    RefPtr<DotIndicatorModifier> modifier = AceType::MakeRefPtr<DotIndicatorModifier>();
    RefPtr<DotIndicatorPaintMethod> paintMethod = AceType::MakeRefPtr<DotIndicatorPaintMethod>(modifier);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto paintProperty = AceType::MakeRefPtr<DotIndicatorPaintProperty>();
    paintProperty->Clone();
    paintProperty->Reset();
    paintProperty->UpdateColor(Color::RED);
    auto renderContext = frameNode_->GetRenderContext();
    PaintWrapper paintWrapper(renderContext, geometryNode, paintProperty);
    Testing::MockCanvas canvas;
    EXPECT_CALL(canvas, ClipRect(_, _, _)).Times(AnyNumber());

    /**
     * @tc.steps: step2. call ClipPadding.
     * @tc.expected: Related function is called.
     */
    swiperPaintMethod1.needClipPadding_ = true;
    swiperPaintMethod1.ClipPadding(&paintWrapper, canvas);
    EXPECT_TRUE(swiperPaintMethod1.needClipPadding_);
    swiperPaintMethod1.needClipPadding_ = false;
    swiperPaintMethod1.ClipPadding(&paintWrapper, canvas);
    EXPECT_FALSE(swiperPaintMethod1.needClipPadding_);
}

/**
 * @tc.name: SwiperPaintMethodPaintFade001
 * @tc.desc: PaintFade
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPaintMethodPaintFade001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    SwiperPaintMethod swiperPaintMethod1(Axis::VERTICAL, 0.0f);
    auto indicatorNode = GetChildFrameNode(frameNode_, 4);
    RefPtr<DotIndicatorModifier> modifier = AceType::MakeRefPtr<DotIndicatorModifier>();
    RefPtr<DotIndicatorPaintMethod> paintMethod = AceType::MakeRefPtr<DotIndicatorPaintMethod>(modifier);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto paintProperty = AceType::MakeRefPtr<DotIndicatorPaintProperty>();
    paintProperty->Clone();
    paintProperty->Reset();
    paintProperty->UpdateColor(Color::RED);
    auto renderContext = frameNode_->GetRenderContext();
    PaintWrapper paintWrapper(renderContext, geometryNode, paintProperty);
    Testing::MockCanvas canvas;
    EXPECT_CALL(canvas, DrawCircle(_, _)).Times(AnyNumber());
    EXPECT_CALL(canvas, ClipRect(_, _, _)).Times(AnyNumber());

    /**
     * @tc.steps: step2. call PaintFade whith setting needPaintFade_ and renderContext.
     * @tc.expected: Related function is called.
     */
    swiperPaintMethod1.needPaintFade_ = true;
    swiperPaintMethod1.PaintFade(canvas, &paintWrapper);
    EXPECT_TRUE(swiperPaintMethod1.needPaintFade_);
    swiperPaintMethod1.needPaintFade_ = false;
    swiperPaintMethod1.PaintFade(canvas, &paintWrapper);
    EXPECT_FALSE(swiperPaintMethod1.needPaintFade_);
    paintWrapper.renderContext_ = renderContext;
    swiperPaintMethod1.needClipPadding_ = true;
    renderContext->UpdateClipEdge(false);
    swiperPaintMethod1.ClipPadding(&paintWrapper, canvas);
    paintWrapper.renderContext_ = nullptr;
    swiperPaintMethod1.ClipPadding(&paintWrapper, canvas);
    EXPECT_TRUE(swiperPaintMethod1.needClipPadding_);
}

/**
 * @tc.name: SwiperPaintMethodPaintFade002
 * @tc.desc: PaintFade
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPaintMethodPaintFade002, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    SwiperPaintMethod swiperPaintMethod1(Axis::VERTICAL, 0.0f);
    auto indicatorNode = GetChildFrameNode(frameNode_, 4);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto paintProperty = AceType::MakeRefPtr<PaintProperty>();
    auto renderContext = frameNode_->GetRenderContext();
    PaintWrapper paintWrapper(renderContext, geometryNode, paintProperty);
    Testing::MockCanvas canvas;
    EXPECT_CALL(canvas, AttachBrush(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachBrush()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DrawCircle(_, _)).Times(AnyNumber());
    paintWrapper.paintProperty_ = AceType::MakeRefPtr<SwiperPaintProperty>();

    /**
     * @tc.steps: step2. call PaintFade whith setting (GreatNotEqual(mainDelta_, 0.0)) .
     * @tc.expected: Related function is called.
     */
    swiperPaintMethod1.needPaintFade_ = true;
    swiperPaintMethod1.mainDelta_ = 1.0f;
    swiperPaintMethod1.PaintFade(canvas, &paintWrapper);
    EXPECT_EQ(swiperPaintMethod1.mainDelta_, 1.0f);
    swiperPaintMethod1.axis_ = Axis::HORIZONTAL;
    swiperPaintMethod1.PaintFade(canvas, &paintWrapper);
    EXPECT_EQ(swiperPaintMethod1.axis_, Axis::HORIZONTAL);
    swiperPaintMethod1.mainDelta_ = 0.002f;
    swiperPaintMethod1.PaintFade(canvas, &paintWrapper);
    EXPECT_EQ(swiperPaintMethod1.mainDelta_, 0.002f);
}

/**
 * @tc.name: SwiperPatternAlgorithmMeasure001
 * @tc.desc: Measure
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternAlgorithmMeasure001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {
        model.SetDisplayArrow(true); // show arrow
        model.SetHoverShow(false);
        model.SetArrowStyle(ARROW_PARAMETERS);
    });
    layoutProperty_->UpdateBackgroundSize(3.0_vp);
    FlushLayoutTask(frameNode_);

    /**
     * @tc.steps: step4. call Measure.
     * @tc.expected: Return button measure, SizeF(3.0f, 3.0f).
     */
    auto swiperPatternAlgorithm = AceType::DynamicCast<SwiperLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    swiperPatternAlgorithm->mainSizeIsMeasured_ = true;
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(swiperPatternAlgorithm->mainSizeIsMeasured_);

    swiperPatternAlgorithm->mainSizeIsMeasured_ = true;
    frameNode_->isConstraintNotChanged_ = true;
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(frameNode_->isConstraintNotChanged_);
}

/**
 * @tc.name: SwiperPaintMethodGetOverlayDrawFunction001
 * @tc.desc: GetOverlayDrawFunction
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPaintMethodGetOverlayDrawFunction001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    SwiperPaintMethod swiperPaintMethod1(Axis::VERTICAL, 0.0f);
    auto indicatorNode = GetChildFrameNode(frameNode_, 4);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto paintProperty = AceType::MakeRefPtr<PaintProperty>();
    auto renderContext = frameNode_->GetRenderContext();
    PaintWrapper paintWrapper(renderContext, geometryNode, paintProperty);
    Testing::MockCanvas canvas;

    /**
     * @tc.steps: step2. call PaintFade whith setting (GreatNotEqual(mainDelta_, 0.0)) .
     * @tc.expected: Related function is called.
     */
    auto canvasDrawFunction = swiperPaintMethod1.GetOverlayDrawFunction(&paintWrapper);
    canvasDrawFunction(canvas);
    EXPECT_TRUE(canvasDrawFunction);
}

/**
 * @tc.name: SwiperPaintMethodPaintFade003
 * @tc.desc: PaintFade
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPaintMethodPaintFade003, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    SwiperPaintMethod swiperPaintMethod1(Axis::VERTICAL, 0.0f);
    auto indicatorNode = GetChildFrameNode(frameNode_, 4);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto paintProperty = AceType::MakeRefPtr<PaintProperty>();
    auto renderContext = frameNode_->GetRenderContext();
    PaintWrapper paintWrapper(renderContext, geometryNode, paintProperty);
    Testing::MockCanvas canvas;
    EXPECT_CALL(canvas, AttachBrush(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachBrush()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DrawCircle(_, _)).Times(AnyNumber());
    paintWrapper.paintProperty_ = AceType::MakeRefPtr<SwiperPaintProperty>();

    /**
     * @tc.steps: step2. call PaintFade whith setting (GreatNotEqual(mainDelta_, 0.0)) .
     * @tc.expected: Related function is called.
     */
    swiperPaintMethod1.needPaintFade_ = true;
    swiperPaintMethod1.mainDelta_ = -1.0f;
    EXPECT_FALSE(NearZero(swiperPaintMethod1.mainDelta_));
    EXPECT_FALSE(GreatNotEqual(swiperPaintMethod1.mainDelta_, 0.0));
    swiperPaintMethod1.PaintFade(canvas, &paintWrapper);
    EXPECT_EQ(swiperPaintMethod1.mainDelta_, -1.0f);
    swiperPaintMethod1.axis_ = Axis::HORIZONTAL;
    swiperPaintMethod1.PaintFade(canvas, &paintWrapper);
    EXPECT_EQ(swiperPaintMethod1.axis_, Axis::HORIZONTAL);
}

/**
 * @tc.name: SwiperPaintMethodPaintFade004
 * @tc.desc: PaintFade
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPaintMethodPaintFade004, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    SwiperPaintMethod swiperPaintMethod1(Axis::VERTICAL, 0.0f);
    auto indicatorNode = GetChildFrameNode(frameNode_, 4);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto paintProperty = AceType::MakeRefPtr<PaintProperty>();
    auto renderContext = frameNode_->GetRenderContext();
    PaintWrapper paintWrapper(renderContext, geometryNode, paintProperty);
    Testing::MockCanvas canvas;
    EXPECT_CALL(canvas, AttachBrush(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachBrush()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DrawCircle(_, _)).Times(AnyNumber());
    paintWrapper.paintProperty_ = AceType::MakeRefPtr<SwiperPaintProperty>();
    ASSERT_NE(paintWrapper.paintProperty_, nullptr);
    auto frameSize = paintWrapper.GetGeometryNode()->GetFrameSize();
    /**
     * @tc.steps: step2. call PaintFade whith setting mainDelta_ and width.
     * @tc.expected: Related function is called.
     */
    swiperPaintMethod1.needPaintFade_ = true;
    swiperPaintMethod1.mainDelta_ = 3000.0f;
    float testnumber = 2000.0f;
    frameSize.SetWidth(testnumber);
    EXPECT_EQ(frameSize.width_, testnumber);
    EXPECT_FALSE(NearZero(swiperPaintMethod1.mainDelta_));
    EXPECT_TRUE(GreatNotEqual(swiperPaintMethod1.mainDelta_, 0.0));
    EXPECT_EQ(swiperPaintMethod1.axis_, Axis::VERTICAL);
    swiperPaintMethod1.PaintFade(canvas, &paintWrapper);
    EXPECT_EQ(swiperPaintMethod1.mainDelta_, 3000.0f);
    swiperPaintMethod1.axis_ = Axis::HORIZONTAL;
    frameSize.SetHeight(testnumber);
    swiperPaintMethod1.PaintFade(canvas, &paintWrapper);
    EXPECT_EQ(swiperPaintMethod1.mainDelta_, 3000.0f);

    /**
     * @tc.steps: step3. call PaintFade whith setting mainDelta_ and width in different confidions.
     * @tc.expected: Related function is called.
     */
    swiperPaintMethod1.mainDelta_ = -3000.0f;
    EXPECT_FALSE(GreatNotEqual(swiperPaintMethod1.mainDelta_, 0.0));
    swiperPaintMethod1.axis_ = Axis::VERTICAL;
    EXPECT_EQ(swiperPaintMethod1.axis_, Axis::VERTICAL);
    frameSize.SetWidth(testnumber);
    swiperPaintMethod1.PaintFade(canvas, &paintWrapper);
    EXPECT_EQ(swiperPaintMethod1.mainDelta_, -3000.0f);
    swiperPaintMethod1.axis_ = Axis::HORIZONTAL;
    EXPECT_EQ(swiperPaintMethod1.axis_, Axis::HORIZONTAL);
    frameSize.SetHeight(testnumber);
    swiperPaintMethod1.PaintFade(canvas, &paintWrapper);
    EXPECT_EQ(swiperPaintMethod1.mainDelta_, -3000.0f);
}

/**
 * @tc.name: SwiperPatternRegisterVisibleAreaChange002
 * @tc.desc: RegisterVisibleAreaChange
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternRegisterVisibleAreaChange002, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    auto pipeline = frameNode_->GetContext();
    auto paintProperty_ = pattern_->GetPaintProperty<SwiperPaintProperty>();

    /**
     * @tc.steps: step2. call RegisterVisibleAreaChange.
     * @tc.expected: Related function runs ok.
     */
    pattern_->hasVisibleChangeRegistered_ = false;
    paintProperty_->UpdateAutoPlay(true);
    pattern_->RegisterVisibleAreaChange();
    EXPECT_TRUE(pattern_->hasVisibleChangeRegistered_);
    pattern_->isWindowShow_ = false;
    pattern_->hasVisibleChangeRegistered_ = false;
    paintProperty_->UpdateAutoPlay(true);
    pattern_->RegisterVisibleAreaChange();
    EXPECT_TRUE(pattern_->hasVisibleChangeRegistered_);
}

/**
 * @tc.name: SwiperPatternInitSurfaceChangedCallback001
 * @tc.desc: InitSurfaceChangedCallback
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternInitSurfaceChangedCallback001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    pattern_->leftButtonId_.reset();
    pattern_->rightButtonId_ = 1;
    pattern_->GetLayoutProperty<SwiperLayoutProperty>()->UpdateShowIndicator(true);
    pattern_->GetLayoutProperty<SwiperLayoutProperty>()->UpdateIndex(-1);
    auto leftArrowNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_LEFT_ARROW_ETS_TAG, pattern_->GetLeftButtonId(),
        []() { return AceType::MakeRefPtr<SwiperArrowPattern>(); });
    auto rightArrowNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_RIGHT_ARROW_ETS_TAG, pattern_->GetRightButtonId(),
        []() { return AceType::MakeRefPtr<SwiperArrowPattern>(); });

    /**
     * @tc.steps: step2. call InitSurfaceChangedCallback and then callback.
     * @tc.expected: Related function is called.
     */
    auto pipeline = frameNode_->GetContext();
    pattern_->surfaceChangedCallbackId_.emplace(1);
    pattern_->InitSurfaceChangedCallback();
    pipeline->callbackId_ = 0;
    pattern_->surfaceChangedCallbackId_.reset();
    EXPECT_FALSE(pattern_->HasSurfaceChangedCallback());
    pipeline->surfaceChangedCallbackMap_.clear();
    pattern_->InitSurfaceChangedCallback();
    auto callbackmapnumber = pipeline->callbackId_;
    EXPECT_EQ(callbackmapnumber, 1);
    auto testFunction = pipeline->surfaceChangedCallbackMap_[1];
    testFunction(1, 1, 1, 1, WindowSizeChangeReason::CUSTOM_ANIMATION);
    auto callbacknumber = pattern_->surfaceChangedCallbackId_;
    EXPECT_EQ(callbacknumber, 1);

    /**
     * @tc.steps: step3. call InitSurfaceChangedCallback and then callback in different conditions.
     * @tc.expected: Related function is called.
     */
    pipeline->callbackId_ = 0;
    pattern_->surfaceChangedCallbackId_.reset();
    EXPECT_FALSE(pattern_->HasSurfaceChangedCallback());
    pipeline->surfaceChangedCallbackMap_.clear();
    pattern_->InitSurfaceChangedCallback();
    auto callbackmapnumber2 = pipeline->callbackId_;
    EXPECT_EQ(callbackmapnumber2, 1);
    auto testFunction2 = pipeline->surfaceChangedCallbackMap_[1];
    testFunction2(1, 1, 1, 1, WindowSizeChangeReason::UNDEFINED);
    auto callbacknumber2 = pattern_->surfaceChangedCallbackId_;
    EXPECT_EQ(callbacknumber2, 1);

    auto childswiperNode1 = FrameNode::CreateFrameNode("childswiper", 1, AceType::MakeRefPtr<SwiperPattern>(), false);
    childswiperNode1->MountToParent(frameNode_);
    auto childswiperNode2 =
        FrameNode::CreateFrameNode(V2::JS_LAZY_FOR_EACH_ETS_TAG, 2, AceType::MakeRefPtr<SwiperPattern>(), false);
    childswiperNode2->MountToParent(frameNode_);
    pipeline->callbackId_ = 0;
    pattern_->surfaceChangedCallbackId_.reset();
    EXPECT_FALSE(pattern_->HasSurfaceChangedCallback());
    pipeline->surfaceChangedCallbackMap_.clear();
    pattern_->InitSurfaceChangedCallback();
    auto callbackmapnumber3 = pipeline->callbackId_;
    EXPECT_EQ(callbackmapnumber3, 1);
    auto testFunction3 = pipeline->surfaceChangedCallbackMap_[1];
    testFunction3(1, 1, 1, 1, WindowSizeChangeReason::CUSTOM_ANIMATION);
    auto callbacknumber3 = pattern_->surfaceChangedCallbackId_;
    EXPECT_EQ(callbacknumber3, 1);
}

/**
 * @tc.name: SwiperPatternMarkDirtyNodeSelf001
 * @tc.desc: MarkDirtyNodeSelf
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternMarkDirtyNodeSelf001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    pattern_->leftButtonId_.reset();
    pattern_->rightButtonId_ = 1;
    pattern_->GetLayoutProperty<SwiperLayoutProperty>()->UpdateShowIndicator(true);
    pattern_->GetLayoutProperty<SwiperLayoutProperty>()->UpdateIndex(-1);

    /**
     * @tc.steps: step2. call MarkDirtyNodeSelf.
     * @tc.expected: Related function is called.
     */
    pattern_->crossMatchChild_ = true;
    pattern_->MarkDirtyNodeSelf();
    EXPECT_TRUE(pattern_->crossMatchChild_);
    pattern_->crossMatchChild_ = false;
    pattern_->MarkDirtyNodeSelf();
    EXPECT_FALSE(pattern_->crossMatchChild_);
}

/**
 * @tc.name: SwiperPatternOnWindowHide001
 * @tc.desc: MarkDirtyNodeSelf
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternOnWindowHide001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    pattern_->leftButtonId_.reset();
    pattern_->rightButtonId_ = 1;
    pattern_->GetLayoutProperty<SwiperLayoutProperty>()->UpdateShowIndicator(true);
    pattern_->GetLayoutProperty<SwiperLayoutProperty>()->UpdateIndex(-1);

    /**
     * @tc.steps: step2. call MarkDirtyNodeSelf.
     * @tc.expected: Related function is called.
     */
    pattern_->isDragging_ = true;
    pattern_->OnWindowHide();
    EXPECT_FALSE(pattern_->isDragging_);
    pattern_->isDragging_ = false;
    pattern_->OnWindowHide();
    EXPECT_FALSE(pattern_->isDragging_);
}

/**
 * @tc.name: SwiperLayoutAlgorithmLayout006
 * @tc.desc: Test SwiperLayoutAlgorithm Layout with arrow
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperLayoutAlgorithmLayout006, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {
        model.SetDisplayArrow(true); // show arrow
        model.SetHoverShow(false);
        model.SetArrowStyle(ARROW_PARAMETERS);
    });
    auto indicatorNode = GetChildFrameNode(frameNode_, 4);
    auto indicatorGeometryNode = indicatorNode->GetGeometryNode();
    indicatorGeometryNode->SetFrameOffset(OffsetF(250.0f, 190.0f));
    indicatorGeometryNode->SetFrameSize(SizeF(144.0f, 48.0f));

    /**
     * @tc.cases: case3. Axis is HORIZONTAL, arrow is in the switch, not show indicator.
     */
    layoutProperty_->UpdateShowIndicator(false);
    pattern_->leftButtonId_.reset();
    pattern_->rightButtonId_.reset();
    FlushLayoutTask(frameNode_);

    pattern_->leftButtonId_.emplace(1);
    pattern_->rightButtonId_.emplace(1);
    FlushLayoutTask(frameNode_);
}

/**
 * @tc.name: SwiperPatternOnDirtyLayoutWrapperSwap003
 * @tc.desc: OnDirtyLayoutWrapperSwap
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternOnDirtyLayoutWrapperSwap003, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {
        model.SetDisplayArrow(true); // show arrow
        model.SetHoverShow(false);
        model.SetArrowStyle(ARROW_PARAMETERS);
    });
    auto indicatorNode = GetChildFrameNode(frameNode_, 4);
    auto firstChild = AccessibilityManager::DynamicCast<FrameNode>(indicatorNode);
    RefPtr<GeometryNode> firstGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    firstGeometryNode->Reset();
    firstGeometryNode->SetFrameSize(SizeF(20.0, 20.0));
    auto firstLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(firstChild, firstGeometryNode, firstChild->GetLayoutProperty());
    auto dirty = AceType::MakeRefPtr<LayoutWrapperNode>(firstChild, firstGeometryNode, firstChild->GetLayoutProperty());
    dirty->AppendChild(firstLayoutWrapper);
    struct DirtySwapConfig config;
    pattern_->isInit_ = true;
    config.skipMeasure = true;
    config.skipLayout = false;
    auto paintProperty_ = pattern_->GetPaintProperty<SwiperPaintProperty>();

    /**
     * @tc.steps: step2. call OnDirtyLayoutWrapperSwap.
     * @tc.expected: Related function runs ok.
     */
    paintProperty_->GetAutoPlay().emplace(false);
    pattern_->OnDirtyLayoutWrapperSwap(dirty, config);
    config.skipMeasure = false;
    paintProperty_->GetAutoPlay().emplace(false);
    pattern_->OnDirtyLayoutWrapperSwap(dirty, config);
    paintProperty_->GetAutoPlay().emplace(true);
    pattern_->OnDirtyLayoutWrapperSwap(dirty, config);
    paintProperty_->GetAutoPlay().emplace(true);
    config.skipMeasure = false;
    config.skipLayout = false;
    pattern_->OnDirtyLayoutWrapperSwap(dirty, config);
}

/**
 * @tc.name: SwiperLayoutAlgorithmLayoutForwardItem002
 * @tc.desc: LayoutForwardItem
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperLayoutAlgorithmLayoutForwardItem002, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    auto indicatorNode =
        FrameNode::GetOrCreateFrameNode("test", 1, []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper = LayoutWrapperNode(frameNode_, geometryNode, frameNode_->GetLayoutProperty());
    LayoutConstraintF layoutConstraint;
    layoutConstraint.maxSize = SizeF(720.f, 1136.f);
    layoutConstraint.percentReference = SizeF(720.f, 1136.f);
    layoutConstraint.parentIdealSize.SetSize(SizeF(720.f, 1136.f));
    ASSERT_NE(layoutWrapper.layoutProperty_, nullptr);
    layoutWrapper.GetLayoutProperty()->UpdateLayoutConstraint(layoutConstraint);
    Axis axis = Axis::HORIZONTAL;
    int32_t currentIndex = 0;
    float endPos = 0.1f;
    float startPos = 0.2f;
    auto swiperLayoutAlgorithm = AceType::DynamicCast<SwiperLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    swiperLayoutAlgorithm->isLoop_ = true;
    auto firstLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(indicatorNode, geometryNode, indicatorNode->GetLayoutProperty());
    layoutWrapper.currentChildCount_ = 1;
    layoutWrapper.AppendChild(firstLayoutWrapper);
    swiperLayoutAlgorithm->totalItemCount_ = 2;
    indicatorNode->layoutProperty_ = AceType::MakeRefPtr<SwiperLayoutProperty>();
    AceType::DynamicCast<SwiperLayoutProperty>(layoutWrapper.GetLayoutProperty())->ResetDisplayCount();
    AceType::DynamicCast<SwiperLayoutProperty>(layoutWrapper.GetLayoutProperty())
        ->UpdateDisplayMode(SwiperDisplayMode::AUTO_LINEAR);

    /**
     * @tc.steps: step2. call LayoutForwardItem in different layoutWrapper and make the return value false.
     * @tc.expected: Related function runs ok.
     */
    currentIndex = 0;
    auto swiperNode2 = FrameNode::GetOrCreateFrameNode(
        V2::SWIPER_RIGHT_ARROW_ETS_TAG, 2, []() { return AceType::MakeRefPtr<SwiperPattern>(); });
    auto layoutWrapper2 = LayoutWrapperNode(swiperNode2, geometryNode, swiperNode2->GetLayoutProperty());
    swiperLayoutAlgorithm->LayoutForwardItem(&layoutWrapper2, layoutConstraint, axis, currentIndex, endPos, startPos);
    auto result2 = swiperLayoutAlgorithm->LayoutForwardItem(
        &layoutWrapper2, layoutConstraint, axis, currentIndex, endPos, startPos);
    EXPECT_FALSE(result2);
    currentIndex = 0;
    auto swiperNode3 = FrameNode::GetOrCreateFrameNode(
        V2::SWIPER_LEFT_ARROW_ETS_TAG, 3, []() { return AceType::MakeRefPtr<SwiperPattern>(); });
    auto layoutWrapper3 = LayoutWrapperNode(swiperNode3, geometryNode, swiperNode3->GetLayoutProperty());
    swiperLayoutAlgorithm->LayoutForwardItem(&layoutWrapper3, layoutConstraint, axis, currentIndex, endPos, startPos);
    auto result3 = swiperLayoutAlgorithm->LayoutForwardItem(
        &layoutWrapper3, layoutConstraint, axis, currentIndex, endPos, startPos);
    EXPECT_FALSE(result3);
    currentIndex = 0;
    auto swiperNode4 = FrameNode::GetOrCreateFrameNode(
        V2::SWIPER_INDICATOR_ETS_TAG, 4, []() { return AceType::MakeRefPtr<SwiperPattern>(); });
    auto layoutWrapper4 = LayoutWrapperNode(swiperNode4, geometryNode, swiperNode2->GetLayoutProperty());
    swiperLayoutAlgorithm->LayoutForwardItem(&layoutWrapper4, layoutConstraint, axis, currentIndex, endPos, startPos);
    auto result4 = swiperLayoutAlgorithm->LayoutForwardItem(
        &layoutWrapper2, layoutConstraint, axis, currentIndex, endPos, startPos);
    EXPECT_FALSE(result4);

    /**
     * @tc.steps: step3. call LayoutForwardItem in different layoutWrapper and make the return value ture.
     * @tc.expected: Related function runs ok.
     */
    currentIndex = 0;
    auto wrapper = layoutWrapper.GetOrCreateChildByIndex(1);
    auto layoutProperty = wrapper->GetLayoutProperty();
    layoutProperty->UpdateVisibility(VisibleType::GONE);
    swiperLayoutAlgorithm->LayoutForwardItem(&layoutWrapper, layoutConstraint, axis, currentIndex, endPos, startPos);
    auto result = swiperLayoutAlgorithm->LayoutForwardItem(
        &layoutWrapper2, layoutConstraint, axis, currentIndex, endPos, startPos);
    EXPECT_NE(result, true);
}

/**
 * @tc.name: SwiperPatternHandleScroll001
 * @tc.desc: test HandleScroll SELF_ONLY
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternHandleScroll001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    pattern_->GetLayoutProperty<SwiperLayoutProperty>()->UpdateLoop(true);
    auto res = pattern_->HandleScroll(5.0f, SCROLL_FROM_UPDATE, NestedState::GESTURE);
    EXPECT_EQ(res.remain, 0.0f);
    EXPECT_FALSE(res.reachEdge);

    pattern_->GetLayoutProperty<SwiperLayoutProperty>()->UpdateDisableSwipe(true);
    res = pattern_->HandleScroll(5.0f, SCROLL_FROM_UPDATE, NestedState::GESTURE);
    EXPECT_EQ(res.remain, 5.0f);
    EXPECT_TRUE(res.reachEdge);
}

/**
 * @tc.name: SwiperPatternHandleScroll002
 * @tc.desc: test HandleScroll SELF_FIRST but scrolling within boundary
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternHandleScroll002, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    pattern_->GetLayoutProperty<SwiperLayoutProperty>()->UpdateLoop(true);
    auto mockScroll = AceType::MakeRefPtr<MockNestableScrollContainer>();
    EXPECT_CALL(*mockScroll, HandleScroll).Times(0);
    pattern_->parent_ = mockScroll;
    NestedScrollOptions nestedOpt = {
        .forward = NestedScrollMode::SELF_FIRST,
        .backward = NestedScrollMode::SELF_FIRST,
    };
    pattern_->SetNestedScroll(nestedOpt);
    auto res = pattern_->HandleScroll(5.0f, SCROLL_FROM_UPDATE, NestedState::GESTURE);
    EXPECT_EQ(res.remain, 0.0f);
}

/**
 * @tc.name: SwiperPatternHandleScroll003
 * @tc.desc: test HandleScroll SELF_FIRST while scrolling out of boundary and EdgeEffect doesn't consume extra offset
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternHandleScroll003, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    pattern_->GetLayoutProperty<SwiperLayoutProperty>()->UpdateLoop(false);
    pattern_->GetPaintProperty<SwiperPaintProperty>()->UpdateEdgeEffect(EdgeEffect::NONE);
    pattern_->itemPosition_.insert({ 0, SwiperItemInfo { .startPos = -0.5 } });

    auto mockScroll = AceType::MakeRefPtr<MockNestableScrollContainer>();
    EXPECT_CALL(*mockScroll, HandleScroll(5.0f, SCROLL_FROM_UPDATE, NestedState::CHILD_SCROLL, 0.f))
        .Times(1)
        .WillOnce(Return(ScrollResult { .remain = 5.0f, .reachEdge = true }));
    EXPECT_CALL(*mockScroll, HandleScroll(5.0f, SCROLL_FROM_UPDATE, NestedState::CHILD_OVER_SCROLL, 0.f))
        .Times(1)
        .WillOnce(Return(ScrollResult { .remain = 5.0f, .reachEdge = true }));
    pattern_->parent_ = mockScroll;
    NestedScrollOptions nestedOpt = {
        .forward = NestedScrollMode::SELF_FIRST,
        .backward = NestedScrollMode::SELF_FIRST,
    };
    pattern_->SetNestedScroll(nestedOpt);
    auto res = pattern_->HandleScroll(5.0f, SCROLL_FROM_UPDATE, NestedState::GESTURE, 0.f);
    EXPECT_EQ(res.remain, 5.0f);
    EXPECT_TRUE(res.reachEdge);
}

/**
 * @tc.name: SwiperPatternHandleScroll004
 * @tc.desc: test HandleScroll SELF_FIRST and scrolling out of boundary and EdgeEffect consumes extra offset
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternHandleScroll004, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    pattern_->GetLayoutProperty<SwiperLayoutProperty>()->UpdateLoop(false);
    pattern_->GetPaintProperty<SwiperPaintProperty>()->UpdateEdgeEffect(EdgeEffect::SPRING);
    pattern_->itemPosition_.insert({ 0, SwiperItemInfo { .startPos = -0.5 } });

    auto mockScroll = AceType::MakeRefPtr<MockNestableScrollContainer>();
    EXPECT_CALL(*mockScroll, HandleScroll(5.0f, SCROLL_FROM_UPDATE, NestedState::CHILD_SCROLL, 0.f))
        .Times(1)
        .WillOnce(Return(ScrollResult { .remain = 5.0f, .reachEdge = true }));
    EXPECT_CALL(*mockScroll, HandleScroll(5.0f, SCROLL_FROM_UPDATE, NestedState::CHILD_OVER_SCROLL, 0.f))
        .Times(1)
        .WillOnce(Return(ScrollResult { .remain = 5.0f, .reachEdge = true }));
    pattern_->parent_ = mockScroll;
    NestedScrollOptions nestedOpt = {
        .forward = NestedScrollMode::SELF_FIRST,
        .backward = NestedScrollMode::SELF_FIRST,
    };
    pattern_->SetNestedScroll(nestedOpt);

    auto res = pattern_->HandleScroll(5.0f, SCROLL_FROM_UPDATE, NestedState::GESTURE, 0.f);
    EXPECT_EQ(res.remain, 0.0f);
}

/**
 * @tc.name: SwiperPatternHandleScroll005
 * @tc.desc: test HandleScroll called by CHILD_SCROLL when edge is reached. Should pass offset back to child.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternHandleScroll005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create swipernode.
     */
    auto swiperNode = FrameNode::CreateFrameNode("Swiper", 0, AceType::MakeRefPtr<SwiperPattern>());
    auto swiperPattern = swiperNode->GetPattern<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);
    swiperPattern->GetLayoutProperty<SwiperLayoutProperty>()->UpdateLoop(false);
    swiperPattern->GetPaintProperty<SwiperPaintProperty>()->UpdateEdgeEffect(EdgeEffect::SPRING);
    swiperPattern->itemPosition_.insert({ 0, SwiperItemInfo { .startPos = -0.5 } });
    auto res = swiperPattern->HandleScroll(5.0f, SCROLL_FROM_UPDATE, NestedState::CHILD_SCROLL);
    EXPECT_EQ(res.remain, 4.5f);
    // three level nesting
    auto mockScroll = AceType::MakeRefPtr<MockNestableScrollContainer>();
    EXPECT_CALL(*mockScroll, HandleScroll(4.5f, SCROLL_FROM_UPDATE, NestedState::CHILD_SCROLL, 0.f))
        .Times(1)
        .WillOnce(Return(ScrollResult { .remain = 4.5f, .reachEdge = true }));
    EXPECT_CALL(*mockScroll, HandleScroll(4.5f, SCROLL_FROM_UPDATE, NestedState::CHILD_OVER_SCROLL, 0.f))
        .Times(1)
        .WillOnce(Return(ScrollResult { .remain = 4.5f, .reachEdge = true }));
    swiperPattern->parent_ = mockScroll;
    NestedScrollOptions nestedOpt = {
        .forward = NestedScrollMode::SELF_FIRST,
        .backward = NestedScrollMode::SELF_FIRST,
    };
    swiperPattern->SetNestedScroll(nestedOpt);
    res = swiperPattern->HandleScroll(5.0f, SCROLL_FROM_UPDATE, NestedState::CHILD_SCROLL, 0.f);
    EXPECT_EQ(res.remain, 4.5f);
}

/**
 * @tc.name: SwiperPatternHandleScroll006
 * @tc.desc: test HandleScroll from child animation
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternHandleScroll006, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    pattern_->GetLayoutProperty<SwiperLayoutProperty>()->UpdateLoop(true);
    // during animation
    pattern_->targetIndex_ = 1;

    auto res = pattern_->HandleScroll(5.0f, SCROLL_FROM_ANIMATION, NestedState::CHILD_SCROLL);
    EXPECT_EQ(res.remain, 5.0f);
}

/**
 * @tc.name: SwiperPatternHandleScroll007
 * @tc.desc: test HandleScroll from child mouse scroll
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternHandleScroll007, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    pattern_->GetLayoutProperty<SwiperLayoutProperty>()->UpdateLoop(true);

    // showPrevious
    auto res = pattern_->HandleScroll(5.0f, SCROLL_FROM_AXIS, NestedState::CHILD_SCROLL);
    EXPECT_EQ(res.remain, 0.0f);

    // showNext
    res = pattern_->HandleScroll(-5.0f, SCROLL_FROM_AXIS, NestedState::CHILD_SCROLL);
    EXPECT_EQ(res.remain, 0.0f);
}

/**
 * @tc.name: SwiperPatternHandleScroll008
 * @tc.desc: test HandleScroll triggering event
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternHandleScroll008, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    pattern_->itemPosition_.insert({ 0, SwiperItemInfo { .startPos = 0.0f } });
    int32_t callCount = 0;
    eventHub_->SetGestureSwipeEvent([&](int32_t index, const AnimationCallbackInfo& info) {
        ++callCount;
    });
    pattern_->OnScrollStartRecursive(0.0f);
    pattern_->HandleScroll(5.0f, SCROLL_FROM_UPDATE, NestedState::CHILD_SCROLL);
    pattern_->HandleScroll(-5.0f, SCROLL_FROM_UPDATE, NestedState::CHILD_SCROLL);
    pattern_->HandleScroll(-2.0f, SCROLL_FROM_UPDATE, NestedState::CHILD_SCROLL);
    EXPECT_EQ(callCount, 3);
}

/**
 * @tc.name: SwiperPatternHandleScrollVelocity001
 * @tc.desc: test HandleScrollVelocity self handle
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternHandleScrollVelocity001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    pattern_->GetLayoutProperty<SwiperLayoutProperty>()->UpdateLoop(true);
    auto res = pattern_->HandleScrollVelocity(5.0f);
    EXPECT_TRUE(res);

    pattern_->GetLayoutProperty<SwiperLayoutProperty>()->UpdateDisableSwipe(true);
    res = pattern_->HandleScrollVelocity(5.0f);
    EXPECT_FALSE(res);
}

/**
 * @tc.name: SwiperPatternHandleScrollVelocity002
 * @tc.desc: test HandleScrollVelocity pass to parent
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternHandleScrollVelocity002, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    pattern_->GetLayoutProperty<SwiperLayoutProperty>()->UpdateLoop(false);
    pattern_->itemPosition_.insert({ 0, SwiperItemInfo { .startPos = 0.0f } });
    auto mockScroll = AceType::MakeRefPtr<MockNestableScrollContainer>();
    EXPECT_CALL(*mockScroll, HandleScrollVelocity).Times(1).WillOnce(Return(true));
    pattern_->parent_ = mockScroll;
    NestedScrollOptions nestedOpt = {
        .forward = NestedScrollMode::SELF_FIRST,
        .backward = NestedScrollMode::SELF_FIRST,
    };
    pattern_->SetNestedScroll(nestedOpt);

    auto res = pattern_->HandleScrollVelocity(5.0f);
    EXPECT_TRUE(res);
}

/**
 * @tc.name: SwiperPatternHandleScrollVelocity003
 * @tc.desc: test HandleScrollVelocity pass to parent and parent doesn't consume
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternHandleScrollVelocity003, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    pattern_->GetLayoutProperty<SwiperLayoutProperty>()->UpdateLoop(false);
    pattern_->GetPaintProperty<SwiperPaintProperty>()->UpdateEdgeEffect(EdgeEffect::NONE);
    pattern_->itemPosition_.insert({ 0, SwiperItemInfo { .startPos = 0.0f } });
    auto mockScroll = AceType::MakeRefPtr<MockNestableScrollContainer>();
    EXPECT_CALL(*mockScroll, HandleScrollVelocity).Times(2).WillRepeatedly(Return(false));
    pattern_->parent_ = mockScroll;
    NestedScrollOptions nestedOpt = {
        .forward = NestedScrollMode::SELF_FIRST,
        .backward = NestedScrollMode::SELF_FIRST,
    };
    pattern_->SetNestedScroll(nestedOpt);
    auto res = pattern_->HandleScrollVelocity(5.0f);
    EXPECT_FALSE(res);

    // change EdgeEffect to Spring and redo
    // should consume velocity
    pattern_->GetPaintProperty<SwiperPaintProperty>()->UpdateEdgeEffect(EdgeEffect::SPRING);
    mockScroll.Reset();
    mockScroll = AceType::MakeRefPtr<MockNestableScrollContainer>();
    EXPECT_CALL(*mockScroll, HandleScrollVelocity).Times(2).WillRepeatedly(Return(false));

    pattern_->parent_ = mockScroll;
    res = pattern_->HandleScrollVelocity(5.0f);
    EXPECT_TRUE(res);
}

/**
 * @tc.name: SwiperPatternOnScrollStart001
 * @tc.desc: test OnScrollStartRecursive
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternOnScrollStart001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    pattern_->GetLayoutProperty<SwiperLayoutProperty>()->UpdateLoop(false);
    pattern_->GetPaintProperty<SwiperPaintProperty>()->UpdateEdgeEffect(EdgeEffect::NONE);
    auto mockScroll = AceType::MakeRefPtr<MockNestableScrollContainer>();
    auto mockScrollNode = FrameNode::CreateFrameNode("MockScroll", -1, mockScroll);
    frameNode_->MountToParent(mockScrollNode);

    EXPECT_CALL(*mockScroll, OnScrollStartRecursive).Times(1);
    EXPECT_CALL(*mockScroll, GetAxis).Times(1).WillOnce(Return(Axis::HORIZONTAL));
    NestedScrollOptions nestedOpt = {
        .forward = NestedScrollMode::SELF_FIRST,
        .backward = NestedScrollMode::SELF_FIRST,
    };
    pattern_->SetNestedScroll(nestedOpt);
    pattern_->isDragging_ = false;
    pattern_->currentIndex_ = 3;
    EXPECT_EQ(pattern_->gestureSwipeIndex_, 0);

    pattern_->OnScrollStartRecursive(5.0f);
    EXPECT_TRUE(pattern_->childScrolling_);
    EXPECT_EQ(pattern_->gestureSwipeIndex_, 3);
}

/**
 * @tc.name: SwiperPatternOnScrollEnd001
 * @tc.desc: test OnScrollEndRecursive
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternOnScrollEnd001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    pattern_->GetLayoutProperty<SwiperLayoutProperty>()->UpdateLoop(false);
    pattern_->GetPaintProperty<SwiperPaintProperty>()->UpdateEdgeEffect(EdgeEffect::NONE);
    auto mockScroll = AceType::MakeRefPtr<MockNestableScrollContainer>();
    EXPECT_CALL(*mockScroll, OnScrollEndRecursive).Times(1);
    EXPECT_CALL(*mockScroll, HandleScrollVelocity).Times(1);
    NestedScrollOptions nestedOpt = {
        .forward = NestedScrollMode::SELF_FIRST,
        .backward = NestedScrollMode::SELF_FIRST,
    };
    pattern_->SetNestedScroll(nestedOpt);
    pattern_->parent_ = mockScroll;
    pattern_->OnScrollEndRecursive(std::nullopt);
    EXPECT_FALSE(pattern_->childScrolling_);

    pattern_->NotifyParentScrollEnd();
}

/**
 * @tc.name: HandleTouchBottomLoop001
 * @tc.desc: test Swiper indicator no touch bottom in loop
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, HandleTouchBottomLoop001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    EXPECT_EQ(pattern_->TotalCount(), 4);
    pattern_->currentFirstIndex_ = 1;
    pattern_->currentIndex_ = 1;
    pattern_->gestureState_ = GestureState::GESTURE_STATE_FOLLOW_RIGHT;
    pattern_->HandleTouchBottomLoop();
    EXPECT_EQ(pattern_->touchBottomType_, TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_NONE);
}

/**
 * @tc.name: HandleTouchBottomLoop002
 * @tc.desc: test Swiper indicator touch left bottom in loop
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, HandleTouchBottomLoop002, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    EXPECT_EQ(pattern_->TotalCount(), 4);
    pattern_->currentFirstIndex_ = pattern_->TotalCount() - 1;
    pattern_->currentIndex_ = 0;
    pattern_->gestureState_ = GestureState::GESTURE_STATE_FOLLOW_LEFT;
    pattern_->HandleTouchBottomLoop();
    EXPECT_EQ(pattern_->touchBottomType_, TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_LEFT);

    pattern_->gestureState_ = GestureState::GESTURE_STATE_FOLLOW_RIGHT;
    pattern_->HandleTouchBottomLoop();
    EXPECT_EQ(pattern_->touchBottomType_, TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_RIGHT);

    pattern_->gestureState_ = GestureState::GESTURE_STATE_RELEASE_LEFT;
    pattern_->HandleTouchBottomLoop();
    EXPECT_EQ(pattern_->touchBottomType_, TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_LEFT);
}

/**
 * @tc.name: HandleTouchBottomLoop003
 * @tc.desc: test Swiper indicator touch right bottom in loop
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, HandleTouchBottomLoop003, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    EXPECT_EQ(pattern_->TotalCount(), 4);
    pattern_->currentFirstIndex_ = 0;
    pattern_->currentIndex_ = pattern_->TotalCount() - 1;
    pattern_->gestureState_ = GestureState::GESTURE_STATE_RELEASE_RIGHT;
    pattern_->HandleTouchBottomLoop();
    EXPECT_EQ(pattern_->touchBottomType_, TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_RIGHT);

    pattern_->currentFirstIndex_ = pattern_->TotalCount() - 1;
    pattern_->currentIndex_ = pattern_->TotalCount() - 1;
    pattern_->gestureState_ = GestureState::GESTURE_STATE_FOLLOW_LEFT;
    pattern_->HandleTouchBottomLoop();
    EXPECT_EQ(pattern_->touchBottomType_, TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_LEFT);

    pattern_->currentFirstIndex_ = pattern_->TotalCount() - 1;
    pattern_->currentIndex_ = pattern_->TotalCount() - 1;
    pattern_->gestureState_ = GestureState::GESTURE_STATE_FOLLOW_RIGHT;
    pattern_->HandleTouchBottomLoop();
    EXPECT_EQ(pattern_->touchBottomType_, TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_RIGHT);
}

/**
 * @tc.name: CalculateGestureState001
 * @tc.desc: test Swiper indicator gesture state
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, CalculateGestureState001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    EXPECT_EQ(pattern_->TotalCount(), 4);
    pattern_->gestureState_ = GestureState::GESTURE_STATE_NONE;
    pattern_->CalculateGestureState(1.0f, 0.0f, 1);
    EXPECT_EQ(pattern_->gestureState_, GestureState::GESTURE_STATE_RELEASE_LEFT);

    pattern_->gestureState_ = GestureState::GESTURE_STATE_NONE;
    pattern_->CalculateGestureState(-1.0f, 0.0f, 1);
    EXPECT_EQ(pattern_->gestureState_, GestureState::GESTURE_STATE_RELEASE_RIGHT);

    pattern_->currentFirstIndex_ = 0;
    pattern_->currentIndex_ = 0;
    pattern_->turnPageRate_ = -1.0f;
    pattern_->gestureState_ = GestureState::GESTURE_STATE_NONE;
    pattern_->CalculateGestureState(0.0f, -1.1f, 1);
    EXPECT_EQ(pattern_->gestureState_, GestureState::GESTURE_STATE_FOLLOW_RIGHT);

    pattern_->currentFirstIndex_ = 0;
    pattern_->currentIndex_ = 1;
    pattern_->turnPageRate_ = -1.0f;
    pattern_->gestureState_ = GestureState::GESTURE_STATE_NONE;
    pattern_->CalculateGestureState(0.0f, -1.1f, 1);
    EXPECT_EQ(pattern_->gestureState_, GestureState::GESTURE_STATE_FOLLOW_LEFT);

    pattern_->currentFirstIndex_ = 0;
    pattern_->currentIndex_ = 0;
    pattern_->turnPageRate_ = -1.0f;
    pattern_->gestureState_ = GestureState::GESTURE_STATE_NONE;
    pattern_->CalculateGestureState(0.0f, -0.9f, 1);
    EXPECT_EQ(pattern_->gestureState_, GestureState::GESTURE_STATE_FOLLOW_RIGHT);
}

/**
 * @tc.name: GetStartAndEndIndex001
 * @tc.desc: get long point start and end index
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, GetStartAndEndIndex001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    EXPECT_EQ(pattern_->TotalCount(), 4);
    RefPtr<DotIndicatorModifier> modifier = AceType::MakeRefPtr<DotIndicatorModifier>();
    RefPtr<DotIndicatorPaintMethod> paintMethod = AceType::MakeRefPtr<DotIndicatorPaintMethod>(modifier);

    paintMethod->itemCount_ = pattern_->TotalCount();
    paintMethod->turnPageRate_ = -0.9f;

    // expand to long point
    paintMethod->pointAnimationStage_ = PointAnimationStage::STATE_EXPAND_TO_LONG_POINT;
    paintMethod->gestureState_ = GestureState::GESTURE_STATE_RELEASE_LEFT;
    paintMethod->touchBottomTypeLoop_ = TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_LEFT;
    auto index = pattern_->TotalCount() - 1;
    auto expectVal = std::pair<int32_t, int32_t>(index, index);
    EXPECT_EQ(paintMethod->GetStartAndEndIndex(index), expectVal);

    paintMethod->gestureState_ = GestureState::GESTURE_STATE_RELEASE_RIGHT;
    paintMethod->touchBottomTypeLoop_ = TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_RIGHT;
    expectVal = std::pair<int32_t, int32_t>(0, 0);
    EXPECT_EQ(paintMethod->GetStartAndEndIndex(index), expectVal);
}

/**
 * @tc.name: GetStartAndEndIndex002
 * @tc.desc: get long point start and end index
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, GetStartAndEndIndex002, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    EXPECT_EQ(pattern_->TotalCount(), 4);
    RefPtr<DotIndicatorModifier> modifier = AceType::MakeRefPtr<DotIndicatorModifier>();
    RefPtr<DotIndicatorPaintMethod> paintMethod = AceType::MakeRefPtr<DotIndicatorPaintMethod>(modifier);

    paintMethod->itemCount_ = pattern_->TotalCount();
    paintMethod->turnPageRate_ = -0.8f;

    // shrink to black point
    paintMethod->pointAnimationStage_ = PointAnimationStage::STATE_SHRINKT_TO_BLACK_POINT;
    paintMethod->touchBottomTypeLoop_ = TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_LEFT;
    auto expectVal = std::pair<int32_t, int32_t>(0, 0);
    auto index = pattern_->TotalCount() - 1;
    EXPECT_EQ(paintMethod->GetStartAndEndIndex(index), expectVal);

    paintMethod->gestureState_ = GestureState::GESTURE_STATE_RELEASE_RIGHT;
    paintMethod->touchBottomTypeLoop_ = TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_RIGHT;
    expectVal = std::pair<int32_t, int32_t>(index, index);
    EXPECT_EQ(paintMethod->GetStartAndEndIndex(1), expectVal);

    paintMethod->gestureState_ = GestureState::GESTURE_STATE_RELEASE_LEFT;
    expectVal = std::pair<int32_t, int32_t>(index, index);
    EXPECT_EQ(paintMethod->GetStartAndEndIndex(index), expectVal);
}

/**
 * @tc.name: AdjustPointCenterXForTouchBottom
 * @tc.desc: adjust long point centerX for touch bottom
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, AdjustPointCenterXForTouchBottom001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    auto totalCount = pattern_->TotalCount();
    EXPECT_EQ(totalCount, 4);
    RefPtr<DotIndicatorModifier> modifier = AceType::MakeRefPtr<DotIndicatorModifier>();
    RefPtr<DotIndicatorPaintMethod> paintMethod = AceType::MakeRefPtr<DotIndicatorPaintMethod>(modifier);
    DotIndicatorPaintMethod::StarAndEndPointCenter pointCenter;
    LinearVector<float> endVectorBlackPointCenterX;
    for (int32_t i = 0; i < totalCount; ++i) {
        endVectorBlackPointCenterX.emplace_back(static_cast<float>(i + 1));
    }

    int32_t startCurrentIndex = 0;
    int32_t endCurrentIndex = totalCount - 1;
    float selectedItemWidth = 0.0f;

    // shrink to black point
    paintMethod->pointAnimationStage_ = PointAnimationStage::STATE_SHRINKT_TO_BLACK_POINT;
    paintMethod->touchBottomTypeLoop_ = TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_LEFT;
    paintMethod->gestureState_ = GestureState::GESTURE_STATE_RELEASE_LEFT;
    paintMethod->AdjustPointCenterXForTouchBottom(
        pointCenter, endVectorBlackPointCenterX, startCurrentIndex, endCurrentIndex, selectedItemWidth, 0);
    EXPECT_EQ(pointCenter.endLongPointRightCenterX, endVectorBlackPointCenterX[0]);
    EXPECT_EQ(pointCenter.endLongPointLeftCenterX, endVectorBlackPointCenterX[0]);

    paintMethod->pointAnimationStage_ = PointAnimationStage::STATE_SHRINKT_TO_BLACK_POINT;
    paintMethod->touchBottomTypeLoop_ = TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_RIGHT;
    pointCenter = { 0.0f, 0.0f, 0.0f, 0.0f };
    paintMethod->AdjustPointCenterXForTouchBottom(
        pointCenter, endVectorBlackPointCenterX, startCurrentIndex, endCurrentIndex, selectedItemWidth, 0);
    EXPECT_EQ(pointCenter.endLongPointRightCenterX, endVectorBlackPointCenterX[startCurrentIndex]);
    EXPECT_EQ(pointCenter.endLongPointLeftCenterX, endVectorBlackPointCenterX[startCurrentIndex]);

    // expand to long point
    paintMethod->pointAnimationStage_ = PointAnimationStage::STATE_EXPAND_TO_LONG_POINT;
    paintMethod->gestureState_ = GestureState::GESTURE_STATE_RELEASE_LEFT;
    paintMethod->touchBottomTypeLoop_ = TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_LEFT;
    pointCenter = { 0.0f, 0.0f, 0.0f, 0.0f };
    paintMethod->AdjustPointCenterXForTouchBottom(
        pointCenter, endVectorBlackPointCenterX, startCurrentIndex, endCurrentIndex, selectedItemWidth, 0);
    EXPECT_EQ(pointCenter.startLongPointRightCenterX, endVectorBlackPointCenterX[endCurrentIndex]);
    EXPECT_EQ(pointCenter.endLongPointLeftCenterX, endVectorBlackPointCenterX[endCurrentIndex]);

    paintMethod->pointAnimationStage_ = PointAnimationStage::STATE_EXPAND_TO_LONG_POINT;
    paintMethod->gestureState_ = GestureState::GESTURE_STATE_RELEASE_RIGHT;
    paintMethod->touchBottomTypeLoop_ = TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_RIGHT;
    pointCenter = { 0.0f, 0.0f, 0.0f, 0.0f };
    paintMethod->AdjustPointCenterXForTouchBottom(
        pointCenter, endVectorBlackPointCenterX, startCurrentIndex, endCurrentIndex, selectedItemWidth, 0);
    EXPECT_EQ(pointCenter.startLongPointRightCenterX, endVectorBlackPointCenterX[0]);
    EXPECT_EQ(pointCenter.endLongPointLeftCenterX, endVectorBlackPointCenterX[0]);
}

/**
 * @tc.name: GetLongPointAnimationStateSecondCenter
 * @tc.desc: get long point animation state second center
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, GetLongPointAnimationStateSecondCenter001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    RefPtr<DotIndicatorModifier> modifier = AceType::MakeRefPtr<DotIndicatorModifier>();
    RefPtr<DotIndicatorPaintMethod> paintMethod = AceType::MakeRefPtr<DotIndicatorPaintMethod>(modifier);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto paintProperty = AceType::MakeRefPtr<DotIndicatorPaintProperty>();
    auto renderContext = frameNode_->GetRenderContext();

    PaintWrapper paintWrapper(renderContext, geometryNode, paintProperty);
    std::vector<std::pair<float, float>> pointCenterX;
    paintMethod->turnPageRate_ = -1.0f;

    paintMethod->gestureState_ = GestureState::GESTURE_STATE_RELEASE_LEFT;
    paintMethod->touchBottomTypeLoop_ = TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_LEFT;
    paintMethod->GetLongPointAnimationStateSecondCenter(&paintWrapper, pointCenterX);
    EXPECT_EQ(pointCenterX.size(), 1);

    paintMethod->gestureState_ = GestureState::GESTURE_STATE_RELEASE_RIGHT;
    paintMethod->touchBottomTypeLoop_ = TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_RIGHT;
    pointCenterX.clear();
    paintMethod->GetLongPointAnimationStateSecondCenter(&paintWrapper, pointCenterX);
    EXPECT_EQ(pointCenterX.size(), 1);

    paintMethod->gestureState_ = GestureState::GESTURE_STATE_RELEASE_LEFT;
    paintMethod->touchBottomTypeLoop_ = TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_RIGHT;
    pointCenterX.clear();
    paintMethod->GetLongPointAnimationStateSecondCenter(&paintWrapper, pointCenterX);
    EXPECT_EQ(pointCenterX.size(), 0);

    paintMethod->gestureState_ = GestureState::GESTURE_STATE_RELEASE_LEFT;
    paintMethod->touchBottomTypeLoop_ = TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_RIGHT;
    pointCenterX.clear();
    paintMethod->GetLongPointAnimationStateSecondCenter(&paintWrapper, pointCenterX);
    EXPECT_EQ(pointCenterX.size(), 0);
}

/**
 * @tc.name: PlayLongPointAnimation
 * @tc.desc: play long point animation
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, PlayLongPointAnimation001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    auto totalCount = pattern_->TotalCount();
    EXPECT_EQ(totalCount, 4);
    RefPtr<DotIndicatorModifier> modifier = AceType::MakeRefPtr<DotIndicatorModifier>();
    LinearVector<float> endVectorBlackPointCenterX;
    for (int32_t i = 0; i < totalCount; ++i) {
        endVectorBlackPointCenterX.emplace_back(static_cast<float>(i + 1));
    }
    std::vector<std::pair<float, float>> longPointCenterX = { { 0.0f, 0.0f } };

    modifier->PlayLongPointAnimation(longPointCenterX, GestureState::GESTURE_STATE_RELEASE_RIGHT,
        TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_NONE, endVectorBlackPointCenterX);
    EXPECT_FALSE(modifier->isTouchBottomLoop_);

    longPointCenterX.emplace_back(1.0f, 1.0f);
    modifier->PlayLongPointAnimation(longPointCenterX, GestureState::GESTURE_STATE_RELEASE_RIGHT,
        TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_RIGHT, endVectorBlackPointCenterX);
    EXPECT_FALSE(modifier->isTouchBottomLoop_);
}

/**
 * @tc.name: SwiperLayoutAlgorithmGetChildMaxSize002
 * @tc.desc: GetChildMaxSize
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperLayoutAlgorithmGetChildMaxSize002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Default value
     */
    CreateWithItem([](SwiperModelNG model) {});
    auto swiperLayoutAlgorithm = AceType::DynamicCast<SwiperLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());

    auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper = LayoutWrapperNode(indicatorNode, geometryNode, indicatorNode->GetLayoutProperty());

    layoutWrapper.currentChildCount_ = 2;
    layoutWrapper.childrenMap_.emplace(std::make_pair(
        0, AceType::MakeRefPtr<LayoutWrapperNode>(indicatorNode, geometryNode, indicatorNode->GetLayoutProperty())));
    layoutWrapper.childrenMap_.emplace(std::make_pair(
        1, AceType::MakeRefPtr<LayoutWrapperNode>(indicatorNode, nullptr, indicatorNode->GetLayoutProperty())));

    LayoutConstraintF layoutConstraint;
    layoutConstraint.maxSize = SizeF(720.f, 1136.f);
    layoutConstraint.percentReference = SizeF(720.f, 1136.f);
    layoutConstraint.parentIdealSize.SetSize(SizeF(720.f, 1136.f));
    ASSERT_NE(layoutWrapper.layoutProperty_, nullptr);

    layoutWrapper.GetLayoutProperty()->UpdateLayoutConstraint(layoutConstraint);
    Axis axis = Axis::HORIZONTAL;
    bool isMainAxis = true;
    swiperLayoutAlgorithm->totalItemCount_ = 3;

    /**
     * @tc.steps: step2. call GetChildMaxSize.
     * @tc.expected: GetChildMaxSize->itemPosition_ not empty
     */
    swiperLayoutAlgorithm->itemPosition_.clear();
    swiperLayoutAlgorithm->GetChildMaxSize(&layoutWrapper, axis, isMainAxis);
    EXPECT_TRUE(swiperLayoutAlgorithm->itemPosition_.empty());
}

/**
 * @tc.name: ResetDisplayCount001
 * @tc.desc: Swiper Model NG.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, ResetDisplayCount001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Default value
     */
    SwiperModelNG model;
    model.Create();
    ViewAbstract::SetWidth(CalcLength(SWIPER_WIDTH));
    ViewAbstract::SetHeight(CalcLength(SWIPER_HEIGHT));
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<SwiperPattern>();
    EXPECT_NE(pattern, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<SwiperLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);
    auto paintProperty = frameNode->GetPaintProperty<SwiperPaintProperty>();
    EXPECT_NE(paintProperty, nullptr);

    /**
     * @tc.steps: step3.1. Test SetIndex function.
     * @tc.expected: layoutProperty->GetIndex() is equal to 1.
     */
    model.SetIndex(1);
    EXPECT_EQ(layoutProperty->GetIndex(), 1);

    /**
     * @tc.steps: step3.1. Test SetIndex function.
     * @tc.expected: layoutProperty->GetIndex() is equal to 1.
     */
    model.SetDisplayCount(10);
    model.ResetDisplayCount();
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    auto uiNode = AceType::DynamicCast<FrameNode>(element);
    pattern = uiNode->GetPattern<SwiperPattern>();
    EXPECT_NE(pattern->GetDisplayCount(), 10);
}

/**
 * @tc.name: SetMinSize001
 * @tc.desc: Swiper Model NG.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SetMinSize003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Default value
     */
    SwiperModelNG model;
    model.Create();
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto pattern = frameNode->GetPattern<SwiperPattern>();
    auto layoutProperty = frameNode->GetLayoutProperty<SwiperLayoutProperty>();
    auto paintProperty = frameNode->GetPaintProperty<SwiperPaintProperty>();

    /**
     * @tc.steps: step2. Calling the SetMinSize interface to set Dimension
     * @tc.expected: LayoutProperty ->GetMinSize(), equal to Dimension()
     */
    model.SetMinSize(Dimension(10));
    layoutProperty->GetMinSize();
    EXPECT_EQ(layoutProperty->GetMinSize(), Dimension(10));
}

/**
 * @tc.name: GetContentDrawFunction001
 * @tc.desc: PaintFade
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, GetContentDrawFunction001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Default value
     */
    CreateWithItem([](SwiperModelNG model) {});
    SwiperPaintMethod swiperPaintMethod1(Axis::VERTICAL, 0.0f);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(geometryNode, nullptr);

    auto paintProperty = AceType::MakeRefPtr<PaintProperty>();
    EXPECT_NE(paintProperty, nullptr);
    auto renderContext = frameNode_->GetRenderContext();
    EXPECT_NE(renderContext, nullptr);
    PaintWrapper paintWrapper(renderContext, geometryNode, paintProperty);

    /**
     * @tc.steps: step2. Calling the switchPaintMethod1. GetContentDrawFunction (&paintWrapper) interface
     * @tc.expected: paintFunc not empty
     */
    auto paintFunc = swiperPaintMethod1.GetContentDrawFunction(&paintWrapper);
    EXPECT_NE(paintFunc, nullptr);
}

HWTEST_F(SwiperTestNg, SwiperPatternOnModifyDone00081, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Default value
     */
    CreateWithItem([](SwiperModelNG model) {});
    auto gestureEventHub = AceType::MakeRefPtr<GestureEventHub>(AceType::WeakClaim(AceType::RawPtr(eventHub_)));

    auto pipeline = MockPipelineContext::GetCurrent();
    pipeline->restoreNodeInfo_.emplace(std::make_pair(1, "testFlushUITasks"));
    pattern_->InitPanEvent(gestureEventHub);
    EXPECT_EQ(pattern_->direction_, Axis::HORIZONTAL);

    pattern_->touchEvent_ = nullptr;
    pattern_->InitTouchEvent(gestureEventHub);
    TouchEventFunc callback = [](TouchEventInfo& info) {};

    pattern_->touchEvent_ = AceType::MakeRefPtr<TouchEventImpl>(std::move(callback));
    pattern_->InitTouchEvent(gestureEventHub);
    pattern_->OnModifyDone();
    EXPECT_TRUE(pattern_->panEvent_);
}

/**
 * @tc.name: SwiperPatternOnDirtyLayoutWrapperSwap002
 * @tc.desc: OnDirtyLayoutWrapperSwap
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternOnDirtyLayoutWrapperSwap005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Default value
     */
    CreateWithItem([](SwiperModelNG model) {
        model.SetDisplayArrow(true); // show arrow
        model.SetHoverShow(false);
        model.SetArrowStyle(ARROW_PARAMETERS);
    });
    auto indicatorNode = GetChildFrameNode(frameNode_, 4);
    auto firstChild = AccessibilityManager::DynamicCast<FrameNode>(indicatorNode);
    RefPtr<GeometryNode> firstGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    firstGeometryNode->Reset();
    firstGeometryNode->SetFrameSize(SizeF(20.0, 20.0));
    auto firstLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(firstChild, firstGeometryNode, firstChild->GetLayoutProperty());
    auto dirty = AceType::MakeRefPtr<LayoutWrapperNode>(firstChild, firstGeometryNode, firstChild->GetLayoutProperty());
    dirty->AppendChild(firstLayoutWrapper);
    struct DirtySwapConfig config;
    pattern_->isInit_ = true;
    config.skipMeasure = false;
    config.skipLayout = false;

    TurnPageRateFunc callback = [](const int32_t i, float f) {};
    pattern_->swiperController_->SetTurnPageRateCallback(callback);
    struct SwiperItemInfo swiperItemInfo1;
    swiperItemInfo1.startPos = -1.0f;
    swiperItemInfo1.endPos = -1.0f;

    auto swiperLayoutAlgorithm = AceType::DynamicCast<SwiperLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    dirty->layoutAlgorithm_ = AceType::MakeRefPtr<LayoutAlgorithmWrapper>(swiperLayoutAlgorithm);
    dirty->layoutAlgorithm_->layoutAlgorithm_ = AceType::MakeRefPtr<SwiperLayoutAlgorithm>();
    ASSERT_NE(dirty->GetLayoutAlgorithm(), nullptr);
    ASSERT_NE(AceType::DynamicCast<SwiperLayoutAlgorithm>(dirty->GetLayoutAlgorithm()->GetLayoutAlgorithm()), nullptr);
    AceType::DynamicCast<SwiperLayoutAlgorithm>(dirty->GetLayoutAlgorithm()->GetLayoutAlgorithm())
        ->itemPosition_.emplace(std::make_pair(1, swiperItemInfo1));
    pattern_->isDragging_ = true;
    pattern_->windowSizeChangeReason_ = WindowSizeChangeReason::ROTATION;
    /**
     * @tc.steps: step2. Calling the OnDirtyLayoutWrapperSwap interface
     * @tc.expected: Pattern_ -> WindowSizeChangeReason_ Not equal to WindowSizeChangeReason::ROTATION
     */
    pattern_->OnDirtyLayoutWrapperSwap(dirty, config);
    EXPECT_NE(pattern_->windowSizeChangeReason_, WindowSizeChangeReason::ROTATION);
}

/**
 * @tc.name: SwiperAutoLinearAnimationNeedReset002
 * @tc.desc: OnDirtyLayoutWrapperSwap
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperAutoLinearAnimationNeedReset002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Default value
     */
    CreateWithItem([](SwiperModelNG model) {});
    EXPECT_EQ(frameNode_->children_.size(), 5);
    pattern_->itemPosition_.clear();
    /**
     * @tc.steps: step2. Calling the AutoLinearAnimationNeedReset interface
     * @tc.expected: ItemPosition_ Empty() condition is true
     */
    pattern_->AutoLinearAnimationNeedReset(0);
    EXPECT_TRUE(pattern_->itemPosition_.empty());
}

/**
 * @tc.name: SwiperPatternAlgorithmMeasure003
 * @tc.desc: Measure
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternAlgorithmMeasure003, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {
        model.SetDisplayArrow(true); // show arrow
        model.SetHoverShow(false);
        model.SetArrowStyle(ARROW_PARAMETERS);
    });
    layoutProperty_->UpdateBackgroundSize(3.0_vp);
    FlushLayoutTask(frameNode_);

    auto swiperPatternAlgorithm = AceType::DynamicCast<SwiperLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    swiperPatternAlgorithm->mainSizeIsMeasured_ = true;
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(swiperPatternAlgorithm->mainSizeIsMeasured_);

    swiperPatternAlgorithm->mainSizeIsMeasured_ = true;
    frameNode_->isConstraintNotChanged_ = true;
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(frameNode_->isConstraintNotChanged_);

    /**
     * @tc.steps: step1. Set totalItemCount_ Equal to 0
     * @tc.expected: SwitchPatternAlgorithm ->totalitemCount_== 0 condition is true
     */
    swiperPatternAlgorithm->totalItemCount_ = 0;
    swiperPatternAlgorithm->mainSizeIsMeasured_ = true;
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(swiperPatternAlgorithm->totalItemCount_ == 0);

    /**
     * @tc.steps: step1. Set totalItem Count_ Greater than 0
     * @tc.expected: SwitchPatternAlgorithm ->totalitemCount_ Condition greater than 0 is true
     */
    swiperPatternAlgorithm->totalItemCount_ = 10;
    swiperPatternAlgorithm->mainSizeIsMeasured_ = true;
    frameNode_->isConstraintNotChanged_ = true;
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(swiperPatternAlgorithm->totalItemCount_ > 0);
}

/**
 * @tc.name: SwiperProcessDelta001
 * @tc.desc: Test for SwiperPattern::ProcessDelta.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperProcessDelta001, TestSize.Level1)
{
    float mainSize = 50.0f;
    float delta = 5.0f;
    float deltaSum = 46.0f;
    SwiperPattern::ProcessDelta(delta, mainSize, deltaSum);
    EXPECT_EQ(delta, 4.0f);

    delta = -10.0f;
    deltaSum = 50.0f;
    SwiperPattern::ProcessDelta(delta, mainSize, deltaSum);
    EXPECT_EQ(delta, -10.0f);

    delta = -10.0f;
    deltaSum = -40.0f;
    SwiperPattern::ProcessDelta(delta, mainSize, deltaSum);
    EXPECT_EQ(delta, -10.0f);

    delta = -10.0f;
    deltaSum = -50.0f;
    SwiperPattern::ProcessDelta(delta, mainSize, deltaSum);
    EXPECT_EQ(delta, 0.0f);

    delta = -50.0f;
    deltaSum = -50.0f;
    SwiperPattern::ProcessDelta(delta, mainSize, deltaSum);
    EXPECT_EQ(delta, 0.0f);

    delta = 1.0f;
    deltaSum = -50.0f;
    SwiperPattern::ProcessDelta(delta, mainSize, deltaSum);
    EXPECT_EQ(delta, 1.0f);
}

/**
 * @tc.name: PlayLongPointAnimation
 * @tc.desc: play long point animation
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, PlayLongPointAnimation002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Default value
     */
    CreateWithItem([](SwiperModelNG model) {});
    auto totalCount = pattern_->TotalCount();
    EXPECT_EQ(totalCount, 4);
    RefPtr<DotIndicatorModifier> modifier = AceType::MakeRefPtr<DotIndicatorModifier>();
    LinearVector<float> endVectorBlackPointCenterX;
    for (int32_t i = 0; i < totalCount; ++i) {
        endVectorBlackPointCenterX.emplace_back(static_cast<float>(i + 1));
    }
    std::vector<std::pair<float, float>> longPointCenterX = { { 0.0f, 0.0f } };

    /**
     * @tc.steps: step1.clear longPointCenterX Calling the PlayLongPointAnimation interface
     * @tc.expected: longPointCenterX is empty.
     */
    longPointCenterX.clear();
    modifier->PlayLongPointAnimation(longPointCenterX, GestureState::GESTURE_STATE_RELEASE_RIGHT,
        TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_RIGHT, endVectorBlackPointCenterX);
    EXPECT_TRUE(longPointCenterX.empty());

    /**
     * @tc.steps: step2.GestureState:: Gesture_ DATE_ RELEASE_ Assign the value of Left to gastureState
     * @tc.expected: Satisfying the condition GestureState==GestureState:: GESTURE_ DATE_ RELEASE_ Left
     */
    auto gestureState = GestureState::GESTURE_STATE_RELEASE_LEFT;
    modifier->PlayLongPointAnimation(
        longPointCenterX, gestureState, TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_RIGHT, endVectorBlackPointCenterX);
    EXPECT_TRUE(gestureState == GestureState::GESTURE_STATE_RELEASE_LEFT);
}

/**
 * @tc.name: StopAnimation
 * @tc.desc: play long point animation
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, StopAnimation001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Default value
     */
    CreateWithItem([](SwiperModelNG model) {});
    auto totalCount = pattern_->TotalCount();
    EXPECT_EQ(totalCount, 4);

    RefPtr<DotIndicatorModifier> modifier = AceType::MakeRefPtr<DotIndicatorModifier>();
    /**
     * @tc.steps: step2. Calling the StopAnimation interface
     * @tc.expected: LongPointLeftAnimEnd_ And longPointRightAnimEnd_ To be true
     */
    modifier->StopAnimation();
    EXPECT_TRUE(modifier->longPointLeftAnimEnd_ && modifier->longPointRightAnimEnd_);
}

/**
 * @tc.name: PlayIndicatorAnimation
 * @tc.desc: play long point animation
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, PlayIndicatorAnimation001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Default value
     */
    CreateWithItem([](SwiperModelNG model) {});
    auto totalCount = pattern_->TotalCount();
    EXPECT_EQ(totalCount, 4);

    RefPtr<DotIndicatorModifier> modifier = AceType::MakeRefPtr<DotIndicatorModifier>();
    LinearVector<float> vectorBlackPointCenterX;
    vectorBlackPointCenterX.push_back(20.0f);
    vectorBlackPointCenterX.push_back(20.0f);
    std::vector<std::pair<float, float>> longPointCenterX = { { 0.0f, 0.0f } };
    auto gestureState = GestureState::GESTURE_STATE_RELEASE_LEFT;
    TouchBottomTypeLoop touchBottomTypeLoop;
    touchBottomTypeLoop = TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_LEFT;
    /**
     * @tc.steps: step2. Construct parameters to call PlayIndicator Animation
     * @tc.expected: IsTouchBottomLoop_ Equal to false
     */
    modifier->PlayIndicatorAnimation(vectorBlackPointCenterX, longPointCenterX, gestureState, touchBottomTypeLoop);
    EXPECT_FALSE(modifier->isTouchBottomLoop_);
}

/**
 * @tc.name: UpdateLongPointDilateRatio001
 * @tc.desc: play long point animation
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, UpdateLongPointDilateRatio001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Default value
     */
    CreateWithItem([](SwiperModelNG model) {});
    auto totalCount = pattern_->TotalCount();
    EXPECT_EQ(totalCount, 4);

    RefPtr<DotIndicatorModifier> modifier = AceType::MakeRefPtr<DotIndicatorModifier>();
    /**
     * @tc.steps: step2. Call the UpdateLongPointDilateRatio interface to convert longPointIsHover_ Set to false
     * @tc.expected: LongPointIsHover_ Equal to true
     */
    modifier->longPointIsHover_ = true;
    modifier->UpdateLongPointDilateRatio();
    EXPECT_TRUE(modifier->longPointIsHover_);
}

/**
 * @tc.name: UpdateDilatePaintProperty001
 * @tc.desc: play long point animation
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, UpdateDilatePaintProperty001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Default value
     */
    CreateWithItem([](SwiperModelNG model) {});
    auto totalCount = pattern_->TotalCount();
    EXPECT_EQ(totalCount, 4);

    RefPtr<DotIndicatorModifier> modifier = AceType::MakeRefPtr<DotIndicatorModifier>();
    /**
     * @tc.steps: step2. Calling the UpdateDilatePaintProperty interface
     * @tc.expected: modifier->longPointLeftAnimEnd_ && modifier->longPointRightAnimEnd_ Condition is true
     */
    LinearVector<float> vectorBlackPointCenterX;
    vectorBlackPointCenterX.push_back(20.0f);
    vectorBlackPointCenterX.push_back(20.0f);

    LinearVector<float> normalItemHalfSizes;
    normalItemHalfSizes.emplace_back(20.f);
    normalItemHalfSizes.emplace_back(20.f);

    const std::pair<float, float> longPointCenterX = { 0.0f, 0.0f };

    modifier->longPointLeftAnimEnd_ = true;
    modifier->longPointRightAnimEnd_ = false;
    modifier->UpdateDilatePaintProperty(normalItemHalfSizes, vectorBlackPointCenterX, longPointCenterX);
    EXPECT_FALSE(modifier->longPointLeftAnimEnd_ && modifier->longPointRightAnimEnd_);

    modifier->longPointLeftAnimEnd_ = true;
    modifier->longPointRightAnimEnd_ = true;
    modifier->UpdateDilatePaintProperty(normalItemHalfSizes, vectorBlackPointCenterX, longPointCenterX);
    EXPECT_TRUE(modifier->longPointLeftAnimEnd_ && modifier->longPointRightAnimEnd_);

    modifier->longPointLeftAnimEnd_ = false;
    modifier->longPointRightAnimEnd_ = false;
    modifier->UpdateDilatePaintProperty(normalItemHalfSizes, vectorBlackPointCenterX, longPointCenterX);
    EXPECT_FALSE(modifier->longPointLeftAnimEnd_ && modifier->longPointRightAnimEnd_);

    modifier->longPointLeftAnimEnd_ = false;
    modifier->longPointRightAnimEnd_ = true;
    modifier->UpdateDilatePaintProperty(normalItemHalfSizes, vectorBlackPointCenterX, longPointCenterX);
    EXPECT_FALSE(modifier->longPointLeftAnimEnd_ && modifier->longPointRightAnimEnd_);
}

/**
 * @tc.name: UpdateShrinkPaintProperty002
 * @tc.desc: play long point animation
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, UpdateShrinkPaintProperty002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Default value
     */
    CreateWithItem([](SwiperModelNG model) {});
    auto totalCount = pattern_->TotalCount();
    EXPECT_EQ(totalCount, 4);

    RefPtr<DotIndicatorModifier> modifier = AceType::MakeRefPtr<DotIndicatorModifier>();
    /**
     * @tc.steps: step2. Calling the UpdateShrinkPaintProperty interface
     * @tc.expected: Modifier ->longPointLeftAnimEnd_&& Modifier ->longPointRightAnimEnd_ Condition is false
     */
    LinearVector<float> vectorBlackPointCenterX;
    vectorBlackPointCenterX.push_back(20.0f);
    vectorBlackPointCenterX.push_back(20.0f);

    LinearVector<float> normalItemHalfSizes;
    normalItemHalfSizes.emplace_back(20.f);
    normalItemHalfSizes.emplace_back(20.f);

    const std::pair<float, float> longPointCenterX = { 0.0f, 0.0f };
    auto offset = OffsetF(0.1f, 0.2f);

    modifier->longPointLeftAnimEnd_ = true;
    modifier->longPointRightAnimEnd_ = false;
    modifier->UpdateShrinkPaintProperty(offset, normalItemHalfSizes, vectorBlackPointCenterX, longPointCenterX);
    EXPECT_FALSE(modifier->longPointLeftAnimEnd_ && modifier->longPointRightAnimEnd_);

    modifier->longPointLeftAnimEnd_ = true;
    modifier->longPointRightAnimEnd_ = true;
    modifier->UpdateShrinkPaintProperty(offset, normalItemHalfSizes, vectorBlackPointCenterX, longPointCenterX);
    EXPECT_TRUE(modifier->longPointLeftAnimEnd_ && modifier->longPointRightAnimEnd_);

    modifier->longPointLeftAnimEnd_ = false;
    modifier->longPointRightAnimEnd_ = true;
    modifier->UpdateShrinkPaintProperty(offset, normalItemHalfSizes, vectorBlackPointCenterX, longPointCenterX);
    EXPECT_FALSE(modifier->longPointLeftAnimEnd_ && modifier->longPointRightAnimEnd_);

    modifier->longPointLeftAnimEnd_ = false;
    modifier->longPointRightAnimEnd_ = false;
    modifier->UpdateShrinkPaintProperty(offset, normalItemHalfSizes, vectorBlackPointCenterX, longPointCenterX);
    EXPECT_FALSE(modifier->longPointLeftAnimEnd_ && modifier->longPointRightAnimEnd_);
}

/**
 * @tc.name: PaintUnselectedIndicator001
 * @tc.desc: play long point animation
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, PaintUnselectedIndicator001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Default value
     */
    CreateWithItem([](SwiperModelNG model) {});
    auto totalCount = pattern_->TotalCount();
    EXPECT_EQ(totalCount, 4);

    RefPtr<DotIndicatorModifier> modifier = AceType::MakeRefPtr<DotIndicatorModifier>();
    /**
     * @tc.steps: step2. Calling the PaintUnselectedIndicator interface
     * @tc.expected: modifier->isCustomSize_ is false
     */
    LinearVector<float> itemHalfSizes;
    itemHalfSizes.push_back(20.0f);
    itemHalfSizes.push_back(20.0f);

    RSCanvas canvas;
    auto offset = OffsetF(0.1f, 0.2f);
    bool currentIndexFlag = false;
    modifier->isCustomSize_ = false;
    modifier->PaintUnselectedIndicator(
        canvas, offset, itemHalfSizes, currentIndexFlag, LinearColor(Color::TRANSPARENT));
    EXPECT_TRUE(modifier->isCustomSize_ == false);

    currentIndexFlag = true;
    modifier->isCustomSize_ = true;
    modifier->PaintUnselectedIndicator(
        canvas, offset, itemHalfSizes, currentIndexFlag, LinearColor(Color::TRANSPARENT));
    EXPECT_TRUE(currentIndexFlag == true);

    currentIndexFlag = true;
    modifier->isCustomSize_ = false;
    modifier->PaintUnselectedIndicator(
        canvas, offset, itemHalfSizes, currentIndexFlag, LinearColor(Color::TRANSPARENT));
    EXPECT_TRUE(currentIndexFlag);
}

/**
 * @tc.name: GetLongPointAnimationStateSecondCenter002
 * @tc.desc: Test DotIndicatorPaintMethod UpdateContentModifier
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, GetLongPointAnimationStateSecondCenter002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Default value
     */
    CreateWithItem([](SwiperModelNG model) {
        model.SetDirection(Axis::VERTICAL);
    });

    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto paintProperty = AceType::MakeRefPtr<DotIndicatorPaintProperty>();
    paintProperty->Clone();
    paintProperty->Reset();
    paintProperty->UpdateColor(Color::RED);
    auto renderContext = frameNode_->GetRenderContext();
    PaintWrapper paintWrapper(renderContext, geometryNode, paintProperty);

    LinearVector<float> longPointCenterX;
    longPointCenterX.push_back(20.0f);
    longPointCenterX.push_back(20.0f);

    auto indicatorNode = GetChildFrameNode(frameNode_, 4);
    RefPtr<DotIndicatorModifier> modifier = AceType::MakeRefPtr<DotIndicatorModifier>();
    RefPtr<DotIndicatorPaintMethod> paintMethod = AceType::MakeRefPtr<DotIndicatorPaintMethod>(modifier);

    paintMethod->gestureState_ = GestureState::GESTURE_STATE_RELEASE_LEFT;
    paintMethod->UpdateNormalIndicator(longPointCenterX, &paintWrapper);
    EXPECT_TRUE(paintMethod->gestureState_ == GestureState::GESTURE_STATE_RELEASE_LEFT);

    paintMethod->gestureState_ = GestureState::GESTURE_STATE_RELEASE_RIGHT;
    paintMethod->UpdateNormalIndicator(longPointCenterX, &paintWrapper);
    EXPECT_TRUE(paintMethod->gestureState_ == GestureState::GESTURE_STATE_RELEASE_RIGHT);
}

/**
 * @tc.name: SwiperIndicatorPaintHoverIndicator003
 * @tc.desc: Test DotIndicatorPaintMethod SwiperIndicatorPaintHoverIndicator
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperIndicatorPaintHoverIndicator003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Default value
     */
    CreateWithItem([](SwiperModelNG model) {
        model.SetDirection(Axis::VERTICAL);
    });
    auto indicatorNode = GetChildFrameNode(frameNode_, 4);
    RefPtr<DotIndicatorModifier> modifier = AceType::MakeRefPtr<DotIndicatorModifier>();
    RefPtr<DotIndicatorPaintMethod> paintMethod = AceType::MakeRefPtr<DotIndicatorPaintMethod>(modifier);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto paintProperty = AceType::MakeRefPtr<DotIndicatorPaintProperty>();
    paintProperty->Clone();
    paintProperty->Reset();
    paintProperty->UpdateColor(Color::RED);
    auto renderContext = frameNode_->GetRenderContext();
    PaintWrapper paintWrapper(renderContext, geometryNode, paintProperty);
    paintMethod->hoverIndex_ = 10;
    paintMethod->currentIndex_ = 10;
    paintMethod->mouseClickIndex_ = 5;
    ASSERT_NE(paintMethod->dotIndicatorModifier_, nullptr);
    paintMethod->dotIndicatorModifier_->SetNormalToHoverIndex(5);
    paintMethod->dotIndicatorModifier_->SetIsPressed(true);

    /**
     * @tc.steps: step2. call PaintHoverIndicator.
     * @tc.expected: dotIndicatorModifier_->GetIsPressed is false.
     */
    paintMethod->mouseClickIndex_ = 100;
    paintMethod->PaintHoverIndicator(&paintWrapper);
    EXPECT_FALSE(paintMethod->dotIndicatorModifier_->GetIsPressed());
}

/**
 * @tc.name: SwiperIndicatorCalculatePointCenterX002
 * @tc.desc: Test DotIndicatorPaintMethod CalculatePointCenterX
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperIndicatorCalculatePointCenterX002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Default value
     */
    CreateWithItem([](SwiperModelNG model) {
        model.SetDirection(Axis::VERTICAL);
    });
    auto indicatorNode = GetChildFrameNode(frameNode_, 4);
    RefPtr<DotIndicatorModifier> modifier = AceType::MakeRefPtr<DotIndicatorModifier>();
    RefPtr<DotIndicatorPaintMethod> paintMethod = AceType::MakeRefPtr<DotIndicatorPaintMethod>(modifier);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    geometryNode->SetFrameSize(SizeF(720.f, 1136.f));
    auto paintProperty = AceType::MakeRefPtr<DotIndicatorPaintProperty>();
    paintProperty->Clone();
    paintProperty->Reset();
    paintProperty->UpdateItemWidth(Dimension(20.f, DimensionUnit::PX));
    paintProperty->UpdateItemHeight(Dimension(10.f, DimensionUnit::PX));
    paintProperty->UpdateSelectedItemWidth(Dimension(30.f, DimensionUnit::PX));
    paintProperty->UpdateSelectedItemHeight(Dimension(15.f, DimensionUnit::PX));
    LinearVector<float> vectorBlackPointCenterX;
    auto renderContext = frameNode_->GetRenderContext();
    PaintWrapper paintWrapper(renderContext, geometryNode, paintProperty);
    paintMethod->dotIndicatorModifier_->SetIsHover(true);
    ASSERT_NE(paintMethod->dotIndicatorModifier_, nullptr);
    paintMethod->IsCustomSizeValue_ = true;
    /**
     * @tc.steps: step2. call CalculatePointCenterX.
     * @tc.expected: run success
     */
    vectorBlackPointCenterX.push_back(20.0f);
    vectorBlackPointCenterX.push_back(20.0f);
    vectorBlackPointCenterX.push_back(20.0f);
    vectorBlackPointCenterX.push_back(20.0f);
    vectorBlackPointCenterX.push_back(20.0f);
    vectorBlackPointCenterX.push_back(20.0f);
    paintMethod->turnPageRate_ = 110.0f;
    paintMethod->itemCount_ = 100;
    paintMethod->CalculatePointCenterX(vectorBlackPointCenterX, 0.0, 0.0, 0.0, 0);
    paintMethod->turnPageRate_ = 10.0f;
    paintMethod->itemCount_ = 10;
    paintMethod->CalculatePointCenterX(vectorBlackPointCenterX, 0.0, 0.0, 0.0, 0);
    EXPECT_EQ(paintMethod->normalMargin_.GetX(), 0);
    EXPECT_EQ(paintMethod->normalMargin_.GetY(), 0);

    paintMethod->turnPageRate_ = 110.0f;
    paintMethod->IsCustomSizeValue_ = false;
    paintMethod->CalculatePointCenterX(vectorBlackPointCenterX, 0.0, 0.0, 0.0, 0);
    EXPECT_EQ(paintMethod->normalMargin_.GetX(), 0);
    EXPECT_EQ(paintMethod->normalMargin_.GetY(), 0);
}

/**
 * @tc.name: GetMoveRate001
 * @tc.desc: Test DotIndicatorPaintMethod CalculatePointCenterX
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, GetMoveRate001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Default value
     */
    CreateWithItem([](SwiperModelNG model) {
        model.SetDirection(Axis::VERTICAL);
    });
    auto indicatorNode = GetChildFrameNode(frameNode_, 4);
    RefPtr<DotIndicatorModifier> modifier = AceType::MakeRefPtr<DotIndicatorModifier>();
    RefPtr<DotIndicatorPaintMethod> paintMethod = AceType::MakeRefPtr<DotIndicatorPaintMethod>(modifier);

    /**
     * @tc.steps: step2. Calling the GetMoveRate interface
     * @tc.expected: GestureState_ 5. After accepting, read the value of std:: get<2>(gestureState_5),
     * which is equal to std:: abs (paintMethod ->turnPageRate2)
     */
    paintMethod->gestureState_ = GestureState::GESTURE_STATE_FOLLOW_RIGHT;
    auto gestureState_5 = paintMethod->GetMoveRate();
    EXPECT_TRUE(std::get<2>(gestureState_5) == std::abs(paintMethod->turnPageRate_));

    paintMethod->gestureState_ = GestureState::GESTURE_STATE_FOLLOW_LEFT;
    auto gestureState_4 = paintMethod->GetMoveRate();
    EXPECT_TRUE(
        std::get<2>(gestureState_4) == std::abs(paintMethod->turnPageRate_) + (1 - std::get<1>(gestureState_4)) * 0.5);

    paintMethod->touchBottomTypeLoop_ = TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_RIGHT;
    auto gestureState_3 = paintMethod->GetMoveRate();
    EXPECT_TRUE(std::get<1>(gestureState_3) == std::get<2>(gestureState_3));

    paintMethod->touchBottomTypeLoop_ = TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_LEFT;
    auto gestureState_2 = paintMethod->GetMoveRate();
    EXPECT_TRUE(std::get<1>(gestureState_2) == std::get<2>(gestureState_2));

    paintMethod->gestureState_ = GestureState::GESTURE_STATE_RELEASE_LEFT;
    auto gestureState_1 = paintMethod->GetMoveRate();
    EXPECT_TRUE(std::get<0>(gestureState_1) == 1);

    paintMethod->gestureState_ = GestureState::GESTURE_STATE_RELEASE_RIGHT;
    auto gestureState = paintMethod->GetMoveRate();
    EXPECT_TRUE(std::get<0>(gestureState) == 1);

    paintMethod->isPressed_ = true;
    paintMethod->touchBottomTypeLoop_ = TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_NONE;
    paintMethod->GetMoveRate();
    EXPECT_TRUE(paintMethod->isPressed_ &&
                paintMethod->touchBottomTypeLoop_ == TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_NONE);
}

/**
 * @tc.name: AdjustCurrentIndexOnSwipePage001
 * @tc.desc: Test SwiperPattern AdjustCurrentIndexOnSwipePage
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternAdjustCurrentIndexOnSwipePage001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    auto totalCount = pattern_->TotalCount();
    EXPECT_EQ(totalCount, 4);

    layoutProperty_->UpdateSwipeByGroup(true);
    layoutProperty_->UpdateDisplayCount(3);
    pattern_->needAdjustIndex_ = true;
    layoutProperty_->UpdateIndex(1);
    pattern_->BeforeCreateLayoutWrapper();
    EXPECT_EQ(layoutProperty_->GetIndex().value(), 0);
    EXPECT_FALSE(pattern_->needAdjustIndex_);

    layoutProperty_->UpdateIndex(5);
    pattern_->BeforeCreateLayoutWrapper();
    EXPECT_EQ(layoutProperty_->GetIndex().value(), 0);

    layoutProperty_->UpdateIndex(6);
    pattern_->needAdjustIndex_ = true;
    pattern_->BeforeCreateLayoutWrapper();
    EXPECT_EQ(layoutProperty_->GetIndex().value(), 0);

    layoutProperty_->UpdateIndex(3);
    pattern_->needAdjustIndex_ = true;
    pattern_->BeforeCreateLayoutWrapper();
    EXPECT_EQ(layoutProperty_->GetIndex().value(), 3);

    layoutProperty_->UpdateDisplayCount(6);
    layoutProperty_->UpdateIndex(3);
    pattern_->needAdjustIndex_ = true;
    pattern_->BeforeCreateLayoutWrapper();
    EXPECT_EQ(layoutProperty_->GetIndex().value(), 0);
}

/**
 * @tc.name: ComputeSwipePageNextIndex001
 * @tc.desc: Test SwiperPattern ComputeSwipePageNextIndex
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternComputeSwipePageNextIndex001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    auto totalCount = pattern_->TotalCount();
    EXPECT_EQ(totalCount, 4);

    layoutProperty_->UpdateSwipeByGroup(true);
    layoutProperty_->UpdateDisplayCount(3);
    layoutProperty_->UpdateLoop(true);
    pattern_->currentIndex_ = 3;
    float dragVelocity = 500.0f;
    pattern_->contentMainSize_ = 0.0f;
    EXPECT_EQ(pattern_->ComputeSwipePageNextIndex(dragVelocity), 3);

    pattern_->contentMainSize_ = 500.0f;
    EXPECT_EQ(pattern_->ComputeSwipePageNextIndex(dragVelocity), 3);

    struct SwiperItemInfo swiperItemInfo1;
    swiperItemInfo1.startPos = -200.0f;
    swiperItemInfo1.endPos = 0.0f;
    pattern_->itemPosition_.emplace(std::make_pair(3, swiperItemInfo1));
    struct SwiperItemInfo swiperItemInfo2;
    swiperItemInfo2.startPos = 0.0f;
    swiperItemInfo2.endPos = 200.0f;
    pattern_->itemPosition_.emplace(std::make_pair(4, swiperItemInfo2));
    struct SwiperItemInfo swiperItemInfo3;
    swiperItemInfo3.startPos = 200.0f;
    swiperItemInfo3.endPos = 400.0f;
    pattern_->itemPosition_.emplace(std::make_pair(5, swiperItemInfo3));
    pattern_->contentMainSize_ = 600.0f;
    dragVelocity = -500.0f;
    EXPECT_EQ(pattern_->ComputeSwipePageNextIndex(dragVelocity), 3);

    dragVelocity = -781.0f;
    EXPECT_EQ(pattern_->ComputeSwipePageNextIndex(dragVelocity), 3);

    pattern_->itemPosition_.clear();
    swiperItemInfo1.startPos = -301.0f;
    swiperItemInfo1.endPos = -101.0f;
    pattern_->itemPosition_.emplace(std::make_pair(3, swiperItemInfo1));
    swiperItemInfo2.startPos = -101.0f;
    swiperItemInfo2.endPos = 99.0f;
    pattern_->itemPosition_.emplace(std::make_pair(4, swiperItemInfo2));
    swiperItemInfo3.startPos = 99.0f;
    swiperItemInfo3.endPos = 299.0f;
    pattern_->itemPosition_.emplace(std::make_pair(5, swiperItemInfo3));
    dragVelocity = -500.0f;
    EXPECT_EQ(pattern_->ComputeSwipePageNextIndex(dragVelocity), 6);

    dragVelocity = -781.0f;
    EXPECT_EQ(pattern_->ComputeSwipePageNextIndex(dragVelocity), 6);

    pattern_->itemPosition_.clear();
    swiperItemInfo1.startPos = -200.0f;
    swiperItemInfo1.endPos = 0.0f;
    pattern_->itemPosition_.emplace(std::make_pair(3, swiperItemInfo1));
    swiperItemInfo2.startPos = 0.0f;
    swiperItemInfo2.endPos = 200.0f;
    pattern_->itemPosition_.emplace(std::make_pair(4, swiperItemInfo2));
    swiperItemInfo3.startPos = 200.0f;
    swiperItemInfo3.endPos = 400.0f;
    pattern_->itemPosition_.emplace(std::make_pair(5, swiperItemInfo3));
    dragVelocity = -781.0f;
    EXPECT_EQ(pattern_->ComputeSwipePageNextIndex(dragVelocity), 6);

    layoutProperty_->UpdateLoop(false);
    pattern_->currentIndex_ = 0;
    dragVelocity = 500.0f;
    EXPECT_EQ(pattern_->ComputeSwipePageNextIndex(dragVelocity), 0);

    pattern_->currentIndex_ = 3;
    dragVelocity = -500.0f;
    EXPECT_EQ(pattern_->ComputeSwipePageNextIndex(dragVelocity), 3);
}

/**
 * @tc.name: SwipeByGroupShowNext001
 * @tc.desc: Test SwiperPattern ShowNext On SwipeByGroup
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternSwipeByGroupShowNext001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    auto totalCount = pattern_->TotalCount();
    EXPECT_EQ(totalCount, 4);

    layoutProperty_->UpdateSwipeByGroup(true);
    layoutProperty_->UpdateDisplayCount(3);
    layoutProperty_->UpdateLoop(true);
    pattern_->currentIndex_ = 0;
    pattern_->isVisible_ = true;
    pattern_->ShowNext();
    EXPECT_EQ(pattern_->targetIndex_.value_or(0), 3);
}

/**
 * @tc.name: SwipeByGroupShowPrevious001
 * @tc.desc: Test SwiperPattern ShowPrevious On SwipeByGroup
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternSwipeByGroupShowPrevious001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    auto totalCount = pattern_->TotalCount();
    EXPECT_EQ(totalCount, 4);

    layoutProperty_->UpdateSwipeByGroup(true);
    layoutProperty_->UpdateDisplayCount(3);
    layoutProperty_->UpdateLoop(true);
    pattern_->currentIndex_ = 0;
    pattern_->isVisible_ = true;
    pattern_->ShowPrevious();
    EXPECT_EQ(pattern_->targetIndex_.value_or(0), -3);
}

/**
 * @tc.name: SwiperPatternChangeIndex001
 * @tc.desc: ChangeIndex
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternChangeIndex001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});

    pattern_->ChangeIndex(1, false);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetCurrentShownIndex(), 1);
}

/**
 * @tc.name: SwiperPatternChangeIndex002
 * @tc.desc: ChangeIndex
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternChangeIndex002, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});

    pattern_->ChangeIndex(1, true);
    EXPECT_EQ(pattern_->targetIndex_.value_or(0), 1);
}

/**
 * @tc.name: SwiperPatternChangeIndex003
 * @tc.desc: ChangeIndex
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternChangeIndex003, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    auto totalCount = pattern_->TotalCount();
    EXPECT_EQ(totalCount, 4);

    pattern_->ChangeIndex(4, false);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetCurrentShownIndex(), 0);
}

/**
 * @tc.name: SwiperPatternSwipeByGroupChangeIndex001
 * @tc.desc: Test SwiperPattern ChangeIndex On SwipeByGroup
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwiperPatternSwipeByGroupChangeIndex001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    auto totalCount = pattern_->TotalCount();
    EXPECT_EQ(totalCount, 4);

    layoutProperty_->UpdateSwipeByGroup(true);
    layoutProperty_->UpdateDisplayCount(2);
    layoutProperty_->UpdateLoop(true);
    pattern_->currentIndex_ = 0;
    pattern_->isVisible_ = true;
    pattern_->ChangeIndex(3, true);
    EXPECT_EQ(pattern_->targetIndex_.value_or(0), 2);
}

void SwiperTestNg::InitCaptureTest()
{
    CreateWithItem([](SwiperModelNG model) {});
    layoutProperty_->UpdateDisplayMode(SwiperDisplayMode::STRETCH);
    layoutProperty_->UpdateLoop(true);
    layoutProperty_->UpdateDisplayCount(3);
    layoutProperty_->UpdatePrevMargin(Dimension(CAPTURE_MARGIN_SIZE));
    layoutProperty_->UpdateNextMargin(Dimension(CAPTURE_MARGIN_SIZE));
    pattern_->OnModifyDone();
    EXPECT_TRUE(pattern_->hasCachedCapture_);
}

/**
 * @tc.name: SwipeInitCapture001
 * @tc.desc: Test SwiperPattern InitCapture
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwipeInitCapture001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create swiper witch need the capture
     */
    InitCaptureTest();
    EXPECT_TRUE(pattern_->leftCaptureId_.has_value());
    EXPECT_TRUE(pattern_->rightCaptureId_.has_value());

    layoutProperty_->UpdatePrevMargin(Dimension(0));
    layoutProperty_->UpdateNextMargin(Dimension(CAPTURE_MARGIN_SIZE));
    EXPECT_TRUE(pattern_->hasCachedCapture_);

    layoutProperty_->UpdatePrevMargin(Dimension(CAPTURE_MARGIN_SIZE));
    layoutProperty_->UpdateNextMargin(Dimension(0));
    EXPECT_TRUE(pattern_->hasCachedCapture_);
    /**
     * @tc.steps: step2. Create swiper witch does not need the capture
     */
    layoutProperty_->UpdateDisplayMode(SwiperDisplayMode::AUTO_LINEAR);
    layoutProperty_->ResetDisplayCount();
    pattern_->OnModifyDone();
    EXPECT_FALSE(pattern_->hasCachedCapture_);
    EXPECT_FALSE(pattern_->leftCaptureId_.has_value());
    EXPECT_FALSE(pattern_->rightCaptureId_.has_value());

    layoutProperty_->UpdateDisplayMode(SwiperDisplayMode::STRETCH);
    layoutProperty_->UpdateDisplayCount(3);
    layoutProperty_->UpdateLoop(false);
    pattern_->OnModifyDone();
    EXPECT_FALSE(pattern_->hasCachedCapture_);

    layoutProperty_->UpdateLoop(true);
    layoutProperty_->UpdateDisplayCount(4);
    pattern_->OnModifyDone();
    EXPECT_FALSE(pattern_->hasCachedCapture_);

    layoutProperty_->UpdateDisplayCount(3);
    layoutProperty_->UpdatePrevMargin(Dimension(0));
    layoutProperty_->UpdateNextMargin(Dimension(0));
    pattern_->OnModifyDone();
    EXPECT_FALSE(pattern_->hasCachedCapture_);
}

/**
 * @tc.name: SwipeCaptureLayoutInfo001
 * @tc.desc: Test check measure and layout info
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwipeCaptureLayoutInfo001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create swiper witch need the capture
     */
    InitCaptureTest();
    /**
     * @tc.steps: step2. check layout info with Axis::VERTICAL
     */
    layoutProperty_->UpdateDirection(Axis::VERTICAL);
    pattern_->OnModifyDone();
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->leftCaptureIndex_, 3);
    auto leftCaptureNode = AceType::DynamicCast<FrameNode>(
        frameNode_->GetChildAtIndex(frameNode_->GetChildIndexById(pattern_->GetLeftCaptureId())));
    EXPECT_NE(leftCaptureNode, nullptr);
    if (leftCaptureNode) {
        auto size = leftCaptureNode->GetGeometryNode()->GetFrameRect();
        EXPECT_EQ(size.Width(), SWIPER_WIDTH);
        EXPECT_EQ(size.Height(), (SWIPER_HEIGHT - CAPTURE_MARGIN_SIZE * 2) / 3);
        auto offset = leftCaptureNode->GetGeometryNode()->GetFrameOffset();
        EXPECT_EQ(offset.GetX(), 0.0f);
        EXPECT_EQ(offset.GetY(), CAPTURE_MARGIN_SIZE - size.Height());
    }
    /**
     * @tc.steps: step3. check layout info with Axis::HORIZONTAL
     * 3'|3' 0 1 2 3|3
     */
    layoutProperty_->UpdateDirection(Axis::HORIZONTAL);
    pattern_->OnModifyDone();
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->leftCaptureIndex_, 3);
    leftCaptureNode = AceType::DynamicCast<FrameNode>(
        frameNode_->GetChildAtIndex(frameNode_->GetChildIndexById(pattern_->GetLeftCaptureId())));
    EXPECT_NE(leftCaptureNode, nullptr);
    float itemWidth = 0.0f;
    if (leftCaptureNode) {
        auto size = leftCaptureNode->GetGeometryNode()->GetFrameRect();
        EXPECT_EQ(size.Width(), (SWIPER_WIDTH - CAPTURE_MARGIN_SIZE * 2) / 3);
        EXPECT_EQ(size.Height(), SWIPER_HEIGHT);
        itemWidth = size.Width();
        auto offset = leftCaptureNode->GetGeometryNode()->GetFrameOffset();
        EXPECT_EQ(offset.GetX(), CAPTURE_MARGIN_SIZE - size.Width());
        EXPECT_EQ(offset.GetY(), 0.0f);
    }

    /**
     * @tc.steps: step4. capture in left, delta swipe to right
     * 3'|3' 0 1 2 3|3 to 2'|2' 3 0 1 2|2
     */
    pattern_->currentDelta_ = -itemWidth;
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->leftCaptureIndex_, 2);
    leftCaptureNode = AceType::DynamicCast<FrameNode>(
        frameNode_->GetChildAtIndex(frameNode_->GetChildIndexById(pattern_->GetLeftCaptureId())));
    EXPECT_NE(leftCaptureNode, nullptr);
    if (leftCaptureNode) {
        auto size = leftCaptureNode->GetGeometryNode()->GetFrameRect();
        auto offset = leftCaptureNode->GetGeometryNode()->GetFrameOffset();
        EXPECT_EQ(offset.GetX(), CAPTURE_MARGIN_SIZE - size.Width());
    }

    /**
     * @tc.steps: step5. capture in left, delta swipe to left
     * 2'|2' 3 0 1 2|2 to 3|3 0 1 2 3'|3'
     */
    pattern_->currentDelta_ = itemWidth;
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->rightCaptureIndex_, 3);
    auto rightCaptureNode = AceType::DynamicCast<FrameNode>(
        frameNode_->GetChildAtIndex(frameNode_->GetChildIndexById(pattern_->GetRightCaptureId())));
    EXPECT_NE(rightCaptureNode, nullptr);
    if (rightCaptureNode) {
        auto size = rightCaptureNode->GetGeometryNode()->GetFrameRect();
        EXPECT_EQ(size.Width(), (SWIPER_WIDTH - CAPTURE_MARGIN_SIZE * 2) / 3);
        EXPECT_EQ(size.Height(), SWIPER_HEIGHT);
        auto offset = rightCaptureNode->GetGeometryNode()->GetFrameOffset();
        EXPECT_EQ(offset.GetX(), SWIPER_WIDTH - CAPTURE_MARGIN_SIZE);
        EXPECT_EQ(offset.GetY(), 0.0f);
    }

    /**
     * @tc.steps: step6. capture in right, delta swipe to left
     * 3|3 0 1 2 3'|3' to 0|0 1 2 3 0'|0'
     */
    pattern_->currentDelta_ = itemWidth;
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->rightCaptureIndex_, 0);
    rightCaptureNode = AceType::DynamicCast<FrameNode>(
        frameNode_->GetChildAtIndex(frameNode_->GetChildIndexById(pattern_->GetRightCaptureId())));
    EXPECT_NE(rightCaptureNode, nullptr);
    if (rightCaptureNode) {
        auto offset = rightCaptureNode->GetGeometryNode()->GetFrameOffset();
        EXPECT_EQ(offset.GetX(), SWIPER_WIDTH - CAPTURE_MARGIN_SIZE);
    }

    /**
     * @tc.steps: step7. capture in right, delta swipe to right
     * 0|0 1 2 3 0'|0' to 3'|3' 0 1 2 3|3
     */
    pattern_->currentDelta_ = -itemWidth;
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->leftCaptureIndex_, 3);
    leftCaptureNode = AceType::DynamicCast<FrameNode>(
        frameNode_->GetChildAtIndex(frameNode_->GetChildIndexById(pattern_->GetLeftCaptureId())));
    EXPECT_NE(leftCaptureNode, nullptr);
    if (leftCaptureNode) {
        auto size = leftCaptureNode->GetGeometryNode()->GetFrameRect();
        auto offset = leftCaptureNode->GetGeometryNode()->GetFrameOffset();
        EXPECT_EQ(offset.GetX(), CAPTURE_MARGIN_SIZE - size.Width());
    }
}

/**
 * @tc.name: SwipeCaptureLayoutInfo002
 * @tc.desc: Test check itemPosition map info
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwipeCaptureLayoutInfo002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create swiper witch need the capture
     */
    InitCaptureTest();
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    FlushLayoutTask(frameNode_);
    /**
     * @tc.steps: step2. capture in left, target index change to equal to first item index in itemPosition
     * current index 0, target index to 0, 3'|3' 0 1 2 3|3 to 3'|3' 0 1 2 3|3
     */
    pattern_->targetIndex_ = 0;
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->leftCaptureIndex_, 3);
    auto leftCaptureNode = AceType::DynamicCast<FrameNode>(
        frameNode_->GetChildAtIndex(frameNode_->GetChildIndexById(pattern_->GetLeftCaptureId())));
    EXPECT_NE(leftCaptureNode, nullptr);
    if (leftCaptureNode) {
        auto size = leftCaptureNode->GetGeometryNode()->GetFrameRect();
        auto offset = leftCaptureNode->GetGeometryNode()->GetFrameOffset();
        EXPECT_EQ(offset.GetX(), CAPTURE_MARGIN_SIZE - size.Width());
    }
    /**
     * @tc.steps: step3. capture in left, target index change to smaller than first item index in itemPosition
     * current index 0, target index to -1, 3'|3' 0 1 2 3|3 to 3|3 0 1 2 3'|3'
     */
    pattern_->targetIndex_ = -1;
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    FlushLayoutTask(frameNode_);
    // isCaptureReverse_ change to true
    EXPECT_TRUE(pattern_->isCaptureReverse_);
    EXPECT_EQ(pattern_->leftCaptureIndex_, 3);
    auto rightCaptureNode = AceType::DynamicCast<FrameNode>(
        frameNode_->GetChildAtIndex(frameNode_->GetChildIndexById(pattern_->GetRightCaptureId())));
    EXPECT_NE(rightCaptureNode, nullptr);
    if (rightCaptureNode) {
        auto offset = leftCaptureNode->GetGeometryNode()->GetFrameOffset();
        EXPECT_EQ(offset.GetX(), SWIPER_WIDTH - CAPTURE_MARGIN_SIZE);
    }
    /**
     * @tc.steps: step4. capture in left, target index change to larger than first item index in itemPosition
     * current index 0, target index to 1, 3|3 0 1 2 3'|3' to 3'|3' 0 1 2 3|3
     */
    pattern_->targetIndex_ = 1;
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    FlushLayoutTask(frameNode_);
    // isCaptureReverse_ change to true
    EXPECT_FALSE(pattern_->isCaptureReverse_);
    EXPECT_EQ(pattern_->leftCaptureIndex_, 3);
    leftCaptureNode = AceType::DynamicCast<FrameNode>(
        frameNode_->GetChildAtIndex(frameNode_->GetChildIndexById(pattern_->GetLeftCaptureId())));
    EXPECT_NE(leftCaptureNode, nullptr);
    if (leftCaptureNode) {
        auto size = leftCaptureNode->GetGeometryNode()->GetFrameRect();
        auto offset = leftCaptureNode->GetGeometryNode()->GetFrameOffset();
        EXPECT_EQ(offset.GetX(), CAPTURE_MARGIN_SIZE - size.Width());
    }
}

void SwiperTestNg::CreateWithCustomAnimation()
{
    CreateWithItem([](SwiperModelNG model) {
        SwiperContentAnimatedTransition transitionInfo;
        transitionInfo.timeout = 0;
        transitionInfo.transition = [](const RefPtr<SwiperContentTransitionProxy>& proxy) {};
        model.SetCustomContentTransition(transitionInfo);

        auto onContentDidScroll = [](int32_t selectedIndex, int32_t index, float position, float mainAxisLength) {};
        model.SetOnContentDidScroll(std::move(onContentDidScroll));
    });
    pattern_->contentMainSize_ = SWIPER_WIDTH;
    EXPECT_TRUE(pattern_->SupportSwiperCustomAnimation());
}

/**
 * @tc.name: SwipeCustomAnimationTest001
 * @tc.desc: Test check itemPositionInAnimation map info
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwipeCustomAnimationTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create swiper and set SetCustomContentTransition interface
     */
    CreateWithCustomAnimation();

    /**
     * @tc.steps: step2. set loop to true, displayCount to 2 and swipeByGroup to true, init itemPosition map info.
     */
    layoutProperty_->UpdateLoop(true);
    layoutProperty_->UpdateDisplayCount(2);
    layoutProperty_->UpdateSwipeByGroup(true);

    struct SwiperItemInfo swiperItemInfo1;
    struct SwiperItemInfo swiperItemInfo2;
    swiperItemInfo1.startPos = 0.0f;
    swiperItemInfo1.endPos = SWIPER_WIDTH / 2;
    swiperItemInfo2.startPos = SWIPER_WIDTH / 2;
    swiperItemInfo2.endPos = SWIPER_WIDTH;
    pattern_->itemPosition_.clear();
    pattern_->itemPosition_.emplace(std::make_pair(0, swiperItemInfo1));
    pattern_->itemPosition_.emplace(std::make_pair(1, swiperItemInfo2));

    /**
     * @tc.steps: step3. set different offset, calculate and update itemPositionInAnimation info.
     */
    auto offset1 = -10.0f;
    pattern_->HandleSwiperCustomAnimation(offset1);
    EXPECT_FALSE(pattern_->itemPositionInAnimation_.find(2) == pattern_->itemPositionInAnimation_.end());
    EXPECT_FALSE(pattern_->itemPositionInAnimation_.find(3) == pattern_->itemPositionInAnimation_.end());
    EXPECT_EQ(pattern_->itemPositionInAnimation_[3].startPos, SWIPER_WIDTH * 3 / 2 + offset1);
    EXPECT_EQ(pattern_->itemPositionInAnimation_[3].endPos, SWIPER_WIDTH * 2 + offset1);
    pattern_->itemPosition_ = pattern_->itemPositionInAnimation_;

    auto offset2 = 20.0f;
    pattern_->HandleSwiperCustomAnimation(offset2);
    EXPECT_FALSE(pattern_->itemPositionInAnimation_.find(2) == pattern_->itemPositionInAnimation_.end());
    EXPECT_FALSE(pattern_->itemPositionInAnimation_.find(3) == pattern_->itemPositionInAnimation_.end());
    EXPECT_EQ(pattern_->itemPositionInAnimation_[2].startPos, offset1 + offset2 - SWIPER_WIDTH);
    EXPECT_EQ(pattern_->itemPositionInAnimation_[2].endPos, offset1 + offset2 - SWIPER_WIDTH / 2);
    pattern_->itemPosition_ = pattern_->itemPositionInAnimation_;

    auto offset3 = -10.0f;
    pattern_->HandleSwiperCustomAnimation(offset3);
    EXPECT_TRUE(pattern_->itemPositionInAnimation_.find(2) == pattern_->itemPositionInAnimation_.end());
    EXPECT_TRUE(pattern_->itemPositionInAnimation_.find(3) == pattern_->itemPositionInAnimation_.end());
    EXPECT_EQ(pattern_->itemPositionInAnimation_[0].startPos, 0.0f);
    EXPECT_EQ(pattern_->itemPositionInAnimation_[0].endPos, SWIPER_WIDTH / 2);
}

/**
 * @tc.name: SwipeCustomAnimationTest002
 * @tc.desc: Test check itemPositionInAnimation map info
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwipeCustomAnimationTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create swiper and set SetCustomContentTransition interface
     */
    CreateWithCustomAnimation();

    /**
     * @tc.steps: step2. set loop to true, itemSpace to 10, prevMargin to 20, nextMargin to 30,
     * init itemPosition map info.
     */
    layoutProperty_->UpdateLoop(true);
    auto itemSpace = 10.0f;
    auto prevMargin = 20.0f;
    auto nextMargin = 30.0f;
    layoutProperty_->UpdateItemSpace(Dimension(itemSpace));
    layoutProperty_->UpdatePrevMargin(Dimension(prevMargin));
    layoutProperty_->UpdateNextMargin(Dimension(nextMargin));

    auto mainAxisLength = SWIPER_WIDTH - prevMargin - nextMargin - itemSpace * 2;
    struct SwiperItemInfo swiperItemInfo1;
    struct SwiperItemInfo swiperItemInfo2;
    struct SwiperItemInfo swiperItemInfo3;
    swiperItemInfo1.startPos = - mainAxisLength - itemSpace;
    swiperItemInfo1.endPos = - itemSpace;
    swiperItemInfo2.startPos = 0.0f;
    swiperItemInfo2.endPos = mainAxisLength;
    swiperItemInfo3.startPos = mainAxisLength + itemSpace;
    swiperItemInfo3.endPos = mainAxisLength * 2 + itemSpace;
    pattern_->itemPosition_.clear();
    pattern_->itemPosition_.emplace(std::make_pair(3, swiperItemInfo1));
    pattern_->itemPosition_.emplace(std::make_pair(0, swiperItemInfo2));
    pattern_->itemPosition_.emplace(std::make_pair(1, swiperItemInfo3));

    /**
     * @tc.steps: step3. set different offset, calculate and update itemPositionInAnimation info.
     */
    auto offset1 = -400.0f;
    pattern_->HandleSwiperCustomAnimation(offset1);
    EXPECT_TRUE(pattern_->itemPositionInAnimation_.find(3) == pattern_->itemPositionInAnimation_.end());
    EXPECT_FALSE(pattern_->itemPositionInAnimation_.find(2) == pattern_->itemPositionInAnimation_.end());
    EXPECT_EQ(pattern_->itemPositionInAnimation_[2].startPos, mainAxisLength * 2 + itemSpace * 2 + offset1);
    EXPECT_EQ(pattern_->itemPositionInAnimation_[2].endPos, mainAxisLength * 3 + itemSpace * 2 + offset1);
    pattern_->itemPosition_ = pattern_->itemPositionInAnimation_;

    auto offset2 = 500.0f;
    pattern_->HandleSwiperCustomAnimation(offset2);
    EXPECT_TRUE(pattern_->itemPositionInAnimation_.find(1) == pattern_->itemPositionInAnimation_.end());
    EXPECT_TRUE(pattern_->itemPositionInAnimation_.find(2) == pattern_->itemPositionInAnimation_.end());
    EXPECT_FALSE(pattern_->itemPositionInAnimation_.find(3) == pattern_->itemPositionInAnimation_.end());
    EXPECT_EQ(pattern_->itemPositionInAnimation_.find(3)->second.startPos,
        - itemSpace - mainAxisLength + offset1 + offset2);
    EXPECT_EQ(pattern_->itemPositionInAnimation_.find(3)->second.endPos, - itemSpace + offset1 + offset2);
}

/**
 * @tc.name: SwipeCustomAnimationTest003
 * @tc.desc: Test check itemPositionInAnimation map info
 * @tc.type: FUNC
 */
HWTEST_F(SwiperTestNg, SwipeCustomAnimationTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create swiper and set SetCustomContentTransition interface
     */
    CreateWithCustomAnimation();

    /**
     * @tc.steps: step2. set loop to false, isDragging to true, init itemPosition map info.
     */
    layoutProperty_->UpdateLoop(false);
    pattern_->isDragging_ = true;

    struct SwiperItemInfo swiperItemInfo1;
    swiperItemInfo1.startPos = 0.0f;
    swiperItemInfo1.endPos = SWIPER_WIDTH;
    pattern_->itemPosition_.clear();
    pattern_->itemPosition_.emplace(std::make_pair(0, swiperItemInfo1));

    /**
     * @tc.steps: step3. set different offset in fade edge effect, calculate and update itemPositionInAnimation info.
     */
    frameNode_->GetPaintProperty<SwiperPaintProperty>()->UpdateEdgeEffect(EdgeEffect::FADE);

    auto offset1 = -10.0f;
    pattern_->UpdateCurrentOffset(offset1);
    EXPECT_EQ(pattern_->itemPositionInAnimation_[0].startPos, offset1);
    EXPECT_EQ(pattern_->itemPositionInAnimation_[0].endPos, SWIPER_WIDTH + offset1);
    pattern_->itemPosition_ = pattern_->itemPositionInAnimation_;

    auto offset2 = 20.0f;
    pattern_->UpdateCurrentOffset(offset2);
    EXPECT_EQ(pattern_->itemPositionInAnimation_[0].startPos, 0.0f);
    EXPECT_EQ(pattern_->itemPositionInAnimation_[0].endPos, SWIPER_WIDTH);
    pattern_->itemPosition_ = pattern_->itemPositionInAnimation_;

    /**
     * @tc.steps: step4. set different offset without edge effect, calculate and update itemPositionInAnimation info.
     */
    frameNode_->GetPaintProperty<SwiperPaintProperty>()->UpdateEdgeEffect(EdgeEffect::NONE);

    pattern_->UpdateCurrentOffset(offset1);
    EXPECT_EQ(pattern_->itemPositionInAnimation_[0].startPos, offset1);
    EXPECT_EQ(pattern_->itemPositionInAnimation_[0].endPos, SWIPER_WIDTH + offset1);
    pattern_->itemPosition_ = pattern_->itemPositionInAnimation_;

    pattern_->UpdateCurrentOffset(offset2);
    EXPECT_EQ(pattern_->itemPositionInAnimation_[0].startPos, 0.0f);
    EXPECT_EQ(pattern_->itemPositionInAnimation_[0].endPos, SWIPER_WIDTH);
    pattern_->itemPosition_ = pattern_->itemPositionInAnimation_;

    /**
     * @tc.steps: step5. set different offset in spring edge effect, calculate and update itemPositionInAnimation info.
     */
    frameNode_->GetPaintProperty<SwiperPaintProperty>()->UpdateEdgeEffect(EdgeEffect::SPRING);

    pattern_->UpdateCurrentOffset(offset1);
    EXPECT_EQ(pattern_->itemPositionInAnimation_[0].startPos, offset1);
    EXPECT_EQ(pattern_->itemPositionInAnimation_[0].endPos, SWIPER_WIDTH + offset1);
    pattern_->itemPosition_ = pattern_->itemPositionInAnimation_;

    pattern_->UpdateCurrentOffset(offset2);
    EXPECT_EQ(pattern_->itemPositionInAnimation_[0].startPos, offset1 + offset2);
    EXPECT_EQ(pattern_->itemPositionInAnimation_[0].endPos, SWIPER_WIDTH + offset1 + offset2);
}
} // namespace OHOS::Ace::NG
