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

class ButtonPatternTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();

protected:
    RefPtr<FrameNode> CreateLabelButtonParagraph(const std::string& createValue, const TestProperty& testProperty);
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
    RefPtr<LayoutWrapper> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(frameNode, geometryNode, frameNode->GetLayoutProperty());
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
    RefPtr<LayoutWrapper> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(frameNode, geometryNode, frameNode->GetLayoutProperty());
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
    RefPtr<LayoutWrapper> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(frameNode, geometryNode, frameNode->GetLayoutProperty());
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
} // namespace OHOS::Ace::NG
