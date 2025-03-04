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
namespace PinchGestureEventAccessor {
void DestroyPeerImpl(Ark_PinchGestureEvent peer)
{
}
Ark_PinchGestureEvent CtorImpl()
{
    return nullptr;
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Ark_Number GetScaleImpl(Ark_PinchGestureEvent peer)
{
    return {};
}
void SetScaleImpl(Ark_PinchGestureEvent peer,
                  const Ark_Number* scale)
{
}
Ark_Number GetPinchCenterXImpl(Ark_PinchGestureEvent peer)
{
    return {};
}
void SetPinchCenterXImpl(Ark_PinchGestureEvent peer,
                         const Ark_Number* pinchCenterX)
{
}
Ark_Number GetPinchCenterYImpl(Ark_PinchGestureEvent peer)
{
    return {};
}
void SetPinchCenterYImpl(Ark_PinchGestureEvent peer,
                         const Ark_Number* pinchCenterY)
{
}
} // PinchGestureEventAccessor
const GENERATED_ArkUIPinchGestureEventAccessor* GetPinchGestureEventAccessor()
{
    static const GENERATED_ArkUIPinchGestureEventAccessor PinchGestureEventAccessorImpl {
        PinchGestureEventAccessor::DestroyPeerImpl,
        PinchGestureEventAccessor::CtorImpl,
        PinchGestureEventAccessor::GetFinalizerImpl,
        PinchGestureEventAccessor::GetScaleImpl,
        PinchGestureEventAccessor::SetScaleImpl,
        PinchGestureEventAccessor::GetPinchCenterXImpl,
        PinchGestureEventAccessor::SetPinchCenterXImpl,
        PinchGestureEventAccessor::GetPinchCenterYImpl,
        PinchGestureEventAccessor::SetPinchCenterYImpl,
    };
    return &PinchGestureEventAccessorImpl;
}

}
