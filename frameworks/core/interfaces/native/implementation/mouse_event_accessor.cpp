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
#include "core/interfaces/native/implementation/mouse_event_peer.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace MouseEventAccessor {
void DestroyPeerImpl(MouseEventPeer* peer)
{
    delete peer;
}
Ark_NativePointer CtorImpl()
{
    return new MouseEventPeer();
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Ark_NativePointer GetButtonImpl(MouseEventPeer* peer)
{
    return nullptr;
}
void SetButtonImpl(MouseEventPeer* peer,
                   Ark_MouseButton button)
{
}
Ark_NativePointer GetActionImpl(MouseEventPeer* peer)
{
    return nullptr;
}
void SetActionImpl(MouseEventPeer* peer,
                   Ark_MouseAction action)
{
}
Ark_Int32 GetDisplayXImpl(MouseEventPeer* peer)
{
    return 0;
}
void SetDisplayXImpl(MouseEventPeer* peer,
                     const Ark_Number* displayX)
{
}
Ark_Int32 GetDisplayYImpl(MouseEventPeer* peer)
{
    return 0;
}
void SetDisplayYImpl(MouseEventPeer* peer,
                     const Ark_Number* displayY)
{
}
Ark_Int32 GetWindowXImpl(MouseEventPeer* peer)
{
    return 0;
}
void SetWindowXImpl(MouseEventPeer* peer,
                    const Ark_Number* windowX)
{
}
Ark_Int32 GetWindowYImpl(MouseEventPeer* peer)
{
    return 0;
}
void SetWindowYImpl(MouseEventPeer* peer,
                    const Ark_Number* windowY)
{
}
Ark_Int32 GetScreenXImpl(MouseEventPeer* peer)
{
    return 0;
}
void SetScreenXImpl(MouseEventPeer* peer,
                    const Ark_Number* screenX)
{
}
Ark_Int32 GetScreenYImpl(MouseEventPeer* peer)
{
    return 0;
}
void SetScreenYImpl(MouseEventPeer* peer,
                    const Ark_Number* screenY)
{
}
Ark_Int32 GetXImpl(MouseEventPeer* peer)
{
    return 0;
}
void SetXImpl(MouseEventPeer* peer,
              const Ark_Number* x)
{
}
Ark_Int32 GetYImpl(MouseEventPeer* peer)
{
    return 0;
}
void SetYImpl(MouseEventPeer* peer,
              const Ark_Number* y)
{
}
void SetStopPropagationImpl(MouseEventPeer* peer,
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
        MouseEventAccessor::SetStopPropagationImpl,
    };
    return &MouseEventAccessorImpl;
}

}
