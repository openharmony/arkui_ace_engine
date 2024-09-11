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
namespace SliderInterfaceModifier {
void SetSliderOptionsImpl(Ark_NativePointer node,
                          const Opt_SliderOptions* options)
{
}
} // SliderInterfaceModifier
namespace SliderAttributeModifier {
void BlockColorImpl(Ark_NativePointer node,
                    const ResourceColor* value)
{
}
void TrackColorImpl(Ark_NativePointer node,
                    const Type_SliderAttribute_trackColor_Arg0* value)
{
}
void SelectedColorImpl(Ark_NativePointer node,
                       const ResourceColor* value)
{
}
void MinLabelImpl(Ark_NativePointer node,
                  const Ark_String* value)
{
}
void MaxLabelImpl(Ark_NativePointer node,
                  const Ark_String* value)
{
}
void ShowStepsImpl(Ark_NativePointer node,
                   Ark_Boolean value)
{
}
void ShowTipsImpl(Ark_NativePointer node,
                  Ark_Boolean value,
                  const Opt_ResourceStr* content)
{
}
void TrackThicknessImpl(Ark_NativePointer node,
                        const Ark_Length* value)
{
}
void OnChangeImpl(Ark_NativePointer node,
                  Ark_Function callback)
{
}
void BlockBorderColorImpl(Ark_NativePointer node,
                          const ResourceColor* value)
{
}
void BlockBorderWidthImpl(Ark_NativePointer node,
                          const Ark_Length* value)
{
}
void StepColorImpl(Ark_NativePointer node,
                   const ResourceColor* value)
{
}
void TrackBorderRadiusImpl(Ark_NativePointer node,
                           const Ark_Length* value)
{
}
void SelectedBorderRadiusImpl(Ark_NativePointer node,
                              const Ark_Length* value)
{
}
void BlockSizeImpl(Ark_NativePointer node,
                   const Ark_SizeOptions* value)
{
}
void BlockStyleImpl(Ark_NativePointer node,
                    const Ark_SliderBlockStyle* value)
{
}
void StepSizeImpl(Ark_NativePointer node,
                  const Ark_Length* value)
{
}
void SliderInteractionModeImpl(Ark_NativePointer node,
                               enum Ark_SliderInteraction value)
{
}
void MinResponsiveDistanceImpl(Ark_NativePointer node,
                               const Ark_Number* value)
{
}
void ContentModifierImpl(Ark_NativePointer node,
                         const Ark_CustomObject* modifier)
{
}
void SlideRangeImpl(Ark_NativePointer node,
                    const Ark_SlideRange* value)
{
}
} // SliderAttributeModifier
const GENERATED_ArkUISliderModifier* GetSliderModifier()
{
    static const GENERATED_ArkUISliderModifier ArkUISliderModifierImpl {
        SliderInterfaceModifier::SetSliderOptionsImpl,
        SliderAttributeModifier::BlockColorImpl,
        SliderAttributeModifier::TrackColorImpl,
        SliderAttributeModifier::SelectedColorImpl,
        SliderAttributeModifier::MinLabelImpl,
        SliderAttributeModifier::MaxLabelImpl,
        SliderAttributeModifier::ShowStepsImpl,
        SliderAttributeModifier::ShowTipsImpl,
        SliderAttributeModifier::TrackThicknessImpl,
        SliderAttributeModifier::OnChangeImpl,
        SliderAttributeModifier::BlockBorderColorImpl,
        SliderAttributeModifier::BlockBorderWidthImpl,
        SliderAttributeModifier::StepColorImpl,
        SliderAttributeModifier::TrackBorderRadiusImpl,
        SliderAttributeModifier::SelectedBorderRadiusImpl,
        SliderAttributeModifier::BlockSizeImpl,
        SliderAttributeModifier::BlockStyleImpl,
        SliderAttributeModifier::StepSizeImpl,
        SliderAttributeModifier::SliderInteractionModeImpl,
        SliderAttributeModifier::MinResponsiveDistanceImpl,
        SliderAttributeModifier::ContentModifierImpl,
        SliderAttributeModifier::SlideRangeImpl,
    };
    return &ArkUISliderModifierImpl;
}

}
