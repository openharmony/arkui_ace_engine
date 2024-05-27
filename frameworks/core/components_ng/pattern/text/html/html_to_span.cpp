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

#include "html_to_span.h"

#include <iterator>
#include <ostream>
#include <string>
#include <utility>

#include "base/geometry/dimension.h"
#include "base/image/file_uri_helper.h"
#include "base/image/image_source.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "base/utils/string_utils.h"
#include "base/utils/utils.h"
#include "core/components/common/properties/color.h"
#include "core/components/common/properties/text_style.h"
#include "core/components/common/properties/text_style_parser.h"
#include "core/components/text/text_theme.h"
#include "core/components_ng/image_provider/image_loading_context.h"
#include "core/components_ng/image_provider/image_provider.h"
#include "core/components_ng/pattern/text/span/mutable_span_string.h"
#include "core/components_ng/pattern/text/span/span_object.h"
#include "core/components_ng/pattern/text/span/span_string.h"
#include "core/components_ng/pattern/text/span_node.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/pattern/text/text_styles.h"
#include "core/components_ng/property/calc_length.h"

namespace OHOS::Ace {
constexpr int ONE_PARAM = 1;
constexpr int TWO_PARAM = 2;
constexpr int THREE_PARAM = 3;
constexpr int FOUR_PARAM = 4;

constexpr int TOP_PARAM = 0;
constexpr int RIGHT_PARAM = 1;
constexpr int BOTTOM_PARAM = 2;
constexpr int LEFT_PARAM = 3;
constexpr int FIRST_PARAM = 0;
constexpr int SECOND_PARAM = 1;
constexpr int THIRD_PARAM = 2;
constexpr int FOUTH_PARAM = 3;

void ToLowerCase(std::string &str)
{
    for (auto &c : str) {
        c = tolower(c);
    }
}

std::vector<std::string> ParseFontFamily(const std::string &fontFamily)
{
    std::vector<std::string> fonts;
    std::stringstream ss(fontFamily);
    std::string token;

    while (std::getline(ss, token, ',')) {
        // 去除字符串两端的空白字符
        std::string font = std::string(token.begin(), token.end());
        font.erase(std::remove_if(font.begin(), font.end(), isspace), font.end());

        // 如果字体名非空，则添加到结果中
        if (!font.empty()) {
            fonts.push_back(font);
        }
    }

    return fonts;
}

VerticalAlign StringToTextVerticalAlign(const std::string &align)
{
    if (align == "bottom") {
        return VerticalAlign::BOTTOM;
    }
    if (align == "middle") {
        return VerticalAlign::CENTER;
    }
    if (align == "top") {
        return VerticalAlign::TOP;
    }
    return VerticalAlign::NONE;
}

FontStyle StringToFontStyle(const std::string &fontStyle)
{
    return fontStyle == "italic" ? FontStyle::ITALIC : FontStyle::NORMAL;
}

TextDecorationStyle StringToTextDecorationStyle(const std::string &textDecorationStyle)
{
    if (textDecorationStyle == "dashed") {
        return TextDecorationStyle::DASHED;
    }
    if (textDecorationStyle == "dotted") {
        return TextDecorationStyle::DOTTED;
    }
    if (textDecorationStyle == "double") {
        return TextDecorationStyle::DOUBLE;
    }
    if (textDecorationStyle == "solid") {
        return TextDecorationStyle::SOLID;
    }
    if (textDecorationStyle == "wavy") {
        return TextDecorationStyle::WAVY;
    }

    return TextDecorationStyle::SOLID;
}

TextDecoration StringToTextDecoration(const std::string &textDecoration)
{
    if (textDecoration == "inherit") {
        return TextDecoration::INHERIT;
    }
    if (textDecoration == "line-through") {
        return TextDecoration::LINE_THROUGH;
    }
    if (textDecoration == "none") {
        return TextDecoration::NONE;
    }
    if (textDecoration == "overline") {
        return TextDecoration::OVERLINE;
    }
    if (textDecoration == "underline") {
        return TextDecoration::UNDERLINE;
    }
    return TextDecoration::NONE;
}

ImageFit ConvertStrToFit(const std::string &fit)
{
    if (fit == "fill") {
        return ImageFit::FILL;
    }
    if (fit == "contain") {
        return ImageFit::CONTAIN;
    }
    if (fit == "cover") {
        return ImageFit::COVER;
    }
    if (fit == "scaledown") {
        return ImageFit::SCALE_DOWN;
    }
    if (fit == "none") {
        return ImageFit::NONE;
    }

    return ImageFit::CONTAIN;
}

HtmlToSpan::Styles HtmlToSpan::ParseStyleAttr(const std::string &style)
{
    Styles styles;
    std::regex pattern(R"(\s*([^:]+):([^;]+);?)");
    std::smatch match;
    std::string::const_iterator searchStart(style.begin());

    while (std::regex_search(searchStart, style.end(), match, pattern)) {
        if (match.size() < 3) {
            continue;
        }
        std::string key = std::regex_replace(match[1].str(), std::regex(R"(\s+)"), "");
        std::string value = std::regex_replace(match[2].str(), std::regex(R"(\s+)"), "");
        ToLowerCase(key);
        styles.emplace_back(key, value);
        searchStart = match[0].second;
    }

    return styles;
}

template<class T>
T* HtmlToSpan::Get(StyleValue *styleValue) const
{
    auto v = std::get_if<T>(styleValue);
    if (v == nullptr) {
        return nullptr;
    }
    return static_cast<T*>(v);
}

void HtmlToSpan::InitFont(const std::string &key,
    const std::string &value, const std::string &index, StyleValues& values)
{
    auto [ret, styleValue] = GetStyleValue<Font>(index, values);
    if (!ret) {
        return;
    }

    Font *font = Get<Font>(styleValue);
    if (font == nullptr) {
        return;
    }

    if (key == "color") {
        font->fontColor = Color::FromString(value);
    } else if (key == "font-size") {
        font->fontSize = Dimension::FromString(value);
    } else if (key == "font-weight") {
        font->fontWeight = StringUtils::StringToFontWeight(value);
    } else if (key == "font-style") {
        font->fontStyle = StringToFontStyle(value);
    } else if (key == "font-family") {
        font->fontFamilies = ParseFontFamily(value);
    } else if (key == "font-variant") { // not support
    }
}

bool HtmlToSpan::IsFontAttr(const std::string &key)
{
    if (key == "font-size" || key == "font-weight" || key == "font-style" || key == "font-family" || key == "color") {
        return true;
    }
    return false;
}


void HtmlToSpan::InitParagrap(const std::string &key, const std::string &value,
    const std::string &index, StyleValues& values)
{
    auto [ret, styleValue] = GetStyleValue<SpanParagraphStyle>(index, values);
    if (!ret) {
        return;
    }

    SpanParagraphStyle *style = Get<SpanParagraphStyle>(styleValue);
    if (style == nullptr) {
        return;
    }

    if (IsTextAlign(key)) {
        style->align = StringToTextAlign(value);
    } else if (IsWordBreak(key)) {
        style->wordBreak = StringToWordBreak(value);
    } else if (IsTextOverflow(key)) {
        style->textOverflow = StringToTextOverflow(value);
    } else if (IsTextIndentAttr(key)) {
        style->textIndent = Dimension::FromString(value);
    } else {
    }
}

bool HtmlToSpan::IsParagraphAttr(const std::string &key)
{
    if (key == "text-align" || key == "word-break" || key == "text-overflow" || key == "text-indent") {
        return true;
    }
    return false;
}

void HtmlToSpan::InitDecoration(
    const std::string &key, const std::string &value, const std::string &index, StyleValues& values)
{
    auto [ret, styleValue] = GetStyleValue<DecorationSpanParam>(index, values);
    if (!ret) {
        return;
    }
    DecorationSpanParam *decoration = Get<DecorationSpanParam>(styleValue);
    if (decoration == nullptr) {
        return;
    }

    if (key == "text-decoration-line") {
        decoration->decorationType = StringToTextDecoration(value);
    } else if (key == "text-decoration-style") {
        decoration->decorationSytle = StringToTextDecorationStyle(value);
    } else if (key == "text-decoration-color") {
        decoration->color = Color::FromString(value);
    } else if (key == "text-decoration-thickness") { // not support
    } else if (key == "text-decoration") {
        // 抽出以上三个类型汇总使用
        std::istringstream ss1(value);
        std::string word1;
        std::vector<std::string> words;
        while (ss1 >> word1) {
            words.push_back(word1);
            if (word1 == "none" || word1 == "underline" || word1 == "overline" || word1 == "line-through" ||
                word1 == "blink" || word1 == "inherit") {
                decoration->decorationType = StringToTextDecoration(word1);
            } else if (word1 == "solid" || word1 == "double" || word1 == "dotted" || word1 == "dashed" ||
                       word1 == "wavy" || word1 == "inherit") {
                decoration->decorationSytle = StringToTextDecorationStyle(word1);
            } else {
                // 默认color
                decoration->color = Color::FromString(word1);
            }
        }
    }
}

bool HtmlToSpan::IsDecorationAttr(const std::string &key)
{
    if (key.compare(0, strlen("text-decoration"), "text-decoration") == 0) {
        return true;
    }
    return false;
}

template <class T>
void HtmlToSpan::InitDimension(const std::string &key, const std::string &value,
    const std::string &index, StyleValues& values)
{
    auto [ret, styleValue] = GetStyleValue<T>(index, values);
    if (!ret) {
        return;
    }
    T* obj = Get<T>(styleValue);
    if (obj == nullptr) {
        return;
    }
    obj->dimension = Dimension::FromString(value);
}

bool HtmlToSpan::IsLetterSpacingAttr(const std::string &key)
{
    if (key.compare(0, strlen("letter-spacing"), "letter-spacing") == 0) {
        return true;
    }
    return false;
}

void HtmlToSpan::InitTextShadow(const std::string &key, const std::string &value,
    const std::string &index, StyleValues& values)
{
    auto [ret, styleValue] = GetStyleValue<std::vector<Shadow>>(index, values);
    if (!ret) {
        return;
    }
    std::vector<Shadow> *shadow = Get<std::vector<Shadow>>(styleValue);
    if (shadow == nullptr) {
        return;
    }

    std::istringstream ss(value);
    std::string word;
    std::vector<std::string> words;
    while (ss >> word) {
        words.push_back(word);
    }
    Shadow textShadow;
    size_t size = words.size();
    if (size == 0) {
        return;
    }
    if (size >= ONE_PARAM) {
        textShadow.SetOffsetX(std::stod(words[FIRST_PARAM]));
    }
    if (size >= TWO_PARAM) {
        textShadow.SetOffsetY(std::stod(words[SECOND_PARAM]));
    }
    if (size >= THREE_PARAM) {
        textShadow.SetBlurRadius(std::stod(words[THIRD_PARAM]));
    }
    if (size >= FOUR_PARAM) {
        textShadow.SetColor(Color::FromString(words[FOUTH_PARAM]));
    }
    shadow->push_back(std::move(textShadow));
}

bool HtmlToSpan::IsTextShadowAttr(const std::string &key)
{
    if (key.compare(0, strlen("text-shadow"), "text-shadow") == 0) {
        return true;
    }
    return false;
}

bool HtmlToSpan::IsTextIndentAttr(const std::string &key)
{
    if (key.compare(0, strlen("text-indent"), "text-indent") == 0) {
        return true;
    }
    return false;
}

bool HtmlToSpan::IsLineHeightAttr(const std::string &key)
{
    if (key.compare(0, strlen("line-height"), "line-height") == 0) {
        return true;
    }
    return false;
}

bool HtmlToSpan::IsPaddingAttr(const std::string &key)
{
    if (key == "padding" || key == "padding-top" || key == "padding-right" || key == "padding-bottom" ||
        key == "padding-left") {
        return true;
    }
    return false;
}

bool HtmlToSpan::IsMarginAttr(const std::string &key)
{
    if (key == "margin" || key == "margin-top" || key == "margin-right" || key == "margin-bottom" ||
        key == "margin-left") {
        return true;
    }
    return false;
}

bool HtmlToSpan::IsBorderAttr(const std::string &key)
{
    if (key == "border-radius" || key == "border-top-left-radius" || key == "border-top-right-radius" ||
        key == "border-bottom-right-radius" || key == "border-bottom-left-radius") {
        return true;
    }
    return false;
}

void HtmlToSpan::SetPaddingOption(const std::string &key, const std::string &value, ImageSpanOptions &options)
{
    if (!options.imageAttribute->paddingProp) {
        options.imageAttribute->paddingProp = std::make_optional<NG::PaddingProperty>();
    }
    auto &paddings = options.imageAttribute->paddingProp;
    if (key == "padding") {
        std::istringstream ss(value);
        std::string word;
        std::vector<std::string> words;
        while (ss >> word) {
            words.push_back(word);
        }

        size_t size = words.size();
        if (size == ONE_PARAM) {
            paddings->top = NG::CalcLength(words[TOP_PARAM]);
            paddings->right = NG::CalcLength(words[TOP_PARAM]);
            paddings->bottom = NG::CalcLength(words[TOP_PARAM]);
            paddings->left = NG::CalcLength(words[TOP_PARAM]);
        } else if (size == TWO_PARAM) {
            paddings->top = NG::CalcLength(words[TOP_PARAM]);
            paddings->right = NG::CalcLength(words[RIGHT_PARAM]);
            paddings->bottom = NG::CalcLength(words[TOP_PARAM]);
            paddings->left = NG::CalcLength(words[RIGHT_PARAM]);
        } else if (size == THREE_PARAM) {
            paddings->top = NG::CalcLength(words[TOP_PARAM]);
            paddings->right = NG::CalcLength(words[RIGHT_PARAM]);
            paddings->bottom = NG::CalcLength(words[BOTTOM_PARAM]);
            paddings->left = NG::CalcLength(words[RIGHT_PARAM]);
        } else if (size == FOUR_PARAM) {
            paddings->top = NG::CalcLength(words[TOP_PARAM]);
            paddings->right = NG::CalcLength(words[RIGHT_PARAM]);
            paddings->bottom = NG::CalcLength(words[BOTTOM_PARAM]);
            paddings->left = NG::CalcLength(words[LEFT_PARAM]);
        }
    } else if (key == "padding-top") {
        paddings->top = NG::CalcLength(value);
    } else if (key == "padding-right") {
        paddings->right = NG::CalcLength(value);
    } else if (key == "padding-bottom") {
        paddings->bottom = NG::CalcLength(value);
    } else if (key == "padding-left") {
        paddings->left = NG::CalcLength(value);
    }
}
void HtmlToSpan::SetMarginOption(const std::string &key, const std::string &value, ImageSpanOptions &options)
{
    if (!options.imageAttribute->marginProp) {
        options.imageAttribute->marginProp = std::make_optional<NG::MarginProperty>();
    }
    auto &marginProp = options.imageAttribute->marginProp;
    if (key == "margin") {
        std::istringstream ss(value);
        std::string word;
        std::vector<std::string> words;
        while (ss >> word) {
            words.push_back(word);
        }

        size_t size = words.size();
        if (size == ONE_PARAM) {
            marginProp->top = NG::CalcLength(words[TOP_PARAM]);
            marginProp->right = NG::CalcLength(words[TOP_PARAM]);
            marginProp->bottom = NG::CalcLength(words[TOP_PARAM]);
            marginProp->left = NG::CalcLength(words[TOP_PARAM]);
        } else if (size == TWO_PARAM) {
            marginProp->top = NG::CalcLength(words[TOP_PARAM]);
            marginProp->right = NG::CalcLength(words[RIGHT_PARAM]);
            marginProp->bottom = NG::CalcLength(words[TOP_PARAM]);
            marginProp->left = NG::CalcLength(words[RIGHT_PARAM]);
        } else if (size == THREE_PARAM) {
            marginProp->top = NG::CalcLength(words[TOP_PARAM]);
            marginProp->right = NG::CalcLength(words[RIGHT_PARAM]);
            marginProp->bottom = NG::CalcLength(words[BOTTOM_PARAM]);
            marginProp->left = NG::CalcLength(words[RIGHT_PARAM]);
        } else if (size == FOUR_PARAM) {
            marginProp->top = NG::CalcLength(words[TOP_PARAM]);
            marginProp->right = NG::CalcLength(words[RIGHT_PARAM]);
            marginProp->bottom = NG::CalcLength(words[BOTTOM_PARAM]);
            marginProp->left = NG::CalcLength(words[LEFT_PARAM]);
        }
    } else if (key == "margin-top") {
        marginProp->top = NG::CalcLength(value);
    } else if (key == "margin-right") {
        marginProp->right = NG::CalcLength(value);
    } else if (key == "margin-bottom") {
        marginProp->bottom = NG::CalcLength(value);
    } else if (key == "margin-left") {
        marginProp->left = NG::CalcLength(value);
    }
}
void HtmlToSpan::SetBorderOption(const std::string &key, const std::string &value, ImageSpanOptions &options)
{
    if (!options.imageAttribute->borderRadius) {
        options.imageAttribute->borderRadius = std::make_optional<NG::BorderRadiusProperty>();
    }
    auto &borderRadius = options.imageAttribute->borderRadius;
    if (key == "border-radius") {
        std::istringstream ss(value);
        std::string word;
        std::vector<std::string> words;
        while (ss >> word) {
            words.push_back(word);
        }
        size_t size = words.size();
        if (size == ONE_PARAM) {
            borderRadius->radiusTopLeft = NG::CalcLength::FromString(words[TOP_PARAM]).GetDimension();
            borderRadius->radiusTopRight = NG::CalcLength::FromString(words[TOP_PARAM]).GetDimension();
            borderRadius->radiusBottomRight = NG::CalcLength::FromString(words[TOP_PARAM]).GetDimension();
            borderRadius->radiusBottomLeft = NG::CalcLength::FromString(words[TOP_PARAM]).GetDimension();
        } else if (size == TWO_PARAM) {
            borderRadius->radiusTopLeft = NG::CalcLength::FromString(words[TOP_PARAM]).GetDimension();
            borderRadius->radiusTopRight = NG::CalcLength::FromString(words[RIGHT_PARAM]).GetDimension();
            borderRadius->radiusBottomRight = NG::CalcLength::FromString(words[TOP_PARAM]).GetDimension();
            borderRadius->radiusBottomLeft = NG::CalcLength::FromString(words[RIGHT_PARAM]).GetDimension();
        } else if (size == THREE_PARAM) {
            borderRadius->radiusTopLeft = NG::CalcLength::FromString(words[TOP_PARAM]).GetDimension();
            borderRadius->radiusTopRight = NG::CalcLength::FromString(words[RIGHT_PARAM]).GetDimension();
            borderRadius->radiusBottomRight = NG::CalcLength::FromString(words[BOTTOM_PARAM]).GetDimension();
            borderRadius->radiusBottomLeft = NG::CalcLength::FromString(words[RIGHT_PARAM]).GetDimension();
        } else if (size == FOUR_PARAM) {
            borderRadius->radiusTopLeft = NG::CalcLength::FromString(words[TOP_PARAM]).GetDimension();
            borderRadius->radiusTopRight = NG::CalcLength::FromString(words[RIGHT_PARAM]).GetDimension();
            borderRadius->radiusBottomRight = NG::CalcLength::FromString(words[BOTTOM_PARAM]).GetDimension();
            borderRadius->radiusBottomLeft = NG::CalcLength::FromString(words[LEFT_PARAM]).GetDimension();
        }
    } else if (key == "border-top-left-radius") {
        borderRadius->radiusTopLeft = NG::CalcLength::FromString(value).GetDimension();
    } else if (key == "border-top-right-radius") {
        borderRadius->radiusTopRight = NG::CalcLength::FromString(value).GetDimension();
    } else if (key == "border-bottom-right-radius") {
        borderRadius->radiusBottomRight = NG::CalcLength::FromString(value).GetDimension();
    } else if (key == "border-bottom-left-radius") {
        borderRadius->radiusBottomLeft = NG::CalcLength::FromString(value).GetDimension();
    }
}
void HtmlToSpan::HandleImgSpanOption(const Styles &styleMap, ImageSpanOptions &options)
{
    for (const auto &[key, value] : styleMap) {
        if (IsPaddingAttr(key)) {
            SetPaddingOption(key, value, options);
        } else if (IsMarginAttr(key)) {
            SetMarginOption(key, value, options);
        } else if (IsBorderAttr(key)) {
            SetBorderOption(key, value, options);
        } else if (key == "object-fit") {
            options.imageAttribute->objectFit = ConvertStrToFit(value);
        } else if (key == "vertical-align") {
            options.imageAttribute->verticalAlign = StringToTextVerticalAlign(value);
        }
    }
}
void HtmlToSpan::HandleImagePixelMap(const std::string &src, ImageSpanOptions &option)
{
    if (src.empty()) {
        return;
    }
    auto iter = src.find_first_of(':');
    if (iter == std::string::npos) {
        return;
    }
    std::string head = src.substr(0, iter);
    std::transform(head.begin(), head.end(), head.begin(), [](unsigned char c) { return std::tolower(c); });
    if (head == "http" || head == "https") {
        NG::LoadNotifier loadNotifier(nullptr, nullptr, nullptr); // 回调中加上日志打印
        RefPtr<NG::ImageLoadingContext> ctx =
            AceType::MakeRefPtr<NG::ImageLoadingContext>(ImageSourceInfo(src), std::move(loadNotifier), true);
        CHECK_NULL_VOID(ctx);
        ctx->LoadImageData();

        option.imagePixelMap = ctx->GetSourceInfo().GetPixmap();
    } else if (head == "file") {
        std::string filePath = FileUriHelper::GetRealPath(src);
        auto imageSource = ImageSource::Create(filePath);
        CHECK_NULL_VOID(imageSource);
        option.imagePixelMap = imageSource->CreatePixelMap();
    }
}

void HtmlToSpan::HandleImageSize(const std::string &key, const std::string &value, ImageSpanOptions &options)
{
    if (!options.imageAttribute->size) {
        options.imageAttribute->size = std::make_optional<ImageSpanSize>();
    }
    if (key == "width") {
        options.imageAttribute->size->width = Dimension::FromString(value);
    } else {
        options.imageAttribute->size->height = Dimension::FromString(value);
    }
}

void HtmlToSpan::MakeImageSpanOptions(const std::string &key, const std::string &value, ImageSpanOptions &options)
{
    if (key == "width" || key == "height") {
        HandleImageSize(key, value, options);
    } else if (key == "src") {
        options.image = value;
        HandleImagePixelMap(value, options);
    } else if (key == "style") {
        Styles styleMap = ParseStyleAttr(value);
        HandleImgSpanOption(styleMap, options);
    }
}

TextAlign HtmlToSpan::StringToTextAlign(const std::string &value)
{
    if (value == "left") {
        return TextAlign::LEFT;
    }
    if (value == "right") {
        return TextAlign::RIGHT;
    }
    if (value == "center") {
        return TextAlign::CENTER;
    }
    if (value == "justify") {
        return TextAlign::JUSTIFY;
    }
    return TextAlign::LEFT;
}

bool HtmlToSpan::IsTextAlign(const std::string &key)
{
    if (key == "text-align") {
        return true;
    }
    return false;
}

WordBreak HtmlToSpan::StringToWordBreak(const std::string &value)
{
    if (value == "normal") {
        return WordBreak::NORMAL;
    }
    if (value == "break-all") {
        return WordBreak::BREAK_ALL;
    }
    if (value == "keep-all") {
        return WordBreak::BREAK_WORD;
    }
    return WordBreak::NORMAL;
}

bool HtmlToSpan::IsWordBreak(const std::string &key)
{
    if (key == "word-break") {
        return true;
    }
    return false;
}

TextOverflow HtmlToSpan::StringToTextOverflow(const std::string &value)
{
    if (value == "clip") {
        return TextOverflow::CLIP;
    }
    if (value == "ellipsis") {
        return TextOverflow::ELLIPSIS;
    }
    if (value == "XXXXX") { // 明确使用那个标签
        return TextOverflow::MARQUEE;
    }
    return TextOverflow::NONE;
}

bool HtmlToSpan::IsTextOverflow(const std::string &key)
{
    if (key == "text-overflow") {
        return true;
    }
    return false;
}

void HtmlToSpan::ToDefalutSpan(xmlNodePtr node, size_t len, size_t& pos)
{
    if (len == 0) {
        return;
    }

    SpanInfo info;
    info.type = HtmlType::Default;
    info.start = pos;
    info.end = pos + len;
    spanInfos_.emplace_back(std::move(info));
}

template<class T>
std::pair<bool, HtmlToSpan::StyleValue*> HtmlToSpan::GetStyleValue(const std::string& key,
    std::map<std::string, StyleValue> &values)
{
    auto it = values.find(key);
    if (it == values.end()) {
        StyleValue value = T();
        it = values.emplace(key, value).first;
    }

    if (it == values.end()) {
        return std::make_pair(false, nullptr);
    }

    return std::make_pair(true, &it->second);
}

void HtmlToSpan::ToParagraphSpan(xmlNodePtr node, size_t len, size_t& pos)
{
    SpanInfo info;
    info.type = HtmlType::ParagraphStyle;
    info.start = pos;
    info.end = pos + len;
    xmlAttrPtr curNode = node->properties;
    if (curNode == nullptr) {
        SpanParagraphStyle style;
        info.values.emplace_back(style);
    } else {
        for (; curNode; curNode = curNode->next) {
            auto styles = ToTextSpanStyle(curNode);
            for (auto [key, value] : styles) {
                info.values.emplace_back(value);
            }
        }
    }

    spanInfos_.emplace_back(std::move(info));
}

std::map<std::string, HtmlToSpan::StyleValue> HtmlToSpan::ToTextSpanStyle(xmlAttrPtr curNode)
{
    auto attrContent = xmlGetProp(curNode->parent, curNode->name);
    if (attrContent == nullptr) {
        return { };
    }
    std::string strStyle(reinterpret_cast<const char *>(attrContent));
    Styles styleMap = ParseStyleAttr(strStyle);
    std::map<std::string, StyleValue> styleValues;
    for (auto &[key, value] : styleMap) {
        if (IsFontAttr(key)) {
            InitFont(key, value, "font", styleValues);
        } else if (IsDecorationAttr(key)) {
            InitDecoration(key, value, "decoration", styleValues);
        } else if (IsLetterSpacingAttr(key)) {
            InitDimension<LetterSpacingSpanParam>(key, value, "letterSpacing", styleValues);
        } else if (IsTextShadowAttr(key)) {
            InitTextShadow(key, value, "shadow", styleValues);
        } else if (IsTextIndentAttr(key)) {
            InitDimension<BaseLineSpanParam>(key, value, "textIndent", styleValues);
        } else if (IsLineHeightAttr(key)) {
            InitDimension<LineHeightSpanSparam>(key, value, "line-height", styleValues);
        } else if (IsParagraphAttr(key)) {
            InitParagrap(key, value, "paragrap", styleValues);
        }
    }

    return styleValues;
}

void HtmlToSpan::ToTextSpan(xmlNodePtr node, size_t len, size_t& pos)
{
    SpanInfo info;
    info.type = HtmlType::Text;
    info.start = pos;
    info.end = pos + len;
    xmlAttrPtr curNode = node->properties;
    for (; curNode; curNode = curNode->next) {
        auto styles = ToTextSpanStyle(curNode);
        for (auto [key, value] : styles) {
            info.values.emplace_back(value);
        }
    }
    spanInfos_.emplace_back(std::move(info));
}

void HtmlToSpan::ToImageOptions(const std::map<std::string, std::string>& styles, ImageSpanOptions& option)
{
    option.imageAttribute = std::make_optional<ImageSpanAttribute>();
    for (auto &[key, value] : styles) {
        MakeImageSpanOptions(key, value, option);
    }
}

void HtmlToSpan::ToImage(xmlNodePtr node, size_t len, size_t& pos)
{
    std::map<std::string, std::string> styleMap;
    xmlAttrPtr curNode = node->properties;
    for (; curNode; curNode = curNode->next) {
        auto attrContent = xmlGetProp(curNode->parent, curNode->name);
        if (attrContent != nullptr) {
            styleMap[reinterpret_cast<const char *>(curNode->name)] = reinterpret_cast<const char *>(attrContent);
        }
    }

    ImageSpanOptions option;
    ToImageOptions(styleMap, option);

    SpanInfo info;
    info.type = HtmlType::Image;
    info.start = pos;
    info.end = pos + len;
    info.values.emplace_back(std::move(option));
    spanInfos_.emplace_back(std::move(info));
}

bool HasElementNode(xmlNodePtr node)
{
    xmlNodePtr curNode = nullptr;
    bool result = false;
    for (curNode = node; curNode; curNode = curNode->next) {
        if (curNode->type == XML_ELEMENT_NODE) {
            return true;
        }

        result = HasElementNode(curNode->children);
    }

    return result;
}

void HtmlToSpan::ToSpan(xmlNodePtr curNode, size_t &pos, std::string &allContent, size_t paragraphEndPos)
{
    std::string contentStr;
    size_t contentLen = 0;
    size_t curNodeLen = 0;
    auto content = xmlNodeGetContent(curNode);
    if (content != nullptr) {
        contentLen = StringUtils::ToWstring(reinterpret_cast<const char *>(content)).length();
        contentStr = reinterpret_cast<const char *>(content);
    }
    std::string nameStr = reinterpret_cast<const char *>(curNode->name);
    if (nameStr != "html" && nameStr != "body" && nameStr != "div") {
        if (curNode->children && curNode->children->content) {
            std::string curNodeContent = reinterpret_cast<const char *>(curNode->children->content);
            allContent += curNodeContent;
            curNodeLen = StringUtils::ToWstring(curNodeContent).length();
        }
    }

    size_t curPos = 0;
    if ((pos + curNodeLen + 1) == paragraphEndPos && paragraphEndPos > 0) {
        allContent += "\n";
        contentLen++;
        curNodeLen++;
    }
    if (nameStr == "p") {
        if (!HasElementNode(curNode->children)) {
            allContent += "\n";
            curNodeLen++;
        } else {
            curPos = pos + contentLen + 1;
        }
        ToParagraphSpan(curNode, contentLen + 1, pos);
    } else if (nameStr == "img") {
        contentLen++;
        ToImage(curNode, contentLen, pos);
        curNodeLen++;
    } else if (nameStr == "span" || nameStr == "strong") {
        ToTextSpan(curNode, contentLen, pos);
    } else if (nameStr != "html" && nameStr != "body" && nameStr != "div") {
        ToDefalutSpan(curNode,  contentLen, pos);
    }

    if (nameStr != "html" && nameStr != "body" && nameStr != "div") {
        pos += curNodeLen;
    }

    ParaseHtmlToSpanInfo(curNode->children, pos, allContent, curPos);
}

void HtmlToSpan::ParaseHtmlToSpanInfo(xmlNodePtr node, size_t& pos, std::string &allContent, size_t paragraphPos)
{
    xmlNodePtr curNode = nullptr;
    for (curNode = node; curNode; curNode = curNode->next) {
        if (curNode->type == XML_ELEMENT_NODE) {
            ToSpan(curNode, pos, allContent, paragraphPos);
        }
    }
}

void HtmlToSpan::PrintSpanInfos()
{
    for (auto &info : spanInfos_) {
        std::cout << "span type " << (int)info.type << " start:"<< info.start << " end:" << info.end
            << " styple:" << info.values.size() << std::endl;
    }
}

RefPtr<SpanBase> HtmlToSpan::CreateSpan(size_t index, const SpanInfo& info, StyleValue& value)
{
    if (index == static_cast<uint32_t>(StyleIndex::STYLE_FONT)) {
        return MakeSpan<Font, FontSpan>(info, value);
    }

    if (index == static_cast<uint32_t>(StyleIndex::STYLE_DECORATION)) {
        return MakeDecorationSpan(info, value);
    }

    if (index == static_cast<uint32_t>(StyleIndex::STYLE_BASELINE)) {
        return MakeDimensionSpan<BaseLineSpanParam, BaselineOffsetSpan>(info, value);
    }

    if (index == static_cast<uint32_t>(StyleIndex::STYLE_LETTERSPACE)) {
        return MakeDimensionSpan<LetterSpacingSpanParam, LetterSpacingSpan>(info, value);
    }

    if (index == static_cast<uint32_t>(StyleIndex::STYLE_LINEHEIGHT)) {
        return MakeDimensionSpan<LineHeightSpanSparam, LineHeightSpan>(info, value);
    }

    if (index == static_cast<uint32_t>(StyleIndex::STYLE_SHADOWS)) {
        return MakeSpan<std::vector<Shadow>, TextShadowSpan>(info, value);
    }

    if (index == static_cast<uint32_t>(StyleIndex::STYLE_PARAGRAPH)) {
        return MakeSpan<SpanParagraphStyle, ParagraphStyleSpan>(info, value);
    }

    return nullptr;
}

template<class T, class P>
RefPtr<SpanBase> HtmlToSpan::MakeSpan(const SpanInfo& info, StyleValue& value)
{
    auto style = Get<T>(&value);
    if (style != nullptr) {
        return AceType::MakeRefPtr<P>(*style, info.start, info.end);
    }

    return nullptr;
}

template<class T, class P>
RefPtr<SpanBase> HtmlToSpan::MakeDimensionSpan(const SpanInfo& info, StyleValue& value)
{
    auto style = Get<T>(&value);
    if (style != nullptr) {
        return AceType::MakeRefPtr<P>(style->dimension, info.start, info.end);
    }

    return nullptr;
}

RefPtr<SpanBase> HtmlToSpan::MakeDecorationSpan(const SpanInfo& info, StyleValue& value)
{
    auto style = Get<DecorationSpanParam>(&value);
    if (style != nullptr) {
        return AceType::MakeRefPtr<DecorationSpan>(style->decorationType, style->color,
            style->decorationSytle, info.start, info.end);
    }

    return nullptr;
}

void HtmlToSpan::AddSpans(const SpanInfo& info, RefPtr<MutableSpanString> mutableSpan)
{
    for (auto value : info.values) {
        size_t index = value.index();
        RefPtr<SpanBase> span;
        if (index >= 0 && index < static_cast<size_t>(StyleIndex::STYLE_MAX)) {
            span = CreateSpan(index, info, value);
        }
        if (span != nullptr) {
            mutableSpan->AddSpan(span);
        }
    }
}

void HtmlToSpan::AddImageSpans(const SpanInfo& info, RefPtr<MutableSpanString> mutableSpan)
{
    for (auto value : info.values) {
        auto style = Get<ImageSpanOptions>(&value);
        if (style == nullptr) {
            continue;
        }
        auto span = AceType::MakeRefPtr<MutableSpanString>(*style);
        mutableSpan->InsertSpanString(info.start, span);
    }
}

RefPtr<MutableSpanString> HtmlToSpan::GenerateSpans(const std::string & allContent)
{
    auto mutableSpan = AceType::MakeRefPtr<MutableSpanString>(allContent);
    RefPtr<MutableSpanString> span;
    for (auto &info: spanInfos_) {
        if (info.type == HtmlType::ParagraphStyle) {
            AddSpans(info, mutableSpan);
        } else if (info.type == HtmlType::Image) {
            AddImageSpans(info, mutableSpan);
        } else {
            AddSpans(info, mutableSpan);
        }
    }
    return mutableSpan;
}

RefPtr<MutableSpanString> HtmlToSpan::ToSpanString(const std::string &html)
{
    htmlDocPtr doc = htmlReadMemory(html.c_str(), html.length(), nullptr, "UTF-8", HTML_PARSE_NOIMPLIED);
    if (doc == nullptr) {
        return nullptr;
    }

    auto docSharedPtr = std::shared_ptr<xmlDoc>(doc, [](htmlDocPtr doc) { xmlFreeDoc(doc); });
    if (docSharedPtr == nullptr) {
        return nullptr;
    }

    xmlNode *root = xmlDocGetRootElement(docSharedPtr.get());
    if (root == nullptr) {
        return nullptr;
    }

    size_t pos = 0;
    std::string content;
    ParaseHtmlToSpanInfo(root, pos, content, 0);
    PrintSpanInfos();
    return GenerateSpans(content);
}
} // namespace OHOS::Ace