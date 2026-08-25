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

#include "test/unittest/core/pattern/lazy_layout/lazy_layout_test_utils.h"

#include "core/components_ng/layout/layout_wrapper_node.h"
#include "core/components_ng/pattern/lazy_layout/lazy_layout_utils.h"
#include "core/components_ng/pattern/lazy_waterflow_layout/lazy_water_flow_layout_algorithm.h"
#include "core/components_ng/pattern/lazy_waterflow_layout/lazy_water_flow_layout_info.h"
#include "core/components_v2/inspector/inspector_constants.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t CACHED_PARENT_MATRIX_NODE_ID = -1000;
constexpr int32_t ESTIMATE_ITEM_COUNT = 10;
constexpr int32_t ESTIMATE_LANE_COUNT = 2;
constexpr int32_t ESTIMATE_HOST_NODE_ID = -2200;
constexpr int32_t ESTIMATE_FIRST_CHILD_NODE_ID = -2201;

class LazyWaterFlowLayoutEstimateTest : public LazyWaterFlowLayoutTestBase {};
} // namespace

/**
 * @tc.name: LazyWaterFlowLayoutPattern_CachedParentMatrix_001
 * @tc.desc: Test cached LazyVWaterFlow identity under List, WaterFlow and Scroll before main-tree attachment
 * @tc.type: FUNC
 */
HWTEST_F(LazyWaterFlowLayoutEstimateTest, LazyWaterFlowLayoutPattern_CachedParentMatrix_001, TestSize.Level1)
{
    int32_t nodeId = CACHED_PARENT_MATRIX_NODE_ID;
    for (const auto& parentCase : CACHED_LAZY_PARENT_CASES) {
        SCOPED_TRACE(parentCase.name);
        auto context = CreateCachedLazyParentTestContext<LazyWaterFlowLayoutPattern>(
            parentCase, V2::LAZY_V_WATERFLOW_LAYOUT_ETS_TAG, nodeId);
        ASSERT_NE(context.parentNode, nullptr);
        ASSERT_NE(context.intermediateNode, nullptr);
        ASSERT_NE(context.lazyNode, nullptr);
        ASSERT_NE(context.layoutWrapper, nullptr);

        auto lazyProperty = context.lazyNode->GetLayoutProperty();
        auto clonedProperty = context.layoutWrapper->GetLayoutProperty();
        ASSERT_NE(lazyProperty, nullptr);
        ASSERT_NE(clonedProperty, nullptr);
        EXPECT_TRUE(context.lazyNode->IsNeedLazyLayout());
        EXPECT_TRUE(lazyProperty->GetNeedLazyLayout());
        EXPECT_TRUE(clonedProperty->GetNeedLazyLayout());

        context.lazyNode->MountToParent(context.intermediateNode, DEFAULT_NODE_SLOT, true);
        EXPECT_FALSE(context.lazyNode->IsOnMainTree());
        EXPECT_TRUE(context.intermediateNode->IsNeedLazyLayout());
        EXPECT_TRUE(context.intermediateNode->GetLayoutProperty()->GetNeedLazyLayout());
        EXPECT_TRUE(LazyLayoutUtils::ValidateAndSetLazyLayoutParent(context.lazyNode, Axis::VERTICAL));
        EXPECT_TRUE(context.lazyNode->IsNeedLazyLayout());
    }
}

/**
 * @tc.name: EstimateLayoutWhenDetached001
 * @tc.desc: Test detached LazyWaterFlowLayout estimates fresh content and preserves measured caches.
 * @tc.type: FUNC
 */
HWTEST_F(LazyWaterFlowLayoutEstimateTest, EstimateLayoutWhenDetached001, TestSize.Level1)
{
    auto layoutInfo = AceType::MakeRefPtr<LazyWaterFlowLayoutInfo>();
    auto algorithm = AceType::MakeRefPtr<LazyWaterFlowLayoutAlgorithm>(layoutInfo);
    algorithm->totalItemCount_ = ESTIMATE_ITEM_COUNT;
    algorithm->crossLens_ = { LAZY_WATER_FLOW_SCROLL_WIDTH / ESTIMATE_LANE_COUNT,
        LAZY_WATER_FLOW_SCROLL_WIDTH / ESTIMATE_LANE_COUNT };
    const auto context = CreateCachedLazyLayoutTestContext(V2::COLUMN_ETS_TAG,
        AceType::MakeRefPtr<LazyWaterFlowLayoutPattern>(), algorithm,
        SizeF(LAZY_WATER_FLOW_SCROLL_WIDTH, LAZY_WATER_FLOW_SCROLL_HEIGHT));
    ASSERT_NE(context.host, nullptr);
    ASSERT_NE(context.wrapper, nullptr);
    EXPECT_FALSE(context.host->IsOnMainTree());
    EXPECT_TRUE(context.host->IsNeedLazyLayout());

    std::optional<ViewPosReference> posRef;
    algorithm->UpdateReferencePos(AceType::RawPtr(context.wrapper), posRef);
    EXPECT_TRUE(algorithm->isEstimatePass_);
    EXPECT_FALSE(algorithm->needSkipLayout_);

    algorithm->prevBodyMainSize_ = 500.0f;
    layoutInfo->CacheItemHeight(0, 40.0f);
    layoutInfo->CacheItemHeight(1, 60.0f);
    layoutInfo->totalMainSize_ = 500.0f;
    const auto previousHeights = layoutInfo->idxToHeight_;
    context.host->AttachToMainTree();
    context.host->DetachFromMainTree();
    algorithm->UpdateReferencePos(AceType::RawPtr(context.wrapper), posRef);
    EXPECT_FALSE(algorithm->isEstimatePass_);
    EXPECT_TRUE(algorithm->needSkipLayout_);
    EXPECT_EQ(layoutInfo->idxToHeight_, previousHeights);
    EXPECT_FLOAT_EQ(layoutInfo->totalMainSize_, 500.0f);

    algorithm->totalItemCount_ = ESTIMATE_LANE_COUNT;
    algorithm->UpdateReferencePos(AceType::RawPtr(context.wrapper), posRef);
    EXPECT_FALSE(algorithm->isEstimatePass_);
    EXPECT_FALSE(algorithm->needSkipLayout_);
}

/**
 * @tc.name: EstimateLayoutWithParentReference001
 * @tc.desc: Test LazyWaterFlowLayout estimation honors parent prediction range and measured body size.
 * @tc.type: FUNC
 */
HWTEST_F(LazyWaterFlowLayoutEstimateTest, EstimateLayoutWithParentReference001, TestSize.Level1)
{
    auto layoutInfo = AceType::MakeRefPtr<LazyWaterFlowLayoutInfo>();
    auto algorithm = AceType::MakeRefPtr<LazyWaterFlowLayoutAlgorithm>(layoutInfo);
    algorithm->totalItemCount_ = ESTIMATE_ITEM_COUNT;
    algorithm->crossLens_ = { LAZY_WATER_FLOW_SCROLL_WIDTH / ESTIMATE_LANE_COUNT,
        LAZY_WATER_FLOW_SCROLL_WIDTH / ESTIMATE_LANE_COUNT };
    const auto context = CreateCachedLazyLayoutTestContext(V2::COLUMN_ETS_TAG,
        AceType::MakeRefPtr<LazyWaterFlowLayoutPattern>(), algorithm,
        SizeF(LAZY_WATER_FLOW_SCROLL_WIDTH, LAZY_WATER_FLOW_SCROLL_HEIGHT));
    ASSERT_NE(context.wrapper, nullptr);
    std::optional<ViewPosReference> posRef = ViewPosReference {
        .viewPosStart = 0.0f,
        .viewPosEnd = LAZY_WATER_FLOW_SCROLL_HEIGHT,
        .referencePos = LAZY_WATER_FLOW_SCROLL_HEIGHT,
        .referenceEdge = ReferenceEdge::START,
        .axis = Axis::VERTICAL,
        .deadline = 1,
    };

    algorithm->UpdateReferencePos(AceType::RawPtr(context.wrapper), posRef);
    EXPECT_TRUE(algorithm->isEstimatePass_);

    algorithm->prevBodyMainSize_ = 100.0f;
    algorithm->UpdateReferencePos(AceType::RawPtr(context.wrapper), posRef);
    EXPECT_FALSE(algorithm->isEstimatePass_);
    EXPECT_TRUE(layoutInfo->deadline_.has_value());

    algorithm->prevBodyMainSize_ = 0.0f;
    posRef->referencePos = LAZY_WATER_FLOW_SCROLL_HEIGHT * 2.0f;
    algorithm->UpdateReferencePos(AceType::RawPtr(context.wrapper), posRef);
    EXPECT_FALSE(algorithm->isEstimatePass_);
}

/**
 * @tc.name: EstimateLaneSetsTotalHeight001
 * @tc.desc: Test LazyVWaterFlow samples two lane sets and estimates the unmeasured suffix.
 * @tc.type: FUNC
 */
HWTEST_F(LazyWaterFlowLayoutEstimateTest, EstimateLaneSetsTotalHeight001, TestSize.Level1)
{
    auto layoutInfo = AceType::MakeRefPtr<LazyWaterFlowLayoutInfo>();
    LazyWaterFlowLayoutAlgorithm algorithm(layoutInfo);
    algorithm.totalItemCount_ = ESTIMATE_ITEM_COUNT;
    algorithm.crossLens_ = { 100.0, 100.0 };
    algorithm.childLayoutConstraints_.resize(ESTIMATE_LANE_COUNT);
    algorithm.mainGap_ = 4.0f;
    algorithm.isEstimatePass_ = true;
    algorithm.viewStart_ = 0.0f;
    algorithm.viewEnd_ = 1.0f;

    auto host = FrameNode::CreateFrameNode(V2::LAZY_V_WATERFLOW_LAYOUT_ETS_TAG, ESTIMATE_HOST_NODE_ID,
        AceType::MakeRefPtr<LazyWaterFlowLayoutPattern>());
    auto wrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        host, AceType::MakeRefPtr<GeometryNode>(), host->GetLayoutProperty());
    int32_t measureCount = 0;
    int32_t childNodeId = ESTIMATE_FIRST_CHILD_NODE_ID;
    AppendFixedHeightChild(wrapper, childNodeId--, 40.0f, measureCount);
    AppendFixedHeightChild(wrapper, childNodeId--, 60.0f, measureCount);
    AppendFixedHeightChild(wrapper, childNodeId--, 80.0f, measureCount);
    AppendFixedHeightChild(wrapper, childNodeId--, 70.0f, measureCount);
    AppendFixedHeightChild(wrapper, childNodeId, 200.0f, measureCount);

    algorithm.MeasureEstimateItems(AceType::RawPtr(wrapper));

    EXPECT_EQ(measureCount, 4);
    EXPECT_EQ(layoutInfo->idxToHeight_.size(), 4);
    EXPECT_GT(layoutInfo->totalMainSize_, 134.0f);
}
} // namespace OHOS::Ace::NG
