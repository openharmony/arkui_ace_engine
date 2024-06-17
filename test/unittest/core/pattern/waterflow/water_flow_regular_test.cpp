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

namespace OHOS::Ace::NG {
// TEST non-segmented layout

/**
 * @tc.name: OffsetEnd001
 * @tc.desc: Check OffsetEnd value with footer
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, OffsetEnd001, TestSize.Level1)
{
    Create([](WaterFlowModelNG model) {
        model.SetColumnsTemplate("1fr 1fr");
        model.SetFooter(GetDefaultHeaderBuilder());
        model.SetRowsGap(Dimension(5.0f));
        CreateItem(30);
    });
    pattern_->ScrollToIndex(29, false, ScrollAlign::END);
    auto info = pattern_->layoutInfo_;
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(info->endIndex_, 29);
    EXPECT_EQ(GetChildY(frameNode_, 30), 600.0f);
    EXPECT_FALSE(info->offsetEnd_);

    UpdateCurrentOffset(-45.0f);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(info->endIndex_, 29);
    EXPECT_FALSE(info->offsetEnd_);

    UpdateCurrentOffset(-5.0f);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(info->endIndex_, 29);
    EXPECT_TRUE(info->offsetEnd_);
    EXPECT_TRUE(info->ReachEnd(50.0f));

    UpdateCurrentOffset(1.0f);
    FlushLayoutTask(frameNode_);
    EXPECT_FALSE(info->offsetEnd_);
}

/**
 * @tc.name: ScrollToEdge001
 * @tc.desc: Test ScrollToEdge func
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, ScrollToEdge001, TestSize.Level1)
{
    Create([](WaterFlowModelNG model) {
        model.SetFooter(GetDefaultHeaderBuilder());
        model.SetColumnsTemplate("1fr 1fr");
        CreateItem(100);
    });
    pattern_->ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, false);
    FlushLayoutTask(frameNode_);
    auto info = pattern_->layoutInfo_;
    EXPECT_EQ(info->endIndex_, 99);
    EXPECT_EQ(GetChildY(frameNode_, 100), 550.0f);
    EXPECT_EQ(GetChildOffset(frameNode_, info->footerIndex_), OffsetF(0.0f, 750.0f));
    // scrolled to footer
}

/**
 * @tc.name: Constraint001
 * @tc.desc: Test Layout when the layoutConstraint changes.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, Constraint001, TestSize.Level1)
{
    Create([](WaterFlowModelNG model) {
        ViewAbstract::SetWidth(CalcLength(400.0f));
        ViewAbstract::SetHeight(CalcLength(600.f));
        model.SetColumnsTemplate("1fr 1fr");
        CreateItem(60);
    });

    auto& info = pattern_->layoutInfo_;
    EXPECT_EQ(info->startIndex_, 0);
    EXPECT_EQ(info->endIndex_, 8);
    EXPECT_EQ(GetChildWidth(frameNode_, 0), 200.0f);

    layoutProperty_->UpdateUserDefinedIdealSize(CalcSize(CalcLength(500.0f), CalcLength(Dimension(600.0f))));
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(GetChildWidth(frameNode_, 4), 250.0f);

    layoutProperty_->UpdateUserDefinedIdealSize(CalcSize(CalcLength(200.0f), CalcLength(Dimension(700.0f))));
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(GetChildWidth(frameNode_, 4), 100.0f);
    EXPECT_EQ(info->endIndex_, 9);

    UpdateCurrentOffset(-220.0f);
    EXPECT_EQ(info->storedOffset_, -20.0f);
    EXPECT_EQ(info->startIndex_, 3);
    layoutProperty_->UpdateUserDefinedIdealSize(CalcSize(CalcLength(600.0f), CalcLength(Dimension(700.0f))));
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(GetChildWidth(frameNode_, 4), 300.0f);
    EXPECT_EQ(info->storedOffset_, -20.0f);
    EXPECT_EQ(info->startIndex_, 3);
}
} // namespace OHOS::Ace::NG
