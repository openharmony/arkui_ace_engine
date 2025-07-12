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
#include "core/components_ng/pattern/slider/slider_model_ng.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/interfaces/native/utility/validators.h"
#include "core/interfaces/native/generated/interface/node_api.h"

namespace OHOS::Ace::NG::Converter {
struct SliderOptions {
    std::optional<float> value;
    std::optional<float> min;
    std::optional<float> max;
    std::optional<float> step;
    std::optional<SliderModel::SliderMode> style;
    std::optional<Axis> direction;
    std::optional<bool> reverse;
};

template<>
SliderOptions Convert(const Ark_SliderOptions& src)
{
    return {
        .value = Converter::OptConvert<float>(src.value),
        .min = Converter::OptConvert<float>(src.min),
        .max = Converter::OptConvert<float>(src.max),
        .step = Converter::OptConvert<float>(src.step),
        .style = Converter::OptConvert<SliderModel::SliderMode>(src.style),
        .direction = Converter::OptConvert<Axis>(src.direction),
        .reverse = Converter::OptConvert<bool>(src.reverse),
    };
}

struct SliderRange {
    std::optional<float> from;
    std::optional<float> to;
};

template<>
SliderRange Convert(const Ark_SlideRange& src)
{
    return {
        .from = Converter::OptConvert<float>(src.from),
        .to = Converter::OptConvert<float>(src.to)
    };
}

struct SliderBlockSizeOptions {
    std::optional<Dimension> width;
    std::optional<Dimension> height;
};

template<>
SliderBlockSizeOptions Convert(const Ark_SizeOptions& src)
{
    return {
        .width = Converter::OptConvert<Dimension>(src.width),
        .height = Converter::OptConvert<Dimension>(src.height)
    };
}

struct SliderBlockImageInfo {
    std::optional<std::string> value;
    std::optional<std::string> bundleName;
    std::optional<std::string> moduleName;
};

struct SliderBlockStyle {
    std::optional<SliderModel::BlockStyleType> type;
    std::optional<ImageSourceInfo> image;
    std::optional<std::string> shape;
};

template<>
SliderBlockStyle Convert(const Ark_SliderBlockStyle& src)
{
    return {
        .type = Converter::OptConvert<SliderModel::BlockStyleType>(src.type),
        .image = Converter::OptConvert<ImageSourceInfo>(src.image),
        .shape = Converter::OptConvert<std::string>(src.shape)
    };
}
}
namespace OHOS::Ace::NG::GeneratedModifier {
namespace SliderModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                Ark_Int32 flags)
{
    auto frameNode = SliderModelNG::CreateFrameNode(id);
    CHECK_NULL_RETURN(frameNode, nullptr);
    frameNode->IncRefCount();
    return AceType::RawPtr(frameNode);
}
} // SliderModifier
namespace SliderInterfaceModifier {
void SetSliderOptionsImpl(Ark_NativePointer node,
                          const Opt_SliderOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = options ? Converter::OptConvert<Converter::SliderOptions>(*options) : std::nullopt;

    if (convValue.has_value()) {
    } else {
    }
}
} // SliderInterfaceModifier
namespace SliderAttributeModifier {
void BlockColorImpl(Ark_NativePointer node,
                    const Ark_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto convValue = Converter::OptConvert<Color>(*value);
}
void TrackColorImpl(Ark_NativePointer node,
                    const Ark_Union_ResourceColor_LinearGradient* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);

    Converter::VisitUnion(*value,
        [frameNode](const Ark_ResourceColor& value) {
            auto colorOpt = Converter::OptConvert<Color>(value);
            auto gradientOpt = colorOpt.has_value() ?
                std::optional<Gradient>{SliderModelNG::CreateSolidGradient(colorOpt.value())} : std::nullopt;
        },
        [frameNode](const Ark_LinearGradient& value) {
            auto gradientOpt = Converter::OptConvert<Gradient>(value);
        },
        []() {}
    );
}
void SelectedColorImpl(Ark_NativePointer node, const Ark_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto convValue = Converter::OptConvert<Color>(*value);
    if (convValue.has_value()) {
        SliderModelNG::SetSelectColor(frameNode, SliderModelNG::CreateSolidGradient(Color(convValue.value())), true);
    } else {
        SliderModelNG::ResetSelectColor(frameNode);
    }
}
void MinLabelImpl(Ark_NativePointer node,
                  const Ark_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto convValue = Converter::OptConvert<float>(*value);
}
void MaxLabelImpl(Ark_NativePointer node,
                  const Ark_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto convValue = Converter::OptConvert<float>(*value);
}
void ShowStepsImpl(Ark_NativePointer node,
                   Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::Convert<bool>(value);
    SliderModelNG::SetShowSteps(frameNode, convValue);
}
void TrackThicknessImpl(Ark_NativePointer node,
                        const Ark_Length* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto convValue = value ? Converter::OptConvert<Dimension>(*value) : std::nullopt;
    Validator::ValidatePositive(convValue);
}
void OnChangeImpl(Ark_NativePointer node,
                  const Callback_Number_SliderChangeMode_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto onChange = [arkCallback = CallbackHelper(*value)](float newValue, int32_t mode) {
        Ark_Number arkValue = Converter::ArkValue<Ark_Number>(newValue);
        Ark_SliderChangeMode arkMode = Converter::ArkValue<Ark_SliderChangeMode>(
            static_cast<SliderModel::SliderChangeMode>(mode));
        arkCallback.Invoke(arkValue, arkMode);
    };
    SliderModelNG::SetOnChange(frameNode, std::move(onChange));
}
void BlockBorderColorImpl(Ark_NativePointer node,
                          const Ark_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto convValue = Converter::OptConvert<Color>(*value);
}
void BlockBorderWidthImpl(Ark_NativePointer node,
                          const Ark_Length* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto convValue = value ? Converter::OptConvert<Dimension>(*value) : std::nullopt;
    Validator::ValidateNonNegative(convValue);
}
void StepColorImpl(Ark_NativePointer node,
                   const Ark_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto convValue = Converter::OptConvert<Color>(*value);
}
void TrackBorderRadiusImpl(Ark_NativePointer node,
                           const Ark_Length* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto convValue = value ? Converter::OptConvert<Dimension>(*value) : std::nullopt;
    Validator::ValidateNonNegative(convValue);
}
void SelectedBorderRadiusImpl(Ark_NativePointer node,
                              const Ark_Length* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto convValue = value ? Converter::OptConvert<Dimension>(*value) : std::nullopt;
    Validator::ValidateNonNegative(convValue);
}
void BlockSizeImpl(Ark_NativePointer node,
                   const Ark_SizeOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto convValue = Converter::Convert<Converter::SliderBlockSizeOptions>(*value);
}
void BlockStyleImpl(Ark_NativePointer node,
                    const Ark_SliderBlockStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto convValue = Converter::OptConvert<Converter::SliderBlockStyle>(*value);
    if (convValue.has_value()) {
        if (convValue.value().image.has_value()) {
            SliderModelNG::SetBlockImage(frameNode, convValue.value().image->GetSrc(),
                convValue.value().image->GetBundleName(), convValue.value().image->GetModuleName());
        } else {
            SliderModelNG::ResetBlockImage(frameNode);
        }
        LOGE("SliderModifier::BlockStyleImpl is not implemented, raw pointer is not supported!");
    }
}
void StepSizeImpl(Ark_NativePointer node,
                  const Ark_Length* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto convValue = value ? Converter::OptConvert<Dimension>(*value) : std::nullopt;
    Validator::ValidateNonNegative(convValue);
}
void SliderInteractionModeImpl(Ark_NativePointer node,
                               Ark_SliderInteraction value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<SliderModel::SliderInteraction>(value);
}
void MinResponsiveDistanceImpl(Ark_NativePointer node,
                               const Ark_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto convValue = value ? Converter::OptConvert<float>(*value) : std::nullopt;
    Validator::ValidateNonNegative(convValue);
}
void ContentModifierImpl(Ark_NativePointer node,
                         const Ark_CustomObject* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    LOGE("SliderModifier::ContentModifierImpl is not implemented, Ark_CustomObject is not supported!");
}
void SlideRangeImpl(Ark_NativePointer node,
                    const Ark_SlideRange* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto convValue = Converter::Convert<Converter::SliderRange>(*value);
}
void ShowTipsImpl(Ark_NativePointer node,
                  Ark_Boolean value,
                  const Opt_ResourceStr* content)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::Convert<bool>(value);
    auto convContent = content ? Converter::OptConvert<std::string>(*content) : std::nullopt;
    SliderModelNG::SetShowTips(frameNode, convValue, convContent);
}
void _onChangeEvent_valueImpl(Ark_NativePointer node,
                              const Callback_Number_Void* callback)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(callback);
    WeakPtr<FrameNode> weakNode = AceType::WeakClaim(frameNode);
    auto onEvent = [arkCallback = CallbackHelper(*callback), weakNode](float value) {
        PipelineContext::SetCallBackNode(weakNode);
        arkCallback.Invoke(Converter::ArkValue<Ark_Number>(value));
    };
}
} // SliderAttributeModifier
const GENERATED_ArkUISliderModifier* GetSliderModifier()
{
    static const GENERATED_ArkUISliderModifier ArkUISliderModifierImpl {
        SliderModifier::ConstructImpl,
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
        SliderAttributeModifier::_onChangeEvent_valueImpl,
    };
    return &ArkUISliderModifierImpl;
}

}
