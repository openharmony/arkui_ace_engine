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

#include <cstddef>

#include "gtest/gtest.h"

#include "core/interfaces/native/node/node_content_modifier.h"
#define private public
#include "interfaces/native/native_node.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

#include "base/memory/ace_type.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/syntax/content_slot_model_ng.h"
#include "core/components_ng/syntax/content_slot_node.h"
#include "core/components_ng/syntax/node_content.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t NODE_CONTENT_INIT_STATUS = 1000;
constexpr int32_t NODE_CONTENT_ATTACH_TO_TREE = 1001;
constexpr int32_t NODE_CONTENT_DETACH_FROM_TREE = 1002;
constexpr uint32_t NUM_1 = 1;
constexpr uint32_t NUM_2 = 2;
} // namespace

class ContentSlotSyntaxTestNg : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp() override;
    void TearDown() override;
};

void ContentSlotSyntaxTestNg::SetUpTestSuite()
{
    GTEST_LOG_(INFO) << "ContentSlotSyntaxTestNg SetUpTestCase";
}

void ContentSlotSyntaxTestNg::TearDownTestSuite()
{
    GTEST_LOG_(INFO) << "ContentSlotSyntaxTestNg TearDownTestCase";
}

void ContentSlotSyntaxTestNg::SetUp()
{
    MockPipelineContext::SetUp();
}

void ContentSlotSyntaxTestNg::TearDown()
{
    MockPipelineContext::TearDown();
}

/**
 * @tc.name: ContentSlotSyntaxTest001
 * @tc.desc: ContentSlot For CAPI 1
 * @tc.type: FUNC
 */
HWTEST_F(ContentSlotSyntaxTestNg, ContentSlotSyntaxTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create contentSlotNode
     * @tc.expected: contentSlotNode create successfully
     */
    auto nodeContentPtr = AceType::MakeRefPtr<NodeContent>();
    NodeContent* nodeContent = AceType::RawPtr(nodeContentPtr);
    ContentSlotModel::Create(nodeContent);
    auto contentSlotNode = AceType::DynamicCast<ContentSlotNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_TRUE(contentSlotNode != nullptr && contentSlotNode->GetTag() == V2::JS_NODE_SLOT_ETS_TAG);

    /**
     * @tc.steps: step2. add/insert/remove child
     * @tc.expected: add/insert/remove child successfully
     */
    const auto* contentModifier = NodeModifier::GetNodeContentModifier();
    auto childFrameNode1 = FrameNode::CreateFrameNode("frameNode1", -1, AceType::MakeRefPtr<Pattern>());
    contentModifier->addChild(reinterpret_cast<ArkUINodeContentHandle>(nodeContent),
        reinterpret_cast<ArkUINodeHandle>(childFrameNode1.GetRawPtr()));
    auto children = contentSlotNode->GetChildren();
    EXPECT_TRUE(children.size() == NUM_1 && children.front()->GetTag() == "frameNode1");

    auto childFrameNode2 = FrameNode::CreateFrameNode("frameNode2", -1, AceType::MakeRefPtr<Pattern>());
    contentModifier->insertChild(reinterpret_cast<ArkUINodeContentHandle>(nodeContent),
        reinterpret_cast<ArkUINodeHandle>(childFrameNode2.GetRawPtr()), 0);
    children = contentSlotNode->GetChildren();
    EXPECT_TRUE(children.size() == NUM_2 && children.front()->GetTag() == "frameNode2");

    contentModifier->removeChild(reinterpret_cast<ArkUINodeContentHandle>(nodeContent),
        reinterpret_cast<ArkUINodeHandle>(childFrameNode1.GetRawPtr()));
    contentModifier->removeChild(reinterpret_cast<ArkUINodeContentHandle>(nodeContent),
        reinterpret_cast<ArkUINodeHandle>(childFrameNode2.GetRawPtr()));
    children = contentSlotNode->GetChildren();
    EXPECT_TRUE(children.size() == 0);
}

/**
 * @tc.name: ContentSlotSyntaxTest002
 * @tc.desc: ContentSlot For CAPI 2
 * @tc.type: FUNC
 */
HWTEST_F(ContentSlotSyntaxTestNg, ContentSlotSyntaxTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create contentSlotNode
     * @tc.expected: contentSlotNode create successfully
     */
    auto nodeContentPtr = AceType::MakeRefPtr<NodeContent>();
    NodeContent* nodeContent = AceType::RawPtr(nodeContentPtr);
    ContentSlotModel::Create(nodeContent);
    auto contentSlotNode = AceType::DynamicCast<ContentSlotNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_TRUE(contentSlotNode != nullptr && contentSlotNode->GetTag() == V2::JS_NODE_SLOT_ETS_TAG);

    /**
     * @tc.steps: step2. releated to event
     * @tc.expected: registerEvent, set/getUserData, getNodeContent successfully
     */
    const auto* contentModifier = NodeModifier::GetNodeContentModifier();
    auto* userData = new int32_t(NODE_CONTENT_INIT_STATUS);
    contentModifier->setUserData(reinterpret_cast<ArkUINodeContentHandle>(nodeContent), userData);
    auto callback = [](ArkUINodeContentEvent* event) {
        auto* nodeContent = event->nodeContent;
        const auto* contentModifier = NodeModifier::GetNodeContentModifier();
        if (event->type == 0) {
            int32_t* userData = reinterpret_cast<int32_t*>(
                contentModifier->getUserData(reinterpret_cast<ArkUINodeContentHandle>(nodeContent)));
            EXPECT_EQ(*userData, NODE_CONTENT_INIT_STATUS);
            delete userData;
            userData = new int32_t(NODE_CONTENT_ATTACH_TO_TREE);
            contentModifier->setUserData(reinterpret_cast<ArkUINodeContentHandle>(nodeContent), userData);
        } else if (event->type == 1) {
            int32_t* userData = reinterpret_cast<int32_t*>(
                contentModifier->getUserData(reinterpret_cast<ArkUINodeContentHandle>(nodeContent)));
            EXPECT_EQ(*userData, NODE_CONTENT_ATTACH_TO_TREE);
            delete userData;
            userData = new int32_t(NODE_CONTENT_DETACH_FROM_TREE);
            contentModifier->setUserData(reinterpret_cast<ArkUINodeContentHandle>(nodeContent), userData);
        }
    };
    contentModifier->registerEvent(reinterpret_cast<ArkUINodeContentHandle>(nodeContent), nullptr, std::move(callback));
    nodeContent->OnAttachToMainTree();
    EXPECT_TRUE(nodeContent->onMainTree_);
    nodeContent->OnDetachFromMainTree();
    EXPECT_FALSE(nodeContent->onMainTree_);
    userData =
        reinterpret_cast<int32_t*>(contentModifier->getUserData(reinterpret_cast<ArkUINodeContentHandle>(nodeContent)));
    EXPECT_EQ(*userData, NODE_CONTENT_DETACH_FROM_TREE);
    delete userData;
}
} // namespace OHOS::Ace::NG