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

namespace OHOS::Ace::NG {
class SwiperCommonTestTwoNg : public SwiperTestNg {
public:
    AssertionResult IsEqualNextFocusNode(
        FocusStep step, const RefPtr<FrameNode>& currentNode, const RefPtr<FrameNode>& expectNextNode);
    void OnKeyEvent(KeyCode keyCode, KeyAction keyAction);
    void SetOnMainTree();
};

AssertionResult SwiperCommonTestTwoNg::IsEqualNextFocusNode(
    FocusStep step, const RefPtr<FrameNode>& currentNode, const RefPtr<FrameNode>& expectNextNode)
{
    RefPtr<FocusHub> currentFocusNode = currentNode->GetOrCreateFocusHub();
    currentFocusNode->RequestFocusImmediately();
    RefPtr<FocusHub> nextFocusNode = pattern_->GetNextFocusNode(step, currentFocusNode).Upgrade();
    if (expectNextNode == nullptr && nextFocusNode != nullptr) {
        return AssertionFailure() << "Next focusNode is not null";
    }
    if (expectNextNode != nullptr && nextFocusNode != expectNextNode->GetOrCreateFocusHub()) {
        return AssertionFailure() << "Next focusNode is not as expected";
    }
    return AssertionSuccess();
}

void SwiperCommonTestTwoNg::SetOnMainTree()
{
    if (indicatorNode_) {
        indicatorNode_->onMainTree_ = true;
    }
    if (leftArrowNode_) {
        leftArrowNode_->onMainTree_ = true;
    }
    if (rightArrowNode_) {
        rightArrowNode_->onMainTree_ = true;
    }
}

void SwiperCommonTestTwoNg::OnKeyEvent(KeyCode keyCode, KeyAction keyAction)
{
    auto focusHub = frameNode_->GetFocusHub();
    focusHub->ProcessOnKeyEventInternal(KeyEvent(keyCode, keyAction));
    FlushUITasks();
}

/**
 * @tc.name: ShowCachedItems009
 * @tc.desc: Test show cached items on loop = true, displayCount = 3
 * @tc.type: FUNC
 */
HWTEST_F(SwiperCommonTestTwoNg, ShowCachedItems009, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetLoop(true);
    model.SetCachedIsShown(true);
    model.SetDisplayCount(3);
    model.SetCachedCount(1);
    model.SetIndex(0);
    CreateSwiperItems(10);
    CreateSwiperDone();
    FlushUITasks();

    ASSERT_EQ(static_cast<int32_t>(pattern_->itemPosition_.size()), 5);
    EXPECT_EQ(pattern_->itemPosition_[-1].startPos, -160.0f);
    EXPECT_EQ(pattern_->itemPosition_[0].startPos, 0.0f);
    EXPECT_EQ(pattern_->itemPosition_[1].startPos, 160.0f);
    EXPECT_EQ(pattern_->itemPosition_[2].startPos, 320.0f);
    EXPECT_EQ(pattern_->itemPosition_[3].startPos, 480.0f);

    pattern_->UpdateCurrentOffset(-100.0f);
    FlushUITasks();
    ASSERT_EQ(static_cast<int32_t>(pattern_->itemPosition_.size()), 6);
    EXPECT_EQ(pattern_->itemPosition_[-1].startPos, -260.0f);
    EXPECT_EQ(pattern_->itemPosition_[0].startPos, -100.0f);
    EXPECT_EQ(pattern_->itemPosition_[1].startPos, 60.0f);
    EXPECT_EQ(pattern_->itemPosition_[2].startPos, 220.0f);
    EXPECT_EQ(pattern_->itemPosition_[3].startPos, 380.0f);
    EXPECT_EQ(pattern_->itemPosition_[4].startPos, 540.0f);

    pattern_->UpdateCurrentOffset(-100.0f);
    FlushUITasks();
    ASSERT_EQ(static_cast<int32_t>(pattern_->itemPosition_.size()), 6);
    EXPECT_EQ(pattern_->itemPosition_[0].startPos, -200.0f);
    EXPECT_EQ(pattern_->itemPosition_[1].startPos, -40.0f);
    EXPECT_EQ(pattern_->itemPosition_[2].startPos, 120.0f);
    EXPECT_EQ(pattern_->itemPosition_[3].startPos, 280.0f);
    EXPECT_EQ(pattern_->itemPosition_[4].startPos, 440.0f);
    EXPECT_EQ(pattern_->itemPosition_[5].startPos, 600.0f);

    pattern_->ChangeIndex(7, false);
    FlushUITasks();
    ASSERT_EQ(static_cast<int32_t>(pattern_->itemPosition_.size()), 5);
    EXPECT_EQ(pattern_->itemPosition_[6].startPos, -160.0f);
    EXPECT_EQ(pattern_->itemPosition_[7].startPos, 0.0f);
    EXPECT_EQ(pattern_->itemPosition_[8].startPos, 160.0f);
    EXPECT_EQ(pattern_->itemPosition_[9].startPos, 320.0f);
    EXPECT_EQ(pattern_->itemPosition_[10].startPos, 480.0f);
}

/**
 * @tc.name: ShowCachedItems010
 * @tc.desc: Test show cached items on loop = true, cachedCount = 2, set nextMargin and prevMargin
 * @tc.type: FUNC
 */
HWTEST_F(SwiperCommonTestTwoNg, ShowCachedItems010, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetLoop(true);
    model.SetCachedIsShown(true);
    model.SetDisplayCount(1);
    model.SetCachedCount(2);
    model.SetIndex(0);
    model.SetNextMargin(Dimension(10, DimensionUnit::PX), false);
    model.SetPreviousMargin(Dimension(10, DimensionUnit::PX), false);
    model.SetItemSpace(Dimension(10, DimensionUnit::PX));
    CreateSwiperItems(10);
    CreateSwiperDone();
    FlushUITasks();

    ASSERT_EQ(static_cast<int32_t>(pattern_->itemPosition_.size()), 7);
    EXPECT_EQ(pattern_->itemPosition_[-3].startPos, -1350.0f);
    EXPECT_EQ(pattern_->itemPosition_[-2].startPos, -900.0f);
    EXPECT_EQ(pattern_->itemPosition_[-1].startPos, -450.0f);
    EXPECT_EQ(pattern_->itemPosition_[-1].endPos, -10.0f);
    EXPECT_EQ(pattern_->itemPosition_[0].startPos, 0.0f);
    EXPECT_EQ(pattern_->itemPosition_[0].endPos, 440.0f);
    EXPECT_EQ(pattern_->itemPosition_[1].startPos, 450.0f);
    EXPECT_EQ(pattern_->itemPosition_[2].startPos, 900.0f);
    EXPECT_EQ(pattern_->itemPosition_[3].startPos, 1350.0f);

    pattern_->UpdateCurrentOffset(-100.0f);
    FlushUITasks();
    ASSERT_EQ(static_cast<int32_t>(pattern_->itemPosition_.size()), 6);
    EXPECT_EQ(pattern_->itemPosition_[-2].startPos, -1000.0f);
    EXPECT_EQ(pattern_->itemPosition_[-1].startPos, -550.0f);
    EXPECT_EQ(pattern_->itemPosition_[0].startPos, -100.0f);
    EXPECT_EQ(pattern_->itemPosition_[1].startPos, 350.0f);
    EXPECT_EQ(pattern_->itemPosition_[2].startPos, 800.0f);
    EXPECT_EQ(pattern_->itemPosition_[3].startPos, 1250.0f);

    pattern_->ChangeIndex(6, false);
    FlushUITasks();
    ASSERT_EQ(static_cast<int32_t>(pattern_->itemPosition_.size()), 7);
    EXPECT_EQ(pattern_->itemPosition_[3].startPos, -1350.0f);
    EXPECT_EQ(pattern_->itemPosition_[4].startPos, -900.0f);
    EXPECT_EQ(pattern_->itemPosition_[5].startPos, -450.0f);
    EXPECT_EQ(pattern_->itemPosition_[6].startPos, 0.0f);
    EXPECT_EQ(pattern_->itemPosition_[7].startPos, 450.0f);
    EXPECT_EQ(pattern_->itemPosition_[8].startPos, 900.0f);
    EXPECT_EQ(pattern_->itemPosition_[9].startPos, 1350.0f);

    pattern_->ChangeIndex(9, false);
    FlushUITasks();
    ASSERT_EQ(static_cast<int32_t>(pattern_->itemPosition_.size()), 7);
    EXPECT_EQ(pattern_->itemPosition_[6].startPos, -1350.0f);
    EXPECT_EQ(pattern_->itemPosition_[7].startPos, -900.0f);
    EXPECT_EQ(pattern_->itemPosition_[8].startPos, -450.0f);
    EXPECT_EQ(pattern_->itemPosition_[9].startPos, 0.0f);
    EXPECT_EQ(pattern_->itemPosition_[10].startPos, 450.0f);
    EXPECT_EQ(pattern_->itemPosition_[11].startPos, 900.0f);
    EXPECT_EQ(pattern_->itemPosition_[12].startPos, 1350.0f);
}

/**
 * @tc.name: ShowCachedItems011
 * @tc.desc: Test show cached items on RTL, loop = true, cachedCount = 1
 * @tc.type: FUNC
 */
HWTEST_F(SwiperCommonTestTwoNg, ShowCachedItems011, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetLoop(true);
    model.SetCachedIsShown(true);
    model.SetDisplayCount(1);
    model.SetCachedCount(1);
    model.SetIndex(0);
    CreateSwiperItems(5);
    CreateSwiperDone();
    layoutProperty_->UpdateLayoutDirection(TextDirection::RTL);
    FlushUITasks();

    ASSERT_EQ(static_cast<int32_t>(pattern_->itemPosition_.size()), 3);
    EXPECT_EQ(pattern_->itemPosition_[-1].startPos, -480.0f);
    EXPECT_EQ(pattern_->itemPosition_[0].startPos, 0.0f);
    EXPECT_EQ(pattern_->itemPosition_[1].startPos, 480.0f);

    pattern_->UpdateCurrentOffset(100.0f);
    FlushUITasks();
    ASSERT_EQ(static_cast<int32_t>(pattern_->itemPosition_.size()), 4);
    EXPECT_EQ(pattern_->itemPosition_[-2].startPos, -860.0f);
    EXPECT_EQ(pattern_->itemPosition_[-1].startPos, -380.0f);
    EXPECT_EQ(pattern_->itemPosition_[0].startPos, 100.0f);
    EXPECT_EQ(pattern_->itemPosition_[1].startPos, 580.0f);

    pattern_->ChangeIndex(4, false);
    FlushUITasks();
    ASSERT_EQ(static_cast<int32_t>(pattern_->itemPosition_.size()), 3);
    EXPECT_EQ(pattern_->itemPosition_[3].startPos, -480.0f);
    EXPECT_EQ(pattern_->itemPosition_[4].startPos, 0.0f);
    EXPECT_EQ(pattern_->itemPosition_[5].startPos, 480.0f);

    pattern_->UpdateCurrentOffset(100.0f);
    FlushUITasks();
    ASSERT_EQ(static_cast<int32_t>(pattern_->itemPosition_.size()), 4);
    EXPECT_EQ(pattern_->itemPosition_[2].startPos, -860.0f);
    EXPECT_EQ(pattern_->itemPosition_[3].startPos, -380.0f);
    EXPECT_EQ(pattern_->itemPosition_[4].startPos, 100.0f);
    EXPECT_EQ(pattern_->itemPosition_[5].startPos, 580.0f);
}

/**
 * @tc.name: ShowCachedItems012
 * @tc.desc: Test show cached items on RTL, loop = true, cachedCount = 2
 * @tc.type: FUNC
 */
HWTEST_F(SwiperCommonTestTwoNg, ShowCachedItems012, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetLoop(true);
    model.SetCachedIsShown(true);
    model.SetDisplayCount(1);
    model.SetCachedCount(2);
    model.SetIndex(1);
    CreateSwiperItems(5);
    CreateSwiperDone();

    layoutProperty_->UpdateLayoutDirection(TextDirection::RTL);
    FlushUITasks();

    ASSERT_EQ(static_cast<int32_t>(pattern_->itemPosition_.size()), 5);
    EXPECT_EQ(pattern_->itemPosition_[-1].startPos, -960.0f);
    EXPECT_EQ(pattern_->itemPosition_[0].startPos, -480.0f);
    EXPECT_EQ(pattern_->itemPosition_[1].startPos, 0.0f);
    EXPECT_EQ(pattern_->itemPosition_[2].startPos, 480.0f);
    EXPECT_EQ(pattern_->itemPosition_[3].startPos, 960.0f);

    pattern_->UpdateCurrentOffset(100.0f);
    FlushUITasks();
    ASSERT_EQ(static_cast<int32_t>(pattern_->itemPosition_.size()), 5);
    EXPECT_EQ(pattern_->itemPosition_[-1].startPos, -860.0f);
    EXPECT_EQ(pattern_->itemPosition_[0].startPos, -380.0f);
    EXPECT_EQ(pattern_->itemPosition_[1].startPos, 100.0f);
    EXPECT_EQ(pattern_->itemPosition_[2].startPos, 580.0f);
    EXPECT_EQ(pattern_->itemPosition_[3].startPos, 1060.0f);

    pattern_->ChangeIndex(0, false);
    FlushUITasks();
    ASSERT_EQ(static_cast<int32_t>(pattern_->itemPosition_.size()), 5);
    EXPECT_EQ(pattern_->itemPosition_[-2].startPos, -960.0f);
    EXPECT_EQ(pattern_->itemPosition_[-1].startPos, -480.0f);
    EXPECT_EQ(pattern_->itemPosition_[0].startPos, 0.0f);
    EXPECT_EQ(pattern_->itemPosition_[1].startPos, 480.0f);
    EXPECT_EQ(pattern_->itemPosition_[2].startPos, 960.0f);

    pattern_->UpdateCurrentOffset(100.0f);
    FlushUITasks();
    ASSERT_EQ(static_cast<int32_t>(pattern_->itemPosition_.size()), 5);
    EXPECT_EQ(pattern_->itemPosition_[-2].startPos, -860.0f);
    EXPECT_EQ(pattern_->itemPosition_[-1].startPos, -380.0f);
    EXPECT_EQ(pattern_->itemPosition_[0].startPos, 100.0f);
    EXPECT_EQ(pattern_->itemPosition_[1].startPos, 580.0f);
    EXPECT_EQ(pattern_->itemPosition_[2].startPos, 1060.0f);
}

/**
 * @tc.name: ShowCachedItems024
 * @tc.desc: Test show cached items on loop = true, cachedCount = 1
 * @tc.type: FUNC
 */
HWTEST_F(SwiperCommonTestTwoNg, ShowCachedItems024, TestSize.Level1)
{
    SwiperModelNG model;
    model.Create();
    model.SetIndicatorType(SwiperIndicatorType::DOT);
    GetSwiper();
    model.SetLoop(true);
    model.SetCachedIsShown(true);
    model.SetDisplayCount(1);
    model.SetCachedCount(1);
    model.SetIndex(0);
    CreateItemWithSize(100.0f, 100.0f);
    CreateItemWithSize(150.0f, 150.0f);
    CreateItemWithSize(200.0f, 200.0f);
    CreateItemWithSize(250.0f, 250.0f);
    CreateItemWithSize(300.0f, 300.0f);
    CreateSwiperDone();

    FlushUITasks();

    auto swiperSize = frameNode_->GetGeometryNode()->GetFrameRect();
    EXPECT_EQ(swiperSize.Width(), 100.0f);
    EXPECT_EQ(swiperSize.Height(), 100.0f);

    auto secondChild = AceType::DynamicCast<FrameNode>(frameNode_->GetOrCreateChildByIndex(1));
    ASSERT_NE(secondChild, nullptr);
    auto secondChildSize = secondChild->GetGeometryNode()->GetFrameRect();
    EXPECT_EQ(secondChildSize.Width(), 100.0f);
    EXPECT_EQ(secondChildSize.Height(), 150.0f);
    auto fifthChild = AceType::DynamicCast<FrameNode>(frameNode_->GetOrCreateChildByIndex(4));
    ASSERT_NE(fifthChild, nullptr);
    auto fifthChildSize = fifthChild->GetGeometryNode()->GetFrameRect();
    EXPECT_EQ(fifthChildSize.Width(), 100.0f);
    EXPECT_EQ(fifthChildSize.Height(), 300.0f);

    pattern_->UpdateCurrentOffset(-10.0f);
    FlushUITasks();
    swiperSize = frameNode_->GetGeometryNode()->GetFrameRect();
    EXPECT_EQ(swiperSize.Width(), 100.0f);
    EXPECT_EQ(swiperSize.Height(), 150.0f);
    auto thirdChild = AceType::DynamicCast<FrameNode>(frameNode_->GetOrCreateChildByIndex(2));
    ASSERT_NE(thirdChild, nullptr);
    auto thirdChildSize = thirdChild->GetGeometryNode()->GetFrameRect();
    EXPECT_EQ(thirdChildSize.Width(), 100.0f);
    EXPECT_EQ(thirdChildSize.Height(), 200.0f);
}

/**
 * @tc.name: UpdateOnUnselectedEvent
 * @tc.desc: Test UpdateOnUnselectedEvent
 * @tc.type: FUNC
 */
HWTEST_F(SwiperCommonTestTwoNg, UpdateOnUnselectedEvent, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<SwiperPattern>();
    ASSERT_NE(pattern, nullptr);
    auto eventHub = frameNode->GetEventHub<SwiperEventHub>();
    ASSERT_NE(eventHub, nullptr);

    eventHub->unselectedEvents_.clear();

    auto onUnselected = [](const BaseEventInfo* info) {};
    pattern->UpdateOnUnselectedEvent([event = std::move(onUnselected)](int32_t index) {});
    EXPECT_EQ(eventHub->unselectedEvents_.size(), 1);

    pattern->UpdateOnUnselectedEvent([event = std::move(onUnselected)](int32_t index) {});
    EXPECT_EQ(eventHub->unselectedEvents_.size(), 1);

    auto onUnselected2 = [](const BaseEventInfo* info) {};
    pattern->UpdateOnUnselectedEvent([event = std::move(onUnselected2)](int32_t index) {});
    EXPECT_EQ(eventHub->unselectedEvents_.size(), 1);
}

/**
 * @tc.name: UpdateOnSelectedEvent
 * @tc.desc: Test UpdateOnSelectedEvent
 * @tc.type: FUNC
 */
HWTEST_F(SwiperCommonTestTwoNg, UpdateOnSelectedEvent, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<SwiperPattern>();
    ASSERT_NE(pattern, nullptr);
    auto eventHub = frameNode->GetEventHub<SwiperEventHub>();
    ASSERT_NE(eventHub, nullptr);

    eventHub->selectedEvents_.clear();
   
    auto onSelected = [](const BaseEventInfo* info) {};
    pattern->UpdateOnSelectedEvent([event = std::move(onSelected)](int32_t index) {});
    EXPECT_EQ(eventHub->selectedEvents_.size(), 1);
   
    pattern->UpdateOnSelectedEvent([event = std::move(onSelected)](int32_t index) {});
    EXPECT_EQ(eventHub->selectedEvents_.size(), 1);

    auto onSelected2 = [](const BaseEventInfo* info) {};
    pattern->UpdateOnSelectedEvent([event = std::move(onSelected2)](int32_t index) {});
    EXPECT_EQ(eventHub->selectedEvents_.size(), 1);
}

/**
 * @tc.name: SetAutoPlayOptions001
 * @tc.desc: Test HandleTouchDown
 * @tc.type: FUNC
 */
HWTEST_F(SwiperCommonTestTwoNg, SetAutoPlayOptions001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Swiper Model.
     */
    SwiperModelNG model = CreateSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    indicatorNode_->tag_ = V2::SWIPER_ETS_TAG;
    pattern_->isIndicatorLongPress_ = false;
    pattern_->isInAutoPlay_ = true;
    auto swiperPaintProperty = frameNode_->GetPaintProperty<SwiperPaintProperty>();
    swiperPaintProperty->UpdateAutoPlay(true);
    /**
     * @tc.steps: step1. Call IsStopWhenTouched Get stopWhenTouched default values.
     * @tc.expected: stopWhenTouched is true.
     */
    EXPECT_TRUE(pattern_->IsStopWhenTouched());
    /**
     * @tc.steps: step2. Call HandleTouchDown when stopWhenTouched is true
     * @tc.expected: The autoplay status pattern_->isInAutoPlay_ has changed.
     */
    TouchLocationInfo touch(0);
    touch.SetLocalLocation(Offset(100.f, 100.f));
    pattern_->HandleTouchDown({ touch });
    EXPECT_FALSE(pattern_->isInAutoPlay_);
    /**
     * @tc.steps: step3. Reset isInAutoPlay_ state and set stopWhenTouched.
     * @tc.expected: pattern_->isInAutoPlay_ is true.
     * @tc.expected: stopWhenTouched is false.
     */
    pattern_->isInAutoPlay_ = true;
    swiperPaintProperty->UpdateAutoPlay(true);
    SwiperAutoPlayOptions parameters;
    parameters.stopWhenTouched = false;
    model.SetAutoPlayOptions(Referenced::RawPtr(frameNode_), parameters);
    EXPECT_FALSE(pattern_->IsStopWhenTouched());
    /**
     * @tc.steps: step4. Call HandleTouchDown when stopWhenTouched is false
     * @tc.expected: The autoplay status pattern_ ->isInAutoPlay_ will not change.
     */
    pattern_->HandleTouchDown({ touch });
    EXPECT_TRUE(pattern_->isInAutoPlay_);
}

/**
 * @tc.name: SwiperIndicatorAccessibilityProperty001
 * @tc.desc: check function about SwiperIndicatorAccessibilityProperty.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperCommonTestTwoNg, SwiperIndicatorAccessibilityProperty001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. indicator type is DOT, indicator use mode is INNER
     * @tc.expected: check function.
     */
    CreateSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    ASSERT_NE(accessibilityProperty_, nullptr);
    auto accessibilityProperty = indicatorNode_->GetAccessibilityProperty<SwiperIndicatorAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    auto frameNode = accessibilityProperty->GetSwiperNode();
    ASSERT_NE(frameNode, nullptr);
    auto currentIndex = accessibilityProperty->GetCurrentIndex();
    EXPECT_EQ(currentIndex, 0);
    auto beginIndex = accessibilityProperty->GetBeginIndex();
    EXPECT_EQ(beginIndex, 0);
    auto endIndex = accessibilityProperty->GetEndIndex();
    EXPECT_EQ(endIndex, 0);
    auto collectionItemCounts = accessibilityProperty->GetCollectionItemCounts();
    EXPECT_EQ(collectionItemCounts, 4);
    auto GetAccessibilityText = accessibilityProperty->GetAccessibilityText();
    EXPECT_EQ(GetAccessibilityText, "");
    auto accessibilityAction = accessibilityProperty->GetAccessibilityValue();
    EXPECT_EQ(accessibilityAction.current, 0);
}

/**
 * @tc.name: UpdateAnimationProperty001
 * @tc.desc: test function UpdateAnimationProperty
 * @tc.type: FUNC
 */
HWTEST_F(SwiperCommonTestTwoNg, UpdateAnimationProperty001, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetOnSelected(std::move(nullptr));
    CreateSwiperItems(6);
    CreateSwiperDone();

    pattern_->targetIndex_ = std::make_optional<int>(0);
    EXPECT_EQ(pattern_->targetIndex_, 0);
    pattern_->currentIndex_ = 3;
    pattern_->isDragging_ = true;
    pattern_->UpdateAnimationProperty(100);
    EXPECT_EQ(pattern_->targetIndex_, 2);
    pattern_->isDragging_ = false;
    pattern_->UpdateAnimationProperty(100);
    EXPECT_FALSE(pattern_->targetIndex_.has_value());

    pattern_->targetIndex_ = std::make_optional<int>(0);
    EXPECT_EQ(pattern_->targetIndex_, 0);
    pattern_->isDragging_ = true;
    pattern_->fastAnimationRunning_ = true;
    pattern_->UpdateAnimationProperty(100);
    EXPECT_EQ(pattern_->targetIndex_, 0);
}
} // namespace OHOS::Ace::NG
