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
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/gestures/gesture_info.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace SwipeGestureInterfaceAccessor {
void DestroyPeerImpl(Ark_SwipeGestureInterface peer)
{
    delete peer;
}
Ark_SwipeGestureInterface CtorImpl()
{
    int32_t fingersNum = DEFAULT_SLIDE_FINGER;
    double speedNum = DEFAULT_SLIDE_SPEED;
    SwipeDirection slideDirection;
    auto peer = new SwipeGestureInterfacePeer();
    peer->gesture = AceType::MakeRefPtr<SwipeGesture>(fingersNum, slideDirection, speedNum);
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
