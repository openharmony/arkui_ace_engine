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

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_abstract_model_ng.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/property/accessibility_property.h"
#include "interfaces/native/native_node.h"
#include "interfaces/native/native_type.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t NODE_ID = 100;
const std::string NODE_TAG = "text";
} // namespace

class AccessibilityNextFocusAttrTestNg : public testing::Test {
public:
    static void SetUpTestCase()
    {
        auto pattern = AceType::MakeRefPtr<TextPattern>();
        frameNode_ = FrameNode::CreateFrameNode(NODE_TAG, NODE_ID, pattern);
        ASSERT_NE(frameNode_, nullptr);
    }

    static void TearDownTestCase()
    {
        frameNode_ = nullptr;
    }

    void SetUp() override {}
    void TearDown() override {}

protected:
    static RefPtr<FrameNode> frameNode_;
};

RefPtr<FrameNode> AccessibilityNextFocusAttrTestNg::frameNode_ = nullptr;

/**
 * @tc.name: AccessibilityNextFocusAttrTest001
 * @tc.desc: Test ArkUI_AccessibilityDefaultFocus enum values
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityNextFocusAttrTestNg, AccessibilityNextFocusAttrTest001, TestSize.Level1)
{
    // Verify DISABLED is 0
    EXPECT_EQ(ARKUI_ACCESSIBILITY_DEFAULT_FOCUS_DISABLED, 0);
    // Verify ENABLED is 1
    EXPECT_EQ(ARKUI_ACCESSIBILITY_DEFAULT_FOCUS_ENABLED, 1);
    // Verify DISABLED and ENABLED are consecutive
    EXPECT_EQ(ARKUI_ACCESSIBILITY_DEFAULT_FOCUS_ENABLED, ARKUI_ACCESSIBILITY_DEFAULT_FOCUS_DISABLED + 1);
}

/**
 * @tc.name: AccessibilityNextFocusAttrTest002
 * @tc.desc: Test NODE_ACCESSIBILITY_NEXT_FOCUS_ID and NODE_ACCESSIBILITY_DEFAULT_FOCUS enum values
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityNextFocusAttrTestNg, AccessibilityNextFocusAttrTest002, TestSize.Level1)
{
    EXPECT_EQ(NODE_ACCESSIBILITY_NEXT_FOCUS_ID, 124);
    EXPECT_EQ(NODE_ACCESSIBILITY_DEFAULT_FOCUS, 125);
    // Verify they are consecutive after NODE_BORDER_RADIUS_TYPE
    EXPECT_EQ(NODE_BORDER_RADIUS_TYPE, 123);
}

/**
 * @tc.name: AccessibilityNextFocusAttrTest003
 * @tc.desc: Test SetAccessibilityNextFocusId with valid string via ViewAbstractModelNG static method
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityNextFocusAttrTestNg, AccessibilityNextFocusAttrTest003, TestSize.Level1)
{
    ASSERT_NE(frameNode_, nullptr);
    auto accessibilityProperty = frameNode_->GetAccessibilityProperty<AccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);

    // Verify default value is empty string
    EXPECT_EQ(accessibilityProperty->GetAccessibilityNextFocusInspectorKey(), "");

    // Set valid focus ID
    ViewAbstractModelNG::SetAccessibilityNextFocusId(frameNode_.GetRawPtr(), "focusId1");
    EXPECT_EQ(accessibilityProperty->GetAccessibilityNextFocusInspectorKey(), "focusId1");

    // Set another valid focus ID (overwrite)
    ViewAbstractModelNG::SetAccessibilityNextFocusId(frameNode_.GetRawPtr(), "focusId2");
    EXPECT_EQ(accessibilityProperty->GetAccessibilityNextFocusInspectorKey(), "focusId2");

    // Reset to empty string
    ViewAbstractModelNG::SetAccessibilityNextFocusId(frameNode_.GetRawPtr(), "");
    EXPECT_EQ(accessibilityProperty->GetAccessibilityNextFocusInspectorKey(), "");
}

/**
 * @tc.name: AccessibilityNextFocusAttrTest004
 * @tc.desc: Test SetAccessibilityNextFocusId with nullptr frameNode does not crash
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityNextFocusAttrTestNg, AccessibilityNextFocusAttrTest004, TestSize.Level1)
{
    // Should not crash when frameNode is nullptr
    ViewAbstractModelNG::SetAccessibilityNextFocusId(nullptr, "focusId");
    // Verify frameNode_ is still valid and unaffected
    ASSERT_NE(frameNode_, nullptr);
    auto accessibilityProperty = frameNode_->GetAccessibilityProperty<AccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    EXPECT_EQ(accessibilityProperty->GetAccessibilityNextFocusInspectorKey(), "");
}

/**
 * @tc.name: AccessibilityNextFocusAttrTest005
 * @tc.desc: Test SetAccessibilityDefaultFocus with nullptr frameNode does not crash
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityNextFocusAttrTestNg, AccessibilityNextFocusAttrTest005, TestSize.Level1)
{
    // Should not crash when frameNode is nullptr
    ViewAbstractModelNG::SetAccessibilityDefaultFocus(nullptr, true);
    ViewAbstractModelNG::SetAccessibilityDefaultFocus(nullptr, false);
    // Verify frameNode_ is still valid and unaffected
    ASSERT_NE(frameNode_, nullptr);
    auto accessibilityProperty = frameNode_->GetAccessibilityProperty<AccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    EXPECT_EQ(accessibilityProperty->GetAccessibilityNextFocusInspectorKey(), "");
}

/**
 * @tc.name: AccessibilityNextFocusAttrTest006
 * @tc.desc: Test SetAccessibilityNextFocusId with empty string via ViewAbstractModelNG static method
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityNextFocusAttrTestNg, AccessibilityNextFocusAttrTest006, TestSize.Level1)
{
    ASSERT_NE(frameNode_, nullptr);
    auto accessibilityProperty = frameNode_->GetAccessibilityProperty<AccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);

    // Set empty string explicitly
    ViewAbstractModelNG::SetAccessibilityNextFocusId(frameNode_.GetRawPtr(), "");
    EXPECT_EQ(accessibilityProperty->GetAccessibilityNextFocusInspectorKey(), "");

    // Set then reset by setting empty string
    ViewAbstractModelNG::SetAccessibilityNextFocusId(frameNode_.GetRawPtr(), "tempFocus");
    EXPECT_EQ(accessibilityProperty->GetAccessibilityNextFocusInspectorKey(), "tempFocus");
    ViewAbstractModelNG::SetAccessibilityNextFocusId(frameNode_.GetRawPtr(), "");
    EXPECT_EQ(accessibilityProperty->GetAccessibilityNextFocusInspectorKey(), "");
}

/**
 * @tc.name: AccessibilityNextFocusAttrTest007
 * @tc.desc: Test SetAccessibilityNextFocusId with long string value
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityNextFocusAttrTestNg, AccessibilityNextFocusAttrTest007, TestSize.Level1)
{
    ASSERT_NE(frameNode_, nullptr);
    auto accessibilityProperty = frameNode_->GetAccessibilityProperty<AccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);

    // Set a long focus ID string
    std::string longFocusId(256, 'a');
    ViewAbstractModelNG::SetAccessibilityNextFocusId(frameNode_.GetRawPtr(), longFocusId);
    EXPECT_EQ(accessibilityProperty->GetAccessibilityNextFocusInspectorKey(), longFocusId);

    // Verify it can be overwritten with a short string
    ViewAbstractModelNG::SetAccessibilityNextFocusId(frameNode_.GetRawPtr(), "short");
    EXPECT_EQ(accessibilityProperty->GetAccessibilityNextFocusInspectorKey(), "short");
}

/**
 * @tc.name: AccessibilityNextFocusAttrTest008
 * @tc.desc: Test SetAccessibilityNextFocusId idempotency - setting same value multiple times
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityNextFocusAttrTestNg, AccessibilityNextFocusAttrTest008, TestSize.Level1)
{
    ASSERT_NE(frameNode_, nullptr);
    auto accessibilityProperty = frameNode_->GetAccessibilityProperty<AccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);

    const std::string sameFocusId = "sameId";
    ViewAbstractModelNG::SetAccessibilityNextFocusId(frameNode_.GetRawPtr(), sameFocusId);
    ViewAbstractModelNG::SetAccessibilityNextFocusId(frameNode_.GetRawPtr(), sameFocusId);
    ViewAbstractModelNG::SetAccessibilityNextFocusId(frameNode_.GetRawPtr(), sameFocusId);
    // Value should remain unchanged
    EXPECT_EQ(accessibilityProperty->GetAccessibilityNextFocusInspectorKey(), sameFocusId);
}

/**
 * @tc.name: AccessibilityNextFocusAttrTest009
 * @tc.desc: Test SetAccessibilityNextFocusId then SetAccessibilityDefaultFocus does not affect each other
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityNextFocusAttrTestNg, AccessibilityNextFocusAttrTest009, TestSize.Level1)
{
    ASSERT_NE(frameNode_, nullptr);
    auto accessibilityProperty = frameNode_->GetAccessibilityProperty<AccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);

    // Set accessibility next focus ID
    ViewAbstractModelNG::SetAccessibilityNextFocusId(frameNode_.GetRawPtr(), "focusId");
    EXPECT_EQ(accessibilityProperty->GetAccessibilityNextFocusInspectorKey(), "focusId");

    // SetAccessibilityDefaultFocus with nullptr frameNode should not affect next focus ID
    ViewAbstractModelNG::SetAccessibilityDefaultFocus(nullptr, true);
    EXPECT_EQ(accessibilityProperty->GetAccessibilityNextFocusInspectorKey(), "focusId");
}
} // namespace OHOS::Ace::NG
