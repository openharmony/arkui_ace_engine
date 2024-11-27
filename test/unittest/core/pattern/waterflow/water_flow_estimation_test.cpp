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

#include "gtest/gtest.h"
#include "water_flow_test_ng.h"

namespace OHOS::Ace::NG {
/**
 * @tc.name: Offset001
 * @tc.desc: waterFlow offset estimation
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, Offset001, TestSize.Level1)
{
    WaterFlowModelNG model = CreateWaterFlow();
    model.SetColumnsTemplate("1fr 1fr 1fr");
    CreateWaterFlowItems(100);
    CreateDone();

    auto info = pattern_->layoutInfo_;
    EXPECT_EQ(info->Offset(), 0.0f);

    pattern_->ScrollToIndex(80);
    FlushLayoutTask(frameNode_);
    EXPECT_NEAR(info->Offset(), -4050.0f, 100.0f);
    EXPECT_NEAR(info->EstimateTotalHeight(), 5200.0f, 100.0f);

    pattern_->ScrollToIndex(10);
    FlushLayoutTask(frameNode_);
    EXPECT_NEAR(info->Offset(), -637.0f, 1.0f);
    EXPECT_NEAR(info->EstimateTotalHeight(), 5200.0f, 100.0f);

    pattern_->ScrollToIndex(0);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(GetChildY(frameNode_, 0), 0.0f);
    EXPECT_EQ(info->startIndex_, 0);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(info->Offset(), 0.0f);
    EXPECT_NEAR(info->EstimateTotalHeight(), 5200.0f, 100.0f);

    pattern_->SetEdgeEffect(EdgeEffect::SPRING);
    pattern_->scrollableEvent_->GetScrollable()->HandleTouchDown();

    UpdateCurrentOffset(300.0f);
    EXPECT_NEAR(info->Offset(), 150.0f, 1.0f);
    EXPECT_NEAR(info->EstimateTotalHeight(), 5100.0f, 100.0f);

    pattern_->ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, false);
    FlushLayoutTask(frameNode_);
    EXPECT_NEAR(info->Offset(), -4400.0f, 100.0f);
    EXPECT_NEAR(info->EstimateTotalHeight(), 5150.0f, 100.0f);

    UpdateCurrentOffset(-300.0f);
    EXPECT_NEAR(info->Offset(), -4500.0f, 100.0f);
    EXPECT_NEAR(info->EstimateTotalHeight(), 5150.0f, 100.0f);
}

/**
 * @tc.name: Offset002
 * @tc.desc: waterFlow offset estimation
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, Offset002, TestSize.Level1)
{
    WaterFlowModelNG model = CreateWaterFlow();
    model.SetColumnsTemplate("1fr 1fr 1fr");
    CreateWaterFlowItems(3);
    model.SetFooter(GetDefaultHeaderBuilder());
    model.SetEdgeEffect(EdgeEffect::SPRING, true);
    CreateDone();
    auto info = pattern_->layoutInfo_;
    pattern_->scrollableEvent_->GetScrollable()->HandleTouchDown();

    pattern_->ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, false);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(info->Offset(), 0.0f);
    EXPECT_EQ(info->EstimateTotalHeight(), 300.0F);
    EXPECT_EQ(GetChildHeight(frameNode_, 0), 100.0f);

    UpdateCurrentOffset(-300.0f);
    EXPECT_NEAR(info->Offset(), -50.0f, 10.0f);
    EXPECT_EQ(info->EstimateTotalHeight(), 300.0f);

    UpdateCurrentOffset(600.0f);
    EXPECT_FLOAT_EQ(info->Offset(), GetChildY(frameNode_, 1));
    EXPECT_NEAR(info->EstimateTotalHeight(), 300.0f, 0.1);
}
} // namespace OHOS::Ace::NG