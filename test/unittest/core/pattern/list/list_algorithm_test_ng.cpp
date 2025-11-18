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
} // namespace OHOS::Ace::NG

