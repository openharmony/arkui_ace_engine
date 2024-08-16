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
#include "core/common/container.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
const double TEST_NUMBER = 10.0;
const char VALUE[] = "value";
const char TYPE[] = "type";
const char DISABLED[] = "disabled";
const char GROUP[] = "accessibilitygroup";
const char ACCESS_TEXT[] = "accessibilitytext";
const char DESCRIPTION[] = "accessibilitydescription";
const char IMPORTANCE[] = "accessibilityimportance";
const char SHOW[] = "show";
const char ID[] = "id";
const char EVENT[] = "accessibility";
const char CLICK[] = "click";
const char LONG_PRESS[] = "longpress";
const char FOCUS[] = "focus";
const char BLUR[] = "blur";
const char FAKE[] = "fake";
const char INPUT_TYPE_CHECKBOX[] = "checkbox";
const char INPUT_TYPE_RADIO[] = "radio";
const char INPUT_TYPE_PASSWORD[] = "password";
} // namespace

class AccessibilityNodeTestNg : public testing::Test {
public:
    static void SetUpTestCase()
    {
        MockPipelineContext::SetUp();
        MockContainer::SetUp();
    };
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
    accessibilityNode.SetActionClickImpl([]() {});
    EXPECT_TRUE(accessibilityNode.ActionClick());

    EXPECT_FALSE(accessibilityNode.ActionLongClick());
    accessibilityNode.SetActionLongClickImpl([]() {});
    EXPECT_TRUE(accessibilityNode.ActionLongClick());

    EXPECT_FALSE(accessibilityNode.ActionSetText(nodeName));
    accessibilityNode.SetActionSetTextImpl([](const std::string& text) {});
    EXPECT_TRUE(accessibilityNode.ActionSetText(nodeName));

    EXPECT_FALSE(accessibilityNode.ActionScrollForward());
    accessibilityNode.SetActionScrollForward([]() { return true; });
    EXPECT_TRUE(accessibilityNode.ActionScrollForward());

    EXPECT_FALSE(accessibilityNode.ActionScrollBackward());
    accessibilityNode.SetActionScrollBackward([]() { return true; });
    EXPECT_TRUE(accessibilityNode.ActionScrollBackward());

    bool result = true;
    EXPECT_FALSE(accessibilityNode.ActionAccessibilityFocus(result));
    accessibilityNode.SetActionAccessibilityFocusImpl([](bool result) {});
    EXPECT_TRUE(accessibilityNode.ActionAccessibilityFocus(result));

    EXPECT_FALSE(accessibilityNode.ActionFocus());
    accessibilityNode.SetActionFocusImpl([]() {});
    EXPECT_TRUE(accessibilityNode.ActionFocus());

    accessibilityNode.ActionUpdateIds();
    accessibilityNode.SetActionUpdateIdsImpl([]() {});
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

    accessibilityNode.focusChangeEventId_ = [](const std::string& str) {};
    accessibilityNode.SetFocusedState(false);
    accessibilityNode.SetFocusedState(true);

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
    vec.emplace_back(std::make_pair(ACCESS_TEXT, "ACCESSIBILITY_TEXT"));
    vec.emplace_back(std::make_pair(DESCRIPTION, "ACCESSIBILITY_DESCRIPTION"));
    vec.emplace_back(std::make_pair(IMPORTANCE, "ACCESSIBILITY_IMPORTANCE"));
    vec.emplace_back(std::make_pair(ID, "ID"));
    vec.emplace_back(std::make_pair(SHOW, "ACCESSIBILITY_SHOW"));

    accessibilityNode.SetStyle(vec);
    accessibilityNode.SetAttr(vec);
    EXPECT_EQ(accessibilityNode.inputType_, "ACCESSIBILITY_TYPE");
    EXPECT_TRUE(accessibilityNode.isEnabled_);
    EXPECT_EQ(accessibilityNode.accessibilityLabel_, "ACCESSIBILITY_TEXT");
    EXPECT_EQ(accessibilityNode.accessibilityHint_, "ACCESSIBILITY_DESCRIPTION");
    EXPECT_EQ(accessibilityNode.importantForAccessibility_, "ACCESSIBILITY_IMPORTANCE");

    accessibilityNode.attrs_.emplace_back(std::make_pair(IMPORTANCE, "ACCESSIBILITY_IMPORTANCE"));
    accessibilityNode.SetAttr(vec);
    EXPECT_EQ(accessibilityNode.importantForAccessibility_, "ACCESSIBILITY_IMPORTANCE");

    accessibilityNode.SetTag("text");
    accessibilityNode.SetAttr(vec);
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
    vec.emplace_back(FAKE);

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
    /**
     * @tc.steps: step1. create AccessibilityNode and vector.
     */
    NodeId id = 0;
    std::string nodeName = "text";
    AccessibilityNode accessibilityNode(id, nodeName);

    /**
     * @tc.steps: step2. create offset.
     */
    Offset offset(1.0, 1.0);

    /**
     * @tc.steps: step3. create child and add node twice.
     * @tc.expected: only one can add success.
     */
    auto child = AceType::MakeRefPtr<AccessibilityNode>(1, "child");
    accessibilityNode.AddNode(child, 0);
    accessibilityNode.AddNode(child, 0);
    EXPECT_EQ(accessibilityNode.children_.size(), 1);

    /**
     * @tc.steps: step4. call AddOffsetForChildren.
     * @tc.expected: accessibilityNode offset is meet expectations.
     */
    accessibilityNode.AddOffsetForChildren(offset);
    EXPECT_EQ(accessibilityNode.GetLeft(), 1);

    /**
     * @tc.steps: step5. call remove node.
     * @tc.expected: child remove success.
     */
    accessibilityNode.RemoveNode(child);
    EXPECT_EQ(accessibilityNode.children_.size(), 0);
}

/**
 * @tc.name: accessibilityNodeTest006
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityNodeTestNg, accessibilityNodeTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create AccessibilityNode and vector.
     */
    NodeId id = 0;
    AccessibilityNode currentNode(id, "test");
    std::vector<std::pair<std::string, std::string>> vec;

    /**
     * @tc.steps: step2. config pare and call SetAttr.
     * @tc.expected: currentNode params text_ is meet expectations.
     */
    vec.emplace_back(std::make_pair(VALUE, "value"));
    currentNode.SetAttr(vec);
    EXPECT_EQ(currentNode.text_, "value");

    /**
     * @tc.steps: step3. create a parent node and setTag recall SetAttr.
     * @tc.expected: currentNode params text_ is meet expectations.
     */
    auto parentNode = AceType::MakeRefPtr<AccessibilityNode>(1, "parent");
    currentNode.SetParentNode(parentNode);
    currentNode.SetTag("text");
    currentNode.SetAttr(vec);
    EXPECT_NE(parentNode->text_, "value");

    /**
     * @tc.steps: step4. put a fake value in pair and set tag popup.
     * @tc.expected: currentNode params text_ is meet expectations.
     */
    vec.emplace_back(std::make_pair(FAKE, "FAKE_VALUE"));
    parentNode->SetTag("popup");
    currentNode.SetAttr(vec);
    EXPECT_EQ(parentNode->text_, "value");

    /**
     * @tc.steps: step5. set tag input, put a wrong type in pair, initialization parameters.
     * @tc.expected: currentNode params isCheckable_ is false.
     */
    currentNode.SetTag("input");
    currentNode.isFocusable_ = false;
    currentNode.isCheckable_ = false;
    currentNode.isCheckable_ = false;
    vec.emplace_back(std::make_pair(TYPE, FAKE));
    currentNode.SetAttr(vec);
    EXPECT_FALSE(currentNode.isCheckable_);

    /**
     * @tc.steps: step6. remove fake pair and put type with INPUT_TYPE_CHECKBOX.
     * @tc.expected: currentNode params isCheckable_ is true.
     */
    vec.pop_back();
    vec.emplace_back(std::make_pair(TYPE, INPUT_TYPE_CHECKBOX));
    currentNode.SetAttr(vec);
    EXPECT_TRUE(currentNode.isCheckable_);

    /**
     * @tc.steps: step7. remove fake pair and put type with INPUT_TYPE_RADIO.
     * @tc.expected: currentNode params isCheckable_ is true.
     */
    currentNode.isCheckable_ = false;
    vec.pop_back();
    vec.emplace_back(std::make_pair(TYPE, INPUT_TYPE_RADIO));
    currentNode.SetAttr(vec);
    EXPECT_TRUE(currentNode.isCheckable_);

    /**
     * @tc.steps: step8. remove fake pair and put type with INPUT_TYPE_PASSWORD.
     * @tc.expected: currentNode params isPassword_ is true.
     */
    vec.pop_back();
    vec.emplace_back(std::make_pair(TYPE, INPUT_TYPE_PASSWORD));
    currentNode.SetAttr(vec);
    EXPECT_TRUE(currentNode.isPassword_);
}

/**
 * @tc.name: accessibilityNodeTest007
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityNodeTestNg, accessibilityNodeTest007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create EventMarker with empty eventId and AccessibilityNode.
     */
    NodeId id = 0;
    int32_t pageId = 1;
    auto marker = EventMarker("", "event", pageId);
    std::string nodeName = "text";
    AccessibilityNode accessibilityNode(id, nodeName);
    accessibilityNode.Mount(0);
    /**
     * @tc.steps: step2. call SetFocusChangeEventMarker function.
     * @tc.expected: the param focusChangeEventId_ in accessibilityNode is null.
     */
    accessibilityNode.SetFocusChangeEventMarker(marker);
    EXPECT_FALSE(accessibilityNode.focusChangeEventId_);

    /**
     * @tc.steps: step3. set eventId not empty and config Container, then recall SetFocusChangeEventMarker.
     * @tc.expected: the param focusChangeEventId_ in accessibilityNode is null.
     */
    marker.data_->eventId = std::to_string(id);
    MockContainer::Current()->pipelineContext_ = MockPipelineContext::GetCurrent();
    accessibilityNode.SetFocusChangeEventMarker(marker);
    EXPECT_FALSE(accessibilityNode.focusChangeEventId_);
}
} // namespace OHOS::Ace::NG
