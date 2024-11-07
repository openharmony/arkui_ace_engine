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

#include "core/components_ng/base/frame_node.h"
#include "core/interfaces/arkoala/utility/converter.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
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
void BlockColorImpl(Ark_NativePointer node,
                    const Ark_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //SliderModelNG::SetBlockColor(frameNode, convValue);
}
void TrackColorImpl(Ark_NativePointer node,
                    const Ark_Union_ResourceColor_LinearGradient* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //SliderModelNG::SetTrackColor(frameNode, convValue);
}
void SelectedColorImpl(Ark_NativePointer node,
                       const Ark_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //SliderModelNG::SetSelectedColor(frameNode, convValue);
}
void MinLabelImpl(Ark_NativePointer node,
                  const Ark_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto convValue = Converter::Convert<std::string>(*value);
    //SliderModelNG::SetMinLabel(frameNode, convValue);
}
void MaxLabelImpl(Ark_NativePointer node,
                  const Ark_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto convValue = Converter::Convert<std::string>(*value);
    //SliderModelNG::SetMaxLabel(frameNode, convValue);
}
void ShowStepsImpl(Ark_NativePointer node,
                   Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::Convert<bool>(value);
    //SliderModelNG::SetShowSteps(frameNode, convValue);
}
void TrackThicknessImpl(Ark_NativePointer node,
                        const Ark_Length* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //SliderModelNG::SetTrackThickness(frameNode, convValue);
}
void OnChangeImpl(Ark_NativePointer node,
                  const Ark_Callback_Number_SliderChangeMode_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //SliderModelNG::SetOnChange(frameNode, convValue);
}
void BlockBorderColorImpl(Ark_NativePointer node,
                          const Ark_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //SliderModelNG::SetBlockBorderColor(frameNode, convValue);
}
void BlockBorderWidthImpl(Ark_NativePointer node,
                          const Ark_Length* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //SliderModelNG::SetBlockBorderWidth(frameNode, convValue);
}
void StepColorImpl(Ark_NativePointer node,
                   const Ark_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //SliderModelNG::SetStepColor(frameNode, convValue);
}
void TrackBorderRadiusImpl(Ark_NativePointer node,
                           const Ark_Length* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //SliderModelNG::SetTrackBorderRadius(frameNode, convValue);
}
void SelectedBorderRadiusImpl(Ark_NativePointer node,
                              const Ark_Length* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //SliderModelNG::SetSelectedBorderRadius(frameNode, convValue);
}
void BlockSizeImpl(Ark_NativePointer node,
                   const Ark_SizeOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //SliderModelNG::SetBlockSize(frameNode, convValue);
}
void BlockStyleImpl(Ark_NativePointer node,
                    const Ark_SliderBlockStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //SliderModelNG::SetBlockStyle(frameNode, convValue);
}
void StepSizeImpl(Ark_NativePointer node,
                  const Ark_Length* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //SliderModelNG::SetStepSize(frameNode, convValue);
}
void SliderInteractionModeImpl(Ark_NativePointer node,
                               Ark_SliderInteraction value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(value);
    //auto convValue = Converter::OptConvert<type>(value); // for enums
    //SliderModelNG::SetSliderInteractionMode(frameNode, convValue);
}
void MinResponsiveDistanceImpl(Ark_NativePointer node,
                               const Ark_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //SliderModelNG::SetMinResponsiveDistance(frameNode, convValue);
}
void ContentModifierImpl(Ark_NativePointer node,
                         const Ark_CustomObject* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //SliderModelNG::SetContentModifier(frameNode, convValue);
}
void SlideRangeImpl(Ark_NativePointer node,
                    const Ark_SlideRange* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //SliderModelNG::SetSlideRange(frameNode, convValue);
}
void ShowTipsImpl(Ark_NativePointer node,
                  Ark_Boolean value,
                  const Opt_ResourceStr* content)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(value);
    //auto convValue = Converter::OptConvert<type>(value); // for enums
    //SliderModelNG::SetShowTips(frameNode, convValue);
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
        SliderAttributeModifier::ShowTipsImpl,
    };
    return &ArkUISliderModifierImpl;
}

}
