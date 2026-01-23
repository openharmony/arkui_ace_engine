/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/implementation/arc_swiper_controller_peer.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace ArcSwiperControllerHelperAccessor {
void DestroyPeerImpl(Ark_ArcSwiperControllerHelper peer)
{
    auto peerImpl = reinterpret_cast<ArcSwiperControllerHelperPeerImpl *>(peer);
    if (peerImpl) {
        peerImpl->DecRefCount();
    }
}
Ark_ArcSwiperControllerHelper ConstructImpl()
{
    auto peerImpl = Referenced::MakeRefPtr<ArcSwiperControllerHelperPeerImpl>();
    peerImpl->IncRefCount();
    return reinterpret_cast<ArcSwiperControllerHelperPeer *>(Referenced::RawPtr(peerImpl));
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
void ShowNextImpl(Ark_NativePointer node)
{
    auto peerImpl = reinterpret_cast<ArcSwiperControllerHelperPeerImpl *>(node);
    CHECK_NULL_VOID(peerImpl);
    peerImpl->TriggerShowNext();
}
void ShowPreviousImpl(Ark_NativePointer node)
{
    auto peerImpl = reinterpret_cast<ArcSwiperControllerHelperPeerImpl *>(node);
    CHECK_NULL_VOID(peerImpl);
    peerImpl->TriggerShowPrevious();
}
void FinishAnimationImpl(Ark_NativePointer node,
                         const Opt_VoidCallback* callback_)
{
    auto peerImpl = reinterpret_cast<ArcSwiperControllerHelperPeerImpl *>(node);
    CHECK_NULL_VOID(peerImpl);
    auto arkCallbackOpt = callback_ ? Converter::OptConvert<VoidCallback>(*callback_) : std::nullopt;
    if (arkCallbackOpt) {
        auto onFinish = [arkCallback = CallbackHelper(*arkCallbackOpt)]() -> void {
            arkCallback.InvokeSync();
        };
        peerImpl->SetFinishCallback(onFinish);
    }
    peerImpl->TriggerFinishAnimation();
}
} // ArcSwiperControllerHelperAccessor
const GENERATED_ArkUIArcSwiperControllerHelperAccessor* GetArcSwiperControllerHelperAccessor()
{
    static const GENERATED_ArkUIArcSwiperControllerHelperAccessor ArcSwiperControllerHelperAccessorImpl {
        ArcSwiperControllerHelperAccessor::DestroyPeerImpl,
        ArcSwiperControllerHelperAccessor::ConstructImpl,
        ArcSwiperControllerHelperAccessor::GetFinalizerImpl,
        ArcSwiperControllerHelperAccessor::ShowNextImpl,
        ArcSwiperControllerHelperAccessor::ShowPreviousImpl,
        ArcSwiperControllerHelperAccessor::FinishAnimationImpl,
    };
    return &ArcSwiperControllerHelperAccessorImpl;
}

}
