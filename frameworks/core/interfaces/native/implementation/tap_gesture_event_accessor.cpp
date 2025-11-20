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
#include "core/interfaces/native/implementation/tap_gesture_event_peer.h"
#include "core/interfaces/native/utility/reverse_converter.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace TapGestureEventAccessor {
void DestroyPeerImpl(Ark_TapGestureEvent peer)
{
    PeerUtils::DestroyPeer(peer);
}
Ark_TapGestureEvent ConstructImpl()
{
    return PeerUtils::CreatePeer<TapGestureEventPeer>();
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Ark_EventLocationInfo GetTapLocationImpl(Ark_TapGestureEvent peer)
{
    CHECK_NULL_RETURN(peer, {});
    auto info = peer->GetBaseGestureInfo();
    CHECK_NULL_RETURN(info, {});

    const std::list<FingerInfo>& fingerList = info->GetFingerList();
    EventLocationInfo tapLocation;
    if (!fingerList.empty()) {
        tapLocation = {
            fingerList.back().localLocation_,
            fingerList.back().screenLocation_,
            fingerList.back().globalLocation_
        };
    }

    return Converter::ArkValue<Ark_EventLocationInfo>(tapLocation);
}
} // TapGestureEventAccessor
const GENERATED_ArkUITapGestureEventAccessor* GetTapGestureEventAccessor()
{
    static const GENERATED_ArkUITapGestureEventAccessor TapGestureEventAccessorImpl {
        TapGestureEventAccessor::DestroyPeerImpl,
        TapGestureEventAccessor::ConstructImpl,
        TapGestureEventAccessor::GetFinalizerImpl,
        TapGestureEventAccessor::GetTapLocationImpl,
    };
    return &TapGestureEventAccessorImpl;
}

}
