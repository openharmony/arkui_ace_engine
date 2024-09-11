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
namespace MarqueeInterfaceModifier {
void SetMarqueeOptionsImpl(Ark_NativePointer node,
                           const Ark_MarqueeOptions* options)
{
}
} // MarqueeInterfaceModifier
namespace MarqueeAttributeModifier {
void FontColorImpl(Ark_NativePointer node,
                   const ResourceColor* value)
{
}
void FontSizeImpl(Ark_NativePointer node,
                  const Ark_Length* value)
{
}
void AllowScaleImpl(Ark_NativePointer node,
                    Ark_Boolean value)
{
}
void FontWeightImpl(Ark_NativePointer node,
                    const Type_MarqueeAttribute_fontWeight_Arg0* value)
{
}
void FontFamilyImpl(Ark_NativePointer node,
                    const Type_MarqueeAttribute_fontFamily_Arg0* value)
{
}
void MarqueeUpdateStrategyImpl(Ark_NativePointer node,
                               enum Ark_MarqueeUpdateStrategy value)
{
}
void OnStartImpl(Ark_NativePointer node,
                 Ark_Function event)
{
}
void OnBounceImpl(Ark_NativePointer node,
                  Ark_Function event)
{
}
void OnFinishImpl(Ark_NativePointer node,
                  Ark_Function event)
{
}
} // MarqueeAttributeModifier
const GENERATED_ArkUIMarqueeModifier* GetMarqueeModifier()
{
    static const GENERATED_ArkUIMarqueeModifier ArkUIMarqueeModifierImpl {
        MarqueeInterfaceModifier::SetMarqueeOptionsImpl,
        MarqueeAttributeModifier::FontColorImpl,
        MarqueeAttributeModifier::FontSizeImpl,
        MarqueeAttributeModifier::AllowScaleImpl,
        MarqueeAttributeModifier::FontWeightImpl,
        MarqueeAttributeModifier::FontFamilyImpl,
        MarqueeAttributeModifier::MarqueeUpdateStrategyImpl,
        MarqueeAttributeModifier::OnStartImpl,
        MarqueeAttributeModifier::OnBounceImpl,
        MarqueeAttributeModifier::OnFinishImpl,
    };
    return &ArkUIMarqueeModifierImpl;
}

}
