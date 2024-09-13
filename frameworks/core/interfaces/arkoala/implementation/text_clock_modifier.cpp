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
namespace TextClockInterfaceModifier {
void SetTextClockOptionsImpl(Ark_NativePointer node,
                             const Opt_Type_TextClockInterface_setTextClockOptions_Arg0* options)
{
}
} // TextClockInterfaceModifier
namespace TextClockAttributeModifier {
void FormatImpl(Ark_NativePointer node,
                const Ark_String* value)
{
}
void OnDateChangeImpl(Ark_NativePointer node,
                      Ark_Function event)
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
                    const Type_TextClockAttribute_fontWeight_Arg0* value)
{
}
void FontFamilyImpl(Ark_NativePointer node,
                    const ResourceStr* value)
{
}
void TextShadowImpl(Ark_NativePointer node,
                    const Type_TextClockAttribute_textShadow_Arg0* value)
{
}
void FontFeatureImpl(Ark_NativePointer node,
                     const Ark_String* value)
{
}
void ContentModifierImpl(Ark_NativePointer node,
                         const Ark_CustomObject* modifier)
{
}
void DateTimeOptionsImpl(Ark_NativePointer node,
                         const Opt_CustomObject* dateTimeOptions)
{
}
} // TextClockAttributeModifier
const GENERATED_ArkUITextClockModifier* GetTextClockModifier()
{
    static const GENERATED_ArkUITextClockModifier ArkUITextClockModifierImpl {
        TextClockInterfaceModifier::SetTextClockOptionsImpl,
        TextClockAttributeModifier::FormatImpl,
        TextClockAttributeModifier::OnDateChangeImpl,
        TextClockAttributeModifier::FontColorImpl,
        TextClockAttributeModifier::FontSizeImpl,
        TextClockAttributeModifier::FontStyleImpl,
        TextClockAttributeModifier::FontWeightImpl,
        TextClockAttributeModifier::FontFamilyImpl,
        TextClockAttributeModifier::TextShadowImpl,
        TextClockAttributeModifier::FontFeatureImpl,
        TextClockAttributeModifier::ContentModifierImpl,
        TextClockAttributeModifier::DateTimeOptionsImpl,
    };
    return &ArkUITextClockModifierImpl;
}

}
