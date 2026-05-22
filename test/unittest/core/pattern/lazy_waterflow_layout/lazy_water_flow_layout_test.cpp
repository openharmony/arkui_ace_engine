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

#include "lazy_water_flow_layout_test.h"

#include <algorithm>
#include <cmath>

#include "test/mock/adapter/ohos/osal/mock_system_properties.h"
#include "test/mock/frameworks/base/thread/mock_task_executor.h"
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"
#include "test/unittest/core/syntax/mock_lazy_for_each_builder.h"

#include "core/components_ng/pattern/common_view/common_view_model_ng.h"
#include "core/components_ng/pattern/lazy_waterflow_layout/lazy_water_flow_layout_algorithm.h"
#include "core/components_ng/pattern/lazy_waterflow_layout/lazy_water_flow_layout_info.h"
#include "core/components_ng/pattern/lazy_waterflow_layout/lazy_water_flow_layout_model.h"
#include "core/components_ng/pattern/lazy_waterflow_layout/lazy_water_flow_layout_model_static.h"
#include "core/components_ng/pattern/lazy_waterflow_layout/lazy_water_flow_layout_property.h"
#include "core/components_ng/pattern/list/list_item_model_ng.h"
#include "core/components_ng/pattern/list/list_model_ng.h"
#include "core/components_ng/pattern/node_container/node_container_model_ng.h"
#include "core/components_ng/pattern/node_container/node_container_pattern.h"
#include "core/components_ng/pattern/scroll/scroll_pattern.h"
#include "core/components_ng/pattern/scroll/scroll_model_ng.h"
#include "core/components_ng/pattern/stack/stack_model_ng.h"
#include "core/components_ng/syntax/lazy_for_each_model_ng.h"
#include "core/components_ng/syntax/lazy_for_each_node.h"
#include "core/components_ng/pattern/waterflow/water_flow_model_ng.h"
#include "core/components_ng/pattern/waterflow/water_flow_item_model_ng.h"
#include "core/components_ng/syntax/arkoala_lazy_node.h"
#include "core/components_v2/inspector/inspector_constants.h"

namespace OHOS::Ace::NG {

namespace {
constexpr int64_t FRAME_INTERVAL_MS = 16;
constexpr int64_t NANOSECONDS_PER_MILLISECOND = 1000000;

class LazyVWaterFlowLayoutCoreTest : public LazyWaterFlowLayoutTestBase {};

void CreateFlowItem(float height)
{
    WaterFlowItemModelNG itemModel;
    itemModel.Create();
    ViewAbstract::SetWidth(CalcLength(1.0f, DimensionUnit::PERCENT));
    ViewAbstract::SetHeight(CalcLength(height));
}

void CreateListFooter(float height)
{
    ListItemModelNG itemModel;
    itemModel.Create();
    ViewAbstract::SetWidth(CalcLength(1.0f, DimensionUnit::PERCENT));
    ViewAbstract::SetHeight(CalcLength(height));
    ViewStackProcessor::GetInstance()->Pop();
}

class LazyWaterFlowMockLazy : public Framework::MockLazyForEachBuilder {
public:
    explicit LazyWaterFlowMockLazy(const std::vector<float>& heights)
    {
        for (auto height : heights) {
            items_.push_back({ nextId_++, height });
        }
    }

    void Insert(int32_t index, float height)
    {
        auto insertIndex = std::max(0, std::min(index, static_cast<int32_t>(items_.size())));
        items_.insert(items_.begin() + insertIndex, { nextId_++, height });
    }

    void Erase(int32_t index)
    {
        if (index < 0 || index >= static_cast<int32_t>(items_.size())) {
            return;
        }
        items_.erase(items_.begin() + index);
    }

protected:
    int32_t OnGetTotalCount() override
    {
        return static_cast<int32_t>(items_.size());
    }

    std::pair<std::string, RefPtr<NG::UINode>> OnGetChildByIndex(
        int32_t index, std::unordered_map<std::string, NG::LazyForEachCacheChild>& expiringItems) override
    {
        ScopedViewStackProcessor scope;
        StackModelNG stackModel;
        stackModel.Create();
        ViewAbstract::SetWidth(CalcLength(1.0f, DimensionUnit::PERCENT));
        auto height = index >= 0 && index < static_cast<int32_t>(items_.size()) ?
            items_[index].height : LAZY_WATER_FLOW_ITEM_HEIGHT;
        ViewAbstract::SetHeight(CalcLength(height));
        auto node = ViewStackProcessor::GetInstance()->Finish();
        auto key = index >= 0 && index < static_cast<int32_t>(items_.size()) ?
            std::to_string(items_[index].id) : std::to_string(index);
        return { key, node };
    }

private:
    struct Item {
        int32_t id = 0;
        float height = 0.0f;
    };

    int32_t nextId_ = 0;
    std::vector<Item> items_;
};

using VisibleRange = std::pair<int32_t, int32_t>;

RefPtr<LazyWaterFlowMockLazy> CreateLazyForEachContent(const std::vector<float>& heights, ElementIdType elmtId)
{
    auto mockLazy = AceType::MakeRefPtr<LazyWaterFlowMockLazy>(heights);
    RefPtr<LazyForEachActuator> mockLazyActuator = mockLazy;
    ViewStackProcessor::GetInstance()->StartGetAccessRecordingFor(elmtId);
    LazyForEachModelNG lazyForEachModel;
    lazyForEachModel.Create(mockLazyActuator);
    ViewStackProcessor::GetInstance()->Pop();
    ViewStackProcessor::GetInstance()->StopGetAccessRecording();
    return mockLazy;
}

void InsertTopBatch(
    const RefPtr<LazyWaterFlowMockLazy>& mockLazy, const RefPtr<LazyForEachNode>& lazyForEachNode, int32_t count,
    float height)
{
    for (int32_t i = 0; i < count; ++i) {
        mockLazy->Insert(i, height);
        lazyForEachNode->OnDataAdded(i);
    }
}

void ExpectVisibleRange(const VisibleRange& visibleRange, int32_t start, int32_t end)
{
    EXPECT_EQ(visibleRange.first, start);
    EXPECT_EQ(visibleRange.second, end);
}

void RegisterVisibleRangeObserver(const RefPtr<FrameNode>& frameNode, int32_t& callCount, VisibleRange& visibleRange)
{
    CHECK_NULL_VOID(frameNode);
    LazyWaterFlowLayoutModel::SetOnVisibleIndexesChange(
        AceType::RawPtr(frameNode), [&callCount, &visibleRange](int32_t start, int32_t end) {
            ++callCount;
            visibleRange = { start, end };
        });
}

}

void LazyWaterFlowLayoutTestBase::SetUpTestSuite()
{
    TestNG::SetUpTestSuite();
    MockPipelineContext::GetCurrent()->SetUseFlushUITasks(true);
    MockPipelineContext::GetCurrentContext()->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    MockAnimationManager::Enable(true);
    g_segmentedWaterflow = false;
}

void LazyWaterFlowLayoutTestBase::TearDownTestSuite()
{
    TestNG::TearDownTestSuite();
}

void LazyWaterFlowLayoutTestBase::SetUp() {}

void LazyWaterFlowLayoutTestBase::TearDown()
{
    RemoveFromStageNode();
    frameNode_ = nullptr;
    pattern_ = nullptr;
    layoutProperty_ = nullptr;
    scrollableFrameNode_ = nullptr;
    scrollablePattern_ = nullptr;
    MockAnimationManager::GetInstance().Reset();
}

RefPtr<FrameNode> LazyWaterFlowLayoutTestBase::GetMainFrameNode()
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->GetMainElementNode();
    return AceType::DynamicCast<FrameNode>(element);
}

void LazyWaterFlowLayoutTestBase::CreateWaterFlow(WaterFlowLayoutMode mode)
{
    WaterFlowModelNG model;
    model.Create();
    ViewAbstract::SetHeight(CalcLength(LAZY_WATER_FLOW_SCROLL_HEIGHT));
    ViewAbstract::SetWidth(CalcLength(LAZY_WATER_FLOW_SCROLL_WIDTH));
    model.SetLayoutMode(mode);
    scrollableFrameNode_ = GetMainFrameNode();
    scrollablePattern_ = scrollableFrameNode_->GetPattern<ScrollablePattern>();
}

void LazyWaterFlowLayoutTestBase::CreateScroll()
{
    ScrollModelNG model;
    model.Create();
    ViewAbstract::SetHeight(CalcLength(LAZY_WATER_FLOW_SCROLL_HEIGHT));
    ViewAbstract::SetWidth(CalcLength(LAZY_WATER_FLOW_SCROLL_WIDTH));
    scrollableFrameNode_ = GetMainFrameNode();
    scrollablePattern_ = scrollableFrameNode_->GetPattern<ScrollablePattern>();
}

void LazyWaterFlowLayoutTestBase::CreateList()
{
    ListModelNG model;
    model.Create();
    ViewAbstract::SetHeight(CalcLength(LAZY_WATER_FLOW_SCROLL_HEIGHT));
    ViewAbstract::SetWidth(CalcLength(LAZY_WATER_FLOW_SCROLL_WIDTH));
    scrollableFrameNode_ = GetMainFrameNode();
    scrollablePattern_ = scrollableFrameNode_->GetPattern<ScrollablePattern>();
}

void LazyWaterFlowLayoutTestBase::CreateLazyWaterFlowLayout()
{
    LazyVWaterFlowLayoutModel model;
    model.Create();
    ViewAbstract::SetWidth(CalcLength(LAZY_WATER_FLOW_SCROLL_WIDTH));
    frameNode_ = GetMainFrameNode();
    pattern_ = frameNode_->GetPattern<LazyWaterFlowLayoutPattern>();
    layoutProperty_ = frameNode_->GetLayoutProperty<LazyWaterFlowLayoutProperty>();
}

void LazyWaterFlowLayoutTestBase::CreateContent(const std::vector<float>& heights)
{
    for (auto height : heights) {
        StackModelNG stackModel;
        stackModel.Create();
        ViewAbstract::SetWidth(CalcLength(1.0f, DimensionUnit::PERCENT));
        ViewAbstract::SetHeight(CalcLength(height));
        ViewStackProcessor::GetInstance()->Pop();
    }
}

void LazyWaterFlowLayoutTestBase::CreateContent(int32_t count)
{
    CreateContent(std::vector<float>(count, LAZY_WATER_FLOW_ITEM_HEIGHT));
}

void LazyWaterFlowLayoutTestBase::FlushIdleTask()
{
    ASSERT_NE(pattern_, nullptr);
    int32_t tryCount = 10;
    auto needPredict = pattern_->layoutInfo_->NeedPredict();
    while (needPredict && tryCount > 0) {
        const int64_t time = GetSysTimestamp();
        auto pipeline = pattern_->GetContext();
        pipeline->OnIdle(time + FRAME_INTERVAL_MS * NANOSECONDS_PER_MILLISECOND);
        FlushUITasks();
        needPredict = pattern_->layoutInfo_->NeedPredict();
        tryCount--;
    }
}

/**
 * @tc.name: Create_001
 * @tc.desc: Verify LazyVWaterFlowLayout can be created under WaterFlow.
 * @tc.type: FUNC
 */
HWTEST_F(LazyVWaterFlowLayoutCoreTest, Create_001, TestSize.Level1)
{
    CreateWaterFlow();
    CreateLazyWaterFlowLayout();
    CreateContent(5);
    CreateDone();

    ASSERT_NE(frameNode_, nullptr);
    ASSERT_NE(pattern_, nullptr);
    EXPECT_EQ(frameNode_->GetTag(), V2::LAZY_V_WATERFLOW_LAYOUT_ETS_TAG);
    EXPECT_TRUE(frameNode_->GetLayoutProperty()->GetNeedLazyLayout());
    EXPECT_EQ(frameNode_->GetGeometryNode()->GetFrameSize(), SizeF(LAZY_WATER_FLOW_SCROLL_WIDTH, 500.0f));
    EXPECT_EQ(pattern_->layoutInfo_->startIndex_, 0);
    EXPECT_EQ(pattern_->layoutInfo_->endIndex_, 4);
}

/**
 * @tc.name: WaterfallMeasure_001
 * @tc.desc: Verify items are placed into the shortest lane.
 * @tc.type: FUNC
 */
HWTEST_F(LazyVWaterFlowLayoutCoreTest, WaterfallMeasure_001, TestSize.Level1)
{
    CreateWaterFlow();
    CreateLazyWaterFlowLayout();
    LazyVWaterFlowLayoutModel::SetColumnsTemplate("1fr 1fr");
    CreateContent({ 100.0f, 150.0f, 90.0f, 120.0f });
    CreateDone();

    ASSERT_NE(pattern_, nullptr);
    ASSERT_EQ(pattern_->layoutInfo_->posMap_.size(), 4u);
    EXPECT_EQ(pattern_->layoutInfo_->posMap_[0].laneIdx, 0);
    EXPECT_EQ(pattern_->layoutInfo_->posMap_[1].laneIdx, 1);
    EXPECT_EQ(pattern_->layoutInfo_->posMap_[2].laneIdx, 0);
    EXPECT_EQ(pattern_->layoutInfo_->posMap_[3].laneIdx, 1);
    EXPECT_EQ(pattern_->layoutInfo_->posMap_[2].startPos, 100.0f);
    EXPECT_EQ(pattern_->layoutInfo_->posMap_[3].startPos, 150.0f);
    EXPECT_EQ(pattern_->layoutInfo_->totalMainSize_, 270.0f);
    EXPECT_EQ(GetChildX(frameNode_, 1), 100.0f);
    EXPECT_EQ(GetChildY(frameNode_, 2), 100.0f);
}

/**
 * @tc.name: ItemFillPolicy_001
 * @tc.desc: Verify ItemFillPolicy is stored, cleared by string columnsTemplate, and used for lanes.
 * @tc.type: FUNC
 */
HWTEST_F(LazyVWaterFlowLayoutCoreTest, ItemFillPolicy_001, TestSize.Level1)
{
    CreateWaterFlow();
    CreateLazyWaterFlowLayout();
    LazyVWaterFlowLayoutModel::SetItemFillPolicy(PresetFillType::BREAKPOINT_SM1MD2LG3);

    ASSERT_NE(layoutProperty_, nullptr);
    ASSERT_TRUE(layoutProperty_->GetItemFillPolicy().has_value());
    EXPECT_EQ(layoutProperty_->GetItemFillPolicy().value(), PresetFillType::BREAKPOINT_SM1MD2LG3);

    LazyVWaterFlowLayoutModel::SetColumnsTemplate("1fr 1fr");
    EXPECT_FALSE(layoutProperty_->GetItemFillPolicy().has_value());

    LazyVWaterFlowLayoutModel::SetItemFillPolicy(PresetFillType::BREAKPOINT_SM1MD2LG3);
    CreateContent(4);
    CreateDone();

    ASSERT_NE(pattern_, nullptr);
    ASSERT_EQ(pattern_->layoutInfo_->crossLens_.size(), 1u);
    EXPECT_EQ(pattern_->layoutInfo_->totalMainSize_, 400.0f);
    EXPECT_EQ(GetChildX(frameNode_, 1), 0.0f);
    EXPECT_EQ(GetChildY(frameNode_, 1), 100.0f);
}

/**
 * @tc.name: GapClamp_001
 * @tc.desc: Verify negative gaps are clamped to zero.
 * @tc.type: FUNC
 */
HWTEST_F(LazyVWaterFlowLayoutCoreTest, GapClamp_001, TestSize.Level1)
{
    CreateWaterFlow();
    CreateLazyWaterFlowLayout();
    LazyVWaterFlowLayoutModel::SetColumnsTemplate("1fr 1fr");
    LazyWaterFlowLayoutModel::SetRowGap(Dimension(-10.0));
    LazyWaterFlowLayoutModel::SetColumnGap(Dimension(-20.0));
    CreateContent(4);
    CreateDone();

    ASSERT_NE(pattern_, nullptr);
    EXPECT_EQ(pattern_->layoutInfo_->totalMainSize_, 200.0f);
    EXPECT_EQ(GetChildX(frameNode_, 1), 100.0f);
    EXPECT_EQ(GetChildY(frameNode_, 2), 100.0f);
}

/**
 * @tc.name: OnVisibleIndexesChange_001
 * @tc.desc: Verify onVisibleIndexesChange is fired after the first layout.
 * @tc.type: FUNC
 */
HWTEST_F(LazyVWaterFlowLayoutCoreTest, OnVisibleIndexesChange_001, TestSize.Level1)
{
    CreateScroll();
    CreateLazyWaterFlowLayout();

    int32_t callCount = 0;
    std::pair<int32_t, int32_t> visibleRange = { -1, -1 };
    LazyWaterFlowLayoutModel::SetOnVisibleIndexesChange([&callCount, &visibleRange](int32_t start, int32_t end) {
        ++callCount;
        visibleRange = { start, end };
    });

    CreateContent(4);
    CreateDone();

    EXPECT_GT(callCount, 0);
    EXPECT_EQ(visibleRange.first, 0);
    EXPECT_EQ(visibleRange.second, 3);
    EXPECT_NE(scrollablePattern_, nullptr);
    pattern_->SetOnVisibleIndexesChange(nullptr);
}

/**
 * @tc.name: OnVisibleIndexesChangeEmpty_001
 * @tc.desc: Verify onVisibleIndexesChange reports -1 when LazyVWaterFlowLayout has no children.
 * @tc.type: FUNC
 */
HWTEST_F(LazyVWaterFlowLayoutCoreTest, OnVisibleIndexesChangeEmpty_001, TestSize.Level1)
{
    CreateScroll();
    CreateLazyWaterFlowLayout();

    std::pair<int32_t, int32_t> visibleRange = { 0, 0 };
    LazyWaterFlowLayoutModel::SetOnVisibleIndexesChange([&visibleRange](int32_t start, int32_t end) {
        visibleRange = { start, end };
    });

    CreateDone();

    EXPECT_EQ(visibleRange.first, -1);
    EXPECT_EQ(visibleRange.second, -1);
    pattern_->SetOnVisibleIndexesChange(nullptr);
}

/**
 * @tc.name: OnVisibleIndexesChangeReset_001
 * @tc.desc: Verify replacing the callback refires the current visible range without requiring a scroll change.
 * @tc.type: FUNC
 */
HWTEST_F(LazyVWaterFlowLayoutCoreTest, OnVisibleIndexesChangeReset_001, TestSize.Level1)
{
    CreateScroll();
    CreateLazyWaterFlowLayout();

    int32_t firstCallbackCount = 0;
    std::pair<int32_t, int32_t> firstRange = { -1, -1 };
    LazyWaterFlowLayoutModel::SetOnVisibleIndexesChange([&firstCallbackCount, &firstRange](int32_t start, int32_t end) {
        ++firstCallbackCount;
        firstRange = { start, end };
    });

    CreateContent(4);
    CreateDone();

    ASSERT_NE(pattern_, nullptr);
    EXPECT_GT(firstCallbackCount, 0);
    EXPECT_EQ(firstRange.first, 0);
    EXPECT_EQ(firstRange.second, 3);

    int32_t secondCallbackCount = 0;
    std::pair<int32_t, int32_t> secondRange = { -1, -1 };
    pattern_->SetOnVisibleIndexesChange([&secondCallbackCount, &secondRange](int32_t start, int32_t end) {
        ++secondCallbackCount;
        secondRange = { start, end };
    });
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    FlushUITasks();

    EXPECT_EQ(secondCallbackCount, 1);
    EXPECT_EQ(secondRange.first, 0);
    EXPECT_EQ(secondRange.second, 3);
    pattern_->SetOnVisibleIndexesChange(nullptr);
}

/**
 * @tc.name: OnInActiveRefiresVisibleRange_001
 * @tc.desc: Verify the visible-range callback is reported again after inactive -> active without requiring a scroll.
 * @tc.type: FUNC
 */
HWTEST_F(LazyVWaterFlowLayoutCoreTest, OnInActiveRefiresVisibleRange_001, TestSize.Level1)
{
    CreateScroll();
    CreateLazyWaterFlowLayout();

    int32_t callCount = 0;
    std::pair<int32_t, int32_t> visibleRange = { -1, -1 };
    LazyWaterFlowLayoutModel::SetOnVisibleIndexesChange([&callCount, &visibleRange](int32_t start, int32_t end) {
        ++callCount;
        visibleRange = { start, end };
    });

    CreateContent(4);
    CreateDone();

    ASSERT_NE(pattern_, nullptr);
    ASSERT_NE(frameNode_, nullptr);
    EXPECT_EQ(visibleRange.first, 0);
    EXPECT_EQ(visibleRange.second, 3);
    const auto callCountAfterCreate = callCount;

    pattern_->OnInActive();
    EXPECT_EQ(callCount, callCountAfterCreate + 1);
    EXPECT_EQ(visibleRange.first, -1);
    EXPECT_EQ(visibleRange.second, -1);

    frameNode_->SetActive();
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    FlushUITasks();

    EXPECT_EQ(callCount, callCountAfterCreate + 2);
    EXPECT_EQ(visibleRange.first, 0);
    EXPECT_EQ(visibleRange.second, 3);
    pattern_->SetOnVisibleIndexesChange(nullptr);
}

/**
 * @tc.name: OnActiveKeepsSizeCache_001
 * @tc.desc: Verify inactive -> active viewport toggles keep stable item-size estimates and positions.
 * @tc.type: FUNC
 */
HWTEST_F(LazyVWaterFlowLayoutCoreTest, OnActiveKeepsSizeCache_001, TestSize.Level1)
{
    CreateList();
    CreateLazyWaterFlowLayout();
    LazyVWaterFlowLayoutModel::SetColumnsTemplate("1fr 1fr");
    CreateContent(8);
    CreateDone();

    ASSERT_NE(pattern_, nullptr);
    ASSERT_NE(frameNode_, nullptr);
    auto layoutInfo = pattern_->layoutInfo_;
    ASSERT_NE(layoutInfo, nullptr);
    ASSERT_TRUE(layoutInfo->GetCachedHeight(0).has_value());
    const auto estimatedSize = layoutInfo->estimateItemSize_;
    const auto itemPositions = layoutInfo->posMap_;

    frameNode_->SetActive(false);
    frameNode_->SetActive(true);
    FlushUITasks();
    frameNode_->SetActive(false);
    frameNode_->SetActive(true);
    FlushUITasks();

    EXPECT_TRUE(layoutInfo->GetCachedHeight(0).has_value());
    EXPECT_FLOAT_EQ(layoutInfo->estimateItemSize_, estimatedSize);
    ASSERT_EQ(layoutInfo->posMap_.size(), itemPositions.size());
    for (const auto& [index, pos] : itemPositions) {
        auto currentPos = layoutInfo->GetPos(index);
        ASSERT_NE(currentPos, nullptr);
        EXPECT_EQ(currentPos->laneIdx, pos.laneIdx);
        EXPECT_FLOAT_EQ(currentPos->startPos, pos.startPos);
        EXPECT_FLOAT_EQ(currentPos->endPos, pos.endPos);
    }
}

/**
 * @tc.name: VisibleRangeNoVisibleItems_001
 * @tc.desc: Verify visible range is empty when measured items do not intersect the visible viewport.
 * @tc.type: FUNC
 */
HWTEST_F(LazyVWaterFlowLayoutCoreTest, VisibleRangeNoVisibleItems_001, TestSize.Level1)
{
    auto layoutInfo = AceType::MakeRefPtr<LazyWaterFlowLayoutInfo>();
    layoutInfo->SetTotalItemCount(2);
    layoutInfo->SetPosMap(0, { .laneIdx = 0, .startPos = 100.0f, .endPos = 150.0f });
    layoutInfo->SetPosMap(1, { .laneIdx = 0, .startPos = 150.0f, .endPos = 200.0f });

    layoutInfo->UpdateVisibleRange(0.0f, 50.0f);

    EXPECT_EQ(layoutInfo->startIndex_, -1);
    EXPECT_EQ(layoutInfo->endIndex_, -1);

    layoutInfo->UpdateVisibleRange(50.0f, 50.0f);

    EXPECT_EQ(layoutInfo->startIndex_, -1);
    EXPECT_EQ(layoutInfo->endIndex_, -1);
}

/**
 * @tc.name: CachedRangeNoCachedItems_001
 * @tc.desc: Verify cache range stays empty when measured items do not intersect the cache viewport.
 * @tc.type: FUNC
 */
HWTEST_F(LazyVWaterFlowLayoutCoreTest, CachedRangeNoCachedItems_001, TestSize.Level1)
{
    auto layoutInfo = AceType::MakeRefPtr<LazyWaterFlowLayoutInfo>();
    layoutInfo->SetTotalItemCount(2);
    layoutInfo->SetPosMap(0, { .laneIdx = 0, .startPos = 100.0f, .endPos = 150.0f });
    layoutInfo->SetPosMap(1, { .laneIdx = 0, .startPos = 150.0f, .endPos = 200.0f });

    layoutInfo->UpdateCachedRange(0.0f, 50.0f);

    EXPECT_EQ(layoutInfo->cachedStartIndex_, -1);
    EXPECT_EQ(layoutInfo->cachedEndIndex_, -1);
}

/**
 * @tc.name: NeedPredictUsesShortestLane_001
 * @tc.desc: Verify predict continues while any lane can still place an item inside the cache window.
 * @tc.type: FUNC
 */
HWTEST_F(LazyVWaterFlowLayoutCoreTest, NeedPredictUsesShortestLane_001, TestSize.Level1)
{
    auto layoutInfo = AceType::MakeRefPtr<LazyWaterFlowLayoutInfo>();
    layoutInfo->SetTotalItemCount(3);
    layoutInfo->SetPosMap(0, { .laneIdx = 0, .startPos = 0.0f, .endPos = 100.0f });
    layoutInfo->SetPosMap(1, { .laneIdx = 1, .startPos = 0.0f, .endPos = 500.0f });
    layoutInfo->laneEndPos_ = { 100.0f, 500.0f };
    layoutInfo->UpdateCachedRange(0.0f, 300.0f);

    EXPECT_EQ(layoutInfo->cachedEndIndex_, 1);
    EXPECT_TRUE(layoutInfo->NeedPredict());

    layoutInfo->laneEndPos_ = { 320.0f, 500.0f };

    EXPECT_FALSE(layoutInfo->NeedPredict());
}

/**
 * @tc.name: NeedPredictSkipsOffscreenCacheOnlyWindow_001
 * @tc.desc: Verify cache overlap alone cannot start predict while the parent-extended view window is
 *           still fully before content.
 * @tc.type: FUNC
 */
HWTEST_F(LazyVWaterFlowLayoutCoreTest, NeedPredictSkipsOffscreenCacheOnlyWindow_001, TestSize.Level1)
{
    auto layoutInfo = AceType::MakeRefPtr<LazyWaterFlowLayoutInfo>();
    layoutInfo->SetTotalItemCount(3);
    layoutInfo->totalMainSize_ = 600.0f;
    layoutInfo->extendedViewStartPos_ = -568.0f;
    layoutInfo->extendedViewEndPos_ = 0.0f;
    layoutInfo->UpdateVisibleRange(-568.0f, 0.0f);
    layoutInfo->UpdateCachedRange(-852.0f, 284.0f);

    EXPECT_EQ(layoutInfo->startIndex_, -1);
    EXPECT_EQ(layoutInfo->endIndex_, -1);
    EXPECT_EQ(layoutInfo->cachedStartIndex_, -1);
    EXPECT_EQ(layoutInfo->cachedEndIndex_, -1);
    EXPECT_FALSE(layoutInfo->NeedPredict());
}

/**
 * @tc.name: NeedPredictContinuesStartedOffscreenCacheBuild_001
 * @tc.desc: Verify a parent-started offscreen preload can finish its cache window after a partial first pass.
 * @tc.type: FUNC
 */
HWTEST_F(LazyVWaterFlowLayoutCoreTest, NeedPredictContinuesStartedOffscreenCacheBuild_001, TestSize.Level1)
{
    auto layoutInfo = AceType::MakeRefPtr<LazyWaterFlowLayoutInfo>();
    layoutInfo->SetTotalItemCount(3);
    layoutInfo->totalMainSize_ = 600.0f;
    layoutInfo->SetPosMap(0, { .laneIdx = 0, .startPos = 0.0f, .endPos = 100.0f });
    layoutInfo->laneEndPos_ = { 100.0f, 0.0f };
    layoutInfo->extendedViewStartPos_ = -568.0f;
    layoutInfo->extendedViewEndPos_ = 0.0f;
    layoutInfo->UpdateVisibleRange(-568.0f, 0.0f);
    layoutInfo->UpdateCachedRange(-852.0f, 284.0f);

    EXPECT_EQ(layoutInfo->startIndex_, -1);
    EXPECT_EQ(layoutInfo->endIndex_, -1);
    EXPECT_EQ(layoutInfo->cachedStartIndex_, 0);
    EXPECT_EQ(layoutInfo->cachedEndIndex_, 0);
    EXPECT_TRUE(layoutInfo->NeedPredict());
}

/**
 * @tc.name: PredictEmptyMeasureKeepsCacheRangeEmpty_001
 * @tc.desc: Verify a predict pass that measures no item does not write an inverted cached range.
 * @tc.type: FUNC
 */
HWTEST_F(LazyVWaterFlowLayoutCoreTest, PredictEmptyMeasureKeepsCacheRangeEmpty_001, TestSize.Level1)
{
    auto layoutInfo = AceType::MakeRefPtr<LazyWaterFlowLayoutInfo>();
    layoutInfo->SetTotalItemCount(3);

    LazyWaterFlowLayoutAlgorithm algorithm(layoutInfo);
    algorithm.isPredictPass_ = true;
    algorithm.totalItemCount_ = 3;
    algorithm.UpdateMeasuredRanges();

    EXPECT_EQ(layoutInfo->cachedStartIndex_, -1);
    EXPECT_EQ(layoutInfo->cachedEndIndex_, -1);
}

/**
 * @tc.name: ItemSizeCacheResetOnCountChange_001
 * @tc.desc: Verify item-size estimates are cleared after structural item-count changes.
 * @tc.type: FUNC
 */
HWTEST_F(LazyVWaterFlowLayoutCoreTest, ItemSizeCacheResetOnCountChange_001, TestSize.Level1)
{
    auto layoutInfo = AceType::MakeRefPtr<LazyWaterFlowLayoutInfo>();
    layoutInfo->SetTotalItemCount(2);
    layoutInfo->CacheItemHeight(0, 80.0f);
    layoutInfo->EstimateItemSize();
    ASSERT_TRUE(layoutInfo->GetCachedHeight(0).has_value());
    EXPECT_FLOAT_EQ(layoutInfo->estimateItemSize_, 80.0f);

    layoutInfo->SetTotalItemCount(3);

    EXPECT_FALSE(layoutInfo->GetCachedHeight(0).has_value());
    EXPECT_FLOAT_EQ(layoutInfo->estimateItemSize_, -1.0f);
}

/**
 * @tc.name: ScrollVisibleRange_001
 * @tc.desc: Verify visible range updates when the parent Scroll changes reference position.
 * @tc.type: FUNC
 */
HWTEST_F(LazyVWaterFlowLayoutCoreTest, ScrollVisibleRange_001, TestSize.Level1)
{
    CreateScroll();
    CreateLazyWaterFlowLayout();
    LazyVWaterFlowLayoutModel::SetColumnsTemplate("1fr 1fr");
    CreateContent(12);
    CreateDone();

    ASSERT_NE(pattern_, nullptr);
    ASSERT_NE(scrollablePattern_, nullptr);
    EXPECT_EQ(pattern_->layoutInfo_->startIndex_, 0);
    EXPECT_EQ(pattern_->layoutInfo_->endIndex_, 9);

    scrollablePattern_->UpdateCurrentOffset(-120.0f, SCROLL_FROM_UPDATE);
    FlushUITasks();

    EXPECT_EQ(pattern_->layoutInfo_->startIndex_, 2);
    EXPECT_EQ(pattern_->layoutInfo_->endIndex_, 11);
}

/**
 * @tc.name: ScrollBackKeepsRememberedPositions_001
 * @tc.desc: Verify previously measured item heights survive a scroll-back-to-top, even though the
 *           top-anchor short-circuit re-anchors the lane window and clears the position map. Heights
 *           live in idxToHeight_ and are reused on the next average-size estimate.
 * @tc.type: FUNC
 */
HWTEST_F(LazyVWaterFlowLayoutCoreTest, ScrollBackKeepsRememberedPositions_001, TestSize.Level1)
{
    CreateScroll();
    CreateLazyWaterFlowLayout();
    LazyVWaterFlowLayoutModel::SetColumnsTemplate("1fr 1fr");
    CreateContent(30);
    CreateDone();

    ASSERT_NE(pattern_, nullptr);
    ASSERT_NE(scrollablePattern_, nullptr);
    ASSERT_FALSE(pattern_->layoutInfo_->posMap_.empty());
    const auto rememberedEndBeforeScroll = pattern_->layoutInfo_->posMap_.rbegin()->first;

    scrollablePattern_->UpdateCurrentOffset(-420.0f, SCROLL_FROM_UPDATE);
    FlushUITasks();

    const auto offsetAfterScrollDown = static_cast<float>(scrollablePattern_->GetTotalOffset());
    ASSERT_GT(offsetAfterScrollDown, 0.0f);
    ASSERT_FALSE(pattern_->layoutInfo_->posMap_.empty());
    const auto rememberedEndAfterScrollDown = pattern_->layoutInfo_->posMap_.rbegin()->first;
    EXPECT_GT(rememberedEndAfterScrollDown, rememberedEndBeforeScroll);
    ASSERT_TRUE(pattern_->layoutInfo_->GetCachedHeight(rememberedEndAfterScrollDown).has_value());

    scrollablePattern_->UpdateCurrentOffset(offsetAfterScrollDown, SCROLL_FROM_UPDATE);
    FlushUITasks();

    EXPECT_EQ(pattern_->layoutInfo_->startIndex_, 0);
    // Top-anchor short-circuit clears posMap_, so the position map only covers the freshly
    // refilled viewport. The cached height in idxToHeight_ must still be present so that the next
    // FillBack reuses it instead of paying for another Measure.
    EXPECT_TRUE(pattern_->layoutInfo_->GetCachedHeight(rememberedEndAfterScrollDown).has_value());
}

/**
 * @tc.name: ScrollKeepsVisibleOffsetOnItemResize_001
 * @tc.desc: Verify parent Scroll consumes lazy adjust offset when a cached item before the viewport grows.
 * @tc.type: FUNC
 */
HWTEST_F(LazyVWaterFlowLayoutCoreTest, ScrollKeepsVisibleOffsetOnItemResize_001, TestSize.Level1)
{
    CreateScroll();
    CreateLazyWaterFlowLayout();
    LazyVWaterFlowLayoutModel::SetColumnsTemplate("1fr");
    CreateContent(10);
    CreateDone();

    ASSERT_NE(pattern_, nullptr);
    ASSERT_NE(scrollablePattern_, nullptr);
    scrollablePattern_->UpdateCurrentOffset(-250.0f, SCROLL_FROM_UPDATE);
    FlushUITasks();

    auto firstVisibleIndex = pattern_->layoutInfo_->startIndex_;
    auto firstVisiblePos = pattern_->layoutInfo_->GetPos(firstVisibleIndex);
    ASSERT_NE(firstVisiblePos, nullptr);
    auto offsetBefore = static_cast<float>(scrollablePattern_->GetTotalOffset());
    auto firstVisibleViewportY = firstVisiblePos->startPos - offsetBefore;

    auto firstChild = GetChildFrameNode(frameNode_, 0);
    ASSERT_NE(firstChild, nullptr);
    firstChild->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(1.0f, DimensionUnit::PERCENT), CalcLength(200.0f)));
    firstChild->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    pattern_->NotifyDataChange(0, 0);
    FlushUITasks();

    auto offsetAfter = static_cast<float>(scrollablePattern_->GetTotalOffset());
    auto firstVisiblePosAfter = pattern_->layoutInfo_->GetPos(firstVisibleIndex);
    ASSERT_NE(firstVisiblePosAfter, nullptr);
    EXPECT_FLOAT_EQ(offsetAfter, offsetBefore + 100.0f);
    EXPECT_FLOAT_EQ(firstVisiblePosAfter->startPos - offsetAfter, firstVisibleViewportY);
}

/**
 * @tc.name: LazyForEachTopInsertKeepsVisiblePosition_001
 * @tc.desc: Verify LazyForEach insert at the top returns adjust offset to keep the old first item stable.
 * @tc.type: FUNC
 */
HWTEST_F(LazyVWaterFlowLayoutCoreTest, LazyForEachTopInsertKeepsVisiblePosition_001, TestSize.Level1)
{
    CreateScroll();
    CreateLazyWaterFlowLayout();
    LazyVWaterFlowLayoutModel::SetColumnsTemplate("1fr");

    auto mockLazy = AceType::MakeRefPtr<LazyWaterFlowMockLazy>(std::vector<float>(10, 100.0f));
    RefPtr<LazyForEachActuator> mockLazyActuator = mockLazy;
    ViewStackProcessor::GetInstance()->StartGetAccessRecordingFor(GetElmtId());
    LazyForEachModelNG lazyForEachModel;
    lazyForEachModel.Create(mockLazyActuator);
    ViewStackProcessor::GetInstance()->Pop();
    ViewStackProcessor::GetInstance()->StopGetAccessRecording();
    CreateDone();

    ASSERT_NE(pattern_, nullptr);
    ASSERT_NE(scrollablePattern_, nullptr);
    auto lazyForEachNode = AceType::DynamicCast<LazyForEachNode>(frameNode_->GetChildAtIndex(0));
    ASSERT_NE(lazyForEachNode, nullptr);

    const auto firstVisibleIndex = pattern_->layoutInfo_->startIndex_;
    EXPECT_EQ(firstVisibleIndex, 0);
    auto firstVisiblePos = pattern_->layoutInfo_->GetPos(firstVisibleIndex);
    ASSERT_NE(firstVisiblePos, nullptr);
    const auto offsetBefore = static_cast<float>(scrollablePattern_->GetTotalOffset());
    EXPECT_FLOAT_EQ(offsetBefore, 0.0f);
    const auto firstVisibleViewportY = firstVisiblePos->startPos - offsetBefore;

    mockLazy->Insert(0, 100.0f);
    lazyForEachNode->OnDataAdded(0);
    FlushUITasks();

    auto offsetAfter = static_cast<float>(scrollablePattern_->GetTotalOffset());
    auto insertedPos = pattern_->layoutInfo_->GetPos(0);
    auto shiftedVisiblePos = pattern_->layoutInfo_->GetPos(firstVisibleIndex + 1);
    ASSERT_NE(insertedPos, nullptr);
    ASSERT_NE(shiftedVisiblePos, nullptr);
    EXPECT_FLOAT_EQ(offsetAfter, offsetBefore + 100.0f);
    EXPECT_FLOAT_EQ(insertedPos->startPos, 0.0f);
    EXPECT_FLOAT_EQ(insertedPos->endPos, 100.0f);
    EXPECT_FLOAT_EQ(shiftedVisiblePos->startPos - offsetAfter, firstVisibleViewportY);
    EXPECT_EQ(pattern_->layoutInfo_->startIndex_, firstVisibleIndex + 1);
}

/**
 * @tc.name: LazyForEachScrollBackTopInsertKeepsNewItemsAboveViewport_001
 * @tc.desc: Verify top insert after scrolling down and back uses the content-start boundary.
 * @tc.type: FUNC
 */
HWTEST_F(LazyVWaterFlowLayoutCoreTest, LazyForEachScrollBackTopInsertKeepsNewItemsAboveViewport_001, TestSize.Level1)
{
    CreateScroll();
    CreateLazyWaterFlowLayout();
    LazyVWaterFlowLayoutModel::SetColumnsTemplate("1fr 1fr");

    auto mockLazy = CreateLazyForEachContent(
        std::vector<float> { 70.0f, 150.0f, 90.0f, 210.0f, 80.0f, 120.0f, 180.0f, 100.0f, 160.0f, 110.0f },
        GetElmtId());
    CreateDone();

    ASSERT_NE(pattern_, nullptr);
    ASSERT_NE(scrollablePattern_, nullptr);
    auto lazyForEachNode = AceType::DynamicCast<LazyForEachNode>(frameNode_->GetChildAtIndex(0));
    ASSERT_NE(lazyForEachNode, nullptr);

    scrollablePattern_->UpdateCurrentOffset(-260.0f, SCROLL_FROM_UPDATE);
    FlushUITasks();
    const auto offsetAfterScrollDown = static_cast<float>(scrollablePattern_->GetTotalOffset());
    EXPECT_GT(offsetAfterScrollDown, 0.0f);

    scrollablePattern_->UpdateCurrentOffset(offsetAfterScrollDown, SCROLL_FROM_UPDATE);
    FlushUITasks();
    EXPECT_FLOAT_EQ(static_cast<float>(scrollablePattern_->GetTotalOffset()), 0.0f);

    const auto topIndexBeforeInsert = pattern_->layoutInfo_->startIndex_;
    EXPECT_EQ(topIndexBeforeInsert, 0);
    auto topPosBeforeInsert = pattern_->layoutInfo_->GetPos(topIndexBeforeInsert);
    ASSERT_NE(topPosBeforeInsert, nullptr);
    const auto topViewportY = topPosBeforeInsert->startPos;

    constexpr int32_t insertCount = 4;
    InsertTopBatch(mockLazy, lazyForEachNode, insertCount, 50.0f);
    FlushUITasks();

    const auto offsetAfterInsert = static_cast<float>(scrollablePattern_->GetTotalOffset());
    EXPECT_GT(offsetAfterInsert, 0.0f);
    for (int32_t i = 0; i < insertCount; ++i) {
        auto insertedPos = pattern_->layoutInfo_->GetPos(i);
        ASSERT_NE(insertedPos, nullptr);
        EXPECT_LE(insertedPos->endPos, offsetAfterInsert);
    }
    auto shiftedTopPos = pattern_->layoutInfo_->GetPos(topIndexBeforeInsert + insertCount);
    ASSERT_NE(shiftedTopPos, nullptr);
    EXPECT_FLOAT_EQ(shiftedTopPos->startPos - offsetAfterInsert, topViewportY);
    EXPECT_EQ(pattern_->layoutInfo_->startIndex_, topIndexBeforeInsert + insertCount);
}

/**
 * @tc.name: LazyForEachInsertOnBackScrollKeepsNewItemsAboveViewport_001
 * @tc.desc: Verify top insert while scrolling back but not at top does not fill the shortest lane in the viewport.
 * @tc.type: FUNC
 */
HWTEST_F(LazyVWaterFlowLayoutCoreTest, LazyForEachInsertOnBackScrollKeepsNewItemsAboveViewport_001, TestSize.Level1)
{
    CreateScroll();
    CreateLazyWaterFlowLayout();
    LazyVWaterFlowLayoutModel::SetColumnsTemplate("1fr 1fr");

    auto mockLazy = CreateLazyForEachContent(
        std::vector<float> { 70.0f, 150.0f, 90.0f, 210.0f, 80.0f, 120.0f, 180.0f, 100.0f, 160.0f, 110.0f },
        GetElmtId());
    CreateDone();

    ASSERT_NE(pattern_, nullptr);
    ASSERT_NE(scrollablePattern_, nullptr);
    auto lazyForEachNode = AceType::DynamicCast<LazyForEachNode>(frameNode_->GetChildAtIndex(0));
    ASSERT_NE(lazyForEachNode, nullptr);

    scrollablePattern_->UpdateCurrentOffset(-260.0f, SCROLL_FROM_UPDATE);
    FlushUITasks();
    const auto offsetAfterScrollDown = static_cast<float>(scrollablePattern_->GetTotalOffset());
    ASSERT_GT(offsetAfterScrollDown, 80.0f);

    scrollablePattern_->UpdateCurrentOffset(offsetAfterScrollDown - 40.0f, SCROLL_FROM_UPDATE);
    FlushUITasks();
    const auto offsetBeforeInsert = static_cast<float>(scrollablePattern_->GetTotalOffset());
    EXPECT_GT(offsetBeforeInsert, 0.0f);
    EXPECT_LT(offsetBeforeInsert, offsetAfterScrollDown);

    const auto firstVisibleIndex = pattern_->layoutInfo_->startIndex_;
    auto firstVisiblePos = pattern_->layoutInfo_->GetPos(firstVisibleIndex);
    ASSERT_NE(firstVisiblePos, nullptr);
    const auto firstVisibleViewportY = firstVisiblePos->startPos - offsetBeforeInsert;

    constexpr int32_t insertCount = 4;
    InsertTopBatch(mockLazy, lazyForEachNode, insertCount, 50.0f);
    FlushUITasks();

    const auto offsetAfterInsert = static_cast<float>(scrollablePattern_->GetTotalOffset());
    EXPECT_GT(offsetAfterInsert, offsetBeforeInsert);
    for (int32_t i = 0; i < insertCount; ++i) {
        auto insertedPos = pattern_->layoutInfo_->GetPos(i);
        ASSERT_NE(insertedPos, nullptr);
        EXPECT_LE(insertedPos->endPos, offsetAfterInsert);
    }
    auto shiftedFirstVisiblePos = pattern_->layoutInfo_->GetPos(firstVisibleIndex + insertCount);
    ASSERT_NE(shiftedFirstVisiblePos, nullptr);
    EXPECT_FLOAT_EQ(shiftedFirstVisiblePos->startPos - offsetAfterInsert, firstVisibleViewportY);
    EXPECT_EQ(pattern_->layoutInfo_->startIndex_, firstVisibleIndex + insertCount);
}

/**
 * @tc.name: LazyForEachAppendOutsideViewportKeepsOffset_001
 * @tc.desc: Verify LazyForEach insertion after the viewport does not move the parent Scroll offset.
 * @tc.type: FUNC
 */
HWTEST_F(LazyVWaterFlowLayoutCoreTest, LazyForEachAppendOutsideViewportKeepsOffset_001, TestSize.Level1)
{
    CreateScroll();
    CreateLazyWaterFlowLayout();
    LazyVWaterFlowLayoutModel::SetColumnsTemplate("1fr");

    auto mockLazy = AceType::MakeRefPtr<LazyWaterFlowMockLazy>(std::vector<float>(10, 100.0f));
    RefPtr<LazyForEachActuator> mockLazyActuator = mockLazy;
    ViewStackProcessor::GetInstance()->StartGetAccessRecordingFor(GetElmtId());
    LazyForEachModelNG lazyForEachModel;
    lazyForEachModel.Create(mockLazyActuator);
    ViewStackProcessor::GetInstance()->Pop();
    ViewStackProcessor::GetInstance()->StopGetAccessRecording();
    CreateDone();

    ASSERT_NE(pattern_, nullptr);
    ASSERT_NE(scrollablePattern_, nullptr);
    auto lazyForEachNode = AceType::DynamicCast<LazyForEachNode>(frameNode_->GetChildAtIndex(0));
    ASSERT_NE(lazyForEachNode, nullptr);

    scrollablePattern_->UpdateCurrentOffset(-250.0f, SCROLL_FROM_UPDATE);
    FlushUITasks();

    const auto firstVisibleIndex = pattern_->layoutInfo_->startIndex_;
    auto firstVisiblePos = pattern_->layoutInfo_->GetPos(firstVisibleIndex);
    ASSERT_NE(firstVisiblePos, nullptr);
    const auto offsetBefore = static_cast<float>(scrollablePattern_->GetTotalOffset());
    const auto firstVisibleViewportY = firstVisiblePos->startPos - offsetBefore;

    mockLazy->Insert(10, 100.0f);
    lazyForEachNode->OnDataAdded(10);
    FlushUITasks();

    auto offsetAfter = static_cast<float>(scrollablePattern_->GetTotalOffset());
    auto firstVisiblePosAfter = pattern_->layoutInfo_->GetPos(firstVisibleIndex);
    ASSERT_NE(firstVisiblePosAfter, nullptr);
    EXPECT_FLOAT_EQ(offsetAfter, offsetBefore);
    EXPECT_FLOAT_EQ(firstVisiblePosAfter->startPos - offsetAfter, firstVisibleViewportY);
}

/**
 * @tc.name: ScrollAxisFallbackFullRange_001
 * @tc.desc: Verify a parent Scroll changing to horizontal falls back to full-range lazy measurement.
 * @tc.type: FUNC
 */
HWTEST_F(LazyVWaterFlowLayoutCoreTest, ScrollAxisFallbackFullRange_001, TestSize.Level1)
{
    CreateScroll();
    CreateLazyWaterFlowLayout();
    LazyVWaterFlowLayoutModel::SetColumnsTemplate("1fr 1fr");
    CreateContent(30);
    CreateDone();

    ASSERT_NE(pattern_, nullptr);
    ASSERT_NE(scrollableFrameNode_, nullptr);
    EXPECT_EQ(pattern_->layoutInfo_->layoutedStartIndex_, 0);
    EXPECT_EQ(pattern_->layoutInfo_->layoutedEndIndex_, 9);
    // Cache is synchronously filled by Measure (Option A), so no predict gap remains.
    EXPECT_FALSE(pattern_->layoutInfo_->NeedPredict());

    ScrollModelNG::SetAxis(AceType::RawPtr(scrollableFrameNode_), Axis::HORIZONTAL);
    pattern_->OnModifyDone();
    FlushUITasks();

    EXPECT_EQ(pattern_->layoutInfo_->layoutedStartIndex_, 0);
    EXPECT_EQ(pattern_->layoutInfo_->layoutedEndIndex_, 29);
    EXPECT_EQ(pattern_->layoutInfo_->cachedStartIndex_, 0);
    EXPECT_EQ(pattern_->layoutInfo_->cachedEndIndex_, 29);
    EXPECT_FALSE(pattern_->layoutInfo_->NeedPredict());
}

/**
 * @tc.name: MissingAnchorAdjustOffset_001
 * @tc.desc: Verify adjust offset stays zero when there is no structural data change.
 * @tc.type: FUNC
 */
HWTEST_F(LazyVWaterFlowLayoutCoreTest, MissingAnchorAdjustOffset_001, TestSize.Level1)
{
    auto layoutInfo = AceType::MakeRefPtr<LazyWaterFlowLayoutInfo>();
    layoutInfo->SetTotalItemCount(3);
    layoutInfo->SetPosMap(0, { .laneIdx = 0, .startPos = 60.0f, .endPos = 120.0f });
    layoutInfo->UpdateVisibleRange(50.0f, 100.0f);

    LazyWaterFlowLayoutAlgorithm algorithm(layoutInfo);
    LazyWaterFlowLayoutAlgorithm::PrevFrameSnapshot prevFrameSnapshot;
    prevFrameSnapshot.anchor.startIndex = 5;
    prevFrameSnapshot.anchor.startPos = LazyWaterFlowItemMainPos { .laneIdx = 0, .startPos = 100.0f, .endPos = 160.0f };
    prevFrameSnapshot.anchor.endIndex = 6;
    prevFrameSnapshot.anchor.endPos = LazyWaterFlowItemMainPos { .laneIdx = 0, .startPos = 180.0f, .endPos = 220.0f };

    algorithm.UpdateAdjustOffset(prevFrameSnapshot);

    EXPECT_FLOAT_EQ(layoutInfo->adjustOffset_.start, 0.0f);
    EXPECT_FLOAT_EQ(layoutInfo->adjustOffset_.end, 0.0f);
}

/**
 * @tc.name: EndAnchorAdjustOffset_AnchorLocated_001
 * @tc.desc: Verify backward-measured nested lazy (referenceEdge_=END) takes the END-anchor delta path when
 *           the previous-frame end item is still located in this frame's posMap_. This path is reached
 *           when the LazyVWaterFlow is nested under a parent that fills backward (e.g. List backward measurement
 *           via list_layout_algorithm.cpp:2170, or WaterFlow SW reverse fill via water_flow_layout_sw.cpp:994).
 * @tc.type: FUNC
 */
HWTEST_F(LazyVWaterFlowLayoutCoreTest, EndAnchorAdjustOffset_AnchorLocated_001, TestSize.Level1)
{
    auto layoutInfo = AceType::MakeRefPtr<LazyWaterFlowLayoutInfo>();
    layoutInfo->SetTotalItemCount(8);
    // New-frame layout: item 5 ends at 250; total grew by 50 vs prev frame.
    layoutInfo->SetPosMap(5, { .laneIdx = 0, .startPos = 200.0f, .endPos = 250.0f });

    LazyWaterFlowLayoutAlgorithm algorithm(layoutInfo);
    algorithm.referenceEdge_ = ReferenceEdge::END;
    algorithm.totalMainSize_ = 350.0f;

    LazyWaterFlowLayoutAlgorithm::PrevFrameSnapshot prevFrameSnapshot;
    prevFrameSnapshot.anchor.startIndex = 4;
    prevFrameSnapshot.anchor.startPos = LazyWaterFlowItemMainPos { .laneIdx = 0, .startPos = 100.0f, .endPos = 150.0f };
    prevFrameSnapshot.anchor.endIndex = 5;
    prevFrameSnapshot.anchor.endPos = LazyWaterFlowItemMainPos { .laneIdx = 0, .startPos = 150.0f, .endPos = 200.0f };
    prevFrameSnapshot.anchor.totalMainSize = 300.0f;

    algorithm.UpdateAdjustOffset(prevFrameSnapshot);

    // END-anchor delta = newEndPos - oldEndPos = 250 - 200 = 50 (the trailing viewport shift).
    EXPECT_FLOAT_EQ(layoutInfo->adjustOffset_.end, 50.0f);
    // adjustOffset_.start absorbs the residual totalDelta. totalDelta = 50, end took 50, start = 0.
    EXPECT_FLOAT_EQ(layoutInfo->adjustOffset_.start, 0.0f);
}

/**
 * @tc.name: EndAnchorAdjustOffset_AnchorLocatedSplitsTotalDelta_001
 * @tc.desc: When the END-anchor item moves less than the total height delta (e.g. items inserted before the
 *           anchor caused total to grow but the anchor itself shifted by a smaller amount), END takes its
 *           own delta and START absorbs the residual so the parent scroll math still balances.
 * @tc.type: FUNC
 */
HWTEST_F(LazyVWaterFlowLayoutCoreTest, EndAnchorAdjustOffset_AnchorLocatedSplitsTotalDelta_001, TestSize.Level1)
{
    auto layoutInfo = AceType::MakeRefPtr<LazyWaterFlowLayoutInfo>();
    layoutInfo->SetTotalItemCount(8);
    // Anchor item (5) shifted down by 30; container grew by 100 (e.g. an extra item inserted at the tail).
    layoutInfo->SetPosMap(5, { .laneIdx = 0, .startPos = 180.0f, .endPos = 230.0f });

    LazyWaterFlowLayoutAlgorithm algorithm(layoutInfo);
    algorithm.referenceEdge_ = ReferenceEdge::END;
    algorithm.totalMainSize_ = 400.0f;

    LazyWaterFlowLayoutAlgorithm::PrevFrameSnapshot prevFrameSnapshot;
    prevFrameSnapshot.anchor.endIndex = 5;
    prevFrameSnapshot.anchor.endPos = LazyWaterFlowItemMainPos { .laneIdx = 0, .startPos = 150.0f, .endPos = 200.0f };
    prevFrameSnapshot.anchor.totalMainSize = 300.0f;

    algorithm.UpdateAdjustOffset(prevFrameSnapshot);

    // END absorbs the anchor's own shift: 230 - 200 = 30.
    EXPECT_FLOAT_EQ(layoutInfo->adjustOffset_.end, 30.0f);
    // START absorbs the residual: totalDelta(100) - end(30) = 70.
    EXPECT_FLOAT_EQ(layoutInfo->adjustOffset_.start, 70.0f);
}

/**
 * @tc.name: EndAnchorAdjustOffset_AnchorMissing_001
 * @tc.desc: When the previous-frame end-anchor item can no longer be located in the new posMap_ (e.g.
 *           data change deleted it or pushed it past the retained window), TryUpdateEndAnchorAdjust returns
 *           false and the START-anchor fallback path runs. Verify the fallback: anchor's start delta + residual
 *           into .end, no spurious END write.
 * @tc.type: FUNC
 */
HWTEST_F(LazyVWaterFlowLayoutCoreTest, EndAnchorAdjustOffset_AnchorMissing_001, TestSize.Level1)
{
    auto layoutInfo = AceType::MakeRefPtr<LazyWaterFlowLayoutInfo>();
    layoutInfo->SetTotalItemCount(8);
    // Start anchor (4) located in the new layout; end anchor (5) is NOT in posMap_.
    layoutInfo->SetPosMap(4, { .laneIdx = 0, .startPos = 120.0f, .endPos = 170.0f });

    LazyWaterFlowLayoutAlgorithm algorithm(layoutInfo);
    algorithm.referenceEdge_ = ReferenceEdge::END;
    algorithm.totalMainSize_ = 320.0f;

    LazyWaterFlowLayoutAlgorithm::PrevFrameSnapshot prevFrameSnapshot;
    prevFrameSnapshot.anchor.startIndex = 4;
    prevFrameSnapshot.anchor.startPos = LazyWaterFlowItemMainPos { .laneIdx = 0, .startPos = 100.0f, .endPos = 150.0f };
    prevFrameSnapshot.anchor.endIndex = 5;
    prevFrameSnapshot.anchor.endPos = LazyWaterFlowItemMainPos { .laneIdx = 0, .startPos = 150.0f, .endPos = 200.0f };
    prevFrameSnapshot.anchor.totalMainSize = 300.0f;

    algorithm.UpdateAdjustOffset(prevFrameSnapshot);

    // Fallback path: START anchor located → adjustOffset_.start = newStartPos - oldStartPos = 120 - 100 = 20.
    EXPECT_FLOAT_EQ(layoutInfo->adjustOffset_.start, 20.0f);
    // .end absorbs the residual: totalDelta(20) - start(20) = 0.
    EXPECT_FLOAT_EQ(layoutInfo->adjustOffset_.end, 0.0f);
}

/**
 * @tc.name: CheckResetClearsStaleMaxHeightOnTailShrinkPastWindow_001
 * @tc.desc: Regression: after a tail-side delete, NotifyDataChange's TransformLaneCacheAfterDataChange
 *           pops the deleted item from the lane cache, so the next Measure sees windowEnd one step earlier
 *           than the recorded updatedStart_. CheckReset's past-window branch (updateIdx > windowEnd) used to
 *           early-return without touching maxHeight_, leaving the sticky high-water mark tracking now-gone
 *           body height. Subsequent EstimateTotalHeight() then froze totalMainSize_ at the pre-delete value,
 *           making the parent's reachable scroll range stale. The fix gates the past-window branch on TWO
 *           conditions before resetting: (1) retained window has reached the new tail
 *           (windowEnd >= totalItemCount_-1) — confirms maxHeight_ is no longer legitimately holding a
 *           far-end scroll range for an unmaterialised tail; AND (2) lane high-water has dropped below
 *           maxHeight_ — confirms the sticky value is actually stale. Both conditions together → reset
 *           maxHeight_ and the boundary latch alongside the existing reset paths. Either alone is
 *           insufficient (see the two negative companions below).
 * @tc.type: FUNC
 */
HWTEST_F(LazyVWaterFlowLayoutCoreTest, CheckResetClearsStaleMaxHeightOnTailShrinkPastWindow_001, TestSize.Level1)
{
    auto layoutInfo = AceType::MakeRefPtr<LazyWaterFlowLayoutInfo>();
    // Simulate post tail-delete steady state. Pre-delete lanes held items 0..5 (lane.endPos = 600);
    // post-delete the lane was stripped of item 5 by TransformLaneCacheAfterDataChange, leaving items 0..4
    // at lane.endPos = 500. totalItemCount_ shrunk from 6 to 5. updatedStart_ = 5 (the deleted index).
    layoutInfo->SetTotalItemCount(5);
    layoutInfo->ResetLanes(1, 0.0f);
    layoutInfo->lanes_[0].items_.push_back({ 0, 100.0f });
    layoutInfo->lanes_[0].items_.push_back({ 1, 100.0f });
    layoutInfo->lanes_[0].items_.push_back({ 2, 100.0f });
    layoutInfo->lanes_[0].items_.push_back({ 3, 100.0f });
    layoutInfo->lanes_[0].items_.push_back({ 4, 100.0f });
    layoutInfo->lanes_[0].endPos = 500.0f;
    // Sticky high-water from before the delete (still holds items 0..5 → 600).
    layoutInfo->maxHeight_ = 600.0f;
    layoutInfo->totalOffset_ = 0.0f;
    layoutInfo->startIndex_ = 0;
    layoutInfo->endIndex_ = 4; // post-strip retained window
    layoutInfo->hasDataChange_ = true;
    layoutInfo->updatedStart_ = 5;
    layoutInfo->newStartIndex_ = -1;
    // Boundary latch held over from a previous bottom-edge frame; the fix should release it alongside.
    layoutInfo->prevItemEnd_ = true;

    LazyWaterFlowLayoutAlgorithm algorithm(layoutInfo);
    algorithm.totalItemCount_ = 5;

    const int32_t dirtyIdx = algorithm.CheckReset();

    // Past-window branch returns -1 (no rebuild needed beyond clearing the sticky).
    EXPECT_EQ(dirtyIdx, -1);
    // Stale maxHeight_ (600 > current lane high-water 500) reset to 0 so EstimateTotalHeight() can
    // shrink totalMainSize_ to the new tail.
    EXPECT_FLOAT_EQ(layoutInfo->maxHeight_, 0.0f);
    // Boundary latch released so the next DetectItemBoundary() can re-fire bottom snap on the new tail.
    EXPECT_FALSE(layoutInfo->prevItemEnd_);
}

/**
 * @tc.name: CheckResetKeepsHighWaterWhenLaneStillCoversIt_001
 * @tc.desc: Negative companion: the past-window reset must NOT fire when the lane high-water still
 *           covers the recorded maxHeight_ — i.e. the data change did not actually shrink the body.
 *           Guards against accidentally dropping maxHeight_ on benign past-window changes.
 * @tc.type: FUNC
 */
HWTEST_F(LazyVWaterFlowLayoutCoreTest, CheckResetKeepsHighWaterWhenLaneStillCoversIt_001, TestSize.Level1)
{
    auto layoutInfo = AceType::MakeRefPtr<LazyWaterFlowLayoutInfo>();
    layoutInfo->SetTotalItemCount(5);
    layoutInfo->ResetLanes(1, 0.0f);
    layoutInfo->lanes_[0].items_.push_back({ 0, 100.0f });
    layoutInfo->lanes_[0].items_.push_back({ 1, 100.0f });
    layoutInfo->lanes_[0].items_.push_back({ 2, 100.0f });
    layoutInfo->lanes_[0].items_.push_back({ 3, 100.0f });
    layoutInfo->lanes_[0].items_.push_back({ 4, 100.0f });
    layoutInfo->lanes_[0].endPos = 500.0f;
    // High-water already matches the current lane end — nothing stale.
    layoutInfo->maxHeight_ = 500.0f;
    layoutInfo->totalOffset_ = 0.0f;
    layoutInfo->startIndex_ = 0;
    layoutInfo->endIndex_ = 4;
    layoutInfo->hasDataChange_ = true;
    layoutInfo->updatedStart_ = 5;
    layoutInfo->newStartIndex_ = -1;
    layoutInfo->prevItemEnd_ = true;

    LazyWaterFlowLayoutAlgorithm algorithm(layoutInfo);
    algorithm.totalItemCount_ = 5;

    const int32_t dirtyIdx = algorithm.CheckReset();

    EXPECT_EQ(dirtyIdx, -1);
    // High-water preserved — current lane covers it, no stale state.
    EXPECT_FLOAT_EQ(layoutInfo->maxHeight_, 500.0f);
    // Boundary latch preserved too: nothing was stale to invalidate it.
    EXPECT_TRUE(layoutInfo->prevItemEnd_);
}

/**
 * @tc.name: CheckResetKeepsHighWaterWhenWindowDoesNotReachTail_001
 * @tc.desc: Negative companion guarding the past-window gate. When the retained window has NOT yet
 *           reached the new tail (windowEnd < totalItemCount_-1), maxHeight_'s sticky purpose is exactly
 *           to keep the far-end scroll range stable while the user scrolls the retained window back up
 *           from a previously-deeper position. Even if `lane.endPos < maxHeight_`, that is the legitimate
 *           steady-state — clearing maxHeight_ here would prematurely shrink scroll range mid-scroll. The
 *           past-window gate must require windowEnd == totalItemCount_-1 before considering reset.
 * @tc.type: FUNC
 */
HWTEST_F(LazyVWaterFlowLayoutCoreTest, CheckResetKeepsHighWaterWhenWindowDoesNotReachTail_001, TestSize.Level1)
{
    auto layoutInfo = AceType::MakeRefPtr<LazyWaterFlowLayoutInfo>();
    // Mid-scroll: 10 items total, retained window covers items 0..4 only (windowEnd < tail).
    layoutInfo->SetTotalItemCount(10);
    layoutInfo->ResetLanes(1, 0.0f);
    layoutInfo->lanes_[0].items_.push_back({ 0, 100.0f });
    layoutInfo->lanes_[0].items_.push_back({ 1, 100.0f });
    layoutInfo->lanes_[0].items_.push_back({ 2, 100.0f });
    layoutInfo->lanes_[0].items_.push_back({ 3, 100.0f });
    layoutInfo->lanes_[0].items_.push_back({ 4, 100.0f });
    layoutInfo->lanes_[0].endPos = 500.0f;
    // Sticky high-water from a deeper previous window (legitimately ahead of current lane.endPos).
    layoutInfo->maxHeight_ = 1000.0f;
    layoutInfo->totalOffset_ = 0.0f;
    layoutInfo->startIndex_ = 0;
    layoutInfo->endIndex_ = 4;
    layoutInfo->hasDataChange_ = true;
    // updateIdx past windowEnd (e.g. a refresh or insert past the retained window's far edge).
    layoutInfo->updatedStart_ = 7;
    layoutInfo->newStartIndex_ = -1;
    layoutInfo->prevItemEnd_ = true;

    LazyWaterFlowLayoutAlgorithm algorithm(layoutInfo);
    algorithm.totalItemCount_ = 10;

    const int32_t dirtyIdx = algorithm.CheckReset();

    EXPECT_EQ(dirtyIdx, -1);
    // High-water preserved — windowEnd (4) < totalItemCount_-1 (9), so sticky is doing its legitimate job.
    EXPECT_FLOAT_EQ(layoutInfo->maxHeight_, 1000.0f);
    // Boundary latch preserved.
    EXPECT_TRUE(layoutInfo->prevItemEnd_);
}

/**
 * @tc.name: ResetForFullRebuild_ClearsPerFrameState_001
 * @tc.desc: Verify ResetForFullRebuild zeros adjustOffset_ and cacheStartPos_/EndPos_ in addition to the
 *           previously cleared structural state. P0-A4 made it delegate to ResetPerFrameState first, so the
 *           per-frame derived fields are no longer left stale across the full rebuild path. SetTotalItemCount(0)
 *           is the public entry that funnels through ResetForFullRebuild. P1-B1 dropped the cross-frame
 *           layoutedStart_/End_ float fields; the layouted main-axis range now comes from GetLayoutedRange()
 *           on demand and degrades to {0, 0} when posMap_ is empty (verified below).
 * @tc.type: FUNC
 */
HWTEST_F(LazyVWaterFlowLayoutCoreTest, ResetForFullRebuild_ClearsPerFrameState_001, TestSize.Level1)
{
    auto layoutInfo = AceType::MakeRefPtr<LazyWaterFlowLayoutInfo>();
    layoutInfo->SetTotalItemCount(4);
    // Seed every field that the original ResetForFullRebuild left alone.
    layoutInfo->adjustOffset_.start = 12.0f;
    layoutInfo->adjustOffset_.end = 8.0f;
    layoutInfo->cacheStartPos_ = -25.0f;
    layoutInfo->cacheEndPos_ = 275.0f;
    // And a few that it always cleared, to confirm the structural reset still happens.
    layoutInfo->ResetLanes(2, 0.0f);
    layoutInfo->lanes_[0].items_.push_back({ 0, 100.0f });
    layoutInfo->idxToLane_[0] = 0;
    layoutInfo->CacheItemHeight(0, 100.0f);
    layoutInfo->totalOffset_ = 30.0f;
    layoutInfo->maxHeight_ = 400.0f;

    // Trigger ResetForFullRebuild via the SetTotalItemCount(0) entry.
    layoutInfo->SetTotalItemCount(0);

    // Per-frame state cleared (the new behavior introduced by P0-A4).
    EXPECT_FLOAT_EQ(layoutInfo->adjustOffset_.start, 0.0f);
    EXPECT_FLOAT_EQ(layoutInfo->adjustOffset_.end, 0.0f);
    EXPECT_FLOAT_EQ(layoutInfo->cacheStartPos_, 0.0f);
    EXPECT_FLOAT_EQ(layoutInfo->cacheEndPos_, 0.0f);
    // After full rebuild posMap_ is empty; GetLayoutedRange() falls back to {0, 0}, which collapses
    // CapturePendingAdjustAnchor's overlap filter to "no item visible" — the desired degenerate behavior.
    auto [layoutedStart, layoutedEnd] = layoutInfo->GetLayoutedRange();
    EXPECT_FLOAT_EQ(layoutedStart, 0.0f);
    EXPECT_FLOAT_EQ(layoutedEnd, 0.0f);
    // Structural state still cleared (unchanged behavior).
    EXPECT_TRUE(layoutInfo->lanes_.empty());
    EXPECT_TRUE(layoutInfo->idxToLane_.empty());
    EXPECT_FALSE(layoutInfo->GetCachedHeight(0).has_value());
    EXPECT_FLOAT_EQ(layoutInfo->totalOffset_, 0.0f);
    EXPECT_FLOAT_EQ(layoutInfo->maxHeight_, 0.0f);
}

/**
 * @tc.name: OrderedDataChangesRekeyStoredIndexes_001
 * @tc.desc: Verify same-frame insert/delete updates stored anchor indexes in notification order.
 * @tc.type: FUNC
 */
HWTEST_F(LazyVWaterFlowLayoutCoreTest, OrderedDataChangesRekeyStoredIndexes_001, TestSize.Level1)
{
    auto layoutInfo = AceType::MakeRefPtr<LazyWaterFlowLayoutInfo>();
    layoutInfo->SetTotalItemCount(4);
    layoutInfo->startIndex_ = 0;
    layoutInfo->endIndex_ = 1;
    layoutInfo->cachedStartIndex_ = 0;
    layoutInfo->cachedEndIndex_ = 1;

    layoutInfo->NotifyDataChange(0, 1);
    layoutInfo->NotifyDataChange(0, 1);
    layoutInfo->NotifyDataChange(0, -1);

    EXPECT_EQ(layoutInfo->startIndex_, 1);
    EXPECT_EQ(layoutInfo->endIndex_, 2);
    EXPECT_EQ(layoutInfo->cachedStartIndex_, 1);
    EXPECT_EQ(layoutInfo->cachedEndIndex_, 2);
    EXPECT_TRUE(layoutInfo->hasDataChange_);

    layoutInfo->ClearDataChanges();
    EXPECT_FALSE(layoutInfo->hasDataChange_);
}

/**
 * @tc.name: DataChangeRekeysItemSizeCacheOnInsert_001
 * @tc.desc: Verify a structural insert keeps measured item sizes under their transformed indexes.
 * @tc.type: FUNC
 */
HWTEST_F(LazyVWaterFlowLayoutCoreTest, DataChangeRekeysItemSizeCacheOnInsert_001, TestSize.Level1)
{
    auto layoutInfo = AceType::MakeRefPtr<LazyWaterFlowLayoutInfo>();
    layoutInfo->SetTotalItemCount(4);
    // ResetLanes clears the item-size cache as part of its lane-topology rebuild contract; seed sizes after it
    // so the test exercises NotifyDataChange's rekey on a populated cache (matches production ordering).
    layoutInfo->ResetLanes(1, 40.0f);
    layoutInfo->CacheItemHeight(0, 40.0f);
    layoutInfo->CacheItemHeight(1, 50.0f);
    layoutInfo->CacheItemHeight(2, 60.0f);
    layoutInfo->CacheItemHeight(3, 70.0f);
    layoutInfo->lanes_[0].endPos = 90.0f;
    layoutInfo->lanes_[0].items_.push_back({ 1, 50.0f });
    layoutInfo->idxToLane_[1] = 0;
    layoutInfo->EstimateItemSize();

    layoutInfo->NotifyDataChange(1, 2);
    layoutInfo->UpdateLanesIndex();
    layoutInfo->SyncItemPositions(0.0f);

    EXPECT_EQ(layoutInfo->totalItemCount_, 6);
    ASSERT_TRUE(layoutInfo->GetCachedHeight(0).has_value());
    EXPECT_FLOAT_EQ(layoutInfo->GetCachedHeight(0).value(), 40.0f);
    EXPECT_FALSE(layoutInfo->GetCachedHeight(1).has_value());
    EXPECT_FALSE(layoutInfo->GetCachedHeight(2).has_value());
    ASSERT_TRUE(layoutInfo->GetCachedHeight(3).has_value());
    EXPECT_FLOAT_EQ(layoutInfo->GetCachedHeight(3).value(), 50.0f);
    auto shiftedPos = layoutInfo->GetPos(3);
    ASSERT_NE(shiftedPos, nullptr);
    EXPECT_FLOAT_EQ(shiftedPos->startPos, 40.0f);
    ASSERT_TRUE(layoutInfo->GetCachedHeight(5).has_value());
    EXPECT_FLOAT_EQ(layoutInfo->GetCachedHeight(5).value(), 70.0f);
    EXPECT_FLOAT_EQ(layoutInfo->estimateItemSize_, 55.0f);
}

/**
 * @tc.name: DataChangeRekeysItemSizeCacheOnDelete_001
 * @tc.desc: Verify a structural delete keeps measured item sizes under their transformed indexes.
 * @tc.type: FUNC
 */
HWTEST_F(LazyVWaterFlowLayoutCoreTest, DataChangeRekeysItemSizeCacheOnDelete_001, TestSize.Level1)
{
    auto layoutInfo = AceType::MakeRefPtr<LazyWaterFlowLayoutInfo>();
    layoutInfo->SetTotalItemCount(4);
    // ResetLanes clears the item-size cache as part of its lane-topology rebuild contract; seed sizes after it
    // so the test exercises NotifyDataChange's rekey on a populated cache (matches production ordering).
    layoutInfo->ResetLanes(1, 150.0f);
    layoutInfo->CacheItemHeight(0, 40.0f);
    layoutInfo->CacheItemHeight(1, 50.0f);
    layoutInfo->CacheItemHeight(2, 60.0f);
    layoutInfo->CacheItemHeight(3, 70.0f);
    layoutInfo->lanes_[0].endPos = 220.0f;
    layoutInfo->lanes_[0].items_.push_back({ 3, 70.0f });
    layoutInfo->idxToLane_[3] = 0;

    layoutInfo->NotifyDataChange(1, -2);
    layoutInfo->UpdateLanesIndex();
    layoutInfo->SyncItemPositions(0.0f);

    EXPECT_EQ(layoutInfo->totalItemCount_, 2);
    ASSERT_TRUE(layoutInfo->GetCachedHeight(0).has_value());
    EXPECT_FLOAT_EQ(layoutInfo->GetCachedHeight(0).value(), 40.0f);
    ASSERT_TRUE(layoutInfo->GetCachedHeight(1).has_value());
    EXPECT_FLOAT_EQ(layoutInfo->GetCachedHeight(1).value(), 70.0f);
    auto shiftedPos = layoutInfo->GetPos(1);
    ASSERT_NE(shiftedPos, nullptr);
    EXPECT_FLOAT_EQ(shiftedPos->startPos, 150.0f);
    EXPECT_FALSE(layoutInfo->GetCachedHeight(2).has_value());
    EXPECT_FLOAT_EQ(layoutInfo->estimateItemSize_, 55.0f);
}

/**
 * @tc.name: FillFrontKeepsCachedContinuousIndexes_001
 * @tc.desc: Verify front recovery does not skip an item whose remembered lane is already cache-covered.
 * @tc.type: FUNC
 */
HWTEST_F(LazyVWaterFlowLayoutCoreTest, FillFrontKeepsCachedContinuousIndexes_001, TestSize.Level1)
{
    auto layoutInfo = AceType::MakeRefPtr<LazyWaterFlowLayoutInfo>();
    layoutInfo->SetTotalItemCount(102);
    layoutInfo->ResetLanes(2, 0.0f);
    layoutInfo->lanes_[0].startPos = 0.0f;
    layoutInfo->lanes_[0].endPos = 100.0f;
    layoutInfo->lanes_[0].items_.push_back({ 100, 100.0f });
    layoutInfo->lanes_[1].startPos = 50.0f;
    layoutInfo->lanes_[1].endPos = 150.0f;
    layoutInfo->lanes_[1].items_.push_back({ 101, 100.0f });
    layoutInfo->idxToLane_[98] = 1;
    layoutInfo->idxToLane_[99] = 0;
    layoutInfo->idxToLane_[100] = 0;
    layoutInfo->idxToLane_[101] = 1;
    layoutInfo->CacheItemHeight(98, 20.0f);
    layoutInfo->CacheItemHeight(99, 20.0f);

    LazyWaterFlowLayoutAlgorithm algorithm(layoutInfo);
    algorithm.totalItemCount_ = 102;
    algorithm.mainGap_ = 10.0f;
    float maxMainSize = 150.0f;
    algorithm.FillFront(nullptr, 25.0f, 99, 98, maxMainSize);

    ASSERT_FALSE(layoutInfo->lanes_[0].items_.empty());
    ASSERT_FALSE(layoutInfo->lanes_[1].items_.empty());
    EXPECT_EQ(layoutInfo->lanes_[0].items_.front().idx, 99);
    EXPECT_EQ(layoutInfo->lanes_[1].items_.front().idx, 98);
    EXPECT_EQ(layoutInfo->StartIndex(), 98);
}

/**
 * @tc.name: FillFrontTieBreakMatchesWaterFlowSW_001
 * @tc.desc: Verify reverse fill uses the same equal-start lane tie-break as WaterFlow sliding window.
 * @tc.type: FUNC
 */
HWTEST_F(LazyVWaterFlowLayoutCoreTest, FillFrontTieBreakMatchesWaterFlowSW_001, TestSize.Level1)
{
    auto layoutInfo = AceType::MakeRefPtr<LazyWaterFlowLayoutInfo>();
    layoutInfo->SetTotalItemCount(4);
    layoutInfo->ResetLanes(2, 0.0f);
    layoutInfo->lanes_[0].startPos = 100.0f;
    layoutInfo->lanes_[0].endPos = 200.0f;
    layoutInfo->lanes_[0].items_.push_back({ 2, 100.0f });
    layoutInfo->lanes_[1].startPos = 100.0f;
    layoutInfo->lanes_[1].endPos = 200.0f;
    layoutInfo->lanes_[1].items_.push_back({ 3, 100.0f });
    layoutInfo->idxToLane_[2] = 0;
    layoutInfo->idxToLane_[3] = 1;
    layoutInfo->CacheItemHeight(1, 20.0f);

    LazyWaterFlowLayoutAlgorithm algorithm(layoutInfo);
    algorithm.totalItemCount_ = 4;
    algorithm.mainGap_ = 10.0f;
    float maxMainSize = 200.0f;
    algorithm.FillFront(nullptr, 0.0f, 1, 1, maxMainSize);

    EXPECT_EQ(layoutInfo->lanes_[0].items_.front().idx, 2);
    EXPECT_EQ(layoutInfo->lanes_[1].items_.front().idx, 1);
    EXPECT_FLOAT_EQ(layoutInfo->lanes_[1].startPos, 70.0f);
}

/**
 * @tc.name: FillBackKeepsCachedContinuousIndexes_001
 * @tc.desc: Verify back recovery does not skip an item whose remembered lane is already cache-covered.
 * @tc.type: FUNC
 */
HWTEST_F(LazyVWaterFlowLayoutCoreTest, FillBackKeepsCachedContinuousIndexes_001, TestSize.Level1)
{
    auto layoutInfo = AceType::MakeRefPtr<LazyWaterFlowLayoutInfo>();
    layoutInfo->SetTotalItemCount(102);
    layoutInfo->ResetLanes(2, 0.0f);
    layoutInfo->lanes_[0].startPos = 100.0f;
    layoutInfo->lanes_[0].endPos = 200.0f;
    layoutInfo->lanes_[0].items_.push_back({ 99, 100.0f });
    layoutInfo->lanes_[1].startPos = 0.0f;
    layoutInfo->lanes_[1].endPos = 100.0f;
    layoutInfo->lanes_[1].items_.push_back({ 98, 100.0f });
    layoutInfo->idxToLane_[98] = 1;
    layoutInfo->idxToLane_[99] = 0;
    layoutInfo->idxToLane_[100] = 0;
    layoutInfo->idxToLane_[101] = 1;
    layoutInfo->CacheItemHeight(100, 20.0f);
    layoutInfo->CacheItemHeight(101, 20.0f);

    LazyWaterFlowLayoutAlgorithm algorithm(layoutInfo);
    algorithm.totalItemCount_ = 102;
    algorithm.mainGap_ = 10.0f;
    float maxMainSize = 200.0f;
    algorithm.FillBack(nullptr, 150.0f, 100, 101, maxMainSize);

    ASSERT_FALSE(layoutInfo->lanes_[0].items_.empty());
    ASSERT_FALSE(layoutInfo->lanes_[1].items_.empty());
    EXPECT_EQ(layoutInfo->lanes_[0].items_.back().idx, 100);
    EXPECT_EQ(layoutInfo->lanes_[1].items_.back().idx, 101);
    EXPECT_EQ(layoutInfo->EndIndex(), 101);
}

/**
 * @tc.name: ClearFrontBackAllowsEmptyLanes_001
 * @tc.desc: Verify clear operations can remove every cached item so far jumps rebuild from an empty window.
 * @tc.type: FUNC
 */
HWTEST_F(LazyVWaterFlowLayoutCoreTest, ClearFrontBackAllowsEmptyLanes_001, TestSize.Level1)
{
    auto layoutInfo = AceType::MakeRefPtr<LazyWaterFlowLayoutInfo>();
    layoutInfo->SetTotalItemCount(2);
    layoutInfo->ResetLanes(2, 0.0f);
    layoutInfo->lanes_[0].endPos = 100.0f;
    layoutInfo->lanes_[0].items_.push_back({ 0, 100.0f });
    layoutInfo->lanes_[1].endPos = 100.0f;
    layoutInfo->lanes_[1].items_.push_back({ 1, 100.0f });
    layoutInfo->idxToLane_[0] = 0;
    layoutInfo->idxToLane_[1] = 1;

    LazyWaterFlowLayoutAlgorithm algorithm(layoutInfo);
    algorithm.mainGap_ = 10.0f;
    algorithm.ClearFront(200.0f);

    EXPECT_TRUE(layoutInfo->lanes_[0].items_.empty());
    EXPECT_TRUE(layoutInfo->lanes_[1].items_.empty());
    EXPECT_EQ(layoutInfo->StartIndex(), -1);
    EXPECT_EQ(layoutInfo->EndIndex(), -1);

    layoutInfo->lanes_[0].startPos = 0.0f;
    layoutInfo->lanes_[0].endPos = 100.0f;
    layoutInfo->lanes_[0].items_.push_back({ 0, 100.0f });
    layoutInfo->lanes_[1].startPos = 0.0f;
    layoutInfo->lanes_[1].endPos = 100.0f;
    layoutInfo->lanes_[1].items_.push_back({ 1, 100.0f });
    layoutInfo->idxToLane_[0] = 0;
    layoutInfo->idxToLane_[1] = 1;
    algorithm.ClearBack(-1.0f);

    EXPECT_TRUE(layoutInfo->lanes_[0].items_.empty());
    EXPECT_TRUE(layoutInfo->lanes_[1].items_.empty());
    EXPECT_EQ(layoutInfo->StartIndex(), -1);
    EXPECT_EQ(layoutInfo->EndIndex(), -1);
}

/**
 * @tc.name: OffscreenAfterContentKeepsWindowEmpty_001
 * @tc.desc: Verify viewport past content end keeps the lane window empty instead of refilling tail items.
 * @tc.type: FUNC
 */
HWTEST_F(LazyVWaterFlowLayoutCoreTest, OffscreenAfterContentKeepsWindowEmpty_001, TestSize.Level1)
{
    auto layoutInfo = AceType::MakeRefPtr<LazyWaterFlowLayoutInfo>();
    layoutInfo->ResetLanes(2, 0.0f);
    layoutInfo->totalItemCount_ = 4;
    layoutInfo->lanes_[0].items_.push_back({ 0, 100.0f });
    layoutInfo->lanes_[0].items_.push_back({ 2, 100.0f });
    layoutInfo->lanes_[1].items_.push_back({ 1, 100.0f });
    layoutInfo->lanes_[1].items_.push_back({ 3, 100.0f });
    layoutInfo->idxToLane_ = { { 0, 0 }, { 1, 1 }, { 2, 0 }, { 3, 1 } };

    LazyWaterFlowLayoutAlgorithm algorithm(layoutInfo);
    algorithm.totalItemCount_ = 4;
    algorithm.totalMainSize_ = 210.0f;
    algorithm.mainGap_ = 10.0f;
    algorithm.viewStart_ = 500.0f;
    algorithm.viewEnd_ = 600.0f;
    algorithm.extendedViewStart_ = 500.0f;
    algorithm.extendedViewEnd_ = 600.0f;
    float maxMainSize = 0.0f;

    algorithm.RefillLaneWindow(nullptr, -1, 500.0f, 600.0f, maxMainSize);

    EXPECT_EQ(layoutInfo->StartIndex(), -1);
    EXPECT_EQ(layoutInfo->EndIndex(), -1);
    EXPECT_TRUE(layoutInfo->posMap_.empty());
    EXPECT_FLOAT_EQ(maxMainSize, 210.0f);
    EXPECT_FLOAT_EQ(algorithm.EstimateBodyHeight(maxMainSize), 210.0f);
}

/**
 * @tc.name: OffscreenBeforeContentKeepsWindowEmpty_001
 * @tc.desc: Verify viewport before content does not trigger the top-edge refill path.
 * @tc.type: FUNC
 */
HWTEST_F(LazyVWaterFlowLayoutCoreTest, OffscreenBeforeContentKeepsWindowEmpty_001, TestSize.Level1)
{
    auto layoutInfo = AceType::MakeRefPtr<LazyWaterFlowLayoutInfo>();
    layoutInfo->ResetLanes(2, 0.0f);
    layoutInfo->totalItemCount_ = 4;
    layoutInfo->lanes_[0].items_.push_back({ 0, 100.0f });
    layoutInfo->lanes_[0].items_.push_back({ 2, 100.0f });
    layoutInfo->lanes_[1].items_.push_back({ 1, 100.0f });
    layoutInfo->lanes_[1].items_.push_back({ 3, 100.0f });
    layoutInfo->idxToLane_ = { { 0, 0 }, { 1, 1 }, { 2, 0 }, { 3, 1 } };

    LazyWaterFlowLayoutAlgorithm algorithm(layoutInfo);
    algorithm.totalItemCount_ = 4;
    algorithm.totalMainSize_ = 210.0f;
    algorithm.mainGap_ = 10.0f;
    algorithm.viewStart_ = -500.0f;
    algorithm.viewEnd_ = -50.0f;
    algorithm.extendedViewStart_ = -500.0f;
    algorithm.extendedViewEnd_ = -50.0f;
    float maxMainSize = 0.0f;

    algorithm.RefillLaneWindow(nullptr, -1, -500.0f, -50.0f, maxMainSize);

    EXPECT_EQ(layoutInfo->StartIndex(), -1);
    EXPECT_EQ(layoutInfo->EndIndex(), -1);
    EXPECT_TRUE(layoutInfo->posMap_.empty());
    EXPECT_FLOAT_EQ(maxMainSize, 210.0f);
    EXPECT_FLOAT_EQ(algorithm.EstimateBodyHeight(maxMainSize), 210.0f);
}

/**
 * @tc.name: ClearFrontKeepsContinuousIndexes_001
 * @tc.desc: Verify front clear does not remove a later index while an earlier index is still retained.
 * @tc.type: FUNC
 */
HWTEST_F(LazyVWaterFlowLayoutCoreTest, ClearFrontKeepsContinuousIndexes_001, TestSize.Level1)
{
    auto layoutInfo = AceType::MakeRefPtr<LazyWaterFlowLayoutInfo>();
    layoutInfo->SetTotalItemCount(2);
    layoutInfo->ResetLanes(2, 0.0f);
    layoutInfo->lanes_[0].endPos = 250.0f;
    layoutInfo->lanes_[0].items_.push_back({ 0, 250.0f });
    layoutInfo->lanes_[1].endPos = 100.0f;
    layoutInfo->lanes_[1].items_.push_back({ 1, 100.0f });
    layoutInfo->idxToLane_[0] = 0;
    layoutInfo->idxToLane_[1] = 1;

    LazyWaterFlowLayoutAlgorithm algorithm(layoutInfo);
    algorithm.ClearFront(200.0f);

    ASSERT_EQ(layoutInfo->lanes_[1].items_.size(), 1u);
    EXPECT_EQ(layoutInfo->lanes_[1].items_.front().idx, 1);
    EXPECT_EQ(layoutInfo->StartIndex(), 0);
    EXPECT_EQ(layoutInfo->EndIndex(), 1);
}

/**
 * @tc.name: DataChangeZeroReconcilesLaneEndPos_001
 * @tc.desc: Verify count=0 invalidation cannot leave lane end positions without the main gap.
 * @tc.type: FUNC
 */
HWTEST_F(LazyVWaterFlowLayoutCoreTest, DataChangeZeroReconcilesLaneEndPos_001, TestSize.Level1)
{
    auto layoutInfo = AceType::MakeRefPtr<LazyWaterFlowLayoutInfo>();
    layoutInfo->SetTotalItemCount(3);
    layoutInfo->ResetLanes(1, 0.0f);
    layoutInfo->lanes_[0].endPos = 320.0f;
    layoutInfo->lanes_[0].items_.push_back({ 0, 100.0f });
    layoutInfo->lanes_[0].items_.push_back({ 1, 100.0f });
    layoutInfo->lanes_[0].items_.push_back({ 2, 100.0f });
    layoutInfo->idxToLane_[0] = 0;
    layoutInfo->idxToLane_[1] = 0;
    layoutInfo->idxToLane_[2] = 0;
    layoutInfo->CacheItemHeight(0, 100.0f);
    layoutInfo->CacheItemHeight(1, 100.0f);
    layoutInfo->CacheItemHeight(2, 100.0f);
    layoutInfo->SetPosMap(0, { .laneIdx = 0, .startPos = 0.0f, .endPos = 100.0f });

    layoutInfo->NotifyDataChange(2, 0);
    EXPECT_EQ(layoutInfo->GetPos(0), nullptr);

    LazyWaterFlowLayoutAlgorithm algorithm(layoutInfo);
    algorithm.mainGap_ = 10.0f;
    algorithm.SyncLaneGeometry();
    EXPECT_FLOAT_EQ(layoutInfo->lanes_[0].endPos, 210.0f);
}

/**
 * @tc.name: ItemStartOffsetShiftsSuffixOnly_001
 * @tc.desc: Verify item-level start offsets keep the lane prefix stable and move the measured item suffix.
 * @tc.type: FUNC
 */
HWTEST_F(LazyVWaterFlowLayoutCoreTest, ItemStartOffsetShiftsSuffixOnly_001, TestSize.Level1)
{
    auto layoutInfo = AceType::MakeRefPtr<LazyWaterFlowLayoutInfo>();
    layoutInfo->SetTotalItemCount(3);
    layoutInfo->ResetLanes(1, 0.0f);
    layoutInfo->lanes_[0].items_.push_back({ 0, 100.0f });
    layoutInfo->lanes_[0].items_.push_back({ 1, 120.0f, -20.0f });
    layoutInfo->lanes_[0].items_.push_back({ 2, 100.0f });
    layoutInfo->SyncItemPositions(10.0f);

    auto firstPos = layoutInfo->GetPos(0);
    auto adjustedPos = layoutInfo->GetPos(1);
    auto suffixPos = layoutInfo->GetPos(2);
    ASSERT_NE(firstPos, nullptr);
    ASSERT_NE(adjustedPos, nullptr);
    ASSERT_NE(suffixPos, nullptr);
    EXPECT_FLOAT_EQ(firstPos->startPos, 0.0f);
    EXPECT_FLOAT_EQ(firstPos->endPos, 100.0f);
    EXPECT_FLOAT_EQ(adjustedPos->startPos, 90.0f);
    EXPECT_FLOAT_EQ(adjustedPos->endPos, 210.0f);
    EXPECT_FLOAT_EQ(suffixPos->startPos, 220.0f);
}

/**
 * @tc.name: LaneTemplateChangeClearsPendingAnchor_001
 * @tc.desc: Verify lane topology changes invalidate pending keep-position anchors.
 * @tc.type: FUNC
 */
HWTEST_F(LazyVWaterFlowLayoutCoreTest, LaneTemplateChangeClearsPendingAnchor_001, TestSize.Level1)
{
    auto layoutInfo = AceType::MakeRefPtr<LazyWaterFlowLayoutInfo>();
    layoutInfo->SetTotalItemCount(2);
    layoutInfo->startIndex_ = 0;
    layoutInfo->endIndex_ = 1;
    layoutInfo->SetPosMap(0, { .laneIdx = 0, .startPos = 0.0f, .endPos = 100.0f });
    layoutInfo->SetPosMap(1, { .laneIdx = 0, .startPos = 100.0f, .endPos = 200.0f });

    layoutInfo->NotifyDataChange(0, 1);
    ASSERT_TRUE(layoutInfo->hasPendingAdjustAnchor_);
    // UpdateLaneCrossLens only signals "lane topology needs a rebuild" now; the actual cleanup
    // (boundary flags, item-size cache, pending anchor, totalOffset_/maxHeight_) lives in ResetLanes.
    // Production callers always pair the two; this test mirrors that contract.
    const std::vector<double> newLens { 100.0, 100.0 };
    ASSERT_TRUE(layoutInfo->UpdateLaneCrossLens(newLens));
    layoutInfo->ResetLanes(static_cast<int32_t>(newLens.size()), 0.0f);
    EXPECT_FALSE(layoutInfo->hasPendingAdjustAnchor_);
}

/**
 * @tc.name: TopDataChangeKeepsAnchor_001
 * @tc.desc: Verify structural changes at the top keep the old first item stable through adjust offset.
 * @tc.type: FUNC
 */
HWTEST_F(LazyVWaterFlowLayoutCoreTest, TopDataChangeKeepsAnchor_001, TestSize.Level1)
{
    auto layoutInfo = AceType::MakeRefPtr<LazyWaterFlowLayoutInfo>();
    layoutInfo->SetTotalItemCount(3);
    LazyWaterFlowItemMainPos oldStartPos { .laneIdx = 0, .startPos = 0.0f, .endPos = 100.0f };
    layoutInfo->SetPosMap(0, oldStartPos);
    layoutInfo->NotifyDataChange(0, 1);
    layoutInfo->SetPosMap(0, { .laneIdx = 0, .startPos = 0.0f, .endPos = 80.0f });
    layoutInfo->SetPosMap(1, { .laneIdx = 0, .startPos = 80.0f, .endPos = 180.0f });

    LazyWaterFlowLayoutAlgorithm algorithm(layoutInfo);
    LazyWaterFlowLayoutAlgorithm::PrevFrameSnapshot prevFrameSnapshot;
    prevFrameSnapshot.anchor.startIndex = 1;
    prevFrameSnapshot.anchor.startPos = oldStartPos;

    algorithm.viewStart_ = 0.0f;
    algorithm.UpdateAdjustOffset(prevFrameSnapshot);
    EXPECT_FLOAT_EQ(layoutInfo->adjustOffset_.start, 80.0f);

    algorithm.viewStart_ = 120.0f;
    algorithm.UpdateAdjustOffset(prevFrameSnapshot);
    EXPECT_FLOAT_EQ(layoutInfo->adjustOffset_.start, 80.0f);
}

/**
 * @tc.name: TopDataChangeUsesAnchorLaneDelta_001
 * @tc.desc: Verify insertions before the viewport take the anchor's own lane delta when the anchor itself can be
 *           located in the new layout. Earlier this case was expected to take the largest visible lane delta, but
 *           that path clipped the anchor behind sticky edges in waterflow with varying-height new items: a sibling
 *           lane sees a larger delta because its inserted items are taller, and applying that delta to the parent
 *           shifts the anchor's lane up by the height difference. The anchor-based delta keeps the anchor's visual
 *           position stable, leaving any residual totalDelta to flow into adjustOffset.end.
 * @tc.type: FUNC
 */
HWTEST_F(LazyVWaterFlowLayoutCoreTest, TopDataChangeUsesAnchorLaneDelta_001, TestSize.Level1)
{
    auto layoutInfo = AceType::MakeRefPtr<LazyWaterFlowLayoutInfo>();
    layoutInfo->SetTotalItemCount(8);
    layoutInfo->hasDataChange_ = true;
    layoutInfo->pendingVisiblePositions_[4] = { .laneIdx = 0, .startPos = 200.0f, .endPos = 300.0f };
    layoutInfo->pendingVisiblePositions_[5] = { .laneIdx = 1, .startPos = 200.0f, .endPos = 300.0f };
    layoutInfo->SetPosMap(4, { .laneIdx = 0, .startPos = 280.0f, .endPos = 380.0f });
    layoutInfo->SetPosMap(5, { .laneIdx = 1, .startPos = 300.0f, .endPos = 400.0f });

    LazyWaterFlowLayoutAlgorithm algorithm(layoutInfo);
    algorithm.totalMainSize_ = 600.0f;
    LazyWaterFlowLayoutAlgorithm::PrevFrameSnapshot prevFrameSnapshot;
    prevFrameSnapshot.anchor.startIndex = 4;
    prevFrameSnapshot.anchor.startPos = LazyWaterFlowItemMainPos { .laneIdx = 0, .startPos = 200.0f, .endPos = 300.0f };
    prevFrameSnapshot.anchor.totalMainSize = 500.0f;

    algorithm.UpdateAdjustOffset(prevFrameSnapshot);

    // Anchor (idx=4, lane=0) moved 280-200=80; the residual totalDelta (600-500-80=20) flows into adjustOffset.end.
    EXPECT_FLOAT_EQ(layoutInfo->adjustOffset_.start, 80.0f);
    EXPECT_FLOAT_EQ(layoutInfo->adjustOffset_.end, 20.0f);
}

/**
 * @tc.name: PredictBuild_001
 * @tc.desc: Verify LazyVWaterFlowLayout synchronously fills the half-screen cache during Measure
 *           (no idle predict pass needed for the standard scroll case).
 * @tc.type: FUNC
 */
HWTEST_F(LazyVWaterFlowLayoutCoreTest, PredictBuild_001, TestSize.Level1)
{
    CreateScroll();
    CreateLazyWaterFlowLayout();
    LazyVWaterFlowLayoutModel::SetColumnsTemplate("1fr 1fr");
    CreateContent(30);
    CreateDone();

    ASSERT_NE(pattern_, nullptr);
    EXPECT_EQ(pattern_->layoutInfo_->startIndex_, 0);
    EXPECT_EQ(pattern_->layoutInfo_->endIndex_, 9);
    EXPECT_EQ(pattern_->layoutInfo_->layoutedStartIndex_, 0);
    EXPECT_EQ(pattern_->layoutInfo_->layoutedEndIndex_, 9);
    EXPECT_EQ(pattern_->layoutInfo_->cachedStartIndex_, 0);
    // Cache extends past the visible end by half a viewport thanks to Option A in ResolveBackBoundary.
    EXPECT_EQ(pattern_->layoutInfo_->cachedEndIndex_, 13);
    EXPECT_EQ(pattern_->layoutInfo_->totalMainSize_, 1500.0f);
    EXPECT_FALSE(pattern_->layoutInfo_->NeedPredict());
}

/**
 * @tc.name: ColumnsTemplateChangeDeactivatesOldVisibleItems_001
 * @tc.desc: Verify direct children visible in the old lane topology are deactivated when they leave the new viewport.
 * @tc.type: FUNC
 */
HWTEST_F(LazyVWaterFlowLayoutCoreTest, ColumnsTemplateChangeDeactivatesOldVisibleItems_001, TestSize.Level1)
{
    CreateScroll();
    CreateLazyWaterFlowLayout();
    LazyVWaterFlowLayoutModel::SetColumnsTemplate("1fr 1fr 1fr");
    CreateContent(30);
    CreateDone();

    ASSERT_NE(pattern_, nullptr);
    ASSERT_EQ(pattern_->layoutInfo_->layoutedStartIndex_, 0);
    ASSERT_EQ(pattern_->layoutInfo_->layoutedEndIndex_, 14);
    auto oldVisibleChild = GetChildFrameNode(frameNode_, 14);
    ASSERT_NE(oldVisibleChild, nullptr);
    EXPECT_TRUE(oldVisibleChild->IsActive());
    auto oldVisibleCachedChild = GetChildFrameNode(frameNode_, 12);
    ASSERT_NE(oldVisibleCachedChild, nullptr);
    EXPECT_TRUE(oldVisibleCachedChild->IsActive());

    LazyVWaterFlowLayoutModel::SetColumnsTemplate(AceType::RawPtr(frameNode_), "1fr 1fr");
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    FlushUITasks();

    EXPECT_EQ(pattern_->layoutInfo_->layoutedStartIndex_, 0);
    EXPECT_EQ(pattern_->layoutInfo_->layoutedEndIndex_, 9);
    auto oldVisibleCachedPos = pattern_->layoutInfo_->GetPos(12);
    const bool oldVisibleCachedItemOutOfViewport =
        oldVisibleCachedPos == nullptr || GreatOrEqual(oldVisibleCachedPos->startPos, LAZY_WATER_FLOW_SCROLL_HEIGHT);
    EXPECT_TRUE(oldVisibleCachedItemOutOfViewport);
    auto oldVisiblePos = pattern_->layoutInfo_->GetPos(14);
    EXPECT_TRUE(oldVisiblePos == nullptr || GreatOrEqual(oldVisiblePos->startPos, pattern_->layoutInfo_->cacheEndPos_));
    // Item 12 falls inside the new layout's cache range (visible 0-9 + half-screen back = up to ~13),
    // so it stays alive as a cache child. Item 14 lies past the cache window and is deactivated.
    EXPECT_TRUE(oldVisibleCachedChild->IsActive());
    EXPECT_FALSE(oldVisibleChild->IsActive());
}

/**
 * @tc.name: ArkoalaChildKeepsVisibleAndCacheRangesSeparated_001
 * @tc.desc: Verify static lazy children receive visible range separately from the cache expansion.
 * @tc.type: FUNC
 */
HWTEST_F(LazyVWaterFlowLayoutCoreTest, ArkoalaChildKeepsVisibleAndCacheRangesSeparated_001, TestSize.Level1)
{
    auto host = FrameNode::CreateFrameNode(
        V2::LAZY_V_WATERFLOW_LAYOUT_ETS_TAG, GetElmtId(), AceType::MakeRefPtr<LazyWaterFlowLayoutPattern>());
    auto arkoalaLazyNode = AceType::MakeRefPtr<ArkoalaLazyNode>(GetElmtId());
    arkoalaLazyNode->SetTotalCount(500);
    host->AddChild(arkoalaLazyNode);

    auto layoutInfo = AceType::MakeRefPtr<LazyWaterFlowLayoutInfo>();
    auto algorithm = AceType::MakeRefPtr<LazyWaterFlowLayoutAlgorithm>(layoutInfo);
    algorithm->UpdateBusinessActiveRangeOnChildren(host, 1, 10, 1, 3);

    const ActiveRangeParam expectedRange = { 1, 10, 1, 3 };
    EXPECT_EQ(arkoalaLazyNode->activeRangeParam_, expectedRange);
}

/**
 * @tc.name: ArkoalaChildReceivesOneRangeUpdate_001
 * @tc.desc: Verify static lazy children are not first reactivated by the raw cache range.
 * @tc.type: FUNC
 */
HWTEST_F(LazyVWaterFlowLayoutCoreTest, ArkoalaChildReceivesOneRangeUpdate_001, TestSize.Level1)
{
    auto host = FrameNode::CreateFrameNode(
        V2::LAZY_V_WATERFLOW_LAYOUT_ETS_TAG, GetElmtId(), AceType::MakeRefPtr<LazyWaterFlowLayoutPattern>());
    auto arkoalaLazyNode = AceType::MakeRefPtr<ArkoalaLazyNode>(GetElmtId());
    arkoalaLazyNode->SetTotalCount(12);
    int32_t updateRangeCount = 0;
    arkoalaLazyNode->SetCallbacks(nullptr,
        [&updateRangeCount](int32_t, int32_t, int32_t, int32_t, bool) { ++updateRangeCount; });
    host->AddChild(arkoalaLazyNode);

    auto layoutInfo = AceType::MakeRefPtr<LazyWaterFlowLayoutInfo>();
    auto algorithm = AceType::MakeRefPtr<LazyWaterFlowLayoutAlgorithm>(layoutInfo);
    algorithm->UpdateActiveChildRange(AceType::RawPtr(host), 6, 11, 2, 11);

    EXPECT_EQ(updateRangeCount, 1);
    const ActiveRangeParam expectedRange = { 6, 11, 4, 0 };
    EXPECT_EQ(arkoalaLazyNode->activeRangeParam_, expectedRange);
}

/**
 * @tc.name: PredictDeadlineMissContinues_001
 * @tc.desc: Verify predict re-posts on missed deadline and finishes when a usable deadline arrives.
 * @tc.type: FUNC
 */
HWTEST_F(LazyVWaterFlowLayoutCoreTest, PredictDeadlineMissContinues_001, TestSize.Level1)
{
    CreateScroll();
    CreateLazyWaterFlowLayout();
    LazyVWaterFlowLayoutModel::SetColumnsTemplate("1fr 1fr");
    CreateContent(30);
    CreateDone();

    ASSERT_NE(pattern_, nullptr);
    // Option A fills the cache synchronously, so force a forward gap to exercise the predict path.
    pattern_->layoutInfo_->cacheEndPos_ += LAZY_WATER_FLOW_SCROLL_HEIGHT;
    ASSERT_TRUE(pattern_->layoutInfo_->NeedPredict());

    pattern_->ProcessIdleTask(0); // missed deadline; re-post path runs, NeedPredict stays true
    EXPECT_TRUE(pattern_->layoutInfo_->NeedPredict());
}

/**
 * @tc.name: ParentPredictDeadlineMarksPredictPass_001
 * @tc.desc: Verify a parent-provided predict deadline is consumed like LazyColumnLayout.
 * @tc.type: FUNC
 */
HWTEST_F(LazyVWaterFlowLayoutCoreTest, ParentPredictDeadlineMarksPredictPass_001, TestSize.Level1)
{
    CreateScroll();
    CreateLazyWaterFlowLayout();
    CreateContent(4);
    CreateDone();

    auto layoutWrapper = frameNode_->CreateLayoutWrapper(true, true);
    ASSERT_NE(layoutWrapper, nullptr);
    constexpr int64_t deadline = 12345;
    std::optional<ViewPosReference> reference = ViewPosReference {
        .viewPosStart = 0.0f,
        .viewPosEnd = LAZY_WATER_FLOW_SCROLL_HEIGHT,
        .referencePos = 0.0f,
        .referenceEdge = ReferenceEdge::START,
        .axis = Axis::VERTICAL,
        .deadline = deadline,
    };

    LazyWaterFlowLayoutAlgorithm algorithm(pattern_->layoutInfo_);
    algorithm.UpdateReferencePos(AceType::RawPtr(layoutWrapper), reference);

    ASSERT_TRUE(pattern_->layoutInfo_->deadline_.has_value());
    EXPECT_EQ(pattern_->layoutInfo_->deadline_.value(), deadline);
}

/**
 * @tc.name: InactiveNodeSkipsIdlePredict_001
 * @tc.desc: Verify an inactive LazyVWaterFlowLayout clears the queued deadline and skips predict.
 * @tc.type: FUNC
 */
HWTEST_F(LazyVWaterFlowLayoutCoreTest, InactiveNodeSkipsIdlePredict_001, TestSize.Level1)
{
    CreateScroll();
    CreateLazyWaterFlowLayout();
    LazyVWaterFlowLayoutModel::SetColumnsTemplate("1fr 1fr");
    CreateContent(30);
    CreateDone();

    ASSERT_NE(pattern_, nullptr);
    // Force NeedPredict() so ProcessIdleTask would normally proceed; the host->IsActive() guard must
    // short-circuit before the work runs and must clear the queued deadline.
    pattern_->layoutInfo_->cacheEndPos_ += LAZY_WATER_FLOW_SCROLL_HEIGHT;
    ASSERT_TRUE(pattern_->layoutInfo_->NeedPredict());
    frameNode_->SetActive(false);
    pattern_->layoutInfo_->deadline_ = GetSysTimestamp();

    pattern_->ProcessIdleTask(GetSysTimestamp() + FRAME_INTERVAL_MS * NANOSECONDS_PER_MILLISECOND);

    EXPECT_FALSE(pattern_->layoutInfo_->deadline_.has_value());
}

/**
 * @tc.name: ListScrollToEdgeBottomThenTop_001
 * @tc.desc: Verify top-edge snapping after a bottom jump does not feed an internal lane correction back to List.
 * @tc.type: FUNC
 */
HWTEST_F(LazyVWaterFlowLayoutCoreTest, ListScrollToEdgeBottomThenTop_001, TestSize.Level1)
{
    CreateList();
    CreateLazyWaterFlowLayout();
    LazyVWaterFlowLayoutModel::SetColumnsTemplate("1fr");
    std::vector<float> heights(50, 80.0f);
    std::fill(heights.begin(), heights.begin() + 25, 120.0f);
    CreateContent(heights);
    CreateDone();

    ASSERT_NE(pattern_, nullptr);
    ASSERT_NE(scrollablePattern_, nullptr);
    EXPECT_EQ(pattern_->layoutInfo_->startIndex_, 0);
    EXPECT_LT(pattern_->layoutInfo_->endIndex_, 49);

    scrollablePattern_->ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, false);
    FlushUITasks();

    EXPECT_GE(pattern_->layoutInfo_->startIndex_, 0);
    EXPECT_EQ(pattern_->layoutInfo_->endIndex_, 49);
    EXPECT_FALSE(pattern_->layoutInfo_->posMap_.empty());
    EXPECT_NE(pattern_->layoutInfo_->posMap_.find(pattern_->layoutInfo_->startIndex_),
        pattern_->layoutInfo_->posMap_.end());
    EXPECT_NE(pattern_->layoutInfo_->posMap_.find(pattern_->layoutInfo_->endIndex_),
        pattern_->layoutInfo_->posMap_.end());
    EXPECT_GT(static_cast<float>(scrollablePattern_->GetTotalOffset()), 0.0f);

    scrollablePattern_->ScrollToEdge(ScrollEdgeType::SCROLL_TOP, false);
    FlushUITasks();

    EXPECT_NEAR(static_cast<float>(scrollablePattern_->GetTotalOffset()), 0.0f, 0.01f);
    EXPECT_EQ(pattern_->layoutInfo_->startIndex_, 0);
    auto firstPos = pattern_->layoutInfo_->GetPos(0);
    ASSERT_NE(firstPos, nullptr);
    EXPECT_NEAR(firstPos->startPos, 0.0f, 0.01f);
}

/**
 * @tc.name: ListOffscreenAfterContentReportsEmptyRange_001
 * @tc.desc: Verify a List child LazyVWaterFlowLayout reports an empty range when it is fully above viewport.
 * @tc.type: FUNC
 */
HWTEST_F(LazyVWaterFlowLayoutCoreTest, ListOffscreenAfterContentReportsEmptyRange_001, TestSize.Level1)
{
    CreateList();
    CreateLazyWaterFlowLayout();
    LazyVWaterFlowLayoutModel::SetColumnsTemplate("1fr 1fr");
    int32_t callCount = 0;
    VisibleRange visibleRange = { -2, -2 };
    RegisterVisibleRangeObserver(frameNode_, callCount, visibleRange);
    CreateContent(12);
    ViewStackProcessor::GetInstance()->Pop();
    CreateListFooter(900.0f);
    CreateDone();

    ASSERT_NE(pattern_, nullptr);
    ASSERT_NE(scrollablePattern_, nullptr);
    ASSERT_GT(callCount, 0);
    EXPECT_GE(pattern_->layoutInfo_->startIndex_, 0);

    scrollablePattern_->ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, false);
    FlushUITasks();

    EXPECT_GT(static_cast<float>(scrollablePattern_->GetTotalOffset()), pattern_->layoutInfo_->totalMainSize_);
    ExpectVisibleRange(visibleRange, -1, -1);
}

/**
 * @tc.name: ScrollBottomThenTopOvershoot_001
 * @tc.desc: Regression for FillFront overshoot after bottom jump. With small front items and tall tail
 *           items, the average-based estimate over-counts the prefix during the bottom jump's FillFront
 *           pass; a subsequent ScrollToEdge(SCROLL_TOP) used to stop at AreFrontLanesCovered before
 *           reaching item 0, leaving lane.startPos negative and item 0 absent from the lane window.
 *           After the fillToTop short-circuit, item 0 must enter the lane and sit at content origin.
 * @tc.type: FUNC
 */
HWTEST_F(LazyVWaterFlowLayoutCoreTest, ScrollBottomThenTopOvershoot_001, TestSize.Level1)
{
    CreateScroll();
    CreateLazyWaterFlowLayout();
    LazyVWaterFlowLayoutModel::SetColumnsTemplate("1fr");
    // Front 25 items short (60), tail 25 tall (200). Initial measure samples only the short prefix,
    // so the avg estimate is biased low; the bottom jump's FillFront overshoots when prepending tall
    // tail items, leaving lane.startPos drifted past 0 when the user scrolls back to top.
    std::vector<float> heights(50, 200.0f);
    std::fill(heights.begin(), heights.begin() + 25, 60.0f);
    CreateContent(heights);
    CreateDone();

    ASSERT_NE(pattern_, nullptr);
    ASSERT_NE(scrollablePattern_, nullptr);

    scrollablePattern_->ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, false);
    FlushUITasks();
    EXPECT_GT(static_cast<float>(scrollablePattern_->GetTotalOffset()), 0.0f);

    scrollablePattern_->ScrollToEdge(ScrollEdgeType::SCROLL_TOP, false);
    FlushUITasks();

    EXPECT_NEAR(static_cast<float>(scrollablePattern_->GetTotalOffset()), 0.0f, 0.01f);
    EXPECT_EQ(pattern_->layoutInfo_->startIndex_, 0);
    auto firstPos = pattern_->layoutInfo_->GetPos(0);
    ASSERT_NE(firstPos, nullptr);
    EXPECT_NEAR(firstPos->startPos, 0.0f, 0.01f);
    // Confirm item 0 actually entered the lane window (the bug-state had laneStartIdx > 0 with
    // negative content positions for items above the lane front).
    ASSERT_FALSE(pattern_->layoutInfo_->lanes_.empty());
    EXPECT_EQ(pattern_->layoutInfo_->lanes_[0].items_.empty() ? -1 :
              pattern_->layoutInfo_->lanes_[0].items_.front().idx, 0);
}

/**
 * @tc.name: FlowItemVisibleRange_001
 * @tc.desc: Verify LazyVWaterFlowLayout works under WaterFlow-FlowItem.
 * @tc.type: FUNC
 */
HWTEST_F(LazyVWaterFlowLayoutCoreTest, FlowItemVisibleRange_001, TestSize.Level1)
{
    WaterFlowModelNG model;
    model.Create();
    ViewAbstract::SetHeight(CalcLength(LAZY_WATER_FLOW_SCROLL_HEIGHT));
    ViewAbstract::SetWidth(CalcLength(LAZY_WATER_FLOW_SCROLL_WIDTH));
    model.SetColumnsTemplate("1fr");
    scrollableFrameNode_ = GetMainFrameNode();
    scrollablePattern_ = scrollableFrameNode_->GetPattern<ScrollablePattern>();

    int32_t callCount = 0;
    std::pair<int32_t, int32_t> visibleRange = { -1, -1 };
    CreateFlowItem(160.0f);
    CreateLazyWaterFlowLayout();
    LazyVWaterFlowLayoutModel::SetColumnsTemplate("1fr 1fr");
    LazyWaterFlowLayoutModel::SetOnVisibleIndexesChange([&callCount, &visibleRange](int32_t start, int32_t end) {
        ++callCount;
        visibleRange = { start, end };
    });
    CreateContent(std::vector<float>(6, 50.0f));
    ViewStackProcessor::GetInstance()->Pop();
    ViewStackProcessor::GetInstance()->Pop();

    CreateDone();

    ASSERT_NE(frameNode_, nullptr);
    EXPECT_EQ(frameNode_->GetParent()->GetTag(), V2::FLOW_ITEM_ETS_TAG);
    EXPECT_GT(callCount, 0);
    EXPECT_EQ(visibleRange.first, 0);
    EXPECT_EQ(visibleRange.second, 5);
}

/**
 * @tc.name: DirectWaterFlowMultiLaneBoundedFallback_001
 * @tc.desc: Verify direct multi-lane WaterFlow keeps a bounded fallback when no view reference is provided.
 * @tc.type: FUNC
 */
HWTEST_F(LazyVWaterFlowLayoutCoreTest, DirectWaterFlowMultiLaneBoundedFallback_001, TestSize.Level1)
{
    WaterFlowModelNG model;
    model.Create();
    ViewAbstract::SetHeight(CalcLength(LAZY_WATER_FLOW_SCROLL_HEIGHT));
    ViewAbstract::SetWidth(CalcLength(LAZY_WATER_FLOW_SCROLL_WIDTH));
    model.SetColumnsTemplate("1fr 1fr");
    scrollableFrameNode_ = GetMainFrameNode();
    scrollablePattern_ = scrollableFrameNode_->GetPattern<ScrollablePattern>();

    CreateLazyWaterFlowLayout();
    LazyVWaterFlowLayoutModel::SetColumnsTemplate("1fr 1fr");
    CreateContent(30);
    CreateDone();

    ASSERT_NE(frameNode_, nullptr);
    ASSERT_NE(pattern_, nullptr);
    EXPECT_EQ(frameNode_->GetParent()->GetTag(), V2::WATERFLOW_ETS_TAG);
    EXPECT_LT(pattern_->layoutInfo_->posMap_.size(), 30u);
    EXPECT_EQ(pattern_->layoutInfo_->layoutedStartIndex_, 0);
    EXPECT_LT(pattern_->layoutInfo_->layoutedEndIndex_, 29);
}

/**
 * @tc.name: DirectWaterFlowWeightedColumnFallback_001
 * @tc.desc: Verify direct WaterFlow fallback remains safe when child content uses layoutWeight.
 * @tc.type: FUNC
 */
HWTEST_F(LazyVWaterFlowLayoutCoreTest, DirectWaterFlowWeightedColumnFallback_001, TestSize.Level1)
{
    WaterFlowModelNG model;
    model.Create();
    ViewAbstract::SetHeight(CalcLength(LAZY_WATER_FLOW_SCROLL_HEIGHT));
    ViewAbstract::SetWidth(CalcLength(LAZY_WATER_FLOW_SCROLL_WIDTH));
    model.SetColumnsTemplate("1fr 1fr");
    scrollableFrameNode_ = GetMainFrameNode();
    scrollablePattern_ = scrollableFrameNode_->GetPattern<ScrollablePattern>();

    CreateLazyWaterFlowLayout();
    LazyVWaterFlowLayoutModel::SetColumnsTemplate("1fr 1fr");
    constexpr int32_t itemCount = 30;
    for (int32_t i = 0; i < itemCount; ++i) {
        CreateColumn([](ColumnModelNG) {
            ViewAbstract::SetWidth(CalcLength(1.0f, DimensionUnit::PERCENT));
            ViewAbstract::SetHeight(CalcLength(LAZY_WATER_FLOW_ITEM_HEIGHT));

            StackModelNG stackModel;
            stackModel.Create();
            ViewAbstract::SetWidth(CalcLength(1.0f, DimensionUnit::PERCENT));
            ViewAbstract::SetHeight(CalcLength(20.0f));
            ViewStackProcessor::GetInstance()->Pop();
            stackModel.Create();
            ViewAbstract::SetWidth(CalcLength(1.0f, DimensionUnit::PERCENT));
            ViewAbstract::SetLayoutWeight(1.0f);
            ViewStackProcessor::GetInstance()->Pop();
        });
    }
    CreateDone();

    ASSERT_NE(frameNode_, nullptr);
    ASSERT_NE(pattern_, nullptr);
    EXPECT_EQ(frameNode_->GetParent()->GetTag(), V2::WATERFLOW_ETS_TAG);
    EXPECT_LT(pattern_->layoutInfo_->posMap_.size(), static_cast<size_t>(itemCount));
    EXPECT_EQ(pattern_->layoutInfo_->layoutedStartIndex_, 0);
    EXPECT_LT(pattern_->layoutInfo_->layoutedEndIndex_, itemCount - 1);

    auto firstColumn = AceType::DynamicCast<FrameNode>(frameNode_->GetChildAtIndex(0));
    ASSERT_NE(firstColumn, nullptr);
    auto weightedStack = AceType::DynamicCast<FrameNode>(firstColumn->GetChildAtIndex(1));
    ASSERT_NE(weightedStack, nullptr);
    const auto columnHeight = firstColumn->GetGeometryNode()->GetFrameSize().Height();
    const auto weightedHeight = weightedStack->GetGeometryNode()->GetFrameSize().Height();
    EXPECT_TRUE(std::isfinite(columnHeight));
    EXPECT_TRUE(std::isfinite(weightedHeight));
    EXPECT_GT(weightedHeight, 0.0f);
    EXPECT_LE(columnHeight, LAZY_WATER_FLOW_ITEM_HEIGHT);
    EXPECT_LE(weightedHeight, LAZY_WATER_FLOW_ITEM_HEIGHT);
}

/**
 * @tc.name: CommonViewWrapper_001
 * @tc.desc: Verify LazyVWaterFlowLayout works when wrapped by a custom component host.
 * @tc.type: FUNC
 */
HWTEST_F(LazyVWaterFlowLayoutCoreTest, CommonViewWrapper_001, TestSize.Level1)
{
    CreateScroll();
    CommonViewModelNG commonViewModel;
    commonViewModel.Create(false);
    auto commonViewNode = GetMainFrameNode();
    CreateLazyWaterFlowLayout();

    int32_t callCount = 0;
    std::pair<int32_t, int32_t> visibleRange = { -1, -1 };
    LazyWaterFlowLayoutModel::SetOnVisibleIndexesChange([&callCount, &visibleRange](int32_t start, int32_t end) {
        ++callCount;
        visibleRange = { start, end };
    });
    CreateContent(4);
    CreateDone();

    ASSERT_NE(frameNode_, nullptr);
    ASSERT_NE(commonViewNode, nullptr);
    EXPECT_EQ(frameNode_->GetParent()->GetTag(), V2::COMMON_VIEW_ETS_TAG);
    EXPECT_TRUE(commonViewNode->GetLayoutProperty()->GetNeedLazyLayout());
    EXPECT_GT(callCount, 0);
    EXPECT_EQ(visibleRange.first, 0);
    EXPECT_EQ(visibleRange.second, 3);
}

/**
 * @tc.name: NodeContainerWrapper_001
 * @tc.desc: Verify LazyVWaterFlowLayout accepts NodeContainer as an intermediate wrapper.
 * @tc.type: FUNC
 */
HWTEST_F(LazyVWaterFlowLayoutCoreTest, NodeContainerWrapper_001, TestSize.Level1)
{
    auto scrollNode = FrameNode::CreateFrameNode(
        V2::SCROLL_ETS_TAG, GetElmtId(), AceType::MakeRefPtr<ScrollPattern>());
    auto nodeContainerNode = NodeContainerModelNG::CreateFrameNode(GetElmtId());
    auto lazyNode = LazyWaterFlowLayoutModelStatic::CreateFrameNode(GetElmtId());
    lazyNode->SetIsArkTsFrameNode(true);
    auto nodeContainerPattern = nodeContainerNode->GetPattern<NodeContainerPattern>();
    ASSERT_NE(nodeContainerPattern, nullptr);
    nodeContainerPattern->SetMakeFunction([lazyNode]() -> RefPtr<UINode> { return lazyNode; });

    scrollNode->AddChild(nodeContainerNode);
    nodeContainerPattern->RemakeNode();
    MountToStageNode(scrollNode);

    auto lazyPattern = lazyNode->GetPattern<LazyWaterFlowLayoutPattern>();
    ASSERT_NE(lazyPattern, nullptr);
    lazyPattern->OnAttachToMainTree();

    EXPECT_TRUE(lazyNode->GetLayoutProperty()->GetNeedLazyLayout());
    EXPECT_TRUE(nodeContainerNode->GetLayoutProperty()->GetNeedLazyLayout());
    EXPECT_EQ(lazyNode->GetParent()->GetTag(), V2::NODE_CONTAINER_ETS_TAG);
}
} // namespace OHOS::Ace::NG
