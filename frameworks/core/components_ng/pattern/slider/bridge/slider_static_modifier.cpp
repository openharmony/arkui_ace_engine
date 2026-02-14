/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "core/common/container.h"
#include "core/common/dynamic_module_helper.h"
#include "core/components/slider/slider_theme.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/common_view/common_view_model_ng.h"
#include "core/components_ng/pattern/slider/bridge/slider_content_modifier_helper.h"
#include "core/components_ng/pattern/slider/slider_model_ng.h"
#include "core/components_ng/pattern/slider/slider_model_static.h"
#include "core/interfaces/native/common/api_impl.h"
#include "core/interfaces/native/implementation/color_metrics_linear_gradient_peer_impl.h"
#include "core/interfaces/native/implementation/frame_node_peer_impl.h"
#include "core/interfaces/native/utility/ace_engine_types.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/object_keeper.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/interfaces/native/utility/validators.h"

namespace OHOS::Ace::NG {
namespace {
std::optional<float> ProcessBindableValue(FrameNode* frameNode, const Opt_Union_F64_Bindable_F64& value)
{
    std::optional<float> result;
    Converter::VisitUnion(
        value, [&result](const Ark_Float64& src) { result = Converter::OptConvert<float>(src); },
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
    auto stepItemAccessibility = Converter::OptConvert<Map_F64_SliderStepItemAccessibility>(accessibilityOpt.value);
    if (!stepItemAccessibility) {
        return dst;
    }

    auto stepItemMap = stepItemAccessibility.value();
    auto mapSize = Converter::Convert<int32_t>(stepItemMap.size);
    if (mapSize <= 0 || !stepItemMap.keys || !stepItemMap.values) {
        return dst;
    }
    for (int32_t i = 0; i < mapSize; i++) {
        double step = Converter::Convert<double>(stepItemMap.keys[i]);
        uint32_t key;
        if ((step >= 0) && (NearZero(std::abs(step - std::floor(step)))) && (step <= INT32_MAX)) {
            key = static_cast<uint32_t>(step);
        } else {
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
        .from = Converter::OptConvert<float>(src.from), .to = Converter::OptConvert<float>(src.to)
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
        .width = Converter::OptConvertFromArkNumStrRes<Opt_Length, Ark_Float64>(src.width, DimensionUnit::VP),
        .height = Converter::OptConvertFromArkNumStrRes<Opt_Length, Ark_Float64>(src.height, DimensionUnit::VP)
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
ACE_FORCE_EXPORT SliderBlockStyle Convert(const Ark_SliderBlockStyle& src)
{
    const Opt_Union_CircleShape_EllipseShape_PathShape_RectShape* shape = &(src.shape);
    return { .type = Converter::OptConvert<SliderModel::BlockStyleType>(src.type),
        .image = Converter::OptConvert<ImageSourceInfo>(src.image),
        .shape = Converter::OptConvertPtr<RefPtr<BasicShape>>(shape) };
}

template<>
SliderPrefixOptions Convert(const Ark_SliderPrefixOptions& src)
{
    SliderPrefixOptions dst;
    dst.accessibilityText = Converter::OptConvert<std::string>(src.accessibilityText).value_or("");
    dst.accessibilityDescription = Converter::OptConvert<std::string>(src.accessibilityDescription).value_or("");
    dst.accessibilityLevel = Converter::OptConvert<std::string>(src.accessibilityLevel).value_or("auto");
    dst.accessibilityGroup = Converter::OptConvert<bool>(src.accessibilityGroup).value_or(false);
    return dst;
}

template<>
SliderSuffixOptions Convert(const Ark_SliderSuffixOptions& src)
{
    SliderSuffixOptions dst;
    dst.accessibilityText = Converter::OptConvert<std::string>(src.accessibilityText).value_or("");
    dst.accessibilityDescription = Converter::OptConvert<std::string>(src.accessibilityDescription).value_or("");
    dst.accessibilityLevel = Converter::OptConvert<std::string>(src.accessibilityLevel).value_or("auto");
    dst.accessibilityGroup = Converter::OptConvert<bool>(src.accessibilityGroup).value_or(false);
    return dst;
}

template<>
ACE_FORCE_EXPORT void AssignCast(std::optional<Gradient>& dst, const Ark_ColorMetricsLinearGradient& src)
{
    CHECK_NULL_VOID(src);
    CHECK_EQUAL_VOID(src->gradient.GetColors().empty(), true);
    dst = src->gradient;
}
} // namespace Converter
} // namespace OHOS::Ace::NG

namespace OHOS::Ace::NG::GeneratedModifier {
namespace SliderModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id, Ark_Int32 flags)
{
    auto frameNode = SliderModelNG::CreateFrameNode(id);
    CHECK_NULL_RETURN(frameNode, nullptr);
    frameNode->IncRefCount();
    return AceType::RawPtr(frameNode);
}
} // namespace SliderModifier
namespace SliderInterfaceModifier {
void SetSliderOptionsImpl(Ark_NativePointer node, const Opt_SliderOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
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
} // namespace SliderInterfaceModifier
namespace SliderAttributeModifier {
void SetBlockColorImpl(Ark_NativePointer node, const Opt_Union_ResourceColor_LinearGradient* value)
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

void SetTrackColorImpl(Ark_NativePointer node, const Opt_Union_ResourceColor_LinearGradient* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    Converter::VisitUnion(
        *value,
        [frameNode](const Ark_ResourceColor& value) {
            auto colorOpt = Converter::OptConvert<Color>(value);
            auto gradientOpt = colorOpt.has_value()
                                   ? std::optional<Gradient> { SliderModelNG::CreateSolidGradient(colorOpt.value()) }
                                   : std::nullopt;
            SliderModelStatic::SetTrackBackgroundColor(frameNode, gradientOpt, true);
        },
        [frameNode](const Ark_LinearGradient& value) {
            auto gradientOpt = Converter::OptConvert<Gradient>(value);
            SliderModelStatic::SetTrackBackgroundColor(frameNode, gradientOpt);
        },
        [frameNode]() { SliderModelStatic::ResetTrackBackgroundColor(frameNode); });
}
void SetSelectedColorImpl(Ark_NativePointer node, const Opt_Union_ResourceColor_LinearGradient* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    Converter::VisitUnion(
        *value,
        [frameNode](const Ark_ResourceColor& value) {
            auto colorOpt = Converter::OptConvert<Color>(value);
            auto gradientOpt = colorOpt.has_value()
                                   ? std::optional<Gradient> { SliderModelNG::CreateSolidGradient(colorOpt.value()) }
                                   : std::nullopt;
            SliderModelStatic::SetSelectColor(frameNode, gradientOpt, true);
        },
        [frameNode](const Ark_LinearGradient& value) {
            auto gradientOpt = Converter::OptConvert<Gradient>(value);
            SliderModelStatic::SetSelectColor(frameNode, gradientOpt);
        },
        [frameNode]() { SliderModelStatic::SetSelectColor(frameNode, std::nullopt, false); });
}
void SetShowSteps0Impl(Ark_NativePointer node, const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<bool>(value);
    if (!convValue) {
        SliderModelStatic::ResetShowSteps(frameNode);
        return;
    }
    SliderModelNG::SetShowSteps(frameNode, *convValue);
}

void SetShowSteps1Impl(Ark_NativePointer node, const Opt_Boolean* value, const Opt_SliderShowStepOptions* options)
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
void SetTrackThicknessImpl(Ark_NativePointer node, const Opt_Length* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertFromArkNumStrRes<Opt_Length, Ark_Float64>(*value, DimensionUnit::VP);
    Validator::ValidatePositive(convValue);
    SliderModelStatic::SetThickness(frameNode, convValue);
}
void SetOnChangeImpl(Ark_NativePointer node, const Opt_Callback_F64_SliderChangeMode_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        SliderModelNG::SetOnChange(frameNode, nullptr);
        return;
    }
    auto onChange = [arkCallback = CallbackHelper(*optValue)](float newValue, int32_t mode) {
        Ark_Float64 arkValue = Converter::ArkValue<Ark_Float64>(newValue);
        Ark_SliderChangeMode arkMode =
            Converter::ArkValue<Ark_SliderChangeMode>(static_cast<SliderModel::SliderChangeMode>(mode));
        arkCallback.Invoke(arkValue, arkMode);
    };
    SliderModelNG::SetOnChange(frameNode, std::move(onChange));
}
void SetBlockBorderColorImpl(Ark_NativePointer node, const Opt_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<Color>(value);
    SliderModelStatic::SetBlockBorderColor(frameNode, convValue);
}
void SetBlockBorderWidthImpl(Ark_NativePointer node, const Opt_Length* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertFromArkNumStrRes<Opt_Length, Ark_Float64>(*value, DimensionUnit::VP);
    Validator::ValidateNonNegative(convValue);
    SliderModelStatic::SetBlockBorderWidth(frameNode, convValue);
}
void SetStepColorImpl(Ark_NativePointer node, const Opt_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<Color>(value);
    SliderModelStatic::SetStepColor(frameNode, convValue);
}
void SetTrackBorderRadiusImpl(Ark_NativePointer node, const Opt_Length* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertFromArkNumStrRes<Opt_Length, Ark_Float64>(*value, DimensionUnit::VP);
    Validator::ValidateNonNegative(convValue);
    SliderModelStatic::SetTrackBorderRadius(frameNode, convValue);
}
void SetSelectedBorderRadiusImpl(Ark_NativePointer node, const Opt_Dimension* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<Dimension>(value);
    Validator::ValidateNonNegative(convValue);
    Validator::ValidateNonPercent(convValue);
    SliderModelStatic::SetSelectedBorderRadius(frameNode, convValue);
}
void SetBlockSizeImpl(Ark_NativePointer node, const Opt_SizeOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<Converter::SliderBlockSizeOptions>(value).value_or(
        Converter::SliderBlockSizeOptions {});
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
void SetStepSizeImpl(Ark_NativePointer node, const Opt_Length* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertFromArkNumStrRes<Opt_Length, Ark_Float64>(*value, DimensionUnit::VP);
    Validator::ValidateNonNegative(convValue);
    SliderModelStatic::SetStepSize(frameNode, convValue);
}
void SetSliderInteractionModeImpl(Ark_NativePointer node, const Opt_SliderInteraction* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<SliderModel::SliderInteraction>(value);
    SliderModelStatic::SetSliderInteractionMode(frameNode, convValue);
}
void SetMinResponsiveDistanceImpl(Ark_NativePointer node, const Opt_Float64* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<float>(value);
    Validator::ValidateNonNegative(convValue);
    SliderModelStatic::SetMinResponsiveDistance(frameNode, convValue);
}
void SetSlideRangeImpl(Ark_NativePointer node, const Opt_SlideRange* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<Converter::SliderRange>(value).value_or(Converter::SliderRange {});
    SliderModelStatic::SetValidSlideRange(frameNode, convValue.from, convValue.to);
}
void SetDigitalCrownSensitivityImpl(Ark_NativePointer node, const Opt_CrownSensitivity* value)
{
#ifdef SUPPORT_DIGITAL_CROWN
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<CrownSensitivity>(value);
    SliderModelStatic::SetDigitalCrownSensitivity(frameNode, convValue);
#endif
}
void SetEnableHapticFeedbackImpl(Ark_NativePointer node, const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<bool>(value);
    if (!convValue.has_value()) {
        SliderModelNG::SetEnableHapticFeedback(frameNode, true);
        return;
    }
    SliderModelNG::SetEnableHapticFeedback(frameNode, *convValue);
}
void SetTrackColorMetricsImpl(Ark_NativePointer node, const Opt_ColorMetricsLinearGradient* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto gradientOpt = Converter::OptConvert<Gradient>(*value);
    if (gradientOpt.has_value()) {
        SliderModelStatic::SetTrackBackgroundColor(frameNode, gradientOpt.value(), false);
    } else {
        SliderModelStatic::ResetTrackBackgroundColor(frameNode);
    }
}
void SetShowTipsImpl(Ark_NativePointer node, const Opt_Boolean* value, const Opt_ResourceStr* content)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<bool>(value);
    if (!convValue) {
        SliderModelStatic::ResetShowTips(frameNode);
        return;
    }
    auto convContent = Converter::OptConvertPtr<std::string>(content);
    SliderModelNG::SetShowTips(frameNode, *convValue, convContent);
}

Gradient CreateSolidGradient(Ark_ResourceColor* color)
{
    auto colorOpt = Converter::OptConvertPtr<Color>(color);
    if (colorOpt.has_value()) {
        return SliderModelNG::CreateSolidGradient(colorOpt.value());
    }
    return {};
}

void ContentModifierSliderImpl(
    Ark_NativePointer node, const Ark_Object* contentModifier, const SliderModifierBuilder* builder)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto objectKeeper = std::make_shared<ObjectKeeper>(*contentModifier);
    auto builderFunc = [arkBuilder = CallbackHelper(*builder), node, frameNode, objectKeeper](
                           const SliderConfiguration& config) -> RefPtr<FrameNode> {
        Ark_ContentModifier contentModifier = (*objectKeeper).get();
        Ark_SliderConfiguration arkConfig;
        arkConfig.contentModifier = contentModifier;
        arkConfig.value = Converter::ArkValue<Ark_Float64>(config.value_);
        arkConfig.min = Converter::ArkValue<Ark_Float64>(config.min_);
        arkConfig.max = Converter::ArkValue<Ark_Float64>(config.max_);
        arkConfig.enabled = Converter::ArkValue<Ark_Boolean>(config.enabled_);
        arkConfig.step = Converter::ArkValue<Ark_Float64>(config.step_);
        auto triggerCallback = CallbackKeeper::Claim<SliderTriggerChangeCallback>(
            [frameNode](Ark_Float64 value, Ark_SliderChangeMode mode) {
                SliderModelNG::SetChangeValue(frameNode, Converter::Convert<double>(value), mode);
            });
        arkConfig.triggerChange = triggerCallback.ArkValue();

        auto boxNode = GeneratedApiImpl::GetContentNode(node);
        if (boxNode == nullptr) {
            boxNode = CommonViewModelNG::CreateFrameNode(ElementRegister::GetInstance()->MakeUniqueId());
            GeneratedApiImpl::SetContentNode(node, boxNode);
        }
        arkBuilder.BuildAsync([boxNode](const RefPtr<UINode>& uiNode) mutable {
            auto old = boxNode->GetChildAtIndex(0);
            if (old != nullptr) {
                boxNode->RemoveChildSilently(old);
            }
            boxNode->AddChild(uiNode);
            boxNode->MarkNeedFrameFlushDirty(PROPERTY_UPDATE_MEASURE);
            }, node, arkConfig);
        return boxNode;
    };
    SliderModelNG::SetBuilderFunc(frameNode, std::move(builderFunc));
}

void ResetContentModifierSliderImpl(Ark_NativePointer node)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SliderModelNG::SetBuilderFunc(frameNode, nullptr);
}
} // namespace SliderAttributeModifier

namespace SliderExtenderAccessor {
void SetPrefixImpl(Ark_NativePointer node, Ark_NativePointer prefixNode, const Opt_SliderPrefixOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto* prefixNodePeer = reinterpret_cast<FrameNodePeer*>(prefixNode);
    CHECK_NULL_VOID(prefixNodePeer);
    auto prefixNodeRef = FrameNodePeer::GetFrameNodeByPeer(prefixNodePeer);
    SliderPrefixOptions prefixOptions =
        options ? Converter::Convert<SliderPrefixOptions>(options->value) : SliderPrefixOptions();
    SliderModelNG::SetPrefix(frameNode, prefixNodeRef, prefixOptions);
}
void SetSuffixImpl(Ark_NativePointer node, Ark_NativePointer suffixNode, const Opt_SliderSuffixOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto* suffixNodePeer = reinterpret_cast<FrameNodePeer*>(suffixNode);
    CHECK_NULL_VOID(suffixNodePeer);
    auto suffixNodeRef = FrameNodePeer::GetFrameNodeByPeer(suffixNodePeer);
    SliderSuffixOptions suffixOptions =
        options ? Converter::Convert<SliderSuffixOptions>(options->value) : SliderSuffixOptions();
    SliderModelNG::SetSuffix(frameNode, suffixNodeRef, suffixOptions);
}
} // namespace SliderExtenderAccessor

const GENERATED_ArkUISliderModifier* GetSliderStaticModifier()
{
    static const GENERATED_ArkUISliderModifier ArkUISliderModifierImpl = {
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
        SliderAttributeModifier::SetTrackColorMetricsImpl,
        SliderAttributeModifier::SetShowSteps1Impl,
        SliderAttributeModifier::SetShowTipsImpl,
    };

    return &ArkUISliderModifierImpl;
}

const GENERATED_ArkUISliderExtenderAccessor* GetSliderExtenderAccessorModifier()
{
    static const GENERATED_ArkUISliderExtenderAccessor ArkUISliderExtenderAccessorImpl = {
        SliderExtenderAccessor::SetPrefixImpl,
        SliderExtenderAccessor::SetSuffixImpl,
    };

    return &ArkUISliderExtenderAccessorImpl;
}

const GENERATED_ArkUISliderContentModifier* GetSliderStaticContentModifier()
{
    static const GENERATED_ArkUISliderContentModifier ArkUISliderStaticContentModifierImpl {
        SliderAttributeModifier::ContentModifierSliderImpl,
        SliderAttributeModifier::ResetContentModifierSliderImpl,
    };
    return &ArkUISliderStaticContentModifierImpl;
}
} // namespace OHOS::Ace::NG::GeneratedModifier