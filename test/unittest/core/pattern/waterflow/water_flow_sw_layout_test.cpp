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

#include "test/mock/core/animation/mock_animation_manager.h"
#include "water_flow_item_maps.h"
#include "water_flow_test_ng.h"

#define private public
#include "core/components_ng/pattern/waterflow/layout/sliding_window/water_flow_layout_sw.h"
#undef private

#include "core/components_ng/pattern/refresh/refresh_model_ng.h"
#include "core/components_ng/pattern/waterflow/layout/sliding_window/water_flow_layout_info_sw.h"

namespace OHOS::Ace::NG {
class WaterFlowSWTest : public WaterFlowTestNg {
protected:
    void GetWaterFlow() override
    {
        WaterFlowTestNg::GetWaterFlow();
        info_ = AceType::DynamicCast<WaterFlowLayoutInfoSW>(pattern_->layoutInfo_);
        EXPECT_TRUE(info_);
    }

    RefPtr<WaterFlowLayoutInfoSW> info_;
};

/**
 * @tc.name: Regular001
 * @tc.desc: waterFlow with fixed column
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowSWTest, Regular001, TestSize.Level1)
{
    WaterFlowModelNG model = CreateWaterFlow();
    ViewAbstract::SetWidth(CalcLength(400.0f));
    ViewAbstract::SetHeight(CalcLength(200.f));
    model.SetColumnsTemplate("1fr 1fr 1fr");
    CreateWaterFlowItems();
    CreateDone();
    FlushUITasks();
    EXPECT_EQ(info_->lanes_[0][0].items_.size(), 2);
    EXPECT_EQ(info_->lanes_[0][0].items_.back().idx, 3);
    EXPECT_EQ(info_->lanes_[0][0].items_.back().mainSize, 200.0f);
    EXPECT_EQ(info_->lanes_[0][0].endPos, 300.0f);
    EXPECT_EQ(info_->lanes_[0][1].items_.back().idx, 1);
    EXPECT_EQ(info_->lanes_[0][1].endPos, 200.0f);
    EXPECT_EQ(info_->lanes_[0][2].endPos, 200.0f);
    EXPECT_EQ(info_->lanes_[0][2].items_.back().idx, 4);
    EXPECT_EQ(info_->startIndex_, 0);
    EXPECT_EQ(info_->endIndex_, 4);
}

/**
 * @tc.name: ScrollToEdge003
 * @tc.desc: Test ScrollToEdge func and layout footer
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowSWTest, ScrollToEdge003, TestSize.Level1)
{
    WaterFlowModelNG model = CreateWaterFlow();
    model.SetFooter(GetDefaultHeaderBuilder());
    model.SetColumnsTemplate("1fr");
    model.SetRowsGap(Dimension(5.0f));
    CreateRandomWaterFlowItems(100);
    CreateDone();
    ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, false);
    auto info = pattern_->layoutInfo_;
    EXPECT_EQ(info->endIndex_, 99);
    EXPECT_EQ(GetChildRect(frameNode_, 100).Bottom(), 750.0f);
    EXPECT_EQ(GetChildOffset(frameNode_, info->footerIndex_), OffsetF(0.0f, 750.0f));
    UpdateCurrentOffset(50.0f + GetChildRect(frameNode_, 100).Height() + 1.0f);
    EXPECT_FALSE(GetChildFrameNode(frameNode_, 0)->IsActive());
}

/**
 * @tc.name: Reset001
 * @tc.desc: waterFlow children update
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowSWTest, Reset001, TestSize.Level1)
{
    WaterFlowModelNG model = CreateWaterFlow();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetFooter(GetDefaultHeaderBuilder());
    CreateWaterFlowItems();
    CreateDone();
    ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, false);
    EXPECT_EQ(info_->startIndex_, 0);
    EXPECT_EQ(info_->endIndex_, 9);
    for (int i = 0; i < 5; i++) {
        frameNode_->RemoveChildAtIndex(6);
    }
    frameNode_->ChildrenUpdatedFrom(5); // footer not included in LazyForEach / ForEach
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    FlushUITasks();
    EXPECT_EQ(info_->startIndex_, 0);
    EXPECT_EQ(info_->endIndex_, 4);
    EXPECT_FALSE(info_->idxToLane_.count(5));
    EXPECT_EQ(GetChildY(frameNode_, 1), 0.0f);
    EXPECT_EQ(GetChildY(frameNode_, 5), 200.0f);
    EXPECT_EQ(GetChildY(frameNode_, 0), 400.0f);
}

/**
 * @tc.name: Reset002
 * @tc.desc: waterFlow children update before startIdx
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowSWTest, Reset002, TestSize.Level1)
{
    WaterFlowModelNG model = CreateWaterFlow();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetFooter(GetDefaultHeaderBuilder());
    CreateWaterFlowItems(100);
    CreateWaterFlowItems();
    CreateDone();
    ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, false);
    EXPECT_EQ(info_->startIndex_, 99);
    EXPECT_EQ(info_->endIndex_, 109);
    for (int i = 0; i < 5; i++) {
        frameNode_->RemoveChildAtIndex(6);
    }
    frameNode_->ChildrenUpdatedFrom(5); // footer not included in LazyForEach / ForEach
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    FlushUITasks();
    EXPECT_EQ(info_->startIndex_, 95);
    EXPECT_EQ(info_->endIndex_, 104);
    EXPECT_TRUE(info_->idxToLane_.find(1) == info_->idxToLane_.end());
    EXPECT_TRUE(info_->offsetEnd_);
    EXPECT_EQ(GetChildY(frameNode_, 96), -50.0f);
    EXPECT_EQ(GetChildY(frameNode_, 0), 750.0f);
    EXPECT_EQ(
        info_->lanes_[0][0].ToString(), "{StartPos: -50.000000 EndPos: 750.000000 Items [95 97 99 100 103 104 ] }");
    EXPECT_EQ(info_->lanes_[0][1].ToString(), "{StartPos: -150.000000 EndPos: 550.000000 Items [96 98 101 102 ] }");

    // delete start index
    frameNode_->RemoveChildAtIndex(96);
    frameNode_->ChildrenUpdatedFrom(95); // footer not included in LazyForEach / ForEach
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    FlushUITasks();
    EXPECT_EQ(info_->startIndex_, 94);
    EXPECT_EQ(info_->endIndex_, 103);
    EXPECT_TRUE(info_->offsetEnd_);
    EXPECT_EQ(GetChildY(frameNode_, 96), -50.0f);
    // triggered adjustOverScroll
    EXPECT_EQ(info_->lanes_[0][0].ToString(), "{StartPos: -150.000000 EndPos: 650.000000 Items [94 96 97 100 101 ] }");
    EXPECT_EQ(info_->lanes_[0][1].ToString(), "{StartPos: -50.000000 EndPos: 750.000000 Items [95 98 99 102 103 ] }");
}

/**
 * @tc.name: Jump001
 * @tc.desc: waterFlow jump
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowSWTest, Jump001, TestSize.Level1)
{
    WaterFlowModelNG model = CreateWaterFlow();
    ViewAbstract::SetWidth(CalcLength(400.0f));
    ViewAbstract::SetHeight(CalcLength(200.f));
    model.SetColumnsTemplate("1fr 1fr 1fr");
    CreateWaterFlowItems();
    CreateDone();
    ScrollToIndex(8, false, ScrollAlign::START);
    EXPECT_EQ(info_->startIndex_, 5);
    EXPECT_EQ(info_->endIndex_, 9);
    EXPECT_EQ(info_->idxToLane_.at(8), 2);
    EXPECT_EQ(info_->lanes_[0][0].endPos, 200.0f);
    EXPECT_EQ(info_->lanes_[0][1].startPos, -100.0f);
    EXPECT_EQ(info_->lanes_[0][1].endPos, 300.0f);
    EXPECT_EQ(info_->lanes_[0][2].endPos, 100.0f);
    EXPECT_EQ(info_->lanes_[0][0].items_.size(), 1);
    EXPECT_EQ(info_->lanes_[0][0].items_.front().idx, 7);
    EXPECT_EQ(info_->lanes_[0][1].items_.size(), 2);
    EXPECT_EQ(info_->lanes_[0][1].items_.front().idx, 5);
    EXPECT_EQ(info_->lanes_[0][1].items_.back().idx, 9);
    EXPECT_EQ(info_->lanes_[0][2].items_.size(), 2);
    EXPECT_TRUE(info_->itemEnd_);
    EXPECT_FALSE(info_->offsetEnd_);
    EXPECT_EQ(info_->startIndex_, 5);
    EXPECT_EQ(info_->endIndex_, 9);
}

/**
 * @tc.name: ChangeTemplate001
 * @tc.desc: waterFlow change lane count
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowSWTest, ChangeTemplate001, TestSize.Level1)
{
    WaterFlowModelNG model = CreateWaterFlow();
    ViewAbstract::SetWidth(CalcLength(600.0f));
    ViewAbstract::SetHeight(CalcLength(200.f));
    model.SetColumnsTemplate("1fr 1fr 1fr");
    CreateWaterFlowItems();
    CreateDone();
    UpdateCurrentOffset(-300.0f);
    EXPECT_EQ(info_->startIndex_, 5);
    EXPECT_EQ(info_->endIndex_, 9);
    EXPECT_EQ(GetChildOffset(frameNode_, 5), OffsetF(200.0f, -100.0f));
    EXPECT_EQ(GetChildOffset(frameNode_, 6), OffsetF(400.0f, -100.0f));
    EXPECT_EQ(GetChildOffset(frameNode_, 7), OffsetF(0.0f, 0.0f));
    EXPECT_EQ(GetChildOffset(frameNode_, 8), OffsetF(400.0f, 0.0f));
    EXPECT_EQ(GetChildOffset(frameNode_, 9), OffsetF(200.0f, 100.0f));
    layoutProperty_->UpdateColumnsTemplate("1fr 1fr");
    FlushUITasks();
    EXPECT_EQ(info_->startIndex_, 5);
    EXPECT_EQ(info_->endIndex_, 8);
    EXPECT_EQ(GetChildOffset(frameNode_, 5), OffsetF(0.0f, -100.0f));
    EXPECT_EQ(GetChildOffset(frameNode_, 6), OffsetF(300.0f, -100.0f));
    EXPECT_EQ(GetChildOffset(frameNode_, 7), OffsetF(300.0f, 0.0f));
    EXPECT_EQ(GetChildOffset(frameNode_, 8), OffsetF(0.0f, 100.0f));
}

/**
 * @tc.name: ModifyItem002
 * @tc.desc: Test WaterFlow reacting to child height change.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowSWTest, ModifyItem002, TestSize.Level1)
{
    WaterFlowModelNG model = CreateWaterFlow();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetFooter(GetDefaultHeaderBuilder());
    CreateWaterFlowItems(80);
    CreateDone();

    ScrollToIndex(50, false, ScrollAlign::CENTER);
    EXPECT_EQ(info_->startIndex_, 44);
    EXPECT_EQ(GetChildY(frameNode_, 45), -50.0f);
    EXPECT_EQ(GetChildY(frameNode_, 46), -100.0f);
    EXPECT_EQ(GetChildY(frameNode_, 51), 350.0f);
    auto child = GetChildFrameNode(frameNode_, 49);
    child->GetLayoutProperty()->UpdateUserDefinedIdealSize(CalcSize(std::nullopt, CalcLength(300.0)));
    child->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    FlushUITasks();
    EXPECT_EQ(GetChildHeight(frameNode_, 49), 300.0f);
    EXPECT_EQ(info_->startIndex_, 45);
    EXPECT_EQ(GetChildY(frameNode_, 45), -100.0f);
    EXPECT_EQ(GetChildY(frameNode_, 46), -50.0f);
    EXPECT_EQ(GetChildHeight(frameNode_, 49), 300.0f); // changed after refill

    child = GetChildFrameNode(frameNode_, 40);
    child->GetLayoutProperty()->UpdateUserDefinedIdealSize(CalcSize(std::nullopt, CalcLength(10.0)));
    child->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    FlushUITasks();
    EXPECT_EQ(info_->startIndex_, 45);
    EXPECT_EQ(GetChildY(frameNode_, 45), -100.0f);
    EXPECT_EQ(GetChildY(frameNode_, 46), -50.0f); // doesn't affect current layout
    UpdateCurrentOffset(500.0f);
    EXPECT_EQ(GetChildHeight(frameNode_, 40), 10.0f); // changed after refill

    // update footer
    ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, false);
    EXPECT_EQ(GetChildY(frameNode_, 80), 550.0f);
    EXPECT_EQ(info_->startIndex_, 69);
    EXPECT_EQ(GetChildY(frameNode_, 70), -150.0f);
    EXPECT_EQ(info_->lanes_[0][0].ToString(), "{StartPos: -150.000000 EndPos: 750.000000 Items [69 70 73 74 77 78 ] }");
    EXPECT_EQ(info_->lanes_[0][1].ToString(), "{StartPos: -50.000000 EndPos: 750.000000 Items [71 72 75 76 79 ] }");

    child = GetChildFrameNode(frameNode_, 0);
    child->GetLayoutProperty()->UpdateUserDefinedIdealSize(CalcSize(std::nullopt, CalcLength(1.0)));
    child->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    FlushUITasks();
    EXPECT_EQ(info_->lanes_[0][0].ToString(), "{StartPos: -101.000000 EndPos: 799.000000 Items [69 70 73 74 77 78 ] }");
    EXPECT_EQ(info_->lanes_[0][1].ToString(), "{StartPos: -1.000000 EndPos: 799.000000 Items [71 72 75 76 79 ] }");
    EXPECT_EQ(GetChildY(frameNode_, 0), 799.0f);
    EXPECT_TRUE(GetChildFrameNode(frameNode_, 0)->IsActive());
}

/**
 * @tc.name: Order001
 * @tc.desc: check fill order
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowSWTest, Order001, TestSize.Level1)
{
    WaterFlowModelNG model = CreateWaterFlow();
    ViewAbstract::SetWidth(CalcLength(400.0f));
    ViewAbstract::SetHeight(CalcLength(600.f));
    model.SetColumnsTemplate("1fr 1fr");
    model.SetRowsGap(Dimension(5.0f));
    model.SetColumnsGap(Dimension(5.0f));
    for (int i = 0; i < 30; ++i) {
        CreateItemWithHeight(100.0f);
    }
    CreateDone();
    AddItemsAtSlot(5, 100.0f, 3);
    frameNode_->ChildrenUpdatedFrom(3);
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    FlushUITasks();
    EXPECT_EQ(GetChildX(frameNode_, 3), (400.0f + 5.0f) / 2.0f);
    EXPECT_EQ(GetChildX(frameNode_, 4), 0.0f);
}

/**
 * @tc.name: Update001
 * @tc.desc: update section item count
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowSWTest, Update001, TestSize.Level1)
{
    CreateWaterFlow();
    ViewAbstract::SetWidth(CalcLength(400.0f));
    ViewAbstract::SetHeight(CalcLength(600.f));
    for (int i = 0; i < 35; ++i) {
        CreateItemWithHeight(100.0f);
    }
    auto secObj = pattern_->GetOrCreateWaterFlowSections();
    secObj->ChangeData(0, 0, SECTION_11);
    CreateDone();
    EXPECT_EQ(GetChildY(frameNode_, 3), 325.0f);

    /* Add 4 items at 3 */
    AddItemsAtSlot(4, 100.0f, 3);
    frameNode_->ChildrenUpdatedFrom(3);

    auto section = SECTION_11[1];
    section.itemsCount += 4;
    section.crossCount = 3;
    secObj->ChangeData(1, 1, { section });
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    FlushUITasks();
    EXPECT_EQ(GetChildY(frameNode_, 0), 5.0f);
    EXPECT_EQ(GetChildY(frameNode_, 3), 325.0f);
    EXPECT_EQ(GetChildY(frameNode_, 6), 430.0f);
    UpdateCurrentOffset(-365.0f);
    EXPECT_EQ(GetChildY(frameNode_, 3), -40.0f);
    EXPECT_EQ(GetChildY(frameNode_, 6), 65.0f);

    /* remove 4 items from 3 */
    section.itemsCount -= 4;
    section.crossCount = 2;
    secObj->ChangeData(1, 1, { section });
    for (int i = 0; i < 4; ++i) {
        frameNode_->RemoveChildAtIndex(3);
    }
    frameNode_->ChildrenUpdatedFrom(3);
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    FlushUITasks();
    EXPECT_EQ(GetChildY(frameNode_, 3), -40.0f);
    ScrollToEdge(ScrollEdgeType::SCROLL_TOP, false);

    EXPECT_EQ(GetChildY(frameNode_, 0), 0.0f);
    EXPECT_EQ(GetChildY(frameNode_, 3), 320.0f);
    EXPECT_EQ(info_->endIndex_, 6);
}

/**
 * @tc.name: OverScroll001
 * @tc.desc: Test overScroll past limits
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowSWTest, OverScroll001, TestSize.Level1)
{
    WaterFlowModelNG model = CreateWaterFlow();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetFooter(GetDefaultHeaderBuilder());
    model.SetEdgeEffect(EdgeEffect::SPRING, true);
    CreateWaterFlowItems(50);
    CreateDone();

    pattern_->SetAnimateCanOverScroll(true);
    for (int i = 0; i < 100; i++) {
        UpdateCurrentOffset(300000.0f);
    }
    const float startPos = info_->StartPos();
    EXPECT_GT(info_->StartPos(), 2000.0f);
    EXPECT_EQ(info_->startIndex_, 0);
    EXPECT_EQ(info_->endIndex_, 0);

    info_->delta_ = -50.0f;
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    FlushUITasks();
    EXPECT_EQ(info_->StartPos(), startPos - 50.0f);
    EXPECT_EQ(info_->startIndex_, 0);
    EXPECT_EQ(info_->endIndex_, 0);

    for (int i = 0; i < 100; i++) {
        UpdateCurrentOffset(-301200.0f);
    }
    EXPECT_EQ(info_->startIndex_, 12);
    EXPECT_EQ(info_->endIndex_, 22);
    EXPECT_EQ(info_->StartPos(), 0.0f);
    EXPECT_EQ(info_->EndPos(), 800.0f);
}

/**
 * @tc.name: OverScroll002
 * @tc.desc: Test overScroll past limits
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowSWTest, OverScroll002, TestSize.Level1)
{
    WaterFlowModelNG model = CreateWaterFlow();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetFooter(GetDefaultHeaderBuilder());
    model.SetEdgeEffect(EdgeEffect::SPRING, true);
    CreateWaterFlowItems(50);
    CreateDone();

    pattern_->SetAnimateCanOverScroll(true);
    ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, false);

    UpdateCurrentOffset(-900000.0f);
    const float endPos = info_->EndPos();
    EXPECT_LT(info_->EndPos(), -2000.0f);
    EXPECT_EQ(info_->startIndex_, 49);
    EXPECT_EQ(info_->endIndex_, 49);

    info_->delta_ = 30.0f;
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    FlushUITasks();
    EXPECT_EQ(info_->EndPos(), endPos + 30.0f);
    EXPECT_EQ(info_->startIndex_, 49);
    EXPECT_EQ(info_->endIndex_, 49);

    info_->delta_ = -30.0f;
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    FlushUITasks();
    EXPECT_EQ(info_->EndPos(), endPos);
    EXPECT_EQ(info_->startIndex_, 49);
    EXPECT_EQ(info_->endIndex_, 49);

    UpdateCurrentOffset(1010000.0f);
    EXPECT_EQ(info_->startIndex_, 32);
    EXPECT_EQ(info_->endIndex_, 42);
    EXPECT_EQ(info_->StartPos(), 0.0f);
    EXPECT_EQ(info_->EndPos(), 800.0f);
}

/**
 * @tc.name: OverScroll003
 * @tc.desc: Test overScroll past limits incrementally
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowSWTest, OverScroll003, TestSize.Level1)
{
    WaterFlowModelNG model = CreateWaterFlow();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetEdgeEffect(EdgeEffect::SPRING, true);
    model.SetRowsGap(Dimension(5.0f));
    CreateRandomWaterFlowItems(50);
    CreateDone();
    pattern_->SetAnimateCanOverScroll(true);
    for (int i = 1; i <= 10; ++i) {
        info_->delta_ = 100.0f;
        frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
        FlushUITasks();
        EXPECT_EQ(info_->StartPos(), 100.0f * i);
        EXPECT_TRUE(info_->itemStart_);
    }
    EXPECT_EQ(info_->startIndex_, 0);
    EXPECT_EQ(info_->endIndex_, 0);
    EXPECT_EQ(info_->TopFinalPos(), -1000.0f);
    for (auto& lane : info_->lanes_[0]) {
        if (lane.items_.empty()) {
            EXPECT_EQ(lane.startPos, lane.endPos);
        } else {
            EXPECT_EQ(lane.endPos - lane.startPos, GetChildHeight(frameNode_, 0));
        }
    }
}

/**
 * @tc.name: OverScroll004
 * @tc.desc: Test overScroll past limits incrementally
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowSWTest, OverScroll004, TestSize.Level1)
{
    WaterFlowModelNG model = CreateWaterFlow();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetEdgeEffect(EdgeEffect::SPRING, true);
    model.SetRowsGap(Dimension(5.0f));
    CreateRandomWaterFlowItems(50);
    CreateDone();
    pattern_->SetAnimateCanOverScroll(true);
    ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, false);
    for (int i = 1; i <= 10; ++i) {
        info_->delta_ = -100.0f;
        frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
        FlushUITasks();
        EXPECT_EQ(info_->EndPos(), -100.0f * i + WATER_FLOW_HEIGHT);
        EXPECT_TRUE(info_->offsetEnd_);
    }
    EXPECT_EQ(info_->startIndex_, 49);
    EXPECT_EQ(info_->endIndex_, 49);
    EXPECT_EQ(info_->BottomFinalPos(WATER_FLOW_HEIGHT), 1000.0f);
    for (auto& lane : info_->lanes_[0]) {
        if (lane.items_.empty()) {
            EXPECT_EQ(lane.startPos, lane.endPos);
        } else {
            EXPECT_EQ(lane.endPos - lane.startPos, GetChildHeight(frameNode_, 49));
        }
    }
}

/**
 * @tc.name: OverScroll004
 * @tc.desc: Test overScroll with content < WATERFLOW
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowSWTest, OverScroll005, TestSize.Level1)
{
    WaterFlowModelNG model = CreateWaterFlow();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetEdgeEffect(EdgeEffect::SPRING, true);
    model.SetFooter(GetDefaultHeaderBuilder());
    CreateWaterFlowItems(3);
    CreateDone();
    pattern_->SetAnimateCanOverScroll(true);
    info_->UpdateOffset(200.0f);
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    FlushUITasks();
    EXPECT_EQ(GetChildY(frameNode_, 1), 200.0f);
    EXPECT_EQ(info_->TopFinalPos(), -200.0f);

    info_->UpdateOffset(-300.0f);
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    FlushUITasks();
    EXPECT_EQ(GetChildY(frameNode_, 2), -100.0f);
    EXPECT_EQ(info_->maxHeight_, 250.0f);
    EXPECT_EQ(info_->BottomFinalPos(WATER_FLOW_HEIGHT), 100.0f);
}

/**
 * @tc.name: Misaligned001
 * @tc.desc: Test misalignment and adjustment
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowSWTest, Misaligned001, TestSize.Level1)
{
    WaterFlowModelNG model = CreateWaterFlow();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetFooter(GetDefaultHeaderBuilder());
    CreateWaterFlowItems(50);
    CreateDone();
    EXPECT_FALSE(info_->IsMisaligned());
    ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, false);

    ScrollToIndex(2, true, ScrollAlign::START);
    EXPECT_EQ(pattern_->GetFinalPosition() - pattern_->GetTotalOffset(), -2850.0f);
    UpdateCurrentOffset(2800.0f + 101.0f);
    // should mark misaligned
    EXPECT_EQ(info_->startIndex_, 0);
    EXPECT_EQ(GetChildY(frameNode_, 1), -49.0f);
    EXPECT_EQ(GetChildX(frameNode_, 1), 0.0f);
    UpdateCurrentOffset(2.0f);
    EXPECT_EQ(GetChildRect(frameNode_, 1).Bottom(), 53.0f);
    EXPECT_FALSE(info_->IsMisaligned());
    EXPECT_EQ(GetChildX(frameNode_, 1), 0.0f);
    EXPECT_EQ(info_->lanes_[0][0].startPos, -47.0f);
    EXPECT_EQ(info_->lanes_[0][0].items_.front().idx, 0);
    EXPECT_EQ(info_->Offset(), -47.0f);
}

/**
 * @tc.name: Misaligned002
 * @tc.desc: Test misalignment with section
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowSWTest, Misaligned002, TestSize.Level1)
{
    CreateWaterFlow();
    const std::vector<float> randomHeights = { 249, 228, 232, 171, 184, 168, 236, 167, 156, 163, 212, 50, 130, 225, 63,
        106, 156, 213, 102, 93, 73, 184, 89, 156, 178, 163, 176, 187, 191, 118, 218, 212, 196, 52, 103, 57, 189, 55,
        127, 230, 51, 167, 166, 118, 107 };
    for (const float& f : randomHeights) {
        CreateItemWithHeight(f);
    }
    auto secObj = pattern_->GetOrCreateWaterFlowSections();
    secObj->ChangeData(0, 0, SECTION_10);
    CreateDone();

    EXPECT_FALSE(info_->IsMisaligned());
    ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, false);
    ScrollToIndex(15, true, ScrollAlign::START);
    EXPECT_EQ(pattern_->GetFinalPosition() - pattern_->GetTotalOffset(), -575.0f);
    UpdateCurrentOffset(550.0f);

    EXPECT_EQ(GetChildY(frameNode_, 15), -25.0f);
    EXPECT_EQ(GetChildX(frameNode_, 15), 0.0f);
    EXPECT_EQ(GetChildY(frameNode_, 16), -62.0f);
    EXPECT_EQ(GetChildX(frameNode_, 16), 320.0f);
    EXPECT_EQ(GetChildY(frameNode_, 17), -96.0f);
    EXPECT_EQ(GetChildX(frameNode_, 17), 160.0f);
    EXPECT_EQ(info_->startIndex_, 15);
    EXPECT_TRUE(info_->IsMisaligned());

    UpdateCurrentOffset(100.0f);
    EXPECT_EQ(info_->startIndex_, 13);
    EXPECT_TRUE(info_->IsMisaligned());

    pattern_->OnScrollEndCallback(); // check misalignment onScrollEnd
    FlushUITasks();
    EXPECT_EQ(GetChildY(frameNode_, 15), 4.0f);
    EXPECT_EQ(GetChildX(frameNode_, 15), 0.0f);
    EXPECT_EQ(GetChildY(frameNode_, 16), 4.0f);
    EXPECT_EQ(GetChildX(frameNode_, 16), 160.0f);
    EXPECT_FALSE(info_->IsMisaligned());
}

/**
 * @tc.name: PositionController100
 * @tc.desc: Test PositionController AnimateTo and ScrollTo
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowSWTest, PositionController100, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create List Item
     */
    WaterFlowModelNG model = CreateWaterFlow();
    model.SetColumnsTemplate("1fr 1fr");
    CreateWaterFlowItems(TOTAL_LINE_NUMBER * 2);
    CreateDone();
    auto controller = pattern_->positionController_;
    /**
     * @tc.steps: step8. Test AnimateTo function
     */
    pattern_->AnimateTo(1.5, 1.f, Curves::LINEAR, false, false);
    EXPECT_FALSE(pattern_->isAnimationStop_);
    MockAnimationManager::GetInstance().Tick();
    FlushUITasks(frameNode_);
    EXPECT_EQ(pattern_->layoutInfo_->Offset(), -1.5);
    EXPECT_EQ(GetChildY(frameNode_, 0), -1.5);

    /**
     * @tc.steps: step8. test event
     */
    bool isOnWillScrollCallBack = false;
    Dimension willScrollOffset;
    ScrollState willScrollState;
    auto onWillScroll = [&willScrollOffset, &willScrollState, &isOnWillScrollCallBack](
                            Dimension offset, ScrollState state, ScrollSource source) {
        willScrollOffset = offset;
        willScrollState = state;
        isOnWillScrollCallBack = true;
        ScrollFrameResult result;
        result.offset = offset;
        return result;
    };

    eventHub_->SetOnWillScroll(std::move(onWillScroll));
    pattern_->ScrollTo(ITEM_MAIN_SIZE * 5);
    EXPECT_TRUE(isOnWillScrollCallBack);
    FlushUITasks(frameNode_);
    const auto &info = pattern_->layoutInfo_;
    EXPECT_EQ(info->Offset(), -ITEM_MAIN_SIZE * 5);
    EXPECT_EQ(info->startIndex_, 7);
    EXPECT_EQ(GetChildY(frameNode_, 7), 0);
}

/**
 * @tc.name: ScrollToEdge002
 * @tc.desc: ScrollToEdge and check overScroll
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowSWTest, ScrollToEdge002, TestSize.Level1)
{
    WaterFlowModelNG model = CreateWaterFlow();
    model.SetFooter(GetDefaultHeaderBuilder());
    model.SetColumnsTemplate("1fr 1fr 1fr");
    model.SetRowsGap(Dimension(5.0f));
    CreateRandomWaterFlowItems(100);
    CreateDone();
    ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, false);
    auto info = pattern_->layoutInfo_;
    EXPECT_EQ(info->endIndex_, 99);
    EXPECT_EQ(GetChildOffset(frameNode_, info->footerIndex_), OffsetF(0.0f, 750.0f));
    EXPECT_EQ(info_->EndPos(), 750.0f);
    EXPECT_FALSE(info->OutOfBounds());
    EXPECT_EQ(info->GetOverScrolledDelta(20.0f).end, 0.0f);
    EXPECT_EQ(info->GetOverScrolledDelta(-10.0f).end, -10.0f);

    UpdateCurrentOffset(30.0f);
    EXPECT_EQ(info->GetOverScrolledDelta(-20.0f).end, 0.0f);
    EXPECT_EQ(info->GetOverScrolledDelta(20.0f).end, 0.0f);

    UpdateCurrentOffset(20.0f);
    EXPECT_EQ(info->GetOverScrolledDelta(-20.0f).end, 0.0f);
    EXPECT_EQ(info->GetOverScrolledDelta(20.0f).end, 0.0f);

    UpdateCurrentOffset(5.0f);
    EXPECT_FALSE(info->itemEnd_);
}

/**
 * @tc.name: ScrollToEdge003
 * @tc.desc: ScrollToEdge and check overScroll
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowSWTest, ScrollToEdge004, TestSize.Level1)
{
    WaterFlowModelNG model = CreateWaterFlow();
    model.SetFooter(GetDefaultHeaderBuilder());
    model.SetColumnsTemplate("1fr 1fr 1fr");
    model.SetRowsGap(Dimension(5.0f));
    model.SetEdgeEffect(EdgeEffect::SPRING, true);
    CreateRandomWaterFlowItems(100);
    CreateDone();
    UpdateCurrentOffset(-Infinity<float>());
    EXPECT_EQ(GetChildY(frameNode_, 0), 750.0f);
    std::vector<float> endPos = { info_->lanes_[0][0].endPos, info_->lanes_[0][1].endPos, info_->lanes_[0][2].endPos };
    std::vector<int32_t> endItems = { info_->lanes_[0][0].items_.back().idx, info_->lanes_[0][1].items_.back().idx,
        info_->lanes_[0][2].items_.back().idx };

    pattern_->SetAnimateCanOverScroll(true);
    info_->delta_ = -751.0f;
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    FlushUITasks();
    for (int i = 0; i < 3; ++i) {
        EXPECT_EQ(info_->lanes_[0][i].endPos, endPos[i] - 751.0f);
        if (info_->idxToLane_[99] != i) {
            EXPECT_EQ(info_->lanes_[0][i].startPos, info_->lanes_[0][i].endPos);
            EXPECT_TRUE(info_->lanes_[0][i].items_.empty());
            EXPECT_FALSE(GetChildFrameNode(frameNode_, endItems[i] + 1)->IsActive()); // + 1 to skip footer node
        } else {
            EXPECT_EQ(info_->lanes_[0][i].items_.back().idx, 99);
        }
    }

    const std::function<bool()> canEnd = [&]() {
        return std::all_of(endItems.begin(), endItems.end(),
            [this](int32_t idx) { return GetChildFrameNode(frameNode_, idx)->IsActive(); });
    };
    while (!canEnd()) {
        info_->delta_ = 2.0f;
        frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
        FlushUITasks();
        for (int i = 0; i < 3; ++i) {
            if (!info_->lanes_[0][i].items_.empty()) {
                ASSERT_TRUE(GetChildFrameNode(frameNode_, endItems[i] + 1)->IsActive());
                ASSERT_EQ(GetChildRect(frameNode_, endItems[i] + 1).Bottom(), info_->lanes_[0][i].endPos);
            } else {
                ASSERT_EQ(info_->lanes_[0][i].startPos, info_->lanes_[0][i].endPos);
            }
        }
    }
}

/**
 * @tc.name: ScrollToEdge003
 * @tc.desc: overScroll top and scroll back
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowSWTest, ScrollToEdge005, TestSize.Level1)
{
    WaterFlowModelNG model = CreateWaterFlow();
    model.SetColumnsTemplate("1fr 1fr 1fr");
    model.SetRowsGap(Dimension(5.0f));
    model.SetEdgeEffect(EdgeEffect::SPRING, true);
    CreateRandomWaterFlowItems(100);
    CreateDone();
    pattern_->SetAnimateCanOverScroll(true);
    info_->delta_ = 800.0f;
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    FlushUITasks();
    for (int i = 1; i < 3; ++i) {
        EXPECT_EQ(info_->lanes_[0][i].startPos, 800.0f);
        EXPECT_EQ(info_->lanes_[0][i].startPos, info_->lanes_[0][i].endPos);
        EXPECT_TRUE(info_->lanes_[0][i].items_.empty());
        EXPECT_FALSE(GetChildFrameNode(frameNode_, i)->IsActive());
    }

    info_->delta_ = -2.0f;
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    FlushUITasks();
    for (int i = 0; i < 3; ++i) {
        ASSERT_TRUE(GetChildFrameNode(frameNode_, i)->IsActive());
        ASSERT_EQ(GetChildY(frameNode_, i), info_->lanes_[0][i].startPos);
        ASSERT_EQ(GetChildRect(frameNode_, i).Bottom(),
            info_->lanes_[0][i].startPos + info_->lanes_[0][i].items_.front().mainSize);
        ASSERT_EQ(GetChildRect(frameNode_, i).Bottom(), info_->lanes_[0][i].endPos);
    }
}

/**
 * @tc.name: ScrollToEdge008
 * @tc.desc: scrollEdge to top form bottom and trigger reach start
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, ScrollToEdge008, TestSize.Level1)
{
    bool isReachStartCalled = false;
    auto reachStart = [&isReachStartCalled]() { isReachStartCalled = true; };
    WaterFlowModelNG model = CreateWaterFlow();
    model.SetOnReachStart(reachStart);
    CreateWaterFlowItems(100);
    CreateDone();

    /**
     * @tc.steps: step1. init will trigger once
     */
    EXPECT_TRUE(isReachStartCalled);
    isReachStartCalled = false;

    /**
     * @tc.steps: step2. scrollEdge to end
     */
    ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, false);

    /**
     * @tc.steps: step3. scrollEdge to start
     * @tc.expected: Trigger reachstart
     */
    ScrollToEdge(ScrollEdgeType::SCROLL_TOP, false);
    EXPECT_TRUE(isReachStartCalled);
}

/**
 * @tc.name: ResetSections001
 * @tc.desc: Layout WaterFlow and then reset to old layout
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowSWTest, ResetSections001, TestSize.Level1)
{
    CreateWaterFlow();
    ViewAbstract::SetWidth(CalcLength(400.0f));
    ViewAbstract::SetHeight(CalcLength(600.f));
    CreateWaterFlowItems(60);
    auto secObj = pattern_->GetOrCreateWaterFlowSections();
    secObj->ChangeData(0, 0, SECTION_5);
    CreateDone();

    UpdateCurrentOffset(-205.0f);
    EXPECT_EQ(info_->startIndex_, 3);
    EXPECT_EQ(info_->endIndex_, 11);
    EXPECT_EQ(info_->storedOffset_, -100.0f);

    // fallback to layout without sections
    pattern_->ResetSections();
    FlushUITasks();
    EXPECT_EQ(info_->startIndex_, 3);
    EXPECT_EQ(info_->storedOffset_, -100.0f);
    EXPECT_EQ(info_->GetCrossCount(), 1);
    EXPECT_EQ(info_->segmentTails_.size(), 1);
    EXPECT_EQ(info_->margins_.size(), 1);
}

/**
 * @tc.name: ChangeLayoutMode001
 * @tc.desc: change WaterFlow layout mode
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowSWTest, ChangeLayoutMode001, TestSize.Level1)
{
    CreateWaterFlow();
    ViewAbstract::SetWidth(CalcLength(400.0f));
    ViewAbstract::SetHeight(CalcLength(600.f));
    CreateWaterFlowItems(60);
    auto secObj = pattern_->GetOrCreateWaterFlowSections();
    secObj->ChangeData(0, 0, SECTION_5);
    CreateDone();

    UpdateCurrentOffset(-205.0f);
    EXPECT_EQ(info_->startIndex_, 3);
    EXPECT_EQ(info_->endIndex_, 11);

    EXPECT_EQ(pattern_->layoutInfo_->Mode(), WaterFlowLayoutMode::SLIDING_WINDOW);
    pattern_->SetLayoutMode(WaterFlowLayoutMode::TOP_DOWN);
    FlushUITasks();
    EXPECT_EQ(pattern_->layoutInfo_->startIndex_, 0);

    UpdateCurrentOffset(-205.0f);
    EXPECT_EQ(pattern_->layoutInfo_->startIndex_, 3);
    pattern_->SetLayoutMode(WaterFlowLayoutMode::SLIDING_WINDOW);
    FlushUITasks();
    EXPECT_EQ(pattern_->layoutInfo_->startIndex_, 0);
}

/**
 * @tc.name: NotifyDataChange001
 * @tc.desc: Test the return value of NotifyDataChange in regular layout.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowSWTest, NotifyDataChange001, TestSize.Level1)
{
    CreateWaterFlow();
    ViewAbstract::SetWidth(CalcLength(400.0f));
    ViewAbstract::SetHeight(CalcLength(600.f));
    CreateWaterFlowItems(60);
    CreateDone();
    UpdateCurrentOffset(-1000.0f);
    EXPECT_EQ(info_->startIndex_, 7);
    EXPECT_EQ(info_->endIndex_, 10);

    EXPECT_EQ(pattern_->layoutInfo_->Mode(), WaterFlowLayoutMode::SLIDING_WINDOW);
    info_->NotifyDataChange(0, 1);
    EXPECT_EQ(info_->newStartIndex_, 8);

    info_->NotifyDataChange(1, 3);
    info_->NotifyDataChange(1, -2);
    EXPECT_EQ(info_->newStartIndex_, 9);

    info_->NotifyDataChange(1, -2);
    EXPECT_EQ(info_->newStartIndex_, 7);

    info_->NotifyDataChange(1, -2);
    EXPECT_EQ(info_->newStartIndex_, 5);

    info_->NotifyDataChange(1, -5);
    EXPECT_EQ(info_->newStartIndex_, -2);
    info_->NotifyDataChange(1, 10);
    EXPECT_EQ(info_->newStartIndex_, -2);

    UpdateCurrentOffset(-1000.0f);
    EXPECT_EQ(info_->newStartIndex_, -1);

    EXPECT_EQ(info_->startIndex_, 13);
    info_->NotifyDataChange(17, 0);
    EXPECT_EQ(info_->newStartIndex_, -2);
    info_->NotifyDataChange(0, 10);
    EXPECT_EQ(info_->newStartIndex_, -2);
}

/**
 * @tc.name: UpdateLanesIndex001
 * @tc.desc: Test the limit of UpdateLanesIndex.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowSWTest, UpdateLanesIndex001, TestSize.Level1)
{
    CreateWaterFlow();
    ViewAbstract::SetWidth(CalcLength(400.0f));
    ViewAbstract::SetHeight(CalcLength(600.f));
    CreateWaterFlowItems(60);
    auto secObj = pattern_->GetOrCreateWaterFlowSections();
    secObj->ChangeData(0, 0, SECTION_5);
    CreateDone();

    UpdateCurrentOffset(-1000.0f);
    EXPECT_EQ(info_->startIndex_, 13);
    EXPECT_EQ(info_->endIndex_, 17);
    info_->newStartIndex_ = 15;
    info_->BeginUpdate();
    info_->UpdateLanesIndex(17);
    EXPECT_EQ(info_->StartIndex(), 15);
    EXPECT_EQ(info_->EndIndex(), 19);
    EXPECT_FALSE(info_->idxToLane_.count(13));
}

/**
 * @tc.name: NotifyDataChange002
 * @tc.desc: Test the return value of NotifyDataChange when updating the section in segment layout.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowSWTest, NotifyDataChange002, TestSize.Level1)
{
    CreateWaterFlow();
    ViewAbstract::SetWidth(CalcLength(400.0f));
    ViewAbstract::SetHeight(CalcLength(600.f));
    CreateWaterFlowItems(45);
    auto secObj = pattern_->GetOrCreateWaterFlowSections();
    secObj->ChangeData(0, 0, SECTION_10);
    CreateDone();

    UpdateCurrentOffset(-1000.0f);
    EXPECT_EQ(info_->startIndex_, 11);
    EXPECT_EQ(info_->endIndex_, 22);

    /**
     * @tc.steps: step1. update the sections above the lanes
     * @tc.expected: newStartIndex_ can be setted to the correct value.
     */

    std::vector<WaterFlowSections::Section> newSections = { WaterFlowSections::Section {
        .itemsCount = 7, .crossCount = 5 } };
    secObj->ChangeData(2, 2, newSections);
    AddItems(2);
    info_->NotifyDataChange(5, 2);
    EXPECT_EQ(info_->newStartIndex_, 13);

    /**
     * @tc.steps: step2. UPDATE the sections which in the lanes without the change of dataSource.
     * @tc.expected: newStartIndex_ is -1.
     */

    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    FlushUITasks();
    EXPECT_EQ(info_->startIndex_, 13);

    newSections = { WaterFlowSections::Section { .itemsCount = 2, .crossCount = 5 } };
    secObj->ChangeData(4, 1, newSections);
    EXPECT_EQ(info_->newStartIndex_, -2);

    FlushUITasks();
    EXPECT_EQ(info_->startIndex_, 13);

    /**
     * @tc.steps: step3. update the sections which in back of the lanes.
     * @tc.expected: newStartIndex_ can be setted to -2.
     */

    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    FlushUITasks();
    EXPECT_EQ(info_->startIndex_, 13);
    EXPECT_EQ(info_->newStartIndex_, -1);

    newSections = { WaterFlowSections::Section { .itemsCount = 30, .crossCount = 5 } };
    secObj->ChangeData(6, 1, newSections);
    EXPECT_EQ(info_->newStartIndex_, -1);
}

/**
 * @tc.name: KeepContentPosition001
 * @tc.desc: In regular layout, test the function of KeepContentPosition when adding items.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowSWTest, KeepContentPosition001, TestSize.Level1)
{
    CreateWaterFlow();
    ViewAbstract::SetWidth(CalcLength(400.0f));
    ViewAbstract::SetHeight(CalcLength(600.f));
    CreateWaterFlowItems(60);
    CreateDone();

    EXPECT_EQ(info_->startIndex_, 0);
    EXPECT_EQ(info_->endIndex_, 3);
    EXPECT_EQ(pattern_->layoutInfo_->Mode(), WaterFlowLayoutMode::SLIDING_WINDOW);

    /**
     * @ts.brief: add items at startIndex_, content should be unchanged.
     * @tc.steps: step1. current lanes_: [0, 3], Add 1 items at 0.
     * @tc.expected: newStartIndex_ should be set to 1, keep content unchanged.
     */
    AddItemsAtSlot(1, 100.0f, 0);
    frameNode_->ChildrenUpdatedFrom(0);
    info_->NotifyDataChange(0, 1);

    EXPECT_EQ(info_->newStartIndex_, 1);
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    FlushUITasks();
    EXPECT_EQ(info_->startIndex_, 1);
    EXPECT_EQ(info_->endIndex_, 4);
    EXPECT_EQ(info_->newStartIndex_, -1);

    // slide backward.
    UpdateCurrentOffset(1000.0f);
    EXPECT_EQ(info_->startIndex_, 0);
    EXPECT_EQ(info_->endIndex_, 4);

    /**
     * @ts.brief: add items in front of startIndex_, content should be unchanged.
     * @tc.steps: step2. current lanes_: [7, 10], Add 2 items at 6.
     * @tc.expected: newStartIndex_ should be set to 7+2, keep content unchanged.
     */
    UpdateCurrentOffset(-1000.0f);
    EXPECT_EQ(info_->startIndex_, 7);
    EXPECT_EQ(info_->endIndex_, 10);

    AddItemsAtSlot(2, 100.0f, 6);
    frameNode_->ChildrenUpdatedFrom(6);
    info_->NotifyDataChange(6, 2);

    EXPECT_EQ(info_->newStartIndex_, 9);
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    FlushUITasks();
    EXPECT_EQ(info_->startIndex_, 9);
    EXPECT_EQ(info_->endIndex_, 12);
    EXPECT_EQ(info_->newStartIndex_, -1);

    // slide forward.
    UpdateCurrentOffset(-500.0f);
    EXPECT_EQ(info_->startIndex_, 12);
    EXPECT_EQ(info_->endIndex_, 16);

    // slide backward.
    UpdateCurrentOffset(1000.0f);
    EXPECT_EQ(info_->startIndex_, 5);
    EXPECT_EQ(info_->endIndex_, 9);

    /**
     * @ts.brief: add items behind startIndex_, content should be changed.
     * @tc.steps: step2. current lanes_: [5, 9], Add 1 items at 6.
     * @tc.expected: newStartIndex_ should be set to -2, content is changed.
     */
    EXPECT_EQ(info_->startIndex_, 5);
    EXPECT_EQ(info_->endIndex_, 9);

    AddItemsAtSlot(1, 100.0f, 6);
    frameNode_->ChildrenUpdatedFrom(6);
    info_->NotifyDataChange(6, 1);

    EXPECT_EQ(info_->newStartIndex_, -2);
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    FlushUITasks();
    EXPECT_EQ(info_->startIndex_, 5);
    EXPECT_EQ(info_->endIndex_, 9);
    EXPECT_EQ(info_->newStartIndex_, -1);
}

/**
 * @tc.name: KeepContentPosition002
 * @tc.desc: In regular layout, test the KeepContentPosition function when deleting items.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowSWTest, KeepContentPosition002, TestSize.Level1)
{
    CreateWaterFlow();
    ViewAbstract::SetWidth(CalcLength(400.0f));
    ViewAbstract::SetHeight(CalcLength(600.f));
    CreateWaterFlowItems(60);
    CreateDone();

    EXPECT_EQ(info_->startIndex_, 0);
    EXPECT_EQ(info_->endIndex_, 3);
    EXPECT_EQ(pattern_->layoutInfo_->Mode(), WaterFlowLayoutMode::SLIDING_WINDOW);

    /**
     * @ts.brief: delete items at startIndex_, content should be changed.
     * @tc.steps: step1. current lanes_: [0, 3], delete 1 items at 0.
     * @tc.expected: newStartIndex_ should be set to -2, content is changed.
     */
    frameNode_->RemoveChildAtIndex(0);
    frameNode_->ChildrenUpdatedFrom(0);
    info_->NotifyDataChange(0, -1);

    EXPECT_EQ(info_->newStartIndex_, -2);
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    FlushUITasks();
    EXPECT_EQ(info_->startIndex_, 0);
    EXPECT_EQ(info_->endIndex_, 3);
    EXPECT_EQ(info_->newStartIndex_, -1);

    // slide forward.
    UpdateCurrentOffset(-600.0f);
    EXPECT_EQ(info_->startIndex_, 4);
    EXPECT_EQ(info_->endIndex_, 7);

    /**
     * @ts.brief: delete items in front of startIndex_, content should be unchanged.
     * @tc.steps: step2. current lanes_: [10, 14], delete 1 items at 9.
     * @tc.expected: newStartIndex_ should be set to 10-1, keep content unchanged.
     */
    UpdateCurrentOffset(-1000.0f);
    EXPECT_EQ(info_->startIndex_, 10);
    EXPECT_EQ(info_->endIndex_, 14);

    frameNode_->RemoveChildAtIndex(9);
    frameNode_->ChildrenUpdatedFrom(9);
    info_->NotifyDataChange(9, -1);

    EXPECT_EQ(info_->newStartIndex_, 9);
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    FlushUITasks();
    EXPECT_EQ(info_->startIndex_, 9);
    EXPECT_EQ(info_->endIndex_, 13);
    EXPECT_EQ(info_->newStartIndex_, -1);

    // slide forward.
    UpdateCurrentOffset(-200.0f);
    EXPECT_EQ(info_->startIndex_, 11);
    EXPECT_EQ(info_->endIndex_, 14);

    // slide backward.
    UpdateCurrentOffset(300.0f);
    EXPECT_EQ(info_->startIndex_, 9);
    EXPECT_EQ(info_->endIndex_, 12);

    /**
     * @ts.brief: If delete the item in [startIndex_, endIndex_], content should be changed.
     * @tc.steps: step2. current lanes_: [9, 12], delete 2 items at 8.
     * @tc.expected: newStartIndex_ should be set to -2, layout at original startIndex_ (9).
     */
    EXPECT_EQ(info_->startIndex_, 9);
    EXPECT_EQ(info_->endIndex_, 12);

    frameNode_->RemoveChildAtIndex(8);
    frameNode_->RemoveChildAtIndex(8);
    frameNode_->ChildrenUpdatedFrom(8);
    info_->NotifyDataChange(8, -2);

    EXPECT_EQ(info_->newStartIndex_, -2);
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    FlushUITasks();
    EXPECT_EQ(info_->startIndex_, 9);
    EXPECT_EQ(info_->endIndex_, 12);
    EXPECT_EQ(info_->newStartIndex_, -1);

    // slide forward.
    UpdateCurrentOffset(-200.0f);
    EXPECT_EQ(info_->startIndex_, 10);
    EXPECT_EQ(info_->endIndex_, 13);

    // slide backward.
    UpdateCurrentOffset(300.0f);
    EXPECT_EQ(info_->startIndex_, 8);
    EXPECT_EQ(info_->endIndex_, 11);

    /**
     * @ts.brief: delete items behind startIndex_, content should be changed.
     * @tc.steps: step2. current lanes_: [8, 11], delete 1 items at 10.
     * @tc.expected: newStartIndex_ should be set to -2, layout at original startIndex_ (9).
     */
    EXPECT_EQ(info_->startIndex_, 8);
    EXPECT_EQ(info_->endIndex_, 11);

    frameNode_->RemoveChildAtIndex(10);
    frameNode_->ChildrenUpdatedFrom(10);
    info_->NotifyDataChange(10, -1);

    EXPECT_EQ(info_->newStartIndex_, -2);
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    FlushUITasks();
    EXPECT_EQ(info_->startIndex_, 8);
    EXPECT_EQ(info_->endIndex_, 11);
    EXPECT_EQ(info_->newStartIndex_, -1);

    /**
     * @ts.brief: change items in front of startIndex_, content should be unchanged.
     * @tc.steps: step2. current lanes_: [8, 11], change 1 items at 7.
     * @tc.expected: newStartIndex_ should be set to 8, layout at startIndex_ (8).
     */
    EXPECT_EQ(info_->startIndex_, 8);
    EXPECT_EQ(info_->endIndex_, 11);

    frameNode_->ChildrenUpdatedFrom(7);
    info_->NotifyDataChange(7, 0);

    EXPECT_EQ(info_->newStartIndex_, 8);
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    FlushUITasks();
    EXPECT_EQ(info_->startIndex_, 8);
    EXPECT_EQ(info_->endIndex_, 11);
    EXPECT_EQ(info_->newStartIndex_, -1);
}

/**
 * @tc.name: KeepContentPosition003
 * @tc.desc: In segment layout, test the function of KeepContentPosition without dataSource change.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowSWTest, KeepContentPosition003, TestSize.Level1)
{
    CreateWaterFlow();
    ViewAbstract::SetWidth(CalcLength(400.0f));
    ViewAbstract::SetHeight(CalcLength(600.f));
    CreateWaterFlowItems(35);
    auto secObj = pattern_->GetOrCreateWaterFlowSections();
    secObj->ChangeData(0, 0, SECTION_11);
    CreateDone();

    UpdateCurrentOffset(-600.0f);
    EXPECT_EQ(info_->startIndex_, 6);
    EXPECT_EQ(info_->endIndex_, 12);
    EXPECT_EQ(pattern_->layoutInfo_->Mode(), WaterFlowLayoutMode::SLIDING_WINDOW);

    /**
     * @ts.brief: when update section in the front of lanes, keep content unchanged.
     * @tc.steps: step1. current lanes_: [6, 12], {seg0: {0, 1, 2}, seg1:{3, 4}} -> {seg0: {0, 1}, seg1: {2, 3, 4}}.
     * @tc.expected: newStartIndex_ should be set to 6, keep content unchanged.
     */
    std::vector<WaterFlowSections::Section> newSection = {
        WaterFlowSections::Section {
            .itemsCount = 2, .onGetItemMainSizeByIndex = GET_MAIN_SIZE_FUNC, .crossCount = 3, .margin = MARGIN_1 },
        WaterFlowSections::Section {
            .itemsCount = 3, .onGetItemMainSizeByIndex = GET_MAIN_SIZE_FUNC, .crossCount = 3, .margin = MARGIN_1 }
    };
    secObj->ChangeData(0, 2, newSection);

    EXPECT_EQ(info_->newStartIndex_, -1);
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    FlushUITasks();
    EXPECT_EQ(info_->startIndex_, 6);
    EXPECT_EQ(info_->endIndex_, 12);
    EXPECT_EQ(info_->newStartIndex_, -1);

    // slide backward.
    UpdateCurrentOffset(1000.0f);
    EXPECT_EQ(info_->startIndex_, 0);
    EXPECT_EQ(info_->endIndex_, 6);

    /**
     * @ts.brief: when update section in the front of lanes, keep content unchanged.
     * @tc.steps: step2. current lanes_: [6, 12], {seg0: {0,1}, seg1:{2,3,4}} -> {seg0: {0,1,2,3}, seg1: {4}}.
     * @tc.expected: newStartIndex_ should be set to 6, keep content unchanged.
     */
    UpdateCurrentOffset(-600.0f);
    EXPECT_EQ(info_->startIndex_, 6);
    EXPECT_EQ(info_->endIndex_, 12);

    newSection = {
        WaterFlowSections::Section {
            .itemsCount = 4, .onGetItemMainSizeByIndex = GET_MAIN_SIZE_FUNC, .crossCount = 3, .margin = MARGIN_1 },
        WaterFlowSections::Section {
            .itemsCount = 1, .onGetItemMainSizeByIndex = GET_MAIN_SIZE_FUNC, .crossCount = 3, .margin = MARGIN_1 }
    };
    secObj->ChangeData(0, 2, newSection);

    EXPECT_EQ(info_->newStartIndex_, -1);
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    FlushUITasks();
    EXPECT_EQ(info_->startIndex_, 6);
    EXPECT_EQ(info_->endIndex_, 12);
    EXPECT_EQ(info_->newStartIndex_, -1);

    // slide forward.
    UpdateCurrentOffset(-500.0f);
    EXPECT_EQ(info_->startIndex_, 11);
    EXPECT_EQ(info_->endIndex_, 17);

    // slide backward.
    UpdateCurrentOffset(1000.0f);
    EXPECT_EQ(info_->startIndex_, 0);
    EXPECT_EQ(info_->endIndex_, 6);
}

/**
 * @tc.name: KeepContentPosition004
 * @tc.desc: In segment layout, test the function of KeepContentPosition using section.UPDATE.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowSWTest, KeepContentPosition004, TestSize.Level1)
{
    CreateWaterFlow();
    ViewAbstract::SetWidth(CalcLength(400.0f));
    ViewAbstract::SetHeight(CalcLength(600.f));
    CreateWaterFlowItems(35);
    auto secObj = pattern_->GetOrCreateWaterFlowSections();
    secObj->ChangeData(0, 0, SECTION_11);
    CreateDone();

    EXPECT_EQ(info_->startIndex_, 0);
    EXPECT_EQ(info_->endIndex_, 6);
    EXPECT_EQ(pattern_->layoutInfo_->Mode(), WaterFlowLayoutMode::SLIDING_WINDOW);

    /**
     * @ts.brief: when ADD new items in the beginning using section.UPDATE, keep content unchanged.
     * @tc.steps: step1. current lanes_: [0, 6], add 1 items at 0.
                 {lanes_[0]: {0, 1, 2}, lanes_[1]: {3, 4}} -> {lanes_[0]: {1, 2, 3}, lanes_[1]: {4, 5}}.
     * @tc.expected: newStartIndex_ should be set to 0+1, keep content unchanged.
     */

    EXPECT_EQ(info_->lanes_[0][0].ToString(), "{StartPos: 5.000000 EndPos: 315.000000 Items [0 1 2 ] }");
    EXPECT_EQ(info_->lanes_[1][0].ToString(), "{StartPos: 325.000000 EndPos: 425.000000 Items [3 ] }");
    EXPECT_EQ(info_->lanes_[1][1].ToString(), "{StartPos: 325.000000 EndPos: 425.000000 Items [4 ] }");
    EXPECT_TRUE(info_->lanes_[2][0].items_.empty());
    EXPECT_EQ(info_->lanes_[3][0].ToString(), "{StartPos: 445.000000 EndPos: 647.000000 Items [5 6 ] }");

    AddItemsAtSlot(1, 100.0f, 0);
    frameNode_->ChildrenUpdatedFrom(0);
    info_->NotifyDataChange(0, 1);
    std::vector<WaterFlowSections::Section> newSection = { WaterFlowSections::Section { .itemsCount = 4,
        .onGetItemMainSizeByIndex = GET_MAIN_SIZE_2,
        .crossCount = 1,
        .rowsGap = 5.0_vp,
        .margin = MARGIN_3 } };
    secObj->ChangeData(0, 1, newSection);

    EXPECT_EQ(info_->newStartIndex_, 1);
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    FlushUITasks();
    EXPECT_EQ(info_->startIndex_, 1);
    EXPECT_EQ(info_->endIndex_, 7);
    EXPECT_EQ(info_->lanes_[0][0].items_.front().idx, 1);
    EXPECT_EQ(info_->newStartIndex_, -1);

    /**
     * @ts.brief: when add new items in the beginning using section.UPDATE, keep content unchanged.
     * @tc.steps: step2. current lanes_: [1, 5], add 3 items at 0.
     *            {lanes_[0]: {1, 2, 3}, lanes_[1]: {4, 5}} -> {lanes_[0]: {4, 5, 6}, lanes_[1]: {7, 8}}.
     * @tc.expected: newStartIndex_ should be set to 1+3, keep content unchanged.
     */

    AddItemsAtSlot(3, 100.0f, 0);
    frameNode_->ChildrenUpdatedFrom(0);
    info_->NotifyDataChange(0, 3);
    newSection = { WaterFlowSections::Section { .itemsCount = 7,
        .onGetItemMainSizeByIndex = GET_MAIN_SIZE_2,
        .crossCount = 1,
        .rowsGap = 5.0_vp,
        .margin = MARGIN_3 } };
    secObj->ChangeData(0, 1, newSection);

    EXPECT_EQ(info_->newStartIndex_, 4);
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    FlushUITasks();
    EXPECT_EQ(info_->startIndex_, 4);
    EXPECT_EQ(info_->endIndex_, 10);
    EXPECT_EQ(info_->newStartIndex_, -1);
    EXPECT_EQ(info_->lanes_[0][0].ToString(), "{StartPos: 5.000000 EndPos: 315.000000 Items [4 5 6 ] }");
    EXPECT_EQ(info_->lanes_[1][0].ToString(), "{StartPos: 325.000000 EndPos: 425.000000 Items [7 ] }");
    EXPECT_EQ(info_->lanes_[1][1].ToString(), "{StartPos: 325.000000 EndPos: 425.000000 Items [8 ] }");
    EXPECT_TRUE(info_->lanes_[2][0].items_.empty());
    EXPECT_EQ(info_->lanes_[3][0].ToString(), "{StartPos: 445.000000 EndPos: 647.000000 Items [9 10 ] }");

    /**
     * @ts.brief: when delete items in front of startIndex_ using section.UPDATE, keep content unchanged.
     * @tc.steps: step4. current lanes_: [4, 10], delete 2 items at 1.
     *            {lanes_[0]: {4, 5, 6}, lanes_[1]: {7, 8}, lanes_[2]: {}, lanes_[3]: {9,10}} ->
     *            {lanes_[0]: {2, 3, 4}, lanes_[1]: {5, 6}, lanes_[2]: {}, lanes_[3]: {7,8}}.
     * @tc.expected: newStartIndex_ should be set to 4-2, keep content unchanged.
     */

    frameNode_->ChildrenUpdatedFrom(1);
    frameNode_->RemoveChildAtIndex(1);
    frameNode_->RemoveChildAtIndex(1);
    info_->NotifyDataChange(1, -2);

    newSection = { WaterFlowSections::Section { .itemsCount = 5,
        .onGetItemMainSizeByIndex = GET_MAIN_SIZE_2,
        .crossCount = 1,
        .rowsGap = 5.0_vp,
        .margin = MARGIN_3 } };
    secObj->ChangeData(0, 1, newSection);

    EXPECT_EQ(info_->newStartIndex_, 2);
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    FlushUITasks();
    EXPECT_EQ(info_->startIndex_, 2);
    EXPECT_EQ(info_->endIndex_, 8);
    EXPECT_EQ(info_->newStartIndex_, -1);
    EXPECT_EQ(info_->lanes_[0][0].ToString(), "{StartPos: 5.000000 EndPos: 315.000000 Items [2 3 4 ] }");
    EXPECT_EQ(info_->lanes_[1][0].ToString(), "{StartPos: 325.000000 EndPos: 425.000000 Items [5 ] }");
    EXPECT_EQ(info_->lanes_[1][1].ToString(), "{StartPos: 325.000000 EndPos: 425.000000 Items [6 ] }");
    EXPECT_TRUE(info_->lanes_[2][0].items_.empty());
    EXPECT_EQ(info_->lanes_[3][0].ToString(), "{StartPos: 445.000000 EndPos: 647.000000 Items [7 8 ] }");

    /**
     * @ts.brief: when delete items in front of startIndex_ using section.UPDATE, keep content unchanged.
     * @tc.steps: step4. current lanes_: [2, 8], delete 1 items at 1.
     *            {lanes_[0]: {2, 3, 4}, lanes_[1]: {5, 6}, lanes_[2]: {}, lanes_[3]: {7,8}} ->
     *            {lanes_[0]: {1, 2, 3}, lanes_[1]: {4, 5}, lanes_[2]: {}, lanes_[3]: {6,7}}.
     * @tc.expected: newStartIndex_ should be set to 2-1, keep content unchanged.
     */

    frameNode_->RemoveChildAtIndex(1);
    frameNode_->ChildrenUpdatedFrom(1);
    info_->NotifyDataChange(1, -1);
    newSection = { WaterFlowSections::Section { .itemsCount = 4,
        .onGetItemMainSizeByIndex = GET_MAIN_SIZE_2,
        .crossCount = 1,
        .rowsGap = 5.0_vp,
        .margin = MARGIN_3 } };
    secObj->ChangeData(0, 1, newSection);

    EXPECT_EQ(info_->newStartIndex_, 1);
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    FlushUITasks();
    EXPECT_EQ(info_->startIndex_, 1);
    EXPECT_EQ(info_->endIndex_, 7);
    EXPECT_EQ(info_->newStartIndex_, -1);
    EXPECT_EQ(info_->lanes_[0][0].ToString(), "{StartPos: 5.000000 EndPos: 315.000000 Items [1 2 3 ] }");
    EXPECT_EQ(info_->lanes_[1][0].ToString(), "{StartPos: 325.000000 EndPos: 425.000000 Items [4 ] }");
    EXPECT_EQ(info_->lanes_[1][1].ToString(), "{StartPos: 325.000000 EndPos: 425.000000 Items [5 ] }");
    EXPECT_TRUE(info_->lanes_[2][0].items_.empty());
    EXPECT_EQ(info_->lanes_[3][0].ToString(), "{StartPos: 445.000000 EndPos: 647.000000 Items [6 7 ] }");

    /**
     * @ts.brief: when delete items in front of startIndex_ using section.UPDATE, keep content unchanged.
     * @tc.steps: step4. current lanes_: [1, 7], delete 1 items at 0.
     *            {lanes_[0]: {1, 2, 3}, lanes_[1]: {4, 5}, lanes_[2]: {}, lanes_[3]: {6, 7}} ->
     *            {lanes_[0]: {0, 1, 2}, lanes_[1]: {3, 4}, lanes_[2]: {}, lanes_[3]: {5, 6}}.
     * @tc.expected: newStartIndex_ should be set to 1-1, keep content unchanged.
     */

    frameNode_->RemoveChildAtIndex(0);
    frameNode_->ChildrenUpdatedFrom(0);
    info_->NotifyDataChange(0, -1);
    newSection = { WaterFlowSections::Section { .itemsCount = 3,
        .onGetItemMainSizeByIndex = GET_MAIN_SIZE_2,
        .crossCount = 1,
        .rowsGap = 5.0_vp,
        .margin = MARGIN_3 } };
    secObj->ChangeData(0, 1, newSection);

    EXPECT_EQ(info_->newStartIndex_, 0);
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    FlushUITasks();
    EXPECT_EQ(info_->startIndex_, 0);
    EXPECT_EQ(info_->endIndex_, 6);
    EXPECT_EQ(info_->newStartIndex_, -1);

    /**
     * @ts.brief: when change the property of section using section.UPDATE, can't keep content unchanged.
     * @tc.steps: step4. current lanes_: [2, 8], delete 1 items at 1.
     *            {lanes_[0]: {2, 3, 4}, lanes_[1]: {5, 6}, lanes_[2]: {}, lanes_[3]: {7,8}} ->
     *            {lanes_[0]: {1, 2, 3}, lanes_[1]: {4, 5}, lanes_[2]: {}, lanes_[3]: {6,7}}.
     * @tc.expected: newStartIndex_ should be set to -2, can't keep content unchanged.
     */

    AddItemsAtSlot(0, 100.0f, 1);
    frameNode_->ChildrenUpdatedFrom(0);
    info_->NotifyDataChange(0, 1);
    newSection = { WaterFlowSections::Section { .itemsCount = 4,
        .onGetItemMainSizeByIndex = GET_MAIN_SIZE_2,
        .crossCount = 2,
        .rowsGap = 5.0_vp,
        .margin = MARGIN_3 } };
    secObj->ChangeData(0, 1, newSection);
    pattern_->BeforeCreateLayoutWrapper();
    EXPECT_EQ(info_->newStartIndex_, -2);
}

/**
 * @tc.name: KeepContentPosition005
 * @tc.desc: In segment layout, test the function of KeepContentPosition using section.SPLICE to add sections in the
 *           beginning.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowSWTest, KeepContentPosition005, TestSize.Level1)
{
    CreateWaterFlow();
    ViewAbstract::SetWidth(CalcLength(400.0f));
    ViewAbstract::SetHeight(CalcLength(600.f));
    CreateWaterFlowItems(35);
    auto secObj = pattern_->GetOrCreateWaterFlowSections();
    secObj->ChangeData(0, 0, SECTION_11);
    CreateDone();

    EXPECT_EQ(info_->startIndex_, 0);
    EXPECT_EQ(info_->endIndex_, 6);
    EXPECT_EQ(pattern_->layoutInfo_->Mode(), WaterFlowLayoutMode::SLIDING_WINDOW);

    /**
     * @ts.brief: when ADD new sections in the beginning using section.SPLICE, keep content unchanged.
     * @tc.steps: step1. current lanes_: [0, 6], add 1 section(including 2 items) at 0.
                 {lanes_[0]: {0, 1, 2}, lanes_[1]: {3, 4}} -> {lanes_[0]: {1, 2, 3}, lanes_[1]: {4, 5}}.
     * @tc.expected: newStartIndex_ should be set to 0+2, keep content unchanged.
     */
    EXPECT_EQ(info_->lanes_[0][0].ToString(), "{StartPos: 5.000000 EndPos: 315.000000 Items [0 1 2 ] }");
    EXPECT_EQ(info_->lanes_[1][0].ToString(), "{StartPos: 325.000000 EndPos: 425.000000 Items [3 ] }");
    EXPECT_EQ(info_->lanes_[1][1].ToString(), "{StartPos: 325.000000 EndPos: 425.000000 Items [4 ] }");
    EXPECT_TRUE(info_->lanes_[2][0].items_.empty());
    EXPECT_EQ(info_->lanes_[3][0].ToString(), "{StartPos: 445.000000 EndPos: 647.000000 Items [5 6 ] }");

    AddItemsAtSlot(2, 100.0f, 0);
    frameNode_->ChildrenUpdatedFrom(0);
    info_->NotifyDataChange(0, 2);
    std::vector<WaterFlowSections::Section> newSection = { WaterFlowSections::Section { .itemsCount = 2,
        .onGetItemMainSizeByIndex = GET_MAIN_SIZE_2,
        .crossCount = 2,
        .rowsGap = 10.0_vp,
        .margin = MARGIN_3 } };
    secObj->ChangeData(0, 0, newSection);

    EXPECT_EQ(info_->newStartIndex_, 2);
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    FlushUITasks();
    EXPECT_EQ(info_->startIndex_, 2);
    EXPECT_EQ(info_->endIndex_, 8);
    EXPECT_TRUE(info_->lanes_[0][0].items_.empty());
    EXPECT_TRUE(info_->lanes_[0][1].items_.empty());
    EXPECT_EQ(info_->lanes_[1][0].ToString(), "{StartPos: 5.000000 EndPos: 315.000000 Items [2 3 4 ] }");
    EXPECT_EQ(info_->lanes_[2][0].ToString(), "{StartPos: 325.000000 EndPos: 425.000000 Items [5 ] }");
    EXPECT_EQ(info_->lanes_[2][1].ToString(), "{StartPos: 325.000000 EndPos: 425.000000 Items [6 ] }");
    EXPECT_TRUE(info_->lanes_[3][0].items_.empty());
    EXPECT_EQ(info_->lanes_[4][0].ToString(), "{StartPos: 445.000000 EndPos: 647.000000 Items [7 8 ] }");
    EXPECT_EQ(info_->newStartIndex_, -1);

    // slide backward.
    UpdateCurrentOffset(1000.0f);
    EXPECT_EQ(info_->startIndex_, 0);
    EXPECT_EQ(info_->endIndex_, 7);
    EXPECT_EQ(info_->lanes_[0][0].ToString(), "{StartPos: 5.000000 EndPos: 105.000000 Items [0 ] }");
    EXPECT_EQ(info_->lanes_[0][1].ToString(), "{StartPos: 5.000000 EndPos: 105.000000 Items [1 ] }");
    EXPECT_EQ(info_->lanes_[1][0].ToString(), "{StartPos: 115.000000 EndPos: 425.000000 Items [2 3 4 ] }");
    EXPECT_EQ(info_->lanes_[2][0].ToString(), "{StartPos: 435.000000 EndPos: 535.000000 Items [5 ] }");
    EXPECT_EQ(info_->lanes_[2][1].ToString(), "{StartPos: 435.000000 EndPos: 535.000000 Items [6 ] }");
    EXPECT_TRUE(info_->lanes_[3][0].items_.empty());
    EXPECT_EQ(info_->lanes_[4][0].ToString(), "{StartPos: 555.000000 EndPos: 655.000000 Items [7 ] }");
    /**
     * @ts.brief: when ADD new sections in the beginning using section.SPLICE, keep content unchanged.
     * @tc.steps: step2. current lanes_: [0, 7], add 2 section(including 2 items) at 0.
                 {lanes_[0]: {0, 1}, lanes_[1]: {2, 3, 4}, lanes_[2]: {5, 6}, lanes_[3]: {}, lanes[4]: {7}}
     *        -> {lanes_[2]: {4, 5}, lanes_[3]: {6, 7, 8}, lanes_[4]: {9, 10}, lanes_[5]: {}, lanes[6]: {11}}.
     * @tc.expected: newStartIndex_ should be set to 0+4, keep content unchanged.
     */

    AddItemsAtSlot(4, 100.0f, 0);
    frameNode_->ChildrenUpdatedFrom(0);
    info_->NotifyDataChange(0, 4);
    newSection = { WaterFlowSections::Section { .itemsCount = 2,
                       .onGetItemMainSizeByIndex = GET_MAIN_SIZE_2,
                       .crossCount = 2,
                       .rowsGap = 10.0_vp,
                       .margin = MARGIN_3 },
        WaterFlowSections::Section { .itemsCount = 2,
            .onGetItemMainSizeByIndex = GET_MAIN_SIZE_2,
            .crossCount = 2,
            .rowsGap = 10.0_vp,
            .margin = MARGIN_3 } };
    secObj->ChangeData(0, 0, newSection);

    EXPECT_EQ(info_->newStartIndex_, 4);
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    FlushUITasks();
    EXPECT_EQ(info_->startIndex_, 4);
    EXPECT_EQ(info_->endIndex_, 11);
    EXPECT_TRUE(info_->lanes_[0][0].items_.empty());
    EXPECT_TRUE(info_->lanes_[0][1].items_.empty());
    EXPECT_TRUE(info_->lanes_[1][0].items_.empty());
    EXPECT_TRUE(info_->lanes_[1][1].items_.empty());
    EXPECT_EQ(info_->lanes_[2][0].ToString(), "{StartPos: 5.000000 EndPos: 105.000000 Items [4 ] }");
    EXPECT_EQ(info_->lanes_[2][1].ToString(), "{StartPos: 5.000000 EndPos: 105.000000 Items [5 ] }");
    EXPECT_EQ(info_->lanes_[3][0].ToString(), "{StartPos: 115.000000 EndPos: 425.000000 Items [6 7 8 ] }");
    EXPECT_EQ(info_->lanes_[4][0].ToString(), "{StartPos: 435.000000 EndPos: 535.000000 Items [9 ] }");
    EXPECT_EQ(info_->lanes_[4][1].ToString(), "{StartPos: 435.000000 EndPos: 535.000000 Items [10 ] }");
    EXPECT_TRUE(info_->lanes_[5][0].items_.empty());
    EXPECT_EQ(info_->lanes_[6][0].ToString(), "{StartPos: 555.000000 EndPos: 655.000000 Items [11 ] }");
    EXPECT_EQ(info_->newStartIndex_, -1);

    // slide backward.
    UpdateCurrentOffset(1000.0f);
    EXPECT_EQ(info_->startIndex_, 0);
    EXPECT_EQ(info_->endIndex_, 8);
    EXPECT_EQ(info_->lanes_[0][0].ToString(), "{StartPos: 5.000000 EndPos: 105.000000 Items [0 ] }");
    EXPECT_EQ(info_->lanes_[0][1].ToString(), "{StartPos: 5.000000 EndPos: 105.000000 Items [1 ] }");
    EXPECT_EQ(info_->lanes_[1][0].ToString(), "{StartPos: 115.000000 EndPos: 215.000000 Items [2 ] }");
    EXPECT_EQ(info_->lanes_[1][1].ToString(), "{StartPos: 115.000000 EndPos: 215.000000 Items [3 ] }");
    EXPECT_EQ(info_->lanes_[2][0].ToString(), "{StartPos: 225.000000 EndPos: 325.000000 Items [4 ] }");
    EXPECT_EQ(info_->lanes_[3][0].ToString(), "{StartPos: 335.000000 EndPos: 645.000000 Items [6 7 8 ] }");
    EXPECT_TRUE(info_->lanes_[4][0].items_.empty());
    EXPECT_TRUE(info_->lanes_[4][1].items_.empty());
    EXPECT_TRUE(info_->lanes_[5][0].items_.empty());
}

/**
 * @tc.name: KeepContentPosition006
 * @tc.desc: In segment layout, test the function of KeepContentPosition using section.SPLICE(0, 2, newSection).
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowSWTest, KeepContentPosition006, TestSize.Level1)
{
    CreateWaterFlow();
    ViewAbstract::SetWidth(CalcLength(400.0f));
    ViewAbstract::SetHeight(CalcLength(600.f));
    CreateWaterFlowItems(35);
    auto secObj = pattern_->GetOrCreateWaterFlowSections();
    secObj->ChangeData(0, 0, SECTION_11);
    CreateDone();

    EXPECT_EQ(info_->startIndex_, 0);
    EXPECT_EQ(info_->endIndex_, 6);
    EXPECT_EQ(pattern_->layoutInfo_->Mode(), WaterFlowLayoutMode::SLIDING_WINDOW);

    /**
     * @ts.brief: when use section.SPLICE operate the sections on the upper of screen, keep content unchanged.
     * @tc.steps: step1. current lanes_: [5, 11], operate lanes_[0] and lanes_[1] which are on the upper of screen.
                 {lanes_[0]: {0, 1, 2}, lanes_[1]: {3, 4}} -> {lanes_[0]: {0, 1, 2, 3, 4}}.
     * @tc.expected: newStartIndex_ should be set to 5, keep content unchanged.
     */
    ScrollToIndex(5, false, ScrollAlign::START);
    EXPECT_EQ(info_->startIndex_, 5);
    EXPECT_EQ(info_->endIndex_, 10);
    EXPECT_TRUE(info_->lanes_[0][0].items_.empty());
    EXPECT_TRUE(info_->lanes_[1][0].items_.empty());
    EXPECT_TRUE(info_->lanes_[1][1].items_.empty());
    EXPECT_TRUE(info_->lanes_[2][0].items_.empty());
    EXPECT_EQ(info_->lanes_[3][0].ToString(), "{StartPos: 0.000000 EndPos: 610.000000 Items [5 6 7 8 9 10 ] }");

    std::vector<WaterFlowSections::Section> newSection = {
        WaterFlowSections::Section { .itemsCount = 5,
            .onGetItemMainSizeByIndex = GET_MAIN_SIZE_2,
            .crossCount = 2,
            .rowsGap = 5.0_vp,
            .margin = MARGIN_3 },
    };

    secObj->ChangeData(0, 2, newSection);

    EXPECT_EQ(info_->newStartIndex_, -1);
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    FlushUITasks();
    EXPECT_EQ(info_->startIndex_, 5);
    EXPECT_EQ(info_->endIndex_, 10);
    EXPECT_TRUE(info_->lanes_[0][0].items_.empty());
    EXPECT_TRUE(info_->lanes_[0][1].items_.empty());
    EXPECT_TRUE(info_->lanes_[1][0].items_.empty());
    EXPECT_EQ(info_->lanes_[2][0].ToString(), "{StartPos: 0.000000 EndPos: 610.000000 Items [5 6 7 8 9 10 ] }");
    // slide backward.
    UpdateCurrentOffset(200.0f);
    EXPECT_EQ(info_->startIndex_, 1);
    EXPECT_EQ(info_->endIndex_, 8);
    EXPECT_EQ(info_->lanes_[0][0].ToString(), "{StartPos: -25.000000 EndPos: 180.000000 Items [1 3 ] }");
    EXPECT_EQ(info_->lanes_[0][1].ToString(), "{StartPos: -25.000000 EndPos: 180.000000 Items [2 4 ] }");
    EXPECT_TRUE(info_->lanes_[1][0].items_.empty());
    EXPECT_EQ(info_->lanes_[2][0].ToString(), "{StartPos: 200.000000 EndPos: 606.000000 Items [5 6 7 8 ] }");
}

/**
 * @tc.name: KeepContentPosition007
 * @tc.desc: In segment layout, test the function of KeepContentPosition.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowSWTest, KeepContentPosition007, TestSize.Level1)
{
    CreateWaterFlow();
    ViewAbstract::SetWidth(CalcLength(400.0f));
    ViewAbstract::SetHeight(CalcLength(600.f));
    CreateWaterFlowItems(45);
    auto secObj = pattern_->GetOrCreateWaterFlowSections();
    secObj->ChangeData(0, 0, SECTION_10);
    CreateDone();

    /**
     * @ts.brief: when use section.UPDATE operate the section on the screen and use section.UPDATE operate the section
     on the upper of screen, can't keep content unchanged.
     * @tc.steps: step1. current lanes_[2,3,4]: [5, 12], operate lanes_[0](on the upper of screen) and lanes_[3](on the
     screen).
     * @tc.expected: newStartIndex_ should be set to -2, can't keep content unchanged.
     */
    ScrollToIndex(5, false, ScrollAlign::START);
    EXPECT_EQ(info_->startIndex_, 5);
    EXPECT_EQ(info_->endIndex_, 12);
    EXPECT_TRUE(info_->lanes_[0][0].items_.empty());
    EXPECT_TRUE(info_->lanes_[1][0].items_.empty());
    EXPECT_EQ(info_->lanes_[2][0].ToString(), "{StartPos: 0.000000 EndPos: 200.000000 Items [5 ] }");
    EXPECT_EQ(info_->lanes_[2][1].ToString(), "{StartPos: 0.000000 EndPos: 100.000000 Items [6 ] }");
    EXPECT_EQ(info_->lanes_[2][2].ToString(), "{StartPos: 0.000000 EndPos: 200.000000 Items [7 ] }");
    EXPECT_EQ(info_->lanes_[3][0].ToString(), "{StartPos: 200.000000 EndPos: 300.000000 Items [8 ] }");
    EXPECT_EQ(info_->lanes_[3].size(), 2);

    // itemsCount reduce from 3 to 2
    std::vector<WaterFlowSections::Section> newSection = { WaterFlowSections::Section {
        .itemsCount = 2, .crossCount = 3, .margin = MARGIN_2, .rowsGap = Dimension(5.0f) } };
    frameNode_->ChildrenUpdatedFrom(0);
    frameNode_->RemoveChildAtIndex(0);
    info_->NotifyDataChange(0, -1);
    secObj->ChangeData(0, 1, newSection);

    // crossCount reduce from 2 to 1
    newSection = { WaterFlowSections::Section { .itemsCount = 2, .crossCount = 1 } };
    secObj->ChangeData(3, 1, newSection);

    // can't keep content unchanged
    EXPECT_EQ(info_->newStartIndex_, -2);
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    FlushUITasks();
    EXPECT_EQ(info_->startIndex_, 5);
    EXPECT_EQ(info_->endIndex_, 11);
    EXPECT_TRUE(info_->lanes_[0][0].items_.empty());
    EXPECT_TRUE(info_->lanes_[1][0].items_.empty());
    EXPECT_EQ(info_->lanes_[2][0].ToString(), "{StartPos: 0.000000 EndPos: 100.000000 Items [5 ] }");
    EXPECT_EQ(info_->lanes_[2][1].ToString(), "{StartPos: 0.000000 EndPos: 200.000000 Items [6 ] }");
    EXPECT_EQ(info_->lanes_[2][2].ToString(), "{StartPos: 0.000000 EndPos: 0.000000 empty}");
    EXPECT_EQ(info_->lanes_[3][0].ToString(), "{StartPos: 200.000000 EndPos: 500.000000 Items [7 8 ] }");
    EXPECT_EQ(info_->lanes_[3].size(), 1);
}

/**
 * @tc.name: Cache002
 * @tc.desc: Test cache item layout position
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowSWTest, Cache002, TestSize.Level1)
{
    auto model = CreateWaterFlow();
    CreateItemsInRepeat(50, [](int32_t i) { return i % 2 ? 100.0f : 200.0f; });

    model.SetCachedCount(3);
    model.SetColumnsTemplate("1fr 1fr");
    model.SetRowsGap(Dimension(10));
    model.SetColumnsGap(Dimension(10));
    CreateDone();
    ScrollToIndex(30, false, ScrollAlign::START);
    EXPECT_EQ(info_->startIndex_, 30);
    EXPECT_EQ(info_->endIndex_, 40);
    const std::list<int32_t> preloadList = { 41, 42, 43, 29, 28, 27 };
    EXPECT_EQ(pattern_->preloadItems_, preloadList);
    PipelineContext::GetCurrentContext()->OnIdle(INT64_MAX);
    EXPECT_TRUE(GetChildFrameNode(frameNode_, 40));
    EXPECT_EQ(GetChildWidth(frameNode_, 40), (WATER_FLOW_WIDTH - 10.0f) / 2.0f);
    FlushUITasks();
    EXPECT_EQ(GetChildY(frameNode_, 41), 850.0f);
    EXPECT_EQ(GetChildY(frameNode_, 42), 960.0f);
    EXPECT_EQ(GetChildY(frameNode_, 43), 960.0f);
    EXPECT_EQ(GetChildY(frameNode_, 27), -220.0f);
    EXPECT_EQ(GetChildY(frameNode_, 28), -210.0f);
    EXPECT_EQ(GetChildY(frameNode_, 29), -110.0f);
    // test lanes_'s constraint
    info_->BeginUpdate();
    EXPECT_EQ(info_->StartIndex(), 30);
    EXPECT_EQ(info_->EndIndex(), 40);

    UpdateCurrentOffset(300.0f);
    EXPECT_EQ(info_->startIndex_, 25);
    EXPECT_EQ(info_->endIndex_, 36);
    // item in cache range shouldn't be created yet
    EXPECT_FALSE(GetChildFrameNode(frameNode_, 22));
    PipelineContext::GetCurrentContext()->OnIdle(INT64_MAX);
    ASSERT_TRUE(GetChildFrameNode(frameNode_, 22));
    EXPECT_FALSE(GetChildFrameNode(frameNode_, 22)->IsActive());
    FlushUITasks();
    EXPECT_EQ(GetChildY(frameNode_, 22), -440.0f);
    EXPECT_FALSE(GetChildFrameNode(frameNode_, 22)->IsActive());
}

/**
 * @tc.name: Refresh002
 * @tc.desc: Test WaterFlow nested in refresh. Currently have different friction from TOP_DOWN mode
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowSWTest, Refresh002, TestSize.Level1)
{
    Container::Current()->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    MockAnimationManager::GetInstance().SetTicks(1);
    MockAnimationManager::GetInstance().Reset();
    RefreshModelNG refreshModel;
    refreshModel.Create();
    auto refreshNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    auto model = CreateWaterFlow();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetEdgeEffect(EdgeEffect::SPRING, true);
    CreateWaterFlowItems(3);
    CreateDone();

    GestureEvent info;
    info.SetMainVelocity(-1200.f);
    info.SetMainDelta(-100.f);
    auto scrollable = pattern_->GetScrollableEvent()->GetScrollable();
    scrollable->HandleTouchDown();
    scrollable->HandleDragStart(info);
    scrollable->HandleDragUpdate(info);
    FlushUITasks();
    EXPECT_FLOAT_EQ(GetChildY(frameNode_, 0), -1.2588142);

    EXPECT_TRUE(pattern_->OutBoundaryCallback());
    scrollable->HandleTouchUp();
    scrollable->HandleDragEnd(info);
    FlushUITasks();
    EXPECT_FLOAT_EQ(GetChildY(frameNode_, 0), -2.5077639);

    MockAnimationManager::GetInstance().TickByVelocity(-100.0f);
    FlushUITasks();
    EXPECT_FLOAT_EQ(GetChildY(frameNode_, 0), -102.50777);
    // swipe in the opposite direction
    info.SetMainVelocity(1200.f);
    info.SetMainDelta(100.f);
    scrollable->HandleTouchDown();
    scrollable->HandleDragStart(info);
    scrollable->HandleDragUpdate(info);
    FlushUITasks();
    scrollable->HandleTouchUp();
    scrollable->HandleDragEnd(info);
    FlushUITasks();
    EXPECT_FLOAT_EQ(GetChildY(frameNode_, 0), -97.84362);
    EXPECT_EQ(frameNode_->GetRenderContext()->GetTransformTranslate()->y.Value(), 0.0f);
    MockAnimationManager::GetInstance().TickByVelocity(200.0f);
    FlushUITasks();
    MockAnimationManager::GetInstance().TickByVelocity(1000.0f);
    FlushUITasks();
    EXPECT_EQ(GetChildY(frameNode_, 0), 0.0f);
    EXPECT_EQ(frameNode_->GetRenderContext()->GetTransformTranslate()->y.Value(), 800);
    MockAnimationManager::GetInstance().Tick();
    MockAnimationManager::GetInstance().Tick();
    FlushUITasks();
    EXPECT_EQ(GetChildY(frameNode_, 0), 0.0f);
    // can't enter the refreshing status when refresh updates scroll offset by animation source
    EXPECT_EQ(frameNode_->GetRenderContext()->GetTransformTranslate()->y.Value(), 0);
    EXPECT_TRUE(MockAnimationManager::GetInstance().AllFinished());
}

/**
 * @tc.name: Illegal001
 * @tc.desc: Update Section with empty sections.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowSWTest, Illegal001, TestSize.Level1)
{
    CreateWaterFlow();
    ViewAbstract::SetWidth(CalcLength(400.0f));
    ViewAbstract::SetHeight(CalcLength(600.f));
    CreateWaterFlowItems(45);
    auto secObj = pattern_->GetOrCreateWaterFlowSections();
    secObj->ChangeData(0, 0, SECTION_10);
    CreateDone();

    UpdateCurrentOffset(-300.0f);
    EXPECT_EQ(info_->startIndex_, 3);
    EXPECT_EQ(info_->endIndex_, 12);

    /**
     * @tc.steps: step1. update [sections_] with empty section, without changing the dataSource.
     * @tc.expected: currentOffset_ is set to 0.0f, cache information is reset.
     */
    auto sectionLength = secObj->GetSectionInfo().size();
    secObj->ChangeData(0, sectionLength, {});
    FlushUITasks();

    EXPECT_TRUE(info_->lanes_.empty());
    EXPECT_TRUE(info_->idxToLane_.empty());
    EXPECT_TRUE(info_->segmentTails_.empty());
    EXPECT_TRUE(info_->segmentCache_.empty());
    EXPECT_TRUE(info_->margins_.empty());

    /**
     * @tc.steps: step2. recover [sections_].
     * @tc.expected: layout at start.
     */
    secObj->ChangeData(0, 0, SECTION_10);
    FlushUITasks();
    EXPECT_EQ(info_->startIndex_, 0);
    EXPECT_EQ(info_->endIndex_, 7);

    EXPECT_EQ(info_->lanes_.size(), 7);
    EXPECT_EQ(info_->idxToLane_.size(), 8);
    EXPECT_EQ(info_->segmentTails_.size(), 7);
    EXPECT_EQ(info_->segmentCache_.size(), 9);
    EXPECT_EQ(info_->margins_.size(), 7);
}

/**
 * @tc.name: DataChange001
 * @tc.desc: In less-than fillViewport scene, test overScroll position after changing dataSource.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowSWTest, DataChange001, TestSize.Level1)
{
    auto model = CreateWaterFlow();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetEdgeEffect(EdgeEffect::SPRING, true);
    CreateWaterFlowItems(2);
    CreateDone();

    EXPECT_EQ(pattern_->layoutInfo_->GetContentHeight(), 200.0f);
    frameNode_->RemoveChildAtIndex(1);
    frameNode_->ChildrenUpdatedFrom(1);
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    FlushUITasks();
    EXPECT_EQ(pattern_->layoutInfo_->GetContentHeight(), 100.0f);

    GestureEvent gesture;
    gesture.SetInputEventType(InputEventType::TOUCH_SCREEN);
    gesture.SetMainVelocity(-1000.0f);
    gesture.SetMainDelta(-100.0f);
    gesture.SetGlobalLocation(Offset(1.0f, 1.0f));
    gesture.SetGlobalPoint(Point(1.0f, 100.0f));
    gesture.SetLocalLocation(Offset(1.0f, 1.0f));
    auto scrollable = pattern_->GetScrollableEvent()->GetScrollable();
    ASSERT_TRUE(scrollable);
    scrollable->HandleTouchDown();
    scrollable->HandleDragStart(gesture);
    scrollable->HandleDragUpdate(gesture);
    FlushUITasks();
    EXPECT_FLOAT_EQ(GetChildY(frameNode_, 0), -0.67379469);
    MockAnimationManager::GetInstance().SetTicks(2);
    scrollable->HandleTouchUp();
    scrollable->HandleDragEnd(gesture);
    FlushUITasks();
    EXPECT_FLOAT_EQ(GetChildY(frameNode_, 0), -1.3475894);

    MockAnimationManager::GetInstance().Tick();
    FlushUITasks();
    EXPECT_FLOAT_EQ(GetChildY(frameNode_, 0), -0.67379177);
    MockAnimationManager::GetInstance().Tick();
    FlushUITasks();
    EXPECT_FLOAT_EQ(GetChildY(frameNode_, 0), 0);
}

/*
 * @tc.name: ShowCache003
 * @tc.desc: Test cache items immediately changing layout
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, ShowCache003, TestSize.Level1)
{
    auto model = CreateWaterFlow();
    CreateItemsInRepeat(50, [](int32_t i) { return i % 2 ? 100.0f : 200.0f; });
    model.SetCachedCount(3, true);
    model.SetColumnsTemplate("1fr 1fr");
    model.SetRowsGap(Dimension(10));
    model.SetColumnsGap(Dimension(10));
    CreateDone();

    ASSERT_TRUE(GetChildFrameNode(frameNode_, 13));
    EXPECT_EQ(GetChildY(frameNode_, 13), 960.0f);
    EXPECT_EQ(GetChildX(frameNode_, 13), 245.0f);

    UpdateCurrentOffset(-300.0f);
    EXPECT_EQ(GetChildY(frameNode_, 0), -300.0f);

    layoutProperty_->UpdateColumnsTemplate("1fr");
    FlushUITasks();
    const auto info = pattern_->layoutInfo_;
    EXPECT_EQ(info->startIndex_, 2);
    EXPECT_EQ(info->endIndex_, 8);
    EXPECT_EQ(GetChildWidth(frameNode_, 1), 480.0f);
    EXPECT_EQ(GetChildWidth(frameNode_, 10), 480.0f);
    EXPECT_EQ(GetChildY(frameNode_, 10), 1090.0f);
    EXPECT_EQ(GetChildY(frameNode_, 0), -510.0f);

    UpdateCurrentOffset(-50.0f);
    EXPECT_EQ(GetChildY(frameNode_, 0), -560.0f);
    EXPECT_EQ(GetChildY(frameNode_, 10), 1040.0f);
    EXPECT_EQ(GetChildLayoutProperty<LayoutProperty>(frameNode_, 0)->GetPropertyChangeFlag(), 0);
}

/**
 * @tc.name: Illegal004
 * @tc.desc: When the notification of Lazyforeach and section update doesn't come in one frame.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowSWTest, Illegal004, TestSize.Level1)
{
    CreateWaterFlow();
    ViewAbstract::SetWidth(CalcLength(400.0f));
    ViewAbstract::SetHeight(CalcLength(800.f));
    CreateWaterFlowItems(5);
    auto secObj = pattern_->GetOrCreateWaterFlowSections();
    secObj->ChangeData(0, 0, SECTION_13);
    CreateDone();

    EXPECT_EQ(info_->startIndex_, 0);
    EXPECT_EQ(info_->endIndex_, 4);
    EXPECT_EQ(info_->maxHeight_, 500);
    // lazyforeach notification comes first.
    for (int i = 3; i <= 4; ++i) {
        frameNode_->RemoveChildAtIndex(3);
    }
    frameNode_->ChildrenUpdatedFrom(3);
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    FlushUITasks();
    // IsSectionValid() is false, stop measure and layout.
    EXPECT_EQ(info_->maxHeight_, 500);
    EXPECT_EQ(info_->startIndex_, 0);
    EXPECT_EQ(info_->endIndex_, 4);
    // if IsSectionValid() is false, remain the ChildrenUpdatedFrom.
    EXPECT_EQ(frameNode_->GetChildrenUpdated(), 3);

    // section update comes in next frame.
    std::vector<WaterFlowSections::Section> newSection = { WaterFlowSections::Section {
                                                               .itemsCount = 2, .crossCount = 2 },
        WaterFlowSections::Section { .itemsCount = 1, .crossCount = 2 } };
    secObj->ChangeData(0, 3, newSection);
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    EXPECT_EQ(frameNode_->GetChildrenUpdated(), 3);

    FlushUITasks();
    EXPECT_EQ(info_->startIndex_, 0);
    EXPECT_EQ(info_->endIndex_, 2);
    EXPECT_EQ(info_->maxHeight_, 300);
    EXPECT_EQ(info_->lanes_[0][0].ToString(), "{StartPos: 0.000000 EndPos: 100.000000 Items [0 ] }");
    EXPECT_EQ(info_->lanes_[0][1].ToString(), "{StartPos: 0.000000 EndPos: 200.000000 Items [1 ] }");
    EXPECT_EQ(info_->lanes_[1][0].ToString(), "{StartPos: 200.000000 EndPos: 300.000000 Items [2 ] }");
    EXPECT_EQ(info_->lanes_[1][1].ToString(), "{StartPos: 200.000000 EndPos: 200.000000 empty}");
    EXPECT_EQ(info_->idxToLane_.size(), 3);
    EXPECT_FALSE(info_->idxToLane_.count(3));
}

/**
 * @tc.name: Illegal005
 * @tc.desc: test in the middle When the notification of Lazyforeach and section update doesn't come in one frame.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowSWTest, Illegal005, TestSize.Level1)
{
    CreateWaterFlow();
    ViewAbstract::SetWidth(CalcLength(400.0f));
    ViewAbstract::SetHeight(CalcLength(800.f));
    RefPtr<WaterFlowMockLazy> mockLazy = CreateItemsInLazyForEach(37, [](int32_t) { return 100.0f; });
    auto secObj = pattern_->GetOrCreateWaterFlowSections();
    secObj->ChangeData(0, 0, SECTION_14);
    CreateDone();

    EXPECT_EQ(info_->startIndex_, 0);
    EXPECT_EQ(info_->endIndex_, 14);

    // test in the middle position.
    pattern_->ScrollToIndex(19, false, ScrollAlign::START);
    FlushUITasks();
    EXPECT_EQ(info_->startIndex_, 19);
    EXPECT_EQ(info_->endIndex_, 26);
    DeleteItemInLazyForEach(16);
    EXPECT_EQ(frameNode_->GetChildrenUpdated(), 16);
    mockLazy->SetTotalCount(36);
    FlushUITasks();
    EXPECT_EQ(info_->startIndex_, 19);
    EXPECT_EQ(info_->endIndex_, 26);
    EXPECT_EQ(frameNode_->GetTotalChildCount(), 36);
    EXPECT_EQ(info_->segmentTails_.size(), 3);
    EXPECT_EQ(info_->segmentTails_.back(), 36);

    std::vector<WaterFlowSections::Section> newSection = {
        WaterFlowSections::Section{.itemsCount = 19, .crossCount = 1}};
    secObj->ChangeData(1, 1, newSection);
    EXPECT_EQ(frameNode_->GetChildrenUpdated(), 16);
    FlushUITasks();

    EXPECT_EQ(info_->startIndex_, 18);
    EXPECT_EQ(info_->endIndex_, 25);
    EXPECT_EQ(frameNode_->GetTotalChildCount(), 36);
    EXPECT_EQ(secObj->GetSectionInfo()[1].itemsCount, 19);
    EXPECT_EQ(info_->segmentTails_.back(), 35);

    EXPECT_EQ(
        info_->lanes_[0][0].ToString(), "{StartPos: 0.000000 EndPos: 0.000000 empty}");
    EXPECT_EQ(
        info_->lanes_[1][0].ToString(), "{StartPos: 0.000000 EndPos: 800.000000 Items [18 19 20 21 22 23 24 25 ] }");
    EXPECT_EQ(info_->idxToLane_.size(), 8);
}

/**
 * @tc.name: EdgeEffect001
 * @tc.desc: only have footer, test Spring EdgeEffect.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowSWTest, EdgeEffect001, TestSize.Level1)
{
    auto model = CreateWaterFlow();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetEdgeEffect(EdgeEffect::SPRING, true, EffectEdge::START);
    model.SetFooter(GetDefaultHeaderBuilder());
    CreateDone();

    EXPECT_EQ(pattern_->layoutInfo_->GetContentHeight(), 50.0f);
    EXPECT_FLOAT_EQ(GetChildY(frameNode_, 0), 0);

    GestureEvent gesture;
    gesture.SetInputEventType(InputEventType::TOUCH_SCREEN);
    gesture.SetMainVelocity(1000.0f);
    gesture.SetMainDelta(100.0f);
    auto scrollable = pattern_->GetScrollableEvent()->GetScrollable();
    ASSERT_TRUE(scrollable);
    scrollable->HandleTouchDown();
    scrollable->HandleDragStart(gesture);
    scrollable->HandleDragUpdate(gesture);
    FlushUITasks();
    EXPECT_FLOAT_EQ(GetChildY(frameNode_, 0), 1.720595);
    MockAnimationManager::GetInstance().SetTicks(2);
    scrollable->HandleTouchUp();
    scrollable->HandleDragEnd(gesture);
    FlushUITasks();
    EXPECT_FLOAT_EQ(GetChildY(frameNode_, 0), 3.4597926);

    MockAnimationManager::GetInstance().Tick();
    FlushUITasks();
    EXPECT_FLOAT_EQ(GetChildY(frameNode_, 0), 1.7298963);
    MockAnimationManager::GetInstance().Tick();
    FlushUITasks();
    EXPECT_FLOAT_EQ(GetChildY(frameNode_, 0), 0);
}

/**
 * @tc.name: UpdateAndJump001
 * @tc.desc: call ScrollToIndex after updating sections.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowSWTest, UpdateAndJump001, TestSize.Level1)
{
    CreateWaterFlow();
    ViewAbstract::SetWidth(CalcLength(400.0f));
    ViewAbstract::SetHeight(CalcLength(1000.f));
    CreateWaterFlowItems(32);
    auto secObj = pattern_->GetOrCreateWaterFlowSections();
    secObj->ChangeData(0, 0, SECTION_15);
    CreateDone();

    EXPECT_EQ(info_->startIndex_, 0);
    EXPECT_EQ(info_->endIndex_, 7);

    std::vector<WaterFlowSections::Section> newSection = { WaterFlowSections::Section {
        .itemsCount = 8, .crossCount = 2, .onGetItemMainSizeByIndex = GET_MAIN_SIZE_FUNC } };
    secObj->ChangeData(1, 1, newSection);
    layoutProperty_->UpdateUserDefinedIdealSize(CalcSize(CalcLength(300.0f), CalcLength(Dimension(1000.0f))));
    pattern_->ScrollToIndex(8, false, ScrollAlign::START);
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    FlushUITasks();

    EXPECT_EQ(info_->startIndex_, 7);
    EXPECT_EQ(info_->endIndex_, 16);
    EXPECT_EQ(info_->lanes_[0][0].ToString(), "{StartPos: -200.000000 EndPos: -200.000000 empty}");
    EXPECT_EQ(info_->lanes_[0][1].ToString(), "{StartPos: -400.000000 EndPos: -400.000000 empty}");
    EXPECT_EQ(info_->lanes_[1][0].ToString(), "{StartPos: 0.000000 EndPos: 500.000000 Items [7 10 11 ] }");
    EXPECT_EQ(info_->lanes_[1][1].ToString(), "{StartPos: 0.000000 EndPos: 300.000000 Items [8 9 ] }");
    EXPECT_EQ(info_->lanes_[2][0].ToString(), "{StartPos: 500.000000 EndPos: 900.000000 Items [12 14 15 ] }");
    EXPECT_EQ(info_->lanes_[2][1].ToString(), "{StartPos: 500.000000 EndPos: 700.000000 Items [13 ] }");
}

/**
 * @tc.name: WaterFlowSWReMeasureTest001
 * @tc.desc: Test WaterFlow sliding window selective clearing mechanism
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowSWTest, WaterFlowSWReMeasureTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create WaterFlow with sliding window
     * @tc.expected: WaterFlow index range is correct
     */
    WaterFlowModelNG model = CreateWaterFlow();
    model.SetColumnsTemplate("1fr 1fr");
    CreateWaterFlowItems(20);
    CreateDone();

    /**
     * @tc.steps: step2. Call measure of WaterFlow for first time
     * @tc.expected: WaterFlow layout range is correct, layouted is false
     */
    auto layoutAlgorithm = AceType::DynamicCast<WaterFlowLayoutSW>(pattern_->CreateLayoutAlgorithm());
    EXPECT_TRUE(layoutAlgorithm);
    layoutAlgorithm->Measure(AceType::RawPtr(frameNode_));
    EXPECT_FALSE(layoutAlgorithm->isLayouted_);

    // Record initial index range
    int32_t initialStartIndex = layoutAlgorithm->info_->StartIndex();
    int32_t initialEndIndex = layoutAlgorithm->info_->EndIndex();

    /**
     * @tc.steps: step3. Change WaterFlow mainSize and call measure for second time
     * @tc.expected: Check selective clearing mechanism works with index-based approach
     */
    LayoutConstraintF contentConstraint;
    contentConstraint.selfIdealSize = OptionalSizeF(240.f, 200.f);
    contentConstraint.maxSize = SizeF(240.f, 200.f);
    contentConstraint.percentReference = SizeF(240.f, 200.f);

    layoutProperty_->UpdateLayoutConstraint(contentConstraint);

    // Verify that prevStartIndex_ and prevEndIndex_ are set correctly before measure
    layoutAlgorithm->Measure(AceType::RawPtr(frameNode_));

    // Verify index range has changed
    int32_t newStartIndex = layoutAlgorithm->info_->StartIndex();
    int32_t newEndIndex = layoutAlgorithm->info_->EndIndex();

    // Verify that the selective clearing mechanism uses real-time indices correctly
    EXPECT_TRUE(newStartIndex != initialStartIndex || newEndIndex != initialEndIndex);

    // Complete layout to trigger ClearUnlayoutedItems
    layoutAlgorithm->Layout(AceType::RawPtr(frameNode_));
    EXPECT_TRUE(layoutAlgorithm->isLayouted_);
}
} // namespace OHOS::Ace::NG
