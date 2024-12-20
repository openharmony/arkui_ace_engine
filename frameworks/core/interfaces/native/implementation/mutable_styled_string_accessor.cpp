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
#include "arkoala_api_generated.h"

#include "core/interfaces/native/implementation/styled_string.h"
#include "core/interfaces/native/implementation/mutable_styled_string_peer.h"

namespace OHOS::Ace::NG::Converter {
template<>
RefPtr<SpanBase> Convert(const Ark_SpanStyle& src)
{
    return Convert<RefPtr<SpanBase>>(Ark_StyleOptions {
        .start = ArkValue<Opt_Number>(src.start),
        .length = ArkValue<Opt_Number>(src.length),
        .styledKey = src.styledKey,
        .styledValue = src.styledValue,
    });
}
} // namespace OHOS::Ace::NG::Converter

namespace OHOS::Ace::NG::GeneratedModifier {
namespace MutableStyledStringAccessor {
void DestroyPeerImpl(MutableStyledStringPeer* peer)
{
    delete peer;
}
Ark_NativePointer CtorImpl()
{
    return new MutableStyledStringPeer();
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
void ReplaceStringImpl(MutableStyledStringPeer* peer,
                       const Ark_Number* start,
                       const Ark_Number* length,
                       const Ark_String* other)
{
    CHECK_NULL_VOID(peer && start && length && other);
    auto mutableString = peer->GetMutableString();
    CHECK_NULL_VOID(mutableString);
    const auto convStart = Converter::Convert<int32_t>(*start);
    const auto convLength = Converter::Convert<int32_t>(*length);
    if (mutableString->CheckRange(convStart, convLength)) {
        const auto string = Converter::Convert<std::string>(*other);
        mutableString->ReplaceString(convStart, convLength, string);
    } else {
        // throw exception.
    }
}
void InsertStringImpl(MutableStyledStringPeer* peer,
                      const Ark_Number* start,
                      const Ark_String* other)
{
    CHECK_NULL_VOID(peer && start && other);
    auto mutableString = peer->GetMutableString();
    CHECK_NULL_VOID(mutableString);
    auto strLength = mutableString->GetLength();
    const auto convStart = Converter::Convert<int32_t>(*start);
    if (convStart >= 0 && convStart <= strLength) {
        const auto string = Converter::Convert<std::string>(*other);
        mutableString->InsertString(convStart, string);
    } else {
        // throw exception.
    }
}
void RemoveStringImpl(MutableStyledStringPeer* peer,
                      const Ark_Number* start,
                      const Ark_Number* length)
{
    CHECK_NULL_VOID(peer && start && length);
    auto mutableString = peer->GetMutableString();
    CHECK_NULL_VOID(mutableString);
    const auto convStart = Converter::Convert<int32_t>(*start);
    const auto convLength = Converter::Convert<int32_t>(*length);
    if (mutableString->CheckRange(convStart, convLength)) {
        mutableString->RemoveString(convStart, convLength);
    } else {
        // throw exception.
    }
}
void ReplaceStyleImpl(MutableStyledStringPeer* peer,
                      const Ark_SpanStyle* spanStyle)
{
    CHECK_NULL_VOID(peer && spanStyle);
    auto mutableString = peer->GetMutableString();
    CHECK_NULL_VOID(mutableString);
    const auto convStart = Converter::Convert<int32_t>(spanStyle->start);
    const auto convLength = Converter::Convert<int32_t>(spanStyle->length);
    if (mutableString->CheckRange(convStart, convLength)) {
        auto convSpan = Converter::Convert<RefPtr<SpanBase>>(*spanStyle);
        mutableString->ReplaceSpan(convStart, convLength, convSpan);
    } else {
        // throw exception.
    }
}
void SetStyleImpl(MutableStyledStringPeer* peer,
                  const Ark_SpanStyle* spanStyle)
{
    CHECK_NULL_VOID(peer && spanStyle);
    auto mutableString = peer->GetMutableString();
    CHECK_NULL_VOID(mutableString);
}
void RemoveStyleImpl(MutableStyledStringPeer* peer,
                     const Ark_Number* start,
                     const Ark_Number* length,
                     Ark_StyledStringKey styledKey)
{
    CHECK_NULL_VOID(peer && start && length);
    auto mutableString = peer->GetMutableString();
    CHECK_NULL_VOID(mutableString);
}
void RemoveStylesImpl(MutableStyledStringPeer* peer,
                      const Ark_Number* start,
                      const Ark_Number* length)
{
    CHECK_NULL_VOID(peer && start && length);
    auto mutableString = peer->GetMutableString();
    CHECK_NULL_VOID(mutableString);
}
void ClearStylesImpl(MutableStyledStringPeer* peer)
{
    CHECK_NULL_VOID(peer);
    auto mutableString = peer->GetMutableString();
    CHECK_NULL_VOID(mutableString);
}
void ReplaceStyledStringImpl(MutableStyledStringPeer* peer,
                             const Ark_Number* start,
                             const Ark_Number* length,
                             const Ark_StyledString* other)
{
    CHECK_NULL_VOID(peer && start && length && other);
    auto mutableString = peer->GetMutableString();
    CHECK_NULL_VOID(mutableString);
}
void InsertStyledStringImpl(MutableStyledStringPeer* peer,
                            const Ark_Number* start,
                            const Ark_StyledString* other)
{
    CHECK_NULL_VOID(peer && start && other);
    auto mutableString = peer->GetMutableString();
    CHECK_NULL_VOID(mutableString);
}
void AppendStyledStringImpl(MutableStyledStringPeer* peer,
                            const Ark_StyledString* other)
{
    CHECK_NULL_VOID(peer && other);
    auto mutableString = peer->GetMutableString();
    CHECK_NULL_VOID(mutableString);
}
} // MutableStyledStringAccessor
const GENERATED_ArkUIMutableStyledStringAccessor* GetMutableStyledStringAccessor()
{
    static const GENERATED_ArkUIMutableStyledStringAccessor MutableStyledStringAccessorImpl {
        MutableStyledStringAccessor::DestroyPeerImpl,
        MutableStyledStringAccessor::CtorImpl,
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

struct MutableStyledStringPeer {
    virtual ~MutableStyledStringPeer() = default;
};
}
