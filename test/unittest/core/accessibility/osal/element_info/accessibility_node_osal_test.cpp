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

#include "adapter/ohos/osal/js_accessibility_manager.h"
#include "base/log/dump_log.h"
#include "frameworks/core/accessibility/accessibility_manager.h"
#include "frameworks/core/accessibility/accessibility_node.h"
#include "frameworks/core/accessibility/accessibility_utils.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace {
} // namespace OHOS::Ace

namespace OHOS::Ace::Framework {
namespace {
    const int32_t IGNORE_POSITION_TRANSITION_SWITCH = -990;
    const char SIDEBARCONTAINER_TAG[] = "SideBarContainer";
    const char LIST_TAG[] = "List";
} // namespace

class JsAccessibilityNodeOsalTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
};

void JsAccessibilityNodeOsalTest::SetUpTestCase()
{
    NG::MockPipelineContext::SetUp();
    MockContainer::SetUp();
    MockContainer::Current()->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    MockContainer::Current()->pipelineContext_ = NG::MockPipelineContext::GetCurrentContext();
    MockContainer::Current()->pipelineContext_->taskExecutor_ = MockContainer::Current()->taskExecutor_;
    auto context = NG::PipelineContext::GetCurrentContext();
    context->instanceId_ = IGNORE_POSITION_TRANSITION_SWITCH;
    std::unique_ptr<std::ostream> ostream = std::make_unique<std::ostringstream>();
    ASSERT_NE(ostream, nullptr);
    DumpLog::GetInstance().SetDumpFile(std::move(ostream));
}

void JsAccessibilityNodeOsalTest::TearDownTestCase()
{
    NG::MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

/**
 * @tc.name: JsThirdAccessibilityHoverNgTest001
 * @tc.desc: content
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityNodeOsalTest, JsAccessibilityNodeOsalTest001, TestSize.Level1)
{
    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    ASSERT_NE(jsAccessibilityManager, nullptr);
    auto accessibilityNode = AceType::MakeRefPtr<AccessibilityNode>(1, "test");
    ASSERT_NE(accessibilityNode, nullptr);
    Accessibility::AccessibilityElementInfo nodeInfo;
    int32_t windowId = 1;

    // windowId
    jsAccessibilityManager->UpdateAccessibilityNodeInfo(accessibilityNode, nodeInfo, jsAccessibilityManager, windowId);
    EXPECT_EQ(nodeInfo.GetWindowId(), windowId);

    // sidebarcontainer
    accessibilityNode->SetTag(SIDEBARCONTAINER_TAG);
    jsAccessibilityManager->UpdateAccessibilityNodeInfo(accessibilityNode, nodeInfo, jsAccessibilityManager, windowId);
    EXPECT_EQ(nodeInfo.GetComponentType(), SIDEBARCONTAINER_TAG);
    // list
    accessibilityNode->SetTag(LIST_TAG);
    jsAccessibilityManager->UpdateAccessibilityNodeInfo(accessibilityNode, nodeInfo, jsAccessibilityManager, windowId);
    EXPECT_EQ(nodeInfo.GetComponentType(), LIST_TAG);

    // content
    std::string testStr = "HelloWorld";
    accessibilityNode->SetText(testStr);
    jsAccessibilityManager->UpdateAccessibilityNodeInfo(accessibilityNode, nodeInfo, jsAccessibilityManager, windowId);
    EXPECT_EQ(nodeInfo.GetContent(), testStr);
    // content with password
    std::string strStar(testStr.size(), '*');
    accessibilityNode->SetIsPassword(true);
    jsAccessibilityManager->UpdateAccessibilityNodeInfo(accessibilityNode, nodeInfo, jsAccessibilityManager, windowId);
    EXPECT_EQ(nodeInfo.GetContent(), strStar);
}

/**
 * @tc.name: JsThirdAccessibilityHoverNgTest002
 * @tc.desc: ImportantForAccessibility
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityNodeOsalTest, JsAccessibilityNodeOsalTest002, TestSize.Level1)
{
    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    ASSERT_NE(jsAccessibilityManager, nullptr);
    auto accessibilityNode = AceType::MakeRefPtr<AccessibilityNode>(1, "test");
    ASSERT_NE(accessibilityNode, nullptr);
    Accessibility::AccessibilityElementInfo nodeInfo;
    int32_t windowId = 1;

    // importantForAccessibility equals NG::AccessibilityProperty::Level::YES_STR
    accessibilityNode->SetImportantForAccessibility(NG::AccessibilityProperty::Level::YES_STR);
    jsAccessibilityManager->UpdateAccessibilityNodeInfo(accessibilityNode, nodeInfo, jsAccessibilityManager, windowId);
    EXPECT_EQ(nodeInfo.IsCheckable(), true);
    // importantForAccessibility equals NG::AccessibilityProperty::Level::NO_STR
    nodeInfo.SetVisible(true);
    accessibilityNode->SetImportantForAccessibility(NG::AccessibilityProperty::Level::NO_STR);
    jsAccessibilityManager->UpdateAccessibilityNodeInfo(accessibilityNode, nodeInfo, jsAccessibilityManager, windowId);
    EXPECT_EQ(nodeInfo.IsVisible(), false);

    // importantForAccessibility equals NG::AccessibilityProperty::Level::NO_STR
    nodeInfo.SetVisible(true);
    accessibilityNode->SetImportantForAccessibility(NG::AccessibilityProperty::Level::NO_HIDE_DESCENDANTS);
    jsAccessibilityManager->UpdateAccessibilityNodeInfo(accessibilityNode, nodeInfo, jsAccessibilityManager, windowId);
    EXPECT_EQ(nodeInfo.IsVisible(), false);
}

/**
 * @tc.name: JsThirdAccessibilityHoverNgTest003
 * @tc.desc: CheckInvalidNodeParentID
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityNodeOsalTest, JsAccessibilityNodeOsalTest003, TestSize.Level1)
{
    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    ASSERT_NE(jsAccessibilityManager, nullptr);
    auto accessibilityNode = AceType::MakeRefPtr<AccessibilityNode>(1, "test");
    ASSERT_NE(accessibilityNode, nullptr);
    Accessibility::AccessibilityElementInfo nodeInfo;
    int32_t windowId = 1;

    // parent id == -1, children empty
    jsAccessibilityManager->UpdateAccessibilityNodeInfo(accessibilityNode, nodeInfo, jsAccessibilityManager, windowId);
    EXPECT_EQ(nodeInfo.GetParentNodeId(), JsAccessibilityManager::INVALID_PARENT_ID);
    // current id == 0,
    Accessibility::AccessibilityElementInfo rootNodeInfo;
    auto accessibilityRootNode = AceType::MakeRefPtr<AccessibilityNode>(0, "root");
    ASSERT_NE(accessibilityRootNode, nullptr);
    jsAccessibilityManager->UpdateAccessibilityNodeInfo(
        accessibilityRootNode, rootNodeInfo, jsAccessibilityManager, windowId);
    EXPECT_EQ(rootNodeInfo.GetParentNodeId(), JsAccessibilityManager::INVALID_PARENT_ID);

    // parentId != -1
    accessibilityNode->SetParentNode(accessibilityRootNode);
    jsAccessibilityManager->UpdateAccessibilityNodeInfo(accessibilityNode, nodeInfo, jsAccessibilityManager, windowId);
    EXPECT_EQ(nodeInfo.GetParentNodeId(), 0);

    // parent id == -1, children !empty
    accessibilityRootNode->AddNode(accessibilityNode, 0);
    jsAccessibilityManager->UpdateAccessibilityNodeInfo(
        accessibilityRootNode, rootNodeInfo, jsAccessibilityManager, windowId);
    EXPECT_EQ(rootNodeInfo.GetParentNodeId(), JsAccessibilityManager::INVALID_PARENT_ID);
}

/**
 * @tc.name: JsThirdAccessibilityHoverNgTest004
 * @tc.desc: ConvertToCardAccessibilityId
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityNodeOsalTest, JsAccessibilityNodeOsalTest004, TestSize.Level1)
{
    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    ASSERT_NE(jsAccessibilityManager, nullptr);
    auto accessibilityNode = AceType::MakeRefPtr<AccessibilityNode>(1, "test");
    ASSERT_NE(accessibilityNode, nullptr);
    Accessibility::AccessibilityElementInfo nodeInfo;
    int32_t windowId = 1;

    jsAccessibilityManager->SetCardViewPosition(0, 0.0f, 0.0f);
    jsAccessibilityManager->SetRootNodeId(0);
    // isOhosHostCard parentId == -1
    jsAccessibilityManager->UpdateAccessibilityNodeInfo(accessibilityNode, nodeInfo, jsAccessibilityManager, windowId);
    EXPECT_EQ(nodeInfo.GetAccessibilityId(), 1);
    EXPECT_EQ(nodeInfo.GetParentNodeId(), JsAccessibilityManager::INVALID_PARENT_ID);

    // isOhosHostCard parentId != -1
    auto accessibilityRootNode = AceType::MakeRefPtr<AccessibilityNode>(0, "root");
    ASSERT_NE(accessibilityRootNode, nullptr);
    accessibilityNode->SetParentNode(accessibilityRootNode);
    jsAccessibilityManager->UpdateAccessibilityNodeInfo(accessibilityNode, nodeInfo, jsAccessibilityManager, windowId);
    EXPECT_EQ(nodeInfo.GetParentNodeId(), 0);
}
} // namespace OHOS::Ace::Framework