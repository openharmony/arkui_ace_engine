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

#include "gmock/gmock.h"
#include "gtest/gtest.h"

#define private public
#define protected public

#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

#include "adapter/ohos/osal/js_accessibility_manager.h"

using namespace OHOS::Accessibility;
using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace {
} // namespace OHOS::Ace

namespace OHOS::Ace::NG {
namespace {
} // namespace

class JsAccessibilityManagerTestTwo : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
};

void JsAccessibilityManagerTestTwo::SetUpTestCase()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
    MockContainer::Current()->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    MockContainer::Current()->pipelineContext_ = MockPipelineContext::GetCurrentContext();
    MockContainer::Current()->pipelineContext_->taskExecutor_ = MockContainer::Current()->taskExecutor_;

    std::unique_ptr<std::ostream> ostream = std::make_unique<std::ostringstream>();
    ASSERT_NE(ostream, nullptr);
    DumpLog::GetInstance().SetDumpFile(std::move(ostream));
}

void JsAccessibilityManagerTestTwo::TearDownTestCase()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

/**
 * @tc.name: JsAccessibilityManager001
 * @tc.desc: Test GetNextFocusNodeByManager with valid currentNode and rootNode but no inspectorKey
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerTestTwo, JsAccessibilityManager001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct JsAccessibilityManager
     */
    auto frameNode = FrameNode::CreateFrameNode("framenode", 1, AceType::MakeRefPtr<Pattern>(), true);
    ASSERT_NE(frameNode, nullptr);
    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    ASSERT_NE(jsAccessibilityManager, nullptr);

    /**
     * @tc.steps: step2. test GetNextFocusNodeByManager
     */
    RefPtr<NG::UINode> currentNode = AceType::MakeRefPtr<NG::UINode>();
    RefPtr<NG::FrameNode> rootNode = AceType::MakeRefPtr<NG::FrameNode>();
    RefPtr<NG::FrameNode> result = jsAccessibilityManager->GetNextFocusNodeByManager(currentNode, rootNode);
    EXPECT_EQ(result, nullptr);
}

/**
 * @tc.name: JsAccessibilityManager002
 * @tc.desc: Test GetNextFocusNodeByManager with null currentNode
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerTestTwo, JsAccessibilityManager002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct JsAccessibilityManager
     */
    auto frameNode = FrameNode::CreateFrameNode("framenode", 1, AceType::MakeRefPtr<Pattern>(), true);
    ASSERT_NE(frameNode, nullptr);
    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    ASSERT_NE(jsAccessibilityManager, nullptr);

    /**
     * @tc.steps: step2. test GetNextFocusNodeByManager
     */
    RefPtr<NG::UINode> currentNode = nullptr;
    RefPtr<NG::FrameNode> rootNode = AceType::MakeRefPtr<NG::FrameNode>();
    RefPtr<NG::FrameNode> result = jsAccessibilityManager->GetNextFocusNodeByManager(currentNode, rootNode);
    EXPECT_EQ(result, nullptr);
}

/**
 * @tc.name: JsAccessibilityManager003
 * @tc.desc: Test GetNextFocusNodeByManager with null rootNode
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerTestTwo, JsAccessibilityManager003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct JsAccessibilityManager
     */
    auto frameNode = FrameNode::CreateFrameNode("framenode", 1, AceType::MakeRefPtr<Pattern>(), true);
    ASSERT_NE(frameNode, nullptr);
    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    ASSERT_NE(jsAccessibilityManager, nullptr);

    /**
     * @tc.steps: step2. test GetNextFocusNodeByManager
     */
    RefPtr<NG::UINode> currentNode = AceType::MakeRefPtr<NG::UINode>();
    RefPtr<NG::FrameNode> rootNode = nullptr;
    RefPtr<NG::FrameNode> result = jsAccessibilityManager->GetNextFocusNodeByManager(currentNode, rootNode);
    EXPECT_EQ(result, nullptr);
}

/**
 * @tc.name: JsAccessibilityManager004
 * @tc.desc: Test GetNextFocusNodeByManager with both currentNode and rootNode as null
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerTestTwo, JsAccessibilityManager004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct JsAccessibilityManager
     */
    auto frameNode = FrameNode::CreateFrameNode("framenode", 1, AceType::MakeRefPtr<Pattern>(), true);
    ASSERT_NE(frameNode, nullptr);
    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    ASSERT_NE(jsAccessibilityManager, nullptr);

    /**
     * @tc.steps: step2. test GetNextFocusNodeByManager
     */
    RefPtr<NG::UINode> currentNode = nullptr;
    RefPtr<NG::FrameNode> rootNode = nullptr;
    RefPtr<NG::FrameNode> result = jsAccessibilityManager->GetNextFocusNodeByManager(currentNode, rootNode);
    EXPECT_EQ(result, nullptr);
}
} // namespace OHOS::Ace::NG