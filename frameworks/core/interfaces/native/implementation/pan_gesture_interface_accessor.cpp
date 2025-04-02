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
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace PanGestureInterfaceAccessor {
namespace {
    constexpr int32_t DEFAULT_FINGERS = 1;
    constexpr double DEFAULT_DISTANCE = 0.0;
    constexpr auto DEFAULT_PAN_DIRECTION = PanDirection{};
}
void DestroyPeerImpl(Ark_PanGestureInterface peer)
{
    delete peer;
}
Ark_PanGestureInterface CtorImpl()
{
    auto peer = new PanGestureInterfacePeer();
    peer->gesture = AceType::MakeRefPtr<PanGesture>(DEFAULT_FINGERS, DEFAULT_PAN_DIRECTION, DEFAULT_DISTANCE);
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
Ark_PanGestureInterface OnActionCancelImpl(Ark_PanGestureInterface peer,
                                           const Callback_Void* event)
{
    CHECK_NULL_RETURN(peer && peer->gesture && event, peer);
    auto onActionCancel = [arkCallback = CallbackHelper(*event)]() {
        arkCallback.Invoke();
    };
    // peer->gesture->SetOnActionCancelId(std::move(onActionCancel));
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
        PanGestureInterfaceAccessor::OnActionCancelImpl,
    };
    return &PanGestureInterfaceAccessorImpl;
}

struct PanGestureInterfacePeer {
    virtual ~PanGestureInterfacePeer() = default;
};
}
