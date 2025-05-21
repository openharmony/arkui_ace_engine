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
namespace TouchTestInfoAccessor {
void DestroyPeerImpl(Ark_TouchTestInfo peer)
{
}
Ark_TouchTestInfo CtorImpl()
{
    return nullptr;
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Ark_Number GetWindowXImpl(Ark_TouchTestInfo peer)
{
    return {};
}
void SetWindowXImpl(Ark_TouchTestInfo peer,
                    const Ark_Number* windowX)
{
}
Ark_Number GetWindowYImpl(Ark_TouchTestInfo peer)
{
    return {};
}
void SetWindowYImpl(Ark_TouchTestInfo peer,
                    const Ark_Number* windowY)
{
}
Ark_Number GetParentXImpl(Ark_TouchTestInfo peer)
{
    return {};
}
void SetParentXImpl(Ark_TouchTestInfo peer,
                    const Ark_Number* parentX)
{
}
Ark_Number GetParentYImpl(Ark_TouchTestInfo peer)
{
    return {};
}
void SetParentYImpl(Ark_TouchTestInfo peer,
                    const Ark_Number* parentY)
{
}
Ark_Number GetXImpl(Ark_TouchTestInfo peer)
{
    return {};
}
void SetXImpl(Ark_TouchTestInfo peer,
              const Ark_Number* x)
{
}
Ark_Number GetYImpl(Ark_TouchTestInfo peer)
{
    return {};
}
void SetYImpl(Ark_TouchTestInfo peer,
              const Ark_Number* y)
{
}
Ark_RectResult GetRectImpl(Ark_TouchTestInfo peer)
{
    return {};
}
void SetRectImpl(Ark_TouchTestInfo peer,
                 const Ark_RectResult* rect)
{
}
Ark_String GetIdImpl(Ark_TouchTestInfo peer)
{
    return {};
}
void SetIdImpl(Ark_TouchTestInfo peer,
               const Ark_String* id)
{
}
} // TouchTestInfoAccessor
const GENERATED_ArkUITouchTestInfoAccessor* GetTouchTestInfoAccessor()
{
    static const GENERATED_ArkUITouchTestInfoAccessor TouchTestInfoAccessorImpl {
        TouchTestInfoAccessor::DestroyPeerImpl,
        TouchTestInfoAccessor::CtorImpl,
        TouchTestInfoAccessor::GetFinalizerImpl,
        TouchTestInfoAccessor::GetWindowXImpl,
        TouchTestInfoAccessor::SetWindowXImpl,
        TouchTestInfoAccessor::GetWindowYImpl,
        TouchTestInfoAccessor::SetWindowYImpl,
        TouchTestInfoAccessor::GetParentXImpl,
        TouchTestInfoAccessor::SetParentXImpl,
        TouchTestInfoAccessor::GetParentYImpl,
        TouchTestInfoAccessor::SetParentYImpl,
        TouchTestInfoAccessor::GetXImpl,
        TouchTestInfoAccessor::SetXImpl,
        TouchTestInfoAccessor::GetYImpl,
        TouchTestInfoAccessor::SetYImpl,
        TouchTestInfoAccessor::GetRectImpl,
        TouchTestInfoAccessor::SetRectImpl,
        TouchTestInfoAccessor::GetIdImpl,
        TouchTestInfoAccessor::SetIdImpl,
    };
    return &TouchTestInfoAccessorImpl;
}

}
