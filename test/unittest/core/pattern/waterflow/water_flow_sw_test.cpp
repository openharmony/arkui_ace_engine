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

#include "water_flow_item_maps.h"
#include "water_flow_test_ng.h"

#include "core/components_ng/pattern/waterflow/layout/sliding_window/water_flow_layout_info_sw.h"

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
} // namespace OHOS::Ace::NG