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
namespace RichEditorModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                Ark_Int32 flags)
{
    return {};
}
} // RichEditorModifier
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
                 const Opt_Callback_Void* value)
{
}
void OnSelectImpl(Ark_NativePointer node,
                  const Opt_Callback_RichEditorSelection_Void* value)
{
}
void OnSelectionChangeImpl(Ark_NativePointer node,
                           const Opt_Callback_RichEditorRange_Void* value)
{
}
void AboutToIMEInputImpl(Ark_NativePointer node,
                         const Opt_Callback_RichEditorInsertValue_Boolean* value)
{
}
void OnIMEInputCompleteImpl(Ark_NativePointer node,
                            const Opt_Callback_RichEditorTextSpanResult_Void* value)
{
}
void OnDidIMEInputImpl(Ark_NativePointer node,
                       const Opt_Callback_TextRange_Void* value)
{
}
void AboutToDeleteImpl(Ark_NativePointer node,
                       const Opt_Callback_RichEditorDeleteValue_Boolean* value)
{
}
void OnDeleteCompleteImpl(Ark_NativePointer node,
                          const Opt_Callback_Void* value)
{
}
void CopyOptionsImpl(Ark_NativePointer node,
                     const Opt_CopyOptions* value)
{
}
void OnPasteImpl(Ark_NativePointer node,
                 const Opt_PasteEventCallback* value)
{
}
void EnableDataDetectorImpl(Ark_NativePointer node,
                            const Opt_Boolean* value)
{
}
void EnablePreviewTextImpl(Ark_NativePointer node,
                           const Opt_Boolean* value)
{
}
void DataDetectorConfigImpl(Ark_NativePointer node,
                            const Opt_TextDataDetectorConfig* value)
{
}
void CaretColorImpl(Ark_NativePointer node,
                    const Opt_ResourceColor* value)
{
}
void SelectedBackgroundColorImpl(Ark_NativePointer node,
                                 const Opt_ResourceColor* value)
{
}
void OnEditingChangeImpl(Ark_NativePointer node,
                         const Opt_Callback_Boolean_Void* value)
{
}
void EnterKeyTypeImpl(Ark_NativePointer node,
                      const Opt_EnterKeyType* value)
{
}
void OnSubmitImpl(Ark_NativePointer node,
                  const Opt_SubmitCallback* value)
{
}
void OnWillChangeImpl(Ark_NativePointer node,
                      const Opt_Callback_RichEditorChangeValue_Boolean* value)
{
}
void OnDidChangeImpl(Ark_NativePointer node,
                     const Opt_OnDidChangeCallback* value)
{
}
void OnCutImpl(Ark_NativePointer node,
               const Opt_Callback_CutEvent_Void* value)
{
}
void OnCopyImpl(Ark_NativePointer node,
                const Opt_Callback_CopyEvent_Void* value)
{
}
void EditMenuOptionsImpl(Ark_NativePointer node,
                         const Opt_EditMenuOptions* value)
{
}
void EnableKeyboardOnFocusImpl(Ark_NativePointer node,
                               const Opt_Boolean* value)
{
}
void EnableHapticFeedbackImpl(Ark_NativePointer node,
                              const Opt_Boolean* value)
{
}
void BarStateImpl(Ark_NativePointer node,
                  const Opt_BarState* value)
{
}
void MaxLengthImpl(Ark_NativePointer node,
                   const Opt_Number* value)
{
}
void MaxLinesImpl(Ark_NativePointer node,
                  const Opt_Number* value)
{
}
void KeyboardAppearanceImpl(Ark_NativePointer node,
                            const Opt_KeyboardAppearance* value)
{
}
void StopBackPressImpl(Ark_NativePointer node,
                       const Opt_Boolean* value)
{
}
void BindSelectionMenuImpl(Ark_NativePointer node,
                           const Opt_RichEditorSpanType* spanType,
                           const Opt_CustomNodeBuilder* content,
                           const Opt_Union_ResponseType_RichEditorResponseType* responseType,
                           const Opt_SelectionMenuOptions* options)
{
}
void CustomKeyboardImpl(Ark_NativePointer node,
                        const Opt_CustomNodeBuilder* value,
                        const Opt_KeyboardOptions* options)
{
}
void PlaceholderImpl(Ark_NativePointer node,
                     const Opt_ResourceStr* value,
                     const Opt_PlaceholderStyle* style)
{
}
} // RichEditorAttributeModifier
const GENERATED_ArkUIRichEditorModifier* GetRichEditorModifier()
{
    static const GENERATED_ArkUIRichEditorModifier ArkUIRichEditorModifierImpl {
        RichEditorModifier::ConstructImpl,
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
        RichEditorAttributeModifier::OnPasteImpl,
        RichEditorAttributeModifier::EnableDataDetectorImpl,
        RichEditorAttributeModifier::EnablePreviewTextImpl,
        RichEditorAttributeModifier::DataDetectorConfigImpl,
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
        RichEditorAttributeModifier::MaxLengthImpl,
        RichEditorAttributeModifier::MaxLinesImpl,
        RichEditorAttributeModifier::KeyboardAppearanceImpl,
        RichEditorAttributeModifier::StopBackPressImpl,
        RichEditorAttributeModifier::BindSelectionMenuImpl,
        RichEditorAttributeModifier::CustomKeyboardImpl,
        RichEditorAttributeModifier::PlaceholderImpl,
    };
    return &ArkUIRichEditorModifierImpl;
}

}
