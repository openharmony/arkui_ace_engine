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

#include "water_flow_test_ng.h"

#include "core/components_ng/property/property.h"
#include "core/components_ng/syntax/if_else_node.h"

namespace OHOS::Ace::NG {
// TEST non-segmented layout

/**
 * @tc.name: OffsetEnd001
 * @tc.desc: Check OffsetEnd value with footer
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, OffsetEnd001, TestSize.Level1)
{
    WaterFlowModelNG model = CreateWaterFlow();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetFooter(GetDefaultHeaderBuilder());
    model.SetRowsGap(Dimension(5.0f));
    CreateWaterFlowItems(30);
    CreateDone();
    auto info = pattern_->layoutInfo_;
    EXPECT_EQ(info->startIndex_, 0);
    EXPECT_EQ(info->endIndex_, 10);
    pattern_->ScrollToIndex(29, false, ScrollAlign::END);
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
    EXPECT_TRUE(info->ReachEnd(50.0f, false));

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
    WaterFlowModelNG model = CreateWaterFlow();
    model.SetFooter(GetDefaultHeaderBuilder());
    model.SetColumnsTemplate("1fr 1fr");
    CreateWaterFlowItems(100);
    CreateDone();
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
    WaterFlowModelNG model = CreateWaterFlow();
    ViewAbstract::SetWidth(CalcLength(400.0f));
    ViewAbstract::SetHeight(CalcLength(600.f));
    model.SetColumnsTemplate("1fr 1fr");
    CreateWaterFlowItems(60);
    CreateDone();

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

/**
 * @tc.name: ChangeFooter001
 * @tc.desc: Test changing the footer of the WaterFlow layout.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, ChangeFooter001, TestSize.Level1)
{
    WaterFlowModelNG model = CreateWaterFlow();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetFooter(GetDefaultHeaderBuilder());
    CreateWaterFlowItems(60);
    CreateDone();

    pattern_->ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, false);
    FlushLayoutTask(frameNode_);
    auto& info = pattern_->layoutInfo_;
    EXPECT_EQ(info->footerIndex_, 0);
    EXPECT_EQ(frameNode_->GetTotalChildCount(), 61);
    EXPECT_EQ(GetChildY(frameNode_, 0), 750.0f);
    EXPECT_EQ(GetChildY(frameNode_, 60), 550.0f);
    EXPECT_EQ(info->endIndex_, 59);

    auto ifNode = IfElseNode::GetOrCreateIfElseNode(-1);

    pattern_->AddFooter(ifNode);
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(info->footerIndex_, -1);
    EXPECT_EQ(frameNode_->GetTotalChildCount(), 60);
    EXPECT_EQ(GetChildY(frameNode_, 59), 600.0f);
    EXPECT_FALSE(GetChildFrameNode(frameNode_, 0)->IsActive());
}

/**
 * @tc.name: IllegalItemCnt
 * @tc.desc: Layout WaterFlow without items.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, IllegalItemCnt, TestSize.Level1)
{
    WaterFlowModelNG model = CreateWaterFlow();
    ViewAbstract::SetWidth(CalcLength(400.0f));
    ViewAbstract::SetHeight(CalcLength(600.f));
    model.SetColumnsTemplate("1fr 1fr");
    CreateWaterFlowItems(6);
    CreateDone();
    const auto& info = pattern_->layoutInfo_;
    EXPECT_EQ(info->endIndex_, 5);

    for (int i = 0; i < 6; ++i) {
        frameNode_->RemoveChildAtIndex(0);
    }
    frameNode_->childrenUpdatedFrom_ = 0;
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_CHILD);
    FlushLayoutTask(frameNode_);

    pattern_->ScrollToIndex(LAST_ITEM);
    EXPECT_EQ(info->jumpIndex_, LAST_ITEM);
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(info->startIndex_ >= info->endIndex_);
}

/**
 * @tc.name: ZeroHeightItem001
 * @tc.desc: Layout WaterFlow with 0-height item.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, ZeroHeightItem001, TestSize.Level1)
{
    WaterFlowModelNG model = CreateWaterFlow();
    ViewAbstract::SetWidth(CalcLength(400.0f));
    ViewAbstract::SetHeight(CalcLength(600.f));
    model.SetColumnsTemplate("1fr 1fr");
    model.SetRowsGap(Dimension(5.0f));
    model.SetEdgeEffect(EdgeEffect::SPRING, false);
    CreateItemWithHeight(0.0f);
    CreateItemWithHeight(100.0f);
    CreateItemWithHeight(100.0f);
    CreateDone();
    const auto& info = pattern_->layoutInfo_;
    EXPECT_EQ(info->startIndex_, 0);
    EXPECT_EQ(info->endIndex_, 2);
    EXPECT_EQ(GetChildY(frameNode_, 0), 0.0f);
    EXPECT_EQ(GetChildY(frameNode_, 1), 0.0f);
    EXPECT_EQ(GetChildY(frameNode_, 2), 5.0f);

    pattern_->SetAnimateCanOverScroll(true);
    UpdateCurrentOffset(100.0f); // shouldn't move
    EXPECT_EQ(GetChildY(frameNode_, 0), 0.0f);
    EXPECT_EQ(GetChildY(frameNode_, 1), 0.0f);
    EXPECT_EQ(GetChildY(frameNode_, 2), 5.0f);

    UpdateCurrentOffset(-100.0f); // shouldn't move
    EXPECT_EQ(GetChildY(frameNode_, 0), 0.0f);
    EXPECT_EQ(GetChildY(frameNode_, 1), 0.0f);
    EXPECT_EQ(GetChildY(frameNode_, 2), 5.0f);
}

/**
 * @tc.name: ZeroHeightItem002
 * @tc.desc: Layout WaterFlow with 0-height item at the bottom.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, ZeroHeightItem002, TestSize.Level1)
{
    WaterFlowModelNG model = CreateWaterFlow();
    model.SetColumnsTemplate("1fr");
    model.SetEdgeEffect(EdgeEffect::SPRING, false);
    for (int i = 0; i < 5; ++i) {
        CreateItemWithHeight(100.0f);
    }
    CreateItemWithHeight(0.0f);
    CreateDone();
    const auto& info = pattern_->layoutInfo_;
    EXPECT_EQ(info->startIndex_, 0);
    EXPECT_EQ(info->endIndex_, 5);
    EXPECT_EQ(GetChildY(frameNode_, 0), 0.0f);
    EXPECT_EQ(GetChildY(frameNode_, 5), 500.0f);

    pattern_->SetAnimateCanOverScroll(true);
    UpdateCurrentOffset(100.0f); // shouldn't move
    EXPECT_EQ(GetChildY(frameNode_, 0), 0.0f);
    EXPECT_EQ(GetChildY(frameNode_, 5), 500.0f);

    UpdateCurrentOffset(-100.0f); // shouldn't move
    EXPECT_EQ(GetChildY(frameNode_, 0), 0.0f);
    EXPECT_EQ(GetChildY(frameNode_, 5), 500.0f);
}

/**
 * @tc.name: Property014
 * @tc.desc: Test the property of itemConstraintSize.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, Property014, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create waterFlow.
     */
    WaterFlowModelNG model;
    model.Create();
    ViewAbstract::SetWidth(CalcLength(WATER_FLOW_WIDTH));
    ViewAbstract::SetHeight(CalcLength(WATER_FLOW_HEIGHT));
    model.SetScroller(model.CreateScrollController(), model.CreateScrollBarProxy());
    GetWaterFlow();
    CreateWaterFlowItems(TOTAL_LINE_NUMBER);
    FlushLayoutTask(frameNode_);
    EXPECT_FALSE(layoutProperty_->HasItemLayoutConstraint());
    EXPECT_EQ(model.GetItemMinWidth(AceType::RawPtr(frameNode_)), Dimension(0.f));
    EXPECT_EQ(model.GetItemMaxWidth(AceType::RawPtr(frameNode_)), Dimension(0.f));
    EXPECT_EQ(model.GetItemMinHeight(AceType::RawPtr(frameNode_)), Dimension(0.f));
    EXPECT_EQ(model.GetItemMaxHeight(AceType::RawPtr(frameNode_)), Dimension(0.f));
    for (int32_t i = 0; i < 2; ++i) {
        Rect rect = pattern_->GetItemRect(i);
        EXPECT_EQ(rect.Width(), WATER_FLOW_WIDTH);
        EXPECT_EQ(rect.Height(), i == 0 ? ITEM_MAIN_SIZE : BIG_ITEM_MAIN_SIZE);
    }

    /**
     * @tc.steps: step2. set minWidth and maxWidth.
     * @tc.expected: the value between minWidth and maxWidth.
     */
    model.SetItemMinWidth(AceType::RawPtr(frameNode_), Dimension(300.f));
    model.SetItemMaxWidth(AceType::RawPtr(frameNode_), Dimension(400.f));
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(layoutProperty_->HasItemLayoutConstraint());
    EXPECT_EQ(model.GetItemMinWidth(AceType::RawPtr(frameNode_)), Dimension(300.f));
    EXPECT_EQ(model.GetItemMaxWidth(AceType::RawPtr(frameNode_)), Dimension(400.f));
    EXPECT_EQ(model.GetItemMinHeight(AceType::RawPtr(frameNode_)), Dimension(0.f));
    EXPECT_EQ(model.GetItemMaxHeight(AceType::RawPtr(frameNode_)), Dimension(0.f));
    Rect rect = pattern_->GetItemRect(0);
    EXPECT_GE(rect.Width(), 300.f);
    EXPECT_LE(rect.Width(), 400.f);

    /**
     * @tc.steps: step3. set minHeight and maxHeight.
     * @tc.expected: the value between minHeight and maxHeight.
     */
    layoutProperty_->Reset();
    model.SetItemMinHeight(AceType::RawPtr(frameNode_), Dimension(150.f));
    model.SetItemMaxHeight(AceType::RawPtr(frameNode_), Dimension(250.f));
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(layoutProperty_->HasItemLayoutConstraint());
    EXPECT_EQ(model.GetItemMinWidth(AceType::RawPtr(frameNode_)), Dimension(0.f));
    EXPECT_EQ(model.GetItemMaxWidth(AceType::RawPtr(frameNode_)), Dimension(0.f));
    EXPECT_EQ(model.GetItemMinHeight(AceType::RawPtr(frameNode_)), Dimension(150.f));
    EXPECT_EQ(model.GetItemMaxHeight(AceType::RawPtr(frameNode_)), Dimension(250.f));
    for (int32_t i = 0; i < 2; ++i) {
        rect = pattern_->GetItemRect(i);
        EXPECT_GE(rect.Height(), 150.f);
        EXPECT_LE(rect.Height(), 250.f);
    }
}

/**
 * @tc.name: Cache003
 * @tc.desc: Test cache item with footer
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, Cache003, TestSize.Level1)
{
    auto model = CreateWaterFlow();
    model.SetFooter(GetDefaultHeaderBuilder());
    CreateItemsInRepeat(50, [](int32_t i) { return i % 2 ? 100.0f : 200.0f; });

    model.SetCachedCount(3);
    model.SetColumnsTemplate("1fr 1fr 1fr");
    model.SetRowsGap(Dimension(10));
    model.SetColumnsGap(Dimension(10));
    CreateDone();
    EXPECT_EQ(frameNode_->GetTotalChildCount(), 51);
    ASSERT_TRUE(GetChildFrameNode(frameNode_, 0));
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    FlushLayoutTask(frameNode_);
    auto info = pattern_->layoutInfo_;
    EXPECT_EQ(info->startIndex_, 0);
    EXPECT_EQ(info->endIndex_, 15);

    const std::list<int32_t> preloadList = { 16, 17, 18 };
    EXPECT_FALSE(GetChildFrameNode(frameNode_, 17));
    EXPECT_EQ(pattern_->preloadItems_, preloadList);
    EXPECT_TRUE(pattern_->cacheLayout_);
    PipelineContext::GetCurrentContext()->OnIdle(INT64_MAX);
    EXPECT_TRUE(pattern_->preloadItems_.empty());
    EXPECT_TRUE(GetChildFrameNode(frameNode_, 17));
    EXPECT_EQ(GetChildHeight(frameNode_, 17), 200.0f);
    EXPECT_EQ(layoutProperty_->propertyChangeFlag_, PROPERTY_UPDATE_LAYOUT);

    UpdateCurrentOffset(-Infinity<float>());
    EXPECT_EQ(info->startIndex_, 36);
    EXPECT_EQ(info->endIndex_, 49);
    EXPECT_TRUE(pattern_->preloadItems_.empty());
    EXPECT_EQ(GetChildY(frameNode_, 36), -140.0f);
    EXPECT_EQ(GetChildY(frameNode_, 35), -250.0f);
    EXPECT_EQ(GetChildY(frameNode_, 34), -250.0f);
}
} // namespace OHOS::Ace::NG