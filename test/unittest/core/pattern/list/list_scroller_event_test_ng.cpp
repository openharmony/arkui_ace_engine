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

#include "list_test_ng.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

namespace OHOS::Ace::NG {

namespace {} // namespace

class ListScrollerEventTestNg : public ListTestNg {
public:
};

/**
 * @tc.name: Event001
 * @tc.desc: Test scroll callback
 * @tc.type: FUNC
 */
HWTEST_F(ListScrollerEventTestNg, Event001, TestSize.Level1)
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
    UpdateCurrentOffset(-ITEM_MAIN_SIZE, SCROLL_FROM_UPDATE);
    EXPECT_TRUE(isTrigger);

    isTrigger = false;
    UpdateCurrentOffset(ITEM_MAIN_SIZE, SCROLL_FROM_AXIS);
    EXPECT_TRUE(isTrigger);

    isTrigger = false;
    UpdateCurrentOffset(-ITEM_MAIN_SIZE, SCROLL_FROM_BAR);
    EXPECT_TRUE(isTrigger);

    isTrigger = false;
    UpdateCurrentOffset(ITEM_MAIN_SIZE, SCROLL_FROM_ANIMATION);
    EXPECT_TRUE(isTrigger);

    isTrigger = false;
    UpdateCurrentOffset(-ITEM_MAIN_SIZE, SCROLL_FROM_ANIMATION_SPRING);
    EXPECT_TRUE(isTrigger);

    isTrigger = false;
    UpdateCurrentOffset(ITEM_MAIN_SIZE, SCROLL_FROM_NONE);
    EXPECT_TRUE(isTrigger);

    /**
     * @tc.steps: step2. Cover condition that onScroll && !NearZero(finalOffset)
     */
    isTrigger = false;
    pattern_->UpdateCurrentOffset(-ITEM_MAIN_SIZE, SCROLL_FROM_UPDATE);
    pattern_->OnScrollEndCallback(); // set scrollStop_ to true
    FlushUITasks();
    EXPECT_TRUE(isTrigger);

    isTrigger = false;
    pattern_->UpdateCurrentOffset(ITEM_MAIN_SIZE, SCROLL_FROM_ANIMATION);
    pattern_->OnScrollEndCallback();
    FlushUITasks();
    EXPECT_TRUE(isTrigger);

    isTrigger = false;
    pattern_->UpdateCurrentOffset(-ITEM_MAIN_SIZE, SCROLL_FROM_ANIMATION_SPRING);
    pattern_->OnScrollEndCallback();
    FlushUITasks();
    EXPECT_TRUE(isTrigger);

    isTrigger = false;
    pattern_->UpdateCurrentOffset(ITEM_MAIN_SIZE, SCROLL_FROM_NONE);
    pattern_->OnScrollEndCallback();
    FlushUITasks();
    EXPECT_TRUE(isTrigger);

    isTrigger = false;
    pattern_->UpdateCurrentOffset(-ITEM_MAIN_SIZE, SCROLL_FROM_AXIS);
    pattern_->OnScrollEndCallback();
    FlushUITasks();
    EXPECT_TRUE(isTrigger);

    isTrigger = false;
    pattern_->UpdateCurrentOffset(ITEM_MAIN_SIZE, SCROLL_FROM_BAR);
    pattern_->OnScrollEndCallback();
    FlushUITasks();
    EXPECT_TRUE(isTrigger);

    isTrigger = false;
    pattern_->UpdateCurrentOffset(-ITEM_MAIN_SIZE, SCROLL_FROM_ANIMATION_CONTROLLER);
    pattern_->OnScrollEndCallback();
    FlushUITasks();
    EXPECT_TRUE(isTrigger);

    isTrigger = false;
    pattern_->UpdateCurrentOffset(ITEM_MAIN_SIZE, SCROLL_FROM_BAR_FLING);
    pattern_->OnScrollEndCallback();
    FlushUITasks();
    EXPECT_TRUE(isTrigger);

    // SetMinPlatformVersion
    MockPipelineContext::pipeline_->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_NINE));

    isTrigger = false;
    pattern_->UpdateCurrentOffset(-ITEM_MAIN_SIZE, SCROLL_FROM_AXIS);
    pattern_->OnScrollEndCallback(); // set scrollStop_ to true
    FlushUITasks();
    EXPECT_TRUE(isTrigger);

    isTrigger = false;
    pattern_->UpdateCurrentOffset(ITEM_MAIN_SIZE, SCROLL_FROM_BAR);
    pattern_->OnScrollEndCallback();
    FlushUITasks();
    EXPECT_TRUE(isTrigger);

    isTrigger = false;
    pattern_->UpdateCurrentOffset(-ITEM_MAIN_SIZE, SCROLL_FROM_ANIMATION_CONTROLLER);
    pattern_->OnScrollEndCallback();
    FlushUITasks();
    EXPECT_TRUE(isTrigger);

    // set back
    MockPipelineContext::pipeline_->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_TEN));
}

/**
 * @tc.name: OnScrollIndex001
 * @tc.desc: Test scroll callback
 * @tc.type: FUNC
 */
HWTEST_F(ListScrollerEventTestNg, OnScrollIndex001, TestSize.Level1)
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

    ScrollTo(ITEM_MAIN_SIZE);
    EXPECT_EQ(startIndex, 1);
    EXPECT_EQ(endIndex, 4);
    EXPECT_EQ(centerIndex, 2);

    ScrollTo(ITEM_MAIN_SIZE * 2);
    EXPECT_EQ(startIndex, 2);
    EXPECT_EQ(endIndex, 5);
    EXPECT_EQ(centerIndex, 3);
}

/**
 * @tc.name: OnScrollIndex002
 * @tc.desc: Test List center snap over scroll onScrollIndex event
 * @tc.type: FUNC
 */
HWTEST_F(ListScrollerEventTestNg, OnScrollIndex002, TestSize.Level1)
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
    model.SetScrollSnapAlign(ScrollSnapAlign::CENTER);
    model.SetOnScrollIndex(event);
    CreateListItems(2);
    CreateDone();

    EXPECT_EQ(startIndex, 0);
    EXPECT_EQ(endIndex, 1);
    EXPECT_EQ(centerIndex, 0);

    pattern_->ratio_ = 0;
    DragAction(frameNode_, Offset(), 200, 0);
    EXPECT_EQ(startIndex, 0);
    EXPECT_EQ(endIndex, 1);
    EXPECT_EQ(centerIndex, 0);

    DragAction(frameNode_, Offset(), -300, 0);
    EXPECT_EQ(startIndex, 0);
    EXPECT_EQ(endIndex, 1);
    EXPECT_EQ(centerIndex, 1);

    DragAction(frameNode_, Offset(), -200, 0);
    EXPECT_EQ(startIndex, 0);
    EXPECT_EQ(endIndex, 1);
    EXPECT_EQ(centerIndex, 1);
}

/**
 * @tc.name: OnScrollIndex003
 * @tc.desc: Test List center snap over scroll onScrollIndex event
 * @tc.type: FUNC
 */
HWTEST_F(ListScrollerEventTestNg, OnScrollIndex003, TestSize.Level1)
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
    model.SetScrollSnapAlign(ScrollSnapAlign::CENTER);
    model.SetOnScrollIndex(event);
    CreateListItems(4);
    CreateDone();

    EXPECT_EQ(startIndex, 0);
    EXPECT_EQ(endIndex, 2);
    EXPECT_EQ(centerIndex, 0);

    pattern_->ratio_ = 0;
    DragAction(frameNode_, Offset(), 10, 0);
    EXPECT_EQ(startIndex, 0);
    EXPECT_EQ(endIndex, 2);
    EXPECT_EQ(centerIndex, 0);

    DragAction(frameNode_, Offset(), 10, 0);
    EXPECT_EQ(startIndex, 0);
    EXPECT_EQ(endIndex, 2);
    EXPECT_EQ(centerIndex, 0);

    DragAction(frameNode_, Offset(), 80, 0);
    EXPECT_EQ(startIndex, 0);
    EXPECT_EQ(endIndex, 2);
    EXPECT_EQ(centerIndex, 0);
}

/**
 * @tc.name: OnScrollIndex004
 * @tc.desc: Test List with content offset over scroll onScrollIndex event
 * @tc.type: FUNC
 */
HWTEST_F(ListScrollerEventTestNg, OnScrollIndex004, TestSize.Level1)
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
    model.SetContentStartOffset(50);
    model.SetContentEndOffset(50);
    model.SetOnScrollIndex(event);
    CreateListItems(5);
    CreateDone();

    EXPECT_EQ(pattern_->currentOffset_, -50);
    EXPECT_EQ(startIndex, 0);
    EXPECT_EQ(endIndex, 3);
    EXPECT_EQ(centerIndex, 1);

    pattern_->ratio_ = 0;
    DragAction(frameNode_, Offset(), 100, 0);
    EXPECT_EQ(pattern_->currentOffset_, -150);
    EXPECT_EQ(startIndex, 0);
    EXPECT_EQ(endIndex, 3);
    EXPECT_EQ(centerIndex, 1);

    pattern_->ScrollToIndex(4, false, ScrollAlign::END);
    FlushUITasks();
    EXPECT_EQ(pattern_->currentOffset_, 150);
    EXPECT_EQ(startIndex, 1);
    EXPECT_EQ(endIndex, 4);
    EXPECT_EQ(centerIndex, 3);

    DragAction(frameNode_, Offset(), -100, 0);
    EXPECT_EQ(pattern_->currentOffset_, 250);
    EXPECT_EQ(startIndex, 1);
    EXPECT_EQ(endIndex, 4);
    EXPECT_EQ(centerIndex, 3);
}

/**
 * @tc.name: Event003
 * @tc.desc: Test scroll callback
 * @tc.type: FUNC
 */
HWTEST_F(ListScrollerEventTestNg, Event003, TestSize.Level1)
{
    bool isTrigger = false;
    auto event = [&isTrigger]() { isTrigger = true; };
    ListModelNG model = CreateList();
    model.SetOnReachStart(event);
    CreateListItems(TOTAL_ITEM_NUMBER);
    CreateDone();

    /**
     * @tc.steps: step1. list first init will trigger ReachStart.
     */
    EXPECT_TRUE(isTrigger);

    /**
     * @tc.steps: step2. Scroll to middle.
     */
    isTrigger = false;
    ScrollTo(ITEM_MAIN_SIZE);
    EXPECT_FALSE(isTrigger);

    /**
     * @tc.steps: step3. Scroll up half item.
     */
    UpdateCurrentOffset(ITEM_MAIN_SIZE / 2.0f);

    /**
     * @tc.steps: step4. Scroll up to start
     */
    isTrigger = false;
    ScrollTo(0);
    EXPECT_TRUE(isTrigger);
}

/**
 * @tc.name: Event004
 * @tc.desc: Test scroll callback
 * @tc.type: FUNC
 */
HWTEST_F(ListScrollerEventTestNg, Event004, TestSize.Level1)
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
    ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM);
    EXPECT_TRUE(isTrigger);
}

/**
 * @tc.name: Event005
 * @tc.desc: Verify onScrollStart, onScrollStop callback
 * @tc.type: FUNC
 */
HWTEST_F(ListScrollerEventTestNg, Event005, TestSize.Level1)
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
    FlushUITasks();
    EXPECT_TRUE(isScrollStopCalled);

    isScrollStopCalled = false;
    pattern_->OnScrollEndCallback();
    pattern_->SetScrollAbort(true);
    FlushUITasks();
    EXPECT_FALSE(isScrollStopCalled);
}

/**
 * @tc.name: Event006
 * @tc.desc: Test other condition
 * @tc.type: FUNC
 */
HWTEST_F(ListScrollerEventTestNg, Event006, TestSize.Level1)
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
    FlushUITasks();
}

/**
 * @tc.name: Event007
 * @tc.desc: Test scroll callback
 * @tc.type: FUNC
 */
HWTEST_F(ListScrollerEventTestNg, Event007, TestSize.Level1)
{
    int32_t startIndex = -1;
    int32_t endIndex = -1;
    auto onScrollVisibleContentChange = [&startIndex, &endIndex](const ListItemIndex start, const ListItemIndex end) {
        startIndex = start.index;
        endIndex = end.index;
    };
    ListModelNG model = CreateList();
    model.SetOnScrollVisibleContentChange(onScrollVisibleContentChange);
    CreateListItems(TOTAL_ITEM_NUMBER);
    CreateDone();

    ScrollTo(ITEM_MAIN_SIZE);
    EXPECT_EQ(startIndex, 1);
    EXPECT_EQ(endIndex, 4);

    ScrollTo(ITEM_MAIN_SIZE * 2);
    EXPECT_EQ(startIndex, 2);
    EXPECT_EQ(endIndex, 5);
}

/**
 * @tc.name: Event008
 * @tc.desc: Test scroll callback
 * @tc.type: FUNC
 */
HWTEST_F(ListScrollerEventTestNg, Event008, TestSize.Level1)
{
    bool isTrigger = false;
    auto event = [&isTrigger](Dimension offset, ScrollState state) { isTrigger = true; };
    ListModelNG model = CreateList();
    model.SetOnScroll(event);
    CreateListItems(2);
    CreateDone();

    /**
     * @tc.steps: step1. Scroll down to end
     */
    ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM);
    EXPECT_FALSE(isTrigger);
}

/**
 * @tc.name: onWillScrollAndOnDidScroll001
 * @tc.desc: Test scroll callback
 * @tc.type: FUNC
 */
HWTEST_F(ListScrollerEventTestNg, onWillScrollAndOnDidScroll001, TestSize.Level1)
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
    UpdateCurrentOffset(-ITEM_MAIN_SIZE, SCROLL_FROM_UPDATE);
    EXPECT_TRUE(isWillTrigger);
    EXPECT_TRUE(isDidTrigger);
    EXPECT_EQ(willOffset.Value(), ITEM_MAIN_SIZE);
    EXPECT_EQ(didOffset.Value(), ITEM_MAIN_SIZE);

    isWillTrigger = false;
    isDidTrigger = false;
    willOffset.Reset();
    didOffset.Reset();
    UpdateCurrentOffset(ITEM_MAIN_SIZE, SCROLL_FROM_AXIS);
    EXPECT_TRUE(isWillTrigger);
    EXPECT_TRUE(isDidTrigger);
    EXPECT_EQ(willOffset.Value(), -ITEM_MAIN_SIZE);
    EXPECT_EQ(didOffset.Value(), -ITEM_MAIN_SIZE);

    isWillTrigger = false;
    isDidTrigger = false;
    willOffset.Reset();
    didOffset.Reset();
    UpdateCurrentOffset(-ITEM_MAIN_SIZE, SCROLL_FROM_BAR);
    EXPECT_TRUE(isWillTrigger);
    EXPECT_TRUE(isDidTrigger);
    EXPECT_EQ(willOffset.Value(), ITEM_MAIN_SIZE);
    EXPECT_EQ(didOffset.Value(), ITEM_MAIN_SIZE);

    isWillTrigger = false;
    isDidTrigger = false;
    willOffset.Reset();
    didOffset.Reset();
    UpdateCurrentOffset(ITEM_MAIN_SIZE, SCROLL_FROM_ANIMATION);
    EXPECT_TRUE(isWillTrigger);
    EXPECT_TRUE(isDidTrigger);
    EXPECT_EQ(willOffset.Value(), -ITEM_MAIN_SIZE);
    EXPECT_EQ(didOffset.Value(), -ITEM_MAIN_SIZE);

    isWillTrigger = false;
    isDidTrigger = false;
    willOffset.Reset();
    didOffset.Reset();
    UpdateCurrentOffset(-ITEM_MAIN_SIZE, SCROLL_FROM_ANIMATION_SPRING);
    EXPECT_TRUE(isWillTrigger);
    EXPECT_TRUE(isDidTrigger);
    EXPECT_EQ(willOffset.Value(), ITEM_MAIN_SIZE);
    EXPECT_EQ(didOffset.Value(), ITEM_MAIN_SIZE);

    isWillTrigger = false;
    isDidTrigger = false;
    willOffset.Reset();
    didOffset.Reset();
    UpdateCurrentOffset(ITEM_MAIN_SIZE, SCROLL_FROM_NONE);
    EXPECT_TRUE(isWillTrigger);
    EXPECT_TRUE(isDidTrigger);
    EXPECT_EQ(willOffset.Value(), -ITEM_MAIN_SIZE);
    EXPECT_EQ(didOffset.Value(), -ITEM_MAIN_SIZE);
}

/**
 * @tc.name: onWillScrollAndOnDidScroll002
 * @tc.desc: Test scroll callback
 * @tc.type: FUNC
 */
HWTEST_F(ListScrollerEventTestNg, onWillScrollAndOnDidScroll002, TestSize.Level1)
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
    pattern_->UpdateCurrentOffset(-ITEM_MAIN_SIZE, SCROLL_FROM_UPDATE);
    pattern_->OnScrollEndCallback(); // set scrollStop_ to true
    FlushUITasks();
    EXPECT_TRUE(isWillTrigger);
    EXPECT_TRUE(isDidTrigger);
    EXPECT_EQ(willOffset.Value(), ITEM_MAIN_SIZE);
    EXPECT_EQ(didOffset.Value(), 0);

    isWillTrigger = false;
    isDidTrigger = false;
    willOffset.Reset();
    didOffset.Reset();
    pattern_->UpdateCurrentOffset(ITEM_MAIN_SIZE, SCROLL_FROM_ANIMATION);
    pattern_->OnScrollEndCallback();
    FlushUITasks();
    EXPECT_TRUE(isWillTrigger);
    EXPECT_TRUE(isDidTrigger);
    EXPECT_EQ(willOffset.Value(), -ITEM_MAIN_SIZE);
    EXPECT_EQ(didOffset.Value(), 0);

    isWillTrigger = false;
    isDidTrigger = false;
    willOffset.Reset();
    didOffset.Reset();
    pattern_->UpdateCurrentOffset(-ITEM_MAIN_SIZE, SCROLL_FROM_ANIMATION_SPRING);
    pattern_->OnScrollEndCallback();
    FlushUITasks();
    EXPECT_TRUE(isWillTrigger);
    EXPECT_TRUE(isDidTrigger);
    EXPECT_EQ(willOffset.Value(), ITEM_MAIN_SIZE);
    EXPECT_EQ(didOffset.Value(), 0);

    isWillTrigger = false;
    isDidTrigger = false;
    willOffset.Reset();
    didOffset.Reset();
    pattern_->UpdateCurrentOffset(ITEM_MAIN_SIZE, SCROLL_FROM_NONE);
    pattern_->OnScrollEndCallback();
    FlushUITasks();
    EXPECT_TRUE(isWillTrigger);
    EXPECT_TRUE(isDidTrigger);
    EXPECT_EQ(willOffset.Value(), -ITEM_MAIN_SIZE);
    EXPECT_EQ(didOffset.Value(), -ITEM_MAIN_SIZE);

    isWillTrigger = false;
    isDidTrigger = false;
    willOffset.Reset();
    didOffset.Reset();
    pattern_->UpdateCurrentOffset(-ITEM_MAIN_SIZE, SCROLL_FROM_AXIS);
    pattern_->OnScrollEndCallback();
    FlushUITasks();
    EXPECT_TRUE(isWillTrigger);
    EXPECT_TRUE(isDidTrigger);
    EXPECT_EQ(willOffset.Value(), ITEM_MAIN_SIZE);
    EXPECT_EQ(didOffset.Value(), 0);

    isWillTrigger = false;
    isDidTrigger = false;
    willOffset.Reset();
    didOffset.Reset();
    pattern_->UpdateCurrentOffset(ITEM_MAIN_SIZE, SCROLL_FROM_BAR);
    pattern_->OnScrollEndCallback();
    FlushUITasks();
    EXPECT_TRUE(isWillTrigger);
    EXPECT_TRUE(isDidTrigger);
    EXPECT_EQ(willOffset.Value(), -ITEM_MAIN_SIZE);
    EXPECT_EQ(didOffset.Value(), 0);

    isWillTrigger = false;
    isDidTrigger = false;
    willOffset.Reset();
    didOffset.Reset();
    pattern_->UpdateCurrentOffset(-ITEM_MAIN_SIZE, SCROLL_FROM_ANIMATION_CONTROLLER);
    pattern_->OnScrollEndCallback();
    FlushUITasks();
    EXPECT_TRUE(isWillTrigger);
    EXPECT_TRUE(isDidTrigger);
    EXPECT_EQ(willOffset.Value(), ITEM_MAIN_SIZE);
    EXPECT_EQ(didOffset.Value(), 0);

    isWillTrigger = false;
    isDidTrigger = false;
    willOffset.Reset();
    didOffset.Reset();
    pattern_->UpdateCurrentOffset(ITEM_MAIN_SIZE, SCROLL_FROM_BAR_FLING);
    pattern_->OnScrollEndCallback();
    FlushUITasks();
    EXPECT_TRUE(isWillTrigger);
    EXPECT_TRUE(isDidTrigger);
    EXPECT_EQ(willOffset.Value(), -ITEM_MAIN_SIZE);
    EXPECT_EQ(didOffset.Value(), 0);

    isWillTrigger = false;
    isDidTrigger = false;
    willOffset.Reset();
    didOffset.Reset();
    pattern_->UpdateCurrentOffset(-ITEM_MAIN_SIZE, SCROLL_FROM_AXIS);
    pattern_->OnScrollEndCallback();
    FlushUITasks();
    EXPECT_TRUE(isWillTrigger);
    EXPECT_TRUE(isDidTrigger);
    EXPECT_EQ(willOffset.Value(), ITEM_MAIN_SIZE);
    EXPECT_EQ(didOffset.Value(), 0);

    isWillTrigger = false;
    isDidTrigger = false;
    willOffset.Reset();
    didOffset.Reset();
    pattern_->UpdateCurrentOffset(ITEM_MAIN_SIZE, SCROLL_FROM_BAR);
    pattern_->OnScrollEndCallback();
    FlushUITasks();
    EXPECT_TRUE(isWillTrigger);
    EXPECT_TRUE(isDidTrigger);
    EXPECT_EQ(willOffset.Value(), -ITEM_MAIN_SIZE);
    EXPECT_EQ(didOffset.Value(), 0);

    isWillTrigger = false;
    isDidTrigger = false;
    willOffset.Reset();
    didOffset.Reset();
    pattern_->UpdateCurrentOffset(-ITEM_MAIN_SIZE, SCROLL_FROM_ANIMATION_CONTROLLER);
    pattern_->OnScrollEndCallback();
    FlushUITasks();
    EXPECT_TRUE(isWillTrigger);
    EXPECT_TRUE(isDidTrigger);
    EXPECT_EQ(willOffset.Value(), ITEM_MAIN_SIZE);
    EXPECT_EQ(didOffset.Value(), 0);
}

/**
 * @tc.name: onWillScrollAndOnDidScroll003
 * @tc.desc: Test scrollToIndex trigger onDidScroll not trigger onWillScroll
 * @tc.type: FUNC
 */
HWTEST_F(ListScrollerEventTestNg, onWillScrollAndOnDidScroll003, TestSize.Level1)
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
    pattern_->ScrollToIndex(1, false, ScrollAlign::START);
    FlushUITasks();
    EXPECT_FALSE(isWillTrigger);
    EXPECT_TRUE(isDidTrigger);
    EXPECT_EQ(willOffset.Value(), 0);
    EXPECT_EQ(didOffset.Value(), ITEM_MAIN_SIZE);
}

/**
 * @tc.name: Pattern005
 * @tc.desc: Test OnScrollCallback
 * @tc.type: FUNC
 */
HWTEST_F(ListScrollerEventTestNg, Pattern005, TestSize.Level1)
{
    ListModelNG model = CreateList();
    model.SetScrollSnapAlign(ScrollSnapAlign::START);
    model.SetChainAnimation(true);
    CreateListItems(TOTAL_ITEM_NUMBER);
    CreateDone();

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
    EXPECT_EQ(pattern_->GetTotalOffset(), 0);
    EXPECT_TRUE(pattern_->AnimateStoped());

    /**
     * @tc.steps: step2. When has animator_ and stop, call OnScrollCallback.
     * @tc.expected:
     */
    ASSERT_NE(pattern_->GetScrollBar(), nullptr);
    pattern_->OnScrollCallback(100.f, SCROLL_FROM_UPDATE);
    FlushUITasks();
    EXPECT_GT(pattern_->GetTotalOffset(), -ITEM_MAIN_SIZE);

    /**
     * @tc.steps: step3. Offset is 0, ProcessDragUpdate do nothing.
     * @tc.expected: CurrentOffset unchange.
     */
    pattern_->OnScrollCallback(0, SCROLL_FROM_UPDATE);
    FlushUITasks();
    EXPECT_GT(pattern_->GetTotalOffset(), -ITEM_MAIN_SIZE);

    /**
     * @tc.steps: step4. When has animator_ and stop, call StopAnimate.
     * @tc.expected: Nothing.
     */
    pattern_->StopAnimate();

    TouchLocationInfo touch(0);
    touch.SetLocalLocation(Offset(0, 850));
    TouchEventInfo info("");
    info.AddTouchLocationInfo(std::move(touch));
    pattern_->OnTouchDown(info);
    EXPECT_EQ(pattern_->chainAnimation_->GetControlIndex(), 4);
    pattern_->OnScrollCallback(0, SCROLL_FROM_UPDATE);
    FlushUITasks();
    pattern_->OnScrollCallback(-100.f, SCROLL_FROM_UPDATE);
    FlushUITasks();
    pattern_->OnScrollCallback(100.f, SCROLL_FROM_UPDATE);
    FlushUITasks();
}

/**
 * @tc.name: OnScrollVisibleContentChange001
 * @tc.desc: Test OnScrollVisibleContentChange
 * @tc.type: FUNC
 */
HWTEST_F(ListScrollerEventTestNg, OnScrollVisibleContentChange001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create List
     * @tc.expected: Init callback OnScrollVisibleContentChange
     */
    ListItemIndex startInfo, endInfo;
    auto onVisibleChange = [&startInfo, &endInfo](ListItemIndex start, ListItemIndex end) {
        startInfo = start;
        endInfo = end;
    };
    ListModelNG model = CreateList();
    model.SetOnScrollVisibleContentChange(onVisibleChange);
    CreateListItems(20);
    CreateDone();

    EXPECT_TRUE(IsEqual(startInfo, { 0 }));
    EXPECT_TRUE(IsEqual(endInfo, { 3 }));

    /**
     * @tc.steps: step2. scroll to the end
     * @tc.expected: Init callback OnScrollVisibleContentChange
     */
    pattern_->ScrollTo(1200);
    FlushUITasks();
    EXPECT_TRUE(IsEqual(startInfo, { 12 }));
    EXPECT_TRUE(IsEqual(endInfo, { 15 }));

    /**
     * @tc.steps: step3. create List with ContentStartOffset, ContentEndOffset and Space
     * @tc.expected: endTop.index = 6
     */
    ClearOldNodes();
    model = CreateList();
    model.SetContentStartOffset(50.f);
    model.SetContentEndOffset(50.f);
    model.SetSpace(Dimension(10.f));
    model.SetOnScrollVisibleContentChange(onVisibleChange);
    CreateListItems(20);
    CreateDone();
    EXPECT_TRUE(IsEqual(startInfo, { 0 }));
    EXPECT_TRUE(IsEqual(endInfo, { 3 }));

    /**
     * @tc.steps: step4. scroll to the end
     * @tc.expected: startBottom.index = 13
     */
    pattern_->ScrollTo(1500);
    FlushUITasks();
    EXPECT_TRUE(IsEqual(startInfo, { 13 }));
    EXPECT_TRUE(IsEqual(endInfo, { 17 }));

    /**
     * @tc.steps: step5. create List with multiple Lanes
     * @tc.expected: endTop.index = 15
     */
    ClearOldNodes();
    model = CreateList();
    model.SetLanes(2);
    model.SetOnScrollVisibleContentChange(onVisibleChange);
    CreateListItems(20);
    CreateDone();
    EXPECT_TRUE(IsEqual(startInfo, { 0 }));
    EXPECT_TRUE(IsEqual(endInfo, { 7 }));

    /**
     * @tc.steps: step6. scroll to the end
     * @tc.expected: startBottom.index = 4
     */
    pattern_->ScrollTo(200);
    FlushUITasks();
    EXPECT_TRUE(IsEqual(startInfo, { 4 }));
    EXPECT_TRUE(IsEqual(endInfo, { 11 }));
}

/**
 * @tc.name: OnScrollVisibleContentChange002
 * @tc.desc: Test OnScrollVisibleContentChange
 * @tc.type: FUNC
 */
HWTEST_F(ListScrollerEventTestNg, OnScrollVisibleContentChange002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create List
     * @tc.expected: Init callback OnScrollVisibleContentChange
     */
    ListItemIndex startInfo, endInfo;
    auto onVisibleChange = [&startInfo, &endInfo](ListItemIndex start, ListItemIndex end) {
        startInfo = start;
        endInfo = end;
    };
    ListModelNG model = CreateList();
    model.SetOnScrollVisibleContentChange(onVisibleChange);
    CreateGroupWithSetting(5, V2::ListItemGroupStyle::NONE);
    CreateDone();
    ListItemIndex startExpect = { 0, 2 };
    ListItemIndex endExpect = { 1, 1, 0 };
    EXPECT_TRUE(IsEqual(startInfo, startExpect));
    EXPECT_TRUE(IsEqual(endInfo, endExpect));

    /**
     * @tc.steps: step2. scroll to 30
     * @tc.cases: indexChanged == startChanged == endChanged == false
     * @tc.expected: startExpect.index = 0
     */
    pattern_->ScrollTo(30);
    FlushUITasks();
    EXPECT_EQ(pattern_->GetTotalOffset(), 30);
    EXPECT_TRUE(IsEqual(startInfo, startExpect));
    EXPECT_TRUE(IsEqual(endInfo, endExpect));

    /**
     * @tc.steps: step3. scroll to 60
     * @tc.cases: startChanged == true and indexChanged == endChanged == false
     * @tc.expected: startExpect.indexInGroup = 0
     */
    startExpect = { 0, 1, 0 };
    pattern_->ScrollTo(60);
    FlushUITasks();
    EXPECT_EQ(pattern_->GetTotalOffset(), 60);
    EXPECT_TRUE(IsEqual(startInfo, startExpect));
    EXPECT_TRUE(IsEqual(endInfo, endExpect));

    /**
     * @tc.steps: step4. scroll to 120
     * @tc.cases: endChanged == true and indexChanged == startChanged == false
     * @tc.expected: endExpect.indexInGroup = 3
     */
    endExpect = { 1, 1, 1 };
    pattern_->ScrollTo(120);
    FlushUITasks();
    EXPECT_EQ(pattern_->GetTotalOffset(), 120);
    EXPECT_TRUE(IsEqual(startInfo, startExpect));
    EXPECT_TRUE(IsEqual(endInfo, endExpect));

    /**
     * @tc.steps: step4. scroll to 240
     * @tc.expected: endExpect.index = 1
     */
    startExpect = { 0, 1, 1 };
    endExpect = { 2, 2, -1 };
    pattern_->ScrollTo(240);
    FlushUITasks();
    EXPECT_EQ(pattern_->GetTotalOffset(), 240);
    EXPECT_TRUE(IsEqual(startInfo, startExpect));
    EXPECT_TRUE(IsEqual(endInfo, endExpect));
}
} // namespace OHOS::Ace::NG
