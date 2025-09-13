/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
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

#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/render/mock_render_context.h"
#include "water_flow_item_maps.h"
#include "water_flow_test_ng.h"

#include "core/components/common/layout/constants.h"
#include "core/components_ng/base/view_abstract_model_ng.h"
#include "core/components_ng/pattern/lazy_layout/grid_layout/lazy_grid_layout_model.h"
#include "core/components_ng/pattern/waterflow/layout/sliding_window/water_flow_layout_info_sw.h"
#include "core/components_ng/syntax/if_else_model_ng.h"
#include "core/components_ng/syntax/if_else_node.h"

namespace OHOS::Ace::NG {
class WaterFlowSWTest : public WaterFlowTestNg {
protected:
    void GetWaterFlow() override
    {
        WaterFlowTestNg::GetWaterFlow();
        info_ = AceType::DynamicCast<WaterFlowLayoutInfoSW>(pattern_->layoutInfo_);
        EXPECT_TRUE(info_);
    }

    RefPtr<WaterFlowLayoutInfoSW> info_;
};

/**
 * @tc.name: LazyforeachReloaded01
 * @tc.desc: test lazyforeach reloaded func
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowSWTest, LazyforeachReloaded01, TestSize.Level1)
{
    WaterFlowModelNG model = CreateWaterFlow();
    ViewAbstract::SetWidth(CalcLength(400.0f));
    ViewAbstract::SetHeight(CalcLength(800.f));
    model.SetFooter(GetDefaultHeaderBuilder());
    RefPtr<WaterFlowMockLazy> mockLazy = CreateItemsInLazyForEach(50, [](int32_t) { return 100.0f; });
    CreateDone();

    EXPECT_EQ(info_->startIndex_, 0);
    EXPECT_EQ(info_->endIndex_, 7);

    auto lazyForEachNode = AceType::DynamicCast<LazyForEachNode>(frameNode_->GetChildAtIndex(1));
    EXPECT_EQ(mockLazy->GetHistoryTotalCount(), 50);
    EXPECT_EQ(lazyForEachNode->FrameCount(), 50);
    mockLazy->SetTotalCount(0);
    lazyForEachNode->OnDataReloaded();
    EXPECT_EQ(info_->newStartIndex_, -2);
    FlushUITasks();
    EXPECT_EQ(frameNode_->GetTotalChildCount(), 1);
    EXPECT_EQ(mockLazy->GetHistoryTotalCount(), 0);
    EXPECT_EQ(lazyForEachNode->FrameCount(), 0);
    ASSERT_TRUE(GetItem(0, true));
    EXPECT_TRUE(GetItem(0, true)->IsActive());
    EXPECT_EQ(info_->newStartIndex_, -1);

    mockLazy->SetTotalCount(20);
    FlushUITasks();
    lazyForEachNode->OnDataReloaded();
    FlushUITasks();
    EXPECT_EQ(info_->newStartIndex_, -1);
    EXPECT_EQ(info_->startIndex_, 0);
    EXPECT_EQ(info_->endIndex_, 7);
    EXPECT_EQ(frameNode_->GetTotalChildCount(), 21);
    EXPECT_EQ(mockLazy->GetHistoryTotalCount(), 20);
    EXPECT_EQ(lazyForEachNode->FrameCount(), 20);
    ASSERT_TRUE(GetItem(0, true));
    EXPECT_FALSE(GetItem(0, true)->IsActive());
}

/**
 * @tc.name: SyncLoad001
 * @tc.desc: test load items frame by frame
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowSWTest, SyncLoad001, TestSize.Level1)
{
    WaterFlowModelNG model = CreateWaterFlow();
    ViewAbstract::SetWidth(CalcLength(400.0f));
    ViewAbstract::SetHeight(CalcLength(800.f));
    model.SetSyncLoad(false);

    CreateRandomWaterFlowItems(10);
    MockPipelineContext::GetCurrent()->SetResponseTime(2);
    CreateDone();

    EXPECT_EQ(info_->startIndex_, 0);
    EXPECT_EQ(info_->endIndex_, 1);
}

/**
 * @tc.name: SyncLoad001
 * @tc.desc: test load items frame by frame
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowSWTest, SyncLoad002, TestSize.Level1)
{
    WaterFlowModelNG model = CreateWaterFlow();
    ViewAbstract::SetWidth(CalcLength(400.0f));
    ViewAbstract::SetHeight(CalcLength(800.f));
    model.SetSyncLoad(false);
    CreateRandomWaterFlowItems(50);
    CreateDone();

    // @tc.steps: limit the number of frame-by-frame loads.
    MockPipelineContext::GetCurrent()->SetResponseTime(2);
    // @tc.steps: scrollby large offset to trigger jump in waterflow
    ScrollBy(0, 800 * 3);
    // @tc.expected: fill current page in one frame
    // The height of the child components is randomly set between 50 and 250. Therefore, we can only determine that the
    // number of layout child nodes is greater than the limit.
    EXPECT_GE(info_->endIndex_ - info_->startIndex_, 2);
}

/**
 * @tc.name: Footer001
 * @tc.desc: Put empty [if] to footer, test the NotifyDataChange.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowSWTest, Footer001, TestSize.Level1)
{
    std::list<int32_t> removedElmtIds;
    std::list<int32_t> reservedElmtIds;
    WaterFlowModelNG model = CreateWaterFlow();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetFooter([]() {
        IfElseModelNG ifElse;
        ifElse.Create();
    });
    CreateWaterFlowItems(1);
    RefPtr<WaterFlowMockLazy> mockLazy = CreateItemsInLazyForEach(20, [](int32_t) { return 100.0f; });
    CreateDone();

    EXPECT_EQ(info_->startIndex_, 0);
    EXPECT_EQ(info_->endIndex_, 15);
    EXPECT_EQ(frameNode_->GetTotalChildCount(), 21);
    EXPECT_EQ(frameNode_->GetChildrenUpdated(), -1);
    EXPECT_EQ(pattern_->layoutInfo_->footerIndex_, -1);

    auto lazyForEachNode = AceType::DynamicCast<LazyForEachNode>(frameNode_->GetChildAtIndex(2));
    lazyForEachNode->OnDataAdded(0);
    EXPECT_EQ(info_->newStartIndex_, -2);
    EXPECT_EQ(frameNode_->GetChildrenUpdated(), 1);
}

/**
 * @tc.name: NoConvert001
 * @tc.desc: Test misalignment and shouldn't trigger ConvertDeltaToJump
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowSWTest, NoConvert001, TestSize.Level1)
{
    WaterFlowModelNG model = CreateWaterFlow();
    model.SetColumnsTemplate("1fr 1fr");
    vector<int> heights = { 183, 300, 244, 287, 100, 125, 160, 300, 129, 147, 118, 179, 137, 177, 169, 234, 179, 288,
        208, 270, 184, 162, 237, 205, 141, 189, 276, 146, 105, 207, 234, 283, 183, 191, 212, 186, 128, 288, 139, 256,
        260, 243, 294, 261, 162 }; // randomly generated
    ASSERT_EQ(heights.size(), 45);
    for (int i = 0; i < 45; ++i) {
        CreateItemWithHeight(heights[i]);
    }
    auto secObj = pattern_->GetOrCreateWaterFlowSections();
    secObj->ChangeData(0, 0, SECTION_16);
    CreateDone();
    ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, false);

    EXPECT_EQ(info_->startIndex_, 33);
    pattern_->isAnimationStop_ = false; // to block jumps
    UpdateCurrentOffset(2000.0f);
    EXPECT_EQ(info_->startIndex_, 5);
    pattern_->isAnimationStop_ = true;
    pattern_->OnScrollEndCallback();
    // should mark misaligned
    EXPECT_EQ(info_->lanes_[0][0].ToString(), "{StartPos: 2800.000000 EndPos: 2800.000000 empty}");
    EXPECT_EQ(info_->lanes_[0][1].ToString(), "{StartPos: 2800.000000 EndPos: 2800.000000 empty}");
    info_->lanes_[0][0].startPos = -6000; // manually create scenario that can trigger ConvertDeltaToJump
    EXPECT_EQ(info_->jumpIndex_, 5);
    FlushUITasks();
    EXPECT_EQ(info_->startIndex_, 5);
}

/**
 * @tc.name: Scroll001
 * @tc.desc: Test Scroll when have big items.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowSWTest, Scroll001, TestSize.Level1)
{
    WaterFlowModelNG model = CreateWaterFlow();
    model.SetColumnsTemplate("1fr");
    model.SetEdgeEffect(EdgeEffect::SPRING, true);
    for (int i = 0; i < 10; ++i) {
        CreateItemWithHeight(WATER_FLOW_HEIGHT * 4);
    }
    CreateDone();

    EXPECT_EQ(info_->startIndex_, 0);
    EXPECT_EQ(info_->endIndex_, 0);
    for (int i = 0; i < 20; ++i) {
        UpdateCurrentOffset(-100.0f);
        EXPECT_EQ(info_->startIndex_, 0);
        EXPECT_EQ(info_->endIndex_, 0);
    }
    UpdateCurrentOffset(-WATER_FLOW_HEIGHT);
    EXPECT_EQ(info_->startIndex_, 0);
    EXPECT_EQ(info_->endIndex_, 1);
    for (int i = 0; i < 3; ++i) {
        UpdateCurrentOffset(400.0f);
        EXPECT_EQ(info_->startIndex_, 0);
        EXPECT_EQ(info_->endIndex_, 0);
    }
}

/**
 * @tc.name: Layout003
 * @tc.desc: Test layout position when have precision error in floating-point arithmetic.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowSWTest, Layout003, TestSize.Level1)
{
    WaterFlowModelNG model = CreateWaterFlow();
    model.SetColumnsTemplate("1fr 1fr 1fr");
    model.SetEdgeEffect(EdgeEffect::SPRING, true);
    pattern_->SetAnimateCanOverScroll(true);
    for (int i = 0; i < 41; ++i) {
        CreateItemWithHeight(100.0f);
    }
    CreateDone();

    ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, false);
    EXPECT_EQ(info_->startIndex_, 18);
    EXPECT_EQ(info_->endIndex_, 40);

    // precision error in floating-point arithmetic.
    info_->lanes_[0][2].endPos -= 0.0099f;
    /* Add 5 items at 41 */
    AddItemsAtSlot(5, 100.0f, 41);
    info_->NotifyDataChange(41, 5);

    ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, false);
    EXPECT_EQ(info_->startIndex_, 24);
    EXPECT_EQ(info_->endIndex_, 45);

    // new Items should be put in order.
    EXPECT_EQ(
        info_->lanes_[0][0].ToString(), "{StartPos: 0.000000 EndPos: 800.000000 Items [24 27 30 33 36 39 42 45 ] }");
    EXPECT_EQ(info_->lanes_[0][1].ToString(), "{StartPos: 0.000000 EndPos: 700.000000 Items [25 28 31 34 37 40 43 ] }");
    EXPECT_EQ(info_->lanes_[0][2].ToString(), "{StartPos: 0.000000 EndPos: 699.990112 Items [26 29 32 35 38 41 44 ] }");
}

/**
 * @tc.name: Layout004
 * @tc.desc: Test layout position when have precision error in floating-point arithmetic.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowSWTest, Layout004, TestSize.Level1)
{
    WaterFlowModelNG model = CreateWaterFlow();
    model.SetColumnsTemplate("1fr 1fr 1fr");
    for (int i = 0; i < 41; ++i) {
        CreateItemWithHeight(100.0f);
    }
    CreateDone();

    ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, false);
    EXPECT_EQ(info_->startIndex_, 18);
    EXPECT_EQ(info_->endIndex_, 40);

    info_->NotifyDataChange(0, 0);
    // precision error in floating-point arithmetic.
    info_->lanes_[0][0].startPos += 0.0099f;

    UpdateCurrentOffset(150.0f);
    EXPECT_EQ(info_->startIndex_, 12);
    EXPECT_EQ(info_->endIndex_, 38);

    // new Items should be put in order.
    EXPECT_EQ(info_->lanes_[0][0].ToString(),
        "{StartPos: -49.990097 EndPos: 850.000000 Items [12 15 18 21 24 27 30 33 36 ] }");
    EXPECT_EQ(info_->lanes_[0][1].ToString(),
        "{StartPos: -50.000000 EndPos: 850.000000 Items [13 16 19 22 25 28 31 34 37 ] }");
    EXPECT_EQ(info_->lanes_[0][2].ToString(),
        "{StartPos: -50.000000 EndPos: 850.000000 Items [14 17 20 23 26 29 32 35 38 ] }");
}

/**
 * @tc.name: Layout001
 * @tc.desc: Test layout position when have precision error in floating-point arithmetic.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowSWTest, Layout001, TestSize.Level1)
{
    WaterFlowModelNG model = CreateWaterFlow();
    model.SetColumnsTemplate("1fr 1fr 1fr");
    model.SetEdgeEffect(EdgeEffect::SPRING, true);
    pattern_->SetAnimateCanOverScroll(true);
    for (int i = 0; i < 41; ++i) {
        CreateItemWithHeight(100.0f);
    }
    CreateDone();

    ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, false);
    EXPECT_EQ(info_->startIndex_, 18);
    EXPECT_EQ(info_->endIndex_, 40);

    // precision error in floating-point arithmetic.
    info_->lanes_[0][2].endPos -= 0.0001f;
    /* Add 5 items at 41 */
    AddItemsAtSlot(5, 100.0f, 41);
    info_->NotifyDataChange(41, 5);

    ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, false);
    EXPECT_EQ(info_->startIndex_, 24);
    EXPECT_EQ(info_->endIndex_, 45);

    // new Items should be put in order.
    EXPECT_EQ(
        info_->lanes_[0][0].ToString(), "{StartPos: 0.000000 EndPos: 800.000000 Items [24 27 30 33 36 39 42 45 ] }");
    EXPECT_EQ(info_->lanes_[0][1].ToString(), "{StartPos: 0.000000 EndPos: 700.000000 Items [25 28 31 34 37 40 43 ] }");
    EXPECT_EQ(info_->lanes_[0][2].ToString(), "{StartPos: 0.000000 EndPos: 699.999878 Items [26 29 32 35 38 41 44 ] }");
}

/**
 * @tc.name: Layout002
 * @tc.desc: Test layout position when change the columnTemplate.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowSWTest, Layout002, TestSize.Level1)
{
    WaterFlowModelNG model = CreateWaterFlow();
    model.SetColumnsTemplate("1fr 1fr 1fr");
    for (int i = 0; i < 80; ++i) {
        CreateItemWithHeight(100.0f);
    }
    CreateDone();

    UpdateCurrentOffset(-450.0f);
    EXPECT_EQ(info_->startIndex_, 12);
    EXPECT_EQ(info_->endIndex_, 38);
    EXPECT_EQ(GetChildRect(frameNode_, 12).Top(), -50.0f);
    EXPECT_EQ(GetChildRect(frameNode_, 13).Top(), -50.0f);
    EXPECT_EQ(GetChildRect(frameNode_, 14).Top(), -50.0f);

    layoutProperty_->UpdateColumnsTemplate("1fr 1fr 1fr 1fr");
    layoutProperty_->UpdateUserDefinedIdealSize(CalcSize(CalcLength(500.0f), CalcLength(Dimension(WATER_FLOW_HEIGHT))));

    FlushUITasks();
    EXPECT_EQ(info_->startIndex_, 12);
    EXPECT_EQ(info_->endIndex_, 47);
    EXPECT_EQ(GetChildRect(frameNode_, 12).Top(), -50.0f);
    EXPECT_EQ(GetChildRect(frameNode_, 13).Top(), -50.0f);
    EXPECT_EQ(GetChildRect(frameNode_, 14).Top(), -50.0f);
    EXPECT_EQ(GetChildRect(frameNode_, 15).Top(), -50.0f);
}

/**
 * @tc.name: ScrollToTagetTest001
 * @tc.desc: Test ScrollToTaget with reverse and expandSafeArea
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowSWTest, ScrollToTagetTest001, TestSize.Level1)
{
    WaterFlowModelNG model = CreateWaterFlow();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetLayoutDirection(FlexDirection::COLUMN_REVERSE);
    
    CreateItemsInLazyForEach(100, [](int32_t) { return 100.0f; });
    CreateDone();

    EXPECT_CALL(*MockPipelineContext::pipeline_, GetSafeArea)
        .Times(1)
        .WillRepeatedly(Return(SafeAreaInsets { {}, { .start = 0, .end = 100 }, {}, {} }));
    layoutProperty_->UpdateSafeAreaExpandOpts({ .type = SAFE_AREA_TYPE_SYSTEM, .edges = SAFE_AREA_EDGE_ALL });

    auto mockContext = AceType::DynamicCast<MockRenderContext>(frameNode_->GetRenderContext());
    mockContext->SetPaintRectWithTransform(RectF(0.0f, 0.0f, WIDTH, HEIGHT));
    ScrollAlign align = ScrollAlign::START;
    // Move index 3 to middle of WaterFlow
    auto child = frameNode_->GetChildByIndex(3);
    ASSERT_NE(child, nullptr);
    auto childNode = child->GetHostNode();
    ASSERT_NE(childNode, nullptr);
    auto mockChildContext = AceType::DynamicCast<MockRenderContext>(childNode->GetRenderContext());
    mockChildContext->SetPaintRectWithTransform(RectF(WIDTH, 6 * ITEM_MAIN_SIZE, WIDTH, ITEM_MAIN_SIZE));
    EXPECT_EQ(ScrollablePattern::ScrollToTarget(frameNode_, childNode, 0.0f, align), RET_SUCCESS);
    EXPECT_TRUE(TickPosition(-100.0f));
}

/**
 * @tc.name: InitialLoadOrderBug001
 * @tc.desc: Test that WaterFlow sliding window mode loads items in correct order during initialization
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowSWTest, InitialLoadOrderBug001, TestSize.Level1)
{
    // Initialize tracking variables
    int32_t firstIndex = -1;
    int32_t lastIndex = -1;

    // Define callback to track scroll indices
    auto onScrollIndex = [&firstIndex, &lastIndex](int32_t first, int32_t last) {
        firstIndex = first;
        lastIndex = last;
    };

    // Initialize waterflow model and set basic properties
    WaterFlowModelNG model = CreateWaterFlow();
    ViewAbstract::SetWidth(CalcLength(400.0f));
    ViewAbstract::SetHeight(CalcLength(800.f));
    model.SetFooter(GetDefaultHeaderBuilder());
    model.SetColumnsTemplate("1fr 1fr");
    model.SetOnScrollIndex(onScrollIndex);

    // Start with some data, then test transition
    RefPtr<WaterFlowMockLazy> mockLazy = CreateItemsInLazyForEach(10, [](int32_t) { return 100.0f; });
    CreateDone();

    // Test transition to empty
    mockLazy->SetTotalCount(0);
    auto lazyForEachNode = AceType::DynamicCast<LazyForEachNode>(frameNode_->GetChildAtIndex(1));
    lazyForEachNode->OnDataReloaded();
    FlushUITasks();

    // Verify empty state
    EXPECT_EQ(firstIndex, Infinity<int32_t>());
    EXPECT_EQ(lastIndex, -1);

    // Test transition back to populated - trigger CheckReset branch
    mockLazy->SetTotalCount(26);
    lazyForEachNode->OnDataReloaded();

    // Manually trigger measure to call CheckReset() instead of immediate FlushUITasks()
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    FlushUITasks();

    // Verify fixed state after transition
    EXPECT_EQ(info_->startIndex_, 0);
    EXPECT_GE(info_->endIndex_, 0);
    EXPECT_EQ(mockLazy->GetHistoryTotalCount(), 26);
    EXPECT_EQ(lazyForEachNode->FrameCount(), 26);

    // Verify that the first item is at index 0 position
    ASSERT_TRUE(GetItem(0, true));
    EXPECT_EQ(pattern_->GetItemIndex(0, 0), 0);
}

/**
 * @tc.name: LazyVGridInWaterFlowSW001
 * @tc.desc: Test LazyVGridLayout basic fast scrolling
 */
HWTEST_F(WaterFlowSWTest, LazyVGridInWaterFlowSW001, TestSize.Level1)
{
    // Create WaterFlow with sliding window mode
    WaterFlowModelNG model = CreateWaterFlow();
    model.SetColumnsTemplate("1fr");
    ViewAbstract::SetWidth(CalcLength(400.0f));
    ViewAbstract::SetHeight(CalcLength(800.0f));

    // Create LazyVGridLayouts
    for (int i = 0; i < 15; ++i) {
        LazyVGridLayoutModel gridModel;
        gridModel.Create();
        gridModel.SetColumnsTemplate("1fr 1fr");
        gridModel.SetRowGap(Dimension(5.0f));
        gridModel.SetColumnGap(Dimension(5.0f));

        // Create child items to trigger adjustOffset mechanism
        for (int j = 0; j < 6; ++j) {
            CreateItemWithHeight(80.0f);
        }
        ViewStackProcessor::GetInstance()->Pop();
    }
    CreateDone();

    auto swInfo = AceType::DynamicCast<WaterFlowLayoutInfoSW>(pattern_->layoutInfo_);
    ASSERT_NE(swInfo, nullptr);

    // Verify initial state
    EXPECT_EQ(swInfo->startIndex_, 0);
    EXPECT_EQ(swInfo->endIndex_, 3);

    // Test fast scrolling
    UpdateCurrentOffset(-1200.0f);

    // Verify sliding window state
    EXPECT_EQ(swInfo->startIndex_, 4);
    EXPECT_EQ(swInfo->endIndex_, 7);

    // Verify lane positions
    for (const auto& segment : swInfo->lanes_) {
        for (const auto& lane : segment) {
            EXPECT_EQ(lane.startPos, -200);
            EXPECT_EQ(lane.endPos, 800);
            EXPECT_LE(lane.startPos, lane.endPos);
        }
    }

    // Verify total offset range
    EXPECT_EQ(swInfo->totalOffset_, -1200);

    // Verify visible items position
    for (int i = swInfo->startIndex_; i <= swInfo->endIndex_; ++i) {
        auto rect = pattern_->GetItemRect(i);
        EXPECT_EQ(rect.Top(), (i - 4) * 250 - 200);
        EXPECT_EQ(rect.Bottom(), (i - 4 + 1) * 250 - 200);
        EXPECT_EQ(rect.Height(), 250);
        EXPECT_EQ(rect.Width(), 400);
    }
}

/**
 * @tc.name: LazyVGridInWaterFlowSW002
 * @tc.desc: Test LazyVGridLayout reverse and multiple rapid scrolling
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowSWTest, LazyVGridInWaterFlowSW002, TestSize.Level1)
{
    // Create WaterFlow with sliding window mode
    WaterFlowModelNG model = CreateWaterFlow();
    model.SetColumnsTemplate("1fr");
    ViewAbstract::SetWidth(CalcLength(400.0f));
    ViewAbstract::SetHeight(CalcLength(800.0f));

    // Create LazyVGridLayouts
    for (int i = 0; i < 15; ++i) {
        LazyVGridLayoutModel gridModel;
        gridModel.Create();
        gridModel.SetColumnsTemplate("1fr 1fr");
        gridModel.SetRowGap(Dimension(5.0f));
        gridModel.SetColumnGap(Dimension(5.0f));

        for (int j = 0; j < 6; ++j) {
            CreateItemWithHeight(80.0f);
        }
        ViewStackProcessor::GetInstance()->Pop();
    }
    CreateDone();

    auto swInfo = AceType::DynamicCast<WaterFlowLayoutInfoSW>(pattern_->layoutInfo_);
    ASSERT_NE(swInfo, nullptr);

    // Initial scroll to set up test state
    UpdateCurrentOffset(-1200.0f);

    // Test reverse scrolling
    UpdateCurrentOffset(600.0f);

    EXPECT_EQ(swInfo->startIndex_, 2);
    EXPECT_EQ(swInfo->endIndex_, 5);

    // Verify lane consistency after reverse scrolling
    for (const auto& segment : swInfo->lanes_) {
        for (const auto& lane : segment) {
            EXPECT_EQ(lane.startPos, -100);
            EXPECT_EQ(lane.endPos, 900);
            EXPECT_LE(lane.startPos, lane.endPos);
        }
    }

    // Test multiple rapid scrolls
    for (int i = 0; i < 3; ++i) {
        UpdateCurrentOffset(-400.0f);
        UpdateCurrentOffset(200.0f);
    }

    // Verify system stability after multiple rapid scrolls
    EXPECT_EQ(swInfo->startIndex_, 4);
    EXPECT_EQ(swInfo->endIndex_, 7);
    EXPECT_EQ(swInfo->totalOffset_, -1200);
}

/**
 * @tc.name: ContentOffsetTest001
 * @tc.desc: Test contentStartOffset_ and contentEndOffset_
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowSWTest, ContentOffsetTest001, TestSize.Level1)
{
    WaterFlowModelNG model = CreateWaterFlow();
    model.SetColumnsTemplate("1fr 1fr");
    float contentOffset = 20;
    ScrollableModelNG::SetContentStartOffset(contentOffset);
    ScrollableModelNG::SetContentEndOffset(contentOffset * 1.5);
    CreateItemsInLazyForEach(100, [](int32_t) { return 100.0f; });
    CreateDone();

    EXPECT_EQ(layoutProperty_->GetContentStartOffset(), contentOffset);
    EXPECT_EQ(layoutProperty_->GetContentEndOffset(), contentOffset * 1.5);
}

/**
 * @tc.name: ContentOffsetTest002
 * @tc.desc: Test contentStartOffset_ and contentEndOffset_ with invalid value
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowSWTest, ContentOffsetTest002, TestSize.Level1)
{
    WaterFlowModelNG model = CreateWaterFlow();
    model.SetColumnsTemplate("1fr 1fr");
    float contentOffset = WATER_FLOW_HEIGHT / 2;
    ScrollableModelNG::SetContentStartOffset(contentOffset);
    ScrollableModelNG::SetContentEndOffset(contentOffset * 1.5);
    CreateItemsInLazyForEach(100, [](int32_t) { return 100.0f; });
    CreateDone();

    EXPECT_EQ(pattern_->layoutInfo_->contentStartOffset_, 0.0f);
    EXPECT_EQ(pattern_->layoutInfo_->contentEndOffset_, 0.0f);
}

/**
 * @tc.name: ContentOffsetTest003
 * @tc.desc: Test contentStartOffset_ and contentEndOffset_ with invalid value
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowSWTest, ContentOffsetTest003, TestSize.Level1)
{
    WaterFlowModelNG model = CreateWaterFlow();
    model.SetColumnsTemplate("1fr 1fr");
    float contentOffset = 20;
    ScrollableModelNG::SetContentStartOffset(contentOffset);
    ScrollableModelNG::SetContentEndOffset(contentOffset * 1.5);
    CreateItemsInLazyForEach(100, [](int32_t) { return 100.0f; });
    CreateDone();

    EXPECT_TRUE(pattern_->IsAtTop());
    EXPECT_FALSE(pattern_->IsAtBottom());
    EXPECT_EQ(pattern_->layoutInfo_->Offset(), 20.0);

    pattern_->UpdateCurrentOffset(-20, SCROLL_FROM_UPDATE);
    FlushUITasks();
    EXPECT_EQ(pattern_->layoutInfo_->Offset(), 0.0);
    EXPECT_FALSE(pattern_->IsAtTop());
    EXPECT_FALSE(pattern_->IsAtBottom());
}
} // namespace OHOS::Ace::NG
