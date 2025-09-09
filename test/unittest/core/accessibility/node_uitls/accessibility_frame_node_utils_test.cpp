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

#include "gtest/gtest.h"

#define private public
#define protected public

#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

#include "base/log/dump_log.h"
#include "base/log/log_wrapper.h"
#include "core/accessibility/node_utils/accessibility_frame_node_utils.h"
#include "core/pipeline_ng/pipeline_context.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {

class AccessibilityFrameNodeUtilsTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
};

void AccessibilityFrameNodeUtilsTest::SetUpTestCase()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
    MockContainer::Current()->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    MockContainer::Current()->pipelineContext_ = MockPipelineContext::GetCurrentContext();
    MockContainer::Current()->pipelineContext_->taskExecutor_ = MockContainer::Current()->taskExecutor_;
    auto context = NG::PipelineContext::GetCurrentContext();
    std::unique_ptr<std::ostream> ostream = std::make_unique<std::ostringstream>();
    ASSERT_NE(ostream, nullptr);
    DumpLog::GetInstance().SetDumpFile(std::move(ostream));
}

void AccessibilityFrameNodeUtilsTest::TearDownTestCase()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

/**
 * @tc.name: GetFramenodeByAccessibilityId001
 * @tc.desc: vitural node
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityFrameNodeUtilsTest, GetFramenodeByAccessibilityId001, TestSize.Level1)
{
    auto context = NG::PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);
    auto root = context->GetRootElement();
    ASSERT_NE(root, nullptr);
    auto frameNode1 = FrameNode::CreateFrameNode("framenode",
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>(), true);
    ASSERT_NE(frameNode1, nullptr);
    root->AddChild(frameNode1);
    auto virtualNode = FrameNode::CreateFrameNode("framenode",
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>(), true);
    ASSERT_NE(virtualNode, nullptr);

    // step 1 can not find virtual node
    auto findNode = AccessibilityFrameNodeUtils::GetFramenodeByAccessibilityId(root, virtualNode->GetAccessibilityId());
    EXPECT_EQ(findNode, nullptr);

    // step 2  add virtual node and find it
    auto accessibilityProperty = frameNode1->GetAccessibilityProperty<AccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);

    virtualNode->SetAccessibilityNodeVirtual();
    virtualNode->SetAccessibilityVirtualNodeParent(frameNode1);
    virtualNode->SetFirstAccessibilityVirtualNode();
    frameNode1->HasAccessibilityVirtualNode(true);
    accessibilityProperty->SaveAccessibilityVirtualNode(virtualNode);
    findNode = AccessibilityFrameNodeUtils::GetFramenodeByAccessibilityId(root, virtualNode->GetAccessibilityId());
    ASSERT_NE(findNode, nullptr);
    EXPECT_EQ(findNode->GetAccessibilityId(), virtualNode->GetAccessibilityId());

    // step 3  add virtual node and find with wrong id
    findNode = AccessibilityFrameNodeUtils::GetFramenodeByAccessibilityId(root, virtualNode->GetAccessibilityId() + 1);
    EXPECT_EQ(findNode, nullptr);

    // step4 reset testcase
    root->RemoveChild(frameNode1);
}

/**
 * @tc.name: GetFramenodeByAccessibilityId002
 * @tc.desc: overlay node
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityFrameNodeUtilsTest, GetFramenodeByAccessibilityId002, TestSize.Level1)
{
    auto context = NG::PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);
    auto root = context->GetRootElement();
    ASSERT_NE(root, nullptr);
    auto frameNode1 = FrameNode::CreateFrameNode("framenode",
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>(), true);
    ASSERT_NE(frameNode1, nullptr);
    root->AddChild(frameNode1);
    auto overlayNode = FrameNode::CreateFrameNode("framenode",
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>(), true);
    ASSERT_NE(overlayNode, nullptr);

    // step 1 can not find overlay node
    auto findNode = AccessibilityFrameNodeUtils::GetFramenodeByAccessibilityId(root, overlayNode->GetAccessibilityId());
    EXPECT_EQ(findNode, nullptr);

    // step 2  add overlay node and find it
    frameNode1->SetOverlayNode(overlayNode);
    findNode = AccessibilityFrameNodeUtils::GetFramenodeByAccessibilityId(root, overlayNode->GetAccessibilityId());
    ASSERT_NE(findNode, nullptr);
    EXPECT_EQ(findNode->GetAccessibilityId(), overlayNode->GetAccessibilityId());

    // step 3  add overlay node and find with wrong id
    frameNode1->SetOverlayNode(overlayNode);
    findNode = AccessibilityFrameNodeUtils::GetFramenodeByAccessibilityId(root, overlayNode->GetAccessibilityId() + 1);
    EXPECT_EQ(findNode, nullptr);
    // step4 reset testcase
    root->RemoveChild(frameNode1);
}

/**
 * @tc.name: UpdateAccessibilityVisibleToRoot001
 * @tc.desc: IsFirstVirtualNode
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityFrameNodeUtilsTest, UpdateAccessibilityVisibleToRoot001, TestSize.Level1)
{
    auto context = NG::PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);

    auto frameNode1 = FrameNode::CreateFrameNode("framenode",
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>(), true);
    ASSERT_NE(frameNode1, nullptr);
    auto virtualNode = FrameNode::CreateFrameNode("virtualNode",
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>(), true);
    ASSERT_NE(virtualNode, nullptr);
    auto virtualNode1 = FrameNode::CreateFrameNode("virtualNode",
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>(), true);
    ASSERT_NE(virtualNode1, nullptr);
    virtualNode->AddChild(virtualNode1);

    auto accessibilityProperty = frameNode1->GetAccessibilityProperty<AccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);

    virtualNode->SetAccessibilityNodeVirtual();
    virtualNode->SetAccessibilityVirtualNodeParent(frameNode1);
    virtualNode->SetFirstAccessibilityVirtualNode();
    frameNode1->HasAccessibilityVirtualNode(true);
    accessibilityProperty->SaveAccessibilityVirtualNode(virtualNode);
    // step 1 IsFirstVirtualNode GetNodeAccessibilityVisible
    AccessibilityFrameNodeUtils::UpdateAccessibilityVisibleToRoot(virtualNode);
    EXPECT_EQ(virtualNode->GetAccessibilityVisible(), false);
    // step 2 IsFirstVirtualNode GetNodeAccessibilityVisible
    AccessibilityFrameNodeUtils::UpdateAccessibilityVisibleToRoot(virtualNode1);
    EXPECT_EQ(virtualNode1->GetAccessibilityVisible(), false);
}

/**
 * @tc.name: UpdateAccessibilityVisibleToRoot001
 * @tc.desc: PageNode
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityFrameNodeUtilsTest, UpdateAccessibilityVisibleToRoot002, TestSize.Level1)
{
    auto context = NG::PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);

    auto frameNode1 = FrameNode::CreateFrameNode("V2::PAGE_ETS_TAG",
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>(), true);
    ASSERT_NE(frameNode1, nullptr);
    auto frameNode2 = FrameNode::CreateFrameNode("frameNode2",
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>(), true);
    ASSERT_NE(frameNode2, nullptr);
    frameNode1->AddChild(frameNode2);
    auto frameNode3 = FrameNode::CreateFrameNode("frameNode3",
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>(), true);
    ASSERT_NE(frameNode3, nullptr);
    frameNode2->AddChild(frameNode3);

    // step 1 gettag == V2::PAGE_ETS_TAG
    AccessibilityFrameNodeUtils::UpdateAccessibilityVisibleToRoot(frameNode2);
    EXPECT_EQ(frameNode2->GetAccessibilityVisible(), false);
}
} // namespace OHOS::Ace::NG