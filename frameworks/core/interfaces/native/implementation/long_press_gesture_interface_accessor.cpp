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
namespace LongPressGestureInterfaceAccessor {
void DestroyPeerImpl(Ark_LongPressGestureInterface peer)
{
}
Ark_LongPressGestureInterface CtorImpl()
{
    return nullptr;
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Ark_LongPressGestureInterface OnActionImpl(Ark_LongPressGestureInterface peer,
                                           const Callback_GestureEvent_Void* event)
{
    return {};
}
Ark_LongPressGestureInterface OnActionEndImpl(Ark_LongPressGestureInterface peer,
                                              const Callback_GestureEvent_Void* event)
{
    return {};
}
Ark_LongPressGestureInterface OnActionCancel0Impl(Ark_LongPressGestureInterface peer,
                                                  const Callback_Void* event)
{
    return {};
}
Ark_LongPressGestureInterface OnActionCancel1Impl(Ark_LongPressGestureInterface peer,
                                                  const Callback_GestureEvent_Void* event)
{
    return {};
}
} // LongPressGestureInterfaceAccessor
const GENERATED_ArkUILongPressGestureInterfaceAccessor* GetLongPressGestureInterfaceAccessor()
{
    static const GENERATED_ArkUILongPressGestureInterfaceAccessor LongPressGestureInterfaceAccessorImpl {
        LongPressGestureInterfaceAccessor::DestroyPeerImpl,
        LongPressGestureInterfaceAccessor::CtorImpl,
        LongPressGestureInterfaceAccessor::GetFinalizerImpl,
        LongPressGestureInterfaceAccessor::OnActionImpl,
        LongPressGestureInterfaceAccessor::OnActionEndImpl,
        LongPressGestureInterfaceAccessor::OnActionCancel0Impl,
        LongPressGestureInterfaceAccessor::OnActionCancel1Impl,
    };
    return &LongPressGestureInterfaceAccessorImpl;
}

}
