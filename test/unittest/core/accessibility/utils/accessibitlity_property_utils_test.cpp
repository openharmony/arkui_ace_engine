/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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
#include "frameworks/core/accessibility/utils/accessibility_property_utils.h"

using namespace OHOS::Accessibility;
using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace {
} // namespace OHOS::Ace

namespace OHOS::Ace::NG {
namespace {
} // namespace


class AccessibilityPropertyUtilsTest  : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
};

void AccessibilityPropertyUtilsTest ::SetUpTestCase()
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

void AccessibilityPropertyUtilsTest ::TearDownTestCase()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

/**
 * @tc.name: GetContent001
 * @tc.desc: Get Content of frameNode
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityPropertyUtilsTest, GetContent001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode("frameNode",
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>(), false);
    ASSERT_NE(frameNode, nullptr);
    auto accessibilityProperty = frameNode->GetAccessibilityProperty<AccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);

    // step1. not hasUserTextValue
    std::string testStr = "test";
    accessibilityProperty->SetText(testStr);
    auto result = AccessibilityPropertyUtils::GetContent(accessibilityProperty);
    EXPECT_EQ(result, testStr);
    // step2. hasUserTextValue
    std::string testStr2 = "hello";
    accessibilityProperty->SetUserTextValue(testStr2);
    result = AccessibilityPropertyUtils::GetContent(accessibilityProperty);
    EXPECT_EQ(result, testStr2);
}


/**
 * @tc.name: GetAccessibilityText001
 * @tc.desc: Get AccessibilityText of frameNode
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityPropertyUtilsTest, GetAccessibilityText001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode("frameNode",
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>(), false);
    ASSERT_NE(frameNode, nullptr);
    auto accessibilityProperty = frameNode->GetAccessibilityProperty<AccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    auto frameNode1 = FrameNode::CreateFrameNode("frameNode1",
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>(), false);
    ASSERT_NE(frameNode1, nullptr);
    frameNode->AddChild(frameNode1);
    auto accessibilityProperty1 = frameNode1->GetAccessibilityProperty<AccessibilityProperty>();
    ASSERT_NE(accessibilityProperty1, nullptr);
    std::string testStr = "test";
    std::string testStr1 = "test1";
    std::string testStr2 = "test, test1";
    accessibilityProperty->SetAccessibilityText(testStr);
    accessibilityProperty1->SetAccessibilityText(testStr1);
    // step1. only accessibility
    auto result = AccessibilityPropertyUtils::GetAccessibilityText(accessibilityProperty);
    EXPECT_EQ(result, testStr);
    // step2. hasUserTextValue no
    // step2.1 GetAccessibilityText not empty
    // step2.1.1 IsAccessibilityGroup false
    // step2-1-1-1 IsAccessibilityTextPreferred false
    result = AccessibilityPropertyUtils::GetAccessibilityText(accessibilityProperty);
    EXPECT_EQ(result, testStr);
    // step2-1-1-2 IsAccessibilityTextPreferred true
    accessibilityProperty->SetAccessibilityTextPreferred(true);
    result = AccessibilityPropertyUtils::GetAccessibilityText(accessibilityProperty);
    EXPECT_EQ(result, testStr);
    // step2.1.2 IsAccessibilityGroup true
    // step2-1-2-1 IsAccessibilityTextPreferred false
    accessibilityProperty->SetAccessibilityTextPreferred(false);
    result = AccessibilityPropertyUtils::GetAccessibilityText(accessibilityProperty);
    EXPECT_EQ(result, testStr);
    // step2-1-2-2 IsAccessibilityTextPreferred true
    accessibilityProperty->SetAccessibilityTextPreferred(true);
    result = AccessibilityPropertyUtils::GetAccessibilityText(accessibilityProperty);
    EXPECT_EQ(result, testStr);
}

/**
 * @tc.name: GetAccessibilityText001
 * @tc.desc: Get AccessibilityText of frameNode
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityPropertyUtilsTest, GetAccessibilityText002, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode("frameNode",
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>(), false);
    ASSERT_NE(frameNode, nullptr);
    auto accessibilityProperty = frameNode->GetAccessibilityProperty<AccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    auto frameNode1 = FrameNode::CreateFrameNode("frameNode1",
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>(), false);
    ASSERT_NE(frameNode1, nullptr);
    frameNode->AddChild(frameNode1);
    frameNode->frameChildren_.emplace(frameNode1);
    auto accessibilityProperty1 = frameNode1->GetAccessibilityProperty<AccessibilityProperty>();
    ASSERT_NE(accessibilityProperty1, nullptr);
    std::string testStr = "test";
    std::string testStr1 = "test1";
    accessibilityProperty->SetAccessibilityText("");
    accessibilityProperty1->SetAccessibilityText(testStr1);
    // step2. hasUserTextValue no
    // step2.2 GetAccessibilityText empty
    // step2.2.1 IsAccessibilityGroup false
    // step2-2-1-1 IsAccessibilityTextPreferred false
    auto result = AccessibilityPropertyUtils::GetAccessibilityText(accessibilityProperty);
    EXPECT_EQ(result, "");
    // step2-2-1-2 IsAccessibilityTextPreferred true
    accessibilityProperty->SetAccessibilityTextPreferred(true);
    result = AccessibilityPropertyUtils::GetAccessibilityText(accessibilityProperty);
    EXPECT_EQ(result, "");
    // step2.2.2 IsAccessibilityGroup true
    accessibilityProperty->SetAccessibilityGroup(true);
    // step2-2-2-1 IsAccessibilityTextPreferred false
    accessibilityProperty->SetAccessibilityTextPreferred(false);
    result = AccessibilityPropertyUtils::GetAccessibilityText(accessibilityProperty);
    EXPECT_EQ(result, "");
    // step2-2-2-2 IsAccessibilityTextPreferred true
    accessibilityProperty->SetAccessibilityTextPreferred(true);
    result = AccessibilityPropertyUtils::GetAccessibilityText(accessibilityProperty);
    EXPECT_EQ(result, testStr1);
}

/**
 * @tc.name: GetAccessibilityText001
 * @tc.desc: Get AccessibilityText of frameNode
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityPropertyUtilsTest, GetAccessibilityText003, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode("frameNode",
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>(), false);
    ASSERT_NE(frameNode, nullptr);
    auto accessibilityProperty = frameNode->GetAccessibilityProperty<AccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    auto frameNode1 = FrameNode::CreateFrameNode("frameNode1",
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>(), false);
    ASSERT_NE(frameNode1, nullptr);
    frameNode->AddChild(frameNode1);
    auto accessibilityProperty1 = frameNode1->GetAccessibilityProperty<AccessibilityProperty>();
    ASSERT_NE(accessibilityProperty1, nullptr);
    std::string testStr = "test";
    std::string testStr1 = "test1";

    accessibilityProperty1->SetAccessibilityText(testStr1);
    // step3. hasUserTextValue yes
    accessibilityProperty->SetUserTextValue("hello");
    // all other conditon will be GetAccessibilityText
    // step3.1 GetAccessibilityText not empty
    accessibilityProperty->SetAccessibilityText(testStr);
    accessibilityProperty->SetAccessibilityGroup(false);
    accessibilityProperty->SetAccessibilityTextPreferred(false);
    bool result = AccessibilityPropertyUtils::GetAccessibilityText(accessibilityProperty) != testStr;
    accessibilityProperty->SetAccessibilityTextPreferred(true);
    result |= AccessibilityPropertyUtils::GetAccessibilityText(accessibilityProperty) != testStr;
    accessibilityProperty->SetAccessibilityGroup(true);
    accessibilityProperty->SetAccessibilityTextPreferred(false);
    result |= AccessibilityPropertyUtils::GetAccessibilityText(accessibilityProperty) != testStr;
    accessibilityProperty->SetAccessibilityTextPreferred(true);
    result |= AccessibilityPropertyUtils::GetAccessibilityText(accessibilityProperty) != testStr;
    // step3.2 GetAccessibilityText empty
    testStr = "";
    accessibilityProperty->SetAccessibilityText(testStr);
    accessibilityProperty->SetAccessibilityGroup(false);
    accessibilityProperty->SetAccessibilityTextPreferred(false);
    result = AccessibilityPropertyUtils::GetAccessibilityText(accessibilityProperty) != testStr;
    accessibilityProperty->SetAccessibilityTextPreferred(true);
    result |= AccessibilityPropertyUtils::GetAccessibilityText(accessibilityProperty) != testStr;
    accessibilityProperty->SetAccessibilityGroup(true);
    accessibilityProperty->SetAccessibilityTextPreferred(false);
    result |= AccessibilityPropertyUtils::GetAccessibilityText(accessibilityProperty) != testStr;
    accessibilityProperty->SetAccessibilityTextPreferred(true);
    result |= AccessibilityPropertyUtils::GetAccessibilityText(accessibilityProperty) != testStr;

    EXPECT_EQ(result, false);
}
/**
 * @tc.name: GetComponentType001
 * @tc.desc: Get AccessibilityText of frameNode
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityPropertyUtilsTest, GetComponentType001, TestSize.Level1)
{
    std::string testTag = "frameNode";
    auto frameNode = FrameNode::CreateFrameNode(testTag,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>(), false);
    ASSERT_NE(frameNode, nullptr);
    auto accessibilityProperty = frameNode->GetAccessibilityProperty<AccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);

    // 1. only tag
    auto result = AccessibilityPropertyUtils::GetComponentType(frameNode, accessibilityProperty);
    EXPECT_EQ(result, testTag);
    // 2. HasAccessibilityRole
    std::string testTag1 = "frameNode1";
    accessibilityProperty->SetAccessibilityRole(testTag1);
    result = AccessibilityPropertyUtils::GetComponentType(frameNode, accessibilityProperty);
    EXPECT_EQ(result, testTag1);
    // 3. HasAccessibilityCustomRole
    std::string testTag2 = "frameNode2";
    accessibilityProperty->SetAccessibilityCustomRole(testTag2);
    result = AccessibilityPropertyUtils::GetComponentType(frameNode, accessibilityProperty);
    EXPECT_EQ(result, testTag2);
    // 4. ResetAccessibilityCustomRole, equals to AccessibilityRole
    accessibilityProperty->ResetAccessibilityCustomRole();
    result = AccessibilityPropertyUtils::GetComponentType(frameNode, accessibilityProperty);
    EXPECT_EQ(result, testTag1);
    // 5. ResetAccessibilityRole , equals to tag
    accessibilityProperty->ResetAccessibilityRole();
    result = AccessibilityPropertyUtils::GetComponentType(frameNode, accessibilityProperty);
    EXPECT_EQ(result, testTag);
}

/**
 * @tc.name: CheckAndGetStateController001
 * @tc.desc: test CheckAndGetStateController when node is nullptr
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityPropertyUtilsTest, CheckAndGetStateController001, TestSize.Level1)
{
    RefPtr<NG::FrameNode> node = nullptr;
    RefPtr<NG::FrameNode> controllerNode = nullptr;
    auto result = AccessibilityPropertyUtils::CheckAndGetStateController(node, controllerNode);
    EXPECT_EQ(controllerNode, nullptr);
    EXPECT_EQ(result, StateControllerType::CONTROLLER_NONE);
}

/**
 * @tc.name: CheckAndGetStateController002
 * @tc.desc: test CheckAndGetStateController when accessibilityGroup is false
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityPropertyUtilsTest, CheckAndGetStateController002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct frameNode
     */
    std::string testTag = "frameNode";
    auto frameNode = FrameNode::CreateFrameNode(testTag,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>(), false);
    ASSERT_NE(frameNode, nullptr);
    auto accessibilityProperty = frameNode->GetAccessibilityProperty<AccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    EXPECT_FALSE(accessibilityProperty->IsAccessibilityGroup());

    /**
     * @tc.steps: step2. test CheckAndGetStateController
     */
    RefPtr<NG::FrameNode> controllerNode = nullptr;
    auto result = AccessibilityPropertyUtils::CheckAndGetStateController(frameNode, controllerNode);
    EXPECT_EQ(controllerNode, nullptr);
    EXPECT_EQ(result, StateControllerType::CONTROLLER_NONE);
}

/**
 * @tc.name: CheckAndGetStateController003
 * @tc.desc: test CheckAndGetStateController when controllerByInspector is empty and not SupportControllerType
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityPropertyUtilsTest, CheckAndGetStateController003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct frameNode
     */
    std::string testTag = "frameNode";
    auto frameNode = FrameNode::CreateFrameNode(testTag,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>(), false);
    ASSERT_NE(frameNode, nullptr);
    auto accessibilityProperty = frameNode->GetAccessibilityProperty<AccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    accessibilityProperty->SetAccessibilityGroup(true);
    EXPECT_TRUE(accessibilityProperty->IsAccessibilityGroup());

    /**
     * @tc.steps: step2. construct AccessibilityGroupOptions
     */
    AccessibilityGroupOptions accessibilityGroupOptions;
    EXPECT_TRUE(accessibilityGroupOptions.stateControllerByInspector.empty());
    accessibilityGroupOptions.stateControllerByType = AccessibilityRoleType::ALERT_DIALOG;
    accessibilityProperty->SetAccessibilityGroupOptions(accessibilityGroupOptions);

    /**
     * @tc.steps: step3. test CheckAndGetStateController
     */
    RefPtr<NG::FrameNode> controllerNode = nullptr;
    auto result = AccessibilityPropertyUtils::CheckAndGetStateController(frameNode, controllerNode);
    EXPECT_EQ(controllerNode, nullptr);
    EXPECT_EQ(result, StateControllerType::CONTROLLER_NONE);
}

/**
 * @tc.name: CheckAndGetActionController001
 * @tc.desc: test CheckAndGetActionController when node is nullptr
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityPropertyUtilsTest, CheckAndGetActionController001, TestSize.Level1)
{
    RefPtr<NG::FrameNode> node = nullptr;
    RefPtr<NG::FrameNode> controllerNode = nullptr;
    auto result = AccessibilityPropertyUtils::CheckAndGetActionController(node, controllerNode);
    EXPECT_EQ(controllerNode, nullptr);
    EXPECT_EQ(result, ActionControllerType::CONTROLLER_NONE);
}

/**
 * @tc.name: CheckAndGetActionController002
 * @tc.desc: test CheckAndGetActionController when accessibilityGroup is false
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityPropertyUtilsTest, CheckAndGetActionController002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct frameNode
     */
    std::string testTag = "frameNode";
    auto frameNode = FrameNode::CreateFrameNode(testTag,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>(), false);
    ASSERT_NE(frameNode, nullptr);
    auto accessibilityProperty = frameNode->GetAccessibilityProperty<AccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    EXPECT_FALSE(accessibilityProperty->IsAccessibilityGroup());

    /**
     * @tc.steps: step2. test CheckAndGetActionController
     */
    RefPtr<NG::FrameNode> controllerNode = nullptr;
    auto result = AccessibilityPropertyUtils::CheckAndGetActionController(frameNode, controllerNode);
    EXPECT_EQ(controllerNode, nullptr);
    EXPECT_EQ(result, ActionControllerType::CONTROLLER_NONE);
}

/**
 * @tc.name: CheckAndGetActionController003
 * @tc.desc: test CheckAndGetActionController when controllerByInspector is empty and not SupportControllerType
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityPropertyUtilsTest, CheckAndGetActionController003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct frameNode
     */
    std::string testTag = "frameNode";
    auto frameNode = FrameNode::CreateFrameNode(testTag,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>(), false);
    ASSERT_NE(frameNode, nullptr);
    auto accessibilityProperty = frameNode->GetAccessibilityProperty<AccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    accessibilityProperty->SetAccessibilityGroup(true);
    EXPECT_TRUE(accessibilityProperty->IsAccessibilityGroup());

    /**
     * @tc.steps: step2. construct AccessibilityGroupOptions
     */
    AccessibilityGroupOptions accessibilityGroupOptions;
    EXPECT_TRUE(accessibilityGroupOptions.actionControllerByInspector.empty());
    accessibilityGroupOptions.actionControllerByType = AccessibilityRoleType::ALERT_DIALOG;
    accessibilityProperty->SetAccessibilityGroupOptions(accessibilityGroupOptions);

    /**
     * @tc.steps: step3. test CheckAndGetActionController
     */
    RefPtr<NG::FrameNode> controllerNode = nullptr;
    auto result = AccessibilityPropertyUtils::CheckAndGetActionController(frameNode, controllerNode);
    EXPECT_EQ(controllerNode, nullptr);
    EXPECT_EQ(result, ActionControllerType::CONTROLLER_NONE);
}

/**
 * @tc.name: NeedRemoveControllerTextFromGroup001
 * @tc.desc: test NeedRemoveControllerTextFromGroup when node is nullptr
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityPropertyUtilsTest, NeedRemoveControllerTextFromGroup001, TestSize.Level1)
{
    RefPtr<NG::FrameNode> node = nullptr;
    auto result = AccessibilityPropertyUtils::NeedRemoveControllerTextFromGroup(node);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: NeedRemoveControllerTextFromGroup002
 * @tc.desc: test NeedRemoveControllerTextFromGroup when node has nothing
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityPropertyUtilsTest, NeedRemoveControllerTextFromGroup002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct frameNode
     */
    std::string testTag = "frameNodeForTestNeedRemoveControllerTextFromGroup";
    auto frameNode = FrameNode::CreateFrameNode(testTag,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>(), false);
    ASSERT_NE(frameNode, nullptr);
    auto accessibilityProperty = frameNode->GetAccessibilityProperty<AccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    EXPECT_FALSE(accessibilityProperty->HasAccessibilityCustomRole());
    EXPECT_FALSE(accessibilityProperty->HasAccessibilityRole());

    /**
     * @tc.steps: step2. test NeedRemoveControllerTextFromGroup
     */
    auto result = AccessibilityPropertyUtils::NeedRemoveControllerTextFromGroup(frameNode);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: NeedRemoveControllerTextFromGroup003
 * @tc.desc: test NeedRemoveControllerTextFromGroup when node has AccessibilityCustomRole
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityPropertyUtilsTest, NeedRemoveControllerTextFromGroup003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct frameNode
     */
    std::string testTag = "frameNodeForTestNeedRemoveControllerTextFromGroup";
    auto frameNode = FrameNode::CreateFrameNode(testTag,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>(), false);
    ASSERT_NE(frameNode, nullptr);
    auto accessibilityProperty = frameNode->GetAccessibilityProperty<AccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    EXPECT_FALSE(accessibilityProperty->HasAccessibilityCustomRole());

    /**
     * @tc.steps: step2. test NeedRemoveControllerTextFromGroup
     */
    accessibilityProperty->accessibilityCustomRole_ = "";
    EXPECT_TRUE(accessibilityProperty->HasAccessibilityCustomRole());
    auto result = AccessibilityPropertyUtils::NeedRemoveControllerTextFromGroup(frameNode);
    EXPECT_FALSE(result);
    accessibilityProperty->accessibilityCustomRole_ = "InvalidRole";
    EXPECT_TRUE(accessibilityProperty->HasAccessibilityCustomRole());
    result = AccessibilityPropertyUtils::NeedRemoveControllerTextFromGroup(frameNode);
    EXPECT_FALSE(result);
    accessibilityProperty->accessibilityCustomRole_ = "checkbox";
    EXPECT_TRUE(accessibilityProperty->HasAccessibilityCustomRole());
    result = AccessibilityPropertyUtils::NeedRemoveControllerTextFromGroup(frameNode);
    EXPECT_TRUE(result);
    accessibilityProperty->accessibilityCustomRole_ = "checkboxgroup";
    EXPECT_TRUE(accessibilityProperty->HasAccessibilityCustomRole());
    result = AccessibilityPropertyUtils::NeedRemoveControllerTextFromGroup(frameNode);
    EXPECT_TRUE(result);
    accessibilityProperty->accessibilityCustomRole_ = "radio";
    EXPECT_TRUE(accessibilityProperty->HasAccessibilityCustomRole());
    result = AccessibilityPropertyUtils::NeedRemoveControllerTextFromGroup(frameNode);
    EXPECT_TRUE(result);
    accessibilityProperty->accessibilityCustomRole_ = "imagedata";
    EXPECT_TRUE(accessibilityProperty->HasAccessibilityCustomRole());
    result = AccessibilityPropertyUtils::NeedRemoveControllerTextFromGroup(frameNode);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: NeedRemoveControllerTextFromGroup004
 * @tc.desc: test NeedRemoveControllerTextFromGroup when node has AccessibilityRole
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityPropertyUtilsTest, NeedRemoveControllerTextFromGroup004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct frameNode
     */
    std::string testTag = "frameNodeForTestNeedRemoveControllerTextFromGroup";
    auto frameNode = FrameNode::CreateFrameNode(testTag,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>(), false);
    ASSERT_NE(frameNode, nullptr);
    auto accessibilityProperty = frameNode->GetAccessibilityProperty<AccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    EXPECT_FALSE(accessibilityProperty->HasAccessibilityCustomRole());
    EXPECT_FALSE(accessibilityProperty->HasAccessibilityRole());

    /**
     * @tc.steps: step2. test NeedRemoveControllerTextFromGroup
     */
    accessibilityProperty->accessibilityRole_ = "";
    EXPECT_TRUE(accessibilityProperty->HasAccessibilityRole());
    auto result = AccessibilityPropertyUtils::NeedRemoveControllerTextFromGroup(frameNode);
    EXPECT_FALSE(result);
    accessibilityProperty->accessibilityRole_ = "InvalidRole";
    EXPECT_TRUE(accessibilityProperty->HasAccessibilityRole());
    result = AccessibilityPropertyUtils::NeedRemoveControllerTextFromGroup(frameNode);
    EXPECT_FALSE(result);
    accessibilityProperty->accessibilityRole_ = V2::CHECK_BOX_ETS_TAG;
    EXPECT_TRUE(accessibilityProperty->HasAccessibilityRole());
    result = AccessibilityPropertyUtils::NeedRemoveControllerTextFromGroup(frameNode);
    EXPECT_TRUE(result);
    accessibilityProperty->accessibilityRole_ = V2::CHECKBOXGROUP_ETS_TAG;
    EXPECT_TRUE(accessibilityProperty->HasAccessibilityRole());
    result = AccessibilityPropertyUtils::NeedRemoveControllerTextFromGroup(frameNode);
    EXPECT_TRUE(result);
    accessibilityProperty->accessibilityRole_ = V2::RADIO_ETS_TAG;
    EXPECT_TRUE(accessibilityProperty->HasAccessibilityRole());
    result = AccessibilityPropertyUtils::NeedRemoveControllerTextFromGroup(frameNode);
    EXPECT_TRUE(result);
    accessibilityProperty->accessibilityRole_ = V2::LINE_ETS_TAG;
    EXPECT_TRUE(accessibilityProperty->HasAccessibilityRole());
    result = AccessibilityPropertyUtils::NeedRemoveControllerTextFromGroup(frameNode);
    EXPECT_FALSE(result);
}
} // namespace OHOS::Ace::NG