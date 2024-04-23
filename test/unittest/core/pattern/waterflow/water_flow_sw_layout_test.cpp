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
#include "test/unittest/core/pattern/waterflow/water_flow_test_ng.h"

#include "core/components_ng/pattern/waterflow/layout/sliding_window/water_flow_layout_info_sw.h"
namespace OHOS::Ace::NG {
class WaterFlowSWTest : public WaterFlowTestNg {
protected:
    void GetInstance() override
    {
        WaterFlowTestNg::GetInstance();
        info_ = AceType::DynamicCast<WaterFlowLayoutInfoSW>(pattern_->layoutInfo_);
        EXPECT_TRUE(info_);
    }

    RefPtr<WaterFlowLayoutInfoSW> info_;
};

/**
 * @tc.name: Regular001
 * @tc.desc: waterFlow with fixed column
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowSWTest, Regular001, TestSize.Level1)
{
    CreateWithItem([](WaterFlowModelNG model) {
        ViewAbstract::SetWidth(CalcLength(400.0f));
        ViewAbstract::SetHeight(CalcLength(200.f));
        model.SetColumnsTemplate("1fr 1fr 1fr");
    });
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(info_->lanes_[0].items_.size(), 2);
    EXPECT_EQ(info_->lanes_[0].items_.back().idx, 3);
    EXPECT_EQ(info_->lanes_[0].items_.back().mainSize, 200.0f);
    EXPECT_EQ(info_->lanes_[0].endPos, 300.0f);
    EXPECT_EQ(info_->lanes_[1].items_.back().idx, 1);
    EXPECT_EQ(info_->lanes_[1].endPos, 200.0f);
    EXPECT_EQ(info_->lanes_[2].endPos, 200.0f);
    EXPECT_EQ(info_->lanes_[2].items_.back().idx, 4);
    EXPECT_EQ(info_->startIndex_, 0);
    EXPECT_EQ(info_->endIndex_, 4);
}

/**
 * @tc.name: Jump001
 * @tc.desc: waterFlow jump
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowSWTest, Jump001, TestSize.Level1)
{
    CreateWithItem([](WaterFlowModelNG model) {
        ViewAbstract::SetWidth(CalcLength(400.0f));
        ViewAbstract::SetHeight(CalcLength(200.f));
        model.SetColumnsTemplate("1fr 1fr 1fr");
    });
    pattern_->ScrollToIndex(8);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(info_->startIndex_, 5);
    EXPECT_EQ(info_->endIndex_, 9);
    for (auto& lane : info_->lanes_) {
        std::cout << "Lane = " << lane.ToString() << std::endl;
    }
    EXPECT_EQ(info_->idxToLane_.at(8), 2);
    EXPECT_EQ(info_->lanes_[0].endPos, 200.0f);
    EXPECT_EQ(info_->lanes_[1].startPos, -100.0f);
    EXPECT_EQ(info_->lanes_[1].endPos, 300.0f);
    EXPECT_EQ(info_->lanes_[2].endPos, 100.0f);
    EXPECT_EQ(info_->lanes_[0].items_.size(), 1);
    EXPECT_EQ(info_->lanes_[0].items_.front().idx, 7);
    EXPECT_EQ(info_->lanes_[1].items_.size(), 2);
    EXPECT_EQ(info_->lanes_[1].items_.front().idx, 5);
    EXPECT_EQ(info_->lanes_[1].items_.back().idx, 9);
    EXPECT_EQ(info_->lanes_[2].items_.size(), 2);
    EXPECT_TRUE(info_->itemEnd_);
    EXPECT_FALSE(info_->offsetEnd_);
    EXPECT_EQ(info_->startIndex_, 5);
    EXPECT_EQ(info_->endIndex_, 9);
}
} // namespace OHOS::Ace::NG
