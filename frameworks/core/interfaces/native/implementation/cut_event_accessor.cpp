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
#include "core/interfaces/native/implementation/cut_event_peer.h"
#include "core/interfaces/native/utility/peer_utils.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace CutEventAccessor {
void DestroyPeerImpl(Ark_CutEvent peer)
{
    PeerUtils::DestroyPeer(peer);
}
Ark_CutEvent ConstructImpl()
{
    return PeerUtils::CreatePeer<CutEventPeer>();
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
void PreventDefaultImpl(Ark_CutEvent peer)
{
    CHECK_NULL_VOID(peer);
    peer->HandlePreventDefault();
}
} // CutEventAccessor
const GENERATED_ArkUICutEventAccessor* GetCutEventAccessor()
{
    static const GENERATED_ArkUICutEventAccessor CutEventAccessorImpl {
        CutEventAccessor::DestroyPeerImpl,
        CutEventAccessor::ConstructImpl,
        CutEventAccessor::GetFinalizerImpl,
        CutEventAccessor::PreventDefaultImpl,
    };
    return &CutEventAccessorImpl;
}

}
