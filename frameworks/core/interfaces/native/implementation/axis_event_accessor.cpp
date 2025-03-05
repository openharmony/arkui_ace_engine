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
namespace AxisEventAccessor {
void DestroyPeerImpl(Ark_AxisEvent peer)
{
}
Ark_AxisEvent CtorImpl()
{
    return nullptr;
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Ark_Number GetHorizontalAxisValueImpl(Ark_AxisEvent peer)
{
    return {};
}
Ark_Number GetVerticalAxisValueImpl(Ark_AxisEvent peer)
{
    return {};
}
Ark_AxisAction GetActionImpl(Ark_AxisEvent peer)
{
    return {};
}
void SetActionImpl(Ark_AxisEvent peer,
                   Ark_AxisAction action)
{
}
Ark_Number GetDisplayXImpl(Ark_AxisEvent peer)
{
    return {};
}
void SetDisplayXImpl(Ark_AxisEvent peer,
                     const Ark_Number* displayX)
{
}
Ark_Number GetDisplayYImpl(Ark_AxisEvent peer)
{
    return {};
}
void SetDisplayYImpl(Ark_AxisEvent peer,
                     const Ark_Number* displayY)
{
}
Ark_Number GetWindowXImpl(Ark_AxisEvent peer)
{
    return {};
}
void SetWindowXImpl(Ark_AxisEvent peer,
                    const Ark_Number* windowX)
{
}
Ark_Number GetWindowYImpl(Ark_AxisEvent peer)
{
    return {};
}
void SetWindowYImpl(Ark_AxisEvent peer,
                    const Ark_Number* windowY)
{
}
Ark_Number GetXImpl(Ark_AxisEvent peer)
{
    return {};
}
void SetXImpl(Ark_AxisEvent peer,
              const Ark_Number* x)
{
}
Ark_Number GetYImpl(Ark_AxisEvent peer)
{
    return {};
}
void SetYImpl(Ark_AxisEvent peer,
              const Ark_Number* y)
{
}
Ark_Number GetScrollStepImpl(Ark_AxisEvent peer)
{
    return {};
}
void SetScrollStepImpl(Ark_AxisEvent peer,
                       const Ark_Number* scrollStep)
{
}
Callback_Void GetPropagationImpl(Ark_AxisEvent peer)
{
    return {};
}
void SetPropagationImpl(Ark_AxisEvent peer,
                        const Callback_Void* propagation)
{
}
} // AxisEventAccessor
const GENERATED_ArkUIAxisEventAccessor* GetAxisEventAccessor()
{
    static const GENERATED_ArkUIAxisEventAccessor AxisEventAccessorImpl {
        AxisEventAccessor::DestroyPeerImpl,
        AxisEventAccessor::CtorImpl,
        AxisEventAccessor::GetFinalizerImpl,
        AxisEventAccessor::GetHorizontalAxisValueImpl,
        AxisEventAccessor::GetVerticalAxisValueImpl,
        AxisEventAccessor::GetActionImpl,
        AxisEventAccessor::SetActionImpl,
        AxisEventAccessor::GetDisplayXImpl,
        AxisEventAccessor::SetDisplayXImpl,
        AxisEventAccessor::GetDisplayYImpl,
        AxisEventAccessor::SetDisplayYImpl,
        AxisEventAccessor::GetWindowXImpl,
        AxisEventAccessor::SetWindowXImpl,
        AxisEventAccessor::GetWindowYImpl,
        AxisEventAccessor::SetWindowYImpl,
        AxisEventAccessor::GetXImpl,
        AxisEventAccessor::SetXImpl,
        AxisEventAccessor::GetYImpl,
        AxisEventAccessor::SetYImpl,
        AxisEventAccessor::GetScrollStepImpl,
        AxisEventAccessor::SetScrollStepImpl,
        AxisEventAccessor::GetPropagationImpl,
        AxisEventAccessor::SetPropagationImpl,
    };
    return &AxisEventAccessorImpl;
}

}
