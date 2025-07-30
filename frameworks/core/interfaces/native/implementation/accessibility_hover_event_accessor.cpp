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
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/interfaces/native/implementation/accessiblt_hover_event_peer.h"
#include "core/interfaces/native/utility/validators.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace AccessibilityHoverEventAccessor {
namespace {
const Ark_Number DefaultValueArkNumber = Converter::ArkValue<Ark_Number>(0);
} // namespace
void DestroyPeerImpl(Ark_AccessibilityHoverEvent peer)
{
    PeerUtils::DestroyPeer(peer);
}
Ark_AccessibilityHoverEvent CtorImpl()
{
    return PeerUtils::CreatePeer<AccessibilityHoverEventPeer>();
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Ark_AccessibilityHoverType GetTypeImpl(Ark_AccessibilityHoverEvent peer)
{
    const auto errValue = static_cast<Ark_AccessibilityHoverType>(-1);
    CHECK_NULL_RETURN(peer, errValue);
    AccessibilityHoverInfo* info = peer->GetEventInfo();
    CHECK_NULL_RETURN(info, errValue);
    return Converter::ArkValue<Ark_AccessibilityHoverType>(info->GetActionType());
}
void SetTypeImpl(Ark_AccessibilityHoverEvent peer,
                 Ark_AccessibilityHoverType type)
{
    CHECK_NULL_VOID(peer);
    auto info = peer->GetEventInfo();
    CHECK_NULL_VOID(info);
    auto optValue = Converter::OptConvert<AccessibilityHoverAction>(type);
    if (optValue.has_value()) {
        info->SetActionType(optValue.value());
    }
}
Ark_Number GetXImpl(Ark_AccessibilityHoverEvent peer)
{
    CHECK_NULL_RETURN(peer, DefaultValueArkNumber);
    auto info = peer->GetEventInfo();
    CHECK_NULL_RETURN(info, DefaultValueArkNumber);
    const auto& localLocation = info->GetLocalLocation();
    LOGE("Arkoala method AccessibilityHoverEventAccessor.GetXImpl return int32_t value");
    const auto value = PipelineBase::Px2VpWithCurrentDensity(localLocation.GetX());
    return Converter::ArkValue<Ark_Number>(static_cast<int32_t>(value));
}
void SetXImpl(Ark_AccessibilityHoverEvent peer,
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
Ark_Number GetYImpl(Ark_AccessibilityHoverEvent peer)
{
    CHECK_NULL_RETURN(peer, DefaultValueArkNumber);
    auto info = peer->GetEventInfo();
    CHECK_NULL_RETURN(info, DefaultValueArkNumber);
    const auto& localLocation = info->GetLocalLocation();
    LOGE("Arkoala method AccessibilityHoverEventAccessor.GetYImpl return int32_t value");
    const auto value = PipelineBase::Px2VpWithCurrentDensity(localLocation.GetY());
    return Converter::ArkValue<Ark_Number>(static_cast<int32_t>(value));
}
void SetYImpl(Ark_AccessibilityHoverEvent peer,
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
Ark_Number GetDisplayXImpl(Ark_AccessibilityHoverEvent peer)
{
    CHECK_NULL_RETURN(peer, DefaultValueArkNumber);
    auto info = peer->GetEventInfo();
    CHECK_NULL_RETURN(info, DefaultValueArkNumber);
    const auto& screenLocation = info->GetScreenLocation();
    LOGE("Arkoala method AccessibilityHoverEventAccessor.GetDisplayXImpl return int32_t value");
    const auto value = PipelineBase::Px2VpWithCurrentDensity(screenLocation.GetX());
    return Converter::ArkValue<Ark_Number>(static_cast<int32_t>(value));
}
void SetDisplayXImpl(Ark_AccessibilityHoverEvent peer,
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
Ark_Number GetDisplayYImpl(Ark_AccessibilityHoverEvent peer)
{
    CHECK_NULL_RETURN(peer, DefaultValueArkNumber);
    auto info = peer->GetEventInfo();
    CHECK_NULL_RETURN(info, DefaultValueArkNumber);
    const auto& screenLocation = info->GetScreenLocation();
    LOGE("Arkoala method AccessibilityHoverEventAccessor.GetDisplayYImpl return int32_t value");
    const auto value = PipelineBase::Px2VpWithCurrentDensity(screenLocation.GetY());
    return Converter::ArkValue<Ark_Number>(static_cast<int32_t>(value));
}
void SetDisplayYImpl(Ark_AccessibilityHoverEvent peer,
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
Ark_Number GetWindowXImpl(Ark_AccessibilityHoverEvent peer)
{
    CHECK_NULL_RETURN(peer, DefaultValueArkNumber);
    auto info = peer->GetEventInfo();
    CHECK_NULL_RETURN(info, DefaultValueArkNumber);
    const auto& globalLocation = info->GetGlobalLocation();
    LOGE("Arkoala method AccessibilityHoverEventAccessor.GetWindowXImpl return int32_t value");
    const auto value = PipelineBase::Px2VpWithCurrentDensity(globalLocation.GetX());
    return Converter::ArkValue<Ark_Number>(static_cast<int32_t>(value));
}
void SetWindowXImpl(Ark_AccessibilityHoverEvent peer,
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
Ark_Number GetWindowYImpl(Ark_AccessibilityHoverEvent peer)
{
    CHECK_NULL_RETURN(peer, DefaultValueArkNumber);
    auto info = peer->GetEventInfo();
    CHECK_NULL_RETURN(info, DefaultValueArkNumber);
    const auto& globalLocation = info->GetGlobalLocation();
    LOGE("Arkoala method AccessibilityHoverEventAccessor.GetWindowYImpl return int32_t value");
    const auto value = PipelineBase::Px2VpWithCurrentDensity(globalLocation.GetY());
    return Converter::ArkValue<Ark_Number>(static_cast<int32_t>(value));
}
void SetWindowYImpl(Ark_AccessibilityHoverEvent peer,
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
} // AccessibilityHoverEventAccessor
const GENERATED_ArkUIAccessibilityHoverEventAccessor* GetAccessibilityHoverEventAccessor()
{
    static const GENERATED_ArkUIAccessibilityHoverEventAccessor AccessibilityHoverEventAccessorImpl {
        AccessibilityHoverEventAccessor::DestroyPeerImpl,
        AccessibilityHoverEventAccessor::CtorImpl,
        AccessibilityHoverEventAccessor::GetFinalizerImpl,
        AccessibilityHoverEventAccessor::GetTypeImpl,
        AccessibilityHoverEventAccessor::SetTypeImpl,
        AccessibilityHoverEventAccessor::GetXImpl,
        AccessibilityHoverEventAccessor::SetXImpl,
        AccessibilityHoverEventAccessor::GetYImpl,
        AccessibilityHoverEventAccessor::SetYImpl,
        AccessibilityHoverEventAccessor::GetDisplayXImpl,
        AccessibilityHoverEventAccessor::SetDisplayXImpl,
        AccessibilityHoverEventAccessor::GetDisplayYImpl,
        AccessibilityHoverEventAccessor::SetDisplayYImpl,
        AccessibilityHoverEventAccessor::GetWindowXImpl,
        AccessibilityHoverEventAccessor::SetWindowXImpl,
        AccessibilityHoverEventAccessor::GetWindowYImpl,
        AccessibilityHoverEventAccessor::SetWindowYImpl,
    };
    return &AccessibilityHoverEventAccessorImpl;
}

}
