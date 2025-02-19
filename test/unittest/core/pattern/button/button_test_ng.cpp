/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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
constexpr float ZERO = 0.0f;
constexpr float BUTTON_WIDTH = 200.0f;
constexpr float BUTTON_HEIGHT = 100.0f;
constexpr float TEXT_WIDTH = 100.0f;
constexpr float TEXT_HEIGHT = 50.0f;
constexpr float FULL_SCREEN_WIDTH = 720.0f;
constexpr float FULL_SCREEN_HEIGHT = 1136.0f;
constexpr bool STATE_EFFECT = true;
constexpr float BUTTON_ONLY_HAS_WIDTH_VALUE = 100.0f;
const SizeF BUTTON_SIZE(BUTTON_WIDTH, BUTTON_HEIGHT);
const SizeF TEXT_SIZE(TEXT_WIDTH, TEXT_HEIGHT);
const std::string CREATE_VALUE = "Hello World";
const std::string BUTTON_VALUE = "Test";
const std::string TEST_RESULT = "result_ok";
const std::string TEST_RESULT_CAPSULE = "capsule";
const std::string TEST_RESULT_DOWNLOAD = "download";
const ButtonType BUTTON_TYPE_CAPSULE_VALUE = ButtonType::CAPSULE;
const ButtonType BUTTON_TYPE_CUSTOM_VALUE = ButtonType::CUSTOM;
const ButtonType BUTTON_TYPE_DOWNLOAD_VALUE = ButtonType::DOWNLOAD;
const ButtonType BUTTON_TYPE_CIRCLE_VALUE = ButtonType::CIRCLE;
const ButtonType BUTTON_TYPE_ROUNDED_RECTANGLE_VALUE = ButtonType::ROUNDED_RECTANGLE;
const Dimension BUTTON_FONT_SIZE_VALUE = 30.0_vp;
const Dimension BORDER_RADIUS = 5.0_vp;
const Ace::FontWeight BUTTON_BOLD_FONT_WEIGHT_VALUE = Ace::FontWeight::BOLD;
const Ace::FontStyle BUTTON_ITALIC_FONT_STYLE_VALUE = Ace::FontStyle::ITALIC;
const Color BUTTON_TEXT_COLOR_VALUE = Color::RED;
const Color FONT_COLOR = Color(0XFFFF0000);
const std::vector<std::string> FONT_FAMILY_VALUE = { "cursive" };
const SizeF CONTAINER_SIZE(FULL_SCREEN_WIDTH, FULL_SCREEN_HEIGHT);
const SizeF BUTTON_ONLY_HAS_WIDTH_SIZE(BUTTON_ONLY_HAS_WIDTH_VALUE, BUTTON_ONLY_HAS_WIDTH_VALUE);
const Dimension DEFAULT_HEIGTH = 40.0_vp;
const uint32_t MAX_LINE_VALUE = 10;
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

class ButtonTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    static void FontWeightTest(RefPtr<ButtonLayoutProperty> buttonLayoutProperty, RefPtr<ButtonPattern> buttonPattern,
        RefPtr<TextLayoutProperty> textLayoutProp);

protected:
    RefPtr<FrameNode> CreateLabelButtonParagraph(const std::string& createValue, const TestProperty& testProperty);
    RefPtr<FrameNode> CreateLabelButtonParagraphByRoundedRect(
        const std::string& createValue, const TestProperty& testProperty);
    RefPtr<FrameNode> CreateChildButtonParagraph(const std::string& createValue, const TestProperty& testProperty);
    RefPtr<FrameNode> CreateLabelButtonParagraphForLableStyle(
        const std::string& createValue, const LableStyleProperty& lableStyleProperty);
};

void ButtonTestNg::SetUpTestCase()
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

void ButtonTestNg::TearDownTestCase()
{
    MockPipelineContext::TearDown();
}

void ButtonTestNg::FontWeightTest(RefPtr<ButtonLayoutProperty> buttonLayoutProperty,
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

PaddingProperty CreatePadding(float left, float top, float right, float bottom)
{
    PaddingProperty padding;
    padding.left = CalcLength(left);
    padding.right = CalcLength(right);
    padding.top = CalcLength(top);
    padding.bottom = CalcLength(bottom);
    return padding;
}
RefPtr<FrameNode> ButtonTestNg::CreateLabelButtonParagraphByRoundedRect(
    const std::string& createValue, const TestProperty& testProperty)
{
    ButtonModelNG buttonModelNG;
    std::list<RefPtr<Component>> buttonChildren;
    createWithPara.parseSuccess = true;
    createWithPara.label = createValue;
    buttonModelNG.CreateWithLabel(createWithParaByRoundedRect, buttonChildren);
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

RefPtr<FrameNode> ButtonTestNg::CreateLabelButtonParagraph(
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

RefPtr<FrameNode> ButtonTestNg::CreateChildButtonParagraph(
    const std::string& createValue, const TestProperty& testProperty)
{
    ButtonModelNG buttonModelNG;
    buttonModelNG.CreateWithChild(createWithPara);
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

    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    return AceType::DynamicCast<FrameNode>(element);
}

RefPtr<FrameNode> ButtonTestNg::CreateLabelButtonParagraphForLableStyle(
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
 * @tc.name: ButtonPatternTest001
 * @tc.desc: Test all the properties of button.
 * @tc.type: FUNC
 */
HWTEST_F(ButtonTestNg, ButtonPatternTest001, TestSize.Level1)
{
    TestProperty testProperty;
    testProperty.typeValue = std::make_optional(BUTTON_TYPE_CAPSULE_VALUE);
    RefPtr<FrameNode> frameNode = CreateLabelButtonParagraph(CREATE_VALUE, testProperty);
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<ButtonLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    EXPECT_EQ(layoutProperty->GetTypeValue(), BUTTON_TYPE_CAPSULE_VALUE);
}

/**
 * @tc.name: ButtonModelTest001
 * @tc.desc: Test all the properties of button.
 * @tc.type: FUNC
 */
HWTEST_F(ButtonTestNg, ButtonModelTest001, TestSize.Level1)
{
    TestProperty testProperty;
    testProperty.typeValue = std::make_optional(BUTTON_TYPE_CAPSULE_VALUE);
    RefPtr<FrameNode> frameNode = CreateChildButtonParagraph(CREATE_VALUE, testProperty);
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<ButtonLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    EXPECT_EQ(layoutProperty->GetTypeValue(), BUTTON_TYPE_CAPSULE_VALUE);
}

/**
 * @tc.name: ButtonPatternTest002
 * @tc.desc: Test all the properties of button.
 * @tc.type: FUNC
 */
HWTEST_F(ButtonTestNg, ButtonPatternTest002, TestSize.Level1)
{
    TestProperty testProperty;
    testProperty.typeValue = std::make_optional(BUTTON_TYPE_CUSTOM_VALUE);
    // create button without label
    ButtonModelNG buttonModelNG;
    std::list<RefPtr<Component>> buttonChildren;
    createWithPara.parseSuccess = false;
    buttonModelNG.CreateWithLabel(CREATE_VALUE);
    buttonModelNG.SetType(static_cast<int32_t>(testProperty.typeValue.value()));
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto buttonPattern = frameNode->GetPattern<ButtonPattern>();
    ASSERT_NE(buttonPattern, nullptr);
    buttonPattern->InitButtonLabel();
    RefPtr<LayoutProperty> layoutProperty = frameNode->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    RefPtr<ButtonLayoutProperty> buttonLayoutProperty = AceType::DynamicCast<ButtonLayoutProperty>(layoutProperty);
    ASSERT_NE(buttonLayoutProperty, nullptr);
    EXPECT_EQ(buttonLayoutProperty->GetTypeValue(), BUTTON_TYPE_CUSTOM_VALUE);
}

/**
 * @tc.name: ButtonPatternTest003
 * @tc.desc: Test all the properties of button.
 * @tc.type: FUNC
 */
HWTEST_F(ButtonTestNg, ButtonPatternTest003, TestSize.Level1)
{
    TestProperty testProperty;
    testProperty.typeValue = std::make_optional(BUTTON_TYPE_DOWNLOAD_VALUE);
    testProperty.fontSizeValue = std::make_optional(BUTTON_FONT_SIZE_VALUE);
    testProperty.fontWeightValue = std::make_optional(BUTTON_BOLD_FONT_WEIGHT_VALUE);
    RefPtr<FrameNode> frameNode = CreateLabelButtonParagraph(CREATE_VALUE, testProperty);
    ASSERT_NE(frameNode, nullptr);
    RefPtr<LayoutProperty> layoutProperty = frameNode->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    RefPtr<ButtonLayoutProperty> buttonLayoutProperty = AceType::DynamicCast<ButtonLayoutProperty>(layoutProperty);
    ASSERT_NE(buttonLayoutProperty, nullptr);
    EXPECT_EQ(buttonLayoutProperty->GetTypeValue(), BUTTON_TYPE_DOWNLOAD_VALUE);
    EXPECT_EQ(buttonLayoutProperty->GetFontSizeValue(), BUTTON_FONT_SIZE_VALUE);
    EXPECT_EQ(buttonLayoutProperty->GetFontWeightValue(), BUTTON_BOLD_FONT_WEIGHT_VALUE);
    EXPECT_EQ(buttonLayoutProperty->GetLabelValue(), CREATE_VALUE);
}

/**
 * @tc.name: ButtonPatternTest004
 * @tc.desc: Test all the properties of button.
 * @tc.type: FUNC
 */
HWTEST_F(ButtonTestNg, ButtonPatternTest004, TestSize.Level1)
{
    TestProperty testProperty;
    testProperty.typeValue = std::make_optional(BUTTON_TYPE_CIRCLE_VALUE);
    testProperty.textColorValue = std::make_optional(BUTTON_TEXT_COLOR_VALUE);
    testProperty.fontStyleValue = std::make_optional(BUTTON_ITALIC_FONT_STYLE_VALUE);
    testProperty.fontFamilyValue = std::make_optional(FONT_FAMILY_VALUE);
    auto frameNode = CreateLabelButtonParagraph(CREATE_VALUE, testProperty);
    ASSERT_NE(frameNode, nullptr);

    RefPtr<LayoutProperty> layoutProperty = frameNode->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    RefPtr<ButtonLayoutProperty> buttonLayoutProperty = AceType::DynamicCast<ButtonLayoutProperty>(layoutProperty);
    ASSERT_NE(buttonLayoutProperty, nullptr);
    EXPECT_EQ(buttonLayoutProperty->GetTypeValue(), BUTTON_TYPE_CIRCLE_VALUE);
    EXPECT_EQ(buttonLayoutProperty->GetFontColorValue(), BUTTON_TEXT_COLOR_VALUE);
    EXPECT_EQ(buttonLayoutProperty->GetLabelValue(), CREATE_VALUE);
    EXPECT_EQ(buttonLayoutProperty->GetFontStyle(), BUTTON_ITALIC_FONT_STYLE_VALUE);
    EXPECT_EQ(buttonLayoutProperty->GetFontFamily(), FONT_FAMILY_VALUE);
}

/**
 * @tc.name: ButtonPatternTest005
 * @tc.desc: test button created.
 * @tc.type: FUNC
 */
HWTEST_F(ButtonTestNg, ButtonPatternTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create button and get frameNode.
     */
    TestProperty testProperty;
    testProperty.borderRadius = std::make_optional(BORDER_RADIUS);
    testProperty.stateEffectValue = std::make_optional(STATE_EFFECT);
    auto frameNode = CreateLabelButtonParagraph(CREATE_VALUE, testProperty);
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::BUTTON_ETS_TAG);

    /**
     * @tc.steps: step2.get switch property and check whether the property value is correct.
     */
    auto pattern = AceType::DynamicCast<ButtonPattern>(frameNode->GetPattern());
    ASSERT_NE(pattern, nullptr);
    auto layoutProperty = pattern->GetLayoutProperty<ButtonLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    auto buttonEventHub = frameNode->GetEventHub<ButtonEventHub>();
    CHECK_NULL_VOID(buttonEventHub);

    EXPECT_EQ(buttonEventHub->GetStateEffect(), STATE_EFFECT);
}

/**
 * @tc.name: ButtonPatternTest006
 * @tc.desc: test button pattern OnModifyDone.
 * @tc.type: FUNC
 */
HWTEST_F(ButtonTestNg, ButtonPatternTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create bubble and get frameNode.
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
    buttonPattern->OnModifyDone();
    auto buttonLayoutProperty = frameNode->GetLayoutProperty<ButtonLayoutProperty>();
    ASSERT_NE(buttonLayoutProperty, nullptr);
    // update layout property
    buttonLayoutProperty->UpdateType(BUTTON_TYPE_CAPSULE_VALUE);
    buttonLayoutProperty->UpdateFontSize(BUTTON_FONT_SIZE_VALUE);
    buttonLayoutProperty->UpdateFontWeight(BUTTON_BOLD_FONT_WEIGHT_VALUE);
    buttonLayoutProperty->UpdateFontColor(FONT_COLOR);
    buttonLayoutProperty->UpdateFontFamily(FONT_FAMILY_VALUE);
    buttonLayoutProperty->UpdateFontStyle(BUTTON_ITALIC_FONT_STYLE_VALUE);

    /**
     * @tc.steps: step3. buttonPattern OnModifyDone.
     * @tc.expected: step3. check whether the properties is correct.
     */

    // set touchEventActuator_
    auto touchCallback = [](TouchEventInfo& info) {};
    auto touchEvent = AceType::MakeRefPtr<TouchEventImpl>(std::move(touchCallback));
    buttonPattern->touchListener_ = touchEvent;
    buttonPattern->OnModifyDone();
    auto text = AceType::DynamicCast<FrameNode>(frameNode->GetFirstChild());
    ASSERT_NE(text, nullptr);
    auto textLayoutProp = text->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProp, nullptr);

    EXPECT_EQ(textLayoutProp->GetContent(), CREATE_VALUE);
    EXPECT_EQ(textLayoutProp->GetFontSize(), BUTTON_FONT_SIZE_VALUE);
    EXPECT_EQ(textLayoutProp->GetFontWeight(), BUTTON_BOLD_FONT_WEIGHT_VALUE);
    EXPECT_EQ(textLayoutProp->GetTextColor(), FONT_COLOR);
    EXPECT_EQ(textLayoutProp->GetFontFamily(), FONT_FAMILY_VALUE);
}

/**
 * @tc.name: ButtonPatternTest007
 * @tc.desc: test button pattern OnModifyDone.
 * @tc.type: FUNC
 */
HWTEST_F(ButtonTestNg, ButtonPatternTest007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create bubble and get frameNode.
     */
    TestProperty testProperty;
    auto frameNode = CreateLabelButtonParagraph(CREATE_VALUE, testProperty);
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: test buttonPattern OnTouchDown OnTouchUp function.
     * @tc.expected: step3. check whether the function is executed.
     */
    auto buttonPattern = frameNode->GetPattern<ButtonPattern>();
    ASSERT_NE(buttonPattern, nullptr);
    buttonPattern->OnTouchDown();
    buttonPattern->OnTouchUp();

    // frameNode SetStateEffect
    auto buttonEventHub = frameNode->GetEventHub<ButtonEventHub>();
    CHECK_NULL_VOID(buttonEventHub);
    buttonEventHub->SetStateEffect(STATE_EFFECT);
    buttonPattern->isSetClickedColor_ = true;
    buttonPattern->clickedColor_ = FONT_COLOR;
    buttonPattern->OnTouchDown();
    buttonPattern->OnTouchUp();
}

/**
 * @tc.name: ButtonPatternTest008
 * @tc.desc: test button layout using buttonType CIRCLE.
 * @tc.type: FUNC
 */
HWTEST_F(ButtonTestNg, ButtonPatternTest008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create bubble and get frameNode.
     */
    TestProperty testProperty;
    testProperty.typeValue = std::make_optional(ButtonType::CIRCLE);
    testProperty.stateEffectValue = std::make_optional(STATE_EFFECT);
    auto frameNode = CreateLabelButtonParagraph(CREATE_VALUE, testProperty);
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. get layout property, layoutAlgorithm and create layoutWrapper.
     * @tc.expected: step2. related function is called.
     */
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    auto layoutWrapper = frameNode->CreateLayoutWrapper();
    auto buttonPattern = frameNode->GetPattern<ButtonPattern>();
    ASSERT_NE(buttonPattern, nullptr);
    auto buttonLayoutProperty = buttonPattern->GetLayoutProperty<ButtonLayoutProperty>();
    ASSERT_NE(buttonLayoutProperty, nullptr);
    auto buttonLayoutAlgorithm = buttonPattern->CreateLayoutAlgorithm();
    ASSERT_NE(buttonLayoutAlgorithm, nullptr);
    layoutWrapper->SetLayoutAlgorithm(AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(buttonLayoutAlgorithm));

    /**
     * @tc.steps: step3. update layoutWrapper.
     */
    layoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(BUTTON_WIDTH), CalcLength(BUTTON_HEIGHT)));
    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.maxSize = CONTAINER_SIZE;
    parentLayoutConstraint.percentReference = CONTAINER_SIZE;

    PaddingProperty noPadding = CreatePadding(ZERO, ZERO, ZERO, ZERO);
    layoutWrapper->GetLayoutProperty()->UpdatePadding(noPadding);
    layoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(parentLayoutConstraint);
    layoutWrapper->GetLayoutProperty()->UpdateContentConstraint();

    /**
     * @tc.steps: step4. use layoutAlgorithm to measure and layout.
     * @tc.expected: step4. check whether the value of geometry's frameSize and frameOffset is correct.
     */
    buttonLayoutAlgorithm->Measure(AccessibilityManager::RawPtr(layoutWrapper));
    buttonLayoutAlgorithm->Layout(AccessibilityManager::RawPtr(layoutWrapper));
    auto minSize = std::min(BUTTON_WIDTH, BUTTON_HEIGHT);
    EXPECT_EQ(layoutWrapper->GetGeometryNode()->GetFrameSize(), SizeF(minSize, minSize));
    EXPECT_EQ(layoutWrapper->GetGeometryNode()->GetFrameOffset(), OffsetF());

    parentLayoutConstraint.selfIdealSize.Reset();
    layoutWrapper->GetLayoutProperty()->calcLayoutConstraint_->Reset();
    layoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(parentLayoutConstraint);
    layoutWrapper->GetLayoutProperty()->UpdateContentConstraint();
    auto layoutProperty = AccessibilityManager::DynamicCast<ButtonLayoutProperty>(layoutWrapper->GetLayoutProperty());
    layoutProperty->UpdateBorderRadius({ BORDER_RADIUS, BORDER_RADIUS, BORDER_RADIUS, BORDER_RADIUS });
    buttonLayoutAlgorithm->Measure(AccessibilityManager::RawPtr(layoutWrapper));
    EXPECT_EQ(layoutWrapper->GetGeometryNode()->GetFrameSize(),
        SizeF(BORDER_RADIUS.ConvertToPx() * 2, BORDER_RADIUS.ConvertToPx() * 2));
}

/**
 * @tc.name: ButtonPatternTest009
 * @tc.desc: test button layout using buttonType CAPSULE.
 * @tc.type: FUNC
 */
HWTEST_F(ButtonTestNg, ButtonPatternTest009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create bubble and get frameNode.
     */
    TestProperty testProperty;
    testProperty.typeValue = std::make_optional(ButtonType::CAPSULE);
    testProperty.stateEffectValue = std::make_optional(STATE_EFFECT);
    auto frameNode = CreateLabelButtonParagraph(CREATE_VALUE, testProperty);
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. get layout property, layoutAlgorithm and create layoutWrapper.
     * @tc.expected: step2. related function is called.
     */
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    auto layoutWrapper = frameNode->CreateLayoutWrapper();
    auto buttonPattern = frameNode->GetPattern<ButtonPattern>();
    ASSERT_NE(buttonPattern, nullptr);
    auto buttonLayoutProperty = buttonPattern->GetLayoutProperty<ButtonLayoutProperty>();
    ASSERT_NE(buttonLayoutProperty, nullptr);
    auto buttonLayoutAlgorithm = buttonPattern->CreateLayoutAlgorithm();
    ASSERT_NE(buttonLayoutAlgorithm, nullptr);
    layoutWrapper->SetLayoutAlgorithm(AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(buttonLayoutAlgorithm));

    /**
     * @tc.steps: step3. update layoutWrapper.
     */
    // set button width and height by user
    layoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(BUTTON_WIDTH), CalcLength(BUTTON_HEIGHT)));
    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.maxSize = CONTAINER_SIZE;
    parentLayoutConstraint.percentReference = CONTAINER_SIZE;

    PaddingProperty noPadding = CreatePadding(ZERO, ZERO, ZERO, ZERO);
    layoutWrapper->GetLayoutProperty()->UpdatePadding(noPadding);
    layoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(parentLayoutConstraint);
    layoutWrapper->GetLayoutProperty()->UpdateContentConstraint();

    /**
     * @tc.steps: step3. use layoutAlgorithm to measure and layout.
     * @tc.expected: step3. check whether the value of geometry's frameSize and frameOffset is correct.
     */
    buttonLayoutAlgorithm->Measure(AccessibilityManager::RawPtr(layoutWrapper));
    buttonLayoutAlgorithm->Layout(AccessibilityManager::RawPtr(layoutWrapper));
    EXPECT_EQ(layoutWrapper->GetGeometryNode()->GetFrameSize(), SizeF(BUTTON_WIDTH, BUTTON_HEIGHT));
    EXPECT_EQ(layoutWrapper->GetGeometryNode()->GetFrameOffset(), OffsetF());
}

/**
 * @tc.name: ButtonPatternTest0010
 * @tc.desc: test button layout using buttonType others and set border by user.
 * @tc.type: FUNC
 */
HWTEST_F(ButtonTestNg, ButtonPatternTest0010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create bubble and get frameNode.
     */
    TestProperty testProperty;
    testProperty.typeValue = std::make_optional(ButtonType::NORMAL);
    testProperty.stateEffectValue = std::make_optional(STATE_EFFECT);
    testProperty.borderRadius = std::make_optional(BORDER_RADIUS);
    auto frameNode = CreateLabelButtonParagraph(CREATE_VALUE, testProperty);
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. get layout property, layoutAlgorithm and create layoutWrapper.
     * @tc.expected: step2. related function is called.
     */
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    auto layoutWrapper = frameNode->CreateLayoutWrapper();
    auto buttonPattern = frameNode->GetPattern<ButtonPattern>();
    ASSERT_NE(buttonPattern, nullptr);
    auto buttonLayoutAlgorithm = buttonPattern->CreateLayoutAlgorithm();
    ASSERT_NE(buttonLayoutAlgorithm, nullptr);
    layoutWrapper->SetLayoutAlgorithm(AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(buttonLayoutAlgorithm));

    /**
     * @tc.steps: step3. update layoutWrapper.
     */
    // set button width and height by user
    layoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(CalcSize(CalcLength(BUTTON_WIDTH), CalcLength()));
    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.maxSize = CONTAINER_SIZE;
    parentLayoutConstraint.percentReference = CONTAINER_SIZE;

    PaddingProperty noPadding = CreatePadding(ZERO, ZERO, ZERO, ZERO);
    layoutWrapper->GetLayoutProperty()->UpdatePadding(noPadding);
    layoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(parentLayoutConstraint);
    layoutWrapper->GetLayoutProperty()->UpdateContentConstraint();

    /**
     * @tc.steps: step3. use layoutAlgorithm to measure and layout.
     * @tc.expected: check whether the value of geometry's frameSize and frameOffset is correct.
     */
    buttonLayoutAlgorithm->Measure(AccessibilityManager::RawPtr(layoutWrapper));
    buttonLayoutAlgorithm->Layout(AccessibilityManager::RawPtr(layoutWrapper));
    EXPECT_EQ(layoutWrapper->GetGeometryNode()->GetFrameSize().Width(), BUTTON_WIDTH);
    EXPECT_EQ(layoutWrapper->GetGeometryNode()->GetFrameOffset(), OffsetF());

    auto childWrapper = AceType::DynamicCast<LayoutWrapperNode>(layoutWrapper->GetOrCreateChildByIndex(0));
    ASSERT_NE(childWrapper, nullptr);
    auto iter = layoutWrapper->childrenMap_.find(0);
    if (iter == layoutWrapper->childrenMap_.end()) {
        layoutWrapper->AppendChild(childWrapper);
    }
    auto childButtonLayoutProperty =
        AccessibilityManager::DynamicCast<LayoutProperty>(childWrapper->GetLayoutProperty());
    ASSERT_NE(childButtonLayoutProperty, nullptr);
    CalcSize calcSize { CalcLength(Dimension(300.0)), CalcLength(Dimension(300.0)) };
    childButtonLayoutProperty->UpdateUserDefinedIdealSize(calcSize);

    buttonLayoutAlgorithm->Measure(AccessibilityManager::RawPtr(layoutWrapper));
    buttonLayoutAlgorithm->Layout(AccessibilityManager::RawPtr(layoutWrapper));
    EXPECT_EQ(childWrapper->GetGeometryNode()->GetContentSize().Width(), 0);
    /**
     * @tc.steps: step4. use layoutAlgorithm to measure and layout.
     * @tc.expected: check whether the value of geometry's contentSize's height is 1.
     */
    auto buttonLayoutProperty =
        AccessibilityManager::DynamicCast<ButtonLayoutProperty>(layoutWrapper->GetLayoutProperty());
    ASSERT_NE(buttonLayoutProperty, nullptr);
    buttonLayoutProperty->UpdateFontSize(Dimension(24.0));
    buttonLayoutAlgorithm->Measure(AccessibilityManager::RawPtr(layoutWrapper));
    buttonLayoutAlgorithm->Layout(AccessibilityManager::RawPtr(layoutWrapper));
    EXPECT_EQ(childWrapper->GetGeometryNode()->GetContentSize().Height(), 0);
}

/**
 * @tc.name: ButtonPatternTest011
 * @tc.desc: test button pattern OnModifyDone.
 * @tc.type: FUNC
 */
HWTEST_F(ButtonTestNg, ButtonPatternTest011, TestSize.Level1)
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
    auto touchCallback = [](TouchEventInfo& info) {};
    auto touchEvent = AceType::MakeRefPtr<TouchEventImpl>(std::move(touchCallback));
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
 * @tc.name: ButtonPatternTest012
 * @tc.desc: test textOverflow enum value.
 * @tc.type: FUNC
 */
HWTEST_F(ButtonTestNg, ButtonPatternTest012, TestSize.Level1)
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
    auto touchCallback = [](TouchEventInfo& info) {};
    auto touchEvent = AceType::MakeRefPtr<TouchEventImpl>(std::move(touchCallback));
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
 * @tc.name: ButtonPatternTest013
 * @tc.desc: test fontStyle enum value.
 * @tc.type: FUNC
 */
HWTEST_F(ButtonTestNg, ButtonPatternTest013, TestSize.Level1)
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
    auto touchCallback = [](TouchEventInfo& info) {};
    auto touchEvent = AceType::MakeRefPtr<TouchEventImpl>(std::move(touchCallback));
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
 * @tc.name: ButtonPatternTest014
 * @tc.desc: test TextHeightAdaptivePolicy and fontWeight enum value.
 * @tc.type: FUNC
 */
HWTEST_F(ButtonTestNg, ButtonPatternTest014, TestSize.Level1)
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
    auto touchCallback = [](TouchEventInfo& info) {};
    auto touchEvent = AceType::MakeRefPtr<TouchEventImpl>(std::move(touchCallback));
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
 * @tc.name: ButtonPatternTest015
 * @tc.desc: Test HandleLabelCircleButtonConstraint and HandleLabelCircleButtonFrameSize.
 * @tc.type: FUNC
 */
HWTEST_F(ButtonTestNg, ButtonPatternTest015, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create button and get frameNode.
     */
    TestProperty testProperty;
    testProperty.typeValue = std::make_optional(ButtonType::CIRCLE);
    testProperty.stateEffectValue = std::make_optional(STATE_EFFECT);
    auto frameNode = CreateLabelButtonParagraph(CREATE_VALUE, testProperty);
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. get layout property, layoutAlgorithm and create layoutWrapper.
     * @tc.expected: step2. related function is called.
     */
    auto layoutWrapper = frameNode->CreateLayoutWrapper();
    auto buttonPattern = frameNode->GetPattern<ButtonPattern>();
    ASSERT_NE(buttonPattern, nullptr);
    auto buttonLayoutAlgorithm =
        AccessibilityManager::DynamicCast<ButtonLayoutAlgorithm>(buttonPattern->CreateLayoutAlgorithm());
    ASSERT_NE(buttonLayoutAlgorithm, nullptr);
    layoutWrapper->SetLayoutAlgorithm(AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(buttonLayoutAlgorithm));

    /**
     * @tc.steps: step3. update layoutWrapper.
     */
    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.maxSize = CONTAINER_SIZE;
    parentLayoutConstraint.percentReference = CONTAINER_SIZE;

    PaddingProperty noPadding = CreatePadding(ZERO, ZERO, ZERO, ZERO);
    layoutWrapper->GetLayoutProperty()->UpdatePadding(noPadding);
    layoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(parentLayoutConstraint);
    layoutWrapper->GetLayoutProperty()->UpdateContentConstraint();

    /**
     * @tc.steps: step4. use layoutAlgorithm to call HandleLabelCircleButtonConstraint and
     * HandleLabelCircleButtonFrameSize.
     * @tc.expected: step4. check whether the value of constraint size and frame szie are correct.
     */
    SizeF frameSize;
    auto constraintSize =
        buttonLayoutAlgorithm->HandleLabelCircleButtonConstraint(AccessibilityManager::RawPtr(layoutWrapper));
    buttonLayoutAlgorithm->HandleLabelCircleButtonFrameSize(
        layoutWrapper->GetLayoutProperty()->CreateChildConstraint(), frameSize, DEFAULT_HEIGTH.ConvertToPx());
    EXPECT_EQ(constraintSize, SizeF(DEFAULT_HEIGTH.ConvertToPx(), DEFAULT_HEIGTH.ConvertToPx()));
    EXPECT_EQ(frameSize, SizeF(DEFAULT_HEIGTH.ConvertToPx(), DEFAULT_HEIGTH.ConvertToPx()));
    auto buttonLayoutProperty =
        AccessibilityManager::DynamicCast<ButtonLayoutProperty>(layoutWrapper->GetLayoutProperty());
    AccessibilityManager::DynamicCast<ButtonLayoutProperty>(layoutWrapper->GetLayoutProperty())
        ->UpdateBorderRadius({ BORDER_RADIUS, BORDER_RADIUS, BORDER_RADIUS, BORDER_RADIUS });
    constraintSize =
        buttonLayoutAlgorithm->HandleLabelCircleButtonConstraint(AccessibilityManager::RawPtr(layoutWrapper));
    EXPECT_EQ(constraintSize, SizeF(BORDER_RADIUS.ConvertToPx() * 2, BORDER_RADIUS.ConvertToPx() * 2));
    parentLayoutConstraint.selfIdealSize.SetHeight(BUTTON_HEIGHT);
    layoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(parentLayoutConstraint);
    layoutWrapper->GetLayoutProperty()->UpdateContentConstraint();
    constraintSize =
        buttonLayoutAlgorithm->HandleLabelCircleButtonConstraint(AccessibilityManager::RawPtr(layoutWrapper));
    frameSize.SetHeight(BUTTON_HEIGHT);
    buttonLayoutAlgorithm->HandleLabelCircleButtonFrameSize(
        layoutWrapper->GetLayoutProperty()->CreateChildConstraint(), frameSize, BUTTON_HEIGHT);
    EXPECT_EQ(constraintSize, SizeF(BUTTON_HEIGHT, BUTTON_HEIGHT));
    EXPECT_EQ(frameSize, SizeF(BUTTON_HEIGHT, BUTTON_HEIGHT));
    parentLayoutConstraint.selfIdealSize.Reset();
    parentLayoutConstraint.selfIdealSize.SetWidth(BUTTON_WIDTH);
    layoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(parentLayoutConstraint);
    layoutWrapper->GetLayoutProperty()->UpdateContentConstraint();
    constraintSize =
        buttonLayoutAlgorithm->HandleLabelCircleButtonConstraint(AccessibilityManager::RawPtr(layoutWrapper));
    frameSize.SetWidth(BUTTON_WIDTH);
    buttonLayoutAlgorithm->HandleLabelCircleButtonFrameSize(
        layoutWrapper->GetLayoutProperty()->CreateChildConstraint(), frameSize, BUTTON_WIDTH);
    EXPECT_EQ(constraintSize, SizeF(BUTTON_WIDTH, BUTTON_WIDTH));
    EXPECT_EQ(frameSize, SizeF(BUTTON_WIDTH, BUTTON_WIDTH));
}

/**
 * @tc.name: ButtonPatternTest016
 * @tc.desc: Test button view branch
 * @tc.type: FUNC
 */
HWTEST_F(ButtonTestNg, ButtonPatternTest016, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create button and set button view's value.
     */
    ButtonModelNG buttonModelNG;
    std::list<RefPtr<Component>> buttonChildren;
    buttonModelNG.CreateWithLabel(createWithPara, buttonChildren);
    ButtonParameters buttonParameters;
    buttonParameters.textOverflow = std::make_optional(TextOverflow::NONE);
    buttonParameters.maxLines = std::make_optional(MAX_LINE_VALUE);
    buttonParameters.minFontSize = std::make_optional(BUTTON_FONT_SIZE_VALUE);
    buttonParameters.maxFontSize = std::make_optional(BUTTON_FONT_SIZE_VALUE);
    buttonParameters.fontSize = std::make_optional(BUTTON_FONT_SIZE_VALUE);
    buttonParameters.heightAdaptivePolicy = std::make_optional(TextHeightAdaptivePolicy::LAYOUT_CONSTRAINT_FIRST);
    buttonParameters.fontWeight = std::make_optional(FontWeight::MEDIUM);
    buttonParameters.fontFamily = std::make_optional(FONT_FAMILY_VALUE);
    buttonParameters.fontStyle = std::make_optional(Ace::FontStyle::NORMAL);

    /**
     * @tc.steps: step3. ButtonModelNG setLabelStyle.
     * @tc.expected: step3. Button properties are set successfully.
     */
    buttonModelNG.SetLabelStyle(buttonParameters);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<ButtonLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    EXPECT_EQ(layoutProperty->GetTextOverflowValue(), TextOverflow::NONE);
    EXPECT_EQ(layoutProperty->GetMaxLinesValue(), MAX_LINE_VALUE);
    EXPECT_EQ(layoutProperty->GetMinFontSizeValue(), BUTTON_FONT_SIZE_VALUE);
    EXPECT_EQ(layoutProperty->GetMaxFontSizeValue(), BUTTON_FONT_SIZE_VALUE);
    EXPECT_EQ(layoutProperty->GetFontSizeValue(), BUTTON_FONT_SIZE_VALUE);
    EXPECT_EQ(layoutProperty->GetHeightAdaptivePolicyValue(), TextHeightAdaptivePolicy::LAYOUT_CONSTRAINT_FIRST);
    EXPECT_EQ(layoutProperty->GetFontWeightValue(), FontWeight::MEDIUM);
    EXPECT_EQ(layoutProperty->GetFontFamilyValue(), FONT_FAMILY_VALUE);
    EXPECT_EQ(layoutProperty->GetFontStyleValue(), Ace::FontStyle::NORMAL);
}

/**
 * @tc.name: ButtonPatternTest017
 * @tc.desc: Test touch event callback
 * @tc.type: FUNC
 */
HWTEST_F(ButtonTestNg, ButtonPatternTest017, TestSize.Level1)
{
    TestProperty testProperty;
    testProperty.typeValue = std::make_optional(ButtonType::CIRCLE);
    testProperty.stateEffectValue = std::make_optional(STATE_EFFECT);
    auto frameNode = CreateLabelButtonParagraph(CREATE_VALUE, testProperty);
    ASSERT_NE(frameNode, nullptr);

    auto buttonPattern = frameNode->GetPattern<ButtonPattern>();
    ASSERT_NE(buttonPattern, nullptr);
    buttonPattern->InitTouchEvent();
    auto gesture = frameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(gesture, nullptr);
    auto touchListener = gesture->touchEventActuator_->touchEvents_.back();
    ASSERT_NE(touchListener, nullptr);
    auto touchCallback = touchListener->callback_;

    buttonPattern->isSetClickedColor_ = true;
    buttonPattern->clickedColor_ = Color::RED;
    auto renderContext = frameNode->GetRenderContext();
    renderContext->UpdateBackgroundColor(Color::BLUE);

    TouchEventInfo info("onTouch");
    TouchLocationInfo touchLocationInfo(1);
    touchLocationInfo.SetTouchType(TouchType::DOWN);
    info.AddTouchLocationInfo(std::move(touchLocationInfo));
    touchCallback(info);
    EXPECT_EQ(buttonPattern->backgroundColor_, Color::BLUE);
    EXPECT_EQ(renderContext->GetBackgroundColorValue(), Color::RED);

    touchLocationInfo.SetTouchType(TouchType::UP);
    info.touches_.clear();
    info.AddTouchLocationInfo(std::move(touchLocationInfo));
    touchCallback(info);
    EXPECT_EQ(renderContext->GetBackgroundColorValue(), Color::BLUE);
}

/**
 * @tc.name: ButtonPatternTest018
 * @tc.desc: Test HandleEnable disable
 * @tc.type: FUNC
 */
HWTEST_F(ButtonTestNg, ButtonPatternTest018, TestSize.Level1)
{
    TestProperty testProperty;
    testProperty.typeValue = std::make_optional(ButtonType::CIRCLE);
    testProperty.stateEffectValue = std::make_optional(STATE_EFFECT);
    auto frameNode = CreateLabelButtonParagraph(CREATE_VALUE, testProperty);
    ASSERT_NE(frameNode, nullptr);

    auto buttonPattern = frameNode->GetPattern<ButtonPattern>();
    ASSERT_NE(buttonPattern, nullptr);
    auto eventHub = frameNode->GetEventHub<EventHub>();
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
    buttonPattern->HandleEnabled();
    EXPECT_EQ(renderContext->GetOpacityValue(1.0), alpha * originalOpacity);
}

/**
 * @tc.name: ButtonPatternTest019
 * @tc.desc: Test AnimateTouchAndHover
 * @tc.type: FUNC
 */
HWTEST_F(ButtonTestNg, ButtonPatternTest019, TestSize.Level1)
{
    TestProperty testProperty;
    auto frameNode = CreateLabelButtonParagraph(CREATE_VALUE, testProperty);
    ASSERT_NE(frameNode, nullptr);
    auto buttonPattern = frameNode->GetPattern<ButtonPattern>();
    ASSERT_NE(buttonPattern, nullptr);
    auto context = frameNode->GetRenderContext();
    ASSERT_NE(context, nullptr);
    buttonPattern->AnimateTouchAndHover(context, START_OPACITY, END_OPACITY, DURATION, Curves::FRICTION);
    buttonPattern->AnimateTouchAndHover(context, END_OPACITY, START_OPACITY, DURATION, Curves::FRICTION);
    EXPECT_EQ(buttonPattern->isHover_, false);
}

/**
 * @tc.name: ButtonPatternTest020
 * @tc.desc: Test GetFirstValidRadius
 * @tc.type: FUNC
 */
HWTEST_F(ButtonTestNg, ButtonPatternTest020, TestSize.Level1)
{
    TestProperty testProperty;
    auto frameNode = CreateLabelButtonParagraph(CREATE_VALUE, testProperty);
    ASSERT_NE(frameNode, nullptr);
    auto buttonPattern = frameNode->GetPattern<ButtonPattern>();
    ASSERT_NE(buttonPattern, nullptr);
    auto buttonLayoutAlgorithm = AceType::DynamicCast<ButtonLayoutAlgorithm>(buttonPattern->CreateLayoutAlgorithm());
    ASSERT_NE(buttonLayoutAlgorithm, nullptr);
    BorderRadiusProperty radius;
    auto firstValidRadius = buttonLayoutAlgorithm->GetFirstValidRadius(radius);
    EXPECT_EQ(firstValidRadius, 0.0_vp);
    radius.radiusTopLeft = BORDER_RADIUS;
    firstValidRadius = buttonLayoutAlgorithm->GetFirstValidRadius(radius);
    EXPECT_EQ(firstValidRadius, BORDER_RADIUS);

    radius.radiusTopLeft.reset();
    radius.radiusTopRight = BORDER_RADIUS;
    firstValidRadius = buttonLayoutAlgorithm->GetFirstValidRadius(radius);
    EXPECT_EQ(firstValidRadius, BORDER_RADIUS);

    radius.radiusTopRight.reset();
    radius.radiusBottomLeft = BORDER_RADIUS;
    firstValidRadius = buttonLayoutAlgorithm->GetFirstValidRadius(radius);
    EXPECT_EQ(firstValidRadius, BORDER_RADIUS);

    radius.radiusBottomLeft.reset();
    radius.radiusBottomRight = BORDER_RADIUS;
    firstValidRadius = buttonLayoutAlgorithm->GetFirstValidRadius(radius);
    EXPECT_EQ(firstValidRadius, BORDER_RADIUS);
}

/**
 * @tc.name: ButtonPatternTest021
 * @tc.desc: Test HandleHoverEvent
 * @tc.type: FUNC
 */
HWTEST_F(ButtonTestNg, ButtonPatternTest021, TestSize.Level1)
{
    TestProperty testProperty;
    auto frameNode = CreateLabelButtonParagraph(CREATE_VALUE, testProperty);
    ASSERT_NE(frameNode, nullptr);
    auto buttonPattern = frameNode->GetPattern<ButtonPattern>();
    ASSERT_NE(buttonPattern, nullptr);
    auto eventHub = frameNode->GetEventHub<EventHub>();
    eventHub->SetEnabled(false);
    buttonPattern->HandleHoverEvent(true);
    EXPECT_EQ(buttonPattern->isHover_, true);
    eventHub->SetEnabled(true);
    buttonPattern->HandleHoverEvent(false);
    EXPECT_EQ(buttonPattern->isHover_, false);
}

/**
 * @tc.name: ButtonPatternTest022
 * @tc.desc: Test default button style
 * @tc.type: FUNC
 */
HWTEST_F(ButtonTestNg, ButtonPatternTest022, TestSize.Level1)
{
    auto pipeline = PipelineBase::GetCurrentContext();
    pipeline->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_NINE));
    TestProperty testProperty;
    auto frameNode = CreateLabelButtonParagraph(CREATE_VALUE, testProperty);
    ASSERT_NE(frameNode, nullptr);
    auto renderContext = frameNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    EXPECT_EQ(renderContext->GetBackgroundColor(), Color::RED);
}

/**
 * @tc.name: ButtonPatternTest023
 * @tc.desc: Test ButtonStyle and ControlSize
 * @tc.type: FUNC
 */
HWTEST_F(ButtonTestNg, ButtonPatternTest023, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create button and get frameNode
     */
    TestProperty testProperty;
    testProperty.buttonStyle = ButtonStyleMode::EMPHASIZE;
    testProperty.controlSize = ControlSize::SMALL;
    testProperty.buttonRole = ButtonRole::NORMAL;
    auto frameNode = CreateLabelButtonParagraph(CREATE_VALUE, testProperty);
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. test button style and control size
     * @tc.expected: step2. button style and control size is set correct
     */
    auto buttonPattern = frameNode->GetPattern<ButtonPattern>();
    ASSERT_NE(buttonPattern, nullptr);
    auto buttonLayoutProperty = buttonPattern->GetLayoutProperty<ButtonLayoutProperty>();
    ASSERT_NE(buttonLayoutProperty, nullptr);
    EXPECT_EQ(buttonLayoutProperty->GetButtonStyleValue(), ButtonStyleMode::EMPHASIZE);
    EXPECT_EQ(buttonLayoutProperty->GetControlSizeValue(), ControlSize::SMALL);
    EXPECT_EQ(buttonLayoutProperty->GetButtonRoleValue(), ButtonRole::NORMAL);
    auto renderContext = frameNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    EXPECT_EQ(renderContext->GetBackgroundColor(), Color::RED);
    EXPECT_EQ(renderContext->GetForegroundColor(), Color::BLACK);

    /**
     * @tc.steps: step3. test layout algorithm
     * @tc.expected: step3. check whether the height of geometry is correct
     */
    auto layoutWrapper = frameNode->CreateLayoutWrapper();
    auto buttonLayoutAlgorithm = buttonPattern->CreateLayoutAlgorithm();
    ASSERT_NE(buttonLayoutAlgorithm, nullptr);
    layoutWrapper->SetLayoutAlgorithm(AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(buttonLayoutAlgorithm));
    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.maxSize = CONTAINER_SIZE;
    parentLayoutConstraint.percentReference = CONTAINER_SIZE;
    layoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(parentLayoutConstraint);
    layoutWrapper->GetLayoutProperty()->UpdateContentConstraint();
    buttonLayoutAlgorithm->Measure(AccessibilityManager::RawPtr(layoutWrapper));
    buttonLayoutAlgorithm->Layout(AccessibilityManager::RawPtr(layoutWrapper));
    EXPECT_EQ(layoutWrapper->GetGeometryNode()->GetFrameSize().Height(), DEFAULT_HEIGTH.ConvertToPx());
}

/**
 * @tc.name: ButtonPatternTest024
 * @tc.desc: Test ButtonStyle 、 ControlSize and ButtonRle
 * @tc.type: FUNC
 */
HWTEST_F(ButtonTestNg, ButtonPatternTest024, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create button and get frameNode
     */
    TestProperty testProperty;
    testProperty.buttonStyle = ButtonStyleMode::EMPHASIZE;
    testProperty.controlSize = ControlSize::NORMAL;
    testProperty.buttonRole = ButtonRole::ERROR;
    auto frameNode = CreateLabelButtonParagraph(CREATE_VALUE, testProperty);
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. test button style control size and button role
     * @tc.expected: step2. button style control size and button role is set correct
     */
    auto buttonPattern = frameNode->GetPattern<ButtonPattern>();
    ASSERT_NE(buttonPattern, nullptr);
    auto buttonLayoutProperty = buttonPattern->GetLayoutProperty<ButtonLayoutProperty>();
    ASSERT_NE(buttonLayoutProperty, nullptr);
    EXPECT_EQ(buttonLayoutProperty->GetButtonStyleValue(), ButtonStyleMode::EMPHASIZE);
    EXPECT_EQ(buttonLayoutProperty->GetControlSizeValue(), ControlSize::NORMAL);
    EXPECT_EQ(buttonLayoutProperty->GetButtonRoleValue(), ButtonRole::ERROR);
    auto renderContext = frameNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    EXPECT_EQ(renderContext->GetBackgroundColor(), Color::WHITE);
    EXPECT_EQ(renderContext->GetForegroundColor(), Color::BLACK);
}

/**
 * @tc.name: ButtonPatternTest025
 * @tc.desc: Test button setLabelStyle
 * @tc.type: FUNC
 */
HWTEST_F(ButtonTestNg, ButtonPatternTest025, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create button and set button view's value.
     */
    ButtonModelNG buttonModelNG;
    std::list<RefPtr<Component>> buttonChildren;
    buttonModelNG.CreateWithLabel(createWithPara, buttonChildren);
    auto buttonFrameNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ViewStackProcessor::GetInstance()->ClaimNodeId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    ASSERT_NE(buttonFrameNode, nullptr);
    ButtonParameters buttonParameters;
    buttonParameters.textOverflow = std::make_optional(TextOverflow::NONE);
    buttonParameters.maxLines = std::make_optional(MAX_LINE_VALUE);
    buttonParameters.minFontSize = std::make_optional(BUTTON_FONT_SIZE_VALUE);
    buttonParameters.maxFontSize = std::make_optional(BUTTON_FONT_SIZE_VALUE);
    buttonParameters.fontSize = std::make_optional(BUTTON_FONT_SIZE_VALUE);
    buttonParameters.heightAdaptivePolicy = std::make_optional(TextHeightAdaptivePolicy::LAYOUT_CONSTRAINT_FIRST);
    buttonParameters.fontWeight = std::make_optional(FontWeight::MEDIUM);
    buttonParameters.fontFamily = std::make_optional(FONT_FAMILY_VALUE);
    buttonParameters.fontStyle = std::make_optional(Ace::FontStyle::NORMAL);
    ButtonModelNG::SetLabelStyle(AccessibilityManager::RawPtr(buttonFrameNode), buttonParameters);
    /**
     * @tc.steps: step3. ButtonModelNG setLabelStyle.
     * @tc.expected: step3. Button properties are set successfully.
     */
    auto layoutProperty = buttonFrameNode->GetLayoutProperty<ButtonLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    EXPECT_EQ(layoutProperty->GetTextOverflowValue(), TextOverflow::NONE);
    EXPECT_EQ(layoutProperty->GetMaxLinesValue(), MAX_LINE_VALUE);
    EXPECT_EQ(layoutProperty->GetMinFontSizeValue(), BUTTON_FONT_SIZE_VALUE);
    EXPECT_EQ(layoutProperty->GetMaxFontSizeValue(), BUTTON_FONT_SIZE_VALUE);
    EXPECT_EQ(layoutProperty->GetFontSizeValue(), BUTTON_FONT_SIZE_VALUE);
    EXPECT_EQ(layoutProperty->GetHeightAdaptivePolicyValue(), TextHeightAdaptivePolicy::LAYOUT_CONSTRAINT_FIRST);
    EXPECT_EQ(layoutProperty->GetFontWeightValue(), FontWeight::MEDIUM);
    EXPECT_EQ(layoutProperty->GetFontFamilyValue(), FONT_FAMILY_VALUE);
    EXPECT_EQ(layoutProperty->GetFontStyleValue(), Ace::FontStyle::NORMAL);
}

/**
 * @tc.name: ButtonPatternTest026
 * @tc.desc: Test SetButtonPress
 * @tc.type: FUNC
 */
HWTEST_F(ButtonTestNg, ButtonPatternTest026, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create button and get frameNode
     */
    TestProperty testProperty;;
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

/**
 * @tc.name: ButtonPatternTest027
 * @tc.desc: Test SetBuilderFunc
 * @tc.type: FUNC
 */
HWTEST_F(ButtonTestNg, ButtonPatternTest027, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create button and get frameNode
     */
    TestProperty testProperty;
    auto frameNode = CreateLabelButtonParagraph(CREATE_VALUE, testProperty);
    auto gesture = frameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. test SetChangeValue
     * @tc.expected: step2. x and y is set correct
     */
    auto buttonPattern = frameNode->GetPattern<ButtonPattern>();
    ASSERT_NE(buttonPattern, nullptr);
    buttonPattern->OnTouchDown();
    auto node = [](ButtonConfiguration config) -> RefPtr<FrameNode> {
            EXPECT_EQ(CREATE_VALUE, config.label_);
            EXPECT_EQ(true, config.pressed_);
            return nullptr;
        };

    /**
     * @tc.steps: step2. Set parameters to pattern builderFunc
     */
    buttonPattern->SetBuilderFunc(node);
    buttonPattern->BuildContentModifierNode();
}

/**
 * @tc.name: ButtonPatternTest028
 * @tc.desc: Test all the properties of rounded rectangle button.
 * @tc.type: FUNC
 */
HWTEST_F(ButtonTestNg, ButtonPatternTest028, TestSize.Level1)
{
    TestProperty testProperty;
    testProperty.typeValue = std::make_optional(BUTTON_TYPE_ROUNDED_RECTANGLE_VALUE);
    RefPtr<FrameNode> frameNode = CreateLabelButtonParagraphByRoundedRect(CREATE_VALUE, testProperty);
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<ButtonLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    EXPECT_EQ(layoutProperty->GetTypeValue(), BUTTON_TYPE_ROUNDED_RECTANGLE_VALUE);
}

/**
 * @tc.name: ButtonPatternTest029
 * @tc.desc: Test all the properties of default button.
 * @tc.type: FUNC
 */
HWTEST_F(ButtonTestNg, ButtonPatternTest029, TestSize.Level1)
{
    TestProperty testProperty;
    RefPtr<FrameNode> frameNode = CreateLabelButtonParagraphByRoundedRect(CREATE_VALUE, testProperty);
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<ButtonLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    EXPECT_EQ(layoutProperty->GetTypeValue(), BUTTON_TYPE_ROUNDED_RECTANGLE_VALUE);
}

/**
 * @tc.name: ButtonPatternTest030
 * @tc.desc: test button layout using buttonType ROUNDED_RECTANGLE and set border by user.
 * @tc.type: FUNC
 */
HWTEST_F(ButtonTestNg, ButtonPatternTest030, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create bubble and get frameNode.
     */
    TestProperty testProperty;
    testProperty.typeValue = std::make_optional(ButtonType::ROUNDED_RECTANGLE);
    testProperty.stateEffectValue = std::make_optional(STATE_EFFECT);
    testProperty.borderRadius = std::make_optional(BORDER_RADIUS);
    auto frameNode = CreateLabelButtonParagraphByRoundedRect(CREATE_VALUE, testProperty);
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. get layout property, layoutAlgorithm and create layoutWrapper.
     * @tc.expected: step2. related function is called.
     */
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    auto layoutWrapper = frameNode->CreateLayoutWrapper();
    auto buttonPattern = frameNode->GetPattern<ButtonPattern>();
    ASSERT_NE(buttonPattern, nullptr);
    auto buttonLayoutAlgorithm = buttonPattern->CreateLayoutAlgorithm();
    ASSERT_NE(buttonLayoutAlgorithm, nullptr);
    layoutWrapper->SetLayoutAlgorithm(AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(buttonLayoutAlgorithm));

    /**
     * @tc.steps: step3. update layoutWrapper.
     */
    // set button width and height by user
    layoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(CalcSize(CalcLength(BUTTON_WIDTH), CalcLength()));
    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.maxSize = CONTAINER_SIZE;
    parentLayoutConstraint.percentReference = CONTAINER_SIZE;

    PaddingProperty noPadding = CreatePadding(ZERO, ZERO, ZERO, ZERO);
    layoutWrapper->GetLayoutProperty()->UpdatePadding(noPadding);
    layoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(parentLayoutConstraint);
    layoutWrapper->GetLayoutProperty()->UpdateContentConstraint();

    /**
     * @tc.steps: step3. use layoutAlgorithm to measure and layout.
     * @tc.expected: check whether the value of geometry's frameSize and frameOffset is correct.
     */
    buttonLayoutAlgorithm->Measure(AccessibilityManager::RawPtr(layoutWrapper));
    buttonLayoutAlgorithm->Layout(AccessibilityManager::RawPtr(layoutWrapper));
    EXPECT_EQ(layoutWrapper->GetGeometryNode()->GetFrameSize().Width(), BUTTON_WIDTH);
    EXPECT_EQ(layoutWrapper->GetGeometryNode()->GetFrameOffset(), OffsetF());

    auto childWrapper = AceType::DynamicCast<LayoutWrapperNode>(layoutWrapper->GetOrCreateChildByIndex(0));
    ASSERT_NE(childWrapper, nullptr);
    auto iter = layoutWrapper->childrenMap_.find(0);
    if (iter == layoutWrapper->childrenMap_.end()) {
        layoutWrapper->AppendChild(childWrapper);
    }
    auto childButtonLayoutProperty =
        AccessibilityManager::DynamicCast<LayoutProperty>(childWrapper->GetLayoutProperty());
    ASSERT_NE(childButtonLayoutProperty, nullptr);
    CalcSize calcSize { CalcLength(Dimension(300.0)), CalcLength(Dimension(300.0)) };
    childButtonLayoutProperty->UpdateUserDefinedIdealSize(calcSize);

    buttonLayoutAlgorithm->Measure(AccessibilityManager::RawPtr(layoutWrapper));
    buttonLayoutAlgorithm->Layout(AccessibilityManager::RawPtr(layoutWrapper));
    EXPECT_EQ(childWrapper->GetGeometryNode()->GetContentSize().Width(), 0);
    /**
     * @tc.steps: step4. use layoutAlgorithm to measure and layout.
     * @tc.expected: check whether the value of geometry's contentSize's height is 1.
     */
    auto buttonLayoutProperty =
        AccessibilityManager::DynamicCast<ButtonLayoutProperty>(layoutWrapper->GetLayoutProperty());
    ASSERT_NE(buttonLayoutProperty, nullptr);
    buttonLayoutProperty->UpdateFontSize(Dimension(24.0));
    buttonLayoutAlgorithm->Measure(AccessibilityManager::RawPtr(layoutWrapper));
    buttonLayoutAlgorithm->Layout(AccessibilityManager::RawPtr(layoutWrapper));
    EXPECT_EQ(childWrapper->GetGeometryNode()->GetContentSize().Height(), 0);
}

/**
 * @tc.name: OnColorConfigurationUpdate001
 * @tc.desc: Test on color configuration update
 * @tc.type: FUNC
 */
HWTEST_F(ButtonTestNg, OnColorConfigurationUpdate001, TestSize.Level1)
{
    ButtonModelNG buttonModelNG;
    buttonModelNG.CreateWithLabel(CREATE_VALUE);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto buttonPattern = frameNode->GetPattern<ButtonPattern>();
    ASSERT_NE(buttonPattern, nullptr);
    buttonPattern->OnColorConfigurationUpdate();
    auto renderContext = frameNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    EXPECT_EQ(renderContext->GetBackgroundColor(), Color::RED);
    auto textNode = AceType::DynamicCast<FrameNode>(frameNode->GetFirstChild());
    ASSERT_NE(textNode, nullptr);
    auto textLayoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);
    EXPECT_EQ(textLayoutProperty->GetTextColor(), Color::BLACK);
}

/**
 * @tc.name: ButtonAccessibilityPropertyTest001
 * @tc.desc: Test button property
 * @tc.type: FUNC
 */
HWTEST_F(ButtonTestNg, ButtonAccessibilityPropertyTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create button and get frameNode.
     */
    ButtonModelNG buttonModelNG;
    std::list<RefPtr<Component>> buttonChildren;
    buttonModelNG.CreateWithLabel(createWithPara, buttonChildren);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. get button property.
     * @tc.expected: step2. check whether the properties is correct.
     */
    auto buttonAccessibilityProperty = frameNode->GetAccessibilityProperty<NG::AccessibilityProperty>();
    ASSERT_NE(buttonAccessibilityProperty, nullptr);
    EXPECT_EQ(buttonAccessibilityProperty->GetText(), CREATE_VALUE);
}

/**
 * @tc.name:SetSizePropertyTest001
 * @tc.desc: Test button setSize property
 * @tc.type: FUNC
 */
HWTEST_F(ButtonTestNg, SetSizePropertyTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create button and get frameNode.
     */
    ButtonModelNG buttonModelNG;
    std::list<RefPtr<Component>> buttonChildren;
    buttonModelNG.CreateWithLabel(createWithPara, buttonChildren);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ButtonPattern>();
    ASSERT_NE(pattern, nullptr);
    auto sizeWidth = std::optional<Dimension>(Dimension(20.00, DimensionUnit::VP));
    auto sizeHeight = std::optional<Dimension>(Dimension(20.00, DimensionUnit::VP));
    buttonModelNG.SetSize(sizeWidth, sizeHeight);
    EXPECT_TRUE(sizeWidth.has_value());
    EXPECT_TRUE(sizeHeight.has_value());
    buttonModelNG.SetSize(std::nullopt, std::nullopt);
}

/**
 * @tc.name: ButtonPatternTestModifier001
 * @tc.desc: Test ContentModifier
 * @tc.type: FUNC
 */
HWTEST_F(ButtonTestNg, ButtonPatternTestModifier001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create button frame node.
     * @tc.expected: step1. node is not null.
     */
    TestProperty testProperty;
    ButtonModelNG buttonModelNG;
    std::list<RefPtr<Component>> buttonChildren;
    CreateWithPara createWithPara;
    createWithPara.parseSuccess = true;
    createWithPara.label = BUTTON_VALUE;
    buttonModelNG.CreateWithLabel(createWithPara, buttonChildren);
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. test BuildContentModifierNode
     * @tc.expected: step2. func is ok,the result is ok.
     */
    auto buttonPattern = frameNode->GetPattern<ButtonPattern>();
    ASSERT_NE(buttonPattern, nullptr);

    /**
     * Mock the func, set the result to 'TEST_RESULT'.
     * when the func is excuted successfully, the result will be changed.
    */
    std::string result;
    auto node = [&result](ButtonConfiguration config) -> RefPtr<FrameNode> {
        result = TEST_RESULT;
        return nullptr;
    };
    buttonPattern->SetBuilderFunc(node);
    buttonPattern->BuildContentModifierNode();
    EXPECT_EQ(result, TEST_RESULT);
}

/**
 * @tc.name: ButtonPatternTestModifier002
 * @tc.desc: Test ContentModifier
 * @tc.type: FUNC
 */
HWTEST_F(ButtonTestNg, ButtonPatternTestModifier002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create button frame node.
     * @tc.expected: step1. node is not null.
     */
    TestProperty testProperty;
    ButtonModelNG buttonModelNG;
    std::list<RefPtr<Component>> buttonChildren;
    CreateWithPara createWithPara;
    createWithPara.parseSuccess = true;
    createWithPara.label = BUTTON_VALUE;
    buttonModelNG.CreateWithLabel(createWithPara, buttonChildren);
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. test BuildContentModifierNode
     * @tc.expected: step2. func is ok,the result is ok.
     */
    auto buttonPattern = frameNode->GetPattern<ButtonPattern>();
    ASSERT_NE(buttonPattern, nullptr);

    /**
     * Mock the func, set the result to 'TEST_RESULT'.
     * when the func is excuted successfully, the result will be changed.
     * when the func is excuted, it will generate a button node.
    */
    std::string result;
    auto node = [&result, this](ButtonConfiguration config) -> RefPtr<FrameNode> {
        result = TEST_RESULT_CAPSULE;
        TestProperty property;
        property.typeValue = std::make_optional(BUTTON_TYPE_CAPSULE_VALUE);
        RefPtr<FrameNode> frameNode = this->CreateLabelButtonParagraph(CREATE_VALUE, property);
        return frameNode;
    };
    buttonPattern->SetBuilderFunc(node);
    auto buttonNode = buttonPattern->BuildContentModifierNode();

    /**
     * @tc.steps: step3. test BuildContentModifierNode, set the button type as CAPSULE.
     * @tc.expected: step3. change func, test the result, it should be CAPSULE.
     */
    EXPECT_EQ(result, TEST_RESULT_CAPSULE);
    EXPECT_EQ("Button", buttonNode->GetTag());
    auto buttonLayoutProperty = buttonNode->GetLayoutProperty<ButtonLayoutProperty>();
    EXPECT_EQ(buttonLayoutProperty->GetTypeValue(), BUTTON_TYPE_CAPSULE_VALUE);

    /**
     * @tc.steps: step4. test BuildContentModifierNode, set new func, set the button type as DOWNLOAD.
     * @tc.expected: step4. change func, test the result. it should be DOWNLOAD. It means the new func is excuted.
     */
    auto nodeFunc = [&result, this](ButtonConfiguration config) -> RefPtr<FrameNode> {
        result = TEST_RESULT_DOWNLOAD;
        TestProperty property;
        property.typeValue = std::make_optional(BUTTON_TYPE_DOWNLOAD_VALUE);
        RefPtr<FrameNode> frameNode = this->CreateLabelButtonParagraph(CREATE_VALUE, property);
        return frameNode;
    };
    buttonPattern->SetBuilderFunc(nodeFunc);

    buttonNode = buttonPattern->BuildContentModifierNode();
    EXPECT_EQ(result, TEST_RESULT_DOWNLOAD);
    EXPECT_EQ("Button", buttonNode->GetTag());
    auto layoutProperty = buttonNode->GetLayoutProperty<ButtonLayoutProperty>();
    EXPECT_EQ(layoutProperty->GetTypeValue(), BUTTON_TYPE_DOWNLOAD_VALUE);
}

/**
 * @tc.name: ButtonBuilderNameTest001
 * @tc.desc: Test SetBuilderFunc
 * @tc.type: FUNC
 */
HWTEST_F(ButtonTestNg, ButtonBuilderNameTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init Button node
     */
    TestProperty testProperty;
    const std::string buttonLabel = "Test Label";
    auto frameNode = CreateLabelButtonParagraph(buttonLabel, testProperty);
    auto gesture = frameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. Set buttonConfiguration
     */
    auto buttonPattern = frameNode->GetPattern<ButtonPattern>();
    ASSERT_NE(buttonPattern, nullptr);
    auto eventHub = frameNode->GetEventHub<EventHub>();
    eventHub->SetEnabled(true);
    buttonPattern->OnTouchDown();

    /**
     * @tc.steps: step3. make builderFunc
     */
    auto node = [buttonLabel](ButtonConfiguration config) -> RefPtr<FrameNode> {
            EXPECT_EQ(buttonLabel, config.label_);
            EXPECT_EQ(true, config.pressed_);
            EXPECT_EQ(true, config.enabled_);
            return nullptr;
        };

    /**
     * @tc.steps: step4. Set parameters to pattern builderFunc
     */
    buttonPattern->SetBuilderFunc(node);
    buttonPattern->BuildContentModifierNode();
}

/**
 * @tc.name: ButtonBuilderNameTest002
 * @tc.desc: Test SetBuilderFunc
 * @tc.type: FUNC
 */
HWTEST_F(ButtonTestNg, ButtonBuilderNameTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init Button node
     */
    TestProperty testProperty;
    const std::string buttonLabel = "123";
    auto frameNode = CreateLabelButtonParagraph(buttonLabel, testProperty);
    auto gesture = frameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. Set buttonConfiguration
     */
    auto buttonPattern = frameNode->GetPattern<ButtonPattern>();
    ASSERT_NE(buttonPattern, nullptr);
    auto eventHub = frameNode->GetEventHub<EventHub>();
    eventHub->SetEnabled(true);
    buttonPattern->OnTouchDown();

    /**
     * @tc.steps: step3. make builderFunc
     */
    auto node = [buttonLabel](ButtonConfiguration config) -> RefPtr<FrameNode> {
            EXPECT_EQ(buttonLabel, config.label_);
            EXPECT_EQ(true, config.pressed_);
            EXPECT_EQ(true, config.enabled_);
            return nullptr;
        };

    /**
     * @tc.steps: step4. Set parameters to pattern builderFunc
     */
    buttonPattern->SetBuilderFunc(node);
    buttonPattern->BuildContentModifierNode();
}

/**
 * @tc.name: ButtonBuilderNameTest003
 * @tc.desc: Test SetBuilderFunc
 * @tc.type: FUNC
 */
HWTEST_F(ButtonTestNg, ButtonBuilderNameTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init Button node
     */
    TestProperty testProperty;
    const std::string buttonLabel = "!!!";
    auto frameNode = CreateLabelButtonParagraph(buttonLabel, testProperty);
    auto gesture = frameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. Set buttonConfiguration
     */
    auto buttonPattern = frameNode->GetPattern<ButtonPattern>();
    ASSERT_NE(buttonPattern, nullptr);
    auto eventHub = frameNode->GetEventHub<EventHub>();
    eventHub->SetEnabled(true);
    buttonPattern->OnTouchDown();

    /**
     * @tc.steps: step3. make builderFunc
     */
    auto node = [buttonLabel](ButtonConfiguration config) -> RefPtr<FrameNode> {
            EXPECT_EQ(buttonLabel, config.label_);
            EXPECT_EQ(true, config.pressed_);
            EXPECT_EQ(true, config.enabled_);
            return nullptr;
        };

    /**
     * @tc.steps: step4. Set parameters to pattern builderFunc
     */
    buttonPattern->SetBuilderFunc(node);
    buttonPattern->BuildContentModifierNode();
}

/**
 * @tc.name: NeedAgingMeasureTest001
 * @tc.desc: Test NeedAgingMeasureFunc
 * @tc.type: FUNC
 */
HWTEST_F(ButtonTestNg, NeedAgingMeasureTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create bubble, set font scale to 1.75 and get frameNode.
     */
    auto context = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(context);
    context->fontScale_ = 1.75f;
    TestProperty testProperty;
    testProperty.typeValue = std::make_optional(ButtonType::CAPSULE);
    testProperty.stateEffectValue = std::make_optional(STATE_EFFECT);
    auto frameNode = CreateLabelButtonParagraph(CREATE_VALUE, testProperty);
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. get layout property, layoutAlgorithm and create layoutWrapper.
     */
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    auto layoutWrapper = frameNode->CreateLayoutWrapper();
    auto buttonPattern = frameNode->GetPattern<ButtonPattern>();
    ASSERT_NE(buttonPattern, nullptr);
    auto buttonLayoutProperty = buttonPattern->GetLayoutProperty<ButtonLayoutProperty>();
    ASSERT_NE(buttonLayoutProperty, nullptr);
    auto buttonLayoutAlgorithm =
        AccessibilityManager::DynamicCast<ButtonLayoutAlgorithm>(buttonPattern->CreateLayoutAlgorithm());
    ASSERT_NE(buttonLayoutAlgorithm, nullptr);
    layoutWrapper->SetLayoutAlgorithm(AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(buttonLayoutAlgorithm));

    /**
     * @tc.steps: step3. update layoutWrapper.
     */
    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.maxSize = CONTAINER_SIZE;
    parentLayoutConstraint.percentReference = CONTAINER_SIZE;
    layoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(parentLayoutConstraint);
    layoutWrapper->GetLayoutProperty()->UpdateContentConstraint();

    /**
     * @tc.steps: step4. call NeedAgingMeasure and verify return value.
     * @tc.expected: the NeedAgingMeasure return value is true
     */
    bool result = buttonLayoutAlgorithm->NeedAgingMeasure(AccessibilityManager::RawPtr(layoutWrapper));
    EXPECT_TRUE(result);
}
} // namespace OHOS::Ace::NG
