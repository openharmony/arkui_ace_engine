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
#include "list_test_ng.h"
#include "test/mock/core/pattern/mock_koala_lazy_for_each.h"
namespace OHOS::Ace::NG {
class ListArkoalaTest : public ListTestNg {
public:
    void IncrementAndLayout(int32_t lineNumber = -1)
    {
        lazy_.Increment(lineNumber);
        frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
        FlushUITasks(frameNode_);
    }

    void InitMockLazy(int32_t itemCnt)
    {
        lazy_ = MockKoalaLazyForEach(frameNode_.GetRawPtr(), itemCnt, [](int32_t idx) {
            auto node = ListItemModelNG::CreateFrameNode(-1);
            node->GetLayoutProperty()->UpdateUserDefinedIdealSize(
                CalcSize(CalcLength(Dimension(1, DimensionUnit::PERCENT)), CalcLength(90.0f)));
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
HWTEST_F(ListArkoalaTest, Basic001, TestSize.Level1)
{
    ListModelNG model = CreateList();
    InitMockLazy(100);
    CreateDone();

    IncrementAndLayout(__LINE__);
    EXPECT_EQ(lazy_.GetRange(), std::pair(0, 4));
    EXPECT_EQ(GetChildRect(frameNode_, 3).ToString(), "RectT (0.00, 270.00) - [240.00 x 90.00]");

    UpdateCurrentOffset(-200.0f);
    IncrementAndLayout(__LINE__);
    EXPECT_EQ(lazy_.GetRange(), std::pair(2, 6));
    EXPECT_EQ(pattern_->GetEndIndex(), 6);
    EXPECT_EQ(GetChildRect(frameNode_, 3).ToString(), "RectT (0.00, 70.00) - [240.00 x 90.00]");

    UpdateCurrentOffset(-350.0f);
    IncrementAndLayout(__LINE__);
    EXPECT_EQ(lazy_.GetRange(), std::pair(6, 10));
    EXPECT_EQ(GetChildRect(frameNode_, 7).ToString(), "RectT (0.00, 80.00) - [240.00 x 90.00]");

    layoutProperty_->UpdateUserDefinedIdealSize(CalcSize(CalcLength(480.0f), CalcLength(1200.0f)));
    FlushUITasks(frameNode_);
    IncrementAndLayout(__LINE__);
    EXPECT_EQ(lazy_.GetRange(), std::pair(6, 19));
    EXPECT_EQ(pattern_->GetEndIndex(), 19);
    EXPECT_EQ(GetChildRect(frameNode_, 10).ToString(), "RectT (0.00, 350.00) - [480.00 x 90.00]");

    UpdateCurrentOffset(300.0f);
    IncrementAndLayout(__LINE__);
    EXPECT_EQ(lazy_.GetRange(), std::pair(2, 16));
    EXPECT_EQ(GetChildRect(frameNode_, 10).ToString(), "RectT (0.00, 650.00) - [480.00 x 90.00]");

    UpdateCurrentOffset(-51.0f);
    EXPECT_FALSE(lazy_.NeedRecompose());
    EXPECT_EQ(GetChildRect(frameNode_, 3).ToString(), "RectT (0.00, -31.00) - [480.00 x 90.00]");

    UpdateCurrentOffset(2.0f);
    EXPECT_FALSE(lazy_.NeedRecompose());
    EXPECT_EQ(GetChildRect(frameNode_, 3).ToString(), "RectT (0.00, -29.00) - [480.00 x 90.00]");
    UpdateCurrentOffset(-2.0f);
    EXPECT_FALSE(lazy_.NeedRecompose());
    EXPECT_EQ(GetChildRect(frameNode_, 3).ToString(), "RectT (0.00, -31.00) - [480.00 x 90.00]");
}

/**
 * @tc.name: Jump001
 * @tc.desc: Test jump on ScrollWindowAdapter with MockKoala
 * @tc.type: FUNC
 */
HWTEST_F(ListArkoalaTest, Jump001, TestSize.Level1)
{
    ListModelNG model = CreateList();
    ViewAbstract::SetHeight(CalcLength(1280));
    model.SetSpace(Dimension(10.0f));
    InitMockLazy(100);
    CreateDone();
    IncrementAndLayout(__LINE__);

    pattern_->ScrollToIndex(90);
    FlushUITasks(frameNode_);
    IncrementAndLayout(__LINE__);
    EXPECT_EQ(lazy_.GetRange(), std::pair(90, 99));
    EXPECT_EQ(pattern_->GetStartIndex(), 90);
    EXPECT_EQ(GetChildRect(frameNode_, 93).ToString(), "RectT (0.00, 590.00) - [240.00 x 90.00]");
    EXPECT_EQ(GetChildRect(frameNode_, 94).ToString(), "RectT (0.00, 690.00) - [240.00 x 90.00]");
}

/**
 * @tc.name: Reset001
 * @tc.desc: Test data reset
 * @tc.type: FUNC
 */
HWTEST_F(ListArkoalaTest, Reset001, TestSize.Level1)
{
    ListModelNG model = CreateList();
    ViewAbstract::SetHeight(CalcLength(1280));
    model.SetSpace(Dimension(10.0f));
    InitMockLazy(100);
    CreateDone();
    IncrementAndLayout(__LINE__);

    pattern_->ScrollToIndex(50);
    FlushUITasks(frameNode_);
    IncrementAndLayout(__LINE__);
    EXPECT_EQ(lazy_.GetRange(), std::pair(50, 64));
    EXPECT_EQ(pattern_->GetStartIndex(), 50);

    UpdateCurrentOffset(-30.0f);
    EXPECT_EQ(GetChildY(frameNode_, 52), 170.0f);
    pattern_->NotifyDataChange(52, -1);
    UpdateCurrentOffset(-100.0f);
    IncrementAndLayout(__LINE__);
    EXPECT_EQ(GetChildY(frameNode_, 52), 70.0f);
}

/**
 * @tc.name: TargetAnimation001
 * @tc.desc: Test FillToTarget on ScrollWindowAdapter with MockKoala
 * @tc.type: FUNC
 */
HWTEST_F(ListArkoalaTest, TargetAnimation001, TestSize.Level1)
{
    ListModelNG model = CreateList();
    model.SetSpace(Dimension(10.0f));
    InitMockLazy(100);
    CreateDone();
    IncrementAndLayout(__LINE__);

    pattern_->ScrollToIndex(10, true, ScrollAlign::END);
    FlushUITasks(frameNode_);
    IncrementAndLayout(__LINE__);
    EXPECT_EQ(lazy_.GetRange(), std::pair(0, 10));
    FlushUITasks(frameNode_);
    EXPECT_FLOAT_EQ(pattern_->GetFinalPosition(), 690.f);
    UpdateCurrentOffset(-400.0f);
    IncrementAndLayout(__LINE__);
    EXPECT_EQ(pattern_->GetStartIndex(), 4);
    EXPECT_EQ(lazy_.GetRange(), std::pair(4, 8));
    UpdateCurrentOffset(-290.0f);
    IncrementAndLayout(__LINE__);
    EXPECT_EQ(lazy_.GetRange(), std::pair(7, 12));
    EXPECT_EQ(pattern_->GetStartIndex(), 7);
    EXPECT_EQ(GetChildY(frameNode_, 9), 210.0f);
}
} // namespace OHOS::Ace::NG
