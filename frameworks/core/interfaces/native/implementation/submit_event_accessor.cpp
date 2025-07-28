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
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/interfaces/native/implementation/submit_event_peer.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace SubmitEventAccessor {
void DestroyPeerImpl(Ark_SubmitEvent peer)
{
    PeerUtils::DestroyPeer(peer);
}
Ark_SubmitEvent CtorImpl()
{
    return PeerUtils::CreatePeer<SubmitEventPeer>();
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
void KeepEditableStateImpl(Ark_SubmitEvent peer)
{
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(peer->GetEventInfo());
    peer->GetEventInfo()->SetKeepEditable(true);
}
Ark_String GetTextImpl(Ark_SubmitEvent peer)
{
    std::u16string result = u"";
    CHECK_NULL_RETURN(peer, Converter::ArkValue<Ark_String>(result, Converter::FC));
    CHECK_NULL_RETURN(peer->GetEventInfo(), Converter::ArkValue<Ark_String>(result, Converter::FC));
    result = peer->GetEventInfo()->GetText();
    return Converter::ArkValue<Ark_String>(result, Converter::FC);
}
void SetTextImpl(Ark_SubmitEvent peer,
                 const Ark_String* text)
{
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(peer->GetEventInfo());
    auto string = Converter::Convert<std::u16string>(*text);
    peer->GetEventInfo()->SetText(string);
}
} // SubmitEventAccessor
const GENERATED_ArkUISubmitEventAccessor* GetSubmitEventAccessor()
{
    static const GENERATED_ArkUISubmitEventAccessor SubmitEventAccessorImpl {
        SubmitEventAccessor::DestroyPeerImpl,
        SubmitEventAccessor::CtorImpl,
        SubmitEventAccessor::GetFinalizerImpl,
        SubmitEventAccessor::KeepEditableStateImpl,
        SubmitEventAccessor::GetTextImpl,
        SubmitEventAccessor::SetTextImpl,
    };
    return &SubmitEventAccessorImpl;
}
}
