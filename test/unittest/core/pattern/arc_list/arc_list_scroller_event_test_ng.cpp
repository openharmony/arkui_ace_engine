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

#include "arc_list_test_ng.h"

namespace OHOS::Ace::NG {

namespace {} // namespace

class ArcListScrollerEventTestNg : public ArcListTestNg {
public:
};

/**
 * @tc.name: Event001
 * @tc.desc: Test scroll callback
 * @tc.type: FUNC
 */
HWTEST_F(ArcListScrollerEventTestNg, Event001, TestSize.Level1)
{
    bool isTrigger = false;
    auto event = [&isTrigger](Dimension offset, ScrollState state) { isTrigger = true; };
    ListModelNG model = CreateList();
    model.SetOnScroll(event);
    CreateListItems(TOTAL_ITEM_NUMBER);
    CreateDone();

    /**
     * @tc.steps: step1. Cover condition that GetMinPlatformVersion() >= 10  && scrollStop_ && !GetScrollAbort()
     */
    isTrigger = false;
    UpdateCurrentOffset(-ITEM_HEIGHT, SCROLL_FROM_UPDATE);
    EXPECT_TRUE(isTrigger);

    isTrigger = false;
    UpdateCurrentOffset(ITEM_HEIGHT, SCROLL_FROM_AXIS);
    EXPECT_TRUE(isTrigger);

    isTrigger = false;
    UpdateCurrentOffset(-ITEM_HEIGHT, SCROLL_FROM_BAR);
    EXPECT_TRUE(isTrigger);

    isTrigger = false;
    UpdateCurrentOffset(ITEM_HEIGHT, SCROLL_FROM_ANIMATION);
    EXPECT_TRUE(isTrigger);

    isTrigger = false;
    UpdateCurrentOffset(-ITEM_HEIGHT, SCROLL_FROM_ANIMATION_SPRING);
    EXPECT_TRUE(isTrigger);

    isTrigger = false;
    UpdateCurrentOffset(ITEM_HEIGHT, SCROLL_FROM_NONE);
    EXPECT_TRUE(isTrigger);

    /**
     * @tc.steps: step2. Cover condition that onScroll && !NearZero(finalOffset)
     */
    isTrigger = false;
    pattern_->UpdateCurrentOffset(-ITEM_HEIGHT, SCROLL_FROM_UPDATE);
    pattern_->OnScrollEndCallback(); // set scrollStop_ to true
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(isTrigger);

    isTrigger = false;
    pattern_->UpdateCurrentOffset(ITEM_HEIGHT, SCROLL_FROM_ANIMATION);
    pattern_->OnScrollEndCallback();
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(isTrigger);

    isTrigger = false;
    pattern_->UpdateCurrentOffset(-ITEM_HEIGHT, SCROLL_FROM_ANIMATION_SPRING);
    pattern_->OnScrollEndCallback();
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(isTrigger);

    isTrigger = false;
    pattern_->UpdateCurrentOffset(ITEM_HEIGHT, SCROLL_FROM_NONE);
    pattern_->OnScrollEndCallback();
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(isTrigger);

    isTrigger = false;
    pattern_->UpdateCurrentOffset(-ITEM_HEIGHT, SCROLL_FROM_AXIS);
    pattern_->OnScrollEndCallback();
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(isTrigger);

    isTrigger = false;
    pattern_->UpdateCurrentOffset(ITEM_HEIGHT, SCROLL_FROM_BAR);
    pattern_->OnScrollEndCallback();
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(isTrigger);

    isTrigger = false;
    pattern_->UpdateCurrentOffset(-ITEM_HEIGHT, SCROLL_FROM_ANIMATION_CONTROLLER);
    pattern_->OnScrollEndCallback();
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(isTrigger);

    isTrigger = false;
    pattern_->UpdateCurrentOffset(ITEM_HEIGHT, SCROLL_FROM_BAR_FLING);
    pattern_->OnScrollEndCallback();
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(isTrigger);

    // SetMinPlatformVersion
    MockPipelineContext::pipeline_->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_NINE));

    isTrigger = false;
    pattern_->UpdateCurrentOffset(-ITEM_HEIGHT, SCROLL_FROM_AXIS);
    pattern_->OnScrollEndCallback(); // set scrollStop_ to true
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(isTrigger);

    isTrigger = false;
    pattern_->UpdateCurrentOffset(ITEM_HEIGHT, SCROLL_FROM_BAR);
    pattern_->OnScrollEndCallback();
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(isTrigger);

    isTrigger = false;
    pattern_->UpdateCurrentOffset(-ITEM_HEIGHT, SCROLL_FROM_ANIMATION_CONTROLLER);
    pattern_->OnScrollEndCallback();
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(isTrigger);

    // set back
    MockPipelineContext::pipeline_->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_TEN));
}

/**
 * @tc.name: Event002
 * @tc.desc: Test scroll callback
 * @tc.type: FUNC
 */
HWTEST_F(ArcListScrollerEventTestNg, Event002, TestSize.Level1)
{
    int32_t startIndex;
    int32_t endIndex;
    int32_t centerIndex;
    auto event = [&startIndex, &endIndex, &centerIndex](int32_t start, int32_t end, int32_t center) {
        startIndex = start;
        endIndex = end;
        centerIndex = center;
    };
    ListModelNG model = CreateList();
    model.SetOnScrollIndex(event);
    CreateListItems(TOTAL_ITEM_NUMBER);
    CreateDone();

    ScrollDown();
    EXPECT_EQ(startIndex, 0);
    EXPECT_EQ(endIndex, 2);
    EXPECT_EQ(centerIndex, 0);

    ScrollDown();
    EXPECT_EQ(startIndex, 0);
    EXPECT_EQ(endIndex, 3);
    EXPECT_EQ(centerIndex, 1);
}

/**
 * @tc.name: Event003
 * @tc.desc: Test scroll callback
 * @tc.type: FUNC
 */
HWTEST_F(ArcListScrollerEventTestNg, Event003, TestSize.Level1)
{
    bool isTrigger = false;
    auto event = [&isTrigger]() { isTrigger = true; };
    ListModelNG model = CreateList();
    model.SetOnReachStart(event);
    CreateListItems(TOTAL_ITEM_NUMBER);
    CreateDone();

    /**
     * @tc.steps: step1. arc_list first init will trigger ReachStart.
     */
    EXPECT_FALSE(isTrigger);

    /**
     * @tc.steps: step2. Scroll to middle.
     */
    isTrigger = false;
    ScrollDown();
    EXPECT_FALSE(isTrigger);

    /**
     * @tc.steps: step3. Scroll up half item.
     */
    UpdateCurrentOffset(ITEM_HEIGHT / 2.0f);

    /**
     * @tc.steps: step4. Scroll up to start
     */
    isTrigger = true;
    ScrollUp(2);
    EXPECT_TRUE(isTrigger);
}

/**
 * @tc.name: Event004
 * @tc.desc: Test scroll callback
 * @tc.type: FUNC
 */
HWTEST_F(ArcListScrollerEventTestNg, Event004, TestSize.Level1)
{
    bool isTrigger = false;
    auto event = [&isTrigger]() { isTrigger = true; };
    ListModelNG model = CreateList();
    model.SetOnReachEnd(event);
    CreateListItems(TOTAL_ITEM_NUMBER);
    CreateDone();

    /**
     * @tc.steps: step1. Scroll down to end
     */
    ScrollDown(3);
    EXPECT_FALSE(isTrigger);
}

/**
 * @tc.name: Event005
 * @tc.desc: Verify onScrollStart, onScrollStop callback
 * @tc.type: FUNC
 */
HWTEST_F(ArcListScrollerEventTestNg, Event005, TestSize.Level1)
{
    bool isScrollStartCalled = false;
    bool isScrollStopCalled = false;
    auto scrollStart = [&isScrollStartCalled]() { isScrollStartCalled = true; };
    auto scrollStop = [&isScrollStopCalled]() { isScrollStopCalled = true; };
    ListModelNG model = CreateList();
    model.SetChainAnimation(true);
    model.SetChainAnimationOptions({ Dimension(0), Dimension(10), 0, 0, 0, DEFAULT_STIFFNESS, DEFAULT_DAMPING });
    model.SetOnScrollStart(scrollStart);
    model.SetOnScrollStop(scrollStop);
    CreateListItems(TOTAL_ITEM_NUMBER);
    CreateDone();

    pattern_->OnScrollCallback(100.f, SCROLL_FROM_START);
    EXPECT_TRUE(isScrollStartCalled);

    pattern_->OnScrollEndCallback();
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(isScrollStopCalled);

    isScrollStopCalled = false;
    pattern_->OnScrollEndCallback();
    pattern_->SetScrollAbort(true);
    FlushLayoutTask(frameNode_);
    EXPECT_FALSE(isScrollStopCalled);
}

/**
 * @tc.name: Event006
 * @tc.desc: Test other condition
 * @tc.type: FUNC
 */
HWTEST_F(ArcListScrollerEventTestNg, Event006, TestSize.Level1)
{
    auto event = [](Dimension, ScrollState) {
        ScrollFrameResult result;
        return result;
    };
    ListModelNG model = CreateList();
    model.SetOnScrollFrameBegin(event);
    CreateListItems(TOTAL_ITEM_NUMBER);
    CreateDone();

    auto scrollableEvent = pattern_->GetScrollableEvent();
    ASSERT_NE(scrollableEvent, nullptr);
    auto scrollable = scrollableEvent->GetScrollable();
    EXPECT_NE(scrollable->callback_, nullptr);
    FlushLayoutTask(frameNode_);
}

/**
 * @tc.name: onWillScrollAndOnDidScroll001
 * @tc.desc: Test scroll callback
 * @tc.type: FUNC
 */
HWTEST_F(ArcListScrollerEventTestNg, onWillScrollAndOnDidScroll001, TestSize.Level1)
{
    bool isWillTrigger = false;
    bool isDidTrigger = false;
    Dimension willOffset;
    Dimension didOffset;
    auto willTriggerEvent = [&isWillTrigger, &willOffset](Dimension offset, ScrollState state, ScrollSource source) {
        isWillTrigger = true;
        willOffset = offset;
        ScrollFrameResult result;
        result.offset = offset;
        return result;
    };
    auto didTriggerEvent = [&isDidTrigger, &didOffset](Dimension offset, ScrollState state) {
        isDidTrigger = true;
        didOffset = offset;
    };
    CreateList();
    CreateListItems(TOTAL_ITEM_NUMBER);
    CreateDone();
    eventHub_->SetOnWillScroll(willTriggerEvent);
    eventHub_->SetOnDidScroll(didTriggerEvent);

    /**
     * @tc.steps: Cover condition that  scrollStop_ && !GetScrollAbort()
     */
    isWillTrigger = false;
    isDidTrigger = false;
    willOffset.Reset();
    didOffset.Reset();
    UpdateCurrentOffset(-ITEM_HEIGHT, SCROLL_FROM_UPDATE);
    EXPECT_TRUE(isWillTrigger);
    EXPECT_TRUE(isDidTrigger);
    EXPECT_EQ(willOffset.Value(), ITEM_HEIGHT);
    EXPECT_EQ(didOffset.Value(), -50);

    isWillTrigger = false;
    isDidTrigger = false;
    willOffset.Reset();
    didOffset.Reset();
    UpdateCurrentOffset(ITEM_HEIGHT, SCROLL_FROM_AXIS);
    EXPECT_TRUE(isWillTrigger);
    EXPECT_TRUE(isDidTrigger);
    EXPECT_EQ(willOffset.Value(), -ITEM_HEIGHT);
    EXPECT_EQ(didOffset.Value(), -ITEM_HEIGHT);

    isWillTrigger = false;
    isDidTrigger = false;
    willOffset.Reset();
    didOffset.Reset();
    UpdateCurrentOffset(-ITEM_HEIGHT, SCROLL_FROM_BAR);
    EXPECT_TRUE(isWillTrigger);
    EXPECT_TRUE(isDidTrigger);
    EXPECT_EQ(willOffset.Value(), ITEM_HEIGHT);
    EXPECT_EQ(didOffset.Value(), ITEM_HEIGHT);

    isWillTrigger = false;
    isDidTrigger = false;
    willOffset.Reset();
    didOffset.Reset();
    UpdateCurrentOffset(ITEM_HEIGHT, SCROLL_FROM_ANIMATION);
    EXPECT_TRUE(isWillTrigger);
    EXPECT_TRUE(isDidTrigger);
    EXPECT_EQ(willOffset.Value(), -ITEM_HEIGHT);
    EXPECT_EQ(didOffset.Value(), -ITEM_HEIGHT);

    isWillTrigger = false;
    isDidTrigger = false;
    willOffset.Reset();
    didOffset.Reset();
    UpdateCurrentOffset(-ITEM_HEIGHT, SCROLL_FROM_ANIMATION_SPRING);
    EXPECT_TRUE(isWillTrigger);
    EXPECT_TRUE(isDidTrigger);
    EXPECT_EQ(willOffset.Value(), ITEM_HEIGHT);
    EXPECT_EQ(didOffset.Value(), ITEM_HEIGHT);

    isWillTrigger = false;
    isDidTrigger = false;
    willOffset.Reset();
    didOffset.Reset();
    UpdateCurrentOffset(ITEM_HEIGHT, SCROLL_FROM_NONE);
    EXPECT_TRUE(isWillTrigger);
    EXPECT_TRUE(isDidTrigger);
    EXPECT_EQ(willOffset.Value(), -ITEM_HEIGHT);
    EXPECT_EQ(didOffset.Value(), -ITEM_HEIGHT);
}

/**
 * @tc.name: onWillScrollAndOnDidScroll002
 * @tc.desc: Test scroll callback
 * @tc.type: FUNC
 */
HWTEST_F(ArcListScrollerEventTestNg, onWillScrollAndOnDidScroll002, TestSize.Level1)
{
    bool isWillTrigger = false;
    bool isDidTrigger = false;
    Dimension willOffset;
    Dimension didOffset;
    auto willTriggerEvent = [&isWillTrigger, &willOffset](Dimension offset, ScrollState state, ScrollSource source) {
        isWillTrigger = true;
        willOffset = offset;
        ScrollFrameResult result;
        result.offset = offset;
        return result;
    };
    auto didTriggerEvent = [&isDidTrigger, &didOffset](Dimension offset, ScrollState state) {
        isDidTrigger = true;
        didOffset = offset;
    };
    CreateList();
    CreateListItems(TOTAL_ITEM_NUMBER);
    CreateDone();
    eventHub_->SetOnWillScroll(willTriggerEvent);
    eventHub_->SetOnDidScroll(didTriggerEvent);
    /**
     * @tc.steps: Cover condition that onScroll && !NearZero(finalOffset)
     */
    isWillTrigger = false;
    isDidTrigger = false;
    willOffset.Reset();
    didOffset.Reset();
    pattern_->UpdateCurrentOffset(-ITEM_HEIGHT, SCROLL_FROM_UPDATE);
    pattern_->OnScrollEndCallback(); // set scrollStop_ to true
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(isWillTrigger);
    EXPECT_TRUE(isDidTrigger);
    EXPECT_EQ(willOffset.Value(), ITEM_HEIGHT);
    EXPECT_EQ(didOffset.Value(), 0);

    isWillTrigger = false;
    isDidTrigger = false;
    willOffset.Reset();
    didOffset.Reset();
    pattern_->UpdateCurrentOffset(ITEM_HEIGHT, SCROLL_FROM_ANIMATION);
    pattern_->OnScrollEndCallback();
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(isWillTrigger);
    EXPECT_TRUE(isDidTrigger);
    EXPECT_EQ(willOffset.Value(), -ITEM_HEIGHT);
    EXPECT_EQ(didOffset.Value(), 0);

    isWillTrigger = false;
    isDidTrigger = false;
    willOffset.Reset();
    didOffset.Reset();
    pattern_->UpdateCurrentOffset(-ITEM_HEIGHT, SCROLL_FROM_ANIMATION_SPRING);
    pattern_->OnScrollEndCallback();
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(isWillTrigger);
    EXPECT_TRUE(isDidTrigger);
    EXPECT_EQ(willOffset.Value(), ITEM_HEIGHT);
    EXPECT_EQ(didOffset.Value(), 0);

    isWillTrigger = false;
    isDidTrigger = false;
    willOffset.Reset();
    didOffset.Reset();
    pattern_->UpdateCurrentOffset(ITEM_HEIGHT, SCROLL_FROM_NONE);
    pattern_->OnScrollEndCallback();
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(isWillTrigger);
    EXPECT_TRUE(isDidTrigger);
    EXPECT_EQ(willOffset.Value(), -ITEM_HEIGHT);
    EXPECT_EQ(didOffset.Value(), -ITEM_HEIGHT);

    isWillTrigger = false;
    isDidTrigger = false;
    willOffset.Reset();
    didOffset.Reset();
    pattern_->UpdateCurrentOffset(-ITEM_HEIGHT, SCROLL_FROM_AXIS);
    pattern_->OnScrollEndCallback();
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(isWillTrigger);
    EXPECT_TRUE(isDidTrigger);
    EXPECT_EQ(willOffset.Value(), ITEM_HEIGHT);
    EXPECT_EQ(didOffset.Value(), 0);

    isWillTrigger = false;
    isDidTrigger = false;
    willOffset.Reset();
    didOffset.Reset();
    pattern_->UpdateCurrentOffset(ITEM_HEIGHT, SCROLL_FROM_BAR);
    pattern_->OnScrollEndCallback();
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(isWillTrigger);
    EXPECT_TRUE(isDidTrigger);
    EXPECT_EQ(willOffset.Value(), -ITEM_HEIGHT);
    EXPECT_EQ(didOffset.Value(), 0);

    isWillTrigger = false;
    isDidTrigger = false;
    willOffset.Reset();
    didOffset.Reset();
    pattern_->UpdateCurrentOffset(-ITEM_HEIGHT, SCROLL_FROM_ANIMATION_CONTROLLER);
    pattern_->OnScrollEndCallback();
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(isWillTrigger);
    EXPECT_TRUE(isDidTrigger);
    EXPECT_EQ(willOffset.Value(), ITEM_HEIGHT);
    EXPECT_EQ(didOffset.Value(), 0);

    isWillTrigger = false;
    isDidTrigger = false;
    willOffset.Reset();
    didOffset.Reset();
    pattern_->UpdateCurrentOffset(ITEM_HEIGHT, SCROLL_FROM_BAR_FLING);
    pattern_->OnScrollEndCallback();
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(isWillTrigger);
    EXPECT_TRUE(isDidTrigger);
    EXPECT_EQ(willOffset.Value(), -ITEM_HEIGHT);
    EXPECT_EQ(didOffset.Value(), 0);

    isWillTrigger = false;
    isDidTrigger = false;
    willOffset.Reset();
    didOffset.Reset();
    pattern_->UpdateCurrentOffset(-ITEM_HEIGHT, SCROLL_FROM_AXIS);
    pattern_->OnScrollEndCallback();
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(isWillTrigger);
    EXPECT_TRUE(isDidTrigger);
    EXPECT_EQ(willOffset.Value(), ITEM_HEIGHT);
    EXPECT_EQ(didOffset.Value(), 0);

    isWillTrigger = false;
    isDidTrigger = false;
    willOffset.Reset();
    didOffset.Reset();
    pattern_->UpdateCurrentOffset(ITEM_HEIGHT, SCROLL_FROM_BAR);
    pattern_->OnScrollEndCallback();
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(isWillTrigger);
    EXPECT_TRUE(isDidTrigger);
    EXPECT_EQ(willOffset.Value(), -ITEM_HEIGHT);
    EXPECT_EQ(didOffset.Value(), 0);

    isWillTrigger = false;
    isDidTrigger = false;
    willOffset.Reset();
    didOffset.Reset();
    pattern_->UpdateCurrentOffset(-ITEM_HEIGHT, SCROLL_FROM_ANIMATION_CONTROLLER);
    pattern_->OnScrollEndCallback();
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(isWillTrigger);
    EXPECT_TRUE(isDidTrigger);
    EXPECT_EQ(willOffset.Value(), ITEM_HEIGHT);
    EXPECT_EQ(didOffset.Value(), 0);
}

/**
 * @tc.name: Pattern005
 * @tc.desc: Test OnScrollCallback
 * @tc.type: FUNC
 */
HWTEST_F(ArcListScrollerEventTestNg, Pattern005, TestSize.Level1)
{
    ListModelNG model = CreateList();
    model.SetChainAnimation(true);
    auto startFunc = GetDefaultSwiperBuilder(START_NODE_LEN);
    CreateItemWithSwipe(startFunc, nullptr, V2::SwipeEdgeEffect::None);
    CreateListItems(TOTAL_ITEM_NUMBER);
    CreateDone();

    // Set swiperItem_ to arc_list pattern
    DragSwiperItem(0, 1.f);

    /**
     * @tc.steps: step1. When has animator_ and not stop, call OnScrollCallback.
     * @tc.expected: Would stop.
     */
    pattern_->AnimateTo(1, 0, nullptr, true);
    EXPECT_FALSE(pattern_->AnimateStoped());
    double offset = 100.0;
    pattern_->OnScrollPosition(offset, SCROLL_FROM_START);
    EXPECT_TRUE(pattern_->scrollAbort_);
    pattern_->OnScrollCallback(100.f, SCROLL_FROM_START);
    EXPECT_TRUE(pattern_->scrollAbort_);
    EXPECT_TRUE(IsEqualTotalOffset(-MID_OFFSET));
    EXPECT_TRUE(pattern_->AnimateStoped());

    /**
     * @tc.steps: step2. When has animator_ and stop, call OnScrollCallback.
     * @tc.expected:
     */
    ASSERT_NE(pattern_->GetScrollBar(), nullptr);
    pattern_->OnScrollCallback(100.f, SCROLL_FROM_UPDATE);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetTotalOffset(), -MID_OFFSET);

    /**
     * @tc.steps: step3. Offset is 0, ProcessDragUpdate do nothing.
     * @tc.expected: CurrentOffset unchange.
     */
    pattern_->OnScrollCallback(0, SCROLL_FROM_UPDATE);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetTotalOffset(), -MID_OFFSET);

    /**
     * @tc.steps: step4. When has animator_ and stop, call StopAnimate.
     * @tc.expected: Nothing.
     */
    pattern_->StopAnimate();

    pattern_->OnScrollCallback(850.f, SCROLL_FROM_START);
    EXPECT_EQ(pattern_->chainAnimation_->GetControlIndex(), 0);
    pattern_->OnScrollCallback(0.f, SCROLL_FROM_UPDATE);
    FlushLayoutTask(frameNode_);
    pattern_->OnScrollCallback(-100.f, SCROLL_FROM_UPDATE);
    FlushLayoutTask(frameNode_);
    pattern_->OnScrollCallback(100.f, SCROLL_FROM_UPDATE);
    FlushLayoutTask(frameNode_);
}
} // namespace OHOS::Ace::NG
