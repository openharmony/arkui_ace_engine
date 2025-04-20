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
namespace TextInputModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                Ark_Int32 flags)
{
    return {};
}
} // TextInputModifier
namespace TextInputInterfaceModifier {
void SetTextInputOptionsImpl(Ark_NativePointer node,
                             const Opt_TextInputOptions* value)
{
}
} // TextInputInterfaceModifier
namespace TextInputAttributeModifier {
void TypeImpl(Ark_NativePointer node,
              const Opt_InputType* value)
{
}
void ContentTypeImpl(Ark_NativePointer node,
                     const Opt_ContentType* value)
{
}
void PlaceholderColorImpl(Ark_NativePointer node,
                          const Opt_ResourceColor* value)
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
void PlaceholderFontImpl(Ark_NativePointer node,
                         const Opt_Font* value)
{
}
void EnterKeyTypeImpl(Ark_NativePointer node,
                      const Opt_EnterKeyType* value)
{
}
void CaretColorImpl(Ark_NativePointer node,
                    const Opt_ResourceColor* value)
{
}
void OnEditChangedImpl(Ark_NativePointer node,
                       const Opt_Callback_Boolean_Void* value)
{
}
void OnEditChangeImpl(Ark_NativePointer node,
                      const Opt_Callback_Boolean_Void* value)
{
}
void OnSubmitImpl(Ark_NativePointer node,
                  const Opt_OnSubmitCallback* value)
{
}
void OnChangeImpl(Ark_NativePointer node,
                  const Opt_EditableTextOnChangeCallback* value)
{
}
void OnTextSelectionChangeImpl(Ark_NativePointer node,
                               const Opt_OnTextSelectionChangeCallback* value)
{
}
void OnContentScrollImpl(Ark_NativePointer node,
                         const Opt_OnContentScrollCallback* value)
{
}
void MaxLengthImpl(Ark_NativePointer node,
                   const Opt_Number* value)
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
void OnCopyImpl(Ark_NativePointer node,
                const Opt_Callback_String_Void* value)
{
}
void OnCutImpl(Ark_NativePointer node,
               const Opt_Callback_String_Void* value)
{
}
void OnPasteImpl(Ark_NativePointer node,
                 const Opt_OnPasteCallback* value)
{
}
void CopyOptionImpl(Ark_NativePointer node,
                    const Opt_CopyOptions* value)
{
}
void ShowPasswordIconImpl(Ark_NativePointer node,
                          const Opt_Boolean* value)
{
}
void TextAlignImpl(Ark_NativePointer node,
                   const Opt_TextAlign* value)
{
}
void StyleImpl(Ark_NativePointer node,
               const Opt_Union_TextInputStyle_TextContentStyle* value)
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
void CaretPositionImpl(Ark_NativePointer node,
                       const Opt_Number* value)
{
}
void EnableKeyboardOnFocusImpl(Ark_NativePointer node,
                               const Opt_Boolean* value)
{
}
void PasswordIconImpl(Ark_NativePointer node,
                      const Opt_PasswordIcon* value)
{
}
void ShowErrorImpl(Ark_NativePointer node,
                   const Opt_ResourceStr* value)
{
}
void ShowUnitImpl(Ark_NativePointer node,
                  const Opt_CustomNodeBuilder* value)
{
}
void ShowUnderlineImpl(Ark_NativePointer node,
                       const Opt_Boolean* value)
{
}
void UnderlineColorImpl(Ark_NativePointer node,
                        const Opt_Union_ResourceColor_UnderlineColor* value)
{
}
void SelectionMenuHiddenImpl(Ark_NativePointer node,
                             const Opt_Boolean* value)
{
}
void BarStateImpl(Ark_NativePointer node,
                  const Opt_BarState* value)
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
void CancelButton0Impl(Ark_NativePointer node,
                       const Opt_CancelButtonOptions* value)
{
}
void CancelButton1Impl(Ark_NativePointer node,
                       const Opt_CancelButtonSymbolOptions* value)
{
}
void SelectAllImpl(Ark_NativePointer node,
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
void EnableAutoFillImpl(Ark_NativePointer node,
                        const Opt_Boolean* value)
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
void LineHeightImpl(Ark_NativePointer node,
                    const Opt_Union_Number_String_Resource* value)
{
}
void PasswordRulesImpl(Ark_NativePointer node,
                       const Opt_String* value)
{
}
void FontFeatureImpl(Ark_NativePointer node,
                     const Opt_String* value)
{
}
void ShowPasswordImpl(Ark_NativePointer node,
                      const Opt_Boolean* value)
{
}
void OnSecurityStateChangeImpl(Ark_NativePointer node,
                               const Opt_Callback_Boolean_Void* value)
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
void CustomKeyboardImpl(Ark_NativePointer node,
                        const Opt_CustomNodeBuilder* value,
                        const Opt_KeyboardOptions* options)
{
}
void ShowCounterImpl(Ark_NativePointer node,
                     const Opt_Boolean* value,
                     const Opt_InputCounterOptions* options)
{
}
void _onChangeEvent_textImpl(Ark_NativePointer node,
                             const Callback_ResourceStr_Void* callback)
{
}
} // TextInputAttributeModifier
const GENERATED_ArkUITextInputModifier* GetTextInputModifier()
{
    static const GENERATED_ArkUITextInputModifier ArkUITextInputModifierImpl {
        TextInputModifier::ConstructImpl,
        TextInputInterfaceModifier::SetTextInputOptionsImpl,
        TextInputAttributeModifier::TypeImpl,
        TextInputAttributeModifier::ContentTypeImpl,
        TextInputAttributeModifier::PlaceholderColorImpl,
        TextInputAttributeModifier::TextOverflowImpl,
        TextInputAttributeModifier::TextIndentImpl,
        TextInputAttributeModifier::PlaceholderFontImpl,
        TextInputAttributeModifier::EnterKeyTypeImpl,
        TextInputAttributeModifier::CaretColorImpl,
        TextInputAttributeModifier::OnEditChangedImpl,
        TextInputAttributeModifier::OnEditChangeImpl,
        TextInputAttributeModifier::OnSubmitImpl,
        TextInputAttributeModifier::OnChangeImpl,
        TextInputAttributeModifier::OnTextSelectionChangeImpl,
        TextInputAttributeModifier::OnContentScrollImpl,
        TextInputAttributeModifier::MaxLengthImpl,
        TextInputAttributeModifier::FontColorImpl,
        TextInputAttributeModifier::FontSizeImpl,
        TextInputAttributeModifier::FontStyleImpl,
        TextInputAttributeModifier::FontWeightImpl,
        TextInputAttributeModifier::FontFamilyImpl,
        TextInputAttributeModifier::OnCopyImpl,
        TextInputAttributeModifier::OnCutImpl,
        TextInputAttributeModifier::OnPasteImpl,
        TextInputAttributeModifier::CopyOptionImpl,
        TextInputAttributeModifier::ShowPasswordIconImpl,
        TextInputAttributeModifier::TextAlignImpl,
        TextInputAttributeModifier::StyleImpl,
        TextInputAttributeModifier::CaretStyleImpl,
        TextInputAttributeModifier::SelectedBackgroundColorImpl,
        TextInputAttributeModifier::CaretPositionImpl,
        TextInputAttributeModifier::EnableKeyboardOnFocusImpl,
        TextInputAttributeModifier::PasswordIconImpl,
        TextInputAttributeModifier::ShowErrorImpl,
        TextInputAttributeModifier::ShowUnitImpl,
        TextInputAttributeModifier::ShowUnderlineImpl,
        TextInputAttributeModifier::UnderlineColorImpl,
        TextInputAttributeModifier::SelectionMenuHiddenImpl,
        TextInputAttributeModifier::BarStateImpl,
        TextInputAttributeModifier::MaxLinesImpl,
        TextInputAttributeModifier::WordBreakImpl,
        TextInputAttributeModifier::LineBreakStrategyImpl,
        TextInputAttributeModifier::CancelButton0Impl,
        TextInputAttributeModifier::CancelButton1Impl,
        TextInputAttributeModifier::SelectAllImpl,
        TextInputAttributeModifier::MinFontSizeImpl,
        TextInputAttributeModifier::MaxFontSizeImpl,
        TextInputAttributeModifier::MinFontScaleImpl,
        TextInputAttributeModifier::MaxFontScaleImpl,
        TextInputAttributeModifier::HeightAdaptivePolicyImpl,
        TextInputAttributeModifier::EnableAutoFillImpl,
        TextInputAttributeModifier::DecorationImpl,
        TextInputAttributeModifier::LetterSpacingImpl,
        TextInputAttributeModifier::LineHeightImpl,
        TextInputAttributeModifier::PasswordRulesImpl,
        TextInputAttributeModifier::FontFeatureImpl,
        TextInputAttributeModifier::ShowPasswordImpl,
        TextInputAttributeModifier::OnSecurityStateChangeImpl,
        TextInputAttributeModifier::OnWillInsertImpl,
        TextInputAttributeModifier::OnDidInsertImpl,
        TextInputAttributeModifier::OnWillDeleteImpl,
        TextInputAttributeModifier::OnDidDeleteImpl,
        TextInputAttributeModifier::EditMenuOptionsImpl,
        TextInputAttributeModifier::EnablePreviewTextImpl,
        TextInputAttributeModifier::EnableHapticFeedbackImpl,
        TextInputAttributeModifier::AutoCapitalizationModeImpl,
        TextInputAttributeModifier::HalfLeadingImpl,
        TextInputAttributeModifier::EllipsisModeImpl,
        TextInputAttributeModifier::StopBackPressImpl,
        TextInputAttributeModifier::OnWillChangeImpl,
        TextInputAttributeModifier::KeyboardAppearanceImpl,
        TextInputAttributeModifier::InputFilterImpl,
        TextInputAttributeModifier::CustomKeyboardImpl,
        TextInputAttributeModifier::ShowCounterImpl,
        TextInputAttributeModifier::_onChangeEvent_textImpl,
    };
    return &ArkUITextInputModifierImpl;
}

}
