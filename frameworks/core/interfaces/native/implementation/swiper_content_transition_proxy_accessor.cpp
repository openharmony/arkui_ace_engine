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

#include "core/interfaces/native/implementation/swiper_content_transition_proxy_peer.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace SwiperContentTransitionProxyAccessor {
void DestroyPeerImpl(SwiperContentTransitionProxyPeer* peer)
{
    CHECK_NULL_VOID(peer);
    peer->handler = nullptr;
    delete peer;
}
SwiperContentTransitionProxyPeer* CtorImpl()
{
    return new SwiperContentTransitionProxyPeer();
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
void FinishTransitionImpl(SwiperContentTransitionProxyPeer* peer)
{
    CHECK_NULL_VOID(peer && peer->handler);
    peer->handler->FinishTransition();
}
Ark_Int32 GetSelectedIndexImpl(SwiperContentTransitionProxyPeer* peer)
{
    CHECK_NULL_RETURN(peer && peer->handler, 0);
    return Converter::ArkValue<Ark_Int32>(peer->handler->GetSelectedIndex());
}
void SetSelectedIndexImpl(SwiperContentTransitionProxyPeer* peer,
                          const Ark_Number* selectedIndex)
{
    CHECK_NULL_VOID(peer && peer->handler);
    CHECK_NULL_VOID(selectedIndex);
    peer->handler->SetSelectedIndex(Converter::Convert<int32_t>(*selectedIndex));
}
Ark_Int32 GetIndexImpl(SwiperContentTransitionProxyPeer* peer)
{
    CHECK_NULL_RETURN(peer && peer->handler, 0);
    return Converter::ArkValue<Ark_Int32>(peer->handler->GetIndex());
}
void SetIndexImpl(SwiperContentTransitionProxyPeer* peer,
                  const Ark_Number* index)
{
    CHECK_NULL_VOID(peer && peer->handler);
    CHECK_NULL_VOID(index);
    peer->handler->SetIndex(Converter::Convert<int32_t>(*index));
}
Ark_Int32 GetPositionImpl(SwiperContentTransitionProxyPeer* peer)
{
    CHECK_NULL_RETURN(peer && peer->handler, 0);
    return static_cast<Ark_Int32>(peer->handler->GetPosition());
}
void SetPositionImpl(SwiperContentTransitionProxyPeer* peer,
                     const Ark_Number* position)
{
    CHECK_NULL_VOID(peer && peer->handler);
    CHECK_NULL_VOID(position);
    peer->handler->SetPosition(Converter::Convert<float>(*position));
}
Ark_Int32 GetMainAxisLengthImpl(SwiperContentTransitionProxyPeer* peer)
{
    CHECK_NULL_RETURN(peer && peer->handler, 0);
    return static_cast<Ark_Int32>(peer->handler->GetMainAxisLength());
}
void SetMainAxisLengthImpl(SwiperContentTransitionProxyPeer* peer,
                           const Ark_Number* mainAxisLength)
{
    CHECK_NULL_VOID(peer && peer->handler);
    CHECK_NULL_VOID(mainAxisLength);
    peer->handler->SetMainAxisLength(Converter::Convert<float>(*mainAxisLength));
}
} // SwiperContentTransitionProxyAccessor
const GENERATED_ArkUISwiperContentTransitionProxyAccessor* GetSwiperContentTransitionProxyAccessor()
{
    static const GENERATED_ArkUISwiperContentTransitionProxyAccessor SwiperContentTransitionProxyAccessorImpl {
        SwiperContentTransitionProxyAccessor::DestroyPeerImpl,
        SwiperContentTransitionProxyAccessor::CtorImpl,
        SwiperContentTransitionProxyAccessor::GetFinalizerImpl,
        SwiperContentTransitionProxyAccessor::FinishTransitionImpl,
        SwiperContentTransitionProxyAccessor::GetSelectedIndexImpl,
        SwiperContentTransitionProxyAccessor::SetSelectedIndexImpl,
        SwiperContentTransitionProxyAccessor::GetIndexImpl,
        SwiperContentTransitionProxyAccessor::SetIndexImpl,
        SwiperContentTransitionProxyAccessor::GetPositionImpl,
        SwiperContentTransitionProxyAccessor::SetPositionImpl,
        SwiperContentTransitionProxyAccessor::GetMainAxisLengthImpl,
        SwiperContentTransitionProxyAccessor::SetMainAxisLengthImpl,
    };
    return &SwiperContentTransitionProxyAccessorImpl;
}

}
