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
#include "core/interfaces/native/implementation/pinch_gesture_interface_peer.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/peer_utils.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace PinchGestureInterfaceAccessor {
namespace {
constexpr int32_t DEFAULT_PINCH_FINGER = 2;
constexpr int32_t DEFAULT_MAX_PINCH_FINGER = 5;
constexpr double DEFAULT_PINCH_DISTANCE = 5.0;
}

void DestroyPeerImpl(Ark_PinchGestureInterface peer)
{
    PeerUtils::DestroyPeer(peer);
}
Ark_PinchGestureInterface CtorImpl(const Opt_Literal_Number_distance_fingers* value)
{
    auto peer = PeerUtils::CreatePeer<PinchGestureInterfacePeer>();
    auto fingers = DEFAULT_PINCH_FINGER;
    auto distance = DEFAULT_PINCH_DISTANCE;
    std::optional<Ark_Literal_Number_distance_fingers> params = value ? Converter::GetOpt(*value) : std::nullopt;
    if (params.has_value()) {
        fingers = Converter::OptConvert<int32_t>(params->fingers).value_or(DEFAULT_PINCH_FINGER);
        fingers = fingers <= DEFAULT_PINCH_FINGER ? DEFAULT_PINCH_FINGER : fingers;
        fingers = fingers > DEFAULT_MAX_PINCH_FINGER ? DEFAULT_PINCH_FINGER : fingers;
        auto distanceOpt = Converter::OptConvert<float>(params->distance);
        if (distanceOpt.has_value()) {
            distance = static_cast<double>(distanceOpt.value());
        }
        distance = LessNotEqual(distance, 0.0) ? DEFAULT_PINCH_DISTANCE : distance;
    }
    peer->gesture = AceType::MakeRefPtr<PinchGesture>(fingers, distance);
    return peer;
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Ark_PinchGestureInterface OnActionStartImpl(Ark_PinchGestureInterface peer,
                                            const Callback_GestureEvent_Void* event)
{
    CHECK_NULL_RETURN(peer && peer->gesture && event, peer);
    auto callback = [arkCallback = CallbackHelper(*event)](GestureEvent& info) {
        auto arkEvent = Converter::ArkGestureEventSync(info);
        arkCallback.InvokeSync(arkEvent.ArkValue());
    };
    peer->gesture->SetOnActionStartId(std::move(callback));
    return peer;
}
Ark_PinchGestureInterface OnActionUpdateImpl(Ark_PinchGestureInterface peer,
                                             const Callback_GestureEvent_Void* event)
{
    CHECK_NULL_RETURN(peer && peer->gesture && event, peer);
    auto callback = [arkCallback = CallbackHelper(*event)](GestureEvent& info) {
        auto arkEvent = Converter::ArkGestureEventSync(info);
        arkCallback.InvokeSync(arkEvent.ArkValue());
    };
    peer->gesture->SetOnActionUpdateId(std::move(callback));
    return peer;
}
Ark_PinchGestureInterface OnActionEndImpl(Ark_PinchGestureInterface peer,
                                          const Callback_GestureEvent_Void* event)
{
    CHECK_NULL_RETURN(peer && peer->gesture && event, peer);
    auto callback = [arkCallback = CallbackHelper(*event)](GestureEvent& info) {
        auto arkEvent = Converter::ArkGestureEventSync(info);
        arkCallback.InvokeSync(arkEvent.ArkValue());
    };
    peer->gesture->SetOnActionEndId(std::move(callback));
    return peer;
}
Ark_PinchGestureInterface OnActionCancel0Impl(Ark_PinchGestureInterface peer,
                                              const Callback_Void* event)
{
    CHECK_NULL_RETURN(peer && peer->gesture && event, peer);
    auto callback = [arkCallback = CallbackHelper(*event)](GestureEvent& info) {
        arkCallback.Invoke();
    };
    peer->gesture->SetOnActionCancelId(std::move(callback));
    return peer;
}
Ark_PinchGestureInterface OnActionCancel1Impl(Ark_PinchGestureInterface peer,
                                              const Callback_GestureEvent_Void* event)
{
    CHECK_NULL_RETURN(peer && peer->gesture && event, peer);
    auto callback = [arkCallback = CallbackHelper(*event)](GestureEvent& info) {
        auto arkEvent = Converter::ArkGestureEventSync(info);
        arkCallback.InvokeSync(arkEvent.ArkValue());
    };
    peer->gesture->SetOnActionCancelId(std::move(callback));
    return peer;
}
} // PinchGestureInterfaceAccessor
const GENERATED_ArkUIPinchGestureInterfaceAccessor* GetPinchGestureInterfaceAccessor()
{
    static const GENERATED_ArkUIPinchGestureInterfaceAccessor PinchGestureInterfaceAccessorImpl {
        PinchGestureInterfaceAccessor::DestroyPeerImpl,
        PinchGestureInterfaceAccessor::CtorImpl,
        PinchGestureInterfaceAccessor::GetFinalizerImpl,
        PinchGestureInterfaceAccessor::OnActionStartImpl,
        PinchGestureInterfaceAccessor::OnActionUpdateImpl,
        PinchGestureInterfaceAccessor::OnActionEndImpl,
        PinchGestureInterfaceAccessor::OnActionCancel0Impl,
        PinchGestureInterfaceAccessor::OnActionCancel1Impl,
    };
    return &PinchGestureInterfaceAccessorImpl;
}
}
