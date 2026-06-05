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

#include "gtest/gtest.h"

#define private public
#define protected public

#include "test/mock/frameworks/base/thread/mock_task_executor.h"
#include "test/mock/frameworks/core/common/mock_container.h"
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"

#include "base/log/dump_log.h"
#include "core/accessibility/node_utils/accessibility_frame_node_utils.h"
#include "core/components_ng/property/accessibility_property.h"
#include "core/pipeline_ng/pipeline_context.h"

using namespace testing;
using namespace testing::ext;

namespace {
const char* const TEST_TAG_CUSTOM = "customNode";
} // namespace

namespace OHOS::Ace::NG {

class AccessibilityFrameNodeUtilsTestThree : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
};

void AccessibilityFrameNodeUtilsTestThree::SetUpTestCase()
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

void AccessibilityFrameNodeUtilsTestThree::TearDownTestCase()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

// ==================== CustomAccessibilityProperty SetAccessibilityText/GetAccessibilityText ====================

/**
 * @tc.name: CustomAccessibilityPropertySetAccessibilityText001
 * @tc.desc: Test SetAccessibilityText and GetAccessibilityText
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityFrameNodeUtilsTestThree, CustomAccessibilityPropertySetAccessibilityText001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create CustomAccessibilityProperty and set text
     * @tc.expected: GetAccessibilityText returns the set value
     */
    auto prop = AceType::MakeRefPtr<CustomAccessibilityProperty>();
    ASSERT_NE(prop, nullptr);
    std::string text = "test_accessibility_text";
    prop->SetAccessibilityText(text);
    EXPECT_EQ(prop->GetAccessibilityText(), text);
}

// ==================== CustomAccessibilityProperty SetAccessibilityLevel/GetAccessibilityLevel ====================

/**
 * @tc.name: CustomAccessibilityPropertySetAccessibilityLevel001
 * @tc.desc: Test SetAccessibilityLevel and GetAccessibilityLevel
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityFrameNodeUtilsTestThree, CustomAccessibilityPropertySetAccessibilityLevel001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create CustomAccessibilityProperty and set level
     * @tc.expected: GetAccessibilityLevel returns the set value
     */
    auto prop = AceType::MakeRefPtr<CustomAccessibilityProperty>();
    ASSERT_NE(prop, nullptr);
    prop->SetAccessibilityLevel("yes");
    EXPECT_EQ(prop->GetAccessibilityLevel(), "yes");
}

// ==================== CustomAccessibilityProperty SetAccessibilityGroup/GetAccessibilityGroup ====================

/**
 * @tc.name: CustomAccessibilityPropertySetAccessibilityGroup001
 * @tc.desc: Test SetAccessibilityGroup and GetAccessibilityGroup
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityFrameNodeUtilsTestThree, CustomAccessibilityPropertySetAccessibilityGroup001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create CustomAccessibilityProperty and set group to true
     * @tc.expected: GetAccessibilityGroup returns true
     */
    auto prop = AceType::MakeRefPtr<CustomAccessibilityProperty>();
    ASSERT_NE(prop, nullptr);
    prop->SetAccessibilityGroup(true);
    EXPECT_TRUE(prop->GetAccessibilityGroup());
}

/**
 * @tc.name: CustomAccessibilityPropertySetAccessibilityGroup002
 * @tc.desc: Test default value of GetAccessibilityGroup is false
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityFrameNodeUtilsTestThree, CustomAccessibilityPropertySetAccessibilityGroup002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create CustomAccessibilityProperty without setting group
     * @tc.expected: GetAccessibilityGroup returns false (default)
     */
    auto prop = AceType::MakeRefPtr<CustomAccessibilityProperty>();
    ASSERT_NE(prop, nullptr);
    EXPECT_FALSE(prop->GetAccessibilityGroup());
}

// ==================== CustomAccessibilityProperty SetRole/GetRole ====================

/**
 * @tc.name: CustomAccessibilityPropertySetRole001
 * @tc.desc: Test SetRole and GetRole
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityFrameNodeUtilsTestThree, CustomAccessibilityPropertySetRole001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create CustomAccessibilityProperty and set role
     * @tc.expected: GetRole returns the set value
     */
    auto prop = AceType::MakeRefPtr<CustomAccessibilityProperty>();
    ASSERT_NE(prop, nullptr);
    prop->SetRole("button");
    EXPECT_EQ(prop->GetRole(), "button");
}

// ==================== CustomAccessibilityProperty SetCheckable/GetCheckable ====================

/**
 * @tc.name: CustomAccessibilityPropertySetCheckable001
 * @tc.desc: Test SetCheckable and GetCheckable
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityFrameNodeUtilsTestThree, CustomAccessibilityPropertySetCheckable001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create CustomAccessibilityProperty and set checkable to true
     * @tc.expected: GetCheckable returns true
     */
    auto prop = AceType::MakeRefPtr<CustomAccessibilityProperty>();
    ASSERT_NE(prop, nullptr);
    prop->SetCheckable(true);
    EXPECT_TRUE(prop->GetCheckable());
}

/**
 * @tc.name: CustomAccessibilityPropertySetCheckable002
 * @tc.desc: Test default value of GetCheckable is false
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityFrameNodeUtilsTestThree, CustomAccessibilityPropertySetCheckable002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create CustomAccessibilityProperty without setting checkable
     * @tc.expected: GetCheckable returns false (default)
     */
    auto prop = AceType::MakeRefPtr<CustomAccessibilityProperty>();
    ASSERT_NE(prop, nullptr);
    EXPECT_FALSE(prop->GetCheckable());
}

// ==================== CustomAccessibilityProperty SetChecked/GetChecked ====================

/**
 * @tc.name: CustomAccessibilityPropertySetChecked001
 * @tc.desc: Test SetChecked and GetChecked
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityFrameNodeUtilsTestThree, CustomAccessibilityPropertySetChecked001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create CustomAccessibilityProperty and set checked to true
     * @tc.expected: GetChecked returns true
     */
    auto prop = AceType::MakeRefPtr<CustomAccessibilityProperty>();
    ASSERT_NE(prop, nullptr);
    prop->SetChecked(true);
    EXPECT_TRUE(prop->GetChecked());
}

// ==================== CustomAccessibilityProperty SetEnabled/GetEnabled ====================

/**
 * @tc.name: CustomAccessibilityPropertySetEnabled001
 * @tc.desc: Test SetEnabled and GetEnabled
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityFrameNodeUtilsTestThree, CustomAccessibilityPropertySetEnabled001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create CustomAccessibilityProperty and set enabled to false
     * @tc.expected: GetEnabled returns false
     */
    auto prop = AceType::MakeRefPtr<CustomAccessibilityProperty>();
    ASSERT_NE(prop, nullptr);
    prop->SetEnabled(false);
    EXPECT_FALSE(prop->GetEnabled());
}

/**
 * @tc.name: CustomAccessibilityPropertySetEnabled002
 * @tc.desc: Test default value of GetEnabled is true
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityFrameNodeUtilsTestThree, CustomAccessibilityPropertySetEnabled002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create CustomAccessibilityProperty without setting enabled
     * @tc.expected: GetEnabled returns true (default)
     */
    auto prop = AceType::MakeRefPtr<CustomAccessibilityProperty>();
    ASSERT_NE(prop, nullptr);
    EXPECT_TRUE(prop->GetEnabled());
}

// ==================== CustomAccessibilityProperty SetSelected/GetSelected ====================

/**
 * @tc.name: CustomAccessibilityPropertySetSelected001
 * @tc.desc: Test SetSelected and GetSelected
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityFrameNodeUtilsTestThree, CustomAccessibilityPropertySetSelected001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create CustomAccessibilityProperty and set selected to true
     * @tc.expected: GetSelected returns true
     */
    auto prop = AceType::MakeRefPtr<CustomAccessibilityProperty>();
    ASSERT_NE(prop, nullptr);
    prop->SetSelected(true);
    EXPECT_TRUE(prop->GetSelected());
}

/**
 * @tc.name: CustomAccessibilityPropertySetSelected002
 * @tc.desc: Test default value of GetSelected is false
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityFrameNodeUtilsTestThree, CustomAccessibilityPropertySetSelected002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create CustomAccessibilityProperty without setting selected
     * @tc.expected: GetSelected returns false (default)
     */
    auto prop = AceType::MakeRefPtr<CustomAccessibilityProperty>();
    ASSERT_NE(prop, nullptr);
    EXPECT_FALSE(prop->GetSelected());
}

// ==================== AccessibilityProperty CreateCustomAccessibilityProperty ====================

/**
 * @tc.name: CreateCustomAccessibilityPropertyTest001
 * @tc.desc: Test CreateCustomAccessibilityProperty creates a non-null instance
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityFrameNodeUtilsTestThree, CreateCustomAccessibilityPropertyTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create AccessibilityProperty and call CreateCustomAccessibilityProperty
     * @tc.expected: returns non-null CustomAccessibilityProperty
     */
    auto frameNode = FrameNode::CreateFrameNode(TEST_TAG_CUSTOM,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>(), true);
    ASSERT_NE(frameNode, nullptr);
    auto accessibilityProperty = frameNode->GetAccessibilityProperty<AccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    auto customProp = accessibilityProperty->CreateCustomAccessibilityProperty();
    ASSERT_NE(customProp, nullptr);
}

// ==================== AccessibilityProperty Get/SetCustomAccessibilityProperty ====================

/**
 * @tc.name: AccessibilityPropertyGetCustomAccessibilityProperty001
 * @tc.desc: Test GetCustomAccessibilityProperty returns nullptr initially
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityFrameNodeUtilsTestThree, AccessibilityPropertyGetCustomAccessibilityProperty001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create AccessibilityProperty and get custom property without setting
     * @tc.expected: returns nullptr
     */
    auto frameNode = FrameNode::CreateFrameNode(TEST_TAG_CUSTOM,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>(), true);
    ASSERT_NE(frameNode, nullptr);
    auto accessibilityProperty = frameNode->GetAccessibilityProperty<AccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    auto result = accessibilityProperty->GetCustomAccessibilityProperty();
    EXPECT_EQ(result, nullptr);
}

/**
 * @tc.name: AccessibilityPropertySetCustomAccessibilityProperty001
 * @tc.desc: Test SetCustomAccessibilityProperty and GetCustomAccessibilityProperty round trip
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityFrameNodeUtilsTestThree, AccessibilityPropertySetCustomAccessibilityProperty001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create AccessibilityProperty, create CustomAccessibilityProperty, set and get
     * @tc.expected: returns the same instance that was set
     */
    auto frameNode = FrameNode::CreateFrameNode(TEST_TAG_CUSTOM,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>(), true);
    ASSERT_NE(frameNode, nullptr);
    auto accessibilityProperty = frameNode->GetAccessibilityProperty<AccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    auto customProp = AceType::MakeRefPtr<CustomAccessibilityProperty>();
    ASSERT_NE(customProp, nullptr);
    customProp->SetAccessibilityText("hello");
    accessibilityProperty->SetCustomAccessibilityProperty(customProp);
    auto result = accessibilityProperty->GetCustomAccessibilityProperty();
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->GetAccessibilityText(), "hello");
}

// ==================== AccessibilityProperty Set/Get/HasVirtualNodeTreeRoot ====================

/**
 * @tc.name: AccessibilityPropertyHasVirtualNodeTreeRoot001
 * @tc.desc: Test HasVirtualNodeTreeRoot returns false initially
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityFrameNodeUtilsTestThree, AccessibilityPropertyHasVirtualNodeTreeRoot001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create AccessibilityProperty and check HasVirtualNodeTreeRoot
     * @tc.expected: returns false since no root is set
     */
    auto frameNode = FrameNode::CreateFrameNode(TEST_TAG_CUSTOM,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>(), true);
    ASSERT_NE(frameNode, nullptr);
    auto accessibilityProperty = frameNode->GetAccessibilityProperty<AccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    EXPECT_FALSE(accessibilityProperty->HasVirtualNodeTreeRoot());
    EXPECT_EQ(accessibilityProperty->GetVirtualNodeTreeRoot(), nullptr);
}

/**
 * @tc.name: AccessibilityPropertySetVirtualNodeTreeRoot001
 * @tc.desc: Test SetVirtualNodeTreeRoot and GetVirtualNodeTreeRoot
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityFrameNodeUtilsTestThree, AccessibilityPropertySetVirtualNodeTreeRoot001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create AccessibilityProperty, set virtual node tree root, verify get/has
     * @tc.expected: HasVirtualNodeTreeRoot returns true and GetVirtualNodeTreeRoot returns the set instance
     */
    auto frameNode = FrameNode::CreateFrameNode(TEST_TAG_CUSTOM,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>(), true);
    ASSERT_NE(frameNode, nullptr);
    auto accessibilityProperty = frameNode->GetAccessibilityProperty<AccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    auto customProp = AceType::MakeRefPtr<CustomAccessibilityProperty>();
    ASSERT_NE(customProp, nullptr);
    accessibilityProperty->SetVirtualNodeTreeRoot(customProp);
    EXPECT_TRUE(accessibilityProperty->HasVirtualNodeTreeRoot());
    auto root = accessibilityProperty->GetVirtualNodeTreeRoot();
    ASSERT_NE(root, nullptr);
}

} // namespace OHOS::Ace::NG
