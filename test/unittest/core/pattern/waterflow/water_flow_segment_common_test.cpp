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

// mock
#include "test/mock/core/pipeline/mock_pipeline_context.h"
namespace OHOS::Ace::NG {
class WaterFlowSegmentCommonTest : public WaterFlowTestNg {
protected:
    void GetInstance() override
    {
        WaterFlowTestNg::GetInstance();
        info_ = AceType::DynamicCast<WaterFlowLayoutInfoBase>(pattern_->layoutInfo_);
        EXPECT_TRUE(info_);
    }

    RefPtr<WaterFlowLayoutInfoBase> info_;
};

/**
 * @tc.name: Illegal001
 * @tc.desc: Layout WaterFlow with empty sections.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowSegmentCommonTest, Illegal001, TestSize.Level1)
{
    Create(
        [](WaterFlowModelNG model) {
            ViewAbstract::SetWidth(CalcLength(400.0f));
            ViewAbstract::SetHeight(CalcLength(600.f));
            CreateItem(37);
        },
        false);
    auto secObj = pattern_->GetOrCreateWaterFlowSections();
    secObj->ChangeData(0, 0, {});
    MockPipelineContext::GetCurrent()->FlushBuildFinishCallbacks();
    FlushLayoutTask(frameNode_);

    UpdateCurrentOffset(-205.0f);
    EXPECT_EQ(info_->startIndex_, 0);
    EXPECT_EQ(info_->endIndex_, -1);
}

/**
 * @tc.name: Illegal002
 * @tc.desc: Layout WaterFlow with negative main size.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowSegmentCommonTest, Illegal002, TestSize.Level1)
{
    Create(
        [](WaterFlowModelNG model) {
            ViewAbstract::SetWidth(CalcLength(400.0f));
            ViewAbstract::SetHeight(CalcLength(600.f));
            CreateItem(10);
        },
        false);
    auto secObj = pattern_->GetOrCreateWaterFlowSections();
    secObj->ChangeData(0, 0, SECTION_8);
    MockPipelineContext::GetCurrent()->FlushBuildFinishCallbacks();
    FlushLayoutTask(frameNode_);

    // user-defined negative size would be treated as 0
    UpdateCurrentOffset(-205.0f);
    EXPECT_EQ(info_->startIndex_, 0);
    EXPECT_EQ(info_->endIndex_, 9);
    for (int i = 0; i <= 9; ++i) {
        EXPECT_EQ(GetChildHeight(frameNode_, i), 0.0f);
    }
}

/**
 * @tc.name: Add001
 * @tc.desc: Layout WaterFlow and then add children
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowSegmentCommonTest, Add001, TestSize.Level1)
{
    Create(
        [](WaterFlowModelNG model) {
            ViewAbstract::SetWidth(CalcLength(400.0f));
            ViewAbstract::SetHeight(CalcLength(600.f));
            CreateItem(60);
        },
        false);
    auto secObj = pattern_->GetOrCreateWaterFlowSections();
    secObj->ChangeData(0, 0, SECTION_5);
    MockPipelineContext::GetCurrent()->FlushBuildFinishCallbacks();
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(info_->startIndex_, 0);
    EXPECT_EQ(info_->endIndex_, 10);
    EXPECT_EQ(GetChildY(frameNode_, 0), 0.0f);
    EXPECT_EQ(GetChildY(frameNode_, 1), 0.0f);
    EXPECT_EQ(GetChildY(frameNode_, 2), 0.0f);
    EXPECT_EQ(GetChildY(frameNode_, 3), 105.0f);
    EXPECT_EQ(GetChildY(frameNode_, 4), 105.0f);
    EXPECT_EQ(GetChildY(frameNode_, 5), 306.0f);
    EXPECT_EQ(GetChildY(frameNode_, 10), 511.0f);

    UpdateCurrentOffset(-2000.0f);
    EXPECT_EQ(info_->startIndex_, 19);
    EXPECT_EQ(info_->endIndex_, 23);
    EXPECT_EQ(info_->segmentTails_.size(), 5);
    EXPECT_EQ(GetChildY(frameNode_, 19), -180.0f);
    EXPECT_EQ(GetChildY(frameNode_, 20), 21.0f);
    EXPECT_EQ(GetChildY(frameNode_, 21), 122.0f);
    EXPECT_EQ(GetChildY(frameNode_, 22), 323.0f);
    EXPECT_EQ(GetChildY(frameNode_, 23), 424.0f);

    AddItems(10);
    secObj->ChangeData(5, 0, ADD_SECTION_6);
    frameNode_->ChildrenUpdatedFrom(60);
    MockPipelineContext::GetCurrent()->FlushBuildFinishCallbacks();
    EXPECT_EQ(secObj->GetSectionInfo().size(), 6);
    EXPECT_EQ(secObj->GetSectionInfo()[5].crossCount, 2);

    FlushLayoutTask(frameNode_);
    EXPECT_EQ(info_->startIndex_, 19);
    EXPECT_EQ(info_->endIndex_, 23);
    EXPECT_EQ(info_->segmentTails_.size(), 6);

    UpdateCurrentOffset(-10000.0f);
    EXPECT_EQ(info_->startIndex_, 63);
    EXPECT_EQ(info_->endIndex_, 69);
    EXPECT_EQ(GetChildRect(frameNode_, 69).Bottom(), 600.0f);
    EXPECT_EQ(GetChildX(frameNode_, 69), 0.0f);
}

/**
 * @tc.name: Splice001
 * @tc.desc: Layout WaterFlow and then change section data in the middle.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowSegmentCommonTest, Splice001, TestSize.Level1)
{
    Create(
        [](WaterFlowModelNG model) {
            ViewAbstract::SetWidth(CalcLength(400.0f));
            ViewAbstract::SetHeight(CalcLength(600.f));
            CreateItem(37);
        },
        false);
    auto secObj = pattern_->GetOrCreateWaterFlowSections();
    secObj->ChangeData(0, 0, SECTION_7);
    MockPipelineContext::GetCurrent()->FlushBuildFinishCallbacks();
    FlushLayoutTask(frameNode_);
    UpdateCurrentOffset(-300.0f);

    EXPECT_EQ(info_->startIndex_, 2);
    EXPECT_EQ(GetChildY(frameNode_, 2), -95.0f);

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

    EXPECT_EQ(info_->startIndex_, 2);
    EXPECT_EQ(info_->endIndex_, 10);
    EXPECT_EQ(GetChildY(frameNode_, 2), -95.0f);
    EXPECT_EQ(GetChildX(frameNode_, 2), 0.0f);
    EXPECT_EQ(GetChildY(frameNode_, 3), 5.0f);
    EXPECT_EQ(GetChildX(frameNode_, 3), 0.0f);
    EXPECT_EQ(GetChildY(frameNode_, 4), 108.0f);
    EXPECT_EQ(GetChildX(frameNode_, 4), 0.0f);
    EXPECT_EQ(GetChildY(frameNode_, 5), 108.0f);
    EXPECT_EQ(GetChildX(frameNode_, 5), 200.0f);
    EXPECT_EQ(GetChildY(frameNode_, 6), 213.0f);
    EXPECT_EQ(GetChildX(frameNode_, 6), 0.0f);
    EXPECT_EQ(GetChildY(frameNode_, 7), 313.0f);
    EXPECT_EQ(GetChildX(frameNode_, 7), 200.0f);
    EXPECT_EQ(GetChildY(frameNode_, 8), 318.0f);
    EXPECT_EQ(GetChildX(frameNode_, 8), 0.0f);
    EXPECT_EQ(GetChildY(frameNode_, 9), 423.0f);
    EXPECT_EQ(GetChildX(frameNode_, 9), 0.0f);
    EXPECT_EQ(GetChildY(frameNode_, 10), 518.0f);
    EXPECT_EQ(GetChildX(frameNode_, 10), 200.0f);

    UpdateCurrentOffset(-1000.0f);
    EXPECT_EQ(info_->startIndex_, 14);
    EXPECT_EQ(info_->endIndex_, 20);
}

/**
 * @tc.name: Splice002
 * @tc.desc: Layout WaterFlow and then change section data in the middle.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowSegmentCommonTest, Splice002, TestSize.Level1)
{
    Create(
        [](WaterFlowModelNG model) {
            ViewAbstract::SetWidth(CalcLength(400.0f));
            ViewAbstract::SetHeight(CalcLength(600.f));
            CreateItem(37);
        },
        false);
    auto secObj = pattern_->GetOrCreateWaterFlowSections();
    secObj->ChangeData(0, 0, SECTION_7);
    MockPipelineContext::GetCurrent()->FlushBuildFinishCallbacks();
    FlushLayoutTask(frameNode_);

    EXPECT_EQ(info_->endIndex_, 6);
    for (int i = 0; i < info_->endIndex_; ++i) {
        EXPECT_EQ(GetChildHeight(frameNode_, i), 100.0f);
    }

    // replace FIRST section
    secObj->ChangeData(0, 1, SECTION_9);
    AddItems(2);
    frameNode_->ChildrenUpdatedFrom(37);
    MockPipelineContext::GetCurrent()->FlushBuildFinishCallbacks();
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(info_->endIndex_, 10);
    for (int i = 0; i < info_->endIndex_; ++i) {
        EXPECT_TRUE(GetChildFrameNode(frameNode_, i)->IsActive());
        EXPECT_EQ(GetChildHeight(frameNode_, i), 100.0f);
    }

    // replace FIRST section
    secObj->ChangeData(0, 4, SECTION_7);
    for (int i = 0; i < 2; ++i) {
        frameNode_->RemoveChildAtIndex(0);
    }
    frameNode_->ChildrenUpdatedFrom(0);
    MockPipelineContext::GetCurrent()->FlushBuildFinishCallbacks();
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(info_->endIndex_, 6);
}

/**
 * @tc.name: Delete001
 * @tc.desc: Layout WaterFlow and then delete sections.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowSegmentCommonTest, Delete001, TestSize.Level1)
{
    Create(
        [](WaterFlowModelNG model) {
            ViewAbstract::SetWidth(CalcLength(400.0f));
            ViewAbstract::SetHeight(CalcLength(600.f));
            CreateItem(37);
        },
        false);
    auto secObj = pattern_->GetOrCreateWaterFlowSections();
    secObj->ChangeData(0, 0, SECTION_7);
    MockPipelineContext::GetCurrent()->FlushBuildFinishCallbacks();
    FlushLayoutTask(frameNode_);

    UpdateCurrentOffset(-200.0f);
    EXPECT_EQ(info_->startIndex_, 1);

    secObj->ChangeData(1, 3, {});
    for (int i = 0; i < 33; ++i) {
        frameNode_->RemoveChildAtIndex(0);
    }
    frameNode_->ChildrenUpdatedFrom(4);
    MockPipelineContext::GetCurrent()->FlushBuildFinishCallbacks();
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(secObj->GetSectionInfo().size(), 1);
    EXPECT_EQ(secObj->GetSectionInfo()[0].itemsCount, 4);

    EXPECT_EQ(info_->startIndex_, 0);
    EXPECT_EQ(info_->endIndex_, 3);
    EXPECT_EQ(GetChildHeight(frameNode_, 0), 100.0f);
    EXPECT_EQ(GetChildWidth(frameNode_, 0), 400.0f);
}

/**
 * @tc.name: Delete002
 * @tc.desc: Layout WaterFlow and then delete sections.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowSegmentCommonTest, Delete002, TestSize.Level1)
{
    Create(
        [](WaterFlowModelNG model) {
            ViewAbstract::SetWidth(CalcLength(400.0f));
            ViewAbstract::SetHeight(CalcLength(600.f));
            CreateItem(37);
        },
        false);
    auto secObj = pattern_->GetOrCreateWaterFlowSections();
    secObj->ChangeData(0, 0, SECTION_7);
    MockPipelineContext::GetCurrent()->FlushBuildFinishCallbacks();
    FlushLayoutTask(frameNode_);

    UpdateCurrentOffset(-400.0f);
    EXPECT_EQ(info_->startIndex_, 3);
    EXPECT_EQ(info_->storedOffset_, -95.0f);

    secObj->ChangeData(0, 2, {});
    for (int i = 0; i < 7; ++i) {
        frameNode_->RemoveChildAtIndex(0);
    }
    frameNode_->ChildrenUpdatedFrom(0);
    MockPipelineContext::GetCurrent()->FlushBuildFinishCallbacks();
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(secObj->GetSectionInfo().size(), 2);
    EXPECT_EQ(secObj->GetSectionInfo()[1].itemsCount, 30);

    EXPECT_EQ(info_->storedOffset_, -95.0f);
    EXPECT_EQ(info_->startIndex_, 3);
    EXPECT_EQ(info_->endIndex_, 9);

    UpdateCurrentOffset(-10000.0f);
    EXPECT_EQ(info_->startIndex_, 24);
    EXPECT_EQ(info_->endIndex_, 29);
}

/**
 * @tc.name: Replace001
 * @tc.desc: Layout WaterFlow and then replace sections.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowSegmentCommonTest, Replace001, TestSize.Level1)
{
    Create(
        [](WaterFlowModelNG model) {
            ViewAbstract::SetWidth(CalcLength(400.0f));
            ViewAbstract::SetHeight(CalcLength(600.f));
            CreateItem(37);
        },
        false);
    auto secObj = pattern_->GetOrCreateWaterFlowSections();
    secObj->ChangeData(0, 0, SECTION_7);
    MockPipelineContext::GetCurrent()->FlushBuildFinishCallbacks();
    FlushLayoutTask(frameNode_);

    UpdateCurrentOffset(-205.0f);
    EXPECT_EQ(info_->startIndex_, 2);

    secObj->ChangeData(1, 3, ADD_SECTION_6);
    for (int i = 0; i < 23; ++i) {
        frameNode_->RemoveChildAtIndex(0);
    }
    frameNode_->ChildrenUpdatedFrom(4);
    MockPipelineContext::GetCurrent()->FlushBuildFinishCallbacks();
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(secObj->GetSectionInfo().size(), 2);
    EXPECT_EQ(secObj->GetSectionInfo()[1].itemsCount, 10);

    EXPECT_EQ(info_->startIndex_, 2);
    EXPECT_EQ(info_->endIndex_, 9);

    UpdateCurrentOffset(-303.0f);
    EXPECT_EQ(info_->startIndex_, 5);
    EXPECT_EQ(info_->endIndex_, 13);

    UpdateCurrentOffset(1.0f);
    EXPECT_EQ(info_->startIndex_, 4);
    EXPECT_EQ(info_->endIndex_, 13);
}

/**
 * @tc.name: Replace002
 * @tc.desc: Layout WaterFlow and then replace sections.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowSegmentCommonTest, Replace002, TestSize.Level1)
{
    Create(
        [](WaterFlowModelNG model) {
            ViewAbstract::SetWidth(CalcLength(400.0f));
            ViewAbstract::SetHeight(CalcLength(600.f));
            CreateItem(37);
        },
        false);
    auto secObj = pattern_->GetOrCreateWaterFlowSections();
    secObj->ChangeData(0, 0, SECTION_7);
    MockPipelineContext::GetCurrent()->FlushBuildFinishCallbacks();
    FlushLayoutTask(frameNode_);

    UpdateCurrentOffset(-300.0f);
    EXPECT_EQ(info_->startIndex_, 2);
    EXPECT_EQ(info_->storedOffset_, -95);

    // relative offset to the first item should remain constant
    secObj->ChangeData(0, 4, SECTION_7);
    MockPipelineContext::GetCurrent()->FlushBuildFinishCallbacks();
    FlushLayoutTask(frameNode_);

    EXPECT_EQ(info_->startIndex_, 2);
    EXPECT_EQ(info_->storedOffset_, -95);
}

/**
 * @tc.name: Replace003
 * @tc.desc: Layout WaterFlow and then add item in last section.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowSegmentCommonTest, Replace003, TestSize.Level1)
{
    Create(
        [](WaterFlowModelNG model) {
            ViewAbstract::SetWidth(CalcLength(400.0f));
            ViewAbstract::SetHeight(CalcLength(600.f));
            CreateItem(37);
        },
        false);
    auto secObj = pattern_->GetOrCreateWaterFlowSections();
    secObj->ChangeData(0, 0, SECTION_7);
    MockPipelineContext::GetCurrent()->FlushBuildFinishCallbacks();
    FlushLayoutTask(frameNode_);

    UpdateCurrentOffset(-2000.0f);
    EXPECT_EQ(info_->startIndex_, 20);
    EXPECT_EQ(info_->endIndex_, 26);

    AddItems(10);
    frameNode_->ChildrenUpdatedFrom(37);
    std::vector<WaterFlowSections::Section> newSection { SECTION_7[3] };
    newSection[0].itemsCount = 40;
    secObj->ChangeData(3, 1, newSection);
    MockPipelineContext::GetCurrent()->FlushBuildFinishCallbacks();
    EXPECT_EQ(info_->segmentTails_.size(), 4);
    EXPECT_EQ(info_->segmentTails_[3], 46);

    FlushLayoutTask(frameNode_);
    EXPECT_EQ(info_->startIndex_, 20);
    EXPECT_EQ(GetChildY(frameNode_, 20), -53.0f);

    AddItems(7);
    frameNode_->ChildrenUpdatedFrom(7);
    secObj->ChangeData(1, 1, ADD_SECTION_7);
    MockPipelineContext::GetCurrent()->FlushBuildFinishCallbacks();
    EXPECT_EQ(info_->segmentTails_[1], 13);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(info_->startIndex_, 20);
    EXPECT_EQ(GetChildY(frameNode_, 20), -53.0f);
}

/**
 * @tc.name: Replace004
 * @tc.desc: Layout WaterFlow and then add item in last section.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowSegmentCommonTest, Replace004, TestSize.Level1)
{
    Create(
        [](WaterFlowModelNG model) {
            ViewAbstract::SetWidth(CalcLength(400.0f));
            ViewAbstract::SetHeight(CalcLength(600.f));
            CreateItem(6);
        },
        false);
    auto secObj = pattern_->GetOrCreateWaterFlowSections();
    secObj->ChangeData(0, 0, SECTION_9);
    MockPipelineContext::GetCurrent()->FlushBuildFinishCallbacks();
    FlushLayoutTask(frameNode_);

    AddItems(100);
    frameNode_->ChildrenUpdatedFrom(6);
    std::vector<WaterFlowSections::Section> newSection { SECTION_9[0] };
    newSection[0].itemsCount = 106;
    secObj->ChangeData(0, 1, newSection);
    MockPipelineContext::GetCurrent()->FlushBuildFinishCallbacks();
    EXPECT_EQ(info_->segmentTails_.size(), 1);
    EXPECT_EQ(info_->segmentTails_[0], 105);

    FlushLayoutTask(frameNode_);
    EXPECT_EQ(info_->endIndex_, 17);
    UpdateCurrentOffset(-10000.0f);
    for (int i = 0; i < 100; ++i) {
        frameNode_->RemoveChildAtIndex(10);
    }
    frameNode_->ChildrenUpdatedFrom(10);
    newSection[0].itemsCount = 10;
    secObj->ChangeData(0, 1, newSection);
    MockPipelineContext::GetCurrent()->FlushBuildFinishCallbacks();
    EXPECT_EQ(info_->segmentTails_[0], 9);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(info_->endIndex_, 9);
    EXPECT_EQ(GetChildY(frameNode_, 0), 0.0f);
    EXPECT_EQ(GetChildRect(frameNode_, 9).Bottom(), 400.0f);
}

/**
 * @tc.name: Replace005
 * @tc.desc: Replace empty section with new data.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowSegmentCommonTest, Replace005, TestSize.Level1)
{
    Create(
        [](WaterFlowModelNG model) {
            ViewAbstract::SetWidth(CalcLength(400.0f));
            ViewAbstract::SetHeight(CalcLength(600.f));
            CreateItem(37);
        },
        false);
    auto secObj = pattern_->GetOrCreateWaterFlowSections();
    secObj->ChangeData(0, 0, SECTION_7);
    MockPipelineContext::GetCurrent()->FlushBuildFinishCallbacks();
    FlushLayoutTask(frameNode_);

    UpdateCurrentOffset(-2000.0f);
    EXPECT_EQ(info_->startIndex_, 20);
    EXPECT_EQ(info_->endIndex_, 26);
    EXPECT_EQ(GetChildY(frameNode_, 20), -53.0f);

    AddItems(10);
    frameNode_->ChildrenUpdatedFrom(7);
    std::vector<WaterFlowSections::Section> newSection { SECTION_7[2] };
    newSection[0].itemsCount = 10;
    secObj->ChangeData(2, 1, newSection);
    MockPipelineContext::GetCurrent()->FlushBuildFinishCallbacks();
    EXPECT_EQ(info_->segmentTails_.size(), 4);
    EXPECT_EQ(info_->segmentTails_[2], 16);

    FlushLayoutTask(frameNode_);
    EXPECT_EQ(info_->startIndex_, 20);
    EXPECT_EQ(GetChildY(frameNode_, 20), -53.0f);
}

/**
 * @tc.name: Replace006
 * @tc.desc: Replace empty section with new data.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowSegmentCommonTest, Replace006, TestSize.Level1)
{
    Create(
        [](WaterFlowModelNG model) {
            ViewAbstract::SetWidth(CalcLength(400.0f));
            ViewAbstract::SetHeight(CalcLength(600.f));
            CreateItem(37);
        },
        false);
    auto secObj = pattern_->GetOrCreateWaterFlowSections();
    secObj->ChangeData(0, 0, SECTION_7);
    MockPipelineContext::GetCurrent()->FlushBuildFinishCallbacks();
    FlushLayoutTask(frameNode_);

    UpdateCurrentOffset(-2000.0f);
    EXPECT_EQ(info_->startIndex_, 20);

    for (int i = 0; i < 37; ++i) {
        frameNode_->RemoveChildAtIndex(0);
    }
    frameNode_->ChildrenUpdatedFrom(0);
    auto newSection = SECTION_9;
    newSection[0].itemsCount = 0;
    secObj->ChangeData(0, 4, newSection);
    MockPipelineContext::GetCurrent()->FlushBuildFinishCallbacks();

    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(info_->startIndex_ > info_->endIndex_);

    secObj->ChangeData(0, 1, SECTION_9);
    AddItems(6);
    frameNode_->ChildrenUpdatedFrom(0);
    MockPipelineContext::GetCurrent()->FlushBuildFinishCallbacks();
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(info_->endIndex_, 5);
    EXPECT_EQ(GetChildY(frameNode_, 0), 0.0f);
}

/**
 * @tc.name: Reset005
 * @tc.desc: Test Changing cross gap.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowSegmentCommonTest, Reset005, TestSize.Level1)
{
    Create([](WaterFlowModelNG model) {
        model.SetColumnsTemplate("1fr 1fr 1fr 1fr");
        model.SetColumnsGap(Dimension(5.0f));
        model.SetRowsGap(Dimension(1.0f));
        CreateItem(200);
        ViewStackProcessor::GetInstance()->Pop();
    });
    EXPECT_EQ(info_->startIndex_, 0);
    EXPECT_EQ(info_->endIndex_, 21);
    for (int i = 0; i <= 21; ++i) {
        EXPECT_EQ(GetChildWidth(frameNode_, i), 116.25f);
    }

    layoutProperty_->UpdateColumnsGap(Dimension(1.0f));
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(info_->startIndex_, 0);
    EXPECT_EQ(info_->endIndex_, 21);
    for (int i = 0; i <= 21; ++i) {
        EXPECT_EQ(GetChildWidth(frameNode_, i), 119.25f);
    }
}

/**
 * @tc.name: Segmented006
 * @tc.desc: Layout WaterFlow with SEGMENT_7 and change RowGaps
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowSegmentCommonTest, Segmented006, TestSize.Level1)
{
    Create(
        [](WaterFlowModelNG model) {
            ViewAbstract::SetWidth(CalcLength(400.0f));
            ViewAbstract::SetHeight(CalcLength(600.f));
            CreateItem(37);
        },
        false);
    auto secObj = pattern_->GetOrCreateWaterFlowSections();
    secObj->ChangeData(0, 0, SECTION_7);
    MockPipelineContext::GetCurrent()->FlushBuildFinishCallbacks();
    FlushLayoutTask(frameNode_);

    EXPECT_EQ(*info_->margins_[0].top, 5.0f);
    EXPECT_EQ(GetChildY(frameNode_, 0), 5.0f);
    EXPECT_EQ(GetChildY(frameNode_, 4), 408.0f);

    UpdateCurrentOffset(-600.0f);

    EXPECT_EQ(GetChildY(frameNode_, 6), -92.0f);
    EXPECT_EQ(GetChildY(frameNode_, 7), 21.0f);
    EXPECT_EQ(info_->startIndex_, 6);

    layoutProperty_->UpdateRowsGap(10.0_vp);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(info_->startIndex_, 6);

    UpdateCurrentOffset(600.0f);
    EXPECT_EQ(info_->startIndex_, 0);
    layoutProperty_->UpdateRowsGap(11.0_vp);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(info_->startIndex_, 0);
    EXPECT_EQ(info_->endIndex_, 6);
}

/**
 * @tc.name: Segmented007
 * @tc.desc: Layout WaterFlow with SEGMENT_7 and change RowGaps
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowSegmentCommonTest, Segmented007, TestSize.Level1)
{
    Create(
        [](WaterFlowModelNG model) {
            ViewAbstract::SetWidth(CalcLength(400.0f));
            ViewAbstract::SetHeight(CalcLength(600.f));
            CreateItem(60);
        },
        false);
    auto secObj = pattern_->GetOrCreateWaterFlowSections();
    secObj->ChangeData(0, 0, SECTION_4);
    MockPipelineContext::GetCurrent()->FlushBuildFinishCallbacks();
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(IsEqual(pattern_->GetItemRect(0), Rect(0, 0, 400.0f / 3, 100)));
    EXPECT_TRUE(IsEqual(pattern_->GetItemRect(2), Rect(400.0f / 3 * 2, 0, 400.0f / 3, 100)));

    layoutProperty_->UpdateLayoutDirection(TextDirection::RTL);
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(IsEqual(pattern_->GetItemRect(0), Rect(400.0f / 3 * 2, 0, 400.0f / 3, 100)));
    EXPECT_TRUE(IsEqual(pattern_->GetItemRect(2), Rect(0, 0, 400.0f / 3, 100)));
}

/**
 * @tc.name: CheckHeight001
 * @tc.desc: Layout WaterFlow and check if callback height is used
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowSegmentCommonTest, CheckHeight001, TestSize.Level1)
{
    Create(
        [](WaterFlowModelNG model) {
            ViewAbstract::SetWidth(CalcLength(400.0f));
            ViewAbstract::SetHeight(CalcLength(600.f));
            CreateItem(37);
        },
        false);
    auto secObj = pattern_->GetOrCreateWaterFlowSections();
    secObj->ChangeData(0, 0, SECTION_7);
    MockPipelineContext::GetCurrent()->FlushBuildFinishCallbacks();
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(info_->startIndex_, 0);
    EXPECT_EQ(info_->endIndex_, 6);
    EXPECT_EQ(GetChildY(frameNode_, 6), 508.0f);

    UpdateCurrentOffset(-10000.0f);
    EXPECT_EQ(info_->Offset(), -3082.0f);
    EXPECT_EQ(info_->startIndex_, 31);
    EXPECT_EQ(info_->endIndex_, 36);
    EXPECT_EQ(GetChildY(frameNode_, 36), 497.0f);
    EXPECT_EQ(GetChildY(frameNode_, 35), 395.0f);
    for (int i = 31; i <= 36; ++i) {
        EXPECT_EQ(GetChildHeight(frameNode_, i), 100.0f);
    }

    for (const auto& child : frameNode_->GetChildren()) {
        auto node = AceType::DynamicCast<FrameNode>(child);
        node->GetGeometryNode()->SetFrameSize({});
        node->GetLayoutProperty()->UpdateUserDefinedIdealSize({ CalcLength(50.0f), CalcLength(50.0f) });
    }

    UpdateCurrentOffset(10000.0f);
    EXPECT_EQ(info_->Offset(), 0.0f);
    EXPECT_EQ(info_->startIndex_, 0);
    EXPECT_EQ(info_->endIndex_, 6);
    for (int i = 0; i <= 6; ++i) {
        EXPECT_EQ(GetChildHeight(frameNode_, i), 100.0f);
    }
}

/**
 * @tc.name: ScrollToEdge
 * @tc.desc: Layout WaterFlow and check if callback height is used
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowSegmentCommonTest, ScrollToEdge, TestSize.Level1)
{
    Create(
        [](WaterFlowModelNG model) {
            ViewAbstract::SetWidth(CalcLength(400.0f));
            ViewAbstract::SetHeight(CalcLength(600.f));
            CreateItem(37);
        },
        false);
    auto secObj = pattern_->GetOrCreateWaterFlowSections();
    secObj->ChangeData(0, 0, SECTION_7);
    MockPipelineContext::GetCurrent()->FlushBuildFinishCallbacks();
    FlushLayoutTask(frameNode_);
    pattern_->ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, false);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(GetChildY(frameNode_, 36), 500.0f);

    pattern_->ScrollToEdge(ScrollEdgeType::SCROLL_TOP, false);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(GetChildY(frameNode_, 0), 0.0f);
}

/**
 * @tc.name: Constraint001
 * @tc.desc: Test Layout when the layoutConstraint changes.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowSegmentCommonTest, Constraint001, TestSize.Level1)
{
    Create(
        [](WaterFlowModelNG model) {
            ViewAbstract::SetWidth(CalcLength(400.0f));
            ViewAbstract::SetHeight(CalcLength(600.f));
            CreateItem(60);
        },
        false);
    auto secObj = pattern_->GetOrCreateWaterFlowSections();
    secObj->ChangeData(0, 0, SECTION_5);
    MockPipelineContext::GetCurrent()->FlushBuildFinishCallbacks();
    FlushLayoutTask(frameNode_);

    EXPECT_EQ(info_->startIndex_, 0);
    EXPECT_EQ(info_->endIndex_, 10);
    EXPECT_TRUE(IsEqual(pattern_->GetItemRect(0), Rect(0, 0, 400.f / 3, 100)));

    layoutProperty_->UpdateUserDefinedIdealSize(CalcSize(CalcLength(500.0f), CalcLength(Dimension(600.0f))));
    FlushLayoutTask(frameNode_);
    for (int i = 0; i < 5; i++) {
        EXPECT_EQ(GetChildWidth(frameNode_, i), 500.f / 3);
    }
    for (int i = 5; i < 10; i++) {
        EXPECT_EQ(GetChildWidth(frameNode_, i), (500.f - 3) / 5);
    }
    EXPECT_EQ(GetChildWidth(frameNode_, 10), 500.f);
    EXPECT_EQ(info_->endIndex_, 10);

    layoutProperty_->UpdateUserDefinedIdealSize(CalcSize(CalcLength(400.0f), CalcLength(Dimension(700.0f))));
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(IsEqual(pattern_->GetItemRect(0), Rect(0, 0, 400.f / 3, 100)));
    EXPECT_EQ(info_->endIndex_, 11);

    layoutProperty_->UpdateUserDefinedIdealSize(CalcSize(CalcLength(500.0f), CalcLength(Dimension(700.0f))));
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(IsEqual(pattern_->GetItemRect(0), Rect(0, 0, 500.f / 3, 100)));
    EXPECT_EQ(info_->endIndex_, 11);
}

/**
 * @tc.name: Multi001
 * @tc.desc: Test regular scrolling.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowSegmentCommonTest, Multi001, TestSize.Level1)
{
    Create(
        [](WaterFlowModelNG model) {
            ViewAbstract::SetWidth(CalcLength(400.0f));
            ViewAbstract::SetHeight(CalcLength(400.f));
            CreateRandomItem(45);
        },
        false);
    auto secObj = pattern_->GetOrCreateWaterFlowSections();
    secObj->ChangeData(0, 0, SECTION_10);
    MockPipelineContext::GetCurrent()->FlushBuildFinishCallbacks();
    FlushLayoutTask(frameNode_);

    float maxHeight = 0.0f;
    for (int i = 0; i <= 2; ++i) {
        maxHeight = std::max(maxHeight, GetChildHeight(frameNode_, i));
    }
    UpdateCurrentOffset(-maxHeight - 10.0f);
    EXPECT_EQ(info_->startIndex_, 3);

    UpdateCurrentOffset(4.0f);
    EXPECT_EQ(info_->startIndex_, 3);
    const int32_t endIdx = info_->endIndex_;

    UpdateCurrentOffset(4.0f);
    EXPECT_LT(info_->startIndex_, 3);
    EXPECT_LE(info_->endIndex_, endIdx);

    UpdateCurrentOffset(-4.0f);
    auto newSec = SECTION_10[1];
    newSec.margin->top = CalcLength(10.0f);
    secObj->ChangeData(1, 1, { newSec });
    MockPipelineContext::GetCurrent()->FlushBuildFinishCallbacks();
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(info_->startIndex_, 3);
    EXPECT_EQ(info_->endIndex_, endIdx);

    UpdateCurrentOffset(4.0f);
    EXPECT_EQ(info_->startIndex_, 3);

    UpdateCurrentOffset(5.0f);
    EXPECT_LT(info_->startIndex_, 3);
    EXPECT_LE(info_->endIndex_, endIdx);
}

/**
 * @tc.name: Illegal003
 * @tc.desc: Layout WaterFlow without items.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowSegmentCommonTest, Illegal003, TestSize.Level1)
{
    Create(
        [](WaterFlowModelNG model) {
            ViewAbstract::SetWidth(CalcLength(400.0f));
            ViewAbstract::SetHeight(CalcLength(600.f));
            CreateItem(6);
        },
        false);
    auto secObj = pattern_->GetOrCreateWaterFlowSections();
    secObj->ChangeData(0, 0, SECTION_9);
    MockPipelineContext::GetCurrent()->FlushBuildFinishCallbacks();
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(info_->endIndex_, 5);

    auto newSection = SECTION_8;
    newSection[0].itemsCount = 0;
    secObj->ChangeData(0, 1, newSection);
    for (int i = 0; i < 10; ++i) {
        frameNode_->RemoveChildAtIndex(0);
    }
    frameNode_->ChildrenUpdatedFrom(0);
    MockPipelineContext::GetCurrent()->FlushBuildFinishCallbacks();
    FlushLayoutTask(frameNode_);
    pattern_->ScrollToIndex(LAST_ITEM);
    EXPECT_EQ(info_->jumpIndex_, LAST_ITEM);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(info_->endIndex_, -1);
    EXPECT_GT(info_->startIndex_, info_->endIndex_);
}
} // namespace OHOS::Ace::NG
