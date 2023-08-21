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

#include <string>
#include "gtest/gtest.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/pattern/text/span_node.h"

#define private public
#define protected public
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/event/long_press_event.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/linear_layout/column_model.h"
#include "core/components_ng/pattern/linear_layout/column_model_ng.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/property/accessibility_property.h"
#include "core/components_v2/inspector/inspector_constants.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
const size_t ARRAY_SIZE = 1;
} // namespace

class MockPattern : public Pattern {
public:
    MockPattern() = default;
    ~MockPattern() override = default;
};
class AccessibilityPropertyTestNg : public testing::Test {
public:
    static void SetUpTestCase() {};
    static void TearDownTestCase() {};
};

/**
 * @tc.name: AccessibilityPropertyTest001
 * @tc.desc: Set show value into supportActions_ and get SupportAction length.
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityPropertyTestNg, AccessibilityPropertyTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. supportActions_ Use default values
     * @tc.expected: Make the array length returned by the GetSupportAction function 0
     */
    AccessibilityProperty props;
    auto actions = props.GetSupportAction();
    EXPECT_EQ(actions.size(), 0);

    /**
     * @tc.steps: step2. supportActions_ = AceAction::ACTION_SCROLL_FORWARD
     * @tc.expected: Make the array length returned by the GetSupportAction function 1
     */
    props.supportActions_ = static_cast<uint32_t>(AceAction::ACTION_SCROLL_FORWARD);
    actions = props.GetSupportAction();
    EXPECT_EQ(actions.size(), ARRAY_SIZE);

    /**
     * @tc.steps: step3. supportActions_ = AceAction::ACTION_PREVIOUS_AT_MOVEMENT_GRANULARITY
     * @tc.expected: Make the array length returned by the GetSupportAction function 1
     */
    props.supportActions_ = static_cast<uint32_t>(AceAction::ACTION_PREVIOUS_AT_MOVEMENT_GRANULARITY);
    actions = props.GetSupportAction();
    EXPECT_EQ(actions.size(), 2);

    /**
     * @tc.steps: step4. supportActions_ = AceAction::ACTION_SET_TEXT
     * @tc.expected: Make the array length returned by the GetSupportAction function 1
     */
    props.supportActions_ = static_cast<uint32_t>(AceAction::ACTION_SET_TEXT);
    actions = props.GetSupportAction();
    EXPECT_EQ(actions.size(), ARRAY_SIZE);

    /**
     * @tc.steps: step5. supportActions_ = AceAction::ACTION_COPY
     * @tc.expected: Make the array length returned by the GetSupportAction function 1
     */
    props.supportActions_ = static_cast<uint32_t>(AceAction::ACTION_COPY);
    actions = props.GetSupportAction();
    EXPECT_EQ(actions.size(), 2);

    /**
     * @tc.steps: step6. supportActions_ = AceAction::ACTION_PASTE
     * @tc.expected: Make the array length returned by the GetSupportAction function 1
     */
    props.supportActions_ = static_cast<uint32_t>(AceAction::ACTION_PASTE);
    actions = props.GetSupportAction();
    EXPECT_EQ(actions.size(), 2);

    /**
     * @tc.steps: step7. supportActions_ = AceAction::ACTION_CUT
     * @tc.expected: Make the array length returned by the GetSupportAction function 1
     */
    props.supportActions_ = static_cast<uint32_t>(AceAction::ACTION_CUT);
    actions = props.GetSupportAction();
    EXPECT_EQ(actions.size(), 3);

    /**
     * @tc.steps: step8. supportActions_ = AceAction::ACTION_SELECT
     * @tc.expected: Make the array length returned by the GetSupportAction function 1
     */
    props.supportActions_ = static_cast<uint32_t>(AceAction::ACTION_SELECT);
    actions = props.GetSupportAction();
    EXPECT_EQ(actions.size(), 0);

    /**
     * @tc.steps: step9. supportActions_ = AceAction::ACTION_SELECT
     * @tc.expected: Make the array length returned by the GetSupportAction function 1
     */
    props.supportActions_ = static_cast<uint32_t>(AceAction::ACTION_SET_SELECTION);
    actions = props.GetSupportAction();
    EXPECT_EQ(actions.size(), 1);

    /**
     * @tc.steps: step10. supportActions_ = AceAction::ACTION_CLEAR_SELECTION
     * @tc.expected: Make the array length returned by the GetSupportAction function 1
     */
    props.supportActions_ = static_cast<uint32_t>(AceAction::ACTION_CLEAR_SELECTION);
    actions = props.GetSupportAction();
    EXPECT_EQ(actions.size(), 1);
}

/**
 * @tc.name: AccessibilityPropertyTest002
 * @tc.desc: Set action and execute it.
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityPropertyTestNg, AccessibilityPropertyTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. actions is empty
     * @tc.expected: act every action return false
     */
    AccessibilityProperty props;
    EXPECT_FALSE(props.ActActionClearSelection());
    EXPECT_FALSE(props.ActActionCopy());
    EXPECT_FALSE(props.ActActionCut());
    EXPECT_FALSE(props.ActActionMoveText(1, true));
    EXPECT_FALSE(props.ActActionPaste());
    EXPECT_FALSE(props.ActActionScrollBackward());
    EXPECT_FALSE(props.ActActionScrollForward());
    EXPECT_FALSE(props.ActActionSelect());
    EXPECT_FALSE(props.ActActionSetSelection(0, 1));
    EXPECT_FALSE(props.ActActionSetText("abc"));

    /**
     * @tc.steps: step2. Set action functions
     * @tc.expected: act every action return true
     */
    props.SetActionClearSelection([]() {});
    EXPECT_TRUE(props.ActActionClearSelection());
    props.SetActionCopy([]() {});
    EXPECT_TRUE(props.ActActionCopy());
    props.SetActionCut([]() {});
    EXPECT_TRUE(props.ActActionCut());
    props.SetActionMoveText([](int32_t moveUnit, bool forward) {});
    EXPECT_TRUE(props.ActActionMoveText(1, true));
    props.SetActionPaste([]() {});
    EXPECT_TRUE(props.ActActionPaste());
    props.SetActionScrollBackward([]() {});
    EXPECT_TRUE(props.ActActionScrollBackward());
    props.SetActionScrollForward([]() {});
    EXPECT_TRUE(props.ActActionScrollForward());
    props.SetActionSelect([]() {});
    EXPECT_TRUE(props.ActActionSelect());
    props.SetActionSetSelection([](int32_t start, int32_t end) {});
    EXPECT_TRUE(props.ActActionSetSelection(0, 1));
    props.SetActionSetText([](std::string text) {});
    EXPECT_TRUE(props.ActActionSetText("abc"));
}

/**
 * @tc.name: AccessibilityPropertyTest003
 * @tc.desc: Set and get accessibility property.
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityPropertyTestNg, AccessibilityPropertyTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set accessibility property value
     * @tc.expected: Get default property value
     */
    AccessibilityProperty props;
    props.SetText("test");
    EXPECT_EQ(props.GetText(), "test");
    auto json = std::make_unique<JsonValue>();
    props.ToJsonValue(json);
    EXPECT_FALSE(json->GetBool("scrollable", false));
    EXPECT_FALSE(props.IsCheckable());
    EXPECT_FALSE(props.IsChecked());
    EXPECT_FALSE(props.IsSelected());
    EXPECT_FALSE(props.IsPassword());
    EXPECT_FALSE(props.IsEditable());
    EXPECT_FALSE(props.IsMultiLine());
    EXPECT_FALSE(props.IsDeletable());

    EXPECT_FALSE(props.IsHint());
    EXPECT_FALSE(props.IsScrollable());
    EXPECT_EQ(props.GetCurrentIndex(), -1);
    EXPECT_EQ(props.GetBeginIndex(), -1);
    EXPECT_EQ(props.GetEndIndex(), -1);
    EXPECT_FALSE(props.HasRange());
    EXPECT_EQ(props.GetAccessibilityValue().min, 0.0);
    EXPECT_EQ(props.GetAccessibilityValue().current, 0.0);
    EXPECT_EQ(props.GetAccessibilityValue().max, 0.0);
    EXPECT_EQ(props.GetHintText(), "");
    EXPECT_EQ(props.GetTextLengthLimit(), -1);
    EXPECT_EQ(props.GetCollectionInfo().columns, 0);
    EXPECT_EQ(props.GetCollectionInfo().rows, 0);
    EXPECT_EQ(props.GetCollectionInfo().selectMode, 0);
    EXPECT_EQ(props.GetCollectionItemInfo().column, 0);
    EXPECT_EQ(props.GetCollectionItemInfo().columnSpan, 0);
    EXPECT_EQ(props.GetCollectionItemInfo().row, 0);
    EXPECT_EQ(props.GetCollectionItemInfo().rowSpan, 0);
    EXPECT_FALSE(props.GetCollectionItemInfo().heading);
    EXPECT_EQ(props.GetErrorText(), "");
    EXPECT_EQ(props.GetTextSelectionStart(), 0);
    EXPECT_EQ(props.GetTextSelectionEnd(), 0);
    EXPECT_EQ(props.GetTextInputType(), AceTextCategory::INPUT_TYPE_DEFAULT);
    EXPECT_EQ(props.GetCollectionItemCounts(), 0);
    EXPECT_TRUE(props.GetContentInvalid());
    props.ResetSupportAction();
    auto actions = props.GetSupportAction();
    EXPECT_EQ(actions.size(), 0);
}

/**
 * @tc.name: AccessibilityPropertyTest004
 * @tc.desc: Set show value into supportActions_ and get SupportAction length.
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityPropertyTestNg, AccessibilityPropertyTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. supportActions_ Use default values
     * @tc.expected: Make the array length returned by the GetSupportAction function 0
     */
    auto columnFrameNode1 = FrameNode::GetOrCreateFrameNode(
        V2::COLUMN_ETS_TAG, 0, []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
    auto columnFrameNode2 = FrameNode::GetOrCreateFrameNode(
        V2::COLUMN_ETS_TAG, 1, []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
    auto buttonNode1 =
        FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG, 2, []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    auto buttonNode2 =
        FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG, 3, []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    auto buttonNode3 =
        FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG, 4, []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    auto buttonNode4 =
        FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG, 5, []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    auto buttonAccessibilityProperty1 = buttonNode1->GetAccessibilityProperty<AccessibilityProperty>();
    auto buttonAccessibilityProperty2 = buttonNode2->GetAccessibilityProperty<AccessibilityProperty>();
    auto buttonAccessibilityProperty3 = buttonNode3->GetAccessibilityProperty<AccessibilityProperty>();
    auto buttonAccessibilityProperty4 = buttonNode4->GetAccessibilityProperty<AccessibilityProperty>();
    auto columnAccessibilityProperty2 = columnFrameNode2->GetAccessibilityProperty<AccessibilityProperty>();
    buttonAccessibilityProperty1->SetText("Button1");
    buttonAccessibilityProperty2->SetText("Button2");
    buttonAccessibilityProperty3->SetText("Button3");
    buttonAccessibilityProperty4->SetText("Button4");
    columnAccessibilityProperty2->SetAccessibilityText("column2");
    buttonAccessibilityProperty1->SetAccessibilityDescription("Button1");

    columnFrameNode1->AddChild(buttonNode1);
    columnFrameNode1->AddChild(buttonNode2);
    columnFrameNode1->AddChild(columnFrameNode2);
    columnFrameNode2->AddChild(buttonNode3);
    columnFrameNode2->AddChild(buttonNode4);

    auto columnAccessibilityProperty1 = columnFrameNode1->GetAccessibilityProperty<AccessibilityProperty>();
    columnAccessibilityProperty1->SetAccessibilityGroup(true);
    columnAccessibilityProperty1->SetAccessibilityLevel("yes");

    buttonAccessibilityProperty3->SetAccessibilityText("buttonAccessibilityProperty3");
    buttonAccessibilityProperty3->SetAccessibilityGroup(true);
    buttonAccessibilityProperty3->SetAccessibilityLevel("yes");
    auto columnAccessibilityText1 = columnAccessibilityProperty1->GetAccessibilityText();
    /**
     * @tc.expected: step1. expect target text combine
     */
    EXPECT_EQ(buttonAccessibilityProperty1->GetAccessibilityDescription(), "Button1");
    EXPECT_EQ(columnAccessibilityText1, "Button1, Button2, column2");

    columnAccessibilityProperty1->SetAccessibilityLevel("no");
    columnAccessibilityText1 = columnAccessibilityProperty1->GetAccessibilityText();
    EXPECT_EQ(columnAccessibilityText1, "");
}

/**
 * @tc.name: AccessibilityPropertyTest005
 * @tc.desc: Set show value into supportActions_ and get SupportAction length.
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityPropertyTestNg, AccessibilityPropertyTest005, TestSize.Level1)
{
    std::string tag = "root";

    auto spanNode = SpanNode::GetOrCreateSpanNode(1);
    auto columnFrameNode1 = FrameNode::GetOrCreateFrameNode(
        V2::COLUMN_ETS_TAG, 0, []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
    auto buttonNode1 =
        FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG, 2, []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    spanNode->AddChild(buttonNode1);
    columnFrameNode1->AddChild(spanNode);

    std::list<RefPtr<FrameNode>> children;
    
    auto columnAccessibilityProperty1 = columnFrameNode1->GetAccessibilityProperty<AccessibilityProperty>();
    columnAccessibilityProperty1->SetAccessibilityGroup(true);
    columnAccessibilityProperty1->SetAccessibilityLevel("yes");
    columnAccessibilityProperty1->SetAccessibilityText("column1");

    auto text = columnAccessibilityProperty1->GetAccessibilityText();
    EXPECT_EQ(text, "column1");
}
} // namespace OHOS::Ace::NG
