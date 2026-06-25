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

#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "accessibility_element_info.h"
#include "adapter/ohos/osal/accessibility/accessibility_hidumper_osal.h"

#include "base/log/dump_log.h"
#include "core/accessibility/accessibility_utils.h"

#define private public
#define protected public


#include "base/log/dump_log.h"

#include "base/log/dump_log.h"
#include "core/accessibility/hidumper/accessibility_hidumper.h"

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/property/accessibility_property.h"


using namespace OHOS::Accessibility;
using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace {
} // namespace OHOS::Ace

namespace OHOS::Ace::NG {
namespace {
} // namespace


class AccessibilityHidumperOsalTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
};

void AccessibilityHidumperOsalTest::SetUpTestCase()
{
    std::unique_ptr<std::ostream> ostream = std::make_unique<std::ostringstream>();
    ASSERT_NE(ostream, nullptr);
    DumpLog::GetInstance().SetDumpFile(std::move(ostream));
}

void AccessibilityHidumperOsalTest::TearDownTestCase()
{
}

void AccessibilityHidumperOsalTest::SetUp()
{
    std::unique_ptr<std::ostream> ostream = std::make_unique<std::ostringstream>();
    ASSERT_NE(ostream, nullptr);
    DumpLog::GetInstance().SetDumpFile(std::move(ostream));
}

void AccessibilityHidumperOsalTest::TearDown()
{
}

/**
 * @tc.name: DumpCustomActionTest001
 * @tc.desc: Test DumpCustomActionTest with nullptr frameNode
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityHidumperOsalTest, DumpCustomActionTest001, TestSize.Level1)
{
    std::vector<std::string> params = {"--custom-action-test", "100"};
    RefPtr<FrameNode> frameNode = nullptr;
    Framework::AccessibilityManagerHidumper::DumpCustomActionTest(params, frameNode);
}

/**
 * @tc.name: DumpCustomActionTest002
 * @tc.desc: Test DumpCustomActionTest with invalid params (empty)
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityHidumperOsalTest, DumpCustomActionTest002, TestSize.Level1)
{
    std::vector<std::string> params;
    auto frameNode = FrameNode::CreateFrameNode("test", 100, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);
    Framework::AccessibilityManagerHidumper::DumpCustomActionTest(params, frameNode);
}

/**
 * @tc.name: DumpCustomActionTest003
 * @tc.desc: Test DumpCustomActionTest with no custom actions on node
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityHidumperOsalTest, DumpCustomActionTest003, TestSize.Level1)
{
    std::vector<std::string> params = {"--custom-action-test", "100", "--list"};
    auto frameNode = FrameNode::CreateFrameNode("test", 100, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);
    auto prop = frameNode->GetAccessibilityProperty<AccessibilityProperty>();
    ASSERT_NE(prop, nullptr);
    prop->SetAccessibilityCustomActions({});
    Framework::AccessibilityManagerHidumper::DumpCustomActionTest(params, frameNode);
}

/**
 * @tc.name: DumpCustomActionTest004
 * @tc.desc: Test DumpCustomActionTest with list flag and custom actions present
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityHidumperOsalTest, DumpCustomActionTest004, TestSize.Level1)
{
    std::vector<std::string> params = {"--custom-action-test", "100", "--list"};
    auto frameNode = FrameNode::CreateFrameNode("test", 100, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);
    auto prop = frameNode->GetAccessibilityProperty<AccessibilityProperty>();
    ASSERT_NE(prop, nullptr);
    std::vector<AccessibilityCustomAction> actions;
    actions.push_back({"action1", nullptr});
    actions.push_back({"action2", []() {}});
    prop->SetAccessibilityCustomActions(actions);
    Framework::AccessibilityManagerHidumper::DumpCustomActionTest(params, frameNode);
}

/**
 * @tc.name: DumpCustomActionTest005
 * @tc.desc: Test DumpCustomActionTest execute action with valid callback
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityHidumperOsalTest, DumpCustomActionTest005, TestSize.Level1)
{
    bool callbackExecuted = false;
    std::vector<std::string> params = {"--custom-action-test", "100", "--list", "testAction"};
    auto frameNode = FrameNode::CreateFrameNode("test", 100, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);
    auto prop = frameNode->GetAccessibilityProperty<AccessibilityProperty>();
    ASSERT_NE(prop, nullptr);
    std::vector<AccessibilityCustomAction> actions;
    actions.push_back({"testAction", [&callbackExecuted]() { callbackExecuted = true; }});
    prop->SetAccessibilityCustomActions(actions);

    Framework::AccessibilityManagerHidumper::DumpCustomActionTest(params, frameNode);
    EXPECT_FALSE(callbackExecuted);
}

/**
 * @tc.name: DumpCustomActionTest006
 * @tc.desc: Test DumpCustomActionTest with --list and no action name (should print list only)
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityHidumperOsalTest, DumpCustomActionTest006, TestSize.Level1)
{
    std::vector<std::string> params = {"--custom-action-test", "100"};
    auto frameNode = FrameNode::CreateFrameNode("test", 100, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);
    auto prop = frameNode->GetAccessibilityProperty<AccessibilityProperty>();
    ASSERT_NE(prop, nullptr);
    std::vector<AccessibilityCustomAction> actions;
    actions.push_back({"action1", nullptr});
    prop->SetAccessibilityCustomActions(actions);
    Framework::AccessibilityManagerHidumper::DumpCustomActionTest(params, frameNode);
}

/**
 * @tc.name: DumpCustomActionTest007
 * @tc.desc: Test DumpCustomActionTest with null callback action
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityHidumperOsalTest, DumpCustomActionTest007, TestSize.Level1)
{
    std::vector<std::string> params = {"--custom-action-test", "100", "--list", "nullAction"};
    auto frameNode = FrameNode::CreateFrameNode("test", 100, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);
    auto prop = frameNode->GetAccessibilityProperty<AccessibilityProperty>();
    ASSERT_NE(prop, nullptr);
    std::vector<AccessibilityCustomAction> actions;
    actions.push_back({"nullAction", nullptr});
    prop->SetAccessibilityCustomActions(actions);
    Framework::AccessibilityManagerHidumper::DumpCustomActionTest(params, frameNode);
}

/**
 * @tc.name: DumpCustomActionTest008
 * @tc.desc: Test DumpCustomActionTest with action name not found
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityHidumperOsalTest, DumpCustomActionTest008, TestSize.Level1)
{
    std::vector<std::string> params = {"--custom-action-test", "100", "--list", "nonExistentAction"};
    auto frameNode = FrameNode::CreateFrameNode("test", 100, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);
    auto prop = frameNode->GetAccessibilityProperty<AccessibilityProperty>();
    ASSERT_NE(prop, nullptr);
    std::vector<AccessibilityCustomAction> actions;
    actions.push_back({"existingAction", []() {}});
    prop->SetAccessibilityCustomActions(actions);
    Framework::AccessibilityManagerHidumper::DumpCustomActionTest(params, frameNode);
}

/**
 * @tc.name: DumpCustomActionTest009
 * @tc.desc: Test DumpCustomActionTest with multiple custom actions
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityHidumperOsalTest, DumpCustomActionTest009, TestSize.Level1)
{
    std::vector<std::string> params = {"--custom-action-test", "100", "--list"};
    auto frameNode = FrameNode::CreateFrameNode("test", 100, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);
    auto prop = frameNode->GetAccessibilityProperty<AccessibilityProperty>();
    ASSERT_NE(prop, nullptr);
    std::vector<AccessibilityCustomAction> actions;
    actions.push_back({"action1", []() {}});
    actions.push_back({"action2", nullptr});
    actions.push_back({"action3", []() {}});
    prop->SetAccessibilityCustomActions(actions);
    Framework::AccessibilityManagerHidumper::DumpCustomActionTest(params, frameNode);
}

/**
 * @tc.name: DumpCustomActionTest010
 * @tc.desc: Test DumpCustomActionTest with --custom-action-test but missing node id
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityHidumperOsalTest, DumpCustomActionTest010, TestSize.Level1)
{
    std::vector<std::string> params = {"--custom-action-test"};
    auto frameNode = FrameNode::CreateFrameNode("test", 100, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);
    Framework::AccessibilityManagerHidumper::DumpCustomActionTest(params, frameNode);
}

/**
 * @tc.name: DumpCustomActionTest011
 * @tc.desc: Test DumpCustomActionTest with empty custom actions
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityHidumperOsalTest, DumpCustomActionTest011, TestSize.Level1)
{
    std::vector<std::string> params = {"--custom-action-test", "100", "--list"};
    auto frameNode = FrameNode::CreateFrameNode("test", 100, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);
    auto prop = frameNode->GetAccessibilityProperty<AccessibilityProperty>();
    ASSERT_NE(prop, nullptr);
    Framework::AccessibilityManagerHidumper::DumpCustomActionTest(params, frameNode);
}

/**
 * @tc.name: DumpCustomActionTest012
 * @tc.desc: Test DumpCustomActionTest with --list and valid custom actions
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityHidumperOsalTest, DumpCustomActionTest012, TestSize.Level1)
{
    std::vector<std::string> params = {"--custom-action-test", "100", "--list"};
    auto frameNode = FrameNode::CreateFrameNode("test", 100, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);
    auto prop = frameNode->GetAccessibilityProperty<AccessibilityProperty>();
    ASSERT_NE(prop, nullptr);
    std::vector<AccessibilityCustomAction> actions;
    actions.push_back({"action1", []() {}});
    actions.push_back({"action2", nullptr});
    prop->SetAccessibilityCustomActions(actions);
    Framework::AccessibilityManagerHidumper::DumpCustomActionTest(params, frameNode);
}

/**
 * @tc.name: DumpCustomActionTest013
 * @tc.desc: Test DumpCustomActionTest with --execute but empty action name
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityHidumperOsalTest, DumpCustomActionTest013, TestSize.Level1)
{
    std::vector<std::string> params = {"--custom-action-test", "100"};
    auto frameNode = FrameNode::CreateFrameNode("test", 100, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);
    auto prop = frameNode->GetAccessibilityProperty<AccessibilityProperty>();
    ASSERT_NE(prop, nullptr);
    std::vector<AccessibilityCustomAction> actions;
    actions.push_back({"action1", []() {}});
    prop->SetAccessibilityCustomActions(actions);
    Framework::AccessibilityManagerHidumper::DumpCustomActionTest(params, frameNode);
}

/**
 * @tc.name: DumpCustomActionTest014
 * @tc.desc: Test DumpCustomActionTest executing action with valid callback
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityHidumperOsalTest, DumpCustomActionTest014, TestSize.Level1)
{
    bool callbackExecuted = false;
    std::vector<std::string> params = {"--custom-action-test", "100", "--execute", "testAction"};
    auto frameNode = FrameNode::CreateFrameNode("test", 100, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);
    auto prop = frameNode->GetAccessibilityProperty<AccessibilityProperty>();
    ASSERT_NE(prop, nullptr);
    std::vector<AccessibilityCustomAction> actions;
    actions.push_back({"testAction", [&callbackExecuted]() { callbackExecuted = true; }});
    prop->SetAccessibilityCustomActions(actions);
    Framework::AccessibilityManagerHidumper::DumpCustomActionTest(params, frameNode);
    EXPECT_TRUE(callbackExecuted);
}

/**
 * @tc.name: DumpCustomActionTest015
 * @tc.desc: Test DumpCustomActionTest executing action with null callback
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityHidumperOsalTest, DumpCustomActionTest015, TestSize.Level1)
{
    std::vector<std::string> params = {"--custom-action-test", "100", "--execute", "nullAction"};
    auto frameNode = FrameNode::CreateFrameNode("test", 100, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);
    auto prop = frameNode->GetAccessibilityProperty<AccessibilityProperty>();
    ASSERT_NE(prop, nullptr);
    std::vector<AccessibilityCustomAction> actions;
    actions.push_back({"nullAction", nullptr});
    prop->SetAccessibilityCustomActions(actions);
    Framework::AccessibilityManagerHidumper::DumpCustomActionTest(params, frameNode);
}

/**
 * @tc.name: DumpCustomActionTest016
 * @tc.desc: Test DumpCustomActionTest executing action with name not found
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityHidumperOsalTest, DumpCustomActionTest016, TestSize.Level1)
{
    std::vector<std::string> params = {"--custom-action-test", "100", "--execute", "nonExistent"};
    auto frameNode = FrameNode::CreateFrameNode("test", 100, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);
    auto prop = frameNode->GetAccessibilityProperty<AccessibilityProperty>();
    ASSERT_NE(prop, nullptr);
    std::vector<AccessibilityCustomAction> actions;
    actions.push_back({"existingAction", []() {}});
    prop->SetAccessibilityCustomActions(actions);
    Framework::AccessibilityManagerHidumper::DumpCustomActionTest(params, frameNode);
}
} // namespace OHOS::Ace::NG