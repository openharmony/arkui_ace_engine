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

// mock
#include "test/mock/core/pipeline/mock_pipeline_context.h"
namespace OHOS::Ace::NG {
class WaterFlowSegmentCommonTest : public WaterFlowTestNg {
protected:
    void GetWaterFlow() override
    {
        WaterFlowTestNg::GetWaterFlow();
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
    CreateWaterFlow();
    ViewAbstract::SetWidth(CalcLength(400.0f));
    ViewAbstract::SetHeight(CalcLength(600.f));
    CreateWaterFlowItems(37);
    auto secObj = pattern_->GetOrCreateWaterFlowSections();
    secObj->ChangeData(0, 0, {});
    MockPipelineContext::GetCurrent()->FlushBuildFinishCallbacks();
    CreateDone();

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
    CreateWaterFlow();
    ViewAbstract::SetWidth(CalcLength(400.0f));
    ViewAbstract::SetHeight(CalcLength(600.f));
    CreateWaterFlowItems(10);
    auto secObj = pattern_->GetOrCreateWaterFlowSections();
    secObj->ChangeData(0, 0, SECTION_8);
    MockPipelineContext::GetCurrent()->FlushBuildFinishCallbacks();
    CreateDone();

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
    CreateWaterFlow();
    ViewAbstract::SetWidth(CalcLength(400.0f));
    ViewAbstract::SetHeight(CalcLength(600.f));
    CreateWaterFlowItems(60);
    auto secObj = pattern_->GetOrCreateWaterFlowSections();
    secObj->ChangeData(0, 0, SECTION_5);
    MockPipelineContext::GetCurrent()->FlushBuildFinishCallbacks();
    CreateDone();
    EXPECT_EQ(info_->startIndex_, 0);
    EXPECT_EQ(info_->endIndex_, 10);
    EXPECT_EQ(GetChildY(frameNode_, 0), 0.0f);
    EXPECT_EQ(GetChildY(frameNode_, 1), 0.0f);
    EXPECT_EQ(GetChildY(frameNode_, 2), 0.0f);
    EXPECT_EQ(GetChildY(frameNode_, 3), 105.0f);
    EXPECT_EQ(GetChildY(frameNode_, 4), 105.0f);
    EXPECT_EQ(GetChildY(frameNode_, 5), 306.0f);
    EXPECT_EQ(GetChildY(frameNode_, 10), 511.0f);

    pattern_->isAnimationStop_ = false; // prevent jumping
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

    FlushUITasks();
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
    CreateWaterFlow();
    ViewAbstract::SetWidth(CalcLength(400.0f));
    ViewAbstract::SetHeight(CalcLength(600.f));
    CreateWaterFlowItems(37);
    auto secObj = pattern_->GetOrCreateWaterFlowSections();
    secObj->ChangeData(0, 0, SECTION_7);
    MockPipelineContext::GetCurrent()->FlushBuildFinishCallbacks();
    CreateDone();
    UpdateCurrentOffset(-300.0f);

    EXPECT_EQ(info_->startIndex_, 2);
    EXPECT_EQ(GetChildY(frameNode_, 2), -95.0f);

    // replace second section
    secObj->ChangeData(1, 1, ADD_SECTION_6);
    AddItems(7);
    frameNode_->ChildrenUpdatedFrom(37);
    MockPipelineContext::GetCurrent()->FlushBuildFinishCallbacks();
    FlushUITasks();
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
    CreateWaterFlow();
    ViewAbstract::SetWidth(CalcLength(400.0f));
    ViewAbstract::SetHeight(CalcLength(600.f));
    CreateWaterFlowItems(37);
    auto secObj = pattern_->GetOrCreateWaterFlowSections();
    secObj->ChangeData(0, 0, SECTION_7);
    MockPipelineContext::GetCurrent()->FlushBuildFinishCallbacks();
    CreateDone();

    EXPECT_EQ(info_->endIndex_, 6);
    for (int i = 0; i < info_->endIndex_; ++i) {
        EXPECT_EQ(GetChildHeight(frameNode_, i), 100.0f);
    }

    // replace FIRST section
    secObj->ChangeData(0, 1, SECTION_9);
    AddItems(2);
    frameNode_->ChildrenUpdatedFrom(37);
    MockPipelineContext::GetCurrent()->FlushBuildFinishCallbacks();
    FlushUITasks();
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
    FlushUITasks();
    EXPECT_EQ(info_->endIndex_, 6);
}

/**
 * @tc.name: Delete001
 * @tc.desc: Layout WaterFlow and then delete sections.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowSegmentCommonTest, Delete001, TestSize.Level1)
{
    CreateWaterFlow();
    ViewAbstract::SetWidth(CalcLength(400.0f));
    ViewAbstract::SetHeight(CalcLength(600.f));
    CreateWaterFlowItems(37);
    auto secObj = pattern_->GetOrCreateWaterFlowSections();
    secObj->ChangeData(0, 0, SECTION_7);
    MockPipelineContext::GetCurrent()->FlushBuildFinishCallbacks();
    CreateDone();

    UpdateCurrentOffset(-200.0f);
    EXPECT_EQ(info_->startIndex_, 1);

    secObj->ChangeData(1, 3, {});
    for (int i = 0; i < 33; ++i) {
        frameNode_->RemoveChildAtIndex(0);
    }
    frameNode_->ChildrenUpdatedFrom(4);
    MockPipelineContext::GetCurrent()->FlushBuildFinishCallbacks();
    FlushUITasks();
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
    CreateWaterFlow();
    ViewAbstract::SetWidth(CalcLength(400.0f));
    ViewAbstract::SetHeight(CalcLength(600.f));
    CreateWaterFlowItems(37);
    auto secObj = pattern_->GetOrCreateWaterFlowSections();
    secObj->ChangeData(0, 0, SECTION_7);
    MockPipelineContext::GetCurrent()->FlushBuildFinishCallbacks();
    CreateDone();

    UpdateCurrentOffset(-400.0f);
    EXPECT_EQ(info_->startIndex_, 3);
    EXPECT_EQ(info_->storedOffset_, -95.0f);

    secObj->ChangeData(0, 2, {});
    for (int i = 0; i < 7; ++i) {
        frameNode_->RemoveChildAtIndex(0);
    }
    frameNode_->ChildrenUpdatedFrom(0);
    MockPipelineContext::GetCurrent()->FlushBuildFinishCallbacks();
    FlushUITasks();
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
    CreateWaterFlow();
    ViewAbstract::SetWidth(CalcLength(400.0f));
    ViewAbstract::SetHeight(CalcLength(600.f));
    CreateWaterFlowItems(37);
    auto secObj = pattern_->GetOrCreateWaterFlowSections();
    secObj->ChangeData(0, 0, SECTION_7);
    MockPipelineContext::GetCurrent()->FlushBuildFinishCallbacks();
    CreateDone();

    UpdateCurrentOffset(-205.0f);
    EXPECT_EQ(info_->startIndex_, 2);

    secObj->ChangeData(1, 3, ADD_SECTION_6);
    for (int i = 0; i < 23; ++i) {
        frameNode_->RemoveChildAtIndex(0);
    }
    frameNode_->ChildrenUpdatedFrom(4);
    MockPipelineContext::GetCurrent()->FlushBuildFinishCallbacks();
    FlushUITasks();
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
    CreateWaterFlow();
    ViewAbstract::SetWidth(CalcLength(400.0f));
    ViewAbstract::SetHeight(CalcLength(600.f));
    CreateWaterFlowItems(37);
    auto secObj = pattern_->GetOrCreateWaterFlowSections();
    secObj->ChangeData(0, 0, SECTION_7);
    MockPipelineContext::GetCurrent()->FlushBuildFinishCallbacks();
    CreateDone();

    UpdateCurrentOffset(-300.0f);
    EXPECT_EQ(info_->startIndex_, 2);
    EXPECT_EQ(info_->storedOffset_, -95);

    // relative offset to the first item should remain constant
    secObj->ChangeData(0, 4, SECTION_7);
    MockPipelineContext::GetCurrent()->FlushBuildFinishCallbacks();
    FlushUITasks();

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
    CreateWaterFlow();
    ViewAbstract::SetWidth(CalcLength(400.0f));
    ViewAbstract::SetHeight(CalcLength(600.f));
    CreateWaterFlowItems(37);
    auto secObj = pattern_->GetOrCreateWaterFlowSections();
    secObj->ChangeData(0, 0, SECTION_7);
    MockPipelineContext::GetCurrent()->FlushBuildFinishCallbacks();
    CreateDone();

    pattern_->isAnimationStop_ = false; // manually set to prevent jumping
    UpdateCurrentOffset(-2000.0f);
    EXPECT_EQ(info_->startIndex_, 20);
    EXPECT_EQ(info_->endIndex_, 26);

    AddItems(10);
    frameNode_->ChildrenUpdatedFrom(37);
    std::vector<WaterFlowSections::Section> newSection { SECTION_7[3] };
    newSection[0].itemsCount = 40;
    secObj->ChangeData(3, 1, newSection);
    pattern_->BeforeCreateLayoutWrapper();
    MockPipelineContext::GetCurrent()->FlushBuildFinishCallbacks();
    EXPECT_EQ(info_->segmentTails_.size(), 4);
    EXPECT_EQ(info_->segmentTails_[3], 46);

    FlushUITasks();
    EXPECT_EQ(info_->startIndex_, 20);
    EXPECT_EQ(GetChildY(frameNode_, 20), -53.0f);

    AddItems(7);
    frameNode_->ChildrenUpdatedFrom(7);
    secObj->ChangeData(1, 1, ADD_SECTION_7);
    pattern_->BeforeCreateLayoutWrapper();
    MockPipelineContext::GetCurrent()->FlushBuildFinishCallbacks();
    EXPECT_EQ(info_->segmentTails_[1], 13);
    FlushUITasks();
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
    CreateWaterFlow();
    ViewAbstract::SetWidth(CalcLength(400.0f));
    ViewAbstract::SetHeight(CalcLength(600.f));
    CreateWaterFlowItems(6);
    auto secObj = pattern_->GetOrCreateWaterFlowSections();
    secObj->ChangeData(0, 0, SECTION_9);
    MockPipelineContext::GetCurrent()->FlushBuildFinishCallbacks();
    CreateDone();

    AddItems(100);
    frameNode_->ChildrenUpdatedFrom(6);
    std::vector<WaterFlowSections::Section> newSection { SECTION_9[0] };
    newSection[0].itemsCount = 106;
    secObj->ChangeData(0, 1, newSection);
    pattern_->BeforeCreateLayoutWrapper();
    MockPipelineContext::GetCurrent()->FlushBuildFinishCallbacks();
    EXPECT_EQ(info_->segmentTails_.size(), 1);
    EXPECT_EQ(info_->segmentTails_[0], 105);

    FlushUITasks();
    EXPECT_EQ(info_->endIndex_, 17);
    UpdateCurrentOffset(-10000.0f);
    for (int i = 0; i < 100; ++i) {
        frameNode_->RemoveChildAtIndex(10);
        pattern_->NotifyDataChange(10, -1);
    }
    frameNode_->ChildrenUpdatedFrom(10);
    newSection[0].itemsCount = 10;
    secObj->ChangeData(0, 1, newSection);
    pattern_->BeforeCreateLayoutWrapper();
    MockPipelineContext::GetCurrent()->FlushBuildFinishCallbacks();
    EXPECT_EQ(info_->segmentTails_[0], 9);
    FlushUITasks();
    // Misalign, need align in the next frame.
    FlushUITasks();
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
    CreateWaterFlow();
    ViewAbstract::SetWidth(CalcLength(400.0f));
    ViewAbstract::SetHeight(CalcLength(600.f));
    CreateWaterFlowItems(37);
    auto secObj = pattern_->GetOrCreateWaterFlowSections();
    secObj->ChangeData(0, 0, SECTION_7);
    MockPipelineContext::GetCurrent()->FlushBuildFinishCallbacks();
    CreateDone();

    pattern_->isAnimationStop_ = false; // manually set to prevent jumping
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
    pattern_->BeforeCreateLayoutWrapper();
    EXPECT_EQ(info_->segmentTails_.size(), 4);
    EXPECT_EQ(info_->segmentTails_[2], 16);

    FlushUITasks();
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
    CreateWaterFlow();
    ViewAbstract::SetWidth(CalcLength(400.0f));
    ViewAbstract::SetHeight(CalcLength(600.f));
    CreateWaterFlowItems(37);
    auto secObj = pattern_->GetOrCreateWaterFlowSections();
    secObj->ChangeData(0, 0, SECTION_7);
    MockPipelineContext::GetCurrent()->FlushBuildFinishCallbacks();
    CreateDone();

    pattern_->isAnimationStop_ = false; // manually set to prevent jumping
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

    FlushUITasks();
    EXPECT_TRUE(info_->startIndex_ > info_->endIndex_);

    secObj->ChangeData(0, 1, SECTION_9);
    AddItems(6);
    frameNode_->ChildrenUpdatedFrom(0);
    MockPipelineContext::GetCurrent()->FlushBuildFinishCallbacks();
    FlushUITasks();
    EXPECT_EQ(info_->endIndex_, 5);
    EXPECT_EQ(GetChildY(frameNode_, 0), 0.0f);
}

/**
 * @tc.name: InsertAndJump001
 * @tc.desc: insert data at top and jump to other index
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowSegmentCommonTest, InsertAndJump001, TestSize.Level1)
{
    CreateWaterFlow();
    ViewAbstract::SetWidth(CalcLength(400.0f));
    ViewAbstract::SetHeight(CalcLength(600.f));
    CreateWaterFlowItems(37);
    auto secObj = pattern_->GetOrCreateWaterFlowSections();
    secObj->ChangeData(0, 0, SECTION_7);
    CreateDone();

    ScrollToIndex(10, false, ScrollAlign::START);
    EXPECT_EQ(GetChildY(frameNode_, 10), 0.0f);

    AddItemsAtSlot(2, 100.0f, 4);
    secObj->ChangeData(0, 1, SECTION_9);
    frameNode_->ChildrenUpdatedFrom(4);
    info_->NotifyDataChange(4, 2);
    ScrollToIndex(12, false, ScrollAlign::START, 20.0f);
    EXPECT_EQ(GetChildY(frameNode_, 12), -20.0f);
}

/**
 * @tc.name: ChangeHeight001
 * @tc.desc: Change height of items without notifying WaterFlow
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowSegmentCommonTest, ChangeHeight001, TestSize.Level1)
{
    CreateWaterFlow();
    ViewAbstract::SetWidth(CalcLength(400.0f));
    ViewAbstract::SetHeight(CalcLength(600.f));
    CreateWaterFlowItems(37);
    auto secObj = pattern_->GetOrCreateWaterFlowSections();
    auto sections = SECTION_7;
    sections[3].onGetItemMainSizeByIndex = nullptr;
    secObj->ChangeData(0, 0, sections);

    MockPipelineContext::GetCurrent()->FlushBuildFinishCallbacks();
    CreateDone();

    pattern_->isAnimationStop_ = false; // manually set to prevent jumping
    UpdateCurrentOffset(-1900.0f);
    EXPECT_EQ(info_->startIndex_, 15);

    auto item = GetChildFrameNode(frameNode_, 14);
    item->GetLayoutProperty()->UpdateUserDefinedIdealSize(CalcSize(CalcLength(100.0f), CalcLength(Dimension(300.0f))));

    UpdateCurrentOffset(100.0f);
    EXPECT_EQ(GetChildY(frameNode_, 15) - GetChildY(frameNode_, 14), 302.0f);
    EXPECT_EQ(GetChildRect(frameNode_, 14).Height(), 300.0f);
}

/**
 * @tc.name: ChangeHeight002
 * @tc.desc: Change height of items without notifying WaterFlow
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowSegmentCommonTest, ChangeHeight002, TestSize.Level1)
{
    CreateWaterFlow();
    ViewAbstract::SetWidth(CalcLength(400.0f));
    ViewAbstract::SetHeight(CalcLength(600.f));
    CreateWaterFlowItems(37);
    auto secObj = pattern_->GetOrCreateWaterFlowSections();
    auto sections = SECTION_7;
    sections[3].onGetItemMainSizeByIndex = nullptr;
    secObj->ChangeData(0, 0, sections);
    CreateDone();

    pattern_->isAnimationStop_ = false; // manually set to prevent jumping
    UpdateCurrentOffset(-1900.0f);
    EXPECT_EQ(info_->startIndex_, 15);
    EXPECT_EQ(GetChildY(frameNode_, 17), 241.0f);

    auto item = GetChildFrameNode(frameNode_, 16);
    item->GetLayoutProperty()->UpdateUserDefinedIdealSize(CalcSize(CalcLength(100.0f), CalcLength(Dimension(300.0f))));
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_BY_CHILD_REQUEST);

    FlushUITasks();
    EXPECT_EQ(GetChildRect(frameNode_, 16).Height(), 300.0f);
    EXPECT_EQ(GetChildY(frameNode_, 17), 441.0f);
}

/**
 * @tc.name: ChangeHeight003
 * @tc.desc: Change height of items while changing next section
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowSegmentCommonTest, ChangeHeight003, TestSize.Level1)
{
    CreateWaterFlow();
    ViewAbstract::SetWidth(CalcLength(400.0f));
    ViewAbstract::SetHeight(CalcLength(600.f));
    CreateWaterFlowItems(45);
    auto secObj = pattern_->GetOrCreateWaterFlowSections();
    auto sections = SECTION_10;
    secObj->ChangeData(0, 0, SECTION_10);
    CreateDone();

    EXPECT_EQ(GetChildHeight(frameNode_, 1), 200.0f);
    EXPECT_EQ(GetChildY(frameNode_, 3), 213.0f);

    secObj->ChangeData(1, 1,
        { {
            .itemsCount = 2,
            .crossCount = 1,
        } });
    GetChildLayoutProperty<LayoutProperty>(frameNode_, 1)
        ->UpdateUserDefinedIdealSize(CalcSize(CalcLength(100.0f), CalcLength(Dimension(300.0f))));
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_BY_CHILD_REQUEST);
    FlushUITasks();

    EXPECT_EQ(GetChildY(frameNode_, 3), 308.0f);
    EXPECT_EQ(GetChildY(frameNode_, 4), 508.0f);
    EXPECT_EQ(GetChildHeight(frameNode_, 1), 300.0f);
}

/**
 * @tc.name: Reset005
 * @tc.desc: Test Changing cross gap.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowSegmentCommonTest, Reset005, TestSize.Level1)
{
    WaterFlowModelNG model = CreateWaterFlow();
    model.SetColumnsTemplate("1fr 1fr 1fr 1fr");
    model.SetColumnsGap(Dimension(5.0f));
    model.SetRowsGap(Dimension(1.0f));
    CreateWaterFlowItems(200);
    CreateDone();
    EXPECT_EQ(info_->startIndex_, 0);
    EXPECT_EQ(info_->endIndex_, 21);
    for (int i = 0; i <= 21; ++i) {
        EXPECT_EQ(GetChildWidth(frameNode_, i), 116.25f);
    }

    layoutProperty_->UpdateColumnsGap(Dimension(1.0f));
    FlushUITasks();
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
    CreateWaterFlow();
    ViewAbstract::SetWidth(CalcLength(400.0f));
    ViewAbstract::SetHeight(CalcLength(600.f));
    CreateWaterFlowItems(37);
    auto secObj = pattern_->GetOrCreateWaterFlowSections();
    secObj->ChangeData(0, 0, SECTION_7);
    MockPipelineContext::GetCurrent()->FlushBuildFinishCallbacks();
    CreateDone();

    EXPECT_EQ(*info_->margins_[0].top, 5.0f);
    EXPECT_EQ(GetChildY(frameNode_, 0), 5.0f);
    EXPECT_EQ(GetChildY(frameNode_, 4), 408.0f);

    UpdateCurrentOffset(-600.0f);

    EXPECT_EQ(GetChildY(frameNode_, 6), -92.0f);
    EXPECT_EQ(GetChildY(frameNode_, 7), 21.0f);
    EXPECT_EQ(info_->startIndex_, 6);

    layoutProperty_->UpdateRowsGap(10.0_vp);
    FlushUITasks();
    EXPECT_EQ(info_->startIndex_, 6);

    UpdateCurrentOffset(600.0f);
    EXPECT_EQ(info_->startIndex_, 0);
    layoutProperty_->UpdateRowsGap(11.0_vp);
    FlushUITasks();
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
    CreateWaterFlow();
    ViewAbstract::SetWidth(CalcLength(400.0f));
    ViewAbstract::SetHeight(CalcLength(600.f));
    CreateWaterFlowItems(60);
    auto secObj = pattern_->GetOrCreateWaterFlowSections();
    secObj->ChangeData(0, 0, SECTION_4);
    MockPipelineContext::GetCurrent()->FlushBuildFinishCallbacks();
    CreateDone();
    EXPECT_TRUE(IsEqual(pattern_->GetItemRect(0), Rect(0, 0, 400.0f / 3, 100)));
    EXPECT_TRUE(IsEqual(pattern_->GetItemRect(2), Rect(400.0f / 3 * 2, 0, 400.0f / 3, 100)));

    layoutProperty_->UpdateLayoutDirection(TextDirection::RTL);
    FlushUITasks();
    EXPECT_TRUE(IsEqual(pattern_->GetItemRect(0), Rect(400.0f / 3 * 2, 0, 400.0f / 3, 100)));
    EXPECT_TRUE(IsEqual(pattern_->GetItemRect(2), Rect(0, 0, 400.0f / 3, 100)));
}

/**
 * @tc.name: Segmented008
 * @tc.desc: It should be dirty after change Section.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowSegmentCommonTest, Segmented008, TestSize.Level1)
{
    CreateWaterFlow();
    ViewAbstract::SetWidth(CalcLength(400.0f));
    ViewAbstract::SetHeight(CalcLength(600.f));
    CreateWaterFlowItems(60);
    CreateDone();
    // after measure, PropertyChangeFlag should be reset to 0.
    EXPECT_EQ(layoutProperty_->GetPropertyChangeFlag(), NG::PROPERTY_UPDATE_NORMAL);
    auto secObj = pattern_->GetOrCreateWaterFlowSections();
    secObj->ChangeData(0, 0, SECTION_4);
    // after change section, PropertyChangeFlag should be dirty.
    EXPECT_EQ(layoutProperty_->GetPropertyChangeFlag(), NG::PROPERTY_UPDATE_MEASURE_SELF);
    FlushUITasks();

    EXPECT_EQ(layoutProperty_->GetPropertyChangeFlag(), NG::PROPERTY_UPDATE_NORMAL);
    std::vector<WaterFlowSections::Section> newSection = { WaterFlowSections::Section {
        .itemsCount = 10, .onGetItemMainSizeByIndex = GET_MAIN_SIZE_FUNC, .crossCount = 5, .margin = MARGIN_1 } };
    secObj->ChangeData(1, 1, newSection);
    EXPECT_EQ(layoutProperty_->GetPropertyChangeFlag(), NG::PROPERTY_UPDATE_MEASURE_SELF);
}

/**
 * @tc.name: CheckHeight001
 * @tc.desc: Layout WaterFlow and check if callback height is used
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowSegmentCommonTest, CheckHeight001, TestSize.Level1)
{
    CreateWaterFlow();
    ViewAbstract::SetWidth(CalcLength(400.0f));
    ViewAbstract::SetHeight(CalcLength(600.f));
    CreateWaterFlowItems(37);
    auto secObj = pattern_->GetOrCreateWaterFlowSections();
    secObj->ChangeData(0, 0, SECTION_7);
    MockPipelineContext::GetCurrent()->FlushBuildFinishCallbacks();
    CreateDone();
    EXPECT_EQ(info_->startIndex_, 0);
    EXPECT_EQ(info_->endIndex_, 6);
    EXPECT_EQ(GetChildY(frameNode_, 6), 508.0f);

    pattern_->isAnimationStop_ = false; // manually set to prevent jumping
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
    CreateWaterFlow();
    ViewAbstract::SetWidth(CalcLength(400.0f));
    ViewAbstract::SetHeight(CalcLength(600.f));
    CreateWaterFlowItems(37);
    auto secObj = pattern_->GetOrCreateWaterFlowSections();
    secObj->ChangeData(0, 0, SECTION_7);
    MockPipelineContext::GetCurrent()->FlushBuildFinishCallbacks();
    CreateDone();
    ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, false);
    EXPECT_EQ(GetChildY(frameNode_, 36), 500.0f);

    ScrollToEdge(ScrollEdgeType::SCROLL_TOP, false);
    EXPECT_EQ(GetChildY(frameNode_, 0), 0.0f);
}

/**
 * @tc.name: Constraint001
 * @tc.desc: Test Layout when the layoutConstraint changes.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowSegmentCommonTest, Constraint001, TestSize.Level1)
{
    CreateWaterFlow();
    ViewAbstract::SetWidth(CalcLength(400.0f));
    ViewAbstract::SetHeight(CalcLength(600.f));
    CreateWaterFlowItems(60);
    auto secObj = pattern_->GetOrCreateWaterFlowSections();
    secObj->ChangeData(0, 0, SECTION_5);
    MockPipelineContext::GetCurrent()->FlushBuildFinishCallbacks();
    CreateDone();

    EXPECT_EQ(info_->startIndex_, 0);
    EXPECT_EQ(info_->endIndex_, 10);
    EXPECT_TRUE(IsEqual(pattern_->GetItemRect(0), Rect(0, 0, 400.f / 3, 100)));

    layoutProperty_->UpdateUserDefinedIdealSize(CalcSize(CalcLength(500.0f), CalcLength(Dimension(600.0f))));
    FlushUITasks();
    for (int i = 0; i < 5; i++) {
        EXPECT_EQ(GetChildWidth(frameNode_, i), 500.f / 3);
    }
    for (int i = 5; i < 10; i++) {
        EXPECT_EQ(GetChildWidth(frameNode_, i), (500.f - 8.0f) / 5);
    }
    EXPECT_EQ(GetChildX(frameNode_, 5), 5.0f);
    EXPECT_EQ(GetChildWidth(frameNode_, 10), 500.f);
    EXPECT_EQ(info_->endIndex_, 10);

    layoutProperty_->UpdateUserDefinedIdealSize(CalcSize(CalcLength(400.0f), CalcLength(Dimension(700.0f))));
    FlushUITasks();
    EXPECT_TRUE(IsEqual(pattern_->GetItemRect(0), Rect(0, 0, 400.f / 3, 100)));
    EXPECT_EQ(info_->endIndex_, 11);

    layoutProperty_->UpdateUserDefinedIdealSize(CalcSize(CalcLength(500.0f), CalcLength(Dimension(700.0f))));
    FlushUITasks();
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
    CreateWaterFlow();
    ViewAbstract::SetWidth(CalcLength(400.0f));
    ViewAbstract::SetHeight(CalcLength(400.f));
    CreateRandomWaterFlowItems(45);
    auto secObj = pattern_->GetOrCreateWaterFlowSections();
    secObj->ChangeData(0, 0, SECTION_10);
    MockPipelineContext::GetCurrent()->FlushBuildFinishCallbacks();
    CreateDone();

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
    FlushUITasks();
    EXPECT_EQ(info_->startIndex_, 3);
    EXPECT_EQ(info_->endIndex_, endIdx);

    UpdateCurrentOffset(4.0f);
    EXPECT_EQ(info_->startIndex_, 3);

    UpdateCurrentOffset(5.0f);
    EXPECT_LT(info_->startIndex_, 3);
    EXPECT_LE(info_->endIndex_, endIdx);
}

/**
 * @tc.name: Spring001
 * @tc.desc: Test spring bounce-back offset.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowSegmentCommonTest, Spring001, TestSize.Level1)
{
    WaterFlowModelNG model = CreateWaterFlow();
    ViewAbstract::SetWidth(CalcLength(400.0f));
    ViewAbstract::SetHeight(CalcLength(400.f));
    model.SetEdgeEffect(EdgeEffect::SPRING, true);
    CreateRandomWaterFlowItems(37);
    auto secObj = pattern_->GetOrCreateWaterFlowSections();
    secObj->ChangeData(0, 0, SECTION_7);
    MockPipelineContext::GetCurrent()->FlushBuildFinishCallbacks();
    CreateDone();
    EXPECT_EQ(GetChildY(frameNode_, 0), 5.0f);
    pattern_->SetAnimateCanOverScroll(true);

    UpdateCurrentOffset(10.0f);
    EXPECT_FLOAT_EQ(GetChildY(frameNode_, 0), 14.5485096f); // friction is applied on delta
    const auto& info = pattern_->layoutInfo_;
    EXPECT_FLOAT_EQ(info->TopFinalPos() - info->CurrentPos(), -9.54851f);

    UpdateCurrentOffset(-10.0f);
    ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, false);
    EXPECT_EQ(GetChildRect(frameNode_, 36).Bottom(), 400.0f);
    UpdateCurrentOffset(-10.0f);
    EXPECT_EQ(GetChildRect(frameNode_, 36).Bottom(), 390.0f);
    EXPECT_EQ(info->BottomFinalPos(400.0f) - info->CurrentPos(), 7.0f);
}

/**
 * @tc.name: Illegal003
 * @tc.desc: Layout WaterFlow without items.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowSegmentCommonTest, Illegal003, TestSize.Level1)
{
    CreateWaterFlow();
    ViewAbstract::SetWidth(CalcLength(400.0f));
    ViewAbstract::SetHeight(CalcLength(600.f));
    CreateWaterFlowItems(6);
    auto secObj = pattern_->GetOrCreateWaterFlowSections();
    secObj->ChangeData(0, 0, SECTION_9);
    MockPipelineContext::GetCurrent()->FlushBuildFinishCallbacks();
    CreateDone();
    EXPECT_EQ(info_->endIndex_, 5);

    auto newSection = SECTION_8;
    newSection[0].itemsCount = 0;
    secObj->ChangeData(0, 1, newSection);
    for (int i = 0; i < 10; ++i) {
        frameNode_->RemoveChildAtIndex(0);
    }
    frameNode_->ChildrenUpdatedFrom(0);
    MockPipelineContext::GetCurrent()->FlushBuildFinishCallbacks();
    FlushUITasks();
    pattern_->ScrollToIndex(LAST_ITEM);
    EXPECT_EQ(info_->jumpIndex_, LAST_ITEM);
    FlushUITasks();
    EXPECT_EQ(info_->endIndex_, -1);
    EXPECT_GT(info_->startIndex_, info_->endIndex_);
}

/**
 * @tc.name: Illegal004
 * @tc.desc: Recover section will layout at original currentOffset_.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowSegmentCommonTest, Illegal004, TestSize.Level1)
{
    CreateWaterFlow();
    ViewAbstract::SetWidth(CalcLength(400.0f));
    ViewAbstract::SetHeight(CalcLength(600.f));
    CreateWaterFlowItems(45);
    auto secObj = pattern_->GetOrCreateWaterFlowSections();
    secObj->ChangeData(0, 0, SECTION_10);
    CreateDone();
    auto info = pattern_->layoutInfo_;

    UpdateCurrentOffset(-300.0f);
    EXPECT_EQ(info->startIndex_, 3);
    EXPECT_EQ(info->endIndex_, 12);

    /**
     * @tc.steps: step1. update [sections_] with mismatching section.
     * @tc.expected: stop layout, currentOffset_ is unchanged.
     */
    std::vector<WaterFlowSections::Section> newSection = { WaterFlowSections::Section {
        .itemsCount = 1, .onGetItemMainSizeByIndex = GET_MAIN_SIZE_FUNC, .crossCount = 1, .margin = MARGIN_1 } };
    secObj->ChangeData(0, 0, newSection);
    FlushUITasks();

    EXPECT_EQ(info->startIndex_, 3);
    EXPECT_EQ(info->endIndex_, 12);

    /**
     * @tc.steps: step2. recover [sections_].
     * @tc.expected: layout at original currentOffset_.
     */
    AddItems(1);
    FlushUITasks();
#ifdef TEST_WATER_FLOW_SW
    EXPECT_EQ(info->startIndex_, 0);
    EXPECT_EQ(info->endIndex_, 8);
#else
    EXPECT_EQ(info->startIndex_, 1);
    EXPECT_EQ(info->endIndex_, 10);
#endif
}

/**
 * @tc.name: overScroll001
 * @tc.desc: Layout WaterFlow with top margin and check overScroll
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowSegmentCommonTest, overScroll001, TestSize.Level1)
{
    CreateWaterFlow();
    ViewAbstract::SetWidth(CalcLength(400.0f));
    ViewAbstract::SetHeight(CalcLength(600.f));
    CreateWaterFlowItems(37);
    auto secObj = pattern_->GetOrCreateWaterFlowSections();
    secObj->ChangeData(0, 0, SECTION_7);
    MockPipelineContext::GetCurrent()->FlushBuildFinishCallbacks();
    CreateDone();

    auto info = pattern_->layoutInfo_;

    EXPECT_EQ(GetChildY(frameNode_, 0), 5.0f);
    UpdateCurrentOffset(-2.0f);
    EXPECT_EQ(GetChildY(frameNode_, 0), 3.0f);
    EXPECT_FALSE(info->itemStart_);
    UpdateCurrentOffset(3.0f);
    EXPECT_EQ(GetChildY(frameNode_, 0), 5.0f);
    EXPECT_TRUE(info->itemStart_);

    ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, false);
    EXPECT_EQ(GetChildY(frameNode_, 36), 500.0f);
    EXPECT_FALSE(info->offsetEnd_);
    UpdateCurrentOffset(-4.0f);
    EXPECT_EQ(GetChildY(frameNode_, 36), 497.0f);
    EXPECT_TRUE(info->offsetEnd_);
}

/**
 * @tc.name: ReachStart001
 * @tc.desc: Test onReachStart
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowSegmentCommonTest, ReachStart001, TestSize.Level1)
{
    auto model = CreateWaterFlow();
    ViewAbstract::SetWidth(CalcLength(400.0f));
    ViewAbstract::SetHeight(CalcLength(600.f));
    CreateWaterFlowItems(37);
    bool reached = false;
    model.SetOnReachStart([&reached]() { reached = true; });
    auto secObj = pattern_->GetOrCreateWaterFlowSections();
    secObj->ChangeData(0, 0, SECTION_7);
    MockPipelineContext::GetCurrent()->FlushBuildFinishCallbacks();
    CreateDone();

    auto info = pattern_->layoutInfo_;

    UpdateCurrentOffset(-2.0f);
    UpdateCurrentOffset(3.0f);
    EXPECT_TRUE(reached);

    reached = false;
    ScrollToIndex(36, false, ScrollAlign::START);
    pattern_->isAnimationStop_ = false;
    UpdateCurrentOffset(Infinity<float>());
    EXPECT_TRUE(reached);
}

/**
 * @tc.name: Cache001
 * @tc.desc: Layout WaterFlow cache items
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowSegmentCommonTest, Cache001, TestSize.Level1)
{
    auto model = CreateWaterFlow();
    CreateItemsInRepeat(30, [](int32_t i) { return 100.0f; });
    model.SetCachedCount(3);
    model.SetRowsGap(Dimension(10));
    model.SetColumnsGap(Dimension(10));
    CreateDone();
    auto secObj = pattern_->GetOrCreateWaterFlowSections();
    secObj->ChangeData(0, 0, SECTION_12);
    FlushUITasks();
    EXPECT_EQ(info_->startIndex_, 0);
    EXPECT_EQ(info_->endIndex_, 7);
    EXPECT_FALSE(GetChildFrameNode(frameNode_, 10));
    const std::list<int32_t> preloadList = { 8, 9, 10 };
    EXPECT_EQ(pattern_->preloadItems_, preloadList);
    PipelineContext::GetCurrentContext()->OnIdle(INT64_MAX);
    ASSERT_TRUE(GetChildFrameNode(frameNode_, 8));
    ASSERT_TRUE(GetChildFrameNode(frameNode_, 9));
    ASSERT_TRUE(GetChildFrameNode(frameNode_, 10));
    EXPECT_EQ(GetChildWidth(frameNode_, 10), 111.5f);
    FlushUITasks();
    EXPECT_EQ(GetChildY(frameNode_, 8), 842.0f);
    EXPECT_EQ(GetChildY(frameNode_, 9), 944.0f);
    EXPECT_EQ(GetChildY(frameNode_, 10), 1154.0f);

    pattern_->isAnimationStop_ = false; // manually set to prevent jumping
    UpdateCurrentOffset(-2000.0f);
    EXPECT_EQ(info_->startIndex_, 15);
    EXPECT_EQ(info_->endIndex_, 29);
    EXPECT_TRUE(pattern_->preloadItems_.empty());
    PipelineContext::GetCurrentContext()->OnIdle(INT64_MAX);
    EXPECT_EQ(GetChildY(frameNode_, 12), -227.0f);
    EXPECT_EQ(GetChildY(frameNode_, 13), -227.0f);
    EXPECT_EQ(GetChildY(frameNode_, 14), -125.0f);
}

/**
 * @tc.name: ShowCachedItems001
 * @tc.desc: Test show cached items
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowSegmentCommonTest, ShowCachedItems001, TestSize.Level1)
{
    auto model = CreateWaterFlow();
    CreateItemsInRepeat(30, [](int32_t i) { return 100.0f; });
    model.SetCachedCount(3, true);
    model.SetRowsGap(Dimension(10));
    model.SetColumnsGap(Dimension(10));
    CreateDone();
    EXPECT_EQ(GetChildWidth(frameNode_, 3), 480.0f);
    auto secObj = pattern_->GetOrCreateWaterFlowSections();
    secObj->ChangeData(0, 0, SECTION_12);
    FlushUITasks();
    EXPECT_EQ(GetChildWidth(frameNode_, 3), 235.5f);
    EXPECT_EQ(info_->startIndex_, 0);
    EXPECT_EQ(info_->endIndex_, 7);
    ASSERT_TRUE(GetChildFrameNode(frameNode_, 8));
    ASSERT_TRUE(GetChildFrameNode(frameNode_, 9));
    ASSERT_TRUE(GetChildFrameNode(frameNode_, 10));
    EXPECT_EQ(GetChildWidth(frameNode_, 6), 233.0f);
    EXPECT_EQ(GetChildWidth(frameNode_, 8), 233.0f);
    EXPECT_EQ(GetChildWidth(frameNode_, 10), 111.5f);
    FlushUITasks();
    EXPECT_EQ(GetChildY(frameNode_, 8), 842.0f);
    EXPECT_EQ(GetChildY(frameNode_, 9), 944.0f);
    EXPECT_EQ(GetChildY(frameNode_, 10), 1154.0f);
    EXPECT_TRUE(GetChildFrameNode(frameNode_, 10)->IsActive());

    pattern_->isAnimationStop_ = false; // manually set to prevent jumping
    UpdateCurrentOffset(-2000.0f);
    EXPECT_EQ(info_->startIndex_, 15);
    EXPECT_EQ(info_->endIndex_, 29);
    EXPECT_TRUE(pattern_->preloadItems_.empty());
    EXPECT_EQ(GetChildY(frameNode_, 12), -227.0f);
    EXPECT_EQ(GetChildY(frameNode_, 13), -227.0f);
    EXPECT_EQ(GetChildY(frameNode_, 14), -125.0f);
    EXPECT_EQ(GetChildWidth(frameNode_, 14), 111.5f);
    EXPECT_TRUE(GetChildFrameNode(frameNode_, 12)->IsActive());
    EXPECT_TRUE(GetChildFrameNode(frameNode_, 13)->IsActive());
    EXPECT_TRUE(GetChildFrameNode(frameNode_, 14)->IsActive());
}

/**
 * @tc.name: SafeAreaExpand001
 * @tc.desc: Test onReachStart
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowSegmentCommonTest, SafeAreaExpand001, TestSize.Level1)
{
    auto model = CreateWaterFlow();
    ViewAbstract::SetWidth(CalcLength(400.0f));
    ViewAbstract::SetHeight(CalcLength(600.f));
    CreateWaterFlowItems(37);
    model.SetCachedCount(0);
    auto secObj = pattern_->GetOrCreateWaterFlowSections();
    secObj->ChangeData(0, 0, SECTION_7);
    CreateDone();

    EXPECT_EQ(pattern_->layoutInfo_->startIndex_, 0);
    EXPECT_EQ(pattern_->layoutInfo_->endIndex_, 6);
    EXPECT_EQ(GetChildHeight(frameNode_, 7), 0.0f);

    EXPECT_CALL(*MockPipelineContext::pipeline_, GetSafeArea)
        .Times(2)
        .WillRepeatedly(Return(SafeAreaInsets { {}, {}, {}, { .start = 0, .end = 100 } }));
    layoutProperty_->UpdateSafeAreaExpandOpts({ .type = SAFE_AREA_TYPE_SYSTEM, .edges = SAFE_AREA_EDGE_ALL });

    FlushUITasks();
    EXPECT_EQ(pattern_->layoutInfo_->startIndex_, 0);
    // When set SAFE_AREA_EDGE_BOTTOM, endIndex should become bigger.
    EXPECT_EQ(pattern_->layoutInfo_->endIndex_, 7);
    EXPECT_EQ(pattern_->layoutInfo_->expandHeight_, 100.0f);
    EXPECT_EQ(GetChildHeight(frameNode_, 7), 100.0f);
    EXPECT_TRUE(IsEqual(frameNode_->GetGeometryNode()->GetFrameRect(), RectF(0, 0, 400, 600)));

    ScrollToIndex(10, false, ScrollAlign::END);
    // scrollTo the last index with ScrollAlign::END, footer should be measured if set SAFE_AREA_EDGE_BOTTOM.
    EXPECT_EQ(pattern_->layoutInfo_->expandHeight_, 100.0f);
    EXPECT_EQ(pattern_->layoutInfo_->startIndex_, 4);
    EXPECT_EQ(pattern_->layoutInfo_->endIndex_, 11);
}

/**
 * @tc.name: ResetSection001
 * @tc.desc: update section then make sections null.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowSegmentCommonTest, ResetSection001, TestSize.Level1)
{
    auto model = CreateWaterFlow();
    CreateItemsInRepeat(30, [](int32_t i) { return 100.0f; });
    model.SetCachedCount(3);
    model.SetRowsGap(Dimension(10));
    model.SetColumnsGap(Dimension(10));
    CreateDone();
    auto secObj = pattern_->GetOrCreateWaterFlowSections();
    secObj->ChangeData(0, 0, SECTION_12);
    FlushUITasks();

    std::vector<WaterFlowSections::Section> newSection = { WaterFlowSections::Section {
        .itemsCount = 3, .onGetItemMainSizeByIndex = GET_MAIN_SIZE_FUNC, .crossCount = 1, .margin = MARGIN_1 } };
    secObj->ChangeData(0, 1, newSection);

    // set this.sections null, trigger ResetSections.
    pattern_->ResetSections();
    EXPECT_EQ(pattern_->sections_, nullptr);
    FlushUITasks();
}

/**
 * @tc.name: ReachEnd001
 * @tc.desc: Test ReachEnd when there has bottom margin in the last section.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowSegmentCommonTest, ReachEnd001, TestSize.Level1)
{
    auto model = CreateWaterFlow();
    CreateItemsInRepeat(30, [](int32_t i) { return 100.0f; });
    model.SetRowsGap(Dimension(10));
    model.SetColumnsGap(Dimension(10));
    bool reached = false;
    model.SetOnReachEnd([&reached]() { reached = true; });
    CreateDone();
    auto secObj = pattern_->GetOrCreateWaterFlowSections();
    secObj->ChangeData(0, 0, SECTION_12);
    FlushUITasks();

    UpdateCurrentOffset(-5000.0f);
    EXPECT_EQ(GetChildRect(frameNode_, 29).Bottom(), 795.0f);
    EXPECT_TRUE(reached);
    reached = false;

    UpdateCurrentOffset(2.0f);
    EXPECT_FALSE(reached);

    UpdateCurrentOffset(-2.0f);
    EXPECT_TRUE(reached);
}
} // namespace OHOS::Ace::NG
