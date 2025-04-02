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
#include "core/interfaces/native/utility/reverse_converter.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace LongPressGestureInterfaceAccessor {
namespace {
    constexpr bool DEFAULT_REPEAT = false;
    constexpr int32_t DEFAULT_FINGERS = 1;
    constexpr int32_t DEFAULT_DURATION = 500;
}
void DestroyPeerImpl(Ark_LongPressGestureInterface peer)
{
    delete peer;
}
Ark_LongPressGestureInterface CtorImpl()
{
    auto peer = new LongPressGestureInterfacePeer();
    peer->gesture = AceType::MakeRefPtr<LongPressGesture>(DEFAULT_FINGERS, DEFAULT_REPEAT, DEFAULT_DURATION);
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
Ark_LongPressGestureInterface OnActionCancelImpl(Ark_LongPressGestureInterface peer,
                                                 const Callback_Void* event)
{
    CHECK_NULL_RETURN(peer && peer->gesture && event, peer);
    auto onActionCancel = [arkCallback = CallbackHelper(*event)]() {
        arkCallback.Invoke();
    };
    // peer->gesture->SetOnActionCancelId(std::move(onActionCancel));
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
        LongPressGestureInterfaceAccessor::OnActionCancelImpl,
    };
    return &LongPressGestureInterfaceAccessorImpl;
}

struct LongPressGestureInterfacePeer {
    virtual ~LongPressGestureInterfacePeer() = default;
};
}
