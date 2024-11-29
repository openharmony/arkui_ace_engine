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

#include "core/components_ng/base/frame_node.h"
#include "core/interfaces/arkoala/utility/converter.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace TextModifier {
Ark_NativePointer ConstructImpl()
{
    return 0;
}
} // TextModifier
namespace TextInterfaceModifier {
void SetTextOptionsImpl(Ark_NativePointer node,
                        const Opt_Union_String_Resource* content,
                        const Opt_TextOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(content);
    //auto convValue = Converter::OptConvert<type>(content); // for enums
    //TextModelNG::SetSetTextOptions(frameNode, convValue);
}
} // TextInterfaceModifier
namespace TextAttributeModifier {
void Font0Impl(Ark_NativePointer node,
               const Ark_Font* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //TextModelNG::SetFont0(frameNode, convValue);
}
void Font1Impl(Ark_NativePointer node,
               const Ark_Font* fontValue,
               const Opt_FontSettingOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(fontValue);
    //auto convValue = Converter::OptConvert<type>(fontValue); // for enums
    //TextModelNG::SetFont1(frameNode, convValue);
}
void FontColorImpl(Ark_NativePointer node,
                   const Ark_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //TextModelNG::SetFontColor(frameNode, convValue);
}
void FontSizeImpl(Ark_NativePointer node,
                  const Ark_Union_Number_String_Resource* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //TextModelNG::SetFontSize(frameNode, convValue);
}
void MinFontSizeImpl(Ark_NativePointer node,
                     const Ark_Union_Number_String_Resource* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //TextModelNG::SetMinFontSize(frameNode, convValue);
}
void MaxFontSizeImpl(Ark_NativePointer node,
                     const Ark_Union_Number_String_Resource* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //TextModelNG::SetMaxFontSize(frameNode, convValue);
}
void MinFontScaleImpl(Ark_NativePointer node,
                      const Ark_Union_Number_Resource* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //TextModelNG::SetMinFontScale(frameNode, convValue);
}
void MaxFontScaleImpl(Ark_NativePointer node,
                      const Ark_Union_Number_Resource* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //TextModelNG::SetMaxFontScale(frameNode, convValue);
}
void FontStyleImpl(Ark_NativePointer node,
                   Ark_FontStyle value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(value);
    //auto convValue = Converter::OptConvert<type>(value); // for enums
    //TextModelNG::SetFontStyle(frameNode, convValue);
}
void FontWeight0Impl(Ark_NativePointer node,
                     const Ark_Union_Number_FontWeight_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //TextModelNG::SetFontWeight0(frameNode, convValue);
}
void FontWeight1Impl(Ark_NativePointer node,
                     const Ark_Union_Number_FontWeight_String* weight,
                     const Opt_FontSettingOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(weight);
    //auto convValue = Converter::OptConvert<type>(weight); // for enums
    //TextModelNG::SetFontWeight1(frameNode, convValue);
}
void LineSpacingImpl(Ark_NativePointer node,
                     const Ark_LengthMetrics* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //TextModelNG::SetLineSpacing(frameNode, convValue);
}
void TextAlignImpl(Ark_NativePointer node,
                   Ark_TextAlign value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(value);
    //auto convValue = Converter::OptConvert<type>(value); // for enums
    //TextModelNG::SetTextAlign(frameNode, convValue);
}
void LineHeightImpl(Ark_NativePointer node,
                    const Ark_Union_Number_String_Resource* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //TextModelNG::SetLineHeight(frameNode, convValue);
}
void TextOverflowImpl(Ark_NativePointer node,
                      const Ark_TextOverflowOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //TextModelNG::SetTextOverflow(frameNode, convValue);
}
void FontFamilyImpl(Ark_NativePointer node,
                    const Ark_Union_String_Resource* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //TextModelNG::SetFontFamily(frameNode, convValue);
}
void MaxLinesImpl(Ark_NativePointer node,
                  const Ark_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //TextModelNG::SetMaxLines(frameNode, convValue);
}
void DecorationImpl(Ark_NativePointer node,
                    const Ark_DecorationStyleInterface* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //TextModelNG::SetDecoration(frameNode, convValue);
}
void LetterSpacingImpl(Ark_NativePointer node,
                       const Ark_Union_Number_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //TextModelNG::SetLetterSpacing(frameNode, convValue);
}
void TextCaseImpl(Ark_NativePointer node,
                  Ark_TextCase value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(value);
    //auto convValue = Converter::OptConvert<type>(value); // for enums
    //TextModelNG::SetTextCase(frameNode, convValue);
}
void BaselineOffsetImpl(Ark_NativePointer node,
                        const Ark_Union_Number_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //TextModelNG::SetBaselineOffset(frameNode, convValue);
}
void CopyOptionImpl(Ark_NativePointer node,
                    Ark_CopyOptions value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(value);
    //auto convValue = Converter::OptConvert<type>(value); // for enums
    //TextModelNG::SetCopyOption(frameNode, convValue);
}
void DraggableImpl(Ark_NativePointer node,
                   Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::Convert<bool>(value);
    //TextModelNG::SetDraggable(frameNode, convValue);
}
void TextShadowImpl(Ark_NativePointer node,
                    const Ark_Union_ShadowOptions_Array_ShadowOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //TextModelNG::SetTextShadow(frameNode, convValue);
}
void HeightAdaptivePolicyImpl(Ark_NativePointer node,
                              Ark_TextHeightAdaptivePolicy value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(value);
    //auto convValue = Converter::OptConvert<type>(value); // for enums
    //TextModelNG::SetHeightAdaptivePolicy(frameNode, convValue);
}
void TextIndentImpl(Ark_NativePointer node,
                    const Ark_Length* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //TextModelNG::SetTextIndent(frameNode, convValue);
}
void WordBreakImpl(Ark_NativePointer node,
                   Ark_WordBreak value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(value);
    //auto convValue = Converter::OptConvert<type>(value); // for enums
    //TextModelNG::SetWordBreak(frameNode, convValue);
}
void LineBreakStrategyImpl(Ark_NativePointer node,
                           Ark_LineBreakStrategy value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(value);
    //auto convValue = Converter::OptConvert<type>(value); // for enums
    //TextModelNG::SetLineBreakStrategy(frameNode, convValue);
}
void OnCopyImpl(Ark_NativePointer node,
                const Callback_String_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //TextModelNG::SetOnCopy(frameNode, convValue);
}
void CaretColorImpl(Ark_NativePointer node,
                    const Ark_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //TextModelNG::SetCaretColor(frameNode, convValue);
}
void SelectedBackgroundColorImpl(Ark_NativePointer node,
                                 const Ark_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //TextModelNG::SetSelectedBackgroundColor(frameNode, convValue);
}
void EllipsisModeImpl(Ark_NativePointer node,
                      Ark_EllipsisMode value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(value);
    //auto convValue = Converter::OptConvert<type>(value); // for enums
    //TextModelNG::SetEllipsisMode(frameNode, convValue);
}
void EnableDataDetectorImpl(Ark_NativePointer node,
                            Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::Convert<bool>(value);
    //TextModelNG::SetEnableDataDetector(frameNode, convValue);
}
void DataDetectorConfigImpl(Ark_NativePointer node,
                            const Ark_TextDataDetectorConfig* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //TextModelNG::SetDataDetectorConfig(frameNode, convValue);
}
void OnTextSelectionChangeImpl(Ark_NativePointer node,
                               const Callback_Number_Number_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //TextModelNG::SetOnTextSelectionChange(frameNode, convValue);
}
void FontFeatureImpl(Ark_NativePointer node,
                     const Ark_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto convValue = Converter::Convert<std::string>(*value);
    //TextModelNG::SetFontFeature(frameNode, convValue);
}
void PrivacySensitiveImpl(Ark_NativePointer node,
                          Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::Convert<bool>(value);
    //TextModelNG::SetPrivacySensitive(frameNode, convValue);
}
void TextSelectableImpl(Ark_NativePointer node,
                        Ark_TextSelectableMode value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(value);
    //auto convValue = Converter::OptConvert<type>(value); // for enums
    //TextModelNG::SetTextSelectable(frameNode, convValue);
}
void EditMenuOptionsImpl(Ark_NativePointer node,
                         const Ark_EditMenuOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //TextModelNG::SetEditMenuOptions(frameNode, convValue);
}
void HalfLeadingImpl(Ark_NativePointer node,
                     Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::Convert<bool>(value);
    //TextModelNG::SetHalfLeading(frameNode, convValue);
}
void EnableHapticFeedbackImpl(Ark_NativePointer node,
                              Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::Convert<bool>(value);
    //TextModelNG::SetEnableHapticFeedback(frameNode, convValue);
}
void SelectionImpl(Ark_NativePointer node,
                   const Ark_Number* selectionStart,
                   const Ark_Number* selectionEnd)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(selectionStart);
    //auto convValue = Converter::OptConvert<type>(selectionStart); // for enums
    //TextModelNG::SetSelection(frameNode, convValue);
}
void BindSelectionMenuImpl(Ark_NativePointer node,
                           Ark_TextSpanType spanType,
                           const Callback_Any* content,
                           Ark_TextResponseType responseType,
                           const Opt_SelectionMenuOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(spanType);
    //auto convValue = Converter::OptConvert<type>(spanType); // for enums
    //TextModelNG::SetBindSelectionMenu(frameNode, convValue);
}
} // TextAttributeModifier
const GENERATED_ArkUITextModifier* GetTextModifier()
{
    static const GENERATED_ArkUITextModifier ArkUITextModifierImpl {
        TextModifier::ConstructImpl,
        TextInterfaceModifier::SetTextOptionsImpl,
        TextAttributeModifier::Font0Impl,
        TextAttributeModifier::Font1Impl,
        TextAttributeModifier::FontColorImpl,
        TextAttributeModifier::FontSizeImpl,
        TextAttributeModifier::MinFontSizeImpl,
        TextAttributeModifier::MaxFontSizeImpl,
        TextAttributeModifier::MinFontScaleImpl,
        TextAttributeModifier::MaxFontScaleImpl,
        TextAttributeModifier::FontStyleImpl,
        TextAttributeModifier::FontWeight0Impl,
        TextAttributeModifier::FontWeight1Impl,
        TextAttributeModifier::LineSpacingImpl,
        TextAttributeModifier::TextAlignImpl,
        TextAttributeModifier::LineHeightImpl,
        TextAttributeModifier::TextOverflowImpl,
        TextAttributeModifier::FontFamilyImpl,
        TextAttributeModifier::MaxLinesImpl,
        TextAttributeModifier::DecorationImpl,
        TextAttributeModifier::LetterSpacingImpl,
        TextAttributeModifier::TextCaseImpl,
        TextAttributeModifier::BaselineOffsetImpl,
        TextAttributeModifier::CopyOptionImpl,
        TextAttributeModifier::DraggableImpl,
        TextAttributeModifier::TextShadowImpl,
        TextAttributeModifier::HeightAdaptivePolicyImpl,
        TextAttributeModifier::TextIndentImpl,
        TextAttributeModifier::WordBreakImpl,
        TextAttributeModifier::LineBreakStrategyImpl,
        TextAttributeModifier::OnCopyImpl,
        TextAttributeModifier::CaretColorImpl,
        TextAttributeModifier::SelectedBackgroundColorImpl,
        TextAttributeModifier::EllipsisModeImpl,
        TextAttributeModifier::EnableDataDetectorImpl,
        TextAttributeModifier::DataDetectorConfigImpl,
        TextAttributeModifier::OnTextSelectionChangeImpl,
        TextAttributeModifier::FontFeatureImpl,
        TextAttributeModifier::PrivacySensitiveImpl,
        TextAttributeModifier::TextSelectableImpl,
        TextAttributeModifier::EditMenuOptionsImpl,
        TextAttributeModifier::HalfLeadingImpl,
        TextAttributeModifier::EnableHapticFeedbackImpl,
        TextAttributeModifier::SelectionImpl,
        TextAttributeModifier::BindSelectionMenuImpl,
    };
    return &ArkUITextModifierImpl;
}

}
