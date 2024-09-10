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
namespace RichEditorInterfaceModifier {
void SetRichEditorOptions0Impl(Ark_NativePointer node,
                               const Ark_RichEditorOptions* value)
{
}
void SetRichEditorOptions1Impl(Ark_NativePointer node,
                               const Ark_RichEditorStyledStringOptions* options)
{
}
} // RichEditorInterfaceModifier
namespace RichEditorAttributeModifier {
void OnReadyImpl(Ark_NativePointer node,
                 Ark_Function callback)
{
}
void OnSelectImpl(Ark_NativePointer node,
                  Ark_Function callback)
{
}
void OnSelectionChangeImpl(Ark_NativePointer node,
                           Ark_Function callback)
{
}
void AboutToIMEInputImpl(Ark_NativePointer node,
                         Ark_Function callback)
{
}
void OnIMEInputCompleteImpl(Ark_NativePointer node,
                            Ark_Function callback)
{
}
void OnDidIMEInputImpl(Ark_NativePointer node,
                       Ark_Function callback)
{
}
void AboutToDeleteImpl(Ark_NativePointer node,
                       Ark_Function callback)
{
}
void OnDeleteCompleteImpl(Ark_NativePointer node,
                          Ark_Function callback)
{
}
void CopyOptionsImpl(Ark_NativePointer node,
                     Ark_Int32 value)
{
}
void BindSelectionMenuImpl(Ark_NativePointer node,
                           Ark_Int32 spanType,
                           const CustomBuilder* content,
                           const Type_RichEditorAttribute_bindSelectionMenu_Arg2* responseType,
                           const Opt_SelectionMenuOptions* options)
{
}
void CustomKeyboardImpl(Ark_NativePointer node,
                        const CustomBuilder* value,
                        const Opt_KeyboardOptions* options)
{
}
void OnPasteImpl(Ark_NativePointer node,
                 Ark_Function callback)
{
}
void EnableDataDetectorImpl(Ark_NativePointer node,
                            Ark_Boolean enable)
{
}
void EnablePreviewTextImpl(Ark_NativePointer node,
                           Ark_Boolean enable)
{
}
void DataDetectorConfigImpl(Ark_NativePointer node,
                            const Ark_TextDataDetectorConfig* config)
{
}
void PlaceholderImpl(Ark_NativePointer node,
                     const ResourceStr* value,
                     const Opt_PlaceholderStyle* style)
{
}
void CaretColorImpl(Ark_NativePointer node,
                    const ResourceColor* value)
{
}
void SelectedBackgroundColorImpl(Ark_NativePointer node,
                                 const ResourceColor* value)
{
}
void OnEditingChangeImpl(Ark_NativePointer node,
                         Ark_Function callback)
{
}
void EnterKeyTypeImpl(Ark_NativePointer node,
                      Ark_Int32 value)
{
}
void OnSubmitImpl(Ark_NativePointer node,
                  Ark_Function callback)
{
}
void OnWillChangeImpl(Ark_NativePointer node,
                      Ark_Function callback)
{
}
void OnDidChangeImpl(Ark_NativePointer node,
                     Ark_Function callback)
{
}
void OnCutImpl(Ark_NativePointer node,
               Ark_Function callback)
{
}
void OnCopyImpl(Ark_NativePointer node,
                Ark_Function callback)
{
}
void EditMenuOptionsImpl(Ark_NativePointer node,
                         const Ark_Materialized* editMenu)
{
}
void EnableKeyboardOnFocusImpl(Ark_NativePointer node,
                               Ark_Boolean isEnabled)
{
}
void EnableHapticFeedbackImpl(Ark_NativePointer node,
                              Ark_Boolean isEnabled)
{
}
void BarStateImpl(Ark_NativePointer node,
                  Ark_Int32 state)
{
}
} // RichEditorAttributeModifier
const GENERATED_ArkUIRichEditorModifier* GetRichEditorModifier()
{
    static const GENERATED_ArkUIRichEditorModifier ArkUIRichEditorModifierImpl {
        RichEditorInterfaceModifier::SetRichEditorOptions0Impl,
        RichEditorInterfaceModifier::SetRichEditorOptions1Impl,
        RichEditorAttributeModifier::OnReadyImpl,
        RichEditorAttributeModifier::OnSelectImpl,
        RichEditorAttributeModifier::OnSelectionChangeImpl,
        RichEditorAttributeModifier::AboutToIMEInputImpl,
        RichEditorAttributeModifier::OnIMEInputCompleteImpl,
        RichEditorAttributeModifier::OnDidIMEInputImpl,
        RichEditorAttributeModifier::AboutToDeleteImpl,
        RichEditorAttributeModifier::OnDeleteCompleteImpl,
        RichEditorAttributeModifier::CopyOptionsImpl,
        RichEditorAttributeModifier::BindSelectionMenuImpl,
        RichEditorAttributeModifier::CustomKeyboardImpl,
        RichEditorAttributeModifier::OnPasteImpl,
        RichEditorAttributeModifier::EnableDataDetectorImpl,
        RichEditorAttributeModifier::EnablePreviewTextImpl,
        RichEditorAttributeModifier::DataDetectorConfigImpl,
        RichEditorAttributeModifier::PlaceholderImpl,
        RichEditorAttributeModifier::CaretColorImpl,
        RichEditorAttributeModifier::SelectedBackgroundColorImpl,
        RichEditorAttributeModifier::OnEditingChangeImpl,
        RichEditorAttributeModifier::EnterKeyTypeImpl,
        RichEditorAttributeModifier::OnSubmitImpl,
        RichEditorAttributeModifier::OnWillChangeImpl,
        RichEditorAttributeModifier::OnDidChangeImpl,
        RichEditorAttributeModifier::OnCutImpl,
        RichEditorAttributeModifier::OnCopyImpl,
        RichEditorAttributeModifier::EditMenuOptionsImpl,
        RichEditorAttributeModifier::EnableKeyboardOnFocusImpl,
        RichEditorAttributeModifier::EnableHapticFeedbackImpl,
        RichEditorAttributeModifier::BarStateImpl,
    };
    return &ArkUIRichEditorModifierImpl;
}

}
