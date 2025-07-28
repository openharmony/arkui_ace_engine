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
}

namespace OHOS::Ace::NG::GeneratedModifier {
namespace ClickEventAccessor {
void DestroyPeerImpl(Ark_ClickEvent peer)
{
    PeerUtils::DestroyPeer(peer);
}
Ark_ClickEvent CtorImpl()
{
    return PeerUtils::CreatePeer<ClickEventPeer>();
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Ark_Number GetDisplayXImpl(Ark_ClickEvent peer)
{
    const auto errValue = Converter::ArkValue<Ark_Number>(0);
    CHECK_NULL_RETURN(peer, errValue);
    const auto* info = peer->GetEventInfo();
    CHECK_NULL_RETURN(info, errValue);
    const auto& offset = info->GetScreenLocation();
    const auto x = PipelineBase::Px2VpWithCurrentDensity(offset.GetX());
    return Converter::ArkValue<Ark_Number>(x);
}
void SetDisplayXImpl(Ark_ClickEvent peer,
                     const Ark_Number* displayX)
{
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(displayX);
    const auto info = peer->GetEventInfo();
    CHECK_NULL_VOID(info);
    Offset offset = info->GetScreenLocation();
    const auto animation = offset.GetXAnimationOption();
    const auto convWindowsX = Converter::Convert<float>(*displayX);
    const auto x = PipelineBase::Vp2PxWithCurrentDensity(convWindowsX);
    offset.SetX(x, animation);
    info->SetScreenLocation(offset);
}
Ark_Number GetDisplayYImpl(Ark_ClickEvent peer)
{
    const auto errValue = Converter::ArkValue<Ark_Number>(0);
    CHECK_NULL_RETURN(peer, errValue);
    const auto* info = peer->GetEventInfo();
    CHECK_NULL_RETURN(info, errValue);
    const auto& offset = info->GetScreenLocation();
    const auto y = PipelineBase::Px2VpWithCurrentDensity(offset.GetY());
    return Converter::ArkValue<Ark_Number>(y);
}
void SetDisplayYImpl(Ark_ClickEvent peer,
                     const Ark_Number* displayY)
{
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(displayY);
    const auto info = peer->GetEventInfo();
    CHECK_NULL_VOID(info);
    Offset offset = info->GetScreenLocation();
    const auto animation = offset.GetYAnimationOption();
    const auto convWindowsY = Converter::Convert<float>(*displayY);
    const auto y = PipelineBase::Vp2PxWithCurrentDensity(convWindowsY);
    offset.SetY(y, animation);
    info->SetScreenLocation(offset);
}
Ark_Number GetWindowXImpl(Ark_ClickEvent peer)
{
    const auto errValue = Converter::ArkValue<Ark_Number>(0);
    CHECK_NULL_RETURN(peer, errValue);
    const auto* info = peer->GetEventInfo();
    CHECK_NULL_RETURN(info, errValue);
    const auto& offset = info->GetGlobalLocation();
    const auto x = PipelineBase::Px2VpWithCurrentDensity(offset.GetX());
    return Converter::ArkValue<Ark_Number>(x);
}
void SetWindowXImpl(Ark_ClickEvent peer,
                    const Ark_Number* windowX)
{
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(windowX);
    const auto info = peer->GetEventInfo();
    CHECK_NULL_VOID(info);
    Offset offset = info->GetGlobalLocation();
    const auto animation = offset.GetXAnimationOption();
    const auto convWindowsX = Converter::Convert<float>(*windowX);
    const auto x = PipelineBase::Vp2PxWithCurrentDensity(convWindowsX);
    offset.SetX(x, animation);
    info->SetGlobalLocation(offset);
}
Ark_Number GetWindowYImpl(Ark_ClickEvent peer)
{
    const auto errValue = Converter::ArkValue<Ark_Number>(0);
    CHECK_NULL_RETURN(peer, errValue);
    const auto* info = peer->GetEventInfo();
    CHECK_NULL_RETURN(info, errValue);
    const auto& offset = info->GetGlobalLocation();
    const auto y = PipelineBase::Px2VpWithCurrentDensity(offset.GetY());
    return Converter::ArkValue<Ark_Number>(y);
}
void SetWindowYImpl(Ark_ClickEvent peer,
                    const Ark_Number* windowY)
{
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(windowY);
    const auto info = peer->GetEventInfo();
    CHECK_NULL_VOID(info);
    Offset offset = info->GetGlobalLocation();
    const auto animation = offset.GetYAnimationOption();
    const auto convWindowsY = Converter::Convert<float>(*windowY);
    const auto y = PipelineBase::Vp2PxWithCurrentDensity(convWindowsY);
    offset.SetY(y, animation);
    info->SetGlobalLocation(offset);
}
Ark_Number GetScreenXImpl(Ark_ClickEvent peer)
{
    return GetWindowXImpl(peer);
}
void SetScreenXImpl(Ark_ClickEvent peer,
                    const Ark_Number* screenX)
{
    SetWindowXImpl(peer, screenX);
}
Ark_Number GetScreenYImpl(Ark_ClickEvent peer)
{
    return GetWindowYImpl(peer);
}
void SetScreenYImpl(Ark_ClickEvent peer,
                    const Ark_Number* screenY)
{
    SetWindowYImpl(peer, screenY);
}
Ark_Number GetXImpl(Ark_ClickEvent peer)
{
    const auto errValue = Converter::ArkValue<Ark_Number>(0);
    CHECK_NULL_RETURN(peer, errValue);
    const auto* info = peer->GetEventInfo();
    CHECK_NULL_RETURN(info, errValue);
    const auto& offset = info->GetLocalLocation();
    const auto x = PipelineBase::Px2VpWithCurrentDensity(offset.GetX());
    return Converter::ArkValue<Ark_Number>(x);
}
void SetXImpl(Ark_ClickEvent peer,
              const Ark_Number* x)
{
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(x);
    const auto info = peer->GetEventInfo();
    CHECK_NULL_VOID(info);
    Offset offset = info->GetLocalLocation();
    const auto animation = offset.GetXAnimationOption();
    const auto convWindowsX = Converter::Convert<float>(*x);
    const auto newX = PipelineBase::Vp2PxWithCurrentDensity(convWindowsX);
    offset.SetX(newX, animation);
    info->SetLocalLocation(offset);
}
Ark_Number GetYImpl(Ark_ClickEvent peer)
{
    const auto errValue = Converter::ArkValue<Ark_Number>(0);
    CHECK_NULL_RETURN(peer, errValue);
    const auto* info = peer->GetEventInfo();
    CHECK_NULL_RETURN(info, errValue);
    const auto& offset = info->GetLocalLocation();
    const auto y = PipelineBase::Px2VpWithCurrentDensity(offset.GetY());
    return Converter::ArkValue<Ark_Number>(y);
}
void SetYImpl(Ark_ClickEvent peer,
              const Ark_Number* y)
{
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(y);
    const auto info = peer->GetEventInfo();
    CHECK_NULL_VOID(info);
    Offset offset = info->GetLocalLocation();
    const auto animation = offset.GetYAnimationOption();
    const auto convWindowsY = Converter::Convert<float>(*y);
    const auto newY = PipelineBase::Vp2PxWithCurrentDensity(convWindowsY);
    offset.SetY(newY, animation);
    info->SetLocalLocation(offset);
}
Opt_InteractionHand GetHandImpl(Ark_ClickEvent peer)
{
    return {};
}
void SetHandImpl(Ark_ClickEvent peer,
                 Ark_InteractionHand hand)
{
}
Callback_Void GetPreventDefaultImpl(Ark_ClickEvent peer)
{
    CHECK_NULL_RETURN(peer, {});
    auto callback = CallbackKeeper::DefineReverseCallback<Callback_Void>([peer]() {
        GestureEvent* info = peer->GetEventInfo();
        CHECK_NULL_VOID(info);
        auto patternName = info->GetPatternName();
        if (g_clickPreventDefPattern.find(patternName.c_str()) == g_clickPreventDefPattern.end()) {
            LOGE("ARKOALA Component does not support prevent function.");
            return;
        }
        info->SetPreventDefault(true);
    });
    return callback;
}
void SetPreventDefaultImpl(Ark_ClickEvent peer,
                           const Callback_Void* preventDefault)
{
    LOGE("ClickEventAccessor::SetPreventDefaultImpl wen can only GET preventDefault callback");
}
} // ClickEventAccessor
const GENERATED_ArkUIClickEventAccessor* GetClickEventAccessor()
{
    static const GENERATED_ArkUIClickEventAccessor ClickEventAccessorImpl {
        ClickEventAccessor::DestroyPeerImpl,
        ClickEventAccessor::CtorImpl,
        ClickEventAccessor::GetFinalizerImpl,
        ClickEventAccessor::GetDisplayXImpl,
        ClickEventAccessor::SetDisplayXImpl,
        ClickEventAccessor::GetDisplayYImpl,
        ClickEventAccessor::SetDisplayYImpl,
        ClickEventAccessor::GetWindowXImpl,
        ClickEventAccessor::SetWindowXImpl,
        ClickEventAccessor::GetWindowYImpl,
        ClickEventAccessor::SetWindowYImpl,
        ClickEventAccessor::GetScreenXImpl,
        ClickEventAccessor::SetScreenXImpl,
        ClickEventAccessor::GetScreenYImpl,
        ClickEventAccessor::SetScreenYImpl,
        ClickEventAccessor::GetXImpl,
        ClickEventAccessor::SetXImpl,
        ClickEventAccessor::GetYImpl,
        ClickEventAccessor::SetYImpl,
        ClickEventAccessor::GetHandImpl,
        ClickEventAccessor::SetHandImpl,
        ClickEventAccessor::GetPreventDefaultImpl,
        ClickEventAccessor::SetPreventDefaultImpl,
    };
    return &ClickEventAccessorImpl;
}

}
