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
    const float DEFAULT_VALUE = 0.0f;
} // namespace
void DestroyPeerImpl(Ark_HoverEvent peer)
{
    PeerUtils::DestroyPeer(peer);
}
Ark_HoverEvent ConstructImpl()
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
              const Opt_Number* x)
{
    CHECK_NULL_VOID(peer);
    auto info = peer->GetEventInfo();
    CHECK_NULL_VOID(info);
    auto location = info->GetLocalLocation();
    auto optX = x ? Converter::OptConvertPtr<float>(x) : std::nullopt;
    auto value = PipelineBase::Vp2PxWithCurrentDensity(optX.value_or(DEFAULT_VALUE));
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
              const Opt_Number* y)
{
    CHECK_NULL_VOID(peer);
    auto info = peer->GetEventInfo();
    CHECK_NULL_VOID(info);
    auto location = info->GetLocalLocation();
    auto optY = y ? Converter::OptConvertPtr<float>(y) : std::nullopt;
    auto value = PipelineBase::Vp2PxWithCurrentDensity(optY.value_or(DEFAULT_VALUE));
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
                    const Opt_Number* windowX)
{
    CHECK_NULL_VOID(peer);
    const auto info = peer->GetEventInfo();
    CHECK_NULL_VOID(info);
    auto location = info->GetGlobalLocation();
    auto optWX = windowX ? Converter::OptConvertPtr<float>(windowX) : std::nullopt;
    const auto value = PipelineBase::Vp2PxWithCurrentDensity(optWX.value_or(DEFAULT_VALUE));
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
                    const Opt_Number* windowY)
{
    CHECK_NULL_VOID(peer);
    const auto info = peer->GetEventInfo();
    CHECK_NULL_VOID(info);
    auto location = info->GetGlobalLocation();
    auto optWY = windowY ? Converter::OptConvertPtr<float>(windowY) : std::nullopt;
    const auto value = PipelineBase::Vp2PxWithCurrentDensity(optWY.value_or(DEFAULT_VALUE));
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
                     const Opt_Number* displayX)
{
    CHECK_NULL_VOID(peer);
    const auto info = peer->GetEventInfo();
    CHECK_NULL_VOID(info);
    auto location = info->GetScreenLocation();
    auto optDX = displayX ? Converter::OptConvertPtr<float>(displayX) : std::nullopt;
    const auto value = PipelineBase::Vp2PxWithCurrentDensity(optDX.value_or(DEFAULT_VALUE));
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
                     const Opt_Number* displayY)
{
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(displayY);
    const auto info = peer->GetEventInfo();
    CHECK_NULL_VOID(info);
    auto location = info->GetScreenLocation();
    auto optDY = displayY ? Converter::OptConvertPtr<float>(displayY) : std::nullopt;
    const auto value = PipelineBase::Vp2PxWithCurrentDensity(optDY.value_or(DEFAULT_VALUE));
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
        HoverEventAccessor::ConstructImpl,
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
