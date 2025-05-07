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
    FlushUITasks();
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
    CreateSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
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
    CreateSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
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
    CreateSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
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
    CreateSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    pattern_->fadeAnimationIsRunning_ = true;

    /**
     * @tc.steps: step1. Touch down a location
     * @tc.expected: Animation stoped
     */
    pattern_->HandleTouchEvent(CreateTouchEventInfo(TouchType::DOWN, Offset()));
    EXPECT_TRUE(pattern_->isTouchDown_);
    EXPECT_TRUE(pattern_->isTouchDownFadeAnimation_);

    /**
     * @tc.steps: step2. Touch cancel
     * @tc.expected: Animation resume
     */
    pattern_->HandleTouchEvent(CreateTouchEventInfo(TouchType::CANCEL, Offset()));
    EXPECT_FALSE(pattern_->isTouchDown_);
    EXPECT_FALSE(pattern_->isTouchDownFadeAnimation_);
}

/**
 * @tc.name: HandleTouchEvent005
 * @tc.desc: When touch down on indicatorNode_, the animation will not stop
 * @tc.type: FUNC
 */
HWTEST_F(SwiperCommonTestNg, HandleTouchEvent005, TestSize.Level1)
{
    CreateSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
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
    EXPECT_TRUE(CurrentIndex(1));
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
    EXPECT_TRUE(CurrentIndex(3));
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
    CreateSwiper();
    CreateSwiperItems();
    CreateSwiperDone();

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
    CreateSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    GetChildFocusHub(frameNode_, 0)->RequestFocusImmediately();

    /**
     * @tc.steps: step1. Call OnKeyEvent KEY_DPAD_LEFT
     * @tc.expected: Trigger ShowPrevious
     */
    OnKeyEvent(KeyCode::KEY_DPAD_LEFT, KeyAction::DOWN);
    EXPECT_EQ(pattern_->GetCurrentIndex(), 3);
    EXPECT_TRUE(GetChildFocusHub(frameNode_, 3)->IsCurrentFocus());

    /**
     * @tc.steps: step2. Call OnKeyEvent KEY_DPAD_RIGHT
     * @tc.expected: Trigger ShowNext
     */
    OnKeyEvent(KeyCode::KEY_DPAD_RIGHT, KeyAction::DOWN);
    EXPECT_EQ(pattern_->GetCurrentIndex(), 0);
    EXPECT_TRUE(GetChildFocusHub(frameNode_, 0)->IsCurrentFocus());
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
    GetChildFocusHub(frameNode_, 0)->RequestFocusImmediately();

    /**
     * @tc.steps: step1. Call OnKeyEvent KEY_DPAD_UP
     * @tc.expected: Trigger ShowPrevious
     */
    OnKeyEvent(KeyCode::KEY_DPAD_UP, KeyAction::DOWN);
    EXPECT_EQ(pattern_->GetCurrentIndex(), 3);
    EXPECT_TRUE(GetChildFocusHub(frameNode_, 3)->IsCurrentFocus());

    /**
     * @tc.steps: step2. Call OnKeyEvent KEY_DPAD_DOWN
     * @tc.expected: Trigger ShowNext
     */
    OnKeyEvent(KeyCode::KEY_DPAD_DOWN, KeyAction::DOWN);
    EXPECT_EQ(pattern_->GetCurrentIndex(), 0);
    EXPECT_TRUE(GetChildFocusHub(frameNode_, 0)->IsCurrentFocus());
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
    pattern_->isVisibleArea_ = false;

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
    pattern_->isVisibleArea_ = false;

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
    CreateSwiper();
    CreateSwiperItems();
    CreateSwiperDone();

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
    EXPECT_TRUE(CurrentIndex(0));
    EXPECT_EQ(GetChildX(frameNode_, 0), 0.f);
    EXPECT_EQ(GetChildX(frameNode_, 1), itemWidth);
    EXPECT_EQ(GetChildX(frameNode_, 2), itemWidth * 2);
    EXPECT_EQ(GetChildX(frameNode_, 3), itemWidth * 3);

    /**
     * @tc.steps: step3. ChangeIndex to 1
     * @tc.expected: Verify ignoreBlank is not effective
     */
    ChangeIndex(1);
    EXPECT_TRUE(CurrentIndex(1));
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
    EXPECT_TRUE(CurrentIndex(2));
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
    EXPECT_TRUE(CurrentIndex(0));
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
    model.SetLoop(false);
    model.SetPreviousMargin(Dimension(0.0_vp), true);
    model.SetItemSpace(Dimension(10.f));
    CreateSwiperItems(3);
    CreateSwiperDone();

    /**
     * @tc.steps: step2. check first item position
     * @tc.expected: current index is 0, prevMargin and itemspace is both 0.
     */
    EXPECT_TRUE(CurrentIndex(0));
    EXPECT_EQ(GetChildX(frameNode_, 0), 0);
}

/**
 * @tc.name: MarginIgnoreBlankTest004
 * @tc.desc: Test Swiper IgnoreBlank with itemSpace
 * @tc.type: FUNC
 */
HWTEST_F(SwiperCommonTestNg, MarginIgnoreBlankTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. CreateWith SetLoop true
     */
    SwiperModelNG model = CreateSwiper();
    model.SetLoop(false);
    model.SetPreviousMargin(Dimension(PRE_MARGIN), true);
    model.SetItemSpace(Dimension(10.f));
    CreateSwiperItems();
    CreateSwiperDone();

    /**
     * @tc.steps: step2. check index 1 item
     * @tc.expected: current index is 0, index 1 item will be measured.
     */
    EXPECT_NE(pattern_->itemPosition_.find(1), pattern_->itemPosition_.end());
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

/**
 * @tc.name: IsFocusNodeInItemPositionTest001
 * @tc.desc: Test IsFocusNodeInItemPosition functionality before and after page jump
 * @tc.type: FUNC
 */
TEST_F(SwiperCommonTestNg, IsFocusNodeInItemPositionAfterJumpTest)
{
    /**
     * @tc.steps: step1. currentIndex is 0
     * @tc.expected: only index 0 is focousable
     */
    SwiperModelNG model = CreateSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    auto childNode = frameNode_->GetChildAtIndex(1);
    auto targetFocusHub = childNode->GetFirstFocusHubChild();
    EXPECT_FALSE(pattern_->IsFocusNodeInItemPosition(targetFocusHub));
    childNode = frameNode_->GetChildAtIndex(0);
    targetFocusHub = childNode->GetFirstFocusHubChild();
    EXPECT_TRUE(pattern_->IsFocusNodeInItemPosition(targetFocusHub));

    /**
     * @tc.steps: step2. Change currentIndex to 2
     * @tc.expected: only index 2 is focousable
     */
    ChangeIndex(2);

    childNode = frameNode_->GetChildAtIndex(2);
    targetFocusHub = childNode->GetFirstFocusHubChild();
    EXPECT_TRUE(pattern_->IsFocusNodeInItemPosition(targetFocusHub));
    childNode = frameNode_->GetChildAtIndex(1);
    targetFocusHub = childNode->GetFirstFocusHubChild();
    EXPECT_FALSE(pattern_->IsFocusNodeInItemPosition(targetFocusHub));
}

/**
 * @tc.name: NeedStartNewAnimation001
 * @tc.desc: Test NeedStartNewAnimation
 * @tc.type: FUNC
 */
HWTEST_F(SwiperCommonTestNg, NeedStartNewAnimation001, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    CreateSwiperItems();
    CreateSwiperDone();

    pattern_->itemPositionInAnimation_.clear();
    OffsetF offset;
    EXPECT_TRUE(pattern_->NeedStartNewAnimation(offset));

    struct SwiperItemInfo swiperItemInfo1;
    struct SwiperItemInfo swiperItemInfo2;
    pattern_->itemPosition_.clear();
    swiperItemInfo1.startPos = 0.0f;
    swiperItemInfo1.endPos = 180.0f;
    pattern_->itemPosition_.emplace(std::make_pair(0, swiperItemInfo1));
    pattern_->itemPositionInAnimation_.emplace(std::make_pair(0, swiperItemInfo1));

    swiperItemInfo2.startPos = 180.0f;
    swiperItemInfo2.endPos = 360.0f;
    pattern_->itemPosition_.emplace(std::make_pair(0, swiperItemInfo2));
    pattern_->itemPositionInAnimation_.emplace(std::make_pair(0, swiperItemInfo2));

    EXPECT_FALSE(pattern_->NeedStartNewAnimation(offset));
}

/**
 * @tc.name: NextMarginIgnoreBlank001
 * @tc.desc: Test nextMargin and ignoreBlank
 * @tc.type: FUNC
 */
HWTEST_F(SwiperCommonTestNg, NextMarginIgnoreBlank001, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetLoop(false);
    model.SetIndex(4);
    model.SetNextMargin(Dimension(NEXT_MARGIN), true);
    CreateSwiperItems(5);
    CreateSwiperDone();

    EXPECT_EQ(pattern_->GetCurrentIndex(), 4);
    EXPECT_EQ(GetChildX(frameNode_, 3), NEXT_MARGIN - (SWIPER_WIDTH - NEXT_MARGIN));
    EXPECT_EQ(GetChildX(frameNode_, 4), NEXT_MARGIN);
}

/**
 * @tc.name: ResetOffscreenItemPosition001
 * @tc.desc: Test swiper layout ResetOffscreenItemPosition
 * @tc.type: FUNC
 */
HWTEST_F(SwiperCommonTestNg, ResetOffscreenItemPosition001, TestSize.Level1)
{
    CreateWithArrow();

    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper = LayoutWrapperNode(frameNode_, geometryNode, frameNode_->GetLayoutProperty());
    auto swiperLayoutAlgorithm = AceType::DynamicCast<SwiperLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());

    auto indicatorIndex = 4;
    auto indicatorGeometryNode = indicatorNode_->GetGeometryNode();
    auto indicatorOffset = indicatorGeometryNode->GetMarginFrameRect();
    swiperLayoutAlgorithm->ResetOffscreenItemPosition(&layoutWrapper, indicatorIndex, true);
    EXPECT_EQ(indicatorGeometryNode->GetMarginFrameRect(), indicatorOffset);

    auto leftArrowIndex = 5;
    auto leftArrowGeometryNode = leftArrowNode_->GetGeometryNode();
    auto leftArrowOffset = leftArrowGeometryNode->GetMarginFrameRect();
    swiperLayoutAlgorithm->ResetOffscreenItemPosition(&layoutWrapper, leftArrowIndex, true);
    EXPECT_EQ(leftArrowGeometryNode->GetMarginFrameRect(), leftArrowOffset);

    auto rightArrowIndex = 6;
    auto rightArrowGeometryNode = rightArrowNode_->GetGeometryNode();
    auto rightArrowOffset = rightArrowGeometryNode->GetMarginFrameRect();
    swiperLayoutAlgorithm->ResetOffscreenItemPosition(&layoutWrapper, rightArrowIndex, true);
    EXPECT_EQ(rightArrowGeometryNode->GetMarginFrameRect(), rightArrowOffset);
}

/**
 * @tc.name: ShowCachedItems001
 * @tc.desc: Test show cached items on loop = false, cachedCount = 1
 * @tc.type: FUNC
 */
HWTEST_F(SwiperCommonTestNg, ShowCachedItems001, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetLoop(false);
    model.SetCachedIsShown(true);
    model.SetDisplayCount(1);
    model.SetCachedCount(1);
    model.SetIndex(0);
    CreateSwiperItems(5);
    CreateSwiperDone();
    FlushUITasks();

    ASSERT_EQ(static_cast<int32_t>(pattern_->itemPosition_.size()), 2);
    EXPECT_EQ(pattern_->itemPosition_[0].startPos, 0.0f);
    EXPECT_EQ(pattern_->itemPosition_[1].startPos, 480.0f);

    pattern_->UpdateCurrentOffset(-100.0f);
    FlushUITasks();
    ASSERT_EQ(static_cast<int32_t>(pattern_->itemPosition_.size()), 3);
    EXPECT_EQ(pattern_->itemPosition_[0].startPos, -100.0f);
    EXPECT_EQ(pattern_->itemPosition_[1].startPos, 380.0f);
    EXPECT_EQ(pattern_->itemPosition_[2].startPos, 860.0f);

    pattern_->ChangeIndex(1, false);
    FlushUITasks();
    ASSERT_EQ(static_cast<int32_t>(pattern_->itemPosition_.size()), 3);
    EXPECT_EQ(pattern_->itemPosition_[0].startPos, -480.0f);
    EXPECT_EQ(pattern_->itemPosition_[1].startPos, 0.0f);
    EXPECT_EQ(pattern_->itemPosition_[2].startPos, 480.0f);

    pattern_->UpdateCurrentOffset(-100.0f);
    FlushUITasks();
    ASSERT_EQ(static_cast<int32_t>(pattern_->itemPosition_.size()), 4);
    EXPECT_EQ(pattern_->itemPosition_[0].startPos, -580.0f);
    EXPECT_EQ(pattern_->itemPosition_[1].startPos, -100.0f);
    EXPECT_EQ(pattern_->itemPosition_[2].startPos, 380.0f);
    EXPECT_EQ(pattern_->itemPosition_[3].startPos, 860.0f);

    pattern_->ChangeIndex(4, false);
    FlushUITasks();
    ASSERT_EQ(static_cast<int32_t>(pattern_->itemPosition_.size()), 2);
    EXPECT_EQ(pattern_->itemPosition_[3].startPos, -480.0f);
    EXPECT_EQ(pattern_->itemPosition_[4].startPos, 0.0f);
}

/**
 * @tc.name: ShowCachedItems002
 * @tc.desc: Test show cached items on loop = false, cachedCount = 2
 * @tc.type: FUNC
 */
HWTEST_F(SwiperCommonTestNg, ShowCachedItems002, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetLoop(false);
    model.SetCachedIsShown(true);
    model.SetDisplayCount(1);
    model.SetCachedCount(2);
    model.SetIndex(0);
    CreateSwiperItems(5);
    CreateSwiperDone();
    FlushUITasks();

    ASSERT_EQ(static_cast<int32_t>(pattern_->itemPosition_.size()), 3);
    EXPECT_EQ(pattern_->itemPosition_[0].startPos, 0.0f);
    EXPECT_EQ(pattern_->itemPosition_[1].startPos, 480.0f);
    EXPECT_EQ(pattern_->itemPosition_[2].startPos, 960.0f);

    pattern_->UpdateCurrentOffset(-100.0f);
    FlushUITasks();
    ASSERT_EQ(static_cast<int32_t>(pattern_->itemPosition_.size()), 4);
    EXPECT_EQ(pattern_->itemPosition_[0].startPos, -100.0f);
    EXPECT_EQ(pattern_->itemPosition_[1].startPos, 380.0f);
    EXPECT_EQ(pattern_->itemPosition_[2].startPos, 860.0f);
    EXPECT_EQ(pattern_->itemPosition_[3].startPos, 1340.0f);

    pattern_->ChangeIndex(1, false);
    FlushUITasks();
    ASSERT_EQ(static_cast<int32_t>(pattern_->itemPosition_.size()), 4);
    EXPECT_EQ(pattern_->itemPosition_[0].startPos, -480.0f);
    EXPECT_EQ(pattern_->itemPosition_[1].startPos, 0.0f);
    EXPECT_EQ(pattern_->itemPosition_[2].startPos, 480.0f);
    EXPECT_EQ(pattern_->itemPosition_[3].startPos, 960.0f);

    pattern_->UpdateCurrentOffset(-100.0f);
    FlushUITasks();
    ASSERT_EQ(static_cast<int32_t>(pattern_->itemPosition_.size()), 5);
    EXPECT_EQ(pattern_->itemPosition_[0].startPos, -580.0f);
    EXPECT_EQ(pattern_->itemPosition_[1].startPos, -100.0f);
    EXPECT_EQ(pattern_->itemPosition_[2].startPos, 380.0f);
    EXPECT_EQ(pattern_->itemPosition_[3].startPos, 860.0f);
    EXPECT_EQ(pattern_->itemPosition_[4].startPos, 1340.0f);

    pattern_->ChangeIndex(4, false);
    FlushUITasks();
    ASSERT_EQ(static_cast<int32_t>(pattern_->itemPosition_.size()), 3);
    EXPECT_EQ(pattern_->itemPosition_[2].startPos, -960.0f);
    EXPECT_EQ(pattern_->itemPosition_[3].startPos, -480.0f);
    EXPECT_EQ(pattern_->itemPosition_[4].startPos, 0.0f);
}

/**
 * @tc.name: ShowCachedItems003
 * @tc.desc: Test show cached items on loop = false, cachedCount = 3
 * @tc.type: FUNC
 */
HWTEST_F(SwiperCommonTestNg, ShowCachedItems003, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetLoop(false);
    model.SetCachedIsShown(true);
    model.SetDisplayCount(1);
    model.SetCachedCount(3);
    model.SetIndex(0);
    CreateSwiperItems(5);
    CreateSwiperDone();
    FlushUITasks();

    ASSERT_EQ(static_cast<int32_t>(pattern_->itemPosition_.size()), 4);
    EXPECT_EQ(pattern_->itemPosition_[0].startPos, 0.0f);
    EXPECT_EQ(pattern_->itemPosition_[1].startPos, 480.0f);
    EXPECT_EQ(pattern_->itemPosition_[2].startPos, 960.0f);
    EXPECT_EQ(pattern_->itemPosition_[3].startPos, 1440.0f);

    pattern_->UpdateCurrentOffset(-100.0f);
    FlushUITasks();
    ASSERT_EQ(static_cast<int32_t>(pattern_->itemPosition_.size()), 5);
    EXPECT_EQ(pattern_->itemPosition_[0].startPos, -100.0f);
    EXPECT_EQ(pattern_->itemPosition_[1].startPos, 380.0f);
    EXPECT_EQ(pattern_->itemPosition_[2].startPos, 860.0f);
    EXPECT_EQ(pattern_->itemPosition_[3].startPos, 1340.0f);
    EXPECT_EQ(pattern_->itemPosition_[4].startPos, 1820.0f);

    pattern_->ChangeIndex(1, false);
    FlushUITasks();
    ASSERT_EQ(static_cast<int32_t>(pattern_->itemPosition_.size()), 5);
    EXPECT_EQ(pattern_->itemPosition_[0].startPos, -480.0f);
    EXPECT_EQ(pattern_->itemPosition_[1].startPos, 0.0f);
    EXPECT_EQ(pattern_->itemPosition_[2].startPos, 480.0f);
    EXPECT_EQ(pattern_->itemPosition_[3].startPos, 960.0f);
    EXPECT_EQ(pattern_->itemPosition_[4].startPos, 1440.0f);

    pattern_->UpdateCurrentOffset(-100.0f);
    FlushUITasks();
    ASSERT_EQ(static_cast<int32_t>(pattern_->itemPosition_.size()), 5);
    EXPECT_EQ(pattern_->itemPosition_[0].startPos, -580.0f);
    EXPECT_EQ(pattern_->itemPosition_[1].startPos, -100.0f);
    EXPECT_EQ(pattern_->itemPosition_[2].startPos, 380.0f);
    EXPECT_EQ(pattern_->itemPosition_[3].startPos, 860.0f);
    EXPECT_EQ(pattern_->itemPosition_[4].startPos, 1340.0f);

    pattern_->ChangeIndex(4, false);
    FlushUITasks();
    ASSERT_EQ(static_cast<int32_t>(pattern_->itemPosition_.size()), 4);
    EXPECT_EQ(pattern_->itemPosition_[1].startPos, -1440.0f);
    EXPECT_EQ(pattern_->itemPosition_[2].startPos, -960.0f);
    EXPECT_EQ(pattern_->itemPosition_[3].startPos, -480.0f);
    EXPECT_EQ(pattern_->itemPosition_[4].startPos, 0.0f);
}

/**
 * @tc.name: ShowCachedItems004
 * @tc.desc: Test show cached items on loop = false, displayCount = 3
 * @tc.type: FUNC
 */
HWTEST_F(SwiperCommonTestNg, ShowCachedItems004, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetLoop(false);
    model.SetCachedIsShown(true);
    model.SetDisplayCount(3);
    model.SetCachedCount(1);
    model.SetIndex(4);
    CreateSwiperItems(10);
    CreateSwiperDone();
    FlushUITasks();

    ASSERT_EQ(static_cast<int32_t>(pattern_->itemPosition_.size()), 5);
    EXPECT_EQ(pattern_->itemPosition_[3].startPos, -160.0f);
    EXPECT_EQ(pattern_->itemPosition_[4].startPos, 0.0f);
    EXPECT_EQ(pattern_->itemPosition_[5].startPos, 160.0f);
    EXPECT_EQ(pattern_->itemPosition_[6].startPos, 320.0f);
    EXPECT_EQ(pattern_->itemPosition_[7].startPos, 480.0f);

    pattern_->UpdateCurrentOffset(-100.0f);
    FlushUITasks();
    ASSERT_EQ(static_cast<int32_t>(pattern_->itemPosition_.size()), 6);
    EXPECT_EQ(pattern_->itemPosition_[3].startPos, -260.0f);
    EXPECT_EQ(pattern_->itemPosition_[4].startPos, -100.0f);
    EXPECT_EQ(pattern_->itemPosition_[5].startPos, 60.0f);
    EXPECT_EQ(pattern_->itemPosition_[6].startPos, 220.0f);
    EXPECT_EQ(pattern_->itemPosition_[7].startPos, 380.0f);
    EXPECT_EQ(pattern_->itemPosition_[8].startPos, 540.0f);

    pattern_->UpdateCurrentOffset(-100.0f);
    FlushUITasks();
    ASSERT_EQ(static_cast<int32_t>(pattern_->itemPosition_.size()), 6);
    EXPECT_EQ(pattern_->itemPosition_[4].startPos, -200.0f);
    EXPECT_EQ(pattern_->itemPosition_[5].startPos, -40.0f);
    EXPECT_EQ(pattern_->itemPosition_[6].startPos, 120.0f);
    EXPECT_EQ(pattern_->itemPosition_[7].startPos, 280.0f);
    EXPECT_EQ(pattern_->itemPosition_[8].startPos, 440.0f);
    EXPECT_EQ(pattern_->itemPosition_[9].startPos, 600.0f);

    pattern_->ChangeIndex(7, false);
    FlushUITasks();
    ASSERT_EQ(static_cast<int32_t>(pattern_->itemPosition_.size()), 4);
    EXPECT_EQ(pattern_->itemPosition_[6].startPos, -160.0f);
    EXPECT_EQ(pattern_->itemPosition_[7].startPos, 0.0f);
    EXPECT_EQ(pattern_->itemPosition_[8].startPos, 160.0f);
    EXPECT_EQ(pattern_->itemPosition_[9].startPos, 320.0f);
}

/**
 * @tc.name: ShowCachedItems005
 * @tc.desc: Test show cached items on loop = false, cachedCount = 2, set nextMargin and prevMargin
 * @tc.type: FUNC
 */
HWTEST_F(SwiperCommonTestNg, ShowCachedItems005, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetLoop(false);
    model.SetCachedIsShown(true);
    model.SetDisplayCount(1);
    model.SetCachedCount(2);
    model.SetIndex(4);
    model.SetNextMargin(Dimension(10, DimensionUnit::PX), false);
    model.SetPreviousMargin(Dimension(10, DimensionUnit::PX), false);
    model.SetItemSpace(Dimension(10, DimensionUnit::PX));
    CreateSwiperItems(10);
    CreateSwiperDone();
    FlushUITasks();

    ASSERT_EQ(static_cast<int32_t>(pattern_->itemPosition_.size()), 7);
    EXPECT_EQ(pattern_->itemPosition_[1].startPos, -1350.0f);
    EXPECT_EQ(pattern_->itemPosition_[2].startPos, -900.0f);
    EXPECT_EQ(pattern_->itemPosition_[3].startPos, -450.0f);
    EXPECT_EQ(pattern_->itemPosition_[3].endPos, -10.0f);
    EXPECT_EQ(pattern_->itemPosition_[4].startPos, 0.0f);
    EXPECT_EQ(pattern_->itemPosition_[4].endPos, 440.0f);
    EXPECT_EQ(pattern_->itemPosition_[5].startPos, 450.0f);
    EXPECT_EQ(pattern_->itemPosition_[6].startPos, 900.0f);
    EXPECT_EQ(pattern_->itemPosition_[7].startPos, 1350.0f);

    pattern_->UpdateCurrentOffset(-100.0f);
    FlushUITasks();
    ASSERT_EQ(static_cast<int32_t>(pattern_->itemPosition_.size()), 6);
    EXPECT_EQ(pattern_->itemPosition_[2].startPos, -1000.0f);
    EXPECT_EQ(pattern_->itemPosition_[3].startPos, -550.0f);
    EXPECT_EQ(pattern_->itemPosition_[4].startPos, -100.0f);
    EXPECT_EQ(pattern_->itemPosition_[5].startPos, 350.0f);
    EXPECT_EQ(pattern_->itemPosition_[6].startPos, 800.0f);
    EXPECT_EQ(pattern_->itemPosition_[7].startPos, 1250.0f);

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
    ASSERT_EQ(static_cast<int32_t>(pattern_->itemPosition_.size()), 4);
    EXPECT_EQ(pattern_->itemPosition_[6].startPos, -1350.0f);
    EXPECT_EQ(pattern_->itemPosition_[7].startPos, -900.0f);
    EXPECT_EQ(pattern_->itemPosition_[8].startPos, -450.0f);
    EXPECT_EQ(pattern_->itemPosition_[9].startPos, 0.0f);
}

/**
 * @tc.name: ShowCachedItems006
 * @tc.desc: Test show cached items on loop = true, cachedCount = 1
 * @tc.type: FUNC
 */
HWTEST_F(SwiperCommonTestNg, ShowCachedItems006, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetLoop(true);
    model.SetCachedIsShown(true);
    model.SetDisplayCount(1);
    model.SetCachedCount(1);
    model.SetIndex(0);
    CreateSwiperItems(5);
    CreateSwiperDone();
    FlushUITasks();

    ASSERT_EQ(static_cast<int32_t>(pattern_->itemPosition_.size()), 3);
    EXPECT_EQ(pattern_->itemPosition_[-1].startPos, -480.0f);
    EXPECT_EQ(pattern_->itemPosition_[0].startPos, 0.0f);
    EXPECT_EQ(pattern_->itemPosition_[1].startPos, 480.0f);

    pattern_->UpdateCurrentOffset(-100.0f);
    FlushUITasks();
    ASSERT_EQ(static_cast<int32_t>(pattern_->itemPosition_.size()), 4);
    EXPECT_EQ(pattern_->itemPosition_[-1].startPos, -580.0f);
    EXPECT_EQ(pattern_->itemPosition_[0].startPos, -100.0f);
    EXPECT_EQ(pattern_->itemPosition_[1].startPos, 380.0f);
    EXPECT_EQ(pattern_->itemPosition_[2].startPos, 860.0f);

    pattern_->ChangeIndex(1, false);
    FlushUITasks();
    ASSERT_EQ(static_cast<int32_t>(pattern_->itemPosition_.size()), 3);
    EXPECT_EQ(pattern_->itemPosition_[0].startPos, -480.0f);
    EXPECT_EQ(pattern_->itemPosition_[1].startPos, 0.0f);
    EXPECT_EQ(pattern_->itemPosition_[2].startPos, 480.0f);

    pattern_->UpdateCurrentOffset(-100.0f);
    FlushUITasks();
    ASSERT_EQ(static_cast<int32_t>(pattern_->itemPosition_.size()), 4);
    EXPECT_EQ(pattern_->itemPosition_[0].startPos, -580.0f);
    EXPECT_EQ(pattern_->itemPosition_[1].startPos, -100.0f);
    EXPECT_EQ(pattern_->itemPosition_[2].startPos, 380.0f);
    EXPECT_EQ(pattern_->itemPosition_[3].startPos, 860.0f);

    pattern_->ChangeIndex(4, false);
    FlushUITasks();
    ASSERT_EQ(static_cast<int32_t>(pattern_->itemPosition_.size()), 3);
    EXPECT_EQ(pattern_->itemPosition_[3].startPos, -480.0f);
    EXPECT_EQ(pattern_->itemPosition_[4].startPos, 0.0f);
    EXPECT_EQ(pattern_->itemPosition_[5].startPos, 480.0f);
}

/**
 * @tc.name: ShowCachedItems007
 * @tc.desc: Test show cached items on loop = true, cachedCount = 2
 * @tc.type: FUNC
 */
HWTEST_F(SwiperCommonTestNg, ShowCachedItems007, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetLoop(true);
    model.SetCachedIsShown(true);
    model.SetDisplayCount(1);
    model.SetCachedCount(2);
    model.SetIndex(0);
    CreateSwiperItems(5);
    CreateSwiperDone();
    FlushUITasks();

    ASSERT_EQ(static_cast<int32_t>(pattern_->itemPosition_.size()), 5);
    EXPECT_EQ(pattern_->itemPosition_[-2].startPos, -960.0f);
    EXPECT_EQ(pattern_->itemPosition_[-1].startPos, -480.0f);
    EXPECT_EQ(pattern_->itemPosition_[0].startPos, 0.0f);
    EXPECT_EQ(pattern_->itemPosition_[1].startPos, 480.0f);
    EXPECT_EQ(pattern_->itemPosition_[2].startPos, 960.0f);

    pattern_->UpdateCurrentOffset(-100.0f);
    FlushUITasks();
    ASSERT_EQ(static_cast<int32_t>(pattern_->itemPosition_.size()), 5);
    EXPECT_EQ(pattern_->itemPosition_[-1].startPos, -580.0f);
    EXPECT_EQ(pattern_->itemPosition_[0].startPos, -100.0f);
    EXPECT_EQ(pattern_->itemPosition_[1].startPos, 380.0f);
    EXPECT_EQ(pattern_->itemPosition_[2].startPos, 860.0f);
    EXPECT_EQ(pattern_->itemPosition_[3].startPos, 1340.0f);

    pattern_->ChangeIndex(1, false);
    FlushUITasks();
    ASSERT_EQ(static_cast<int32_t>(pattern_->itemPosition_.size()), 5);
    EXPECT_EQ(pattern_->itemPosition_[-1].startPos, -960.0f);
    EXPECT_EQ(pattern_->itemPosition_[0].startPos, -480.0f);
    EXPECT_EQ(pattern_->itemPosition_[1].startPos, 0.0f);
    EXPECT_EQ(pattern_->itemPosition_[2].startPos, 480.0f);
    EXPECT_EQ(pattern_->itemPosition_[3].startPos, 960.0f);

    pattern_->UpdateCurrentOffset(-100.0f);
    FlushUITasks();
    ASSERT_EQ(static_cast<int32_t>(pattern_->itemPosition_.size()), 5);
    EXPECT_EQ(pattern_->itemPosition_[0].startPos, -580.0f);
    EXPECT_EQ(pattern_->itemPosition_[1].startPos, -100.0f);
    EXPECT_EQ(pattern_->itemPosition_[2].startPos, 380.0f);
    EXPECT_EQ(pattern_->itemPosition_[3].startPos, 860.0f);
    EXPECT_EQ(pattern_->itemPosition_[4].startPos, 1340.0f);

    pattern_->ChangeIndex(4, false);
    FlushUITasks();
    ASSERT_EQ(static_cast<int32_t>(pattern_->itemPosition_.size()), 5);
    EXPECT_EQ(pattern_->itemPosition_[2].startPos, -960.0f);
    EXPECT_EQ(pattern_->itemPosition_[3].startPos, -480.0f);
    EXPECT_EQ(pattern_->itemPosition_[4].startPos, 0.0f);
    EXPECT_EQ(pattern_->itemPosition_[5].startPos, 480.0f);
    EXPECT_EQ(pattern_->itemPosition_[6].startPos, 960.0f);
}

/**
 * @tc.name: ShowCachedItems008
 * @tc.desc: Test show cached items on loop = true, cachedCount = 3
 * @tc.type: FUNC
 */
HWTEST_F(SwiperCommonTestNg, ShowCachedItems008, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetLoop(true);
    model.SetCachedIsShown(true);
    model.SetDisplayCount(1);
    model.SetCachedCount(3);
    model.SetIndex(0);
    CreateSwiperItems(5);
    CreateSwiperDone();
    FlushUITasks();

    ASSERT_EQ(static_cast<int32_t>(pattern_->itemPosition_.size()), 5);
    EXPECT_EQ(pattern_->itemPosition_[-2].startPos, -960.0f);
    EXPECT_EQ(pattern_->itemPosition_[-1].startPos, -480.0f);
    EXPECT_EQ(pattern_->itemPosition_[0].startPos, 0.0f);
    EXPECT_EQ(pattern_->itemPosition_[1].startPos, 480.0f);
    EXPECT_EQ(pattern_->itemPosition_[2].startPos, 960.0f);

    pattern_->UpdateCurrentOffset(-100.0f);
    FlushUITasks();
    ASSERT_EQ(static_cast<int32_t>(pattern_->itemPosition_.size()), 5);
    EXPECT_EQ(pattern_->itemPosition_[-1].startPos, -580.0f);
    EXPECT_EQ(pattern_->itemPosition_[0].startPos, -100.0f);
    EXPECT_EQ(pattern_->itemPosition_[1].startPos, 380.0f);
    EXPECT_EQ(pattern_->itemPosition_[2].startPos, 860.0f);
    EXPECT_EQ(pattern_->itemPosition_[3].startPos, 1340.0f);

    pattern_->ChangeIndex(1, false);
    FlushUITasks();
    ASSERT_EQ(static_cast<int32_t>(pattern_->itemPosition_.size()), 5);
    EXPECT_EQ(pattern_->itemPosition_[-1].startPos, -960.0f);
    EXPECT_EQ(pattern_->itemPosition_[0].startPos, -480.0f);
    EXPECT_EQ(pattern_->itemPosition_[1].startPos, 0.0f);
    EXPECT_EQ(pattern_->itemPosition_[2].startPos, 480.0f);
    EXPECT_EQ(pattern_->itemPosition_[3].startPos, 960.0f);

    pattern_->UpdateCurrentOffset(-100.0f);
    FlushUITasks();
    ASSERT_EQ(static_cast<int32_t>(pattern_->itemPosition_.size()), 5);
    EXPECT_EQ(pattern_->itemPosition_[0].startPos, -580.0f);
    EXPECT_EQ(pattern_->itemPosition_[1].startPos, -100.0f);
    EXPECT_EQ(pattern_->itemPosition_[2].startPos, 380.0f);
    EXPECT_EQ(pattern_->itemPosition_[3].startPos, 860.0f);
    EXPECT_EQ(pattern_->itemPosition_[4].startPos, 1340.0f);

    pattern_->ChangeIndex(4, false);
    FlushUITasks();
    ASSERT_EQ(static_cast<int32_t>(pattern_->itemPosition_.size()), 5);
    EXPECT_EQ(pattern_->itemPosition_[2].startPos, -960.0f);
    EXPECT_EQ(pattern_->itemPosition_[3].startPos, -480.0f);
    EXPECT_EQ(pattern_->itemPosition_[4].startPos, 0.0f);
    EXPECT_EQ(pattern_->itemPosition_[5].startPos, 480.0f);
    EXPECT_EQ(pattern_->itemPosition_[6].startPos, 960.0f);
}

/**
 * @tc.name: ShowCachedItems009
 * @tc.desc: Test show cached items on loop = true, displayCount = 3
 * @tc.type: FUNC
 */
HWTEST_F(SwiperCommonTestNg, ShowCachedItems009, TestSize.Level1)
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
HWTEST_F(SwiperCommonTestNg, ShowCachedItems010, TestSize.Level1)
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
HWTEST_F(SwiperCommonTestNg, ShowCachedItems011, TestSize.Level1)
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
HWTEST_F(SwiperCommonTestNg, ShowCachedItems012, TestSize.Level1)
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
HWTEST_F(SwiperCommonTestNg, ShowCachedItems024, TestSize.Level1)
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
HWTEST_F(SwiperCommonTestNg, UpdateOnUnselectedEvent, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<SwiperPattern>();
    ASSERT_NE(pattern, nullptr);
    auto eventHub = frameNode->GetOrCreateEventHub<SwiperEventHub>();
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
HWTEST_F(SwiperCommonTestNg, UpdateOnSelectedEvent, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<SwiperPattern>();
    ASSERT_NE(pattern, nullptr);
    auto eventHub = frameNode->GetOrCreateEventHub<SwiperEventHub>();
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
HWTEST_F(SwiperCommonTestNg, SetAutoPlayOptions001, TestSize.Level1)
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
HWTEST_F(SwiperCommonTestNg, SwiperIndicatorAccessibilityProperty001, TestSize.Level1)
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
} // namespace OHOS::Ace::NG
