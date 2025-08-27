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

#include "core/components_ng/pattern/grid/grid_scroll/grid_scroll_layout_algorithm.h"
#include "core/components_ng/pattern/grid/grid_scroll/grid_scroll_with_options_layout_algorithm.h"

namespace OHOS::Ace::NG {
class GridScrollLayoutTestNg : public GridTestNg {
};

/**
 * @tc.name: GetStartingItem001
 * @tc.desc: Test GetStartingItem in GridScrollWithOptionsLayoutAlgorithm
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollLayoutTestNg, GetStartingItem001, TestSize.Level1)
{
    GridLayoutOptions option;
    option.regularSize.rows = 1;
    option.regularSize.columns = 1;
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr");
    model.SetLayoutOptions(option);
    model.SetEdgeEffect(EdgeEffect::SPRING, true);
    CreateFixedHeightItems(600, ITEM_MAIN_SIZE);
    CreateDone();

    ScrollToIndex(99, false, ScrollAlign::END);
    FlushUITasks();

    auto layoutAlgorithmWrapper = AceType::DynamicCast<LayoutAlgorithmWrapper>(frameNode_->GetLayoutAlgorithm());
    auto layoutAlgorithm =
        AceType::DynamicCast<GridScrollWithOptionsLayoutAlgorithm>(layoutAlgorithmWrapper->GetLayoutAlgorithm());

    layoutAlgorithm->info_.hasBigItem_ = true;
    EXPECT_EQ(layoutAlgorithm->GetStartingItem(AceType::RawPtr(frameNode_), 99), 99);
}

/**
 * @tc.name: ShowCache001
 * @tc.desc: Test show cache in Grid
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollLayoutTestNg, ShowCache001, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr");
    model.SetCachedCount(2, true);
    CreateBigItem(0, 0, 0, 2, NULL_VALUE, ITEM_MAIN_SIZE);
    CreateFixedHeightItems(14, ITEM_MAIN_SIZE);
    CreateDone();

    /**
     * @tc.steps: step1. Add item
     * @tc.expected: The added item in the correct position
     */
    for (int32_t i = 0; i < 5; i++) {
        GridItemModelNG itemModel;
        itemModel.Create(GridItemStyle::NONE);
        ViewAbstract::SetHeight(CalcLength(Dimension(ITEM_MAIN_SIZE)));
        RefPtr<UINode> currentNode = ViewStackProcessor::GetInstance()->Finish();
        auto currentFrameNode = AceType::DynamicCast<FrameNode>(currentNode);
        currentFrameNode->MountToParent(frameNode_);
    }
    frameNode_->ChildrenUpdatedFrom(17);
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    FlushUITasks();

    for (int i = 0; i <= 5; i++) {
        UpdateCurrentOffset(-15);
        FlushUITasks();
    }

    std::map<int32_t, std::map<int32_t, int32_t>> gridMatrix = { { 0, { { 0, 0 }, { 1, 0 }, { 2, 0 } } },
        { 1, { { 0, 1 }, { 1, 2 }, { 2, 3 } } }, { 2, { { 0, 4 }, { 1, 5 }, { 2, 6 } } },
        { 3, { { 0, 7 }, { 1, 8 }, { 2, 9 } } }, { 4, { { 0, 10 }, { 1, 11 }, { 2, 12 } } },
        { 5, { { 0, 13 }, { 1, 14 }, { 2, 15 } } }, { 6, { { 0, 16 }, { 1, 17 }, { 2, 18 } } } };
    EXPECT_EQ(pattern_->info_.gridMatrix_, gridMatrix);
}

/**
 * @tc.name: Remeasure001
 * @tc.desc: Test triggering measure multiple times on the same Algo object
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollLayoutTestNg, Remeasure001, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetCachedCount(0, false);
    CreateFixedItems(20);
    CreateDone();

    auto layoutAlgorithmWrapper = AceType::DynamicCast<LayoutAlgorithmWrapper>(frameNode_->GetLayoutAlgorithm());
    auto algo = AceType::DynamicCast<GridScrollLayoutAlgorithm>(layoutAlgorithmWrapper->GetLayoutAlgorithm());
    ASSERT_TRUE(algo);
    algo->Measure(AceType::RawPtr(frameNode_));
    EXPECT_TRUE(algo->unLayoutedItems_.empty());
    EXPECT_EQ(algo->info_.lastMainSize_, HEIGHT);

    auto layoutProperty = AceType::DynamicCast<GridLayoutProperty>(frameNode_->GetLayoutProperty());
    layoutProperty->layoutConstraint_->selfIdealSize.SetHeight(HEIGHT - 100);
    algo->Measure(AceType::RawPtr(frameNode_));
    EXPECT_EQ(algo->info_.lastMainSize_, HEIGHT - 100);
    EXPECT_EQ(algo->unLayoutedItems_.size(), 2);
    EXPECT_EQ(algo->unLayoutedItems_.count(7), 1);
    EXPECT_EQ(algo->unLayoutedItems_.count(6), 1);
}

/**
 * @tc.name: GetTotalHeight002
 * @tc.desc: Test GetTotalHeight when all items in viewport are irregular item
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollLayoutTestNg, GetTotalHeight002, TestSize.Level1)
{
    GridLayoutOptions option;
    option.regularSize.rows = 1;
    option.regularSize.columns = 1;
    option.irregularIndexes = { 0, 5, 8, 9, 10 };
    GridModelNG model = CreateGrid();
    model.SetLayoutOptions(option);
    model.SetColumnsTemplate("1fr 1fr");
    model.SetCachedCount(0, false);
    CreateFixedItems(9);
    CreateFixedHeightItems(1, 350);
    CreateFixedItems(1);
    CreateDone();

    ScrollToIndex(10, false, ScrollAlign::START);
    EXPECT_TRUE(GreatNotEqual(pattern_->GetTotalHeight(), pattern_->info_.lastMainSize_));
}

/**
 * @tc.name: Cache003
 * @tc.desc: Test Grid cached items.
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollLayoutTestNg, Cache003, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr");
    model.SetRowsGap(Dimension(5));
    model.SetCachedCount(1);
    model.SetLayoutOptions({});
    CreateItemsInLazyForEach(50, [](uint32_t idx) { return 50.0f; });
    CreateDone();

    GetItem(7, true)->GetLayoutProperty()->UpdatePropertyChangeFlag(PROPERTY_UPDATE_LAYOUT);
    EXPECT_EQ(pattern_->info_.startIndex_, 0);
    EXPECT_EQ(pattern_->info_.endIndex_, 23);
    UpdateCurrentOffset(-200.0f);
    EXPECT_EQ(pattern_->info_.startIndex_, 9);
    EXPECT_EQ(pattern_->info_.endIndex_, 32);
    EXPECT_NE(GetItem(7, true)->GetLayoutProperty()->GetPropertyChangeFlag(), 0);
    PipelineContext::GetCurrentContext()->OnIdle(INT64_MAX);
    EXPECT_TRUE(GetItem(6, true));
    EXPECT_FALSE(GetItem(5, true));
    EXPECT_NE(GetItem(7, true)->GetLayoutProperty()->GetPropertyChangeFlag(), 0);

    UpdateCurrentOffset(60.0f);
    PipelineContext::GetCurrentContext()->OnIdle(INT64_MAX);
    EXPECT_EQ(pattern_->info_.startIndex_, 6);
    ASSERT_TRUE(GetItem(5, true));
    EXPECT_FALSE(GetItem(5, true)->IsOnMainTree());
    EXPECT_NE(GetItem(5, true)->GetLayoutProperty()->GetPropertyChangeFlag(), 0);

    GetItem(5, true)->GetLayoutProperty()->UpdatePropertyChangeFlag(PROPERTY_UPDATE_LAYOUT);
    GetItem(5, true)->SetActive(true); // ::Layout would reset PropertyFlag if item is active
    UpdateCurrentOffset(1.0f);
    EXPECT_EQ(pattern_->info_.startIndex_, 6);
    EXPECT_FALSE(GetItem(5, true)->IsOnMainTree());
    EXPECT_TRUE(GetItem(5, true)->GetLayoutProperty()->GetPropertyChangeFlag() & PROPERTY_UPDATE_LAYOUT);
}

/**
 * @tc.name: FadingEdge003
 * @tc.desc: Test FadingEdge property with safe area
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollLayoutTestNg, FadingEdge003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set FadingEdge
     * @tc.expected: Would create a overlayNode attach to list
     */
    const Dimension fadingEdgeLength = Dimension(10.0f);
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetLayoutOptions({});
    ScrollableModelNG::SetFadingEdge(true, fadingEdgeLength);
    CreateFixedItems(20);
    CreateDone();
    EXPECT_TRUE(frameNode_->GetOverlayNode());
    auto geo = frameNode_->GetOverlayNode()->GetGeometryNode();
    EXPECT_EQ(geo->GetFrameSize().Height(), 400.f);

    /**
     * @tc.steps: step2. Update Safe Area
     * @tc.expected: overlay frame size expand safe area.
     */
    frameNode_->GetGeometryNode()->SetSelfAdjust(RectF(0, 0, 0, 10.f));
    FlushUITasks(frameNode_);
    geo = frameNode_->GetOverlayNode()->GetGeometryNode();
    EXPECT_EQ(geo->GetFrameSize().Height(), 410.f);
}

/**
 * @tc.name: ContentOffset001
 * @tc.desc: Test Grid ContentStartOffset and ContentEndOffset.
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollLayoutTestNg, ContentOffset001, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr");
    model.SetLayoutOptions({});
    float contentOffset = 20;
    ScrollableModelNG::SetContentStartOffset(contentOffset);
    ScrollableModelNG::SetContentEndOffset(contentOffset * 1.5);
    CreateFixedItems(20);
    CreateDone();

    EXPECT_EQ(layoutProperty_->GetContentStartOffset(), contentOffset);
    EXPECT_EQ(layoutProperty_->GetContentEndOffset(), contentOffset * 1.5);
}

/**
 * @tc.name: ContentOffset001
 * @tc.desc: Test Grid ContentStartOffset and ContentEndOffset.
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollLayoutTestNg, ContentOffset002, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr");
    model.SetLayoutOptions({});
    float contentOffset = 20;
    ScrollableModelNG::SetContentStartOffset(contentOffset);
    ScrollableModelNG::SetContentEndOffset(contentOffset * 1.5);
    CreateFixedItems(20);
    CreateDone();

    ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, false);
    EXPECT_EQ(pattern_->GetTotalOffset(), ITEM_MAIN_SIZE * 16 + contentOffset * 1.5);
    EXPECT_EQ(pattern_->GetTotalHeight(), ITEM_MAIN_SIZE * 20 + contentOffset * 2.5);

    ScrollToEdge(ScrollEdgeType::SCROLL_TOP, false);
    EXPECT_EQ(pattern_->GetTotalOffset(), -20.0f);
    EXPECT_EQ(pattern_->info_.currentOffset_, contentOffset);
}
} // namespace OHOS::Ace::NG
 