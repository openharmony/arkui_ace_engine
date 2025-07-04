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
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //TextAreaModelNG::SetSetTextAreaOptions(frameNode, convValue);
}
} // TextAreaInterfaceModifier
namespace TextAreaAttributeModifier {
void SetPlaceholderColorImpl(Ark_NativePointer node,
                             const Opt_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //TextAreaModelNG::SetSetPlaceholderColor(frameNode, convValue);
}
void SetPlaceholderFontImpl(Ark_NativePointer node,
                            const Opt_Font* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //TextAreaModelNG::SetSetPlaceholderFont(frameNode, convValue);
}
void SetEnterKeyTypeImpl(Ark_NativePointer node,
                         const Opt_EnterKeyType* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //TextAreaModelNG::SetSetEnterKeyType(frameNode, convValue);
}
void SetTextAlignImpl(Ark_NativePointer node,
                      const Opt_TextAlign* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //TextAreaModelNG::SetSetTextAlign(frameNode, convValue);
}
void SetCaretColorImpl(Ark_NativePointer node,
                       const Opt_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //TextAreaModelNG::SetSetCaretColor(frameNode, convValue);
}
void SetFontColorImpl(Ark_NativePointer node,
                      const Opt_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //TextAreaModelNG::SetSetFontColor(frameNode, convValue);
}
void SetFontSizeImpl(Ark_NativePointer node,
                     const Opt_Length* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //TextAreaModelNG::SetSetFontSize(frameNode, convValue);
}
void SetFontStyleImpl(Ark_NativePointer node,
                      const Opt_FontStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //TextAreaModelNG::SetSetFontStyle(frameNode, convValue);
}
void SetFontWeightImpl(Ark_NativePointer node,
                       const Opt_Union_Number_FontWeight_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //TextAreaModelNG::SetSetFontWeight(frameNode, convValue);
}
void SetFontFamilyImpl(Ark_NativePointer node,
                       const Opt_ResourceStr* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //TextAreaModelNG::SetSetFontFamily(frameNode, convValue);
}
void SetTextOverflowImpl(Ark_NativePointer node,
                         const Opt_TextOverflow* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //TextAreaModelNG::SetSetTextOverflow(frameNode, convValue);
}
void SetTextIndentImpl(Ark_NativePointer node,
                       const Opt_Dimension* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //TextAreaModelNG::SetSetTextIndent(frameNode, convValue);
}
void SetCaretStyleImpl(Ark_NativePointer node,
                       const Opt_CaretStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //TextAreaModelNG::SetSetCaretStyle(frameNode, convValue);
}
void SetSelectedBackgroundColorImpl(Ark_NativePointer node,
                                    const Opt_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //TextAreaModelNG::SetSetSelectedBackgroundColor(frameNode, convValue);
}
void SetOnSubmitImpl(Ark_NativePointer node,
                     const Opt_Union_Callback_EnterKeyType_Void_TextAreaSubmitCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //TextAreaModelNG::SetSetOnSubmit(frameNode, convValue);
}
void SetOnChangeImpl(Ark_NativePointer node,
                     const Opt_EditableTextOnChangeCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //TextAreaModelNG::SetSetOnChange(frameNode, convValue);
}
void SetOnTextSelectionChangeImpl(Ark_NativePointer node,
                                  const Opt_Callback_Number_Number_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //TextAreaModelNG::SetSetOnTextSelectionChange(frameNode, convValue);
}
void SetOnContentScrollImpl(Ark_NativePointer node,
                            const Opt_Callback_Number_Number_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //TextAreaModelNG::SetSetOnContentScroll(frameNode, convValue);
}
void SetOnEditChangeImpl(Ark_NativePointer node,
                         const Opt_Callback_Boolean_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //TextAreaModelNG::SetSetOnEditChange(frameNode, convValue);
}
void SetOnCopyImpl(Ark_NativePointer node,
                   const Opt_Callback_String_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //TextAreaModelNG::SetSetOnCopy(frameNode, convValue);
}
void SetOnCutImpl(Ark_NativePointer node,
                  const Opt_Callback_String_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //TextAreaModelNG::SetSetOnCut(frameNode, convValue);
}
void SetOnPasteImpl(Ark_NativePointer node,
                    const Opt_Callback_String_PasteEvent_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //TextAreaModelNG::SetSetOnPaste(frameNode, convValue);
}
void SetCopyOptionImpl(Ark_NativePointer node,
                       const Opt_CopyOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //TextAreaModelNG::SetSetCopyOption(frameNode, convValue);
}
void SetEnableKeyboardOnFocusImpl(Ark_NativePointer node,
                                  const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //TextAreaModelNG::SetSetEnableKeyboardOnFocus(frameNode, convValue);
}
void SetMaxLengthImpl(Ark_NativePointer node,
                      const Opt_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //TextAreaModelNG::SetSetMaxLength(frameNode, convValue);
}
void SetStyleImpl(Ark_NativePointer node,
                  const Opt_TextContentStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //TextAreaModelNG::SetSetStyle(frameNode, convValue);
}
void SetBarStateImpl(Ark_NativePointer node,
                     const Opt_BarState* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //TextAreaModelNG::SetSetBarState(frameNode, convValue);
}
void SetSelectionMenuHiddenImpl(Ark_NativePointer node,
                                const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //TextAreaModelNG::SetSetSelectionMenuHidden(frameNode, convValue);
}
void SetMinFontSizeImpl(Ark_NativePointer node,
                        const Opt_Union_Number_String_Resource* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //TextAreaModelNG::SetSetMinFontSize(frameNode, convValue);
}
void SetMaxFontSizeImpl(Ark_NativePointer node,
                        const Opt_Union_Number_String_Resource* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //TextAreaModelNG::SetSetMaxFontSize(frameNode, convValue);
}
void SetMinFontScaleImpl(Ark_NativePointer node,
                         const Opt_Union_Number_Resource* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //TextAreaModelNG::SetSetMinFontScale(frameNode, convValue);
}
void SetMaxFontScaleImpl(Ark_NativePointer node,
                         const Opt_Union_Number_Resource* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //TextAreaModelNG::SetSetMaxFontScale(frameNode, convValue);
}
void SetHeightAdaptivePolicyImpl(Ark_NativePointer node,
                                 const Opt_TextHeightAdaptivePolicy* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //TextAreaModelNG::SetSetHeightAdaptivePolicy(frameNode, convValue);
}
void SetMaxLinesImpl(Ark_NativePointer node,
                     const Opt_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //TextAreaModelNG::SetSetMaxLines(frameNode, convValue);
}
void SetWordBreakImpl(Ark_NativePointer node,
                      const Opt_WordBreak* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //TextAreaModelNG::SetSetWordBreak(frameNode, convValue);
}
void SetLineBreakStrategyImpl(Ark_NativePointer node,
                              const Opt_LineBreakStrategy* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //TextAreaModelNG::SetSetLineBreakStrategy(frameNode, convValue);
}
void SetDecorationImpl(Ark_NativePointer node,
                       const Opt_TextDecorationOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //TextAreaModelNG::SetSetDecoration(frameNode, convValue);
}
void SetLetterSpacingImpl(Ark_NativePointer node,
                          const Opt_Union_Number_String_Resource* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //TextAreaModelNG::SetSetLetterSpacing(frameNode, convValue);
}
void SetLineSpacingImpl(Ark_NativePointer node,
                        const Opt_LengthMetrics* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //TextAreaModelNG::SetSetLineSpacing(frameNode, convValue);
}
void SetLineHeightImpl(Ark_NativePointer node,
                       const Opt_Union_Number_String_Resource* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //TextAreaModelNG::SetSetLineHeight(frameNode, convValue);
}
void SetTypeImpl(Ark_NativePointer node,
                 const Opt_TextAreaType* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //TextAreaModelNG::SetSetType(frameNode, convValue);
}
void SetEnableAutoFillImpl(Ark_NativePointer node,
                           const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //TextAreaModelNG::SetSetEnableAutoFill(frameNode, convValue);
}
void SetContentTypeImpl(Ark_NativePointer node,
                        const Opt_ContentType* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //TextAreaModelNG::SetSetContentType(frameNode, convValue);
}
void SetFontFeatureImpl(Ark_NativePointer node,
                        const Opt_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //TextAreaModelNG::SetSetFontFeature(frameNode, convValue);
}
void SetOnWillInsertImpl(Ark_NativePointer node,
                         const Opt_Callback_InsertValue_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //TextAreaModelNG::SetSetOnWillInsert(frameNode, convValue);
}
void SetOnDidInsertImpl(Ark_NativePointer node,
                        const Opt_Callback_InsertValue_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //TextAreaModelNG::SetSetOnDidInsert(frameNode, convValue);
}
void SetOnWillDeleteImpl(Ark_NativePointer node,
                         const Opt_Callback_DeleteValue_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //TextAreaModelNG::SetSetOnWillDelete(frameNode, convValue);
}
void SetOnDidDeleteImpl(Ark_NativePointer node,
                        const Opt_Callback_DeleteValue_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //TextAreaModelNG::SetSetOnDidDelete(frameNode, convValue);
}
void SetEditMenuOptionsImpl(Ark_NativePointer node,
                            const Opt_EditMenuOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // TODO: Reset value
        return;
    }
    auto onCreateMenuCallback = [arkCreateMenu = CallbackHelper(optValue->onCreateMenu)](
        const std::vector<NG::MenuItemParam>& systemMenuItems) -> std::vector<NG::MenuOptionsParam> {
            auto menuItems = Converter::ArkValue<Array_TextMenuItem>(systemMenuItems, Converter::FC);
            auto result = arkCreateMenu.InvokeWithOptConvertResult<std::vector<NG::MenuOptionsParam>,
                Array_TextMenuItem, Callback_Array_TextMenuItem_Void>(menuItems);
            return result.value_or(std::vector<NG::MenuOptionsParam>());
        };
    auto onMenuItemClick = [arkMenuItemClick = CallbackHelper(optValue->onMenuItemClick)](
        NG::MenuItemParam menuOptionsParam) -> bool {
            TextRange range {.start = menuOptionsParam.start, .end = menuOptionsParam.end};
            auto menuItem = Converter::ArkValue<Ark_TextMenuItem>(menuOptionsParam);
            auto arkRange = Converter::ArkValue<Ark_TextRange>(range);
            auto arkResult = arkMenuItemClick.InvokeWithObtainResult<
                Ark_Boolean, Callback_Boolean_Void>(menuItem, arkRange);
            return Converter::Convert<bool>(arkResult);
        };
    TextFieldModelStatic::SetSelectionMenuOptions(frameNode, std::move(onCreateMenuCallback),
        std::move(onMenuItemClick));
}
void SetEnablePreviewTextImpl(Ark_NativePointer node,
                              const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //TextAreaModelNG::SetSetEnablePreviewText(frameNode, convValue);
}
void SetEnableHapticFeedbackImpl(Ark_NativePointer node,
                                 const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //TextAreaModelNG::SetSetEnableHapticFeedback(frameNode, convValue);
}
void SetAutoCapitalizationModeImpl(Ark_NativePointer node,
                                   const Opt_AutoCapitalizationMode* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //TextAreaModelNG::SetSetAutoCapitalizationMode(frameNode, convValue);
}
void SetHalfLeadingImpl(Ark_NativePointer node,
                        const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //TextAreaModelNG::SetSetHalfLeading(frameNode, convValue);
}
void SetEllipsisModeImpl(Ark_NativePointer node,
                         const Opt_EllipsisMode* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //TextAreaModelNG::SetSetEllipsisMode(frameNode, convValue);
}
void SetStopBackPressImpl(Ark_NativePointer node,
                          const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //TextAreaModelNG::SetSetStopBackPress(frameNode, convValue);
}
void SetOnWillChangeImpl(Ark_NativePointer node,
                         const Opt_Callback_EditableTextChangeValue_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //TextAreaModelNG::SetSetOnWillChange(frameNode, convValue);
}
void SetKeyboardAppearanceImpl(Ark_NativePointer node,
                               const Opt_KeyboardAppearance* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //TextAreaModelNG::SetSetKeyboardAppearance(frameNode, convValue);
}
void SetInputFilterImpl(Ark_NativePointer node,
                        const Opt_ResourceStr* value,
                        const Opt_Callback_String_Void* error)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(value);
    //auto convValue = Converter::OptConvert<type>(value); // for enums
    //TextAreaModelNG::SetSetInputFilter(frameNode, convValue);
}
void SetShowCounterImpl(Ark_NativePointer node,
                        const Opt_Boolean* value,
                        const Opt_InputCounterOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(value);
    //auto convValue = Converter::OptConvert<type>(value); // for enums
    //TextAreaModelNG::SetSetShowCounter(frameNode, convValue);
}
void SetCustomKeyboardImpl(Ark_NativePointer node,
                           const Opt_CustomNodeBuilder* value,
                           const Opt_KeyboardOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(value);
    //auto convValue = Converter::OptConvert<type>(value); // for enums
    //TextAreaModelNG::SetSetCustomKeyboard(frameNode, convValue);
}
} // TextAreaAttributeModifier
const GENERATED_ArkUITextAreaModifier* GetTextAreaModifier()
{
    static const GENERATED_ArkUITextAreaModifier ArkUITextAreaModifierImpl {
        TextAreaModifier::ConstructImpl,
        TextAreaInterfaceModifier::SetTextAreaOptionsImpl,
        TextAreaAttributeModifier::SetPlaceholderColorImpl,
        TextAreaAttributeModifier::SetPlaceholderFontImpl,
        TextAreaAttributeModifier::SetEnterKeyTypeImpl,
        TextAreaAttributeModifier::SetTextAlignImpl,
        TextAreaAttributeModifier::SetCaretColorImpl,
        TextAreaAttributeModifier::SetFontColorImpl,
        TextAreaAttributeModifier::SetFontSizeImpl,
        TextAreaAttributeModifier::SetFontStyleImpl,
        TextAreaAttributeModifier::SetFontWeightImpl,
        TextAreaAttributeModifier::SetFontFamilyImpl,
        TextAreaAttributeModifier::SetTextOverflowImpl,
        TextAreaAttributeModifier::SetTextIndentImpl,
        TextAreaAttributeModifier::SetCaretStyleImpl,
        TextAreaAttributeModifier::SetSelectedBackgroundColorImpl,
        TextAreaAttributeModifier::SetOnSubmitImpl,
        TextAreaAttributeModifier::SetOnChangeImpl,
        TextAreaAttributeModifier::SetOnTextSelectionChangeImpl,
        TextAreaAttributeModifier::SetOnContentScrollImpl,
        TextAreaAttributeModifier::SetOnEditChangeImpl,
        TextAreaAttributeModifier::SetOnCopyImpl,
        TextAreaAttributeModifier::SetOnCutImpl,
        TextAreaAttributeModifier::SetOnPasteImpl,
        TextAreaAttributeModifier::SetCopyOptionImpl,
        TextAreaAttributeModifier::SetEnableKeyboardOnFocusImpl,
        TextAreaAttributeModifier::SetMaxLengthImpl,
        TextAreaAttributeModifier::SetStyleImpl,
        TextAreaAttributeModifier::SetBarStateImpl,
        TextAreaAttributeModifier::SetSelectionMenuHiddenImpl,
        TextAreaAttributeModifier::SetMinFontSizeImpl,
        TextAreaAttributeModifier::SetMaxFontSizeImpl,
        TextAreaAttributeModifier::SetMinFontScaleImpl,
        TextAreaAttributeModifier::SetMaxFontScaleImpl,
        TextAreaAttributeModifier::SetHeightAdaptivePolicyImpl,
        TextAreaAttributeModifier::SetMaxLinesImpl,
        TextAreaAttributeModifier::SetWordBreakImpl,
        TextAreaAttributeModifier::SetLineBreakStrategyImpl,
        TextAreaAttributeModifier::SetDecorationImpl,
        TextAreaAttributeModifier::SetLetterSpacingImpl,
        TextAreaAttributeModifier::SetLineSpacingImpl,
        TextAreaAttributeModifier::SetLineHeightImpl,
        TextAreaAttributeModifier::SetTypeImpl,
        TextAreaAttributeModifier::SetEnableAutoFillImpl,
        TextAreaAttributeModifier::SetContentTypeImpl,
        TextAreaAttributeModifier::SetFontFeatureImpl,
        TextAreaAttributeModifier::SetOnWillInsertImpl,
        TextAreaAttributeModifier::SetOnDidInsertImpl,
        TextAreaAttributeModifier::SetOnWillDeleteImpl,
        TextAreaAttributeModifier::SetOnDidDeleteImpl,
        TextAreaAttributeModifier::SetEditMenuOptionsImpl,
        TextAreaAttributeModifier::SetEnablePreviewTextImpl,
        TextAreaAttributeModifier::SetEnableHapticFeedbackImpl,
        TextAreaAttributeModifier::SetAutoCapitalizationModeImpl,
        TextAreaAttributeModifier::SetHalfLeadingImpl,
        TextAreaAttributeModifier::SetEllipsisModeImpl,
        TextAreaAttributeModifier::SetStopBackPressImpl,
        TextAreaAttributeModifier::SetOnWillChangeImpl,
        TextAreaAttributeModifier::SetKeyboardAppearanceImpl,
        TextAreaAttributeModifier::SetInputFilterImpl,
        TextAreaAttributeModifier::SetShowCounterImpl,
        TextAreaAttributeModifier::SetCustomKeyboardImpl,
    };
    return &ArkUITextAreaModifierImpl;
}

}
