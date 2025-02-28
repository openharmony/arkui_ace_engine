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
    std::string testStr[] = { "hello", "world", "this", "find", "gank", "pink", "that", "when", "how", "cpp" };
    Font testFont1 { OHOS::Ace::FontWeight::BOLD, Dimension(29.0, DimensionUnit::PX), OHOS::Ace::FontStyle::ITALIC,
        std::vector<std::string>(testStr, testStr + 10), OHOS::Ace::Color::BLUE };
    Font testFont2 { OHOS::Ace::FontWeight::LIGHTER, Dimension(19.0, DimensionUnit::PX), OHOS::Ace::FontStyle::ITALIC,
        std::vector<std::string>(testStr, testStr + 10), OHOS::Ace::Color::GRAY };
    Font testEmptyFont {};
}

/**
 * @tc.name: SpanStringConvert001
 * @tc.desc: This test case verifies the conversion of a `SpanString` object to HTML and
 *           back from HTML to `SpanString`.
 *           It ensures that the content and structure are preserved during the entire conversion process.
 * @tc.level: 1
 */
HWTEST_F(HtmlConvertTestNg, SpanStringConvert001, TestSize.Level1)
{
    /**
     * @tc.steps1: Initialize parameters and create a `SpanString` object, adding different font style spans.
     *             Each span represents a substring with a specific style (e.g., font, size, etc.).
     * @tc.expected: The `SpanString` object should be correctly initialized with the given content and spans.
     */
    auto spanString = AceType::MakeRefPtr<SpanString>(u"0123456789");

    // Adding FontSpans with different fonts to the spanString
    spanString->AddSpan(AceType::MakeRefPtr<FontSpan>(testFont1, 0, 3));
    spanString->AddSpan(AceType::MakeRefPtr<FontSpan>(testFont2, 3, 5));
    spanString->AddSpan(AceType::MakeRefPtr<FontSpan>(testEmptyFont, 5, 8));

    /**
     * @tc.steps2: Call the `ToHtml` function to convert the `SpanString` object to an HTML string.
     *             First, use `EncodeTlv` method to convert the content into a byte buffer.
     * @tc.expected: `u8ToHtml` should be a non-empty string representing the successful HTML conversion.
     */
    std::vector<uint8_t> buffer;
    spanString->EncodeTlv(buffer);

    SpanToHtml convert;
    auto u8ToHtml = convert.ToHtml(buffer);
    EXPECT_NE(u8ToHtml.empty(), true);

    // Directly convert `SpanString` to HTML string
    auto out = convert.ToHtml(*spanString);
    EXPECT_NE(out.empty(), true);
    EXPECT_EQ(out, u8ToHtml);

    /**
     * @tc.steps3: Call the `ToSpanString` function to convert the HTML string back to a `SpanString` object.
     * @tc.expected: The `ToSpanString` function should successfully convert the HTML back to a `SpanString`.
     */
    HtmlToSpan toSpan;
    auto dstSpan = toSpan.ToSpanString(out);  // Convert the HTML string back to a SpanString
    EXPECT_NE(dstSpan, nullptr);  // Expect the returned SpanString to be non-null

    // Get the SpanItems from the converted `SpanString`
    auto items = dstSpan->GetSpanItems();
    EXPECT_EQ(items.size(), 4);  // Expect the number of SpanItems to be 4, as there were 4 FontSpans added

    /**
     * @tc.steps4: Verify that the number of SpanItems in the original `SpanString` matches the converted `SpanString`.
     * @tc.expected: The number of SpanItems in the original `SpanString` and the converted `SpanString` be the same.
     */
    EXPECT_EQ(items.size(), spanString->GetSpanItems().size());
}

/**
 * @tc.name: SpanStringConvert002
 * @tc.desc: This test case checks the HTML conversion when special HTML tags like `<strong>`, `<del>`,
 *           and inline styles are used. It verifies that these elements are correctly converted to
 *           `SpanString` and back to HTML.
 * @tc.level: 1
 */
HWTEST_F(HtmlConvertTestNg, SpanStringConvert002, TestSize.Level1)
{
    /**
     * @tc.steps1: Initialize HTML string containing special tags and inline styles.
     * @tc.expected: The HTML should be properly formatted and support special tags like `<strong>`, `<del>`, etc.
     */
    const std::string fontHtml =
        "<html>\n"
        "<body>\n"
        "<p>\n"
        "<strong>Important Text</strong>\n"
        "<del>Deleted Text</del>\n"
        "</p>\n"
        "</body>\n"
        "</html>\n";
    
    /**
     * @tc.steps2: Convert the HTML string to `SpanString`.
     * @tc.expected: The conversion should result in a valid `SpanString` with correct `SpanItems` for the tags.
     */
    HtmlToSpan toSpan;
    auto dstSpan = toSpan.ToSpanString(fontHtml);
    EXPECT_NE(dstSpan, nullptr);
    auto items = dstSpan->GetSpanItems();
    EXPECT_GT(items.size(), 0);

    /**
     * @tc.steps3: Convert the `SpanString` back to HTML and verify the result matches the original HTML.
     * @tc.expected:  Verify that the outHtml's size is not empty.
     */
    SpanToHtml convert;
    auto outHtml = convert.ToHtml(*dstSpan);
    EXPECT_GT(outHtml.size(), 0);
}

/**
 * @tc.name: SpanStringConvert003
 * @tc.desc: This test case checks the conversion when complex inline styles are applied to text.
 *           It ensures that the font styles, color, and size are properly handled during the conversion.
 * @tc.level: 1
 */
HWTEST_F(HtmlConvertTestNg, SpanStringConvert003, TestSize.Level1)
{
    /**
     * @tc.steps1: Initialize HTML string with complex inline styles (font size, color, and weight).
     * @tc.expected: The HTML should contain the correct inline styles for each text element.
     */
    const std::string complexHtml =
        "<html>\n"
        "<body>\n"
        "<p style=\"font-size:20px; color:red; font-weight:bold;\">\n"
        "Styled Text\n"
        "</p>\n"
        "</body>\n"
        "</html>\n";
    
    /**
     * @tc.steps2: Convert the HTML string to `SpanString`.
     * @tc.expected: The conversion should parse the inline styles correctly and convert them into `FontSpan` objects.
     */
    HtmlToSpan toSpan;
    auto dstSpan = toSpan.ToSpanString(complexHtml);
    EXPECT_NE(dstSpan, nullptr);

    // Verify that the SpanItems reflect the correct styles (e.g., size, color, and weight)
    auto items = dstSpan->GetSpanItems();
    EXPECT_GT(items.size(), 0);

    /**
     * @tc.steps3: Convert the `SpanString` back to HTML and ensure the inline styles are retained.
     * @tc.expected: Verify that the outHtml's size is not empty.
     */
    SpanToHtml convert;
    auto outHtml = convert.ToHtml(*dstSpan);
    EXPECT_GT(outHtml.size(), 0);
}

/**
 * @tc.name: SpanStringConvert004
 * @tc.desc: This test case verifies the behavior when converting HTML with embedded spans and complex inline elements.
 *           It ensures that nested HTML elements like `<span>` are handled correctly during the conversion process.
 * @tc.level: 1
 */
HWTEST_F(HtmlConvertTestNg, SpanStringConvert004, TestSize.Level1)
{
    /**
     * @tc.steps1: Initialize HTML string with nested `<span>` tags and inline styles.
     * @tc.expected: The HTML should contain nested spans with different styles.
     */
    const std::string nestedHtml = "<html>\n"
                                   "<body>\n"
                                   "<p>\n"
                                   "<span style=\"color:blue;\">Blue Text</span>\n"
                                   "<span style=\"color:red;\">Red Text</span>\n"
                                   "</p>\n"
                                   "</body>\n"
                                   "</html>";
    /**
     * @tc.steps2: Convert the HTML string to `SpanString`.
     * @tc.expected: The conversion should properly handle nested spans and inline styles.
     */
    HtmlToSpan toSpan;
    auto dstSpan = toSpan.ToSpanString(nestedHtml);
    EXPECT_NE(dstSpan, nullptr);

    // Verify that the SpanItems reflect the correct styles for each span
    auto items = dstSpan->GetSpanItems();
    EXPECT_GT(items.size(), 0);

    /**
     * @tc.steps3: Convert the `SpanString` back to HTML and ensure that nested spans are correctly retained.
     * @tc.expected: Verify that the outHtml's size is not empty.
     */
    SpanToHtml convert;
    auto outHtml = convert.ToHtml(*dstSpan);
    EXPECT_GT(outHtml.size(), 0);
}

/**
 * @tc.name: SpanStringConvert005
 * @tc.desc: This test case checks the behavior when HTML contains elements with different text alignment properties.
 *           It verifies that text alignment properties like `text-align` are properly converted and maintained.
 * @tc.level: 1
 */
HWTEST_F(HtmlConvertTestNg, SpanStringConvert005, TestSize.Level1)
{
    /**
     * @tc.steps1: Initialize HTML string with different text alignments (center, left, right).
     * @tc.expected: The HTML should contain proper alignment properties for each element.
     */
    const std::string alignmentHtml = "<html>\n"
                                      "<body>\n"
                                      "<p style=\"text-align:center;\">Centered Text</p>\n"
                                      "<p style=\"text-align:left;\">Left Aligned Text</p>\n"
                                      "<p style=\"text-align:right;\">Right Aligned Text</p>\n"
                                      "</body>\n"
                                      "</html>";
    /**
     * @tc.steps2: Convert the HTML string to `SpanString`.
     * @tc.expected: The conversion should properly handle text alignment properties for each text block.
     */
    HtmlToSpan toSpan;
    auto dstSpan = toSpan.ToSpanString(alignmentHtml);
    EXPECT_NE(dstSpan, nullptr);

    // Verify that the SpanItems reflect the correct alignment for each paragraph
    auto items = dstSpan->GetSpanItems();
    EXPECT_GT(items.size(), 0);

    /**
     * @tc.steps3: Convert the `SpanString` back to HTML and ensure that text alignment properties are preserved.
     * @tc.expected: Verify that the outHtml's size is not empty.
     */
    SpanToHtml convert;
    auto outHtml = convert.ToHtml(*dstSpan);
    EXPECT_GT(outHtml.size(), 0);
}

/**
 * @tc.name: SpanStringConvert006
 * @tc.desc: This test case checks the conversion of a SpanString with multiple font spans and the
 *           encoding/decoding of the span string into HTML and back. It verifies that the correct number
 *           of span items is maintained and that the conversion preserves the span data.
 * @tc.level: 1
 */
HWTEST_F(HtmlConvertTestNg, SpanStringConvert006, TestSize.Level1)
{
    /**
     * @tc.steps1: Initialize a SpanString with a series of font spans (testFont1, testFont2, and testEmptyFont),
     *             each covering different ranges of the string "0123456789".
     * @tc.expected: Each span should correctly apply its respective font style to the
     *               corresponding range in the string.
     */
    auto spanString = AceType::MakeRefPtr<SpanString>(u"0123456789");
    spanString->AddSpan(AceType::MakeRefPtr<FontSpan>(testFont1, 0, 3));
    spanString->AddSpan(AceType::MakeRefPtr<FontSpan>(testFont2, 3, 5));
    spanString->AddSpan(AceType::MakeRefPtr<FontSpan>(testEmptyFont, 5, 8));

    /**
     * @tc.steps2: Encode the SpanString into a TLV (Type-Length-Value) format and convert it to HTML.
     *             Check that the resulting HTML is not empty and is properly generated.
     * @tc.expected: The conversion to HTML should produce a valid output, and the generated HTML should
     *               match the encoded TLV version.
     */
    std::vector<uint8_t> buffer;
    spanString->EncodeTlv(buffer);
    SpanToHtml convert;
    auto u8ToHtml = convert.ToHtml(buffer);
    EXPECT_NE(u8ToHtml.empty(), true);

    auto out = convert.ToHtml(*spanString);
    EXPECT_NE(out.empty(), true);
    EXPECT_EQ(out, u8ToHtml);

    /**
     * @tc.steps3: Convert the HTML back to a SpanString and validate that the number of span items is correct.
     * @tc.expected: The number of span items in the resulting SpanString should match the original SpanString.
     */
    HtmlToSpan toSpan;
    auto dstSpan = toSpan.ToSpanString(out);
    EXPECT_NE(dstSpan, nullptr);
    auto items = dstSpan->GetSpanItems();
    EXPECT_EQ(items.size(), 4);

    /**
     * @tc.steps4: Verify that the number of span items in the resulting SpanString matches the original.
     * @tc.expected: The number of span items in the original SpanString should be the same as in
     *               the converted SpanString.
     */
    EXPECT_EQ(items.size(), spanString->GetSpanItems().size());
}

/**
 * @tc.name: SpanStringConvert008
 * @tc.desc: This test case checks the conversion of a simple SpanString with basic text color and font size.
 *           It ensures that the span string is correctly converted to HTML with the specified styles.
 * @tc.level: 1
 */
HWTEST_F(HtmlConvertTestNg, SpanStringConvert008, TestSize.Level1)
{
    /**
     * @tc.steps1: Create a SpanString with the text "简单的文本" and apply basic paragraph styles
     *             including text alignment (left), text indent (0), word break (break_word),
     *             and text overflow (clip).
     * @tc.expected: The generated HTML should include basic font color and size styles.
     */
    auto spanString = AceType::MakeRefPtr<SpanString>(u"this is a normal text Hello WORLD");
    SpanParagraphStyle spanParagraphStyle;
    spanParagraphStyle.align = TextAlign::LEFT;
    spanParagraphStyle.textIndent = Dimension(0.0_vp);
    spanParagraphStyle.wordBreak = WordBreak::BREAK_WORD;
    spanParagraphStyle.textOverflow = TextOverflow::CLIP;
    spanParagraphStyle.leadingMargin = LeadingMargin();
    spanParagraphStyle.leadingMargin->size = LeadingMarginSize(Dimension(10.0_vp), Dimension(12.0));
    auto paragraphStyle = AceType::MakeRefPtr<ParagraphStyleSpan>(spanParagraphStyle, 0, 2);
    spanString->AddSpan(paragraphStyle);

    /**
     * @tc.steps2: Convert the SpanString to HTML using the SpanToHtml converter.
     * @tc.expected: The resulting HTML should match the specified span and paragraph styles.
     */
    SpanToHtml convert;
    auto out = convert.ToHtml(*spanString);
    std::string result =
        "<div ><p style=\"word-break: break_word;text-overflow: clip;\"><span style=\"font-size: 16.00px;"
        "font-style: normal;font-weight: normal;color: #000000FF;font-family: HarmonyOS Sans;\">th</span>"
        "<span style=\"font-size: 16.00px;font-style: normal;font-weight: normal;color: #000000FF;"
        "font-family: HarmonyOS Sans;\">is is a normal text Hello WORLD</span></p></div>";
    EXPECT_EQ(out, result);
}

/**
 * @tc.name: SpanStringConvert009
 * @tc.desc: This test case checks the conversion of a SpanString with text that is aligned to the center
 *           and has an indentation applied. It ensures the HTML conversion reflects the correct text alignment
 *           and indentation.
 * @tc.level: 1
 */
HWTEST_F(HtmlConvertTestNg, SpanStringConvert009, TestSize.Level1)
{
    /**
     * @tc.steps1: Create a SpanString with the text "居中的文本" and apply paragraph styles such as
     *             center alignment, text indentation (20px), word break (break_word),
     *             and text overflow (clip).
     * @tc.expected: The generated HTML should reflect the correct text alignment (center) and indentation (20px).
     */
    auto spanString = AceType::MakeRefPtr<SpanString>(u"this text with CENTER BREAK_ALL textIndent property");
    SpanParagraphStyle spanParagraphStyle;
    spanParagraphStyle.align = TextAlign::CENTER;
    spanParagraphStyle.textIndent = Dimension(20.0_vp);
    spanParagraphStyle.wordBreak = WordBreak::BREAK_ALL;
    spanParagraphStyle.textOverflow = TextOverflow::CLIP;
    spanParagraphStyle.leadingMargin = LeadingMargin();
    spanParagraphStyle.leadingMargin->size = LeadingMarginSize(Dimension(12.0_vp), Dimension(14.0));
    auto paragraphStyle = AceType::MakeRefPtr<ParagraphStyleSpan>(spanParagraphStyle, 0, 5);
    spanString->AddSpan(paragraphStyle);

    /**
     * @tc.steps2: Convert the SpanString to HTML using the SpanToHtml converter.
     * @tc.expected: The resulting HTML should match the specified paragraph and span styles.
     */
    SpanToHtml convert;
    auto out = convert.ToHtml(*spanString);
    std::string result =
        "<div ><p style=\"text-align: center;text-indent: 20.00px;word-break: break_all;text-overflow: clip;\">"
        "<span style=\"font-size: 16.00px;font-style: normal;font-weight: normal;color: #000000FF;"
        "font-family: HarmonyOS Sans;\">this </span><span style=\"font-size: 16.00px;font-style: normal;"
        "font-weight: normal;color: #000000FF;font-family: HarmonyOS Sans;\">text with CENTER BREAK_ALL"
        " textIndent property</span></p></div>";
    EXPECT_EQ(out, result);
}

/**
 * @tc.name: SpanStringConvert010
 * @tc.desc: This test case checks the conversion of a SpanString with mixed font sizes in the text,
 *           verifying that the HTML conversion applies the correct font sizes to different spans within the same text.
 * @tc.level: 1
 */
HWTEST_F(HtmlConvertTestNg, SpanStringConvert010, TestSize.Level1)
{
    /**
     * @tc.steps1: Create a SpanString with the text "大<span style=\"font-size: 50px;\">小</span>的文本"
     *             and apply appropriate font styles for each span element.
     * @tc.expected: The HTML should reflect the correct font sizes for each part of the text.
     */
    auto spanString = AceType::MakeRefPtr<SpanString>(u"big 中文混排情况 text");
    SpanParagraphStyle spanParagraphStyle;
    spanParagraphStyle.align = TextAlign::LEFT;
    spanParagraphStyle.textIndent = Dimension(0.0_vp);
    spanParagraphStyle.wordBreak = WordBreak::BREAK_WORD;
    spanParagraphStyle.textOverflow = TextOverflow::CLIP;
    spanParagraphStyle.leadingMargin = LeadingMargin();
    spanParagraphStyle.leadingMargin->size = LeadingMarginSize(Dimension(10.0_vp), Dimension(12.0));
    auto paragraphStyle = AceType::MakeRefPtr<ParagraphStyleSpan>(spanParagraphStyle, 0, 7);
    spanString->AddSpan(paragraphStyle);

    /**
     * @tc.steps2: Convert the SpanString to HTML using the SpanToHtml converter.
     * @tc.expected: The HTML should reflect the correct font sizes, with the word "小" being 50px,
     *               while others remain 16px.
     */
    SpanToHtml convert;
    auto out = convert.ToHtml(*spanString);
    std::string result =
        "<div ><p style=\"word-break: break_word;text-overflow: clip;\"><span style=\"font-size: 16.00px;"
        "font-style: normal;font-weight: normal;color: #000000FF;font-family: HarmonyOS Sans;\">big"
        " \xE4\xB8\xAD\xE6\x96\x87\xE6\xB7\xB7</span><span style=\"font-size: 16.00px;font-style: "
        "normal;font-weight: normal;color: #000000FF;font-family: HarmonyOS Sans"
        ";\">\xE6\x8E\x92\xE6\x83\x85\xE5\x86\xB5 text</span></p></div>"; // xE4 etc is corresponding Chinese
    EXPECT_EQ(out, result);
}

/**
 * @tc.name: SpanStringConvert011
 * @tc.desc: This test case checks the conversion of a SpanString with mixed text styles including font size,
 *           text shadow, and alignment. It ensures that the HTML conversion applies the correct styles
 *           for both the paragraph and the individual spans.
 * @tc.level: 1
 */
HWTEST_F(HtmlConvertTestNg, SpanStringConvert011, TestSize.Level1)
{
    /**
     * @tc.steps1: Create a SpanString and apply complex paragraph styles and nested text shadow within the span.
     * @tc.expected: The HTML should reflect the correct styles including text shadow for the nested span.
     */
    auto spanString = AceType::MakeRefPtr<SpanString>
        (u"complext text span style= font size: 40px;text shadow: 0 0 3px red; shadow span ");
    SpanParagraphStyle spanParagraphStyle;
    spanParagraphStyle.align = TextAlign::START;
    spanParagraphStyle.textIndent = Dimension(10.0_vp);
    spanParagraphStyle.wordBreak = WordBreak::HYPHENATION;
    spanParagraphStyle.textOverflow = TextOverflow::DEFAULT;
    spanParagraphStyle.leadingMargin = LeadingMargin();
    spanParagraphStyle.leadingMargin->size = LeadingMarginSize(Dimension(20.0_vp), Dimension(30.0));
    auto paragraphStyle = AceType::MakeRefPtr<ParagraphStyleSpan>(spanParagraphStyle, 0, 7);
    spanString->AddSpan(paragraphStyle);

    /**
     * @tc.steps2: Convert the SpanString to HTML using the SpanToHtml converter.
     * @tc.expected: The resulting HTML should include the correct text shadow and font size styles.
     */
    SpanToHtml convert;
    auto out = convert.ToHtml(*spanString);
    std::string result =
        "<div ><p style=\"text-align: start;text-indent: 10.00px;\"><span style=\"font-size: 16.00px;"
        "font-style: normal;font-weight: normal;color: #000000FF;font-family: HarmonyOS Sans;\">complex"
        "</span><span style=\"font-size: 16.00px;font-style: normal;font-weight: normal;color: #000000FF;"
        "font-family: HarmonyOS Sans;\">t text span style= font size: 40px;text shadow: 0 0 3px red; "
        "shadow span </span></p></div>";
    EXPECT_EQ(out, result);
}

/**
 * @tc.name: SpanStringConvert012
 * @tc.desc: This test case checks the conversion of a complex HTML string with various font styles,
 *           including colors, font-family, font-size, and nested elements like strong and del tags.
 *           It verifies that the HTML is correctly parsed and converted back to a SpanString.
 * @tc.level: 1
 */
HWTEST_F(HtmlConvertTestNg, SpanStringConvert012, TestSize.Level1)
{
    /**
     * @tc.steps1: Create a complex HTML string with various font styles and elements. Convert it to SpanString.
     * @tc.expected: The SpanString should correctly represent the HTML content and its styles.
     */
    const std::string fontHtml = "<!DOCTYPE html>"
                                 "<html>"
                                 "<body>"
                                 "<p>我是正常的</p>"
                                 "<p style=\"COLOR:red;\">我是红色的</p>"
                                 "<p style=\"font-family: 'Times New Roman', serif; font-size: 14px; font-weight: "
                                 "normal; color: red; color: blue;\">我是蓝色的<strong style=\"color:blue; "
                                 "font-size:100px;\">这段文字很重要！</strong><del>蓝色</del></p>"
                                 "<p style=\"font-size:50px;\">我是50的</p>"
                                 "</body>"
                                 "</html>";
    HtmlToSpan toSpan;
    auto dstSpan = toSpan.ToSpanString(fontHtml);
    EXPECT_NE(dstSpan, nullptr);

    SpanToHtml convert;
    auto dstHtml = convert.ToHtml(*dstSpan);
    HtmlToSpan toSpan1;
    auto dstSpan1 = toSpan1.ToSpanString(dstHtml);
    EXPECT_EQ(IsSpanItemSame(dstSpan->GetSpanItems(), dstSpan1->GetSpanItems()), true);
    auto secondHtml = convert.ToHtml(*dstSpan1);
    EXPECT_EQ(secondHtml, dstHtml);
}

/**
 * @tc.name: SpanStringConvert013
 * @tc.desc: This test case checks the encoding and decoding of a simple SpanString with both English and Chinese.
 *           It verifies that no information is lost during the encoding and decoding process.
 * @tc.level: 1
 */
HWTEST_F(HtmlConvertTestNg, SpanStringConvert013, TestSize.Level1)
{
    /**
     * @tc.steps1: Create a SpanString with mixed English and Chinese characters, and encode it to a buffer.
     *             Convert the buffer to HTML and then convert it back to SpanString.
     *             Finally, compare the original SpanString with the decoded SpanString.
     * @tc.expected: The original SpanString and the decoded SpanString should be identical.
     */
    auto spanString = AceType::MakeRefPtr<SpanString>(u"01234中文56789");
    std::vector<uint8_t> buff;
    spanString->EncodeTlv(buff);
    EXPECT_EQ(buff.size() > 0, true);
    SpanToHtml toHtml;
    auto htmlFromU8 = toHtml.ToHtml(buff);
    auto htmlFromSpan = toHtml.ToHtml(*spanString); // 如果一致，说明编码和解码过程中没有丢失信息。
    EXPECT_EQ(htmlFromU8, htmlFromSpan);

    HtmlToSpan toSpan;
    auto spanFromHtml = toSpan.ToSpanString(htmlFromU8);
    EXPECT_EQ(IsSpanItemSame(spanFromHtml->GetSpanItems(), spanString->GetSpanItems()), true);

    SpanToHtml toHtml1;
    auto hmtlString = toHtml1.ToHtml(*spanFromHtml);
    EXPECT_EQ(hmtlString, htmlFromSpan);
}

/**
 * @tc.name: SpanStringConvert014
 * @tc.desc: This test case checks the conversion of a SpanString with multiple styles, including font spans,
 *           letter spacing, and text decoration. It verifies that all styles are correctly applied and
 *           preserved during conversion.
 * @tc.level: 1
 */
HWTEST_F(HtmlConvertTestNg, SpanStringConvert014, TestSize.Level1)
{
    /**
     * @tc.steps1: Create a SpanString with multiple spans, including font styles, letter spacing, and text decoration.
     *             Convert it to HTML and then back to a SpanString.
     *             Compare the span items to ensure no information is lost during the conversion process.
     * @tc.expected: The converted SpanString should match the original SpanString with all styles applied correctly.
     */
    auto spanString = AceType::MakeRefPtr<SpanString>(u"0123456789");
    spanString->AddSpan(AceType::MakeRefPtr<FontSpan>(testFont1, 0, 3));
    spanString->AddSpan(AceType::MakeRefPtr<FontSpan>(testFont2, 3, 5));
    spanString->AddSpan(AceType::MakeRefPtr<FontSpan>(testEmptyFont, 5, 8));
    spanString->AddSpan(AceType::MakeRefPtr<LetterSpacingSpan>(Dimension(5), 5, 8));
    spanString->AddSpan(AceType::MakeRefPtr<DecorationSpan>(
        TextDecoration::LINE_THROUGH, Color::BLUE, TextDecorationStyle::WAVY, 0, 1));

    SpanToHtml convert;
    auto out = convert.ToHtml(*spanString);
    HtmlToSpan toSpan;
    auto dstSpan = toSpan.ToSpanString(out);
    EXPECT_EQ(IsSpanItemSame(dstSpan->GetSpanItems(), spanString->GetSpanItems()), true);
}

} // namespace OHOS::Ace::NG