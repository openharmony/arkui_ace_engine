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

class ListAlgorithmTestTwoNg : public TestNG {
public:
};

/**
 * @tc.name: LayoutALineForward001
 * @tc.desc: Test ListLayoutAlgorithm LayoutALineForward
 * @tc.type: FUNC
 */
HWTEST_F(ListAlgorithmTestTwoNg, LayoutALineForward001, TestSize.Level1)
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
HWTEST_F(ListAlgorithmTestTwoNg, LayoutALineBackward001, TestSize.Level1)
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
HWTEST_F(ListAlgorithmTestTwoNg, LayoutALineBackward002, TestSize.Level1)
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
HWTEST_F(ListAlgorithmTestTwoNg, LayoutALineBackward003, TestSize.Level1)
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
HWTEST_F(ListAlgorithmTestTwoNg, LayoutALineBackward004, TestSize.Level1)
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
HWTEST_F(ListAlgorithmTestTwoNg, LayoutBackward001, TestSize.Level1)
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
HWTEST_F(ListAlgorithmTestTwoNg, FixPredictSnapPos001, TestSize.Level1)
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
HWTEST_F(ListAlgorithmTestTwoNg, FixPredictSnapOffset001, TestSize.Level1)
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
HWTEST_F(ListAlgorithmTestTwoNg, FixPredictSnapOffset002, TestSize.Level1)
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
HWTEST_F(ListAlgorithmTestTwoNg, FixPredictSnapOffset003, TestSize.Level1)
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
HWTEST_F(ListAlgorithmTestTwoNg, FixPredictSnapOffsetAlignStart001, TestSize.Level1)
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
HWTEST_F(ListAlgorithmTestTwoNg, FixPredictSnapOffsetAlignCenter001, TestSize.Level1)
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
HWTEST_F(ListAlgorithmTestTwoNg, FixPredictSnapOffsetAlignCenter002, TestSize.Level1)
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
HWTEST_F(ListAlgorithmTestTwoNg, FixPredictSnapOffsetAlignCenter003, TestSize.Level1)
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
HWTEST_F(ListAlgorithmTestTwoNg, FixPredictSnapOffsetAlignCenter004, TestSize.Level1)
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
HWTEST_F(ListAlgorithmTestTwoNg, FixPredictSnapOffsetAlignCenter005, TestSize.Level1)
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
HWTEST_F(ListAlgorithmTestTwoNg, FixPredictSnapOffsetAlignEnd001, TestSize.Level1)
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
HWTEST_F(ListAlgorithmTestTwoNg, CalculateLaneCrossOffset001, TestSize.Level1)
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
HWTEST_F(ListAlgorithmTestTwoNg, OnSurfaceChanged001, TestSize.Level1)
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
 * @tc.name: CheckAndUpdateCurOffset001
 * @tc.desc: Test ListItemLayoutAlgorithm CheckAndUpdateCurOffset
 * @tc.type: FUNC
 */
HWTEST_F(ListAlgorithmTestTwoNg, CheckAndUpdateCurOffset001, TestSize.Level1)
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
HWTEST_F(ListAlgorithmTestTwoNg, CheckAndUpdateCurOffset002, TestSize.Level1)
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
HWTEST_F(ListAlgorithmTestTwoNg, CheckAndUpdateCurOffset003, TestSize.Level1)
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
HWTEST_F(ListAlgorithmTestTwoNg, CheckAndUpdateCurOffset004, TestSize.Level1)
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
