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
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = options ? Converter::OptConvert<type>(*options) : std::nullopt;
    //SliderModelNG::SetSetSliderOptions(frameNode, convValue);
}
} // SliderInterfaceModifier
namespace SliderAttributeModifier {
void SetBlockColorImpl(Ark_NativePointer node,
                       const Opt_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //SliderModelNG::SetSetBlockColor(frameNode, convValue);
}
void SetTrackColorImpl(Ark_NativePointer node,
                       const Opt_Union_ResourceColor_LinearGradient* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //SliderModelNG::SetSetTrackColor(frameNode, convValue);
}
void SetSelectedColorImpl(Ark_NativePointer node,
                          const Opt_Union_ResourceColor_LinearGradient* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //SliderModelNG::SetSetSelectedColor(frameNode, convValue);
}
void SetShowStepsImpl(Ark_NativePointer node,
                      const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //SliderModelNG::SetSetShowSteps(frameNode, convValue);
}
void SetTrackThicknessImpl(Ark_NativePointer node,
                           const Opt_Length* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //SliderModelNG::SetSetTrackThickness(frameNode, convValue);
}
void SetOnChangeImpl(Ark_NativePointer node,
                     const Opt_Callback_Number_SliderChangeMode_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //SliderModelNG::SetSetOnChange(frameNode, convValue);
}
void SetBlockBorderColorImpl(Ark_NativePointer node,
                             const Opt_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //SliderModelNG::SetSetBlockBorderColor(frameNode, convValue);
}
void SetBlockBorderWidthImpl(Ark_NativePointer node,
                             const Opt_Length* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //SliderModelNG::SetSetBlockBorderWidth(frameNode, convValue);
}
void SetStepColorImpl(Ark_NativePointer node,
                      const Opt_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //SliderModelNG::SetSetStepColor(frameNode, convValue);
}
void SetTrackBorderRadiusImpl(Ark_NativePointer node,
                              const Opt_Length* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //SliderModelNG::SetSetTrackBorderRadius(frameNode, convValue);
}
void SetSelectedBorderRadiusImpl(Ark_NativePointer node,
                                 const Opt_Dimension* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //SliderModelNG::SetSetSelectedBorderRadius(frameNode, convValue);
}
void SetBlockSizeImpl(Ark_NativePointer node,
                      const Opt_SizeOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //SliderModelNG::SetSetBlockSize(frameNode, convValue);
}
void SetBlockStyleImpl(Ark_NativePointer node,
                       const Opt_SliderBlockStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //SliderModelNG::SetSetBlockStyle(frameNode, convValue);
}
void SetStepSizeImpl(Ark_NativePointer node,
                     const Opt_Length* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //SliderModelNG::SetSetStepSize(frameNode, convValue);
}
void SetSliderInteractionModeImpl(Ark_NativePointer node,
                                  const Opt_SliderInteraction* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //SliderModelNG::SetSetSliderInteractionMode(frameNode, convValue);
}
void SetMinResponsiveDistanceImpl(Ark_NativePointer node,
                                  const Opt_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //SliderModelNG::SetSetMinResponsiveDistance(frameNode, convValue);
}
void SetContentModifierImpl(Ark_NativePointer node,
                            const Opt_ContentModifier* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //SliderModelNG::SetSetContentModifier(frameNode, convValue);
}
void SetSlideRangeImpl(Ark_NativePointer node,
                       const Opt_SlideRange* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //SliderModelNG::SetSetSlideRange(frameNode, convValue);
}
void SetDigitalCrownSensitivityImpl(Ark_NativePointer node,
                                    const Opt_CrownSensitivity* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //SliderModelNG::SetSetDigitalCrownSensitivity(frameNode, convValue);
}
void SetEnableHapticFeedbackImpl(Ark_NativePointer node,
                                 const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //SliderModelNG::SetSetEnableHapticFeedback(frameNode, convValue);
}
void SetShowTipsImpl(Ark_NativePointer node,
                     const Opt_Boolean* value,
                     const Opt_ResourceStr* content)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(value);
    //auto convValue = Converter::OptConvert<type>(value); // for enums
    //SliderModelNG::SetSetShowTips(frameNode, convValue);
}
} // SliderAttributeModifier
const GENERATED_ArkUISliderModifier* GetSliderModifier()
{
    static const GENERATED_ArkUISliderModifier ArkUISliderModifierImpl {
        SliderModifier::ConstructImpl,
        SliderInterfaceModifier::SetSliderOptionsImpl,
        SliderAttributeModifier::SetBlockColorImpl,
        SliderAttributeModifier::SetTrackColorImpl,
        SliderAttributeModifier::SetSelectedColorImpl,
        SliderAttributeModifier::SetShowStepsImpl,
        SliderAttributeModifier::SetTrackThicknessImpl,
        SliderAttributeModifier::SetOnChangeImpl,
        SliderAttributeModifier::SetBlockBorderColorImpl,
        SliderAttributeModifier::SetBlockBorderWidthImpl,
        SliderAttributeModifier::SetStepColorImpl,
        SliderAttributeModifier::SetTrackBorderRadiusImpl,
        SliderAttributeModifier::SetSelectedBorderRadiusImpl,
        SliderAttributeModifier::SetBlockSizeImpl,
        SliderAttributeModifier::SetBlockStyleImpl,
        SliderAttributeModifier::SetStepSizeImpl,
        SliderAttributeModifier::SetSliderInteractionModeImpl,
        SliderAttributeModifier::SetMinResponsiveDistanceImpl,
        SliderAttributeModifier::SetContentModifierImpl,
        SliderAttributeModifier::SetSlideRangeImpl,
        SliderAttributeModifier::SetDigitalCrownSensitivityImpl,
        SliderAttributeModifier::SetEnableHapticFeedbackImpl,
        SliderAttributeModifier::SetShowTipsImpl,
    };
    return &ArkUISliderModifierImpl;
}

}
