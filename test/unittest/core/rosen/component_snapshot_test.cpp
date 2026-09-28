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

#include "gtest/gtest.h"

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/text/span_node.h"
#include "core/components_ng/render/adapter/component_snapshot.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "test/mock/frameworks/core/common/mock_container.h"
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"

namespace OHOS::Ace::NG {
using namespace testing;
using namespace testing::ext;

namespace {
constexpr int32_t INACTIVE_IMAGE_SPAN_NODE_ID = 991001;
constexpr int32_t ACTIVE_IMAGE_SPAN_NODE_ID = 991002;
constexpr int32_t IMAGE_NODE_ID = 991003;
constexpr int32_t VISIBLE_NODE_ID = 991004;
constexpr int32_t DELETED_NODE_ID = 991005;
constexpr int32_t INVISIBLE_NODE_ID = 991006;
constexpr int32_t INVISIBLE_CHILD_NODE_ID = 991007;
constexpr int32_t TREE_ROOT_NODE_ID = 991008;
constexpr int32_t TREE_CHILD_ONE_NODE_ID = 991009;
constexpr int32_t TREE_CHILD_TWO_NODE_ID = 991010;
} // namespace

class ComponentSnapshotCheckImageTest : public testing::Test {
public:
    static void SetUpTestSuite()
    {
        MockPipelineContext::SetUp();
        MockContainer::SetUp();
    }
    static void TearDownTestSuite()
    {
        MockContainer::TearDown();
        MockPipelineContext::TearDown();
    }
};

/**
 * @tc.name: CheckImageSuccessfullyLoadImageSpanInactive001
 * @tc.desc: Test CheckImageSuccessfullyLoad with an inactive ImageSpanNode, which must skip the
 *           image loading state check and return true even without a loading context.
 * @tc.type: FUNC
 */
HWTEST_F(ComponentSnapshotCheckImageTest, CheckImageSuccessfullyLoadImageSpanInactive001, TestSize.Level1)
{
    // isActive_ defaults to false, so a freshly created ImageSpanNode is inactive.
    auto imageSpanNode = AceType::MakeRefPtr<ImageSpanNode>(V2::IMAGE_ETS_TAG, INACTIVE_IMAGE_SPAN_NODE_ID);
    ASSERT_TRUE(imageSpanNode);
    ASSERT_FALSE(imageSpanNode->IsActive());

    SnapshotDFXInfo dfxInfo;
    EXPECT_TRUE(CheckImageSuccessfullyLoad(imageSpanNode, dfxInfo));
    EXPECT_EQ(dfxInfo.imageCount, 1);
    EXPECT_EQ(dfxInfo.nodeCount, 1);
    EXPECT_EQ(dfxInfo.invisibleCount, 0);
    EXPECT_EQ(dfxInfo.deletedCount, 0);
}

/**
 * @tc.name: CheckImageSuccessfullyLoadImageSpanActive002
 * @tc.desc: Test CheckImageSuccessfullyLoad with an active ImageSpanNode, which must NOT skip the
 *           image loading state check; without a loading context it returns false.
 * @tc.type: FUNC
 */
HWTEST_F(ComponentSnapshotCheckImageTest, CheckImageSuccessfullyLoadImageSpanActive002, TestSize.Level1)
{
    auto imageSpanNode = AceType::MakeRefPtr<ImageSpanNode>(V2::IMAGE_ETS_TAG, ACTIVE_IMAGE_SPAN_NODE_ID);
    ASSERT_TRUE(imageSpanNode);
    imageSpanNode->SetActive(true);
    ASSERT_TRUE(imageSpanNode->IsActive());

    SnapshotDFXInfo dfxInfo;
    EXPECT_FALSE(CheckImageSuccessfullyLoad(imageSpanNode, dfxInfo));
    EXPECT_EQ(dfxInfo.imageCount, 1);
    EXPECT_EQ(dfxInfo.nodeCount, 1);
}

/**
 * @tc.name: CheckImageSuccessfullyLoadPlainImageNode003
 * @tc.desc: Test CheckImageSuccessfullyLoad with a plain Image node (not ImageSpanNode); the
 *           inactive-skip branch must not apply and the null loading context yields false.
 * @tc.type: FUNC
 */
HWTEST_F(ComponentSnapshotCheckImageTest, CheckImageSuccessfullyLoadPlainImageNode003, TestSize.Level1)
{
    auto imageNode = FrameNode::CreateFrameNode(
        V2::IMAGE_ETS_TAG, IMAGE_NODE_ID, AceType::MakeRefPtr<ImagePattern>());
    ASSERT_TRUE(imageNode);
    ASSERT_FALSE(AceType::InstanceOf<ImageSpanNode>(imageNode));

    SnapshotDFXInfo dfxInfo;
    EXPECT_FALSE(CheckImageSuccessfullyLoad(imageNode, dfxInfo));
    EXPECT_EQ(dfxInfo.imageCount, 1);
    EXPECT_EQ(dfxInfo.nodeCount, 1);
}

/**
 * @tc.name: CheckImageSuccessfullyLoadNullNode004
 * @tc.desc: Test CheckImageSuccessfullyLoad with a null node.
 * @tc.type: FUNC
 */
HWTEST_F(ComponentSnapshotCheckImageTest, CheckImageSuccessfullyLoadNullNode004, TestSize.Level1)
{
    SnapshotDFXInfo dfxInfo;
    EXPECT_FALSE(CheckImageSuccessfullyLoad(nullptr, dfxInfo));
    EXPECT_EQ(dfxInfo.imageCount, 0);
    EXPECT_EQ(dfxInfo.nodeCount, 0);
}

/**
 * @tc.name: CheckImageSuccessfullyLoadVisibleNode005
 * @tc.desc: Test CheckImageSuccessfullyLoad with a visible leaf FrameNode; all DFX counters except
 *           nodeCount stay zero.
 * @tc.type: FUNC
 */
HWTEST_F(ComponentSnapshotCheckImageTest, CheckImageSuccessfullyLoadVisibleNode005, TestSize.Level1)
{
    auto node = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, VISIBLE_NODE_ID, AceType::MakeRefPtr<Pattern>());
    ASSERT_TRUE(node);
    ASSERT_TRUE(node->IsVisible());

    SnapshotDFXInfo dfxInfo;
    EXPECT_TRUE(CheckImageSuccessfullyLoad(node, dfxInfo));
    EXPECT_EQ(dfxInfo.nodeCount, 1);
    EXPECT_EQ(dfxInfo.imageCount, 0);
    EXPECT_EQ(dfxInfo.invisibleCount, 0);
    EXPECT_EQ(dfxInfo.deletedCount, 0);
}

/**
 * @tc.name: CheckImageSuccessfullyLoadDeletedNode006
 * @tc.desc: Test CheckImageSuccessfullyLoad with a deleted (but visible) FrameNode; deletedCount
 *           is collected and the traversal continues.
 * @tc.type: FUNC
 */
HWTEST_F(ComponentSnapshotCheckImageTest, CheckImageSuccessfullyLoadDeletedNode006, TestSize.Level1)
{
    auto node = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, DELETED_NODE_ID, AceType::MakeRefPtr<Pattern>());
    ASSERT_TRUE(node);
    node->SetDeleteRsNode(true);
    ASSERT_TRUE(node->GetIsDelete());

    SnapshotDFXInfo dfxInfo;
    EXPECT_TRUE(CheckImageSuccessfullyLoad(node, dfxInfo));
    EXPECT_EQ(dfxInfo.nodeCount, 1);
    EXPECT_EQ(dfxInfo.deletedCount, 1);
    EXPECT_EQ(dfxInfo.invisibleCount, 0);
}

/**
 * @tc.name: CheckImageSuccessfullyLoadInvisibleSkipsChildren007
 * @tc.desc: Test CheckImageSuccessfullyLoad with an invisible FrameNode; it returns true early and
 *           its children are not traversed (child not counted in nodeCount).
 * @tc.type: FUNC
 */
HWTEST_F(ComponentSnapshotCheckImageTest, CheckImageSuccessfullyLoadInvisibleSkipsChildren007, TestSize.Level1)
{
    auto parent = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, INVISIBLE_NODE_ID, AceType::MakeRefPtr<Pattern>());
    auto child = FrameNode::CreateFrameNode(
        V2::COLUMN_ETS_TAG, INVISIBLE_CHILD_NODE_ID, AceType::MakeRefPtr<Pattern>());
    ASSERT_TRUE(parent);
    ASSERT_TRUE(child);
    parent->AddChild(child);
    parent->GetLayoutProperty()->UpdateVisibility(VisibleType::INVISIBLE);
    ASSERT_FALSE(parent->IsVisible());

    SnapshotDFXInfo dfxInfo;
    EXPECT_TRUE(CheckImageSuccessfullyLoad(parent, dfxInfo));
    EXPECT_EQ(dfxInfo.nodeCount, 1); // only the parent: the child is skipped by the early return
    EXPECT_EQ(dfxInfo.invisibleCount, 1);
    EXPECT_EQ(dfxInfo.imageCount, 0);
    EXPECT_EQ(dfxInfo.deletedCount, 0);
}

/**
 * @tc.name: CheckImageSuccessfullyLoadCountsAcrossTree008
 * @tc.desc: Test CheckImageSuccessfullyLoad aggregates nodeCount across a visible node tree.
 * @tc.type: FUNC
 */
HWTEST_F(ComponentSnapshotCheckImageTest, CheckImageSuccessfullyLoadCountsAcrossTree008, TestSize.Level1)
{
    auto root = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, TREE_ROOT_NODE_ID, AceType::MakeRefPtr<Pattern>());
    auto childOne = FrameNode::CreateFrameNode(V2::ROW_ETS_TAG, TREE_CHILD_ONE_NODE_ID, AceType::MakeRefPtr<Pattern>());
    auto childTwo = FrameNode::CreateFrameNode(V2::ROW_ETS_TAG, TREE_CHILD_TWO_NODE_ID, AceType::MakeRefPtr<Pattern>());
    ASSERT_TRUE(root);
    ASSERT_TRUE(childOne);
    ASSERT_TRUE(childTwo);
    root->AddChild(childOne);
    root->AddChild(childTwo);

    SnapshotDFXInfo dfxInfo;
    EXPECT_TRUE(CheckImageSuccessfullyLoad(root, dfxInfo));
    EXPECT_EQ(dfxInfo.nodeCount, 3);
    EXPECT_EQ(dfxInfo.imageCount, 0);
    EXPECT_EQ(dfxInfo.invisibleCount, 0);
    EXPECT_EQ(dfxInfo.deletedCount, 0);
}
} // namespace OHOS::Ace::NG
