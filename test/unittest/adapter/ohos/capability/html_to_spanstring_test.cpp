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
 * @tc.name: HtmlConvertComplex01
 * @tc.desc: This test case checks the conversion of a span string with various complex styles like font,
 *           letter spacing, background color, line height, text shadow, image spans, and paragraph styles.
 *           It ensures that all styles are properly applied and the correct number of span items is produced.
 * @tc.level: 1
 */
HWTEST_F(HtmlConvertTestNg, HtmlConvertComplex01, TestSize.Level1)
{
    /**
     * @tc.steps1: Initialize mutable SpanString and add a variety of styles like font, letter spacing,
     *             background color, line height, and text shadow.
     * @tc.expected: Span string should apply all styles correctly and be ready for conversion.
     */
    auto imageOption = GetImageOption("src/icon-2.png");
    auto mutableStr = AceType::MakeRefPtr<MutableSpanString>(imageOption);
    auto spanString3 = AceType::MakeRefPtr<SpanString>(u"Hello World! This is a test to cover complex cases.");

    // Adding Font Spans
    spanString3->AddSpan(AceType::MakeRefPtr<FontSpan>(testFont1, 0, 5));
    spanString3->AddSpan(AceType::MakeRefPtr<FontSpan>(testFont2, 6, 11));

    // Adding Letter Spacing
    spanString3->AddSpan(AceType::MakeRefPtr<LetterSpacingSpan>(Dimension(3), 12, 18));

    // Adding Background Color Span
    NG::BorderRadiusProperty borderRadius;
    borderRadius.radiusTopLeft = Dimension(0, OHOS::Ace::DimensionUnit::VP);
    borderRadius.radiusTopRight = Dimension(0, OHOS::Ace::DimensionUnit::VP);
    borderRadius.radiusBottomLeft = Dimension(0, OHOS::Ace::DimensionUnit::VP);
    borderRadius.radiusBottomRight = Dimension(0, OHOS::Ace::DimensionUnit::VP);
    TextBackgroundStyle textBackgroundStyle;
    textBackgroundStyle.backgroundColor = Color::RED;
    textBackgroundStyle.backgroundRadius = borderRadius;
    spanString3->AddSpan(AceType::MakeRefPtr<BackgroundColorSpan>(textBackgroundStyle, 19, 25));

    // Adding Line Height Span
    spanString3->AddSpan(AceType::MakeRefPtr<LineHeightSpan>(Dimension(1.5), 26, 32));

    // Adding Text Shadow Span
    Shadow shadow1;
    shadow1.SetBlurRadius(2.0);
    shadow1.SetColor(Color::RED);
    shadow1.SetOffsetX(4.0);
    shadow1.SetOffsetY(4.0);
    
    spanString3->AddSpan(AceType::MakeRefPtr<TextShadowSpan>(std::vector<Shadow>{shadow1}, 15, 25));

    // Adding Image Span
    auto imageSpan = AceType::MakeRefPtr<ImageSpan>(imageOption);
    spanString3->AddSpan(imageSpan);

    // Adding a complex Paragraph Style
    auto paragraphStyle = GetDefaultParagraphStyle();
    auto paraSpan = AceType::MakeRefPtr<ParagraphStyleSpan>(paragraphStyle, 8, 15);
    spanString3->AddSpan(paraSpan);

    mutableStr->InsertSpanString(0, spanString3);

    /**
     * @tc.steps2: Create a new SpanString with Chinese content and more complex styles,
     *             and insert into mutable string.
     * @tc.expected: Correct application of font, letter spacing, and span insertion.
     */
    auto spanString2 = AceType::MakeRefPtr<SpanString>(u"中文文本，包含更多复杂的样式。123456");
    spanString2->AddSpan(AceType::MakeRefPtr<FontSpan>(testFont1, 0, 2));
    spanString2->AddSpan(AceType::MakeRefPtr<FontSpan>(testFont2, 3, 6));
    spanString2->AddSpan(AceType::MakeRefPtr<LetterSpacingSpan>(Dimension(8), 7, 10));

    mutableStr->InsertSpanString(16, spanString2);

    /**
     * @tc.steps3: Call the conversion function to convert the mutable span string to HTML.
     * @tc.expected: Ensure that the conversion correctly maintains all span properties and styles.
     */
    SpanToHtml convert;
    auto out = convert.ToHtml(*mutableStr);

    /**
     * @tc.steps4: Convert HTML back to SpanString and validate the number of span items.
     * @tc.expected: The number of span items should match the total number of spans added.
     */
    HtmlToSpan toSpan;
    auto dstSpan = toSpan.ToSpanString(out);
    EXPECT_NE(dstSpan, nullptr);
    auto items = dstSpan->GetSpanItems();
    EXPECT_EQ(items.size(), 22);
}

/**
 * @tc.name: HtmlConvertComplex02
 * @tc.desc: This test case checks the conversion of a span string with nested and complex styles like
 *           font spans, letter spacing, background color, and image spans. It ensures that the nested
 *           styles are applied correctly and that the correct number of span items is produced.
 * @tc.level: 1
 */
HWTEST_F(HtmlConvertTestNg, HtmlConvertComplex02, TestSize.Level1)
{
    /**
     * @tc.steps1: Initialize mutable SpanString and add various font, letter spacing, background color,
     *             and image spans in a nested manner.
     * @tc.expected: Nested and complex spans should be applied correctly.
     */
    auto mutableStr = AceType::MakeRefPtr<MutableSpanString>(imageOption1);
    auto spanString4 = AceType::MakeRefPtr<SpanString>(u"Complex Nested Styles Test: Begin");

    // Add some font spans with different styles
    spanString4->AddSpan(AceType::MakeRefPtr<FontSpan>(testFont1, 0, 7));
    spanString4->AddSpan(AceType::MakeRefPtr<FontSpan>(testFont2, 8, 15));
    spanString4->AddSpan(AceType::MakeRefPtr<FontSpan>(testFont1, 16, 21));

    // Add multiple letter spacing spans
    spanString4->AddSpan(AceType::MakeRefPtr<LetterSpacingSpan>(Dimension(5), 5, 10));
    spanString4->AddSpan(AceType::MakeRefPtr<LetterSpacingSpan>(Dimension(2), 12, 18));

    // Add Background Color Span for a range
    NG::BorderRadiusProperty borderRadius;
    borderRadius.radiusTopLeft = Dimension(4, OHOS::Ace::DimensionUnit::FP);
    borderRadius.radiusTopRight = Dimension(3, OHOS::Ace::DimensionUnit::FP);
    borderRadius.radiusBottomLeft = Dimension(5, OHOS::Ace::DimensionUnit::FP);
    borderRadius.radiusBottomRight = Dimension(7, OHOS::Ace::DimensionUnit::FP);
    TextBackgroundStyle textBackgroundStyle;
    textBackgroundStyle.backgroundColor = Color::RED;
    textBackgroundStyle.backgroundRadius = borderRadius;
    spanString4->AddSpan(AceType::MakeRefPtr<BackgroundColorSpan>(textBackgroundStyle, 5, 15));

    // Add Image Span at the end
    auto imageSpan = AceType::MakeRefPtr<ImageSpan>(imageOption2);
    spanString4->AddSpan(imageSpan);

    mutableStr->InsertSpanString(0, spanString4);

    /**
     * @tc.steps2: Create another SpanString with more complex Chinese content,
     *             add font spans, letter spacing, and text shadow, and insert it into mutable string.
     * @tc.expected: The second span string with additional styles should be properly inserted and applied.
     */
    auto spanString5 = AceType::MakeRefPtr<SpanString>(u"进一步增加复杂性，测试多个样式的组合应用。");
    spanString5->AddSpan(AceType::MakeRefPtr<FontSpan>(testFont2, 0, 4));
    spanString5->AddSpan(AceType::MakeRefPtr<FontSpan>(testFont1, 5, 9));
    spanString5->AddSpan(AceType::MakeRefPtr<LetterSpacingSpan>(Dimension(7), 9, 14));

    Shadow shadow1;
    shadow1.SetBlurRadius(10.0);
    shadow1.SetColor(Color::RED);
    shadow1.SetOffsetX(-10.0);
    shadow1.SetOffsetY(0.0);
    spanString5->AddSpan(AceType::MakeRefPtr<TextShadowSpan>(std::vector<Shadow>{shadow1}, 10, 20));

    mutableStr->InsertSpanString(10, spanString5);

    /**
     * @tc.steps3: Call the conversion function to convert the mutable span string to HTML.
     * @tc.expected: Ensure that the conversion correctly maintains all nested and complex span properties.
     */
    SpanToHtml convert;
    auto out = convert.ToHtml(*mutableStr);
    
    /**
     * @tc.steps4: Convert HTML back to SpanString and validate the number of span items.
     * @tc.expected: The number of span items should match the total number of spans added.
     */
    HtmlToSpan toSpan;
    auto dstSpan = toSpan.ToSpanString(out);
    EXPECT_NE(dstSpan, nullptr);
    auto items = dstSpan->GetSpanItems();
    EXPECT_EQ(items.size(), 20);
}

/**
 * @tc.name: HtmlConvertComplex03
 * @tc.desc: This test case verifies the conversion of a very large text block with multiple font spans,
 *           letter spacing, background color, and text shadow applied in various iterations. It ensures
 *           that the correct number of span items is produced and that the styles are applied consistently.
 * @tc.level: 1
 */
HWTEST_F(HtmlConvertTestNg, HtmlConvertComplex03, TestSize.Level1)
{
    /**
     * @tc.steps1: Initialize mutable SpanString with a large text block and apply various font,
     *             letter spacing, and other styles.
     * @tc.expected: Large text block with correct number of spans, properly applied styles, and correct span count.
     */
    auto mutableStr = AceType::MakeRefPtr<MutableSpanString>(imageOption3);
    
    // Test with a very large text block, mimicking an article
    std::u16string largeText = u"这是一段包含多个字体和样式的大段文本。我们将使用不同的样式组合来测试转换的效果。";
    auto spanString6 = AceType::MakeRefPtr<SpanString>(largeText);
    
    // Apply multiple font spans with varied fonts
    spanString6->AddSpan(AceType::MakeRefPtr<FontSpan>(testFont1, 0, 5));
    spanString6->AddSpan(AceType::MakeRefPtr<FontSpan>(testFont2, 6, 10));
    spanString6->AddSpan(AceType::MakeRefPtr<FontSpan>(testFont1, 11, 15));
    
    // Add a large number of letter spacing spans
    for (int i = 0; i < 20; ++i) {
        spanString6->AddSpan(AceType::MakeRefPtr<LetterSpacingSpan>(Dimension(i), i * 2, i * 3));
    }

    // Add a combination of other spans
    Shadow shadow;
    shadow.SetBlurRadius(2.0);
    shadow.SetColor(Color::TRANSPARENT);
    shadow.SetOffsetX(2.0);
    shadow.SetOffsetY(2.0);
    spanString6->AddSpan(AceType::MakeRefPtr<TextShadowSpan>(std::vector<Shadow>{shadow}, 6, 12));

    NG::BorderRadiusProperty borderRadius;
    borderRadius.radiusTopLeft = Dimension(1, OHOS::Ace::DimensionUnit::AUTO);
    borderRadius.radiusTopRight = Dimension(2, OHOS::Ace::DimensionUnit::AUTO);
    borderRadius.radiusBottomLeft = Dimension(3, OHOS::Ace::DimensionUnit::AUTO);
    borderRadius.radiusBottomRight = Dimension(4, OHOS::Ace::DimensionUnit::AUTO);

    TextBackgroundStyle textBackgroundStyle;
    textBackgroundStyle.backgroundColor = Color::RED;
    textBackgroundStyle.backgroundRadius = borderRadius;
    spanString6->AddSpan(AceType::MakeRefPtr<BackgroundColorSpan>(textBackgroundStyle, 0, 10));

    mutableStr->InsertSpanString(0, spanString6);

    /**
     * @tc.steps2: Convert the large mutable string to HTML format and validate the number of span items.
     * @tc.expected: The conversion should result in a high number of span items due to the large amount of styling.
     */
    SpanToHtml convert;
    auto out = convert.ToHtml(*mutableStr);
    
    HtmlToSpan toSpan;
    auto dstSpan = toSpan.ToSpanString(out);
    EXPECT_NE(dstSpan, nullptr);
    auto items = dstSpan->GetSpanItems();
    EXPECT_EQ(items.size(), 26);
}

/**
 * @tc.name: HtmlConvertComplex04
 * @tc.desc: This test case checks the conversion of multiple text blocks with embedded images and various
 *           styles such as font and letter spacing applied. It verifies the correct insertion of images and
 *           the accurate number of span items after conversion.
 * @tc.level: 3
 */
HWTEST_F(HtmlConvertTestNg, HtmlConvertComplex04, TestSize.Level3)
{
    /**
     * @tc.steps1: Initialize mutable SpanString with imageOption1.
     * @tc.expected: The mutable string should be ready for inserting span strings with various styles and images.
     */
    auto mutableStr = AceType::MakeRefPtr<MutableSpanString>(imageOption1);

    // First text block with an image
    /**
     * @tc.steps2: Create the first text span string and apply font and letter spacing styles to it.
     *             Insert an image (imageOption1) into the text span.
     * @tc.expected: The first span string should be styled correctly and the image should be inserted
     *                at the correct position.
     */
    std::u16string text1 = u"This is the first paragraph with an image display:";
    auto spanString1 = AceType::MakeRefPtr<SpanString>(text1);
    spanString1->AddSpan(AceType::MakeRefPtr<FontSpan>(testFont1, 0, 10)); // "This is the first"
    spanString1->AddSpan(AceType::MakeRefPtr<LetterSpacingSpan>(Dimension(4), 10, 20)); // "paragraph"
    
    // Insert image (using imageOption1)
    auto imageSpan1 = AceType::MakeRefPtr<ImageSpan>(imageOption1);
    spanString1->AddSpan(imageSpan1);

    mutableStr->InsertSpanString(0, spanString1);

    // Second text block with different image configurations
    /**
     * @tc.steps3: Create the second text span string and apply font and letter spacing styles.
     *             Insert a different image (imageOption2) into this span string.
     * @tc.expected: The second span string should have proper font styles, letter spacing, and image insertion.
     */
    std::u16string text2 = u"The second paragraph with different image configurations:";
    auto spanString2 = AceType::MakeRefPtr<SpanString>(text2);
    spanString2->AddSpan(AceType::MakeRefPtr<FontSpan>(testFont2, 0, 10)); // "The second"
    spanString2->AddSpan(AceType::MakeRefPtr<FontSpan>(testFont1, 11, 18)); // "paragraph"
    spanString2->AddSpan(AceType::MakeRefPtr<LetterSpacingSpan>(Dimension(6), 18, 25)); // "with different"
    
    // Insert image (using imageOption2)
    auto imageSpan2 = AceType::MakeRefPtr<ImageSpan>(imageOption2);
    spanString2->AddSpan(imageSpan2);

    mutableStr->InsertSpanString(30, spanString2);

    // Third text block with more images
    /**
     * @tc.steps4: Create the third text span string and apply font and letter spacing styles.
     *             Insert an image (imageOption3) into this span string.
     * @tc.expected: The third span string should have the correct styles and image insertion.
     */
    std::u16string text3 = u"The third paragraph showcasing another image configuration:";
    auto spanString3 = AceType::MakeRefPtr<SpanString>(text3);
    spanString3->AddSpan(AceType::MakeRefPtr<FontSpan>(testFont1, 0, 10)); // "The third"
    spanString3->AddSpan(AceType::MakeRefPtr<FontSpan>(testFont2, 11, 15)); // "paragraph"
    spanString3->AddSpan(AceType::MakeRefPtr<LetterSpacingSpan>(Dimension(3), 15, 20)); // "showcasing"
    
    // Insert image (using imageOption3)
    auto imageSpan3 = AceType::MakeRefPtr<ImageSpan>(imageOption3);
    spanString3->AddSpan(imageSpan3);

    mutableStr->InsertSpanString(50, spanString3);

    // Fourth text block with the final image
    /**
     * @tc.steps5: Create the fourth text span string and apply font and letter spacing styles.
     *             Insert the final image (imageOption4) into this span string.
     * @tc.expected: The fourth span string should be styled correctly and the image should
     *               be inserted at the right position.
     */
    std::u16string text4 = u"The final paragraph showcasing the last image configuration:";
    auto spanString4 = AceType::MakeRefPtr<SpanString>(text4);
    spanString4->AddSpan(AceType::MakeRefPtr<FontSpan>(testFont2, 0, 10)); // "The final"
    spanString4->AddSpan(AceType::MakeRefPtr<LetterSpacingSpan>(Dimension(4), 10, 18)); // "paragraph"
    
    // Insert image (using imageOption4)
    auto imageSpan4 = AceType::MakeRefPtr<ImageSpan>(imageOption4);
    spanString4->AddSpan(imageSpan4);

    mutableStr->InsertSpanString(70, spanString4);

    /**
     * @tc.steps6: Convert the entire mutable string to HTML format and verify the result.
     * @tc.expected: The conversion should result in the correct number of span items,
     *               including those with images and different styles.
     */
    SpanToHtml convert;
    auto out = convert.ToHtml(*mutableStr);
    
    HtmlToSpan toSpan;
    auto dstSpan = toSpan.ToSpanString(out);
    EXPECT_NE(dstSpan, nullptr);
    auto items = dstSpan->GetSpanItems();
    
    EXPECT_EQ(items.size(), 24);
}

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

} // namespace OHOS::Ace::NG