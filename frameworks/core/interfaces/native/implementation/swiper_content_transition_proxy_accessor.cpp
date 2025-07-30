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

#include "core/interfaces/native/implementation/swiper_content_transition_proxy_peer.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace SwiperContentTransitionProxyAccessor {
void DestroyPeerImpl(Ark_SwiperContentTransitionProxy peer)
{
    delete peer;
}
Ark_SwiperContentTransitionProxy CtorImpl()
{
    return new SwiperContentTransitionProxyPeer();
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
void FinishTransitionImpl(Ark_SwiperContentTransitionProxy peer)
{
    CHECK_NULL_VOID(peer && peer->handler);
    peer->handler->FinishTransition();
}
Ark_Number GetSelectedIndexImpl(Ark_SwiperContentTransitionProxy peer)
{
    const auto errValue = Converter::ArkValue<Ark_Number>(0);
    CHECK_NULL_RETURN(peer && peer->handler, errValue);
    return Converter::ArkValue<Ark_Number>(peer->handler->GetSelectedIndex());
}
void SetSelectedIndexImpl(Ark_SwiperContentTransitionProxy peer,
                          const Ark_Number* selectedIndex)
{
    CHECK_NULL_VOID(peer && peer->handler);
    CHECK_NULL_VOID(selectedIndex);
    peer->handler->SetSelectedIndex(Converter::Convert<int32_t>(*selectedIndex));
}
Ark_Number GetIndexImpl(Ark_SwiperContentTransitionProxy peer)
{
    const auto errValue = Converter::ArkValue<Ark_Number>(0);
    CHECK_NULL_RETURN(peer && peer->handler, errValue);
    return Converter::ArkValue<Ark_Number>(peer->handler->GetIndex());
}
void SetIndexImpl(Ark_SwiperContentTransitionProxy peer,
                  const Ark_Number* index)
{
    CHECK_NULL_VOID(peer && peer->handler);
    CHECK_NULL_VOID(index);
    peer->handler->SetIndex(Converter::Convert<float>(*index));
}
Ark_Number GetPositionImpl(Ark_SwiperContentTransitionProxy peer)
{
    const auto errValue = Converter::ArkValue<Ark_Number>(0);
    CHECK_NULL_RETURN(peer && peer->handler, errValue);
    return Converter::ArkValue<Ark_Number>(peer->handler->GetPosition());
}
void SetPositionImpl(Ark_SwiperContentTransitionProxy peer,
                     const Ark_Number* position)
{
    CHECK_NULL_VOID(peer && peer->handler);
    CHECK_NULL_VOID(position);
    peer->handler->SetPosition(Converter::Convert<float>(*position));
}
Ark_Number GetMainAxisLengthImpl(Ark_SwiperContentTransitionProxy peer)
{
    const auto errValue = Converter::ArkValue<Ark_Number>(0);
    CHECK_NULL_RETURN(peer && peer->handler, errValue);
    return Converter::ArkValue<Ark_Number>(peer->handler->GetMainAxisLength());
}
void SetMainAxisLengthImpl(Ark_SwiperContentTransitionProxy peer,
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
