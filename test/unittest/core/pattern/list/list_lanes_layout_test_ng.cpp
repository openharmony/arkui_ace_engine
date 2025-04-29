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

#include "core/components_ng/pattern/list/list_lanes_layout_algorithm.h"
#include "core/components_ng/pattern/list/list_pattern.h"

namespace OHOS::Ace::NG {
using namespace testing;
using namespace testing::ext;

class ListLanesLayoutTestNg : public TestNG {
public:
};

/**
 * @tc.name: LayoutALineForward001
 * @tc.desc: Test ListLanesLayoutAlgorithm LayoutALineForward
 * @tc.type: FUNC
 */
HWTEST_F(ListLanesLayoutTestNg, LayoutALineForward001, TestSize.Level1)
{
    RefPtr<ListPattern> listPattern = AceType::MakeRefPtr<ListPattern>();
    auto frameNode = FrameNode::CreateFrameNode(V2::LIST_ITEM_GROUP_ETS_TAG, 2, listPattern);
    ASSERT_NE(frameNode, nullptr);
    RefPtr<ListLayoutProperty> listLayoutProperty = AceType::MakeRefPtr<ListLayoutProperty>();
    frameNode->layoutProperty_ = listLayoutProperty;
    listPattern->frameNode_ = frameNode;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(geometryNode, nullptr);
    GeometryProperty geometryProperty;
    geometryNode->frame_ = geometryProperty;
    LayoutWrapperNode layoutWrapper(frameNode, geometryNode, listLayoutProperty);
    int32_t currentIndex = 2;
    float endPos = 2.0f;
    RefPtr<ListLanesLayoutAlgorithm> listLanesLayoutAlgorithm = AceType::MakeRefPtr<ListLanesLayoutAlgorithm>();
    std::optional<std::pair<int32_t, ListItemInfo>> firstItemInfo;
    ListItemInfo itemInfo = { 1, 0.0f, 100.0f, false };
    firstItemInfo = std::make_pair(3, itemInfo);
    listLanesLayoutAlgorithm->firstItemInfo_ = firstItemInfo;
    auto result = listLanesLayoutAlgorithm->LayoutALineForward(&layoutWrapper, currentIndex, 2.0f, endPos);
    EXPECT_EQ(result, 1);
}

/**
 * @tc.name: LayoutALineForward002
 * @tc.desc: Test ListLanesLayoutAlgorithm LayoutALineForward
 * @tc.type: FUNC
 */
HWTEST_F(ListLanesLayoutTestNg, LayoutALineForward002, TestSize.Level1)
{
    RefPtr<ListPattern> listPattern = AceType::MakeRefPtr<ListPattern>();
    auto frameNode = FrameNode::CreateFrameNode(V2::LIST_ITEM_GROUP_ETS_TAG, 2, listPattern);
    ASSERT_NE(frameNode, nullptr);
    RefPtr<ListLayoutProperty> listLayoutProperty = AceType::MakeRefPtr<ListLayoutProperty>();
    frameNode->layoutProperty_ = listLayoutProperty;
    listPattern->frameNode_ = frameNode;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(geometryNode, nullptr);
    GeometryProperty geometryProperty;
    geometryNode->frame_ = geometryProperty;
    LayoutWrapperNode layoutWrapper(frameNode, geometryNode, listLayoutProperty);
    int32_t currentIndex = 2;
    float endPos = 2.0f;
    RefPtr<ListLanesLayoutAlgorithm> listLanesLayoutAlgorithm = AceType::MakeRefPtr<ListLanesLayoutAlgorithm>();
    std::optional<std::pair<int32_t, ListItemInfo>> firstItemInfo;
    ListItemInfo itemInfo = { 1, 0.0f, 100.0f, false };
    firstItemInfo = std::make_pair(0, itemInfo);
    listLanesLayoutAlgorithm->firstItemInfo_ = firstItemInfo;
    listLanesLayoutAlgorithm->LayoutALineForward(&layoutWrapper, currentIndex, 2.0f, endPos);
    EXPECT_FALSE(listLanesLayoutAlgorithm->firstItemInfo_.has_value());
}

/**
 * @tc.name: LayoutALineForward003
 * @tc.desc: Test ListLanesLayoutAlgorithm LayoutALineForward
 * @tc.type: FUNC
 */
HWTEST_F(ListLanesLayoutTestNg, LayoutALineForward003, TestSize.Level1)
{
    RefPtr<ListPattern> listPattern = AceType::MakeRefPtr<ListPattern>();
    auto frameNode = FrameNode::CreateFrameNode(V2::LIST_ITEM_GROUP_ETS_TAG, 2, listPattern);
    ASSERT_NE(frameNode, nullptr);
    RefPtr<ListLayoutProperty> listLayoutProperty = AceType::MakeRefPtr<ListLayoutProperty>();
    frameNode->layoutProperty_ = listLayoutProperty;
    listPattern->frameNode_ = frameNode;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(geometryNode, nullptr);
    GeometryProperty geometryProperty;
    geometryNode->frame_ = geometryProperty;
    LayoutWrapperNode layoutWrapper(frameNode, geometryNode, listLayoutProperty);
    int32_t currentIndex = 2;
    float endPos = 2.0f;
    RefPtr<ListLanesLayoutAlgorithm> listLanesLayoutAlgorithm = AceType::MakeRefPtr<ListLanesLayoutAlgorithm>();
    listLanesLayoutAlgorithm->firstItemInfo_ = std::nullopt;
    auto result = listLanesLayoutAlgorithm->LayoutALineForward(&layoutWrapper, currentIndex, 2.0f, endPos);
    EXPECT_EQ(result, 0);
}

/**
 * @tc.name: LayoutALineForward004
 * @tc.desc: Test ListLanesLayoutAlgorithm LayoutALineForward
 * @tc.type: FUNC
 */
HWTEST_F(ListLanesLayoutTestNg, LayoutALineForward004, TestSize.Level1)
{
    RefPtr<ListPattern> listPattern = AceType::MakeRefPtr<ListPattern>();
    auto frameNode = FrameNode::CreateFrameNode(V2::LIST_ITEM_GROUP_ETS_TAG, 2, listPattern);
    ASSERT_NE(frameNode, nullptr);
    frameNode->tag_ = V2::LIST_ITEM_GROUP_ETS_TAG;
    RefPtr<ListLayoutProperty> listLayoutProperty = AceType::MakeRefPtr<ListLayoutProperty>();
    frameNode->layoutProperty_ = listLayoutProperty;
    listPattern->frameNode_ = frameNode;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(geometryNode, nullptr);
    GeometryProperty geometryProperty;
    geometryNode->frame_ = geometryProperty;
    LayoutWrapperNode layoutWrapper(frameNode, geometryNode, listLayoutProperty);
    layoutWrapper.hostNode_ = frameNode;
    int32_t currentIndex = 2;
    float endPos = 2.0f;
    RefPtr<ListLanesLayoutAlgorithm> listLanesLayoutAlgorithm = AceType::MakeRefPtr<ListLanesLayoutAlgorithm>();
    listLanesLayoutAlgorithm->firstItemInfo_ = std::nullopt;
    listLanesLayoutAlgorithm->SetLanes(2);
    listLanesLayoutAlgorithm->totalItemCount_ = 5;
    auto result = listLanesLayoutAlgorithm->LayoutALineForward(&layoutWrapper, currentIndex, 2.0f, endPos);
    EXPECT_EQ(result, 0);
}

/**
 * @tc.name: LayoutALineForward005
 * @tc.desc: Test ListLanesLayoutAlgorithm LayoutALineForward
 * @tc.type: FUNC
 */
HWTEST_F(ListLanesLayoutTestNg, LayoutALineForward005, TestSize.Level1)
{
    RefPtr<ListPattern> listPattern = AceType::MakeRefPtr<ListPattern>();
    auto frameNode = FrameNode::CreateFrameNode(V2::LIST_ITEM_GROUP_ETS_TAG, 2, listPattern);
    ASSERT_NE(frameNode, nullptr);
    frameNode->tag_ = V2::LIST_ITEM_GROUP_ETS_TAG;
    RefPtr<ListLayoutProperty> listLayoutProperty = AceType::MakeRefPtr<ListLayoutProperty>();
    frameNode->layoutProperty_ = listLayoutProperty;
    listPattern->frameNode_ = frameNode;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(geometryNode, nullptr);
    GeometryProperty geometryProperty;
    geometryNode->frame_ = geometryProperty;
    LayoutWrapperNode layoutWrapper(frameNode, geometryNode, listLayoutProperty);
    layoutWrapper.hostNode_ = frameNode;
    layoutWrapper.currentChildCount_ = 5;
    std::unordered_map<int32_t, RefPtr<LayoutWrapperNode>> childrenMap;
    childrenMap[3] = AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, listLayoutProperty);
    layoutWrapper.childrenMap_ = childrenMap;
    int32_t currentIndex = 2;
    float endPos = 2.0f;
    RefPtr<ListLanesLayoutAlgorithm> listLanesLayoutAlgorithm = AceType::MakeRefPtr<ListLanesLayoutAlgorithm>();
    listLanesLayoutAlgorithm->firstItemInfo_ = std::nullopt;
    listLanesLayoutAlgorithm->SetLanes(2);
    listLanesLayoutAlgorithm->totalItemCount_ = 5;
    listLanesLayoutAlgorithm->LayoutALineForward(&layoutWrapper, currentIndex, 2.0f, endPos);
    EXPECT_FALSE(layoutWrapper.isActive_);
}

/**
 * @tc.name: LayoutALineBackward001
 * @tc.desc: Test ListLanesLayoutAlgorithm LayoutALineBackward
 * @tc.type: FUNC
 */
HWTEST_F(ListLanesLayoutTestNg, LayoutALineBackward001, TestSize.Level1)
{
    RefPtr<ListPattern> listPattern = AceType::MakeRefPtr<ListPattern>();
    auto frameNode = FrameNode::CreateFrameNode(V2::LIST_ITEM_GROUP_ETS_TAG, 2, listPattern);
    ASSERT_NE(frameNode, nullptr);
    RefPtr<ListLayoutProperty> listLayoutProperty = AceType::MakeRefPtr<ListLayoutProperty>();
    frameNode->layoutProperty_ = listLayoutProperty;
    listPattern->frameNode_ = frameNode;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(geometryNode, nullptr);
    GeometryProperty geometryProperty;
    geometryNode->frame_ = geometryProperty;
    LayoutWrapperNode layoutWrapper(frameNode, geometryNode, listLayoutProperty);
    int32_t currentIndex = 2;
    float endPos = 2.0f;
    RefPtr<ListLanesLayoutAlgorithm> listLanesLayoutAlgorithm = AceType::MakeRefPtr<ListLanesLayoutAlgorithm>();
    std::optional<std::pair<int32_t, ListItemInfo>> firstItemInfo;
    ListItemInfo itemInfo = { 1, 0.0f, 100.0f, false };
    firstItemInfo = std::make_pair(1, itemInfo);
    listLanesLayoutAlgorithm->firstItemInfo_ = firstItemInfo;
    auto result = listLanesLayoutAlgorithm->LayoutALineBackward(&layoutWrapper, currentIndex, 2.0f, endPos);
    EXPECT_EQ(result, 1);
}

/**
 * @tc.name: LayoutALineBackward002
 * @tc.desc: Test ListLanesLayoutAlgorithm LayoutALineBackward
 * @tc.type: FUNC
 */
HWTEST_F(ListLanesLayoutTestNg, LayoutALineBackward002, TestSize.Level1)
{
    RefPtr<ListPattern> listPattern = AceType::MakeRefPtr<ListPattern>();
    auto frameNode = FrameNode::CreateFrameNode(V2::LIST_ITEM_GROUP_ETS_TAG, 2, listPattern);
    ASSERT_NE(frameNode, nullptr);
    RefPtr<ListLayoutProperty> listLayoutProperty = AceType::MakeRefPtr<ListLayoutProperty>();
    frameNode->layoutProperty_ = listLayoutProperty;
    listPattern->frameNode_ = frameNode;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(geometryNode, nullptr);
    GeometryProperty geometryProperty;
    geometryNode->frame_ = geometryProperty;
    LayoutWrapperNode layoutWrapper(frameNode, geometryNode, listLayoutProperty);
    int32_t currentIndex = 2;
    float endPos = 2.0f;
    RefPtr<ListLanesLayoutAlgorithm> listLanesLayoutAlgorithm = AceType::MakeRefPtr<ListLanesLayoutAlgorithm>();
    std::optional<std::pair<int32_t, ListItemInfo>> firstItemInfo;
    ListItemInfo itemInfo = { 1, 0.0f, 100.0f, false };
    firstItemInfo = std::make_pair(0, itemInfo);
    listLanesLayoutAlgorithm->firstItemInfo_ = firstItemInfo;
    listLanesLayoutAlgorithm->LayoutALineBackward(&layoutWrapper, currentIndex, 2.0f, endPos);
    EXPECT_FALSE(listLanesLayoutAlgorithm->firstItemInfo_.has_value());
}

/**
 * @tc.name: LayoutALineBackward003
 * @tc.desc: Test ListLanesLayoutAlgorithm LayoutALineBackward
 * @tc.type: FUNC
 */
HWTEST_F(ListLanesLayoutTestNg, LayoutALineBackward003, TestSize.Level1)
{
    RefPtr<ListPattern> listPattern = AceType::MakeRefPtr<ListPattern>();
    auto frameNode = FrameNode::CreateFrameNode(V2::LIST_ITEM_GROUP_ETS_TAG, 2, listPattern);
    ASSERT_NE(frameNode, nullptr);
    RefPtr<ListLayoutProperty> listLayoutProperty = AceType::MakeRefPtr<ListLayoutProperty>();
    frameNode->layoutProperty_ = listLayoutProperty;
    listPattern->frameNode_ = frameNode;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(geometryNode, nullptr);
    GeometryProperty geometryProperty;
    geometryNode->frame_ = geometryProperty;
    LayoutWrapperNode layoutWrapper(frameNode, geometryNode, listLayoutProperty);
    int32_t currentIndex = 2;
    float endPos = 2.0f;
    RefPtr<ListLanesLayoutAlgorithm> listLanesLayoutAlgorithm = AceType::MakeRefPtr<ListLanesLayoutAlgorithm>();
    listLanesLayoutAlgorithm->firstItemInfo_ = std::nullopt;
    auto result = listLanesLayoutAlgorithm->LayoutALineBackward(&layoutWrapper, currentIndex, 2.0f, endPos);
    EXPECT_EQ(result, 0);
}

/**
 * @tc.name: LayoutALineBackward004
 * @tc.desc: Test ListLanesLayoutAlgorithm LayoutALineBackward
 * @tc.type: FUNC
 */
HWTEST_F(ListLanesLayoutTestNg, LayoutALineBackward004, TestSize.Level1)
{
    RefPtr<ListPattern> listPattern = AceType::MakeRefPtr<ListPattern>();
    auto frameNode = FrameNode::CreateFrameNode(V2::LIST_ITEM_GROUP_ETS_TAG, 2, listPattern);
    ASSERT_NE(frameNode, nullptr);
    RefPtr<ListLayoutProperty> listLayoutProperty = AceType::MakeRefPtr<ListLayoutProperty>();
    frameNode->layoutProperty_ = listLayoutProperty;
    listPattern->frameNode_ = frameNode;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(geometryNode, nullptr);
    GeometryProperty geometryProperty;
    geometryNode->frame_ = geometryProperty;
    LayoutWrapperNode layoutWrapper(frameNode, geometryNode, listLayoutProperty);
    int32_t currentIndex = 5;
    float endPos = 2.0f;
    RefPtr<ListLanesLayoutAlgorithm> listLanesLayoutAlgorithm = AceType::MakeRefPtr<ListLanesLayoutAlgorithm>();
    listLanesLayoutAlgorithm->firstItemInfo_ = std::nullopt;
    listLanesLayoutAlgorithm->SetLanes(2);
    listLanesLayoutAlgorithm->totalItemCount_ = 3;
    auto result = listLanesLayoutAlgorithm->LayoutALineBackward(&layoutWrapper, currentIndex, 2.0f, endPos);
    EXPECT_EQ(result, 0);
}

/**
 * @tc.name: LayoutALineBackward005
 * @tc.desc: Test ListLanesLayoutAlgorithm LayoutALineBackward
 * @tc.type: FUNC
 */
HWTEST_F(ListLanesLayoutTestNg, LayoutALineBackward005, TestSize.Level1)
{
    RefPtr<ListPattern> listPattern = AceType::MakeRefPtr<ListPattern>();
    auto frameNode = FrameNode::CreateFrameNode(V2::LIST_ITEM_GROUP_ETS_TAG, 2, listPattern);
    ASSERT_NE(frameNode, nullptr);
    RefPtr<ListLayoutProperty> listLayoutProperty = AceType::MakeRefPtr<ListLayoutProperty>();
    frameNode->layoutProperty_ = listLayoutProperty;
    listPattern->frameNode_ = frameNode;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(geometryNode, nullptr);
    GeometryProperty geometryProperty;
    geometryNode->frame_ = geometryProperty;
    LayoutWrapperNode layoutWrapper(frameNode, geometryNode, listLayoutProperty);
    int32_t currentIndex = 4;
    float endPos = 2.0f;
    RefPtr<ListLanesLayoutAlgorithm> listLanesLayoutAlgorithm = AceType::MakeRefPtr<ListLanesLayoutAlgorithm>();
    listLanesLayoutAlgorithm->firstItemInfo_ = std::nullopt;
    listLanesLayoutAlgorithm->SetLanes(2);
    listLanesLayoutAlgorithm->totalItemCount_ = 3;
    auto result = listLanesLayoutAlgorithm->LayoutALineBackward(&layoutWrapper, currentIndex, 2.0f, endPos);
    EXPECT_EQ(result, 0);
}

/**
 * @tc.name: CalculateLanesParam001
 * @tc.desc: Test ListLanesLayoutAlgorithm CalculateLanesParam
 * @tc.type: FUNC
 */
HWTEST_F(ListLanesLayoutTestNg, CalculateLanesParam001, TestSize.Level1)
{
    RefPtr<ListLanesLayoutAlgorithm> listLanesLayoutAlgorithm = AceType::MakeRefPtr<ListLanesLayoutAlgorithm>();
    std::optional<float> minLaneLength = 2.0f;
    std::optional<float> maxLaneLength = 8.0f;
    std::optional<float> crossSizeOptional = 2.0f;
    auto result =
        listLanesLayoutAlgorithm->CalculateLanesParam(minLaneLength, maxLaneLength, 0, crossSizeOptional, 2.0f);
    EXPECT_EQ(result, 1);
}

/**
 * @tc.name: CalculateLanesParam002
 * @tc.desc: Test ListLanesLayoutAlgorithm CalculateLanesParam
 * @tc.type: FUNC
 */
HWTEST_F(ListLanesLayoutTestNg, CalculateLanesParam002, TestSize.Level1)
{
    RefPtr<ListLanesLayoutAlgorithm> listLanesLayoutAlgorithm = AceType::MakeRefPtr<ListLanesLayoutAlgorithm>();
    std::optional<float> minLaneLength = 2.0f;
    std::optional<float> maxLaneLength = 8.0f;
    std::optional<float> crossSizeOptional = 2.0f;
    auto result =
        listLanesLayoutAlgorithm->CalculateLanesParam(minLaneLength, maxLaneLength, 2, crossSizeOptional, 2.0f);
    EXPECT_EQ(result, 1);
}

/**
 * @tc.name: MeasureAndGetChildHeight001
 * @tc.desc: Test ListLanesLayoutAlgorithm MeasureAndGetChildHeight
 * @tc.type: FUNC
 */
HWTEST_F(ListLanesLayoutTestNg, MeasureAndGetChildHeight001, TestSize.Level1)
{
    RefPtr<ListPattern> listPattern = AceType::MakeRefPtr<ListPattern>();
    RefPtr<ListLanesLayoutAlgorithm> listLanesLayoutAlgorithm = AceType::MakeRefPtr<ListLanesLayoutAlgorithm>();
    RefPtr<ListLayoutProperty> listLayoutProperty = AceType::MakeRefPtr<ListLayoutProperty>();
    auto frameNode = FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, 2, listPattern);
    ASSERT_NE(frameNode, nullptr);
    frameNode->layoutProperty_ = listLayoutProperty;
    listPattern->frameNode_ = frameNode;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(geometryNode, nullptr);
    GeometryProperty geometryProperty;
    RectT rect(20.0f, 20.0f, 80.0f, 80.0f);
    geometryProperty.rect_ = rect;
    geometryNode->frame_ = geometryProperty;
    LayoutWrapperNode layoutWrapper(frameNode, geometryNode, listLayoutProperty);
    layoutWrapper.geometryNode_ = geometryNode;
    layoutWrapper.currentChildCount_ = 2;
    listLanesLayoutAlgorithm->isStackFromEnd_ = false;
    listLanesLayoutAlgorithm->itemStartIndex_ = 2;
    auto result = listLanesLayoutAlgorithm->MeasureAndGetChildHeight(&layoutWrapper, 4, true);
    EXPECT_EQ(result, 0.0f);
}

/**
 * @tc.name: MeasureAndGetChildHeight002
 * @tc.desc: Test ListLanesLayoutAlgorithm MeasureAndGetChildHeight
 * @tc.type: FUNC
 */
HWTEST_F(ListLanesLayoutTestNg, MeasureAndGetChildHeight002, TestSize.Level1)
{
    RefPtr<ListPattern> listPattern = AceType::MakeRefPtr<ListPattern>();
    RefPtr<ListLanesLayoutAlgorithm> listLanesLayoutAlgorithm = AceType::MakeRefPtr<ListLanesLayoutAlgorithm>();
    RefPtr<ListLayoutProperty> listLayoutProperty = AceType::MakeRefPtr<ListLayoutProperty>();
    auto frameNode = FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, 2, listPattern);
    ASSERT_NE(frameNode, nullptr);
    frameNode->layoutProperty_ = listLayoutProperty;
    listPattern->frameNode_ = frameNode;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(geometryNode, nullptr);
    GeometryProperty geometryProperty;
    RectT rect(20.0f, 20.0f, 80.0f, 80.0f);
    geometryProperty.rect_ = rect;
    geometryNode->frame_ = geometryProperty;
    RefPtr<LayoutWrapperNode> layoutWrapperNode =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, listLayoutProperty);
    layoutWrapperNode->SetActive();
    layoutWrapperNode->geometryNode_ = geometryNode;
    layoutWrapperNode->geometryNode_->frame_.rect_ = rect;
    layoutWrapperNode->hostNode_ = frameNode;
    layoutWrapperNode->hostNode_.Upgrade()->tag_ = V2::LIST_ITEM_GROUP_ETS_TAG;
    RefPtr<LayoutAlgorithmWrapper> layoutAlgorithmWrapper =
        AceType::MakeRefPtr<LayoutAlgorithmWrapper>(listLanesLayoutAlgorithm);
    layoutWrapperNode->layoutAlgorithm_ = layoutAlgorithmWrapper;
    LayoutWrapperNode layoutWrapper(frameNode, geometryNode, listLayoutProperty);
    layoutWrapper.geometryNode_ = geometryNode;
    layoutWrapper.currentChildCount_ = 8;
    layoutWrapper.childrenMap_[6] = layoutWrapperNode;
    listLanesLayoutAlgorithm->isStackFromEnd_ = false;
    listLanesLayoutAlgorithm->itemStartIndex_ = 2;
    auto result = listLanesLayoutAlgorithm->MeasureAndGetChildHeight(&layoutWrapper, 4, true);
    EXPECT_NE(result, 0.0f);
}

/**
 * @tc.name: MeasureAndGetChildHeight003
 * @tc.desc: Test ListLanesLayoutAlgorithm MeasureAndGetChildHeight
 * @tc.type: FUNC
 */
HWTEST_F(ListLanesLayoutTestNg, MeasureAndGetChildHeight003, TestSize.Level1)
{
    RefPtr<ListPattern> listPattern = AceType::MakeRefPtr<ListPattern>();
    RefPtr<ListLanesLayoutAlgorithm> listLanesLayoutAlgorithm = AceType::MakeRefPtr<ListLanesLayoutAlgorithm>();
    RefPtr<ListLayoutProperty> listLayoutProperty = AceType::MakeRefPtr<ListLayoutProperty>();
    auto frameNode = FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, 2, listPattern);
    ASSERT_NE(frameNode, nullptr);
    frameNode->layoutProperty_ = listLayoutProperty;
    listPattern->frameNode_ = frameNode;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(geometryNode, nullptr);
    GeometryProperty geometryProperty;
    RectT rect(20.0f, 20.0f, 80.0f, 60.0f);
    geometryProperty.rect_ = rect;
    geometryNode->frame_ = geometryProperty;
    RefPtr<LayoutWrapperNode> layoutWrapperNode =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, listLayoutProperty);
    layoutWrapperNode->SetActive();
    layoutWrapperNode->geometryNode_ = geometryNode;
    layoutWrapperNode->hostNode_ = frameNode;
    layoutWrapperNode->hostNode_.Upgrade()->tag_ = V2::LIST_ITEM_GROUP_COMPONENT_TAG;
    RefPtr<LayoutAlgorithmWrapper> layoutAlgorithmWrapper =
        AceType::MakeRefPtr<LayoutAlgorithmWrapper>(listLanesLayoutAlgorithm);
    layoutWrapperNode->layoutAlgorithm_ = layoutAlgorithmWrapper;
    LayoutWrapperNode layoutWrapper(frameNode, geometryNode, listLayoutProperty);
    layoutWrapper.geometryNode_ = geometryNode;
    layoutWrapper.currentChildCount_ = 5;
    layoutWrapper.childrenMap_[4] = layoutWrapperNode;
    RefPtr<ListChildrenMainSize> listChildrenMainSize = AceType::MakeRefPtr<ListChildrenMainSize>();
    RefPtr<ListPositionMap> listPositionMap = AceType::MakeRefPtr<ListPositionMap>();
    ListPositionInfo positionInfo { 20.0f, 4.0f, true };
    ListPositionInfo info { 30.0f, 4.0f, true };
    listPositionMap->posMap_[0] = info;
    listPositionMap->posMap_[1] = info;
    listPositionMap->posMap_[2] = info;
    listPositionMap->posMap_[3] = info;
    listPositionMap->posMap_[4] = positionInfo;
    listPositionMap->posMap_[5] = positionInfo;
    listLanesLayoutAlgorithm->posMap_ = listPositionMap;
    listLanesLayoutAlgorithm->posMap_->totalItemCount_ = 9;
    listLanesLayoutAlgorithm->posMap_->totalHeight_ = 100.0f;
    listLanesLayoutAlgorithm->posMap_->footerSize_ = 10.0f;
    listLanesLayoutAlgorithm->posMap_->space_ = 5.0f;
    listLanesLayoutAlgorithm->childrenSize_ = listChildrenMainSize;
    listLanesLayoutAlgorithm->lanes_ = 2;
    listLanesLayoutAlgorithm->isStackFromEnd_ = false;
    listLanesLayoutAlgorithm->itemStartIndex_ = 0;
    auto result = listLanesLayoutAlgorithm->MeasureAndGetChildHeight(&layoutWrapper, 4, true);
    EXPECT_EQ(result, 0.0f);
}

/**
 * @tc.name: CalculateLaneCrossOffset001
 * @tc.desc: Test ListLanesLayoutAlgorithm CalculateLaneCrossOffset
 * @tc.type: FUNC
 */
HWTEST_F(ListLanesLayoutTestNg, CalculateLaneCrossOffset001, TestSize.Level1)
{
    RefPtr<ListLanesLayoutAlgorithm> listLanesLayoutAlgorithm = AceType::MakeRefPtr<ListLanesLayoutAlgorithm>();
    listLanesLayoutAlgorithm->lanes_ = 0;
    auto result = listLanesLayoutAlgorithm->CalculateLaneCrossOffset(2.0f, 4.0f, true);
    EXPECT_EQ(result, 0.0f);
}

/**
 * @tc.name: LayoutCachedALineForward001
 * @tc.desc: Test ListLanesLayoutAlgorithm LayoutCachedALineForward
 * @tc.type: FUNC
 */
HWTEST_F(ListLanesLayoutTestNg, LayoutCachedALineForward001, TestSize.Level1)
{
    RefPtr<ListPattern> listPattern = AceType::MakeRefPtr<ListPattern>();
    RefPtr<ListLanesLayoutAlgorithm> listLanesLayoutAlgorithm = AceType::MakeRefPtr<ListLanesLayoutAlgorithm>();
    RefPtr<ListLayoutProperty> listLayoutProperty = AceType::MakeRefPtr<ListLayoutProperty>();
    auto frameNode = FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, 2, listPattern);
    ASSERT_NE(frameNode, nullptr);
    frameNode->layoutProperty_ = listLayoutProperty;
    listPattern->frameNode_ = frameNode;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(geometryNode, nullptr);
    GeometryProperty geometryProperty;
    RectT rect(20.0f, 20.0f, 80.0f, 80.0f);
    geometryProperty.rect_ = rect;
    geometryNode->frame_ = geometryProperty;
    LayoutWrapperNode layoutWrapper(frameNode, geometryNode, listLayoutProperty);
    layoutWrapper.geometryNode_ = geometryNode;
    layoutWrapper.currentChildCount_ = 2;
    listLanesLayoutAlgorithm->isStackFromEnd_ = false;
    listLanesLayoutAlgorithm->itemStartIndex_ = 2;
    listLanesLayoutAlgorithm->totalItemCount_ = 5;
    listLanesLayoutAlgorithm->lanes_ = 3;
    int32_t index = 2;
    float startPos = 2.0f;
    auto result = listLanesLayoutAlgorithm->LayoutCachedALineForward(&layoutWrapper, index, startPos, 2.0f);
    auto it = result.begin();
    EXPECT_EQ(index, 3);
    EXPECT_EQ(startPos, 2.0f);
    EXPECT_EQ(*it, 2);
}

/**
 * @tc.name: LayoutCachedALineBackward001
 * @tc.desc: Test ListLanesLayoutAlgorithm LayoutCachedALineBackward
 * @tc.type: FUNC
 */
HWTEST_F(ListLanesLayoutTestNg, LayoutCachedALineBackward001, TestSize.Level1)
{
    RefPtr<ListPattern> listPattern = AceType::MakeRefPtr<ListPattern>();
    RefPtr<ListLanesLayoutAlgorithm> listLanesLayoutAlgorithm = AceType::MakeRefPtr<ListLanesLayoutAlgorithm>();
    RefPtr<ListLayoutProperty> listLayoutProperty = AceType::MakeRefPtr<ListLayoutProperty>();
    auto frameNode = FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, 2, listPattern);
    ASSERT_NE(frameNode, nullptr);
    frameNode->layoutProperty_ = listLayoutProperty;
    listPattern->frameNode_ = frameNode;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(geometryNode, nullptr);
    GeometryProperty geometryProperty;
    RectT rect(20.0f, 20.0f, 80.0f, 80.0f);
    geometryProperty.rect_ = rect;
    geometryNode->frame_ = geometryProperty;
    LayoutWrapperNode layoutWrapper(frameNode, geometryNode, listLayoutProperty);
    layoutWrapper.geometryNode_ = geometryNode;
    layoutWrapper.currentChildCount_ = 2;
    listLanesLayoutAlgorithm->isStackFromEnd_ = false;
    listLanesLayoutAlgorithm->itemStartIndex_ = 2;
    listLanesLayoutAlgorithm->totalItemCount_ = 5;
    listLanesLayoutAlgorithm->lanes_ = 3;
    int32_t index = 4;
    float endPos = 2.0f;
    auto result = listLanesLayoutAlgorithm->LayoutCachedALineBackward(&layoutWrapper, index, endPos, 2.0f);
    auto it = result.begin();
    EXPECT_EQ(index, 3);
    EXPECT_EQ(endPos, 2.0f);
    EXPECT_EQ(*it, 4);
}
} // namespace OHOS::Ace::NG