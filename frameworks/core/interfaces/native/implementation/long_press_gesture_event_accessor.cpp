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
#include "core/interfaces/native/implementation/long_press_gesture_event_peer.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace LongPressGestureEventAccessor {
void DestroyPeerImpl(Ark_LongPressGestureEvent peer)
{
    delete peer;
}
Ark_LongPressGestureEvent CtorImpl()
{
    return new LongPressGestureEventPeer();
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Ark_Boolean GetRepeatImpl(Ark_LongPressGestureEvent peer)
{
    const auto errValue = Converter::ArkValue<Ark_Boolean>(false);
    CHECK_NULL_RETURN(peer, errValue);
    auto event = peer->GetEventInfo();
    CHECK_NULL_RETURN(event, errValue);
    return event->GetRepeat();
}
void SetRepeatImpl(Ark_LongPressGestureEvent peer,
                   Ark_Boolean repeat)
{
    CHECK_NULL_VOID(peer);
    auto event = peer->GetEventInfo();
    CHECK_NULL_VOID(event);
    event->SetRepeat(Converter::Convert<bool>(repeat));
}
} // LongPressGestureEventAccessor
const GENERATED_ArkUILongPressGestureEventAccessor* GetLongPressGestureEventAccessor()
{
    static const GENERATED_ArkUILongPressGestureEventAccessor LongPressGestureEventAccessorImpl {
        LongPressGestureEventAccessor::DestroyPeerImpl,
        LongPressGestureEventAccessor::CtorImpl,
        LongPressGestureEventAccessor::GetFinalizerImpl,
        LongPressGestureEventAccessor::GetRepeatImpl,
        LongPressGestureEventAccessor::SetRepeatImpl,
    };
    return &LongPressGestureEventAccessorImpl;
}
}
