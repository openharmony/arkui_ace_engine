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

#include "grid_test_ng.h"

#include "core/components_ng/pattern/grid/grid_item_layout_property.h"

namespace OHOS::Ace::NG {

namespace {} // namespace

class GridCacheLayoutTestNg : public GridTestNg {
public:
    void CreateItems1();
    void CreateItems2();
};

void GridCacheLayoutTestNg::CreateItems1()
{
    /**
     * 0:  [0],  [0],  [0],  [0]
     * 1:  [1],  [1],  [1],  [1]
     * 2:  [2],  [2],  [2],  [2]
     * 3:  [3],  [3],  [4],  [4]
     * 4:  [5],  [6],  [4],  [4]
     * 5:  [7],  [8],  [9],  [9]
     * 6:  [10], [11], [12], [13]
     * 7:  [14], [14], [14], [14]
     * 8:  [15], [15], [16], [17]
     * 9:  [18], [18], [18], [18]
     */
    CreateBigItem(0, 0, 0, 3, ITEM_WIDTH, ITEM_HEIGHT);
    CreateBigItem(1, 1, 0, 3, ITEM_WIDTH, ITEM_HEIGHT);
    CreateBigItem(2, 2, 0, 3, ITEM_WIDTH, ITEM_HEIGHT);
    CreateBigItem(3, 3, 0, 1, ITEM_WIDTH, ITEM_HEIGHT);
    CreateBigItem(3, 4, 2, 3, ITEM_WIDTH, ITEM_HEIGHT * 2);
    CreateBigItem(4, 4, 0, 0, ITEM_WIDTH, ITEM_HEIGHT);
    CreateBigItem(4, 4, 1, 1, ITEM_WIDTH, ITEM_HEIGHT);
    CreateBigItem(5, 5, 0, 0, ITEM_WIDTH, ITEM_HEIGHT);
    CreateBigItem(5, 5, 1, 1, ITEM_WIDTH, ITEM_HEIGHT);
    CreateBigItem(5, 5, 2, 3, ITEM_WIDTH, ITEM_HEIGHT);
    CreateBigItem(6, 6, 0, 0, ITEM_WIDTH, ITEM_HEIGHT);
    CreateBigItem(6, 6, 1, 1, ITEM_WIDTH, ITEM_HEIGHT);
    CreateBigItem(6, 6, 2, 2, ITEM_WIDTH, ITEM_HEIGHT);
    CreateBigItem(6, 6, 3, 3, ITEM_WIDTH, ITEM_HEIGHT);
    CreateBigItem(7, 7, 0, 3, ITEM_WIDTH, ITEM_HEIGHT);
    CreateBigItem(8, 8, 0, 1, ITEM_WIDTH, ITEM_HEIGHT);
    CreateBigItem(8, 8, 2, 2, ITEM_WIDTH, ITEM_HEIGHT);
    CreateBigItem(8, 8, 3, 3, ITEM_WIDTH, ITEM_HEIGHT);
    CreateBigItem(9, 9, 0, 3, ITEM_WIDTH, ITEM_HEIGHT);
}

void GridCacheLayoutTestNg::CreateItems2()
{
    /**
     * 0:  [0],  [0],  [0],  [0],  [0],  [0]
     * 1:  [1],  [1],  [1],  [1],  [2],  [2]
     * 2:  [3],  [3],  [4],  [5],  [2],  [2]
     * 3:  [6],  [7],  [8],  [8],  [9],  [10]
     * 4:  [11], [12], [13], [13], [14], [15]
     * 5:  [16], [16], [16], [16], [17], [17]
     * 6:  [18], [18], [18], [18]
     */
    CreateBigItem(0, 0, 0, 5, ITEM_WIDTH, ITEM_HEIGHT);
    CreateBigItem(1, 1, 0, 3, ITEM_WIDTH, ITEM_HEIGHT);
    CreateBigItem(1, 2, 4, 5, ITEM_WIDTH, ITEM_HEIGHT * 2);
    CreateBigItem(2, 2, 0, 1, ITEM_WIDTH, ITEM_HEIGHT);
    CreateBigItem(2, 2, 2, 2, ITEM_WIDTH, ITEM_HEIGHT);
    CreateBigItem(2, 2, 3, 3, ITEM_WIDTH, ITEM_HEIGHT);
    CreateBigItem(3, 3, 0, 0, ITEM_WIDTH, ITEM_HEIGHT);
    CreateBigItem(3, 3, 1, 1, ITEM_WIDTH, ITEM_HEIGHT);
    CreateBigItem(3, 3, 2, 3, ITEM_WIDTH, ITEM_HEIGHT);
    CreateBigItem(3, 3, 4, 4, ITEM_WIDTH, ITEM_HEIGHT);
    CreateBigItem(3, 3, 5, 5, ITEM_WIDTH, ITEM_HEIGHT);
    CreateBigItem(4, 4, 0, 0, ITEM_WIDTH, ITEM_HEIGHT);
    CreateBigItem(4, 4, 1, 1, ITEM_WIDTH, ITEM_HEIGHT);
    CreateBigItem(4, 4, 2, 3, ITEM_WIDTH, ITEM_HEIGHT);
    CreateBigItem(4, 4, 4, 4, ITEM_WIDTH, ITEM_HEIGHT);
    CreateBigItem(4, 4, 5, 5, ITEM_WIDTH, ITEM_HEIGHT);
    CreateBigItem(5, 5, 0, 3, ITEM_WIDTH, ITEM_HEIGHT);
    CreateBigItem(5, 5, 4, 5, ITEM_WIDTH, ITEM_HEIGHT);
    CreateBigItem(6, 6, 0, 3, ITEM_WIDTH, ITEM_HEIGHT);
}

/**
 * @tc.name: Layout forward cache lines for regular
 * @tc.desc: Test forward cache lines layout
 * @tc.type: FUNC
 */
HWTEST_F(GridCacheLayoutTestNg, LayoutForwardCachedLines001, TestSize.Level1)
{
    GridModelNG model = CreateRepeatGrid(30, [](uint32_t idx) { return ITEM_HEIGHT; });
    model.SetColumnsTemplate("1fr 1fr 1fr");
    model.SetCachedCount(10); // 10 lines
    model.SetLayoutOptions({});
    CreateDone(frameNode_);
    EXPECT_EQ(frameNode_->GetTotalChildCount(), 30);
    const auto& info = pattern_->info_;
    EXPECT_EQ(info.startIndex_, 0);
    EXPECT_EQ(info.endIndex_, 11);

    for (int32_t i = 0; i < 10; i++) {
        pattern_->ScrollBy(ITEM_HEIGHT);
        FlushLayoutTask(frameNode_);
    }

    int32_t colsNumber = 3;
    float itemWidth = 160.f;
    float totalHeight = ITEM_HEIGHT * 10;
    for (int32_t index = 29; index >= 0; index--) {
        RectF childRect = GetChildRect(frameNode_, index);
        float offsetX = index % colsNumber * itemWidth;
        float offsetY = -totalHeight + floor(index / colsNumber) * ITEM_HEIGHT + GRID_HEIGHT;
        RectF expectRect = RectF(offsetX, offsetY, itemWidth, ITEM_HEIGHT);
        EXPECT_TRUE(IsEqual(childRect, expectRect)) << "index: " << index;
    }
}

/**
 * @tc.name: Layout forward cache lines for irregular item with columnStart
 * @tc.desc: Test forward cache lines layout
 * @tc.type: FUNC
 */
HWTEST_F(GridCacheLayoutTestNg, LayoutForwardCachedLines002, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr 1fr");
    CreateItems1();
    model.SetCachedCount(10); // 10 lines
    CreateDone(frameNode_);

    for (int32_t i = 0; i < 25; i++) {
        pattern_->ScrollBy(100);
        FlushLayoutTask(frameNode_);
    }

    float totalHeight = ITEM_HEIGHT * 10;
    for (int32_t index = 18; index >= 0; index--) {
        auto child = frameNode_->GetChildByIndex(index);
        auto childProps = AceType::DynamicCast<GridItemLayoutProperty>(child->GetLayoutProperty());
        RectF childRect = GetChildRect(frameNode_, index);
        float width = childProps->GetCrossSpan(Axis::VERTICAL) * GRID_WIDTH / 4;
        float height = childProps->GetMainSpan(Axis::VERTICAL) * ITEM_HEIGHT;
        float offsetY = -totalHeight + childProps->GetMainIndex().value_or(0) * ITEM_HEIGHT + GRID_HEIGHT;
        // multi-line item's mainIndex may be translated to its last line during scrolling.
        if (index == 4) {
            offsetY -= ITEM_HEIGHT;
        }
        float offsetX = childProps->GetCrossIndex().value_or(0) * GRID_WIDTH / 4;
        RectF expectRect = RectF(offsetX, offsetY, width, height);
        EXPECT_TRUE(IsEqual(childRect, expectRect)) << "index: " << index;
    }
}

/**
 * @tc.name: Layout forward cache lines for irregular item with columnStart
 * @tc.desc: Test forward cache lines layout
 * @tc.type: FUNC
 */
HWTEST_F(GridCacheLayoutTestNg, LayoutForwardCachedLines003, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr 1fr 1fr 1fr");
    CreateItems2();
    model.SetCachedCount(6); // 6 lines
    CreateDone(frameNode_);

    for (int32_t i = 0; i < 14; i++) {
        pattern_->ScrollBy(100);
        FlushLayoutTask(frameNode_);
    }

    float totalHeight = ITEM_HEIGHT * 7;
    for (int32_t index = 18; index >= 0; index--) {
        auto child = frameNode_->GetChildByIndex(index);
        auto childProps = AceType::DynamicCast<GridItemLayoutProperty>(child->GetLayoutProperty());
        RectF childRect = GetChildRect(frameNode_, index);
        float width = childProps->GetCrossSpan(Axis::VERTICAL) * GRID_WIDTH / 6;
        float height = childProps->GetMainSpan(Axis::VERTICAL) * ITEM_HEIGHT;
        float offsetY = -totalHeight + childProps->GetMainIndex().value_or(0) * ITEM_HEIGHT + GRID_HEIGHT;
        // multi-line item's mainIndex may be translated to its last line during scrolling.
        if (index == 2) {
            offsetY -= ITEM_HEIGHT;
        }
        float offsetX = childProps->GetCrossIndex().value_or(0) * GRID_WIDTH / 6;
        RectF expectRect = RectF(offsetX, offsetY, width, height);
        EXPECT_TRUE(IsEqual(childRect, expectRect)) << "index: " << index;
    }
}

/**
 * @tc.name: Create001
 * @tc.desc: Test creating items in front
 * @tc.type: FUNC
 */
HWTEST_F(GridCacheLayoutTestNg, Create001, TestSize.Level1)
{
    GridModelNG model = CreateRepeatGrid(100, [](uint32_t idx) { return ITEM_HEIGHT; });
    model.SetColumnsTemplate("1fr 1fr 1fr");
    model.SetLayoutOptions({});
    model.SetCachedCount(1); // 6 lines
    CreateDone(frameNode_);
    const auto& info = pattern_->info_;
    EXPECT_EQ(info.endIndex_, 11);

    pattern_->ScrollToIndex(99, false, ScrollAlign::END);
    FlushLayoutTask(frameNode_);
    EXPECT_FALSE(GetChildFrameNode(frameNode_, 89));
    EXPECT_EQ(info.startIndex_, 90);
    const std::list<int32_t> preload = { 89, 88, 87 };
    CheckPreloadListEqual(preload);

    PipelineContext::GetCurrentContext()->OnIdle(INT64_MAX);
    EXPECT_TRUE(pattern_->preloadItemList_.empty());
    ASSERT_TRUE(GetChildFrameNode(frameNode_, 88));
    EXPECT_FALSE(GetChildFrameNode(frameNode_, 88)->IsActive());
}

/**
 * @tc.name: Create001
 * @tc.desc: Test creating items in front
 * @tc.type: FUNC
 */
HWTEST_F(GridCacheLayoutTestNg, Create005, TestSize.Level1)
{
    GridModelNG model = CreateRepeatGrid(100, [](uint32_t idx) { return ITEM_HEIGHT; });
    model.SetColumnsTemplate("1fr 1fr 1fr");
    model.SetLayoutOptions({});
    model.SetCachedCount(1, true); // 6 lines
    CreateDone(frameNode_);
    const auto& info = pattern_->info_;
    EXPECT_EQ(info.endIndex_, 11);

    pattern_->ScrollToIndex(99, false, ScrollAlign::END);
    FlushLayoutTask(frameNode_);
    ASSERT_TRUE(GetChildFrameNode(frameNode_, 88));
    EXPECT_TRUE(GetChildFrameNode(frameNode_, 88)->IsActive());
    EXPECT_EQ(GetChildHeight(frameNode_, 88), 200.0f);
}

/**
 * @tc.name: ShowCache001
 * @tc.desc: Test Grid showCache items
 * @tc.type: FUNC
 */
HWTEST_F(GridCacheLayoutTestNg, ShowCache001, TestSize.Level1)
{
    GridModelNG model = CreateRepeatGrid(50, [](uint32_t idx) { return 200.0f; });
    model.SetColumnsTemplate("1fr 1fr");
    model.SetLayoutOptions({});
    model.SetRowsGap(Dimension(10));
    model.SetColumnsGap(Dimension(10));
    model.SetCachedCount(1, true);
    CreateDone(frameNode_);
    const auto& info = pattern_->info_;
    EXPECT_EQ(info.startIndex_, 0);
    EXPECT_EQ(info.endIndex_, 7);
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(GetChildFrameNode(frameNode_, 8)->IsActive());
    EXPECT_TRUE(GetChildFrameNode(frameNode_, 9)->IsActive());
    EXPECT_EQ(GetChildWidth(frameNode_, 8), 235.0f);
    EXPECT_EQ(GetChildY(frameNode_, 8), 840.0f);
    EXPECT_EQ(GetChildY(frameNode_, 9), 840.0f);

    UpdateCurrentOffset(-400.0f);
    EXPECT_EQ(info.startIndex_, 2);
    EXPECT_EQ(info.endIndex_, 11);
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(GetChildFrameNode(frameNode_, 12)->IsActive());
    EXPECT_TRUE(GetChildFrameNode(frameNode_, 13)->IsActive());
    EXPECT_EQ(GetChildY(frameNode_, 10), 650.0f);
    EXPECT_EQ(GetChildY(frameNode_, 11), 650.0f);
    EXPECT_EQ(GetChildY(frameNode_, 12), 860.0f);
    EXPECT_EQ(GetChildY(frameNode_, 13), 860.0f);
    EXPECT_TRUE(GetChildFrameNode(frameNode_, 0)->IsActive());
    EXPECT_TRUE(GetChildFrameNode(frameNode_, 1)->IsActive());
    EXPECT_EQ(GetChildY(frameNode_, 0), -400.0f);
    EXPECT_EQ(GetChildY(frameNode_, 1), -400.0f);
}

/**
 * @tc.name: ShowCache002
 * @tc.desc: Test Grid showCache items and change width
 * @tc.type: FUNC
 */
HWTEST_F(GridCacheLayoutTestNg, ShowCache002, TestSize.Level1)
{
    GridModelNG model = CreateRepeatGrid(50, [](uint32_t idx) { return 200.0f; });
    model.SetColumnsTemplate("1fr 1fr");
    model.SetLayoutOptions({});
    model.SetRowsGap(Dimension(10));
    model.SetColumnsGap(Dimension(10));
    model.SetCachedCount(2, true);
    CreateDone(frameNode_);
    const auto& info = pattern_->info_;
    EXPECT_EQ(info.endIndex_, 7);
    EXPECT_EQ(GetChildY(frameNode_, 9), 840.0f);
    EXPECT_EQ(GetChildY(frameNode_, 11), 1050.0f);

    UpdateCurrentOffset(-550.0f);
    EXPECT_EQ(info.startIndex_, 4);
    EXPECT_EQ(info.endIndex_, 13);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(GetChildWidth(frameNode_, 15), 235.0f);
    EXPECT_EQ(GetChildX(frameNode_, 15), 245.0f);

    layoutProperty_->UpdateUserDefinedIdealSize(CalcSize(CalcLength(200.0f), CalcLength(800.0f)));
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(GetChildWidth(frameNode_, 14), 95.0f);
    EXPECT_EQ(GetChildWidth(frameNode_, 15), 95.0f);
    EXPECT_EQ(GetChildX(frameNode_, 15), 105.0f);
    EXPECT_EQ(GetChildWidth(frameNode_, 3), 95.0f);
    EXPECT_EQ(GetChildX(frameNode_, 3), 105.0f);
    EXPECT_TRUE(GetChildFrameNode(frameNode_, 3)->IsActive());
    EXPECT_TRUE(GetChildFrameNode(frameNode_, 14)->IsActive());
    EXPECT_EQ(GetChildY(frameNode_, 2), -340.0f);
    EXPECT_EQ(GetChildY(frameNode_, 14), 920.0f);
    EXPECT_EQ(info.gridMatrix_.size(), 9);

    UpdateCurrentOffset(-300.0f);
    EXPECT_EQ(info.startIndex_, 8);
    EXPECT_EQ(info.endIndex_, 15);
    EXPECT_EQ(GetChildY(frameNode_, 4), -430.0f);
    EXPECT_EQ(GetChildX(frameNode_, 5), 105.0f);
    EXPECT_EQ(GetChildY(frameNode_, 16), 830.0f);
    EXPECT_EQ(GetChildY(frameNode_, 19), 1040.0f);
    EXPECT_EQ(GetChildWidth(frameNode_, 19), 95.0f);
}

/**
 * @tc.name: ShowCache003
 * @tc.desc: Test Grid showCache items with padding
 * @tc.type: FUNC
 */
HWTEST_F(GridCacheLayoutTestNg, ShowCache003, TestSize.Level1)
{
    GridModelNG model = CreateRepeatGrid(50, [](uint32_t idx) { return 200.0f; });
    model.SetColumnsTemplate("1fr 1fr");
    model.SetLayoutOptions({});
    model.SetRowsGap(Dimension(10));
    model.SetColumnsGap(Dimension(10));
    model.SetCachedCount(3, true);
    ViewAbstract::SetPadding(CalcLength(5));
    CreateDone(frameNode_);
    const auto& info = pattern_->info_;
    EXPECT_EQ(info.endIndex_, 7);
    EXPECT_EQ(GetChildX(frameNode_, 0), 5.0f);
    EXPECT_EQ(GetChildWidth(frameNode_, 0), 230.0f);
    EXPECT_EQ(GetChildWidth(frameNode_, 1), 230.0f);
    EXPECT_EQ(GetChildX(frameNode_, 1), 245.0f);
    EXPECT_EQ(GetChildX(frameNode_, 8), 5.0f);
    EXPECT_EQ(GetChildWidth(frameNode_, 8), 230.0f);
    EXPECT_EQ(GetChildX(frameNode_, 9), 245.0f);
    EXPECT_EQ(GetChildWidth(frameNode_, 9), 230.0f);
    EXPECT_EQ(GetChildY(frameNode_, 9), 845.0f);
    EXPECT_EQ(GetChildY(frameNode_, 11), 1055.0f);
    EXPECT_EQ(GetChildWidth(frameNode_, 11), 230.0f);
}

/**
 * @tc.name: Cache001
 * @tc.desc: Test Grid preload items
 * @tc.type: FUNC
 */
HWTEST_F(GridCacheLayoutTestNg, Cache001, TestSize.Level1)
{
    GridModelNG model = CreateRepeatGrid(50, [](uint32_t idx) { return 200.0f; });
    model.SetColumnsTemplate("1fr 1fr 1fr");
    model.SetRowsGap(Dimension(10));
    model.SetColumnsGap(Dimension(10));
    model.SetCachedCount(2); // 2 lines
    CreateDone(frameNode_);
    EXPECT_EQ(frameNode_->GetTotalChildCount(), 50);
    const auto& info = pattern_->info_;
    EXPECT_EQ(info.startIndex_, 0);
    EXPECT_EQ(info.endIndex_, 11);
    const std::list<int32_t> preloadList = { 12, 13, 14 };
    for (const int32_t i : preloadList) {
        EXPECT_FALSE(frameNode_->GetChildByIndex(i));
    }
    CheckPreloadListEqual(preloadList);
    PipelineContext::GetCurrentContext()->OnIdle(INT64_MAX);
    EXPECT_TRUE(pattern_->preloadItemList_.empty());
    for (const int32_t i : preloadList) {
        EXPECT_TRUE(frameNode_->GetChildByIndex(i));
        EXPECT_EQ(GetChildRect(frameNode_, i).Height(), 200.0f);
    }
    FlushLayoutTask(frameNode_);
    // preload next line
    const std::list<int32_t> preloadList2 = { 15, 16, 17 };
    CheckPreloadListEqual(preloadList2);
    PipelineContext::GetCurrentContext()->OnIdle(INT64_MAX);
    EXPECT_TRUE(pattern_->preloadItemList_.empty());
    for (const int32_t i : preloadList2) {
        EXPECT_TRUE(frameNode_->GetChildByIndex(i));
        EXPECT_EQ(GetChildRect(frameNode_, i).Height(), 200.0f);
    }
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(pattern_->preloadItemList_.empty());

    pattern_->ScrollToIndex(49);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(info.startIndex_, 39);
    // GridScroll algo currently not capable of preloading backward
    EXPECT_TRUE(pattern_->preloadItemList_.empty());
}

/**
 * @tc.name: LayoutCachedItem001
 * @tc.desc: Test LayoutCachedItem
 * @tc.type: FUNC
 */
HWTEST_F(GridCacheLayoutTestNg, LayoutCachedItem001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set CachedCount:1
     * @tc.expected: The item(index:16) below view is active, no item above view
     */
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr 1fr");
    model.SetCachedCount(1);
    CreateFixedItems(40);
    CreateDone(frameNode_);
    EXPECT_FALSE(GetChildFrameNode(frameNode_, 16)->IsActive()); // the fifth row
    EXPECT_FALSE(GetChildFrameNode(frameNode_, 20)->IsActive()); // the sixth row

    /**
     * @tc.steps: step2. Scroll down
     * @tc.expected: The item(index:0) above view is active, the item(index:20) below view is active
     */
    pattern_->UpdateCurrentOffset(-ITEM_HEIGHT, SCROLL_FROM_UPDATE);
    pattern_->ScrollToIndex(4, false, ScrollAlign::START);
    FlushLayoutTask(frameNode_);
    EXPECT_FALSE(GetChildFrameNode(frameNode_, 0)->IsActive());
    EXPECT_FALSE(GetChildFrameNode(frameNode_, 20)->IsActive());

    /**
     * @tc.steps: step3. Scroll down
     * @tc.expected: The item(index:4) above view is active, the item(index:24) below view is active
     */
    pattern_->ScrollToIndex(8, false, ScrollAlign::START);
    FlushLayoutTask(frameNode_);
    EXPECT_FALSE(GetChildFrameNode(frameNode_, 0)->IsActive());
    EXPECT_FALSE(GetChildFrameNode(frameNode_, 4)->IsActive());
    EXPECT_FALSE(GetChildFrameNode(frameNode_, 24)->IsActive()); // th seventh row

    /**
     * @tc.steps: step4. Scroll up
     * @tc.expected: The item(index:0) above view is active, the item(index:20) below view is active
     */
    pattern_->ScrollToIndex(4, false, ScrollAlign::START);
    FlushLayoutTask(frameNode_);
    EXPECT_FALSE(GetChildFrameNode(frameNode_, 0)->IsActive());
    EXPECT_FALSE(GetChildFrameNode(frameNode_, 20)->IsActive());
    EXPECT_FALSE(GetChildFrameNode(frameNode_, 24)->IsActive());

    /**
     * @tc.steps: step5. Scroll up
     * @tc.expected: The item(index:16) below view is active, no item above view
     */
    pattern_->ScrollToIndex(0, false, ScrollAlign::START);
    FlushLayoutTask(frameNode_);
    EXPECT_FALSE(GetChildFrameNode(frameNode_, 16)->IsActive());
    EXPECT_FALSE(GetChildFrameNode(frameNode_, 20)->IsActive());
}
} // namespace OHOS::Ace::NG