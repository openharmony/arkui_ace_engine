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
const std::u16string CREATE_U16VALUE = u"Hello World";
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
const Dimension DEFAULT_HEIGTH = 40.0_vp;
const uint32_t MAX_LINE_VALUE = 10;

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

class ButtonPropertyTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();

protected:
    RefPtr<FrameNode> CreateLabelButtonParagraph(const std::string& createValue, const TestProperty& testProperty);
    RefPtr<FrameNode> CreateLabelButtonParagraphByRoundedRect(
        const std::string& createValue, const TestProperty& testProperty);
};

void ButtonPropertyTestNg::SetUpTestCase()
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

void ButtonPropertyTestNg::TearDownTestCase()
{
    MockPipelineContext::TearDown();
}

RefPtr<FrameNode> ButtonPropertyTestNg::CreateLabelButtonParagraph(
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

RefPtr<FrameNode> ButtonPropertyTestNg::CreateLabelButtonParagraphByRoundedRect(
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

/**
 * @tc.name: ButtonPropertyTest001
 * @tc.desc: Test all the properties of button.
 * @tc.type: FUNC
 */
HWTEST_F(ButtonPropertyTestNg, ButtonPropertyTest001, TestSize.Level1)
{
    TestProperty testProperty;
    testProperty.typeValue = std::make_optional(BUTTON_TYPE_CAPSULE_VALUE);
    /**
     * @tc.steps: step1. create button and get frameNode.
     */
    RefPtr<FrameNode> frameNode = CreateLabelButtonParagraph(CREATE_VALUE, testProperty);
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<ButtonLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    /**
     * @tc.steps: step2. get property from frameNode.
     * @tc.expected: step2. the button type property meet expectations.
     */
    EXPECT_EQ(layoutProperty->GetTypeValue(), BUTTON_TYPE_CAPSULE_VALUE);
}

/**
 * @tc.name: ButtonPropertyTest002
 * @tc.desc: Test all the properties of button.
 * @tc.type: FUNC
 */
HWTEST_F(ButtonPropertyTestNg, ButtonPropertyTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create test property.
     */
    TestProperty testProperty;
    testProperty.typeValue = std::make_optional(BUTTON_TYPE_CUSTOM_VALUE);
    // create button without label
    ButtonModelNG buttonModelNG;
    std::list<RefPtr<Component>> buttonChildren;
    createWithPara.parseSuccess = false;
    /**
     * @tc.steps: step2. call CreateWithLabel build a button, change the button type.
     */
    buttonModelNG.CreateWithLabel(CREATE_VALUE);
    buttonModelNG.SetType(static_cast<int32_t>(testProperty.typeValue.value()));
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto buttonPattern = frameNode->GetPattern<ButtonPattern>();
    ASSERT_NE(buttonPattern, nullptr);
    /**
     * @tc.steps: step3. try init button label.
     * @tc.expected: step3. the button type property meet expectations.
     */
    buttonPattern->InitButtonLabel();
    RefPtr<LayoutProperty> layoutProperty = frameNode->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    RefPtr<ButtonLayoutProperty> buttonLayoutProperty = AceType::DynamicCast<ButtonLayoutProperty>(layoutProperty);
    ASSERT_NE(buttonLayoutProperty, nullptr);
    EXPECT_EQ(buttonLayoutProperty->GetTypeValue(), BUTTON_TYPE_CUSTOM_VALUE);
}

/**
 * @tc.name: ButtonPropertyTest003
 * @tc.desc: Test all the properties of button.
 * @tc.type: FUNC
 */
HWTEST_F(ButtonPropertyTestNg, ButtonPropertyTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create test property.
     */
    TestProperty testProperty;
    testProperty.typeValue = std::make_optional(BUTTON_TYPE_DOWNLOAD_VALUE);
    testProperty.fontSizeValue = std::make_optional(BUTTON_FONT_SIZE_VALUE);
    testProperty.fontWeightValue = std::make_optional(BUTTON_BOLD_FONT_WEIGHT_VALUE);
    /**
     * @tc.steps: step2. build a button with test property.
     */
    RefPtr<FrameNode> frameNode = CreateLabelButtonParagraph(CREATE_VALUE, testProperty);
    ASSERT_NE(frameNode, nullptr);
    RefPtr<LayoutProperty> layoutProperty = frameNode->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    /**
     * @tc.steps: step3. get button layout property.
     * @tc.expected: step3. the property value meet expectations.
     */
    RefPtr<ButtonLayoutProperty> buttonLayoutProperty = AceType::DynamicCast<ButtonLayoutProperty>(layoutProperty);
    ASSERT_NE(buttonLayoutProperty, nullptr);
    EXPECT_EQ(buttonLayoutProperty->GetTypeValue(), BUTTON_TYPE_DOWNLOAD_VALUE);
    EXPECT_EQ(buttonLayoutProperty->GetFontSizeValue(), BUTTON_FONT_SIZE_VALUE);
    EXPECT_EQ(buttonLayoutProperty->GetFontWeightValue(), BUTTON_BOLD_FONT_WEIGHT_VALUE);
    EXPECT_EQ(buttonLayoutProperty->GetLabelValue(), CREATE_VALUE);
}

/**
 * @tc.name: ButtonPropertyTest004
 * @tc.desc: Test all the properties of button.
 * @tc.type: FUNC
 */
HWTEST_F(ButtonPropertyTestNg, ButtonPropertyTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create test property.
     */
    TestProperty testProperty;
    testProperty.typeValue = std::make_optional(BUTTON_TYPE_CIRCLE_VALUE);
    testProperty.textColorValue = std::make_optional(BUTTON_TEXT_COLOR_VALUE);
    testProperty.fontStyleValue = std::make_optional(BUTTON_ITALIC_FONT_STYLE_VALUE);
    testProperty.fontFamilyValue = std::make_optional(FONT_FAMILY_VALUE);
    /**
     * @tc.steps: step2. build a button with test property.
     */
    auto frameNode = CreateLabelButtonParagraph(CREATE_VALUE, testProperty);
    ASSERT_NE(frameNode, nullptr);

    RefPtr<LayoutProperty> layoutProperty = frameNode->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    /**
     * @tc.steps: step3. get button layout property.
     * @tc.expected: step3. the property value meet expectations.
     */
    RefPtr<ButtonLayoutProperty> buttonLayoutProperty = AceType::DynamicCast<ButtonLayoutProperty>(layoutProperty);
    ASSERT_NE(buttonLayoutProperty, nullptr);
    EXPECT_EQ(buttonLayoutProperty->GetTypeValue(), BUTTON_TYPE_CIRCLE_VALUE);
    EXPECT_EQ(buttonLayoutProperty->GetFontColorValue(), BUTTON_TEXT_COLOR_VALUE);
    EXPECT_EQ(buttonLayoutProperty->GetLabelValue(), CREATE_VALUE);
    EXPECT_EQ(buttonLayoutProperty->GetFontStyle(), BUTTON_ITALIC_FONT_STYLE_VALUE);
    EXPECT_EQ(buttonLayoutProperty->GetFontFamily(), FONT_FAMILY_VALUE);
}

/**
 * @tc.name: ButtonPropertyTest005
 * @tc.desc: test button created.
 * @tc.type: FUNC
 */
HWTEST_F(ButtonPropertyTestNg, ButtonPropertyTest005, TestSize.Level1)
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
    /**
     * @tc.steps: step3. get button layout property.
     * @tc.expected: step3. the property value meet expectations.
     */
    auto layoutProperty = pattern->GetLayoutProperty<ButtonLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    auto buttonEventHub = frameNode->GetEventHub<ButtonEventHub>();
    CHECK_NULL_VOID(buttonEventHub);

    EXPECT_EQ(buttonEventHub->GetStateEffect(), STATE_EFFECT);
}

/**
 * @tc.name: ButtonPropertyTest006
 * @tc.desc: test button created.
 * @tc.type: FUNC
 */
HWTEST_F(ButtonPropertyTestNg, ButtonPropertyTest006, TestSize.Level1)
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
    /**
     * @tc.steps: step3. get button layout property.
     * @tc.expected: step3. the property value meet expectations.
     */
    auto layoutProperty = pattern->GetLayoutProperty<ButtonLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    auto buttonEventHub = frameNode->GetEventHub<ButtonEventHub>();
    CHECK_NULL_VOID(buttonEventHub);

    EXPECT_EQ(buttonEventHub->GetStateEffect(), STATE_EFFECT);
}

/**
 * @tc.name: ButtonPropertyTest007
 * @tc.desc: test button pattern OnModifyDone.
 * @tc.type: FUNC
 */
HWTEST_F(ButtonPropertyTestNg, ButtonPropertyTest007, TestSize.Level1)
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
    /**
     * @tc.steps: step3. get button layout property.
     * @tc.expected: step3. the property value meet expectations.
     */
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

    EXPECT_EQ(textLayoutProp->GetContent(), CREATE_U16VALUE);
    EXPECT_EQ(textLayoutProp->GetFontSize(), BUTTON_FONT_SIZE_VALUE);
    EXPECT_EQ(textLayoutProp->GetFontWeight(), BUTTON_BOLD_FONT_WEIGHT_VALUE);
    EXPECT_EQ(textLayoutProp->GetTextColor(), FONT_COLOR);
    EXPECT_EQ(textLayoutProp->GetFontFamily(), FONT_FAMILY_VALUE);
}

/**
 * @tc.name: ButtonPropertyTest008
 * @tc.desc: Test button view branch
 * @tc.type: FUNC
 */
HWTEST_F(ButtonPropertyTestNg, ButtonPropertyTest008, TestSize.Level1)
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
 * @tc.name: ButtonPropertyTest009
 * @tc.desc: Test GetFirstValidRadius
 * @tc.type: FUNC
 */
HWTEST_F(ButtonPropertyTestNg, ButtonPropertyTest009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create and get a button node.
     */
    TestProperty testProperty;
    auto frameNode = CreateLabelButtonParagraph(CREATE_VALUE, testProperty);
    ASSERT_NE(frameNode, nullptr);
    auto buttonPattern = frameNode->GetPattern<ButtonPattern>();
    ASSERT_NE(buttonPattern, nullptr);
    auto buttonLayoutAlgorithm = AceType::DynamicCast<ButtonLayoutAlgorithm>(buttonPattern->CreateLayoutAlgorithm());
    ASSERT_NE(buttonLayoutAlgorithm, nullptr);
    BorderRadiusProperty radius;
    /**
     * @tc.steps: step2. get FirstValidRadius in ButtonLayoutAlgorithm.
     * @tc.expected: step2. firstValidRadius is zero.
     */
    auto firstValidRadius = buttonLayoutAlgorithm->GetFirstValidRadius(radius);
    EXPECT_EQ(firstValidRadius, 0.0_vp);
    /**
     * @tc.steps: step3. update top left radius.
     * @tc.expected: step3. the radius update success.
     */
    radius.radiusTopLeft = BORDER_RADIUS;
    firstValidRadius = buttonLayoutAlgorithm->GetFirstValidRadius(radius);
    EXPECT_EQ(firstValidRadius, BORDER_RADIUS);
    /**
     * @tc.steps: step4. reset top left and update top right radius.
     * @tc.expected: step4. the radius update success.
     */
    radius.radiusTopLeft.reset();
    radius.radiusTopRight = BORDER_RADIUS;
    firstValidRadius = buttonLayoutAlgorithm->GetFirstValidRadius(radius);
    EXPECT_EQ(firstValidRadius, BORDER_RADIUS);
    /**
     * @tc.steps: step5. reset top right and update bottom left radius.
     * @tc.expected: step5. the radius update success.
     */
    radius.radiusTopRight.reset();
    radius.radiusBottomLeft = BORDER_RADIUS;
    firstValidRadius = buttonLayoutAlgorithm->GetFirstValidRadius(radius);
    EXPECT_EQ(firstValidRadius, BORDER_RADIUS);
    /**
     * @tc.steps: step5. reset bottom left and update bottom right radius.
     * @tc.expected: step5. the radius update success.
     */
    radius.radiusBottomLeft.reset();
    radius.radiusBottomRight = BORDER_RADIUS;
    firstValidRadius = buttonLayoutAlgorithm->GetFirstValidRadius(radius);
    EXPECT_EQ(firstValidRadius, BORDER_RADIUS);
}


/**
 * @tc.name: ButtonPropertyTest010
 * @tc.desc: Test default button style
 * @tc.type: FUNC
 */
HWTEST_F(ButtonPropertyTestNg, ButtonPropertyTest010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. change the api level.
     */
    auto pipeline = PipelineBase::GetCurrentContext();
    pipeline->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_NINE));
    TestProperty testProperty;
    /**
     * @tc.steps: step2. create and get a button node.
     * @tc.expected: step2. the background in renderContext is as expected.
     */
    auto frameNode = CreateLabelButtonParagraph(CREATE_VALUE, testProperty);
    ASSERT_NE(frameNode, nullptr);
    auto renderContext = frameNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    EXPECT_EQ(renderContext->GetBackgroundColor(), Color::RED);
}


/**
 * @tc.name: ButtonPropertyTest011
 * @tc.desc: Test ButtonStyle 、 ControlSize and ButtonRle
 * @tc.type: FUNC
 */
HWTEST_F(ButtonPropertyTestNg, ButtonPropertyTest011, TestSize.Level1)
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
 * @tc.name: ButtonPropertyTest012
 * @tc.desc: Test button setLabelStyle
 * @tc.type: FUNC
 */
HWTEST_F(ButtonPropertyTestNg, ButtonPropertyTest012, TestSize.Level1)
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
    /**
     * @tc.steps: step2. create ButtonParameters and set default value.
     */
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
 * @tc.name: ButtonPropertyTest013
 * @tc.desc: Test all the properties of rounded rectangle button.
 * @tc.type: FUNC
 */
HWTEST_F(ButtonPropertyTestNg, ButtonPropertyTest013, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create button with type.
     * @tc.expected: step1. the type in button is as expected.
     */
    TestProperty testProperty;
    testProperty.typeValue = std::make_optional(BUTTON_TYPE_ROUNDED_RECTANGLE_VALUE);
    RefPtr<FrameNode> frameNode = CreateLabelButtonParagraphByRoundedRect(CREATE_VALUE, testProperty);
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<ButtonLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    EXPECT_EQ(layoutProperty->GetTypeValue(), BUTTON_TYPE_ROUNDED_RECTANGLE_VALUE);
}

/**
 * @tc.name: ButtonPropertyTest014
 * @tc.desc: Test all the properties of default button.
 * @tc.type: FUNC
 */
HWTEST_F(ButtonPropertyTestNg, ButtonPropertyTest014, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create button and get frameNode.
     * @tc.expected: step1. the default type is as expected.
     */
    TestProperty testProperty;
    RefPtr<FrameNode> frameNode = CreateLabelButtonParagraphByRoundedRect(CREATE_VALUE, testProperty);
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<ButtonLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    EXPECT_EQ(layoutProperty->GetTypeValue(), BUTTON_TYPE_ROUNDED_RECTANGLE_VALUE);
}


/**
 * @tc.name: ButtonPropertyTest015
 * @tc.desc: Test button accessible property
 * @tc.type: FUNC
 */
HWTEST_F(ButtonPropertyTestNg, ButtonPropertyTest015, TestSize.Level1)
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
 * @tc.name:ButtonPropertyTest016
 * @tc.desc: Test button setSize property
 * @tc.type: FUNC
 */
HWTEST_F(ButtonPropertyTestNg, ButtonPropertyTest016, TestSize.Level1)
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
    /**
     * @tc.steps: step2. update size property.
     * @tc.expected: step2. the size property update success.
     */
    buttonModelNG.SetSize(sizeWidth, sizeHeight);
    EXPECT_TRUE(sizeWidth.has_value());
    EXPECT_TRUE(sizeHeight.has_value());
    buttonModelNG.SetSize(std::nullopt, std::nullopt);
}
}