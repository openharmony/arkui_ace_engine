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
#include <random>

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
    std::mt19937 rng(1); // random number generator
    std::uniform_int_distribution<int> dist(100, 300);
    for (int i = 0; i < 45; ++i) {
        CreateItemWithHeight(dist(rng));
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
} // namespace OHOS::Ace::NG