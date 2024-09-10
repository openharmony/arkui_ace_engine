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
namespace TextInterfaceModifier {
void SetTextOptionsImpl(Ark_NativePointer node,
                        const Opt_Type_TextInterface_setTextOptions_Arg0* content,
                        const Opt_TextOptions* value)
{
}
} // TextInterfaceModifier
namespace TextAttributeModifier {
void Font0Impl(Ark_NativePointer node,
               const Ark_Font* value)
{
}
void Font1Impl(Ark_NativePointer node,
               const Ark_Font* fontValue,
               const Opt_FontSettingOptions* options)
{
}
void FontColorImpl(Ark_NativePointer node,
                   const ResourceColor* value)
{
}
void FontSizeImpl(Ark_NativePointer node,
                  const Type_TextAttribute_fontSize_Arg0* value)
{
}
void MinFontSizeImpl(Ark_NativePointer node,
                     const Type_TextAttribute_minFontSize_Arg0* value)
{
}
void MaxFontSizeImpl(Ark_NativePointer node,
                     const Type_TextAttribute_maxFontSize_Arg0* value)
{
}
void MinFontScaleImpl(Ark_NativePointer node,
                      const Type_TextAttribute_minFontScale_Arg0* scale)
{
}
void MaxFontScaleImpl(Ark_NativePointer node,
                      const Type_TextAttribute_maxFontScale_Arg0* scale)
{
}
void FontStyleImpl(Ark_NativePointer node,
                   Ark_Int32 value)
{
}
void FontWeight0Impl(Ark_NativePointer node,
                     const Type_TextAttribute_fontWeight_Arg0* value)
{
}
void FontWeight1Impl(Ark_NativePointer node,
                     const Type_TextAttribute_fontWeight1_Arg0* weight,
                     const Opt_FontSettingOptions* options)
{
}
void LineSpacingImpl(Ark_NativePointer node,
                     const Ark_CustomObject* value)
{
}
void TextAlignImpl(Ark_NativePointer node,
                   Ark_Int32 value)
{
}
void LineHeightImpl(Ark_NativePointer node,
                    const Type_TextAttribute_lineHeight_Arg0* value)
{
}
void TextOverflowImpl(Ark_NativePointer node,
                      const Ark_TextOverflowOptions* options)
{
}
void FontFamilyImpl(Ark_NativePointer node,
                    const Type_TextAttribute_fontFamily_Arg0* value)
{
}
void MaxLinesImpl(Ark_NativePointer node,
                  const Ark_Number* value)
{
}
void DecorationImpl(Ark_NativePointer node,
                    const Ark_DecorationStyleInterface* value)
{
}
void LetterSpacingImpl(Ark_NativePointer node,
                       const Type_TextAttribute_letterSpacing_Arg0* value)
{
}
void TextCaseImpl(Ark_NativePointer node,
                  Ark_Int32 value)
{
}
void BaselineOffsetImpl(Ark_NativePointer node,
                        const Type_TextAttribute_baselineOffset_Arg0* value)
{
}
void CopyOptionImpl(Ark_NativePointer node,
                    Ark_Int32 value)
{
}
void DraggableImpl(Ark_NativePointer node,
                   Ark_Boolean value)
{
}
void TextShadowImpl(Ark_NativePointer node,
                    const Type_TextAttribute_textShadow_Arg0* value)
{
}
void HeightAdaptivePolicyImpl(Ark_NativePointer node,
                              Ark_Int32 value)
{
}
void TextIndentImpl(Ark_NativePointer node,
                    const Ark_Length* value)
{
}
void WordBreakImpl(Ark_NativePointer node,
                   Ark_Int32 value)
{
}
void LineBreakStrategyImpl(Ark_NativePointer node,
                           Ark_Int32 strategy)
{
}
void OnCopyImpl(Ark_NativePointer node,
                Ark_Function callback)
{
}
void SelectionImpl(Ark_NativePointer node,
                   const Ark_Number* selectionStart,
                   const Ark_Number* selectionEnd)
{
}
void EllipsisModeImpl(Ark_NativePointer node,
                      Ark_Int32 value)
{
}
void EnableDataDetectorImpl(Ark_NativePointer node,
                            Ark_Boolean enable)
{
}
void DataDetectorConfigImpl(Ark_NativePointer node,
                            const Ark_TextDataDetectorConfig* config)
{
}
void BindSelectionMenuImpl(Ark_NativePointer node,
                           Ark_Int32 spanType,
                           const CustomBuilder* content,
                           Ark_Int32 responseType,
                           const Opt_SelectionMenuOptions* options)
{
}
void OnTextSelectionChangeImpl(Ark_NativePointer node,
                               Ark_Function callback)
{
}
void FontFeatureImpl(Ark_NativePointer node,
                     const Ark_String* value)
{
}
void PrivacySensitiveImpl(Ark_NativePointer node,
                          Ark_Boolean supported)
{
}
void TextSelectableImpl(Ark_NativePointer node,
                        Ark_Int32 mode)
{
}
void EditMenuOptionsImpl(Ark_NativePointer node,
                         const Ark_Materialized* editMenu)
{
}
void HalfLeadingImpl(Ark_NativePointer node,
                     Ark_Boolean halfLeading)
{
}
} // TextAttributeModifier
const GENERATED_ArkUITextModifier* GetTextModifier()
{
    static const GENERATED_ArkUITextModifier ArkUITextModifierImpl {
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
        TextAttributeModifier::SelectionImpl,
        TextAttributeModifier::EllipsisModeImpl,
        TextAttributeModifier::EnableDataDetectorImpl,
        TextAttributeModifier::DataDetectorConfigImpl,
        TextAttributeModifier::BindSelectionMenuImpl,
        TextAttributeModifier::OnTextSelectionChangeImpl,
        TextAttributeModifier::FontFeatureImpl,
        TextAttributeModifier::PrivacySensitiveImpl,
        TextAttributeModifier::TextSelectableImpl,
        TextAttributeModifier::EditMenuOptionsImpl,
        TextAttributeModifier::HalfLeadingImpl,
    };
    return &ArkUITextModifierImpl;
}

}
