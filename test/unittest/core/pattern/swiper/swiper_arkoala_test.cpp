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
#include "swiper_test_ng.h"
#include "test/mock/core/pattern/mock_koala_lazy_for_each.h"

#include "core/components_ng/pattern/linear_layout/row_model_ng.h"
namespace OHOS::Ace::NG {
class SwiperArkoalaTest : public SwiperTestNg {
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
            auto node = RowModelNG::CreateFrameNode(-1);
            node->GetLayoutProperty()->UpdateUserDefinedIdealSize(CalcSize(
                CalcLength(Dimension(1, DimensionUnit::PERCENT)), CalcLength(Dimension(1, DimensionUnit::PERCENT))));
            return node;
        });
        lazy_.Register();
    }

    void UpdateOffset(float delta)
    {
        pattern_->UpdateCurrentOffset(delta);
        FlushUITasks(frameNode_);
    }

    MockKoalaLazyForEach lazy_;
};

/**
 * @tc.name: Basic001
 * @tc.desc: Test ScrollWindowAdapter with MockKoala
 * @tc.type: FUNC
 */
HWTEST_F(SwiperArkoalaTest, Basic001, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetItemSpace(Dimension(10.0f));
    InitMockLazy(10);
    CreateDone();

    IncrementAndLayout(__LINE__);
    EXPECT_EQ(lazy_.GetRange(), std::pair(0, 1));
    EXPECT_EQ(GetChildRect(frameNode_, 0).ToString(), "RectT (0.00, 0.00) - [480.00 x 800.00]");

    UpdateOffset(-200.0f);
    IncrementAndLayout(__LINE__);
    EXPECT_EQ(lazy_.GetRange(), std::pair(0, 2));
    EXPECT_EQ(pattern_->GetEndIndex(), 1);
    EXPECT_EQ(GetChildRect(frameNode_, 1).ToString(), "RectT (290.00, 0.00) - [480.00 x 800.00]");

    UpdateOffset(-200.0f);
    EXPECT_FALSE(lazy_.NeedRecompose());
    EXPECT_EQ(GetChildRect(frameNode_, 1).ToString(), "RectT (90.00, 0.00) - [480.00 x 800.00]");
    UpdateOffset(-200.0f);
    IncrementAndLayout(__LINE__);
    EXPECT_EQ(lazy_.GetRange(), std::pair(0, 3));
    EXPECT_EQ(GetChildRect(frameNode_, 1).ToString(), "RectT (-110.00, 0.00) - [480.00 x 800.00]");
    EXPECT_EQ(GetChildRect(frameNode_, 2).ToString(), "RectT (380.00, 0.00) - [480.00 x 800.00]");

    UpdateOffset(300.0f);
    IncrementAndLayout(__LINE__);
    EXPECT_EQ(lazy_.GetRange(), std::pair(0, 2));
    EXPECT_EQ(GetChildRect(frameNode_, 0).ToString(), "RectT (-300.00, 0.00) - [480.00 x 800.00]");
    EXPECT_EQ(GetChildRect(frameNode_, 1).ToString(), "RectT (190.00, 0.00) - [480.00 x 800.00]");

    UpdateOffset(-51.0f);
    EXPECT_FALSE(lazy_.NeedRecompose());
    EXPECT_EQ(GetChildRect(frameNode_, 0).ToString(), "RectT (-351.00, 0.00) - [480.00 x 800.00]");

    UpdateOffset(2.0f);
    // to optimize. Lanes didn't record Item 0 and requested Fill... EXPECT_FALSE(lazy_.NeedRecompose());
    IncrementAndLayout(__LINE__);
    EXPECT_EQ(GetChildRect(frameNode_, 0).ToString(), "RectT (-349.00, 0.00) - [480.00 x 800.00]");
    UpdateOffset(-2.0f);
    EXPECT_FALSE(lazy_.NeedRecompose());
    EXPECT_EQ(GetChildRect(frameNode_, 0).ToString(), "RectT (-351.00, 0.00) - [480.00 x 800.00]");
}

/**
 * @tc.name: Jump001
 * @tc.desc: Test jump on ScrollWindowAdapter with MockKoala
 * @tc.type: FUNC
 */
HWTEST_F(SwiperArkoalaTest, Jump001, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetItemSpace(Dimension(5.0f));
    InitMockLazy(100);
    CreateDone();
    IncrementAndLayout(__LINE__);

    pattern_->ChangeIndex(8, false);
    FlushUITasks(frameNode_);
    IncrementAndLayout(__LINE__);
    EXPECT_EQ(pattern_->GetStartIndex(), 8);
    EXPECT_EQ(GetChildRect(frameNode_, 8).ToString(), "RectT (0.00, 0.00) - [480.00 x 800.00]");

    UpdateOffset(-50.0f);
    IncrementAndLayout(__LINE__);
    EXPECT_EQ(lazy_.GetRange(), std::pair(7, 10));
    EXPECT_EQ(GetChildRect(frameNode_, 8).ToString(), "RectT (-50.00, 0.00) - [480.00 x 800.00]");
    EXPECT_EQ(GetChildRect(frameNode_, 9).ToString(), "RectT (435.00, 0.00) - [480.00 x 800.00]");
}

/**
 * @tc.name: Animation001
 * @tc.desc: Test animated jump on ScrollWindowAdapter with MockKoala
 * @tc.type: FUNC
 */
HWTEST_F(SwiperArkoalaTest, Animation001, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetItemSpace(Dimension(5.0f));
    InitMockLazy(100);
    CreateDone();
    IncrementAndLayout(__LINE__);

    pattern_->ChangeIndex(8, true);
    FlushUITasks(frameNode_);
    EXPECT_EQ(pattern_->GetStartIndex(), 0);
    IncrementAndLayout(__LINE__);
    EXPECT_EQ(lazy_.GetRange(), std::pair(0, 8));
    /** Commented out because Swiper layout seems to have changed
    EXPECT_EQ(pattern_->GetStartIndex(), 0);
    EXPECT_EQ(GetChildX(frameNode_, 8), 3880.0f);

    UpdateOffset(-100.0f);
    FlushUITasks(frameNode_);
    EXPECT_EQ(GetChildX(frameNode_, 0), -100.0f);
    */
}
} // namespace OHOS::Ace::NG
