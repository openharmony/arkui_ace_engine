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

#include "arkoala_api_generated.h"

#include "core/components_ng/base/frame_node.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/interfaces/native/implementation/mouse_event_peer.h"

namespace OHOS::Ace::NG::Converter {
    template<>
    void AssignCast(std::optional<MouseButton>& dst, const Ark_MouseButton& src)
    {
        switch (src) {
            case ARK_MOUSE_BUTTON_NONE: dst = MouseButton::NONE_BUTTON; break;
            case ARK_MOUSE_BUTTON_LEFT: dst = MouseButton::LEFT_BUTTON; break;
            case ARK_MOUSE_BUTTON_RIGHT: dst = MouseButton::RIGHT_BUTTON; break;
            case ARK_MOUSE_BUTTON_MIDDLE: dst = MouseButton::MIDDLE_BUTTON; break;
            case ARK_MOUSE_BUTTON_BACK: dst = MouseButton::BACK_BUTTON; break;
            case ARK_MOUSE_BUTTON_FORWARD: dst = MouseButton::FORWARD_BUTTON; break;
            default: LOGE("Unexpected enum value in Ark_MouseButton: %{public}d", src);
        }
    }

    template<>
    void AssignCast(std::optional<MouseAction>& dst, const Ark_MouseAction& src)
    {
        switch (src) {
            case ARK_MOUSE_ACTION_HOVER: dst = MouseAction::HOVER; break;
            case ARK_MOUSE_ACTION_MOVE: dst = MouseAction::MOVE; break;
            case ARK_MOUSE_ACTION_PRESS: dst = MouseAction::PRESS; break;
            case ARK_MOUSE_ACTION_RELEASE: dst = MouseAction::RELEASE; break;
            case ARK_MOUSE_ACTION_CANCEL: dst = MouseAction::CANCEL; break;
            default: LOGE("Unexpected enum value in Ark_MouseAction: %{public}d", src);
        }
    }
} // namespace OHOS::Ace::NG::Converter

namespace OHOS::Ace::NG::GeneratedModifier {
namespace MouseEventAccessor {
void DestroyPeerImpl(Ark_MouseEvent peer)
{
    PeerUtils::DestroyPeer(peer);
}
Ark_MouseEvent ConstructImpl()
{
    return PeerUtils::CreatePeer<MouseEventPeer>();
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Ark_MouseButton GetButtonImpl(Ark_MouseEvent peer)
{
    const auto errValue = Converter::ArkValue<Ark_MouseButton>(MouseButton::NONE_BUTTON);
    CHECK_NULL_RETURN(peer, errValue);
    auto info = peer->GetEventInfo();
    CHECK_NULL_RETURN(info, errValue);
    auto mouseBtn = info->GetButton();
    return Converter::ArkValue<Ark_MouseButton>(mouseBtn);
}
void SetButtonImpl(Ark_MouseEvent peer,
                   Ark_MouseButton button)
{
    CHECK_NULL_VOID(peer);
    auto info = peer->GetEventInfo();
    CHECK_NULL_VOID(info);
    auto aceMouseButton = Converter::OptConvert<MouseButton>(button);
    if (aceMouseButton) {
        info->SetButton(aceMouseButton.value());
    }
}
Ark_MouseAction GetActionImpl(Ark_MouseEvent peer)
{
    const auto errValue = Converter::ArkValue<Ark_MouseAction>(MouseAction::NONE);
    CHECK_NULL_RETURN(peer, errValue);
    auto info = peer->GetEventInfo();
    CHECK_NULL_RETURN(info, errValue);
    auto mouseAct = info->GetAction();
    return Converter::ArkValue<Ark_MouseAction>(mouseAct);
}
void SetActionImpl(Ark_MouseEvent peer,
                   Ark_MouseAction action)
{
    CHECK_NULL_VOID(peer);
    auto info = peer->GetEventInfo();
    CHECK_NULL_VOID(info);
    auto aceMouseAction = Converter::OptConvert<MouseAction>(action);
    if (aceMouseAction) {
        info->SetAction(aceMouseAction.value());
    }
}
Ark_Float64 GetDisplayXImpl(Ark_MouseEvent peer)
{
    const auto errValue = Converter::ArkValue<Ark_Float64>(0);
    CHECK_NULL_RETURN(peer, errValue);
    auto info = peer->GetEventInfo();
    CHECK_NULL_RETURN(info, errValue);
    const auto& screenLocation = info->GetScreenLocation();
    const auto value = PipelineBase::Px2VpWithCurrentDensity(screenLocation.GetX());
    return Converter::ArkValue<Ark_Float64>(value);
}
void SetDisplayXImpl(Ark_MouseEvent peer, Ark_Float64 displayX)
{
    CHECK_NULL_VOID(peer);
    auto info = peer->GetEventInfo();
    CHECK_NULL_VOID(info);
    auto screenLocation = info->GetScreenLocation();
    const auto animation = screenLocation.GetXAnimationOption();
    auto value = Converter::Convert<float>(displayX);
    auto xConvert = PipelineBase::Vp2PxWithCurrentDensity(value);
    screenLocation.SetX(xConvert, animation);
    info->SetScreenLocation(screenLocation);
}
Ark_Float64 GetDisplayYImpl(Ark_MouseEvent peer)
{
    const auto errValue = Converter::ArkValue<Ark_Float64>(0);
    CHECK_NULL_RETURN(peer, errValue);
    auto info = peer->GetEventInfo();
    CHECK_NULL_RETURN(info, errValue);
    const auto& screenLocation = info->GetScreenLocation();
    const auto value = PipelineBase::Px2VpWithCurrentDensity(screenLocation.GetY());
    return Converter::ArkValue<Ark_Float64>(value);
}
void SetDisplayYImpl(Ark_MouseEvent peer, Ark_Float64 displayY)
{
    CHECK_NULL_VOID(peer);
    auto info = peer->GetEventInfo();
    CHECK_NULL_VOID(info);
    auto screenLocation = info->GetScreenLocation();
    const auto animation = screenLocation.GetYAnimationOption();
    auto value = Converter::Convert<float>(displayY);
    auto yConvert = PipelineBase::Vp2PxWithCurrentDensity(value);
    screenLocation.SetY(yConvert, animation);
    info->SetScreenLocation(screenLocation);
}
Ark_Float64 GetWindowXImpl(Ark_MouseEvent peer)
{
    const auto errValue = Converter::ArkValue<Ark_Float64>(0);
    CHECK_NULL_RETURN(peer, errValue);
    auto info = peer->GetEventInfo();
    CHECK_NULL_RETURN(info, errValue);
    const auto& globalLocation = info->GetGlobalLocation();
    const auto value = PipelineBase::Px2VpWithCurrentDensity(globalLocation.GetX());
    return Converter::ArkValue<Ark_Float64>(value);
}
void SetWindowXImpl(Ark_MouseEvent peer, Ark_Float64 windowX)
{
    CHECK_NULL_VOID(peer);
    auto info = peer->GetEventInfo();
    CHECK_NULL_VOID(info);
    auto globalLocation = info->GetGlobalLocation();
    const auto animation = globalLocation.GetXAnimationOption();
    auto value = Converter::Convert<float>(windowX);
    auto xConvert = PipelineBase::Vp2PxWithCurrentDensity(value);
    globalLocation.SetX(xConvert, animation);
    info->SetGlobalLocation(globalLocation);
}
Ark_Float64 GetWindowYImpl(Ark_MouseEvent peer)
{
    const auto errValue = Converter::ArkValue<Ark_Float64>(0);
    CHECK_NULL_RETURN(peer, errValue);
    auto info = peer->GetEventInfo();
    CHECK_NULL_RETURN(info, errValue);
    const auto& globalLocation = info->GetGlobalLocation();
    const auto value = PipelineBase::Px2VpWithCurrentDensity(globalLocation.GetY());
    return Converter::ArkValue<Ark_Float64>(value);
}
void SetWindowYImpl(Ark_MouseEvent peer, Ark_Float64 windowY)
{
    CHECK_NULL_VOID(peer);
    auto info = peer->GetEventInfo();
    CHECK_NULL_VOID(info);
    auto globalLocation = info->GetGlobalLocation();
    const auto animation = globalLocation.GetYAnimationOption();
    auto value = Converter::Convert<float>(windowY);
    auto yConvert = PipelineBase::Vp2PxWithCurrentDensity(value);
    globalLocation.SetY(yConvert, animation);
    info->SetGlobalLocation(globalLocation);
}
Ark_Float64 GetXImpl(Ark_MouseEvent peer)
{
    const auto errValue = Converter::ArkValue<Ark_Float64>(0);
    CHECK_NULL_RETURN(peer, errValue);
    auto info = peer->GetEventInfo();
    CHECK_NULL_RETURN(info, errValue);
    const auto& localLocation = info->GetLocalLocation();
    const auto value = PipelineBase::Px2VpWithCurrentDensity(localLocation.GetX());
    return Converter::ArkValue<Ark_Float64>(value);
}
void SetXImpl(Ark_MouseEvent peer, Ark_Float64 x)
{
    CHECK_NULL_VOID(peer);
    auto info = peer->GetEventInfo();
    CHECK_NULL_VOID(info);
    auto localLocation = info->GetLocalLocation();
    const auto animation = localLocation.GetXAnimationOption();
    auto value = Converter::Convert<float>(x);
    auto xConvert = PipelineBase::Vp2PxWithCurrentDensity(value);
    localLocation.SetX(xConvert, animation);
    info->SetLocalLocation(localLocation);
}
Ark_Float64 GetYImpl(Ark_MouseEvent peer)
{
    const auto errValue = Converter::ArkValue<Ark_Float64>(0);
    CHECK_NULL_RETURN(peer, errValue);
    auto info = peer->GetEventInfo();
    CHECK_NULL_RETURN(info, errValue);
    const auto& localLocation = info->GetLocalLocation();
    const auto value = PipelineBase::Px2VpWithCurrentDensity(localLocation.GetY());
    return Converter::ArkValue<Ark_Float64>(value);
}
void SetYImpl(Ark_MouseEvent peer, Ark_Float64 y)
{
    CHECK_NULL_VOID(peer);
    auto info = peer->GetEventInfo();
    CHECK_NULL_VOID(info);
    auto localLocation = info->GetLocalLocation();
    const auto animation = localLocation.GetYAnimationOption();
    auto value = Converter::Convert<float>(y);
    auto yConvert = PipelineBase::Vp2PxWithCurrentDensity(value);
    localLocation.SetY(yConvert, animation);
    info->SetLocalLocation(localLocation);
}
Callback_Void GetStopPropagationImpl(Ark_MouseEvent peer)
{
    CHECK_NULL_RETURN(peer, {});
    auto callback = CallbackKeeper::DefineReverseCallback<Callback_Void>([peer]() {
        MouseInfo* info = peer->GetEventInfo();
        CHECK_NULL_VOID(info);
        info->SetStopPropagation(true);
    });
    return callback;
}
void SetStopPropagationImpl(Ark_MouseEvent peer,
                            const Callback_Void* stopPropagation)
{
    CHECK_NULL_VOID(peer);
    auto info = peer->GetEventInfo();
    CHECK_NULL_VOID(info);
    LOGE("Arkoala method MouseEventAccessor.SetStopPropagation doesn't have sense. Not implemented...");
}
Opt_Float64 GetRawDeltaXImpl(Ark_MouseEvent peer)
{
    const auto errValue = Converter::ArkValue<Opt_Float64>();
    CHECK_NULL_RETURN(peer, errValue);
    auto info = peer->GetEventInfo();
    CHECK_NULL_RETURN(info, errValue);
    return Converter::ArkValue<Opt_Float64>(PipelineBase::Px2VpWithCurrentDensity(info->GetRawDeltaX()));
}
void SetRawDeltaXImpl(Ark_MouseEvent peer,
                      const Opt_Float64* rawDeltaX)
{
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(rawDeltaX);
    auto info = peer->GetEventInfo();
    CHECK_NULL_VOID(info);
    auto valueX = Converter::OptConvertPtr<float>(rawDeltaX);
    if (valueX) {
        info->SetRawDeltaX(valueX.value());
    }
}
Opt_Float64 GetRawDeltaYImpl(Ark_MouseEvent peer)
{
    const auto errValue = Converter::ArkValue<Opt_Float64>();
    CHECK_NULL_RETURN(peer, errValue);
    auto info = peer->GetEventInfo();
    CHECK_NULL_RETURN(info, errValue);
    return Converter::ArkValue<Opt_Float64>(PipelineBase::Px2VpWithCurrentDensity(info->GetRawDeltaY()));
}
void SetRawDeltaYImpl(Ark_MouseEvent peer,
                      const Opt_Float64* rawDeltaY)
{
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(rawDeltaY);
    auto info = peer->GetEventInfo();
    CHECK_NULL_VOID(info);
    auto valueY = Converter::OptConvertPtr<float>(rawDeltaY);
    if (valueY) {
        info->SetRawDeltaX(valueY.value());
    }
}
Opt_Array_MouseButton GetPressedButtonsImpl(Ark_MouseEvent peer)
{
    auto invalid = Converter::ArkValue<Opt_Array_MouseButton>();
    CHECK_NULL_RETURN(peer, invalid);
    auto info = peer->GetEventInfo();
    CHECK_NULL_RETURN(info, invalid);
    return Converter::ArkValue<Opt_Array_MouseButton>(info->GetPressedButtons(), Converter::FC);
}
void SetPressedButtonsImpl(Ark_MouseEvent peer,
                           const Opt_Array_MouseButton* pressedButtons)
{
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(pressedButtons);
    auto info = peer->GetEventInfo();
    CHECK_NULL_VOID(info);
    std::vector<MouseButton> buttons;
    auto arrOpt  = Converter::OptConvertPtr<Array_MouseButton>(pressedButtons);
    if (arrOpt) {
        for (int i = 0; i < arrOpt->length; ++i) {
            auto mouseButton = Converter::OptConvert<MouseButton>(arrOpt->array[i]);
            if (mouseButton) {
                buttons.push_back(mouseButton.value());
            }
        }
        info->SetPressedButtons(buttons);
    }
}
} // MouseEventAccessor
const GENERATED_ArkUIMouseEventAccessor* GetMouseEventAccessor()
{
    static const GENERATED_ArkUIMouseEventAccessor MouseEventAccessorImpl {
        MouseEventAccessor::DestroyPeerImpl,
        MouseEventAccessor::ConstructImpl,
        MouseEventAccessor::GetFinalizerImpl,
        MouseEventAccessor::GetButtonImpl,
        MouseEventAccessor::SetButtonImpl,
        MouseEventAccessor::GetActionImpl,
        MouseEventAccessor::SetActionImpl,
        MouseEventAccessor::GetDisplayXImpl,
        MouseEventAccessor::SetDisplayXImpl,
        MouseEventAccessor::GetDisplayYImpl,
        MouseEventAccessor::SetDisplayYImpl,
        MouseEventAccessor::GetWindowXImpl,
        MouseEventAccessor::SetWindowXImpl,
        MouseEventAccessor::GetWindowYImpl,
        MouseEventAccessor::SetWindowYImpl,
        MouseEventAccessor::GetXImpl,
        MouseEventAccessor::SetXImpl,
        MouseEventAccessor::GetYImpl,
        MouseEventAccessor::SetYImpl,
        MouseEventAccessor::GetStopPropagationImpl,
        MouseEventAccessor::SetStopPropagationImpl,
        MouseEventAccessor::GetRawDeltaXImpl,
        MouseEventAccessor::SetRawDeltaXImpl,
        MouseEventAccessor::GetRawDeltaYImpl,
        MouseEventAccessor::SetRawDeltaYImpl,
        MouseEventAccessor::GetPressedButtonsImpl,
        MouseEventAccessor::SetPressedButtonsImpl,
    };
    return &MouseEventAccessorImpl;
}
}
