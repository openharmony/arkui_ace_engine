/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "test/mock/frameworks/core/components_ng/render/mock_render_context.h"
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"
#include "test/unittest/core/pattern/scrollable/scrollable_test_utils.h"

#define protected public
#define private public
#include "core/components_ng/pattern/lazy_column_layout/lazy_column_layout_pattern.h"
#include "core/components_ng/pattern/lazy_grid_layout/lazy_grid_layout_pattern.h"
#include "core/components_ng/pattern/lazy_waterflow_layout/lazy_water_flow_layout_info.h"
#include "core/components_ng/pattern/lazy_waterflow_layout/lazy_water_flow_layout_pattern.h"
#undef private
#undef protected

#include "core/components_ng/pattern/lazy_column_layout/lazy_column_layout_model.h"
#include "core/components_ng/pattern/lazy_grid_layout/lazy_grid_layout_model.h"
#include "core/components_ng/pattern/lazy_waterflow_layout/lazy_water_flow_layout_model.h"
#include "core/components_ng/pattern/scrollable/scrollable_model_ng.h"
#include "core/components_ng/pattern/stack/stack_model_ng.h"
#include "core/components_ng/pattern/waterflow/layout/top_down/water_flow_layout_info.h"

namespace OHOS::Ace::NG {
namespace {
PaddingProperty CreatePadding(float left, float top, float right, float bottom)
{
    PaddingProperty padding;
    padding.left = CalcLength(left);
    padding.right = CalcLength(right);
    padding.top = CalcLength(top);
    padding.bottom = CalcLength(bottom);
    return padding;
}

void CreateStackItems(int32_t count, float height)
{
    for (int32_t i = 0; i < count; ++i) {
        StackModelNG stackModel;
        stackModel.Create();
        ViewAbstract::SetWidth(CalcLength(1.0f, DimensionUnit::PERCENT));
        ViewAbstract::SetHeight(CalcLength(height));
        ViewStackProcessor::GetInstance()->Pop();
    }
}

RefPtr<ShapeRect> CreateCustomClipShape(float offsetY, float height)
{
    auto shape = AceType::MakeRefPtr<ShapeRect>();
    shape->SetWidth(Dimension(1.0f, DimensionUnit::PERCENT));
    shape->SetHeight(Dimension(height));
    shape->SetOffset(DimensionOffset(Dimension(0.0f), Dimension(offsetY)));
    return shape;
}

} // namespace

class WaterFlowContentClipTest : public WaterFlowTestNg {
protected:
    void PrepareBoundaryLazyChildWaterFlow(WaterFlowModelNG& model)
    {
        model.SetColumnsTemplate("1fr");
        ViewAbstract::SetWidth(CalcLength(WATER_FLOW_WIDTH));
        ViewAbstract::SetHeight(CalcLength(400.0f));
        layoutProperty_->UpdatePadding(CreatePadding(0.0f, 0.0f, 0.0f, 150.0f));
        ScrollableModelNG::SetContentClip(AceType::RawPtr(frameNode_), ContentClipMode::BOUNDARY, nullptr);
    }
};

/**
 * @tc.name: ContentClipBoundaryEnd001
 * @tc.desc: BOUNDARY extends layout active range while scroll index keeps report range.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowContentClipTest, ContentClipBoundaryEnd001, TestSize.Level1)
{
    int32_t startIndex = -1;
    int32_t endIndex = -1;
    int32_t callbackCount = 0;
    WaterFlowModelNG model = CreateWaterFlow();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetOnScrollIndex([&startIndex, &endIndex, &callbackCount](int32_t start, int32_t end) {
        ++callbackCount;
        startIndex = start;
        endIndex = end;
    });
    layoutProperty_->UpdatePadding(CreatePadding(0.0f, 0.0f, 0.0f, 300.0f));
    ScrollableModelNG::SetContentClip(AceType::RawPtr(frameNode_), ContentClipMode::BOUNDARY, nullptr);
    for (int32_t i = 0; i < 40; ++i) {
        CreateItemWithHeight(100.0f);
    }
    CreateDone();

    auto info = pattern_->layoutInfo_;
    EXPECT_EQ(info->startFixOffset_, 0.0f);
    EXPECT_EQ(info->endFixOffset_, 300.0f);
    EXPECT_EQ(info->reportStartIndex_, 0);
    EXPECT_GT(info->endIndex_, info->reportEndIndex_);
    EXPECT_EQ(startIndex, info->reportStartIndex_);
    EXPECT_EQ(endIndex, info->reportEndIndex_);
    EXPECT_EQ(pattern_->GetFirstIndex(), info->reportStartIndex_);
    EXPECT_EQ(pattern_->GetBeginIndex(), info->reportStartIndex_);
    EXPECT_EQ(pattern_->GetEndIndex(), info->reportEndIndex_);
    ASSERT_TRUE(GetItem(info->endIndex_));
    EXPECT_TRUE(GetItem(info->endIndex_)->IsActive());

    const int32_t oldCallbackCount = callbackCount;
    UpdateCurrentOffset(100.0f);
    EXPECT_EQ(callbackCount, oldCallbackCount);
}

/**
 * @tc.name: ContentClipBoundaryLazyForEachFlowItem001
 * @tc.desc: BOUNDARY extends active range for FlowItems generated by LazyForEach.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowContentClipTest, ContentClipBoundaryLazyForEachFlowItem001, TestSize.Level1)
{
    int32_t startIndex = -1;
    int32_t endIndex = -1;
    WaterFlowModelNG model = CreateWaterFlow();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetOnScrollIndex([&startIndex, &endIndex](int32_t start, int32_t end) {
        startIndex = start;
        endIndex = end;
    });
    layoutProperty_->UpdatePadding(CreatePadding(0.0f, 0.0f, 0.0f, 300.0f));
    ScrollableModelNG::SetContentClip(AceType::RawPtr(frameNode_), ContentClipMode::BOUNDARY, nullptr);
    CreateItemsInLazyForEach(40, [](int32_t) { return 100.0f; });
    CreateDone();

    auto info = pattern_->layoutInfo_;
    EXPECT_EQ(info->startFixOffset_, 0.0f);
    EXPECT_EQ(info->endFixOffset_, 300.0f);
    EXPECT_EQ(info->reportStartIndex_, 0);
    EXPECT_GT(info->endIndex_, info->reportEndIndex_);
    EXPECT_EQ(startIndex, info->reportStartIndex_);
    EXPECT_EQ(endIndex, info->reportEndIndex_);
    ASSERT_TRUE(GetItem(info->endIndex_));
    EXPECT_TRUE(GetItem(info->endIndex_)->IsActive());
}

/**
 * @tc.name: ContentClipBoundaryLazyForEachReload001
 * @tc.desc: DataReload keeps LazyForEach FlowItems in the contentClip extension active.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowContentClipTest, ContentClipBoundaryLazyForEachReload001, TestSize.Level1)
{
    WaterFlowModelNG model = CreateWaterFlow();
    model.SetColumnsTemplate("1fr 1fr");
    layoutProperty_->UpdatePadding(CreatePadding(0.0f, 0.0f, 0.0f, 300.0f));
    ScrollableModelNG::SetContentClip(AceType::RawPtr(frameNode_), ContentClipMode::BOUNDARY, nullptr);
    auto mockLazy = CreateItemsInLazyForEach(30, [](int32_t) { return 100.0f; });
    CreateDone();

    auto lazyForEachNode = AceType::DynamicCast<LazyForEachNode>(frameNode_->GetChildAtIndex(0));
    ASSERT_NE(lazyForEachNode, nullptr);
    mockLazy->SetTotalCount(50);
    lazyForEachNode->OnDataReloaded();
    FlushUITasks(frameNode_);

    auto info = pattern_->layoutInfo_;
    EXPECT_EQ(info->startFixOffset_, 0.0f);
    EXPECT_EQ(info->endFixOffset_, 300.0f);
    EXPECT_GT(info->endIndex_, info->reportEndIndex_);
    ASSERT_TRUE(GetItem(info->endIndex_));
    EXPECT_TRUE(GetItem(info->endIndex_)->IsActive());
}

/**
 * @tc.name: ContentClipBoundarySyncLoad001
 * @tc.desc: Frame-by-frame loading eventually fills the contentClip extension area.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowContentClipTest, ContentClipBoundarySyncLoad001, TestSize.Level1)
{
    WaterFlowModelNG model = CreateWaterFlow();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetSyncLoad(false);
    layoutProperty_->UpdatePadding(CreatePadding(0.0f, 0.0f, 0.0f, 300.0f));
    ScrollableModelNG::SetContentClip(AceType::RawPtr(frameNode_), ContentClipMode::BOUNDARY, nullptr);
    CreateItemsInLazyForEach(80, [](int32_t) { return 100.0f; });
    MockPipelineContext::GetCurrent()->SetResponseTime(2);
    CreateDone();

    MockPipelineContext::GetCurrent()->SetResponseTime(1000);
    FlushUITasks(frameNode_);

    auto info = pattern_->layoutInfo_;
    EXPECT_EQ(info->startFixOffset_, 0.0f);
    EXPECT_EQ(info->endFixOffset_, 300.0f);
    EXPECT_GT(info->endIndex_, info->reportEndIndex_);
    ASSERT_TRUE(GetItem(info->endIndex_));
    EXPECT_TRUE(GetItem(info->endIndex_)->IsActive());
}

/**
 * @tc.name: ContentClipDefault001
 * @tc.desc: Default CONTENT_ONLY keeps active range and report range identical.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowContentClipTest, ContentClipDefault001, TestSize.Level1)
{
    WaterFlowModelNG model = CreateWaterFlow();
    model.SetColumnsTemplate("1fr 1fr");
    layoutProperty_->UpdatePadding(CreatePadding(0.0f, 0.0f, 0.0f, 300.0f));
    for (int32_t i = 0; i < 40; ++i) {
        CreateItemWithHeight(100.0f);
    }
    CreateDone();

    auto info = pattern_->layoutInfo_;
    EXPECT_EQ(info->startFixOffset_, 0.0f);
    EXPECT_EQ(info->endFixOffset_, 0.0f);
    EXPECT_EQ(info->startIndex_, info->reportStartIndex_);
    EXPECT_EQ(info->endIndex_, info->reportEndIndex_);
    EXPECT_EQ(info->startIndex_, info->FirstIdx());

    UpdateCurrentOffset(-450.0f);

    EXPECT_EQ(info->startFixOffset_, 0.0f);
    EXPECT_EQ(info->endFixOffset_, 0.0f);
    EXPECT_EQ(info->startIndex_, info->reportStartIndex_);
    EXPECT_EQ(info->endIndex_, info->reportEndIndex_);
    EXPECT_EQ(info->startIndex_, info->FirstIdx());
}

#if !defined(TEST_WATER_FLOW_SW) && !defined(TEST_SEGMENTED_WATER_FLOW)
/**
 * @tc.name: ContentClipDefaultZeroHeightTail001
 * @tc.desc: Default CONTENT_ONLY keeps trailing zero-height items in report range at end.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowContentClipTest, ContentClipDefaultZeroHeightTail001, TestSize.Level1)
{
    int32_t startIndex = -1;
    int32_t endIndex = -1;
    WaterFlowModelNG model = CreateWaterFlow();
    model.SetColumnsTemplate("1fr");
    model.SetOnScrollIndex([&startIndex, &endIndex](int32_t start, int32_t end) {
        startIndex = start;
        endIndex = end;
    });
    for (int32_t i = 0; i < 20; ++i) {
        CreateItemWithHeight(100.0f);
    }
    CreateItemWithHeight(0.0f);
    CreateDone();
    ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, false);
    FlushUITasks();

    auto info = pattern_->layoutInfo_;
    const int32_t tailIndex = info->ItemCnt(info->GetChildrenCount()) - 1;
    ASSERT_EQ(tailIndex, 20);
    EXPECT_TRUE(info->itemEnd_);
    EXPECT_EQ(info->endIndex_, tailIndex);
    EXPECT_EQ(info->reportEndIndex_, tailIndex);
    EXPECT_EQ(pattern_->GetEndIndex(), tailIndex);
    EXPECT_EQ(startIndex, info->reportStartIndex_);
    EXPECT_EQ(endIndex, info->reportEndIndex_);
}
#endif

/**
 * @tc.name: ContentClipBoundaryStartScroll001
 * @tc.desc: BOUNDARY front extension keeps scrolled-out active items hittable while report range stays visible.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowContentClipTest, ContentClipBoundaryStartScroll001, TestSize.Level1)
{
    WaterFlowModelNG model = CreateWaterFlow();
    model.SetColumnsTemplate("1fr");
    layoutProperty_->UpdatePadding(CreatePadding(0.0f, 300.0f, 0.0f, 0.0f));
    ScrollableModelNG::SetContentClip(AceType::RawPtr(frameNode_), ContentClipMode::BOUNDARY, nullptr);
    for (int32_t i = 0; i < 40; ++i) {
        CreateItemWithHeight(100.0f);
    }
    CreateDone();
    UpdateCurrentOffset(-450.0f);

    auto info = pattern_->layoutInfo_;
    EXPECT_EQ(info->startFixOffset_, 300.0f);
    EXPECT_EQ(info->endFixOffset_, 0.0f);
    ASSERT_LT(info->startIndex_, info->reportStartIndex_);

    const auto activeStartRect = pattern_->GetItemRect(info->startIndex_);
    EXPECT_LT(activeStartRect.Top(), 0.0f);
    EXPECT_GT(activeStartRect.Bottom(), info->GetViewStartBound());
    const double hitY = std::max<double>(activeStartRect.Top() + 1.0, info->GetViewStartBound() + 1.0f);
    EXPECT_LT(hitY, 0.0);
    EXPECT_LT(hitY, activeStartRect.Bottom());
    EXPECT_EQ(pattern_->GetItemIndex(activeStartRect.Left() + 1.0, hitY), info->startIndex_);
    EXPECT_EQ(pattern_->GetFirstIndex(), info->reportStartIndex_);
    EXPECT_EQ(pattern_->GetBeginIndex(), info->reportStartIndex_);
}

/**
 * @tc.name: ContentClipBoundaryCachedCount001
 * @tc.desc: cachedCount(4, true) starts from active range and does not double extend from report range.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowContentClipTest, ContentClipBoundaryCachedCount001, TestSize.Level1)
{
    WaterFlowModelNG model = CreateWaterFlow();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetCachedCount(4, true);
    layoutProperty_->UpdatePadding(CreatePadding(0.0f, 0.0f, 0.0f, 300.0f));
    ScrollableModelNG::SetContentClip(AceType::RawPtr(frameNode_), ContentClipMode::BOUNDARY, nullptr);
    for (int32_t i = 0; i < 40; ++i) {
        CreateItemWithHeight(100.0f);
    }
    CreateDone();

    auto info = pattern_->layoutInfo_;
    ASSERT_GT(info->endIndex_, info->reportEndIndex_);
    const int32_t lastCachedIndex = std::min(info->ItemCnt(info->GetChildrenCount()) - 1, info->endIndex_ + 4);
    const int32_t firstOutOfCachedIndex = lastCachedIndex + 1;
    ASSERT_TRUE(GetItem(lastCachedIndex));
    EXPECT_TRUE(GetItem(lastCachedIndex)->IsActive());
    if (firstOutOfCachedIndex < info->ItemCnt(info->GetChildrenCount())) {
        ASSERT_TRUE(GetItem(firstOutOfCachedIndex));
        EXPECT_FALSE(GetItem(firstOutOfCachedIndex)->IsActive());
    }
}

/**
 * @tc.name: ContentClipBoundaryCachedCountIdle001
 * @tc.desc: cachedCount(4, false) keeps contentClip extension active and preloads extra cache only on idle.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowContentClipTest, ContentClipBoundaryCachedCountIdle001, TestSize.Level1)
{
    WaterFlowModelNG model = CreateWaterFlow();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetCachedCount(4, false);
    layoutProperty_->UpdatePadding(CreatePadding(0.0f, 0.0f, 0.0f, 300.0f));
    ScrollableModelNG::SetContentClip(AceType::RawPtr(frameNode_), ContentClipMode::BOUNDARY, nullptr);
    CreateItemsInLazyForEach(80, [](int32_t) { return 100.0f; });
    CreateDone();

    auto info = pattern_->layoutInfo_;
    ASSERT_GT(info->endIndex_, info->reportEndIndex_);
    ASSERT_TRUE(GetItem(info->endIndex_));
    EXPECT_TRUE(GetItem(info->endIndex_)->IsActive());

    const int32_t lastCachedIndex = std::min(info->ItemCnt(info->GetChildrenCount()) - 1, info->endIndex_ + 4);
    ASSERT_FALSE(GetItem(lastCachedIndex, true));

    PipelineContext::GetCurrentContext()->OnIdle(INT64_MAX);
    auto cachedItem = GetItem(lastCachedIndex, true);
    ASSERT_TRUE(cachedItem);
    EXPECT_FALSE(cachedItem->IsActive());
    EXPECT_EQ(info->startFixOffset_, 0.0f);
    EXPECT_EQ(info->endFixOffset_, 300.0f);
    EXPECT_GT(info->endIndex_, info->reportEndIndex_);
}

/**
 * @tc.name: ContentClipBoundaryScrollToIndex001
 * @tc.desc: ScrollToIndex keeps the contentClip extension active without polluting reported indices.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowContentClipTest, ContentClipBoundaryScrollToIndex001, TestSize.Level1)
{
    int32_t startIndex = -1;
    int32_t endIndex = -1;
    WaterFlowModelNG model = CreateWaterFlow();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetOnScrollIndex([&startIndex, &endIndex](int32_t start, int32_t end) {
        startIndex = start;
        endIndex = end;
    });
    layoutProperty_->UpdatePadding(CreatePadding(0.0f, 0.0f, 0.0f, 300.0f));
    ScrollableModelNG::SetContentClip(AceType::RawPtr(frameNode_), ContentClipMode::BOUNDARY, nullptr);
    for (int32_t i = 0; i < 80; ++i) {
        CreateItemWithHeight(100.0f);
    }
    CreateDone();

    pattern_->ScrollToIndex(20, false, ScrollAlign::START);
    FlushUITasks(frameNode_);

    auto info = pattern_->layoutInfo_;
    EXPECT_EQ(info->startFixOffset_, 0.0f);
    EXPECT_EQ(info->endFixOffset_, 300.0f);
    EXPECT_GT(info->endIndex_, info->reportEndIndex_);
    EXPECT_EQ(startIndex, info->reportStartIndex_);
    EXPECT_EQ(endIndex, info->reportEndIndex_);
    ASSERT_TRUE(GetItem(info->endIndex_));
    EXPECT_TRUE(GetItem(info->endIndex_)->IsActive());

    pattern_->ScrollToIndex(30, false, ScrollAlign::END);
    FlushUITasks(frameNode_);

    EXPECT_EQ(info->startFixOffset_, 0.0f);
    EXPECT_EQ(info->endFixOffset_, 300.0f);
    EXPECT_GT(info->endIndex_, info->reportEndIndex_);
    EXPECT_EQ(startIndex, info->reportStartIndex_);
    EXPECT_EQ(endIndex, info->reportEndIndex_);
    EXPECT_NEAR(pattern_->GetItemRect(30).Bottom(), WATER_FLOW_HEIGHT - 300.0f, 1.0f);
}

/**
 * @tc.name: ContentClipCustomEnd001
 * @tc.desc: CUSTOM percentage main size extends active range with the same basis as the paint clip.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowContentClipTest, ContentClipCustomEnd001, TestSize.Level1)
{
    constexpr float clipHeightRatio = 1.25f;
    int32_t startIndex = -1;
    int32_t endIndex = -1;
    WaterFlowModelNG model = CreateWaterFlow();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetOnScrollIndex([&startIndex, &endIndex](int32_t start, int32_t end) {
        startIndex = start;
        endIndex = end;
    });
    auto shape = AceType::MakeRefPtr<ShapeRect>();
    shape->SetWidth(Dimension(1.0f, DimensionUnit::PERCENT));
    shape->SetHeight(Dimension(clipHeightRatio, DimensionUnit::PERCENT));
    ScrollableModelNG::SetContentClip(AceType::RawPtr(frameNode_), ContentClipMode::CUSTOM, shape);
    auto ctx = AceType::DynamicCast<MockRenderContext>(frameNode_->GetRenderContext());
    ASSERT_NE(ctx, nullptr);
    EXPECT_CALL(*ctx, SetContentClip(ClipRectEq(shape))).Times(1);
    for (int32_t i = 0; i < 40; ++i) {
        CreateItemWithHeight(100.0f);
    }
    CreateDone();

    auto info = pattern_->layoutInfo_;
    const float frameHeight = frameNode_->GetGeometryNode()->GetFrameSize().Height();
    const float expectedPaintClipEnd = frameHeight * clipHeightRatio;
    const float expectedEndFixOffset = expectedPaintClipEnd - frameHeight;
    EXPECT_EQ(info->startFixOffset_, 0.0f);
    EXPECT_EQ(info->endFixOffset_, expectedEndFixOffset);
    EXPECT_EQ(info->GetViewEndBound(frameHeight), expectedPaintClipEnd);
    EXPECT_GT(info->endIndex_, info->reportEndIndex_);
    EXPECT_EQ(startIndex, info->reportStartIndex_);
    EXPECT_EQ(endIndex, info->reportEndIndex_);
}

/**
 * @tc.name: ContentClipCustomSmaller001
 * @tc.desc: CUSTOM clip inside content only affects paint and does not extend active range.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowContentClipTest, ContentClipCustomSmaller001, TestSize.Level1)
{
    WaterFlowModelNG model = CreateWaterFlow();
    model.SetColumnsTemplate("1fr 1fr");
    auto shape = CreateCustomClipShape(100.0f, 400.0f);
    ScrollableModelNG::SetContentClip(AceType::RawPtr(frameNode_), ContentClipMode::CUSTOM, shape);
    for (int32_t i = 0; i < 40; ++i) {
        CreateItemWithHeight(100.0f);
    }
    CreateDone();

    auto info = pattern_->layoutInfo_;
    EXPECT_EQ(info->startFixOffset_, 0.0f);
    EXPECT_EQ(info->endFixOffset_, 0.0f);
    EXPECT_EQ(info->startIndex_, info->reportStartIndex_);
    EXPECT_EQ(info->endIndex_, info->reportEndIndex_);
}

/**
 * @tc.name: ContentClipCustomStart001
 * @tc.desc: CUSTOM clip extending before content start keeps front extension in active range only.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowContentClipTest, ContentClipCustomStart001, TestSize.Level1)
{
    WaterFlowModelNG model = CreateWaterFlow();
    model.SetColumnsTemplate("1fr");
    auto shape = CreateCustomClipShape(-200.0f, WATER_FLOW_HEIGHT);
    ScrollableModelNG::SetContentClip(AceType::RawPtr(frameNode_), ContentClipMode::CUSTOM, shape);
    for (int32_t i = 0; i < 40; ++i) {
        CreateItemWithHeight(100.0f);
    }
    CreateDone();
    UpdateCurrentOffset(-450.0f);

    auto info = pattern_->layoutInfo_;
    EXPECT_EQ(info->startFixOffset_, 200.0f);
    EXPECT_EQ(info->endFixOffset_, 0.0f);
    EXPECT_LT(info->startIndex_, info->reportStartIndex_);
}

/**
 * @tc.name: ContentClipCustomBothSides001
 * @tc.desc: CUSTOM clip extending beyond both sides applies per-edge fixOffset independently.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowContentClipTest, ContentClipCustomBothSides001, TestSize.Level1)
{
    WaterFlowModelNG model = CreateWaterFlow();
    model.SetColumnsTemplate("1fr 1fr");
    auto shape = CreateCustomClipShape(-100.0f, WATER_FLOW_HEIGHT + 200.0f);
    ScrollableModelNG::SetContentClip(AceType::RawPtr(frameNode_), ContentClipMode::CUSTOM, shape);
    for (int32_t i = 0; i < 40; ++i) {
        CreateItemWithHeight(100.0f);
    }
    CreateDone();

    auto info = pattern_->layoutInfo_;
    EXPECT_EQ(info->startFixOffset_, 100.0f);
    EXPECT_EQ(info->endFixOffset_, 100.0f);
    EXPECT_GT(info->endIndex_, info->reportEndIndex_);
}

/**
 * @tc.name: ContentClipSafeAreaCachedPad001
 * @tc.desc: SAFE_AREA uses the converged safe area pad to extend layout active range.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowContentClipTest, ContentClipSafeAreaCachedPad001, TestSize.Level1)
{
    WaterFlowModelNG model = CreateWaterFlow();
    model.SetColumnsTemplate("1fr 1fr");
    ScrollableModelNG::SetContentClip(AceType::RawPtr(frameNode_), ContentClipMode::SAFE_AREA, nullptr);
    layoutProperty_->UpdateSafeAreaPadding(CreatePadding(0.0f, 0.0f, 0.0f, 300.0f));
    for (int32_t i = 0; i < 40; ++i) {
        CreateItemWithHeight(100.0f);
    }
    CreateDone();
    FlushUITasks(frameNode_);

    auto info = pattern_->layoutInfo_;
    EXPECT_EQ(info->startFixOffset_, 0.0f);
    EXPECT_EQ(info->endFixOffset_, 300.0f);
    EXPECT_GT(info->endIndex_, info->reportEndIndex_);
}

/**
 * @tc.name: ContentClipSafeAreaBothEdges001
 * @tc.desc: SAFE_AREA extends both top and bottom safe-area regions into the active range.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowContentClipTest, ContentClipSafeAreaBothEdges001, TestSize.Level1)
{
    WaterFlowModelNG model = CreateWaterFlow();
    model.SetColumnsTemplate("1fr");
    ScrollableModelNG::SetContentClip(AceType::RawPtr(frameNode_), ContentClipMode::SAFE_AREA, nullptr);
    layoutProperty_->UpdateSafeAreaPadding(CreatePadding(0.0f, 120.0f, 0.0f, 180.0f));
    for (int32_t i = 0; i < 40; ++i) {
        CreateItemWithHeight(100.0f);
    }
    CreateDone();
    FlushUITasks(frameNode_);

    auto info = pattern_->layoutInfo_;
    EXPECT_EQ(info->startFixOffset_, 120.0f);
    EXPECT_EQ(info->endFixOffset_, 180.0f);
    EXPECT_GT(info->endIndex_, info->reportEndIndex_);

    UpdateCurrentOffset(-450.0f);
    EXPECT_LT(info->startIndex_, info->reportStartIndex_);
}

/**
 * @tc.name: ContentClipSafeAreaPostBundle001
 * @tc.desc: SAFE_AREA posts a bundle, stores the converged safe area pad, and then remeasures with fixOffset.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowContentClipTest, ContentClipSafeAreaPostBundle001, TestSize.Level1)
{
    WaterFlowModelNG model = CreateWaterFlow();
    model.SetColumnsTemplate("1fr 1fr");
    ScrollableModelNG::SetContentClip(AceType::RawPtr(frameNode_), ContentClipMode::SAFE_AREA, nullptr);
    layoutProperty_->UpdateSafeAreaPadding(CreatePadding(0.0f, 0.0f, 0.0f, 300.0f));
    for (int32_t i = 0; i < 40; ++i) {
        CreateItemWithHeight(100.0f);
    }
    CreateDone();

    EXPECT_TRUE(pattern_->safeAreaPad_.has_value());
    auto info = pattern_->layoutInfo_;
    EXPECT_EQ(info->startFixOffset_, 0.0f);
    EXPECT_EQ(info->endFixOffset_, 300.0f);
    EXPECT_GT(info->endIndex_, info->reportEndIndex_);
}

/**
 * @tc.name: ContentClipSafeAreaWithIgnoreLayoutSafeArea001
 * @tc.desc: SAFE_AREA contentClip remeasures correctly after a FlowItem updates ignoreLayoutSafeArea.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowContentClipTest, ContentClipSafeAreaWithIgnoreLayoutSafeArea001, TestSize.Level1)
{
    int32_t startIndex = -1;
    int32_t endIndex = -1;
    WaterFlowModelNG model = CreateWaterFlow();
    model.SetColumnsTemplate("1fr");
    model.SetOnScrollIndex([&startIndex, &endIndex](int32_t start, int32_t end) {
        startIndex = start;
        endIndex = end;
    });
    ViewAbstract::SetHeight(CalcLength(400.0f));
    ScrollableModelNG::SetContentClip(AceType::RawPtr(frameNode_), ContentClipMode::SAFE_AREA, nullptr);
    layoutProperty_->UpdateSafeAreaPadding(CreatePadding(0.0f, 0.0f, 0.0f, 150.0f));
    for (int32_t i = 0; i < 10; ++i) {
        CreateItemWithHeight(100.0f);
    }
    CreateDone();
    FlushUITasks(frameNode_);

    auto info = pattern_->layoutInfo_;
    EXPECT_EQ(info->startFixOffset_, 0.0f);
    EXPECT_EQ(info->endFixOffset_, 150.0f);
    ASSERT_GT(info->endIndex_, info->reportEndIndex_);
    const int32_t extensionIndex = info->reportEndIndex_ + 1;
    ASSERT_LE(extensionIndex, info->endIndex_);
    auto extensionItem = GetItem(extensionIndex);
    ASSERT_NE(extensionItem, nullptr);

    IgnoreLayoutSafeAreaOpts opts = { .type = NG::LAYOUT_SAFE_AREA_TYPE_SYSTEM,
        .edges = NG::LAYOUT_SAFE_AREA_EDGE_BOTTOM };
    extensionItem->GetLayoutProperty()->UpdateIgnoreLayoutSafeAreaOpts(opts);
    FlushUITasks(frameNode_);

    EXPECT_TRUE(pattern_->safeAreaPad_.has_value());
    EXPECT_EQ(info->startFixOffset_, 0.0f);
    EXPECT_EQ(info->endFixOffset_, 150.0f);
    EXPECT_TRUE(extensionItem->IsActive());
    EXPECT_EQ(startIndex, info->reportStartIndex_);
    EXPECT_EQ(endIndex, info->reportEndIndex_);
    const int32_t outOfSafeAreaIndex = info->endIndex_ + 1;
    if (outOfSafeAreaIndex < info->ItemCnt(info->GetChildrenCount())) {
        ASSERT_TRUE(GetItem(outOfSafeAreaIndex));
        EXPECT_FALSE(GetItem(outOfSafeAreaIndex)->IsActive());
    }
}

/**
 * @tc.name: ExpandSafeAreaWithoutContentClip001
 * @tc.desc: expandSafeArea without contentClip keeps fixOffset zero and report range equal to active range.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowContentClipTest, ExpandSafeAreaWithoutContentClip001, TestSize.Level1)
{
    WaterFlowModelNG model = CreateWaterFlow();
    model.SetColumnsTemplate("1fr 1fr");
    for (int32_t i = 0; i < 40; ++i) {
        CreateItemWithHeight(100.0f);
    }
    CreateDone();

    auto info = pattern_->layoutInfo_;
    EXPECT_EQ(info->startFixOffset_, 0.0f);
    EXPECT_EQ(info->endFixOffset_, 0.0f);
    EXPECT_EQ(info->startIndex_, info->reportStartIndex_);
    EXPECT_EQ(info->endIndex_, info->reportEndIndex_);

    EXPECT_CALL(*MockPipelineContext::pipeline_, GetSafeArea)
        .Times(AtLeast(1))
        .WillRepeatedly(Return(SafeAreaInsets { {}, {}, {}, { .start = 0, .end = 100 } }));
    layoutProperty_->UpdateSafeAreaExpandOpts({ .type = SAFE_AREA_TYPE_SYSTEM, .edges = SAFE_AREA_EDGE_ALL });
    FlushUITasks(frameNode_);

    EXPECT_EQ(info->expandHeight_, 100.0f);
    EXPECT_EQ(info->startFixOffset_, 0.0f);
    EXPECT_EQ(info->endFixOffset_, 0.0f);
    EXPECT_EQ(info->startIndex_, info->reportStartIndex_);
    EXPECT_EQ(info->endIndex_, info->reportEndIndex_);

    auto topDownInfo = AceType::DynamicCast<WaterFlowLayoutInfo>(info);
    if (topDownInfo && !topDownInfo->itemInfos_.empty()) {
        const float mainSize = frameNode_->GetGeometryNode()->GetFrameSize().MainSize(layoutProperty_->GetAxis());
        EXPECT_EQ(info->reportStartIndex_, topDownInfo->FastSolveStartIndex(info->GetViewStartBound(true)));
        EXPECT_EQ(info->reportEndIndex_, topDownInfo->FastSolveEndIndex(info->GetViewEndBound(mainSize, true)));
    }
}

/**
 * @tc.name: ContentClipBoundaryColumnReverse001
 * @tc.desc: COLUMN_REVERSE swaps main-axis contentClip extension to the start side.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowContentClipTest, ContentClipBoundaryColumnReverse001, TestSize.Level1)
{
    WaterFlowModelNG model = CreateWaterFlow();
    model.SetColumnsTemplate("1fr");
    model.SetLayoutDirection(FlexDirection::COLUMN_REVERSE);
    layoutProperty_->UpdatePadding(CreatePadding(0.0f, 0.0f, 0.0f, 300.0f));
    ScrollableModelNG::SetContentClip(AceType::RawPtr(frameNode_), ContentClipMode::BOUNDARY, nullptr);
    for (int32_t i = 0; i < 40; ++i) {
        CreateItemWithHeight(100.0f);
    }
    CreateDone();
    UpdateCurrentOffset(-450.0f);

    auto info = pattern_->layoutInfo_;
    EXPECT_EQ(info->startFixOffset_, 300.0f);
    EXPECT_EQ(info->endFixOffset_, 0.0f);
    EXPECT_LT(info->startIndex_, info->reportStartIndex_);
}

/**
 * @tc.name: ContentClipSafeAreaColumnReverseWithExpandSafeArea001
 * @tc.desc: COLUMN_REVERSE with SAFE_AREA keeps bottom safe-area expansion on the layout start side.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowContentClipTest, ContentClipSafeAreaColumnReverseWithExpandSafeArea001, TestSize.Level1)
{
    EXPECT_CALL(*MockPipelineContext::pipeline_, GetSafeArea)
        .Times(AtLeast(1))
        .WillRepeatedly(Return(SafeAreaInsets { {}, {}, {}, { .start = 0, .end = 100 } }));
    WaterFlowModelNG model = CreateWaterFlow();
    model.SetColumnsTemplate("1fr");
    model.SetLayoutDirection(FlexDirection::COLUMN_REVERSE);
    ScrollableModelNG::SetContentClip(AceType::RawPtr(frameNode_), ContentClipMode::SAFE_AREA, nullptr);
    layoutProperty_->UpdateSafeAreaPadding(CreatePadding(0.0f, 0.0f, 0.0f, 300.0f));
    layoutProperty_->UpdateSafeAreaExpandOpts({ .type = SAFE_AREA_TYPE_SYSTEM, .edges = SAFE_AREA_EDGE_ALL });
    for (int32_t i = 0; i < 40; ++i) {
        CreateItemWithHeight(100.0f);
    }
    CreateDone();
    FlushUITasks(frameNode_);

    auto info = pattern_->layoutInfo_;
    EXPECT_EQ(info->expandHeight_, 100.0f);
    EXPECT_EQ(info->startFixOffset_, 300.0f);
    EXPECT_EQ(info->endFixOffset_, 0.0f);

    UpdateCurrentOffset(-450.0f);
    info = pattern_->layoutInfo_;
    ASSERT_LT(info->startIndex_, info->reportStartIndex_);
    const auto activeStartRect = pattern_->GetItemRect(info->startIndex_);
    EXPECT_GT(activeStartRect.Bottom(), WATER_FLOW_HEIGHT);
    EXPECT_LT(activeStartRect.Top(), WATER_FLOW_HEIGHT + info->startFixOffset_);
}

/**
 * @tc.name: ContentClipBoundaryRowRtl001
 * @tc.desc: ROW in RTL swaps main-axis contentClip extension to the start side.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowContentClipTest, ContentClipBoundaryRowRtl001, TestSize.Level1)
{
    WaterFlowModelNG model = CreateWaterFlow();
    model.SetLayoutDirection(FlexDirection::ROW);
    model.SetRowsTemplate("1fr");
    layoutProperty_->UpdateLayoutDirection(TextDirection::RTL);
    layoutProperty_->UpdateWaterflowDirection(FlexDirection::ROW);
    layoutProperty_->UpdatePadding(CreatePadding(0.0f, 0.0f, 120.0f, 0.0f));
    ScrollableModelNG::SetContentClip(AceType::RawPtr(frameNode_), ContentClipMode::BOUNDARY, nullptr);
    for (int32_t i = 0; i < 40; ++i) {
        CreateItemWithHeight(100.0f);
    }
    CreateDone();

    auto info = pattern_->layoutInfo_;
    EXPECT_EQ(layoutProperty_->GetAxis(), Axis::HORIZONTAL);
    EXPECT_EQ(info->startFixOffset_, 120.0f);
    EXPECT_EQ(info->endFixOffset_, 0.0f);
}

/**
 * @tc.name: ContentClipBoundaryRowReverseLtr001
 * @tc.desc: ROW_REVERSE in LTR maps the physical left boundary extension to main-axis end.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowContentClipTest, ContentClipBoundaryRowReverseLtr001, TestSize.Level1)
{
    WaterFlowModelNG model = CreateWaterFlow();
    model.SetLayoutDirection(FlexDirection::ROW_REVERSE);
    model.SetRowsTemplate("1fr");
    layoutProperty_->UpdateWaterflowDirection(FlexDirection::ROW_REVERSE);
    layoutProperty_->UpdatePadding(CreatePadding(120.0f, 0.0f, 0.0f, 0.0f));
    ScrollableModelNG::SetContentClip(AceType::RawPtr(frameNode_), ContentClipMode::BOUNDARY, nullptr);
    for (int32_t i = 0; i < 40; ++i) {
        CreateItemWithHeight(100.0f);
    }
    CreateDone();

    auto info = pattern_->layoutInfo_;
    EXPECT_EQ(layoutProperty_->GetAxis(), Axis::HORIZONTAL);
    EXPECT_EQ(info->startFixOffset_, 0.0f);
    EXPECT_EQ(info->endFixOffset_, 120.0f);
}

/**
 * @tc.name: ContentClipBoundaryLazyColumn001
 * @tc.desc: LazyColumnLayout under WaterFlow gets the clip extension as active range,
 *           without visible callback pollution.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowContentClipTest, ContentClipBoundaryLazyColumn001, TestSize.Level1)
{
    int32_t visibleStart = -1;
    int32_t visibleEnd = -1;
    WaterFlowModelNG model = CreateWaterFlow();
    PrepareBoundaryLazyChildWaterFlow(model);

    LazyColumnLayoutModel::Create();
    ViewAbstract::SetWidth(CalcLength(1.0f, DimensionUnit::PERCENT));
    LazyColumnLayoutModel::SetOnVisibleIndexesChange([&visibleStart, &visibleEnd](int32_t start, int32_t end) {
        visibleStart = start;
        visibleEnd = end;
    });
    CreateStackItems(10, 100.0f);
    ViewStackProcessor::GetInstance()->Pop();
    CreateDone();

    auto lazyColumn = AceType::DynamicCast<FrameNode>(frameNode_->GetChildAtIndex(0));
    ASSERT_NE(lazyColumn, nullptr);
    auto lazyColumnPattern = lazyColumn->GetPattern<LazyColumnLayoutPattern>();
    ASSERT_NE(lazyColumnPattern, nullptr);
    EXPECT_EQ(visibleStart, 0);
    EXPECT_GT(lazyColumnPattern->layoutInfo_->endIndex_, visibleEnd);
}

/**
 * @tc.name: ContentClipBoundaryLazyVGrid001
 * @tc.desc: LazyVGridLayout under WaterFlow gets the clip extension as active range,
 *           without visible callback pollution.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowContentClipTest, ContentClipBoundaryLazyVGrid001, TestSize.Level1)
{
    int32_t visibleStart = -1;
    int32_t visibleEnd = -1;
    WaterFlowModelNG model = CreateWaterFlow();
    PrepareBoundaryLazyChildWaterFlow(model);

    LazyVGridLayoutModel::Create();
    ViewAbstract::SetWidth(CalcLength(1.0f, DimensionUnit::PERCENT));
    LazyVGridLayoutModel::SetColumnsTemplate("1fr 1fr");
    LazyVGridLayoutModel::SetOnVisibleIndexesChange([&visibleStart, &visibleEnd](int32_t start, int32_t end) {
        visibleStart = start;
        visibleEnd = end;
    });
    CreateStackItems(20, 100.0f);
    ViewStackProcessor::GetInstance()->Pop();
    CreateDone();

    auto lazyGrid = AceType::DynamicCast<FrameNode>(frameNode_->GetChildAtIndex(0));
    ASSERT_NE(lazyGrid, nullptr);
    auto lazyGridPattern = lazyGrid->GetPattern<LazyGridLayoutPattern>();
    ASSERT_NE(lazyGridPattern, nullptr);
    EXPECT_EQ(visibleStart, 0);
    EXPECT_GT(lazyGridPattern->layoutInfo_->endIndex_, visibleEnd);
}

/**
 * @tc.name: ContentClipBoundaryLazyVWaterFlow001
 * @tc.desc: LazyVWaterFlowLayout under WaterFlow gets the clip extension as active range, without callback pollution.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowContentClipTest, ContentClipBoundaryLazyVWaterFlow001, TestSize.Level1)
{
    int32_t visibleStart = -1;
    int32_t visibleEnd = -1;
    WaterFlowModelNG model = CreateWaterFlow();
    PrepareBoundaryLazyChildWaterFlow(model);

    LazyWaterFlowLayoutModel::Create();
    ViewAbstract::SetWidth(CalcLength(1.0f, DimensionUnit::PERCENT));
    LazyVWaterFlowLayoutModel::SetColumnsTemplate("1fr 1fr");
    LazyWaterFlowLayoutModel::SetOnVisibleIndexesChange([&visibleStart, &visibleEnd](int32_t start, int32_t end) {
        visibleStart = start;
        visibleEnd = end;
    });
    CreateStackItems(20, 100.0f);
    ViewStackProcessor::GetInstance()->Pop();
    CreateDone();

    auto lazyWaterFlow = AceType::DynamicCast<FrameNode>(frameNode_->GetChildAtIndex(0));
    ASSERT_NE(lazyWaterFlow, nullptr);
    auto lazyWaterFlowPattern = lazyWaterFlow->GetPattern<LazyWaterFlowLayoutPattern>();
    ASSERT_NE(lazyWaterFlowPattern, nullptr);
    EXPECT_EQ(visibleStart, 0);
    EXPECT_GT(lazyWaterFlowPattern->layoutInfo_->endIndex_, visibleEnd);
}
} // namespace OHOS::Ace::NG
