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
#include "core/components_ng/pattern/text/html/span_to_html.h"
#include "core/components_ng/pattern/text/html/html_to_span.h"
#include "core/components_ng/pattern/text/span/mutable_span_string.h"
#include "core/components_ng/pattern/text/span/span_object.h"
#include "core/components_ng/pattern/text/span/span_string.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/pattern/text/text_styles.h"
#include "core/components_ng/property/measure_property.h"
#include "core/components_ng/pattern/text/span_node.h"
#include "html_convert.h"

#undef private
#undef protected

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
class HtmlConvertTestNg : public testing::Test {
public:
    static void SetUpTestSuite() {};
    static void TearDownTestSuite() {};
    void SetUp() override;
    void TearDown() override;
};

void HtmlConvertTestNg::SetUp()
{
}

void HtmlConvertTestNg::TearDown()
{
}

std::string test_str[] = { "hello", "world", "this", "find", "gank", "pink", "that", "when", "how", "cpp" };
Font testFont1 { OHOS::Ace::FontWeight::BOLD, Dimension(29.0, DimensionUnit::PX), OHOS::Ace::FontStyle::ITALIC,
    std::vector<std::string>(test_str, test_str + 10), OHOS::Ace::Color::BLUE };
Font testFont2 { OHOS::Ace::FontWeight::LIGHTER, Dimension(19.0, DimensionUnit::PX), OHOS::Ace::FontStyle::ITALIC,
    std::vector<std::string>(test_str, test_str + 10), OHOS::Ace::Color::GRAY };
Font testEmptyFont {};
ImageSpanOptions GetImageOption(const std::string& src)
{
    ImageSpanSize size { .width = 50.0_vp, .height = 50.0_vp };
    BorderRadiusProperty borderRadius;
    borderRadius.SetRadius(2.0_vp);
    MarginProperty margins;
    margins.SetEdges(CalcLength(10.0));
    PaddingProperty paddings;
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

void PrintSpanItem(std::list<RefPtr<NG::SpanItem>> items)
{   
    for (auto &item : items) {
        std::cout << "test span:" << item->interval.first << " " << item->interval.second << " " << item->content << std::endl;
    }
}

bool IsSpanItemSame(std::list<RefPtr<NG::SpanItem>> src, std::list<RefPtr<NG::SpanItem>> other)
{
    if (src.size() != other.size()) {
        return false;
    }
    
    while (src.size() != 0) {
        auto it = src.front();
        auto otherIt = other.front();
        if (it->interval.first != otherIt->interval.first ||
            it->interval.second != otherIt->interval.second ||
            it->content != otherIt->content ) {
            return false;
        }
        src.pop_front();
        other.pop_front();
    }
    return true;
}


HWTEST_F(HtmlConvertTestNg, HtmlConvert000, TestSize.Level1)
{
    auto imageOption = GetImageOption("http://www.runoob.com/wp-content/uploads/2016/04/trolltunga.jpg");
    auto mutableStr = AceType::MakeRefPtr<MutableSpanString>(imageOption);

    auto spanString3 = AceType::MakeRefPtr<SpanString>("012345678\n9");
    spanString3->AddSpan(AceType::MakeRefPtr<FontSpan>(testFont1, 0, 3));
    spanString3->AddSpan(AceType::MakeRefPtr<FontSpan>(testFont2, 3, 5));
    spanString3->AddSpan(AceType::MakeRefPtr<FontSpan>(testEmptyFont, 5, 8));

    spanString3->AddSpan(AceType::MakeRefPtr<BaselineOffsetSpan>(Dimension(4), 0, 2));
    spanString3->AddSpan(AceType::MakeRefPtr<LetterSpacingSpan>(Dimension(5), 5, 8));
    spanString3->AddSpan(
        AceType::MakeRefPtr<DecorationSpan>(TextDecoration::LINE_THROUGH, Color::BLUE, TextDecorationStyle::WAVY, 0, 1));

    SpanParagraphStyle spanParagraphStyle;
    spanParagraphStyle.align = TextAlign::END;
    spanParagraphStyle.maxLines = 4;
    spanParagraphStyle.wordBreak = WordBreak::BREAK_ALL;
    spanParagraphStyle.textOverflow = TextOverflow::ELLIPSIS;
    spanParagraphStyle.textIndent = Dimension(23);
    spanParagraphStyle.leadingMargin = LeadingMargin();
    spanParagraphStyle.leadingMargin->size = LeadingMarginSize(Dimension(25.0), Dimension(26.0));
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

    auto spanString2 = AceType::MakeRefPtr<SpanString>("测试一下中文，\n看看是什么情况");
    spanString2->AddSpan(AceType::MakeRefPtr<FontSpan>(testFont1, 0, 5));
    spanString2->AddSpan(AceType::MakeRefPtr<FontSpan>(testFont2, 6, 10));
    spanString2->AddSpan(AceType::MakeRefPtr<LetterSpacingSpan>(Dimension(10), 12, 14));

    mutableStr->InsertSpanString(5, spanString2);

    auto firstSpans = spanString3->GetSpans(5, 2);
    EXPECT_EQ(firstSpans.size(), 1);
    auto firstFontSpan = AceType::DynamicCast<FontSpan>(firstSpans[0]);
    EXPECT_NE(firstFontSpan, nullptr);
    EXPECT_EQ(firstFontSpan->GetStartIndex(), 5);
    EXPECT_EQ(firstFontSpan->GetEndIndex(), 7);
    EXPECT_EQ(firstFontSpan->GetFont().GetFontColor(), "");

    SpanToHtml convert;
    auto out = convert.ToHtml(*mutableStr);
    std::cout << out << std::endl;

    HtmlToSpan toSpan;
    auto dstSpan = toSpan.ToSpanString(out);
    EXPECT_NE(dstSpan, nullptr);
    auto items = dstSpan->GetSpanItems();
    EXPECT_EQ(items.size(), 4);

    EXPECT_EQ(items.size(), mutableStr->GetSpanItems().size());

    EXPECT_TRUE(mutableStr->IsEqualToSpanString(dstSpan));

    auto dstHtml = convert.ToHtml(*dstSpan);
    std::cout << "spanTohtml:" << dstHtml << std::endl;
    EXPECT_EQ(out, dstHtml);
    EXPECT_EQ(IsSpanItemSame(dstSpan->GetSpanItems(), mutableStr->GetSpanItems()), true);

}

HWTEST_F(HtmlConvertTestNg, HtmlConvert001, TestSize.Level1)
{
    auto spanString = AceType::MakeRefPtr<SpanString>("0123456789");
    spanString->AddSpan(AceType::MakeRefPtr<FontSpan>(testFont1, 0, 3));
    spanString->AddSpan(AceType::MakeRefPtr<FontSpan>(testFont2, 3, 5));
    spanString->AddSpan(AceType::MakeRefPtr<FontSpan>(testEmptyFont, 5, 8));

    std::vector<uint8_t> buffer;
    spanString->EncodeTlv(buffer);
    SpanToHtml convert;
    auto u8ToHtml = convert.ToHtml(buffer);
    std::cout << "uint8_t:" << u8ToHtml << std::endl;
    EXPECT_NE(u8ToHtml.empty(), true);

    auto out = convert.ToHtml(*spanString);
    std::cout << "spanstring:" << out << std::endl;
    EXPECT_NE(out.empty(), true);
    EXPECT_EQ(out, u8ToHtml);

    HtmlToSpan toSpan;
    auto dstSpan = toSpan.ToSpanString(out);
    EXPECT_NE(dstSpan, nullptr);
    auto items = dstSpan->GetSpanItems();
    EXPECT_EQ(items.size(), 4);

    EXPECT_EQ(items.size(), spanString->GetSpanItems().size());

    auto dstHtml = convert.ToHtml(*dstSpan);
    std::cout << "spanTohtml:" << dstHtml << std::endl;
    EXPECT_EQ(out, dstHtml);

    PrintSpanItem(dstSpan->GetSpanItems());
    // auto firstSpans = dstSpan->GetSpans(5, 2);
    // EXPECT_EQ(firstSpans.size(), 1);
    // auto firstFontSpan = AceType::DynamicCast<FontSpan>(firstSpans[0]);
    // EXPECT_NE(firstFontSpan, nullptr);
    // EXPECT_EQ(firstFontSpan->GetStartIndex(), 5);
    // EXPECT_EQ(firstFontSpan->GetEndIndex(), 7);
    // EXPECT_EQ(firstFontSpan->GetFont().GetFontColor(), "");

    // auto secondString = dstSpan->GetSpans(0, 3);
    // EXPECT_EQ(secondString.size(), 1);
    // auto secondFontSpan = AceType::DynamicCast<FontSpan>(secondString[0]);
    // EXPECT_NE(secondFontSpan, nullptr);
    // EXPECT_EQ(secondFontSpan->GetStartIndex(), 0);
    // EXPECT_EQ(secondFontSpan->GetEndIndex(), 3);
    // EXPECT_EQ(secondFontSpan->GetFont().GetFontColor(), OHOS::Ace::Color::BLUE.ColorToString());

    // auto thirdString3 = dstSpan->GetSpans(3, 1);
    // EXPECT_EQ(thirdString3.size(), 1);
    // auto thirdFontSpan = AceType::DynamicCast<FontSpan>(thirdString3[0]);
    // EXPECT_NE(thirdFontSpan, nullptr);
    // EXPECT_EQ(thirdFontSpan->GetStartIndex(), 3);
    // EXPECT_EQ(thirdFontSpan->GetEndIndex(), 4);
    // EXPECT_EQ(thirdFontSpan->GetFont().GetFontColor(), OHOS::Ace::Color::GRAY.ColorToString());
}

HWTEST_F(HtmlConvertTestNg, HtmlConvert002, TestSize.Level1)
{
    auto imageOption = GetImageOption("src/icon-1.png");
    auto imageSpan = AceType::MakeRefPtr<MutableSpanString>(imageOption);
    auto mutableStr2 = AceType::MakeRefPtr<MutableSpanString>("123456");
    imageSpan->AppendSpanString(mutableStr2);
    
    std::cout << "fisrt size: :" << imageSpan->GetSpansMap().size() << std::endl;
    std::vector<uint8_t> buffer;
    imageSpan->EncodeTlv(buffer);

    SpanToHtml convert;
    auto u8ToHtml = convert.ToHtml(buffer);
    std::cout << "uint8_t:" << u8ToHtml << std::endl;
    EXPECT_NE(u8ToHtml.empty(), true);

    auto out = convert.ToHtml(*imageSpan);
    std::cout << "spanstring:" << out << std::endl;
    EXPECT_NE(out.empty(), true);
    EXPECT_EQ(out, u8ToHtml);

    std::cout << "src span size:" << imageSpan->GetSpanItems().size() << std::endl;

    HtmlToSpan toSpan;
    auto dstSpan = toSpan.ToSpanString(out);
    EXPECT_NE(dstSpan, nullptr);
    EXPECT_EQ(IsSpanItemSame(dstSpan->GetSpanItems(), imageSpan->GetSpanItems()), true);
    // EXPECT_TRUE(dstSpan->IsEqualToSpanString(imageSpan));

    auto dstHtml = convert.ToHtml(*dstSpan);
    std::cout << "second:" << dstHtml << std::endl;
    EXPECT_EQ(out, dstHtml);

    EXPECT_EQ(dstSpan->GetString(), " 123456");
    auto spans = dstSpan->GetSpans(0, 7);
    EXPECT_EQ(spans.size(), 2);
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
                                "<p style=\"font-size:50px;\">我是很大的</p>"
                                "</body>"
                                "</html>";
    HtmlToSpan toSpan;
    auto dstSpan = toSpan.ToSpanString(fontHtml);
    EXPECT_NE(dstSpan, nullptr);

    PrintSpanItem(dstSpan->GetSpanItems());

    std::cout << "dst span size:" << dstSpan->GetSpanItems().size() << std::endl;

    SpanToHtml convert;
    auto dstHtml = convert.ToHtml(*dstSpan);
    std::cout << "second:" << dstHtml << std::endl;
    HtmlToSpan toSpan1;
    auto dstSpan1 = toSpan1.ToSpanString(dstHtml);
    EXPECT_EQ(IsSpanItemSame(dstSpan->GetSpanItems(), dstSpan1->GetSpanItems()), true);
    // EXPECT_TRUE(dstSpan->IsEqualToSpanString(dstSpan1));
    auto secondHtml = convert.ToHtml(*dstSpan1);
    std::cout << "second:" << secondHtml << std::endl;
    EXPECT_EQ(secondHtml, dstHtml);
}

HWTEST_F(HtmlConvertTestNg, HtmlConvert004, TestSize.Level1)
{
    const std::string multiHtml = "<html>"
                                  "<body>"
                                  "<p>我是正常的</p>"
                                  "<p style=\"COLOR:red;\">我是红色的</p>"
                                  "<p style=\"color:blue;font-size:50px;color:red;\">我是蓝色的<strong style=\"color:blue; font-size:100px;\">这段文字很重要！</strong><del>蓝色</del></p>"
                                  "<p style=\"font-size:50px;\">我是50号字体</p>"
                                  "</body>"
                                  "</html>";
    HtmlToSpan toSpan;
    auto dstSpan = toSpan.ToSpanString(multiHtml);
    EXPECT_NE(dstSpan, nullptr);

    PrintSpanItem(dstSpan->GetSpanItems());

    std::cout << "dst span size:" << dstSpan->GetSpanItems().size() << std::endl;

    SpanToHtml convert;
    auto dstHtml = convert.ToHtml(*dstSpan);
    std::cout << "second:" << dstHtml << std::endl;
    HtmlToSpan toSpan1;
    auto dstSpan1 = toSpan1.ToSpanString(dstHtml);
    EXPECT_EQ(IsSpanItemSame(dstSpan->GetSpanItems(), dstSpan1->GetSpanItems()), true);
    auto secondHtml = convert.ToHtml(*dstSpan1);
    std::cout << "second:" << secondHtml << std::endl;
    EXPECT_EQ(secondHtml, dstHtml);
}

HWTEST_F(HtmlConvertTestNg, HtmlConvert005, TestSize.Level1)
{
    const std::string multiHtml = "<html>"
                                  "<body>"
                                  "<p>我是正常的</p>"
                                  "<p style=\"COLOR:red;\">我是红色的</p>"
                                  "<p style=\"color:blue;font-size:50px;color:red;\">我是蓝色的<strong style=\"color:blue; font-size:100px;\">这段文字很重要！</strong><del>蓝色</del></p>"
                                  "<p style=\"font-size:50px;\">我是50号字体</p>"
                                  "</body>"
                                  "</html>";
    HtmlToSpan toSpan;
    auto dstSpan = toSpan.ToSpanString(multiHtml);
    EXPECT_NE(dstSpan, nullptr);

    std::vector<uint8_t> spanString;
    dstSpan->DecodeTlv(spanString);
    HtmlConvert convert;
    auto dstHtml = convert.SpanStringToHtml(spanString);
    std::cout << "second:" << dstHtml << std::endl;
    HtmlToSpan toSpan1;
    auto dstSpan1 = toSpan1.ToSpanString(dstHtml);
    EXPECT_EQ(IsSpanItemSame(dstSpan->GetSpanItems(), dstSpan1->GetSpanItems()), true);
    SpanToHtml toHtml;
    auto secondHtml = toHtml.ToHtml(*dstSpan1);
    std::cout << "second:" << secondHtml << std::endl;
    EXPECT_EQ(secondHtml, dstHtml);
}

} // namespace OHOS::Ace::NG