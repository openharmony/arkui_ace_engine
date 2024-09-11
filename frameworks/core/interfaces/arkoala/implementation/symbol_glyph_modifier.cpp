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
namespace SymbolGlyphInterfaceModifier {
void SetSymbolGlyphOptionsImpl(Ark_NativePointer node,
                               const Opt_Resource* value)
{
}
} // SymbolGlyphInterfaceModifier
namespace SymbolGlyphAttributeModifier {
void FontSizeImpl(Ark_NativePointer node,
                  const Type_SymbolGlyphAttribute_fontSize_Arg0* value)
{
}
void FontColorImpl(Ark_NativePointer node,
                   const Array_ResourceColor* value)
{
}
void FontWeightImpl(Ark_NativePointer node,
                    const Type_SymbolGlyphAttribute_fontWeight_Arg0* value)
{
}
void EffectStrategyImpl(Ark_NativePointer node,
                        enum Ark_SymbolEffectStrategy value)
{
}
void RenderingStrategyImpl(Ark_NativePointer node,
                           enum Ark_SymbolRenderingStrategy value)
{
}
void SymbolEffect0Impl(Ark_NativePointer node,
                       const Ark_SymbolEffect* symbolEffect,
                       const Opt_Boolean* isActive)
{
}
void SymbolEffect1Impl(Ark_NativePointer node,
                       const Ark_SymbolEffect* symbolEffect,
                       const Opt_Number* triggerValue)
{
}
} // SymbolGlyphAttributeModifier
const GENERATED_ArkUISymbolGlyphModifier* GetSymbolGlyphModifier()
{
    static const GENERATED_ArkUISymbolGlyphModifier ArkUISymbolGlyphModifierImpl {
        SymbolGlyphInterfaceModifier::SetSymbolGlyphOptionsImpl,
        SymbolGlyphAttributeModifier::FontSizeImpl,
        SymbolGlyphAttributeModifier::FontColorImpl,
        SymbolGlyphAttributeModifier::FontWeightImpl,
        SymbolGlyphAttributeModifier::EffectStrategyImpl,
        SymbolGlyphAttributeModifier::RenderingStrategyImpl,
        SymbolGlyphAttributeModifier::SymbolEffect0Impl,
        SymbolGlyphAttributeModifier::SymbolEffect1Impl,
    };
    return &ArkUISymbolGlyphModifierImpl;
}

}
