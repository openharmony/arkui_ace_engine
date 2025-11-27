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
#include "core/components_ng/pattern/slider/slider_model_static.h"
#include "core/components/slider/slider_theme.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/interfaces/native/utility/validators.h"

namespace OHOS::Ace::NG {
namespace {
std::optional<float> ProcessBindableValue(FrameNode* frameNode, const Opt_Union_F64_Bindable& value)
{
    std::optional<float> result;
    Converter::VisitUnion(value,
        [&result](const Ark_Float64& src) {
            result = Converter::OptConvert<float>(src);
        },
        [&result, frameNode](const Ark_Bindable_F64& src) {
            result = Converter::OptConvert<float>(src.value);
            WeakPtr<FrameNode> weakNode = AceType::WeakClaim(frameNode);
            auto onEvent = [arkCallback = CallbackHelper(src.onChange), weakNode](float value) {
                PipelineContext::SetCallBackNode(weakNode);
                arkCallback.Invoke(Converter::ArkValue<Ark_Float64>(value));
            };
            SliderModelStatic::SetOnChangeEvent(frameNode, std::move(onEvent));
        },
        [] {});
    return result;
}
} // namespace
namespace Converter {
template<>
SliderModel::SliderStepItemAccessibility Convert(const Ark_SliderStepItemAccessibility& src)
{
    auto textOpt = Converter::OptConvert<std::string>(src.text);
    return textOpt.has_value() ? SliderModel::SliderStepItemAccessibility(std::move(textOpt.value()))
                               : SliderModel::SliderStepItemAccessibility();
}

template<>
SliderModel::SliderShowStepOptions Convert(const Ark_SliderShowStepOptions& src)
{
    SliderModel::SliderShowStepOptions dst;
    const auto& accessibilityOpt = src.stepsAccessibility;
    if (accessibilityOpt.tag == InteropTag::INTEROP_TAG_UNDEFINED) {
        return dst;
    }
    auto stepItemAccessibility = Converter::OptConvert<Map_Number_SliderStepItemAccessibility>(accessibilityOpt.value);
    if (!stepItemAccessibility) {
        return dst;
    }

    auto stepItemMap = stepItemAccessibility.value();
    auto mapSize = Converter::Convert<int32_t>(stepItemMap.size);
    if (mapSize <= 0 || !stepItemMap.keys || !stepItemMap.values) {
        return dst;
    }
    for (int32_t i = 0; i < mapSize; i++) {
        uint32_t key = Converter::Convert<uint32_t>(stepItemMap.keys[i]);
        if (key < 0) {
            continue;
        }
        auto stepItem = Converter::Convert<Ark_SliderStepItemAccessibility>(stepItemMap.values[i]);
        auto textOpt = Converter::OptConvert<std::string>(stepItem.text);
        if (!textOpt.has_value()) {
            continue;
        }
        dst[key] = std::move(textOpt.value());
    }

    return dst;
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
        .width = Converter::OptConvertFromArkNumStrRes<Opt_Length, Ark_Number>(src.width, DimensionUnit::VP),
        .height = Converter::OptConvertFromArkNumStrRes<Opt_Length, Ark_Number>(src.height, DimensionUnit::VP)
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
    std::optional<RefPtr<BasicShape>> shape;
};

template<>
SliderBlockStyle Convert(const Ark_SliderBlockStyle& src)
{
    const Opt_Union_CircleShape_EllipseShape_PathShape_RectShape* shape = &(src.shape);
    return {
        .type = Converter::OptConvert<SliderModel::BlockStyleType>(src.type),
        .image = Converter::OptConvert<ImageSourceInfo>(src.image),
        .shape = Converter::OptConvertPtr<RefPtr<BasicShape>>(shape)
    };
}
} // namespace Converter
} // namespace OHOS::Ace::NG
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
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optOptions = Converter::GetOptPtr(options);
    CHECK_NULL_VOID(optOptions);
    auto value = ProcessBindableValue(frameNode, optOptions->value);
    auto minVal = Converter::OptConvert<float>(optOptions->min);
    auto maxVal = Converter::OptConvert<float>(optOptions->max);
    auto step = Converter::OptConvert<float>(optOptions->step);
    auto style = Converter::OptConvert<SliderModel::SliderMode>(optOptions->style);
    auto direction = Converter::OptConvert<Axis>(optOptions->direction);
    auto reverse = Converter::OptConvert<bool>(optOptions->reverse);

    SliderModelStatic::SetMinLabel(frameNode, minVal);
    SliderModelStatic::SetMaxLabel(frameNode, maxVal);
    Validator::ValidatePositive(step);
    SliderModelStatic::SetStep(frameNode, step);
    SliderModelStatic::SetSliderValue(frameNode, value);
    SliderModelStatic::SetDirection(frameNode, direction);
    SliderModelStatic::SetReverse(frameNode, reverse);
    SliderModelStatic::SetSliderMode(frameNode, style);
}
} // SliderInterfaceModifier
namespace SliderAttributeModifier {
void SetBlockColorImpl(Ark_NativePointer node,
                       const Opt_Union_ResourceColor_LinearGradient* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    Converter::VisitUnion(
        *value,
        [frameNode](const Ark_ResourceColor& value) {
            auto colorOpt = Converter::OptConvert<Color>(value);
            if (!colorOpt.has_value()) {
                SliderModelNG::ResetBlockColor(frameNode);
                return;
            }
            SliderModelNG::SetBlockColor(frameNode, colorOpt.value());
        },
        [frameNode](const Ark_LinearGradient& value) {
            auto gradientOpt = Converter::OptConvert<Gradient>(value);
            if (!gradientOpt.has_value()) {
                SliderModelNG::ResetBlockColor(frameNode);
                return;
            }
            SliderModelNG::SetLinearGradientBlockColor(frameNode, gradientOpt.value());
        },
        [frameNode]() { SliderModelNG::ResetBlockColor(frameNode); });
}

void SetTrackColorImpl(Ark_NativePointer node,
                       const Opt_Union_ResourceColor_LinearGradient* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    Converter::VisitUnion(*value,
        [frameNode](const Ark_ResourceColor& value) {
            auto colorOpt = Converter::OptConvert<Color>(value);
            auto gradientOpt = colorOpt.has_value() ?
                std::optional<Gradient>{SliderModelNG::CreateSolidGradient(colorOpt.value())} : std::nullopt;
            SliderModelStatic::SetTrackBackgroundColor(frameNode, gradientOpt, true);
        },
        [frameNode](const Ark_LinearGradient& value) {
            auto gradientOpt = Converter::OptConvert<Gradient>(value);
            SliderModelStatic::SetTrackBackgroundColor(frameNode, gradientOpt);
        },
        [frameNode]() {
            SliderModelStatic::ResetTrackBackgroundColor(frameNode);
        }
    );
}
void SetSelectedColorImpl(Ark_NativePointer node,
                          const Opt_Union_ResourceColor_LinearGradient* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    Converter::VisitUnion(*value,
        [frameNode](const Ark_ResourceColor& value) {
            auto colorOpt = Converter::OptConvert<Color>(value);
            auto gradientOpt = colorOpt.has_value() ?
                std::optional<Gradient>{SliderModelNG::CreateSolidGradient(colorOpt.value())} : std::nullopt;
            SliderModelStatic::SetSelectColor(frameNode, gradientOpt, true);
        },
        [frameNode](const Ark_LinearGradient& value) {
            auto gradientOpt = Converter::OptConvert<Gradient>(value);
            SliderModelStatic::SetSelectColor(frameNode, gradientOpt);
        },
        [frameNode]() {
            SliderModelStatic::SetSelectColor(frameNode, std::nullopt, false);
        });
}
void SetShowSteps0Impl(Ark_NativePointer node,
                       const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<bool>(value);
    if (!convValue) {
        SliderModelStatic::ResetShowSteps(frameNode);
        return;
    }
    SliderModelNG::SetShowSteps(frameNode, *convValue);
}

void SetShowSteps1Impl(Ark_NativePointer node,
                       const Opt_Boolean* value,
                       const Opt_SliderShowStepOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<bool>(value);
    if (!convValue || !options) {
        SliderModelStatic::ResetShowSteps(frameNode);
        return;
    }
    auto convOptions = Converter::Convert<SliderModel::SliderShowStepOptions>(options->value);
    SliderModelNG::SetShowSteps(frameNode, *convValue, convOptions);
}
void SetTrackThicknessImpl(Ark_NativePointer node,
                           const Opt_Length* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertFromArkNumStrRes<Opt_Length, Ark_Number>(*value, DimensionUnit::VP);
    Validator::ValidatePositive(convValue);
    SliderModelStatic::SetThickness(frameNode, convValue);
}
void SetOnChangeImpl(Ark_NativePointer node,
                     const Opt_Callback_F64_SliderChangeMode_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        SliderModelNG::SetOnChange(frameNode, nullptr);
        return;
    }
    auto onChange = [arkCallback = CallbackHelper(*optValue)](float newValue, int32_t mode) {
        Ark_Float64 arkValue = Converter::ArkValue<Ark_Float64>(newValue);
        Ark_SliderChangeMode arkMode = Converter::ArkValue<Ark_SliderChangeMode>(
            static_cast<SliderModel::SliderChangeMode>(mode));
        arkCallback.Invoke(arkValue, arkMode);
    };
    SliderModelNG::SetOnChange(frameNode, std::move(onChange));
}
void SetBlockBorderColorImpl(Ark_NativePointer node,
                             const Opt_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<Color>(value);
    SliderModelStatic::SetBlockBorderColor(frameNode, convValue);
}
void SetBlockBorderWidthImpl(Ark_NativePointer node,
                             const Opt_Length* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertFromArkNumStrRes<Opt_Length, Ark_Number>(*value, DimensionUnit::VP);
    Validator::ValidateNonNegative(convValue);
    SliderModelStatic::SetBlockBorderWidth(frameNode, convValue);
}
void SetStepColorImpl(Ark_NativePointer node,
                      const Opt_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<Color>(value);
    SliderModelStatic::SetStepColor(frameNode, convValue);
}
void SetTrackBorderRadiusImpl(Ark_NativePointer node,
                              const Opt_Length* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertFromArkNumStrRes<Opt_Length, Ark_Number>(*value, DimensionUnit::VP);
    Validator::ValidateNonNegative(convValue);
    SliderModelStatic::SetTrackBorderRadius(frameNode, convValue);
}
void SetSelectedBorderRadiusImpl(Ark_NativePointer node,
                                 const Opt_Dimension* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<Dimension>(value);
    Validator::ValidateNonNegative(convValue);
    Validator::ValidateNonPercent(convValue);
    SliderModelStatic::SetSelectedBorderRadius(frameNode, convValue);
}
void SetBlockSizeImpl(Ark_NativePointer node,
                      const Opt_SizeOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<Converter::SliderBlockSizeOptions>(value)
        .value_or(Converter::SliderBlockSizeOptions{});
    SliderModelStatic::SetBlockSize(frameNode, convValue.width, convValue.height);
}
void SetBlockStyleImpl(Ark_NativePointer node, const Opt_SliderBlockStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<Converter::SliderBlockStyle>(value);
    if (convValue.has_value()) {
        SliderModelStatic::SetBlockType(frameNode, convValue.value().type);
        if (convValue.value().image.has_value()) {
            SliderModelNG::SetBlockImage(frameNode, convValue.value().image->GetSrc(),
                convValue.value().image->GetBundleName(), convValue.value().image->GetModuleName());
        } else if (convValue.value().shape.has_value()) {
            SliderModelNG::SetBlockShape(frameNode, convValue.value().shape.value());
        } else {
            SliderModelNG::ResetBlockImage(frameNode);
            SliderModelNG::ResetBlockShape(frameNode);
        }
    } else {
        SliderModelStatic::SetBlockType(frameNode, std::nullopt);
        SliderModelNG::ResetBlockImage(frameNode);
    }
}
void SetStepSizeImpl(Ark_NativePointer node,
                     const Opt_Length* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertFromArkNumStrRes<Opt_Length, Ark_Number>(*value, DimensionUnit::VP);
    Validator::ValidateNonNegative(convValue);
    SliderModelStatic::SetStepSize(frameNode, convValue);
}
void SetSliderInteractionModeImpl(Ark_NativePointer node,
                                  const Opt_SliderInteraction* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<SliderModel::SliderInteraction>(value);
    SliderModelStatic::SetSliderInteractionMode(frameNode, convValue);
}
void SetMinResponsiveDistanceImpl(Ark_NativePointer node,
                                  const Opt_Float64* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<float>(value);
    Validator::ValidateNonNegative(convValue);
    SliderModelStatic::SetMinResponsiveDistance(frameNode, convValue);
}
void SetSlideRangeImpl(Ark_NativePointer node,
                       const Opt_SlideRange* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<Converter::SliderRange>(value).value_or(Converter::SliderRange{});
    SliderModelStatic::SetValidSlideRange(frameNode, convValue.from, convValue.to);
}
void SetDigitalCrownSensitivityImpl(Ark_NativePointer node,
                                    const Opt_CrownSensitivity* value)
{
#ifdef SUPPORT_DIGITAL_CROWN
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<CrownSensitivity>(value);
    SliderModelStatic::SetDigitalCrownSensitivity(frameNode, convValue);
#endif
}
void SetEnableHapticFeedbackImpl(Ark_NativePointer node,
                                 const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<bool>(value);
    if (!convValue.has_value()) {
        SliderModelNG::SetEnableHapticFeedback(frameNode, true);
        return;
    }
    SliderModelNG::SetEnableHapticFeedback(frameNode, *convValue);
}
void SetShowTipsImpl(Ark_NativePointer node,
                     const Opt_Boolean* value,
                     const Opt_ResourceStr* content)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<bool>(value);
    if (!convValue) {
        SliderModelStatic::ResetShowTips(frameNode);
        return;
    }
    auto convContent = Converter::OptConvertPtr<std::string>(content);
    SliderModelNG::SetShowTips(frameNode, *convValue, convContent);
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
        SliderAttributeModifier::SetShowSteps0Impl,
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
        SliderAttributeModifier::SetSlideRangeImpl,
        SliderAttributeModifier::SetDigitalCrownSensitivityImpl,
        SliderAttributeModifier::SetEnableHapticFeedbackImpl,
        SliderAttributeModifier::SetShowSteps1Impl,
        SliderAttributeModifier::SetShowTipsImpl,
    };
    return &ArkUISliderModifierImpl;
}

}
