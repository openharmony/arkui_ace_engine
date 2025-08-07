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
namespace {
const InspectorFilter filter;
const size_t ARRAY_SIZE = 1;
const OffsetF OFFSETF { 1.0, 1.0 };
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
    props.SetActionSetSelection([](int32_t start, int32_t end, bool isforward) {});
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
    props.ToJsonValue(json, filter);
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

    columnFrameNode1->frameChildren_.emplace(buttonNode1);
    columnFrameNode1->frameChildren_.emplace(buttonNode2);
    columnFrameNode1->frameChildren_.emplace(columnFrameNode2);
    columnFrameNode2->frameChildren_.emplace(buttonNode3);
    columnFrameNode2->frameChildren_.emplace(buttonNode4);

    auto columnAccessibilityProperty1 = columnFrameNode1->GetAccessibilityProperty<AccessibilityProperty>();
    columnAccessibilityProperty1->SetAccessibilityGroup(true);
    columnAccessibilityProperty1->SetAccessibilityLevel("yes");

    auto columnAccessibilityText1 = columnAccessibilityProperty1->GetGroupText();
    /**
     * @tc.expected: step1. expect target text combine
     */
    EXPECT_EQ(buttonAccessibilityProperty1->GetAccessibilityDescription(), "Button1");
    EXPECT_EQ(columnAccessibilityText1, "Button1, Button2, Button3, Button4");

    columnAccessibilityProperty1->SetAccessibilityLevel("no-hide-descendants");
    columnAccessibilityText1 = columnAccessibilityProperty1->GetGroupText();
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

/**
 * @tc.name: AccessibilityPropertyTest006
 * @tc.desc: Set show value into supportActions_ and get SupportAction length.
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityPropertyTestNg, AccessibilityPropertyTest006, TestSize.Level1)
{
    /**
     * @tc.steps1: Create FrameNode and Add Children
     */
    std::string tag = "root";
    auto spanNode = SpanNode::GetOrCreateSpanNode(1);
    auto columnFrameNode1 = FrameNode::GetOrCreateFrameNode(
        V2::COLUMN_ETS_TAG, 0, []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
    auto buttonNode1 =
        FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG, 2, []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    auto customFrameNode2 = CustomNode::CreateCustomNode(1, "Column");
    spanNode->AddChild(buttonNode1);
    spanNode->AddChild(customFrameNode2);
    columnFrameNode1->AddChild(spanNode);
    columnFrameNode1->AddChild(buttonNode1);
    auto columnAccessibilityProperty1 = columnFrameNode1->GetAccessibilityProperty<AccessibilityProperty>();
    columnAccessibilityProperty1->SetAccessibilityGroup(true);
    columnAccessibilityProperty1->SetAccessibilityLevel("yes");
    columnAccessibilityProperty1->SetAccessibilityText("column1");

    /**
     * @tc.steps2: call GetAccessibilityText
     * @tc.expected: 'column1'
     */
    auto text = columnAccessibilityProperty1->GetAccessibilityText();
    EXPECT_EQ(text, "column1");

    /**
     * @tc.steps3: reset accessibilityText_ and call GetAccessibilityText
     * @tc.expected: ''
     */
    columnAccessibilityProperty1->accessibilityText_.reset();
    text = columnAccessibilityProperty1->GetAccessibilityText();
    EXPECT_EQ(text, "");

    /**
     * @tc.steps4: add a new frameNode and SetAccessibilityText
     * @tc.expected: 'test'
     */
    auto buttonNode2 =
        FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG, 3, []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    buttonNode2->GetAccessibilityProperty<AccessibilityProperty>()->SetAccessibilityText("test");
    text = buttonNode2->GetAccessibilityProperty<AccessibilityProperty>()->GetAccessibilityText();
    EXPECT_EQ(text, "test");
}

/**
 * @tc.name: AccessibilityPropertyTest007
 * @tc.desc: Set action and execute it.
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityPropertyTestNg, AccessibilityPropertyTest007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. actions is empty
     * @tc.expected: act every action return false
     */
    AccessibilityProperty props;
    props.SetActionSetSelection([](int32_t start, int32_t end, bool isforward) {});
    EXPECT_TRUE(props.ActActionSetSelection(0, 1));
    props.SetActionSetIndex([](int32_t start) {});
    EXPECT_TRUE(props.ActActionSetIndex(1));
    props.SetActionGetIndex([]() {return 2;});
    EXPECT_TRUE(props.ActActionGetIndex());
}

/**
 * @tc.name: AccessibilityPropertyTest008
 * @tc.desc: GetScrollOffSet
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityPropertyTestNg, AccessibilityPropertyTest008, TestSize.Level1)
{
    AccessibilityProperty accessibilityProperty;
    auto result = accessibilityProperty.GetScrollOffSet();
    EXPECT_EQ(result, -1.0f);
}

/**
 * @tc.name: AccessibilityPropertyTest009
 * @tc.desc: HoverTest
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityPropertyTestNg, AccessibilityPropertyTest009, TestSize.Level1)
{
    AccessibilityProperty accessibilityProperty;
    auto root = FrameNode::GetOrCreateFrameNode(
        V2::BUTTON_ETS_TAG, 11, []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    NG::PointF hoverPoint(0, 0);
    auto debugInfo = std::make_unique<AccessibilityProperty::HoverTestDebugTraceInfo>();
    auto result = accessibilityProperty.HoverTest(hoverPoint, root, debugInfo);
    EXPECT_EQ(result.size(), 0);
}

/**
 * @tc.name: AccessibilityPropertyTest010
 * @tc.desc: CreateNodeSearchInfo
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityPropertyTestNg, AccessibilityPropertyTest010, TestSize.Level1)
{
    AccessibilityProperty accessibilityProperty;
    bool ancestorGroupFlag = false;
    auto root = FrameNode::CreateFrameNode(
        V2::BUTTON_ETS_TAG, 12, AceType::MakeRefPtr<Pattern>(), true);
    NG::PointF hoverPoint(0, 0);
    auto result = accessibilityProperty.CreateNodeSearchInfo(root, hoverPoint, ancestorGroupFlag);
    EXPECT_TRUE(root->IsRootNode());

    auto subNode = FrameNode::GetOrCreateFrameNode(
        V2::BUTTON_ETS_TAG, 1, []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    root->AddChild(subNode);
    EXPECT_FALSE(subNode->IsRootNode());
    result = accessibilityProperty.CreateNodeSearchInfo(subNode, hoverPoint, ancestorGroupFlag);
    EXPECT_TRUE(result->Contains("parent"));
    EXPECT_TRUE(result->Contains("visible"));

    auto accessibilityPropertyRoot = root->GetAccessibilityProperty<NG::AccessibilityProperty>();
    EXPECT_NE(accessibilityPropertyRoot, nullptr);
    EXPECT_TRUE(result->Contains("accessibilityLevel"));

    root->SetHitTestMode(HitTestMode::HTMDEFAULT);
    result = accessibilityProperty.CreateNodeSearchInfo(subNode, hoverPoint, ancestorGroupFlag);
    EXPECT_TRUE(result->Contains("hitTestMode"));
    std::string value = result->GetString("hitTestMode");
    EXPECT_EQ(value, "Default");

    auto subNode1 = FrameNode::GetOrCreateFrameNode(
        V2::BUTTON_ETS_TAG, 2, []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    root->AddChild(subNode1);
    subNode1->SetHitTestMode(HitTestMode::HTMBLOCK);
    auto result1 = accessibilityProperty.CreateNodeSearchInfo(subNode1, hoverPoint, ancestorGroupFlag);
    EXPECT_TRUE(result1->Contains("hitTestMode"));
    std::string value1 = result1->GetString("hitTestMode");
    EXPECT_EQ(value1, "Block");

    auto subNode2 = FrameNode::GetOrCreateFrameNode(
        V2::BUTTON_ETS_TAG, 3, []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    root->AddChild(subNode2);
    subNode2->SetHitTestMode(HitTestMode::HTMTRANSPARENT);
    auto result2 = accessibilityProperty.CreateNodeSearchInfo(subNode2, hoverPoint, ancestorGroupFlag);
    EXPECT_TRUE(result2->Contains("hitTestMode"));
    std::string value2 = result2->GetString("hitTestMode");
    EXPECT_EQ(value2, "Transparent");
}

/**
 * @tc.name: AccessibilityPropertyTest011
 * @tc.desc: HoverTestRecursive
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityPropertyTestNg, AccessibilityPropertyTest011, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "AccessibilityPropertyTest011 start";
    AccessibilityProperty accessibilityProperty;
    AccessibilityHoverTestPath path;
    auto root = FrameNode::GetOrCreateFrameNode(
        V2::BUTTON_ETS_TAG, 1, []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    NG::PointF hoverPoint(0, 0);
    auto debugInfo = std::make_unique<AccessibilityProperty::HoverTestDebugTraceInfo>();

    bool ancestorGroupFlag = false;

    root->SetActive(false);
    auto result = accessibilityProperty.HoverTestRecursive(hoverPoint, root, path, debugInfo, ancestorGroupFlag);
    EXPECT_EQ(result, false);
    root->SetActive(true);

    root->SetInternal();
    result = accessibilityProperty.HoverTestRecursive(hoverPoint, root, path, debugInfo, ancestorGroupFlag);
    EXPECT_EQ(result, false);

    root->SetActive(true);
    root->isInternal_ = false;
}

/**
 * @tc.name: AccessibilityPropertyTest012
 * @tc.desc: GetSearchStrategy
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityPropertyTestNg, AccessibilityPropertyTest012, TestSize.Level1)
{
    AccessibilityProperty accessibilityProperty;
    bool ancestorGroupFlag = false;
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::BUTTON_ETS_TAG, 14, []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    auto result = accessibilityProperty.GetSearchStrategy(frameNode, ancestorGroupFlag);
    EXPECT_EQ(result, std::make_tuple(true, true, false));

    auto accessibilityPropertyNew = frameNode->GetAccessibilityProperty<NG::AccessibilityProperty>();
    EXPECT_NE(accessibilityPropertyNew, nullptr);
    auto levelBak = accessibilityPropertyNew->GetAccessibilityLevel();
    accessibilityPropertyNew->SetAccessibilityLevel(AccessibilityProperty::Level::YES_STR);
    result = accessibilityProperty.GetSearchStrategy(frameNode, ancestorGroupFlag);
    EXPECT_EQ(result, std::make_tuple(true, true, false));

    bool hasGroupOrVirtualNodeBak = accessibilityPropertyNew->IsAccessibilityGroup();
    accessibilityPropertyNew->SetAccessibilityGroup(true);
    result = accessibilityProperty.GetSearchStrategy(frameNode, ancestorGroupFlag);
    EXPECT_EQ(result, std::make_tuple(true, true, true));
    accessibilityPropertyNew->SetAccessibilityGroup(hasGroupOrVirtualNodeBak);
    accessibilityPropertyNew->SetAccessibilityLevel(levelBak);

    accessibilityPropertyNew->SetAccessibilityLevel(AccessibilityProperty::Level::NO_HIDE_DESCENDANTS);
    result = accessibilityProperty.GetSearchStrategy(frameNode, ancestorGroupFlag);
    EXPECT_EQ(result, std::make_tuple(false, false, false));
    accessibilityPropertyNew->SetAccessibilityLevel(levelBak);

    hasGroupOrVirtualNodeBak = accessibilityPropertyNew->IsAccessibilityGroup();
    result = accessibilityProperty.GetSearchStrategy(frameNode, ancestorGroupFlag);
    EXPECT_EQ(result, std::make_tuple(true, true, false));

    accessibilityPropertyNew->SetAccessibilityGroup(true);
    result = accessibilityProperty.GetSearchStrategy(frameNode, ancestorGroupFlag);
    EXPECT_EQ(result, std::make_tuple(true, true, true));
    accessibilityPropertyNew->SetAccessibilityGroup(hasGroupOrVirtualNodeBak);

    accessibilityPropertyNew->SetAccessibilityLevel(AccessibilityProperty::Level::NO_STR);
    result = accessibilityProperty.GetSearchStrategy(frameNode, ancestorGroupFlag);
    EXPECT_EQ(result, std::make_tuple(false, true, false));

    accessibilityPropertyNew->SetAccessibilityLevel(AccessibilityProperty::Level::AUTO);
    accessibilityPropertyNew->SetAccessibilityGroup(true);
    bool hasGroupOrVirtualNode = accessibilityPropertyNew->IsAccessibilityGroup() ||
                accessibilityPropertyNew->HasAccessibilityVirtualNode();
    EXPECT_TRUE(hasGroupOrVirtualNode);
    result = accessibilityProperty.GetSearchStrategy(frameNode, ancestorGroupFlag);
    EXPECT_EQ(result, std::make_tuple(true, true, true));
    accessibilityPropertyNew->SetAccessibilityGroup(hasGroupOrVirtualNodeBak);
}

/**
 * @tc.name: AccessibilityPropertyTest013
 * @tc.desc: IsAccessibilityFocusableDebug
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityPropertyTestNg, AccessibilityPropertyTest013, TestSize.Level1)
{
    AccessibilityProperty accessibilityProperty;
    auto root = FrameNode::CreateFrameNode(
        V2::BUTTON_ETS_TAG, 15, AceType::MakeRefPtr<Pattern>(), true);
    std::unique_ptr<JsonValue> info = JsonUtil::Create();

    auto result = accessibilityProperty.IsAccessibilityFocusableDebug(root, info);
    EXPECT_EQ(result, false);

    bool isRoot = root->IsRootNode();
    EXPECT_EQ(isRoot, true);
    auto buttonNode = FrameNode::GetOrCreateFrameNode(
        V2::BUTTON_ETS_TAG, 6, []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    root->AddChild(buttonNode);
    result = accessibilityProperty.IsAccessibilityFocusableDebug(buttonNode, info);
    EXPECT_EQ(result, false);
    EXPECT_TRUE(info->Contains("parent"));

    auto accessibilityPropertyBt = buttonNode->GetAccessibilityProperty<NG::AccessibilityProperty>();
    EXPECT_NE(accessibilityPropertyBt, nullptr);
    EXPECT_TRUE(info->Contains("hasAction"));
}


/**
 * @tc.name: AccessibilityPropertyTest014
 * @tc.desc: IsAccessibilityFocusable
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityPropertyTestNg, AccessibilityPropertyTest014, TestSize.Level1)
{
    AccessibilityProperty accessibilityProperty1;
    auto root = FrameNode::CreateFrameNode(
        V2::BUTTON_ETS_TAG, 15, AceType::MakeRefPtr<Pattern>(), true);
    auto result = accessibilityProperty1.IsAccessibilityFocusable(root);
    EXPECT_EQ(result, false);

    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::BUTTON_ETS_TAG, 6, []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    auto accessibilityProperty = frameNode->GetAccessibilityProperty<NG::AccessibilityProperty>();
    auto levelBak = accessibilityProperty->GetAccessibilityLevel();
    EXPECT_NE(accessibilityProperty, nullptr);

    accessibilityProperty->SetAccessibilityLevel(AccessibilityProperty::Level::YES_STR);
    result = accessibilityProperty->IsAccessibilityFocusable(frameNode);
    EXPECT_EQ(result, true);

    accessibilityProperty->SetAccessibilityLevel(AccessibilityProperty::Level::NO_STR);
    result = accessibilityProperty->IsAccessibilityFocusable(frameNode);
    EXPECT_EQ(result, false);

    accessibilityProperty->SetAccessibilityLevel(AccessibilityProperty::Level::AUTO);
    accessibilityProperty->SetAccessibilityGroup(true);
    result = accessibilityProperty->IsAccessibilityFocusable(frameNode);
    EXPECT_EQ(result, true);


    auto eventHub = frameNode->GetOrCreateEventHub<EventHub>();
    bool isEnableBak = eventHub->IsEnabled();
    eventHub->SetEnabledInternal(false);
    result = accessibilityProperty->IsAccessibilityFocusable(frameNode);
    EXPECT_EQ(result, true);
    eventHub->SetEnabledInternal(isEnableBak);

    auto gestureEventHubBak = eventHub->GetGestureEventHub();
    auto gestureEventHubNew = eventHub->GetOrCreateGestureEventHub();
    EXPECT_TRUE(gestureEventHubNew != nullptr);


    result = accessibilityProperty->IsAccessibilityFocusable(frameNode);
    EXPECT_EQ(result, true);
    eventHub->SetGestureEventHub(gestureEventHubBak);
}

/**
 * @tc.name: AccessibilityPropertyTest015
 * @tc.desc: HasAccessibilityTextOrDescription
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityPropertyTestNg, AccessibilityPropertyTest015, TestSize.Level1)
{
    AccessibilityProperty accessibilityProperty;
    auto result = accessibilityProperty.HasAccessibilityTextOrDescription();
    EXPECT_EQ(result, false);
}

/**
 * @tc.name: AccessibilityPropertyTest016
 * @tc.desc: HasAction
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityPropertyTestNg, AccessibilityPropertyTest016, TestSize.Level1)
{
    AccessibilityProperty accessibilityProperty;
    auto result = accessibilityProperty.HasAction();
    EXPECT_EQ(result, false);
}

/**
 * @tc.name: AccessibilityPropertyTest017
 * @tc.desc: SetAccessibilityActions, ResetAccessibilityActions, HasAccessibilityActions and GetAccessibilityActions
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityPropertyTestNg, AccessibilityPropertyTest017, TestSize.Level1)
{
    AccessibilityProperty accessibilityProperty;
    uint32_t accessibilityActions = 1;
    accessibilityProperty.SetAccessibilityActions(accessibilityActions);
    EXPECT_TRUE(accessibilityProperty.HasAccessibilityActions());
    EXPECT_EQ(accessibilityProperty.GetAccessibilityActions(), accessibilityActions);
    accessibilityProperty.ResetAccessibilityActions();
    EXPECT_FALSE(accessibilityProperty.HasAccessibilityActions());
    EXPECT_EQ(accessibilityProperty.GetAccessibilityActions(), 0);
}

/**
 * @tc.name: AccessibilityPropertyTest018
 * @tc.desc: SetAccessibilityRole, ResetAccessibilityRole, HasAccessibilityRole and GetAccessibilityRole
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityPropertyTestNg, AccessibilityPropertyTest018, TestSize.Level1)
{
    AccessibilityProperty accessibilityProperty;
    const std::string role = "role";
    accessibilityProperty.SetAccessibilityRole(role);
    EXPECT_TRUE(accessibilityProperty.HasAccessibilityRole());
    EXPECT_EQ(accessibilityProperty.GetAccessibilityRole(), role);
    accessibilityProperty.ResetAccessibilityRole();
    EXPECT_FALSE(accessibilityProperty.HasAccessibilityRole());
    EXPECT_EQ(accessibilityProperty.GetAccessibilityRole(), "");
}

/**
 * @tc.name: AccessibilityPropertyTest019
 * @tc.desc: SetActions
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityPropertyTestNg, AccessibilityPropertyTest019, TestSize.Level1)
{
    AccessibilityProperty accessibilityProperty;
    ActionsImpl actionsImpl = [](uint32_t type){};
    accessibilityProperty.SetActions(actionsImpl);
}

/**
 * @tc.name: AccessibilityPropertyTest020
 * @tc.desc: SetUserDisabled HasUserDisabled and IsUserDisabled
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityPropertyTestNg, AccessibilityPropertyTest020, TestSize.Level1)
{
    AccessibilityProperty accessibilityProperty;
    const bool isDisabled = true;
    EXPECT_FALSE(accessibilityProperty.HasUserDisabled());
    EXPECT_FALSE(accessibilityProperty.IsUserDisabled());
    accessibilityProperty.SetUserDisabled(isDisabled);
    EXPECT_TRUE(accessibilityProperty.HasUserDisabled());
    EXPECT_TRUE(accessibilityProperty.IsUserDisabled());
}

/**
 * @tc.name: AccessibilityPropertyTest021
 * @tc.desc: HasUserSelected SetUserSelected and IsUserSelected
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityPropertyTestNg, AccessibilityPropertyTest021, TestSize.Level1)
{
    AccessibilityProperty accessibilityProperty;
    const bool isSelected = true;
    EXPECT_FALSE(accessibilityProperty.HasUserSelected());
    EXPECT_FALSE(accessibilityProperty.IsUserSelected());
    accessibilityProperty.SetUserSelected(isSelected);
    EXPECT_TRUE(accessibilityProperty.HasUserSelected());
    EXPECT_TRUE(accessibilityProperty.IsUserSelected());
}

/**
 * @tc.name: AccessibilityPropertyTest022
 * @tc.desc: HasUserCheckedType GetUserCheckedType and SetUserCheckedType
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityPropertyTestNg, AccessibilityPropertyTest022, TestSize.Level1)
{
    AccessibilityProperty accessibilityProperty;
    const int32_t checkedType = 1;
    EXPECT_FALSE(accessibilityProperty.HasUserCheckedType());
    EXPECT_EQ(accessibilityProperty.GetUserCheckedType(), 0);
    accessibilityProperty.SetUserCheckedType(checkedType);
    EXPECT_TRUE(accessibilityProperty.HasUserCheckedType());
    EXPECT_EQ(accessibilityProperty.GetUserCheckedType(), checkedType);
}

/**
 * @tc.name: AccessibilityPropertyTest023
 * @tc.desc: GetUserMinValue SetUserMinValue and HasUserMinValue
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityPropertyTestNg, AccessibilityPropertyTest023, TestSize.Level1)
{
    AccessibilityProperty accessibilityProperty;
    const int32_t minValue = -2;
    EXPECT_EQ(accessibilityProperty.GetUserMinValue(), -1);
    EXPECT_FALSE(accessibilityProperty.HasUserMinValue());
    accessibilityProperty.SetUserMinValue(minValue);
    EXPECT_TRUE(accessibilityProperty.HasUserMinValue());
    EXPECT_EQ(accessibilityProperty.GetUserMinValue(), minValue);
}

/**
 * @tc.name: AccessibilityPropertyTest024
 * @tc.desc: GetUserMaxValue HasUserMaxValue and SetUserMaxValue
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityPropertyTestNg, AccessibilityPropertyTest024, TestSize.Level1)
{
    AccessibilityProperty accessibilityProperty;
    const int32_t maxValue = 2;
    EXPECT_EQ(accessibilityProperty.GetUserMaxValue(), -1);
    EXPECT_FALSE(accessibilityProperty.HasUserMaxValue());
    accessibilityProperty.SetUserMaxValue(maxValue);
    EXPECT_TRUE(accessibilityProperty.HasUserMaxValue());
    EXPECT_EQ(accessibilityProperty.GetUserMaxValue(), maxValue);
}

/**
 * @tc.name: AccessibilityPropertyTest025
 * @tc.desc: GetUserCurrentValue SetUserCurrentValue and HasUserCurrentValue
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityPropertyTestNg, AccessibilityPropertyTest025, TestSize.Level1)
{
    AccessibilityProperty accessibilityProperty;
    const int32_t currentValue = 2;
    EXPECT_EQ(accessibilityProperty.GetUserCurrentValue(), -1);
    EXPECT_FALSE(accessibilityProperty.HasUserCurrentValue());
    accessibilityProperty.SetUserCurrentValue(currentValue);
    EXPECT_TRUE(accessibilityProperty.HasUserCurrentValue());
    EXPECT_EQ(accessibilityProperty.GetUserCurrentValue(), currentValue);
}

/**
 * @tc.name: AccessibilityPropertyTest026
 * @tc.desc: SetUserTextValue, SetUserTextValue and GetUserTextValue
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityPropertyTestNg, AccessibilityPropertyTest026, TestSize.Level1)
{
    AccessibilityProperty accessibilityProperty;
    const std::string textValue = "textValue";
    EXPECT_EQ(accessibilityProperty.GetUserTextValue(), "");
    EXPECT_FALSE(accessibilityProperty.HasUserTextValue());
    accessibilityProperty.SetUserTextValue(textValue);
    EXPECT_TRUE(accessibilityProperty.HasUserTextValue());
    EXPECT_EQ(accessibilityProperty.GetUserTextValue(), textValue);
}

/**
 * @tc.name: AccessibilityPropertyTest027
 * @tc.desc: test GetGroupTextRecursive
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityPropertyTestNg, AccessibilityPropertyTest027, TestSize.Level1)
{
    AccessibilityProperty accessibilityProperty;
    const std::string textValue = "textValue";
    accessibilityProperty.SetUserTextValue(textValue);
    WeakPtr<FrameNode> hostBak = accessibilityProperty.host_;
    accessibilityProperty.SetHost(nullptr);
    std::string text = "";
    accessibilityProperty.GetGroupTextRecursive(false, text, false);
    EXPECT_EQ(text, "");

    accessibilityProperty.SetHost(hostBak);
    accessibilityProperty.GetGroupTextRecursive(false, text, false);
    EXPECT_EQ(text, "");

    std::string levelBak = accessibilityProperty.GetAccessibilityLevel();
    accessibilityProperty.SetAccessibilityLevel(AccessibilityProperty::Level::YES_STR);
    accessibilityProperty.GetGroupTextRecursive(false, text, false);
    EXPECT_EQ(text, "");
    size_t found = text.find(',');
    EXPECT_FALSE(found != std::string::npos);
    accessibilityProperty.SetAccessibilityLevel(levelBak);

    text = "";
    levelBak = accessibilityProperty.GetAccessibilityLevel();
    accessibilityProperty.SetAccessibilityLevel(AccessibilityProperty::Level::NO_HIDE_DESCENDANTS);
    accessibilityProperty.GetGroupTextRecursive(false, text, false);
    EXPECT_EQ(text, "");
    accessibilityProperty.SetAccessibilityLevel(levelBak);

    text = "";
    levelBak = accessibilityProperty.GetAccessibilityLevel();
    accessibilityProperty.SetAccessibilityLevel(AccessibilityProperty::Level::NO_STR);
    accessibilityProperty.GetGroupTextRecursive(false, text, false);
    EXPECT_EQ(text, "");
    accessibilityProperty.SetAccessibilityLevel(levelBak);

    text = "";
    levelBak = accessibilityProperty.GetAccessibilityLevel();
    bool isAccessibilityGroup = accessibilityProperty.IsAccessibilityGroup();
    accessibilityProperty.SetAccessibilityLevel(AccessibilityProperty::Level::AUTO);
    accessibilityProperty.SetAccessibilityGroup(true);
    accessibilityProperty.GetGroupTextRecursive(true, text, false);
    found = text.find(',');
    EXPECT_FALSE(found != std::string::npos);
    accessibilityProperty.SetAccessibilityLevel(levelBak);
    accessibilityProperty.SetAccessibilityGroup(isAccessibilityGroup);
}

/**
 * @tc.name: AccessibilityPropertyTest028
 * @tc.desc: test ActionsDefined
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityPropertyTestNg, AccessibilityPropertyTest028, TestSize.Level1)
{
    AccessibilityProperty accessibilityProperty;
    uint32_t actions = static_cast<uint32_t>(ArkUI_AccessibilityActionType::ARKUI_ACCESSIBILITY_ACTION_COPY);
    accessibilityProperty.ResetAccessibilityActions();
    bool isDefined = accessibilityProperty.ActionsDefined(actions);
    EXPECT_FALSE(isDefined);

    accessibilityProperty.SetAccessibilityActions(actions);
    isDefined = accessibilityProperty.ActionsDefined(actions);
    ActionsImpl actionsImplBak = accessibilityProperty.actionsImpl_;
    accessibilityProperty.SetActions(nullptr);
    isDefined = accessibilityProperty.ActionsDefined(actions);
    EXPECT_FALSE(isDefined);

    ActionsImpl actionsImpl = [](uint32_t type){};
    accessibilityProperty.SetActions(actionsImpl);
    isDefined = accessibilityProperty.ActionsDefined(actions);
    EXPECT_TRUE(isDefined);
}

/**
 * @tc.name: AccessibilityPropertyTest029
 * @tc.desc: test CreateNodeSearchInfo
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityPropertyTestNg, AccessibilityPropertyTest029, TestSize.Level1)
{
    AccessibilityProperty accessibilityProperty;
    bool ancestorGroupFlag = false;
    auto root = FrameNode::CreateFrameNode(
        V2::BUTTON_ETS_TAG, 12, AceType::MakeRefPtr<Pattern>(), true);
    NG::PointF hoverPoint(0, 0);
    auto result = accessibilityProperty.CreateNodeSearchInfo(root, hoverPoint, ancestorGroupFlag);
    EXPECT_TRUE(root->IsRootNode());

    auto subNode = FrameNode::GetOrCreateFrameNode(
        V2::BUTTON_ETS_TAG, 1, []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    root->AddChild(subNode);
    EXPECT_FALSE(subNode->IsRootNode());
    result = accessibilityProperty.CreateNodeSearchInfo(subNode, hoverPoint, ancestorGroupFlag);
    EXPECT_TRUE(result->Contains("parent"));
    EXPECT_TRUE(result->Contains("visible"));

    auto accessibilityPropertyRoot = root->GetAccessibilityProperty<NG::AccessibilityProperty>();
    EXPECT_NE(accessibilityPropertyRoot, nullptr);
    EXPECT_TRUE(result->Contains("accessibilityLevel"));

    auto subNode3 = FrameNode::GetOrCreateFrameNode(
        V2::BUTTON_ETS_TAG, 4, []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    root->AddChild(subNode3);
    subNode3->SetHitTestMode(HitTestMode::HTMNONE);
    auto result3 = accessibilityProperty.CreateNodeSearchInfo(subNode3, hoverPoint, ancestorGroupFlag);
    EXPECT_TRUE(result3->Contains("hitTestMode"));
    std::string value3 = result3->GetString("hitTestMode");
    EXPECT_EQ(value3, "None");

    auto subNode4 = FrameNode::GetOrCreateFrameNode(
        V2::BUTTON_ETS_TAG, 5, []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    root->AddChild(subNode4);
    subNode4->SetHitTestMode(HitTestMode::HTMTRANSPARENT_SELF);
    auto result4 = accessibilityProperty.CreateNodeSearchInfo(subNode4, hoverPoint, ancestorGroupFlag);
    EXPECT_TRUE(result4->Contains("hitTestMode"));
    std::string value4 = result4->GetString("hitTestMode");
    EXPECT_EQ(value4, "Unsupported");
}

/**
 * @tc.name: AccessibilityPropertyTest030
 * @tc.desc: GetSearchStrategy
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityPropertyTestNg, AccessibilityPropertyTest030, TestSize.Level1)
{
    AccessibilityProperty accessibilityProperty;
    bool ancestorGroupFlag = false;
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::BUTTON_ETS_TAG, 14, []() { return AceType::MakeRefPtr<ButtonPattern>(); });

    auto accessibilityPropertyNew = frameNode->GetAccessibilityProperty<NG::AccessibilityProperty>();
    EXPECT_NE(accessibilityPropertyNew, nullptr);
    auto levelBak = accessibilityPropertyNew->GetAccessibilityLevel();
    accessibilityPropertyNew->SetAccessibilityLevel(AccessibilityProperty::Level::YES_STR);
    auto result = accessibilityProperty.GetSearchStrategy(frameNode, ancestorGroupFlag);
    EXPECT_EQ(result, std::make_tuple(true, true, false));

    bool hasGroupOrVirtualNodeBak = accessibilityPropertyNew->IsAccessibilityGroup();
    result = accessibilityProperty.GetSearchStrategy(frameNode, ancestorGroupFlag);
    EXPECT_EQ(result, std::make_tuple(true, true, false));

    accessibilityPropertyNew->SetAccessibilityGroup(true);
    result = accessibilityProperty.GetSearchStrategy(frameNode, ancestorGroupFlag);
    EXPECT_EQ(result, std::make_tuple(true, true, true));
    accessibilityPropertyNew->SetAccessibilityGroup(hasGroupOrVirtualNodeBak);

    accessibilityPropertyNew->SetAccessibilityText("test");
    bool hasAccessibilityText = accessibilityPropertyNew->HasAccessibilityTextOrDescription();
    EXPECT_TRUE(hasAccessibilityText);
    result = accessibilityPropertyNew->GetSearchStrategy(frameNode, ancestorGroupFlag);
    EXPECT_EQ(result, std::make_tuple(true, true, false));
    accessibilityPropertyNew->SetAccessibilityLevel(levelBak);

    frameNode->accessibilityProperty_ = nullptr;
    auto accessibilityProperty2 = frameNode->GetAccessibilityProperty<NG::AccessibilityProperty>();
    EXPECT_EQ(accessibilityProperty2, nullptr);

    auto eventHub = frameNode->GetOrCreateEventHub<EventHub>();
    eventHub->SetEnabled(false);
    EXPECT_FALSE(eventHub->IsEnabled());
    result = accessibilityProperty.GetSearchStrategy(frameNode, ancestorGroupFlag);
    EXPECT_EQ(result, std::make_tuple(true, false, false));

    frameNode->SetHitTestMode(HitTestMode::HTMBLOCK);
    result = accessibilityProperty.GetSearchStrategy(frameNode, ancestorGroupFlag);
    EXPECT_EQ(result, std::make_tuple(true, false, false));

    frameNode->SetHitTestMode(HitTestMode::HTMTRANSPARENT);
    result = accessibilityProperty.GetSearchStrategy(frameNode, ancestorGroupFlag);
    EXPECT_EQ(result, std::make_tuple(true, false, false));

    frameNode->SetHitTestMode(HitTestMode::HTMNONE);
    result = accessibilityProperty.GetSearchStrategy(frameNode, ancestorGroupFlag);
    EXPECT_EQ(result, std::make_tuple(false, false, false));
}

/**
 * @tc.name: AccessibilityPropertyTest031
 * @tc.desc: GetSearchStrategy
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityPropertyTestNg, AccessibilityPropertyTest031, TestSize.Level1)
{
    bool ancestorGroupFlag = true;
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::BUTTON_ETS_TAG, 14, []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    auto vNode = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(true));
    auto vChildNode = FrameNode::CreateFrameNode(V2::BUTTON_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<ButtonPattern>());
    vNode->AddChild(vChildNode);
    auto accessibilityProperty = frameNode->GetAccessibilityProperty<AccessibilityProperty>();
    accessibilityProperty->SetAccessibilityLevel("yes");
    accessibilityProperty->SetAccessibilityGroup(false);
    accessibilityProperty->SaveAccessibilityVirtualNode(vNode);

    auto result = accessibilityProperty->GetSearchStrategy(frameNode, ancestorGroupFlag);
    EXPECT_EQ(accessibilityProperty->HasAccessibilityVirtualNode(), true);
    EXPECT_EQ(result, std::make_tuple(true, true, true));
}

/**
 * @tc.name: AccessibilityPropertyTest032
 * @tc.desc: ProcessHoverTestRecursive
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityPropertyTestNg, AccessibilityPropertyTest032, TestSize.Level1)
{
    AccessibilityProperty accessibilityProperty;
    AccessibilityHoverTestPath path;
    auto root = FrameNode::GetOrCreateFrameNode(
        V2::BUTTON_ETS_TAG, 13, []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    NG::PointF hoverPoint(0, 0);
    auto debugInfo = std::make_unique<AccessibilityProperty::HoverTestDebugTraceInfo>();
    AccessibilityProperty::RecursiveParam recursiveParam;
    recursiveParam.hitTarget = true;
    recursiveParam.ancestorGroupFlag = true;
    auto result = accessibilityProperty.ProcessHoverTestRecursive(hoverPoint, root, path, debugInfo, recursiveParam);
    EXPECT_EQ(result, true);
}

/**
 * @tc.name: AccessibilityPropertyTest033
 * @tc.desc: IsAccessibilityCompInResponseRegion
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityPropertyTestNg, AccessibilityPropertyTest033, TestSize.Level1)
{
    AccessibilityProperty accessibilityProperty;
    RectF rect1 = RectF(0.0f, 0.0f, 100.0f, 100.0f);
    RectF rect2 = RectF(-10.0f, -10.0f, 100.0f, 100.0f);
    RectF origRect1 = RectF(-10.0f, 0.0f, 100.0f, 100.0f);
    RectF origRect2 = RectF(0.0f, -10.0f, 100.0f, 100.0f);
    RectF origRect3 = RectF(0.0f, 0.0f, 200.0f, 100.0f);
    RectF origRect4 = RectF(0.0f, 0.0f, 100.0f, 200.0f);
    RectF origRect5 = RectF(0.0f, 0.0f, 50.0f, 50.0f);
    RectF origRect6 = RectF(0.0f, 0.0f, 50.0f, 50.0f);
    auto result = accessibilityProperty.IsAccessibilityCompInResponseRegion(rect1, origRect1);
    EXPECT_EQ(result, false);

    auto result1 = accessibilityProperty.IsAccessibilityCompInResponseRegion(rect1, origRect2);
    EXPECT_EQ(result1, false);

    auto result2 = accessibilityProperty.IsAccessibilityCompInResponseRegion(rect1, origRect3);
    EXPECT_EQ(result2, false);

    auto result3 = accessibilityProperty.IsAccessibilityCompInResponseRegion(rect1, origRect4);
    EXPECT_EQ(result3, false);

    auto result4 = accessibilityProperty.IsAccessibilityCompInResponseRegion(rect1, origRect5);
    EXPECT_EQ(result4, true);

    auto result5 = accessibilityProperty.IsAccessibilityCompInResponseRegion(rect2, origRect6);
    EXPECT_EQ(result5, true);
}

/**
 * @tc.name: AccessibilityPropertyTest034
 * @tc.desc: IsMatchAccessibilityResponseRegion
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityPropertyTestNg, AccessibilityPropertyTest034, TestSize.Level1)
{
    AccessibilityProperty accessibilityProperty;
    auto host = FrameNode::GetOrCreateFrameNode(
        V2::BUTTON_ETS_TAG, 1, []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    host->isActive_ = true;
    DimensionRect responseRect(Dimension(-1), Dimension(-1), DimensionOffset(OFFSETF));
    std::vector<DimensionRect> responseRegion;
    responseRegion.push_back(responseRect);
    auto gestureEventHub = host->GetOrCreateEventHub<EventHub>()->GetOrCreateGestureEventHub();
    gestureEventHub->SetResponseRegion(responseRegion);
    auto paintRect = host->renderContext_->GetPaintRectWithoutTransform();
    auto responseRegionList = host->GetResponseRegionList(paintRect, 2);
    EXPECT_FALSE(responseRegionList.size() != 1);

    auto rect = responseRegionList.back();
    EXPECT_FALSE(rect == paintRect);

    EXPECT_FALSE(!accessibilityProperty.IsAccessibilityCompInResponseRegion(rect, paintRect));

    WeakPtr<FrameNode> hostBak = host;
    accessibilityProperty.SetHost(hostBak);
    auto result = accessibilityProperty.IsMatchAccessibilityResponseRegion(false);
    EXPECT_EQ(result, true);
}

/**
 * @tc.name: AccessibilityPropertyTest035
 * @tc.desc: IsMatchAccessibilityResponseRegion
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityPropertyTestNg, AccessibilityPropertyTest035, TestSize.Level1)
{
    AccessibilityProperty accessibilityProperty;
    auto host = FrameNode::GetOrCreateFrameNode(
        V2::BUTTON_ETS_TAG, 1, []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    host->isActive_ = true;
    auto paintRect = host->GetTransformRectRelativeToWindow();
    DimensionRect responseRect(Dimension(-1), Dimension(-1), DimensionOffset(OFFSETF));
    std::vector<DimensionRect> responseRegion;
    responseRegion.push_back(responseRect);
    auto gestureEventHub = host->GetOrCreateEventHub<EventHub>()->GetOrCreateGestureEventHub();
    gestureEventHub->SetResponseRegion(responseRegion);

    auto responseRegionList = host->GetResponseRegionList(paintRect, 2);
    EXPECT_FALSE(responseRegionList.size() != 1);

    auto rect = responseRegionList.back();
    EXPECT_FALSE(rect == paintRect);

    EXPECT_FALSE(!accessibilityProperty.IsAccessibilityCompInResponseRegion(rect, paintRect));

    WeakPtr<FrameNode> hostBak = host;
    accessibilityProperty.SetHost(hostBak);
    auto result = accessibilityProperty.IsMatchAccessibilityResponseRegion(false);
    EXPECT_EQ(result, true);
}

/**
 * @tc.name: AccessibilityPropertyTest036
 * @tc.desc: GetAccessibilityResponseRegionRect
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityPropertyTestNg, AccessibilityPropertyTest036, TestSize.Level1)
{
    NG::RectT<int32_t> rectInt = RectT<int32_t>(0, 0, 0, 0);
    AccessibilityProperty accessibilityProperty;
    auto host = FrameNode::GetOrCreateFrameNode(
        V2::BUTTON_ETS_TAG, 1, []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    host->isActive_ = true;
    WeakPtr<FrameNode> hostBak = host;
    accessibilityProperty.SetHost(hostBak);

    auto result = accessibilityProperty.GetAccessibilityResponseRegionRect(false);
    EXPECT_EQ(result, rectInt);

    auto result1 = accessibilityProperty.GetAccessibilityResponseRegionRect(true);
    EXPECT_EQ(result1, rectInt);
}

/**
 * @tc.name: AccessibilityPropertyTest037
 * @tc.desc: AccessibilityRole
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityPropertyTestNg, AccessibilityPropertyTest037, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    AccessibilityProperty accessibilityProperty;
    ViewAbstractModelNG viewAbstractModelNG;
    const std::string role = "";
    viewAbstractModelNG.SetAccessibilityRole(role, true);
    EXPECT_EQ(accessibilityProperty.GetAccessibilityCustomRole(), "");
    accessibilityProperty.SetAccessibilityCustomRole(role);
    EXPECT_EQ(accessibilityProperty.GetAccessibilityCustomRole(), role);
    accessibilityProperty.ResetAccessibilityCustomRole();
    EXPECT_EQ(accessibilityProperty.GetAccessibilityCustomRole(), "");

    const std::string customrole = "IMAGE";
    viewAbstractModelNG.SetAccessibilityRole(customrole, false);
    EXPECT_EQ(accessibilityProperty.GetAccessibilityCustomRole(), customrole);
}

/**
 * @tc.name: AccessibilityPropertyTest038
 * @tc.desc: OnAccessibilityFocus
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityPropertyTestNg, AccessibilityPropertyTest038, TestSize.Level1)
{
    AccessibilityProperty accessibilityProperty;
    ViewAbstractModelNG viewAbstractModelNG;
    viewAbstractModelNG.ResetOnAccessibilityFocus();
    EXPECT_EQ(accessibilityProperty.onUserAccessibilityFocusCallbackImpl_, nullptr);
}

/**
 * @tc.name: AccessibilityPropertyTest039
 * @tc.desc: SetAccessibilityNextFocusInspectorKey and GetAccessibilityNextFocusInspectorKey
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityPropertyTestNg, AccessibilityPropertyTest039, TestSize.Level1)
{
    AccessibilityProperty accessibilityProperty;
    const std::string nextFocusId = "nextId";
    accessibilityProperty.SetAccessibilityNextFocusInspectorKey(nextFocusId);
    EXPECT_EQ(accessibilityProperty.GetAccessibilityNextFocusInspectorKey(), nextFocusId);
}

/**
 * @tc.name: AccessibilityPropertyTest040
 * @tc.desc: SetAccessibilitySamePage, HasAccessibilitySamePage and GetAccessibilitySamePage
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityPropertyTestNg, AccessibilityPropertyTest040, TestSize.Level1)
{
    AccessibilityProperty accessibilityProperty;
    const std::string pageMode = "FULL_SILENT";
    accessibilityProperty.SetAccessibilitySamePage(pageMode);
    EXPECT_TRUE(accessibilityProperty.HasAccessibilitySamePage());
    EXPECT_EQ(accessibilityProperty.GetAccessibilitySamePage(), pageMode);
}

/**
 * @tc.name: AccessibilityPropertyTest041
 * @tc.desc: SetAccessibilitySamePage, HasAccessibilitySamePage and IsAccessibilityTextPreferred
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityPropertyTestNg, AccessibilityPropertyTest041, TestSize.Level1)
{
    AccessibilityProperty accessibilityProperty;
    const std::string pageMode = "FULL_SILENT";
    accessibilityProperty.SetAccessibilitySamePage(pageMode);
    EXPECT_TRUE(accessibilityProperty.HasAccessibilitySamePage());
    accessibilityProperty.SetAccessibilityTextPreferred(true);
    EXPECT_TRUE(accessibilityProperty.IsAccessibilityTextPreferred());
    accessibilityProperty.SetAccessibilityTextPreferred(false);
    EXPECT_FALSE(accessibilityProperty.IsAccessibilityTextPreferred());
}

/**
 * @tc.name: AccessibilityPropertyTest042
 * @tc.desc: IsMatchAccessibilityResponseRegion
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityPropertyTestNg, AccessibilityPropertyTest042, TestSize.Level1)
{
    AccessibilityProperty accessibilityProperty;
    auto host = FrameNode::GetOrCreateFrameNode(
        V2::BUTTON_ETS_TAG, 1, []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    host->isActive_ = true;
    auto paintRect = host->GetTransformRectRelativeToWindow();
    auto responseRegionList = host->GetResponseRegionList(paintRect, 2);
    EXPECT_FALSE(responseRegionList.size() != 1);

    auto rect = responseRegionList.back();
    EXPECT_TRUE(rect == paintRect);

    WeakPtr<FrameNode> hostBak = host;
    accessibilityProperty.SetHost(hostBak);
    auto result = accessibilityProperty.IsMatchAccessibilityResponseRegion(false);
    EXPECT_EQ(result, true);

    accessibilityProperty.focusDrawLevel_ = FocusDrawLevel::TOP;
    result = accessibilityProperty.IsMatchAccessibilityResponseRegion(false);
    EXPECT_EQ(result, false);
}
} // namespace OHOS::Ace::NG
