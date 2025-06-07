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
#include "core/interfaces/native/implementation/axis_event_peer.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"

namespace OHOS::Ace::NG::Converter {
    template<>
    void AssignCast(std::optional<AxisAction>& dst, const Ark_AxisAction& src)
    {
        switch (src) {
            case ARK_AXIS_ACTION_NONE: dst = AxisAction::NONE; break;
            case ARK_AXIS_ACTION_BEGIN: dst = AxisAction::BEGIN; break;
            case ARK_AXIS_ACTION_UPDATE: dst = AxisAction::UPDATE; break;
            case ARK_AXIS_ACTION_END: dst = AxisAction::END; break;
            default: LOGE("Unexpected enum value in Ark_AxisAction: %{public}d", src);
        }
    }
} // namespace OHOS::Ace::NG::Converter

namespace OHOS::Ace::NG::GeneratedModifier {
namespace AxisEventAccessor {
void DestroyPeerImpl(Ark_AxisEvent peer)
{
    PeerUtils::DestroyPeer(peer);
}
Ark_AxisEvent CtorImpl()
{
    return PeerUtils::CreatePeer<AxisEventPeer>();
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Ark_Number GetHorizontalAxisValueImpl(Ark_AxisEvent peer)
{
    const auto errValue = Converter::ArkValue<Ark_Number>(0);
    CHECK_NULL_RETURN(peer, errValue);
    AxisInfo* event = peer->GetEventInfo();
    CHECK_NULL_RETURN(event, errValue);

    double value = event->GetHorizontalAxis();
    return Converter::ArkValue<Ark_Number>(value);
}
Ark_Number GetVerticalAxisValueImpl(Ark_AxisEvent peer)
{
    const auto errValue = Converter::ArkValue<Ark_Number>(0);
    CHECK_NULL_RETURN(peer, errValue);
    AxisInfo* event = peer->GetEventInfo();
    CHECK_NULL_RETURN(event, errValue);

    double value = event->GetVerticalAxis();
    return Converter::ArkValue<Ark_Number>(value);
}
Ark_AxisAction GetActionImpl(Ark_AxisEvent peer)
{
    const auto errValue = Converter::ArkValue<Ark_AxisAction>(AxisAction::NONE);
    CHECK_NULL_RETURN(peer, errValue);
    auto info = peer->GetEventInfo();
    CHECK_NULL_RETURN(info, errValue);
    auto axisAct = info->GetAction();
    return Converter::ArkValue<Ark_AxisAction>(axisAct);
}
void SetActionImpl(Ark_AxisEvent peer,
                   Ark_AxisAction action)
{
    CHECK_NULL_VOID(peer);
    auto info = peer->GetEventInfo();
    CHECK_NULL_VOID(info);
    auto aceAxisAction = Converter::OptConvert<AxisAction>(action);
    if (aceAxisAction) {
        info->SetAction(aceAxisAction.value());
    }
}
Ark_Number GetDisplayXImpl(Ark_AxisEvent peer)
{
    const auto errValue = Converter::ArkValue<Ark_Number>(0);
    CHECK_NULL_RETURN(peer, errValue);
    AxisInfo* event = peer->GetEventInfo();
    CHECK_NULL_RETURN(event, errValue);
    const auto& screenLocation = event->GetScreenLocation();
    const auto value = PipelineBase::Px2VpWithCurrentDensity(screenLocation.GetX());
    return Converter::ArkValue<Ark_Number>(value);
}
void SetDisplayXImpl(Ark_AxisEvent peer,
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
Ark_Number GetDisplayYImpl(Ark_AxisEvent peer)
{
    const auto errValue = Converter::ArkValue<Ark_Number>(0);
    CHECK_NULL_RETURN(peer, errValue);
    AxisInfo* event = peer->GetEventInfo();
    CHECK_NULL_RETURN(event, errValue);
    const auto& screenLocation = event->GetScreenLocation();
    const auto value = PipelineBase::Px2VpWithCurrentDensity(screenLocation.GetY());
    return Converter::ArkValue<Ark_Number>(value);
}
void SetDisplayYImpl(Ark_AxisEvent peer,
                     const Ark_Number* displayY)
{
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(displayY);
    auto info = peer->GetEventInfo();
    CHECK_NULL_VOID(info);
    auto screenLocation = info->GetScreenLocation();
    const auto animation = screenLocation.GetXAnimationOption();
    auto value = Converter::Convert<float>(*displayY);
    auto yConvert = PipelineBase::Vp2PxWithCurrentDensity(value);
    screenLocation.SetY(yConvert, animation);
    info->SetScreenLocation(screenLocation);
}
Ark_Number GetWindowXImpl(Ark_AxisEvent peer)
{
    const auto errValue = Converter::ArkValue<Ark_Number>(0);
    CHECK_NULL_RETURN(peer, errValue);
    auto info = peer->GetEventInfo();
    CHECK_NULL_RETURN(info, errValue);
    const auto& globalLocation = info->GetGlobalLocation();
    const auto value = PipelineBase::Px2VpWithCurrentDensity(globalLocation.GetX());
    return Converter::ArkValue<Ark_Number>(value);
}
void SetWindowXImpl(Ark_AxisEvent peer,
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
Ark_Number GetWindowYImpl(Ark_AxisEvent peer)
{
    const auto errValue = Converter::ArkValue<Ark_Number>(0);
    CHECK_NULL_RETURN(peer, errValue);
    auto info = peer->GetEventInfo();
    CHECK_NULL_RETURN(info, errValue);
    const auto& globalLocation = info->GetGlobalLocation();
    const auto value = PipelineBase::Px2VpWithCurrentDensity(globalLocation.GetY());
    return Converter::ArkValue<Ark_Number>(value);
}
void SetWindowYImpl(Ark_AxisEvent peer,
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
Ark_Number GetXImpl(Ark_AxisEvent peer)
{
    const auto errValue = Converter::ArkValue<Ark_Number>(0);
    CHECK_NULL_RETURN(peer, errValue);
    auto info = peer->GetEventInfo();
    CHECK_NULL_RETURN(info, errValue);
    const auto& localLocation = info->GetLocalLocation();
    const auto value = PipelineBase::Px2VpWithCurrentDensity(localLocation.GetX());
    return Converter::ArkValue<Ark_Number>(value);
}
void SetXImpl(Ark_AxisEvent peer,
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
Ark_Number GetYImpl(Ark_AxisEvent peer)
{
    const auto errValue = Converter::ArkValue<Ark_Number>(0);
    CHECK_NULL_RETURN(peer, errValue);
    auto info = peer->GetEventInfo();
    CHECK_NULL_RETURN(info, errValue);
    const auto& localLocation = info->GetLocalLocation();
    const auto value = PipelineBase::Px2VpWithCurrentDensity(localLocation.GetY());
    return Converter::ArkValue<Ark_Number>(value);
}
void SetYImpl(Ark_AxisEvent peer,
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
Opt_Number GetScrollStepImpl(Ark_AxisEvent peer)
{
    const auto errValue = Converter::ArkValue<Opt_Number>();
    CHECK_NULL_RETURN(peer, errValue);
    auto info = peer->GetEventInfo();
    CHECK_NULL_RETURN(info, errValue);
    return Converter::ArkValue<Opt_Number>(info->GetScrollStep());
}
void SetScrollStepImpl(Ark_AxisEvent peer,
                       const Ark_Number* scrollStep)
{
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(scrollStep);
    auto info = peer->GetEventInfo();
    CHECK_NULL_VOID(info);
    LOGE("Arkoala method AxisEventAccessor.SetScrollStep doesn't have sense. Not implemented...");
}
Callback_Void GetPropagationImpl(Ark_AxisEvent peer)
{
    CHECK_NULL_RETURN(peer, {});
    auto callback = CallbackKeeper::DefineReverseCallback<Callback_Void>([peer]() {
        AxisInfo* info = peer->GetEventInfo();
        CHECK_NULL_VOID(info);
        info->SetStopPropagation(false);
    });
    return callback;
}
void SetPropagationImpl(Ark_AxisEvent peer,
                        const Callback_Void* propagation)
{
    CHECK_NULL_VOID(peer);
    auto info = peer->GetEventInfo();
    CHECK_NULL_VOID(info);
    LOGE("Arkoala method AxisEventAccessor.SetPropagation doesn't have sense. Not implemented...");
}
} // AxisEventAccessor
const GENERATED_ArkUIAxisEventAccessor* GetAxisEventAccessor()
{
    static const GENERATED_ArkUIAxisEventAccessor AxisEventAccessorImpl {
        AxisEventAccessor::DestroyPeerImpl,
        AxisEventAccessor::CtorImpl,
        AxisEventAccessor::GetFinalizerImpl,
        AxisEventAccessor::GetHorizontalAxisValueImpl,
        AxisEventAccessor::GetVerticalAxisValueImpl,
        AxisEventAccessor::GetActionImpl,
        AxisEventAccessor::SetActionImpl,
        AxisEventAccessor::GetDisplayXImpl,
        AxisEventAccessor::SetDisplayXImpl,
        AxisEventAccessor::GetDisplayYImpl,
        AxisEventAccessor::SetDisplayYImpl,
        AxisEventAccessor::GetWindowXImpl,
        AxisEventAccessor::SetWindowXImpl,
        AxisEventAccessor::GetWindowYImpl,
        AxisEventAccessor::SetWindowYImpl,
        AxisEventAccessor::GetXImpl,
        AxisEventAccessor::SetXImpl,
        AxisEventAccessor::GetYImpl,
        AxisEventAccessor::SetYImpl,
        AxisEventAccessor::GetScrollStepImpl,
        AxisEventAccessor::SetScrollStepImpl,
        AxisEventAccessor::GetPropagationImpl,
        AxisEventAccessor::SetPropagationImpl,
    };
    return &AxisEventAccessorImpl;
}

}
