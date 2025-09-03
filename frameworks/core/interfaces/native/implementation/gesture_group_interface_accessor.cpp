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
#include "core/interfaces/native/implementation/gesture_group_interface_peer.h"
#include "core/interfaces/native/implementation/long_press_gesture_interface_peer.h"
#include "core/interfaces/native/implementation/pan_gesture_interface_peer.h"
#include "core/interfaces/native/implementation/pinch_gesture_interface_peer.h"
#include "core/interfaces/native/implementation/rotation_gesture_interface_peer.h"
#include "core/interfaces/native/implementation/swipe_gesture_interface_peer.h"
#include "core/interfaces/native/implementation/tap_gesture_interface_peer.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/peer_utils.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::Converter {
template<>
RefPtr<Gesture> Convert(const Ark_GestureGroupInterface& src)
{
    return src ? src->gesture : nullptr;
}

template<>
RefPtr<Gesture> Convert(const Ark_LongPressGestureInterface& src)
{
    return src ? src->gesture : nullptr;
}

template<>
RefPtr<Gesture> Convert(const Ark_PanGestureInterface& src)
{
    return src ? src->gesture : nullptr;
}

template<>
RefPtr<Gesture> Convert(const Ark_PinchGestureInterface& src)
{
    return src ? src->gesture : nullptr;
}

template<>
RefPtr<Gesture> Convert(const Ark_RotationGestureInterface& src)
{
    return src ? src->gesture : nullptr;
}

template<>
RefPtr<Gesture> Convert(const Ark_SwipeGestureInterface& src)
{
    return src ? src->gesture : nullptr;
}

template<>
RefPtr<Gesture> Convert(const Ark_TapGestureInterface& src)
{
    return src ? src->gesture : nullptr;
}

template<>
std::vector<RefPtr<Gesture>> Convert(const Array_GestureType& src)
{
    std::vector<RefPtr<Gesture>> dst;
    auto length = Converter::Convert<int>(src.length);
    for (int i = 0; i < length; i++) {
        auto opt = Converter::OptConvert<RefPtr<Gesture>>(*(src.array + i));
        if (opt) {
            dst.push_back(*opt);
        }
    }
    return dst;
}
}

namespace OHOS::Ace::NG::GeneratedModifier {
namespace GestureGroupInterfaceAccessor {
void DestroyPeerImpl(Ark_GestureGroupInterface peer)
{
    PeerUtils::DestroyPeer(peer);
}
Ark_GestureGroupInterface CtorImpl(Ark_GestureMode mode,
                                   const Array_GestureType* gesture)
{
    auto peer = PeerUtils::CreatePeer<GestureGroupInterfacePeer>();
    auto gestureMode = (Converter::OptConvert<GestureMode>(mode)).value_or(GestureMode::Sequence);
    std::vector<RefPtr<Gesture>> gestures;
    if (gesture) {
        gestures = Converter::Convert<std::vector<RefPtr<Gesture>>>(*gesture);
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
        GestureGroupInterfaceAccessor::CtorImpl,
        GestureGroupInterfaceAccessor::GetFinalizerImpl,
        GestureGroupInterfaceAccessor::OnCancelImpl,
    };
    return &GestureGroupInterfaceAccessorImpl;
}
}
