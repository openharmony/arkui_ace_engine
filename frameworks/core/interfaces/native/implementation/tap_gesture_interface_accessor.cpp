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
#include "core/interfaces/native/implementation/tap_gesture_interface_peer.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/peer_utils.h"
#include "core/interfaces/native/utility/reverse_converter.h"

#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace TapGestureInterfaceAccessor {
namespace {
    constexpr int32_t DEFAULT_TAP_FINGERS = 1;
    constexpr int32_t DEFAULT_TAP_COUNT = 1;
    constexpr double DEFAULT_TAP_DISTANCE = std::numeric_limits<double>::infinity();
    constexpr bool DEFAULT_IS_LIMIT_FINGER_COUNT = false;
}
void DestroyPeerImpl(Ark_TapGestureInterface peer)
{
    PeerUtils::DestroyPeer(peer);
}
Ark_TapGestureInterface CtorImpl(const Opt_TapGestureParameters* value)
{
    bool isLimitFingerCount = DEFAULT_IS_LIMIT_FINGER_COUNT;
    int32_t fingers = DEFAULT_TAP_FINGERS;
    int32_t count = DEFAULT_TAP_COUNT;
    double distance = DEFAULT_TAP_DISTANCE;
    auto peer = PeerUtils::CreatePeer<TapGestureInterfacePeer>();
    std::optional<Ark_TapGestureParameters> params = value ? Converter::GetOpt(*value) : std::nullopt;
    if (params.has_value()) {
        fingers = Converter::OptConvert<int32_t>(params->fingers).value_or(DEFAULT_TAP_FINGERS);
        fingers = fingers <= DEFAULT_TAP_FINGERS ? DEFAULT_TAP_FINGERS : fingers;
        count = Converter::OptConvert<int32_t>(params->count).value_or(DEFAULT_TAP_COUNT);
        count = count <= DEFAULT_TAP_COUNT ? DEFAULT_TAP_COUNT : count;
        auto distanceThreshold = Converter::OptConvert<float>(params->distanceThreshold);
        if (distanceThreshold.has_value()) {
            distance = static_cast<double>(distanceThreshold.value());
            distance = LessNotEqual(distance, 0.0) ? DEFAULT_TAP_DISTANCE : distance;
            distance = Dimension(distance, DimensionUnit::VP).ConvertToPx();
        }
        isLimitFingerCount =
            Converter::OptConvert<bool>(params->isFingerCountLimited).value_or(DEFAULT_IS_LIMIT_FINGER_COUNT);
    }
    peer->gesture = Referenced::MakeRefPtr<TapGesture>(count, fingers, distance, isLimitFingerCount);
    return peer;
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Ark_TapGestureInterface OnActionImpl(Ark_TapGestureInterface peer,
                                     const Callback_GestureEvent_Void* event)
{
    CHECK_NULL_RETURN(peer, peer);
    CHECK_NULL_RETURN(event, peer);
    CHECK_NULL_RETURN(peer->gesture, peer);

    auto onAction = [arkCallback = CallbackHelper(*event)](GestureEvent& event) -> void {
        auto arkEvent = Converter::ArkGestureEventSync(event);
        arkCallback.InvokeSync(arkEvent.ArkValue());
    };
    peer->gesture->SetOnActionId(std::move(onAction));
    return peer;
}
} // TapGestureInterfaceAccessor
const GENERATED_ArkUITapGestureInterfaceAccessor* GetTapGestureInterfaceAccessor()
{
    static const GENERATED_ArkUITapGestureInterfaceAccessor TapGestureInterfaceAccessorImpl {
        TapGestureInterfaceAccessor::DestroyPeerImpl,
        TapGestureInterfaceAccessor::CtorImpl,
        TapGestureInterfaceAccessor::GetFinalizerImpl,
        TapGestureInterfaceAccessor::OnActionImpl,
    };
    return &TapGestureInterfaceAccessorImpl;
}

}
