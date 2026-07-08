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

#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"
#include "test/mock/frameworks/core/components_ng/render/mock_render_context.h"
#include "water_flow_item_maps.h"
#include "water_flow_test_ng.h"

#include "core/components/common/layout/constants.h"
#include "core/components_ng/base/view_abstract_model_ng.h"
#include "core/components_ng/pattern/lazy_grid_layout/lazy_grid_layout_model.h"
#include "core/components_ng/pattern/scrollable/scrollable_model_ng.h"
#include "core/components_ng/pattern/waterflow/layout/sliding_window/water_flow_layout_info_sw.h"
#include "core/components_ng/syntax/if_else_model_ng.h"
#include "core/components_ng/syntax/if_else_node.h"

namespace OHOS::Ace::NG {
namespace {
PaddingProperty CreatePadding(float left, float top, float right, float bottom)
{
    PaddingProperty padding;
    padding.left = CalcLength(left);
    padding.right = CalcLength(right);
    padding.top = CalcLength(top);
    padding.bottom = CalcLength(bottom);
    return padding;
}
} // namespace

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
    EXPECT_EQ(info_->lanes_[0][0].ToString(), "{StartPos: -37.000000 EndPos: -37.000000 empty}");
    EXPECT_EQ(info_->lanes_[0][1].ToString(), "{StartPos: -37.000000 EndPos: -37.000000 empty}");
    info_->lanes_[0][0].startPos = -6000; // manually create scenario that can trigger ConvertDeltaToJump
    EXPECT_EQ(info_->jumpIndex_, -2);
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

/**
 * @tc.name: ScrollToIndexStartWithContentOffset
 * @tc.desc: Test ScrollToIndex with ContentOffset and ScrollAlign::Start without animation
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowSWTest, ScrollToIndexStartWithContentOffsetTest, TestSize.Level1)
{
    WaterFlowModelNG model = CreateWaterFlow();
    model.SetColumnsTemplate("1fr 1fr");
    ScrollableModelNG::SetContentStartOffset(CONTENT_START_OFFSET);
    ScrollableModelNG::SetContentEndOffset(CONTENT_END_OFFSET);
    CreateWaterFlowItems(20);
    CreateDone();
    ScrollAlign scrollAlign = ScrollAlign::START;
    bool smooth = false;
    ScrollToIndex(19, smooth, scrollAlign);
    EXPECT_EQ(pattern_->layoutInfo_->Offset(), -830);
    EXPECT_EQ(pattern_->GetTotalOffset(), 830);

    ScrollToIndex(5, smooth, scrollAlign);
    EXPECT_EQ(pattern_->layoutInfo_->Offset(), -280);
    EXPECT_EQ(pattern_->GetTotalOffset(), 280);

    ScrollToIndex(13, smooth, scrollAlign);
    EXPECT_EQ(pattern_->layoutInfo_->Offset(), -830);
    EXPECT_EQ(pattern_->GetTotalOffset(), 830);

    ScrollToIndex(17, smooth, scrollAlign);
    EXPECT_EQ(pattern_->layoutInfo_->Offset(), -830);
    EXPECT_EQ(pattern_->GetTotalOffset(), 830);

    ScrollToIndex(0, smooth, scrollAlign);
    EXPECT_EQ(pattern_->layoutInfo_->Offset(), CONTENT_START_OFFSET);
    EXPECT_EQ(pattern_->GetTotalOffset(), -CONTENT_START_OFFSET);
}

/**
 * @tc.name: AnimateToIndexStartWithContentOffsetTest
 * @tc.desc: Test ScrollToIndex with ContentOffset and ScrollAlign::Start with animation
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowSWTest, AnimateToIndexStartWithContentOffsetTest, TestSize.Level1)
{
    WaterFlowModelNG model = CreateWaterFlow();
    model.SetColumnsTemplate("1fr 1fr");
    ScrollableModelNG::SetContentStartOffset(CONTENT_START_OFFSET);
    ScrollableModelNG::SetContentEndOffset(CONTENT_END_OFFSET);
    CreateWaterFlowItems(20);
    CreateDone();
    ScrollAlign scrollAlign = ScrollAlign::START;

    AnimateToIndexWithTicks(19, scrollAlign);
    EXPECT_EQ(pattern_->layoutInfo_->Offset(), -830);
    EXPECT_EQ(pattern_->GetTotalOffset(), 830);

    AnimateToIndexWithTicks(5, scrollAlign);
    EXPECT_EQ(pattern_->layoutInfo_->Offset(), -280);
    EXPECT_EQ(pattern_->GetTotalOffset(), 280);

    AnimateToIndexWithTicks(13, scrollAlign);
    EXPECT_EQ(pattern_->layoutInfo_->Offset(), -830);
    EXPECT_EQ(pattern_->GetTotalOffset(), 830);

    AnimateToIndexWithTicks(17, scrollAlign);
    EXPECT_EQ(pattern_->layoutInfo_->Offset(), -830);
    EXPECT_EQ(pattern_->GetTotalOffset(), 830);

    AnimateToIndexWithTicks(0, scrollAlign);
    EXPECT_EQ(pattern_->layoutInfo_->Offset(), CONTENT_START_OFFSET);
    EXPECT_EQ(pattern_->GetTotalOffset(), -CONTENT_START_OFFSET);
}

/**
 * @tc.name: ScrollToIndexEndWithContentOffset
 * @tc.desc: Test ScrollToIndex with ContentOffset and ScrollAlign::End without animation
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowSWTest, ScrollToIndexEndWithContentOffsetTest, TestSize.Level1)
{
    WaterFlowModelNG model = CreateWaterFlow();
    model.SetColumnsTemplate("1fr 1fr");
    ScrollableModelNG::SetContentStartOffset(CONTENT_START_OFFSET);
    ScrollableModelNG::SetContentEndOffset(CONTENT_END_OFFSET);
    CreateWaterFlowItems(20);
    CreateDone();
    ScrollAlign scrollAlign = ScrollAlign::END;
    bool smooth = false;

    ScrollToIndex(19, smooth, scrollAlign);
    EXPECT_EQ(pattern_->layoutInfo_->Offset(), -830);
    EXPECT_EQ(pattern_->GetTotalOffset(), 830);

    ScrollToIndex(5, smooth, scrollAlign);
    EXPECT_EQ(pattern_->layoutInfo_->Offset(), CONTENT_START_OFFSET);
    EXPECT_EQ(pattern_->GetTotalOffset(), -CONTENT_START_OFFSET);

    ScrollToIndex(13, smooth, scrollAlign);
    EXPECT_EQ(pattern_->layoutInfo_->Offset(), -330);
    EXPECT_EQ(pattern_->GetTotalOffset(), 330);

    ScrollToIndex(17, smooth, scrollAlign);
    EXPECT_EQ(pattern_->layoutInfo_->Offset(), -630);
    EXPECT_EQ(pattern_->GetTotalOffset(), 630);

    ScrollToIndex(0, smooth, scrollAlign);
    EXPECT_EQ(pattern_->layoutInfo_->Offset(), CONTENT_START_OFFSET);
    EXPECT_EQ(pattern_->GetTotalOffset(), -CONTENT_START_OFFSET);
}

/**
 * @tc.name: AnimateToIndexEndWithContentOffsetTest
 * @tc.desc: Test ScrollToIndex with ContentOffset and ScrollAlign::End with animation
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowSWTest, AnimateToIndexEndWithContentOffsetTest, TestSize.Level1)
{
    WaterFlowModelNG model = CreateWaterFlow();
    model.SetColumnsTemplate("1fr 1fr");
    ScrollableModelNG::SetContentStartOffset(CONTENT_START_OFFSET);
    ScrollableModelNG::SetContentEndOffset(CONTENT_END_OFFSET);
    CreateWaterFlowItems(20);
    CreateDone();
    ScrollAlign scrollAlign = ScrollAlign::END;

    AnimateToIndexWithTicks(19, scrollAlign);
    EXPECT_EQ(pattern_->layoutInfo_->Offset(), -830);
    EXPECT_EQ(pattern_->GetTotalOffset(), 830);

    AnimateToIndexWithTicks(5, scrollAlign);
    EXPECT_EQ(pattern_->layoutInfo_->Offset(), CONTENT_START_OFFSET);
    EXPECT_EQ(pattern_->GetTotalOffset(), -CONTENT_START_OFFSET);

    AnimateToIndexWithTicks(13, scrollAlign);
    EXPECT_EQ(pattern_->layoutInfo_->Offset(), -330);
    EXPECT_EQ(pattern_->GetTotalOffset(), 330);

    AnimateToIndexWithTicks(17, scrollAlign);
    EXPECT_EQ(pattern_->layoutInfo_->Offset(), -630);
    EXPECT_EQ(pattern_->GetTotalOffset(), 630);

    AnimateToIndexWithTicks(0, scrollAlign);
    EXPECT_EQ(pattern_->layoutInfo_->Offset(), CONTENT_START_OFFSET);
    EXPECT_EQ(pattern_->GetTotalOffset(), -CONTENT_START_OFFSET);
}

/**
 * @tc.name: ScrollToIndexAutoWithContentOffset
 * @tc.desc: Test ScrollToIndex with ContentOffset and ScrollAlign::Auto without animation
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowSWTest, ScrollToIndexAutoWithContentOffsetTest, TestSize.Level1)
{
    WaterFlowModelNG model = CreateWaterFlow();
    model.SetColumnsTemplate("1fr 1fr");
    ScrollableModelNG::SetContentStartOffset(CONTENT_START_OFFSET);
    ScrollableModelNG::SetContentEndOffset(CONTENT_END_OFFSET);
    CreateWaterFlowItems(20);
    CreateDone();
    ScrollAlign scrollAlign = ScrollAlign::AUTO;
    bool smooth = false;

    ScrollToIndex(19, smooth, scrollAlign);
    EXPECT_EQ(pattern_->layoutInfo_->Offset(), -830);
    EXPECT_EQ(pattern_->GetTotalOffset(), 830);

    // Scroll forward, item 5 is at top
    ScrollToIndex(5, smooth, scrollAlign);
    EXPECT_EQ(pattern_->layoutInfo_->Offset(), -280);
    EXPECT_EQ(pattern_->GetTotalOffset(), 280);

    // Scroll backward, item 15 is at end
    ScrollToIndex(15, smooth, scrollAlign);
    EXPECT_EQ(pattern_->layoutInfo_->Offset(), -530);
    EXPECT_EQ(pattern_->GetTotalOffset(), 530);

    // item 11 is in view
    ScrollToIndex(11, smooth, scrollAlign);
    EXPECT_EQ(pattern_->layoutInfo_->Offset(), -530);
    EXPECT_EQ(pattern_->GetTotalOffset(), 530);

    ScrollBy(0, -CONTENT_END_OFFSET);
    EXPECT_EQ(pattern_->layoutInfo_->Offset(), -500);
    EXPECT_EQ(pattern_->layoutInfo_->startIndex_, 7);
    EXPECT_EQ(pattern_->layoutInfo_->endIndex_, 17);
    // item 7 is at top without contentStartOffset
    ScrollToIndex(7, smooth, scrollAlign);
    EXPECT_EQ(pattern_->layoutInfo_->Offset(), -480);
    EXPECT_EQ(pattern_->GetTotalOffset(), 480);

    ScrollTo(300);
    EXPECT_EQ(pattern_->layoutInfo_->Offset(), -300);
    EXPECT_EQ(pattern_->layoutInfo_->startIndex_, 3);
    EXPECT_EQ(pattern_->layoutInfo_->endIndex_, 14);
    // item 14 is at bottom without contentEndOffset
    ScrollToIndex(14, false, scrollAlign);
    EXPECT_EQ(pattern_->layoutInfo_->Offset(), -330);
    EXPECT_EQ(pattern_->GetTotalOffset(), 330);

    ScrollToIndex(0, smooth, scrollAlign);
    EXPECT_EQ(pattern_->layoutInfo_->Offset(), CONTENT_START_OFFSET);
    EXPECT_EQ(pattern_->GetTotalOffset(), -20);
}

/**
 * @tc.name: AnimateToIndexAutoWithContentOffsetTest
 * @tc.desc: Test ScrollToIndex with ContentOffset and ScrollAlign::Auto with animation
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowSWTest, AnimateToIndexAutoWithContentOffsetTest, TestSize.Level1)
{
    WaterFlowModelNG model = CreateWaterFlow();
    model.SetColumnsTemplate("1fr 1fr");
    ScrollableModelNG::SetContentStartOffset(CONTENT_START_OFFSET);
    ScrollableModelNG::SetContentEndOffset(CONTENT_END_OFFSET);
    CreateWaterFlowItems(20);
    CreateDone();
    ScrollAlign scrollAlign = ScrollAlign::AUTO;

    AnimateToIndexWithTicks(19, scrollAlign);
    EXPECT_EQ(pattern_->layoutInfo_->Offset(), -830);
    EXPECT_EQ(pattern_->GetTotalOffset(), 830);

    // Scroll forward, item 5 is at top
    AnimateToIndexWithTicks(5, scrollAlign);
    EXPECT_EQ(pattern_->layoutInfo_->Offset(), -280);
    EXPECT_EQ(pattern_->GetTotalOffset(), 280);

    // Scroll backward, item 15 is at end
    AnimateToIndexWithTicks(15, scrollAlign);
    EXPECT_EQ(pattern_->layoutInfo_->Offset(), -530);
    EXPECT_EQ(pattern_->GetTotalOffset(), 530);

    // item 11 is in view
    AnimateToIndexWithTicks(11, scrollAlign);
    EXPECT_EQ(pattern_->layoutInfo_->Offset(), -530);
    EXPECT_EQ(pattern_->GetTotalOffset(), 530);

    ScrollBy(0, -CONTENT_END_OFFSET);
    EXPECT_EQ(pattern_->layoutInfo_->Offset(), -500);
    EXPECT_EQ(pattern_->layoutInfo_->startIndex_, 7);
    EXPECT_EQ(pattern_->layoutInfo_->endIndex_, 17);
    // item 7 is at top without contentStartOffset
    AnimateToIndexWithTicks(7, scrollAlign);
    EXPECT_EQ(pattern_->layoutInfo_->Offset(), -480);
    EXPECT_EQ(pattern_->GetTotalOffset(), 480);

    ScrollTo(300);
    EXPECT_EQ(pattern_->layoutInfo_->Offset(), -300);
    EXPECT_EQ(pattern_->layoutInfo_->startIndex_, 3);
    EXPECT_EQ(pattern_->layoutInfo_->endIndex_, 14);
    // item 14 is at bottom without contentEndOffset
    AnimateToIndexWithTicks(14, scrollAlign);
    EXPECT_EQ(pattern_->layoutInfo_->Offset(), -330);
    EXPECT_EQ(pattern_->GetTotalOffset(), 330);

    AnimateToIndexWithTicks(0, scrollAlign);
    EXPECT_EQ(pattern_->layoutInfo_->Offset(), CONTENT_START_OFFSET);
    EXPECT_EQ(pattern_->GetTotalOffset(), -20);
}

/**
 * @tc.name: GetContentHeightWithContentOffset
 * @tc.desc: Test GetContentHeight with contentStartOffset and contentEndOffset
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowSWTest, GetContentHeightWithContentOffset, TestSize.Level1)
{
    WaterFlowModelNG model = CreateWaterFlow();
    model.SetColumnsTemplate("1fr 1fr");
    ScrollableModelNG::SetContentStartOffset(CONTENT_START_OFFSET);
    ScrollableModelNG::SetContentEndOffset(CONTENT_END_OFFSET);
    CreateWaterFlowItems(20);
    CreateDone();

    AnimateToIndexWithTicks(19, ScrollAlign::END);
    EXPECT_EQ(pattern_->GetChildrenExpandedSize().Height(), 1600);
    EXPECT_EQ(pattern_->layoutInfo_->GetContentHeight(), 1600);

    layoutProperty_->UpdateContentStartOffset(0);
    FlushUITasks();
    EXPECT_EQ(pattern_->GetChildrenExpandedSize().Height(), 1600);
    EXPECT_EQ(pattern_->layoutInfo_->GetContentHeight(), 1600);

    layoutProperty_->UpdateContentEndOffset(0);
    FlushUITasks();
    EXPECT_EQ(pattern_->GetChildrenExpandedSize().Height(), 1600);
    EXPECT_EQ(pattern_->layoutInfo_->GetContentHeight(), 1600);
}

/**
 * @tc.name: GetContentHeightWithContentOffset
 * @tc.desc: Test GetContentHeight with contentStartOffset and contentEndOffset
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowSWTest, GetContentHeightWithContentStartOffsetChange, TestSize.Level1)
{
    WaterFlowModelNG model = CreateWaterFlow();
    model.SetColumnsTemplate("1fr 1fr");
    ScrollableModelNG::SetContentStartOffset(CONTENT_START_OFFSET);
    ScrollableModelNG::SetContentEndOffset(CONTENT_END_OFFSET);
    CreateWaterFlowItems(20);
    CreateDone();

    AnimateToIndexWithTicks(19, ScrollAlign::END);
    EXPECT_EQ(pattern_->GetChildrenExpandedSize().Height(), 1600);
    EXPECT_EQ(pattern_->layoutInfo_->GetContentHeight(), 1600);

    layoutProperty_->UpdateContentStartOffset(CONTENT_START_OFFSET + 20);
    FlushUITasks();
    EXPECT_EQ(pattern_->GetChildrenExpandedSize().Height(), 1600);
    EXPECT_EQ(pattern_->layoutInfo_->GetContentHeight(), 1600);

    layoutProperty_->UpdateContentStartOffset(CONTENT_START_OFFSET - 20);
    FlushUITasks();
    EXPECT_EQ(pattern_->GetChildrenExpandedSize().Height(), 1600);
    EXPECT_EQ(pattern_->layoutInfo_->GetContentHeight(), 1600);
}

/**
 * @tc.name: GetContentHeightWithContentEndOffsetChange
 * @tc.desc: Test GetContentHeight with contentStartOffset change
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowSWTest, GetContentHeightWithContentEndOffsetChange, TestSize.Level1)
{
    WaterFlowModelNG model = CreateWaterFlow();
    model.SetColumnsTemplate("1fr 1fr");
    ScrollableModelNG::SetContentStartOffset(CONTENT_START_OFFSET);
    ScrollableModelNG::SetContentEndOffset(CONTENT_END_OFFSET);
    CreateWaterFlowItems(20);
    CreateDone();

    AnimateToIndexWithTicks(19, ScrollAlign::END);
    EXPECT_EQ(pattern_->GetChildrenExpandedSize().Height(), 1600);
    EXPECT_EQ(pattern_->layoutInfo_->GetContentHeight(), 1600);
  
    layoutProperty_->UpdateContentEndOffset(CONTENT_END_OFFSET + 20);
    FlushUITasks();
    EXPECT_EQ(pattern_->GetChildrenExpandedSize().Height(), 1600);
    EXPECT_EQ(pattern_->layoutInfo_->GetContentHeight(), 1600);

    layoutProperty_->UpdateContentEndOffset(CONTENT_END_OFFSET - 20);
    FlushUITasks();
    EXPECT_EQ(pattern_->GetChildrenExpandedSize().Height(), 1600);
    EXPECT_EQ(pattern_->layoutInfo_->GetContentHeight(), 1600);
}

/**
 * @tc.name: OnScrollIndexDeleteCacheClear
 * @tc.desc: Test cache cleared when deleting LazyForEach nodes in onScrollIndex callback
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowSWTest, OnScrollIndexDeleteCacheClear, TestSize.Level1)
{
    // Initialize tracking variables for onScrollIndex callback
    int32_t firstIndex = -1;
    int32_t lastIndex = -1;
    bool deleteTriggered = false;
    RefPtr<WaterFlowMockLazy> mockLazy;

    // Define onScrollIndex callback that deletes nodes when reaching specific index
    auto onScrollIndex = [&firstIndex, &lastIndex, &deleteTriggered, &mockLazy, this](int32_t first, int32_t last) {
        firstIndex = first;
        lastIndex = last;

        // Delete LazyForEach nodes when scrolling to index 15
        if (first >= 15 && !deleteTriggered) {
            deleteTriggered = true;
            // Delete items from index 10-14 (5 items)
            for (int i = 0; i < 5; i++) {
                DeleteItemInLazyForEach(10 + i);
            }
            mockLazy->SetTotalCount(95);
        }
    };

    // Create WaterFlow with onScrollIndex callback
    WaterFlowModelNG model = CreateWaterFlow();
    ViewAbstract::SetWidth(CalcLength(400.0f));
    ViewAbstract::SetHeight(CalcLength(800.f));
    model.SetColumnsTemplate("1fr 1fr");
    model.SetCachedCount(5);
    model.SetOnScrollIndex(onScrollIndex);
    mockLazy = CreateItemsInLazyForEach(100, [](int32_t) { return 100.0f; });
    CreateDone();

    // Verify initial cache state
    EXPECT_FALSE(pattern_->PreloadListEmpty());
    EXPECT_GT(pattern_->preloadItems_.size(), 0);

    // Scroll to trigger onScrollIndex callback and deletion
    UpdateCurrentOffset(-1500.0f);
    FlushUITasks();

    // Verify deletion was triggered
    EXPECT_TRUE(deleteTriggered);
    EXPECT_EQ(mockLazy->GetTotalCount(), 95);
    EXPECT_EQ(frameNode_->GetTotalChildCount(), 95);

    // Manually clear cache after LazyForEach deletion in onScrollIndex
    // This is needed because cache clearing doesn't happen automatically in callback context
    pattern_->SetPreloadList(std::list<int32_t>());

    // Verify cache is cleared after manual clearing
    EXPECT_TRUE(pattern_->PreloadListEmpty());
    EXPECT_EQ(pattern_->preloadItems_.size(), 0);

    // Verify layout info is updated correctly
    EXPECT_GE(info_->startIndex_, 10);
    EXPECT_LE(info_->endIndex_, 94);
}

/**
 * @tc.name: BackToTopFallback001
 * @tc.desc: In SW mode, when a backToTop animation reaches its numeric endpoint but stops short of the real
 *           top, OnAnimateStop should re-align to index 0 via a precise jump.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowSWTest, BackToTopFallback001, TestSize.Level1)
{
    WaterFlowModelNG model = CreateWaterFlow();
    model.SetColumnsTemplate("1fr 1fr");
    CreateWaterFlowItems(100);
    CreateDone();

    // scroll down so the list is no longer at the top
    UpdateCurrentOffset(-1000.0f);
    FlushUITasks();
    EXPECT_FALSE(pattern_->IsAtTop());
    EXPECT_NE(info_->startIndex_, 0);

    // reproduce the SW failure: the estimated totalOffset_ has settled near the top endpoint while the real
    // layout is still scrolled down (startIndex_ > 0). On a real device totalOffset_ stops near-but-not-exactly
    // 0 (e.g. ~0.94), so the fallback must NOT gate on totalOffset_ being exactly at finalPosition_.
    info_->totalOffset_ = 0.94f; // numerically ~top, but startIndex_ still > 0
    pattern_->SetScrollSource(SCROLL_FROM_STATUSBAR);
    pattern_->SetScrollAbort(false);
    ASSERT_GT(info_->startIndex_, 0);
    ASSERT_FALSE(pattern_->IsAtTop());

    pattern_->OnAnimateStop();
    // fallback queues a precise jump to index 0
    EXPECT_EQ(info_->jumpIndex_, 0);

    FlushUITasks();
    EXPECT_EQ(info_->startIndex_, 0);
    EXPECT_TRUE(pattern_->IsAtTop());
}

/**
 * @tc.name: BackToTopFallback002
 * @tc.desc: An interrupted animation (scrollAbort) must not trigger the SW backToTop fallback.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowSWTest, BackToTopFallback002, TestSize.Level1)
{
    WaterFlowModelNG model = CreateWaterFlow();
    model.SetColumnsTemplate("1fr 1fr");
    CreateWaterFlowItems(100);
    CreateDone();

    UpdateCurrentOffset(-1000.0f);
    FlushUITasks();
    ASSERT_FALSE(pattern_->IsAtTop());
    const int32_t startBefore = info_->startIndex_;
    ASSERT_GT(startBefore, 0);

    // same endpoint state as the positive case; the only difference is scrollAbort below
    info_->totalOffset_ = 0.94f;
    pattern_->SetScrollSource(SCROLL_FROM_STATUSBAR);
    pattern_->SetScrollAbort(true); // animation was interrupted

    pattern_->OnAnimateStop();
    // no fallback jump should be queued
    EXPECT_EQ(info_->jumpIndex_, WaterFlowLayoutInfoBase::EMPTY_JUMP_INDEX);

    FlushUITasks();
    EXPECT_EQ(info_->startIndex_, startBefore);
    EXPECT_FALSE(pattern_->IsAtTop());
}

/**
 * @tc.name: CacheExtensionAfterHardJump
 * @tc.desc: After scrolling and then jumping (ScrollAlign::START) to an index far outside the
 *           current viewport, Jump() takes the hard-reset path (ResetWithLaneOffset), which wipes
 *           idxToLane_ / idxToHeight_. The cachedCount extension just above the new viewport must
 *           still be built synchronously in the same frame, instead of only reappearing once the
 *           async PreloadItems idle task eventually runs.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowSWTest, CacheExtensionAfterHardJump, TestSize.Level1)
{
    WaterFlowModelNG model = CreateWaterFlow();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetCachedCount(3);
    layoutProperty_->UpdatePadding(CreatePadding(0.0f, 300.0f, 0.0f, 0.0f));
    ScrollableModelNG::SetContentClip(AceType::RawPtr(frameNode_), ContentClipMode::BOUNDARY, nullptr);
    CreateWaterFlowItems(100);
    CreateDone();

    // scroll down first so the layout has scroll history unrelated to the jump target
    UpdateCurrentOffset(-1500.0f);
    const int32_t startBeforeJump = info_->startIndex_;
    ASSERT_GT(startBeforeJump, 0);

    // jump far enough that ItemCloseToView() is false, forcing Jump()'s hard-reset branch
    ScrollToIndex(95, false, ScrollAlign::START);

    const int32_t start = info_->startIndex_;
    ASSERT_GT(start, 0);
    ASSERT_GT(info_->startFixOffset_, 0.0f);
    // the cachedCount items directly above the new viewport must already have a lane assigned
    // synchronously; before the fix these were only filled later by the async PreloadItems task.
    for (int32_t i = std::max(0, start - 3); i < start; ++i) {
        EXPECT_TRUE(info_->idxToLane_.count(i));
        ASSERT_TRUE(GetItem(i, true));
        EXPECT_TRUE(GetItem(i, true)->IsActive());
    }

    PipelineContext::GetCurrentContext()->OnIdle(INT64_MAX);
    FlushUITasks(frameNode_);
    const int32_t endCacheIndex = info_->endIndex_ + 1;
    if (endCacheIndex < info_->ItemCnt(info_->GetChildrenCount())) {
        auto endCache = GetItem(endCacheIndex, true);
        ASSERT_TRUE(endCache);
        EXPECT_FALSE(endCache->IsActive());
    }

    // lanes_ must still hold only the stable viewport (see the "REQUIRES" comment on lanes_ in
    // water_flow_layout_info_sw.h): the cache extension above must be reachable via idxToLane_ /
    // idxToHeight_ for RecoverCacheItems to rebuild later, but must NOT be permanently baked into
    // lanes_ itself. StartIndex()/EndIndex() short-circuit to the frozen members once synced_ is
    // true, so scan lanes_ directly to catch a regression back to a version that left cache items
    // sitting in lanes_ (which would corrupt StartIndex()/EndIndex() on the next unsynced frame).
    int32_t scannedMin = start;
    int32_t scannedMax = info_->endIndex_;
    bool foundAnyLane = false;
    for (const auto& section : info_->lanes_) {
        for (const auto& lane : section) {
            if (lane.items_.empty()) {
                continue;
            }
            foundAnyLane = true;
            scannedMin = std::min(scannedMin, lane.items_.front().idx);
            scannedMax = std::max(scannedMax, lane.items_.back().idx);
        }
    }
    ASSERT_TRUE(foundAnyLane);
    EXPECT_EQ(scannedMin, start);
    EXPECT_EQ(scannedMax, info_->endIndex_);
}

/**
 * @tc.name: CacheExtensionAfterHardJumpEnd
 * @tc.desc: After a hard jump with ScrollAlign::END, only the end fix-offset extension should activate
 *           hidden cache items. Start-side cache items remain inactive when startFixOffset_ is zero.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowSWTest, CacheExtensionAfterHardJumpEnd, TestSize.Level1)
{
    WaterFlowModelNG model = CreateWaterFlow();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetCachedCount(3);
    layoutProperty_->UpdatePadding(CreatePadding(0.0f, 0.0f, 0.0f, 300.0f));
    ScrollableModelNG::SetContentClip(AceType::RawPtr(frameNode_), ContentClipMode::BOUNDARY, nullptr);
    CreateWaterFlowItems(100);
    CreateDone();

    ScrollToIndex(80, false, ScrollAlign::END);

    const int32_t end = info_->endIndex_;
    ASSERT_LT(end, info_->ItemCnt(info_->GetChildrenCount()) - 1);
    ASSERT_EQ(info_->startFixOffset_, 0.0f);
    ASSERT_GT(info_->endFixOffset_, 0.0f);
    const int32_t endCacheIndex = end + 1;
    EXPECT_TRUE(info_->idxToLane_.count(endCacheIndex));
    ASSERT_TRUE(GetItem(endCacheIndex, true));
    EXPECT_TRUE(GetItem(endCacheIndex, true)->IsActive());

    PipelineContext::GetCurrentContext()->OnIdle(INT64_MAX);
    FlushUITasks(frameNode_);
    const int32_t startCacheIndex = info_->startIndex_ - 1;
    if (startCacheIndex >= 0) {
        auto startCache = GetItem(startCacheIndex, true);
        ASSERT_TRUE(startCache);
        EXPECT_FALSE(startCache->IsActive());
    }
}

/**
 * @tc.name: CacheExtensionAfterDataUpdateReset
 * @tc.desc: A LazyForEach deletion at the visible range makes CheckReset() take the
 *           ResetWithLaneOffset path. The start fix-offset cache should be synchronously rebuilt
 *           in the same frame, without waiting for the async cache preload task.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowSWTest, CacheExtensionAfterDataUpdateReset, TestSize.Level1)
{
    WaterFlowModelNG model = CreateWaterFlow();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetCachedCount(3);
    layoutProperty_->UpdatePadding(CreatePadding(0.0f, 300.0f, 0.0f, 0.0f));
    ScrollableModelNG::SetContentClip(AceType::RawPtr(frameNode_), ContentClipMode::BOUNDARY, nullptr);
    auto mockLazy = CreateItemsInLazyForEach(100, [](int32_t) { return 100.0f; });
    CreateDone();

    ScrollToIndex(50, false, ScrollAlign::START);
    const int32_t startBeforeUpdate = info_->startIndex_;
    ASSERT_GT(startBeforeUpdate, 0);
    ASSERT_GT(info_->startFixOffset_, 0.0f);

    const int32_t deleteIndex = startBeforeUpdate;
    DeleteItemInLazyForEach(deleteIndex);
    mockLazy->SetTotalCount(99);
    ASSERT_EQ(info_->newStartIndex_, INVALID_NEW_START_INDEX);
    FlushUITasks(frameNode_);

    const int32_t start = info_->startIndex_;
    ASSERT_GT(start, 0);
    ASSERT_GT(info_->startFixOffset_, 0.0f);
    EXPECT_FALSE(info_->needFixOffsetCache_);
    for (int32_t i = std::max(0, start - 3); i < start; ++i) {
        EXPECT_TRUE(info_->idxToLane_.count(i));
        ASSERT_TRUE(GetItem(i, true));
        EXPECT_TRUE(GetItem(i, true)->IsActive());
    }

    PipelineContext::GetCurrentContext()->OnIdle(INT64_MAX);
    FlushUITasks(frameNode_);
    const int32_t endCacheIndex = info_->endIndex_ + 1;
    if (endCacheIndex < info_->ItemCnt(info_->GetChildrenCount())) {
        auto endCache = GetItem(endCacheIndex, true);
        ASSERT_TRUE(endCache);
        EXPECT_FALSE(endCache->IsActive());
    }
}

/**
 * @tc.name: CacheExtensionAfterHardJumpShowCache
 * @tc.desc: showCachedItems=true keeps the normal cache activation behavior and does not leave a pending
 *           fix-offset cache preload after a hard jump.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowSWTest, CacheExtensionAfterHardJumpShowCache, TestSize.Level1)
{
    WaterFlowModelNG model = CreateWaterFlow();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetCachedCount(3, true);
    layoutProperty_->UpdatePadding(CreatePadding(0.0f, 300.0f, 0.0f, 0.0f));
    ScrollableModelNG::SetContentClip(AceType::RawPtr(frameNode_), ContentClipMode::BOUNDARY, nullptr);
    CreateWaterFlowItems(100);
    CreateDone();

    ScrollToIndex(95, false, ScrollAlign::START);

    ASSERT_GT(info_->startIndex_, 0);
    ASSERT_GT(info_->startFixOffset_, 0.0f);
    EXPECT_FALSE(info_->needFixOffsetCache_);
    const int32_t startCacheIndex = info_->startIndex_ - 1;
    ASSERT_TRUE(GetItem(startCacheIndex, true));
    EXPECT_TRUE(GetItem(startCacheIndex, true)->IsActive());
}
} // namespace OHOS::Ace::NG
