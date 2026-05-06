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

#include "arkoala_api_generated.h"
#include "core/interfaces/native/implementation/touch_object_peer.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "ui/event/touch_event.h"
#include "core/components_ng/base/frame_node.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace TouchObjectAccessor {
void DestroyPeerImpl(Ark_TouchObject peer)
{
    PeerUtils::DestroyPeer(peer);
}
Ark_TouchObject ConstructImpl()
{
    return PeerUtils::CreatePeer<TouchObjectPeer>();
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Ark_Coordinate2D GetCurrentLocalPositionImpl(Ark_TouchObject peer)
{
    const auto errValue = Converter::ArkValue<Ark_Coordinate2D>(Offset{});
    CHECK_NULL_RETURN(peer, errValue);
    const auto* info = peer->GetEventInfo();
    CHECK_NULL_RETURN(info, errValue);
    const auto& localLocation = info->GetCurrentLocalLocation();
    const auto x = PipelineBase::Px2VpWithCurrentDensity(localLocation.GetX());
    const auto y = PipelineBase::Px2VpWithCurrentDensity(localLocation.GetY());
    return Converter::ArkValue<Ark_Coordinate2D>(Offset{x, y});
}
Ark_TouchType GetTypeImpl(Ark_TouchObject peer)
{
    const auto errValue = Converter::ArkValue<Ark_TouchType>(TouchType::UNKNOWN);
    CHECK_NULL_RETURN(peer, errValue);
    TouchLocationInfo* info = peer->GetEventInfo();
    CHECK_NULL_RETURN(info, errValue);
    return Converter::ArkValue<Ark_TouchType>(info->GetTouchType());
}
void SetTypeImpl(Ark_TouchObject peer,
                 Ark_TouchType type)
{
}
Ark_Int32 GetIdImpl(Ark_TouchObject peer)
{
    const auto errValue = Converter::ArkValue<Ark_Int32>(-1);
    CHECK_NULL_RETURN(peer, errValue);
    TouchLocationInfo* info = peer->GetEventInfo();
    CHECK_NULL_RETURN(info, errValue);
    return Converter::ArkValue<Ark_Int32>(info->GetFingerId());
}
void SetIdImpl(Ark_TouchObject peer,
               Ark_Int32 id)
{
}
Ark_Float64 GetDisplayXImpl(Ark_TouchObject peer)
{
    const auto errValue = Converter::ArkValue<Ark_Float64>(0);
    CHECK_NULL_RETURN(peer, errValue);
    TouchLocationInfo* info = peer->GetEventInfo();
    CHECK_NULL_RETURN(info, errValue);
    Offset screenOffset = info->GetScreenLocation();
    return Converter::ArkValue<Ark_Float64>(PipelineBase::Px2VpWithCurrentDensity(screenOffset.GetX()));
}
void SetDisplayXImpl(Ark_TouchObject peer,
                     Ark_Float64 displayX)
{
    CHECK_NULL_VOID(peer);
    auto* info = peer->GetEventInfo();
    CHECK_NULL_VOID(info);
    auto screenOffset = info->GetScreenLocation();
    screenOffset.SetX(displayX);
    info->SetScreenLocation(screenOffset);
}
Ark_Float64 GetDisplayYImpl(Ark_TouchObject peer)
{
    const auto errValue = Converter::ArkValue<Ark_Float64>(0);
    CHECK_NULL_RETURN(peer, errValue);
    TouchLocationInfo* info = peer->GetEventInfo();
    CHECK_NULL_RETURN(info, errValue);
    Offset screenOffset = info->GetScreenLocation();
    return Converter::ArkValue<Ark_Float64>(PipelineBase::Px2VpWithCurrentDensity(screenOffset.GetY()));
}
void SetDisplayYImpl(Ark_TouchObject peer,
                     Ark_Float64 displayY)
{
    CHECK_NULL_VOID(peer);
    auto* info = peer->GetEventInfo();
    CHECK_NULL_VOID(info);
    auto screenOffset = info->GetScreenLocation();
    screenOffset.SetY(displayY);
    info->SetScreenLocation(screenOffset);
}
Ark_Float64 GetWindowXImpl(Ark_TouchObject peer)
{
    const auto errValue = Converter::ArkValue<Ark_Float64>(0);
    CHECK_NULL_RETURN(peer, errValue);
    TouchLocationInfo* info = peer->GetEventInfo();
    CHECK_NULL_RETURN(info, errValue);
    Offset globalOffset = info->GetGlobalLocation();
    return Converter::ArkValue<Ark_Float64>(PipelineBase::Px2VpWithCurrentDensity(globalOffset.GetX()));
}
void SetWindowXImpl(Ark_TouchObject peer,
                    Ark_Float64 windowX)
{
    CHECK_NULL_VOID(peer);
    auto* info = peer->GetEventInfo();
    CHECK_NULL_VOID(info);
    auto globalOffset = info->GetGlobalLocation();
    globalOffset.SetX(windowX);
    info->SetGlobalLocation(globalOffset);
}
Ark_Float64 GetWindowYImpl(Ark_TouchObject peer)
{
    const auto errValue = Converter::ArkValue<Ark_Float64>(0);
    CHECK_NULL_RETURN(peer, errValue);
    TouchLocationInfo* info = peer->GetEventInfo();
    CHECK_NULL_RETURN(info, errValue);
    Offset globalOffset = info->GetGlobalLocation();
    return Converter::ArkValue<Ark_Float64>(PipelineBase::Px2VpWithCurrentDensity(globalOffset.GetY()));
}
void SetWindowYImpl(Ark_TouchObject peer,
                    Ark_Float64 windowY)
{
    CHECK_NULL_VOID(peer);
    auto* info = peer->GetEventInfo();
    CHECK_NULL_VOID(info);
    auto globalOffset = info->GetGlobalLocation();
    globalOffset.SetY(windowY);
    info->SetGlobalLocation(globalOffset);
}
Ark_Float64 GetXImpl(Ark_TouchObject peer)
{
    const auto errValue = Converter::ArkValue<Ark_Float64>(0);
    CHECK_NULL_RETURN(peer, errValue);
    TouchLocationInfo* info = peer->GetEventInfo();
    CHECK_NULL_RETURN(info, errValue);
    Offset localOffset = info->GetLocalLocation();
    return Converter::ArkValue<Ark_Float64>(PipelineBase::Px2VpWithCurrentDensity(localOffset.GetX()));
}
void SetXImpl(Ark_TouchObject peer,
              Ark_Float64 x)
{
    CHECK_NULL_VOID(peer);
    auto* info = peer->GetEventInfo();
    CHECK_NULL_VOID(info);
    auto localOffset = info->GetLocalLocation();
    localOffset.SetX(x);
    info->SetLocalLocation(localOffset);
}
Ark_Float64 GetYImpl(Ark_TouchObject peer)
{
    const auto errValue = Converter::ArkValue<Ark_Float64>(0);
    CHECK_NULL_RETURN(peer, errValue);
    TouchLocationInfo* info = peer->GetEventInfo();
    CHECK_NULL_RETURN(info, errValue);
    Offset localOffset = info->GetLocalLocation();
    return Converter::ArkValue<Ark_Float64>(PipelineBase::Px2VpWithCurrentDensity(localOffset.GetY()));
}
void SetYImpl(Ark_TouchObject peer,
              Ark_Float64 y)
{
    CHECK_NULL_VOID(peer);
    auto* info = peer->GetEventInfo();
    CHECK_NULL_VOID(info);
    auto localOffset = info->GetLocalLocation();
    localOffset.SetY(y);
    info->SetLocalLocation(localOffset);
}
Opt_InteractionHand GetHandImpl(Ark_TouchObject peer)
{
    auto errValue = Converter::ArkValue<Opt_InteractionHand>();
    CHECK_NULL_RETURN(peer, errValue);
    TouchLocationInfo* info = peer->GetEventInfo();
    CHECK_NULL_RETURN(info, errValue);
    return Converter::ArkValue<Opt_InteractionHand>(static_cast<ArkUI_InteractionHand>(info->GetOperatingHand()));
}
void SetHandImpl(Ark_TouchObject peer,
                 const Opt_InteractionHand* hand)
{
}
Opt_Int64 GetPressedTimeImpl(Ark_TouchObject peer)
{
    auto errValue = Converter::ArkValue<Opt_Int64>();
    CHECK_NULL_RETURN(peer, errValue);
    TouchLocationInfo* info = peer->GetEventInfo();
    CHECK_NULL_RETURN(info, errValue);
    return Converter::ArkValue<Opt_Int64>(static_cast<int64_t>(info->GetPressedTime().time_since_epoch().count()));
}
void SetPressedTimeImpl(Ark_TouchObject peer,
                        const Opt_Int64* pressedTime)
{
}
Opt_Float64 GetPressureImpl(Ark_TouchObject peer)
{
    auto errValue = Converter::ArkValue<Opt_Float64>();
    CHECK_NULL_RETURN(peer, errValue);
    TouchLocationInfo* info = peer->GetEventInfo();
    CHECK_NULL_RETURN(info, errValue);
    return Converter::ArkValue<Opt_Float64>(PipelineBase::Px2VpWithCurrentDensity(info->GetForce()));
}
void SetPressureImpl(Ark_TouchObject peer,
                     const Opt_Float64* pressure)
{
}
Opt_Float64 GetWidthImpl(Ark_TouchObject peer)
{
    auto errValue = Converter::ArkValue<Opt_Float64>();
    CHECK_NULL_RETURN(peer, errValue);
    TouchLocationInfo* info = peer->GetEventInfo();
    CHECK_NULL_RETURN(info, errValue);
    return Converter::ArkValue<Opt_Float64>(PipelineBase::Px2VpWithCurrentDensity(info->GetWidth()));
}
void SetWidthImpl(Ark_TouchObject peer,
                  const Opt_Float64* width)
{
}
Opt_Float64 GetHeightImpl(Ark_TouchObject peer)
{
    auto errValue = Converter::ArkValue<Opt_Float64>();
    CHECK_NULL_RETURN(peer, errValue);
    TouchLocationInfo* info = peer->GetEventInfo();
    CHECK_NULL_RETURN(info, errValue);
    return Converter::ArkValue<Opt_Float64>(PipelineBase::Px2VpWithCurrentDensity(info->GetHeight()));
}
void SetHeightImpl(Ark_TouchObject peer,
                   const Opt_Float64* height)
{
}
Opt_Float64 GetGlobalDisplayXImpl(Ark_TouchObject peer)
{
    const auto errValue = Converter::ArkValue<Opt_Float64>();
    CHECK_NULL_RETURN(peer, errValue);
    TouchLocationInfo* info = peer->GetEventInfo();
    CHECK_NULL_RETURN(info, errValue);
    Offset globalDisplayOffset = info->GetGlobalDisplayLocation();
    return Converter::ArkValue<Opt_Float64>(PipelineBase::Px2VpWithCurrentDensity(globalDisplayOffset.GetX()));
}
void SetGlobalDisplayXImpl(Ark_TouchObject peer,
                           const Opt_Float64* globalDisplayX)
{
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(globalDisplayX);
    if (globalDisplayX->tag == InteropTag::INTEROP_TAG_UNDEFINED) {
        return;
    }
    auto* info = peer->GetEventInfo();
    CHECK_NULL_VOID(info);
    auto globalDisplayOffset = info->GetGlobalDisplayLocation();
    globalDisplayOffset.SetX(globalDisplayX->value);
    info->SetGlobalDisplayLocation(globalDisplayOffset);
}
Opt_Float64 GetGlobalDisplayYImpl(Ark_TouchObject peer)
{
    const auto errValue = Converter::ArkValue<Opt_Float64>();
    CHECK_NULL_RETURN(peer, errValue);
    TouchLocationInfo* info = peer->GetEventInfo();
    CHECK_NULL_RETURN(info, errValue);
    Offset globalDisplayOffset = info->GetGlobalDisplayLocation();
    return Converter::ArkValue<Opt_Float64>(PipelineBase::Px2VpWithCurrentDensity(globalDisplayOffset.GetY()));
}
void SetGlobalDisplayYImpl(Ark_TouchObject peer,
                           const Opt_Float64* globalDisplayY)
{
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(globalDisplayY);
    if (globalDisplayY->tag == InteropTag::INTEROP_TAG_UNDEFINED) {
        return;
    }
    auto* info = peer->GetEventInfo();
    CHECK_NULL_VOID(info);
    auto globalDisplayOffset = info->GetGlobalDisplayLocation();
    globalDisplayOffset.SetY(globalDisplayY->value);
    info->SetGlobalDisplayLocation(globalDisplayOffset);
}
} // TouchObjectAccessor
const GENERATED_ArkUITouchObjectAccessor* GetTouchObjectAccessor()
{
    static const GENERATED_ArkUITouchObjectAccessor TouchObjectAccessorImpl {
        TouchObjectAccessor::DestroyPeerImpl,
        TouchObjectAccessor::ConstructImpl,
        TouchObjectAccessor::GetFinalizerImpl,
        TouchObjectAccessor::GetCurrentLocalPositionImpl,
        TouchObjectAccessor::GetTypeImpl,
        TouchObjectAccessor::SetTypeImpl,
        TouchObjectAccessor::GetIdImpl,
        TouchObjectAccessor::SetIdImpl,
        TouchObjectAccessor::GetDisplayXImpl,
        TouchObjectAccessor::SetDisplayXImpl,
        TouchObjectAccessor::GetDisplayYImpl,
        TouchObjectAccessor::SetDisplayYImpl,
        TouchObjectAccessor::GetWindowXImpl,
        TouchObjectAccessor::SetWindowXImpl,
        TouchObjectAccessor::GetWindowYImpl,
        TouchObjectAccessor::SetWindowYImpl,
        TouchObjectAccessor::GetXImpl,
        TouchObjectAccessor::SetXImpl,
        TouchObjectAccessor::GetYImpl,
        TouchObjectAccessor::SetYImpl,
        TouchObjectAccessor::GetHandImpl,
        TouchObjectAccessor::SetHandImpl,
        TouchObjectAccessor::GetPressedTimeImpl,
        TouchObjectAccessor::SetPressedTimeImpl,
        TouchObjectAccessor::GetPressureImpl,
        TouchObjectAccessor::SetPressureImpl,
        TouchObjectAccessor::GetWidthImpl,
        TouchObjectAccessor::SetWidthImpl,
        TouchObjectAccessor::GetHeightImpl,
        TouchObjectAccessor::SetHeightImpl,
        TouchObjectAccessor::GetGlobalDisplayXImpl,
        TouchObjectAccessor::SetGlobalDisplayXImpl,
        TouchObjectAccessor::GetGlobalDisplayYImpl,
        TouchObjectAccessor::SetGlobalDisplayYImpl,
    };
    return &TouchObjectAccessorImpl;
}

}
