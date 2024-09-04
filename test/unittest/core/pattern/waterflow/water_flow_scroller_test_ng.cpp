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

#include "water_flow_test_ng.h"

namespace OHOS::Ace::NG {

namespace {} // namespace

class WaterFlowScrollerTestNg : public WaterFlowTestNg {
public:
};

/**
 * @tc.name: UpdateCurrentOffset001
 * @tc.desc: Test UpdateCurrentOffset
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowScrollerTestNg, UpdateCurrentOffset001, TestSize.Level1)
{
    Create([](WaterFlowModelNG model) {
        model.SetColumnsTemplate("1fr 1fr");
        CreateItem(TOTAL_LINE_NUMBER * 2);
    });

    /**
     * @tc.steps: step1. When itemStart_ and scroll up
     * @tc.expected: can not scroll.
     */
    UpdateCurrentOffset(ITEM_HEIGHT);
    EXPECT_TRUE(IsEqualTotalOffset(0));

    /**
     * @tc.steps: step2. Scroll down
     * @tc.expected: can scroll.
     */
    UpdateCurrentOffset(-ITEM_HEIGHT);
    EXPECT_TRUE(IsEqualTotalOffset(ITEM_HEIGHT));

    /**
     * @tc.steps: step3. Continue scroll down
     * @tc.expected: can scroll and IsAtEnd.
     */
    UpdateCurrentOffset(-WATERFLOW_HEIGHT);
    EXPECT_TRUE(IsEqualTotalOffset(WATERFLOW_HEIGHT));
    EXPECT_TRUE(pattern_->positionController_->IsAtEnd());

    /**
     * @tc.steps: step4. Continue scroll down
     * @tc.expected: can not scroll.
     */
    UpdateCurrentOffset(-ITEM_HEIGHT);
    EXPECT_TRUE(IsEqualTotalOffset(WATERFLOW_HEIGHT));

    /**
     * @tc.steps: step5. When offsetEnd_ and scroll up
     * @tc.expected: can scroll.
     */
    UpdateCurrentOffset(ITEM_HEIGHT);
    EXPECT_TRUE(IsEqualTotalOffset(WATERFLOW_HEIGHT - ITEM_HEIGHT));
}

/**
 * @tc.name: UpdateCurrentOffset002
 * @tc.desc: Test UpdateCurrentOffset
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowScrollerTestNg, UpdateCurrentOffset002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create waterFlow
     * @tc.expected: startIndex_ = 0 endIndex_ = 10.
     */
    Create([](WaterFlowModelNG model) {
        model.SetColumnsTemplate("1fr 1fr");
        model.SetEdgeEffect(EdgeEffect::SPRING, false);
        CreateItem(TOTAL_LINE_NUMBER * 2);
    });
    EXPECT_EQ(pattern_->layoutInfo_->startIndex_, 0);
    EXPECT_EQ(pattern_->layoutInfo_->endIndex_, 10);
    EXPECT_TRUE(pattern_->layoutInfo_->itemStart_);
    EXPECT_FALSE(pattern_->layoutInfo_->itemEnd_);
    EXPECT_FALSE(pattern_->layoutInfo_->offsetEnd_);

    /**
     * @tc.steps: step2. Scroll down
     * @tc.expected: startIndex_ = 1 endIndex_ = 13.
     */
    UpdateCurrentOffset(-2 * ITEM_HEIGHT);
    EXPECT_EQ(pattern_->layoutInfo_->startIndex_, 1);
    EXPECT_EQ(pattern_->layoutInfo_->endIndex_, 13);
    EXPECT_FALSE(pattern_->layoutInfo_->itemStart_);
    EXPECT_FALSE(pattern_->layoutInfo_->itemEnd_);
    EXPECT_FALSE(pattern_->layoutInfo_->offsetEnd_);

    /**
     * @tc.steps: step3. scroll down
     * @tc.expected: startIndex_ = 11 endIndex_ = 19.
     */
    UpdateCurrentOffset(-10000.f);
    EXPECT_EQ(pattern_->layoutInfo_->startIndex_, 11);
    EXPECT_EQ(pattern_->layoutInfo_->endIndex_, 19);
    EXPECT_FALSE(pattern_->layoutInfo_->itemStart_);
    EXPECT_TRUE(pattern_->layoutInfo_->itemEnd_);
    EXPECT_TRUE(pattern_->layoutInfo_->offsetEnd_);

    /**
     * @tc.steps: step4. scroll up
     * @tc.expected: startIndex_ = 7 endIndex_ = 19.
     */
    UpdateCurrentOffset(2 * ITEM_HEIGHT);
    EXPECT_EQ(pattern_->layoutInfo_->startIndex_, 7);
    EXPECT_EQ(pattern_->layoutInfo_->endIndex_, 19);
    EXPECT_FALSE(pattern_->layoutInfo_->itemStart_);
    EXPECT_TRUE(pattern_->layoutInfo_->itemEnd_);
    EXPECT_FALSE(pattern_->layoutInfo_->offsetEnd_);
}

/**
 * @tc.name: onScroll001
 * @tc.desc: Test onScroll event
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowScrollerTestNg, OnScroll001, TestSize.Level1)
{
    CalcDimension scrollOffset;
    ScrollState scrollState = ScrollState::IDLE;
    auto onScroll = [&scrollOffset, &scrollState](CalcDimension offset, ScrollState state) {
        scrollOffset = offset;
        scrollState = state;
    };
    CreateWithItem([onScroll](WaterFlowModelNG model) { model.SetOnScroll(onScroll); });

    /**
     * @tc.steps: step1. finger moves up
     * @tc.expected: Trigger onScroll with SCROLL state
     */
    UpdateCurrentOffset(-ITEM_HEIGHT);
    EXPECT_EQ(scrollOffset.Value(), ITEM_HEIGHT);
    EXPECT_EQ(scrollState, ScrollState::SCROLL);

    /**
     * @tc.steps: step2. fling
     * @tc.expected: Trigger onScroll with FLING state
     */
    UpdateCurrentOffset(-1, SCROLL_FROM_ANIMATION);
    EXPECT_EQ(scrollOffset.Value(), 1);
    EXPECT_EQ(scrollState, ScrollState::FLING);

    /**
     * @tc.steps: step3. stop
     * @tc.expected: Trigger onScroll with IDLE state
     */
    pattern_->OnAnimateStop();
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(scrollOffset.Value(), 0);
    EXPECT_EQ(scrollState, ScrollState::IDLE);
}

/**
 * @tc.name: onScroll002
 * @tc.desc: Test onScroll event
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowScrollerTestNg, OnScroll002, TestSize.Level1)
{
    CalcDimension scrollOffset;
    ScrollState scrollState = ScrollState::IDLE;
    auto onScroll = [&scrollOffset, &scrollState](CalcDimension offset, ScrollState state) {
        scrollOffset = offset;
        scrollState = state;
    };
    CreateWithItem([onScroll](WaterFlowModelNG model) { model.SetOnScroll(onScroll); });

    /**
     * @tc.steps: step1. finger moves down at top
     * @tc.expected: Trigger onScroll with SCROLL state
     */
    UpdateCurrentOffset(ITEM_HEIGHT);
    EXPECT_EQ(scrollOffset.Value(), 0);
    EXPECT_EQ(scrollState, ScrollState::IDLE);
}

/**
 * @tc.name: onScrollIndex001
 * @tc.desc: Test onScrollIndex event
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowScrollerTestNg, onScrollIndex001, TestSize.Level1)
{
    int32_t firstIndex = -1;
    int32_t lastIndex = -1;
    auto onScrollIndex = [&firstIndex, &lastIndex](int32_t first, int32_t last) {
        firstIndex = first;
        lastIndex = last;
    };
    // 10 items total, 8 items showed
    CreateWithItem([onScrollIndex](WaterFlowModelNG model) { model.SetOnScrollIndex(onScrollIndex); });

    /**
     * @tc.steps: step0. event on first layout
     * @tc.expected: Trigger onScrollIndex
     */
    EXPECT_EQ(firstIndex, 0);
    EXPECT_EQ(lastIndex, 5);

    /**
     * @tc.steps: step1. finger move up, offset less than one item height
     * @tc.expected: last item changed, trigger onScrollIndex
     */
    UpdateCurrentOffset(-ITEM_HEIGHT / 2);
    EXPECT_EQ(firstIndex, 0);
    EXPECT_EQ(lastIndex, 5);

    /**
     * @tc.steps: step2. finger move up, offset more than one item height
     * @tc.expected: first and last item changed, trigger onScrollIndex
     */
    UpdateCurrentOffset(-ITEM_HEIGHT);
    EXPECT_EQ(firstIndex, 1);
    EXPECT_EQ(lastIndex, 6);
}

/**
 * @tc.name: OnScrollStart001
 * @tc.desc: Verify onScrollStart and onScrollStop event
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowScrollerTestNg, OnScrollStart001, TestSize.Level1)
{
    bool isScrollStartCalled = false;
    bool isScrollStopCalled = false;
    auto scrollStart = [&isScrollStartCalled]() { isScrollStartCalled = true; };
    auto scrollStop = [&isScrollStopCalled]() { isScrollStopCalled = true; };
    Create([scrollStart, scrollStop](WaterFlowModelNG model) {
        model.SetOnScrollStart(scrollStart);
        model.SetOnScrollStop(scrollStop);
    });

    /**
     * @tc.steps: step1. pan start
     * @tc.expected: trigger onScrollStart
     */
    pattern_->OnScrollCallback(0, SCROLL_FROM_START);
    EXPECT_TRUE(isScrollStartCalled);

    /**
     * @tc.steps: step2. OnScrollEnd
     * @tc.expected: trigger onScrollStop
     */
    pattern_->OnScrollEndCallback();
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(isScrollStopCalled);
}

/**
 * @tc.name: WaterFlowPositionController_ScrollPage001
 * @tc.desc: Test ScrollPage.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowScrollerTestNg, WaterFlowPositionController_ScrollPage001, TestSize.Level1)
{
    Create([](WaterFlowModelNG model) {
        CreateItem(TOTAL_LINE_NUMBER * 2);
        model.SetColumnsTemplate("1fr 1fr");
    });
    auto controller = pattern_->positionController_;

    /**
     * @tc.steps: step2. test function.
     * @tc.expected: function ScrollPage is called.
     */
    pattern_->SetAxis(Axis::VERTICAL);
    controller->ScrollPage(false, false);
    EXPECT_TRUE(IsEqualTotalOffset(WATERFLOW_HEIGHT));
    EXPECT_EQ(controller->GetCurrentOffset().GetY(), WATERFLOW_HEIGHT);
    EXPECT_EQ(accessibilityProperty_->GetScrollOffSet(), pattern_->GetTotalOffset());
    EXPECT_TRUE(controller->IsAtEnd());

    pattern_->SetAxis(Axis::NONE);
    controller->ScrollPage(false, false);
    EXPECT_TRUE(IsEqualTotalOffset(WATERFLOW_HEIGHT));
    EXPECT_EQ(controller->GetCurrentOffset().GetY(), 0);
    EXPECT_TRUE(controller->IsAtEnd());
}

/**
 * @tc.name: ScrollToIndex001
 * @tc.desc: Test WaterFlow ScrollToIndex function.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowScrollerTestNg, ScrollToIndex001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Calling the ScrollToIndex interface to set values to 20 and true.
     * @tc.expected: pattern_->targetIndex_ is 20
     */
    CreateWithItem([](WaterFlowModelNG model) {});
    pattern_->ScrollToIndex(20, true);
    // Item 20 doesn't exist
    EXPECT_EQ(pattern_->targetIndex_, std::nullopt);
}

/**
 * @tc.name: ScrollToIndex002
 * @tc.desc: Test ScrollToIndex func
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowScrollerTestNg, ScrollToIndex002, TestSize.Level1)
{
    Create([](WaterFlowModelNG model) {
        model.SetColumnsTemplate("1fr 1fr");
        CreateItem(30);
    });

    pattern_->ScrollToIndex(3, false, ScrollAlign::AUTO);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->layoutInfo_->startIndex_, 0);
    EXPECT_EQ(pattern_->layoutInfo_->storedOffset_, 0);
    EXPECT_EQ(pattern_->layoutInfo_->Offset(), 0);

    pattern_->ScrollToIndex(15, false, ScrollAlign::START);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->layoutInfo_->startIndex_, 15);
    EXPECT_EQ(pattern_->layoutInfo_->storedOffset_, 0);
    EXPECT_EQ(pattern_->layoutInfo_->Offset(), -1100);

    pattern_->ScrollToIndex(LAST_ITEM);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->layoutInfo_->startIndex_, 19);
    EXPECT_EQ(pattern_->layoutInfo_->storedOffset_, -100);
    EXPECT_EQ(pattern_->layoutInfo_->Offset(), -1500);

    pattern_->ScrollToIndex(0, false, ScrollAlign::START);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->layoutInfo_->startIndex_, 0);
    EXPECT_EQ(pattern_->layoutInfo_->storedOffset_, 0);
    EXPECT_EQ(pattern_->layoutInfo_->Offset(), 0);

    pattern_->ScrollToIndex(15, false, ScrollAlign::AUTO);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->layoutInfo_->startIndex_, 7);
    EXPECT_EQ(pattern_->layoutInfo_->storedOffset_, 0);
    EXPECT_EQ(pattern_->layoutInfo_->Offset(), -500);

    pattern_->ScrollToIndex(7, false, ScrollAlign::CENTER);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->layoutInfo_->startIndex_, 3);
    EXPECT_EQ(pattern_->layoutInfo_->storedOffset_, 0);
    EXPECT_EQ(pattern_->layoutInfo_->Offset(), -200);

    pattern_->ScrollToIndex(14, false, ScrollAlign::END);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->layoutInfo_->startIndex_, 3);
    EXPECT_EQ(pattern_->layoutInfo_->storedOffset_, -100);
    EXPECT_EQ(pattern_->layoutInfo_->Offset(), -300);

    pattern_->ScrollToIndex(2, false, ScrollAlign::AUTO);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->layoutInfo_->startIndex_, 1);
    EXPECT_EQ(pattern_->layoutInfo_->storedOffset_, -100);
    EXPECT_EQ(pattern_->layoutInfo_->Offset(), -100);
}

/**
 * @tc.name: ScrollToIndex003
 * @tc.desc: Test ScrollToIndex func
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowScrollerTestNg, ScrollToIndex003, TestSize.Level1)
{
    Create([](WaterFlowModelNG model) {
        model.SetColumnsTemplate("1fr 1fr");
        CreateItem(30);
    });

    pattern_->ScrollToIndex(3, true, ScrollAlign::START);
    FlushLayoutTask(frameNode_);
    EXPECT_FLOAT_EQ(pattern_->finalPosition_, 200.f);

    pattern_->ScrollToIndex(3, true, ScrollAlign::END);
    FlushLayoutTask(frameNode_);
    EXPECT_FLOAT_EQ(pattern_->finalPosition_, -400.f);

    pattern_->ScrollToIndex(15, true, ScrollAlign::AUTO);
    FlushLayoutTask(frameNode_);
    EXPECT_FLOAT_EQ(pattern_->finalPosition_, 500.f);

    pattern_->ScrollToIndex(15, true, ScrollAlign::CENTER);
    FlushLayoutTask(frameNode_);
    EXPECT_FLOAT_EQ(pattern_->finalPosition_, 800.f);

    pattern_->ScrollToIndex(3, true, ScrollAlign::AUTO);
    FlushLayoutTask(frameNode_);
    EXPECT_FLOAT_EQ(pattern_->finalPosition_, 800.f);

    pattern_->ScrollPage(false);
    FlushLayoutTask(frameNode_);
    EXPECT_LT(pattern_->layoutInfo_->Offset(), 0.f);

    pattern_->ScrollToIndex(3, true, ScrollAlign::AUTO);
    FlushLayoutTask(frameNode_);
    EXPECT_FLOAT_EQ(pattern_->finalPosition_, 200.f);

    pattern_->ScrollToIndex(29, true);
    FlushLayoutTask(frameNode_);
    EXPECT_FLOAT_EQ(pattern_->finalPosition_, 2100.f);
}

/**
 * @tc.name: Focus001
 * @tc.desc: Test WaterFlow scroll during focus change
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowScrollerTestNg, Focus001, TestSize.Level1)
{
    Create([](WaterFlowModelNG model) {
        model.SetColumnsTemplate("1fr 1fr");
        CreateFocusableItem(30);
    });

    auto next = pattern_->GetNextFocusNode(FocusStep::DOWN, GetChildFocusHub(frameNode_, 5)).Upgrade();
    auto cmp = GetChildFocusHub(frameNode_, 6);
    EXPECT_EQ(AceType::RawPtr(next), AceType::RawPtr(cmp));

    cmp = GetChildFocusHub(frameNode_, 4);
    next = pattern_->GetNextFocusNode(FocusStep::UP, GetChildFocusHub(frameNode_, 5)).Upgrade();
    EXPECT_EQ(AceType::RawPtr(next), AceType::RawPtr(cmp));
    auto info = pattern_->layoutInfo_;

    EXPECT_EQ(info->startIndex_, 0);
    EXPECT_EQ(info->endIndex_, 10);

    next = pattern_->GetNextFocusNode(FocusStep::LEFT, GetChildFocusHub(frameNode_, 0)).Upgrade();
    EXPECT_FALSE(next);

    EXPECT_EQ(info->startIndex_, 0);
    EXPECT_EQ(info->endIndex_, 10);
    next = pattern_->GetNextFocusNode(FocusStep::RIGHT, GetChildFocusHub(frameNode_, 10)).Upgrade();
    EXPECT_EQ(GetChildRect(frameNode_, 11).Bottom(), WATERFLOW_HEIGHT);
    cmp = GetChildFocusHub(frameNode_, 11);
    EXPECT_EQ(AceType::RawPtr(next), AceType::RawPtr(cmp));

    pattern_->ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, false);
    FlushLayoutTask(frameNode_);
    next = pattern_->GetNextFocusNode(FocusStep::LEFT, GetChildFocusHub(frameNode_, 29)).Upgrade();
    cmp = GetChildFocusHub(frameNode_, 28);
    EXPECT_EQ(AceType::RawPtr(next), AceType::RawPtr(cmp));
    next = pattern_->GetNextFocusNode(FocusStep::DOWN_END, GetChildFocusHub(frameNode_, 29)).Upgrade();
    EXPECT_FALSE(next);

    EXPECT_EQ(info->startIndex_, 19);
    next = pattern_->GetNextFocusNode(FocusStep::UP_END, GetChildFocusHub(frameNode_, info->startIndex_)).Upgrade();
    cmp = GetChildFocusHub(frameNode_, 18);
    EXPECT_EQ(AceType::RawPtr(next), AceType::RawPtr(cmp));
    EXPECT_EQ(GetChildY(frameNode_, 18), 0.0f);
}

/**
 * @tc.name: Focus002
 * @tc.desc: Test GetScrollIndexAbility
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowScrollerTestNg, Focus002, TestSize.Level1)
{
    Create([](WaterFlowModelNG model) {
        model.SetColumnsTemplate("1fr 1fr");
        CreateFocusableItem(30);
    });
    auto eventHub = frameNode_->GetEventHub<EventHub>();
    auto focusHub = eventHub->GetOrCreateFocusHub();
    focusHub->SetFocusDependence(FocusDependence::AUTO);

    /**
     * @tc.steps: step1. ScrollToEdge SCROLL_BOTTOM false
     * @tc.expected: scroll to bottom
     */
    focusHub->FocusToHeadOrTailChild(false);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetBeginIndex(), 19);
    EXPECT_EQ(pattern_->GetEndIndex(), 29);
    EXPECT_EQ(pattern_->layoutInfo_->itemStart_, false);
    EXPECT_EQ(pattern_->layoutInfo_->itemEnd_, true);
    EXPECT_EQ(pattern_->layoutInfo_->offsetEnd_, true);
    EXPECT_EQ(pattern_->layoutInfo_->storedOffset_, -100);

    /**
     * @tc.steps: step1. ScrollToEdge SCROLL_TOP false
     * @tc.expected: scroll to top
     */
    focusHub->FocusToHeadOrTailChild(true);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetBeginIndex(), 0);
    EXPECT_EQ(pattern_->GetEndIndex(), 10);
    EXPECT_EQ(pattern_->layoutInfo_->itemStart_, true);
    EXPECT_EQ(pattern_->layoutInfo_->itemEnd_, false);
    EXPECT_EQ(pattern_->layoutInfo_->offsetEnd_, false);
    EXPECT_EQ(pattern_->layoutInfo_->storedOffset_, 0);

    /**
     * @tc.steps: step1. ScrollToIndex 29 false ScrollAlign::AUTO
     * @tc.expected: scroll to bottom
     */
    auto scrollIndexAbility = pattern_->GetScrollIndexAbility();
    EXPECT_TRUE(scrollIndexAbility(29));
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetBeginIndex(), 19);
    EXPECT_EQ(pattern_->GetEndIndex(), 29);
    EXPECT_EQ(pattern_->layoutInfo_->itemStart_, false);
    EXPECT_EQ(pattern_->layoutInfo_->itemEnd_, true);
    EXPECT_EQ(pattern_->layoutInfo_->offsetEnd_, true);
    EXPECT_EQ(pattern_->layoutInfo_->storedOffset_, -100);

    /**
     * @tc.steps: step1. ScrollToIndex 0 false ScrollAlign::AUTO
     * @tc.expected: scroll to top
     */
    EXPECT_TRUE(scrollIndexAbility(0));
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetBeginIndex(), 0);
    EXPECT_EQ(pattern_->GetEndIndex(), 10);
    EXPECT_EQ(pattern_->layoutInfo_->itemStart_, true);
    EXPECT_EQ(pattern_->layoutInfo_->itemEnd_, false);
    EXPECT_EQ(pattern_->layoutInfo_->offsetEnd_, false);
    EXPECT_EQ(pattern_->layoutInfo_->storedOffset_, 0);
}
} // namespace OHOS::Ace::NG
