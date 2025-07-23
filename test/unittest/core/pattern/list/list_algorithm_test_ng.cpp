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

#include <cstdint>
#include <optional>

#include "gtest/gtest.h"
#include "test/unittest/core/pattern/test_ng.h"

#include "core/components_ng/pattern/list/list_item_group_pattern.h"
#include "core/components_ng/pattern/list/list_item_layout_algorithm.h"
#include "core/components_ng/pattern/list/list_layout_algorithm.h"
#include "core/components_ng/pattern/list/list_pattern.h"
#include "core/components_v2/list/list_properties.h"

namespace OHOS::Ace::NG {
using namespace testing;
using namespace testing::ext;

class ListAlgorithmTestNg : public TestNG {
public:
};

/**
 * @tc.name: UpdateListItemConstraint001
 * @tc.desc: Test ListLayoutAlgorithm UpdateListItemConstraint
 * @tc.type: FUNC
 */
HWTEST_F(ListAlgorithmTestNg, UpdateListItemConstraint001, TestSize.Level1)
{
    RefPtr<ListLayoutAlgorithm> listLayoutAlgorithm = AceType::MakeRefPtr<ListLayoutAlgorithm>(2);
    std::optional<float> width = 5.0f;
    std::optional<float> height = std::nullopt;
    OptionalSizeF selfIdealSize(width, height);
    LayoutConstraintF contentConstraint;
    contentConstraint.maxSize.SetCrossSize(10.0f, Axis::HORIZONTAL);
    contentConstraint.percentReference.SetCrossSize(6.0f, Axis::HORIZONTAL);
    listLayoutAlgorithm->UpdateListItemConstraint(Axis::HORIZONTAL, selfIdealSize, contentConstraint);
    EXPECT_EQ(selfIdealSize.Height(), std::nullopt);
    EXPECT_EQ(selfIdealSize.Width(), 5.0f);
    EXPECT_EQ(contentConstraint.maxSize.Height(), 10.0f);
    EXPECT_EQ(contentConstraint.percentReference.Height(), 6.0f);
}

/**
 * @tc.name: ReviseSpace001
 * @tc.desc: Test ListLayoutAlgorithm ReviseSpace
 * @tc.type: FUNC
 */
HWTEST_F(ListAlgorithmTestNg, ReviseSpace001, TestSize.Level1)
{
    RefPtr<ListLayoutAlgorithm> listLayoutAlgorithm = AceType::MakeRefPtr<ListLayoutAlgorithm>(2);
    listLayoutAlgorithm->isRoundingMode_ = true;
    listLayoutAlgorithm->contentMainSize_ = 10.0f;
    listLayoutAlgorithm->spaceWidth_ = 3.8f;
    listLayoutAlgorithm->chainInterval_ = 1.0f;
    RefPtr<ListLayoutProperty> listLayoutProperty = AceType::MakeRefPtr<ListLayoutProperty>();
    listLayoutAlgorithm->ReviseSpace(listLayoutProperty);
    EXPECT_EQ(listLayoutAlgorithm->spaceWidth_, 5.0f);
}

/**
 * @tc.name: Measure001
 * @tc.desc: Test ListLayoutAlgorithm Measure
 * @tc.type: FUNC
 */
HWTEST_F(ListAlgorithmTestNg, Measure001, TestSize.Level1)
{
    RefPtr<ListPattern> listPattern = AceType::MakeRefPtr<ListPattern>();
    RefPtr<ListLayoutAlgorithm> listLayoutAlgorithm = AceType::MakeRefPtr<ListLayoutAlgorithm>(2);
    RefPtr<ListLayoutProperty> listLayoutProperty = AceType::MakeRefPtr<ListLayoutProperty>();
    std::optional<float> width = 5.0f;
    std::optional<float> height = 8.0f;
    OptionalSizeF selfIdealSize(width, height);
    OptionalSizeF parentIdealSize(width, height);
    ViewPosReference viewPosRef = { 5.0f, 5.0f, 5.0f, ReferenceEdge::END, Axis::FREE };
    LayoutConstraintF layoutConstraint;
    layoutConstraint.selfIdealSize = selfIdealSize;
    layoutConstraint.parentIdealSize = parentIdealSize;
    layoutConstraint.viewPosRef = viewPosRef;
    listLayoutProperty->layoutConstraint_ = layoutConstraint;
    listLayoutProperty->contentConstraint_ = layoutConstraint;
    listLayoutProperty->safeAreaExpandOpts_ = std::make_unique<SafeAreaExpandOpts>();
    listLayoutProperty->safeAreaExpandOpts_->type = SAFE_AREA_TYPE_SYSTEM;
    listLayoutProperty->safeAreaExpandOpts_->edges = SAFE_AREA_EDGE_BOTTOM;
    auto frameNode = FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, 2, listPattern);
    ASSERT_NE(frameNode, nullptr);
    listPattern->frameNode_ = frameNode;
    frameNode->layoutProperty_ = listLayoutProperty;
    listPattern->frameNode_ = frameNode;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(geometryNode, nullptr);
    GeometryProperty geometryProperty;
    geometryNode->frame_ = geometryProperty;
    LayoutWrapperNode layoutWrapper(frameNode, geometryNode, listLayoutProperty);
    layoutWrapper.layoutProperty_ = listLayoutProperty;
    ListItemInfo listItemInfo { 2, 2.0f, 4.0f, true };
    listLayoutAlgorithm->itemPosition_[0] = listItemInfo;
    RefPtr<ListPositionMap> listPositionMap = AceType::MakeRefPtr<ListPositionMap>();
    ListPositionInfo positionInfo { 2.0f, 4.0f, true };
    listPositionMap->posMap_[0] = positionInfo;
    listLayoutAlgorithm->posMap_ = listPositionMap;
    listLayoutAlgorithm->childrenSize_ = AceType::MakeRefPtr<ListChildrenMainSize>();
    listLayoutAlgorithm->totalItemCount_ = 0;
    listLayoutAlgorithm->Measure(&layoutWrapper);
    EXPECT_TRUE(listLayoutAlgorithm->itemPosition_.empty());
    EXPECT_TRUE(listLayoutAlgorithm->posMap_->posMap_.empty());
}

/**
 * @tc.name: GetStartPositionWithChainOffset001
 * @tc.desc: Test ListLayoutAlgorithm GetStartPositionWithChainOffset
 * @tc.type: FUNC
 */
HWTEST_F(ListAlgorithmTestNg, GetStartPositionWithChainOffset001, TestSize.Level1)
{
    RefPtr<ListLayoutAlgorithm> listLayoutAlgorithm = AceType::MakeRefPtr<ListLayoutAlgorithm>(2);
    listLayoutAlgorithm->itemPosition_.clear();
    auto result = listLayoutAlgorithm->GetStartPositionWithChainOffset();
    EXPECT_EQ(result, 0.0f);
}

/**
 * @tc.name: GetStartPositionWithChainOffset002
 * @tc.desc: Test ListLayoutAlgorithm GetStartPositionWithChainOffset
 * @tc.type: FUNC
 */
HWTEST_F(ListAlgorithmTestNg, GetStartPositionWithChainOffset002, TestSize.Level1)
{
    RefPtr<ListLayoutAlgorithm> listLayoutAlgorithm = AceType::MakeRefPtr<ListLayoutAlgorithm>(2);
    listLayoutAlgorithm->itemPosition_.clear();
    ListItemInfo listItemInfo { 2, 2.0f, 4.0f, true };
    listLayoutAlgorithm->itemPosition_[0] = listItemInfo;
    listLayoutAlgorithm->chainOffsetFunc_ = [](int32_t value) { return static_cast<float>(value) * 1.5f; };
    listLayoutAlgorithm->isStackFromEnd_ = true;
    auto result = listLayoutAlgorithm->GetStartPositionWithChainOffset();
    EXPECT_EQ(result, 3.5f);
}

/**
 * @tc.name: BeginLayoutForward001
 * @tc.desc: Test ListLayoutAlgorithm BeginLayoutForward
 * @tc.type: FUNC
 */
HWTEST_F(ListAlgorithmTestNg, BeginLayoutForward001, TestSize.Level1)
{
    RefPtr<ListPattern> listPattern = AceType::MakeRefPtr<ListPattern>();
    RefPtr<ListLayoutAlgorithm> listLayoutAlgorithm = AceType::MakeRefPtr<ListLayoutAlgorithm>(2);
    RefPtr<ListLayoutProperty> listLayoutProperty = AceType::MakeRefPtr<ListLayoutProperty>();
    auto frameNode = FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, 2, listPattern);
    ASSERT_NE(frameNode, nullptr);
    frameNode->layoutProperty_ = listLayoutProperty;
    listPattern->frameNode_ = frameNode;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(geometryNode, nullptr);
    GeometryProperty geometryProperty;
    geometryNode->frame_ = geometryProperty;
    LayoutWrapperNode layoutWrapper(frameNode, geometryNode, listLayoutProperty);
    listLayoutAlgorithm->BeginLayoutForward(2.0f, &layoutWrapper);
    EXPECT_FALSE(listLayoutAlgorithm->jumpIndex_.has_value());
}

/**
 * @tc.name: CheckNoNeedJumpListItemGroup001
 * @tc.desc: Test ListLayoutAlgorithm CheckNoNeedJumpListItemGroup
 * @tc.type: FUNC
 */
HWTEST_F(ListAlgorithmTestNg, CheckNoNeedJumpListItemGroup001, TestSize.Level1)
{
    RefPtr<ListPattern> listPattern = AceType::MakeRefPtr<ListPattern>();
    RefPtr<ListLayoutAlgorithm> listLayoutAlgorithm = AceType::MakeRefPtr<ListLayoutAlgorithm>(2);
    RefPtr<ListLayoutProperty> listLayoutProperty = AceType::MakeRefPtr<ListLayoutProperty>();
    auto frameNode = FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, 2, listPattern);
    ASSERT_NE(frameNode, nullptr);
    frameNode->layoutProperty_ = listLayoutProperty;
    listPattern->frameNode_ = frameNode;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(geometryNode, nullptr);
    GeometryProperty geometryProperty;
    geometryNode->frame_ = geometryProperty;
    LayoutWrapperNode layoutWrapper(frameNode, geometryNode, listLayoutProperty);
    layoutWrapper.currentChildCount_ = 2;
    auto result = listLayoutAlgorithm->CheckNoNeedJumpListItemGroup(&layoutWrapper, 2, 3, 5, 2.0f);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: CheckNoNeedJumpListItemGroup002
 * @tc.desc: Test ListLayoutAlgorithm CheckNoNeedJumpListItemGroup
 * @tc.type: FUNC
 */
HWTEST_F(ListAlgorithmTestNg, CheckNoNeedJumpListItemGroup002, TestSize.Level1)
{
    RefPtr<ListPattern> listPattern = AceType::MakeRefPtr<ListPattern>();
    RefPtr<ListLayoutAlgorithm> listLayoutAlgorithm = AceType::MakeRefPtr<ListLayoutAlgorithm>(2);
    RefPtr<ListLayoutProperty> listLayoutProperty = AceType::MakeRefPtr<ListLayoutProperty>();
    auto frameNode = FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, 2, listPattern);
    ASSERT_NE(frameNode, nullptr);
    frameNode->layoutProperty_ = listLayoutProperty;
    listPattern->frameNode_ = frameNode;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(geometryNode, nullptr);
    GeometryProperty geometryProperty;
    geometryNode->frame_ = geometryProperty;
    RefPtr<LayoutWrapperNode> layoutWrapperNode =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, listLayoutProperty);
    layoutWrapperNode->SetActive();
    layoutWrapperNode->geometryNode_ = geometryNode;
    layoutWrapperNode->hostNode_ = frameNode;
    layoutWrapperNode->hostNode_.Upgrade()->tag_ = V2::LIST_ITEM_GROUP_COMPONENT_TAG;
    RefPtr<LayoutAlgorithmWrapper> layoutAlgorithmWrapper =
        AceType::MakeRefPtr<LayoutAlgorithmWrapper>(listLayoutAlgorithm);
    layoutWrapperNode->layoutAlgorithm_ = layoutAlgorithmWrapper;
    LayoutWrapperNode layoutWrapper(frameNode, geometryNode, listLayoutProperty);
    layoutWrapper.geometryNode_ = geometryNode;
    layoutWrapper.currentChildCount_ = 6;
    layoutWrapper.childrenMap_[5] = layoutWrapperNode;
    listLayoutAlgorithm->itemStartIndex_ = 0;
    listLayoutAlgorithm->isStackFromEnd_ = false;
    auto result = listLayoutAlgorithm->CheckNoNeedJumpListItemGroup(&layoutWrapper, 2, 3, 5, 2.0f);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: CheckNoNeedJumpListItemGroup003
 * @tc.desc: Test ListLayoutAlgorithm CheckNoNeedJumpListItemGroup
 * @tc.type: FUNC
 */
HWTEST_F(ListAlgorithmTestNg, CheckNoNeedJumpListItemGroup003, TestSize.Level1)
{
    RefPtr<ListPattern> listPattern = AceType::MakeRefPtr<ListPattern>();
    RefPtr<ListLayoutAlgorithm> listLayoutAlgorithm = AceType::MakeRefPtr<ListLayoutAlgorithm>(2);
    RefPtr<ListLayoutProperty> listLayoutProperty = AceType::MakeRefPtr<ListLayoutProperty>();
    auto frameNode = FrameNode::CreateFrameNode(V2::LIST_ITEM_GROUP_ETS_TAG, 2, listPattern);
    ASSERT_NE(frameNode, nullptr);
    frameNode->layoutProperty_ = listLayoutProperty;
    listPattern->frameNode_ = frameNode;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(geometryNode, nullptr);
    GeometryProperty geometryProperty;
    geometryNode->frame_ = geometryProperty;
    RefPtr<LayoutWrapperNode> layoutWrapperNode =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, listLayoutProperty);
    layoutWrapperNode->SetActive();
    layoutWrapperNode->geometryNode_ = geometryNode;
    layoutWrapperNode->hostNode_ = frameNode;
    layoutWrapperNode->hostNode_.Upgrade()->tag_ = V2::LIST_ITEM_GROUP_ETS_TAG;
    RefPtr<LayoutAlgorithmWrapper> layoutAlgorithmWrapper =
        AceType::MakeRefPtr<LayoutAlgorithmWrapper>(listLayoutAlgorithm);
    layoutWrapperNode->layoutAlgorithm_ = layoutAlgorithmWrapper;
    LayoutWrapperNode layoutWrapper(frameNode, geometryNode, listLayoutProperty);
    layoutWrapper.geometryNode_ = geometryNode;
    layoutWrapper.currentChildCount_ = 6;
    layoutWrapper.childrenMap_[5] = layoutWrapperNode;
    listLayoutAlgorithm->jumpIndexInGroup_ = std::nullopt;
    listLayoutAlgorithm->itemStartIndex_ = 0;
    listLayoutAlgorithm->isStackFromEnd_ = false;
    auto result = listLayoutAlgorithm->CheckNoNeedJumpListItemGroup(&layoutWrapper, 2, 3, 5, 2.0f);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: CheckNoNeedJumpListItemGroup004
 * @tc.desc: Test ListLayoutAlgorithm CheckNoNeedJumpListItemGroup
 * @tc.type: FUNC
 */
HWTEST_F(ListAlgorithmTestNg, CheckNoNeedJumpListItemGroup004, TestSize.Level1)
{
    RefPtr<ListPattern> listPattern = AceType::MakeRefPtr<ListPattern>();
    RefPtr<ListLayoutAlgorithm> listLayoutAlgorithm = AceType::MakeRefPtr<ListLayoutAlgorithm>(2);
    listLayoutAlgorithm->jumpIndexInGroup_ = 3;
    RefPtr<ListLayoutProperty> listLayoutProperty = AceType::MakeRefPtr<ListLayoutProperty>();
    auto frameNode = FrameNode::CreateFrameNode(V2::LIST_ITEM_GROUP_ETS_TAG, 2, listPattern);
    ASSERT_NE(frameNode, nullptr);
    frameNode->layoutProperty_ = listLayoutProperty;
    listPattern->frameNode_ = frameNode;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(geometryNode, nullptr);
    GeometryProperty geometryProperty;
    geometryNode->frame_ = geometryProperty;
    RefPtr<LayoutWrapperNode> layoutWrapperNode =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, listLayoutProperty);
    layoutWrapperNode->SetActive();
    layoutWrapperNode->geometryNode_ = geometryNode;
    layoutWrapperNode->hostNode_ = frameNode;
    layoutWrapperNode->hostNode_.Upgrade()->tag_ = V2::LIST_ITEM_GROUP_ETS_TAG;
    RefPtr<LayoutAlgorithmWrapper> layoutAlgorithmWrapper =
        AceType::MakeRefPtr<LayoutAlgorithmWrapper>(listLayoutAlgorithm);
    RefPtr<ListItemGroupLayoutAlgorithm> listItemGroupLayoutAlgorithm =
        AceType::MakeRefPtr<ListItemGroupLayoutAlgorithm>(0, 0, 2);
    ListItemGroupInfo listItemGroupInfo { 2, 2.0f, 4.0f, true };
    listItemGroupLayoutAlgorithm->itemPosition_[2] = listItemGroupInfo;
    layoutAlgorithmWrapper->layoutAlgorithm_ = listItemGroupLayoutAlgorithm;
    layoutWrapperNode->layoutAlgorithm_ = layoutAlgorithmWrapper;
    layoutWrapperNode->layoutProperty_ = listLayoutProperty;
    LayoutWrapperNode layoutWrapper(frameNode, geometryNode, listLayoutProperty);
    layoutWrapper.geometryNode_ = geometryNode;
    layoutWrapper.currentChildCount_ = 6;
    layoutWrapper.childrenMap_[5] = layoutWrapperNode;
    listLayoutAlgorithm->itemStartIndex_ = 0;
    listLayoutAlgorithm->isStackFromEnd_ = false;
    auto result = listLayoutAlgorithm->CheckNoNeedJumpListItemGroup(&layoutWrapper, 2, 6, 5, 2.0f);
    EXPECT_EQ(listLayoutAlgorithm->jumpIndexInGroup_, 3);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: CheckNoNeedJumpListItemGroup005
 * @tc.desc: Test ListLayoutAlgorithm CheckNoNeedJumpListItemGroup
 * @tc.type: FUNC
 */
HWTEST_F(ListAlgorithmTestNg, CheckNoNeedJumpListItemGroup005, TestSize.Level1)
{
    RefPtr<ListPattern> listPattern = AceType::MakeRefPtr<ListPattern>();
    RefPtr<ListLayoutAlgorithm> listLayoutAlgorithm = AceType::MakeRefPtr<ListLayoutAlgorithm>(2);
    listLayoutAlgorithm->jumpIndexInGroup_ = 3;
    RefPtr<ListLayoutProperty> listLayoutProperty = AceType::MakeRefPtr<ListLayoutProperty>();
    auto frameNode = FrameNode::CreateFrameNode(V2::LIST_ITEM_GROUP_ETS_TAG, 2, listPattern);
    ASSERT_NE(frameNode, nullptr);
    frameNode->layoutProperty_ = listLayoutProperty;
    listPattern->frameNode_ = frameNode;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(geometryNode, nullptr);
    GeometryProperty geometryProperty;
    geometryNode->frame_ = geometryProperty;
    RefPtr<LayoutWrapperNode> layoutWrapperNode =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, listLayoutProperty);
    layoutWrapperNode->SetActive();
    layoutWrapperNode->geometryNode_ = geometryNode;
    layoutWrapperNode->hostNode_ = frameNode;
    layoutWrapperNode->hostNode_.Upgrade()->tag_ = V2::LIST_ITEM_GROUP_ETS_TAG;
    RefPtr<LayoutAlgorithmWrapper> layoutAlgorithmWrapper =
        AceType::MakeRefPtr<LayoutAlgorithmWrapper>(listLayoutAlgorithm);
    RefPtr<ListItemGroupLayoutAlgorithm> listItemGroupLayoutAlgorithm =
        AceType::MakeRefPtr<ListItemGroupLayoutAlgorithm>(0, 0, 2);
    layoutAlgorithmWrapper->layoutAlgorithm_ = listItemGroupLayoutAlgorithm;
    layoutWrapperNode->layoutAlgorithm_ = layoutAlgorithmWrapper;
    layoutWrapperNode->layoutProperty_ = listLayoutProperty;
    LayoutWrapperNode layoutWrapper(frameNode, geometryNode, listLayoutProperty);
    layoutWrapper.geometryNode_ = geometryNode;
    layoutWrapper.currentChildCount_ = 6;
    layoutWrapper.childrenMap_[5] = layoutWrapperNode;
    listLayoutAlgorithm->itemStartIndex_ = 0;
    listLayoutAlgorithm->isStackFromEnd_ = false;
    listLayoutAlgorithm->jumpIndexInGroup_ = 0;
    auto result = listLayoutAlgorithm->CheckNoNeedJumpListItemGroup(&layoutWrapper, 2, 6, 5, 2.0f);
    EXPECT_EQ(listLayoutAlgorithm->scrollAutoType_, ScrollAutoType::NOT_CHANGE);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: NoNeedJump001
 * @tc.desc: Test ListLayoutAlgorithm NoNeedJump
 * @tc.type: FUNC
 */
HWTEST_F(ListAlgorithmTestNg, NoNeedJump001, TestSize.Level1)
{
    RefPtr<ListPattern> listPattern = AceType::MakeRefPtr<ListPattern>();
    RefPtr<ListLayoutAlgorithm> listLayoutAlgorithm = AceType::MakeRefPtr<ListLayoutAlgorithm>(2);
    RefPtr<ListLayoutProperty> listLayoutProperty = AceType::MakeRefPtr<ListLayoutProperty>();
    auto frameNode = FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, 2, listPattern);
    ASSERT_NE(frameNode, nullptr);
    frameNode->layoutProperty_ = listLayoutProperty;
    listPattern->frameNode_ = frameNode;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(geometryNode, nullptr);
    GeometryProperty geometryProperty;
    geometryNode->frame_ = geometryProperty;
    LayoutWrapperNode layoutWrapper(frameNode, geometryNode, listLayoutProperty);
    layoutWrapper.currentChildCount_ = 2;
    auto result = listLayoutAlgorithm->NoNeedJump(&layoutWrapper, 2.0f, 3.0f, 1, 2, 3, 2.0f);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: JudgeInOfScreenScrollAutoType001
 * @tc.desc: Test ListLayoutAlgorithm JudgeInOfScreenScrollAutoType
 * @tc.type: FUNC
 */
HWTEST_F(ListAlgorithmTestNg, JudgeInOfScreenScrollAutoType001, TestSize.Level1)
{
    RefPtr<ShallowBuilder> shallowBuilder = AceType::MakeRefPtr<ShallowBuilder>(nullptr);
    RefPtr<ListItemGroupPattern> listItemGroupPattern =
        AceType::MakeRefPtr<ListItemGroupPattern>(shallowBuilder, V2::ListItemGroupStyle::CARD);
    RefPtr<ListLayoutAlgorithm> listLayoutAlgorithm = AceType::MakeRefPtr<ListLayoutAlgorithm>(2);
    RefPtr<ListLayoutProperty> layoutProperty = AceType::MakeRefPtr<ListLayoutProperty>();
    layoutProperty->propStickyStyle_ = V2::StickyStyle::BOTH;
    auto frameNode = FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, 2, listItemGroupPattern);
    ASSERT_NE(frameNode, nullptr);
    frameNode->layoutProperty_ = layoutProperty;
    listItemGroupPattern->frameNode_ = frameNode;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(geometryNode, nullptr);
    GeometryProperty geometryProperty;
    geometryNode->frame_ = geometryProperty;
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, layoutProperty);
    layoutWrapper->hostNode_ = frameNode;
    listLayoutAlgorithm->startMainPos_ = 2.0f;
    listLayoutAlgorithm->endMainPos_ = 2.0f;
    auto result = listLayoutAlgorithm->JudgeInOfScreenScrollAutoType(layoutWrapper, layoutProperty, 2.0f, 6.0f);
    EXPECT_EQ(listLayoutAlgorithm->scrollAutoType_, ScrollAutoType::NOT_CHANGE);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: JudgeInOfScreenScrollAutoType002
 * @tc.desc: Test ListLayoutAlgorithm JudgeInOfScreenScrollAutoType
 * @tc.type: FUNC
 */
HWTEST_F(ListAlgorithmTestNg, JudgeInOfScreenScrollAutoType002, TestSize.Level1)
{
    RefPtr<ShallowBuilder> shallowBuilder = AceType::MakeRefPtr<ShallowBuilder>(nullptr);
    RefPtr<ListItemGroupPattern> listItemGroupPattern =
        AceType::MakeRefPtr<ListItemGroupPattern>(shallowBuilder, V2::ListItemGroupStyle::CARD);
    RefPtr<ListLayoutAlgorithm> listLayoutAlgorithm = AceType::MakeRefPtr<ListLayoutAlgorithm>(2);
    RefPtr<ListLayoutProperty> layoutProperty = AceType::MakeRefPtr<ListLayoutProperty>();
    layoutProperty->propStickyStyle_ = V2::StickyStyle::HEADER;
    auto frameNode = FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, 2, listItemGroupPattern);
    ASSERT_NE(frameNode, nullptr);
    frameNode->layoutProperty_ = layoutProperty;
    listItemGroupPattern->frameNode_ = frameNode;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(geometryNode, nullptr);
    GeometryProperty geometryProperty;
    geometryNode->frame_ = geometryProperty;
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, layoutProperty);
    layoutWrapper->hostNode_ = frameNode;
    listLayoutAlgorithm->startMainPos_ = 1.5f;
    listLayoutAlgorithm->endMainPos_ = 6.5f;
    listItemGroupPattern->headerMainSize_ = 4.0f;
    listItemGroupPattern->footerMainSize_ = 3.0f;
    auto result = listLayoutAlgorithm->JudgeInOfScreenScrollAutoType(layoutWrapper, layoutProperty, 2.0f, 6.0f);
    EXPECT_EQ(listLayoutAlgorithm->scrollAutoType_, ScrollAutoType::END);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: JudgeInOfScreenScrollAutoType003
 * @tc.desc: Test ListLayoutAlgorithm JudgeInOfScreenScrollAutoType
 * @tc.type: FUNC
 */
HWTEST_F(ListAlgorithmTestNg, JudgeInOfScreenScrollAutoType003, TestSize.Level1)
{
    RefPtr<ShallowBuilder> shallowBuilder = AceType::MakeRefPtr<ShallowBuilder>(nullptr);
    RefPtr<ListItemGroupPattern> listItemGroupPattern =
        AceType::MakeRefPtr<ListItemGroupPattern>(shallowBuilder, V2::ListItemGroupStyle::CARD);
    RefPtr<ListLayoutAlgorithm> listLayoutAlgorithm = AceType::MakeRefPtr<ListLayoutAlgorithm>(2);
    RefPtr<ListLayoutProperty> layoutProperty = AceType::MakeRefPtr<ListLayoutProperty>();
    layoutProperty->propStickyStyle_ = V2::StickyStyle::HEADER;
    auto frameNode = FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, 2, listItemGroupPattern);
    ASSERT_NE(frameNode, nullptr);
    frameNode->layoutProperty_ = layoutProperty;
    listItemGroupPattern->frameNode_ = frameNode;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(geometryNode, nullptr);
    GeometryProperty geometryProperty;
    geometryNode->frame_ = geometryProperty;
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, layoutProperty);
    layoutWrapper->hostNode_ = frameNode;
    listLayoutAlgorithm->startMainPos_ = 2.5f;
    listLayoutAlgorithm->endMainPos_ = 8.0f;
    listItemGroupPattern->headerMainSize_ = 4.0f;
    listItemGroupPattern->footerMainSize_ = 3.0f;
    auto result = listLayoutAlgorithm->JudgeInOfScreenScrollAutoType(layoutWrapper, layoutProperty, 2.0f, 6.0f);
    EXPECT_EQ(listLayoutAlgorithm->scrollAutoType_, ScrollAutoType::START);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: JudgeOutOfScreenScrollAutoType001
 * @tc.desc: Test ListLayoutAlgorithm JudgeOutOfScreenScrollAutoType
 * @tc.type: FUNC
 */
HWTEST_F(ListAlgorithmTestNg, JudgeOutOfScreenScrollAutoType001, TestSize.Level1)
{
    RefPtr<ShallowBuilder> shallowBuilder = AceType::MakeRefPtr<ShallowBuilder>(nullptr);
    RefPtr<ListItemGroupPattern> listItemGroupPattern =
        AceType::MakeRefPtr<ListItemGroupPattern>(shallowBuilder, V2::ListItemGroupStyle::CARD);
    RefPtr<ListLayoutAlgorithm> listLayoutAlgorithm = AceType::MakeRefPtr<ListLayoutAlgorithm>(2);
    RefPtr<ListLayoutProperty> layoutProperty = AceType::MakeRefPtr<ListLayoutProperty>();
    layoutProperty->propStickyStyle_ = V2::StickyStyle::HEADER;
    auto frameNode = FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, 2, listItemGroupPattern);
    ASSERT_NE(frameNode, nullptr);
    frameNode->layoutProperty_ = layoutProperty;
    listItemGroupPattern->frameNode_ = frameNode;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(geometryNode, nullptr);
    GeometryProperty geometryProperty;
    geometryNode->frame_ = geometryProperty;
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, layoutProperty);
    layoutWrapper->hostNode_ = frameNode;
    RefPtr<LayoutAlgorithmWrapper> layoutAlgorithmWrapper =
        AceType::MakeRefPtr<LayoutAlgorithmWrapper>(listLayoutAlgorithm);
    RefPtr<ListItemGroupLayoutAlgorithm> listItemGroupLayoutAlgorithm =
        AceType::MakeRefPtr<ListItemGroupLayoutAlgorithm>(0, 0, 2);
    listItemGroupLayoutAlgorithm->itemPosition_[2] = ListItemGroupInfo { 2, 2.0f, 4.0f, true };
    layoutAlgorithmWrapper->layoutAlgorithm_ = listItemGroupLayoutAlgorithm;
    layoutWrapper->layoutAlgorithm_ = layoutAlgorithmWrapper;
    listLayoutAlgorithm->startMainPos_ = 2.5f;
    listLayoutAlgorithm->endMainPos_ = 8.0f;
    listItemGroupPattern->headerMainSize_ = 4.0f;
    listItemGroupPattern->footerMainSize_ = 3.0f;
    listLayoutAlgorithm->JudgeOutOfScreenScrollAutoType(layoutWrapper, 2, layoutProperty, 2, 1, 2, 4);
    EXPECT_EQ(listLayoutAlgorithm->scrollAutoType_, ScrollAutoType::END);
}

/**
 * @tc.name: JudgeOutOfScreenScrollAutoType002
 * @tc.desc: Test ListLayoutAlgorithm JudgeOutOfScreenScrollAutoType
 * @tc.type: FUNC
 */
HWTEST_F(ListAlgorithmTestNg, JudgeOutOfScreenScrollAutoType002, TestSize.Level1)
{
    RefPtr<ShallowBuilder> shallowBuilder = AceType::MakeRefPtr<ShallowBuilder>(nullptr);
    RefPtr<ListItemGroupPattern> listItemGroupPattern =
        AceType::MakeRefPtr<ListItemGroupPattern>(shallowBuilder, V2::ListItemGroupStyle::CARD);
    RefPtr<ListLayoutAlgorithm> listLayoutAlgorithm = AceType::MakeRefPtr<ListLayoutAlgorithm>(2);
    RefPtr<ListLayoutProperty> layoutProperty = AceType::MakeRefPtr<ListLayoutProperty>();
    layoutProperty->propStickyStyle_ = V2::StickyStyle::HEADER;
    auto frameNode = FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, 2, listItemGroupPattern);
    ASSERT_NE(frameNode, nullptr);
    frameNode->layoutProperty_ = layoutProperty;
    listItemGroupPattern->frameNode_ = frameNode;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(geometryNode, nullptr);
    GeometryProperty geometryProperty;
    geometryNode->frame_ = geometryProperty;
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, layoutProperty);
    layoutWrapper->hostNode_ = frameNode;
    RefPtr<LayoutAlgorithmWrapper> layoutAlgorithmWrapper =
        AceType::MakeRefPtr<LayoutAlgorithmWrapper>(listLayoutAlgorithm);
    RefPtr<ListItemGroupLayoutAlgorithm> listItemGroupLayoutAlgorithm =
        AceType::MakeRefPtr<ListItemGroupLayoutAlgorithm>(0, 0, 2);
    listItemGroupLayoutAlgorithm->itemPosition_[2] = ListItemGroupInfo { 2, 2.0f, 4.0f, true };
    layoutAlgorithmWrapper->layoutAlgorithm_ = listItemGroupLayoutAlgorithm;
    layoutWrapper->layoutAlgorithm_ = layoutAlgorithmWrapper;
    listLayoutAlgorithm->startMainPos_ = 2.5f;
    listLayoutAlgorithm->endMainPos_ = 8.0f;
    listItemGroupPattern->headerMainSize_ = 4.0f;
    listItemGroupPattern->footerMainSize_ = 3.0f;
    listLayoutAlgorithm->JudgeOutOfScreenScrollAutoType(layoutWrapper, 2, layoutProperty, 2, 3, 1, 2);
    EXPECT_EQ(listLayoutAlgorithm->scrollAutoType_, ScrollAutoType::START);
}

/**
 * @tc.name: CheckJumpToIndex001
 * @tc.desc: Test ListLayoutAlgorithm CheckJumpToIndex
 * @tc.type: FUNC
 */
HWTEST_F(ListAlgorithmTestNg, CheckJumpToIndex001, TestSize.Level1)
{
    RefPtr<ListLayoutAlgorithm> listLayoutAlgorithm = AceType::MakeRefPtr<ListLayoutAlgorithm>(2);
    listLayoutAlgorithm->jumpIndex_ = std::nullopt;
    listLayoutAlgorithm->isNeedCheckOffset_ = true;
    listLayoutAlgorithm->childrenSize_ = nullptr;
    listLayoutAlgorithm->currentDelta_ = 5.0f;
    listLayoutAlgorithm->contentMainSize_ = 1.0f;
    listLayoutAlgorithm->posMap_ = AceType::MakeRefPtr<ListPositionMap>();
    ListItemGroupLayoutInfo groupInfo = { true, true, 4.0f, 2.0f, 4.0f, 2.0f };
    ListItemInfo listItemInfo = { 2, 2.0f, 4.0f, true, true, 1.0f, 2.0f, groupInfo };
    listLayoutAlgorithm->itemPosition_[0] = listItemInfo;
    listLayoutAlgorithm->CheckJumpToIndex();
    EXPECT_EQ(listLayoutAlgorithm->groupItemAverageHeight_, 4.0f);
}

/**
 * @tc.name: CheckJumpToIndex002
 * @tc.desc: Test ListLayoutAlgorithm CheckJumpToIndex
 * @tc.type: FUNC
 */
HWTEST_F(ListAlgorithmTestNg, CheckJumpToIndex002, TestSize.Level1)
{
    RefPtr<ListLayoutAlgorithm> listLayoutAlgorithm = AceType::MakeRefPtr<ListLayoutAlgorithm>(2);
    listLayoutAlgorithm->jumpIndex_ = std::nullopt;
    listLayoutAlgorithm->isNeedCheckOffset_ = true;
    listLayoutAlgorithm->childrenSize_ = nullptr;
    listLayoutAlgorithm->currentDelta_ = 5.0f;
    listLayoutAlgorithm->contentMainSize_ = 1.0f;
    listLayoutAlgorithm->posMap_ = AceType::MakeRefPtr<ListPositionMap>();
    ListItemInfo listItemInfo = { 2, 2.0f, 4.0f, true };
    listLayoutAlgorithm->itemPosition_[0] = listItemInfo;
    listLayoutAlgorithm->CheckJumpToIndex();
    EXPECT_EQ(listLayoutAlgorithm->groupItemAverageHeight_, 0.0f);
}

/**
 * @tc.name: CheckJumpToIndex003
 * @tc.desc: Test ListLayoutAlgorithm CheckJumpToIndex
 * @tc.type: FUNC
 */
HWTEST_F(ListAlgorithmTestNg, CheckJumpToIndex003, TestSize.Level1)
{
    RefPtr<ListLayoutAlgorithm> listLayoutAlgorithm = AceType::MakeRefPtr<ListLayoutAlgorithm>(2);
    listLayoutAlgorithm->jumpIndex_ = std::nullopt;
    listLayoutAlgorithm->isNeedCheckOffset_ = true;
    listLayoutAlgorithm->childrenSize_ = nullptr;
    listLayoutAlgorithm->currentDelta_ = -1.0f;
    listLayoutAlgorithm->contentMainSize_ = 0.0f;
    listLayoutAlgorithm->totalItemCount_ = 3;
    listLayoutAlgorithm->posMap_ = AceType::MakeRefPtr<ListPositionMap>();
    ListItemInfo listItemInfo = { 2, 2.0f, 4.0f, false };
    listLayoutAlgorithm->itemPosition_[2] = listItemInfo;
    listLayoutAlgorithm->CheckJumpToIndex();
    EXPECT_EQ(listLayoutAlgorithm->currentDelta_, -1.0f);
    EXPECT_EQ(listLayoutAlgorithm->jumpIndex_.value(), 1.0f);
}

/**
 * @tc.name: CheckJumpValid001
 * @tc.desc: Test ListLayoutAlgorithm CheckJumpValid
 * @tc.type: FUNC
 */
HWTEST_F(ListAlgorithmTestNg, CheckJumpValid001, TestSize.Level1)
{
    RefPtr<ListPattern> listPattern = AceType::MakeRefPtr<ListPattern>();
    RefPtr<ListLayoutAlgorithm> listLayoutAlgorithm = AceType::MakeRefPtr<ListLayoutAlgorithm>(2);
    RefPtr<ListLayoutProperty> listLayoutProperty = AceType::MakeRefPtr<ListLayoutProperty>();
    auto frameNode = FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, 2, listPattern);
    ASSERT_NE(frameNode, nullptr);
    frameNode->layoutProperty_ = listLayoutProperty;
    listPattern->frameNode_ = frameNode;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(geometryNode, nullptr);
    GeometryProperty geometryProperty;
    geometryNode->frame_ = geometryProperty;
    LayoutWrapperNode layoutWrapper(frameNode, geometryNode, listLayoutProperty);
    layoutWrapper.currentChildCount_ = 2;
    listLayoutAlgorithm->jumpIndex_ = LAST_ITEM;
    listLayoutAlgorithm->totalItemCount_ = 4;
    listLayoutAlgorithm->jumpIndexInGroup_ = std::nullopt;
    auto result = listLayoutAlgorithm->CheckJumpValid(&layoutWrapper);
    EXPECT_EQ(listLayoutAlgorithm->jumpIndex_.value(), 3);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: CheckJumpValid002
 * @tc.desc: Test ListLayoutAlgorithm CheckJumpValid
 * @tc.type: FUNC
 */
HWTEST_F(ListAlgorithmTestNg, CheckJumpValid002, TestSize.Level1)
{
    RefPtr<ListPattern> listPattern = AceType::MakeRefPtr<ListPattern>();
    RefPtr<ListLayoutAlgorithm> listLayoutAlgorithm = AceType::MakeRefPtr<ListLayoutAlgorithm>(2);
    RefPtr<ListLayoutProperty> listLayoutProperty = AceType::MakeRefPtr<ListLayoutProperty>();
    auto frameNode = FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, 2, listPattern);
    ASSERT_NE(frameNode, nullptr);
    frameNode->layoutProperty_ = listLayoutProperty;
    listPattern->frameNode_ = frameNode;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(geometryNode, nullptr);
    GeometryProperty geometryProperty;
    geometryNode->frame_ = geometryProperty;
    LayoutWrapperNode layoutWrapper(frameNode, geometryNode, listLayoutProperty);
    layoutWrapper.currentChildCount_ = 1;
    listLayoutAlgorithm->jumpIndex_ = LAST_ITEM;
    listLayoutAlgorithm->totalItemCount_ = 4;
    listLayoutAlgorithm->jumpIndexInGroup_ = 2;
    listLayoutAlgorithm->isStackFromEnd_ = false;
    auto result = listLayoutAlgorithm->CheckJumpValid(&layoutWrapper);
    EXPECT_EQ(listLayoutAlgorithm->jumpIndex_.value(), 3);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: CheckJumpValid003
 * @tc.desc: Test ListLayoutAlgorithm CheckJumpValid
 * @tc.type: FUNC
 */
HWTEST_F(ListAlgorithmTestNg, CheckJumpValid003, TestSize.Level1)
{
    RefPtr<ListPattern> listPattern = AceType::MakeRefPtr<ListPattern>();
    RefPtr<ListLayoutAlgorithm> listLayoutAlgorithm = AceType::MakeRefPtr<ListLayoutAlgorithm>(2);
    RefPtr<ListLayoutProperty> listLayoutProperty = AceType::MakeRefPtr<ListLayoutProperty>();
    auto frameNode = FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, 2, listPattern);
    ASSERT_NE(frameNode, nullptr);
    frameNode->layoutProperty_ = listLayoutProperty;
    listPattern->frameNode_ = frameNode;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(geometryNode, nullptr);
    GeometryProperty geometryProperty;
    geometryNode->frame_ = geometryProperty;
    RefPtr<LayoutWrapperNode> layoutWrapperNode =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, listLayoutProperty);
    layoutWrapperNode->SetActive();
    layoutWrapperNode->currentChildCount_ = 10;
    layoutWrapperNode->geometryNode_ = geometryNode;
    layoutWrapperNode->hostNode_ = frameNode;
    layoutWrapperNode->hostNode_.Upgrade()->tag_ = V2::LIST_ITEM_GROUP_COMPONENT_TAG;
    RefPtr<LayoutAlgorithmWrapper> layoutAlgorithmWrapper =
        AceType::MakeRefPtr<LayoutAlgorithmWrapper>(listLayoutAlgorithm);
    layoutWrapperNode->layoutAlgorithm_ = layoutAlgorithmWrapper;
    LayoutWrapperNode layoutWrapper(frameNode, geometryNode, listLayoutProperty);
    layoutWrapper.geometryNode_ = geometryNode;
    layoutWrapper.currentChildCount_ = 10;
    listLayoutAlgorithm->jumpIndex_ = LAST_ITEM;
    listLayoutAlgorithm->totalItemCount_ = 4;
    listLayoutAlgorithm->jumpIndexInGroup_ = 2;
    listLayoutAlgorithm->isStackFromEnd_ = true;
    layoutWrapper.childrenMap_[0] = layoutWrapperNode;
    listLayoutAlgorithm->itemStartIndex_ = 0;
    auto result = listLayoutAlgorithm->CheckJumpValid(&layoutWrapper);
    EXPECT_EQ(listLayoutAlgorithm->jumpIndexInGroup_.value(), 2);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: CheckJumpValid004
 * @tc.desc: Test ListLayoutAlgorithm CheckJumpValid
 * @tc.type: FUNC
 */
HWTEST_F(ListAlgorithmTestNg, CheckJumpValid004, TestSize.Level1)
{
    RefPtr<ShallowBuilder> shallowBuilder = AceType::MakeRefPtr<ShallowBuilder>(nullptr);
    RefPtr<ListItemGroupPattern> listItemGroupPattern =
        AceType::MakeRefPtr<ListItemGroupPattern>(shallowBuilder, V2::ListItemGroupStyle::CARD);
    listItemGroupPattern->itemStartIndex_ = 2;
    RefPtr<ListLayoutAlgorithm> listLayoutAlgorithm = AceType::MakeRefPtr<ListLayoutAlgorithm>(2);
    RefPtr<ListLayoutProperty> listLayoutProperty = AceType::MakeRefPtr<ListLayoutProperty>();
    auto frameNode = FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, 2, listItemGroupPattern);
    ASSERT_NE(frameNode, nullptr);
    frameNode->pattern_ = listItemGroupPattern;
    frameNode->layoutProperty_ = listLayoutProperty;
    listItemGroupPattern->frameNode_ = frameNode;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(geometryNode, nullptr);
    GeometryProperty geometryProperty;
    geometryNode->frame_ = geometryProperty;
    RefPtr<LayoutWrapperNode> layoutWrapperNode =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, listLayoutProperty);
    layoutWrapperNode->SetActive();
    layoutWrapperNode->geometryNode_ = geometryNode;
    layoutWrapperNode->hostNode_ = frameNode;
    layoutWrapperNode->hostNode_.Upgrade()->tag_ = V2::LIST_ITEM_GROUP_ETS_TAG;
    layoutWrapperNode->currentChildCount_ = 10;
    RefPtr<LayoutAlgorithmWrapper> layoutAlgorithmWrapper =
        AceType::MakeRefPtr<LayoutAlgorithmWrapper>(listLayoutAlgorithm);
    layoutWrapperNode->layoutAlgorithm_ = layoutAlgorithmWrapper;
    LayoutWrapperNode layoutWrapper(frameNode, geometryNode, listLayoutProperty);
    layoutWrapper.geometryNode_ = geometryNode;
    layoutWrapper.currentChildCount_ = 10;
    listLayoutAlgorithm->jumpIndex_ = LAST_ITEM;
    listLayoutAlgorithm->totalItemCount_ = 4;
    listLayoutAlgorithm->jumpIndexInGroup_ = -1;
    listLayoutAlgorithm->isStackFromEnd_ = true;
    layoutWrapper.childrenMap_[0] = layoutWrapperNode;
    listLayoutAlgorithm->itemStartIndex_ = 0;
    auto result = listLayoutAlgorithm->CheckJumpValid(&layoutWrapper);
    EXPECT_EQ(listLayoutAlgorithm->jumpIndexInGroup_.value(), 7);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: CheckJumpValid005
 * @tc.desc: Test ListLayoutAlgorithm CheckJumpValid
 * @tc.type: FUNC
 */
HWTEST_F(ListAlgorithmTestNg, CheckJumpValid005, TestSize.Level1)
{
    RefPtr<ShallowBuilder> shallowBuilder = AceType::MakeRefPtr<ShallowBuilder>(nullptr);
    RefPtr<ListItemGroupPattern> listItemGroupPattern =
        AceType::MakeRefPtr<ListItemGroupPattern>(shallowBuilder, V2::ListItemGroupStyle::CARD);
    listItemGroupPattern->itemStartIndex_ = 2;
    RefPtr<ListLayoutAlgorithm> listLayoutAlgorithm = AceType::MakeRefPtr<ListLayoutAlgorithm>(2);
    RefPtr<ListLayoutProperty> listLayoutProperty = AceType::MakeRefPtr<ListLayoutProperty>();
    auto frameNode = FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, 2, listItemGroupPattern);
    ASSERT_NE(frameNode, nullptr);
    frameNode->pattern_ = listItemGroupPattern;
    frameNode->layoutProperty_ = listLayoutProperty;
    listItemGroupPattern->frameNode_ = frameNode;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(geometryNode, nullptr);
    GeometryProperty geometryProperty;
    geometryNode->frame_ = geometryProperty;
    RefPtr<LayoutWrapperNode> layoutWrapperNode =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, listLayoutProperty);
    layoutWrapperNode->SetActive();
    layoutWrapperNode->geometryNode_ = geometryNode;
    layoutWrapperNode->hostNode_ = frameNode;
    layoutWrapperNode->hostNode_.Upgrade()->tag_ = V2::LIST_ITEM_GROUP_ETS_TAG;
    layoutWrapperNode->currentChildCount_ = 10;
    RefPtr<LayoutAlgorithmWrapper> layoutAlgorithmWrapper =
        AceType::MakeRefPtr<LayoutAlgorithmWrapper>(listLayoutAlgorithm);
    layoutWrapperNode->layoutAlgorithm_ = layoutAlgorithmWrapper;
    LayoutWrapperNode layoutWrapper(frameNode, geometryNode, listLayoutProperty);
    layoutWrapper.geometryNode_ = geometryNode;
    layoutWrapper.currentChildCount_ = 10;
    listLayoutAlgorithm->jumpIndex_ = LAST_ITEM;
    listLayoutAlgorithm->totalItemCount_ = 4;
    listLayoutAlgorithm->jumpIndexInGroup_ = 10;
    listLayoutAlgorithm->isStackFromEnd_ = true;
    layoutWrapper.childrenMap_[0] = layoutWrapperNode;
    listLayoutAlgorithm->itemStartIndex_ = 0;
    auto result = listLayoutAlgorithm->CheckJumpValid(&layoutWrapper);
    EXPECT_EQ(listLayoutAlgorithm->jumpIndexInGroup_.value(), 10);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: CheckAndMeasureStartItem001
 * @tc.desc: Test ListLayoutAlgorithm CheckAndMeasureStartItem
 * @tc.type: FUNC
 */
HWTEST_F(ListAlgorithmTestNg, CheckAndMeasureStartItem001, TestSize.Level1)
{
    RefPtr<ListPattern> listPattern = AceType::MakeRefPtr<ListPattern>();
    RefPtr<ListLayoutAlgorithm> listLayoutAlgorithm = AceType::MakeRefPtr<ListLayoutAlgorithm>(2);
    RefPtr<ListLayoutProperty> listLayoutProperty = AceType::MakeRefPtr<ListLayoutProperty>();
    auto frameNode = FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, 2, listPattern);
    ASSERT_NE(frameNode, nullptr);
    frameNode->layoutProperty_ = listLayoutProperty;
    listPattern->frameNode_ = frameNode;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(geometryNode, nullptr);
    GeometryProperty geometryProperty;
    geometryNode->frame_ = geometryProperty;
    LayoutWrapperNode layoutWrapper(frameNode, geometryNode, listLayoutProperty);
    layoutWrapper.currentChildCount_ = 2;
    listLayoutAlgorithm->totalItemCount_ = 4;
    listLayoutAlgorithm->prevContentMainSize_ = 1;
    listLayoutAlgorithm->isStackFromEnd_ = false;
    float startPos = 2.0f;
    listLayoutAlgorithm->CheckAndMeasureStartItem(&layoutWrapper, 2, startPos, true, false);
    EXPECT_EQ(startPos, 2.0f);
}

/**
 * @tc.name: CheckAndMeasureStartItem002
 * @tc.desc: Test ListLayoutAlgorithm CheckAndMeasureStartItem
 * @tc.type: FUNC
 */
HWTEST_F(ListAlgorithmTestNg, CheckAndMeasureStartItem002, TestSize.Level1)
{
    RefPtr<ListPattern> listPattern = AceType::MakeRefPtr<ListPattern>();
    RefPtr<ListLayoutAlgorithm> listLayoutAlgorithm = AceType::MakeRefPtr<ListLayoutAlgorithm>(2);
    RefPtr<ListLayoutProperty> listLayoutProperty = AceType::MakeRefPtr<ListLayoutProperty>();
    auto frameNode = FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, 2, listPattern);
    ASSERT_NE(frameNode, nullptr);
    frameNode->layoutProperty_ = listLayoutProperty;
    listPattern->frameNode_ = frameNode;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(geometryNode, nullptr);
    GeometryProperty geometryProperty;
    geometryNode->frame_ = geometryProperty;
    RefPtr<LayoutWrapperNode> layoutWrapperNode =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, listLayoutProperty);
    layoutWrapperNode->SetActive();
    layoutWrapperNode->currentChildCount_ = 10;
    layoutWrapperNode->geometryNode_ = geometryNode;
    layoutWrapperNode->hostNode_ = frameNode;
    layoutWrapperNode->hostNode_.Upgrade()->tag_ = V2::LIST_ITEM_GROUP_COMPONENT_TAG;
    RefPtr<LayoutAlgorithmWrapper> layoutAlgorithmWrapper =
        AceType::MakeRefPtr<LayoutAlgorithmWrapper>(listLayoutAlgorithm);
    layoutWrapperNode->layoutAlgorithm_ = layoutAlgorithmWrapper;
    LayoutWrapperNode layoutWrapper(frameNode, geometryNode, listLayoutProperty);
    layoutWrapper.geometryNode_ = geometryNode;
    layoutWrapper.currentChildCount_ = 10;
    listLayoutAlgorithm->totalItemCount_ = 4;
    std::pair<int32_t, ListItemInfo> firstItemInfo = { 1, { 2, 0.0f, 10.0f, false } };
    listLayoutAlgorithm->firstItemInfo_ = firstItemInfo;
    layoutWrapper.childrenMap_[2] = layoutWrapperNode;
    listLayoutAlgorithm->itemStartIndex_ = 0;
    listLayoutAlgorithm->isStackFromEnd_ = false;
    listLayoutAlgorithm->prevContentMainSize_ = 1;
    float startPos = 2.0f;
    listLayoutAlgorithm->CheckAndMeasureStartItem(&layoutWrapper, 2, startPos, true, false);
    EXPECT_EQ(startPos, 2.0f);
    EXPECT_EQ(listLayoutAlgorithm->firstItemInfo_.value().first, 1);
    EXPECT_EQ(listLayoutAlgorithm->firstItemInfo_.value().second.endPos, 10.0f);
}

/**
 * @tc.name: CheckAndMeasureStartItem003
 * @tc.desc: Test ListLayoutAlgorithm CheckAndMeasureStartItem
 * @tc.type: FUNC
 */
HWTEST_F(ListAlgorithmTestNg, CheckAndMeasureStartItem003, TestSize.Level1)
{
    RefPtr<ListPattern> listPattern = AceType::MakeRefPtr<ListPattern>();
    RefPtr<ListLayoutAlgorithm> listLayoutAlgorithm = AceType::MakeRefPtr<ListLayoutAlgorithm>(2);
    RefPtr<ListLayoutProperty> listLayoutProperty = AceType::MakeRefPtr<ListLayoutProperty>();
    auto frameNode = FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, 2, listPattern);
    ASSERT_NE(frameNode, nullptr);
    frameNode->layoutProperty_ = listLayoutProperty;
    listPattern->frameNode_ = frameNode;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(geometryNode, nullptr);
    GeometryProperty geometryProperty;
    geometryNode->frame_ = geometryProperty;
    RefPtr<LayoutWrapperNode> layoutWrapperNode =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, listLayoutProperty);
    layoutWrapperNode->SetActive();
    layoutWrapperNode->currentChildCount_ = 10;
    layoutWrapperNode->geometryNode_ = geometryNode;
    layoutWrapperNode->hostNode_ = frameNode;
    layoutWrapperNode->hostNode_.Upgrade()->tag_ = V2::LIST_ITEM_GROUP_ETS_TAG;
    RefPtr<LayoutAlgorithmWrapper> layoutAlgorithmWrapper =
        AceType::MakeRefPtr<LayoutAlgorithmWrapper>(listLayoutAlgorithm);
    RefPtr<ListItemGroupLayoutAlgorithm> listItemGroupLayoutAlgorithm =
        AceType::MakeRefPtr<ListItemGroupLayoutAlgorithm>(0, 0, 2);
    listItemGroupLayoutAlgorithm->refPos_ = 6.0f;
    layoutAlgorithmWrapper->layoutAlgorithm_ = listItemGroupLayoutAlgorithm;
    layoutWrapperNode->layoutAlgorithm_ = layoutAlgorithmWrapper;
    LayoutWrapperNode layoutWrapper(frameNode, geometryNode, listLayoutProperty);
    layoutWrapper.geometryNode_ = geometryNode;
    layoutWrapper.currentChildCount_ = 10;
    listLayoutAlgorithm->totalItemCount_ = 4;
    ListItemInfo listItemInfo = { 2, 2.0f, 4.0f, true };
    std::pair<int32_t, ListItemInfo> firstItemInfo = { 1, listItemInfo };
    listLayoutAlgorithm->firstItemInfo_ = firstItemInfo;
    layoutWrapper.childrenMap_[2] = layoutWrapperNode;
    listLayoutAlgorithm->itemStartIndex_ = 0;
    listLayoutAlgorithm->isStackFromEnd_ = false;
    listLayoutAlgorithm->prevContentMainSize_ = 1;
    float startPos = 2.0f;
    RefPtr<ListChildrenMainSize> listChildrenMainSize = AceType::MakeRefPtr<ListChildrenMainSize>();
    listLayoutAlgorithm->childrenSize_ = listChildrenMainSize;
    listLayoutAlgorithm->CheckAndMeasureStartItem(&layoutWrapper, 2, startPos, true, false);
    EXPECT_EQ(startPos, 2.0f);
    EXPECT_EQ(listLayoutAlgorithm->firstItemInfo_.value().second.startPos, 2.0f);
    EXPECT_EQ(listLayoutAlgorithm->firstItemInfo_.value().second.endPos, 2.0f);
}

/**
 * @tc.name: LayoutDirectionForTargetIndex001
 * @tc.desc: Test ListLayoutAlgorithm LayoutDirectionForTargetIndex
 * @tc.type: FUNC
 */
HWTEST_F(ListAlgorithmTestNg, LayoutDirectionForTargetIndex001, TestSize.Level1)
{
    RefPtr<ListPattern> listPattern = AceType::MakeRefPtr<ListPattern>();
    RefPtr<ListLayoutAlgorithm> listLayoutAlgorithm = AceType::MakeRefPtr<ListLayoutAlgorithm>(2);
    RefPtr<ListLayoutProperty> listLayoutProperty = AceType::MakeRefPtr<ListLayoutProperty>();
    auto frameNode = FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, 2, listPattern);
    ASSERT_NE(frameNode, nullptr);
    frameNode->layoutProperty_ = listLayoutProperty;
    listPattern->frameNode_ = frameNode;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(geometryNode, nullptr);
    GeometryProperty geometryProperty;
    geometryNode->frame_ = geometryProperty;
    LayoutWrapperNode layoutWrapper(frameNode, geometryNode, listLayoutProperty);
    layoutWrapper.currentChildCount_ = 1;
    listLayoutAlgorithm->totalItemCount_ = 4;
    listLayoutAlgorithm->targetIndex_ = 2;
    listLayoutAlgorithm->targetIndexInGroup_ = 2;
    listLayoutAlgorithm->isStackFromEnd_ = false;
    auto result = listLayoutAlgorithm->LayoutDirectionForTargetIndex(&layoutWrapper, 2);
    EXPECT_EQ(result, LayoutDirection::NONE);
}

/**
 * @tc.name: LayoutALineForward001
 * @tc.desc: Test ListLayoutAlgorithm LayoutALineForward
 * @tc.type: FUNC
 */
HWTEST_F(ListAlgorithmTestNg, LayoutALineForward001, TestSize.Level1)
{
    RefPtr<ListPattern> listPattern = AceType::MakeRefPtr<ListPattern>();
    RefPtr<ListLayoutAlgorithm> listLayoutAlgorithm = AceType::MakeRefPtr<ListLayoutAlgorithm>(2);
    RefPtr<ListLayoutProperty> listLayoutProperty = AceType::MakeRefPtr<ListLayoutProperty>();
    int32_t currentIndex = 2;
    float endPos = 4.0f;
    auto frameNode = FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, 2, listPattern);
    ASSERT_NE(frameNode, nullptr);
    frameNode->layoutProperty_ = listLayoutProperty;
    listPattern->frameNode_ = frameNode;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(geometryNode, nullptr);
    GeometryProperty geometryProperty;
    geometryNode->frame_ = geometryProperty;
    LayoutWrapperNode layoutWrapper(frameNode, geometryNode, listLayoutProperty);
    layoutWrapper.currentChildCount_ = 1;
    listLayoutAlgorithm->totalItemCount_ = 4;
    listLayoutAlgorithm->targetIndex_ = 2;
    listLayoutAlgorithm->targetIndexInGroup_ = 2;
    listLayoutAlgorithm->isStackFromEnd_ = false;
    listLayoutAlgorithm->firstItemInfo_ = std::nullopt;
    auto result = listLayoutAlgorithm->LayoutALineForward(&layoutWrapper, currentIndex, 2.0f, endPos);
    EXPECT_EQ(currentIndex, 2);
    EXPECT_EQ(endPos, 4.0f);
    EXPECT_EQ(result, 0);
}

/**
 * @tc.name: LayoutALineBackward001
 * @tc.desc: Test ListLayoutAlgorithm LayoutALineBackward
 * @tc.type: FUNC
 */
HWTEST_F(ListAlgorithmTestNg, LayoutALineBackward001, TestSize.Level1)
{
    RefPtr<ListPattern> listPattern = AceType::MakeRefPtr<ListPattern>();
    RefPtr<ListLayoutAlgorithm> listLayoutAlgorithm = AceType::MakeRefPtr<ListLayoutAlgorithm>(2);
    RefPtr<ListLayoutProperty> listLayoutProperty = AceType::MakeRefPtr<ListLayoutProperty>();
    int32_t currentIndex = 2;
    float startPos = 2.0f;
    auto frameNode = FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, 2, listPattern);
    ASSERT_NE(frameNode, nullptr);
    frameNode->layoutProperty_ = listLayoutProperty;
    listPattern->frameNode_ = frameNode;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(geometryNode, nullptr);
    GeometryProperty geometryProperty;
    geometryNode->frame_ = geometryProperty;
    LayoutWrapperNode layoutWrapper(frameNode, geometryNode, listLayoutProperty);
    layoutWrapper.currentChildCount_ = 1;
    listLayoutAlgorithm->totalItemCount_ = 4;
    listLayoutAlgorithm->targetIndex_ = 2;
    listLayoutAlgorithm->targetIndexInGroup_ = 2;
    listLayoutAlgorithm->isStackFromEnd_ = false;
    int32_t index = 1;
    ListItemInfo listItemInfo = { 2, 2.0f, 4.0f, true };
    listLayoutAlgorithm->firstItemInfo_ = std::make_pair(index, listItemInfo);
    auto result = listLayoutAlgorithm->LayoutALineBackward(&layoutWrapper, currentIndex, 4.0f, startPos);
    EXPECT_EQ(currentIndex, 1);
    EXPECT_EQ(startPos, 2.0f);
    EXPECT_FALSE(listLayoutAlgorithm->firstItemInfo_.has_value());
    EXPECT_EQ(result, 1);
}

/**
 * @tc.name: LayoutALineBackward002
 * @tc.desc: Test ListLayoutAlgorithm LayoutALineBackward
 * @tc.type: FUNC
 */
HWTEST_F(ListAlgorithmTestNg, LayoutALineBackward002, TestSize.Level1)
{
    RefPtr<ListPattern> listPattern = AceType::MakeRefPtr<ListPattern>();
    RefPtr<ListLayoutAlgorithm> listLayoutAlgorithm = AceType::MakeRefPtr<ListLayoutAlgorithm>(2);
    RefPtr<ListLayoutProperty> listLayoutProperty = AceType::MakeRefPtr<ListLayoutProperty>();
    int32_t currentIndex = 2;
    float startPos = 2.0f;
    auto frameNode = FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, 2, listPattern);
    ASSERT_NE(frameNode, nullptr);
    frameNode->layoutProperty_ = listLayoutProperty;
    listPattern->frameNode_ = frameNode;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(geometryNode, nullptr);
    GeometryProperty geometryProperty;
    geometryNode->frame_ = geometryProperty;
    LayoutWrapperNode layoutWrapper(frameNode, geometryNode, listLayoutProperty);
    layoutWrapper.currentChildCount_ = 1;
    listLayoutAlgorithm->totalItemCount_ = 4;
    listLayoutAlgorithm->targetIndex_ = 2;
    listLayoutAlgorithm->targetIndexInGroup_ = 2;
    listLayoutAlgorithm->isStackFromEnd_ = false;
    listLayoutAlgorithm->firstItemInfo_ = std::nullopt;
    auto result = listLayoutAlgorithm->LayoutALineBackward(&layoutWrapper, currentIndex, 4.0f, startPos);
    EXPECT_EQ(currentIndex, 2);
    EXPECT_EQ(startPos, 2.0f);
    EXPECT_EQ(result, 0);
}

/**
 * @tc.name: LayoutALineBackward003
 * @tc.desc: Test ListLayoutAlgorithm LayoutALineBackward
 * @tc.type: FUNC
 */
HWTEST_F(ListAlgorithmTestNg, LayoutALineBackward003, TestSize.Level1)
{
    RefPtr<ListPattern> listPattern = AceType::MakeRefPtr<ListPattern>();
    RefPtr<ListLayoutAlgorithm> listLayoutAlgorithm = AceType::MakeRefPtr<ListLayoutAlgorithm>(2);
    RefPtr<ListLayoutProperty> listLayoutProperty = AceType::MakeRefPtr<ListLayoutProperty>();
    int32_t currentIndex = 2;
    float startPos = 2.0f;
    auto frameNode = FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, 2, listPattern);
    ASSERT_NE(frameNode, nullptr);
    frameNode->layoutProperty_ = listLayoutProperty;
    listPattern->frameNode_ = frameNode;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(geometryNode, nullptr);
    GeometryProperty geometryProperty;
    geometryNode->frame_ = geometryProperty;
    LayoutWrapperNode layoutWrapper(frameNode, geometryNode, listLayoutProperty);
    layoutWrapper.currentChildCount_ = 1;
    listLayoutAlgorithm->totalItemCount_ = 4;
    listLayoutAlgorithm->targetIndex_ = 2;
    listLayoutAlgorithm->targetIndexInGroup_ = 2;
    listLayoutAlgorithm->isStackFromEnd_ = false;
    int32_t index = 3;
    ListItemInfo listItemInfo = { 2, 2.0f, 4.0f, true };
    listLayoutAlgorithm->firstItemInfo_ = std::make_pair(index, listItemInfo);
    auto result = listLayoutAlgorithm->LayoutALineBackward(&layoutWrapper, currentIndex, 4.0f, startPos);
    EXPECT_EQ(currentIndex, 2);
    EXPECT_EQ(startPos, 2.0f);
    EXPECT_EQ(result, 0);
}

/**
 * @tc.name: LayoutALineBackward004
 * @tc.desc: Test ListLayoutAlgorithm LayoutALineBackward
 * @tc.type: FUNC
 */
HWTEST_F(ListAlgorithmTestNg, LayoutALineBackward004, TestSize.Level1)
{
    RefPtr<ListPattern> listPattern = AceType::MakeRefPtr<ListPattern>();
    RefPtr<ListLayoutAlgorithm> listLayoutAlgorithm = AceType::MakeRefPtr<ListLayoutAlgorithm>(2);
    RefPtr<ListLayoutProperty> listLayoutProperty = AceType::MakeRefPtr<ListLayoutProperty>();
    int32_t currentIndex = 2;
    float startPos = 2.0f;
    auto frameNode = FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, 2, listPattern);
    ASSERT_NE(frameNode, nullptr);
    frameNode->layoutProperty_ = listLayoutProperty;
    listPattern->frameNode_ = frameNode;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(geometryNode, nullptr);
    GeometryProperty geometryProperty;
    geometryNode->frame_ = geometryProperty;
    LayoutWrapperNode layoutWrapper(frameNode, geometryNode, listLayoutProperty);
    layoutWrapper.currentChildCount_ = 1;
    listLayoutAlgorithm->totalItemCount_ = 4;
    listLayoutAlgorithm->targetIndex_ = 2;
    listLayoutAlgorithm->targetIndexInGroup_ = 2;
    listLayoutAlgorithm->isStackFromEnd_ = false;
    int32_t index = 1;
    ListItemInfo listItemInfo = { 2, 2.0f, 4.0f, true };
    listLayoutAlgorithm->firstItemInfo_ = std::make_pair(index, listItemInfo);
    auto result = listLayoutAlgorithm->LayoutALineBackward(&layoutWrapper, currentIndex, 4.0f, startPos);
    EXPECT_EQ(startPos, 2.0f);
    EXPECT_EQ(result, 1);
    EXPECT_EQ(currentIndex, 1);
    EXPECT_EQ(listLayoutAlgorithm->itemPosition_[1].startPos, 2.0f);
}

/**
 * @tc.name: LayoutBackward001
 * @tc.desc: Test ListLayoutAlgorithm LayoutBackward
 * @tc.type: FUNC
 */
HWTEST_F(ListAlgorithmTestNg, LayoutBackward001, TestSize.Level1)
{
    RefPtr<ListPattern> listPattern = AceType::MakeRefPtr<ListPattern>();
    RefPtr<ListLayoutAlgorithm> listLayoutAlgorithm = AceType::MakeRefPtr<ListLayoutAlgorithm>(2);
    RefPtr<ListLayoutProperty> listLayoutProperty = AceType::MakeRefPtr<ListLayoutProperty>();
    listLayoutProperty->propScrollSnapAlign_ = ScrollSnapAlign::CENTER;
    auto frameNode = FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, 2, listPattern);
    ASSERT_NE(frameNode, nullptr);
    frameNode->layoutProperty_ = listLayoutProperty;
    listPattern->frameNode_ = frameNode;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(geometryNode, nullptr);
    GeometryProperty geometryProperty;
    geometryNode->frame_ = geometryProperty;
    LayoutWrapperNode layoutWrapper(frameNode, geometryNode, listLayoutProperty);
    layoutWrapper.currentChildCount_ = 1;
    layoutWrapper.layoutProperty_ = listLayoutProperty;
    listLayoutAlgorithm->overScrollFeature_ = true;
    listLayoutAlgorithm->backwardFeature_ = false;
    listLayoutAlgorithm->prevContentMainSize_ = 2.0f;
    listLayoutAlgorithm->currentOffset_ = 3.0f;
    listLayoutAlgorithm->contentMainSize_ = 10.0f;
    listLayoutAlgorithm->contentStartOffset_ = 1.0f;
    listLayoutAlgorithm->contentEndOffset_ = 8.0f;
    listLayoutAlgorithm->startMainPos_ = 2.0f;
    listLayoutAlgorithm->totalItemCount_ = 2;
    ListItemInfo listItemInfo = { 2, 2.0f, 4.0f, false };
    listLayoutAlgorithm->itemPosition_[1] = listItemInfo;
    listLayoutAlgorithm->LayoutBackward(&layoutWrapper, -1, 4.0f);
    EXPECT_EQ(listLayoutAlgorithm->currentOffset_, 11.0f);
    EXPECT_EQ(listLayoutAlgorithm->contentMainSize_, 5.0f);
}

/**
 * @tc.name: FixPredictSnapPos001
 * @tc.desc: Test ListLayoutAlgorithm FixPredictSnapPos
 * @tc.type: FUNC
 */
HWTEST_F(ListAlgorithmTestNg, FixPredictSnapPos001, TestSize.Level1)
{
    RefPtr<ListLayoutAlgorithm> listLayoutAlgorithm = AceType::MakeRefPtr<ListLayoutAlgorithm>(2);
    listLayoutAlgorithm->predictSnapEndPos_ = 2.0f;
    ListItemInfo listItemInfo = { 2, 2.0f, 4.0f, false };
    listLayoutAlgorithm->itemPosition_[1] = listItemInfo;
    listLayoutAlgorithm->FixPredictSnapPos();
    EXPECT_EQ(listLayoutAlgorithm->scrollSnapAlign_, ScrollSnapAlign::NONE);
    EXPECT_EQ(listLayoutAlgorithm->predictSnapEndPos_, 2.0f);
}

/**
 * @tc.name: FixPredictSnapOffset001
 * @tc.desc: Test ListLayoutAlgorithm FixPredictSnapOffset
 * @tc.type: FUNC
 */
HWTEST_F(ListAlgorithmTestNg, FixPredictSnapOffset001, TestSize.Level1)
{
    RefPtr<ListLayoutAlgorithm> listLayoutAlgorithm = AceType::MakeRefPtr<ListLayoutAlgorithm>(2);
    RefPtr<ListLayoutProperty> listLayoutProperty = AceType::MakeRefPtr<ListLayoutProperty>();
    listLayoutAlgorithm->predictSnapEndPos_ = 2.0f;
    listLayoutAlgorithm->predictSnapOffset_ = 2.0f;
    ListItemInfo listItemInfo = { 2, 2.0f, 4.0f, false };
    listLayoutAlgorithm->itemPosition_[1] = listItemInfo;
    listLayoutAlgorithm->FixPredictSnapOffset(listLayoutProperty);
    EXPECT_FALSE(listLayoutAlgorithm->predictSnapOffset_.has_value());
    EXPECT_FALSE(listLayoutAlgorithm->predictSnapEndPos_.has_value());
}

/**
 * @tc.name: FixPredictSnapOffset002
 * @tc.desc: Test ListLayoutAlgorithm FixPredictSnapOffset
 * @tc.type: FUNC
 */
HWTEST_F(ListAlgorithmTestNg, FixPredictSnapOffset002, TestSize.Level1)
{
    RefPtr<ListLayoutAlgorithm> listLayoutAlgorithm = AceType::MakeRefPtr<ListLayoutAlgorithm>(2);
    RefPtr<ListLayoutProperty> listLayoutProperty = AceType::MakeRefPtr<ListLayoutProperty>();
    listLayoutAlgorithm->predictSnapEndPos_ = 2.0f;
    listLayoutAlgorithm->predictSnapOffset_ = 2.0f;
    listLayoutAlgorithm->scrollSnapAlign_ = ScrollSnapAlign::CENTER;
    ListItemInfo listItemInfo = { 2, 2.0f, 4.0f, false };
    listLayoutAlgorithm->itemPosition_[1] = listItemInfo;
    listLayoutAlgorithm->itemPosition_[2] = { 2, 3.0f, 4.0f, false };
    listLayoutAlgorithm->FixPredictSnapOffset(listLayoutProperty);
    EXPECT_EQ(listLayoutAlgorithm->predictSnapOffset_, 2.0f);
    EXPECT_EQ(listLayoutAlgorithm->predictSnapEndPos_, -2.0f);
}

/**
 * @tc.name: FixPredictSnapOffset003
 * @tc.desc: Test ListLayoutAlgorithm FixPredictSnapOffset
 * @tc.type: FUNC
 */
HWTEST_F(ListAlgorithmTestNg, FixPredictSnapOffset003, TestSize.Level1)
{
    RefPtr<ListLayoutAlgorithm> listLayoutAlgorithm = AceType::MakeRefPtr<ListLayoutAlgorithm>(2);
    RefPtr<ListLayoutProperty> listLayoutProperty = AceType::MakeRefPtr<ListLayoutProperty>();
    listLayoutAlgorithm->scrollSnapVelocity_ = 1000.0f;
    listLayoutAlgorithm->predictSnapOffset_ = 10.0f;
    listLayoutAlgorithm->scrollSnapAlign_ = ScrollSnapAlign::CENTER;
    ListItemInfo listItemInfo = { 2, -100.0f, 100.0f, false };
    listLayoutAlgorithm->itemPosition_[1] = listItemInfo;
    listLayoutAlgorithm->FixPredictSnapOffset(listLayoutProperty);
    EXPECT_EQ(listLayoutAlgorithm->predictSnapOffset_, 0.0f);
    EXPECT_EQ(listLayoutAlgorithm->predictSnapEndPos_, 0.0f);
}

/**
 * @tc.name: FixPredictSnapOffsetAlignStart001
 * @tc.desc: Test ListLayoutAlgorithm FixPredictSnapOffsetAlignStart
 * @tc.type: FUNC
 */
HWTEST_F(ListAlgorithmTestNg, FixPredictSnapOffsetAlignStart001, TestSize.Level1)
{
    RefPtr<ListLayoutAlgorithm> listLayoutAlgorithm = AceType::MakeRefPtr<ListLayoutAlgorithm>(2);
    listLayoutAlgorithm->predictSnapEndPos_ = 2.0f;
    listLayoutAlgorithm->predictSnapOffset_ = 2.0f;
    listLayoutAlgorithm->scrollSnapAlign_ = ScrollSnapAlign::CENTER;
    listLayoutAlgorithm->FixPredictSnapOffsetAlignStart();
    EXPECT_EQ(listLayoutAlgorithm->predictSnapOffset_, 2.0f);
    EXPECT_EQ(listLayoutAlgorithm->predictSnapEndPos_, 2.0f);
}

/**
 * @tc.name: FixPredictSnapOffsetAlignCenter001
 * @tc.desc: Test ListLayoutAlgorithm FixPredictSnapOffsetAlignCenter
 * @tc.type: FUNC
 */
HWTEST_F(ListAlgorithmTestNg, FixPredictSnapOffsetAlignCenter001, TestSize.Level1)
{
    RefPtr<ListLayoutAlgorithm> listLayoutAlgorithm = AceType::MakeRefPtr<ListLayoutAlgorithm>(2);
    listLayoutAlgorithm->predictSnapEndPos_ = 2.0f;
    listLayoutAlgorithm->predictSnapOffset_ = 2.0f;
    listLayoutAlgorithm->scrollSnapAlign_ = ScrollSnapAlign::CENTER;
    listLayoutAlgorithm->FixPredictSnapOffsetAlignCenter();
    EXPECT_EQ(listLayoutAlgorithm->predictSnapOffset_, 2.0f);
    EXPECT_EQ(listLayoutAlgorithm->predictSnapEndPos_, 2.0f);
}

/**
 * @tc.name: FixPredictSnapOffsetAlignCenter002
 * @tc.desc: Test ListLayoutAlgorithm FixPredictSnapOffsetAlignCenter
 * @tc.type: FUNC
 */
HWTEST_F(ListAlgorithmTestNg, FixPredictSnapOffsetAlignCenter002, TestSize.Level1)
{
    RefPtr<ListLayoutAlgorithm> listLayoutAlgorithm = AceType::MakeRefPtr<ListLayoutAlgorithm>(2);
    listLayoutAlgorithm->predictSnapEndPos_ = 2.0f;
    listLayoutAlgorithm->predictSnapOffset_ = 2.0f;
    listLayoutAlgorithm->totalOffset_ = 2.0f;
    listLayoutAlgorithm->spaceWidth_ = 6.0f;
    listLayoutAlgorithm->contentMainSize_ = 1.0f;
    listLayoutAlgorithm->scrollSnapAlign_ = ScrollSnapAlign::CENTER;
    listLayoutAlgorithm->isSpringEffect_ = true;
    ListItemInfo listItemInfo = { 2, 2.0f, 4.0f, false };
    listLayoutAlgorithm->itemPosition_[1] = listItemInfo;
    listLayoutAlgorithm->FixPredictSnapOffsetAlignCenter();
    EXPECT_EQ(listLayoutAlgorithm->predictSnapOffset_, 2.0f);
    EXPECT_EQ(listLayoutAlgorithm->predictSnapEndPos_, 2.0f);
}

/**
 * @tc.name: FixPredictSnapOffsetAlignCenter003
 * @tc.desc: Test ListLayoutAlgorithm FixPredictSnapOffsetAlignCenter
 * @tc.type: FUNC
 */
HWTEST_F(ListAlgorithmTestNg, FixPredictSnapOffsetAlignCenter003, TestSize.Level1)
{
    RefPtr<ListLayoutAlgorithm> listLayoutAlgorithm = AceType::MakeRefPtr<ListLayoutAlgorithm>(2);
    listLayoutAlgorithm->predictSnapEndPos_ = 2.0f;
    listLayoutAlgorithm->predictSnapOffset_ = 2.0f;
    listLayoutAlgorithm->totalOffset_ = 2.0f;
    listLayoutAlgorithm->spaceWidth_ = 6.0f;
    listLayoutAlgorithm->contentMainSize_ = 1.0f;
    listLayoutAlgorithm->scrollSnapAlign_ = ScrollSnapAlign::CENTER;
    listLayoutAlgorithm->isSpringEffect_ = false;
    ListItemInfo listItemInfo = { 2, 2.0f, 4.0f, false };
    listLayoutAlgorithm->itemPosition_[1] = listItemInfo;
    listLayoutAlgorithm->FixPredictSnapOffsetAlignCenter();
    EXPECT_EQ(listLayoutAlgorithm->predictSnapOffset_, 1.5f);
    EXPECT_EQ(listLayoutAlgorithm->predictSnapEndPos_, 0.5f);
}

/**
 * @tc.name: FixPredictSnapOffsetAlignCenter004
 * @tc.desc: Test ListLayoutAlgorithm FixPredictSnapOffsetAlignCenter
 * @tc.type: FUNC
 */
HWTEST_F(ListAlgorithmTestNg, FixPredictSnapOffsetAlignCenter004, TestSize.Level1)
{
    RefPtr<ListLayoutAlgorithm> listLayoutAlgorithm = AceType::MakeRefPtr<ListLayoutAlgorithm>(2);
    listLayoutAlgorithm->predictSnapEndPos_ = 2.0f;
    listLayoutAlgorithm->predictSnapOffset_ = 2.0f;
    listLayoutAlgorithm->totalOffset_ = 4.0f;
    listLayoutAlgorithm->spaceWidth_ = 6.0f;
    listLayoutAlgorithm->contentMainSize_ = 8.0f;
    listLayoutAlgorithm->totalItemCount_ = 1;
    listLayoutAlgorithm->scrollSnapAlign_ = ScrollSnapAlign::CENTER;
    listLayoutAlgorithm->isSpringEffect_ = true;
    ListItemInfo listItemInfo = { 2, 2.0f, 4.0f, false };
    listLayoutAlgorithm->itemPosition_[1] = listItemInfo;
    listLayoutAlgorithm->FixPredictSnapOffsetAlignCenter();
    EXPECT_EQ(listLayoutAlgorithm->predictSnapOffset_, 2.0f);
    EXPECT_EQ(listLayoutAlgorithm->predictSnapEndPos_, 2.0f);
}

/**
 * @tc.name: FixPredictSnapOffsetAlignCenter005
 * @tc.desc: Test ListLayoutAlgorithm FixPredictSnapOffsetAlignCenter
 * @tc.type: FUNC
 */
HWTEST_F(ListAlgorithmTestNg, FixPredictSnapOffsetAlignCenter005, TestSize.Level1)
{
    RefPtr<ListLayoutAlgorithm> listLayoutAlgorithm = AceType::MakeRefPtr<ListLayoutAlgorithm>(2);
    listLayoutAlgorithm->predictSnapEndPos_ = 2.0f;
    listLayoutAlgorithm->predictSnapOffset_ = 2.0f;
    listLayoutAlgorithm->totalOffset_ = 4.0f;
    listLayoutAlgorithm->spaceWidth_ = 6.0f;
    listLayoutAlgorithm->contentMainSize_ = 8.0f;
    listLayoutAlgorithm->totalItemCount_ = 1;
    listLayoutAlgorithm->scrollSnapAlign_ = ScrollSnapAlign::CENTER;
    listLayoutAlgorithm->isSpringEffect_ = false;
    ListItemInfo listItemInfo = { 2, 2.0f, 4.0f, false };
    listLayoutAlgorithm->itemPosition_[1] = listItemInfo;
    listLayoutAlgorithm->FixPredictSnapOffsetAlignCenter();
    EXPECT_EQ(listLayoutAlgorithm->predictSnapOffset_, 7.0f);
    EXPECT_EQ(listLayoutAlgorithm->predictSnapEndPos_, -3.0f);
}

/**
 * @tc.name: FixPredictSnapOffsetAlignEnd001
 * @tc.desc: Test ListLayoutAlgorithm FixPredictSnapOffsetAlignEnd
 * @tc.type: FUNC
 */
HWTEST_F(ListAlgorithmTestNg, FixPredictSnapOffsetAlignEnd001, TestSize.Level1)
{
    RefPtr<ListLayoutAlgorithm> listLayoutAlgorithm = AceType::MakeRefPtr<ListLayoutAlgorithm>(2);
    listLayoutAlgorithm->predictSnapEndPos_ = 5.0f;
    listLayoutAlgorithm->predictSnapOffset_ = 6.0f;
    listLayoutAlgorithm->scrollSnapAlign_ = ScrollSnapAlign::END;
    listLayoutAlgorithm->FixPredictSnapOffsetAlignEnd();
    EXPECT_EQ(listLayoutAlgorithm->predictSnapOffset_, 6.0f);
    EXPECT_EQ(listLayoutAlgorithm->predictSnapEndPos_, 5.0f);
}

/**
 * @tc.name: CalculateLaneCrossOffset001
 * @tc.desc: Test ListLayoutAlgorithm CalculateLaneCrossOffset
 * @tc.type: FUNC
 */
HWTEST_F(ListAlgorithmTestNg, CalculateLaneCrossOffset001, TestSize.Level1)
{
    RefPtr<ListLayoutAlgorithm> listLayoutAlgorithm = AceType::MakeRefPtr<ListLayoutAlgorithm>(2);
    listLayoutAlgorithm->predictSnapEndPos_ = 2.0f;
    listLayoutAlgorithm->predictSnapOffset_ = 2.0f;
    listLayoutAlgorithm->totalOffset_ = 6.0f;
    int32_t number = 6;
    listLayoutAlgorithm->listItemAlign_ = static_cast<OHOS::Ace::V2::ListItemAlign>(number);
    auto result = listLayoutAlgorithm->CalculateLaneCrossOffset(3.0f, 2.0f, true);
    EXPECT_EQ(result, 0.0f);
}

/**
 * @tc.name: OnSurfaceChanged001
 * @tc.desc: Test ListLayoutAlgorithm OnSurfaceChanged
 * @tc.type: FUNC
 */
HWTEST_F(ListAlgorithmTestNg, OnSurfaceChanged001, TestSize.Level1)
{
    RefPtr<ListPattern> listPattern = AceType::MakeRefPtr<ListPattern>();
    RefPtr<ListLayoutAlgorithm> listLayoutAlgorithm = AceType::MakeRefPtr<ListLayoutAlgorithm>(2);
    RefPtr<ListLayoutProperty> listLayoutProperty = AceType::MakeRefPtr<ListLayoutProperty>();
    auto frameNode = FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, 2, listPattern);
    ASSERT_NE(frameNode, nullptr);
    WeakPtr<FrameNode> node = frameNode;
    RefPtr<FocusHub> focusHub = AceType::MakeRefPtr<FocusHub>(node);
    focusHub->currentFocus_ = true;
    frameNode->focusHub_ = focusHub;
    listPattern->frameNode_ = frameNode;
    frameNode->layoutProperty_ = listLayoutProperty;
    listPattern->frameNode_ = frameNode;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(geometryNode, nullptr);
    GeometryProperty geometryProperty;
    geometryNode->frame_ = geometryProperty;
    LayoutWrapperNode layoutWrapper(frameNode, geometryNode, listLayoutProperty);
    layoutWrapper.layoutProperty_ = listLayoutProperty;
    layoutWrapper.hostNode_ = frameNode;
    listLayoutAlgorithm->contentMainSize_ = 3.0f;
    listLayoutAlgorithm->prevContentMainSize_ = 5.0f;
    listLayoutAlgorithm->currentDelta_ = 2.0f;
    listLayoutAlgorithm->OnSurfaceChanged(&layoutWrapper);
    EXPECT_EQ(listLayoutAlgorithm->currentDelta_, 2.0f);
}

/**
 * @tc.name: LayoutCachedALine001
 * @tc.desc: Test ListLayoutAlgorithm LayoutCachedALine
 * @tc.type: FUNC
 */
HWTEST_F(ListAlgorithmTestNg, LayoutCachedALine001, TestSize.Level1)
{
    RefPtr<ListPattern> listPattern = AceType::MakeRefPtr<ListPattern>();
    RefPtr<ListLayoutAlgorithm> listLayoutAlgorithm = AceType::MakeRefPtr<ListLayoutAlgorithm>(2);
    RefPtr<ListLayoutProperty> listLayoutProperty = AceType::MakeRefPtr<ListLayoutProperty>();
    auto frameNode = FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, 2, listPattern);
    ASSERT_NE(frameNode, nullptr);
    frameNode->layoutProperty_ = listLayoutProperty;
    listPattern->frameNode_ = frameNode;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(geometryNode, nullptr);
    GeometryProperty geometryProperty;
    geometryNode->frame_ = geometryProperty;
    LayoutWrapperNode layoutWrapper(frameNode, geometryNode, listLayoutProperty);
    layoutWrapper.currentChildCount_ = 1;
    listLayoutAlgorithm->itemStartIndex_ = 2;
    float currPos = 4.0f;
    auto result = listLayoutAlgorithm->LayoutCachedALine(&layoutWrapper, 4, true, currPos, 2.0f);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: LayoutCachedItem001
 * @tc.desc: Test ListLayoutAlgorithm LayoutCachedItem
 * @tc.type: FUNC
 */
HWTEST_F(ListAlgorithmTestNg, LayoutCachedItem001, TestSize.Level1)
{
    RefPtr<ListPattern> listPattern = AceType::MakeRefPtr<ListPattern>();
    RefPtr<ListLayoutAlgorithm> listLayoutAlgorithm = AceType::MakeRefPtr<ListLayoutAlgorithm>(2);
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
    ListItemInfo listItemInfo = { 2, 2.0f, 4.0f, false };
    listLayoutAlgorithm->itemPosition_[1] = listItemInfo;
    listLayoutAlgorithm->spaceWidth_ = 2;
    listLayoutAlgorithm->totalItemCount_ = 3;
    listLayoutAlgorithm->itemStartIndex_ = 2;
    auto result = listLayoutAlgorithm->LayoutCachedItem(&layoutWrapper, 4);
    auto it = result.begin();
    EXPECT_EQ(*it, 2);
    EXPECT_EQ(*(++it), 0);
}

/**
 * @tc.name: LayoutCachedItem002
 * @tc.desc: Test ListLayoutAlgorithm LayoutCachedItem
 * @tc.type: FUNC
 */
HWTEST_F(ListAlgorithmTestNg, LayoutCachedItem002, TestSize.Level1)
{
    RefPtr<ListPattern> listPattern = AceType::MakeRefPtr<ListPattern>();
    RefPtr<ListLayoutAlgorithm> listLayoutAlgorithm = AceType::MakeRefPtr<ListLayoutAlgorithm>(2);
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
    ListItemInfo listItemInfo = { 2, 2.0f, 4.0f, false };
    listLayoutAlgorithm->itemPosition_[-1] = listItemInfo;
    listLayoutAlgorithm->spaceWidth_ = 2;
    listLayoutAlgorithm->totalItemCount_ = 3;
    listLayoutAlgorithm->itemStartIndex_ = 2;
    auto result = listLayoutAlgorithm->LayoutCachedItem(&layoutWrapper, 4);
    auto it = result.begin();
    EXPECT_EQ(*it, 0);
    EXPECT_EQ(*(++it), 1);
}

/**
 * @tc.name: LayoutCachedItem003
 * @tc.desc: Test ListLayoutAlgorithm LayoutCachedItem
 * @tc.type: FUNC
 */
HWTEST_F(ListAlgorithmTestNg, LayoutCachedItem003, TestSize.Level1)
{
    RefPtr<ListPattern> listPattern = AceType::MakeRefPtr<ListPattern>();
    RefPtr<ListLayoutAlgorithm> listLayoutAlgorithm = AceType::MakeRefPtr<ListLayoutAlgorithm>(2);
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
    ListItemInfo listItemInfo = { 2, 2.0f, 4.0f, false };
    listLayoutAlgorithm->itemPosition_[1] = listItemInfo;
    listLayoutAlgorithm->spaceWidth_ = 2;
    listLayoutAlgorithm->totalItemCount_ = 3;
    listLayoutAlgorithm->itemStartIndex_ = 2;
    auto result = listLayoutAlgorithm->LayoutCachedItem(&layoutWrapper, 0);
    EXPECT_TRUE(result.empty());
}

/**
 * @tc.name: PredictBuildItem001
 * @tc.desc: Test ListLayoutAlgorithm PredictBuildItem
 * @tc.type: FUNC
 */
HWTEST_F(ListAlgorithmTestNg, PredictBuildItem001, TestSize.Level1)
{
    RefPtr<ListPattern> listPattern = AceType::MakeRefPtr<ListPattern>();
    RefPtr<ListLayoutAlgorithm> listLayoutAlgorithm = AceType::MakeRefPtr<ListLayoutAlgorithm>(2);
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
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, listLayoutProperty);
    layoutWrapper->geometryNode_ = geometryNode;
    layoutWrapper->hostNode_ = frameNode;
    layoutWrapper->hostNode_.Upgrade()->tag_ = V2::LIST_ITEM_GROUP_ETS_TAG;
    ListItemInfo listItemInfo = { 2, 2.0f, 4.0f, false };
    listLayoutAlgorithm->itemPosition_[1] = listItemInfo;
    listLayoutAlgorithm->spaceWidth_ = 2;
    listLayoutAlgorithm->totalItemCount_ = 3;
    listLayoutAlgorithm->itemStartIndex_ = 2;
    std::optional<float> width = 5.0f;
    std::optional<float> height = 8.0f;
    OptionalSizeF selfIdealSize(width, height);
    OptionalSizeF parentIdealSize(width, height);
    ViewPosReference viewPosRef = { 5.0f, 5.0f, 5.0f, ReferenceEdge::END, Axis::FREE };
    LayoutConstraintF layoutConstraint;
    layoutConstraint.selfIdealSize = selfIdealSize;
    layoutConstraint.parentIdealSize = parentIdealSize;
    layoutConstraint.viewPosRef = viewPosRef;
    auto result = listLayoutAlgorithm->PredictBuildItem(layoutWrapper, layoutConstraint);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: PredictBuildItem002
 * @tc.desc: Test ListLayoutAlgorithm PredictBuildItem
 * @tc.type: FUNC
 */
HWTEST_F(ListAlgorithmTestNg, PredictBuildItem002, TestSize.Level1)
{
    RefPtr<ListPattern> listPattern = AceType::MakeRefPtr<ListPattern>();
    RefPtr<ListLayoutAlgorithm> listLayoutAlgorithm = AceType::MakeRefPtr<ListLayoutAlgorithm>(2);
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
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, listLayoutProperty);
    layoutWrapper->geometryNode_ = geometryNode;
    layoutWrapper->hostNode_ = frameNode;
    layoutWrapper->hostNode_.Upgrade()->tag_ = V2::LIST_ETS_TAG;
    ListItemInfo listItemInfo = { 2, 2.0f, 4.0f, false };
    listLayoutAlgorithm->itemPosition_[1] = listItemInfo;
    listLayoutAlgorithm->spaceWidth_ = 2;
    listLayoutAlgorithm->totalItemCount_ = 3;
    listLayoutAlgorithm->itemStartIndex_ = 2;
    std::optional<float> width = 5.0f;
    std::optional<float> height = 8.0f;
    OptionalSizeF selfIdealSize(width, height);
    OptionalSizeF parentIdealSize(width, height);
    ViewPosReference viewPosRef = { 5.0f, 5.0f, 5.0f, ReferenceEdge::END, Axis::FREE };
    LayoutConstraintF layoutConstraint;
    layoutConstraint.selfIdealSize = selfIdealSize;
    layoutConstraint.parentIdealSize = parentIdealSize;
    layoutConstraint.viewPosRef = viewPosRef;
    auto result = listLayoutAlgorithm->PredictBuildItem(layoutWrapper, layoutConstraint);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: CheckAndUpdateCurOffset001
 * @tc.desc: Test ListItemLayoutAlgorithm CheckAndUpdateCurOffset
 * @tc.type: FUNC
 */
HWTEST_F(ListAlgorithmTestNg, CheckAndUpdateCurOffset001, TestSize.Level1)
{
    RefPtr<ListPattern> listPattern = AceType::MakeRefPtr<ListPattern>();
    RefPtr<ListItemLayoutAlgorithm> listItemLayoutAlgorithm = AceType::MakeRefPtr<ListItemLayoutAlgorithm>(2, 4, 3);
    RefPtr<ListLayoutProperty> listLayoutProperty = AceType::MakeRefPtr<ListLayoutProperty>();
    auto frameNode = FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, 2, listPattern);
    ASSERT_NE(frameNode, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(geometryNode, nullptr);
    GeometryProperty geometryProperty;
    RectT rect(20.0f, 20.0f, 80.0f, 80.0f);
    geometryProperty.rect_ = rect;
    geometryNode->frame_ = geometryProperty;
    LayoutWrapperNode layoutWrapper(frameNode, geometryNode, listLayoutProperty);
    layoutWrapper.geometryNode_ = geometryNode;
    layoutWrapper.hostNode_ = frameNode;
    listItemLayoutAlgorithm->isCurOffsetUpdated_ = false;
    listItemLayoutAlgorithm->canUpdateCurOffset_ = true;
    listItemLayoutAlgorithm->curOffset_ = 2.0f;
    listItemLayoutAlgorithm->CheckAndUpdateCurOffset(&layoutWrapper);
    EXPECT_TRUE(listItemLayoutAlgorithm->isCurOffsetUpdated_);
    EXPECT_EQ(listItemLayoutAlgorithm->curOffset_, 80.0f);
}

/**
 * @tc.name: CheckAndUpdateCurOffset002
 * @tc.desc: Test ListItemLayoutAlgorithm CheckAndUpdateCurOffset
 * @tc.type: FUNC
 */
HWTEST_F(ListAlgorithmTestNg, CheckAndUpdateCurOffset002, TestSize.Level1)
{
    RefPtr<ListPattern> listPattern = AceType::MakeRefPtr<ListPattern>();
    RefPtr<ListItemLayoutAlgorithm> listItemLayoutAlgorithm = AceType::MakeRefPtr<ListItemLayoutAlgorithm>(-1, 4, 3);
    RefPtr<ListLayoutProperty> listLayoutProperty = AceType::MakeRefPtr<ListLayoutProperty>();
    auto frameNode = FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, 2, listPattern);
    ASSERT_NE(frameNode, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(geometryNode, nullptr);
    GeometryProperty geometryProperty;
    RectT rect(20.0f, 20.0f, 80.0f, 80.0f);
    geometryProperty.rect_ = rect;
    geometryNode->frame_ = geometryProperty;
    LayoutWrapperNode layoutWrapper(frameNode, geometryNode, listLayoutProperty);
    layoutWrapper.geometryNode_ = geometryNode;
    layoutWrapper.hostNode_ = frameNode;
    listItemLayoutAlgorithm->isCurOffsetUpdated_ = false;
    listItemLayoutAlgorithm->canUpdateCurOffset_ = true;
    listItemLayoutAlgorithm->curOffset_ = 2.0f;
    listItemLayoutAlgorithm->CheckAndUpdateCurOffset(&layoutWrapper);
    EXPECT_TRUE(listItemLayoutAlgorithm->isCurOffsetUpdated_);
    EXPECT_EQ(listItemLayoutAlgorithm->curOffset_, 2.0f);
}

/**
 * @tc.name: CheckAndUpdateCurOffset003
 * @tc.desc: Test ListItemLayoutAlgorithm CheckAndUpdateCurOffset
 * @tc.type: FUNC
 */
HWTEST_F(ListAlgorithmTestNg, CheckAndUpdateCurOffset003, TestSize.Level1)
{
    RefPtr<ListPattern> listPattern = AceType::MakeRefPtr<ListPattern>();
    RefPtr<ListItemLayoutAlgorithm> listItemLayoutAlgorithm = AceType::MakeRefPtr<ListItemLayoutAlgorithm>(2, 4, 3);
    RefPtr<ListLayoutProperty> listLayoutProperty = AceType::MakeRefPtr<ListLayoutProperty>();
    auto frameNode = FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, 2, listPattern);
    ASSERT_NE(frameNode, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(geometryNode, nullptr);
    GeometryProperty geometryProperty;
    RectT rect(20.0f, 20.0f, 80.0f, 80.0f);
    geometryProperty.rect_ = rect;
    geometryNode->frame_ = geometryProperty;
    LayoutWrapperNode layoutWrapper(frameNode, geometryNode, listLayoutProperty);
    layoutWrapper.geometryNode_ = geometryNode;
    layoutWrapper.hostNode_ = frameNode;
    listItemLayoutAlgorithm->isCurOffsetUpdated_ = false;
    listItemLayoutAlgorithm->canUpdateCurOffset_ = true;
    listItemLayoutAlgorithm->curOffset_ = -2.0f;
    listItemLayoutAlgorithm->CheckAndUpdateCurOffset(&layoutWrapper);
    EXPECT_TRUE(listItemLayoutAlgorithm->isCurOffsetUpdated_);
    EXPECT_EQ(listItemLayoutAlgorithm->curOffset_, -80.0f);
}

/**
 * @tc.name: CheckAndUpdateCurOffset004
 * @tc.desc: Test ListItemLayoutAlgorithm CheckAndUpdateCurOffset
 * @tc.type: FUNC
 */
HWTEST_F(ListAlgorithmTestNg, CheckAndUpdateCurOffset004, TestSize.Level1)
{
    RefPtr<ListPattern> listPattern = AceType::MakeRefPtr<ListPattern>();
    RefPtr<ListItemLayoutAlgorithm> listItemLayoutAlgorithm = AceType::MakeRefPtr<ListItemLayoutAlgorithm>(-2, -4, 3);
    RefPtr<ListLayoutProperty> listLayoutProperty = AceType::MakeRefPtr<ListLayoutProperty>();
    auto frameNode = FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, 2, listPattern);
    ASSERT_NE(frameNode, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(geometryNode, nullptr);
    GeometryProperty geometryProperty;
    RectT rect(20.0f, 20.0f, 80.0f, 80.0f);
    geometryProperty.rect_ = rect;
    geometryNode->frame_ = geometryProperty;
    LayoutWrapperNode layoutWrapper(frameNode, geometryNode, listLayoutProperty);
    layoutWrapper.geometryNode_ = geometryNode;
    layoutWrapper.hostNode_ = frameNode;
    listItemLayoutAlgorithm->isCurOffsetUpdated_ = false;
    listItemLayoutAlgorithm->canUpdateCurOffset_ = true;
    listItemLayoutAlgorithm->curOffset_ = -2.0f;
    listItemLayoutAlgorithm->CheckAndUpdateCurOffset(&layoutWrapper);
    EXPECT_TRUE(listItemLayoutAlgorithm->isCurOffsetUpdated_);
    EXPECT_EQ(listItemLayoutAlgorithm->curOffset_, -2.0f);
}
} // namespace OHOS::Ace::NG

