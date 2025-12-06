/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "grid_test_ng.h"

#include "test/mock/core/animation/mock_animation_manager.h"

namespace OHOS::Ace::NG {

namespace {} // namespace

class GridScrollerEventTestTwoNg : public GridTestNg {
public:
    GridModelNG CreateWithNoProxy();
};

GridModelNG GridScrollerEventTestTwoNg::CreateWithNoProxy()
{
    GridModelNG model;
    RefPtr<ScrollControllerBase> positionController = model.CreatePositionController();
    model.Create(positionController, nullptr);
    ViewAbstract::SetWidth(CalcLength(WIDTH));
    ViewAbstract::SetHeight(CalcLength(HEIGHT));
    GetGrid();
    return model;
}

/**
 * @tc.name: VerticalGridWithScrollBarWithAnimation001
 * @tc.desc: Test Grid(Axis::VERTICAL) Scroll With Scroll Bar With Animation
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollerEventTestTwoNg, VerticalGridWithScrollBarWithAnimation001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set five kinds of scroll events: onScroll, onScrollStart,
     *                   onScrollStop, onReachStart, onReachEnd
     */
    bool isOnScrollCallBack = false;
    bool isOnScrollStartCallBack = false;
    bool isOnScrollStopCallBack = false;
    bool isOnReachStartCallBack = false;
    bool isOnReachEndCallBack = false;

    Dimension offsetY;
    ScrollState scrollState;
    auto onScroll = [&offsetY, &scrollState, &isOnScrollCallBack](Dimension offset, ScrollState state) {
        offsetY = offset;
        scrollState = state;
        isOnScrollCallBack = true;
    };
    auto onScrollStart = [&isOnScrollStartCallBack]() { isOnScrollStartCallBack = true; };
    auto onScrollStop = [&isOnScrollStopCallBack]() { isOnScrollStopCallBack = true; };
    auto onReachStart = [&isOnReachStartCallBack]() { isOnReachStartCallBack = true; };
    auto onReachEnd = [&isOnReachEndCallBack]() { isOnReachEndCallBack = true; };

    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetOnScroll(onScroll);
    model.SetOnScrollStart(onScrollStart);
    model.SetOnScrollStop(onScrollStop);
    model.SetOnReachStart(onReachStart);
    model.SetOnReachEnd(onReachEnd);
    model.SetSupportAnimation(true);
    CreateFixedItems(20);
    CreateDone();
    EXPECT_TRUE(isOnReachStartCallBack);
    isOnReachStartCallBack = false;

    /**
     * @tc.steps: step2. Scroll to grid's center with animation, and check the
     *                   five kinds of call back functions are triggered or not.
     * @tc.expected: OnScroll OnScrollStart and onScrollStop call back functions should be triggered
     */
    auto controller = pattern_->positionController_;
    controller->AnimateTo(Dimension(-5 * ITEM_MAIN_SIZE, DimensionUnit::PX), 1.f, Curves::LINEAR, false);
    pattern_->StopAnimate();
    pattern_->SetScrollAbort(false);
    pattern_->OnScrollEndCallback();
    pattern_->UpdateCurrentOffset(-5 * ITEM_MAIN_SIZE, SCROLL_FROM_ANIMATION_CONTROLLER);

    FlushUITasks();
    EXPECT_TRUE(isOnScrollCallBack);
    EXPECT_TRUE(isOnScrollStartCallBack);
    EXPECT_TRUE(isOnScrollStopCallBack);
    EXPECT_FALSE(isOnReachStartCallBack);
    EXPECT_FALSE(isOnReachEndCallBack);
}

/**
 * @tc.name: VerticalGridWithScrollBarWithAnimation002
 * @tc.desc: Test Grid(Axis::VERTICAL) Scroll With Scroll Bar With Animation
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollerEventTestTwoNg, VerticalGridWithScrollBarWithAnimation002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set five kinds of scroll events: onScroll, onScrollStart,
     *                   onScrollStop, onReachStart, onReachEnd
     */
    bool isOnScrollCallBack = false;
    bool isOnScrollStartCallBack = false;
    bool isOnScrollStopCallBack = false;
    bool isOnReachStartCallBack = false;
    bool isOnReachEndCallBack = false;

    Dimension offsetY;
    ScrollState scrollState;
    auto onScroll = [&offsetY, &scrollState, &isOnScrollCallBack](Dimension offset, ScrollState state) {
        offsetY = offset;
        scrollState = state;
        isOnScrollCallBack = true;
    };
    auto onScrollStart = [&isOnScrollStartCallBack]() { isOnScrollStartCallBack = true; };
    auto onScrollStop = [&isOnScrollStopCallBack]() { isOnScrollStopCallBack = true; };
    auto onReachStart = [&isOnReachStartCallBack]() { isOnReachStartCallBack = true; };
    auto onReachEnd = [&isOnReachEndCallBack]() { isOnReachEndCallBack = true; };

    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetOnScroll(onScroll);
    model.SetOnScrollStart(onScrollStart);
    model.SetOnScrollStop(onScrollStop);
    model.SetOnReachStart(onReachStart);
    model.SetOnReachEnd(onReachEnd);
    model.SetSupportAnimation(true);
    CreateFixedItems(20);
    CreateDone();
    EXPECT_TRUE(isOnReachStartCallBack);
    isOnReachStartCallBack = false;

    /**
     * @tc.steps: step2. Scroll to grid's end without animation, and check the
     *                   five kinds of call back functions is triggered or not.
     * @tc.expected:All call back functions except onReachStart should be triggered
     */
    auto controller = pattern_->positionController_;
    controller->AnimateTo(Dimension(-10 * ITEM_MAIN_SIZE, DimensionUnit::PX), 1.f, Curves::LINEAR, false);
    pattern_->StopAnimate();
    pattern_->SetScrollAbort(false);
    pattern_->OnScrollEndCallback();
    pattern_->UpdateCurrentOffset(-10 * ITEM_MAIN_SIZE, SCROLL_FROM_ANIMATION_CONTROLLER);

    FlushUITasks();
    EXPECT_TRUE(isOnScrollCallBack);
    EXPECT_TRUE(isOnScrollStartCallBack);
    EXPECT_TRUE(isOnScrollStopCallBack);
    EXPECT_FALSE(isOnReachStartCallBack);
    EXPECT_TRUE(isOnReachEndCallBack);
}

/**
 * @tc.name: HorizontalGridWithScrollBarWithoutAnimation001
 * @tc.desc: Test Grid(Axis::HORIZONTAL) Scroll With Scroll Bar Without Animation
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollerEventTestTwoNg, HorizontalGridWithScrollBarWithoutAnimation001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set five kinds of scroll events: onScroll, onScrollStart,
     *                   onScrollStop, onReachStart, onReachEnd
     * @tc.expected: creat grid
     */
    bool isOnScrollCallBack = false;
    bool isOnScrollStartCallBack = false;
    bool isOnScrollStopCallBack = false;
    bool isOnReachStartCallBack = false;
    bool isOnReachEndCallBack = false;

    Dimension offsetY;
    ScrollState scrollState;
    auto onScroll = [&offsetY, &scrollState, &isOnScrollCallBack](Dimension offset, ScrollState state) {
        offsetY = offset;
        scrollState = state;
        isOnScrollCallBack = true;
    };
    auto onScrollStart = [&isOnScrollStartCallBack]() { isOnScrollStartCallBack = true; };
    auto onScrollStop = [&isOnScrollStopCallBack]() { isOnScrollStopCallBack = true; };
    auto onReachStart = [&isOnReachStartCallBack]() { isOnReachStartCallBack = true; };
    auto onReachEnd = [&isOnReachEndCallBack]() { isOnReachEndCallBack = true; };

    GridModelNG model = CreateGrid();
    model.SetRowsTemplate("1fr 1fr");
    model.SetOnScroll(onScroll);
    model.SetOnScrollStart(onScrollStart);
    model.SetOnScrollStop(onScrollStop);
    model.SetOnReachStart(onReachStart);
    model.SetOnReachEnd(onReachEnd);
    CreateFixedItems(20);
    CreateDone();
    EXPECT_TRUE(isOnReachStartCallBack);
    isOnReachStartCallBack = false;

    /**
     * @tc.steps: step2. Scroll to grid's center position without animation, and check the
     *                   five kinds of call back functions are triggered or not.
     * @tc.expected: Only onScroll call back function should be triggered
     */
    ScrollToIndex(5, false, ScrollAlign::CENTER, std::nullopt);
    EXPECT_TRUE(isOnScrollCallBack);
    EXPECT_FALSE(isOnScrollStartCallBack);
    EXPECT_FALSE(isOnScrollStopCallBack);
    EXPECT_FALSE(isOnReachStartCallBack);
    EXPECT_FALSE(isOnReachEndCallBack);
}

/**
 * @tc.name: HorizontalGridWithScrollBarWithoutAnimation002
 * @tc.desc: Test Grid(Axis::HORIZONTAL) Scroll With Scroll Bar Without Animation
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollerEventTestTwoNg, HorizontalGridWithScrollBarWithoutAnimation002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set five kinds of scroll events: onScroll, onScrollStart,
     *                   onScrollStop, onReachStart, onReachEnd
     */
    bool isOnScrollCallBack = false;
    bool isOnScrollStartCallBack = false;
    bool isOnScrollStopCallBack = false;
    bool isOnReachStartCallBack = false;
    bool isOnReachEndCallBack = false;

    Dimension offsetY;
    ScrollState scrollState;
    auto onScroll = [&offsetY, &scrollState, &isOnScrollCallBack](Dimension offset, ScrollState state) {
        offsetY = offset;
        scrollState = state;
        isOnScrollCallBack = true;
    };
    auto onScrollStart = [&isOnScrollStartCallBack]() { isOnScrollStartCallBack = true; };
    auto onScrollStop = [&isOnScrollStopCallBack]() { isOnScrollStopCallBack = true; };
    auto onReachStart = [&isOnReachStartCallBack]() { isOnReachStartCallBack = true; };
    auto onReachEnd = [&isOnReachEndCallBack]() { isOnReachEndCallBack = true; };

    GridModelNG model = CreateGrid();
    model.SetRowsTemplate("1fr 1fr");
    model.SetOnScroll(onScroll);
    model.SetOnScrollStart(onScrollStart);
    model.SetOnScrollStop(onScrollStop);
    model.SetOnReachStart(onReachStart);
    model.SetOnReachEnd(onReachEnd);
    CreateFixedItems(20);
    CreateDone();
    EXPECT_TRUE(isOnReachStartCallBack);
    isOnReachStartCallBack = false;

    /**
     * @tc.steps: step3. Scroll to grid's end position without animation, and check the
     *                   five kinds of call back functions are triggered or not.
     * @tc.expected: Only onScroll and onReachEnd should be triggered
     */
    ScrollToIndex(19, false, ScrollAlign::END, std::nullopt);
    EXPECT_TRUE(isOnScrollCallBack);
    EXPECT_FALSE(isOnScrollStartCallBack);
    EXPECT_FALSE(isOnScrollStopCallBack);
    EXPECT_FALSE(isOnReachStartCallBack);
    EXPECT_TRUE(isOnReachEndCallBack);
}

/**
 * @tc.name: HorizontalGridWithScrollBarWithAnimation001
 * @tc.desc: Test Grid(Axis::HORIZONTAL) Scroll With Scroll Bar With Animation
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollerEventTestTwoNg, HorizontalGridWithScrollBarWithAnimation001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set five kinds of scroll events: onScroll, onScrollStart,
     *                   onScrollStop, onReachStart, onReachEnd
     */
    bool isOnScrollCallBack = false;
    bool isOnScrollStartCallBack = false;
    bool isOnScrollStopCallBack = false;
    bool isOnReachStartCallBack = false;
    bool isOnReachEndCallBack = false;

    Dimension offsetY;
    ScrollState scrollState;
    auto onScroll = [&offsetY, &scrollState, &isOnScrollCallBack](Dimension offset, ScrollState state) {
        offsetY = offset;
        scrollState = state;
        isOnScrollCallBack = true;
    };
    auto onScrollStart = [&isOnScrollStartCallBack]() { isOnScrollStartCallBack = true; };
    auto onScrollStop = [&isOnScrollStopCallBack]() { isOnScrollStopCallBack = true; };
    auto onReachStart = [&isOnReachStartCallBack]() { isOnReachStartCallBack = true; };
    auto onReachEnd = [&isOnReachEndCallBack]() { isOnReachEndCallBack = true; };

    GridModelNG model = CreateGrid();
    model.SetRowsTemplate("1fr 1fr");
    model.SetOnScroll(onScroll);
    model.SetOnScrollStart(onScrollStart);
    model.SetOnScrollStop(onScrollStop);
    model.SetOnReachStart(onReachStart);
    model.SetOnReachEnd(onReachEnd);
    model.SetSupportAnimation(true);
    CreateFixedItems(20);
    CreateDone();
    EXPECT_TRUE(isOnReachStartCallBack);
    isOnReachStartCallBack = false;

    /**
     * @tc.steps: step2. Scroll to grid's center with animation, and check the
     *                   five kinds of call back functions are triggered or not.
     * @tc.expected: OnScroll OnScrollStart and onScrollStop call back functions should be triggered
     */
    auto controller = pattern_->positionController_;
    controller->AnimateTo(Dimension(-5 * ITEM_MAIN_SIZE, DimensionUnit::PX), 1.f, Curves::LINEAR, false);
    pattern_->StopAnimate();
    pattern_->SetScrollAbort(false);
    pattern_->OnScrollEndCallback();
    pattern_->UpdateCurrentOffset(-5 * ITEM_MAIN_SIZE, SCROLL_FROM_ANIMATION_CONTROLLER);

    FlushUITasks();
    EXPECT_TRUE(isOnScrollCallBack);
    EXPECT_TRUE(isOnScrollStartCallBack);
    EXPECT_TRUE(isOnScrollStopCallBack);
    EXPECT_FALSE(isOnReachStartCallBack);
    EXPECT_FALSE(isOnReachEndCallBack);
}

/**
 * @tc.name: HorizontalGridWithScrollBarWithAnimation002
 * @tc.desc: Test Grid(Axis::HORIZONTAL) Scroll With Scroll Bar With Animation
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollerEventTestTwoNg, HorizontalGridWithScrollBarWithAnimation002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set five kinds of scroll events: onScroll, onScrollStart,
     *                   onScrollStop, onReachStart, onReachEnd
     */
    bool isOnScrollCallBack = false;
    bool isOnScrollStartCallBack = false;
    bool isOnScrollStopCallBack = false;
    bool isOnReachStartCallBack = false;
    bool isOnReachEndCallBack = false;

    Dimension offsetY;
    ScrollState scrollState;
    auto onScroll = [&offsetY, &scrollState, &isOnScrollCallBack](Dimension offset, ScrollState state) {
        offsetY = offset;
        scrollState = state;
        isOnScrollCallBack = true;
    };
    auto onScrollStart = [&isOnScrollStartCallBack]() { isOnScrollStartCallBack = true; };
    auto onScrollStop = [&isOnScrollStopCallBack]() { isOnScrollStopCallBack = true; };
    auto onReachStart = [&isOnReachStartCallBack]() { isOnReachStartCallBack = true; };
    auto onReachEnd = [&isOnReachEndCallBack]() { isOnReachEndCallBack = true; };

    GridModelNG model = CreateGrid();
    model.SetRowsTemplate("1fr 1fr");
    model.SetOnScroll(onScroll);
    model.SetOnScrollStart(onScrollStart);
    model.SetOnScrollStop(onScrollStop);
    model.SetOnReachStart(onReachStart);
    model.SetOnReachEnd(onReachEnd);
    model.SetSupportAnimation(true);
    CreateFixedItems(20);
    CreateDone();
    EXPECT_TRUE(isOnReachStartCallBack);
    isOnReachStartCallBack = false;

    /**
     * @tc.steps: step2. Scroll to grid's end without animation, and check the
     *                   five kinds of call back functions is triggered or not.
     * @tc.expected:All call back functions except onReachStart should be triggered
     */
    auto controller = pattern_->positionController_;
    controller->AnimateTo(Dimension(-10 * ITEM_MAIN_SIZE, DimensionUnit::PX), 1.f, Curves::LINEAR, false);
    pattern_->StopAnimate();
    pattern_->SetScrollAbort(false);
    pattern_->OnScrollEndCallback();
    pattern_->UpdateCurrentOffset(-10 * ITEM_MAIN_SIZE, SCROLL_FROM_ANIMATION_CONTROLLER);

    FlushUITasks();
    EXPECT_TRUE(isOnScrollCallBack);
    EXPECT_TRUE(isOnScrollStartCallBack);
    EXPECT_TRUE(isOnScrollStopCallBack);
    EXPECT_FALSE(isOnReachStartCallBack);
    EXPECT_TRUE(isOnReachEndCallBack);
}

/**
 * @tc.name: onWillScrollAndOnDidScroll001
 * @tc.desc: Test Grid(Axis::Vertical) Scroll, onWillScroll and onDidScroll
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollerEventTestTwoNg, onWillScrollAndOnDidScroll001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set three kinds of scroll events: onScroll, onWillScroll, onDidScroll
     * @tc.expected: creat grid
     */
    bool isOnScrollCallBack = false;
    bool isOnWillScrollCallBack = false;
    bool isOnDidScrollCallBack = false;

    Dimension offsetY;
    ScrollState scrollState;
    auto onScroll = [&offsetY, &scrollState, &isOnScrollCallBack](Dimension offset, ScrollState state) {
        offsetY = offset;
        scrollState = state;
        isOnScrollCallBack = true;
    };
    Dimension willScrollOffset;
    ScrollState willScrollState;
    auto onWillScroll = [&willScrollOffset, &willScrollState, &isOnWillScrollCallBack](
                            Dimension offset, ScrollState state, ScrollSource source) {
        willScrollOffset = offset * 2;
        willScrollState = state;
        isOnWillScrollCallBack = true;
        ScrollFrameResult result;
        result.offset = offset;
        return result;
    };
    Dimension didScrollOffset;
    ScrollState didScrollState;
    auto onDidScroll = [&didScrollOffset, &didScrollState, &isOnDidScrollCallBack](
                           Dimension offset, ScrollState state) {
        didScrollOffset = offset * 3;
        didScrollState = state;
        isOnDidScrollCallBack = true;
    };

    GridModelNG model = CreateWithNoProxy();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetOnScroll(onScroll);
    CreateFixedItems(20);
    CreateDone();
    eventHub_->SetOnWillScroll(onWillScroll);
    eventHub_->SetOnDidScroll(onDidScroll);

    /**
     * @tc.steps: step2. Scroll to grid's end position without animation, and check the
     *                   three kinds of call back functions are triggered or not.
     * @tc.expected: All functions should be triggered
     */
    ScrollTo(ITEM_MAIN_SIZE * 5);
    EXPECT_TRUE(isOnScrollCallBack);
    EXPECT_EQ(offsetY.Value(), ITEM_MAIN_SIZE * 5);
    EXPECT_EQ(willScrollOffset.Value(), ITEM_MAIN_SIZE * 5 * 2);
    EXPECT_EQ(didScrollOffset.Value(), ITEM_MAIN_SIZE * 5 * 3);
    EXPECT_EQ(scrollState, willScrollState);
    EXPECT_EQ(scrollState, didScrollState);
}

/**
 * @tc.name: onWillScrollAndOnDidScroll002
 * @tc.desc: Test Grid(Axis::HORIZONTAL) Scroll, onWillScroll and onDidScroll
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollerEventTestTwoNg, onWillScrollAndOnDidScroll002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set three kinds of scroll events: onScroll, onWillScroll, onDidScroll
     * @tc.expected: creat grid
     */
    bool isOnScrollCallBack = false;
    bool isOnWillScrollCallBack = false;
    bool isOnDidScrollCallBack = false;

    Dimension offsetY;
    ScrollState scrollState;
    auto onScroll = [&offsetY, &scrollState, &isOnScrollCallBack](Dimension offset, ScrollState state) {
        offsetY = offset;
        scrollState = state;
        isOnScrollCallBack = true;
    };
    Dimension willScrollOffset;
    ScrollState willScrollState;
    auto onWillScroll = [&willScrollOffset, &willScrollState, &isOnWillScrollCallBack](
                            Dimension offset, ScrollState state, ScrollSource source) {
        willScrollOffset = offset * 2;
        willScrollState = state;
        isOnWillScrollCallBack = true;
        ScrollFrameResult result;
        result.offset = offset;
        return result;
    };
    Dimension didScrollOffset;
    ScrollState didScrollState;
    auto onDidScroll = [&didScrollOffset, &didScrollState, &isOnDidScrollCallBack](
                           Dimension offset, ScrollState state) {
        didScrollOffset = offset * 3;
        didScrollState = state;
        isOnDidScrollCallBack = true;
    };

    GridModelNG model = CreateWithNoProxy();
    model.SetRowsTemplate("1fr 1fr");
    model.SetOnScroll(onScroll);
    CreateFixedItems(20);
    CreateDone();
    eventHub_->SetOnWillScroll(onWillScroll);
    eventHub_->SetOnDidScroll(onDidScroll);

    /**
     * @tc.steps: step2. Scroll to grid's end position without animation, and check the
     *                   three kinds of call back functions are triggered or not.
     * @tc.expected: All functions should be triggered
     */
    ScrollTo(ITEM_MAIN_SIZE * 5);
    EXPECT_TRUE(isOnScrollCallBack);
    EXPECT_TRUE(isOnWillScrollCallBack);
    EXPECT_TRUE(isOnDidScrollCallBack);
    EXPECT_EQ(offsetY.Value(), ITEM_MAIN_SIZE * 5);
    EXPECT_EQ(willScrollOffset.Value(), ITEM_MAIN_SIZE * 5 * 2);
    EXPECT_EQ(didScrollOffset.Value(), ITEM_MAIN_SIZE * 5 * 3);
    EXPECT_EQ(scrollState, willScrollState);
    EXPECT_EQ(scrollState, didScrollState);
}

/**
 * @tc.name: onWillScrollAndOnDidScroll003
 * @tc.desc: Test Grid(Axis::HORIZONTAL) Scroll Without Scroll Bar Without Animation
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollerEventTestTwoNg, onWillScrollAndOnDidScroll003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set three kinds of scroll events: onScroll, onWillScroll, onDidScroll
     * @tc.expected: creat grid
     */
    bool isOnScrollCallBack = false;
    bool isOnWillScrollCallBack = false;
    bool isOnDidScrollCallBack = false;

    Dimension offsetY;
    ScrollState scrollState;
    auto onScroll = [&offsetY, &scrollState, &isOnScrollCallBack](Dimension offset, ScrollState state) {
        offsetY = offset;
        scrollState = state;
        isOnScrollCallBack = true;
    };
    Dimension willScrollOffset;
    ScrollState willScrollState;
    auto onWillScroll = [&willScrollOffset, &willScrollState, &isOnWillScrollCallBack](
                            Dimension offset, ScrollState state, ScrollSource source) {
        willScrollOffset = offset * 2;
        willScrollState = state;
        isOnWillScrollCallBack = true;
        ScrollFrameResult result;
        result.offset = offset;
        return result;
    };
    Dimension didScrollOffset;
    ScrollState didScrollState;
    auto onDidScroll = [&didScrollOffset, &didScrollState, &isOnDidScrollCallBack](
                           Dimension offset, ScrollState state) {
        didScrollOffset = offset * 3;
        didScrollState = state;
        isOnDidScrollCallBack = true;
    };

    GridModelNG model = CreateWithNoProxy();
    model.SetRowsTemplate("1fr 1fr");
    model.SetOnScroll(onScroll);
    CreateFixedItems(20);
    CreateDone();
    eventHub_->SetOnWillScroll(onWillScroll);
    eventHub_->SetOnDidScroll(onDidScroll);

    /**
     * @tc.steps: step2. Scroll to a large offset beyond the total height of the grid without animation, and check
     *                   three kinds of call back functions are triggered and values are correct.
     * @tc.expected: All functions should be triggered
     */
    pattern_->ScrollBy(ITEM_MAIN_SIZE);
    FlushUITasks();
    EXPECT_TRUE(isOnScrollCallBack);
    EXPECT_TRUE(isOnWillScrollCallBack);
    EXPECT_TRUE(isOnDidScrollCallBack);
    EXPECT_EQ(offsetY.Value(), ITEM_MAIN_SIZE);
    EXPECT_EQ(willScrollOffset.Value(), ITEM_MAIN_SIZE * 2);
    EXPECT_EQ(didScrollOffset.Value(), ITEM_MAIN_SIZE * 3);
    EXPECT_EQ(scrollState, willScrollState);
    EXPECT_EQ(scrollState, didScrollState);
}

/**
 * @tc.name: onWillScrollAndOnDidScroll004
 * @tc.desc: Test Grid(Axis::Vertical) Scroll, onWillScroll and onDidScroll
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollerEventTestTwoNg, onWillScrollAndOnDidScroll004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set three kinds of scroll events: onScroll, onWillScroll, onDidScroll
     * @tc.expected: creat grid
     */
    bool isOnScrollCallBack = false;
    bool isOnWillScrollCallBack = false;
    bool isOnDidScrollCallBack = false;

    Dimension offsetY;
    ScrollState scrollState;
    auto onScroll = [&offsetY, &scrollState, &isOnScrollCallBack](Dimension offset, ScrollState state) {
        offsetY = offset;
        scrollState = state;
        isOnScrollCallBack = true;
    };
    Dimension willScrollOffset;
    ScrollState willScrollState;
    auto onWillScroll = [&willScrollOffset, &willScrollState, &isOnWillScrollCallBack](
                            Dimension offset, ScrollState state, ScrollSource source) {
        willScrollOffset = offset;
        willScrollState = state;
        isOnWillScrollCallBack = true;
        ScrollFrameResult result;
        result.offset = offset;
        return result;
    };
    Dimension didScrollOffset;
    ScrollState didScrollState;
    auto onDidScroll = [&didScrollOffset, &didScrollState, &isOnDidScrollCallBack](
                           Dimension offset, ScrollState state) {
        didScrollOffset = offset;
        didScrollState = state;
        isOnDidScrollCallBack = true;
    };

    GridModelNG model = CreateWithNoProxy();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetOnScroll(onScroll);
    CreateFixedItems(20);
    CreateDone();
    eventHub_->SetOnWillScroll(onWillScroll);
    eventHub_->SetOnDidScroll(onDidScroll);

    /**
     * @tc.steps: step2. Scroll to a large offset beyond the total height of the grid without animation, and check
     *                   three kinds of call back functions are triggered and values are correct.
     * @tc.expected: All functions should be triggered
     */
    ScrollTo(ITEM_MAIN_SIZE * 10);
    EXPECT_TRUE(isOnScrollCallBack);
    EXPECT_TRUE(isOnWillScrollCallBack);
    EXPECT_TRUE(isOnDidScrollCallBack);
    EXPECT_EQ(offsetY.Value(), ITEM_MAIN_SIZE * 6);
    EXPECT_EQ(willScrollOffset.Value(), ITEM_MAIN_SIZE * 10);
    EXPECT_EQ(didScrollOffset.Value(), ITEM_MAIN_SIZE * 6);
    EXPECT_EQ(scrollState, willScrollState);
    EXPECT_EQ(scrollState, didScrollState);
}

/**
 * @tc.name: onWillScrollAndOnDidScroll005
 * @tc.desc: Test Grid(Axis::Vertical) Scroll, onWillScroll and onDidScroll
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollerEventTestTwoNg, onWillScrollAndOnDidScroll005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set three kinds of scroll events: onScroll, onWillScroll, onDidScroll
     * @tc.expected: creat grid
     */
    bool isOnScrollCallBack = false;
    bool isOnWillScrollCallBack = false;
    bool isOnDidScrollCallBack = false;

    Dimension offsetY;
    ScrollState scrollState;
    auto onScroll = [&offsetY, &scrollState, &isOnScrollCallBack](Dimension offset, ScrollState state) {
        offsetY = offset;
        scrollState = state;
        isOnScrollCallBack = true;
    };
    Dimension willScrollOffset;
    ScrollState willScrollState;
    auto onWillScroll = [&willScrollOffset, &willScrollState, &isOnWillScrollCallBack](
                            Dimension offset, ScrollState state, ScrollSource source) {
        willScrollOffset = offset;
        willScrollState = state;
        isOnWillScrollCallBack = true;
        ScrollFrameResult result;
        result.offset = offset;
        return result;
    };
    Dimension didScrollOffset;
    ScrollState didScrollState;
    auto onDidScroll = [&didScrollOffset, &didScrollState, &isOnDidScrollCallBack](
                           Dimension offset, ScrollState state) {
        didScrollOffset = offset;
        didScrollState = state;
        isOnDidScrollCallBack = true;
    };

    GridModelNG model = CreateWithNoProxy();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetOnScroll(onScroll);
    CreateFixedItems(20);
    CreateDone();
    eventHub_->SetOnWillScroll(onWillScroll);
    eventHub_->SetOnDidScroll(onDidScroll);

    /**
     * @tc.steps: step2. Scroll to a negative position without animation, and check
     *                   three kinds of call back functions are triggered and values are correct.
     * @tc.expected: All functions should be triggered
     */
    ScrollTo(-ITEM_MAIN_SIZE);
    EXPECT_FALSE(isOnScrollCallBack);
    EXPECT_FALSE(isOnWillScrollCallBack);
    EXPECT_FALSE(isOnDidScrollCallBack);
    EXPECT_EQ(offsetY.Value(), 0);
    EXPECT_EQ(willScrollOffset.Value(), 0);
    EXPECT_EQ(didScrollOffset.Value(), 0);
    EXPECT_EQ(scrollState, willScrollState);
    EXPECT_EQ(scrollState, didScrollState);
}

/**
 * @tc.name: onWillScrollAndOnDidScroll006
 * @tc.desc: Test Grid(Axis::Vertical) Scroll, onWillScroll and onDidScroll
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollerEventTestTwoNg, onWillScrollAndOnDidScroll006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set three kinds of scroll events: onScroll, onWillScroll, onDidScroll
     * @tc.expected: creat grid
     */
    bool isOnScrollCallBack = false;
    bool isOnWillScrollCallBack = false;
    bool isOnDidScrollCallBack = false;

    Dimension offsetY;
    ScrollState scrollState;
    auto onScroll = [&offsetY, &scrollState, &isOnScrollCallBack](Dimension offset, ScrollState state) {
        offsetY = offset;
        scrollState = state;
        isOnScrollCallBack = true;
    };
    Dimension willScrollOffset;
    ScrollState willScrollState;
    auto onWillScroll = [&willScrollOffset, &willScrollState, &isOnWillScrollCallBack](
                            Dimension offset, ScrollState state, ScrollSource source) {
        willScrollOffset = offset;
        willScrollState = state;
        isOnWillScrollCallBack = true;
        ScrollFrameResult result;
        result.offset = offset;
        return result;
    };
    Dimension didScrollOffset;
    ScrollState didScrollState;
    auto onDidScroll = [&didScrollOffset, &didScrollState, &isOnDidScrollCallBack](
                           Dimension offset, ScrollState state) {
        didScrollOffset = offset;
        didScrollState = state;
        isOnDidScrollCallBack = true;
    };

    GridModelNG model = CreateWithNoProxy();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetOnScroll(onScroll);
    model.SetEdgeEffect(EdgeEffect::SPRING, true);
    CreateFixedItems(20);
    CreateDone();
    eventHub_->SetOnWillScroll(onWillScroll);
    eventHub_->SetOnDidScroll(onDidScroll);

    /**
     * @tc.steps: step2. Scroll to a negative position without animation, and check
     *                   three kinds of call back functions are triggered and values are correct.
     * @tc.expected: All functions should be triggered
     */
    pattern_->OnScrollCallback(ITEM_MAIN_SIZE, SCROLL_FROM_UPDATE);
    FlushUITasks();
    EXPECT_FALSE(isOnScrollCallBack);
    EXPECT_TRUE(isOnWillScrollCallBack);
    EXPECT_FALSE(isOnDidScrollCallBack);
    EXPECT_EQ(offsetY.Value(), 0);
    EXPECT_EQ(willScrollOffset.Value(), -ITEM_MAIN_SIZE);
    EXPECT_EQ(didScrollOffset.Value(), 0);
    EXPECT_EQ(willScrollState, ScrollState::SCROLL);
    EXPECT_EQ(scrollState, didScrollState);
}

/**
 * @tc.name: HandleOnWillStopDragging001
 * @tc.desc: Test HandleOnWillStopDragging001
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollerEventTestTwoNg, HandleOnWillStopDragging001, TestSize.Level1)
{
    bool isOnWillStopDraggingCallBack = false;
    Dimension willStopDraggingVelocity;
    auto onWillStopDragging = [&willStopDraggingVelocity, &isOnWillStopDraggingCallBack](
                           Dimension velocity) {
        willStopDraggingVelocity = velocity;
        isOnWillStopDraggingCallBack = true;
    };

    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetEdgeEffect(EdgeEffect::SPRING, false);
    CreateFixedItems(20);
    CreateDone();
    eventHub_->SetOnWillStopDragging(onWillStopDragging);

    GestureEvent info;
    info.SetMainVelocity(-1200.f);
    info.SetMainDelta(-200.f);
    auto scrollable = pattern_->GetScrollableEvent()->GetScrollable();
    scrollable->HandleTouchDown();
    scrollable->HandleDragStart(info);
    scrollable->HandleDragUpdate(info);
    FlushUITasks();

    scrollable->HandleTouchUp();
    scrollable->HandleDragEnd(info);
    FlushUITasks();

    EXPECT_TRUE(isOnWillStopDraggingCallBack);
    EXPECT_FLOAT_EQ(willStopDraggingVelocity.Value(), info.GetMainVelocity());
}

/**
 * @tc.name: HandleOnWillStopDragging002
 * @tc.desc: Test HandleOnWillStopDragging002
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollerEventTestTwoNg, HandleOnWillStopDragging002, TestSize.Level1)
{
    bool isOnWillStopDraggingCallBack = false;
    Dimension willStopDraggingVelocity;
    auto onWillStopDragging = [&willStopDraggingVelocity, &isOnWillStopDraggingCallBack](
                           Dimension velocity) {
        willStopDraggingVelocity = velocity;
        isOnWillStopDraggingCallBack = true;
    };

    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetEdgeEffect(EdgeEffect::SPRING, false);
    CreateFixedItems(20);
    CreateDone();
    eventHub_->SetOnWillStopDragging(onWillStopDragging);

    GestureEvent info;
    info.SetMainVelocity(1200.f);
    info.SetMainDelta(200.f);
    auto scrollable = pattern_->GetScrollableEvent()->GetScrollable();
    scrollable->HandleTouchDown();
    scrollable->HandleDragStart(info);
    scrollable->HandleDragUpdate(info);
    FlushUITasks();

    scrollable->HandleTouchUp();
    scrollable->HandleDragEnd(info);
    FlushUITasks();

    EXPECT_TRUE(isOnWillStopDraggingCallBack);
    EXPECT_FLOAT_EQ(willStopDraggingVelocity.Value(), info.GetMainVelocity());
}

/**
 * @tc.name: HandleOnWillStartDragging001
 * @tc.desc: Test OnWillStartDragging001
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollerEventTestTwoNg, OnWillStartDragging001, TestSize.Level1)
{
    bool isOnWillStartDraggingCallBack = false;
    auto onWillStartDragging = [&isOnWillStartDraggingCallBack]() {
        isOnWillStartDraggingCallBack = true;
    };

    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetEdgeEffect(EdgeEffect::SPRING, false);
    CreateFixedItems(20);
    CreateDone();
    eventHub_->SetOnWillStartDragging(onWillStartDragging);

    GestureEvent info;
    info.SetMainVelocity(-1200.f);
    info.SetMainDelta(-200.f);
    auto scrollable = pattern_->GetScrollableEvent()->GetScrollable();
    scrollable->HandleTouchDown();
    scrollable->HandleDragStart(info);
    scrollable->HandleDragUpdate(info);
    FlushUITasks();

    scrollable->HandleTouchUp();
    scrollable->HandleDragEnd(info);
    FlushUITasks();

    EXPECT_TRUE(isOnWillStartDraggingCallBack);
}

/**
 * @tc.name: onDidStopDragging001
 * @tc.desc: Test onDidStopDragging001
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollerEventTestTwoNg, onDidStopDragging001, TestSize.Level1)
{
    bool isDidStopDraggingCallBack = false;
    bool isFlingAfterDrag = false;
    auto onDidStopDragging = [&isDidStopDraggingCallBack, &isFlingAfterDrag](bool isWillFling) {
        isDidStopDraggingCallBack = true;
        isFlingAfterDrag = isWillFling;
    };
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetEdgeEffect(EdgeEffect::SPRING, false);
    CreateFixedItems(20);
    CreateDone();
    eventHub_->SetOnDidStopDragging(onDidStopDragging);

    GestureEvent info;
    info.SetMainVelocity(-1200.f);
    info.SetMainDelta(-200.f);
    auto scrollable = pattern_->GetScrollableEvent()->GetScrollable();
    scrollable->HandleTouchDown();
    scrollable->HandleDragStart(info);
    scrollable->HandleDragUpdate(info);
    FlushUITasks();

    scrollable->HandleTouchUp();
    scrollable->HandleDragEnd(info);
    FlushUITasks();

    EXPECT_TRUE(isDidStopDraggingCallBack);
    EXPECT_TRUE(isFlingAfterDrag);
}

/**
 * @tc.name: OnReachEndWithHeightChange
 * @tc.desc: Test Grid OnReachEnd with height changed
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollerEventTestTwoNg, OnReachEndWithHeightChange, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a grid that adapts to the main size of gridItems.
     * @tc.expected: onReachEnd not called
     */
    ResetElmtId();
    ViewStackProcessor::GetInstance()->StartGetAccessRecordingFor(GetElmtId());
    GridModelNG model;
    RefPtr<ScrollControllerBase> positionController = model.CreatePositionController();
    RefPtr<ScrollProxy> scrollBarProxy = model.CreateScrollBarProxy();
    model.Create(positionController, scrollBarProxy);
    ViewAbstract::SetWidth(CalcLength(WIDTH));
    ViewAbstract::SetHeight(CalcLength(Infinity<float>()));
    GetGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetMaxCount(1);
    int32_t reachEndCount = 0;
    auto event = [&reachEndCount]() { ++reachEndCount; };
    model.SetOnReachEnd(event);
    CreateGridItems(1);
    CreateDone();
    EXPECT_EQ(reachEndCount, 0);

    /**
     * @tc.steps: step2. Remove all gridItems
     * @tc.expected: onReachEnd not called
     */
    frameNode_->RemoveChildAtIndex(0);
    FlushUITasks();
    EXPECT_EQ(reachEndCount, 0);

    /**
     * @tc.steps: step3. Add 4 gridItems
     * @tc.expected: onReachEnd not called
     */
    for (int32_t i = 0; i < 4; i++) {
        GridItemModelNG itemModel;
        itemModel.Create(GridItemStyle::NONE);
        ViewAbstract::SetHeight(CalcLength(Dimension(ITEM_MAIN_SIZE)));
        RefPtr<UINode> currentNode = ViewStackProcessor::GetInstance()->Finish();
        auto currentFrameNode = AceType::DynamicCast<FrameNode>(currentNode);
        currentFrameNode->MountToParent(frameNode_);
    }
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    FlushUITasks();
    EXPECT_EQ(reachEndCount, 0);
}

/**
 * @tc.name: SpringAnimationTest001
 * @tc.desc: Test Grid onReachEnd when change height during spring animation.
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollerEventTestTwoNg, SpringAnimationTest001, TestSize.Level1)
{
    int32_t reachEndTimes = 0;
    auto onReachEnd = [&reachEndTimes]() { ++reachEndTimes; };
    MockAnimationManager::GetInstance().Reset();
    MockAnimationManager::GetInstance().SetTicks(2);
    auto model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetEdgeEffect(EdgeEffect::SPRING, true);
    model.SetOnReachEnd(std::move(onReachEnd));
    CreateFixedItems(10);
    CreateDone();

    /**
     * @tc.steps: step1. Simulate a scrolling gesture.
     * @tc.expected: Grid trigger spring animation.
     */

    GestureEvent info;
    info.SetMainVelocity(-1200.f);
    info.SetMainDelta(-200.f);
    auto scrollable = pattern_->GetScrollableEvent()->GetScrollable();
    scrollable->HandleTouchDown();
    scrollable->HandleDragStart(info);
    scrollable->HandleDragUpdate(info);
    FlushUITasks();
    EXPECT_EQ(reachEndTimes, 1);

    EXPECT_TRUE(pattern_->OutBoundaryCallback());
    scrollable->HandleTouchUp();
    scrollable->HandleDragEnd(info);
    FlushUITasks();
    EXPECT_EQ(reachEndTimes, 1);

    /**
     * @tc.steps: step2. play spring animation frame by frame, and decrease grid height during animation
     * @tc.expected: reachEnd will not trigger by height change
     */

    MockAnimationManager::GetInstance().Tick();
    layoutProperty_->UpdateUserDefinedIdealSize(CalcSize(std::nullopt, CalcLength(Dimension(HEIGHT + 100))));
    FlushUITasks();
    EXPECT_EQ(reachEndTimes, 1);
    MockAnimationManager::GetInstance().Tick();
    FlushUITasks();
    EXPECT_TRUE(MockAnimationManager::GetInstance().AllFinished());

    FlushUITasks();
    EXPECT_FLOAT_EQ(pattern_->info_.currentOffset_, 0.f);
    EXPECT_EQ(reachEndTimes, 2);
}

/**
 * @tc.name: SpringAnimationTest002
 * @tc.desc: Test Grid onReachEnd when change height during spring animation.
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollerEventTestTwoNg, SpringAnimationTest002, TestSize.Level1)
{
    int32_t reachEndTimes = 0;
    auto onReachEnd = [&reachEndTimes]() { ++reachEndTimes; };
    MockAnimationManager::GetInstance().Reset();
    MockAnimationManager::GetInstance().SetTicks(2);
    auto model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetEdgeEffect(EdgeEffect::SPRING, true);
    model.SetOnReachEnd(std::move(onReachEnd));
    CreateFixedItems(10);
    CreateDone();

    /**
     * @tc.steps: step1. Simulate a scrolling gesture.
     * @tc.expected: Grid trigger spring animation.
     */

    GestureEvent info;
    info.SetMainVelocity(-1200.f);
    info.SetMainDelta(-200.f);
    auto scrollable = pattern_->GetScrollableEvent()->GetScrollable();
    scrollable->HandleTouchDown();
    scrollable->HandleDragStart(info);
    scrollable->HandleDragUpdate(info);
    FlushUITasks();
    EXPECT_EQ(reachEndTimes, 1);

    EXPECT_TRUE(pattern_->OutBoundaryCallback());
    scrollable->HandleTouchUp();
    scrollable->HandleDragEnd(info);
    FlushUITasks();
    EXPECT_EQ(reachEndTimes, 1);

    /**
     * @tc.steps: step2. play spring animation frame by frame, and decrease grid height during animation
     * @tc.expected: reachEnd will not trigger by height change
     */

    MockAnimationManager::GetInstance().Tick();
    layoutProperty_->UpdateUserDefinedIdealSize(CalcSize(std::nullopt, CalcLength(Dimension(HEIGHT - 100))));
    FlushUITasks();
    EXPECT_EQ(reachEndTimes, 1);
    MockAnimationManager::GetInstance().Tick();
    FlushUITasks();
    EXPECT_TRUE(MockAnimationManager::GetInstance().AllFinished());

    FlushUITasks();
    EXPECT_FLOAT_EQ(pattern_->info_.currentOffset_, 0.f);
    EXPECT_EQ(reachEndTimes, 2);
}
} // namespace OHOS::Ace::NG