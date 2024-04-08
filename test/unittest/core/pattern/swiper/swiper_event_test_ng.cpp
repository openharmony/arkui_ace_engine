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

#include "swiper_test_ng.h"

namespace OHOS::Ace::NG {

namespace {} // namespace

class SwiperEventTestNg : public SwiperTestNg {
public:
    void HandleDrag(GestureEvent info);
};

void SwiperEventTestNg::HandleDrag(GestureEvent info)
{
    auto HandleDragStart = pattern_->panEvent_->GetActionStartEventFunc();
    auto HandleDragUpdate = pattern_->panEvent_->GetActionUpdateEventFunc();
    auto HandleDragEnd = pattern_->panEvent_->GetActionEndEventFunc();
    HandleDragStart(info);
    HandleDragUpdate(info);
    HandleDragEnd(info);
    FlushLayoutTask(frameNode_);
}

/**
 * @tc.name: HandleDrag001
 * @tc.desc: HandleDrag with AXIS and MOUSE, will trigger ShowPrevious or ShowNext
 * @tc.type: FUNC
 */
HWTEST_F(SwiperEventTestNg, HandleDrag001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    GestureEvent info;
    info.SetInputEventType(InputEventType::AXIS);
    info.SetSourceTool(SourceTool::MOUSE);

    /**
     * @tc.steps: step1. SetMainDelta > 0
     * @tc.expected: Trigger ShowPrevious
     */
    info.SetMainDelta(10.f);
    HandleDrag(info);
    EXPECT_EQ(pattern_->GetCurrentIndex(), 3);

    /**
     * @tc.steps: step2. SetMainDelta < 0
     * @tc.expected: Trigger ShowNext
     */
    info.SetMainDelta(-10.f);
    HandleDrag(info);
    EXPECT_EQ(pattern_->GetCurrentIndex(), 0);

    /**
     * @tc.steps: step2. SetMainDelta == 0
     * @tc.expected: CurrentIndex not changed
     */
    info.SetMainDelta(0.f);
    HandleDrag(info);
    EXPECT_EQ(pattern_->GetCurrentIndex(), 0);
}

/**
 * @tc.name: SwiperEvent001
 * @tc.desc: HandleTouchDown
 * @tc.type: FUNC
 */
HWTEST_F(SwiperEventTestNg, SwiperEvent001, TestSize.Level1)
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
HWTEST_F(SwiperEventTestNg, SwiperEvent002, TestSize.Level1)
{
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
 * @tc.name: SwiperPatternHandleTouchEvent002
 * @tc.desc: HandleTouchDown
 * @tc.type: FUNC
 */
HWTEST_F(SwiperEventTestNg, SwiperPatternHandleTouchEvent002, TestSize.Level1)
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
 * @tc.name: ButtonTouchEvent001
 * @tc.desc: Test ButtonTouchEvent
 * @tc.type: FUNC
 */
HWTEST_F(SwiperEventTestNg, ButtonTouchEvent001, TestSize.Level1)
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
HWTEST_F(SwiperEventTestNg, SwiperArrowPatternButtonClickEvent001, TestSize.Level2)
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
 * @tc.name: SwiperPatternTriggerEventOnFinish001
 * @tc.desc: TriggerEventOnFinish
 * @tc.type: FUNC
 */
HWTEST_F(SwiperEventTestNg, SwiperPatternTriggerEventOnFinish001, TestSize.Level1)
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
 * @tc.name: SwiperPatternHandleMouseEvent001
 * @tc.desc: HandleMouseEvent
 * @tc.type: FUNC
 */
HWTEST_F(SwiperEventTestNg, SwiperPatternHandleMouseEvent001, TestSize.Level1)
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
 * @tc.name: PanEvent001
 * @tc.desc: PanEvent
 * @tc.type: FUNC
 */
HWTEST_F(SwiperEventTestNg, PanEvent001, TestSize.Level1)
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
HWTEST_F(SwiperEventTestNg, PanEvent002, TestSize.Level1)
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
 * @tc.name: SwiperPatternInitPanEvent001
 * @tc.desc: Test InitPanEvent
 * @tc.type: FUNC
 */
HWTEST_F(SwiperEventTestNg, SwiperPatternInitPanEvent001, TestSize.Level1)
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
 * @tc.name: SwiperPatternInitHoverMouseEvent001
 * @tc.desc: InitHoverMouseEvent
 * @tc.type: FUNC
 */
HWTEST_F(SwiperEventTestNg, SwiperPatternInitHoverMouseEvent001, TestSize.Level1)
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
 * @tc.name: SwiperPatternHandleTouchUp003
 * @tc.desc: HandleTouchUp
 * @tc.type: FUNC
 */
HWTEST_F(SwiperEventTestNg, SwiperPatternHandleTouchUp003, TestSize.Level1)
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
 * @tc.name: SwiperPatternHandleDragEnd006
 * @tc.desc: HandleDragEnd
 * @tc.type: FUNC
 */
HWTEST_F(SwiperEventTestNg, SwiperPatternHandleDragEnd006, TestSize.Level1)
{
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
 * @tc.name: SwiperPatternHandleTouchUp001
 * @tc.desc: HandleTouchUp
 * @tc.type: FUNC
 */
HWTEST_F(SwiperEventTestNg, SwiperPatternHandleTouchUp001, TestSize.Level1)
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
 * @tc.name: SwiperPatternHandleDragEnd001
 * @tc.desc: HandleDragEnd
 * @tc.type: FUNC
 */
HWTEST_F(SwiperEventTestNg, SwiperPatternHandleDragEnd001, TestSize.Level1)
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
 * @tc.name: SwiperPatternHandleDragUpdate001
 * @tc.desc: HandleDragUpdate
 * @tc.type: FUNC
 */
HWTEST_F(SwiperEventTestNg, SwiperPatternHandleDragUpdate001, TestSize.Level1)
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
HWTEST_F(SwiperEventTestNg, SwiperPatternHandleDragUpdate002, TestSize.Level1)
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
 * @tc.name: SwiperPatternHandleDragEnd002
 * @tc.desc: HandleDragEnd
 * @tc.type: FUNC
 */
HWTEST_F(SwiperEventTestNg, SwiperPatternHandleDragEnd002, TestSize.Level1)
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
 * @tc.name: SwiperPatternHandleTouchDown001
 * @tc.desc: HandleTouchDown
 * @tc.type: FUNC
 */
HWTEST_F(SwiperEventTestNg, SwiperPatternHandleTouchDown001, TestSize.Level1)
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
 * @tc.name: SwiperPatternHandleTouchUp002
 * @tc.desc: HandleTouchUp
 * @tc.type: FUNC
 */
HWTEST_F(SwiperEventTestNg, SwiperPatternHandleTouchUp002, TestSize.Level1)
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
 * @tc.name: SwiperPatternHandleDragEnd003
 * @tc.desc: HandleDragEnd
 * @tc.type: FUNC
 */
HWTEST_F(SwiperEventTestNg, SwiperPatternHandleDragEnd003, TestSize.Level1)
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
 * @tc.name: SwiperPatternHandleScroll001
 * @tc.desc: test HandleScroll SELF_ONLY
 * @tc.type: FUNC
 */
HWTEST_F(SwiperEventTestNg, SwiperPatternHandleScroll001, TestSize.Level1)
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
HWTEST_F(SwiperEventTestNg, SwiperPatternHandleScroll002, TestSize.Level1)
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
HWTEST_F(SwiperEventTestNg, SwiperPatternHandleScroll003, TestSize.Level1)
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
HWTEST_F(SwiperEventTestNg, SwiperPatternHandleScroll004, TestSize.Level1)
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
HWTEST_F(SwiperEventTestNg, SwiperPatternHandleScroll005, TestSize.Level1)
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
HWTEST_F(SwiperEventTestNg, SwiperPatternHandleScroll006, TestSize.Level1)
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
HWTEST_F(SwiperEventTestNg, SwiperPatternHandleScroll007, TestSize.Level1)
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
HWTEST_F(SwiperEventTestNg, SwiperPatternHandleScroll008, TestSize.Level1)
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
HWTEST_F(SwiperEventTestNg, SwiperPatternHandleScrollVelocity001, TestSize.Level1)
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
HWTEST_F(SwiperEventTestNg, SwiperPatternHandleScrollVelocity002, TestSize.Level1)
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
HWTEST_F(SwiperEventTestNg, SwiperPatternHandleScrollVelocity003, TestSize.Level1)
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
 * @tc.name: HandleTouchBottomLoop001
 * @tc.desc: test Swiper indicator no touch bottom in loop
 * @tc.type: FUNC
 */
HWTEST_F(SwiperEventTestNg, HandleTouchBottomLoop001, TestSize.Level1)
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
HWTEST_F(SwiperEventTestNg, HandleTouchBottomLoop002, TestSize.Level1)
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
HWTEST_F(SwiperEventTestNg, HandleTouchBottomLoop003, TestSize.Level1)
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
 * @tc.name: SwiperFunc004
 * @tc.desc: HandleDragUpdate
 * @tc.type: FUNC
 */
HWTEST_F(SwiperEventTestNg, SwiperFunc004, TestSize.Level1)
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
 * @tc.name: SwiperInit001
 * @tc.desc: InitIndicator
 * @tc.type: FUNC
 */
HWTEST_F(SwiperEventTestNg, SwiperInit001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    EXPECT_EQ(frameNode_->children_.size(), 5);
}

/**
 * @tc.name: SwiperInit002
 * @tc.desc: InitOnKeyEvent
 * @tc.type: FUNC
 */
HWTEST_F(SwiperEventTestNg, SwiperInit002, TestSize.Level1)
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
HWTEST_F(SwiperEventTestNg, SwiperFunc001, TestSize.Level1)
{
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
HWTEST_F(SwiperEventTestNg, SwiperFunc002, TestSize.Level1)
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
HWTEST_F(SwiperEventTestNg, SwiperFunc003, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {});
    EXPECT_EQ(pattern_->TotalCount(), 4);
}

/**
 * @tc.name: SwiperPatternOnIndexChange001
 * @tc.desc: OnIndexChange
 * @tc.type: FUNC
 */
HWTEST_F(SwiperEventTestNg, SwiperPatternOnIndexChange001, TestSize.Level1)
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
 * @tc.name: SwiperPatternOnVisibleChange001
 * @tc.desc: OnVisibleChange
 * @tc.type: FUNC
 */
HWTEST_F(SwiperEventTestNg, SwiperPatternOnVisibleChange001, TestSize.Level1)
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
 * @tc.name: SwiperPatternOnScrollStart001
 * @tc.desc: test OnScrollStartRecursive
 * @tc.type: FUNC
 */
HWTEST_F(SwiperEventTestNg, SwiperPatternOnScrollStart001, TestSize.Level1)
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
HWTEST_F(SwiperEventTestNg, SwiperPatternOnScrollEnd001, TestSize.Level1)
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
} // namespace OHOS::Ace::NG
