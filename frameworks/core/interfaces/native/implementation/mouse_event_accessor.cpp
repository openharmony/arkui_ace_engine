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
            default: LOGE("Unexpected enum value in Ark_MouseAction: %{public}d", src);
        }
    }
} // namespace OHOS::Ace::NG::Converter

namespace OHOS::Ace::NG::GeneratedModifier {
namespace MouseEventAccessor {
void DestroyPeerImpl(Ark_MouseEvent peer)
{
    delete peer;
}
Ark_MouseEvent CtorImpl()
{
    return new MouseEventPeer();
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Ark_MouseButton GetButtonImpl(Ark_MouseEvent peer)
{
    CHECK_NULL_RETURN(peer, {});
    auto info = peer->GetEventInfo();
    CHECK_NULL_RETURN(info, {});
    LOGE("Arkoala method MouseEventAccessor.GetButtonImpl return nullptr value but should return enum MouseButton");
    LOGE("return info->GetButton();");
    return {};
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
    CHECK_NULL_RETURN(peer, {});
    auto info = peer->GetEventInfo();
    CHECK_NULL_RETURN(info, {});
    LOGE("Arkoala method MouseEventAccessor.GetButtonImpl return nullptr value but should return enum MouseAction");
    LOGE("return info->GetAction();");
    return {};
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
Ark_Number GetDisplayXImpl(Ark_MouseEvent peer)
{
    const auto errValue = Converter::ArkValue<Ark_Number>(0);
    CHECK_NULL_RETURN(peer, errValue);
    auto info = peer->GetEventInfo();
    CHECK_NULL_RETURN(info, errValue);
    const auto& screenLocation = info->GetScreenLocation();
    LOGE("Arkoala method MouseEventAccessor.GetDisplayXImpl return int32_t value");
    const auto value = PipelineBase::Px2VpWithCurrentDensity(screenLocation.GetX());
    return Converter::ArkValue<Ark_Number>(static_cast<int32_t>(value));
}
void SetDisplayXImpl(Ark_MouseEvent peer,
                     const Ark_Number* displayX)
{
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(displayX);
    auto info = peer->GetEventInfo();
    CHECK_NULL_VOID(info);
    auto screenLocation = info->GetScreenLocation();
    const auto animation = screenLocation.GetXAnimationOption();
    auto value = Converter::Convert<float>(*displayX);
    auto xConvert = PipelineBase::Vp2PxWithCurrentDensity(value);
    screenLocation.SetX(xConvert, animation);
    info->SetScreenLocation(screenLocation);
}
Ark_Number GetDisplayYImpl(Ark_MouseEvent peer)
{
    const auto errValue = Converter::ArkValue<Ark_Number>(0);
    CHECK_NULL_RETURN(peer, errValue);
    auto info = peer->GetEventInfo();
    CHECK_NULL_RETURN(info, errValue);
    const auto& screenLocation = info->GetScreenLocation();
    LOGE("Arkoala method MouseEventAccessor.GetDisplayYImpl return int32_t value");
    const auto value = PipelineBase::Px2VpWithCurrentDensity(screenLocation.GetY());
    return Converter::ArkValue<Ark_Number>(static_cast<int32_t>(value));
}
void SetDisplayYImpl(Ark_MouseEvent peer,
                     const Ark_Number* displayY)
{
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(displayY);
    auto info = peer->GetEventInfo();
    CHECK_NULL_VOID(info);
    auto screenLocation = info->GetScreenLocation();
    const auto animation = screenLocation.GetYAnimationOption();
    auto value = Converter::Convert<float>(*displayY);
    auto yConvert = PipelineBase::Vp2PxWithCurrentDensity(value);
    screenLocation.SetY(yConvert, animation);
    info->SetScreenLocation(screenLocation);
}
Ark_Number GetWindowXImpl(Ark_MouseEvent peer)
{
    const auto errValue = Converter::ArkValue<Ark_Number>(0);
    CHECK_NULL_RETURN(peer, errValue);
    auto info = peer->GetEventInfo();
    CHECK_NULL_RETURN(info, errValue);
    const auto& globalLocation = info->GetGlobalLocation();
    LOGE("Arkoala method MouseEventAccessor.GetWindowXImpl return int32_t value");
    const auto value = PipelineBase::Px2VpWithCurrentDensity(globalLocation.GetX());
    return Converter::ArkValue<Ark_Number>(static_cast<int32_t>(value));
}
void SetWindowXImpl(Ark_MouseEvent peer,
                    const Ark_Number* windowX)
{
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(windowX);
    auto info = peer->GetEventInfo();
    CHECK_NULL_VOID(info);
    auto globalLocation = info->GetGlobalLocation();
    const auto animation = globalLocation.GetXAnimationOption();
    auto value = Converter::Convert<float>(*windowX);
    auto xConvert = PipelineBase::Vp2PxWithCurrentDensity(value);
    globalLocation.SetX(xConvert, animation);
    info->SetGlobalLocation(globalLocation);
}
Ark_Number GetWindowYImpl(Ark_MouseEvent peer)
{
    const auto errValue = Converter::ArkValue<Ark_Number>(0);
    CHECK_NULL_RETURN(peer, errValue);
    auto info = peer->GetEventInfo();
    CHECK_NULL_RETURN(info, errValue);
    const auto& globalLocation = info->GetGlobalLocation();
    LOGE("Arkoala method MouseEventAccessor.GetWindowYImpl return int32_t value");
    const auto value = PipelineBase::Px2VpWithCurrentDensity(globalLocation.GetY());
    return Converter::ArkValue<Ark_Number>(static_cast<int32_t>(value));
}
void SetWindowYImpl(Ark_MouseEvent peer,
                    const Ark_Number* windowY)
{
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(windowY);
    auto info = peer->GetEventInfo();
    CHECK_NULL_VOID(info);
    auto globalLocation = info->GetGlobalLocation();
    const auto animation = globalLocation.GetYAnimationOption();
    auto value = Converter::Convert<float>(*windowY);
    auto yConvert = PipelineBase::Vp2PxWithCurrentDensity(value);
    globalLocation.SetY(yConvert, animation);
    info->SetGlobalLocation(globalLocation);
}
Ark_Number GetScreenXImpl(Ark_MouseEvent peer)
{
    const auto errValue = Converter::ArkValue<Ark_Number>(0);
    CHECK_NULL_RETURN(peer, errValue);
    auto info = peer->GetEventInfo();
    CHECK_NULL_RETURN(info, errValue);
    const auto& globalLocation = info->GetGlobalLocation();
    LOGE("Arkoala method MouseEventAccessor.GetScreenXImpl return int32_t value");
    const auto value = PipelineBase::Px2VpWithCurrentDensity(globalLocation.GetX());
    return Converter::ArkValue<Ark_Number>(static_cast<int32_t>(value));
}
void SetScreenXImpl(Ark_MouseEvent peer,
                    const Ark_Number* screenX)
{
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(screenX);
    auto info = peer->GetEventInfo();
    CHECK_NULL_VOID(info);
    auto globalLocation = info->GetGlobalLocation();
    const auto animation = globalLocation.GetXAnimationOption();
    auto value = Converter::Convert<float>(*screenX);
    auto xConvert = PipelineBase::Vp2PxWithCurrentDensity(value);
    globalLocation.SetX(xConvert, animation);
    info->SetGlobalLocation(globalLocation);
}
Ark_Number GetScreenYImpl(Ark_MouseEvent peer)
{
    const auto errValue = Converter::ArkValue<Ark_Number>(0);
    CHECK_NULL_RETURN(peer, errValue);
    auto info = peer->GetEventInfo();
    CHECK_NULL_RETURN(info, errValue);
    const auto& globalLocation = info->GetGlobalLocation();
    LOGE("Arkoala method MouseEventAccessor.GetScreenYImpl return int32_t value");
    const auto value = PipelineBase::Px2VpWithCurrentDensity(globalLocation.GetY());
    return Converter::ArkValue<Ark_Number>(static_cast<int32_t>(value));
}
void SetScreenYImpl(Ark_MouseEvent peer,
                    const Ark_Number* screenY)
{
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(screenY);
    auto info = peer->GetEventInfo();
    CHECK_NULL_VOID(info);
    auto globalLocation = info->GetGlobalLocation();
    const auto animation = globalLocation.GetYAnimationOption();
    auto value = Converter::Convert<float>(*screenY);
    auto yConvert = PipelineBase::Vp2PxWithCurrentDensity(value);
    globalLocation.SetY(yConvert, animation);
    info->SetGlobalLocation(globalLocation);
}
Ark_Number GetXImpl(Ark_MouseEvent peer)
{
    const auto errValue = Converter::ArkValue<Ark_Number>(0);
    CHECK_NULL_RETURN(peer, errValue);
    auto info = peer->GetEventInfo();
    CHECK_NULL_RETURN(info, errValue);
    const auto& localLocation = info->GetLocalLocation();
    LOGE("Arkoala method MouseEventAccessor.GetXImpl return int32_t value");
    const auto value = PipelineBase::Px2VpWithCurrentDensity(localLocation.GetX());
    return Converter::ArkValue<Ark_Number>(static_cast<int32_t>(value));
}
void SetXImpl(Ark_MouseEvent peer,
              const Ark_Number* x)
{
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(x);
    auto info = peer->GetEventInfo();
    CHECK_NULL_VOID(info);
    auto localLocation = info->GetLocalLocation();
    const auto animation = localLocation.GetXAnimationOption();
    auto value = Converter::Convert<float>(*x);
    auto xConvert = PipelineBase::Vp2PxWithCurrentDensity(value);
    localLocation.SetX(xConvert, animation);
    info->SetLocalLocation(localLocation);
}
Ark_Number GetYImpl(Ark_MouseEvent peer)
{
    const auto errValue = Converter::ArkValue<Ark_Number>(0);
    CHECK_NULL_RETURN(peer, errValue);
    auto info = peer->GetEventInfo();
    CHECK_NULL_RETURN(info, errValue);
    const auto& localLocation = info->GetLocalLocation();
    LOGE("Arkoala method MouseEventAccessor.GetYImpl return int32_t value");
    const auto value = PipelineBase::Px2VpWithCurrentDensity(localLocation.GetY());
    return Converter::ArkValue<Ark_Number>(static_cast<int32_t>(value));
}
void SetYImpl(Ark_MouseEvent peer,
              const Ark_Number* y)
{
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(y);
    auto info = peer->GetEventInfo();
    CHECK_NULL_VOID(info);
    auto localLocation = info->GetLocalLocation();
    const auto animation = localLocation.GetYAnimationOption();
    auto value = Converter::Convert<float>(*y);
    auto yConvert = PipelineBase::Vp2PxWithCurrentDensity(value);
    localLocation.SetY(yConvert, animation);
    info->SetLocalLocation(localLocation);
}
Callback_Void GetStopPropagationImpl(Ark_MouseEvent peer)
{
    return {};
}
void SetStopPropagationImpl(Ark_MouseEvent peer,
                            const Callback_Void* stopPropagation)
{
    CHECK_NULL_VOID(peer);
    auto info = peer->GetEventInfo();
    CHECK_NULL_VOID(info);
    LOGE("Arkoala method MouseEventAccessor.SetStopPropagation doesn't have sence. Not implemented...");
}
Ark_Number GetRawDeltaXImpl(Ark_MouseEvent peer)
{
    return {};
}
void SetRawDeltaXImpl(Ark_MouseEvent peer,
                      const Ark_Number* rawDeltaX)
{
}
Ark_Number GetRawDeltaYImpl(Ark_MouseEvent peer)
{
    return {};
}
void SetRawDeltaYImpl(Ark_MouseEvent peer,
                      const Ark_Number* rawDeltaY)
{
}
Array_MouseButton GetPressedButtonsImpl(Ark_MouseEvent peer)
{
    return {};
}
void SetPressedButtonsImpl(Ark_MouseEvent peer,
                           const Array_MouseButton* pressedButtons)
{
}
} // MouseEventAccessor
const GENERATED_ArkUIMouseEventAccessor* GetMouseEventAccessor()
{
    static const GENERATED_ArkUIMouseEventAccessor MouseEventAccessorImpl {
        MouseEventAccessor::DestroyPeerImpl,
        MouseEventAccessor::CtorImpl,
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
        MouseEventAccessor::GetScreenXImpl,
        MouseEventAccessor::SetScreenXImpl,
        MouseEventAccessor::GetScreenYImpl,
        MouseEventAccessor::SetScreenYImpl,
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
