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

#include "test/mock/frameworks/core/animation/mock_animation_manager.h"
#include "water_flow_test_ng.h"

#include "core/animation/scroll_motion.h"

#define private public
#define protected public
#include "core/components_ng/pattern/scroll/scroll_edge_effect.h"
#include "core/components_ng/pattern/waterflow/layout/sliding_window/water_flow_layout_sw.h"
#undef protected
#undef private

#include "core/components_ng/pattern/lazy_column_layout/lazy_column_layout_model.h"
#include "core/components_ng/pattern/scrollable/scrollable_model_ng.h"
#include "core/components_ng/pattern/waterflow/layout/sliding_window/water_flow_layout_info_sw.h"
#include "core/components_ng/syntax/lazy_for_each_node.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t RELOADED_ITEM_COUNT = 3;
}

class MockWaterFlowSpringEffect : public ScrollEdgeEffect {
public:
    MockWaterFlowSpringEffect() : ScrollEdgeEffect(EdgeEffect::SPRING) {}
    MOCK_METHOD(void, ProcessSpringUpdate, (), (override));
};

class WaterFlowSWLazyLayoutTest : public WaterFlowTestNg {
protected:
    void GetWaterFlow() override
    {
        WaterFlowTestNg::GetWaterFlow();
        info_ = AceType::DynamicCast<WaterFlowLayoutInfoSW>(pattern_->layoutInfo_);
        EXPECT_TRUE(info_);
    }

    RefPtr<FrameNode> PrepareBoundaryLazyColumnReload()
    {
        WaterFlowModelNG model = CreateWaterFlow();
        model.SetColumnsTemplate("1fr");
        ViewAbstract::SetWidth(CalcLength(WATER_FLOW_WIDTH));
        ViewAbstract::SetHeight(CalcLength(400.0f));
        PaddingProperty padding;
        padding.bottom = CalcLength(150.0f);
        layoutProperty_->UpdatePadding(padding);
        ScrollableModelNG::SetContentClip(AceType::RawPtr(frameNode_), ContentClipMode::BOUNDARY, nullptr);

        LazyColumnLayoutModel::Create();
        ViewAbstract::SetWidth(CalcLength(1.0f, DimensionUnit::PERCENT));
        auto mockLazy = CreateItemsInLazyForEach(100, [](int32_t) { return 100.0f; });
        ViewStackProcessor::GetInstance()->Pop();
        CreateDone();

        auto lazyColumn = AceType::DynamicCast<FrameNode>(frameNode_->GetChildAtIndex(0));
        if (!lazyColumn) {
            return nullptr;
        }
        auto lazyForEachNode = AceType::DynamicCast<LazyForEachNode>(lazyColumn->GetChildAtIndex(0));
        if (!lazyForEachNode) {
            return nullptr;
        }
        UpdateCurrentOffset(-5000.0f);
        mockLazy->SetTotalCount(RELOADED_ITEM_COUNT);
        lazyForEachNode->OnDataReloaded();
        return lazyColumn;
    }

    RefPtr<WaterFlowLayoutInfoSW> info_;
};

/**
 * @tc.name: DirtyLazyLayoutItemChildRequest001
 * @tc.desc: A child-request layout pass measures a lazy-layout item only through the lazy child path.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowSWLazyLayoutTest, DirtyLazyLayoutItemChildRequest001, TestSize.Level1)
{
    WaterFlowModelNG model = CreateWaterFlow();
    model.SetColumnsTemplate("1fr");
    CreateWaterFlowItems(20);
    CreateDone();

    auto item = GetItem(2);
    ASSERT_TRUE(item);
    item->GetLayoutProperty()->SetNeedLazyLayout(true);

    int32_t measureCount = 0;
    item->measureCallback_ = [&measureCount](RefPtr<Kit::FrameNode>&) { ++measureCount; };
    item->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_BY_CHILD_REQUEST);
    ASSERT_TRUE(CheckUpdateByChildRequest(layoutProperty_->GetPropertyChangeFlag()));

    UpdateCurrentOffset(-1.0f);

    EXPECT_EQ(measureCount, 1);
}

/**
 * @tc.name: ContentClipBoundaryLazyColumnReload001
 * @tc.desc: SW updates its exact extent and shrink state when a sole LazyColumn reloads fewer items.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowSWLazyLayoutTest, ContentClipBoundaryLazyColumnReload001, TestSize.Level1)
{
    auto lazyColumn = PrepareBoundaryLazyColumnReload();
    ASSERT_NE(lazyColumn, nullptr);
    info_->maxHeight_ += 1000.0f;

    auto layoutAlgorithm = AceType::DynamicCast<WaterFlowLayoutSW>(pattern_->CreateLayoutAlgorithm());
    ASSERT_NE(layoutAlgorithm, nullptr);
    auto algoWrapper = AceType::MakeRefPtr<LayoutAlgorithmWrapper>(layoutAlgorithm);
    algoWrapper->Measure(AceType::RawPtr(frameNode_));
    EXPECT_TRUE(info_->contentSizeDiminished_);
    EXPECT_NEAR(info_->maxHeight_,
        -info_->totalOffset_ + info_->EndPos() + info_->footerHeight_ + info_->BotMargin(), 0.01f);

    algoWrapper->Layout(AceType::RawPtr(frameNode_));
    DirtySwapConfig config;
    EXPECT_FALSE(pattern_->IsOutOfBoundary(false));
    pattern_->OnDirtyLayoutWrapperSwap(frameNode_, config);
    EXPECT_FALSE(info_->contentSizeDiminished_);

    info_->contentSizeDiminished_ = true;
    algoWrapper->Measure(AceType::RawPtr(frameNode_));
    EXPECT_FALSE(info_->contentSizeDiminished_);
}

/**
 * @tc.name: PredictSoleLazyChildDoesNotPublishState001
 * @tc.desc: A cache measurement does not publish the sole lazy child's scroll and content extent state.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowSWLazyLayoutTest, PredictSoleLazyChildDoesNotPublishState001, TestSize.Level1)
{
    auto lazyColumn = PrepareBoundaryLazyColumnReload();
    ASSERT_NE(lazyColumn, nullptr);
    auto layoutAlgorithm = AceType::DynamicCast<WaterFlowLayoutSW>(pattern_->CreateLayoutAlgorithm());
    ASSERT_NE(layoutAlgorithm, nullptr);
    auto algoWrapper = AceType::MakeRefPtr<LayoutAlgorithmWrapper>(layoutAlgorithm);
    algoWrapper->Measure(AceType::RawPtr(frameNode_));
    const auto totalOffset = info_->totalOffset_;
    const auto maxHeight = info_->maxHeight_;
    info_->contentSizeDiminished_ = false;

    layoutAlgorithm->cacheDeadline_ = 0;
    layoutAlgorithm->UpdateSoleLazyChild(lazyColumn, 0, 0, 10.0f, 100.0f, 50.0f);

    EXPECT_EQ(info_->totalOffset_, totalOffset);
    EXPECT_EQ(info_->maxHeight_, maxHeight);
    EXPECT_FALSE(info_->contentSizeDiminished_);
}

/**
 * @tc.name: ContentSizeDiminishedRestartsSpring001
 * @tc.desc: A diminished SW content extent updates an active spring after layout swap.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowSWLazyLayoutTest, ContentSizeDiminishedRestartsSpring001, TestSize.Level1)
{
    WaterFlowModelNG model = CreateWaterFlow();
    model.SetColumnsTemplate("1fr");
    CreateWaterFlowItems(20);
    CreateDone();

    info_->itemStart_ = false;
    info_->offsetEnd_ = true;
    for (auto& lane : info_->lanes_.back()) {
        lane.endPos = 0.0f;
    }
    ASSERT_TRUE(pattern_->IsOutOfBoundary(false));

    auto scrollable = pattern_->GetScrollableEvent()->GetScrollable();
    ASSERT_NE(scrollable, nullptr);
    MockAnimationManager::GetInstance().SetTicks(2);
    scrollable->StartSpringMotion(1.0, 0.0, ExtentPair(0.0, 0.0), ExtentPair(0.0, 0.0));
    ASSERT_TRUE(scrollable->IsSpringMotionRunning());

    auto springEffect = AceType::MakeRefPtr<MockWaterFlowSpringEffect>();
    pattern_->scrollEffect_ = springEffect;
    info_->contentSizeDiminished_ = true;
    EXPECT_CALL(*springEffect, ProcessSpringUpdate()).Times(1);
    pattern_->OnDirtyLayoutWrapperSwap(frameNode_, {});
    EXPECT_FALSE(info_->contentSizeDiminished_);

    pattern_->SetCanStayOverScroll(true);
    info_->contentSizeDiminished_ = true;
    pattern_->OnDirtyLayoutWrapperSwap(frameNode_, {});
    EXPECT_FALSE(info_->contentSizeDiminished_);
    scrollable->StopScrollable();
}

} // namespace OHOS::Ace::NG
