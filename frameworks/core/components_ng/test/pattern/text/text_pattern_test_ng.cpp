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

#include <optional>

#include "gtest/gtest.h"

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/pattern/text/text_model_ng.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
const std::string CREATE_VALUE = "Hello World";
const Dimension FONT_SIZE_VALUE = Dimension(20.1, DimensionUnit::PX);
const Color TEXT_COLOR_VALUE = Color::FromRGB(255, 100, 100);
const Ace::FontStyle ITALIC_FONT_STYLE_VALUE = Ace::FontStyle::ITALIC;
const Ace::FontWeight FONT_WEIGHT_VALUE = Ace::FontWeight::W100;
const std::vector<std::string> FONT_FAMILY_VALUE = { "cursive" };
const Ace::TextAlign TEXT_ALIGN_VALUE = Ace::TextAlign::CENTER;
const Ace::TextOverflow TEXT_OVERFLOW_VALUE = Ace::TextOverflow::CLIP;
const uint32_t MAX_LINES_VALUE = 10;
const Dimension LINE_HEIGHT_VALUE = Dimension(20.1, DimensionUnit::PX);
const Ace::TextDecoration TEXT_DECORATION_VALUE = Ace::TextDecoration::INHERIT;
const Color TEXT_DECORATION_COLOR_VALUE = Color::FromRGB(255, 100, 100);
const Dimension BASELINE_OFFSET_VALUE = Dimension(20.1, DimensionUnit::PX);
const Ace::TextCase TEXT_CASE_VALUE = Ace::TextCase::LOWERCASE;
const Dimension ADAPT_MIN_FONT_SIZE_VALUE = Dimension(50, DimensionUnit::PX);
const Dimension ADAPT_MAX_FONT_SIZE_VALUE = Dimension(200, DimensionUnit::PX);
} // namespace

struct TestProperty {
    std::optional<Dimension> fontSizeValue = std::nullopt;
    std::optional<Color> textColorValue = std::nullopt;
    std::optional<Ace::FontStyle> italicFontStyleValue = std::nullopt;
    std::optional<Ace::FontWeight> fontWeightValue = std::nullopt;
    std::optional<std::vector<std::string>> fontFamilyValue = std::nullopt;
    std::optional<Ace::TextAlign> textAlignValue = std::nullopt;
    std::optional<Ace::TextOverflow> textOverflowValue = std::nullopt;
    std::optional<uint32_t> maxLinesValue = std::nullopt;
    std::optional<Dimension> lineHeightValue = std::nullopt;
    std::optional<Ace::TextDecoration> textDecorationValue = std::nullopt;
    std::optional<Color> textDecorationColorValue = std::nullopt;
    std::optional<Dimension> baselineOffsetValue = std::nullopt;
    std::optional<Ace::TextCase> textCaseValue = std::nullopt;
    std::optional<Dimension> adaptMinFontSize = std::nullopt;
    std::optional<Dimension> adaptMaxFontSize = std::nullopt;
};

class TextPatternTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;

protected:
    static RefPtr<FrameNode> CreateTextParagraph(const std::string& createValue, const TestProperty& testProperty);
};

void TextPatternTestNg::SetUpTestCase() {}
void TextPatternTestNg::TearDownTestCase() {}
void TextPatternTestNg::SetUp() {}
void TextPatternTestNg::TearDown() {}

RefPtr<FrameNode> TextPatternTestNg::CreateTextParagraph(
    const std::string& createValue, const TestProperty& testProperty)
{
    TextModelNG textModel;
    textModel.Create(createValue);
    if (testProperty.fontSizeValue.has_value()) {
        textModel.SetFontSize(testProperty.fontSizeValue.value());
    }
    if (testProperty.textColorValue.has_value()) {
        textModel.SetTextColor(testProperty.textColorValue.value());
    }
    if (testProperty.italicFontStyleValue.has_value()) {
        textModel.SetItalicFontStyle(testProperty.italicFontStyleValue.value());
    }
    if (testProperty.fontWeightValue.has_value()) {
        textModel.SetFontWeight(testProperty.fontWeightValue.value());
    }
    if (testProperty.fontFamilyValue.has_value()) {
        textModel.SetFontFamily(testProperty.fontFamilyValue.value());
    }
    if (testProperty.textAlignValue.has_value()) {
        textModel.SetTextAlign(testProperty.textAlignValue.value());
    }
    if (testProperty.textOverflowValue.has_value()) {
        textModel.SetTextOverflow(testProperty.textOverflowValue.value());
    }
    if (testProperty.maxLinesValue.has_value()) {
        textModel.SetMaxLines(testProperty.maxLinesValue.value());
    }
    if (testProperty.lineHeightValue.has_value()) {
        textModel.SetLineHeight(testProperty.lineHeightValue.value());
    }
    if (testProperty.textDecorationValue.has_value()) {
        textModel.SetTextDecoration(testProperty.textDecorationValue.value());
    }
    if (testProperty.textDecorationColorValue.has_value()) {
        textModel.SetTextDecorationColor(testProperty.textDecorationColorValue.value());
    }
    if (testProperty.baselineOffsetValue.has_value()) {
        textModel.SetBaselineOffset(testProperty.baselineOffsetValue.value());
    }
    if (testProperty.textCaseValue.has_value()) {
        textModel.SetTextCase(testProperty.textCaseValue.value());
    }
    if (testProperty.adaptMinFontSize.has_value()) {
        textModel.SetAdaptMinFontSize(testProperty.adaptMinFontSize.value());
    }
    if (testProperty.adaptMaxFontSize.has_value()) {
        textModel.SetAdaptMaxFontSize(testProperty.adaptMaxFontSize.value());
    }

    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish(); // TextView pop
    return AceType::DynamicCast<FrameNode>(element);
}

/**
 * @tc.name: TextFrameNodeCreator001
 * @tc.desc: Test all the properties of text.
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, TextFrameNodeCreator001, TestSize.Level1)
{
    TestProperty testProperty;
    testProperty.fontSizeValue = std::make_optional(FONT_SIZE_VALUE);
    testProperty.textColorValue = std::make_optional(TEXT_COLOR_VALUE);
    testProperty.italicFontStyleValue = std::make_optional(ITALIC_FONT_STYLE_VALUE);
    testProperty.fontWeightValue = std::make_optional(FONT_WEIGHT_VALUE);
    testProperty.fontFamilyValue = std::make_optional(FONT_FAMILY_VALUE);
    testProperty.textAlignValue = std::make_optional(TEXT_ALIGN_VALUE);
    testProperty.textOverflowValue = std::make_optional(TEXT_OVERFLOW_VALUE);
    testProperty.maxLinesValue = std::make_optional(MAX_LINES_VALUE);
    testProperty.lineHeightValue = std::make_optional(LINE_HEIGHT_VALUE);
    testProperty.textDecorationValue = std::make_optional(TEXT_DECORATION_VALUE);
    testProperty.textDecorationColorValue = std::make_optional(TEXT_DECORATION_COLOR_VALUE);
    testProperty.baselineOffsetValue = std::make_optional(BASELINE_OFFSET_VALUE);
    testProperty.textCaseValue = std::make_optional(TEXT_CASE_VALUE);
    testProperty.adaptMinFontSize = std::make_optional(ADAPT_MIN_FONT_SIZE_VALUE);
    testProperty.adaptMaxFontSize = std::make_optional(ADAPT_MAX_FONT_SIZE_VALUE);

    RefPtr<FrameNode> frameNode = CreateTextParagraph(CREATE_VALUE, testProperty);
    EXPECT_EQ(frameNode == nullptr, false);
    RefPtr<LayoutProperty> layoutProperty = frameNode->GetLayoutProperty();
    EXPECT_EQ(layoutProperty == nullptr, false);
    RefPtr<TextLayoutProperty> textLayoutProperty = AceType::DynamicCast<TextLayoutProperty>(layoutProperty);
    EXPECT_EQ(textLayoutProperty == nullptr, false);
    EXPECT_EQ(textLayoutProperty->GetContentValue(), CREATE_VALUE);
    const std::unique_ptr<FontStyle>& fontStyle = textLayoutProperty->GetFontStyle();
    EXPECT_EQ(fontStyle == nullptr, false);
    const std::unique_ptr<TextLineStyle>& textLineStyle = textLayoutProperty->GetTextLineStyle();
    EXPECT_EQ(textLineStyle == nullptr, false);
    TextStyle textStyle = CreateTextStyleUsingTheme(fontStyle, textLineStyle, nullptr);
    EXPECT_EQ(textStyle.GetFontSize(), FONT_SIZE_VALUE);
    EXPECT_EQ(textStyle.GetTextColor(), TEXT_COLOR_VALUE);
    EXPECT_EQ(textStyle.GetFontStyle(), ITALIC_FONT_STYLE_VALUE);
    EXPECT_EQ(textStyle.GetFontWeight(), FONT_WEIGHT_VALUE);
    EXPECT_EQ(textStyle.GetFontFamilies(), FONT_FAMILY_VALUE);
    EXPECT_EQ(textStyle.GetTextAlign(), TEXT_ALIGN_VALUE);
    EXPECT_EQ(textStyle.GetTextOverflow(), TEXT_OVERFLOW_VALUE);
    EXPECT_EQ(textStyle.GetMaxLines(), MAX_LINES_VALUE);
    EXPECT_EQ(textStyle.GetLineHeight(), LINE_HEIGHT_VALUE);
    EXPECT_EQ(textStyle.GetTextDecoration(), TEXT_DECORATION_VALUE);
    EXPECT_EQ(textStyle.GetTextDecorationColor(), TEXT_DECORATION_COLOR_VALUE);
    EXPECT_EQ(textStyle.GetBaselineOffset(), BASELINE_OFFSET_VALUE);
    EXPECT_EQ(textStyle.GetTextCase(), TEXT_CASE_VALUE);
    EXPECT_EQ(textStyle.GetAdaptMinFontSize(), ADAPT_MIN_FONT_SIZE_VALUE);
    EXPECT_EQ(textStyle.GetAdaptMaxFontSize(), ADAPT_MAX_FONT_SIZE_VALUE);
    EXPECT_EQ(textStyle.GetAdaptTextSize(),
        testProperty.adaptMinFontSize.has_value() || testProperty.adaptMaxFontSize.has_value());
}
} // namespace OHOS::Ace::NG
