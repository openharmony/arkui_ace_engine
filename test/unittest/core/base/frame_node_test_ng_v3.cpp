/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
#include "test/unittest/core/base/frame_node_test_ng.h"

#include "core/event/touch_event.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {} // namespace

/**
 * @tc.name: ResetLayoutAlgorithmTest1
 * @tc.desc: Test the function ResetLayoutAlgorithm with default param
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, ResetLayoutAlgorithmTest1, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     */
    auto frameNode1 = FrameNode::CreateFrameNode("framenode", 1, AceType::MakeRefPtr<Pattern>(), true);
    auto frameNode2 = FrameNode::CreateFrameNode("framenode", 2, AceType::MakeRefPtr<Pattern>());
    auto frameNode3 = FrameNode::CreateFrameNode("framenode", 3, AceType::MakeRefPtr<Pattern>());
    /**
     * @tc.steps: step2. mount nodes and create layoutAlgorithm
     */
    frameNode2->MountToParent(frameNode1);
    frameNode3->MountToParent(frameNode2);
    EXPECT_NE(frameNode1->GetLayoutAlgorithm(), nullptr);
    EXPECT_NE(frameNode2->GetLayoutAlgorithm(), nullptr);
    EXPECT_NE(frameNode3->GetLayoutAlgorithm(), nullptr);
    /**
     * @tc.steps: step2. start to clear. layoutAlgo of frameNode1 will not not be cleared
     */
    frameNode1->ClearSubtreeLayoutAlgorithm(false);
    EXPECT_TRUE(frameNode1->HasLayoutAlgorithm());
    EXPECT_FALSE(frameNode2->HasLayoutAlgorithm());
    EXPECT_FALSE(frameNode3->HasLayoutAlgorithm());
}

/**
 * @tc.name: ResetLayoutAlgorithmTest2
 * @tc.desc: Test the function ResetLayoutAlgorithm with default param
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, ResetLayoutAlgorithmTest2, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     */
    auto frameNode1 = FrameNode::CreateFrameNode("framenode", 1, AceType::MakeRefPtr<Pattern>(), true);
    auto frameNode2 = FrameNode::CreateFrameNode("framenode", 2, AceType::MakeRefPtr<Pattern>());
    auto frameNode3 = FrameNode::CreateFrameNode("framenode", 3, AceType::MakeRefPtr<Pattern>());

    /**
     * @tc.steps: step2. mount nodes and create layoutAlgorithm
     */
    frameNode2->MountToParent(frameNode1);
    frameNode3->MountToParent(frameNode2);
    EXPECT_NE(frameNode1->GetLayoutAlgorithm(), nullptr);
    EXPECT_NE(frameNode2->GetLayoutAlgorithm(), nullptr);
    EXPECT_NE(frameNode3->GetLayoutAlgorithm(), nullptr);
    /**
     * @tc.steps: step3. start to clear. layoutAlgo of frameNode1 will not not be cleared
     */
    frameNode1->ClearSubtreeLayoutAlgorithm(true);
    EXPECT_FALSE(frameNode1->HasLayoutAlgorithm());
    EXPECT_FALSE(frameNode2->HasLayoutAlgorithm());
    EXPECT_FALSE(frameNode3->HasLayoutAlgorithm());
}

/**
 * @tc.name: ResetLayoutAlgorithmTest3
 * @tc.desc: Test the function ResetLayoutAlgorithm and node3 should still have layoutAlgorithm
 * because chain broke at node2
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, ResetLayoutAlgorithmTest3, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     */
    auto frameNode1 = FrameNode::CreateFrameNode("framenode", 1, AceType::MakeRefPtr<Pattern>(), true);
    auto frameNode2 = FrameNode::CreateFrameNode("framenode", 2, AceType::MakeRefPtr<Pattern>());
    auto frameNode3 = FrameNode::CreateFrameNode("framenode", 3, AceType::MakeRefPtr<Pattern>());
    /**
     * @tc.steps: step2. mount nodes and create layoutAlgorithm
     */
    frameNode2->MountToParent(frameNode1);
    frameNode3->MountToParent(frameNode2);
    EXPECT_NE(frameNode1->GetLayoutAlgorithm(), nullptr);
    EXPECT_NE(frameNode3->GetLayoutAlgorithm(), nullptr);
    /**
     * @tc.steps: step3. start to clear. layoutAlgo of frameNode1 will not not be cleared
     */
    frameNode1->ClearSubtreeLayoutAlgorithm(true);
    EXPECT_FALSE(frameNode1->HasLayoutAlgorithm());
    EXPECT_FALSE(frameNode2->HasLayoutAlgorithm());
    EXPECT_TRUE(frameNode3->HasLayoutAlgorithm());
}

/**
 * @tc.name: ResetLayoutAlgorithmTest4
 * @tc.desc: Test the function ResetLayoutAlgorithm with clearing the whole tree
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, ResetLayoutAlgorithmTest4, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     */
    auto frameNode1 = FrameNode::CreateFrameNode("framenode", 1, AceType::MakeRefPtr<Pattern>(), true);
    auto frameNode2 = FrameNode::CreateFrameNode("framenode", 2, AceType::MakeRefPtr<Pattern>());
    auto frameNode3 = FrameNode::CreateFrameNode("framenode", 3, AceType::MakeRefPtr<Pattern>());
    /**
     * @tc.steps: step2. mount nodes and create layoutAlgorithm
     */
    frameNode2->MountToParent(frameNode1);
    frameNode3->MountToParent(frameNode2);
    EXPECT_NE(frameNode1->GetLayoutAlgorithm(), nullptr);
    EXPECT_NE(frameNode3->GetLayoutAlgorithm(), nullptr);
    /**
     * @tc.steps: step3. start to clear. layoutAlgo of frameNode1 will not not be cleared
     */
    frameNode1->ClearSubtreeLayoutAlgorithm(true, true);
    EXPECT_FALSE(frameNode1->HasLayoutAlgorithm());
    EXPECT_FALSE(frameNode2->HasLayoutAlgorithm());
    EXPECT_FALSE(frameNode3->HasLayoutAlgorithm());
}
/**
 * @tc.name: FrameNodeGetExtraCustomProperty001
 * @tc.desc: Test GetExtraCustomProperty.
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeGetExtraCustomProperty001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. initialize parameters.
     */
    auto frameNode = FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);
    char value[7]= "value1";
    /**
     * @tc.steps: step2. set key is value1
     * @tc.expected: expect result value.
     */
    frameNode->setIsCNode(true);
    frameNode->AddExtraCustomProperty("key", value);
    bool result = frameNode->GetExtraCustomProperty("key1");
    EXPECT_EQ(result, false);
}

/**
 * @tc.name: FrameNodeGetExtraCustomProperty002
 * @tc.desc: Test GetExtraCustomProperty.
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeGetExtraCustomProperty002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. initialize parameters.
     */
    auto frameNode = FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);

    /**
     * @tc.steps: step2. set key is value
     * @tc.expected: expect result value.
     */
    char value[7]= "value1";
    frameNode->setIsCNode(true);
    frameNode->AddExtraCustomProperty("key", value);
    bool result = frameNode->GetExtraCustomProperty("key");
    EXPECT_EQ(result, true);
}

/**
 * @tc.name: FrameNodeRemoveExtraCustomProperty001
 * @tc.desc: Test RemoveExtraCustomProperty.
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestNg, FrameNodeRemoveExtraCustomProperty001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. initialize parameters.
     */
    auto frameNode = FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);

    /**
     * @tc.steps: step2. set key is value1, remove key.
     * @tc.expected: expect result false.
     */
    char value[7]= "value1";
    frameNode->setIsCNode(true);
    frameNode->AddExtraCustomProperty("key", value);
    frameNode->RemoveExtraCustomProperty("key");
    bool result = frameNode->GetExtraCustomProperty("key");
    EXPECT_EQ(result, false);
}
} // namespace OHOS::Ace::NG