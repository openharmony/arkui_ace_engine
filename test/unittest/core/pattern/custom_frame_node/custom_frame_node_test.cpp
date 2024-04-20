/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/pattern.h"

#define private public
#define protected public
#include "test/mock/core/pipeline/mock_pipeline_context.h"

#include "core/components_ng/pattern/custom_frame_node/custom_frame_node.h"
#include "core/components_ng/pattern/custom_frame_node/custom_frame_node_layout_algorithm.h"
#include "core/components_ng/pattern/custom_frame_node/custom_frame_node_pattern.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
const std::string CHILD_NODE = "ChildNode";
} // namespace

class CustomFrameNodeTestNg : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();

protected:
    static RefPtr<FrameNode> CreateNode();
};

void CustomFrameNodeTestNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
}

void CustomFrameNodeTestNg::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
}

RefPtr<FrameNode> CustomFrameNodeTestNg::CreateNode()
{
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    return CustomFrameNode::GetOrCreateCustomFrameNode(nodeId);
}

/**
 * @tc.name: CustomFrameNodeFrameNodeCreator001
 * @tc.desc: Test the create of CustomFrameNode.
 * @tc.type: FUNC
 */
HWTEST_F(CustomFrameNodeTestNg, CustomFrameNodeFrameNodeCreator001, TestSize.Level1)
{
    RefPtr<FrameNode> customFrameNode = CreateNode();
    ASSERT_NE(customFrameNode, nullptr);
}

/**
 * @tc.name: CustomFrameNodeRenderNodeModifierCreate001
 * @tc.desc: Test creation of renderNodeModifier_ in CustomFrameNode.
 * @tc.type: FUNC
 */
HWTEST_F(CustomFrameNodeTestNg, CustomFrameNodeRenderNodeModifierCreate001, TestSize.Level1)
{
    RefPtr<FrameNode> customFrameNode = CreateNode();
    ASSERT_NE(customFrameNode, nullptr);
    RefPtr<FrameNode> childNode_0 = FrameNode::CreateFrameNode(CHILD_NODE, 0, AceType::MakeRefPtr<Pattern>());
    auto pattern = customFrameNode->GetPattern<CustomFrameNodePattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step1.Create RenderNodeModifier by CreateNodePaintMethod.
     * @tc.expected: renderNodeModifier_ in pattern is nullptr, it created by fire CreateNodePaintMethod function.
     */
    ASSERT_EQ(pattern->renderNodeModifier_, nullptr);
    pattern->CreateNodePaintMethod();
    ASSERT_NE(pattern->renderNodeModifier_, nullptr);

    /**
     * @tc.steps: step2. Create RenderNodeModifier by SetDrawCallback.
     * @tc.expected: renderNodeModifier_ in pattern is nullptr.
     */
    pattern->renderNodeModifier_ = nullptr;
    ASSERT_EQ(pattern->renderNodeModifier_, nullptr);
    pattern->SetDrawCallback(nullptr);
    ASSERT_NE(pattern->renderNodeModifier_, nullptr);
}

/**
 * @tc.name: CustomFrameNodeRenderNodeInvalidate001
 * @tc.desc: Test Invalidate function in CustomFrameNode.
 * @tc.type: FUNC
 */
HWTEST_F(CustomFrameNodeTestNg, CustomFrameNodeRenderNodeInvalidate001, TestSize.Level1)
{
    RefPtr<FrameNode> customFrameNode = CreateNode();
    ASSERT_NE(customFrameNode, nullptr);
    RefPtr<FrameNode> childNode_0 = FrameNode::CreateFrameNode(CHILD_NODE, 0, AceType::MakeRefPtr<Pattern>());
    auto pattern = customFrameNode->GetPattern<CustomFrameNodePattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step1. Call Invalidate without renderNodeModifier_.
     * @tc.expected: Process success without crash.
     */
    ASSERT_EQ(pattern->renderNodeModifier_, nullptr);
    pattern->Invalidate();

    /**
     * @tc.steps: step2.Create RenderNodeModifier by CreateNodePaintMethod.
     * @tc.expected: renderNodeModifier_ in pattern is nullptr, it created by fire CreateNodePaintMethod function.
     */
    pattern->CreateNodePaintMethod();
    ASSERT_NE(pattern->renderNodeModifier_, nullptr);

    /**
     * @tc.steps: step3. Create RenderNodeModifier by SetDrawCallback.
     * @tc.expected: renderNodeModifier_ in pattern is nullptr.
     */
    ASSERT_EQ(pattern->renderNodeModifier_->renderNodeFlag_->Get(), 0);
    pattern->Invalidate();
    ASSERT_EQ(pattern->renderNodeModifier_->renderNodeFlag_->Get(), 1);
}
} // namespace OHOS::Ace::NG
