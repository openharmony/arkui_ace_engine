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

#include "core/components_ng/pattern/gauge/gauge_model_ng.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/validators.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/implementation/linear_gradient_peer.h"

namespace OHOS::Ace::NG {
namespace {
void SortColorStopOffset(std::vector<ColorStopArray>& colors)
{
    for (auto& colorStopArray : colors) {
        std::sort(colorStopArray.begin(), colorStopArray.end(),
            [](const std::pair<Color, Dimension>& left, const std::pair<Color, Dimension>& right) {
                return left.second.Value() < right.second.Value();
            });

        auto iter = std::unique(colorStopArray.begin(), colorStopArray.end(),
            [](const std::pair<Color, Dimension>& left, const std::pair<Color, Dimension>& right) {
                return left.second.Value() == right.second.Value();
            });
        colorStopArray.erase(iter, colorStopArray.end());
    }
}
} // namespace
} // namespace OHOS::Ace::NG

namespace OHOS::Ace::NG::Converter {
template<>
ColorStopArray Convert(const Ark_ResourceColor& src)
{
    auto colorStop = ColorStopArray();
    const auto color = OptConvert<Color>(src);
    if (color) {
        colorStop.emplace_back(std::make_pair(*color, Dimension(0.0)));
    }
    return colorStop;
}

template<>
ColorStopArray Convert(const Ark_LinearGradient& src)
{
    ColorStopArray result;
    CHECK_NULL_RETURN(src, result);
    result.reserve(src->colorStops.size());
    for (const auto& color : src->colorStops) {
        if (color.first.has_value()) {
            result.emplace_back(std::make_pair(color.first.value(), color.second));
        }
    }
    return result;
}

using ColorWithWeight = std::tuple<ColorStopArray, float>;
template<>
ColorWithWeight Convert(const Ark_Tuple_Union_ResourceColor_LinearGradient_Number& src)
{
    ColorStopArray colors;
    Converter::VisitUnion(src.value0,
        [&colors](const auto& value) {
            colors = Convert<ColorStopArray>(value);
        },
        []() {}
    );
    const auto weight = Convert<float>(src.value1);
    return {colors, weight};
}

template<>
GaugeShadowOptions Convert(const Ark_GaugeShadowOptions& src)
{
    auto shadow = GaugeShadowOptions();
    auto radius = OptConvert<float>(src.radius);
    Validator::ValidatePositive(radius);
    if (radius) {
        shadow.radius = *radius;
    }
    const auto offsetX = OptConvert<float>(src.offsetX);
    if (offsetX) {
        shadow.offsetX = *offsetX;
    }
    const auto offsetY = OptConvert<float>(src.offsetY);
    if (offsetY) {
        shadow.offsetY = *offsetY;
    }
    return shadow;
}

struct GaugeIndicatorOptions {
    std::optional<ImageSourceInfo> icon;
    std::optional<Dimension> space;
};

template<>
GaugeIndicatorOptions Convert(const Ark_GaugeIndicatorOptions& src)
{
    return {
        .icon = OptConvert<ImageSourceInfo>(src.icon),
        .space = OptConvert<Dimension>(src.space)
    };
}
} // namespace OHOS::Ace::NG::Converter

namespace OHOS::Ace::NG::GeneratedModifier {
namespace GaugeModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                Ark_Int32 flags)
{
    return nullptr;
}
} // GaugeModifier
namespace GaugeInterfaceModifier {
void SetGaugeOptionsImpl(Ark_NativePointer node,
                         const Ark_GaugeOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(options);
    auto min = Converter::OptConvert<float>(options->min);
    auto max = Converter::OptConvert<float>(options->max);
    if (min && max && LessNotEqual(*max, *min)) {
        min.reset();
        max.reset();
    }
    auto value = Converter::OptConvert<float>(options->value);
    if (value && ((min && LessNotEqual(*value, *min)) || (max && GreatNotEqual(*value, *max)))) {
        value = min;
    }
    // GaugeModelNG::SetValue(frameNode, value);
    // GaugeModelNG::SetMin(frameNode, min);
    // GaugeModelNG::SetMax(frameNode, max);
    // GaugeModelNG::SetIsShowLimitValue(frameNode, min || max);
}
} // GaugeInterfaceModifier
namespace GaugeAttributeModifier {
void ValueImpl(Ark_NativePointer node,
               const Ark_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    // GaugeModelNG::SetValue(frameNode, Converter::OptConvert<float>(*value));
}
void StartAngleImpl(Ark_NativePointer node,
                    const Ark_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    GaugeModelNG::SetStartAngle(frameNode, Converter::Convert<float>(*value));
}
void EndAngleImpl(Ark_NativePointer node,
                  const Ark_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    GaugeModelNG::SetEndAngle(frameNode, Converter::Convert<float>(*value));
}
void ColorsImpl(Ark_NativePointer node,
                const Ark_Type_GaugeAttribute_colors_colors* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    struct GaugeColors {
        std::vector<ColorStopArray> gradient;
        std::vector<float> weights;
        GaugeType type;
    };
    std::optional<GaugeColors> gaugeColors;
    Converter::VisitUnion(*value,
        [&gaugeColors](const Ark_ResourceColor& color) {
            gaugeColors = GaugeColors {
                .gradient = std::vector<ColorStopArray> {Converter::Convert<ColorStopArray>(color)},
                .type = GaugeType::TYPE_CIRCULAR_MONOCHROME
            };
        },
        [&gaugeColors](const Ark_LinearGradient& color) {
            gaugeColors = GaugeColors {
                .gradient = std::vector<ColorStopArray> {Converter::Convert<ColorStopArray>(color)},
                .type = GaugeType::TYPE_CIRCULAR_SINGLE_SEGMENT_GRADIENT
            };
        },
        [&gaugeColors](const Array_Tuple_Union_ResourceColor_LinearGradient_Number& colorsArray) {
            gaugeColors = GaugeColors {
                .type = GaugeType::TYPE_CIRCULAR_MULTI_SEGMENT_GRADIENT
            };
            const auto colors = Converter::Convert<std::vector<Converter::ColorWithWeight>>(colorsArray);
            const auto colorsSize = std::min(static_cast<int32_t>(colors.size()), COLORS_MAX_COUNT);
            gaugeColors->gradient.reserve(colorsSize);
            gaugeColors->weights.reserve(colorsSize);
            for (int32_t i = 0; i < colorsSize; ++i) {
                const auto [gradient, weight] = colors[i];
                gaugeColors->gradient.emplace_back(gradient);
                gaugeColors->weights.emplace_back(weight);
            }
        },
        []() {
            LOGE("Arkoala. Converter::AssignCast for Ark_Type_GaugeAttribute_colors_colors. Unexpected type.");
        });
    if (gaugeColors.has_value()) {
        SortColorStopOffset(gaugeColors->gradient);
        GaugeModelNG::SetGradientColors(frameNode, gaugeColors->gradient, gaugeColors->weights, gaugeColors->type);
    } else {
        GaugeModelNG::ResetGradientColors(frameNode);
    }
}
void StrokeWidthImpl(Ark_NativePointer node,
                     const Ark_Length* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto strokeWidth = Converter::OptConvert<Dimension>(*value);
    Validator::ValidateNonNegative(strokeWidth);
    Validator::ValidateNonPercent(strokeWidth);
    // GaugeModelNG::SetGaugeStrokeWidth(frameNode, strokeWidth);
}
void DescriptionImpl(Ark_NativePointer node,
                     const CustomNodeBuilder* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto builderNode = CallbackHelper(*value).BuildSync(node);
    // GaugeModelNG::SetDescription(frameNode, builderNode);
}
void TrackShadowImpl(Ark_NativePointer node,
                     const Ark_GaugeShadowOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    GaugeShadowOptions gaugeShadowOptions;
    gaugeShadowOptions.isShadowVisible = false;
    const auto shadow = value ? Converter::Convert<GaugeShadowOptions>(*value)
        : gaugeShadowOptions;
    GaugeModelNG::SetShadowOptions(frameNode, shadow);
}
void IndicatorImpl(Ark_NativePointer node,
                   const Ark_GaugeIndicatorOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    if (value) {
        auto indicator = Converter::Convert<Converter::GaugeIndicatorOptions>(*value);
        GaugeModelNG::SetIsShowIndicator(frameNode, true);
        if (indicator.icon) {
            GaugeModelNG::SetIndicatorIconPath(frameNode,
                indicator.icon->GetSrc(), indicator.icon->GetBundleName(), indicator.icon->GetModuleName());
        } else {
            GaugeModelNG::ResetIndicatorIconPath(frameNode);
        }
        Validator::ValidateNonNegative(indicator.space);
        Validator::ValidateNonPercent(indicator.space);
        // GaugeModelNG::SetIndicatorSpace(frameNode, indicator.space);
    } else {
        GaugeModelNG::SetIsShowIndicator(frameNode, false);
    }
}
void PrivacySensitiveImpl(Ark_NativePointer node,
                          const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    const auto sensitive = value ? Converter::OptConvert<bool>(*value) : std::nullopt;
    // GaugeModelNG::SetPrivacySensitive(frameNode, sensitive);
}
void ContentModifierImpl(Ark_NativePointer node,
                         const Ark_CustomObject* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
}
} // GaugeAttributeModifier
const GENERATED_ArkUIGaugeModifier* GetGaugeModifier()
{
    static const GENERATED_ArkUIGaugeModifier ArkUIGaugeModifierImpl {
        GaugeModifier::ConstructImpl,
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
