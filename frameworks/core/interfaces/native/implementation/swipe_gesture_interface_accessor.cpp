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
#include "core/interfaces/native/implementation/swipe_gesture_interface_peer.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/peer_utils.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace SwipeGestureInterfaceAccessor {
namespace {
    constexpr int32_t DEFAULT_SWIPE_FINGERS = 1;
    constexpr double DEFAULT_SWIPE_SPEED = 100.0;
    constexpr auto DEFAULT_SWIPE_DIRECTION = SwipeDirection{};
    constexpr bool DEFAULT_IS_LIMIT_FINGER_COUNT = false;
}
void DestroyPeerImpl(Ark_SwipeGestureInterface peer)
{
    PeerUtils::DestroyPeer(peer);
}
Ark_SwipeGestureInterface CtorImpl(const Opt_Literal_Number_fingers_speed_SwipeDirection_direction* value)
{
    auto peer =  PeerUtils::CreatePeer<SwipeGestureInterfacePeer>();
    int32_t fingers = DEFAULT_SWIPE_FINGERS;
    SwipeDirection direction = DEFAULT_SWIPE_DIRECTION;
    double speed = DEFAULT_SWIPE_SPEED;
    bool isLimitFingerCount = DEFAULT_IS_LIMIT_FINGER_COUNT;
    std::optional<Ark_Literal_Number_fingers_speed_SwipeDirection_direction> params =
        value ? Converter::GetOpt(*value) : std::nullopt;
    if (params.has_value()) {
        fingers = Converter::OptConvert<int32_t>(params->fingers).value_or(DEFAULT_SWIPE_FINGERS);
        fingers = fingers <= DEFAULT_SWIPE_FINGERS ? DEFAULT_SWIPE_FINGERS : fingers;
        direction = Converter::OptConvert<SwipeDirection>(params->direction).value_or(DEFAULT_SWIPE_DIRECTION);
        auto speedOpt = Converter::OptConvert<float>(params->speed);
        if (speedOpt.has_value()) {
            speed = static_cast<double>(speedOpt.value());
            speed = LessOrEqual(speed, 0.0) ? DEFAULT_SWIPE_SPEED : speed;
        }
        LOGE("Arkoala method SwipeGestureInterfaceAccessor.CtorImpl use default value for isLimitFingerCount");
    }
    peer->gesture = AceType::MakeRefPtr<SwipeGesture>(fingers, direction, speed, isLimitFingerCount);
    return peer;
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Ark_SwipeGestureInterface OnActionImpl(Ark_SwipeGestureInterface peer,
                                       const Callback_GestureEvent_Void* event)
{
    CHECK_NULL_RETURN(peer && peer->gesture && event, peer);
    auto onAction = [arkCallback = CallbackHelper(*event)](GestureEvent& info) {
        auto arkEvent = Converter::ArkGestureEventSync(info);
        arkCallback.InvokeSync(arkEvent.ArkValue());
    };
    peer->gesture->SetOnActionId(std::move(onAction));
    return peer;
}
} // SwipeGestureInterfaceAccessor
const GENERATED_ArkUISwipeGestureInterfaceAccessor* GetSwipeGestureInterfaceAccessor()
{
    static const GENERATED_ArkUISwipeGestureInterfaceAccessor SwipeGestureInterfaceAccessorImpl {
        SwipeGestureInterfaceAccessor::DestroyPeerImpl,
        SwipeGestureInterfaceAccessor::CtorImpl,
        SwipeGestureInterfaceAccessor::GetFinalizerImpl,
        SwipeGestureInterfaceAccessor::OnActionImpl,
    };
    return &SwipeGestureInterfaceAccessorImpl;
}
}
