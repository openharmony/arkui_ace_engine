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
#include "core/interfaces/native/utility/callback_helper.h"
#include "rotation_gesture_interface_peer.h"
#include "arkoala_api_generated.h"
#include "core/gestures/gesture_info.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace RotationGestureInterfaceAccessor {
void DestroyPeerImpl(Ark_RotationGestureInterface peer)
{
    delete peer;
}
Ark_RotationGestureInterface CtorImpl()
{
    int32_t fingersNum = DEFAULT_SLIDE_FINGER;
    double angleNum = 0;
    auto peer = new RotationGestureInterfacePeer();
    peer->gesture = AceType::MakeRefPtr<RotationGesture>(fingersNum, angleNum);
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
Ark_RotationGestureInterface OnActionCancelImpl(Ark_RotationGestureInterface peer,
                                                const Callback_Void* event)
{
    CHECK_NULL_RETURN(peer && peer->gesture && event, peer);
    auto onActionCancel = [arkCallback = CallbackHelper(*event)]() {
        arkCallback.Invoke();
    };
    // peer->gesture->SetOnActionCancelId(onActionCancel);
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
        RotationGestureInterfaceAccessor::OnActionCancelImpl,
    };
    return &RotationGestureInterfaceAccessorImpl;
}

struct RotationGestureInterfacePeer {
    virtual ~RotationGestureInterfacePeer() = default;
};
}
