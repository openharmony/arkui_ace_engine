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

#include "arkoala_api_generated.h"
#include "core/interfaces/native/implementation/paste_event_peer.h"
#include "core/interfaces/native/utility/peer_utils.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace PasteEventAccessor {
void DestroyPeerImpl(Ark_PasteEvent peer)
{
    PeerUtils::DestroyPeer(peer);
}

Ark_PasteEvent ConstructImpl()
{
    return PeerUtils::CreatePeer<PasteEventPeer>();
}

Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}

void PreventDefaultImpl(Ark_PasteEvent peer)
{
    CHECK_NULL_VOID(peer);
    peer->HandlePreventDefault();
}
} // PasteEventAccessor

const GENERATED_ArkUIPasteEventAccessor* GetPasteEventAccessor()
{
    static const GENERATED_ArkUIPasteEventAccessor PasteEventAccessorImpl {
        PasteEventAccessor::DestroyPeerImpl,
        PasteEventAccessor::ConstructImpl,
        PasteEventAccessor::GetFinalizerImpl,
        PasteEventAccessor::PreventDefaultImpl,
    };
    return &PasteEventAccessorImpl;
}
}