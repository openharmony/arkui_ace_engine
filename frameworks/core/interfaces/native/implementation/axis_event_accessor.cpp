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

#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/interfaces/native/implementation/axis_event_peer.h"
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
    static const Ark_Number INVALID_ARK_NUMBER = Converter::ArkValue<Ark_Number>(0);
    static const Opt_Number INVALID_OPT_NUMBER = Converter::ArkValue<Opt_Number>();
} // namespace
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
    CHECK_NULL_RETURN(peer, INVALID_ARK_NUMBER);
    const auto info = peer->GetEventInfo();
    CHECK_NULL_RETURN(info, INVALID_ARK_NUMBER);
    return Converter::ArkValue<Ark_Number>(info->GetHorizontalAxis());
}
Ark_Number GetVerticalAxisValueImpl(Ark_AxisEvent peer)
{
    CHECK_NULL_RETURN(peer, INVALID_ARK_NUMBER);
    const auto info = peer->GetEventInfo();
    CHECK_NULL_RETURN(info, INVALID_ARK_NUMBER);
    return Converter::ArkValue<Ark_Number>(info->GetVerticalAxis());
}
Ark_AxisAction GetActionImpl(Ark_AxisEvent peer)
{
    auto invalidAction = static_cast<Ark_AxisAction>(-1);
    CHECK_NULL_RETURN(peer, invalidAction);
    const auto info = peer->GetEventInfo();
    CHECK_NULL_RETURN(info, invalidAction);
    return Converter::ArkValue<Ark_AxisAction>(info->GetAction());
}
void SetActionImpl(Ark_AxisEvent peer,
                   Ark_AxisAction action)
{
    CHECK_NULL_VOID(peer);
    const auto info = peer->GetEventInfo();
    CHECK_NULL_VOID(info);
    info->SetAction(Converter::OptConvert<AxisAction>(action).value_or(AxisAction::NONE));
}
Ark_Number GetDisplayXImpl(Ark_AxisEvent peer)
{
    CHECK_NULL_RETURN(peer, INVALID_ARK_NUMBER);
    const auto info = peer->GetEventInfo();
    CHECK_NULL_RETURN(info, INVALID_ARK_NUMBER);
    const auto value = PipelineBase::Px2VpWithCurrentDensity(info->GetScreenLocation().GetX());
    return Converter::ArkValue<Ark_Number>(value);
}
void SetDisplayXImpl(Ark_AxisEvent peer,
                     const Ark_Number* displayX)
{
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(displayX);
    const auto info = peer->GetEventInfo();
    CHECK_NULL_VOID(info);
    auto location = info->GetScreenLocation();
    const auto value = PipelineBase::Vp2PxWithCurrentDensity(Converter::Convert<float>(*displayX));
    location.SetX(value, location.GetXAnimationOption());
    info->SetScreenLocation(location);
}
Ark_Number GetDisplayYImpl(Ark_AxisEvent peer)
{
    CHECK_NULL_RETURN(peer, INVALID_ARK_NUMBER);
    const auto info = peer->GetEventInfo();
    CHECK_NULL_RETURN(info, INVALID_ARK_NUMBER);
    const auto value = PipelineBase::Px2VpWithCurrentDensity(info->GetScreenLocation().GetY());
    return Converter::ArkValue<Ark_Number>(value);
}
void SetDisplayYImpl(Ark_AxisEvent peer,
                     const Ark_Number* displayY)
{
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(displayY);
    const auto info = peer->GetEventInfo();
    CHECK_NULL_VOID(info);
    auto location = info->GetScreenLocation();
    const auto value = PipelineBase::Vp2PxWithCurrentDensity(Converter::Convert<float>(*displayY));
    location.SetY(value, location.GetYAnimationOption());
    info->SetScreenLocation(location);
}
Ark_Number GetWindowXImpl(Ark_AxisEvent peer)
{
    CHECK_NULL_RETURN(peer, INVALID_ARK_NUMBER);
    const auto info = peer->GetEventInfo();
    CHECK_NULL_RETURN(info, INVALID_ARK_NUMBER);
    const auto value = PipelineBase::Px2VpWithCurrentDensity(info->GetGlobalLocation().GetX());
    return Converter::ArkValue<Ark_Number>(value);
}
void SetWindowXImpl(Ark_AxisEvent peer,
                    const Ark_Number* windowX)
{
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(windowX);
    const auto info = peer->GetEventInfo();
    CHECK_NULL_VOID(info);
    auto location = info->GetGlobalLocation();
    const auto value = PipelineBase::Vp2PxWithCurrentDensity(Converter::Convert<float>(*windowX));
    location.SetX(value, location.GetXAnimationOption());
    info->SetGlobalLocation(location);
}
Ark_Number GetWindowYImpl(Ark_AxisEvent peer)
{
    CHECK_NULL_RETURN(peer, INVALID_ARK_NUMBER);
    const auto info = peer->GetEventInfo();
    CHECK_NULL_RETURN(info, INVALID_ARK_NUMBER);
    const auto value = PipelineBase::Px2VpWithCurrentDensity(info->GetGlobalLocation().GetY());
    return Converter::ArkValue<Ark_Number>(value);
}
void SetWindowYImpl(Ark_AxisEvent peer,
                    const Ark_Number* windowY)
{
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(windowY);
    const auto info = peer->GetEventInfo();
    CHECK_NULL_VOID(info);
    auto location = info->GetGlobalLocation();
    const auto value = PipelineBase::Vp2PxWithCurrentDensity(Converter::Convert<float>(*windowY));
    location.SetY(value, location.GetYAnimationOption());
    info->SetGlobalLocation(location);
}
Ark_Number GetXImpl(Ark_AxisEvent peer)
{
    CHECK_NULL_RETURN(peer, INVALID_ARK_NUMBER);
    const auto info = peer->GetEventInfo();
    CHECK_NULL_RETURN(info, INVALID_ARK_NUMBER);
    const auto value = PipelineBase::Px2VpWithCurrentDensity(info->GetLocalLocation().GetX());
    return Converter::ArkValue<Ark_Number>(value);
}
void SetXImpl(Ark_AxisEvent peer,
              const Ark_Number* x)
{
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(x);
    auto info = peer->GetEventInfo();
    CHECK_NULL_VOID(info);
    auto location = info->GetLocalLocation();
    auto value = PipelineBase::Vp2PxWithCurrentDensity(Converter::Convert<float>(*x));
    location.SetX(value, location.GetXAnimationOption());
    info->SetLocalLocation(location);
}
Ark_Number GetYImpl(Ark_AxisEvent peer)
{
    CHECK_NULL_RETURN(peer, INVALID_ARK_NUMBER);
    const auto info = peer->GetEventInfo();
    CHECK_NULL_RETURN(info, INVALID_ARK_NUMBER);
    const auto value = PipelineBase::Px2VpWithCurrentDensity(info->GetLocalLocation().GetY());
    return Converter::ArkValue<Ark_Number>(value);
}
void SetYImpl(Ark_AxisEvent peer,
              const Ark_Number* y)
{
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(y);
    auto info = peer->GetEventInfo();
    CHECK_NULL_VOID(info);
    auto location = info->GetLocalLocation();
    auto value = PipelineBase::Vp2PxWithCurrentDensity(Converter::Convert<float>(*y));
    location.SetY(value, location.GetYAnimationOption());
    info->SetLocalLocation(location);
}
Opt_Number GetScrollStepImpl(Ark_AxisEvent peer)
{
    CHECK_NULL_RETURN(peer, INVALID_OPT_NUMBER);
    const auto info = peer->GetEventInfo();
    CHECK_NULL_RETURN(info, INVALID_OPT_NUMBER);
    return Converter::ArkValue<Opt_Number>(info->GetScrollStep());
}
void SetScrollStepImpl(Ark_AxisEvent peer,
                       const Ark_Number* scrollStep)
{
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(scrollStep);
    auto info = peer->GetEventInfo();
    CHECK_NULL_VOID(info);
    info->SetScrollStep(Converter::Convert<int32_t>(*scrollStep));
}
Callback_Void GetPropagationImpl(Ark_AxisEvent peer)
{
    CHECK_NULL_RETURN(peer, {});
    auto callback = CallbackKeeper::DefineReverseCallback<Callback_Void>([peer]() {
        auto info = peer->GetEventInfo();
        CHECK_NULL_VOID(info);
        info->SetStopPropagation(true);
    });
    return callback;
}
void SetPropagationImpl(Ark_AxisEvent peer,
                        const Callback_Void* propagation)
{
    LOGE("AxisEventAccessor::SetStopPropagationImpl - we can only GET stopPropagation callback");
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
