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
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace GestureEventAccessor {
void DestroyPeerImpl(Ark_GestureEvent peer)
{
}
Ark_GestureEvent CtorImpl()
{
    return nullptr;
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Ark_Boolean GetRepeatImpl(Ark_GestureEvent peer)
{
    return {};
}
void SetRepeatImpl(Ark_GestureEvent peer,
                   Ark_Boolean repeat)
{
}
Array_FingerInfo GetFingerListImpl(Ark_GestureEvent peer)
{
    return {};
}
void SetFingerListImpl(Ark_GestureEvent peer,
                       const Array_FingerInfo* fingerList)
{
}
Ark_Number GetOffsetXImpl(Ark_GestureEvent peer)
{
    return {};
}
void SetOffsetXImpl(Ark_GestureEvent peer,
                    const Ark_Number* offsetX)
{
}
Ark_Number GetOffsetYImpl(Ark_GestureEvent peer)
{
    return {};
}
void SetOffsetYImpl(Ark_GestureEvent peer,
                    const Ark_Number* offsetY)
{
}
Ark_Number GetAngleImpl(Ark_GestureEvent peer)
{
    return {};
}
void SetAngleImpl(Ark_GestureEvent peer,
                  const Ark_Number* angle)
{
}
Ark_Number GetSpeedImpl(Ark_GestureEvent peer)
{
    return {};
}
void SetSpeedImpl(Ark_GestureEvent peer,
                  const Ark_Number* speed)
{
}
Ark_Number GetScaleImpl(Ark_GestureEvent peer)
{
    return {};
}
void SetScaleImpl(Ark_GestureEvent peer,
                  const Ark_Number* scale)
{
}
Ark_Number GetPinchCenterXImpl(Ark_GestureEvent peer)
{
    return {};
}
void SetPinchCenterXImpl(Ark_GestureEvent peer,
                         const Ark_Number* pinchCenterX)
{
}
Ark_Number GetPinchCenterYImpl(Ark_GestureEvent peer)
{
    return {};
}
void SetPinchCenterYImpl(Ark_GestureEvent peer,
                         const Ark_Number* pinchCenterY)
{
}
Ark_Number GetVelocityXImpl(Ark_GestureEvent peer)
{
    return {};
}
void SetVelocityXImpl(Ark_GestureEvent peer,
                      const Ark_Number* velocityX)
{
}
Ark_Number GetVelocityYImpl(Ark_GestureEvent peer)
{
    return {};
}
void SetVelocityYImpl(Ark_GestureEvent peer,
                      const Ark_Number* velocityY)
{
}
Ark_Number GetVelocityImpl(Ark_GestureEvent peer)
{
    return {};
}
void SetVelocityImpl(Ark_GestureEvent peer,
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
        GestureEventAccessor::GetFingerListImpl,
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
