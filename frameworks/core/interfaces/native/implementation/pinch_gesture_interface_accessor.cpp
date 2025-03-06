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
namespace PinchGestureInterfaceAccessor {
void DestroyPeerImpl(Ark_PinchGestureInterface peer)
{
}
Ark_PinchGestureInterface CtorImpl()
{
    return nullptr;
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Ark_PinchGestureInterface OnActionStartImpl(Ark_PinchGestureInterface peer,
                                            const Callback_GestureEvent_Void* event)
{
    return {};
}
Ark_PinchGestureInterface OnActionUpdateImpl(Ark_PinchGestureInterface peer,
                                             const Callback_GestureEvent_Void* event)
{
    return {};
}
Ark_PinchGestureInterface OnActionEndImpl(Ark_PinchGestureInterface peer,
                                          const Callback_GestureEvent_Void* event)
{
    return {};
}
Ark_PinchGestureInterface OnActionCancel0Impl(Ark_PinchGestureInterface peer,
                                              const Callback_Void* event)
{
    return {};
}
Ark_PinchGestureInterface OnActionCancel1Impl(Ark_PinchGestureInterface peer,
                                              const Callback_GestureEvent_Void* event)
{
    return {};
}
} // PinchGestureInterfaceAccessor
const GENERATED_ArkUIPinchGestureInterfaceAccessor* GetPinchGestureInterfaceAccessor()
{
    static const GENERATED_ArkUIPinchGestureInterfaceAccessor PinchGestureInterfaceAccessorImpl {
        PinchGestureInterfaceAccessor::DestroyPeerImpl,
        PinchGestureInterfaceAccessor::CtorImpl,
        PinchGestureInterfaceAccessor::GetFinalizerImpl,
        PinchGestureInterfaceAccessor::OnActionStartImpl,
        PinchGestureInterfaceAccessor::OnActionUpdateImpl,
        PinchGestureInterfaceAccessor::OnActionEndImpl,
        PinchGestureInterfaceAccessor::OnActionCancel0Impl,
        PinchGestureInterfaceAccessor::OnActionCancel1Impl,
    };
    return &PinchGestureInterfaceAccessorImpl;
}

}
