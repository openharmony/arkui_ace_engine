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
#include "core/components_ng/pattern/list/list_children_main_size.h"
#include "core/components_ng/pattern/list/list_item_group_layout_algorithm.h"
#include "core/components_ng/pattern/list/list_item_pattern.h"
#include "core/components_ng/pattern/list/list_position_map.h"
#include "core/components_v2/inspector/inspector_constants.h"

namespace OHOS::Ace::NG {
using namespace testing;
using namespace testing::ext;

class ListItemGroupAlgorithmTestNg : public TestNG {
public:
};

/**
 * @tc.name: CheckJumpForwardForBigOffset001
 * @tc.desc: Test ListItemGroupLayoutAlgorithm CheckJumpForwardForBigOffset
 * @tc.type: FUNC
 */
HWTEST_F(ListItemGroupAlgorithmTestNg, CheckJumpForwardForBigOffset001, TestSize.Level1)
{
    RefPtr<ListItemGroupLayoutAlgorithm> listItemGroupLayoutAlgorithm =
        AceType::MakeRefPtr<ListItemGroupLayoutAlgorithm>(2, 2, 2);
    listItemGroupLayoutAlgorithm->isNeedCheckOffset_ = true;
    std::vector<float> mainSize;
    mainSize.push_back(2.0f);
    RefPtr<ListChildrenMainSize> childrenSize = AceType::MakeRefPtr<ListChildrenMainSize>(mainSize, 2.0f);
    listItemGroupLayoutAlgorithm->childrenSize_ = childrenSize;
    int32_t startIndex = 2;
    float startPos = 2.0f;
    auto result = listItemGroupLayoutAlgorithm->CheckJumpForwardForBigOffset(startIndex, startPos);
    EXPECT_EQ(startIndex, 2);
    EXPECT_EQ(startPos, 2.0f);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: CheckJumpForwardForBigOffset002
 * @tc.desc: Test ListItemGroupLayoutAlgorithm CheckJumpForwardForBigOffset
 * @tc.type: FUNC
 */
HWTEST_F(ListItemGroupAlgorithmTestNg, CheckJumpForwardForBigOffset002, TestSize.Level1)
{
    RefPtr<ListItemGroupLayoutAlgorithm> listItemGroupLayoutAlgorithm =
        AceType::MakeRefPtr<ListItemGroupLayoutAlgorithm>(2, 2, 2);
    listItemGroupLayoutAlgorithm->isNeedCheckOffset_ = false;
    std::vector<float> mainSize;
    mainSize.push_back(2.0f);
    RefPtr<ListChildrenMainSize> childrenSize = AceType::MakeRefPtr<ListChildrenMainSize>(mainSize, 2.0f);
    listItemGroupLayoutAlgorithm->childrenSize_ = childrenSize;
    int32_t startIndex = 2;
    float startPos = 2.0f;
    auto result = listItemGroupLayoutAlgorithm->CheckJumpForwardForBigOffset(startIndex, startPos);
    EXPECT_EQ(startIndex, 2);
    EXPECT_EQ(startPos, 2.0f);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: CheckJumpForwardForBigOffset003
 * @tc.desc: Test ListItemGroupLayoutAlgorithm CheckJumpForwardForBigOffset
 * @tc.type: FUNC
 */
HWTEST_F(ListItemGroupAlgorithmTestNg, CheckJumpForwardForBigOffset003, TestSize.Level1)
{
    RefPtr<ListItemGroupLayoutAlgorithm> listItemGroupLayoutAlgorithm =
        AceType::MakeRefPtr<ListItemGroupLayoutAlgorithm>(2, 2, 2);
    listItemGroupLayoutAlgorithm->isNeedCheckOffset_ = false;
    int32_t startIndex = 2;
    float startPos = 2.0f;
    auto result = listItemGroupLayoutAlgorithm->CheckJumpForwardForBigOffset(startIndex, startPos);
    EXPECT_EQ(startIndex, 2);
    EXPECT_EQ(startPos, 2.0f);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: CheckJumpForwardForBigOffset004
 * @tc.desc: Test ListItemGroupLayoutAlgorithm CheckJumpForwardForBigOffset
 * @tc.type: FUNC
 */
HWTEST_F(ListItemGroupAlgorithmTestNg, CheckJumpForwardForBigOffset004, TestSize.Level1)
{
    RefPtr<ListItemGroupLayoutAlgorithm> listItemGroupLayoutAlgorithm =
        AceType::MakeRefPtr<ListItemGroupLayoutAlgorithm>(2, 2, 2);
    listItemGroupLayoutAlgorithm->isNeedCheckOffset_ = true;
    int32_t startIndex = 2;
    float startPos = 2.0f;
    auto result = listItemGroupLayoutAlgorithm->CheckJumpForwardForBigOffset(startIndex, startPos);
    EXPECT_EQ(startIndex, 2);
    EXPECT_EQ(startPos, 2.0f);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: CheckJumpForwardForBigOffset005
 * @tc.desc: Test ListItemGroupLayoutAlgorithm CheckJumpForwardForBigOffset
 * @tc.type: FUNC
 */
HWTEST_F(ListItemGroupAlgorithmTestNg, CheckJumpForwardForBigOffset005, TestSize.Level1)
{
    RefPtr<ListItemGroupLayoutAlgorithm> listItemGroupLayoutAlgorithm =
        AceType::MakeRefPtr<ListItemGroupLayoutAlgorithm>(2, 2, 2);
    listItemGroupLayoutAlgorithm->isNeedCheckOffset_ = true;
    listItemGroupLayoutAlgorithm->startPos_ = 4.0f;
    listItemGroupLayoutAlgorithm->endPos_ = 5.0f;
    listItemGroupLayoutAlgorithm->referencePos_ = 1.0f;
    listItemGroupLayoutAlgorithm->groupItemAverageHeight_ = 1.0f;
    listItemGroupLayoutAlgorithm->spaceWidth_ = 1.0f;
    listItemGroupLayoutAlgorithm->totalItemCount_ = 3;
    listItemGroupLayoutAlgorithm->itemPosition_.clear();
    LayoutedItemInfo layoutedItemInfo { 1, 2.0f, 2, 4.0f };
    listItemGroupLayoutAlgorithm->layoutedItemInfo_ = layoutedItemInfo;
    int32_t startIndex = 2;
    float startPos = 1.0f;
    auto result = listItemGroupLayoutAlgorithm->CheckJumpForwardForBigOffset(startIndex, startPos);
    EXPECT_EQ(startIndex, 2);
    EXPECT_EQ(startPos, 1.0f);
    EXPECT_EQ(listItemGroupLayoutAlgorithm->itemPosition_[0].endPos, 0.0f);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: CheckJumpForwardForBigOffset006
 * @tc.desc: Test ListItemGroupLayoutAlgorithm CheckJumpForwardForBigOffset
 * @tc.type: FUNC
 */
HWTEST_F(ListItemGroupAlgorithmTestNg, CheckJumpForwardForBigOffset006, TestSize.Level1)
{
    RefPtr<ListItemGroupLayoutAlgorithm> listItemGroupLayoutAlgorithm =
        AceType::MakeRefPtr<ListItemGroupLayoutAlgorithm>(2, 2, 2);
    listItemGroupLayoutAlgorithm->isNeedCheckOffset_ = true;
    listItemGroupLayoutAlgorithm->startPos_ = 4.0f;
    listItemGroupLayoutAlgorithm->endPos_ = 5.0f;
    listItemGroupLayoutAlgorithm->referencePos_ = 1.0f;
    listItemGroupLayoutAlgorithm->groupItemAverageHeight_ = 1.0f;
    listItemGroupLayoutAlgorithm->spaceWidth_ = 1.0f;
    listItemGroupLayoutAlgorithm->totalItemCount_ = 8;
    listItemGroupLayoutAlgorithm->itemPosition_.clear();
    int32_t startIndex = 2;
    float startPos = 1.0f;
    auto result = listItemGroupLayoutAlgorithm->CheckJumpForwardForBigOffset(startIndex, startPos);
    EXPECT_EQ(startIndex, 4);
    EXPECT_EQ(startPos, 3.0f);
    EXPECT_TRUE(listItemGroupLayoutAlgorithm->itemPosition_.empty());
    EXPECT_FALSE(result);
}

/**
 * @tc.name: CheckJumpForwardForBigOffset007
 * @tc.desc: Test ListItemGroupLayoutAlgorithm CheckJumpForwardForBigOffset
 * @tc.type: FUNC
 */
HWTEST_F(ListItemGroupAlgorithmTestNg, CheckJumpForwardForBigOffset007, TestSize.Level1)
{
    RefPtr<ListItemGroupLayoutAlgorithm> listItemGroupLayoutAlgorithm =
        AceType::MakeRefPtr<ListItemGroupLayoutAlgorithm>(2, 2, 2);
    listItemGroupLayoutAlgorithm->isNeedCheckOffset_ = true;
    listItemGroupLayoutAlgorithm->startPos_ = 4.0f;
    listItemGroupLayoutAlgorithm->endPos_ = 5.0f;
    listItemGroupLayoutAlgorithm->referencePos_ = 1.0f;
    listItemGroupLayoutAlgorithm->groupItemAverageHeight_ = 1.0f;
    listItemGroupLayoutAlgorithm->spaceWidth_ = 1.0f;
    listItemGroupLayoutAlgorithm->totalItemCount_ = 8;
    LayoutedItemInfo layoutedItemInfo { 3, 2.0f, 1, 4.0f };
    listItemGroupLayoutAlgorithm->layoutedItemInfo_ = layoutedItemInfo;
    int32_t startIndex = 2;
    float startPos = 1.0f;
    auto result = listItemGroupLayoutAlgorithm->CheckJumpForwardForBigOffset(startIndex, startPos);
    EXPECT_EQ(startIndex, 2);
    EXPECT_EQ(startPos, 1.0f);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: CheckJumpBackwardForBigOffset001
 * @tc.desc: Test ListItemGroupLayoutAlgorithm CheckJumpBackwardForBigOffset
 * @tc.type: FUNC
 */
HWTEST_F(ListItemGroupAlgorithmTestNg, CheckJumpBackwardForBigOffset001, TestSize.Level1)
{
    RefPtr<ListItemGroupLayoutAlgorithm> listItemGroupLayoutAlgorithm =
        AceType::MakeRefPtr<ListItemGroupLayoutAlgorithm>(2, 2, 2);
    listItemGroupLayoutAlgorithm->isNeedCheckOffset_ = true;
    std::vector<float> mainSize;
    mainSize.push_back(2.0f);
    RefPtr<ListChildrenMainSize> childrenSize = AceType::MakeRefPtr<ListChildrenMainSize>(mainSize, 2.0f);
    listItemGroupLayoutAlgorithm->childrenSize_ = childrenSize;
    int32_t endIndex = 2;
    float endPos = 2.0f;
    auto result = listItemGroupLayoutAlgorithm->CheckJumpBackwardForBigOffset(endIndex, endPos);
    EXPECT_EQ(endIndex, 2);
    EXPECT_EQ(endPos, 2.0f);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: CheckJumpBackwardForBigOffset002
 * @tc.desc: Test ListItemGroupLayoutAlgorithm CheckJumpBackwardForBigOffset
 * @tc.type: FUNC
 */
HWTEST_F(ListItemGroupAlgorithmTestNg, CheckJumpBackwardForBigOffset002, TestSize.Level1)
{
    RefPtr<ListItemGroupLayoutAlgorithm> listItemGroupLayoutAlgorithm =
        AceType::MakeRefPtr<ListItemGroupLayoutAlgorithm>(2, 2, 2);
    listItemGroupLayoutAlgorithm->isNeedCheckOffset_ = false;
    std::vector<float> mainSize;
    mainSize.push_back(2.0f);
    RefPtr<ListChildrenMainSize> childrenSize = AceType::MakeRefPtr<ListChildrenMainSize>(mainSize, 2.0f);
    listItemGroupLayoutAlgorithm->childrenSize_ = childrenSize;
    int32_t endIndex = 2;
    float endPos = 2.0f;
    auto result = listItemGroupLayoutAlgorithm->CheckJumpBackwardForBigOffset(endIndex, endPos);
    EXPECT_EQ(endIndex, 2);
    EXPECT_EQ(endPos, 2.0f);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: CheckJumpBackwardForBigOffset003
 * @tc.desc: Test ListItemGroupLayoutAlgorithm CheckJumpBackwardForBigOffset
 * @tc.type: FUNC
 */
HWTEST_F(ListItemGroupAlgorithmTestNg, CheckJumpBackwardForBigOffset003, TestSize.Level1)
{
    RefPtr<ListItemGroupLayoutAlgorithm> listItemGroupLayoutAlgorithm =
        AceType::MakeRefPtr<ListItemGroupLayoutAlgorithm>(2, 2, 2);
    listItemGroupLayoutAlgorithm->isNeedCheckOffset_ = false;
    int32_t endIndex = 2;
    float endPos = 2.0f;
    auto result = listItemGroupLayoutAlgorithm->CheckJumpBackwardForBigOffset(endIndex, endPos);
    EXPECT_EQ(endIndex, 2);
    EXPECT_EQ(endPos, 2.0f);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: CheckJumpBackwardForBigOffset004
 * @tc.desc: Test ListItemGroupLayoutAlgorithm CheckJumpBackwardForBigOffset
 * @tc.type: FUNC
 */
HWTEST_F(ListItemGroupAlgorithmTestNg, CheckJumpBackwardForBigOffset004, TestSize.Level1)
{
    RefPtr<ListItemGroupLayoutAlgorithm> listItemGroupLayoutAlgorithm =
        AceType::MakeRefPtr<ListItemGroupLayoutAlgorithm>(2, 2, 2);
    listItemGroupLayoutAlgorithm->isNeedCheckOffset_ = true;
    listItemGroupLayoutAlgorithm->startPos_ = 4.0f;
    listItemGroupLayoutAlgorithm->endPos_ = 5.0f;
    listItemGroupLayoutAlgorithm->referencePos_ = 1.0f;
    listItemGroupLayoutAlgorithm->totalMainSize_ = 2.0f;
    int32_t endIndex = 2;
    float endPos = 2.0f;
    auto result = listItemGroupLayoutAlgorithm->CheckJumpBackwardForBigOffset(endIndex, endPos);
    EXPECT_EQ(endIndex, 2);
    EXPECT_EQ(endPos, 2.0f);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: CheckJumpBackwardForBigOffset005
 * @tc.desc: Test ListItemGroupLayoutAlgorithm CheckJumpBackwardForBigOffset
 * @tc.type: FUNC
 */
HWTEST_F(ListItemGroupAlgorithmTestNg, CheckJumpBackwardForBigOffset005, TestSize.Level1)
{
    RefPtr<ListItemGroupLayoutAlgorithm> listItemGroupLayoutAlgorithm =
        AceType::MakeRefPtr<ListItemGroupLayoutAlgorithm>(2, 2, 2);
    listItemGroupLayoutAlgorithm->isNeedCheckOffset_ = true;
    listItemGroupLayoutAlgorithm->startPos_ = 4.0f;
    listItemGroupLayoutAlgorithm->endPos_ = 5.0f;
    listItemGroupLayoutAlgorithm->referencePos_ = 11.0f;
    listItemGroupLayoutAlgorithm->groupItemAverageHeight_ = 2.0f;
    listItemGroupLayoutAlgorithm->totalMainSize_ = 2.0f;
    listItemGroupLayoutAlgorithm->spaceWidth_ = 1.0f;
    listItemGroupLayoutAlgorithm->itemPosition_.clear();
    LayoutedItemInfo layoutedItemInfo { 1, 2.0f, 2, 4.0f };
    listItemGroupLayoutAlgorithm->layoutedItemInfo_ = layoutedItemInfo;
    int32_t endIndex = 2;
    float endPos = 1.0f;
    auto result = listItemGroupLayoutAlgorithm->CheckJumpBackwardForBigOffset(endIndex, endPos);
    EXPECT_EQ(endIndex, 2);
    EXPECT_EQ(endPos, 1.0f);
    EXPECT_EQ(listItemGroupLayoutAlgorithm->itemPosition_[0].startPos, -2.5f);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: CheckJumpBackwardForBigOffset006
 * @tc.desc: Test ListItemGroupLayoutAlgorithm CheckJumpBackwardForBigOffset
 * @tc.type: FUNC
 */
HWTEST_F(ListItemGroupAlgorithmTestNg, CheckJumpBackwardForBigOffset006, TestSize.Level1)
{
    RefPtr<ListItemGroupLayoutAlgorithm> listItemGroupLayoutAlgorithm =
        AceType::MakeRefPtr<ListItemGroupLayoutAlgorithm>(2, 2, 2);
    listItemGroupLayoutAlgorithm->isNeedCheckOffset_ = true;
    listItemGroupLayoutAlgorithm->startPos_ = 0.0f;
    listItemGroupLayoutAlgorithm->endPos_ = 1.0f;
    listItemGroupLayoutAlgorithm->referencePos_ = 1.0f;
    listItemGroupLayoutAlgorithm->groupItemAverageHeight_ = 2.0f;
    listItemGroupLayoutAlgorithm->totalMainSize_ = 0.0f;
    listItemGroupLayoutAlgorithm->spaceWidth_ = 1.0f;
    listItemGroupLayoutAlgorithm->itemPosition_.clear();
    int32_t endIndex = 2;
    float endPos = 3.0f;
    auto result = listItemGroupLayoutAlgorithm->CheckJumpBackwardForBigOffset(endIndex, endPos);
    EXPECT_EQ(endIndex, 1);
    EXPECT_EQ(endPos, 1.0f);
    EXPECT_TRUE(listItemGroupLayoutAlgorithm->itemPosition_.empty());
    EXPECT_FALSE(result);
}

/**
 * @tc.name: CheckJumpBackwardForBigOffset007
 * @tc.desc: Test ListItemGroupLayoutAlgorithm CheckJumpBackwardForBigOffset
 * @tc.type: FUNC
 */
HWTEST_F(ListItemGroupAlgorithmTestNg, CheckJumpBackwardForBigOffset007, TestSize.Level1)
{
    RefPtr<ListItemGroupLayoutAlgorithm> listItemGroupLayoutAlgorithm =
        AceType::MakeRefPtr<ListItemGroupLayoutAlgorithm>(2, 2, 2);
    listItemGroupLayoutAlgorithm->isNeedCheckOffset_ = true;
    listItemGroupLayoutAlgorithm->startPos_ = 4.0f;
    listItemGroupLayoutAlgorithm->endPos_ = 5.0f;
    listItemGroupLayoutAlgorithm->referencePos_ = 11.0f;
    listItemGroupLayoutAlgorithm->groupItemAverageHeight_ = 2.0f;
    listItemGroupLayoutAlgorithm->totalMainSize_ = 2.0f;
    listItemGroupLayoutAlgorithm->spaceWidth_ = 1.0f;
    LayoutedItemInfo layoutedItemInfo { 3, 2.0f, 1, 4.0f };
    listItemGroupLayoutAlgorithm->layoutedItemInfo_ = layoutedItemInfo;
    int32_t endIndex = 2;
    float endPos = 1.0f;
    auto result = listItemGroupLayoutAlgorithm->CheckJumpBackwardForBigOffset(endIndex, endPos);
    EXPECT_EQ(endIndex, 2);
    EXPECT_EQ(endPos, 1.0f);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: CheckUpdateGroupAndItemPos001
 * @tc.desc: Test ListItemGroupLayoutAlgorithm CheckUpdateGroupAndItemPos
 * @tc.type: FUNC
 */
HWTEST_F(ListItemGroupAlgorithmTestNg, CheckUpdateGroupAndItemPos001, TestSize.Level1)
{
    RefPtr<ListItemGroupLayoutAlgorithm> listItemGroupLayoutAlgorithm =
        AceType::MakeRefPtr<ListItemGroupLayoutAlgorithm>(2, 2, 2);
    RefPtr<ShallowBuilder> shallowBuilder = AceType::MakeRefPtr<ShallowBuilder>(nullptr);
    RefPtr<ListItemPattern> listItemPattern =
        AceType::MakeRefPtr<ListItemPattern>(shallowBuilder, V2::ListItemStyle::CARD);
    auto frameNode = FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, 2, listItemPattern);
    ASSERT_NE(frameNode, nullptr);
    listItemPattern->frameNode_ = frameNode;
    RefPtr<ListLayoutProperty> listLayoutProperty = AceType::MakeRefPtr<ListLayoutProperty>();
    frameNode->layoutProperty_ = listLayoutProperty;
    listItemPattern->frameNode_ = frameNode;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(geometryNode, nullptr);
    geometryNode->margin_ = std::make_unique<MarginPropertyF>();
    geometryNode->margin_->left = 5.0f;
    geometryNode->margin_->right = 2.0f;
    geometryNode->margin_->top = 10.0f;
    geometryNode->margin_->bottom = 4.0f;
    GeometryProperty geometryProperty;
    geometryProperty.rect_ = RectF(20.0f, 20.0f, 100.0f, 100.0f);
    geometryNode->frame_ = geometryProperty;
    LayoutWrapperNode layoutWrapper(frameNode, geometryNode, listLayoutProperty);
    layoutWrapper.geometryNode_ = geometryNode;
    frameNode->geometryNode_ = geometryNode;
    listItemGroupLayoutAlgorithm->axis_ = Axis::HORIZONTAL;
    listItemGroupLayoutAlgorithm->layoutDirection_ = TextDirection::RTL;
    listItemGroupLayoutAlgorithm->isStackFromEnd_ = true;
    listItemGroupLayoutAlgorithm->adjustReferenceDelta_ = 2.0f;
    listItemGroupLayoutAlgorithm->adjustTotalSize_ = 0.0f;
    OffsetF paddingOffset(2.0f, 2.0f);
    listItemGroupLayoutAlgorithm->CheckUpdateGroupAndItemPos(&layoutWrapper, paddingOffset, 2.0f);
    EXPECT_EQ(layoutWrapper.geometryNode_->frame_.rect_.GetX(), 22.0f);
    EXPECT_EQ(layoutWrapper.geometryNode_->frame_.rect_.GetY(), 20.0f);
}

/**
 * @tc.name: CheckUpdateGroupAndItemPos002
 * @tc.desc: Test ListItemGroupLayoutAlgorithm CheckUpdateGroupAndItemPos
 * @tc.type: FUNC
 */
HWTEST_F(ListItemGroupAlgorithmTestNg, CheckUpdateGroupAndItemPos002, TestSize.Level1)
{
    RefPtr<ListItemGroupLayoutAlgorithm> listItemGroupLayoutAlgorithm =
        AceType::MakeRefPtr<ListItemGroupLayoutAlgorithm>(2, 2, 2);
    RefPtr<ShallowBuilder> shallowBuilder = AceType::MakeRefPtr<ShallowBuilder>(nullptr);
    RefPtr<ListItemPattern> listItemPattern =
        AceType::MakeRefPtr<ListItemPattern>(shallowBuilder, V2::ListItemStyle::CARD);
    auto frameNode = FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, 2, listItemPattern);
    ASSERT_NE(frameNode, nullptr);
    listItemPattern->frameNode_ = frameNode;
    RefPtr<ListLayoutProperty> listLayoutProperty = AceType::MakeRefPtr<ListLayoutProperty>();
    frameNode->layoutProperty_ = listLayoutProperty;
    listItemPattern->frameNode_ = frameNode;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(geometryNode, nullptr);
    geometryNode->margin_ = std::make_unique<MarginPropertyF>();
    geometryNode->margin_->left = 5.0f;
    geometryNode->margin_->right = 2.0f;
    geometryNode->margin_->top = 10.0f;
    geometryNode->margin_->bottom = 4.0f;
    GeometryProperty geometryProperty;
    geometryProperty.rect_ = RectF(20.0f, 20.0f, 100.0f, 100.0f);
    geometryNode->frame_ = geometryProperty;
    LayoutWrapperNode layoutWrapper(frameNode, geometryNode, listLayoutProperty);
    layoutWrapper.geometryNode_ = geometryNode;
    frameNode->geometryNode_ = geometryNode;
    listItemGroupLayoutAlgorithm->axis_ = Axis::FREE;
    listItemGroupLayoutAlgorithm->layoutDirection_ = TextDirection::AUTO;
    listItemGroupLayoutAlgorithm->isStackFromEnd_ = true;
    listItemGroupLayoutAlgorithm->adjustReferenceDelta_ = 2.0f;
    listItemGroupLayoutAlgorithm->adjustTotalSize_ = 0.0f;
    OffsetF paddingOffset(2.0f, 2.0f);
    listItemGroupLayoutAlgorithm->CheckUpdateGroupAndItemPos(&layoutWrapper, paddingOffset, 2.0f);
    EXPECT_EQ(layoutWrapper.geometryNode_->frame_.rect_.GetX(), 18.0f);
    EXPECT_EQ(layoutWrapper.geometryNode_->frame_.rect_.GetY(), 20.0f);
}

/**
 * @tc.name: GetItemHeight001
 * @tc.desc: Test ListItemGroupLayoutAlgorithm GetItemHeight
 * @tc.type: FUNC
 */
HWTEST_F(ListItemGroupAlgorithmTestNg, GetItemHeight001, TestSize.Level1)
{
    RefPtr<ListItemGroupLayoutAlgorithm> listItemGroupLayoutAlgorithm =
        AceType::MakeRefPtr<ListItemGroupLayoutAlgorithm>(2, 2, 2);
    ListItemGroupInfo listItemGroupInfo { 2, 2.0f, 2.0f, true };
    listItemGroupLayoutAlgorithm->itemPosition_[0] = listItemGroupInfo;
    auto result = listItemGroupLayoutAlgorithm->GetItemHeight(1);
    EXPECT_EQ(result, 0.0f);
}

/**
 * @tc.name: MeasureALineAuto001
 * @tc.desc: Test ListItemGroupLayoutAlgorithm MeasureALineAuto
 * @tc.type: FUNC
 */
HWTEST_F(ListItemGroupAlgorithmTestNg, MeasureALineAuto001, TestSize.Level1)
{
    RefPtr<ListItemGroupLayoutAlgorithm> listItemGroupLayoutAlgorithm =
        AceType::MakeRefPtr<ListItemGroupLayoutAlgorithm>(2, 2, 2);
    RefPtr<ShallowBuilder> shallowBuilder = AceType::MakeRefPtr<ShallowBuilder>(nullptr);
    RefPtr<ListItemPattern> listItemPattern =
        AceType::MakeRefPtr<ListItemPattern>(shallowBuilder, V2::ListItemStyle::CARD);
    auto frameNode = FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, 2, listItemPattern);
    ASSERT_NE(frameNode, nullptr);
    listItemPattern->frameNode_ = frameNode;
    RefPtr<ListLayoutProperty> listLayoutProperty = AceType::MakeRefPtr<ListLayoutProperty>();
    frameNode->layoutProperty_ = listLayoutProperty;
    listItemPattern->frameNode_ = frameNode;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(geometryNode, nullptr);
    GeometryProperty geometryProperty;
    geometryNode->frame_ = geometryProperty;
    LayoutWrapperNode layoutWrapper(frameNode, geometryNode, listLayoutProperty);
    layoutWrapper.geometryNode_ = geometryNode;
    frameNode->geometryNode_ = geometryNode;
    layoutWrapper.currentChildCount_ = 3;
    listItemGroupLayoutAlgorithm->isStackFromEnd_ = true;
    listItemGroupLayoutAlgorithm->itemStartIndex_ = 2;
    LayoutConstraintF layoutConstraint;
    auto result = listItemGroupLayoutAlgorithm->MeasureALineAuto(&layoutWrapper, layoutConstraint, 2);
    EXPECT_EQ(result, 0);
}

/**
 * @tc.name: MeasureALineAuto002
 * @tc.desc: Test ListItemGroupLayoutAlgorithm MeasureALineAuto
 * @tc.type: FUNC
 */
HWTEST_F(ListItemGroupAlgorithmTestNg, MeasureALineAuto002, TestSize.Level1)
{
    RefPtr<ListItemGroupLayoutAlgorithm> listItemGroupLayoutAlgorithm =
        AceType::MakeRefPtr<ListItemGroupLayoutAlgorithm>(2, 2, 2);
    listItemGroupLayoutAlgorithm->itemPosition_.clear();
    RefPtr<ShallowBuilder> shallowBuilder = AceType::MakeRefPtr<ShallowBuilder>(nullptr);
    RefPtr<ListItemPattern> listItemPattern =
        AceType::MakeRefPtr<ListItemPattern>(shallowBuilder, V2::ListItemStyle::CARD);
    LayoutConstraintF layoutConstraint;
    auto frameNode = FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, 2, listItemPattern);
    ASSERT_NE(frameNode, nullptr);
    listItemPattern->frameNode_ = frameNode;
    RefPtr<ListLayoutProperty> listLayoutProperty = AceType::MakeRefPtr<ListLayoutProperty>();
    listLayoutProperty->layoutConstraint_ = layoutConstraint;
    frameNode->layoutProperty_ = listLayoutProperty;
    listItemPattern->frameNode_ = frameNode;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(geometryNode, nullptr);
    geometryNode->margin_ = std::make_unique<MarginPropertyF>();
    geometryNode->margin_->left = 5.0f;
    geometryNode->margin_->right = 2.0f;
    geometryNode->margin_->top = 10.0f;
    geometryNode->margin_->bottom = 4.0f;
    GeometryProperty geometryProperty;
    geometryProperty.rect_ = RectF(20.0f, 20.0f, 100.0f, 100.0f);
    geometryNode->frame_ = geometryProperty;
    geometryNode->parentLayoutConstraint_ = layoutConstraint;
    RefPtr<LayoutWrapperNode> layoutWrapperNode =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, listLayoutProperty);
    layoutWrapperNode->SetActive();
    layoutWrapperNode->needForceMeasureAndLayout_ = true;
    layoutWrapperNode->geometryNode_ = geometryNode;
    layoutWrapperNode->hostNode_ = frameNode;
    layoutWrapperNode->layoutProperty_ = listLayoutProperty;
    RefPtr<LayoutAlgorithmWrapper> layoutAlgorithmWrapper =
        AceType::MakeRefPtr<LayoutAlgorithmWrapper>(listItemGroupLayoutAlgorithm);
    layoutWrapperNode->layoutAlgorithm_ = layoutAlgorithmWrapper;
    LayoutWrapperNode layoutWrapper(frameNode, geometryNode, listLayoutProperty);
    layoutWrapper.geometryNode_ = geometryNode;
    frameNode->geometryNode_ = geometryNode;
    layoutWrapper.currentChildCount_ = 6;
    layoutWrapper.childrenMap_[4] = layoutWrapperNode;
    listItemGroupLayoutAlgorithm->isStackFromEnd_ = false;
    listItemGroupLayoutAlgorithm->itemStartIndex_ = 2;
    listItemGroupLayoutAlgorithm->childLayoutConstraint_ = layoutConstraint;
    auto result = listItemGroupLayoutAlgorithm->MeasureALineAuto(&layoutWrapper, layoutConstraint, 2);
    EXPECT_EQ(layoutWrapperNode->layoutProperty_->contentConstraint_,
        layoutWrapperNode->layoutProperty_->layoutConstraint_.value());
    EXPECT_EQ(listItemGroupLayoutAlgorithm->itemPosition_[2].endPos, 100.0f);
    EXPECT_EQ(result, 1);
}

/**
 * @tc.name: MeasureALineAuto003
 * @tc.desc: Test ListItemGroupLayoutAlgorithm MeasureALineAuto
 * @tc.type: FUNC
 */
HWTEST_F(ListItemGroupAlgorithmTestNg, MeasureALineAuto003, TestSize.Level1)
{
    RefPtr<ListItemGroupLayoutAlgorithm> listItemGroupLayoutAlgorithm =
        AceType::MakeRefPtr<ListItemGroupLayoutAlgorithm>(2, 2, 2);
    listItemGroupLayoutAlgorithm->itemPosition_.clear();
    RefPtr<ShallowBuilder> shallowBuilder = AceType::MakeRefPtr<ShallowBuilder>(nullptr);
    RefPtr<ListItemPattern> listItemPattern =
        AceType::MakeRefPtr<ListItemPattern>(shallowBuilder, V2::ListItemStyle::CARD);
    LayoutConstraintF layoutConstraint;
    auto frameNode = FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, 2, listItemPattern);
    ASSERT_NE(frameNode, nullptr);
    listItemPattern->frameNode_ = frameNode;
    RefPtr<ListLayoutProperty> listLayoutProperty = AceType::MakeRefPtr<ListLayoutProperty>();
    frameNode->layoutProperty_ = listLayoutProperty;
    listItemPattern->frameNode_ = frameNode;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(geometryNode, nullptr);
    geometryNode->margin_ = std::make_unique<MarginPropertyF>();
    geometryNode->margin_->left = 6.0f;
    geometryNode->margin_->right = 3.0f;
    geometryNode->margin_->top = 20.0f;
    geometryNode->margin_->bottom = 8.0f;
    GeometryProperty geometryProperty;
    geometryProperty.rect_ = RectF(10.0f, 300.0f, 50.0f, 50.0f);
    geometryNode->frame_ = geometryProperty;
    geometryNode->parentLayoutConstraint_ = layoutConstraint;
    RefPtr<LayoutWrapperNode> layoutWrapperNode =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, listLayoutProperty);
    layoutWrapperNode->SetActive();
    layoutWrapperNode->needForceMeasureAndLayout_ = false;
    layoutWrapperNode->geometryNode_ = geometryNode;
    LayoutWrapperNode layoutWrapper(frameNode, geometryNode, listLayoutProperty);
    layoutWrapper.geometryNode_ = geometryNode;
    frameNode->geometryNode_ = geometryNode;
    layoutWrapper.currentChildCount_ = 6;
    layoutWrapper.childrenMap_[4] = layoutWrapperNode;
    listItemGroupLayoutAlgorithm->isStackFromEnd_ = false;
    listItemGroupLayoutAlgorithm->itemStartIndex_ = 2;
    listItemGroupLayoutAlgorithm->childLayoutConstraint_ = layoutConstraint;
    auto result = listItemGroupLayoutAlgorithm->MeasureALineAuto(&layoutWrapper, layoutConstraint, 2);
    EXPECT_EQ(listItemGroupLayoutAlgorithm->itemPosition_[2].endPos, 78.0f);
    EXPECT_EQ(result, 1);
}

/**
 * @tc.name: MeasureAuto001
 * @tc.desc: Test ListItemGroupLayoutAlgorithm MeasureAuto
 * @tc.type: FUNC
 */
HWTEST_F(ListItemGroupAlgorithmTestNg, MeasureAuto001, TestSize.Level1)
{
    RefPtr<ListItemGroupLayoutAlgorithm> listItemGroupLayoutAlgorithm =
        AceType::MakeRefPtr<ListItemGroupLayoutAlgorithm>(2, 2, 2);
    RefPtr<ShallowBuilder> shallowBuilder = AceType::MakeRefPtr<ShallowBuilder>(nullptr);
    RefPtr<ListItemPattern> listItemPattern =
        AceType::MakeRefPtr<ListItemPattern>(shallowBuilder, V2::ListItemStyle::CARD);
    auto frameNode = FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, 2, listItemPattern);
    ASSERT_NE(frameNode, nullptr);
    listItemPattern->frameNode_ = frameNode;
    RefPtr<ListLayoutProperty> listLayoutProperty = AceType::MakeRefPtr<ListLayoutProperty>();
    frameNode->layoutProperty_ = listLayoutProperty;
    listItemPattern->frameNode_ = frameNode;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(geometryNode, nullptr);
    GeometryProperty geometryProperty;
    geometryNode->frame_ = geometryProperty;
    LayoutWrapperNode layoutWrapper(frameNode, geometryNode, listLayoutProperty);
    layoutWrapper.geometryNode_ = geometryNode;
    frameNode->geometryNode_ = geometryNode;
    layoutWrapper.currentChildCount_ = 3;
    listItemGroupLayoutAlgorithm->isStackFromEnd_ = true;
    listItemGroupLayoutAlgorithm->itemStartIndex_ = 2;
    listItemGroupLayoutAlgorithm->totalMainSize_ = 2.0f;
    LayoutConstraintF layoutConstraint;
    listItemGroupLayoutAlgorithm->MeasureAuto(&layoutWrapper, layoutConstraint, 2);
    EXPECT_EQ(listItemGroupLayoutAlgorithm->totalMainSize_, 2.0f);
}

/**
 * @tc.name: MeasureAuto002
 * @tc.desc: Test ListItemGroupLayoutAlgorithm MeasureAuto
 * @tc.type: FUNC
 */
HWTEST_F(ListItemGroupAlgorithmTestNg, MeasureAuto002, TestSize.Level1)
{
    RefPtr<ListItemGroupLayoutAlgorithm> listItemGroupLayoutAlgorithm =
        AceType::MakeRefPtr<ListItemGroupLayoutAlgorithm>(2, 2, 2);
    listItemGroupLayoutAlgorithm->itemPosition_.clear();
    RefPtr<ShallowBuilder> shallowBuilder = AceType::MakeRefPtr<ShallowBuilder>(nullptr);
    RefPtr<ListItemPattern> listItemPattern =
        AceType::MakeRefPtr<ListItemPattern>(shallowBuilder, V2::ListItemStyle::CARD);
    LayoutConstraintF layoutConstraint;
    auto frameNode = FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, 2, listItemPattern);
    ASSERT_NE(frameNode, nullptr);
    listItemPattern->frameNode_ = frameNode;
    RefPtr<ListLayoutProperty> listLayoutProperty = AceType::MakeRefPtr<ListLayoutProperty>();
    frameNode->layoutProperty_ = listLayoutProperty;
    listItemPattern->frameNode_ = frameNode;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(geometryNode, nullptr);
    geometryNode->margin_ = std::make_unique<MarginPropertyF>();
    geometryNode->margin_->left = 6.0f;
    geometryNode->margin_->right = 3.0f;
    geometryNode->margin_->top = 20.0f;
    geometryNode->margin_->bottom = 8.0f;
    GeometryProperty geometryProperty;
    geometryProperty.rect_ = RectF(10.0f, 300.0f, 50.0f, 50.0f);
    geometryNode->frame_ = geometryProperty;
    geometryNode->parentLayoutConstraint_ = layoutConstraint;
    RefPtr<LayoutWrapperNode> layoutWrapperNode =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, listLayoutProperty);
    layoutWrapperNode->SetActive();
    layoutWrapperNode->needForceMeasureAndLayout_ = false;
    layoutWrapperNode->geometryNode_ = geometryNode;
    LayoutWrapperNode layoutWrapper(frameNode, geometryNode, listLayoutProperty);
    layoutWrapper.geometryNode_ = geometryNode;
    frameNode->geometryNode_ = geometryNode;
    layoutWrapper.currentChildCount_ = 6;
    layoutWrapper.childrenMap_[4] = layoutWrapperNode;
    listItemGroupLayoutAlgorithm->isStackFromEnd_ = false;
    listItemGroupLayoutAlgorithm->itemStartIndex_ = 2;
    listItemGroupLayoutAlgorithm->childLayoutConstraint_ = layoutConstraint;
    listItemGroupLayoutAlgorithm->headerMainSize_ = 5.0f;
    listItemGroupLayoutAlgorithm->footerMainSize_ = 10.0f;
    listItemGroupLayoutAlgorithm->spaceWidth_ = 1.0f;
    ListItemGroupInfo listItemGroupInfo { 2, 2.0f, 2.0f, true };
    ListItemGroupInfo info { 2, 4.0f, 8.0f, false };
    listItemGroupLayoutAlgorithm->itemPosition_[0] = listItemGroupInfo;
    listItemGroupLayoutAlgorithm->itemPosition_[1] = info;
    listItemGroupLayoutAlgorithm->MeasureAuto(&layoutWrapper, layoutConstraint, 2);
    EXPECT_EQ(listItemGroupLayoutAlgorithm->totalMainSize_, 92.0f);
}

/**
 * @tc.name: GetChildMaxCrossSize001
 * @tc.desc: Test ListItemGroupLayoutAlgorithm GetChildMaxCrossSize
 * @tc.type: FUNC
 */
HWTEST_F(ListItemGroupAlgorithmTestNg, GetChildMaxCrossSize001, TestSize.Level1)
{
    RefPtr<ListItemGroupLayoutAlgorithm> listItemGroupLayoutAlgorithm =
        AceType::MakeRefPtr<ListItemGroupLayoutAlgorithm>(2, 2, 2);
    listItemGroupLayoutAlgorithm->itemPosition_.clear();
    RefPtr<ShallowBuilder> shallowBuilder = AceType::MakeRefPtr<ShallowBuilder>(nullptr);
    RefPtr<ListItemPattern> listItemPattern =
        AceType::MakeRefPtr<ListItemPattern>(shallowBuilder, V2::ListItemStyle::CARD);
    auto frameNode = FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, 2, listItemPattern);
    ASSERT_NE(frameNode, nullptr);
    listItemPattern->frameNode_ = frameNode;
    RefPtr<ListLayoutProperty> listLayoutProperty = AceType::MakeRefPtr<ListLayoutProperty>();
    frameNode->layoutProperty_ = listLayoutProperty;
    listItemPattern->frameNode_ = frameNode;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(geometryNode, nullptr);
    GeometryProperty geometryProperty;
    geometryNode->frame_ = geometryProperty;
    LayoutWrapperNode layoutWrapper(frameNode, geometryNode, listLayoutProperty);
    layoutWrapper.geometryNode_ = geometryNode;
    frameNode->geometryNode_ = geometryNode;
    layoutWrapper.currentChildCount_ = 0;
    listItemGroupLayoutAlgorithm->isStackFromEnd_ = false;
    listItemGroupLayoutAlgorithm->itemStartIndex_ = 2;
    listItemGroupLayoutAlgorithm->spaceWidth_ = 1.0f;
    ListItemGroupInfo listItemGroupInfo { 2, 2.0f, 2.0f, true };
    listItemGroupLayoutAlgorithm->itemPosition_[0] = listItemGroupInfo;
    listItemGroupLayoutAlgorithm->cachedItemPosition_[0] = listItemGroupInfo;
    auto result = listItemGroupLayoutAlgorithm->GetChildMaxCrossSize(&layoutWrapper, Axis::FREE);
    EXPECT_EQ(result, 0.0f);
}

/**
 * @tc.name: GetChildMaxCrossSize002
 * @tc.desc: Test ListItemGroupLayoutAlgorithm GetChildMaxCrossSize
 * @tc.type: FUNC
 */
HWTEST_F(ListItemGroupAlgorithmTestNg, GetChildMaxCrossSize002, TestSize.Level1)
{
    RefPtr<ListItemGroupLayoutAlgorithm> listItemGroupLayoutAlgorithm =
        AceType::MakeRefPtr<ListItemGroupLayoutAlgorithm>(2, 2, 2);
    listItemGroupLayoutAlgorithm->itemPosition_.clear();
    RefPtr<ShallowBuilder> shallowBuilder = AceType::MakeRefPtr<ShallowBuilder>(nullptr);
    RefPtr<ListItemPattern> listItemPattern =
        AceType::MakeRefPtr<ListItemPattern>(shallowBuilder, V2::ListItemStyle::CARD);
    auto frameNode = FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, 2, listItemPattern);
    ASSERT_NE(frameNode, nullptr);
    listItemPattern->frameNode_ = frameNode;
    RefPtr<ListLayoutProperty> listLayoutProperty = AceType::MakeRefPtr<ListLayoutProperty>();
    frameNode->layoutProperty_ = listLayoutProperty;
    listItemPattern->frameNode_ = frameNode;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(geometryNode, nullptr);
    geometryNode->margin_ = std::make_unique<MarginPropertyF>();
    geometryNode->margin_->left = 6.0f;
    geometryNode->margin_->right = 3.0f;
    geometryNode->margin_->top = 20.0f;
    geometryNode->margin_->bottom = 8.0f;
    GeometryProperty geometryProperty;
    geometryProperty.rect_ = RectF(10.0f, 300.0f, 50.0f, 50.0f);
    geometryNode->frame_ = geometryProperty;
    RefPtr<LayoutWrapperNode> layoutWrapperNode =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, listLayoutProperty);
    layoutWrapperNode->SetActive();
    layoutWrapperNode->needForceMeasureAndLayout_ = false;
    layoutWrapperNode->geometryNode_ = geometryNode;
    LayoutWrapperNode layoutWrapper(frameNode, geometryNode, listLayoutProperty);
    layoutWrapper.geometryNode_ = geometryNode;
    frameNode->geometryNode_ = geometryNode;
    layoutWrapper.currentChildCount_ = 6;
    layoutWrapper.childrenMap_[2] = layoutWrapperNode;
    listItemGroupLayoutAlgorithm->isStackFromEnd_ = false;
    listItemGroupLayoutAlgorithm->itemStartIndex_ = 2;
    listItemGroupLayoutAlgorithm->spaceWidth_ = 1.0f;
    ListItemGroupInfo listItemGroupInfo { 2, 2.0f, 2.0f, true };
    listItemGroupLayoutAlgorithm->itemPosition_[0] = listItemGroupInfo;
    listItemGroupLayoutAlgorithm->cachedItemPosition_[0] = listItemGroupInfo;
    auto result = listItemGroupLayoutAlgorithm->GetChildMaxCrossSize(&layoutWrapper, Axis::FREE);
    EXPECT_EQ(result, 59.0f);
}

/**
 * @tc.name: GetChildMaxCrossSize003
 * @tc.desc: Test ListItemGroupLayoutAlgorithm GetChildMaxCrossSize
 * @tc.type: FUNC
 */
HWTEST_F(ListItemGroupAlgorithmTestNg, GetChildMaxCrossSize003, TestSize.Level1)
{
    RefPtr<ListItemGroupLayoutAlgorithm> listItemGroupLayoutAlgorithm =
        AceType::MakeRefPtr<ListItemGroupLayoutAlgorithm>(2, 2, 2);
    listItemGroupLayoutAlgorithm->itemPosition_.clear();
    RefPtr<ShallowBuilder> shallowBuilder = AceType::MakeRefPtr<ShallowBuilder>(nullptr);
    RefPtr<ListItemPattern> listItemPattern =
        AceType::MakeRefPtr<ListItemPattern>(shallowBuilder, V2::ListItemStyle::CARD);
    auto frameNode = FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, 2, listItemPattern);
    ASSERT_NE(frameNode, nullptr);
    listItemPattern->frameNode_ = frameNode;
    RefPtr<ListLayoutProperty> listLayoutProperty = AceType::MakeRefPtr<ListLayoutProperty>();
    frameNode->layoutProperty_ = listLayoutProperty;
    listItemPattern->frameNode_ = frameNode;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(geometryNode, nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapperNode =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, listLayoutProperty);
    layoutWrapperNode->needForceMeasureAndLayout_ = false;
    layoutWrapperNode->geometryNode_ = nullptr;
    LayoutWrapperNode layoutWrapper(frameNode, geometryNode, listLayoutProperty);
    layoutWrapper.geometryNode_ = geometryNode;
    frameNode->geometryNode_ = geometryNode;
    layoutWrapper.currentChildCount_ = 6;
    layoutWrapper.childrenMap_[2] = layoutWrapperNode;
    listItemGroupLayoutAlgorithm->isStackFromEnd_ = false;
    listItemGroupLayoutAlgorithm->itemStartIndex_ = 2;
    listItemGroupLayoutAlgorithm->spaceWidth_ = 1.0f;
    ListItemGroupInfo listItemGroupInfo { 2, 2.0f, 2.0f, true };
    listItemGroupLayoutAlgorithm->itemPosition_[0] = listItemGroupInfo;
    listItemGroupLayoutAlgorithm->cachedItemPosition_[0] = listItemGroupInfo;
    auto result = listItemGroupLayoutAlgorithm->GetChildMaxCrossSize(&layoutWrapper, Axis::FREE);
    EXPECT_EQ(result, 0.0f);
}

/**
 * @tc.name: SetActiveChildRange001
 * @tc.desc: Test ListItemGroupLayoutAlgorithm SetActiveChildRange
 * @tc.type: FUNC
 */
HWTEST_F(ListItemGroupAlgorithmTestNg, SetActiveChildRange001, TestSize.Level1)
{
    RefPtr<ListItemGroupLayoutAlgorithm> listItemGroupLayoutAlgorithm =
        AceType::MakeRefPtr<ListItemGroupLayoutAlgorithm>(2, 2, 2);
    listItemGroupLayoutAlgorithm->itemPosition_.clear();
    RefPtr<ShallowBuilder> shallowBuilder = AceType::MakeRefPtr<ShallowBuilder>(nullptr);
    RefPtr<ListItemPattern> listItemPattern =
        AceType::MakeRefPtr<ListItemPattern>(shallowBuilder, V2::ListItemStyle::CARD);
    auto frameNode = FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, 2, listItemPattern);
    ASSERT_NE(frameNode, nullptr);
    listItemPattern->frameNode_ = frameNode;
    RefPtr<ListLayoutProperty> listLayoutProperty = AceType::MakeRefPtr<ListLayoutProperty>();
    frameNode->layoutProperty_ = listLayoutProperty;
    listItemPattern->frameNode_ = frameNode;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(geometryNode, nullptr);
    LayoutWrapperNode layoutWrapper(frameNode, geometryNode, listLayoutProperty);
    ListItemGroupInfo listItemGroupInfo { 2, 2.0f, 2.0f, true };
    listItemGroupLayoutAlgorithm->cachedItemPosition_[0] = listItemGroupInfo;
    listItemGroupLayoutAlgorithm->cachedItemPosition_[3] = listItemGroupInfo;
    listItemGroupLayoutAlgorithm->SetActiveChildRange(&layoutWrapper, 2, true);
    EXPECT_EQ(listItemGroupLayoutAlgorithm->cachedItemPosition_[0].startPos, 2.0f);
}

/**
 * @tc.name: SetActiveChildRange002
 * @tc.desc: Test ListItemGroupLayoutAlgorithm SetActiveChildRange
 * @tc.type: FUNC
 */
HWTEST_F(ListItemGroupAlgorithmTestNg, SetActiveChildRange002, TestSize.Level1)
{
    RefPtr<ListItemGroupLayoutAlgorithm> listItemGroupLayoutAlgorithm =
        AceType::MakeRefPtr<ListItemGroupLayoutAlgorithm>(2, 2, 2);
    listItemGroupLayoutAlgorithm->itemPosition_.clear();
    RefPtr<ShallowBuilder> shallowBuilder = AceType::MakeRefPtr<ShallowBuilder>(nullptr);
    RefPtr<ListItemPattern> listItemPattern =
        AceType::MakeRefPtr<ListItemPattern>(shallowBuilder, V2::ListItemStyle::CARD);
    auto frameNode = FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, 2, listItemPattern);
    ASSERT_NE(frameNode, nullptr);
    listItemPattern->frameNode_ = frameNode;
    RefPtr<ListLayoutProperty> listLayoutProperty = AceType::MakeRefPtr<ListLayoutProperty>();
    frameNode->layoutProperty_ = listLayoutProperty;
    listItemPattern->frameNode_ = frameNode;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(geometryNode, nullptr);
    LayoutWrapperNode layoutWrapper(frameNode, geometryNode, listLayoutProperty);
    listItemGroupLayoutAlgorithm->totalItemCount_ = 4;
    ListItemGroupInfo listItemGroupInfo { 2, 2.0f, 2.0f, true };
    listItemGroupLayoutAlgorithm->cachedItemPosition_[1] = listItemGroupInfo;
    listItemGroupLayoutAlgorithm->cachedItemPosition_[3] = listItemGroupInfo;
    listItemGroupLayoutAlgorithm->SetActiveChildRange(&layoutWrapper, 2, true);
    EXPECT_EQ(listItemGroupLayoutAlgorithm->cachedItemPosition_[1].startPos, 2.0f);
}

/**
 * @tc.name: SetActiveChildRange003
 * @tc.desc: Test ListItemGroupLayoutAlgorithm SetActiveChildRange
 * @tc.type: FUNC
 */
HWTEST_F(ListItemGroupAlgorithmTestNg, SetActiveChildRange003, TestSize.Level1)
{
    RefPtr<ListItemGroupLayoutAlgorithm> listItemGroupLayoutAlgorithm =
        AceType::MakeRefPtr<ListItemGroupLayoutAlgorithm>(2, 2, 2);
    listItemGroupLayoutAlgorithm->itemPosition_.clear();
    RefPtr<ShallowBuilder> shallowBuilder = AceType::MakeRefPtr<ShallowBuilder>(nullptr);
    RefPtr<ListItemPattern> listItemPattern =
        AceType::MakeRefPtr<ListItemPattern>(shallowBuilder, V2::ListItemStyle::CARD);
    auto frameNode = FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, 2, listItemPattern);
    ASSERT_NE(frameNode, nullptr);
    listItemPattern->frameNode_ = frameNode;
    RefPtr<ListLayoutProperty> listLayoutProperty = AceType::MakeRefPtr<ListLayoutProperty>();
    frameNode->layoutProperty_ = listLayoutProperty;
    listItemPattern->frameNode_ = frameNode;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(geometryNode, nullptr);
    LayoutWrapperNode layoutWrapper(frameNode, geometryNode, listLayoutProperty);
    listItemGroupLayoutAlgorithm->totalItemCount_ = 2;
    ListItemGroupInfo listItemGroupInfo { 2, 2.0f, 2.0f, true };
    listItemGroupLayoutAlgorithm->cachedItemPosition_[1] = listItemGroupInfo;
    listItemGroupLayoutAlgorithm->cachedItemPosition_[3] = listItemGroupInfo;
    listItemGroupLayoutAlgorithm->SetActiveChildRange(&layoutWrapper, 2, true);
    EXPECT_EQ(listItemGroupLayoutAlgorithm->cachedItemPosition_[1].startPos, 2.0f);
}

/**
 * @tc.name: SetActiveChildRange004
 * @tc.desc: Test ListItemGroupLayoutAlgorithm SetActiveChildRange
 * @tc.type: FUNC
 */
HWTEST_F(ListItemGroupAlgorithmTestNg, SetActiveChildRange004, TestSize.Level1)
{
    RefPtr<ListItemGroupLayoutAlgorithm> listItemGroupLayoutAlgorithm =
        AceType::MakeRefPtr<ListItemGroupLayoutAlgorithm>(2, 2, 2);
    listItemGroupLayoutAlgorithm->itemPosition_.clear();
    RefPtr<ShallowBuilder> shallowBuilder = AceType::MakeRefPtr<ShallowBuilder>(nullptr);
    RefPtr<ListItemPattern> listItemPattern =
        AceType::MakeRefPtr<ListItemPattern>(shallowBuilder, V2::ListItemStyle::CARD);
    auto frameNode = FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, 2, listItemPattern);
    ASSERT_NE(frameNode, nullptr);
    listItemPattern->frameNode_ = frameNode;
    RefPtr<ListLayoutProperty> listLayoutProperty = AceType::MakeRefPtr<ListLayoutProperty>();
    frameNode->layoutProperty_ = listLayoutProperty;
    listItemPattern->frameNode_ = frameNode;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(geometryNode, nullptr);
    LayoutConstraintF layoutConstraint;
    geometryNode->margin_ = std::make_unique<MarginPropertyF>();
    geometryNode->margin_->left = 6.0f;
    geometryNode->margin_->right = 3.0f;
    geometryNode->margin_->top = 20.0f;
    geometryNode->margin_->bottom = 8.0f;
    GeometryProperty geometryProperty;
    geometryProperty.rect_ = RectF(10.0f, 300.0f, 50.0f, 50.0f);
    geometryNode->frame_ = geometryProperty;
    geometryNode->parentLayoutConstraint_ = layoutConstraint;
    LayoutWrapperNode layoutWrapper(frameNode, geometryNode, listLayoutProperty);
    layoutWrapper.geometryNode_ = geometryNode;
    listItemGroupLayoutAlgorithm->listLayoutProperty_ = listLayoutProperty;
    ListItemGroupInfo listItemGroupInfo { 2, 4.0f, 8.0f, true };
    listItemGroupLayoutAlgorithm->cachedItemPosition_[0] = listItemGroupInfo;
    listItemGroupLayoutAlgorithm->cachedItemPosition_[3] = listItemGroupInfo;
    listItemGroupLayoutAlgorithm->SetActiveChildRange(&layoutWrapper, 2, false);
    EXPECT_EQ(listItemGroupLayoutAlgorithm->cachedItemPosition_[0].startPos, 4.0f);
}

/**
 * @tc.name: SetActiveChildRange005
 * @tc.desc: Test ListItemGroupLayoutAlgorithm SetActiveChildRange
 * @tc.type: FUNC
 */
HWTEST_F(ListItemGroupAlgorithmTestNg, SetActiveChildRange005, TestSize.Level1)
{
    RefPtr<ListItemGroupLayoutAlgorithm> listItemGroupLayoutAlgorithm =
        AceType::MakeRefPtr<ListItemGroupLayoutAlgorithm>(2, 2, 2);
    listItemGroupLayoutAlgorithm->itemPosition_.clear();
    RefPtr<ShallowBuilder> shallowBuilder = AceType::MakeRefPtr<ShallowBuilder>(nullptr);
    RefPtr<ListItemPattern> listItemPattern =
        AceType::MakeRefPtr<ListItemPattern>(shallowBuilder, V2::ListItemStyle::CARD);
    auto frameNode = FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, 2, listItemPattern);
    ASSERT_NE(frameNode, nullptr);
    listItemPattern->frameNode_ = frameNode;
    RefPtr<ListLayoutProperty> listLayoutProperty = AceType::MakeRefPtr<ListLayoutProperty>();
    frameNode->layoutProperty_ = listLayoutProperty;
    listItemPattern->frameNode_ = frameNode;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(geometryNode, nullptr);
    LayoutConstraintF layoutConstraint;
    geometryNode->margin_ = std::make_unique<MarginPropertyF>();
    geometryNode->margin_->left = 6.0f;
    geometryNode->margin_->right = 3.0f;
    geometryNode->margin_->top = 20.0f;
    geometryNode->margin_->bottom = 8.0f;
    GeometryProperty geometryProperty;
    geometryProperty.rect_ = RectF(10.0f, 300.0f, 50.0f, 50.0f);
    geometryNode->frame_ = geometryProperty;
    geometryNode->parentLayoutConstraint_ = layoutConstraint;
    LayoutWrapperNode layoutWrapper(frameNode, geometryNode, listLayoutProperty);
    layoutWrapper.geometryNode_ = geometryNode;
    listLayoutProperty->layoutConstraint_ = layoutConstraint;
    listItemGroupLayoutAlgorithm->listLayoutProperty_ = listLayoutProperty;
    listItemGroupLayoutAlgorithm->cachedItemPosition_.clear();
    listItemGroupLayoutAlgorithm->SetActiveChildRange(&layoutWrapper, 2, true);
    EXPECT_EQ(listItemGroupLayoutAlgorithm->cachedItemPosition_.size(), 0);
}
} // namespace OHOS::Ace::NG