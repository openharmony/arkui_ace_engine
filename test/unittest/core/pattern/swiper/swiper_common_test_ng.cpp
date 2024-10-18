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
class SwiperCommonTestNg : public SwiperTestNg {
public:
    AssertionResult IsEqualNextFocusNode(
        FocusStep step, const RefPtr<FrameNode>& currentNode, const RefPtr<FrameNode>& expectNextNode);
    void OnKeyEvent(KeyCode keyCode, KeyAction keyAction);
    void SetOnMainTree();
};

AssertionResult SwiperCommonTestNg::IsEqualNextFocusNode(
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

void SwiperCommonTestNg::SetOnMainTree()
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

void SwiperCommonTestNg::OnKeyEvent(KeyCode keyCode, KeyAction keyAction)
{
    auto focusHub = frameNode_->GetFocusHub();
    focusHub->ProcessOnKeyEventInternal(KeyEvent(keyCode, keyAction));
    FlushLayoutTask(frameNode_);
}

/**
 * @tc.name: HandleTouchEvent001
 * @tc.desc: Test HandleTouchEvent invalid args
 * @tc.type: FUNC
 */
HWTEST_F(SwiperCommonTestNg, HandleTouchEvent001, TestSize.Level1)
{
    /**
     * @tc.cases: Call HandleTouchEvent with empty TouchLocationInfo
     * @tc.expected: isTouchDown_ is still false when touch
     */
    CreateDefaultSwiper();
    EXPECT_FALSE(pattern_->isTouchDown_);

    pattern_->HandleTouchEvent(TouchEventInfo("touch"));
    EXPECT_FALSE(pattern_->isTouchDown_);
}

/**
 * @tc.name: HandleTouchEvent002
 * @tc.desc: Test HandleTouchEvent invalid args
 * @tc.type: FUNC
 */
HWTEST_F(SwiperCommonTestNg, HandleTouchEvent002, TestSize.Level1)
{
    /**
     * @tc.cases: Call HandleTouchEvent with invalid TouchType::UNKNOWN
     * @tc.expected: isTouchDown_ is still false when touch
     */
    CreateDefaultSwiper();
    EXPECT_FALSE(pattern_->isTouchDown_);

    pattern_->HandleTouchEvent(CreateTouchEventInfo(TouchType::UNKNOWN, Offset()));
    EXPECT_FALSE(pattern_->isTouchDown_);
}

/**
 * @tc.name: HandleTouchEvent003
 * @tc.desc: When touch down, the animation will stop. When touch up, the animation will run.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperCommonTestNg, HandleTouchEvent003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Swipe to item(index:1), set animation to true
     * @tc.expected: When touch up, will trigger UpdateAnimationProperty and stop animation
     */
    CreateDefaultSwiper();
    ShowNext();
    EXPECT_EQ(pattern_->GetCurrentIndex(), 1);
    pattern_->springAnimationIsRunning_ = true;
    pattern_->isTouchDownSpringAnimation_ = false;
    pattern_->childScrolling_ = true;

    /**
     * @tc.steps: step1. Touch down a location
     * @tc.expected: isTouchDown_ is true, Animation stop
     */
    pattern_->HandleTouchEvent(CreateTouchEventInfo(TouchType::DOWN, Offset()));
    EXPECT_TRUE(pattern_->isTouchDown_);
    EXPECT_TRUE(pattern_->springAnimationIsRunning_);
    EXPECT_TRUE(pattern_->isTouchDownSpringAnimation_);
    EXPECT_FALSE(pattern_->childScrolling_);

    /**
     * @tc.steps: step2. Touch up
     * @tc.expected: isTouchDown_ is false, Animation resume
     */
    pattern_->HandleTouchEvent(CreateTouchEventInfo(TouchType::UP, Offset()));
    EXPECT_FALSE(pattern_->isTouchDown_);
    EXPECT_TRUE(pattern_->springAnimationIsRunning_);
    EXPECT_FALSE(pattern_->isTouchDownSpringAnimation_);
    EXPECT_TRUE(pattern_->moveDirection_);
}

/**
 * @tc.name: HandleTouchEvent004
 * @tc.desc: When touch down, the animation will stop. When touch cancel, the animation will run.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperCommonTestNg, HandleTouchEvent004, TestSize.Level1)
{
    CreateDefaultSwiper();
    pattern_->fadeAnimationIsRunning_ = true;

    /**
     * @tc.steps: step1. Touch down a location
     * @tc.expected: Animation stoped
     */
    pattern_->HandleTouchEvent(CreateTouchEventInfo(TouchType::DOWN, Offset()));
    EXPECT_TRUE(pattern_->isTouchDown_);
    EXPECT_FALSE(pattern_->fadeAnimationIsRunning_);

    /**
     * @tc.steps: step2. Touch cancel
     * @tc.expected: Animation resume
     */
    pattern_->HandleTouchEvent(CreateTouchEventInfo(TouchType::CANCEL, Offset()));
    EXPECT_FALSE(pattern_->isTouchDown_);
    EXPECT_TRUE(pattern_->fadeAnimationIsRunning_);
}

/**
 * @tc.name: HandleTouchEvent005
 * @tc.desc: When touch down on indicatorNode_, the animation will not stop
 * @tc.type: FUNC
 */
HWTEST_F(SwiperCommonTestNg, HandleTouchEvent005, TestSize.Level1)
{
    CreateDefaultSwiper();
    pattern_->springAnimationIsRunning_ = true;

    /**
     * @tc.steps: step1. Touch down on indicatorNode_
     * @tc.expected: Animation still running
     */
    pattern_->HandleTouchEvent(CreateTouchEventInfo(TouchType::DOWN, Offset(SWIPER_WIDTH / 2, SWIPER_HEIGHT)));
    EXPECT_TRUE(pattern_->isTouchDown_);
    EXPECT_TRUE(pattern_->springAnimationIsRunning_);

    /**
     * @tc.steps: step2. Touch up
     * @tc.expected: Animation still running
     */
    pattern_->HandleTouchEvent(CreateTouchEventInfo(TouchType::UP, Offset(SWIPER_WIDTH / 2, SWIPER_HEIGHT)));
    EXPECT_FALSE(pattern_->isTouchDown_);
    EXPECT_TRUE(pattern_->springAnimationIsRunning_);
}

/**
 * @tc.name: HandleTouchEvent006
 * @tc.desc: When touch down on indicatorNode_ area, but no indicatorNode_, the animation will stop
 * @tc.type: FUNC
 */
HWTEST_F(SwiperCommonTestNg, HandleTouchEvent006, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetShowIndicator(false); // not show indicator
    CreateSwiperItems();
    CreateSwiperDone();
    pattern_->translateAnimationIsRunning_ = true;

    /**
     * @tc.steps: step1. Touch down on indicatorNode_ area
     * @tc.expected: Animation stoped
     */
    pattern_->HandleTouchEvent(CreateTouchEventInfo(TouchType::DOWN, Offset(SWIPER_WIDTH / 2, SWIPER_HEIGHT)));
    EXPECT_TRUE(pattern_->isTouchDown_);
    EXPECT_FALSE(pattern_->translateAnimationIsRunning_);
}

/**
 * @tc.name: AccessibilityProperty001
 * @tc.desc: Test AccessibilityProperty
 * @tc.type: FUNC
 */
HWTEST_F(SwiperCommonTestNg, AccessibilityProperty001, TestSize.Level1)
{
    CreateDefaultSwiper();
    EXPECT_EQ(accessibilityProperty_->GetCurrentIndex(), 0);
    EXPECT_EQ(accessibilityProperty_->GetBeginIndex(), 0);
    EXPECT_EQ(accessibilityProperty_->GetEndIndex(), 0);
    AccessibilityValue result = accessibilityProperty_->GetAccessibilityValue();
    EXPECT_EQ(result.min, 0);
    EXPECT_EQ(result.max, 3);
    EXPECT_EQ(result.current, 0);
    EXPECT_TRUE(accessibilityProperty_->IsScrollable());
    EXPECT_EQ(accessibilityProperty_->GetCollectionItemCounts(), 4);
}

/**
 * @tc.name: AccessibilityProperty002
 * @tc.desc: Test AccessibilityProperty
 * @tc.type: FUNC
 */
HWTEST_F(SwiperCommonTestNg, AccessibilityProperty002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set loop to false
     */
    SwiperModelNG model = CreateSwiper();
    model.SetLoop(false);
    CreateSwiperItems();
    CreateSwiperDone();

    /**
     * @tc.steps: step2. Current is first page
     * @tc.expected: ACTION_SCROLL_FORWARD
     */
    accessibilityProperty_->ResetSupportAction(); // call SetSpecificSupportAction
    uint64_t expectActions = 0;
    expectActions |= 1UL << static_cast<uint32_t>(AceAction::ACTION_SCROLL_FORWARD);
    EXPECT_EQ(GetActions(accessibilityProperty_), expectActions);
}

/**
 * @tc.name: AccessibilityProperty003
 * @tc.desc: Test AccessibilityProperty
 * @tc.type: FUNC
 */
HWTEST_F(SwiperCommonTestNg, AccessibilityProperty003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set loop to false
     */
    SwiperModelNG model = CreateSwiper();
    model.SetLoop(false);
    CreateSwiperItems();
    CreateSwiperDone();

    /**
     * @tc.steps: step2. Show next page, Current is second(middle) page
     * @tc.expected: ACTION_SCROLL_FORWARD ACTION_SCROLL_BACKWARD
     */
    ShowNext();
    accessibilityProperty_->ResetSupportAction();
    uint64_t expectActions = 0;
    expectActions |= 1UL << static_cast<uint32_t>(AceAction::ACTION_SCROLL_FORWARD);
    expectActions |= 1UL << static_cast<uint32_t>(AceAction::ACTION_SCROLL_BACKWARD);
    EXPECT_EQ(GetActions(accessibilityProperty_), expectActions);
}

/**
 * @tc.name: AccessibilityProperty004
 * @tc.desc: Test AccessibilityProperty
 * @tc.type: FUNC
 */
HWTEST_F(SwiperCommonTestNg, AccessibilityProperty004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set loop to false
     */
    SwiperModelNG model = CreateSwiper();
    model.SetLoop(false);
    CreateSwiperItems();
    CreateSwiperDone();

    /**
     * @tc.steps: step2. Show last page, Current is last page
     * @tc.expected: ACTION_SCROLL_BACKWARD
     */
    ChangeIndex(3);
    accessibilityProperty_->ResetSupportAction();
    uint64_t expectActions = 0;
    expectActions |= 1UL << static_cast<uint32_t>(AceAction::ACTION_SCROLL_BACKWARD);
    EXPECT_EQ(GetActions(accessibilityProperty_), expectActions);
}

/**
 * @tc.name: AccessibilityProperty005
 * @tc.desc: Test AccessibilityProperty
 * @tc.type: FUNC
 */
HWTEST_F(SwiperCommonTestNg, AccessibilityProperty005, TestSize.Level1)
{
    /**
     * @tc.cases: Swiper is loop
     * @tc.expected: ACTION_SCROLL_FORWARD ACTION_SCROLL_BACKWARD
     */
    CreateDefaultSwiper();
    accessibilityProperty_->ResetSupportAction(); // call SetSpecificSupportAction
    uint64_t expectActions = 0;
    expectActions |= 1UL << static_cast<uint32_t>(AceAction::ACTION_SCROLL_FORWARD);
    expectActions |= 1UL << static_cast<uint32_t>(AceAction::ACTION_SCROLL_BACKWARD);
    EXPECT_EQ(GetActions(accessibilityProperty_), expectActions);
}

/**
 * @tc.name: AccessibilityProperty006
 * @tc.desc: Test AccessibilityProperty
 * @tc.type: FUNC
 */
HWTEST_F(SwiperCommonTestNg, AccessibilityProperty006, TestSize.Level1)
{
    /**
     * @tc.cases: Create UnScrollable swiper
     * @tc.expected: expectActions is 0
     */
    SwiperModelNG model = CreateSwiper();
    model.SetLoop(false);
    CreateSwiperItems(1);
    CreateSwiperDone();
    accessibilityProperty_->ResetSupportAction(); // call SetSpecificSupportAction
    uint64_t expectActions = 0;
    EXPECT_EQ(GetActions(accessibilityProperty_), expectActions);
}

/**
 * @tc.name: PerformActionTest001
 * @tc.desc: Swiper AccessibilityProperty PerformAction test ScrollForward and ScrollBackward.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperCommonTestNg, PerformActionTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Scrollable swiper
     */
    CreateDefaultSwiper();
    EXPECT_TRUE(accessibilityProperty_->IsScrollable());

    /**
     * @tc.steps: step2. call ActActionScrollForward
     * @tc.expected: ShowNext is triggered
     */
    accessibilityProperty_->ActActionScrollForward();
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetCurrentShownIndex(), 1);

    /**
     * @tc.steps: step3. call ActActionScrollBackward
     * @tc.expected: ShowPrevious is triggered
     */
    accessibilityProperty_->ActActionScrollBackward();
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetCurrentShownIndex(), 0);
}

/**
 * @tc.name: PerformActionTest002
 * @tc.desc: Swiper AccessibilityProperty PerformAction test ScrollForward and ScrollBackward.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperCommonTestNg, PerformActionTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. UnScrollable swiper
     */
    SwiperModelNG model = CreateSwiper();
    model.SetLoop(false);
    CreateSwiperItems(1);
    CreateSwiperDone();
    EXPECT_FALSE(accessibilityProperty_->IsScrollable());

    /**
     * @tc.steps: step2. call ActActionScrollForward
     * @tc.expected: ShowNext is not triggered
     */
    accessibilityProperty_->ActActionScrollForward();
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetCurrentShownIndex(), 0);

    /**
     * @tc.steps: step3. call ActActionScrollBackward
     * @tc.expected: ShowPrevious is not triggered
     */
    accessibilityProperty_->ActActionScrollBackward();
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetCurrentShownIndex(), 0);
}

/**
 * @tc.name: FocusStep001
 * @tc.desc: Test FocusStep with arrow
 * @tc.type: FUNC
 */
HWTEST_F(SwiperCommonTestNg, FocusStep001, TestSize.Level1)
{
    CreateWithArrow();
    SetOnMainTree();

    /**
     * @tc.cases: GetNextFocusNode from indicatorNode_
     */
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP, indicatorNode_, leftArrowNode_));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::SHIFT_TAB, indicatorNode_, leftArrowNode_));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT, indicatorNode_, nullptr));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, indicatorNode_, rightArrowNode_));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::TAB, indicatorNode_, rightArrowNode_));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT, indicatorNode_, nullptr));

    /**
     * @tc.cases: GetNextFocusNode from leftArrowNode_
     */
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP, leftArrowNode_, nullptr));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::SHIFT_TAB, leftArrowNode_, nullptr));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT, leftArrowNode_, nullptr));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, leftArrowNode_, indicatorNode_));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::TAB, leftArrowNode_, indicatorNode_));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT, leftArrowNode_, nullptr));

    /**
     * @tc.cases: GetNextFocusNode from rightArrowNode_
     */
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP, rightArrowNode_, indicatorNode_));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::SHIFT_TAB, rightArrowNode_, indicatorNode_));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT, rightArrowNode_, nullptr));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, rightArrowNode_, nullptr));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::TAB, rightArrowNode_, nullptr));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT, rightArrowNode_, nullptr));
}

/**
 * @tc.name: FocusStep002
 * @tc.desc: Test FocusStep with arrow and VERTICAL layout
 * @tc.type: FUNC
 */
HWTEST_F(SwiperCommonTestNg, FocusStep002, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetDirection(Axis::VERTICAL); // set VERTICAL
    model.SetDisplayArrow(true);        // show arrow
    model.SetHoverShow(false);
    model.SetArrowStyle(ARROW_PARAMETERS);
    CreateSwiperItems();
    CreateSwiperDone();
    SetOnMainTree();

    /**
     * @tc.cases: GetNextFocusNode from indicatorNode_
     */
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP, indicatorNode_, nullptr));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::SHIFT_TAB, indicatorNode_, nullptr));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT, indicatorNode_, leftArrowNode_));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, indicatorNode_, nullptr));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::TAB, indicatorNode_, nullptr));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT, indicatorNode_, rightArrowNode_));

    /**
     * @tc.cases: GetNextFocusNode from leftArrowNode_
     */
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP, leftArrowNode_, nullptr));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::SHIFT_TAB, leftArrowNode_, nullptr));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT, leftArrowNode_, nullptr));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, leftArrowNode_, nullptr));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::TAB, leftArrowNode_, nullptr));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT, leftArrowNode_, indicatorNode_));

    /**
     * @tc.cases: GetNextFocusNode from rightArrowNode_
     */
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP, rightArrowNode_, nullptr));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::SHIFT_TAB, rightArrowNode_, nullptr));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT, rightArrowNode_, indicatorNode_));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, rightArrowNode_, nullptr));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::TAB, rightArrowNode_, nullptr));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT, rightArrowNode_, nullptr));
}

/**
 * @tc.name: FocusStep003
 * @tc.desc: Test FocusStep with arrow and loop:false
 * @tc.type: FUNC
 */
HWTEST_F(SwiperCommonTestNg, FocusStep003, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetLoop(false);        // set false loop
    model.SetDisplayArrow(true); // show arrow
    model.SetHoverShow(false);
    model.SetArrowStyle(ARROW_PARAMETERS);
    CreateSwiperItems();
    CreateSwiperDone();
    SetOnMainTree();

    /**
     * @tc.cases: LoopIndex is first item(index:0)
     */
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP, indicatorNode_, nullptr));           // PreviousFocus
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, indicatorNode_, rightArrowNode_)); // NextFocus

    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP, leftArrowNode_, nullptr));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, leftArrowNode_, indicatorNode_));

    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP, rightArrowNode_, indicatorNode_));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, rightArrowNode_, nullptr));

    /**
     * @tc.cases: LoopIndex is middle item(index:1)
     */
    ChangeIndex(1);
    EXPECT_EQ(pattern_->GetCurrentShownIndex(), 1);
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP, indicatorNode_, leftArrowNode_));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, indicatorNode_, rightArrowNode_));

    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP, leftArrowNode_, nullptr));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, leftArrowNode_, indicatorNode_));

    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP, rightArrowNode_, indicatorNode_));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, rightArrowNode_, nullptr));

    /**
     * @tc.cases: LoopIndex is last item(index:3)
     */
    ChangeIndex(3);
    EXPECT_EQ(pattern_->GetCurrentShownIndex(), 3);
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP, indicatorNode_, leftArrowNode_));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, indicatorNode_, nullptr));

    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP, leftArrowNode_, nullptr));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, leftArrowNode_, indicatorNode_));

    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP, rightArrowNode_, indicatorNode_));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, rightArrowNode_, nullptr));
}

/**
 * @tc.name: FocusStep004
 * @tc.desc: Test FocusStep with arrow and loop:false and without indicator
 * @tc.type: FUNC
 */
HWTEST_F(SwiperCommonTestNg, FocusStep004, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetShowIndicator(false); // without indicator
    model.SetLoop(false);
    model.SetDisplayArrow(true); // show arrow
    model.SetHoverShow(false);
    model.SetArrowStyle(ARROW_PARAMETERS);
    CreateSwiperItems();
    CreateSwiperDone();
    SetOnMainTree();

    /**
     * @tc.cases: LoopIndex is last item(index:0)
     */
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP, leftArrowNode_, nullptr));           // PreviousFocus
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, leftArrowNode_, rightArrowNode_)); // NextFocus

    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP, rightArrowNode_, nullptr));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, rightArrowNode_, nullptr));

    /**
     * @tc.cases: LoopIndex is middle item(index:1)
     */
    ChangeIndex(1);
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP, leftArrowNode_, nullptr));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, leftArrowNode_, rightArrowNode_));

    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP, rightArrowNode_, leftArrowNode_));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, rightArrowNode_, nullptr));

    /**
     * @tc.cases: LoopIndex is last item(index:3)
     */
    ChangeIndex(3);
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP, leftArrowNode_, nullptr));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, leftArrowNode_, nullptr));

    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP, rightArrowNode_, leftArrowNode_));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, rightArrowNode_, nullptr));
}

/**
 * @tc.name: FocusStep005
 * @tc.desc: Test FocusStep without arrow
 * @tc.type: FUNC
 */
HWTEST_F(SwiperCommonTestNg, FocusStep005, TestSize.Level1)
{
    CreateDefaultSwiper();

    /**
     * @tc.cases: GetNextFocusNode from indicatorNode_
     */
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP, indicatorNode_, nullptr));   // PreviousFocus
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, indicatorNode_, nullptr)); // NextFocus
}

/**
 * @tc.name: FocusStep006
 * @tc.desc: Test FocusStep without indicator
 * @tc.type: FUNC
 */
HWTEST_F(SwiperCommonTestNg, FocusStep006, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetShowIndicator(false); // without indicator
    model.SetDisplayArrow(true);   // show arrow
    model.SetHoverShow(false);
    model.SetArrowStyle(ARROW_PARAMETERS);
    CreateSwiperItems();
    CreateSwiperDone();
    SetOnMainTree();

    /**
     * @tc.cases: GetNextFocusNode from leftArrowNode_
     */
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP, leftArrowNode_, nullptr));           // PreviousFocus
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, leftArrowNode_, rightArrowNode_)); // NextFocus

    /**
     * @tc.cases: GetNextFocusNode from rightArrowNode_
     */
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP, rightArrowNode_, leftArrowNode_));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, rightArrowNode_, nullptr));
}

/**
 * @tc.name: Distributed001
 * @tc.desc: Test the distributed capability of Swiper
 * @tc.type: FUNC
 */
HWTEST_F(SwiperCommonTestNg, Distributed001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set Index.
     * @tc.expected: Function ProvideRestoreInfo is called.
     */
    const int32_t initIndex = 1;
    SwiperModelNG model = CreateSwiper();
    model.SetIndex(initIndex);
    CreateSwiperItems();
    CreateSwiperDone();
    EXPECT_EQ(pattern_->ProvideRestoreInfo(), R"({"Index":1})");

    /**
     * @tc.steps: step2. Function OnRestoreInfo is called.
     * @tc.expected: Passing invalid & valid JSON format.
     */
    pattern_->OnRestoreInfo(R"({"Index":1})");
    EXPECT_EQ(layoutProperty_->GetIndexValue(0), initIndex);
    pattern_->OnRestoreInfo(R"({"Index":0})");
    EXPECT_EQ(layoutProperty_->GetIndexValue(0), 0);
    pattern_->OnRestoreInfo("invalid_json_string");
    EXPECT_EQ(layoutProperty_->GetIndexValue(0), 0);
}

/**
 * @tc.name: OnKeyEvent001
 * @tc.desc: InitOnKeyEvent
 * @tc.type: FUNC
 */
HWTEST_F(SwiperCommonTestNg, OnKeyEvent001, TestSize.Level1)
{
    CreateDefaultSwiper();

    /**
     * @tc.steps: step1. Call OnKeyEvent KEY_DPAD_LEFT
     * @tc.expected: Trigger ShowPrevious
     */
    OnKeyEvent(KeyCode::KEY_DPAD_LEFT, KeyAction::DOWN);
    EXPECT_EQ(pattern_->GetCurrentIndex(), 3);

    /**
     * @tc.steps: step2. Call OnKeyEvent KEY_DPAD_RIGHT
     * @tc.expected: Trigger ShowNext
     */
    OnKeyEvent(KeyCode::KEY_DPAD_RIGHT, KeyAction::DOWN);
    EXPECT_EQ(pattern_->GetCurrentIndex(), 0);
}

/**
 * @tc.name: OnKeyEvent002
 * @tc.desc: InitOnKeyEvent in VERTICAL layout
 * @tc.type: FUNC
 */
HWTEST_F(SwiperCommonTestNg, OnKeyEvent002, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetDirection(Axis::VERTICAL);
    CreateSwiperItems();
    CreateSwiperDone();

    /**
     * @tc.steps: step1. Call OnKeyEvent KEY_DPAD_UP
     * @tc.expected: Trigger ShowPrevious
     */
    OnKeyEvent(KeyCode::KEY_DPAD_UP, KeyAction::DOWN);
    EXPECT_EQ(pattern_->GetCurrentIndex(), 3);

    /**
     * @tc.steps: step2. Call OnKeyEvent KEY_DPAD_DOWN
     * @tc.expected: Trigger ShowNext
     */
    OnKeyEvent(KeyCode::KEY_DPAD_DOWN, KeyAction::DOWN);
    EXPECT_EQ(pattern_->GetCurrentIndex(), 0);
}

/**
 * @tc.name: OnKeyEvent003
 * @tc.desc: InitOnKeyEvent with DisplayCount>1, swipe only when focus first/last item in page
 * @tc.type: FUNC
 */
HWTEST_F(SwiperCommonTestNg, OnKeyEvent003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. DisplayCount>1, focus item(index:0)
     */
    SwiperModelNG model = CreateSwiper();
    model.SetDisplayCount(2);
    CreateSwiperItems();
    CreateSwiperDone();
    GetChildFocusHub(frameNode_, 0)->RequestFocusImmediately();

    /**
     * @tc.steps: step2. Call OnKeyEvent KEY_DPAD_LEFT
     * @tc.expected: ShowPrevious and Focus pre item
     */
    OnKeyEvent(KeyCode::KEY_DPAD_LEFT, KeyAction::DOWN);
    EXPECT_EQ(pattern_->GetCurrentIndex(), 3);
    EXPECT_TRUE(GetChildFocusHub(frameNode_, 3)->IsCurrentFocus());

    /**
     * @tc.steps: step3. Call OnKeyEvent KEY_DPAD_RIGHT
     * @tc.expected: Focus next item
     */
    OnKeyEvent(KeyCode::KEY_DPAD_RIGHT, KeyAction::DOWN);
    EXPECT_EQ(pattern_->GetCurrentIndex(), 3);
    EXPECT_TRUE(GetChildFocusHub(frameNode_, 0)->IsCurrentFocus());

    /**
     * @tc.steps: step4. Call OnKeyEvent KEY_DPAD_RIGHT
     * @tc.expected: ShowNext and Focus next item
     */
    OnKeyEvent(KeyCode::KEY_DPAD_RIGHT, KeyAction::DOWN);
    EXPECT_EQ(pattern_->GetCurrentIndex(), 0);
    EXPECT_TRUE(GetChildFocusHub(frameNode_, 1)->IsCurrentFocus());

    /**
     * @tc.steps: step5. Call OnKeyEvent KEY_DPAD_LEFT
     * @tc.expected: Focus pre item
     */
    OnKeyEvent(KeyCode::KEY_DPAD_LEFT, KeyAction::DOWN);
    EXPECT_EQ(pattern_->GetCurrentIndex(), 0);
    EXPECT_TRUE(GetChildFocusHub(frameNode_, 0)->IsCurrentFocus());
}

/**
 * @tc.name: OnKeyEvent004
 * @tc.desc: InitOnKeyEvent with DisplayCount>1, swipe only when focus first/last item in page in VERTICAL layout
 * @tc.type: FUNC
 */
HWTEST_F(SwiperCommonTestNg, OnKeyEvent004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. DisplayCount>1, focus item(index:0)
     */
    SwiperModelNG model = CreateSwiper();
    model.SetDirection(Axis::VERTICAL);
    model.SetDisplayCount(2);
    CreateSwiperItems();
    CreateSwiperDone();
    GetChildFocusHub(frameNode_, 0)->RequestFocusImmediately();

    /**
     * @tc.steps: step2. Call OnKeyEvent KEY_DPAD_UP
     * @tc.expected: ShowPrevious and Focus pre item
     */
    OnKeyEvent(KeyCode::KEY_DPAD_UP, KeyAction::DOWN);
    EXPECT_EQ(pattern_->GetCurrentIndex(), 3);
    EXPECT_TRUE(GetChildFocusHub(frameNode_, 3)->IsCurrentFocus());

    /**
     * @tc.steps: step3. Call OnKeyEvent KEY_DPAD_DOWN
     * @tc.expected: Focus next item
     */
    OnKeyEvent(KeyCode::KEY_DPAD_DOWN, KeyAction::DOWN);
    EXPECT_EQ(pattern_->GetCurrentIndex(), 3);
    EXPECT_TRUE(GetChildFocusHub(frameNode_, 0)->IsCurrentFocus());

    /**
     * @tc.steps: step4. Call OnKeyEvent KEY_DPAD_DOWN
     * @tc.expected: ShowNext and Focus next item
     */
    OnKeyEvent(KeyCode::KEY_DPAD_DOWN, KeyAction::DOWN);
    EXPECT_EQ(pattern_->GetCurrentIndex(), 0);
    EXPECT_TRUE(GetChildFocusHub(frameNode_, 1)->IsCurrentFocus());

    /**
     * @tc.steps: step5. Call OnKeyEvent KEY_DPAD_UP
     * @tc.expected: Focus pre item
     */
    OnKeyEvent(KeyCode::KEY_DPAD_UP, KeyAction::DOWN);
    EXPECT_EQ(pattern_->GetCurrentIndex(), 0);
    EXPECT_TRUE(GetChildFocusHub(frameNode_, 0)->IsCurrentFocus());
}

/**
 * @tc.name: OnKeyEvent005
 * @tc.desc: OnKeyEvent return false
 * @tc.type: FUNC
 */
HWTEST_F(SwiperCommonTestNg, OnKeyEvent005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. set axis default
     */
    CreateDefaultSwiper();

    /**
     * @tc.steps: step2. Call OnKeyEvent KEY_DPAD_LEFT
     * @tc.expected: false
     */
    EXPECT_FALSE(pattern_->OnKeyEvent(KeyEvent(KeyCode::KEY_DPAD_LEFT, KeyAction::LONG_PRESS)));

    /**
     * @tc.steps: step3. Call OnKeyEvent KEY_DPAD_RIGHT
     * @tc.expected: false
     */
    EXPECT_FALSE(pattern_->OnKeyEvent(KeyEvent(KeyCode::KEY_DPAD_RIGHT, KeyAction::LONG_PRESS)));

    /**
     * @tc.steps: step4. Call OnKeyEvent KEY_DPAD_UP
     * @tc.expected: false
     */
    EXPECT_FALSE(pattern_->OnKeyEvent(KeyEvent(KeyCode::KEY_DPAD_UP, KeyAction::DOWN)));

    /**
     * @tc.steps: step5. Call OnKeyEvent KEY_DPAD_DOWN
     * @tc.expected: false
     */
    EXPECT_FALSE(pattern_->OnKeyEvent(KeyEvent(KeyCode::KEY_DPAD_DOWN, KeyAction::DOWN)));

    /**
     * @tc.steps: step6. set axis vertical
     */
    SwiperModelNG model = CreateSwiper();
    model.SetDirection(Axis::VERTICAL);
    CreateSwiperItems();
    CreateSwiperDone();

    /**
     * @tc.steps: step7. Call OnKeyEvent KEY_DPAD_LEFT
     * @tc.expected: false
     */
    EXPECT_FALSE(pattern_->OnKeyEvent(KeyEvent(KeyCode::KEY_DPAD_LEFT, KeyAction::DOWN)));

    /**
     * @tc.steps: step8. Call OnKeyEvent KEY_DPAD_RIGHT
     * @tc.expected: false
     */
    EXPECT_FALSE(pattern_->OnKeyEvent(KeyEvent(KeyCode::KEY_DPAD_RIGHT, KeyAction::DOWN)));
}

/**
 * @tc.name: MarginIgnoreBlankTest001
 * @tc.desc: Test Swiper IgnoreBlank in jumpIndex case
 * @tc.type: FUNC
 */
HWTEST_F(SwiperCommonTestNg, MarginIgnoreBlankTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. SetLoop false
     */
    const int32_t displayCount = 3;
    const float itemWidth = (SWIPER_WIDTH - PRE_MARGIN - NEXT_MARGIN) / displayCount;
    SwiperModelNG model = CreateSwiper();
    model.SetDisplayCount(displayCount);
    model.SetLoop(false);
    model.SetPreviousMargin(Dimension(PRE_MARGIN), true);
    model.SetNextMargin(Dimension(NEXT_MARGIN), true);
    CreateSwiperItems(5);
    CreateSwiperDone();

    /**
     * @tc.steps: step2. ChangeIndex to 0
     * @tc.expected: Verify ignoreBlank on the homepage is effective
     */
    ChangeIndex(0);
    EXPECT_EQ(pattern_->GetCurrentShownIndex(), 0);
    EXPECT_EQ(GetChildX(frameNode_, 0), 0.f);
    EXPECT_EQ(GetChildX(frameNode_, 1), itemWidth);
    EXPECT_EQ(GetChildX(frameNode_, 2), itemWidth * 2);
    EXPECT_EQ(GetChildX(frameNode_, 3), itemWidth * 3);

    /**
     * @tc.steps: step3. ChangeIndex to 1
     * @tc.expected: Verify ignoreBlank is not effective
     */
    ChangeIndex(1);
    EXPECT_EQ(pattern_->GetCurrentShownIndex(), 1);
    EXPECT_EQ(GetChildX(frameNode_, 0), PRE_MARGIN - itemWidth);
    EXPECT_EQ(GetChildX(frameNode_, 1), PRE_MARGIN);
    EXPECT_EQ(GetChildX(frameNode_, 2), PRE_MARGIN + itemWidth);
    EXPECT_EQ(GetChildX(frameNode_, 3), PRE_MARGIN + itemWidth * 2);
    EXPECT_EQ(GetChildX(frameNode_, 4), PRE_MARGIN + itemWidth * 3);

    /**
     * @tc.steps: step4. ChangeIndex to 2
     * @tc.expected: Verify ignoreBlank on the endPage is effective
     */
    ChangeIndex(2);
    EXPECT_EQ(pattern_->GetCurrentShownIndex(), 2);
    EXPECT_EQ(GetChildX(frameNode_, 1), PRE_MARGIN + NEXT_MARGIN - itemWidth);
    EXPECT_EQ(GetChildX(frameNode_, 2), PRE_MARGIN + NEXT_MARGIN);
    EXPECT_EQ(GetChildX(frameNode_, 3), PRE_MARGIN + NEXT_MARGIN + itemWidth);
    EXPECT_EQ(GetChildX(frameNode_, 4), PRE_MARGIN + NEXT_MARGIN + itemWidth * 2);
}

/**
 * @tc.name: MarginIgnoreBlankTest002
 * @tc.desc: Test Swiper IgnoreBlank Not effective in loop scenarios
 * @tc.type: FUNC
 */
HWTEST_F(SwiperCommonTestNg, MarginIgnoreBlankTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. CreateWith SetLoop true
     */
    const int32_t displayCount = 3;
    const float itemWidth = (SWIPER_WIDTH - PRE_MARGIN - NEXT_MARGIN) / displayCount;
    SwiperModelNG model = CreateSwiper();
    model.SetDisplayCount(displayCount);
    model.SetPreviousMargin(Dimension(PRE_MARGIN), true);
    model.SetNextMargin(Dimension(NEXT_MARGIN), true);
    CreateSwiperItems(5);
    CreateSwiperDone();

    /**
     * @tc.steps: step2. ChangeIndex to 0
     * @tc.expected: loop is true, ignoreBlank on the endPage is not effective
     */
    ChangeIndex(0);
    EXPECT_EQ(pattern_->GetCurrentShownIndex(), 0);
    EXPECT_EQ(GetChildX(frameNode_, 4), PRE_MARGIN - itemWidth);
    EXPECT_EQ(GetChildX(frameNode_, 0), PRE_MARGIN);
    EXPECT_EQ(GetChildX(frameNode_, 1), PRE_MARGIN + itemWidth * 1);
    EXPECT_EQ(GetChildX(frameNode_, 2), PRE_MARGIN + itemWidth * 2);
    EXPECT_EQ(GetChildX(frameNode_, 3), PRE_MARGIN + itemWidth * 3);
}

/**
 * @tc.name: MarginIgnoreBlankTest003
 * @tc.desc: Test Swiper IgnoreBlank with itemSpace
 * @tc.type: FUNC
 */
HWTEST_F(SwiperCommonTestNg, MarginIgnoreBlankTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. CreateWith SetLoop true
     */
    const int32_t displayCount = 2;
    SwiperModelNG model = CreateSwiper();
    model.SetDisplayCount(displayCount);
    model.SetPreviousMargin(Dimension(0.0_vp), true);
    model.SetItemSpace(Dimension(10.f));
    CreateSwiperItems(3);
    CreateSwiperDone();

    /**
     * @tc.steps: step2. check first item position
     * @tc.expected: loop is true, ignoreBlank on the endPage is not effective
     */
    EXPECT_EQ(pattern_->GetCurrentShownIndex(), 0);
    EXPECT_EQ(GetChildX(frameNode_, 0), 0);
}

/**
 * @tc.name: IsAtStartEnd001
 * @tc.desc: Test IsAtStart IsAtEnd
 * @tc.type: FUNC
 */
HWTEST_F(SwiperCommonTestNg, IsAtStartEnd001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Loop is true
     * @tc.expected: There are no start or end
     */
    SwiperModelNG model = CreateSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    EXPECT_FALSE(pattern_->IsAtStart());
    EXPECT_FALSE(pattern_->IsAtEnd());

    /**
     * @tc.steps: step2. Empty items
     * @tc.expected: There are no start or end
     */
    model = CreateSwiper();
    model.SetLoop(false);
    CreateSwiperDone();
    EXPECT_FALSE(pattern_->IsAtStart());
    EXPECT_FALSE(pattern_->IsAtEnd());
}

/**
 * @tc.name: IsAtStartEnd002
 * @tc.desc: Test IsAtStart IsAtEnd
 * @tc.type: FUNC
 */
HWTEST_F(SwiperCommonTestNg, IsAtStartEnd002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. At start
     */
    SwiperModelNG model = CreateSwiper();
    model.SetLoop(false);
    CreateSwiperItems();
    CreateSwiperDone();
    EXPECT_TRUE(pattern_->IsAtStart());
    EXPECT_FALSE(pattern_->IsAtEnd());

    /**
     * @tc.steps: step2. Change currentIndex to middle item
     * @tc.expected: Not at start or end
     */
    ChangeIndex(1);
    EXPECT_FALSE(pattern_->IsAtStart());
    EXPECT_FALSE(pattern_->IsAtEnd());

    /**
     * @tc.steps: step3. Change currentIndex to end item
     * @tc.expected: At end
     */
    ChangeIndex(ITEM_NUMBER - 1);
    EXPECT_FALSE(pattern_->IsAtStart());
    EXPECT_TRUE(pattern_->IsAtEnd());
}
} // namespace OHOS::Ace::NG
