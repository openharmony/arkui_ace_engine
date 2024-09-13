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
namespace TextTimerInterfaceModifier {
void SetTextTimerOptionsImpl(Ark_NativePointer node,
                             const Opt_TextTimerOptions* options)
{
}
} // TextTimerInterfaceModifier
namespace TextTimerAttributeModifier {
void FormatImpl(Ark_NativePointer node,
                const Ark_String* value)
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
                    const Type_TextTimerAttribute_fontWeight_Arg0* value)
{
}
void FontFamilyImpl(Ark_NativePointer node,
                    const ResourceStr* value)
{
}
void OnTimerImpl(Ark_NativePointer node,
                 Ark_Function event)
{
}
void TextShadowImpl(Ark_NativePointer node,
                    const Type_TextTimerAttribute_textShadow_Arg0* value)
{
}
void ContentModifierImpl(Ark_NativePointer node,
                         const Ark_CustomObject* modifier)
{
}
} // TextTimerAttributeModifier
const GENERATED_ArkUITextTimerModifier* GetTextTimerModifier()
{
    static const GENERATED_ArkUITextTimerModifier ArkUITextTimerModifierImpl {
        TextTimerInterfaceModifier::SetTextTimerOptionsImpl,
        TextTimerAttributeModifier::FormatImpl,
        TextTimerAttributeModifier::FontColorImpl,
        TextTimerAttributeModifier::FontSizeImpl,
        TextTimerAttributeModifier::FontStyleImpl,
        TextTimerAttributeModifier::FontWeightImpl,
        TextTimerAttributeModifier::FontFamilyImpl,
        TextTimerAttributeModifier::OnTimerImpl,
        TextTimerAttributeModifier::TextShadowImpl,
        TextTimerAttributeModifier::ContentModifierImpl,
    };
    return &ArkUITextTimerModifierImpl;
}

}
