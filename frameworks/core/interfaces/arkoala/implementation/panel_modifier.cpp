/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace PanelInterfaceModifier {
void SetPanelOptionsImpl(Ark_NativePointer node,
                         Ark_Boolean show)
{
}
} // PanelInterfaceModifier
namespace PanelAttributeModifier {
void ModeImpl(Ark_NativePointer node,
              enum Ark_PanelMode value)
{
}
void TypeImpl(Ark_NativePointer node,
              enum Ark_PanelType value)
{
}
void DragBarImpl(Ark_NativePointer node,
                 Ark_Boolean value)
{
}
void CustomHeightImpl(Ark_NativePointer node,
                      const Type_PanelAttribute_customHeight_Arg0* value)
{
}
void FullHeightImpl(Ark_NativePointer node,
                    const Type_PanelAttribute_fullHeight_Arg0* value)
{
}
void HalfHeightImpl(Ark_NativePointer node,
                    const Type_PanelAttribute_halfHeight_Arg0* value)
{
}
void MiniHeightImpl(Ark_NativePointer node,
                    const Type_PanelAttribute_miniHeight_Arg0* value)
{
}
void ShowImpl(Ark_NativePointer node,
              Ark_Boolean value)
{
}
void BackgroundMaskImpl(Ark_NativePointer node,
                        const ResourceColor* color)
{
}
void ShowCloseIconImpl(Ark_NativePointer node,
                       Ark_Boolean value)
{
}
void OnChangeImpl(Ark_NativePointer node,
                  Ark_Function event)
{
}
void OnHeightChangeImpl(Ark_NativePointer node,
                        Ark_Function callback)
{
}
} // PanelAttributeModifier
const GENERATED_ArkUIPanelModifier* GetPanelModifier()
{
    static const GENERATED_ArkUIPanelModifier ArkUIPanelModifierImpl {
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
    };
    return &ArkUIPanelModifierImpl;
}

}
