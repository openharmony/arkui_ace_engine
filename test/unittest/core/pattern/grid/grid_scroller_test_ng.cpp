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
    EXPECT_TRUE(Position(0));
    EXPECT_TRUE(pattern_->IsAtTop());

    // Scroll to the first item in row in view
    ScrollToIndex(2, smooth, align);
    EXPECT_TRUE(Position(-100.0f));

    // Scroll to the last item in row in view
    ScrollToIndex(5, smooth, align);
    EXPECT_TRUE(Position(-200.0f));

    if (smooth) {
        // Scroll to the item out of view
        ScrollToIndex(12, smooth, align);
        EXPECT_TRUE(Position(-600.0f));
        EXPECT_FALSE(pattern_->IsAtBottom());

        // Scroll back
        ScrollToIndex(3, smooth, align);
        EXPECT_TRUE(Position(0));
    } else {
        // Scroll to the item out of view
        ScrollToIndex(12, smooth, align);
        EXPECT_TRUE(Position(-600.0f));
        EXPECT_TRUE(pattern_->IsAtBottom());

        // Scroll back
        ScrollToIndex(3, smooth, align);
        EXPECT_TRUE(Position(-100.0f));
    }

    // Scroll to the last item
    ScrollToIndex(LAST_ITEM, smooth, align);
    EXPECT_TRUE(Position(-600.0f));
    EXPECT_TRUE(pattern_->IsAtBottom());

    // Scroll with invalid index
    ScrollToIndex(-100, smooth, align);
    EXPECT_TRUE(Position(-600.0f));
    ScrollToIndex(100, smooth, align);
    EXPECT_TRUE(Position(-600.0f));
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
    EXPECT_TRUE(Position(0));
    EXPECT_TRUE(pattern_->IsAtTop());

    // Scroll to the first item in row in view
    ScrollToIndex(4, smooth, align);
    EXPECT_TRUE(Position(-50.0f));

    // Scroll to the last item in row in view
    ScrollToIndex(7, smooth, align);
    EXPECT_TRUE(Position(-150.0f));

    // Scroll to the item out of view
    ScrollToIndex(12, smooth, align);
    EXPECT_TRUE(Position(-450.0f));

    // Scroll back
    ScrollToIndex(5, smooth, align);
    EXPECT_TRUE(Position(-50.0f));

    // Scroll to the last item
    ScrollToIndex(LAST_ITEM, smooth, align);
    if (smooth) {
        EXPECT_TRUE(Position(-50.0f));
        EXPECT_FALSE(pattern_->IsAtBottom());
    } else {
        EXPECT_TRUE(Position(-600.0f));
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
    EXPECT_TRUE(Position(0));
    EXPECT_TRUE(pattern_->IsAtTop());

    // Scroll to the first item in row in view
    ScrollToIndex(4, smooth, align);
    EXPECT_TRUE(Position(0));

    // Scroll to the first item in row out of view
    ScrollToIndex(12, smooth, align);
    EXPECT_TRUE(Position(-300.0f));

    // Scroll to the last item in row out of view
    ScrollToIndex(15, smooth, align);
    EXPECT_TRUE(Position(-400.0f));

    if (smooth) {
        // Scroll back
        ScrollToIndex(5, smooth, align);
        EXPECT_TRUE(Position(100));

        // Scroll to the last item
        ScrollToIndex(LAST_ITEM, smooth, align);
        EXPECT_TRUE(Position(0));
        EXPECT_FALSE(pattern_->IsAtBottom());
    } else {
        // Scroll back
        ScrollToIndex(5, smooth, align);
        EXPECT_TRUE(Position(0));

        // Scroll to the last item
        ScrollToIndex(LAST_ITEM, smooth, align);
        EXPECT_TRUE(Position(-600.0f));
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
    EXPECT_TRUE(Position(0));
    EXPECT_TRUE(pattern_->IsAtTop());

    // Scroll to the first item in row in view
    ScrollToIndex(4, smooth, align);
    EXPECT_TRUE(Position(0));

    // Scroll to the first item in row out of view
    ScrollToIndex(12, smooth, align);
    EXPECT_TRUE(Position(-300.0f));

    // Scroll to the last item in row out of view
    ScrollToIndex(15, smooth, align);
    EXPECT_TRUE(Position(-400.0f));

    // Scroll back
    ScrollToIndex(5, smooth, align);
    EXPECT_TRUE(Position(-200.0f));

    // Scroll to the last item
    ScrollToIndex(LAST_ITEM, smooth, align);
    if (smooth) {
        EXPECT_TRUE(Position(-200.0f));
        EXPECT_FALSE(pattern_->IsAtBottom());
    } else {
        EXPECT_TRUE(Position(-600.0f));
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
    EXPECT_TRUE(Position(-105.0f));

    // ScrollAlign::CENTER
    ScrollToIndex(7, smooth, ScrollAlign::CENTER);
    EXPECT_TRUE(Position(-165.0f));

    // ScrollAlign::END
    ScrollToIndex(12, smooth, ScrollAlign::END);
    EXPECT_TRUE(Position(-330.0f));

    // ScrollAlign::AUTO
    ScrollToIndex(LAST_ITEM, smooth, ScrollAlign::AUTO);
    if (smooth) {
        EXPECT_TRUE(Position(-330.0f));
        EXPECT_FALSE(pattern_->IsAtBottom());
    } else {
        EXPECT_TRUE(Position(-645.0f));
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
    EXPECT_TRUE(Position(-(ITEM_MAIN_SIZE * 3 + BIG_ROW_GAP * 2 - GRID_HEIGHT)));
    /**
     * @tc.cases: use ScrollTo to make item 5 in the last line, ScrollTo index:5, text ScrollAlign::AUTO
     * @tc.expected: scrollToIndex don't change grid offset
     */
    auto autoPosition = ITEM_MAIN_SIZE * 3 + BIG_ROW_GAP * 2 - GRID_HEIGHT + ITEM_MAIN_SIZE;
    ScrollTo(autoPosition);
    ScrollToIndex(index, smooth, ScrollAlign::AUTO);
    EXPECT_TRUE(Position(-autoPosition));
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
    EXPECT_TRUE(Position(-(endPosition + (GRID_HEIGHT - ITEM_MAIN_SIZE) / 2)));
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
    EXPECT_TRUE(Position(-position));

    bool smooth = GetParam();
    ScrollToIndex(6, smooth, ScrollAlign::AUTO);
    EXPECT_TRUE(Position(-position));
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
    EXPECT_TRUE(Position(-105.0f));

    ScrollToIndex(3, smooth, ScrollAlign::CENTER);
    EXPECT_TRUE(Position(-165.0f));

    ScrollToIndex(5, smooth, ScrollAlign::END);
    EXPECT_TRUE(Position(-225.0f));

    ScrollToIndex(LAST_ITEM, smooth, ScrollAlign::AUTO);
    if (smooth) {
        EXPECT_TRUE(Position(-225.0f));
    } else {
        EXPECT_TRUE(Position(-435.0f));
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
    EXPECT_TRUE(Position(-105.0f));

    ScrollToIndex(3, smooth, ScrollAlign::CENTER);
    EXPECT_TRUE(Position(-60.0f));

    ScrollToIndex(5, smooth, ScrollAlign::END);
    EXPECT_TRUE(Position(-120.0f));
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
    EXPECT_TRUE(Position(0));

    ScrollToIndex(17, smooth, ScrollAlign::START, extraOffset);
    EXPECT_TRUE(Position(-700.0f));

    ScrollToIndex(17, smooth, ScrollAlign::END, extraOffset);
    EXPECT_TRUE(Position(-400.0f));

    ScrollToIndex(LAST_ITEM, smooth, ScrollAlign::END, extraOffset);
    if (smooth) {
        EXPECT_TRUE(Position(-300.0f));
    } else {
        EXPECT_TRUE(Position(-500.0f));
    }

    /**
     * @tc.steps: step2. Reset position
     */
    ScrollTo(0);
    EXPECT_TRUE(Position(0));

    /**
     * @tc.steps: step3. extraOffset > 0
     */
    extraOffset = 100.0f;
    ScrollToIndex(2, smooth, ScrollAlign::START, extraOffset);
    EXPECT_TRUE(Position(-200.0f));

    ScrollToIndex(2, smooth, ScrollAlign::END, extraOffset);
    if (smooth) {
        EXPECT_TRUE(Position(100.0f));
    } else {
        EXPECT_TRUE(Position(0));
    }

    ScrollToIndex(17, smooth, ScrollAlign::END, extraOffset);
    EXPECT_TRUE(Position(-600.0f));

    ScrollToIndex(LAST_ITEM, smooth, ScrollAlign::END, extraOffset);
    if (smooth) {
        EXPECT_TRUE(Position(0));
    } else {
        EXPECT_TRUE(Position(-600.0f));
    }
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
    EXPECT_TRUE(Position(-ITEM_MAIN_SIZE));

    /**
     * @tc.steps: step2. AnimateTo the position over the scroll
     * @tc.expected: AnimateTo the bottom, can not over scroll
     */
    AnimateTo(Dimension(1000.0f), 0, nullptr, smooth);
    if (smooth) {
        EXPECT_TRUE(Position(-1000.0f));
    } else {
        EXPECT_TRUE(Position(-600.0f));
    }

    /**
     * @tc.steps: step3. AnimateTo the top
     * @tc.expected: AnimateTo the top
     */
    AnimateTo(Dimension(0), 0, nullptr, smooth);
    EXPECT_TRUE(Position(0));
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
    EXPECT_TRUE(Position(-ITEM_MAIN_SIZE));

    /**
     * @tc.steps: step2. AnimateTo the position over the scroll
     * @tc.expected: AnimateTo the bottom, can not over scroll
     */
    AnimateTo(Dimension(1000.0f), 1000.0f, Curves::EASE, false);
    EXPECT_TRUE(Position(-1000.0f));

    /**
     * @tc.steps: step3. AnimateTo the top
     * @tc.expected: AnimateTo the top
     */
    AnimateTo(Dimension(0), 1000.0f, Curves::EASE, false);
    EXPECT_TRUE(Position(0));
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
    EXPECT_TRUE(Position(0));
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
    EXPECT_TRUE(Position(-ITEM_MAIN_SIZE * 5));
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
    EXPECT_TRUE(Position(0));
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
    positionController_->ScrollBy(0, ITEM_MAIN_SIZE, smooth);
    FlushUITasks();
    EXPECT_TRUE(Position(-ITEM_MAIN_SIZE));

    /**
     * @tc.steps: step2. ScrollBy the position over the scroll
     * @tc.expected: ScrollBy the bottom, can not over scroll
     */
    positionController_->ScrollBy(0, 1000.0f, smooth);
    FlushUITasks();
    EXPECT_TRUE(Position(-600.0f));

    /**
     * @tc.steps: step3. ScrollBy the position 0
     * @tc.expected: Not scroll
     */
    positionController_->ScrollBy(0, 0, smooth);
    FlushUITasks();
    EXPECT_TRUE(Position(-600.0f));

    /**
     * @tc.steps: step4. ScrollBy the position to top
     * @tc.expected: ScrollBy the top
     */
    positionController_->ScrollBy(0, -1000.0f, smooth);
    FlushUITasks();
    EXPECT_TRUE(Position(0));
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
    positionController_->ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, smooth);
    FlushUITasks();
    EXPECT_TRUE(Position(-600.0f));

    /**
     * @tc.steps: step2. SCROLL_TOP
     * @tc.expected: Scroll to top with animation
     */
    positionController_->ScrollToEdge(ScrollEdgeType::SCROLL_TOP, smooth);
    FlushUITasks();
    EXPECT_TRUE(Position(0));
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
    positionController_->ScrollPage(false, smooth);
    FlushUITasks();
    EXPECT_TRUE(Position(-GRID_HEIGHT));

    /**
     * @tc.steps: step2. ScrollPage up
     * @tc.expected: Scroll up
     */
    positionController_->ScrollPage(true, smooth);
    FlushUITasks();
    EXPECT_TRUE(Position(0));
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
    EXPECT_TRUE(Position(-200.f));
    EXPECT_TRUE(Position(-400.f));
    EXPECT_TRUE(Position(-600.0f));
    EXPECT_TRUE(Position(-800.f)); // Tick doesn't advance new animations created within the same tick
    EXPECT_TRUE(Position(-1000.f));
    EXPECT_TRUE(Position(-1000.f));
    EXPECT_TRUE(Position(-1000.f));
    EXPECT_TRUE(Position(-1000.f));
    EXPECT_TRUE(Position(-1000.0f));
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
    EXPECT_TRUE(Position(-ITEM_MAIN_SIZE / 2));
    EXPECT_TRUE(isTrigger);

    /**
     * @tc.steps: step2. When Animation is running, call AnimateTo
     * @tc.expected: onScrollStart event will not be triggered
     */
    isTrigger = false; // reset val
    pattern_->AnimateTo(ITEM_MAIN_SIZE * 2, 200.f, Curves::LINEAR, true);
    EXPECT_FALSE(isTrigger);
    EXPECT_TRUE(Position(-125.0f));
    EXPECT_TRUE(Position(-ITEM_MAIN_SIZE * 2));
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
    positionController_->ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, 200.f);
    FlushUITasks();
    EXPECT_TRUE(Position(-492.0f));

    /**
     * @tc.steps: step2. SCROLL_TOP
     * @tc.expected: Scroll to top with animation
     */
    positionController_->ScrollToEdge(ScrollEdgeType::SCROLL_TOP, 200.f);
    FlushUITasks();
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
    positionController_->Fling(flingVelocity);
    FlushUITasks();
    EXPECT_TRUE(Position(-finalPosition / TICK));
    EXPECT_TRUE(Position(-finalPosition));

    /**
     * @tc.steps: step2. Fling, the flingVelocity less than 0
     * @tc.expected: Scroll up
     */
    positionController_->Fling(-flingVelocity);
    FlushUITasks();
    EXPECT_TRUE(Position(-finalPosition / TICK));
    EXPECT_TRUE(Position(0));
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
    EXPECT_EQ(positionController_->GetScrollDirection(), Axis::VERTICAL);
    EXPECT_TRUE(IsEqual(positionController_->GetCurrentOffset(), Offset()));
    EXPECT_FALSE(positionController_->IsAtEnd());
    EXPECT_TRUE(IsEqual(positionController_->GetItemRect(0), Rect(0, 0, GRID_WIDTH, ITEM_MAIN_SIZE)));
    EXPECT_TRUE(IsEqual(positionController_->GetItemRect(4), Rect()));

    /**
     * @tc.steps: step1. AnimateTo the position
     */
    AnimateTo(Dimension(ITEM_MAIN_SIZE), 0, nullptr, false);
    EXPECT_TRUE(IsEqual(positionController_->GetCurrentOffset(), Offset(0, ITEM_MAIN_SIZE)));
    EXPECT_FALSE(positionController_->IsAtEnd());
    EXPECT_TRUE(IsEqual(positionController_->GetItemRect(0), Rect()));
    EXPECT_TRUE(IsEqual(positionController_->GetItemRect(1), Rect(0, 0, GRID_WIDTH, ITEM_MAIN_SIZE)));
    EXPECT_TRUE(IsEqual(positionController_->GetItemRect(5), Rect()));

    /**
     * @tc.steps: step2. AnimateTo bottom
     */
    AnimateTo(Dimension(600.0f), 0, nullptr, false);
    EXPECT_TRUE(IsEqual(positionController_->GetCurrentOffset(), Offset(0, 600.0f)));
    EXPECT_TRUE(positionController_->IsAtEnd());
    EXPECT_TRUE(IsEqual(positionController_->GetItemRect(5), Rect()));
    EXPECT_TRUE(IsEqual(positionController_->GetItemRect(6), Rect(0, 0, GRID_WIDTH, ITEM_MAIN_SIZE)));
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
    CreateDone();
    EXPECT_TRUE(pattern_->IsAtTop());
    int32_t index = 0;
    ScrollToIndex(index, false, ScrollAlign::START);
    EXPECT_TRUE(Position(0));
    ScrollToIndex(index, false, ScrollAlign::CENTER);
    EXPECT_TRUE(Position(0));
    ScrollToIndex(index, false, ScrollAlign::END);
    EXPECT_TRUE(Position(0));
    ScrollToIndex(index, false, ScrollAlign::AUTO);
    EXPECT_TRUE(Position(0));
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
    CreateDone();
    int32_t index = 4;
    ScrollToIndex(index, false, ScrollAlign::START);
    EXPECT_TRUE(Position(-ITEM_MAIN_SIZE * 2));
    ScrollToIndex(index, false, ScrollAlign::CENTER);
    EXPECT_TRUE(Position(-ITEM_MAIN_SIZE * 0.5));
    ScrollToIndex(index, false, ScrollAlign::END);
    EXPECT_TRUE(Position(0));
    ScrollToIndex(index, false, ScrollAlign::AUTO);
    EXPECT_TRUE(Position(0));
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
    CreateDone();
    int32_t index = 8;
    ScrollToIndex(index, false, ScrollAlign::START);
    EXPECT_TRUE(Position(-ITEM_MAIN_SIZE * 4));
    ScrollToIndex(index, false, ScrollAlign::CENTER);
    EXPECT_TRUE(Position(-ITEM_MAIN_SIZE * 2.5));
    ScrollToIndex(index, false, ScrollAlign::END);
    EXPECT_TRUE(Position(-ITEM_MAIN_SIZE));
    ScrollToIndex(index, false, ScrollAlign::AUTO);
    EXPECT_TRUE(Position(-ITEM_MAIN_SIZE));
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
    CreateDone();
    int32_t index = LAST_ITEM;
    ScrollToIndex(index, false, ScrollAlign::START);
    EXPECT_TRUE(Position(-ITEM_MAIN_SIZE * 6));
    ScrollToIndex(index, false, ScrollAlign::CENTER);
    EXPECT_TRUE(Position(-ITEM_MAIN_SIZE * 6));
    ScrollToIndex(index, false, ScrollAlign::END);
    EXPECT_TRUE(Position(-ITEM_MAIN_SIZE * 6));
    ScrollToIndex(index, false, ScrollAlign::AUTO);
    EXPECT_TRUE(Position(-ITEM_MAIN_SIZE * 6));
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
    CreateDone();
    pattern_->ScrollTo(ITEM_MAIN_SIZE * 4);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetTotalOffset(), ITEM_MAIN_SIZE * 4);
    EXPECT_EQ(accessibilityProperty_->GetScrollOffSet(), pattern_->GetTotalOffset());
    EXPECT_FALSE(pattern_->IsAtTop());
    EXPECT_FALSE(pattern_->IsAtBottom());
    int32_t index = 0;
    ScrollToIndex(index, false, ScrollAlign::START);
    EXPECT_TRUE(Position(0));
    ScrollToIndex(index, false, ScrollAlign::CENTER);
    EXPECT_TRUE(Position(0));
    ScrollToIndex(index, false, ScrollAlign::END);
    EXPECT_TRUE(Position(0));
    ScrollToIndex(index, false, ScrollAlign::AUTO);
    EXPECT_TRUE(Position(0));
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
    CreateDone();
    pattern_->ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, false);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetTotalOffset(), ITEM_MAIN_SIZE * 6);
    EXPECT_TRUE(pattern_->IsAtBottom());
    int32_t index = LAST_ITEM;
    ScrollToIndex(index, false, ScrollAlign::START);
    EXPECT_TRUE(Position(-ITEM_MAIN_SIZE * 6));
    ScrollToIndex(index, false, ScrollAlign::CENTER);
    EXPECT_TRUE(Position(-ITEM_MAIN_SIZE * 6));
    ScrollToIndex(index, false, ScrollAlign::END);
    EXPECT_TRUE(Position(-ITEM_MAIN_SIZE * 6));
    ScrollToIndex(index, false, ScrollAlign::AUTO);
    EXPECT_TRUE(Position(-ITEM_MAIN_SIZE * 6));
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
    CreateDone();
    int32_t index = -2;
    ScrollToIndex(index, false, ScrollAlign::START);
    EXPECT_TRUE(Position(0));
    ScrollToIndex(index, false, ScrollAlign::CENTER);
    EXPECT_TRUE(Position(0));
    ScrollToIndex(index, false, ScrollAlign::END);
    EXPECT_TRUE(Position(0));
    ScrollToIndex(index, false, ScrollAlign::AUTO);
    EXPECT_TRUE(Position(0));
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
    CreateDone();
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
    CreateDone();
    int32_t index = 8;
    ScrollToIndex(index, false, ScrollAlign::START);
    EXPECT_TRUE(Position(-(ITEM_MAIN_SIZE * 4 + ROW_GAP * 4)));
    ScrollToIndex(index, false, ScrollAlign::CENTER);
    EXPECT_TRUE(Position(-(ITEM_MAIN_SIZE * 2.5 + ROW_GAP * 4)));
    ScrollToIndex(index, false, ScrollAlign::END);
    EXPECT_TRUE(Position(-(ITEM_MAIN_SIZE + ROW_GAP * 4)));
    ScrollToIndex(index, false, ScrollAlign::AUTO);
    EXPECT_TRUE(Position(-(ITEM_MAIN_SIZE + ROW_GAP * 4)));
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
    CreateDone();
    int32_t index = 5;
    ScrollToIndex(index, false, ScrollAlign::START);
    EXPECT_TRUE(Position(-(ITEM_MAIN_SIZE * 4 + ROW_GAP * 7)));
    ScrollToIndex(index, false, ScrollAlign::CENTER);
    EXPECT_TRUE(Position(-(ITEM_MAIN_SIZE * 3.5 + ROW_GAP * 5)));
    ScrollToIndex(index, false, ScrollAlign::END);
    EXPECT_TRUE(Position(-(ITEM_MAIN_SIZE * 2 + ROW_GAP * 5)));
    ScrollToIndex(index, false, ScrollAlign::AUTO);
    EXPECT_TRUE(Position(-(ITEM_MAIN_SIZE * 2 + ROW_GAP * 5)));
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
    CreateDone();
    int32_t index = 5;
    ScrollToIndex(index, false, ScrollAlign::START);
    EXPECT_TRUE(Position(-(ITEM_MAIN_SIZE * 4 + ROW_GAP * 3)));
    ScrollToIndex(index, false, ScrollAlign::CENTER);
    EXPECT_TRUE(Position(-(ITEM_MAIN_SIZE * 5.5 + ROW_GAP * 4)));
    ScrollToIndex(index, false, ScrollAlign::END);
    EXPECT_TRUE(Position(-(ITEM_MAIN_SIZE + ROW_GAP * 3)));
    ScrollToIndex(index, false, ScrollAlign::AUTO);
    EXPECT_TRUE(Position(-(ITEM_MAIN_SIZE + ROW_GAP * 3)));
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
    CreateDone();
    int32_t index = 5;
    ScrollToIndex(index, false, ScrollAlign::AUTO);
    EXPECT_TRUE(Position(-(ITEM_MAIN_SIZE * 3 + BIG_ROW_GAP * 2 - GRID_HEIGHT)));
    /**
     * @tc.cases: use ScrollTo to make item 5 in the last line, ScrollTo index:5, text ScrollAlign::AUTO
     * @tc.expected: scrollToIndex don't change grid offset
     */
    auto autoPosition = ITEM_MAIN_SIZE * 3 + BIG_ROW_GAP * 2 - GRID_HEIGHT + ITEM_MAIN_SIZE;
    pattern_->ScrollTo(autoPosition);
    FlushLayoutTask(frameNode_);
    ScrollToIndex(index, false, ScrollAlign::AUTO);
    EXPECT_TRUE(Position(-autoPosition));
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
    CreateDone();
    int32_t index = 5;
    auto endPosition = ITEM_MAIN_SIZE * 3 + BIG_ROW_GAP * 2 - GRID_HEIGHT;
    ScrollToIndex(index, false, ScrollAlign::CENTER);
    EXPECT_TRUE(Position(-(endPosition + (GRID_HEIGHT - ITEM_MAIN_SIZE) / 2)));
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
    CreateDone();
    auto position = ITEM_MAIN_SIZE + 5 * COL_GAP;
    pattern_->ScrollTo(position);
    FlushLayoutTask(frameNode_);
    int32_t index = 6;
    ScrollToIndex(index, false, ScrollAlign::AUTO);
    EXPECT_TRUE(Position(-position));
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
    CreateDone();
    std::optional<float> extraOffset = -200;
    ScrollToIndex(2, false, ScrollAlign::START, extraOffset);
    EXPECT_FLOAT_EQ(pattern_->GetTotalOffset(), 0);
    ScrollToIndex(17, false, ScrollAlign::START, extraOffset);
    EXPECT_FLOAT_EQ(pattern_->GetTotalOffset(), 600);
    ScrollToIndex(17, false, ScrollAlign::END, extraOffset);
    EXPECT_FLOAT_EQ(pattern_->GetTotalOffset(), 300);
    ScrollToIndex(LAST_ITEM, false, ScrollAlign::END, extraOffset);
    EXPECT_FLOAT_EQ(pattern_->GetTotalOffset(), 400);

    extraOffset = 200;
    ScrollToIndex(2, false, ScrollAlign::START, extraOffset);
    EXPECT_FLOAT_EQ(pattern_->GetTotalOffset(), 300);
    ScrollToIndex(2, false, ScrollAlign::END, extraOffset);
    EXPECT_FLOAT_EQ(pattern_->GetTotalOffset(), 0);
    ScrollToIndex(17, false, ScrollAlign::END, extraOffset);
    EXPECT_FLOAT_EQ(pattern_->GetTotalOffset(), 600);
    ScrollToIndex(LAST_ITEM, false, ScrollAlign::END, extraOffset);
    EXPECT_FLOAT_EQ(pattern_->GetTotalOffset(), 600);
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
    CreateDone();

    std::optional<float> extraOffset = -200;
    ScrollToIndex(2, true, ScrollAlign::START, extraOffset);
    EXPECT_FLOAT_EQ(pattern_->GetFinalPosition(), -100);
    ScrollToIndex(17, true, ScrollAlign::START, extraOffset);
    EXPECT_FLOAT_EQ(pattern_->GetFinalPosition(), 600);
    ScrollToIndex(17, true, ScrollAlign::END, extraOffset);
    EXPECT_FLOAT_EQ(pattern_->GetFinalPosition(), 300);
    ScrollToIndex(LAST_ITEM, true, ScrollAlign::END, extraOffset);
    EXPECT_FLOAT_EQ(pattern_->GetFinalPosition(), -200);

    extraOffset = 200;
    ScrollToIndex(2, true, ScrollAlign::START, extraOffset);
    EXPECT_FLOAT_EQ(pattern_->GetFinalPosition(), 300);
    ScrollToIndex(17, true, ScrollAlign::END, extraOffset);
    EXPECT_FLOAT_EQ(pattern_->GetFinalPosition(), 700);
    ScrollToIndex(LAST_ITEM, true, ScrollAlign::END, extraOffset);
    EXPECT_FLOAT_EQ(pattern_->GetFinalPosition(), 200);
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
    CreateDone();
    pattern_->ScrollTo(ITEM_MAIN_SIZE);
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
    CreateDone();
    pattern_->ScrollTo(ITEM_MAIN_SIZE);
    EXPECT_EQ(pattern_->GetGridLayoutInfo().currentOffset_, -ITEM_MAIN_SIZE);
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
    CreateDone();
    pattern_->ScrollTo(ITEM_MAIN_SIZE * 5);
    EXPECT_EQ(pattern_->GetGridLayoutInfo().currentOffset_, -ITEM_MAIN_SIZE * 5);
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
    CreateDone();
    EXPECT_FALSE(pattern_->isConfigScrollable_);

    pattern_->ScrollTo(ITEM_MAIN_SIZE * 5);
    EXPECT_EQ(pattern_->GetGridLayoutInfo().currentOffset_, 0);
}

/**
 * @tc.name: PositionController001
 * @tc.desc: Test positionController func in VERTICAL
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollerTestNg, PositionController001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. UnScrollable
     * @tc.expected: jumpIndex_ not change
     */
    GridModelNG model = CreateGrid();
    CreateFixedItems(14);
    CreateDone();
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
    CreateDone();
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
    CreateDone();
    controller = pattern_->positionController_;
    controller->ScrollToIndex(1, false, ScrollAlign::CENTER, std::nullopt);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetGridLayoutInfo().currentOffset_, 0);
    controller->ScrollToIndex(6, false, ScrollAlign::CENTER, std::nullopt);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetGridLayoutInfo().currentOffset_, 0);
    controller->ScrollToIndex(5, false, ScrollAlign::CENTER, std::nullopt);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetGridLayoutInfo().currentOffset_, -50);

    ClearOldNodes();
    model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    CreateFixedItems(10);
    CreateDone();
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
    CreateDone();
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
    CreateDone();
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
    CreateDone();
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
    CreateDone();
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
    CreateDone();
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
    CreateDone();
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
    CreateDone();
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
    CreateDone();

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
    CreateDone();

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
    pattern_->AnimateTo(ITEM_MAIN_SIZE * 2, 200.f, Curves::LINEAR, true);
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
    CreateDone();

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
    CreateDone();

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
    CreateFocusableGridItems(10, ITEM_MAIN_SIZE, ITEM_MAIN_SIZE);
    CreateDone();

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
    CreateDone();

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
    UpdateCurrentOffset(-50, SCROLL_FROM_UPDATE);
    EXPECT_EQ(pattern_->GetGridLayoutInfo().currentOffset_, -50);
    UpdateCurrentOffset(50, SCROLL_FROM_UPDATE);
    EXPECT_EQ(pattern_->GetGridLayoutInfo().currentOffset_, 0);
    UpdateCurrentOffset(-100, SCROLL_FROM_UPDATE);
    EXPECT_EQ(pattern_->GetGridLayoutInfo().currentOffset_, 0);
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
    UpdateCurrentOffset(-50, SCROLL_FROM_BAR);
    EXPECT_EQ(pattern_->GetGridLayoutInfo().currentOffset_, -50);
    UpdateCurrentOffset(50, SCROLL_FROM_BAR);
    EXPECT_EQ(pattern_->GetGridLayoutInfo().currentOffset_, 0);
    UpdateCurrentOffset(-100, SCROLL_FROM_BAR);
    EXPECT_EQ(pattern_->GetGridLayoutInfo().currentOffset_, 0);
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
    UpdateCurrentOffset(-50, SCROLL_FROM_UPDATE);
    EXPECT_EQ(pattern_->GetGridLayoutInfo().currentOffset_, -50);
    UpdateCurrentOffset(50, SCROLL_FROM_UPDATE);
    EXPECT_EQ(pattern_->GetGridLayoutInfo().currentOffset_, 0);
    UpdateCurrentOffset(-100, SCROLL_FROM_UPDATE);
    EXPECT_EQ(pattern_->GetGridLayoutInfo().currentOffset_, 0);
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
    EXPECT_EQ(pattern_->GetGridLayoutInfo().currentOffset_, 0);
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
    CreateGridItems(20, ITEM_MAIN_SIZE, NULL_VALUE, GridItemStyle::NONE);
    CreateDone();

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
    CreateGridItems(20, ITEM_MAIN_SIZE, NULL_VALUE, GridItemStyle::NONE);
    CreateDone();

    int32_t targetIndex = 15;
    ScrollAlign align = ScrollAlign::CENTER;

    pattern_->ScrollToIndex(targetIndex, true, align);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->finalPosition_, -200);
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
    CreateGridItems(20, ITEM_MAIN_SIZE, NULL_VALUE, GridItemStyle::NONE);
    CreateDone();

    int32_t targetIndex = 15;
    ScrollAlign align = ScrollAlign::END;

    pattern_->ScrollToIndex(targetIndex, true, align);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->finalPosition_, -400);
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
    CreateDone();

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
    EXPECT_EQ(pattern_->finalPosition_, 200);
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
    CreateGridItems(20, ITEM_MAIN_SIZE, NULL_VALUE, GridItemStyle::NONE);
    CreateDone();

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
    CreateDone();

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
    CreateGridItems(20, ITEM_MAIN_SIZE, NULL_VALUE, GridItemStyle::NONE);
    CreateDone();

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
const decltype(GridLayoutInfo::lineHeightMap_) cmp = { { 0, ITEM_MAIN_SIZE }, { 1, ITEM_MAIN_SIZE },
    { 2, ITEM_MAIN_SIZE }, { 3, ITEM_MAIN_SIZE }, { 6, ITEM_MAIN_SIZE }, { 7, ITEM_MAIN_SIZE }, { 8, ITEM_MAIN_SIZE },
    { 9, ITEM_MAIN_SIZE } };
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
    CreateDone();

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
        UpdateCurrentOffset(-100.0f);
    }
    if (SystemProperties::GetGridIrregularLayoutEnabled()) {
        EXPECT_EQ(info.startMainLineIndex_, 9);
    } else {
        EXPECT_EQ(info.startMainLineIndex_, 10);
    }
    EXPECT_EQ(info.endMainLineIndex_, 9);

    EXPECT_LT(info.currentOffset_, -75.0f);

    pattern_->ScrollToIndex(targetIndex, false, ScrollAlign::END);
    FlushLayoutTask(frameNode_);
    for (int i = 0; i < 10; ++i) {
        info.currentOffset_ -= 75.0f;
        frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
        FlushLayoutTask(frameNode_);
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
    pattern_->ScrollToIndex(targetIndex, false, align);
    FlushLayoutTask(frameNode_);
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
    CreateGridItem(60, 550);
    ViewStackProcessor::GetInstance()->Pop();
    ViewStackProcessor::GetInstance()->StopGetAccessRecording();
    CreateGridItems(20, 60, 390);
    CreateDone();

    // cache all line in Grid
    auto controller = pattern_->positionController_;
    controller->ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, true);
    FlushLayoutTask(frameNode_);
    controller->ScrollToEdge(ScrollEdgeType::SCROLL_TOP, false);
    FlushLayoutTask(frameNode_);

    controller->ScrollToIndex(5, false, ScrollAlign::AUTO, std::nullopt);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetGridLayoutInfo().currentOffset_, -550);

    controller->ScrollToEdge(ScrollEdgeType::SCROLL_TOP, true);
    FlushLayoutTask(frameNode_);

    controller->ScrollToIndex(7, false, ScrollAlign::AUTO, std::nullopt);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetGridLayoutInfo().currentOffset_, -390);

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
    CreateGridItems(3, 60.0f, 150.0f);

    CreateGridItem(60.0f, 550.0f);
    ViewStackProcessor::GetInstance()->Pop();
    ViewStackProcessor::GetInstance()->StopGetAccessRecording();

    CreateGridItems(20, 60.0f, 190.0f);
    CreateDone();

    // cache all line in Grid
    auto controller = pattern_->positionController_;
    controller->ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, true);
    FlushLayoutTask(frameNode_);
    controller->ScrollToEdge(ScrollEdgeType::SCROLL_TOP, false);
    FlushLayoutTask(frameNode_);

    controller->ScrollToIndex(5, false, ScrollAlign::AUTO, std::nullopt);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetGridLayoutInfo().currentOffset_, -150);

    controller->ScrollToEdge(ScrollEdgeType::SCROLL_TOP, true);
    FlushLayoutTask(frameNode_);

    controller->ScrollToIndex(7, false, ScrollAlign::AUTO, std::nullopt);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetGridLayoutInfo().currentOffset_, -350);

    controller->ScrollToEdge(ScrollEdgeType::SCROLL_TOP, true);
    FlushLayoutTask(frameNode_);

    controller->ScrollToIndex(9, false, ScrollAlign::AUTO, std::nullopt);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetGridLayoutInfo().currentOffset_, -550);
}
} // namespace OHOS::Ace::NG
