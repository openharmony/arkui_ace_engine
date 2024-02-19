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
#include "test/unittest/core/pattern/waterflow/water_flow_item_maps.h"
#include "test/unittest/core/pattern/waterflow/water_flow_test_ng.h"

#include "core/components_ng/property/measure_property.h"

#define protected public
#define private public
#include "frameworks/core/components_ng/pattern/waterflow/water_flow_segmented_layout.h"
#undef private
#undef protected

namespace OHOS::Ace::NG {
class WaterFlowSegmentTest : public WaterFlowTestNg {};

/**
 * @tc.name: Fill001
 * @tc.desc: Test SegmentedLayout::Fill.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowSegmentTest, Fill001, TestSize.Level1)
{
    Create([](WaterFlowModelNG model) {
        model.SetColumnsTemplate("1fr 1fr");
        CreateItemWithHeight(50.0f);
        CreateItemWithHeight(30.0f);
        CreateItemWithHeight(40.0f);
        CreateItemWithHeight(60.0f);
        CreateItemWithHeight(20.0f);
        CreateItemWithHeight(50.0f);
        CreateItemWithHeight(30.0f);
        CreateItemWithHeight(40.0f);
        CreateItemWithHeight(2.0f);
        CreateItemWithHeight(20.0f);
    }, false);

    auto algo = AceType::MakeRefPtr<WaterFlowSegmentedLayout>(WaterFlowLayoutInfo {});
    algo->wrapper_ = AceType::RawPtr(frameNode_);
    algo->mainSize_ = 2000.0f;
    algo->itemsCrossSize_ = { { 50.0f, 50.0f, 50.0f, 50.0f }, {}, { 70.0f, 70.0f, 70.0f } };
    algo->mainGaps_ = { 5.0f, 0.0f, 1.0f };
    algo->margins_ = { {}, {}, PaddingPropertyF { .top = 5.0f } };

    auto& info = algo->info_;

    info.items_.resize(3);
    for (int i = 0; i < 3; ++i) {
        info.items_[0][i] = {};
        info.items_[2][i] = {};
    }
    info.items_[0][3] = {};

    info.segmentTails_ = SEGMENT_TAILS_1;

    algo->Fill();
    EXPECT_EQ(info.items_, ITEM_MAP_1);
}

/**
 * @tc.name: MeasureOnOffset001
 * @tc.desc: Test SegmentedLayout::MeasureOnOffset.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowSegmentTest, MeasureOnOffset001, TestSize.Level1)
{
    Create([](WaterFlowModelNG model) {
        model.SetColumnsTemplate("1fr 1fr 1fr 1fr");
        model.SetColumnsGap(Dimension(5.0f));
        model.SetRowsGap(Dimension(1.0f));
        auto footer = GetDefaultHeaderBuilder();
        model.SetFooter(std::move(footer));
        CreateItem(10);
        ViewStackProcessor::GetInstance()->Pop();
    }, false);

    LayoutConstraintF constraint { .maxSize = { 480.0f, 800.0f }, .percentReference = { 480.0f, 800.0f } };
    layoutProperty_->layoutConstraint_ = constraint;
    layoutProperty_->contentConstraint_ = constraint;

    auto algo = AceType::MakeRefPtr<WaterFlowSegmentedLayout>(WaterFlowLayoutInfo {});
    auto& info = algo->info_;

    info.footerIndex_ = 0;

    for (int i = 0; i < 2; ++i) {
        algo->Measure(AceType::RawPtr(frameNode_));

        EXPECT_EQ(info.childrenCount_, 11);
        EXPECT_EQ(info.items_, ITEM_MAP_2);
        EXPECT_EQ(info.itemInfos_, ITEM_INFO_2);
        EXPECT_EQ(info.segmentTails_, SEGMENT_TAILS_2);
        EXPECT_EQ(info.endPosArray_, END_POS_ARRAY_2);
        EXPECT_EQ(info.segmentStartPos_, SEGMENT_START_POS_2);
    }

    info.prevOffset_ = 0.0f;
    info.currentOffset_ = -100.0f;
    algo->Measure(AceType::RawPtr(frameNode_));
    EXPECT_EQ(info.currentOffset_, 0.0f);
    EXPECT_EQ(info.startIndex_, 0);
    EXPECT_EQ(info.endIndex_, 10);

    algo->overScroll_ = true;
    info.prevOffset_ = 0.0f;
    info.currentOffset_ = -200.0f;
    algo->Measure(AceType::RawPtr(frameNode_));
    EXPECT_EQ(info.currentOffset_, -200.0f);
    EXPECT_EQ(info.startIndex_, 4);
    EXPECT_EQ(info.endIndex_, 10);
}

/**
 * @tc.name: Layout001
 * @tc.desc: Test SegmentedLayout::Layout.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowSegmentTest, Layout001, TestSize.Level1)
{
    Create([](WaterFlowModelNG model) {
        model.SetColumnsTemplate("1fr 1fr 1fr 1fr");
        model.SetColumnsGap(Dimension(5.0f));
        model.SetRowsGap(Dimension(1.0f));
        auto footer = GetDefaultHeaderBuilder();
        model.SetFooter(std::move(footer));
        CreateItem(10);
        ViewStackProcessor::GetInstance()->Pop();
    }, false);

    LayoutConstraintF constraint { .maxSize = { 480.0f, 800.0f }, .percentReference = { 480.0f, 800.0f } };
    layoutProperty_->layoutConstraint_ = constraint;
    layoutProperty_->contentConstraint_ = constraint;

    auto algo = AceType::MakeRefPtr<WaterFlowSegmentedLayout>(WaterFlowLayoutInfo {});
    auto& info = algo->info_;

    info.footerIndex_ = 0;

    algo->Measure(AceType::RawPtr(frameNode_));
    const std::vector<std::vector<float>> crossPos = { { 0.0f, 121.25f, 242.5f, 363.75f }, { 0.0f } };
    EXPECT_EQ(algo->itemsCrossPosition_, crossPos);
    algo->Layout(AceType::RawPtr(frameNode_));
    EXPECT_EQ(GetChildOffset(frameNode_, 0), OffsetF(0.0f, 0.0f));
    EXPECT_EQ(GetChildOffset(frameNode_, 1), OffsetF(121.25f, 0.0f));
    EXPECT_EQ(GetChildOffset(frameNode_, 2), OffsetF(242.5f, 0.0f));
    EXPECT_EQ(GetChildOffset(frameNode_, 3), OffsetF(363.75f, 0.0f));
    EXPECT_EQ(GetChildOffset(frameNode_, 4), OffsetF(0.0f, 101.0f));
    EXPECT_EQ(GetChildOffset(frameNode_, 5), OffsetF(242.5f, 101.0f));
    EXPECT_EQ(GetChildOffset(frameNode_, 6), OffsetF(121.25f, 201.0f));
    EXPECT_EQ(GetChildOffset(frameNode_, 7), OffsetF(363.75f, 201.0f));
    EXPECT_EQ(GetChildOffset(frameNode_, 8), OffsetF(0.0f, 202.0f));
    EXPECT_EQ(GetChildOffset(frameNode_, 9), OffsetF(121.25f, 302.0f));
    EXPECT_EQ(GetChildOffset(frameNode_, 10), OffsetF(0.0f, 502.0f));

    info.prevOffset_ = 0.0f;
    info.currentOffset_ = -100.0f;
    algo->overScroll_ = true;
    algo->Measure(AceType::RawPtr(frameNode_));
    algo->Layout(AceType::RawPtr(frameNode_));
    EXPECT_EQ(info.startIndex_, 1);
    EXPECT_EQ(info.endIndex_, 10);
    EXPECT_EQ(GetChildOffset(frameNode_, 1), OffsetF(121.25f, -100.0f));
    EXPECT_EQ(GetChildOffset(frameNode_, 2), OffsetF(242.5f, -100.0f));
    EXPECT_EQ(GetChildOffset(frameNode_, 3), OffsetF(363.75f, -100.0f));
    EXPECT_EQ(GetChildOffset(frameNode_, 4), OffsetF(0.0f, 1.0f));
    EXPECT_EQ(GetChildOffset(frameNode_, 5), OffsetF(242.5f, 1.0f));
    EXPECT_EQ(GetChildOffset(frameNode_, 6), OffsetF(121.25f, 101.0f));
    EXPECT_EQ(GetChildOffset(frameNode_, 7), OffsetF(363.75f, 101.0f));
    EXPECT_EQ(GetChildOffset(frameNode_, 8), OffsetF(0.0f, 102.0f));
    EXPECT_EQ(GetChildOffset(frameNode_, 9), OffsetF(121.25f, 202.0f));
    EXPECT_EQ(GetChildOffset(frameNode_, 10), OffsetF(0.0f, 402.0f));
}

/**
 * @tc.name: MeasureOnOffset002
 * @tc.desc: Test SegmentedLayout::MeasureOnOffset.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowSegmentTest, MeasureOnOffset002, TestSize.Level1)
{
    Create([](WaterFlowModelNG model) {
        model.SetColumnsTemplate("1fr 1fr 1fr 1fr 1fr");
        model.SetColumnsGap(Dimension(5.0f));
        model.SetRowsGap(Dimension(1.0f));
        auto footer = GetDefaultHeaderBuilder();
        model.SetFooter(std::move(footer));
        CreateItem(100);
        ViewStackProcessor::GetInstance()->Pop();
    }, false);

    LayoutConstraintF constraint { .maxSize = { 480.0f, 800.0f }, .percentReference = { 480.0f, 800.0f } };
    layoutProperty_->layoutConstraint_ = constraint;
    layoutProperty_->contentConstraint_ = constraint;

    auto algo = AceType::MakeRefPtr<WaterFlowSegmentedLayout>(WaterFlowLayoutInfo {});
    auto& info = algo->info_;

    info.footerIndex_ = 0;

    for (int i = 0; i < 2; ++i) {
        algo->Measure(AceType::RawPtr(frameNode_));

        EXPECT_EQ(info.childrenCount_, 101);
        EXPECT_EQ(info.items_.size(), 2);
        EXPECT_EQ(info.startIndex_, 0);
        EXPECT_EQ(info.endIndex_, 27);
        EXPECT_EQ(info.segmentTails_, SEGMENT_TAILS_3);
    }

    info.prevOffset_ = 0.0f;
    info.currentOffset_ = -100.0f;
    algo->Measure(AceType::RawPtr(frameNode_));
    EXPECT_EQ(info.currentOffset_, -100.0f);
    EXPECT_EQ(info.startIndex_, 1);
    EXPECT_EQ(info.endIndex_, 30);

    info.prevOffset_ = -100.0f;
    info.currentOffset_ = -500.0f;
    algo->Measure(AceType::RawPtr(frameNode_));
    EXPECT_EQ(info.currentOffset_, -500.0f);
    EXPECT_EQ(info.startIndex_, 11);
    EXPECT_EQ(info.endIndex_, 44);

    const auto itemMap = info.items_;
    const auto itemInfo = info.itemInfos_;
    const auto endPosArr = info.endPosArray_;

    info.prevOffset_ = -500.0f;
    info.currentOffset_ = -300.0f;
    algo->Measure(AceType::RawPtr(frameNode_));
    EXPECT_EQ(info.items_, itemMap);
    EXPECT_EQ(info.itemInfos_, itemInfo);
    EXPECT_EQ(info.endPosArray_, endPosArr);
    EXPECT_EQ(info.startIndex_, 5);
    EXPECT_EQ(info.endIndex_, 37);
    EXPECT_EQ(info.segmentStartPos_, std::vector<float> { 0.0f });
}
} // namespace OHOS::Ace::NG