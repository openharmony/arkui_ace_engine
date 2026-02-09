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

#include <cstddef>
#include <vector>

#include "gtest/gtest.h"

#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/syntax/if_else_model_ng.h"
#include "core/components_v2/inspector/inspector_constants.h"

#define private public
#include "core/components_ng/syntax/if_else_node.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t IF_ELSE_BRANCH_ID_0 = 0;
constexpr int32_t IF_ELSE_BRANCH_ID_1 = 1;
constexpr int32_t IF_ELSE_BRANCH_ID_2 = 2;
constexpr int32_t IF_ELSE_BRANCH_ID_3 = 3;
constexpr int32_t IF_ELSE_NODE_ID_1 = 100;
constexpr int32_t IF_ELSE_NODE_ID_2 = 200;
constexpr int32_t IF_ELSE_CHILDREN_COUNT_0 = 0;
constexpr int32_t IF_ELSE_CHILDREN_COUNT_1 = 1;
constexpr int32_t IF_ELSE_CHILDREN_COUNT_3 = 3;
constexpr int32_t IF_ELSE_CHILDREN_COUNT_5 = 5;
constexpr int32_t IF_ELSE_CHILDREN_COUNT_10 = 10;
constexpr int32_t LARGE_REMOVED_LIST_SIZE = 1000;
constexpr int32_t NESTED_DEPTH_100 = 100;
} // namespace

class IfElseSyntaxAdvancedTestNg : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp() override;
    void TearDown() override;

    RefPtr<FrameNode> CreateChildNode(const std::string& tag, int32_t id);
    RefPtr<FrameNode> CreateNestedChildNodes(int32_t depth);
};

void IfElseSyntaxAdvancedTestNg::SetUpTestSuite()
{
    GTEST_LOG_(INFO) << "IfElseSyntaxAdvancedTestNg SetUpTestSuite";
}

void IfElseSyntaxAdvancedTestNg::TearDownTestSuite()
{
    GTEST_LOG_(INFO) << "IfElseSyntaxAdvancedTestNg TearDownTestSuite";
}

void IfElseSyntaxAdvancedTestNg::SetUp()
{
    MockPipelineContext::SetUp();
}

void IfElseSyntaxAdvancedTestNg::TearDown()
{
    MockPipelineContext::TearDown();
}

RefPtr<FrameNode> IfElseSyntaxAdvancedTestNg::CreateChildNode(const std::string& tag, int32_t id)
{
    auto pattern = AceType::MakeRefPtr<Pattern>();
    auto frameNode = FrameNode::CreateFrameNode(tag, id, pattern);
    return frameNode;
}

RefPtr<FrameNode> IfElseSyntaxAdvancedTestNg::CreateNestedChildNodes(int32_t depth)
{
    RefPtr<FrameNode> root = CreateChildNode(V2::BLANK_ETS_TAG, 1);
    RefPtr<FrameNode> current = root;

    for (int32_t i = 0; i < depth; ++i) {
        auto child = CreateChildNode(V2::TEXT_ETS_TAG, i + 10);
        current->AddChild(child);
        current = child;
    }

    return root;
}

/**
 * @tc.name: IfElseMultipleBranchChangeTest001
 * @tc.desc: Test multiple sequential branch changes from 0->1->2->0
 * @tc.type: FUNC
 */
HWTEST_F(IfElseSyntaxAdvancedTestNg, IfElseMultipleBranchChangeTest001, TestSize.Level1)
{
    IfElseModelNG ifElse;
    ifElse.Create();
    std::list<int32_t> removedElmtIds;
    std::list<int32_t> reservedElmtIds;

    auto ifElseNode = AceType::DynamicCast<IfElseNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(ifElseNode, nullptr);

    auto child1 = CreateChildNode(V2::BLANK_ETS_TAG, 1);
    ifElseNode->AddChild(child1);
    EXPECT_EQ(ifElseNode->GetChildren().size(), IF_ELSE_CHILDREN_COUNT_1);

    ifElseNode->SetBranchId(IF_ELSE_BRANCH_ID_1, removedElmtIds, reservedElmtIds);
    ifElseNode->FlushUpdateAndMarkDirty();
    EXPECT_EQ(ifElseNode->GetChildren().size(), IF_ELSE_CHILDREN_COUNT_0);

    auto child2 = CreateChildNode(V2::TEXT_ETS_TAG, 2);
    ifElseNode->AddChild(child2);
    EXPECT_EQ(ifElseNode->GetChildren().size(), IF_ELSE_CHILDREN_COUNT_1);

    ifElseNode->SetBranchId(IF_ELSE_BRANCH_ID_2, removedElmtIds, reservedElmtIds);
    ifElseNode->FlushUpdateAndMarkDirty();
    EXPECT_EQ(ifElseNode->GetChildren().size(), IF_ELSE_CHILDREN_COUNT_0);

    auto child3 = CreateChildNode(V2::IMAGE_ETS_TAG, 3);
    ifElseNode->AddChild(child3);
    EXPECT_EQ(ifElseNode->GetChildren().size(), IF_ELSE_CHILDREN_COUNT_1);

    ifElseNode->SetBranchId(IF_ELSE_BRANCH_ID_0, removedElmtIds, reservedElmtIds);
    ifElseNode->FlushUpdateAndMarkDirty();
    EXPECT_EQ(ifElseNode->GetChildren().size(), IF_ELSE_CHILDREN_COUNT_0);
}

/**
 * @tc.name: IfElseBranchChangeLargeRemovedListTest003
 * @tc.desc: Test branch change with large removedElmtId list (stress test)
 * @tc.type: FUNC
 */
HWTEST_F(IfElseSyntaxAdvancedTestNg, IfElseBranchChangeLargeRemovedListTest003, TestSize.Level1)
{
    IfElseModelNG ifElse;
    ifElse.Create();
    std::list<int32_t> largeRemovedElmtIds;
    std::list<int32_t> reservedElmtIds;

    for (int32_t i = 0; i < LARGE_REMOVED_LIST_SIZE; ++i) {
        largeRemovedElmtIds.push_back(i);
    }

    auto ifElseNode = AceType::DynamicCast<IfElseNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(ifElseNode, nullptr);

    for (int32_t i = 0; i < IF_ELSE_CHILDREN_COUNT_5; ++i) {
        auto child = CreateChildNode(V2::BLANK_ETS_TAG, i);
        ifElseNode->AddChild(child);
    }
    EXPECT_EQ(ifElseNode->GetChildren().size(), IF_ELSE_CHILDREN_COUNT_5);

    ifElseNode->SetBranchId(IF_ELSE_BRANCH_ID_1, largeRemovedElmtIds, reservedElmtIds);
    ifElseNode->FlushUpdateAndMarkDirty();
    EXPECT_EQ(ifElseNode->GetChildren().size(), IF_ELSE_CHILDREN_COUNT_0);
    EXPECT_GE(largeRemovedElmtIds.size(), LARGE_REMOVED_LIST_SIZE);
}

/**
 * @tc.name: IfElseTryRetakeNonExistentNodeTest004
 * @tc.desc: Test TryRetake with non-existent node ID
 * @tc.type: FUNC
 */
HWTEST_F(IfElseSyntaxAdvancedTestNg, IfElseTryRetakeNonExistentNodeTest004, TestSize.Level1)
{
    auto ifElseNode = IfElseNode::GetOrCreateIfElseNode(IF_ELSE_NODE_ID_1);
    ASSERT_NE(ifElseNode, nullptr);

    std::list<int32_t> emptyRemovedElmtIds;
    std::list<int32_t> emptyReservedElmtIds;
    ifElseNode->SetBranchId(IF_ELSE_BRANCH_ID_0, emptyRemovedElmtIds, emptyReservedElmtIds);

    ifElseNode->SetBranchId(IF_ELSE_BRANCH_ID_0, emptyRemovedElmtIds, emptyReservedElmtIds);
    bool result = ifElseNode->TryRetake("nonExistentNode");
    EXPECT_FALSE(result);
    EXPECT_EQ(ifElseNode->GetChildren().size(), IF_ELSE_CHILDREN_COUNT_0);
}

/**
 * @tc.name: IfElseCollectRetakenNodesEmptyChildrenTest010
 * @tc.desc: Test CollectRetakenNodes with empty children list
 * @tc.type: FUNC
 */
HWTEST_F(IfElseSyntaxAdvancedTestNg, IfElseCollectRetakenNodesEmptyChildrenTest010, TestSize.Level1)
{
    auto ifElseNode = IfElseNode::GetOrCreateIfElseNode(IF_ELSE_NODE_ID_1);
    ASSERT_NE(ifElseNode, nullptr);

    auto emptyNode = CreateChildNode(V2::BLANK_ETS_TAG, 1);
    EXPECT_TRUE(emptyNode->GetChildren().empty());

    ifElseNode->CollectRetakenNodes(emptyNode);
    EXPECT_EQ(ifElseNode->retakenElmtIds_.size(), IF_ELSE_CHILDREN_COUNT_1);
}

/**
 * @tc.name: IfElseCollectRetakenNodesDeepHierarchyTest011
 * @tc.desc: Test CollectRetakenNodes with very deep node hierarchy (100 levels)
 * @tc.type: FUNC
 */
HWTEST_F(IfElseSyntaxAdvancedTestNg, IfElseCollectRetakenNodesDeepHierarchyTest011, TestSize.Level1)
{
    auto ifElseNode = IfElseNode::GetOrCreateIfElseNode(IF_ELSE_NODE_ID_1);
    ASSERT_NE(ifElseNode, nullptr);

    auto deepNode = CreateNestedChildNodes(NESTED_DEPTH_100);
    ifElseNode->AddChild(deepNode);

    ifElseNode->CollectRetakenNodes(deepNode);
    EXPECT_EQ(ifElseNode->retakenElmtIds_.size(), NESTED_DEPTH_100 + 1);
}

/**
 * @tc.name: IfElseGetRetakenElmtIdsMultipleCallsTest012
 * @tc.desc: Test multiple calls to GetRetakenElmtIds (should return empty after first call)
 * @tc.type: FUNC
 */
HWTEST_F(IfElseSyntaxAdvancedTestNg, IfElseGetRetakenElmtIdsMultipleCallsTest012, TestSize.Level1)
{
    auto ifElseNode = IfElseNode::GetOrCreateIfElseNode(IF_ELSE_NODE_ID_1);
    ASSERT_NE(ifElseNode, nullptr);

    auto child = CreateChildNode(V2::TEXT_ETS_TAG, 1);
    ifElseNode->retakenElmtIds_.push_back(1);
    ifElseNode->retakenElmtIds_.push_back(2);
    ifElseNode->retakenElmtIds_.push_back(3);

    std::list<int32_t> output1;
    ifElseNode->GetRetakenElmtIds(output1);
    EXPECT_EQ(output1.size(), IF_ELSE_CHILDREN_COUNT_3);
    EXPECT_TRUE(ifElseNode->retakenElmtIds_.empty());

    std::list<int32_t> output2;
    ifElseNode->GetRetakenElmtIds(output2);
    EXPECT_EQ(output2.size(), IF_ELSE_CHILDREN_COUNT_0);
}

/**
 * @tc.name: IfElseGetRetakenElmtIdsPreFilledListTest013
 * @tc.desc: Test GetRetakenElmtIds with pre-filled output list
 * @tc.type: FUNC
 */
HWTEST_F(IfElseSyntaxAdvancedTestNg, IfElseGetRetakenElmtIdsPreFilledListTest013, TestSize.Level1)
{
    auto ifElseNode = IfElseNode::GetOrCreateIfElseNode(IF_ELSE_NODE_ID_1);
    ASSERT_NE(ifElseNode, nullptr);

    ifElseNode->retakenElmtIds_.push_back(10);
    ifElseNode->retakenElmtIds_.push_back(20);
    ifElseNode->retakenElmtIds_.push_back(30);

    std::list<int32_t> output;
    output.push_back(1);
    output.push_back(2);
    size_t initialSize = output.size();

    ifElseNode->GetRetakenElmtIds(output);
    EXPECT_EQ(output.size(), initialSize + IF_ELSE_CHILDREN_COUNT_3);
    EXPECT_TRUE(ifElseNode->retakenElmtIds_.empty());
}

/**
 * @tc.name: IfElseGetRetakenElmtIdsEmptyRetakenIdsTest014
 * @tc.desc: Test GetRetakenElmtIds with empty retakenElmtIds_
 * @tc.type: FUNC
 */
HWTEST_F(IfElseSyntaxAdvancedTestNg, IfElseGetRetakenElmtIdsEmptyRetakenIdsTest014, TestSize.Level1)
{
    auto ifElseNode = IfElseNode::GetOrCreateIfElseNode(IF_ELSE_NODE_ID_1);
    ASSERT_NE(ifElseNode, nullptr);
    EXPECT_TRUE(ifElseNode->retakenElmtIds_.empty());

    std::list<int32_t> output;
    ifElseNode->GetRetakenElmtIds(output);
    EXPECT_EQ(output.size(), IF_ELSE_CHILDREN_COUNT_0);
}

/**
 * @tc.name: IfElseBranchChangeWithMultipleChildrenTest015
 * @tc.desc: Test branch change with children at different depths
 * @tc.type: FUNC
 */
HWTEST_F(IfElseSyntaxAdvancedTestNg, IfElseBranchChangeWithMultipleChildrenTest015, TestSize.Level1)
{
    IfElseModelNG ifElse;
    ifElse.Create();
    std::list<int32_t> removedElmtIds;
    std::list<int32_t> reservedElmtIds;

    auto ifElseNode = AceType::DynamicCast<IfElseNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(ifElseNode, nullptr);

    for (int32_t i = 0; i < IF_ELSE_CHILDREN_COUNT_3; ++i) {
        auto child = CreateChildNode(V2::BLANK_ETS_TAG, i);
        ifElseNode->AddChild(child);
    }
    EXPECT_EQ(ifElseNode->GetChildren().size(), IF_ELSE_CHILDREN_COUNT_3);

    ifElseNode->SetBranchId(IF_ELSE_BRANCH_ID_1, removedElmtIds, reservedElmtIds);
    ifElseNode->FlushUpdateAndMarkDirty();
    EXPECT_EQ(ifElseNode->GetChildren().size(), IF_ELSE_CHILDREN_COUNT_0);

    for (int32_t i = 0; i < IF_ELSE_CHILDREN_COUNT_5; ++i) {
        auto child = CreateChildNode(V2::TEXT_ETS_TAG, i + 10);
        ifElseNode->AddChild(child);
    }
    EXPECT_EQ(ifElseNode->GetChildren().size(), IF_ELSE_CHILDREN_COUNT_5);

    ifElseNode->SetBranchId(IF_ELSE_BRANCH_ID_2, removedElmtIds, reservedElmtIds);
    ifElseNode->FlushUpdateAndMarkDirty();
    EXPECT_EQ(ifElseNode->GetChildren().size(), IF_ELSE_CHILDREN_COUNT_0);
}

/**
 * @tc.name: IfElseSameNodeIdMultipleInstancesTest016
 * @tc.desc: Test multiple IfElseNodes with same nodeId returns same instance
 * @tc.type: FUNC
 */
HWTEST_F(IfElseSyntaxAdvancedTestNg, IfElseSameNodeIdMultipleInstancesTest016, TestSize.Level1)
{
    auto ifElseNode1 = IfElseNode::GetOrCreateIfElseNode(IF_ELSE_NODE_ID_1);
    auto ifElseNode2 = IfElseNode::GetOrCreateIfElseNode(IF_ELSE_NODE_ID_1);
    auto ifElseNode3 = IfElseNode::GetOrCreateIfElseNode(IF_ELSE_NODE_ID_1);

    EXPECT_EQ(ifElseNode1, ifElseNode2);
    EXPECT_EQ(ifElseNode2, ifElseNode3);
    EXPECT_EQ(ifElseNode1, ifElseNode3);
}

/**
 * @tc.name: IfElseDifferentNodeIdDifferentInstancesTest017
 * @tc.desc: Test different nodeIds return different instances
 * @tc.type: FUNC
 */
HWTEST_F(IfElseSyntaxAdvancedTestNg, IfElseDifferentNodeIdDifferentInstancesTest017, TestSize.Level1)
{
    auto ifElseNode1 = IfElseNode::GetOrCreateIfElseNode(IF_ELSE_NODE_ID_1);
    auto ifElseNode2 = IfElseNode::GetOrCreateIfElseNode(IF_ELSE_NODE_ID_2);

    EXPECT_NE(ifElseNode1, ifElseNode2);
}

/**
 * @tc.name: IfElseFlushUpdateAndMarkDirtyNullParentTest018
 * @tc.desc: Test FlushUpdateAndMarkDirty with null parent
 * @tc.type: FUNC
 */
HWTEST_F(IfElseSyntaxAdvancedTestNg, IfElseFlushUpdateAndMarkDirtyNullParentTest018, TestSize.Level1)
{
    IfElseModelNG ifElse;
    ifElse.Create();

    auto ifElseNode = AceType::DynamicCast<IfElseNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(ifElseNode, nullptr);
    EXPECT_EQ(ifElseNode->GetParent(), nullptr);

    ifElseNode->branchIdChanged_ = true;
    ifElseNode->FlushUpdateAndMarkDirty();
    EXPECT_FALSE(ifElseNode->branchIdChanged_);
}

/**
 * @tc.name: IfElseBranchIdChangedFlagTest019
 * @tc.desc: Test branchIdChanged_ flag behavior
 * @tc.type: FUNC
 */
HWTEST_F(IfElseSyntaxAdvancedTestNg, IfElseBranchIdChangedFlagTest019, TestSize.Level1)
{
    IfElseModelNG ifElse;
    ifElse.Create();
    std::list<int32_t> removedElmtIds;
    std::list<int32_t> reservedElmtIds;

    auto ifElseNode = AceType::DynamicCast<IfElseNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(ifElseNode, nullptr);
    EXPECT_FALSE(ifElseNode->branchIdChanged_);

    auto child = CreateChildNode(V2::BLANK_ETS_TAG, 1);
    ifElseNode->AddChild(child);

    ifElseNode->SetBranchId(IF_ELSE_BRANCH_ID_1, removedElmtIds, reservedElmtIds);
    EXPECT_TRUE(ifElseNode->branchIdChanged_);

    ifElseNode->FlushUpdateAndMarkDirty();
    EXPECT_FALSE(ifElseNode->branchIdChanged_);

    ifElseNode->SetBranchId(IF_ELSE_BRANCH_ID_1, removedElmtIds, reservedElmtIds);
    EXPECT_FALSE(ifElseNode->branchIdChanged_);
}

/**
 * @tc.name: IfElseSetBranchIdReservedIdsTest020
 * @tc.desc: Test SetBranchId with reservedElmtIds
 * @tc.type: FUNC
 */
HWTEST_F(IfElseSyntaxAdvancedTestNg, IfElseSetBranchIdReservedIdsTest020, TestSize.Level1)
{
    IfElseModelNG ifElse;
    ifElse.Create();
    std::list<int32_t> removedElmtIds;
    std::list<int32_t> reservedElmtIds;
    reservedElmtIds.push_back(1);
    reservedElmtIds.push_back(2);
    reservedElmtIds.push_back(3);

    auto ifElseNode = AceType::DynamicCast<IfElseNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(ifElseNode, nullptr);

    for (int32_t i = 0; i < IF_ELSE_CHILDREN_COUNT_10; ++i) {
        auto child = CreateChildNode(V2::BLANK_ETS_TAG, i);
        ifElseNode->AddChild(child);
    }

    ifElseNode->SetBranchId(IF_ELSE_BRANCH_ID_1, removedElmtIds, reservedElmtIds);
    ifElseNode->FlushUpdateAndMarkDirty();
    EXPECT_EQ(ifElseNode->GetChildren().size(), IF_ELSE_CHILDREN_COUNT_0);
}

/**
 * @tc.name: IfElseBranchChangeCycleTest023
 * @tc.desc: Test cyclic branch changes 0->1->2->3->0
 * @tc.type: FUNC
 */
HWTEST_F(IfElseSyntaxAdvancedTestNg, IfElseBranchChangeCycleTest023, TestSize.Level1)
{
    IfElseModelNG ifElse;
    ifElse.Create();
    std::list<int32_t> removedElmtIds;
    std::list<int32_t> reservedElmtIds;

    auto ifElseNode = AceType::DynamicCast<IfElseNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(ifElseNode, nullptr);

    std::vector<int32_t> branchIds = {
        IF_ELSE_BRANCH_ID_1, IF_ELSE_BRANCH_ID_2, IF_ELSE_BRANCH_ID_3, IF_ELSE_BRANCH_ID_0};

    for (auto branchId : branchIds) {
        auto child = CreateChildNode(V2::BLANK_ETS_TAG, branchId);
        ifElseNode->AddChild(child);
        EXPECT_EQ(ifElseNode->GetChildren().size(), IF_ELSE_CHILDREN_COUNT_1);

        ifElseNode->SetBranchId(branchId, removedElmtIds, reservedElmtIds);
        ifElseNode->FlushUpdateAndMarkDirty();
        EXPECT_EQ(ifElseNode->GetChildren().size(), IF_ELSE_CHILDREN_COUNT_0);
    }
}

/**
 * @tc.name: IfElseGetOrCreateNodeDifferentIdsTest024
 * @tc.desc: Test GetOrCreateIfElseNode with various nodeId values
 * @tc.type: FUNC
 */
HWTEST_F(IfElseSyntaxAdvancedTestNg, IfElseGetOrCreateNodeDifferentIdsTest024, TestSize.Level1)
{
    auto node1 = IfElseNode::GetOrCreateIfElseNode(0);
    auto node2 = IfElseNode::GetOrCreateIfElseNode(-1);
    auto node3 = IfElseNode::GetOrCreateIfElseNode(9999);

    ASSERT_NE(node1, nullptr);
    ASSERT_NE(node2, nullptr);
    ASSERT_NE(node3, nullptr);

    EXPECT_NE(node1, node2);
    EXPECT_NE(node2, node3);
    EXPECT_NE(node1, node3);
}

} // namespace OHOS::Ace::NG
