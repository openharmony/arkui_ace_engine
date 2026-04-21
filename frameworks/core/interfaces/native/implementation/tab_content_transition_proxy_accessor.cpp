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
#include "core/interfaces/native/implementation/tab_content_transition_proxy_peer_impl.h"
#include "core/interfaces/native/utility/converter.h"
#include "arkoala_api_generated.h"

struct TabContentTransitionProxyPeer : public OHOS::Ace::NG::GeneratedModifier::TabContentTransitionProxyPeerImpl {};
namespace OHOS::Ace::NG::GeneratedModifier {
namespace TabContentTransitionProxyAccessor {
void DestroyPeerImpl(Ark_TabContentTransitionProxy peer)
{
    if (peer) {
        delete peer;
    }
}
Ark_TabContentTransitionProxy ConstructImpl()
{
    return new TabContentTransitionProxyPeer();
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
void FinishTransitionImpl(Ark_TabContentTransitionProxy peer)
{
    CHECK_NULL_VOID(peer);
    peer->FinishTransition();
}
Ark_Int32 GetFromImpl(Ark_TabContentTransitionProxy peer)
{
    CHECK_NULL_RETURN(peer, Converter::ArkValue<Ark_Int32>(0));
    auto idx = peer->GetFrom();
    return Converter::ArkValue<Ark_Int32>(idx);
}
void SetFromImpl(Ark_TabContentTransitionProxy peer,
                 Ark_Int32 from)
{
    CHECK_NULL_VOID(peer);
    int32_t idx = Converter::Convert<int32_t>(from);
    peer->SetFrom(idx);
}
Ark_Int32 GetToImpl(Ark_TabContentTransitionProxy peer)
{
    CHECK_NULL_RETURN(peer, Converter::ArkValue<Ark_Int32>(0));
    auto idx = peer->GetTo();
    return Converter::ArkValue<Ark_Int32>(idx);
}
void SetToImpl(Ark_TabContentTransitionProxy peer,
               Ark_Int32 to)
{
    CHECK_NULL_VOID(peer);
    int32_t idx = Converter::Convert<int32_t>(to);
    peer->SetTo(idx);
}
} // TabContentTransitionProxyAccessor
const GENERATED_ArkUITabContentTransitionProxyAccessor* GetTabContentTransitionProxyAccessor()
{
    static const GENERATED_ArkUITabContentTransitionProxyAccessor TabContentTransitionProxyAccessorImpl {
        TabContentTransitionProxyAccessor::DestroyPeerImpl,
        TabContentTransitionProxyAccessor::ConstructImpl,
        TabContentTransitionProxyAccessor::GetFinalizerImpl,
        TabContentTransitionProxyAccessor::FinishTransitionImpl,
        TabContentTransitionProxyAccessor::GetFromImpl,
        TabContentTransitionProxyAccessor::SetFromImpl,
        TabContentTransitionProxyAccessor::GetToImpl,
        TabContentTransitionProxyAccessor::SetToImpl,
    };
    return &TabContentTransitionProxyAccessorImpl;
}

}
