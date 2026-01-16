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

#include "core/components_ng/pattern/common_view/common_view_model_ng.h"
#include "core/components_ng/pattern/gauge/bridge/content_modifier_helper.h"
#include "core/components_ng/pattern/gauge/gauge_model_ng.h"
#include "core/components_ng/pattern/gauge/gauge_model_static.h"
#include "core/interfaces/native/common/api_impl.h"
#include "core/interfaces/native/implementation/linear_gradient_peer.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/object_keeper.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/interfaces/native/utility/validators.h"

namespace OHOS::Ace::NG {
namespace {
using LinearGradientColorSteps = GaugeModelStatic::LinearGradientColorSteps;

constexpr double DEFAULT_GAUGE_VALUE = 0;
constexpr double DEFAULT_GAUGE_MIN = 0;
constexpr double DEFAULT_GAUGE_MAX = 100;
constexpr double DEFAULT_GAUGE_STARTANGLE = 0;
constexpr double DEFAULT_GAUGE_ENDANGLE = 360;
void SortColorStopOffset(std::vector<LinearGradientColorSteps>& colors)
{
    for (auto& colorStopArray : colors) {
        std::sort(colorStopArray.begin(), colorStopArray.end(),
            [](const std::pair<std::optional<Color>, Dimension>& left,
                const std::pair<std::optional<Color>, Dimension>& right) {
                return left.second.Value() < right.second.Value();
            });

        auto iter = std::unique(colorStopArray.begin(), colorStopArray.end(),
            [](const std::pair<std::optional<Color>, Dimension>& left,
                const std::pair<std::optional<Color>, Dimension>& right) {
                return left.second.Value() == right.second.Value();
            });
        colorStopArray.erase(iter, colorStopArray.end());
    }
}
} // namespace
} // namespace OHOS::Ace::NG

namespace OHOS::Ace::NG::Converter {
template<>
LinearGradientColorSteps Convert(const Ark_ResourceColor& src)
{
    auto colorStop = LinearGradientColorSteps();
    const auto color = OptConvert<Color>(src);
    colorStop.emplace_back(std::make_pair(color, Dimension(0.0)));
    return colorStop;
}

template<>
LinearGradientColorSteps Convert(const Ark_LinearGradient& src)
{
    CHECK_NULL_RETURN(src, {});
    return src->colorStops;
}

using ColorWithWeight = std::tuple<LinearGradientColorSteps, float>;
template<>
ColorWithWeight Convert(const Ark_Tuple_Union_ResourceColor_LinearGradient_F64& src)
{
    LinearGradientColorSteps colors;
    Converter::VisitUnion(
        src.value0, [&colors](const auto& value) { colors = Convert<LinearGradientColorSteps>(value); }, []() {});
    const auto weight = Convert<float>(src.value1);
    return { colors, weight };
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
    return { .icon = OptConvert<ImageSourceInfo>(src.icon), .space = OptConvert<Dimension>(src.space) };
}
} // namespace OHOS::Ace::NG::Converter

namespace OHOS::Ace::NG::GeneratedModifier {
namespace GaugeModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id, Ark_Int32 flags)
{
    auto frameNode = GaugeModelStatic::CreateFrameNode(id);
    CHECK_NULL_RETURN(frameNode, nullptr);
    frameNode->IncRefCount();
    return AceType::RawPtr(frameNode);
}
} // namespace GaugeModifier
namespace GaugeInterfaceModifier {
void SetGaugeOptionsImpl(Ark_NativePointer node, const Ark_GaugeOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(options);
    auto min = Converter::OptConvert<float>(options->min);
    auto max = Converter::OptConvert<float>(options->max);
    if (!min) {
        min = DEFAULT_GAUGE_MIN;
    }
    if (!max) {
        max = DEFAULT_GAUGE_MAX;
    }
    if (LessNotEqual(*max, *min)) {
        min = DEFAULT_GAUGE_MIN;
        max = DEFAULT_GAUGE_MAX;
    }
    auto value = Converter::OptConvert<float>(options->value);
    if (!value) {
        value = DEFAULT_GAUGE_VALUE;
    }
    if (LessNotEqual(*value, *min) || GreatNotEqual(*value, *max)) {
        value = min;
    }
    GaugeModelStatic::SetValue(frameNode, value);
    GaugeModelStatic::SetMin(frameNode, min);
    GaugeModelStatic::SetMax(frameNode, max);
    GaugeModelStatic::SetIsShowLimitValue(frameNode, min || max);
}
} // namespace GaugeInterfaceModifier
namespace GaugeAttributeModifier {
void SetValueImpl(Ark_NativePointer node, const Opt_Float64* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<float>(value);
    if (!convValue) {
        GaugeModelNG::SetValue(frameNode, DEFAULT_GAUGE_VALUE);
        return;
    }
    GaugeModelStatic::SetValue(frameNode, convValue);
}
void SetStartAngleImpl(Ark_NativePointer node, const Opt_Float64* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<float>(value);
    if (!convValue) {
        GaugeModelNG::SetStartAngle(frameNode, DEFAULT_GAUGE_STARTANGLE);
        return;
    }
    GaugeModelNG::SetStartAngle(frameNode, *convValue);
}
void SetEndAngleImpl(Ark_NativePointer node, const Opt_Float64* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<float>(value);
    if (!convValue) {
        GaugeModelNG::SetEndAngle(frameNode, DEFAULT_GAUGE_ENDANGLE);
        return;
    }
    GaugeModelNG::SetEndAngle(frameNode, *convValue);
}
void SetColorsImpl(Ark_NativePointer node,
    const Opt_Union_ResourceColor_LinearGradient_Array_Tuple_Union_ResourceColor_LinearGradient_F64* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    struct GaugeColors {
        std::vector<LinearGradientColorSteps> gradient;
        std::vector<float> weights;
        GaugeType type;
    };
    std::optional<GaugeColors> gaugeColors;
    Converter::VisitUnion(
        *value,
        [&gaugeColors](const Ark_ResourceColor& color) {
            gaugeColors = GaugeColors { .gradient = { Converter::Convert<LinearGradientColorSteps>(color) },
                .type = GaugeType::TYPE_CIRCULAR_MONOCHROME };
        },
        [&gaugeColors](const Ark_LinearGradient& color) {
            gaugeColors = GaugeColors { .gradient = { Converter::Convert<LinearGradientColorSteps>(color) },
                .type = GaugeType::TYPE_CIRCULAR_SINGLE_SEGMENT_GRADIENT };
        },
        [&gaugeColors](const Array_Tuple_Union_ResourceColor_LinearGradient_F64& colorsArray) {
            const auto colors = Converter::Convert<std::vector<Converter::ColorWithWeight>>(colorsArray);
            const auto colorsSize = std::min(static_cast<int32_t>(colors.size()), COLORS_MAX_COUNT);
            if (colorsSize > 0) {
                gaugeColors = GaugeColors { .type = GaugeType::TYPE_CIRCULAR_MULTI_SEGMENT_GRADIENT };
                gaugeColors->gradient.reserve(colorsSize);
                gaugeColors->weights.reserve(colorsSize);
                for (int32_t i = 0; i < colorsSize; ++i) {
                    const auto [gradient, weight] = colors[i];
                    gaugeColors->gradient.emplace_back(gradient);
                    gaugeColors->weights.emplace_back(weight);
                }
            }
        },
        []() {});
    if (gaugeColors.has_value()) {
        SortColorStopOffset(gaugeColors->gradient);
        GaugeModelStatic::SetGradientColors(frameNode, gaugeColors->gradient, gaugeColors->weights, gaugeColors->type);
    } else {
        GaugeModelNG::ResetGradientColors(frameNode);
    }
}
void SetStrokeWidthImpl(Ark_NativePointer node, const Opt_Length* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto strokeWidth = Converter::OptConvertPtr<Dimension>(value);
    Validator::ValidateNonPercent(strokeWidth);
    GaugeModelStatic::SetGaugeStrokeWidth(frameNode, strokeWidth);
}
void SetPrivacySensitiveImpl(Ark_NativePointer node, const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    const auto sensitive = Converter::OptConvertPtr<bool>(value);
    GaugeModelStatic::SetPrivacySensitive(frameNode, sensitive);
}
} // namespace GaugeAttributeModifier

void ContentModifierGaugeImpl(
    Ark_NativePointer node, const Ark_Object* contentModifier, const GaugeModifierBuilder* builder)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto objectKeeper = std::make_shared<ObjectKeeper>(*contentModifier);
    auto builderFunc = [arkBuilder = CallbackHelper(*builder), node, frameNode, objectKeeper](
                           GaugeConfiguration config) -> RefPtr<FrameNode> {
        Ark_ContentModifier contentModifier = (*objectKeeper).get();
        Ark_GaugeConfiguration arkConfig;
        arkConfig.contentModifier = contentModifier;
        arkConfig.enabled = Converter::ArkValue<Ark_Boolean>(config.enabled_);
        arkConfig.max = Converter::ArkValue<Ark_Float64>(config.max_);
        arkConfig.min = Converter::ArkValue<Ark_Float64>(config.min_);
        arkConfig.value = Converter::ArkValue<Ark_Float64>(config.value_);
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
    GaugeModelNG::SetBuilderFunc(frameNode, std::move(builderFunc));
}
void ResetContentModifierGaugeImpl(Ark_NativePointer node)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    GaugeModelNG::SetBuilderFunc(frameNode, nullptr);
}

namespace GaugeExtenderAccessor {
void SetIndicatorImpl(Ark_NativePointer node,
                      const Opt_GaugeIndicatorOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto indicator = Converter::OptConvertPtr<Converter::GaugeIndicatorOptions>(value);
    if (indicator) {
        if (indicator->icon) {
            GaugeModelNG::SetIndicatorIconPath(frameNode, indicator->icon->GetSrc(), indicator->icon->GetBundleName(),
                indicator->icon->GetModuleName());
        } else {
            GaugeModelNG::ResetIndicatorIconPath(frameNode);
        }
        Validator::ValidateNonNegative(indicator->space);
        Validator::ValidateNonPercent(indicator->space);
        GaugeModelStatic::SetIndicatorSpace(frameNode, indicator->space);
    } else {
        GaugeModelNG::ResetIndicatorIconPath(frameNode);
        GaugeModelNG::ResetIndicatorSpace(frameNode);
    }
    GaugeModelNG::SetIsShowIndicator(frameNode, true);
}

void NullIndicatorImpl(Ark_NativePointer node)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    GaugeModelNG::SetIsShowIndicator(frameNode, false);
}

void SetDescriptionImpl(Ark_NativePointer node, const Opt_CustomNodeBuilder* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        GaugeModelNG::SetIsShowLimitValue(frameNode, true);
        GaugeModelNG::SetIsShowDescription(frameNode, false);
        return;
    }
    CallbackHelper(*optValue).BuildAsync(
        [frameNode](const RefPtr<UINode>& uiNode) {
            GaugeModelStatic::SetDescription(frameNode, uiNode);
            GaugeModelNG::SetIsShowLimitValue(frameNode, false);
            GaugeModelNG::SetIsShowDescription(frameNode, true);
        }, node);
}

void NullDescriptionImpl(Ark_NativePointer node)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    GaugeModelNG::SetIsShowLimitValue(frameNode, false);
    GaugeModelNG::SetIsShowDescription(frameNode, false);
}

void SetTrackShadowImpl(Ark_NativePointer node, const Opt_GaugeShadowOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<GaugeShadowOptions>(value);
    GaugeShadowOptions defaultOptions;
    auto shadow = convValue.value_or(defaultOptions);
    GaugeModelNG::SetShadowOptions(frameNode, shadow);
}

void NullTrackShadowImpl(Ark_NativePointer node)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    GaugeShadowOptions shadow;
    shadow.isShadowVisible = false;
    GaugeModelNG::SetShadowOptions(frameNode, shadow);
}

void NullIndicatorImpl(Ark_NativePointer node)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(node);
    //auto convValue = Converter::OptConvert<type>(node); // for enums
    //undefinedModelNG::NullIndicator(frameNode, convValue);
}
void SetTrackShadowImpl(Ark_NativePointer node,
                        const Opt_GaugeShadowOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(node);
    //auto convValue = Converter::OptConvert<type>(node); // for enums
    //undefinedModelNG::SetTrackShadow(frameNode, convValue);
}
void NullTrackShadowImpl(Ark_NativePointer node)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(node);
    //auto convValue = Converter::OptConvert<type>(node); // for enums
    //undefinedModelNG::NullTrackShadow(frameNode, convValue);
}
void SetDescriptionImpl(Ark_NativePointer node,
                        const Opt_CustomNodeBuilder* builder)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(node);
    //auto convValue = Converter::OptConvert<type>(node); // for enums
    //undefinedModelNG::SetDescription(frameNode, convValue);
}
void NullDescriptionImpl(Ark_NativePointer node)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(node);
    //auto convValue = Converter::OptConvert<type>(node); // for enums
    //undefinedModelNG::NullDescription(frameNode, convValue);
}
} // GaugeExtenderAccessor

const GENERATED_ArkUIGaugeModifier* GetGaugeStaticModifier()
{
    static const GENERATED_ArkUIGaugeModifier ArkUIGaugeModifierImpl {
        GaugeModifier::ConstructImpl,
        GaugeInterfaceModifier::SetGaugeOptionsImpl,
        GaugeAttributeModifier::SetValueImpl,
        GaugeAttributeModifier::SetStartAngleImpl,
        GaugeAttributeModifier::SetEndAngleImpl,
        GaugeAttributeModifier::SetColorsImpl,
        GaugeAttributeModifier::SetStrokeWidthImpl,
        GaugeAttributeModifier::SetPrivacySensitiveImpl,
    };
    return &ArkUIGaugeModifierImpl;
}

const GENERATED_ArkUIGaugeContentModifier* GetGaugeStaticContentModifier()
{
    static const GENERATED_ArkUIGaugeContentModifier GaugeContentModifierImpl { ContentModifierGaugeImpl,
        ResetContentModifierGaugeImpl };
    return &GaugeContentModifierImpl;
}

const GENERATED_ArkUIGaugeExtenderAccessor* GetGaugeExtenderAccessor()
{
    static const GENERATED_ArkUIGaugeExtenderAccessor GaugeExtenderAccessorImpl {
        GaugeExtenderAccessor::SetIndicatorImpl,
        GaugeExtenderAccessor::NullIndicatorImpl,
        GaugeExtenderAccessor::SetTrackShadowImpl,
        GaugeExtenderAccessor::NullTrackShadowImpl,
        GaugeExtenderAccessor::SetDescriptionImpl,
        GaugeExtenderAccessor::NullDescriptionImpl
    };
    return &GaugeExtenderAccessorImpl;
}
} // namespace OHOS::Ace::NG::GeneratedModifier
