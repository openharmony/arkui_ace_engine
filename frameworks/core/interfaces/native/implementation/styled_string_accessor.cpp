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
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/implementation/styled_string.h"
#include "core/interfaces/native/implementation/styled_string_peer.h"
#include "core/text/html_utils.h"

namespace OHOS::Ace::NG::Converter {
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
ImageSpanSize Convert(const Ark_SizeOptions& src)
{
    return {
        .width = OptConvert<CalcDimension>(src.width),
        .height = OptConvert<CalcDimension>(src.height)
    };
}

template<>
BorderRadiusProperty Convert(const Ark_ImageAttachmentLayoutStyle& src)
{
    auto result = OptConvert<BorderRadiusProperty>(src.borderRadius);
    if (!result.has_value()) {
        result = BorderRadiusProperty();
    }
    return result.value();
}

template<>
ImageSpanAttribute Convert(const Ark_ImageAttachment& src)
{
    const auto optLayoutStyle = OptConvert<Ark_ImageAttachmentLayoutStyle>(src.layoutStyle);
    return {
        .size = OptConvert<ImageSpanSize>(src.size),
        .verticalAlign = OptConvert<VerticalAlign>(src.verticalAlign),
        .objectFit = OptConvert<ImageFit>(src.objectFit),
        .marginProp = optLayoutStyle ? OptConvert<MarginProperty>(optLayoutStyle->margin) : std::nullopt,
        .borderRadius = OptConvert<BorderRadiusProperty>(src.layoutStyle),
        .paddingProp = optLayoutStyle ? OptConvert<MarginProperty>(optLayoutStyle->padding) : std::nullopt
    };
}

template<>
ImageSpanOptions Convert(const Ark_ImageAttachment& src)
{
    LOGE("Converter::Convert Ark_ImageAttachment, the PixelMap support not implemented");
    return {
        .imageAttribute = OptConvert<ImageSpanAttribute>(src)
    };
}

template<>
Font Convert(const Ark_TextStyle_styled_string& src)
{
    return {
        .fontWeight = OptConvert<FontWeight>(src.fontWeight),
        .fontSize = OptConvert<Dimension>(src.fontSize),
        .fontStyle = OptConvert<Ace::FontStyle>(src.fontStyle),
        .fontColor = OptConvert<Color>(src.fontColor),
        .fontFamiliesNG = OptConvert<FontFamilies>(src.fontFamily).value_or(FontFamilies()).families
    };
}

struct DecorationSpanOptions {
    TextDecoration type;
    std::optional<Color> color;
    std::optional<TextDecorationStyle> style;
};

template<>
DecorationSpanOptions Convert(const Ark_DecorationStyle& src)
{
    return {
        .type = OptConvert<TextDecoration>(src.type).value_or(TextDecoration::NONE),
        .color = OptConvert<Color>(src.color),
        .style = OptConvert<TextDecorationStyle>(src.style)
    };
}

template<>
Dimension Convert(const Ark_LetterSpacingStyle& src)
{
    return Convert<Dimension>(src.letterSpacing);
}

template<>
Dimension Convert(const Ark_BaselineOffsetStyle& src)
{
    return Convert<Dimension>(src.baselineOffset);
}

template<>
Dimension Convert(const Ark_LineHeightStyle& src)
{
    return Convert<Dimension>(src.lineHeight);
}

template<>
GestureStyle Convert(const Ark_GestureStyle& src)
{
    LOGE("Converter::Convert Ark_GestureStyle, the handle support not implemented");
    return GestureStyle();
}

template<>
std::vector<Shadow> Convert(const Ark_TextShadowStyle& src)
{
    return Convert<std::vector<Shadow>>(src.textShadow);
}

template<>
LeadingMarginSize Convert(const Ark_Number& src)
{
    auto size = Convert<Dimension>(src);
    return LeadingMarginSize(size, size);
}

template<>
LeadingMarginSize Convert(const Ark_Tuple_Dimension_Dimension& src)
{
    auto width = Convert<Dimension>(src.value0);
    auto height = Convert<Dimension>(src.value1);
    return LeadingMarginSize(width, height);
}

template<>
LeadingMargin Convert(const Ark_Number& src)
{
    return {
        .size = Convert<LeadingMarginSize>(src),
        .pixmap = nullptr
    };
}

template<>
LeadingMargin Convert(const Ark_LeadingMarginPlaceholder& src)
{
    LOGE("Converter::Convert Ark_LeadingMarginPlaceholder, the PixelMap support not implemented");
    return {
        .size = Convert<LeadingMarginSize>(src.size),
        .pixmap = nullptr
    };
}

template<>
SpanParagraphStyle Convert(const Ark_ParagraphStyle& src)
{
    return {
        .align = OptConvert<TextAlign>(src.textAlign),
        .maxLines = OptConvert<int32_t>(src.maxLines),
        .wordBreak = OptConvert<WordBreak>(src.wordBreak),
        .textOverflow = OptConvert<TextOverflow>(src.overflow),
        .leadingMargin = OptConvert<LeadingMargin>(src.leadingMargin),
        .textIndent = OptConvert<Dimension>(src.textIndent)
    };
}

template<>
TextBackgroundStyle Convert(const Ark_BackgroundColorStyle& src)
{
    return Convert<TextBackgroundStyle>(src.textBackgroundStyle);
}

template<>
std::string Convert(const Ark_UrlStyle& src)
{
    return Convert<std::string>(src.url);
}

// The information for the Ark_StyleOptions converter.
template<typename T>
struct StyleOptionsTypes {};
template<>
struct StyleOptionsTypes<Ark_TextStyle_styled_string> {
    using Style = Font;
    using Span = FontSpan;
    static constexpr Ark_StyledStringKey KEY = ARK_STYLED_STRING_KEY_FONT;
};
template<>
struct StyleOptionsTypes<Ark_BaselineOffsetStyle> {
    using Style = Dimension;
    using Span = BaselineOffsetSpan;
    static constexpr Ark_StyledStringKey KEY = ARK_STYLED_STRING_KEY_BASELINE_OFFSET;
};
template<>
struct StyleOptionsTypes<Ark_LetterSpacingStyle> {
    using Style = Dimension;
    using Span = LetterSpacingSpan;
    static constexpr Ark_StyledStringKey KEY = ARK_STYLED_STRING_KEY_LETTER_SPACING;
};
template<>
struct StyleOptionsTypes<Ark_TextShadowStyle> {
    using Style = std::vector<Shadow>;
    using Span = TextShadowSpan;
    static constexpr Ark_StyledStringKey KEY = ARK_STYLED_STRING_KEY_TEXT_SHADOW;
};
template<>
struct StyleOptionsTypes<Ark_LineHeightStyle> {
    using Style = Dimension;
    using Span = LineHeightSpan;
    static constexpr Ark_StyledStringKey KEY = ARK_STYLED_STRING_KEY_LINE_HEIGHT;
};
template<>
struct StyleOptionsTypes<Ark_BackgroundColorStyle> {
    using Style = std::optional<TextBackgroundStyle>;
    using Span = BackgroundColorSpan;
    static constexpr Ark_StyledStringKey KEY = ARK_STYLED_STRING_KEY_BACKGROUND_COLOR;
};
template<>
struct StyleOptionsTypes<Ark_UrlStyle> {
    using Style = std::string;
    using Span = UrlSpan;
    static constexpr Ark_StyledStringKey KEY = ARK_STYLED_STRING_KEY_URL;
};
template<>
struct StyleOptionsTypes<Ark_GestureStyle> {
    using Style = GestureStyle;
    using Span = GestureSpan;
    static constexpr Ark_StyledStringKey KEY = ARK_STYLED_STRING_KEY_GESTURE;
};
template<>
struct StyleOptionsTypes<Ark_ParagraphStyle> {
    using Style = SpanParagraphStyle;
    using Span = ParagraphStyleSpan;
    static constexpr Ark_StyledStringKey KEY = ARK_STYLED_STRING_KEY_PARAGRAPH_STYLE;
};

struct StyleOptionsData {
    explicit StyleOptionsData(const Ark_StyleOptions& src)
        : start(Converter::OptConvert<int32_t>(src.start).value_or(0)),
        end(Converter::OptConvert<int32_t>(src.length).value_or(0) + start),
        key(src.styledKey) {}

    int32_t start;
    int32_t end;
    Ark_StyledStringKey key;
    RefPtr<SpanBase> result;
};

template<>
RefPtr<SpanBase> Convert(const Ark_StyleOptions& src)
{
    StyleOptionsData data(src);
    Converter::VisitUnion(src.styledValue,
        [&data](const auto& style) {
            using StyleTypes = StyleOptionsTypes<std::remove_cv_t<std::remove_reference_t<decltype(style)>>>;
            CHECK_NULL_VOID(data.key == StyleTypes::KEY);
            auto value = Convert<typename StyleTypes::Style>(style);
            data.result = AceType::MakeRefPtr<typename StyleTypes::Span>(value, data.start, data.end);
        },
        [&data](const Ark_DecorationStyle& style) {
            CHECK_NULL_VOID(data.key == ARK_STYLED_STRING_KEY_DECORATION);
            auto value = Convert<DecorationSpanOptions>(style);
            data.result = AceType::MakeRefPtr<DecorationSpan>(value.type, value.color,
                value.style, data.start, data.end);
        },
        [&data](const Ark_UserDataSpan& style) {
            CHECK_NULL_VOID(data.key == ARK_STYLED_STRING_KEY_USER_DATA);
            data.result = AceType::MakeRefPtr<ExtSpan>(data.start, data.end);
        },
        [](const Ark_ImageAttachment& style) {
            LOGE("Converter::Convert(Ark_StyleOptions) the Ark_ImageAttachment is not implemented.");
        },
        [](const Ark_CustomSpan& style) {
            LOGE("Converter::Convert(Ark_StyleOptions) the Ark_CustomSpan is not implemented.");
        },
        []() {}
    );
    return data.result;
}
} // namespace OHOS::Ace::NG::Converter

namespace OHOS::Ace::NG::GeneratedModifier {
namespace {
void UpdateSpansRange(std::vector<RefPtr<SpanBase>>& styles, int32_t maxLength)
{
    for (auto& style : styles) {
        if (style->GetStartIndex() < 0 || style->GetStartIndex() >= maxLength) {
            style->UpdateStartIndex(0);
        }
        if (style->GetEndIndex() < style->GetStartIndex() || style->GetEndIndex() >= maxLength) {
            style->UpdateEndIndex(maxLength);
        }
    }
}
} // namespace

const GENERATED_ArkUIStyledStringAccessor* GetStyledStringAccessor();

namespace StyledStringAccessor {
void DestroyPeerImpl(StyledStringPeer* peer)
{
    delete peer;
}
Ark_NativePointer CtorImpl(const Ark_Union_String_ImageAttachment_CustomSpan* value,
                           const Opt_Array_StyleOptions* styles)
{
    auto peer = new StyledStringPeer();
    if (value) {
        Converter::VisitUnion(*value,
            [&peer, styles](const Ark_String& arkText) {
                std::string data = Converter::Convert<std::string>(arkText);
                peer->spanString = AceType::MakeRefPtr<SpanString>(data);
                CHECK_NULL_VOID(!data.empty() && styles);
                auto spans = Converter::OptConvert<std::vector<RefPtr<SpanBase>>>(*styles);
                CHECK_NULL_VOID(spans);
                UpdateSpansRange(spans.value(), StringUtils::ToWstring(data).length());
                peer->spanString->BindWithSpans(spans.value());
            },
            [&peer](const Ark_ImageAttachment& arkImageAttachment) {
                auto attachment = Converter::OptConvert<ImageSpanOptions>(arkImageAttachment);
                CHECK_NULL_VOID(attachment);
                peer->spanString = AceType::MakeRefPtr<SpanString>(attachment.value());
            },
            [](const Ark_CustomSpan& arkCustomSpan) {
                LOGE("StyledStringAccessor::CtorImpl unsupported Ark_CustomSpan");
            },
            []() {}
        );
    }
    if (!peer->spanString) {
        peer->spanString = AceType::MakeRefPtr<SpanString>(std::string());
    }
    return peer;
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
void GetStringImpl(StyledStringPeer* peer)
{
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(peer->spanString);
    peer->spanString->GetString();
    // string need to be returned
    LOGE("StyledStringAccessor::GetStringImpl - return value need to be supported");
}
void GetStylesImpl(StyledStringPeer* peer,
                   const Ark_Number* start,
                   const Ark_Number* length,
                   const Opt_StyledStringKey* styledKey)
{
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(peer->spanString);
    CHECK_NULL_VOID(start);
    CHECK_NULL_VOID(length);
    auto spanStart = Converter::Convert<int32_t>(*start);
    auto spanLength = Converter::Convert<int32_t>(*length);
    if (!peer->spanString->CheckRange(spanStart, spanLength)) {
        LOGE("CheckBoundary failed: start:%{public}d length:%{public}d", spanStart, spanLength);
        return;
    }
    std::vector<RefPtr<SpanBase>> spans;
    auto spanType = styledKey ? Converter::OptConvert<Ace::SpanType>(*styledKey) : std::nullopt;
    if (spanType.has_value()) {
        spans = peer->spanString->GetSpans(spanStart, spanLength, spanType.value());
    } else {
        spans = peer->spanString->GetSpans(spanStart, spanLength);
    }
    // spans need to be returned
    LOGE("StyledStringAccessor::GetStylesImpl - return value need to be supported");
}
Ark_Boolean EqualsImpl(StyledStringPeer* peer,
                       const Ark_StyledString* other)
{
    CHECK_NULL_RETURN(peer, false);
    CHECK_NULL_RETURN(peer->spanString, false);
    CHECK_NULL_RETURN(other, false);
    CHECK_NULL_RETURN(other->ptr, false);
    auto otherPeer = reinterpret_cast<StyledStringPeer *>(other->ptr);
    CHECK_NULL_RETURN(otherPeer->spanString, false);
    return peer->spanString->IsEqualToSpanString(otherPeer->spanString);
}
Ark_NativePointer SubStyledStringImpl(StyledStringPeer* peer,
                                      const Ark_Number* start,
                                      const Opt_Number* length)
{
    Ark_NativePointer ret = nullptr;
    CHECK_NULL_RETURN(peer, ret);
    CHECK_NULL_RETURN(peer->spanString, ret);
    CHECK_NULL_RETURN(start, ret);
    auto startSpan = Converter::Convert<int32_t>(*start);
    auto lengthSpan = peer->spanString->GetLength() - startSpan;
    auto lengthOpt = length ? Converter::OptConvert<int32_t>(*length) : std::nullopt;
    if (lengthOpt) {
        lengthSpan = std::min(lengthSpan, lengthOpt.value());
    }
    if (!peer->spanString->CheckRange(startSpan, lengthSpan)) {
        LOGE("CheckBoundary failed: start:%{public}d length:%{public}d", startSpan, lengthSpan);
        return ret;
    }
    auto spanString = peer->spanString->GetSubSpanString(startSpan, lengthSpan);
    CHECK_NULL_RETURN(spanString, ret);
    auto spanPeerCtor = GetStyledStringAccessor()->ctor(nullptr, nullptr);
    auto spanPeer = reinterpret_cast<StyledStringPeer *>(spanPeerCtor);
    spanPeer->spanString = spanString;
    ret = reinterpret_cast<Ark_NativePointer>(spanPeer);
    return ret;
}
void FromHtmlImpl(const Ark_String* html,
                  const Callback_Opt_StyledString_Opt_Array_String_Void* outputArgumentForReturningPromise)
{
    CHECK_NULL_VOID(html);
    auto htmlStr = Converter::Convert<std::string>(*html);
    CHECK_NULL_VOID(!htmlStr.empty());
    // StyledString need to be returned
    LOGE("StyledStringAccessor::FromHtmlImpl - return value need to be supported");
}
void ToHtmlImpl(const Ark_StyledString* styledString)
{
    CHECK_NULL_VOID(styledString);
    auto peer = reinterpret_cast<StyledStringPeer *>(styledString->ptr);
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(peer->spanString);
    auto htmlStr = OHOS::Ace::HtmlUtils::ToHtml(peer->spanString.GetRawPtr());
    LOGE("StyledStringAccessor::ToHtmlImpl - return value need to be supported");
}
void MarshallingImpl(const Ark_StyledString* styledString)
{
    CHECK_NULL_VOID(styledString);
    StyledStringPeer* peer = reinterpret_cast<StyledStringPeer *>(styledString->ptr);
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(peer->spanString);
    auto spanStringRawPtr = peer->spanString.GetRawPtr();
    std::vector<uint8_t> tlvData;
    spanStringRawPtr->EncodeTlv(tlvData);

    size_t bufferSize = tlvData.size();
    auto data = tlvData.data();
    LOGE("StyledStringAccessor::MarshallingImpl - return value need to be supported");
}
void UnmarshallingImpl(const Ark_Buffer* buffer,
                       const Callback_Opt_StyledString_Opt_Array_String_Void* outputArgumentForReturningPromise)
{
    CHECK_NULL_VOID(outputArgumentForReturningPromise);
    std::vector<std::string> errorsStr;
    auto str = Converter::Convert<std::string>(*buffer);
    std::vector<uint8_t> vec(str.begin(), str.end());
    auto spanString = SpanString::DecodeTlv(vec);
    StyledStringPeer *peer = new StyledStringPeer();
    peer->spanString = spanString;
    Opt_StyledString styledString = Converter::ArkValue<Opt_StyledString>(*peer);
    Converter::ArkArrayHolder<Array_String> errorHolder(errorsStr);
    auto error = errorHolder.OptValue<Opt_Array_String>();
    // StyledString need to be returned
    peer->spanString = nullptr;
    delete peer;
    LOGE("StyledStringAccessor::UnmarshallingImpl - return value need to be supported");
}
Ark_Int32 GetLengthImpl(StyledStringPeer* peer)
{
    CHECK_NULL_RETURN(peer, 0);
    CHECK_NULL_RETURN(peer->spanString, 0);
    return Converter::ArkValue<Ark_Int32>(peer->spanString->GetLength());
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
