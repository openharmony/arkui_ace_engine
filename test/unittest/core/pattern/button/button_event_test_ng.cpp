/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include <algorithm>
#include <cstddef>
#include <optional>
#include <utility>

#include "gtest/gtest.h"

#define protected public
#define private public
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

#include "base/geometry/dimension.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/components/button/button_theme.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/color.h"
#include "core/components/common/properties/text_style.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/event/focus_hub.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/pattern/button/button_layout_property.h"
#include "core/components_ng/pattern/button/button_model_ng.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/button/toggle_button_pattern.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/pattern/text/text_styles.h"
#include "core/event/touch_event.h"
#include "core/pipeline_ng/ui_task_scheduler.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr bool STATE_EFFECT = true;
const std::string CREATE_VALUE = "Hello World";
const Dimension BORDER_RADIUS = 5.0_vp;
const Color FONT_COLOR = Color(0XFFFF0000);
const Dimension DEFAULT_HEIGTH = 40.0_vp;
const float START_OPACITY = 0.0f;
const float END_OPACITY = 0.1f;
const int32_t DURATION = 100;

struct CreateWithPara createWithPara = { std::make_optional(true), std::make_optional(CREATE_VALUE),
    std::make_optional(true), std::make_optional(ButtonType::CAPSULE), std::make_optional(true), std::nullopt,
    std::nullopt, std::nullopt };
struct CreateWithPara createWithParaByRoundedRect = { std::make_optional(true), std::make_optional(CREATE_VALUE),
    std::make_optional(true), std::make_optional(ButtonType::ROUNDED_RECTANGLE), std::make_optional(true), std::nullopt,
    std::nullopt, std::nullopt };
} // namespace

struct TestProperty {
    std::optional<ButtonType> typeValue = std::nullopt;
    std::optional<bool> stateEffectValue = std::nullopt;
    std::optional<Dimension> fontSizeValue = std::nullopt;
    std::optional<Ace::FontWeight> fontWeightValue = std::nullopt;
    std::optional<Color> textColorValue = std::nullopt;
    std::optional<Ace::FontStyle> fontStyleValue = std::nullopt;
    std::optional<std::vector<std::string>> fontFamilyValue = std::nullopt;
    std::optional<Dimension> borderRadius = std::nullopt;
    std::optional<ButtonStyleMode> buttonStyle = std::nullopt;
    std::optional<ControlSize> controlSize = std::nullopt;
    std::optional<ButtonRole> buttonRole = std::nullopt;
};

struct LableStyleProperty {
    std::optional<Ace::TextOverflow> textOverflow = std::nullopt;
    std::optional<uint32_t> maxLines = std::nullopt;
    std::optional<Dimension> minFontSize = std::nullopt;
    std::optional<Dimension> maxFontSize = std::nullopt;
    std::optional<Dimension> fontSize = std::nullopt;
    std::optional<Ace::FontWeight> fontWeight = std::nullopt;
    std::optional<std::vector<std::string>> fontFamily = std::nullopt;
    std::optional<Ace::FontStyle> fontStyle = std::nullopt;
    std::optional<Ace::TextHeightAdaptivePolicy> adaptHeight;
};

class ButtonEventTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    static void FontWeightTest(RefPtr<ButtonLayoutProperty> buttonLayoutProperty, RefPtr<ButtonPattern> buttonPattern,
        RefPtr<TextLayoutProperty> textLayoutProp);

protected:
    RefPtr<FrameNode> CreateLabelButtonParagraph(const std::string& createValue, const TestProperty& testProperty);
    RefPtr<FrameNode> CreateLabelButtonParagraphForLableStyle(
        const std::string& createValue, const LableStyleProperty& lableStyleProperty);
};

void ButtonEventTestNg::SetUpTestCase()
{
    MockPipelineContext::SetUp();
    // set buttonTheme to themeManager before using themeManager to get buttonTheme
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto buttonTheme = AceType::MakeRefPtr<ButtonTheme>();
    buttonTheme->height_ = DEFAULT_HEIGTH;

    std::unordered_map<ButtonStyleMode, Color> normalBgColorMap_ = { { ButtonStyleMode::EMPHASIZE, Color::RED },
        { ButtonStyleMode::NORMAL, Color::GRAY }, { ButtonStyleMode::TEXT, Color::BLUE } };
    std::unordered_map<ButtonStyleMode, Color> errorBgColorMap_ = { { ButtonStyleMode::EMPHASIZE, Color::WHITE },
        { ButtonStyleMode::NORMAL, Color::GRAY }, { ButtonStyleMode::TEXT, Color::BLUE } };
    buttonTheme->bgColorMap_.emplace(ButtonRole::NORMAL, normalBgColorMap_);
    buttonTheme->bgColorMap_.emplace(ButtonRole::ERROR, errorBgColorMap_);
    buttonTheme->textColorMap_.insert(std::pair<ButtonStyleMode, Color>(ButtonStyleMode::EMPHASIZE, Color::BLACK));
    buttonTheme->textColorMap_.insert(std::pair<ButtonStyleMode, Color>(ButtonStyleMode::NORMAL, Color::BLUE));
    buttonTheme->textColorMap_.insert(std::pair<ButtonStyleMode, Color>(ButtonStyleMode::TEXT, Color::WHITE));
    buttonTheme->textColorByRoleMap_.insert(std::pair<ButtonRole, Color>(ButtonRole::NORMAL, Color::BLACK));
    buttonTheme->textColorByRoleMap_.insert(std::pair<ButtonRole, Color>(ButtonRole::ERROR, Color::RED));

    buttonTheme->heightMap_.emplace(std::pair<ControlSize, Dimension>(ControlSize::SMALL, DEFAULT_HEIGTH));
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(buttonTheme));
}

void ButtonEventTestNg::TearDownTestCase()
{
    MockPipelineContext::TearDown();
}

void ButtonEventTestNg::FontWeightTest(RefPtr<ButtonLayoutProperty> buttonLayoutProperty,
    RefPtr<ButtonPattern> buttonPattern, RefPtr<TextLayoutProperty> textLayoutProp)
{
    buttonLayoutProperty->UpdateFontWeight(Ace::FontWeight::BOLD);
    buttonPattern->OnModifyDone();
    EXPECT_EQ(textLayoutProp->GetFontWeight(), Ace::FontWeight::BOLD);

    buttonLayoutProperty->UpdateFontWeight(Ace::FontWeight::BOLDER);
    buttonPattern->OnModifyDone();
    EXPECT_EQ(textLayoutProp->GetFontWeight(), Ace::FontWeight::BOLDER);

    buttonLayoutProperty->UpdateFontWeight(Ace::FontWeight::LIGHTER);
    buttonPattern->OnModifyDone();
    EXPECT_EQ(textLayoutProp->GetFontWeight(), Ace::FontWeight::LIGHTER);

    buttonLayoutProperty->UpdateFontWeight(Ace::FontWeight::MEDIUM);
    buttonPattern->OnModifyDone();
    EXPECT_EQ(textLayoutProp->GetFontWeight(), Ace::FontWeight::MEDIUM);

    buttonLayoutProperty->UpdateFontWeight(Ace::FontWeight::NORMAL);
    buttonPattern->OnModifyDone();
    EXPECT_EQ(textLayoutProp->GetFontWeight(), Ace::FontWeight::NORMAL);

    buttonLayoutProperty->UpdateFontWeight(Ace::FontWeight::REGULAR);
    buttonPattern->OnModifyDone();
    EXPECT_EQ(textLayoutProp->GetFontWeight(), Ace::FontWeight::REGULAR);

    buttonLayoutProperty->UpdateFontWeight(Ace::FontWeight::W100);
    buttonPattern->OnModifyDone();
    EXPECT_EQ(textLayoutProp->GetFontWeight(), Ace::FontWeight::W100);

    buttonLayoutProperty->UpdateFontWeight(Ace::FontWeight::W200);
    buttonPattern->OnModifyDone();
    EXPECT_EQ(textLayoutProp->GetFontWeight(), Ace::FontWeight::W200);

    buttonLayoutProperty->UpdateFontWeight(Ace::FontWeight::W300);
    buttonPattern->OnModifyDone();
    EXPECT_EQ(textLayoutProp->GetFontWeight(), Ace::FontWeight::W300);

    buttonLayoutProperty->UpdateFontWeight(Ace::FontWeight::W400);
    buttonPattern->OnModifyDone();
    EXPECT_EQ(textLayoutProp->GetFontWeight(), Ace::FontWeight::W400);

    buttonLayoutProperty->UpdateFontWeight(Ace::FontWeight::W500);
    buttonPattern->OnModifyDone();
    EXPECT_EQ(textLayoutProp->GetFontWeight(), Ace::FontWeight::W500);

    buttonLayoutProperty->UpdateFontWeight(Ace::FontWeight::W600);
    buttonPattern->OnModifyDone();
    EXPECT_EQ(textLayoutProp->GetFontWeight(), Ace::FontWeight::W600);

    buttonLayoutProperty->UpdateFontWeight(Ace::FontWeight::W700);
    buttonPattern->OnModifyDone();
    EXPECT_EQ(textLayoutProp->GetFontWeight(), Ace::FontWeight::W700);

    buttonLayoutProperty->UpdateFontWeight(Ace::FontWeight::W800);
    buttonPattern->OnModifyDone();
    EXPECT_EQ(textLayoutProp->GetFontWeight(), Ace::FontWeight::W800);

    buttonLayoutProperty->UpdateFontWeight(Ace::FontWeight::W900);
    buttonPattern->OnModifyDone();
    EXPECT_EQ(textLayoutProp->GetFontWeight(), Ace::FontWeight::W900);
}

RefPtr<FrameNode> ButtonEventTestNg::CreateLabelButtonParagraph(
    const std::string& createValue, const TestProperty& testProperty)
{
    ButtonModelNG buttonModelNG;
    std::list<RefPtr<Component>> buttonChildren;
    createWithPara.parseSuccess = true;
    createWithPara.label = createValue;
    buttonModelNG.CreateWithLabel(createWithPara, buttonChildren);
    if (testProperty.typeValue.has_value()) {
        buttonModelNG.SetType(static_cast<int32_t>(testProperty.typeValue.value()));
    }
    if (testProperty.stateEffectValue.has_value()) {
        buttonModelNG.SetStateEffect(testProperty.stateEffectValue.value());
    }
    if (testProperty.fontSizeValue.has_value()) {
        buttonModelNG.SetFontSize(testProperty.fontSizeValue.value());
    }
    if (testProperty.fontWeightValue.has_value()) {
        buttonModelNG.SetFontWeight(testProperty.fontWeightValue.value());
    }
    if (testProperty.textColorValue.has_value()) {
        buttonModelNG.SetFontColor(testProperty.textColorValue.value());
    }
    if (testProperty.fontStyleValue.has_value()) {
        buttonModelNG.SetFontStyle(testProperty.fontStyleValue.value());
    }
    if (testProperty.fontFamilyValue.has_value()) {
        buttonModelNG.SetFontFamily(testProperty.fontFamilyValue.value());
    }
    if (testProperty.borderRadius.has_value()) {
        buttonModelNG.SetBorderRadius(testProperty.borderRadius.value());
    }
    if (testProperty.buttonStyle.has_value()) {
        buttonModelNG.SetButtonStyle(testProperty.buttonStyle.value());
    }
    if (testProperty.controlSize.has_value()) {
        buttonModelNG.SetControlSize(testProperty.controlSize.value());
    }
    if (testProperty.buttonRole.has_value()) {
        buttonModelNG.SetRole(testProperty.buttonRole.value());
    }
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    return AceType::DynamicCast<FrameNode>(element);
}

RefPtr<FrameNode> ButtonEventTestNg::CreateLabelButtonParagraphForLableStyle(
    const std::string& createValue, const LableStyleProperty& lableStyleProperty)
{
    ButtonParameters buttonParameters;
    ButtonModelNG buttonModelNG;
    std::list<RefPtr<Component>> buttonChildren;
    buttonModelNG.CreateWithLabel(createWithPara, buttonChildren);
    if (lableStyleProperty.textOverflow.has_value()) {
        buttonParameters.textOverflow = lableStyleProperty.textOverflow;
    }
    if (lableStyleProperty.maxLines.has_value()) {
        buttonParameters.maxLines = lableStyleProperty.maxLines;
    }
    if (lableStyleProperty.minFontSize.has_value()) {
        buttonParameters.minFontSize = lableStyleProperty.minFontSize;
    }
    if (lableStyleProperty.maxFontSize.has_value()) {
        buttonParameters.maxFontSize = lableStyleProperty.maxFontSize;
    }
    if (lableStyleProperty.fontSize.has_value()) {
        buttonParameters.fontSize = lableStyleProperty.fontSize;
    }
    if (lableStyleProperty.fontWeight.has_value()) {
        buttonParameters.fontWeight = lableStyleProperty.fontWeight;
    }
    if (lableStyleProperty.fontFamily.has_value()) {
        buttonParameters.fontFamily = lableStyleProperty.fontFamily;
    }
    if (lableStyleProperty.fontStyle.has_value()) {
        buttonParameters.fontStyle = lableStyleProperty.fontStyle;
    }
    buttonModelNG.SetLabelStyle(buttonParameters);

    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    return AceType::DynamicCast<FrameNode>(element);
}

/**
 * @tc.name: ButtonEventTest001
 * @tc.desc: test button pattern touch event.
 * @tc.type: FUNC
 */
HWTEST_F(ButtonEventTestNg, ButtonEventTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create bubble and get frameNode.
     */
    TestProperty testProperty;
    auto frameNode = CreateLabelButtonParagraph(CREATE_VALUE, testProperty);
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: test buttonPattern HandlePressedStyle HandleNormalStyle function.
     * @tc.expected: step3. check whether the function is executed.
     */
    auto buttonPattern = frameNode->GetPattern<ButtonPattern>();
    ASSERT_NE(buttonPattern, nullptr);
    buttonPattern->HandlePressedStyle();
    buttonPattern->HandleNormalStyle();

    // frameNode SetStateEffect
    auto buttonEventHub = frameNode->GetEventHub<ButtonEventHub>();
    CHECK_NULL_VOID(buttonEventHub);
    buttonEventHub->SetStateEffect(STATE_EFFECT);
    buttonPattern->isSetClickedColor_ = true;
    buttonPattern->clickedColor_ = FONT_COLOR;
    buttonPattern->HandlePressedStyle();
    buttonPattern->HandleNormalStyle();
}

/**
 * @tc.name: ButtonEventTest002
 * @tc.desc: test button pattern OnModifyDone.
 * @tc.type: FUNC
 */
HWTEST_F(ButtonEventTestNg, ButtonEventTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create button and get frameNode.
     */
    LableStyleProperty lableStyleProperty;
    auto frameNode = CreateLabelButtonParagraphForLableStyle(CREATE_VALUE, lableStyleProperty);
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::BUTTON_ETS_TAG);

    /**
     * @tc.steps: step2. get pattern and update frameNode.
     * @tc.expected: step2. related function is called.
     */
    auto buttonPattern = frameNode->GetPattern<ButtonPattern>();
    ASSERT_NE(buttonPattern, nullptr);
    buttonPattern->OnModifyDone();
    auto buttonLayoutProperty = frameNode->GetLayoutProperty<ButtonLayoutProperty>();
    ASSERT_NE(buttonLayoutProperty, nullptr);
    std::vector<std::string> fontFamily = { "sans-serif" };
    // update layout property
    buttonLayoutProperty->UpdateTextOverflow(TextOverflow::CLIP);
    buttonLayoutProperty->UpdateMaxLines(10);
    buttonLayoutProperty->UpdateMinFontSize(Ace::Dimension(15));
    buttonLayoutProperty->UpdateMaxFontSize(Ace::Dimension(50));
    buttonLayoutProperty->UpdateFontSize(Ace::Dimension(20));
    buttonLayoutProperty->UpdateFontWeight(Ace::FontWeight::W100);
    buttonLayoutProperty->UpdateFontFamily(fontFamily);
    buttonLayoutProperty->UpdateFontStyle(Ace::FontStyle::NORMAL);
    buttonLayoutProperty->UpdateHeightAdaptivePolicy(Ace::TextHeightAdaptivePolicy::LAYOUT_CONSTRAINT_FIRST);

    /**
     * @tc.steps: step3. buttonPattern OnModifyDone.
     * @tc.expected: step3. check whether the properties is correct.
     */

    // set touchEventActuator_
    std::function<void(UIState)> touchEvent = [](const UIState& state) {};
    buttonPattern->touchListener_ = touchEvent;
    buttonPattern->OnModifyDone();
    auto text = AceType::DynamicCast<FrameNode>(frameNode->GetFirstChild());
    ASSERT_NE(text, nullptr);
    auto textLayoutProp = text->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProp, nullptr);

    EXPECT_EQ(textLayoutProp->GetTextOverflow(), TextOverflow::CLIP);
    EXPECT_EQ(textLayoutProp->GetMaxLines(), 10);
    EXPECT_EQ(buttonLayoutProperty->GetMinFontSize()->ConvertToPx(), 15);
    EXPECT_EQ(buttonLayoutProperty->GetMaxFontSize()->ConvertToPx(), 50);
    EXPECT_EQ(textLayoutProp->GetFontSize()->ConvertToPx(), 20);
    EXPECT_EQ(textLayoutProp->GetFontWeight(), Ace::FontWeight::W100);
    EXPECT_EQ(textLayoutProp->GetFontFamily(), fontFamily);
    EXPECT_EQ(textLayoutProp->GetItalicFontStyle(), Ace::FontStyle::NORMAL);
    EXPECT_EQ(textLayoutProp->GetHeightAdaptivePolicy(), Ace::TextHeightAdaptivePolicy::LAYOUT_CONSTRAINT_FIRST);
}

/**
 * @tc.name: ButtonEventTest003
 * @tc.desc: test textOverflow enum value.
 * @tc.type: FUNC
 */
HWTEST_F(ButtonEventTestNg, ButtonEventTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create button and get frameNode.
     */
    TestProperty testProperty;
    testProperty.borderRadius = std::make_optional(BORDER_RADIUS);
    auto frameNode = CreateLabelButtonParagraph(CREATE_VALUE, testProperty);
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::BUTTON_ETS_TAG);

    /**
     * @tc.steps: step2. get pattern and update frameNode.
     * @tc.expected: step2. related function is called.
     */
    auto buttonPattern = frameNode->GetPattern<ButtonPattern>();
    ASSERT_NE(buttonPattern, nullptr);
    auto buttonLayoutProperty = frameNode->GetLayoutProperty<ButtonLayoutProperty>();
    ASSERT_NE(buttonLayoutProperty, nullptr);

    /**
     * @tc.steps: step3. buttonPattern OnModifyDone.
     * @tc.expected: step3. check whether the properties is correct.
     */

    // set touchEventActuator_
    std::function<void(UIState)> touchEvent = [](const UIState& state) {};
    buttonPattern->touchListener_ = touchEvent;
    auto text = AceType::DynamicCast<FrameNode>(frameNode->GetFirstChild());
    ASSERT_NE(text, nullptr);
    auto textLayoutProp = text->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProp, nullptr);

    buttonLayoutProperty->UpdateTextOverflow(TextOverflow::CLIP);
    buttonPattern->OnModifyDone();
    EXPECT_EQ(textLayoutProp->GetTextOverflow(), TextOverflow::CLIP);

    buttonLayoutProperty->UpdateTextOverflow(TextOverflow::ELLIPSIS);
    buttonPattern->OnModifyDone();
    EXPECT_EQ(textLayoutProp->GetTextOverflow(), TextOverflow::ELLIPSIS);

    buttonLayoutProperty->UpdateTextOverflow(TextOverflow::NONE);
    buttonPattern->OnModifyDone();
    EXPECT_EQ(textLayoutProp->GetTextOverflow(), TextOverflow::NONE);

    buttonLayoutProperty->UpdateTextOverflow(TextOverflow::MARQUEE);
    buttonPattern->OnModifyDone();
    EXPECT_EQ(textLayoutProp->GetTextOverflow(), TextOverflow::MARQUEE);
}

/**
 * @tc.name: ButtonEventTest004
 * @tc.desc: test fontStyle enum value.
 * @tc.type: FUNC
 */
HWTEST_F(ButtonEventTestNg, ButtonEventTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create button and get frameNode.
     */
    TestProperty testProperty;
    testProperty.borderRadius = std::make_optional(BORDER_RADIUS);
    auto frameNode = CreateLabelButtonParagraph(CREATE_VALUE, testProperty);
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::BUTTON_ETS_TAG);

    /**
     * @tc.steps: step2. get pattern and update frameNode.
     * @tc.expected: step2. related function is called.
     */
    auto buttonPattern = frameNode->GetPattern<ButtonPattern>();
    ASSERT_NE(buttonPattern, nullptr);
    auto buttonLayoutProperty = frameNode->GetLayoutProperty<ButtonLayoutProperty>();
    ASSERT_NE(buttonLayoutProperty, nullptr);

    /**
     * @tc.steps: step3. buttonPattern OnModifyDone.
     * @tc.expected: step3. check whether the properties is correct.
     */

    // set touchEventActuator_
    std::function<void(UIState)> touchEvent = [](const UIState& state) {};
    buttonPattern->touchListener_ = touchEvent;
    auto text = AceType::DynamicCast<FrameNode>(frameNode->GetFirstChild());
    ASSERT_NE(text, nullptr);
    auto textLayoutProp = text->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProp, nullptr);

    buttonLayoutProperty->UpdateFontStyle(Ace::FontStyle::ITALIC);
    buttonPattern->OnModifyDone();
    EXPECT_EQ(textLayoutProp->GetItalicFontStyle(), Ace::FontStyle::ITALIC);

    buttonLayoutProperty->UpdateFontStyle(Ace::FontStyle::NORMAL);
    buttonPattern->OnModifyDone();
    EXPECT_EQ(textLayoutProp->GetItalicFontStyle(), Ace::FontStyle::NORMAL);
}

/**
 * @tc.name: ButtonEventTest005
 * @tc.desc: test TextHeightAdaptivePolicy and fontWeight enum value.
 * @tc.type: FUNC
 */
HWTEST_F(ButtonEventTestNg, ButtonEventTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create button and get frameNode.
     */
    TestProperty testProperty;
    testProperty.borderRadius = std::make_optional(BORDER_RADIUS);
    auto frameNode = CreateLabelButtonParagraph(CREATE_VALUE, testProperty);
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::BUTTON_ETS_TAG);

    /**
     * @tc.steps: step2. get pattern and update frameNode.
     * @tc.expected: step2. related function is called.
     */
    auto buttonPattern = frameNode->GetPattern<ButtonPattern>();
    ASSERT_NE(buttonPattern, nullptr);
    auto buttonLayoutProperty = frameNode->GetLayoutProperty<ButtonLayoutProperty>();
    ASSERT_NE(buttonLayoutProperty, nullptr);

    /**
     * @tc.steps: step3. buttonPattern OnModifyDone.
     * @tc.expected: step3. check whether the properties is correct.
     */

    // set touchEventActuator_
    std::function<void(UIState)> touchEvent = [](const UIState& state) {};
    buttonPattern->touchListener_ = touchEvent;
    auto text = AceType::DynamicCast<FrameNode>(frameNode->GetFirstChild());
    ASSERT_NE(text, nullptr);
    auto textLayoutProp = text->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProp, nullptr);

    buttonLayoutProperty->UpdateHeightAdaptivePolicy(Ace::TextHeightAdaptivePolicy::MAX_LINES_FIRST);
    buttonPattern->OnModifyDone();
    EXPECT_EQ(textLayoutProp->GetHeightAdaptivePolicy(), Ace::TextHeightAdaptivePolicy::MAX_LINES_FIRST);

    buttonLayoutProperty->UpdateHeightAdaptivePolicy(Ace::TextHeightAdaptivePolicy::MIN_FONT_SIZE_FIRST);
    buttonPattern->OnModifyDone();
    EXPECT_EQ(textLayoutProp->GetHeightAdaptivePolicy(), Ace::TextHeightAdaptivePolicy::MIN_FONT_SIZE_FIRST);

    buttonLayoutProperty->UpdateHeightAdaptivePolicy(Ace::TextHeightAdaptivePolicy::LAYOUT_CONSTRAINT_FIRST);
    buttonPattern->OnModifyDone();
    EXPECT_EQ(textLayoutProp->GetHeightAdaptivePolicy(), Ace::TextHeightAdaptivePolicy::LAYOUT_CONSTRAINT_FIRST);

    FontWeightTest(buttonLayoutProperty, buttonPattern, textLayoutProp);
}

/**
 * @tc.name: ButtonEventTest006
 * @tc.desc: Test touch event callback
 * @tc.type: FUNC
 */
HWTEST_F(ButtonEventTestNg, ButtonEventTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create TestProperty.
     */
    TestProperty testProperty;
    testProperty.typeValue = std::make_optional(ButtonType::CIRCLE);
    testProperty.stateEffectValue = std::make_optional(STATE_EFFECT);
    /**
     * @tc.steps: step2. create button with TestProperty.
     */
    auto frameNode = CreateLabelButtonParagraph(CREATE_VALUE, testProperty);
    ASSERT_NE(frameNode, nullptr);

    auto buttonPattern = frameNode->GetPattern<ButtonPattern>();
    ASSERT_NE(buttonPattern, nullptr);
    buttonPattern->InitTouchEvent();
    auto eventHub = frameNode->GetEventHub<ButtonEventHub>();
    ASSERT_NE(eventHub, nullptr);
    std::function<void(UIState)>& touchListener = buttonPattern->GetTouchListener();
    ASSERT_NE(touchListener, nullptr);
    /**
     * @tc.steps: step3. change button params.
     */
    buttonPattern->isSetClickedColor_ = true;
    buttonPattern->clickedColor_ = Color::RED;
    auto renderContext = frameNode->GetRenderContext();
    renderContext->UpdateBackgroundColor(Color::BLUE);

    /**
     * @tc.steps: step4. mock touch event and call touch callback.
     * @tc.expected: step4. the button background color will change when touch down.
     */
    UIState pressedState = UI_STATE_PRESSED;
    eventHub->AddSupportedUIStateWithCallback(pressedState, touchListener, true);
    buttonPattern->HandlePressedStyle();
    EXPECT_EQ(buttonPattern->backgroundColor_, Color::BLUE);
    EXPECT_EQ(renderContext->GetBackgroundColorValue(), Color::RED);
    /**
     * @tc.steps: step5. change the touch type.
     * @tc.expected: step5. the button background color will restore when touch up.
     */
    UIState normalState = UI_STATE_NORMAL;
    eventHub->AddSupportedUIStateWithCallback(normalState, touchListener, true);
    buttonPattern->HandleNormalStyle();
    EXPECT_EQ(renderContext->GetBackgroundColorValue(), Color::BLUE);
}

/**
 * @tc.name: ButtonEventTest007
 * @tc.desc: Test HandleEnable disable
 * @tc.type: FUNC
 */
HWTEST_F(ButtonEventTestNg, ButtonEventTest007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create TestProperty.
     */
    TestProperty testProperty;
    testProperty.typeValue = std::make_optional(ButtonType::CIRCLE);
    testProperty.stateEffectValue = std::make_optional(STATE_EFFECT);
    /**
     * @tc.steps: step2. create button with TestProperty.
     */
    auto frameNode = CreateLabelButtonParagraph(CREATE_VALUE, testProperty);
    ASSERT_NE(frameNode, nullptr);

    auto buttonPattern = frameNode->GetPattern<ButtonPattern>();
    ASSERT_NE(buttonPattern, nullptr);
    auto eventHub = frameNode->GetEventHub<EventHub>();
    /**
     * @tc.steps: step3. make button disable.
     */
    eventHub->SetEnabled(false);
    frameNode->eventHub_ = eventHub;

    auto renderContext = frameNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    auto pipeline = PipelineBase::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    auto theme = pipeline->GetTheme<ButtonTheme>();
    ASSERT_NE(theme, nullptr);
    auto alpha = theme->GetBgDisabledAlpha();
    auto originalOpacity = renderContext->GetOpacityValue(1.0);
    /**
     * @tc.steps: step4. call button handle enable.
     * @tc.expected: step4. the button opacity is as expected.
     */
    buttonPattern->HandleEnabled();
    EXPECT_EQ(renderContext->GetOpacityValue(1.0), alpha * originalOpacity);
}

/**
 * @tc.name: ButtonEventTest008
 * @tc.desc: Test AnimateTouchAndHover
 * @tc.type: FUNC
 */
HWTEST_F(ButtonEventTestNg, ButtonEventTest008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create button with TestProperty.
     */
    TestProperty testProperty;
    auto frameNode = CreateLabelButtonParagraph(CREATE_VALUE, testProperty);
    ASSERT_NE(frameNode, nullptr);
    auto buttonPattern = frameNode->GetPattern<ButtonPattern>();
    ASSERT_NE(buttonPattern, nullptr);
    auto context = frameNode->GetRenderContext();
    ASSERT_NE(context, nullptr);
    /**
     * @tc.steps: step2. try call AnimateTouchAndHover.
     * @tc.expected: step2. the hover status is as expected.
     */
    buttonPattern->AnimateTouchAndHover(context, START_OPACITY, END_OPACITY, DURATION, Curves::FRICTION);
    buttonPattern->AnimateTouchAndHover(context, END_OPACITY, START_OPACITY, DURATION, Curves::FRICTION);
    EXPECT_EQ(buttonPattern->isHover_, false);
}

/**
 * @tc.name: ButtonEventTest009
 * @tc.desc: Test HandleHoverEvent
 * @tc.type: FUNC
 */
HWTEST_F(ButtonEventTestNg, ButtonEventTest009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create button with TestProperty.
     */
    TestProperty testProperty;
    auto frameNode = CreateLabelButtonParagraph(CREATE_VALUE, testProperty);
    ASSERT_NE(frameNode, nullptr);
    auto buttonPattern = frameNode->GetPattern<ButtonPattern>();
    ASSERT_NE(buttonPattern, nullptr);
    auto eventHub = frameNode->GetEventHub<EventHub>();
    /**
     * @tc.steps: step2. change button disable and call HandleHoverEvent.
     * @tc.expected: step2. the hover status is as expected.
     */
    eventHub->SetEnabled(false);
    buttonPattern->HandleHoverEvent(true);
    EXPECT_EQ(buttonPattern->isHover_, true);
    /**
     * @tc.steps: step3. change button enable and call HandleHoverEvent.
     * @tc.expected: step3. the hover status is as expected.
     */
    eventHub->SetEnabled(true);
    buttonPattern->HandleHoverEvent(false);
    EXPECT_EQ(buttonPattern->isHover_, false);
}

/**
 * @tc.name: ButtonEventTest010
 * @tc.desc: Test SetButtonPress
 * @tc.type: FUNC
 */
HWTEST_F(ButtonEventTestNg, ButtonEventTest010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create button and get frameNode
     */
    TestProperty testProperty;
    ;
    auto frameNode = CreateLabelButtonParagraph(CREATE_VALUE, testProperty);
    ASSERT_NE(frameNode, nullptr);
    auto gesture = frameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(gesture, nullptr);

    /**
     * @tc.steps: step2. test SetButtonPress
     * @tc.expected: step2. x and y is set correct
     */
    auto buttonPattern = frameNode->GetPattern<ButtonPattern>();
    ASSERT_NE(buttonPattern, nullptr);
    GestureEventFunc callback = [](GestureEvent& info) {
        EXPECT_EQ(info.globalPoint_.GetX(), 1.0);
        EXPECT_EQ(info.globalPoint_.GetY(), 1.0);
    };
    auto clickEvent = AceType::MakeRefPtr<ClickEvent>(std::move(callback));
    gesture->AddClickEvent(clickEvent);
    buttonPattern->FireBuilder();
    buttonPattern->SetButtonPress(1.0, 1.0);
}
} // namespace OHOS::Ace::NG