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
namespace SearchInterfaceModifier {
void SetSearchOptionsImpl(Ark_NativePointer node,
                          const Opt_Type_SearchInterface_setSearchOptions_Arg0* options)
{
}
} // SearchInterfaceModifier
namespace SearchAttributeModifier {
void SearchButtonImpl(Ark_NativePointer node,
                      const Ark_String* value,
                      const Opt_SearchButtonOptions* option)
{
}
void FontColorImpl(Ark_NativePointer node,
                   const ResourceColor* value)
{
}
void SearchIconImpl(Ark_NativePointer node,
                    const Type_SearchAttribute_searchIcon_Arg0* value)
{
}
void CancelButtonImpl(Ark_NativePointer node,
                      const Type_SearchAttribute_cancelButton_Arg0* value)
{
}
void TextIndentImpl(Ark_NativePointer node,
                    const Ark_Length* value)
{
}
void InputFilterImpl(Ark_NativePointer node,
                     const ResourceStr* value,
                     const Opt_Callback* error)
{
}
void OnEditChangeImpl(Ark_NativePointer node,
                      Ark_Function callback)
{
}
void SelectedBackgroundColorImpl(Ark_NativePointer node,
                                 const ResourceColor* value)
{
}
void CaretStyleImpl(Ark_NativePointer node,
                    const Ark_CaretStyle* value)
{
}
void PlaceholderColorImpl(Ark_NativePointer node,
                          const ResourceColor* value)
{
}
void PlaceholderFontImpl(Ark_NativePointer node,
                         const Opt_Font* value)
{
}
void TextFontImpl(Ark_NativePointer node,
                  const Opt_Font* value)
{
}
void EnterKeyTypeImpl(Ark_NativePointer node,
                      enum Ark_EnterKeyType value)
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
void MaxLengthImpl(Ark_NativePointer node,
                   const Ark_Number* value)
{
}
void TextAlignImpl(Ark_NativePointer node,
                   enum Ark_TextAlign value)
{
}
void EnableKeyboardOnFocusImpl(Ark_NativePointer node,
                               Ark_Boolean value)
{
}
void SelectionMenuHiddenImpl(Ark_NativePointer node,
                             Ark_Boolean value)
{
}
void MinFontSizeImpl(Ark_NativePointer node,
                     const Type_SearchAttribute_minFontSize_Arg0* value)
{
}
void MaxFontSizeImpl(Ark_NativePointer node,
                     const Type_SearchAttribute_maxFontSize_Arg0* value)
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
                       const Type_SearchAttribute_letterSpacing_Arg0* value)
{
}
void LineHeightImpl(Ark_NativePointer node,
                    const Type_SearchAttribute_lineHeight_Arg0* value)
{
}
void TypeImpl(Ark_NativePointer node,
              enum Ark_SearchType value)
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
} // SearchAttributeModifier
const GENERATED_ArkUISearchModifier* GetSearchModifier()
{
    static const GENERATED_ArkUISearchModifier ArkUISearchModifierImpl {
        SearchInterfaceModifier::SetSearchOptionsImpl,
        SearchAttributeModifier::SearchButtonImpl,
        SearchAttributeModifier::FontColorImpl,
        SearchAttributeModifier::SearchIconImpl,
        SearchAttributeModifier::CancelButtonImpl,
        SearchAttributeModifier::TextIndentImpl,
        SearchAttributeModifier::InputFilterImpl,
        SearchAttributeModifier::OnEditChangeImpl,
        SearchAttributeModifier::SelectedBackgroundColorImpl,
        SearchAttributeModifier::CaretStyleImpl,
        SearchAttributeModifier::PlaceholderColorImpl,
        SearchAttributeModifier::PlaceholderFontImpl,
        SearchAttributeModifier::TextFontImpl,
        SearchAttributeModifier::EnterKeyTypeImpl,
        SearchAttributeModifier::OnSubmitImpl,
        SearchAttributeModifier::OnChangeImpl,
        SearchAttributeModifier::OnTextSelectionChangeImpl,
        SearchAttributeModifier::OnContentScrollImpl,
        SearchAttributeModifier::OnCopyImpl,
        SearchAttributeModifier::OnCutImpl,
        SearchAttributeModifier::OnPasteImpl,
        SearchAttributeModifier::CopyOptionImpl,
        SearchAttributeModifier::MaxLengthImpl,
        SearchAttributeModifier::TextAlignImpl,
        SearchAttributeModifier::EnableKeyboardOnFocusImpl,
        SearchAttributeModifier::SelectionMenuHiddenImpl,
        SearchAttributeModifier::MinFontSizeImpl,
        SearchAttributeModifier::MaxFontSizeImpl,
        SearchAttributeModifier::CustomKeyboardImpl,
        SearchAttributeModifier::DecorationImpl,
        SearchAttributeModifier::LetterSpacingImpl,
        SearchAttributeModifier::LineHeightImpl,
        SearchAttributeModifier::TypeImpl,
        SearchAttributeModifier::FontFeatureImpl,
        SearchAttributeModifier::OnWillInsertImpl,
        SearchAttributeModifier::OnDidInsertImpl,
        SearchAttributeModifier::OnWillDeleteImpl,
        SearchAttributeModifier::OnDidDeleteImpl,
        SearchAttributeModifier::EditMenuOptionsImpl,
        SearchAttributeModifier::EnablePreviewTextImpl,
    };
    return &ArkUISearchModifierImpl;
}

}
