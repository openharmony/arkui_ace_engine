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

#include "core/components_ng/base/frame_node.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "arkoala_api_generated.h"

#include "core/interfaces/native/implementation/styled_string.h"
#include "core/interfaces/native/implementation/mutable_styled_string_peer.h"
#include "core/interfaces/native/implementation/image_attachment_peer.h"
#include "core/interfaces/native/implementation/custom_span_peer.h"

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

namespace MutableStyledStringAccessor {
void DestroyPeerImpl(Ark_MutableStyledString peer)
{
    PeerUtils::DestroyPeer(peer);
}
Ark_MutableStyledString ConstructImpl(const Ark_Union_String_ImageAttachment_CustomSpan* value,
                                      const Opt_Array_StyleOptions* styles)
{
    auto peer = PeerUtils::CreatePeer<MutableStyledStringPeer>();
    if (value) {
        Converter::VisitUnion(*value,
            [&peer, styles](const Ark_String& arkText) {
                auto data = Converter::Convert<std::u16string>(arkText);
                peer->spanString = AceType::MakeRefPtr<MutableSpanString>(data);
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
                peer->spanString = AceType::MakeRefPtr<MutableSpanString>(options);
            },
            [&peer](const Ark_CustomSpan& arkCustomSpan) {
                CustomSpanPeer* peerCustomSpan = arkCustomSpan;
                CHECK_NULL_VOID(peerCustomSpan && peerCustomSpan->span);
                auto customSpan = AceType::DynamicCast<CustomSpan>(peerCustomSpan->span);
                peer->spanString = AceType::MakeRefPtr<MutableSpanString>(customSpan);
            },
            []() {}
        );
    }
    if (!peer->spanString) {
        peer->spanString = AceType::MakeRefPtr<MutableSpanString>(std::u16string());
    }
    return peer;
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
void ReplaceStringImpl(Ark_MutableStyledString peer,
                       Ark_Int32 start,
                       Ark_Int32 length,
                       const Ark_String* other)
{
    CHECK_NULL_VOID(peer && other);
    auto mutableString = peer->GetMutableString();
    CHECK_NULL_VOID(mutableString);
    const auto convStart = Converter::Convert<int32_t>(start);
    const auto convLength = Converter::Convert<int32_t>(length);
    if (mutableString->CheckRange(convStart, convLength)) {
        const auto string = Converter::Convert<std::u16string>(*other);
        mutableString->ReplaceString(convStart, convLength, string);
    } else {
        // throw exception.
        LOGE("MutableStyledStringAccessor::ReplaceStringImpl CheckBoundary failed: start:%d length:%d",
            convStart, convLength);
    }
}
void InsertStringImpl(Ark_MutableStyledString peer,
                      Ark_Int32 start,
                      const Ark_String* other)
{
    CHECK_NULL_VOID(peer && other);
    auto mutableString = peer->GetMutableString();
    CHECK_NULL_VOID(mutableString);
    auto strLength = mutableString->GetLength();
    const auto convStart = Converter::Convert<int32_t>(start);
    if (convStart >= 0 && convStart <= strLength) {
        const auto string = Converter::Convert<std::u16string>(*other);
        mutableString->InsertString(convStart, string);
    } else {
        // throw exception.
        LOGE("MutableStyledStringAccessor::InsertStringImpl CheckBoundary failed: start:%d length:%d",
            convStart, strLength);
    }
}
void RemoveStringImpl(Ark_MutableStyledString peer,
                      Ark_Int32 start,
                      Ark_Int32 length)
{
    CHECK_NULL_VOID(peer);
    auto mutableString = peer->GetMutableString();
    CHECK_NULL_VOID(mutableString);
    const auto convStart = Converter::Convert<int32_t>(start);
    const auto convLength = Converter::Convert<int32_t>(length);
    if (mutableString->CheckRange(convStart, convLength)) {
        mutableString->RemoveString(convStart, convLength);
    } else {
        // throw exception.
        LOGE("MutableStyledStringAccessor::RemoveStringImpl CheckBoundary failed: start:%d length:%d",
            convStart, convLength);
    }
}
void ReplaceStyleImpl(Ark_MutableStyledString peer,
                      const Ark_SpanStyle* spanStyle)
{
    CHECK_NULL_VOID(peer && spanStyle);
    auto mutableString = peer->GetMutableString();
    CHECK_NULL_VOID(mutableString);
    const auto convStart = Converter::Convert<int32_t>(spanStyle->start);
    const auto convLength = Converter::Convert<int32_t>(spanStyle->length);
    if (mutableString->CheckRange(convStart, convLength)) {
        auto convSpan = Converter::Convert<RefPtr<SpanBase>>(*spanStyle);
        CHECK_NULL_VOID(convSpan);
        mutableString->ReplaceSpan(convStart, convLength, convSpan);
    } else {
        // throw exception.
        LOGE("MutableStyledStringAccessor::ReplaceStyleImpl CheckBoundary failed: start:%d length:%d",
            convStart, convLength);
    }
}
void SetStyleImpl(Ark_MutableStyledString peer,
                  const Ark_SpanStyle* spanStyle)
{
    CHECK_NULL_VOID(peer && spanStyle);
    auto mutableString = peer->GetMutableString();
    CHECK_NULL_VOID(mutableString);
    const auto convStart = Converter::Convert<int32_t>(spanStyle->start);
    const auto convLength = Converter::Convert<int32_t>(spanStyle->length);
    if (mutableString->CheckRange(convStart, convLength)) {
        const auto type = Converter::OptConvert<Ace::SpanType>(spanStyle->styledKey);
        CHECK_NULL_VOID(type);
        if (type.value() == SpanType::Image || type.value() == SpanType::CustomSpan) {
            mutableString->RemoveSpan(convStart, convLength, type.value());
        }
        auto convSpan = Converter::Convert<RefPtr<SpanBase>>(*spanStyle);
        CHECK_NULL_VOID(convSpan);
        mutableString->AddSpan(convSpan);
    } else {
        // throw exception.
        LOGE("MutableStyledStringAccessor::SetStyleImpl CheckBoundary failed: start:%d length:%d",
            convStart, convLength);
    }
}
void RemoveStyleImpl(Ark_MutableStyledString peer,
                     Ark_Int32 start,
                     Ark_Int32 length,
                     Ark_StyledStringKey styledKey)
{
    CHECK_NULL_VOID(peer);
    auto mutableString = peer->GetMutableString();
    CHECK_NULL_VOID(mutableString);
    const auto convStart = Converter::Convert<int32_t>(start);
    const auto convLength = Converter::Convert<int32_t>(length);
    CHECK_NULL_VOID(mutableString->CheckRange(convStart, convLength));
    const auto type = Converter::OptConvert<Ace::SpanType>(styledKey);
    CHECK_NULL_VOID(type);
    mutableString->RemoveSpan(convStart, convLength, type.value());
}
void RemoveStylesImpl(Ark_MutableStyledString peer,
                      Ark_Int32 start,
                      Ark_Int32 length)
{
    CHECK_NULL_VOID(peer);
    auto mutableString = peer->GetMutableString();
    CHECK_NULL_VOID(mutableString);
    const auto convStart = Converter::Convert<int32_t>(start);
    const auto convLength = Converter::Convert<int32_t>(length);
    CHECK_NULL_VOID(mutableString->CheckRange(convStart, convLength));
    mutableString->RemoveSpans(convStart, convLength);
}
void ClearStylesImpl(Ark_MutableStyledString peer)
{
    CHECK_NULL_VOID(peer);
    auto mutableString = peer->GetMutableString();
    CHECK_NULL_VOID(mutableString);
    mutableString->ClearAllSpans();
}
void ReplaceStyledStringImpl(Ark_MutableStyledString peer,
                             Ark_Int32 start,
                             Ark_Int32 length,
                             Ark_StyledString other)
{
    CHECK_NULL_VOID(peer && other);
    auto mutableString = peer->GetMutableString();
    CHECK_NULL_VOID(mutableString);
    auto otherString = other->GetString();
    CHECK_NULL_VOID(otherString);
    const auto convStart = Converter::Convert<int32_t>(start);
    const auto convLength = Converter::Convert<int32_t>(length);
    if (mutableString->CheckRange(convStart, convLength)) {
        mutableString->ReplaceSpanString(convStart, convLength, otherString);
    } else {
        // throw exception.
        LOGE("MutableStyledStringAccessor::ReplaceStyledStringImpl CheckBoundary failed: start:%d length:%d",
            convStart, convLength);
    }
}
void InsertStyledStringImpl(Ark_MutableStyledString peer,
                            Ark_Int32 start,
                            Ark_StyledString other)
{
    CHECK_NULL_VOID(peer && other);
    auto mutableString = peer->GetMutableString();
    CHECK_NULL_VOID(mutableString);
    auto strLength = mutableString->GetLength();
    const auto convStart = Converter::Convert<int32_t>(start);
    if (convStart >= 0 && convStart <= strLength) {
        auto otherString = other->GetString();
        CHECK_NULL_VOID(otherString);
        mutableString->InsertSpanString(convStart, otherString);
    } else {
        // throw exception.
        LOGE("MutableStyledStringAccessor::InsertStyledStringImpl CheckBoundary failed: start:%d length:%d",
            convStart, strLength);
    }
}
void AppendStyledStringImpl(Ark_MutableStyledString peer,
                            Ark_StyledString other)
{
    CHECK_NULL_VOID(peer && other);
    auto mutableString = peer->GetMutableString();
    CHECK_NULL_VOID(mutableString);
    auto otherString = other->GetString();
    CHECK_NULL_VOID(otherString);
    mutableString->AppendSpanString(otherString);
}
} // MutableStyledStringAccessor
const GENERATED_ArkUIMutableStyledStringAccessor* GetMutableStyledStringAccessor()
{
    static const GENERATED_ArkUIMutableStyledStringAccessor MutableStyledStringAccessorImpl {
        MutableStyledStringAccessor::DestroyPeerImpl,
        MutableStyledStringAccessor::ConstructImpl,
        MutableStyledStringAccessor::GetFinalizerImpl,
        MutableStyledStringAccessor::ReplaceStringImpl,
        MutableStyledStringAccessor::InsertStringImpl,
        MutableStyledStringAccessor::RemoveStringImpl,
        MutableStyledStringAccessor::ReplaceStyleImpl,
        MutableStyledStringAccessor::SetStyleImpl,
        MutableStyledStringAccessor::RemoveStyleImpl,
        MutableStyledStringAccessor::RemoveStylesImpl,
        MutableStyledStringAccessor::ClearStylesImpl,
        MutableStyledStringAccessor::ReplaceStyledStringImpl,
        MutableStyledStringAccessor::InsertStyledStringImpl,
        MutableStyledStringAccessor::AppendStyledStringImpl,
    };
    return &MutableStyledStringAccessorImpl;
}
}
