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

#include <sys/stat.h>
#include <unistd.h>

#include "base/image/image_packer.h"
#include "core/text/html_utils.h"

namespace OHOS::Ace {
const constexpr char* CONVERT_PNG_FORMAT = "image/png";
const constexpr char* DEFAULT_SUFFIX = ".png";
const mode_t CHOWN_RW_UG = 0660;
const constexpr size_t COLOR_MIN_LENGHT = 3;
const constexpr char* TEMP_HTML_CONVERT_DATA_ROOT_PATH = "data/storage/el2/base/temp/htmlconvert";
extern "C" ACE_FORCE_EXPORT int OHOS_ACE_ConvertHmtlToSpanString(std::vector<uint8_t>& span, std::string& html)
{
    SpanToHtml convert;
    html = convert.ToHtml(span);
    return 0;
}

using namespace OHOS::Ace::NG;
std::string SpanToHtml::FontStyleToHtml(const std::optional<Ace::FontStyle>& value)
{
    return ToHtmlStyleFormat(
        "font-style", value.value_or(Ace::FontStyle::NORMAL) == Ace::FontStyle::NORMAL ? "normal" : "italic");
}

std::string SpanToHtml::FontSizeToHtml(const std::optional<Dimension>& value)
{
    return ToHtmlStyleFormat("font-size", DimensionToString(value.value_or(TEXT_DEFAULT_FONT_SIZE)));
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
    return ToHtmlStyleFormat("font-weight", index < 0 ? "normal" : table[index].value);
}

std::string SpanToHtml::StrokeWidthToHtml(const std::optional<Dimension>& value)
{
    return ToHtmlStyleFormat("stroke-width", DimensionToString(value.value_or(TEXT_DEFAULT_STROKE_WIDTH)));
}

std::string SpanToHtml::StrokeColorToHtml(const std::optional<Color>& value)
{
    auto color = value.value_or(Color::BLACK).ColorToString();
    ToHtmlColor(color);
    return ToHtmlStyleFormat("stroke-color", color);
}

void SpanToHtml::ToHtmlColor(std::string& color)
{
    if (color.length() < COLOR_MIN_LENGHT) {
        return;
    }
    // argb -> rgda
    char second = color[1];
    char third = color[2];
    // earse 2 character after # and apped at end
    color.erase(1, 2);
    color.push_back(second);
    color.push_back(third);
}

std::string SpanToHtml::ColorToHtml(const std::optional<Color>& value)
{
    auto color = value.value_or(Color::BLACK).ColorToString();
    ToHtmlColor(color);
    return ToHtmlStyleFormat("color", color);
}

std::string SpanToHtml::BackgroundColorToHtml(const std::optional<TextBackgroundStyle>& value)
{
    if (!value.has_value()) {
        return "";
    }

    const auto& backgroundStyle = value.value();
    if (!backgroundStyle.backgroundColor.has_value()) {
        return "";
    }

    auto color = backgroundStyle.backgroundColor.value().ColorToString();
    ToHtmlColor(color);
    return ToHtmlStyleFormat("background-color", color);
}

std::string SpanToHtml::FontFamilyToHtml(const std::optional<std::vector<std::string>>& value)
{
    return ToHtmlStyleFormat("font-family", GetFontFamilyInJson(value));
}

std::string SpanToHtml::FontSuperscriptToHtml(const std::optional<SuperscriptStyle>& value)
{
    static const LinearEnumMapNode<SuperscriptStyle, std::string> table[] = {
        { SuperscriptStyle::SUPERSCRIPT, "superscript" },
        { SuperscriptStyle::SUBSCRIPT, "subscript" },
        { SuperscriptStyle::NORMAL, "normal" },
    };

    auto index = BinarySearchFindIndex(table, ArraySize(table), value.value_or(SuperscriptStyle::NORMAL));
    return ToHtmlStyleFormat("font-superscript", index < 0 ? "normal" : table[index].value);
}

std::string SpanToHtml::TextDecorationToHtml(const std::vector<TextDecoration>& decorations)
{
    static const LinearEnumMapNode<TextDecoration, std::string> decorationTable[] = {
        { TextDecoration::NONE, "none" },
        { TextDecoration::UNDERLINE, "underline" },
        { TextDecoration::OVERLINE, "overline" },
        { TextDecoration::LINE_THROUGH, "line-through" },
        { TextDecoration::INHERIT, "inherit" },
    };

    std::string style;
    for (TextDecoration decoration : decorations) {
        auto index = BinarySearchFindIndex(decorationTable, ArraySize(decorationTable), decoration);
        if (index < 0) {
            continue;
        }
        style += decorationTable[index].value + " ";
    }
    style.pop_back();

    return ToHtmlStyleFormat("text-decoration-line", style);
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

    return ToHtmlStyleFormat("text-decoration-style", table[index].value);
}

std::string SpanToHtml::DimensionToString(const Dimension& dimension)
{
    return StringUtils::DoubleToString(dimension.ConvertToVp()).append("px");
}

std::string SpanToHtml::DimensionToStringWithoutUnit(const Dimension& dimension)
{
    return StringUtils::DoubleToString(dimension.ConvertToVp());
}

std::string SpanToHtml::ToHtml(const std::string& key, const std::optional<Dimension>& dimension)
{
    if (!dimension) {
        return "";
    }
    auto& value = *dimension;
    if (!value.IsValid()) {
        return "";
    }
    return ToHtmlStyleFormat(key, DimensionToString(value));
}

std::string SpanToHtml::DecorationToHtml(const NG::FontStyle& fontStyle)
{
    auto types = fontStyle.GetTextDecoration().value_or(
        std::vector<TextDecoration>({TextDecoration::NONE}));
    if (!V2::IsValidTextDecorations(types)) {
        return "";
    }
    std::string html;
    auto color = fontStyle.GetTextDecorationColor();
    if (color) {
        auto htmlColor = color->ColorToString();
        ToHtmlColor(htmlColor);
        html += ToHtmlStyleFormat("text-decoration-color", htmlColor);
    }
    html += TextDecorationToHtml(types);
    auto style = fontStyle.GetTextDecorationStyle();
    if (style) {
        html += TextDecorationStyleToHtml(*style);
    }

    return html;
}

std::string SpanToHtml::ToHtml(const std::optional<std::vector<Shadow>>& shadows)
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

        auto htmlColor = shadow.GetColor().ColorToString();
        ToHtmlColor(htmlColor);

        style += Dimension(shadow.GetOffset().GetX()).ToString() + " " +
                 Dimension(shadow.GetOffset().GetY()).ToString() + " " + Dimension(shadow.GetBlurRadius()).ToString() +
                 " " + htmlColor + ",";
    }
    style.pop_back();

    return ToHtmlStyleFormat("text-shadow", style);
}

std::string SpanToHtml::ToHtml(const std::string& key, const std::optional<CalcDimension>& dimesion)
{
    if (!dimesion) {
        return "";
    }

    return ToHtmlStyleFormat(key, DimensionToString(*dimesion));
}

std::string SpanToHtml::ToHtml(const std::string& key, bool syncLoad)
{
    return ToHtmlStyleFormat(key, V2::ConvertBoolToString(syncLoad));
}

std::string SpanToHtml::ToHtmlImgSizeAttribute(const std::string& key, const std::optional<CalcDimension>& dimesion)
{
    if (!dimesion) {
        return "";
    }

    return ToHtmlAttributeFormat(key, DimensionToStringWithoutUnit(*dimesion));
}

std::string SpanToHtml::ToHtml(const std::optional<ImageSpanSize>& size)
{
    if (!size) {
        return "";
    }

    std::string style = ToHtmlImgSizeAttribute("width", size->width);
    style += ToHtmlImgSizeAttribute("height", size->height);
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

    return ToHtmlStyleFormat("vertical-align", table[iter].value);
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

    return ToHtmlStyleFormat("object-fit", table[index].value);
}

std::string SpanToHtml::ToHtml(const std::string& key, const std::optional<OHOS::Ace::NG::MarginProperty>& prop)
{
    if (!prop) {
        return "";
    }

    if (prop->top == prop->right && prop->right == prop->bottom && prop->bottom == prop->left) {
        if (!prop->top) {
            return "";
        }
        return ToHtmlStyleFormat(key, DimensionToString(prop->top->GetDimension()));
    }

    auto padding = prop->top.has_value() ? DimensionToString(prop->top->GetDimension()) : "0";
    padding += " " + (prop->right.has_value() ? DimensionToString(prop->right->GetDimension()) : "0");
    padding += " " + (prop->bottom.has_value() ? DimensionToString(prop->bottom->GetDimension()) : "0");
    padding += " " + (prop->left.has_value() ? DimensionToString(prop->left->GetDimension()) : "0");

    return ToHtmlStyleFormat(key, padding);
}

std::string SpanToHtml::ToHtml(const std::optional<OHOS::Ace::NG::BorderRadiusProperty>& borderRadius)
{
    if (!borderRadius) {
        return "";
    }

    std::string radius;
    if (borderRadius->radiusTopLeft) {
        radius += ToHtmlStyleFormat("border-top-left-radius", DimensionToString(*borderRadius->radiusTopLeft));
    }
    if (borderRadius->radiusTopRight) {
        radius += ToHtmlStyleFormat("border-top-right-radius", DimensionToString(*borderRadius->radiusTopRight));
    }
    if (borderRadius->radiusBottomRight) {
        radius += ToHtmlStyleFormat("border-bottom-right-radius", DimensionToString(*borderRadius->radiusBottomRight));
    }
    if (borderRadius->radiusBottomLeft) {
        radius += ToHtmlStyleFormat("border-bottom-left-radius", DimensionToString(*borderRadius->radiusBottomLeft));
    }

    return radius;
}

bool SpanToHtml::CreateDirectory(const std::string& path)
{
    if (access(path.c_str(), F_OK) == 0) {
        return true;
    }

    std::string::size_type index = 0;
    do {
        std::string subPath;
        index = path.find('/', index + 1);
        if (index == std::string::npos) {
            subPath = path;
        } else {
            subPath = path.substr(0, index);
        }

        if (access(subPath.c_str(), F_OK) != 0) {
            if (mkdir(subPath.c_str(), (S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH)) != 0) {
                return false;
            }
        }
    } while (index != std::string::npos);

    if (access(path.c_str(), F_OK) == 0) {
        return true;
    }

    return false;
}

int SpanToHtml::WriteLocalFile(RefPtr<PixelMap> pixelMap, std::string& filePath, std::string& fileUri)
{
    std::string fileName;
    auto pos = filePath.rfind("/");
    if (pos == std::string::npos) {
        fileName = filePath;
    } else {
        fileName = filePath.substr(pos + 1);
    }

    if (fileName.empty()) {
        int64_t now =
            std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch())
                .count();
        fileName = std::to_string(now) + DEFAULT_SUFFIX;
    }

    CreateDirectory(TEMP_HTML_CONVERT_DATA_ROOT_PATH);
    std::string localPath = TEMP_HTML_CONVERT_DATA_ROOT_PATH + std::string("/") + fileName;
    RefPtr<ImagePacker> imagePacker = ImagePacker::Create();
    if (imagePacker == nullptr) {
        return -1;
    }
    PackOption option;
    option.format = CONVERT_PNG_FORMAT;
    imagePacker->StartPacking(localPath, option);
    imagePacker->AddImage(*pixelMap);
    int64_t packedSize = 0;
    if (imagePacker->FinalizePacking(packedSize)) {
        return -1;
    }

    if (chmod(localPath.c_str(), CHOWN_RW_UG) != 0) {
    }

    fileUri = "file:///" + localPath;
    return 0;
}

std::string SpanToHtml::ImageToHtml(RefPtr<NG::SpanItem> item)
{
    auto image = AceType::DynamicCast<ImageSpanItem>(item);
    if (image == nullptr) {
        return "";
    }

    auto options = image->options;
    if (!options.image && !options.imagePixelMap) {
        return "";
    }

    std::string urlName;
    auto pixelMap = options.imagePixelMap.value_or(nullptr);
    if (pixelMap) {
        int ret = WriteLocalFile(pixelMap, *options.image, urlName);
        LOGI("img write ret: %{public}d height: %{public}d, width: %{public}d, size:%{public}d", ret,
            pixelMap->GetHeight(), pixelMap->GetWidth(), pixelMap->GetByteCount());
    } else if (options.image.has_value()) {
        urlName = options.image.value();
    }
    std::string imgHtml = "<img src=\"" + urlName + "\" ";
    imgHtml += ToHtml(options.imageAttribute->size);
    if (options.imageAttribute) {
        imgHtml += " style=\"";
        imgHtml += ToHtml(options.imageAttribute->verticalAlign);
        imgHtml += ToHtml(options.imageAttribute->objectFit);
        imgHtml += ToHtml("margin", options.imageAttribute->marginProp);
        imgHtml += ToHtml(options.imageAttribute->borderRadius);
        imgHtml += ToHtml("padding", options.imageAttribute->paddingProp);
        if (!pixelMap) {
            imgHtml += ToHtml("sync-load", options.imageAttribute->syncLoad);
        }
        imgHtml += "\"";
    }

    imgHtml += ">";
    return imgHtml;
}

std::string SpanToHtml::NormalStyleToHtml(
    const NG::FontStyle& fontStyle, const OHOS::Ace::NG::TextLineStyle& textLineStyle)
{
    std::string style = FontSizeToHtml(fontStyle.GetFontSize());
    style += FontStyleToHtml(fontStyle.GetItalicFontStyle());
    style += FontWeightToHtml(fontStyle.GetFontWeight());
    style += ColorToHtml(fontStyle.GetTextColor());
    style += FontFamilyToHtml(fontStyle.GetFontFamily());
    style += StrokeWidthToHtml(fontStyle.GetStrokeWidth());
    style += StrokeColorToHtml(fontStyle.GetStrokeColor());
    style += FontSuperscriptToHtml(fontStyle.GetSuperscript());
    style += DecorationToHtml(fontStyle);
    style += ToHtml("vertical-align", textLineStyle.GetBaselineOffset());
    style += ToHtml("line-height", textLineStyle.GetLineHeight());
    style += ToHtml("letter-spacing", fontStyle.GetLetterSpacing());
    style += ToHtml(fontStyle.GetTextShadow());
    if (style.empty()) {
        return "";
    }
    return "style=\"" + style + "\"";
}

std::string SpanToHtml::NormalStyleToHtml(const RefPtr<NG::SpanItem>& item)
{
    if (!item || !item->fontStyle || !item->textLineStyle) {
        return "";
    }

    const auto& fontStyle = *item->fontStyle;
    const auto& textLineStyle = *item->textLineStyle;

    std::string style = FontSizeToHtml(fontStyle.GetFontSize());
    style += FontStyleToHtml(fontStyle.GetItalicFontStyle());
    style += FontWeightToHtml(fontStyle.GetFontWeight());
    style += ColorToHtml(fontStyle.GetTextColor());
    style += FontFamilyToHtml(fontStyle.GetFontFamily());
    style += StrokeWidthToHtml(fontStyle.GetStrokeWidth());
    style += StrokeColorToHtml(fontStyle.GetStrokeColor());
    style += FontSuperscriptToHtml(fontStyle.GetSuperscript());
    style += DecorationToHtml(fontStyle);
    style += ToHtml("vertical-align", textLineStyle.GetBaselineOffset());
    style += ToHtml("line-height", textLineStyle.GetLineHeight());
    style += ToHtml("letter-spacing", fontStyle.GetLetterSpacing());
    style += ToHtml(fontStyle.GetTextShadow());

    // Add backgroundStyle parsing
    if (item->backgroundStyle) {
        style += BackgroundColorToHtml(item->backgroundStyle);
    }

    if (style.empty()) {
        return "";
    }
    return "style=\"" + style + "\"";
}

std::string SpanToHtml::ToHtml(const std::optional<OHOS::Ace::TextAlign>& object)
{
    if (!object.has_value()) {
        return "";
    }

    static const LinearEnumMapNode<TextAlign, std::string> table[] = {
        { TextAlign::START, "start" },
        { TextAlign::CENTER, "center" },
        { TextAlign::END, "end" },
        { TextAlign::JUSTIFY, "justify" },
    };
    auto index = BinarySearchFindIndex(table, ArraySize(table), *object);
    if (index < 0) {
        return "";
    }

    return ToHtmlStyleFormat("text-align", table[index].value);
}

std::string SpanToHtml::ToHtml(const std::optional<OHOS::Ace::TextVerticalAlign>& object)
{
    if (!object.has_value()) {
        return "";
    }

    static const LinearEnumMapNode<TextVerticalAlign, std::string> table[] = {
        { TextVerticalAlign::BASELINE, "baseline" },
        { TextVerticalAlign::BOTTOM, "bottom" },
        { TextVerticalAlign::CENTER, "middle" },
        { TextVerticalAlign::TOP, "top" },
    };
    auto index = BinarySearchFindIndex(table, ArraySize(table), *object);
    if (index < 0) {
        return "";
    }

    return ToHtmlStyleFormat("vertical-align", table[index].value);
}

std::string SpanToHtml::ToHtml(const std::optional<OHOS::Ace::WordBreak>& object)
{
    if (!object.has_value()) {
        return "";
    }

    // no keep_all
    static const LinearEnumMapNode<WordBreak, std::string> table[] = {
        { WordBreak::NORMAL, "normal" },
        { WordBreak::BREAK_ALL, "break_all" },
        { WordBreak::BREAK_WORD, "break_word" },
    };
    auto index = BinarySearchFindIndex(table, ArraySize(table), *object);
    if (index < 0) {
        return "";
    }

    return ToHtmlStyleFormat("word-break", table[index].value);
}

std::string SpanToHtml::ToHtml(const std::optional<OHOS::Ace::TextOverflow>& object)
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

    return ToHtmlStyleFormat("text-overflow", table[index].value);
}

std::string SpanToHtml::LeadingMarginToHtml(const OHOS::Ace::NG::TextLineStyle& style)
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

std::string SpanToHtml::ParagraphStyleToHtml(const OHOS::Ace::NG::TextLineStyle& textLineStyle)
{
    auto details = ToHtml(textLineStyle.GetTextAlign());
    details += ToHtml(textLineStyle.GetTextVerticalAlign());
    details += ToHtml("text-indent", textLineStyle.GetTextIndent());
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
    for (const auto& item : items) {
        auto paragraphStyle = ParagraphStyleToHtml(*item->textLineStyle);
        if (newLine && !paragraphStyle.empty()) {
            out += "<p " + paragraphStyle + ">";
            newLine = false;
        }
        std::string str = "";
        if (item->spanItemType == SpanItemType::NORMAL) {
            if (paragrapStart == 0) {
                paragrapStart = str.length();
            }
            if (item->backgroundStyle) {
                str += "<span " + NormalStyleToHtml(item) + ">";
            } else {
                str += "<span " + NormalStyleToHtml(*item->fontStyle, *item->textLineStyle) + ">";
            }
            auto content = UtfUtils::Str16DebugToStr8(item->GetSpanContent());
            auto wContent = StringUtils::ToWstring(content);
            if (wContent.back() == L'\n') {
                if (newLine) {
                    str.insert(paragrapStart, "<p>");
                    paragrapStart = 0;
                }
                content.pop_back();
                str += WrapWithAnchorIfNeeded(item, content) + "</span>";
                str += "</p>";
                newLine = true;
            } else {
                str += WrapWithAnchorIfNeeded(item, content) + "</span>";
            }
        } else if (item->spanItemType == SpanItemType::IMAGE) {
            str += ImageToHtml(item);
        }
        out += str;
    }

    if (!newLine) {
        out += "</p>";
    }

    out += "</div>";
    return out;
}

std::string SpanToHtml::ToHtml(std::vector<uint8_t>& values)
{
    auto spanString = SpanString::DecodeTlv(values);
    return ToHtml(*spanString);
}

void SpanToHtml::HandleSingleSpanItemHtml(const RefPtr<NG::SpanItem>& item, std::string& out,
    size_t& paragraphStart, bool& newLine)
{
    auto paragraphStyle = ParagraphStyleToHtml(*item->textLineStyle);
    if (newLine && !paragraphStyle.empty()) {
        out += "<p " + paragraphStyle + ">";
        newLine = false;
    }
    std::string str = "";
    if (item->spanItemType == SpanItemType::NORMAL) {
        if (paragraphStart == 0) {
            paragraphStart = str.length();
        }
        if (item->backgroundStyle) {
            str += "<span " + NormalStyleToHtml(item) + ">";
        } else {
            str += "<span " + NormalStyleToHtml(*item->fontStyle, *item->textLineStyle) + ">";
        }
        auto content = UtfUtils::Str16DebugToStr8(item->GetSpanContent());
        auto wContent = StringUtils::ToWstring(content);
        if (wContent.back() == L'\n') {
            if (newLine) {
                str.insert(paragraphStart, "<p>");
                paragraphStart = 0;
            }
            content.pop_back();
            str += WrapWithAnchorIfNeeded(item, content) + "</span>";
            str += "</p>";
            newLine = true;
        } else {
            str += WrapWithAnchorIfNeeded(item, content) + "</span>";
        }
    } else if (item->spanItemType == SpanItemType::IMAGE) {
        str += ImageToHtml(item);
    }
    out += str;
}

std::string SpanToHtml::ToHtml(const std::list<RefPtr<SpanItem>>& spanItems)
{
    bool newLine = true;
    size_t paragraphStart = 0;
    std::string out = "<div >";
    for (const auto& item : spanItems) {
        HandleSingleSpanItemHtml(item, out, paragraphStart, newLine);
    }
    if (!newLine) {
        out += "</p>";
    }
    out += "</div>";
    return out;
}

std::string SpanToHtml::ToHtmlForNormalType(const NG::FontStyle& fontStyle,
    const NG::TextLineStyle& textLineStyle, const std::u16string& contentStr)
{
    bool newLine = true;
    size_t paragraphStart = 0;
    std::string out = "<div >";
    auto paragraphStyle = ParagraphStyleToHtml(textLineStyle);
    if (newLine && !paragraphStyle.empty()) {
        out += "<p " + paragraphStyle + ">";
        newLine = false;
    }
    if (paragraphStart == 0) {
        paragraphStart = out.length();
    }
    out += "<span " + NormalStyleToHtml(fontStyle, textLineStyle) + ">";
    auto content = UtfUtils::Str16DebugToStr8(contentStr);
    auto wContent = StringUtils::ToWstring(content);
    if (wContent.back() == L'\n') {
        if (newLine) {
            out.insert(paragraphStart, "<p>");
            paragraphStart = 0;
        }
        content.pop_back();
        out += content + "</span>";
        out += "</p>";
        newLine = true;
    } else {
        out += content + "</span>";
    }
    if (!newLine) {
        out += "</p>";
    }
    out += "</div>";
    return out;
}

std::string HtmlUtils::ToHtml(const SpanString* str)
{
    const std::string html = SpanToHtml::ToHtml(*str);
    return html;
}

std::string HtmlUtils::ToHtml(const std::list<RefPtr<NG::SpanItem>>& spanItems)
{
    const std::string html = SpanToHtml::ToHtml(spanItems);
    return html;
}

std::string HtmlUtils::ToHtmlForNormalType(const NG::FontStyle& fontStyle,
    const NG::TextLineStyle& textLineStyle, const std::u16string& contentStr)
{
    const std::string html = SpanToHtml::ToHtmlForNormalType(fontStyle, textLineStyle, contentStr);
    return html;
}
std::string SpanToHtml::WrapWithAnchorIfNeeded(const RefPtr<NG::SpanItem>& item, const std::string& content)
{
    if (item->urlAddress) {
        std::string href = UtfUtils::Str16DebugToStr8(item->urlAddress.value_or(std::u16string(u"")));
        return "<a href=\"" + href + "\">" + content + "</a>";
    }
    return content;
}
} // namespace OHOS::Ace