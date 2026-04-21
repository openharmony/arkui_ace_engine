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

#include "test/mock/frameworks/base/thread/mock_task_executor.h"
#include "test/mock/frameworks/core/common/mock_container.h"
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"

#include "accessibility_element_info.h"
#include "accessibility_system_ability_client.h"
#include "adapter/ohos/osal/accessibility/accessibility_hidumper_osal.h"
#include "adapter/ohos/osal/accessibility/focus_move/accessibility_focus_accessibility_node_utils.h"
#include "adapter/ohos/osal/accessibility/focus_move/accessibility_focus_frame_node_utils.h"
#include "adapter/ohos/osal/accessibility/focus_move/accessibility_focus_third_node_utils.h"
#include "adapter/ohos/osal/accessibility/focus_move/accessibility_focus_move_osal_ng.h"
#include "adapter/ohos/osal/js_third_provider_interaction_operation.h"
#include "base/log/dump_log.h"
#include "frameworks/core/accessibility/accessibility_node.h"
#include "frameworks/core/accessibility/accessibility_utils.h"
#include "frameworks/core/accessibility/native_interface_accessibility_provider.h"
#include "frameworks/core/components_ng/base/frame_node.h"
#include "frameworks/core/components_ng/pattern/ui_extension/ui_extension_manager.h"

using namespace OHOS::Accessibility;
using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace {
} // namespace OHOS::Ace

namespace OHOS::Ace::Framework {

// ============================================================================
// Test class for AccessibilityElementInfoUtils (HiDumper OSAL)
// ============================================================================
class AccessibilityElementInfoUtilsTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
};

void AccessibilityElementInfoUtilsTest::SetUpTestCase()
{
    std::unique_ptr<std::ostream> ostream = std::make_unique<std::ostringstream>();
    ASSERT_NE(ostream, nullptr);
    DumpLog::GetInstance().SetDumpFile(std::move(ostream));
}

void AccessibilityElementInfoUtilsTest::TearDownTestCase()
{
}

/**
 * @tc.name: AccessibilityElementInfoUtilsTest001
 * @tc.desc: Test ToKeyInfo method with valid AccessibilityElementInfo
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityElementInfoUtilsTest, AccessibilityElementInfoUtilsTest001, TestSize.Level1)
{
    Accessibility::AccessibilityElementInfo elementInfo;
    elementInfo.SetAccessibilityId(100);
    elementInfo.SetComponentType("button");
    elementInfo.SetContent("TestButton");

    int32_t treeId = 1;

    // Should not crash when calling ToKeyInfo
    AccessibilityElementInfoUtils::ToKeyInfo(elementInfo, treeId);

    // Verify dump log contains expected content
    EXPECT_NE(DumpLog::GetInstance().GetDumpFile(), nullptr);
}

/**
 * @tc.name: AccessibilityElementInfoUtilsTest002
 * @tc.desc: Test ToCommonInfo method with valid AccessibilityElementInfo
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityElementInfoUtilsTest, AccessibilityElementInfoUtilsTest002, TestSize.Level1)
{
    Accessibility::AccessibilityElementInfo elementInfo;
    elementInfo.SetAccessibilityId(101);
    elementInfo.SetComponentType("text");
    elementInfo.SetContent("TestText");
    elementInfo.SetHint("TestHint");

    int32_t treeId = 2;

    // Should not crash when calling ToCommonInfo
    AccessibilityElementInfoUtils::ToCommonInfo(elementInfo, treeId);

    EXPECT_NE(DumpLog::GetInstance().GetDumpFile(), nullptr);
}

/**
 * @tc.name: AccessibilityElementInfoUtilsTest003
 * @tc.desc: Test ToDetailInfo method with valid AccessibilityElementInfo
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityElementInfoUtilsTest, AccessibilityElementInfoUtilsTest003, TestSize.Level1)
{
    Accessibility::AccessibilityElementInfo elementInfo;
    elementInfo.SetAccessibilityId(102);
    elementInfo.SetComponentType("image");
    elementInfo.SetContent("TestImage");
    elementInfo.SetDescriptionInfo("TestDescription");

    int32_t treeId = 3;

    // Should not crash when calling ToDetailInfo
    AccessibilityElementInfoUtils::ToDetailInfo(elementInfo, treeId);

    EXPECT_NE(DumpLog::GetInstance().GetDumpFile(), nullptr);
}

// ============================================================================
// Test class for AccessibilityManagerHidumper (HiDumper OSAL)
// ============================================================================
class AccessibilityManagerHidumperTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
};

void AccessibilityManagerHidumperTest::SetUpTestCase()
{
    std::unique_ptr<std::ostream> ostream = std::make_unique<std::ostringstream>();
    ASSERT_NE(ostream, nullptr);
    DumpLog::GetInstance().SetDumpFile(std::move(ostream));
}

void AccessibilityManagerHidumperTest::TearDownTestCase()
{
}

/**
 * @tc.name: AccessibilityManagerHidumperTest001
 * @tc.desc: Test ConvertAccessibilityAction method
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityManagerHidumperTest, AccessibilityManagerHidumperTest001, TestSize.Level1)
{
    // Test various action type conversions
    Accessibility::ActionType actionType = Accessibility::ActionType::ACCESSIBILITY_ACTION_CLICK;

    AceAction result = AccessibilityManagerHidumper::ConvertAccessibilityAction(actionType);

    // Verify the conversion doesn't crash and returns a valid action
    EXPECT_EQ(result.actionType, AceAction::ActionType::CLICK);
}

/**
 * @tc.name: AccessibilityManagerHidumperTest002
 * @tc.desc: Test ConvertActionTypeToString method with various action types
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityManagerHidumperTest, AccessibilityManagerHidumperTest002, TestSize.Level1)
{
    // Test various action type to string conversions
    Accessibility::ActionType clickAction = Accessibility::ActionType::ACCESSIBILITY_ACTION_CLICK;
    std::string clickStr = AccessibilityManagerHidumper::ConvertActionTypeToString(clickAction);
    EXPECT_FALSE(clickStr.empty());

    Accessibility::ActionType longClickAction = Accessibility::ActionType::ACCESSIBILITY_ACTION_LONG_CLICK;
    std::string longClickStr = AccessibilityManagerHidumper::ConvertActionTypeToString(longClickAction);
    EXPECT_FALSE(longClickStr.empty());

    Accessibility::ActionType forwardAction = Accessibility::ActionType::ACCESSIBILITY_ACTION_SCROLL_FORWARD;
    std::string forwardStr = AccessibilityManagerHidumper::ConvertActionTypeToString(forwardAction);
    EXPECT_FALSE(forwardStr.empty());

    Accessibility::ActionType backwardAction = Accessibility::ActionType::ACCESSIBILITY_ACTION_SCROLL_BACKWARD;
    std::string backwardStr = AccessibilityManagerHidumper::ConvertActionTypeToString(backwardAction);
    EXPECT_FALSE(backwardStr.empty());
}

/**
 * @tc.name: AccessibilityManagerHidumperTest003
 * @tc.desc: Test ConvertActionTypeToString with invalid action type
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityManagerHidumperTest, AccessibilityManagerHidumperTest003, TestSize.Level1)
{
    // Test with an invalid/unknown action type
    Accessibility::ActionType invalidAction = static_cast<Accessibility::ActionType>(9999);
    std::string result = AccessibilityManagerHidumper::ConvertActionTypeToString(invalidAction);

    // Should return empty string or default value for invalid action
    EXPECT_TRUE(result.empty() || result == "UNKNOWN");
}

// ============================================================================
// Test class for AccessibilityNodeRulesCheckNode
// ============================================================================
class AccessibilityNodeRulesCheckNodeTest : public testing::Test {
public:
    static void SetUpTestCase() {}
    static void TearDownTestCase() {}
};

/**
 * @tc.name: AccessibilityNodeRulesCheckNodeTest001
 * @tc.desc: Test GetPropText when node is nullptr
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityNodeRulesCheckNodeTest, AccessibilityNodeRulesCheckNodeTest001, TestSize.Level1)
{
    WeakPtr<AccessibilityNode> weakNode;
    AccessibilityNodeRulesCheckNode checkNode(weakNode, 123);

    Accessibility::PropValue value;
    bool result = checkNode.GetPropText(value);

    EXPECT_FALSE(result);
    EXPECT_EQ(value.valueType, Accessibility::ValueType::TYPE_NULL);
}

/**
 * @tc.name: AccessibilityNodeRulesCheckNodeTest002
 * @tc.desc: Test GetPropHintText when node is nullptr
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityNodeRulesCheckNodeTest, AccessibilityNodeRulesCheckNodeTest002, TestSize.Level1)
{
    WeakPtr<AccessibilityNode> weakNode;
    AccessibilityNodeRulesCheckNode checkNode(weakNode, 124);

    Accessibility::PropValue value;
    bool result = checkNode.GetPropHintText(value);

    EXPECT_FALSE(result);
}

/**
 * @tc.name: AccessibilityNodeRulesCheckNodeTest003
 * @tc.desc: Test GetPropDesc when node is nullptr
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityNodeRulesCheckNodeTest, AccessibilityNodeRulesCheckNodeTest003, TestSize.Level1)
{
    WeakPtr<AccessibilityNode> weakNode;
    AccessibilityNodeRulesCheckNode checkNode(weakNode, 125);

    Accessibility::PropValue value;
    bool result = checkNode.GetPropDesc(value);

    EXPECT_FALSE(result);
}

/**
 * @tc.name: AccessibilityNodeRulesCheckNodeTest004
 * @tc.desc: Test GetPropType when node is nullptr
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityNodeRulesCheckNodeTest, AccessibilityNodeRulesCheckNodeTest004, TestSize.Level1)
{
    WeakPtr<AccessibilityNode> weakNode;
    AccessibilityNodeRulesCheckNode checkNode(weakNode, 126);

    Accessibility::PropValue value;
    bool result = checkNode.GetPropType(value);

    EXPECT_FALSE(result);
}

/**
 * @tc.name: AccessibilityNodeRulesCheckNodeTest005
 * @tc.desc: Test GetPropIsEnable when node is nullptr
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityNodeRulesCheckNodeTest, AccessibilityNodeRulesCheckNodeTest005, TestSize.Level1)
{
    WeakPtr<AccessibilityNode> weakNode;
    AccessibilityNodeRulesCheckNode checkNode(weakNode, 127);

    Accessibility::PropValue value;
    bool result = checkNode.GetPropIsEnable(value);

    EXPECT_FALSE(result);
}

/**
 * @tc.name: AccessibilityNodeRulesCheckNodeTest006
 * @tc.desc: Test GetChildren when node is nullptr
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityNodeRulesCheckNodeTest, AccessibilityNodeRulesCheckNodeTest006, TestSize.Level1)
{
    WeakPtr<AccessibilityNode> weakNode;
    AccessibilityNodeRulesCheckNode checkNode(weakNode, 128);

    auto children = checkNode.GetChildren();
    EXPECT_TRUE(children.empty());
}

/**
 * @tc.name: AccessibilityNodeRulesCheckNodeTest007
 * @tc.desc: Test GetParent when node is nullptr
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityNodeRulesCheckNodeTest, AccessibilityNodeRulesCheckNodeTest007, TestSize.Level1)
{
    WeakPtr<AccessibilityNode> weakNode;
    AccessibilityNodeRulesCheckNode checkNode(weakNode, 129);

    auto parent = checkNode.GetParent();
    EXPECT_EQ(parent, nullptr);
}

/**
 * @tc.name: AccessibilityNodeRulesCheckNodeTest008
 * @tc.desc: Test GetAceChildren when node is nullptr
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityNodeRulesCheckNodeTest, AccessibilityNodeRulesCheckNodeTest008, TestSize.Level1)
{
    WeakPtr<AccessibilityNode> weakNode;
    AccessibilityNodeRulesCheckNode checkNode(weakNode, 130);

    auto aceChildren = checkNode.GetAceChildren();
    EXPECT_TRUE(aceChildren.empty());
}

/**
 * @tc.name: AccessibilityNodeRulesCheckNodeTest009
 * @tc.desc: Test GetAceParent when node is nullptr
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityNodeRulesCheckNodeTest, AccessibilityNodeRulesCheckNodeTest009, TestSize.Level1)
{
    WeakPtr<AccessibilityNode> weakNode;
    AccessibilityNodeRulesCheckNode checkNode(weakNode, 131);

    auto aceParent = checkNode.GetAceParent();
    EXPECT_EQ(aceParent, nullptr);
}

// ============================================================================
// Test class for ThirdRulesCheckNode
// ============================================================================
class ThirdRulesCheckNodeTest : public testing::Test {
public:
    static void SetUpTestCase() {}
    static void TearDownTestCase() {}
};

/**
 * @tc.name: ThirdRulesCheckNodeTest001
 * @tc.desc: Test GetPropText with valid nodeInfo
 * @tc.type: FUNC
 */
HWTEST_F(ThirdRulesCheckNodeTest, ThirdRulesCheckNodeTest001, TestSize.Level1)
{
    auto nodeInfo = std::make_shared<ArkUI_AccessibilityElementInfo>();
    nodeInfo->SetContent("TestContent");

    WeakPtr<AccessibilityProvider> weakProvider;
    ThirdRulesCheckNode checkNode(nodeInfo, 123, weakProvider);

    Accessibility::PropValue value;
    bool result = checkNode.GetPropText(value);

    EXPECT_TRUE(result);
    EXPECT_EQ(value.valueStr, "TestContent");
}

/**
 * @tc.name: ThirdRulesCheckNodeTest002
 * @tc.desc: Test GetPropHintText with valid nodeInfo
 * @tc.type: FUNC
 */
HWTEST_F(ThirdRulesCheckNodeTest, ThirdRulesCheckNodeTest002, TestSize.Level1)
{
    auto nodeInfo = std::make_shared<ArkUI_AccessibilityElementInfo>();
    nodeInfo->SetHintText("TestHint");

    WeakPtr<AccessibilityProvider> weakProvider;
    ThirdRulesCheckNode checkNode(nodeInfo, 124, weakProvider);

    Accessibility::PropValue value;
    bool result = checkNode.GetPropHintText(value);

    EXPECT_TRUE(result);
    EXPECT_EQ(value.valueStr, "TestHint");
}

/**
 * @tc.name: ThirdRulesCheckNodeTest003
 * @tc.desc: Test GetPropDesc with valid nodeInfo
 * @tc.type: FUNC
 */
HWTEST_F(ThirdRulesCheckNodeTest, ThirdRulesCheckNodeTest003, TestSize.Level1)
{
    auto nodeInfo = std::make_shared<ArkUI_AccessibilityElementInfo>();
    nodeInfo->SetAccessibilityDescription("TestDescription");

    WeakPtr<AccessibilityProvider> weakProvider;
    ThirdRulesCheckNode checkNode(nodeInfo, 125, weakProvider);

    Accessibility::PropValue value;
    bool result = checkNode.GetPropDesc(value);

    EXPECT_TRUE(result);
    EXPECT_EQ(value.valueStr, "TestDescription");
}

/**
 * @tc.name: ThirdRulesCheckNodeTest004
 * @tc.desc: Test GetPropType with valid nodeInfo
 * @tc.type: FUNC
 */
HWTEST_F(ThirdRulesCheckNodeTest, ThirdRulesCheckNodeTest004, TestSize.Level1)
{
    auto nodeInfo = std::make_shared<ArkUI_AccessibilityElementInfo>();
    nodeInfo->SetComponentType("button");

    WeakPtr<AccessibilityProvider> weakProvider;
    ThirdRulesCheckNode checkNode(nodeInfo, 126, weakProvider);

    Accessibility::PropValue value;
    bool result = checkNode.GetPropType(value);

    EXPECT_TRUE(result);
    EXPECT_EQ(value.valueStr, "button");
}

/**
 * @tc.name: ThirdRulesCheckNodeTest005
 * @tc.desc: Test GetPropIsEnable with valid nodeInfo
 * @tc.type: FUNC
 */
HWTEST_F(ThirdRulesCheckNodeTest, ThirdRulesCheckNodeTest005, TestSize.Level1)
{
    auto nodeInfo = std::make_shared<ArkUI_AccessibilityElementInfo>();
    nodeInfo->SetEnabled(true);

    WeakPtr<AccessibilityProvider> weakProvider;
    ThirdRulesCheckNode checkNode(nodeInfo, 127, weakProvider);

    Accessibility::PropValue value;
    bool result = checkNode.GetPropIsEnable(value);

    EXPECT_TRUE(result);
    EXPECT_EQ(value.valueBool, true);
}

/**
 * @tc.name: ThirdRulesCheckNodeTest006
 * @tc.desc: Test IsInChildTree returns true
 * @tc.type: FUNC
 */
HWTEST_F(ThirdRulesCheckNodeTest, ThirdRulesCheckNodeTest006, TestSize.Level1)
{
    auto nodeInfo = std::make_shared<ArkUI_AccessibilityElementInfo>();
    WeakPtr<AccessibilityProvider> weakProvider;
    ThirdRulesCheckNode checkNode(nodeInfo, 128, weakProvider);

    EXPECT_TRUE(checkNode.IsInChildTree());
}

// ============================================================================
// Test class for DetectParentRulesCheckNode
// ============================================================================
class DetectParentRulesCheckNodeTest : public testing::Test {
public:
    static void SetUpTestCase() {}
    static void TearDownTestCase() {}
};

/**
 * @tc.name: DetectParentRulesCheckNodeTest001
 * @tc.desc: Test GetPropText with elementInfo
 * @tc.type: FUNC
 */
HWTEST_F(DetectParentRulesCheckNodeTest, DetectParentRulesCheckNodeTest001, TestSize.Level1)
{
    Accessibility::AccessibilityElementInfo elementInfo;
    elementInfo.SetContent("TestContent");

    RefPtr<NG::FrameNode> customizedParentNode = nullptr;
    DetectParentRulesCheckNode checkNode(elementInfo, customizedParentNode);

    Accessibility::PropValue value;
    bool result = checkNode.GetPropText(value);

    EXPECT_TRUE(result);
    EXPECT_EQ(value.valueStr, "TestContent");
}

/**
 * @tc.name: DetectParentRulesCheckNodeTest002
 * @tc.desc: Test GetPropHintText with elementInfo
 * @tc.type: FUNC
 */
HWTEST_F(DetectParentRulesCheckNodeTest, DetectParentRulesCheckNodeTest002, TestSize.Level1)
{
    Accessibility::AccessibilityElementInfo elementInfo;
    elementInfo.SetHint("TestHint");

    RefPtr<NG::FrameNode> customizedParentNode = nullptr;
    DetectParentRulesCheckNode checkNode(elementInfo, customizedParentNode);

    Accessibility::PropValue value;
    bool result = checkNode.GetPropHintText(value);

    EXPECT_TRUE(result);
    EXPECT_EQ(value.valueStr, "TestHint");
}

/**
 * @tc.name: DetectParentRulesCheckNodeTest003
 * @tc.desc: Test GetChildren returns empty when no parent node
 * @tc.type: FUNC
 */
HWTEST_F(DetectParentRulesCheckNodeTest, DetectParentRulesCheckNodeTest003, TestSize.Level1)
{
    Accessibility::AccessibilityElementInfo elementInfo;
    RefPtr<NG::FrameNode> customizedParentNode = nullptr;
    DetectParentRulesCheckNode checkNode(elementInfo, customizedParentNode);

    auto children = checkNode.GetChildren();
    EXPECT_TRUE(children.empty());
}

/**
 * @tc.name: DetectParentRulesCheckNodeTest004
 * @tc.desc: Test GetParent returns nullptr when no parent node
 * @tc.type: FUNC
 */
HWTEST_F(DetectParentRulesCheckNodeTest, DetectParentRulesCheckNodeTest004, TestSize.Level1)
{
    Accessibility::AccessibilityElementInfo elementInfo;
    RefPtr<NG::FrameNode> customizedParentNode = nullptr;
    DetectParentRulesCheckNode checkNode(elementInfo, customizedParentNode);

    auto parent = checkNode.GetParent();
    EXPECT_EQ(parent, nullptr);
}

/**
 * @tc.name: DetectParentRulesCheckNodeTest005
 * @tc.desc: Test GetAceChildren returns empty when no parent node
 * @tc.type: FUNC
 */
HWTEST_F(DetectParentRulesCheckNodeTest, DetectParentRulesCheckNodeTest005, TestSize.Level1)
{
    Accessibility::AccessibilityElementInfo elementInfo;
    RefPtr<NG::FrameNode> customizedParentNode = nullptr;
    DetectParentRulesCheckNode checkNode(elementInfo, customizedParentNode);

    auto aceChildren = checkNode.GetAceChildren();
    EXPECT_TRUE(aceChildren.empty());
}

/**
 * @tc.name: DetectParentRulesCheckNodeTest006
 * @tc.desc: Test GetAceParent returns nullptr when no parent node
 * @tc.type: FUNC
 */
HWTEST_F(DetectParentRulesCheckNodeTest, DetectParentRulesCheckNodeTest006, TestSize.Level1)
{
    Accessibility::AccessibilityElementInfo elementInfo;
    RefPtr<NG::FrameNode> customizedParentNode = nullptr;
    DetectParentRulesCheckNode checkNode(elementInfo, customizedParentNode);

    auto aceParent = checkNode.GetAceParent();
    EXPECT_EQ(aceParent, nullptr);
}

// ============================================================================
// Test class for DetectParentMockChildNode
// ============================================================================
class DetectParentMockChildNodeTest : public testing::Test {
public:
    static void SetUpTestCase() {}
    static void TearDownTestCase() {}
};

/**
 * @tc.name: DetectParentMockChildNodeTest001
 * @tc.desc: Test GetPropText returns empty for mock child
 * @tc.type: FUNC
 */
HWTEST_F(DetectParentMockChildNodeTest, DetectParentMockChildNodeTest001, TestSize.Level1)
{
    DetectParentMockChildNode mockNode(123);

    Accessibility::PropValue value;
    bool result = mockNode.GetPropText(value);

    EXPECT_FALSE(result);
}

/**
 * @tc.name: DetectParentMockChildNodeTest002
 * @tc.desc: Test GetChildren returns empty for mock child
 * @tc.type: FUNC
 */
HWTEST_F(DetectParentMockChildNodeTest, DetectParentMockChildNodeTest002, TestSize.Level1)
{
    DetectParentMockChildNode mockNode(124);

    auto children = mockNode.GetChildren();
    EXPECT_TRUE(children.empty());
}

/**
 * @tc.name: DetectParentMockChildNodeTest003
 * @tc.desc: Test GetParent returns nullptr for mock child
 * @tc.type: FUNC
 */
HWTEST_F(DetectParentMockChildNodeTest, DetectParentMockChildNodeTest003, TestSize.Level1)
{
    DetectParentMockChildNode mockNode(125);

    auto parent = mockNode.GetParent();
    EXPECT_EQ(parent, nullptr);
}

// ============================================================================
// Test class for FrameNodeRulesCheckNode additional methods
// ============================================================================
class FrameNodeRulesCheckNodeAdditionalTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
};

void FrameNodeRulesCheckNodeAdditionalTest::SetUpTestCase()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
    MockContainer::Current()->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    MockContainer::Current()->pipelineContext_ = MockPipelineContext::GetCurrentContext();
    MockContainer::Current()->pipelineContext_->taskExecutor_ = MockContainer::Current()->taskExecutor_;
}

void FrameNodeRulesCheckNodeAdditionalTest::TearDownTestCase()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

/**
 * @tc.name: FrameNodeRulesCheckNodeAdditionalTest001
 * @tc.desc: Test GetPropChildrenCount when node is nullptr
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeRulesCheckNodeAdditionalTest, FrameNodeRulesCheckNodeAdditionalTest001, TestSize.Level1)
{
    NG::FrameNodeHandleParam frameNodeHandleParam;
    FrameNodeRulesCheckNode checkNode(nullptr, 123, frameNodeHandleParam);

    Accessibility::PropValue value;
    bool result = checkNode.GetPropChildrenCount(value);

    EXPECT_FALSE(result);
    EXPECT_EQ(value.valueNum, 0);
}

/**
 * @tc.name: FrameNodeRulesCheckNodeAdditionalTest002
 * @tc.desc: Test GetPropActionNames when node is nullptr
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeRulesCheckNodeAdditionalTest, FrameNodeRulesCheckNodeAdditionalTest002, TestSize.Level1)
{
    NG::FrameNodeHandleParam frameNodeHandleParam;
    FrameNodeRulesCheckNode checkNode(nullptr, 124, frameNodeHandleParam);

    Accessibility::PropValue value;
    bool result = checkNode.GetPropActionNames(value);

    EXPECT_FALSE(result);
}

/**
 * @tc.name: FrameNodeRulesCheckNodeAdditionalTest003
 * @tc.desc: Test GetChildren when node is nullptr
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeRulesCheckNodeAdditionalTest, FrameNodeRulesCheckNodeAdditionalTest003, TestSize.Level1)
{
    NG::FrameNodeHandleParam frameNodeHandleParam;
    FrameNodeRulesCheckNode checkNode(nullptr, 125, frameNodeHandleParam);

    auto children = checkNode.GetChildren();
    EXPECT_TRUE(children.empty());
}

/**
 * @tc.name: FrameNodeRulesCheckNodeAdditionalTest004
 * @tc.desc: Test GetParent when node is nullptr
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeRulesCheckNodeAdditionalTest, FrameNodeRulesCheckNodeAdditionalTest004, TestSize.Level1)
{
    NG::FrameNodeHandleParam frameNodeHandleParam;
    FrameNodeRulesCheckNode checkNode(nullptr, 126, frameNodeHandleParam);

    auto parent = checkNode.GetParent();
    EXPECT_EQ(parent, nullptr);
}

/**
 * @tc.name: FrameNodeRulesCheckNodeAdditionalTest005
 * @tc.desc: Test IsModal when node is nullptr
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeRulesCheckNodeAdditionalTest, FrameNodeRulesCheckNodeAdditionalTest005, TestSize.Level1)
{
    NG::FrameNodeHandleParam frameNodeHandleParam;
    FrameNodeRulesCheckNode checkNode(nullptr, 127, frameNodeHandleParam);

    EXPECT_FALSE(checkNode.IsModal());
}

/**
 * @tc.name: FrameNodeRulesCheckNodeAdditionalTest006
 * @tc.desc: Test IsInChildTree when node is nullptr
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeRulesCheckNodeAdditionalTest, FrameNodeRulesCheckNodeAdditionalTest006, TestSize.Level1)
{
    NG::FrameNodeHandleParam frameNodeHandleParam;
    FrameNodeRulesCheckNode checkNode(nullptr, 128, frameNodeHandleParam);

    EXPECT_FALSE(checkNode.IsInChildTree());
}

/**
 * @tc.name: FrameNodeRulesCheckNodeAdditionalTest007
 * @tc.desc: Test IsChildTreeContainer when node is nullptr
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeRulesCheckNodeAdditionalTest, FrameNodeRulesCheckNodeAdditionalTest007, TestSize.Level1)
{
    NG::FrameNodeHandleParam frameNodeHandleParam;
    FrameNodeRulesCheckNode checkNode(nullptr, 129, frameNodeHandleParam);

    EXPECT_FALSE(checkNode.IsChildTreeContainer());
}

/**
 * @tc.name: FrameNodeRulesCheckNodeAdditionalTest008
 * @tc.desc: Test IsEmbededTarget when node is nullptr
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeRulesCheckNodeAdditionalTest, FrameNodeRulesCheckNodeAdditionalTest008, TestSize.Level1)
{
    NG::FrameNodeHandleParam frameNodeHandleParam;
    FrameNodeRulesCheckNode checkNode(nullptr, 130, frameNodeHandleParam);

    EXPECT_FALSE(checkNode.IsEmbededTarget());
}

/**
 * @tc.name: FrameNodeRulesCheckNodeAdditionalTest009
 * @tc.desc: Test IsHeaderFooterInScroll when node is nullptr
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeRulesCheckNodeAdditionalTest, FrameNodeRulesCheckNodeAdditionalTest009, TestSize.Level1)
{
    NG::FrameNodeHandleParam frameNodeHandleParam;
    FrameNodeRulesCheckNode checkNode(nullptr, 131, frameNodeHandleParam);

    EXPECT_FALSE(checkNode.IsHeaderFooterInScroll());
}

/**
 * @tc.name: FrameNodeRulesCheckNodeAdditionalTest010
 * @tc.desc: Test IsBackward and IsForward default values
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeRulesCheckNodeAdditionalTest, FrameNodeRulesCheckNodeAdditionalTest010, TestSize.Level1)
{
    NG::FrameNodeHandleParam frameNodeHandleParam;
    FrameNodeRulesCheckNode checkNode(nullptr, 132, frameNodeHandleParam);

    EXPECT_FALSE(checkNode.IsBackward());
    EXPECT_FALSE(checkNode.IsForward());
}

} // namespace OHOS::Ace::Framework
