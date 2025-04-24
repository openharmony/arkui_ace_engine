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
namespace SliderModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                Ark_Int32 flags)
{
    return {};
}
} // SliderModifier
namespace SliderInterfaceModifier {
void SetSliderOptionsImpl(Ark_NativePointer node,
                          const Opt_SliderOptions* options)
{
}
} // SliderInterfaceModifier
namespace SliderAttributeModifier {
void BlockColorImpl(Ark_NativePointer node,
                    const Opt_ResourceColor* value)
{
}
void TrackColorImpl(Ark_NativePointer node,
                    const Opt_Union_ResourceColor_LinearGradient* value)
{
}
void SelectedColor0Impl(Ark_NativePointer node,
                        const Opt_ResourceColor* value)
{
}
void SelectedColor1Impl(Ark_NativePointer node,
                        const Opt_Union_ResourceColor_LinearGradient* value)
{
}
void MinLabelImpl(Ark_NativePointer node,
                  const Opt_String* value)
{
}
void MaxLabelImpl(Ark_NativePointer node,
                  const Opt_String* value)
{
}
void ShowStepsImpl(Ark_NativePointer node,
                   const Opt_Boolean* value)
{
}
void TrackThicknessImpl(Ark_NativePointer node,
                        const Opt_Length* value)
{
}
void OnChangeImpl(Ark_NativePointer node,
                  const Opt_Callback_Number_SliderChangeMode_Void* value)
{
}
void BlockBorderColorImpl(Ark_NativePointer node,
                          const Opt_ResourceColor* value)
{
}
void BlockBorderWidthImpl(Ark_NativePointer node,
                          const Opt_Length* value)
{
}
void StepColorImpl(Ark_NativePointer node,
                   const Opt_ResourceColor* value)
{
}
void TrackBorderRadiusImpl(Ark_NativePointer node,
                           const Opt_Length* value)
{
}
void SelectedBorderRadiusImpl(Ark_NativePointer node,
                              const Opt_Length* value)
{
}
void BlockSizeImpl(Ark_NativePointer node,
                   const Opt_SizeOptions* value)
{
}
void BlockStyleImpl(Ark_NativePointer node,
                    const Opt_SliderBlockStyle* value)
{
}
void StepSizeImpl(Ark_NativePointer node,
                  const Opt_Length* value)
{
}
void SliderInteractionModeImpl(Ark_NativePointer node,
                               const Opt_SliderInteraction* value)
{
}
void MinResponsiveDistanceImpl(Ark_NativePointer node,
                               const Opt_Number* value)
{
}
void ContentModifierImpl(Ark_NativePointer node,
                         const Opt_ContentModifier* value)
{
}
void SlideRangeImpl(Ark_NativePointer node,
                    const Opt_SlideRange* value)
{
}
void DigitalCrownSensitivityImpl(Ark_NativePointer node,
                                 const Opt_CrownSensitivity* value)
{
}
void EnableHapticFeedbackImpl(Ark_NativePointer node,
                              const Opt_Boolean* value)
{
}
void ShowTipsImpl(Ark_NativePointer node,
                  const Opt_Boolean* value,
                  const Opt_ResourceStr* content)
{
}
void _onChangeEvent_valueImpl(Ark_NativePointer node,
                              const Callback_Number_Void* callback)
{
}
} // SliderAttributeModifier
const GENERATED_ArkUISliderModifier* GetSliderModifier()
{
    static const GENERATED_ArkUISliderModifier ArkUISliderModifierImpl {
        SliderModifier::ConstructImpl,
        SliderInterfaceModifier::SetSliderOptionsImpl,
        SliderAttributeModifier::BlockColorImpl,
        SliderAttributeModifier::TrackColorImpl,
        SliderAttributeModifier::SelectedColor0Impl,
        SliderAttributeModifier::SelectedColor1Impl,
        SliderAttributeModifier::MinLabelImpl,
        SliderAttributeModifier::MaxLabelImpl,
        SliderAttributeModifier::ShowStepsImpl,
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
        SliderAttributeModifier::DigitalCrownSensitivityImpl,
        SliderAttributeModifier::EnableHapticFeedbackImpl,
        SliderAttributeModifier::ShowTipsImpl,
        SliderAttributeModifier::_onChangeEvent_valueImpl,
    };
    return &ArkUISliderModifierImpl;
}

}
