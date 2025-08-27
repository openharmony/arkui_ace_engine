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

#include "core/interfaces/native/implementation/navigation_transition_proxy_peer.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/interfaces/native/utility/validators.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::Converter {
struct NavContentInfo {
    std::optional<std::string> name = "";
    int32_t index = -1;
    std::optional<NavDestinationMode> mode = NavDestinationMode::STANDARD;
    std::optional<void*> param = nullptr; // temp stub for CustomObject
    std::optional<std::string> navDestinationId = "";
};

template<>
inline void* Convert(const Ark_Object& src)
{
    return new NavigationTransitionProxyPeer();
}

template<>
NavContentInfo Convert(const Ark_NavContentInfo& src)
{
    NavContentInfo dst;
    dst.name = Converter::OptConvert<std::string>(src.name);
    dst.index = Converter::Convert<int32_t>(src.index);
    dst.mode = Converter::OptConvert<NavDestinationMode>(src.mode);
    dst.param = Converter::OptConvert<void*>(src.param);
    dst.navDestinationId = Converter::OptConvert<std::string>(src.navDestinationId);
    return dst;
}
}

namespace OHOS::Ace::NG::GeneratedModifier {
namespace NavigationTransitionProxyAccessor {
void DestroyPeerImpl(Ark_NavigationTransitionProxy peer)
{
    delete peer;
}
Ark_NavigationTransitionProxy CtorImpl()
{
    return new NavigationTransitionProxyPeer();
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
void FinishTransitionImpl(Ark_NavigationTransitionProxy peer)
{
    CHECK_NULL_VOID(peer && peer->handler);
    peer->handler->FireFinishCallback();
}
void CancelTransitionImpl(Ark_NavigationTransitionProxy peer)
{
    CHECK_NULL_VOID(peer && peer->handler);
    peer->handler->CancelInteractiveAnimation();
}
void UpdateTransitionImpl(Ark_NavigationTransitionProxy peer,
                          const Ark_Number* progress)
{
    CHECK_NULL_VOID(peer && progress && peer->handler);
    auto convProgress = Converter::OptConvert<float>(*progress);
    Validator::ValidateByRange(convProgress, 0.0f, 1.0f);
    if (convProgress.has_value()) {
        peer->handler->UpdateTransition(convProgress.value());
    }
}
Ark_NavContentInfo GetFromImpl(Ark_NavigationTransitionProxy peer)
{
    return {};
}
void SetFromImpl(Ark_NavigationTransitionProxy peer,
                 const Ark_NavContentInfo* from)
{
    CHECK_NULL_VOID(peer && from && peer->handler);
    Converter::Convert<Converter::NavContentInfo>(*from);
    LOGE("NavigationTransitionProxyAccessor::SetFromImpl, modifying from attribute isn't supported");
}
Ark_NavContentInfo GetToImpl(Ark_NavigationTransitionProxy peer)
{
    return {};
}
void SetToImpl(Ark_NavigationTransitionProxy peer,
               const Ark_NavContentInfo* to)
{
    CHECK_NULL_VOID(peer && to && peer->handler);
    Converter::Convert<Converter::NavContentInfo>(*to);
    LOGE("NavigationTransitionProxyAccessor::SetToImpl, modifying from attribute isn't supported");
}
Opt_Boolean GetIsInteractiveImpl(Ark_NavigationTransitionProxy peer)
{
    auto invalid = Converter::ArkValue<Opt_Boolean>();
    CHECK_NULL_RETURN(peer && peer->handler, invalid);
    return Converter::ArkValue<Opt_Boolean>(peer->handler->GetInteractive());
}
void SetIsInteractiveImpl(Ark_NavigationTransitionProxy peer,
                          Ark_Boolean isInteractive)
{
    CHECK_NULL_VOID(peer && peer->handler);
    peer->handler->SetInteractive(Converter::Convert<bool>(isInteractive));
}
} // NavigationTransitionProxyAccessor
const GENERATED_ArkUINavigationTransitionProxyAccessor* GetNavigationTransitionProxyAccessor()
{
    static const GENERATED_ArkUINavigationTransitionProxyAccessor NavigationTransitionProxyAccessorImpl {
        NavigationTransitionProxyAccessor::DestroyPeerImpl,
        NavigationTransitionProxyAccessor::CtorImpl,
        NavigationTransitionProxyAccessor::GetFinalizerImpl,
        NavigationTransitionProxyAccessor::FinishTransitionImpl,
        NavigationTransitionProxyAccessor::CancelTransitionImpl,
        NavigationTransitionProxyAccessor::UpdateTransitionImpl,
        NavigationTransitionProxyAccessor::GetFromImpl,
        NavigationTransitionProxyAccessor::SetFromImpl,
        NavigationTransitionProxyAccessor::GetToImpl,
        NavigationTransitionProxyAccessor::SetToImpl,
        NavigationTransitionProxyAccessor::GetIsInteractiveImpl,
        NavigationTransitionProxyAccessor::SetIsInteractiveImpl,
    };
    return &NavigationTransitionProxyAccessorImpl;
}

}
