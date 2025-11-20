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
#include "core/interfaces/native/utility/buffer_keeper.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/promise_helper.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/interfaces/native/implementation/background_color_style_peer.h"
#include "core/interfaces/native/implementation/baseline_offset_style_peer.h"
#include "core/interfaces/native/implementation/custom_span_peer.h"
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
#include "core/interfaces/native/implementation/text_style_peer.h"
#include "core/interfaces/native/implementation/url_style_peer.h"
#include "core/interfaces/native/implementation/user_data_span_holder.h"
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

static bool CheckKeyAndValueTypeEqual(int32_t styledKey, size_t valueTypeId)
{
    static int32_t KeyAndValueTypeMap[] = {
        ARK_STYLED_STRING_KEY_FONT, ARK_STYLED_STRING_KEY_DECORATION, ARK_STYLED_STRING_KEY_BASELINE_OFFSET,
        ARK_STYLED_STRING_KEY_LETTER_SPACING, ARK_STYLED_STRING_KEY_TEXT_SHADOW, ARK_STYLED_STRING_KEY_GESTURE,
        ARK_STYLED_STRING_KEY_IMAGE, ARK_STYLED_STRING_KEY_PARAGRAPH_STYLE, ARK_STYLED_STRING_KEY_LINE_HEIGHT,
        ARK_STYLED_STRING_KEY_URL, ARK_STYLED_STRING_KEY_CUSTOM_SPAN, ARK_STYLED_STRING_KEY_USER_DATA,
        ARK_STYLED_STRING_KEY_BACKGROUND_COLOR
    };
    return (valueTypeId < (sizeof(KeyAndValueTypeMap) / sizeof(int32_t))) &&
        (KeyAndValueTypeMap[valueTypeId] == styledKey);
}

template<>
RefPtr<SpanBase> Convert(const Ark_StyleOptions& src)
{
    RefPtr<SpanBase> result;
    auto start = Converter::OptConvert<int32_t>(src.start).value_or(0);
    start = std::max(0, start);
    auto end = Converter::OptConvert<int32_t>(src.length).value_or(0) + start;
    Converter::VisitUnion(src.styledValue,
        [&result, start, end, &src](const auto& peer) {
            CHECK_NULL_VOID(peer && peer->span);
            auto valueTypeId = Converter::Convert<int32_t>(src.styledValue.selector);
            // Ark_CustomSpan, Ark_ImageAttachment will be declined by this check
            if (!CheckKeyAndValueTypeEqual(static_cast<int32_t>(src.styledKey), valueTypeId)) {
                return;
            }
            result = peer->span->GetSubSpan(start, end);
        },
        [&result, start, end](const Ark_UserDataSpan& value) {
            result = AceType::MakeRefPtr<UserDataSpanHolder>(value, start, end);
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
Ark_StyledString ConstructImpl(const Ark_Union_String_ImageAttachment_CustomSpan* value,
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
            [&peer](const Ark_CustomSpan& arkCustomSpan) {
                CustomSpanPeer* peerCustomSpan = arkCustomSpan;
                CHECK_NULL_VOID(peerCustomSpan && peerCustomSpan->span);
                auto customSpan = AceType::DynamicCast<CustomSpan>(peerCustomSpan->span);
                peer->spanString = AceType::MakeRefPtr<SpanString>(customSpan);
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
Opt_Array_SpanStyle GetStylesImpl(Ark_StyledString peer,
                                  Ark_Int32 start,
                                  Ark_Int32 length,
                                  const Opt_StyledStringKey* styledKey)
{
    CHECK_NULL_RETURN(peer, Converter::ArkValue<Opt_Array_SpanStyle>(Ark_Empty()));
    CHECK_NULL_RETURN(peer->spanString, Converter::ArkValue<Opt_Array_SpanStyle>(Ark_Empty()));
    auto spanStart = Converter::Convert<int32_t>(start);
    auto spanLength = Converter::Convert<int32_t>(length);
    if (!peer->spanString->CheckRange(spanStart, spanLength)) {
        LOGE("CheckBoundary failed: start:%{public}d length:%{public}d", spanStart, spanLength);
        return Converter::ArkValue<Opt_Array_SpanStyle>(Ark_Empty());
    }
    std::vector<RefPtr<SpanBase>> spans;
    auto spanType = Converter::OptConvertPtr<Ace::SpanType>(styledKey);
    if (spanType.has_value()) {
        spans = peer->spanString->GetSpans(spanStart, spanLength, spanType.value());
    } else {
        spans = peer->spanString->GetSpans(spanStart, spanLength);
    }
    return Converter::ArkValue<Opt_Array_SpanStyle>(spans, Converter::FC);
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
Opt_StyledString SubStyledStringImpl(Ark_StyledString peer,
                                     Ark_Int32 start,
                                     const Opt_Int32* length)
{
    CHECK_NULL_RETURN(peer, Converter::ArkValue<Opt_StyledString>(Ark_Empty()));
    CHECK_NULL_RETURN(peer->spanString, Converter::ArkValue<Opt_StyledString>(Ark_Empty()));
    auto startSpan = Converter::Convert<int32_t>(start);
    auto lengthSpan = peer->spanString->GetLength() - startSpan;
    auto lengthOpt = Converter::OptConvertPtr<int32_t>(length);
    if (lengthOpt) {
        lengthSpan = std::min(lengthSpan, lengthOpt.value());
    }
    if (!peer->spanString->CheckRange(startSpan, lengthSpan)) {
        LOGE("CheckBoundary failed: start:%{public}d length:%{public}d", startSpan, lengthSpan);
        return Converter::ArkValue<Opt_StyledString>(Ark_Empty());
    }
    auto spanString = peer->spanString->GetSubSpanString(startSpan, lengthSpan);
    CHECK_NULL_RETURN(spanString, Converter::ArkValue<Opt_StyledString>(Ark_Empty()));
    return Converter::ArkValue<Opt_StyledString>(StyledStringPeer::Create(spanString));
}
void FromHtmlImpl(Ark_VMContext vmContext,
                  Ark_AsyncWorkerPtr asyncWorker,
                  const Ark_String* html,
                  const Callback_Opt_StyledString_Opt_Array_String_Void* outputArgumentForReturningPromise)
{
    CHECK_NULL_VOID(asyncWorker);
    auto promise = std::make_shared<PromiseHelper<Callback_Opt_StyledString_Opt_Array_String_Void>>(
        outputArgumentForReturningPromise);
    auto htmlStr = html ? Converter::Convert<std::string>(*html) : std::string();
    if (htmlStr.empty()) {
        promise->Reject<Opt_StyledString>({"html is empty"});
        return;
    }
    promise->StartAsync(vmContext, *asyncWorker, [promise, htmlStr]() {
        if (auto styledString = OHOS::Ace::HtmlUtils::FromHtml(htmlStr); styledString) {
            auto peer = StyledStringPeer::Create();
            peer->spanString = styledString;
            promise->Resolve(Converter::ArkValue<Opt_StyledString, Ark_StyledString>(peer));
        } else {
            promise->Reject<Opt_StyledString>({"Convert html to styledString fails"});
        }
    });
}
Ark_String ToHtmlImpl(Ark_StyledString styledString)
{
    std::string result = "";
    CHECK_NULL_RETURN(styledString, Converter::ArkValue<Ark_String>(result, Converter::FC));
    CHECK_NULL_RETURN(styledString->spanString, Converter::ArkValue<Ark_String>(result, Converter::FC));
    result = OHOS::Ace::HtmlUtils::ToHtml(Referenced::RawPtr(styledString->spanString));
    return Converter::ArkValue<Ark_String>(result, Converter::FC);
}
Opt_Buffer Marshalling0Impl(Ark_StyledString styledString,
                            const StyledStringMarshallCallback* callback_)
{
    CHECK_NULL_RETURN(styledString, Converter::ArkValue<Opt_Buffer>(Ark_Empty()));
    CHECK_NULL_RETURN(callback_, Converter::ArkValue<Opt_Buffer>(Ark_Empty()));

    std::vector<uint8_t> tlvData;
    if (!styledString->spanString->EncodeTlv(tlvData)) {
        return Converter::ArkValue<Opt_Buffer>(Ark_Empty());
    }

    if (callback_) {
        auto arkCallback = CallbackHelper(*callback_);
        RefPtr<UserDataSpanHolder> currentSpan = nullptr;
        auto handlerDataFunc = [&tlvData, &currentSpan](const Ark_Buffer arkBuff) {
            TLVUtil::WriteUint8(tlvData, TLV_CUSTOM_MARSHALL_BUFFER_START);
            TLVUtil::WriteInt32(tlvData, arkBuff.length + sizeof(int32_t) + sizeof(int32_t));
            TLVUtil::WriteInt32(tlvData, currentSpan->GetStartIndex());
            TLVUtil::WriteInt32(tlvData, currentSpan->GetLength());
            auto arkBuffData = static_cast<const uint8_t*>(arkBuff.data);
            tlvData.insert(tlvData.end(), arkBuffData, arkBuffData + arkBuff.length);
        };
        auto continuation = CallbackKeeper::Claim<Callback_Buffer_Void>(handlerDataFunc);

        auto spans = styledString->spanString->GetSpans(0, styledString->spanString->GetLength(), SpanType::ExtSpan);
        for (const RefPtr<SpanBase>& span : spans) {
            currentSpan = AceType::DynamicCast<UserDataSpanHolder>(span);
            if (currentSpan) {
                arkCallback.InvokeSync(currentSpan->span_, continuation.ArkValue());
            }
        }
        TLVUtil::WriteUint8(tlvData, TLV_END);
    }
    if (tlvData.empty()) {
        return Converter::ArkValue<Opt_Buffer>(Ark_Empty());
    }
    Ark_Buffer result = BufferKeeper::Allocate(tlvData.size());
    std::copy(tlvData.begin(), tlvData.end(), reinterpret_cast<uint8_t*>(result.data));
    return Converter::ArkValue<Opt_Buffer>(result);
}
void Unmarshalling0Impl(Ark_VMContext vmContext,
                        Ark_AsyncWorkerPtr asyncWorker,
                        const Ark_Buffer* buffer,
                        const StyledStringUnmarshallCallback* callback_,
                        const Callback_Opt_StyledString_Opt_Array_String_Void* outputArgumentForReturningPromise)
{
    CHECK_NULL_VOID(asyncWorker);
    auto promise = std::make_shared<PromiseHelper<Callback_Opt_StyledString_Opt_Array_String_Void>>(
        outputArgumentForReturningPromise);

    if (!buffer || !buffer->data || !buffer->length) {
        promise->Reject<Opt_StyledString>({"buffer is empty"});
        return;
    }
    (buffer->resource.hold) ? (*buffer->resource.hold)(buffer->resource.resourceId): (void)0;

    auto instanceId = Container::CurrentIdSafely();

    std::function<RefPtr<ExtSpan>(const std::vector<uint8_t>&, int32_t, int32_t)> unmarshall;
    if (callback_) {
        unmarshall = [instanceId, arkCallback = CallbackHelper(*callback_)]
        (const std::vector<uint8_t>& buff, int32_t spanStart, int32_t spanLength) -> RefPtr<ExtSpan> {
            ContainerScope scope(instanceId);
            Ark_Buffer arkBuffer = BufferKeeper::Allocate(buff.size());
            std::copy(buff.begin(), buff.end(), reinterpret_cast<uint8_t*>(arkBuffer.data));
            RefPtr<ExtSpan> result;
            auto continuation = CallbackKeeper::Claim<Callback_UserDataSpan_Void>(
                [&result, spanStart, spanLength](Ark_UserDataSpan arkUserDataSpan) {
                result = AceType::MakeRefPtr<UserDataSpanHolder>(arkUserDataSpan, spanStart, spanStart + spanLength);
            });
            arkCallback.InvokeSync(arkBuffer, continuation.ArkValue());
            arkBuffer.resource.release(arkBuffer.resource.resourceId);
            return result;
        };
    }

    auto unmarshallingExec = [promise, buffer = std::move(buffer), instanceId, unmarshall = std::move(unmarshall)]() {
        auto data = static_cast<uint8_t*>(buffer->data);
        auto buff = data ? std::vector<uint8_t>(data, data + buffer->length) : std::vector<uint8_t>();
        (buffer->resource.release) ? (*buffer->resource.release)(buffer->resource.resourceId): (void)0;

        Ark_StyledString peer = StyledStringPeer::Create();
        peer->spanString = SpanString::DecodeTlv(buff, std::move(unmarshall), instanceId);
        promise->Resolve(Converter::ArkValue<Opt_StyledString, Ark_StyledString>(peer));
    };

    promise->StartAsync(vmContext, *asyncWorker, std::move(unmarshallingExec));
}
Opt_Buffer Marshalling1Impl(Ark_StyledString styledString)
{
    CHECK_NULL_RETURN(styledString, Converter::ArkValue<Opt_Buffer>(Ark_Empty()));
    CHECK_NULL_RETURN(styledString->spanString, Converter::ArkValue<Opt_Buffer>(Ark_Empty()));
    std::vector<uint8_t> tlvData;
    styledString->spanString->EncodeTlv(tlvData);
    Ark_Buffer result = BufferKeeper::Allocate(tlvData.size());
    copy(tlvData.begin(), tlvData.end(), reinterpret_cast<uint8_t*>(result.data));
    return Converter::ArkValue<Opt_Buffer>(result);
}
void Unmarshalling1Impl(Ark_VMContext vmContext,
                        Ark_AsyncWorkerPtr asyncWorker,
                        const Ark_Buffer* buffer,
                        const Callback_Opt_StyledString_Opt_Array_String_Void* outputArgumentForReturningPromise)
{
    Unmarshalling0Impl(vmContext, asyncWorker, buffer, nullptr, outputArgumentForReturningPromise);
}
Ark_Int32 GetLengthImpl(Ark_StyledString peer)
{
    const auto errValue = Converter::ArkValue<Ark_Int32>(0);
    CHECK_NULL_RETURN(peer, errValue);
    CHECK_NULL_RETURN(peer->spanString, errValue);
    return Converter::ArkValue<Ark_Int32>(peer->spanString->GetLength());
}
} // StyledStringAccessor
const GENERATED_ArkUIStyledStringAccessor* GetStyledStringAccessor()
{
    static const GENERATED_ArkUIStyledStringAccessor StyledStringAccessorImpl {
        StyledStringAccessor::DestroyPeerImpl,
        StyledStringAccessor::ConstructImpl,
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
