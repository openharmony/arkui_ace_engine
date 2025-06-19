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
#include "core/interfaces/native/utility/reverse_converter.h"

#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace TapGestureInterfaceAccessor {
void DestroyPeerImpl(Ark_TapGestureInterface peer)
{
    CHECK_NULL_VOID(peer);
    delete peer;
}
Ark_TapGestureInterface CtorImpl()
{
    auto peer = new TapGestureInterfacePeer();
    peer->gesture = Referenced::MakeRefPtr<TapGesture>();
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
