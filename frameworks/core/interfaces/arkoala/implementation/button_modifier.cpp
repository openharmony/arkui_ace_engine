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
namespace ButtonInterfaceModifier {
void SetButtonOptions0Impl(Ark_NativePointer node)
{
}
void SetButtonOptions1Impl(Ark_NativePointer node,
                           const Ark_ButtonOptions* options)
{
}
void SetButtonOptions2Impl(Ark_NativePointer node,
                           const ResourceStr* label,
                           const Opt_ButtonOptions* options)
{
}
} // ButtonInterfaceModifier
namespace ButtonAttributeModifier {
void TypeImpl(Ark_NativePointer node,
              Ark_Int32 value)
{
}
void StateEffectImpl(Ark_NativePointer node,
                     Ark_Boolean value)
{
}
void ButtonStyleImpl(Ark_NativePointer node,
                     Ark_Int32 value)
{
}
void ControlSizeImpl(Ark_NativePointer node,
                     Ark_Int32 value)
{
}
void RoleImpl(Ark_NativePointer node,
              Ark_Int32 value)
{
}
void FontColorImpl(Ark_NativePointer node,
                   const ResourceColor* value)
{
}
void FontSizeImpl(Ark_NativePointer node,
                  const Ark_Length* value)
{
}
void FontWeightImpl(Ark_NativePointer node,
                    const Type_ButtonAttribute_fontWeight_Arg0* value)
{
}
void FontStyleImpl(Ark_NativePointer node,
                   Ark_Int32 value)
{
}
void FontFamilyImpl(Ark_NativePointer node,
                    const Type_ButtonAttribute_fontFamily_Arg0* value)
{
}
void ContentModifierImpl(Ark_NativePointer node,
                         const Ark_CustomObject* modifier)
{
}
void LabelStyleImpl(Ark_NativePointer node,
                    const Ark_LabelStyle* value)
{
}
} // ButtonAttributeModifier
const GENERATED_ArkUIButtonModifier* GetButtonModifier()
{
    static const GENERATED_ArkUIButtonModifier ArkUIButtonModifierImpl {
        ButtonInterfaceModifier::SetButtonOptions0Impl,
        ButtonInterfaceModifier::SetButtonOptions1Impl,
        ButtonInterfaceModifier::SetButtonOptions2Impl,
        ButtonAttributeModifier::TypeImpl,
        ButtonAttributeModifier::StateEffectImpl,
        ButtonAttributeModifier::ButtonStyleImpl,
        ButtonAttributeModifier::ControlSizeImpl,
        ButtonAttributeModifier::RoleImpl,
        ButtonAttributeModifier::FontColorImpl,
        ButtonAttributeModifier::FontSizeImpl,
        ButtonAttributeModifier::FontWeightImpl,
        ButtonAttributeModifier::FontStyleImpl,
        ButtonAttributeModifier::FontFamilyImpl,
        ButtonAttributeModifier::ContentModifierImpl,
        ButtonAttributeModifier::LabelStyleImpl,
    };
    return &ArkUIButtonModifierImpl;
}

}
