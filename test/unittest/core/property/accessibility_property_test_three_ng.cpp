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

#include <string>

#include "gtest/gtest.h"

#define private public
#define protected public
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/event/long_press_event.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/linear_layout/column_model.h"
#include "core/components_ng/pattern/linear_layout/column_model_ng.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/text/span_node.h"
#include "core/components_ng/property/accessibility_property.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/components_ng/base/view_abstract_model_ng.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
class MockPattern : public Pattern {
public:
    MockPattern() = default;
    ~MockPattern() override = default;
};
class AccessibilityPropertyTestThreeNg : public testing::Test {
public:
    static void SetUpTestCase() {};
    static void TearDownTestCase() {};
};

/**
 * @tc.name: AccessibilityPropertyTest001
 * @tc.desc: Test the method IsTagInSubTreeComponent.
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityPropertyTestThreeNg, AccessibilityPropertyTestThree001, TestSize.Level1)
{
    std::string tag = V2::XCOMPONENT_ETS_TAG;
    AccessibilityProperty accessibilityProperty;

    bool ret = accessibilityProperty.IsTagInSubTreeComponent(tag);
    EXPECT_TRUE(ret);
}

/**
 * @tc.name: AccessibilityPropertyTest002
 * @tc.desc: Test the method IsTagInSubTreeComponent.
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityPropertyTestThreeNg, AccessibilityPropertyTestThree002, TestSize.Level1)
{
    std::string tag = V2::CHECKBOX_ETS_TAG;
    AccessibilityProperty accessibilityProperty;

    bool ret = accessibilityProperty.IsAccessibilityFocusableTag(tag);
    EXPECT_TRUE(ret);

    tag = "test";
    ret = accessibilityProperty.IsAccessibilityFocusableTag(tag);
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: AccessibilityPropertyTest003
 * @tc.desc: Test the method IsAccessibilityFocusableTag.
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityPropertyTestThreeNg, AccessibilityPropertyTestThree003, TestSize.Level1)
{
    std::string tag = V2::CHECKBOX_ETS_TAG;
    AccessibilityProperty accessibilityProperty;

    bool ret = accessibilityProperty.IsAccessibilityFocusableTag(tag);
    EXPECT_TRUE(ret);

    tag = "test";
    ret = accessibilityProperty.IsAccessibilityFocusableTag(tag);
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: AccessibilityPropertyTest004
 * @tc.desc: Test the method SetAccessibilityNextFocusInspectorKey && SetAccessibilityTextWithEvent
 *           && SetAccessibilityDescriptionWithEvent.
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityPropertyTestThreeNg, AccessibilityPropertyTestThree004, TestSize.Level1)
{
    std::string accessibilityNextFocusInspectorKey = "test";
    AccessibilityProperty accessibilityProperty;

    accessibilityProperty.SetAccessibilityNextFocusInspectorKey(accessibilityNextFocusInspectorKey);
    EXPECT_EQ(accessibilityNextFocusInspectorKey, accessibilityProperty.accessibilityNextFocusInspectorKey_);

    accessibilityNextFocusInspectorKey = "";
    accessibilityProperty.SetAccessibilityNextFocusInspectorKey(accessibilityNextFocusInspectorKey);
    EXPECT_EQ(accessibilityNextFocusInspectorKey,
        accessibilityProperty.accessibilityNextFocusInspectorKey_.value_or(""));

    std::string text = "test";
    accessibilityProperty.SetAccessibilityTextWithEvent(text);
    EXPECT_EQ(text, accessibilityProperty.accessibilityText_);

    text = "";
    accessibilityProperty.SetAccessibilityTextWithEvent(text);
    EXPECT_EQ(text, accessibilityProperty.accessibilityText_.value_or(""));

    std::string accessibilityDescription = "";
    accessibilityProperty.SetAccessibilityDescriptionWithEvent(accessibilityDescription);
    EXPECT_EQ(accessibilityDescription, accessibilityProperty.accessibilityDescription_.value_or(""));
}

/**
 * @tc.name: AccessibilityPropertyTest005
 * @tc.desc: Test the method ActActionClick.
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityPropertyTestThreeNg, AccessibilityPropertyTestThree005, TestSize.Level1)
{
    AccessibilityProperty accessibilityProperty;

    uint32_t action = 1;
    accessibilityProperty.accessibilityActions_ = 1;
    accessibilityProperty.actionsImpl_ = [](uint32_t type){};
    bool actionsDefined = accessibilityProperty.ActionsDefined(action);
    EXPECT_TRUE(actionsDefined);
    actionsDefined = accessibilityProperty.ActionsDefined(static_cast<uint32_t>(ARKUI_ACCESSIBILITY_ACTION_CLICK));
    EXPECT_TRUE(actionsDefined);
    auto result = accessibilityProperty.ActActionClick();
    EXPECT_TRUE(result);

    action = 0;
    accessibilityProperty.accessibilityActions_ = 0;
    accessibilityProperty.actionClickImpl_ = nullptr;
    result = accessibilityProperty.ActActionClick();
    EXPECT_FALSE(result);
}

/**
 * @tc.name: AccessibilityPropertyTest006
 * @tc.desc: Test the method ActActionLongClick.
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityPropertyTestThreeNg, AccessibilityPropertyTestThree006, TestSize.Level1)
{
    AccessibilityProperty accessibilityProperty;

    uint32_t action = 2;
    accessibilityProperty.accessibilityActions_ = 2;
    accessibilityProperty.actionsImpl_ = [](uint32_t type){};
    bool actionsDefined = accessibilityProperty.ActionsDefined(action);
    EXPECT_TRUE(actionsDefined);
    actionsDefined = accessibilityProperty.ActionsDefined(static_cast<uint32_t>(ARKUI_ACCESSIBILITY_ACTION_LONG_CLICK));
    EXPECT_TRUE(actionsDefined);
    auto result = accessibilityProperty.ActActionLongClick();
    EXPECT_TRUE(result);

    action = 0;
    accessibilityProperty.accessibilityActions_ = 0;
    accessibilityProperty.actionClickImpl_ = nullptr;
    result = accessibilityProperty.ActActionLongClick();
    EXPECT_FALSE(result);
}

/**
 * @tc.name: AccessibilityPropertyTest007
 * @tc.desc: Test the method ActActionPaste.
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityPropertyTestThreeNg, AccessibilityPropertyTestThree007, TestSize.Level1)
{
    AccessibilityProperty accessibilityProperty;

    uint32_t action = 16;
    accessibilityProperty.accessibilityActions_ = 16;
    accessibilityProperty.actionsImpl_ = [](uint32_t type){};
    bool actionsDefined = accessibilityProperty.ActionsDefined(action);
    EXPECT_TRUE(actionsDefined);
    actionsDefined = accessibilityProperty.ActionsDefined(static_cast<uint32_t>(ARKUI_ACCESSIBILITY_ACTION_PASTE));
    EXPECT_TRUE(actionsDefined);
    auto result = accessibilityProperty.ActActionPaste();
    EXPECT_TRUE(result);
}

/**
 * @tc.name: AccessibilityPropertyTest008
 * @tc.desc: Test the method ActActionCut.
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityPropertyTestThreeNg, AccessibilityPropertyTestThree008, TestSize.Level1)
{
    AccessibilityProperty accessibilityProperty;

    uint32_t action = 4;
    accessibilityProperty.accessibilityActions_ = 4;
    accessibilityProperty.actionsImpl_ = [](uint32_t type){};
    bool actionsDefined = accessibilityProperty.ActionsDefined(action);
    EXPECT_TRUE(actionsDefined);
    actionsDefined = accessibilityProperty.ActionsDefined(static_cast<uint32_t>(ARKUI_ACCESSIBILITY_ACTION_CUT));
    EXPECT_TRUE(actionsDefined);
    auto result = accessibilityProperty.ActActionCut();
    EXPECT_TRUE(result);
}

/**
 * @tc.name: AccessibilityPropertyTest009
 * @tc.desc: Test the method ActActionCopy.
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityPropertyTestThreeNg, AccessibilityPropertyTestThree009, TestSize.Level1)
{
    AccessibilityProperty accessibilityProperty;

    uint32_t action = 8;
    accessibilityProperty.accessibilityActions_ = 8;
    accessibilityProperty.actionsImpl_ = [](uint32_t type){};
    bool actionsDefined = accessibilityProperty.ActionsDefined(action);
    EXPECT_TRUE(actionsDefined);
    actionsDefined = accessibilityProperty.ActionsDefined(static_cast<uint32_t>(ARKUI_ACCESSIBILITY_ACTION_COPY));
    EXPECT_TRUE(actionsDefined);
    auto result = accessibilityProperty.ActActionCopy();
    EXPECT_TRUE(result);
}

/**
 * @tc.name: AccessibilityPropertyTest010
 * @tc.desc: Test the method UpdateHoverTestRect.
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityPropertyTestThreeNg, AccessibilityPropertyTestThree010, TestSize.Level1)
{
    AccessibilityProperty accessibilityProperty;
    RectF origRect;
    auto node = FrameNode::GetOrCreateFrameNode(
        V2::BUTTON_ETS_TAG, 1, []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    auto ret = accessibilityProperty.UpdateHoverTestRect(node);
    EXPECT_EQ(origRect, ret);
}

/**
 * @tc.name: AccessibilityPropertyTest011
 * @tc.desc: Test the method HoverTestRecursive.
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityPropertyTestThreeNg, AccessibilityPropertyTestThree011, TestSize.Level1)
{
    AccessibilityProperty accessibilityProperty;
    PointF parentPoint(1, 1);
    auto node = FrameNode::GetOrCreateFrameNode(
        V2::BUTTON_ETS_TAG, 1, []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    AccessibilityHoverTestPath path;
    std::unique_ptr<AccessibilityProperty::HoverTestDebugTraceInfo> debugInfo = nullptr;
    bool ancestorGroupFlag;

    node->SetAccessibilityNodeVirtual();
    EXPECT_TRUE(node->IsAccessibilityVirtualNode());
    debugInfo = std::make_unique<AccessibilityProperty::HoverTestDebugTraceInfo>();

    bool ret = accessibilityProperty.HoverTestRecursive(parentPoint, node, path, debugInfo, ancestorGroupFlag);
    EXPECT_FALSE(ret);

    node->isActive_ = true;
    ret = accessibilityProperty.HoverTestRecursive(parentPoint, node, path, debugInfo, ancestorGroupFlag);
    EXPECT_FALSE(ret);
}
} // namespace OHOS::Ace::NG
