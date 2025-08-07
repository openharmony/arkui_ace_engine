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
#include "core/interfaces/native/implementation/pan_gesture_interface_peer.h"
#include "core/interfaces/native/implementation/pan_gesture_options_peer.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/peer_utils.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace PanGestureInterfaceAccessor {
namespace {
    constexpr int32_t DEFAULT_PAN_FINGERS = 1;
    constexpr int32_t DEFAULT_MAX_PAN_FINGERS = 10;
    Dimension DEFAULT_PAN_DISTANCE = 5.0_vp;
    constexpr auto DEFAULT_PAN_DIRECTION = PanDirection{};
}
void DestroyPeerImpl(Ark_PanGestureInterface peer)
{
    PeerUtils::DestroyPeer(peer);
}
Ark_PanGestureInterface CtorImpl(const Opt_Type_PanGestureInterface_callable0_value* value)
{
    auto peer = PeerUtils::CreatePeer<PanGestureInterfacePeer>();
    int32_t fingers = DEFAULT_PAN_FINGERS;
    double distance = DEFAULT_PAN_DISTANCE.ConvertToPx();
    PanDirection direction = DEFAULT_PAN_DIRECTION;
    if (true) {
        Converter::VisitUnionPtr(value,
            [&fingers, &distance, &direction, &peer](
                const Ark_Literal_Number_distance_fingers_PanDirection_direction& value) {
                fingers = Converter::OptConvert<int32_t>(value.fingers).value_or(DEFAULT_PAN_FINGERS);
                fingers = fingers <= DEFAULT_PAN_FINGERS ? DEFAULT_PAN_FINGERS : fingers;
                fingers = fingers > DEFAULT_MAX_PAN_FINGERS ? DEFAULT_PAN_FINGERS : fingers;
                auto distanceOpt = Converter::OptConvert<float>(value.distance);
                if (distanceOpt.has_value()) {
                    auto distanceNum = static_cast<double>(distanceOpt.value());
                    Dimension dimension = LessNotEqual(distanceNum, 0.0) ?
                        DEFAULT_PAN_DISTANCE : Dimension(distanceNum, DimensionUnit::VP);
                    distance = dimension.ConvertToPx();
                }
                direction = Converter::OptConvert<PanDirection>(value.direction).value_or(DEFAULT_PAN_DIRECTION);
                peer->gesture = AceType::MakeRefPtr<PanGesture>(fingers, direction, distance);
            },
            [&fingers, &distance, &direction, &peer](const Ark_PanGestureOptions& value) {
                if (value && value->handler) {
                    peer->gesture = AceType::MakeRefPtr<PanGesture>(value->handler);
                } else {
                    peer->gesture = AceType::MakeRefPtr<PanGesture>(fingers, direction, distance);
                }
            },
            [&peer, fingers, direction, distance]() {
                peer->gesture = AceType::MakeRefPtr<PanGesture>(fingers, direction, distance);
            }
        );
    }
    return peer;
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Ark_PanGestureInterface OnActionStartImpl(Ark_PanGestureInterface peer,
                                          const Callback_GestureEvent_Void* event)
{
    CHECK_NULL_RETURN(peer && peer->gesture && event, peer);
    auto onActionStart = [arkCallback = CallbackHelper(*event)](GestureEvent& aceEvent) {
        auto arkEvent = Converter::ArkGestureEventSync(aceEvent);
        arkCallback.InvokeSync(arkEvent.ArkValue());
    };
    peer->gesture->SetOnActionStartId(std::move(onActionStart));
    return peer;
}
Ark_PanGestureInterface OnActionUpdateImpl(Ark_PanGestureInterface peer,
                                           const Callback_GestureEvent_Void* event)
{
    CHECK_NULL_RETURN(peer && peer->gesture && event, peer);
    auto onActionUpdate = [arkCallback = CallbackHelper(*event)](GestureEvent& aceEvent) {
        auto arkEvent = Converter::ArkGestureEventSync(aceEvent);
        arkCallback.InvokeSync(arkEvent.ArkValue());
    };
    peer->gesture->SetOnActionUpdateId(std::move(onActionUpdate));
    return peer;
}
Ark_PanGestureInterface OnActionEndImpl(Ark_PanGestureInterface peer,
                                        const Callback_GestureEvent_Void* event)
{
    CHECK_NULL_RETURN(peer && peer->gesture && event, peer);
    auto onActionEnd = [arkCallback = CallbackHelper(*event)](GestureEvent& aceEvent) {
        auto arkEvent = Converter::ArkGestureEventSync(aceEvent);
        arkCallback.InvokeSync(arkEvent.ArkValue());
    };
    peer->gesture->SetOnActionEndId(std::move(onActionEnd));
    return peer;
}
Ark_PanGestureInterface OnActionCancel0Impl(Ark_PanGestureInterface peer,
                                            const Callback_Void* event)
{
    CHECK_NULL_RETURN(peer && peer->gesture && event, peer);
    auto onActionCancel = [arkCallback = CallbackHelper(*event)](GestureEvent& aceEvent) {
        arkCallback.Invoke();
    };
    peer->gesture->SetOnActionCancelId(std::move(onActionCancel));
    return peer;
}
Ark_PanGestureInterface OnActionCancel1Impl(Ark_PanGestureInterface peer,
                                            const Callback_GestureEvent_Void* event)
{
    CHECK_NULL_RETURN(peer && peer->gesture && event, peer);
    auto onActionCancel = [arkCallback = CallbackHelper(*event)](GestureEvent& aceEvent) {
        auto arkEvent = Converter::ArkGestureEventSync(aceEvent);
        arkCallback.InvokeSync(arkEvent.ArkValue());
    };
    peer->gesture->SetOnActionCancelId(std::move(onActionCancel));
    return peer;
}
} // PanGestureInterfaceAccessor
const GENERATED_ArkUIPanGestureInterfaceAccessor* GetPanGestureInterfaceAccessor()
{
    static const GENERATED_ArkUIPanGestureInterfaceAccessor PanGestureInterfaceAccessorImpl {
        PanGestureInterfaceAccessor::DestroyPeerImpl,
        PanGestureInterfaceAccessor::CtorImpl,
        PanGestureInterfaceAccessor::GetFinalizerImpl,
        PanGestureInterfaceAccessor::OnActionStartImpl,
        PanGestureInterfaceAccessor::OnActionUpdateImpl,
        PanGestureInterfaceAccessor::OnActionEndImpl,
        PanGestureInterfaceAccessor::OnActionCancel0Impl,
        PanGestureInterfaceAccessor::OnActionCancel1Impl,
    };
    return &PanGestureInterfaceAccessorImpl;
}

}
