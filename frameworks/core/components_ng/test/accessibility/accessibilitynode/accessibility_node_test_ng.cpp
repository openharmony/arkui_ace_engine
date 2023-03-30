/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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
#include "frameworks/core/accessibility/accessibility_manager.h"
#include "frameworks/core/accessibility/accessibility_node.h"
#include "frameworks/core/accessibility/accessibility_utils.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
const double TEST_NUMBER = 10.0;
const char VALUE[] = "value";
const char TYPE[] = "type";
const char DISABLED[] = "disabled";
const char GROUP[] = "accessibilitygroup";
const char TEXT[] = "accessibilitytext";
const char DESCRIPTION[] = "accessibilitydescription";
const char IMPORTANCE[] = "accessibilityimportance";
const char SHOW[] = "show";
const char ID[] = "id";
const char EVENT[] = "accessibility";
const char CLICK[] = "click";
const char LONG_PRESS[] = "longpress";
const char FOCUS[] = "focus";
const char BLUR[] = "blur";
} // namespace

class AccessibilityNodeTestNg : public testing::Test {
public:
    static void SetUpTestCase() {};
    static void TearDownTestCase() {};
};

/**
 * @tc.name: accessibilityNodeTest001
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityNodeTestNg, accessibilityNodeTest001, TestSize.Level1)
{
    NodeId id = 0;
    std::string nodeName = "accessibilityNodeTest";
    AccessibilityNode accessibilityNode(id, nodeName);
    EXPECT_FALSE(accessibilityNode.ActionClick());
    ActionClickImpl actionClickImpl = []() {};
    accessibilityNode.SetActionClickImpl(actionClickImpl);
    EXPECT_TRUE(accessibilityNode.ActionClick());

    EXPECT_FALSE(accessibilityNode.ActionLongClick());
    ActionLongClickImpl actionLongClickImpl = []() {};
    accessibilityNode.SetActionLongClickImpl(actionLongClickImpl);
    EXPECT_TRUE(accessibilityNode.ActionLongClick());

    EXPECT_FALSE(accessibilityNode.ActionSetText(nodeName));
    ActionSetTextImpl actionSetTextImpl = [](const std::string& text) {};
    accessibilityNode.SetActionSetTextImpl(actionSetTextImpl);
    EXPECT_TRUE(accessibilityNode.ActionSetText(nodeName));

    EXPECT_FALSE(accessibilityNode.ActionScrollForward());
    ActionScrollForwardImpl actionScrollForwardImpl = []() { return true; };
    accessibilityNode.SetActionScrollForward(actionScrollForwardImpl);
    EXPECT_TRUE(accessibilityNode.ActionScrollForward());

    EXPECT_FALSE(accessibilityNode.ActionScrollBackward());
    ActionScrollBackwardImpl actionScrollBackwardImpl = []() { return true; };
    accessibilityNode.SetActionScrollBackward(actionScrollBackwardImpl);
    EXPECT_TRUE(accessibilityNode.ActionScrollBackward());

    bool result = true;
    EXPECT_FALSE(accessibilityNode.ActionAccessibilityFocus(result));
    ActionAccessibilityFocusImpl actionAccessibilityFocusImpl = [](bool result) {};
    accessibilityNode.SetActionAccessibilityFocusImpl(actionAccessibilityFocusImpl);
    EXPECT_TRUE(accessibilityNode.ActionAccessibilityFocus(result));

    EXPECT_FALSE(accessibilityNode.ActionFocus());
    ActionFocusImpl actionFocusImpl = []() {};
    accessibilityNode.SetActionFocusImpl(actionFocusImpl);
    EXPECT_TRUE(accessibilityNode.ActionFocus());

    accessibilityNode.ActionUpdateIds();
    ActionUpdateIdsImpl actionUpdateIdsImpl = []() {};
    accessibilityNode.SetActionUpdateIdsImpl(actionUpdateIdsImpl);
    accessibilityNode.ActionUpdateIds();
}

/**
 * @tc.name: accessibilityNodeTest002
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityNodeTestNg, accessibilityNodeTest002, TestSize.Level1)
{
    NodeId id = 0;
    std::string nodeName = "accessibilityNodeTest";
    AccessibilityNode accessibilityNode(id, nodeName);

    PositionInfo positionInfo;
    positionInfo.height = TEST_NUMBER;
    accessibilityNode.SetPositionInfo(positionInfo);
    EXPECT_EQ(accessibilityNode.rect_.Height(), TEST_NUMBER);

    accessibilityNode.OnFocusChange(false);
    accessibilityNode.focusChangeEventId_ = [](const std::string& str) {};
    accessibilityNode.OnFocusChange(true);

    EXPECT_EQ(accessibilityNode.GetSupportAction().size(), 0);
    accessibilityNode.supportActions_ = static_cast<uint32_t>(AceAction::ACTION_SCROLL_FORWARD);
    EXPECT_EQ(accessibilityNode.GetSupportAction().size(), 1);
}

/**
 * @tc.name: accessibilityNodeTest003
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityNodeTestNg, accessibilityNodeTest003, TestSize.Level1)
{
    NodeId id = 0;
    std::string nodeName = "text";
    AccessibilityNode accessibilityNode(id, nodeName);

    std::vector<std::pair<std::string, std::string>> vec;
    vec.emplace_back(std::make_pair(VALUE, "ACCESSIBILITY_VALUE"));
    vec.emplace_back(std::make_pair(DISABLED, "ACCESSIBILITY_DISABLED"));
    vec.emplace_back(std::make_pair(TYPE, "ACCESSIBILITY_TYPE"));
    vec.emplace_back(std::make_pair(GROUP, "ACCESSIBILITY_GROUP"));
    vec.emplace_back(std::make_pair(TEXT, "ACCESSIBILITY_TEXT"));
    vec.emplace_back(std::make_pair(DESCRIPTION, "ACCESSIBILITY_DESCRIPTION"));
    vec.emplace_back(std::make_pair(IMPORTANCE, "ACCESSIBILITY_IMPORTANCE"));
    vec.emplace_back(std::make_pair(ID, "ID"));
    vec.emplace_back(std::make_pair(SHOW, "ACCESSIBILITY_SHOW"));

    accessibilityNode.SetAttr(vec);
    EXPECT_EQ(accessibilityNode.inputType_, "ACCESSIBILITY_TYPE");
    EXPECT_TRUE(accessibilityNode.isEnabled_);
    EXPECT_EQ(accessibilityNode.accessibilityLabel_, "ACCESSIBILITY_TEXT");
    EXPECT_EQ(accessibilityNode.accessibilityHint_, "ACCESSIBILITY_DESCRIPTION");
    EXPECT_EQ(accessibilityNode.importantForAccessibility_, "ACCESSIBILITY_IMPORTANCE");

    accessibilityNode.attrs_.emplace_back(std::make_pair(IMPORTANCE, "ACCESSIBILITY_IMPORTANCE"));
    accessibilityNode.SetAttr(vec);
    EXPECT_EQ(accessibilityNode.importantForAccessibility_, "ACCESSIBILITY_IMPORTANCE");
}

/**
 * @tc.name: accessibilityNodeTest004
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityNodeTestNg, accessibilityNodeTest004, TestSize.Level1)
{
    NodeId id = 0;
    std::string nodeName = "text";
    AccessibilityNode accessibilityNode(id, nodeName);

    std::vector<std::string> vec;
    vec.emplace_back(EVENT);
    vec.emplace_back(CLICK);
    vec.emplace_back(LONG_PRESS);
    vec.emplace_back(FOCUS);
    vec.emplace_back(BLUR);

    accessibilityNode.AddEvent(0, vec);
    EXPECT_TRUE(accessibilityNode.isClickable_);
    EXPECT_TRUE(accessibilityNode.isLongClickable_);
}

/**
 * @tc.name: accessibilityNodeTest005
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityNodeTestNg, accessibilityNodeTest005, TestSize.Level1)
{
    NodeId id = 0;
    std::string nodeName = "text";
    AccessibilityNode accessibilityNode(id, nodeName);
    auto child = AceType::MakeRefPtr<AccessibilityNode>(1, "child");
    accessibilityNode.AddNode(child, 0);
    EXPECT_EQ(accessibilityNode.children_.size(), 1);
    accessibilityNode.RemoveNode(child);
    EXPECT_EQ(accessibilityNode.children_.size(), 0);
}
} // namespace OHOS::Ace::NG
