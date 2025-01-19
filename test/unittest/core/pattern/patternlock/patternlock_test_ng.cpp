/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#include "patternlock_test_ng.h"

void PatternLockTestNg::SetUpTestSuite()
{
    TestNG::SetUpTestSuite();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto themeConstants = CreateThemeConstants(THEME_PATTERN_SCROLL_BAR);
    auto scrollBarTheme = ScrollBarTheme::Builder().Build(themeConstants);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(scrollBarTheme));
    auto patternLockThemeConstants = CreateThemeConstants(THEME_PATTERN_PATTERN_LOCK);
    auto patternLockTheme = V2::PatternLockTheme::Builder().Build(patternLockThemeConstants);
    EXPECT_CALL(*themeManager, GetTheme(V2::PatternLockTheme::TypeId())).WillRepeatedly(Return(patternLockTheme));
    MockPipelineContext::GetCurrentContext()->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
}

void PatternLockTestNg::TearDownTestSuite()
{
    TestNG::TearDownTestSuite();
}

void PatternLockTestNg::SetUp() {}

void PatternLockTestNg::TearDown()
{
    frameNode_ = nullptr;
    pattern_ = nullptr;
    eventHub_ = nullptr;
    layoutProperty_ = nullptr;
    paintProperty_ = nullptr;
}

void PatternLockTestNg::GetInstance()
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    frameNode_ = AceType::DynamicCast<FrameNode>(element);
    pattern_ = frameNode_->GetPattern<PatternLockPattern>();
    eventHub_ = frameNode_->GetEventHub<PatternLockEventHub>();
    layoutProperty_ = frameNode_->GetLayoutProperty<PatternLockLayoutProperty>();
    paintProperty_ = frameNode_->GetPaintProperty<PatternLockPaintProperty>();
}

void PatternLockTestNg::Create(const std::function<void(PatternLockModelNG)>& callback)
{
    PatternLockModelNG model;
    model.Create();
    ViewAbstract::SetWidth(CalcLength(PATTERNLOCK_WIDTH));
    ViewAbstract::SetHeight(CalcLength(PATTERNLOCK_HEIGHT));
    if (callback) {
        callback(model);
    }
    GetInstance();
    FlushLayoutTask(frameNode_);
}

/**
 * @tc.name: PaintProperty001
 * @tc.desc: Set PatternLock value into PatternLockPaintProperty and get it.
 * @tc.type: FUNC
 */
HWTEST_F(PatternLockTestNg, PaintProperty001, TestSize.Level1)
{
    Create([](PatternLockModelNG model) {
        model.SetCircleRadius(CIRCLE_RADIUS);
        model.SetRegularColor(REGULAR_COLOR);
        model.SetSelectedColor(SELECTED_COLOR);
        model.SetActiveColor(ACTIVE_COLOR);
        model.SetPathColor(PATH_COLOR);
        model.SetStrokeWidth(PATH_STROKE_WIDTH);
        model.SetAutoReset(true);
        model.SetSideLength(SIDE_LENGTH);
        model.SetActiveCircleColor(ACTIVE_CIRCLE_COLOR);
        model.SetActiveCircleRadius(ACTIVE_CIRCLE_RADIUS);
        model.SetEnableWaveEffect(false);
    });
    EXPECT_EQ(paintProperty_->GetCircleRadiusValue(), CIRCLE_RADIUS);
    EXPECT_EQ(paintProperty_->GetRegularColorValue(), REGULAR_COLOR);
    EXPECT_EQ(paintProperty_->GetSelectedColorValue(), SELECTED_COLOR);
    EXPECT_EQ(paintProperty_->GetActiveColorValue(), ACTIVE_COLOR);
    EXPECT_EQ(paintProperty_->GetPathColorValue(), PATH_COLOR);
    EXPECT_EQ(paintProperty_->GetPathStrokeWidthValue(), PATH_STROKE_WIDTH);
    EXPECT_TRUE(paintProperty_->GetAutoResetValue());
    EXPECT_EQ(layoutProperty_->GetSideLength(), SIDE_LENGTH);
    EXPECT_EQ(paintProperty_->GetActiveCircleColorValue(), ACTIVE_CIRCLE_COLOR);
    EXPECT_EQ(paintProperty_->GetActiveCircleRadiusValue(), ACTIVE_CIRCLE_RADIUS);
    EXPECT_FALSE(paintProperty_->GetEnableWaveEffectValue());
}

/**
 * @tc.name: PatternLockEventTest001
 * @tc.desc: Test PatternLock onComplete event.
 * @tc.type: FUNC
 */
HWTEST_F(PatternLockTestNg, PatternLockEventTest001, TestSize.Level1)
{
    std::vector<int> chooseCellVec;
    std::vector<int> afterComplete;
    chooseCellVec.push_back(1);
    chooseCellVec.push_back(2);
    chooseCellVec.push_back(3);
    chooseCellVec.push_back(4);
    chooseCellVec.push_back(5);
    chooseCellVec.push_back(6);
    auto patternCompleteEvent = V2::PatternCompleteEvent(chooseCellVec);
    auto onComplete = [&afterComplete](const BaseEventInfo* completeResult) {
        const auto* eventInfo = TypeInfoHelper::DynamicCast<V2::PatternCompleteEvent>(completeResult);
        afterComplete = eventInfo->GetInput();
    };
    Create([onComplete](PatternLockModelNG model) {
        model.SetPatternComplete(onComplete);
    });

    /**
     * @tc.steps: step1. Get event hub and call UpdateCompleteEvent function
     */
    eventHub_->UpdateCompleteEvent(&patternCompleteEvent);
    EXPECT_FALSE(afterComplete.empty());
    EXPECT_EQ(afterComplete.back(), 6);
    afterComplete.pop_back();
    EXPECT_EQ(afterComplete.back(), 5);
    afterComplete.pop_back();
    EXPECT_EQ(afterComplete.back(), 4);
    afterComplete.pop_back();
    EXPECT_EQ(afterComplete.back(), 3);
    afterComplete.pop_back();
    EXPECT_EQ(afterComplete.back(), 2);
    afterComplete.pop_back();
    EXPECT_EQ(afterComplete.back(), 1);
}

/**
 * @tc.name: PatternLockEventTest002
 * @tc.desc: Test PatternLock onDotConnect event.
 * @tc.type: FUNC
 */
HWTEST_F(PatternLockTestNg, PatternLockEventTest002, TestSize.Level1)
{
    int32_t connectedDot = -1;
    auto onDotConnect = [&connectedDot](int32_t currentIndex) { connectedDot = currentIndex; };
    Create([onDotConnect](PatternLockModelNG model) {
        model.SetDotConnect(onDotConnect);
    });

    /**
     * @tc.steps: step1. Get event hub and call UpdateDotConnectEvent function
     */
    eventHub_->UpdateDotConnectEvent(1);
    EXPECT_EQ(connectedDot, 1);
}

/**
 * @tc.name: PatternLockPatternTest001
 * @tc.desc: Test PatternLock pattern method HandleReset.
 * @tc.type: FUNC
 */
HWTEST_F(PatternLockTestNg, PatternLockPatternTest001, TestSize.Level1)
{
    Create([](PatternLockModelNG model) {});
    pattern_->patternLockModifier_ = AceType::MakeRefPtr<PatternLockModifier>();

    /**
     * @tc.steps: step3. Set PatternLock pattern variable and call HandleReset
     * @tc.expected: step3. Check the PatternLock pattern variable
     */
    pattern_->isMoveEventValid_ = true;
    pattern_->choosePoint_.push_back(PatternLockCell(1, 2));
    pattern_->cellCenter_ = OffsetF(1.0, 1.0);
    pattern_->HandleReset();
    EXPECT_FALSE(pattern_->isMoveEventValid_);
    EXPECT_TRUE(pattern_->choosePoint_.empty());
    EXPECT_EQ(pattern_->cellCenter_, OffsetF(0, 0));

    /**
     * @tc.steps: step4. PatternLock Init PatternLockController.
     */
    pattern_->InitPatternLockController();
    ASSERT_NE(pattern_->patternLockController_->resetImpl_, nullptr);
    pattern_->patternLockController_->resetImpl_();
    EXPECT_FALSE(pattern_->isMoveEventValid_);
    EXPECT_TRUE(pattern_->choosePoint_.empty());
    EXPECT_EQ(pattern_->cellCenter_, OffsetF(0, 0));
}

/**
 * @tc.name: PatternLockPatternTest002
 * @tc.desc: Test PatternLock pattern method CheckAutoReset.
 * @tc.type: FUNC
 */
HWTEST_F(PatternLockTestNg, PatternLockPatternTest002, TestSize.Level1)
{
    Create([](PatternLockModelNG model) {
        model.SetAutoReset(true);
    });

    /**
     * @tc.steps: step1. Set PatternLock pattern variable and call CheckAutoReset
     * @tc.expected: step1. Check the return value of PatternLock pattern method CheckAutoReset
     */
    bool result1 = pattern_->CheckAutoReset();
    EXPECT_TRUE(pattern_->autoReset_);
    EXPECT_TRUE(result1);
    auto paintProperty_ = frameNode_->GetPaintProperty<PatternLockPaintProperty>();
    paintProperty_->Reset();
    bool result2 = pattern_->CheckAutoReset();
    EXPECT_TRUE(result2);
    pattern_->autoReset_ = false;
    pattern_->choosePoint_ = { PatternLockCell(1, 2) };
    pattern_->isMoveEventValid_ = false;
    bool result3 = pattern_->CheckAutoReset();
    EXPECT_FALSE(result3);
}

/**
 * @tc.name: PatternLockPatternTest003
 * @tc.desc: Test PatternLock pattern method AddPassPoint.
 * @tc.type: FUNC
 */
HWTEST_F(PatternLockTestNg, PatternLockPatternTest003, TestSize.Level1)
{
    Create([](PatternLockModelNG model) {});
    pattern_->patternLockModifier_ = AceType::MakeRefPtr<PatternLockModifier>();

    /**
     * @tc.case: case1: choosePoint_ vec is empty.
     */
    pattern_->AddPassPoint(1, 2);
    EXPECT_TRUE(pattern_->choosePoint_.empty());
    /**
     * @tc.case: case2: choosePoint_ vec is not empty.
     */
    pattern_->choosePoint_.push_back(PatternLockCell(1, 1));
    pattern_->AddPassPoint(1, 2);
    EXPECT_EQ(pattern_->choosePoint_.back().GetRow(), 1);
    EXPECT_EQ(pattern_->choosePoint_.back().GetColumn(), 1);
    /**
     * @tc.case: case3: lastPoint(1, 2), add Point(2, 2), no passPoint.
     */
    pattern_->choosePoint_.clear();
    pattern_->choosePoint_.push_back(PatternLockCell(1, 2));
    pattern_->AddPassPoint(2, 2);
    EXPECT_EQ(pattern_->choosePoint_.back().GetRow(), 2);
    EXPECT_EQ(pattern_->choosePoint_.back().GetColumn(), 1);
    /**
     * @tc.case: case4: lastPoint(0, 2), add Point(2, 2), passPoint(1, 2)
     */
    pattern_->choosePoint_.clear();
    pattern_->choosePoint_.push_back(PatternLockCell(0, 2));
    pattern_->AddPassPoint(2, 2);
    EXPECT_EQ(pattern_->choosePoint_.back().GetColumn(), 1);
    EXPECT_EQ(pattern_->choosePoint_.back().GetRow(), 2);
    EXPECT_EQ(pattern_->choosePoint_.size(), 2);
    /**
     * @tc.case: case5: lastPoint(2, 2), add Point(0, 0), passPoint(1, 1)
     */
    pattern_->choosePoint_.clear();
    pattern_->choosePoint_.push_back(PatternLockCell(2, 2));
    pattern_->AddPassPoint(0, 0);
    EXPECT_EQ(pattern_->choosePoint_.back().GetColumn(), 1);
    EXPECT_EQ(pattern_->choosePoint_.back().GetRow(), 1);
    EXPECT_EQ(pattern_->choosePoint_.size(), 2);
}

/**
 * @tc.name: PatternLockPatternTest004
 * @tc.desc: Test PatternLock pattern method CheckChoosePoint.
 * @tc.type: FUNC
 */
HWTEST_F(PatternLockTestNg, PatternLockPatternTest004, TestSize.Level1)
{
    Create([](PatternLockModelNG model) {});

    /**
     * @tc.steps: step1. Set PatternLock pattern variable and call CheckChoosePoint
     * @tc.expected: step1. Check the return value of PatternLock pattern method CheckChoosePoint
     */
    pattern_->choosePoint_.push_back(PatternLockCell(1, 1));
    pattern_->choosePoint_.push_back(PatternLockCell(1, 2));
    auto result1 = pattern_->CheckChoosePoint(1, 2);
    EXPECT_TRUE(result1);
    auto result2 = pattern_->CheckChoosePoint(2, 2);
    EXPECT_FALSE(result2);
}

/**
 * @tc.name: PatternLockPatternTest005
 * @tc.desc: Test PatternLock pattern method AddChoosePoint.
 * @tc.type: FUNC
 */
HWTEST_F(PatternLockTestNg, PatternLockPatternTest005, TestSize.Level1)
{
    Create([](PatternLockModelNG model) {});

    frameNode_->GetGeometryNode()->SetContentSize(SizeF(300.0f, 300.0f));
    pattern_->patternLockModifier_ = AceType::MakeRefPtr<PatternLockModifier>();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto patternlockTheme = AceType::MakeRefPtr<V2::PatternLockTheme>();
    patternlockTheme->hotSpotCircleRadius_ = HOTSPOT_CIRCLE_RADIUS;
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(patternlockTheme));

    /**
     * @tc.cases: when distance is unvalid, Point(x, y) will not AddChoosePoint.
     */
    float offsetX = 75.0f;
    float offsetY = 75.0f;
    OffsetF offset(offsetX, offsetY);
    bool result1 = pattern_->AddChoosePoint(offset, 1, 1);
    EXPECT_FALSE(result1);
    auto paintProperty_ = frameNode_->GetPaintProperty<PatternLockPaintProperty>();
    paintProperty_->UpdateCircleRadius(CIRCLE_RADIUS);
    bool result2 = pattern_->AddChoosePoint(offset, 1, 1);
    EXPECT_FALSE(result2);

    /**
     * @tc.cases: when distance is valid, Point(x, y) will AddChoosePoint.
     */
    paintProperty_->UpdateCircleRadius(Dimension(200.0));
    EXPECT_EQ(pattern_->choosePoint_.size(), 0);
    EXPECT_FALSE(pattern_->CheckChoosePoint(1, 1));
    bool result3 = pattern_->AddChoosePoint(offset, 1, 1);
    EXPECT_EQ(pattern_->choosePoint_.size(), 1);
    EXPECT_TRUE(result3);

    EXPECT_TRUE(pattern_->CheckChoosePoint(1, 1));
    bool result4 = pattern_->AddChoosePoint(offset, 1, 1);
    EXPECT_EQ(pattern_->choosePoint_.size(), 1);
    EXPECT_TRUE(result4);

    EXPECT_EQ(frameNode_->GetGeometryNode()->GetFrameSize(), SizeF(400.f, 400.f));
    offsetX = 200.f;
    offsetY = 200.f;
    offset.SetX(offsetX);
    offset.SetY(offsetY);
    EXPECT_FALSE(pattern_->CheckChoosePoint(2, 2));
    bool result5 = pattern_->AddChoosePoint(offset, 2, 2);
    EXPECT_EQ(pattern_->choosePoint_.size(), 2);
    EXPECT_TRUE(result5);
}

/**
 * @tc.name: PatternLockPatternTest006
 * @tc.desc: Test PatternLock pattern method OnTouchUp.
 * @tc.type: FUNC
 */
HWTEST_F(PatternLockTestNg, PatternLockPatternTest006, TestSize.Level1)
{
    Create([](PatternLockModelNG model) {});
    pattern_->patternLockModifier_ = AceType::MakeRefPtr<PatternLockModifier>();

    /**
     * @tc.steps: step3. Set PatternLock pattern variable and call OnTouchUp
     * @tc.expected: step3. Check the PatternLock pattern value
     */
    pattern_->autoReset_ = false;
    pattern_->choosePoint_.push_back(PatternLockCell(1, 1));
    pattern_->patternLockModifier_->choosePoint_.push_back(PatternLockCell(1, 1));
    pattern_->patternLockModifier_->choosePoint_.push_back(PatternLockCell(2, 2));
    pattern_->isMoveEventValid_ = false;
    pattern_->OnTouchUp();
    pattern_->isMoveEventValid_ = true;
    pattern_->OnTouchUp();
    EXPECT_FALSE(pattern_->isMoveEventValid_);
}

/**
 * @tc.name: PatternLockPatternTest007
 * @tc.desc: Test PatternLock pattern method OnTouchMove.
 * @tc.type: FUNC
 */
HWTEST_F(PatternLockTestNg, PatternLockPatternTest007, TestSize.Level1)
{
    Create([](PatternLockModelNG model) {});

    /**
     * @tc.steps: step3. Set PatternLock pattern variable and call OnTouchMove
     * @tc.expected: step3. Check the PatternLock pattern value
     */
    float offsetX = 1.0f;
    float offsetY = 1.0f;
    Offset offset(offsetX, offsetY);
    pattern_->isMoveEventValid_ = false;
    TouchLocationInfo locationInfo(0);
    locationInfo.SetTouchType(TouchType::MOVE);
    locationInfo.SetLocalLocation(offset);
    pattern_->OnTouchMove(locationInfo);
    EXPECT_EQ(pattern_->cellCenter_.GetX(), .0f);
    EXPECT_EQ(pattern_->cellCenter_.GetY(), .0f);
    pattern_->isMoveEventValid_ = true;
    pattern_->OnTouchMove(locationInfo);
    EXPECT_EQ(pattern_->cellCenter_.GetX(), offset.GetX());
    EXPECT_EQ(pattern_->cellCenter_.GetY(), offset.GetY());
}

/**
 * @tc.name: PatternLockPatternTest008
 * @tc.desc: Test PatternLock pattern method OnTouchDown.
 * @tc.type: FUNC
 */
HWTEST_F(PatternLockTestNg, PatternLockPatternTest008, TestSize.Level1)
{
    Create([](PatternLockModelNG model) {});
    pattern_->patternLockModifier_ = AceType::MakeRefPtr<PatternLockModifier>();

    /**
     * @tc.steps: step3. Set PatternLock pattern variable and call OnTouchDown
     * @tc.expected: step3. Check the PatternLock pattern value
     */
    float offsetX = 1.0f;
    float offsetY = 1.0f;
    Offset offset(offsetX, offsetY);
    pattern_->autoReset_ = false;
    pattern_->choosePoint_.push_back(PatternLockCell(1, 1));
    pattern_->isMoveEventValid_ = false;
    TouchLocationInfo locationInfo(0);
    locationInfo.SetLocalLocation(offset);
    pattern_->isMoveEventValid_ = true;
    pattern_->OnTouchDown(locationInfo);
    EXPECT_EQ(pattern_->cellCenter_.GetX(), offset.GetX());
    EXPECT_EQ(pattern_->cellCenter_.GetY(), offset.GetY());
}

/**
 * @tc.name: PatternLockPatternTest009
 * @tc.desc: Test PatternLock pattern method HandleTouchEvent.
 * @tc.type: FUNC
 */
HWTEST_F(PatternLockTestNg, PatternLockPatternTest009, TestSize.Level1)
{
    Create([](PatternLockModelNG model) {});
    pattern_->patternLockModifier_ = AceType::MakeRefPtr<PatternLockModifier>();

    /**
     * @tc.steps: step3. Set PatternLock pattern variable and call HandleTouchEvent
     * @tc.expected: step3. Check the PatternLock pattern value
     */
    float offsetX = 1.0f;
    float offsetY = 1.0f;
    Offset offset(offsetX, offsetY);
    TouchLocationInfo locationInfoTouchDown(0);
    locationInfoTouchDown.SetLocalLocation(offset);
    locationInfoTouchDown.SetTouchType(TouchType::DOWN);
    TouchEventInfo touchEventInfoTouchDown("onTouchDown");
    touchEventInfoTouchDown.AddChangedTouchLocationInfo(std::move(locationInfoTouchDown));
    pattern_->HandleTouchEvent(touchEventInfoTouchDown);
    EXPECT_EQ(pattern_->fingerId_, 0);
    EXPECT_EQ(pattern_->cellCenter_.GetX(), offset.GetX());
    EXPECT_EQ(pattern_->cellCenter_.GetY(), offset.GetY());
    pattern_->cellCenter_.Reset();

    pattern_->isMoveEventValid_ = true;
    TouchLocationInfo locationInfoTouchMove(0);
    locationInfoTouchMove.SetLocalLocation(offset);
    locationInfoTouchMove.SetTouchType(TouchType::MOVE);
    TouchEventInfo touchEventInfoTouchMove("onTouchMove");
    touchEventInfoTouchMove.AddChangedTouchLocationInfo(std::move(locationInfoTouchMove));
    pattern_->HandleTouchEvent(touchEventInfoTouchMove);
    EXPECT_EQ(pattern_->cellCenter_.GetX(), offset.GetX());
    EXPECT_EQ(pattern_->cellCenter_.GetY(), offset.GetY());
    pattern_->cellCenter_.Reset();

    pattern_->isMoveEventValid_ = true;
    TouchLocationInfo locationInfoTouchUp(0);
    locationInfoTouchUp.SetLocalLocation(offset);
    locationInfoTouchUp.SetTouchType(TouchType::UP);
    TouchEventInfo touchEventInfoUp("onTouchUp");
    touchEventInfoUp.AddChangedTouchLocationInfo(std::move(locationInfoTouchUp));
    pattern_->patternLockModifier_->choosePoint_.push_back(PatternLockCell(2, 1));
    pattern_->patternLockModifier_->choosePoint_.push_back(PatternLockCell(2, 2));
    pattern_->HandleTouchEvent(touchEventInfoUp);
    EXPECT_FALSE(pattern_->isMoveEventValid_);
    EXPECT_EQ(pattern_->fingerId_, -1);

    pattern_->isMoveEventValid_ = true;
    TouchLocationInfo locationInfoTouchUnkown(0);
    locationInfoTouchUnkown.SetLocalLocation(offset);
    locationInfoTouchUnkown.SetTouchType(TouchType::UNKNOWN);
    TouchEventInfo touchEventInfoTouchUnkown("onTouchUnkown");
    touchEventInfoTouchUnkown.AddChangedTouchLocationInfo(std::move(locationInfoTouchUnkown));
    pattern_->HandleTouchEvent(touchEventInfoTouchUnkown);
}

/**
 * @tc.name: PatternLockPatternTest010
 * @tc.desc: Test PatternLock pattern method InitTouchEvent.
 * @tc.type: FUNC
 */
HWTEST_F(PatternLockTestNg, PatternLockPatternTest010, TestSize.Level1)
{
    Create([](PatternLockModelNG model) {});

    /**
     * @tc.steps: step3. Set PatternLock pattern variable and call InitTouchEvent
     * @tc.expected: step3. Check the PatternLock pattern value
     */
    auto gestureHub = frameNode_->GetOrCreateGestureEventHub();
    pattern_->InitTouchEvent(gestureHub, pattern_->touchDownListener_);
    ASSERT_NE(pattern_->touchDownListener_, nullptr);
    auto touchEvent = gestureHub->touchEventActuator_->touchEvents_.back();
    ASSERT_NE(touchEvent, nullptr);
    auto info = TouchEventInfo("");
    touchEvent->callback_(info);
    pattern_->InitTouchEvent(gestureHub, pattern_->touchDownListener_);
    EXPECT_EQ(gestureHub->touchEventActuator_->touchEvents_.back(), touchEvent);
}

/**
 * @tc.name: PatternLockPatternTest011
 * @tc.desc: Test PatternLock pattern method HandleFocusEvent, HandleBlurEvent and GetInnerFocusPaintRect.
 * @tc.type: FUNC
 */
HWTEST_F(PatternLockTestNg, PatternLockPatternTest011, TestSize.Level1)
{
    Create([](PatternLockModelNG model) {});

    auto focushub = frameNode_->GetFocusHub();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto patternlockTheme = AceType::MakeRefPtr<V2::PatternLockTheme>();
    patternlockTheme->hotSpotCircleRadius_ = HOTSPOT_CIRCLE_RADIUS;
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(patternlockTheme));
    /**
     * @tc.steps: step3. Set PatternLock pattern variable and Init FocusHub.
     */
    pattern_->isMoveEventValid_ = false;
    pattern_->choosePoint_.push_back(PatternLockCell(1, 2));
    pattern_->cellCenter_ = OffsetF(1.0f, 1.0f);
    pattern_->currentPoint_ = { 0, 0 };
    pattern_->InitFocusEvent();
    /**
     * @tc.steps: step4. Call HandleFocusEvent function.
     */
    ASSERT_NE(focushub->onFocusInternal_, nullptr);
    focushub->onFocusInternal_();
    EXPECT_TRUE(pattern_->isMoveEventValid_);
    EXPECT_TRUE(pattern_->choosePoint_.empty());
    EXPECT_EQ(pattern_->cellCenter_, OffsetF(0.0f, 0.0f));
    EXPECT_EQ(pattern_->currentPoint_, std::make_pair(1, 1));
    /**
     * @tc.steps: step5. Call HandleBlurEvent function.
     */
    ASSERT_NE(focushub->onBlurInternal_, nullptr);
    focushub->onBlurInternal_();
    EXPECT_FALSE(pattern_->isMoveEventValid_);
    /**
     * @tc.steps: step6. Call GetInnerFocusPaintRect function.
     */
    ASSERT_NE(focushub->getInnerFocusRectFunc_, nullptr);
    RoundRect focusRectInner;
    focushub->getInnerFocusRectFunc_(focusRectInner);
    EXPECT_FALSE(focusRectInner.radius_.data_.empty());
}

/**
 * @tc.name: PatternLockPatternTest012
 * @tc.desc: Test PatternLock pattern method HandleFocusEvent, HandleBlurEvent and GetInnerFocusPaintRect.
 * @tc.type: FUNC
 */
HWTEST_F(PatternLockTestNg, PatternLockPatternTest012, TestSize.Level1)
{
    Create([](PatternLockModelNG model) {});
    auto focushub = frameNode_->GetFocusHub();
    pattern_->InitFocusEvent();
    ASSERT_NE(focushub->onKeyEventsInternal_[OnKeyEventType::DEFAULT], nullptr);
    /**
     * @tc.steps: step3. Call OnKeyEvent function.
     */
    auto event = KeyEvent();
    /**
     * @tc.case: case1: KeyAction is UNKNOWN.
     */
    event.action = KeyAction::UNKNOWN;
    EXPECT_FALSE(focushub->onKeyEventsInternal_[OnKeyEventType::DEFAULT](event));
    /**
     * @tc.case: case2: KeyAction is DOWN and KeyCode is KEY_SPACE.
     */
    event.action = KeyAction::DOWN;
    event.code = KeyCode::KEY_SPACE;
    EXPECT_TRUE(pattern_->OnKeyEvent(event));
    /**
     * @tc.case: case3: KeyAction is DOWN, KeyCode is KEY_ENTER and isMoveEventValid_ is true.
     */
    event.code = KeyCode::KEY_ENTER;
    EXPECT_TRUE(pattern_->OnKeyEvent(event));
    /**
     * @tc.case: case4: KeyAction is DOWN, KeyCode is KEY_ENTER and isMoveEventValid_ is false.
     */
    EXPECT_TRUE(pattern_->OnKeyEvent(event));
    /**
     * @tc.case: case5: KeyAction is DOWN, KeyCode is KEY_DPAD_UP and current point is first point.
     */
    event.code = KeyCode::KEY_DPAD_UP;
    pattern_->currentPoint_ = { 1, 1 };
    EXPECT_TRUE(pattern_->OnKeyEvent(event));
    /**
     * @tc.case: case6: KeyAction is DOWN, KeyCode is KEY_DPAD_UP and current point is last point.
     */
    pattern_->currentPoint_ = { 3, 3 };
    EXPECT_TRUE(pattern_->OnKeyEvent(event));
    /**
     * @tc.case: case7: KeyAction is DOWN, KeyCode is KEY_DPAD_DOWN and current point is first point.
     */
    event.code = KeyCode::KEY_DPAD_DOWN;
    pattern_->currentPoint_ = { 1, 1 };
    EXPECT_TRUE(pattern_->OnKeyEvent(event));
    /**
     * @tc.case: case8: KeyAction is DOWN, KeyCode is KEY_DPAD_DOWN and current point is last point.
     */
    pattern_->currentPoint_ = { 3, 3 };
    EXPECT_TRUE(pattern_->OnKeyEvent(event));
    /**
     * @tc.case: case9: KeyAction is DOWN, KeyCode is KEY_DPAD_LEFT and current point is first point.
     */
    event.code = KeyCode::KEY_DPAD_LEFT;
    pattern_->currentPoint_ = { 1, 1 };
    EXPECT_TRUE(pattern_->OnKeyEvent(event));
    /**
     * @tc.case: case10: KeyAction is DOWN, KeyCode is KEY_DPAD_LEFT and current point is last point.
     */
    pattern_->currentPoint_ = { 3, 3 };
    EXPECT_TRUE(pattern_->OnKeyEvent(event));
    /**
     * @tc.case: case11: KeyAction is DOWN, KeyCode is KEY_DPAD_RIGHT and current point is first point.
     */
    event.code = KeyCode::KEY_DPAD_RIGHT;
    pattern_->currentPoint_ = { 1, 1 };
    EXPECT_TRUE(pattern_->OnKeyEvent(event));
    /**
     * @tc.case: case12: KeyAction is DOWN, KeyCode is KEY_DPAD_RIGHT and current point is last point.
     */
    pattern_->currentPoint_ = { 3, 3 };
    EXPECT_TRUE(pattern_->OnKeyEvent(event));
    /**
     * @tc.case: case13: KeyAction is DOWN, KeyCode is KEY_MOVE_HOME and current point is last point.
     */
    event.code = KeyCode::KEY_MOVE_HOME;
    EXPECT_TRUE(pattern_->OnKeyEvent(event));
    /**
     * @tc.case: case14: KeyAction is DOWN, KeyCode is KEY_MOVE_END and current point is first point.
     */
    event.code = KeyCode::KEY_MOVE_END;
    EXPECT_TRUE(pattern_->OnKeyEvent(event));
    /**
     * @tc.case: case15: KeyAction is DOWN and KeyCode is KEY_ESCAPE.
     */
    event.code = KeyCode::KEY_ESCAPE;
    EXPECT_TRUE(pattern_->OnKeyEvent(event));
    /**
     * @tc.case: case16: KeyAction is DOWN and KeyCode is illegal.
     */
    event.code = KeyCode::KEY_FORWARD_DEL;
    EXPECT_FALSE(pattern_->OnKeyEvent(event));
}

/**
 * @tc.name: PatternLockPatternTest013
 * @tc.desc: Test PatternLock pattern OnFocusClick.
 * @tc.type: FUNC
 */
HWTEST_F(PatternLockTestNg, PatternLockPatternTest013, TestSize.Level1)
{
    Create([](PatternLockModelNG model) {});

    /**
     * @tc.case: case1: CheckAutoReset is false.
     */
    pattern_->autoReset_ = false;
    pattern_->choosePoint_ = { PatternLockCell(1, 2) };
    pattern_->isMoveEventValid_ = false;
    EXPECT_FALSE(pattern_->CheckAutoReset());
    pattern_->OnFocusClick();
    EXPECT_FALSE(pattern_->isMoveEventValid_);
    /**
     * @tc.case: case2: CheckAutoReset is true and isMoveEventValid_ is false.
     */
    pattern_->autoReset_ = true;
    pattern_->currentPoint_ = std::make_pair(1, 1);
    pattern_->OnFocusClick();
    EXPECT_TRUE(pattern_->isMoveEventValid_);
    EXPECT_FALSE(pattern_->choosePoint_.empty());
    /**
     * @tc.case: case3: CheckAutoReset is true, isMoveEventValid_ is false current point is checked.
     */
    pattern_->OnFocusClick();
    EXPECT_TRUE(pattern_->isMoveEventValid_);
}

/**
 * @tc.name: PatternLockPatternTest014
 * @tc.desc: Test PatternLock pattern method HandleHoverEvent and HandleMouseEvent.
 * @tc.type: FUNC
 */
HWTEST_F(PatternLockTestNg, PatternLockPatternTest014, TestSize.Level1)
{
    Create([](PatternLockModelNG model) {});

    frameNode_->GetGeometryNode()->SetContentSize(SizeF(CONTENT_SIZE_FLOAT, CONTENT_SIZE_FLOAT));
    frameNode_->GetGeometryNode()->SetContentOffset(OffsetF(CONTENT_OFFSET_FLOAT, CONTENT_OFFSET_FLOAT));
    auto eventHub = frameNode_->GetEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    auto inputEventHub = eventHub->GetOrCreateInputEventHub();
    CHECK_NULL_VOID(inputEventHub);
    pattern_->patternLockModifier_ = AceType::MakeRefPtr<PatternLockModifier>();
    auto paintProperty_ = frameNode_->GetPaintProperty<PatternLockPaintProperty>();
    paintProperty_->UpdateCircleRadius(Dimension(CIRCLE_RADIUS_FLOAT));
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto patternlockTheme = AceType::MakeRefPtr<V2::PatternLockTheme>();
    patternlockTheme->hotSpotCircleRadius_ = HOTSPOT_CIRCLE_RADIUS;
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(patternlockTheme));
    pattern_->InitMouseEvent();
    ASSERT_FALSE(inputEventHub->hoverEventActuator_->inputEvents_.empty());
    ASSERT_FALSE(inputEventHub->mouseEventActuator_->inputEvents_.empty());
    /**
     * @tc.steps: step3. Call HandleHoverEvent function.
     */
    for (const auto& hoverCallback : inputEventHub->hoverEventActuator_->inputEvents_) {
        ASSERT_NE(hoverCallback, nullptr);
        (*hoverCallback)(false);
    }
    EXPECT_FALSE(pattern_->patternLockModifier_->isHover_->Get());
    /**
     * @tc.steps: step4. Call HandleMouseEvent function and hover not on point.
     */
    auto info = MouseInfo();
    info.SetLocalLocation(Offset(0.0f, 0.0f));
    for (const auto& mouseCallback : inputEventHub->mouseEventActuator_->inputEvents_) {
        ASSERT_NE(mouseCallback, nullptr);
        (*mouseCallback)(info);
    }
    EXPECT_EQ(pattern_->patternLockModifier_->hoverIndex_->Get(), -1);
    /**
     * @tc.steps: step5. Call HandleMouseEvent function and hover on point.
     */
    info.SetLocalLocation(Offset(FIRST_POINT_CHECK_FLOAT, FIRST_POINT_CHECK_FLOAT));
    for (const auto& mouseCallback : inputEventHub->mouseEventActuator_->inputEvents_) {
        ASSERT_NE(mouseCallback, nullptr);
        (*mouseCallback)(info);
    }
    EXPECT_EQ(pattern_->patternLockModifier_->hoverIndex_->Get(), 0);
}

/**
 * @tc.name: PatternLockPatternTest015
 * @tc.desc: Test PatternLock pattern method SetChallengeResult.
 * @tc.type: FUNC
 */
HWTEST_F(PatternLockTestNg, PatternLockPatternTest015, TestSize.Level1)
{
    Create([](PatternLockModelNG model) {});
    pattern_->patternLockModifier_ = AceType::MakeRefPtr<PatternLockModifier>();
    ASSERT_NE(pattern_->patternLockController_->setChallengeResultImpl_, nullptr);

    /**
     * @tc.steps: step3. Call SetChallengeResult function and challenge result set CORRECT.
     */
    pattern_->patternLockController_->SetChallengeResult(V2::PatternLockChallengeResult::CORRECT);
    ASSERT_TRUE(pattern_->patternLockModifier_->challengeResult_.has_value());
    EXPECT_EQ(pattern_->patternLockModifier_->challengeResult_.value(), NG::PatternLockChallengeResult::CORRECT);

    /**
     * @tc.steps: step4. Call SetChallengeResult function and challenge result set WRONG.
     */
    pattern_->patternLockController_->SetChallengeResult(V2::PatternLockChallengeResult::WRONG);
    ASSERT_TRUE(pattern_->patternLockModifier_->challengeResult_.has_value());
    EXPECT_EQ(pattern_->patternLockModifier_->challengeResult_.value(), NG::PatternLockChallengeResult::WRONG);

    /**
     * @tc.steps: step5. When isMoveEventValid_ is true call SetChallengeResult function and challenge result set
     * CORRECT.
     */
    EXPECT_EQ(pattern_->patternLockModifier_->challengeResult_, NG::PatternLockChallengeResult::WRONG);
    pattern_->isMoveEventValid_ = true;
    pattern_->patternLockController_->SetChallengeResult(V2::PatternLockChallengeResult::CORRECT);
    ASSERT_TRUE(pattern_->patternLockModifier_->challengeResult_.has_value());
    EXPECT_EQ(pattern_->patternLockModifier_->challengeResult_.value(), NG::PatternLockChallengeResult::WRONG);

    /**
     * @tc.steps: step6. Call SetChallengeResult function and challenge result illegal.
     */
    pattern_->isMoveEventValid_ = false;
    pattern_->patternLockController_->SetChallengeResult(V2::PatternLockChallengeResult(0));
    ASSERT_FALSE(pattern_->patternLockModifier_->challengeResult_.has_value());
}

/**
 * @tc.name: PatternLockPatternTest016
 * @tc.desc: Test PatternLock pattern method CreateNodePaintMethod.
 * @tc.type: FUNC
 */
HWTEST_F(PatternLockTestNg, PatternLockPatternTest016, TestSize.Level1)
{
    Create([](PatternLockModelNG model) {});

    /**
     * @tc.steps: step3. Set PatternLock pattern variables and call CreateNodePaintMethod.
     * @tc.expected: step3. Check the PatternLock paintMethod cellCenter_ value.
     */
    pattern_->screenTouchPoint_ = OffsetF(TOUCHPOINT_OFFSET_FLOAT, TOUCHPOINT_OFFSET_FLOAT);
    auto paintMethod = AceType::DynamicCast<PatternLockPaintMethod>(pattern_->CreateNodePaintMethod());
    EXPECT_EQ(paintMethod->cellCenter_, OffsetF(TOUCHPOINT_OFFSET_FLOAT, TOUCHPOINT_OFFSET_FLOAT));
}

/**
 * @tc.name: PatternLockPatternTest017
 * @tc.desc: Test PatternLock pattern method CalculateCellCenter and GetLastChoosePointOffset.
 * @tc.type: FUNC
 */
HWTEST_F(PatternLockTestNg, PatternLockPatternTest017, TestSize.Level1)
{
    Create([](PatternLockModelNG model) {});

    /**
     * @tc.steps: step3. Set PatternLock pattern variables and call CalculateCellCenter.
     * @tc.expected: step3. Check the PatternLock cellCenter_ value.
     */
    pattern_->screenTouchPoint_ = OffsetF(TOUCHPOINT_OFFSET_FLOAT, TOUCHPOINT_OFFSET_FLOAT);
    pattern_->CalculateCellCenter();
    EXPECT_EQ(pattern_->cellCenter_, OffsetF(TOUCHPOINT_OFFSET_FLOAT, TOUCHPOINT_OFFSET_FLOAT));

    /**
     * @tc.steps: step4. Set PatternLock pattern variables and call CalculateCellCenter.
     * @tc.expected: step4. Check the PatternLock cellCenter_ value is not changed.
     */
    pattern_->cellCenter_ = OffsetF();
    pattern_->isOnKeyEventState_ = true;
    pattern_->CalculateCellCenter();
    EXPECT_EQ(pattern_->cellCenter_, OffsetF());

    /**
     * @tc.steps: step5. Set PatternLock pattern variables and call CalculateCellCenter
     * @tc.expected: step5. Check the PatternLock cellCenter_ value.
     */
    auto geometryNode = frameNode_->GetGeometryNode();
    geometryNode->SetContentSize(SizeF(CONTENT_SIZE_FLOAT, CONTENT_SIZE_FLOAT));
    geometryNode->SetContentOffset(OffsetF(CONTENT_OFFSET_FLOAT, CONTENT_OFFSET_FLOAT));
    pattern_->choosePoint_.push_back(PatternLockCell(1, 1));
    pattern_->CalculateCellCenter();
    auto calculateOffsetResult = CONTENT_OFFSET_FLOAT + CONTENT_SIZE_FLOAT / PATTERN_LOCK_COL_COUNT /
                                                            RADIUS_TO_DIAMETER * (RADIUS_TO_DIAMETER - 1);
    EXPECT_EQ(pattern_->cellCenter_, OffsetF(calculateOffsetResult, calculateOffsetResult));
}

/**
 * @tc.name: PatternLockPatternTest018
 * @tc.desc: Test PatternLock in scrollNode
 * @tc.type: FUNC
 */
HWTEST_F(PatternLockTestNg, PatternLockPatternTest018, TestSize.Level1)
{
    ScrollModelNG model;
    model.Create();
    ViewAbstract::SetWidth(CalcLength(SCROLL_WIDTH));
    ViewAbstract::SetHeight(CalcLength(SCROLL_HEIGHT));
    {
        ColumnModelNG colModel;
        colModel.Create(Dimension(0), nullptr, "");
        ViewAbstract::SetWidth(CalcLength(FILL_LENGTH));
        ViewAbstract::SetHeight(CalcLength(SCROLL_HEIGHT + 100));
        PaddingProperty padding;
        padding.top = CalcLength(100);
        ViewAbstract::SetPadding(padding);
        {
            PatternLockModelNG patternLockModelNG;
            patternLockModelNG.Create();
            ViewAbstract::SetWidth(CalcLength(PATTERNLOCK_WIDTH));
            ViewAbstract::SetHeight(CalcLength(PATTERNLOCK_HEIGHT));
            ViewStackProcessor::GetInstance()->Pop();
        }
        ViewStackProcessor::GetInstance()->Pop();
    }
    auto scrollNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    FlushLayoutTask(scrollNode);

    /**
     * @tc.steps: step1. because colNode padding, patternLockNode offsetY is 100
     */
    auto colNode = GetChildFrameNode(scrollNode, 0);
    auto patternLockNode = GetChildFrameNode(colNode, 0);
    auto scrollPattern = scrollNode->GetPattern<ScrollPattern>();
    auto patternLockPattern = patternLockNode->GetPattern<PatternLockPattern>();
    EXPECT_TRUE(IsEqual(patternLockNode->GetGeometryNode()->GetFrameOffset(), OffsetF(40, 100)));

    /**
     * @tc.steps: step3. Call OnTouchDown
     * @tc.expected: cellCenter_ is equal to locationInfo
     */
    auto mockRenderContext = AceType::DynamicCast<MockRenderContext>(patternLockNode->renderContext_);
    mockRenderContext->rect_ = RectF(40, 100, PATTERNLOCK_WIDTH, PATTERNLOCK_HEIGHT);

    TouchLocationInfo locationInfo(0);
    locationInfo.SetLocalLocation(Offset(200, 200));
    patternLockPattern->OnTouchDown(locationInfo);
    EXPECT_TRUE(IsEqual(patternLockPattern->cellCenter_, OffsetF(200, 200)));

    locationInfo.SetLocalLocation(Offset(300, 300));
    patternLockPattern->OnTouchMove(locationInfo);
    EXPECT_TRUE(IsEqual(patternLockPattern->cellCenter_, OffsetF(300, 300)));
    patternLockPattern->OnTouchUp();

    /**
     * @tc.steps: step2. Scroll view and Call OnTouchDown
     * @tc.expected: cellCenter_ is equal to locationInfo
     */
    scrollPattern->UpdateCurrentOffset(-100, SCROLL_FROM_UPDATE); // scroll view
    FlushLayoutTask(scrollNode);
    EXPECT_EQ(scrollPattern->GetTotalOffset(), 100);
    mockRenderContext->rect_ = RectF(40, 0, PATTERNLOCK_WIDTH, PATTERNLOCK_HEIGHT);

    locationInfo.SetLocalLocation(Offset(200, 200));
    patternLockPattern->OnTouchDown(locationInfo);
    EXPECT_TRUE(IsEqual(patternLockPattern->cellCenter_, OffsetF(200, 200)));

    locationInfo.SetLocalLocation(Offset(300, 300));
    patternLockPattern->OnTouchMove(locationInfo);
    EXPECT_TRUE(IsEqual(patternLockPattern->cellCenter_, OffsetF(300, 300)));
    patternLockPattern->OnTouchUp();
}

/**
 * @tc.name: PatternLockPatternTest019
 * @tc.desc: Test cellCenter_ when patternlock size change
 * @tc.type: FUNC
 */
HWTEST_F(PatternLockTestNg, PatternLockPatternTest019, TestSize.Level1)
{
    Create([](PatternLockModelNG model) {});

    /**
     * @tc.steps: step1. OnTouchDown a point
     * @tc.expected: cellCenter_ is relative to patternlock
     */
    auto mockRenderContext = AceType::DynamicCast<MockRenderContext>(frameNode_->renderContext_);
    mockRenderContext->paintRect_ = RectF(40, 0, PATTERNLOCK_WIDTH, PATTERNLOCK_HEIGHT);

    TouchLocationInfo locationInfo(0);
    locationInfo.SetLocalLocation(Offset(200, 200));
    pattern_->OnTouchDown(locationInfo);
    EXPECT_TRUE(IsEqual(pattern_->cellCenter_, OffsetF(200, 200)));

    /**
     * @tc.steps: step2. Reduce patternloack size, call OnTouchMove
     * @tc.expected: cellCenter_ will change with patternlock
     */
    float width = 300.f;
    float height = 300.f;
    ViewAbstract::SetWidth(AceType::RawPtr(frameNode_), CalcLength(width));
    ViewAbstract::SetHeight(AceType::RawPtr(frameNode_), CalcLength(height));
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(IsEqual(frameNode_->GetGeometryNode()->GetFrameRect().Width(), width));
    EXPECT_TRUE(IsEqual(frameNode_->GetGeometryNode()->GetFrameRect().Height(), height));

    mockRenderContext->paintRect_ = RectF(90, 0, width, height);
    locationInfo.SetLocalLocation(Offset(300, 300));
    pattern_->OnTouchMove(locationInfo);
    EXPECT_TRUE(IsEqual(pattern_->cellCenter_, OffsetF(300, 300)));
    pattern_->OnTouchUp();
}

/**
 * @tc.name: PatternLockPaintMethodTest001
 * @tc.desc: Test PatternLockPaintMethod GetThemeProp and UpdateContentModifier Function.
 * @tc.type: FUNC
 */
HWTEST_F(PatternLockTestNg, PatternLockPaintMethodTest001, TestSize.Level1)
{
    /**
     * @tc.step: step1. create patternLock PaintMethod and PatternLockTheme.
     */
    std::vector<PatternLockCell> vecCell;
    auto modifier = AceType::MakeRefPtr<PatternLockModifier>();
    PatternLockPaintMethod paintMethod(OffsetF(), false, vecCell, modifier);
    auto paintProperty_ = AceType::MakeRefPtr<PatternLockPaintProperty>();
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetContentSize(SizeF());
    // create mock theme manager
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto patternlockTheme = AceType::MakeRefPtr<V2::PatternLockTheme>();
    patternlockTheme->regularColor_ = REGULAR_COLOR;
    patternlockTheme->selectedColor_ = SELECTED_COLOR;
    patternlockTheme->activeColor_ = ACTIVE_COLOR;
    patternlockTheme->pathColor_ = PATH_COLOR;
    patternlockTheme->circleRadius_ = CIRCLE_RADIUS;
    patternlockTheme->pathStrokeWidth_ = PATH_STROKE_WIDTH;
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(patternlockTheme));
    /**
     * @tc.case: case1. call GetThemeProp with PatternLockTheme.
     */
    paintMethod.GetThemeProp();
    EXPECT_EQ(paintMethod.sideLength_, .0f);
    EXPECT_EQ(paintMethod.circleRadius_, CIRCLE_RADIUS);
    EXPECT_EQ(paintMethod.pathStrokeWidth_, PATH_STROKE_WIDTH);
    EXPECT_EQ(paintMethod.regularColor_, REGULAR_COLOR);
    EXPECT_EQ(paintMethod.selectedColor_, SELECTED_COLOR);
    EXPECT_EQ(paintMethod.activeColor_, ACTIVE_COLOR);
    EXPECT_EQ(paintMethod.pathColor_, PATH_COLOR);
    /**
     * @tc.case: case2. call UpdateContentModifier with unvalid PatternLockPaintProperty.
     */
    PaintWrapper paintWrapper(nullptr, geometryNode, paintProperty_);
    paintMethod.UpdateContentModifier(&paintWrapper);
    EXPECT_EQ(paintMethod.sideLength_, paintWrapper.GetContentSize().Width());
    EXPECT_EQ(paintMethod.circleRadius_, CIRCLE_RADIUS);
    EXPECT_EQ(paintMethod.pathStrokeWidth_, PATH_STROKE_WIDTH);
    EXPECT_EQ(paintMethod.regularColor_, REGULAR_COLOR);
    EXPECT_EQ(paintMethod.selectedColor_, SELECTED_COLOR);
    EXPECT_EQ(paintMethod.activeColor_, ACTIVE_COLOR);
    EXPECT_EQ(paintMethod.pathColor_, PATH_COLOR);
    /**
     * @tc.case: case3. call UpdateContentModifier with valid PatternLockPaintProperty.
     */
    paintProperty_->UpdateCircleRadius(Dimension(20.0));
    paintProperty_->UpdatePathStrokeWidth(Dimension(10.0));
    paintProperty_->UpdateAutoReset(false);
    paintProperty_->UpdateRegularColor(Color::RED);
    paintProperty_->UpdateSelectedColor(Color::GREEN);
    paintProperty_->UpdateActiveColor(Color::BLACK);
    paintProperty_->UpdatePathColor(Color::WHITE);
    paintMethod.UpdateContentModifier(&paintWrapper);
    EXPECT_EQ(paintMethod.circleRadius_, paintProperty_->GetCircleRadiusValue());
    EXPECT_EQ(paintMethod.pathStrokeWidth_, paintProperty_->GetPathStrokeWidthValue());
    EXPECT_EQ(paintMethod.regularColor_, paintProperty_->GetRegularColorValue());
    EXPECT_EQ(paintMethod.selectedColor_, paintProperty_->GetSelectedColorValue());
    EXPECT_EQ(paintMethod.activeColor_, paintProperty_->GetActiveColorValue());
    EXPECT_EQ(paintMethod.pathColor_, paintProperty_->GetPathColorValue());
}

/**
 * @tc.name: PatternLockPaintMethodTest002
 * @tc.desc: Test PatternLockPaintMethod GetThemeProp and UpdateContentModifier Function.
 * @tc.type: FUNC
 */
HWTEST_F(PatternLockTestNg, PatternLockPaintMethodTest002, TestSize.Level1)
{
    /**
     * @tc.step: step1. create patternLock PaintMethod and PatternLockTheme.
     */
    std::vector<PatternLockCell> vecCell;
    auto modifier = AceType::MakeRefPtr<PatternLockModifier>();
    PatternLockPaintMethod paintMethod(OffsetF(), false, vecCell, modifier);
    auto paintProperty_ = AceType::MakeRefPtr<PatternLockPaintProperty>();
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetContentSize(SizeF());
    // create mock theme manager
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto patternlockTheme = AceType::MakeRefPtr<V2::PatternLockTheme>();
    patternlockTheme->activeColor_ = ACTIVE_COLOR;
    patternlockTheme->pathColor_ = PATH_COLOR;
    patternlockTheme->circleRadius_ = CIRCLE_RADIUS;
    patternlockTheme->backgroundCircleRadius_ = ACTIVE_CIRCLE_RADIUS;
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(patternlockTheme));
    /**
     * @tc.case: case1. call GetThemeProp with PatternLockTheme.
     */
    paintMethod.GetThemeProp();
    EXPECT_EQ(paintMethod.circleRadius_, CIRCLE_RADIUS);
    EXPECT_EQ(paintMethod.activeColor_, ACTIVE_COLOR);
    EXPECT_EQ(paintMethod.pathColor_, PATH_COLOR);
    EXPECT_EQ(paintMethod.backgroundCircleRadius_, Dimension(.0));
    /**
     * @tc.case: case2. call UpdateContentModifier with unvalid PatternLockPaintProperty.
     */
    PaintWrapper paintWrapper(nullptr, geometryNode, paintProperty_);
    paintMethod.UpdateContentModifier(&paintWrapper);
    EXPECT_EQ(paintMethod.circleRadius_, CIRCLE_RADIUS);
    EXPECT_EQ(paintMethod.activeColor_, ACTIVE_COLOR);
    EXPECT_EQ(paintMethod.pathColor_, PATH_COLOR);
    EXPECT_EQ(paintMethod.activeCircleColor_, PATH_COLOR);
    /**
     * @tc.case: case3. call UpdateContentModifier with valid PatternLockPaintProperty.
     */
    paintProperty_->UpdateCircleRadius(Dimension(20.0));
    paintProperty_->UpdateActiveColor(Color::BLACK);
    paintProperty_->UpdatePathColor(Color::WHITE);
    paintProperty_->UpdateActiveCircleColor(Color::BLUE);
    paintProperty_->UpdateActiveCircleRadius(Dimension(25.0));
    paintMethod.UpdateContentModifier(&paintWrapper);
    EXPECT_EQ(paintMethod.circleRadius_, paintProperty_->GetCircleRadiusValue());
    EXPECT_EQ(paintMethod.activeColor_, paintProperty_->GetActiveColorValue());
    EXPECT_EQ(paintMethod.pathColor_, paintProperty_->GetPathColorValue());
    EXPECT_EQ(paintMethod.activeCircleColor_, paintProperty_->GetActiveCircleColor());
    EXPECT_EQ(paintMethod.backgroundCircleRadius_, paintProperty_->GetActiveCircleRadius());
}

/**
 * @tc.name: PatternLockLayoutAlgorithmTest001
 * @tc.desc: Test MeasureContent function .
 * @tc.type: FUNC
 */
HWTEST_F(PatternLockTestNg, PatternLockLayoutAlgorithmTest001, TestSize.Level1)
{
    PatternLockLayoutAlgorithm layoutAlgorithm;
    auto layoutProperty = AceType::MakeRefPtr<PatternLockLayoutProperty>();
    LayoutWrapperNode layoutWrapper(nullptr, nullptr, layoutProperty);
    /**
     * @tc.case: case1.
     */
    layoutProperty->UpdateSideLength(Dimension(DEFAULT_SIDE_LENGTH));
    LayoutConstraintF constraint1;
    auto size1 = layoutAlgorithm.MeasureContent(constraint1, &layoutWrapper);
    EXPECT_EQ(size1.value(), SizeF(20.0f, 20.0f));
    /**
     * @tc.case: case2.
     */
    LayoutConstraintF constraint2;
    constraint2.maxSize = SizeF(10.0f, 25.0f);
    constraint2.minSize = SizeF(15.0f, 20.0f);
    auto size2 = layoutAlgorithm.MeasureContent(constraint2, &layoutWrapper);
    EXPECT_EQ(size2.value(), SizeF(15.0f, 15.0f));
    /**
     * @tc.case: case3.
     */
    LayoutConstraintF constraint3;
    constraint3.maxSize = SizeF(40.0f, 30.0f);
    constraint3.minSize = SizeF(15.0f, 20.0f);
    layoutProperty->UpdateSideLength(Dimension(30.0));
    auto size3 = layoutAlgorithm.MeasureContent(constraint3, &layoutWrapper);
    EXPECT_EQ(size3.value(), SizeF(30.0f, 30.0f));
}

/**
 * @tc.name: PatternLockAccessibilityTest001
 * @tc.desc: Test PatternLockAccessibility .
 * @tc.type: FUNC
 */
HWTEST_F(PatternLockTestNg, PatternLockAccessibilityTest001, TestSize.Level1)
{
    Create([](PatternLockModelNG model) {
        model.SetCircleRadius(CIRCLE_RADIUS);
        model.SetRegularColor(REGULAR_COLOR);
        model.SetSelectedColor(SELECTED_COLOR);
        model.SetActiveColor(ACTIVE_COLOR);
        model.SetPathColor(PATH_COLOR);
        model.SetStrokeWidth(PATH_STROKE_WIDTH);
        model.SetAutoReset(true);
        model.SetSideLength(SIDE_LENGTH);
        model.SetActiveCircleColor(ACTIVE_CIRCLE_COLOR);
        model.SetActiveCircleRadius(ACTIVE_CIRCLE_RADIUS);
        model.SetEnableWaveEffect(false);
    });
    /**
     * @tc.case: case1 InitVirtualNode .
     */
    AceApplicationInfo::GetInstance().SetAccessibilityEnabled(true);
    pattern_->CreateNodePaintMethod();
    pattern_->OnModifyDone();
    EXPECT_TRUE(pattern_->accessibilityPropertyVec_.size() > 0);
    /**
     * @tc.case: case2 HandleAccessibilityHoverEvent 1.
     */
    AccessibilityHoverInfo info;
    info.SetActionType(AccessibilityHoverAction::HOVER_ENTER);
    pattern_->HandleAccessibilityHoverEvent(true, info);
    EXPECT_TRUE(pattern_->accessibilityPropertyVec_[0]->GetAccessibilityLevel() ==
        AccessibilityProperty::Level::YES_STR);
    /**
     * @tc.case: case3 HandleTextOnAccessibilityFocusCallback 1.
     */
    pattern_->HandleTextOnAccessibilityFocusCallback(0, 0);
    auto accessibilityProperty = frameNode_->GetAccessibilityProperty<AccessibilityProperty>();
    EXPECT_TRUE(accessibilityProperty->GetAccessibilityLevel() == AccessibilityProperty::Level::NO_STR);
    /**
     * @tc.case: case4 HandleTextOnAccessibilityFocusCallback 2.
     */
    pattern_->HandleTextOnAccessibilityFocusCallback(0, 1);
    pattern_->HandleTextOnAccessibilityFocusCallback(0, 2);
    pattern_->HandleTextOnAccessibilityFocusCallback(1, 0);
    pattern_->HandleTextOnAccessibilityFocusCallback(1, 1);
    pattern_->HandleTextOnAccessibilityFocusCallback(1, 2);
    pattern_->HandleTextOnAccessibilityFocusCallback(2, 0);
    pattern_->HandleTextOnAccessibilityFocusCallback(2, 1);
    pattern_->HandleTextOnAccessibilityFocusCallback(2, 2);
    EXPECT_TRUE(pattern_->choosePoint_.size() == 9);
    EXPECT_TRUE(pattern_->choosePoint_[0].GetColumn() == 0);
    EXPECT_TRUE(pattern_->choosePoint_[0].GetRow() == 0);
    EXPECT_TRUE(pattern_->choosePoint_[3].GetColumn() == 1);
    EXPECT_TRUE(pattern_->choosePoint_[3].GetRow() == 0);
    EXPECT_TRUE(pattern_->choosePoint_[8].GetColumn() == 2);
    EXPECT_TRUE(pattern_->choosePoint_[8].GetRow() == 2);
    /**
     * @tc.case: case5 HandleAccessibilityHoverEvent 2.
     */
    info.SetActionType(AccessibilityHoverAction::HOVER_MOVE);
    pattern_->HandleAccessibilityHoverEvent(false, info);
    EXPECT_TRUE(pattern_->accessibilityPropertyVec_[0]->GetAccessibilityLevel() ==
        AccessibilityProperty::Level::NO_STR);
    EXPECT_TRUE(accessibilityProperty->GetAccessibilityLevel() == AccessibilityProperty::Level::YES_STR);
    /**
     * @tc.case: case6 HandleAccessibilityHoverEvent 3.
     */
    info.SetActionType(AccessibilityHoverAction::HOVER_ENTER);
    pattern_->HandleAccessibilityHoverEvent(true, info);
    info.SetActionType(AccessibilityHoverAction::HOVER_MOVE);
    pattern_->HandleAccessibilityHoverEvent(false, info);
    EXPECT_TRUE(pattern_->choosePoint_.size() == 0);
}

/**
 * @tc.name: StartModifierCanceledAnimate
 * @tc.desc: Test MeasureContent function .
 * @tc.type: FUNC
 */
HWTEST_F(PatternLockTestNg, StartModifierCanceledAnimate, TestSize.Level1)
{
    ScrollModelNG model;
    model.Create();
    ViewAbstract::SetWidth(CalcLength(SCROLL_WIDTH));
    ViewAbstract::SetHeight(CalcLength(SCROLL_HEIGHT));
    {
        ColumnModelNG colModel;
        colModel.Create(Dimension(0), nullptr, "");
        ViewAbstract::SetWidth(CalcLength(FILL_LENGTH));
        ViewAbstract::SetHeight(CalcLength(SCROLL_HEIGHT + 100));
        PaddingProperty padding;
        padding.top = CalcLength(100);
        ViewAbstract::SetPadding(padding);
        {
            PatternLockModelNG patternLockModelNG;
            patternLockModelNG.Create();
            ViewAbstract::SetWidth(CalcLength(PATTERNLOCK_WIDTH));
            ViewAbstract::SetHeight(CalcLength(PATTERNLOCK_HEIGHT));
            ViewStackProcessor::GetInstance()->Pop();
        }
        ViewStackProcessor::GetInstance()->Pop();
    }
    auto scrollNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    FlushLayoutTask(scrollNode);

    /**
     * @tc.steps: step1. because colNode padding, patternLockNode offsetY is 100
     */
    auto colNode = GetChildFrameNode(scrollNode, 0);
    auto patternLockNode = GetChildFrameNode(colNode, 0);
    auto scrollPattern = scrollNode->GetPattern<ScrollPattern>();
    auto patternLockPattern = patternLockNode->GetPattern<PatternLockPattern>();
    patternLockPattern->patternLockModifier_ = AceType::MakeRefPtr<PatternLockModifier>();
    patternLockPattern->isMoveEventValid_ = true;
    patternLockPattern->StartModifierCanceledAnimate();
    EXPECT_TRUE(patternLockPattern->isMoveEventValid_);
    patternLockPattern->isMoveEventValid_ = false;
    patternLockPattern->StartModifierCanceledAnimate();
    EXPECT_FALSE(patternLockPattern->isMoveEventValid_);
}

/**
 * @tc.name: AddPassPointToChoosePoint
 * @tc.desc: Test MeasureContent function .
 * @tc.type: FUNC
 */
HWTEST_F(PatternLockTestNg, AddPassPointToChoosePoint, TestSize.Level1)
{
    ScrollModelNG model;
    model.Create();
    ViewAbstract::SetWidth(CalcLength(SCROLL_WIDTH));
    ViewAbstract::SetHeight(CalcLength(SCROLL_HEIGHT));
    {
        ColumnModelNG colModel;
        colModel.Create(Dimension(0), nullptr, "");
        ViewAbstract::SetWidth(CalcLength(FILL_LENGTH));
        ViewAbstract::SetHeight(CalcLength(SCROLL_HEIGHT + 100));
        PaddingProperty padding;
        padding.top = CalcLength(100);
        ViewAbstract::SetPadding(padding);
        {
            PatternLockModelNG patternLockModelNG;
            patternLockModelNG.Create();
            ViewAbstract::SetWidth(CalcLength(PATTERNLOCK_WIDTH));
            ViewAbstract::SetHeight(CalcLength(PATTERNLOCK_HEIGHT));
            ViewStackProcessor::GetInstance()->Pop();
        }
        ViewStackProcessor::GetInstance()->Pop();
    }
    auto scrollNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    FlushLayoutTask(scrollNode);

    /**
     * @tc.steps: step1. because colNode padding, patternLockNode offsetY is 100
     */
    auto colNode = GetChildFrameNode(scrollNode, 0);
    auto patternLockNode = GetChildFrameNode(colNode, 0);
    auto scrollPattern = scrollNode->GetPattern<ScrollPattern>();
    auto patternLockPattern = patternLockNode->GetPattern<PatternLockPattern>();
    std::vector<PatternLockCell> choosePoint;
    choosePoint.push_back(PatternLockCell(1, 1));
    choosePoint.push_back(PatternLockCell(2, 2));
    patternLockPattern->AddPassPointToChoosePoint(2, 1, choosePoint);
    EXPECT_EQ(patternLockPattern->choosePoint_.back().GetColumn(), 1);
    EXPECT_EQ(patternLockPattern->choosePoint_.back().GetRow(), 1);

    patternLockPattern->AddPassPointToChoosePoint(1, 2, choosePoint);
    EXPECT_EQ(patternLockPattern->choosePoint_.back().GetColumn(), 2);
    EXPECT_EQ(patternLockPattern->choosePoint_.back().GetRow(), 2);
}

/**
 * @tc.name: PatternLockReplacePlaceHolderTest001
 * @tc.desc: Test ReplacePlaceHolder function .
 * @tc.type: FUNC
 */
HWTEST_F(PatternLockTestNg, PatternLockReplacePlaceHolderTest001, TestSize.Level1)
{
    Create([](PatternLockModelNG model) {});

    std::string bo_CN = "སྒོར་ཚེག་ %d ལ་སྦྲེལ་ཟིན།";
    std::string ug = "نۇقتا %d ئۇلاندى";
    std::string zh_CN = "已连接圆点%d";
    std::string en_US = "Connected to dot %d";
    std::string zh_CN_ = "已连接圆点%d";
    std::string zh_CN_nod = "已连接圆点";

    std::string bo_CN_replace = "སྒོར་ཚེག་ 5 ལ་སྦྲེལ་ཟིན།";
    std::string ug_replace = "نۇقتا 1 ئۇلاندى";
    std::string zh_CN_replace = "已连接圆点0";
    std::string en_US_replace = "Connected to dot 9";
    std::string zh_CN_replace2 = "已连接圆点88";
    std::string zh_CN_replace_nod = "已连接圆点4";

    std::string bo_CN_result = pattern_->ReplacePlaceHolder(bo_CN, 5);
    std::string ug_result = pattern_->ReplacePlaceHolder(ug, 1);
    std::string zh_CN_result = pattern_->ReplacePlaceHolder(zh_CN, 0);
    std::string en_US_result = pattern_->ReplacePlaceHolder(en_US, 9);
    std::string zh_CN_result2 = pattern_->ReplacePlaceHolder(zh_CN, 88);
    std::string zh_CN_result_nod = pattern_->ReplacePlaceHolder(zh_CN, 4);

    EXPECT_EQ(bo_CN_result, bo_CN_replace);
    EXPECT_EQ(ug_result, ug_replace);
    EXPECT_EQ(zh_CN_result, zh_CN_replace);
    EXPECT_EQ(en_US_result, en_US_replace);
    EXPECT_EQ(zh_CN_result2, zh_CN_replace2);
    EXPECT_EQ(zh_CN_result_nod, zh_CN_replace_nod);
}

/**
 * @tc.name: PatternLockSkipUnselectedPointTest001
 * @tc.desc: Test PatternLockAccessibility .
 * @tc.type: FUNC
 */
HWTEST_F(PatternLockTestNg, PatternLockSkipUnselectedPointTest001, TestSize.Level1)
{
    Create([](PatternLockModelNG model) {
        model.SetCircleRadius(CIRCLE_RADIUS);
        model.SetRegularColor(REGULAR_COLOR);
        model.SetSelectedColor(SELECTED_COLOR);
        model.SetActiveColor(ACTIVE_COLOR);
        model.SetPathColor(PATH_COLOR);
        model.SetStrokeWidth(PATH_STROKE_WIDTH);
        model.SetAutoReset(true);
        model.SetSideLength(SIDE_LENGTH);
        model.SetActiveCircleColor(ACTIVE_CIRCLE_COLOR);
        model.SetActiveCircleRadius(ACTIVE_CIRCLE_RADIUS);
        model.SetEnableWaveEffect(false);
        model.SetSkipUnselectedPoint(true);
    });
    /**
     * @tc.case: case1 InitVirtualNode .
     */
    AceApplicationInfo::GetInstance().SetAccessibilityEnabled(true);
    pattern_->CreateNodePaintMethod();
    pattern_->OnModifyDone();
    EXPECT_EQ(pattern_->skipUnselectedPoint_, true);
}

/**
 * @tc.name: PatternLockSkipUnselectedPointTest002
 * @tc.desc: Test PatternLock pattern method AddPassPoint.
 * @tc.type: FUNC
 */
HWTEST_F(PatternLockTestNg, PatternLockSkipUnselectedPointTest002, TestSize.Level1)
{
    Create([](PatternLockModelNG model) {
        model.SetSkipUnselectedPoint(false);
    });
    pattern_->patternLockModifier_ = AceType::MakeRefPtr<PatternLockModifier>();
    pattern_->InitSkipUnselectedPoint();

    /**
     * @tc.case: case1: selectedPoint(1, 1) and link Point(1, 3) auto select Point(1, 2)
     */
    pattern_->choosePoint_.clear();
    pattern_->choosePoint_.push_back(PatternLockCell(1, 1));
    pattern_->AddPassPoint(1, 3);
    EXPECT_EQ(pattern_->choosePoint_.back().GetColumn(), 1);
    EXPECT_EQ(pattern_->choosePoint_.back().GetRow(), 2);
    /**
     * @tc.case: case2: selectedPoint(1, 1) and link Point(3, 1) auto select Point(2, 1)
     */
    pattern_->choosePoint_.clear();
    pattern_->choosePoint_.push_back(PatternLockCell(1, 1));
    pattern_->AddPassPoint(3, 1);
    EXPECT_EQ(pattern_->choosePoint_.back().GetColumn(), 2);
    EXPECT_EQ(pattern_->choosePoint_.back().GetRow(), 1);
    /**
     * @tc.case: case3: selectedPoint(1, 1) and link Point(3, 3) auto select Point(2, 2)
     */
    pattern_->choosePoint_.clear();
    pattern_->choosePoint_.push_back(PatternLockCell(1, 1));
    pattern_->AddPassPoint(3, 3);
    EXPECT_EQ(pattern_->choosePoint_.back().GetColumn(), 2);
    EXPECT_EQ(pattern_->choosePoint_.back().GetRow(), 2);
}

/**
 * @tc.name: PatternLockSkipUnselectedPointTest003
 * @tc.desc: Test PatternLock pattern method AddPassPoint.
 * @tc.type: FUNC
 */
HWTEST_F(PatternLockTestNg, PatternLockSkipUnselectedPointTest003, TestSize.Level1)
{
    Create([](PatternLockModelNG model) {
        model.SetSkipUnselectedPoint(true);
    });
    pattern_->patternLockModifier_ = AceType::MakeRefPtr<PatternLockModifier>();
    pattern_->InitSkipUnselectedPoint();

    /**
     * @tc.case: case1: selectedPoint(1, 1) and link Point(1, 3), skip unselected Point(1, 2)
     */
    pattern_->choosePoint_.clear();
    pattern_->choosePoint_.push_back(PatternLockCell(1, 1));
    pattern_->AddPassPoint(1, 3);
    EXPECT_EQ(pattern_->choosePoint_.back().GetColumn(), 1);
    EXPECT_EQ(pattern_->choosePoint_.back().GetRow(), 1);
    /**
     * @tc.case: case2: selectedPoint(1, 1) and link Point(3, 1), skip unselected Point(1, 2)
     */
    pattern_->choosePoint_.clear();
    pattern_->choosePoint_.push_back(PatternLockCell(1, 1));
    pattern_->AddPassPoint(3, 1);
    EXPECT_EQ(pattern_->choosePoint_.back().GetColumn(), 1);
    EXPECT_EQ(pattern_->choosePoint_.back().GetRow(), 1);
    /**
     * @tc.case: case3: selectedPoint(1, 1) and link Point(3, 3), skip unselected Point(1, 2)
     */
    pattern_->choosePoint_.clear();
    pattern_->choosePoint_.push_back(PatternLockCell(1, 1));
    pattern_->AddPassPoint(3, 3);
    EXPECT_EQ(pattern_->choosePoint_.back().GetColumn(), 1);
    EXPECT_EQ(pattern_->choosePoint_.back().GetRow(), 1);
}


/**
 * @tc.name: PatternLockEnableForegroundTest001
 * @tc.desc: Test PatternLockAccessibility .
 * @tc.type: FUNC
 */
HWTEST_F(PatternLockTestNg, PatternLockEnableForegroundTest001, TestSize.Level1)
{
    Create([](PatternLockModelNG model) {
        model.SetCircleRadius(CIRCLE_RADIUS);
        model.SetRegularColor(REGULAR_COLOR);
        model.SetSelectedColor(SELECTED_COLOR);
        model.SetActiveColor(ACTIVE_COLOR);
        model.SetPathColor(PATH_COLOR);
        model.SetStrokeWidth(PATH_STROKE_WIDTH);
        model.SetAutoReset(true);
        model.SetSideLength(SIDE_LENGTH);
        model.SetActiveCircleColor(ACTIVE_CIRCLE_COLOR);
        model.SetActiveCircleRadius(ACTIVE_CIRCLE_RADIUS);
        model.SetEnableWaveEffect(false);
        model.SetEnableForeground(true);
    });
    EXPECT_TRUE(paintProperty_->GetEnableForegroundValue());
}
} // namespace OHOS::Ace::NG
