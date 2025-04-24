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
namespace PanelModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                Ark_Int32 flags)
{
    return {};
}
} // PanelModifier
namespace PanelInterfaceModifier {
void SetPanelOptionsImpl(Ark_NativePointer node,
                         Ark_Boolean show)
{
}
} // PanelInterfaceModifier
namespace PanelAttributeModifier {
void ModeImpl(Ark_NativePointer node,
              const Opt_PanelMode* value)
{
}
void TypeImpl(Ark_NativePointer node,
              const Opt_PanelType* value)
{
}
void DragBarImpl(Ark_NativePointer node,
                 const Opt_Boolean* value)
{
}
void CustomHeightImpl(Ark_NativePointer node,
                      const Opt_Union_Dimension_PanelHeight* value)
{
}
void FullHeightImpl(Ark_NativePointer node,
                    const Opt_Union_Number_String* value)
{
}
void HalfHeightImpl(Ark_NativePointer node,
                    const Opt_Union_Number_String* value)
{
}
void MiniHeightImpl(Ark_NativePointer node,
                    const Opt_Union_Number_String* value)
{
}
void ShowImpl(Ark_NativePointer node,
              const Opt_Boolean* value)
{
}
void BackgroundMaskImpl(Ark_NativePointer node,
                        const Opt_ResourceColor* value)
{
}
void ShowCloseIconImpl(Ark_NativePointer node,
                       const Opt_Boolean* value)
{
}
void OnChangeImpl(Ark_NativePointer node,
                  const Opt_Callback_Number_Number_PanelMode_Void* value)
{
}
void OnHeightChangeImpl(Ark_NativePointer node,
                        const Opt_Callback_Number_Void* value)
{
}
void _onChangeEvent_modeImpl(Ark_NativePointer node,
                             const Callback_Opt_PanelMode_Void* callback)
{
}
} // PanelAttributeModifier
const GENERATED_ArkUIPanelModifier* GetPanelModifier()
{
    static const GENERATED_ArkUIPanelModifier ArkUIPanelModifierImpl {
        PanelModifier::ConstructImpl,
        PanelInterfaceModifier::SetPanelOptionsImpl,
        PanelAttributeModifier::ModeImpl,
        PanelAttributeModifier::TypeImpl,
        PanelAttributeModifier::DragBarImpl,
        PanelAttributeModifier::CustomHeightImpl,
        PanelAttributeModifier::FullHeightImpl,
        PanelAttributeModifier::HalfHeightImpl,
        PanelAttributeModifier::MiniHeightImpl,
        PanelAttributeModifier::ShowImpl,
        PanelAttributeModifier::BackgroundMaskImpl,
        PanelAttributeModifier::ShowCloseIconImpl,
        PanelAttributeModifier::OnChangeImpl,
        PanelAttributeModifier::OnHeightChangeImpl,
        PanelAttributeModifier::_onChangeEvent_modeImpl,
    };
    return &ArkUIPanelModifierImpl;
}

}
