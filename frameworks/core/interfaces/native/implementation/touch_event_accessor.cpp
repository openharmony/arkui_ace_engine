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
#include "core/interfaces/native/implementation/touch_event_peer.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace TouchEventAccessor {
void DestroyPeerImpl(TouchEventPeer* peer)
{
    delete peer;
}
Ark_NativePointer CtorImpl()
{
    return new TouchEventPeer();
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
void GetHistoricalPointsImpl(TouchEventPeer* peer)
{
}
Ark_NativePointer GetTypeImpl(TouchEventPeer* peer)
{
    return {};
}
void SetTypeImpl(TouchEventPeer* peer,
                 Ark_TouchType type)
{
}
void SetTouchesImpl(TouchEventPeer* peer,
                    const Array_TouchObject* touches)
{
}
void SetChangedTouchesImpl(TouchEventPeer* peer,
                           const Array_TouchObject* changedTouches)
{
}
Callback_Void GetStopPropagationImpl(TouchEventPeer* peer)
{
    return {};
}
void SetStopPropagationImpl(TouchEventPeer* peer,
                            const Callback_Void* stopPropagation)
{
}
Callback_Void GetPreventDefaultImpl(TouchEventPeer* peer)
{
    return {};
}
void SetPreventDefaultImpl(TouchEventPeer* peer,
                           const Callback_Void* preventDefault)
{
}
} // TouchEventAccessor
const GENERATED_ArkUITouchEventAccessor* GetTouchEventAccessor()
{
    static const GENERATED_ArkUITouchEventAccessor TouchEventAccessorImpl {
        TouchEventAccessor::DestroyPeerImpl,
        TouchEventAccessor::CtorImpl,
        TouchEventAccessor::GetFinalizerImpl,
        TouchEventAccessor::GetHistoricalPointsImpl,
        TouchEventAccessor::GetTypeImpl,
        TouchEventAccessor::SetTypeImpl,
        TouchEventAccessor::SetTouchesImpl,
        TouchEventAccessor::SetChangedTouchesImpl,
        TouchEventAccessor::GetStopPropagationImpl,
        TouchEventAccessor::SetStopPropagationImpl,
        TouchEventAccessor::GetPreventDefaultImpl,
        TouchEventAccessor::SetPreventDefaultImpl,
    };
    return &TouchEventAccessorImpl;
}
}
