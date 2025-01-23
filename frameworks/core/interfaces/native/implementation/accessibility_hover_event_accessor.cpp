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
namespace AccessibilityHoverEventAccessor {
void DestroyPeerImpl(AccessibilityHoverEventPeer* peer)
{
}
Ark_NativePointer CtorImpl()
{
    return nullptr;
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Ark_NativePointer GetTypeImpl(AccessibilityHoverEventPeer* peer)
{
    return nullptr;
}
void SetTypeImpl(AccessibilityHoverEventPeer* peer,
                 Ark_AccessibilityHoverType type)
{
}
Ark_Int32 GetXImpl(AccessibilityHoverEventPeer* peer)
{
    return 0;
}
void SetXImpl(AccessibilityHoverEventPeer* peer,
              const Ark_Number* x)
{
}
Ark_Int32 GetYImpl(AccessibilityHoverEventPeer* peer)
{
    return 0;
}
void SetYImpl(AccessibilityHoverEventPeer* peer,
              const Ark_Number* y)
{
}
Ark_Int32 GetDisplayXImpl(AccessibilityHoverEventPeer* peer)
{
    return 0;
}
void SetDisplayXImpl(AccessibilityHoverEventPeer* peer,
                     const Ark_Number* displayX)
{
}
Ark_Int32 GetDisplayYImpl(AccessibilityHoverEventPeer* peer)
{
    return 0;
}
void SetDisplayYImpl(AccessibilityHoverEventPeer* peer,
                     const Ark_Number* displayY)
{
}
Ark_Int32 GetWindowXImpl(AccessibilityHoverEventPeer* peer)
{
    return 0;
}
void SetWindowXImpl(AccessibilityHoverEventPeer* peer,
                    const Ark_Number* windowX)
{
}
Ark_Int32 GetWindowYImpl(AccessibilityHoverEventPeer* peer)
{
    return 0;
}
void SetWindowYImpl(AccessibilityHoverEventPeer* peer,
                    const Ark_Number* windowY)
{
}
} // AccessibilityHoverEventAccessor
const GENERATED_ArkUIAccessibilityHoverEventAccessor* GetAccessibilityHoverEventAccessor()
{
    static const GENERATED_ArkUIAccessibilityHoverEventAccessor AccessibilityHoverEventAccessorImpl {
        AccessibilityHoverEventAccessor::DestroyPeerImpl,
        AccessibilityHoverEventAccessor::CtorImpl,
        AccessibilityHoverEventAccessor::GetFinalizerImpl,
        AccessibilityHoverEventAccessor::GetTypeImpl,
        AccessibilityHoverEventAccessor::SetTypeImpl,
        AccessibilityHoverEventAccessor::GetXImpl,
        AccessibilityHoverEventAccessor::SetXImpl,
        AccessibilityHoverEventAccessor::GetYImpl,
        AccessibilityHoverEventAccessor::SetYImpl,
        AccessibilityHoverEventAccessor::GetDisplayXImpl,
        AccessibilityHoverEventAccessor::SetDisplayXImpl,
        AccessibilityHoverEventAccessor::GetDisplayYImpl,
        AccessibilityHoverEventAccessor::SetDisplayYImpl,
        AccessibilityHoverEventAccessor::GetWindowXImpl,
        AccessibilityHoverEventAccessor::SetWindowXImpl,
        AccessibilityHoverEventAccessor::GetWindowYImpl,
        AccessibilityHoverEventAccessor::SetWindowYImpl,
    };
    return &AccessibilityHoverEventAccessorImpl;
}

}
