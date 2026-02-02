/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "custom_layout_options.h"
#include "test/mock/core/animation/mock_animation_manager.h"
#include "test/unittest/core/pattern/grid/grid_test_ng.h"

#include "core/components_ng/pattern/grid/grid_custom/grid_custom_layout_algorithm.h"

namespace OHOS::Ace::NG {
class GridCustomScrollerTestNg : public GridTestNg {};

/**
 * @tc.name: ScrollToIndexStartWithContentOffset
 * @tc.desc: Test ScrollToIndex with ContentOffset and ScrollAlign::Start without animation
 * @tc.type: FUNC
 */
HWTEST_F(GridCustomScrollerTestNg, ScrollToIndexStartWithContentOffsetTest, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetLayoutOptions(GetRegularDemoOptions(2, ITEM_MAIN_SIZE));
    ScrollableModelNG::SetContentStartOffset(CONTENT_START_OFFSET);
    ScrollableModelNG::SetContentEndOffset(CONTENT_END_OFFSET);
    CreateFixedItems(20);
    CreateDone();
    ScrollAlign scrollAlign = ScrollAlign::START;
    bool smooth = false;
    ScrollToIndex(19, smooth, scrollAlign);
    EXPECT_EQ(pattern_->info_.currentOffset_, -CONTENT_END_OFFSET);
    EXPECT_EQ(pattern_->info_.prevOffset_, -CONTENT_END_OFFSET);
    EXPECT_EQ(pattern_->GetTotalOffset(), 630);

    ScrollToIndex(5, smooth, scrollAlign);
    EXPECT_EQ(pattern_->info_.currentOffset_, -ITEM_MAIN_SIZE + CONTENT_START_OFFSET);
    EXPECT_EQ(pattern_->info_.prevOffset_, -ITEM_MAIN_SIZE + CONTENT_START_OFFSET);
    EXPECT_EQ(pattern_->GetTotalOffset(), 180);

    ScrollToIndex(13, smooth, scrollAlign);
    EXPECT_EQ(pattern_->info_.currentOffset_, -ITEM_MAIN_SIZE + CONTENT_START_OFFSET);
    EXPECT_EQ(pattern_->info_.prevOffset_, -ITEM_MAIN_SIZE + CONTENT_START_OFFSET);
    EXPECT_EQ(pattern_->GetTotalOffset(), 580);

    ScrollToIndex(17, smooth, scrollAlign);
    EXPECT_EQ(pattern_->info_.currentOffset_, -CONTENT_END_OFFSET);
    EXPECT_EQ(pattern_->info_.prevOffset_, -CONTENT_END_OFFSET);
    EXPECT_EQ(pattern_->GetTotalOffset(), 630);

    ScrollToIndex(0, smooth, scrollAlign);
    EXPECT_EQ(pattern_->info_.currentOffset_, CONTENT_START_OFFSET);
    EXPECT_EQ(pattern_->info_.prevOffset_, CONTENT_START_OFFSET);
    EXPECT_EQ(pattern_->GetTotalOffset(), -20);
}

/**
 * @tc.name: AnimateToIndexStartWithContentOffsetTest
 * @tc.desc: Test ScrollToIndex with ContentOffset and ScrollAlign::Start with animation
 * @tc.type: FUNC
 */
HWTEST_F(GridCustomScrollerTestNg, AnimateToIndexStartWithContentOffsetTest, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetLayoutOptions(GetRegularDemoOptions(2, ITEM_MAIN_SIZE));
    ScrollableModelNG::SetContentStartOffset(CONTENT_START_OFFSET);
    ScrollableModelNG::SetContentEndOffset(CONTENT_END_OFFSET);
    CreateFixedItems(20);
    CreateDone();
    ScrollAlign scrollAlign = ScrollAlign::START;

    AnimateToIndexWithTicks(19, scrollAlign);
    EXPECT_EQ(pattern_->info_.currentOffset_, -CONTENT_END_OFFSET);
    EXPECT_EQ(pattern_->GetTotalOffset(), 630);

    AnimateToIndexWithTicks(5, scrollAlign);
    EXPECT_EQ(pattern_->info_.currentOffset_, -ITEM_MAIN_SIZE + CONTENT_START_OFFSET);
    EXPECT_EQ(pattern_->GetTotalOffset(), 180);

    AnimateToIndexWithTicks(13, scrollAlign);
    EXPECT_EQ(pattern_->info_.currentOffset_, -ITEM_MAIN_SIZE + CONTENT_START_OFFSET);
    EXPECT_EQ(pattern_->GetTotalOffset(), 580);

    AnimateToIndexWithTicks(17, scrollAlign);
    EXPECT_EQ(pattern_->info_.currentOffset_, -CONTENT_END_OFFSET);
    EXPECT_EQ(pattern_->GetTotalOffset(), 630);

    AnimateToIndexWithTicks(0, scrollAlign);
    EXPECT_EQ(pattern_->info_.currentOffset_, CONTENT_START_OFFSET);
    EXPECT_EQ(pattern_->GetTotalOffset(), -20);
}

/**
 * @tc.name: ScrollToIndexEndWithContentOffset
 * @tc.desc: Test ScrollToIndex with ContentOffset and ScrollAlign::End without animation
 * @tc.type: FUNC
 */
HWTEST_F(GridCustomScrollerTestNg, ScrollToIndexEndWithContentOffsetTest, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetLayoutOptions(GetRegularDemoOptions(2, ITEM_MAIN_SIZE));
    ScrollableModelNG::SetContentStartOffset(CONTENT_START_OFFSET);
    ScrollableModelNG::SetContentEndOffset(CONTENT_END_OFFSET);
    CreateFixedItems(20);
    CreateDone();
    ScrollAlign scrollAlign = ScrollAlign::END;
    bool smooth = false;

    ScrollToIndex(19, smooth, scrollAlign);
    EXPECT_EQ(pattern_->info_.currentOffset_, -CONTENT_END_OFFSET);
    EXPECT_EQ(pattern_->GetTotalOffset(), 630);

    ScrollToIndex(5, smooth, scrollAlign);
    EXPECT_EQ(pattern_->info_.currentOffset_, CONTENT_START_OFFSET);
    EXPECT_EQ(pattern_->GetTotalOffset(), -20);

    ScrollToIndex(13, smooth, scrollAlign);
    EXPECT_EQ(pattern_->info_.currentOffset_, -CONTENT_END_OFFSET);
    EXPECT_EQ(pattern_->GetTotalOffset(), 330);

    ScrollToIndex(17, smooth, scrollAlign);
    EXPECT_EQ(pattern_->info_.currentOffset_, -CONTENT_END_OFFSET);
    EXPECT_EQ(pattern_->GetTotalOffset(), 530);

    ScrollToIndex(0, smooth, scrollAlign);
    EXPECT_EQ(pattern_->info_.currentOffset_, CONTENT_START_OFFSET);
    EXPECT_EQ(pattern_->GetTotalOffset(), -20);
}

/**
 * @tc.name: AnimateToIndexEndWithContentOffsetTest
 * @tc.desc: Test ScrollToIndex with ContentOffset and ScrollAlign::End with animation
 * @tc.type: FUNC
 */
HWTEST_F(GridCustomScrollerTestNg, AnimateToIndexEndWithContentOffsetTest, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetLayoutOptions(GetRegularDemoOptions(2, ITEM_MAIN_SIZE));
    ScrollableModelNG::SetContentStartOffset(CONTENT_START_OFFSET);
    ScrollableModelNG::SetContentEndOffset(CONTENT_END_OFFSET);
    CreateFixedItems(20);
    CreateDone();
    ScrollAlign scrollAlign = ScrollAlign::END;

    AnimateToIndexWithTicks(19, scrollAlign);
    EXPECT_EQ(pattern_->info_.currentOffset_, -CONTENT_END_OFFSET);
    EXPECT_EQ(pattern_->GetTotalOffset(), 630);

    AnimateToIndexWithTicks(5, scrollAlign);
    EXPECT_EQ(pattern_->info_.currentOffset_, CONTENT_START_OFFSET);
    EXPECT_EQ(pattern_->GetTotalOffset(), -20);

    AnimateToIndexWithTicks(13, scrollAlign);
    EXPECT_EQ(pattern_->info_.currentOffset_, -CONTENT_END_OFFSET);
    EXPECT_EQ(pattern_->GetTotalOffset(), 330);

    AnimateToIndexWithTicks(17, scrollAlign);
    EXPECT_EQ(pattern_->info_.currentOffset_, -CONTENT_END_OFFSET);
    EXPECT_EQ(pattern_->GetTotalOffset(), 530);

    AnimateToIndexWithTicks(0, scrollAlign);
    EXPECT_EQ(pattern_->info_.currentOffset_, CONTENT_START_OFFSET);
    EXPECT_EQ(pattern_->GetTotalOffset(), -20);
}

/**
 * @tc.name: ScrollToIndexAutoWithContentOffset
 * @tc.desc: Test ScrollToIndex with ContentOffset and ScrollAlign::Auto without animation
 * @tc.type: FUNC
 */
HWTEST_F(GridCustomScrollerTestNg, ScrollToIndexAutoWithContentOffsetTest, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetLayoutOptions(GetRegularDemoOptions(2, ITEM_MAIN_SIZE));
    ScrollableModelNG::SetContentStartOffset(CONTENT_START_OFFSET);
    ScrollableModelNG::SetContentEndOffset(CONTENT_END_OFFSET);
    CreateFixedItems(20);
    CreateDone();
    ScrollAlign scrollAlign = ScrollAlign::AUTO;
    bool smooth = false;

    ScrollToIndex(19, smooth, scrollAlign);
    EXPECT_EQ(pattern_->info_.currentOffset_, -CONTENT_END_OFFSET);
    EXPECT_EQ(pattern_->GetTotalOffset(), 630);

    // Scroll forward, item 5 is at top
    ScrollToIndex(5, smooth, scrollAlign);
    EXPECT_EQ(pattern_->info_.currentOffset_, -ITEM_MAIN_SIZE + CONTENT_START_OFFSET);
    EXPECT_EQ(pattern_->GetTotalOffset(), 180);

    // Scroll backward, item 13 is at end
    ScrollToIndex(13, smooth, scrollAlign);
    EXPECT_EQ(pattern_->info_.currentOffset_, -CONTENT_END_OFFSET);
    EXPECT_EQ(pattern_->GetTotalOffset(), 330);

    // item 11 is in view
    ScrollToIndex(11, smooth, scrollAlign);
    EXPECT_EQ(pattern_->info_.currentOffset_, -CONTENT_END_OFFSET);
    EXPECT_EQ(pattern_->GetTotalOffset(), 330);

    ScrollBy(0, -CONTENT_END_OFFSET);
    EXPECT_EQ(pattern_->info_.currentOffset_, 0);
    EXPECT_EQ(pattern_->info_.startIndex_, 6);
    EXPECT_EQ(pattern_->info_.endIndex_, 13);
    ScrollToIndex(7, smooth, scrollAlign);
    EXPECT_EQ(pattern_->info_.currentOffset_, -ITEM_MAIN_SIZE + CONTENT_START_OFFSET);
    EXPECT_EQ(pattern_->GetTotalOffset(), 280);

    ScrollTo(300);
    EXPECT_EQ(pattern_->info_.currentOffset_, 0);
    EXPECT_EQ(pattern_->info_.startIndex_, 6);
    EXPECT_EQ(pattern_->info_.endIndex_, 13);
    ScrollToIndex(13, false, scrollAlign);
    EXPECT_EQ(pattern_->info_.currentOffset_, -CONTENT_END_OFFSET);
    EXPECT_EQ(pattern_->GetTotalOffset(), 330);

    ScrollToIndex(0, smooth, scrollAlign);
    EXPECT_EQ(pattern_->info_.currentOffset_, CONTENT_START_OFFSET);
    EXPECT_EQ(pattern_->GetTotalOffset(), -20);
}

/**
 * @tc.name: AnimateToIndexAutoWithContentOffsetTest
 * @tc.desc: Test ScrollToIndex with ContentOffset and ScrollAlign::Auto with animation
 * @tc.type: FUNC
 */
HWTEST_F(GridCustomScrollerTestNg, AnimateToIndexAutoWithContentOffsetTest, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetLayoutOptions(GetRegularDemoOptions(2, ITEM_MAIN_SIZE));
    ScrollableModelNG::SetContentStartOffset(CONTENT_START_OFFSET);
    ScrollableModelNG::SetContentEndOffset(CONTENT_END_OFFSET);
    CreateFixedItems(20);
    CreateDone();
    ScrollAlign scrollAlign = ScrollAlign::AUTO;

    AnimateToIndexWithTicks(19, scrollAlign);
    EXPECT_EQ(pattern_->info_.currentOffset_, -CONTENT_END_OFFSET);
    EXPECT_EQ(pattern_->GetTotalOffset(), 630);

    AnimateToIndexWithTicks(5, scrollAlign);
    EXPECT_EQ(pattern_->info_.currentOffset_, -ITEM_MAIN_SIZE + CONTENT_START_OFFSET);
    EXPECT_EQ(pattern_->GetTotalOffset(), 180);

    AnimateToIndexWithTicks(13, scrollAlign);
    EXPECT_EQ(pattern_->info_.currentOffset_, -CONTENT_END_OFFSET);
    EXPECT_EQ(pattern_->GetTotalOffset(), 330);

    AnimateToIndexWithTicks(11, scrollAlign);
    EXPECT_EQ(pattern_->info_.currentOffset_, -CONTENT_END_OFFSET);
    EXPECT_EQ(pattern_->GetTotalOffset(), 330);

    ScrollBy(0, -CONTENT_END_OFFSET);
    EXPECT_EQ(pattern_->info_.currentOffset_, 0);
    EXPECT_EQ(pattern_->info_.startIndex_, 6);
    EXPECT_EQ(pattern_->info_.endIndex_, 13);
    AnimateToIndexWithTicks(7, scrollAlign);
    EXPECT_EQ(pattern_->info_.currentOffset_, -ITEM_MAIN_SIZE + CONTENT_START_OFFSET);
    EXPECT_EQ(pattern_->GetTotalOffset(), 280);

    ScrollTo(300);
    EXPECT_EQ(pattern_->info_.currentOffset_, 0);
    EXPECT_EQ(pattern_->info_.startIndex_, 6);
    EXPECT_EQ(pattern_->info_.endIndex_, 13);
    AnimateToIndexWithTicks(13, scrollAlign);
    EXPECT_EQ(pattern_->info_.currentOffset_, -CONTENT_END_OFFSET);
    EXPECT_EQ(pattern_->GetTotalOffset(), 330);

    AnimateToIndexWithTicks(0, scrollAlign);
    EXPECT_EQ(pattern_->info_.currentOffset_, CONTENT_START_OFFSET);
    EXPECT_EQ(pattern_->GetTotalOffset(), -20);
}

/**
 * @tc.name: ScrollToIndexStart
 * @tc.desc: Test ScrollToIndex with ScrollAlign::Start without animation
 * @tc.type: FUNC
 */
HWTEST_F(GridCustomScrollerTestNg, ScrollToIndexStartTest, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetLayoutOptions(GetRegularDemoOptions(2, ITEM_MAIN_SIZE));
    CreateFixedItems(20);
    CreateDone();
    ScrollAlign scrollAlign = ScrollAlign::START;
    bool smooth = false;
    ScrollToIndex(19, smooth, scrollAlign);
    EXPECT_EQ(pattern_->info_.currentOffset_, 0.f);
    EXPECT_EQ(pattern_->info_.prevOffset_, 0.f);
    EXPECT_EQ(pattern_->GetTotalOffset(), 600);

    ScrollToIndex(5, smooth, scrollAlign);
    EXPECT_EQ(pattern_->info_.currentOffset_, 0.f);
    EXPECT_EQ(pattern_->info_.prevOffset_, 0.f);
    EXPECT_EQ(pattern_->GetTotalOffset(), 200);

    ScrollToIndex(13, smooth, scrollAlign);
    EXPECT_EQ(pattern_->info_.currentOffset_, 0.f);
    EXPECT_EQ(pattern_->info_.prevOffset_, 0.f);
    EXPECT_EQ(pattern_->GetTotalOffset(), 600);
    ScrollToIndex(17, smooth, scrollAlign);
    EXPECT_EQ(pattern_->info_.currentOffset_, 0.f);
    EXPECT_EQ(pattern_->info_.prevOffset_, 0.f);
    EXPECT_EQ(pattern_->GetTotalOffset(), 600);

    ScrollToIndex(0, smooth, scrollAlign);
    EXPECT_EQ(pattern_->info_.currentOffset_, 0.f);
    EXPECT_EQ(pattern_->info_.prevOffset_, 0.f);
    EXPECT_EQ(pattern_->GetTotalOffset(), 0.f);
}

/**
 * @tc.name: ScrollToIndexCenter
 * @tc.desc: Test ScrollToIndex with ScrollAlign::Center without animation
 * @tc.type: FUNC
 */
HWTEST_F(GridCustomScrollerTestNg, ScrollToIndexCenterTest, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetLayoutOptions(GetRegularDemoOptions(2, ITEM_MAIN_SIZE));
    CreateFixedItems(20);
    CreateDone();
    ScrollAlign scrollAlign = ScrollAlign::CENTER;
    bool smooth = false;
    ScrollToIndex(19, smooth, scrollAlign);
    EXPECT_EQ(pattern_->info_.currentOffset_, 0.f);
    EXPECT_EQ(pattern_->info_.prevOffset_, 0.f);
    EXPECT_EQ(pattern_->GetTotalOffset(), 600);

    ScrollToIndex(5, smooth, scrollAlign);
    EXPECT_EQ(pattern_->info_.currentOffset_, -50.f);
    EXPECT_EQ(pattern_->info_.prevOffset_, -50.f);
    EXPECT_EQ(pattern_->GetTotalOffset(), 50);

    ScrollToIndex(13, smooth, scrollAlign);
    EXPECT_EQ(pattern_->info_.currentOffset_, -50.f);
    EXPECT_EQ(pattern_->info_.prevOffset_, -50.f);
    EXPECT_EQ(pattern_->GetTotalOffset(), 450);
    ScrollToIndex(17, smooth, scrollAlign);
    EXPECT_EQ(pattern_->info_.currentOffset_, 0.f);
    EXPECT_EQ(pattern_->info_.prevOffset_, 0.f);
    EXPECT_EQ(pattern_->GetTotalOffset(), 600);
    ScrollToIndex(0, smooth, scrollAlign);
    EXPECT_EQ(pattern_->info_.currentOffset_, 0.f);
    EXPECT_EQ(pattern_->info_.prevOffset_, 0.f);
    EXPECT_EQ(pattern_->GetTotalOffset(), 0.f);
}

/**
 * @tc.name: ScrollToIndexEnd
 * @tc.desc: Test ScrollToIndex with ScrollAlign::End without animation
 * @tc.type: FUNC
 */
HWTEST_F(GridCustomScrollerTestNg, ScrollToIndexEndTest, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetLayoutOptions(GetRegularDemoOptions(2, ITEM_MAIN_SIZE));
    CreateFixedItems(20);
    CreateDone();
    ScrollAlign scrollAlign = ScrollAlign::END;
    bool smooth = false;
    ScrollToIndex(19, smooth, scrollAlign);
    EXPECT_EQ(pattern_->info_.currentOffset_, 0.f);
    EXPECT_EQ(pattern_->info_.prevOffset_, 0.f);
    EXPECT_EQ(pattern_->GetTotalOffset(), 600);

    ScrollToIndex(5, smooth, scrollAlign);
    EXPECT_EQ(pattern_->info_.currentOffset_, 0.f);
    EXPECT_EQ(pattern_->info_.prevOffset_, 0.f);
    EXPECT_EQ(pattern_->GetTotalOffset(), 0);

    ScrollToIndex(13, smooth, scrollAlign);
    EXPECT_EQ(pattern_->info_.currentOffset_, 0.f);
    EXPECT_EQ(pattern_->info_.prevOffset_, 0.f);
    EXPECT_EQ(pattern_->GetTotalOffset(), 300);

    ScrollToIndex(17, smooth, scrollAlign);
    EXPECT_EQ(pattern_->info_.currentOffset_, 0.f);
    EXPECT_EQ(pattern_->info_.prevOffset_, 0.f);
    EXPECT_EQ(pattern_->GetTotalOffset(), 500);
    ScrollToIndex(0, smooth, scrollAlign);
    EXPECT_EQ(pattern_->info_.currentOffset_, 0.f);
    EXPECT_EQ(pattern_->info_.prevOffset_, 0.f);
    EXPECT_EQ(pattern_->GetTotalOffset(), 0.f);
}

/**
 * @tc.name: ScrollEdgeWithoutAnimationTest
 * @tc.desc: Test ScrollEdge without animation
 * @tc.type: FUNC
 */
HWTEST_F(GridCustomScrollerTestNg, ScrollEdgeWithoutAnimationTest, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetLayoutOptions(GetRegularDemoOptions(2, ITEM_MAIN_SIZE));
    CreateFixedItems(20);
    CreateDone();
    bool smooth = false;
    ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, smooth);
    EXPECT_EQ(pattern_->info_.currentOffset_, 0.f);
    EXPECT_EQ(pattern_->info_.prevOffset_, 0.f);
    EXPECT_EQ(pattern_->GetTotalOffset(), 600);

    ScrollToEdge(ScrollEdgeType::SCROLL_TOP, smooth);
    EXPECT_EQ(pattern_->info_.currentOffset_, 0.f);
    EXPECT_EQ(pattern_->info_.prevOffset_, 0.f);
    EXPECT_EQ(pattern_->GetTotalOffset(), 0);
}

/**
 * @tc.name: ScrollEdgeWithAnimationTest
 * @tc.desc: Test ScrollEdge with animation
 * @tc.type: FUNC
 */
HWTEST_F(GridCustomScrollerTestNg, ScrollEdgeWithAnimationTest, TestSize.Level1)
{
    MockAnimationManager::GetInstance().Reset();
    MockAnimationManager::GetInstance().SetTicks(10);
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetLayoutOptions(GetRegularDemoOptions(2, ITEM_MAIN_SIZE));
    CreateFixedItems(20);
    CreateDone();
    bool smooth = true;
    ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, smooth);
    TickToFinish();
    EXPECT_EQ(pattern_->info_.currentOffset_, 0.f);
    EXPECT_EQ(pattern_->info_.prevOffset_, 0.f);
    EXPECT_EQ(pattern_->GetTotalOffset(), 600);

    ScrollToEdge(ScrollEdgeType::SCROLL_TOP, smooth);
    TickToFinish();
    EXPECT_EQ(pattern_->info_.currentOffset_, 0.f);
    EXPECT_EQ(pattern_->info_.prevOffset_, 0.f);
    EXPECT_EQ(pattern_->GetTotalOffset(), 0);
}

/**
 * @tc.name: ScrollEdgeWithContentOffsetTest
 * @tc.desc: Test ScrollEdge with ContentOffset
 * @tc.type: FUNC
 */
HWTEST_F(GridCustomScrollerTestNg, ScrollEdgeWithContentOffsetTest, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetLayoutOptions(GetRegularDemoOptions(2, ITEM_MAIN_SIZE));
    ScrollableModelNG::SetContentStartOffset(CONTENT_START_OFFSET);
    ScrollableModelNG::SetContentEndOffset(CONTENT_END_OFFSET);
    CreateFixedItems(20);
    CreateDone();
    bool smooth = false;
    ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, smooth);
    EXPECT_EQ(pattern_->info_.currentOffset_, -30.f);
    EXPECT_EQ(pattern_->info_.prevOffset_, -30.f);
    EXPECT_EQ(pattern_->GetTotalOffset(), 630);

    ScrollToEdge(ScrollEdgeType::SCROLL_TOP, smooth);
    EXPECT_EQ(pattern_->info_.currentOffset_, 20.f);
    EXPECT_EQ(pattern_->info_.prevOffset_, 20.f);
    EXPECT_EQ(pattern_->GetTotalOffset(), -20);

    smooth = true;
    ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, smooth);
    TickToFinish();
    EXPECT_EQ(pattern_->info_.currentOffset_, -30.f);
    EXPECT_EQ(pattern_->info_.prevOffset_, -30.f);
    EXPECT_EQ(pattern_->GetTotalOffset(), 630);

    ScrollToEdge(ScrollEdgeType::SCROLL_TOP, smooth);
    TickToFinish();
    EXPECT_EQ(pattern_->info_.currentOffset_, 20.f);
    EXPECT_EQ(pattern_->info_.prevOffset_, 20.f);
    EXPECT_EQ(pattern_->GetTotalOffset(), -20);
}

/**
 * @tc.name: ScrollToIndexStart
 * @tc.desc: Test ScrollToIndex with ScrollAlign::Start without animation
 * @tc.type: FUNC
 */
HWTEST_F(GridCustomScrollerTestNg, IrregularScrollToIndexStartTest, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr");
    model.SetLayoutOptions(Get3LinesIrregularDemoOptions(50, ITEM_MAIN_SIZE));
    CreateItemsInLazyForEach(50, [](uint32_t idx) { return idx % 3 == 0 ? ITEM_MAIN_SIZE * 2 : ITEM_MAIN_SIZE; });
    CreateDone();
    ScrollAlign scrollAlign = ScrollAlign::START;
    bool smooth = false;
    ScrollToIndex(20, smooth, scrollAlign);
    EXPECT_EQ(pattern_->info_.currentOffset_, -100.f);
    EXPECT_EQ(pattern_->info_.prevOffset_, -100.f);
    EXPECT_EQ(pattern_->GetTotalOffset(), 1300);
    EXPECT_EQ(pattern_->info_.startIndex_, 18);
}
} // namespace OHOS::Ace::NG
