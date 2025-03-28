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

#include "swiper_test_ng.h"

#include "core/components_ng/pattern/swiper_indicator/dot_indicator/dot_indicator_paint_property.h"
#include "core/components_ng/pattern/swiper_indicator/indicator_common/swiper_indicator_pattern.h"
#include "core/components_ng/pattern/text/text_pattern.h"

namespace OHOS::Ace::NG {
namespace {
// padding:12 space:8 size:8
Offset FIRST_POINT = Offset(16.f, 16.f);
Offset SECOND_POINT = Offset(40.f, 16.f);
Offset FOURTH_POINT = Offset(72.f, 16.f);
} // namespace

class SwiperIndicatorTestNg : public SwiperTestNg {
public:
    void MouseClickIndicator(SourceType sourceType, Offset hoverPoint);
    void TouchClickIndicator(SourceType sourceType, Offset touchPoint);
    void LongPressIndicator(Offset startPoint, Offset endPoint);
};

void SwiperIndicatorTestNg::MouseClickIndicator(SourceType sourceType, Offset hoverPoint)
{
    auto indicatorPattern = indicatorNode_->GetPattern<SwiperIndicatorPattern>();
    HoverInfo hoverInfo;
    hoverInfo.SetSourceDevice(sourceType);
    indicatorPattern->hoverEvent_->GetOnHoverFunc()(true, hoverInfo);

    MouseInfo mouseInfo;
    mouseInfo.SetSourceDevice(sourceType);
    mouseInfo.SetAction(MouseAction::PRESS);
    mouseInfo.SetLocalLocation(hoverPoint);
    indicatorPattern->mouseEvent_->GetOnMouseEventFunc()(mouseInfo);

    GestureEvent gestureEvent;
    gestureEvent.SetSourceDevice(sourceType);
    indicatorPattern->isRepeatClicked_ = false;
    indicatorPattern->HandleClick(gestureEvent);
    FlushUITasks();
}

void SwiperIndicatorTestNg::TouchClickIndicator(SourceType sourceType, Offset touchPoint)
{
    auto indicatorPattern = indicatorNode_->GetPattern<SwiperIndicatorPattern>();
    indicatorPattern->HandleTouchEvent(CreateTouchEventInfo(TouchType::DOWN, touchPoint));
    indicatorPattern->HandleTouchEvent(CreateTouchEventInfo(TouchType::UP, touchPoint));

    GestureEvent gestureEvent;
    gestureEvent.SetSourceDevice(sourceType);
    gestureEvent.SetLocalLocation(touchPoint);
    indicatorPattern->HandleClick(gestureEvent);
    FlushUITasks();
}

void SwiperIndicatorTestNg::LongPressIndicator(Offset startPoint, Offset endPoint)
{
    auto indicatorPattern = indicatorNode_->GetPattern<SwiperIndicatorPattern>();
    indicatorPattern->HandleTouchEvent(CreateTouchEventInfo(TouchType::DOWN, startPoint));
    GestureEvent gestureEvent;
    gestureEvent.SetLocalLocation(startPoint);
    indicatorPattern->HandleLongPress(gestureEvent);

    indicatorPattern->HandleTouchEvent(CreateTouchEventInfo(TouchType::MOVE, endPoint));
    indicatorPattern->HandleTouchEvent(CreateTouchEventInfo(TouchType::UP, endPoint));
    FlushUITasks();
}

/**
 * @tc.name: OnIndicatorChangeEvent001
 * @tc.desc: Test IndicatorChangeEvent, only effected with DIGIT
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestNg, OnIndicatorChangeEvent001, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetIndicatorType(SwiperIndicatorType::DIGIT);
    CreateSwiperItems();
    CreateSwiperDone();
    auto firstTextNode = AceType::DynamicCast<FrameNode>(indicatorNode_->GetFirstChild());
    auto lastTextNode = AceType::DynamicCast<FrameNode>(indicatorNode_->GetLastChild());
    auto firstTextLayoutProperty = firstTextNode->GetLayoutProperty<TextLayoutProperty>();
    auto lastTextLayoutProperty = lastTextNode->GetLayoutProperty<TextLayoutProperty>();

    /**
     * @tc.steps: step1. Default
     * @tc.expected: text is "1/4"
     */
    EXPECT_TRUE(DigitText(u"1/4"));

    /**
     * @tc.steps: step2. Call ShowNext
     * @tc.expected: Change firstText
     */
    ShowNext();
    EXPECT_TRUE(DigitText(u"2/4"));

    /**
     * @tc.steps: step3. Call ShowPrevious
     * @tc.expected: Change firstText
     */
    ShowPrevious();
    EXPECT_TRUE(DigitText(u"1/4"));

    /**
     * @tc.steps: step4. Call ChangeIndex
     * @tc.expected: Change firstText
     */
    ChangeIndex(3);
    EXPECT_TRUE(DigitText(u"4/4"));
}

/**
 * @tc.name: HandleMouseClick001
 * @tc.desc: Test SwiperIndicator HandleMouseClick
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestNg, HandleMouseClick001, TestSize.Level1)
{
    CreateSwiper();
    CreateSwiperItems();
    CreateSwiperDone();

    /**
     * @tc.steps: step1. Click item(index:1)
     * @tc.expected: Swipe to item(index:1)
     */
    MouseClickIndicator(SourceType::MOUSE, SECOND_POINT);
    EXPECT_EQ(pattern_->GetCurrentIndex(), 1);

    /**
     * @tc.steps: step2. Click item(index:2)
     * @tc.expected: Still is item(index:1)
     */
    MouseClickIndicator(SourceType::MOUSE, SECOND_POINT);
    EXPECT_EQ(pattern_->GetCurrentIndex(), 1);

    /**
     * @tc.steps: step3. Click item(index:3)
     * @tc.expected: Swipe to item(index:3)
     */
    MouseClickIndicator(SourceType::MOUSE, FOURTH_POINT);
    EXPECT_EQ(pattern_->GetCurrentIndex(), 3);

    /**
     * @tc.steps: step4. Click item(index:0)
     * @tc.expected: Swipe to item(index:0)
     */
    MouseClickIndicator(SourceType::MOUSE, FIRST_POINT);
    EXPECT_EQ(pattern_->GetCurrentIndex(), 0);
}

/**
 * @tc.name: HandleMouseClick002
 * @tc.desc: Test SwiperIndicator HandleMouseClick when SwipeByGroup is true
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestNg, HandleMouseClick002, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetDisplayCount(3);
    model.SetSwipeByGroup(true);
    model.SetIndicatorType(SwiperIndicatorType::DOT);
    CreateSwiperItems(6);
    CreateSwiperDone();
    EXPECT_EQ(pattern_->TotalCount(), 6);
    int32_t settingApiVersion = static_cast<int32_t>(PlatformVersion::VERSION_EIGHTEEN);
    int32_t backupApiVersion = MockContainer::Current()->GetApiTargetVersion();
    MockContainer::Current()->SetApiTargetVersion(settingApiVersion);
    EXPECT_EQ(pattern_->DisplayIndicatorTotalCount(), 2);

    /**
     * @tc.steps: step1. Click item(index:0)
     * @tc.expected: Swipe to item(index:0)
     */
    MouseClickIndicator(SourceType::MOUSE, FIRST_POINT);
    EXPECT_EQ(pattern_->GetCurrentIndex(), 0);
    MockContainer::Current()->SetApiTargetVersion(backupApiVersion);
}

/**
 * @tc.name: HandleMouseClick003
 * @tc.desc: Test SwiperIndicator HandleMouseClick
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestNg, HandleMouseClick003, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetIndicatorType(SwiperIndicatorType::DOT);
    model.SetBindIndicator(true);
    CreateSwiperItems();
    CreateSwiperDone();
    EXPECT_EQ(indicatorNode_, nullptr);
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    indicatorNode_ = FrameNode::GetOrCreateFrameNode(
        V2::SWIPER_INDICATOR_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<IndicatorPattern>(); });
    EXPECT_NE(indicatorNode_, nullptr);
    auto indicatorPattern = indicatorNode_->GetPattern<IndicatorPattern>();
    auto controller = indicatorPattern->GetIndicatorController();
    controller->SetSwiperNode(frameNode_);
    indicatorPattern->OnModifyDone();
    FlushUITasks();
    indicatorPattern->isRepeatClicked_ = false;
    layoutProperty_->UpdateSwipeByGroup(true);

    /**
     * @tc.steps: step1. Click item(index:1)
     * @tc.expected: Swipe to item(index:1)
     */
    MouseClickIndicator(SourceType::MOUSE, SECOND_POINT);
    EXPECT_EQ(pattern_->GetCurrentIndex(), 1);
    /**
     * @tc.steps: step2. Click item(index:2)
     * @tc.expected: Still is item(index:1)
     */
    MouseClickIndicator(SourceType::MOUSE, SECOND_POINT);
    EXPECT_EQ(pattern_->GetCurrentIndex(), 1);
    /**
     * @tc.steps: step3. Click item(index:3)
     * @tc.expected: Swipe to item(index:3)
     */
    MouseClickIndicator(SourceType::MOUSE, FOURTH_POINT);
    EXPECT_EQ(pattern_->GetCurrentIndex(), 3);
    /**
     * @tc.steps: step4. Click item(index:0)
     * @tc.expected: Swipe to item(index:0)
     */
    MouseClickIndicator(SourceType::MOUSE, FIRST_POINT);
    EXPECT_EQ(pattern_->GetCurrentIndex(), 0);
}

/**
 * @tc.name: HandleTouchClick001
 * @tc.desc: Test SwiperIndicator HandleTouchClick
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestNg, HandleTouchClick001, TestSize.Level1)
{
    CreateSwiper();
    CreateSwiperItems();
    CreateSwiperDone();

    /**
     * @tc.steps: step1. Click item(index:1)
     * @tc.expected: Swipe to item(index:1)
     */
    TouchClickIndicator(SourceType::TOUCH, SECOND_POINT);
    EXPECT_EQ(pattern_->GetCurrentIndex(), 1);

    /**
     * @tc.steps: step2. Click item(index:3)
     * @tc.expected: Swipe to item(index:2)
     */
    TouchClickIndicator(SourceType::TOUCH, FOURTH_POINT);
    EXPECT_EQ(pattern_->GetCurrentIndex(), 2);

    /**
     * @tc.steps: step3. Click item(index:0)
     * @tc.expected: Swipe to item(index:1)
     */
    TouchClickIndicator(SourceType::TOUCH, FIRST_POINT);
    EXPECT_EQ(pattern_->GetCurrentIndex(), 1);
}

/**
 * @tc.name: HandleLongPress001
 * @tc.desc: Test SwiperIndicator HandleLongPress
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestNg, HandleLongPress001, TestSize.Level1)
{
    CreateSwiper();
    CreateSwiperItems();
    CreateSwiperDone();

    /**
     * @tc.steps: step1. Touch and move right
     * @tc.expected: Swipe to item(index:1)
     */
    LongPressIndicator(FIRST_POINT, FOURTH_POINT);
    EXPECT_EQ(pattern_->GetCurrentIndex(), 1);

    /**
     * @tc.steps: step1. Touch and move left
     * @tc.expected: Swipe to item(index:0)
     */
    LongPressIndicator(FOURTH_POINT, SECOND_POINT);
    EXPECT_EQ(pattern_->GetCurrentIndex(), 0);
}

/**
 * @tc.name: SetDotIndicatorStyle001
 * @tc.desc: Test SwiperModelNG SetDotIndicatorStyle
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestNg, SetDotIndicatorStyle001, TestSize.Level1)
{
    SwiperParameters swiperParameters;
    swiperParameters.colorVal = Color(Color::BLUE);
    SwiperModelNG model = CreateSwiper();
    model.SetDotIndicatorStyle(swiperParameters);
    CreateSwiperItems();
    CreateSwiperDone();
    ASSERT_EQ(pattern_->swiperParameters_->colorVal, swiperParameters.colorVal);
}

/**
 * @tc.name: SetDigitIndicatorStyle001
 * @tc.desc: Test SwiperModelNG SetDigitIndicatorStyle
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestNg, SetDigitIndicatorStyle001, TestSize.Level1)
{
    SwiperDigitalParameters digitalParameters;
    digitalParameters.fontColor = Color(Color::GREEN);
    SwiperModelNG model = CreateSwiper();
    model.SetDigitIndicatorStyle(digitalParameters);
    CreateSwiperItems();
    CreateSwiperDone();
    ASSERT_EQ(pattern_->swiperDigitalParameters_->fontColor, digitalParameters.fontColor);
}

/**
 * @tc.name: SwiperPatternPlayIndicatorTranslateAnimation002
 * @tc.desc: PlayIndicatorTranslateAnimation
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestNg, SwiperPatternPlayIndicatorTranslateAnimation002, TestSize.Level1)
{
    CreateSwiper();
    CreateSwiperItems();
    CreateSwiperDone();

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
 * @tc.name: SwiperInitIndicator006
 * @tc.desc: Test SwiperPattern SwiperInitIndicator
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestNg, SwiperInitIndicator006, TestSize.Level1)
{
    CreateSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
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
 * @tc.name: SwiperIndicatorPatternTestNg005
 * @tc.desc: HandleHoverEvent
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestNg, SwiperIndicatorPatternTestNg005, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetDirection(Axis::VERTICAL);
    CreateSwiperItems();
    CreateSwiperDone();
    auto indicatorNode = GetChildFrameNode(frameNode_, 4);
    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    auto eventHub = indicatorNode->GetEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    indicatorPattern->SetIndicatorInteractive(true);
    EXPECT_TRUE(eventHub->IsEnabled());
    indicatorPattern->SetIndicatorInteractive(false);
    EXPECT_FALSE(eventHub->IsEnabled());
}

/**
 * @tc.name: SwiperIndicatorPatternCheckIsTouchBottom001
 * @tc.desc: CheckIsTouchBottom
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestNg, SwiperIndicatorPatternCheckIsTouchBottom001, TestSize.Level1)
{
    CreateSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    auto indicatorPattern = indicatorNode_->GetPattern<SwiperIndicatorPattern>();
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
 * @tc.name: SwiperIndicatorPatternCheckIsTouchBottom002
 * @tc.desc: CheckIsTouchBottom
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestNg, SwiperIndicatorPatternCheckIsTouchBottom002, TestSize.Level1)
{
    CreateSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    auto displayCount = pattern_->GetLayoutProperty<SwiperLayoutProperty>()->GetDisplayCount().value_or(1);
    auto childrenSize = pattern_->RealTotalCount();
    auto indicatorPattern = indicatorNode_->GetPattern<SwiperIndicatorPattern>();
    GestureEvent info;
    layoutProperty_->UpdateLoop(false);
    pattern_->leftButtonId_.reset();
    pattern_->rightButtonId_.reset();
    pattern_->GetLayoutProperty<SwiperLayoutProperty>()->UpdateShowIndicator(false);
    /**
     * @tc.steps: step1. call no mirror func.
     */
    pattern_->currentIndex_ = -5;
    layoutProperty_->UpdateLayoutDirection(TextDirection::LTR);
    EXPECT_TRUE(indicatorPattern->CheckIsTouchBottom(info));
    pattern_->currentIndex_ = 5;
    EXPECT_TRUE(pattern_->currentIndex_ >= childrenSize - displayCount);
    EXPECT_TRUE(indicatorPattern->CheckIsTouchBottom(info));
    /**
     * @tc.steps: step2. call mirror func.
     */
    pattern_->currentIndex_ = -5;
    layoutProperty_->UpdateLayoutDirection(TextDirection::RTL);
    EXPECT_TRUE(indicatorPattern->CheckIsTouchBottom(info));
    pattern_->currentIndex_ = 5;
    EXPECT_TRUE(pattern_->currentIndex_ >= childrenSize - displayCount);
    EXPECT_TRUE(indicatorPattern->CheckIsTouchBottom(info));
}

/**
 * @tc.name: SwiperIndicatorPatternTouchBottom001
 * @tc.desc: CheckIsTouchBottom
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestNg, SwiperIndicatorPatternTouchBottom001, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetDirection(Axis::VERTICAL);
    CreateSwiperItems();
    CreateSwiperDone();
    auto indicatorNode_ = AceType::DynamicCast<FrameNode>(frameNode_->GetChildAtIndex(4));
    auto indicatorPattern = indicatorNode_->GetPattern<SwiperIndicatorPattern>();

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
 * @tc.name: SwiperIndicatorPatternTouchBottom002
 * @tc.desc: CheckIsTouchBottom
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestNg, SwiperIndicatorPatternTouchBottom002, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetDirection(Axis::VERTICAL);
    model.SetBindIndicator(true);
    CreateSwiperItems();
    CreateSwiperDone();
    EXPECT_EQ(indicatorNode_, nullptr);
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    indicatorNode_ = FrameNode::GetOrCreateFrameNode(
        V2::SWIPER_INDICATOR_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<IndicatorPattern>(); });
    EXPECT_NE(indicatorNode_, nullptr);
    auto indicatorPattern = indicatorNode_->GetPattern<IndicatorPattern>();
    auto controller = indicatorPattern->GetIndicatorController();
    controller->SetSwiperNode(frameNode_);

    GestureEvent info;
    info.mainDelta_ = 1.0f;
    TouchLocationInfo touchLocationInfo("down", 0);
    touchLocationInfo.SetTouchType(TouchType::DOWN);
    EXPECT_FALSE(indicatorPattern->SwiperIndicatorPattern::CheckIsTouchBottom(info));
    EXPECT_TRUE(indicatorPattern->SwiperIndicatorPattern::CheckIsTouchBottom(touchLocationInfo));

    pattern_->currentIndex_ = 0;
    layoutProperty_->UpdateLoop(false);
    pattern_->leftButtonId_ = 1;
    pattern_->rightButtonId_ = 1;
    pattern_->GetLayoutProperty<SwiperLayoutProperty>()->UpdateShowIndicator(true);
    EXPECT_TRUE(indicatorPattern->SwiperIndicatorPattern::CheckIsTouchBottom(info));
    EXPECT_TRUE(indicatorPattern->SwiperIndicatorPattern::CheckIsTouchBottom(touchLocationInfo));
}

/**
 * @tc.name: SwiperIndicatorGetMouseClickIndex001
 * @tc.desc: Test GetMouseClickIndex
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestNg, SwiperIndicatorGetMouseClickIndex001, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetIndicatorType(SwiperIndicatorType::DOT);
    model.SetDirection(Axis::VERTICAL);
    CreateSwiperItems();
    CreateSwiperDone();
    RefPtr<SwiperIndicatorPattern> indicatorPattern = indicatorNode_->GetPattern<SwiperIndicatorPattern>();
    auto paintProperty = indicatorNode_->GetPaintProperty<DotIndicatorPaintProperty>();
    indicatorPattern->GetMouseClickIndex();
    paintProperty->UpdateIsCustomSize(true);
    indicatorPattern->GetMouseClickIndex();
    ASSERT_TRUE(paintProperty->GetIsCustomSizeValue(false));
}

/**
 * @tc.name: SwiperIndicatorGetMouseClickIndex002
 * @tc.desc: Test GetMouseClickIndex
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestNg, SwiperIndicatorGetMouseClickIndex002, TestSize.Level1)
{
    CreateSwiper();
    CreateSwiperItems();
    CreateSwiperDone();

    /**
     * @tc.steps: step1. call no mirror func.
     */
    RefPtr<SwiperIndicatorPattern> indicatorPattern = indicatorNode_->GetPattern<SwiperIndicatorPattern>();
    layoutProperty_->UpdateLayoutDirection(TextDirection::LTR);
    indicatorPattern->hoverPoint_ = PointF(72.f, 16.f);
    indicatorPattern->GetMouseClickIndex();
    EXPECT_EQ(indicatorPattern->mouseClickIndex_, 3);

    /**
     * @tc.steps: step2. call mirror func.
     */
    layoutProperty_->UpdateLayoutDirection(TextDirection::RTL);
    FlushUITasks();
    indicatorPattern->hoverPoint_ = PointF(16.f, 16.f);
    indicatorPattern->GetMouseClickIndex();
    EXPECT_EQ(indicatorPattern->mouseClickIndex_, 3);
}

/**
 * @tc.name: SwiperIndicatorGetMouseClickIndex003
 * @tc.desc: Test GetMouseClickIndex
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestNg, SwiperIndicatorGetMouseClickIndex003, TestSize.Level1)
{
    CreateSwiper();
    CreateSwiperItems();
    CreateSwiperDone();

    MouseClickIndicator(SourceType::MOUSE, FOURTH_POINT);
    EXPECT_EQ(pattern_->currentIndex_, 3);

    pattern_->ShowNext();
    MouseClickIndicator(SourceType::MOUSE, SECOND_POINT);
    EXPECT_EQ(pattern_->currentIndex_, 5);

    pattern_->ShowNext();
    pattern_->ShowNext();
    EXPECT_EQ(pattern_->currentIndex_, 7);
    MouseClickIndicator(SourceType::MOUSE, FIRST_POINT);
    EXPECT_EQ(pattern_->currentIndex_, 4);

    MouseClickIndicator(SourceType::MOUSE, FOURTH_POINT);
    EXPECT_EQ(pattern_->currentIndex_, 7);
    pattern_->ShowNext();
    MouseClickIndicator(SourceType::MOUSE, FOURTH_POINT);
    EXPECT_EQ(pattern_->currentIndex_, 11);
    pattern_->ShowNext();
    MouseClickIndicator(SourceType::MOUSE, SECOND_POINT);
    EXPECT_EQ(pattern_->currentIndex_, 13);
    MouseClickIndicator(SourceType::MOUSE, FOURTH_POINT);
    EXPECT_EQ(pattern_->currentIndex_, 15);

    MouseClickIndicator(SourceType::MOUSE, FIRST_POINT);
    EXPECT_EQ(pattern_->currentIndex_, 12);

    pattern_->ChangeIndex(0, false);
    FlushUITasks();
    EXPECT_EQ(pattern_->currentIndex_, 0);
    pattern_->ShowPrevious();
    EXPECT_EQ(pattern_->currentIndex_, -1);
    MouseClickIndicator(SourceType::MOUSE, FIRST_POINT);
    EXPECT_EQ(pattern_->currentIndex_, -4);

    pattern_->ShowPrevious();
    MouseClickIndicator(SourceType::MOUSE, FIRST_POINT);
    pattern_->ShowPrevious();
    EXPECT_EQ(pattern_->currentIndex_, -9);
    MouseClickIndicator(SourceType::MOUSE, FIRST_POINT);
    EXPECT_EQ(pattern_->currentIndex_, -12);
    MouseClickIndicator(SourceType::MOUSE, FOURTH_POINT);
    EXPECT_EQ(pattern_->currentIndex_, -9);
}

/**
 * @tc.name: SwiperIndicatorGetMouseClickIndex004
 * @tc.desc: Test GetMouseClickIndex
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestNg, SwiperIndicatorGetMouseClickIndex004, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetDirection(Axis::HORIZONTAL);
    model.SetBindIndicator(true);
    CreateSwiperItems();
    CreateSwiperDone();
    EXPECT_EQ(indicatorNode_, nullptr);
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    indicatorNode_ = FrameNode::GetOrCreateFrameNode(
        V2::SWIPER_INDICATOR_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<IndicatorPattern>(); });
    EXPECT_NE(indicatorNode_, nullptr);
    auto indicatorPattern = indicatorNode_->GetPattern<IndicatorPattern>();
    auto controller = indicatorPattern->GetIndicatorController();
    controller->SetSwiperNode(frameNode_);
    indicatorPattern->OnModifyDone();
    FlushUITasks();

    /**
     * @tc.steps: step1. call no mirror func.
     */
    layoutProperty_->UpdateLayoutDirection(TextDirection::LTR);

    MouseClickIndicator(SourceType::MOUSE, Offset(72.f, 16.f));
    indicatorPattern->ChangeIndex(0, false);
    FlushUITasks();
    EXPECT_EQ(pattern_->currentIndex_, 0);
    indicatorPattern->GetMouseClickIndex();
    EXPECT_EQ(indicatorPattern->mouseClickIndex_, 3);
    /**
     * @tc.steps: step2. call mirror func.
     */
    MouseClickIndicator(SourceType::MOUSE, Offset(72.f, 16.f));
    layoutProperty_->UpdateLayoutDirection(TextDirection::RTL);
    indicatorPattern->ChangeIndex(3, false);
    FlushUITasks();
    EXPECT_EQ(pattern_->currentIndex_, 3);
    indicatorPattern->GetMouseClickIndex();
    EXPECT_EQ(indicatorPattern->mouseClickIndex_, 0);
}

/**
 * @tc.name: GetIndicatorDragAngleThreshold001
 * @tc.desc: GetIndicatorDragAngleThreshold
 * @tc.type: FUNC
 */
 HWTEST_F(SwiperIndicatorTestNg, GetIndicatorDragAngleThreshold001, TestSize.Level1)
 {
     SwiperModelNG model = CreateSwiper();
     model.SetDirection(Axis::VERTICAL);
     CreateSwiperItems();
     CreateSwiperDone();
     auto indicatorNode = GetChildFrameNode(frameNode_, 4);
     auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
     EXPECT_TRUE(indicatorPattern->GetIndicatorDragAngleThreshold(true));
 }
 
 /**
  * @tc.name: GetIndicatorDragAngleThreshold002
  * @tc.desc: GetIndicatorDragAngleThreshold
  * @tc.type: FUNC
  */
 HWTEST_F(SwiperIndicatorTestNg, GetIndicatorDragAngleThreshold002, TestSize.Level1)
 {
     SwiperModelNG model = CreateSwiper();
     model.SetDirection(Axis::VERTICAL);
     CreateSwiperItems();
     CreateSwiperDone();
     auto indicatorNode = GetChildFrameNode(frameNode_, 4);
     auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
     EXPECT_TRUE(indicatorPattern->GetIndicatorDragAngleThreshold(false));
 }
 
 /**
  * @tc.name: DumpAdvanceInfo001
  * @tc.desc: DumpAdvanceInfo
  * @tc.type: FUNC
  */
 HWTEST_F(SwiperIndicatorTestNg, DumpAdvanceInfo001, TestSize.Level1)
 {
     SwiperModelNG model = CreateSwiper();
     model.SetDirection(Axis::VERTICAL);
     model.SetIndicatorType(SwiperIndicatorType::DOT);
     CreateSwiperItems();
     CreateSwiperDone();
     auto indicatorNode = GetChildFrameNode(frameNode_, 4);
     auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
     auto json = JsonUtil::Create(true);
     EXPECT_EQ(indicatorPattern->GetIndicatorType(), SwiperIndicatorType::DOT);
     indicatorPattern->DumpAdvanceInfo(json);
     EXPECT_EQ(json->GetString("SwiperIndicatorType"), "DOT");
 }
 
 /**
  * @tc.name: DumpAdvanceInfo002
  * @tc.desc: DumpAdvanceInfo
  * @tc.type: FUNC
  */
 HWTEST_F(SwiperIndicatorTestNg, DumpAdvanceInfo002, TestSize.Level1)
 {
     SwiperModelNG model = CreateSwiper();
     model.SetDirection(Axis::VERTICAL);
     model.SetIndicatorType(SwiperIndicatorType::DIGIT);
     CreateSwiperItems();
     CreateSwiperDone();
     auto indicatorNode = GetChildFrameNode(frameNode_, 4);
     auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
     auto json = JsonUtil::Create(true);
     EXPECT_EQ(indicatorPattern->GetIndicatorType(), SwiperIndicatorType::DIGIT);
     indicatorPattern->DumpAdvanceInfo(json);
     EXPECT_EQ(json->GetString("SwiperIndicatorType"), "DIGIT");
 }

/**
 * @tc.name: SwiperIndicatorPatternTestNg0020
 * @tc.desc: CheckIsTouchBottom
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestNg, SwiperIndicatorPatternTestNg0020, TestSize.Level1)
{
    CreateSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    auto indicatorPattern = indicatorNode_->GetPattern<SwiperIndicatorPattern>();
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
 * @tc.desc: CheckIsTouchBottom
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestNg, SwiperIndicatorPatternTestNg0021, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetBindIndicator(true);
    CreateSwiperItems();
    CreateSwiperDone();
    EXPECT_EQ(indicatorNode_, nullptr);
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    indicatorNode_ = FrameNode::GetOrCreateFrameNode(
        V2::SWIPER_INDICATOR_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<IndicatorPattern>(); });
    EXPECT_NE(indicatorNode_, nullptr);
    auto indicatorPattern = indicatorNode_->GetPattern<IndicatorPattern>();
    auto controller = indicatorPattern->GetIndicatorController();
    controller->SetSwiperNode(frameNode_);

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
 * @tc.name: SwiperPatternDisplayIndicatorTotalCount001
 * @tc.desc: DisplayIndicatorTotalCount when SwipeByGroup is false and loop is false
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestNg, SwiperPatternDisplayIndicatorTotalCount001, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetDisplayCount(3);
    model.SetSwipeByGroup(false);
    model.SetLoop(false);
    CreateSwiperItems(6);
    CreateSwiperDone();
    EXPECT_EQ(pattern_->TotalCount(), 6);
    int32_t settingApiVersion = static_cast<int32_t>(PlatformVersion::VERSION_EIGHTEEN);
    int32_t backupApiVersion = MockContainer::Current()->GetApiTargetVersion();
    MockContainer::Current()->SetApiTargetVersion(settingApiVersion);
    EXPECT_EQ(pattern_->DisplayIndicatorTotalCount(), 4);
    MockContainer::Current()->SetApiTargetVersion(backupApiVersion);
}

/**
 * @tc.name: SwiperPatternDisplayIndicatorTotalCount002
 * @tc.desc: DisplayIndicatorTotalCount when SwipeByGroup is true
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestNg, SwiperPatternDisplayIndicatorTotalCount002, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetDisplayCount(4);
    model.SetSwipeByGroup(true);
    model.SetLoop(false);
    CreateSwiperItems(6);
    CreateSwiperDone();
    EXPECT_EQ(pattern_->TotalCount(), 8);
    int32_t settingApiVersion = static_cast<int32_t>(PlatformVersion::VERSION_EIGHTEEN);
    int32_t backupApiVersion = MockContainer::Current()->GetApiTargetVersion();
    MockContainer::Current()->SetApiTargetVersion(settingApiVersion);
    EXPECT_EQ(pattern_->DisplayIndicatorTotalCount(), 2);
    MockContainer::Current()->SetApiTargetVersion(backupApiVersion);
}

/**
 * @tc.name: CalculateGroupTurnPageRate001
 * @tc.desc: Test SwiperPattern CalculateGroupTurnPageRate
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestNg, CalculateGroupTurnPageRate001, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetDisplayCount(2);
    model.SetSwipeByGroup(true);
    model.SetLoop(true);
    CreateSwiperItems(6);
    CreateSwiperDone();

    auto totalCount = pattern_->TotalCount();
    EXPECT_EQ(totalCount, 6);

    float additionalOffset = 0.0f;
    pattern_->contentMainSize_ = SWIPER_WIDTH;

    pattern_->UpdateCurrentOffset(-120.0f);
    FlushUITasks();

    auto groupTurnPageRate = pattern_->CalculateGroupTurnPageRate(additionalOffset);
    EXPECT_EQ(groupTurnPageRate, -0.25f);
}

/**
 * @tc.name: CircleSwiperIndicatorPatternCheckIsTouchBottom001
 * @tc.desc: CheckIsTouchBottom
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestNg, CircleSwiperIndicatorPatternCheckIsTouchBottom001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create swiper and set parameters.
     */
    SwiperModelNG model = CreateArcSwiper();
    model.SetDirection(Axis::VERTICAL);
    CreateSwiperItems();
    CreateSwiperDone();
    auto indicatorPattern = indicatorNode_->GetPattern<ArcSwiperIndicatorPattern>();
    GestureEvent info;
    TouchLocationInfo touchLocationInfo("down", 0);
    touchLocationInfo.SetTouchType(TouchType::DOWN);
    std::list<TouchLocationInfo> infoSwiper;
    infoSwiper.emplace_back(touchLocationInfo);
    TouchEventInfo touchEventInfo("down");
    touchEventInfo.touches_ = infoSwiper;
    indicatorPattern->HandleLongDragUpdate(touchLocationInfo);

    /**
     * @tc.steps: step2. call CheckIsTouchBottom.
     */
    EXPECT_FALSE(indicatorPattern->CheckIsTouchBottom(info));
    EXPECT_TRUE(indicatorPattern->CheckIsTouchBottom(touchEventInfo.GetTouches().front()));
}

/**
 * @tc.name: CircleSwiperIndicatorPatternCheckIsTouchBottom002
 * @tc.desc: CheckIsTouchBottom
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestNg, CircleSwiperIndicatorPatternCheckIsTouchBottom002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create swiper and set parameters.
     */
    SwiperModelNG model = CreateArcSwiper();
    model.SetDirection(Axis::VERTICAL);
    CreateSwiperItems();
    CreateSwiperDone();
    auto indicatorPattern = indicatorNode_->GetPattern<ArcSwiperIndicatorPattern>();
    TouchLocationInfo touchLocationInfo("down", 2);
    indicatorPattern->HandleLongDragUpdate(touchLocationInfo);

    /**
     * @tc.steps: step2. call CheckIsTouchBottom.
     */
    EXPECT_TRUE(indicatorPattern->CheckIsTouchBottom(touchLocationInfo));
}

/**
 * @tc.name: CircleSwiperIndicatorPatternConvertAngleWithArcDirection001
 * @tc.desc: ConvertAngleWithArcDirection
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestNg, CircleSwiperIndicatorPatternConvertAngleWithArcDirection001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create swiper and set parameters.
     */
    SwiperModelNG model = CreateArcSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    auto indicatorPattern = indicatorNode_->GetPattern<ArcSwiperIndicatorPattern>();

    /**
     * @tc.steps: step2. call ConvertAngleWithArcDirection.
     */
    EXPECT_EQ(indicatorPattern->ConvertAngleWithArcDirection(SwiperArcDirection::THREE_CLOCK_DIRECTION, 91.0f),
        179.0f);
    EXPECT_EQ(indicatorPattern->ConvertAngleWithArcDirection(SwiperArcDirection::THREE_CLOCK_DIRECTION, 89.0f),
        -179.0f);
    EXPECT_EQ(indicatorPattern->ConvertAngleWithArcDirection(SwiperArcDirection::NINE_CLOCK_DIRECTION, -91.0f),
        179.0f);
    EXPECT_EQ(indicatorPattern->ConvertAngleWithArcDirection(SwiperArcDirection::NINE_CLOCK_DIRECTION, 1.0f),
        -89.0f);
}

/**
 * @tc.name: DynamicChangeIndicatorType001
 * @tc.desc: Dynamic change indicator type
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestNg, DynamicChangeIndicatorType001, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetIndicatorType(SwiperIndicatorType::DOT);
    CreateSwiperDone();
    FlushUITasks();

    EXPECT_EQ(pattern_->lastSwiperIndicatorType_, SwiperIndicatorType::DOT);

    auto indicatorId = pattern_->GetIndicatorId();
    layoutProperty_->UpdateIndicatorType(SwiperIndicatorType::DIGIT);
    pattern_->InitIndicator();
    FlushUITasks();
    EXPECT_EQ(pattern_->lastSwiperIndicatorType_, SwiperIndicatorType::DIGIT);
    auto newIndicatorId = pattern_->GetIndicatorId();
    EXPECT_NE(indicatorId, newIndicatorId);

    layoutProperty_->UpdateIndicatorType(SwiperIndicatorType::DOT);
    pattern_->InitIndicator();
    FlushUITasks();
    EXPECT_EQ(pattern_->lastSwiperIndicatorType_, SwiperIndicatorType::DOT);
    auto lastIndicatorId = pattern_->GetIndicatorId();
    EXPECT_NE(lastIndicatorId, newIndicatorId);
}

/**
 * @tc.name: CheckPointLocation001
 * @tc.desc: CheckPointLocation
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestNg, CheckPointLocation001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create swiper and set parameters.
     */
    SwiperModelNG model = CreateArcSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    auto indicatorPattern = indicatorNode_->GetPattern<ArcSwiperIndicatorPattern>();

    /**
     * @tc.steps: step2. call CheckPointLocation.
     */
    const PointT<float> center = PointT(float(1.0), float(2.0));
    const PointT<float> point = PointT(float(2.0), float(1.0));
    indicatorPattern->direction_ = SwiperDirection::LEFT;
    auto result = indicatorPattern->CheckPointLocation(center, point);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: CheckPointLocation002
 * @tc.desc: CheckPointLocation
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestNg, CheckPointLocation002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create swiper and set parameters.
     */
    SwiperModelNG model = CreateArcSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    auto indicatorPattern = indicatorNode_->GetPattern<ArcSwiperIndicatorPattern>();

    /**
     * @tc.steps: step2. call CheckPointLocation.
     */
    const PointT<float> center = PointT(float(1.0), float(2.0));
    const PointT<float> point = PointT(float(2.0), float(1.0));
    indicatorPattern->direction_ = SwiperDirection::RIGHT;
    auto result = indicatorPattern->CheckPointLocation(center, point);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: CheckPointLocation003
 * @tc.desc: CheckPointLocation
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestNg, CheckPointLocation003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create swiper and set parameters.
     */
    SwiperModelNG model = CreateArcSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    auto indicatorPattern = indicatorNode_->GetPattern<ArcSwiperIndicatorPattern>();

    /**
     * @tc.steps: step2. call CheckPointLocation.
     */
    const PointT<float> center = PointT(float(1.0), float(2.0));
    const PointT<float> point = PointT(float(0.0), float(1.0));
    indicatorPattern->direction_ = SwiperDirection::LEFT;
    auto result = indicatorPattern->CheckPointLocation(center, point);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: CheckPointLocation004
 * @tc.desc: CheckPointLocation
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestNg, CheckPointLocation004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create swiper and set parameters.
     */
    SwiperModelNG model = CreateArcSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    auto indicatorPattern = indicatorNode_->GetPattern<ArcSwiperIndicatorPattern>();

    /**
     * @tc.steps: step2. call CheckPointLocation.
     */
    const PointT<float> center = PointT(float(1.0), float(0.0));
    const PointT<float> point = PointT(float(2.0), float(1.0));
    indicatorPattern->direction_ = SwiperDirection::LEFT;
    auto result = indicatorPattern->CheckPointLocation(center, point);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: CheckPointLocation005
 * @tc.desc: CheckPointLocation
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestNg, CheckPointLocation005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create swiper and set parameters.
     */
    SwiperModelNG model = CreateArcSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    auto indicatorPattern = indicatorNode_->GetPattern<ArcSwiperIndicatorPattern>();

    /**
     * @tc.steps: step2. call CheckPointLocation.
     */
    const PointT<float> center = PointT(float(1.0), float(0.0));
    const PointT<float> point = PointT(float(0.0), float(1.0));
    indicatorPattern->direction_ = SwiperDirection::RIGHT;
    auto result = indicatorPattern->CheckPointLocation(center, point);
    EXPECT_FALSE(result);
}
} // namespace OHOS::Ace::NG
