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
#include "core/interfaces/native/implementation/rotation_gesture_event_peer.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace RotationGestureEventAccessor {
void DestroyPeerImpl(Ark_RotationGestureEvent peer)
{
    PeerUtils::DestroyPeer(peer);
}
Ark_RotationGestureEvent CtorImpl()
{
    return PeerUtils::CreatePeer<RotationGestureEventPeer>();
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Ark_Number GetAngleImpl(Ark_RotationGestureEvent peer)
{
    const auto errValue = Converter::ArkValue<Ark_Number>(0);
    CHECK_NULL_RETURN(peer, errValue);
    auto info = peer->GetEventInfo();
    CHECK_NULL_RETURN(info, errValue);
    const auto& angle = info->GetAngle();
    return Converter::ArkValue<Ark_Number>(static_cast<float>(angle));
}
void SetAngleImpl(Ark_RotationGestureEvent peer,
                  const Ark_Number* angle)
{
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(angle);
    auto info = peer->GetEventInfo();
    CHECK_NULL_VOID(info);
    info->SetAngle(Converter::Convert<float>(*angle));
}
} // RotationGestureEventAccessor
const GENERATED_ArkUIRotationGestureEventAccessor* GetRotationGestureEventAccessor()
{
    static const GENERATED_ArkUIRotationGestureEventAccessor RotationGestureEventAccessorImpl {
        RotationGestureEventAccessor::DestroyPeerImpl,
        RotationGestureEventAccessor::CtorImpl,
        RotationGestureEventAccessor::GetFinalizerImpl,
        RotationGestureEventAccessor::GetAngleImpl,
        RotationGestureEventAccessor::SetAngleImpl,
    };
    return &RotationGestureEventAccessorImpl;
}
}
