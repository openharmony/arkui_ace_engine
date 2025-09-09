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
#include "core/components_ng/pattern/button/button_model_static.h"
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
const ButtonType BUTTON_TYPE_CAPSULE_VALUE = ButtonType::CAPSULE;
const Dimension DEFAULT_HEIGTH = 40.0_vp;
const char* BUTTON_LABEL = "This is Button";
const Dimension BORDER_RADIUS = 5.0_vp;
const Dimension BUTTON_FONT_SIZE_VALUE = 30.0_vp;
const Ace::FontWeight BUTTON_BOLD_FONT_WEIGHT_VALUE = Ace::FontWeight::BOLD;
const Ace::FontStyle BUTTON_ITALIC_FONT_STYLE_VALUE = Ace::FontStyle::ITALIC;
const std::vector<std::string> FONT_FAMILY_VALUE = { "cursive" };
const Color BUTTON_TEXT_COLOR_VALUE = Color::RED;
const float BUTTON_SIZE = 20.00;
const float MIN_SCALE_VALUE = 0.5f;
const float MAX_SCALE_VALUE = 3.2f;
const uint32_t MAX_LINE_VALUE = 10;
} // namespace

class ButtonStaticTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();

protected:
    RefPtr<FrameNode> CreateLabelButtonParagraph(const std::string& createValue, const TestProperty& testProperty);
    RefPtr<FrameNode> CreateLabelButtonParagraphByRoundedRect(
        const std::string& createValue, const TestProperty& testProperty);
};

void ButtonStaticTestNg::SetUpTestCase()
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

void ButtonStaticTestNg::TearDownTestCase()
{
    MockPipelineContext::TearDown();
}

/**
 * @tc.name: ButtonStaticTestNg001
 * @tc.desc: test button SetRole.
 * @tc.type: FUNC
 */
HWTEST_F(ButtonStaticTestNg, ButtonStaticTestNg001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create button frameNode.
     */
    auto node = ButtonModelStatic::CreateFrameNode(ElementRegister::GetInstance()->MakeUniqueId());
    ASSERT_NE(node, nullptr);
    EXPECT_EQ(node->GetTag(), V2::BUTTON_ETS_TAG);
    auto frameNode = AceType::RawPtr(node);
    ASSERT_NE(node, nullptr);
    /**
     * @tc.steps: step2. create button layoutProperty.
     */
    auto layoutProperty = frameNode->GetLayoutProperty<ButtonLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    /**
     * @tc.steps: step3. test setRole.
     * @tc.expected: step3. the property value meet expectations.
     */
    std::optional<ButtonRole> buttonRole = std::nullopt;
    ButtonModelStatic::SetRole(frameNode, buttonRole);
    EXPECT_EQ(layoutProperty->GetButtonRole(), std::nullopt);
    buttonRole = ButtonRole::ERROR;
    ButtonModelStatic::SetRole(frameNode, buttonRole);
    EXPECT_EQ(layoutProperty->GetButtonRoleValue(), ButtonRole::ERROR);
}

/**
 * @tc.name: ButtonStaticTestNg002
 * @tc.desc: test button SetButtonStyle.
 * @tc.type: FUNC
 */
HWTEST_F(ButtonStaticTestNg, ButtonStaticTestNg002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create button frameNode.
     */
    auto node = ButtonModelStatic::CreateFrameNode(ElementRegister::GetInstance()->MakeUniqueId());
    ASSERT_NE(node, nullptr);
    EXPECT_EQ(node->GetTag(), V2::BUTTON_ETS_TAG);
    auto frameNode = AceType::RawPtr(node);
    ASSERT_NE(node, nullptr);
    /**
     * @tc.steps: step2. create button layoutProperty.
     */
    auto layoutProperty = frameNode->GetLayoutProperty<ButtonLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    /**
     * @tc.steps: step3. test SetButtonStyle.
     * @tc.expected: step3. the property value meet expectations.
     */
    std::optional<ButtonStyleMode> buttonStyle = std::nullopt;
    ButtonModelStatic::SetButtonStyle(frameNode, buttonStyle);
    EXPECT_EQ(layoutProperty->GetButtonStyle(), std::nullopt);
    buttonStyle = ButtonStyleMode::EMPHASIZE;
    ButtonModelStatic::SetButtonStyle(frameNode, buttonStyle);
    EXPECT_EQ(layoutProperty->GetButtonStyleValue(), ButtonStyleMode::EMPHASIZE);
}

/**
 * @tc.name: ButtonStaticTestNg003
 * @tc.desc: test button SetButtonSize.
 * @tc.type: FUNC
 */
HWTEST_F(ButtonStaticTestNg, ButtonStaticTestNg003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create button frameNode.
     */
    auto node = ButtonModelStatic::CreateFrameNode(ElementRegister::GetInstance()->MakeUniqueId());
    ASSERT_NE(node, nullptr);
    EXPECT_EQ(node->GetTag(), V2::BUTTON_ETS_TAG);
    auto frameNode = AceType::RawPtr(node);
    ASSERT_NE(node, nullptr);
    /**
     * @tc.steps: step2. create button layoutProperty.
     */
    auto layoutProperty = frameNode->GetLayoutProperty<ButtonLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    /**
     * @tc.steps: step3. test SetButtonSize.
     * @tc.expected: step3. the property value meet expectations.
     */
    std::optional<ControlSize> buttonControlSize = std::nullopt;
    ButtonModelStatic::SetControlSize(frameNode, buttonControlSize);
    EXPECT_EQ(layoutProperty->GetControlSize(), std::nullopt);
    buttonControlSize = ControlSize::SMALL;
    ButtonModelStatic::SetControlSize(frameNode, buttonControlSize);
    EXPECT_EQ(layoutProperty->GetControlSizeValue(), ControlSize::SMALL);
}

/**
 * @tc.name: ButtonStaticTestNg004
 * @tc.desc: test button SetLabel.
 * @tc.type: FUNC
 */
HWTEST_F(ButtonStaticTestNg, ButtonStaticTestNg004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create button frameNode.
     */
    auto node = ButtonModelStatic::CreateFrameNode(ElementRegister::GetInstance()->MakeUniqueId());
    ASSERT_NE(node, nullptr);
    EXPECT_EQ(node->GetTag(), V2::BUTTON_ETS_TAG);
    auto frameNode = AceType::RawPtr(node);
    ASSERT_NE(frameNode, nullptr);
    /**
     * @tc.steps: step2. create button layoutProperty.
     */
    auto layoutProperty = frameNode->GetLayoutProperty<ButtonLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    /**
     * @tc.steps: step3. test SetLabel.
     * @tc.expected: step3. the property value meet expectations.
     */
    ButtonModelStatic::SetLabel(frameNode, BUTTON_LABEL);
    EXPECT_EQ(layoutProperty->GetLabelValue(), BUTTON_LABEL);
}

/**
 * @tc.name: ButtonStaticTestNg005
 * @tc.desc: test button BackgroundColor.
 * @tc.type: FUNC
 */
HWTEST_F(ButtonStaticTestNg, ButtonStaticTestNg005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create button frameNode.
     */
    auto node = ButtonModelStatic::CreateFrameNode(ElementRegister::GetInstance()->MakeUniqueId());
    ASSERT_NE(node, nullptr);
    EXPECT_EQ(node->GetTag(), V2::BUTTON_ETS_TAG);
    auto frameNode = AceType::RawPtr(node);
    ASSERT_NE(frameNode, nullptr);
    /**
     * @tc.steps: step2. create button layoutProperty.
     */
    auto layoutProperty = frameNode->GetLayoutProperty<ButtonLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    /**
     * @tc.steps: step3. test BackgroundColor.
     * @tc.expected: step3. the property value meet expectations.
     */
    ButtonModelStatic::BackgroundColor(frameNode, Color::RED, true);
    auto renderContext = frameNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    EXPECT_EQ(renderContext->GetBackgroundColor(), Color::RED);
}

/**
 * @tc.name: ButtonStaticTestNg006
 * @tc.desc: test button SetBorderRadius.
 * @tc.type: FUNC
 */
HWTEST_F(ButtonStaticTestNg, ButtonStaticTestNg006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create button frameNode.
     */
    auto node = ButtonModelStatic::CreateFrameNode(ElementRegister::GetInstance()->MakeUniqueId());
    ASSERT_NE(node, nullptr);
    EXPECT_EQ(node->GetTag(), V2::BUTTON_ETS_TAG);
    auto frameNode = AceType::RawPtr(node);
    ASSERT_NE(frameNode, nullptr);
    /**
     * @tc.steps: step2. create button layoutProperty.
     */
    auto layoutProperty = frameNode->GetLayoutProperty<ButtonLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    /**
     * @tc.steps: step3. test SetBorderRadius.
     * @tc.expected: step3. the property value meet expectations.
     */
    std::optional<Dimension> borderRadius = std::make_optional(BORDER_RADIUS);
    ButtonModelStatic::SetBorderRadius(frameNode, borderRadius.value());
    EXPECT_EQ(layoutProperty->GetBorderRadius()->radiusTopLeft.value(), BORDER_RADIUS);
    EXPECT_EQ(layoutProperty->GetBorderRadius()->radiusTopRight.value(), BORDER_RADIUS);
    EXPECT_EQ(layoutProperty->GetBorderRadius()->radiusBottomLeft.value(), BORDER_RADIUS);
    EXPECT_EQ(layoutProperty->GetBorderRadius()->radiusBottomRight.value(), BORDER_RADIUS);
}

/**
 * @tc.name: ButtonStaticTestNg007
 * @tc.desc: test button SetType.
 * @tc.type: FUNC
 */
HWTEST_F(ButtonStaticTestNg, ButtonStaticTestNg007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create button frameNode.
     */
    auto node = ButtonModelStatic::CreateFrameNode(ElementRegister::GetInstance()->MakeUniqueId());
    ASSERT_NE(node, nullptr);
    EXPECT_EQ(node->GetTag(), V2::BUTTON_ETS_TAG);
    auto frameNode = AceType::RawPtr(node);
    /**
     * @tc.steps: step2. create button layoutProperty.
     */
    auto layoutProperty = frameNode->GetLayoutProperty<ButtonLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    /**
     * @tc.steps: step3. test SetButtonSize.
     * @tc.expected: step3. the property value meet expectations.
     */
    std::optional<ButtonType> buttonType = std::make_optional(BUTTON_TYPE_CAPSULE_VALUE);
    ButtonModelStatic::SetType(frameNode, static_cast<int32_t>(buttonType.value()));
    EXPECT_EQ(static_cast<int32_t>(layoutProperty->GetTypeValue()), static_cast<int32_t>(BUTTON_TYPE_CAPSULE_VALUE));
}

/**
 * @tc.name: ButtonStaticTestNg008
 * @tc.desc: test button SetFontSize.
 * @tc.type: FUNC
 */
HWTEST_F(ButtonStaticTestNg, ButtonStaticTestNg008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create button frameNode.
     */
    auto node = ButtonModelStatic::CreateFrameNode(ElementRegister::GetInstance()->MakeUniqueId());
    ASSERT_NE(node, nullptr);
    EXPECT_EQ(node->GetTag(), V2::BUTTON_ETS_TAG);
    auto frameNode = AceType::RawPtr(node);
    /**
     * @tc.steps: step2. create button layoutProperty.
     */
    auto layoutProperty = frameNode->GetLayoutProperty<ButtonLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    /**
     * @tc.steps: step3. test SetFontSize.
     * @tc.expected: step3. the property value meet expectations.
     */
    ButtonModelStatic::SetLabel(frameNode, BUTTON_LABEL);
    std::optional<Dimension> fontSize = std::nullopt;
    ButtonModelStatic::SetFontSize(frameNode, fontSize);
    EXPECT_EQ(layoutProperty->GetFontSize(), std::nullopt);
    fontSize = std::make_optional(BUTTON_FONT_SIZE_VALUE);
    ButtonModelStatic::SetFontSize(frameNode, fontSize);
    EXPECT_EQ(layoutProperty->GetFontSizeValue(), BUTTON_FONT_SIZE_VALUE);
}

/**
 * @tc.name: ButtonStaticTestNg009
 * @tc.desc: test button SetFontWeight.
 * @tc.type: FUNC
 */
HWTEST_F(ButtonStaticTestNg, ButtonStaticTestNg009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create button frameNode.
     */
    auto node = ButtonModelStatic::CreateFrameNode(ElementRegister::GetInstance()->MakeUniqueId());
    ASSERT_NE(node, nullptr);
    EXPECT_EQ(node->GetTag(), V2::BUTTON_ETS_TAG);
    auto frameNode = AceType::RawPtr(node);
    /**
     * @tc.steps: step2. create button layoutProperty.
     */
    auto layoutProperty = frameNode->GetLayoutProperty<ButtonLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    /**
     * @tc.steps: step3. test SetFontWeight.
     * @tc.expected: step3. the property value meet expectations.
     */
    ButtonModelStatic::SetLabel(frameNode, BUTTON_LABEL);
    std::optional<Ace::FontWeight> fontWeight = std::nullopt;
    ButtonModelStatic::SetFontWeight(frameNode, fontWeight);
    EXPECT_EQ(layoutProperty->GetFontWeight(), std::nullopt);
    fontWeight = std::make_optional(BUTTON_BOLD_FONT_WEIGHT_VALUE);
    ButtonModelStatic::SetFontWeight(frameNode, fontWeight);
    EXPECT_EQ(layoutProperty->GetFontWeightValue(), BUTTON_BOLD_FONT_WEIGHT_VALUE);
}

/**
 * @tc.name: ButtonStaticTestNg010
 * @tc.desc: test button SetFontStyle.
 * @tc.type: FUNC
 */
HWTEST_F(ButtonStaticTestNg, ButtonStaticTestNg010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create button frameNode.
     */
    auto node = ButtonModelStatic::CreateFrameNode(ElementRegister::GetInstance()->MakeUniqueId());
    ASSERT_NE(node, nullptr);
    EXPECT_EQ(node->GetTag(), V2::BUTTON_ETS_TAG);
    auto frameNode = AceType::RawPtr(node);
    /**
     * @tc.steps: step2. create button layoutProperty.
     */
    auto layoutProperty = frameNode->GetLayoutProperty<ButtonLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    /**
     * @tc.steps: step3. test SetFontStyle.
     * @tc.expected: step3. the property value meet expectations.
     */
    ButtonModelStatic::SetLabel(frameNode, BUTTON_LABEL);
    std::optional<Ace::FontStyle> fontStyleValue = std::nullopt;
    ButtonModelStatic::SetFontStyle(frameNode, fontStyleValue);
    EXPECT_EQ(layoutProperty->GetFontStyle(), std::nullopt);
    fontStyleValue = std::make_optional(BUTTON_ITALIC_FONT_STYLE_VALUE);
    ButtonModelStatic::SetFontStyle(frameNode, fontStyleValue);
    EXPECT_EQ(layoutProperty->GetFontStyleValue(), BUTTON_ITALIC_FONT_STYLE_VALUE);
}

/**
 * @tc.name: ButtonStaticTestNg011
 * @tc.desc: test button SetFontFamily.
 * @tc.type: FUNC
 */
HWTEST_F(ButtonStaticTestNg, ButtonStaticTestNg011, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create button frameNode.
     */
    auto node = ButtonModelStatic::CreateFrameNode(ElementRegister::GetInstance()->MakeUniqueId());
    ASSERT_NE(node, nullptr);
    EXPECT_EQ(node->GetTag(), V2::BUTTON_ETS_TAG);
    auto frameNode = AceType::RawPtr(node);
    /**
     * @tc.steps: step2. create button layoutProperty.
     */
    auto layoutProperty = frameNode->GetLayoutProperty<ButtonLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    /**
     * @tc.steps: step3. test SetFontFamily.
     * @tc.expected: step3. the property value meet expectations.
     */
    ButtonModelStatic::SetLabel(frameNode, BUTTON_LABEL);
    std::optional<std::vector<std::string>> fontFamilyValue = std::nullopt;
    ButtonModelStatic::SetFontFamily(frameNode, fontFamilyValue);
    EXPECT_EQ(layoutProperty->GetFontStyle(), std::nullopt);
    fontFamilyValue = std::make_optional(FONT_FAMILY_VALUE);
    ButtonModelStatic::SetFontFamily(frameNode, fontFamilyValue);
    EXPECT_EQ(layoutProperty->GetFontFamily(), FONT_FAMILY_VALUE);
}

/**
 * @tc.name: ButtonStaticTestNg012
 * @tc.desc: test button SetFontColor.
 * @tc.type: FUNC
 */
HWTEST_F(ButtonStaticTestNg, ButtonStaticTestNg012, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create button frameNode.
     */
    auto node = ButtonModelStatic::CreateFrameNode(ElementRegister::GetInstance()->MakeUniqueId());
    ASSERT_NE(node, nullptr);
    EXPECT_EQ(node->GetTag(), V2::BUTTON_ETS_TAG);
    auto frameNode = AceType::RawPtr(node);
    /**
     * @tc.steps: step2. create button layoutProperty.
     */
    auto layoutProperty = frameNode->GetLayoutProperty<ButtonLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    /**
     * @tc.steps: step3. test SetFontStyle.
     * @tc.expected: step3. the property value meet expectations.
     */
    ButtonModelStatic::SetLabel(frameNode, BUTTON_LABEL);
    std::optional<Color> fontColorValue = std::nullopt;
    ButtonModelStatic::SetFontColor(frameNode, fontColorValue);
    EXPECT_EQ(layoutProperty->GetFontColor(), std::nullopt);
    fontColorValue = std::make_optional(BUTTON_TEXT_COLOR_VALUE);
    ButtonModelStatic::SetFontColor(frameNode, fontColorValue);
    EXPECT_EQ(layoutProperty->GetFontColorValue(), BUTTON_TEXT_COLOR_VALUE);
}

/**
 * @tc.name: ButtonStaticTestNg013
 * @tc.desc: test button SetStateEffect.
 * @tc.type: FUNC
 */
HWTEST_F(ButtonStaticTestNg, ButtonStaticTestNg013, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create button frameNode.
     */
    auto node = ButtonModelStatic::CreateFrameNode(ElementRegister::GetInstance()->MakeUniqueId());
    ASSERT_NE(node, nullptr);
    EXPECT_EQ(node->GetTag(), V2::BUTTON_ETS_TAG);
    auto frameNode = AceType::RawPtr(node);
    /**
     * @tc.steps: step2. create button layoutProperty.
     */
    auto layoutProperty = frameNode->GetLayoutProperty<ButtonLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    /**
     * @tc.steps: step3. test SetStateEffect.
     * @tc.expected: step3. the property value meet expectations.
     */
    std::optional<bool> stateEffectValue = true;
    auto buttonEventHub = frameNode->GetEventHub<ButtonEventHub>();
    ButtonModelStatic::SetStateEffect(frameNode, stateEffectValue);
    EXPECT_EQ(buttonEventHub->GetStateEffect(), true);
}

/**
 * @tc.name: ButtonStaticTestNg014
 * @tc.desc: test button SetLabelStyle.
 * @tc.type: FUNC
 */
HWTEST_F(ButtonStaticTestNg, ButtonStaticTestNg014, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create button frameNode.
     */
    auto node = ButtonModelStatic::CreateFrameNode(ElementRegister::GetInstance()->MakeUniqueId());
    ASSERT_NE(node, nullptr);
    EXPECT_EQ(node->GetTag(), V2::BUTTON_ETS_TAG);
    auto frameNode = AceType::RawPtr(node);
    /**
     * @tc.steps: step2. create button layoutProperty.
     */
    auto layoutProperty = frameNode->GetLayoutProperty<ButtonLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    /**
     * @tc.steps: step3. create ButtonParameters and set value.
     */
    ButtonModelStatic::SetLabel(frameNode, BUTTON_LABEL);
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
    ButtonModelStatic::SetLabelStyle(frameNode, buttonParameters);
    /**
     * @tc.steps: step4. ButtonModelNG setLabelStyle.
     * @tc.expected: step4. Button properties are set successfully.
     */
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
 * @tc.name: ButtonStaticTestNg015
 * @tc.desc: test button SetSize.
 * @tc.type: FUNC
 */
HWTEST_F(ButtonStaticTestNg, ButtonStaticTestNg015, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create button frameNode.
     */
    auto node = ButtonModelStatic::CreateFrameNode(ElementRegister::GetInstance()->MakeUniqueId());
    ASSERT_NE(node, nullptr);
    EXPECT_EQ(node->GetTag(), V2::BUTTON_ETS_TAG);
    auto frameNode = AceType::RawPtr(node);
    /**
     * @tc.steps: step2. create button layoutProperty.
     */
    auto layoutProperty = frameNode->GetLayoutProperty<ButtonLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    /**
     * @tc.steps: step3. test SetSize.
     * @tc.expected: step3. the property value meet expectations.
     */
    std::optional<Dimension> sizeWidth = std::nullopt;
    std::optional<Dimension> sizeHeight = std::nullopt;
    ButtonModelStatic::SetSize(frameNode, sizeWidth, sizeHeight);
    EXPECT_EQ(layoutProperty->GetLayoutConstraint()->selfIdealSize.Width(), std::nullopt);
    EXPECT_EQ(layoutProperty->GetLayoutConstraint()->selfIdealSize.Height(), std::nullopt);
    sizeWidth = std::optional<Dimension>(Dimension(BUTTON_SIZE, DimensionUnit::VP));
    sizeHeight = std::optional<Dimension>(Dimension(BUTTON_SIZE, DimensionUnit::VP));
    ButtonModelStatic::SetSize(frameNode, sizeWidth, sizeHeight);
    if (layoutProperty->GetLayoutConstraint().has_value()) {
        if (layoutProperty->GetLayoutConstraint()->selfIdealSize.Width().has_value()) {
            EXPECT_EQ(layoutProperty->GetLayoutConstraint()->selfIdealSize.Width().value(), BUTTON_SIZE);
        }
        if (layoutProperty->GetLayoutConstraint()->selfIdealSize.Height().has_value()) {
            EXPECT_EQ(layoutProperty->GetLayoutConstraint()->selfIdealSize.Height().value(), BUTTON_SIZE);
        }
    }
}

/**
 * @tc.name: ButtonStaticTestNg016
 * @tc.desc: test button SetMinFontScale.
 * @tc.type: FUNC
 */
HWTEST_F(ButtonStaticTestNg, ButtonStaticTestNg016, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create button frameNode.
     */
    auto node = ButtonModelStatic::CreateFrameNode(ElementRegister::GetInstance()->MakeUniqueId());
    ASSERT_NE(node, nullptr);
    EXPECT_EQ(node->GetTag(), V2::BUTTON_ETS_TAG);
    auto frameNode = AceType::RawPtr(node);
    /**
     * @tc.steps: step2. create button layoutProperty.
     */
    auto layoutProperty = frameNode->GetLayoutProperty<ButtonLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    /**
     * @tc.steps: step3. test SetMinFontScale.
     * @tc.expected: step3. the property value meet expectations.
     */
    ButtonModelStatic::SetLabel(frameNode, BUTTON_LABEL);
    std::optional<float> minFontScaleValue = std::nullopt;
    ButtonModelStatic::SetMinFontScale(frameNode, minFontScaleValue);
    EXPECT_EQ(layoutProperty->GetMinFontScale(), std::nullopt);
    minFontScaleValue = std::make_optional(MIN_SCALE_VALUE);
    ButtonModelStatic::SetMinFontScale(frameNode, minFontScaleValue);
    EXPECT_EQ(layoutProperty->GetMinFontScaleValue(), MIN_SCALE_VALUE);
}

/**
 * @tc.name: ButtonStaticTestNg017
 * @tc.desc: test button SetMaxFontScale.
 * @tc.type: FUNC
 */
HWTEST_F(ButtonStaticTestNg, ButtonStaticTestNg017, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create button frameNode.
     */
    auto node = ButtonModelStatic::CreateFrameNode(ElementRegister::GetInstance()->MakeUniqueId());
    ASSERT_NE(node, nullptr);
    EXPECT_EQ(node->GetTag(), V2::BUTTON_ETS_TAG);
    auto frameNode = AceType::RawPtr(node);
    /**
     * @tc.steps: step2. create button layoutProperty.
     */
    auto layoutProperty = frameNode->GetLayoutProperty<ButtonLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    /**
     * @tc.steps: step3. test SetMaxFontScale.
     * @tc.expected: step3. the property value meet expectations.
     */
    ButtonModelStatic::SetLabel(frameNode, BUTTON_LABEL);
    std::optional<float> maxFontScaleValue = std::nullopt;
    ButtonModelStatic::SetMaxFontScale(frameNode, maxFontScaleValue);
    EXPECT_EQ(layoutProperty->GetMaxFontScale(), std::nullopt);
    maxFontScaleValue = std::make_optional(MAX_SCALE_VALUE);
    ButtonModelStatic::SetMaxFontScale(frameNode, maxFontScaleValue);
    EXPECT_EQ(layoutProperty->GetMaxFontScaleValue(), MAX_SCALE_VALUE);
}
} // namespace OHOS::Ace::NG