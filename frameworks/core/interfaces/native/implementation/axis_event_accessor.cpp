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
            case ARK_AXIS_ACTION_CANCEL: dst = AxisAction::CANCEL; break;
            default: LOGE("Unexpected enum value in Ark_AxisAction: %{public}d", src);
        }
    }
} // namespace OHOS::Ace::NG::Converter

namespace OHOS::Ace::NG::GeneratedModifier {
namespace AxisEventAccessor {
namespace {
    const Opt_Float64 INVALID_OPT_FLOAT64 = Converter::ArkValue<Opt_Float64>();
    const double DEFAULT_VALUE = 0.0;
} // namespace
void DestroyPeerImpl(Ark_AxisEvent peer)
{
    PeerUtils::DestroyPeer(peer);
}
Ark_AxisEvent ConstructImpl()
{
    return PeerUtils::CreatePeer<AxisEventPeer>();
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Ark_Float64 GetHorizontalAxisValueImpl(Ark_AxisEvent peer)
{
    const auto errValue = Converter::ArkValue<Ark_Float64>(0);
    CHECK_NULL_RETURN(peer, errValue);
    AxisInfo* event = peer->GetEventInfo();
    CHECK_NULL_RETURN(event, errValue);

    double value = event->GetHorizontalAxis();
    return Converter::ArkValue<Ark_Float64>(value);
}
Ark_Float64 GetVerticalAxisValueImpl(Ark_AxisEvent peer)
{
    const auto errValue = Converter::ArkValue<Ark_Float64>(0);
    CHECK_NULL_RETURN(peer, errValue);
    AxisInfo* event = peer->GetEventInfo();
    CHECK_NULL_RETURN(event, errValue);

    double value = event->GetVerticalAxis();
    return Converter::ArkValue<Ark_Float64>(value);
}
Ark_Boolean HasAxisImpl(Ark_AxisEvent peer,
                        Ark_AxisType axisType)
{
    CHECK_NULL_RETURN(peer, false);
    AxisInfo* event = peer->GetEventInfo();
    CHECK_NULL_RETURN(event, false);
    return Converter::ArkValue<Ark_Boolean>(event->HasAxis(static_cast<AxisType>(axisType)));
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
Ark_Float64 GetDisplayXImpl(Ark_AxisEvent peer)
{
    const auto errValue = Converter::ArkValue<Ark_Float64>(0);
    CHECK_NULL_RETURN(peer, errValue);
    AxisInfo* event = peer->GetEventInfo();
    CHECK_NULL_RETURN(event, errValue);
    const auto& screenLocation = event->GetScreenLocation();
    const auto value = PipelineBase::Px2VpWithCurrentDensity(screenLocation.GetX());
    return Converter::ArkValue<Ark_Float64>(value);
}
void SetDisplayXImpl(Ark_AxisEvent peer, Ark_Float64 displayX)
{
    CHECK_NULL_VOID(peer);
    auto info = peer->GetEventInfo();
    CHECK_NULL_VOID(info);
    auto screenLocation = info->GetScreenLocation();
    const auto animation = screenLocation.GetXAnimationOption();
    auto value = Converter::Convert<double>(displayX);
    auto xConvert = PipelineBase::Vp2PxWithCurrentDensity(value);
    screenLocation.SetX(xConvert, animation);
    info->SetScreenLocation(screenLocation);
}
Ark_Float64 GetDisplayYImpl(Ark_AxisEvent peer)
{
    const auto errValue = Converter::ArkValue<Ark_Float64>(0);
    CHECK_NULL_RETURN(peer, errValue);
    AxisInfo* event = peer->GetEventInfo();
    CHECK_NULL_RETURN(event, errValue);
    const auto& screenLocation = event->GetScreenLocation();
    const auto value = PipelineBase::Px2VpWithCurrentDensity(screenLocation.GetY());
    return Converter::ArkValue<Ark_Float64>(value);
}
void SetDisplayYImpl(Ark_AxisEvent peer, Ark_Float64 displayY)
{
    CHECK_NULL_VOID(peer);
    auto info = peer->GetEventInfo();
    CHECK_NULL_VOID(info);
    auto screenLocation = info->GetScreenLocation();
    const auto animation = screenLocation.GetXAnimationOption();
    auto value = Converter::Convert<double>(displayY);
    auto yConvert = PipelineBase::Vp2PxWithCurrentDensity(value);
    screenLocation.SetY(yConvert, animation);
    info->SetScreenLocation(screenLocation);
}
Ark_Float64 GetWindowXImpl(Ark_AxisEvent peer)
{
    const auto errValue = Converter::ArkValue<Ark_Float64>(0);
    CHECK_NULL_RETURN(peer, errValue);
    auto info = peer->GetEventInfo();
    CHECK_NULL_RETURN(info, errValue);
    const auto& globalLocation = info->GetGlobalLocation();
    const auto value = PipelineBase::Px2VpWithCurrentDensity(globalLocation.GetX());
    return Converter::ArkValue<Ark_Float64>(value);
}
void SetWindowXImpl(Ark_AxisEvent peer, Ark_Float64 windowX)
{
    CHECK_NULL_VOID(peer);
    auto info = peer->GetEventInfo();
    CHECK_NULL_VOID(info);
    auto globalLocation = info->GetGlobalLocation();
    const auto animation = globalLocation.GetXAnimationOption();
    auto value = Converter::Convert<double>(windowX);
    auto xConvert = PipelineBase::Vp2PxWithCurrentDensity(value);
    globalLocation.SetX(xConvert, animation);
    info->SetGlobalLocation(globalLocation);
}
Ark_Float64 GetWindowYImpl(Ark_AxisEvent peer)
{
    const auto errValue = Converter::ArkValue<Ark_Float64>(0);
    CHECK_NULL_RETURN(peer, errValue);
    auto info = peer->GetEventInfo();
    CHECK_NULL_RETURN(info, errValue);
    const auto& globalLocation = info->GetGlobalLocation();
    const auto value = PipelineBase::Px2VpWithCurrentDensity(globalLocation.GetY());
    return Converter::ArkValue<Ark_Float64>(value);
}
void SetWindowYImpl(Ark_AxisEvent peer, Ark_Float64 windowY)
{
    CHECK_NULL_VOID(peer);
    auto info = peer->GetEventInfo();
    CHECK_NULL_VOID(info);
    auto globalLocation = info->GetGlobalLocation();
    const auto animation = globalLocation.GetYAnimationOption();
    auto value = Converter::Convert<double>(windowY);
    auto yConvert = PipelineBase::Vp2PxWithCurrentDensity(value);
    globalLocation.SetY(yConvert, animation);
    info->SetGlobalLocation(globalLocation);
}
Ark_Float64 GetXImpl(Ark_AxisEvent peer)
{
    const auto errValue = Converter::ArkValue<Ark_Float64>(0);
    CHECK_NULL_RETURN(peer, errValue);
    auto info = peer->GetEventInfo();
    CHECK_NULL_RETURN(info, errValue);
    const auto& localLocation = info->GetLocalLocation();
    const auto value = PipelineBase::Px2VpWithCurrentDensity(localLocation.GetX());
    return Converter::ArkValue<Ark_Float64>(value);
}
void SetXImpl(Ark_AxisEvent peer, Ark_Float64 x)
{
    CHECK_NULL_VOID(peer);
    auto info = peer->GetEventInfo();
    CHECK_NULL_VOID(info);
    auto localLocation = info->GetLocalLocation();
    const auto animation = localLocation.GetXAnimationOption();
    auto value = Converter::Convert<double>(x);
    auto xConvert = PipelineBase::Vp2PxWithCurrentDensity(value);
    localLocation.SetX(xConvert, animation);
    info->SetLocalLocation(localLocation);
}
Ark_Float64 GetYImpl(Ark_AxisEvent peer)
{
    const auto errValue = Converter::ArkValue<Ark_Float64>(0);
    CHECK_NULL_RETURN(peer, errValue);
    auto info = peer->GetEventInfo();
    CHECK_NULL_RETURN(info, errValue);
    const auto& localLocation = info->GetLocalLocation();
    const auto value = PipelineBase::Px2VpWithCurrentDensity(localLocation.GetY());
    return Converter::ArkValue<Ark_Float64>(value);
}
void SetYImpl(Ark_AxisEvent peer, Ark_Float64 y)
{
    CHECK_NULL_VOID(peer);
    auto info = peer->GetEventInfo();
    CHECK_NULL_VOID(info);
    auto localLocation = info->GetLocalLocation();
    const auto animation = localLocation.GetYAnimationOption();
    auto value = Converter::Convert<double>(y);
    auto yConvert = PipelineBase::Vp2PxWithCurrentDensity(value);
    localLocation.SetY(yConvert, animation);
    info->SetLocalLocation(localLocation);
}
Opt_Int32 GetScrollStepImpl(Ark_AxisEvent peer)
{
    const auto errValue = Converter::ArkValue<Opt_Int32>();
    CHECK_NULL_RETURN(peer, errValue);
    auto info = peer->GetEventInfo();
    CHECK_NULL_RETURN(info, errValue);
    return Converter::ArkValue<Opt_Int32>(info->GetScrollStep());
}
void SetScrollStepImpl(Ark_AxisEvent peer,
                       const Opt_Int32* scrollStep)
{
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(scrollStep);
    auto info = peer->GetEventInfo();
    CHECK_NULL_VOID(info);
    LOGE("Arkoala method AxisEventAccessor.SetScrollStep doesn't have sense. Not implemented...");
}
void PropagationImpl(Ark_AxisEvent peer)
{
    CHECK_NULL_VOID(peer);
    AxisInfo* info = peer->GetEventInfo();
    CHECK_NULL_VOID(info);
    info->SetStopPropagation(false);
}
Opt_Float64 GetGlobalDisplayXImpl(Ark_AxisEvent peer)
{
    CHECK_NULL_RETURN(peer, INVALID_OPT_FLOAT64);
    AxisInfo* event = peer->GetEventInfo();
    CHECK_NULL_RETURN(event, INVALID_OPT_FLOAT64);
    const auto& globalDisplayLocation = event->GetGlobalDisplayLocation();
    const auto value = PipelineBase::Px2VpWithCurrentDensity(globalDisplayLocation.GetX());
    return Converter::ArkValue<Opt_Float64>(value);
}
void SetGlobalDisplayXImpl(Ark_AxisEvent peer,
                           const Opt_Float64* globalDisplayX)
{
    CHECK_NULL_VOID(peer);
    auto info = peer->GetEventInfo();
    CHECK_NULL_VOID(info);
    auto globalDisplayLocation = info->GetGlobalDisplayLocation();
    const auto animation = globalDisplayLocation.GetXAnimationOption();
    auto value = Converter::OptConvertPtr<double>(globalDisplayX);
    auto xConvert = PipelineBase::Vp2PxWithCurrentDensity(value.value_or(DEFAULT_VALUE));
    globalDisplayLocation.SetX(xConvert, animation);
    info->SetGlobalDisplayLocation(globalDisplayLocation);
}
Opt_Float64 GetGlobalDisplayYImpl(Ark_AxisEvent peer)
{
    CHECK_NULL_RETURN(peer, INVALID_OPT_FLOAT64);
    AxisInfo* event = peer->GetEventInfo();
    CHECK_NULL_RETURN(event, INVALID_OPT_FLOAT64);
    const auto& globalDisplayLocation = event->GetGlobalDisplayLocation();
    const auto value = PipelineBase::Px2VpWithCurrentDensity(globalDisplayLocation.GetY());
    return Converter::ArkValue<Opt_Float64>(value);
}
void SetGlobalDisplayYImpl(Ark_AxisEvent peer,
                           const Opt_Float64* globalDisplayY)
{
    CHECK_NULL_VOID(peer);
    auto info = peer->GetEventInfo();
    CHECK_NULL_VOID(info);
    auto globalDisplayLocation = info->GetGlobalDisplayLocation();
    const auto animation = globalDisplayLocation.GetYAnimationOption();
    auto value = Converter::OptConvertPtr<double>(globalDisplayY);
    auto yConvert = PipelineBase::Vp2PxWithCurrentDensity(value.value_or(DEFAULT_VALUE));
    globalDisplayLocation.SetY(yConvert, animation);
    info->SetGlobalDisplayLocation(globalDisplayLocation);
}
} // AxisEventAccessor
const GENERATED_ArkUIAxisEventAccessor* GetAxisEventAccessor()
{
    static const GENERATED_ArkUIAxisEventAccessor AxisEventAccessorImpl {
        AxisEventAccessor::DestroyPeerImpl,
        AxisEventAccessor::ConstructImpl,
        AxisEventAccessor::GetFinalizerImpl,
        AxisEventAccessor::GetHorizontalAxisValueImpl,
        AxisEventAccessor::GetVerticalAxisValueImpl,
        AxisEventAccessor::HasAxisImpl,
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
        AxisEventAccessor::PropagationImpl,
        AxisEventAccessor::GetGlobalDisplayXImpl,
        AxisEventAccessor::SetGlobalDisplayXImpl,
        AxisEventAccessor::GetGlobalDisplayYImpl,
        AxisEventAccessor::SetGlobalDisplayYImpl,
    };
    return &AxisEventAccessorImpl;
}

}
