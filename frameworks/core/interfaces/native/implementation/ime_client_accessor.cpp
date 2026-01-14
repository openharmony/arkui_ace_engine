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

#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/interfaces/native/implementation/ime_client_peer.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace IMEClientAccessor {
void DestroyPeerImpl(Ark_IMEClient peer)
{
    PeerUtils::DestroyPeer(peer);
}
Ark_IMEClient ConstructImpl()
{
    return PeerUtils::CreatePeer<IMEClientPeer>();
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
void SetExtraConfigImpl(Ark_IMEClient peer,
                        const Ark_CustomObject* config)
{
}
Ark_Int64 GetNodeIdImpl(Ark_IMEClient peer)
{
    CHECK_NULL_RETURN(peer, -1);
    return peer->nodeId;
}
void SetNodeIdImpl(Ark_IMEClient peer,
                   Ark_Int64 nodeId)
{
    CHECK_NULL_VOID(peer);
    peer->nodeId = nodeId;
}
} // IMEClientAccessor
const GENERATED_ArkUIIMEClientAccessor* GetIMEClientAccessor()
{
    static const GENERATED_ArkUIIMEClientAccessor IMEClientAccessorImpl {
        IMEClientAccessor::DestroyPeerImpl,
        IMEClientAccessor::ConstructImpl,
        IMEClientAccessor::GetFinalizerImpl,
        IMEClientAccessor::SetExtraConfigImpl,
        IMEClientAccessor::GetNodeIdImpl,
        IMEClientAccessor::SetNodeIdImpl,
    };
    return &IMEClientAccessorImpl;
}

}
