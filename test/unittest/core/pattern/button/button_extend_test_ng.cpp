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
constexpr float BUTTON_WIDTH = 200.0f;
constexpr float BUTTON_HEIGHT = 100.0f;
constexpr float TEXT_WIDTH = 100.0f;
constexpr float TEXT_HEIGHT = 50.0f;
constexpr float FULL_SCREEN_WIDTH = 720.0f;
constexpr float FULL_SCREEN_HEIGHT = 1136.0f;
constexpr float BUTTON_ONLY_HAS_WIDTH_VALUE = 100.0f;
const SizeF BUTTON_SIZE(BUTTON_WIDTH, BUTTON_HEIGHT);
const SizeF TEXT_SIZE(TEXT_WIDTH, TEXT_HEIGHT);
const std::string CREATE_VALUE = "Hello World";
const std::string BUTTON_VALUE = "Test";
const std::string TEST_RESULT = "result_ok";
const std::string TEST_RESULT_CAPSULE = "capsule";
const std::string TEST_RESULT_DOWNLOAD = "download";
const std::vector<std::string> FONT_FAMILY_VALUE = { "cursive" };
const SizeF CONTAINER_SIZE(FULL_SCREEN_WIDTH, FULL_SCREEN_HEIGHT);
const SizeF BUTTON_ONLY_HAS_WIDTH_SIZE(BUTTON_ONLY_HAS_WIDTH_VALUE, BUTTON_ONLY_HAS_WIDTH_VALUE);
const Dimension DEFAULT_HEIGTH = 40.0_vp;
const char LABEL_TEXT[] = "button";
constexpr float BUTTON_ZERO = 0.0f;

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

class ButtonExtendTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();

protected:
    PaddingProperty CreatePadding(float left, float top, float right, float bottom);
};

void ButtonExtendTestNg::SetUpTestCase()
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

void ButtonExtendTestNg::TearDownTestCase()
{
    MockPipelineContext::TearDown();
}

PaddingProperty ButtonExtendTestNg::CreatePadding(float left, float top, float right, float bottom)
{
    PaddingProperty padding;
    padding.left = CalcLength(left);
    padding.right = CalcLength(right);
    padding.top = CalcLength(top);
    padding.bottom = CalcLength(bottom);
    return padding;
}

/**
 * @tc.name: ButtonPatternTest001
 * @tc.desc: Test ButtonModelNG::Set##name(FrameNode* frameNode,value2).
 * @tc.type: FUNC
 */
HWTEST_F(ButtonExtendTestNg, ButtonModelNgTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create a button and set model.
     */
    auto buttonNode = FrameNode::CreateFrameNode(V2::BUTTON_ETS_TAG, 1, AceType::MakeRefPtr<ButtonPattern>());
    ButtonModelNG buttonModelNG;
    buttonModelNG.SetRole(AceType::RawPtr(buttonNode), ButtonRole::NORMAL);
    buttonModelNG.SetButtonStyle(AceType::RawPtr(buttonNode), ButtonStyleMode::NORMAL);
    buttonModelNG.SetControlSize(AceType::RawPtr(buttonNode), ControlSize::SMALL);
    const char* testChar = LABEL_TEXT;
    buttonModelNG.SetLabel(AceType::RawPtr(buttonNode), testChar);
    auto sizeWidth = std::optional<Dimension>(Dimension(20.00, DimensionUnit::VP));
    auto sizeHeight = std::optional<Dimension>(Dimension(20.00, DimensionUnit::VP));
    buttonModelNG.SetSize(AceType::RawPtr(buttonNode), sizeWidth, sizeHeight);
    buttonModelNG.TriggerClick(AceType::RawPtr(buttonNode), 1.0, 1.0);
    buttonModelNG.ApplyTheme(AceType::RawPtr(buttonNode), ButtonStyleMode::NORMAL, ButtonRole::NORMAL);
    buttonModelNG.SetLabelWithCheck(AceType::RawPtr(buttonNode), testChar);
    buttonModelNG.SetCreateWithLabel(AceType::RawPtr(buttonNode), true);
    /**
     * @tc.steps: step1+. create a button with a text childnode and set model not.
     */
    auto buttonNodeEx = FrameNode::CreateFrameNode(V2::BUTTON_ETS_TAG, 1, AceType::MakeRefPtr<ButtonPattern>());
    auto testNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 1, AceType::MakeRefPtr<TextPattern>());
    testNode->MountToParent(buttonNodeEx);
    ButtonModelNG buttonModelNGEx;
    auto gestureEventHub = buttonNodeEx->GetOrCreateGestureEventHub();
    gestureEventHub->clickEventActuator_ = nullptr;
    auto property = buttonNodeEx->GetLayoutProperty<ButtonLayoutProperty>();
    ASSERT_TRUE(property);
    property->UpdateCreateWithLabel(true);
    buttonModelNGEx.SetRole(AceType::RawPtr(buttonNodeEx), std::nullopt);
    buttonModelNGEx.SetButtonStyle(AceType::RawPtr(buttonNodeEx), std::nullopt);
    buttonModelNGEx.SetControlSize(AceType::RawPtr(buttonNodeEx), std::nullopt);
    buttonModelNGEx.SetLabel(AceType::RawPtr(buttonNodeEx), testChar);
    buttonModelNGEx.SetSize(AceType::RawPtr(buttonNodeEx), std::nullopt, std::nullopt);
    buttonModelNGEx.TriggerClick(AceType::RawPtr(buttonNodeEx), 1.0, 1.0);
    buttonModelNGEx.ApplyTheme(AceType::RawPtr(buttonNodeEx), ButtonStyleMode::NORMAL, ButtonRole::NORMAL);
    buttonModelNGEx.SetLabelWithCheck(AceType::RawPtr(buttonNodeEx), testChar);
    buttonModelNGEx.SetCreateWithLabel(AceType::RawPtr(buttonNodeEx), true);
    EXPECT_EQ(property->GetLabelValue(), LABEL_TEXT);
}

/**
 * @tc.name: ButtonPatternTest002
 * @tc.desc: Test ButtonModelNG::CreateWithChild.
 * @tc.type: FUNC
 */
HWTEST_F(ButtonExtendTestNg, ButtonModelNgTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create a button and set model.
     */
    ButtonModelNG buttonModelNG;
    std::list<RefPtr<Component>> buttonChildren;
    createWithPara.parseSuccess = true;
    createWithPara.label = CREATE_VALUE;
    buttonModelNG.CreateWithChild(createWithPara);
    EXPECT_TRUE(createWithPara.optionSetFirst.has_value());
    /**
     * @tc.steps: step1+. create a button and set model.
     */
    createWithPara.optionSetFirst = false;
    createWithPara.label = CREATE_VALUE;
    buttonModelNG.CreateWithChild(createWithPara);
    EXPECT_TRUE(createWithPara.optionSetFirst.has_value());
}
/**
 * @tc.name: ButtonPatternTest003
 * @tc.desc: Test ButtonModelNG::CreateFrameNode.
 * @tc.type: FUNC
 */
HWTEST_F(ButtonExtendTestNg, ButtonModelNgTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create a button and set model.
     */
    ButtonModelNG buttonModelNG;
    buttonModelNG.CreateFrameNode(1);
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    auto buttonNode = AceType::DynamicCast<FrameNode>(element);
    PaddingProperty noPadding = CreatePadding(BUTTON_ZERO, BUTTON_ZERO, BUTTON_ZERO, BUTTON_ZERO);
    auto layoutProperty = buttonNode->GetLayoutProperty<ButtonLayoutProperty>();
    layoutProperty->UpdatePadding(noPadding);
    buttonModelNG.CreateFrameNode(1);
    EXPECT_TRUE(layoutProperty->GetPaddingProperty());
}

} // namespace OHOS::Ace::NG
