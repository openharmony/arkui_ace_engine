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

#include "core/components_ng/base/frame_node.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/interfaces/native/implementation/hover_event_peer.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace HoverEventAccessor {
namespace {
    const Opt_Number INVALID_OPT_NUMBER = Converter::ArkValue<Opt_Number>();
} // namespace
void DestroyPeerImpl(Ark_HoverEvent peer)
{
    PeerUtils::DestroyPeer(peer);
}
Ark_HoverEvent CtorImpl()
{
    return PeerUtils::CreatePeer<HoverEventPeer>();
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Opt_Number GetXImpl(Ark_HoverEvent peer)
{
    CHECK_NULL_RETURN(peer, INVALID_OPT_NUMBER);
    const auto info = peer->GetEventInfo();
    CHECK_NULL_RETURN(info, INVALID_OPT_NUMBER);
    const auto value = PipelineBase::Px2VpWithCurrentDensity(info->GetLocalLocation().GetX());
    return Converter::ArkValue<Opt_Number>(value);
}
void SetXImpl(Ark_HoverEvent peer,
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
Opt_Number GetYImpl(Ark_HoverEvent peer)
{
    CHECK_NULL_RETURN(peer, INVALID_OPT_NUMBER);
    const auto info = peer->GetEventInfo();
    CHECK_NULL_RETURN(info, INVALID_OPT_NUMBER);
    const auto value = PipelineBase::Px2VpWithCurrentDensity(info->GetLocalLocation().GetY());
    return Converter::ArkValue<Opt_Number>(value);
}
void SetYImpl(Ark_HoverEvent peer,
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
Opt_Number GetWindowXImpl(Ark_HoverEvent peer)
{
    CHECK_NULL_RETURN(peer, INVALID_OPT_NUMBER);
    const auto info = peer->GetEventInfo();
    CHECK_NULL_RETURN(info, INVALID_OPT_NUMBER);
    const auto value = PipelineBase::Px2VpWithCurrentDensity(info->GetGlobalLocation().GetX());
    return Converter::ArkValue<Opt_Number>(value);
}
void SetWindowXImpl(Ark_HoverEvent peer,
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
Opt_Number GetWindowYImpl(Ark_HoverEvent peer)
{
    CHECK_NULL_RETURN(peer, INVALID_OPT_NUMBER);
    const auto info = peer->GetEventInfo();
    CHECK_NULL_RETURN(info, INVALID_OPT_NUMBER);
    const auto value = PipelineBase::Px2VpWithCurrentDensity(info->GetGlobalLocation().GetY());
    return Converter::ArkValue<Opt_Number>(value);
}
void SetWindowYImpl(Ark_HoverEvent peer,
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
Opt_Number GetDisplayXImpl(Ark_HoverEvent peer)
{
    CHECK_NULL_RETURN(peer, INVALID_OPT_NUMBER);
    const auto info = peer->GetEventInfo();
    CHECK_NULL_RETURN(info, INVALID_OPT_NUMBER);
    const auto value = PipelineBase::Px2VpWithCurrentDensity(info->GetScreenLocation().GetX());
    return Converter::ArkValue<Opt_Number>(value);
}
void SetDisplayXImpl(Ark_HoverEvent peer,
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
Opt_Number GetDisplayYImpl(Ark_HoverEvent peer)
{
    CHECK_NULL_RETURN(peer, INVALID_OPT_NUMBER);
    const auto info = peer->GetEventInfo();
    CHECK_NULL_RETURN(info, INVALID_OPT_NUMBER);
    const auto value = PipelineBase::Px2VpWithCurrentDensity(info->GetScreenLocation().GetY());
    return Converter::ArkValue<Opt_Number>(value);
}
void SetDisplayYImpl(Ark_HoverEvent peer,
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
Callback_Void GetStopPropagationImpl(Ark_HoverEvent peer)
{
    CHECK_NULL_RETURN(peer, {});
    auto callback = CallbackKeeper::DefineReverseCallback<Callback_Void>([peer]() {
        HoverInfo* info = peer->GetEventInfo();
        CHECK_NULL_VOID(info);
        info->SetStopPropagation(true);
    });
    return callback;
}
void SetStopPropagationImpl(Ark_HoverEvent peer,
                            const Callback_Void* stopPropagation)
{
    LOGE("HoverEventAccessor::SetStopPropagationImpl we can only GET stopPropagation callback");
}
} // HoverEventAccessor
const GENERATED_ArkUIHoverEventAccessor* GetHoverEventAccessor()
{
    static const GENERATED_ArkUIHoverEventAccessor HoverEventAccessorImpl {
        HoverEventAccessor::DestroyPeerImpl,
        HoverEventAccessor::CtorImpl,
        HoverEventAccessor::GetFinalizerImpl,
        HoverEventAccessor::GetXImpl,
        HoverEventAccessor::SetXImpl,
        HoverEventAccessor::GetYImpl,
        HoverEventAccessor::SetYImpl,
        HoverEventAccessor::GetWindowXImpl,
        HoverEventAccessor::SetWindowXImpl,
        HoverEventAccessor::GetWindowYImpl,
        HoverEventAccessor::SetWindowYImpl,
        HoverEventAccessor::GetDisplayXImpl,
        HoverEventAccessor::SetDisplayXImpl,
        HoverEventAccessor::GetDisplayYImpl,
        HoverEventAccessor::SetDisplayYImpl,
        HoverEventAccessor::GetStopPropagationImpl,
        HoverEventAccessor::SetStopPropagationImpl,
    };
    return &HoverEventAccessorImpl;
}

}
