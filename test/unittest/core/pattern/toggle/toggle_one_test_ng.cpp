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
#define protected public
#define private public
#include "base/geometry/dimension.h"
#include "core/components/checkable/checkable_theme.h"
#include "core/components/toggle/toggle_theme.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/button/toggle_button_event_hub.h"
#include "core/components_ng/pattern/button/toggle_button_paint_property.h"
#include "core/components_ng/pattern/button/toggle_button_pattern.h"
#include "core/components_ng/pattern/checkbox/checkbox_event_hub.h"
#include "core/components_ng/pattern/checkbox/checkbox_paint_property.h"
#include "core/components_ng/pattern/checkbox/checkbox_pattern.h"
#include "core/components_ng/pattern/toggle/switch_event_hub.h"
#include "core/components_ng/pattern/toggle/switch_paint_method.h"
#include "core/components_ng/pattern/toggle/switch_paint_property.h"
#include "core/components_ng/pattern/toggle/switch_pattern.h"
#include "core/components_ng/pattern/toggle/toggle_model.h"
#include "core/components_ng/pattern/toggle/toggle_model_ng.h"
#include "test/mock/base/mock_system_properties.h"
#include "test/mock/core/rosen/mock_canvas.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "core/components_ng/pattern/root/root_pattern.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
namespace {
constexpr bool IS_ON = true;
constexpr float CONTAINER_WIDTH = 200.0f;
constexpr float CONTAINER_HEIGHT = 100.0f;
constexpr Color SELECTED_COLOR = Color(0XFFFF0000);
constexpr Dimension TOGGLE_WIDTH = 60.0_px;
constexpr float SWITCH_WIDTH = 100.0f;
constexpr float SWITCH_HEIGHT = 50.0f;
const SizeF CONTAINER_SIZE(CONTAINER_WIDTH, CONTAINER_HEIGHT);
const std::vector<NG::ToggleType> TOGGLE_TYPE = { ToggleType::CHECKBOX, ToggleType::BUTTON, ToggleType::SWITCH };
} // namespace

class ToggleOneTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();

protected:
    static PaddingPropertyF CreatePadding(Dimension length);
};

void ToggleOneTestNg::SetUpTestCase()
{
    MockPipelineContext::SetUp();
}

void ToggleOneTestNg::TearDownTestCase()
{
    MockPipelineContext::TearDown();
}

PaddingPropertyF ToggleOneTestNg::CreatePadding(Dimension length)
{
    PaddingPropertyF padding;
    padding.left = length.ConvertToPx();
    padding.right = length.ConvertToPx();
    padding.top = length.ConvertToPx();
    padding.bottom = length.ConvertToPx();
    return padding;
}

/**
 * @tc.name: ToggleModelTest003
 * @tc.desc: Test toggle create.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleOneTestNg, ToggleModelTest003, TestSize.Level1)
{
    const RefPtr<FrameNode> frameParent = FrameNode::CreateFrameNode("parent", 0, AceType::MakeRefPtr<Pattern>(), true);
    ViewStackProcessor::GetInstance()->StartGetAccessRecordingFor(100);
    /**
     * @tc.steps: step1. create ToggleButton and get frameNode.
     */
    ToggleModelNG toggleModelNG;
    toggleModelNG.Create(TOGGLE_TYPE[1], IS_ON);
    auto switchFrameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(switchFrameNode, nullptr);
    EXPECT_EQ(switchFrameNode->GetId(), 100);
    switchFrameNode->SetParent(frameParent);
    /**
     * Create again,cover all branches in function Create for ToggleButton
     */
    ViewStackProcessor::GetInstance()->StartGetAccessRecordingFor(100);
    toggleModelNG.Create(TOGGLE_TYPE[1], IS_ON);
    ViewStackProcessor::GetInstance()->StartGetAccessRecordingFor(100);
    toggleModelNG.Create(TOGGLE_TYPE[0], IS_ON);
    ViewStackProcessor::GetInstance()->StartGetAccessRecordingFor(100);
    toggleModelNG.Create(TOGGLE_TYPE[1], IS_ON);
    ViewStackProcessor::GetInstance()->StartGetAccessRecordingFor(100);
    toggleModelNG.Create(TOGGLE_TYPE[2], IS_ON);
}

/**
 * @tc.name: TogglePatternTest0019
 * @tc.desc: Test toggle HandleDragEnd.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleOneTestNg, TogglePatternTest0019, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create switch and get frameNode.
     */
    ToggleModelNG toggleModelNG;
    toggleModelNG.Create(TOGGLE_TYPE[2], IS_ON);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<SwitchPattern>();
    ASSERT_NE(pattern, nullptr);
    auto geometryNode = frameNode->GetGeometryNode();
    geometryNode->SetContentSize(SizeF(SWITCH_WIDTH, SWITCH_HEIGHT));
    /**
     * @tc.steps: step2. call function HandleDragEnd.
     */
    pattern->dragOffsetX_ = 0;
    pattern->HandleDragEnd();
    pattern->dragOffsetX_ = SWITCH_WIDTH;
    pattern->HandleDragEnd();
    EXPECT_FALSE(pattern->isDragEvent_);
    /**
     * cover isOn_ == false branch.
     */
    pattern->isOn_ = false;
    pattern->HandleDragEnd();
    pattern->dragOffsetX_ = 0;
    pattern->HandleDragEnd();
    EXPECT_FALSE(pattern->isDragEvent_);
}

/**
 * @tc.name: TogglePatternTest020
 * @tc.desc: Switch test Select and ClearSelection.
 */
HWTEST_F(ToggleOneTestNg, TogglePatternTest020, TestSize.Level1)
{
    ToggleModelNG toggleModelNG;
    toggleModelNG.Create(TOGGLE_TYPE[2], IS_ON);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<SwitchPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->isOn_ = false;
    pattern->SetAccessibilityAction();

    auto accessibilityProperty = frameNode->GetAccessibilityProperty<SwitchAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    EXPECT_TRUE(accessibilityProperty->ActActionSelect());

    bool isSelected = true;
    pattern->isOn_ = false;
    pattern->UpdateSelectStatus(isSelected);
    EXPECT_TRUE(accessibilityProperty->ActActionClearSelection());
}

/**
 * @tc.name: ToggleModelTest004
 * @tc.desc: Test checkbox create twice.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleOneTestNg, ToggleModelTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create the first checkbox.
     */
    ViewStackProcessor::GetInstance()->StartGetAccessRecordingFor(100);
    ToggleModelNG toggleModelNG;
    toggleModelNG.Create(TOGGLE_TYPE[0], IS_ON);
    auto checkboxNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(checkboxNode, nullptr);
    EXPECT_EQ(checkboxNode->GetId(), 100);
    /**
     * @tc.steps: step2. create the second checkbox.
     */
    ViewStackProcessor::GetInstance()->StartGetAccessRecordingFor(100);
    toggleModelNG.Create(TOGGLE_TYPE[0], IS_ON);
}

/**
 * @tc.name: ToggleModelTest005
 * @tc.desc: Test ToggleButton create twice.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleOneTestNg, ToggleModelTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create the first ToggleButton.
     */
    ViewStackProcessor::GetInstance()->StartGetAccessRecordingFor(100);
    ToggleModelNG toggleModelNG;
    toggleModelNG.Create(TOGGLE_TYPE[1], IS_ON);
    auto buttonNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(buttonNode, nullptr);
    EXPECT_EQ(buttonNode->GetId(), 100);
    /**
     * @tc.steps: step2. create the second ToggleButton.
     */
    ViewStackProcessor::GetInstance()->StartGetAccessRecordingFor(100);
    toggleModelNG.Create(TOGGLE_TYPE[1], IS_ON);
}

/**
 * @tc.name: ToggleModelTest006
 * @tc.desc: Test OnChangeEvent.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleOneTestNg, ToggleModelTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. generate ChangeEvent.
     */
    ChangeEvent changeEvent;
    /**
     * @tc.steps: step2. create checkbox toggle and trigger OnChangeEvent.
     */
    ToggleModelNG toggleModelNG;
    toggleModelNG.Create(TOGGLE_TYPE[0], IS_ON);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    toggleModelNG.OnChangeEvent(std::move(changeEvent));
    /**
     * @tc.steps: step3. create ToggleButton and trigger OnChangeEvent.
     */
    ToggleModelNG toggleModelNG2;
    toggleModelNG2.Create(TOGGLE_TYPE[1], IS_ON);
    frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    toggleModelNG2.OnChangeEvent(std::move(changeEvent));
    /**
     * @tc.steps: step4. create switch toggle and trigger OnChangeEvent.
     */
    ToggleModelNG toggleModelNG3;
    toggleModelNG3.Create(TOGGLE_TYPE[2], IS_ON);
    frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    toggleModelNG3.OnChangeEvent(std::move(changeEvent));
}

/**
 * @tc.name: ToggleModelDistributedTest001
 * @tc.desc: Test the distributed capability of Toggle
 * @tc.type: FUNC
 */
HWTEST_F(ToggleOneTestNg, ToggleModelDistributedTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create switch and get frameNode.
     */
    ToggleModelNG toggleModelNG;
    toggleModelNG.Create(TOGGLE_TYPE[2], IS_ON);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<SwitchPattern>();
    ASSERT_NE(pattern, nullptr);
    auto switchPaintProperty = pattern->GetPaintProperty<SwitchPaintProperty>();
    ASSERT_NE(switchPaintProperty, nullptr);

    /**
     * @tc.expected: Function ProvideRestoreInfo is called.
     */
    pattern->isOn_ = false;
    std::string ret = pattern->ProvideRestoreInfo();
    EXPECT_TRUE(ret == R"({"IsOn":false})");

    /**
     * @tc.steps: step3. Function OnRestoreInfo is called.
     * @tc.expected: Passing invalid & valid JSON format.
     */
    std::string restoreInfo_ = R"({"IsOn":true})";
    pattern->OnRestoreInfo(restoreInfo_);
    EXPECT_TRUE(switchPaintProperty->GetIsOnValue(false));
    restoreInfo_ = "invalid_json_string";
    pattern->OnRestoreInfo(restoreInfo_);
    ASSERT_NE(switchPaintProperty, nullptr);
    EXPECT_TRUE(switchPaintProperty->GetIsOnValue(false));
}

/**
 * @tc.name: ToggleAccessibilityPropertyTestNg001
 * @tc.desc: Test the IsCheckable and IsChecked properties of ToggleButton.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleOneTestNg, ToggleAccessibilityPropertyTestNg001, TestSize.Level1)
{
    ToggleModelNG toggleModelNG;
    toggleModelNG.Create(ToggleType::BUTTON, true);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);

    auto accessibility = frameNode->GetAccessibilityProperty<ToggleButtonAccessibilityProperty>();
    ASSERT_NE(accessibility, nullptr);
    EXPECT_TRUE(accessibility->IsCheckable());
    EXPECT_TRUE(accessibility->IsChecked());

    auto paintProperty = frameNode->GetPaintProperty<ToggleButtonPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    paintProperty->UpdateIsOn(false);
    EXPECT_FALSE(accessibility->IsChecked());
}

/**
 * @tc.name: ToggleAccessibilityPropertyTestNg002
 * @tc.desc: Test the IsCheckable and IsChecked properties of Switch.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleOneTestNg, ToggleAccessibilityPropertyTestNg002, TestSize.Level1)
{
    ToggleModelNG toggleModelNG;
    toggleModelNG.Create(ToggleType::SWITCH, true);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);

    auto accessibility = frameNode->GetAccessibilityProperty<SwitchAccessibilityProperty>();
    ASSERT_NE(accessibility, nullptr);
    EXPECT_TRUE(accessibility->IsCheckable());

    auto pattern = AceType::DynamicCast<SwitchPattern>(frameNode->GetPattern());
    ASSERT_NE(pattern, nullptr);
    pattern->isOn_ = false;
    EXPECT_FALSE(accessibility->IsChecked());

    pattern->isOn_ = true;
    EXPECT_TRUE(accessibility->IsChecked());
}

/**
 * @tc.name: SwitchPatternTest001
 * @tc.desc: Test the IsCheckable and IsChecked properties of Switch.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleOneTestNg, SwitchPatternTest001, TestSize.Level1)
{
    ToggleModelNG toggleModelNG;
    toggleModelNG.Create(ToggleType::SWITCH, true);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);

    auto accessibility = frameNode->GetAccessibilityProperty<SwitchAccessibilityProperty>();
    ASSERT_NE(accessibility, nullptr);
    EXPECT_TRUE(accessibility->IsCheckable());

    auto pattern = AceType::DynamicCast<SwitchPattern>(frameNode->GetPattern());
    ASSERT_NE(pattern, nullptr);
    pattern->isOn_ = false;
    EXPECT_FALSE(accessibility->IsChecked());

    pattern->isOn_ = true;
    EXPECT_TRUE(accessibility->IsChecked());

    pattern->OnAfterModifyDone();
}

/**
 * @tc.name: ToggleModelTest007
 * @tc.desc: Test ToggleModelNG::ReplaceAllChild
 * @tc.type: FUNC
 */
HWTEST_F(ToggleOneTestNg, ToggleModelTest007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create toggle and get frameNode.
     */
    ToggleModelNG toggleModelNG;
    toggleModelNG.CreateFrameNode(0, ToggleType::CHECKBOX, true);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    /**
     * @tc.steps: step2. create oldframenode with RootPattern and call ReplaceAllChild.
     */
    auto oldFrameNodeRoot = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    auto childRootNode = FrameNode::CreateFrameNode(V2::BUTTON_ETS_TAG, 1, AceType::MakeRefPtr<ButtonPattern>());
    childRootNode->MountToParent(oldFrameNodeRoot);
    toggleModelNG.ReplaceAllChild(oldFrameNodeRoot);
    auto children = oldFrameNodeRoot->GetChildren();
    EXPECT_EQ(children.size(), 1);
}

/**
 * @tc.name: ToggleModelTest008
 * @tc.desc: Test ToggleModelNG::ReplaceAllChild
 * @tc.type: FUNC
 */
HWTEST_F(ToggleOneTestNg, ToggleModelTest008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create toggle and get frameNode.
     */
    ToggleModelNG toggleModelNG;
    toggleModelNG.CreateFrameNode(1, ToggleType::CHECKBOX, true);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    /**
     * @tc.steps: step2 - 1. create oldframenode with switchPattern and call ReplaceAllChild.
     */
    auto oldFrameNodeSwitch = FrameNode::CreateFrameNode(V2::SWITCH_ETS_TAG, 1, AceType::MakeRefPtr<SwitchPattern>());
    auto childNode = FrameNode::CreateFrameNode(V2::ROW_ETS_TAG, 1, AceType::MakeRefPtr<ButtonPattern>());
    childNode->MountToParent(oldFrameNodeSwitch);
    auto switchPattern = oldFrameNodeSwitch->GetPattern<SwitchPattern>();
    ASSERT_NE(switchPattern, nullptr);
    auto modifierNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    switchPattern->contentModifierNode_ = modifierNode;
    switchPattern->nodeId_ = childNode->GetId();
    toggleModelNG.ReplaceAllChild(oldFrameNodeSwitch);
    auto children = oldFrameNodeSwitch->GetChildren();
    EXPECT_EQ(children.size(), 1);
}

/**
 * @tc.name: ToggleModelTest009
 * @tc.desc: Test ToggleModelNG::ReplaceAllChild
 * @tc.type: FUNC
 */
HWTEST_F(ToggleOneTestNg, ToggleModelTest009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create toggle and get frameNode.
     */
    ToggleModelNG toggleModelNG;
    toggleModelNG.CreateFrameNode(0, ToggleType::SWITCH, true);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    /**
     * @tc.steps: step2 - 2. create oldframenode with checkboxPattern and call ReplaceAllChild.
     */
    auto oldFrameNodeCheckbox =
        FrameNode::CreateFrameNode(V2::CHECKBOX_ETS_TAG, 1, AceType::MakeRefPtr<CheckBoxPattern>());
    auto childCheckboxNode = FrameNode::CreateFrameNode(V2::BUTTON_ETS_TAG, 1, AceType::MakeRefPtr<ButtonPattern>());
    childCheckboxNode->MountToParent(oldFrameNodeCheckbox);
    auto checkboxPattern = oldFrameNodeCheckbox->GetPattern<CheckBoxPattern>();
    ASSERT_NE(checkboxPattern, nullptr);
    auto modifierNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    checkboxPattern->contentModifierNode_ = modifierNode;
    toggleModelNG.ReplaceAllChild(oldFrameNodeCheckbox);
    auto children = oldFrameNodeCheckbox->GetChildren();
    EXPECT_EQ(children.size(), 1);
}

/**
 * @tc.name: ToggleModelTest010
 * @tc.desc: Test ToggleModelNG::ReplaceAllChild
 * @tc.type: FUNC
 */
HWTEST_F(ToggleOneTestNg, ToggleModelTest010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create toggle and get frameNode.
     */
    ToggleModelNG toggleModelNG;
    toggleModelNG.CreateFrameNode(0, ToggleType::SWITCH, true);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    /**
     * @tc.steps: step2 - 3. create oldframenode with toggleButtonPattern and call ReplaceAllChild.
     */
    auto oldFrameNodeToggle =
        FrameNode::CreateFrameNode(V2::TOGGLE_ETS_TAG, 1, AceType::MakeRefPtr<ToggleButtonPattern>());
    auto childToggleNode = FrameNode::CreateFrameNode(V2::BUTTON_ETS_TAG, 1, AceType::MakeRefPtr<ButtonPattern>());
    childToggleNode->MountToParent(oldFrameNodeToggle);
    auto togglePattern = oldFrameNodeToggle->GetPattern<ToggleButtonPattern>();
    ASSERT_NE(togglePattern, nullptr);
    auto modifierNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    togglePattern->contentModifierNode_ = modifierNode;
    togglePattern->nodeId_ = childToggleNode->GetId();
    toggleModelNG.ReplaceAllChild(oldFrameNodeToggle);
    auto children = oldFrameNodeToggle->GetChildren();
    EXPECT_EQ(children.size(), 1);
}

/**
 * @tc.name: ToggleModelTest011
 * @tc.desc: Test ToggleModelNG::SetUnselectedColor
 * @tc.type: FUNC
 */
HWTEST_F(ToggleOneTestNg, ToggleModelTest011, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create toggle and get frameNode.
     */
    ToggleModelNG toggleModelNG;
    toggleModelNG.Create(TOGGLE_TYPE[2], IS_ON);
    auto switchFrameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(switchFrameNode, nullptr);
    /**
     * @tc.steps: step2. set Modifer.
     */
    ToggleModelNG toggleModelNGEx;
    toggleModelNGEx.SetUnselectedColor(AceType::RawPtr(switchFrameNode), SELECTED_COLOR);
    toggleModelNGEx.SetTrackBorderRadius(AceType::RawPtr(switchFrameNode), TOGGLE_WIDTH);
    toggleModelNGEx.ResetTrackBorderRadius(AceType::RawPtr(switchFrameNode));
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
}

/**
 * @tc.name: ToggleModelTest012
 * @tc.desc: Test ToggleModelNG::CreateTypeNode and ToggleModelNG::SetToggleState
 * @tc.type: FUNC
 */
HWTEST_F(ToggleOneTestNg, ToggleModelTest012, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init Toggle node.
     */
    ToggleModelNG toggleModelNG;
    toggleModelNG.Create(ToggleType::CHECKBOX, false);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. SetToggleState.
     */
    auto node = AceType::RawPtr(frameNode);
    ASSERT_NE(node, nullptr);
    ToggleModelNG::SetToggleState(node, true);

    /**
     * @tc.steps: step3. assert ToggleState.
     */
    auto paintProperty = frameNode->GetPaintProperty<CheckBoxPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    EXPECT_EQ(paintProperty->GetCheckBoxSelectValue(), true);
}

/**
 * @tc.name: ToggleModelTest013
 * @tc.desc: Test InitOnKeyEvent().
 * @tc.type: FUNC
 */
HWTEST_F(ToggleOneTestNg, ToggleModelTest013, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create switch and get frameNode.
     */
    ToggleModelNG toggleModelNG;
    toggleModelNG.Create(TOGGLE_TYPE[2], IS_ON);
    auto switchFrameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(switchFrameNode, nullptr);
    switchFrameNode->MarkModifyDone();
    auto eventHub = switchFrameNode->GetFocusHub();
    ASSERT_NE(eventHub, nullptr);
    /**
     * @tc.steps: step2. test event.action != KeyAction::DOWN and event.code == KeyCode::KEY_FUNCTION
     * @tc.expected: step3. check the switch checked status
     */
    KeyEvent keyEventOne(KeyCode::KEY_FUNCTION, KeyAction::UP);
    bool ret = eventHub->ProcessOnKeyEventInternal(keyEventOne);
    auto pattern = AceType::DynamicCast<SwitchPattern>(switchFrameNode->GetPattern());
    EXPECT_FALSE(ret);
    bool isChecked = pattern->IsChecked();
    EXPECT_EQ(isChecked, IS_ON);
    /**
     * @tc.steps: step4. test event.action == KeyAction::DOWN and event.code != KeyCode::KEY_FUNCTION
     * @tc.expected: step5. check the checked status
     */
    KeyEvent keyEventTwo(KeyCode::KEY_A, KeyAction::DOWN);
    ret = eventHub->ProcessOnKeyEventInternal(keyEventTwo);
    EXPECT_FALSE(ret);
    isChecked = pattern->IsChecked();
    EXPECT_EQ(isChecked, IS_ON);
    /**
     * @tc.steps: step4. test event.action != KeyAction::DOWN and event.code != KeyCode::KEY_FUNCTION
     * @tc.expected: step5. check the checked status
     */
    KeyEvent keyEventThree(KeyCode::KEY_F1, KeyAction::UP);
    ret = eventHub->ProcessOnKeyEventInternal(keyEventThree);
    EXPECT_FALSE(ret);
    isChecked = pattern->IsChecked();
    EXPECT_EQ(isChecked, IS_ON);
    /**
     * @tc.steps: step4. test event.action == KeyAction::DOWN and event.code == KeyCode::KEY_FUNCTION
     * @tc.expected: step5. check the checked status
     */
    KeyEvent keyEventFour(KeyCode::KEY_FUNCTION, KeyAction::DOWN);
    ret = eventHub->ProcessOnKeyEventInternal(keyEventFour);
    EXPECT_TRUE(ret);
    isChecked = pattern->IsChecked();
    EXPECT_EQ(isChecked, !IS_ON);
}

/**
 * @tc.name: SetSelectedColor001
 * @tc.desc: Test SetSelectedColor() for CheckBox.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleOneTestNg, SetSelectedColor001, TestSize.Level1)
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<CheckboxTheme>()));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(AceType::MakeRefPtr<CheckboxTheme>()));
    /**
     * @tc.steps: step1. Create checkbox and get frameNode.
     */
    ToggleModelNG toggleModelNG;
    toggleModelNG.Create(TOGGLE_TYPE[0], IS_ON);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = AceType::DynamicCast<CheckBoxPattern>(frameNode->GetPattern());
    EXPECT_NE(pattern, nullptr);
    auto paintProperty = pattern->GetPaintProperty<CheckBoxPaintProperty>();
    EXPECT_NE(paintProperty, nullptr);
    std::optional<Color> emptySelectedColor = std::optional<Color>();

    /**
     * @tc.steps: step2. Set valid selected color.
     * @tc.expected: The selected color flag should be true.
     */
    toggleModelNG.SetSelectedColor(frameNode, SELECTED_COLOR);
    EXPECT_TRUE(paintProperty->GetCheckBoxSelectedColorFlagByUserValue(false));

    /**
     * @tc.steps: step3. Set empty selected color.
     * @tc.expected: The selected color flag should still be true.
     */
    toggleModelNG.SetSelectedColor(frameNode, emptySelectedColor);
    EXPECT_TRUE(paintProperty->GetCheckBoxSelectedColorFlagByUserValue(false));

    /**
     * @tc.steps: step4. Set valid selected color with configuration change.
     * @tc.expected: The selected color flag should be true.
     */
    g_isConfigChangePerform = true;
    toggleModelNG.SetSelectedColor(frameNode, SELECTED_COLOR);
    EXPECT_TRUE(paintProperty->GetCheckBoxSelectedColorFlagByUserValue(false));

    /**
     * @tc.steps: step5. Set empty selected color with configuration change.
     * @tc.expected: The selected color flag should be false.
     */
    toggleModelNG.SetSelectedColor(frameNode, emptySelectedColor);
    EXPECT_FALSE(paintProperty->GetCheckBoxSelectedColorFlagByUserValue(true));
    g_isConfigChangePerform = false;
}

/**
 * @tc.name: SetSelectedColor002
 * @tc.desc: Test SetSelectedColor() for Button.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleOneTestNg, SetSelectedColor002, TestSize.Level1)
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<ToggleTheme>()));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(AceType::MakeRefPtr<ToggleTheme>()));
    /**
     * @tc.steps: step1. Create button and get frameNode.
     */
    ToggleModelNG toggleModelNG;
    toggleModelNG.Create(TOGGLE_TYPE[1], IS_ON);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = AceType::DynamicCast<ToggleButtonPattern>(frameNode->GetPattern());
    EXPECT_NE(pattern, nullptr);
    auto paintProperty = pattern->GetPaintProperty<ToggleButtonPaintProperty>();
    EXPECT_NE(paintProperty, nullptr);
    std::optional<Color> emptySelectedColor = std::optional<Color>();

    /**
     * @tc.steps: step2. Set valid selected color.
     * @tc.expected: The selected color flag should be true.
     */
    toggleModelNG.SetSelectedColor(frameNode, SELECTED_COLOR);
    EXPECT_TRUE(paintProperty->GetSelectedColorSetByUserValue(false));

    /**
     * @tc.steps: step3. Set empty selected color.
     * @tc.expected: The selected color flag should still be true.
     */
    toggleModelNG.SetSelectedColor(frameNode, emptySelectedColor);
    EXPECT_TRUE(paintProperty->GetSelectedColorSetByUserValue(false));

    /**
     * @tc.steps: step4. Set valid selected color with configuration change.
     * @tc.expected: The selected color flag should be true.
     */
    g_isConfigChangePerform = true;
    toggleModelNG.SetSelectedColor(frameNode, SELECTED_COLOR);
    EXPECT_TRUE(paintProperty->GetSelectedColorSetByUserValue(false));

    /**
     * @tc.steps: step5. Set empty selected color with configuration change.
     * @tc.expected: The selected color flag should be false.
     */
    toggleModelNG.SetSelectedColor(frameNode, emptySelectedColor);
    EXPECT_FALSE(paintProperty->GetSelectedColorSetByUserValue(true));
    g_isConfigChangePerform = false;
}

/**
 * @tc.name: ColorTypeToStringTest001
 * @tc.desc: test ColorTypeToString.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleOneTestNg, ColorTypeToStringTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Prepare test data pairs of ToggleColorType and expected string values.
     * @tc.expected: step1. Test data contains valid color type to string mappings.
     */
    std::vector<std::pair<ToggleColorType, std::string>> types = { { ToggleColorType::SELECTED_COLOR, "SelectedColor" },
        { ToggleColorType::SWITCH_POINT_COLOR, "SwitchPointColor" },
        { ToggleColorType::UN_SELECTED_COLOR, "UnselectedColor" }, { static_cast<ToggleColorType>(3), "Unknown" } };

    /**
     * @tc.steps: step2. Iterate through each test pair and call ColorTypeToString.
     * @tc.expected: step2. The function returns the expected string for each color type.
     */
    for (const auto& [type, val] : types) {
        auto ret = ToggleModelNG::ColorTypeToString(type);
        EXPECT_EQ(val, ret);
    }
}

/**
 * @tc.name: DimensionTypeToStringTest001
 * @tc.desc: test DimensionTypeToString.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleOneTestNg, DimensionTypeToStringTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Prepare test data pairs of ToggleDimensionType and expected string values.
     * @tc.expected: step1. Test data contains valid dimension type to string mappings.
     */
    std::vector<std::pair<ToggleDimensionType, std::string>> types = {
        { ToggleDimensionType::POINT_RADIUS, "PointRadius" },
        { ToggleDimensionType::TRACK_BORDER_RADIUS, "TrackBorderRadius" },
        { static_cast<ToggleDimensionType>(2), "Unknown" } };

    /**
     * @tc.steps: step2. Iterate through each test pair and call DimensionTypeToString.
     * @tc.expected: step2. The function returns the expected string for each dimension type.
     */
    for (const auto& [type, val] : types) {
        auto ret = ToggleModelNG::DimensionTypeToString(type);
        EXPECT_EQ(val, ret);
    }
}

/**
 * @tc.name: SetCheckboxDefaultColorTest001
 * @tc.desc: test SetCheckboxDefaultColor.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleOneTestNg, SetCheckboxDefaultColorTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a toggle model and verify frame node and paint property setup.
     * @tc.expected: step1. Frame node and paint property are created and valid, selected color is not set initially.
     */
    ToggleModelNG toggleModelNG;
    toggleModelNG.Create(TOGGLE_TYPE[2], IS_ON);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto paintProperty = frameNode->GetPaintProperty<SwitchPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    auto colorRet = paintProperty->GetSelectedColor();
    EXPECT_FALSE(colorRet.has_value());

    /**
     * @tc.steps: step2. Create a checkbox and mock theme manager to provide checkbox theme.
     * @tc.expected: step2. Checkbox theme is retrieved successfully from the mock manager.
     */
    ToggleModelNG toggleModelNG2;
    toggleModelNG2.Create(TOGGLE_TYPE[0], IS_ON);
    auto checkboxFrameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(checkboxFrameNode, nullptr);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto checkboxTheme = AceType::MakeRefPtr<CheckboxTheme>();
    ASSERT_NE(checkboxTheme, nullptr);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(checkboxTheme));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(checkboxTheme));
    auto color = checkboxTheme->GetActiveColor();

    /**
     * @tc.steps: step3. Test default color setting with invalid and valid color types.
     * @tc.expected: step3. Selected color is updated to theme's active color when valid type is used.
     */
    toggleModelNG.SetCheckboxDefaultColor(checkboxFrameNode, static_cast<ToggleColorType>(3));
    toggleModelNG.SetCheckboxDefaultColor(checkboxFrameNode, ToggleColorType::SELECTED_COLOR);
    colorRet = paintProperty->GetSelectedColor();
    EXPECT_EQ(colorRet.value_or(Color::BLACK), color);
}

/**
 * @tc.name: SetCheckboxDefaultColorTest002
 * @tc.desc: test SetCheckboxDefaultColor.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleOneTestNg, SetCheckboxDefaultColorTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a toggle model and verify frame node and paint property setup.
     * @tc.expected: step1. Frame node and paint property are created and valid, selected color is not set initially.
     */
    ToggleModelNG toggleModelNG;
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto toggleNode = FrameNode::CreateFrameNode(V2::TOGGLE_ETS_TAG, 1, AceType::MakeRefPtr<ToggleButtonPattern>());
    EXPECT_NE(toggleNode, nullptr);
    auto pattern = AceType::DynamicCast<ToggleButtonPattern>(toggleNode->GetPattern());
    EXPECT_NE(pattern, nullptr);
    auto paintProperty = pattern->GetPaintProperty<ToggleButtonPaintProperty>();
    EXPECT_NE(paintProperty, nullptr);
    stack->Push(toggleNode);

    /**
     * @tc.steps: step2. Test default color setting for BACKGROUND_COLOR type.
     * @tc.expected: step2. Background color is reset and no longer has a valid value after setting default color.
     */
    paintProperty->UpdateBackgroundColor(Color::BLACK);
    EXPECT_TRUE(paintProperty->GetBackgroundColor().has_value());
    toggleModelNG.SetCheckboxDefaultColor(AceType::RawPtr(toggleNode), ToggleColorType::BACKGROUND_COLOR);
    EXPECT_FALSE(paintProperty->GetBackgroundColor().has_value());
}

/**
 * @tc.name: SetSwitchDefaultColorTest001
 * @tc.desc: test SetSwitchDefaultColor.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleOneTestNg, SetSwitchDefaultColorTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a toggle model and verify initial color properties are not set.
     * @tc.expected: step1. Frame node and paint property are valid, all color properties are initially unset.
     */
    ToggleModelNG toggleModelNG;
    toggleModelNG.Create(TOGGLE_TYPE[2], IS_ON);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto paintProperty = frameNode->GetPaintProperty<SwitchPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    auto colorRet = paintProperty->GetUnselectedColor();
    EXPECT_FALSE(colorRet.has_value());
    colorRet = paintProperty->GetSwitchPointColor();
    EXPECT_FALSE(colorRet.has_value());
    colorRet = paintProperty->GetSelectedColor();
    EXPECT_FALSE(colorRet.has_value());

    /**
     * @tc.steps: step2. Mock theme manager to provide switch theme.
     * @tc.expected: step2. Mock theme manager returns valid switch theme instances.
     */
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto switchTheme = AceType::MakeRefPtr<SwitchTheme>();
    ASSERT_NE(switchTheme, nullptr);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SwitchTheme>()));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(AceType::MakeRefPtr<SwitchTheme>()));

    /**
     * @tc.steps: step3. Test setting default colors for different color types.
     * @tc.expected: step3. Each color property is updated to the corresponding theme color when set.
     */
    toggleModelNG.SetSwitchDefaultColor(frameNode, static_cast<ToggleColorType>(3));
    auto color = switchTheme->GetActiveColor();
    toggleModelNG.SetSwitchDefaultColor(frameNode, ToggleColorType::SELECTED_COLOR);
    colorRet = paintProperty->GetSelectedColor();
    EXPECT_EQ(colorRet.value_or(Color::BLACK), color);
    color = switchTheme->GetPointColor();
    toggleModelNG.SetSwitchDefaultColor(frameNode, ToggleColorType::SWITCH_POINT_COLOR);
    colorRet = paintProperty->GetSwitchPointColor();
    EXPECT_EQ(colorRet.value_or(Color::BLACK), color);
    color = switchTheme->GetInactiveColor();
    toggleModelNG.SetSwitchDefaultColor(frameNode, ToggleColorType::UN_SELECTED_COLOR);
    colorRet = paintProperty->GetUnselectedColor();
    EXPECT_EQ(colorRet.value_or(Color::BLACK), color);

    auto toggleNode = FrameNode::CreateFrameNode(V2::TOGGLE_ETS_TAG, 1, AceType::MakeRefPtr<ToggleButtonPattern>());
    EXPECT_NE(toggleNode, nullptr);
    auto pattern = AceType::DynamicCast<ToggleButtonPattern>(toggleNode->GetPattern());
    EXPECT_NE(pattern, nullptr);
    auto paintProp = pattern->GetPaintProperty<ToggleButtonPaintProperty>();
    EXPECT_NE(paintProp, nullptr);
    toggleModelNG.SetSwitchDefaultColor(AceType::RawPtr(toggleNode), ToggleColorType::BACKGROUND_COLOR);
    EXPECT_FALSE(paintProp->GetBackgroundColor().has_value());
}

/**
 * @tc.name: SetButtonDefaultColorTest001
 * @tc.desc: test SetButtonDefaultColor.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleOneTestNg, SetButtonDefaultColorTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a toggle model and verify initial selected color is not set.
     * @tc.expected: step1. Frame node and paint property are valid, selected color is initially unset.
     */
    ToggleModelNG toggleModelNG;
    toggleModelNG.Create(TOGGLE_TYPE[2], IS_ON);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto paintProperty = frameNode->GetPaintProperty<SwitchPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    auto colorRet = paintProperty->GetSelectedColor();
    EXPECT_FALSE(colorRet.has_value());

    /**
     * @tc.steps: step2. Create a button toggle and mock theme manager to provide toggle theme.
     * @tc.expected: step2. Button frame node is valid and theme manager returns valid toggle theme.
     */
    ToggleModelNG toggleModelNG2;
    toggleModelNG2.Create(TOGGLE_TYPE[1], IS_ON);
    auto buttonFrameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(buttonFrameNode, nullptr);

    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto buttonTheme = AceType::MakeRefPtr<ToggleTheme>();
    ASSERT_NE(buttonTheme, nullptr);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<ToggleTheme>()));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(AceType::MakeRefPtr<ToggleTheme>()));
    auto color = buttonTheme->GetCheckedColor();

    /**
     * @tc.steps: step3. Test setting default color with invalid and valid color types.
     * @tc.expected: step3. Selected color is updated to theme's checked color when valid type is used.
     */
    toggleModelNG.SetButtonDefaultColor(buttonFrameNode, static_cast<ToggleColorType>(3));
    toggleModelNG.SetButtonDefaultColor(buttonFrameNode, ToggleColorType::SELECTED_COLOR);
    colorRet = paintProperty->GetSelectedColor();
    EXPECT_EQ(colorRet.value_or(Color::BLACK), color);
}

/**
 * @tc.name: SetButtonDefaultColorTest002
 * @tc.desc: test SetButtonDefaultColor.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleOneTestNg, SetButtonDefaultColorTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a toggle model and verify frame node and paint property setup.
     * @tc.expected: step1. Frame node and paint property are created and valid, selected color is not set initially.
     */
    ToggleModelNG toggleModelNG;
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto toggleNode = FrameNode::CreateFrameNode(V2::TOGGLE_ETS_TAG, 1, AceType::MakeRefPtr<ToggleButtonPattern>());
    EXPECT_NE(toggleNode, nullptr);
    auto pattern = AceType::DynamicCast<ToggleButtonPattern>(toggleNode->GetPattern());
    EXPECT_NE(pattern, nullptr);
    auto paintProperty = pattern->GetPaintProperty<ToggleButtonPaintProperty>();
    EXPECT_NE(paintProperty, nullptr);
    stack->Push(toggleNode);

    /**
     * @tc.steps: step2. Test default color setting for BACKGROUND_COLOR type.
     * @tc.expected: step2. Background color is reset and no longer has a valid value after setting default color.
     */
    paintProperty->UpdateBackgroundColor(Color::BLACK);
    EXPECT_TRUE(paintProperty->GetBackgroundColor().has_value());
    toggleModelNG.SetButtonDefaultColor(AceType::RawPtr(toggleNode), ToggleColorType::BACKGROUND_COLOR);
    EXPECT_FALSE(paintProperty->GetBackgroundColor().has_value());
}

/**
 * @tc.name: CreateWithSwitchResourceObj
 * @tc.desc: Test CreateWithSwitchResourceObj.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleOneTestNg, CreateWithSwitchResourceObj, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a switch toggle and prepare resource objects.
     * @tc.expected: step1. Frame node is created and marked as modified.
     */
    ToggleModelNG toggleModelNG;
    toggleModelNG.Create(TOGGLE_TYPE[2], IS_ON);
    auto switchFrameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(switchFrameNode, nullptr);
    switchFrameNode->MarkModifyDone();

    /**
     * @tc.steps: step2. Attempt to create resource with null object and verify no resource is added.
     * @tc.expected: step2. Resource map does not contain the key after null resource creation.
     */
    auto resObj = AceType::MakeRefPtr<ResourceObject>("", "", -1);
    std::string key = "toggle" + toggleModelNG.ColorTypeToString(ToggleColorType::SELECTED_COLOR);
    toggleModelNG.CreateWithSwitchResourceObj(
        const_cast<FrameNode*>(switchFrameNode), ToggleColorType::SELECTED_COLOR, nullptr, key);
    auto pattern = switchFrameNode->GetPattern<SwitchPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->resourceMgr_ = AceType::MakeRefPtr<PatternResourceManager>();
    auto resMgr = pattern->resourceMgr_;
    ASSERT_NE(resMgr, nullptr);
    auto count = resMgr->resMap_.count(key);
    EXPECT_EQ(count, 0);

    /**
     * @tc.steps: step3. Create resource with valid objects for different color types.
     * @tc.expected: step3. Resource map contains exactly one entry after valid resource creation.
     */
    ResourceObjectParams params { .value = "", .type = ResourceObjectParamType::NONE };
    RefPtr<ResourceObject> resObjWithParams =
        AceType::MakeRefPtr<ResourceObject>(-1, 10003, std::vector<ResourceObjectParams> { params }, "", "", 100000);
    toggleModelNG.CreateWithSwitchResourceObj(
        const_cast<FrameNode*>(switchFrameNode), ToggleColorType::SELECTED_COLOR, resObj, key);
    toggleModelNG.CreateWithSwitchResourceObj(
        const_cast<FrameNode*>(switchFrameNode), ToggleColorType::SWITCH_POINT_COLOR, resObjWithParams, key);
    toggleModelNG.CreateWithSwitchResourceObj(
        const_cast<FrameNode*>(switchFrameNode), ToggleColorType::UN_SELECTED_COLOR, resObjWithParams, key);
    toggleModelNG.CreateWithSwitchResourceObj(
        const_cast<FrameNode*>(switchFrameNode), static_cast<ToggleColorType>(3), resObjWithParams, key);
    count = resMgr->resMap_.count(key);
    EXPECT_EQ(count, 1);
}

/**
 * @tc.name: CreateWithCheckBoxResourceObj
 * @tc.desc: Test CreateWithCheckBoxResourceObj.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleOneTestNg, CreateWithCheckBoxResourceObj, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a checkbox toggle and prepare resource objects.
     * @tc.expected: step1. Frame node is created and marked as modified.
     */
    ToggleModelNG toggleModelNG;
    toggleModelNG.Create(TOGGLE_TYPE[0], IS_ON);
    auto switchFrameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(switchFrameNode, nullptr);
    switchFrameNode->MarkModifyDone();

    /**
     * @tc.steps: step2. Attempt to create resource with null object and verify no resource is added.
     * @tc.expected: step2. Resource map does not contain the key after null resource creation.
     */
    auto resObj = AceType::MakeRefPtr<ResourceObject>("", "", -1);
    std::string key = "toggle" + toggleModelNG.ColorTypeToString(ToggleColorType::SELECTED_COLOR);
    toggleModelNG.CreateWithCheckBoxResourceObj(
        const_cast<FrameNode*>(switchFrameNode), ToggleColorType::SELECTED_COLOR, nullptr, key);
    auto pattern = switchFrameNode->GetPattern<CheckBoxPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->resourceMgr_ = AceType::MakeRefPtr<PatternResourceManager>();
    auto resMgr = pattern->resourceMgr_;
    ASSERT_NE(resMgr, nullptr);
    auto count = resMgr->resMap_.count(key);
    EXPECT_EQ(count, 0);

    /**
     * @tc.steps: step3. Create resource with valid objects for different color types.
     * @tc.expected: step3. Resource map contains exactly one entry after valid resource creation.
     */
    ResourceObjectParams params { .value = "", .type = ResourceObjectParamType::NONE };
    RefPtr<ResourceObject> resObjWithParams =
        AceType::MakeRefPtr<ResourceObject>(-1, 10003, std::vector<ResourceObjectParams> { params }, "", "", 100000);
    toggleModelNG.CreateWithCheckBoxResourceObj(
        const_cast<FrameNode*>(switchFrameNode), ToggleColorType::SELECTED_COLOR, resObj, key);
    toggleModelNG.CreateWithCheckBoxResourceObj(
        const_cast<FrameNode*>(switchFrameNode), ToggleColorType::SWITCH_POINT_COLOR, resObj, key);
    count = resMgr->resMap_.count(key);
    EXPECT_EQ(count, 1);
}

/**
 * @tc.name: CreateWithButtonResourceObj
 * @tc.desc: Test CreateWithButtonResourceObj.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleOneTestNg, CreateWithButtonResourceObj, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a button toggle and prepare resource objects.
     * @tc.expected: step1. Frame node is created and marked as modified.
     */
    ToggleModelNG toggleModelNG;
    toggleModelNG.Create(TOGGLE_TYPE[1], IS_ON);
    auto switchFrameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(switchFrameNode, nullptr);
    switchFrameNode->MarkModifyDone();

    /**
     * @tc.steps: step2. Attempt to create resource with null object and verify no resource is added.
     * @tc.expected: step2. Resource map does not contain the key after null resource creation.
     */
    auto resObj = AceType::MakeRefPtr<ResourceObject>("", "", -1);
    std::string key = "toggle" + toggleModelNG.ColorTypeToString(ToggleColorType::SELECTED_COLOR);
    toggleModelNG.CreateWithButtonResourceObj(
        const_cast<FrameNode*>(switchFrameNode), ToggleColorType::SELECTED_COLOR, nullptr, key);
    auto pattern = switchFrameNode->GetPattern<ToggleButtonPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->resourceMgr_ = AceType::MakeRefPtr<PatternResourceManager>();
    auto resMgr = pattern->resourceMgr_;
    ASSERT_NE(resMgr, nullptr);
    auto count = resMgr->resMap_.count(key);
    EXPECT_EQ(count, 0);

    /**
     * @tc.steps: step3. Create resource with valid objects for different color types.
     * @tc.expected: step3. Resource map contains exactly one entry after valid resource creation.
     */
    ResourceObjectParams params { .value = "", .type = ResourceObjectParamType::NONE };
    RefPtr<ResourceObject> resObjWithParams =
        AceType::MakeRefPtr<ResourceObject>(-1, 10003, std::vector<ResourceObjectParams> { params }, "", "", 100000);
    toggleModelNG.CreateWithButtonResourceObj(
        const_cast<FrameNode*>(switchFrameNode), ToggleColorType::SELECTED_COLOR, resObj, key);
    toggleModelNG.CreateWithButtonResourceObj(
        const_cast<FrameNode*>(switchFrameNode), ToggleColorType::SWITCH_POINT_COLOR, resObj, key);
    count = resMgr->resMap_.count(key);
    EXPECT_EQ(count, 1);
}

/**
 * @tc.name: CreateWithDimensionVpResourceObj
 * @tc.desc: Test CreateWithDimensionVpResourceObj.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleOneTestNg, CreateWithDimensionVpResourceObj, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a switch toggle and prepare resource objects.
     * @tc.expected: step1. Frame node is created and marked as modified.
     */
    ToggleModelNG toggleModelNG;
    toggleModelNG.Create(TOGGLE_TYPE[2], IS_ON);
    auto switchFrameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(switchFrameNode, nullptr);
    switchFrameNode->MarkModifyDone();

    /**
     * @tc.steps: step2. Attempt to create resource with null object and verify no resource is added.
     * @tc.expected: step2. Resource map does not contain the key after null resource creation.
     */
    auto resObj = AceType::MakeRefPtr<ResourceObject>("", "", -1);
    std::string key = "toggle" + toggleModelNG.DimensionTypeToString(ToggleDimensionType::POINT_RADIUS);
    toggleModelNG.CreateWithDimensionVpResourceObj(nullptr, ToggleDimensionType::POINT_RADIUS);
    auto pattern = switchFrameNode->GetPattern<SwitchPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->resourceMgr_ = AceType::MakeRefPtr<PatternResourceManager>();
    auto resMgr = pattern->resourceMgr_;
    ASSERT_NE(resMgr, nullptr);
    auto count = resMgr->resMap_.count(key);
    EXPECT_EQ(count, 0);

    /**
     * @tc.steps: step3. Create resource with valid objects for different dimension types.
     * @tc.expected: step3. Resource map contains exactly one entry after valid resource creation.
     */
    ResourceObjectParams params { .value = "", .type = ResourceObjectParamType::NONE };
    RefPtr<ResourceObject> resObjWithParams =
        AceType::MakeRefPtr<ResourceObject>(-1, 10003, std::vector<ResourceObjectParams> { params }, "", "", 100000);
    toggleModelNG.CreateWithDimensionVpResourceObj(resObjWithParams, ToggleDimensionType::POINT_RADIUS);
    toggleModelNG.CreateWithDimensionVpResourceObj(resObjWithParams, ToggleDimensionType::TRACK_BORDER_RADIUS);
    toggleModelNG.CreateWithDimensionVpResourceObj(resObjWithParams, static_cast<ToggleDimensionType>(2));
    count = resMgr->resMap_.count(key);
    EXPECT_EQ(count, 1);
}

/**
 * @tc.name: GetOrCreateHolderNode
 * @tc.desc: Test GetOrCreateHolderNode.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleOneTestNg, GetOrCreateHolderNode, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a toggleBase.
     */
    ToggleModelNG toggleModelNG;
    toggleModelNG.Create(TOGGLE_TYPE[2], IS_ON);
    auto toggleBase = AceType::MakeRefPtr<ToggleBasePattern>();
    ASSERT_NE(toggleBase, nullptr);

    /**
     * @tc.steps: step2. Call GetOrCreateHolderNode.
     */
    auto holder = toggleBase->GetOrCreateHolderNode();
    ASSERT_NE(holder, nullptr);
    RefPtr<FrameNode> child = FrameNode::GetOrCreateFrameNode(V2::TOGGLE_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwitchPattern>(); });
    toggleBase->MountToHolder(child);
    ASSERT_NE(child, nullptr);
}

/**
 * @tc.name: ToggleTypeWrongTest
 * @tc.desc: Test toggle checkbox update switch property.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleOneTestNg, ToggleTypeWrongTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a toggle checkbox.
     */
    ToggleModelNG toggleModelNG;
    toggleModelNG.Create(TOGGLE_TYPE[0], IS_ON);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    /**
     * @tc.steps: step2. call set switch property.
     * @tc.expected: step2. The test suite does not crash.
     */
    toggleModelNG.SetUnselectedColorSetByUser(frameNode, true);
    toggleModelNG.SetSwitchPointColorSetByUser(frameNode, true);
    toggleModelNG.SetSwitchIsOn(frameNode, true);
    /**
     * @tc.steps: step3. call get switch property.
     * @tc.expected: step3. The test suite does not crash.
     */
    auto color = toggleModelNG.GetSelectedColor(frameNode);
    EXPECT_EQ(color, Color::WHITE);
    color = toggleModelNG.GetSwitchPointColor(frameNode);
    EXPECT_EQ(color, Color::WHITE);
    color = toggleModelNG.GetUnselectedColor(frameNode);
    EXPECT_EQ(color, Color::WHITE);
    auto isOn = toggleModelNG.GetSwitchIsOn(frameNode);
    EXPECT_FALSE(isOn);
}
} // namespace OHOS::Ace::NG
