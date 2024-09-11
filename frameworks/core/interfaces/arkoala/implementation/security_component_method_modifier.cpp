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
namespace SecurityComponentMethodModifier {
void IconSizeImpl(Ark_NativePointer node,
                  const Ark_Length* value)
{
}
void LayoutDirectionImpl(Ark_NativePointer node,
                         enum Ark_SecurityComponentLayoutDirection value)
{
}
void PositionImpl(Ark_NativePointer node,
                  const Ark_Position* value)
{
}
void MarkAnchorImpl(Ark_NativePointer node,
                    const Ark_Position* value)
{
}
void OffsetImpl(Ark_NativePointer node,
                const Type_SecurityComponentMethod_offset_Arg0* value)
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
                    const Type_SecurityComponentMethod_fontWeight_Arg0* value)
{
}
void FontFamilyImpl(Ark_NativePointer node,
                    const Type_SecurityComponentMethod_fontFamily_Arg0* value)
{
}
void FontColorImpl(Ark_NativePointer node,
                   const ResourceColor* value)
{
}
void IconColorImpl(Ark_NativePointer node,
                   const ResourceColor* value)
{
}
void BackgroundColorImpl(Ark_NativePointer node,
                         const ResourceColor* value)
{
}
void BorderStyleImpl(Ark_NativePointer node,
                     enum Ark_BorderStyle value)
{
}
void BorderWidthImpl(Ark_NativePointer node,
                     const Ark_Length* value)
{
}
void BorderColorImpl(Ark_NativePointer node,
                     const ResourceColor* value)
{
}
void BorderRadiusImpl(Ark_NativePointer node,
                      const Ark_Length* value)
{
}
void PaddingImpl(Ark_NativePointer node,
                 const Type_SecurityComponentMethod_padding_Arg0* value)
{
}
void TextIconSpaceImpl(Ark_NativePointer node,
                       const Ark_Length* value)
{
}
void KeyImpl(Ark_NativePointer node,
             const Ark_String* value)
{
}
void WidthImpl(Ark_NativePointer node,
               const Ark_Length* value)
{
}
void HeightImpl(Ark_NativePointer node,
                const Ark_Length* value)
{
}
void SizeImpl(Ark_NativePointer node,
              const Ark_SizeOptions* value)
{
}
void ConstraintSizeImpl(Ark_NativePointer node,
                        const Ark_ConstraintSizeOptions* value)
{
}
} // SecurityComponentMethodModifier
const GENERATED_ArkUISecurityComponentMethodModifier* GetSecurityComponentMethodModifier()
{
    static const GENERATED_ArkUISecurityComponentMethodModifier ArkUISecurityComponentMethodModifierImpl {
        SecurityComponentMethodModifier::IconSizeImpl,
        SecurityComponentMethodModifier::LayoutDirectionImpl,
        SecurityComponentMethodModifier::PositionImpl,
        SecurityComponentMethodModifier::MarkAnchorImpl,
        SecurityComponentMethodModifier::OffsetImpl,
        SecurityComponentMethodModifier::FontSizeImpl,
        SecurityComponentMethodModifier::FontStyleImpl,
        SecurityComponentMethodModifier::FontWeightImpl,
        SecurityComponentMethodModifier::FontFamilyImpl,
        SecurityComponentMethodModifier::FontColorImpl,
        SecurityComponentMethodModifier::IconColorImpl,
        SecurityComponentMethodModifier::BackgroundColorImpl,
        SecurityComponentMethodModifier::BorderStyleImpl,
        SecurityComponentMethodModifier::BorderWidthImpl,
        SecurityComponentMethodModifier::BorderColorImpl,
        SecurityComponentMethodModifier::BorderRadiusImpl,
        SecurityComponentMethodModifier::PaddingImpl,
        SecurityComponentMethodModifier::TextIconSpaceImpl,
        SecurityComponentMethodModifier::KeyImpl,
        SecurityComponentMethodModifier::WidthImpl,
        SecurityComponentMethodModifier::HeightImpl,
        SecurityComponentMethodModifier::SizeImpl,
        SecurityComponentMethodModifier::ConstraintSizeImpl,
    };
    return &ArkUISecurityComponentMethodModifierImpl;
}

}
