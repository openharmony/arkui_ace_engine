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

/**
 * @tc.name: AccessibilityNextFocusAttrTest011
 * @tc.desc: Test SetAccessibilityNextFocusParams with descendantMode = false preserves the value
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityNextFocusAttrTestNg, AccessibilityNextFocusAttrTest011, TestSize.Level1)
{
    ASSERT_NE(frameNode_, nullptr);
    auto accessibilityProperty = frameNode_->GetAccessibilityProperty<AccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);

    // Set params with descendantMode = false
    AccessibilityNextFocusParams params;
    params.nextFocusInspectorKey = "directTarget";
    params.descendantMode = false;
    ViewAbstractModelNG::SetAccessibilityNextFocusParams(frameNode_.GetRawPtr(), params);

    EXPECT_TRUE(accessibilityProperty->HasAccessibilityNextFocusParams());
    auto resultParams = accessibilityProperty->GetAccessibilityNextFocusParams();
    EXPECT_EQ(resultParams.nextFocusInspectorKey, "directTarget");
    EXPECT_FALSE(resultParams.descendantMode);
}

/**
 * @tc.name: AccessibilityNextFocusAttrTest012
 * @tc.desc: Test ResetAccessibilityNextFocusParams clears the optional and restores defaults
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityNextFocusAttrTestNg, AccessibilityNextFocusAttrTest012, TestSize.Level1)
{
    ASSERT_NE(frameNode_, nullptr);
    auto accessibilityProperty = frameNode_->GetAccessibilityProperty<AccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);

    // Set params first
    AccessibilityNextFocusParams params;
    params.nextFocusInspectorKey = "toBeReset";
    params.descendantMode = true;
    ViewAbstractModelNG::SetAccessibilityNextFocusParams(frameNode_.GetRawPtr(), params);
    EXPECT_TRUE(accessibilityProperty->HasAccessibilityNextFocusParams());

    // Reset params
    accessibilityProperty->ResetAccessibilityNextFocusParams();
    EXPECT_FALSE(accessibilityProperty->HasAccessibilityNextFocusParams());

    // GetAccessibilityNextFocusParams should return default-constructed value
    auto defaultParams = accessibilityProperty->GetAccessibilityNextFocusParams();
    EXPECT_EQ(defaultParams.nextFocusInspectorKey, "");
    EXPECT_FALSE(defaultParams.descendantMode);
}

/**
 * @tc.name: AccessibilityNextFocusAttrTest013
 * @tc.desc: Test SetAccessibilityNextFocusParams with nullptr frameNode does not crash
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityNextFocusAttrTestNg, AccessibilityNextFocusAttrTest013, TestSize.Level1)
{
    // Should not crash when frameNode is nullptr
    AccessibilityNextFocusParams params;
    params.nextFocusInspectorKey = "safeId";
    params.descendantMode = true;
    ViewAbstractModelNG::SetAccessibilityNextFocusParams(nullptr, params);

    // Verify frameNode_ is still valid and unaffected
    ASSERT_NE(frameNode_, nullptr);
    auto accessibilityProperty = frameNode_->GetAccessibilityProperty<AccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    EXPECT_FALSE(accessibilityProperty->HasAccessibilityNextFocusParams());
}

/**
 * @tc.name: AccessibilityNextFocusAttrTest014
 * @tc.desc: Test SetAccessibilityNextFocusParams overwrites previous params completely
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityNextFocusAttrTestNg, AccessibilityNextFocusAttrTest014, TestSize.Level1)
{
    ASSERT_NE(frameNode_, nullptr);
    auto accessibilityProperty = frameNode_->GetAccessibilityProperty<AccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);

    // Set first params
    AccessibilityNextFocusParams params1;
    params1.nextFocusInspectorKey = "firstTarget";
    params1.descendantMode = false;
    ViewAbstractModelNG::SetAccessibilityNextFocusParams(frameNode_.GetRawPtr(), params1);

    // Overwrite with second params
    AccessibilityNextFocusParams params2;
    params2.nextFocusInspectorKey = "secondTarget";
    params2.descendantMode = true;
    ViewAbstractModelNG::SetAccessibilityNextFocusParams(frameNode_.GetRawPtr(), params2);

    auto resultParams = accessibilityProperty->GetAccessibilityNextFocusParams();
    EXPECT_EQ(resultParams.nextFocusInspectorKey, "secondTarget");
    EXPECT_TRUE(resultParams.descendantMode);
}

/**
 * @tc.name: AccessibilityNextFocusAttrTest015
 * @tc.desc: Test SetAccessibilityNextFocusId then SetAccessibilityNextFocusParams interaction
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityNextFocusAttrTestNg, AccessibilityNextFocusAttrTest015, TestSize.Level1)
{
    ASSERT_NE(frameNode_, nullptr);
    auto accessibilityProperty = frameNode_->GetAccessibilityProperty<AccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);

    // Set next focus ID first via SetAccessibilityNextFocusId
    ViewAbstractModelNG::SetAccessibilityNextFocusId(frameNode_.GetRawPtr(), "initialId");
    EXPECT_EQ(accessibilityProperty->GetAccessibilityNextFocusInspectorKey(), "initialId");
    // SetAccessibilityNextFocusId creates the optional internally
    EXPECT_TRUE(accessibilityProperty->HasAccessibilityNextFocusParams());

    // Now set full params with descendantMode - this should overwrite the entire params
    AccessibilityNextFocusParams params;
    params.nextFocusInspectorKey = "updatedId";
    params.descendantMode = true;
    ViewAbstractModelNG::SetAccessibilityNextFocusParams(frameNode_.GetRawPtr(), params);

    auto resultParams = accessibilityProperty->GetAccessibilityNextFocusParams();
    EXPECT_EQ(resultParams.nextFocusInspectorKey, "updatedId");
    EXPECT_TRUE(resultParams.descendantMode);
}

/**
 * @tc.name: AccessibilityNextFocusAttrTest016
 * @tc.desc: Test SetAccessibilityNextFocusParams after reset restores ability to set new params
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityNextFocusAttrTestNg, AccessibilityNextFocusAttrTest016, TestSize.Level1)
{
    ASSERT_NE(frameNode_, nullptr);
    auto accessibilityProperty = frameNode_->GetAccessibilityProperty<AccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);

    // Set and reset
    AccessibilityNextFocusParams params1;
    params1.nextFocusInspectorKey = "oldId";
    params1.descendantMode = true;
    ViewAbstractModelNG::SetAccessibilityNextFocusParams(frameNode_.GetRawPtr(), params1);
    accessibilityProperty->ResetAccessibilityNextFocusParams();
    EXPECT_FALSE(accessibilityProperty->HasAccessibilityNextFocusParams());

    // Set new params after reset
    AccessibilityNextFocusParams params2;
    params2.nextFocusInspectorKey = "newId";
    params2.descendantMode = false;
    ViewAbstractModelNG::SetAccessibilityNextFocusParams(frameNode_.GetRawPtr(), params2);

    EXPECT_TRUE(accessibilityProperty->HasAccessibilityNextFocusParams());
    auto resultParams = accessibilityProperty->GetAccessibilityNextFocusParams();
    EXPECT_EQ(resultParams.nextFocusInspectorKey, "newId");
    EXPECT_FALSE(resultParams.descendantMode);
}

/**
 * @tc.name: AccessibilityNextFocusAttrTest017
 * @tc.desc: Test SetAccessibilityNextFocusParams with empty nextFocusInspectorKey and descendantMode
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityNextFocusAttrTestNg, AccessibilityNextFocusAttrTest017, TestSize.Level1)
{
    ASSERT_NE(frameNode_, nullptr);
    auto accessibilityProperty = frameNode_->GetAccessibilityProperty<AccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);

    // Set params with empty key but descendantMode enabled
    AccessibilityNextFocusParams params;
    params.nextFocusInspectorKey = "";
    params.descendantMode = true;
    ViewAbstractModelNG::SetAccessibilityNextFocusParams(frameNode_.GetRawPtr(), params);

    EXPECT_TRUE(accessibilityProperty->HasAccessibilityNextFocusParams());
    auto resultParams = accessibilityProperty->GetAccessibilityNextFocusParams();
    EXPECT_EQ(resultParams.nextFocusInspectorKey, "");
    EXPECT_TRUE(resultParams.descendantMode);
}

/**
 * @tc.name: AccessibilityNextFocusAttrTest018
 * @tc.desc: Test SetAccessibilityNextFocusParams idempotency - setting same params multiple times
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityNextFocusAttrTestNg, AccessibilityNextFocusAttrTest018, TestSize.Level1)
{
    ASSERT_NE(frameNode_, nullptr);
    auto accessibilityProperty = frameNode_->GetAccessibilityProperty<AccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);

    const std::string focusKey = "stableKey";
    AccessibilityNextFocusParams params;
    params.nextFocusInspectorKey = focusKey;
    params.descendantMode = true;

    // Set same params three times
    ViewAbstractModelNG::SetAccessibilityNextFocusParams(frameNode_.GetRawPtr(), params);
    ViewAbstractModelNG::SetAccessibilityNextFocusParams(frameNode_.GetRawPtr(), params);
    ViewAbstractModelNG::SetAccessibilityNextFocusParams(frameNode_.GetRawPtr(), params);

    auto resultParams = accessibilityProperty->GetAccessibilityNextFocusParams();
    EXPECT_EQ(resultParams.nextFocusInspectorKey, focusKey);
    EXPECT_TRUE(resultParams.descendantMode);
}

/**
 * @tc.name: AccessibilityNextFocusAttrTest020
 * @tc.desc: Test AccessibilityNextFocusParams default field values
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityNextFocusAttrTestNg, AccessibilityNextFocusAttrTest020, TestSize.Level1)
{
    // Verify default-constructed AccessibilityNextFocusParams has expected defaults
    AccessibilityNextFocusParams defaultParams;
    EXPECT_EQ(defaultParams.nextFocusInspectorKey, "");
    EXPECT_FALSE(defaultParams.descendantMode);
}

} // namespace OHOS::Ace::NG
