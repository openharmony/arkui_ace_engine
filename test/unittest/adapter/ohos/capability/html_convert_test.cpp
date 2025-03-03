/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
#include <cstdint>
#include <iostream>
#include <ostream>
#include <vector>

#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/render/mock_paragraph.h"

#include "base/geometry/dimension.h"
#include "base/geometry/size.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/components/common/properties/color.h"
#include "core/components/common/properties/text_style.h"
#include "core/components/text/text_theme.h"
#include "html_to_span.h"
#include "span_to_html.h"
#include "core/components_ng/pattern/text/span/mutable_span_string.h"
#include "core/components_ng/pattern/text/span/span_object.h"
#include "core/components_ng/pattern/text/span/span_string.h"
#include "core/components_ng/pattern/text/span_node.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/pattern/text/text_styles.h"
#include "core/components_ng/property/measure_property.h"

#undef private
#undef protected

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
class HtmlConvertTestNg : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp() override;
    void TearDown() override;
    bool IsSpanItemSame(std::list<RefPtr<NG::SpanItem>> src, std::list<RefPtr<NG::SpanItem>> other);
    SpanParagraphStyle GetDefaultParagraphStyle();
    ImageSpanOptions GetImageOption(const std::string& src);
};

void HtmlConvertTestNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
}

void HtmlConvertTestNg::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
}

void HtmlConvertTestNg::SetUp() {}

void HtmlConvertTestNg::TearDown() {}

std::string test_str[] = { "hello", "world", "this", "find", "gank", "pink", "that", "when", "how", "cpp" };
Font testFont1 { OHOS::Ace::FontWeight::BOLD, Dimension(29.0, DimensionUnit::PX), OHOS::Ace::FontStyle::ITALIC,
    std::vector<std::string>(test_str, test_str + 10), OHOS::Ace::Color::BLUE };
Font testFont2 { OHOS::Ace::FontWeight::LIGHTER, Dimension(19.0, DimensionUnit::PX), OHOS::Ace::FontStyle::ITALIC,
    std::vector<std::string>(test_str, test_str + 10), OHOS::Ace::Color::GRAY };
Font testEmptyFont {};
ImageSpanOptions HtmlConvertTestNg::GetImageOption(const std::string& src)
{
    ImageSpanSize size { .width = 50.0_vp, .height = 50.0_vp };
    BorderRadiusProperty borderRadius;
    borderRadius.SetRadius(2.0_vp);
    MarginProperty margins;
    // margins len 10.0
    margins.SetEdges(CalcLength(10.0));
    PaddingProperty paddings;
    // paddings len 5.0
    paddings.SetEdges(CalcLength(5.0));
    ImageSpanAttribute attr { .size = size,
        .paddingProp = paddings,
        .marginProp = margins,
        .borderRadius = borderRadius,
        .objectFit = ImageFit::COVER,
        .verticalAlign = VerticalAlign::BOTTOM };
    ImageSpanOptions option { .image = src, .imageAttribute = attr };
    return option;
}

SpanParagraphStyle HtmlConvertTestNg::GetDefaultParagraphStyle()
{
    SpanParagraphStyle spanParagraphStyle;
    spanParagraphStyle.align = TextAlign::END;
    // default max lines 4
    spanParagraphStyle.maxLines = 4;
    spanParagraphStyle.wordBreak = WordBreak::BREAK_ALL;
    spanParagraphStyle.textOverflow = TextOverflow::ELLIPSIS;
    // defalut textIndent 23
    spanParagraphStyle.textIndent = Dimension(23.0_vp);
    spanParagraphStyle.leadingMargin = LeadingMargin();
    // default width 25.0 height 26.0
    spanParagraphStyle.leadingMargin->size = LeadingMarginSize(Dimension(25.0_vp), Dimension(26.0));
    return spanParagraphStyle;
}

bool HtmlConvertTestNg::IsSpanItemSame(std::list<RefPtr<NG::SpanItem>> src, std::list<RefPtr<NG::SpanItem>> other)
{
    if (src.size() != other.size()) {
        return false;
    }

    while (src.size() != 0) {
        auto it = src.front();
        auto otherIt = other.front();
        if (it->interval.first != otherIt->interval.first || it->interval.second != otherIt->interval.second ||
            it->content != otherIt->content) {
            return false;
        }
        src.pop_front();
        other.pop_front();
    }
    return true;
}

HWTEST_F(HtmlConvertTestNg, HtmlConvert000, TestSize.Level1)
{
    auto imageOption = GetImageOption("src/icon-1.png");
    auto mutableStr = AceType::MakeRefPtr<MutableSpanString>(imageOption);
    auto spanString3 = AceType::MakeRefPtr<SpanString>(u"012345678\n9");
    spanString3->AddSpan(AceType::MakeRefPtr<FontSpan>(testFont1, 0, 3));
    spanString3->AddSpan(AceType::MakeRefPtr<FontSpan>(testFont2, 3, 5));
    spanString3->AddSpan(AceType::MakeRefPtr<FontSpan>(testEmptyFont, 5, 8));

    spanString3->AddSpan(AceType::MakeRefPtr<BaselineOffsetSpan>(Dimension(4), 0, 2));
    spanString3->AddSpan(AceType::MakeRefPtr<LetterSpacingSpan>(Dimension(5), 5, 8));
    spanString3->AddSpan(AceType::MakeRefPtr<DecorationSpan>(
        TextDecoration::LINE_THROUGH, Color::BLUE, TextDecorationStyle::WAVY, 0, 1));

    auto spanParagraphStyle = GetDefaultParagraphStyle();
    auto paraSpan = AceType::MakeRefPtr<ParagraphStyleSpan>(spanParagraphStyle, 2, 5);

    spanString3->AddSpan(paraSpan);
    Shadow textShadow;
    textShadow.SetBlurRadius(0.0);
    textShadow.SetColor(Color::BLUE);
    textShadow.SetOffsetX(5.0);
    textShadow.SetOffsetY(5.0);

    Shadow textShadow1;
    textShadow1.SetBlurRadius(1.0);
    textShadow1.SetColor(Color::BLUE);
    textShadow1.SetOffsetX(10.0);
    textShadow1.SetOffsetY(10.0);

    vector<Shadow> textShadows { textShadow, textShadow1 };
    spanString3->AddSpan(AceType::MakeRefPtr<TextShadowSpan>(textShadows, 3, 6));
    mutableStr->InsertSpanString(1, spanString3);

    auto spanString2 = AceType::MakeRefPtr<SpanString>(u"测试一下中文，\n看看是什么情况");
    spanString2->AddSpan(AceType::MakeRefPtr<FontSpan>(testFont1, 0, 5));
    spanString2->AddSpan(AceType::MakeRefPtr<FontSpan>(testFont2, 6, 10));
    spanString2->AddSpan(AceType::MakeRefPtr<LetterSpacingSpan>(Dimension(10), 12, 14));

    mutableStr->InsertSpanString(5, spanString2);
    SpanToHtml convert;
    auto out = convert.ToHtml(*mutableStr);
    HtmlToSpan toSpan;
    auto dstSpan = toSpan.ToSpanString(out);
    EXPECT_NE(dstSpan, nullptr);
    auto items = dstSpan->GetSpanItems();
    EXPECT_EQ(items.size(), 17);
}

HWTEST_F(HtmlConvertTestNg, HtmlConvert001, TestSize.Level1)
{
    auto spanString = AceType::MakeRefPtr<SpanString>(u"0123456789");
    spanString->AddSpan(AceType::MakeRefPtr<FontSpan>(testFont1, 0, 3));
    spanString->AddSpan(AceType::MakeRefPtr<FontSpan>(testFont2, 3, 5));
    spanString->AddSpan(AceType::MakeRefPtr<FontSpan>(testEmptyFont, 5, 8));

    std::vector<uint8_t> buffer;
    spanString->EncodeTlv(buffer);
    SpanToHtml convert;
    auto u8ToHtml = convert.ToHtml(buffer);
    EXPECT_NE(u8ToHtml.empty(), true);

    auto out = convert.ToHtml(*spanString);
    EXPECT_NE(out.empty(), true);
    EXPECT_EQ(out, u8ToHtml);

    HtmlToSpan toSpan;
    auto dstSpan = toSpan.ToSpanString(out);
    EXPECT_NE(dstSpan, nullptr);
    auto items = dstSpan->GetSpanItems();
    EXPECT_EQ(items.size(), 4);

    EXPECT_EQ(items.size(), spanString->GetSpanItems().size());
}

HWTEST_F(HtmlConvertTestNg, HtmlConvert002, TestSize.Level1)
{
    auto imageOption = GetImageOption("src/icon-1.png");
    auto imageSpan = AceType::MakeRefPtr<MutableSpanString>(u"123456");

    std::vector<uint8_t> buffer;
    imageSpan->EncodeTlv(buffer);

    SpanToHtml convert;
    auto u8ToHtml = convert.ToHtml(buffer);
    EXPECT_NE(u8ToHtml.empty(), true);

    auto out = convert.ToHtml(*imageSpan);
    EXPECT_NE(out.empty(), true);
    EXPECT_EQ(out, u8ToHtml);

    HtmlToSpan toSpan;
    auto dstSpan = toSpan.ToSpanString(out);
    EXPECT_NE(dstSpan, nullptr);

    auto dstHtml = convert.ToHtml(*dstSpan);
    EXPECT_EQ(out, dstHtml);

    // image is invalid，to html discart image the first char is not black space
    EXPECT_EQ(dstSpan->GetString(), "123456");
    auto spans = dstSpan->GetSpans(0, 6);
    EXPECT_EQ(spans.size(), 1);
}

HWTEST_F(HtmlConvertTestNg, HtmlConvert003, TestSize.Level1)
{
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

HWTEST_F(HtmlConvertTestNg, SpanString004, TestSize.Level1)
{
    auto spanString = AceType::MakeRefPtr<SpanString>(u"01234中文56789");
    std::vector<uint8_t> buff;
    spanString->EncodeTlv(buff);
    EXPECT_EQ(buff.size() > 0, true);
    SpanToHtml toHtml;
    auto htmlFromU8 = toHtml.ToHtml(buff);
    auto htmlFromSpan = toHtml.ToHtml(*spanString);
    EXPECT_EQ(htmlFromU8, htmlFromSpan);

    HtmlToSpan toSpan;
    auto spanFromHtml = toSpan.ToSpanString(htmlFromU8);
    EXPECT_EQ(IsSpanItemSame(spanFromHtml->GetSpanItems(), spanString->GetSpanItems()), true);

    SpanToHtml toHtml1;
    auto hmtlString = toHtml1.ToHtml(*spanFromHtml);
    EXPECT_EQ(hmtlString, htmlFromSpan);
}

HWTEST_F(HtmlConvertTestNg, HtmlConvert005, TestSize.Level1)
{
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
HWTEST_F(HtmlConvertTestNg, HtmlConvert006, TestSize.Level1)
{
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

HWTEST_F(HtmlConvertTestNg, HtmlConvert007, TestSize.Level1)
{
    const std::string multiHtml = "<html>"
                                  "<body>"
                                  "<p style=\"font-size:50px\">dddd当地经的123456</p>"
                                  "</body>"
                                  "</html>";
    HtmlToSpan toSpan;
    auto dstSpan = toSpan.ToSpanString(multiHtml);
    std::list<RefPtr<NG::SpanItem>> spans = dstSpan->GetSpanItems();
    EXPECT_EQ(spans.size(), 1);
    auto it = spans.begin();
    EXPECT_EQ((*it)->fontStyle->GetFontSize().value(), Dimension(50, DimensionUnit::VP));
}

HWTEST_F(HtmlConvertTestNg, HtmlConvert008, TestSize.Level1)
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

HWTEST_F(HtmlConvertTestNg, HtmlConvert009, TestSize.Level1)
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

HWTEST_F(HtmlConvertTestNg, HtmlConvert010, TestSize.Level1)
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

HWTEST_F(HtmlConvertTestNg, HtmlConvert011, TestSize.Level1)
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
} // namespace OHOS::Ace::NG