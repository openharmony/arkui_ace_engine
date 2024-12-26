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
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "water_flow_item_maps.h"
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
    model.SetEdgeEffect(EdgeEffect::SPRING, true);
    CreateWaterFlowItems(100);
    CreateDone();

    auto info = pattern_->layoutInfo_;
    EXPECT_EQ(info->Offset(), 0.0f);

    ScrollToIndex(80, false, ScrollAlign::START);
    EXPECT_NEAR(info->Offset(), -4050.0f, 100.0f);
    EXPECT_NEAR(info->EstimateTotalHeight(), 5200.0f, 100.0f);

    ScrollToIndex(10, false, ScrollAlign::START);
    EXPECT_NEAR(info->Offset(), -637.0f, 1.0f);
    EXPECT_NEAR(info->EstimateTotalHeight(), 5200.0f, 100.0f);

    ScrollToIndex(0, false, ScrollAlign::START);
    EXPECT_EQ(GetChildY(frameNode_, 0), 0.0f);
    EXPECT_EQ(info->startIndex_, 0);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(info->Offset(), 0.0f);
    EXPECT_NEAR(info->EstimateTotalHeight(), 5200.0f, 100.0f);

    pattern_->scrollableEvent_->GetScrollable()->HandleTouchDown();

    UpdateCurrentOffset(300.0f);
    EXPECT_NEAR(info->Offset(), 150.0f, 1.0f);
    EXPECT_NEAR(info->EstimateTotalHeight(), 5100.0f, 100.0f);

    ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, false);
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

    ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, false);
    EXPECT_EQ(info->Offset(), 0.0f);
    EXPECT_EQ(info->EstimateTotalHeight(), 250.0F);
    EXPECT_EQ(GetChildHeight(frameNode_, 0), 50.0f);

    UpdateCurrentOffset(-300.0f);
    EXPECT_NEAR(info->Offset(), -50.0f, 10.0f);
    EXPECT_EQ(info->EstimateTotalHeight(), 250.0f);

    UpdateCurrentOffset(600.0f);
    EXPECT_FLOAT_EQ(info->Offset(), GetChildY(frameNode_, 1));
    EXPECT_NEAR(info->EstimateTotalHeight(), 250.0f, 0.1);
}

/**
 * @tc.name: LargeOffset001
 * @tc.desc: move WaterFlow by large offset
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, LargeOffset001, TestSize.Level1)
{
    CreateWaterFlow();
    ViewAbstract::SetWidth(CalcLength(400.0f));
    ViewAbstract::SetHeight(CalcLength(600.f));
    CreateWaterFlowItems(37);
    auto secObj = pattern_->GetOrCreateWaterFlowSections();
    secObj->ChangeData(0, 0, SECTION_7);
    CreateDone();

    auto info = pattern_->layoutInfo_;
    UpdateCurrentOffset(-2000.0f);
    EXPECT_EQ(info->startIndex_, 18);
    EXPECT_EQ(info->endIndex_, 23);

    UpdateCurrentOffset(1000.0f); // no jump
    EXPECT_EQ(info->startIndex_, 8);
    EXPECT_EQ(info->endIndex_, 14);

    UpdateCurrentOffset(-3000.0f);
    EXPECT_EQ(info->startIndex_, 28);
    EXPECT_EQ(info->endIndex_, 33);

    UpdateCurrentOffset(-5000.0f);
    EXPECT_EQ(info->startIndex_, 31);
    EXPECT_EQ(info->endIndex_, 36);

    UpdateCurrentOffset(5000.0f);
    EXPECT_EQ(info->startIndex_, 0);
    EXPECT_EQ(info->endIndex_, 6);
}

/**
 * @tc.name: LargeOffset001
 * @tc.desc: move WaterFlow by large offset
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, LargeOffset002, TestSize.Level1)
{
    auto model = CreateWaterFlow();
    model.SetCachedCount(10);
    model.SetRowsGap(Dimension(10));
    model.SetColumnsGap(Dimension(10));
    CreateWaterFlowItems(100);
    CreateDone();

    auto info = pattern_->layoutInfo_;
    UpdateCurrentOffset(-2000.0f);
    EXPECT_EQ(info->startIndex_, 11);
    EXPECT_EQ(info->endIndex_, 15);

    UpdateCurrentOffset(-10000.0f);
    EXPECT_EQ(info->startIndex_, 57);
    EXPECT_EQ(info->endIndex_, 61);

    layoutProperty_->UpdateColumnsTemplate("1fr 1fr 1fr");
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(info->startIndex_, 57);
    EXPECT_EQ(info->endIndex_, 72);

    UpdateCurrentOffset(-Infinity<float>());
    EXPECT_EQ(info->startIndex_, 86);
    EXPECT_EQ(info->endIndex_, 99);

    UpdateCurrentOffset(10000.0f);
    EXPECT_EQ(info->startIndex_, 0);
    EXPECT_EQ(info->endIndex_, 16);

    UpdateCurrentOffset(-2000.0f);
    EXPECT_EQ(info->startIndex_, 36);
    EXPECT_EQ(info->endIndex_, 52);
}

/**
 * @tc.name: LargeOffset003
 * @tc.desc: move WaterFlow by large offset
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, LargeOffset003, TestSize.Level1)
{
    CreateWaterFlow();
    CreateWaterFlowItems(45);
    auto secObj = pattern_->GetOrCreateWaterFlowSections();
    secObj->ChangeData(0, 0, SECTION_10);
    CreateDone();

    auto info = pattern_->layoutInfo_;
    UpdateCurrentOffset(-2000.0f);
    EXPECT_EQ(info->startIndex_, 28);
    EXPECT_EQ(info->endIndex_, 44);

    UpdateCurrentOffset(1500.0f); // no jump
    EXPECT_EQ(info->startIndex_, 5);
    EXPECT_EQ(info->endIndex_, 15);

    UpdateCurrentOffset(-3000.0f);
    EXPECT_EQ(info->startIndex_, 29);
    EXPECT_EQ(info->endIndex_, 44);

    UpdateCurrentOffset(5000.0f);
    EXPECT_EQ(info->startIndex_, 0);
    EXPECT_EQ(info->endIndex_, 9);
}
} // namespace OHOS::Ace::NG