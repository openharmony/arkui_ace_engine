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

#include <list>
#include <unordered_map>
#include <vector>

#include "gtest/gtest.h"

#define protected public
#define private public

#include "base/geometry/dimension.h"
#include "base/geometry/dimension_rect.h"
#include "base/geometry/ng/offset_t.h"
#include "base/json/json_util.h"
#include "base/log/dump_log.h"
#include "base/memory/referenced.h"
#include "base/utils/system_properties.h"
#include "core/common/ace_application_info.h"
#include "core/common/resource/resource_configuration.h"
#include "core/components/common/layout/screen_system_manager.h"
#include "core/components_ng/animation/geometry_transition.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/frame_scene_status.h"
#include "core/components_ng/base/modifier.h"
#include "core/components_ng/event/focus_hub.h"
#include "core/components_ng/layout/layout_wrapper.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/stack/stack_pattern.h"
#include "core/components_ng/syntax/if_else_model_ng.h"
#include "test/mock/core/render/mock_render_context.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/event/mouse_event.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
const InspectorFilter filter;
const std::string NODE_TAG_ONE("111");
const std::string NODE_TAG_A("aaa");
const std::string NODE_TAG_SPOT("...");
const std::string NODE_TAG_EMPTY("");
} // namespace
class FrameNodeDropTestNg : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
};

void FrameNodeDropTestNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
}

void FrameNodeDropTestNg::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
}

class TestNode : public UINode {
    DECLARE_ACE_TYPE(TestNode, UINode);

public:
    static RefPtr<TestNode> CreateTestNode(int32_t nodeId)
    {
        auto node = MakeRefPtr<TestNode>(nodeId);
        return node;
    }

    bool IsAtomicNode() const override
    {
        return true;
    }

    explicit TestNode(int32_t nodeId) : UINode("TestNode", nodeId) {}
    ~TestNode() override = default;
};

/**
 * @tc.name: FrameNodeDropTestNg001
 * @tc.desc: Test frame node method
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeDropTestNg, FrameNodeDropTestNg001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a frameNode.
     * @tc.expected: frameNode is not null.
     */
    auto frameNodeNullId = ElementRegister::GetInstance()->MakeUniqueId();
    auto frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG_EMPTY, frameNodeNullId, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. construct a allowDropSet.
     * @tc.expected: allowDropSet is not null.
     */
    std::set<std::string> allowDropSet = { NODE_TAG_EMPTY };

    /**
     * @tc.steps: step3. Set an allowDrop in the frameNode and then get an allowDrop.
     * @tc.expected: The set allowDrop is the same as the get allowDrop.
     */
    frameNode->SetAllowDrop(allowDropSet);
    std::set<std::string> allowDropGet = frameNode->GetAllowDrop();
    EXPECT_EQ(allowDropGet, allowDropSet);

    /**
     * @tc.steps: step4. Set an isDisallowDropForcedly in the frameNode and then get an isDisallowDropForcedly.
     * @tc.expected: The set isDisallowDropForcedly is the same as the get isDisallowDropForcedly.
     */
    bool isDisallowDropForcedly = frameNode->GetDisallowDropForcedly();
    ASSERT_FALSE(isDisallowDropForcedly);
}

/**
 * @tc.name: FrameNodeDropTestNg002
 * @tc.desc: Test frame node method
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeDropTestNg, FrameNodeDropTestNg002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a frameNode.
     * @tc.expected: frameNode is not null.
     */
    auto frameNodeNullId = ElementRegister::GetInstance()->MakeUniqueId();
    auto frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG_ONE, frameNodeNullId, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. construct a allowDropSet.
     * @tc.expected: allowDropSet is not null.
     */
    std::set<std::string> allowDropSet = { NODE_TAG_ONE };

    /**
     * @tc.steps: step3. Set an allowDrop in the frameNode and then get an allowDrop.
     * @tc.expected: The set allowDrop is the same as the get allowDrop.
     */
    frameNode->SetAllowDrop(allowDropSet);
    std::set<std::string> allowDropGet = frameNode->GetAllowDrop();
    EXPECT_EQ(allowDropGet, allowDropSet);

    /**
     * @tc.steps: step4. Set an isDisallowDropForcedly in the frameNode and then get an isDisallowDropForcedly.
     * @tc.expected: The set isDisallowDropForcedly is the same as the get isDisallowDropForcedly.
     */
    bool isDisallowDropForcedly = frameNode->GetDisallowDropForcedly();
    ASSERT_FALSE(isDisallowDropForcedly);
}

/**
 * @tc.name: FrameNodeDropTestNg003
 * @tc.desc: Test frame node method
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeDropTestNg, FrameNodeDropTestNg003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a frameNode.
     * @tc.expected: frameNode is not null.
     */
    auto frameNodeNullId = ElementRegister::GetInstance()->MakeUniqueId();
    auto frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG_SPOT, frameNodeNullId, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. construct a allowDropSet.
     * @tc.expected: allowDropSet is not null.
     */
    std::set<std::string> allowDropSet = { NODE_TAG_SPOT };

    /**
     * @tc.steps: step3. Set an allowDrop in the frameNode and then get an allowDrop.
     * @tc.expected: The set allowDrop is the same as the get allowDrop.
     */
    frameNode->SetAllowDrop(allowDropSet);
    std::set<std::string> allowDropGet = frameNode->GetAllowDrop();
    EXPECT_EQ(allowDropGet, allowDropSet);

    /**
     * @tc.steps: step4. Set an isDisallowDropForcedly in the frameNode and then get an isDisallowDropForcedly.
     * @tc.expected: The set isDisallowDropForcedly is the same as the get isDisallowDropForcedly.
     */
    bool isDisallowDropForcedly = frameNode->GetDisallowDropForcedly();
    ASSERT_FALSE(isDisallowDropForcedly);
}

/**
 * @tc.name: FrameNodeDropTestNg004
 * @tc.desc: Test frame node method
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeDropTestNg, FrameNodeDropTestNg004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a frameNode.
     * @tc.expected: frameNode is not null.
     */
    auto frameNodeNullId = ElementRegister::GetInstance()->MakeUniqueId();
    auto frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG_A, frameNodeNullId, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. construct a allowDropSet.
     * @tc.expected: allowDropSet is not null.
     */
    std::set<std::string> allowDropSet = { NODE_TAG_A };

    /**
     * @tc.steps: step3. Set an allowDrop in the frameNode and then get an allowDrop.
     * @tc.expected: The set allowDrop is the same as the get allowDrop.
     */
    frameNode->SetAllowDrop(allowDropSet);
    std::set<std::string> allowDropGet = frameNode->GetAllowDrop();
    EXPECT_EQ(allowDropGet, allowDropSet);

    /**
     * @tc.steps: step4. Set an isDisallowDropForcedly in the frameNode and then get an isDisallowDropForcedly.
     * @tc.expected: The set isDisallowDropForcedly is the same as the get isDisallowDropForcedly.
     */
    bool isDisallowDropForcedly = frameNode->GetDisallowDropForcedly();
    ASSERT_FALSE(isDisallowDropForcedly);
}

/**
 * @tc.name: FrameNodeDropTestNg005
 * @tc.desc: Test frame node method
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeDropTestNg, FrameNodeDropTestNg005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a frameNode.
     * @tc.expected: frameNode is not null.
     */
    auto frameNode = FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. construct a allowDropSet.
     * @tc.expected: allowDropSet is not null.
     */
    std::set<std::string> allowDropSet;

    /**
     * @tc.steps: step3. Set an allowDrop in the frameNode and then get an allowDrop.
     * @tc.expected: The set allowDrop is the same as the get allowDrop.
     */
    frameNode->SetAllowDrop(allowDropSet);
    std::set<std::string> allowDropGet = frameNode->GetAllowDrop();
    EXPECT_EQ(allowDropGet, allowDropSet);

    /**
     * @tc.steps: step4. Set an isDisallowDropForcedly in the frameNode and then get an isDisallowDropForcedly.
     * @tc.expected: The set isDisallowDropForcedly is the same as the get isDisallowDropForcedly.
     */
    bool isDisallowDropForcedly = frameNode->GetDisallowDropForcedly();
    ASSERT_FALSE(isDisallowDropForcedly);
}

/**
 * @tc.name: FrameNodeDropTestNg006
 * @tc.desc: Test frame node method
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeDropTestNg, FrameNodeDropTestNg006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a frameNode.
     * @tc.expected: frameNode is not null.
     */
    auto frameNodeNullId = ElementRegister::GetInstance()->MakeUniqueId();
    auto frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG_EMPTY, frameNodeNullId, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. construct a allowDropSet.
     * @tc.expected: allowDropSet is not null.
     */
    std::set<std::string> allowDropSet = { NODE_TAG_EMPTY };

    /**
     * @tc.steps: step3. Set an allowDrop in the frameNode and then get an allowDrop.
     * @tc.expected: The set allowDrop is the same as the get allowDrop.
     */
    frameNode->SetAllowDrop(allowDropSet);
    std::set<std::string> allowDropGet = frameNode->GetAllowDrop();
    EXPECT_EQ(allowDropGet, allowDropSet);

    /**
     * @tc.steps: step4. Set an isDisallowDropForcedly in the frameNode and then get an isDisallowDropForcedly.
     * @tc.expected: The set isDisallowDropForcedly is the same as the get isDisallowDropForcedly.
     */
    bool isDisallowDrop = true;
    ASSERT_TRUE(isDisallowDrop);
    frameNode->SetDisallowDropForcedly(isDisallowDrop);
    bool isDisallowDropForcedly = frameNode->GetDisallowDropForcedly();
    ASSERT_TRUE(isDisallowDropForcedly);
}

/**
 * @tc.name: FrameNodeDropTestNg007
 * @tc.desc: Test frame node method
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeDropTestNg, FrameNodeDropTestNg007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a frameNode.
     * @tc.expected: frameNode is not null.
     */
    auto frameNodeNullId = ElementRegister::GetInstance()->MakeUniqueId();
    auto frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG_ONE, frameNodeNullId, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. construct a allowDropSet.
     * @tc.expected: allowDropSet is not null.
     */
    std::set<std::string> allowDropSet = { NODE_TAG_ONE };

    /**
     * @tc.steps: step3. Set an allowDrop in the frameNode and then get an allowDrop.
     * @tc.expected: The set allowDrop is the same as the get allowDrop.
     */
    frameNode->SetAllowDrop(allowDropSet);
    std::set<std::string> allowDropGet = frameNode->GetAllowDrop();
    EXPECT_EQ(allowDropGet, allowDropSet);

    /**
     * @tc.steps: step4. Set an isDisallowDropForcedly in the frameNode and then get an isDisallowDropForcedly.
     * @tc.expected: The set isDisallowDropForcedly is the same as the get isDisallowDropForcedly.
     */
    bool isDisallowDrop = true;
    ASSERT_TRUE(isDisallowDrop);
    frameNode->SetDisallowDropForcedly(isDisallowDrop);
    bool isDisallowDropForcedly = frameNode->GetDisallowDropForcedly();
    ASSERT_TRUE(isDisallowDropForcedly);
}

/**
 * @tc.name: FrameNodeDropTestNg008
 * @tc.desc: Test frame node method
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeDropTestNg, FrameNodeDropTestNg008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a frameNode.
     * @tc.expected: frameNode is not null.
     */
    auto frameNodeNullId = ElementRegister::GetInstance()->MakeUniqueId();
    auto frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG_SPOT, frameNodeNullId, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. construct a allowDropSet.
     * @tc.expected: allowDropSet is not null.
     */
    std::set<std::string> allowDropSet = { NODE_TAG_SPOT };

    /**
     * @tc.steps: step3. Set an allowDrop in the frameNode and then get an allowDrop.
     * @tc.expected: The set allowDrop is the same as the get allowDrop.
     */
    frameNode->SetAllowDrop(allowDropSet);
    std::set<std::string> allowDropGet = frameNode->GetAllowDrop();
    EXPECT_EQ(allowDropGet, allowDropSet);

    /**
     * @tc.steps: step4. Set an isDisallowDropForcedly in the frameNode and then get an isDisallowDropForcedly.
     * @tc.expected: The set isDisallowDropForcedly is the same as the get isDisallowDropForcedly.
     */
    bool isDisallowDrop = true;
    ASSERT_TRUE(isDisallowDrop);
    frameNode->SetDisallowDropForcedly(isDisallowDrop);
    bool isDisallowDropForcedly = frameNode->GetDisallowDropForcedly();
    ASSERT_TRUE(isDisallowDropForcedly);
}

/**
 * @tc.name: FrameNodeDropTestNg009
 * @tc.desc: Test frame node method
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeDropTestNg, FrameNodeDropTestNg009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a frameNode.
     * @tc.expected: frameNode is not null.
     */
    auto frameNodeNullId = ElementRegister::GetInstance()->MakeUniqueId();
    auto frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG_A, frameNodeNullId, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. construct a allowDropSet.
     * @tc.expected: allowDropSet is not null.
     */
    std::set<std::string> allowDropSet = { NODE_TAG_A };

    /**
     * @tc.steps: step3. Set an allowDrop in the frameNode and then get an allowDrop.
     * @tc.expected: The set allowDrop is the same as the get allowDrop.
     */
    frameNode->SetAllowDrop(allowDropSet);
    std::set<std::string> allowDropGet = frameNode->GetAllowDrop();
    EXPECT_EQ(allowDropGet, allowDropSet);

    /**
     * @tc.steps: step4. Set an isDisallowDropForcedly in the frameNode and then get an isDisallowDropForcedly.
     * @tc.expected: The set isDisallowDropForcedly is the same as the get isDisallowDropForcedly.
     */
    bool isDisallowDrop = true;
    ASSERT_TRUE(isDisallowDrop);
    frameNode->SetDisallowDropForcedly(isDisallowDrop);
    bool isDisallowDropForcedly = frameNode->GetDisallowDropForcedly();
    ASSERT_TRUE(isDisallowDropForcedly);
}

/**
 * @tc.name: FrameNodeDropTestNg010
 * @tc.desc: Test frame node method
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeDropTestNg, FrameNodeDropTestNg010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a frameNode.
     * @tc.expected: frameNode is not null.
     */
    auto frameNode = FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. construct a allowDropSet.
     * @tc.expected: allowDropSet is not null.
     */
    std::set<std::string> allowDropSet;

    /**
     * @tc.steps: step3. Set an allowDrop in the frameNode and then get an allowDrop.
     * @tc.expected: The set allowDrop is the same as the get allowDrop.
     */
    frameNode->SetAllowDrop(allowDropSet);
    std::set<std::string> allowDropGet = frameNode->GetAllowDrop();
    EXPECT_EQ(allowDropGet, allowDropSet);

    /**
     * @tc.steps: step4. Set an isDisallowDropForcedly in the frameNode and then get an isDisallowDropForcedly.
     * @tc.expected: The set isDisallowDropForcedly is the same as the get isDisallowDropForcedly.
     */
    bool isDisallowDrop = true;
    ASSERT_TRUE(isDisallowDrop);
    frameNode->SetDisallowDropForcedly(isDisallowDrop);
    bool isDisallowDropForcedly = frameNode->GetDisallowDropForcedly();
    ASSERT_TRUE(isDisallowDropForcedly);
}

/**
 * @tc.name: FrameNodeDropTestNg011
 * @tc.desc: Test frame node method
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeDropTestNg, FrameNodeDropTestNg011, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a frameNode.
     * @tc.expected: frameNode is not null.
     */
    auto frameNodeNullId = ElementRegister::GetInstance()->MakeUniqueId();
    auto frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG_EMPTY, frameNodeNullId, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. construct a allowDropSet.
     * @tc.expected: allowDropSet is not null.
     */
    std::set<std::string> allowDropSet = { NODE_TAG_EMPTY };

    /**
     * @tc.steps: step3. Set an allowDrop in the frameNode and then get an allowDrop.
     * @tc.expected: The set allowDrop is the same as the get allowDrop.
     */
    frameNode->SetAllowDrop(allowDropSet);
    std::set<std::string> allowDropGet = frameNode->GetAllowDrop();
    EXPECT_EQ(allowDropGet, allowDropSet);

    /**
     * @tc.steps: step4. Set an isDisallowDropForcedly in the frameNode and then get an isDisallowDropForcedly.
     * @tc.expected: The set isDisallowDropForcedly is the same as the get isDisallowDropForcedly.
     */
    bool isDisallowDrop = false;
    ASSERT_FALSE(isDisallowDrop);
    frameNode->SetDisallowDropForcedly(isDisallowDrop);
    bool isDisallowDropForcedly = frameNode->GetDisallowDropForcedly();
    ASSERT_FALSE(isDisallowDropForcedly);
}

/**
 * @tc.name: FrameNodeDropTestNg012
 * @tc.desc: Test frame node method
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeDropTestNg, FrameNodeDropTestNg012, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a frameNode.
     * @tc.expected: frameNode is not null.
     */
    auto frameNodeNullId = ElementRegister::GetInstance()->MakeUniqueId();
    auto frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG_ONE, frameNodeNullId, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. construct a allowDropSet.
     * @tc.expected: allowDropSet is not null.
     */
    std::set<std::string> allowDropSet = { NODE_TAG_ONE };

    /**
     * @tc.steps: step3. Set an allowDrop in the frameNode and then get an allowDrop.
     * @tc.expected: The set allowDrop is the same as the get allowDrop.
     */
    frameNode->SetAllowDrop(allowDropSet);
    std::set<std::string> allowDropGet = frameNode->GetAllowDrop();
    EXPECT_EQ(allowDropGet, allowDropSet);

    /**
     * @tc.steps: step4. Set an isDisallowDropForcedly in the frameNode and then get an isDisallowDropForcedly.
     * @tc.expected: The set isDisallowDropForcedly is the same as the get isDisallowDropForcedly.
     */
    bool isDisallowDrop = false;
    ASSERT_FALSE(isDisallowDrop);
    frameNode->SetDisallowDropForcedly(isDisallowDrop);
    bool isDisallowDropForcedly = frameNode->GetDisallowDropForcedly();
    ASSERT_FALSE(isDisallowDropForcedly);
}

/**
 * @tc.name: FrameNodeDropTestNg013
 * @tc.desc: Test frame node method
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeDropTestNg, FrameNodeDropTestNg013, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a frameNode.
     * @tc.expected: frameNode is not null.
     */
    auto frameNodeNullId = ElementRegister::GetInstance()->MakeUniqueId();
    auto frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG_SPOT, frameNodeNullId, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. construct a allowDropSet.
     * @tc.expected: allowDropSet is not null.
     */
    std::set<std::string> allowDropSet = { NODE_TAG_SPOT };

    /**
     * @tc.steps: step3. Set an allowDrop in the frameNode and then get an allowDrop.
     * @tc.expected: The set allowDrop is the same as the get allowDrop.
     */
    frameNode->SetAllowDrop(allowDropSet);
    std::set<std::string> allowDropGet = frameNode->GetAllowDrop();
    EXPECT_EQ(allowDropGet, allowDropSet);

    /**
     * @tc.steps: step4. Set an isDisallowDropForcedly in the frameNode and then get an isDisallowDropForcedly.
     * @tc.expected: The set isDisallowDropForcedly is the same as the get isDisallowDropForcedly.
     */
    bool isDisallowDrop = false;
    ASSERT_FALSE(isDisallowDrop);
    frameNode->SetDisallowDropForcedly(isDisallowDrop);
    bool isDisallowDropForcedly = frameNode->GetDisallowDropForcedly();
    ASSERT_FALSE(isDisallowDropForcedly);
}

/**
 * @tc.name: FrameNodeDropTestNg014
 * @tc.desc: Test frame node method
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeDropTestNg, FrameNodeDropTestNg014, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a frameNode.
     * @tc.expected: frameNode is not null.
     */
    auto frameNodeNullId = ElementRegister::GetInstance()->MakeUniqueId();
    auto frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG_A, frameNodeNullId, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. construct a allowDropSet.
     * @tc.expected: allowDropSet is not null.
     */
    std::set<std::string> allowDropSet = { NODE_TAG_A };

    /**
     * @tc.steps: step3. Set an allowDrop in the frameNode and then get an allowDrop.
     * @tc.expected: The set allowDrop is the same as the get allowDrop.
     */
    frameNode->SetAllowDrop(allowDropSet);
    std::set<std::string> allowDropGet = frameNode->GetAllowDrop();
    EXPECT_EQ(allowDropGet, allowDropSet);

    /**
     * @tc.steps: step4. Set an isDisallowDropForcedly in the frameNode and then get an isDisallowDropForcedly.
     * @tc.expected: The set isDisallowDropForcedly is the same as the get isDisallowDropForcedly.
     */
    bool isDisallowDrop = false;
    ASSERT_FALSE(isDisallowDrop);
    frameNode->SetDisallowDropForcedly(isDisallowDrop);
    bool isDisallowDropForcedly = frameNode->GetDisallowDropForcedly();
    ASSERT_FALSE(isDisallowDropForcedly);
}

/**
 * @tc.name: FrameNodeDropTestNg015
 * @tc.desc: Test frame node method
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeDropTestNg, FrameNodeDropTestNg015, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a frameNode.
     * @tc.expected: frameNode is not null.
     */
    auto frameNode = FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. construct a allowDropSet.
     * @tc.expected: allowDropSet is not null.
     */
    std::set<std::string> allowDropSet;

    /**
     * @tc.steps: step3. Set an allowDrop in the frameNode and then get an allowDrop.
     * @tc.expected: The set allowDrop is the same as the get allowDrop.
     */
    frameNode->SetAllowDrop(allowDropSet);
    std::set<std::string> allowDropGet = frameNode->GetAllowDrop();
    EXPECT_EQ(allowDropGet, allowDropSet);

    /**
     * @tc.steps: step4. Set an isDisallowDropForcedly in the frameNode and then get an isDisallowDropForcedly.
     * @tc.expected: The set isDisallowDropForcedly is the same as the get isDisallowDropForcedly.
     */
    bool isDisallowDrop = false;
    ASSERT_FALSE(isDisallowDrop);
    frameNode->SetDisallowDropForcedly(isDisallowDrop);
    bool isDisallowDropForcedly = frameNode->GetDisallowDropForcedly();
    ASSERT_FALSE(isDisallowDropForcedly);
}

/**
 * @tc.name: FrameNodeDropTestNg016
 * @tc.desc: Test frame node method
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeDropTestNg, FrameNodeDropTestNg016, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a DragDropManager.
     * @tc.expected: dragDropManager is not null.
     */
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();
    ASSERT_NE(dragDropManager, nullptr);

    /**
     * @tc.steps: step2. construct frameNode and update the properties.
     * @tc.expected: frameNode is not null.
     */
    const std::string allowTag(NODE_TAG_SPOT);
    auto frameNodeNullId = ElementRegister::GetInstance()->MakeUniqueId();
    auto frameNode = AceType::MakeRefPtr<FrameNode>(allowTag, frameNodeNullId, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);
    std::set<std::string> allowDrop = { allowTag };
    frameNode->SetAllowDrop(allowDrop);
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step3. construct summaryMap for dragDropManager.
     * @tc.expected: dragDropManager is not null.
     */
    const std::string summary_TAG(NODE_TAG_SPOT);
    dragDropManager->summaryMap_.clear();
    dragDropManager->summaryMap_.insert(make_pair(summary_TAG, frameNodeNullId));
    ASSERT_NE(dragDropManager, nullptr);

    /**
     * @tc.steps: step4. Set an isDisallowDropForcedly in the frameNode and then get an isDisallowDropForcedly.
     * @tc.expected: The set isDisallowDropForcedly is the same as the get isDisallowDropForcedly.
     */
    bool isDisallowDrop = false;
    ASSERT_FALSE(isDisallowDrop);
    frameNode->SetDisallowDropForcedly(isDisallowDrop);
    bool isDisallowDropForcedly = frameNode->GetDisallowDropForcedly();
    ASSERT_FALSE(isDisallowDropForcedly);
    
    /**
     * @tc.steps: step5. ReportingSupported is set to false.
     * @tc.expected: reportingEnabledFalse is false.
     */
    ASSERT_TRUE(dragDropManager->IsDropAllowed(frameNode));
}

/**
 * @tc.name: FrameNodeDropTestNg017
 * @tc.desc: Test frame node method
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeDropTestNg, FrameNodeDropTestNg017, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a DragDropManager.
     * @tc.expected: dragDropManager is not null.
     */
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();
    ASSERT_NE(dragDropManager, nullptr);

    /**
     * @tc.steps: step2. construct frameNode and update the properties.
     * @tc.expected: frameNode is not null.
     */
    const std::string allowTag(NODE_TAG_SPOT);
    auto frameNodeNullId = ElementRegister::GetInstance()->MakeUniqueId();
    auto frameNode = AceType::MakeRefPtr<FrameNode>(allowTag, frameNodeNullId, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);
    std::set<std::string> allowDrop = { allowTag };
    frameNode->SetAllowDrop(allowDrop);
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step3. construct summaryMap for dragDropManager.
     * @tc.expected: dragDropManager is not null.
     */
    const std::string summary_TAG(NODE_TAG_ONE);
    dragDropManager->summaryMap_.clear();
    dragDropManager->summaryMap_.insert(make_pair(summary_TAG, frameNodeNullId));
    ASSERT_NE(dragDropManager, nullptr);

    /**
     * @tc.steps: step4. Set an isDisallowDropForcedly in the frameNode and then get an isDisallowDropForcedly.
     * @tc.expected: The set isDisallowDropForcedly is the same as the get isDisallowDropForcedly.
     */
    bool isDisallowDrop = false;
    ASSERT_FALSE(isDisallowDrop);
    frameNode->SetDisallowDropForcedly(isDisallowDrop);
    bool isDisallowDropForcedly = frameNode->GetDisallowDropForcedly();
    ASSERT_FALSE(isDisallowDropForcedly);
    
    /**
     * @tc.steps: step5. ReportingSupported is set to false.
     * @tc.expected: reportingEnabledFalse is false.
     */
    ASSERT_FALSE(dragDropManager->IsDropAllowed(frameNode));
}

/**
 * @tc.name: FrameNodeDropTestNg018
 * @tc.desc: Test frame node method
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeDropTestNg, FrameNodeDropTestNg018, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a DragDropManager.
     * @tc.expected: dragDropManager is not null.
     */
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();
    ASSERT_NE(dragDropManager, nullptr);

    /**
     * @tc.steps: step2. construct frameNode and update the properties.
     * @tc.expected: frameNode is not null.
     */
    const std::string allowTag(NODE_TAG_SPOT);
    auto frameNodeNullId = ElementRegister::GetInstance()->MakeUniqueId();
    auto frameNode = AceType::MakeRefPtr<FrameNode>(allowTag, frameNodeNullId, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);
    std::set<std::string> allowDrop = { allowTag };
    frameNode->SetAllowDrop(allowDrop);
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step3. construct summaryMap for dragDropManager.
     * @tc.expected: dragDropManager is not null.
     */
    const std::string summary_TAG(NODE_TAG_A);
    dragDropManager->summaryMap_.clear();
    dragDropManager->summaryMap_.insert(make_pair(summary_TAG, frameNodeNullId));
    ASSERT_NE(dragDropManager, nullptr);

    /**
     * @tc.steps: step4. Set an isDisallowDropForcedly in the frameNode and then get an isDisallowDropForcedly.
     * @tc.expected: The set isDisallowDropForcedly is the same as the get isDisallowDropForcedly.
     */
    bool isDisallowDrop = false;
    ASSERT_FALSE(isDisallowDrop);
    frameNode->SetDisallowDropForcedly(isDisallowDrop);
    bool isDisallowDropForcedly = frameNode->GetDisallowDropForcedly();
    ASSERT_FALSE(isDisallowDropForcedly);
    
    /**
     * @tc.steps: step5. ReportingSupported is set to false.
     * @tc.expected: reportingEnabledFalse is false.
     */
    ASSERT_FALSE(dragDropManager->IsDropAllowed(frameNode));
}

/**
 * @tc.name: FrameNodeDropTestNg019
 * @tc.desc: Test frame node method
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeDropTestNg, FrameNodeDropTestNg019, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a DragDropManager.
     * @tc.expected: dragDropManager is not null.
     */
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();
    ASSERT_NE(dragDropManager, nullptr);

    /**
     * @tc.steps: step2. construct frameNode and update the properties.
     * @tc.expected: frameNode is not null.
     */
    const std::string allowTag(NODE_TAG_ONE);
    auto frameNodeNullId = ElementRegister::GetInstance()->MakeUniqueId();
    auto frameNode = AceType::MakeRefPtr<FrameNode>(allowTag, frameNodeNullId, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);
    std::set<std::string> allowDrop = { allowTag };
    frameNode->SetAllowDrop(allowDrop);
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step3. construct summaryMap for dragDropManager.
     * @tc.expected: dragDropManager is not null.
     */
    const std::string summary_TAG(NODE_TAG_SPOT);
    dragDropManager->summaryMap_.clear();
    dragDropManager->summaryMap_.insert(make_pair(summary_TAG, frameNodeNullId));
    ASSERT_NE(dragDropManager, nullptr);

    /**
     * @tc.steps: step4. Set an isDisallowDropForcedly in the frameNode and then get an isDisallowDropForcedly.
     * @tc.expected: The set isDisallowDropForcedly is the same as the get isDisallowDropForcedly.
     */
    bool isDisallowDrop = false;
    ASSERT_FALSE(isDisallowDrop);
    frameNode->SetDisallowDropForcedly(isDisallowDrop);
    bool isDisallowDropForcedly = frameNode->GetDisallowDropForcedly();
    ASSERT_FALSE(isDisallowDropForcedly);
    
    /**
     * @tc.steps: step5. ReportingSupported is set to false.
     * @tc.expected: reportingEnabledFalse is false.
     */
    ASSERT_FALSE(dragDropManager->IsDropAllowed(frameNode));
}

/**
 * @tc.name: FrameNodeDropTestNg020
 * @tc.desc: Test frame node method
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeDropTestNg, FrameNodeDropTestNg020, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a DragDropManager.
     * @tc.expected: dragDropManager is not null.
     */
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();
    ASSERT_NE(dragDropManager, nullptr);

    /**
     * @tc.steps: step2. construct frameNode and update the properties.
     * @tc.expected: frameNode is not null.
     */
    const std::string allowTag(NODE_TAG_ONE);
    auto frameNodeNullId = ElementRegister::GetInstance()->MakeUniqueId();
    auto frameNode = AceType::MakeRefPtr<FrameNode>(allowTag, frameNodeNullId, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);
    std::set<std::string> allowDrop = { allowTag };
    frameNode->SetAllowDrop(allowDrop);
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step3. construct summaryMap for dragDropManager.
     * @tc.expected: dragDropManager is not null.
     */
    const std::string summary_TAG(NODE_TAG_ONE);
    dragDropManager->summaryMap_.clear();
    dragDropManager->summaryMap_.insert(make_pair(summary_TAG, frameNodeNullId));
    ASSERT_NE(dragDropManager, nullptr);

    /**
     * @tc.steps: step4. Set an isDisallowDropForcedly in the frameNode and then get an isDisallowDropForcedly.
     * @tc.expected: The set isDisallowDropForcedly is the same as the get isDisallowDropForcedly.
     */
    bool isDisallowDrop = false;
    ASSERT_FALSE(isDisallowDrop);
    frameNode->SetDisallowDropForcedly(isDisallowDrop);
    bool isDisallowDropForcedly = frameNode->GetDisallowDropForcedly();
    ASSERT_FALSE(isDisallowDropForcedly);
    
    /**
     * @tc.steps: step5. ReportingSupported is set to false.
     * @tc.expected: reportingEnabledFalse is false.
     */
    ASSERT_TRUE(dragDropManager->IsDropAllowed(frameNode));
}

/**
 * @tc.name: FrameNodeDropTestNg021
 * @tc.desc: Test frame node method
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeDropTestNg, FrameNodeDropTestNg021, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a DragDropManager.
     * @tc.expected: dragDropManager is not null.
     */
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();
    ASSERT_NE(dragDropManager, nullptr);

    /**
     * @tc.steps: step2. construct frameNode and update the properties.
     * @tc.expected: frameNode is not null.
     */
    const std::string allowTag(NODE_TAG_ONE);
    auto frameNodeNullId = ElementRegister::GetInstance()->MakeUniqueId();
    auto frameNode = AceType::MakeRefPtr<FrameNode>(allowTag, frameNodeNullId, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);
    std::set<std::string> allowDrop = { allowTag };
    frameNode->SetAllowDrop(allowDrop);
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step3. construct summaryMap for dragDropManager.
     * @tc.expected: dragDropManager is not null.
     */
    const std::string summary_TAG(NODE_TAG_A);
    dragDropManager->summaryMap_.clear();
    dragDropManager->summaryMap_.insert(make_pair(summary_TAG, frameNodeNullId));
    ASSERT_NE(dragDropManager, nullptr);

    /**
     * @tc.steps: step4. Set an isDisallowDropForcedly in the frameNode and then get an isDisallowDropForcedly.
     * @tc.expected: The set isDisallowDropForcedly is the same as the get isDisallowDropForcedly.
     */
    bool isDisallowDrop = false;
    ASSERT_FALSE(isDisallowDrop);
    frameNode->SetDisallowDropForcedly(isDisallowDrop);
    bool isDisallowDropForcedly = frameNode->GetDisallowDropForcedly();
    ASSERT_FALSE(isDisallowDropForcedly);
    
    /**
     * @tc.steps: step5. ReportingSupported is set to false.
     * @tc.expected: reportingEnabledFalse is false.
     */
    ASSERT_FALSE(dragDropManager->IsDropAllowed(frameNode));
}

/**
 * @tc.name: FrameNodeDropTestNg022
 * @tc.desc: Test frame node method
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeDropTestNg, FrameNodeDropTestNg022, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a DragDropManager.
     * @tc.expected: dragDropManager is not null.
     */
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();
    ASSERT_NE(dragDropManager, nullptr);

    /**
     * @tc.steps: step2. construct frameNode and update the properties.
     * @tc.expected: frameNode is not null.
     */
    const std::string allowTag(NODE_TAG_A);
    auto frameNodeNullId = ElementRegister::GetInstance()->MakeUniqueId();
    auto frameNode = AceType::MakeRefPtr<FrameNode>(allowTag, frameNodeNullId, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);
    std::set<std::string> allowDrop = { allowTag };
    frameNode->SetAllowDrop(allowDrop);
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step3. construct summaryMap for dragDropManager.
     * @tc.expected: dragDropManager is not null.
     */
    const std::string summary_TAG(NODE_TAG_SPOT);
    dragDropManager->summaryMap_.clear();
    dragDropManager->summaryMap_.insert(make_pair(summary_TAG, frameNodeNullId));
    ASSERT_NE(dragDropManager, nullptr);

    /**
     * @tc.steps: step4. Set an isDisallowDropForcedly in the frameNode and then get an isDisallowDropForcedly.
     * @tc.expected: The set isDisallowDropForcedly is the same as the get isDisallowDropForcedly.
     */
    bool isDisallowDrop = false;
    ASSERT_FALSE(isDisallowDrop);
    frameNode->SetDisallowDropForcedly(isDisallowDrop);
    bool isDisallowDropForcedly = frameNode->GetDisallowDropForcedly();
    ASSERT_FALSE(isDisallowDropForcedly);
    
    /**
     * @tc.steps: step5. ReportingSupported is set to false.
     * @tc.expected: reportingEnabledFalse is false.
     */
    ASSERT_FALSE(dragDropManager->IsDropAllowed(frameNode));
}

/**
 * @tc.name: FrameNodeDropTestNg023
 * @tc.desc: Test frame node method
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeDropTestNg, FrameNodeDropTestNg023, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a DragDropManager.
     * @tc.expected: dragDropManager is not null.
     */
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();
    ASSERT_NE(dragDropManager, nullptr);

    /**
     * @tc.steps: step2. construct frameNode and update the properties.
     * @tc.expected: frameNode is not null.
     */
    const std::string allowTag(NODE_TAG_A);
    auto frameNodeNullId = ElementRegister::GetInstance()->MakeUniqueId();
    auto frameNode = AceType::MakeRefPtr<FrameNode>(allowTag, frameNodeNullId, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);
    std::set<std::string> allowDrop = { allowTag };
    frameNode->SetAllowDrop(allowDrop);
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step3. construct summaryMap for dragDropManager.
     * @tc.expected: dragDropManager is not null.
     */
    const std::string summary_TAG(NODE_TAG_ONE);
    dragDropManager->summaryMap_.clear();
    dragDropManager->summaryMap_.insert(make_pair(summary_TAG, frameNodeNullId));
    ASSERT_NE(dragDropManager, nullptr);

    /**
     * @tc.steps: step4. Set an isDisallowDropForcedly in the frameNode and then get an isDisallowDropForcedly.
     * @tc.expected: The set isDisallowDropForcedly is the same as the get isDisallowDropForcedly.
     */
    bool isDisallowDrop = false;
    ASSERT_FALSE(isDisallowDrop);
    frameNode->SetDisallowDropForcedly(isDisallowDrop);
    bool isDisallowDropForcedly = frameNode->GetDisallowDropForcedly();
    ASSERT_FALSE(isDisallowDropForcedly);
    
    /**
     * @tc.steps: step5. ReportingSupported is set to false.
     * @tc.expected: reportingEnabledFalse is false.
     */
    ASSERT_FALSE(dragDropManager->IsDropAllowed(frameNode));
}

/**
 * @tc.name: FrameNodeDropTestNg024
 * @tc.desc: Test frame node method
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeDropTestNg, FrameNodeDropTestNg024, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a DragDropManager.
     * @tc.expected: dragDropManager is not null.
     */
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();
    ASSERT_NE(dragDropManager, nullptr);

    /**
     * @tc.steps: step2. construct frameNode and update the properties.
     * @tc.expected: frameNode is not null.
     */
    const std::string allowTag(NODE_TAG_A);
    auto frameNodeNullId = ElementRegister::GetInstance()->MakeUniqueId();
    auto frameNode = AceType::MakeRefPtr<FrameNode>(allowTag, frameNodeNullId, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);
    std::set<std::string> allowDrop = { allowTag };
    frameNode->SetAllowDrop(allowDrop);
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step3. construct summaryMap for dragDropManager.
     * @tc.expected: dragDropManager is not null.
     */
    const std::string summary_TAG(NODE_TAG_A);
    dragDropManager->summaryMap_.clear();
    dragDropManager->summaryMap_.insert(make_pair(summary_TAG, frameNodeNullId));
    ASSERT_NE(dragDropManager, nullptr);

    /**
     * @tc.steps: step4. Set an isDisallowDropForcedly in the frameNode and then get an isDisallowDropForcedly.
     * @tc.expected: The set isDisallowDropForcedly is the same as the get isDisallowDropForcedly.
     */
    bool isDisallowDrop = false;
    ASSERT_FALSE(isDisallowDrop);
    frameNode->SetDisallowDropForcedly(isDisallowDrop);
    bool isDisallowDropForcedly = frameNode->GetDisallowDropForcedly();
    ASSERT_FALSE(isDisallowDropForcedly);
    
    /**
     * @tc.steps: step5. ReportingSupported is set to false.
     * @tc.expected: reportingEnabledFalse is false.
     */
    ASSERT_TRUE(dragDropManager->IsDropAllowed(frameNode));
}

/**
 * @tc.name: FrameNodeDropTestNg025
 * @tc.desc: Test frame node method
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeDropTestNg, FrameNodeDropTestNg025, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a DragDropManager.
     * @tc.expected: dragDropManager is not null.
     */
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();
    ASSERT_NE(dragDropManager, nullptr);

    /**
     * @tc.steps: step2. construct frameNode and update the properties.
     * @tc.expected: frameNode is not null.
     */
    const std::string allowTag(NODE_TAG_EMPTY);
    auto frameNodeNullId = ElementRegister::GetInstance()->MakeUniqueId();
    auto frameNode = AceType::MakeRefPtr<FrameNode>(allowTag, frameNodeNullId, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);
    std::set<std::string> allowDrop;
    frameNode->SetAllowDrop(allowDrop);
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step3. construct summaryMap for dragDropManager.
     * @tc.expected: dragDropManager is not null.
     */
    const std::string summary_TAG(NODE_TAG_SPOT);
    dragDropManager->summaryMap_.clear();
    dragDropManager->summaryMap_.insert(make_pair(summary_TAG, frameNodeNullId));
    ASSERT_NE(dragDropManager, nullptr);

    /**
     * @tc.steps: step4. Set an isDisallowDropForcedly in the frameNode and then get an isDisallowDropForcedly.
     * @tc.expected: The set isDisallowDropForcedly is the same as the get isDisallowDropForcedly.
     */
    bool isDisallowDrop = false;
    ASSERT_FALSE(isDisallowDrop);
    frameNode->SetDisallowDropForcedly(isDisallowDrop);
    bool isDisallowDropForcedly = frameNode->GetDisallowDropForcedly();
    ASSERT_FALSE(isDisallowDropForcedly);
    
    /**
     * @tc.steps: step5. ReportingSupported is set to false.
     * @tc.expected: reportingEnabledFalse is false.
     */
    ASSERT_TRUE(dragDropManager->IsDropAllowed(frameNode));
}

/**
 * @tc.name: FrameNodeDropTestNg026
 * @tc.desc: Test frame node method
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeDropTestNg, FrameNodeDropTestNg026, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a DragDropManager.
     * @tc.expected: dragDropManager is not null.
     */
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();
    ASSERT_NE(dragDropManager, nullptr);

    /**
     * @tc.steps: step2. construct frameNode and update the properties.
     * @tc.expected: frameNode is not null.
     */
    const std::string allowTag(NODE_TAG_EMPTY);
    auto frameNodeNullId = ElementRegister::GetInstance()->MakeUniqueId();
    auto frameNode = AceType::MakeRefPtr<FrameNode>(allowTag, frameNodeNullId, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);
    std::set<std::string> allowDrop;
    frameNode->SetAllowDrop(allowDrop);
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step3. construct summaryMap for dragDropManager.
     * @tc.expected: dragDropManager is not null.
     */
    const std::string summary_TAG(NODE_TAG_ONE);
    dragDropManager->summaryMap_.clear();
    dragDropManager->summaryMap_.insert(make_pair(summary_TAG, frameNodeNullId));
    ASSERT_NE(dragDropManager, nullptr);

    /**
     * @tc.steps: step4. Set an isDisallowDropForcedly in the frameNode and then get an isDisallowDropForcedly.
     * @tc.expected: The set isDisallowDropForcedly is the same as the get isDisallowDropForcedly.
     */
    bool isDisallowDrop = false;
    ASSERT_FALSE(isDisallowDrop);
    frameNode->SetDisallowDropForcedly(isDisallowDrop);
    bool isDisallowDropForcedly = frameNode->GetDisallowDropForcedly();
    ASSERT_FALSE(isDisallowDropForcedly);
    
    /**
     * @tc.steps: step5. ReportingSupported is set to false.
     * @tc.expected: reportingEnabledFalse is false.
     */
    ASSERT_TRUE(dragDropManager->IsDropAllowed(frameNode));
}

/**
 * @tc.name: FrameNodeDropTestNg027
 * @tc.desc: Test frame node method
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeDropTestNg, FrameNodeDropTestNg027, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a DragDropManager.
     * @tc.expected: dragDropManager is not null.
     */
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();
    ASSERT_NE(dragDropManager, nullptr);

    /**
     * @tc.steps: step2. construct frameNode and update the properties.
     * @tc.expected: frameNode is not null.
     */
    const std::string allowTag(NODE_TAG_EMPTY);
    auto frameNodeNullId = ElementRegister::GetInstance()->MakeUniqueId();
    auto frameNode = AceType::MakeRefPtr<FrameNode>(allowTag, frameNodeNullId, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);
    std::set<std::string> allowDrop;
    frameNode->SetAllowDrop(allowDrop);
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step3. construct summaryMap for dragDropManager.
     * @tc.expected: dragDropManager is not null.
     */
    const std::string summary_TAG(NODE_TAG_A);
    dragDropManager->summaryMap_.clear();
    dragDropManager->summaryMap_.insert(make_pair(summary_TAG, frameNodeNullId));
    ASSERT_NE(dragDropManager, nullptr);

    /**
     * @tc.steps: step4. Set an isDisallowDropForcedly in the frameNode and then get an isDisallowDropForcedly.
     * @tc.expected: The set isDisallowDropForcedly is the same as the get isDisallowDropForcedly.
     */
    bool isDisallowDrop = false;
    ASSERT_FALSE(isDisallowDrop);
    frameNode->SetDisallowDropForcedly(isDisallowDrop);
    bool isDisallowDropForcedly = frameNode->GetDisallowDropForcedly();
    ASSERT_FALSE(isDisallowDropForcedly);
    
    /**
     * @tc.steps: step5. ReportingSupported is set to false.
     * @tc.expected: reportingEnabledFalse is false.
     */
    ASSERT_TRUE(dragDropManager->IsDropAllowed(frameNode));
}

/**
 * @tc.name: FrameNodeDropTestNg028
 * @tc.desc: Test frame node method
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeDropTestNg, FrameNodeDropTestNg028, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a DragDropManager.
     * @tc.expected: dragDropManager is not null.
     */
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();
    ASSERT_NE(dragDropManager, nullptr);

    /**
     * @tc.steps: step2. construct frameNode and update the properties.
     * @tc.expected: frameNode is not null.
     */
    const std::string allowTag(NODE_TAG_SPOT);
    auto frameNodeNullId = ElementRegister::GetInstance()->MakeUniqueId();
    auto frameNode = AceType::MakeRefPtr<FrameNode>(allowTag, frameNodeNullId, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);
    std::set<std::string> allowDrop = { allowTag };
    frameNode->SetAllowDrop(allowDrop);
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step3. construct summaryMap for dragDropManager.
     * @tc.expected: dragDropManager is not null.
     */
    dragDropManager->summaryMap_.clear();
    ASSERT_NE(dragDropManager, nullptr);

    /**
     * @tc.steps: step4. Set an isDisallowDropForcedly in the frameNode and then get an isDisallowDropForcedly.
     * @tc.expected: The set isDisallowDropForcedly is the same as the get isDisallowDropForcedly.
     */
    bool isDisallowDrop = false;
    ASSERT_FALSE(isDisallowDrop);
    frameNode->SetDisallowDropForcedly(isDisallowDrop);
    bool isDisallowDropForcedly = frameNode->GetDisallowDropForcedly();
    ASSERT_FALSE(isDisallowDropForcedly);
    
    /**
     * @tc.steps: step5. ReportingSupported is set to false.
     * @tc.expected: reportingEnabledFalse is false.
     */
    ASSERT_TRUE(dragDropManager->IsDropAllowed(frameNode));
}

/**
 * @tc.name: FrameNodeDropTestNg029
 * @tc.desc: Test frame node method
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeDropTestNg, FrameNodeDropTestNg029, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a DragDropManager.
     * @tc.expected: dragDropManager is not null.
     */
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();
    ASSERT_NE(dragDropManager, nullptr);

    /**
     * @tc.steps: step2. construct frameNode and update the properties.
     * @tc.expected: frameNode is not null.
     */
    const std::string allowTag(NODE_TAG_ONE);
    auto frameNodeNullId = ElementRegister::GetInstance()->MakeUniqueId();
    auto frameNode = AceType::MakeRefPtr<FrameNode>(allowTag, frameNodeNullId, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);
    std::set<std::string> allowDrop = { allowTag };
    frameNode->SetAllowDrop(allowDrop);
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step3. construct summaryMap for dragDropManager.
     * @tc.expected: dragDropManager is not null.
     */
    dragDropManager->summaryMap_.clear();
    ASSERT_NE(dragDropManager, nullptr);

    /**
     * @tc.steps: step4. Set an isDisallowDropForcedly in the frameNode and then get an isDisallowDropForcedly.
     * @tc.expected: The set isDisallowDropForcedly is the same as the get isDisallowDropForcedly.
     */
    bool isDisallowDrop = false;
    ASSERT_FALSE(isDisallowDrop);
    frameNode->SetDisallowDropForcedly(isDisallowDrop);
    bool isDisallowDropForcedly = frameNode->GetDisallowDropForcedly();
    ASSERT_FALSE(isDisallowDropForcedly);
    
    /**
     * @tc.steps: step5. ReportingSupported is set to false.
     * @tc.expected: reportingEnabledFalse is false.
     */
    ASSERT_TRUE(dragDropManager->IsDropAllowed(frameNode));
}

/**
 * @tc.name: FrameNodeDropTestNg030
 * @tc.desc: Test frame node method
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeDropTestNg, FrameNodeDropTestNg030, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a DragDropManager.
     * @tc.expected: dragDropManager is not null.
     */
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();
    ASSERT_NE(dragDropManager, nullptr);

    /**
     * @tc.steps: step2. construct frameNode and update the properties.
     * @tc.expected: frameNode is not null.
     */
    const std::string allowTag(NODE_TAG_A);
    auto frameNodeNullId = ElementRegister::GetInstance()->MakeUniqueId();
    auto frameNode = AceType::MakeRefPtr<FrameNode>(allowTag, frameNodeNullId, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);
    std::set<std::string> allowDrop = { allowTag };
    frameNode->SetAllowDrop(allowDrop);
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step3. construct summaryMap for dragDropManager.
     * @tc.expected: dragDropManager is not null.
     */
    dragDropManager->summaryMap_.clear();
    ASSERT_NE(dragDropManager, nullptr);

    /**
     * @tc.steps: step4. Set an isDisallowDropForcedly in the frameNode and then get an isDisallowDropForcedly.
     * @tc.expected: The set isDisallowDropForcedly is the same as the get isDisallowDropForcedly.
     */
    bool isDisallowDrop = false;
    ASSERT_FALSE(isDisallowDrop);
    frameNode->SetDisallowDropForcedly(isDisallowDrop);
    bool isDisallowDropForcedly = frameNode->GetDisallowDropForcedly();
    ASSERT_FALSE(isDisallowDropForcedly);
    
    /**
     * @tc.steps: step5. ReportingSupported is set to false.
     * @tc.expected: reportingEnabledFalse is false.
     */
    ASSERT_TRUE(dragDropManager->IsDropAllowed(frameNode));
}

/**
 * @tc.name: FrameNodeDropTestNg031
 * @tc.desc: Test frame node method
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeDropTestNg, FrameNodeDropTestNg031, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a DragDropManager.
     * @tc.expected: dragDropManager is not null.
     */
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();
    ASSERT_NE(dragDropManager, nullptr);

    /**
     * @tc.steps: step2. construct frameNode and update the properties.
     * @tc.expected: frameNode is not null.
     */
    const std::string allowTag(NODE_TAG_SPOT);
    auto frameNodeNullId = ElementRegister::GetInstance()->MakeUniqueId();
    auto frameNode = AceType::MakeRefPtr<FrameNode>(allowTag, frameNodeNullId, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);
    std::set<std::string> allowDrop = { allowTag };
    frameNode->SetAllowDrop(allowDrop);
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step3. construct summaryMap for dragDropManager.
     * @tc.expected: dragDropManager is not null.
     */
    const std::string summary_TAG(NODE_TAG_SPOT);
    dragDropManager->summaryMap_.clear();
    dragDropManager->summaryMap_.insert(make_pair(summary_TAG, frameNodeNullId));
    ASSERT_NE(dragDropManager, nullptr);

    /**
     * @tc.steps: step4. Set an isDisallowDropForcedly in the frameNode and then get an isDisallowDropForcedly.
     * @tc.expected: The set isDisallowDropForcedly is the same as the get isDisallowDropForcedly.
     */
    bool isDisallowDrop = true;
    ASSERT_TRUE(isDisallowDrop);
    frameNode->SetDisallowDropForcedly(isDisallowDrop);
    bool isDisallowDropForcedly = frameNode->GetDisallowDropForcedly();
    ASSERT_TRUE(isDisallowDropForcedly);
    
    /**
     * @tc.steps: step5. ReportingSupported is set to false.
     * @tc.expected: reportingEnabledFalse is false.
     */
    ASSERT_FALSE(dragDropManager->IsDropAllowed(frameNode));
}

/**
 * @tc.name: FrameNodeDropTestNg032
 * @tc.desc: Test frame node method
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeDropTestNg, FrameNodeDropTestNg032, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a DragDropManager.
     * @tc.expected: dragDropManager is not null.
     */
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();
    ASSERT_NE(dragDropManager, nullptr);

    /**
     * @tc.steps: step2. construct frameNode and update the properties.
     * @tc.expected: frameNode is not null.
     */
    const std::string allowTag(NODE_TAG_SPOT);
    auto frameNodeNullId = ElementRegister::GetInstance()->MakeUniqueId();
    auto frameNode = AceType::MakeRefPtr<FrameNode>(allowTag, frameNodeNullId, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);
    std::set<std::string> allowDrop = { allowTag };
    frameNode->SetAllowDrop(allowDrop);
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step3. construct summaryMap for dragDropManager.
     * @tc.expected: dragDropManager is not null.
     */
    const std::string summary_TAG(NODE_TAG_ONE);
    dragDropManager->summaryMap_.clear();
    dragDropManager->summaryMap_.insert(make_pair(summary_TAG, frameNodeNullId));
    ASSERT_NE(dragDropManager, nullptr);

    /**
     * @tc.steps: step4. Set an isDisallowDropForcedly in the frameNode and then get an isDisallowDropForcedly.
     * @tc.expected: The set isDisallowDropForcedly is the same as the get isDisallowDropForcedly.
     */
    bool isDisallowDrop = true;
    ASSERT_TRUE(isDisallowDrop);
    frameNode->SetDisallowDropForcedly(isDisallowDrop);
    bool isDisallowDropForcedly = frameNode->GetDisallowDropForcedly();
    ASSERT_TRUE(isDisallowDropForcedly);
    
    /**
     * @tc.steps: step5. ReportingSupported is set to false.
     * @tc.expected: reportingEnabledFalse is false.
     */
    ASSERT_FALSE(dragDropManager->IsDropAllowed(frameNode));
}

/**
 * @tc.name: FrameNodeDropTestNg033
 * @tc.desc: Test frame node method
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeDropTestNg, FrameNodeDropTestNg033, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a DragDropManager.
     * @tc.expected: dragDropManager is not null.
     */
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();
    ASSERT_NE(dragDropManager, nullptr);

    /**
     * @tc.steps: step2. construct frameNode and update the properties.
     * @tc.expected: frameNode is not null.
     */
    const std::string allowTag(NODE_TAG_SPOT);
    auto frameNodeNullId = ElementRegister::GetInstance()->MakeUniqueId();
    auto frameNode = AceType::MakeRefPtr<FrameNode>(allowTag, frameNodeNullId, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);
    std::set<std::string> allowDrop = { allowTag };
    frameNode->SetAllowDrop(allowDrop);
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step3. construct summaryMap for dragDropManager.
     * @tc.expected: dragDropManager is not null.
     */
    const std::string summary_TAG(NODE_TAG_A);
    dragDropManager->summaryMap_.clear();
    dragDropManager->summaryMap_.insert(make_pair(summary_TAG, frameNodeNullId));
    ASSERT_NE(dragDropManager, nullptr);

    /**
     * @tc.steps: step4. Set an isDisallowDropForcedly in the frameNode and then get an isDisallowDropForcedly.
     * @tc.expected: The set isDisallowDropForcedly is the same as the get isDisallowDropForcedly.
     */
    bool isDisallowDrop = true;
    ASSERT_TRUE(isDisallowDrop);
    frameNode->SetDisallowDropForcedly(isDisallowDrop);
    bool isDisallowDropForcedly = frameNode->GetDisallowDropForcedly();
    ASSERT_TRUE(isDisallowDropForcedly);
    
    /**
     * @tc.steps: step5. ReportingSupported is set to false.
     * @tc.expected: reportingEnabledFalse is false.
     */
    ASSERT_FALSE(dragDropManager->IsDropAllowed(frameNode));
}

/**
 * @tc.name: FrameNodeDropTestNg034
 * @tc.desc: Test frame node method
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeDropTestNg, FrameNodeDropTestNg034, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a DragDropManager.
     * @tc.expected: dragDropManager is not null.
     */
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();
    ASSERT_NE(dragDropManager, nullptr);

    /**
     * @tc.steps: step2. construct frameNode and update the properties.
     * @tc.expected: frameNode is not null.
     */
    const std::string allowTag(NODE_TAG_ONE);
    auto frameNodeNullId = ElementRegister::GetInstance()->MakeUniqueId();
    auto frameNode = AceType::MakeRefPtr<FrameNode>(allowTag, frameNodeNullId, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);
    std::set<std::string> allowDrop = { allowTag };
    frameNode->SetAllowDrop(allowDrop);
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step3. construct summaryMap for dragDropManager.
     * @tc.expected: dragDropManager is not null.
     */
    const std::string summary_TAG(NODE_TAG_SPOT);
    dragDropManager->summaryMap_.clear();
    dragDropManager->summaryMap_.insert(make_pair(summary_TAG, frameNodeNullId));
    ASSERT_NE(dragDropManager, nullptr);

    /**
     * @tc.steps: step4. Set an isDisallowDropForcedly in the frameNode and then get an isDisallowDropForcedly.
     * @tc.expected: The set isDisallowDropForcedly is the same as the get isDisallowDropForcedly.
     */
    bool isDisallowDrop = true;
    ASSERT_TRUE(isDisallowDrop);
    frameNode->SetDisallowDropForcedly(isDisallowDrop);
    bool isDisallowDropForcedly = frameNode->GetDisallowDropForcedly();
    ASSERT_TRUE(isDisallowDropForcedly);
    
    /**
     * @tc.steps: step5. ReportingSupported is set to false.
     * @tc.expected: reportingEnabledFalse is false.
     */
    ASSERT_FALSE(dragDropManager->IsDropAllowed(frameNode));
}

/**
 * @tc.name: FrameNodeDropTestNg035
 * @tc.desc: Test frame node method
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeDropTestNg, FrameNodeDropTestNg035, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a DragDropManager.
     * @tc.expected: dragDropManager is not null.
     */
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();
    ASSERT_NE(dragDropManager, nullptr);

    /**
     * @tc.steps: step2. construct frameNode and update the properties.
     * @tc.expected: frameNode is not null.
     */
    const std::string allowTag(NODE_TAG_ONE);
    auto frameNodeNullId = ElementRegister::GetInstance()->MakeUniqueId();
    auto frameNode = AceType::MakeRefPtr<FrameNode>(allowTag, frameNodeNullId, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);
    std::set<std::string> allowDrop = { allowTag };
    frameNode->SetAllowDrop(allowDrop);
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step3. construct summaryMap for dragDropManager.
     * @tc.expected: dragDropManager is not null.
     */
    const std::string summary_TAG(NODE_TAG_ONE);
    dragDropManager->summaryMap_.clear();
    dragDropManager->summaryMap_.insert(make_pair(summary_TAG, frameNodeNullId));
    ASSERT_NE(dragDropManager, nullptr);

    /**
     * @tc.steps: step4. Set an isDisallowDropForcedly in the frameNode and then get an isDisallowDropForcedly.
     * @tc.expected: The set isDisallowDropForcedly is the same as the get isDisallowDropForcedly.
     */
    bool isDisallowDrop = true;
    ASSERT_TRUE(isDisallowDrop);
    frameNode->SetDisallowDropForcedly(isDisallowDrop);
    bool isDisallowDropForcedly = frameNode->GetDisallowDropForcedly();
    ASSERT_TRUE(isDisallowDropForcedly);
    
    /**
     * @tc.steps: step5. ReportingSupported is set to false.
     * @tc.expected: reportingEnabledFalse is false.
     */
    ASSERT_FALSE(dragDropManager->IsDropAllowed(frameNode));
}

/**
 * @tc.name: FrameNodeDropTestNg036
 * @tc.desc: Test frame node method
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeDropTestNg, FrameNodeDropTestNg036, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a DragDropManager.
     * @tc.expected: dragDropManager is not null.
     */
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();
    ASSERT_NE(dragDropManager, nullptr);

    /**
     * @tc.steps: step2. construct frameNode and update the properties.
     * @tc.expected: frameNode is not null.
     */
    const std::string allowTag(NODE_TAG_ONE);
    auto frameNodeNullId = ElementRegister::GetInstance()->MakeUniqueId();
    auto frameNode = AceType::MakeRefPtr<FrameNode>(allowTag, frameNodeNullId, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);
    std::set<std::string> allowDrop = { allowTag };
    frameNode->SetAllowDrop(allowDrop);
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step3. construct summaryMap for dragDropManager.
     * @tc.expected: dragDropManager is not null.
     */
    const std::string summary_TAG(NODE_TAG_A);
    dragDropManager->summaryMap_.clear();
    dragDropManager->summaryMap_.insert(make_pair(summary_TAG, frameNodeNullId));
    ASSERT_NE(dragDropManager, nullptr);

    /**
     * @tc.steps: step4. Set an isDisallowDropForcedly in the frameNode and then get an isDisallowDropForcedly.
     * @tc.expected: The set isDisallowDropForcedly is the same as the get isDisallowDropForcedly.
     */
    bool isDisallowDrop = true;
    ASSERT_TRUE(isDisallowDrop);
    frameNode->SetDisallowDropForcedly(isDisallowDrop);
    bool isDisallowDropForcedly = frameNode->GetDisallowDropForcedly();
    ASSERT_TRUE(isDisallowDropForcedly);
    
    /**
     * @tc.steps: step5. ReportingSupported is set to false.
     * @tc.expected: reportingEnabledFalse is false.
     */
    ASSERT_FALSE(dragDropManager->IsDropAllowed(frameNode));
}

/**
 * @tc.name: FrameNodeDropTestNg037
 * @tc.desc: Test frame node method
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeDropTestNg, FrameNodeDropTestNg037, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a DragDropManager.
     * @tc.expected: dragDropManager is not null.
     */
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();
    ASSERT_NE(dragDropManager, nullptr);

    /**
     * @tc.steps: step2. construct frameNode and update the properties.
     * @tc.expected: frameNode is not null.
     */
    const std::string allowTag(NODE_TAG_A);
    auto frameNodeNullId = ElementRegister::GetInstance()->MakeUniqueId();
    auto frameNode = AceType::MakeRefPtr<FrameNode>(allowTag, frameNodeNullId, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);
    std::set<std::string> allowDrop = { allowTag };
    frameNode->SetAllowDrop(allowDrop);
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step3. construct summaryMap for dragDropManager.
     * @tc.expected: dragDropManager is not null.
     */
    const std::string summary_TAG(NODE_TAG_SPOT);
    dragDropManager->summaryMap_.clear();
    dragDropManager->summaryMap_.insert(make_pair(summary_TAG, frameNodeNullId));
    ASSERT_NE(dragDropManager, nullptr);

    /**
     * @tc.steps: step4. Set an isDisallowDropForcedly in the frameNode and then get an isDisallowDropForcedly.
     * @tc.expected: The set isDisallowDropForcedly is the same as the get isDisallowDropForcedly.
     */
    bool isDisallowDrop = true;
    ASSERT_TRUE(isDisallowDrop);
    frameNode->SetDisallowDropForcedly(isDisallowDrop);
    bool isDisallowDropForcedly = frameNode->GetDisallowDropForcedly();
    ASSERT_TRUE(isDisallowDropForcedly);
    
    /**
     * @tc.steps: step5. ReportingSupported is set to false.
     * @tc.expected: reportingEnabledFalse is false.
     */
    ASSERT_FALSE(dragDropManager->IsDropAllowed(frameNode));
}

/**
 * @tc.name: FrameNodeDropTestNg038
 * @tc.desc: Test frame node method
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeDropTestNg, FrameNodeDropTestNg038, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a DragDropManager.
     * @tc.expected: dragDropManager is not null.
     */
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();
    ASSERT_NE(dragDropManager, nullptr);

    /**
     * @tc.steps: step2. construct frameNode and update the properties.
     * @tc.expected: frameNode is not null.
     */
    const std::string allowTag(NODE_TAG_A);
    auto frameNodeNullId = ElementRegister::GetInstance()->MakeUniqueId();
    auto frameNode = AceType::MakeRefPtr<FrameNode>(allowTag, frameNodeNullId, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);
    std::set<std::string> allowDrop = { allowTag };
    frameNode->SetAllowDrop(allowDrop);
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step3. construct summaryMap for dragDropManager.
     * @tc.expected: dragDropManager is not null.
     */
    const std::string summary_TAG(NODE_TAG_ONE);
    dragDropManager->summaryMap_.clear();
    dragDropManager->summaryMap_.insert(make_pair(summary_TAG, frameNodeNullId));
    ASSERT_NE(dragDropManager, nullptr);

    /**
     * @tc.steps: step4. Set an isDisallowDropForcedly in the frameNode and then get an isDisallowDropForcedly.
     * @tc.expected: The set isDisallowDropForcedly is the same as the get isDisallowDropForcedly.
     */
    bool isDisallowDrop = true;
    ASSERT_TRUE(isDisallowDrop);
    frameNode->SetDisallowDropForcedly(isDisallowDrop);
    bool isDisallowDropForcedly = frameNode->GetDisallowDropForcedly();
    ASSERT_TRUE(isDisallowDropForcedly);
    
    /**
     * @tc.steps: step5. ReportingSupported is set to false.
     * @tc.expected: reportingEnabledFalse is false.
     */
    ASSERT_FALSE(dragDropManager->IsDropAllowed(frameNode));
}

/**
 * @tc.name: FrameNodeDropTestNg039
 * @tc.desc: Test frame node method
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeDropTestNg, FrameNodeDropTestNg039, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a DragDropManager.
     * @tc.expected: dragDropManager is not null.
     */
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();
    ASSERT_NE(dragDropManager, nullptr);

    /**
     * @tc.steps: step2. construct frameNode and update the properties.
     * @tc.expected: frameNode is not null.
     */
    const std::string allowTag(NODE_TAG_A);
    auto frameNodeNullId = ElementRegister::GetInstance()->MakeUniqueId();
    auto frameNode = AceType::MakeRefPtr<FrameNode>(allowTag, frameNodeNullId, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);
    std::set<std::string> allowDrop = { allowTag };
    frameNode->SetAllowDrop(allowDrop);
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step3. construct summaryMap for dragDropManager.
     * @tc.expected: dragDropManager is not null.
     */
    const std::string summary_TAG(NODE_TAG_A);
    dragDropManager->summaryMap_.clear();
    dragDropManager->summaryMap_.insert(make_pair(summary_TAG, frameNodeNullId));
    ASSERT_NE(dragDropManager, nullptr);

    /**
     * @tc.steps: step4. Set an isDisallowDropForcedly in the frameNode and then get an isDisallowDropForcedly.
     * @tc.expected: The set isDisallowDropForcedly is the same as the get isDisallowDropForcedly.
     */
    bool isDisallowDrop = true;
    ASSERT_TRUE(isDisallowDrop);
    frameNode->SetDisallowDropForcedly(isDisallowDrop);
    bool isDisallowDropForcedly = frameNode->GetDisallowDropForcedly();
    ASSERT_TRUE(isDisallowDropForcedly);
    
    /**
     * @tc.steps: step5. ReportingSupported is set to false.
     * @tc.expected: reportingEnabledFalse is false.
     */
    ASSERT_FALSE(dragDropManager->IsDropAllowed(frameNode));
}

/**
 * @tc.name: FrameNodeDropTestNg040
 * @tc.desc: Test frame node method
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeDropTestNg, FrameNodeDropTestNg040, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a DragDropManager.
     * @tc.expected: dragDropManager is not null.
     */
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();
    ASSERT_NE(dragDropManager, nullptr);

    /**
     * @tc.steps: step2. construct frameNode and update the properties.
     * @tc.expected: frameNode is not null.
     */
    const std::string allowTag(NODE_TAG_EMPTY);
    auto frameNodeNullId = ElementRegister::GetInstance()->MakeUniqueId();
    auto frameNode = AceType::MakeRefPtr<FrameNode>(allowTag, frameNodeNullId, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);
    std::set<std::string> allowDrop;
    frameNode->SetAllowDrop(allowDrop);
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step3. construct summaryMap for dragDropManager.
     * @tc.expected: dragDropManager is not null.
     */
    const std::string summary_TAG(NODE_TAG_SPOT);
    dragDropManager->summaryMap_.clear();
    dragDropManager->summaryMap_.insert(make_pair(summary_TAG, frameNodeNullId));
    ASSERT_NE(dragDropManager, nullptr);

    /**
     * @tc.steps: step4. Set an isDisallowDropForcedly in the frameNode and then get an isDisallowDropForcedly.
     * @tc.expected: The set isDisallowDropForcedly is the same as the get isDisallowDropForcedly.
     */
    bool isDisallowDrop = true;
    ASSERT_TRUE(isDisallowDrop);
    frameNode->SetDisallowDropForcedly(isDisallowDrop);
    bool isDisallowDropForcedly = frameNode->GetDisallowDropForcedly();
    ASSERT_TRUE(isDisallowDropForcedly);
    
    /**
     * @tc.steps: step5. ReportingSupported is set to false.
     * @tc.expected: reportingEnabledFalse is false.
     */
    ASSERT_FALSE(dragDropManager->IsDropAllowed(frameNode));
}

/**
 * @tc.name: FrameNodeDropTestNg041
 * @tc.desc: Test frame node method
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeDropTestNg, FrameNodeDropTestNg041, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a DragDropManager.
     * @tc.expected: dragDropManager is not null.
     */
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();
    ASSERT_NE(dragDropManager, nullptr);

    /**
     * @tc.steps: step2. construct frameNode and update the properties.
     * @tc.expected: frameNode is not null.
     */
    const std::string allowTag(NODE_TAG_EMPTY);
    auto frameNodeNullId = ElementRegister::GetInstance()->MakeUniqueId();
    auto frameNode = AceType::MakeRefPtr<FrameNode>(allowTag, frameNodeNullId, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);
    std::set<std::string> allowDrop;
    frameNode->SetAllowDrop(allowDrop);
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step3. construct summaryMap for dragDropManager.
     * @tc.expected: dragDropManager is not null.
     */
    const std::string summary_TAG(NODE_TAG_ONE);
    dragDropManager->summaryMap_.clear();
    dragDropManager->summaryMap_.insert(make_pair(summary_TAG, frameNodeNullId));
    ASSERT_NE(dragDropManager, nullptr);

    /**
     * @tc.steps: step4. Set an isDisallowDropForcedly in the frameNode and then get an isDisallowDropForcedly.
     * @tc.expected: The set isDisallowDropForcedly is the same as the get isDisallowDropForcedly.
     */
    bool isDisallowDrop = true;
    ASSERT_TRUE(isDisallowDrop);
    frameNode->SetDisallowDropForcedly(isDisallowDrop);
    bool isDisallowDropForcedly = frameNode->GetDisallowDropForcedly();
    ASSERT_TRUE(isDisallowDropForcedly);
    
    /**
     * @tc.steps: step5. ReportingSupported is set to false.
     * @tc.expected: reportingEnabledFalse is false.
     */
    ASSERT_FALSE(dragDropManager->IsDropAllowed(frameNode));
}

/**
 * @tc.name: FrameNodeDropTestNg042
 * @tc.desc: Test frame node method
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeDropTestNg, FrameNodeDropTestNg042, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a DragDropManager.
     * @tc.expected: dragDropManager is not null.
     */
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();
    ASSERT_NE(dragDropManager, nullptr);

    /**
     * @tc.steps: step2. construct frameNode and update the properties.
     * @tc.expected: frameNode is not null.
     */
    const std::string allowTag(NODE_TAG_EMPTY);
    auto frameNodeNullId = ElementRegister::GetInstance()->MakeUniqueId();
    auto frameNode = AceType::MakeRefPtr<FrameNode>(allowTag, frameNodeNullId, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);
    std::set<std::string> allowDrop;
    frameNode->SetAllowDrop(allowDrop);
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step3. construct summaryMap for dragDropManager.
     * @tc.expected: dragDropManager is not null.
     */
    const std::string summary_TAG(NODE_TAG_A);
    dragDropManager->summaryMap_.clear();
    dragDropManager->summaryMap_.insert(make_pair(summary_TAG, frameNodeNullId));
    ASSERT_NE(dragDropManager, nullptr);

    /**
     * @tc.steps: step4. Set an isDisallowDropForcedly in the frameNode and then get an isDisallowDropForcedly.
     * @tc.expected: The set isDisallowDropForcedly is the same as the get isDisallowDropForcedly.
     */
    bool isDisallowDrop = true;
    ASSERT_TRUE(isDisallowDrop);
    frameNode->SetDisallowDropForcedly(isDisallowDrop);
    bool isDisallowDropForcedly = frameNode->GetDisallowDropForcedly();
    ASSERT_TRUE(isDisallowDropForcedly);
    
    /**
     * @tc.steps: step5. ReportingSupported is set to false.
     * @tc.expected: reportingEnabledFalse is false.
     */
    ASSERT_FALSE(dragDropManager->IsDropAllowed(frameNode));
}

/**
 * @tc.name: FrameNodeDropTestNg043
 * @tc.desc: Test frame node method
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeDropTestNg, FrameNodeDropTestNg043, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a DragDropManager.
     * @tc.expected: dragDropManager is not null.
     */
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();
    ASSERT_NE(dragDropManager, nullptr);

    /**
     * @tc.steps: step2. construct frameNode and update the properties.
     * @tc.expected: frameNode is not null.
     */
    const std::string allowTag(NODE_TAG_SPOT);
    auto frameNodeNullId = ElementRegister::GetInstance()->MakeUniqueId();
    auto frameNode = AceType::MakeRefPtr<FrameNode>(allowTag, frameNodeNullId, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);
    std::set<std::string> allowDrop = { allowTag };
    frameNode->SetAllowDrop(allowDrop);
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step3. construct summaryMap for dragDropManager.
     * @tc.expected: dragDropManager is not null.
     */
    const std::string summary_TAG(NODE_TAG_EMPTY);
    dragDropManager->summaryMap_.clear();
    ASSERT_NE(dragDropManager, nullptr);

    /**
     * @tc.steps: step4. Set an isDisallowDropForcedly in the frameNode and then get an isDisallowDropForcedly.
     * @tc.expected: The set isDisallowDropForcedly is the same as the get isDisallowDropForcedly.
     */
    bool isDisallowDrop = true;
    ASSERT_TRUE(isDisallowDrop);
    frameNode->SetDisallowDropForcedly(isDisallowDrop);
    bool isDisallowDropForcedly = frameNode->GetDisallowDropForcedly();
    ASSERT_TRUE(isDisallowDropForcedly);
    
    /**
     * @tc.steps: step5. ReportingSupported is set to false.
     * @tc.expected: reportingEnabledFalse is false.
     */
    ASSERT_FALSE(dragDropManager->IsDropAllowed(frameNode));
}

/**
 * @tc.name: FrameNodeDropTestNg044
 * @tc.desc: Test frame node method
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeDropTestNg, FrameNodeDropTestNg044, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a DragDropManager.
     * @tc.expected: dragDropManager is not null.
     */
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();
    ASSERT_NE(dragDropManager, nullptr);

    /**
     * @tc.steps: step2. construct frameNode and update the properties.
     * @tc.expected: frameNode is not null.
     */
    const std::string allowTag(NODE_TAG_ONE);
    auto frameNodeNullId = ElementRegister::GetInstance()->MakeUniqueId();
    auto frameNode = AceType::MakeRefPtr<FrameNode>(allowTag, frameNodeNullId, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);
    std::set<std::string> allowDrop = { allowTag };
    frameNode->SetAllowDrop(allowDrop);
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step3. construct summaryMap for dragDropManager.
     * @tc.expected: dragDropManager is not null.
     */
    const std::string summary_TAG(NODE_TAG_EMPTY);
    dragDropManager->summaryMap_.clear();
    ASSERT_NE(dragDropManager, nullptr);

    /**
     * @tc.steps: step4. Set an isDisallowDropForcedly in the frameNode and then get an isDisallowDropForcedly.
     * @tc.expected: The set isDisallowDropForcedly is the same as the get isDisallowDropForcedly.
     */
    bool isDisallowDrop = true;
    ASSERT_TRUE(isDisallowDrop);
    frameNode->SetDisallowDropForcedly(isDisallowDrop);
    bool isDisallowDropForcedly = frameNode->GetDisallowDropForcedly();
    ASSERT_TRUE(isDisallowDropForcedly);
    
    /**
     * @tc.steps: step5. ReportingSupported is set to false.
     * @tc.expected: reportingEnabledFalse is false.
     */
    ASSERT_FALSE(dragDropManager->IsDropAllowed(frameNode));
}

/**
 * @tc.name: FrameNodeDropTestNg045
 * @tc.desc: Test frame node method
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeDropTestNg, FrameNodeDropTestNg045, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a DragDropManager.
     * @tc.expected: dragDropManager is not null.
     */
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();
    ASSERT_NE(dragDropManager, nullptr);

    /**
     * @tc.steps: step2. construct frameNode and update the properties.
     * @tc.expected: frameNode is not null.
     */
    const std::string allowTag(NODE_TAG_A);
    auto frameNodeNullId = ElementRegister::GetInstance()->MakeUniqueId();
    auto frameNode = AceType::MakeRefPtr<FrameNode>(allowTag, frameNodeNullId, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);
    std::set<std::string> allowDrop = { allowTag };
    frameNode->SetAllowDrop(allowDrop);
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step3. construct summaryMap for dragDropManager.
     * @tc.expected: dragDropManager is not null.
     */
    const std::string summary_TAG(NODE_TAG_EMPTY);
    dragDropManager->summaryMap_.clear();
    ASSERT_NE(dragDropManager, nullptr);

    /**
     * @tc.steps: step4. Set an isDisallowDropForcedly in the frameNode and then get an isDisallowDropForcedly.
     * @tc.expected: The set isDisallowDropForcedly is the same as the get isDisallowDropForcedly.
     */
    bool isDisallowDrop = true;
    ASSERT_TRUE(isDisallowDrop);
    frameNode->SetDisallowDropForcedly(isDisallowDrop);
    bool isDisallowDropForcedly = frameNode->GetDisallowDropForcedly();
    ASSERT_TRUE(isDisallowDropForcedly);
    
    /**
     * @tc.steps: step5. ReportingSupported is set to false.
     * @tc.expected: reportingEnabledFalse is false.
     */
    ASSERT_FALSE(dragDropManager->IsDropAllowed(frameNode));
}

/**
 * @tc.name: FrameNodeDropTestNg046
 * @tc.desc: Test frame node method
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeDropTestNg, FrameNodeDropTestNg046, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a DragDropManager.
     * @tc.expected: dragDropManager is not null.
     */
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();
    ASSERT_NE(dragDropManager, nullptr);

    /**
     * @tc.steps: step2. construct frameNode and update the properties.
     * @tc.expected: frameNode is not null.
     */
    const std::string allowTag(NODE_TAG_EMPTY);
    auto frameNodeNullId = ElementRegister::GetInstance()->MakeUniqueId();
    auto frameNode = AceType::MakeRefPtr<FrameNode>(allowTag, frameNodeNullId, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);
    std::set<std::string> allowDrop = { allowTag };
    frameNode->SetAllowDrop(allowDrop);
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step3. construct summaryMap for dragDropManager.
     * @tc.expected: dragDropManager is not null.
     */
    const std::string summary_TAG(NODE_TAG_EMPTY);
    dragDropManager->summaryMap_.clear();
    dragDropManager->summaryMap_.insert(make_pair(summary_TAG, frameNodeNullId));
    ASSERT_NE(dragDropManager, nullptr);

    /**
     * @tc.steps: step4. Set an isDisallowDropForcedly in the frameNode and then get an isDisallowDropForcedly.
     * @tc.expected: The set isDisallowDropForcedly is the same as the get isDisallowDropForcedly.
     */
    bool isDisallowDrop = false;
    ASSERT_FALSE(isDisallowDrop);
    frameNode->SetDisallowDropForcedly(isDisallowDrop);
    bool isDisallowDropForcedly = frameNode->GetDisallowDropForcedly();
    ASSERT_FALSE(isDisallowDropForcedly);
    
    /**
     * @tc.steps: step5. ReportingSupported is set to false.
     * @tc.expected: reportingEnabledFalse is false.
     */
    ASSERT_TRUE(dragDropManager->IsDropAllowed(frameNode));
}

/**
 * @tc.name: FrameNodeDropTestNg047
 * @tc.desc: Test frame node method
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeDropTestNg, FrameNodeDropTestNg047, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a DragDropManager.
     * @tc.expected: dragDropManager is not null.
     */
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();
    ASSERT_NE(dragDropManager, nullptr);

    /**
     * @tc.steps: step2. construct frameNode and update the properties.
     * @tc.expected: frameNode is not null.
     */
    const std::string allowTag(NODE_TAG_EMPTY);
    auto frameNodeNullId = ElementRegister::GetInstance()->MakeUniqueId();
    auto frameNode = AceType::MakeRefPtr<FrameNode>(allowTag, frameNodeNullId, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);
    std::set<std::string> allowDrop = { allowTag };
    frameNode->SetAllowDrop(allowDrop);
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step3. construct summaryMap for dragDropManager.
     * @tc.expected: dragDropManager is not null.
     */
    const std::string summary_TAG(NODE_TAG_EMPTY);
    dragDropManager->summaryMap_.clear();
    ASSERT_NE(dragDropManager, nullptr);

    /**
     * @tc.steps: step4. Set an isDisallowDropForcedly in the frameNode and then get an isDisallowDropForcedly.
     * @tc.expected: The set isDisallowDropForcedly is the same as the get isDisallowDropForcedly.
     */
    bool isDisallowDrop = true;
    ASSERT_TRUE(isDisallowDrop);
    frameNode->SetDisallowDropForcedly(isDisallowDrop);
    bool isDisallowDropForcedly = frameNode->GetDisallowDropForcedly();
    ASSERT_TRUE(isDisallowDropForcedly);
    
    /**
     * @tc.steps: step5. ReportingSupported is set to false.
     * @tc.expected: reportingEnabledFalse is false.
     */
    ASSERT_FALSE(dragDropManager->IsDropAllowed(frameNode));
}

/**
 * @tc.name: FrameNodeDropTestNg048
 * @tc.desc: Test frame node method
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeDropTestNg, FrameNodeDropTestNg048, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a DragDropManager.
     * @tc.expected: dragDropManager is not null.
     */
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();
    ASSERT_NE(dragDropManager, nullptr);

    /**
     * @tc.steps: step2. construct frameNode and update the properties.
     * @tc.expected: frameNode is not null.
     */
    const std::string allowTag(NODE_TAG_SPOT);
    auto frameNodeNullId = ElementRegister::GetInstance()->MakeUniqueId();
    auto frameNode = AceType::MakeRefPtr<FrameNode>(allowTag, frameNodeNullId, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);
    std::set<std::string> allowDrop = { allowTag };
    frameNode->SetAllowDrop(allowDrop);
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step3. construct summaryMap for dragDropManager.
     * @tc.expected: dragDropManager is not null.
     */
    const std::string summary_TAG(NODE_TAG_EMPTY);
    dragDropManager->summaryMap_.clear();
    ASSERT_NE(dragDropManager, nullptr);

    /**
     * @tc.steps: step4. Set an isDisallowDropForcedly in the frameNode and then get an isDisallowDropForcedly.
     * @tc.expected: The set isDisallowDropForcedly is the same as the get isDisallowDropForcedly.
     */
    bool isDisallowDrop = false;
    ASSERT_FALSE(isDisallowDrop);
    frameNode->SetDisallowDropForcedly(isDisallowDrop);
    bool isDisallowDropForcedly = frameNode->GetDisallowDropForcedly();
    ASSERT_FALSE(isDisallowDropForcedly);
    
    /**
     * @tc.steps: step5. ReportingSupported is set to false.
     * @tc.expected: reportingEnabledFalse is false.
     */
    ASSERT_TRUE(dragDropManager->IsDropAllowed(frameNode));
}

/**
 * @tc.name: FrameNodeDropTestNg049
 * @tc.desc: Test frame node method
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeDropTestNg, FrameNodeDropTestNg049, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a DragDropManager.
     * @tc.expected: dragDropManager is not null.
     */
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();
    ASSERT_NE(dragDropManager, nullptr);

    /**
     * @tc.steps: step2. construct frameNode and update the properties.
     * @tc.expected: frameNode is not null.
     */
    const std::string allowTag(NODE_TAG_ONE);
    auto frameNodeNullId = ElementRegister::GetInstance()->MakeUniqueId();
    auto frameNode = AceType::MakeRefPtr<FrameNode>(allowTag, frameNodeNullId, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);
    std::set<std::string> allowDrop = { allowTag };
    frameNode->SetAllowDrop(allowDrop);
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step3. construct summaryMap for dragDropManager.
     * @tc.expected: dragDropManager is not null.
     */
    const std::string summary_TAG(NODE_TAG_EMPTY);
    dragDropManager->summaryMap_.clear();
    ASSERT_NE(dragDropManager, nullptr);

    /**
     * @tc.steps: step4. Set an isDisallowDropForcedly in the frameNode and then get an isDisallowDropForcedly.
     * @tc.expected: The set isDisallowDropForcedly is the same as the get isDisallowDropForcedly.
     */
    bool isDisallowDrop = false;
    ASSERT_FALSE(isDisallowDrop);
    frameNode->SetDisallowDropForcedly(isDisallowDrop);
    bool isDisallowDropForcedly = frameNode->GetDisallowDropForcedly();
    ASSERT_FALSE(isDisallowDropForcedly);
    
    /**
     * @tc.steps: step5. ReportingSupported is set to false.
     * @tc.expected: reportingEnabledFalse is false.
     */
    ASSERT_TRUE(dragDropManager->IsDropAllowed(frameNode));
}

/**
 * @tc.name: FrameNodeDropTestNg050
 * @tc.desc: Test frame node method
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeDropTestNg, FrameNodeDropTestNg050, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a DragDropManager.
     * @tc.expected: dragDropManager is not null.
     */
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();
    ASSERT_NE(dragDropManager, nullptr);

    /**
     * @tc.steps: step2. construct frameNode and update the properties.
     * @tc.expected: frameNode is not null.
     */
    const std::string allowTag(NODE_TAG_A);
    auto frameNodeNullId = ElementRegister::GetInstance()->MakeUniqueId();
    auto frameNode = AceType::MakeRefPtr<FrameNode>(allowTag, frameNodeNullId, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);
    std::set<std::string> allowDrop = { allowTag };
    frameNode->SetAllowDrop(allowDrop);
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step3. construct summaryMap for dragDropManager.
     * @tc.expected: dragDropManager is not null.
     */
    const std::string summary_TAG(NODE_TAG_EMPTY);
    dragDropManager->summaryMap_.clear();
    ASSERT_NE(dragDropManager, nullptr);

    /**
     * @tc.steps: step4. Set an isDisallowDropForcedly in the frameNode and then get an isDisallowDropForcedly.
     * @tc.expected: The set isDisallowDropForcedly is the same as the get isDisallowDropForcedly.
     */
    bool isDisallowDrop = false;
    ASSERT_FALSE(isDisallowDrop);
    frameNode->SetDisallowDropForcedly(isDisallowDrop);
    bool isDisallowDropForcedly = frameNode->GetDisallowDropForcedly();
    ASSERT_FALSE(isDisallowDropForcedly);
    
    /**
     * @tc.steps: step5. ReportingSupported is set to false.
     * @tc.expected: reportingEnabledFalse is false.
     */
    ASSERT_TRUE(dragDropManager->IsDropAllowed(frameNode));
}

/**
 * @tc.name: FrameNodeDropTestNg051
 * @tc.desc: Test frame node method
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeDropTestNg, FrameNodeDropTestNg051, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a DragDropManager.
     * @tc.expected: dragDropManager is not null.
     */
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();
    ASSERT_NE(dragDropManager, nullptr);

    /**
     * @tc.steps: step2. construct frameNode and update the properties.
     * @tc.expected: frameNode is not null.
     */
    const std::string allowTag(NODE_TAG_EMPTY);
    auto frameNodeNullId = ElementRegister::GetInstance()->MakeUniqueId();
    auto frameNode = AceType::MakeRefPtr<FrameNode>(allowTag, frameNodeNullId, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);
    std::set<std::string> allowDrop = { allowTag };
    frameNode->SetAllowDrop(allowDrop);
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step3. construct summaryMap for dragDropManager.
     * @tc.expected: dragDropManager is not null.
     */
    const std::string summary_TAG(NODE_TAG_EMPTY);
    dragDropManager->summaryMap_.clear();
    ASSERT_NE(dragDropManager, nullptr);

    /**
     * @tc.steps: step4. Set an isDisallowDropForcedly in the frameNode and then get an isDisallowDropForcedly.
     * @tc.expected: The set isDisallowDropForcedly is the same as the get isDisallowDropForcedly.
     */
    bool isDisallowDrop = false;
    ASSERT_FALSE(isDisallowDrop);
    frameNode->SetDisallowDropForcedly(isDisallowDrop);
    bool isDisallowDropForcedly = frameNode->GetDisallowDropForcedly();
    ASSERT_FALSE(isDisallowDropForcedly);
    
    /**
     * @tc.steps: step5. ReportingSupported is set to false.
     * @tc.expected: reportingEnabledFalse is false.
     */
    ASSERT_TRUE(dragDropManager->IsDropAllowed(frameNode));
}

/**
 * @tc.name: FrameNodeDropTestNg048
 * @tc.desc: Test frame node method
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeDropTestNg, FrameNodeDropTestNg052, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a DragDropManager.
     * @tc.expected: dragDropManager is not null.
     */
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();
    ASSERT_NE(dragDropManager, nullptr);

    /**
     * @tc.steps: step2. construct frameNode and update the properties.
     * @tc.expected: frameNode is not null.
     */
    const std::string allowTag(NODE_TAG_SPOT);
    auto frameNodeNullId = ElementRegister::GetInstance()->MakeUniqueId();
    auto frameNode = AceType::MakeRefPtr<FrameNode>(allowTag, frameNodeNullId, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);
    std::set<std::string> allowDrop = { allowTag };
    frameNode->SetAllowDrop(allowDrop);
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step3. construct summaryMap for dragDropManager.
     * @tc.expected: dragDropManager is not null.
     */
    const std::string summary_TAG(NODE_TAG_EMPTY);
    dragDropManager->summaryMap_.clear();
    ASSERT_NE(dragDropManager, nullptr);

    /**
     * @tc.steps: step4. Set an isDisallowDropForcedly in the frameNode and then get an isDisallowDropForcedly.
     * @tc.expected: The set isDisallowDropForcedly is the same as the get isDisallowDropForcedly.
     */
    bool isDisallowDrop = true;
    ASSERT_TRUE(isDisallowDrop);
    frameNode->SetDisallowDropForcedly(isDisallowDrop);
    bool isDisallowDropForcedly = frameNode->GetDisallowDropForcedly();
    ASSERT_TRUE(isDisallowDropForcedly);
    
    /**
     * @tc.steps: step5. ReportingSupported is set to false.
     * @tc.expected: reportingEnabledFalse is false.
     */
    ASSERT_FALSE(dragDropManager->IsDropAllowed(frameNode));
}

/**
 * @tc.name: FrameNodeDropTestNg049
 * @tc.desc: Test frame node method
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeDropTestNg, FrameNodeDropTestNg053, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a DragDropManager.
     * @tc.expected: dragDropManager is not null.
     */
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();
    ASSERT_NE(dragDropManager, nullptr);

    /**
     * @tc.steps: step2. construct frameNode and update the properties.
     * @tc.expected: frameNode is not null.
     */
    const std::string allowTag(NODE_TAG_ONE);
    auto frameNodeNullId = ElementRegister::GetInstance()->MakeUniqueId();
    auto frameNode = AceType::MakeRefPtr<FrameNode>(allowTag, frameNodeNullId, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);
    std::set<std::string> allowDrop = { allowTag };
    frameNode->SetAllowDrop(allowDrop);
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step3. construct summaryMap for dragDropManager.
     * @tc.expected: dragDropManager is not null.
     */
    const std::string summary_TAG(NODE_TAG_EMPTY);
    dragDropManager->summaryMap_.clear();
    ASSERT_NE(dragDropManager, nullptr);

    /**
     * @tc.steps: step4. Set an isDisallowDropForcedly in the frameNode and then get an isDisallowDropForcedly.
     * @tc.expected: The set isDisallowDropForcedly is the same as the get isDisallowDropForcedly.
     */
    bool isDisallowDrop = true;
    ASSERT_TRUE(isDisallowDrop);
    frameNode->SetDisallowDropForcedly(isDisallowDrop);
    bool isDisallowDropForcedly = frameNode->GetDisallowDropForcedly();
    ASSERT_TRUE(isDisallowDropForcedly);
    
    /**
     * @tc.steps: step5. ReportingSupported is set to false.
     * @tc.expected: reportingEnabledFalse is false.
     */
    ASSERT_FALSE(dragDropManager->IsDropAllowed(frameNode));
}

/**
 * @tc.name: FrameNodeDropTestNg050
 * @tc.desc: Test frame node method
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeDropTestNg, FrameNodeDropTestNg054, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a DragDropManager.
     * @tc.expected: dragDropManager is not null.
     */
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();
    ASSERT_NE(dragDropManager, nullptr);

    /**
     * @tc.steps: step2. construct frameNode and update the properties.
     * @tc.expected: frameNode is not null.
     */
    const std::string allowTag(NODE_TAG_A);
    auto frameNodeNullId = ElementRegister::GetInstance()->MakeUniqueId();
    auto frameNode = AceType::MakeRefPtr<FrameNode>(allowTag, frameNodeNullId, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);
    std::set<std::string> allowDrop = { allowTag };
    frameNode->SetAllowDrop(allowDrop);
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step3. construct summaryMap for dragDropManager.
     * @tc.expected: dragDropManager is not null.
     */
    const std::string summary_TAG(NODE_TAG_EMPTY);
    dragDropManager->summaryMap_.clear();
    ASSERT_NE(dragDropManager, nullptr);

    /**
     * @tc.steps: step4. Set an isDisallowDropForcedly in the frameNode and then get an isDisallowDropForcedly.
     * @tc.expected: The set isDisallowDropForcedly is the same as the get isDisallowDropForcedly.
     */
    bool isDisallowDrop = true;
    ASSERT_TRUE(isDisallowDrop);
    frameNode->SetDisallowDropForcedly(isDisallowDrop);
    bool isDisallowDropForcedly = frameNode->GetDisallowDropForcedly();
    ASSERT_TRUE(isDisallowDropForcedly);
    
    /**
     * @tc.steps: step5. ReportingSupported is set to false.
     * @tc.expected: reportingEnabledFalse is false.
     */
    ASSERT_FALSE(dragDropManager->IsDropAllowed(frameNode));
}

/**
 * @tc.name: FrameNodeDropTestNg051
 * @tc.desc: Test frame node method
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeDropTestNg, FrameNodeDropTestNg055, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a DragDropManager.
     * @tc.expected: dragDropManager is not null.
     */
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();
    ASSERT_NE(dragDropManager, nullptr);

    /**
     * @tc.steps: step2. construct frameNode and update the properties.
     * @tc.expected: frameNode is not null.
     */
    const std::string allowTag(NODE_TAG_EMPTY);
    auto frameNodeNullId = ElementRegister::GetInstance()->MakeUniqueId();
    auto frameNode = AceType::MakeRefPtr<FrameNode>(allowTag, frameNodeNullId, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);
    std::set<std::string> allowDrop = { allowTag };
    frameNode->SetAllowDrop(allowDrop);
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step3. construct summaryMap for dragDropManager.
     * @tc.expected: dragDropManager is not null.
     */
    const std::string summary_TAG(NODE_TAG_EMPTY);
    dragDropManager->summaryMap_.clear();
    ASSERT_NE(dragDropManager, nullptr);

    /**
     * @tc.steps: step4. Set an isDisallowDropForcedly in the frameNode and then get an isDisallowDropForcedly.
     * @tc.expected: The set isDisallowDropForcedly is the same as the get isDisallowDropForcedly.
     */
    bool isDisallowDrop = true;
    ASSERT_TRUE(isDisallowDrop);
    frameNode->SetDisallowDropForcedly(isDisallowDrop);
    bool isDisallowDropForcedly = frameNode->GetDisallowDropForcedly();
    ASSERT_TRUE(isDisallowDropForcedly);
    
    /**
     * @tc.steps: step5. ReportingSupported is set to false.
     * @tc.expected: reportingEnabledFalse is false.
     */
    ASSERT_FALSE(dragDropManager->IsDropAllowed(frameNode));
}
} // namespace OHOS::Ace::NG