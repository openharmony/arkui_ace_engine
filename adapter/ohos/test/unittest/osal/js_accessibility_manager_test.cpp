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

#include <gtest/gtest.h>
#include <string>
#define private public
#define protected public
#include "adapter/ohos/osal/js_accessibility_manager.h"
#undef private
#undef protected
#include "adapter/ohos/test/unittest/mock/mock_accessibility_element_operator_callback.h"

using namespace testing::ext;
namespace OHOS::Ace::Framework {
class JsAccessibilityManagerTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
    RefPtr<Framework::JsAccessibilityManager> manager_;
};

void JsAccessibilityManagerTest::SetUpTestCase() {}

void JsAccessibilityManagerTest::TearDownTestCase() {}

void JsAccessibilityManagerTest::SetUp()
{
    manager_ = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
}

void JsAccessibilityManagerTest::TearDown()
{
    manager_ = nullptr;
}

/**
 * @tc.name: JsAccessibilityManagerTest001
 * @tc.desc: ConvertStrToEventType
 * @tc.desc: SetCardViewParams
 * @tc.type: FUNC
 * @tc.require:
 */
HWTEST_F(JsAccessibilityManagerTest, JsAccessibilityManagerTest001, TestSize.Level1)
{
    EXPECT_NE(manager_, nullptr);
    manager_->SetCardViewParams("callbackKey", true);
    EXPECT_NE(manager_, nullptr);
}

/**
 * @tc.name: JsAccessibilityManagerTest002
 * @tc.desc: ConvertStrToEventType
 * @tc.desc: SetCardViewParams
 * @tc.type: FUNC
 * @tc.require:
 */
HWTEST_F(JsAccessibilityManagerTest, JsAccessibilityManagerTest002, TestSize.Level1)
{
    EXPECT_NE(manager_, nullptr);
    manager_->SetCardViewParams("", true);
    EXPECT_NE(manager_, nullptr);
}

/**
 * @tc.name: JsAccessibilityManagerTest003
 * @tc.desc: SendActionEvent
 * @tc.type: FUNC
 * @tc.require:
 */
HWTEST_F(JsAccessibilityManagerTest, JsAccessibilityManagerTest003, TestSize.Level1)
{
    EXPECT_NE(manager_, nullptr);
    manager_->SendActionEvent(Accessibility::ActionType::ACCESSIBILITY_ACTION_INVALID, 0);
    EXPECT_NE(manager_, nullptr);
}

/**
 * @tc.name: JsAccessibilityManagerTest004
 * @tc.desc: SendActionEvent
 * @tc.type: FUNC
 * @tc.require:
 */
HWTEST_F(JsAccessibilityManagerTest, JsAccessibilityManagerTest004, TestSize.Level1)
{
    EXPECT_NE(manager_, nullptr);
    manager_->SendActionEvent(Accessibility::ActionType::ACCESSIBILITY_ACTION_CLICK, 0);
    EXPECT_NE(manager_, nullptr);
}

/**
 * @tc.name: JsAccessibilityManagerTest005
 * @tc.desc: FindNodeInRelativeDirection
 * @tc.type: FUNC
 * @tc.require:
 */
HWTEST_F(JsAccessibilityManagerTest, JsAccessibilityManagerTest005, TestSize.Level1)
{
    EXPECT_NE(manager_, nullptr);
    int32_t nodeId = 0;
    std::string tag = "tag";
    RefPtr<AccessibilityNode> result = nullptr;
    std::list<RefPtr<AccessibilityNode>> nodeList;
    RefPtr<AccessibilityNode> node = AceType::MakeRefPtr<AccessibilityNode>(nodeId, tag);
    nodeList.emplace_back(node);
    result = manager_->FindNodeInRelativeDirection(nodeList, node, Accessibility::FocusMoveDirection::FORWARD);
    EXPECT_NE(manager_, nullptr);
    EXPECT_NE(result, nullptr);
}

/**
 * @tc.name: JsAccessibilityManagerTest006
 * @tc.desc: FindNodeInRelativeDirection
 * @tc.type: FUNC
 * @tc.require:
 */
HWTEST_F(JsAccessibilityManagerTest, JsAccessibilityManagerTest006, TestSize.Level1)
{
    EXPECT_NE(manager_, nullptr);
    int32_t nodeId = 0;
    std::string tag = "tag";
    RefPtr<AccessibilityNode> result = nullptr;
    std::list<RefPtr<AccessibilityNode>> nodeList;
    RefPtr<AccessibilityNode> node = AceType::MakeRefPtr<AccessibilityNode>(nodeId, tag);
    nodeList.emplace_back(node);
    result = manager_->FindNodeInRelativeDirection(nodeList, node, Accessibility::FocusMoveDirection::BACKWARD);
    EXPECT_NE(manager_, nullptr);
    EXPECT_NE(result, nullptr);
}

/**
 * @tc.name: JsAccessibilityManagerTest007
 * @tc.desc: FindNodeInRelativeDirection
 * @tc.type: FUNC
 * @tc.require:
 */
HWTEST_F(JsAccessibilityManagerTest, JsAccessibilityManagerTest007, TestSize.Level1)
{
    EXPECT_NE(manager_, nullptr);
    int32_t nodeId = 0;
    std::string tag = "tag";
    RefPtr<AccessibilityNode> result = nullptr;
    std::list<RefPtr<AccessibilityNode>> nodeList;
    RefPtr<AccessibilityNode> node = AceType::MakeRefPtr<AccessibilityNode>(nodeId, tag);
    nodeList.emplace_back(node);
    result = manager_->FindNodeInRelativeDirection(nodeList, node, Accessibility::FocusMoveDirection::UP);
    EXPECT_NE(manager_, nullptr);
    EXPECT_EQ(result, nullptr);
}

/**
 * @tc.name: JsAccessibilityManagerTest008
 * @tc.desc: ClearAccessibilityFocus
 * @tc.type: FUNC
 * @tc.require:
 */
HWTEST_F(JsAccessibilityManagerTest, JsAccessibilityManagerTest008, TestSize.Level1)
{
    EXPECT_NE(manager_, nullptr);
    int32_t nodeId = 0;
    std::string tag = "tag";
    bool result = true;
    RefPtr<AccessibilityNode> node = AceType::MakeRefPtr<AccessibilityNode>(nodeId, tag);
    result = manager_->ClearAccessibilityFocus(node);
    EXPECT_NE(manager_, nullptr);
    EXPECT_EQ(result, false);
}

/**
 * @tc.name: JsAccessibilityManagerTest009
 * @tc.desc: ClearAccessibilityFocus
 * @tc.type: FUNC
 * @tc.require:
 */
HWTEST_F(JsAccessibilityManagerTest, JsAccessibilityManagerTest009, TestSize.Level1)
{
    EXPECT_NE(manager_, nullptr);
    int32_t nodeId = -1;
    std::string tag = "tag";
    bool result = true;
    RefPtr<AccessibilityNode> node = AceType::MakeRefPtr<AccessibilityNode>(nodeId, tag);
    result = manager_->ClearAccessibilityFocus(node);
    EXPECT_NE(manager_, nullptr);
    EXPECT_EQ(result, false);
}

/**
 * @tc.name: JsAccessibilityManagerTest010
 * @tc.desc: RequestAccessibilityFocus
 * @tc.type: FUNC
 * @tc.require:
 */
HWTEST_F(JsAccessibilityManagerTest, JsAccessibilityManagerTest010, TestSize.Level1)
{
    EXPECT_NE(manager_, nullptr);
    int32_t nodeId = 0;
    std::string tag = "tag";
    bool result = true;
    RefPtr<AccessibilityNode> node = AceType::MakeRefPtr<AccessibilityNode>(nodeId, tag);
    result = manager_->RequestAccessibilityFocus(node);
    EXPECT_NE(manager_, nullptr);
    EXPECT_EQ(result, false);
}

/**
 * @tc.name: JsAccessibilityManagerTest011
 * @tc.desc: RequestAccessibilityFocus
 * @tc.type: FUNC
 * @tc.require:
 */
HWTEST_F(JsAccessibilityManagerTest, JsAccessibilityManagerTest011, TestSize.Level1)
{
    EXPECT_NE(manager_, nullptr);
    int32_t nodeId = -1;
    std::string tag = "tag";
    bool result = true;
    RefPtr<AccessibilityNode> node = AceType::MakeRefPtr<AccessibilityNode>(nodeId, tag);
    result = manager_->RequestAccessibilityFocus(node);
    EXPECT_NE(manager_, nullptr);
    EXPECT_EQ(result, false);
}

/**
 * @tc.name: JsAccessibilityManagerTest012
 * @tc.desc: SetExecuteActionResult
 * @tc.type: FUNC
 * @tc.require:
 */
HWTEST_F(JsAccessibilityManagerTest, JsAccessibilityManagerTest012, TestSize.Level1)
{
    EXPECT_NE(manager_, nullptr);
    manager_->Register(true);
    MockAccessibilityElementOperatorCallback mockCallback =
        MockAccessibilityElementOperatorCallback();
    manager_->SetExecuteActionResult(mockCallback, true, 0);
    EXPECT_NE(manager_, nullptr);
}

/**
 * @tc.name: JsAccessibilityManagerTest013
 * @tc.desc: SetExecuteActionResult
 * @tc.type: FUNC
 * @tc.require:
 */
HWTEST_F(JsAccessibilityManagerTest, JsAccessibilityManagerTest013, TestSize.Level1)
{
    EXPECT_NE(manager_, nullptr);
    manager_->Register(false);
    MockAccessibilityElementOperatorCallback mockCallback =
        MockAccessibilityElementOperatorCallback();
    manager_->SetExecuteActionResult(mockCallback, true, 0);
    EXPECT_NE(manager_, nullptr);
}

/**
 * @tc.name: JsAccessibilityManagerTest014
 * @tc.desc: SetFocusMoveSearchResult
 * @tc.type: FUNC
 * @tc.require:
 */
HWTEST_F(JsAccessibilityManagerTest, JsAccessibilityManagerTest014, TestSize.Level1)
{
    EXPECT_NE(manager_, nullptr);
    manager_->Register(true);
    Accessibility::AccessibilityElementInfo nodeInfo;
    MockAccessibilityElementOperatorCallback mockCallback =
        MockAccessibilityElementOperatorCallback();
    manager_->SetFocusMoveSearchResult(mockCallback, nodeInfo, 0);
    EXPECT_NE(manager_, nullptr);
}

/**
 * @tc.name: JsAccessibilityManagerTest015
 * @tc.desc: SetFocusMoveSearchResult
 * @tc.type: FUNC
 * @tc.require:
 */
HWTEST_F(JsAccessibilityManagerTest, JsAccessibilityManagerTest015, TestSize.Level1)
{
    EXPECT_NE(manager_, nullptr);
    manager_->Register(false);
    Accessibility::AccessibilityElementInfo nodeInfo;
    MockAccessibilityElementOperatorCallback mockCallback =
        MockAccessibilityElementOperatorCallback();
    manager_->SetFocusMoveSearchResult(mockCallback, nodeInfo, 0);
    EXPECT_NE(manager_, nullptr);
}
} // namespace OHOS::Ace::Framework
