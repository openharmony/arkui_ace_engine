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

/**
 * @tc.name: ChangeTemplate001
 * @tc.desc: waterFlow change lane count
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, ChangeTemplate001, TestSize.Level1)
{
    CreateWithItem([](WaterFlowModelNG model) {
        ViewAbstract::SetWidth(CalcLength(600.0f));
        ViewAbstract::SetHeight(CalcLength(200.f));
        model.SetColumnsTemplate("1fr 1fr 1fr");
    });
    UpdateCurrentOffset(-300.0f);
    auto info = pattern_->layoutInfo_;
    EXPECT_EQ(info->startIndex_, 5);
    EXPECT_EQ(info->endIndex_, 9);
    EXPECT_EQ(GetChildOffset(frameNode_, 5), OffsetF(200.0f, -100.0f));
    EXPECT_EQ(GetChildOffset(frameNode_, 6), OffsetF(400.0f, -100.0f));
    EXPECT_EQ(GetChildOffset(frameNode_, 7), OffsetF(0.0f, 0.0f));
    EXPECT_EQ(GetChildOffset(frameNode_, 8), OffsetF(400.0f, 0.0f));
    EXPECT_EQ(GetChildOffset(frameNode_, 9), OffsetF(200.0f, 100.0f));
    layoutProperty_->UpdateColumnsTemplate("1fr 1fr");
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(info->startIndex_, 5);
    EXPECT_EQ(info->endIndex_, 8);
    EXPECT_EQ(GetChildOffset(frameNode_, 5), OffsetF(0.0f, -100.0f));
    EXPECT_EQ(GetChildOffset(frameNode_, 6), OffsetF(300.0f, -100.0f));
    EXPECT_EQ(GetChildOffset(frameNode_, 7), OffsetF(300.0f, 0.0f));
    EXPECT_EQ(GetChildOffset(frameNode_, 8), OffsetF(0.0f, 100.0f));
}
} // namespace OHOS::Ace::NG
