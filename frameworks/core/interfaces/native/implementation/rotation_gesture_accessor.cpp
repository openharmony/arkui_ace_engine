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
namespace RotationGestureAccessor {
void DestroyPeerImpl(Ark_RotationGesture peer)
{
}
Ark_RotationGesture ConstructImpl()
{
    return {};
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Ark_RotationGesture $_instantiateImpl(const Callback_RotationGesture* factory,
                                      const Opt_RotationGestureHandlerOptions* value)
{
    return {};
}
void OnActionStartImpl(Ark_RotationGesture peer,
                       const Callback_GestureEvent_Void* event)
{
}
void OnActionUpdateImpl(Ark_RotationGesture peer,
                        const Callback_GestureEvent_Void* event)
{
}
void OnActionEndImpl(Ark_RotationGesture peer,
                     const Callback_GestureEvent_Void* event)
{
}
void OnActionCancelImpl(Ark_RotationGesture peer,
                        const Callback_GestureEvent_Void* event)
{
}
} // RotationGestureAccessor
const GENERATED_ArkUIRotationGestureAccessor* GetRotationGestureAccessor()
{
    static const GENERATED_ArkUIRotationGestureAccessor RotationGestureAccessorImpl {
        RotationGestureAccessor::DestroyPeerImpl,
        RotationGestureAccessor::ConstructImpl,
        RotationGestureAccessor::GetFinalizerImpl,
        RotationGestureAccessor::$_instantiateImpl,
        RotationGestureAccessor::OnActionStartImpl,
        RotationGestureAccessor::OnActionUpdateImpl,
        RotationGestureAccessor::OnActionEndImpl,
        RotationGestureAccessor::OnActionCancelImpl,
    };
    return &RotationGestureAccessorImpl;
}

}
