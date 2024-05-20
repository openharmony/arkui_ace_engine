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

#include "span_to_html.h"
#include <cstdint>
#include <string>
#include "base/utils/macros.h"

namespace OHOS::Ace {
extern "C" ACE_FORCE_EXPORT int OHOS_ACE_ConvertHmtlToSpanString(std::vector<uint8_t> &span, std::string& html)
{
    SpanToHtml convert;
    html = convert.ToHtml(span);
    return 0;
}

using namespace OHOS::Ace::NG;
#define TO_HMTL_STYLE_FROMAT(key, value) (key) + std::string(": ") + (value) + (";")

#define TO_HMTL_ATTRIBUTE_FROMAT(key, value) (key) + std::string("=") + ("\"") + (value) + ("\" ")

std::string SpanToHtml::FontStyleToHtml(const std::optional<Ace::FontStyle>& value)
{
    return TO_HMTL_STYLE_FROMAT("font-style",
        value.value_or(Ace::FontStyle::NORMAL) == Ace::FontStyle::NORMAL ? "normal" : "italic");
}

std::string SpanToHtml::FontSizeToHtml(const std::optional<Dimension>& value)
{
    return TO_HMTL_STYLE_FROMAT("font-size", GetFontSizeInJson(value));
}

std::string SpanToHtml::FontWeightToHtml(const std::optional<FontWeight>& value)
{
    static const LinearEnumMapNode<FontWeight, std::string> table[] = {
        { FontWeight::W100, "100" },
        { FontWeight::W200, "200" },
        { FontWeight::W300, "300" },
        { FontWeight::W400, "400" },
        { FontWeight::W500, "500" },
        { FontWeight::W600, "600" },
        { FontWeight::W700, "700" },
        { FontWeight::W800, "800" },
        { FontWeight::W900, "900" },
        { FontWeight::BOLD, "bold" },
        { FontWeight::NORMAL, "normal" },
        { FontWeight::BOLDER, "bolder" },
        { FontWeight::LIGHTER, "lighter" },
        { FontWeight::MEDIUM, "medium" },
        { FontWeight::REGULAR, "regular" },
    };

    auto index = BinarySearchFindIndex(table, ArraySize(table), value.value_or(FontWeight::NORMAL));
    return TO_HMTL_STYLE_FROMAT("font-weight", index < 0 ? "normal" : table[index].value);
}

std::string SpanToHtml::ColorToHtml(const std::optional<Color>& value)
{
    return TO_HMTL_STYLE_FROMAT("color", value.value_or(Color::BLACK).ColorToString());
}

std::string SpanToHtml::FontFamilyToHtml(const std::optional<std::vector<std::string>>& value)
{
    return TO_HMTL_STYLE_FROMAT("font-family", GetFontFamilyInJson(value));
}

std::string SpanToHtml::TextDecorationToHtml(TextDecoration decoration)
{
    static const LinearEnumMapNode<TextDecoration, std::string> decorationTable[] = {
        { TextDecoration::NONE, "none" },
        { TextDecoration::UNDERLINE, "underline" },
        { TextDecoration::OVERLINE, "overline" },
        { TextDecoration::LINE_THROUGH, "line-through" },
        { TextDecoration::INHERIT, "inherit"},
    };

    auto index = BinarySearchFindIndex(decorationTable, ArraySize(decorationTable), decoration);
    if (index < 0) {
        return "";
    }

    return TO_HMTL_STYLE_FROMAT("text-decoration-line", decorationTable[index].value);
}

std::string SpanToHtml::TextDecorationStyleToHtml(TextDecorationStyle decorationStyle)
{
    static const LinearEnumMapNode<TextDecorationStyle, std::string> table[] = {
        { TextDecorationStyle::SOLID, "solid" },
        { TextDecorationStyle::DOUBLE, "double" },
        { TextDecorationStyle::DOTTED, "dotted" },
        { TextDecorationStyle::DASHED, "dashed" },
        { TextDecorationStyle::WAVY, "wavy" },
    };

    auto index = BinarySearchFindIndex(table, ArraySize(table), decorationStyle);
    if (index < 0) {
        return "";
    }

    return TO_HMTL_STYLE_FROMAT("text-decoration-style", table[index].value);
}

std::string SpanToHtml::ToHtml(const std::string &key, const std::optional<Dimension> &space)
{
    if (!space) {
        return "";
    }
    auto &letterSpace = *space;
    if (!letterSpace.IsValid()) {
        return "";
    }

    return TO_HMTL_STYLE_FROMAT(key, letterSpace.ToString());
}

std::string SpanToHtml::DeclarationToHtml(const NG::FontStyle &fontStyle)
{
    auto type = fontStyle.GetTextDecoration().value_or(TextDecoration::NONE);
    if (type == TextDecoration::NONE) {
        return "";
    }
    std::string html;
    auto color = fontStyle.GetTextDecorationColor();
    if (color) {
        html += TO_HMTL_STYLE_FROMAT("text-decoration-color", color->ColorToString());
    }
    html += TextDecorationToHtml(type);
    auto style = fontStyle.GetTextDecorationStyle();
    if (style) {
        html += TextDecorationStyleToHtml(*style);
    }

    return html;
}

std::string SpanToHtml::ToHtml(const std::optional<std::vector<Shadow>> &shadows)
{
    if (!shadows.has_value()) {
        return "";
    }

    if (shadows.value().empty()) {
        return "";
    }

    std::string style;
    for (const auto& shadow : shadows.value()) {
        if (!shadow.IsValid()) {
            continue;
        }

        style += Dimension(shadow.GetOffset().GetX()).ToString() + " " +
        Dimension(shadow.GetOffset().GetY()).ToString() + " " +
        Dimension(shadow.GetBlurRadius()).ToString() + " " +
        shadow.GetColor().ColorToString() + ",";
    }
    style.pop_back();

    return TO_HMTL_STYLE_FROMAT("text-shadow", style);
}

std::string SpanToHtml::ToHtml(const std::string &key, const std::optional<CalcDimension>& dimesion)
{
    if (!dimesion) {
        return "";
    }

    return TO_HMTL_STYLE_FROMAT(key, dimesion->ToString());
}

std::string SpanToHtml::ToHtmlAttribute(const std::string &key, const std::optional<CalcDimension>& dimesion)
{
    if (!dimesion) {
        return "";
    }

    return TO_HMTL_ATTRIBUTE_FROMAT(key, dimesion->ToString());
}

std::string SpanToHtml::ToHtml(const std::optional<ImageSpanSize>& size)
{
    if (!size) {
        return "";
    }

    std::string style = ToHtmlAttribute("width", size->width);
    style += ToHtmlAttribute("height", size->height);
    return style;
}

std::string SpanToHtml::ToHtml(const std::optional<VerticalAlign>& verticalAlign)
{
    if (!verticalAlign) {
        return "";
    }

    static const LinearEnumMapNode<VerticalAlign, std::string> table[] = {
        { VerticalAlign::TOP, "top" },
        { VerticalAlign::CENTER, "center" },
        { VerticalAlign::BOTTOM, "bottom" },
        { VerticalAlign::BASELINE, "baseline" },
        { VerticalAlign::NONE, "" },
    };
    auto iter = BinarySearchFindIndex(table, ArraySize(table), *verticalAlign);
    if (iter < 0) {
        return "";
    }

    return TO_HMTL_STYLE_FROMAT("vertical-align", table[iter].value);
}

std::string SpanToHtml::ToHtml(const std::optional<ImageFit>& objectFit)
{
    if (!objectFit) {
        return "";
    }

    static const LinearEnumMapNode<ImageFit, std::string> table[] = {
        { ImageFit::FILL, "fill" },
        { ImageFit::CONTAIN, "contain" },
        { ImageFit::COVER, "cover" },
        { ImageFit::FITWIDTH, "none" },
        { ImageFit::FITHEIGHT, "none" },
        { ImageFit::NONE, "none" },
        { ImageFit::SCALE_DOWN, "scale-down" },
    };

    auto index = BinarySearchFindIndex(table, ArraySize(table), *objectFit);
    if (index < 0) {
        return "";
    }

    return TO_HMTL_STYLE_FROMAT("object-fit", table[index].value);
}

std::string SpanToHtml::ToHtml(const std::string &key, const std::optional<OHOS::Ace::NG::MarginProperty>& prop)
{
    if (!prop) {
        return "";
    }

    if (prop->top == prop->right && prop->right == prop->bottom
        && prop->bottom == prop->left) {
        if (!prop->top) {
            return "";
        }
        return TO_HMTL_STYLE_FROMAT(key, prop->top->ToString());
    }

    auto padding = prop->top.has_value() ? prop->top->ToString() : "0";
    padding += " " + (prop->right.has_value() ? prop->right->ToString() : "0");
    padding += " " + (prop->bottom.has_value() ? prop->bottom->ToString() : "0");
    padding += " " + (prop->left.has_value() ? prop->left->ToString() : "0");
    
    return TO_HMTL_STYLE_FROMAT(key, padding);
}

std::string SpanToHtml::ToHtml(const std::optional<OHOS::Ace::NG::BorderRadiusProperty>& borderRadius)
{
    if (!borderRadius) {
        return "";
    }

    std::string radius;
    if (borderRadius->radiusTopLeft) {
        radius += TO_HMTL_STYLE_FROMAT("border-top-left-radius", borderRadius->radiusTopLeft->ToString());
    }
    if (borderRadius->radiusTopRight) {
        radius += TO_HMTL_STYLE_FROMAT("border-top-right-radius", borderRadius->radiusTopRight->ToString());
    }
    if (borderRadius->radiusBottomRight) {
        radius += TO_HMTL_STYLE_FROMAT("border-bottom-right-radius", borderRadius->radiusBottomRight->ToString());
    }
    if (borderRadius->radiusBottomLeft) {
        radius += TO_HMTL_STYLE_FROMAT("border-bottom-left-radius", borderRadius->radiusBottomLeft->ToString());
    }

    return radius;
}

std::string SpanToHtml::ImageToHtml(RefPtr<NG::SpanItem> item)
{
    auto image = AceType::DynamicCast<ImageSpanItem>(item);
    if (image == nullptr) {
        return "";
    }

    auto options = image->options;
    if (!options.image) {
        return "";
    }

    std::string imgHtml = "<img src=\"" + *options.image + "\" ";
    imgHtml += ToHtml(options.imageAttribute->size);
    if (options.imageAttribute) {
        imgHtml += " style=\"";
        imgHtml += ToHtml(options.imageAttribute->verticalAlign);
        imgHtml += ToHtml(options.imageAttribute->objectFit);
        imgHtml += ToHtml("margin", options.imageAttribute->marginProp);
        imgHtml += ToHtml(options.imageAttribute->borderRadius);
        imgHtml += ToHtml("padding", options.imageAttribute->paddingProp);
        imgHtml += "\"";
    }

    imgHtml += ">";
    return imgHtml;
}

std::string SpanToHtml::NormalStyleToHtml(const NG::FontStyle &fontStyle)
{
    std::string style = FontSizeToHtml(fontStyle.GetFontSize());
    style += FontStyleToHtml(fontStyle.GetItalicFontStyle());
    style += FontWeightToHtml(fontStyle.GetFontWeight());
    style += ColorToHtml(fontStyle.GetTextColor());
    style += FontFamilyToHtml(fontStyle.GetFontFamily());
    style += DeclarationToHtml(fontStyle);
    style += ToHtml("letter-spacing", fontStyle.GetLetterSpacing());
    style += ToHtml(fontStyle.GetTextShadow());
    if (style.empty()) {
        return "";
    }
    return "style=\"" + style + "\"";
}

std::string SpanToHtml::ToHtml(const std::optional<OHOS::Ace::TextAlign> &object)
{
    if (!object.has_value()) {
        return "";
    }

    static const LinearEnumMapNode<TextAlign, std::string> table[] = {
        { TextAlign::CENTER, "center" },
        { TextAlign::JUSTIFY, "justify" },
        { TextAlign::START, "start" },
        { TextAlign::END, "end" },
    };
    auto index = BinarySearchFindIndex(table, ArraySize(table), *object);
    if (index < 0) {
        return "";
    }

    return TO_HMTL_STYLE_FROMAT("text-align", table[index].value);
}

std::string SpanToHtml::ToHtml(const std::optional<OHOS::Ace::WordBreak> &object)
{
    if (!object.has_value()) {
        return "";
    }

    // 缺少一个 keep-all
    static const LinearEnumMapNode<WordBreak, std::string> table[] = {
        { WordBreak::NORMAL, "normal" },
        { WordBreak::BREAK_ALL, "break_all" },
        { WordBreak::BREAK_WORD, "break_word" },
    };
    auto index = BinarySearchFindIndex(table, ArraySize(table), *object);
    if (index < 0) {
        return "";
    }

    return TO_HMTL_STYLE_FROMAT("word-break", table[index].value);
}

std::string SpanToHtml::ToHtml(const std::optional<OHOS::Ace::TextOverflow> &object)
{
    if (!object.has_value()) {
        return "";
    }

    static const LinearEnumMapNode<TextOverflow, std::string> table[] = {
        { TextOverflow::CLIP, "clip" },
        { TextOverflow::ELLIPSIS, "ellipsis" },
        { TextOverflow::MARQUEE, "marquee" },
    };
    auto index = BinarySearchFindIndex(table, ArraySize(table), *object);
    if (index < 0) {
        return "";
    }

    return TO_HMTL_STYLE_FROMAT("text-overflow", table[index].value);
}

std::string SpanToHtml::LeadingMarginToHtml(const OHOS::Ace::NG::TextLineStyle &style)
{
    auto object = style.GetLeadingMargin();
    if (!object) {
        return "";
    }

    if (!object.has_value()) {
        return "";
    }

    return "";
}

std::string SpanToHtml::ParagraphStyleToHtml(const OHOS::Ace::NG::TextLineStyle &textLineStyle)
{
    auto details = ToHtml(textLineStyle.GetTextAlign());
    details += ToHtml("text-indent", textLineStyle.GetBaselineOffset());
    details += ToHtml(textLineStyle.GetWordBreak());
    details += ToHtml(textLineStyle.GetTextOverflow());
    if (details.empty()) {
        return "";
    }
    return "style=\"" + details + "\"";
}

std::string SpanToHtml::ToHtml(const SpanString& spanString)
{
    auto items = spanString.GetSpanItems();
    bool newLine = true;
    size_t paragrapStart = 0;
    std::string out = "<div >";
    for (const auto &item : items) {
        auto paragraphStyle = ParagraphStyleToHtml(*item->textLineStyle);
        if (newLine && !paragraphStyle.empty()) {
            out += "<p " + paragraphStyle + ">";
            newLine = false;
        }
        if (item->spanItemType == OHOS::Ace::NG::SpanItemType::NORMAL) {
            if (paragrapStart == 0) {
                paragrapStart = out.length();
            }
            out +="<span " + NormalStyleToHtml(*item->fontStyle) + ">";
            auto content = item->GetSpanContent();
            auto wContent = StringUtils::ToWstring(content);
            if (wContent.back() == L'\n') {
                if (newLine) {
                    out.insert(paragrapStart, "<p>");
                    paragrapStart = 0;
                }
                content.pop_back();
                out +=  content + "</span>";
                out += "</p>";
                newLine = true;
            } else {
                out += content + "</span>";
            }
        } else if (item->spanItemType == OHOS::Ace::NG::SpanItemType::IMAGE) {
            out += ImageToHtml(item);
        }
    }

    if (!newLine) {
        out += "</p>";
    }

    out += "</div>";
    return out;
}

std::string SpanToHtml::ToHtml(std::vector<uint8_t> &values)
{
    auto spanString = SpanString::DecodeTlv(values);
    return ToHtml(*spanString);
}
}