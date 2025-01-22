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
namespace ClickEventAccessor {
void DestroyPeerImpl(ClickEventPeer* peer)
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
Ark_Int32 GetDisplayXImpl(ClickEventPeer* peer)
{
    return 0;
}
void SetDisplayXImpl(ClickEventPeer* peer,
                     const Ark_Number* displayX)
{
}
Ark_Int32 GetDisplayYImpl(ClickEventPeer* peer)
{
    return 0;
}
void SetDisplayYImpl(ClickEventPeer* peer,
                     const Ark_Number* displayY)
{
}
Ark_Int32 GetWindowXImpl(ClickEventPeer* peer)
{
    return 0;
}
void SetWindowXImpl(ClickEventPeer* peer,
                    const Ark_Number* windowX)
{
}
Ark_Int32 GetWindowYImpl(ClickEventPeer* peer)
{
    return 0;
}
void SetWindowYImpl(ClickEventPeer* peer,
                    const Ark_Number* windowY)
{
}
Ark_Int32 GetScreenXImpl(ClickEventPeer* peer)
{
    return 0;
}
void SetScreenXImpl(ClickEventPeer* peer,
                    const Ark_Number* screenX)
{
}
Ark_Int32 GetScreenYImpl(ClickEventPeer* peer)
{
    return 0;
}
void SetScreenYImpl(ClickEventPeer* peer,
                    const Ark_Number* screenY)
{
}
Ark_Int32 GetXImpl(ClickEventPeer* peer)
{
    return 0;
}
void SetXImpl(ClickEventPeer* peer,
              const Ark_Number* x)
{
}
Ark_Int32 GetYImpl(ClickEventPeer* peer)
{
    return 0;
}
void SetYImpl(ClickEventPeer* peer,
              const Ark_Number* y)
{
}
void SetPreventDefaultImpl(ClickEventPeer* peer,
                           const Callback_Void* preventDefault)
{
}
} // ClickEventAccessor
const GENERATED_ArkUIClickEventAccessor* GetClickEventAccessor()
{
    static const GENERATED_ArkUIClickEventAccessor ClickEventAccessorImpl {
        ClickEventAccessor::DestroyPeerImpl,
        ClickEventAccessor::CtorImpl,
        ClickEventAccessor::GetFinalizerImpl,
        ClickEventAccessor::GetDisplayXImpl,
        ClickEventAccessor::SetDisplayXImpl,
        ClickEventAccessor::GetDisplayYImpl,
        ClickEventAccessor::SetDisplayYImpl,
        ClickEventAccessor::GetWindowXImpl,
        ClickEventAccessor::SetWindowXImpl,
        ClickEventAccessor::GetWindowYImpl,
        ClickEventAccessor::SetWindowYImpl,
        ClickEventAccessor::GetScreenXImpl,
        ClickEventAccessor::SetScreenXImpl,
        ClickEventAccessor::GetScreenYImpl,
        ClickEventAccessor::SetScreenYImpl,
        ClickEventAccessor::GetXImpl,
        ClickEventAccessor::SetXImpl,
        ClickEventAccessor::GetYImpl,
        ClickEventAccessor::SetYImpl,
        ClickEventAccessor::SetPreventDefaultImpl,
    };
    return &ClickEventAccessorImpl;
}

struct ClickEventPeer {
    virtual ~ClickEventPeer() = default;
};
}
