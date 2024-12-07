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

#include "core/components_ng/syntax/if_else_node.h"

#define protected public
#define private public
#include "core/components_ng/pattern/waterflow/layout/sliding_window/water_flow_layout_sw.h"
#include "core/components_ng/pattern/waterflow/layout/top_down/water_flow_layout_algorithm.h"
#undef protected
#undef private

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
 * @tc.name: ScrollToEdge006
 * @tc.desc: Test ScrollToEdge with footer and OffsetEnd
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, ScrollToEdge006, TestSize.Level1)
{
    bool isReachEndCalled = false;
    auto reachEnd = [&isReachEndCalled]() { isReachEndCalled = true; };
    WaterFlowModelNG model = CreateWaterFlow();
    model.SetFooter(GetDefaultHeaderBuilder());
    model.SetColumnsTemplate("1fr 1fr 1fr");
    model.SetOnReachEnd(reachEnd);
    CreateWaterFlowItems(100);
    CreateDone();

    pattern_->ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, false);
    FlushLayoutTask(frameNode_);
    auto info = pattern_->layoutInfo_;
    EXPECT_EQ(info->endIndex_, 99);
    EXPECT_EQ(GetChildY(frameNode_, 100), 550.0f);
    EXPECT_EQ(GetChildOffset(frameNode_, info->footerIndex_), OffsetF(0.0f, 750.0f));
    EXPECT_TRUE(info->offsetEnd_);
    EXPECT_TRUE(isReachEndCalled);
}

/**
 * @tc.name: ScrollToEdge007
 * @tc.desc: Test ScrollToEdge with footer and OffsetEnd
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, ScrollToEdge007, TestSize.Level1)
{
    bool isReachEndCalled = false;
    auto reachEnd = [&isReachEndCalled]() { isReachEndCalled = true; };
    WaterFlowModelNG model = CreateWaterFlow();
    model.SetFooter(GetDefaultHeaderBuilder());
    model.SetColumnsTemplate("1fr 1fr 1fr");
    model.SetOnReachEnd(reachEnd);
    CreateWaterFlowItems(3);
    CreateDone();

    pattern_->ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, false);
    FlushLayoutTask(frameNode_);
    auto info = pattern_->layoutInfo_;
    EXPECT_EQ(info->endIndex_, 2);
    EXPECT_EQ(GetChildY(frameNode_, 3), 0.0f);
    EXPECT_TRUE(info->itemStart_);
    EXPECT_TRUE(info->offsetEnd_);
    EXPECT_FALSE(isReachEndCalled);
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
    bool isReachEndCalled = false;
    auto reachEnd = [&isReachEndCalled]() { isReachEndCalled = true; };
    WaterFlowModelNG model = CreateWaterFlow();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetFooter(GetDefaultHeaderBuilder());
    model.SetOnReachEnd(reachEnd);
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
    EXPECT_TRUE(info->offsetEnd_);
    EXPECT_TRUE(isReachEndCalled);

    isReachEndCalled = false;
    auto ifNode = IfElseNode::GetOrCreateIfElseNode(-1);

    pattern_->AddFooter(ifNode);
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(info->footerIndex_, -1);
    EXPECT_EQ(frameNode_->GetTotalChildCount(), 60);
    EXPECT_EQ(GetChildY(frameNode_, 59), 600.0f);
    EXPECT_FALSE(GetChildFrameNode(frameNode_, 0)->IsActive());
    EXPECT_TRUE(info->offsetEnd_);
    EXPECT_TRUE(isReachEndCalled);
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
    CreateDone();
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

/**
 * @tc.name: CacheScroll001
 * @tc.desc: Layout WaterFlow cache items
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, CacheScroll001, TestSize.Level1)
{
    auto model = CreateWaterFlow();
    model.SetCachedCount(10);
    model.SetRowsGap(Dimension(10));
    model.SetColumnsGap(Dimension(10));
    CreateItemsInLazyForEach(100, [](int32_t) { return 100.0f; });
    CreateDone();
    frameNode_->AttachToMainTree(true, PipelineContext::GetCurrentContextPtrSafely());

    UpdateCurrentOffset(-2000.0f);
    EXPECT_EQ(pattern_->layoutInfo_->startIndex_, 18);
    EXPECT_EQ(pattern_->layoutInfo_->endIndex_, 25);
    EXPECT_EQ(GetChildY(frameNode_, 18), -20.0f);
    PipelineContext::GetCurrentContext()->OnIdle(INT64_MAX);
    EXPECT_TRUE(GetChildFrameNode(frameNode_, 8));
    EXPECT_FALSE(GetChildFrameNode(frameNode_, 7));

    UpdateCurrentOffset(200.0f);
    EXPECT_EQ(pattern_->layoutInfo_->startIndex_, 16);
    EXPECT_EQ(pattern_->layoutInfo_->endIndex_, 23);
    EXPECT_FALSE(GetChildFrameNode(frameNode_, 7));
    EXPECT_EQ(GetChildY(frameNode_, 18), 180.0f);
    EXPECT_TRUE(GetItem(18)->IsOnMainTree());

    PipelineContext::GetCurrentContext()->OnIdle(INT64_MAX);
    ASSERT_TRUE(GetItem(7, true));
    EXPECT_FALSE(GetItem(7, true)->IsOnMainTree());
    EXPECT_EQ(GetItem(7, true)->GetLayoutProperty()->GetPropertyChangeFlag() & PROPERTY_UPDATE_MEASURE,
        PROPERTY_UPDATE_MEASURE);
    UpdateCurrentOffset(5.0f);
    EXPECT_FALSE(GetItem(7, true)->IsOnMainTree());
    EXPECT_EQ(GetChildLayoutProperty<LayoutProperty>(frameNode_, 7)->GetPropertyChangeFlag() & PROPERTY_UPDATE_MEASURE,
        PROPERTY_UPDATE_MEASURE);
}

/**
 * @tc.name: Remeasure001
 * @tc.desc: Test triggering measure multiple times on the same Algo object
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, Remeasure001, TestSize.Level1)
{
    WaterFlowModelNG model = CreateWaterFlow();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetCachedCount(3);
    CreateItemsInRepeat(50, [](int32_t i) { return i % 2 ? 100.0f : 200.0f; });
    CreateDone();

    auto algo = pattern_->GetCacheLayoutAlgo();
    ASSERT_TRUE(algo);
    algo->Measure(AceType::RawPtr(frameNode_));
    if (auto swAlgo = AceType::DynamicCast<WaterFlowLayoutSW>(algo); swAlgo) {
        EXPECT_EQ(swAlgo->itemsCrossSize_[0].size(), 2);
    } else {
        EXPECT_EQ(AceType::DynamicCast<WaterFlowLayoutAlgorithm>(algo)->itemsCrossSize_.size(), 2);
    }
}

/**
 * @tc.name: ShowCachedItems001
 * @tc.desc: Test show cached items
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, ShowCachedItems001, TestSize.Level1)
{
    WaterFlowModelNG model = CreateWaterFlow();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetFooter(GetDefaultHeaderBuilder());
    model.SetCachedCount(3, true);
    CreateItemsInRepeat(50, [](int32_t i) { return i % 2 ? 100.0f : 200.0f; });
    CreateDone();
    EXPECT_EQ(pattern_->layoutInfo_->endIndex_, 10);
    ASSERT_TRUE(GetChildFrameNode(frameNode_, 12));
    EXPECT_FALSE(GetChildFrameNode(frameNode_, 0)->IsActive()); // footer
    EXPECT_TRUE(GetChildFrameNode(frameNode_, 12)->IsActive());
    EXPECT_EQ(GetChildY(frameNode_, 12), 800.0f);
    // check if ::Layout is called
    EXPECT_EQ(GetChildLayoutProperty<LayoutProperty>(frameNode_, 12)->GetPropertyChangeFlag(), 0);
}

/**
 * @tc.name: ScrollToIndex001
 * @tc.desc: Test the range of ScrollToIndex when has footer.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, ScrollToIndex001, TestSize.Level1)
{
    WaterFlowModelNG model = CreateWaterFlow();
    model.SetFooter(GetDefaultHeaderBuilder());
    CreateWaterFlowItems(30);
    CreateDone();

    pattern_->ScrollToIndex(29, false, ScrollAlign::END);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->layoutInfo_->startIndex_, 25);
    EXPECT_EQ(GetChildY(frameNode_, 26), 0.0f);
    EXPECT_TRUE(GetChildFrameNode(frameNode_, 0)->IsActive());

    pattern_->ScrollToIndex(0, false);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->layoutInfo_->startIndex_, 0);
    EXPECT_EQ(GetChildY(frameNode_, 1), 0.0f);
    EXPECT_FALSE(GetChildFrameNode(frameNode_, 0)->IsActive());

    /**
     * @tc.steps: step1. jump to 30, which is out of [0, 29].
     * @tc.expected: fail to jump.
     */
    pattern_->ScrollToIndex(30, false);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->layoutInfo_->startIndex_, 0);
    EXPECT_FALSE(GetChildFrameNode(frameNode_, 0)->IsActive());
    EXPECT_EQ(GetChildY(frameNode_, 1), 0.0f);

    /**
     * @tc.steps: step2. jump to LAST_ITEM, which will be used in scrollEdge.
     * @tc.expected: jump successfully, if has footer, jump to footer.
     */
    pattern_->ScrollToIndex(LAST_ITEM, false);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->layoutInfo_->startIndex_, 25);
    EXPECT_TRUE(GetChildFrameNode(frameNode_, 0)->IsActive());
    EXPECT_EQ(GetChildY(frameNode_, 26), -50.0f);
    EXPECT_EQ(GetChildY(frameNode_, 0), WATER_FLOW_HEIGHT - 50.0f);
}

/**
 * @tc.name: Delete003
 * @tc.desc: Test layout after deleting all items on the screen when has footer.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, Delete003, TestSize.Level1)
{
    WaterFlowModelNG model = CreateWaterFlow();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetFooter(GetDefaultHeaderBuilder());
    CreateWaterFlowItems(15);
    CreateDone();

    EXPECT_EQ(pattern_->layoutInfo_->startIndex_, 0);
    EXPECT_EQ(pattern_->layoutInfo_->endIndex_, 10);
    EXPECT_EQ(frameNode_->GetTotalChildCount(), 16);

    // delete all items.
    for (int i = 1; i < 16; ++i) {
        frameNode_->RemoveChildAtIndex(1);
        frameNode_->ChildrenUpdatedFrom(1);
    }
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    FlushLayoutTask(frameNode_);

    EXPECT_EQ(frameNode_->GetTotalChildCount(), 1);
    // layout footer.
    EXPECT_TRUE(GetChildFrameNode(frameNode_, 0)->IsActive());
    EXPECT_EQ(GetChildRect(frameNode_, 0).Bottom(), 50.0f);
}

/**
 * @tc.name: Jump002
 * @tc.desc: Test jump function after changing dataSource.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, Jump002, TestSize.Level1)
{
    auto model = CreateWaterFlow();
    model.SetCachedCount(10);
    model.SetRowsGap(Dimension(10));
    model.SetColumnsGap(Dimension(10));
    CreateWaterFlowItems(100);
    CreateDone();

    UpdateCurrentOffset(-2000.0f);
    EXPECT_EQ(pattern_->layoutInfo_->startIndex_, 12);
    EXPECT_EQ(pattern_->layoutInfo_->endIndex_, 17);

    AddItemsAtSlot(1, 100.0f, 14);
    frameNode_->ChildrenUpdatedFrom(12);
    pattern_->ScrollToIndex(14, false, ScrollAlign::START);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->layoutInfo_->startIndex_, 14);
    EXPECT_EQ(pattern_->layoutInfo_->endIndex_, 19);

    AddItemsAtSlot(1, 100.0f, 40);
    frameNode_->ChildrenUpdatedFrom(45);
    pattern_->ScrollToIndex(45, false, ScrollAlign::START);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->layoutInfo_->startIndex_, 45);
    EXPECT_EQ(pattern_->layoutInfo_->endIndex_, 49);

    AddItemsAtSlot(1, 100.0f, 100);
    frameNode_->ChildrenUpdatedFrom(100);
    pattern_->ScrollToIndex(101, false, ScrollAlign::START);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->layoutInfo_->startIndex_, 97);
    EXPECT_EQ(pattern_->layoutInfo_->endIndex_, 102);

    AddItemsAtSlot(1, 100.0f, 0);
    frameNode_->ChildrenUpdatedFrom(0);
    pattern_->ScrollToIndex(0, false, ScrollAlign::START);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->layoutInfo_->startIndex_, 0);
    EXPECT_EQ(pattern_->layoutInfo_->endIndex_, 5);
}

/**
 * @tc.name: Jump003
 * @tc.desc: Test jump function after changing dataSource.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, Jump003, TestSize.Level1)
{
    auto model = CreateWaterFlow();
    model.SetCachedCount(10);
    model.SetRowsGap(Dimension(10));
    model.SetColumnsGap(Dimension(10));
    CreateWaterFlowItems(100);
    CreateDone();

    UpdateCurrentOffset(-2000.0f);
    EXPECT_EQ(pattern_->layoutInfo_->startIndex_, 12);
    EXPECT_EQ(pattern_->layoutInfo_->endIndex_, 17);

    frameNode_->RemoveChildAtIndex(12);
    frameNode_->ChildrenUpdatedFrom(12);
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    FlushLayoutTask(frameNode_);
    
    pattern_->ScrollToIndex(12, false, ScrollAlign::START);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->layoutInfo_->startIndex_, 12);
    EXPECT_EQ(pattern_->layoutInfo_->endIndex_, 16);

    pattern_->ScrollToIndex(60, false, ScrollAlign::START);
    FlushLayoutTask(frameNode_);

    for (int i = 22; i > 10; i--) {
        frameNode_->RemoveChildAtIndex(i);
        frameNode_->ChildrenUpdatedFrom(i);
    }
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    FlushLayoutTask(frameNode_);

    pattern_->ScrollToIndex(15, false, ScrollAlign::START);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->layoutInfo_->startIndex_, 15);
    EXPECT_EQ(pattern_->layoutInfo_->endIndex_, 20);
}

/**
 * @tc.name: LazyForEachJump001
 * @tc.desc: Test jump function after changing dataSource in lazyforeach.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, LazyForEachJump001, TestSize.Level1)
{
    auto model = CreateWaterFlow();
    model.SetCachedCount(10);
    CreateItemsInLazyForEach(100, [](int32_t) { return 100.0f; });
    CreateDone();

    AddItemInLazyForEach(1);
    FlushUITasks();
    EXPECT_EQ(pattern_->layoutInfo_->startIndex_, 0);
    EXPECT_EQ(pattern_->layoutInfo_->endIndex_, 7);
    EXPECT_EQ(GetChildY(frameNode_, 0), 0.0f);

    AddItemInLazyForEach(6);
    FlushUITasks();
    EXPECT_EQ(pattern_->layoutInfo_->startIndex_, 0);
    EXPECT_EQ(pattern_->layoutInfo_->endIndex_, 7);
    EXPECT_EQ(GetChildY(frameNode_, 6), 600.0f);
    pattern_->ScrollToIndex(6, false, ScrollAlign::START);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->layoutInfo_->startIndex_, 6);
    EXPECT_EQ(pattern_->layoutInfo_->endIndex_, 13);
    EXPECT_FALSE(GetItem(5, true)->IsOnMainTree());

    AddItemInLazyForEach(17);
    FlushUITasks();
    EXPECT_EQ(pattern_->layoutInfo_->startIndex_, 6);
    EXPECT_EQ(pattern_->layoutInfo_->endIndex_, 13);
    pattern_->ScrollToIndex(17, false, ScrollAlign::START);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->layoutInfo_->startIndex_, 17);
    EXPECT_EQ(pattern_->layoutInfo_->endIndex_, 24);
    EXPECT_EQ(GetChildY(frameNode_, 17), 0.0f);
    EXPECT_FALSE(GetItem(5, true)->IsOnMainTree());

    AddItemInLazyForEach(99);
    FlushUITasks();
    pattern_->ScrollToIndex(99, false, ScrollAlign::START);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->layoutInfo_->startIndex_, 92);
    EXPECT_EQ(pattern_->layoutInfo_->endIndex_, 99);
    EXPECT_EQ(frameNode_->GetTotalChildCount(), 100);
}

/**
 * @tc.name: LazyForEachJump002
 * @tc.desc: Test jump function after changing dataSource in lazyforeach.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, LazyForEachJump002, TestSize.Level1)
{
    auto model = CreateWaterFlow();
    model.SetCachedCount(10);
    RefPtr<WaterFlowMockLazy> mockLazy = CreateItemsInLazyForEach(100, [](int32_t) { return 100.0f; });
    CreateDone();
    frameNode_->AttachToMainTree(true, PipelineContext::GetCurrentContextPtrSafely());

    pattern_->ScrollToIndex(2, false, ScrollAlign::START);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->layoutInfo_->startIndex_, 2);
    EXPECT_EQ(pattern_->layoutInfo_->endIndex_, 9);

    DeleteItemInLazyForEach(58);
    mockLazy->SetTotalCount(99);
    FlushUITasks();
    pattern_->ScrollToIndex(58, false, ScrollAlign::START);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->layoutInfo_->startIndex_, 58);
    EXPECT_EQ(pattern_->layoutInfo_->endIndex_, 65);
    EXPECT_EQ(frameNode_->GetTotalChildCount(), 99);

    DeleteItemInLazyForEach(63);
    mockLazy->SetTotalCount(98);
    FlushUITasks();
    EXPECT_EQ(pattern_->layoutInfo_->startIndex_, 58);
    EXPECT_EQ(pattern_->layoutInfo_->endIndex_, 65);
    EXPECT_EQ(GetChildY(frameNode_, 58), 0.0f);
    pattern_->ScrollToIndex(60, false, ScrollAlign::START);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->layoutInfo_->startIndex_, 60);
    EXPECT_EQ(pattern_->layoutInfo_->endIndex_, 67);
    EXPECT_TRUE(GetItem(58, true)->IsOnMainTree());

    DeleteItemInLazyForEach(52);
    mockLazy->SetTotalCount(97);
    FlushUITasks();
    pattern_->ScrollToIndex(49, false, ScrollAlign::START);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->layoutInfo_->startIndex_, 49);
    EXPECT_EQ(pattern_->layoutInfo_->endIndex_, 56);

    DeleteItemInLazyForEach(0);
    mockLazy->SetTotalCount(96);
    FlushUITasks();
    pattern_->ScrollToIndex(0, false, ScrollAlign::START);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->layoutInfo_->startIndex_, 0);
    EXPECT_EQ(pattern_->layoutInfo_->endIndex_, 7);
    EXPECT_EQ(frameNode_->GetTotalChildCount(), 96);
}

/**
 * @tc.name: ScrollToEdge009
 * @tc.desc: scrollEdge to bottom from top and trigger reach end
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, ScrollToEdge009, TestSize.Level1)
{
    bool isReachEndCalled = false;
    auto reachEnd = [&isReachEndCalled]() { isReachEndCalled = true; };
    WaterFlowModelNG model = CreateWaterFlow();
    model.SetOnReachEnd(reachEnd);
    CreateWaterFlowItems(100);
    CreateDone();

    /**
     * @tc.steps: step1. scrollEdge to end
     */
    pattern_->ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, false);
    FlushLayoutTask(frameNode_);
    isReachEndCalled = false;

    /**
     * @tc.steps: step2. scrollEdge to top
     */
    pattern_->ScrollToEdge(ScrollEdgeType::SCROLL_TOP, false);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->layoutInfo_->Offset(), 0.0f);

    /**
     * @tc.steps: step3. scrollEdge to end again
     * @tc.expected: Trigger reach end
     */
    pattern_->ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, false);
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(isReachEndCalled);
    EXPECT_LE(pattern_->layoutInfo_->Offset(), -14200.0f);
}
} // namespace OHOS::Ace::NG
