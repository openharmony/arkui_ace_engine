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

#include <algorithm>
#include <cstddef>
#include <optional>

#include "gtest/gtest.h"

#define protected public
#define private public
#include "base/geometry/dimension.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/components/button/button_theme.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/text_style.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/pattern/button/button_layout_property.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/button/button_view.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/test/mock/theme/mock_theme_manager.h"
#include "core/pipeline_ng/test/mock/mock_pipeline_base.h"

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
const ButtonType BUTTON_TYPE_CAPSULE_VALUE = ButtonType::CAPSULE;
const ButtonType BUTTON_TYPE_CUSTOM_VALUE = ButtonType::CUSTOM;
const ButtonType BUTTON_TYPE_DOWNLOAD_VALUE = ButtonType::DOWNLOAD;
const ButtonType BUTTON_TYPE_CIRCLE_VALUE = ButtonType::CIRCLE;
const Dimension BUTTON_FONT_SIZE_VALUE = 30.0_vp;
const Dimension BORDER_RADIUS = 5.0_vp;
const Ace::FontWeight BUTTON_BOLD_FONT_WEIGHT_VALUE = Ace::FontWeight::BOLD;
const Ace::FontStyle BUTTON_ITALIC_FONT_STYLE_VALUE = Ace::FontStyle::ITALIC;
const Color BUTTON_TEXT_COLOR_VALUE = Color::RED;
const Color FONT_COLOR = Color(0XFFFF0000);
const std::vector<std::string> FONT_FAMILY_VALUE = { "cursive" };
const char BUTTON_ETS_TAG[] = "Button";
const SizeF CONTAINER_SIZE(FULL_SCREEN_WIDTH, FULL_SCREEN_HEIGHT);
const SizeF BUTTON_ONLY_HAS_WIDTH_SIZE(BUTTON_ONLY_HAS_WIDTH_VALUE, BUTTON_ONLY_HAS_WIDTH_VALUE);
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

class ButtonPatternTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    static void FontWeightTest(RefPtr<ButtonLayoutProperty> buttonLayoutProperty,
        RefPtr<ButtonPattern> buttonPattern, RefPtr<TextLayoutProperty> textLayoutProp);

protected:
    RefPtr<FrameNode> CreateLabelButtonParagraph(const std::string& createValue, const TestProperty& testProperty);
    RefPtr<FrameNode> CreateLabelButtonParagraphForLableStyle(
        const std::string& createValue, const LableStyleProperty& lableStyleProperty);
};

void ButtonPatternTestNg::SetUpTestCase()
{
    MockPipelineBase::SetUp();
    // set buttonTheme to themeManager before using themeManager to get buttonTheme
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<ButtonTheme>()));
}

void ButtonPatternTestNg::TearDownTestCase()
{
    MockPipelineBase::TearDown();
}

void ButtonPatternTestNg::FontWeightTest(RefPtr<ButtonLayoutProperty> buttonLayoutProperty,
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

RefPtr<FrameNode> ButtonPatternTestNg::CreateLabelButtonParagraph(
    const std::string& createValue, const TestProperty& testProperty)
{
    ButtonView::CreateWithLabel(createValue);
    if (testProperty.typeValue.has_value()) {
        ButtonView::SetType(testProperty.typeValue.value());
    }
    if (testProperty.stateEffectValue.has_value()) {
        ButtonView::SetStateEffect(testProperty.stateEffectValue.value());
    }
    if (testProperty.fontSizeValue.has_value()) {
        ButtonView::SetFontSize(testProperty.fontSizeValue.value());
    }
    if (testProperty.fontWeightValue.has_value()) {
        ButtonView::SetFontWeight(testProperty.fontWeightValue.value());
    }
    if (testProperty.textColorValue.has_value()) {
        ButtonView::SetFontColor(testProperty.textColorValue.value());
    }
    if (testProperty.fontStyleValue.has_value()) {
        ButtonView::SetFontStyle(testProperty.fontStyleValue.value());
    }
    if (testProperty.fontFamilyValue.has_value()) {
        ButtonView::SetFontFamily(testProperty.fontFamilyValue.value());
    }
    if (testProperty.borderRadius.has_value()) {
        ButtonView::SetBorderRadius(testProperty.borderRadius.value());
    }

    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    return AceType::DynamicCast<FrameNode>(element);
}

RefPtr<FrameNode> ButtonPatternTestNg::CreateLabelButtonParagraphForLableStyle(
    const std::string& createValue, const LableStyleProperty& lableStyleProperty)
{
    ButtonView::ButtonParameters buttonParameters;
    ButtonView::CreateWithLabel(createValue);
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
    ButtonView::SetLableStyle(buttonParameters);

    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    return AceType::DynamicCast<FrameNode>(element);
}

/**
 * @tc.name: ButtonPatternTest001
 * @tc.desc: Test all the properties of button.
 * @tc.type: FUNC
 * @tc.author: zhangxiao
 */
HWTEST_F(ButtonPatternTestNg, ButtonPatternTest001, TestSize.Level1)
{
    TestProperty testProperty;
    testProperty.typeValue = std::make_optional(BUTTON_TYPE_CAPSULE_VALUE);

    RefPtr<FrameNode> frameNode = CreateLabelButtonParagraph(CREATE_VALUE, testProperty);
    EXPECT_EQ(frameNode == nullptr, false);
    auto layoutProperty = frameNode->GetLayoutProperty<ButtonLayoutProperty>();
    EXPECT_EQ(layoutProperty == nullptr, false);
    EXPECT_EQ(layoutProperty->GetTypeValue(), BUTTON_TYPE_CAPSULE_VALUE);
}

/**
 * @tc.name: ButtonPatternTest002
 * @tc.desc: Test all the properties of button.
 * @tc.type: FUNC
 * @tc.author: shanshurong
 */
HWTEST_F(ButtonPatternTestNg, ButtonPatternTest002, TestSize.Level1)
{
    TestProperty testProperty;
    testProperty.typeValue = std::make_optional(BUTTON_TYPE_CUSTOM_VALUE);
    // create button without label
    ButtonView::Create(BUTTON_ETS_TAG);
    ButtonView::SetType(testProperty.typeValue.value());
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    EXPECT_EQ(frameNode == nullptr, false);
    auto buttonPattern = frameNode->GetPattern<ButtonPattern>();
    EXPECT_EQ(buttonPattern == nullptr, false);
    buttonPattern->InitButtonLabel();
    RefPtr<LayoutProperty> layoutProperty = frameNode->GetLayoutProperty();
    EXPECT_EQ(layoutProperty == nullptr, false);
    RefPtr<ButtonLayoutProperty> buttonLayoutProperty = AceType::DynamicCast<ButtonLayoutProperty>(layoutProperty);
    EXPECT_EQ(buttonLayoutProperty == nullptr, false);
    EXPECT_EQ(buttonLayoutProperty->GetTypeValue(), BUTTON_TYPE_CUSTOM_VALUE);
}

/**
 * @tc.name: ButtonPatternTest003
 * @tc.desc: Test all the properties of button.
 * @tc.type: FUNC
 * @tc.author: shanshurong
 */
HWTEST_F(ButtonPatternTestNg, ButtonPatternTest003, TestSize.Level1)
{
    TestProperty testProperty;
    testProperty.typeValue = std::make_optional(BUTTON_TYPE_DOWNLOAD_VALUE);
    testProperty.fontSizeValue = std::make_optional(BUTTON_FONT_SIZE_VALUE);
    testProperty.fontWeightValue = std::make_optional(BUTTON_BOLD_FONT_WEIGHT_VALUE);
    RefPtr<FrameNode> frameNode = CreateLabelButtonParagraph(CREATE_VALUE, testProperty);
    EXPECT_EQ(frameNode == nullptr, false);
    RefPtr<LayoutProperty> layoutProperty = frameNode->GetLayoutProperty();
    EXPECT_EQ(layoutProperty == nullptr, false);
    RefPtr<ButtonLayoutProperty> buttonLayoutProperty = AceType::DynamicCast<ButtonLayoutProperty>(layoutProperty);
    EXPECT_EQ(buttonLayoutProperty == nullptr, false);
    EXPECT_EQ(buttonLayoutProperty->GetTypeValue(), BUTTON_TYPE_DOWNLOAD_VALUE);
    EXPECT_EQ(buttonLayoutProperty->GetFontSizeValue(), BUTTON_FONT_SIZE_VALUE);
    EXPECT_EQ(buttonLayoutProperty->GetFontWeightValue(), BUTTON_BOLD_FONT_WEIGHT_VALUE);
    EXPECT_EQ(buttonLayoutProperty->GetLabelValue(), CREATE_VALUE);
}

/**
 * @tc.name: ButtonPatternTest004
 * @tc.desc: Test all the properties of button.
 * @tc.type: FUNC
 * @tc.author: shanshurong
 */
HWTEST_F(ButtonPatternTestNg, ButtonPatternTest004, TestSize.Level1)
{
    TestProperty testProperty;
    testProperty.typeValue = std::make_optional(BUTTON_TYPE_CIRCLE_VALUE);
    testProperty.textColorValue = std::make_optional(BUTTON_TEXT_COLOR_VALUE);
    testProperty.fontStyleValue = std::make_optional(BUTTON_ITALIC_FONT_STYLE_VALUE);
    testProperty.fontFamilyValue = std::make_optional(FONT_FAMILY_VALUE);
    auto frameNode = CreateLabelButtonParagraph(CREATE_VALUE, testProperty);
    EXPECT_EQ(frameNode == nullptr, false);

    RefPtr<LayoutProperty> layoutProperty = frameNode->GetLayoutProperty();
    EXPECT_EQ(layoutProperty == nullptr, false);
    RefPtr<ButtonLayoutProperty> buttonLayoutProperty = AceType::DynamicCast<ButtonLayoutProperty>(layoutProperty);
    EXPECT_EQ(buttonLayoutProperty == nullptr, false);
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
HWTEST_F(ButtonPatternTestNg, ButtonPatternTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create button and get frameNode.
     */
    TestProperty testProperty;
    testProperty.borderRadius = std::make_optional(BORDER_RADIUS);
    testProperty.stateEffectValue = std::make_optional(STATE_EFFECT);
    auto frameNode = CreateLabelButtonParagraph(CREATE_VALUE, testProperty);
    EXPECT_FALSE(frameNode == nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::BUTTON_ETS_TAG);

    /**
     * @tc.steps: step2.get switch property and check whether the property value is correct.
     */
    auto pattern = AceType::DynamicCast<ButtonPattern>(frameNode->GetPattern());
    EXPECT_FALSE(pattern == nullptr);
    auto layoutProperty = pattern->GetLayoutProperty<ButtonLayoutProperty>();
    EXPECT_FALSE(layoutProperty == nullptr);
    auto buttonEventHub = frameNode->GetEventHub<ButtonEventHub>();
    CHECK_NULL_VOID(buttonEventHub);

    EXPECT_EQ(layoutProperty->GetBorderRadius(), BORDER_RADIUS);
    EXPECT_EQ(buttonEventHub->GetStateEffect(), STATE_EFFECT);
}

/**
 * @tc.name: ButtonPatternTest006
 * @tc.desc: test button pattern OnModifyDone.
 * @tc.type: FUNC
 */
HWTEST_F(ButtonPatternTestNg, ButtonPatternTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create bubble and get frameNode.
     */
    TestProperty testProperty;
    testProperty.borderRadius = std::make_optional(BORDER_RADIUS);
    auto frameNode = CreateLabelButtonParagraph(CREATE_VALUE, testProperty);
    EXPECT_FALSE(frameNode == nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::BUTTON_ETS_TAG);

    /**
     * @tc.steps: step2. get pattern and update frameNode.
     * @tc.expected: step2. related function is called.
     */
    auto buttonPattern = frameNode->GetPattern<ButtonPattern>();
    EXPECT_FALSE(buttonPattern == nullptr);
    buttonPattern->OnModifyDone();
    auto buttonLayoutProperty = frameNode->GetLayoutProperty<ButtonLayoutProperty>();
    EXPECT_FALSE(buttonLayoutProperty == nullptr);
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
    EXPECT_FALSE(text == nullptr);
    auto textLayoutProp = text->GetLayoutProperty<TextLayoutProperty>();
    EXPECT_FALSE(textLayoutProp == nullptr);

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
HWTEST_F(ButtonPatternTestNg, ButtonPatternTest007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create bubble and get frameNode.
     */
    TestProperty testProperty;
    auto frameNode = CreateLabelButtonParagraph(CREATE_VALUE, testProperty);
    EXPECT_FALSE(frameNode == nullptr);

    /**
     * @tc.steps: test buttonPattern OnTouchDown OnTouchUp function.
     * @tc.expected: step3. check whether the function is executed.
     */
    auto buttonPattern = frameNode->GetPattern<ButtonPattern>();
    EXPECT_FALSE(buttonPattern == nullptr);
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
HWTEST_F(ButtonPatternTestNg, ButtonPatternTest008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create bubble and get frameNode.
     */
    TestProperty testProperty;
    testProperty.typeValue = std::make_optional(ButtonType::CIRCLE);
    testProperty.stateEffectValue = std::make_optional(STATE_EFFECT);
    auto frameNode = CreateLabelButtonParagraph(CREATE_VALUE, testProperty);
    EXPECT_FALSE(frameNode == nullptr);

    /**
     * @tc.steps: step2. get layout property, layoutAlgorithm and create layoutWrapper.
     * @tc.expected: step2. related function is called.
     */
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_FALSE(geometryNode == nullptr);
    auto layoutWrapper = frameNode->CreateLayoutWrapper();
    auto buttonPattern = frameNode->GetPattern<ButtonPattern>();
    EXPECT_FALSE(buttonPattern == nullptr);
    auto buttonLayoutProperty = buttonPattern->GetLayoutProperty<ButtonLayoutProperty>();
    EXPECT_FALSE(buttonLayoutProperty == nullptr);
    auto buttonLayoutAlgorithm = buttonPattern->CreateLayoutAlgorithm();
    EXPECT_FALSE(buttonLayoutAlgorithm == nullptr);
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
}

/**
 * @tc.name: ButtonPatternTest009
 * @tc.desc: test button layout using buttonType CAPSULE.
 * @tc.type: FUNC
 */
HWTEST_F(ButtonPatternTestNg, ButtonPatternTest009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create bubble and get frameNode.
     */
    TestProperty testProperty;
    testProperty.typeValue = std::make_optional(ButtonType::CAPSULE);
    testProperty.stateEffectValue = std::make_optional(STATE_EFFECT);
    auto frameNode = CreateLabelButtonParagraph(CREATE_VALUE, testProperty);
    EXPECT_FALSE(frameNode == nullptr);

    /**
     * @tc.steps: step2. get layout property, layoutAlgorithm and create layoutWrapper.
     * @tc.expected: step2. related function is called.
     */
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_FALSE(geometryNode == nullptr);
    auto layoutWrapper = frameNode->CreateLayoutWrapper();
    auto buttonPattern = frameNode->GetPattern<ButtonPattern>();
    EXPECT_FALSE(buttonPattern == nullptr);
    auto buttonLayoutProperty = buttonPattern->GetLayoutProperty<ButtonLayoutProperty>();
    EXPECT_FALSE(buttonLayoutProperty == nullptr);
    auto buttonLayoutAlgorithm = buttonPattern->CreateLayoutAlgorithm();
    EXPECT_FALSE(buttonLayoutAlgorithm == nullptr);
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
HWTEST_F(ButtonPatternTestNg, ButtonPatternTest0010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create bubble and get frameNode.
     */
    TestProperty testProperty;
    testProperty.typeValue = std::make_optional(ButtonType::NORMAL);
    testProperty.stateEffectValue = std::make_optional(STATE_EFFECT);
    testProperty.borderRadius = std::make_optional(BORDER_RADIUS);
    auto frameNode = CreateLabelButtonParagraph(CREATE_VALUE, testProperty);
    EXPECT_FALSE(frameNode == nullptr);

    /**
     * @tc.steps: step2. get layout property, layoutAlgorithm and create layoutWrapper.
     * @tc.expected: step2. related function is called.
     */
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_FALSE(geometryNode == nullptr);
    auto layoutWrapper = frameNode->CreateLayoutWrapper();
    auto buttonPattern = frameNode->GetPattern<ButtonPattern>();
    EXPECT_FALSE(buttonPattern == nullptr);
    auto buttonLayoutAlgorithm = buttonPattern->CreateLayoutAlgorithm();
    EXPECT_FALSE(buttonLayoutAlgorithm == nullptr);
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
     * @tc.expected: step3. check whether the value of geometry's frameSize and frameOffset is correct.
     */
    buttonLayoutAlgorithm->Measure(AccessibilityManager::RawPtr(layoutWrapper));
    buttonLayoutAlgorithm->Layout(AccessibilityManager::RawPtr(layoutWrapper));
    EXPECT_EQ(layoutWrapper->GetGeometryNode()->GetFrameSize().Width(), BUTTON_WIDTH);
    EXPECT_EQ(layoutWrapper->GetGeometryNode()->GetFrameOffset(), OffsetF());
}

/**
 * @tc.name: ButtonPatternTest011
 * @tc.desc: test button pattern OnModifyDone.
 * @tc.type: FUNC
 */
HWTEST_F(ButtonPatternTestNg, ButtonPatternTest011, TestSize.Level1)
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
    EXPECT_EQ(textLayoutProp->GetAdaptMinFontSize()->ConvertToPx(), 15);
    EXPECT_EQ(textLayoutProp->GetAdaptMaxFontSize()->ConvertToPx(), 50);
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
HWTEST_F(ButtonPatternTestNg, ButtonPatternTest012, TestSize.Level1)
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
HWTEST_F(ButtonPatternTestNg, ButtonPatternTest013, TestSize.Level1)
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
HWTEST_F(ButtonPatternTestNg, ButtonPatternTest014, TestSize.Level1)
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
} // namespace OHOS::Ace::NG
