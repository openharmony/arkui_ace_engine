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
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //RichEditorModelNG::SetSetRichEditorOptions0(frameNode, convValue);
}
void SetRichEditorOptions1Impl(Ark_NativePointer node,
                               const Ark_RichEditorStyledStringOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(options);
    //auto convValue = Converter::OptConvert<type_name>(*options);
    //RichEditorModelNG::SetSetRichEditorOptions1(frameNode, convValue);
}
} // RichEditorInterfaceModifier
namespace RichEditorAttributeModifier {
void SetOnReadyImpl(Ark_NativePointer node,
                    const Opt_VoidCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //RichEditorModelNG::SetSetOnReady(frameNode, convValue);
}
void SetOnSelectImpl(Ark_NativePointer node,
                     const Opt_Callback_RichEditorSelection_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //RichEditorModelNG::SetSetOnSelect(frameNode, convValue);
}
void SetOnSelectionChangeImpl(Ark_NativePointer node,
                              const Opt_Callback_RichEditorRange_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //RichEditorModelNG::SetSetOnSelectionChange(frameNode, convValue);
}
void SetAboutToIMEInputImpl(Ark_NativePointer node,
                            const Opt_Callback_RichEditorInsertValue_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //RichEditorModelNG::SetSetAboutToIMEInput(frameNode, convValue);
}
void SetOnIMEInputCompleteImpl(Ark_NativePointer node,
                               const Opt_Callback_RichEditorTextSpanResult_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //RichEditorModelNG::SetSetOnIMEInputComplete(frameNode, convValue);
}
void SetOnDidIMEInputImpl(Ark_NativePointer node,
                          const Opt_Callback_TextRange_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //RichEditorModelNG::SetSetOnDidIMEInput(frameNode, convValue);
}
void SetAboutToDeleteImpl(Ark_NativePointer node,
                          const Opt_Callback_RichEditorDeleteValue_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //RichEditorModelNG::SetSetAboutToDelete(frameNode, convValue);
}
void SetOnDeleteCompleteImpl(Ark_NativePointer node,
                             const Opt_VoidCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //RichEditorModelNG::SetSetOnDeleteComplete(frameNode, convValue);
}
void SetCopyOptionsImpl(Ark_NativePointer node,
                        const Opt_CopyOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //RichEditorModelNG::SetSetCopyOptions(frameNode, convValue);
}
void SetOnPasteImpl(Ark_NativePointer node,
                    const Opt_PasteEventCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //RichEditorModelNG::SetSetOnPaste(frameNode, convValue);
}
void SetEnableDataDetectorImpl(Ark_NativePointer node,
                               const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //RichEditorModelNG::SetSetEnableDataDetector(frameNode, convValue);
}
void SetEnablePreviewTextImpl(Ark_NativePointer node,
                              const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //RichEditorModelNG::SetSetEnablePreviewText(frameNode, convValue);
}
void SetDataDetectorConfigImpl(Ark_NativePointer node,
                               const Opt_TextDataDetectorConfig* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //RichEditorModelNG::SetSetDataDetectorConfig(frameNode, convValue);
}
void SetCaretColorImpl(Ark_NativePointer node,
                       const Opt_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //RichEditorModelNG::SetSetCaretColor(frameNode, convValue);
}
void SetSelectedBackgroundColorImpl(Ark_NativePointer node,
                                    const Opt_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //RichEditorModelNG::SetSetSelectedBackgroundColor(frameNode, convValue);
}
void SetOnEditingChangeImpl(Ark_NativePointer node,
                            const Opt_Callback_Boolean_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //RichEditorModelNG::SetSetOnEditingChange(frameNode, convValue);
}
void SetEnterKeyTypeImpl(Ark_NativePointer node,
                         const Opt_EnterKeyType* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //RichEditorModelNG::SetSetEnterKeyType(frameNode, convValue);
}
void SetOnSubmitImpl(Ark_NativePointer node,
                     const Opt_SubmitCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //RichEditorModelNG::SetSetOnSubmit(frameNode, convValue);
}
void SetOnWillChangeImpl(Ark_NativePointer node,
                         const Opt_Callback_RichEditorChangeValue_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //RichEditorModelNG::SetSetOnWillChange(frameNode, convValue);
}
void SetOnDidChangeImpl(Ark_NativePointer node,
                        const Opt_OnDidChangeCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //RichEditorModelNG::SetSetOnDidChange(frameNode, convValue);
}
void SetOnCutImpl(Ark_NativePointer node,
                  const Opt_Callback_CutEvent_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //RichEditorModelNG::SetSetOnCut(frameNode, convValue);
}
void SetOnCopyImpl(Ark_NativePointer node,
                   const Opt_Callback_CopyEvent_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //RichEditorModelNG::SetSetOnCopy(frameNode, convValue);
}
void SetEditMenuOptionsImpl(Ark_NativePointer node,
                            const Opt_EditMenuOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //RichEditorModelNG::SetSetEditMenuOptions(frameNode, convValue);
}
void SetEnableKeyboardOnFocusImpl(Ark_NativePointer node,
                                  const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //RichEditorModelNG::SetSetEnableKeyboardOnFocus(frameNode, convValue);
}
void SetEnableHapticFeedbackImpl(Ark_NativePointer node,
                                 const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //RichEditorModelNG::SetSetEnableHapticFeedback(frameNode, convValue);
}
void SetBarStateImpl(Ark_NativePointer node,
                     const Opt_BarState* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //RichEditorModelNG::SetSetBarState(frameNode, convValue);
}
void SetMaxLengthImpl(Ark_NativePointer node,
                      const Opt_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //RichEditorModelNG::SetSetMaxLength(frameNode, convValue);
}
void SetMaxLinesImpl(Ark_NativePointer node,
                     const Opt_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //RichEditorModelNG::SetSetMaxLines(frameNode, convValue);
}
void SetKeyboardAppearanceImpl(Ark_NativePointer node,
                               const Opt_KeyboardAppearance* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //RichEditorModelNG::SetSetKeyboardAppearance(frameNode, convValue);
}
void SetStopBackPressImpl(Ark_NativePointer node,
                          const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //RichEditorModelNG::SetSetStopBackPress(frameNode, convValue);
}
void SetBindSelectionMenuImpl(Ark_NativePointer node,
                              const Opt_RichEditorSpanType* spanType,
                              const Opt_CustomNodeBuilder* content,
                              const Opt_Union_ResponseType_RichEditorResponseType* responseType,
                              const Opt_SelectionMenuOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(spanType);
    //auto convValue = Converter::OptConvert<type>(spanType); // for enums
    //RichEditorModelNG::SetSetBindSelectionMenu(frameNode, convValue);
}
void SetCustomKeyboardImpl(Ark_NativePointer node,
                           const Opt_CustomNodeBuilder* value,
                           const Opt_KeyboardOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(value);
    //auto convValue = Converter::OptConvert<type>(value); // for enums
    //RichEditorModelNG::SetSetCustomKeyboard(frameNode, convValue);
}
void SetPlaceholderImpl(Ark_NativePointer node,
                        const Opt_ResourceStr* value,
                        const Opt_PlaceholderStyle* style)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(value);
    //auto convValue = Converter::OptConvert<type>(value); // for enums
    //RichEditorModelNG::SetSetPlaceholder(frameNode, convValue);
}
} // RichEditorAttributeModifier
const GENERATED_ArkUIRichEditorModifier* GetRichEditorModifier()
{
    static const GENERATED_ArkUIRichEditorModifier ArkUIRichEditorModifierImpl {
        RichEditorModifier::ConstructImpl,
        RichEditorInterfaceModifier::SetRichEditorOptions0Impl,
        RichEditorInterfaceModifier::SetRichEditorOptions1Impl,
        RichEditorAttributeModifier::SetOnReadyImpl,
        RichEditorAttributeModifier::SetOnSelectImpl,
        RichEditorAttributeModifier::SetOnSelectionChangeImpl,
        RichEditorAttributeModifier::SetAboutToIMEInputImpl,
        RichEditorAttributeModifier::SetOnIMEInputCompleteImpl,
        RichEditorAttributeModifier::SetOnDidIMEInputImpl,
        RichEditorAttributeModifier::SetAboutToDeleteImpl,
        RichEditorAttributeModifier::SetOnDeleteCompleteImpl,
        RichEditorAttributeModifier::SetCopyOptionsImpl,
        RichEditorAttributeModifier::SetOnPasteImpl,
        RichEditorAttributeModifier::SetEnableDataDetectorImpl,
        RichEditorAttributeModifier::SetEnablePreviewTextImpl,
        RichEditorAttributeModifier::SetDataDetectorConfigImpl,
        RichEditorAttributeModifier::SetCaretColorImpl,
        RichEditorAttributeModifier::SetSelectedBackgroundColorImpl,
        RichEditorAttributeModifier::SetOnEditingChangeImpl,
        RichEditorAttributeModifier::SetEnterKeyTypeImpl,
        RichEditorAttributeModifier::SetOnSubmitImpl,
        RichEditorAttributeModifier::SetOnWillChangeImpl,
        RichEditorAttributeModifier::SetOnDidChangeImpl,
        RichEditorAttributeModifier::SetOnCutImpl,
        RichEditorAttributeModifier::SetOnCopyImpl,
        RichEditorAttributeModifier::SetEditMenuOptionsImpl,
        RichEditorAttributeModifier::SetEnableKeyboardOnFocusImpl,
        RichEditorAttributeModifier::SetEnableHapticFeedbackImpl,
        RichEditorAttributeModifier::SetBarStateImpl,
        RichEditorAttributeModifier::SetMaxLengthImpl,
        RichEditorAttributeModifier::SetMaxLinesImpl,
        RichEditorAttributeModifier::SetKeyboardAppearanceImpl,
        RichEditorAttributeModifier::SetStopBackPressImpl,
        RichEditorAttributeModifier::SetBindSelectionMenuImpl,
        RichEditorAttributeModifier::SetCustomKeyboardImpl,
        RichEditorAttributeModifier::SetPlaceholderImpl,
    };
    return &ArkUIRichEditorModifierImpl;
}

}
