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
namespace SecurityComponentMethodModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                Ark_Int32 flags)
{
    return {};
}
void IconSizeImpl(Ark_NativePointer node,
                  const Opt_Length* value)
{
}
void LayoutDirectionImpl(Ark_NativePointer node,
                         const Opt_SecurityComponentLayoutDirection* value)
{
}
void PositionImpl(Ark_NativePointer node,
                  const Opt_Position* value)
{
}
void MarkAnchorImpl(Ark_NativePointer node,
                    const Opt_Position* value)
{
}
void OffsetImpl(Ark_NativePointer node,
                const Opt_Union_Position_Edges_LocalizedEdges* value)
{
}
void FontSizeImpl(Ark_NativePointer node,
                  const Opt_Length* value)
{
}
void FontStyleImpl(Ark_NativePointer node,
                   const Opt_FontStyle* value)
{
}
void FontWeightImpl(Ark_NativePointer node,
                    const Opt_Union_Number_FontWeight_String* value)
{
}
void FontFamilyImpl(Ark_NativePointer node,
                    const Opt_Union_String_Resource* value)
{
}
void FontColorImpl(Ark_NativePointer node,
                   const Opt_ResourceColor* value)
{
}
void IconColorImpl(Ark_NativePointer node,
                   const Opt_ResourceColor* value)
{
}
void BackgroundColorImpl(Ark_NativePointer node,
                         const Opt_ResourceColor* value)
{
}
void BorderStyleImpl(Ark_NativePointer node,
                     const Opt_BorderStyle* value)
{
}
void BorderWidthImpl(Ark_NativePointer node,
                     const Opt_Length* value)
{
}
void BorderColorImpl(Ark_NativePointer node,
                     const Opt_ResourceColor* value)
{
}
void BorderRadius0Impl(Ark_NativePointer node,
                       const Opt_Length* value)
{
}
void BorderRadius1Impl(Ark_NativePointer node,
                       const Opt_Union_Dimension_BorderRadiuses* value)
{
}
void PaddingImpl(Ark_NativePointer node,
                 const Opt_Union_Padding_Dimension* value)
{
}
void TextIconSpaceImpl(Ark_NativePointer node,
                       const Opt_Length* value)
{
}
void KeyImpl(Ark_NativePointer node,
             const Opt_String* value)
{
}
void WidthImpl(Ark_NativePointer node,
               const Opt_Length* value)
{
}
void HeightImpl(Ark_NativePointer node,
                const Opt_Length* value)
{
}
void SizeImpl(Ark_NativePointer node,
              const Opt_SizeOptions* value)
{
}
void ConstraintSizeImpl(Ark_NativePointer node,
                        const Opt_ConstraintSizeOptions* value)
{
}
void AlignImpl(Ark_NativePointer node,
               const Opt_Alignment* value)
{
}
void AlignRules0Impl(Ark_NativePointer node,
                     const Opt_AlignRuleOption* value)
{
}
void AlignRules1Impl(Ark_NativePointer node,
                     const Opt_LocalizedAlignRuleOptions* value)
{
}
void IdImpl(Ark_NativePointer node,
            const Opt_String* value)
{
}
void MinFontScaleImpl(Ark_NativePointer node,
                      const Opt_Union_Number_Resource* value)
{
}
void MaxFontScaleImpl(Ark_NativePointer node,
                      const Opt_Union_Number_Resource* value)
{
}
void MaxLinesImpl(Ark_NativePointer node,
                  const Opt_Number* value)
{
}
void MinFontSizeImpl(Ark_NativePointer node,
                     const Opt_Union_Number_String_Resource* value)
{
}
void MaxFontSizeImpl(Ark_NativePointer node,
                     const Opt_Union_Number_String_Resource* value)
{
}
void HeightAdaptivePolicyImpl(Ark_NativePointer node,
                              const Opt_TextHeightAdaptivePolicy* value)
{
}
void EnabledImpl(Ark_NativePointer node,
                 const Opt_Boolean* value)
{
}
void ChainModeImpl(Ark_NativePointer node,
                   const Opt_Axis* direction,
                   const Opt_ChainStyle* style)
{
}
} // SecurityComponentMethodModifier
const GENERATED_ArkUISecurityComponentMethodModifier* GetSecurityComponentMethodModifier()
{
    static const GENERATED_ArkUISecurityComponentMethodModifier ArkUISecurityComponentMethodModifierImpl {
        SecurityComponentMethodModifier::ConstructImpl,
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
        SecurityComponentMethodModifier::BorderRadius0Impl,
        SecurityComponentMethodModifier::BorderRadius1Impl,
        SecurityComponentMethodModifier::PaddingImpl,
        SecurityComponentMethodModifier::TextIconSpaceImpl,
        SecurityComponentMethodModifier::KeyImpl,
        SecurityComponentMethodModifier::WidthImpl,
        SecurityComponentMethodModifier::HeightImpl,
        SecurityComponentMethodModifier::SizeImpl,
        SecurityComponentMethodModifier::ConstraintSizeImpl,
        SecurityComponentMethodModifier::AlignImpl,
        SecurityComponentMethodModifier::AlignRules0Impl,
        SecurityComponentMethodModifier::AlignRules1Impl,
        SecurityComponentMethodModifier::IdImpl,
        SecurityComponentMethodModifier::MinFontScaleImpl,
        SecurityComponentMethodModifier::MaxFontScaleImpl,
        SecurityComponentMethodModifier::MaxLinesImpl,
        SecurityComponentMethodModifier::MinFontSizeImpl,
        SecurityComponentMethodModifier::MaxFontSizeImpl,
        SecurityComponentMethodModifier::HeightAdaptivePolicyImpl,
        SecurityComponentMethodModifier::EnabledImpl,
        SecurityComponentMethodModifier::ChainModeImpl,
    };
    return &ArkUISecurityComponentMethodModifierImpl;
}

}
