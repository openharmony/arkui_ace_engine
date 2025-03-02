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
#include "grid_test_ng.h"
#include "test/mock/core/pattern/mock_koala_lazy_for_each.h"

namespace OHOS::Ace::NG {
class GridArkoalaTest : public GridTestNg {
private:
    void IncrementAndLayout(int32_t lineNumber = -1)
    {
        lazy_.Increment(lineNumber);
        frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
        FlushLayoutTask(frameNode_);
    }
    void InitMockLazy(int32_t itemCnt)
    {
        lazy_ = MockKoalaLazyForEach(frameNode_.GetRawPtr(), itemCnt, [](int32_t idx) {
            auto node = GridItemModelNG::CreateGridItem(-1);
            node->GetLayoutProperty()->UpdateUserDefinedIdealSize(CalcSize(std::nullopt, CalcLength(450.0f)));
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
HWTEST_F(GridArkoalaTest, Basic001, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    InitMockLazy(100);
    CreateDone(frameNode_);

    IncrementAndLayout(__LINE__);
    EXPECT_EQ(lazy_.GetRange(), std::pair(0, 4));

    EXPECT_EQ(GetChildRect(frameNode_, 0).ToString(), "RectT (0.00, 0.00) - [240.00 x 450.00]");
    EXPECT_EQ(GetChildRect(frameNode_, 1).ToString(), "RectT (240.00, 0.00) - [240.00 x 450.00]");

    UpdateCurrentOffset(-200.0f);
    IncrementAndLayout(__LINE__);
    EXPECT_EQ(lazy_.GetRange(), std::pair(0, 6));
    EXPECT_EQ(GetChildRect(frameNode_, 4).ToString(), "RectT (0.00, 700.00) - [240.00 x 450.00]");
    EXPECT_EQ(GetChildRect(frameNode_, 5).ToString(), "RectT (240.00, 700.00) - [240.00 x 450.00]");

    UpdateCurrentOffset(-500.0f);
    IncrementAndLayout(__LINE__);
    EXPECT_EQ(lazy_.GetRange(), std::pair(0, 8));
    EXPECT_EQ(GetChildRect(frameNode_, 2).ToString(), "RectT (0.00, -250.00) - [240.00 x 450.00]");
    EXPECT_EQ(GetChildRect(frameNode_, 3).ToString(), "RectT (240.00, -250.00) - [240.00 x 450.00]");

    layoutProperty_->UpdateUserDefinedIdealSize(CalcSize(CalcLength(480.0f), CalcLength(1200.0f)));
    FlushLayoutTask(frameNode_);
    IncrementAndLayout(__LINE__);
    EXPECT_EQ(lazy_.GetRange(), std::pair(2, 10));
    EXPECT_EQ(GetChildRect(frameNode_, 9).ToString(), "RectT (240.00, 1100.00) - [240.00 x 450.00]");

    UpdateCurrentOffset(300.0f);
    IncrementAndLayout(__LINE__);
    EXPECT_EQ(lazy_.GetRange(), std::pair(0, 8));
    EXPECT_TRUE(GetChildFrameNode(frameNode_, 1));

    UpdateCurrentOffset(-51.0f);
    EXPECT_FALSE(lazy_.NeedRecompose());
    EXPECT_EQ(pattern_->info_.startMainLineIndex_, 1);
    EXPECT_EQ(pattern_->info_.currentOffset_, -1.0f);

    UpdateCurrentOffset(2.0f);
    IncrementAndLayout(__LINE__);
    EXPECT_EQ(lazy_.GetRange(), std::pair(0, 8)); // to be optimized
    EXPECT_TRUE(GetChildFrameNode(frameNode_, 1));
    EXPECT_EQ(GetChildRect(frameNode_, 1).ToString(), "RectT (240.00, -449.00) - [240.00 x 450.00]");

    UpdateCurrentOffset(-2.0f);
    EXPECT_FALSE(lazy_.NeedRecompose());
}

/**
 * @tc.name: Basic002
 * @tc.desc: Test ScrollWindowAdapter with MockKoala
 * @tc.type: FUNC
 */
HWTEST_F(GridArkoalaTest, Basic002, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    ViewAbstract::SetHeight(CalcLength(1280));
    model.SetColumnsTemplate("1fr 1fr");
    model.SetRowsGap(Dimension(8.0f));
    InitMockLazy(100);
    CreateDone(frameNode_);

    IncrementAndLayout(__LINE__);
    EXPECT_EQ(lazy_.GetRange(), std::pair(0, 6));

    UpdateCurrentOffset(-450.0f);
    IncrementAndLayout(__LINE__);
    EXPECT_EQ(lazy_.GetRange(), std::pair(0, 8));
    EXPECT_EQ(pattern_->info_.startMainLineIndex_, 0);
    EXPECT_EQ(pattern_->info_.currentOffset_, -450.0f);
    EXPECT_FALSE(GetChildFrameNode(frameNode_, 9));
    EXPECT_FALSE(lazy_.NeedRecompose());

    UpdateCurrentOffset(-2.0f);
    EXPECT_EQ(pattern_->info_.startMainLineIndex_, 0);
    EXPECT_EQ(pattern_->info_.currentOffset_, -452.0f);
    EXPECT_FALSE(lazy_.NeedRecompose());

    UpdateCurrentOffset(-18.0f);
    EXPECT_FALSE(lazy_.NeedRecompose());
    EXPECT_EQ(pattern_->info_.startMainLineIndex_, 1);
    EXPECT_EQ(pattern_->info_.currentOffset_, -12.0f);

    UpdateCurrentOffset(15.0f);
    EXPECT_EQ(pattern_->info_.startMainLineIndex_, 1);
    EXPECT_EQ(pattern_->info_.currentOffset_, 3.0f);
    IncrementAndLayout(__LINE__);
    EXPECT_EQ(lazy_.GetRange(), std::pair(0, 8)); // to optimize
    EXPECT_EQ(pattern_->info_.startMainLineIndex_, 0);
    EXPECT_EQ(pattern_->info_.currentOffset_, -455.0f);

    UpdateCurrentOffset(15.0f);
    IncrementAndLayout(__LINE__);
    EXPECT_EQ(lazy_.GetRange(), std::pair(0, 8));
    EXPECT_EQ(pattern_->info_.startMainLineIndex_, 0);
    EXPECT_EQ(pattern_->info_.currentOffset_, -440.0f);
}

/**
 * @tc.name: LargeOffset001
 * @tc.desc: Test large offset on ScrollWindowAdapter with MockKoala
 * @tc.type: FUNC
 */
HWTEST_F(GridArkoalaTest, LargeOffset001, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    ViewAbstract::SetHeight(CalcLength(1280));
    model.SetColumnsTemplate("1fr 1fr");
    model.SetRowsGap(Dimension(8.0f));
    InitMockLazy(100);
    CreateDone(frameNode_);

    IncrementAndLayout(__LINE__);

    UpdateCurrentOffset(-5000.0f);
    IncrementAndLayout(__LINE__);
    EXPECT_EQ(lazy_.GetRange(), std::pair(20, 26));
    EXPECT_EQ(GetChildRect(frameNode_, 21).ToString(), "RectT (240.00, 8.00) - [240.00 x 450.00]");

    UpdateCurrentOffset(-8000.0f);
    IncrementAndLayout(__LINE__);
    EXPECT_EQ(lazy_.GetRange(), std::pair(54, 60));
    EXPECT_EQ(GetChildRect(frameNode_, 60).ToString(), "RectT (120.00, 1382.00) - [0.00 x 450.00]");

    UpdateCurrentOffset(4000.0f);
    IncrementAndLayout(__LINE__);
    EXPECT_EQ(lazy_.GetRange(), std::pair(36, 42));
    EXPECT_EQ(GetChildRect(frameNode_, 38).ToString(), "RectT (0.00, 466.00) - [240.00 x 450.00]");
    EXPECT_EQ(pattern_->info_.startIndex_, 36);
}

/**
 * @tc.name: Jump001
 * @tc.desc: Test jump on ScrollWindowAdapter with MockKoala
 * @tc.type: FUNC
 */
HWTEST_F(GridArkoalaTest, Jump001, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    ViewAbstract::SetHeight(CalcLength(1280));
    model.SetColumnsTemplate("1fr 1fr");
    model.SetRowsGap(Dimension(8.0f));
    InitMockLazy(100);
    CreateDone(frameNode_);
    IncrementAndLayout(__LINE__);

    pattern_->ScrollToIndex(90, false, ScrollAlign::START);
    FlushLayoutTask(frameNode_);
    IncrementAndLayout(__LINE__);
    EXPECT_EQ(lazy_.GetRange(), std::pair(90, 96));
    EXPECT_EQ(pattern_->info_.jumpIndex_, -2);
    EXPECT_EQ(pattern_->info_.startIndex_, 90);
    EXPECT_EQ(pattern_->info_.startMainLineIndex_, 45);
    EXPECT_EQ(GetChildRect(frameNode_, 90).ToString(), "RectT (0.00, 8.00) - [240.00 x 450.00]");
    EXPECT_EQ(GetChildRect(frameNode_, 93).ToString(), "RectT (240.00, 466.00) - [240.00 x 450.00]");
}

/**
 * @tc.name: TargetAnimation001
 * @tc.desc: Test FillToTarget on ScrollWindowAdapter with MockKoala
 * @tc.type: FUNC
 */
HWTEST_F(GridArkoalaTest, TargetAnimation001, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    ViewAbstract::SetHeight(CalcLength(1280));
    model.SetColumnsTemplate("1fr 1fr");
    model.SetRowsGap(Dimension(8.0f));
    InitMockLazy(100);
    CreateDone(frameNode_);
    IncrementAndLayout(__LINE__);

    pattern_->ScrollToIndex(10, true, ScrollAlign::END);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->info_.endIndex_, 5);
    IncrementAndLayout(__LINE__);
    EXPECT_EQ(lazy_.GetRange(), std::pair(0, 10));
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->info_.endIndex_, 5);
    EXPECT_FLOAT_EQ(pattern_->GetFinalPosition(), 1460.f);
    EXPECT_EQ(pattern_->info_.endIndex_, 5);
    UpdateCurrentOffset(-400.0f);
    IncrementAndLayout(__LINE__);
    EXPECT_EQ(pattern_->info_.startIndex_, 0);
    EXPECT_EQ(pattern_->info_.endIndex_, 7);
    UpdateCurrentOffset(-450.0f);
    IncrementAndLayout(__LINE__);
    EXPECT_EQ(pattern_->info_.startIndex_, 2);
    EXPECT_EQ(pattern_->info_.endIndex_, 9);
    EXPECT_EQ(GetChildY(frameNode_, 9), 982.0f);
}

/**
 * @tc.name: Reset001
 * @tc.desc: Test data reset
 * @tc.type: FUNC
 */
HWTEST_F(GridArkoalaTest, Reset001, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    ViewAbstract::SetHeight(CalcLength(1280));
    model.SetColumnsTemplate("1fr 1fr");
    model.SetRowsGap(Dimension(8.0f));
    InitMockLazy(100);
    CreateDone(frameNode_);
    IncrementAndLayout(__LINE__);

    pattern_->ScrollToIndex(50);
    FlushLayoutTask(frameNode_);
    IncrementAndLayout(__LINE__);
    EXPECT_EQ(lazy_.GetRange(), std::pair(50, 56));
    EXPECT_EQ(pattern_->info_.startIndex_, 50);

    frameNode_->NotifyChange(40, 0, -1, UINode::NotificationType::START_CHANGE_POSITION);
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    FlushLayoutTask(frameNode_);
    IncrementAndLayout(__LINE__);
    EXPECT_EQ(lazy_.GetRange(), std::pair(50, 56));
    EXPECT_EQ(pattern_->info_.startIndex_, 50);
    EXPECT_EQ(pattern_->info_.startMainLineIndex_, 25);

    frameNode_->NotifyChange(52, 0, -1, UINode::NotificationType::START_CHANGE_POSITION);
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    lazy_.NormalModeUpdate(50, nullptr);
    EXPECT_EQ(lazy_.GetRange(), std::pair(50, 56));
    FlushLayoutTask(frameNode_);
    IncrementAndLayout(__LINE__);
    EXPECT_EQ(pattern_->info_.startIndex_, 50);
    EXPECT_EQ(pattern_->info_.startMainLineIndex_, 25);
}
} // namespace OHOS::Ace::NG