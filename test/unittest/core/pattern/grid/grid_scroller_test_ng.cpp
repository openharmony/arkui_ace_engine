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
#include "test/mock/core/animation/mock_animation_manager.h"

namespace OHOS::Ace::NG {
class GridScrollerTestNg : public GridTestNg, public testing::WithParamInterface<bool> {};

/**
 * @tc.name: ScrollToIndex_Align001
 * @tc.desc: Test ScrollToIndex with ScrollAlign::START
 * @tc.desc: Scroll to (first/inView/outOfView/last) item (with/without) animation
 * @tc.type: FUNC
 */
HWTEST_P(GridScrollerTestNg, ScrollToIndex_Align001, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    CreateFixedItems(20);
    CreateDone();

    // Scroll to the first item
    bool smooth = GetParam();
    ScrollAlign align = ScrollAlign::START;
    ScrollToIndex(0, smooth, align);
    EXPECT_TRUE(TickPosition(0));
    EXPECT_TRUE(pattern_->IsAtTop());

    // Scroll to the first item in row in view
    ScrollToIndex(2, smooth, align);
    EXPECT_TRUE(TickPosition(-100.0f));

    // Scroll to the last item in row in view
    ScrollToIndex(5, smooth, align);
    EXPECT_TRUE(TickPosition(-200.0f));

    // Scroll to the item out of view
    ScrollToIndex(12, smooth, align);
    EXPECT_TRUE(TickPosition(-600.0f));
    EXPECT_TRUE(pattern_->IsAtBottom());

    // Scroll back
    ScrollToIndex(3, smooth, align);
    EXPECT_TRUE(TickPosition(-100.0f));

    // Scroll with invalid index
    ScrollToIndex(-100, smooth, align);
    EXPECT_TRUE(TickPosition(-100.0f));
    ScrollToIndex(100, smooth, align);
    EXPECT_TRUE(TickPosition(-100.0f));

    // Scroll to the last item
    ScrollToIndex(LAST_ITEM, smooth, align);
    if (smooth) {
        EXPECT_TRUE(TickPosition(-100.0f));
        EXPECT_FALSE(pattern_->IsAtBottom());
    } else {
        EXPECT_TRUE(TickPosition(-600.0f));
        EXPECT_TRUE(pattern_->IsAtBottom());
    }
}

/**
 * @tc.name: ScrollToIndex_Align002
 * @tc.desc: Test ScrollToIndex with ScrollAlign::CENTER
 * @tc.desc: Scroll to (first/inView/outOfView/last) item (with/without) animation
 * @tc.type: FUNC
 */
HWTEST_P(GridScrollerTestNg, ScrollToIndex_Align002, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    CreateFixedItems(20);
    CreateDone();

    // Scroll to the first item
    bool smooth = GetParam();
    ScrollAlign align = ScrollAlign::CENTER;
    ScrollToIndex(0, smooth, align);
    EXPECT_TRUE(TickPosition(0));
    EXPECT_TRUE(pattern_->IsAtTop());

    // Scroll to the first item in row in view
    ScrollToIndex(4, smooth, align);
    EXPECT_TRUE(TickPosition(-50.0f));

    // Scroll to the last item in row in view
    ScrollToIndex(7, smooth, align);
    EXPECT_TRUE(TickPosition(-150.0f));

    // Scroll to the item out of view
    ScrollToIndex(12, smooth, align);
    EXPECT_TRUE(TickPosition(-450.0f));

    // Scroll back
    ScrollToIndex(5, smooth, align);
    EXPECT_TRUE(TickPosition(-50.0f));

    // Scroll to the last item
    ScrollToIndex(LAST_ITEM, smooth, align);
    if (smooth) {
        EXPECT_TRUE(TickPosition(-50.0f));
        EXPECT_FALSE(pattern_->IsAtBottom());
    } else {
        EXPECT_TRUE(TickPosition(-600.0f));
        EXPECT_TRUE(pattern_->IsAtBottom());
    }
}

/**
 * @tc.name: ScrollToIndex_Align003
 * @tc.desc: Test ScrollToIndex with ScrollAlign::END
 * @tc.desc: Scroll to (first/inView/outOfView/last) item (with/without) animation
 * @tc.type: FUNC
 */
HWTEST_P(GridScrollerTestNg, ScrollToIndex_Align003, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    CreateFixedItems(20);
    CreateDone();

    // Scroll to the first item
    bool smooth = GetParam();
    ScrollAlign align = ScrollAlign::END;
    ScrollToIndex(0, smooth, align);
    EXPECT_TRUE(TickPosition(0));
    EXPECT_TRUE(pattern_->IsAtTop());

    // Scroll to the first item in row in view
    ScrollToIndex(4, smooth, align);
    EXPECT_TRUE(TickPosition(0));

    // Scroll to the first item in row out of view
    ScrollToIndex(12, smooth, align);
    EXPECT_TRUE(TickPosition(-300.0f));

    // Scroll to the last item in row out of view
    ScrollToIndex(15, smooth, align);
    EXPECT_TRUE(TickPosition(-400.0f));

    // Scroll back
    ScrollToIndex(5, smooth, align);
    EXPECT_TRUE(TickPosition(0));

    // Scroll to the last item
    ScrollToIndex(LAST_ITEM, smooth, align);
    if (smooth) {
        EXPECT_TRUE(TickPosition(0));
        EXPECT_FALSE(pattern_->IsAtBottom());
    } else {
        EXPECT_TRUE(TickPosition(-600.0f));
        EXPECT_TRUE(pattern_->IsAtBottom());
    }
}

/**
 * @tc.name: ScrollToIndex_Align004
 * @tc.desc: Test ScrollToIndex with ScrollAlign::AUTO
 * @tc.desc: Scroll to (first/inView/outOfView/last) item (with/without) animation
 * @tc.type: FUNC
 */
HWTEST_P(GridScrollerTestNg, ScrollToIndex_Align004, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    CreateFixedItems(20);
    CreateDone();

    // Scroll to the first item
    bool smooth = GetParam();
    ScrollAlign align = ScrollAlign::AUTO;
    ScrollToIndex(0, smooth, align);
    EXPECT_TRUE(TickPosition(0));
    EXPECT_TRUE(pattern_->IsAtTop());

    // Scroll to the first item in row in view
    ScrollToIndex(4, smooth, align);
    EXPECT_TRUE(TickPosition(0));

    // Scroll to the first item in row out of view
    ScrollToIndex(12, smooth, align);
    EXPECT_TRUE(TickPosition(-300.0f));

    // Scroll to the last item in row out of view
    ScrollToIndex(15, smooth, align);
    EXPECT_TRUE(TickPosition(-400.0f));

    // Scroll back
    ScrollToIndex(5, smooth, align);
    EXPECT_TRUE(TickPosition(-200.0f));

    // Scroll to the last item
    ScrollToIndex(LAST_ITEM, smooth, align);
    if (smooth) {
        EXPECT_TRUE(TickPosition(-200.0f));
        EXPECT_FALSE(pattern_->IsAtBottom());
    } else {
        EXPECT_TRUE(TickPosition(-600.0f));
        EXPECT_TRUE(pattern_->IsAtBottom());
    }
}

/**
 * @tc.name: ScrollToIndex_Gap001
 * @tc.desc: Test ScrollToIndex with Gap
 * @tc.type: FUNC
 */
HWTEST_P(GridScrollerTestNg, ScrollToIndex_Gap001, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetColumnsGap(Dimension(COL_GAP));
    model.SetRowsGap(Dimension(ROW_GAP));
    CreateFixedItems(20);
    CreateDone();

    // ScrollAlign::START
    bool smooth = GetParam();
    ScrollToIndex(2, smooth, ScrollAlign::START);
    EXPECT_TRUE(TickPosition(-105.0f));

    // ScrollAlign::CENTER
    ScrollToIndex(7, smooth, ScrollAlign::CENTER);
    EXPECT_TRUE(TickPosition(-165.0f));

    // ScrollAlign::END
    ScrollToIndex(12, smooth, ScrollAlign::END);
    EXPECT_TRUE(TickPosition(-330.0f));

    // ScrollAlign::AUTO
    ScrollToIndex(LAST_ITEM, smooth, ScrollAlign::AUTO);
    if (smooth) {
        EXPECT_TRUE(TickPosition(-330.0f));
        EXPECT_FALSE(pattern_->IsAtBottom());
    } else {
        EXPECT_TRUE(TickPosition(-645.0f));
        EXPECT_TRUE(pattern_->IsAtBottom());
    }
}

/**
 * @tc.name: ScrollToIndex_Gap002
 * @tc.desc: Test ScrollToIndex with big gap(lineHeight + gap > mainSize)
 * @tc.type: FUNC
 */
HWTEST_P(GridScrollerTestNg, ScrollToIndex_Gap002, TestSize.Level1)
{
    /**
     * @tc.cases: Set BIG_ROW_GAP, ScrollTo index:5, text ScrollAlign::AUTO
     * @tc.expected: Each test scroll the correct distance
     */
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetRowsGap(Dimension(BIG_ROW_GAP));
    CreateFixedItems(15);
    CreateDone();

    bool smooth = GetParam();
    int32_t index = 5;
    ScrollToIndex(index, smooth, ScrollAlign::AUTO);
    EXPECT_TRUE(TickPosition(-(ITEM_MAIN_SIZE * 3 + BIG_ROW_GAP * 2 - GRID_HEIGHT)));
    /**
     * @tc.cases: use ScrollTo to make item 5 in the last line, ScrollTo index:5, text ScrollAlign::AUTO
     * @tc.expected: scrollToIndex don't change grid offset
     */
    auto autoPosition = ITEM_MAIN_SIZE * 3 + BIG_ROW_GAP * 2 - GRID_HEIGHT + ITEM_MAIN_SIZE;
    ScrollTo(autoPosition);
    ScrollToIndex(index, smooth, ScrollAlign::AUTO);
    EXPECT_TRUE(TickPosition(-autoPosition));
}

/**
 * @tc.name: ScrollToIndex_Gap003
 * @tc.desc: Test ScrollToIndex with big gap(lineHeight + gap > mainSize)
 * @tc.type: FUNC
 */
HWTEST_P(GridScrollerTestNg, ScrollToIndex_Gap003, TestSize.Level1)
{
    /**
     * @tc.cases: Set BIG_ROW_GAP, ScrollTo index, text each ScrollAlign::CENTER
     * @tc.expected: Each test scroll the correct distance
     */
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetRowsGap(Dimension(BIG_ROW_GAP));
    CreateFixedItems(15);
    CreateDone();

    auto endPosition = ITEM_MAIN_SIZE * 3 + BIG_ROW_GAP * 2 - GRID_HEIGHT;
    bool smooth = GetParam();
    ScrollToIndex(5, smooth, ScrollAlign::CENTER);
    EXPECT_TRUE(TickPosition(-(endPosition + (GRID_HEIGHT - ITEM_MAIN_SIZE) / 2)));
}

/**
 * @tc.name: ScrollToIndex_Gap004
 * @tc.desc: Test ScrollToIndex with medium gap(3*lineHeight + 3*gap > mainSize)
 * @tc.type: FUNC
 */
HWTEST_P(GridScrollerTestNg, ScrollToIndex_Gap004, TestSize.Level1)
{
    /**
     * @tc.cases: Set MEDIUM_ROW_GAP and scroll to specified position, ScrollTo index, text each ScrollAlign::AUTO
     * @tc.expected: Each test scroll the correct distance
     */
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetRowsGap(Dimension(MEDIUM_ROW_GAP));
    CreateFixedItems(15);
    CreateDone();

    auto position = ITEM_MAIN_SIZE + 5 * COL_GAP;
    ScrollTo(position);
    EXPECT_TRUE(TickPosition(-position));

    bool smooth = GetParam();
    ScrollToIndex(6, smooth, ScrollAlign::AUTO);
    EXPECT_TRUE(TickPosition(-position));
}

/**
 * @tc.name: ScrollToIndex_Irregular001
 * @tc.desc: Test ScrollToIndex with irregular
 * @tc.desc: The irregularIndexes index take up a whole row
 * @tc.type: FUNC
 */
HWTEST_P(GridScrollerTestNg, ScrollToIndex_Irregular001, TestSize.Level1)
{
    GridLayoutOptions option;
    option.irregularIndexes = { 6, 1, 3, 4, 5, 0 };
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr 1fr");
    model.SetLayoutOptions(option);
    model.SetColumnsGap(Dimension(COL_GAP));
    model.SetRowsGap(Dimension(ROW_GAP));
    CreateFixedItems(10);
    CreateDone();

    bool smooth = GetParam();
    ScrollToIndex(1, smooth, ScrollAlign::START);
    EXPECT_TRUE(TickPosition(-105.0f));

    ScrollToIndex(3, smooth, ScrollAlign::CENTER);
    EXPECT_TRUE(TickPosition(-165.0f));

    ScrollToIndex(5, smooth, ScrollAlign::END);
    EXPECT_TRUE(TickPosition(-225.0f));

    ScrollToIndex(LAST_ITEM, smooth, ScrollAlign::AUTO);
    if (smooth) {
        EXPECT_TRUE(TickPosition(-225.0f));
    } else {
        EXPECT_TRUE(TickPosition(-435.0f));
    }
}

/**
 * @tc.name: ScrollToIndex_Irregular002
 * @tc.desc: Test ScrollToIndex with irregular
 * @tc.desc: OnGetIrregularSizeByIndex will set item (rows/cols) that in irregularIndexes
 * @tc.type: FUNC
 */
HWTEST_P(GridScrollerTestNg, ScrollToIndex_Irregular002, TestSize.Level1)
{
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
    CreateDone();

    bool smooth = GetParam();
    ScrollToIndex(1, smooth, ScrollAlign::START);
    EXPECT_TRUE(TickPosition(-105.0f));

    ScrollToIndex(3, smooth, ScrollAlign::CENTER);
    EXPECT_TRUE(TickPosition(-60.0f));

    ScrollToIndex(5, smooth, ScrollAlign::END);
    EXPECT_TRUE(TickPosition(-120.0f));
}

/**
 * @tc.name: ScrollToIndex_ExtraOffset001
 * @tc.desc: Test ScrollToIndex with extraOffset
 * @tc.type: FUNC
 */
HWTEST_P(GridScrollerTestNg, ScrollToIndex_ExtraOffset001, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    CreateFixedItems(20);
    CreateDone();

    /**
     * @tc.steps: step1. extraOffset < 0
     */
    bool smooth = GetParam();
    float extraOffset = -100.0f;
    ScrollToIndex(2, smooth, ScrollAlign::START, extraOffset);
    EXPECT_TRUE(TickPosition(0));

    ScrollToIndex(17, smooth, ScrollAlign::START, extraOffset);
    FlushUITasks();
    EXPECT_TRUE(TickPosition(-600.0f));

    ScrollToIndex(17, smooth, ScrollAlign::END, extraOffset);
    EXPECT_TRUE(TickPosition(-400.0f));

    ScrollToIndex(LAST_ITEM, smooth, ScrollAlign::END, extraOffset);
    if (smooth) {
        EXPECT_TRUE(TickPosition(-300.0f));
    } else {
        EXPECT_TRUE(TickPosition(-500.0f));
    }

    /**
     * @tc.steps: step2. Reset position
     */
    ScrollTo(0);
    EXPECT_TRUE(TickPosition(0));

    /**
     * @tc.steps: step3. extraOffset > 0
     */
    extraOffset = 100.0f;
    ScrollToIndex(2, smooth, ScrollAlign::START, extraOffset);
    EXPECT_TRUE(TickPosition(-200.0f));

    ScrollToIndex(2, smooth, ScrollAlign::END, extraOffset);
    EXPECT_TRUE(TickPosition(0));

    ScrollToIndex(17, smooth, ScrollAlign::END, extraOffset);
    EXPECT_TRUE(TickPosition(-600.0f));

    ScrollToIndex(LAST_ITEM, smooth, ScrollAlign::END, extraOffset);
    EXPECT_TRUE(TickPosition(-600.0f));
}

/**
 * @tc.name: AnimateTo001
 * @tc.desc: Test AnimateTo Function.
 * @tc.type: FUNC
 */
HWTEST_P(GridScrollerTestNg, AnimateTo001, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr");
    CreateFixedItems(10);
    CreateDone();
    EXPECT_EQ(pattern_->GetScrollableDistance(), 600.0f);

    /**
     * @tc.steps: step1. AnimateTo the position in the scroll
     * @tc.expected: AnimateTo the position
     */
    bool smooth = GetParam();
    AnimateTo(Dimension(ITEM_MAIN_SIZE), 0, nullptr, smooth);
    EXPECT_TRUE(TickPosition(-ITEM_MAIN_SIZE));

    /**
     * @tc.steps: step2. AnimateTo the position over the scroll
     * @tc.expected: AnimateTo the bottom, can not over scroll
     */
    AnimateTo(Dimension(1000.0f), 0, nullptr, smooth);
    EXPECT_TRUE(TickPosition(-600.0f));

    /**
     * @tc.steps: step3. AnimateTo the top
     * @tc.expected: AnimateTo the top
     */
    AnimateTo(Dimension(0), 0, nullptr, smooth);
    EXPECT_TRUE(TickPosition(0));
}

/**
 * @tc.name: AnimateTo002
 * @tc.desc: Test AnimateTo with duration animation
 * @tc.type: FUNC
 */
HWTEST_P(GridScrollerTestNg, AnimateTo002, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr");
    CreateFixedItems(10);
    CreateDone();
    EXPECT_EQ(pattern_->GetScrollableDistance(), 600.0f);

    /**
     * @tc.steps: step1. AnimateTo the position in the scroll
     * @tc.expected: AnimateTo the position
     */
    AnimateTo(Dimension(ITEM_MAIN_SIZE), 1000.0f, Curves::EASE, false);
    EXPECT_TRUE(TickPosition(-ITEM_MAIN_SIZE));

    /**
     * @tc.steps: step2. AnimateTo the position over the scroll
     * @tc.expected: AnimateTo the bottom, can not over scroll
     */
    AnimateTo(Dimension(1000.0f), 1000.0f, Curves::EASE, false);
    EXPECT_TRUE(TickPosition(-600.0f));

    /**
     * @tc.steps: step3. AnimateTo the top
     * @tc.expected: AnimateTo the top
     */
    AnimateTo(Dimension(0), 1000.0f, Curves::EASE, false);
    EXPECT_TRUE(TickPosition(0));
}

/**
 * @tc.name: AnimateTo003
 * @tc.desc: Test unScrollable, can not scroll
 * @tc.type: FUNC
 */
HWTEST_P(GridScrollerTestNg, AnimateTo003, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr");
    CreateFixedItems(4);
    CreateDone();

    bool smooth = GetParam();
    AnimateTo(Dimension(ITEM_MAIN_SIZE), 0, nullptr, smooth);
    EXPECT_TRUE(TickPosition(0));
}

/**
 * @tc.name: AnimateTo004
 * @tc.desc: Test scroll position greater than GRID_HEIGHT
 * @tc.type: FUNC
 */
HWTEST_P(GridScrollerTestNg, AnimateTo004, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr");
    CreateFixedItems(10);
    CreateDone();

    bool smooth = GetParam();
    AnimateTo(Dimension(ITEM_MAIN_SIZE * 5), 0, nullptr, smooth);
    EXPECT_TRUE(TickPosition(-ITEM_MAIN_SIZE * 5));
}

/**
 * @tc.name: AnimateTo005
 * @tc.desc: Test unScrollable, set col/row template at same time, can not scroll
 * @tc.type: FUNC
 */
HWTEST_P(GridScrollerTestNg, AnimateTo005, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr");
    model.SetRowsTemplate("1fr");
    CreateFixedItems(10);
    CreateDone();
    EXPECT_FALSE(pattern_->isConfigScrollable_);

    bool smooth = GetParam();
    AnimateTo(Dimension(ITEM_MAIN_SIZE * 5), 0, nullptr, smooth);
    EXPECT_TRUE(TickPosition(0));
}

/**
 * @tc.name: ScrollBy001
 * @tc.desc: Test ScrollBy
 * @tc.type: FUNC
 */
HWTEST_P(GridScrollerTestNg, ScrollBy001, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    CreateFixedItems(20);
    CreateDone();
    EXPECT_EQ(pattern_->GetScrollableDistance(), 600.0f);

    /**
     * @tc.steps: step1. ScrollBy the position
     * @tc.expected: ScrollBy the position
     */
    bool smooth = GetParam();
    ScrollBy(0, ITEM_MAIN_SIZE, smooth);
    EXPECT_TRUE(TickPosition(-ITEM_MAIN_SIZE));

    /**
     * @tc.steps: step2. ScrollBy the position over the scroll
     * @tc.expected: ScrollBy the bottom, can not over scroll
     */
    ScrollBy(0, 1000.0f, smooth);
    EXPECT_TRUE(TickPosition(-600.0f));

    /**
     * @tc.steps: step3. ScrollBy the position 0
     * @tc.expected: Not scroll
     */
    ScrollBy(0, 0, smooth);
    EXPECT_TRUE(TickPosition(-600.0f));

    /**
     * @tc.steps: step4. ScrollBy the position to top
     * @tc.expected: ScrollBy the top
     */
    ScrollBy(0, -1000.0f, smooth);
    EXPECT_TRUE(TickPosition(0));
}

/**
 * @tc.name: ScrollToEdge001
 * @tc.desc: Test ScrollToEdge
 * @tc.type: FUNC
 */
HWTEST_P(GridScrollerTestNg, ScrollToEdge001, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr");
    CreateFixedItems(10);
    CreateDone();
    EXPECT_EQ(pattern_->GetScrollableDistance(), 600.0f);

    /**
     * @tc.steps: step1. SCROLL_BOTTOM
     * @tc.expected: Scroll to bottom with animation
     */
    bool smooth = GetParam();
    ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, smooth);
    EXPECT_TRUE(TickPosition(-600.0f));

    /**
     * @tc.steps: step2. SCROLL_TOP
     * @tc.expected: Scroll to top with animation
     */
    ScrollToEdge(ScrollEdgeType::SCROLL_TOP, smooth);
    EXPECT_TRUE(TickPosition(0));
}

/**
 * @tc.name: ScrollPage001
 * @tc.desc: Test ScrollPage
 * @tc.type: FUNC
 */
HWTEST_P(GridScrollerTestNg, ScrollPage001, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr");
    CreateFixedItems(10);
    CreateDone();
    EXPECT_EQ(pattern_->GetScrollableDistance(), 600.0f);

    /**
     * @tc.steps: step1. ScrollPage down
     * @tc.expected: Scroll down
     */
    bool smooth = GetParam();
    ScrollPage(false, smooth);
    EXPECT_TRUE(TickPosition(-GRID_HEIGHT));

    /**
     * @tc.steps: step2. ScrollPage up
     * @tc.expected: Scroll up
     */
    ScrollPage(true, smooth);
    EXPECT_TRUE(TickPosition(0));
}

INSTANTIATE_TEST_SUITE_P(Smooth, GridScrollerTestNg, testing::Bool());

/**
 * @tc.name: AnimateTo006
 * @tc.desc: Test AnimateTo with duration animation, canOverScroll
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollerTestNg, AnimateTo006, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr");
    model.SetEdgeEffect(EdgeEffect::SPRING, true);
    CreateFixedItems(10);
    CreateDone();
    EXPECT_EQ(pattern_->GetScrollableDistance(), 600.0f);

    /**
     * @tc.steps: step1. AnimateTo the position over the scroll
     * @tc.expected: AnimateTo the bottom, can over scroll
     */
    MockAnimationManager::GetInstance().SetTicks(5);
    bool canOverScroll = true;
    bool smooth = false;
    AnimateTo(Dimension(1000.0f), 1000.0f, Curves::EASE, smooth, canOverScroll);
    EXPECT_TRUE(TickPosition(-200.0f));
    EXPECT_TRUE(TickPosition(-400.0f));
    EXPECT_TRUE(TickPosition(-600.0f));
    EXPECT_TRUE(TickPosition(-800.0f)); // Tick doesn't advance new animations created within the same tick
    EXPECT_TRUE(TickPosition(-600.0f));
    EXPECT_TRUE(TickPosition(-600.0f));
    EXPECT_TRUE(TickPosition(-600.0f));
    EXPECT_TRUE(TickPosition(-600.0f));
    EXPECT_TRUE(TickPosition(-600.0f));
}

/**
 * @tc.name: AnimateTo007
 * @tc.desc: Test AnimateTo events.
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollerTestNg, AnimateTo007, TestSize.Level1)
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
    CreateDone();

    MockAnimationManager::GetInstance().SetTicks(2);
    AnimateTo(Dimension(ITEM_MAIN_SIZE), 0, nullptr, true);
    EXPECT_TRUE(TickPosition(-ITEM_MAIN_SIZE / 2));
    EXPECT_TRUE(isTrigger);

    /**
     * @tc.steps: step2. When Animation is running, call AnimateTo
     * @tc.expected: onScrollStart event will not be triggered
     */
    isTrigger = false; // reset val
    pattern_->AnimateTo(ITEM_MAIN_SIZE * 2, 200.f, Curves::LINEAR, true);
    EXPECT_FALSE(isTrigger);
    EXPECT_TRUE(TickPosition(-125.0f));
    EXPECT_TRUE(TickPosition(-ITEM_MAIN_SIZE * 2));
    EXPECT_TRUE(MockAnimationManager::GetInstance().AllFinished());
}

/**
 * @tc.name: ScrollToEdge002
 * @tc.desc: Test ScrollToEdge
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollerTestNg, ScrollToEdge002, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr");
    CreateFixedItems(10);
    CreateDone();
    EXPECT_EQ(pattern_->GetScrollableDistance(), 600.0f);

    /**
     * @tc.steps: step1. SCROLL_BOTTOM
     * @tc.expected: Scroll to bottom with animation
     */
    ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, 200.0f);
    EXPECT_TRUE(Position(-492.0f));

    /**
     * @tc.steps: step2. SCROLL_TOP
     * @tc.expected: Scroll to top with animation
     */
    ScrollToEdge(ScrollEdgeType::SCROLL_TOP, 200.0f);
    EXPECT_TRUE(Position(0));
}

/**
 * @tc.name: Fling001
 * @tc.desc: Test Fling
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollerTestNg, Fling001, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr");
    CreateFixedItems(10);
    CreateDone();
    EXPECT_EQ(pattern_->GetScrollableDistance(), 600.0f);

    /**
     * @tc.steps: step1. Fling, the flingVelocity greater than 0
     * @tc.expected: Scroll down
     */
    MockAnimationManager::GetInstance().SetTicks(TICK);
    const float finalPosition = 100.f;
    const float flingVelocity = finalPosition * FRICTION * FRICTION_SCALE;
    Fling(flingVelocity);
    EXPECT_TRUE(TickPosition(-finalPosition / TICK));
    EXPECT_TRUE(TickPosition(-finalPosition));

    /**
     * @tc.steps: step2. Fling, the flingVelocity less than 0
     * @tc.expected: Scroll up
     */
    Fling(-flingVelocity);
    EXPECT_TRUE(TickPosition(-finalPosition / TICK));
    EXPECT_TRUE(TickPosition(0));
}

/**
 * @tc.name: GetInfo001
 * @tc.desc: Test non-action GetCurrentOffset/GetScrollDirection/IsAtEnd/GetItemRect
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollerTestNg, GetInfo001, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr");
    CreateFixedItems(10);
    CreateDone();
    EXPECT_EQ(pattern_->GetScrollableDistance(), 600.0f);
    EXPECT_EQ(GetScrollDirection(), Axis::VERTICAL);
    EXPECT_TRUE(IsEqual(GetCurrentOffset(), Offset()));
    EXPECT_FALSE(IsAtEnd());
    EXPECT_TRUE(IsEqual(GetItemRect(0), Rect(0, 0, GRID_WIDTH, ITEM_MAIN_SIZE)));
    EXPECT_TRUE(IsEqual(GetItemRect(4), Rect()));

    /**
     * @tc.steps: step1. AnimateTo the position
     */
    AnimateTo(Dimension(ITEM_MAIN_SIZE), 0, nullptr, false);
    EXPECT_TRUE(IsEqual(GetCurrentOffset(), Offset(0, ITEM_MAIN_SIZE)));
    EXPECT_FALSE(IsAtEnd());
    EXPECT_TRUE(IsEqual(GetItemRect(0), Rect()));
    EXPECT_TRUE(IsEqual(GetItemRect(1), Rect(0, 0, GRID_WIDTH, ITEM_MAIN_SIZE)));
    EXPECT_TRUE(IsEqual(GetItemRect(5), Rect()));

    /**
     * @tc.steps: step2. AnimateTo bottom
     */
    AnimateTo(Dimension(600.0f), 0, nullptr, false);
    EXPECT_TRUE(IsEqual(GetCurrentOffset(), Offset(0, 600.0f)));
    EXPECT_TRUE(IsAtEnd());
    EXPECT_TRUE(IsEqual(GetItemRect(5), Rect()));
    EXPECT_TRUE(IsEqual(GetItemRect(6), Rect(0, 0, GRID_WIDTH, ITEM_MAIN_SIZE)));
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
    CreateFocusableGridItems(10, ITEM_MAIN_SIZE, ITEM_MAIN_SIZE);
    CreateDone();

    /**
     * @tc.steps: step1. Focus node outside the viewport
     * @tc.expected: scroll to the node
     */
    int32_t focusNodeIndex = 6;
    pattern_->ScrollToFocusNodeIndex(focusNodeIndex);
    FlushUITasks();
    RefPtr<FocusHub> focusNode = GetChildFocusHub(frameNode_, focusNodeIndex);
    EXPECT_TRUE(focusNode->IsCurrentFocus());
    EXPECT_TRUE(Position(0));

    /**
     * @tc.steps: step2. Focus node index not exist
     * @tc.expected: do nothing
     */
    focusNodeIndex = 10;
    pattern_->ScrollToFocusNodeIndex(focusNodeIndex);
    FlushUITasks();
    EXPECT_TRUE(Position(0));
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
    CreateDone();

    /**
     * @tc.steps: step1. Focus node outside the viewport
     * @tc.expected: scroll to the node
     */
    int32_t focusNodeIndex = 6;
    RefPtr<FrameNode> focusNode = GetChildFrameNode(frameNode_, focusNodeIndex);
    pattern_->ScrollToNode(focusNode);
    FlushUITasks();
    EXPECT_TRUE(Position(0));
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
    model.SetLayoutOptions({});
    CreateFixedItems(10);
    CreateDone();

    OverScrollOffset offset = pattern_->GetOverScrollOffset(ITEM_MAIN_SIZE);
    OverScrollOffset expectOffset = { ITEM_MAIN_SIZE, 0 };
    EXPECT_TRUE(IsEqual(offset, expectOffset));
    offset = pattern_->GetOverScrollOffset(0);
    expectOffset = { 0, 0 };
    EXPECT_TRUE(IsEqual(offset, expectOffset));
    offset = pattern_->GetOverScrollOffset(-ITEM_MAIN_SIZE);
    expectOffset = { 0, 0 };
    EXPECT_TRUE(IsEqual(offset, expectOffset));

    pattern_->info_.currentOffset_ = -ITEM_MAIN_SIZE;
    offset = pattern_->GetOverScrollOffset(ITEM_MAIN_SIZE * 2);
    expectOffset = { ITEM_MAIN_SIZE, 0 };
    EXPECT_TRUE(IsEqual(offset, expectOffset));
    offset = pattern_->GetOverScrollOffset(0);
    expectOffset = { 0, 0 };
    EXPECT_TRUE(IsEqual(offset, expectOffset));
    offset = pattern_->GetOverScrollOffset(-ITEM_MAIN_SIZE * 2);
    expectOffset = { 0, 0 };
    EXPECT_TRUE(IsEqual(offset, expectOffset));

    pattern_->info_.currentOffset_ = -ITEM_MAIN_SIZE * 2;
    offset = pattern_->GetOverScrollOffset(ITEM_MAIN_SIZE);
    expectOffset = { 0, 0 };
    EXPECT_TRUE(IsEqual(offset, expectOffset));
    offset = pattern_->GetOverScrollOffset(0);
    expectOffset = { 0, 0 };
    EXPECT_TRUE(IsEqual(offset, expectOffset));
    offset = pattern_->GetOverScrollOffset(-ITEM_MAIN_SIZE);
    expectOffset = { 0, 0 };
    EXPECT_TRUE(IsEqual(offset, expectOffset));

    pattern_->info_.currentOffset_ = ITEM_MAIN_SIZE;
    offset = pattern_->GetOverScrollOffset(ITEM_MAIN_SIZE);
    expectOffset = { ITEM_MAIN_SIZE, 0 };
    EXPECT_TRUE(IsEqual(offset, expectOffset));
    offset = pattern_->GetOverScrollOffset(0);
    expectOffset = { 0, 0 };
    EXPECT_TRUE(IsEqual(offset, expectOffset));
    offset = pattern_->GetOverScrollOffset(-ITEM_MAIN_SIZE * 2);
    expectOffset = { -ITEM_MAIN_SIZE, 0 };
    EXPECT_TRUE(IsEqual(offset, expectOffset));

    pattern_->info_.currentOffset_ = -ITEM_MAIN_SIZE * 3;
    offset = pattern_->GetOverScrollOffset(ITEM_MAIN_SIZE * 2);
    expectOffset = { 0, 0 };
    EXPECT_TRUE(IsEqual(offset, expectOffset));
    offset = pattern_->GetOverScrollOffset(0);
    expectOffset = { 0, 0 };
    EXPECT_TRUE(IsEqual(offset, expectOffset));
    offset = pattern_->GetOverScrollOffset(-ITEM_MAIN_SIZE);
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
    CreateDone();

    OverScrollOffset offset = pattern_->GetOverScrollOffset(ITEM_MAIN_SIZE);
    OverScrollOffset expectOffset = { ITEM_MAIN_SIZE, 0 };
    EXPECT_TRUE(IsEqual(offset, expectOffset));
    offset = pattern_->GetOverScrollOffset(0);
    expectOffset = { 0, 0 };
    EXPECT_TRUE(IsEqual(offset, expectOffset));
    offset = pattern_->GetOverScrollOffset(-ITEM_MAIN_SIZE);
    expectOffset = { 0, -ITEM_MAIN_SIZE };
    EXPECT_TRUE(IsEqual(offset, expectOffset));

    pattern_->info_.currentOffset_ = -ITEM_MAIN_SIZE;
    offset = pattern_->GetOverScrollOffset(ITEM_MAIN_SIZE * 2);
    expectOffset = { ITEM_MAIN_SIZE, ITEM_MAIN_SIZE };
    EXPECT_TRUE(IsEqual(offset, expectOffset));
    offset = pattern_->GetOverScrollOffset(0);
    expectOffset = { 0, 0 };
    EXPECT_TRUE(IsEqual(offset, expectOffset));
    offset = pattern_->GetOverScrollOffset(-ITEM_MAIN_SIZE * 2);
    expectOffset = { 0, -ITEM_MAIN_SIZE * 2 };
    EXPECT_TRUE(IsEqual(offset, expectOffset));

    pattern_->info_.currentOffset_ = -ITEM_MAIN_SIZE * 2;
    offset = pattern_->GetOverScrollOffset(ITEM_MAIN_SIZE);
    expectOffset = { 0, ITEM_MAIN_SIZE };
    EXPECT_TRUE(IsEqual(offset, expectOffset));
    offset = pattern_->GetOverScrollOffset(0);
    expectOffset = { 0, 0 };
    EXPECT_TRUE(IsEqual(offset, expectOffset));
    offset = pattern_->GetOverScrollOffset(-ITEM_MAIN_SIZE);
    expectOffset = { 0, -ITEM_MAIN_SIZE };
    EXPECT_TRUE(IsEqual(offset, expectOffset));

    pattern_->info_.currentOffset_ = ITEM_MAIN_SIZE;
    offset = pattern_->GetOverScrollOffset(ITEM_MAIN_SIZE);
    expectOffset = { ITEM_MAIN_SIZE, 0 };
    EXPECT_TRUE(IsEqual(offset, expectOffset));
    offset = pattern_->GetOverScrollOffset(0);
    expectOffset = { 0, 0 };
    EXPECT_TRUE(IsEqual(offset, expectOffset));
    offset = pattern_->GetOverScrollOffset(-ITEM_MAIN_SIZE * 2);
    expectOffset = { -ITEM_MAIN_SIZE, -ITEM_MAIN_SIZE };
    EXPECT_TRUE(IsEqual(offset, expectOffset));

    pattern_->info_.currentOffset_ = -ITEM_MAIN_SIZE * 3;
    offset = pattern_->GetOverScrollOffset(ITEM_MAIN_SIZE * 2);
    expectOffset = { 0, ITEM_MAIN_SIZE * 2 };
    EXPECT_TRUE(IsEqual(offset, expectOffset));
    offset = pattern_->GetOverScrollOffset(0);
    expectOffset = { 0, 0 };
    EXPECT_TRUE(IsEqual(offset, expectOffset));
    offset = pattern_->GetOverScrollOffset(-ITEM_MAIN_SIZE);
    expectOffset = { 0, -ITEM_MAIN_SIZE };
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
    CreateDone();
    UpdateCurrentOffset(-50.0f, SCROLL_FROM_UPDATE);
    EXPECT_TRUE(Position(-50.0f));
    UpdateCurrentOffset(50.0f, SCROLL_FROM_UPDATE);
    EXPECT_TRUE(Position(0.0f));
    UpdateCurrentOffset(-100.0f, SCROLL_FROM_UPDATE);
    EXPECT_TRUE(Position(-100.0f));
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
    CreateDone();
    UpdateCurrentOffset(-50.0f, SCROLL_FROM_BAR);
    EXPECT_TRUE(Position(-50.0f));
    UpdateCurrentOffset(50.0f, SCROLL_FROM_BAR);
    EXPECT_TRUE(Position(0));
    UpdateCurrentOffset(-100.0f, SCROLL_FROM_BAR);
    EXPECT_TRUE(Position(-100.0f));
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
    CreateDone();
    pattern_->scrollEffect_ = AceType::MakeRefPtr<ScrollEdgeEffect>(EdgeEffect::FADE);
    UpdateCurrentOffset(-50.0f, SCROLL_FROM_UPDATE);
    EXPECT_TRUE(Position(-50.0f));
    UpdateCurrentOffset(50.0f, SCROLL_FROM_UPDATE);
    EXPECT_TRUE(Position(0.0f));
    UpdateCurrentOffset(-100.0f, SCROLL_FROM_UPDATE);
    EXPECT_TRUE(Position(-100.0f));
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
    CreateDone();
    EXPECT_FALSE(pattern_->isConfigScrollable_);

    UpdateCurrentOffset(-100.f, SCROLL_FROM_UPDATE);
    EXPECT_TRUE(Position(0));
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
    model.SetEdgeEffect(EdgeEffect::SPRING, true);
    CreateFixedItems(20, GridItemStyle::NONE);
    CreateDone();

    int32_t targetIndex = 19;
    ScrollAlign align = ScrollAlign::AUTO;
    ScrollToIndex(targetIndex, false, align);
    auto& info = pattern_->info_;
    EXPECT_EQ(info.startMainLineIndex_, 6);
    EXPECT_EQ(info.endMainLineIndex_, 9);
    pattern_->scrollableEvent_->scrollable_->isTouching_ = true;
    for (int i = 0; i < 500; ++i) {
        UpdateCurrentOffset(-100.0f);
    }
    if (SystemProperties::GetGridIrregularLayoutEnabled()) {
        EXPECT_EQ(info.startMainLineIndex_, 9);
    } else {
        EXPECT_EQ(info.startMainLineIndex_, 10);
    }
    EXPECT_EQ(info.endMainLineIndex_, 9);

    EXPECT_LT(info.currentOffset_, -75.0f);

    ScrollToIndex(targetIndex, false, ScrollAlign::END);
    for (int i = 0; i < 10; ++i) {
        info.currentOffset_ -= 75.0f;
        frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
        FlushUITasks();
    }
    if (SystemProperties::GetGridIrregularLayoutEnabled()) {
        EXPECT_EQ(info.startMainLineIndex_, 9);
    } else {
        EXPECT_EQ(info.startMainLineIndex_, 10);
    }
    EXPECT_EQ(info.endMainLineIndex_, 9);

    EXPECT_LT(info.currentOffset_, -75.0f);
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
    CreateDone();

    int32_t targetIndex = 19;
    ScrollAlign align = ScrollAlign::AUTO;
    ScrollToIndex(targetIndex, false, align);
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
 * @tc.name: GetEndOffset002
 * @tc.desc: Test GetEndOffset with updated offset on old layout
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollerTestNg, GetEndOffset002, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    CreateFixedItems(20, GridItemStyle::NONE);
    model.SetLayoutOptions({});
    CreateDone();

    int32_t targetIndex = 19;
    ScrollAlign align = ScrollAlign::AUTO;
    ScrollToIndex(targetIndex, false, align);
    auto& info = pattern_->info_;
    info.prevOffset_ = info.currentOffset_;
    info.currentOffset_ -= 399;
    info.synced_ = false;
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    pattern_->SetEdgeEffect(EdgeEffect::SPRING);
    pattern_->scrollableEvent_->scrollable_->isTouching_ = true;
    pattern_->GetScrollEdgeEffect()->ProcessScrollOver(-399);
    EXPECT_TRUE(info.synced_);
    EXPECT_EQ(info.prevOffset_, -99);
    EXPECT_EQ(info.currentOffset_, -99);
    EXPECT_EQ(info.startIndex_, 18);
    EXPECT_EQ(info.endIndex_, 19);
    EXPECT_EQ(info.startMainLineIndex_, 9);
    EXPECT_EQ(info.endMainLineIndex_, 9);
    EXPECT_EQ(pattern_->GetEndOffset(), 300);
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
    CreateBigItem(0, 1, 0, 1, 2 * ITEM_MAIN_SIZE, 2 * ITEM_MAIN_SIZE);
    CreateDone();

    pattern_->ScrollBy(-10);
    FlushUITasks();
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
    CreateGridItem(60, 550);
    ViewStackProcessor::GetInstance()->Pop();
    ViewStackProcessor::GetInstance()->StopGetAccessRecording();
    CreateGridItems(20, 60, 390);
    CreateDone();

    // cache all line in Grid
    ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, true);
    ScrollToEdge(ScrollEdgeType::SCROLL_TOP, false);

    ScrollToIndex(5, false, ScrollAlign::AUTO, std::nullopt);
    EXPECT_TRUE(Position(-550.0f));

    ScrollToEdge(ScrollEdgeType::SCROLL_TOP, true);

    ScrollToIndex(7, false, ScrollAlign::AUTO, std::nullopt);
    EXPECT_TRUE(Position(-790.0f));

    ScrollToEdge(ScrollEdgeType::SCROLL_TOP, true);

    ScrollToIndex(9, false, ScrollAlign::AUTO, std::nullopt);
    EXPECT_TRUE(Position(-1190.0f));
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
    CreateGridItems(3, 60.0f, 150.0f);

    CreateGridItem(60.0f, 550.0f);
    ViewStackProcessor::GetInstance()->Pop();
    ViewStackProcessor::GetInstance()->StopGetAccessRecording();

    CreateGridItems(20, 60.0f, 190.0f);
    CreateDone();

    // cache all line in Grid
    ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, true);
    ScrollToEdge(ScrollEdgeType::SCROLL_TOP, false);

    ScrollToIndex(5, false, ScrollAlign::AUTO, std::nullopt);
    EXPECT_TRUE(Position(-310.0f));

    ScrollToEdge(ScrollEdgeType::SCROLL_TOP, true);

    ScrollToIndex(7, false, ScrollAlign::AUTO, std::nullopt);
    EXPECT_TRUE(Position(-730.0f));

    ScrollToEdge(ScrollEdgeType::SCROLL_TOP, true);

    ScrollToIndex(9, false, ScrollAlign::AUTO, std::nullopt);
    EXPECT_TRUE(Position(-870.0f));
}
} // namespace OHOS::Ace::NG
