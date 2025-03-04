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
void DestroyPeerImpl(Ark_AccessibilityHoverEvent peer)
{
}
Ark_AccessibilityHoverEvent CtorImpl()
{
    return nullptr;
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Ark_AccessibilityHoverType GetTypeImpl(Ark_AccessibilityHoverEvent peer)
{
    return {};
}
void SetTypeImpl(Ark_AccessibilityHoverEvent peer,
                 Ark_AccessibilityHoverType type)
{
}
Ark_Number GetXImpl(Ark_AccessibilityHoverEvent peer)
{
    return {};
}
void SetXImpl(Ark_AccessibilityHoverEvent peer,
              const Ark_Number* x)
{
}
Ark_Number GetYImpl(Ark_AccessibilityHoverEvent peer)
{
    return {};
}
void SetYImpl(Ark_AccessibilityHoverEvent peer,
              const Ark_Number* y)
{
}
Ark_Number GetDisplayXImpl(Ark_AccessibilityHoverEvent peer)
{
    return {};
}
void SetDisplayXImpl(Ark_AccessibilityHoverEvent peer,
                     const Ark_Number* displayX)
{
}
Ark_Number GetDisplayYImpl(Ark_AccessibilityHoverEvent peer)
{
    return {};
}
void SetDisplayYImpl(Ark_AccessibilityHoverEvent peer,
                     const Ark_Number* displayY)
{
}
Ark_Number GetWindowXImpl(Ark_AccessibilityHoverEvent peer)
{
    return {};
}
void SetWindowXImpl(Ark_AccessibilityHoverEvent peer,
                    const Ark_Number* windowX)
{
}
Ark_Number GetWindowYImpl(Ark_AccessibilityHoverEvent peer)
{
    return {};
}
void SetWindowYImpl(Ark_AccessibilityHoverEvent peer,
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
