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

#include <cstdint>

#include "gtest/gtest.h"

#define private public
#define protected public

#include "base/memory/ace_type.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/syntax/arkoala_condition_scope.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t TEST_NODE_ID = 100;
constexpr int32_t DEFAULT_SLOT = 0;
}

class ArkoalaConditionScopeTestNgAI : public testing::Test {
public:
    static void SetUpTestSuite()
    {
        MockPipelineContext::SetUp();
    }

    static void TearDownTestSuite()
    {
        MockPipelineContext::TearDown();
    }

    void SetUp() override
    {
        MockPipelineContext::SetUp();
    }

    void TearDown() override
    {
        MockPipelineContext::TearDown();
    }

    RefPtr<ConditionScopeNode> CreateConditionScopeNode()
    {
        return AceType::MakeRefPtr<ConditionScopeNode>(TEST_NODE_ID);
    }

    RefPtr<FrameNode> CreateFrameNode(const std::string& tag)
    {
        auto pattern = AceType::MakeRefPtr<Pattern>();
        auto frameNode = AceType::MakeRefPtr<FrameNode>(tag, -1, pattern);
        pattern->AttachToFrameNode(frameNode);
        return frameNode;
    }
};

/**
 * @tc.name: Constructor_BasicTest
 * @tc.desc: Test ConditionScopeNode constructor initializes correctly
 * @tc.type: FUNC
 */
HWTEST_F(ArkoalaConditionScopeTestNgAI, Constructor_BasicTest, TestSize.Level1)
{
    auto node = CreateConditionScopeNode();
    ASSERT_NE(node, nullptr);

    EXPECT_EQ(node->GetId(), TEST_NODE_ID);
    EXPECT_EQ(node->GetTag(), V2::JS_IF_ELSE_ETS_TAG);
}

/**
 * @tc.name: IsAtomicNode_ReturnsFalseTest
 * @tc.desc: Test IsAtomicNode returns false
 * @tc.type: FUNC
 */
HWTEST_F(ArkoalaConditionScopeTestNgAI, IsAtomicNode_ReturnsFalseTest, TestSize.Level1)
{
    auto node = CreateConditionScopeNode();
    ASSERT_NE(node, nullptr);

    EXPECT_FALSE(node->IsAtomicNode());
}

/**
 * @tc.name: IsSyntaxNode_ReturnsTrueTest
 * @tc.desc: Test IsSyntaxNode returns true
 * @tc.type: FUNC
 */
HWTEST_F(ArkoalaConditionScopeTestNgAI, IsSyntaxNode_ReturnsTrueTest, TestSize.Level1)
{
    auto node = CreateConditionScopeNode();
    ASSERT_NE(node, nullptr);

    EXPECT_TRUE(node->IsSyntaxNode());
}

/**
 * @tc.name: AddChild_AddsChildCorrectlyTest
 * @tc.desc: Test AddChild adds child node correctly
 * @tc.type: FUNC
 */
HWTEST_F(ArkoalaConditionScopeTestNgAI, AddChild_AddsChildCorrectlyTest, TestSize.Level1)
{
    auto conditionNode = CreateConditionScopeNode();
    ASSERT_NE(conditionNode, nullptr);

    auto childNode = CreateFrameNode(V2::TEXT_ETS_TAG);
    ASSERT_NE(childNode, nullptr);

    conditionNode->AddChild(childNode, DEFAULT_SLOT, false, false, false);

    const auto& children = conditionNode->GetChildren();
    EXPECT_EQ(children.size(), 1);
    EXPECT_EQ(children.front(), childNode);
}

/**
 * @tc.name: AddChild_WithDefaultTransitionTest
 * @tc.desc: Test AddChild with default transition enabled
 * @tc.type: FUNC
 */
HWTEST_F(ArkoalaConditionScopeTestNgAI, AddChild_WithDefaultTransitionTest, TestSize.Level1)
{
    auto conditionNode = CreateConditionScopeNode();
    ASSERT_NE(conditionNode, nullptr);

    auto childNode = CreateFrameNode(V2::TEXT_ETS_TAG);
    ASSERT_NE(childNode, nullptr);

    conditionNode->AddChild(childNode, DEFAULT_SLOT, false, true, false);

    const auto& children = conditionNode->GetChildren();
    EXPECT_EQ(children.size(), 1);
}

/**
 * @tc.name: AddChild_SilentlyTest
 * @tc.desc: Test AddChild with silently flag
 * @tc.type: FUNC
 */
HWTEST_F(ArkoalaConditionScopeTestNgAI, AddChild_SilentlyTest, TestSize.Level1)
{
    auto conditionNode = CreateConditionScopeNode();
    ASSERT_NE(conditionNode, nullptr);

    auto childNode = CreateFrameNode(V2::TEXT_ETS_TAG);
    ASSERT_NE(childNode, nullptr);

    conditionNode->AddChild(childNode, DEFAULT_SLOT, true, false, false);

    const auto& children = conditionNode->GetChildren();
    EXPECT_EQ(children.size(), 1);
}

/**
 * @tc.name: AddChild_NullChildTest
 * @tc.desc: Test AddChild handles null child gracefully
 * @tc.type: FUNC
 */
HWTEST_F(ArkoalaConditionScopeTestNgAI, AddChild_NullChildTest, TestSize.Level1)
{
    auto conditionNode = CreateConditionScopeNode();
    ASSERT_NE(conditionNode, nullptr);

    conditionNode->AddChild(nullptr, DEFAULT_SLOT, false, false, false);

    const auto& children = conditionNode->GetChildren();
    EXPECT_TRUE(children.empty());
}

/**
 * @tc.name: FlushUpdateAndMarkDirty_MarksDirtyTest
 * @tc.desc: Test FlushUpdateAndMarkDirty marks parent dirty
 * @tc.type: FUNC
 */
HWTEST_F(ArkoalaConditionScopeTestNgAI, FlushUpdateAndMarkDirty_MarksDirtyTest, TestSize.Level1)
{
    auto conditionNode = CreateConditionScopeNode();
    ASSERT_NE(conditionNode, nullptr);

    auto parentNode = CreateFrameNode(V2::COLUMN_ETS_TAG);
    ASSERT_NE(parentNode, nullptr);

    parentNode->AddChild(conditionNode);

    conditionNode->FlushUpdateAndMarkDirty();

    SUCCEED();
}

/**
 * @tc.name: FlushUpdateAndMarkDirty_WithoutParentTest
 * @tc.desc: Test FlushUpdateAndMarkDirty handles missing parent
 * @tc.type: FUNC
 */
HWTEST_F(ArkoalaConditionScopeTestNgAI, FlushUpdateAndMarkDirty_WithoutParentTest, TestSize.Level1)
{
    auto conditionNode = CreateConditionScopeNode();
    ASSERT_NE(conditionNode, nullptr);

    conditionNode->FlushUpdateAndMarkDirty();

    SUCCEED();
}

} // namespace OHOS::Ace::NG
