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
#include "core/interfaces/native/implementation/copy_event_peer.h"
#include "core/interfaces/native/utility/peer_utils.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace CopyEventAccessor {
void DestroyPeerImpl(Ark_CopyEvent peer)
{
    PeerUtils::DestroyPeer(peer);
}

Ark_CopyEvent ConstructImpl()
{
    return PeerUtils::CreatePeer<CopyEventPeer>();
}

Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}

void PreventDefaultImpl(Ark_CopyEvent peer)
{
    CHECK_NULL_VOID(peer);
    peer->HandlePreventDefault();
}
} // CopyEventAccessor

const GENERATED_ArkUICopyEventAccessor* GetCopyEventAccessor()
{
    static const GENERATED_ArkUICopyEventAccessor CopyEventAccessorImpl {
        CopyEventAccessor::DestroyPeerImpl,
        CopyEventAccessor::ConstructImpl,
        CopyEventAccessor::GetFinalizerImpl,
        CopyEventAccessor::PreventDefaultImpl,
    };
    return &CopyEventAccessorImpl;
}
}