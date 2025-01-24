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
#include "core/interfaces/native/implementation/gesture_event_peer.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace GestureEventAccessor {
void DestroyPeerImpl(GestureEventPeer* peer)
{
    delete peer;
}
Ark_NativePointer CtorImpl()
{
    return new GestureEventPeer();
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Ark_Boolean GetRepeatImpl(GestureEventPeer* peer)
{
    return 0;
}
void SetRepeatImpl(GestureEventPeer* peer,
                   Ark_Boolean repeat)
{
}
void SetFingerListImpl(GestureEventPeer* peer,
                       const Array_FingerInfo* fingerList)
{
}
Ark_Int32 GetOffsetXImpl(GestureEventPeer* peer)
{
    return 0;
}
void SetOffsetXImpl(GestureEventPeer* peer,
                    const Ark_Number* offsetX)
{
}
Ark_Int32 GetOffsetYImpl(GestureEventPeer* peer)
{
    return 0;
}
void SetOffsetYImpl(GestureEventPeer* peer,
                    const Ark_Number* offsetY)
{
}
Ark_Int32 GetAngleImpl(GestureEventPeer* peer)
{
    return 0;
}
void SetAngleImpl(GestureEventPeer* peer,
                  const Ark_Number* angle)
{
}
Ark_Int32 GetSpeedImpl(GestureEventPeer* peer)
{
    return 0;
}
void SetSpeedImpl(GestureEventPeer* peer,
                  const Ark_Number* speed)
{
}
Ark_Int32 GetScaleImpl(GestureEventPeer* peer)
{
    return 0;
}
void SetScaleImpl(GestureEventPeer* peer,
                  const Ark_Number* scale)
{
}
Ark_Int32 GetPinchCenterXImpl(GestureEventPeer* peer)
{
    return 0;
}
void SetPinchCenterXImpl(GestureEventPeer* peer,
                         const Ark_Number* pinchCenterX)
{
}
Ark_Int32 GetPinchCenterYImpl(GestureEventPeer* peer)
{
    return 0;
}
void SetPinchCenterYImpl(GestureEventPeer* peer,
                         const Ark_Number* pinchCenterY)
{
}
Ark_Int32 GetVelocityXImpl(GestureEventPeer* peer)
{
    return 0;
}
void SetVelocityXImpl(GestureEventPeer* peer,
                      const Ark_Number* velocityX)
{
}
Ark_Int32 GetVelocityYImpl(GestureEventPeer* peer)
{
    return 0;
}
void SetVelocityYImpl(GestureEventPeer* peer,
                      const Ark_Number* velocityY)
{
}
Ark_Int32 GetVelocityImpl(GestureEventPeer* peer)
{
    return 0;
}
void SetVelocityImpl(GestureEventPeer* peer,
                     const Ark_Number* velocity)
{
}
} // GestureEventAccessor
const GENERATED_ArkUIGestureEventAccessor* GetGestureEventAccessor()
{
    static const GENERATED_ArkUIGestureEventAccessor GestureEventAccessorImpl {
        GestureEventAccessor::DestroyPeerImpl,
        GestureEventAccessor::CtorImpl,
        GestureEventAccessor::GetFinalizerImpl,
        GestureEventAccessor::GetRepeatImpl,
        GestureEventAccessor::SetRepeatImpl,
        GestureEventAccessor::SetFingerListImpl,
        GestureEventAccessor::GetOffsetXImpl,
        GestureEventAccessor::SetOffsetXImpl,
        GestureEventAccessor::GetOffsetYImpl,
        GestureEventAccessor::SetOffsetYImpl,
        GestureEventAccessor::GetAngleImpl,
        GestureEventAccessor::SetAngleImpl,
        GestureEventAccessor::GetSpeedImpl,
        GestureEventAccessor::SetSpeedImpl,
        GestureEventAccessor::GetScaleImpl,
        GestureEventAccessor::SetScaleImpl,
        GestureEventAccessor::GetPinchCenterXImpl,
        GestureEventAccessor::SetPinchCenterXImpl,
        GestureEventAccessor::GetPinchCenterYImpl,
        GestureEventAccessor::SetPinchCenterYImpl,
        GestureEventAccessor::GetVelocityXImpl,
        GestureEventAccessor::SetVelocityXImpl,
        GestureEventAccessor::GetVelocityYImpl,
        GestureEventAccessor::SetVelocityYImpl,
        GestureEventAccessor::GetVelocityImpl,
        GestureEventAccessor::SetVelocityImpl,
    };
    return &GestureEventAccessorImpl;
}
}
