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
#include "water_flow_item_maps.h"
#include "water_flow_test_ng.h"

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
} // namespace OHOS::Ace::NG
