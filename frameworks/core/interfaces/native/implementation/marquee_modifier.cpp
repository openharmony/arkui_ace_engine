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
namespace MarqueeModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                Ark_Int32 flags)
{
    return {};
}
} // MarqueeModifier
namespace MarqueeInterfaceModifier {
void SetMarqueeOptionsImpl(Ark_NativePointer node,
                           const Ark_MarqueeOptions* options)
{
}
} // MarqueeInterfaceModifier
namespace MarqueeAttributeModifier {
void FontColorImpl(Ark_NativePointer node,
                   const Opt_ResourceColor* value)
{
}
void FontSizeImpl(Ark_NativePointer node,
                  const Opt_Length* value)
{
}
void AllowScaleImpl(Ark_NativePointer node,
                    const Opt_Boolean* value)
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
void MarqueeUpdateStrategyImpl(Ark_NativePointer node,
                               const Opt_MarqueeUpdateStrategy* value)
{
}
void OnStartImpl(Ark_NativePointer node,
                 const Opt_Callback_Void* value)
{
}
void OnBounceImpl(Ark_NativePointer node,
                  const Opt_Callback_Void* value)
{
}
void OnFinishImpl(Ark_NativePointer node,
                  const Opt_Callback_Void* value)
{
}
} // MarqueeAttributeModifier
const GENERATED_ArkUIMarqueeModifier* GetMarqueeModifier()
{
    static const GENERATED_ArkUIMarqueeModifier ArkUIMarqueeModifierImpl {
        MarqueeModifier::ConstructImpl,
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
