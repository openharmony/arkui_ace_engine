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
#include <cstdint>
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
#include "core/components_ng/layout/layout_wrapper_node.h"
#include "core/components_ng/pattern/button/button_layout_property.h"
#include "core/components_ng/pattern/button/button_model_ng.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/button/toggle_button_pattern.h"
#include "core/components_ng/pattern/root/root_pattern.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/pattern/text/text_styles.h"
#include "core/event/touch_event.h"
#include "core/pipeline_ng/ui_task_scheduler.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr float FULL_SCREEN_WIDTH = 720.0f;
constexpr float FULL_SCREEN_HEIGHT = 1136.0f;
constexpr bool STATE_EFFECT = true;
const std::string CREATE_VALUE = "Hello World";
const std::string BUTTON_VALUE = "Test";
const std::string TEST_RESULT = "result_ok";
const std::string TEST_RESULT_CAPSULE = "capsule";
const std::string TEST_RESULT_DOWNLOAD = "download";
const Dimension BORDER_RADIUS = 5.0_vp;
const SizeF CONTAINER_SIZE(FULL_SCREEN_WIDTH, FULL_SCREEN_HEIGHT);
const Dimension DEFAULT_HEIGTH = 40.0_vp;

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

class ButtonFunctionTestTwoNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    static void CreateLayoutTask(const RefPtr<FrameNode>& frameNode);
    static RefPtr<FrameNode> CreateButton(
        const std::u16string& content, const std::function<void(ButtonModelNG)>& callback);

protected:
    PaddingProperty CreatePadding(float left, float top, float right, float bottom);
    RefPtr<FrameNode> CreateLabelButtonParagraph(const std::string& createValue, const TestProperty& testProperty);
    RefPtr<FrameNode> CreateLabelButtonParagraphByRoundedRect(
        const std::string& createValue, const TestProperty& testProperty);

private:
    void CreateAndCheckTextOverflow(RefPtr<FrameNode> frameNode, bool isCheckTextOverflow);
    void CheckTextMarqueeOption(RefPtr<FrameNode> frameNode, bool isMarqueeStart);
};

RefPtr<FrameNode> ButtonFunctionTestTwoNg::CreateLabelButtonParagraph(
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

RefPtr<FrameNode> ButtonFunctionTestTwoNg::CreateLabelButtonParagraphByRoundedRect(
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

void ButtonFunctionTestTwoNg::SetUpTestCase()
{
    MockPipelineContext::SetUp();
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

void ButtonFunctionTestTwoNg::TearDownTestCase()
{
    MockPipelineContext::TearDown();
}

PaddingProperty ButtonFunctionTestTwoNg::CreatePadding(float left, float top, float right, float bottom)
{
    PaddingProperty padding;
    padding.left = CalcLength(left);
    padding.right = CalcLength(right);
    padding.top = CalcLength(top);
    padding.bottom = CalcLength(bottom);
    return padding;
}

void ButtonFunctionTestTwoNg::CreateAndCheckTextOverflow(RefPtr<FrameNode> frameNode, bool isCheckTextOverflow)
{
    /**
     * @tc.steps: step1. get pattern and update frameNode.
     * @tc.expected: step1. related function is called.
     */
    auto buttonPattern = frameNode->GetPattern<ButtonPattern>();
    ASSERT_NE(buttonPattern, nullptr);
    auto buttonLayoutProperty = frameNode->GetLayoutProperty<ButtonLayoutProperty>();
    ASSERT_NE(buttonLayoutProperty, nullptr);

    /**
     * @tc.steps: step2. updateTextOverflow then execute onModifyDone.
     * @tc.expected: step2. check whether the properties is correct.
     */
    // set touchEventActuator_
    std::function<void(UIState)> touchEvent = [](const UIState& state) {};
    buttonPattern->touchListener_ = touchEvent;
    auto text = AceType::DynamicCast<FrameNode>(frameNode->GetFirstChild());
    ASSERT_NE(text, nullptr);
    auto textLayoutProp = text->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProp, nullptr);

    if (isCheckTextOverflow) {
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
}

void ButtonFunctionTestTwoNg::CheckTextMarqueeOption(RefPtr<FrameNode> frameNode, bool isMarqueeStart)
{
    auto textFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetFirstChild());
    ASSERT_NE(textFrameNode, nullptr);
    auto textLayoutProp = textFrameNode->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProp, nullptr);

    EXPECT_EQ(textLayoutProp->GetTextOverflow(), TextOverflow::MARQUEE);
    EXPECT_EQ(textLayoutProp->GetTextMarqueeFadeout(), true);
    EXPECT_EQ(textLayoutProp->GetTextMarqueeStart(), isMarqueeStart);
    EXPECT_EQ(textLayoutProp->GetTextMarqueeStartPolicy(), MarqueeStartPolicy::DEFAULT);
}

RefPtr<FrameNode> ButtonFunctionTestTwoNg::CreateButton(
    const std::u16string& content, const std::function<void(ButtonModelNG)>& callback)
{
    ButtonModelNG model;
    std::string contentStr(content.begin(), content.end());
    model.Create(contentStr);
    if (callback) {
        callback(model);
    }
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->GetMainElementNode();
    ViewStackProcessor::GetInstance()->PopContainer();
    return AceType::DynamicCast<FrameNode>(element);
}

void ButtonFunctionTestTwoNg::CreateLayoutTask(const RefPtr<FrameNode>& frameNode)
{
    frameNode->SetActive();
    frameNode->SetLayoutDirtyMarked(true);
    frameNode->CreateLayoutTask();
}

/**
 * @tc.name: ButtonFunctionTest020
 * @tc.desc: Test NeedAgingMeasureFunc
 * @tc.type: FUNC
 */
HWTEST_F(ButtonFunctionTestTwoNg, ButtonFunctionTest020, TestSize.Level1)
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

/**
 * @tc.name: ButtonFunctionTest021
 * @tc.desc: test textOverflow enum value.
 * @tc.type: FUNC
 */
HWTEST_F(ButtonFunctionTestTwoNg, ButtonFunctionTest021, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get frameNode.
     */
    TestProperty testProperty;
    testProperty.borderRadius = std::make_optional(BORDER_RADIUS);
    testProperty.controlSize = ControlSize::SMALL;
    auto frameNode = CreateLabelButtonParagraph(CREATE_VALUE, testProperty);
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::BUTTON_ETS_TAG);

    /**
     * @tc.steps: step2. visit function CreateAndCheckTextOverflow, then check whether the properties is correct.
     */
    CreateAndCheckTextOverflow(frameNode, true);

    /**
     * @tc.steps: step3. buttonPattern UpdateButtonStyle.
     */
    auto buttonPattern = frameNode->GetPattern<ButtonPattern>();
    ASSERT_NE(buttonPattern, nullptr);
    buttonPattern->isTextFadeOut_ = true;
    buttonPattern->SetIsFocus(true);
    buttonPattern->UpdateButtonStyle();

    /**
     * @tc.steps: step4. visit function CheckTextMarqueeOption.
     * @tc.expected: step4. check whether the properties is correct.
     */
    CheckTextMarqueeOption(frameNode, true);
}

/**
 * @tc.name: ButtonFunctionTest022
 * @tc.desc: test textOverflow enum value.
 * @tc.type: FUNC
 */
HWTEST_F(ButtonFunctionTestTwoNg, ButtonFunctionTest022, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get frameNode.
     */
    TestProperty testProperty;
    testProperty.borderRadius = std::make_optional(BORDER_RADIUS);
    auto frameNode = CreateLabelButtonParagraph(CREATE_VALUE, testProperty);
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::BUTTON_ETS_TAG);

    /**
     * @tc.steps: step2. visit function CreateAndCheckTextOverflow, then check whether the properties is correct.
     */
    CreateAndCheckTextOverflow(frameNode, true);

    /**
     * @tc.steps: step3. buttonPattern UpdateButtonStyle.
     */
    auto buttonPattern = frameNode->GetPattern<ButtonPattern>();
    ASSERT_NE(buttonPattern, nullptr);
    buttonPattern->isTextFadeOut_ = true;
    buttonPattern->isHover_ = true;
    buttonPattern->SetIsFocus(false);
    buttonPattern->UpdateButtonStyle();

    /**
     * @tc.steps: step4. visit function CheckTextMarqueeOption.
     * @tc.expected: step4. check whether the properties is correct.
     */
    CheckTextMarqueeOption(frameNode, true);
}

/**
 * @tc.name: ButtonFunctionTest023
 * @tc.desc: test textOverflow enum value.
 * @tc.type: FUNC
 */
HWTEST_F(ButtonFunctionTestTwoNg, ButtonFunctionTest023, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get frameNode.
     */
    TestProperty testProperty;
    testProperty.borderRadius = std::make_optional(BORDER_RADIUS);
    auto frameNode = CreateLabelButtonParagraph(CREATE_VALUE, testProperty);
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::BUTTON_ETS_TAG);

    /**
     * @tc.steps: step2. visit function CreateAndCheckTextOverflow, then check whether the properties is correct.
     */
    CreateAndCheckTextOverflow(frameNode, true);

    /**
     * @tc.steps: step3. buttonPattern UpdateButtonStyle.
     */
    auto buttonPattern = frameNode->GetPattern<ButtonPattern>();
    ASSERT_NE(buttonPattern, nullptr);
    buttonPattern->isTextFadeOut_ = true;
    buttonPattern->isHover_ = false;
    buttonPattern->SetIsFocus(false);
    buttonPattern->UpdateButtonStyle();

    /**
     * @tc.steps: step4. visit function CheckTextMarqueeOption.
     * @tc.expected: step4. check whether the properties is correct.
     */
    CheckTextMarqueeOption(frameNode, false);
}

/**
 * @tc.name: ButtonFunctionTest024
 * @tc.desc: test AddIsFocusActiveUpdateEvent.
 * @tc.type: FUNC
 */
HWTEST_F(ButtonFunctionTestTwoNg, ButtonFunctionTest024, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get frameNode.
     */
    TestProperty testProperty;
    testProperty.borderRadius = std::make_optional(BORDER_RADIUS);
    auto frameNode = CreateLabelButtonParagraph(CREATE_VALUE, testProperty);
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::BUTTON_ETS_TAG);

    /**
     * @tc.steps: step2. visit function CreateAndCheckTextOverflow, then check whether the properties is correct.
     */
    CreateAndCheckTextOverflow(frameNode, false);

    /**
     * @tc.steps: step3. buttonPattern AddIsFocusActiveUpdateEvent.
     */
    auto buttonPattern = frameNode->GetPattern<ButtonPattern>();
    ASSERT_NE(buttonPattern, nullptr);
    buttonPattern->OnModifyDone();
    buttonPattern->isTextFadeOut_ = true;
    buttonPattern->HandleFocusStatusStyle();
    buttonPattern->SetIsFocus(true);
    buttonPattern->HandleFocusStyleTask();
    buttonPattern->AddIsFocusActiveUpdateEvent();
    buttonPattern->UpdateButtonStyle();

    /**
     * @tc.steps: step4. visit function CheckTextMarqueeOption.
     * @tc.expected: step4. check whether the properties is correct.
     */
    CheckTextMarqueeOption(frameNode, true);

    /**
     * @tc.steps: step5. buttonPattern RemoveIsFocusActiveUpdateEvent.
     */
    buttonPattern->SetIsFocus(false);
    buttonPattern->HandleBlurStyleTask();
    buttonPattern->RemoveIsFocusActiveUpdateEvent();
    buttonPattern->UpdateButtonStyle();

    /**
     * @tc.steps: step6. visit function CheckTextMarqueeOption.
     * @tc.expected: step6. check whether the properties is correct.
     */
    CheckTextMarqueeOption(frameNode, false);
}

/**
 * @tc.name: test match parent layout policy.
 * @tc.desc: test the measure result when setting layoutPolicy is match parent.
 * @tc.type: FUNC
 */
HWTEST_F(ButtonFunctionTestTwoNg, LayoutPolicyTest001, TestSize.Level1)
{
    RefPtr<FrameNode> button;
    RefPtr<FrameNode> frameNode = CreateButton(u"partent", [this, &button](ButtonModelNG model) {
        ViewAbstract::SetWidth(CalcLength(500));
        ViewAbstract::SetHeight(CalcLength(300));
        button = CreateButton(u"child", [](ButtonModelNG model) {
            ViewAbstractModelNG model1;
            model1.UpdateLayoutPolicyProperty(LayoutCalPolicy::MATCH_PARENT, true);
            model1.UpdateLayoutPolicyProperty(LayoutCalPolicy::MATCH_PARENT, false);
        });
    });
    ASSERT_NE(frameNode, nullptr);
    ASSERT_NE(button, nullptr);
    ASSERT_EQ(frameNode->GetChildren().size(), 1);
    CreateLayoutTask(frameNode);

    // Expect button's width is 500, height is 300 and offset is [0.0, 0.0].
    auto geometryNode = frameNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    auto size = geometryNode->GetFrameSize();
    auto offset = geometryNode->GetFrameOffset();
    EXPECT_EQ(size, SizeF(500.0f, 300.0f));
    EXPECT_EQ(offset, OffsetF(0.0f, 0.0f));

    // Expect button1's width is 500, height is 300 and offset is [0.0, 0.0].
    auto geometryNode1 = button->GetGeometryNode();
    ASSERT_NE(geometryNode1, nullptr);
    auto size1 = geometryNode1->GetFrameSize();
    auto offset1 = geometryNode1->GetFrameOffset();
    EXPECT_EQ(size1, SizeF(500.0f, 300.0f));
    EXPECT_EQ(offset1, OffsetF(0.0f, 0.0f));
}

/**
 * @tc.name: ParseButtonResColor
 * @tc.desc: test ParseButtonResColor.
 * @tc.type: FUNC
 */
HWTEST_F(ButtonFunctionTestTwoNg, ParseButtonResColor, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create button frame node.
     * @tc.expected: step1. Button node is not null.
     */
    ButtonModelNG buttonModelNG;
    buttonModelNG.CreateWithLabel(CREATE_VALUE);
    auto buttonNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(buttonNode, nullptr);
    auto context = PipelineBase::GetCurrentContextSafely();
    ASSERT_NE(context, nullptr);
    auto buttonTheme = context->GetTheme<ButtonTheme>();
    ASSERT_NE(buttonTheme, nullptr);

    /**
     * @tc.steps: step2. Create resource and color.
     * @tc.expected: step2. Resource and color are created.
     */
    auto resObj = AceType::MakeRefPtr<ResourceObject>("", "", -1);
    Color result(Color::RED);

    /**
     * @tc.steps: step3. Parse resource with invalid color type.
     * @tc.expected: step3. Color remains unchanged.
     */
    buttonModelNG.ParseButtonResColor(resObj, result, static_cast<ButtonColorType>(2));
    EXPECT_EQ(result, Color::RED);

    /**
     * @tc.steps: step4. Parse resource with background color type.
     * @tc.expected: step4. Color is set to button theme's background color.
     */
    buttonModelNG.ParseButtonResColor(resObj, result, ButtonColorType::BACKGROUND_COLOR);
    EXPECT_EQ(result, buttonTheme->GetBgColor());

    /**
     * @tc.steps: step5. Parse resource with font color type.
     * @tc.expected: step5. Color is set to button theme's font color.
     */
    buttonModelNG.ParseButtonResColor(resObj, result, ButtonColorType::FONT_COLOR);
    EXPECT_EQ(result, buttonTheme->GetTextStyle().GetTextColor());
}

/**
 * @tc.name: UpdateResColor
 * @tc.desc: test UpdateResColor.
 * @tc.type: FUNC
 */
HWTEST_F(ButtonFunctionTestTwoNg, UpdateResColor, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create button frame node.
     * @tc.expected: step1. Button node is not null.
     */
    ButtonModelNG buttonModelNG;
    buttonModelNG.CreateWithLabel(CREATE_VALUE);
    auto buttonNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(buttonNode, nullptr);

    /**
     * @tc.steps: step2. Verify initial color properties.
     * @tc.expected: step2. Font color and background color are not set.
     */
    auto layoutProperty = buttonNode->GetLayoutProperty<ButtonLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    auto colorRet = layoutProperty->GetFontColor();
    EXPECT_FALSE(colorRet.has_value());
    auto renderContext = buttonNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    colorRet = renderContext->GetBackgroundColor();
    EXPECT_FALSE(colorRet.has_value());

    /**
     * @tc.steps: step3. Update color properties.
     * @tc.expected: step3. Background color and font color are updated.
     */
    buttonModelNG.UpdateResColor(buttonNode, Color::RED, ButtonColorType::BACKGROUND_COLOR);
    colorRet = renderContext->GetBackgroundColor();
    EXPECT_EQ(colorRet.value_or(Color::BLACK), Color::RED);

    buttonModelNG.UpdateResColor(buttonNode, Color::RED, ButtonColorType::FONT_COLOR);
    colorRet = layoutProperty->GetFontColor();
    EXPECT_EQ(colorRet.value_or(Color::BLACK), Color::RED);
}

/**
 * @tc.name: CreateWithColorResourceObj
 * @tc.desc: test CreateWithColorResourceObj.
 * @tc.type: FUNC
 */
HWTEST_F(ButtonFunctionTestTwoNg, CreateWithColorResourceObj, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create button frame node.
     * @tc.expected: step1. Button node is not null.
     */
    ButtonModelNG buttonModelNG;
    buttonModelNG.CreateWithLabel(CREATE_VALUE);
    auto buttonNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(buttonNode, nullptr);

    /**
     * @tc.steps: step2. Set system color change flag.
     * @tc.expected: step2. Flag is set.
     */
    auto pipelineContext = buttonNode->GetContext();
    ASSERT_NE(pipelineContext, nullptr);
    pipelineContext->SetIsSystemColorChange(true);

    /**
     * @tc.steps: step3. Update background color and create color resource object.
     * @tc.expected: step3. Background color is updated.
     */
    auto renderContext = buttonNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    renderContext->UpdateBackgroundColor(Color::RED);
    auto colorRet = renderContext->GetBackgroundColor();
    EXPECT_EQ(colorRet.value_or(Color::WHITE), Color::RED);

    auto resObj = AceType::MakeRefPtr<ResourceObject>("", "", -1);
    buttonModelNG.CreateWithColorResourceObj(resObj, ButtonColorType::BACKGROUND_COLOR);
    colorRet = renderContext->GetBackgroundColor();
    EXPECT_EQ(colorRet.value_or(Color::WHITE), Color::RED);
}

/**
 * @tc.name: CreateWithStringResourceObj
 * @tc.desc: test CreateWithStringResourceObj.
 * @tc.type: FUNC
 */
HWTEST_F(ButtonFunctionTestTwoNg, CreateWithStringResourceObj, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create button frame node.
     * @tc.expected: step1. Button node is not null.
     */
    ButtonModelNG buttonModelNG;
    buttonModelNG.CreateWithLabel(CREATE_VALUE);
    auto buttonNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(buttonNode, nullptr);

    /**
     * @tc.steps: step2. Create string resource object and verify resource manager.
     * @tc.expected: step2. Resource is added to manager.
     */
    auto resObj = AceType::MakeRefPtr<ResourceObject>("", "", -1);
    buttonModelNG.CreateWithStringResourceObj(resObj, ButtonStringType::LABEL);

    auto pattern = buttonNode->GetPattern<ButtonPattern>();
    ASSERT_NE(pattern, nullptr);
    std::string key = "button" + ButtonModelNG::StringTypeToStr(ButtonStringType::LABEL);
    auto resMgr = pattern->resourceMgr_;
    ASSERT_NE(resMgr, nullptr);
    auto count = resMgr->resMap_.count(key);
    EXPECT_EQ(count, 1);
    pattern->OnColorModeChange(1);

    /**
     * @tc.steps: step3. Create another string resource object with parameters.
     * @tc.expected: step3. Resource is added to manager.
     */
    ResourceObjectParams params { .value = "", .type = ResourceObjectParamType::NONE };
    RefPtr<ResourceObject> resObjWithParams =
        AceType::MakeRefPtr<ResourceObject>(1, 10003, std::vector<ResourceObjectParams> { params }, "", "", 100000);
    buttonModelNG.CreateWithStringResourceObj(resObjWithParams, ButtonStringType::FONT_FAMILY);
    key = "button" + ButtonModelNG::StringTypeToStr(ButtonStringType::FONT_FAMILY);
    count = resMgr->resMap_.count(key);
    EXPECT_EQ(count, 1);
    pattern->OnColorModeChange(1);
}

/**
 * @tc.name: CreateWithFamiliesResourceObj
 * @tc.desc: test CreateWithFamiliesResourceObj.
 * @tc.type: FUNC
 */
HWTEST_F(ButtonFunctionTestTwoNg, CreateWithFamiliesResourceObj, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create button frame node.
     * @tc.expected: step1. Button node is not null.
     */
    ButtonModelNG buttonModelNG;
    buttonModelNG.CreateWithLabel(CREATE_VALUE);
    auto buttonNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(buttonNode, nullptr);

    /**
     * @tc.steps: step2. Create font family resource object and verify resource manager.
     * @tc.expected: step2. Resource is added to manager.
     */
    auto resObj = AceType::MakeRefPtr<ResourceObject>("", "", -1);
    buttonModelNG.CreateWithFamiliesResourceObj(resObj, ButtonStringType::FONT_FAMILY);

    auto pattern = buttonNode->GetPattern<ButtonPattern>();
    ASSERT_NE(pattern, nullptr);
    std::string key = "button" + ButtonModelNG::StringTypeToStr(ButtonStringType::FONT_FAMILY);
    auto resMgr = pattern->resourceMgr_;
    ASSERT_NE(resMgr, nullptr);
    auto count = resMgr->resMap_.count(key);
    EXPECT_EQ(count, 1);
    pattern->OnColorModeChange(1);

    /**
     * @tc.steps: step3. Create another font family resource object with parameters.
     * @tc.expected: step3. Resource is added to manager.
     */
    ResourceObjectParams params { .value = "", .type = ResourceObjectParamType::NONE };
    RefPtr<ResourceObject> resObjWithParams =
        AceType::MakeRefPtr<ResourceObject>(1, 10003, std::vector<ResourceObjectParams> { params }, "", "", 100000);
    buttonModelNG.CreateWithFamiliesResourceObj(resObjWithParams, ButtonStringType::LABEL);
    key = "button" + ButtonModelNG::StringTypeToStr(ButtonStringType::LABEL);
    count = resMgr->resMap_.count(key);
    EXPECT_EQ(count, 1);
    pattern->OnColorModeChange(1);
}

/**
 * @tc.name: UpdateDefaultFamilies
 * @tc.desc: test UpdateDefaultFamilies.
 * @tc.type: FUNC
 */
HWTEST_F(ButtonFunctionTestTwoNg, UpdateDefaultFamilies, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create button frame node.
     * @tc.expected: step1. Button node is not null.
     */
    ButtonModelNG buttonModelNG;
    buttonModelNG.CreateWithLabel(CREATE_VALUE);
    auto buttonNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(buttonNode, nullptr);

    /**
     * @tc.steps: step2. Set up theme and layout properties.
     * @tc.expected: step2. Theme and layout properties are set.
     */
    auto pipelineContext = PipelineBase::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto theme = pipelineContext->GetTheme<ButtonTheme>();
    ASSERT_NE(theme, nullptr);
    auto layout = buttonNode->GetLayoutPropertyPtr<ButtonLayoutProperty>();
    ASSERT_NE(layout, nullptr);

    /**
     * @tc.steps: step3. Update default font families with different conditions.
     * @tc.expected: step3. Font families are updated correctly.
     */
    std::vector<std::string> fonts { "test" };
    theme->textStyle_.SetFontFamilies(fonts);
    std::vector<std::pair<bool, bool>> vec { { true, true }, { true, false }, { false, true }, { false, false } };
    for (const auto& pair : vec) {
        pipelineContext->SetIsSystemColorChange(pair.first);
        buttonNode->SetRerenderable(pair.second);
        buttonModelNG.UpdateDefaultFamilies(buttonNode, fonts, ButtonStringType::LABEL);
        if (pipelineContext->IsSystmColorChange()) {
            buttonModelNG.UpdateDefaultFamilies(buttonNode, fonts, ButtonStringType::FONT_FAMILY);
            auto ret = layout->GetFontFamily();
            ASSERT_NE(ret.has_value(), false);
            EXPECT_EQ(ret.value(), fonts);
        }
    }
}

/**
 * @tc.name: UpdateComponentFamilies001
 * @tc.desc: test Model UpdateComponentFamilies.
 * @tc.type: FUNC
 */
HWTEST_F(ButtonFunctionTestTwoNg, UpdateComponentFamilies001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create button frame node.
     * @tc.expected: step1. Button node is not null.
     */
    ButtonModelNG buttonModelNG;
    buttonModelNG.CreateWithLabel(CREATE_VALUE);
    auto buttonNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(buttonNode, nullptr);

    /**
     * @tc.steps: step2. Set up pipeline context and layout properties.
     * @tc.expected: step2. Pipeline context and layout properties are set.
     */
    auto pipelineContext = PipelineBase::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto layout = buttonNode->GetLayoutPropertyPtr<ButtonLayoutProperty>();
    ASSERT_NE(layout, nullptr);

    /**
     * @tc.steps: step3. Update component font families with different conditions.
     * @tc.expected: step3. Font families are updated correctly.
     */
    std::vector<std::string> fonts { "test" };
    std::vector<std::pair<bool, bool>> vec { { true, true }, { true, false }, { false, true }, { false, false } };
    for (const auto& pair : vec) {
        pipelineContext->SetIsSystemColorChange(pair.first);
        buttonNode->SetRerenderable(pair.second);
        buttonModelNG.UpdateComponentFamilies(buttonNode, fonts, ButtonStringType::LABEL);
        if (pipelineContext->IsSystmColorChange()) {
            buttonModelNG.UpdateComponentFamilies(buttonNode, fonts, ButtonStringType::FONT_FAMILY);
            auto ret = layout->GetFontFamily();
            ASSERT_NE(ret.has_value(), false);
            EXPECT_EQ(ret.value(), fonts);
        }
    }
}

/**
 * @tc.name: CreateWithDimensionFpResourceObj
 * @tc.desc: test CreateWithDimensionFpResourceObj.
 * @tc.type: FUNC
 */
HWTEST_F(ButtonFunctionTestTwoNg, CreateWithDimensionFpResourceObj, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create button frame node.
     * @tc.expected: step1. Button node is not null.
     */
    ButtonModelNG buttonModelNG;
    buttonModelNG.CreateWithLabel(CREATE_VALUE);
    auto buttonNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(buttonNode, nullptr);

    /**
     * @tc.steps: step2. Create dimension resource object and verify resource manager.
     * @tc.expected: step2. Resource is added to manager.
     */
    auto resObj = AceType::MakeRefPtr<ResourceObject>("", "", -1);
    buttonModelNG.CreateWithDimensionFpResourceObj(resObj, ButtonDimensionType::MIN_FONT_SIZE);

    auto pattern = buttonNode->GetPattern<ButtonPattern>();
    ASSERT_NE(pattern, nullptr);
    std::string key = "button" + ButtonModelNG::DimensionTypeToString(ButtonDimensionType::MIN_FONT_SIZE);
    auto resMgr = pattern->resourceMgr_;
    ASSERT_NE(resMgr, nullptr);
    auto count = resMgr->resMap_.count(key);
    EXPECT_EQ(count, 1);
    pattern->OnColorModeChange(1);

    /**
     * @tc.steps: step3. Create another dimension resource object with parameters.
     * @tc.expected: step3. Resource is added to manager.
     */
    ResourceObjectParams params { .value = "", .type = ResourceObjectParamType::NONE };
    RefPtr<ResourceObject> resObjWithParams =
        AceType::MakeRefPtr<ResourceObject>(1, 10002, std::vector<ResourceObjectParams> { params }, "", "", 100000);
    buttonModelNG.CreateWithDimensionFpResourceObj(resObjWithParams, ButtonDimensionType::MAX_FONT_SIZE);
    key = "button" + ButtonModelNG::DimensionTypeToString(ButtonDimensionType::MAX_FONT_SIZE);
    count = resMgr->resMap_.count(key);
    EXPECT_EQ(count, 1);
    pattern->OnColorModeChange(1);
}

/**
 * @tc.name: CheckFontScale
 * @tc.desc: test CheckFontScale.
 * @tc.type: FUNC
 */
HWTEST_F(ButtonFunctionTestTwoNg, CheckFontScale, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create button frame node.
     * @tc.expected: step1. Button node is not null.
     */
    ButtonModelNG buttonModelNG;
    buttonModelNG.CreateWithLabel(CREATE_VALUE);
    auto buttonNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(buttonNode, nullptr);

    /**
     * @tc.steps: step2. Check font scale with different values and types.
     * @tc.expected: step2. Font scale checks return expected results.
     */
    double scale = 1.0f;
    auto ret = buttonModelNG.CheckFontScale(true, scale, ButtonDoubleType::MAX_FONT_SCALE);
    EXPECT_FALSE(ret);

    scale = 0.5f;
    ret = buttonModelNG.CheckFontScale(true, scale, ButtonDoubleType::MIN_FONT_SCALE);
    EXPECT_TRUE(ret);
    scale = 2.0f;
    ret = buttonModelNG.CheckFontScale(true, scale, ButtonDoubleType::MIN_FONT_SCALE);
    EXPECT_TRUE(ret);
}

/**
 * @tc.name: CreateWithDoubleResourceObj
 * @tc.desc: test CreateWithDoubleResourceObj.
 * @tc.type: FUNC
 */
HWTEST_F(ButtonFunctionTestTwoNg, CreateWithDoubleResourceObj, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create button frame node.
     * @tc.expected: step1. Button node is not null.
     */
    ButtonModelNG buttonModelNG;
    buttonModelNG.CreateWithLabel(CREATE_VALUE);
    auto buttonNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(buttonNode, nullptr);

    /**
     * @tc.steps: step2. Create double resource object and verify resource manager.
     * @tc.expected: step2. Resource is added to manager.
     */
    auto resObj = AceType::MakeRefPtr<ResourceObject>("", "", -1);
    buttonModelNG.CreateWithDoubleResourceObj(resObj, ButtonDoubleType::MIN_FONT_SCALE);

    auto pattern = buttonNode->GetPattern<ButtonPattern>();
    ASSERT_NE(pattern, nullptr);
    std::string key = "button" + ButtonModelNG::DoubleTypeToString(ButtonDoubleType::MIN_FONT_SCALE);
    auto resMgr = pattern->resourceMgr_;
    ASSERT_NE(resMgr, nullptr);
    auto count = resMgr->resMap_.count(key);
    EXPECT_EQ(count, 1);
    pattern->OnColorModeChange(1);

    /**
     * @tc.steps: step3. Create another double resource object with parameters.
     * @tc.expected: step3. Resource is added to manager.
     */
    ResourceObjectParams params { .value = "", .type = ResourceObjectParamType::NONE };
    RefPtr<ResourceObject> resObjWithParams =
        AceType::MakeRefPtr<ResourceObject>(1, 10002, std::vector<ResourceObjectParams> { params }, "", "", 100000);
    buttonModelNG.CreateWithDoubleResourceObj(resObjWithParams, ButtonDoubleType::MAX_FONT_SCALE);
    key = "button" + ButtonModelNG::DoubleTypeToString(ButtonDoubleType::MAX_FONT_SCALE);
    count = resMgr->resMap_.count(key);
    EXPECT_EQ(count, 1);
    pattern->OnColorModeChange(1);
}

/**
 * @tc.name: ColorTypeToString
 * @tc.desc: test ColorTypeToString.
 * @tc.type: FUNC
 */
HWTEST_F(ButtonFunctionTestTwoNg, ColorTypeToString, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Test color type to string conversion.
     * @tc.expected: step1. Conversion returns correct string values.
     */
    std::vector<std::pair<ButtonColorType, std::string>> types = { { ButtonColorType::FONT_COLOR, "FontColor" },
        { ButtonColorType::BACKGROUND_COLOR, "BackgroundColor" }, { static_cast<ButtonColorType>(2), "Unknown" } };
    for (const auto& [type, val] : types) {
        auto ret = ButtonModelNG::ColorTypeToString(type);
        EXPECT_EQ(val, ret);
    }
}

/**
 * @tc.name: StringTypeToStr
 * @tc.desc: test StringTypeToStr.
 * @tc.type: FUNC
 */
HWTEST_F(ButtonFunctionTestTwoNg, StringTypeToStr, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Test string type to string conversion.
     * @tc.expected: step1. Conversion returns correct string values.
     */
    std::vector<std::pair<ButtonStringType, std::string>> types = { { ButtonStringType::LABEL, "Label" },
        { ButtonStringType::FONT_FAMILY, "FontFamily" }, { static_cast<ButtonStringType>(2), "Unknown" } };
    for (const auto& [type, val] : types) {
        auto ret = ButtonModelNG::StringTypeToStr(type);
        EXPECT_EQ(val, ret);
    }
}
/**
 * @tc.name: DimensionTypeToString
 * @tc.desc: test DimensionTypeToString.
 * @tc.type: FUNC
 */
HWTEST_F(ButtonFunctionTestTwoNg, DimensionTypeToString, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Test dimension type to string conversion.
     * @tc.expected: step1. Conversion returns correct string values.
     */
    std::vector<std::pair<ButtonDimensionType, std::string>> types = {
        { ButtonDimensionType::MIN_FONT_SIZE, "MinFontSize" },
        { ButtonDimensionType::MAX_FONT_SIZE, "MaxFontSize" },
        { static_cast<ButtonDimensionType>(2), "Unknown" } };
    for (const auto& [type, val] : types) {
        auto ret = ButtonModelNG::DimensionTypeToString(type);
        EXPECT_EQ(val, ret);
    }
}

/**
 * @tc.name: DoubleTypeToString
 * @tc.desc: test DoubleTypeToString.
 * @tc.type: FUNC
 */
HWTEST_F(ButtonFunctionTestTwoNg, DoubleTypeToString, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Test double type to string conversion.
     * @tc.expected: step1. Conversion returns correct string values.
     */
    std::vector<std::pair<ButtonDoubleType, std::string>> types = {
        { ButtonDoubleType::MIN_FONT_SCALE, "MinFontScale" },
        { ButtonDoubleType::MAX_FONT_SCALE, "MaxFontScale" },
        { static_cast<ButtonDoubleType>(2), "Unknown" } };
    for (const auto& [type, val] : types) {
        auto ret = ButtonModelNG::DoubleTypeToString(type);
        EXPECT_EQ(val, ret);
    }
}

/**
 * @tc.name: UpdateComponentColor
 * @tc.desc: test UpdateComponentColor.
 * @tc.type: FUNC
 */
HWTEST_F(ButtonFunctionTestTwoNg, UpdateComponentColor, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create button frame node and get necessary properties.
     * @tc.expected: step1. Button node and properties are not null.
     */
    ButtonModelNG buttonModelNG;
    buttonModelNG.CreateWithLabel(CREATE_VALUE);
    auto buttonNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(buttonNode, nullptr);
    auto pipelineContext = buttonNode->GetContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto layoutProperty = buttonNode->GetLayoutProperty<ButtonLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    auto pattern = buttonNode->GetPattern<ButtonPattern>();
    ASSERT_NE(pattern, nullptr);
    auto renderContext = buttonNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    auto textNode = AceType::DynamicCast<FrameNode>(buttonNode->GetFirstChild());
    ASSERT_NE(textNode, nullptr);
    auto textRenderContext = textNode->GetRenderContext();
    ASSERT_NE(textRenderContext, nullptr);
    /**
     * @tc.steps: step2. Update component color with different conditions.
     * @tc.expected: step2. Color properties are updated correctly.
     */
    std::vector<std::pair<bool, bool>> vec { { true, true }, { true, false }, { false, true }, { false, false } };
    for (const auto& pair : vec) {
        pipelineContext->SetIsSystemColorChange(pair.first);
        buttonNode->SetRerenderable(pair.second);
        pattern->UpdateComponentColor(Color::RED, static_cast<ButtonColorType>(2));
        if (pipelineContext->IsSystmColorChange() && pair.second) {
            pattern->UpdateComponentColor(Color::RED, ButtonColorType::FONT_COLOR);
            auto foregroundColor = textRenderContext->GetForegroundColor();
            EXPECT_EQ(foregroundColor, Color::RED);
            pattern->UpdateComponentColor(Color::RED, ButtonColorType::BACKGROUND_COLOR);
            auto color = renderContext->GetBackgroundColor();
            EXPECT_EQ(color.value_or(Color::BLACK), Color::RED);
        }
    }
}

/**
 * @tc.name: UpdateComponentString
 * @tc.desc: test UpdateComponentString.
 * @tc.type: FUNC
 */
HWTEST_F(ButtonFunctionTestTwoNg, UpdateComponentString, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create button frame node and get necessary properties.
     * @tc.expected: step1. Button node and properties are not null.
     */
    ButtonModelNG buttonModelNG;
    buttonModelNG.CreateWithLabel(CREATE_VALUE);
    auto buttonNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(buttonNode, nullptr);
    auto pipelineContext = buttonNode->GetContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto textNode = AceType::DynamicCast<FrameNode>(buttonNode->GetFirstChild());
    ASSERT_NE(textNode, nullptr);
    auto textLayoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);
    auto pattern = buttonNode->GetPattern<ButtonPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Update component string with different conditions.
     * @tc.expected: step2. String properties are updated correctly.
     */
    std::string value { "Test Sans" };
    std::u16string eValue { u"error" };
    std::vector<std::pair<bool, bool>> vec { { true, true }, { true, false }, { false, true }, { false, false } };
    for (const auto& pair : vec) {
        pipelineContext->SetIsSystemColorChange(pair.first);
        buttonNode->SetRerenderable(pair.second);
        pattern->UpdateComponentString(value, static_cast<ButtonStringType>(2));
        if (pipelineContext->IsSystmColorChange() && pair.second) {
            auto ret = textLayoutProperty->GetContent();
            EXPECT_NE(ret.value_or(eValue), UtfUtils::Str8DebugToStr16(value));
            pattern->UpdateComponentString(value, ButtonStringType::LABEL);
            ret = textLayoutProperty->GetContent();
            EXPECT_EQ(ret.value_or(eValue), UtfUtils::Str8DebugToStr16(value));
        }
    }
}

/**
 * @tc.name: UpdateComponentFamilies002
 * @tc.desc: test Pattern UpdateComponentFamilies.
 * @tc.type: FUNC
 */
HWTEST_F(ButtonFunctionTestTwoNg, UpdateComponentFamilies002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create button frame node and get necessary properties.
     * @tc.expected: step1. Button node and properties are not null.
     */
    ButtonModelNG buttonModelNG;
    buttonModelNG.CreateWithLabel(CREATE_VALUE);
    auto buttonNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(buttonNode, nullptr);
    auto pipelineContext = buttonNode->GetContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto textNode = AceType::DynamicCast<FrameNode>(buttonNode->GetFirstChild());
    ASSERT_NE(textNode, nullptr);
    auto textLayoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);
    auto pattern = buttonNode->GetPattern<ButtonPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Update component font families with different conditions.
     * @tc.expected: step2. Font families are updated correctly.
     */
    std::vector<std::string> fonts { "Test Sans" };
    std::vector<std::pair<bool, bool>> vec { { true, true }, { true, false }, { false, true }, { false, false } };
    for (const auto& pair : vec) {
        pipelineContext->SetIsSystemColorChange(pair.first);
        buttonNode->SetRerenderable(pair.second);
        pattern->UpdateComponentFamilies(fonts, static_cast<ButtonStringType>(2));
        if (pipelineContext->IsSystmColorChange() && pair.second) {
            auto ret = textLayoutProperty->GetFontFamily();
            ASSERT_NE(ret.has_value(), true);
            pattern->UpdateComponentFamilies(fonts, ButtonStringType::FONT_FAMILY);
            ret = textLayoutProperty->GetFontFamily();
            ASSERT_NE(ret.has_value(), false);
            EXPECT_EQ(ret.value(), fonts);
        }
    }
}

/**
 * @tc.name: UpdateComponentDimension
 * @tc.desc: test UpdateComponentDimension.
 * @tc.type: FUNC
 */
HWTEST_F(ButtonFunctionTestTwoNg, UpdateComponentDimension, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create button frame node and get necessary properties.
     * @tc.expected: step1. Button node and properties are not null.
     */
    ButtonModelNG buttonModelNG;
    buttonModelNG.CreateWithLabel(CREATE_VALUE);
    auto buttonNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(buttonNode, nullptr);
    auto pipelineContext = buttonNode->GetContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto textNode = AceType::DynamicCast<FrameNode>(buttonNode->GetFirstChild());
    ASSERT_NE(textNode, nullptr);
    auto textLayoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);
    auto pattern = buttonNode->GetPattern<ButtonPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Update component dimension with different conditions.
     * @tc.expected: step2. Dimension properties are updated correctly.
     */
    CalcDimension value { 1.0f };
    std::vector<std::pair<bool, bool>> vec { { true, true }, { true, false }, { false, true }, { false, false } };
    for (const auto& pair : vec) {
        pipelineContext->SetIsSystemColorChange(pair.first);
        buttonNode->SetRerenderable(pair.second);
        pattern->UpdateComponentDimension(value, static_cast<ButtonDimensionType>(2));
        if (pipelineContext->IsSystmColorChange() && pair.second) {
            auto ret = textLayoutProperty->GetAdaptMinFontSize();
            ASSERT_NE(ret.has_value(), true);
            pattern->UpdateComponentDimension(value, ButtonDimensionType::MIN_FONT_SIZE);
            ret = textLayoutProperty->GetAdaptMinFontSize();
            EXPECT_EQ(ret.value(), value);
            pattern->UpdateComponentDimension(value, ButtonDimensionType::MAX_FONT_SIZE);
            ret = textLayoutProperty->GetAdaptMaxFontSize();
            EXPECT_EQ(ret.value(), value);
        }
    }
}

/**
 * @tc.name: UpdateComponentDouble
 * @tc.desc: test UpdateComponentDouble.
 * @tc.type: FUNC
 */
HWTEST_F(ButtonFunctionTestTwoNg, UpdateComponentDouble, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create button frame node and get necessary properties.
     * @tc.expected: step1. Button node and properties are not null.
     */
    ButtonModelNG buttonModelNG;
    buttonModelNG.CreateWithLabel(CREATE_VALUE);
    auto buttonNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(buttonNode, nullptr);
    auto pipelineContext = buttonNode->GetContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto textNode = AceType::DynamicCast<FrameNode>(buttonNode->GetFirstChild());
    ASSERT_NE(textNode, nullptr);
    auto textLayoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);
    auto pattern = buttonNode->GetPattern<ButtonPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Update component double with different conditions.
     * @tc.expected: step2. Double properties are updated correctly.
     */
    double value = 1.0f;
    std::vector<std::pair<bool, bool>> vec { { true, true }, { true, false }, { false, true }, { false, false } };
    for (const auto& pair : vec) {
        pipelineContext->SetIsSystemColorChange(pair.first);
        buttonNode->SetRerenderable(pair.second);
        pattern->UpdateComponentDouble(value, static_cast<ButtonDoubleType>(2));
        if (pipelineContext->IsSystmColorChange() && pair.second) {
            auto ret = textLayoutProperty->GetMinFontScale();
            ASSERT_NE(ret.has_value(), true);
            pattern->UpdateComponentDouble(value, ButtonDoubleType::MIN_FONT_SCALE);
            ret = textLayoutProperty->GetMinFontScale();
            EXPECT_EQ(ret.value(), value);
            pattern->UpdateComponentDouble(value, ButtonDoubleType::MAX_FONT_SCALE);
            ret = textLayoutProperty->GetMaxFontScale();
            EXPECT_EQ(ret.value(), value);
        }
    }
}

/**
 * @tc.name: VectorToString
 * @tc.desc: test VectorToString.
 * @tc.type: FUNC
 */
HWTEST_F(ButtonFunctionTestTwoNg, VectorToString, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create button frame node and get pattern.
     * @tc.expected: step1. Button node and pattern are not null.
     */
    ButtonModelNG buttonModelNG;
    buttonModelNG.CreateWithLabel(CREATE_VALUE);
    auto buttonNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto pattern = buttonNode->GetPattern<ButtonPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Convert vector to string.
     * @tc.expected: step2. Conversion returns correct string.
     */
    std::vector<std::string> vec { "hello", "world" };
    auto ret = pattern->VectorToString(vec, ",");
    EXPECT_EQ(ret, std::string { "hello,world" });
}

/**
 * @tc.name: StringToVector
 * @tc.desc: test StringToVector.
 * @tc.type: FUNC
 */
HWTEST_F(ButtonFunctionTestTwoNg, StringToVector, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create button frame node and get pattern.
     * @tc.expected: step1. Button node and pattern are not null.
     */
    ButtonModelNG buttonModelNG;
    buttonModelNG.CreateWithLabel(CREATE_VALUE);
    auto buttonNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto pattern = buttonNode->GetPattern<ButtonPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Convert string to vector.
     * @tc.expected: step2. Conversion returns correct vector.
     */
    std::vector<std::string> vec { "hello", "world" };
    auto ret = pattern->StringToVector("hello,world", ',');
    EXPECT_EQ(ret, vec);
}

/**
 * @tc.name: SetNavBarMenuFocusStyle
 * @tc.desc: test SetNavBarMenuFocusStyle.
 * @tc.type: FUNC
 */
HWTEST_F(ButtonFunctionTestTwoNg, SetNavBarMenuFocusStyle, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create button frame node and get pattern.
     * @tc.expected: step1. Button node and pattern are not null.
     */
    ButtonModelNG buttonModelNG;
    buttonModelNG.CreateWithLabel(CREATE_VALUE);
    auto buttonNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto pattern = buttonNode->GetPattern<ButtonPattern>();
    ASSERT_NE(pattern, nullptr);

    auto pipelineContext = PipelineBase::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto theme = pipelineContext->GetTheme<ButtonTheme>();
    ASSERT_NE(theme, nullptr);
    auto layout = AceType::MakeRefPtr<ButtonLayoutProperty>();
    ASSERT_NE(layout, nullptr);
    auto renderContext = buttonNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    Color color = Color::RED;
    renderContext->UpdateBackgroundColor(color);
    pattern->buttonType_ = ComponentButtonType::BUTTON;
    pattern->navMenuItemNeedFocus_ = false;
    pattern->SetNavBarMenuFocusStyle(renderContext, true);
    EXPECT_EQ(renderContext->GetBackgroundColor(), color);

    pattern->buttonType_ = ComponentButtonType::NAVIGATION;
    pattern->navMenuItemNeedFocus_ = false;
    pattern->SetNavBarMenuFocusStyle(renderContext, true);
    EXPECT_EQ(renderContext->GetBackgroundColor(), color);

    pattern->buttonType_ = ComponentButtonType::BUTTON;
    pattern->navMenuItemNeedFocus_ = true;
    pattern->SetNavBarMenuFocusStyle(renderContext, true);
    EXPECT_EQ(renderContext->GetBackgroundColor(), color);

    pattern->buttonType_ = ComponentButtonType::NAVIGATION;
    pattern->navMenuItemNeedFocus_ = true;
    pattern->SetNavBarMenuFocusStyle(renderContext, true);
    EXPECT_EQ(renderContext->GetBackgroundColor(), color);

    pattern->buttonType_ = ComponentButtonType::NAVIGATION;
    pattern->navMenuItemNeedFocus_ = true;
    pattern->SetNavBarMenuFocusStyle(renderContext, false);
    EXPECT_EQ(renderContext->GetBackgroundColor(), color);
}
} // namespace OHOS::Ace::NG
