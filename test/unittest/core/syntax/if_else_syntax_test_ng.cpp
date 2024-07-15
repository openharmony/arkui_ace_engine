/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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
constexpr int32_t IF_ELSE_BRANCH_ID = 1;
constexpr int32_t IF_ELSE_BRANCH_ID_2 = 2;
constexpr int32_t IF_ELSE_CHILDREN_COUNT = 1;
constexpr int32_t IF_ELSE_CHILDREN_COUNT_2 = 0;
constexpr int32_t IF_ELSE_NODE_ID = 1;
std::list<int32_t> removedElmtIds;
constexpr bool IS_ATOMIC_NODE = false;
} // namespace

class IfElseSyntaxTestNg : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp() override;
    void TearDown() override;
};

void IfElseSyntaxTestNg::SetUpTestSuite()
{
    GTEST_LOG_(INFO) << "IfElseSyntaxTestNg SetUpTestCase";
}

void IfElseSyntaxTestNg::TearDownTestSuite()
{
    GTEST_LOG_(INFO) << "IfElseSyntaxTestNg TearDownTestCase";
}

void IfElseSyntaxTestNg::SetUp()
{
    MockPipelineContext::SetUp();
}

void IfElseSyntaxTestNg::TearDown()
{
    MockPipelineContext::TearDown();
}

/**
 * @tc.name: IfElseSyntaxCreateTest001
 * @tc.desc: Create IfElse.
 * @tc.type: FUNC
 */
HWTEST_F(IfElseSyntaxTestNg, IfElseSyntaxTest001, TestSize.Level1)
{
    IfElseModelNG ifElse;
    ifElse.Create();
    auto ifElseNodeNode = AceType::DynamicCast<IfElseNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_TRUE(ifElseNodeNode != nullptr && ifElseNodeNode->GetTag() == V2::JS_IF_ELSE_ETS_TAG);
}

/**
 * @tc.name: IfElseSyntaxPopTest002
 * @tc.desc: Create IfElse and pop it.
 * @tc.type: FUNC
 */
HWTEST_F(IfElseSyntaxTestNg, IfElseSyntaxTest002, TestSize.Level1)
{
    IfElseModelNG ifElse;
    ifElse.Create();
    ifElse.Pop();
    // ViewStackProcessor will not pop when it's size equals 1.
    EXPECT_FALSE(ViewStackProcessor::GetInstance()->GetMainElementNode() == nullptr);
}

/**
 * @tc.name: IfElseSyntaxBranchIDTest003
 * @tc.desc: Create IfElse and set/get branchId.
 * @tc.type: FUNC
 */
HWTEST_F(IfElseSyntaxTestNg, IfElseSyntaxBranchIDTest003, TestSize.Level1)
{
    IfElseModelNG ifElse;
    ifElse.Create();
    ifElse.SetBranchId(IF_ELSE_BRANCH_ID, removedElmtIds);

    EXPECT_EQ(ifElse.GetBranchId(), IF_ELSE_BRANCH_ID);
    auto ifElseNodeNode = AceType::DynamicCast<IfElseNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_TRUE(ifElseNodeNode != nullptr && ifElseNodeNode->GetTag() == V2::JS_IF_ELSE_ETS_TAG);
    EXPECT_EQ(ifElseNodeNode->GetBranchId(), IF_ELSE_BRANCH_ID);

    /**
    // corresponding ets code:
    //     if () {
    //       Blank()
    //     }
    */
    auto childFrameNode = FrameNode::CreateFrameNode(V2::BLANK_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>());
    ifElseNodeNode->AddChild(childFrameNode);
    EXPECT_EQ(ifElseNodeNode->GetChildren().size(), IF_ELSE_CHILDREN_COUNT);
    // ifElse node will clean its children when its branch id has changed.
    ifElseNodeNode->SetBranchId(IF_ELSE_BRANCH_ID_2, removedElmtIds);
    ifElseNodeNode->FlushUpdateAndMarkDirty();
    EXPECT_EQ(ifElseNodeNode->GetChildren().size(), IF_ELSE_CHILDREN_COUNT_2);

    /**
     * @tc.steps: step1. Set branch id which is same as before.
     * @tc.expected: OnDirtyLayoutWrapperSwap return the true only when the canvas images all have been initialized.
     */
    ifElseNodeNode->SetBranchId(IF_ELSE_BRANCH_ID, removedElmtIds);
    ifElseNodeNode->FlushUpdateAndMarkDirty();
    EXPECT_FALSE(ifElseNodeNode->branchIdChanged_);
}

/**
 * @tc.name: IfElseSyntaxTest004
 * @tc.desc: Create IfElse and invoke IsAtomicNode.
 * @tc.type: FUNC
 */
HWTEST_F(IfElseSyntaxTestNg, IfElseSyntaxTest004, TestSize.Level1)
{
    IfElseModelNG ifElse;
    ifElse.Create();
    ifElse.SetBranchId(IF_ELSE_BRANCH_ID, removedElmtIds);

    auto ifElseNodeNode = AceType::DynamicCast<IfElseNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_TRUE(ifElseNodeNode != nullptr && ifElseNodeNode->GetTag() == V2::JS_IF_ELSE_ETS_TAG);
    EXPECT_EQ(ifElseNodeNode->IsAtomicNode(), IS_ATOMIC_NODE);
}

/**
 * @tc.name: IfElseSyntaxBranchIDTest005
 * @tc.desc: Create IfElse and set/get branchId in abnormal condition.
 * @tc.type: FUNC
 */
HWTEST_F(IfElseSyntaxTestNg, IfElseSyntaxBranchIDTest005, TestSize.Level1)
{
    IfElseModelNG ifElse;
    ifElse.Create();
    ifElse.SetBranchId(IF_ELSE_BRANCH_ID, removedElmtIds);

    EXPECT_EQ(ifElse.GetBranchId(), IF_ELSE_BRANCH_ID);
    auto ifElseNodeNode = AceType::DynamicCast<IfElseNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_TRUE(ifElseNodeNode != nullptr && ifElseNodeNode->GetTag() == V2::JS_IF_ELSE_ETS_TAG);
    EXPECT_EQ(ifElseNodeNode->GetBranchId(), IF_ELSE_BRANCH_ID);

    /**
    // corresponding ets code:
    //     if () {
    //       Blank()
    //     }
    */
    auto childFrameNode = FrameNode::CreateFrameNode(V2::BLANK_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>());
    ifElseNodeNode->AddChild(childFrameNode);
    EXPECT_EQ(ifElseNodeNode->GetChildren().size(), IF_ELSE_CHILDREN_COUNT);
    // ifElse node will clean its children when its branch id has changed.
    ifElseNodeNode->SetBranchId(IF_ELSE_BRANCH_ID_2, removedElmtIds);
    ifElseNodeNode->FlushUpdateAndMarkDirty();
    EXPECT_EQ(ifElseNodeNode->GetChildren().size(), IF_ELSE_CHILDREN_COUNT_2);

    /**
     * @tc.steps: step1. Set branch id which is same as before.
     * @tc.expected: OnDirtyLayoutWrapperSwap return the true only when the canvas images all have been initialized.
     */
    ifElseNodeNode->SetBranchId(IF_ELSE_BRANCH_ID_2, removedElmtIds);
    ifElseNodeNode->FlushUpdateAndMarkDirty();
    EXPECT_FALSE(ifElseNodeNode->branchIdChanged_);
}

/**
 * @tc.name: IfElseSyntaxCreateTest006
 * @tc.desc: Create IfElse with same id.
 * @tc.type: FUNC
 */
HWTEST_F(IfElseSyntaxTestNg, IfElseSyntaxTest006, TestSize.Level1)
{
    auto ifElseNode = IfElseNode::GetOrCreateIfElseNode(IF_ELSE_NODE_ID);
    auto anotherIfElseNode = IfElseNode::GetOrCreateIfElseNode(IF_ELSE_NODE_ID);
    EXPECT_TRUE(ifElseNode == anotherIfElseNode);
}

/**
 * @tc.name: IfElseSyntaxCreateTest007
 * @tc.desc: Test TryRetake function.
 * @tc.type: FUNC
 */
HWTEST_F(IfElseSyntaxTestNg, IfElseSyntaxTest007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Add a node whose id is "node1" to the disappearingChildren of ifElseNode.
     */
    auto ifElseNode = IfElseNode::GetOrCreateIfElseNode(IF_ELSE_NODE_ID);
    ASSERT_NE(ifElseNode, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);
    ASSERT_NE(frameNode->GetLayoutProperty(), nullptr);
    frameNode->UpdateInspectorId("node1");
    auto frameNode2 = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode2, nullptr);
    ASSERT_NE(frameNode2->GetLayoutProperty(), nullptr);
    frameNode2->UpdateInspectorId("node2");
    ifElseNode->branchId_ = 0;
    ifElseNode->AddDisappearingChild(frameNode, -1, 0);
    ifElseNode->branchId_ = 1;
    ifElseNode->AddDisappearingChild(frameNode2, -1, 1);

    /**
     * @tc.steps: step2. IfElse is branch 0 again. Try to reuse "node1".
     * @tc.expected: node1 can be reused, return value is true.
     */
    ifElseNode->branchId_ = 0;
    bool result1 = ifElseNode->TryRetake("node1");
    EXPECT_TRUE(result1);
    EXPECT_TRUE(ifElseNode->GetChildren().size() == 1 && ifElseNode->GetChildAtIndex(0) == frameNode);

    /**
     * @tc.steps: step3. Try to reuse "node10".
     * @tc.expected: node10 is not in disappearingChildren so it can't be reused, return value is false.
     */
    bool result2 = ifElseNode->TryRetake("node10");
    EXPECT_FALSE(result2);

    /**
     * @tc.steps: step4. Try to reuse "node2".
     * @tc.expected: node2 branch is not same with branchId of ifElse, return value is false.
     */
    bool result3 = ifElseNode->TryRetake("node2");
    EXPECT_FALSE(result3);
}
} // namespace OHOS::Ace::NG
