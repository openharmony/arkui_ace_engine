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
void DestroyPeerImpl(Ark_ClickEvent peer)
{
}
Ark_ClickEvent CtorImpl()
{
    return nullptr;
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Ark_Number GetDisplayXImpl(Ark_ClickEvent peer)
{
    return {};
}
void SetDisplayXImpl(Ark_ClickEvent peer,
                     const Ark_Number* displayX)
{
}
Ark_Number GetDisplayYImpl(Ark_ClickEvent peer)
{
    return {};
}
void SetDisplayYImpl(Ark_ClickEvent peer,
                     const Ark_Number* displayY)
{
}
Ark_Number GetWindowXImpl(Ark_ClickEvent peer)
{
    return {};
}
void SetWindowXImpl(Ark_ClickEvent peer,
                    const Ark_Number* windowX)
{
}
Ark_Number GetWindowYImpl(Ark_ClickEvent peer)
{
    return {};
}
void SetWindowYImpl(Ark_ClickEvent peer,
                    const Ark_Number* windowY)
{
}
Ark_Number GetScreenXImpl(Ark_ClickEvent peer)
{
    return {};
}
void SetScreenXImpl(Ark_ClickEvent peer,
                    const Ark_Number* screenX)
{
}
Ark_Number GetScreenYImpl(Ark_ClickEvent peer)
{
    return {};
}
void SetScreenYImpl(Ark_ClickEvent peer,
                    const Ark_Number* screenY)
{
}
Ark_Number GetXImpl(Ark_ClickEvent peer)
{
    return {};
}
void SetXImpl(Ark_ClickEvent peer,
              const Ark_Number* x)
{
}
Ark_Number GetYImpl(Ark_ClickEvent peer)
{
    return {};
}
void SetYImpl(Ark_ClickEvent peer,
              const Ark_Number* y)
{
}
Ark_InteractionHand GetHandImpl(Ark_ClickEvent peer)
{
    return {};
}
void SetHandImpl(Ark_ClickEvent peer,
                 Ark_InteractionHand hand)
{
}
Callback_Void GetPreventDefaultImpl(Ark_ClickEvent peer)
{
    return {};
}
void SetPreventDefaultImpl(Ark_ClickEvent peer,
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
        ClickEventAccessor::GetHandImpl,
        ClickEventAccessor::SetHandImpl,
        ClickEventAccessor::GetPreventDefaultImpl,
        ClickEventAccessor::SetPreventDefaultImpl,
    };
    return &ClickEventAccessorImpl;
}

}
