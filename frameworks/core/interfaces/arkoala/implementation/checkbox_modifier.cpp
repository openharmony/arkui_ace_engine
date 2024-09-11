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
namespace CheckboxInterfaceModifier {
void SetCheckboxOptionsImpl(Ark_NativePointer node,
                            const Opt_CheckboxOptions* options)
{
}
} // CheckboxInterfaceModifier
namespace CheckboxAttributeModifier {
void SelectImpl(Ark_NativePointer node,
                Ark_Boolean value)
{
}
void SelectedColorImpl(Ark_NativePointer node,
                       const ResourceColor* value)
{
}
void ShapeImpl(Ark_NativePointer node,
               enum Ark_CheckBoxShape value)
{
}
void UnselectedColorImpl(Ark_NativePointer node,
                         const ResourceColor* value)
{
}
void MarkImpl(Ark_NativePointer node,
              const Ark_MarkStyle* value)
{
}
void OnChangeImpl(Ark_NativePointer node,
                  Ark_Function callback)
{
}
void ContentModifierImpl(Ark_NativePointer node,
                         const Ark_CustomObject* modifier)
{
}
} // CheckboxAttributeModifier
const GENERATED_ArkUICheckboxModifier* GetCheckboxModifier()
{
    static const GENERATED_ArkUICheckboxModifier ArkUICheckboxModifierImpl {
        CheckboxInterfaceModifier::SetCheckboxOptionsImpl,
        CheckboxAttributeModifier::SelectImpl,
        CheckboxAttributeModifier::SelectedColorImpl,
        CheckboxAttributeModifier::ShapeImpl,
        CheckboxAttributeModifier::UnselectedColorImpl,
        CheckboxAttributeModifier::MarkImpl,
        CheckboxAttributeModifier::OnChangeImpl,
        CheckboxAttributeModifier::ContentModifierImpl,
    };
    return &ArkUICheckboxModifierImpl;
}

}
