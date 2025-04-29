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
#include "core/interfaces/native/utility/peer_utils.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "rotation_gesture_interface_peer.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace RotationGestureInterfaceAccessor {
namespace {
    constexpr int32_t DEFAULT_ROTATION_FINGERS = 2;
    constexpr double DEFAULT_ROTATION_ANGLE = 1.0;
    constexpr bool DEFAULT_IS_LIMIT_FINGER_COUNT = false;
}
void DestroyPeerImpl(Ark_RotationGestureInterface peer)
{
    PeerUtils::DestroyPeer(peer);
}
Ark_RotationGestureInterface CtorImpl(const Opt_Literal_Number_angle_fingers* value)
{
    auto peer =  PeerUtils::CreatePeer<RotationGestureInterfacePeer>();
    int32_t fingers = DEFAULT_ROTATION_FINGERS;
    double angle = DEFAULT_ROTATION_ANGLE;
    bool isLimitFingerCount = DEFAULT_IS_LIMIT_FINGER_COUNT;
    std::optional<Ark_Literal_Number_angle_fingers> params = value ? Converter::GetOpt(*value) : std::nullopt;
    if (params.has_value()) {
        fingers = Converter::OptConvert<int32_t>(params->fingers).value_or(DEFAULT_ROTATION_FINGERS);
        fingers = fingers <= DEFAULT_ROTATION_FINGERS ? DEFAULT_ROTATION_FINGERS : fingers;
        auto angleOpt = Converter::OptConvert<float>(params->angle);
        if (angleOpt.has_value()) {
            angle = static_cast<double>(angleOpt.value());
            angle = LessNotEqual(angle, 0.0) ? DEFAULT_ROTATION_ANGLE : angle;
        }
        LOGE("Arkoala method RotationGestureInterfaceAccessor.CtorImpl use default value for isLimitFingerCount");
    }
    peer->gesture = AceType::MakeRefPtr<RotationGesture>(fingers, angle, isLimitFingerCount);
    return peer;
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Ark_RotationGestureInterface OnActionStartImpl(Ark_RotationGestureInterface peer,
                                               const Callback_GestureEvent_Void* event)
{
    CHECK_NULL_RETURN(peer && peer->gesture && event, peer);
    auto onActionStart = [arkCallback = CallbackHelper(*event)](GestureEvent& aceEvent) {
        auto arkEvent = Converter::ArkGestureEventSync(aceEvent);
        arkCallback.InvokeSync(arkEvent.ArkValue());
    };
    peer->gesture->SetOnActionStartId(onActionStart);
    return peer;
}
Ark_RotationGestureInterface OnActionUpdateImpl(Ark_RotationGestureInterface peer,
                                                const Callback_GestureEvent_Void* event)
{
    CHECK_NULL_RETURN(peer && peer->gesture && event, peer);
    auto onActionUpdate = [arkCallback = CallbackHelper(*event)](GestureEvent& aceEvent) {
        const auto arkEvent = Converter::ArkGestureEventSync(aceEvent);
        arkCallback.InvokeSync(arkEvent.ArkValue());
    };
    peer->gesture->SetOnActionUpdateId(onActionUpdate);
    return peer;
}
Ark_RotationGestureInterface OnActionEndImpl(Ark_RotationGestureInterface peer,
                                             const Callback_GestureEvent_Void* event)
{
    CHECK_NULL_RETURN(peer && peer->gesture && event, peer);
    auto onActionEnd = [arkCallback = CallbackHelper(*event)](GestureEvent& aceEvent) {
        const auto arkEvent = Converter::ArkGestureEventSync(aceEvent);
        arkCallback.InvokeSync(arkEvent.ArkValue());
    };
    peer->gesture->SetOnActionEndId(onActionEnd);
    return peer;
}
Ark_RotationGestureInterface OnActionCancel0Impl(Ark_RotationGestureInterface peer,
                                                 const Callback_Void* event)
{
    CHECK_NULL_RETURN(peer && peer->gesture && event, peer);
    auto onActionCancel = [arkCallback = CallbackHelper(*event)](GestureEvent& info) {
        arkCallback.Invoke();
    };
    peer->gesture->SetOnActionCancelId(std::move(onActionCancel));
    return peer;
}
Ark_RotationGestureInterface OnActionCancel1Impl(Ark_RotationGestureInterface peer,
                                                 const Callback_GestureEvent_Void* event)
{
    CHECK_NULL_RETURN(peer && peer->gesture && event, peer);
    auto onActionCancel = [arkCallback = CallbackHelper(*event)](GestureEvent& aceEvent) {
        const auto arkEvent = Converter::ArkGestureEventSync(aceEvent);
        arkCallback.InvokeSync(arkEvent.ArkValue());
    };
    peer->gesture->SetOnActionCancelId(onActionCancel);
    return peer;
}
} // RotationGestureInterfaceAccessor
const GENERATED_ArkUIRotationGestureInterfaceAccessor* GetRotationGestureInterfaceAccessor()
{
    static const GENERATED_ArkUIRotationGestureInterfaceAccessor RotationGestureInterfaceAccessorImpl {
        RotationGestureInterfaceAccessor::DestroyPeerImpl,
        RotationGestureInterfaceAccessor::CtorImpl,
        RotationGestureInterfaceAccessor::GetFinalizerImpl,
        RotationGestureInterfaceAccessor::OnActionStartImpl,
        RotationGestureInterfaceAccessor::OnActionUpdateImpl,
        RotationGestureInterfaceAccessor::OnActionEndImpl,
        RotationGestureInterfaceAccessor::OnActionCancel0Impl,
        RotationGestureInterfaceAccessor::OnActionCancel1Impl,
    };
    return &RotationGestureInterfaceAccessorImpl;
}

}
