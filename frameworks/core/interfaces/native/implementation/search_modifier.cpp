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
namespace SearchModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                Ark_Int32 flags)
{
    return {};
}
} // SearchModifier
namespace SearchInterfaceModifier {
void SetSearchOptionsImpl(Ark_NativePointer node,
                          const Opt_SearchOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = options ? Converter::OptConvert<type>(*options) : std::nullopt;
    //SearchModelNG::SetSetSearchOptions(frameNode, convValue);
}
} // SearchInterfaceModifier
namespace SearchAttributeModifier {
void SetFontColorImpl(Ark_NativePointer node,
                      const Opt_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //SearchModelNG::SetSetFontColor(frameNode, convValue);
}
void SetSearchIconImpl(Ark_NativePointer node,
                       const Opt_Union_IconOptions_SymbolGlyphModifier* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //SearchModelNG::SetSetSearchIcon(frameNode, convValue);
}
void SetCancelButtonImpl(Ark_NativePointer node,
                         const Opt_Union_CancelButtonOptions_CancelButtonSymbolOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //SearchModelNG::SetSetCancelButton(frameNode, convValue);
}
void SetTextIndentImpl(Ark_NativePointer node,
                       const Opt_Dimension* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //SearchModelNG::SetSetTextIndent(frameNode, convValue);
}
void SetOnEditChangeImpl(Ark_NativePointer node,
                         const Opt_Callback_Boolean_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //SearchModelNG::SetSetOnEditChange(frameNode, convValue);
}
void SetSelectedBackgroundColorImpl(Ark_NativePointer node,
                                    const Opt_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //SearchModelNG::SetSetSelectedBackgroundColor(frameNode, convValue);
}
void SetCaretStyleImpl(Ark_NativePointer node,
                       const Opt_CaretStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //SearchModelNG::SetSetCaretStyle(frameNode, convValue);
}
void SetPlaceholderColorImpl(Ark_NativePointer node,
                             const Opt_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //SearchModelNG::SetSetPlaceholderColor(frameNode, convValue);
}
void SetPlaceholderFontImpl(Ark_NativePointer node,
                            const Opt_Font* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //SearchModelNG::SetSetPlaceholderFont(frameNode, convValue);
}
void SetTextFontImpl(Ark_NativePointer node,
                     const Opt_Font* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //SearchModelNG::SetSetTextFont(frameNode, convValue);
}
void SetEnterKeyTypeImpl(Ark_NativePointer node,
                         const Opt_EnterKeyType* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //SearchModelNG::SetSetEnterKeyType(frameNode, convValue);
}
void SetOnSubmitImpl(Ark_NativePointer node,
                     const Opt_Union_Callback_String_Void_SearchSubmitCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //SearchModelNG::SetSetOnSubmit(frameNode, convValue);
}
void SetOnChangeImpl(Ark_NativePointer node,
                     const Opt_EditableTextOnChangeCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //SearchModelNG::SetSetOnChange(frameNode, convValue);
}
void SetOnTextSelectionChangeImpl(Ark_NativePointer node,
                                  const Opt_OnTextSelectionChangeCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //SearchModelNG::SetSetOnTextSelectionChange(frameNode, convValue);
}
void SetOnContentScrollImpl(Ark_NativePointer node,
                            const Opt_OnContentScrollCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //SearchModelNG::SetSetOnContentScroll(frameNode, convValue);
}
void SetOnCopyImpl(Ark_NativePointer node,
                   const Opt_Callback_String_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //SearchModelNG::SetSetOnCopy(frameNode, convValue);
}
void SetOnCutImpl(Ark_NativePointer node,
                  const Opt_Callback_String_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //SearchModelNG::SetSetOnCut(frameNode, convValue);
}
void SetOnPasteImpl(Ark_NativePointer node,
                    const Opt_OnPasteCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //SearchModelNG::SetSetOnPaste(frameNode, convValue);
}
void SetCopyOptionImpl(Ark_NativePointer node,
                       const Opt_CopyOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //SearchModelNG::SetSetCopyOption(frameNode, convValue);
}
void SetMaxLengthImpl(Ark_NativePointer node,
                      const Opt_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //SearchModelNG::SetSetMaxLength(frameNode, convValue);
}
void SetTextAlignImpl(Ark_NativePointer node,
                      const Opt_TextAlign* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //SearchModelNG::SetSetTextAlign(frameNode, convValue);
}
void SetEnableKeyboardOnFocusImpl(Ark_NativePointer node,
                                  const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //SearchModelNG::SetSetEnableKeyboardOnFocus(frameNode, convValue);
}
void SetSelectionMenuHiddenImpl(Ark_NativePointer node,
                                const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //SearchModelNG::SetSetSelectionMenuHidden(frameNode, convValue);
}
void SetMinFontSizeImpl(Ark_NativePointer node,
                        const Opt_Union_Number_String_Resource* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //SearchModelNG::SetSetMinFontSize(frameNode, convValue);
}
void SetMaxFontSizeImpl(Ark_NativePointer node,
                        const Opt_Union_Number_String_Resource* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //SearchModelNG::SetSetMaxFontSize(frameNode, convValue);
}
void SetMinFontScaleImpl(Ark_NativePointer node,
                         const Opt_Union_Number_Resource* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //SearchModelNG::SetSetMinFontScale(frameNode, convValue);
}
void SetMaxFontScaleImpl(Ark_NativePointer node,
                         const Opt_Union_Number_Resource* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //SearchModelNG::SetSetMaxFontScale(frameNode, convValue);
}
void SetDecorationImpl(Ark_NativePointer node,
                       const Opt_TextDecorationOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //SearchModelNG::SetSetDecoration(frameNode, convValue);
}
void SetLetterSpacingImpl(Ark_NativePointer node,
                          const Opt_Union_Number_String_Resource* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //SearchModelNG::SetSetLetterSpacing(frameNode, convValue);
}
void SetLineHeightImpl(Ark_NativePointer node,
                       const Opt_Union_Number_String_Resource* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //SearchModelNG::SetSetLineHeight(frameNode, convValue);
}
void SetTypeImpl(Ark_NativePointer node,
                 const Opt_SearchType* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //SearchModelNG::SetSetType(frameNode, convValue);
}
void SetFontFeatureImpl(Ark_NativePointer node,
                        const Opt_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //SearchModelNG::SetSetFontFeature(frameNode, convValue);
}
void SetOnWillInsertImpl(Ark_NativePointer node,
                         const Opt_Callback_InsertValue_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //SearchModelNG::SetSetOnWillInsert(frameNode, convValue);
}
void SetOnDidInsertImpl(Ark_NativePointer node,
                        const Opt_Callback_InsertValue_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //SearchModelNG::SetSetOnDidInsert(frameNode, convValue);
}
void SetOnWillDeleteImpl(Ark_NativePointer node,
                         const Opt_Callback_DeleteValue_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //SearchModelNG::SetSetOnWillDelete(frameNode, convValue);
}
void SetOnDidDeleteImpl(Ark_NativePointer node,
                        const Opt_Callback_DeleteValue_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //SearchModelNG::SetSetOnDidDelete(frameNode, convValue);
}
void SetEditMenuOptionsImpl(Ark_NativePointer node,
                            const Opt_EditMenuOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //SearchModelNG::SetSetEditMenuOptions(frameNode, convValue);
}
void SetEnablePreviewTextImpl(Ark_NativePointer node,
                              const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //SearchModelNG::SetSetEnablePreviewText(frameNode, convValue);
}
void SetEnableHapticFeedbackImpl(Ark_NativePointer node,
                                 const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //SearchModelNG::SetSetEnableHapticFeedback(frameNode, convValue);
}
void SetAutoCapitalizationModeImpl(Ark_NativePointer node,
                                   const Opt_AutoCapitalizationMode* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //SearchModelNG::SetSetAutoCapitalizationMode(frameNode, convValue);
}
void SetHalfLeadingImpl(Ark_NativePointer node,
                        const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //SearchModelNG::SetSetHalfLeading(frameNode, convValue);
}
void SetStopBackPressImpl(Ark_NativePointer node,
                          const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //SearchModelNG::SetSetStopBackPress(frameNode, convValue);
}
void SetOnWillChangeImpl(Ark_NativePointer node,
                         const Opt_Callback_EditableTextChangeValue_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //SearchModelNG::SetSetOnWillChange(frameNode, convValue);
}
void SetKeyboardAppearanceImpl(Ark_NativePointer node,
                               const Opt_KeyboardAppearance* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //SearchModelNG::SetSetKeyboardAppearance(frameNode, convValue);
}
void SetSearchButtonImpl(Ark_NativePointer node,
                         const Opt_String* value,
                         const Opt_SearchButtonOptions* option)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(value);
    //auto convValue = Converter::OptConvert<type>(value); // for enums
    //SearchModelNG::SetSetSearchButton(frameNode, convValue);
}
void SetInputFilterImpl(Ark_NativePointer node,
                        const Opt_ResourceStr* value,
                        const Opt_Callback_String_Void* error)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(value);
    //auto convValue = Converter::OptConvert<type>(value); // for enums
    //SearchModelNG::SetSetInputFilter(frameNode, convValue);
}
void SetCustomKeyboardImpl(Ark_NativePointer node,
                           const Opt_CustomNodeBuilder* value,
                           const Opt_KeyboardOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(value);
    //auto convValue = Converter::OptConvert<type>(value); // for enums
    //SearchModelNG::SetSetCustomKeyboard(frameNode, convValue);
}
} // SearchAttributeModifier
const GENERATED_ArkUISearchModifier* GetSearchModifier()
{
    static const GENERATED_ArkUISearchModifier ArkUISearchModifierImpl {
        SearchModifier::ConstructImpl,
        SearchInterfaceModifier::SetSearchOptionsImpl,
        SearchAttributeModifier::SetFontColorImpl,
        SearchAttributeModifier::SetSearchIconImpl,
        SearchAttributeModifier::SetCancelButtonImpl,
        SearchAttributeModifier::SetTextIndentImpl,
        SearchAttributeModifier::SetOnEditChangeImpl,
        SearchAttributeModifier::SetSelectedBackgroundColorImpl,
        SearchAttributeModifier::SetCaretStyleImpl,
        SearchAttributeModifier::SetPlaceholderColorImpl,
        SearchAttributeModifier::SetPlaceholderFontImpl,
        SearchAttributeModifier::SetTextFontImpl,
        SearchAttributeModifier::SetEnterKeyTypeImpl,
        SearchAttributeModifier::SetOnSubmitImpl,
        SearchAttributeModifier::SetOnChangeImpl,
        SearchAttributeModifier::SetOnTextSelectionChangeImpl,
        SearchAttributeModifier::SetOnContentScrollImpl,
        SearchAttributeModifier::SetOnCopyImpl,
        SearchAttributeModifier::SetOnCutImpl,
        SearchAttributeModifier::SetOnPasteImpl,
        SearchAttributeModifier::SetCopyOptionImpl,
        SearchAttributeModifier::SetMaxLengthImpl,
        SearchAttributeModifier::SetTextAlignImpl,
        SearchAttributeModifier::SetEnableKeyboardOnFocusImpl,
        SearchAttributeModifier::SetSelectionMenuHiddenImpl,
        SearchAttributeModifier::SetMinFontSizeImpl,
        SearchAttributeModifier::SetMaxFontSizeImpl,
        SearchAttributeModifier::SetMinFontScaleImpl,
        SearchAttributeModifier::SetMaxFontScaleImpl,
        SearchAttributeModifier::SetDecorationImpl,
        SearchAttributeModifier::SetLetterSpacingImpl,
        SearchAttributeModifier::SetLineHeightImpl,
        SearchAttributeModifier::SetTypeImpl,
        SearchAttributeModifier::SetFontFeatureImpl,
        SearchAttributeModifier::SetOnWillInsertImpl,
        SearchAttributeModifier::SetOnDidInsertImpl,
        SearchAttributeModifier::SetOnWillDeleteImpl,
        SearchAttributeModifier::SetOnDidDeleteImpl,
        SearchAttributeModifier::SetEditMenuOptionsImpl,
        SearchAttributeModifier::SetEnablePreviewTextImpl,
        SearchAttributeModifier::SetEnableHapticFeedbackImpl,
        SearchAttributeModifier::SetAutoCapitalizationModeImpl,
        SearchAttributeModifier::SetHalfLeadingImpl,
        SearchAttributeModifier::SetStopBackPressImpl,
        SearchAttributeModifier::SetOnWillChangeImpl,
        SearchAttributeModifier::SetKeyboardAppearanceImpl,
        SearchAttributeModifier::SetSearchButtonImpl,
        SearchAttributeModifier::SetInputFilterImpl,
        SearchAttributeModifier::SetCustomKeyboardImpl,
    };
    return &ArkUISearchModifierImpl;
}

}
