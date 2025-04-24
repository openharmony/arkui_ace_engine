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
namespace CheckboxGroupModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                Ark_Int32 flags)
{
    return {};
}
} // CheckboxGroupModifier
namespace CheckboxGroupInterfaceModifier {
void SetCheckboxGroupOptionsImpl(Ark_NativePointer node,
                                 const Opt_CheckboxGroupOptions* options)
{
}
} // CheckboxGroupInterfaceModifier
namespace CheckboxGroupAttributeModifier {
void SelectAll0Impl(Ark_NativePointer node,
                    const Opt_Boolean* value)
{
}
void SelectAll1Impl(Ark_NativePointer node,
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
                   const Opt_OnCheckboxGroupChangeCallback* value)
{
}
void OnChange1Impl(Ark_NativePointer node,
                   const Opt_OnCheckboxGroupChangeCallback* value)
{
}
void CheckboxShape0Impl(Ark_NativePointer node,
                        const Opt_CheckBoxShape* value)
{
}
void CheckboxShape1Impl(Ark_NativePointer node,
                        const Opt_CheckBoxShape* value)
{
}
void _onChangeEvent_selectAllImpl(Ark_NativePointer node,
                                  const Callback_Opt_Boolean_Void* callback)
{
}
} // CheckboxGroupAttributeModifier
const GENERATED_ArkUICheckboxGroupModifier* GetCheckboxGroupModifier()
{
    static const GENERATED_ArkUICheckboxGroupModifier ArkUICheckboxGroupModifierImpl {
        CheckboxGroupModifier::ConstructImpl,
        CheckboxGroupInterfaceModifier::SetCheckboxGroupOptionsImpl,
        CheckboxGroupAttributeModifier::SelectAll0Impl,
        CheckboxGroupAttributeModifier::SelectAll1Impl,
        CheckboxGroupAttributeModifier::SelectedColor0Impl,
        CheckboxGroupAttributeModifier::SelectedColor1Impl,
        CheckboxGroupAttributeModifier::UnselectedColor0Impl,
        CheckboxGroupAttributeModifier::UnselectedColor1Impl,
        CheckboxGroupAttributeModifier::Mark0Impl,
        CheckboxGroupAttributeModifier::Mark1Impl,
        CheckboxGroupAttributeModifier::OnChange0Impl,
        CheckboxGroupAttributeModifier::OnChange1Impl,
        CheckboxGroupAttributeModifier::CheckboxShape0Impl,
        CheckboxGroupAttributeModifier::CheckboxShape1Impl,
        CheckboxGroupAttributeModifier::_onChangeEvent_selectAllImpl,
    };
    return &ArkUICheckboxGroupModifierImpl;
}

}
