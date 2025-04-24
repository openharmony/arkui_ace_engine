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
namespace CheckboxModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                Ark_Int32 flags)
{
    return {};
}
} // CheckboxModifier
namespace CheckboxInterfaceModifier {
void SetCheckboxOptionsImpl(Ark_NativePointer node,
                            const Opt_CheckboxOptions* options)
{
}
} // CheckboxInterfaceModifier
namespace CheckboxAttributeModifier {
void Select0Impl(Ark_NativePointer node,
                 const Opt_Boolean* value)
{
}
void Select1Impl(Ark_NativePointer node,
                 const Opt_Boolean* value)
{
}
void SelectedColor0Impl(Ark_NativePointer node,
                        const Opt_ResourceColor* value)
{
}
void SelectedColor1Impl(Ark_NativePointer node,
                        const Opt_ResourceColor* value)
{
}
void Shape0Impl(Ark_NativePointer node,
                const Opt_CheckBoxShape* value)
{
}
void Shape1Impl(Ark_NativePointer node,
                const Opt_CheckBoxShape* value)
{
}
void UnselectedColor0Impl(Ark_NativePointer node,
                          const Opt_ResourceColor* value)
{
}
void UnselectedColor1Impl(Ark_NativePointer node,
                          const Opt_ResourceColor* value)
{
}
void Mark0Impl(Ark_NativePointer node,
               const Opt_MarkStyle* value)
{
}
void Mark1Impl(Ark_NativePointer node,
               const Opt_MarkStyle* value)
{
}
void OnChange0Impl(Ark_NativePointer node,
                   const Opt_OnCheckboxChangeCallback* value)
{
}
void OnChange1Impl(Ark_NativePointer node,
                   const Opt_OnCheckboxChangeCallback* value)
{
}
void ContentModifier0Impl(Ark_NativePointer node,
                          const Opt_ContentModifier* value)
{
}
void ContentModifier1Impl(Ark_NativePointer node,
                          const Opt_ContentModifier* value)
{
}
void _onChangeEvent_selectImpl(Ark_NativePointer node,
                               const Callback_Opt_Boolean_Void* callback)
{
}
} // CheckboxAttributeModifier
const GENERATED_ArkUICheckboxModifier* GetCheckboxModifier()
{
    static const GENERATED_ArkUICheckboxModifier ArkUICheckboxModifierImpl {
        CheckboxModifier::ConstructImpl,
        CheckboxInterfaceModifier::SetCheckboxOptionsImpl,
        CheckboxAttributeModifier::Select0Impl,
        CheckboxAttributeModifier::Select1Impl,
        CheckboxAttributeModifier::SelectedColor0Impl,
        CheckboxAttributeModifier::SelectedColor1Impl,
        CheckboxAttributeModifier::Shape0Impl,
        CheckboxAttributeModifier::Shape1Impl,
        CheckboxAttributeModifier::UnselectedColor0Impl,
        CheckboxAttributeModifier::UnselectedColor1Impl,
        CheckboxAttributeModifier::Mark0Impl,
        CheckboxAttributeModifier::Mark1Impl,
        CheckboxAttributeModifier::OnChange0Impl,
        CheckboxAttributeModifier::OnChange1Impl,
        CheckboxAttributeModifier::ContentModifier0Impl,
        CheckboxAttributeModifier::ContentModifier1Impl,
        CheckboxAttributeModifier::_onChangeEvent_selectImpl,
    };
    return &ArkUICheckboxModifierImpl;
}

}
