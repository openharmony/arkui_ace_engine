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
void PreventDefaultImpl(Ark_ClickEvent peer)
{
    CHECK_NULL_VOID(peer);
    GestureEvent* info = peer->GetEventInfo();
    CHECK_NULL_VOID(info);
    info->SetPreventDefault(true);
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
void SetDisplayXImpl(Ark_ClickEvent peer,
                     Ark_Float64 displayX)
{
    CHECK_NULL_VOID(peer);
    const auto info = peer->GetEventInfo();
    CHECK_NULL_VOID(info);
    Offset offset = info->GetScreenLocation();
    const auto animation = offset.GetXAnimationOption();
    const auto convWindowsX = Converter::Convert<double>(displayX);
    const auto x = PipelineBase::Vp2PxWithCurrentDensity(convWindowsX);
    offset.SetX(x, animation);
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
void SetDisplayYImpl(Ark_ClickEvent peer,
                     Ark_Float64 displayY)
{
    CHECK_NULL_VOID(peer);
    const auto info = peer->GetEventInfo();
    CHECK_NULL_VOID(info);
    Offset offset = info->GetScreenLocation();
    const auto animation = offset.GetYAnimationOption();
    const auto convWindowsY = Converter::Convert<double>(displayY);
    const auto y = PipelineBase::Vp2PxWithCurrentDensity(convWindowsY);
    offset.SetY(y, animation);
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
void SetWindowXImpl(Ark_ClickEvent peer,
                    Ark_Float64 windowX)
{
    CHECK_NULL_VOID(peer);
    const auto info = peer->GetEventInfo();
    CHECK_NULL_VOID(info);
    Offset offset = info->GetGlobalLocation();
    const auto animation = offset.GetXAnimationOption();
    const auto convWindowsX = Converter::Convert<double>(windowX);
    const auto x = PipelineBase::Vp2PxWithCurrentDensity(convWindowsX);
    offset.SetX(x, animation);
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
void SetWindowYImpl(Ark_ClickEvent peer,
                    Ark_Float64 windowY)
{
    CHECK_NULL_VOID(peer);
    const auto info = peer->GetEventInfo();
    CHECK_NULL_VOID(info);
    Offset offset = info->GetGlobalLocation();
    const auto animation = offset.GetYAnimationOption();
    const auto convWindowsY = Converter::Convert<double>(windowY);
    const auto y = PipelineBase::Vp2PxWithCurrentDensity(convWindowsY);
    offset.SetY(y, animation);
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
void SetXImpl(Ark_ClickEvent peer,
              Ark_Float64 x)
{
    CHECK_NULL_VOID(peer);
    const auto info = peer->GetEventInfo();
    CHECK_NULL_VOID(info);
    Offset offset = info->GetLocalLocation();
    const auto animation = offset.GetXAnimationOption();
    const auto convWindowsX = Converter::Convert<double>(x);
    const auto newX = PipelineBase::Vp2PxWithCurrentDensity(convWindowsX);
    offset.SetX(newX, animation);
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
void SetYImpl(Ark_ClickEvent peer,
              Ark_Float64 y)
{
    CHECK_NULL_VOID(peer);
    const auto info = peer->GetEventInfo();
    CHECK_NULL_VOID(info);
    Offset offset = info->GetLocalLocation();
    const auto animation = offset.GetYAnimationOption();
    const auto convWindowsY = Converter::Convert<double>(y);
    const auto newY = PipelineBase::Vp2PxWithCurrentDensity(convWindowsY);
    offset.SetY(newY, animation);
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
} // ClickEventAccessor
const GENERATED_ArkUIClickEventAccessor* GetClickEventAccessor()
{
    static const GENERATED_ArkUIClickEventAccessor ClickEventAccessorImpl {
        ClickEventAccessor::DestroyPeerImpl,
        ClickEventAccessor::ConstructImpl,
        ClickEventAccessor::GetFinalizerImpl,
        ClickEventAccessor::PreventDefaultImpl,
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
    };
    return &ClickEventAccessorImpl;
}

}
