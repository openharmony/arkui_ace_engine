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
#include <random>

#include "test/mock/core/pattern/mock_koala_lazy_for_each.h"
#include "water_flow_test_ng.h"
namespace OHOS::Ace::NG {
class WaterFlowArkoalaTest : public WaterFlowTestNg {
public:
    void IncrementAndLayout(int32_t lineNumber = -1)
    {
        lazy_.Increment(lineNumber);
        frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
        FlushLayoutTask(frameNode_);
    }
    void InitMockLazy(int32_t itemCnt)
    {
        // to generate random numbers between 100 and 300
        std::mt19937 rng(1); // Mersenne Twister engine
        std::uniform_int_distribution<int> dist(100, 300);
        std::vector<int> height;
        for (int i = 0; i < 100; ++i) {
            height.emplace_back(dist(rng));
        }

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
    CreateDone(frameNode_);

    IncrementAndLayout(__LINE__);
    EXPECT_EQ(lazy_.GetRange(), std::pair(0, 7));
    EXPECT_EQ(GetChildY(frameNode_, 6), 542);

    UpdateCurrentOffset(-400.0f);
    IncrementAndLayout(__LINE__);
    EXPECT_EQ(lazy_.GetRange(), std::pair(3, 12));
    EXPECT_EQ(pattern_->layoutInfo_->startIndex_, 3);
    EXPECT_EQ(GetChildRect(frameNode_, 12).ToString(), "RectT (240.00, 796.00) - [240.00 x 278.00]");
    EXPECT_EQ(GetChildRect(frameNode_, 3).ToString(), "RectT (240.00, -160.00) - [240.00 x 237.00]");

    UpdateCurrentOffset(-500.0f);
    IncrementAndLayout(__LINE__);
    EXPECT_EQ(lazy_.GetRange(), std::pair(8, 16));
    EXPECT_EQ(GetChildRect(frameNode_, 10).ToString(), "RectT (0.00, 163.00) - [240.00 x 234.00]");
    EXPECT_EQ(GetChildRect(frameNode_, 15).ToString(), "RectT (240.00, 574.00) - [240.00 x 246.00]");

    layoutProperty_->UpdateUserDefinedIdealSize(CalcSize(CalcLength(480.0f), CalcLength(1200.0f)));
    FlushLayoutTask(frameNode_);
    IncrementAndLayout(__LINE__);
    EXPECT_EQ(lazy_.GetRange(), std::pair(8, 19));
    EXPECT_EQ(GetChildRect(frameNode_, 19).ToString(), "RectT (240.00, 1076.00) - [240.00 x 242.00]");

    UpdateCurrentOffset(300.0f);
    IncrementAndLayout(__LINE__);
    EXPECT_EQ(lazy_.GetRange(), std::pair(5, 17));
    EXPECT_FALSE(GetChildFrameNode(frameNode_, 4));

    UpdateCurrentOffset(-51.0f);
    EXPECT_FALSE(lazy_.NeedRecompose());

    UpdateCurrentOffset(2.0f);
    EXPECT_FALSE(lazy_.NeedRecompose());
    UpdateCurrentOffset(-2.0f);
    EXPECT_FALSE(lazy_.NeedRecompose());
}
} // namespace OHOS::Ace::NG
