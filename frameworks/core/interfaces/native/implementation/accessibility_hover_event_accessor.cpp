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
const Ark_Int32 DefaultValueInt32 = Converter::ArkValue<Ark_Int32>(0);
}  // namespace
void DestroyPeerImpl(AccessibilityHoverEventPeer* peer)
{
    delete peer;
}
Ark_NativePointer CtorImpl()
{
    return new AccessibilityHoverEventPeer();
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Ark_NativePointer GetTypeImpl(AccessibilityHoverEventPeer* peer)
{
    LOGE("ARKOALA AccessibilityHoverEventAccessor::GetTypeImpl is not implemented.");
    return nullptr;
}
void SetTypeImpl(AccessibilityHoverEventPeer* peer,
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
Ark_Int32 GetXImpl(AccessibilityHoverEventPeer* peer)
{
    CHECK_NULL_RETURN(peer, DefaultValueInt32);
    auto info = peer->GetEventInfo();
    CHECK_NULL_RETURN(info, DefaultValueInt32);
    auto px = PipelineBase::Vp2PxWithCurrentDensity(info->GetLocalLocation().GetX());
    LOGE("Arkoala method AccessibilityHoverEventAccessor.GetXImpl return int32_t value");
    return Converter::ArkValue<Ark_Int32>(static_cast<int>(px));
}
void SetXImpl(AccessibilityHoverEventPeer* peer,
              const Ark_Number* x)
{
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(x);
    auto info = peer->GetEventInfo();
    CHECK_NULL_VOID(info);
    auto valueX = Converter::OptConvert<float>(*x);
    Offset newLomation(valueX.value_or(0), info->GetLocalLocation().GetY());
    info->SetLocalLocation(newLomation);
}
Ark_Int32 GetYImpl(AccessibilityHoverEventPeer* peer)
{
    CHECK_NULL_RETURN(peer, DefaultValueInt32);
    auto info = peer->GetEventInfo();
    CHECK_NULL_RETURN(info, DefaultValueInt32);
    auto px = PipelineBase::Vp2PxWithCurrentDensity(info->GetLocalLocation().GetY());
    LOGE("Arkoala method AccessibilityHoverEventAccessor.GetYImpl return int32_t value");
    return Converter::ArkValue<Ark_Int32>(static_cast<int>(px));
}
void SetYImpl(AccessibilityHoverEventPeer* peer,
              const Ark_Number* y)
{
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(y);
    auto info = peer->GetEventInfo();
    CHECK_NULL_VOID(info);
    auto valueY = Converter::OptConvert<float>(*y);
    Offset newLomation(info->GetLocalLocation().GetX(), valueY.value_or(0));
    info->SetLocalLocation(newLomation);
}
Ark_Int32 GetDisplayXImpl(AccessibilityHoverEventPeer* peer)
{
    CHECK_NULL_RETURN(peer, DefaultValueInt32);
    auto info = peer->GetEventInfo();
    CHECK_NULL_RETURN(info, DefaultValueInt32);
    auto screenLocation = info->GetScreenLocation();
    auto vp = PipelineBase::Px2VpWithCurrentDensity(screenLocation.GetX());
    LOGE("Arkoala method AccessibilityHoverEventAccessor.GetDisplayXImpl return int32_t value");
    return Converter::ArkValue<Ark_Int32>(static_cast<int>(vp));
}
void SetDisplayXImpl(AccessibilityHoverEventPeer* peer,
                     const Ark_Number* displayX)
{
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(displayX);
    auto info = peer->GetEventInfo();
    CHECK_NULL_VOID(info);
    auto valueX = Converter::Convert<double>(*displayX);
    Offset newLomation(valueX, info->GetScreenLocation().GetY());
    info->SetScreenLocation(newLomation);
}
Ark_Int32 GetDisplayYImpl(AccessibilityHoverEventPeer* peer)
{
    CHECK_NULL_RETURN(peer, DefaultValueInt32);
    auto info = peer->GetEventInfo();
    CHECK_NULL_RETURN(info, DefaultValueInt32);
    auto vp = PipelineBase::Px2VpWithCurrentDensity(info->GetScreenLocation().GetY());
    LOGE("Arkoala method AccessibilityHoverEventAccessor.GetDisplayYImpl return int32_t value");
    return Converter::ArkValue<Ark_Int32>(static_cast<int>(vp));
}
void SetDisplayYImpl(AccessibilityHoverEventPeer* peer,
                     const Ark_Number* displayY)
{
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(displayY);
    auto info = peer->GetEventInfo();
    CHECK_NULL_VOID(info);
    auto valueY = Converter::Convert<double>(*displayY);
    Offset newLomation(info->GetScreenLocation().GetX(), valueY);
    info->SetScreenLocation(newLomation);
}
Ark_Int32 GetWindowXImpl(AccessibilityHoverEventPeer* peer)
{
    CHECK_NULL_RETURN(peer, DefaultValueInt32);
    auto info = peer->GetEventInfo();
    CHECK_NULL_RETURN(info, DefaultValueInt32);
    auto vp = PipelineBase::Px2VpWithCurrentDensity(info->GetGlobalLocation().GetX());
    LOGE("Arkoala method AccessibilityHoverEventAccessor.GetWindowXImpl return int32_t value");
    return Converter::ArkValue<Ark_Int32>(static_cast<int>(vp));
}
void SetWindowXImpl(AccessibilityHoverEventPeer* peer,
                    const Ark_Number* windowX)
{
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(windowX);
    auto info = peer->GetEventInfo();
    CHECK_NULL_VOID(info);
    auto valueX = Converter::Convert<double>(*windowX);
    Offset newLomation(valueX, info->GetGlobalLocation().GetY());
    info->SetGlobalLocation(newLomation);
}
Ark_Int32 GetWindowYImpl(AccessibilityHoverEventPeer* peer)
{
    CHECK_NULL_RETURN(peer, DefaultValueInt32);
    auto info = peer->GetEventInfo();
    CHECK_NULL_RETURN(info, DefaultValueInt32);
    auto vp = PipelineBase::Px2VpWithCurrentDensity(info->GetGlobalLocation().GetY());
    LOGE("Arkoala method AccessibilityHoverEventAccessor.GetWindowYImpl return int32_t value");
    return Converter::ArkValue<Ark_Int32>(static_cast<int>(vp));
}
void SetWindowYImpl(AccessibilityHoverEventPeer* peer,
                    const Ark_Number* windowY)
{
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(windowY);
    auto info = peer->GetEventInfo();
    CHECK_NULL_VOID(info);
    auto valueY = Converter::Convert<double>(*windowY);
    Offset newLomation(info->GetGlobalLocation().GetX(), valueY);
    info->SetGlobalLocation(newLomation);
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
