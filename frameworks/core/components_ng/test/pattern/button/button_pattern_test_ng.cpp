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

#include "base/geometry/dimension.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/text_style.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/pattern/button/button_layout_property.h"
#include "core/components_ng/pattern/button/button_view.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/pattern/text/text_pattern.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {

const std::string CREATE_VALUE = "Hello World";
const ButtonType BUTTON_TYPE_CAPSULE_VALUE = ButtonType::CAPSULE;
const ButtonType BUTTON_TYPE_CUSTOM_VALUE = ButtonType::CUSTOM;
const ButtonType BUTTON_TYPE_DOWNLOAD_VALUE = ButtonType::DOWNLOAD;
const ButtonType BUTTON_TYPE_CIRCLE_VALUE = ButtonType::CIRCLE;
const Dimension BUTTON_FONT_SIZE_VALUE = 30.0_vp;
const Ace::FontWeight BUTTON_BOLD_FONT_WEIGHT_VALUE = Ace::FontWeight::BOLD;
const Ace::FontStyle BUTTON_ITALIC_FONT_STYLE_VALUE = Ace::FontStyle::ITALIC;
const Color BUTTON_TEXT_COLOR_VALUE = Color::RED;
const std::vector<std::string> FONT_FAMILY_VALUE = { "cursive" };
const bool STATE_EFFECT_TRUE_VALUE = true;
const char BUTTON_ETS_TAG[] = "Button";
const char TEXT_ETS_TAG[] = "Text";

} // namespace

struct TestProperty {
    std::optional<ButtonType> typeValue = std::nullopt;
    std::optional<bool> stateEffectValue = std::nullopt;
    std::optional<Dimension> fontSizeValue = std::nullopt;
    std::optional<Ace::FontWeight> fontWeightValue = std::nullopt;
    std::optional<Color> textColorValue = std::nullopt;
    std::optional<Ace::FontStyle> fontStyleValue = std::nullopt;
    std::optional<std::vector<std::string>> fontFamilyValue = std::nullopt;
};

class ButtonPatternTestNg : public testing::Test {
public:
protected:
    RefPtr<FrameNode> CreateLabelButtonParagraph(const std::string& createValue, const TestProperty& testProperty);
    RefPtr<FrameNode> CreateChildButtonParagraph(const std::string& createValue, const TestProperty& testProperty);
};

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
        ButtonView::SetTextColor(testProperty.textColorValue.value());
    }
    if (testProperty.fontStyleValue.has_value()) {
        ButtonView::SetItalicFontStyle(testProperty.fontStyleValue.value());
    }
    if (testProperty.fontFamilyValue.has_value()) {
        ButtonView::SetFontFamily(testProperty.fontFamilyValue.value());
    }

    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish(); // TextView pop
    return AceType::DynamicCast<FrameNode>(element);
}

/**
 * @tc.name: ButtonFrameNodeCreator001
 * @tc.desc: Test all the properties of button.
 * @tc.type: FUNC
 * @tc.author: zhangxiao
 */
HWTEST_F(ButtonPatternTestNg, ButtonFrameNodeCreator001, TestSize.Level1)
{
    TestProperty testProperty;
    testProperty.typeValue = std::make_optional(BUTTON_TYPE_CAPSULE_VALUE);
    testProperty.stateEffectValue = std::make_optional(STATE_EFFECT_TRUE_VALUE);

    RefPtr<FrameNode> frameNode = CreateLabelButtonParagraph(CREATE_VALUE, testProperty);
    EXPECT_EQ(frameNode == nullptr, false);
    RefPtr<LayoutProperty> layoutProperty = frameNode->GetLayoutProperty();
    EXPECT_EQ(layoutProperty == nullptr, false);
    RefPtr<ButtonLayoutProperty> buttonLayoutProperty = AceType::DynamicCast<ButtonLayoutProperty>(layoutProperty);
    EXPECT_EQ(buttonLayoutProperty == nullptr, false);
    EXPECT_EQ(buttonLayoutProperty->GetTypeValue(), BUTTON_TYPE_CAPSULE_VALUE);
}

/**
 * @tc.name: ButtonFrameNodeCreator002
 * @tc.desc: Test all the properties of button.
 * @tc.type: FUNC
 * @tc.author: shanshurong
 */
HWTEST_F(ButtonPatternTestNg, ButtonFrameNodeCreator002, TestSize.Level1)
{
    TestProperty testProperty;
    testProperty.typeValue = std::make_optional(BUTTON_TYPE_CUSTOM_VALUE);
    ButtonView::Create(BUTTON_ETS_TAG);
    ButtonView::SetType(testProperty.typeValue.value());
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    EXPECT_EQ(frameNode == nullptr, false);
    RefPtr<LayoutProperty> layoutProperty = frameNode->GetLayoutProperty();
    EXPECT_EQ(layoutProperty == nullptr, false);
    RefPtr<ButtonLayoutProperty> buttonLayoutProperty = AceType::DynamicCast<ButtonLayoutProperty>(layoutProperty);
    EXPECT_EQ(buttonLayoutProperty == nullptr, false);
    EXPECT_EQ(buttonLayoutProperty->GetTypeValue(), BUTTON_TYPE_CUSTOM_VALUE);
}

/**
 * @tc.name: ButtonFrameNodeCreator003
 * @tc.desc: Test all the properties of button.
 * @tc.type: FUNC
 * @tc.author: shanshurong
 */
HWTEST_F(ButtonPatternTestNg, ButtonFrameNodeCreator003, TestSize.Level1)
{
    TestProperty testProperty;
    testProperty.typeValue = std::make_optional(BUTTON_TYPE_DOWNLOAD_VALUE);
    testProperty.stateEffectValue = std::make_optional(STATE_EFFECT_TRUE_VALUE);
    testProperty.fontSizeValue = std::make_optional(BUTTON_FONT_SIZE_VALUE);
    testProperty.fontWeightValue = std::make_optional(BUTTON_BOLD_FONT_WEIGHT_VALUE);
    RefPtr<FrameNode> frameNode = CreateLabelButtonParagraph(CREATE_VALUE, testProperty);
    EXPECT_EQ(frameNode == nullptr, false);
    RefPtr<LayoutProperty> layoutProperty = frameNode->GetLayoutProperty();
    EXPECT_EQ(layoutProperty == nullptr, false);
    RefPtr<ButtonLayoutProperty> buttonLayoutProperty = AceType::DynamicCast<ButtonLayoutProperty>(layoutProperty);
    EXPECT_EQ(buttonLayoutProperty == nullptr, false);
    EXPECT_EQ(buttonLayoutProperty->GetTypeValue(), BUTTON_TYPE_DOWNLOAD_VALUE);
    EXPECT_EQ(buttonLayoutProperty->GetStateEffectValue(), STATE_EFFECT_TRUE_VALUE);
    EXPECT_EQ(buttonLayoutProperty->GetFontSizeValue(), BUTTON_FONT_SIZE_VALUE);
    EXPECT_EQ(buttonLayoutProperty->GetFontWeightValue(), BUTTON_BOLD_FONT_WEIGHT_VALUE);
    EXPECT_EQ(buttonLayoutProperty->GetLabelValue(), CREATE_VALUE);
}

/**
 * @tc.name: ButtonFrameNodeCreator004
 * @tc.desc: Test all the properties of button.
 * @tc.type: FUNC
 * @tc.author: shanshurong
 */
HWTEST_F(ButtonPatternTestNg, ButtonFrameNodeCreator004, TestSize.Level1)
{
    TestProperty testProperty;
    testProperty.typeValue = std::make_optional(BUTTON_TYPE_CIRCLE_VALUE);
    testProperty.textColorValue = std::make_optional(BUTTON_TEXT_COLOR_VALUE);
    testProperty.fontStyleValue = std::make_optional(BUTTON_ITALIC_FONT_STYLE_VALUE);
    testProperty.fontFamilyValue = std::make_optional(FONT_FAMILY_VALUE);
    auto frameNode = CreateLabelButtonParagraph(CREATE_VALUE, testProperty);
    EXPECT_EQ(frameNode == nullptr, false);
    auto textNode = FrameNode::CreateFrameNode(
        TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    EXPECT_EQ(textNode == nullptr, false);
    auto textLayoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
    EXPECT_EQ(textLayoutProperty == nullptr, false);
    textLayoutProperty->UpdateContent(CREATE_VALUE);
    textNode->SetInternal();
    frameNode->AddChild(textNode);
    auto textChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    EXPECT_EQ(textChild == nullptr, false);
    auto textLayoutPropertyValue = textChild->GetLayoutProperty<TextLayoutProperty>();
    EXPECT_EQ(textLayoutProperty == nullptr, false);
    RefPtr<LayoutProperty> layoutProperty = frameNode->GetLayoutProperty();
    EXPECT_EQ(layoutProperty == nullptr, false);
    RefPtr<ButtonLayoutProperty> buttonLayoutProperty = AceType::DynamicCast<ButtonLayoutProperty>(layoutProperty);
    EXPECT_EQ(buttonLayoutProperty == nullptr, false);
    EXPECT_EQ(buttonLayoutProperty->GetTypeValue(), BUTTON_TYPE_CIRCLE_VALUE);
    EXPECT_EQ(buttonLayoutProperty->GetTextColorValue(), BUTTON_TEXT_COLOR_VALUE);
    EXPECT_EQ(buttonLayoutProperty->GetLabelValue(), CREATE_VALUE);
    EXPECT_EQ(textLayoutPropertyValue->GetItalicFontStyle().value(), BUTTON_ITALIC_FONT_STYLE_VALUE);
    EXPECT_EQ(textLayoutPropertyValue->GetFontFamily().value(), FONT_FAMILY_VALUE);
}

} // namespace OHOS::Ace::NG
