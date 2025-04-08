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
#include "test/mock/core/pattern/mock_koala_lazy_for_each.h"
#include "water_flow_test_ng.h"

#include "core/components_ng/syntax/lazy_for_each_node.h"

namespace OHOS::Ace::NG {
class WaterFlowArkoalaTest : public WaterFlowTestNg {
public:
    void IncrementAndLayout(int32_t lineNumber = -1)
    {
        lazy_.Increment(lineNumber);
        frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
        FlushUITasks(frameNode_);
    }
    void InitMockLazy(int32_t itemCnt)
    {
        // generated random numbers between 100 and 300
        std::vector<int> height = { 183, 300, 244, 287, 100, 125, 160, 300, 129, 147, 118, 179, 137, 177, 169, 234, 179,
            288, 208, 270, 184, 162, 237, 205, 141, 189, 276, 146, 105, 207, 234, 283, 183, 191, 212, 186, 128, 288,
            139, 256, 260, 243, 294, 261, 162, 118, 239, 204, 276, 273, 279, 266, 117, 266, 107, 154, 134, 111, 276,
            234, 119, 219, 184, 235, 292, 182, 207, 139, 239, 158, 163, 128, 237, 257, 267, 182, 103, 106, 250, 225,
            298, 232, 250, 159, 156, 189, 258, 144, 120, 114, 190, 194, 282, 119, 159, 281, 157, 124, 126, 205 };
        lazy_ = MockKoalaLazyForEach(frameNode_.GetRawPtr(), itemCnt, [height](int32_t idx) {
            auto node = WaterFlowItemModelNG::CreateFrameNode(-1);
            node->GetLayoutProperty()->UpdateUserDefinedIdealSize(
                CalcSize(CalcLength(1, DimensionUnit::PERCENT), CalcLength(height[idx])));
            return node;
        });
        lazy_.Register();
    }

    MockKoalaLazyForEach lazy_;
};

/**
 * @tc.name: Basic001
 * @tc.desc: Test ScrollWindowAdapter with MockKoala
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowArkoalaTest, Basic001, TestSize.Level1)
{
    WaterFlowModelNG model = CreateWaterFlow();
    model.SetColumnsTemplate("1fr 1fr");
    InitMockLazy(100);
    CreateDone();

    IncrementAndLayout(__LINE__);
    EXPECT_EQ(lazy_.GetRange(), std::pair(0, 8));
    EXPECT_EQ(GetChildY(frameNode_, 6), 587);

    UpdateCurrentOffset(-400.0f);
    IncrementAndLayout(__LINE__);
    EXPECT_EQ(lazy_.GetRange(), std::pair(2, 12));
    EXPECT_EQ(pattern_->layoutInfo_->startIndex_, 2);
    EXPECT_EQ(GetChildRect(frameNode_, 12).ToString(), "RectT (0.00, 670.00) - [240.00 x 137.00]");
    EXPECT_EQ(GetChildRect(frameNode_, 3).ToString(), "RectT (240.00, -100.00) - [240.00 x 287.00]");

    UpdateCurrentOffset(-500.0f);
    IncrementAndLayout(__LINE__);
    EXPECT_EQ(lazy_.GetRange(), std::pair(7, 18));
    EXPECT_EQ(GetChildRect(frameNode_, 10).ToString(), "RectT (0.00, 52.00) - [240.00 x 118.00]");
    EXPECT_EQ(GetChildRect(frameNode_, 15).ToString(), "RectT (0.00, 476.00) - [240.00 x 234.00]");

    layoutProperty_->UpdateUserDefinedIdealSize(CalcSize(CalcLength(480.0f), CalcLength(1200.0f)));
    FlushUITasks(frameNode_);
    IncrementAndLayout(__LINE__);
    EXPECT_EQ(lazy_.GetRange(), std::pair(7, 22));
    EXPECT_EQ(GetChildRect(frameNode_, 19).ToString(), "RectT (0.00, 918.00) - [240.00 x 270.00]");

    UpdateCurrentOffset(300.0f);
    IncrementAndLayout(__LINE__);
    EXPECT_EQ(lazy_.GetRange(), std::pair(5, 18));
    EXPECT_FALSE(GetChildFrameNode(frameNode_, 4));

    UpdateCurrentOffset(-51.0f);
    IncrementAndLayout(__LINE__);
    EXPECT_EQ(lazy_.GetRange(), std::pair(5, 20));

    UpdateCurrentOffset(2.0f);
    EXPECT_FALSE(lazy_.NeedRecompose());
    UpdateCurrentOffset(-2.0f);
    EXPECT_FALSE(lazy_.NeedRecompose());
}

/**
 * @tc.name: Jump001
 * @tc.desc: Test jump on ScrollWindowAdapter with MockKoala
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowArkoalaTest, Jump001, TestSize.Level1)
{
    WaterFlowModelNG model = CreateWaterFlow();
    model.SetColumnsTemplate("1fr 1fr");
    InitMockLazy(100);
    CreateDone();
    IncrementAndLayout(__LINE__);
    if (pattern_->layoutInfo_->Mode() == WaterFlowLayoutMode::TOP_DOWN) {
        return; // currently doesn't support direct jump
    }
    pattern_->ScrollToIndex(90);
    FlushUITasks(frameNode_);
    IncrementAndLayout(__LINE__);
    EXPECT_EQ(lazy_.GetRange(), std::pair(90, 99));
    EXPECT_EQ(pattern_->layoutInfo_->startIndex_, 90);
    EXPECT_EQ(GetChildRect(frameNode_, 93).ToString(), "RectT (240.00, 194.00) - [240.00 x 119.00]");
    EXPECT_EQ(GetChildRect(frameNode_, 94).ToString(), "RectT (240.00, 313.00) - [240.00 x 159.00]");
}

/**
 * @tc.name: Reset001
 * @tc.desc: Test data reset
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowArkoalaTest, Reset001, TestSize.Level1)
{
    WaterFlowModelNG model = CreateWaterFlow();
    model.SetColumnsTemplate("1fr 1fr");
    InitMockLazy(100);
    CreateDone();
    IncrementAndLayout(__LINE__);

    if (pattern_->layoutInfo_->Mode() == WaterFlowLayoutMode::TOP_DOWN) {
        return; // currently doesn't support direct jump
    }

    pattern_->ScrollToIndex(50);
    FlushUITasks(frameNode_);
    IncrementAndLayout(__LINE__);
    EXPECT_EQ(lazy_.GetRange(), std::pair(50, 59));
    EXPECT_EQ(pattern_->layoutInfo_->startIndex_, 50);

    UpdateCurrentOffset(-30.0f);
    EXPECT_EQ(GetChildY(frameNode_, 51), -30.0f);
    
    frameNode_->ChildrenUpdatedFrom(40);
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    FlushUITasks(frameNode_);
    EXPECT_FALSE(lazy_.NeedRecompose());


    frameNode_->ChildrenUpdatedFrom(52);
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    FlushUITasks(frameNode_);
    IncrementAndLayout(__LINE__);
    EXPECT_EQ(lazy_.GetRange(), std::pair(50, 59));

    EXPECT_EQ(GetChildY(frameNode_, 53), 249.0f);
    frameNode_->ChildrenUpdatedFrom(56);
    UpdateCurrentOffset(-100.0f);
    IncrementAndLayout(__LINE__);
    EXPECT_EQ(lazy_.GetRange(), std::pair(50, 59));
    EXPECT_EQ(GetChildY(frameNode_, 53), 149.0f);
}
} // namespace OHOS::Ace::NG
