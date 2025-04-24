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
namespace TextAreaModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                Ark_Int32 flags)
{
    return {};
}
} // TextAreaModifier
namespace TextAreaInterfaceModifier {
void SetTextAreaOptionsImpl(Ark_NativePointer node,
                            const Opt_TextAreaOptions* value)
{
}
} // TextAreaInterfaceModifier
namespace TextAreaAttributeModifier {
void PlaceholderColorImpl(Ark_NativePointer node,
                          const Opt_ResourceColor* value)
{
}
void PlaceholderFontImpl(Ark_NativePointer node,
                         const Opt_Font* value)
{
}
void EnterKeyTypeImpl(Ark_NativePointer node,
                      const Opt_EnterKeyType* value)
{
}
void TextAlignImpl(Ark_NativePointer node,
                   const Opt_TextAlign* value)
{
}
void CaretColorImpl(Ark_NativePointer node,
                    const Opt_ResourceColor* value)
{
}
void FontColorImpl(Ark_NativePointer node,
                   const Opt_ResourceColor* value)
{
}
void FontSizeImpl(Ark_NativePointer node,
                  const Opt_Length* value)
{
}
void FontStyleImpl(Ark_NativePointer node,
                   const Opt_FontStyle* value)
{
}
void FontWeightImpl(Ark_NativePointer node,
                    const Opt_Union_Number_FontWeight_String* value)
{
}
void FontFamilyImpl(Ark_NativePointer node,
                    const Opt_ResourceStr* value)
{
}
void TextOverflowImpl(Ark_NativePointer node,
                      const Opt_TextOverflow* value)
{
}
void TextIndentImpl(Ark_NativePointer node,
                    const Opt_Length* value)
{
}
void CaretStyleImpl(Ark_NativePointer node,
                    const Opt_CaretStyle* value)
{
}
void SelectedBackgroundColorImpl(Ark_NativePointer node,
                                 const Opt_ResourceColor* value)
{
}
void OnSubmit0Impl(Ark_NativePointer node,
                   const Opt_Callback_EnterKeyType_Void* value)
{
}
void OnSubmit1Impl(Ark_NativePointer node,
                   const Opt_TextAreaSubmitCallback* value)
{
}
void OnChangeImpl(Ark_NativePointer node,
                  const Opt_EditableTextOnChangeCallback* value)
{
}
void OnTextSelectionChangeImpl(Ark_NativePointer node,
                               const Opt_Callback_Number_Number_Void* value)
{
}
void OnContentScrollImpl(Ark_NativePointer node,
                         const Opt_Callback_Number_Number_Void* value)
{
}
void OnEditChangeImpl(Ark_NativePointer node,
                      const Opt_Callback_Boolean_Void* value)
{
}
void OnCopyImpl(Ark_NativePointer node,
                const Opt_Callback_String_Void* value)
{
}
void OnCutImpl(Ark_NativePointer node,
               const Opt_Callback_String_Void* value)
{
}
void OnPasteImpl(Ark_NativePointer node,
                 const Opt_Callback_String_PasteEvent_Void* value)
{
}
void CopyOptionImpl(Ark_NativePointer node,
                    const Opt_CopyOptions* value)
{
}
void EnableKeyboardOnFocusImpl(Ark_NativePointer node,
                               const Opt_Boolean* value)
{
}
void MaxLengthImpl(Ark_NativePointer node,
                   const Opt_Number* value)
{
}
void StyleImpl(Ark_NativePointer node,
               const Opt_TextContentStyle* value)
{
}
void BarStateImpl(Ark_NativePointer node,
                  const Opt_BarState* value)
{
}
void SelectionMenuHiddenImpl(Ark_NativePointer node,
                             const Opt_Boolean* value)
{
}
void MinFontSizeImpl(Ark_NativePointer node,
                     const Opt_Union_Number_String_Resource* value)
{
}
void MaxFontSizeImpl(Ark_NativePointer node,
                     const Opt_Union_Number_String_Resource* value)
{
}
void MinFontScaleImpl(Ark_NativePointer node,
                      const Opt_Union_Number_Resource* value)
{
}
void MaxFontScaleImpl(Ark_NativePointer node,
                      const Opt_Union_Number_Resource* value)
{
}
void HeightAdaptivePolicyImpl(Ark_NativePointer node,
                              const Opt_TextHeightAdaptivePolicy* value)
{
}
void MaxLinesImpl(Ark_NativePointer node,
                  const Opt_Number* value)
{
}
void WordBreakImpl(Ark_NativePointer node,
                   const Opt_WordBreak* value)
{
}
void LineBreakStrategyImpl(Ark_NativePointer node,
                           const Opt_LineBreakStrategy* value)
{
}
void DecorationImpl(Ark_NativePointer node,
                    const Opt_TextDecorationOptions* value)
{
}
void LetterSpacingImpl(Ark_NativePointer node,
                       const Opt_Union_Number_String_Resource* value)
{
}
void LineSpacingImpl(Ark_NativePointer node,
                     const Opt_LengthMetrics* value)
{
}
void LineHeightImpl(Ark_NativePointer node,
                    const Opt_Union_Number_String_Resource* value)
{
}
void TypeImpl(Ark_NativePointer node,
              const Opt_TextAreaType* value)
{
}
void EnableAutoFillImpl(Ark_NativePointer node,
                        const Opt_Boolean* value)
{
}
void ContentTypeImpl(Ark_NativePointer node,
                     const Opt_ContentType* value)
{
}
void FontFeatureImpl(Ark_NativePointer node,
                     const Opt_String* value)
{
}
void OnWillInsertImpl(Ark_NativePointer node,
                      const Opt_Callback_InsertValue_Boolean* value)
{
}
void OnDidInsertImpl(Ark_NativePointer node,
                     const Opt_Callback_InsertValue_Void* value)
{
}
void OnWillDeleteImpl(Ark_NativePointer node,
                      const Opt_Callback_DeleteValue_Boolean* value)
{
}
void OnDidDeleteImpl(Ark_NativePointer node,
                     const Opt_Callback_DeleteValue_Void* value)
{
}
void EditMenuOptionsImpl(Ark_NativePointer node,
                         const Opt_EditMenuOptions* value)
{
}
void EnablePreviewTextImpl(Ark_NativePointer node,
                           const Opt_Boolean* value)
{
}
void EnableHapticFeedbackImpl(Ark_NativePointer node,
                              const Opt_Boolean* value)
{
}
void AutoCapitalizationModeImpl(Ark_NativePointer node,
                                const Opt_AutoCapitalizationMode* value)
{
}
void HalfLeadingImpl(Ark_NativePointer node,
                     const Opt_Boolean* value)
{
}
void EllipsisModeImpl(Ark_NativePointer node,
                      const Opt_EllipsisMode* value)
{
}
void StopBackPressImpl(Ark_NativePointer node,
                       const Opt_Boolean* value)
{
}
void OnWillChangeImpl(Ark_NativePointer node,
                      const Opt_Callback_EditableTextChangeValue_Boolean* value)
{
}
void KeyboardAppearanceImpl(Ark_NativePointer node,
                            const Opt_KeyboardAppearance* value)
{
}
void InputFilterImpl(Ark_NativePointer node,
                     const Opt_ResourceStr* value,
                     const Opt_Callback_String_Void* error)
{
}
void ShowCounterImpl(Ark_NativePointer node,
                     const Opt_Boolean* value,
                     const Opt_InputCounterOptions* options)
{
}
void CustomKeyboardImpl(Ark_NativePointer node,
                        const Opt_CustomNodeBuilder* value,
                        const Opt_KeyboardOptions* options)
{
}
void _onChangeEvent_textImpl(Ark_NativePointer node,
                             const Callback_ResourceStr_Void* callback)
{
}
} // TextAreaAttributeModifier
const GENERATED_ArkUITextAreaModifier* GetTextAreaModifier()
{
    static const GENERATED_ArkUITextAreaModifier ArkUITextAreaModifierImpl {
        TextAreaModifier::ConstructImpl,
        TextAreaInterfaceModifier::SetTextAreaOptionsImpl,
        TextAreaAttributeModifier::PlaceholderColorImpl,
        TextAreaAttributeModifier::PlaceholderFontImpl,
        TextAreaAttributeModifier::EnterKeyTypeImpl,
        TextAreaAttributeModifier::TextAlignImpl,
        TextAreaAttributeModifier::CaretColorImpl,
        TextAreaAttributeModifier::FontColorImpl,
        TextAreaAttributeModifier::FontSizeImpl,
        TextAreaAttributeModifier::FontStyleImpl,
        TextAreaAttributeModifier::FontWeightImpl,
        TextAreaAttributeModifier::FontFamilyImpl,
        TextAreaAttributeModifier::TextOverflowImpl,
        TextAreaAttributeModifier::TextIndentImpl,
        TextAreaAttributeModifier::CaretStyleImpl,
        TextAreaAttributeModifier::SelectedBackgroundColorImpl,
        TextAreaAttributeModifier::OnSubmit0Impl,
        TextAreaAttributeModifier::OnSubmit1Impl,
        TextAreaAttributeModifier::OnChangeImpl,
        TextAreaAttributeModifier::OnTextSelectionChangeImpl,
        TextAreaAttributeModifier::OnContentScrollImpl,
        TextAreaAttributeModifier::OnEditChangeImpl,
        TextAreaAttributeModifier::OnCopyImpl,
        TextAreaAttributeModifier::OnCutImpl,
        TextAreaAttributeModifier::OnPasteImpl,
        TextAreaAttributeModifier::CopyOptionImpl,
        TextAreaAttributeModifier::EnableKeyboardOnFocusImpl,
        TextAreaAttributeModifier::MaxLengthImpl,
        TextAreaAttributeModifier::StyleImpl,
        TextAreaAttributeModifier::BarStateImpl,
        TextAreaAttributeModifier::SelectionMenuHiddenImpl,
        TextAreaAttributeModifier::MinFontSizeImpl,
        TextAreaAttributeModifier::MaxFontSizeImpl,
        TextAreaAttributeModifier::MinFontScaleImpl,
        TextAreaAttributeModifier::MaxFontScaleImpl,
        TextAreaAttributeModifier::HeightAdaptivePolicyImpl,
        TextAreaAttributeModifier::MaxLinesImpl,
        TextAreaAttributeModifier::WordBreakImpl,
        TextAreaAttributeModifier::LineBreakStrategyImpl,
        TextAreaAttributeModifier::DecorationImpl,
        TextAreaAttributeModifier::LetterSpacingImpl,
        TextAreaAttributeModifier::LineSpacingImpl,
        TextAreaAttributeModifier::LineHeightImpl,
        TextAreaAttributeModifier::TypeImpl,
        TextAreaAttributeModifier::EnableAutoFillImpl,
        TextAreaAttributeModifier::ContentTypeImpl,
        TextAreaAttributeModifier::FontFeatureImpl,
        TextAreaAttributeModifier::OnWillInsertImpl,
        TextAreaAttributeModifier::OnDidInsertImpl,
        TextAreaAttributeModifier::OnWillDeleteImpl,
        TextAreaAttributeModifier::OnDidDeleteImpl,
        TextAreaAttributeModifier::EditMenuOptionsImpl,
        TextAreaAttributeModifier::EnablePreviewTextImpl,
        TextAreaAttributeModifier::EnableHapticFeedbackImpl,
        TextAreaAttributeModifier::AutoCapitalizationModeImpl,
        TextAreaAttributeModifier::HalfLeadingImpl,
        TextAreaAttributeModifier::EllipsisModeImpl,
        TextAreaAttributeModifier::StopBackPressImpl,
        TextAreaAttributeModifier::OnWillChangeImpl,
        TextAreaAttributeModifier::KeyboardAppearanceImpl,
        TextAreaAttributeModifier::InputFilterImpl,
        TextAreaAttributeModifier::ShowCounterImpl,
        TextAreaAttributeModifier::CustomKeyboardImpl,
        TextAreaAttributeModifier::_onChangeEvent_textImpl,
    };
    return &ArkUITextAreaModifierImpl;
}

}
