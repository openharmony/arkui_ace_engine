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
constexpr float BUTTON_WIDTH = 200.0f;
constexpr float BUTTON_HEIGHT = 100.0f;
constexpr float TEXT_WIDTH = 100.0f;
constexpr float TEXT_HEIGHT = 50.0f;
constexpr float FULL_SCREEN_WIDTH = 720.0f;
constexpr float FULL_SCREEN_HEIGHT = 1136.0f;
constexpr float BUTTON_ONLY_HAS_WIDTH_VALUE = 100.0f;
constexpr int BIG_INT = 100000000;
constexpr int NEGATIVE_BIG_INT = -100000000;
const SizeF BUTTON_SIZE(BUTTON_WIDTH, BUTTON_HEIGHT);
const SizeF TEXT_SIZE(TEXT_WIDTH, TEXT_HEIGHT);
const std::string CREATE_VALUE = "Hello World";
const std::vector<std::string> FONT_FAMILY_VALUE = { "cursive" };
const SizeF CONTAINER_SIZE(FULL_SCREEN_WIDTH, FULL_SCREEN_HEIGHT);
const SizeF BUTTON_ONLY_HAS_WIDTH_SIZE(BUTTON_ONLY_HAS_WIDTH_VALUE, BUTTON_ONLY_HAS_WIDTH_VALUE);
const Dimension DEFAULT_HEIGTH = 40.0_vp;

struct CreateWithPara createWithPara = { std::make_optional(true), std::make_optional(CREATE_VALUE),
    std::make_optional(true), std::make_optional(ButtonType::CAPSULE), std::make_optional(true), std::nullopt,
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

class ButtonContentModifierTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    static void FontWeightTest(RefPtr<ButtonLayoutProperty> buttonLayoutProperty, RefPtr<ButtonPattern> buttonPattern,
        RefPtr<TextLayoutProperty> textLayoutProp);

protected:
    RefPtr<FrameNode> CreateLabelButtonParagraph(const std::string& createValue, const TestProperty& testProperty);
    RefPtr<FrameNode> CreateChildButtonParagraph(const std::string& createValue, const TestProperty& testProperty);
    RefPtr<FrameNode> CreateLabelButtonParagraphForLableStyle(
        const std::string& createValue, const LableStyleProperty& lableStyleProperty);
};

void ButtonContentModifierTestNg::SetUpTestCase()
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

void ButtonContentModifierTestNg::TearDownTestCase()
{
    MockPipelineContext::TearDown();
}

void ButtonContentModifierTestNg::FontWeightTest(RefPtr<ButtonLayoutProperty> buttonLayoutProperty,
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

RefPtr<FrameNode> ButtonContentModifierTestNg::CreateLabelButtonParagraph(
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

RefPtr<FrameNode> ButtonContentModifierTestNg::CreateChildButtonParagraph(
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

RefPtr<FrameNode> ButtonContentModifierTestNg::CreateLabelButtonParagraphForLableStyle(
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
 * @tc.name: ButtonContentModifierTest001
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(ButtonContentModifierTestNg, ButtonContentModifierTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init Button node
     */
    TestProperty testProperty;
    auto frameNode = CreateLabelButtonParagraph(CREATE_VALUE, testProperty);
    auto gesture = frameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. Set buttonConfiguration
     */
    auto buttonPattern = frameNode->GetPattern<ButtonPattern>();
    ASSERT_NE(buttonPattern, nullptr);
    auto eventHub = frameNode->GetEventHub<EventHub>();
    eventHub->SetEnabled(false);
    buttonPattern->HandlePressedStyle();

    /**
     * @tc.steps: step3. make builderFunc
     */
    auto node = [](ButtonConfiguration config) -> RefPtr<FrameNode> {
            EXPECT_EQ(CREATE_VALUE, config.label_);
            EXPECT_EQ(true, config.pressed_);
            EXPECT_EQ(false, config.enabled_);
            return nullptr;
        };

    /**
     * @tc.steps: step4. Set parameters to pattern builderFunc
     */
    buttonPattern->SetBuilderFunc(node);
    buttonPattern->BuildContentModifierNode();
}

/**
 * @tc.name: ButtonContentModifierTest002
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(ButtonContentModifierTestNg, ButtonContentModifierTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init Button node
     */
    TestProperty testProperty;
    auto frameNode = CreateLabelButtonParagraph(CREATE_VALUE, testProperty);
    auto gesture = frameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. Set buttonConfiguration
     */
    auto buttonPattern = frameNode->GetPattern<ButtonPattern>();
    ASSERT_NE(buttonPattern, nullptr);
    auto eventHub = frameNode->GetEventHub<EventHub>();
    eventHub->SetEnabled(1);
    buttonPattern->HandlePressedStyle();

    /**
     * @tc.steps: step3. make builderFunc
     */
    auto node = [](ButtonConfiguration config) -> RefPtr<FrameNode> {
            EXPECT_EQ(CREATE_VALUE, config.label_);
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
 * @tc.name: ButtonContentModifierTest003
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(ButtonContentModifierTestNg, ButtonContentModifierTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init Button node
     */
    TestProperty testProperty;
    auto frameNode = CreateLabelButtonParagraph(CREATE_VALUE, testProperty);
    auto gesture = frameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. Set buttonConfiguration
     */
    auto buttonPattern = frameNode->GetPattern<ButtonPattern>();
    ASSERT_NE(buttonPattern, nullptr);
    auto eventHub = frameNode->GetEventHub<EventHub>();
    eventHub->SetEnabled(0);
    buttonPattern->HandlePressedStyle();

    /**
     * @tc.steps: step3. make builderFunc
     */
    auto node = [](ButtonConfiguration config) -> RefPtr<FrameNode> {
            EXPECT_EQ(CREATE_VALUE, config.label_);
            EXPECT_EQ(true, config.pressed_);
            EXPECT_EQ(false, config.enabled_);
            return nullptr;
        };

    /**
     * @tc.steps: step4. Set parameters to pattern builderFunc
     */
    buttonPattern->SetBuilderFunc(node);
    buttonPattern->BuildContentModifierNode();
}

/**
 * @tc.name: ButtonContentModifierTest004
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(ButtonContentModifierTestNg, ButtonContentModifierTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init Button node
     */
    TestProperty testProperty;
    auto frameNode = CreateLabelButtonParagraph(CREATE_VALUE, testProperty);
    auto gesture = frameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. Set buttonConfiguration
     */
    auto buttonPattern = frameNode->GetPattern<ButtonPattern>();
    ASSERT_NE(buttonPattern, nullptr);
    auto eventHub = frameNode->GetEventHub<EventHub>();
    eventHub->SetEnabled(-1);
    buttonPattern->HandlePressedStyle();

    /**
     * @tc.steps: step3. make builderFunc
     */
    auto node = [](ButtonConfiguration config) -> RefPtr<FrameNode> {
            EXPECT_EQ(CREATE_VALUE, config.label_);
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
 * @tc.name: ButtonContentModifierTest005
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(ButtonContentModifierTestNg, ButtonContentModifierTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init Button node
     */
    TestProperty testProperty;
    auto frameNode = CreateLabelButtonParagraph(CREATE_VALUE, testProperty);
    auto gesture = frameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. Set buttonConfiguration
     */
    auto buttonPattern = frameNode->GetPattern<ButtonPattern>();
    ASSERT_NE(buttonPattern, nullptr);
    auto eventHub = frameNode->GetEventHub<EventHub>();
    eventHub->SetEnabled(BIG_INT);
    buttonPattern->HandlePressedStyle();

    /**
     * @tc.steps: step3. make builderFunc
     */
    auto node = [](ButtonConfiguration config) -> RefPtr<FrameNode> {
            EXPECT_EQ(CREATE_VALUE, config.label_);
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
 * @tc.name: ButtonContentModifierTest006
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(ButtonContentModifierTestNg, ButtonContentModifierTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init Button node
     */
    TestProperty testProperty;
    auto frameNode = CreateLabelButtonParagraph(CREATE_VALUE, testProperty);
    auto gesture = frameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. Set buttonConfiguration
     */
    auto buttonPattern = frameNode->GetPattern<ButtonPattern>();
    ASSERT_NE(buttonPattern, nullptr);
    auto eventHub = frameNode->GetEventHub<EventHub>();
    eventHub->SetEnabled(NEGATIVE_BIG_INT);
    buttonPattern->HandlePressedStyle();

    /**
     * @tc.steps: step3. make builderFunc
     */
    auto node = [](ButtonConfiguration config) -> RefPtr<FrameNode> {
            EXPECT_EQ(CREATE_VALUE, config.label_);
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
 * @tc.name: ButtonContentModifierTest007
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(ButtonContentModifierTestNg, ButtonContentModifierTest007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init Button node
     */
    TestProperty testProperty;
    auto frameNode = CreateLabelButtonParagraph(CREATE_VALUE, testProperty);
    auto gesture = frameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. Set buttonConfiguration
     */
    auto buttonPattern = frameNode->GetPattern<ButtonPattern>();
    ASSERT_NE(buttonPattern, nullptr);
    auto eventHub = frameNode->GetEventHub<EventHub>();
    eventHub->SetEnabled(true);
    buttonPattern->HandleNormalStyle();

    /**
     * @tc.steps: step3. make builderFunc
     */
    auto node = [](ButtonConfiguration config) -> RefPtr<FrameNode> {
            EXPECT_EQ(CREATE_VALUE, config.label_);
            EXPECT_EQ(false, config.pressed_);
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
 * @tc.name: ButtonContentModifierTest008
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(ButtonContentModifierTestNg, ButtonContentModifierTest008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init Button node
     */
    TestProperty testProperty;
    auto frameNode = CreateLabelButtonParagraph(CREATE_VALUE, testProperty);
    auto gesture = frameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. Set buttonConfiguration
     */
    auto buttonPattern = frameNode->GetPattern<ButtonPattern>();
    ASSERT_NE(buttonPattern, nullptr);
    auto eventHub = frameNode->GetEventHub<EventHub>();
    eventHub->SetEnabled(false);
    buttonPattern->HandleNormalStyle();

    /**
     * @tc.steps: step3. make builderFunc
     */
    auto node = [](ButtonConfiguration config) -> RefPtr<FrameNode> {
            EXPECT_EQ(CREATE_VALUE, config.label_);
            EXPECT_EQ(false, config.pressed_);
            EXPECT_EQ(false, config.enabled_);
            return nullptr;
        };

    /**
     * @tc.steps: step4. Set parameters to pattern builderFunc
     */
    buttonPattern->SetBuilderFunc(node);
    buttonPattern->BuildContentModifierNode();
}

/**
 * @tc.name: ButtonContentModifierTest009
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(ButtonContentModifierTestNg, ButtonContentModifierTest009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init Button node
     */
    TestProperty testProperty;
    auto frameNode = CreateLabelButtonParagraph(CREATE_VALUE, testProperty);
    auto gesture = frameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. Set buttonConfiguration
     */
    auto buttonPattern = frameNode->GetPattern<ButtonPattern>();
    ASSERT_NE(buttonPattern, nullptr);
    auto eventHub = frameNode->GetEventHub<EventHub>();
    eventHub->SetEnabled(1);
    buttonPattern->HandleNormalStyle();

    /**
     * @tc.steps: step3. make builderFunc
     */
    auto node = [](ButtonConfiguration config) -> RefPtr<FrameNode> {
            EXPECT_EQ(CREATE_VALUE, config.label_);
            EXPECT_EQ(false, config.pressed_);
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
 * @tc.name: ButtonContentModifierTest010
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(ButtonContentModifierTestNg, ButtonContentModifierTest010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init Button node
     */
    TestProperty testProperty;
    auto frameNode = CreateLabelButtonParagraph(CREATE_VALUE, testProperty);
    auto gesture = frameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. Set buttonConfiguration
     */
    auto buttonPattern = frameNode->GetPattern<ButtonPattern>();
    ASSERT_NE(buttonPattern, nullptr);
    auto eventHub = frameNode->GetEventHub<EventHub>();
    eventHub->SetEnabled(0);
    buttonPattern->HandleNormalStyle();

    /**
     * @tc.steps: step3. make builderFunc
     */
    auto node = [](ButtonConfiguration config) -> RefPtr<FrameNode> {
            EXPECT_EQ(CREATE_VALUE, config.label_);
            EXPECT_EQ(false, config.pressed_);
            EXPECT_EQ(false, config.enabled_);
            return nullptr;
        };

    /**
     * @tc.steps: step4. Set parameters to pattern builderFunc
     */
    buttonPattern->SetBuilderFunc(node);
    buttonPattern->BuildContentModifierNode();
}

/**
 * @tc.name: ButtonContentModifierTest011
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(ButtonContentModifierTestNg, ButtonContentModifierTest011, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init Button node
     */
    TestProperty testProperty;
    auto frameNode = CreateLabelButtonParagraph(CREATE_VALUE, testProperty);
    auto gesture = frameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. Set buttonConfiguration
     */
    auto buttonPattern = frameNode->GetPattern<ButtonPattern>();
    ASSERT_NE(buttonPattern, nullptr);
    auto eventHub = frameNode->GetEventHub<EventHub>();
    eventHub->SetEnabled(-1);
    buttonPattern->HandleNormalStyle();

    /**
     * @tc.steps: step3. make builderFunc
     */
    auto node = [](ButtonConfiguration config) -> RefPtr<FrameNode> {
            EXPECT_EQ(CREATE_VALUE, config.label_);
            EXPECT_EQ(false, config.pressed_);
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
 * @tc.name: ButtonContentModifierTest012
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(ButtonContentModifierTestNg, ButtonContentModifierTest012, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init Button node
     */
    TestProperty testProperty;
    auto frameNode = CreateLabelButtonParagraph(CREATE_VALUE, testProperty);
    auto gesture = frameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. Set buttonConfiguration
     */
    auto buttonPattern = frameNode->GetPattern<ButtonPattern>();
    ASSERT_NE(buttonPattern, nullptr);
    auto eventHub = frameNode->GetEventHub<EventHub>();
    eventHub->SetEnabled(BIG_INT);
    buttonPattern->HandleNormalStyle();

    /**
     * @tc.steps: step3. make builderFunc
     */
    auto node = [](ButtonConfiguration config) -> RefPtr<FrameNode> {
            EXPECT_EQ(CREATE_VALUE, config.label_);
            EXPECT_EQ(false, config.pressed_);
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
 * @tc.name: ButtonContentModifierTest013
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(ButtonContentModifierTestNg, ButtonContentModifierTest013, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init Button node
     */
    TestProperty testProperty;
    auto frameNode = CreateLabelButtonParagraph(CREATE_VALUE, testProperty);
    auto gesture = frameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. Set buttonConfiguration
     */
    auto buttonPattern = frameNode->GetPattern<ButtonPattern>();
    ASSERT_NE(buttonPattern, nullptr);
    auto eventHub = frameNode->GetEventHub<EventHub>();
    eventHub->SetEnabled(NEGATIVE_BIG_INT);
    buttonPattern->HandleNormalStyle();

    /**
     * @tc.steps: step3. make builderFunc
     */
    auto node = [](ButtonConfiguration config) -> RefPtr<FrameNode> {
            EXPECT_EQ(CREATE_VALUE, config.label_);
            EXPECT_EQ(false, config.pressed_);
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
 * @tc.name: ButtonContentModifierTest014
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(ButtonContentModifierTestNg, ButtonContentModifierTest014, TestSize.Level1)
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
    eventHub->SetEnabled(false);
    buttonPattern->HandlePressedStyle();

    /**
     * @tc.steps: step3. make builderFunc
     */
    auto node = [buttonLabel](ButtonConfiguration config) -> RefPtr<FrameNode> {
            EXPECT_EQ(buttonLabel, config.label_);
            EXPECT_EQ(true, config.pressed_);
            EXPECT_EQ(false, config.enabled_);
            return nullptr;
        };

    /**
     * @tc.steps: step4. Set parameters to pattern builderFunc
     */
    buttonPattern->SetBuilderFunc(node);
    buttonPattern->BuildContentModifierNode();
}

/**
 * @tc.name: ButtonContentModifierTest015
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(ButtonContentModifierTestNg, ButtonContentModifierTest015, TestSize.Level1)
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
    eventHub->SetEnabled(1);
    buttonPattern->HandlePressedStyle();

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
 * @tc.name: ButtonContentModifierTest016
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(ButtonContentModifierTestNg, ButtonContentModifierTest016, TestSize.Level1)
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
    eventHub->SetEnabled(0);
    buttonPattern->HandlePressedStyle();

    /**
     * @tc.steps: step3. make builderFunc
     */
    auto node = [buttonLabel](ButtonConfiguration config) -> RefPtr<FrameNode> {
            EXPECT_EQ(buttonLabel, config.label_);
            EXPECT_EQ(true, config.pressed_);
            EXPECT_EQ(false, config.enabled_);
            return nullptr;
        };

    /**
     * @tc.steps: step4. Set parameters to pattern builderFunc
     */
    buttonPattern->SetBuilderFunc(node);
    buttonPattern->BuildContentModifierNode();
}

/**
 * @tc.name: ButtonContentModifierTest017
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(ButtonContentModifierTestNg, ButtonContentModifierTest017, TestSize.Level1)
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
    eventHub->SetEnabled(-1);
    buttonPattern->HandlePressedStyle();

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
 * @tc.name: ButtonContentModifierTest018
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(ButtonContentModifierTestNg, ButtonContentModifierTest018, TestSize.Level1)
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
    eventHub->SetEnabled(BIG_INT);
    buttonPattern->HandlePressedStyle();

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
 * @tc.name: ButtonContentModifierTest019
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(ButtonContentModifierTestNg, ButtonContentModifierTest019, TestSize.Level1)
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
    eventHub->SetEnabled(NEGATIVE_BIG_INT);
    buttonPattern->HandlePressedStyle();

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
 * @tc.name: ButtonContentModifierTest020
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(ButtonContentModifierTestNg, ButtonContentModifierTest020, TestSize.Level1)
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
    buttonPattern->HandleNormalStyle();

    /**
     * @tc.steps: step3. make builderFunc
     */
    auto node = [buttonLabel](ButtonConfiguration config) -> RefPtr<FrameNode> {
            EXPECT_EQ(buttonLabel, config.label_);
            EXPECT_EQ(false, config.pressed_);
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
 * @tc.name: ButtonContentModifierTest021
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(ButtonContentModifierTestNg, ButtonContentModifierTest021, TestSize.Level1)
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
    eventHub->SetEnabled(false);
    buttonPattern->HandleNormalStyle();

    /**
     * @tc.steps: step3. make builderFunc
     */
    auto node = [buttonLabel](ButtonConfiguration config) -> RefPtr<FrameNode> {
            EXPECT_EQ(buttonLabel, config.label_);
            EXPECT_EQ(false, config.pressed_);
            EXPECT_EQ(false, config.enabled_);
            return nullptr;
        };

    /**
     * @tc.steps: step4. Set parameters to pattern builderFunc
     */
    buttonPattern->SetBuilderFunc(node);
    buttonPattern->BuildContentModifierNode();
}

/**
 * @tc.name: ButtonContentModifierTest022
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(ButtonContentModifierTestNg, ButtonContentModifierTest022, TestSize.Level1)
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
    eventHub->SetEnabled(1);
    buttonPattern->HandleNormalStyle();

    /**
     * @tc.steps: step3. make builderFunc
     */
    auto node = [buttonLabel](ButtonConfiguration config) -> RefPtr<FrameNode> {
            EXPECT_EQ(buttonLabel, config.label_);
            EXPECT_EQ(false, config.pressed_);
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
 * @tc.name: ButtonContentModifierTest023
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(ButtonContentModifierTestNg, ButtonContentModifierTest023, TestSize.Level1)
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
    eventHub->SetEnabled(0);
    buttonPattern->HandleNormalStyle();

    /**
     * @tc.steps: step3. make builderFunc
     */
    auto node = [buttonLabel](ButtonConfiguration config) -> RefPtr<FrameNode> {
            EXPECT_EQ(buttonLabel, config.label_);
            EXPECT_EQ(false, config.pressed_);
            EXPECT_EQ(false, config.enabled_);
            return nullptr;
        };

    /**
     * @tc.steps: step4. Set parameters to pattern builderFunc
     */
    buttonPattern->SetBuilderFunc(node);
    buttonPattern->BuildContentModifierNode();
}

/**
 * @tc.name: ButtonContentModifierTest024
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(ButtonContentModifierTestNg, ButtonContentModifierTest024, TestSize.Level1)
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
    eventHub->SetEnabled(-1);
    buttonPattern->HandleNormalStyle();

    /**
     * @tc.steps: step3. make builderFunc
     */
    auto node = [buttonLabel](ButtonConfiguration config) -> RefPtr<FrameNode> {
            EXPECT_EQ(buttonLabel, config.label_);
            EXPECT_EQ(false, config.pressed_);
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
 * @tc.name: ButtonContentModifierTest025
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(ButtonContentModifierTestNg, ButtonContentModifierTest025, TestSize.Level1)
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
    eventHub->SetEnabled(BIG_INT);
    buttonPattern->HandleNormalStyle();

    /**
     * @tc.steps: step3. make builderFunc
     */
    auto node = [buttonLabel](ButtonConfiguration config) -> RefPtr<FrameNode> {
            EXPECT_EQ(buttonLabel, config.label_);
            EXPECT_EQ(false, config.pressed_);
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
 * @tc.name: ButtonContentModifierTest026
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(ButtonContentModifierTestNg, ButtonContentModifierTest026, TestSize.Level1)
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
    eventHub->SetEnabled(NEGATIVE_BIG_INT);
    buttonPattern->HandleNormalStyle();

    /**
     * @tc.steps: step3. make builderFunc
     */
    auto node = [buttonLabel](ButtonConfiguration config) -> RefPtr<FrameNode> {
            EXPECT_EQ(buttonLabel, config.label_);
            EXPECT_EQ(false, config.pressed_);
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
 * @tc.name: ButtonContentModifierTest027
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(ButtonContentModifierTestNg, ButtonContentModifierTest027, TestSize.Level1)
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
    eventHub->SetEnabled(false);
    buttonPattern->HandlePressedStyle();

    /**
     * @tc.steps: step3. make builderFunc
     */
    auto node = [buttonLabel](ButtonConfiguration config) -> RefPtr<FrameNode> {
            EXPECT_EQ(buttonLabel, config.label_);
            EXPECT_EQ(true, config.pressed_);
            EXPECT_EQ(false, config.enabled_);
            return nullptr;
        };

    /**
     * @tc.steps: step4. Set parameters to pattern builderFunc
     */
    buttonPattern->SetBuilderFunc(node);
    buttonPattern->BuildContentModifierNode();
}

/**
 * @tc.name: ButtonContentModifierTest028
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(ButtonContentModifierTestNg, ButtonContentModifierTest028, TestSize.Level1)
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
    eventHub->SetEnabled(1);
    buttonPattern->HandlePressedStyle();

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
 * @tc.name: ButtonContentModifierTest029
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(ButtonContentModifierTestNg, ButtonContentModifierTest029, TestSize.Level1)
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
    eventHub->SetEnabled(0);
    buttonPattern->HandlePressedStyle();

    /**
     * @tc.steps: step3. make builderFunc
     */
    auto node = [buttonLabel](ButtonConfiguration config) -> RefPtr<FrameNode> {
            EXPECT_EQ(buttonLabel, config.label_);
            EXPECT_EQ(true, config.pressed_);
            EXPECT_EQ(false, config.enabled_);
            return nullptr;
        };

    /**
     * @tc.steps: step4. Set parameters to pattern builderFunc
     */
    buttonPattern->SetBuilderFunc(node);
    buttonPattern->BuildContentModifierNode();
}

/**
 * @tc.name: ButtonContentModifierTest030
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(ButtonContentModifierTestNg, ButtonContentModifierTest030, TestSize.Level1)
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
    eventHub->SetEnabled(-1);
    buttonPattern->HandlePressedStyle();

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
 * @tc.name: ButtonContentModifierTest031
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(ButtonContentModifierTestNg, ButtonContentModifierTest031, TestSize.Level1)
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
    eventHub->SetEnabled(BIG_INT);
    buttonPattern->HandlePressedStyle();

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
 * @tc.name: ButtonContentModifierTest032
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(ButtonContentModifierTestNg, ButtonContentModifierTest032, TestSize.Level1)
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
    eventHub->SetEnabled(NEGATIVE_BIG_INT);
    buttonPattern->HandlePressedStyle();

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
 * @tc.name: ButtonContentModifierTest033
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(ButtonContentModifierTestNg, ButtonContentModifierTest033, TestSize.Level1)
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
    buttonPattern->HandleNormalStyle();

    /**
     * @tc.steps: step3. make builderFunc
     */
    auto node = [buttonLabel](ButtonConfiguration config) -> RefPtr<FrameNode> {
            EXPECT_EQ(buttonLabel, config.label_);
            EXPECT_EQ(false, config.pressed_);
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
 * @tc.name: ButtonContentModifierTest034
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(ButtonContentModifierTestNg, ButtonContentModifierTest034, TestSize.Level1)
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
    eventHub->SetEnabled(false);
    buttonPattern->HandleNormalStyle();

    /**
     * @tc.steps: step3. make builderFunc
     */
    auto node = [buttonLabel](ButtonConfiguration config) -> RefPtr<FrameNode> {
            EXPECT_EQ(buttonLabel, config.label_);
            EXPECT_EQ(false, config.pressed_);
            EXPECT_EQ(false, config.enabled_);
            return nullptr;
        };

    /**
     * @tc.steps: step4. Set parameters to pattern builderFunc
     */
    buttonPattern->SetBuilderFunc(node);
    buttonPattern->BuildContentModifierNode();
}

/**
 * @tc.name: ButtonContentModifierTest035
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(ButtonContentModifierTestNg, ButtonContentModifierTest035, TestSize.Level1)
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
    eventHub->SetEnabled(1);
    buttonPattern->HandleNormalStyle();

    /**
     * @tc.steps: step3. make builderFunc
     */
    auto node = [buttonLabel](ButtonConfiguration config) -> RefPtr<FrameNode> {
            EXPECT_EQ(buttonLabel, config.label_);
            EXPECT_EQ(false, config.pressed_);
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
 * @tc.name: ButtonContentModifierTest036
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(ButtonContentModifierTestNg, ButtonContentModifierTest036, TestSize.Level1)
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
    eventHub->SetEnabled(0);
    buttonPattern->HandleNormalStyle();

    /**
     * @tc.steps: step3. make builderFunc
     */
    auto node = [buttonLabel](ButtonConfiguration config) -> RefPtr<FrameNode> {
            EXPECT_EQ(buttonLabel, config.label_);
            EXPECT_EQ(false, config.pressed_);
            EXPECT_EQ(false, config.enabled_);
            return nullptr;
        };

    /**
     * @tc.steps: step4. Set parameters to pattern builderFunc
     */
    buttonPattern->SetBuilderFunc(node);
    buttonPattern->BuildContentModifierNode();
}

/**
 * @tc.name: ButtonContentModifierTest037
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(ButtonContentModifierTestNg, ButtonContentModifierTest037, TestSize.Level1)
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
    eventHub->SetEnabled(-1);
    buttonPattern->HandleNormalStyle();

    /**
     * @tc.steps: step3. make builderFunc
     */
    auto node = [buttonLabel](ButtonConfiguration config) -> RefPtr<FrameNode> {
            EXPECT_EQ(buttonLabel, config.label_);
            EXPECT_EQ(false, config.pressed_);
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
 * @tc.name: ButtonContentModifierTest038
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(ButtonContentModifierTestNg, ButtonContentModifierTest038, TestSize.Level1)
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
    eventHub->SetEnabled(BIG_INT);
    buttonPattern->HandleNormalStyle();

    /**
     * @tc.steps: step3. make builderFunc
     */
    auto node = [buttonLabel](ButtonConfiguration config) -> RefPtr<FrameNode> {
            EXPECT_EQ(buttonLabel, config.label_);
            EXPECT_EQ(false, config.pressed_);
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
 * @tc.name: ButtonContentModifierTest039
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(ButtonContentModifierTestNg, ButtonContentModifierTest039, TestSize.Level1)
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
    eventHub->SetEnabled(NEGATIVE_BIG_INT);
    buttonPattern->HandleNormalStyle();

    /**
     * @tc.steps: step3. make builderFunc
     */
    auto node = [buttonLabel](ButtonConfiguration config) -> RefPtr<FrameNode> {
            EXPECT_EQ(buttonLabel, config.label_);
            EXPECT_EQ(false, config.pressed_);
            EXPECT_EQ(true, config.enabled_);
            return nullptr;
        };

    /**
     * @tc.steps: step4. Set parameters to pattern builderFunc
     */
    buttonPattern->SetBuilderFunc(node);
    buttonPattern->BuildContentModifierNode();
}

} // namespace OHOS::Ace::NG