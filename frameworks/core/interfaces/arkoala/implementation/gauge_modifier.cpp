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
namespace GaugeInterfaceModifier {
void SetGaugeOptionsImpl(Ark_NativePointer node,
                         const Ark_GaugeOptions* options)
{
}
} // GaugeInterfaceModifier
namespace GaugeAttributeModifier {
void ValueImpl(Ark_NativePointer node,
               const Ark_Number* value)
{
}
void StartAngleImpl(Ark_NativePointer node,
                    const Ark_Number* angle)
{
}
void EndAngleImpl(Ark_NativePointer node,
                  const Ark_Number* angle)
{
}
void ColorsImpl(Ark_NativePointer node,
                const Type_GaugeAttribute_colors_Arg0* colors)
{
}
void StrokeWidthImpl(Ark_NativePointer node,
                     const Ark_Length* length)
{
}
void DescriptionImpl(Ark_NativePointer node,
                     const CustomBuilder* value)
{
}
void TrackShadowImpl(Ark_NativePointer node,
                     const Ark_GaugeShadowOptions* value)
{
}
void IndicatorImpl(Ark_NativePointer node,
                   const Ark_GaugeIndicatorOptions* value)
{
}
void PrivacySensitiveImpl(Ark_NativePointer node,
                          const Opt_Boolean* isPrivacySensitiveMode)
{
}
void ContentModifierImpl(Ark_NativePointer node,
                         const Ark_CustomObject* modifier)
{
}
} // GaugeAttributeModifier
const GENERATED_ArkUIGaugeModifier* GetGaugeModifier()
{
    static const GENERATED_ArkUIGaugeModifier ArkUIGaugeModifierImpl {
        GaugeInterfaceModifier::SetGaugeOptionsImpl,
        GaugeAttributeModifier::ValueImpl,
        GaugeAttributeModifier::StartAngleImpl,
        GaugeAttributeModifier::EndAngleImpl,
        GaugeAttributeModifier::ColorsImpl,
        GaugeAttributeModifier::StrokeWidthImpl,
        GaugeAttributeModifier::DescriptionImpl,
        GaugeAttributeModifier::TrackShadowImpl,
        GaugeAttributeModifier::IndicatorImpl,
        GaugeAttributeModifier::PrivacySensitiveImpl,
        GaugeAttributeModifier::ContentModifierImpl,
    };
    return &ArkUIGaugeModifierImpl;
}

}
