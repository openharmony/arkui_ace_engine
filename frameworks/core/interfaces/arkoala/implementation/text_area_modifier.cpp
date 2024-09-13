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
namespace TextAreaInterfaceModifier {
void SetTextAreaOptionsImpl(Ark_NativePointer node,
                            const Opt_TextAreaOptions* value)
{
}
} // TextAreaInterfaceModifier
namespace TextAreaAttributeModifier {
void PlaceholderColorImpl(Ark_NativePointer node,
                          const ResourceColor* value)
{
}
void PlaceholderFontImpl(Ark_NativePointer node,
                         const Ark_Font* value)
{
}
void EnterKeyTypeImpl(Ark_NativePointer node,
                      enum Ark_EnterKeyType value)
{
}
void TextAlignImpl(Ark_NativePointer node,
                   enum Ark_TextAlign value)
{
}
void CaretColorImpl(Ark_NativePointer node,
                    const ResourceColor* value)
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
void FontStyleImpl(Ark_NativePointer node,
                   enum Ark_FontStyle value)
{
}
void FontWeightImpl(Ark_NativePointer node,
                    const Type_TextAreaAttribute_fontWeight_Arg0* value)
{
}
void FontFamilyImpl(Ark_NativePointer node,
                    const ResourceStr* value)
{
}
void TextOverflowImpl(Ark_NativePointer node,
                      enum Ark_TextOverflow value)
{
}
void TextIndentImpl(Ark_NativePointer node,
                    const Ark_Length* value)
{
}
void InputFilterImpl(Ark_NativePointer node,
                     const ResourceStr* value,
                     const Opt_Function* error)
{
}
void CaretStyleImpl(Ark_NativePointer node,
                    const Ark_CaretStyle* value)
{
}
void SelectedBackgroundColorImpl(Ark_NativePointer node,
                                 const ResourceColor* value)
{
}
void OnSubmitImpl(Ark_NativePointer node,
                  Ark_Function callback)
{
}
void OnChangeImpl(Ark_NativePointer node,
                  Ark_Function callback)
{
}
void OnTextSelectionChangeImpl(Ark_NativePointer node,
                               Ark_Function callback)
{
}
void OnContentScrollImpl(Ark_NativePointer node,
                         Ark_Function callback)
{
}
void OnEditChangeImpl(Ark_NativePointer node,
                      Ark_Function callback)
{
}
void OnCopyImpl(Ark_NativePointer node,
                Ark_Function callback)
{
}
void OnCutImpl(Ark_NativePointer node,
               Ark_Function callback)
{
}
void OnPasteImpl(Ark_NativePointer node,
                 Ark_Function callback)
{
}
void CopyOptionImpl(Ark_NativePointer node,
                    enum Ark_CopyOptions value)
{
}
void EnableKeyboardOnFocusImpl(Ark_NativePointer node,
                               Ark_Boolean value)
{
}
void MaxLengthImpl(Ark_NativePointer node,
                   const Ark_Number* value)
{
}
void ShowCounterImpl(Ark_NativePointer node,
                     Ark_Boolean value,
                     const Opt_InputCounterOptions* options)
{
}
void StyleImpl(Ark_NativePointer node,
               enum Ark_TextContentStyle value)
{
}
void BarStateImpl(Ark_NativePointer node,
                  enum Ark_BarState value)
{
}
void SelectionMenuHiddenImpl(Ark_NativePointer node,
                             Ark_Boolean value)
{
}
void MinFontSizeImpl(Ark_NativePointer node,
                     const Type_TextAreaAttribute_minFontSize_Arg0* value)
{
}
void MaxFontSizeImpl(Ark_NativePointer node,
                     const Type_TextAreaAttribute_maxFontSize_Arg0* value)
{
}
void HeightAdaptivePolicyImpl(Ark_NativePointer node,
                              enum Ark_TextHeightAdaptivePolicy value)
{
}
void MaxLinesImpl(Ark_NativePointer node,
                  const Ark_Number* value)
{
}
void WordBreakImpl(Ark_NativePointer node,
                   enum Ark_WordBreak value)
{
}
void LineBreakStrategyImpl(Ark_NativePointer node,
                           enum Ark_LineBreakStrategy strategy)
{
}
void CustomKeyboardImpl(Ark_NativePointer node,
                        const CustomBuilder* value,
                        const Opt_KeyboardOptions* options)
{
}
void DecorationImpl(Ark_NativePointer node,
                    const Ark_TextDecorationOptions* value)
{
}
void LetterSpacingImpl(Ark_NativePointer node,
                       const Type_TextAreaAttribute_letterSpacing_Arg0* value)
{
}
void LineSpacingImpl(Ark_NativePointer node,
                     const Ark_CustomObject* value)
{
}
void LineHeightImpl(Ark_NativePointer node,
                    const Type_TextAreaAttribute_lineHeight_Arg0* value)
{
}
void TypeImpl(Ark_NativePointer node,
              enum Ark_TextAreaType value)
{
}
void EnableAutoFillImpl(Ark_NativePointer node,
                        Ark_Boolean value)
{
}
void ContentTypeImpl(Ark_NativePointer node,
                     enum Ark_ContentType contentType)
{
}
void FontFeatureImpl(Ark_NativePointer node,
                     const Ark_String* value)
{
}
void OnWillInsertImpl(Ark_NativePointer node,
                      Ark_Function callback)
{
}
void OnDidInsertImpl(Ark_NativePointer node,
                     Ark_Function callback)
{
}
void OnWillDeleteImpl(Ark_NativePointer node,
                      Ark_Function callback)
{
}
void OnDidDeleteImpl(Ark_NativePointer node,
                     Ark_Function callback)
{
}
void EditMenuOptionsImpl(Ark_NativePointer node,
                         const Ark_Materialized* editMenu)
{
}
void EnablePreviewTextImpl(Ark_NativePointer node,
                           Ark_Boolean enable)
{
}
} // TextAreaAttributeModifier
const GENERATED_ArkUITextAreaModifier* GetTextAreaModifier()
{
    static const GENERATED_ArkUITextAreaModifier ArkUITextAreaModifierImpl {
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
        TextAreaAttributeModifier::InputFilterImpl,
        TextAreaAttributeModifier::CaretStyleImpl,
        TextAreaAttributeModifier::SelectedBackgroundColorImpl,
        TextAreaAttributeModifier::OnSubmitImpl,
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
        TextAreaAttributeModifier::ShowCounterImpl,
        TextAreaAttributeModifier::StyleImpl,
        TextAreaAttributeModifier::BarStateImpl,
        TextAreaAttributeModifier::SelectionMenuHiddenImpl,
        TextAreaAttributeModifier::MinFontSizeImpl,
        TextAreaAttributeModifier::MaxFontSizeImpl,
        TextAreaAttributeModifier::HeightAdaptivePolicyImpl,
        TextAreaAttributeModifier::MaxLinesImpl,
        TextAreaAttributeModifier::WordBreakImpl,
        TextAreaAttributeModifier::LineBreakStrategyImpl,
        TextAreaAttributeModifier::CustomKeyboardImpl,
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
    };
    return &ArkUITextAreaModifierImpl;
}

}
