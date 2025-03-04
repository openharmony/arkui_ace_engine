/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
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

#include "core/common/ace_engine.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/text/span/mutable_span_string.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/implementation/styled_string.h"
#include "core/interfaces/native/implementation/styled_string_peer.h"
#include "core/interfaces/native/implementation/mutable_styled_string_peer.h"
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
#ifdef WRONG_TYPE
    const auto optLayoutStyle = OptConvert<Ark_ImageAttachmentLayoutStyle>(src.layoutStyle);
    return {
        .size = OptConvert<ImageSpanSize>(src.size),
        .verticalAlign = OptConvert<VerticalAlign>(src.verticalAlign),
        .objectFit = OptConvert<ImageFit>(src.objectFit),
        .marginProp = optLayoutStyle ? OptConvert<MarginProperty>(optLayoutStyle->margin) : std::nullopt,
        .borderRadius = OptConvert<BorderRadiusProperty>(src.layoutStyle),
        .paddingProp = optLayoutStyle ? OptConvert<MarginProperty>(optLayoutStyle->padding) : std::nullopt
    };
#else
    return {};
#endif
}

template<>
ImageSpanOptions Convert(const Ark_ImageAttachment& src)
{
#ifdef WRONG_TYPE
    return {
        .imagePixelMap = OptConvert<RefPtr<PixelMap>>(src.value),
        .imageAttribute = OptConvert<ImageSpanAttribute>(src)
    };
#else
    return {};
#endif
}

template<>
Font Convert(const Ark_TextStyle_styled_string& src)
{
#ifdef WRONG_TYPE
    return {
        .fontWeight = OptConvert<FontWeight>(src.fontWeight),
        .fontSize = OptConvert<Dimension>(src.fontSize),
        .fontStyle = OptConvert<Ace::FontStyle>(src.fontStyle),
        .fontColor = OptConvert<Color>(src.fontColor),
        .fontFamiliesNG = OptConvert<FontFamilies>(src.fontFamily).value_or(FontFamilies()).families
    };
#else
    return {};
#endif
}

struct DecorationSpanOptions {
    TextDecoration type;
    std::optional<Color> color;
    std::optional<TextDecorationStyle> style;
};

template<>
DecorationSpanOptions Convert(const Ark_DecorationStyle& src)
{
#ifdef WRONG_TYPE
    return {
        .type = OptConvert<TextDecoration>(src.type).value_or(TextDecoration::NONE),
        .color = OptConvert<Color>(src.color),
        .style = OptConvert<TextDecorationStyle>(src.style)
    };
#else
    return {};
#endif
}

template<>
Dimension Convert(const Ark_LetterSpacingStyle& src)
{
#ifdef WRONG_TYPE
    return Convert<Dimension>(src.letterSpacing);
#else
    return {};
#endif
}

template<>
Dimension Convert(const Ark_BaselineOffsetStyle& src)
{
#ifdef WRONG_TYPE
    return Convert<Dimension>(src.baselineOffset);
#else
    return {};
#endif
}

template<>
Dimension Convert(const Ark_LineHeightStyle& src)
{
#ifdef WRONG_TYPE
    return Convert<Dimension>(src.lineHeight);
#else
    return {};
#endif
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
#ifdef WRONG_TYPE
    return Convert<std::vector<Shadow>>(src.textShadow);
#else
    return {};
#endif
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
    return {
        .size = Convert<LeadingMarginSize>(src.size),
        .pixmap = Convert<RefPtr<PixelMap>>(src.pixelMap)
    };
}

template<>
SpanParagraphStyle Convert(const Ark_ParagraphStyle& src)
{
#ifdef WRONG_TYPE
    return {
        .align = OptConvert<TextAlign>(src.textAlign),
        .maxLines = OptConvert<int32_t>(src.maxLines),
        .wordBreak = OptConvert<WordBreak>(src.wordBreak),
        .textOverflow = OptConvert<TextOverflow>(src.overflow),
        .leadingMargin = OptConvert<LeadingMargin>(src.leadingMargin),
        .textIndent = OptConvert<Dimension>(src.textIndent)
    };
#else
    return {};
#endif
}

template<>
TextBackgroundStyle Convert(const Ark_BackgroundColorStyle& src)
{
#ifdef WRONG_TYPE
    return Convert<TextBackgroundStyle>(src.textBackgroundStyle);
#else
    return {};
#endif
}

template<>
std::string Convert(const Ark_UrlStyle& src)
{
#ifdef WRONG_TYPE
    return Convert<std::string>(src.url);
#else
    return {};
#endif
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
#ifdef WRONG_TYPE
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
#else
    return nullptr;
#endif
}
} // namespace OHOS::Ace::NG::Converter

namespace OHOS::Ace::NG::GeneratedModifier {
namespace {
void UpdateSpansRange(std::vector<RefPtr<SpanBase>>& styles, int32_t maxLength)
{
    for (auto& style : styles) {
        if (style == nullptr) {
            continue;
        }
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
const GENERATED_ArkUIMutableStyledStringAccessor* GetMutableStyledStringAccessor();

namespace StyledStringAccessor {
RefPtr<TaskExecutor> CreateTaskExecutor(StringArray& errors)
{
    auto container = Container::CurrentSafely();
    if (!container) {
        errors.emplace_back("FromHtml container is null");
        return nullptr;
    }
    auto taskExecutor = container->GetTaskExecutor();
    if (taskExecutor == nullptr) {
        errors.emplace_back("FromHtml taskExecutor is null");
        return nullptr;
    }
    return taskExecutor;
}
void DestroyPeerImpl(Ark_StyledString peer)
{
    StyledStringPeer::Destroy(peer);
}
Ark_StyledString CtorImpl(const Ark_Union_String_ImageAttachment_CustomSpan* value,
                          const Opt_Array_StyleOptions* styles)
{
    auto peer = StyledStringPeer::Create();
    if (value) {
        Converter::VisitUnion(*value,
            [&peer, styles](const Ark_String& arkText) {
                auto data = Converter::Convert<std::u16string>(arkText);
                peer->spanString = AceType::MakeRefPtr<SpanString>(data);
                CHECK_NULL_VOID(!data.empty() && styles);
                auto spans = Converter::OptConvert<std::vector<RefPtr<SpanBase>>>(*styles);
                CHECK_NULL_VOID(spans);
                UpdateSpansRange(spans.value(), data.length());
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
        peer->spanString = AceType::MakeRefPtr<SpanString>(std::u16string());
    }
    return peer;
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Ark_String GetStringImpl(Ark_StyledString peer)
{
    CHECK_NULL_RETURN(peer, {});
    CHECK_NULL_RETURN(peer->spanString, {});
    peer->spanString->GetString();
    // string need to be returned
    LOGE("StyledStringAccessor::GetStringImpl - return value need to be supported");
    return {};
}
Array_SpanStyle GetStylesImpl(Ark_VMContext vmContext,
                              Ark_StyledString peer,
                              const Ark_Number* start,
                              const Ark_Number* length,
                              const Opt_StyledStringKey* styledKey)
{
    CHECK_NULL_RETURN(peer, {});
    CHECK_NULL_RETURN(peer->spanString, {});
    CHECK_NULL_RETURN(start, {});
    CHECK_NULL_RETURN(length, {});
    auto spanStart = Converter::Convert<int32_t>(*start);
    auto spanLength = Converter::Convert<int32_t>(*length);
    if (!peer->spanString->CheckRange(spanStart, spanLength)) {
        LOGE("CheckBoundary failed: start:%{public}d length:%{public}d", spanStart, spanLength);
        return {};
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
    return {};
}
Ark_Boolean EqualsImpl(Ark_StyledString peer,
                       Ark_StyledString other)
{
    CHECK_NULL_RETURN(peer, false);
    CHECK_NULL_RETURN(peer->spanString, false);
    CHECK_NULL_RETURN(other, false);
    CHECK_NULL_RETURN(other->spanString, false);
    return peer->spanString->IsEqualToSpanString(other->spanString);
}
Ark_StyledString SubStyledStringImpl(Ark_VMContext vmContext,
                                     Ark_StyledString peer,
                                     const Ark_Number* start,
                                     const Opt_Number* length)
{
    Ark_StyledString ret = nullptr;
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
    return StyledStringPeer::Create(spanString);
}
void FromHtmlImpl(Ark_VMContext vmContext,
                  Ark_AsyncWorkerPtr asyncWorker,
                  const Ark_String* html,
                  const Callback_Opt_StyledString_Opt_Array_String_Void* outputArgumentForReturningPromise)
{
    ContainerScope scope(Container::CurrentIdSafely());
    StringArray errorsStr;
    Ark_StyledString peer = GetMutableStyledStringAccessor()->ctor();

    auto callback = [arkCallback = CallbackHelper(*outputArgumentForReturningPromise)]
        (Ark_StyledString peer, const StringArray& errors) {
        Converter::ArkArrayHolder<Array_String> errorHolder(errors);
        arkCallback.Invoke(Converter::ArkValue<Opt_StyledString>(peer), errorHolder.OptValue<Opt_Array_String>());
    };

    auto htmlStr = html ? Converter::Convert<std::string>(*html) : std::string();
    if (htmlStr.empty()) {
        errorsStr.emplace_back("html is empty");
        callback(peer, errorsStr);
        return;
    }
    auto taskExecutor = CreateTaskExecutor(errorsStr);
    if (taskExecutor == nullptr) {
        callback(peer, errorsStr);
        return;
    }

    auto instanceId = Container::CurrentIdSafely();
    taskExecutor->PostTask([callback, peer, htmlStr, errors = errorsStr, instanceId]() mutable {
        ContainerScope scope(instanceId);
        if (auto styledString = OHOS::Ace::HtmlUtils::FromHtml(htmlStr); styledString) {
            peer->spanString = styledString;
        } else {
            errors.emplace_back("Convert html to styledString fails");
        }
        auto container = OHOS::Ace::AceEngine::Get().GetContainer(instanceId);
        if (!container) {
            errors.emplace_back("FromHtmlReturn container is null");
            callback(peer, errors);
            return;
        }
        auto taskExecutor = container->GetTaskExecutor();
        if (!taskExecutor) {
            errors.emplace_back("FromHtmlReturn taskExecutor is null");
            callback(peer, errors);
            return;
        }
        taskExecutor->PostTask(
            [callback, peer, errors]() mutable { callback(peer, errors); },
            TaskExecutor::TaskType::UI, "FromHtmlReturn", PriorityType::VIP);
        }, TaskExecutor::TaskType::BACKGROUND, "FromHtml", PriorityType::IMMEDIATE);
}
Ark_String ToHtmlImpl(Ark_VMContext vmContext,
                      Ark_StyledString styledString)
{
    CHECK_NULL_RETURN(styledString, {});
    CHECK_NULL_RETURN(styledString->spanString, {});
    auto htmlStr = OHOS::Ace::HtmlUtils::ToHtml(Referenced::RawPtr(styledString->spanString));
    LOGE("StyledStringAccessor::ToHtmlImpl - return value need to be supported");
    return {};
}
Ark_Buffer Marshalling0Impl(Ark_StyledString styledString,
                            const StyledStringMarshallCallback* callback_)
{
    return {};
}
void Unmarshalling0Impl(Ark_VMContext vmContext,
                        Ark_AsyncWorkerPtr asyncWorker,
                        const Ark_Buffer* buffer,
                        const StyledStringUnmarshallCallback* callback_,
                        const Callback_Opt_StyledString_Opt_Array_String_Void* outputArgumentForReturningPromise)
{
}
Ark_Buffer Marshalling1Impl(Ark_StyledString styledString)
{
    CHECK_NULL_RETURN(styledString, {});
    CHECK_NULL_RETURN(styledString->spanString, {});
    std::vector<uint8_t> tlvData;
    styledString->spanString->EncodeTlv(tlvData);

    size_t bufferSize = tlvData.size();
    auto data = tlvData.data();
    LOGE("StyledStringAccessor::MarshallingImpl - return value need to be supported");
    return {};
}
void Unmarshalling1Impl(Ark_VMContext vmContext,
                        Ark_AsyncWorkerPtr asyncWorker,
                        const Ark_Buffer* buffer,
                        const Callback_Opt_StyledString_Opt_Array_String_Void* outputArgumentForReturningPromise)
{
    CHECK_NULL_VOID(outputArgumentForReturningPromise);
    std::vector<std::string> errorsStr;
    StyledStringPeer *peer = StyledStringPeer::Create();

    auto callback = [arkCallback = CallbackHelper(*outputArgumentForReturningPromise)]
        (StyledStringPeer* peer, const StringArray& errors) {
        Converter::ArkArrayHolder<Array_String> errorHolder(errors);
        arkCallback.Invoke(Converter::ArkValue<Opt_StyledString>(peer), errorHolder.OptValue<Opt_Array_String>());
    };

    auto str = Converter::Convert<std::string>(*buffer);
    if (str.empty()) {
        errorsStr.emplace_back("buffer is empty");
        callback(peer, errorsStr);
        return;
    }
    std::vector<uint8_t> vec(str.begin(), str.end());
    peer->spanString = SpanString::DecodeTlv(vec);

    callback(peer, errorsStr);
}
Ark_Number GetLengthImpl(Ark_StyledString peer)
{
    const auto errValue = Converter::ArkValue<Ark_Number>(0);
    CHECK_NULL_RETURN(peer, errValue);
    CHECK_NULL_RETURN(peer->spanString, errValue);
    return Converter::ArkValue<Ark_Number>(peer->spanString->GetLength());
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
        StyledStringAccessor::Marshalling0Impl,
        StyledStringAccessor::Unmarshalling0Impl,
        StyledStringAccessor::Marshalling1Impl,
        StyledStringAccessor::Unmarshalling1Impl,
        StyledStringAccessor::GetLengthImpl,
    };
    return &StyledStringAccessorImpl;
}

}
