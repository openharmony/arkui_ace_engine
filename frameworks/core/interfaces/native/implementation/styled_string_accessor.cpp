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
#include "core/interfaces/native/utility/buffer_keeper.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/implementation/background_color_style_peer.h"
#include "core/interfaces/native/implementation/baseline_offset_style_peer.h"
#include "core/interfaces/native/implementation/decoration_style_peer.h"
#include "core/interfaces/native/implementation/gesture_style_peer.h"
#include "core/interfaces/native/implementation/image_attachment_peer.h"
#include "core/interfaces/native/implementation/letter_spacing_style_peer.h"
#include "core/interfaces/native/implementation/line_height_style_peer.h"
#include "core/interfaces/native/implementation/paragraph_style_peer.h"
#include "core/interfaces/native/implementation/styled_string.h"
#include "core/interfaces/native/implementation/styled_string_peer.h"
#include "core/interfaces/native/implementation/mutable_styled_string_peer.h"
#include "core/interfaces/native/implementation/text_shadow_style_peer.h"
#include "core/interfaces/native/implementation/text_style_styled_string_peer.h"
#include "core/interfaces/native/implementation/url_style_peer.h"
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
BorderRadiusProperty Convert(const Ark_ImageAttachmentLayoutStyle& src)
{
    auto result = OptConvert<BorderRadiusProperty>(src.borderRadius);
    if (!result.has_value()) {
        result = BorderRadiusProperty();
    }
    return result.value();
}

template<>
RefPtr<SpanBase> Convert(const Ark_StyleOptions& src)
{
    RefPtr<SpanBase> result;
    Converter::VisitUnion(src.styledValue,
        [&result, &src](const auto& peer) {
            CHECK_NULL_VOID(peer);
            result = peer->span;
            CHECK_NULL_VOID(result);
            auto start = Converter::OptConvert<int32_t>(src.start).value_or(0);
            auto end = Converter::OptConvert<int32_t>(src.length).value_or(0) + start;
            result->UpdateStartIndex(start);
            result->UpdateEndIndex(end);
        },
        [&result, &src](const Ark_UserDataSpan& peer) {
            auto start = Converter::OptConvert<int32_t>(src.start).value_or(0);
            auto end = Converter::OptConvert<int32_t>(src.length).value_or(0) + start;
            result = AceType::MakeRefPtr<ExtSpan>(start, end);
        },
        [](const Ark_ImageAttachment& style) {
            LOGE("Converter::Convert(Ark_StyleOptions) the Ark_ImageAttachment is not implemented.");
        },
        [](const Ark_CustomSpan& style) {
            LOGE("Converter::Convert(Ark_StyleOptions) the Ark_CustomSpan is not implemented.");
        },
        []() {}
    );
    return result;
}
} // namespace OHOS::Ace::NG::Converter

namespace OHOS::Ace::NG::GeneratedModifier {
using namespace Converter;

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
                ImageAttachmentPeer* peerImageAttachment = arkImageAttachment;
                CHECK_NULL_VOID(peerImageAttachment && peerImageAttachment->span);
                auto options = peerImageAttachment->span->GetImageSpanOptions();
                peer->spanString = AceType::MakeRefPtr<SpanString>(options);
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
    std::string result = "";
    CHECK_NULL_RETURN(peer, Converter::ArkValue<Ark_String>(result, Converter::FC));
    CHECK_NULL_RETURN(peer->spanString, Converter::ArkValue<Ark_String>(result, Converter::FC));
    result = peer->spanString->GetString();
    return Converter::ArkValue<Ark_String>(result, Converter::FC);
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
    return Converter::ArkValue<Array_SpanStyle>(spans, Converter::FC);
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
    std::string result = "";
    CHECK_NULL_RETURN(styledString, Converter::ArkValue<Ark_String>(result, Converter::FC));
    CHECK_NULL_RETURN(styledString->spanString, Converter::ArkValue<Ark_String>(result, Converter::FC));
    result = OHOS::Ace::HtmlUtils::ToHtml(Referenced::RawPtr(styledString->spanString));
    return Converter::ArkValue<Ark_String>(result, Converter::FC);
}
Ark_Buffer Marshalling0Impl(Ark_StyledString styledString,
                            const StyledStringMarshallCallback* callback_)
{
    CHECK_NULL_RETURN(styledString, {});
    CHECK_NULL_RETURN(callback_, {});
    LOGE("Ark_UserDataSpan is not implemented.");

    std::vector<uint8_t> tlvData;
    styledString->spanString->EncodeTlv(tlvData);
    Ark_Buffer result = BufferKeeper::Allocate(tlvData.size());
    copy(tlvData.begin(), tlvData.end(), reinterpret_cast<uint8_t*>(result.data));
    return result;
}
Ark_Buffer Marshalling1Impl(Ark_StyledString styledString)
{
    CHECK_NULL_RETURN(styledString, {});
    CHECK_NULL_RETURN(styledString->spanString, {});
    std::vector<uint8_t> tlvData;
    styledString->spanString->EncodeTlv(tlvData);
    Ark_Buffer result = BufferKeeper::Allocate(tlvData.size());
    copy(tlvData.begin(), tlvData.end(), reinterpret_cast<uint8_t*>(result.data));
    return result;
}
void Unmarshalling0Impl(Ark_VMContext vmContext,
                        Ark_AsyncWorkerPtr asyncWorker,
                        const Ark_Buffer* buffer,
                        const StyledStringUnmarshallCallback* callback_,
                        const Callback_Opt_StyledString_Opt_Array_String_Void* outputArgumentForReturningPromise)
{
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
        StyledStringAccessor::Marshalling1Impl,
        StyledStringAccessor::Unmarshalling0Impl,
        StyledStringAccessor::Unmarshalling1Impl,
        StyledStringAccessor::GetLengthImpl,
    };
    return &StyledStringAccessorImpl;
}

}
