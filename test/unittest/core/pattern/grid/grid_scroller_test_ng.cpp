/*
 * Copyright (c) 2023-2024 Huawei Device Co., Ltd.
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

namespace OHOS::Ace::NG {

namespace {} // namespace

class GridScrollerTestNg : public GridTestNg {
public:
    AssertionResult ScrollToIndex(int32_t index, bool smooth, ScrollAlign align, float expectOffset);
    void ScrollToIndex(int32_t index, bool smooth, ScrollAlign align, std::optional<float> extraOffset);
};

AssertionResult GridScrollerTestNg::ScrollToIndex(int32_t index, bool smooth, ScrollAlign align, float expectOffset)
{
    // After every call to ScrollToIndex(), reset currentOffset_
    float startOffset = pattern_->GetTotalOffset();
    pattern_->ScrollToIndex(index, smooth, align);
    FlushLayoutTask(frameNode_);
    if (smooth) {
        // Straight to the end of the anmiation
    }
    float currentOffset = pattern_->GetTotalOffset();
    pattern_->info_.currentOffset_ = 0; // for avoid some error
    FlushLayoutTask(frameNode_);
    pattern_->ScrollTo(startOffset); // reset currentOffset_
    FlushLayoutTask(frameNode_);
    return IsEqual(currentOffset, expectOffset);
}

void GridScrollerTestNg::ScrollToIndex(int32_t index, bool smooth, ScrollAlign align, std::optional<float> extraOffset)
{
    pattern_->ScrollToIndex(index, smooth, align, extraOffset);
    FlushLayoutTask(frameNode_);
}

/**
 * @tc.name: ScrollToIndex001
 * @tc.desc: Test ScrollToIndex
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollerTestNg, ScrollToIndex001, TestSize.Level1)
{
    /**
     * @tc.cases: Grid at top, ScrollTo index:0, text each ScrollAlign
     * @tc.expected: Each test grid does not scroll
     */
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    CreateFixedItems(10);
    CreateDone(frameNode_);
    EXPECT_TRUE(pattern_->IsAtTop());
    int32_t index = 0;
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::START, 0.f));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::CENTER, 0.f));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::END, 0.f));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::AUTO, 0.f));
}

/**
 * @tc.name: ScrollToIndex002
 * @tc.desc: Test ScrollToIndex
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollerTestNg, ScrollToIndex002, TestSize.Level1)
{
    /**
     * @tc.cases: Grid at top, ScrollTo index:4, index:4 item is in the view, text each ScrollAlign
     * @tc.expected: Each test scroll the correct distance
     */
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    CreateFixedItems(15);
    CreateDone(frameNode_);
    int32_t index = 4;
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::START, ITEM_HEIGHT * 2));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::CENTER, ITEM_HEIGHT * 0.5));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::END, 0));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::AUTO, 0));
}

/**
 * @tc.name: ScrollToIndex003
 * @tc.desc: Test ScrollToIndex
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollerTestNg, ScrollToIndex003, TestSize.Level1)
{
    /**
     * @tc.cases: Grid at top, ScrollTo index:8, index:8 item is below the view, text each ScrollAlign
     * @tc.expected: Each test scroll the correct distance
     */
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    CreateFixedItems(20);
    CreateDone(frameNode_);
    int32_t index = 8;
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::START, ITEM_HEIGHT * 4));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::CENTER, ITEM_HEIGHT * 2.5));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::END, ITEM_HEIGHT));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::AUTO, ITEM_HEIGHT));
}

/**
 * @tc.name: ScrollToIndex004
 * @tc.desc: Test ScrollToIndex
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollerTestNg, ScrollToIndex004, TestSize.Level1)
{
    /**
     * @tc.cases: Grid at top, ScrollTo index:LAST_ITEM, index:LAST_ITEM item is below the view, text each ScrollAlign
     * @tc.expected: Each test scroll the correct distance
     */
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    CreateFixedItems(20);
    CreateDone(frameNode_);
    int32_t index = LAST_ITEM;
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::START, ITEM_HEIGHT * 6));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::CENTER, ITEM_HEIGHT * 6));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::END, ITEM_HEIGHT * 6));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::AUTO, ITEM_HEIGHT * 6));
}

/**
 * @tc.name: ScrollToIndex005
 * @tc.desc: Test ScrollToIndex
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollerTestNg, ScrollToIndex005, TestSize.Level1)
{
    /**
     * @tc.cases: Grid at middle(scroll a little distance), ScrollTo index:0, index:0 item is above the view,
     *            text each ScrollAlign
     * @tc.expected: Each test scroll the correct distance
     */
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    CreateFixedItems(20);
    CreateDone(frameNode_);
    pattern_->ScrollTo(ITEM_HEIGHT * 4);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetTotalOffset(), ITEM_HEIGHT * 4);
    EXPECT_EQ(accessibilityProperty_->GetScrollOffSet(), pattern_->GetTotalOffset());
    EXPECT_FALSE(pattern_->IsAtTop());
    EXPECT_FALSE(pattern_->IsAtBottom());
    int32_t index = 0;
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::START, 0));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::CENTER, 0));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::END, 0));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::AUTO, 0));
}

/**
 * @tc.name: ScrollToIndex006
 * @tc.desc: Test ScrollToIndex
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollerTestNg, ScrollToIndex006, TestSize.Level1)
{
    /**
     * @tc.cases: Grid at bottom, ScrollTo index:LAST_ITEM, index:LAST_ITEM item is in the view, text each ScrollAlign
     * @tc.expected: Each test scroll the correct distance
     */
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    CreateFixedItems(20);
    CreateDone(frameNode_);
    pattern_->ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, false);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetTotalOffset(), ITEM_HEIGHT * 6);
    EXPECT_TRUE(pattern_->IsAtBottom());
    int32_t index = LAST_ITEM;
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::START, ITEM_HEIGHT * 6));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::CENTER, ITEM_HEIGHT * 6));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::END, ITEM_HEIGHT * 6));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::AUTO, ITEM_HEIGHT * 6));
}

/**
 * @tc.name: ScrollToIndex007
 * @tc.desc: Test ScrollToIndex invalid
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollerTestNg, ScrollToIndex007, TestSize.Level1)
{
    /**
     * @tc.cases: ScrollTo invalid index:-2, text each ScrollAlign
     * @tc.expected: Each test scroll the correct distance
     */
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    CreateFixedItems(12);
    CreateDone(frameNode_);
    int32_t index = -2;
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::START, 0));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::CENTER, 0));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::END, 0));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::AUTO, 0));
}

/**
 * @tc.name: ScrollToIndex008
 * @tc.desc: Test ScrollToIndex
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollerTestNg, ScrollToIndex008, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    CreateFixedItems(16);
    CreateDone(frameNode_);
    /**
     * @tc.steps: step1. Call ScrollToIndex()
     * @tc.expected: pattern_->targetIndex.value() is 15.
     * @tc.expected: pattern_->scrollAlign_ is ScrollAlign::END.
     */
    pattern_->ScrollToIndex(15, true, ScrollAlign::END);
    EXPECT_EQ(pattern_->targetIndex_.value(), 15);
    EXPECT_EQ(pattern_->scrollAlign_, ScrollAlign::END);
}

/**
 * @tc.name: ScrollToIndex009
 * @tc.desc: Test ScrollToIndex
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollerTestNg, ScrollToIndex009, TestSize.Level1)
{
    /**
     * @tc.cases: Set gap, ScrollTo index:8, text each ScrollAlign
     * @tc.expected: Each test scroll the correct distance
     */
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetColumnsGap(Dimension(COL_GAP));
    model.SetRowsGap(Dimension(ROW_GAP));
    CreateFixedItems(20);
    CreateDone(frameNode_);
    int32_t index = 8;
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::START, ITEM_HEIGHT * 4 + ROW_GAP * 4));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::CENTER, ITEM_HEIGHT * 2.5 + ROW_GAP * 4));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::END, ITEM_HEIGHT + ROW_GAP * 4));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::AUTO, ITEM_HEIGHT + ROW_GAP * 4));
}

/**
 * @tc.name: ScrollToIndex010
 * @tc.desc: Test ScrollToIndex
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollerTestNg, ScrollToIndex010, TestSize.Level1)
{
    /**
     * @tc.cases: Set GridLayoutOptions:irregularIndexes, ScrollTo index:7, text each ScrollAlign
     * @tc.expected: Each test scroll the correct distance
     */
    GridLayoutOptions option;
    option.irregularIndexes = { 6, 1, 3, 4, 5, 0 };
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr 1fr");
    model.SetLayoutOptions(option);
    model.SetColumnsGap(Dimension(COL_GAP));
    model.SetRowsGap(Dimension(ROW_GAP));
    CreateFixedItems(10);
    CreateDone(frameNode_);
    int32_t index = 5;
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::START, ITEM_HEIGHT * 4 + ROW_GAP * 7));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::CENTER, ITEM_HEIGHT * 3.5 + ROW_GAP * 5));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::END, ITEM_HEIGHT * 2 + ROW_GAP * 5));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::AUTO, ITEM_HEIGHT * 2 + ROW_GAP * 5));
}

/**
 * @tc.name: ScrollToIndex011
 * @tc.desc: Test ScrollToIndex
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollerTestNg, DISABLED_ScrollToIndex011, TestSize.Level1)
{
    // to do ... ScrollToIndex not support getSizeByIndex at now!!!!
    /**
     * @tc.cases: Set GridLayoutOptions:irregularIndexes getSizeByIndex,
     *            set gap, ScrollTo index:7, text each ScrollAlign
     * @tc.expected: Each test scroll the correct distance
     */
    GridLayoutOptions option;
    option.irregularIndexes = { 6, 1, 3, 4, 5, 0 };
    GetSizeByIndex onGetIrregularSizeByIndex = [](int32_t index) {
        if (index == 3) {
            return GridItemSize { 1, 2 };
        }
        return GridItemSize { 1, 4 };
    };
    option.getSizeByIndex = std::move(onGetIrregularSizeByIndex);
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr 1fr");
    model.SetLayoutOptions(option);
    model.SetColumnsGap(Dimension(COL_GAP));
    model.SetRowsGap(Dimension(ROW_GAP));
    CreateFixedItems(10);
    CreateDone(frameNode_);
    int32_t index = 5;
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::START, ITEM_HEIGHT * 4 + ROW_GAP * 3));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::CENTER, ITEM_HEIGHT * 5.5 + ROW_GAP * 4));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::END, ITEM_HEIGHT + ROW_GAP * 3));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::AUTO, ITEM_HEIGHT + ROW_GAP * 3));
}

/**
 * @tc.name: ScrollToIndex012
 * @tc.desc: Test ScrollToIndex with big gap(lineHeight + gap > mainSize)
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollerTestNg, ScrollToIndex012, TestSize.Level1)
{
    /**
     * @tc.cases: Set BIG_ROW_GAP, ScrollTo index:5, text ScrollAlign::AUTO
     * @tc.expected: Each test scroll the correct distance
     */
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetRowsGap(Dimension(BIG_ROW_GAP));
    CreateFixedItems(15);
    CreateDone(frameNode_);
    int32_t index = 5;
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::AUTO, ITEM_HEIGHT * 3 + BIG_ROW_GAP * 2 - GRID_HEIGHT));
    /**
     * @tc.cases: use ScrollTo to make item 5 in the last line, ScrollTo index:5, text ScrollAlign::AUTO
     * @tc.expected: scrollToIndex don't change grid offset
     */
    auto autoPosition = ITEM_HEIGHT * 3 + BIG_ROW_GAP * 2 - GRID_HEIGHT + ITEM_HEIGHT;
    pattern_->ScrollTo(autoPosition);
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::AUTO, autoPosition));
}

/**
 * @tc.name: ScrollToIndex013
 * @tc.desc: Test ScrollToIndex with big gap(lineHeight + gap > mainSize)
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollerTestNg, ScrollToIndex013, TestSize.Level1)
{
    /**
     * @tc.cases: Set BIG_ROW_GAP, ScrollTo index:11, text each ScrollAlign::CENTER
     * @tc.expected: Each test scroll the correct distance
     */
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetRowsGap(Dimension(BIG_ROW_GAP));
    CreateFixedItems(15);
    CreateDone(frameNode_);
    int32_t index = 5;
    auto enddPosition = ITEM_HEIGHT * 3 + BIG_ROW_GAP * 2 - GRID_HEIGHT;
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::CENTER, enddPosition + (GRID_HEIGHT - ITEM_HEIGHT) / 2));
}

/**
 * @tc.name: ScrollToIndex014
 * @tc.desc: Test ScrollToIndex with medium gap(3*lineHeight + 3*gap > mainSize)
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollerTestNg, ScrollToIndex014, TestSize.Level1)
{
    /**
     * @tc.cases: Set MEDIUM_ROW_GAP and scroll to specified position, ScrollTo index:12, text each ScrollAlign::AUTO
     * @tc.expected: Each test scroll the correct distance
     */
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetRowsGap(Dimension(MEDIUM_ROW_GAP));
    CreateFixedItems(15);
    CreateDone(frameNode_);
    auto position = ITEM_HEIGHT + 5 * COL_GAP;
    pattern_->ScrollTo(position);
    FlushLayoutTask(frameNode_);
    int32_t index = 6;
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::AUTO, position));
}

/**
 * @tc.name: ScrollToIndex015
 * @tc.desc: Test ScrollToIndex with extraOffset
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollerTestNg, ScrollToIndex015, TestSize.Level1)
{
    /**
     * @tc.cases: ScrollToIndex without animation
     * @tc.expected: GetTotalOffset is right
     */
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    CreateFixedItems(20);
    CreateDone(frameNode_);
    std::optional<float> extraOffset = -400.f;
    ScrollToIndex(2, false, ScrollAlign::START, extraOffset);
    EXPECT_FLOAT_EQ(pattern_->GetTotalOffset(), 0.f);
    ScrollToIndex(17, false, ScrollAlign::START, extraOffset);
    EXPECT_FLOAT_EQ(pattern_->GetTotalOffset(), 1200.f); // 10 * ITEM_HEIGHT -  GRID_HEIGHT
    ScrollToIndex(17, false, ScrollAlign::END, extraOffset);
    EXPECT_FLOAT_EQ(pattern_->GetTotalOffset(), 600.f); // 1200.f - ITEM_HEIGHT - 400.f
    ScrollToIndex(LAST_ITEM, false, ScrollAlign::END, extraOffset);
    EXPECT_FLOAT_EQ(pattern_->GetTotalOffset(), 800.f); // 1200.f - 400.f

    extraOffset = 400.f;
    ScrollToIndex(2, false, ScrollAlign::START, extraOffset);
    EXPECT_FLOAT_EQ(pattern_->GetTotalOffset(), 600.f); // ITEM_HEIGHT + 400.f
    ScrollToIndex(2, false, ScrollAlign::END, extraOffset);
    EXPECT_FLOAT_EQ(pattern_->GetTotalOffset(), 0.f);
    ScrollToIndex(17, false, ScrollAlign::END, extraOffset);
    EXPECT_FLOAT_EQ(pattern_->GetTotalOffset(), 1200.f);
    ScrollToIndex(LAST_ITEM, false, ScrollAlign::END, extraOffset);
    EXPECT_FLOAT_EQ(pattern_->GetTotalOffset(), 1200.f);
}

/**
 * @tc.name: ScrollToIndex016
 * @tc.desc: Test ScrollToIndex with extraOffset
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollerTestNg, ScrollToIndex016, TestSize.Level1)
{
    /**
     * @tc.cases: ScrollToIndex with animation
     * @tc.expected: GetFinalPosition is right
     */
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetLayoutOptions({});
    CreateFixedItems(20);
    CreateDone(frameNode_);

    std::optional<float> extraOffset = -400.f;
    ScrollToIndex(2, true, ScrollAlign::START, extraOffset);
    EXPECT_FLOAT_EQ(pattern_->GetFinalPosition(), -200.f); // ITEM_HEIGHT - 400.f
    ScrollToIndex(17, true, ScrollAlign::START, extraOffset);
    EXPECT_FLOAT_EQ(pattern_->GetFinalPosition(), 1200.f); // 10 * ITEM_HEIGHT - GRID_HEIGHT
    ScrollToIndex(17, true, ScrollAlign::END, extraOffset);
    EXPECT_FLOAT_EQ(pattern_->GetFinalPosition(), 600.f); // 1200.f - ITEM_HEIGHT - 400.f
    ScrollToIndex(LAST_ITEM, true, ScrollAlign::END, extraOffset);
    EXPECT_FLOAT_EQ(pattern_->GetFinalPosition(), -400.f); // extraOffset

    extraOffset = 400.f;
    ScrollToIndex(2, true, ScrollAlign::START, extraOffset);
    EXPECT_FLOAT_EQ(pattern_->GetFinalPosition(), 600.f); // ITEM_HEIGHT + 400.f
    ScrollToIndex(17, true, ScrollAlign::END, extraOffset);
    EXPECT_FLOAT_EQ(pattern_->GetFinalPosition(), 1400.f); // 1200.f - ITEM_HEIGHT + 400.f
    ScrollToIndex(LAST_ITEM, true, ScrollAlign::END, extraOffset);
    EXPECT_FLOAT_EQ(pattern_->GetFinalPosition(), 400.f); // extraOffset
}

/**
 * @tc.name: ScrollTo001
 * @tc.desc: Test ScrollTo Function.
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollerTestNg, ScrollTo001, TestSize.Level1)
{
    /**
     * @tc.cases: UnScrollable grid
     * @tc.expected: Unroll
     */
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr");
    CreateFixedItems(4);
    CreateDone(frameNode_);
    pattern_->ScrollTo(ITEM_HEIGHT);
    EXPECT_EQ(pattern_->GetGridLayoutInfo().currentOffset_, 0);
}

/**
 * @tc.name: ScrollTo002
 * @tc.desc: Test ScrollTo Function.
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollerTestNg, ScrollTo002, TestSize.Level1)
{
    /**
     * @tc.cases: Scrollable grid
     * @tc.expected: Rolled
     */
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr");
    CreateFixedItems(10);
    CreateDone(frameNode_);
    pattern_->ScrollTo(ITEM_HEIGHT);
    EXPECT_EQ(pattern_->GetGridLayoutInfo().currentOffset_, -ITEM_HEIGHT);
}

/**
 * @tc.name: ScrollTo003
 * @tc.desc: Test ScrollTo Function.
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollerTestNg, ScrollTo003, TestSize.Level1)
{
    /**
     * @tc.cases: Scrollable grid, scroll position greater than GRID_HEIGHT
     * @tc.expected: Rolled
     */
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr");
    CreateFixedItems(10);
    CreateDone(frameNode_);
    pattern_->ScrollTo(ITEM_HEIGHT * 5);
    EXPECT_EQ(pattern_->GetGridLayoutInfo().currentOffset_, -ITEM_HEIGHT * 5);
}

/**
 * @tc.name: ScrollTo004
 * @tc.desc: Test ScrollTo Function.
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollerTestNg, ScrollTo004, TestSize.Level1)
{
    /**
     * @tc.cases: When isConfigScrollable_ is false
     * @tc.expected: Can not roll
     */
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr");
    model.SetRowsTemplate("1fr");
    CreateFixedItems(10);
    CreateDone(frameNode_);
    EXPECT_FALSE(pattern_->isConfigScrollable_);

    pattern_->ScrollTo(ITEM_HEIGHT * 5);
    EXPECT_EQ(pattern_->GetGridLayoutInfo().currentOffset_, 0.f);
}

/**
 * @tc.name: AnimateTo001
 * @tc.desc: Test AnimateTo Function.
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollerTestNg, AnimateTo001, TestSize.Level1)
{
    /**
     * @tc.cases: UnScrollable grid
     * @tc.expected: Unroll
     */
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr");
    CreateFixedItems(4);
    CreateDone(frameNode_);
    pattern_->AnimateTo(ITEM_HEIGHT, 200.f, Curves::LINEAR, true);
    float endValue = pattern_->GetFinalPosition();
    pattern_->UpdateCurrentOffset(pattern_->GetTotalOffset() - endValue, SCROLL_FROM_ANIMATION_CONTROLLER);
    EXPECT_EQ(pattern_->GetGridLayoutInfo().currentOffset_, 0);
}

/**
 * @tc.name: AnimateTo002
 * @tc.desc: Test AnimateTo Function.
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollerTestNg, AnimateTo002, TestSize.Level1)
{
    /**
     * @tc.cases: Scrollable grid
     * @tc.expected: Rolled
     */
    // smooth is true
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr");
    CreateFixedItems(10);
    CreateDone(frameNode_);
    pattern_->AnimateTo(ITEM_HEIGHT, 200.f, Curves::LINEAR, true);
    float endValue = pattern_->GetFinalPosition();
    pattern_->UpdateCurrentOffset(pattern_->GetTotalOffset() - endValue, SCROLL_FROM_ANIMATION_CONTROLLER);
    EXPECT_EQ(pattern_->GetGridLayoutInfo().currentOffset_, -ITEM_HEIGHT);
}

/**
 * @tc.name: AnimateTo003
 * @tc.desc: Test AnimateTo Function.
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollerTestNg, AnimateTo003, TestSize.Level1)
{
    /**
     * @tc.cases: Scrollable grid, scroll position greater than GRID_HEIGHT
     * @tc.expected: Rolled
     */
    // smooth is true
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr");
    CreateFixedItems(10);
    CreateDone(frameNode_);
    pattern_->AnimateTo(ITEM_HEIGHT * 9, 200.f, Curves::LINEAR, true);
    float endValue = pattern_->GetFinalPosition();
    pattern_->UpdateCurrentOffset(pattern_->GetTotalOffset() - endValue, SCROLL_FROM_ANIMATION_CONTROLLER);
    EXPECT_EQ(pattern_->GetGridLayoutInfo().currentOffset_, -ITEM_HEIGHT * 9);
}

/**
 * @tc.name: AnimateTo004
 * @tc.desc: Test AnimateTo Function.
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollerTestNg, AnimateTo004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. When Animation is not running, call AnimateTo
     * @tc.expected: onScrollStart event will be triggered
     */
    bool isTrigger = false;
    auto onScrollStart = [&isTrigger]() { isTrigger = true; };
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr");
    model.SetOnScrollStart(onScrollStart);
    model.SetScrollBarMode(DisplayMode::ON);
    CreateFixedItems(10);
    CreateDone(frameNode_);
    pattern_->AnimateTo(ITEM_HEIGHT, 200.f, Curves::LINEAR, true);
    EXPECT_TRUE(isTrigger);

    float endValue = pattern_->GetFinalPosition();
    pattern_->UpdateCurrentOffset(pattern_->GetTotalOffset() - endValue, SCROLL_FROM_ANIMATION_CONTROLLER);
    EXPECT_EQ(pattern_->GetGridLayoutInfo().currentOffset_, -ITEM_HEIGHT);

    /**
     * @tc.steps: step2. When Animation is running, call AnimateTo
     * @tc.expected: onScrollStart event will not be triggered
     */
    isTrigger = false;             // reset val
    pattern_->scrollAbort_ = true; // set running
    pattern_->AnimateTo(ITEM_HEIGHT * 2, 200.f, Curves::LINEAR, true);
    EXPECT_FALSE(isTrigger);
}

/**
 * @tc.name: AnimateTo005
 * @tc.desc: Test AnimateTo Function.
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollerTestNg, AnimateTo005, TestSize.Level1)
{
    /**
     * @tc.cases: When isConfigScrollable_ is false
     * @tc.expected: Can not roll
     */
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr");
    model.SetRowsTemplate("1fr");
    CreateFixedItems(10);
    CreateDone(frameNode_);
    EXPECT_FALSE(pattern_->isConfigScrollable_);

    pattern_->AnimateTo(ITEM_HEIGHT, 200.f, Curves::LINEAR, true);
    float endValue = pattern_->GetFinalPosition();
    pattern_->UpdateCurrentOffset(pattern_->GetTotalOffset() - endValue, SCROLL_FROM_ANIMATION_CONTROLLER);
    EXPECT_EQ(pattern_->GetGridLayoutInfo().currentOffset_, 0.f);
}

/**
 * @tc.name: PositionController001
 * @tc.desc: Test positionController func in VERTICAL
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollerTestNg, PositionController001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Unscrollable
     * @tc.expected: jumpIndex_ not change
     */
    GridModelNG model = CreateGrid();
    CreateFixedItems(14);
    CreateDone(frameNode_);
    EXPECT_FALSE(pattern_->isConfigScrollable_);
    auto controller = pattern_->positionController_;
    controller->ScrollToIndex(1, false, ScrollAlign::START, std::nullopt);
    EXPECT_EQ(pattern_->GetGridLayoutInfo().jumpIndex_, EMPTY_JUMP_INDEX);
    EXPECT_EQ(pattern_->GetGridLayoutInfo().currentOffset_, 0);

    /**
     * @tc.steps: step2. Test JumpTo func.
     * @tc.expected: Verify return value.
     */
    ClearOldNodes();
    model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    CreateFixedItems(10);
    CreateDone(frameNode_);
    controller = pattern_->positionController_;
    controller->ScrollToIndex(1, false, ScrollAlign::START, std::nullopt);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetGridLayoutInfo().currentOffset_, 0);
    controller->ScrollToIndex(9, false, ScrollAlign::START, std::nullopt);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetGridLayoutInfo().currentOffset_, 0);
    controller->ScrollToIndex(5, false, ScrollAlign::START, std::nullopt);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetGridLayoutInfo().currentOffset_, 0);

    ClearOldNodes();
    model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    CreateFixedItems(10);
    CreateDone(frameNode_);
    controller = pattern_->positionController_;
    controller->ScrollToIndex(1, false, ScrollAlign::CENTER, std::nullopt);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetGridLayoutInfo().currentOffset_, 0);
    controller->ScrollToIndex(6, false, ScrollAlign::CENTER, std::nullopt);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetGridLayoutInfo().currentOffset_, 0);
    controller->ScrollToIndex(5, false, ScrollAlign::CENTER, std::nullopt);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetGridLayoutInfo().currentOffset_, -100.f);

    ClearOldNodes();
    model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    CreateFixedItems(10);
    CreateDone(frameNode_);
    controller = pattern_->positionController_;
    controller->ScrollToIndex(1, false, ScrollAlign::END, std::nullopt);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetGridLayoutInfo().currentOffset_, 0);
    controller->ScrollToIndex(6, false, ScrollAlign::END, std::nullopt);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetGridLayoutInfo().currentOffset_, 0);
    controller->ScrollToIndex(5, false, ScrollAlign::END, std::nullopt);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetGridLayoutInfo().currentOffset_, 0);

    ClearOldNodes();
    model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    CreateFixedItems(10);
    CreateDone(frameNode_);
    controller = pattern_->positionController_;
    controller->ScrollToIndex(1, false, ScrollAlign::AUTO, std::nullopt);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetGridLayoutInfo().currentOffset_, 0);
    controller->ScrollToIndex(6, false, ScrollAlign::AUTO, std::nullopt);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetGridLayoutInfo().currentOffset_, 0);
    controller->ScrollToIndex(5, false, ScrollAlign::AUTO, std::nullopt);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetGridLayoutInfo().currentOffset_, 0);

    ClearOldNodes();
    model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    CreateFixedItems(10);
    CreateDone(frameNode_);
    controller = pattern_->positionController_;
    controller->ScrollToIndex(1, false, ScrollAlign::NONE, std::nullopt);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetGridLayoutInfo().currentOffset_, 0);
    controller->ScrollToIndex(6, false, ScrollAlign::NONE, std::nullopt);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetGridLayoutInfo().currentOffset_, 0);
    controller->ScrollToIndex(5, false, ScrollAlign::NONE, std::nullopt);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetGridLayoutInfo().currentOffset_, 0);
}

/**
 * @tc.name: PositionController002
 * @tc.desc: Test positionController func in VERTICAL Grid
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollerTestNg, PositionController002, TestSize.Level1)
{
    /**
     * @tc.steps: step2. Test AnimateTo func.
     * @tc.expected: Verify return value.
     */
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    CreateFixedItems(10);
    CreateDone(frameNode_);
    auto controller = pattern_->positionController_;
    controller->AnimateTo(Dimension(100.f, DimensionUnit::PX), 200.f, Curves::LINEAR, false);
    ASSERT_NE(pattern_->curveAnimation_, nullptr);

    /**
     * @tc.steps: step3. Test GetScrollDirection func.
     * @tc.expected: Verify return value.
     */
    EXPECT_EQ(controller->GetScrollDirection(), Axis::VERTICAL);

    /**
     * @tc.steps: step4. Test GetCurrentOffset func.
     * @tc.expected: Verify return value.
     */
    // When finger moves up, offset is negative.
    pattern_->UpdateCurrentOffset(-20.f, SCROLL_FROM_UPDATE);
    Offset currentOffset = controller->GetCurrentOffset();
    EXPECT_EQ(currentOffset, Offset(0, 20.f));

    /**
     * @tc.steps: step5. Test ScrollToEdge func.
     * @tc.expected: Verify return value. Animation should be stopped
     */
    controller->ScrollToEdge(ScrollEdgeType::SCROLL_LEFT, true);
    EXPECT_EQ(pattern_->GetGridLayoutInfo().jumpIndex_, EMPTY_JUMP_INDEX);

    controller->ScrollToEdge(ScrollEdgeType::SCROLL_RIGHT, true);
    EXPECT_EQ(pattern_->GetGridLayoutInfo().jumpIndex_, EMPTY_JUMP_INDEX);

    pattern_->isSmoothScrolling_ = true;
    controller->ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, true);
    EXPECT_FALSE(pattern_->isSmoothScrolling_);
    EXPECT_EQ(pattern_->GetGridLayoutInfo().jumpIndex_, LAST_ITEM);

    pattern_->isSmoothScrolling_ = true;
    controller->ScrollToEdge(ScrollEdgeType::SCROLL_TOP, true);
    EXPECT_FALSE(pattern_->isSmoothScrolling_);
    EXPECT_EQ(pattern_->GetGridLayoutInfo().jumpIndex_, 0);

    /**
     * @tc.steps: step6. Test ScrollPage func.
     * @tc.expected: Verify currentOffset.
     */
    FlushLayoutTask(frameNode_);
    controller->ScrollPage(false, false);
    EXPECT_TRUE(IsEqual(controller->GetCurrentOffset(), Offset(0, GRID_HEIGHT)));

    // scroll to previous page
    controller->ScrollPage(true, false);
    EXPECT_EQ(controller->GetCurrentOffset(), Offset(0, 0));

    /**
     * @tc.steps: step7. Test IsAtEnd func.
     */
    EXPECT_FALSE(controller->IsAtEnd());
    controller->ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, true);
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(controller->IsAtEnd());
}

/**
 * @tc.name: PositionController003
 * @tc.desc: Test positionController func in HORIZONTAL Grid
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollerTestNg, PositionController003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Change Grid width to 300.
     */
    GridModelNG model = CreateGrid();
    model.SetRowsTemplate("1fr 1fr");
    CreateFixedItems(10);
    CreateDone(frameNode_);
    FlushLayoutTask(frameNode_);

    /**
     * @tc.steps: step2. Test GetScrollDirection func.
     * @tc.expected: Verify return value.
     */
    auto controller = pattern_->positionController_;
    EXPECT_EQ(controller->GetScrollDirection(), Axis::HORIZONTAL);

    /**
     * @tc.steps: step4. Test ScrollToEdge func.
     * @tc.expected: Verify return value.
     */
    controller->ScrollToEdge(ScrollEdgeType::SCROLL_RIGHT, false);
    EXPECT_EQ(pattern_->GetGridLayoutInfo().jumpIndex_, EMPTY_JUMP_INDEX);
    controller->ScrollToEdge(ScrollEdgeType::SCROLL_LEFT, false);
    EXPECT_EQ(pattern_->GetGridLayoutInfo().jumpIndex_, EMPTY_JUMP_INDEX);
    controller->ScrollToEdge(ScrollEdgeType::SCROLL_TOP, false);
    EXPECT_EQ(pattern_->GetGridLayoutInfo().jumpIndex_, 0);
    controller->ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, false);
    EXPECT_EQ(pattern_->GetGridLayoutInfo().jumpIndex_, LAST_ITEM);

    /**
     * @tc.steps: step5. Test ScrollPage func.
     * @tc.expected: Verify currentOffset.
     */
    pattern_->UpdateCurrentOffset(-20.f, SCROLL_FROM_UPDATE);
    controller->ScrollPage(true, false);
    EXPECT_TRUE(IsEqual(controller->GetCurrentOffset(), Offset(20 - GRID_WIDTH, 0)));
    EXPECT_EQ(pattern_->GetMainContentSize(), GRID_WIDTH);
    controller->ScrollPage(false, false);
    EXPECT_TRUE(IsEqual(controller->GetCurrentOffset(), Offset(20.f, 0)));
}

/**
 * @tc.name: PositionController004
 * @tc.desc: Test positionController func in Axis::NONE Grid
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollerTestNg, PositionController004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Supplement ScrollPage, GetCurrentOffset branch,
     * has no condition that axis_ is Axis::NONE.
     */
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    CreateFixedItems(10);
    CreateDone(frameNode_);
    pattern_->SetAxis(Axis::NONE);
    auto controller = pattern_->positionController_;
    controller->ScrollPage(true, false);
    controller->GetCurrentOffset();
    EXPECT_EQ(pattern_->GetGridLayoutInfo().currentOffset_, 0);
}

/**
 * @tc.name: PositionController005
 * @tc.desc: Test positionController func
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollerTestNg, PositionController005, TestSize.Level1)
{
    /**
     * @tc.cases: When isConfigScrollable_ is false
     * @tc.expected: Can not roll
     */
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr 1fr");
    model.SetRowsTemplate("1fr 1fr");
    CreateFixedItems(10);
    CreateDone(frameNode_);
    EXPECT_FALSE(pattern_->isConfigScrollable_);

    auto controller = pattern_->positionController_;
    controller->ScrollPage(true, false);
    EXPECT_EQ(pattern_->GetGridLayoutInfo().currentOffset_, 0);
}

namespace {
constexpr float SCROLL_FIXED_VELOCITY = 200.f;
constexpr float OFFSET_TIME = 100.f;
constexpr int32_t TIME_CHANGED_COUNTS = 20;
} // namespace
/**
 * @tc.name: PositionController006
 * @tc.desc: Test positionController func in VERTICAL Grid
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollerTestNg, PositionController006, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    CreateFixedItems(10);
    CreateDone(frameNode_);
    auto controller = pattern_->positionController_;
    controller->ScrollToEdge(ScrollEdgeType::SCROLL_LEFT, SCROLL_FIXED_VELOCITY);
    EXPECT_FALSE(pattern_->fixedVelocityMotion_);
    controller->ScrollToEdge(ScrollEdgeType::SCROLL_RIGHT, SCROLL_FIXED_VELOCITY);
    EXPECT_FALSE(pattern_->fixedVelocityMotion_);
    controller->ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, SCROLL_FIXED_VELOCITY);
    EXPECT_TRUE(pattern_->fixedVelocityMotion_);
    EXPECT_EQ(pattern_->fixedVelocityMotion_->GetCurrentVelocity(), -SCROLL_FIXED_VELOCITY);
    int32_t offsetTime = OFFSET_TIME;
    for (int i = 0; i < TIME_CHANGED_COUNTS; i++) {
        pattern_->fixedVelocityMotion_->OnTimestampChanged(offsetTime, 0.0f, false);
        offsetTime = offsetTime + OFFSET_TIME;
        FlushLayoutTask(frameNode_);
    }
    EXPECT_TRUE(pattern_->IsAtBottom());
    controller->ScrollToEdge(ScrollEdgeType::SCROLL_TOP, SCROLL_FIXED_VELOCITY);
    EXPECT_TRUE(pattern_->fixedVelocityMotion_);
    EXPECT_EQ(pattern_->fixedVelocityMotion_->GetCurrentVelocity(), SCROLL_FIXED_VELOCITY);
    offsetTime = OFFSET_TIME;
    for (int i = 0; i < TIME_CHANGED_COUNTS; i++) {
        pattern_->fixedVelocityMotion_->OnTimestampChanged(offsetTime, 0.0f, false);
        offsetTime = offsetTime + OFFSET_TIME;
        FlushLayoutTask(frameNode_);
    }
    EXPECT_TRUE(pattern_->IsAtTop());
}

namespace {
constexpr float SCROLL_FIXED_VELOCITY_007 = 100.f;
constexpr float OFFSET_TIME_007 = 100.f;
constexpr int32_t TIME_CHANGED_COUNTS_007 = 21;
} // namespace
/**
 * @tc.name: PositionController007
 * @tc.desc: Test positionController func in VERTICAL Grid
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollerTestNg, PositionController007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Grid Item
     */
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    CreateFixedItems(10);
    CreateDone(frameNode_);

    /**
     * @tc.steps: step2. Scroll to the left edge
     * expected: Fixed Verify is is 0.
     */
    auto controller = pattern_->positionController_;
    controller->ScrollToEdge(ScrollEdgeType::SCROLL_LEFT, SCROLL_FIXED_VELOCITY_007);
    EXPECT_FALSE(pattern_->fixedVelocityMotion_);

    /**
     * @tc.steps: step3. Scroll to the right edge
     * expected: Fixed Verify is is 0.
     */
    controller->ScrollToEdge(ScrollEdgeType::SCROLL_RIGHT, SCROLL_FIXED_VELOCITY_007);
    EXPECT_FALSE(pattern_->fixedVelocityMotion_);

    /**
     * @tc.steps: step4. Scroll to the bottom edge
     * expected: 1.Fixed Verify is is non-zero.
     *           2.The current Velocity is equal to the set fixed velocity
     */
    controller->ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, SCROLL_FIXED_VELOCITY_007);
    EXPECT_TRUE(pattern_->fixedVelocityMotion_);
    EXPECT_EQ(pattern_->fixedVelocityMotion_->GetCurrentVelocity(), -SCROLL_FIXED_VELOCITY_007);

    /**
     * @tc.steps: step5. 1. Set offset time
     *                   2. Set changed count
     *                   3. Flush layout
     * expected: Scroll to the bottom edge
     */
    int32_t offsetTime = OFFSET_TIME_007;
    for (int i = 0; i < TIME_CHANGED_COUNTS_007; i++) {
        pattern_->fixedVelocityMotion_->OnTimestampChanged(offsetTime, 0.0f, false);
        offsetTime = offsetTime + OFFSET_TIME_007;
        FlushLayoutTask(frameNode_);
    }
    EXPECT_TRUE(pattern_->IsAtBottom());

    /**
     * @tc.steps: step6. Scroll to the top edge
     * expected: 1.Fixed Verify is is non-zero.
     *           2.The current Velocity is equal to the set fixed velocity
     */
    controller->ScrollToEdge(ScrollEdgeType::SCROLL_TOP, SCROLL_FIXED_VELOCITY_007);
    EXPECT_TRUE(pattern_->fixedVelocityMotion_);
    EXPECT_EQ(pattern_->fixedVelocityMotion_->GetCurrentVelocity(), SCROLL_FIXED_VELOCITY_007);

    /**
     * @tc.steps: step7. 1. Set offset time
     *                   2. Set changed count
     *                   3. Flush layout
     * expected: Scroll to the top edge
     */
    offsetTime = OFFSET_TIME_007;
    for (int i = 0; i < TIME_CHANGED_COUNTS_007; i++) {
        pattern_->fixedVelocityMotion_->OnTimestampChanged(offsetTime, 0.0f, false);
        offsetTime = offsetTime + OFFSET_TIME_007;
        FlushLayoutTask(frameNode_);
    }
    EXPECT_TRUE(pattern_->IsAtTop());

    /**
     * @tc.steps: step8. Test GetScrollDirection func.
     * @tc.expected: The scrolling direction is landscape
     */
    EXPECT_EQ(controller->GetScrollDirection(), Axis::VERTICAL);
}

namespace {
constexpr float SCROLL_FIXED_VELOCITY_008 = 300.f;
constexpr float OFFSET_TIME_008 = 100.f;
constexpr int32_t TIME_CHANGED_COUNTS_008 = 20;
} // namespace
/**
 * @tc.name: PositionController008
 * @tc.desc: Test positionController func with AnimateTo
 */
HWTEST_F(GridScrollerTestNg, PositionController008, TestSize.Level1)
{
    bool isTrigger = false;
    /**
     * @tc.steps: step1. Create Grid Item
     */
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    CreateFixedItems(10);
    CreateDone(frameNode_);

    /**
     * @tc.steps: step2. Scroll to the left edge
     * expected: Fixed Verify is is 0.
     */
    auto controller = pattern_->positionController_;
    controller->ScrollToEdge(ScrollEdgeType::SCROLL_LEFT, SCROLL_FIXED_VELOCITY_008);
    EXPECT_FALSE(pattern_->fixedVelocityMotion_);

    /**
     * @tc.steps: step3. Scroll to the right edge
     * expected: Fixed Verify is is 0.
     */
    controller->ScrollToEdge(ScrollEdgeType::SCROLL_RIGHT, SCROLL_FIXED_VELOCITY_008);
    EXPECT_FALSE(pattern_->fixedVelocityMotion_);

    /**
     * @tc.steps: step4. Scroll to the bottom edge
     * expected: 1.Fixed Verify is is non-zero.
     *           2.The current Velocity is equal to the set fixed velocity
     */
    controller->ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, SCROLL_FIXED_VELOCITY_008);
    EXPECT_TRUE(pattern_->fixedVelocityMotion_);
    EXPECT_EQ(pattern_->fixedVelocityMotion_->GetCurrentVelocity(), -SCROLL_FIXED_VELOCITY_008);

    /**
     * @tc.steps: step5. 1. Set offset time
     *                   2. Set changed count
     *                   3. Flush layout
     * expected: Scroll to the bottom edge
     */
    int32_t offsetTime = OFFSET_TIME_008;
    for (int i = 0; i < TIME_CHANGED_COUNTS_008; i++) {
        pattern_->fixedVelocityMotion_->OnTimestampChanged(offsetTime, 0.0f, false);
        offsetTime = offsetTime + OFFSET_TIME_008;
        FlushLayoutTask(frameNode_);
    }
    EXPECT_TRUE(pattern_->IsAtBottom());

    /**
     * @tc.steps: step6. Scroll to the top edge
     * expected: 1.Fixed Verify is is non-zero.
     *           2.The current Velocity is equal to the set fixed velocity
     */
    controller->ScrollToEdge(ScrollEdgeType::SCROLL_TOP, SCROLL_FIXED_VELOCITY_008);
    EXPECT_TRUE(pattern_->fixedVelocityMotion_);
    EXPECT_EQ(pattern_->fixedVelocityMotion_->GetCurrentVelocity(), SCROLL_FIXED_VELOCITY_008);

    /**
     * @tc.steps: step7. 1. Set offset time
     *                   2. Set changed count
     *                   3. Flush layout
     * expected: Scroll to the top edge
     */
    offsetTime = OFFSET_TIME_008;
    for (int i = 0; i < TIME_CHANGED_COUNTS_008; i++) {
        pattern_->fixedVelocityMotion_->OnTimestampChanged(offsetTime, 0.0f, false);
        offsetTime = offsetTime + OFFSET_TIME_008;
        FlushLayoutTask(frameNode_);
    }
    EXPECT_TRUE(pattern_->IsAtTop());

    /**
     * @tc.steps: step8. When Animation is running, call AnimateTo
     * @tc.expected: onScrollStart event will not be triggered
     */
    isTrigger = false;             // reset val
    pattern_->scrollAbort_ = true; // set running
    pattern_->AnimateTo(ITEM_HEIGHT * 2, 200.f, Curves::LINEAR, true);
    EXPECT_FALSE(isTrigger);
}

namespace {
constexpr float SCROLL_FIXED_VELOCITY_009 = 400.f;
constexpr float OFFSET_TIME_009 = 100.f;
constexpr int32_t TIME_CHANGED_COUNTS_009 = 20;
} // namespace
/**
 * @tc.name: PositionController009
 * @tc.desc: Test positionController with AnimateTo
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollerTestNg, PositionController009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Grid Item
     */
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    CreateFixedItems(10);
    CreateDone(frameNode_);

    /**
     * @tc.steps: step2. Scroll to the left edge
     * expected: Fixed Verify is is 0.
     */
    auto controller = pattern_->positionController_;
    controller->ScrollToEdge(ScrollEdgeType::SCROLL_LEFT, SCROLL_FIXED_VELOCITY_009);
    EXPECT_FALSE(pattern_->fixedVelocityMotion_);

    /**
     * @tc.steps: step3. Scroll to the right edge
     * expected: Fixed Verify is is 0.
     */
    controller->ScrollToEdge(ScrollEdgeType::SCROLL_RIGHT, SCROLL_FIXED_VELOCITY_009);
    EXPECT_FALSE(pattern_->fixedVelocityMotion_);

    /**
     * @tc.steps: step4. Scroll to the bottom edge
     * expected: 1.Fixed Verify is is non-zero.
     *           2.The current Velocity is equal to the set fixed velocity
     */
    controller->ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, SCROLL_FIXED_VELOCITY_009);
    EXPECT_TRUE(pattern_->fixedVelocityMotion_);
    EXPECT_EQ(pattern_->fixedVelocityMotion_->GetCurrentVelocity(), -SCROLL_FIXED_VELOCITY_009);

    /**
     * @tc.steps: step5. 1. Set offset time
     *                   2. Set changed count
     *                   3. Flush layout
     * expected: Scroll to the bottom edge
     */
    int32_t offsetTime = OFFSET_TIME_009;
    for (int i = 0; i < TIME_CHANGED_COUNTS_009; i++) {
        pattern_->fixedVelocityMotion_->OnTimestampChanged(offsetTime, 0.0f, false);
        offsetTime = offsetTime + OFFSET_TIME_009;
        FlushLayoutTask(frameNode_);
    }
    EXPECT_TRUE(pattern_->IsAtBottom());

    /**
     * @tc.steps: step6. Scroll to the top edge
     * expected: 1.Fixed Verify is is non-zero.
     *           2.The current Velocity is equal to the set fixed velocity
     */
    controller->ScrollToEdge(ScrollEdgeType::SCROLL_TOP, SCROLL_FIXED_VELOCITY_009);
    EXPECT_TRUE(pattern_->fixedVelocityMotion_);
    EXPECT_EQ(pattern_->fixedVelocityMotion_->GetCurrentVelocity(), SCROLL_FIXED_VELOCITY_009);

    /**
     * @tc.steps: step7. 1. Set offset time
     *                   2. Set changed count
     *                   3. Flush layout
     * expected: Scroll to the top edge
     */
    offsetTime = OFFSET_TIME_009;
    for (int i = 0; i < TIME_CHANGED_COUNTS_009; i++) {
        pattern_->fixedVelocityMotion_->OnTimestampChanged(offsetTime, 0.0f, false);
        offsetTime = offsetTime + OFFSET_TIME_009;
        FlushLayoutTask(frameNode_);
    }
    EXPECT_TRUE(pattern_->IsAtTop());

    /**
     * @tc.steps: step8. Test AnimateTo function
     * @tc.expected: pattern_->isAnimationStop_ is false
     */
    pattern_->AnimateTo(1.5, 1.f, Curves::LINEAR, false);
    EXPECT_FALSE(pattern_->isAnimationStop_);
}

namespace {
constexpr float SCROLL_FIXED_VELOCITY_010 = 500.f;
constexpr float OFFSET_TIME_010 = 100.f;
constexpr int32_t TIME_CHANGED_COUNTS_010 = 20;
} // namespace
/**
 * @tc.name: PositionController010
 * @tc.desc: Test positionController func with ScrollToIndex
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollerTestNg, PositionController010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Grid Item
     */
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    CreateFixedItems(10);
    CreateDone(frameNode_);

    /**
     * @tc.steps: step2. Scroll to the left edge
     * expected: Fixed Verify is is 0.
     */
    auto controller = pattern_->positionController_;
    controller->ScrollToEdge(ScrollEdgeType::SCROLL_LEFT, SCROLL_FIXED_VELOCITY_010);
    EXPECT_FALSE(pattern_->fixedVelocityMotion_);

    /**
     * @tc.steps: step3. Scroll to the right edge
     * expected: Fixed Verify is is 0.
     */
    controller->ScrollToEdge(ScrollEdgeType::SCROLL_RIGHT, SCROLL_FIXED_VELOCITY_010);
    EXPECT_FALSE(pattern_->fixedVelocityMotion_);

    /**
     * @tc.steps: step4. Scroll to the bottom edge
     * expected: 1.Fixed Verify is is non-zero.
     *           2.The current Velocity is equal to the set fixed velocity
     */
    controller->ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, SCROLL_FIXED_VELOCITY_010);
    EXPECT_TRUE(pattern_->fixedVelocityMotion_);
    EXPECT_EQ(pattern_->fixedVelocityMotion_->GetCurrentVelocity(), -SCROLL_FIXED_VELOCITY_010);

    /**
     * @tc.steps: step5. 1. Set offset time
     *                   2. Set changed count
     *                   3. Flush layout
     * expected: Scroll to the bottom edge
     */
    int32_t offsetTime = OFFSET_TIME_010;
    for (int i = 0; i < TIME_CHANGED_COUNTS_010; i++) {
        pattern_->fixedVelocityMotion_->OnTimestampChanged(offsetTime, 0.0f, false);
        offsetTime = offsetTime + OFFSET_TIME_010;
        FlushLayoutTask(frameNode_);
    }
    EXPECT_TRUE(pattern_->IsAtBottom());

    /**
     * @tc.steps: step6. Scroll to the top edge
     * expected: 1.Fixed Verify is is non-zero.
     *           2.The current Velocity is equal to the set fixed velocity
     */
    controller->ScrollToEdge(ScrollEdgeType::SCROLL_TOP, SCROLL_FIXED_VELOCITY_010);
    EXPECT_TRUE(pattern_->fixedVelocityMotion_);
    EXPECT_EQ(pattern_->fixedVelocityMotion_->GetCurrentVelocity(), SCROLL_FIXED_VELOCITY_010);

    /**
     * @tc.steps: step7. 1. Set offset time
     *                   2. Set changed count
     *                   3. Flush layout
     * expected: Scroll to the top edge
     */
    offsetTime = OFFSET_TIME_010;
    for (int i = 0; i < TIME_CHANGED_COUNTS_010; i++) {
        pattern_->fixedVelocityMotion_->OnTimestampChanged(offsetTime, 0.0f, false);
        offsetTime = offsetTime + OFFSET_TIME_010;
        FlushLayoutTask(frameNode_);
    }
    EXPECT_TRUE(pattern_->IsAtTop());

    /**
     * @tc.steps: step7. Set scroll index
     * expected: finalPosition_ is is 0.
     */
    int32_t targetIndex = 0;
    ScrollAlign align = ScrollAlign::START;
    targetIndex = 0;
    pattern_->ScrollToIndex(targetIndex, true, align);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->finalPosition_, 0.0f);
}

/**
 * @tc.name: ScrollToFocusNodeIndex001
 * @tc.desc: Test ScrollToFocusNodeIndex
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollerTestNg, ScrollToFocusNodeIndex001, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    CreateFocusableGridItems(10, ITEM_WIDTH, ITEM_HEIGHT);
    CreateDone(frameNode_);

    /**
     * @tc.steps: step1. Focus node outside the viewport
     * @tc.expected: scroll to the node
     */
    int32_t focusNodeIndex = 6;
    pattern_->ScrollToFocusNodeIndex(focusNodeIndex);
    FlushLayoutTask(frameNode_);
    RefPtr<FocusHub> focusNode = GetChildFocusHub(frameNode_, focusNodeIndex);
    EXPECT_TRUE(focusNode->IsCurrentFocus());
    EXPECT_EQ(pattern_->GetGridLayoutInfo().currentOffset_, 0);

    /**
     * @tc.steps: step2. Focus node index not exist
     * @tc.expected: do nothing
     */
    focusNodeIndex = 10;
    pattern_->ScrollToFocusNodeIndex(focusNodeIndex);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetGridLayoutInfo().currentOffset_, 0);
}

/**
 * @tc.name: ScrollToNode001
 * @tc.desc: Test ScrollToNode
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollerTestNg, ScrollToNode001, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    CreateFixedItems(10);
    CreateDone(frameNode_);

    /**
     * @tc.steps: step1. Focus node outside the viewport
     * @tc.expected: scroll to the node
     */
    int32_t focusNodeIndex = 6;
    RefPtr<FrameNode> focusNode = GetChildFrameNode(frameNode_, focusNodeIndex);
    pattern_->ScrollToNode(focusNode);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetGridLayoutInfo().currentOffset_, 0);
}

/**
 * @tc.name: GetOverScrollOffset001
 * @tc.desc: Test GetOverScrollOffset
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollerTestNg, GetOverScrollOffset001, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    CreateFixedItems(10);
    CreateDone(frameNode_);

    OverScrollOffset offset = pattern_->GetOverScrollOffset(ITEM_HEIGHT);
    OverScrollOffset expectOffset = { ITEM_HEIGHT, 0 };
    EXPECT_TRUE(IsEqual(offset, expectOffset));
    offset = pattern_->GetOverScrollOffset(0.f);
    expectOffset = { 0, 0 };
    EXPECT_TRUE(IsEqual(offset, expectOffset));
    offset = pattern_->GetOverScrollOffset(-ITEM_HEIGHT);
    expectOffset = { 0, 0 };
    EXPECT_TRUE(IsEqual(offset, expectOffset));

    pattern_->info_.currentOffset_ = -ITEM_HEIGHT;
    offset = pattern_->GetOverScrollOffset(ITEM_HEIGHT * 2);
    expectOffset = { ITEM_HEIGHT, 0 };
    EXPECT_TRUE(IsEqual(offset, expectOffset));
    offset = pattern_->GetOverScrollOffset(0.f);
    expectOffset = { 0, 0 };
    EXPECT_TRUE(IsEqual(offset, expectOffset));
    offset = pattern_->GetOverScrollOffset(-ITEM_HEIGHT * 2);
    expectOffset = { 0, 0 };
    EXPECT_TRUE(IsEqual(offset, expectOffset));

    pattern_->info_.currentOffset_ = -ITEM_HEIGHT * 2;
    offset = pattern_->GetOverScrollOffset(ITEM_HEIGHT);
    expectOffset = { 0, 0 };
    EXPECT_TRUE(IsEqual(offset, expectOffset));
    offset = pattern_->GetOverScrollOffset(0.f);
    expectOffset = { 0, 0 };
    EXPECT_TRUE(IsEqual(offset, expectOffset));
    offset = pattern_->GetOverScrollOffset(-ITEM_HEIGHT);
    expectOffset = { 0, 0 };
    EXPECT_TRUE(IsEqual(offset, expectOffset));

    pattern_->info_.currentOffset_ = ITEM_HEIGHT;
    offset = pattern_->GetOverScrollOffset(ITEM_HEIGHT);
    expectOffset = { ITEM_HEIGHT, 0 };
    EXPECT_TRUE(IsEqual(offset, expectOffset));
    offset = pattern_->GetOverScrollOffset(0.f);
    expectOffset = { 0, 0 };
    EXPECT_TRUE(IsEqual(offset, expectOffset));
    offset = pattern_->GetOverScrollOffset(-ITEM_HEIGHT * 2);
    expectOffset = { -ITEM_HEIGHT, 0 };
    EXPECT_TRUE(IsEqual(offset, expectOffset));

    pattern_->info_.currentOffset_ = -ITEM_HEIGHT * 3;
    offset = pattern_->GetOverScrollOffset(ITEM_HEIGHT * 2);
    expectOffset = { 0, 0 };
    EXPECT_TRUE(IsEqual(offset, expectOffset));
    offset = pattern_->GetOverScrollOffset(0.f);
    expectOffset = { 0, 0 };
    EXPECT_TRUE(IsEqual(offset, expectOffset));
    offset = pattern_->GetOverScrollOffset(-ITEM_HEIGHT);
    expectOffset = { 0, 0 };
    EXPECT_TRUE(IsEqual(offset, expectOffset));
}

/**
 * @tc.name: GetOverScrollOffset002
 * @tc.desc: Test GetOverScrollOffset
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollerTestNg, GetOverScrollOffset002, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    CreateFixedItems(8);
    CreateDone(frameNode_);

    OverScrollOffset offset = pattern_->GetOverScrollOffset(ITEM_HEIGHT);
    OverScrollOffset expectOffset = { ITEM_HEIGHT, 0 };
    EXPECT_TRUE(IsEqual(offset, expectOffset));
    offset = pattern_->GetOverScrollOffset(0.f);
    expectOffset = { 0, 0 };
    EXPECT_TRUE(IsEqual(offset, expectOffset));
    offset = pattern_->GetOverScrollOffset(-ITEM_HEIGHT);
    expectOffset = { 0, -ITEM_HEIGHT };
    EXPECT_TRUE(IsEqual(offset, expectOffset));

    pattern_->info_.currentOffset_ = -ITEM_HEIGHT;
    offset = pattern_->GetOverScrollOffset(ITEM_HEIGHT * 2);
    expectOffset = { ITEM_HEIGHT, ITEM_HEIGHT };
    EXPECT_TRUE(IsEqual(offset, expectOffset));
    offset = pattern_->GetOverScrollOffset(0.f);
    expectOffset = { 0, 0 };
    EXPECT_TRUE(IsEqual(offset, expectOffset));
    offset = pattern_->GetOverScrollOffset(-ITEM_HEIGHT * 2);
    expectOffset = { 0, -ITEM_HEIGHT * 2 };
    EXPECT_TRUE(IsEqual(offset, expectOffset));

    pattern_->info_.currentOffset_ = -ITEM_HEIGHT * 2;
    offset = pattern_->GetOverScrollOffset(ITEM_HEIGHT);
    expectOffset = { 0, ITEM_HEIGHT };
    EXPECT_TRUE(IsEqual(offset, expectOffset));
    offset = pattern_->GetOverScrollOffset(0.f);
    expectOffset = { 0, 0 };
    EXPECT_TRUE(IsEqual(offset, expectOffset));
    offset = pattern_->GetOverScrollOffset(-ITEM_HEIGHT);
    expectOffset = { 0, -ITEM_HEIGHT };
    EXPECT_TRUE(IsEqual(offset, expectOffset));

    pattern_->info_.currentOffset_ = ITEM_HEIGHT;
    offset = pattern_->GetOverScrollOffset(ITEM_HEIGHT);
    expectOffset = { ITEM_HEIGHT, 0 };
    EXPECT_TRUE(IsEqual(offset, expectOffset));
    offset = pattern_->GetOverScrollOffset(0.f);
    expectOffset = { 0, 0 };
    EXPECT_TRUE(IsEqual(offset, expectOffset));
    offset = pattern_->GetOverScrollOffset(-ITEM_HEIGHT * 2);
    expectOffset = { -ITEM_HEIGHT, -ITEM_HEIGHT };
    EXPECT_TRUE(IsEqual(offset, expectOffset));

    pattern_->info_.currentOffset_ = -ITEM_HEIGHT * 3;
    offset = pattern_->GetOverScrollOffset(ITEM_HEIGHT * 2);
    expectOffset = { 0, ITEM_HEIGHT * 2 };
    EXPECT_TRUE(IsEqual(offset, expectOffset));
    offset = pattern_->GetOverScrollOffset(0.f);
    expectOffset = { 0, 0 };
    EXPECT_TRUE(IsEqual(offset, expectOffset));
    offset = pattern_->GetOverScrollOffset(-ITEM_HEIGHT);
    expectOffset = { 0, -ITEM_HEIGHT };
    EXPECT_TRUE(IsEqual(offset, expectOffset));
}

/**
 * @tc.name: UpdateCurrentOffset001
 * @tc.desc: Test grid pattern UpdateCurrentOffset function
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollerTestNg, UpdateCurrentOffset001, TestSize.Level1)
{
    /**
     * @tc.cases: Test SCROLL_FROM_UPDATE
     */
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    CreateFixedItems(10);
    CreateDone(frameNode_);
    UpdateCurrentOffset(-100.f, SCROLL_FROM_UPDATE);
    EXPECT_EQ(pattern_->GetGridLayoutInfo().currentOffset_, -100.f);
    UpdateCurrentOffset(100.f, SCROLL_FROM_UPDATE);
    EXPECT_EQ(pattern_->GetGridLayoutInfo().currentOffset_, 0);
    UpdateCurrentOffset(-200.f, SCROLL_FROM_UPDATE);
    EXPECT_EQ(pattern_->GetGridLayoutInfo().currentOffset_, 0.f);
}

/**
 * @tc.name: UpdateCurrentOffset002
 * @tc.desc: Test grid pattern UpdateCurrentOffset function
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollerTestNg, UpdateCurrentOffset002, TestSize.Level1)
{
    /**
     * @tc.cases: Test SCROLL_FROM_BAR
     */
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    CreateFixedItems(10);
    CreateDone(frameNode_);
    UpdateCurrentOffset(-100.f, SCROLL_FROM_BAR);
    EXPECT_EQ(pattern_->GetGridLayoutInfo().currentOffset_, -100.f);
    UpdateCurrentOffset(100.f, SCROLL_FROM_BAR);
    EXPECT_EQ(pattern_->GetGridLayoutInfo().currentOffset_, 0);
    UpdateCurrentOffset(-200.f, SCROLL_FROM_BAR);
    EXPECT_EQ(pattern_->GetGridLayoutInfo().currentOffset_, 0.f);
}

/**
 * @tc.name: UpdateCurrentOffset003
 * @tc.desc: Test grid pattern UpdateCurrentOffset function
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollerTestNg, UpdateCurrentOffset003, TestSize.Level1)
{
    /**
     * @tc.cases: Test SCROLL_FROM_UPDATE and EdgeEffect::FADE
     */
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    CreateFixedItems(10);
    CreateDone(frameNode_);
    pattern_->scrollEffect_ = AceType::MakeRefPtr<ScrollEdgeEffect>(EdgeEffect::FADE);
    UpdateCurrentOffset(-100.f, SCROLL_FROM_UPDATE);
    EXPECT_EQ(pattern_->GetGridLayoutInfo().currentOffset_, -100.f);
    UpdateCurrentOffset(100.f, SCROLL_FROM_UPDATE);
    EXPECT_EQ(pattern_->GetGridLayoutInfo().currentOffset_, 0);
    UpdateCurrentOffset(-200.f, SCROLL_FROM_UPDATE);
    EXPECT_EQ(pattern_->GetGridLayoutInfo().currentOffset_, 0.f);
}

/**
 * @tc.name: UpdateCurrentOffset004
 * @tc.desc: Test grid pattern UpdateCurrentOffset function
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollerTestNg, UpdateCurrentOffset004, TestSize.Level1)
{
    /**
     * @tc.cases: When isConfigScrollable_ is false
     * @tc.expected: Can not roll
     */
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr 1fr");
    model.SetRowsTemplate("1fr 1fr");
    CreateFixedItems(10);
    CreateDone(frameNode_);
    EXPECT_FALSE(pattern_->isConfigScrollable_);

    UpdateCurrentOffset(-100.f, SCROLL_FROM_UPDATE);
    EXPECT_EQ(pattern_->GetGridLayoutInfo().currentOffset_, 0.f);
}

/**
 * @tc.name: ScrollBy
 * @tc.desc: Test ScrollBy
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollerTestNg, ScrollBy001, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    CreateFixedItems(10);
    CreateDone(frameNode_);

    /**
     * @tc.steps: step1. ScrollBy information function call
     * @tc.expected: scroll to the node
     */
    pattern_->ScrollBy(1.2);
    EXPECT_TRUE(pattern_->UpdateCurrentOffset(-1.2, 3));
    pattern_->OnAnimateStop();
    EXPECT_TRUE(pattern_->scrollStop_);

    pattern_->OutBoundaryCallback();
    EXPECT_FALSE(pattern_->IsOutOfBoundary(true));

    /**
     * @tc.steps: step3. Test AnimateTo function
     * @tc.expected: pattern_->isAnimationStop_ is false
     */
    pattern_->AnimateTo(1.5, 1.f, Curves::LINEAR, false);
    EXPECT_FALSE(pattern_->isAnimationStop_);
}

/**
 * @tc.name: GetGridItemAnimatePos001
 * @tc.desc: Test GetGridItemAnimatePos
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollerTestNg, GetGridItemAnimatePos001, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    CreateGridItems(20, ITEM_WIDTH, NULL_VALUE, GridItemStyle::NONE);
    CreateDone(frameNode_);

    int32_t targetIndex = 15;
    ScrollAlign align = ScrollAlign::START;
    pattern_->ScrollToIndex(targetIndex, true, align);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->finalPosition_, 0.0f);
}

/**
 * @tc.name: GetGridItemAnimatePos002
 * @tc.desc: Test GetGridItemAnimatePos
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollerTestNg, GetGridItemAnimatePos002, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    CreateGridItems(20, ITEM_WIDTH, NULL_VALUE, GridItemStyle::NONE);
    CreateDone(frameNode_);

    int32_t targetIndex = 15;
    ScrollAlign align = ScrollAlign::CENTER;

    pattern_->ScrollToIndex(targetIndex, true, align);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->finalPosition_, -400.0f);
}

/**
 * @tc.name: GetGridItemAnimatePos003
 * @tc.desc: Test GetGridItemAnimatePos
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollerTestNg, GetGridItemAnimatePos003, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    CreateGridItems(20, ITEM_WIDTH, NULL_VALUE, GridItemStyle::NONE);
    CreateDone(frameNode_);

    int32_t targetIndex = 15;
    ScrollAlign align = ScrollAlign::END;

    pattern_->ScrollToIndex(targetIndex, true, align);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->finalPosition_, -800.0f);
}

/**
 * @tc.name: GetGridItemAnimatePos004
 * @tc.desc: Test GetGridItemAnimatePos
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollerTestNg, GetGridItemAnimatePos004, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    CreateFixedItems(20);
    CreateDone(frameNode_);

    pattern_->ScrollToIndex(10, true, ScrollAlign::AUTO);
    AceType::DynamicCast<LayoutAlgorithmWrapper>(frameNode_->GetLayoutAlgorithm());

    int32_t targetIndex = 10;
    ScrollAlign align = ScrollAlign::AUTO;

    pattern_->ScrollToIndex(targetIndex, true, align);
    FlushLayoutTask(frameNode_);

    targetIndex = 0;
    pattern_->ScrollToIndex(targetIndex, true, align);
    FlushLayoutTask(frameNode_);

    targetIndex = 10;
    pattern_->ScrollToIndex(targetIndex, true, align);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->finalPosition_, 400.0f);
}

/**
 * @tc.name: GetGridItemAnimatePos005
 * @tc.desc: Test GetGridItemAnimatePos
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollerTestNg, GetGridItemAnimatePos005, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    CreateGridItems(20, ITEM_WIDTH, NULL_VALUE, GridItemStyle::NONE);
    CreateDone(frameNode_);

    int32_t targetIndex = 10;
    ScrollAlign align = ScrollAlign::AUTO;
    pattern_->ScrollToIndex(targetIndex, true, align);
    FlushLayoutTask(frameNode_);

    targetIndex = 15;
    pattern_->ScrollToIndex(targetIndex, true, align);
    FlushLayoutTask(frameNode_);

    targetIndex = 0;
    pattern_->ScrollToIndex(targetIndex, true, align);
    FlushLayoutTask(frameNode_);

    targetIndex = 300;
    pattern_->ScrollToIndex(targetIndex, true, align);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->finalPosition_, 0.0f);
}

/**
 * @tc.name: GetGridItemAnimatePos006
 * @tc.desc: Test GetGridItemAnimatePos
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollerTestNg, GetGridItemAnimatePos006, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr");
    CreateFixedItems(1);
    CreateDone(frameNode_);

    int32_t targetIndex = 0;
    ScrollAlign align = ScrollAlign::START;
    targetIndex = 0;
    pattern_->ScrollToIndex(targetIndex, true, align);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->finalPosition_, 0.0f);
}

/**
 * @tc.name: GetGridItemAnimatePos007
 * @tc.desc: Test GetGridItemAnimatePos
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollerTestNg, GetGridItemAnimatePos007, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    CreateGridItems(20, ITEM_WIDTH, NULL_VALUE, GridItemStyle::NONE);
    CreateDone(frameNode_);

    int32_t targetIndex = 10;
    ScrollAlign align = ScrollAlign::AUTO;
    pattern_->ScrollToIndex(targetIndex, true, align);
    FlushLayoutTask(frameNode_);

    targetIndex = 15;
    pattern_->ScrollToIndex(targetIndex, true, align);
    FlushLayoutTask(frameNode_);

    targetIndex = 10;
    pattern_->ScrollToIndex(targetIndex, true, align);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->finalPosition_, 0.0f);
}

namespace {
const decltype(GridLayoutInfo::lineHeightMap_) cmp = { { 0, ITEM_HEIGHT }, { 1, ITEM_HEIGHT }, { 2, ITEM_HEIGHT },
    { 3, ITEM_HEIGHT }, { 6, ITEM_HEIGHT }, { 7, ITEM_HEIGHT }, { 8, ITEM_HEIGHT }, { 9, ITEM_HEIGHT } };
}
/**
 * @tc.name: GetEndOffset000
 * @tc.desc: Test scrolling past limits
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollerTestNg, GetEndOffset000, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetLayoutOptions({});
    CreateFixedItems(20, GridItemStyle::NONE);
    CreateDone(frameNode_);

    int32_t targetIndex = 19;
    ScrollAlign align = ScrollAlign::AUTO;
    pattern_->ScrollToIndex(targetIndex, false, align);
    FlushLayoutTask(frameNode_);
    auto& info = pattern_->info_;
    EXPECT_EQ(info.startMainLineIndex_, 6);
    EXPECT_EQ(info.endMainLineIndex_, 9);
    pattern_->SetEdgeEffect(EdgeEffect::SPRING);
    pattern_->scrollableEvent_->scrollable_->isTouching_ = true;
    for (int i = 0; i < 500; ++i) {
        UpdateCurrentOffset(-200.0f);
    }
    if (SystemProperties::GetGridIrregularLayoutEnabled()) {
        EXPECT_EQ(info.startMainLineIndex_, 9);
    } else {
        EXPECT_EQ(info.startMainLineIndex_, 10);
    }
    EXPECT_EQ(info.endMainLineIndex_, 9);

    EXPECT_LT(info.currentOffset_, -150.0f);

    pattern_->ScrollToIndex(targetIndex, false, ScrollAlign::END);
    FlushLayoutTask(frameNode_);
    for (int i = 0; i < 10; ++i) {
        info.currentOffset_ -= 150.0f;
        frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
        FlushLayoutTask(frameNode_);
    }
    if (SystemProperties::GetGridIrregularLayoutEnabled()) {
        EXPECT_EQ(info.startMainLineIndex_, 9);
    } else {
        EXPECT_EQ(info.startMainLineIndex_, 10);
    }
    EXPECT_EQ(info.endMainLineIndex_, 9);

    EXPECT_LT(info.currentOffset_, -150.0f);
}

/**
 * @tc.name: GetEndOffset001
 * @tc.desc: Test GetEndOffset with updated offset on old layout
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollerTestNg, GetEndOffset001, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    CreateFixedItems(20, GridItemStyle::NONE);
    CreateDone(frameNode_);

    int32_t targetIndex = 19;
    ScrollAlign align = ScrollAlign::AUTO;
    pattern_->ScrollToIndex(targetIndex, false, align);
    FlushLayoutTask(frameNode_);
    auto& info = pattern_->info_;
    info.prevOffset_ = info.currentOffset_;
    info.currentOffset_ -= 1000.0f;
    info.synced_ = false;
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    pattern_->SetEdgeEffect(EdgeEffect::SPRING);
    pattern_->scrollableEvent_->scrollable_->isTouching_ = true;
    pattern_->GetScrollEdgeEffect()->ProcessScrollOver(-2000.0f);
    EXPECT_TRUE(info.synced_);
    // overScroll disabled to avoid layout bug
    EXPECT_EQ(info.currentOffset_, info.prevOffset_);
    EXPECT_EQ(info.startIndex_, 12);
    EXPECT_EQ(info.endIndex_, 19);
    EXPECT_EQ(info.startMainLineIndex_, 6);
    EXPECT_EQ(info.endMainLineIndex_, 9);
    EXPECT_EQ(pattern_->GetEndOffset(), 0.0f);
}

/**
 * @tc.name: MultiLineItemScroll001
 * @tc.desc: Test multiLine item in last line scroll end
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollerTestNg, MultiLineItemScroll001, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    CreateFixedItems(6, GridItemStyle::NONE);
    CreateBigItem(0, 1, 0, 1, 2 * ITEM_WIDTH, 2 * ITEM_HEIGHT);
    CreateDone(frameNode_);

    pattern_->ScrollBy(-10);
    FlushLayoutTask(frameNode_);
    auto& info = pattern_->info_;
    EXPECT_TRUE(info.reachEnd_);
    EXPECT_FALSE(info.offsetEnd_);
}

/**
 * @tc.name: VerticalGridScrollToIndexWithLargeLineHeight001
 * @tc.desc: Test Grid(Axis::VERTICAL) ScrollToIndex With line height Greater than main size Item
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollerTestNg, VerticalGridScrollToIndexWithLargeLineHeight001, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr");
    model.SetRowsGap(Dimension(10));
    CreateGridItem(ITEM_WIDTH, 1350);
    ViewStackProcessor::GetInstance()->Pop();
    ViewStackProcessor::GetInstance()->StopGetAccessRecording();
    CreateGridItems(20, ITEM_WIDTH, 390);
    CreateDone(frameNode_);

    // cache all line in Grid
    auto controller = pattern_->positionController_;
    controller->ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, true);
    FlushLayoutTask(frameNode_);
    controller->ScrollToEdge(ScrollEdgeType::SCROLL_TOP, false);
    FlushLayoutTask(frameNode_);

    controller->ScrollToIndex(5, false, ScrollAlign::AUTO, std::nullopt);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetGridLayoutInfo().currentOffset_, -950.0f);

    controller->ScrollToEdge(ScrollEdgeType::SCROLL_TOP, true);
    FlushLayoutTask(frameNode_);

    controller->ScrollToIndex(7, false, ScrollAlign::AUTO, std::nullopt);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetGridLayoutInfo().currentOffset_, -1350.0f);

    controller->ScrollToEdge(ScrollEdgeType::SCROLL_TOP, true);
    FlushLayoutTask(frameNode_);

    controller->ScrollToIndex(9, false, ScrollAlign::AUTO, std::nullopt);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetGridLayoutInfo().currentOffset_, -390.0f);
}

/**
 * @tc.name: VerticalGridScrollToIndexWithLargeLineHeight002
 * @tc.desc: Test Grid(Axis::VERTICAL) ScrollToIndex With line height Greater than main size Item
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollerTestNg, VerticalGridScrollToIndexWithLargeLineHeight002, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr");
    model.SetRowsGap(Dimension(10));
    CreateGridItems(3, ITEM_WIDTH, 250);

    CreateGridItem(ITEM_WIDTH, 1350);
    ViewStackProcessor::GetInstance()->Pop();
    ViewStackProcessor::GetInstance()->StopGetAccessRecording();

    CreateGridItems(20, ITEM_WIDTH, 390);
    CreateDone(frameNode_);

    // cache all line in Grid
    auto controller = pattern_->positionController_;
    controller->ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, true);
    FlushLayoutTask(frameNode_);
    controller->ScrollToEdge(ScrollEdgeType::SCROLL_TOP, false);
    FlushLayoutTask(frameNode_);

    controller->ScrollToIndex(5, false, ScrollAlign::AUTO, std::nullopt);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetGridLayoutInfo().currentOffset_, -550.0f);

    controller->ScrollToEdge(ScrollEdgeType::SCROLL_TOP, true);
    FlushLayoutTask(frameNode_);

    controller->ScrollToIndex(7, false, ScrollAlign::AUTO, std::nullopt);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetGridLayoutInfo().currentOffset_, -950.0f);

    controller->ScrollToEdge(ScrollEdgeType::SCROLL_TOP, true);
    FlushLayoutTask(frameNode_);

    controller->ScrollToIndex(9, false, ScrollAlign::AUTO, std::nullopt);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetGridLayoutInfo().currentOffset_, -1350.0f);
}
} // namespace OHOS::Ace::NG
