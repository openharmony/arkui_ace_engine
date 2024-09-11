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
namespace SymbolSpanInterfaceModifier {
void SetSymbolSpanOptionsImpl(Ark_NativePointer node,
                              const Ark_Resource* value)
{
}
} // SymbolSpanInterfaceModifier
namespace SymbolSpanAttributeModifier {
void FontSizeImpl(Ark_NativePointer node,
                  const Type_SymbolSpanAttribute_fontSize_Arg0* value)
{
}
void FontColorImpl(Ark_NativePointer node,
                   const Array_ResourceColor* value)
{
}
void FontWeightImpl(Ark_NativePointer node,
                    const Type_SymbolSpanAttribute_fontWeight_Arg0* value)
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
} // SymbolSpanAttributeModifier
const GENERATED_ArkUISymbolSpanModifier* GetSymbolSpanModifier()
{
    static const GENERATED_ArkUISymbolSpanModifier ArkUISymbolSpanModifierImpl {
        SymbolSpanInterfaceModifier::SetSymbolSpanOptionsImpl,
        SymbolSpanAttributeModifier::FontSizeImpl,
        SymbolSpanAttributeModifier::FontColorImpl,
        SymbolSpanAttributeModifier::FontWeightImpl,
        SymbolSpanAttributeModifier::EffectStrategyImpl,
        SymbolSpanAttributeModifier::RenderingStrategyImpl,
    };
    return &ArkUISymbolSpanModifierImpl;
}

}
