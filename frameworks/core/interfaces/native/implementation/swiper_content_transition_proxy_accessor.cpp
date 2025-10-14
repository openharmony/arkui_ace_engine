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
Ark_SwiperContentTransitionProxy ConstructImpl()
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
Ark_Int32 GetSelectedIndexImpl(Ark_SwiperContentTransitionProxy peer)
{
    const auto errValue = Converter::ArkValue<Ark_Int32>(0);
    CHECK_NULL_RETURN(peer && peer->handler, errValue);
    return Converter::ArkValue<Ark_Int32>(peer->handler->GetSelectedIndex());
}
void SetSelectedIndexImpl(Ark_SwiperContentTransitionProxy peer,
                          Ark_Int32 selectedIndex)
{
    CHECK_NULL_VOID(peer && peer->handler);
    peer->handler->SetSelectedIndex(Converter::Convert<int32_t>(selectedIndex));
}
Ark_Int32 GetIndexImpl(Ark_SwiperContentTransitionProxy peer)
{
    const auto errValue = Converter::ArkValue<Ark_Int32>(0);
    CHECK_NULL_RETURN(peer && peer->handler, errValue);
    return Converter::ArkValue<Ark_Int32>(peer->handler->GetIndex());
}
void SetIndexImpl(Ark_SwiperContentTransitionProxy peer,
                  Ark_Int32 index)
{
    CHECK_NULL_VOID(peer && peer->handler);
    peer->handler->SetIndex(Converter::Convert<float>(index));
}
Ark_Float64 GetPositionImpl(Ark_SwiperContentTransitionProxy peer)
{
    const auto errValue = Converter::ArkValue<Ark_Float64>(0);
    CHECK_NULL_RETURN(peer && peer->handler, errValue);
    return Converter::ArkValue<Ark_Float64>(peer->handler->GetPosition());
}
void SetPositionImpl(Ark_SwiperContentTransitionProxy peer,
                     Ark_Float64 position)
{
    CHECK_NULL_VOID(peer && peer->handler);
    peer->handler->SetPosition(Converter::Convert<float>(position));
}
Ark_Float64 GetMainAxisLengthImpl(Ark_SwiperContentTransitionProxy peer)
{
    const auto errValue = Converter::ArkValue<Ark_Float64>(0);
    CHECK_NULL_RETURN(peer && peer->handler, errValue);
    return Converter::ArkValue<Ark_Float64>(peer->handler->GetMainAxisLength());
}
void SetMainAxisLengthImpl(Ark_SwiperContentTransitionProxy peer,
                           Ark_Float64 mainAxisLength)
{
    CHECK_NULL_VOID(peer && peer->handler);
    peer->handler->SetMainAxisLength(Converter::Convert<float>(mainAxisLength));
}
} // SwiperContentTransitionProxyAccessor
const GENERATED_ArkUISwiperContentTransitionProxyAccessor* GetSwiperContentTransitionProxyAccessor()
{
    static const GENERATED_ArkUISwiperContentTransitionProxyAccessor SwiperContentTransitionProxyAccessorImpl {
        SwiperContentTransitionProxyAccessor::DestroyPeerImpl,
        SwiperContentTransitionProxyAccessor::ConstructImpl,
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
