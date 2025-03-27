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
class SwiperIndicatorCommon : public SwiperTestNg {
public:
};

/**
 * @tc.name: SwiperIndicatorPattern001
 * @tc.desc: Test OnModifyDone
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorCommon, SwiperIndicatorPattern001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create indicatorPattern and init params
     */
    SwiperModelNG model = CreateSwiper();
    model.SetIndicatorType(SwiperIndicatorType::DOT);
    CreateSwiperItems();
    CreateSwiperDone();
    auto indicatorPattern = indicatorNode_->GetPattern<SwiperIndicatorPattern>();
    auto modifier = AceType::MakeRefPtr<DotIndicatorModifier>();
    indicatorPattern->dotIndicatorModifier_ = modifier;
    ASSERT_NE(indicatorPattern->dotIndicatorModifier_, nullptr);
    modifier->longPointLeftAnimEnd_ = false;
    /**
     * @tc.steps: step2. Call OnModifyDone with longPointLeftAnimEnd_ = false
     * @tc.expected: modifier->longPointLeftAnimEnd_ eq true
     */
    indicatorPattern->OnModifyDone();
    EXPECT_TRUE(modifier->longPointLeftAnimEnd_);
}

/**
 * @tc.name: SwiperIndicatorPattern002
 * @tc.desc: Test InitClickEvent and Handle
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorCommon, SwiperIndicatorPattern002, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetIndicatorType(SwiperIndicatorType::DOT);
    CreateSwiperItems();
    CreateSwiperDone();
    auto eventHub = indicatorNode_->GetOrCreateGestureEventHub();
    auto indicatorPattern = indicatorNode_->GetPattern<SwiperIndicatorPattern>();
    /**
     * @tc.steps: step1. Call InitClickEvent and HandleClick with SourceType::KEYBOARD type
     * @tc.expected: Case SourceType::KEYBOARD and ClickTask executed successfully
     */
    auto actuator = eventHub->clickEventActuator_;
    auto events = actuator->clickEvents_;
    indicatorPattern->InitClickEvent(eventHub);
    EXPECT_GT(events.size(), 0);
    GestureEvent info;
    info.SetSourceDevice(SourceType::KEYBOARD);
    for (const auto& callback : events) {
        (*callback)(info);
    }
    EXPECT_NE(indicatorPattern->clickEvent_, nullptr);
    /**
     * @tc.steps: step2. Call HandleClick with SourceType::MOUSE type
     * @tc.expected: Case SourceType::MOUSE and ClickTask executed successfully and isClicked_ true
     */
    indicatorPattern->isClicked_ = false;
    indicatorPattern->isRepeatClicked_ = false;
    indicatorPattern->mouseClickIndex_ = 0;
    info.SetSourceDevice(SourceType::MOUSE);
    layoutProperty_->UpdateSwipeByGroup(true);
    layoutProperty_->UpdateIndex(0);
    for (const auto& callback : events) {
        (*callback)(info);
    }
    EXPECT_TRUE(indicatorPattern->isClicked_);
    EXPECT_EQ(indicatorPattern->mouseClickIndex_, 0);
}

/**
 * @tc.name: SwiperIndicatorPattern003
 * @tc.desc: Test InitClickEvent and Handle
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorCommon, SwiperIndicatorPattern003, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetIndicatorType(SwiperIndicatorType::DOT);
    CreateSwiperItems();
    CreateSwiperDone();
    auto eventHub = indicatorNode_->GetOrCreateGestureEventHub();
    auto indicatorPattern = indicatorNode_->GetPattern<SwiperIndicatorPattern>();
    auto actuator = eventHub->clickEventActuator_;
    auto events = actuator->clickEvents_;
    indicatorPattern->InitClickEvent(eventHub);
    EXPECT_GT(events.size(), 0);
    GestureEvent info;
    /**
     * @tc.expected: Case SourceType::MOUSE and ClickTask executed successfully and isClicked_ true
     */
    indicatorPattern->isRepeatClicked_ = false;
    indicatorPattern->mouseClickIndex_ = 0;
    info.SetSourceDevice(SourceType::MOUSE);
    layoutProperty_->UpdateSwipeByGroup(true);
    layoutProperty_->UpdateIndex(0);
    indicatorPattern->isClicked_ = false;
    layoutProperty_->UpdateDisplayCount(2);
    indicatorPattern->mouseClickIndex_ = 3;
    for (const auto& callback : events) {
        (*callback)(info);
    }
    EXPECT_TRUE(indicatorPattern->isClicked_);
    EXPECT_EQ(indicatorPattern->mouseClickIndex_, 2);
    /**
     * @tc.expected: Case SourceType::TOUCH and ItemWidth or Selected Neg and ClickTask executed successfully
     */
    info.SetSourceDevice(SourceType::TOUCH);
    auto paintProperty = indicatorNode_->GetPaintProperty<DotIndicatorPaintProperty>();
    paintProperty->UpdateItemWidth(Dimension(-20.f, DimensionUnit::PX));
    for (const auto& callback : events) {
        (*callback)(info);
    }
    EXPECT_NE(indicatorPattern->clickEvent_, nullptr);

    paintProperty->UpdateItemWidth(Dimension(20.f, DimensionUnit::PX));
    paintProperty->UpdateSelectedItemWidth(Dimension(-20.f, DimensionUnit::PX));
    for (const auto& callback : events) {
        (*callback)(info);
    }
    EXPECT_NE(indicatorPattern->clickEvent_, nullptr);
}

/**
 * @tc.name: SwiperIndicatorPattern004
 * @tc.desc: Test HandleTouchEvent with TouchType::CANCEL
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorCommon, SwiperIndicatorPattern004, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetIndicatorType(SwiperIndicatorType::DOT);
    CreateSwiperItems();
    CreateSwiperDone();
    auto indicatorPattern = indicatorNode_->GetPattern<SwiperIndicatorPattern>();
    /**
     * @tc.steps: step1. Simulate touch event with TouchType::CANCEL
     * @tc.expected: HandleTouchEvent correctly handles touch cancel event
     */
    auto touchEventInfo = CreateTouchEventInfo(TouchType::CANCEL, Offset());
    indicatorPattern->isPressed_ = true;
    indicatorPattern->HandleTouchEvent(touchEventInfo);
    EXPECT_FALSE(indicatorPattern->isPressed_);
}

/**
 * @tc.name: SwiperIndicatorPattern005
 * @tc.desc: Test GetCurrentIndex method of SwiperIndicatorPattern
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorCommon, SwiperIndicatorPattern005, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetIndicatorType(SwiperIndicatorType::DOT);
    CreateSwiperItems();
    CreateSwiperDone();
    auto indicatorPattern = indicatorNode_->GetPattern<SwiperIndicatorPattern>();
    /**
     * @tc.steps: step1. Test GetCurrentIndex with SwipeByGroup
     * @tc.expected: currentIndex equals to computed page index
     */
    layoutProperty_->UpdateIndex(0);
    layoutProperty_->UpdateSwipeByGroup(true);
    layoutProperty_->UpdateDisplayCount(2);
    auto currentIndex = indicatorPattern->GetCurrentIndex();
    EXPECT_EQ(currentIndex, 0);
}

/**
 * @tc.name: SwiperIndicatorPattern006
 * @tc.desc: Test UpdateTextContentSub method of SwiperIndicatorPattern
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorCommon, SwiperIndicatorPattern006, TestSize.Level1)
{
    CreateSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    auto indicatorPattern = indicatorNode_->GetPattern<SwiperIndicatorPattern>();
    auto layoutProperty = indicatorNode_->GetLayoutProperty<SwiperIndicatorLayoutProperty>();
    auto firstTextNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    auto lastTextNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    /**
     * @tc.steps: step1. Test currentIndex > swiperPattern->RealTotalCount()
     * @tc.expected: currentIndex is set to 1
     */
    pattern_->currentFirstIndex_ = 3;
    indicatorPattern->UpdateTextContentSub(layoutProperty, firstTextNode, lastTextNode);
    auto firstTextLayoutProperty = firstTextNode->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(firstTextLayoutProperty, nullptr);
    EXPECT_EQ(firstTextLayoutProperty->GetContent().value_or(u""), u"1");

    /**
     * @tc.steps: step2. Test swiperLayoutProperty->HasIndex() and currentIndex > swiperPattern->RealTotalCount()
     * @tc.expected: currentIndex equals to computed page index
     */
    layoutProperty_->UpdateIndex(4);
    indicatorPattern->UpdateTextContentSub(layoutProperty, firstTextNode, lastTextNode);
    firstTextLayoutProperty = firstTextNode->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(firstTextLayoutProperty, nullptr);
    EXPECT_EQ(firstTextLayoutProperty->GetContent().value_or(u""), u"1");
}

/**
 * @tc.name: SwiperIndicatorPattern007
 * @tc.desc: Test HandleDragEnd method of SwiperIndicatorPattern
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorCommon, SwiperIndicatorPattern007, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetIndicatorType(SwiperIndicatorType::DOT);
    CreateSwiperItems();
    CreateSwiperDone();
    auto indicatorPattern = indicatorNode_->GetPattern<SwiperIndicatorPattern>();
    auto swiperPaintProperty = frameNode_->GetPaintProperty<SwiperPaintProperty>();
    pattern_->isIndicatorLongPress_ = true;
    /**
     * @tc.steps: step1. Set AutoPlay to true and call HandleDragEnd
     * @tc.expected: HandleDragEnd correctly handles AutoPlay case
     */
    swiperPaintProperty->UpdateAutoPlay(true);
    indicatorPattern->HandleDragEnd(0.0);
    EXPECT_EQ(pattern_->isIndicatorLongPress_, false);
}

/**
 * @tc.name: SwiperIndicatorPattern008
 * @tc.desc: Test CheckIsTouchBottom method of SwiperIndicatorPattern
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorCommon, SwiperIndicatorPattern008, TestSize.Level1)
{
    CreateSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    auto indicatorPattern = indicatorNode_->GetPattern<SwiperIndicatorPattern>();
    auto childrenSize = pattern_->RealTotalCount();
    auto displayCount = pattern_->GetDisplayCount();
    layoutProperty_->UpdateLoop(false);
    GestureEvent info;
    indicatorPattern->dragStartPoint_.SetX(0.0f);
    indicatorPattern->dragStartPoint_.SetY(0.0f);
    info.SetLocalLocation(Offset(100.f, 100.f));
    /**
     * @tc.steps: step1. Set currentIndex to childrenSize - displayCount and call with Positive main delta
     * @tc.expected: CheckIsTouchBottom returns true and touchBottomType is set to END
     */
    info.SetMainDelta(1.0);
    pattern_->currentIndex_ = childrenSize - displayCount;
    auto result = indicatorPattern->CheckIsTouchBottom(info);
    EXPECT_TRUE(result);
    EXPECT_EQ(indicatorPattern->touchBottomType_, TouchBottomType::END);
    /**
     * @tc.steps: step2. Set currentIndex to childrenSize - displayCount and call with 0 main delta
     * @tc.expected: CheckIsTouchBottom returns true and touchBottomType is set to END
     */
    info.SetMainDelta(0.0);
    pattern_->currentIndex_ = childrenSize - displayCount;
    result = indicatorPattern->CheckIsTouchBottom(info);
    EXPECT_TRUE(result);
    EXPECT_EQ(indicatorPattern->touchBottomType_, TouchBottomType::END);
    /**
     * @tc.steps: step3. Set currentIndex to childrenSize - displayCount and call with Negative
     * @tc.expected: CheckIsTouchBottom returns false
     */
    info.SetMainDelta(-1.0);
    pattern_->currentIndex_ = childrenSize - displayCount;
    info.SetLocalLocation(Offset(-100.0f, -100.0f));
    result = indicatorPattern->CheckIsTouchBottom(info);
    EXPECT_FALSE(result);
    EXPECT_EQ(indicatorPattern->touchBottomType_, TouchBottomType::NONE);
}

/**
 * @tc.name: SwiperIndicatorPattern009
 * @tc.desc: Test CheckIsTouchBottom
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorCommon, SwiperIndicatorPattern009, TestSize.Level1)
{
    CreateSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    auto indicatorPattern = indicatorNode_->GetPattern<SwiperIndicatorPattern>();
    indicatorPattern->dragStartPoint_.SetX(0.0f);
    indicatorPattern->dragStartPoint_.SetY(0.0f);
    layoutProperty_->UpdateLoop(false);
    TouchLocationInfo touchLocationInfo("down", 0);
    touchLocationInfo.SetTouchType(TouchType::DOWN);
    touchLocationInfo.SetLocalLocation(Offset(100.f, 100.f));
    /**
     * @tc.steps: step1. Set currentIndex to 0, set horizontal and right-to-left, and call with positive touch offset
     * @tc.expected: CheckIsTouchBottom returns true and touchBottomType is set to END
     */
    layoutProperty_->UpdateDirection(Axis::HORIZONTAL);
    layoutProperty_->UpdateLayoutDirection(TextDirection::RTL);
    pattern_->currentIndex_ = 0;
    auto result = indicatorPattern->CheckIsTouchBottom(touchLocationInfo);
    EXPECT_TRUE(result);
    EXPECT_EQ(indicatorPattern->touchBottomType_, TouchBottomType::END);

    /**
     * @tc.steps: step2.set horizontal and right-to-left, and call with negpositive touch offset
     * @tc.expected: CheckIsTouchBottom returns false and touchBottomType is set to NONE
     */
    touchLocationInfo.SetLocalLocation(Offset(-100.f, -100.f));
    result = indicatorPattern->CheckIsTouchBottom(touchLocationInfo);
    EXPECT_FALSE(result);
    EXPECT_EQ(indicatorPattern->touchBottomType_, TouchBottomType::NONE);
}

/**
 * @tc.name: SwiperIndicatorPattern010
 * @tc.desc: Test CheckIsTouchBottom
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorCommon, SwiperIndicatorPattern010, TestSize.Level1)
{
    CreateSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    auto indicatorPattern = indicatorNode_->GetPattern<SwiperIndicatorPattern>();
    auto childrenSize = pattern_->RealTotalCount();
    auto displayCount = pattern_->GetDisplayCount();
    indicatorPattern->dragStartPoint_.SetX(0.0f);
    indicatorPattern->dragStartPoint_.SetY(0.0f);
    layoutProperty_->UpdateLoop(false);
    TouchLocationInfo touchLocationInfo("down", 0);
    touchLocationInfo.SetTouchType(TouchType::DOWN);
    touchLocationInfo.SetLocalLocation(Offset(100.f, 100.f));

    /**
     * @tc.steps: step1. Set currentIndex to childrenSize - displayCount with positive touch offset
     * @tc.expected: CheckIsTouchBottom returns false and touchBottomType is set to NONE
     */
    layoutProperty_->UpdateDirection(Axis::HORIZONTAL);
    layoutProperty_->UpdateLayoutDirection(TextDirection::RTL);
    pattern_->currentIndex_ = childrenSize - displayCount;
    auto result = indicatorPattern->CheckIsTouchBottom(touchLocationInfo);
    EXPECT_EQ(indicatorPattern->touchBottomType_, TouchBottomType::NONE);
    EXPECT_FALSE(result);
    /**
     * @tc.steps: step2. Set currentIndex to childrenSize - displayCount with positive touch offset
     * @tc.expected: CheckIsTouchBottom returns true and touchBottomType is set to END
     */
    pattern_->currentIndex_ = childrenSize - displayCount;
    touchLocationInfo.SetLocalLocation(Offset(-100.f, -100.f));
    result = indicatorPattern->CheckIsTouchBottom(touchLocationInfo);
    EXPECT_TRUE(result);
    EXPECT_EQ(indicatorPattern->touchBottomType_, TouchBottomType::START);
}

/**
 * @tc.name: SwiperIndicatorPattern011
 * @tc.desc: Test CheckIsTouchBottom
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorCommon, SwiperIndicatorPattern011, TestSize.Level1)
{
    CreateSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    auto indicatorPattern = indicatorNode_->GetPattern<SwiperIndicatorPattern>();
    auto childrenSize = pattern_->RealTotalCount();
    auto displayCount = pattern_->GetDisplayCount();
    indicatorPattern->dragStartPoint_.SetX(0.0f);
    indicatorPattern->dragStartPoint_.SetY(0.0f);
    layoutProperty_->UpdateLoop(false);
    TouchLocationInfo touchLocationInfo("down", 0);
    touchLocationInfo.SetTouchType(TouchType::DOWN);
    touchLocationInfo.SetLocalLocation(Offset(100.f, 100.f));

    /**
     * @tc.steps: step1. Set currentIndex to childrenSize - displayCount with positive touch offset
     * @tc.expected: CheckIsTouchBottom returns true and touchBottomType is set to END
     */
    layoutProperty_->UpdateDirection(Axis::HORIZONTAL);
    layoutProperty_->UpdateLayoutDirection(TextDirection::LTR);
    pattern_->currentIndex_ = childrenSize - displayCount;
    auto result = indicatorPattern->CheckIsTouchBottom(touchLocationInfo);
    EXPECT_TRUE(result);
    EXPECT_EQ(indicatorPattern->touchBottomType_, TouchBottomType::END);
    /**
     * @tc.steps: step2. Set currentIndex to childrenSize - displayCount with negpositive touch offset
     * @tc.expected: CheckIsTouchBottom returns false and touchBottomType is set to None
     */
    pattern_->currentIndex_ = childrenSize - displayCount;
    touchLocationInfo.SetLocalLocation(Offset(-100.f, -100.f));
    result = indicatorPattern->CheckIsTouchBottom(touchLocationInfo);
    EXPECT_FALSE(result);
    EXPECT_EQ(indicatorPattern->touchBottomType_, TouchBottomType::NONE);
}

/**
 * @tc.name: SwiperIndicatorPattern012
 * @tc.desc: Test InitLongPressEvent
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorCommon, SwiperIndicatorPattern012, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetIndicatorType(SwiperIndicatorType::DOT);
    CreateSwiperItems();
    CreateSwiperDone();
    auto eventHub = indicatorNode_->GetOrCreateGestureEventHub();
    auto indicatorPattern = indicatorNode_->GetPattern<SwiperIndicatorPattern>();
    indicatorPattern->isPressed_ = false;
    GestureEvent info;
    info.SetLocalLocation(Offset(100.f, 100.f));
    pattern_->isIndicatorLongPress_ = false;
    pattern_->isInAutoPlay_ = true;
    /**
     * @tc.steps: step1. Call InitLongPressEvent and trigger HandleLongPress
     * @tc.expected: LongPress event is set and handled correctly with autoPlay true
     */
    auto swiperPaintProperty = frameNode_->GetPaintProperty<SwiperPaintProperty>();
    swiperPaintProperty->UpdateAutoPlay(true);
    indicatorPattern->InitLongPressEvent(eventHub);
    ASSERT_NE(indicatorPattern->longPressEvent_, nullptr);
    auto actuator = eventHub->longPressEventActuator_;
    auto event = actuator->longPressEvent_;
    ASSERT_NE(event, nullptr);
    (*event)(info);
    EXPECT_TRUE(indicatorPattern->isPressed_);
    EXPECT_TRUE(pattern_->isIndicatorLongPress_);
    EXPECT_FALSE(pattern_->isInAutoPlay_);
}

/**
 * @tc.name: SwiperIndicatorPattern013
 * @tc.desc: Test HandleLongDragUpdate method
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorCommon, SwiperIndicatorPattern013, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetDisplayCount(4);
    CreateSwiperItems();
    CreateSwiperDone();
    auto indicatorPattern = indicatorNode_->GetPattern<SwiperIndicatorPattern>();
    pattern_->indicatorAnimationIsRunning_ = true;
    TouchLocationInfo touchLocationInfo("down", 0);
    /**
     * @tc.steps: step1. Call HandleLongDragUpdate when IsIndicatorAnimatorRunning returns true
     * @tc.expected: return from HandleLongDragUpdate
     */
    indicatorPattern->HandleLongDragUpdate(touchLocationInfo);
    EXPECT_TRUE(pattern_->IsIndicatorAnimatorRunning());
    pattern_->indicatorAnimationIsRunning_ = false;
    /**
     * @tc.steps: step2. Call HandleLongDragUpdate when RealTotalCount equals displayCount
     * @tc.expected: return from HandleLongDragUpdate
     */
    indicatorPattern->HandleLongDragUpdate(touchLocationInfo);
    EXPECT_EQ(pattern_->RealTotalCount(), 4);
    layoutProperty_->UpdateDisplayCount(2);
    ChangeIndex(2);
    /**
     * @tc.steps: step3. Call HandleLongDragUpdate when CheckIsTouchBottom returns true
     * @tc.expected: return from HandleLongDragUpdate
     */
    indicatorPattern->dragStartPoint_.SetX(0.0f);
    indicatorPattern->dragStartPoint_.SetY(0.0f);
    touchLocationInfo.SetLocalLocation(Offset(100.f, 100.f));
    indicatorPattern->HandleLongDragUpdate(touchLocationInfo);
    EXPECT_EQ(indicatorPattern->touchBottomType_, TouchBottomType::END);
}

/**
 * @tc.name: SwiperIndicatorPattern014
 * @tc.desc: Test the method DumpAdvanceInfo
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorCommon, SwiperIndicatorPattern014, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetIndicatorType(SwiperIndicatorType::DOT);
    CreateSwiperItems();
    CreateSwiperDone();
    auto indicatorPattern = indicatorNode_->GetPattern<SwiperIndicatorPattern>();
    /**
     * @tc.steps: step1. set boolean values.
     */
    indicatorPattern->isHover_ = true;
    indicatorPattern->isPressed_ = false;
    indicatorPattern->isClicked_ = true;
    indicatorPattern->isRepeatClicked_ = false;
    /**
     * @tc.steps: step2. call the function DumpAdvanceInfo.
     * @tc.expected: verify the size dumped correctly.
     */
    DumpLog::GetInstance().description_.clear();
    indicatorPattern->DumpAdvanceInfo();
    EXPECT_EQ(DumpLog::GetInstance().description_.size(), 5);
    /**
     * @tc.steps: step3. call the function DumpAdvanceInfo.
     * @tc.expected: verify the size dumped correctly.
     */
    DumpLog::GetInstance().description_.clear();
    indicatorPattern->isHover_ = false;
    indicatorPattern->isPressed_ = true;
    indicatorPattern->isClicked_ = false;
    indicatorPattern->isRepeatClicked_ = true;
    indicatorPattern->DumpAdvanceInfo();
    EXPECT_EQ(DumpLog::GetInstance().description_.size(), 5);
}

/**
 * @tc.name: SwiperIndicatorPattern015
 * @tc.desc: Test the method CreateOverlongDotIndicatorPaintMethod
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorCommon, SwiperIndicatorPattern015, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetIndicatorType(SwiperIndicatorType::DOT);
    CreateSwiperItems();
    CreateSwiperDone();
    auto indicatorPattern = indicatorNode_->GetPattern<SwiperIndicatorPattern>();
    /**
     * @tc.steps: step1. Test when dotIndicatorModifier_ is not null and overlongDotIndicatorModifier_ is null.
     * @tc.expected: dotIndicatorModifier_ methods are called, overlongDotIndicatorModifier_ is created.
     */
    indicatorPattern->dotIndicatorModifier_ = AceType::MakeRefPtr<DotIndicatorModifier>();
    indicatorPattern->overlongDotIndicatorModifier_ = nullptr;
    auto result = indicatorPattern->CreateOverlongDotIndicatorPaintMethod(pattern_);
    EXPECT_EQ(indicatorPattern->dotIndicatorModifier_, nullptr);
    EXPECT_NE(indicatorPattern->overlongDotIndicatorModifier_, nullptr);
    EXPECT_NE(result, nullptr);
    /**
     * @tc.steps: step2. Test when dotIndicatorModifier_ is not null and overlongDotIndicatorModifier_ is not null.
     * @tc.expected: dotIndicatorModifier_ methods are called, overlongDotIndicatorModifier_ is reused.
     */
    indicatorPattern->dotIndicatorModifier_ = AceType::MakeRefPtr<DotIndicatorModifier>();
    indicatorPattern->overlongDotIndicatorModifier_ = AceType::MakeRefPtr<OverlengthDotIndicatorModifier>();
    result = indicatorPattern->CreateOverlongDotIndicatorPaintMethod(pattern_);
    EXPECT_EQ(indicatorPattern->dotIndicatorModifier_, nullptr);
    EXPECT_NE(indicatorPattern->overlongDotIndicatorModifier_, nullptr);
    EXPECT_NE(result, nullptr);

    /**
     * @tc.steps: step3. Test when dotIndicatorModifier_ is null and overlongDotIndicatorModifier_ is null.
     * @tc.expected: overlongDotIndicatorModifier_ is created.
     */
    indicatorPattern->dotIndicatorModifier_ = nullptr;
    indicatorPattern->overlongDotIndicatorModifier_ = nullptr;
    result = indicatorPattern->CreateOverlongDotIndicatorPaintMethod(pattern_);
    EXPECT_NE(result, nullptr);
    EXPECT_NE(indicatorPattern->overlongDotIndicatorModifier_, nullptr);
    /**
     * @tc.steps: step4. Test when dotIndicatorModifier_ is null and overlongDotIndicatorModifier_ is not null.
     * @tc.expected: overlongDotIndicatorModifier_ is reused.
     */
    indicatorPattern->dotIndicatorModifier_ = nullptr;
    indicatorPattern->overlongDotIndicatorModifier_ = AceType::MakeRefPtr<OverlengthDotIndicatorModifier>();
    result = indicatorPattern->CreateOverlongDotIndicatorPaintMethod(pattern_);
    EXPECT_NE(result, nullptr);
    EXPECT_NE(indicatorPattern->overlongDotIndicatorModifier_, nullptr);
}

/**
 * @tc.name: SwiperIndicatorPattern016
 * @tc.desc: Test CreateDotIndicatorPaintMethod
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorCommon, SwiperIndicatorPattern016, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetIndicatorType(SwiperIndicatorType::DOT);
    CreateSwiperItems();
    CreateSwiperDone();
    auto indicatorPattern = indicatorNode_->GetPattern<SwiperIndicatorPattern>();
    /**
     * @tc.steps: step1. Test when overlongDotIndicatorModifier_ is not null
     * @tc.expected: overlongDotIndicatorModifier_ methods are called
     */
    indicatorPattern->overlongDotIndicatorModifier_ = AceType::MakeRefPtr<OverlengthDotIndicatorModifier>();
    indicatorPattern->CreateDotIndicatorPaintMethod(pattern_);
    EXPECT_EQ(indicatorPattern->overlongDotIndicatorModifier_, nullptr);
}

/**
 * @tc.name: SwiperIndicatorPattern017
 * @tc.desc: Test UpdateOverlongPaintMethod method
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorCommon, SwiperIndicatorPattern017, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetIndicatorType(SwiperIndicatorType::DOT);
    CreateSwiperItems();
    CreateSwiperDone();
    auto indicatorPattern = indicatorNode_->GetPattern<SwiperIndicatorPattern>();
    auto modifier = AceType::MakeRefPtr<OverlengthDotIndicatorModifier>();
    auto overlongPaintMethod = AceType::MakeRefPtr<OverlengthDotIndicatorPaintMethod>(modifier);
    indicatorPattern->overlongDotIndicatorModifier_ = modifier;
    /**
     * @tc.steps: step1. Set changeIndexWithAnimation_ to false and call UpdateOverlongPaintMethod.
     * @tc.expected: changeIndexWithAnimation_ logic is executed.
     */
    indicatorPattern->changeIndexWithAnimation_ = false;
    indicatorPattern->jumpIndex_.reset();
    overlongPaintMethod->gestureState_ = GestureState::GESTURE_STATE_INIT;
    EXPECT_EQ(pattern_->GetCurrentIndex(), 0);
    EXPECT_EQ(pattern_->GetCurrentFirstIndex(), 0);
    indicatorPattern->UpdateOverlongPaintMethod(pattern_, overlongPaintMethod);
    EXPECT_EQ(overlongPaintMethod->gestureState_, GestureState::GESTURE_STATE_NONE);
    /**
     * @tc.steps: step2. Set changeIndexWithAnimation_ to true and call UpdateOverlongPaintMethod.
     * @tc.expected: changeIndexWithAnimation_ logic is not executed.
     */
    indicatorPattern->changeIndexWithAnimation_ = true;
    indicatorPattern->jumpIndex_.reset();
    overlongPaintMethod->gestureState_ = GestureState::GESTURE_STATE_INIT;
    indicatorPattern->UpdateOverlongPaintMethod(pattern_, overlongPaintMethod);
    EXPECT_EQ(overlongPaintMethod->gestureState_, GestureState::GESTURE_STATE_INIT);
}

/**
 * @tc.name: SwiperIndicatorPattern018
 * @tc.desc: Test UpdateOverlongPaintMethod method
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorCommon, SwiperIndicatorPattern018, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetIndicatorType(SwiperIndicatorType::DOT);
    CreateSwiperItems();
    CreateSwiperDone();
    auto indicatorPattern = indicatorNode_->GetPattern<SwiperIndicatorPattern>();
    auto modifier = AceType::MakeRefPtr<OverlengthDotIndicatorModifier>();
    auto overlongPaintMethod = AceType::MakeRefPtr<OverlengthDotIndicatorPaintMethod>(modifier);
    indicatorPattern->overlongDotIndicatorModifier_ = modifier;
    /**
     * @tc.steps: step1. Set changeIndexWithAnimation_ to false and jumpIndex_ = 1 and call UpdateOverlongPaintMethod.
     * @tc.expected: changeIndexWithAnimation_ and jumpIndex_ logic is executed.
     */
    modifier->longPointLeftAnimEnd_ = false;
    indicatorPattern->changeIndexWithAnimation_ = false;
    indicatorPattern->jumpIndex_ = 1;
    overlongPaintMethod->gestureState_ = GestureState::GESTURE_STATE_INIT;
    modifier->currentOverlongType_ = OverlongType::LEFT_NORMAL_RIGHT_FADEOUT;
    EXPECT_EQ(pattern_->GetCurrentIndex(), 0);
    EXPECT_EQ(pattern_->GetCurrentFirstIndex(), 0);
    indicatorPattern->UpdateOverlongPaintMethod(pattern_, overlongPaintMethod);
    EXPECT_EQ(overlongPaintMethod->gestureState_, GestureState::GESTURE_STATE_NONE);
    EXPECT_FALSE(modifier->longPointLeftAnimEnd_);

    /**
     * @tc.steps: step2. Set changeIndexWithAnimation_ no value and jumpIndex_ = 1 and call UpdateOverlongPaintMethod.
     * @tc.expected: changeIndexWithAnimation_ and jumpIndex_ logic is executed.
     */
    modifier->longPointLeftAnimEnd_ = false;
    indicatorPattern->changeIndexWithAnimation_.reset();
    indicatorPattern->jumpIndex_ = 1;
    overlongPaintMethod->gestureState_ = GestureState::GESTURE_STATE_INIT;
    modifier->currentOverlongType_ = OverlongType::LEFT_NORMAL_RIGHT_FADEOUT;
    indicatorPattern->UpdateOverlongPaintMethod(pattern_, overlongPaintMethod);
    EXPECT_EQ(overlongPaintMethod->gestureState_, GestureState::GESTURE_STATE_NONE);
    EXPECT_TRUE(modifier->longPointLeftAnimEnd_);
}

/**
 * @tc.name: SwiperIndicatorPattern019
 * @tc.desc: Test UpdateOverlongPaintMethod method
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorCommon, SwiperIndicatorPattern019, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetIndicatorType(SwiperIndicatorType::DOT);
    CreateSwiperItems();
    CreateSwiperDone();
    auto indicatorPattern = indicatorNode_->GetPattern<SwiperIndicatorPattern>();
    auto modifier = AceType::MakeRefPtr<OverlengthDotIndicatorModifier>();
    auto overlongPaintMethod = AceType::MakeRefPtr<OverlengthDotIndicatorPaintMethod>(modifier);
    indicatorPattern->overlongDotIndicatorModifier_ = modifier;
    /**
     * @tc.steps: step1. Set changeIndexWithAnimation_ to true and jumpIndex_ = 1 and call UpdateOverlongPaintMethod.
     * @tc.expected:jumpIndex_ logic is executed.
     */
    modifier->longPointLeftAnimEnd_ = false;
    indicatorPattern->changeIndexWithAnimation_ = true;
    indicatorPattern->jumpIndex_ = 1;
    overlongPaintMethod->gestureState_ = GestureState::GESTURE_STATE_INIT;
    modifier->currentOverlongType_ = OverlongType::LEFT_NORMAL_RIGHT_FADEOUT;
    EXPECT_EQ(pattern_->GetCurrentIndex(), 0);
    EXPECT_EQ(pattern_->GetCurrentFirstIndex(), 0);
    indicatorPattern->UpdateOverlongPaintMethod(pattern_, overlongPaintMethod);
    EXPECT_EQ(overlongPaintMethod->gestureState_, GestureState::GESTURE_STATE_NONE);
    EXPECT_FALSE(modifier->longPointLeftAnimEnd_);
    /**
     * @tc.steps: step2. Set changeIndexWithAnimation_ no value and jumpIndex_ = 1 and call UpdateOverlongPaintMethod.
     * @tc.expected: jumpIndex_ logic is executed.
     */
    modifier->longPointLeftAnimEnd_ = false;
    indicatorPattern->changeIndexWithAnimation_.reset();
    indicatorPattern->jumpIndex_ = 1;
    overlongPaintMethod->gestureState_ = GestureState::GESTURE_STATE_INIT;
    modifier->currentOverlongType_ = OverlongType::LEFT_NORMAL_RIGHT_FADEOUT;
    indicatorPattern->UpdateOverlongPaintMethod(pattern_, overlongPaintMethod);
    EXPECT_EQ(overlongPaintMethod->gestureState_, GestureState::GESTURE_STATE_NONE);
    EXPECT_TRUE(modifier->longPointLeftAnimEnd_);
}

/**
 * @tc.name: UpdateTextContentSub001
 * @tc.desc: Test UpdateTextContentSub method of SwiperIndicatorPattern
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorCommon, UpdateTextContentSub001, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetIndicatorType(SwiperIndicatorType::DIGIT);
    model.SetSwipeByGroup(true);
    model.SetDisplayCount(3);
    CreateSwiperItems();
    CreateSwiperDone();

    auto indicatorPattern = indicatorNode_->GetPattern<SwiperIndicatorPattern>();
    auto layoutProperty = indicatorNode_->GetLayoutProperty<SwiperIndicatorLayoutProperty>();
    auto firstTextNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    auto lastTextNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    indicatorPattern->UpdateTextContentSub(layoutProperty, firstTextNode, lastTextNode);
    auto lastTextLayoutProperty = lastTextNode->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(lastTextLayoutProperty, nullptr);
    EXPECT_EQ(lastTextLayoutProperty->GetContent().value_or(u""), u"/4");
}

/**
 * @tc.name: UpdateTextContentSub002
 * @tc.desc: Test UpdateTextContentSub method of SwiperIndicatorPattern
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorCommon, UpdateTextContentSub002, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetIndicatorType(SwiperIndicatorType::DIGIT);
    model.SetSwipeByGroup(true);
    model.SetDisplayCount(3);
    model.SetIndex(2);
    CreateSwiperItems();
    CreateSwiperDone();

    auto indicatorPattern = indicatorNode_->GetPattern<SwiperIndicatorPattern>();
    auto layoutProperty = indicatorNode_->GetLayoutProperty<SwiperIndicatorLayoutProperty>();
    auto firstTextNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    auto lastTextNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    indicatorPattern->UpdateTextContentSub(layoutProperty, firstTextNode, lastTextNode);
    auto firstTextLayoutProperty = firstTextNode->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(firstTextLayoutProperty, nullptr);
    EXPECT_EQ(firstTextLayoutProperty->GetContent().value_or(u""), u"1");
}

/**
 * @tc.name: SwiperIndicatorPattern020
 * @tc.desc: Test HandleLongDragUpdate when SwipeByGroup is true
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorCommon, SwiperIndicatorPattern020, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetDisplayCount(2);
    model.SetSwipeByGroup(true);
    CreateSwiperItems();
    CreateSwiperDone();

    auto indicatorPattern = indicatorNode_->GetPattern<SwiperIndicatorPattern>();
    ASSERT_NE(indicatorPattern, nullptr);
    ASSERT_NE(pattern_, nullptr);

    int32_t settingApiVersion = static_cast<int32_t>(PlatformVersion::VERSION_EIGHTEEN);
    int32_t backupApiVersion = MockContainer::Current()->GetApiTargetVersion();
    MockContainer::Current()->SetApiTargetVersion(settingApiVersion);

    TouchEventInfo touchEventInfo("default");
    TouchLocationInfo touchLocationInfo("down", 0);
    touchLocationInfo.SetLocalLocation(Offset(18.0f, 1.0f));
    touchEventInfo.AddTouchLocationInfo(std::move(touchLocationInfo));

    GestureEvent info;
    info.SetLocalLocation(Offset(0.0f, 1.0f));
    indicatorPattern->HandleTouchDown();
    indicatorPattern->HandleDragStart(info);
    indicatorPattern->HandleTouchEvent(touchEventInfo);
    EXPECT_EQ(pattern_->jumpIndex_.value(), 2);
    MockContainer::Current()->SetApiTargetVersion(backupApiVersion);
}
} // namespace OHOS::Ace::NG
