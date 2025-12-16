/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "grid_test_ng.h"
#include "core/components_ng/pattern/scroll/scroll_edge_effect.h"
#include "test/mock/core/animation/mock_animation_manager.h"
#include "test/mock/core/common/mock_resource_adapter_v2.h"

namespace OHOS::Ace::NG {
class GridScrollerTestTwoNg : public GridTestNg, public testing::WithParamInterface<bool> {};

/**
 * @tc.name: GetOverScrollOffset001
 * @tc.desc: Test GetOverScrollOffset
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollerTestTwoNg, GetOverScrollOffset001, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetLayoutOptions({});
    CreateFixedItems(10);
    CreateDone();

    OverScrollOffset offset = pattern_->GetOverScrollOffset(ITEM_MAIN_SIZE);
    OverScrollOffset expectOffset = { ITEM_MAIN_SIZE, 0 };
    EXPECT_TRUE(IsEqual(offset, expectOffset));
    offset = pattern_->GetOverScrollOffset(0);
    expectOffset = { 0, 0 };
    EXPECT_TRUE(IsEqual(offset, expectOffset));
    offset = pattern_->GetOverScrollOffset(-ITEM_MAIN_SIZE);
    expectOffset = { 0, 0 };
    EXPECT_TRUE(IsEqual(offset, expectOffset));

    pattern_->info_.currentOffset_ = -ITEM_MAIN_SIZE;
    offset = pattern_->GetOverScrollOffset(ITEM_MAIN_SIZE * 2);
    expectOffset = { ITEM_MAIN_SIZE, 0 };
    EXPECT_TRUE(IsEqual(offset, expectOffset));
    offset = pattern_->GetOverScrollOffset(0);
    expectOffset = { 0, 0 };
    EXPECT_TRUE(IsEqual(offset, expectOffset));
    offset = pattern_->GetOverScrollOffset(-ITEM_MAIN_SIZE * 2);
    expectOffset = { 0, 0 };
    EXPECT_TRUE(IsEqual(offset, expectOffset));

    pattern_->info_.currentOffset_ = -ITEM_MAIN_SIZE * 2;
    offset = pattern_->GetOverScrollOffset(ITEM_MAIN_SIZE);
    expectOffset = { 0, 0 };
    EXPECT_TRUE(IsEqual(offset, expectOffset));
    offset = pattern_->GetOverScrollOffset(0);
    expectOffset = { 0, 0 };
    EXPECT_TRUE(IsEqual(offset, expectOffset));
    offset = pattern_->GetOverScrollOffset(-ITEM_MAIN_SIZE);
    expectOffset = { 0, 0 };
    EXPECT_TRUE(IsEqual(offset, expectOffset));

    pattern_->info_.currentOffset_ = ITEM_MAIN_SIZE;
    offset = pattern_->GetOverScrollOffset(ITEM_MAIN_SIZE);
    expectOffset = { ITEM_MAIN_SIZE, 0 };
    EXPECT_TRUE(IsEqual(offset, expectOffset));
    offset = pattern_->GetOverScrollOffset(0);
    expectOffset = { 0, 0 };
    EXPECT_TRUE(IsEqual(offset, expectOffset));
    offset = pattern_->GetOverScrollOffset(-ITEM_MAIN_SIZE * 2);
    expectOffset = { -ITEM_MAIN_SIZE, 0 };
    EXPECT_TRUE(IsEqual(offset, expectOffset));
}

/**
 * @tc.name: GetOverScrollOffset002
 * @tc.desc: Test GetOverScrollOffset
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollerTestTwoNg, GetOverScrollOffset002, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetLayoutOptions({});
    CreateFixedItems(10);
    CreateDone();
    
    pattern_->info_.currentOffset_ = -ITEM_MAIN_SIZE * 3;
    OverScrollOffset offset = pattern_->GetOverScrollOffset(ITEM_MAIN_SIZE * 2);
    OverScrollOffset expectOffset = { 0, 0 };
    EXPECT_TRUE(IsEqual(offset, expectOffset));
    offset = pattern_->GetOverScrollOffset(0);
    expectOffset = { 0, 0 };
    EXPECT_TRUE(IsEqual(offset, expectOffset));
    offset = pattern_->GetOverScrollOffset(-ITEM_MAIN_SIZE);
    expectOffset = { 0, 0 };
    EXPECT_TRUE(IsEqual(offset, expectOffset));
}

/**
 * @tc.name: GetOverScrollOffset003
 * @tc.desc: Test GetOverScrollOffset
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollerTestTwoNg, GetOverScrollOffset003, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    CreateFixedItems(8);
    CreateDone();

    OverScrollOffset offset = pattern_->GetOverScrollOffset(ITEM_MAIN_SIZE);
    OverScrollOffset expectOffset = { ITEM_MAIN_SIZE, 0 };
    EXPECT_TRUE(IsEqual(offset, expectOffset));
    offset = pattern_->GetOverScrollOffset(0);
    expectOffset = { 0, 0 };
    EXPECT_TRUE(IsEqual(offset, expectOffset));
    offset = pattern_->GetOverScrollOffset(-ITEM_MAIN_SIZE);
    expectOffset = { 0, -ITEM_MAIN_SIZE };
    EXPECT_TRUE(IsEqual(offset, expectOffset));

    pattern_->info_.currentOffset_ = -ITEM_MAIN_SIZE;
    offset = pattern_->GetOverScrollOffset(ITEM_MAIN_SIZE * 2);
    expectOffset = { ITEM_MAIN_SIZE, ITEM_MAIN_SIZE };
    EXPECT_TRUE(IsEqual(offset, expectOffset));
    offset = pattern_->GetOverScrollOffset(0);
    expectOffset = { 0, 0 };
    EXPECT_TRUE(IsEqual(offset, expectOffset));
    offset = pattern_->GetOverScrollOffset(-ITEM_MAIN_SIZE * 2);
    expectOffset = { 0, -ITEM_MAIN_SIZE * 2 };
    EXPECT_TRUE(IsEqual(offset, expectOffset));

    pattern_->info_.currentOffset_ = -ITEM_MAIN_SIZE * 2;
    offset = pattern_->GetOverScrollOffset(ITEM_MAIN_SIZE);
    expectOffset = { 0, ITEM_MAIN_SIZE };
    EXPECT_TRUE(IsEqual(offset, expectOffset));
    offset = pattern_->GetOverScrollOffset(0);
    expectOffset = { 0, 0 };
    EXPECT_TRUE(IsEqual(offset, expectOffset));
    offset = pattern_->GetOverScrollOffset(-ITEM_MAIN_SIZE);
    expectOffset = { 0, -ITEM_MAIN_SIZE };
    EXPECT_TRUE(IsEqual(offset, expectOffset));

    pattern_->info_.currentOffset_ = ITEM_MAIN_SIZE;
    offset = pattern_->GetOverScrollOffset(ITEM_MAIN_SIZE);
    expectOffset = { ITEM_MAIN_SIZE, 0 };
    EXPECT_TRUE(IsEqual(offset, expectOffset));
    offset = pattern_->GetOverScrollOffset(0);
    expectOffset = { 0, 0 };
    EXPECT_TRUE(IsEqual(offset, expectOffset));
    offset = pattern_->GetOverScrollOffset(-ITEM_MAIN_SIZE * 2);
    expectOffset = { -ITEM_MAIN_SIZE, -ITEM_MAIN_SIZE };
    EXPECT_TRUE(IsEqual(offset, expectOffset));
}

/**
 * @tc.name: GetOverScrollOffset004
 * @tc.desc: Test GetOverScrollOffset
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollerTestTwoNg, GetOverScrollOffset004, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    CreateFixedItems(8);
    CreateDone();

    pattern_->info_.currentOffset_ = -ITEM_MAIN_SIZE * 3;
    OverScrollOffset offset = pattern_->GetOverScrollOffset(ITEM_MAIN_SIZE * 2);
    OverScrollOffset expectOffset = { 0, ITEM_MAIN_SIZE * 2 };
    EXPECT_TRUE(IsEqual(offset, expectOffset));
    offset = pattern_->GetOverScrollOffset(0);
    expectOffset = { 0, 0 };
    EXPECT_TRUE(IsEqual(offset, expectOffset));
    offset = pattern_->GetOverScrollOffset(-ITEM_MAIN_SIZE);
    expectOffset = { 0, -ITEM_MAIN_SIZE };
    EXPECT_TRUE(IsEqual(offset, expectOffset));
}

/**
 * @tc.name: UpdateCurrentOffset001
 * @tc.desc: Test grid pattern UpdateCurrentOffset function
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollerTestTwoNg, UpdateCurrentOffset001, TestSize.Level1)
{
    /**
     * @tc.cases: Test SCROLL_FROM_UPDATE
     */
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    CreateFixedItems(10);
    CreateDone();
    UpdateCurrentOffset(-50.0f, SCROLL_FROM_UPDATE);
    EXPECT_TRUE(Position(-50.0f));
    UpdateCurrentOffset(50.0f, SCROLL_FROM_UPDATE);
    EXPECT_TRUE(Position(0.0f));
    UpdateCurrentOffset(-100.0f, SCROLL_FROM_UPDATE);
    EXPECT_TRUE(Position(-100.0f));
}

/**
 * @tc.name: UpdateCurrentOffset002
 * @tc.desc: Test grid pattern UpdateCurrentOffset function
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollerTestTwoNg, UpdateCurrentOffset002, TestSize.Level1)
{
    /**
     * @tc.cases: Test SCROLL_FROM_BAR
     */
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    CreateFixedItems(10);
    CreateDone();
    UpdateCurrentOffset(-50.0f, SCROLL_FROM_BAR);
    EXPECT_TRUE(Position(-50.0f));
    UpdateCurrentOffset(50.0f, SCROLL_FROM_BAR);
    EXPECT_TRUE(Position(0));
    UpdateCurrentOffset(-100.0f, SCROLL_FROM_BAR);
    EXPECT_TRUE(Position(-100.0f));
}

/**
 * @tc.name: UpdateCurrentOffset003
 * @tc.desc: Test grid pattern UpdateCurrentOffset function
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollerTestTwoNg, UpdateCurrentOffset003, TestSize.Level1)
{
    /**
     * @tc.cases: Test SCROLL_FROM_UPDATE and EdgeEffect::FADE
     */
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    CreateFixedItems(10);
    CreateDone();
    pattern_->scrollEffect_ = AceType::MakeRefPtr<ScrollEdgeEffect>(EdgeEffect::FADE);
    UpdateCurrentOffset(-50.0f, SCROLL_FROM_UPDATE);
    EXPECT_TRUE(Position(-50.0f));
    UpdateCurrentOffset(50.0f, SCROLL_FROM_UPDATE);
    EXPECT_TRUE(Position(0.0f));
    UpdateCurrentOffset(-100.0f, SCROLL_FROM_UPDATE);
    EXPECT_TRUE(Position(-100.0f));
}

/**
 * @tc.name: UpdateCurrentOffset004
 * @tc.desc: Test grid pattern UpdateCurrentOffset function
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollerTestTwoNg, UpdateCurrentOffset004, TestSize.Level1)
{
    /**
     * @tc.cases: When isConfigScrollable_ is false
     * @tc.expected: Can not roll
     */
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr 1fr");
    model.SetRowsTemplate("1fr 1fr");
    CreateFixedItems(10);
    CreateDone();
    EXPECT_FALSE(pattern_->isConfigScrollable_);

    UpdateCurrentOffset(-100.f, SCROLL_FROM_UPDATE);
    EXPECT_TRUE(Position(0));
}

/**
 * @tc.name: GetEndOffset000
 * @tc.desc: Test scrolling past limits
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollerTestTwoNg, GetEndOffset000, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetLayoutOptions({});
    model.SetEdgeEffect(EdgeEffect::SPRING, true);
    CreateFixedItems(20, GridItemStyle::NONE);
    CreateDone();

    int32_t targetIndex = 19;
    ScrollAlign align = ScrollAlign::AUTO;
    ScrollToIndex(targetIndex, false, align);
    auto& info = pattern_->info_;
    EXPECT_EQ(info.startMainLineIndex_, 6);
    EXPECT_EQ(info.endMainLineIndex_, 9);
    pattern_->scrollableEvent_->scrollable_->isTouching_ = true;
    for (int i = 0; i < 500; ++i) {
        UpdateCurrentOffset(-100.0f);
    }
    if (SystemProperties::GetGridIrregularLayoutEnabled()) {
        EXPECT_EQ(info.startMainLineIndex_, 9);
    } else {
        EXPECT_EQ(info.startMainLineIndex_, 10);
    }
    EXPECT_EQ(info.endMainLineIndex_, 9);

    EXPECT_LT(info.currentOffset_, -75.0f);

    ScrollToIndex(targetIndex, false, ScrollAlign::END);
    for (int i = 0; i < 10; ++i) {
        info.currentOffset_ -= 75.0f;
        frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
        FlushUITasks();
    }
    if (SystemProperties::GetGridIrregularLayoutEnabled()) {
        EXPECT_EQ(info.startMainLineIndex_, 9);
    } else {
        EXPECT_EQ(info.startMainLineIndex_, 10);
    }
    EXPECT_EQ(info.endMainLineIndex_, 9);

    EXPECT_LT(info.currentOffset_, -75.0f);
}

/**
 * @tc.name: GetEndOffset001
 * @tc.desc: Test GetEndOffset with updated offset on old layout
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollerTestTwoNg, GetEndOffset001, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    CreateFixedItems(20, GridItemStyle::NONE);
    CreateDone();

    int32_t targetIndex = 19;
    ScrollAlign align = ScrollAlign::AUTO;
    ScrollToIndex(targetIndex, false, align);
    auto& info = pattern_->info_;
    info.prevOffset_ = info.currentOffset_;
    info.currentOffset_ -= 1000.0f;
    info.synced_ = false;
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    pattern_->SetEdgeEffect(EdgeEffect::SPRING);
    pattern_->scrollableEvent_->scrollable_->isTouching_ = true;
    pattern_->GetScrollEdgeEffect()->ProcessScrollOver(-2000.0f);
    EXPECT_TRUE(info.synced_);
    // overScroll disabled to avoid layout bug
    EXPECT_EQ(info.currentOffset_, info.prevOffset_);
    EXPECT_EQ(info.startIndex_, 12);
    EXPECT_EQ(info.endIndex_, 19);
    EXPECT_EQ(info.startMainLineIndex_, 6);
    EXPECT_EQ(info.endMainLineIndex_, 9);
    EXPECT_EQ(pattern_->GetEndOffset(), 0.0f);
}

/**
 * @tc.name: GetEndOffset002
 * @tc.desc: Test GetEndOffset with updated offset on old layout
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollerTestTwoNg, GetEndOffset002, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    CreateFixedItems(20, GridItemStyle::NONE);
    model.SetLayoutOptions({});
    CreateDone();

    int32_t targetIndex = 19;
    ScrollAlign align = ScrollAlign::AUTO;
    ScrollToIndex(targetIndex, false, align);
    auto& info = pattern_->info_;
    info.prevOffset_ = info.currentOffset_;
    info.currentOffset_ -= 399;
    info.synced_ = false;
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    pattern_->SetEdgeEffect(EdgeEffect::SPRING);
    pattern_->scrollableEvent_->scrollable_->isTouching_ = true;
    pattern_->GetScrollEdgeEffect()->ProcessScrollOver(-399);
    EXPECT_TRUE(info.synced_);
    EXPECT_EQ(info.prevOffset_, -99);
    EXPECT_EQ(info.currentOffset_, -99);
    EXPECT_EQ(info.startIndex_, 18);
    EXPECT_EQ(info.endIndex_, 19);
    EXPECT_EQ(info.startMainLineIndex_, 9);
    EXPECT_EQ(info.endMainLineIndex_, 9);
    EXPECT_EQ(pattern_->GetEndOffset(), 300);
}

/**
 * @tc.name: MultiLineItemScroll001
 * @tc.desc: Test multiLine item in last line scroll end
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollerTestTwoNg, MultiLineItemScroll001, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    CreateFixedItems(6, GridItemStyle::NONE);
    CreateBigItem(0, 1, 0, 1, 2 * ITEM_MAIN_SIZE, 2 * ITEM_MAIN_SIZE);
    CreateDone();

    pattern_->ScrollBy(-10);
    FlushUITasks();
    auto& info = pattern_->info_;
    EXPECT_TRUE(info.reachEnd_);
    EXPECT_FALSE(info.offsetEnd_);
}

/**
 * @tc.name: VerticalGridScrollToIndexWithLargeLineHeight001
 * @tc.desc: Test Grid(Axis::VERTICAL) ScrollToIndex With line height Greater than main size Item
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollerTestTwoNg, VerticalGridScrollToIndexWithLargeLineHeight001, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr");
    model.SetRowsGap(Dimension(10));
    CreateGridItem(60, 550);
    ViewStackProcessor::GetInstance()->Pop();
    ViewStackProcessor::GetInstance()->StopGetAccessRecording();
    CreateGridItems(20, 60, 390);
    CreateDone();

    // cache all line in Grid
    ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, true);
    ScrollToEdge(ScrollEdgeType::SCROLL_TOP, false);

    ScrollToIndex(5, false, ScrollAlign::AUTO, std::nullopt);
    EXPECT_TRUE(Position(-550.0f));

    ScrollToEdge(ScrollEdgeType::SCROLL_TOP, true);

    ScrollToIndex(7, false, ScrollAlign::AUTO, std::nullopt);
    EXPECT_TRUE(Position(-790.0f));

    ScrollToEdge(ScrollEdgeType::SCROLL_TOP, true);

    ScrollToIndex(9, false, ScrollAlign::AUTO, std::nullopt);
    EXPECT_TRUE(Position(-1190.0f));
}

/**
 * @tc.name: VerticalGridScrollToIndexWithLargeLineHeight002
 * @tc.desc: Test Grid(Axis::VERTICAL) ScrollToIndex With line height Greater than main size Item
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollerTestTwoNg, VerticalGridScrollToIndexWithLargeLineHeight002, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr");
    model.SetRowsGap(Dimension(10));
    CreateGridItems(3, 60.0f, 150.0f);

    CreateGridItem(60.0f, 550.0f);
    ViewStackProcessor::GetInstance()->Pop();
    ViewStackProcessor::GetInstance()->StopGetAccessRecording();

    CreateGridItems(20, 60.0f, 190.0f);
    CreateDone();

    // cache all line in Grid
    ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, true);
    ScrollToEdge(ScrollEdgeType::SCROLL_TOP, false);

    ScrollToIndex(5, false, ScrollAlign::AUTO, std::nullopt);
    EXPECT_TRUE(Position(-310.0f));

    ScrollToEdge(ScrollEdgeType::SCROLL_TOP, true);

    ScrollToIndex(7, false, ScrollAlign::AUTO, std::nullopt);
    EXPECT_TRUE(Position(-730.0f));

    ScrollToEdge(ScrollEdgeType::SCROLL_TOP, true);

    ScrollToIndex(9, false, ScrollAlign::AUTO, std::nullopt);
    EXPECT_TRUE(Position(-870.0f));
}

/**
 * @tc.name: ScrollToIndexWithExtraOffset001
 * @tc.desc: Test Grid(Axis::VERTICAL) ScrollToIndex With extra offset
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollerTestTwoNg, ScrollToIndexWithExtraOffset001, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr");
    model.SetEdgeEffect(EdgeEffect::SPRING, true);
    model.SetRowsGap(Dimension(10));
    CreateFixedItems(50);
    CreateDone();
    float extraOffset = -100.0f;

    ScrollToIndex(0, false, ScrollAlign::AUTO, extraOffset);
    EXPECT_TRUE(Position(0.0f));
    ScrollToEdge(ScrollEdgeType::SCROLL_TOP, false);

    ScrollToIndex(0, false, ScrollAlign::AUTO, -extraOffset);
    EXPECT_TRUE(Position(-100.0f));
    ScrollToEdge(ScrollEdgeType::SCROLL_TOP, false);

    ScrollToIndex(0, false, ScrollAlign::START, extraOffset);
    EXPECT_TRUE(Position(0.0f));
    ScrollToEdge(ScrollEdgeType::SCROLL_TOP, false);

    ScrollToIndex(0, false, ScrollAlign::START, -extraOffset);
    EXPECT_TRUE(Position(-100.0f));
    ScrollToEdge(ScrollEdgeType::SCROLL_TOP, false);

    ScrollToIndex(0, false, ScrollAlign::CENTER, extraOffset);
    EXPECT_TRUE(Position(0.0f));
    ScrollToEdge(ScrollEdgeType::SCROLL_TOP, false);

    ScrollToIndex(0, false, ScrollAlign::CENTER, -extraOffset);
    EXPECT_TRUE(Position(0.0f));
    ScrollToEdge(ScrollEdgeType::SCROLL_TOP, false);

    ScrollToIndex(0, false, ScrollAlign::END, extraOffset);
    EXPECT_TRUE(Position(0.0f));
    ScrollToEdge(ScrollEdgeType::SCROLL_TOP, false);

    ScrollToIndex(0, false, ScrollAlign::END, -extraOffset);
    EXPECT_TRUE(Position(0.0f));
}

/**
 * @tc.name: ScrollToIndexWithExtraOffset002
 * @tc.desc: Test Grid(Axis::VERTICAL) ScrollToIndex With extra offset
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollerTestTwoNg, ScrollToIndexWithExtraOffset002, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr");
    model.SetEdgeEffect(EdgeEffect::SPRING, true);
    model.SetCachedCount(2, false);
    CreateItemsInLazyForEach(50, [](uint32_t idx) { return ITEM_MAIN_SIZE; });
    CreateDone();
    float extraOffset = -50.0f;

    ScrollToIndex(49, false, ScrollAlign::AUTO, std::nullopt);
    EXPECT_TRUE(Position(-4600.0f));
    ScrollToEdge(ScrollEdgeType::SCROLL_TOP, false);

    ScrollToIndex(49, false, ScrollAlign::AUTO, extraOffset);
    EXPECT_TRUE(Position(-4550.0f));
    ScrollToEdge(ScrollEdgeType::SCROLL_TOP, false);

    ScrollToIndex(49, false, ScrollAlign::AUTO, -extraOffset);
    EXPECT_TRUE(Position(-4600.0f));
    ScrollToEdge(ScrollEdgeType::SCROLL_TOP, false);

    ScrollToIndex(49, false, ScrollAlign::START, std::nullopt);
    EXPECT_TRUE(Position(-4600.0f));
    ScrollToEdge(ScrollEdgeType::SCROLL_TOP, false);

    ScrollToIndex(49, false, ScrollAlign::START, extraOffset);
    EXPECT_TRUE(Position(-4600.0f));
    ScrollToEdge(ScrollEdgeType::SCROLL_TOP, false);

    ScrollToIndex(49, false, ScrollAlign::START, -extraOffset);
    EXPECT_TRUE(Position(-4600.0f));
    ScrollToEdge(ScrollEdgeType::SCROLL_TOP, false);

    ScrollToIndex(49, false, ScrollAlign::CENTER, std::nullopt);
    EXPECT_TRUE(Position(-4600.0f));
    ScrollToEdge(ScrollEdgeType::SCROLL_TOP, false);

    ScrollToIndex(49, false, ScrollAlign::CENTER, extraOffset);
    EXPECT_TRUE(Position(-4600.0f));
    ScrollToEdge(ScrollEdgeType::SCROLL_TOP, false);

    ScrollToIndex(49, false, ScrollAlign::CENTER, -extraOffset);
    EXPECT_TRUE(Position(-4600.0f));
    ScrollToEdge(ScrollEdgeType::SCROLL_TOP, false);

    ScrollToIndex(49, false, ScrollAlign::END, std::nullopt);
    EXPECT_TRUE(Position(-4600.0f));
    ScrollToEdge(ScrollEdgeType::SCROLL_TOP, false);

    ScrollToIndex(49, false, ScrollAlign::END, extraOffset);
    EXPECT_TRUE(Position(-4550.0f));
    ScrollToEdge(ScrollEdgeType::SCROLL_TOP, false);

    ScrollToIndex(49, false, ScrollAlign::END, -extraOffset);
    EXPECT_TRUE(Position(-4600.0f));
    ScrollToEdge(ScrollEdgeType::SCROLL_TOP, false);
}

/**
 * @tc.name: ScrollToIndexWithExtraOffset003
 * @tc.desc: Test Grid(Axis::VERTICAL) ScrollToIndex With extra offset
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollerTestTwoNg, ScrollToIndexWithExtraOffset003, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr");
    model.SetEdgeEffect(EdgeEffect::SPRING, true);
    CreateFixedItems(50);
    CreateDone();
    float extraOffset = -150.0f;

    ScrollToIndex(49, false, ScrollAlign::AUTO, std::nullopt);
    EXPECT_TRUE(Position(-4600.0f));
    ScrollToEdge(ScrollEdgeType::SCROLL_TOP, false);

    ScrollToIndex(49, false, ScrollAlign::AUTO, extraOffset);
    EXPECT_TRUE(Position(-4450.0f));

    ScrollToIndex(49, false, ScrollAlign::AUTO, -extraOffset);
    EXPECT_TRUE(Position(-4600.0f));

    ScrollToIndex(49, false, ScrollAlign::START, std::nullopt);
    EXPECT_TRUE(Position(-4600.0f));

    ScrollToIndex(49, false, ScrollAlign::START, extraOffset);
    EXPECT_TRUE(Position(-4600.0f));

    ScrollToIndex(49, false, ScrollAlign::START, -extraOffset);
    EXPECT_TRUE(Position(-4600.0f));

    ScrollToIndex(49, false, ScrollAlign::CENTER, std::nullopt);
    EXPECT_TRUE(Position(-4600.0f));
    ScrollToIndex(49, false, ScrollAlign::CENTER, extraOffset);
    EXPECT_TRUE(Position(-4600.0f));

    ScrollToIndex(49, false, ScrollAlign::CENTER, -extraOffset);
    EXPECT_TRUE(Position(-4600.0f));

    ScrollToIndex(49, false, ScrollAlign::END, std::nullopt);
    EXPECT_TRUE(Position(-4600.0f));
    ScrollToIndex(49, false, ScrollAlign::END, extraOffset);
    EXPECT_TRUE(Position(-4450.0f));

    ScrollToIndex(49, false, ScrollAlign::END, -extraOffset);
    EXPECT_TRUE(Position(-4600.0f));
}

/**
 * @tc.name: CreateWithResourceObjScrollBarColor
 * @tc.desc: Test CreateWithResourceObjScrollBarColor in GridModelNG
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollerTestTwoNg, CreateWithResourceObjScrollBarColor001, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    ASSERT_NE(frameNode_, nullptr);
    ASSERT_NE(pattern_, nullptr);
    ASSERT_EQ(pattern_->resourceMgr_, nullptr);

    RefPtr<ResourceObject> invalidResObj = AceType::MakeRefPtr<ResourceObject>("", "", 0);
    model.CreateWithResourceObjScrollBarColor(invalidResObj);
    ASSERT_NE(pattern_->resourceMgr_, nullptr);
    EXPECT_NE(pattern_->resourceMgr_->resMap_.size(), 0);

    std::vector<ResourceObjectParams> params;
    AddMockResourceData(0, Color::BLUE);
    auto resObjWithString = AceType::MakeRefPtr<ResourceObject>(
        0, static_cast<int32_t>(ResourceType::COLOR), params, "", "", Container::CurrentIdSafely());
    model.CreateWithResourceObjScrollBarColor(resObjWithString);
    pattern_->resourceMgr_->ReloadResources();
    auto props = frameNode_->GetPaintProperty<ScrollablePaintProperty>();
    ASSERT_NE(props, nullptr);
    auto color = props->GetScrollBarColorValue(Color::BLUE);
    EXPECT_EQ(color, Color::BLUE);

    model.CreateWithResourceObjScrollBarColor(resObjWithString);
    pattern_->OnColorModeChange((uint32_t)ColorMode::DARK);
    ASSERT_NE(pattern_->resourceMgr_, nullptr);
    EXPECT_NE(pattern_->resourceMgr_->resMap_.size(), 0);
}

/**
 * @tc.name: CreateWithResourceObjScrollBarColor
 * @tc.desc: Test CreateWithResourceObjScrollBarColor in GridModelNG
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollerTestTwoNg, CreateWithResourceObjScrollBarColor002, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    ASSERT_NE(frameNode_, nullptr);
    ASSERT_NE(pattern_, nullptr);
    ASSERT_EQ(pattern_->resourceMgr_, nullptr);

    RefPtr<ResourceObject> invalidResObj = AceType::MakeRefPtr<ResourceObject>("", "", 0);
    GridModelNG::CreateWithResourceObjScrollBarColor(AceType::RawPtr(frameNode_), invalidResObj);
    model.CreateWithResourceObjScrollBarColor(invalidResObj);
    ASSERT_NE(pattern_->resourceMgr_, nullptr);
    EXPECT_NE(pattern_->resourceMgr_->resMap_.size(), 0);

    std::vector<ResourceObjectParams> params;
    AddMockResourceData(0, Color::BLUE);
    auto resObjWithString = AceType::MakeRefPtr<ResourceObject>(
        0, static_cast<int32_t>(ResourceType::COLOR), params, "", "", Container::CurrentIdSafely());

    GridModelNG::CreateWithResourceObjScrollBarColor(AceType::RawPtr(frameNode_), resObjWithString);
    pattern_->resourceMgr_->ReloadResources();
    auto props = frameNode_->GetPaintProperty<ScrollablePaintProperty>();
    ASSERT_NE(props, nullptr);
    auto color = props->GetScrollBarColorValue(Color::BLUE);
    EXPECT_EQ(color, Color::BLUE);

    model.CreateWithResourceObjScrollBarColor(resObjWithString);
    ASSERT_NE(pattern_->resourceMgr_, nullptr);
    EXPECT_NE(pattern_->resourceMgr_->resMap_.size(), 0);
}

/**
 * @tc.name: GetOverScrollOffsetWithContentOffset001
 * @tc.desc: Test GetOverScrollOffsetWithContentOffset
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollerTestTwoNg, GetOverScrollOffsetWithContentOffset001, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetLayoutOptions({});
    ScrollableModelNG::SetContentStartOffset(CONTENT_START_OFFSET);
    ScrollableModelNG::SetContentEndOffset(CONTENT_END_OFFSET);
    CreateFixedItems(10);
    CreateDone();

    EXPECT_EQ(pattern_->info_.currentOffset_, CONTENT_START_OFFSET);
    OverScrollOffset offset = pattern_->GetOverScrollOffset(ITEM_MAIN_SIZE);
    OverScrollOffset expectOffset = { ITEM_MAIN_SIZE, 0 };
    EXPECT_TRUE(IsEqual(offset, expectOffset));
    offset = pattern_->GetOverScrollOffset(0);
    expectOffset = { 0, 0 };
    EXPECT_TRUE(IsEqual(offset, expectOffset));
    offset = pattern_->GetOverScrollOffset(-ITEM_MAIN_SIZE);
    expectOffset = { 0, 0 };
    EXPECT_TRUE(IsEqual(offset, expectOffset));

    pattern_->info_.currentOffset_ = -ITEM_MAIN_SIZE;
    offset = pattern_->GetOverScrollOffset(ITEM_MAIN_SIZE * 2);
    expectOffset = { ITEM_MAIN_SIZE - CONTENT_START_OFFSET, 0 };
    EXPECT_TRUE(IsEqual(offset, expectOffset));
    offset = pattern_->GetOverScrollOffset(0);
    expectOffset = { 0, 0 };
    EXPECT_TRUE(IsEqual(offset, expectOffset));
    offset = pattern_->GetOverScrollOffset(-ITEM_MAIN_SIZE * 2);
    expectOffset = { 0, 0 };
    EXPECT_TRUE(IsEqual(offset, expectOffset));

    pattern_->info_.currentOffset_ = -ITEM_MAIN_SIZE * 2;
    offset = pattern_->GetOverScrollOffset(ITEM_MAIN_SIZE);
    expectOffset = { 0, 0 };
    EXPECT_TRUE(IsEqual(offset, expectOffset));
    offset = pattern_->GetOverScrollOffset(0);
    expectOffset = { 0, 0 };
    EXPECT_TRUE(IsEqual(offset, expectOffset));
    offset = pattern_->GetOverScrollOffset(-ITEM_MAIN_SIZE);
    expectOffset = { 0, 0 };
    EXPECT_TRUE(IsEqual(offset, expectOffset));
}

/**
 * @tc.name: GetOverScrollOffsetWithContentOffset
 * @tc.desc: Test GetOverScrollOffsetWithContentOffset
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollerTestTwoNg, GetOverScrollOffsetWithContentOffset002, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetLayoutOptions({});
    ScrollableModelNG::SetContentStartOffset(CONTENT_START_OFFSET);
    ScrollableModelNG::SetContentEndOffset(CONTENT_END_OFFSET);
    CreateFixedItems(10);
    CreateDone();

    pattern_->info_.currentOffset_ = ITEM_MAIN_SIZE;
    OverScrollOffset offset = pattern_->GetOverScrollOffset(ITEM_MAIN_SIZE);
    OverScrollOffset expectOffset = { ITEM_MAIN_SIZE, 0 };
    EXPECT_TRUE(IsEqual(offset, expectOffset));
    offset = pattern_->GetOverScrollOffset(0);
    expectOffset = { 0, 0 };
    EXPECT_TRUE(IsEqual(offset, expectOffset));
    offset = pattern_->GetOverScrollOffset(-ITEM_MAIN_SIZE * 2);
    expectOffset = { -ITEM_MAIN_SIZE + CONTENT_START_OFFSET, 0 };
    EXPECT_TRUE(IsEqual(offset, expectOffset));

    pattern_->info_.currentOffset_ = -ITEM_MAIN_SIZE * 3;
    offset = pattern_->GetOverScrollOffset(ITEM_MAIN_SIZE * 2);
    expectOffset = { 0, 0 };
    EXPECT_TRUE(IsEqual(offset, expectOffset));
    offset = pattern_->GetOverScrollOffset(0);
    expectOffset = { 0, 0 };
    EXPECT_TRUE(IsEqual(offset, expectOffset));
    offset = pattern_->GetOverScrollOffset(-ITEM_MAIN_SIZE);
    expectOffset = { 0, 0 };
    EXPECT_TRUE(IsEqual(offset, expectOffset));
}

/**
 * @tc.name: ScrollToIndexStartWithContentOffset
 * @tc.desc: Test ScrollToIndex with ContentOffset and ScrollAlign::Start without animation
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollerTestTwoNg, ScrollToIndexStartWithContentOffsetTest, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetLayoutOptions({});
    ScrollableModelNG::SetContentStartOffset(CONTENT_START_OFFSET);
    ScrollableModelNG::SetContentEndOffset(CONTENT_END_OFFSET);
    CreateFixedItems(20);
    CreateDone();
    ScrollAlign scrollAlign = ScrollAlign::START;
    bool smooth = false;
    ScrollToIndex(19, smooth, scrollAlign);
    EXPECT_EQ(pattern_->info_.currentOffset_, -CONTENT_END_OFFSET);
    EXPECT_EQ(pattern_->info_.prevOffset_, -CONTENT_END_OFFSET);
    EXPECT_EQ(pattern_->GetTotalOffset(), 630);

    ScrollToIndex(5, smooth, scrollAlign);
    EXPECT_EQ(pattern_->info_.currentOffset_, -ITEM_MAIN_SIZE + CONTENT_START_OFFSET);
    EXPECT_EQ(pattern_->info_.prevOffset_, -ITEM_MAIN_SIZE + CONTENT_START_OFFSET);
    EXPECT_EQ(pattern_->GetTotalOffset(), 180);

    ScrollToIndex(13, smooth, scrollAlign);
    EXPECT_EQ(pattern_->info_.currentOffset_, -ITEM_MAIN_SIZE + CONTENT_START_OFFSET);
    EXPECT_EQ(pattern_->info_.prevOffset_, -ITEM_MAIN_SIZE + CONTENT_START_OFFSET);
    EXPECT_EQ(pattern_->GetTotalOffset(), 580);

    ScrollToIndex(17, smooth, scrollAlign);
    EXPECT_EQ(pattern_->info_.currentOffset_, -CONTENT_END_OFFSET);
    EXPECT_EQ(pattern_->info_.prevOffset_, -CONTENT_END_OFFSET);
    EXPECT_EQ(pattern_->GetTotalOffset(), 630);

    ScrollToIndex(0, smooth, scrollAlign);
    EXPECT_EQ(pattern_->info_.currentOffset_, CONTENT_START_OFFSET);
    EXPECT_EQ(pattern_->info_.prevOffset_, CONTENT_START_OFFSET);
    EXPECT_EQ(pattern_->GetTotalOffset(), -20);
}

/**
 * @tc.name: AnimateToIndexStartWithContentOffsetTest
 * @tc.desc: Test ScrollToIndex with ContentOffset and ScrollAlign::Start with animation
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollerTestTwoNg, AnimateToIndexStartWithContentOffsetTest, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetLayoutOptions({});
    ScrollableModelNG::SetContentStartOffset(CONTENT_START_OFFSET);
    ScrollableModelNG::SetContentEndOffset(CONTENT_END_OFFSET);
    CreateFixedItems(20);
    CreateDone();
    ScrollAlign scrollAlign = ScrollAlign::START;

    AnimateToIndexWithTicks(19, scrollAlign);
    EXPECT_EQ(pattern_->info_.currentOffset_, -CONTENT_END_OFFSET);
    EXPECT_EQ(pattern_->GetTotalOffset(), 630);

    AnimateToIndexWithTicks(5, scrollAlign);
    EXPECT_EQ(pattern_->info_.currentOffset_, -ITEM_MAIN_SIZE + CONTENT_START_OFFSET);
    EXPECT_EQ(pattern_->GetTotalOffset(), 180);

    AnimateToIndexWithTicks(13, scrollAlign);
    EXPECT_EQ(pattern_->info_.currentOffset_, -ITEM_MAIN_SIZE + CONTENT_START_OFFSET);
    EXPECT_EQ(pattern_->GetTotalOffset(), 580);

    AnimateToIndexWithTicks(17, scrollAlign);
    EXPECT_EQ(pattern_->info_.currentOffset_, -CONTENT_END_OFFSET);
    EXPECT_EQ(pattern_->GetTotalOffset(), 630);

    AnimateToIndexWithTicks(0, scrollAlign);
    EXPECT_EQ(pattern_->info_.currentOffset_, CONTENT_START_OFFSET);
    EXPECT_EQ(pattern_->GetTotalOffset(), -20);
}

/**
 * @tc.name: ScrollToIndexEndWithContentOffset
 * @tc.desc: Test ScrollToIndex with ContentOffset and ScrollAlign::End without animation
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollerTestTwoNg, ScrollToIndexEndWithContentOffsetTest, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetLayoutOptions({});
    ScrollableModelNG::SetContentStartOffset(CONTENT_START_OFFSET);
    ScrollableModelNG::SetContentEndOffset(CONTENT_END_OFFSET);
    CreateFixedItems(20);
    CreateDone();
    ScrollAlign scrollAlign = ScrollAlign::END;
    bool smooth = false;

    ScrollToIndex(19, smooth, scrollAlign);
    EXPECT_EQ(pattern_->info_.currentOffset_, -CONTENT_END_OFFSET);
    EXPECT_EQ(pattern_->GetTotalOffset(), 630);

    ScrollToIndex(5, smooth, scrollAlign);
    EXPECT_EQ(pattern_->info_.currentOffset_, CONTENT_START_OFFSET);
    EXPECT_EQ(pattern_->GetTotalOffset(), -20);

    ScrollToIndex(13, smooth, scrollAlign);
    EXPECT_EQ(pattern_->info_.currentOffset_, -CONTENT_END_OFFSET);
    EXPECT_EQ(pattern_->GetTotalOffset(), 330);

    ScrollToIndex(17, smooth, scrollAlign);
    EXPECT_EQ(pattern_->info_.currentOffset_, -CONTENT_END_OFFSET);
    EXPECT_EQ(pattern_->GetTotalOffset(), 530);

    ScrollToIndex(0, smooth, scrollAlign);
    EXPECT_EQ(pattern_->info_.currentOffset_, CONTENT_START_OFFSET);
    EXPECT_EQ(pattern_->GetTotalOffset(), -20);
}

/**
 * @tc.name: AnimateToIndexEndWithContentOffsetTest
 * @tc.desc: Test ScrollToIndex with ContentOffset and ScrollAlign::End with animation
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollerTestTwoNg, AnimateToIndexEndWithContentOffsetTest, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetLayoutOptions({});
    ScrollableModelNG::SetContentStartOffset(CONTENT_START_OFFSET);
    ScrollableModelNG::SetContentEndOffset(CONTENT_END_OFFSET);
    CreateFixedItems(20);
    CreateDone();
    ScrollAlign scrollAlign = ScrollAlign::END;

    AnimateToIndexWithTicks(19, scrollAlign);
    EXPECT_EQ(pattern_->info_.currentOffset_, -CONTENT_END_OFFSET);
    EXPECT_EQ(pattern_->GetTotalOffset(), 630);

    AnimateToIndexWithTicks(5, scrollAlign);
    EXPECT_EQ(pattern_->info_.currentOffset_, CONTENT_START_OFFSET);
    EXPECT_EQ(pattern_->GetTotalOffset(), -20);

    AnimateToIndexWithTicks(13, scrollAlign);
    EXPECT_EQ(pattern_->info_.currentOffset_, -CONTENT_END_OFFSET);
    EXPECT_EQ(pattern_->GetTotalOffset(), 330);

    AnimateToIndexWithTicks(17, scrollAlign);
    EXPECT_EQ(pattern_->info_.currentOffset_, -CONTENT_END_OFFSET);
    EXPECT_EQ(pattern_->GetTotalOffset(), 530);

    AnimateToIndexWithTicks(0, scrollAlign);
    EXPECT_EQ(pattern_->info_.currentOffset_, CONTENT_START_OFFSET);
    EXPECT_EQ(pattern_->GetTotalOffset(), -20);
}

/**
 * @tc.name: ScrollToIndexAutoWithContentOffset
 * @tc.desc: Test ScrollToIndex with ContentOffset and ScrollAlign::Auto without animation
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollerTestTwoNg, ScrollToIndexAutoWithContentOffsetTest, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetLayoutOptions({});
    ScrollableModelNG::SetContentStartOffset(CONTENT_START_OFFSET);
    ScrollableModelNG::SetContentEndOffset(CONTENT_END_OFFSET);
    CreateFixedItems(20);
    CreateDone();
    ScrollAlign scrollAlign = ScrollAlign::AUTO;
    bool smooth = false;

    ScrollToIndex(19, smooth, scrollAlign);
    EXPECT_EQ(pattern_->info_.currentOffset_, -CONTENT_END_OFFSET);
    EXPECT_EQ(pattern_->GetTotalOffset(), 630);

    // Scroll forward, item 5 is at top
    ScrollToIndex(5, smooth, scrollAlign);
    EXPECT_EQ(pattern_->info_.currentOffset_, -ITEM_MAIN_SIZE + CONTENT_START_OFFSET);
    EXPECT_EQ(pattern_->GetTotalOffset(), 180);

    // Scroll backward, item 13 is at end
    ScrollToIndex(13, smooth, scrollAlign);
    EXPECT_EQ(pattern_->info_.currentOffset_, -CONTENT_END_OFFSET);
    EXPECT_EQ(pattern_->GetTotalOffset(), 330);

    // item 11 is in view
    ScrollToIndex(11, smooth, scrollAlign);
    EXPECT_EQ(pattern_->info_.currentOffset_, -CONTENT_END_OFFSET);
    EXPECT_EQ(pattern_->GetTotalOffset(), 330);

    ScrollBy(0, -CONTENT_END_OFFSET);
    EXPECT_EQ(pattern_->info_.currentOffset_, 0);
    EXPECT_EQ(pattern_->info_.startIndex_, 6);
    EXPECT_EQ(pattern_->info_.endIndex_, 13);
    ScrollToIndex(7, smooth, scrollAlign);
    EXPECT_EQ(pattern_->info_.currentOffset_, -ITEM_MAIN_SIZE + CONTENT_START_OFFSET);
    EXPECT_EQ(pattern_->GetTotalOffset(), 280);

    ScrollTo(300);
    EXPECT_EQ(pattern_->info_.currentOffset_, 0);
    EXPECT_EQ(pattern_->info_.startIndex_, 6);
    EXPECT_EQ(pattern_->info_.endIndex_, 13);
    ScrollToIndex(13, false, scrollAlign);
    EXPECT_EQ(pattern_->info_.currentOffset_, -CONTENT_END_OFFSET);
    EXPECT_EQ(pattern_->GetTotalOffset(), 330);

    ScrollToIndex(0, smooth, scrollAlign);
    EXPECT_EQ(pattern_->info_.currentOffset_, CONTENT_START_OFFSET);
    EXPECT_EQ(pattern_->GetTotalOffset(), -20);
}

/**
 * @tc.name: AnimateToIndexAutoWithContentOffsetTest
 * @tc.desc: Test ScrollToIndex with ContentOffset and ScrollAlign::Auto with animation
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollerTestTwoNg, AnimateToIndexAutoWithContentOffsetTest, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetLayoutOptions({});
    ScrollableModelNG::SetContentStartOffset(CONTENT_START_OFFSET);
    ScrollableModelNG::SetContentEndOffset(CONTENT_END_OFFSET);
    CreateFixedItems(20);
    CreateDone();
    ScrollAlign scrollAlign = ScrollAlign::AUTO;

    AnimateToIndexWithTicks(19, scrollAlign);
    EXPECT_EQ(pattern_->info_.currentOffset_, -CONTENT_END_OFFSET);
    EXPECT_EQ(pattern_->GetTotalOffset(), 630);

    AnimateToIndexWithTicks(5, scrollAlign);
    EXPECT_EQ(pattern_->info_.currentOffset_, -ITEM_MAIN_SIZE + CONTENT_START_OFFSET);
    EXPECT_EQ(pattern_->GetTotalOffset(), 180);

    AnimateToIndexWithTicks(13, scrollAlign);
    EXPECT_EQ(pattern_->info_.currentOffset_, -CONTENT_END_OFFSET);
    EXPECT_EQ(pattern_->GetTotalOffset(), 330);

    AnimateToIndexWithTicks(11, scrollAlign);
    EXPECT_EQ(pattern_->info_.currentOffset_, -CONTENT_END_OFFSET);
    EXPECT_EQ(pattern_->GetTotalOffset(), 330);

    ScrollBy(0, -CONTENT_END_OFFSET);
    EXPECT_EQ(pattern_->info_.currentOffset_, 0);
    EXPECT_EQ(pattern_->info_.startIndex_, 6);
    EXPECT_EQ(pattern_->info_.endIndex_, 13);
    AnimateToIndexWithTicks(7, scrollAlign);
    EXPECT_EQ(pattern_->info_.currentOffset_, -ITEM_MAIN_SIZE + CONTENT_START_OFFSET);
    EXPECT_EQ(pattern_->GetTotalOffset(), 280);

    ScrollTo(300);
    EXPECT_EQ(pattern_->info_.currentOffset_, 0);
    EXPECT_EQ(pattern_->info_.startIndex_, 6);
    EXPECT_EQ(pattern_->info_.endIndex_, 13);
    AnimateToIndexWithTicks(13, scrollAlign);
    EXPECT_EQ(pattern_->info_.currentOffset_, -CONTENT_END_OFFSET);
    EXPECT_EQ(pattern_->GetTotalOffset(), 330);

    AnimateToIndexWithTicks(0, scrollAlign);
    EXPECT_EQ(pattern_->info_.currentOffset_, CONTENT_START_OFFSET);
    EXPECT_EQ(pattern_->GetTotalOffset(), -20);
}

/**
 * @tc.name: ScrollToIndexAutoWithContentOffset
 * @tc.desc: Test ScrollToIndex with ContentOffset and ScrollAlign::Auto without animation
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollerTestTwoNg, UpdateContentEndOffset, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetLayoutOptions({});
    ScrollableModelNG::SetContentStartOffset(CONTENT_START_OFFSET);
    ScrollableModelNG::SetContentEndOffset(CONTENT_END_OFFSET + 100);
    CreateFixedItems(20);
    CreateDone();
    ScrollAlign scrollAlign = ScrollAlign::END;
    bool smooth = false;

    ScrollToIndex(18, smooth, scrollAlign);
    EXPECT_EQ(pattern_->info_.currentOffset_, -CONTENT_END_OFFSET);
    EXPECT_EQ(pattern_->info_.prevOffset_, -CONTENT_END_OFFSET);
    EXPECT_EQ(pattern_->info_.startIndex_, 14);
    EXPECT_EQ(pattern_->info_.endIndex_, 19);
    EXPECT_EQ(pattern_->GetTotalOffset(), 730);

    layoutProperty_->UpdateContentEndOffset(CONTENT_END_OFFSET + 80);
    FlushUITasks();
    EXPECT_EQ(pattern_->info_.currentOffset_, -CONTENT_END_OFFSET + 20);
    EXPECT_EQ(pattern_->info_.prevOffset_, -CONTENT_END_OFFSET + 20);
    EXPECT_EQ(pattern_->GetTotalOffset(), 710);

    layoutProperty_->UpdateContentEndOffset(CONTENT_END_OFFSET + 60);
    FlushUITasks();
    EXPECT_EQ(pattern_->info_.currentOffset_, -90);
    EXPECT_EQ(pattern_->info_.prevOffset_, -90);
    EXPECT_EQ(pattern_->GetTotalOffset(), 690);
     
    layoutProperty_->UpdateContentEndOffset(CONTENT_END_OFFSET + 40);
    FlushUITasks();
    EXPECT_EQ(pattern_->info_.currentOffset_, -70);
    EXPECT_EQ(pattern_->info_.prevOffset_, -70);
    EXPECT_EQ(pattern_->GetTotalOffset(), 670);
}

/**
 * @tc.name: ScrollToIndexWithContentAndCrossCountChanged
 * @tc.desc: test Scroll to index with contentOffset and crossCount changed
 * @tc.type: FUNC
 */
HWTEST_F(GridScrollerTestTwoNg, ScrollToIndexWithContentAndCrossCountChanged, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr");
    model.SetLayoutOptions({});
    ScrollableModelNG::SetContentStartOffset(CONTENT_START_OFFSET);
    ScrollableModelNG::SetContentEndOffset(CONTENT_END_OFFSET);
    CreateItemsInLazyForEach(30, [](uint32_t idx) { return ITEM_MAIN_SIZE; });
    CreateDone();

    bool smooth = false;
    ScrollAlign scrollAlign = ScrollAlign::START;
    AnimateToIndexWithTicks(19, scrollAlign);
    EXPECT_EQ(pattern_->info_.startIndex_, 15);
    EXPECT_EQ(pattern_->info_.endIndex_, 29);

    layoutProperty_->UpdateColumnsTemplate("1fr");
    FlushUITasks();
    EXPECT_EQ(pattern_->info_.startIndex_, 15);
    EXPECT_EQ(pattern_->info_.endIndex_, 19);

    layoutProperty_->UpdateColumnsTemplate("1fr 1fr");
    FlushUITasks();
    EXPECT_EQ(pattern_->info_.startIndex_, 14);
    EXPECT_EQ(pattern_->info_.endIndex_, 23);

    layoutProperty_->UpdateColumnsTemplate("1fr 1fr 1fr");
    FlushUITasks();
    EXPECT_EQ(pattern_->info_.startIndex_, 12);
    EXPECT_EQ(pattern_->info_.endIndex_, 26);

    ScrollToIndex(6, smooth, scrollAlign);
    EXPECT_EQ(pattern_->info_.startIndex_, 3);
    EXPECT_EQ(pattern_->info_.endIndex_, 17);
}
} // namespace OHOS::Ace::NG