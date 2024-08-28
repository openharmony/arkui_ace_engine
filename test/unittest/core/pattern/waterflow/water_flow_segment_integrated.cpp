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
#include "water_flow_item_maps.h"
#include "water_flow_test_ng.h"

#include "core/components_ng/pattern/waterflow/layout/top_down/water_flow_layout_info.h"
#include "core/components_ng/property/calc_length.h"
// mocks
#include "test/mock/core/pipeline/mock_pipeline_context.h"

namespace OHOS::Ace::NG {
class WaterFlowSegmentIntegratedTest : public WaterFlowTestNg {
public:
    static void SetUpTestSuite()
    {
        MockPipelineContext::SetUp();
    }
    static void TearDownTestSuite()
    {
        MockPipelineContext::TearDown();
    }
};

/**
 * @tc.name: Add001
 * @tc.desc: Layout WaterFlow and then add children
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowSegmentIntegratedTest, Add001, TestSize.Level1)
{
    CreateWaterFlow();
    ViewAbstract::SetWidth(CalcLength(400.0f));
    ViewAbstract::SetHeight(CalcLength(600.f));
    CreateWaterFlowItems(60);
    CreateDone();
    auto secObj = pattern_->GetOrCreateWaterFlowSections();
    secObj->ChangeData(0, 0, SECTION_5);
    MockPipelineContext::GetCurrent()->FlushBuildFinishCallbacks();
    FlushLayoutTask(frameNode_);

    auto info = AceType::DynamicCast<WaterFlowLayoutInfo>(pattern_->layoutInfo_);
    EXPECT_EQ(info->startIndex_, 0);
    EXPECT_EQ(info->endIndex_, 10);

    UpdateCurrentOffset(-2000.0f);
    EXPECT_EQ(info->currentOffset_, -2000.0f);
    EXPECT_EQ(info->startIndex_, 19);
    EXPECT_EQ(info->endIndex_, 23);
    EXPECT_EQ(info->segmentTails_.size(), 5);

    AddItems(10);
    secObj->ChangeData(5, 0, ADD_SECTION_6);
    frameNode_->ChildrenUpdatedFrom(60);
    MockPipelineContext::GetCurrent()->FlushBuildFinishCallbacks();
    EXPECT_EQ(secObj->GetSectionInfo().size(), 6);
    EXPECT_EQ(secObj->GetSectionInfo()[5].crossCount, 2);

    FlushLayoutTask(frameNode_);
    EXPECT_EQ(info->currentOffset_, -2000.0f);
    EXPECT_EQ(info->startIndex_, 19);
    EXPECT_EQ(info->endIndex_, 23);
    EXPECT_EQ(info->segmentTails_.size(), 6);
    EXPECT_EQ(info->childrenCount_, 70);

    UpdateCurrentOffset(-10000.0f);
    EXPECT_EQ(info->currentOffset_, -6883.0f);
    EXPECT_EQ(info->startIndex_, 63);
    EXPECT_EQ(info->endIndex_, 69);
    EXPECT_EQ(info->items_[5][1].size(), 4);
    EXPECT_EQ(info->itemInfos_[60].mainOffset, 6658.0f);
    EXPECT_EQ(info->itemInfos_[9].mainOffset, 306.0f);
    EXPECT_EQ(info->itemInfos_[10].mainOffset, 511.0f);
}

/**
 * @tc.name: Splice001
 * @tc.desc: Layout WaterFlow and then change section data in the middle.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowSegmentIntegratedTest, Splice001, TestSize.Level1)
{
    CreateWaterFlow();
    ViewAbstract::SetWidth(CalcLength(400.0f));
    ViewAbstract::SetHeight(CalcLength(600.f));
    CreateWaterFlowItems(37);
    auto secObj = pattern_->GetOrCreateWaterFlowSections();
    secObj->ChangeData(0, 0, SECTION_7);
    MockPipelineContext::GetCurrent()->FlushBuildFinishCallbacks();
    CreateDone();
    auto info = AceType::DynamicCast<WaterFlowLayoutInfo>(pattern_->layoutInfo_);

    UpdateCurrentOffset(-300.0f);

    EXPECT_EQ(info->segmentStartPos_[2], 613.0f);
    EXPECT_EQ(info->segmentStartPos_[3], 621.0f);
    EXPECT_EQ(info->startIndex_, 2);

    // replace second section
    secObj->ChangeData(1, 1, ADD_SECTION_6);
    AddItems(7);
    frameNode_->ChildrenUpdatedFrom(37);
    MockPipelineContext::GetCurrent()->FlushBuildFinishCallbacks();
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(secObj->GetSectionInfo().size(), 4);
    EXPECT_EQ(secObj->GetSectionInfo()[0].itemsCount, 4);
    EXPECT_EQ(secObj->GetSectionInfo()[1].itemsCount, 10);
    EXPECT_EQ(secObj->GetSectionInfo()[3].itemsCount, 30);
    EXPECT_TRUE(secObj->GetSectionInfo()[1].onGetItemMainSizeByIndex);

    EXPECT_EQ(info->currentOffset_, -300.0f);
    EXPECT_EQ(info->startIndex_, 2);
    EXPECT_EQ(info->endIndex_, 10);
    EXPECT_EQ(info->segmentStartPos_.size(), 2);
    EXPECT_EQ(info->segmentStartPos_[0], 5.0f);
    EXPECT_EQ(info->segmentStartPos_[1], 408.0f);
    EXPECT_EQ(info->itemInfos_[5].mainOffset, 408.0f);
    EXPECT_EQ(info->itemInfos_[5].crossIdx, 1);

    UpdateCurrentOffset(-1000.0f);
    EXPECT_EQ(info->startIndex_, 14);
    EXPECT_EQ(info->endIndex_, 20);
}

/**
 * @tc.name: Splice002
 * @tc.desc: Layout WaterFlow and then change section data in the middle.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowSegmentIntegratedTest, Splice002, TestSize.Level1)
{
    CreateWaterFlow();
    ViewAbstract::SetWidth(CalcLength(400.0f));
    ViewAbstract::SetHeight(CalcLength(600.f));
    CreateWaterFlowItems(37);
    auto secObj = pattern_->GetOrCreateWaterFlowSections();
    secObj->ChangeData(0, 0, SECTION_7);
    MockPipelineContext::GetCurrent()->FlushBuildFinishCallbacks();
    CreateDone();
    auto info = AceType::DynamicCast<WaterFlowLayoutInfo>(pattern_->layoutInfo_);
    EXPECT_EQ(info->endIndex_, 6);
    for (int i = 0; i < info->endIndex_; ++i) {
        EXPECT_EQ(GetChildHeight(frameNode_, i), 100.0f);
    }

    // replace FIRST section
    secObj->ChangeData(0, 1, SECTION_9);
    AddItems(2);
    frameNode_->ChildrenUpdatedFrom(37);
    MockPipelineContext::GetCurrent()->FlushBuildFinishCallbacks();
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(info->endIndex_, 10);
    for (int i = 0; i < info->endIndex_; ++i) {
        EXPECT_TRUE(GetChildFrameNode(frameNode_, i)->IsActive());
        EXPECT_EQ(GetChildHeight(frameNode_, i), 100.0f);
    }
    EXPECT_EQ(info->segmentStartPos_[0], 0.0f);

    // replace FIRST section
    secObj->ChangeData(0, 4, SECTION_7);
    for (int i = 0; i < 2; ++i) {
        frameNode_->RemoveChildAtIndex(0);
    }
    frameNode_->ChildrenUpdatedFrom(0);
    MockPipelineContext::GetCurrent()->FlushBuildFinishCallbacks();
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(info->childrenCount_, 37);
    EXPECT_EQ(info->endIndex_, 6);
    EXPECT_EQ(info->segmentStartPos_[0], 5.0f);
}

/**
 * @tc.name: Delete001
 * @tc.desc: Layout WaterFlow and then delete sections.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowSegmentIntegratedTest, Delete001, TestSize.Level1)
{
    CreateWaterFlow();
    ViewAbstract::SetWidth(CalcLength(400.0f));
    ViewAbstract::SetHeight(CalcLength(600.f));
    CreateWaterFlowItems(37);
    auto secObj = pattern_->GetOrCreateWaterFlowSections();
    secObj->ChangeData(0, 0, SECTION_7);
    MockPipelineContext::GetCurrent()->FlushBuildFinishCallbacks();
    CreateDone();
    auto info = AceType::DynamicCast<WaterFlowLayoutInfo>(pattern_->layoutInfo_);

    UpdateCurrentOffset(-200.0f);
    EXPECT_EQ(info->startIndex_, 1);

    secObj->ChangeData(1, 3, {});
    for (int i = 0; i < 33; ++i) {
        frameNode_->RemoveChildAtIndex(0);
    }
    frameNode_->ChildrenUpdatedFrom(4);
    MockPipelineContext::GetCurrent()->FlushBuildFinishCallbacks();
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(secObj->GetSectionInfo().size(), 1);
    EXPECT_EQ(secObj->GetSectionInfo()[0].itemsCount, 4);

    EXPECT_EQ(info->childrenCount_, 4);
    EXPECT_EQ(info->currentOffset_, 0.0f);
    EXPECT_EQ(info->startIndex_, 0);
    EXPECT_EQ(info->endIndex_, 3);
    EXPECT_EQ(info->segmentStartPos_.size(), 1);
    EXPECT_EQ(info->segmentStartPos_[0], 5.0f);
    EXPECT_EQ(GetChildHeight(frameNode_, 0), 100.0f);
    EXPECT_EQ(GetChildWidth(frameNode_, 0), 400.0f);
}

/**
 * @tc.name: Delete002
 * @tc.desc: Layout WaterFlow and then delete sections.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowSegmentIntegratedTest, Delete002, TestSize.Level1)
{
    CreateWaterFlow();
    ViewAbstract::SetWidth(CalcLength(400.0f));
    ViewAbstract::SetHeight(CalcLength(600.f));
    CreateWaterFlowItems(37);
    auto secObj = pattern_->GetOrCreateWaterFlowSections();
    secObj->ChangeData(0, 0, SECTION_7);
    MockPipelineContext::GetCurrent()->FlushBuildFinishCallbacks();
    CreateDone();
    auto info = AceType::DynamicCast<WaterFlowLayoutInfo>(pattern_->layoutInfo_);

    UpdateCurrentOffset(-400.0f);
    EXPECT_EQ(info->startIndex_, 3);
    EXPECT_EQ(info->storedOffset_, -95.0f);

    secObj->ChangeData(0, 2, {});
    for (int i = 0; i < 7; ++i) {
        frameNode_->RemoveChildAtIndex(0);
    }
    frameNode_->ChildrenUpdatedFrom(0);
    MockPipelineContext::GetCurrent()->FlushBuildFinishCallbacks();
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(secObj->GetSectionInfo().size(), 2);
    EXPECT_EQ(secObj->GetSectionInfo()[1].itemsCount, 30);

    EXPECT_EQ(info->currentOffset_, -414.0f);
    EXPECT_EQ(info->storedOffset_, -95.0f);
    EXPECT_EQ(info->startIndex_, 3);
    EXPECT_EQ(info->endIndex_, 9);
    EXPECT_EQ(info->segmentStartPos_.size(), 2);
    EXPECT_EQ(info->segmentStartPos_[0], 5.0f);
    EXPECT_EQ(info->itemInfos_[3].mainOffset, 319.0f);
    EXPECT_EQ(info->itemInfos_[3].crossIdx, 0);

    UpdateCurrentOffset(-10000.0f);
    EXPECT_EQ(info->currentOffset_, -2474.0f);
    EXPECT_EQ(info->startIndex_, 24);
    EXPECT_EQ(info->endIndex_, 29);
}

/**
 * @tc.name: Replace001
 * @tc.desc: Layout WaterFlow and then replace sections.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowSegmentIntegratedTest, Replace001, TestSize.Level1)
{
    CreateWaterFlow();
    ViewAbstract::SetWidth(CalcLength(400.0f));
    ViewAbstract::SetHeight(CalcLength(600.f));
    CreateWaterFlowItems(37);
    auto secObj = pattern_->GetOrCreateWaterFlowSections();
    secObj->ChangeData(0, 0, SECTION_7);
    MockPipelineContext::GetCurrent()->FlushBuildFinishCallbacks();
    CreateDone();
    auto info = AceType::DynamicCast<WaterFlowLayoutInfo>(pattern_->layoutInfo_);

    UpdateCurrentOffset(-205.0f);
    EXPECT_EQ(info->startIndex_, 2);

    secObj->ChangeData(1, 3, ADD_SECTION_6);
    for (int i = 0; i < 23; ++i) {
        frameNode_->RemoveChildAtIndex(0);
    }
    frameNode_->ChildrenUpdatedFrom(4);
    MockPipelineContext::GetCurrent()->FlushBuildFinishCallbacks();
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(secObj->GetSectionInfo().size(), 2);
    EXPECT_EQ(secObj->GetSectionInfo()[1].itemsCount, 10);

    EXPECT_EQ(info->currentOffset_, -205.0f);
    EXPECT_EQ(info->startIndex_, 2);
    EXPECT_EQ(info->endIndex_, 9);
    EXPECT_EQ(info->segmentStartPos_.size(), 2);
    EXPECT_EQ(info->segmentStartPos_[1], 408.0f);
    EXPECT_EQ(info->itemInfos_[3].mainOffset, 305.0f);
    EXPECT_EQ(info->itemInfos_[3].crossIdx, 0);

    UpdateCurrentOffset(-303.0f);
    EXPECT_EQ(info->currentOffset_, -508.0f);
    EXPECT_EQ(info->startIndex_, 5);
    EXPECT_EQ(info->endIndex_, 13);
    EXPECT_EQ(info->itemInfos_[7].mainOffset, 613.0f);
    EXPECT_EQ(info->itemInfos_[7].crossIdx, 1);

    UpdateCurrentOffset(1.0f);
    EXPECT_EQ(info->currentOffset_, -507.0f);
    EXPECT_EQ(info->startIndex_, 4);
    EXPECT_EQ(info->endIndex_, 13);
}

/**
 * @tc.name: Replace002
 * @tc.desc: Layout WaterFlow and then replace sections.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowSegmentIntegratedTest, Replace002, TestSize.Level1)
{
    CreateWaterFlow();
    ViewAbstract::SetWidth(CalcLength(400.0f));
    ViewAbstract::SetHeight(CalcLength(600.f));
    CreateWaterFlowItems(37);
    auto secObj = pattern_->GetOrCreateWaterFlowSections();
    secObj->ChangeData(0, 0, SECTION_7);
    MockPipelineContext::GetCurrent()->FlushBuildFinishCallbacks();
    CreateDone();
    auto info = AceType::DynamicCast<WaterFlowLayoutInfo>(pattern_->layoutInfo_);

    UpdateCurrentOffset(-300.0f);
    EXPECT_EQ(info->startIndex_, 2);
    EXPECT_EQ(info->storedOffset_, -95);

    // relative offset to the first item should remain constant
    secObj->ChangeData(0, 4, SECTION_7);
    MockPipelineContext::GetCurrent()->FlushBuildFinishCallbacks();
    FlushLayoutTask(frameNode_);

    EXPECT_EQ(info->currentOffset_, -300.0f);
    EXPECT_EQ(info->startIndex_, 2);
    EXPECT_EQ(info->storedOffset_, -95);
}

/**
 * @tc.name: Replace003
 * @tc.desc: Layout WaterFlow and then add item in last section.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowSegmentIntegratedTest, Replace003, TestSize.Level1)
{
    CreateWaterFlow();
    ViewAbstract::SetWidth(CalcLength(400.0f));
    ViewAbstract::SetHeight(CalcLength(600.f));
    CreateWaterFlowItems(37);
    auto secObj = pattern_->GetOrCreateWaterFlowSections();
    secObj->ChangeData(0, 0, SECTION_7);
    MockPipelineContext::GetCurrent()->FlushBuildFinishCallbacks();
    CreateDone();
    auto info = AceType::DynamicCast<WaterFlowLayoutInfo>(pattern_->layoutInfo_);
    UpdateCurrentOffset(-2000.0f);
    EXPECT_EQ(info->segmentStartPos_[2], 613.0f);
    EXPECT_EQ(info->currentOffset_, -2000.0f);
    EXPECT_EQ(info->startIndex_, 20);
    EXPECT_EQ(info->endIndex_, 26);
    EXPECT_EQ(info->itemInfos_.size(), 27);
    EXPECT_EQ(info->endPosArray_.size(), 26);

    AddItems(10);
    frameNode_->ChildrenUpdatedFrom(37);
    std::vector<WaterFlowSections::Section> newSection { SECTION_7[3] };
    newSection[0].itemsCount = 40;
    secObj->ChangeData(3, 1, newSection);
    pattern_->BeforeCreateLayoutWrapper();
    MockPipelineContext::GetCurrent()->FlushBuildFinishCallbacks();
    EXPECT_EQ(info->itemInfos_.size(), 27);
    EXPECT_EQ(info->items_[3].at(0).size(), 20);
    EXPECT_EQ(info->endPosArray_.size(), 26);
    EXPECT_EQ(info->segmentStartPos_[3], 621.0f);
    EXPECT_EQ(info->segmentStartPos_.size(), 4);
    EXPECT_EQ(info->segmentTails_.size(), 4);
    EXPECT_EQ(info->segmentTails_[3], 46);

    FlushLayoutTask(frameNode_);
    EXPECT_EQ(info->currentOffset_, -2000.0f);
    EXPECT_EQ(info->startIndex_, 20);
    EXPECT_EQ(GetChildY(frameNode_, 20), -53.0f);

    AddItems(7);
    frameNode_->ChildrenUpdatedFrom(7);
    secObj->ChangeData(1, 1, ADD_SECTION_7);
    pattern_->BeforeCreateLayoutWrapper();
    MockPipelineContext::GetCurrent()->FlushBuildFinishCallbacks();
    EXPECT_EQ(info->itemInfos_.size(), 14);
    EXPECT_EQ(info->segmentTails_[1], 13);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(info->startIndex_, 20);
    EXPECT_EQ(GetChildY(frameNode_, 20), -53.0f);
}

/**
 * @tc.name: Replace004
 * @tc.desc: Layout WaterFlow and then add item in last section.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowSegmentIntegratedTest, Replace004, TestSize.Level1)
{
    CreateWaterFlow();
    ViewAbstract::SetWidth(CalcLength(400.0f));
    ViewAbstract::SetHeight(CalcLength(600.f));
    CreateWaterFlowItems(6);
    auto secObj = pattern_->GetOrCreateWaterFlowSections();
    secObj->ChangeData(0, 0, SECTION_9);
    MockPipelineContext::GetCurrent()->FlushBuildFinishCallbacks();
    CreateDone();
    auto info = AceType::DynamicCast<WaterFlowLayoutInfo>(pattern_->layoutInfo_);

    AddItems(100);
    frameNode_->ChildrenUpdatedFrom(6);
    std::vector<WaterFlowSections::Section> newSection { SECTION_9[0] };
    newSection[0].itemsCount = 106;
    secObj->ChangeData(0, 1, newSection);
    pattern_->BeforeCreateLayoutWrapper();
    MockPipelineContext::GetCurrent()->FlushBuildFinishCallbacks();
    EXPECT_EQ(info->itemInfos_.size(), 6);
    EXPECT_EQ(info->items_[0].at(0).size(), 2);
    EXPECT_EQ(info->endPosArray_.size(), 2);
    EXPECT_EQ(info->segmentStartPos_[0], 0.0f);
    EXPECT_EQ(info->segmentStartPos_.size(), 1);
    EXPECT_EQ(info->segmentTails_.size(), 1);
    EXPECT_EQ(info->segmentTails_[0], 105);

    FlushLayoutTask(frameNode_);
    EXPECT_EQ(info->currentOffset_, 0.0f);
    EXPECT_EQ(info->endIndex_, 17);
    EXPECT_EQ(info->items_[0].at(0).size(), 6);
    UpdateCurrentOffset(-10000.0f);
    EXPECT_EQ(info->currentOffset_, -3000.0f);
    for (int i = 0; i < 100; ++i) {
        frameNode_->RemoveChildAtIndex(10);
    }
    frameNode_->ChildrenUpdatedFrom(10);
    newSection[0].itemsCount = 10;
    secObj->ChangeData(0, 1, newSection);
    pattern_->BeforeCreateLayoutWrapper();
    MockPipelineContext::GetCurrent()->FlushBuildFinishCallbacks();
    EXPECT_EQ(info->segmentTails_[0], 9);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(info->currentOffset_, 0.0f);
    EXPECT_EQ(info->endIndex_, 9);
    EXPECT_EQ(info->items_[0].at(0).size(), 4);
}

/**
 * @tc.name: Replace005
 * @tc.desc: Replace empty section with new data.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowSegmentIntegratedTest, Replace005, TestSize.Level1)
{
    CreateWaterFlow();
    ViewAbstract::SetWidth(CalcLength(400.0f));
    ViewAbstract::SetHeight(CalcLength(600.f));
    CreateWaterFlowItems(37);
    auto secObj = pattern_->GetOrCreateWaterFlowSections();
    secObj->ChangeData(0, 0, SECTION_7);
    MockPipelineContext::GetCurrent()->FlushBuildFinishCallbacks();
    CreateDone();
    auto info = AceType::DynamicCast<WaterFlowLayoutInfo>(pattern_->layoutInfo_);
    UpdateCurrentOffset(-2000.0f);
    EXPECT_EQ(info->segmentStartPos_[2], 613.0f);
    EXPECT_EQ(info->currentOffset_, -2000.0f);
    EXPECT_EQ(info->startIndex_, 20);
    EXPECT_EQ(info->endIndex_, 26);
    EXPECT_EQ(info->itemInfos_.size(), 27);
    EXPECT_EQ(info->endPosArray_.size(), 26);
    EXPECT_EQ(GetChildY(frameNode_, 20), -53.0f);

    AddItems(10);
    frameNode_->ChildrenUpdatedFrom(7);
    std::vector<WaterFlowSections::Section> newSection { SECTION_7[2] };
    newSection[0].itemsCount = 10;
    secObj->ChangeData(2, 1, newSection);
    pattern_->BeforeCreateLayoutWrapper();
    MockPipelineContext::GetCurrent()->FlushBuildFinishCallbacks();
    // section 2 reset should be skipped
    EXPECT_EQ(info->endPosArray_.size(), 16);
    EXPECT_EQ(info->segmentStartPos_.size(), 3);
    EXPECT_EQ(info->segmentTails_.size(), 4);
    EXPECT_EQ(info->segmentTails_[2], 16);

    FlushLayoutTask(frameNode_);
    EXPECT_EQ(info->startIndex_, 20);
    EXPECT_EQ(GetChildY(frameNode_, 20), -53.0f);
    EXPECT_EQ(info->segmentStartPos_.size(), 4);
}

/**
 * @tc.name: Replace006
 * @tc.desc: Replace empty section with new data.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowSegmentIntegratedTest, Replace006, TestSize.Level1)
{
    CreateWaterFlow();
    ViewAbstract::SetWidth(CalcLength(400.0f));
    ViewAbstract::SetHeight(CalcLength(600.f));
    CreateWaterFlowItems(37);
    auto secObj = pattern_->GetOrCreateWaterFlowSections();
    secObj->ChangeData(0, 0, SECTION_7);
    MockPipelineContext::GetCurrent()->FlushBuildFinishCallbacks();
    CreateDone();
    auto info = AceType::DynamicCast<WaterFlowLayoutInfo>(pattern_->layoutInfo_);
    UpdateCurrentOffset(-2000.0f);
    EXPECT_EQ(info->currentOffset_, -2000.0f);
    EXPECT_EQ(info->startIndex_, 20);

    for (int i = 0; i < 37; ++i) {
        frameNode_->RemoveChildAtIndex(0);
    }
    frameNode_->ChildrenUpdatedFrom(0);
    auto newSection = SECTION_9;
    newSection[0].itemsCount = 0;
    secObj->ChangeData(0, 4, newSection);
    MockPipelineContext::GetCurrent()->FlushBuildFinishCallbacks();

    FlushLayoutTask(frameNode_);
    EXPECT_EQ(info->startIndex_, 0);
    EXPECT_EQ(info->endIndex_, -1);

    secObj->ChangeData(0, 1, SECTION_9);
    AddItems(6);
    frameNode_->ChildrenUpdatedFrom(0);
    MockPipelineContext::GetCurrent()->FlushBuildFinishCallbacks();
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(info->endIndex_, 5);
    EXPECT_EQ(info->currentOffset_, 0.0f);
    EXPECT_EQ(GetChildY(frameNode_, 0), 0.0f);
}
} // namespace OHOS::Ace::NG
