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
namespace PanGestureInterfaceAccessor {
void DestroyPeerImpl(Ark_PanGestureInterface peer)
{
}
Ark_PanGestureInterface CtorImpl()
{
    return nullptr;
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Ark_PanGestureInterface OnActionStartImpl(Ark_PanGestureInterface peer,
                                          const Callback_GestureEvent_Void* event)
{
    return {};
}
Ark_PanGestureInterface OnActionUpdateImpl(Ark_PanGestureInterface peer,
                                           const Callback_GestureEvent_Void* event)
{
    return {};
}
Ark_PanGestureInterface OnActionEndImpl(Ark_PanGestureInterface peer,
                                        const Callback_GestureEvent_Void* event)
{
    return {};
}
Ark_PanGestureInterface OnActionCancel0Impl(Ark_PanGestureInterface peer,
                                            const Callback_Void* event)
{
    return {};
}
Ark_PanGestureInterface OnActionCancel1Impl(Ark_PanGestureInterface peer,
                                            const Callback_GestureEvent_Void* event)
{
    return {};
}
} // PanGestureInterfaceAccessor
const GENERATED_ArkUIPanGestureInterfaceAccessor* GetPanGestureInterfaceAccessor()
{
    static const GENERATED_ArkUIPanGestureInterfaceAccessor PanGestureInterfaceAccessorImpl {
        PanGestureInterfaceAccessor::DestroyPeerImpl,
        PanGestureInterfaceAccessor::CtorImpl,
        PanGestureInterfaceAccessor::GetFinalizerImpl,
        PanGestureInterfaceAccessor::OnActionStartImpl,
        PanGestureInterfaceAccessor::OnActionUpdateImpl,
        PanGestureInterfaceAccessor::OnActionEndImpl,
        PanGestureInterfaceAccessor::OnActionCancel0Impl,
        PanGestureInterfaceAccessor::OnActionCancel1Impl,
    };
    return &PanGestureInterfaceAccessorImpl;
}

}
