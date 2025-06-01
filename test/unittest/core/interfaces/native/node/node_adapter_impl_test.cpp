/*
 * Copyright (c) 2025 iSoftStone Information Technology (Group) Co.,Ltd.
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

#include <optional>

#include "gtest/gtest.h"
#include "test/mock/core/pattern/mock_pattern.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

#include "core/interfaces/native/node/node_adapter_impl.h"
#include "core/interfaces/arkoala/arkoala_api.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {

class NodeAdapterImplTest : public testing::Test {
public:
    static void SetUpTestSuite()
    {
        MockPipelineContext::SetUp();
    }
    static void TearDownTestSuite()
    {
        MockPipelineContext::TearDown();
    }
};

/**
 * @tc.name: AttachHostNode001
 * @tc.desc: handle is null, AttachHostNode return true.
 * @tc.type: FUNC
 */
HWTEST_F(NodeAdapterImplTest, AttachHostNode001, TestSize.Level1)
{
    /**
     * @tc.steps1 Create a frameNode.
     */
    const ArkUINodeAdapterAPI* node = NodeAdapter::GetNodeAdapterAPI();
    CHECK_NULL_VOID(node);
    ArkUINodeAdapterHandle handle = nullptr;
    auto frameNode1 = FrameNode::CreateFrameNode("framenode", 1, AceType::MakeRefPtr<Pattern>(), false);
    CHECK_NULL_VOID(frameNode1);
    ArkUINodeHandle host = reinterpret_cast<ArkUINodeHandle>(Referenced::RawPtr(frameNode1));
    /**
     * @tc.steps2: handle is null, return true.
     * @tc.expected: return true
     */
    auto attachResult = node->attachHostNode(handle, host);
    EXPECT_TRUE(attachResult);
}

/**
 * @tc.name: AttachHostNode002
 * @tc.desc: host is null, AttachHostNode return true.
 * @tc.type: FUNC
 */
HWTEST_F(NodeAdapterImplTest, AttachHostNode002, TestSize.Level1)
{
    /**
     * @tc.steps1 Create a handle.
     */
    const ArkUINodeAdapterAPI* node = NodeAdapter::GetNodeAdapterAPI();
    CHECK_NULL_VOID(node);
    ArkUINodeAdapterHandle handle = node->create();
    ArkUINodeHandle host = nullptr;

    /**
     * @tc.steps2: handle is null, return true.
     * @tc.expected: return true
     */
    auto attachResult = node->attachHostNode(handle, host);
    EXPECT_TRUE(attachResult);
}

/**
 * @tc.name: AttachHostNode003
 * @tc.desc: OnAttachAdapter return true, AttachHostNode return true.
 * @tc.type: FUNC
 */
HWTEST_F(NodeAdapterImplTest, AttachHostNode003, TestSize.Level1)
{
    /**
     * @tc.steps1 Create a handle.
     */
    const ArkUINodeAdapterAPI* node = NodeAdapter::GetNodeAdapterAPI();
    CHECK_NULL_VOID(node);
    ArkUINodeAdapterHandle handle = node->create();
    auto frameNode1 = FrameNode::CreateFrameNode("framenode", 1, AceType::MakeRefPtr<Pattern>(), false);
    CHECK_NULL_VOID(frameNode1);
    ArkUINodeHandle host = reinterpret_cast<ArkUINodeHandle>(Referenced::RawPtr(frameNode1));

    /**
     * @tc.steps2: OnAttachAdapter return true, return true.
     * @tc.expected: return true
     */
    auto attachResult = node->attachHostNode(handle, host);
    EXPECT_TRUE(attachResult);
}

/**
 * @tc.name: AttachHostNode004
 * @tc.desc: OnAttachAtapper returns true, frameNode has no child node, and AttachHostNode returns false.
 * @tc.type: FUNC
 */
HWTEST_F(NodeAdapterImplTest, AttachHostNode004, TestSize.Level1)
{
    /**
     * @tc.steps1 Create a handle.
     */
    const ArkUINodeAdapterAPI* node = NodeAdapter::GetNodeAdapterAPI();
    CHECK_NULL_VOID(node);
    ArkUINodeAdapterHandle handle = node->create();
    auto frameNode1 = FrameNode::CreateFrameNode("parent", 1, AceType::MakeRefPtr<Pattern>());
    ArkUINodeHandle host = reinterpret_cast<ArkUINodeHandle>(Referenced::RawPtr(frameNode1));

    /**
     * @tc.steps2: OnAttachAtapper returns true, frameNode has no child node.
     * @tc.expected: return true
     */
    auto attachResult = node->attachHostNode(handle, host);
    EXPECT_TRUE(attachResult);
}

/**
 * @tc.name: AttachHostNode005
 * @tc.desc: OnAttachAtapper returns true, frameNode has child node, and AttachHostNode returns false.
 * @tc.type: FUNC
 */
HWTEST_F(NodeAdapterImplTest, AttachHostNode005, TestSize.Level1)
{
    /**
     * @tc.steps1 Create a handle.
     */
    const ArkUINodeAdapterAPI* node = NodeAdapter::GetNodeAdapterAPI();
    CHECK_NULL_VOID(node);
    ArkUINodeAdapterHandle handle = node->create();
    RefPtr<FrameNode> frameNode1 = FrameNode::CreateFrameNode("parent", 1, AceType::MakeRefPtr<Pattern>());
    RefPtr<FrameNode> frameNode2 = FrameNode::CreateFrameNode("child1", 2, AceType::MakeRefPtr<Pattern>());
    frameNode1->AddChild(frameNode2);
    ArkUINodeHandle host = reinterpret_cast<ArkUINodeHandle>(Referenced::RawPtr(frameNode1));

    /**
     * @tc.steps2: OnAttachAtapper returns true, frameNode has child node.
     * @tc.expected: return false
     */
    auto attachResult = node->attachHostNode(handle, host);
    EXPECT_FALSE(attachResult);
}
} // namespace OHOS::Ace::NG
