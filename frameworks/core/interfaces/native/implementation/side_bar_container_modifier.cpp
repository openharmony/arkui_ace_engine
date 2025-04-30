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
namespace SideBarContainerModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                Ark_Int32 flags)
{
    return {};
}
} // SideBarContainerModifier
namespace SideBarContainerInterfaceModifier {
void SetSideBarContainerOptionsImpl(Ark_NativePointer node,
                                    const Opt_SideBarContainerType* type)
{
}
} // SideBarContainerInterfaceModifier
namespace SideBarContainerAttributeModifier {
void ShowSideBarImpl(Ark_NativePointer node,
                     const Opt_Boolean* value)
{
}
void ControlButtonImpl(Ark_NativePointer node,
                       const Opt_ButtonStyle* value)
{
}
void ShowControlButtonImpl(Ark_NativePointer node,
                           const Opt_Boolean* value)
{
}
void OnChangeImpl(Ark_NativePointer node,
                  const Opt_Callback_Boolean_Void* value)
{
}
void SideBarWidth0Impl(Ark_NativePointer node,
                       const Opt_Number* value)
{
}
void SideBarWidth1Impl(Ark_NativePointer node,
                       const Opt_Length* value)
{
}
void MinSideBarWidth0Impl(Ark_NativePointer node,
                          const Opt_Number* value)
{
}
void MinSideBarWidth1Impl(Ark_NativePointer node,
                          const Opt_Length* value)
{
}
void MaxSideBarWidth0Impl(Ark_NativePointer node,
                          const Opt_Number* value)
{
}
void MaxSideBarWidth1Impl(Ark_NativePointer node,
                          const Opt_Length* value)
{
}
void AutoHideImpl(Ark_NativePointer node,
                  const Opt_Boolean* value)
{
}
void SideBarPositionImpl(Ark_NativePointer node,
                         const Opt_SideBarPosition* value)
{
}
void DividerImpl(Ark_NativePointer node,
                 const Opt_DividerStyle* value)
{
}
void MinContentWidthImpl(Ark_NativePointer node,
                         const Opt_Length* value)
{
}
void _onChangeEvent_showSideBarImpl(Ark_NativePointer node,
                                    const Callback_Opt_Boolean_Void* callback)
{
}
} // SideBarContainerAttributeModifier
const GENERATED_ArkUISideBarContainerModifier* GetSideBarContainerModifier()
{
    static const GENERATED_ArkUISideBarContainerModifier ArkUISideBarContainerModifierImpl {
        SideBarContainerModifier::ConstructImpl,
        SideBarContainerInterfaceModifier::SetSideBarContainerOptionsImpl,
        SideBarContainerAttributeModifier::ShowSideBarImpl,
        SideBarContainerAttributeModifier::ControlButtonImpl,
        SideBarContainerAttributeModifier::ShowControlButtonImpl,
        SideBarContainerAttributeModifier::OnChangeImpl,
        SideBarContainerAttributeModifier::SideBarWidth0Impl,
        SideBarContainerAttributeModifier::SideBarWidth1Impl,
        SideBarContainerAttributeModifier::MinSideBarWidth0Impl,
        SideBarContainerAttributeModifier::MinSideBarWidth1Impl,
        SideBarContainerAttributeModifier::MaxSideBarWidth0Impl,
        SideBarContainerAttributeModifier::MaxSideBarWidth1Impl,
        SideBarContainerAttributeModifier::AutoHideImpl,
        SideBarContainerAttributeModifier::SideBarPositionImpl,
        SideBarContainerAttributeModifier::DividerImpl,
        SideBarContainerAttributeModifier::MinContentWidthImpl,
        SideBarContainerAttributeModifier::_onChangeEvent_showSideBarImpl,
    };
    return &ArkUISideBarContainerModifierImpl;
}

}
