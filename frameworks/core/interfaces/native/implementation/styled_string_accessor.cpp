/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "core/components_ng/base/frame_node.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/implementation/styled_string_peer.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG {
using StyleValueOptions = std::variant<
    Ark_TextStyle_styled_string,
    Ark_DecorationStyle,
    Ark_BaselineOffsetStyle,
    Ark_LetterSpacingStyle,
    Ark_TextShadowStyle,
    Ark_GestureStyle,
    Ark_ImageAttachment,
    Ark_ParagraphStyle,
    Ark_LineHeightStyle,
    Ark_UrlStyle,
    Ark_CustomSpan,
    Ark_UserDataSpan,
    Ark_BackgroundColorStyle
>;


struct MarginOptions {
    std::optional<MarginProperty> margin;
};

struct StyleOptions {
    int32_t start = 0;
    int32_t length = 0;
    std::optional<Ace::SpanType> styledKey;
    std::optional<StyleValueOptions> styledValue;
};

struct DecorationSpanOptions {
    TextDecoration type = TextDecoration::NONE;
    std::optional<Color> color;
    std::optional<TextDecorationStyle> style;
};
}

namespace OHOS::Ace::NG::Converter {

template<>
ImageSpanSize Convert(const Ark_SizeOptions& src)
{
    ImageSpanSize ret;
    ret.width = Converter::OptConvert<CalcDimension>(src.width);
    ret.height = Converter::OptConvert<CalcDimension>(src.height);
    return ret;
}

template<>
BorderRadiusProperty Convert(const Ark_ImageAttachmentLayoutStyle& src)
{
    BorderRadiusProperty dst;
    if (auto value = Converter::OptConvert<BorderRadiusProperty>(src.borderRadius);
        value.has_value() ) {
        dst = value.value();
    }
    return dst;
}

template<>
MarginOptions Convert(const Ark_ImageAttachmentLayoutStyle& src)
{
    return MarginOptions {
        .margin = Converter::OptConvert<MarginProperty>(src.margin)
    };
}

template<>
PaddingProperty Convert(const Ark_ImageAttachmentLayoutStyle& src)
{
    PaddingProperty dst;
    if (auto value = Converter::OptConvert<PaddingProperty>(src.padding);
        value.has_value() ) {
        dst = value.value();
    }
    return dst;
}

template<>
ImageSpanAttribute Convert(const Ark_ImageAttachment& src)
{
    return ImageSpanAttribute {
        .size = Converter::OptConvert<ImageSpanSize>(src.size),
        .verticalAlign = Converter::OptConvert<VerticalAlign>(src.verticalAlign),
        .objectFit = Converter::OptConvert<ImageFit>(src.objectFit),
        .marginProp = Converter::OptConvert<MarginOptions>(src.layoutStyle).value().margin,
        .borderRadius = Converter::OptConvert<BorderRadiusProperty>(src.layoutStyle),
        .paddingProp = Converter::OptConvert<PaddingProperty>(src.layoutStyle)
    };
}

template<>
Ace::ImageSpanOptions Convert(const Ark_ImageAttachment& src)
{
    Ace::ImageSpanOptions options;
    options.imageAttribute = Converter::OptConvert<ImageSpanAttribute>(src);
    LOGE("Converter::Convert Ark_ImageAttachment, the PixelMap support not implemented");
    return options;
}

template<>
void AssignCast(std::optional<Ace::SpanType>& dst, const Ark_StyledStringKey& src)
{
    switch (src) {
        case ARK_STYLED_STRING_KEY_FONT: dst = Ace::SpanType::Font; break;
        case ARK_STYLED_STRING_KEY_DECORATION: dst = Ace::SpanType::Decoration; break;
        case ARK_STYLED_STRING_KEY_BASELINE_OFFSET: dst = Ace::SpanType::BaselineOffset; break;
        case ARK_STYLED_STRING_KEY_LETTER_SPACING: dst = Ace::SpanType::LetterSpacing; break;
        case ARK_STYLED_STRING_KEY_TEXT_SHADOW: dst = Ace::SpanType::TextShadow; break;
        case ARK_STYLED_STRING_KEY_LINE_HEIGHT: dst = Ace::SpanType::LineHeight; break;
        case ARK_STYLED_STRING_KEY_BACKGROUND_COLOR: dst = Ace::SpanType::BackgroundColor; break;
        case ARK_STYLED_STRING_KEY_URL: dst = Ace::SpanType::Url; break;
        case ARK_STYLED_STRING_KEY_GESTURE: dst = Ace::SpanType::Gesture; break;
        case ARK_STYLED_STRING_KEY_PARAGRAPH_STYLE: dst = Ace::SpanType::ParagraphStyle; break;
        case ARK_STYLED_STRING_KEY_IMAGE: dst = Ace::SpanType::Image; break;
        case ARK_STYLED_STRING_KEY_CUSTOM_SPAN: dst = Ace::SpanType::CustomSpan; break;
        case ARK_STYLED_STRING_KEY_USER_DATA: dst = Ace::SpanType::ExtSpan; break;
        default: LOGE("Unexpected enum value in Ark_StyledStringKey: %{public}d", src);
    }
}

template<>
StyleOptions Convert(const Ark_StyleOptions& src)
{
    StyleOptions dst;
    dst.start = OptConvert<int32_t>(src.start).value_or(0);
    dst.length = OptConvert<int32_t>(src.length).value_or(0);
    dst.styledKey = OptConvert<Ace::SpanType>(src.styledKey);
    dst.styledValue = OptConvert<StyleValueOptions>(src.styledValue);
    return dst;
}

template<>
Font Convert(const Ark_TextStyle_styled_string& src)
{
    return Font {
        .fontWeight = OptConvert<FontWeight>(src.fontWeight),
        .fontSize = OptConvert<Dimension>(src.fontSize),
        .fontStyle = OptConvert<Ace::FontStyle>(src.fontStyle),
        .fontFamilies = OptConvert<FontFamilies>(src.fontFamily).value_or(FontFamilies()).families,
        .fontColor = OptConvert<Color>(src.fontColor)
    };
}

template<>
Font Convert(const StyleValueOptions& src)
{
    Font font;
    if (auto textStyle = std::get_if<Ark_TextStyle_styled_string>(&src); textStyle) {
        font = Converter::OptConvert<Font>(*textStyle).value_or(font);
    }
    return font;
}

template<>
DecorationSpanOptions Convert(const Ark_DecorationStyle& src)
{
    return DecorationSpanOptions {
        .type = OptConvert<TextDecoration>(src.type).value_or(TextDecoration::NONE),
        .color = OptConvert<Color>(src.color),
        .style = OptConvert<TextDecorationStyle>(src.style)
    };
}

template<>
DecorationSpanOptions Convert(const StyleValueOptions& src)
{
    DecorationSpanOptions dst;
    if (auto decorationStyle = std::get_if<Ark_DecorationStyle>(&src); decorationStyle) {
        dst = OptConvert<DecorationSpanOptions>(*decorationStyle).value_or(dst);
    }
    return dst;
}

template<>
Dimension Convert(const StyleValueOptions& src)
{
    Dimension dst(0);
    if (auto style = std::get_if<Ark_LetterSpacingStyle>(&src); style) {
        dst = OptConvert<Dimension>(style->letterSpacing).value_or(dst);
    } else if (auto style = std::get_if<Ark_BaselineOffsetStyle>(&src); style) {
        dst = OptConvert<Dimension>(style->baselineOffset).value_or(dst);
    } else if (auto style = std::get_if<Ark_LineHeightStyle>(&src); style) {
        dst = OptConvert<Dimension>(style->lineHeight).value_or(dst);
    }
    return dst;
}

template<>
GestureStyle Convert(const StyleValueOptions& src)
{
    GestureStyle dst;
    if (auto style = std::get_if<Ark_GestureStyle>(&src); style) {
        //dst = OptConvert<GestureStyle>(*style).value_or(dst);
        LOGE("Converter::Convert Ark_GestureStyle, the handle support not implemented");
    }
    return dst;
}

template<>
std::vector<Shadow> Convert(const StyleValueOptions& src)
{
    std::vector<Shadow> dst;
    if (auto style = std::get_if<Ark_TextShadowStyle>(&src); style) {
        dst = OptConvert<std::vector<Shadow>>(style->textShadow).value_or(dst);
    }
    return dst;
}

template<>
NG::LeadingMarginSize Convert(const Ark_Number& src)
{
    auto size = OptConvert<Dimension>(src).value_or(Dimension(0));
    return NG::LeadingMarginSize(size, size);
}

template<>
NG::LeadingMarginSize Convert(const Ark_Tuple_Dimension_Dimension& src)
{
    auto width = Converter::OptConvert<Dimension>(src.value0).value_or(Dimension(0));
    auto height = Converter::OptConvert<Dimension>(src.value1).value_or(Dimension(0));
    return NG::LeadingMarginSize(width, height);
}

template<>
NG::LeadingMargin Convert(const Ark_Number& src)
{
    return NG::LeadingMargin {
        .size = OptConvert<NG::LeadingMarginSize>(src).value_or(NG::LeadingMarginSize()),
        .pixmap = nullptr
    };
}

template<>
NG::LeadingMargin Convert(const Ark_LeadingMarginPlaceholder& src)
{
    NG::LeadingMargin dst;
    dst.size = OptConvert<NG::LeadingMarginSize>(src.size).value_or(NG::LeadingMarginSize());
    dst.pixmap = nullptr;
    LOGE("Converter::Convert Ark_LeadingMarginPlaceholder, the PixelMap support not implemented");
    return dst;
}

template<>
SpanParagraphStyle Convert(const Ark_ParagraphStyle& src)
{
    return SpanParagraphStyle {
        .align = OptConvert<TextAlign>(src.textAlign),
        .maxLines = OptConvert<int32_t>(src.maxLines),
        .wordBreak = OptConvert<WordBreak>(src.wordBreak),
        .textOverflow = OptConvert<TextOverflow>(src.overflow),
        .leadingMargin = OptConvert<NG::LeadingMargin>(src.leadingMargin),
        .textIndent = OptConvert<Dimension>(src.textIndent)
    };
}

template<>
SpanParagraphStyle Convert(const StyleValueOptions& src)
{
    SpanParagraphStyle dst;
    if (auto style = std::get_if<Ark_ParagraphStyle>(&src); style) {
        dst = OptConvert<SpanParagraphStyle>(*style).value_or(dst);
    }
    return dst;
}

template<>
TextBackgroundStyle Convert(const StyleValueOptions& src)
{
    TextBackgroundStyle dst;
    if (auto style = std::get_if<Ark_BackgroundColorStyle>(&src); style) {
        dst = OptConvert<TextBackgroundStyle>(style->textBackgroundStyle).value_or(dst);
    }
    return dst;
}

template<>
std::string Convert(const StyleValueOptions& src)
{
    std::string dst;
    if (auto style = std::get_if<Ark_UrlStyle>(&src); style) {
        dst = OptConvert<std::string>(style->url).value_or(dst);
    }
    return dst;
}

template<typename Spn, typename In>
RefPtr<Spn> CreateSpan(int32_t start, int32_t length, const StyleOptions& src)
{
    In data;
    if (src.styledValue.has_value()) {
        data = OptConvert<In>(src.styledValue.value()).value_or(data);
    }
    return AceType::MakeRefPtr<Spn>(data, start, start + length);
}

RefPtr<DecorationSpan> CreateDecorationSpan(int32_t start, int32_t length, const StyleOptions& src)
{
    DecorationSpanOptions options;
    if (src.styledValue.has_value()) {
        options = OptConvert<DecorationSpanOptions>(src.styledValue.value()).value_or(options);
    }
    return AceType::MakeRefPtr<DecorationSpan>(
        options.type, options.color, options.style, start, start + length);
}

template<>
RefPtr<SpanBase> Convert(const StyleOptions& src)
{
    if (!src.styledKey.has_value()) {
        return nullptr;
    }
    auto type = src.styledKey.value();
    auto start = src.start;
    auto length = src.length;

    if (type == Ace::SpanType::Image || type == Ace::SpanType::CustomSpan) {
        return nullptr;
    }

    switch (type) {
        case Ace::SpanType::Font:
            return CreateSpan<FontSpan, Font>(start, length, src);
        case Ace::SpanType::Decoration:
            return CreateDecorationSpan(start, length, src);
        case Ace::SpanType::LetterSpacing:
            return CreateSpan<LetterSpacingSpan, Dimension>(start, length, src);
        case Ace::SpanType::BaselineOffset:
            return CreateSpan<BaselineOffsetSpan, Dimension>(start, length, src);
        case Ace::SpanType::Gesture:
            return CreateSpan<GestureSpan, GestureStyle>(start, length, src);
        case Ace::SpanType::TextShadow:
            return CreateSpan<TextShadowSpan, std::vector<Shadow>>(start, length, src);
        case Ace::SpanType::LineHeight:
            return CreateSpan<LineHeightSpan, Dimension>(start, length, src);
        case Ace::SpanType::ParagraphStyle:
            return CreateSpan<ParagraphStyleSpan, SpanParagraphStyle>(start, length, src);
        case Ace::SpanType::ExtSpan:
            return AceType::MakeRefPtr<ExtSpan>(start, start + length);
        case Ace::SpanType::BackgroundColor:
            return CreateSpan<BackgroundColorSpan, std::optional<TextBackgroundStyle>>(start, length, src);
        case Ace::SpanType::Url:
            return CreateSpan<UrlSpan, std::string>(start, length, src);
        default:
            break;
    }
    return nullptr;
}
} // namespace OHOS::Ace::NG::Converter

namespace OHOS::Ace::NG::GeneratedModifier {
namespace StyledStringAccessor {
void DestroyPeerImpl(StyledStringPeer* peer)
{
    if (peer) {
        delete peer;
    }
}
std::vector<RefPtr<SpanBase>> ParseSpanBaseVector(const std::vector<StyleOptions>& styles, int32_t maxLength)
{
    std::vector<RefPtr<SpanBase>> spanBaseVector;
    spanBaseVector.reserve(styles.size());
    for (const auto& style : styles) {
        StyleOptions styleTmp = style;
        styleTmp.length  = style.length > maxLength - style.start || style.length <= 0
            ? maxLength - style.start : style.length;
        styleTmp.start = style.start < 0 || style.start >= maxLength ? 0 : style.start;
        auto spanBase = Converter::OptConvert<RefPtr<SpanBase>>(styleTmp);
        if (spanBase) {
            spanBaseVector.push_back(spanBase.value());
        }
    }
    return spanBaseVector;
}
StyledStringPeer* CtorImpl(const Ark_Union_String_ImageAttachment_CustomSpan* value,
                           const Opt_Array_StyleOptions* styles)
{
    auto peer = new StyledStringPeer();
    RefPtr<SpanString> spanString = nullptr;
    if (value) {
        Converter::VisitUnion(*value,
            [&spanString, &styles](const Ark_String& arkText) {
                std::string data = Converter::OptConvert<std::string>(arkText).value_or("");
                spanString = AceType::MakeRefPtr<SpanString>(data);
                if (!data.empty() && styles && styles->tag != ARK_TAG_UNDEFINED) {
                    auto styleOptions = Converter::OptConvert<std::vector<StyleOptions>>(*styles);
                    if (!styleOptions.has_value()) {
                        int32_t maxLength = StringUtils::ToWstring(data).length();
                        auto spanBases = ParseSpanBaseVector(styleOptions.value(), maxLength);
                        if (!spanBases.empty()) {
                            spanString->BindWithSpans(spanBases);
                        }
                    }
                }
            },
            [&spanString](const Ark_ImageAttachment& arkImageAttachment) {
                auto attachment = Converter::OptConvert<Ace::ImageSpanOptions>(arkImageAttachment);
                if (attachment.has_value()) {
                    spanString = AceType::MakeRefPtr<SpanString>(attachment.value());
                }
            },
            [&spanString](const Ark_CustomSpan& arkCustomSpan) {
                LOGE("StyledStringAccessor::CtorImpl unsupported Ark_CustomSpan");
            },
            []() {}
        );
    }
    if (!spanString) {
        spanString = AceType::MakeRefPtr<SpanString>(std::string());
    }
    peer->spanString = spanString;
    return peer;
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
void GetStringImpl(StyledStringPeer* peer)
{
}
void GetStylesImpl(StyledStringPeer* peer,
                   const Ark_Number* start,
                   const Ark_Number* length,
                   const Opt_StyledStringKey* styledKey)
{
}
Ark_Boolean EqualsImpl(StyledStringPeer* peer,
                       const Ark_StyledString* other)
{
    return 0;
}
Ark_NativePointer SubStyledStringImpl(StyledStringPeer* peer,
                                      const Ark_Number* start,
                                      const Opt_Number* length)
{
    return 0;
}
void FromHtmlImpl(const Ark_String* html,
                  const Callback_Opt_StyledString_Opt_Array_String_Void* outputArgumentForReturningPromise)
{
}
void ToHtmlImpl(const Ark_StyledString* styledString)
{
}
void MarshallingImpl(const Ark_StyledString* styledString)
{
}
void UnmarshallingImpl(Ark_Buffer buffer,
                       const Callback_Opt_StyledString_Opt_Array_String_Void* outputArgumentForReturningPromise)
{
}
Ark_Int32 GetLengthImpl(StyledStringPeer* peer)
{
    return 0;
}
} // StyledStringAccessor
const GENERATED_ArkUIStyledStringAccessor* GetStyledStringAccessor()
{
    static const GENERATED_ArkUIStyledStringAccessor StyledStringAccessorImpl {
        StyledStringAccessor::DestroyPeerImpl,
        StyledStringAccessor::CtorImpl,
        StyledStringAccessor::GetFinalizerImpl,
        StyledStringAccessor::GetStringImpl,
        StyledStringAccessor::GetStylesImpl,
        StyledStringAccessor::EqualsImpl,
        StyledStringAccessor::SubStyledStringImpl,
        StyledStringAccessor::FromHtmlImpl,
        StyledStringAccessor::ToHtmlImpl,
        StyledStringAccessor::MarshallingImpl,
        StyledStringAccessor::UnmarshallingImpl,
        StyledStringAccessor::GetLengthImpl,
    };
    return &StyledStringAccessorImpl;
}

}
