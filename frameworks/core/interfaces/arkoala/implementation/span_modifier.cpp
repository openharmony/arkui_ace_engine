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
namespace SpanInterfaceModifier {
void SetSpanOptionsImpl(Ark_NativePointer node,
                        const Type_SpanInterface_setSpanOptions_Arg0* value)
{
}
} // SpanInterfaceModifier
namespace SpanAttributeModifier {
void FontImpl(Ark_NativePointer node,
              const Ark_Font* value)
{
}
void FontColorImpl(Ark_NativePointer node,
                   const ResourceColor* value)
{
}
void FontSizeImpl(Ark_NativePointer node,
                  const Type_SpanAttribute_fontSize_Arg0* value)
{
}
void FontStyleImpl(Ark_NativePointer node,
                   enum Ark_FontStyle value)
{
}
void FontWeightImpl(Ark_NativePointer node,
                    const Type_SpanAttribute_fontWeight_Arg0* value)
{
}
void FontFamilyImpl(Ark_NativePointer node,
                    const Type_SpanAttribute_fontFamily_Arg0* value)
{
}
void DecorationImpl(Ark_NativePointer node,
                    const Ark_DecorationStyleInterface* value)
{
}
void LetterSpacingImpl(Ark_NativePointer node,
                       const Type_SpanAttribute_letterSpacing_Arg0* value)
{
}
void TextCaseImpl(Ark_NativePointer node,
                  enum Ark_TextCase value)
{
}
void LineHeightImpl(Ark_NativePointer node,
                    const Ark_Length* value)
{
}
void TextShadowImpl(Ark_NativePointer node,
                    const Type_SpanAttribute_textShadow_Arg0* value)
{
}
} // SpanAttributeModifier
const GENERATED_ArkUISpanModifier* GetSpanModifier()
{
    static const GENERATED_ArkUISpanModifier ArkUISpanModifierImpl {
        SpanInterfaceModifier::SetSpanOptionsImpl,
        SpanAttributeModifier::FontImpl,
        SpanAttributeModifier::FontColorImpl,
        SpanAttributeModifier::FontSizeImpl,
        SpanAttributeModifier::FontStyleImpl,
        SpanAttributeModifier::FontWeightImpl,
        SpanAttributeModifier::FontFamilyImpl,
        SpanAttributeModifier::DecorationImpl,
        SpanAttributeModifier::LetterSpacingImpl,
        SpanAttributeModifier::TextCaseImpl,
        SpanAttributeModifier::LineHeightImpl,
        SpanAttributeModifier::TextShadowImpl,
    };
    return &ArkUISpanModifierImpl;
}

}
