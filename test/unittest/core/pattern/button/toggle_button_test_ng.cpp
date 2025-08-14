/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include <cstddef>
#include <optional>

#include "gtest/gtest.h"
#define protected public
#define private public

#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/components/button/button_theme.h"
#include "core/components/toggle/toggle_theme.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/event/focus_hub.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/button/toggle_button_model_ng.h"
#include "core/components_ng/pattern/button/toggle_button_paint_property.h"
#include "core/components_ng/pattern/button/toggle_button_pattern.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/event/touch_event.h"
#include "core/pipeline/base/element_register.h"
#include "core/pipeline_ng/ui_task_scheduler.h"
#include "test/mock/base/mock_system_properties.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr bool IS_ON = true;
constexpr Color SELECTED_COLOR = Color(0XFFFF0000);
constexpr Color BACKGROUND_COLOR = Color(0XFFFF0000);
const char TOGGLE_ETS_TAG[] = "Toggle";
const Alignment ALIGNMENT = Alignment::BOTTOM_RIGHT;
const double dimensionValue = 1.0;
const double childDimensionValue = 5.0;
constexpr float HOVER_OPACITY = 0.05f;
constexpr int32_t TOUCH_DURATION = 250;
constexpr bool STATE_EFFECT = false;
} // namespace

struct TestProperty {
    std::optional<bool> isOn = std::nullopt;
    std::optional<Color> selectedColor = std::nullopt;
    std::optional<Color> backgroundColor = std::nullopt;
};

class ToggleButtonTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();

protected:
    RefPtr<FrameNode> CreateToggleButtonFrameNode(const TestProperty& testProperty);
};

void ToggleButtonTestNg::SetUpTestCase()
{
    MockPipelineContext::SetUp();
    // set buttonTheme to themeManager before using themeManager to get buttonTheme
    auto themeManagerOne = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManagerOne);
    EXPECT_CALL(*themeManagerOne, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<ButtonTheme>()));
}

void ToggleButtonTestNg::TearDownTestCase()
{
    MockPipelineContext::TearDown();
}

RefPtr<FrameNode> ToggleButtonTestNg::CreateToggleButtonFrameNode(const TestProperty& testProperty)
{
    ToggleButtonModelNG toggleButtonModelNG;
    toggleButtonModelNG.Create(TOGGLE_ETS_TAG);
    if (testProperty.isOn.has_value()) {
        toggleButtonModelNG.SetIsOn(testProperty.isOn.value());
    }
    if (testProperty.selectedColor.has_value()) {
        toggleButtonModelNG.SetSelectedColor(testProperty.selectedColor.value());
    }
    if (testProperty.backgroundColor.has_value()) {
        toggleButtonModelNG.SetBackgroundColor(testProperty.backgroundColor.value(), true);
    }

    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    return AceType::DynamicCast<FrameNode>(element);
}

/**
 * @tc.name: ToggleButtonPatternTest001
 * @tc.desc: Test all the properties of bubble.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleButtonTestNg, ToggleButtonPatternTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize all properties of bubble.
     */
    TestProperty testProperty;
    testProperty.isOn = std::make_optional(IS_ON);
    testProperty.selectedColor = std::make_optional(SELECTED_COLOR);
    testProperty.backgroundColor = std::make_optional(BACKGROUND_COLOR);

    /**
     * @tc.steps: step2. create list frameNode and get LayoutProperty and paintProperty.
     * @tc.expected: step2. get paintProperty success.
     */
    RefPtr<FrameNode> frameNode = CreateToggleButtonFrameNode(testProperty);
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::TOGGLE_ETS_TAG);
    auto pattern = AceType::DynamicCast<ToggleButtonPattern>(frameNode->GetPattern());
    ASSERT_NE(pattern, nullptr);
    auto paintProperty = pattern->GetPaintProperty<ToggleButtonPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    auto toggleButtonEventHub = frameNode->GetOrCreateEventHub<ToggleButtonEventHub>();
    CHECK_NULL_VOID(toggleButtonEventHub);

    /**
     * @tc.steps: step3. get the properties of all settings.
     * @tc.expected: step3. check whether the properties is correct.
     */
    EXPECT_EQ(paintProperty->GetIsOn(), IS_ON);
    EXPECT_EQ(paintProperty->GetSelectedColor(), SELECTED_COLOR);
    EXPECT_EQ(paintProperty->GetBackgroundColor(), BACKGROUND_COLOR);
}

/**
 * @tc.name: ToggleButtonPatternTest002
 * @tc.desc: test toggleButton pattern OnModifyDone .
 * @tc.type: FUNC
 */
HWTEST_F(ToggleButtonTestNg, ToggleButtonPatternTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create bubble and get frameNode.
     */
    TestProperty testProperty;
    testProperty.isOn = std::make_optional(IS_ON);
    testProperty.selectedColor = std::make_optional(SELECTED_COLOR);
    testProperty.backgroundColor = std::make_optional(BACKGROUND_COLOR);
    RefPtr<FrameNode> frameNode = CreateToggleButtonFrameNode(testProperty);
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. get pattern and update frameNode.
     * @tc.expected: step2. related function is called.
     */
    auto togglePattern = AceType::DynamicCast<ToggleButtonPattern>(frameNode->GetPattern());
    ASSERT_NE(togglePattern, nullptr);

    // set toggleTheme to themeManager before using themeManager to get toggleTheme
    auto themeManagerSecond = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManagerSecond);
    EXPECT_CALL(*themeManagerSecond, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<ToggleTheme>()));
    EXPECT_CALL(*themeManagerSecond, GetTheme(_, _)).WillRepeatedly(Return(AceType::MakeRefPtr<ToggleTheme>()));

    /**
     * @tc.steps: step3. pattern OnModifyDone and OnClick.
     * @tc.expected: step3. check whether the function is executed successfully.
     */
    togglePattern->isOn_ = false;
    togglePattern->OnModifyDone();
}

/**
 * @tc.name: ToggleButtonPatternTest003
 * @tc.desc: test toggleButton pattern OnModifyDone and onClick.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleButtonTestNg, ToggleButtonPatternTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create bubble and get frameNode.
     */
    TestProperty testProperty;
    testProperty.isOn = std::make_optional(IS_ON);
    RefPtr<FrameNode> frameNode = CreateToggleButtonFrameNode(testProperty);
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. get pattern and update frameNode.
     * @tc.expected: step2. related function is called.
     */
    auto togglePattern = AceType::DynamicCast<ToggleButtonPattern>(frameNode->GetPattern());
    ASSERT_NE(togglePattern, nullptr);
    auto paintProperty = frameNode->GetPaintProperty<ToggleButtonPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty();
    paintProperty->UpdateSelectedColor(SELECTED_COLOR);
    paintProperty->UpdateBackgroundColor(BACKGROUND_COLOR);

    // set toggleTheme to themeManager before using themeManager to get toggleTheme
    auto themeManagerSecond = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManagerSecond);
    EXPECT_CALL(*themeManagerSecond, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<ToggleTheme>()));
    EXPECT_CALL(*themeManagerSecond, GetTheme(_, _)).WillRepeatedly(Return(AceType::MakeRefPtr<ToggleTheme>()));

    /**
     * @tc.steps: step3. pattern OnModifyDone and OnClick.
     * @tc.expected: step3. check whether the function is executed successfully.
     */
    togglePattern->OnModifyDone();
    togglePattern->OnClick();
    layoutProperty->UpdateAlignment(ALIGNMENT);
    EXPECT_EQ(ALIGNMENT, layoutProperty->GetPositionProperty()->GetAlignmentValue());

    // update isOn value
    togglePattern->isOn_ = false;
    togglePattern->OnModifyDone();
    paintProperty->UpdateIsOn(false);
    togglePattern->OnClick();
}

/**
 * @tc.name: ToggleButtonPatternTest004
 * @tc.desc: test toggleButton pattern OnKeyEvent.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleButtonTestNg, ToggleButtonPatternTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create and get frameNode.
     */
    TestProperty testProperty;
    testProperty.isOn = std::make_optional(IS_ON);
    RefPtr<FrameNode> frameNode = CreateToggleButtonFrameNode(testProperty);
    ASSERT_NE(frameNode, nullptr);
    auto togglePattern = AceType::DynamicCast<ToggleButtonPattern>(frameNode->GetPattern());
    ASSERT_NE(togglePattern, nullptr);

    /**
     * @tc.steps: step2. call pattern OnKeyEvent.
     * @tc.expected: step2. check whether the function is executed successfully.
     */
    auto event = KeyEvent();
    event.action = KeyAction::UNKNOWN;
    EXPECT_FALSE(togglePattern->OnKeyEvent(event));
    event.action = KeyAction::DOWN;
    event.code = KeyCode::KEY_BRIGHTNESS_DOWN;
    EXPECT_FALSE(togglePattern->OnKeyEvent(event));
    event.code = KeyCode::KEY_SPACE;
    EXPECT_TRUE(togglePattern->OnKeyEvent(event));
}

HWTEST_F(ToggleButtonTestNg, ToggleButtonPatternTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create bubble and get frameNode.
     */
    TestProperty testProperty;
    testProperty.isOn = std::make_optional(IS_ON);
    RefPtr<FrameNode> frameNode = CreateToggleButtonFrameNode(testProperty);
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. get pattern and update frameNode.
     * @tc.expected: step2. related function is called.
     */
    auto togglePattern = AceType::DynamicCast<ToggleButtonPattern>(frameNode->GetPattern());
    ASSERT_NE(togglePattern, nullptr);

    // set toggleTheme to themeManager before using themeManager to get toggleTheme
    auto themeManagerSecond = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManagerSecond);
    EXPECT_CALL(*themeManagerSecond, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<ToggleTheme>()));
    EXPECT_CALL(*themeManagerSecond, GetTheme(_, _)).WillRepeatedly(Return(AceType::MakeRefPtr<ToggleTheme>()));

    /**
     * @tc.steps: step3. pattern OnModifyDone.
     * @tc.expected: step3. check whether the function is executed successfully.
     */
    auto eventHub = frameNode->GetOrCreateEventHub<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    eventHub->SetEnabled(false);
    togglePattern->OnModifyDone();
}

HWTEST_F(ToggleButtonTestNg, ToggleButtonPatternTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create bubble and get frameNode.
     */
    TestProperty testProperty;
    testProperty.isOn = std::make_optional(IS_ON);
    RefPtr<FrameNode> frameNode = CreateToggleButtonFrameNode(testProperty);
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. get pattern and update frameNode.
     * @tc.expected: step2. related function is called.
     */
    auto togglePattern = AceType::DynamicCast<ToggleButtonPattern>(frameNode->GetPattern());
    ASSERT_NE(togglePattern, nullptr);

    // set toggleTheme to themeManager before using themeManager to get toggleTheme
    auto themeManagerSecond = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManagerSecond);
    EXPECT_CALL(*themeManagerSecond, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<ToggleTheme>()));
    EXPECT_CALL(*themeManagerSecond, GetTheme(_, _)).WillRepeatedly(Return(AceType::MakeRefPtr<ToggleTheme>()));

    /**
     * @tc.steps: step3. pattern InitClickEvent.
     * @tc.expected: step3. check whether clickListener_ is initialized.
     */
    EXPECT_TRUE(togglePattern->clickListener_);
}

HWTEST_F(ToggleButtonTestNg, ToggleButtonPatternTest007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create bubble and get frameNode.
     */
    TestProperty testProperty;
    testProperty.isOn = std::make_optional(IS_ON);
    RefPtr<FrameNode> frameNode = CreateToggleButtonFrameNode(testProperty);
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. get pattern and update frameNode.
     * @tc.expected: step2. related function is called.
     */
    auto togglePattern = AceType::DynamicCast<ToggleButtonPattern>(frameNode->GetPattern());
    ASSERT_NE(togglePattern, nullptr);

    // set toggleTheme to themeManager before using themeManager to get toggleTheme
    auto themeManagerSecond = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManagerSecond);
    EXPECT_CALL(*themeManagerSecond, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<ToggleTheme>()));
    EXPECT_CALL(*themeManagerSecond, GetTheme(_, _)).WillRepeatedly(Return(AceType::MakeRefPtr<ToggleTheme>()));

    /**
     * @tc.steps: step3. Creat child node but not set font size.
     * @tc.expected: step3. Child frame node's font size synchronized with parent.
     */
    Dimension buttonFontSize(dimensionValue);
    Dimension childFontSize(childDimensionValue);
    RefPtr<FrameNode> childrenNode =
        FrameNode::GetOrCreateFrameNode("childTag", 1, []() { return AceType::MakeRefPtr<TextPattern>(); });
    frameNode->children_.emplace_back(childrenNode);
    togglePattern->textFontSize_ = buttonFontSize;
    togglePattern->OnModifyDone();
    auto textNode = AceType::DynamicCast<FrameNode>(frameNode->GetFirstChild());
    ASSERT_NE(textNode, nullptr);
    auto textLayoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);
    EXPECT_EQ(textLayoutProperty->GetFontSizeValue(childFontSize).Value(), childDimensionValue);

    /**
     * @tc.steps: step4. Creat child node and set font size.
     * @tc.expected: step4. Parent frame node's font size synchronized with child.
     */
    frameNode->children_.clear();
    auto childrenTextNode = AceType::DynamicCast<FrameNode>(childrenNode);
    ASSERT_NE(childrenTextNode, nullptr);
    auto childrenTextLayoutProperty = childrenTextNode->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(childrenTextLayoutProperty, nullptr);
    childrenTextLayoutProperty->UpdateFontSize(childFontSize);
    frameNode->children_.emplace_back(childrenNode);
    togglePattern->isOn_ = false;
    togglePattern->OnModifyDone();
    auto layoutProperty = frameNode->GetLayoutProperty<ButtonLayoutProperty>();
    EXPECT_EQ(layoutProperty->GetFontSizeValue(buttonFontSize).Value(), childDimensionValue);
}

/**
 * @tc.name: ToggleButtonPatternTest008
 * @tc.desc: test ToggleButtonModelNG::SetBackgroundColor.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleButtonTestNg, ToggleButtonPatternTest008, TestSize.Level1)
{
    ToggleButtonModelNG toggleButtonModelNG;
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(TOGGLE_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<TextPattern>(); });
    stack->Push(frameNode);
    ToggleButtonModelNG::SetBackgroundColor(BACKGROUND_COLOR, true);
    auto context = frameNode->GetRenderContext();
    EXPECT_EQ(context->GetBackgroundColorValue(), BACKGROUND_COLOR);
    ToggleButtonModelNG::SetBackgroundColor(BACKGROUND_COLOR, false);
    EXPECT_EQ(context->GetBackgroundColorValue(), BACKGROUND_COLOR);

    auto buttonNode = FrameNode::CreateFrameNode(V2::BUTTON_ETS_TAG, 1, AceType::MakeRefPtr<ButtonPattern>());
    toggleButtonModelNG.SetBackgroundColor(AceType::RawPtr(buttonNode), BACKGROUND_COLOR);
    auto toggleNode = FrameNode::CreateFrameNode(V2::TOGGLE_ETS_TAG, 1, AceType::MakeRefPtr<ToggleButtonPattern>());
    toggleButtonModelNG.SetBackgroundColor(AceType::RawPtr(toggleNode), BACKGROUND_COLOR);
}

/**
 * @tc.name: ToggleButtonPatternTest009
 * @tc.desc: test button pattern AnimateTouchAndHover.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleButtonTestNg, ToggleButtonPatternTest009, TestSize.Level1)
{
    TestProperty testProperty;
    testProperty.isOn = std::make_optional(IS_ON);
    RefPtr<FrameNode> frameNode = CreateToggleButtonFrameNode(testProperty);
    ASSERT_NE(frameNode, nullptr);
    auto buttonPattern = frameNode->GetPattern<ToggleButtonPattern>();
    ASSERT_NE(buttonPattern, nullptr);
    auto context = frameNode->GetRenderContext();
    ASSERT_NE(context, nullptr);
    buttonPattern->AnimateTouchAndHover(context, 0.0f, HOVER_OPACITY, TOUCH_DURATION, Curves::FRICTION);
    buttonPattern->AnimateTouchAndHover(context, HOVER_OPACITY, 0.0f, TOUCH_DURATION, Curves::FRICTION);
    EXPECT_TRUE(buttonPattern->isOn_);
}

/**
 * @tc.name: ToggleButtonPatternTest010
 * @tc.desc: Test the Distributed capability of ToggleButton.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleButtonTestNg, ToggleButtonPatternTest010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create bubble and get frameNode.
     */
    TestProperty testProperty;
    testProperty.isOn = std::make_optional(IS_ON);
    RefPtr<FrameNode> frameNode = CreateToggleButtonFrameNode(testProperty);
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. get pattern and update frameNode.
     * @tc.expected: function ProvideRestoreInfo is called.
     */
    auto buttonPattern = frameNode->GetPattern<ToggleButtonPattern>();
    ASSERT_NE(buttonPattern, nullptr);
    buttonPattern->isOn_ = false;
    auto ret = buttonPattern->ProvideRestoreInfo();
    EXPECT_TRUE(ret == R"({"IsOn":false})");

    /**
     * @tc.steps: step3. function OnRestoreInfo is called.
     * @tc.expected: Passing invalid & valid JSON format.
     */
    std::string restoreInfo_ = "invalid_json_string";
    buttonPattern->OnRestoreInfo(restoreInfo_);
    auto toggleButtonPaintProperty = buttonPattern->GetPaintProperty<ToggleButtonPaintProperty>();
    ASSERT_NE(toggleButtonPaintProperty, nullptr);
    EXPECT_TRUE(toggleButtonPaintProperty->GetIsOnValue(false));
    restoreInfo_ = R"({"IsOn":true})";
    buttonPattern->OnRestoreInfo(restoreInfo_);
    ASSERT_NE(toggleButtonPaintProperty, nullptr);
    EXPECT_TRUE(toggleButtonPaintProperty->GetIsOnValue(false));
}

/**
 * @tc.name: ToggleButtonPatternTest011
 * @tc.desc: ToggleButton test Select and ClearSelection.
 */
HWTEST_F(ToggleButtonTestNg, ToggleButtonPatternTest011, TestSize.Level1)
{
    ToggleButtonModelNG toggleButtonModelNG;
    toggleButtonModelNG.Create(TOGGLE_ETS_TAG);
    toggleButtonModelNG.SetIsOn(true);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ToggleButtonPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->isOn_ = false;
    pattern->SetAccessibilityAction();

    auto accessibilityProperty = frameNode->GetAccessibilityProperty<ToggleButtonAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    EXPECT_TRUE(accessibilityProperty->ActActionSelect());

    bool isSelected = true;
    pattern->isOn_ = false;
    pattern->UpdateSelectStatus(isSelected);
    EXPECT_TRUE(accessibilityProperty->ActActionClearSelection());
}

/**
 * @tc.name: ToggleButtonPatternTest012
 * @tc.desc: test ToggleButtonPattern::OnTouchDown.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleButtonTestNg, ToggleButtonPatternTest012, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create bubble and get frameNode.
     */
    ToggleButtonModelNG toggleButtonModelNG;
    toggleButtonModelNG.Create(TOGGLE_ETS_TAG);
    toggleButtonModelNG.SetIsOn(true);
    auto togglebuttonNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(togglebuttonNode, nullptr);
    auto togglebuttonPattern = togglebuttonNode->GetPattern<ToggleButtonPattern>();
    ASSERT_NE(togglebuttonPattern, nullptr);
    auto gestureHub = togglebuttonNode->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureHub, nullptr);

    /**
     * @tc.steps: test buttonPattern OnTouchDown OnTouchUp function.
     * @tc.expected: step3. check whether the function is executed.
     */
    togglebuttonPattern->OnTouchDown();
    togglebuttonPattern->OnTouchUp();

    auto togglebuttonEventHub = togglebuttonNode->GetOrCreateEventHub<ButtonEventHub>();
    CHECK_NULL_VOID(togglebuttonEventHub);
    togglebuttonEventHub->SetStateEffect(STATE_EFFECT);
    togglebuttonPattern->clickedColor_ = std::nullopt;
    togglebuttonPattern->OnTouchDown();
    togglebuttonPattern->OnTouchUp();
    togglebuttonEventHub->SetStateEffect(IS_ON);
    togglebuttonEventHub->SetEnabled(false);
    togglebuttonPattern->OnTouchUp();
    EXPECT_FALSE(togglebuttonPattern->isOn_);
}

/**
 * @tc.name: ToggleButtonPatternTest013
 * @tc.desc: test ToggleButtonPattern::SetFocusButtonStyle.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleButtonTestNg, ToggleButtonPatternTest013, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create bubble and get frameNode.
     */
    TestProperty testProperty;
    testProperty.isOn = std::make_optional(IS_ON);
    RefPtr<FrameNode> frameNode = CreateToggleButtonFrameNode(testProperty);
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. get pattern and update frameNode.
     * @tc.expected: step2. related function is called.
     */
    auto togglePattern = AceType::DynamicCast<ToggleButtonPattern>(frameNode->GetPattern());
    ASSERT_NE(togglePattern, nullptr);

    // set toggleTheme to themeManager before using themeManager to get toggleTheme
    auto themeManagerSecond = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManagerSecond);
    EXPECT_CALL(*themeManagerSecond, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<ToggleTheme>()));
    EXPECT_CALL(*themeManagerSecond, GetTheme(_, _)).WillRepeatedly(Return(AceType::MakeRefPtr<ToggleTheme>()));

    /**
     * @tc.steps: step3. test toggleButtonPattern SetFocusButtonStyle function.
     * @tc.expected: step3. check whether the function is executed.
     */
    RefPtr<FrameNode> childrenNode =
        FrameNode::GetOrCreateFrameNode("childTag", 1, []() { return AceType::MakeRefPtr<TextPattern>(); });
    frameNode->children_.emplace_back(childrenNode);
    togglePattern->OnModifyDone();
    auto renderContext = frameNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    auto pipeline = PipelineBase::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    auto theme = pipeline->GetTheme<ToggleTheme>();
    ASSERT_NE(theme, nullptr);
    auto textNode = AceType::DynamicCast<FrameNode>(frameNode->GetFirstChild());
    ASSERT_NE(textNode, nullptr);
    auto textLayoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);

    togglePattern->SetFocusButtonStyle(textNode, textLayoutProperty, true, renderContext);

    EXPECT_EQ(textLayoutProperty->GetTextColor(), theme->GetTextColorFocus());
    EXPECT_EQ(renderContext->GetBackgroundColor(), theme->GetCheckedColor());
}

/**
 * @tc.name: ToggleButtonPatternTest014
 * @tc.desc: test ToggleButtonPattern::UpdateButtonStyle.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleButtonTestNg, ToggleButtonPatternTest014, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create bubble and get frameNode.
     */
    TestProperty testProperty;
    testProperty.isOn = std::make_optional(IS_ON);
    RefPtr<FrameNode> frameNode = CreateToggleButtonFrameNode(testProperty);
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. get pattern and update frameNode.
     * @tc.expected: step2. related function is called.
     */
    auto togglePattern = AceType::DynamicCast<ToggleButtonPattern>(frameNode->GetPattern());
    ASSERT_NE(togglePattern, nullptr);

    // set toggleTheme to themeManager before using themeManager to get toggleTheme
    auto themeManagerSecond = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManagerSecond);
    EXPECT_CALL(*themeManagerSecond, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<ToggleTheme>()));
    EXPECT_CALL(*themeManagerSecond, GetTheme(_, _)).WillRepeatedly(Return(AceType::MakeRefPtr<ToggleTheme>()));

    /**
     * @tc.steps: step3. Creat child node but not set font size.
     * @tc.expected: step3. Child frame node's font size synchronized with parent.
     */
    RefPtr<FrameNode> childrenNode =
        FrameNode::GetOrCreateFrameNode("childTag", 1, []() { return AceType::MakeRefPtr<TextPattern>(); });
    frameNode->children_.emplace_back(childrenNode);
    togglePattern->OnModifyDone();
    auto textNode = AceType::DynamicCast<FrameNode>(frameNode->GetFirstChild());
    ASSERT_NE(textNode, nullptr);
    auto textLayoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);

    /**
     * @tc.steps: step4. ToggleButtonPattern UpdateButtonStyle
     * @tc.expected: Check the param value
     */
    togglePattern->SetIsFocus(true);
    togglePattern->UpdateButtonStyle();
    EXPECT_EQ(togglePattern->isScale_, true);
    EXPECT_EQ(togglePattern->isCheckedShadow_, true);
    EXPECT_EQ(togglePattern->isbgColorFocus_, true);
}

/**
 * @tc.name: ToggleButtonPatternTest015
 * @tc.desc: test ToggleButtonPattern::UpdateButtonStyle.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleButtonTestNg, ToggleButtonPatternTest015, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create bubble and get frameNode.
     */
    TestProperty testProperty;
    testProperty.isOn = std::make_optional(IS_ON);
    RefPtr<FrameNode> frameNode = CreateToggleButtonFrameNode(testProperty);
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. get pattern and update frameNode.
     * @tc.expected: step2. related function is called.
     */
    auto togglePattern = AceType::DynamicCast<ToggleButtonPattern>(frameNode->GetPattern());
    ASSERT_NE(togglePattern, nullptr);

    // set toggleTheme to themeManager before using themeManager to get toggleTheme
    auto themeManagerSecond = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManagerSecond);
    EXPECT_CALL(*themeManagerSecond, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<ToggleTheme>()));
    EXPECT_CALL(*themeManagerSecond, GetTheme(_, _)).WillRepeatedly(Return(AceType::MakeRefPtr<ToggleTheme>()));

    /**
     * @tc.steps: step3. Creat child node but not set font size.
     * @tc.expected: step3. Child frame node's font size synchronized with parent.
     */
    RefPtr<FrameNode> childrenNode =
        FrameNode::GetOrCreateFrameNode("childTag", 1, []() { return AceType::MakeRefPtr<TextPattern>(); });
    frameNode->children_.emplace_back(childrenNode);
    togglePattern->OnModifyDone();
    auto textNode = AceType::DynamicCast<FrameNode>(frameNode->GetFirstChild());
    ASSERT_NE(textNode, nullptr);
    auto textLayoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);

    /**
     * @tc.steps: step2. ToggleButtonPattern UpdateButtonStyle
     * @tc.expected: Check the param value
     */
    togglePattern->SetIsFocus(false);
    togglePattern->UpdateButtonStyle();
    EXPECT_EQ(togglePattern->isScale_, false);
    EXPECT_EQ(togglePattern->isCheckedShadow_, false);
}

/**
 * @tc.name: ToggleButtonPatternTest016
 * @tc.desc: test ToggleButtonPattern::UpdateButtonStyle.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleButtonTestNg, ToggleButtonPatternTest016, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create bubble and get frameNode.
     */
    TestProperty testProperty;
    testProperty.isOn = std::make_optional(IS_ON);
    RefPtr<FrameNode> frameNode = CreateToggleButtonFrameNode(testProperty);
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. get pattern and update frameNode.
     * @tc.expected: step2. related function is called.
     */
    auto togglePattern = AceType::DynamicCast<ToggleButtonPattern>(frameNode->GetPattern());
    ASSERT_NE(togglePattern, nullptr);

    // set toggleTheme to themeManager before using themeManager to get toggleTheme
    auto themeManagerSecond = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManagerSecond);
    EXPECT_CALL(*themeManagerSecond, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<ToggleTheme>()));
    EXPECT_CALL(*themeManagerSecond, GetTheme(_, _)).WillRepeatedly(Return(AceType::MakeRefPtr<ToggleTheme>()));

    /**
     * @tc.steps: step3. Creat child node but not set font size.
     * @tc.expected: step3. Child frame node's font size synchronized with parent.
     */
    RefPtr<FrameNode> childrenNode =
        FrameNode::GetOrCreateFrameNode("childTag", 1, []() { return AceType::MakeRefPtr<TextPattern>(); });
    frameNode->children_.emplace_back(childrenNode);
    togglePattern->OnModifyDone();
    auto textNode = AceType::DynamicCast<FrameNode>(frameNode->GetFirstChild());
    ASSERT_NE(textNode, nullptr);
    auto textLayoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);

    /**
     * @tc.steps: step2. ToggleButtonPattern UpdateButtonStyle
     * @tc.expected: Check the param value
     */
    togglePattern->SetIsFocus(true);
    togglePattern->HandleFocusEvent();
    togglePattern->AddIsFocusActiveUpdateEvent();
    togglePattern->UpdateButtonStyle();
    EXPECT_EQ(togglePattern->isScale_, true);
    EXPECT_EQ(togglePattern->isCheckedShadow_, true);
    EXPECT_EQ(togglePattern->isbgColorFocus_, true);

    /**
     * @tc.steps: step5. buttonPattern RemoveIsFocusActiveUpdateEvent.
     * @tc.expected: step5. check whether the properties is correct.
     */
    togglePattern->SetIsFocus(false);
    togglePattern->HandleBlurEvent();
    togglePattern->RemoveIsFocusActiveUpdateEvent();
    togglePattern->UpdateButtonStyle();
    EXPECT_EQ(togglePattern->isScale_, false);
    EXPECT_EQ(togglePattern->isCheckedShadow_, false);
    EXPECT_EQ(togglePattern->isbgColorFocus_, true);
}

/**
 * @tc.name: ToggleButtonPatternTest017
 * @tc.desc: test ToggleButtonPattern::UpdateButtonStyle.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleButtonTestNg, ToggleButtonPatternTest017, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create bubble and get frameNode.
     */
    TestProperty testProperty;
    testProperty.isOn = std::make_optional(IS_ON);
    RefPtr<FrameNode> frameNode = CreateToggleButtonFrameNode(testProperty);
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. get pattern and update frameNode.
     * @tc.expected: step2. related function is called.
     */
    auto togglePattern = AceType::DynamicCast<ToggleButtonPattern>(frameNode->GetPattern());
    ASSERT_NE(togglePattern, nullptr);
    auto paintProperty = frameNode->GetPaintProperty<ToggleButtonPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    paintProperty->UpdateSelectedColor(SELECTED_COLOR);
    paintProperty->UpdateBackgroundColor(BACKGROUND_COLOR);

    // set toggleTheme to themeManager before using themeManager to get toggleTheme
    auto themeManagerSecond = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManagerSecond);
    EXPECT_CALL(*themeManagerSecond, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<ToggleTheme>()));
    EXPECT_CALL(*themeManagerSecond, GetTheme(_, _)).WillRepeatedly(Return(AceType::MakeRefPtr<ToggleTheme>()));

    /**
     * @tc.steps: step3. Creat child node but not set font size.
     * @tc.expected: step3. Child frame node's font size synchronized with parent.
     */
    RefPtr<FrameNode> childrenNode =
        FrameNode::GetOrCreateFrameNode("childTag", 1, []() { return AceType::MakeRefPtr<TextPattern>(); });
    frameNode->children_.emplace_back(childrenNode);
    togglePattern->OnModifyDone();
    auto textNode = AceType::DynamicCast<FrameNode>(frameNode->GetFirstChild());
    ASSERT_NE(textNode, nullptr);
    auto textLayoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);

    /**
     * @tc.steps: step3. pattern OnModifyDone and OnClick.
     * @tc.expected: step3. check whether the function is executed successfully.
     */
    auto pipeline = PipelineBase::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    auto toggleTheme = pipeline->GetTheme<ToggleTheme>();
    ASSERT_NE(toggleTheme, nullptr);
    auto renderContext = frameNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);

    togglePattern->OnModifyDone();
    togglePattern->SetIsFocus(true);
    togglePattern->OnClick();
    layoutProperty->UpdateAlignment(ALIGNMENT);
    EXPECT_EQ(ALIGNMENT, layoutProperty->GetPositionProperty()->GetAlignmentValue());
    EXPECT_EQ(togglePattern->isbgColorFocus_, false);

    // update isOn value
    togglePattern->isOn_ = false;
    togglePattern->OnModifyDone();
    paintProperty->UpdateIsOn(false);
    togglePattern->SetIsFocus(true);
    togglePattern->OnClick();
    EXPECT_EQ(togglePattern->isbgColorFocus_, false);
}

/**
 * @tc.name: ToggleButtonPatternTest018
 * @tc.desc: test ToggleButtonPattern::HandleHoverEvent.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleButtonTestNg, ToggleButtonPatternTest018, TestSize.Level1)
{
    TestProperty testProperty;
    testProperty.isOn = std::make_optional(IS_ON);
    RefPtr<FrameNode> frameNode = CreateToggleButtonFrameNode(testProperty);
    ASSERT_NE(frameNode, nullptr);
    auto togglePattern = AceType::DynamicCast<ToggleButtonPattern>(frameNode->GetPattern());
    ASSERT_NE(togglePattern, nullptr);
    auto buttonFrameNode = AceType::MakeRefPtr<FrameNode>("Button", 1, AceType::MakeRefPtr<ButtonPattern>());
    togglePattern->frameNode_ = std::move(buttonFrameNode);
    togglePattern->HandleHoverEvent(true);
    EXPECT_FALSE(togglePattern->isPress_);
    auto eventHub = buttonFrameNode->GetEventHub<EventHub>();
    eventHub->enabled_ = false;
    togglePattern->frameNode_ = std::move(buttonFrameNode);
    togglePattern->HandleHoverEvent(false);
    EXPECT_FALSE(togglePattern->isScale_);
    togglePattern->isScale_ = true;
    togglePattern->HandleHoverEvent(false);
    EXPECT_FALSE(togglePattern->isScale_);
    togglePattern->isPress_ = true;
    togglePattern->HandleHoverEvent(false);
    EXPECT_EQ(buttonFrameNode->GetFirstChild(), nullptr);
    togglePattern->isPress_ = false;
    togglePattern->HandleHoverEvent(true);
    EXPECT_EQ(buttonFrameNode->GetFirstChild(), nullptr);
    auto inputEventHub = buttonFrameNode->GetOrCreateInputEventHub();
    togglePattern->frameNode_ = std::move(buttonFrameNode);
    inputEventHub->hoverEffectType_ = HoverEffectType::NONE;
    togglePattern->HandleHoverEvent(true);
    EXPECT_EQ(inputEventHub->GetHoverEffect(), HoverEffectType::NONE);
    inputEventHub->hoverEffectType_ = HoverEffectType::SCALE;
    togglePattern->HandleHoverEvent(true);
    EXPECT_EQ(inputEventHub->GetHoverEffect(), HoverEffectType::SCALE);
}

/**
 * @tc.name: ToggleButtonPatternTest019
 * @tc.desc: test ToggleButtonPattern::OnAfterModifyDone.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleButtonTestNg, ToggleButtonPatternTest019, TestSize.Level1)
{
    TestProperty testProperty;
    testProperty.isOn = std::make_optional(IS_ON);
    RefPtr<FrameNode> frameNode = CreateToggleButtonFrameNode(testProperty);
    ASSERT_NE(frameNode, nullptr);
    auto togglePattern = AceType::DynamicCast<ToggleButtonPattern>(frameNode->GetPattern());
    ASSERT_NE(togglePattern, nullptr);
    auto buttonFrameNode = AceType::MakeRefPtr<FrameNode>("Button", 1, AceType::MakeRefPtr<ButtonPattern>());
    togglePattern->frameNode_ = std::move(buttonFrameNode);
    togglePattern->OnAfterModifyDone();
    buttonFrameNode->UpdateInspectorId("Toggle");
    togglePattern->frameNode_ = std::move(buttonFrameNode);
    togglePattern->OnAfterModifyDone();
}

/**
 * @tc.name: OnColorConfigurationUpdate
 * @tc.desc: test ToggleButtonPattern::OnColorConfigurationUpdate.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleButtonTestNg, OnColorConfigurationUpdate, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create bubble and get frameNode.
     */
    TestProperty testProperty;
    testProperty.isOn = std::make_optional(IS_ON);
    RefPtr<FrameNode> frameNode = CreateToggleButtonFrameNode(testProperty);
    ASSERT_NE(frameNode, nullptr);
    auto togglePattern = AceType::DynamicCast<ToggleButtonPattern>(frameNode->GetPattern());
    ASSERT_NE(togglePattern, nullptr);
    auto pipeline = frameNode->GetContext();
    ASSERT_NE(pipeline, nullptr);
    auto theme = pipeline->GetTheme<ToggleTheme>();
    ASSERT_NE(theme, nullptr);
    auto pops = frameNode->GetPaintProperty<ToggleButtonPaintProperty>();
    ASSERT_NE(pops, nullptr);

    /**
     * @tc.steps: step2. pattern OnColorConfigurationUpdate.
     * @tc.expected: step2. check whether the function is executed successfully.
     */
    Color color = theme->GetCheckedColor();
    std::vector<std::pair<bool, bool>> vec { { true, false }, { true, true }, { false, true }, { false, false } };
    for (const auto& pair : vec) {
        g_isConfigChangePerform = pair.first;
        pops->UpdateSelectedColorSetByUser(pair.second);
        togglePattern->OnColorConfigurationUpdate();
        if (pair.first && !pair.second) {
            auto ret = pops->GetSelectedColor();
            EXPECT_EQ(ret.value_or(Color::BLACK), color);
        }
    }
    g_isConfigChangePerform = false;
}

/**
 * @tc.name: SetBackgroundColor
 * @tc.desc: test ToggleButtonModelNG::SetBackgroundColor.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleButtonTestNg, SetBackgroundColor, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create bubble and get frameNode.
     */
    ToggleButtonModelNG toggleButtonModelNG;
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto buttonNode = FrameNode::CreateFrameNode(V2::BUTTON_ETS_TAG, 1, AceType::MakeRefPtr<ButtonPattern>());
    EXPECT_NE(buttonNode, nullptr);
    stack->Push(buttonNode);

    /**
     * @tc.steps: step2. call SetBackgroundColor for button frameNode with flag true.
     * @tc.expected: step2. context background color should be updated to BACKGROUND_COLOR.
     */
    toggleButtonModelNG.SetBackgroundColor(AceType::RawPtr(buttonNode), BACKGROUND_COLOR, true);
    auto context = buttonNode->GetRenderContext();
    EXPECT_NE(context, nullptr);
    EXPECT_EQ(context->GetBackgroundColorValue(), BACKGROUND_COLOR);

    /**
     * @tc.steps: step3. create toggle frameNode and get its pattern and paint property.
     */
    auto toggleNode = FrameNode::CreateFrameNode(V2::TOGGLE_ETS_TAG, 1, AceType::MakeRefPtr<ToggleButtonPattern>());
    EXPECT_NE(toggleNode, nullptr);
    auto pattern = AceType::DynamicCast<ToggleButtonPattern>(toggleNode->GetPattern());
    EXPECT_NE(pattern, nullptr);
    auto paintProperty = pattern->GetPaintProperty<ToggleButtonPaintProperty>();
    EXPECT_NE(paintProperty, nullptr);

    /**
     * @tc.steps: step4. call SetBackgroundColor for toggle frameNode with flag true or false.
     * @tc.expected: step4. toggle background color should be updated.
     */
    toggleButtonModelNG.SetBackgroundColor(AceType::RawPtr(toggleNode), BACKGROUND_COLOR, true);
    EXPECT_EQ(paintProperty->GetBackgroundColor(), BACKGROUND_COLOR);
    toggleButtonModelNG.SetBackgroundColor(AceType::RawPtr(toggleNode), BACKGROUND_COLOR, false);
    EXPECT_NE(paintProperty->GetBackgroundColor(), BACKGROUND_COLOR);
}
} // namespace OHOS::Ace::NG
