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
#include "core/interfaces/native/implementation/event_location_info_peer.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace EventLocationInfoAccessor {
void DestroyPeerImpl(Ark_EventLocationInfo peer)
{
    PeerUtils::DestroyPeer(peer);
}
Ark_EventLocationInfo ConstructImpl()
{
    return PeerUtils::CreatePeer<EventLocationInfoPeer>();
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Ark_Coordinate2D GetCurrentLocalPositionImpl(Ark_EventLocationInfo peer)
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
Ark_Float64 GetXImpl(Ark_EventLocationInfo peer)
{
    const auto errValue = Converter::ArkValue<Ark_Float64>(0);
    CHECK_NULL_RETURN(peer, errValue);
    const auto* info = peer->GetEventInfo();
    CHECK_NULL_RETURN(info, errValue);
    return Converter::ArkValue<Ark_Float64>(PipelineBase::Px2VpWithCurrentDensity(info->localLocation_.GetX()));
}
void SetXImpl(Ark_EventLocationInfo peer,
              Ark_Float64 x)
{
}
Ark_Float64 GetYImpl(Ark_EventLocationInfo peer)
{
    const auto errValue = Converter::ArkValue<Ark_Float64>(0);
    CHECK_NULL_RETURN(peer, errValue);
    const auto* info = peer->GetEventInfo();
    CHECK_NULL_RETURN(info, errValue);
    return Converter::ArkValue<Ark_Float64>(PipelineBase::Px2VpWithCurrentDensity(info->localLocation_.GetY()));
}
void SetYImpl(Ark_EventLocationInfo peer,
              Ark_Float64 y)
{
}
Ark_Float64 GetWindowXImpl(Ark_EventLocationInfo peer)
{
    const auto errValue = Converter::ArkValue<Ark_Float64>(0);
    CHECK_NULL_RETURN(peer, errValue);
    const auto* info = peer->GetEventInfo();
    CHECK_NULL_RETURN(info, errValue);
    return Converter::ArkValue<Ark_Float64>(PipelineBase::Px2VpWithCurrentDensity(info->globalLocation_.GetX()));
}
void SetWindowXImpl(Ark_EventLocationInfo peer,
                    Ark_Float64 windowX)
{
}
Ark_Float64 GetWindowYImpl(Ark_EventLocationInfo peer)
{
    const auto errValue = Converter::ArkValue<Ark_Float64>(0);
    CHECK_NULL_RETURN(peer, errValue);
    const auto* info = peer->GetEventInfo();
    CHECK_NULL_RETURN(info, errValue);
    return Converter::ArkValue<Ark_Float64>(PipelineBase::Px2VpWithCurrentDensity(info->globalLocation_.GetY()));
}
void SetWindowYImpl(Ark_EventLocationInfo peer,
                    Ark_Float64 windowY)
{
}
Ark_Float64 GetDisplayXImpl(Ark_EventLocationInfo peer)
{
    const auto errValue = Converter::ArkValue<Ark_Float64>(0);
    CHECK_NULL_RETURN(peer, errValue);
    const auto* info = peer->GetEventInfo();
    CHECK_NULL_RETURN(info, errValue);
    return Converter::ArkValue<Ark_Float64>(PipelineBase::Px2VpWithCurrentDensity(info->screenLocation_.GetX()));
}
void SetDisplayXImpl(Ark_EventLocationInfo peer,
                     Ark_Float64 displayX)
{
}
Ark_Float64 GetDisplayYImpl(Ark_EventLocationInfo peer)
{
    const auto errValue = Converter::ArkValue<Ark_Float64>(0);
    CHECK_NULL_RETURN(peer, errValue);
    const auto* info = peer->GetEventInfo();
    CHECK_NULL_RETURN(info, errValue);
    return Converter::ArkValue<Ark_Float64>(PipelineBase::Px2VpWithCurrentDensity(info->screenLocation_.GetY()));
}
void SetDisplayYImpl(Ark_EventLocationInfo peer,
                     Ark_Float64 displayY)
{
}
Opt_Float64 GetGlobalDisplayXImpl(Ark_EventLocationInfo peer)
{
    const auto errValue = Converter::ArkValue<Opt_Float64>();
    CHECK_NULL_RETURN(peer, errValue);
    const auto* info = peer->GetEventInfo();
    CHECK_NULL_RETURN(info, errValue);
    return Converter::ArkValue<Opt_Float64>(PipelineBase::Px2VpWithCurrentDensity(info->globalDisplayLocation_.GetX()));
}
void SetGlobalDisplayXImpl(Ark_EventLocationInfo peer,
                           const Opt_Float64* globalDisplayX)
{
}
Opt_Float64 GetGlobalDisplayYImpl(Ark_EventLocationInfo peer)
{
    const auto errValue = Converter::ArkValue<Opt_Float64>();
    CHECK_NULL_RETURN(peer, errValue);
    const auto* info = peer->GetEventInfo();
    CHECK_NULL_RETURN(info, errValue);
    return Converter::ArkValue<Opt_Float64>(PipelineBase::Px2VpWithCurrentDensity(info->globalDisplayLocation_.GetY()));
}
void SetGlobalDisplayYImpl(Ark_EventLocationInfo peer,
                           const Opt_Float64* globalDisplayY)
{
}
} // EventLocationInfoAccessor
const GENERATED_ArkUIEventLocationInfoAccessor* GetEventLocationInfoAccessor()
{
    static const GENERATED_ArkUIEventLocationInfoAccessor EventLocationInfoAccessorImpl {
        EventLocationInfoAccessor::DestroyPeerImpl,
        EventLocationInfoAccessor::ConstructImpl,
        EventLocationInfoAccessor::GetFinalizerImpl,
        EventLocationInfoAccessor::GetCurrentLocalPositionImpl,
        EventLocationInfoAccessor::GetXImpl,
        EventLocationInfoAccessor::SetXImpl,
        EventLocationInfoAccessor::GetYImpl,
        EventLocationInfoAccessor::SetYImpl,
        EventLocationInfoAccessor::GetWindowXImpl,
        EventLocationInfoAccessor::SetWindowXImpl,
        EventLocationInfoAccessor::GetWindowYImpl,
        EventLocationInfoAccessor::SetWindowYImpl,
        EventLocationInfoAccessor::GetDisplayXImpl,
        EventLocationInfoAccessor::SetDisplayXImpl,
        EventLocationInfoAccessor::GetDisplayYImpl,
        EventLocationInfoAccessor::SetDisplayYImpl,
        EventLocationInfoAccessor::GetGlobalDisplayXImpl,
        EventLocationInfoAccessor::SetGlobalDisplayXImpl,
        EventLocationInfoAccessor::GetGlobalDisplayYImpl,
        EventLocationInfoAccessor::SetGlobalDisplayYImpl,
    };
    return &EventLocationInfoAccessorImpl;
}

}
