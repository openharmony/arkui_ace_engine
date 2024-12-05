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

#include "core/components_ng/pattern/gauge/gauge_model_ng.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/validators.h"

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
    LOGE("OHOS::Ace::NG::Converter::Convert, Ark_LinearGradient to ColorStopArray is not implemented yet\n");
    return ColorStopArray();
}

struct GaugeColors {
    std::vector<ColorStopArray> gradient;
    std::vector<float> weights;
    GaugeType type;

    explicit GaugeColors(GaugeType t) : type(t) {}
};

template<>
void AssignTo(std::optional<GaugeColors>& dst, const Ark_ResourceColor& src)
{
    auto colorStop = Convert<ColorStopArray>(src);
    if (!colorStop.empty()) {
        if (!dst) {
            dst = GaugeColors(GaugeType::TYPE_CIRCULAR_MONOCHROME);
        }
        dst->gradient.emplace_back(colorStop);
    }
}

template<>
void AssignTo(std::optional<GaugeColors>& dst, const Ark_LinearGradient& src)
{
    auto colorStop = Convert<ColorStopArray>(src);
    if (!colorStop.empty()) {
        if (!dst) {
            dst = GaugeColors(GaugeType::TYPE_CIRCULAR_SINGLE_SEGMENT_GRADIENT);
        }
        dst->gradient.emplace_back(colorStop);
    }
}

template<>
void AssignCast(std::optional<GaugeColors>& dst, const Ark_Tuple_Union_ResourceColor_LinearGradient_Number& src)
{
    AssignTo(dst, src.value0);
    if (dst && dst->weights.size() < dst->gradient.size()) {
        dst->weights.emplace_back(Convert<float>(src.value1));
    }
}

template<>
void AssignCast(std::optional<GaugeColors>& dst, const Array_Tuple_Union_ResourceColor_LinearGradient_Number& src)
{
    const auto length = std::min(Convert<int32_t>(src.length), COLORS_MAX_COUNT);
    for (int i = 0; i < length; ++i) {
        AssignTo(dst, src.array[i]);
    }
    if (dst) {
        dst->type = GaugeType::TYPE_CIRCULAR_MULTI_SEGMENT_GRADIENT;
    }
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
Ark_NativePointer ConstructImpl()
{
    return 0;
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
    GaugeModelNG::SetValue(frameNode, value);
    GaugeModelNG::SetMin(frameNode, min);
    GaugeModelNG::SetMax(frameNode, max);
    GaugeModelNG::SetIsShowLimitValue(frameNode, min || max);
}
} // GaugeInterfaceModifier
namespace GaugeAttributeModifier {
void ValueImpl(Ark_NativePointer node,
               const Ark_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    GaugeModelNG::SetValue(frameNode, Converter::OptConvert<float>(*value));
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
    auto gaugeColors = Converter::OptConvert<Converter::GaugeColors>(*value);
    if (gaugeColors) {
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
    GaugeModelNG::SetGaugeStrokeWidth(frameNode, strokeWidth);
}
void DescriptionImpl(Ark_NativePointer node,
                     const Callback_Any* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //GaugeModelNG::SetDescription(frameNode, convValue);
}
void TrackShadowImpl(Ark_NativePointer node,
                     const Ark_GaugeShadowOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    const auto shadow = value ? Converter::Convert<GaugeShadowOptions>(*value)
        : GaugeShadowOptions { .isShadowVisible = false };
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
        GaugeModelNG::SetIndicatorSpace(frameNode, indicator.space);
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
    GaugeModelNG::SetPrivacySensitive(frameNode, sensitive);
}
void ContentModifierImpl(Ark_NativePointer node,
                         const Ark_CustomObject* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //GaugeModelNG::SetContentModifier(frameNode, convValue);
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
