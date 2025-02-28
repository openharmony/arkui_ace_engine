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

#include "test/unittest/adapter/ohos/capability/convert_test_tools.h"

#undef private
#undef protected

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {

namespace {
    std::string testStr[] = { "微软雅黑", "宋体", "Times New Roman", "未知字体", "Unknow", "楷体"};
    Font testFont1 { OHOS::Ace::FontWeight::BOLDER, Dimension(0.0, DimensionUnit::VP), OHOS::Ace::FontStyle::NORMAL,
        std::vector<std::string>(testStr, testStr + 5), OHOS::Ace::Color::WHITE };
    Font testFont2 { OHOS::Ace::FontWeight::LIGHTER, Dimension(20.0, DimensionUnit::PX), OHOS::Ace::FontStyle::ITALIC,
        std::vector<std::string>(testStr, testStr + 5), OHOS::Ace::Color::BLACK };
}

// imageOption1: default parameter
auto imageOption1 = HtmlConvertTestNg::GetImageOption(
    "src/icon-1.png",
    Dimension(50.0, DimensionUnit::VP),
    Dimension(50.0, DimensionUnit::VP)
);

// imageOption2: define ImageFit, VerticalAlign and BorderRadiusProperty
auto imageOption2 = HtmlConvertTestNg::GetImageOption(
    "src/icon-2.png",
    Dimension(100.0, DimensionUnit::VP),
    Dimension(100.0, DimensionUnit::VP),
    ImageFit::COVER,
    VerticalAlign::TOP,
    BorderRadiusProperty(Dimension(10.0, DimensionUnit::VP))
);

// imageOption3: ImageFit, VerticalAlign and BorderRadiusProperty set 2
auto imageOption3 = HtmlConvertTestNg::GetImageOption(
    "src/icon-3.png",
    Dimension(75.0, DimensionUnit::VP),
    Dimension(75.0, DimensionUnit::VP),
    ImageFit::FILL,
    VerticalAlign::BOTTOM,
    BorderRadiusProperty(Dimension(5.0, DimensionUnit::VP))
);

// imageOption3: ImageFit, VerticalAlign and BorderRadiusProperty set 3
auto imageOption4 = HtmlConvertTestNg::GetImageOption(
    "src/icon-4.png",
    Dimension(150.0, DimensionUnit::VP),
    Dimension(150.0, DimensionUnit::VP),
    ImageFit::NONE,
    VerticalAlign::CENTER,
    BorderRadiusProperty(Dimension(20.0, DimensionUnit::VP))
);

/**
 * @tc.name: HtmlConvert000
 * @tc.desc: This test case verifies the conversion of a simple SpanString (without complex styles)
 *           to TLV format, HTML format, and back to SpanString. It ensures the conversion
 *           maintains the integrity of the content and results in identical HTML outputs after
 *           multiple conversions.
 * @tc.level: 1
 */
HWTEST_F(HtmlConvertTestNg, HtmlConvert000, TestSize.Level1)
{
    /**
     * @tc.steps1: Create a simple SpanString with basic text content.
     * @tc.expected: The SpanString should be successfully created without any errors.
     */
    auto spanString = AceType::MakeRefPtr<SpanString>(u"Hello");

    /**
     * @tc.steps2: Convert the SpanString to TLV format and ensure the result is not empty.
     * @tc.expected: TLV format conversion should produce a non-empty result.
     */
    std::vector<uint8_t> buff;
    spanString->EncodeTlv(buff);
    EXPECT_EQ(buff.size() > 0, true);

    /**
     * @tc.steps3: Convert the TLV format back to HTML and compare it with the direct HTML conversion
     *             of the SpanString.
     * @tc.expected: The HTML results from both methods should be identical.
     */
    SpanToHtml toHtml;
    auto htmlFromU8 = toHtml.ToHtml(buff);
    auto htmlFromSpan = toHtml.ToHtml(*spanString);
    EXPECT_EQ(htmlFromU8, htmlFromSpan);

    /**
     * @tc.steps4: Convert the HTML back to SpanString and verify that the items match.
     * @tc.expected: The SpanString items after conversion should be identical to the original.
     */
    HtmlToSpan toSpan;
    auto spanFromHtml = toSpan.ToSpanString(htmlFromU8);
    EXPECT_EQ(IsSpanItemSame(spanFromHtml->GetSpanItems(), spanString->GetSpanItems()), true);

    /**
     * @tc.steps5: Convert the SpanString back to HTML and verify consistency.
     * @tc.expected: The final HTML should match the HTML obtained earlier.
     */
    SpanToHtml toHtml1;
    auto hmtlString = toHtml1.ToHtml(*spanFromHtml);
    EXPECT_EQ(hmtlString, htmlFromSpan);
}

/**
 * @tc.name: HtmlConvert001
 * @tc.desc: This test case checks the conversion of a SpanString with different font styles applied
 *           to different parts of the text. The test ensures that font spans are correctly applied
 *           during conversion to TLV, HTML, and back to SpanString.
 * @tc.level: 1
 */
HWTEST_F(HtmlConvertTestNg, HtmlConvert001, TestSize.Level1)
{
    /**
     * @tc.steps1: Create a SpanString with text and apply font styles to different ranges.
     * @tc.expected: Font styles should be applied correctly to the specified ranges.
     */
    auto spanString = AceType::MakeRefPtr<SpanString>(u"Hello World");
    spanString->AddSpan(AceType::MakeRefPtr<FontSpan>(testFont1, 0, 5));
    spanString->AddSpan(AceType::MakeRefPtr<FontSpan>(testFont2, 6, 11));

    /**
     * @tc.steps2: Convert the SpanString to TLV format and ensure the result is not empty.
     * @tc.expected: TLV format conversion should produce a non-empty result.
     */
    std::vector<uint8_t> buff;
    spanString->EncodeTlv(buff);
    EXPECT_EQ(buff.size() > 0, true);

    /**
     * @tc.steps3: Convert the TLV format back to HTML and compare it with the direct HTML conversion
     *             of the SpanString.
     * @tc.expected: The HTML results from both methods should be identical.
     */
    SpanToHtml toHtml;
    auto htmlFromU8 = toHtml.ToHtml(buff);
    auto htmlFromSpan = toHtml.ToHtml(*spanString);
    EXPECT_EQ(htmlFromU8, htmlFromSpan);

    /**
     * @tc.steps4: Convert the HTML back to SpanString and verify that the items match.
     * @tc.expected: The SpanString items after conversion should be identical to the original.
     */
    HtmlToSpan toSpan;
    auto spanFromHtml = toSpan.ToSpanString(htmlFromU8);
    EXPECT_EQ(IsSpanItemSame(spanFromHtml->GetSpanItems(), spanString->GetSpanItems()), true);

    /**
     * @tc.steps5: Convert the SpanString back to HTML and verify consistency.
     * @tc.expected: The final HTML should match the HTML obtained earlier.
     */
    SpanToHtml toHtml1;
    auto hmtlString = toHtml1.ToHtml(*spanFromHtml);
    EXPECT_EQ(hmtlString, htmlFromSpan);
}

/**
 * @tc.name: HtmlConvert002
 * @tc.desc: This test case checks the conversion of a SpanString with letter spacing applied to
 *           different parts of the text. The test ensures that letter spacing is correctly applied
 *           during conversion to TLV, HTML, and back to SpanString.
 * @tc.level: 1
 */
HWTEST_F(HtmlConvertTestNg, HtmlConvert002, TestSize.Level1)
{
    /**
     * @tc.steps1: Create a SpanString with text and apply letter spacing to different ranges.
     * @tc.expected: Letter spacing should be applied correctly to the specified ranges.
     */
    auto spanString = AceType::MakeRefPtr<SpanString>(u"Hello World");
    spanString->AddSpan(AceType::MakeRefPtr<LetterSpacingSpan>(Dimension(2), 0, 5));
    spanString->AddSpan(AceType::MakeRefPtr<LetterSpacingSpan>(Dimension(3), 6, 11));

    /**
     * @tc.steps2: Convert the SpanString to TLV format and ensure the result is not empty.
     * @tc.expected: TLV format conversion should produce a non-empty result.
     */
    std::vector<uint8_t> buff;
    spanString->EncodeTlv(buff);
    EXPECT_EQ(buff.size() > 0, true);

    /**
     * @tc.steps3: Convert the TLV format back to HTML and compare it with the direct HTML conversion
     *             of the SpanString.
     * @tc.expected: The HTML results from both methods should be identical.
     */
    SpanToHtml toHtml;
    auto htmlFromU8 = toHtml.ToHtml(buff);
    auto htmlFromSpan = toHtml.ToHtml(*spanString);
    EXPECT_EQ(htmlFromU8, htmlFromSpan);

    /**
     * @tc.steps4: Convert the HTML back to SpanString and verify that the items match.
     * @tc.expected: The SpanString items after conversion should be identical to the original.
     */
    HtmlToSpan toSpan;
    auto spanFromHtml = toSpan.ToSpanString(htmlFromU8);
    EXPECT_EQ(IsSpanItemSame(spanFromHtml->GetSpanItems(), spanString->GetSpanItems()), true);

    /**
     * @tc.steps5: Convert the SpanString back to HTML and verify consistency.
     * @tc.expected: The final HTML should match the HTML obtained earlier.
     */
    SpanToHtml toHtml1;
    auto hmtlString = toHtml1.ToHtml(*spanFromHtml);
    EXPECT_EQ(hmtlString, htmlFromSpan);
}

/**
 * @tc.name: HtmlConvert003
 * @tc.desc: This test case checks the conversion of a SpanString with background color and text
 *           shadow applied to different parts of the text. It ensures that background and shadow
 *           styles are properly converted between TLV, HTML, and SpanString formats.
 * @tc.level: 1
 */
HWTEST_F(HtmlConvertTestNg, HtmlConvert003, TestSize.Level1)
{
    /**
     * @tc.steps1: Create a SpanString with text and apply background color and text shadow.
     * @tc.expected: Background color and text shadow should be applied correctly.
     */
    auto spanString = AceType::MakeRefPtr<SpanString>(u"Hello World");
    
    // Add background color
    NG::BorderRadiusProperty borderRadius;
    TextBackgroundStyle textBackgroundStyle;
    textBackgroundStyle.backgroundColor = Color::BLUE;
    textBackgroundStyle.backgroundRadius = borderRadius;
    spanString->AddSpan(AceType::MakeRefPtr<BackgroundColorSpan>(textBackgroundStyle, 0, 5));
    
    // Add text shadow
    Shadow shadow1;
    shadow1.SetBlurRadius(5.0);
    shadow1.SetColor(Color::RED);
    shadow1.SetOffsetX(2.0);
    shadow1.SetOffsetY(2.0);
    spanString->AddSpan(AceType::MakeRefPtr<TextShadowSpan>(std::vector<Shadow>{shadow1}, 6, 11));

    /**
     * @tc.steps2: Convert the SpanString to TLV format and ensure the result is not empty.
     * @tc.expected: TLV format conversion should produce a non-empty result.
     */
    std::vector<uint8_t> buff;
    spanString->EncodeTlv(buff);
    EXPECT_EQ(buff.size() > 0, true);

    /**
     * @tc.steps3: Convert the TLV format back to HTML and compare it with the direct HTML conversion
     *             of the SpanString.
     * @tc.expected: The HTML results from both methods should be identical.
     */
    SpanToHtml toHtml;
    auto htmlFromU8 = toHtml.ToHtml(buff);
    auto htmlFromSpan = toHtml.ToHtml(*spanString);
    EXPECT_EQ(htmlFromU8, htmlFromSpan);

    /**
     * @tc.steps4: Convert the HTML back to SpanString and verify that the items match.
     * @tc.expected: The SpanString items after conversion should be identical to the original.
     */
    HtmlToSpan toSpan;
    auto spanFromHtml = toSpan.ToSpanString(htmlFromU8);
    EXPECT_EQ(IsSpanItemSame(spanFromHtml->GetSpanItems(), spanString->GetSpanItems()), true);

    /**
     * @tc.steps5: Convert the SpanString back to HTML and verify consistency.
     * @tc.expected: The final HTML should match the HTML obtained earlier.
     */
    SpanToHtml toHtml1;
    auto hmtlString = toHtml1.ToHtml(*spanFromHtml);
    EXPECT_EQ(hmtlString, htmlFromSpan);
}

/**
 * @tc.name: HtmlConvert004
 * @tc.desc: This test case verifies the conversion of a SpanString with multiple complex styles
 *           (font, letter spacing, background color, and text shadow) applied to different
 *           parts of the text. It ensures the complex styles are applied correctly during conversion
 *           to TLV, HTML, and back to SpanString.
 * @tc.level: 1
 */
HWTEST_F(HtmlConvertTestNg, HtmlConvert004, TestSize.Level1)
{
    /**
     * @tc.steps1: Create a SpanString with various complex styles applied (font, letter spacing,
     *             background color, text shadow).
     * @tc.expected: All styles should be applied correctly to the specified ranges.
     */
    auto spanString = AceType::MakeRefPtr<SpanString>(u"Hello World Test with Styles");

    // Add fonts, letter spacing, background color, and text shadow
    spanString->AddSpan(AceType::MakeRefPtr<FontSpan>(testFont1, 0, 5));
    spanString->AddSpan(AceType::MakeRefPtr<FontSpan>(testFont2, 6, 11));
    spanString->AddSpan(AceType::MakeRefPtr<LetterSpacingSpan>(Dimension(2), 12, 17));

    NG::BorderRadiusProperty borderRadius;
    TextBackgroundStyle textBackgroundStyle;
    textBackgroundStyle.backgroundColor = Color::GREEN;
    textBackgroundStyle.backgroundRadius = borderRadius;
    spanString->AddSpan(AceType::MakeRefPtr<BackgroundColorSpan>(textBackgroundStyle, 0, 5));

    Shadow shadow1;
    shadow1.SetBlurRadius(5.0);
    shadow1.SetColor(Color::BLACK);
    shadow1.SetOffsetX(3.0);
    shadow1.SetOffsetY(3.0);
    spanString->AddSpan(AceType::MakeRefPtr<TextShadowSpan>(std::vector<Shadow>{shadow1}, 6, 11));

    /**
     * @tc.steps2: Convert the SpanString to TLV format and ensure the result is not empty.
     * @tc.expected: TLV format conversion should produce a non-empty result.
     */
    std::vector<uint8_t> buff;
    spanString->EncodeTlv(buff);
    EXPECT_EQ(buff.size() > 0, true);

    /**
     * @tc.steps3: Convert the TLV format back to HTML and compare it with the direct HTML conversion
     *             of the SpanString.
     * @tc.expected: The HTML results from both methods should be identical.
     */
    SpanToHtml toHtml;
    auto htmlFromU8 = toHtml.ToHtml(buff);
    auto htmlFromSpan = toHtml.ToHtml(*spanString);
    EXPECT_EQ(htmlFromU8, htmlFromSpan);

    /**
     * @tc.steps4: Convert the HTML back to SpanString and verify that the items match.
     * @tc.expected: The SpanString items after conversion should be identical to the original.
     */
    HtmlToSpan toSpan;
    auto spanFromHtml = toSpan.ToSpanString(htmlFromU8);
    EXPECT_EQ(IsSpanItemSame(spanFromHtml->GetSpanItems(), spanString->GetSpanItems()), true);

    /**
     * @tc.steps5: Convert the SpanString back to HTML and verify consistency.
     * @tc.expected: The final HTML should match the HTML obtained earlier.
     */
    SpanToHtml toHtml1;
    auto hmtlString = toHtml1.ToHtml(*spanFromHtml);
    EXPECT_EQ(hmtlString, htmlFromSpan);
}

/**
 * @tc.name: HtmlConvert005
 * @tc.desc: This test case checks the conversion of an empty SpanString. It ensures that an empty SpanString
 *           correctly converts to TLV and HTML formats without issues.
 * @tc.level: 1
 */
HWTEST_F(HtmlConvertTestNg, HtmlConvert005, TestSize.Level1)
{
    /**
     * @tc.steps1: Create an empty SpanString.
     * @tc.expected: The SpanString should remain empty and correctly handle conversion to TLV and HTML.
     */
    auto spanString = AceType::MakeRefPtr<SpanString>(u"");

    // Convert to TLV format
    std::vector<uint8_t> buff;
    spanString->EncodeTlv(buff);
    EXPECT_EQ(buff.size(), 13);

    /**
     * @tc.steps2: Convert the TLV buffer to HTML.
     * @tc.expected: The HTML string should match the result of directly converting the SpanString to HTML.
     */
    SpanToHtml toHtml;
    auto htmlFromU8 = toHtml.ToHtml(buff);
    auto htmlFromSpan = toHtml.ToHtml(*spanString);
    EXPECT_EQ(htmlFromU8, htmlFromSpan);

    /**
     * @tc.steps3: Convert the HTML back to SpanString and verify if it matches the original SpanString.
     * @tc.expected: The SpanString obtained from the HTML should match the original SpanString.
     */
    HtmlToSpan toSpan;
    auto spanFromHtml = toSpan.ToSpanString(htmlFromU8);
    EXPECT_EQ(IsSpanItemSame(spanFromHtml->GetSpanItems(), spanString->GetSpanItems()), true);

    /**
     * @tc.steps4: Convert back to HTML and verify that it matches the initial HTML result.
     * @tc.expected: The final HTML should match the HTML obtained earlier.
     */
    SpanToHtml toHtml1;
    auto hmtlString = toHtml1.ToHtml(*spanFromHtml);
    EXPECT_EQ(hmtlString, htmlFromSpan);
}

/**
 * @tc.name: HtmlConvert006
 * @tc.desc: This test case checks the conversion of a SpanString with overlapping styles applied in different ranges.
 *           It ensures that the overlapping styles are correctly maintained during the conversion process.
 * @tc.level: 1
 */
HWTEST_F(HtmlConvertTestNg, HtmlConvert006, TestSize.Level1)
{
    /**
     * @tc.steps1: Create a SpanString with overlapping styles (FontSpans).
     * @tc.expected: The SpanString should correctly handle overlapping styles and preserve them during conversion.
     */
    auto spanString = AceType::MakeRefPtr<SpanString>(u"Hello World");
    spanString->AddSpan(AceType::MakeRefPtr<FontSpan>(testFont1, 0, 5));
    spanString->AddSpan(AceType::MakeRefPtr<FontSpan>(testFont2, 3, 8));

    // Convert to TLV format
    std::vector<uint8_t> buff;
    spanString->EncodeTlv(buff);
    EXPECT_EQ(buff.size() > 0, true);

    /**
     * @tc.steps2: Convert the TLV buffer to HTML and compare with direct SpanString to HTML conversion.
     * @tc.expected: The converted HTML from TLV and direct SpanString should be identical.
     */
    SpanToHtml toHtml;
    auto htmlFromU8 = toHtml.ToHtml(buff);
    auto htmlFromSpan = toHtml.ToHtml(*spanString);
    EXPECT_EQ(htmlFromU8, htmlFromSpan);

    /**
     * @tc.steps3: Convert the HTML back to SpanString and validate that the spans are equivalent.
     * @tc.expected: The SpanString obtained from HTML should match the original SpanString.
     */
    HtmlToSpan toSpan;
    auto spanFromHtml = toSpan.ToSpanString(htmlFromU8);
    EXPECT_EQ(IsSpanItemSame(spanFromHtml->GetSpanItems(), spanString->GetSpanItems()), true);

    /**
     * @tc.steps4: Convert back to HTML and validate consistency with the initial HTML result.
     * @tc.expected: The final HTML should match the initial HTML obtained from the SpanString.
     */
    SpanToHtml toHtml1;
    auto hmtlString = toHtml1.ToHtml(*spanFromHtml);
    EXPECT_EQ(hmtlString, htmlFromSpan);
}

/**
 * @tc.name: HtmlConvert007
 * @tc.desc: This test case checks overlapping styles involving font spans and background color spans,
 *           ensuring that both styles are applied correctly and do not interfere with each other.
 * @tc.level: 1
 */
HWTEST_F(HtmlConvertTestNg, HtmlConvert007, TestSize.Level1)
{
    /**
     * @tc.steps1: Add font spans and background color spans with overlapping ranges.
     * @tc.expected: Both styles should be applied correctly without interference.
     */
    auto spanString = AceType::MakeRefPtr<SpanString>(u"Overlapping styles test");
    spanString->AddSpan(AceType::MakeRefPtr<FontSpan>(testFont1, 0, 10));
    TextBackgroundStyle bgStyle;
    bgStyle.backgroundColor = Color::GREEN;
    spanString->AddSpan(AceType::MakeRefPtr<BackgroundColorSpan>(bgStyle, 5, 15));

    /**
     * @tc.steps2: Convert the SpanString to TLV format and check the result.
     * @tc.expected: The TLV conversion should handle both font and background color styles correctly.
     */
    std::vector<uint8_t> buff;
    spanString->EncodeTlv(buff);
    EXPECT_GT(buff.size(), 0);

    /**
     * @tc.steps3: Convert the SpanString to HTML format and validate the output.
     * @tc.expected: The HTML conversion should match the expected HTML representation.
     */
    SpanToHtml toHtml;
    auto htmlFromSpan = toHtml.ToHtml(*spanString);

    /**
     * @tc.steps4: Convert the HTML back to SpanString and ensure consistency with the original SpanString.
     * @tc.expected: The SpanString obtained from HTML should match the original SpanString.
     */
    HtmlToSpan toSpan;
    auto spanFromHtml = toSpan.ToSpanString(htmlFromSpan);
    EXPECT_EQ(IsSpanItemSame(spanFromHtml->GetSpanItems(), spanString->GetSpanItems()), true);
}

/**
 * @tc.name: HtmlConvert008
 * @tc.desc: This test case checks the behavior of overlapping letter spacing and text shadow spans in a `SpanString`.
 *           It ensures that both styles work together without interfering with each other.
 * @tc.level: 1
 */
HWTEST_F(HtmlConvertTestNg, HtmlConvert008, TestSize.Level1)
{
    /**
     * @tc.steps1: Add letter spacing and text shadow spans with overlapping ranges.
     * @tc.expected: Both letter spacing and shadow effects should be applied correctly and not interfere.
     */
    auto spanString = AceType::MakeRefPtr<SpanString>(u"Letter spacing and shadow test");
    spanString->AddSpan(AceType::MakeRefPtr<LetterSpacingSpan>(Dimension(5), 0, 10));
    
    Shadow shadow1;
    shadow1.SetBlurRadius(5.0);
    shadow1.SetColor(Color::BLUE);
    shadow1.SetOffsetX(2.0);
    shadow1.SetOffsetY(2.0);
    spanString->AddSpan(AceType::MakeRefPtr<TextShadowSpan>(std::vector<Shadow>{shadow1}, 5, 15));

    /**
     * @tc.steps2: Convert the SpanString to TLV format and check the result.
     * @tc.expected: The conversion should handle both letter spacing and shadow effects correctly.
     */
    std::vector<uint8_t> buff;
    spanString->EncodeTlv(buff);
    EXPECT_GT(buff.size(), 0);

    /**
     * @tc.steps3: Convert the SpanString to HTML format and validate the result.
     * @tc.expected: The HTML conversion should correctly apply both the letter spacing and text shadow.
     */
    SpanToHtml toHtml;
    auto htmlFromSpan = toHtml.ToHtml(*spanString);

    /**
     * @tc.steps4: Convert the HTML back to SpanString and validate if it matches the original SpanString.
     * @tc.expected: The SpanString obtained from HTML should match the original SpanString.
     */
    HtmlToSpan toSpan;
    auto spanFromHtml = toSpan.ToSpanString(htmlFromSpan);
    EXPECT_EQ(IsSpanItemSame(spanFromHtml->GetSpanItems(), spanString->GetSpanItems()), true);
}

/**
 * @tc.name: HtmlConvert009
 * @tc.desc: This test case checks the overlapping of font spans and letter spacing spans in a `SpanString`.
 *           It ensures that both styles are applied correctly and do not interfere with each other.
 * @tc.level: 1
 */
HWTEST_F(HtmlConvertTestNg, HtmlConvert009, TestSize.Level1)
{
    /**
     * @tc.steps1: Add font and letter spacing spans with overlapping ranges.
     * @tc.expected: Both font and letter spacing should be applied correctly without any conflicts.
     */
    auto spanString = AceType::MakeRefPtr<SpanString>(u"Overlapping font and letter spacing");
    spanString->AddSpan(AceType::MakeRefPtr<FontSpan>(testFont1, 0, 10));
    spanString->AddSpan(AceType::MakeRefPtr<LetterSpacingSpan>(Dimension(5), 5, 15));

    // Convert to TLV and HTML
    std::vector<uint8_t> buff;
    spanString->EncodeTlv(buff);
    EXPECT_GT(buff.size(), 0);

    /**
     * @tc.steps2: Convert the SpanString to HTML format and check for correctness.
     * @tc.expected: The HTML conversion should apply both the font and letter spacing styles correctly.
     */
    SpanToHtml toHtml;
    auto htmlFromSpan = toHtml.ToHtml(*spanString);

    /**
     * @tc.steps3: Convert the HTML back to SpanString and verify if the spans are correctly restored.
     * @tc.expected: The SpanString obtained from HTML should match the original SpanString.
     */
    HtmlToSpan toSpan;
    auto spanFromHtml = toSpan.ToSpanString(htmlFromSpan);
    EXPECT_EQ(IsSpanItemSame(spanFromHtml->GetSpanItems(), spanString->GetSpanItems()), true);
}

/**
 * @tc.name: HtmlConvert010
 * @tc.desc: This test case checks the overlapping of background color spans and text shadow spans in a `SpanString`.
 *           It ensures that both styles are applied correctly without interference.
 * @tc.level: 1
 */
HWTEST_F(HtmlConvertTestNg, HtmlConvert010, TestSize.Level1)
{
    /**
     * @tc.steps1: Add background color and text shadow spans with overlapping ranges.
     * @tc.expected: Both background color and text shadow should be applied correctly without any conflicts.
     */
    auto spanString = AceType::MakeRefPtr<SpanString>(u"Overlapping background and shadow styles");
    NG::BorderRadiusProperty borderRadius;
    TextBackgroundStyle textBackgroundStyle;
    textBackgroundStyle.backgroundColor = Color::WHITE;
    textBackgroundStyle.backgroundRadius = borderRadius;
    spanString->AddSpan(AceType::MakeRefPtr<BackgroundColorSpan>(textBackgroundStyle, 0, 10));

    Shadow shadow1;
    shadow1.SetBlurRadius(3.0);
    shadow1.SetColor(Color::BLACK);
    shadow1.SetOffsetX(1.0);
    shadow1.SetOffsetY(1.0);
    spanString->AddSpan(AceType::MakeRefPtr<TextShadowSpan>(std::vector<Shadow>{shadow1}, 5, 15));

    // Convert to TLV and HTML
    std::vector<uint8_t> buff;
    spanString->EncodeTlv(buff);
    EXPECT_GT(buff.size(), 0);

    /**
     * @tc.steps2: Convert the SpanString to HTML and check for correctness.
     * @tc.expected: The HTML conversion should correctly reflect both background color and text shadow styles.
     */
    SpanToHtml toHtml;
    auto htmlFromSpan = toHtml.ToHtml(*spanString);

    /**
     * @tc.steps3: Convert the HTML back to SpanString and validate if it matches the original SpanString.
     * @tc.expected: The SpanString obtained from HTML should match the original SpanString.
     */
    HtmlToSpan toSpan;
    auto spanFromHtml = toSpan.ToSpanString(htmlFromSpan);
    EXPECT_EQ(IsSpanItemSame(spanFromHtml->GetSpanItems(), spanString->GetSpanItems()), true);
}

/**
 * @tc.name: HtmlConvert011
 * @tc.desc: This test case checks the overlapping of font spans, letter spacing spans, and background color spans.
 *           It ensures that all styles are applied correctly without any conflicts between them.
 * @tc.level: 1
 */
HWTEST_F(HtmlConvertTestNg, HtmlConvert011, TestSize.Level1)
{
    /**
     * @tc.steps1: Add font, letter spacing, and background color spans with overlapping ranges.
     * @tc.expected: All three styles (font, letter spacing, and background color) should be applied correctly.
     */
    auto spanString = AceType::MakeRefPtr<SpanString>(u"Overlapping font, letter spacing, and background styles");
    spanString->AddSpan(AceType::MakeRefPtr<FontSpan>(testFont1, 0, 10));
    spanString->AddSpan(AceType::MakeRefPtr<LetterSpacingSpan>(Dimension(4), 5, 15));
    
    NG::BorderRadiusProperty borderRadius;
    TextBackgroundStyle textBackgroundStyle;
    textBackgroundStyle.backgroundColor = Color::RED;
    textBackgroundStyle.backgroundRadius = borderRadius;
    spanString->AddSpan(AceType::MakeRefPtr<BackgroundColorSpan>(textBackgroundStyle, 0, 10));

    // Convert to TLV and HTML
    std::vector<uint8_t> buff;
    spanString->EncodeTlv(buff);
    EXPECT_GT(buff.size(), 0);

    /**
     * @tc.steps2: Convert the SpanString to HTML and verify the result.
     * @tc.expected: The HTML conversion should correctly reflect all three styles
     *               (font, letter spacing, and background).
     */
    SpanToHtml toHtml;
    auto htmlFromSpan = toHtml.ToHtml(*spanString);

    /**
     * @tc.steps3: Convert the HTML back to SpanString and validate if it matches the original SpanString.
     * @tc.expected: The SpanString obtained from HTML should match the original SpanString.
     */
    HtmlToSpan toSpan;
    auto spanFromHtml = toSpan.ToSpanString(htmlFromSpan);
    EXPECT_EQ(IsSpanItemSame(spanFromHtml->GetSpanItems(), spanString->GetSpanItems()), true);
}

/**
 * @tc.name: HtmlConvert012
 * @tc.desc: This test case checks the conversion of a SpanString containing English and Chinese.
 *           It ensures these characters are handled properly in both TLV and HTML conversions.
 * @tc.level: 1
 */
HWTEST_F(HtmlConvertTestNg, HtmlConvert012, TestSize.Level1)
{
    /**
     * @tc.steps1: Create a SpanString with English and Chinese.
     * @tc.expected: The SpanString should correctly preserve and handle these special characters during conversion.
     */
    auto spanString = AceType::MakeRefPtr<SpanString>(u"Hello World, Friends 你好，世界，朋友们。");

    // Convert to TLV format
    std::vector<uint8_t> buff;
    spanString->EncodeTlv(buff);
    EXPECT_EQ(buff.size() > 0, true);

    /**
     * @tc.steps2: Convert the TLV buffer to HTML and compare it with the result from SpanString conversion.
     * @tc.expected: The HTML string should match the result of directly converting the SpanString with
     *               English and Chinese.
     */
    SpanToHtml toHtml;
    auto htmlFromU8 = toHtml.ToHtml(buff);
    auto htmlFromSpan = toHtml.ToHtml(*spanString);
    EXPECT_EQ(htmlFromU8, htmlFromSpan);

    /**
     * @tc.steps3: Convert the HTML back to SpanString and check if it matches the original SpanString.
     * @tc.expected: The SpanString obtained from the HTML should match the original SpanString.
     */
    HtmlToSpan toSpan;
    auto spanFromHtml = toSpan.ToSpanString(htmlFromU8);
    EXPECT_EQ(IsSpanItemSame(spanFromHtml->GetSpanItems(), spanString->GetSpanItems()), true);

    /**
     * @tc.steps4: Convert the final SpanString back to HTML and ensure consistency with the initial HTML.
     * @tc.expected: The final HTML should match the HTML obtained before the conversion to SpanString.
     */
    SpanToHtml toHtml1;
    auto hmtlString = toHtml1.ToHtml(*spanFromHtml);
    EXPECT_EQ(hmtlString, htmlFromSpan);
}

/**
 * @tc.name: HtmlConvert013
 * @tc.desc: This test case ensures that containing English and Chinese in a `SpanString`
 *           are properly encoded and decoded during the conversion process.
 * @tc.level: 1
 */
HWTEST_F(HtmlConvertTestNg, HtmlConvert013, TestSize.Level1)
{
    /**
     * @tc.steps1: Create a SpanString with special characters and encode it.
     * @tc.expected: The special characters should be properly encoded and decoded in HTML.
     */
    auto spanString = AceType::MakeRefPtr<SpanString>(
        u"Hello World Friends!\n你好，世界，朋友们。\nTest!测试！SpanString");

    // Convert to TLV and HTML
    std::vector<uint8_t> buff;
    spanString->EncodeTlv(buff);
    EXPECT_GT(buff.size(), 0);

    /**
     * @tc.steps2: Convert the TLV buffer to HTML format and verify the result.
     * @tc.expected: The HTML conversion should correctly encode the special characters.
     */
    SpanToHtml toHtml;
    auto htmlFromSpan = toHtml.ToHtml(*spanString);

    /**
     * @tc.steps3: Convert the HTML back to SpanString and check for correctness.
     * @tc.expected: The SpanString obtained from HTML should match the original SpanString.
     */
    HtmlToSpan toSpan;
    auto spanFromHtml = toSpan.ToSpanString(htmlFromSpan);
    EXPECT_EQ(IsSpanItemSame(spanFromHtml->GetSpanItems(), spanString->GetSpanItems()), true);

    /**
     * @tc.steps4: Convert the final SpanString back to HTML and ensure it matches the initial HTML.
     * @tc.expected: The final HTML should match the original HTML obtained from the SpanString.
     */
    SpanToHtml toHtml1;
    auto hmtlString = toHtml1.ToHtml(*spanFromHtml);
    EXPECT_EQ(hmtlString, htmlFromSpan);
}

/**
 * @tc.name: HtmlConvert014
 * @tc.desc: This test case ensures that newline and tab characters in a `SpanString` are
 *           correctly processed during conversion.
 * @tc.level: 1
 */
HWTEST_F(HtmlConvertTestNg, HtmlConvert014, TestSize.Level1)
{
    /**
     * @tc.steps1: Create a SpanString with newline and tab characters and verify proper conversion.
     * @tc.expected: Newline and tab characters should be retained correctly in the conversion process.
     */
    auto spanString = AceType::MakeRefPtr<SpanString>(u"Hello\tWorld!\nThis is a test.");

    // Convert to TLV and HTML
    std::vector<uint8_t> buff;
    spanString->EncodeTlv(buff);
    EXPECT_GT(buff.size(), 0);

    /**
     * @tc.steps2: Convert the TLV buffer to HTML format and verify the result.
     * @tc.expected: The HTML conversion should correctly encode the newline and tab characters.
     */
    SpanToHtml toHtml;
    auto htmlFromSpan = toHtml.ToHtml(*spanString);

    /**
     * @tc.steps3: Convert the HTML back to SpanString and check for correctness.
     * @tc.expected: The SpanString obtained from HTML should match the original SpanString.
     */
    HtmlToSpan toSpan;
    auto spanFromHtml = toSpan.ToSpanString(htmlFromSpan);
    EXPECT_EQ(IsSpanItemSame(spanFromHtml->GetSpanItems(), spanString->GetSpanItems()), true);

    /**
     * @tc.steps4: Convert the final SpanString back to HTML and ensure it matches the initial HTML.
     * @tc.expected: The final HTML should match the original HTML obtained from the SpanString.
     */
    SpanToHtml toHtml1;
    auto hmtlString = toHtml1.ToHtml(*spanFromHtml);
    EXPECT_EQ(hmtlString, htmlFromSpan);
}

/**
 * @tc.name: HtmlConvert015
 * @tc.desc: This test case checks the conversion of a SpanString with long text content.
 *           It ensures that long text is correctly handled in both TLV and HTML conversions.
 * @tc.level: 1
 */
HWTEST_F(HtmlConvertTestNg, HtmlConvert015, TestSize.Level1)
{
    /**
     * @tc.steps1: Create a SpanString with a long text (over 1000 characters).
     * @tc.expected: The SpanString with long text should be handled properly during
     *               conversion to TLV and HTML formats.
     */
    std::u16string longText = u"Hello World! " + std::u16string(1000, u'X') + u" Test with long text.";
    auto spanString = AceType::MakeRefPtr<SpanString>(longText);

    // Convert to TLV format
    std::vector<uint8_t> buff;
    spanString->EncodeTlv(buff);
    EXPECT_EQ(buff.size() > 0, true);

    /**
     * @tc.steps2: Convert the TLV buffer to HTML and compare with the direct SpanString to HTML conversion.
     * @tc.expected: The HTML obtained from TLV and from SpanString should be identical.
     */
    SpanToHtml toHtml;
    auto htmlFromU8 = toHtml.ToHtml(buff);
    auto htmlFromSpan = toHtml.ToHtml(*spanString);
    EXPECT_EQ(htmlFromU8, htmlFromSpan);

    /**
     * @tc.steps3: Convert the HTML back to SpanString and verify consistency with the original SpanString.
     * @tc.expected: The SpanString obtained from HTML should match the original SpanString.
     */
    HtmlToSpan toSpan;
    auto spanFromHtml = toSpan.ToSpanString(htmlFromU8);
    EXPECT_EQ(IsSpanItemSame(spanFromHtml->GetSpanItems(), spanString->GetSpanItems()), true);

    /**
     * @tc.steps4: Convert the final SpanString back to HTML and check for consistency with the original HTML.
     * @tc.expected: The final HTML should match the initial HTML result.
     */
    SpanToHtml toHtml1;
    auto hmtlString = toHtml1.ToHtml(*spanFromHtml);
    EXPECT_EQ(hmtlString, htmlFromSpan);
}

/**
 * @tc.name: HtmlConvert016
 * @tc.desc: This test case checks how `SpanString` handles very long text inputs and ensures that the conversion
 *           process still works efficiently with long texts.
 * @tc.level: 1
 */
HWTEST_F(HtmlConvertTestNg, HtmlConvert016, TestSize.Level1)
{
    /**
     * @tc.steps1: Create a long text string and verify its conversion to TLV and HTML formats.
     * @tc.expected: Long text should be handled without errors, and conversion should retain all data.
     */
    std::u16string longText = u"Long text testing " + std::u16string(5000, u'X');
    auto spanString = AceType::MakeRefPtr<SpanString>(longText);

    // Convert to TLV and HTML
    std::vector<uint8_t> buff;
    spanString->EncodeTlv(buff);
    EXPECT_GT(buff.size(), 0);

    /**
     * @tc.steps2: Convert the TLV buffer to HTML format and verify the result.
     * @tc.expected: The HTML conversion should correctly handle long text.
     */
    SpanToHtml toHtml;
    auto htmlFromSpan = toHtml.ToHtml(*spanString);

    /**
     * @tc.steps3: Convert the HTML back to SpanString and check for correctness.
     * @tc.expected: The SpanString obtained from HTML should match the original SpanString.
     */
    HtmlToSpan toSpan;
    auto spanFromHtml = toSpan.ToSpanString(htmlFromSpan);
    EXPECT_EQ(IsSpanItemSame(spanFromHtml->GetSpanItems(), spanString->GetSpanItems()), true);

    /**
     * @tc.steps4: Convert the final SpanString back to HTML and ensure it matches the initial HTML.
     * @tc.expected: The final HTML should match the original HTML obtained from the SpanString.
     */
    SpanToHtml toHtml1;
    auto hmtlString = toHtml1.ToHtml(*spanFromHtml);
    EXPECT_EQ(hmtlString, htmlFromSpan);
}

/**
 * @tc.name: HtmlConvert017
 * @tc.desc: This test case checks the conversion of a SpanString that includes nested SpanStrings.
 *           It ensures that nested spans are correctly handled and converted between formats.
 * @tc.level: 1
 */
HWTEST_F(HtmlConvertTestNg, HtmlConvert017, TestSize.Level1)
{
    /**
     * @tc.steps1: Create a SpanString that contains other SpanStrings (nested).
     * @tc.expected: The nested SpanStrings should be correctly handled and maintained during conversion.
     */
    auto spanString1 = AceType::MakeRefPtr<SpanString>(u"Hello");

    // Convert to TLV format
    std::vector<uint8_t> buff;
    spanString1->EncodeTlv(buff);
    EXPECT_EQ(buff.size() > 0, true);

    /**
     * @tc.steps2: Convert the TLV buffer to HTML and compare with the direct SpanString to HTML conversion.
     * @tc.expected: The HTML string should match the result of converting the nested SpanString directly to HTML.
     */
    SpanToHtml toHtml;
    auto htmlFromU8 = toHtml.ToHtml(buff);
    auto htmlFromSpan = toHtml.ToHtml(*spanString1);
    EXPECT_EQ(htmlFromU8, htmlFromSpan);

    /**
     * @tc.steps3: Convert the HTML back to SpanString and verify if it matches the original nested SpanString.
     * @tc.expected: The SpanString obtained from HTML should match the original nested SpanString.
     */
    HtmlToSpan toSpan;
    auto spanFromHtml = toSpan.ToSpanString(htmlFromU8);
    EXPECT_EQ(IsSpanItemSame(spanFromHtml->GetSpanItems(), spanString1->GetSpanItems()), true);

    /**
     * @tc.steps4: Convert the final SpanString back to HTML and check if it matches the initial HTML.
     * @tc.expected: The final HTML should match the initial HTML obtained from the nested SpanString.
     */
    SpanToHtml toHtml1;
    auto hmtlString = toHtml1.ToHtml(*spanFromHtml);
    EXPECT_EQ(hmtlString, htmlFromSpan);
}

/**
 * @tc.name: HtmlConverter001
 * @tc.desc: This test case checks the conversion of a span string with a font-family property applied.
 *           It verifies that the font-family attribute is correctly parsed and converted into a SpanItem.
 * @tc.level: 1
 */
HWTEST_F(HtmlConvertTestNg, HtmlConverter001, TestSize.Level1)
{
    /**
     * @tc.steps1: Create a multiHtml string containing a <p> tag with a font-family property.
     *             Convert it to SpanString and retrieve the font-family from the span item.
     * @tc.expected: The font-family property should be correctly converted and retrieved.
     */
    const std::string multiHtml = "<html>"
                                  "<body>"
                                  "<p style=\"font-family:'Times New Roman', serif;\">Times New Roman 字体</p>"
                                  "</body>"
                                  "</html>";
    HtmlToSpan toSpan;
    auto dstSpan = toSpan.ToSpanString(multiHtml);
    std::list<RefPtr<NG::SpanItem>> spans = dstSpan->GetSpanItems();
    EXPECT_EQ(spans.size(), 1);
}

/**
 * @tc.name: HtmlConverter002
 * @tc.desc: This test case checks the conversion of a span string with font-size and letter-spacing applied.
 *           It ensures that the font size and letter spacing are correctly converted into SpanItem properties.
 * @tc.level: 1
 */
HWTEST_F(HtmlConvertTestNg, HtmlConverter002, TestSize.Level1)
{
    /**
     * @tc.steps1: Create a multiHtml string containing a <p> tag with font-size and letter-spacing properties.
     *             Convert it to SpanString and retrieve the font size and letter spacing from the span item.
     * @tc.expected: The font-size and letter-spacing properties should be correctly converted and retrieved.
     */
    const std::string multiHtml = "<html>"
                                  "<body>"
                                  "<p style=\"font-size:18px;letter-spacing:2px;\">带字间距的文字</p>"
                                  "</body>"
                                  "</html>";
    HtmlToSpan toSpan;
    auto dstSpan = toSpan.ToSpanString(multiHtml);
    std::list<RefPtr<NG::SpanItem>> spans = dstSpan->GetSpanItems();
    EXPECT_EQ(spans.size(), 1);
    auto it = spans.begin();
    EXPECT_EQ((*it)->fontStyle->GetFontSize().value(), Dimension(18, DimensionUnit::VP));
    EXPECT_EQ((*it)->fontStyle->GetLetterSpacing().value(), Dimension(2, DimensionUnit::VP));
}

/**
 * @tc.name: HtmlConverter003
 * @tc.desc: This test case checks the conversion of a span string with text-decoration and color applied.
 *           It verifies that the text-decoration (line-through) and text color are correctly
 *           converted into SpanItem properties.
 * @tc.level: 1
 */
HWTEST_F(HtmlConvertTestNg, HtmlConverter003, TestSize.Level1)
{
    /**
     * @tc.steps1: Create a multiHtml string containing a <p> tag with text-decoration and color properties.
     *             Convert it to SpanString and retrieve the text-decoration and text color from the span item.
     * @tc.expected: The text-decoration (line-through) and text color (blue) properties should be
     *               correctly converted and retrieved.
     */
    const std::string multiHtml = "<html>"
                                  "<body>"
                                  "<p style=\"text-decoration:line-through;color:blue;\">带删除线的蓝色文字</p>"
                                  "</body>"
                                  "</html>";
    HtmlToSpan toSpan;
    auto dstSpan = toSpan.ToSpanString(multiHtml);
    std::list<RefPtr<NG::SpanItem>> spans = dstSpan->GetSpanItems();
    EXPECT_EQ(spans.size(), 1);
    auto it = spans.begin();
    EXPECT_EQ((*it)->fontStyle->GetTextDecoration().value(), TextDecoration::LINE_THROUGH);
}

/**
 * @tc.name: HtmlConverter004
 * @tc.desc: This test case checks the conversion of a span string with font-size, color,
 *           and text-decoration properties applied.
 *           It ensures that all three properties are correctly converted into SpanItem properties.
 * @tc.level: 1
 */
HWTEST_F(HtmlConvertTestNg, HtmlConverter004, TestSize.Level1)
{
    /**
     * @tc.steps1: Create a multiHtml string containing a <p> tag with font-size, color,
     *             and text-decoration properties. Convert it to SpanString and retrieve
     *             the font size, text color, and text-decoration from the span item.
     * @tc.expected: The font-size (16px), text color (red), and text-decoration (underline)
     *               properties should be correctly converted and retrieved.
     */
    const std::string multiHtml = "<html>"
                                  "<body>"
                                  "<p style=\"font-size:16px;color:red;text-decoration:underline;\">"
                                  "带下划线的红色小字体</p>"
                                  "</body>"
                                  "</html>";
    HtmlToSpan toSpan;
    auto dstSpan = toSpan.ToSpanString(multiHtml);
    std::list<RefPtr<NG::SpanItem>> spans = dstSpan->GetSpanItems();
    EXPECT_EQ(spans.size(), 1);
    auto it = spans.begin();
    EXPECT_EQ((*it)->fontStyle->GetFontSize().value(), Dimension(16, DimensionUnit::VP));
    EXPECT_EQ((*it)->fontStyle->GetTextColor().value(), OHOS::Ace::Color::RED);
}

/**
 * @tc.name: HtmlConverter005
 * @tc.desc: This test case checks the conversion of a span string with font-weight and font-style properties applied.
 *           It ensures that both the font-weight (bold) and font-style (italic) are correctly converted into SpanItem.
 * @tc.level: 1
 */
HWTEST_F(HtmlConvertTestNg, HtmlConverter005, TestSize.Level1)
{
    /**
     * @tc.steps1: Create a multiHtml string containing a <p> tag with font-weight (bold) and font-style (italic).
     *             Convert it to SpanString and retrieve the font-weight and font-style from the span item.
     * @tc.expected: The font-weight (bold) and font-style (italic) should be correctly converted and retrieved.
     */
    const std::string multiHtml = "<html>"
                                  "<body>"
                                  "<p style=\"font-weight:bold;font-style:italic;\">加粗斜体文字</p>"
                                  "</body>"
                                  "</html>";
    HtmlToSpan toSpan;
    auto dstSpan = toSpan.ToSpanString(multiHtml);
    std::list<RefPtr<NG::SpanItem>> spans = dstSpan->GetSpanItems();
    EXPECT_EQ(spans.size(), 1);
    auto it = spans.begin();
    EXPECT_TRUE((*it)->fontStyle->GetFontWeight().has_value());
    EXPECT_EQ((*it)->fontStyle->GetFontWeight().value(), FontWeight::BOLD);
    EXPECT_TRUE((*it)->fontStyle->GetItalicFontStyle().has_value());
}

/**
 * @tc.name: HtmlConverter006
 * @tc.desc: This test case checks the conversion of a span string with nested font-size properties.
 *           It ensures that the correct font-size is applied for each nested span element.
 * @tc.level: 1
 */
HWTEST_F(HtmlConvertTestNg, HtmlConverter006, TestSize.Level1)
{
    /**
     * @tc.steps1: Create a multiHtml string containing a <p> tag with nested <span> tags have different font-size.
     *             Convert it to SpanString and retrieve the font-size for each span item.
     * @tc.expected: The nested <span> tags should correctly apply the respective font-size (100px and 50px).
     */
    const std::string multiHtml = "<html>"
                                  "<body>"
                                  "<p style=\"font-size:50px\"><span style=\"font-size:100px\">100px</span>50px</p>"
                                  "</body>"
                                  "</html>";
    HtmlToSpan toSpan;
    auto dstSpan = toSpan.ToSpanString(multiHtml);
    std::list<RefPtr<NG::SpanItem>> spans = dstSpan->GetSpanItems();
    EXPECT_EQ(spans.size(), 2);
    auto it = spans.begin();
    EXPECT_EQ((*it)->fontStyle->GetFontSize().value(), Dimension(50, DimensionUnit::VP));
}

/**
 * @tc.name: HtmlConverter007
 * @tc.desc: This test case checks the conversion of a span string with font-size and text-shadow properties applied.
 *           It ensures that both the font-size and text-shadow are correctly converted into SpanItem properties.
 * @tc.level: 1
 */
HWTEST_F(HtmlConvertTestNg, HtmlConverter007, TestSize.Level1)
{
    /**
     * @tc.steps1: Create a multiHtml string containing a <p> tag with font-size and text-shadow properties.
     *             Convert it to SpanString and retrieve the font-size and text-shadow from the span item.
     * @tc.expected: The font-size (50px) and text-shadow (red and green shadows) should be correctly converted.
     */
    const std::string multiHtml = "<html>"
                                  "<body>"
                                  "<p style=\"font-size:50px;text-shadow:0 0 3px red, green 0 0;\">"
                                  "带有字体大小和阴影的文字</p>"
                                  "</body>"
                                  "</html>";
    HtmlToSpan toSpan;
    auto dstSpan = toSpan.ToSpanString(multiHtml);
    std::list<RefPtr<NG::SpanItem>> spans = dstSpan->GetSpanItems();
    EXPECT_EQ(spans.size(), 1);
    auto it = spans.begin();
    EXPECT_EQ((*it)->fontStyle->GetFontSize().value(), Dimension(50, DimensionUnit::VP));
    EXPECT_EQ((*it)->fontStyle->GetTextShadow().value()[0].GetColor(), OHOS::Ace::Color::RED);
}

/**
 * @tc.name: HtmlConverter008
 * @tc.desc: This test case checks the conversion of HTML with multiple inline styles
 *           applied to various elements like `span`, `strong`, and `em`, ensuring correct styling.
 * @tc.level: 1
 */
HWTEST_F(HtmlConvertTestNg, HtmlConverter008, TestSize.Level1)
{
    /**
     * @tc.steps1: Create a complex HTML with multiple inline styles, such as `em`, and `span`,
     *             to check the proper conversion to span strings.
     * @tc.expected: All inline styles such as font weight, font style, and color should be applied correctly.
     */
    const std::string multiHtml = "<html>"
                                  "<body>"
                                  "<p><strong>Text</strong> and "
                                  "<em style=\"font-style:italic; color:blue;\">Italic Blue</em> and "
                                  "<span style=\"font-size:14px; color:green;\">Green 14px</span></p>"
                                  "</body>"
                                  "</html>";
    HtmlToSpan toSpan;
    auto dstSpan = toSpan.ToSpanString(multiHtml);

    /**
     * @tc.steps2: Verify the size of the converted `SpanString`. It should have 5 span items.
     * @tc.expected: The size of the spans list should be 5.
     */
    std::list<RefPtr<NG::SpanItem>> spans = dstSpan->GetSpanItems();
    EXPECT_EQ(spans.size(), 5);

    /**
     * @tc.steps3: Verify the first span item, which should have a bold font weight.
     * @tc.expected: The first span item should have font weight set to bold.
     */
    auto it = spans.begin();
    EXPECT_TRUE((*it)->fontStyle->GetFontWeight().has_value());
    EXPECT_EQ((*it)->fontStyle->GetFontWeight().value(), FontWeight::BOLD);

    /**
     * @tc.steps4: Verify the third span item, which should have an italic font style and blue color.
     * @tc.expected: The third span item should have italic font style and color set to blue.
     */
    ++it;
    ++it;
    EXPECT_TRUE((*it)->fontStyle->GetTextColor().has_value());
    EXPECT_EQ((*it)->fontStyle->GetTextColor().value(), Color::BLUE);
    EXPECT_TRUE((*it)->fontStyle->GetItalicFontStyle().has_value());
    EXPECT_EQ((*it)->fontStyle->GetItalicFontStyle().value(), Ace::FontStyle::ITALIC);

    /**
     * @tc.steps5: Verify the fifth span item, which should have a font size of 14px and green color.
     * @tc.expected: The fifth span item should have font size set to 14px and color set to green.
     */
    ++it;
    ++it;
    EXPECT_TRUE((*it)->fontStyle->GetTextColor().has_value());
    EXPECT_EQ((*it)->fontStyle->GetTextColor().value(), Color::GREEN);
    EXPECT_TRUE((*it)->fontStyle->GetFontSize().has_value());
    EXPECT_EQ((*it)->fontStyle->GetFontSize().value(), Dimension(14, DimensionUnit::VP));
}

/**
 * @tc.name: HtmlConverter009
 * @tc.desc: This test case checks the conversion of HTML with nested `span` tags with
 *           varying `text-shadow` and `background-color`.
 * @tc.level: 1
 */
HWTEST_F(HtmlConvertTestNg, HtmlConverter009, TestSize.Level1)
{
    /**
     * @tc.steps1: Create a nested HTML structure with `span` elements having `text-shadow` and `background-color`.
     * @tc.expected: Nested `span` tags should preserve both text-shadow and background color styles correctly.
     */
    const std::string multiHtml = "<html>"
                                  "<body>"
                                  "<p>"
                                  "<span style=\"text-shadow:2px 2px 4px #000000; background-color:#ffcc00;\">"
                                  "Shadowed and Colored Text</span></p>"
                                  "</body>"
                                  "</html>";
    HtmlToSpan toSpan;
    auto dstSpan = toSpan.ToSpanString(multiHtml);

    /**
     * @tc.steps2: Verify the size of the converted `SpanString`. It have 1 span item for the single `span` tag.
     * @tc.expected: The size of the spans list should be 1.
     */
    std::list<RefPtr<NG::SpanItem>> spans = dstSpan->GetSpanItems();
    EXPECT_EQ(spans.size(), 1);

    /**
     * @tc.steps3: Verify the text shadow applied to the span. It should have a shadow with the specified parameters.
     * @tc.expected: The text-shadow should have a 2px offset, 4px blur, and black color.
     */
    auto it = spans.begin();
    EXPECT_EQ((*it)->fontStyle->GetTextShadow().value()[0].GetColor(), OHOS::Ace::Color::BLACK);
}

/**
 * @tc.name: HtmlConverter010
 * @tc.desc: This test case checks the conversion of HTML with `div` elements having
 *           padding, margin, and background color.
 * @tc.level: 1
 */
HWTEST_F(HtmlConvertTestNg, HtmlConverter010, TestSize.Level1)
{
    /**
     * @tc.steps1: Create a `div` element with padding, margin, and background color.
     * @tc.expected: Padding, margin, and background color styles should be correctly applied to the div content.
     */
    const std::string multiHtml = "<html>"
                                  "<body>"
                                  "<div style=\"padding:10px; margin:5px; background-color:#f4f4f4;\">"
                                  "Styled Div Content</div>"
                                  "</body>"
                                  "</html>";
    HtmlToSpan toSpan;
    auto dstSpan = toSpan.ToSpanString(multiHtml);

    /**
     * @tc.steps2: Verify the size of the converted `SpanString`. It should have 1 span item for the `div` tag.
     * @tc.expected: The size of the spans list should be 1.
     */
    std::list<RefPtr<NG::SpanItem>> spans = dstSpan->GetSpanItems();
    EXPECT_EQ(spans.size(), 1);
}


/**
 * @tc.name: HtmlConverter011
 * @tc.desc: This test case checks the conversion of HTML containing a paragraph with a red text color.
 *           It ensures that the correct color is applied to the text in the resulting SpanItem.
 * @tc.level: 1
 */
HWTEST_F(HtmlConvertTestNg, HtmlConverter011, TestSize.Level1)
{
    /**
     * @tc.steps1: Initialize a multi-line HTML string with a paragraph containing red text color.
     *             Convert the HTML to SpanString and verify the text color.
     * @tc.expected: The text color of the span should be red.
     */
    const std::string multiHtml = "<html>"
                                  "<body>"
                                  "<p style=\"color:red;\">dddd当地经的123456</p>"
                                  "</body>"
                                  "</html>";
    HtmlToSpan toSpan;
    auto dstSpan = toSpan.ToSpanString(multiHtml);
    std::list<RefPtr<NG::SpanItem>> spans = dstSpan->GetSpanItems();
    EXPECT_EQ(spans.size(), 1);
    auto it = spans.begin();
    EXPECT_EQ((*it)->fontStyle->GetTextColor().value(), OHOS::Ace::Color::RED);
}


/**
 * @tc.name: HtmlConverter012
 * @tc.desc: This test case checks the conversion of a SpanString with basic spanParagraphStyle.
 *           It ensures that the span string is correctly converted to HTML with the specified styles.
 * @tc.level: 1
 */
HWTEST_F(HtmlConvertTestNg, HtmlConverter012, TestSize.Level1)
{
    auto spanString = AceType::MakeRefPtr<SpanString>(u"段落标题\n正文第一段开始");
    SpanParagraphStyle spanParagraphStyle;
    spanParagraphStyle.align = TextAlign::CENTER;

    // default max lines 4
    spanParagraphStyle.maxLines = 4;
    spanParagraphStyle.wordBreak = WordBreak::BREAK_ALL;
    spanParagraphStyle.textOverflow = TextOverflow::ELLIPSIS;

    // defalut textIndent 23
    spanParagraphStyle.textIndent = Dimension(23.0_vp);
    spanParagraphStyle.leadingMargin = LeadingMargin();

    // default width 25.0 height 26.0
    spanParagraphStyle.leadingMargin->size = LeadingMarginSize(Dimension(25.0_vp), Dimension(26.0));
    auto paragraphStyle = AceType::MakeRefPtr<ParagraphStyleSpan>(spanParagraphStyle, 0, 5);
    spanString->AddSpan(paragraphStyle);

    SpanToHtml convert;
    auto out = convert.ToHtml(*spanString);
    std::string result =
        "<div ><p style=\"text-align: center;text-indent: 23.00px;word-break: break_all;text-overflow: ellipsis;\">"
        "<span style=\"font-size: 16.00px;font-style: normal;font-weight: normal;color: #000000FF;font-family: "
        "HarmonyOS Sans;\">段落标题</span></p><span style=\"font-size: 16.00px;font-style: normal;font-weight: "
        "normal;color: #000000FF;font-family: HarmonyOS Sans;\">正文第一段开始</span></div>";
    EXPECT_EQ(out, result);
}

/**
 * @tc.name: HtmlConverter013
 * @tc.desc: This test case checks the conversion of a SpanString with spanString.
 *           It ensures that the span string is correctly converted to HTML with the specified styles.
 * @tc.level: 1
 */
HWTEST_F(HtmlConvertTestNg, HtmlConverter013, TestSize.Level1)
{
    auto spanString = AceType::MakeRefPtr<SpanString>(u"向上到顶适中向下到底");
    spanString->AddSpan(AceType::MakeRefPtr<BaselineOffsetSpan>(Dimension(20.0_vp), 0, 4));
    spanString->AddSpan(AceType::MakeRefPtr<BaselineOffsetSpan>(Dimension(10.0_vp), 4, 6));

    SpanToHtml convert;
    auto out = convert.ToHtml(*spanString);
    std::string result =
        "<div ><span style=\"font-size: 16.00px;font-style: normal;font-weight: normal;color: #000000FF;font-family: "
        "HarmonyOS Sans;vertical-align: 20.00px;\">向上到顶</span><span style=\"font-size: 16.00px;font-style: "
        "normal;font-weight: normal;color: #000000FF;font-family: HarmonyOS Sans;vertical-align: "
        "10.00px;\">适中</span><span style=\"font-size: 16.00px;font-style: normal;font-weight: normal;color: "
        "#000000FF;font-family: HarmonyOS Sans;\">向下到底</span></div>";
    EXPECT_EQ(out, result);
}

/**
 * @tc.name: HtmlConverter014
 * @tc.desc: This test case checks the conversion of a string that includes some style.
 * @tc.level: 1
 */
HWTEST_F(HtmlConvertTestNg, HtmlConverter014, TestSize.Level1)
{
    const std::string multiHtml =
        "<html>"
        "<body>"
        "<p style=\"font-size:50px\"><span style=\"font-size:100px\">100fontsize</span>dddd当地经的123456<span "
        "style=\"font-size:30px\">30fontsize</span>1232132</p>"
        "</body>"
        "</html>";
    HtmlToSpan toSpan;
    auto dstSpan = toSpan.ToSpanString(multiHtml);
    std::list<RefPtr<NG::SpanItem>> spans = dstSpan->GetSpanItems();
    EXPECT_EQ(spans.size(), 4);

    SpanToHtml convert;
    auto dstHtml = convert.ToHtml(*dstSpan);
    HtmlToSpan toSpan1;
    auto dstSpan1 = toSpan1.ToSpanString(dstHtml);
    EXPECT_EQ(IsSpanItemSame(dstSpan->GetSpanItems(), dstSpan1->GetSpanItems()), true);
    auto secondHtml = convert.ToHtml(*dstSpan1);
    EXPECT_EQ(secondHtml, dstHtml);
}

/**
 * @tc.name: HtmlConverter015
 * @tc.desc: This test case checks the conversion of a string that includes more style.
 * @tc.level: 1
 */
HWTEST_F(HtmlConvertTestNg, HtmlConverter015, TestSize.Level1)
{
    const std::string multiHtml =
        "<html>"
        "<head>"
        "</head>"
        "<body>"
        "<p style=\"font-size:50px;text-shadow: 0 0 3px red, green 0 0;\">"
        "<span style=\"font-size:100px\">100fontsize</span>dddd当地经的123456<span "
        "style=\"font-size:30px\">30fontsize</span>1232132</p>"
        "</body>"
        "</html>";
    HtmlToSpan toSpan;
    auto dstSpan = toSpan.ToSpanString(multiHtml);
    std::list<RefPtr<NG::SpanItem>> spans = dstSpan->GetSpanItems();
    EXPECT_EQ(spans.size(), 4);
    auto it = spans.begin();
    EXPECT_EQ((*it)->fontStyle->GetTextShadow().value()[0].GetColor(), OHOS::Ace::Color::RED);
    EXPECT_EQ((*it)->fontStyle->GetTextShadow().value()[1].GetColor(), OHOS::Ace::Color::GREEN);
}

/**
 * @tc.name: HtmlConvertExam001
 * @tc.desc: This test case checks the conversion of a SpanString with basic text color and font size.
 *           It ensures that the HTML conversion correctly applies the font size and text color.
 * @tc.level: 1
 */
HWTEST_F(HtmlConvertTestNg, HtmlConvertExam001, TestSize.Level1)
{
    /**
     * @tc.steps1: Create a SpanString with the text and apply the basic paragraph style with
     *             font-size (50px) and text color (red).
     * @tc.expected: The generated HTML should include basic font size and text color styles.
     */
    const std::string multiHtml =
        "<html>"
        "<head>"
        "</head>"
        "<body>"
        "<p style=\"font-weight:bold;letter-spacing:5px;\">"
        "这是一个测试，检查字体为粗体，字符间距为5px的文本。"
        "</p>"
        "</body>"
        "</html>";
    
    /**
     * @tc.steps2: Convert the HTML string to SpanString and then back to HTML.
     *             The result should match the original input HTML.
     * @tc.expected: The generated SpanString should match the original input HTML.
     */
    HtmlToSpan toSpan;
    auto dstSpan = toSpan.ToSpanString(multiHtml);
    EXPECT_EQ(dstSpan->GetSpanItems().size(), 1);
    SpanToHtml convert;

    auto dstHtml = convert.ToHtml(*dstSpan);
    EXPECT_GT(dstHtml.size(), 0);  // dstHtml is converted
    HtmlToSpan toSpan1;
    auto dstSpan1 = toSpan1.ToSpanString(dstHtml);
    EXPECT_EQ(IsSpanItemSame(dstSpan->GetSpanItems(), dstSpan1->GetSpanItems()), true);
    auto secondHtml = convert.ToHtml(*dstSpan1);
    EXPECT_EQ(secondHtml, dstHtml);
}

/**
 * @tc.name: HtmlConvertExam002
 * @tc.desc: This test case checks the conversion of a SpanString with basic text color and font size.
 *           It ensures that the HTML conversion correctly applies the font size and text color.
 * @tc.level: 1
 */
HWTEST_F(HtmlConvertTestNg, HtmlConvertExam002, TestSize.Level1)
{
    /**
     * @tc.steps1: Create a SpanString with the text and apply the basic paragraph style with
     *             font-size (50px) and text color (red).
     * @tc.expected: The generated SpanString should include basic font size and text color styles.
     */
    const std::string multiHtml =
        "<html>"
        "<head>"
        "</head>"
        "<body>"
        "<p style=\"font-size:50px;color:red;\">"
        "这是一个测试，检查字体颜色为红色，字体大小为50px的文本转换。"
        "</p>"
        "</body>"
        "</html>";
    
    /**
     * @tc.steps2: Convert the HTML string to SpanString and then back to HTML.
     *             The result should match the original input HTML.
     * @tc.expected: The generated SpanString should match the original input HTML.
     */
    HtmlToSpan toSpan;
    auto dstSpan = toSpan.ToSpanString(multiHtml);
    EXPECT_EQ(dstSpan->GetSpanItems().size(), 1);
    SpanToHtml convert;

    auto dstHtml = convert.ToHtml(*dstSpan);
    EXPECT_GT(dstHtml.size(), 0);  // dstHtml is converted
    HtmlToSpan toSpan1;
    auto dstSpan1 = toSpan1.ToSpanString(dstHtml);
    EXPECT_EQ(IsSpanItemSame(dstSpan->GetSpanItems(), dstSpan1->GetSpanItems()), true);
    auto secondHtml = convert.ToHtml(*dstSpan1);
    EXPECT_EQ(secondHtml, dstHtml);
}

/**
 * @tc.name: HtmlConvertExam003
 * @tc.desc: This test case checks the conversion of a SpanString with mixed font sizes and text shadow.
 *           It ensures that the HTML correctly applies different font sizes and text shadow effects.
 * @tc.level: 1
 */
HWTEST_F(HtmlConvertTestNg, HtmlConvertExam003, TestSize.Level1)
{
    /**
     * @tc.steps1: Create a SpanString and apply the paragraph style with font-size (50px) and text shadow (red).
     * @tc.expected: The generated HTML should include the correct font size and shadow effect.
     */
    const std::string multiHtml =
        "<html>"
        "<head>"
        "</head>"
        "<body>"
        "<p style=\"font-size:50px;text-shadow:0px 0px 5px red;\">"
        "这段文本具有红色阴影效果，字体大小为50px，用于测试阴影和字体大小的转换。"
        "</p>"
        "</body>"
        "</html>";
    
    /**
     * @tc.steps2: Convert the HTML string to SpanString and then back to HTML.
     *             The result should match the original input HTML.
     * @tc.expected: The generated SpanString should match the original input HTML.
     */
    HtmlToSpan toSpan;
    auto dstSpan = toSpan.ToSpanString(multiHtml);
    EXPECT_EQ(dstSpan->GetSpanItems().size(), 1);
    SpanToHtml convert;
    auto dstHtml = convert.ToHtml(*dstSpan);

    EXPECT_GT(dstHtml.size(), 0);  // dstHtml is converted
    HtmlToSpan toSpan1;
    auto dstSpan1 = toSpan1.ToSpanString(dstHtml);
    EXPECT_EQ(IsSpanItemSame(dstSpan->GetSpanItems(), dstSpan1->GetSpanItems()), true);
    auto secondHtml = convert.ToHtml(*dstSpan1);
    EXPECT_EQ(secondHtml, dstHtml);
}

/**
 * @tc.name: HtmlConvertExam004
 * @tc.desc: This test case checks the conversion of a SpanString with bold and italic font styles.
 *           It ensures that the HTML applies the font styles correctly.
 * @tc.level: 1
 */
HWTEST_F(HtmlConvertTestNg, HtmlConvertExam004, TestSize.Level1)
{
    /**
     * @tc.steps1: Create a SpanString with the text and apply the paragraph style with font-weight (bold)
     *             and font-style (italic).
     * @tc.expected: The generated HTML should include bold and italic font styles.
     */
    const std::string multiHtml =
        "<html>"
        "<head>"
        "</head>"
        "<body>"
        "<p style=\"font-size:50px;font-weight:bold;font-style:italic;\">"
        "这是加粗且斜体的文本，用于测试段落中的加粗和斜体字体样式。"
        "</p>"
        "</body>"
        "</html>";
    
    /**
     * @tc.steps2: Convert the HTML string to SpanString and then back to HTML.
     *             The result should match the original input HTML.
     * @tc.expected: The generated SpanString should match the original input HTML.
     */
    HtmlToSpan toSpan;
    auto dstSpan = toSpan.ToSpanString(multiHtml);
    EXPECT_EQ(dstSpan->GetSpanItems().size(), 1);

    SpanToHtml convert;
    auto dstHtml = convert.ToHtml(*dstSpan);
    EXPECT_GT(dstHtml.size(), 0);  // dstHtml is converted
    HtmlToSpan toSpan1;
    auto dstSpan1 = toSpan1.ToSpanString(dstHtml);
    EXPECT_EQ(IsSpanItemSame(dstSpan->GetSpanItems(), dstSpan1->GetSpanItems()), true);
    auto secondHtml = convert.ToHtml(*dstSpan1);
    EXPECT_EQ(secondHtml, dstHtml);
}

/**
 * @tc.name: HtmlConvertExam005
 * @tc.desc: This test case checks the conversion of a SpanString with mixed font sizes and colors.
 *           It ensures that different parts of the text have the correct font size and color.
 * @tc.level: 1
 */
HWTEST_F(HtmlConvertTestNg, HtmlConvertExam005, TestSize.Level1)
{
    /**
     * @tc.steps1: Create a SpanString with the text and apply the paragraph style with font-size (50px) and
     *             color (red), and a span with font-size (30px) and color (blue).
     */
    const std::string multiHtml =
        "<html>"
        "<head>"
        "</head>"
        "<body>"
        "<p style=\"font-size:50px;color:red;\">"
        "这一部分为红色，字体大小50px，后面是<span style=\"font-size:30px;color:blue;\">蓝色30px字体</span>。"
        "</p>"
        "</body>"
        "</html>";
    
    /**
     * @tc.steps2: Convert the HTML string to SpanString and then back to HTML.
     *             The result should match the original input HTML.
     * @tc.expected: The generated SpanString should match the original input HTML.
     */
    HtmlToSpan toSpan;
    auto dstSpan = toSpan.ToSpanString(multiHtml);
    EXPECT_EQ(dstSpan->GetSpanItems().size(), 3);

    SpanToHtml convert;
    auto dstHtml = convert.ToHtml(*dstSpan);
    EXPECT_GT(dstHtml.size(), 0);  // dstHtml is converted
    HtmlToSpan toSpan1;
    auto dstSpan1 = toSpan1.ToSpanString(dstHtml);
    EXPECT_EQ(IsSpanItemSame(dstSpan->GetSpanItems(), dstSpan1->GetSpanItems()), true);
    auto secondHtml = convert.ToHtml(*dstSpan1);
    EXPECT_EQ(secondHtml, dstHtml);
}

/**
 * @tc.name: HtmlConvertExam006
 * @tc.desc: This test case checks the conversion of a SpanString with underline and strikethrough.
 *           It ensures the HTML conversion applies the text decoration correctly.
 * @tc.level: 1
 */
HWTEST_F(HtmlConvertTestNg, HtmlConvertExam006, TestSize.Level1)
{
    /**
     * @tc.steps1: Create a SpanString with the text and apply text-decoration (underline).
     *             Add a span with text-decoration (line-through).
     * @tc.expected: The generated SpanString should include the underline and strikethrough decoration.
     */
    const std::string multiHtml =
        "<html>"
        "<head>"
        "</head>"
        "<body>"
        "<p style=\"font-size:50px;text-decoration:underline;\">"
        "这段文本带有下划线效果，用于测试下划线装饰功能。"
        "<span style=\"text-decoration:line-through;\"> 这一部分有删除线效果。</span>"
        "</p>"
        "</body>"
        "</html>";
    
    /**
     * @tc.steps2: Convert the HTML string to SpanString and then back to HTML.
     *             The result should match the original input HTML.
     * @tc.expected: The generated SpanString should match the original input HTML.
     */
    HtmlToSpan toSpan;
    auto dstSpan = toSpan.ToSpanString(multiHtml);
    EXPECT_EQ(dstSpan->GetSpanItems().size(), 2);
    SpanToHtml convert;

    auto dstHtml = convert.ToHtml(*dstSpan);
    EXPECT_GT(dstHtml.size(), 0);  // dstHtml is converted
    HtmlToSpan toSpan1;
    auto dstSpan1 = toSpan1.ToSpanString(dstHtml);
    EXPECT_EQ(IsSpanItemSame(dstSpan->GetSpanItems(), dstSpan1->GetSpanItems()), true);
    auto secondHtml = convert.ToHtml(*dstSpan1);
    EXPECT_EQ(secondHtml, dstHtml);
}

/**
 * @tc.name: HtmlConvertExam007
 * @tc.desc: This test case checks the conversion of a SpanString with font size and background color.
 *           It ensures the HTML correctly applies the background color and font size.
 * @tc.level: 1
 */
HWTEST_F(HtmlConvertTestNg, HtmlConvertExam007, TestSize.Level1)
{
    /**
     * @tc.steps1: Create a SpanString with the text "这段文本有黄色背景，字体大小为50px，用于测试背景颜色转换。"
     *             and apply paragraph styles with font-size (50px) and background-color (yellow).
     * @tc.expected: The generated HTML should include the font size and background color styles.
     */
    const std::string multiHtml =
        "<html>"
        "<head>"
        "</head>"
        "<body>"
        "<p style=\"font-size:50px;background-color:yellow;\">"
        "这段文本有黄色背景，字体大小为50px，用于测试背景颜色转换。"
        "</p>"
        "</body>"
        "</html>";
    
    /**
     * @tc.steps2: Convert the HTML string to SpanString and then back to HTML.
     *             The result should match the original input HTML.
     * @tc.expected: The generated SpanString should match the original input HTML.
     */
    HtmlToSpan toSpan;
    auto dstSpan = toSpan.ToSpanString(multiHtml);
    EXPECT_EQ(dstSpan->GetSpanItems().size(), 1);
    SpanToHtml convert;

    auto dstHtml = convert.ToHtml(*dstSpan);
    EXPECT_GT(dstHtml.size(), 0);  // dstHtml is converted
    HtmlToSpan toSpan1;
    auto dstSpan1 = toSpan1.ToSpanString(dstHtml);
    EXPECT_EQ(IsSpanItemSame(dstSpan->GetSpanItems(), dstSpan1->GetSpanItems()), true);
    auto secondHtml = convert.ToHtml(*dstSpan1);
    EXPECT_EQ(secondHtml, dstHtml);
}

/**
 * @tc.name: HtmlConvertExam008
 * @tc.desc: This test case checks the conversion of a SpanString with different font sizes and letter spacing.
 *           It ensures the HTML correctly reflects the application of font size and letter spacing.
 * @tc.level: 1
 */
HWTEST_F(HtmlConvertTestNg, HtmlConvertExam008, TestSize.Level1)
{
    /**
     * @tc.steps1: Create a SpanString with the text "这段文字有5px的字母间距，字体大小为50px。"
     *             and apply paragraph styles with font-size (50px) and letter-spacing (5px).
     *             Add a span with font-size (30px) and letter-spacing (2px).
     * @tc.expected: The generated HTML should include correct font sizes and letter spacing.
     */
    const std::string multiHtml =
        "<html>"
        "<head>"
        "</head>"
        "<body>"
        "<p style=\"font-size:50px;letter-spacing:5px;\">"
        "这段文字有5px的字母间距，字体大小为50px。<span style=\"font-size:30px;letter-spacing:2px;\">"
        "这一部分有2px字母间距和30px字体大小。</span>"
        "</p>"
        "</body>"
        "</html>";
    
    /**
     * @tc.steps2: Convert the HTML string to SpanString and then back to HTML.
     *             The result should match the original input HTML.
     * @tc.expected: The generated SpanString should match the original input HTML.
     */
    HtmlToSpan toSpan;
    auto dstSpan = toSpan.ToSpanString(multiHtml);
    EXPECT_EQ(dstSpan->GetSpanItems().size(), 2);
    SpanToHtml convert;

    auto dstHtml = convert.ToHtml(*dstSpan);
    EXPECT_GT(dstHtml.size(), 0);  // dstHtml is converted
    HtmlToSpan toSpan1;
    auto dstSpan1 = toSpan1.ToSpanString(dstHtml);
    EXPECT_EQ(IsSpanItemSame(dstSpan->GetSpanItems(), dstSpan1->GetSpanItems()), true);
    auto secondHtml = convert.ToHtml(*dstSpan1);
    EXPECT_EQ(secondHtml, dstHtml);
}

/**
 * @tc.name: HtmlConvertExam009
 * @tc.desc: This test case checks the conversion of a SpanString with text color and multiple shadows.
 *           It ensures the HTML correctly applies text color and shadow effects.
 * @tc.level: 1
 */
HWTEST_F(HtmlConvertTestNg, HtmlConvertExam009, TestSize.Level1)
{
    /**
     * @tc.steps1: Create a SpanString with the text "这段文本具有红色文本颜色和两个阴影效果（蓝色和绿色）。"
     *             and apply the paragraph styles with text color (red) and multiple text shadows (blue and green).
     * @tc.expected: The generated HTML should include the correct text color and shadow effects.
     */
    const std::string multiHtml =
        "<html>"
        "<head>"
        "</head>"
        "<body>"
        "<p style=\"font-size:50px;color:red;text-shadow:0px 0px 5px blue, 2px 2px 3px green;\">"
        "这段文本具有红色文本颜色和两个阴影效果（蓝色和绿色）。"
        "</p>"
        "</body>"
        "</html>";
    
    /**
     * @tc.steps2: Convert the HTML string to SpanString and then back to HTML.
     *             The result should match the original input HTML.
     * @tc.expected: The generated HTML should match the original input HTML.
     */
    HtmlToSpan toSpan;
    auto dstSpan = toSpan.ToSpanString(multiHtml);
    EXPECT_EQ(dstSpan->GetSpanItems().size(), 1);
    SpanToHtml convert;

    auto dstHtml = convert.ToHtml(*dstSpan);
    EXPECT_GT(dstHtml.size(), 0);  // dstHtml is converted
    HtmlToSpan toSpan1;
    auto dstSpan1 = toSpan1.ToSpanString(dstHtml);
    EXPECT_EQ(IsSpanItemSame(dstSpan->GetSpanItems(), dstSpan1->GetSpanItems()), true);
    auto secondHtml = convert.ToHtml(*dstSpan1);
    EXPECT_EQ(secondHtml, dstHtml);
}

/**
 * @tc.name: HtmlConvertExam010
 * @tc.desc: This test case checks the conversion of a SpanString with font size, text color,
 *           text decoration, and text shadow. It ensures all styles are correctly applied in the generated SpanString.
 * @tc.level: 1
 */
HWTEST_F(HtmlConvertTestNg, HtmlConvertExam010, TestSize.Level1)
{
    /**
     * @tc.steps1: Create a SpanString with the text and apply the paragraph styles with font-size (50px),
                   color (red), text-decoration (underline), and text-shadow (blue).
     * @tc.expected: The generated HTML should include all styles: font size, color, text decoration, and shadow.
     */
    const std::string multiHtml =
        "<html>"
        "<head>"
        "</head>"
        "<body>"
        "<p style=\"font-size:50px;color:red;text-decoration:underline;text-shadow:0px 0px 5px blue;\">"
        "这段文本为红色，有下划线，并且有一个蓝色阴影效果，字体大小为50px。"
        "</p>"
        "</body>"
        "</html>";
    
    /**
     * @tc.steps2: Convert the HTML string to SpanString and then back to HTML.
     *             The result should match the original input HTML.
     * @tc.expected: The generated HTML should match the original input HTML.
     */
    HtmlToSpan toSpan;
    auto dstSpan = toSpan.ToSpanString(multiHtml);
    EXPECT_EQ(dstSpan->GetSpanItems().size(), 1);
    SpanToHtml convert;

    auto dstHtml = convert.ToHtml(*dstSpan);
    EXPECT_GT(dstHtml.size(), 0);  // dstHtml is converted
    HtmlToSpan toSpan1;
    auto dstSpan1 = toSpan1.ToSpanString(dstHtml);
    EXPECT_EQ(IsSpanItemSame(dstSpan->GetSpanItems(), dstSpan1->GetSpanItems()), true);
    auto secondHtml = convert.ToHtml(*dstSpan1);
    EXPECT_EQ(secondHtml, dstHtml);
}

/**
 * @tc.name: MultiHtmlConvert
 * @tc.desc: This test case checks the conversion of HTML with different text-decoration styles
 *           (underline, strike-through, overline).
 * @tc.level: 1
 */
HWTEST_F(HtmlConvertTestNg, MultiHtmlConvert, TestSize.Level1)
{
    /**
     * @tc.steps1: Test conversion with `text-decoration` values: `underline`, `line-through`, and `overline`.
     * @tc.expected: Each text-decoration style should be correctly applied to the resulting `SpanString`.
     */
    const std::string multiHtml = "<html>"
                                  "<body>"
                                  "<p style=\"text-decoration:underline;\">Underlined Text</p>"
                                  "<p style=\"text-decoration:line-through;\">Strikethrough Text</p>"
                                  "<p style=\"text-decoration:overline;\">Overlined Text</p>"
                                  "</body>"
                                  "</html>";
    HtmlToSpan toSpan;
    auto dstSpan = toSpan.ToSpanString(multiHtml);

    /**
     * @tc.steps2: Verify the size of the converted `SpanString`.
     *             It should have 3 span items for the 3 different text-decoration styles.
     * @tc.expected: The size of the spans list should be 3.
     */
    std::list<RefPtr<NG::SpanItem>> spans = dstSpan->GetSpanItems();
    EXPECT_EQ(spans.size(), 3);

    /**
     * @tc.steps3: Verify that the first span item has the `underline` text-decoration.
     * @tc.expected: The first span item should have the `underline` text-decoration.
     */
    auto it = spans.begin();
    EXPECT_EQ((*it)->fontStyle->GetTextDecoration().value(), TextDecoration::UNDERLINE);

    /**
     * @tc.steps4: Verify that the second span item has the `line-through` text-decoration.
     * @tc.expected: The second span item should have the `line-through` text-decoration.
     */
    ++it;
    EXPECT_EQ((*it)->fontStyle->GetTextDecoration().value(), TextDecoration::LINE_THROUGH);

    /**
     * @tc.steps5: Verify that the third span item has the `overline` text-decoration.
     * @tc.expected: The third span item should have the `overline` text-decoration.
     */
    ++it;
    EXPECT_EQ((*it)->fontStyle->GetTextDecoration().value(), TextDecoration::OVERLINE);
}

} // namespace OHOS::Ace::NG