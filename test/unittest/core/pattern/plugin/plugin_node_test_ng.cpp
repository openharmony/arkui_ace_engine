/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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
#include <memory>
#include <optional>

#include "gtest/gtest.h"
#include "gmock/gmock-actions.h"
#include "gmock/gmock-matchers.h"

#include "core/common/container.h"

#define private public
#define protected public

#include "bundlemgr/bundle_mgr_interface.h"

#include "base/memory/ace_type.h"
#include "core/components/plugin/plugin_sub_container.h"
#include "core/components/plugin/resource/plugin_manager_delegate.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/plugin/plugin_event_hub.h"
#include "core/components_ng/pattern/plugin/plugin_layout_property.h"
#include "core/components_ng/pattern/plugin/plugin_node.h"
#include "core/components_ng/pattern/plugin/plugin_pattern.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t NODE_ID_OF_PLUGIN_NODE = 123456;
constexpr int32_t NODE_ID_OF_PARENT_NODE = 654321;
} // namespace

class PluginNodeTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override {}
    void TearDown() override {}
};

void PluginNodeTestNg::SetUpTestCase()
{
    MockPipelineContext::SetUp();
}

void PluginNodeTestNg::TearDownTestCase()
{
    MockPipelineContext::TearDown();
}

/**
 * @tc.name: GetOrCreatePluginNode
 * @tc.desc: Test GetOrCreatePluginNode in plugin_node.
 * @tc.type: FUNC
 */
HWTEST_F(PluginNodeTestNg, GetOrCreatePluginNode, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a plugin node by GetOrCreatePluginNode.
     * @tc.expected: Create node success.
     */
    auto* stack = ViewStackProcessor::GetInstance();
    auto frameNode = PluginNode::GetOrCreatePluginNode(
        "PluginComponent", NODE_ID_OF_PLUGIN_NODE, []() { return AceType::MakeRefPtr<PluginPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);

    /**
     * @tc.steps: step2. Get a Plugin node by GetOrCreatePluginNode with same nodeId.
     * @tc.expected: Get same node success.
     */
    auto samepluginNode = PluginNode::GetOrCreatePluginNode(
        "PluginComponent", NODE_ID_OF_PLUGIN_NODE, []() { return AceType::MakeRefPtr<PluginPattern>(); });
    EXPECT_EQ(frameNode == samepluginNode, true);

    /**
     * @tc.steps: step3. Remove a Plugin node by GetOrCreatePluginNode with different tag when parent is nullptr.
     * @tc.expected: Get a different node success.
     */
    auto diffPluginNode = PluginNode::GetOrCreatePluginNode(
        "PluginComponent1", NODE_ID_OF_PLUGIN_NODE, []() { return AceType::MakeRefPtr<PluginPattern>(); });
    EXPECT_NE(frameNode == diffPluginNode, true);

    /**
     * @tc.steps: step4. Remove a Plugin node by GetOrCreatePluginNode with different tag.
     * @tc.expected: Get a different node success and remove the node from parent.
     */
    auto parentPluginNode = PluginNode::GetOrCreatePluginNode(
        "PluginComponent", NODE_ID_OF_PARENT_NODE, []() { return AceType::MakeRefPtr<PluginPattern>(); });
    ASSERT_NE(parentPluginNode, nullptr);
    auto PluginNode = PluginNode::GetOrCreatePluginNode(
        "PluginComponent", NODE_ID_OF_PLUGIN_NODE, []() { return AceType::MakeRefPtr<PluginPattern>(); });
    PluginNode->SetParent(parentPluginNode);
    parentPluginNode->AddChild(PluginNode);
    ASSERT_EQ(parentPluginNode->GetFirstChild(), PluginNode);
    diffPluginNode = PluginNode::GetOrCreatePluginNode(
        "PluginComponent1", NODE_ID_OF_PLUGIN_NODE, []() { return AceType::MakeRefPtr<PluginPattern>(); });
    EXPECT_NE(PluginNode == diffPluginNode, true);
    ASSERT_EQ(AceType::TypeName(diffPluginNode->GetPattern()), "PluginPattern");
    ASSERT_EQ(parentPluginNode->GetFirstChild(), nullptr);

    /**
     * @tc.steps: step5. Remove a Plugin node by GetOrCreatePluginNode without  patternCreator.
     * @tc.expected: Get a different node success.
     */
    PluginNode = PluginNode::GetOrCreatePluginNode("PluginComponent", NODE_ID_OF_PLUGIN_NODE, nullptr);
    auto pattrn = PluginNode->GetPattern();
    ASSERT_EQ(AceType::TypeName(pattrn), "Pattern");
}
} // namespace OHOS::Ace::NG
