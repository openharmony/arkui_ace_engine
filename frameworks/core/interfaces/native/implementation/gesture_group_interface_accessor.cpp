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

#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/peer_utils.h"
#include "core/interfaces/native/utility/reverse_converter.h"

#include "arkoala_api_generated.h"
#include "gesture_group_interface_peer.h"
#include "gesture_peer.h"

namespace OHOS::Ace::NG::Converter {
template<>
RefPtr<Gesture> Convert(const Ark_CustomObject& src)
{
    return nullptr;
}

template<>
RefPtr<Gesture> Convert(const Ark_Gesture& src)
{
    return src ? src->GetGesture() : nullptr;
}
}

namespace OHOS::Ace::NG::GeneratedModifier {
namespace GestureGroupInterfaceAccessor {
void DestroyPeerImpl(Ark_GestureGroupInterface peer)
{
    PeerUtils::DestroyPeer(peer);
}
Ark_GestureGroupInterface ConstructImpl(Ark_GestureMode mode,
                                        const Array_GestureType* gesture)
{
    auto peer = PeerUtils::CreatePeer<GestureGroupInterfacePeer>();
    auto gestureMode = (Converter::OptConvert<GestureMode>(mode)).value_or(GestureMode::Sequence);
    std::vector<RefPtr<Gesture>> gestures;
    if (gesture) {
        gestures = Converter::Squash(Converter::Convert<std::vector<std::optional<RefPtr<Gesture>>>>(*gesture));
    }
    peer->gesture = AceType::MakeRefPtr<GestureGroup>(gestureMode, gestures);
    return peer;
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Ark_GestureGroupInterface OnCancelImpl(Ark_GestureGroupInterface peer,
                                       const Callback_Void* event)
{
    CHECK_NULL_RETURN(peer && peer->gesture && event, peer);
    auto callback = [arkCallback = CallbackHelper(*event)](GestureEvent& info) {
        arkCallback.Invoke();
    };
    peer->gesture->SetOnActionCancelId(std::move(callback));
    return peer;
}
} // GestureGroupInterfaceAccessor
const GENERATED_ArkUIGestureGroupInterfaceAccessor* GetGestureGroupInterfaceAccessor()
{
    static const GENERATED_ArkUIGestureGroupInterfaceAccessor GestureGroupInterfaceAccessorImpl {
        GestureGroupInterfaceAccessor::DestroyPeerImpl,
        GestureGroupInterfaceAccessor::ConstructImpl,
        GestureGroupInterfaceAccessor::GetFinalizerImpl,
        GestureGroupInterfaceAccessor::OnCancelImpl,
    };
    return &GestureGroupInterfaceAccessorImpl;
}
}
