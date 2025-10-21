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

#include "gtest/gtest.h"
#include "search_base.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "ui/base/referenced.h"
#include "ui/properties/color.h"

#include "core/components_ng/pattern/search/search_model_static.h"
#include "core/components_v2/inspector/inspector_constants.h"

namespace OHOS::Ace::NG {
namespace {
constexpr double DEFAULT_OPACITY = 0.2;
} // namespace

class SearchModelStaticNg : public SearchBases {
public:
};

/**
 * @tc.name: SetLineHeight_valueOpt_has_value
 * @tc.desc: Test SearchModelStatic SetLineHeight
 * @tc.type: FUNC
 */
HWTEST_F(SearchModelStaticNg, SetLineHeight_valueOpt_has_value, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Search node
     */
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(DEFAULT_TEXT_U16, PLACEHOLDER_U16, SEARCH_SVG);
    auto searchNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(searchNode, nullptr);
    auto textFieldChild =
        FrameNode::CreateFrameNode(V2::SEARCH_Field_ETS_TAG, 1, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(textFieldChild, nullptr);
    RefPtr<TextFieldLayoutProperty> textFieldLayoutProperty = AceType::MakeRefPtr<TextFieldLayoutProperty>();
    textFieldChild->SetLayoutProperty(textFieldLayoutProperty);
    auto layoutProperty = textFieldChild->GetLayoutProperty<TextFieldLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    searchNode->children_ = { textFieldChild };

    /**
     * @tc.steps: step2. Get layoutProperty and call SetLineHeight
     * @tc.expected: GetLineHeight() return 10.0_vp
     */
    std::optional<Dimension> valueOpt = 10.0_vp;
    SearchModelStatic::SetLineHeight(searchNode, valueOpt);
    EXPECT_EQ(layoutProperty->GetLineHeight(), 10.0_vp);
}

/**
 * @tc.name: SetLineHeight_valueOpt_not_value
 * @tc.desc: Test SearchModelStatic SetLineHeight
 * @tc.type: FUNC
 */
HWTEST_F(SearchModelStaticNg, SetLineHeight_valueOpt_not_value, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Search node
     */
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(DEFAULT_TEXT_U16, PLACEHOLDER_U16, SEARCH_SVG);
    auto searchNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(searchNode, nullptr);
    auto textFieldChild =
        FrameNode::CreateFrameNode(V2::SEARCH_Field_ETS_TAG, 1, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(textFieldChild, nullptr);
    RefPtr<TextFieldLayoutProperty> textFieldLayoutProperty = AceType::MakeRefPtr<TextFieldLayoutProperty>();
    textFieldChild->SetLayoutProperty(textFieldLayoutProperty);
    auto layoutProperty = textFieldChild->GetLayoutProperty<TextFieldLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    searchNode->children_ = { textFieldChild };

    /**
     * @tc.steps: step2. Get layoutProperty and call SetLineHeight
     * @tc.expected: GetLineHeight().has_value() return false
     */
    std::optional<Dimension> valueOpt = std::nullopt;
    SearchModelStatic::SetLineHeight(searchNode, valueOpt);
    EXPECT_FALSE(layoutProperty->GetLineHeight().has_value());
}

/**
 * @tc.name: SetHalfLeading_valueOpt_has_value
 * @tc.desc: Test SearchModelStatic SetHalfLeading
 * @tc.type: FUNC
 */
HWTEST_F(SearchModelStaticNg, SetHalfLeading_valueOpt_has_value, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Search node
     */
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(DEFAULT_TEXT_U16, PLACEHOLDER_U16, SEARCH_SVG);
    auto searchNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(searchNode, nullptr);
    auto textFieldChild =
        FrameNode::CreateFrameNode(V2::SEARCH_Field_ETS_TAG, 1, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(textFieldChild, nullptr);
    RefPtr<TextFieldLayoutProperty> textFieldLayoutProperty = AceType::MakeRefPtr<TextFieldLayoutProperty>();
    textFieldChild->SetLayoutProperty(textFieldLayoutProperty);
    auto layoutProperty = textFieldChild->GetLayoutProperty<TextFieldLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    searchNode->children_ = { textFieldChild };

    /**
     * @tc.steps: step2. Get layoutProperty and call SetHalfLeading
     * @tc.expected: GetHalfLeading() return true
     */
    std::optional<bool> valueOpt = true;
    SearchModelStatic::SetHalfLeading(searchNode, valueOpt);
    EXPECT_TRUE(layoutProperty->GetHalfLeading());
}

/**
 * @tc.name: SetHalfLeading_valueOpt_not_value
 * @tc.desc: Test SearchModelStatic SetHalfLeading
 * @tc.type: FUNC
 */
HWTEST_F(SearchModelStaticNg, SetHalfLeading_valueOpt_not_value, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Search node
     */
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(DEFAULT_TEXT_U16, PLACEHOLDER_U16, SEARCH_SVG);
    auto searchNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(searchNode, nullptr);
    auto textFieldChild =
        FrameNode::CreateFrameNode(V2::SEARCH_Field_ETS_TAG, 1, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(textFieldChild, nullptr);
    RefPtr<TextFieldLayoutProperty> textFieldLayoutProperty = AceType::MakeRefPtr<TextFieldLayoutProperty>();
    textFieldChild->SetLayoutProperty(textFieldLayoutProperty);
    auto layoutProperty = textFieldChild->GetLayoutProperty<TextFieldLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    searchNode->children_ = { textFieldChild };

    /**
     * @tc.steps: step2. Get layoutProperty and call SetHalfLeading
     * @tc.expected: GetHalfLeading().has_value() return false
     */
    std::optional<bool> valueOpt = std::nullopt;
    SearchModelStatic::SetHalfLeading(searchNode, valueOpt);
    EXPECT_FALSE(layoutProperty->GetHalfLeading().has_value());
}

/**
 * @tc.name: SetTextDecoration_valueOpt_has_value
 * @tc.desc: Test SearchModelStatic SetTextDecoration
 * @tc.type: FUNC
 */
HWTEST_F(SearchModelStaticNg, SetTextDecoration_valueOpt_has_value, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Search node
     */
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(DEFAULT_TEXT_U16, PLACEHOLDER_U16, SEARCH_SVG);
    auto searchNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(searchNode, nullptr);
    auto textFieldChild =
        FrameNode::CreateFrameNode(V2::SEARCH_Field_ETS_TAG, 1, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(textFieldChild, nullptr);
    RefPtr<TextFieldLayoutProperty> textFieldLayoutProperty = AceType::MakeRefPtr<TextFieldLayoutProperty>();
    textFieldChild->SetLayoutProperty(textFieldLayoutProperty);
    auto layoutProperty = textFieldChild->GetLayoutProperty<TextFieldLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    searchNode->children_ = { textFieldChild };

    /**
     * @tc.steps: step2. Get layoutProperty and call SetTextDecoration
     * @tc.expected: GetTextDecoration().value().front() return LINE_THROUGH
     */
    std::optional<Ace::TextDecoration> valueOpt = Ace::TextDecoration::LINE_THROUGH;
    SearchModelStatic::SetTextDecoration(searchNode, valueOpt);
    EXPECT_EQ(layoutProperty->GetTextDecoration().value().front(), Ace::TextDecoration::LINE_THROUGH);
}

/**
 * @tc.name: SetTextDecoration_valueOpt_not_value
 * @tc.desc: Test SearchModelStatic SetTextDecoration
 * @tc.type: FUNC
 */
HWTEST_F(SearchModelStaticNg, SetTextDecoration_valueOpt_not_value, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Search node
     */
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(DEFAULT_TEXT_U16, PLACEHOLDER_U16, SEARCH_SVG);
    auto searchNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(searchNode, nullptr);
    auto textFieldChild =
        FrameNode::CreateFrameNode(V2::SEARCH_Field_ETS_TAG, 1, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(textFieldChild, nullptr);
    RefPtr<TextFieldLayoutProperty> textFieldLayoutProperty = AceType::MakeRefPtr<TextFieldLayoutProperty>();
    textFieldChild->SetLayoutProperty(textFieldLayoutProperty);
    auto layoutProperty = textFieldChild->GetLayoutProperty<TextFieldLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    searchNode->children_ = { textFieldChild };

    /**
     * @tc.steps: step2. Get layoutProperty and call SetTextDecoration
     * @tc.expected: GetTextDecoration().has_value() return false
     */
    std::optional<Ace::TextDecoration> valueOpt = std::nullopt;
    SearchModelStatic::SetTextDecoration(searchNode, valueOpt);
    EXPECT_FALSE(layoutProperty->GetTextDecoration().has_value());
}

/**
 * @tc.name: SetCustomKeyboard_TextFieldPattern_True
 * @tc.desc: Test SearchModelStatic SetCustomKeyboard
 * @tc.type: FUNC
 */
HWTEST_F(SearchModelStaticNg, SetCustomKeyboard_TextFieldPattern_True, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Search node
     */
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(DEFAULT_TEXT_U16, PLACEHOLDER_U16, SEARCH_SVG);
    auto searchNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(searchNode, nullptr);
    auto textFieldChild =
        FrameNode::CreateFrameNode(V2::SEARCH_Field_ETS_TAG, 1, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(textFieldChild, nullptr);
    searchNode->children_ = { textFieldChild };

    /**
     * @tc.steps: step2. Get textFieldPattern and call SetCustomKeyboard
     * @tc.expected: keyboardAvoidance_ is true
     */
    auto textFieldPattern = textFieldChild->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);
    textFieldPattern->SetCustomKeyboardOption(false);
    SearchModelStatic::SetCustomKeyboard(
        searchNode, []() {}, true);
    EXPECT_TRUE(textFieldPattern->keyboardAvoidance_);
}

/**
 * @tc.name: SetTextDecorationColor_valueOpt_has_value
 * @tc.desc: Test SearchModelStatic SetTextDecorationColor
 * @tc.type: FUNC
 */
HWTEST_F(SearchModelStaticNg, SetTextDecorationColor_valueOpt_has_value, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Search node
     */
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(DEFAULT_TEXT_U16, PLACEHOLDER_U16, SEARCH_SVG);
    auto searchNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(searchNode, nullptr);
    auto textFieldChild =
        FrameNode::CreateFrameNode(V2::SEARCH_Field_ETS_TAG, 1, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(textFieldChild, nullptr);
    RefPtr<TextFieldLayoutProperty> textFieldLayoutProperty = AceType::MakeRefPtr<TextFieldLayoutProperty>();
    textFieldChild->SetLayoutProperty(textFieldLayoutProperty);
    auto layoutProperty = textFieldChild->GetLayoutProperty<TextFieldLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    searchNode->children_ = { textFieldChild };

    /**
     * @tc.steps: step2. Get layoutProperty and call SetTextDecorationColor
     * @tc.expected: GetTextDecorationColor() return Color::RED
     */
    auto valueOpt = std::make_optional<Color>(Color::RED);
    SearchModelStatic::SetTextDecorationColor(searchNode, valueOpt);
    EXPECT_EQ(layoutProperty->GetTextDecorationColor(), Color::RED);
}

/**
 * @tc.name: SetTextDecorationColor_valueOpt_not_value
 * @tc.desc: Test SearchModelStatic SetTextDecorationColor
 * @tc.type: FUNC
 */
HWTEST_F(SearchModelStaticNg, SetTextDecorationColor_valueOpt_not_value, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Search node
     */
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(DEFAULT_TEXT_U16, PLACEHOLDER_U16, SEARCH_SVG);
    auto searchNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(searchNode, nullptr);
    auto textFieldChild =
        FrameNode::CreateFrameNode(V2::SEARCH_Field_ETS_TAG, 1, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(textFieldChild, nullptr);
    RefPtr<TextFieldLayoutProperty> textFieldLayoutProperty = AceType::MakeRefPtr<TextFieldLayoutProperty>();
    textFieldChild->SetLayoutProperty(textFieldLayoutProperty);
    auto layoutProperty = textFieldChild->GetLayoutProperty<TextFieldLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    searchNode->children_ = { textFieldChild };

    /**
     * @tc.steps: step2. Get layoutProperty and call SetTextDecorationColor
     * @tc.expected: GetTextDecorationColor().has_value() return false
     */
    std::optional<Color> valueOpt = std::nullopt;
    SearchModelStatic::SetTextDecorationColor(searchNode, valueOpt);
    EXPECT_FALSE(layoutProperty->GetTextDecorationColor().has_value());
}

/**
 * @tc.name: SetSelectedBackgroundColor_valueOpt_value_default
 * @tc.desc: Test SearchModelStatic SetSelectedBackgroundColor
 * @tc.type: FUNC
 */
HWTEST_F(SearchModelStaticNg, SetSelectedBackgroundColor_valueOpt_value_default, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Search node
     */
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(DEFAULT_TEXT_U16, PLACEHOLDER_U16, SEARCH_SVG);
    auto searchNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(searchNode, nullptr);
    auto textFieldChild =
        FrameNode::CreateFrameNode(V2::SEARCH_Field_ETS_TAG, 1, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(textFieldChild, nullptr);
    RefPtr<TextFieldPaintProperty> textFieldPaintProperty = AceType::MakeRefPtr<TextFieldPaintProperty>();
    textFieldChild->paintProperty_ = textFieldPaintProperty;
    auto paintProperty = textFieldChild->GetPaintProperty<TextFieldPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    searchNode->children_ = { textFieldChild };

    /**
     * @tc.steps: step2. Get paintProperty and call SetSelectedBackgroundColor
     * @tc.expected: GetSelectedBackgroundColor() return 20%default
     */
    Color defaultColor;
    std::optional<Color> valueOpt = defaultColor;
    SearchModelStatic::SetSelectedBackgroundColor(searchNode, valueOpt);
    EXPECT_EQ(paintProperty->GetSelectedBackgroundColor(), valueOpt.value().ChangeOpacity(DEFAULT_OPACITY));
}

/**
 * @tc.name: SetSelectedBackgroundColor_valueOpt_not_value
 * @tc.desc: Test SearchModelStatic SetSelectedBackgroundColor
 * @tc.type: FUNC
 */
HWTEST_F(SearchModelStaticNg, SetSelectedBackgroundColor_valueOpt_not_value, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Search node
     */
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(DEFAULT_TEXT_U16, PLACEHOLDER_U16, SEARCH_SVG);
    auto searchNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(searchNode, nullptr);
    auto textFieldChild =
        FrameNode::CreateFrameNode(V2::SEARCH_Field_ETS_TAG, 1, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(textFieldChild, nullptr);
    RefPtr<TextFieldPaintProperty> textFieldPaintProperty = AceType::MakeRefPtr<TextFieldPaintProperty>();
    textFieldChild->paintProperty_ = textFieldPaintProperty;
    auto paintProperty = textFieldChild->GetPaintProperty<TextFieldPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    searchNode->children_ = { textFieldChild };

    /**
     * @tc.steps: step2. Get paintProperty and call SetSelectedBackgroundColor
     * @tc.expected: GetSelectedBackgroundColor().has_value() return false
     */
    std::optional<Color> valueOpt = std::nullopt;
    SearchModelStatic::SetSelectedBackgroundColor(searchNode, valueOpt);
    EXPECT_FALSE(paintProperty->GetSelectedBackgroundColor().has_value());
}

/**
 * @tc.name: SetTextDecorationStyle_valueOpt_has_value
 * @tc.desc: Test SearchModelStatic SetTextDecorationStyle
 * @tc.type: FUNC
 */
HWTEST_F(SearchModelStaticNg, SetTextDecorationStyle_valueOpt_has_value, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Search node
     */
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(DEFAULT_TEXT_U16, PLACEHOLDER_U16, SEARCH_SVG);
    auto searchNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(searchNode, nullptr);
    auto textFieldChild =
        FrameNode::CreateFrameNode(V2::SEARCH_Field_ETS_TAG, 1, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(textFieldChild, nullptr);
    RefPtr<TextFieldLayoutProperty> textFieldLayoutProperty = AceType::MakeRefPtr<TextFieldLayoutProperty>();
    textFieldChild->SetLayoutProperty(textFieldLayoutProperty);
    auto layoutProperty = textFieldChild->GetLayoutProperty<TextFieldLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    searchNode->children_ = { textFieldChild };

    /**
     * @tc.steps: step2. Get layoutProperty and call SetTextDecorationStyle
     * @tc.expected: GetTextDecorationStyle() return DOUBLE
     */
    auto valueOpt = std::make_optional<Ace::TextDecorationStyle>(Ace::TextDecorationStyle::DOUBLE);
    SearchModelStatic::SetTextDecorationStyle(searchNode, valueOpt);
    EXPECT_EQ(layoutProperty->GetTextDecorationStyle(), Ace::TextDecorationStyle::DOUBLE);
}

/**
 * @tc.name: SetTextDecorationStyle_valueOpt_not_value
 * @tc.desc: Test SearchModelStatic SetTextDecorationStyle
 * @tc.type: FUNC
 */
HWTEST_F(SearchModelStaticNg, SetTextDecorationStyle_valueOpt_not_value, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Search node
     */
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(DEFAULT_TEXT_U16, PLACEHOLDER_U16, SEARCH_SVG);
    auto searchNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(searchNode, nullptr);
    auto textFieldChild =
        FrameNode::CreateFrameNode(V2::SEARCH_Field_ETS_TAG, 1, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(textFieldChild, nullptr);
    RefPtr<TextFieldLayoutProperty> textFieldLayoutProperty = AceType::MakeRefPtr<TextFieldLayoutProperty>();
    textFieldChild->SetLayoutProperty(textFieldLayoutProperty);
    auto layoutProperty = textFieldChild->GetLayoutProperty<TextFieldLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    searchNode->children_ = { textFieldChild };

    /**
     * @tc.steps: step2. Get layoutProperty and call SetTextDecorationStyle
     * @tc.expected: GetTextDecorationStyle().has_value() return false
     */
    std::optional<Ace::TextDecorationStyle> valueOpt = std::nullopt;
    SearchModelStatic::SetTextDecorationStyle(searchNode, valueOpt);
    EXPECT_FALSE(layoutProperty->GetTextDecorationStyle().has_value());
}

/**
 * @tc.name: SetType_valueOpt_has_value
 * @tc.desc: Test SearchModelStatic SetType
 * @tc.type: FUNC
 */
HWTEST_F(SearchModelStaticNg, SetType_valueOpt_has_value, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Search node
     */
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(DEFAULT_TEXT_U16, PLACEHOLDER_U16, SEARCH_SVG);
    auto searchNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(searchNode, nullptr);
    auto textFieldChild =
        FrameNode::CreateFrameNode(V2::SEARCH_Field_ETS_TAG, 1, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(textFieldChild, nullptr);
    RefPtr<TextFieldLayoutProperty> textFieldLayoutProperty = AceType::MakeRefPtr<TextFieldLayoutProperty>();
    textFieldChild->SetLayoutProperty(textFieldLayoutProperty);
    auto layoutProperty = textFieldChild->GetLayoutProperty<TextFieldLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    searchNode->children_ = { textFieldChild };

    /**
     * @tc.steps: step2. Get layoutProperty and call SetType
     * @tc.expected: GetTextInputTypeValue() return NUMBER
     */
    auto valueOpt = std::make_optional<TextInputType>(TextInputType::NUMBER);
    SearchModelStatic::SetType(searchNode, valueOpt);
    EXPECT_EQ(layoutProperty->GetTextInputTypeValue(), TextInputType::NUMBER);
}

/**
 * @tc.name: SetType_valueOpt_not_value
 * @tc.desc: Test SearchModelStatic SetType
 * @tc.type: FUNC
 */
HWTEST_F(SearchModelStaticNg, SetType_valueOpt_not_value, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Search node
     */
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(DEFAULT_TEXT_U16, PLACEHOLDER_U16, SEARCH_SVG);
    auto searchNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(searchNode, nullptr);
    auto textFieldChild =
        FrameNode::CreateFrameNode(V2::SEARCH_Field_ETS_TAG, 1, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(textFieldChild, nullptr);
    RefPtr<TextFieldLayoutProperty> textFieldLayoutProperty = AceType::MakeRefPtr<TextFieldLayoutProperty>();
    textFieldChild->SetLayoutProperty(textFieldLayoutProperty);
    auto layoutProperty = textFieldChild->GetLayoutProperty<TextFieldLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    searchNode->children_ = { textFieldChild };

    /**
     * @tc.steps: step2. Get layoutProperty and call SetType
     * @tc.expected: GetTextInputType().has_value() return false
     */
    std::optional<TextInputType> valueOpt = std::nullopt;
    SearchModelStatic::SetType(searchNode, valueOpt);
    EXPECT_FALSE(layoutProperty->GetTextInputType().has_value());
}

/**
 * @tc.name: SetType_HasTextInputType_not_equal_UNSPECIFIED
 * @tc.desc: Test SearchModelStatic SetType
 * @tc.type: FUNC
 */
HWTEST_F(SearchModelStaticNg, SetType_HasTextInputType_not_equal_UNSPECIFIED, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Search node
     */
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(DEFAULT_TEXT_U16, PLACEHOLDER_U16, SEARCH_SVG);
    auto searchNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(searchNode, nullptr);
    auto textFieldChild =
        FrameNode::CreateFrameNode(V2::SEARCH_Field_ETS_TAG, 1, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(textFieldChild, nullptr);
    auto pattern = textFieldChild->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->SetIsFilterChanged(false);
    EXPECT_FALSE(pattern->isFilterChanged_);
    RefPtr<TextFieldLayoutProperty> textFieldLayoutProperty = AceType::MakeRefPtr<TextFieldLayoutProperty>();
    textFieldChild->SetLayoutProperty(textFieldLayoutProperty);
    auto layoutProperty = textFieldChild->GetLayoutProperty<TextFieldLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateTextInputType(TextInputType::USER_NAME);
    searchNode->children_ = { textFieldChild };

    /**
     * @tc.steps: step2. Get layoutProperty and call SetType
     * @tc.expected: GetTypeChanged() return true and isFilterChanged_ return true
     */
    std::optional<TextInputType> valueOpt = std::nullopt;
    SearchModelStatic::SetType(searchNode, valueOpt);
    EXPECT_TRUE(layoutProperty->GetTypeChanged());
    EXPECT_TRUE(pattern->isFilterChanged_);
}

/**
 * @tc.name: SetType_HasTextInputType_equal_UNSPECIFIED
 * @tc.desc: Test SearchModelStatic SetType
 * @tc.type: FUNC
 */
HWTEST_F(SearchModelStaticNg, SetType_HasTextInputType_equal_UNSPECIFIED, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Search node
     */
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(DEFAULT_TEXT_U16, PLACEHOLDER_U16, SEARCH_SVG);
    auto searchNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(searchNode, nullptr);
    auto textFieldChild =
        FrameNode::CreateFrameNode(V2::SEARCH_Field_ETS_TAG, 1, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(textFieldChild, nullptr);
    auto pattern = textFieldChild->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->SetIsFilterChanged(false);
    EXPECT_FALSE(pattern->isFilterChanged_);
    RefPtr<TextFieldLayoutProperty> textFieldLayoutProperty = AceType::MakeRefPtr<TextFieldLayoutProperty>();
    textFieldChild->SetLayoutProperty(textFieldLayoutProperty);
    auto layoutProperty = textFieldChild->GetLayoutProperty<TextFieldLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateTextInputType(TextInputType::UNSPECIFIED);
    searchNode->children_ = { textFieldChild };

    /**
     * @tc.steps: step2. Get layoutProperty and call SetType
     * @tc.expected: GetTextInputType().has_value() return false
     */
    std::optional<TextInputType> valueOpt = std::nullopt;
    SearchModelStatic::SetType(searchNode, valueOpt);
    EXPECT_FALSE(layoutProperty->GetTextInputType().has_value());
}

/**
 * @tc.name: SetType_HasTextInputType_False
 * @tc.desc: Test SearchModelStatic SetType
 * @tc.type: FUNC
 */
HWTEST_F(SearchModelStaticNg, SetType_HasTextInputType_False, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Search node
     */
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(DEFAULT_TEXT_U16, PLACEHOLDER_U16, SEARCH_SVG);
    auto searchNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(searchNode, nullptr);
    auto textFieldChild =
        FrameNode::CreateFrameNode(V2::SEARCH_Field_ETS_TAG, 1, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(textFieldChild, nullptr);
    auto pattern = textFieldChild->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->SetIsFilterChanged(false);
    RefPtr<TextFieldLayoutProperty> textFieldLayoutProperty = AceType::MakeRefPtr<TextFieldLayoutProperty>();
    textFieldChild->SetLayoutProperty(textFieldLayoutProperty);
    auto layoutProperty = textFieldChild->GetLayoutProperty<TextFieldLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    searchNode->children_ = { textFieldChild };

    /**
     * @tc.steps: step2. Get layoutProperty and call SetType
     * @tc.expected: GetTextInputType().has_value() return false
     */
    std::optional<TextInputType> valueOpt = std::nullopt;
    SearchModelStatic::SetType(searchNode, valueOpt);
    EXPECT_FALSE(pattern->isFilterChanged_);
    EXPECT_FALSE(layoutProperty->GetTextInputType().has_value());
}

/**
 * @tc.name: SetStopBackPress_valueOpt_has_value
 * @tc.desc: Test SearchModelStatic SetStopBackPress
 * @tc.type: FUNC
 */
HWTEST_F(SearchModelStaticNg, SetStopBackPress_valueOpt_has_value, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Search node
     */
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(DEFAULT_TEXT_U16, PLACEHOLDER_U16, SEARCH_SVG);
    auto searchNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(searchNode, nullptr);
    auto textFieldChild =
        FrameNode::CreateFrameNode(V2::SEARCH_Field_ETS_TAG, 1, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(textFieldChild, nullptr);
    RefPtr<TextFieldLayoutProperty> textFieldLayoutProperty = AceType::MakeRefPtr<TextFieldLayoutProperty>();
    textFieldChild->SetLayoutProperty(textFieldLayoutProperty);
    auto layoutProperty = textFieldChild->GetLayoutProperty<TextFieldLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    searchNode->children_ = { textFieldChild };

    /**
     * @tc.steps: step2. Get layoutProperty and call SetStopBackPress
     * @tc.expected: GetStopBackPress() return true
     */
    auto valueOpt = std::make_optional<bool>(true);
    SearchModelStatic::SetStopBackPress(searchNode, valueOpt);
    EXPECT_TRUE(layoutProperty->GetStopBackPress());
}

/**
 * @tc.name: SetStopBackPress_valueOpt_not_value
 * @tc.desc: Test SearchModelStatic SetStopBackPress
 * @tc.type: FUNC
 */
HWTEST_F(SearchModelStaticNg, SetStopBackPress_valueOpt_not_value, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Search node
     */
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(DEFAULT_TEXT_U16, PLACEHOLDER_U16, SEARCH_SVG);
    auto searchNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(searchNode, nullptr);
    auto textFieldChild =
        FrameNode::CreateFrameNode(V2::SEARCH_Field_ETS_TAG, 1, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(textFieldChild, nullptr);
    RefPtr<TextFieldLayoutProperty> textFieldLayoutProperty = AceType::MakeRefPtr<TextFieldLayoutProperty>();
    textFieldChild->SetLayoutProperty(textFieldLayoutProperty);
    auto layoutProperty = textFieldChild->GetLayoutProperty<TextFieldLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    searchNode->children_ = { textFieldChild };

    /**
     * @tc.steps: step2. Get layoutProperty and call SetStopBackPress
     * @tc.expected: GetStopBackPress().has_value() return false
     */
    std::optional<bool> valueOpt = std::nullopt;
    SearchModelStatic::SetStopBackPress(searchNode, valueOpt);
    EXPECT_FALSE(layoutProperty->GetStopBackPress().has_value());
}

/**
 * @tc.name: SetOnChangeEvent_onChangeEvent_true
 * @tc.desc: Test SearchModelStatic SetOnChangeEvent
 * @tc.type: FUNC
 */
HWTEST_F(SearchModelStaticNg, SetOnChangeEvent_onChangeEvent_true, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Search node
     */
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(DEFAULT_TEXT_U16, PLACEHOLDER_U16, SEARCH_SVG);
    auto searchNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(searchNode, nullptr);
    auto textFieldChild =
        FrameNode::CreateFrameNode(V2::SEARCH_Field_ETS_TAG, 1, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(textFieldChild, nullptr);
    auto pattern = textFieldChild->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    RefPtr<TextFieldEventHub> textFieldEventHub = AceType::MakeRefPtr<TextFieldEventHub>();
    textFieldChild->eventHub_ = textFieldEventHub;
    auto eventHub = textFieldChild->GetEventHub<TextFieldEventHub>();
    ASSERT_NE(eventHub, nullptr);
    searchNode->children_ = { textFieldChild };

    /**
     * @tc.steps: step2. Call SetOnChangeEvent and trigger onChange
     * @tc.expected: onChangeEventFlag return true after onChange called
     */
    bool onChangeEventFlag = false;
    std::function<void(const std::u16string&)> onChangeEvent = [&onChangeEventFlag](const std::u16string& text) {
        onChangeEventFlag = true;
    };
    SearchModelStatic::SetOnChangeEvent(searchNode, std::move(onChangeEvent));
    auto onChange = eventHub->onValueChangeEvent_;
    std::u16string value = u"test";
    onChange(value);
    EXPECT_EQ(onChangeEventFlag, true);
}

/**
 * @tc.name: RequestKeyboardOnFocus_has_value_true
 * @tc.desc: Test SearchModelStatic RequestKeyboardOnFocus
 * @tc.type: FUNC
 */
HWTEST_F(SearchModelStaticNg, RequestKeyboardOnFocus_has_value_true, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Search node
     */
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(DEFAULT_TEXT_U16, PLACEHOLDER_U16, SEARCH_SVG);
    auto searchNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(searchNode, nullptr);
    auto textFieldChild =
        FrameNode::CreateFrameNode(V2::SEARCH_Field_ETS_TAG, 1, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(textFieldChild, nullptr);
    auto pattern = textFieldChild->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    searchNode->children_ = { textFieldChild };

    /**
     * @tc.steps: step2. Get pattern and call RequestKeyboardOnFocus
     * @tc.expected: NeedToRequestKeyboardOnFocus() return false
     */
    auto needToRequest = std::make_optional<bool>(false);
    SearchModelStatic::RequestKeyboardOnFocus(searchNode, needToRequest);
    EXPECT_FALSE(pattern->NeedToRequestKeyboardOnFocus());
}

/**
 * @tc.name: RequestKeyboardOnFocus_has_value_false
 * @tc.desc: Test SearchModelStatic RequestKeyboardOnFocus
 * @tc.type: FUNC
 */
HWTEST_F(SearchModelStaticNg, RequestKeyboardOnFocus_has_value_false, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Search node
     */
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(DEFAULT_TEXT_U16, PLACEHOLDER_U16, SEARCH_SVG);
    auto searchNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(searchNode, nullptr);
    auto textFieldChild =
        FrameNode::CreateFrameNode(V2::SEARCH_Field_ETS_TAG, 1, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(textFieldChild, nullptr);
    auto pattern = textFieldChild->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    searchNode->children_ = { textFieldChild };

    /**
     * @tc.steps: step2. Get pattern and call RequestKeyboardOnFocus
     * @tc.expected: NeedToRequestKeyboardOnFocus() return true
     */
    std::optional<bool> needToRequest = std::nullopt;
    SearchModelStatic::RequestKeyboardOnFocus(searchNode, needToRequest);
    EXPECT_TRUE(pattern->NeedToRequestKeyboardOnFocus());
}

/**
 * @tc.name: SetSelectionMenuHidden_has_value_true
 * @tc.desc: Test SearchModelStatic SetSelectionMenuHidden
 * @tc.type: FUNC
 */
HWTEST_F(SearchModelStaticNg, SetSelectionMenuHidden_has_value_true, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Search node
     */
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(DEFAULT_TEXT_U16, PLACEHOLDER_U16, SEARCH_SVG);
    auto searchNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(searchNode, nullptr);
    auto textFieldChild =
        FrameNode::CreateFrameNode(V2::SEARCH_Field_ETS_TAG, 1, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(textFieldChild, nullptr);
    RefPtr<TextFieldLayoutProperty> textFieldLayoutProperty = AceType::MakeRefPtr<TextFieldLayoutProperty>();
    textFieldChild->SetLayoutProperty(textFieldLayoutProperty);
    auto layoutProperty = textFieldChild->GetLayoutProperty<TextFieldLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    searchNode->children_ = { textFieldChild };

    /**
     * @tc.steps: step2. Get layoutProperty and call SetSelectionMenuHidden
     * @tc.expected: GetSelectionMenuHidden().value() return true
     */
    auto selectionMenuHidden = std::make_optional<bool>(true);
    SearchModelStatic::SetSelectionMenuHidden(searchNode, selectionMenuHidden);
    EXPECT_TRUE(layoutProperty->GetSelectionMenuHidden().value());
}

/**
 * @tc.name: SetSelectionMenuHidden_has_value_false
 * @tc.desc: Test SearchModelStatic SetSelectionMenuHidden
 * @tc.type: FUNC
 */
HWTEST_F(SearchModelStaticNg, SetSelectionMenuHidden_has_value_false, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Search node
     */
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(DEFAULT_TEXT_U16, PLACEHOLDER_U16, SEARCH_SVG);
    auto searchNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(searchNode, nullptr);
    auto textFieldChild =
        FrameNode::CreateFrameNode(V2::SEARCH_Field_ETS_TAG, 1, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(textFieldChild, nullptr);
    RefPtr<TextFieldLayoutProperty> textFieldLayoutProperty = AceType::MakeRefPtr<TextFieldLayoutProperty>();
    textFieldChild->SetLayoutProperty(textFieldLayoutProperty);
    auto layoutProperty = textFieldChild->GetLayoutProperty<TextFieldLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    searchNode->children_ = { textFieldChild };

    /**
     * @tc.steps: step2. Get layoutProperty and call SetSelectionMenuHidden
     * @tc.expected: GetSelectionMenuHidden().value() return false
     */
    std::optional<bool> selectionMenuHidden = std::nullopt;
    SearchModelStatic::SetSelectionMenuHidden(searchNode, selectionMenuHidden);
    EXPECT_FALSE(layoutProperty->GetSelectionMenuHidden().value());
}

/**
 * @tc.name: SetEnablePreviewText_has_value_true
 * @tc.desc: Test SearchModelStatic SetEnablePreviewText
 * @tc.type: FUNC
 */
HWTEST_F(SearchModelStaticNg, SetEnablePreviewText_has_value_true, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Search node
     */
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(DEFAULT_TEXT_U16, PLACEHOLDER_U16, SEARCH_SVG);
    auto searchNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(searchNode, nullptr);
    auto textFieldChild =
        FrameNode::CreateFrameNode(V2::SEARCH_Field_ETS_TAG, 1, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(textFieldChild, nullptr);
    auto pattern = textFieldChild->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    searchNode->children_ = { textFieldChild };

    /**
     * @tc.steps: step2. Get pattern and call SetEnablePreviewText
     * @tc.expected: GetSupportPreviewText() return false
     */
    auto enablePreviewText = std::make_optional<bool>(false);
    SearchModelStatic::SetEnablePreviewText(searchNode, enablePreviewText);
    EXPECT_FALSE(pattern->GetSupportPreviewText());
}

/**
 * @tc.name: SetEnablePreviewText_has_value_false
 * @tc.desc: Test SearchModelStatic SetEnablePreviewText
 * @tc.type: FUNC
 */
HWTEST_F(SearchModelStaticNg, SetEnablePreviewText_has_value_false, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Search node
     */
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(DEFAULT_TEXT_U16, PLACEHOLDER_U16, SEARCH_SVG);
    auto searchNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(searchNode, nullptr);
    auto textFieldChild =
        FrameNode::CreateFrameNode(V2::SEARCH_Field_ETS_TAG, 1, AceType::MakeRefPtr<TextFieldPattern>());
    ASSERT_NE(textFieldChild, nullptr);
    auto pattern = textFieldChild->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    searchNode->children_ = { textFieldChild };

    /**
     * @tc.steps: step2. Get pattern and call SetEnablePreviewText
     * @tc.expected: GetSupportPreviewText() return true
     */
    std::optional<bool> enablePreviewText = std::nullopt;
    SearchModelStatic::SetEnablePreviewText(searchNode, enablePreviewText);
    EXPECT_TRUE(pattern->GetSupportPreviewText());
}
} // namespace OHOS::Ace::NG