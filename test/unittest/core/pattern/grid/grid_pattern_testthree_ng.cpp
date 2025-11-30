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

#include "gtest/gtest.h"
#include "test/unittest/core/pattern/test_ng.h"

#include "core/components_ng/layout/layout_wrapper_node.h"
#include "core/components_ng/pattern/grid/grid_pattern.h"
#include "core/components_ng/pattern/grid/grid_scroll/grid_scroll_layout_algorithm.h"
#include "core/components_ng/pattern/grid/grid_scroll/grid_scroll_with_options_layout_algorithm.h"
#include "core/components_ng/pattern/scroll/scroll_event_hub.h"
#include "core/components_ng/pattern/scrollable/scrollable_pattern.h"

namespace OHOS::Ace::NG {
using namespace testing;
using namespace testing::ext;

class GridTestThreeNg : public TestNG {
public:
};

/**
 * @tc.name: SkipRegularLines001
 * @tc.desc: Test GridScrollLayoutAlgorithm SkipRegularLines
 * @tc.type: FUNC
 */
HWTEST_F(GridTestThreeNg, SkipRegularLines001, TestSize.Level1)
{
    GridLayoutInfo gridLayoutInfo;
    gridLayoutInfo.lineHeightMap_[0] = 1.0f;
    gridLayoutInfo.lineHeightMap_[1] = 2.0f;
    gridLayoutInfo.lineHeightMap_[2] = 3.0f;
    gridLayoutInfo.lineHeightMap_[3] = 6.0f;
    gridLayoutInfo.startIndex_ = 1;
    gridLayoutInfo.currentOffset_ = 24.0f;
    RefPtr<GridScrollLayoutAlgorithm> layout = AceType::MakeRefPtr<GridScrollLayoutAlgorithm>(gridLayoutInfo);
    ASSERT_NE(layout, nullptr);
    layout->mainGap_ = -20.0f;
    layout->info_.crossCount_ = 4;
    layout->SkipRegularLines(true);
    EXPECT_EQ(layout->info_.currentOffset_, 24.0f);
}

/**
 * @tc.name: SkipRegularLinesForward
 * @tc.desc: Test GridScrollLayoutAlgorithm SkipRegularLines
 * @tc.type: FUNC
 */
HWTEST_F(GridTestThreeNg, SkipRegularLinesForward, TestSize.Level1)
{
    GridLayoutInfo gridLayoutInfo;
    gridLayoutInfo.lineHeightMap_[0] = 60.0f;
    gridLayoutInfo.lineHeightMap_[1] = 60.0f;
    gridLayoutInfo.startIndex_ = 30;
    gridLayoutInfo.currentOffset_ = 240.0f;
    gridLayoutInfo.childrenCount_ = 100;
    gridLayoutInfo.crossCount_ = 3;
    RefPtr<GridScrollLayoutAlgorithm> layout = AceType::MakeRefPtr<GridScrollLayoutAlgorithm>(gridLayoutInfo);
    ASSERT_NE(layout, nullptr);
    layout->mainGap_ = 0;
    layout->SkipRegularLines(true);
    EXPECT_EQ(layout->info_.currentOffset_, 0.0f);
    EXPECT_EQ(layout->info_.startIndex_, 18);
}
/**
 * @tc.name: SkipIrregularLines001
 * @tc.desc: Test GridScrollLayoutAlgorithm SkipIrregularLines
 * @tc.type: FUNC
 */
HWTEST_F(GridTestThreeNg, SkipIrregularLines001, TestSize.Level1)
{
    GridLayoutInfo gridLayoutInfo;
    gridLayoutInfo.lineHeightMap_[0] = 1.0f;
    gridLayoutInfo.lineHeightMap_[1] = 2.0f;
    gridLayoutInfo.lineHeightMap_[2] = 3.0f;
    gridLayoutInfo.lineHeightMap_[3] = 6.0f;
    gridLayoutInfo.startIndex_ = 1;
    gridLayoutInfo.currentOffset_ = 24.0f;
    gridLayoutInfo.prevOffset_ = 30.0f;
    gridLayoutInfo.gridMatrix_[0] = { { 1, -2 }, { 3, -4 } };
    gridLayoutInfo.gridMatrix_[1] = { { 5, -6 }, { 7, -8 } };
    RefPtr<GridScrollLayoutAlgorithm> layout = AceType::MakeRefPtr<GridScrollLayoutAlgorithm>(gridLayoutInfo);
    ASSERT_NE(layout, nullptr);
    layout->info_.crossCount_ = 4;
    RefPtr<GridPattern> gridPattern = AceType::MakeRefPtr<GridPattern>();
    auto frameNode = FrameNode::CreateFrameNode(V2::SWIPER_ETS_TAG, 2, gridPattern);
    ASSERT_NE(frameNode, nullptr);
    RefPtr<GridLayoutProperty> gridLayoutProperty = AceType::MakeRefPtr<GridLayoutProperty>();
    frameNode->layoutProperty_ = gridLayoutProperty;
    gridPattern->frameNode_ = frameNode;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(geometryNode, nullptr);
    GeometryProperty geometryProperty;
    geometryProperty.rect_ = RectF(20.0f, 20.0f, 100.0f, 100.0f);
    geometryNode->frame_ = geometryProperty;
    LayoutWrapperNode layoutWrapper(frameNode, geometryNode, gridLayoutProperty);
    frameNode->geometryNode_ = geometryNode;
    gridPattern->frameNode_ = frameNode;
    gridPattern->info_ = gridLayoutInfo;
    layout->SkipIrregularLines(&layoutWrapper, true);
    EXPECT_EQ(layout->info_.currentOffset_, 24.0f);
}

/**
 * @tc.name: SkipIrregularLines002
 * @tc.desc: Test GridScrollLayoutAlgorithm SkipIrregularLines
 * @tc.type: FUNC
 */
HWTEST_F(GridTestThreeNg, SkipIrregularLines002, TestSize.Level1)
{
    GridLayoutInfo gridLayoutInfo;
    gridLayoutInfo.lineHeightMap_[0] = 1.0f;
    gridLayoutInfo.lineHeightMap_[1] = 2.0f;
    gridLayoutInfo.lineHeightMap_[2] = 3.0f;
    gridLayoutInfo.lineHeightMap_[3] = 6.0f;
    gridLayoutInfo.startIndex_ = 1;
    gridLayoutInfo.currentOffset_ = 24.0f;
    gridLayoutInfo.prevOffset_ = 30.0f;
    gridLayoutInfo.gridMatrix_[0] = { { 1, 2 }, { 3, 4 } };
    gridLayoutInfo.gridMatrix_[1] = { { 5, 6 }, { 7, 8 } };
    RefPtr<GridScrollLayoutAlgorithm> layout = AceType::MakeRefPtr<GridScrollLayoutAlgorithm>(gridLayoutInfo);
    ASSERT_NE(layout, nullptr);
    layout->info_.crossCount_ = 4;
    RefPtr<GridPattern> gridPattern = AceType::MakeRefPtr<GridPattern>();
    auto frameNode = FrameNode::CreateFrameNode(V2::SWIPER_ETS_TAG, 2, gridPattern);
    ASSERT_NE(frameNode, nullptr);
    RefPtr<GridLayoutProperty> gridLayoutProperty = AceType::MakeRefPtr<GridLayoutProperty>();
    frameNode->layoutProperty_ = gridLayoutProperty;
    gridPattern->frameNode_ = frameNode;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(geometryNode, nullptr);
    GeometryProperty geometryProperty;
    geometryProperty.rect_ = RectF(-20.0f, -20.0f, -100.0f, -100.0f);
    geometryNode->frame_ = geometryProperty;
    LayoutWrapperNode layoutWrapper(frameNode, geometryNode, gridLayoutProperty);
    frameNode->geometryNode_ = geometryNode;
    gridPattern->frameNode_ = frameNode;
    gridPattern->info_ = gridLayoutInfo;
    layout->SkipIrregularLines(&layoutWrapper, true);
    EXPECT_EQ(layout->info_.currentOffset_, layout->info_.prevOffset_);
}

/**
 * @tc.name: FillNewLineBackward001
 * @tc.desc: Test GridScrollLayoutAlgorithm FillNewLineBackward
 * @tc.type: FUNC
 */
HWTEST_F(GridTestThreeNg, FillNewLineBackward001, TestSize.Level1)
{
    GridLayoutInfo gridLayoutInfo;
    gridLayoutInfo.lineHeightMap_[0] = 1.0f;
    gridLayoutInfo.lineHeightMap_[1] = 2.0f;
    gridLayoutInfo.lineHeightMap_[2] = 3.0f;
    gridLayoutInfo.lineHeightMap_[3] = 6.0f;
    gridLayoutInfo.startIndex_ = 1;
    gridLayoutInfo.currentOffset_ = 24.0f;
    gridLayoutInfo.prevOffset_ = 30.0f;
    gridLayoutInfo.endIndex_ = 5;
    gridLayoutInfo.gridMatrix_[0] = { { 1, 2 }, { 3, 4 } };
    gridLayoutInfo.gridMatrix_[1] = { { 5, 6 }, { 7, 8 } };
    RefPtr<GridScrollLayoutAlgorithm> layout = AceType::MakeRefPtr<GridScrollLayoutAlgorithm>(gridLayoutInfo);
    ASSERT_NE(layout, nullptr);
    layout->info_.crossCount_ = 4;
    RefPtr<GridPattern> gridPattern = AceType::MakeRefPtr<GridPattern>();
    auto frameNode = FrameNode::CreateFrameNode(V2::SWIPER_ETS_TAG, 2, gridPattern);
    ASSERT_NE(frameNode, nullptr);
    RefPtr<GridLayoutProperty> gridLayoutProperty = AceType::MakeRefPtr<GridLayoutProperty>();
    frameNode->layoutProperty_ = gridLayoutProperty;
    gridPattern->frameNode_ = frameNode;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(geometryNode, nullptr);
    GeometryProperty geometryProperty;
    geometryProperty.rect_ = RectF(20.0f, 20.0f, 100.0f, 100.0f);
    geometryNode->frame_ = geometryProperty;
    LayoutWrapperNode layoutWrapper(frameNode, geometryNode, gridLayoutProperty);
    frameNode->geometryNode_ = geometryNode;
    gridPattern->frameNode_ = frameNode;
    gridPattern->info_ = gridLayoutInfo;
    layout->moveToEndLineIndex_ = 4;
    layout->FillNewLineBackward(2.0f, 3.0f, &layoutWrapper, true);
    EXPECT_EQ(layout->cellAveLength_, -1.0f);
}

/**
 * @tc.name: MeasureNewChild001
 * @tc.desc: Test GridScrollLayoutAlgorithm MeasureNewChild
 * @tc.type: FUNC
 */
HWTEST_F(GridTestThreeNg, MeasureNewChild001, TestSize.Level1)
{
    GridLayoutInfo gridLayoutInfo;
    gridLayoutInfo.lineHeightMap_[0] = 1.0f;
    gridLayoutInfo.lineHeightMap_[1] = 2.0f;
    gridLayoutInfo.lineHeightMap_[2] = 3.0f;
    gridLayoutInfo.lineHeightMap_[3] = 6.0f;
    gridLayoutInfo.startIndex_ = 1;
    gridLayoutInfo.currentOffset_ = 24.0f;
    gridLayoutInfo.prevOffset_ = 30.0f;
    gridLayoutInfo.endIndex_ = 5;
    gridLayoutInfo.gridMatrix_[0] = { { 1, 2 }, { 3, 4 } };
    gridLayoutInfo.gridMatrix_[1] = { { 5, 6 }, { 7, 8 } };
    RefPtr<GridScrollLayoutAlgorithm> layout = AceType::MakeRefPtr<GridScrollLayoutAlgorithm>(gridLayoutInfo);
    ASSERT_NE(layout, nullptr);
    layout->info_.crossCount_ = 4;
    RefPtr<GridPattern> gridPattern = AceType::MakeRefPtr<GridPattern>();
    auto frameNode = FrameNode::CreateFrameNode(V2::SWIPER_ETS_TAG, 2, gridPattern);
    ASSERT_NE(frameNode, nullptr);
    RefPtr<GridLayoutProperty> gridLayoutProperty = AceType::MakeRefPtr<GridLayoutProperty>();
    frameNode->layoutProperty_ = gridLayoutProperty;
    gridPattern->frameNode_ = frameNode;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(geometryNode, nullptr);
    GeometryProperty geometryProperty;
    geometryProperty.rect_ = RectF(20.0f, 20.0f, 100.0f, 100.0f);
    geometryNode->frame_ = geometryProperty;
    LayoutWrapperNode layoutWrapper(frameNode, geometryNode, gridLayoutProperty);
    frameNode->geometryNode_ = geometryNode;
    gridPattern->frameNode_ = frameNode;
    gridPattern->info_ = gridLayoutInfo;
    layout->moveToEndLineIndex_ = 4;
    SizeF frameSize(100.0f, 100.0f);
    RefPtr<LayoutWrapper> childLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, gridLayoutProperty);
    layout->currentItemColSpan_ = 5;
    layout->MeasureNewChild(frameSize, 2, &layoutWrapper, childLayoutWrapper, true);
    EXPECT_EQ(layout->currentItemColSpan_, 5);
}

/**
 * @tc.name: MeasureChildPlaced001
 * @tc.desc: Test GridScrollLayoutAlgorithm MeasureChildPlaced
 * @tc.type: FUNC
 */
HWTEST_F(GridTestThreeNg, MeasureChildPlaced001, TestSize.Level1)
{
    GridLayoutInfo gridLayoutInfo;
    gridLayoutInfo.lineHeightMap_[0] = 1.0f;
    gridLayoutInfo.lineHeightMap_[1] = 2.0f;
    gridLayoutInfo.lineHeightMap_[2] = 3.0f;
    gridLayoutInfo.lineHeightMap_[3] = 6.0f;
    gridLayoutInfo.startIndex_ = 1;
    gridLayoutInfo.currentOffset_ = 24.0f;
    gridLayoutInfo.prevOffset_ = 30.0f;
    gridLayoutInfo.endIndex_ = 5;
    gridLayoutInfo.gridMatrix_[0] = { { 1, 2 }, { 3, 4 } };
    gridLayoutInfo.gridMatrix_[1] = { { 5, 6 }, { 7, 8 } };
    RefPtr<GridScrollLayoutAlgorithm> layout = AceType::MakeRefPtr<GridScrollLayoutAlgorithm>(gridLayoutInfo);
    ASSERT_NE(layout, nullptr);
    RefPtr<GridPattern> gridPattern = AceType::MakeRefPtr<GridPattern>();
    auto frameNode = FrameNode::CreateFrameNode(V2::SWIPER_ETS_TAG, 2, gridPattern);
    ASSERT_NE(frameNode, nullptr);
    RefPtr<GridLayoutProperty> gridLayoutProperty = AceType::MakeRefPtr<GridLayoutProperty>();
    frameNode->layoutProperty_ = gridLayoutProperty;
    gridPattern->frameNode_ = frameNode;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(geometryNode, nullptr);
    GeometryProperty geometryProperty;
    geometryProperty.rect_ = RectF(20.0f, 20.0f, 100.0f, 100.0f);
    geometryNode->frame_ = geometryProperty;
    LayoutWrapperNode layoutWrapper(frameNode, geometryNode, gridLayoutProperty);
    frameNode->geometryNode_ = geometryNode;
    gridPattern->frameNode_ = frameNode;
    gridPattern->info_ = gridLayoutInfo;
    layout->moveToEndLineIndex_ = 4;
    SizeF frameSize(100.0f, 100.0f);
    RefPtr<LayoutWrapper> childLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, gridLayoutProperty);
    layout->info_.crossCount_ = 4;
    layout->currentItemColSpan_ = 5;
    auto result = layout->MeasureChildPlaced(frameSize, 2, 2, &layoutWrapper, childLayoutWrapper);
    EXPECT_EQ(result, 0);
}

/**
 * @tc.name: CheckNeedMeasure001
 * @tc.desc: Test GridScrollLayoutAlgorithm CheckNeedMeasure
 * @tc.type: FUNC
 */
HWTEST_F(GridTestThreeNg, CheckNeedMeasure001, TestSize.Level1)
{
    GridLayoutInfo gridLayoutInfo;
    gridLayoutInfo.clearStretch_ = true;
    RefPtr<GridScrollLayoutAlgorithm> layout = AceType::MakeRefPtr<GridScrollLayoutAlgorithm>(gridLayoutInfo);
    ASSERT_NE(layout, nullptr);
    RefPtr<GridPattern> gridPattern = AceType::MakeRefPtr<GridPattern>();
    auto frameNode = FrameNode::CreateFrameNode(V2::SWIPER_ETS_TAG, 2, gridPattern);
    ASSERT_NE(frameNode, nullptr);
    RefPtr<GridItemLayoutProperty> gridItemLayoutProperty = AceType::MakeRefPtr<GridItemLayoutProperty>();
    gridItemLayoutProperty->needStretch_ = true;
    frameNode->layoutProperty_ = gridItemLayoutProperty;
    gridPattern->frameNode_ = frameNode;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(geometryNode, nullptr);
    GeometryProperty geometryProperty;
    geometryProperty.rect_ = RectF(20.0f, 20.0f, 100.0f, 100.0f);
    geometryNode->frame_ = geometryProperty;
    LayoutWrapperNode layoutWrapper(frameNode, geometryNode, gridItemLayoutProperty);
    frameNode->geometryNode_ = geometryNode;
    gridPattern->frameNode_ = frameNode;
    gridPattern->info_ = gridLayoutInfo;
    layout->moveToEndLineIndex_ = 4;
    SizeF frameSize(100.0f, 100.0f);
    RefPtr<LayoutWrapper> childLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, gridItemLayoutProperty);
    layout->info_.crossCount_ = 4;
    layout->currentItemColSpan_ = 5;
    LayoutConstraintF layoutConstraint;
    auto result = layout->CheckNeedMeasure(childLayoutWrapper, layoutConstraint);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: CheckNeedMeasure002
 * @tc.desc: Test GridScrollLayoutAlgorithm CheckNeedMeasure
 * @tc.type: FUNC
 */
HWTEST_F(GridTestThreeNg, CheckNeedMeasure002, TestSize.Level1)
{
    GridLayoutInfo gridLayoutInfo;
    gridLayoutInfo.clearStretch_ = true;
    RefPtr<GridScrollLayoutAlgorithm> layout = AceType::MakeRefPtr<GridScrollLayoutAlgorithm>(gridLayoutInfo);
    ASSERT_NE(layout, nullptr);
    RefPtr<GridPattern> gridPattern = AceType::MakeRefPtr<GridPattern>();
    auto frameNode = FrameNode::CreateFrameNode(V2::SWIPER_ETS_TAG, 2, gridPattern);
    ASSERT_NE(frameNode, nullptr);
    RefPtr<GridItemLayoutProperty> gridItemLayoutProperty = AceType::MakeRefPtr<GridItemLayoutProperty>();
    gridItemLayoutProperty->needStretch_ = true;
    frameNode->layoutProperty_ = gridItemLayoutProperty;
    gridPattern->frameNode_ = frameNode;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(geometryNode, nullptr);
    GeometryProperty geometryProperty;
    geometryProperty.rect_ = RectF(20.0f, 20.0f, 100.0f, 100.0f);
    geometryNode->frame_ = geometryProperty;
    LayoutWrapperNode layoutWrapper(frameNode, geometryNode, gridItemLayoutProperty);
    frameNode->geometryNode_ = geometryNode;
    gridPattern->frameNode_ = frameNode;
    gridPattern->info_ = gridLayoutInfo;
    layout->moveToEndLineIndex_ = 4;
    SizeF frameSize(100.0f, 100.0f);
    RefPtr<LayoutWrapper> childLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, gridItemLayoutProperty);
    layout->info_.crossCount_ = 4;
    layout->currentItemColSpan_ = 5;
    LayoutConstraintF layoutConstraint;
    layout->info_.axis_ = Axis::HORIZONTAL;
    auto result = layout->CheckNeedMeasure(childLayoutWrapper, layoutConstraint);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: CheckGridPlaced001
 * @tc.desc: Test GridScrollLayoutAlgorithm CheckGridPlaced
 * @tc.type: FUNC
 */
HWTEST_F(GridTestThreeNg, CheckGridPlaced001, TestSize.Level1)
{
    GridLayoutInfo gridLayoutInfo;
    gridLayoutInfo.lineHeightMap_[0] = 1.0f;
    gridLayoutInfo.lineHeightMap_[1] = 2.0f;
    gridLayoutInfo.startMainLineIndex_ = 0;
    gridLayoutInfo.endMainLineIndex_ = 2;
    RefPtr<GridScrollLayoutAlgorithm> layout = AceType::MakeRefPtr<GridScrollLayoutAlgorithm>(gridLayoutInfo);
    ASSERT_NE(layout, nullptr);
    layout->info_.crossCount_ = 4;
    auto result = layout->CheckGridPlaced(2, 2, 3, 2, 5);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: ComputeItemCrossPosition001
 * @tc.desc: Test GridScrollLayoutAlgorithm ComputeItemCrossPosition
 * @tc.type: FUNC
 */
HWTEST_F(GridTestThreeNg, ComputeItemCrossPosition001, TestSize.Level1)
{
    GridLayoutInfo gridLayoutInfo;
    gridLayoutInfo.lineHeightMap_[0] = 1.0f;
    gridLayoutInfo.lineHeightMap_[1] = 2.0f;
    gridLayoutInfo.startMainLineIndex_ = 0;
    gridLayoutInfo.endMainLineIndex_ = 2;
    RefPtr<GridScrollLayoutAlgorithm> layout = AceType::MakeRefPtr<GridScrollLayoutAlgorithm>(gridLayoutInfo);
    ASSERT_NE(layout, nullptr);
    layout->info_.crossCount_ = 4;
    layout->itemsCrossSize_[0] = 1.0f;
    layout->itemsCrossSize_[1] = 2.0f;
    layout->crossPaddingOffset_ = 2.0f;
    layout->crossGap_ = 2.0f;
    auto result = layout->ComputeItemCrossPosition(3);
    EXPECT_EQ(result, 11);
}

/**
 * @tc.name: MeasureCachedChild001
 * @tc.desc: Test GridScrollLayoutAlgorithm MeasureCachedChild
 * @tc.type: FUNC
 */
HWTEST_F(GridTestThreeNg, MeasureCachedChild001, TestSize.Level1)
{
    GridLayoutInfo gridLayoutInfo;
    gridLayoutInfo.clearStretch_ = true;
    RefPtr<GridScrollLayoutAlgorithm> layout = AceType::MakeRefPtr<GridScrollLayoutAlgorithm>(gridLayoutInfo);
    ASSERT_NE(layout, nullptr);
    RefPtr<GridPattern> gridPattern = AceType::MakeRefPtr<GridPattern>();
    auto frameNode = FrameNode::CreateFrameNode(V2::SWIPER_ETS_TAG, 2, gridPattern);
    ASSERT_NE(frameNode, nullptr);
    RefPtr<GridItemLayoutProperty> gridItemLayoutProperty = AceType::MakeRefPtr<GridItemLayoutProperty>();
    gridItemLayoutProperty->needStretch_ = true;
    frameNode->layoutProperty_ = gridItemLayoutProperty;
    gridPattern->frameNode_ = frameNode;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(geometryNode, nullptr);
    GeometryProperty geometryProperty;
    geometryProperty.rect_ = RectF(20.0f, 20.0f, 100.0f, 100.0f);
    geometryNode->frame_ = geometryProperty;
    LayoutWrapperNode layoutWrapper(frameNode, geometryNode, gridItemLayoutProperty);
    frameNode->geometryNode_ = geometryNode;
    gridPattern->frameNode_ = frameNode;
    gridPattern->info_ = gridLayoutInfo;
    layout->moveToEndLineIndex_ = 4;
    SizeF frameSize(100.0f, 100.0f);
    RefPtr<LayoutWrapper> childLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, gridItemLayoutProperty);
    layout->info_.crossCount_ = 4;
    layout->currentItemColSpan_ = 5;
    LayoutConstraintF layoutConstraint;
    auto result = layout->MeasureCachedChild(frameSize, 2, &layoutWrapper, childLayoutWrapper);
    EXPECT_EQ(result, 1);
}

/**
 * @tc.name: MeasureCachedChild002
 * @tc.desc: Test GridScrollLayoutAlgorithm MeasureCachedChild
 * @tc.type: FUNC
 */
HWTEST_F(GridTestThreeNg, MeasureCachedChild002, TestSize.Level1)
{
    GridLayoutInfo gridLayoutInfo;
    gridLayoutInfo.clearStretch_ = true;
    RefPtr<GridScrollLayoutAlgorithm> layout = AceType::MakeRefPtr<GridScrollLayoutAlgorithm>(gridLayoutInfo);
    ASSERT_NE(layout, nullptr);
    RefPtr<GridPattern> gridPattern = AceType::MakeRefPtr<GridPattern>();
    auto frameNode = FrameNode::CreateFrameNode(V2::SWIPER_ETS_TAG, 2, gridPattern);
    ASSERT_NE(frameNode, nullptr);
    RefPtr<GridItemLayoutProperty> gridItemLayoutProperty = AceType::MakeRefPtr<GridItemLayoutProperty>();
    gridItemLayoutProperty->needStretch_ = true;
    frameNode->layoutProperty_ = gridItemLayoutProperty;
    gridPattern->frameNode_ = frameNode;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(geometryNode, nullptr);
    GeometryProperty geometryProperty;
    geometryProperty.rect_ = RectF(20.0f, 20.0f, 100.0f, 100.0f);
    geometryNode->frame_ = geometryProperty;
    LayoutWrapperNode layoutWrapper(frameNode, geometryNode, gridItemLayoutProperty);
    frameNode->geometryNode_ = geometryNode;
    gridPattern->frameNode_ = frameNode;
    gridPattern->info_ = gridLayoutInfo;
    layout->moveToEndLineIndex_ = 4;
    SizeF frameSize(100.0f, 100.0f);
    RefPtr<LayoutWrapper> childLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, gridItemLayoutProperty);
    layout->info_.crossCount_ = 4;
    layout->currentItemColSpan_ = 2;
    layout->currentItemColStart_ = 3;
    layout->lastCross_ = 4;
    LayoutConstraintF layoutConstraint;
    auto result = layout->MeasureCachedChild(frameSize, 2, &layoutWrapper, childLayoutWrapper);
    EXPECT_EQ(result, -1);
}

/**
 * @tc.name: MeasureCachedChild003
 * @tc.desc: Test GridScrollLayoutAlgorithm MeasureCachedChild
 * @tc.type: FUNC
 */
HWTEST_F(GridTestThreeNg, MeasureCachedChild003, TestSize.Level1)
{
    GridLayoutInfo gridLayoutInfo;
    gridLayoutInfo.clearStretch_ = true;
    RefPtr<GridScrollLayoutAlgorithm> layout = AceType::MakeRefPtr<GridScrollLayoutAlgorithm>(gridLayoutInfo);
    ASSERT_NE(layout, nullptr);
    RefPtr<GridPattern> gridPattern = AceType::MakeRefPtr<GridPattern>();
    auto frameNode = FrameNode::CreateFrameNode(V2::SWIPER_ETS_TAG, 2, gridPattern);
    ASSERT_NE(frameNode, nullptr);
    RefPtr<GridItemLayoutProperty> gridItemLayoutProperty = AceType::MakeRefPtr<GridItemLayoutProperty>();
    gridItemLayoutProperty->needStretch_ = true;
    frameNode->layoutProperty_ = gridItemLayoutProperty;
    gridPattern->frameNode_ = frameNode;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(geometryNode, nullptr);
    GeometryProperty geometryProperty;
    geometryProperty.rect_ = RectF(20.0f, 20.0f, 100.0f, 100.0f);
    geometryNode->frame_ = geometryProperty;
    LayoutWrapperNode layoutWrapper(frameNode, geometryNode, gridItemLayoutProperty);
    frameNode->geometryNode_ = geometryNode;
    gridPattern->frameNode_ = frameNode;
    gridPattern->info_ = gridLayoutInfo;
    layout->moveToEndLineIndex_ = 4;
    SizeF frameSize(100.0f, 100.0f);
    RefPtr<LayoutWrapper> childLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, gridItemLayoutProperty);
    layout->info_.crossCount_ = 4;
    layout->currentItemColSpan_ = 2;
    layout->currentItemColStart_ = 3;
    layout->lastCross_ = 3;
    LayoutConstraintF layoutConstraint;
    auto result = layout->MeasureCachedChild(frameSize, 2, &layoutWrapper, childLayoutWrapper);
    EXPECT_EQ(result, 1);
}

/**
 * @tc.name: MeasureCachedChild004
 * @tc.desc: Test GridScrollLayoutAlgorithm MeasureCachedChild
 * @tc.type: FUNC
 */
HWTEST_F(GridTestThreeNg, MeasureCachedChild004, TestSize.Level1)
{
    GridLayoutInfo gridLayoutInfo;
    gridLayoutInfo.lineHeightMap_[0] = 1.0f;
    gridLayoutInfo.lineHeightMap_[1] = 2.0f;
    RefPtr<GridScrollLayoutAlgorithm> layout = AceType::MakeRefPtr<GridScrollLayoutAlgorithm>(gridLayoutInfo);
    ASSERT_NE(layout, nullptr);
    RefPtr<GridPattern> gridPattern = AceType::MakeRefPtr<GridPattern>();
    auto frameNode = FrameNode::CreateFrameNode(V2::SWIPER_ETS_TAG, 2, gridPattern);
    ASSERT_NE(frameNode, nullptr);
    RefPtr<GridItemLayoutProperty> gridItemLayoutProperty = AceType::MakeRefPtr<GridItemLayoutProperty>();
    gridItemLayoutProperty->needStretch_ = true;
    frameNode->layoutProperty_ = gridItemLayoutProperty;
    gridPattern->frameNode_ = frameNode;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(geometryNode, nullptr);
    GeometryProperty geometryProperty;
    geometryProperty.rect_ = RectF(20.0f, 20.0f, 100.0f, 100.0f);
    geometryNode->frame_ = geometryProperty;
    LayoutWrapperNode layoutWrapper(frameNode, geometryNode, gridItemLayoutProperty);
    frameNode->geometryNode_ = geometryNode;
    gridPattern->frameNode_ = frameNode;
    gridPattern->info_ = gridLayoutInfo;
    layout->moveToEndLineIndex_ = 4;
    SizeF frameSize(100.0f, 100.0f);
    RefPtr<LayoutWrapper> childLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, gridItemLayoutProperty);
    layout->info_.crossCount_ = 2;
    layout->currentItemColSpan_ = 2;
    layout->currentItemColStart_ = 3;
    layout->lastCross_ = 3;
    LayoutConstraintF layoutConstraint;
    auto result = layout->MeasureCachedChild(frameSize, 2, &layoutWrapper, childLayoutWrapper);
    EXPECT_EQ(result, -1);
}

/**
 * @tc.name: MeasureCachedChild005
 * @tc.desc: Test GridScrollLayoutAlgorithm MeasureCachedChild
 * @tc.type: FUNC
 */
HWTEST_F(GridTestThreeNg, MeasureCachedChild005, TestSize.Level1)
{
    GridLayoutInfo gridLayoutInfo;
    gridLayoutInfo.lineHeightMap_[0] = 1.0f;
    gridLayoutInfo.lineHeightMap_[1] = 2.0f;
    RefPtr<GridScrollLayoutAlgorithm> layout = AceType::MakeRefPtr<GridScrollLayoutAlgorithm>(gridLayoutInfo);
    ASSERT_NE(layout, nullptr);
    RefPtr<GridPattern> gridPattern = AceType::MakeRefPtr<GridPattern>();
    auto frameNode = FrameNode::CreateFrameNode(V2::SWIPER_ETS_TAG, 2, gridPattern);
    ASSERT_NE(frameNode, nullptr);
    RefPtr<GridItemLayoutProperty> gridItemLayoutProperty = AceType::MakeRefPtr<GridItemLayoutProperty>();
    gridItemLayoutProperty->needStretch_ = true;
    frameNode->layoutProperty_ = gridItemLayoutProperty;
    gridPattern->frameNode_ = frameNode;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(geometryNode, nullptr);
    GeometryProperty geometryProperty;
    geometryProperty.rect_ = RectF(20.0f, 20.0f, 100.0f, 100.0f);
    geometryNode->frame_ = geometryProperty;
    LayoutWrapperNode layoutWrapper(frameNode, geometryNode, gridItemLayoutProperty);
    frameNode->geometryNode_ = geometryNode;
    gridPattern->frameNode_ = frameNode;
    gridPattern->info_ = gridLayoutInfo;
    layout->moveToEndLineIndex_ = 4;
    SizeF frameSize(100.0f, 100.0f);
    RefPtr<LayoutWrapper> childLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, gridItemLayoutProperty);
    layout->info_.crossCount_ = 5;
    layout->currentItemColSpan_ = 2;
    layout->currentItemColStart_ = 4;
    layout->lastCross_ = 3;
    LayoutConstraintF layoutConstraint;
    auto result = layout->MeasureCachedChild(frameSize, 2, &layoutWrapper, childLayoutWrapper);
    EXPECT_EQ(result, 1);
}

/**
 * @tc.name: MeasureCachedChild006
 * @tc.desc: Test GridScrollLayoutAlgorithm MeasureCachedChild
 * @tc.type: FUNC
 */
HWTEST_F(GridTestThreeNg, MeasureCachedChild006, TestSize.Level1)
{
    GridLayoutInfo gridLayoutInfo;
    gridLayoutInfo.lineHeightMap_[0] = 1.0f;
    gridLayoutInfo.lineHeightMap_[1] = 2.0f;
    RefPtr<GridScrollLayoutAlgorithm> layout = AceType::MakeRefPtr<GridScrollLayoutAlgorithm>(gridLayoutInfo);
    ASSERT_NE(layout, nullptr);
    RefPtr<GridPattern> gridPattern = AceType::MakeRefPtr<GridPattern>();
    auto frameNode = FrameNode::CreateFrameNode(V2::SWIPER_ETS_TAG, 2, gridPattern);
    ASSERT_NE(frameNode, nullptr);
    RefPtr<GridItemLayoutProperty> gridItemLayoutProperty = AceType::MakeRefPtr<GridItemLayoutProperty>();
    gridItemLayoutProperty->needStretch_ = true;
    frameNode->layoutProperty_ = gridItemLayoutProperty;
    gridPattern->frameNode_ = frameNode;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(geometryNode, nullptr);
    GeometryProperty geometryProperty;
    geometryProperty.rect_ = RectF(20.0f, 20.0f, 100.0f, 100.0f);
    geometryNode->frame_ = geometryProperty;
    LayoutWrapperNode layoutWrapper(frameNode, geometryNode, gridItemLayoutProperty);
    frameNode->geometryNode_ = geometryNode;
    gridPattern->frameNode_ = frameNode;
    gridPattern->info_ = gridLayoutInfo;
    layout->moveToEndLineIndex_ = 4;
    SizeF frameSize(100.0f, 100.0f);
    RefPtr<LayoutWrapper> childLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, gridItemLayoutProperty);
    layout->info_.crossCount_ = 5;
    layout->currentItemColSpan_ = 2;
    layout->currentItemColStart_ = 4;
    layout->lastCross_ = 3;
    LayoutConstraintF layoutConstraint;
    auto result = layout->MeasureCachedChild(frameSize, 2, &layoutWrapper, childLayoutWrapper);
    EXPECT_EQ(result, 1);
}

/**
 * @tc.name: MeasureCachedChild007
 * @tc.desc: Test GridScrollLayoutAlgorithm MeasureCachedChild
 * @tc.type: FUNC
 */
HWTEST_F(GridTestThreeNg, MeasureCachedChild007, TestSize.Level1)
{
    GridLayoutInfo gridLayoutInfo;
    gridLayoutInfo.lineHeightMap_[0] = 1.0f;
    gridLayoutInfo.lineHeightMap_[1] = 2.0f;
    RefPtr<GridScrollLayoutAlgorithm> layout = AceType::MakeRefPtr<GridScrollLayoutAlgorithm>(gridLayoutInfo);
    ASSERT_NE(layout, nullptr);
    RefPtr<GridPattern> gridPattern = AceType::MakeRefPtr<GridPattern>();
    auto frameNode = FrameNode::CreateFrameNode(V2::SWIPER_ETS_TAG, 2, gridPattern);
    ASSERT_NE(frameNode, nullptr);
    RefPtr<GridItemLayoutProperty> gridItemLayoutProperty = AceType::MakeRefPtr<GridItemLayoutProperty>();
    gridItemLayoutProperty->needStretch_ = true;
    frameNode->layoutProperty_ = gridItemLayoutProperty;
    gridPattern->frameNode_ = frameNode;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(geometryNode, nullptr);
    GeometryProperty geometryProperty;
    geometryProperty.rect_ = RectF(20.0f, 20.0f, 100.0f, 100.0f);
    geometryNode->frame_ = geometryProperty;
    LayoutWrapperNode layoutWrapper(frameNode, geometryNode, gridItemLayoutProperty);
    frameNode->geometryNode_ = geometryNode;
    gridPattern->frameNode_ = frameNode;
    gridPattern->info_ = gridLayoutInfo;
    layout->moveToEndLineIndex_ = 4;
    SizeF frameSize(100.0f, 100.0f);
    RefPtr<LayoutWrapper> childLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, gridItemLayoutProperty);
    layout->info_.crossCount_ = 3;
    layout->currentItemColSpan_ = 2;
    layout->currentItemColStart_ = 4;
    layout->lastCross_ = 3;
    layout->mainCount_ = 2;
    layout->currentMainLineIndex_ = 3;
    LayoutConstraintF layoutConstraint;
    auto result = layout->MeasureCachedChild(frameSize, 2, &layoutWrapper, childLayoutWrapper);
    EXPECT_EQ(result, -1);
}

/**
 * @tc.name: MeasureCachedChild008
 * @tc.desc: Test GridScrollLayoutAlgorithm MeasureCachedChild
 * @tc.type: FUNC
 */
HWTEST_F(GridTestThreeNg, MeasureCachedChild008, TestSize.Level1)
{
    GridLayoutInfo gridLayoutInfo;
    gridLayoutInfo.lineHeightMap_[0] = 1.0f;
    gridLayoutInfo.lineHeightMap_[1] = 2.0f;
    RefPtr<GridScrollLayoutAlgorithm> layout = AceType::MakeRefPtr<GridScrollLayoutAlgorithm>(gridLayoutInfo);
    ASSERT_NE(layout, nullptr);
    RefPtr<GridPattern> gridPattern = AceType::MakeRefPtr<GridPattern>();
    auto frameNode = FrameNode::CreateFrameNode(V2::SWIPER_ETS_TAG, 2, gridPattern);
    ASSERT_NE(frameNode, nullptr);
    RefPtr<GridItemLayoutProperty> gridItemLayoutProperty = AceType::MakeRefPtr<GridItemLayoutProperty>();
    gridItemLayoutProperty->needStretch_ = true;
    frameNode->layoutProperty_ = gridItemLayoutProperty;
    gridPattern->frameNode_ = frameNode;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(geometryNode, nullptr);
    GeometryProperty geometryProperty;
    geometryProperty.rect_ = RectF(20.0f, 20.0f, 100.0f, 100.0f);
    geometryNode->frame_ = geometryProperty;
    LayoutWrapperNode layoutWrapper(frameNode, geometryNode, gridItemLayoutProperty);
    frameNode->geometryNode_ = geometryNode;
    gridPattern->frameNode_ = frameNode;
    gridPattern->info_ = gridLayoutInfo;
    layout->moveToEndLineIndex_ = 4;
    SizeF frameSize(100.0f, 100.0f);
    RefPtr<LayoutWrapper> childLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, gridItemLayoutProperty);
    layout->info_.crossCount_ = 2;
    layout->currentItemColSpan_ = 1;
    layout->currentItemColStart_ = 3;
    layout->lastCross_ = 3;
    layout->mainCount_ = 5;
    layout->currentMainLineIndex_ = 4;
    LayoutConstraintF layoutConstraint;
    auto result = layout->MeasureCachedChild(frameSize, 2, &layoutWrapper, childLayoutWrapper);
    EXPECT_EQ(result, -1);
}

/**
 * @tc.name: MeasureCachedChild009
 * @tc.desc: Test GridScrollLayoutAlgorithm MeasureCachedChild
 * @tc.type: FUNC
 */
HWTEST_F(GridTestThreeNg, MeasureCachedChild009, TestSize.Level1)
{
    GridLayoutInfo gridLayoutInfo;
    gridLayoutInfo.lineHeightMap_[0] = 1.0f;
    gridLayoutInfo.lineHeightMap_[1] = 2.0f;
    RefPtr<GridScrollLayoutAlgorithm> layout = AceType::MakeRefPtr<GridScrollLayoutAlgorithm>(gridLayoutInfo);
    ASSERT_NE(layout, nullptr);
    RefPtr<GridPattern> gridPattern = AceType::MakeRefPtr<GridPattern>();
    auto frameNode = FrameNode::CreateFrameNode(V2::SWIPER_ETS_TAG, 2, gridPattern);
    ASSERT_NE(frameNode, nullptr);
    RefPtr<GridItemLayoutProperty> gridItemLayoutProperty = AceType::MakeRefPtr<GridItemLayoutProperty>();
    gridItemLayoutProperty->needStretch_ = true;
    frameNode->layoutProperty_ = gridItemLayoutProperty;
    gridPattern->frameNode_ = frameNode;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(geometryNode, nullptr);
    GeometryProperty geometryProperty;
    geometryProperty.rect_ = RectF(20.0f, 20.0f, 100.0f, 100.0f);
    geometryNode->frame_ = geometryProperty;
    LayoutWrapperNode layoutWrapper(frameNode, geometryNode, gridItemLayoutProperty);
    frameNode->geometryNode_ = geometryNode;
    gridPattern->frameNode_ = frameNode;
    gridPattern->info_ = gridLayoutInfo;
    layout->moveToEndLineIndex_ = 4;
    SizeF frameSize(100.0f, 100.0f);
    RefPtr<LayoutWrapper> childLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, gridItemLayoutProperty);
    layout->info_.crossCount_ = 2;
    layout->currentItemColSpan_ = 2;
    layout->currentItemColStart_ = 3;
    layout->lastCross_ = 3;
    layout->mainCount_ = 5;
    layout->currentMainLineIndex_ = 4;
    layout->currentItemRowSpan_ = 2;
    LayoutConstraintF layoutConstraint;
    auto result = layout->MeasureCachedChild(frameSize, 2, &layoutWrapper, childLayoutWrapper);
    EXPECT_EQ(result, -1);
}

/**
 * @tc.name: CalculateStartCachedCount001
 * @tc.desc: Test GridScrollWithOptionsLayoutAlgorithm CalculateStartCachedCount
 * @tc.type: FUNC
 */
HWTEST_F(GridTestThreeNg, CalculateStartCachedCount001, TestSize.Level1)
{
    GridLayoutInfo gridLayoutInfo;
    gridLayoutInfo.crossCount_ = 2;
    gridLayoutInfo.startIndex_ = 1;
    gridLayoutInfo.startMainLineIndex_ = 4;
    RefPtr<GridScrollWithOptionsLayoutAlgorithm> layout =
        AceType::MakeRefPtr<GridScrollWithOptionsLayoutAlgorithm>(gridLayoutInfo);
    ASSERT_NE(layout, nullptr);
    GridLayoutOptions options;
    options.irregularIndexes.insert(3);
    auto result = layout->CalculateStartCachedCount(options, 2);
    EXPECT_EQ(result, 4);
}

/**
 * @tc.name: CalculateStartCachedCount002
 * @tc.desc: Test GridScrollWithOptionsLayoutAlgorithm CalculateStartCachedCount
 * @tc.type: FUNC
 */
HWTEST_F(GridTestThreeNg, CalculateStartCachedCount002, TestSize.Level1)
{
    GridLayoutInfo gridLayoutInfo;
    gridLayoutInfo.crossCount_ = 2;
    gridLayoutInfo.startIndex_ = 8;
    gridLayoutInfo.startMainLineIndex_ = 4;
    RefPtr<GridScrollWithOptionsLayoutAlgorithm> layout =
        AceType::MakeRefPtr<GridScrollWithOptionsLayoutAlgorithm>(gridLayoutInfo);
    ASSERT_NE(layout, nullptr);
    GridLayoutOptions options;
    options.irregularIndexes.insert(3);
    options.getSizeByIndex = [](int32_t index) {
        GridItemSize size;
        return size;
    };
    auto result = layout->CalculateStartCachedCount(options, 2);
    EXPECT_EQ(result, 4);
}

/**
 * @tc.name: CalculateStartCachedCount003
 * @tc.desc: Test GridScrollWithOptionsLayoutAlgorithm CalculateStartCachedCount
 * @tc.type: FUNC
 */
HWTEST_F(GridTestThreeNg, CalculateStartCachedCount003, TestSize.Level1)
{
    GridLayoutInfo gridLayoutInfo;
    gridLayoutInfo.crossCount_ = 2;
    gridLayoutInfo.startIndex_ = 8;
    gridLayoutInfo.startMainLineIndex_ = 4;
    RefPtr<GridScrollWithOptionsLayoutAlgorithm> layout =
        AceType::MakeRefPtr<GridScrollWithOptionsLayoutAlgorithm>(gridLayoutInfo);
    ASSERT_NE(layout, nullptr);
    GridLayoutOptions options;
    options.irregularIndexes = { 7, 8 };
    layout->info_.crossCount_ = 0;
    auto result = layout->CalculateStartCachedCount(options, 2);
    EXPECT_EQ(result, 0);
}

/**
 * @tc.name: CalculateStartCachedCount004
 * @tc.desc: Test GridScrollWithOptionsLayoutAlgorithm CalculateStartCachedCount
 * @tc.type: FUNC
 */
HWTEST_F(GridTestThreeNg, CalculateStartCachedCount004, TestSize.Level1)
{
    GridLayoutInfo gridLayoutInfo;
    gridLayoutInfo.crossCount_ = 2;
    gridLayoutInfo.startIndex_ = 8;
    gridLayoutInfo.startMainLineIndex_ = 4;
    RefPtr<GridScrollWithOptionsLayoutAlgorithm> layout =
        AceType::MakeRefPtr<GridScrollWithOptionsLayoutAlgorithm>(gridLayoutInfo);
    ASSERT_NE(layout, nullptr);
    GridLayoutOptions options;
    options.irregularIndexes = { 7, 9 };
    layout->info_.crossCount_ = 0;
    auto result = layout->CalculateStartCachedCount(options, 2);
    EXPECT_EQ(result, 0);
}

/**
 * @tc.name: CalculateStartCachedCount005
 * @tc.desc: Test GridScrollWithOptionsLayoutAlgorithm CalculateStartCachedCount
 * @tc.type: FUNC
 */
HWTEST_F(GridTestThreeNg, CalculateStartCachedCount005, TestSize.Level1)
{
    GridLayoutInfo gridLayoutInfo;
    gridLayoutInfo.crossCount_ = 2;
    gridLayoutInfo.startIndex_ = 8;
    gridLayoutInfo.startMainLineIndex_ = 4;
    RefPtr<GridScrollWithOptionsLayoutAlgorithm> layout =
        AceType::MakeRefPtr<GridScrollWithOptionsLayoutAlgorithm>(gridLayoutInfo);
    ASSERT_NE(layout, nullptr);
    GridLayoutOptions options;
    options.irregularIndexes = { 7, 9 };
    layout->info_.crossCount_ = 0;
    auto result = layout->CalculateStartCachedCount(options, 2);
    EXPECT_EQ(result, 0);
}

/**
 * @tc.name: CalculateStartCachedCount006
 * @tc.desc: Test GridScrollWithOptionsLayoutAlgorithm CalculateStartCachedCount
 * @tc.type: FUNC
 */
HWTEST_F(GridTestThreeNg, CalculateStartCachedCount006, TestSize.Level1)
{
    GridLayoutInfo gridLayoutInfo;
    gridLayoutInfo.crossCount_ = 0;
    gridLayoutInfo.startIndex_ = 8;
    gridLayoutInfo.startMainLineIndex_ = 4;
    RefPtr<GridScrollWithOptionsLayoutAlgorithm> layout =
        AceType::MakeRefPtr<GridScrollWithOptionsLayoutAlgorithm>(gridLayoutInfo);
    ASSERT_NE(layout, nullptr);
    GridLayoutOptions options;
    options.irregularIndexes = { 7, 9 };
    auto result = layout->CalculateStartCachedCount(options, 2);
    EXPECT_EQ(result, 0);
}

/**
 * @tc.name: CalculateStartCachedCount007
 * @tc.desc: Test GridScrollWithOptionsLayoutAlgorithm CalculateStartCachedCount
 * @tc.type: FUNC
 */
HWTEST_F(GridTestThreeNg, CalculateStartCachedCount007, TestSize.Level1)
{
    GridLayoutInfo gridLayoutInfo;
    gridLayoutInfo.crossCount_ = 0;
    gridLayoutInfo.startIndex_ = 8;
    gridLayoutInfo.startMainLineIndex_ = 4;
    RefPtr<GridScrollWithOptionsLayoutAlgorithm> layout =
        AceType::MakeRefPtr<GridScrollWithOptionsLayoutAlgorithm>(gridLayoutInfo);
    ASSERT_NE(layout, nullptr);
    GridLayoutOptions options;
    options.irregularIndexes = { 6, 7, 9 };
    auto result = layout->CalculateStartCachedCount(options, 2);
    EXPECT_EQ(result, 0);
}

/**
 * @tc.name: CalculateStartCachedCount008
 * @tc.desc: Test GridScrollWithOptionsLayoutAlgorithm CalculateStartCachedCount
 * @tc.type: FUNC
 */
HWTEST_F(GridTestThreeNg, CalculateStartCachedCount008, TestSize.Level1)
{
    GridLayoutInfo gridLayoutInfo;
    gridLayoutInfo.crossCount_ = 2;
    gridLayoutInfo.startIndex_ = 8;
    gridLayoutInfo.startMainLineIndex_ = 4;
    RefPtr<GridScrollWithOptionsLayoutAlgorithm> layout =
        AceType::MakeRefPtr<GridScrollWithOptionsLayoutAlgorithm>(gridLayoutInfo);
    ASSERT_NE(layout, nullptr);
    GridLayoutOptions options;
    options.irregularIndexes = { 7, 6 };
    auto result = layout->CalculateStartCachedCount(options, 2);
    EXPECT_EQ(result, 4);
}

/**
 * @tc.name: CalculateStartCachedCount009
 * @tc.desc: Test GridScrollWithOptionsLayoutAlgorithm CalculateStartCachedCount
 * @tc.type: FUNC
 */
HWTEST_F(GridTestThreeNg, CalculateStartCachedCount009, TestSize.Level1)
{
    GridLayoutInfo gridLayoutInfo;
    gridLayoutInfo.crossCount_ = 2;
    gridLayoutInfo.startIndex_ = 8;
    gridLayoutInfo.startMainLineIndex_ = 4;
    RefPtr<GridScrollWithOptionsLayoutAlgorithm> layout =
        AceType::MakeRefPtr<GridScrollWithOptionsLayoutAlgorithm>(gridLayoutInfo);
    ASSERT_NE(layout, nullptr);
    GridLayoutOptions options;
    options.irregularIndexes = { 1, 2, 3, 4, 5, 6, 7 };
    auto result = layout->CalculateStartCachedCount(options, 2);
    EXPECT_EQ(result, 4);
}
} // namespace OHOS::Ace::NG