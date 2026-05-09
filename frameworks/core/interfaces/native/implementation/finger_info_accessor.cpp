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

#include "core/components_ng/base/frame_node.h"
#include "core/interfaces/native/implementation/finger_info_peer.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace FingerInfoAccessor {
void DestroyPeerImpl(Ark_FingerInfo peer)
{
    PeerUtils::DestroyPeer(peer);
}
Ark_FingerInfo ConstructImpl()
{
    return PeerUtils::CreatePeer<FingerInfoPeer>();
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Ark_Coordinate2D GetCurrentLocalPositionImpl(Ark_FingerInfo peer)
{
    const auto errValue = Converter::ArkValue<Ark_Coordinate2D>(Offset{});
    CHECK_NULL_RETURN(peer, errValue);
    const auto* info = peer->GetEventInfo();
    CHECK_NULL_RETURN(info, errValue);
    const auto localLocation = info->currentLocalLocation_ ? info->currentLocalLocation_() : info->localLocation_;
    const auto x = PipelineBase::Px2VpWithCurrentDensity(localLocation.GetX());
    const auto y = PipelineBase::Px2VpWithCurrentDensity(localLocation.GetY());
    return Converter::ArkValue<Ark_Coordinate2D>(Offset{x, y});
}
Ark_Int32 GetIdImpl(Ark_FingerInfo peer)
{
    const auto errValue = Converter::ArkValue<Ark_Int32>(0);
    CHECK_NULL_RETURN(peer, errValue);
    auto info = peer->GetEventInfo();
    CHECK_NULL_RETURN(info, errValue);
    return Converter::ArkValue<Ark_Int32>(info->fingerId_);
}
void SetIdImpl(Ark_FingerInfo peer,
               Ark_Int32 id)
{
}
Opt_Float64 GetGlobalDisplayXImpl(Ark_FingerInfo peer)
{
    const auto errValue = Converter::ArkValue<Opt_Float64>(0);
    CHECK_NULL_RETURN(peer, errValue);
    auto info = peer->GetEventInfo();
    CHECK_NULL_RETURN(info, errValue);
    return Converter::ArkValue<Opt_Float64>(PipelineBase::Px2VpWithCurrentDensity(info->globalDisplayLocation_.GetX()));
}
void SetGlobalDisplayXImpl(Ark_FingerInfo peer,
                           const Opt_Float64* globalDisplayX)
{
}
Opt_Float64 GetGlobalDisplayYImpl(Ark_FingerInfo peer)
{
    const auto errValue = Converter::ArkValue<Opt_Float64>();
    CHECK_NULL_RETURN(peer, errValue);
    auto info = peer->GetEventInfo();
    CHECK_NULL_RETURN(info, errValue);
    return Converter::ArkValue<Opt_Float64>(PipelineBase::Px2VpWithCurrentDensity(info->globalDisplayLocation_.GetY()));
}
void SetGlobalDisplayYImpl(Ark_FingerInfo peer,
                           const Opt_Float64* globalDisplayY)
{
}
Ark_Float64 GetGlobalXImpl(Ark_FingerInfo peer)
{
    const auto errValue = Converter::ArkValue<Ark_Float64>(0);
    CHECK_NULL_RETURN(peer, errValue);
    auto info = peer->GetEventInfo();
    CHECK_NULL_RETURN(info, errValue);
    return Converter::ArkValue<Ark_Float64>(PipelineBase::Px2VpWithCurrentDensity(info->globalLocation_.GetX()));
}
void SetGlobalXImpl(Ark_FingerInfo peer,
                    Ark_Float64 globalX)
{
}
Ark_Float64 GetGlobalYImpl(Ark_FingerInfo peer)
{
    const auto errValue = Converter::ArkValue<Ark_Float64>(0);
    CHECK_NULL_RETURN(peer, errValue);
    auto info = peer->GetEventInfo();
    CHECK_NULL_RETURN(info, errValue);
    return Converter::ArkValue<Ark_Float64>(PipelineBase::Px2VpWithCurrentDensity(info->globalLocation_.GetY()));
}
void SetGlobalYImpl(Ark_FingerInfo peer,
                    Ark_Float64 globalY)
{
}
Ark_Float64 GetLocalXImpl(Ark_FingerInfo peer)
{
    const auto errValue = Converter::ArkValue<Ark_Float64>(0);
    CHECK_NULL_RETURN(peer, errValue);
    auto info = peer->GetEventInfo();
    CHECK_NULL_RETURN(info, errValue);
    return Converter::ArkValue<Ark_Float64>(PipelineBase::Px2VpWithCurrentDensity(info->localLocation_.GetX()));
}
void SetLocalXImpl(Ark_FingerInfo peer,
                   Ark_Float64 localX)
{
}
Ark_Float64 GetLocalYImpl(Ark_FingerInfo peer)
{
    const auto errValue = Converter::ArkValue<Ark_Float64>(0);
    CHECK_NULL_RETURN(peer, errValue);
    auto info = peer->GetEventInfo();
    CHECK_NULL_RETURN(info, errValue);
    return Converter::ArkValue<Ark_Float64>(PipelineBase::Px2VpWithCurrentDensity(info->localLocation_.GetY()));
}
void SetLocalYImpl(Ark_FingerInfo peer,
                   Ark_Float64 localY)
{
}
Ark_Float64 GetDisplayXImpl(Ark_FingerInfo peer)
{
    const auto errValue = Converter::ArkValue<Ark_Float64>(0);
    CHECK_NULL_RETURN(peer, errValue);
    auto info = peer->GetEventInfo();
    CHECK_NULL_RETURN(info, errValue);
    return Converter::ArkValue<Ark_Float64>(PipelineBase::Px2VpWithCurrentDensity(info->screenLocation_.GetX()));
}
void SetDisplayXImpl(Ark_FingerInfo peer,
                     Ark_Float64 displayX)
{
}
Ark_Float64 GetDisplayYImpl(Ark_FingerInfo peer)
{
    const auto errValue = Converter::ArkValue<Ark_Float64>(0);
    CHECK_NULL_RETURN(peer, errValue);
    auto info = peer->GetEventInfo();
    CHECK_NULL_RETURN(info, errValue);
    return Converter::ArkValue<Ark_Float64>(PipelineBase::Px2VpWithCurrentDensity(info->screenLocation_.GetY()));
}
void SetDisplayYImpl(Ark_FingerInfo peer,
                     Ark_Float64 displayY)
{
}
Opt_InteractionHand GetHandImpl(Ark_FingerInfo peer)
{
    auto errValue = Converter::ArkValue<Opt_InteractionHand>();
    CHECK_NULL_RETURN(peer, errValue);
    auto info = peer->GetEventInfo();
    CHECK_NULL_RETURN(info, errValue);
    return Converter::ArkValue<Opt_InteractionHand>(static_cast<ArkUI_InteractionHand>(info->operatingHand_));
}
void SetHandImpl(Ark_FingerInfo peer,
                 const Opt_InteractionHand* hand)
{
}
} // FingerInfoAccessor
const GENERATED_ArkUIFingerInfoAccessor* GetFingerInfoAccessor()
{
    static const GENERATED_ArkUIFingerInfoAccessor FingerInfoAccessorImpl {
        FingerInfoAccessor::DestroyPeerImpl,
        FingerInfoAccessor::ConstructImpl,
        FingerInfoAccessor::GetFinalizerImpl,
        FingerInfoAccessor::GetCurrentLocalPositionImpl,
        FingerInfoAccessor::GetIdImpl,
        FingerInfoAccessor::SetIdImpl,
        FingerInfoAccessor::GetGlobalDisplayXImpl,
        FingerInfoAccessor::SetGlobalDisplayXImpl,
        FingerInfoAccessor::GetGlobalDisplayYImpl,
        FingerInfoAccessor::SetGlobalDisplayYImpl,
        FingerInfoAccessor::GetGlobalXImpl,
        FingerInfoAccessor::SetGlobalXImpl,
        FingerInfoAccessor::GetGlobalYImpl,
        FingerInfoAccessor::SetGlobalYImpl,
        FingerInfoAccessor::GetLocalXImpl,
        FingerInfoAccessor::SetLocalXImpl,
        FingerInfoAccessor::GetLocalYImpl,
        FingerInfoAccessor::SetLocalYImpl,
        FingerInfoAccessor::GetDisplayXImpl,
        FingerInfoAccessor::SetDisplayXImpl,
        FingerInfoAccessor::GetDisplayYImpl,
        FingerInfoAccessor::SetDisplayYImpl,
        FingerInfoAccessor::GetHandImpl,
        FingerInfoAccessor::SetHandImpl,
    };
    return &FingerInfoAccessorImpl;
}

struct FingerInfoPeer {
    virtual ~FingerInfoPeer() = default;
};
}
