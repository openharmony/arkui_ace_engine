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
namespace MouseEventAccessor {
void DestroyPeerImpl(Ark_MouseEvent peer)
{
}
Ark_MouseEvent CtorImpl()
{
    return nullptr;
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Ark_MouseButton GetButtonImpl(Ark_MouseEvent peer)
{
    return {};
}
void SetButtonImpl(Ark_MouseEvent peer,
                   Ark_MouseButton button)
{
}
Ark_MouseAction GetActionImpl(Ark_MouseEvent peer)
{
    return {};
}
void SetActionImpl(Ark_MouseEvent peer,
                   Ark_MouseAction action)
{
}
Ark_Number GetDisplayXImpl(Ark_MouseEvent peer)
{
    return {};
}
void SetDisplayXImpl(Ark_MouseEvent peer,
                     const Ark_Number* displayX)
{
}
Ark_Number GetDisplayYImpl(Ark_MouseEvent peer)
{
    return {};
}
void SetDisplayYImpl(Ark_MouseEvent peer,
                     const Ark_Number* displayY)
{
}
Ark_Number GetWindowXImpl(Ark_MouseEvent peer)
{
    return {};
}
void SetWindowXImpl(Ark_MouseEvent peer,
                    const Ark_Number* windowX)
{
}
Ark_Number GetWindowYImpl(Ark_MouseEvent peer)
{
    return {};
}
void SetWindowYImpl(Ark_MouseEvent peer,
                    const Ark_Number* windowY)
{
}
Ark_Number GetScreenXImpl(Ark_MouseEvent peer)
{
    return {};
}
void SetScreenXImpl(Ark_MouseEvent peer,
                    const Ark_Number* screenX)
{
}
Ark_Number GetScreenYImpl(Ark_MouseEvent peer)
{
    return {};
}
void SetScreenYImpl(Ark_MouseEvent peer,
                    const Ark_Number* screenY)
{
}
Ark_Number GetXImpl(Ark_MouseEvent peer)
{
    return {};
}
void SetXImpl(Ark_MouseEvent peer,
              const Ark_Number* x)
{
}
Ark_Number GetYImpl(Ark_MouseEvent peer)
{
    return {};
}
void SetYImpl(Ark_MouseEvent peer,
              const Ark_Number* y)
{
}
Callback_Void GetStopPropagationImpl(Ark_MouseEvent peer)
{
    return {};
}
void SetStopPropagationImpl(Ark_MouseEvent peer,
                            const Callback_Void* stopPropagation)
{
}
} // MouseEventAccessor
const GENERATED_ArkUIMouseEventAccessor* GetMouseEventAccessor()
{
    static const GENERATED_ArkUIMouseEventAccessor MouseEventAccessorImpl {
        MouseEventAccessor::DestroyPeerImpl,
        MouseEventAccessor::CtorImpl,
        MouseEventAccessor::GetFinalizerImpl,
        MouseEventAccessor::GetButtonImpl,
        MouseEventAccessor::SetButtonImpl,
        MouseEventAccessor::GetActionImpl,
        MouseEventAccessor::SetActionImpl,
        MouseEventAccessor::GetDisplayXImpl,
        MouseEventAccessor::SetDisplayXImpl,
        MouseEventAccessor::GetDisplayYImpl,
        MouseEventAccessor::SetDisplayYImpl,
        MouseEventAccessor::GetWindowXImpl,
        MouseEventAccessor::SetWindowXImpl,
        MouseEventAccessor::GetWindowYImpl,
        MouseEventAccessor::SetWindowYImpl,
        MouseEventAccessor::GetScreenXImpl,
        MouseEventAccessor::SetScreenXImpl,
        MouseEventAccessor::GetScreenYImpl,
        MouseEventAccessor::SetScreenYImpl,
        MouseEventAccessor::GetXImpl,
        MouseEventAccessor::SetXImpl,
        MouseEventAccessor::GetYImpl,
        MouseEventAccessor::SetYImpl,
        MouseEventAccessor::GetStopPropagationImpl,
        MouseEventAccessor::SetStopPropagationImpl,
    };
    return &MouseEventAccessorImpl;
}

}
