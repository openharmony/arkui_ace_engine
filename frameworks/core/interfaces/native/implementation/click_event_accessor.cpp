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

#include <unordered_set>

#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/interfaces/native/implementation/click_event_peer.h"

namespace {
const std::unordered_set<std::string> g_clickPreventDefPattern = { "RichEditor", "Checkbox", "CheckboxGroup",
    "Rating", "Radio", "Toggle", "Hyperlink" };

const int32_t HAND_NONE = 0;
const int32_t HAND_LEFT = 1;
const int32_t HAND_RIGHT = 2;
}

namespace OHOS::Ace::NG::GeneratedModifier {
namespace ClickEventAccessor {
namespace {
    const Opt_Float64 INVALID_OPT_FLOAT64 = Converter::ArkValue<Opt_Float64>();
    const float DEFAULT_VALUE = 0.0;
} // namespace
void DestroyPeerImpl(Ark_ClickEvent peer)
{
    PeerUtils::DestroyPeer(peer);
}
Ark_ClickEvent ConstructImpl()
{
    return PeerUtils::CreatePeer<ClickEventPeer>();
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Ark_Float64 GetDisplayXImpl(Ark_ClickEvent peer)
{
    const auto errValue = Converter::ArkValue<Ark_Float64>(0);
    CHECK_NULL_RETURN(peer, errValue);
    const auto* info = peer->GetEventInfo();
    CHECK_NULL_RETURN(info, errValue);
    const auto& offset = info->GetScreenLocation();
    const auto x = PipelineBase::Px2VpWithCurrentDensity(offset.GetX());
    return Converter::ArkValue<Ark_Float64>(x);
}
void SetDisplayXImpl(Ark_ClickEvent peer, Ark_Float64 displayX)
{
    CHECK_NULL_VOID(peer);
    const auto info = peer->GetEventInfo();
    CHECK_NULL_VOID(info);
    Offset offset = info->GetScreenLocation();
    const auto animation = offset.GetXAnimationOption();
    offset.SetX(displayX, animation);
    info->SetScreenLocation(offset);
}
Ark_Float64 GetDisplayYImpl(Ark_ClickEvent peer)
{
    const auto errValue = Converter::ArkValue<Ark_Float64>(0);
    CHECK_NULL_RETURN(peer, errValue);
    const auto* info = peer->GetEventInfo();
    CHECK_NULL_RETURN(info, errValue);
    const auto& offset = info->GetScreenLocation();
    const auto y = PipelineBase::Px2VpWithCurrentDensity(offset.GetY());
    return Converter::ArkValue<Ark_Float64>(y);
}
void SetDisplayYImpl(Ark_ClickEvent peer, Ark_Float64 displayY)
{
    CHECK_NULL_VOID(peer);
    const auto info = peer->GetEventInfo();
    CHECK_NULL_VOID(info);
    Offset offset = info->GetScreenLocation();
    const auto animation = offset.GetYAnimationOption();
    offset.SetY(displayY, animation);
    info->SetScreenLocation(offset);
}
Ark_Float64 GetWindowXImpl(Ark_ClickEvent peer)
{
    const auto errValue = Converter::ArkValue<Ark_Float64>(0);
    CHECK_NULL_RETURN(peer, errValue);
    const auto* info = peer->GetEventInfo();
    CHECK_NULL_RETURN(info, errValue);
    const auto& offset = info->GetGlobalLocation();
    const auto x = PipelineBase::Px2VpWithCurrentDensity(offset.GetX());
    return Converter::ArkValue<Ark_Float64>(x);
}
void SetWindowXImpl(Ark_ClickEvent peer, Ark_Float64 windowX)
{
    CHECK_NULL_VOID(peer);
    const auto info = peer->GetEventInfo();
    CHECK_NULL_VOID(info);
    Offset offset = info->GetGlobalLocation();
    const auto animation = offset.GetXAnimationOption();
    offset.SetX(windowX, animation);
    info->SetGlobalLocation(offset);
}
Ark_Float64 GetWindowYImpl(Ark_ClickEvent peer)
{
    const auto errValue = Converter::ArkValue<Ark_Float64>(0);
    CHECK_NULL_RETURN(peer, errValue);
    const auto* info = peer->GetEventInfo();
    CHECK_NULL_RETURN(info, errValue);
    const auto& offset = info->GetGlobalLocation();
    const auto y = PipelineBase::Px2VpWithCurrentDensity(offset.GetY());
    return Converter::ArkValue<Ark_Float64>(y);
}
void SetWindowYImpl(Ark_ClickEvent peer, Ark_Float64 windowY)
{
    CHECK_NULL_VOID(peer);
    const auto info = peer->GetEventInfo();
    CHECK_NULL_VOID(info);
    Offset offset = info->GetGlobalLocation();
    const auto animation = offset.GetYAnimationOption();
    offset.SetY(windowY, animation);
    info->SetGlobalLocation(offset);
}
Ark_Float64 GetXImpl(Ark_ClickEvent peer)
{
    const auto errValue = Converter::ArkValue<Ark_Float64>(0);
    CHECK_NULL_RETURN(peer, errValue);
    const auto* info = peer->GetEventInfo();
    CHECK_NULL_RETURN(info, errValue);
    const auto& offset = info->GetLocalLocation();
    const auto x = PipelineBase::Px2VpWithCurrentDensity(offset.GetX());
    return Converter::ArkValue<Ark_Float64>(x);
}
void SetXImpl(Ark_ClickEvent peer, Ark_Float64 x)
{
    CHECK_NULL_VOID(peer);
    const auto info = peer->GetEventInfo();
    CHECK_NULL_VOID(info);
    Offset offset = info->GetLocalLocation();
    const auto animation = offset.GetXAnimationOption();
    offset.SetX(x, animation);
    info->SetLocalLocation(offset);
}
Ark_Float64 GetYImpl(Ark_ClickEvent peer)
{
    const auto errValue = Converter::ArkValue<Ark_Float64>(0);
    CHECK_NULL_RETURN(peer, errValue);
    const auto* info = peer->GetEventInfo();
    CHECK_NULL_RETURN(info, errValue);
    const auto& offset = info->GetLocalLocation();
    const auto y = PipelineBase::Px2VpWithCurrentDensity(offset.GetY());
    return Converter::ArkValue<Ark_Float64>(y);
}
void SetYImpl(Ark_ClickEvent peer, Ark_Float64 y)
{
    CHECK_NULL_VOID(peer);
    const auto info = peer->GetEventInfo();
    CHECK_NULL_VOID(info);
    Offset offset = info->GetLocalLocation();
    const auto animation = offset.GetYAnimationOption();
    offset.SetY(y, animation);
    info->SetLocalLocation(offset);
}
Opt_InteractionHand GetHandImpl(Ark_ClickEvent peer)
{
    auto errorValue = Converter::ArkValue<Opt_InteractionHand>();
    CHECK_NULL_RETURN(peer, errorValue);
    const auto info = peer->GetEventInfo();
    CHECK_NULL_RETURN(info, errorValue);

    int32_t left = 0;
    int32_t right = 0;
    for (const FingerInfo& fingerInfo : info->GetFingerList()) {
        if (fingerInfo.operatingHand_ == HAND_LEFT) {
            ++left;
        } else if (fingerInfo.operatingHand_ == HAND_RIGHT) {
            ++right;
        }
    }
    Ark_InteractionHand retVal = ARK_INTERACTION_HAND_NONE;
    if (left > right) {
        retVal = ARK_INTERACTION_HAND_LEFT;
    } else if (right > left) {
        retVal = ARK_INTERACTION_HAND_RIGHT;
    }
    return Converter::ArkValue<Opt_InteractionHand>(retVal);
}
void SetHandImpl(Ark_ClickEvent peer,
                 const Opt_InteractionHand* hand)
{
    LOGE("ClickEventAccessor::SetHandImpl we can only GET hand");
}
void PreventDefaultImpl(Ark_ClickEvent peer)
{
    CHECK_NULL_VOID(peer);
    GestureEvent* info = peer->GetEventInfo();
    CHECK_NULL_VOID(info);
    info->SetPreventDefault(true);
}
Ark_Coordinate2D GetCurrentLocalPositionImpl(Ark_ClickEvent peer)
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
Opt_Float64 GetGlobalDisplayXImpl(Ark_ClickEvent peer)
{
    CHECK_NULL_RETURN(peer, INVALID_OPT_FLOAT64);
    const auto* info = peer->GetEventInfo();
    CHECK_NULL_RETURN(info, INVALID_OPT_FLOAT64);
    const auto& globalDisplayLocation = info->GetGlobalDisplayLocation();
    const auto x = PipelineBase::Px2VpWithCurrentDensity(globalDisplayLocation.GetX());
    return Converter::ArkValue<Opt_Float64>(x);
}
void SetGlobalDisplayXImpl(Ark_ClickEvent peer,
                           const Opt_Float64* globalDisplayX)
{
    CHECK_NULL_VOID(peer);
    const auto info = peer->GetEventInfo();
    CHECK_NULL_VOID(info);
    Offset globalDisplayLocation = info->GetGlobalDisplayLocation();
    const auto animation = globalDisplayLocation.GetXAnimationOption();
    const auto globalDisplayXValue = Converter::OptConvertPtr<double>(globalDisplayX).value_or(DEFAULT_VALUE);
    globalDisplayLocation.SetX(globalDisplayXValue, animation);
    info->SetGlobalDisplayLocation(globalDisplayLocation);
}
Opt_Float64 GetGlobalDisplayYImpl(Ark_ClickEvent peer)
{
    CHECK_NULL_RETURN(peer, INVALID_OPT_FLOAT64);
    const auto* info = peer->GetEventInfo();
    CHECK_NULL_RETURN(info, INVALID_OPT_FLOAT64);
    const auto& globalDisplayLocation = info->GetGlobalDisplayLocation();
    const auto y = PipelineBase::Px2VpWithCurrentDensity(globalDisplayLocation.GetY());
    return Converter::ArkValue<Opt_Float64>(y);
}
void SetGlobalDisplayYImpl(Ark_ClickEvent peer,
                           const Opt_Float64* globalDisplayY)
{
    CHECK_NULL_VOID(peer);
    const auto info = peer->GetEventInfo();
    CHECK_NULL_VOID(info);
    Offset globalDisplayLocation = info->GetGlobalDisplayLocation();
    const auto animation = globalDisplayLocation.GetYAnimationOption();
    const auto globalDisplayYValue = Converter::OptConvertPtr<double>(globalDisplayY).value_or(DEFAULT_VALUE);
    globalDisplayLocation.SetY(globalDisplayYValue, animation);
    info->SetGlobalDisplayLocation(globalDisplayLocation);
}
} // ClickEventAccessor
const GENERATED_ArkUIClickEventAccessor* GetClickEventAccessor()
{
    static const GENERATED_ArkUIClickEventAccessor ClickEventAccessorImpl {
        ClickEventAccessor::DestroyPeerImpl,
        ClickEventAccessor::ConstructImpl,
        ClickEventAccessor::GetFinalizerImpl,
        ClickEventAccessor::PreventDefaultImpl,
        ClickEventAccessor::GetCurrentLocalPositionImpl,
        ClickEventAccessor::GetDisplayXImpl,
        ClickEventAccessor::SetDisplayXImpl,
        ClickEventAccessor::GetDisplayYImpl,
        ClickEventAccessor::SetDisplayYImpl,
        ClickEventAccessor::GetWindowXImpl,
        ClickEventAccessor::SetWindowXImpl,
        ClickEventAccessor::GetWindowYImpl,
        ClickEventAccessor::SetWindowYImpl,
        ClickEventAccessor::GetXImpl,
        ClickEventAccessor::SetXImpl,
        ClickEventAccessor::GetYImpl,
        ClickEventAccessor::SetYImpl,
        ClickEventAccessor::GetHandImpl,
        ClickEventAccessor::SetHandImpl,
        ClickEventAccessor::GetGlobalDisplayXImpl,
        ClickEventAccessor::SetGlobalDisplayXImpl,
        ClickEventAccessor::GetGlobalDisplayYImpl,
        ClickEventAccessor::SetGlobalDisplayYImpl,
    };
    return &ClickEventAccessorImpl;
}

}
