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

#include "core/interfaces/arkoala/implementation/swiper_content_transition_proxy_peer_impl.h"
#include "core/interfaces/arkoala/utility/converter.h"
#include "core/interfaces/arkoala/utility/reverse_converter.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace SwiperContentTransitionProxyAccessor {
static void DestroyPeer(SwiperContentTransitionProxyPeerImpl *peerImpl)
{
    if (peerImpl) {
        if (peerImpl->handler) {
            peerImpl->handler = nullptr;
        }
        delete peerImpl;
    }
}

Ark_NativePointer CtorImpl()
{
    return reinterpret_cast<Ark_NativePointer>(new SwiperContentTransitionProxyPeerImpl());
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<Ark_NativePointer>(&DestroyPeer);
}
void FinishTransitionImpl(SwiperContentTransitionProxyPeer* peer)
{
    auto peerImpl = reinterpret_cast<SwiperContentTransitionProxyPeerImpl *>(peer);
    if (peerImpl && peerImpl->handler) {
        peerImpl->handler->FinishTransition();
    }
}
Ark_Int32 GetSelectedIndexImpl(SwiperContentTransitionProxyPeer* peer)
{
    auto peerImpl = reinterpret_cast<SwiperContentTransitionProxyPeerImpl *>(peer);
    if (peerImpl && peerImpl->handler) {
        return Converter::ArkValue<Ark_Int32>(peerImpl->handler->GetSelectedIndex());
    }
    return 0;
}
void SetSelectedIndexImpl(SwiperContentTransitionProxyPeer* peer,
                          const Ark_Number* selectedIndex)
{
    auto peerImpl = reinterpret_cast<SwiperContentTransitionProxyPeerImpl *>(peer);
    if (peerImpl && peerImpl->handler) {
        if (selectedIndex) {
            peerImpl->handler->SetSelectedIndex(Converter::Convert<int32_t>(*selectedIndex));
        }
    }
}
Ark_Int32 GetIndexImpl(SwiperContentTransitionProxyPeer* peer)
{
    auto peerImpl = reinterpret_cast<SwiperContentTransitionProxyPeerImpl *>(peer);
    if (peerImpl && peerImpl->handler) {
        return Converter::ArkValue<Ark_Int32>(peerImpl->handler->GetIndex());
    }
    return 0;
}
void SetIndexImpl(SwiperContentTransitionProxyPeer* peer,
                  const Ark_Number* index)
{
    auto peerImpl = reinterpret_cast<SwiperContentTransitionProxyPeerImpl *>(peer);
    if (peerImpl && peerImpl->handler) {
        if (index) {
            peerImpl->handler->SetIndex(Converter::Convert<int32_t>(*index));
        }
    }
}
Ark_Int32 GetPositionImpl(SwiperContentTransitionProxyPeer* peer)
{
    auto peerImpl = reinterpret_cast<SwiperContentTransitionProxyPeerImpl *>(peer);
    if (peerImpl && peerImpl->handler) {
        return static_cast<Ark_Int32>(peerImpl->handler->GetPosition());
    }
    return 0;
}
void SetPositionImpl(SwiperContentTransitionProxyPeer* peer,
                     const Ark_Number* position)
{
    auto peerImpl = reinterpret_cast<SwiperContentTransitionProxyPeerImpl *>(peer);
    if (peerImpl && peerImpl->handler) {
        if (position) {
            peerImpl->handler->SetPosition(Converter::Convert<float>(*position));
        }
    }
}
Ark_Int32 GetMainAxisLengthImpl(SwiperContentTransitionProxyPeer* peer)
{
    auto peerImpl = reinterpret_cast<SwiperContentTransitionProxyPeerImpl *>(peer);
    if (peerImpl && peerImpl->handler) {
        return static_cast<Ark_Int32>(peerImpl->handler->GetMainAxisLength());
    }
    return 0;
}
void SetMainAxisLengthImpl(SwiperContentTransitionProxyPeer* peer,
                           const Ark_Number* mainAxisLength)
{
    auto peerImpl = reinterpret_cast<SwiperContentTransitionProxyPeerImpl *>(peer);
    if (peerImpl && peerImpl->handler) {
        if (mainAxisLength) {
            peerImpl->handler->SetMainAxisLength(Converter::Convert<float>(*mainAxisLength));
        }
    }
}
} // SwiperContentTransitionProxyAccessor
const GENERATED_ArkUISwiperContentTransitionProxyAccessor* GetSwiperContentTransitionProxyAccessor()
{
    static const GENERATED_ArkUISwiperContentTransitionProxyAccessor SwiperContentTransitionProxyAccessorImpl {
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
