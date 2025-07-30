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
#include "core/interfaces/native/implementation/long_press_gesture_interface_peer.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/peer_utils.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace LongPressGestureInterfaceAccessor {
namespace {
    constexpr bool DEFAULT_REPEAT = false;
    constexpr bool DEFAULT_IS_LIMIT_FINGER_COUNT = false;
    constexpr int32_t DEFAULT_FINGERS = 1;
    constexpr int32_t DEFAULT_DURATION = 500;
}
void DestroyPeerImpl(Ark_LongPressGestureInterface peer)
{
    PeerUtils::DestroyPeer(peer);
}
Ark_LongPressGestureInterface CtorImpl(const Opt_Literal_Number_duration_fingers_Boolean_repeat* value)
{
    auto peer = PeerUtils::CreatePeer<LongPressGestureInterfacePeer>();
    int32_t fingers = DEFAULT_FINGERS;
    int32_t duration = DEFAULT_DURATION;
    bool repeat = DEFAULT_REPEAT;
    bool isLimitFingerCount = DEFAULT_IS_LIMIT_FINGER_COUNT;
    std::optional<Ark_Literal_Number_duration_fingers_Boolean_repeat> params =
        value ? Converter::GetOpt(*value) : std::nullopt;
    if (params.has_value()) {
        fingers = Converter::OptConvert<int32_t>(params->fingers).value_or(DEFAULT_FINGERS);
        duration = Converter::OptConvert<int32_t>(params->duration).value_or(DEFAULT_DURATION);
        repeat = Converter::OptConvert<bool>(params->repeat).value_or(DEFAULT_REPEAT);
        LOGE("Arkoala method LongPressGestureInterfaceAccessor.CtorImpl use default value for isLimitFingerCount");
    }
    fingers = fingers <= DEFAULT_FINGERS ? DEFAULT_FINGERS : fingers;
    duration = duration <= 0 ? DEFAULT_DURATION : duration;
    peer->gesture = AceType::MakeRefPtr<LongPressGesture>(fingers, repeat, duration, false, false, isLimitFingerCount);
    return peer;
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Ark_LongPressGestureInterface OnActionImpl(Ark_LongPressGestureInterface peer,
                                           const Callback_GestureEvent_Void* event)
{
    CHECK_NULL_RETURN(peer && peer->gesture && event, peer);
    auto onAction = [arkCallback = CallbackHelper(*event)](GestureEvent& aceEvent) {
        auto arkEvent = Converter::ArkGestureEventSync(aceEvent);
        arkCallback.InvokeSync(arkEvent.ArkValue());
    };
    peer->gesture->SetOnActionId(std::move(onAction));
    return peer;
}
Ark_LongPressGestureInterface OnActionEndImpl(Ark_LongPressGestureInterface peer,
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
Ark_LongPressGestureInterface OnActionCancel0Impl(Ark_LongPressGestureInterface peer,
                                                  const Callback_Void* event)
{
    CHECK_NULL_RETURN(peer && peer->gesture && event, peer);
    auto onActionCancel = [arkCallback = CallbackHelper(*event)](GestureEvent& aceEvent) {
        arkCallback.Invoke();
    };
    peer->gesture->SetOnActionCancelId(std::move(onActionCancel));
    return peer;
}
Ark_LongPressGestureInterface OnActionCancel1Impl(Ark_LongPressGestureInterface peer,
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
} // LongPressGestureInterfaceAccessor
const GENERATED_ArkUILongPressGestureInterfaceAccessor* GetLongPressGestureInterfaceAccessor()
{
    static const GENERATED_ArkUILongPressGestureInterfaceAccessor LongPressGestureInterfaceAccessorImpl {
        LongPressGestureInterfaceAccessor::DestroyPeerImpl,
        LongPressGestureInterfaceAccessor::CtorImpl,
        LongPressGestureInterfaceAccessor::GetFinalizerImpl,
        LongPressGestureInterfaceAccessor::OnActionImpl,
        LongPressGestureInterfaceAccessor::OnActionEndImpl,
        LongPressGestureInterfaceAccessor::OnActionCancel0Impl,
        LongPressGestureInterfaceAccessor::OnActionCancel1Impl,
    };
    return &LongPressGestureInterfaceAccessorImpl;
}

}
