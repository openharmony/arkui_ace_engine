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

#include <algorithm>
#include <variant>

#include "base/utils/system_properties.h"
#include "base/utils/time_util.h"
#include "core/components/common/properties/alignment.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/base/view_abstract_model_ng.h"
#include "core/components_ng/pattern/counter/counter_model_ng.h"
#include "core/components_ng/pattern/counter/counter_node.h"
#include "core/components_ng/pattern/text/span_model_ng.h"
#include "core/components_ng/pattern/view_context/view_context_model_ng.h"
#include "core/interfaces/arkoala/utility/converter.h"
#include "core/interfaces/arkoala/utility/reverse_converter.h"
#include "core/interfaces/arkoala/utility/validators.h"
#include "core/interfaces/arkoala/utility/callback_helper.h"
#include "core/interfaces/arkoala/generated/interface/node_api.h"
#include "base/log/log_wrapper.h"

namespace {
constexpr double FULL_DIMENSION = 100.0;
constexpr double HALF_DIMENSION = 50.0;
constexpr double VISIBLE_RATIO_MIN = 0.0;
constexpr double VISIBLE_RATIO_MAX = 1.0;
constexpr uint32_t DEFAULT_DURATION = 1000; // ms
constexpr int64_t MICROSEC_TO_MILLISEC = 1000;
constexpr int NUM_3 = 3;
}

namespace OHOS::Ace::NG {
struct EdgesParamOptions {
    EdgesParam value;
    bool isLocalized;
};

struct ScaleOpt {
    std::optional<float> x;
    std::optional<float> y;
    std::optional<float> z;
    std::optional<Dimension> centerX;
    std::optional<Dimension> centerY;
};

struct TranslateOpt {
    std::optional<Dimension> x;
    std::optional<Dimension> y;
    std::optional<Dimension> z;
};

using ColorOrStrategy = std::variant<std::monostate, std::optional<Color>, std::optional<ForegroundColorStrategy>>;
using OffsetOrEdgesParam = std::variant<
    std::monostate,
    std::optional<OffsetT<Dimension>>,
    std::optional<EdgesParamOptions>
>;
using BackgroundImagePositionType = std::variant<
    Ark_Position,
    Ark_Alignment
>;
using ClipType = std::variant<
    Ark_Boolean,
    Ark_CircleAttribute,
    Ark_EllipseAttribute,
    Ark_PathAttribute,
    Ark_RectAttribute
>;

namespace Validator {
void ValidateAnimationOption(AnimationOption& opt, bool isForm)
{
    // limit animation for ArkTS Form
    if (isForm) {
        auto duration = opt.GetDuration();
        auto delay = opt.GetDelay();
        auto iterations = opt.GetIteration();
        auto tempo = opt.GetTempo();

        if (duration > static_cast<int32_t>(DEFAULT_DURATION)) {
            duration = static_cast<int32_t>(DEFAULT_DURATION);
        }
        if (delay != 0) {
            delay = 0;
        }
        if (SystemProperties::IsFormAnimationLimited() && iterations != 1) {
            iterations = 1;
        }
        if (!NearEqual(tempo, 1.0)) {
            tempo = 1.0;
        }
    }
}
} // namespace Validator

namespace Converter {
template<>
void AssignCast(std::optional<ColorOrStrategy>& dst, const Ark_Color& src)
{
    dst = OptConvert<Color>(src);
}

template<>
void AssignCast(std::optional<ColorOrStrategy>& dst, const Ark_Resource& src)
{
    dst = OptConvert<Color>(src);
}

template<>
void AssignCast(std::optional<ColorOrStrategy>& dst, const Ark_String& src)
{
    dst = OptConvert<Color>(src);
}

template<>
void AssignCast(std::optional<ColorOrStrategy>& dst, const Ark_Number& src)
{
    dst = OptConvert<Color>(src);
}

template<>
void AssignCast(std::optional<ColorOrStrategy>& dst, const Ark_ColoringStrategy& src)
{
    dst = OptConvert<ForegroundColorStrategy>(src);
}

template<>
void AssignCast(std::optional<BackgroundImageSizeType>& dst, const Ark_ImageSize& src)
{
    switch (src) {
        case ARK_IMAGE_SIZE_AUTO: dst = BackgroundImageSizeType::AUTO; break;
        case ARK_IMAGE_SIZE_COVER: dst = BackgroundImageSizeType::COVER; break;
        case ARK_IMAGE_SIZE_CONTAIN: dst = BackgroundImageSizeType::CONTAIN; break;
        case ARK_IMAGE_SIZE_FILL: dst = BackgroundImageSizeType::FILL; break;
        default: LOGE("Unexpected enum value in Ark_ImageSize: %{public}d", src);
    }
}

template<>
void AssignCast(std::optional<std::pair<double, double>>& dst, const Ark_Alignment& src)
{
    switch (src) {
        case ARK_ALIGNMENT_TOP_START: dst = { 0.0, 0.0 }; break;
        case ARK_ALIGNMENT_TOP: dst = { HALF_DIMENSION, 0.0 }; break;
        case ARK_ALIGNMENT_TOP_END: dst = { FULL_DIMENSION, 0.0 }; break;
        case ARK_ALIGNMENT_START: dst = { 0.0, HALF_DIMENSION }; break;
        case ARK_ALIGNMENT_CENTER: dst = { HALF_DIMENSION, HALF_DIMENSION }; break;
        case ARK_ALIGNMENT_END: dst = { FULL_DIMENSION, HALF_DIMENSION }; break;
        case ARK_ALIGNMENT_BOTTOM_START: dst = { 0.0, FULL_DIMENSION }; break;
        case ARK_ALIGNMENT_BOTTOM: dst = { HALF_DIMENSION, FULL_DIMENSION }; break;
        case ARK_ALIGNMENT_BOTTOM_END: dst = { FULL_DIMENSION, FULL_DIMENSION }; break;
        default: LOGE("Unexpected enum value in Ark_Alignment: %{public}d", src);
    }
}

template<>
MotionPathOption Convert(const Ark_MotionPathOptions& src)
{
    MotionPathOption p;
    p.SetPath(Converter::Convert<std::string>(src.path));
    if (auto opt = Converter::OptConvert<float>(src.from); opt) {
        p.SetBegin(*opt);
    }
    if (auto opt = Converter::OptConvert<float>(src.to); opt) {
        p.SetEnd(*opt);
    }
    if (auto opt = Converter::OptConvert<bool>(src.rotatable); opt) {
        p.SetRotate(*opt);
    }
    return p;
}

template<>
OHOS::Ace::SharedTransitionOption Convert(const Ark_sharedTransitionOptions& src)
{
    OHOS::Ace::SharedTransitionOption o = { .duration = INT_MIN };
    if (auto opt = Converter::OptConvert<RefPtr<Curve>>(src.curve); opt) {
        o.curve = *opt;
    }
    if (auto opt = Converter::OptConvert<int32_t>(src.duration); opt) {
        o.duration = *opt;
    }
    if (auto opt = Converter::OptConvert<int32_t>(src.delay); opt) {
        o.delay = *opt;
    }
    if (auto opt = Converter::OptConvert<MotionPathOption>(src.motionPath); opt) {
        o.motionPathOption = *opt;
    }
    if (auto opt = Converter::OptConvert<int32_t>(src.zIndex); opt) {
        o.zIndex = *opt;
    }
    if (auto opt = Converter::OptConvert<SharedTransitionEffectType>(src.type); opt) {
        o.type = *opt;
    }
    return o;
}

template<>
OffsetOrEdgesParam Convert(const Ark_Position& src)
{
    OffsetT<Dimension> offset;
    std::optional<Dimension> x = Converter::OptConvert<Dimension>(src.x);
    if (x) {
        offset.SetX(x.value());
    }
    std::optional<Dimension> y = Converter::OptConvert<Dimension>(src.y);
    if (y) {
        offset.SetY(y.value());
    }
    return offset;
}

template<>
OffsetOrEdgesParam Convert(const Ark_Edges& src)
{
    EdgesParamOptions edgesParamOptions;
    edgesParamOptions.value = Converter::Convert<EdgesParam>(src);
    edgesParamOptions.isLocalized = false;
    return edgesParamOptions;
}

template<>
OffsetOrEdgesParam Convert(const Ark_LocalizedEdges& src)
{
    return EdgesParamOptions {
        .value = EdgesParam {
            .top = OptConvert<Dimension>(src.top),
            .left = OptConvert<Dimension>(src.start),
            .bottom = OptConvert<Dimension>(src.bottom),
            .right = OptConvert<Dimension>(src.end),
        },
        .isLocalized = true
    };
}

template<>
Gradient Convert(const Ark_Type_CommonMethod_radialGradient_value& src)
{
    NG::Gradient gradient;
    gradient.CreateGradientWithType(NG::GradientType::RADIAL);

    // center
    gradient.GetRadialGradient()->radialCenterX = Converter::Convert<Dimension>(src.center.value0);
    gradient.GetRadialGradient()->radialCenterY = Converter::Convert<Dimension>(src.center.value1);

    // radius
    std::optional<Dimension> radiusOpt = Converter::OptConvert<Dimension>(src.radius);
    if (radiusOpt) {
        // radius should be positive [0, +∞)
        Dimension radius = radiusOpt.value().IsNonPositive() ? Dimension(0, DimensionUnit::VP) : radiusOpt.value();
        gradient.GetRadialGradient()->radialVerticalSize = radius;
        gradient.GetRadialGradient()->radialHorizontalSize = radius;
    }

    // repeating
    std::optional<bool> repeating = Converter::OptConvert<bool>(src.repeating);
    if (repeating) {
        gradient.SetRepeat(repeating.value());
    }

    // color stops
    std::vector<GradientColor> colorStops = Converter::Convert<std::vector<GradientColor>>(src.colors);
    for (GradientColor gradientColor : colorStops) {
        gradient.AddColor(gradientColor);
    }

    return gradient;
}

template<>
BackgroundImageSize Convert(const Ark_SizeOptions& src)
{
    BackgroundImageSize imageSize;
    CalcDimension width;
    CalcDimension height;
    auto widthOpt = Converter::OptConvert<Dimension>(src.width);
    if (widthOpt) {
        width = widthOpt.value();
    }
    auto heightOpt = Converter::OptConvert<Dimension>(src.height);
    if (heightOpt) {
        height = heightOpt.value();
    }
    double valueWidth = width.ConvertToPx();
    double valueHeight = height.ConvertToPx();
    BackgroundImageSizeType typeWidth = BackgroundImageSizeType::LENGTH;
    BackgroundImageSizeType typeHeight = BackgroundImageSizeType::LENGTH;
    if (width.Unit() == DimensionUnit::PERCENT) {
        typeWidth = BackgroundImageSizeType::PERCENT;
        valueWidth = width.Value();
    }
    if (height.Unit() == DimensionUnit::PERCENT) {
        typeHeight = BackgroundImageSizeType::PERCENT;
        valueHeight = height.Value();
    }
    imageSize.SetSizeTypeX(typeWidth);
    imageSize.SetSizeValueX(valueWidth);
    imageSize.SetSizeTypeY(typeHeight);
    imageSize.SetSizeValueY(valueHeight);
    return imageSize;
}

template<>
BackgroundImageSize Convert(const Ark_ImageSize& src)
{
    auto sizeType = OptConvert<BackgroundImageSizeType>(src).value_or(BackgroundImageSizeType::AUTO);
    BackgroundImageSize imageSize;
    imageSize.SetSizeTypeX(sizeType);
    imageSize.SetSizeTypeY(sizeType);
    return imageSize;
}

template<>
std::pair<std::optional<Dimension>, std::optional<Dimension>> Convert(const Ark_Position& src)
{
    auto x = OptConvert<Dimension>(src.x);
    auto y = OptConvert<Dimension>(src.y);
    return {x, y};
}

template<>
ScaleOpt Convert(const Ark_ScaleOptions& src)
{
    ScaleOpt scaleOptions;
    scaleOptions.x = OptConvert<float>(src.x);
    scaleOptions.y = OptConvert<float>(src.y);
    scaleOptions.z = OptConvert<float>(src.z);
    scaleOptions.centerX = OptConvert<Dimension>(src.centerX);
    scaleOptions.centerY = OptConvert<Dimension>(src.centerY);
    return scaleOptions;
}

template<>
TranslateOpt Convert(const Ark_TranslateOptions& src)
{
    TranslateOpt translateOptions;
    translateOptions.x = OptConvert<Dimension>(src.x);
    translateOptions.y = OptConvert<Dimension>(src.y);
    translateOptions.z = OptConvert<Dimension>(src.z);
    return translateOptions;
}

template<>
AnimationOption Convert(const Ark_AnimateParam& src)
{
    AnimationOption option;
    // If the attribute does not exist, the default value is used.
    auto duration = Converter::OptConvert<int32_t>(src.duration).value_or(DEFAULT_DURATION);
    auto delay = Converter::OptConvert<int32_t>(src.delay).value_or(0);
    auto iterations = Converter::OptConvert<int32_t>(src.iterations).value_or(1);
    auto tempo = static_cast<double>(Converter::OptConvert<float>(src.tempo).value_or(1.0f));
    if (SystemProperties::GetRosenBackendEnabled() && NearZero(tempo)) {
        // set duration to 0 to disable animation.
        duration = 0;
    }
    auto direction = Converter::OptConvert<AnimationDirection>(src.playMode).value_or(AnimationDirection::NORMAL);
    auto finishCallbackType = Converter::OptConvert<FinishCallbackType>(src.finishCallbackType)
        .value_or(FinishCallbackType::REMOVED);
    auto curve = Converter::OptConvert<RefPtr<Curve>>(src.curve).value_or(Curves::EASE_IN_OUT);
    auto frameRateRange = Converter::OptConvert<RefPtr<FrameRateRange>>(src.expectedFrameRateRange)
        .value_or(AceType::MakeRefPtr<FrameRateRange>(0, 0, 0));

    option.SetDuration(duration);
    option.SetDelay(delay);
    option.SetIteration(iterations);
    option.SetTempo(tempo);
    option.SetAnimationDirection(direction);
    option.SetFinishCallbackType(finishCallbackType);
    option.SetCurve(curve);
    option.SetFrameRateRange(frameRateRange);
    return option;
}

template<>
std::vector<DimensionRect> Convert(const Ark_Rectangle &src)
{
    return { Convert<DimensionRect>(src) };
}

using PixelRoundPolicyOneRule = bool; // let rule 'Ceil' is false, rool 'FLoor' is true

template<>
void AssignCast(std::optional<PixelRoundPolicyOneRule>& dst, const Ark_PixelRoundCalcPolicy& src)
{
    if (src == Ark_PixelRoundCalcPolicy::ARK_PIXEL_ROUND_CALC_POLICY_FORCE_CEIL) {
        dst = false;
    }
    if (src == Ark_PixelRoundCalcPolicy::ARK_PIXEL_ROUND_CALC_POLICY_FORCE_FLOOR) {
        dst = true;
    }
}

template<>
uint8_t Convert(const Ark_PixelRoundPolicy& src)
{
    uint8_t dst = 0;
    if (auto rule = OptConvert<PixelRoundPolicyOneRule>(src.start); rule) {
        auto policy = *rule ? PixelRoundPolicy::FORCE_FLOOR_START : PixelRoundPolicy::FORCE_CEIL_START;
        dst |= static_cast<uint8_t>(policy);
    }
    if (auto rule = OptConvert<PixelRoundPolicyOneRule>(src.end); rule) {
        auto policy = *rule ? PixelRoundPolicy::FORCE_FLOOR_END : PixelRoundPolicy::FORCE_CEIL_END;
        dst |= static_cast<uint8_t>(policy);
    }
    if (auto rule = OptConvert<PixelRoundPolicyOneRule>(src.top); rule) {
        auto policy = *rule ? PixelRoundPolicy::FORCE_FLOOR_TOP : PixelRoundPolicy::FORCE_CEIL_TOP;
        dst |= static_cast<uint8_t>(policy);
    }
    if (auto rule = OptConvert<PixelRoundPolicyOneRule>(src.bottom); rule) {
        auto policy = *rule ? PixelRoundPolicy::FORCE_FLOOR_BOTTOM : PixelRoundPolicy::FORCE_CEIL_BOTTOM;
        dst |= static_cast<uint8_t>(policy);
    }
    return dst;
}

template<>
BlurOption Convert(const Ark_BlurOptions& src)
{
    return BlurOption {
        .grayscale = {
            Converter::Convert<float>(src.grayscale.value0),
            Converter::Convert<float>(src.grayscale.value1)
        }
    };
}

template<>
void AssignCast(std::optional<BlurStyleActivePolicy>& dst, const Ark_BlurStyleActivePolicy& src)
{
    switch (src) {
        case ARK_BLUR_STYLE_ACTIVE_POLICY_FOLLOWS_WINDOW_ACTIVE_STATE:
            dst = BlurStyleActivePolicy::FOLLOWS_WINDOW_ACTIVE_STATE; break;
        case ARK_BLUR_STYLE_ACTIVE_POLICY_ALWAYS_ACTIVE: dst = BlurStyleActivePolicy::ALWAYS_ACTIVE; break;
        case ARK_BLUR_STYLE_ACTIVE_POLICY_ALWAYS_INACTIVE: dst = BlurStyleActivePolicy::ALWAYS_INACTIVE; break;
        default: LOGE("Unexpected enum value in Ark_BlurStyleActivePolicy: %{public}d", src);
    }
}

template<>
void AssignCast(std::optional<BlurType>& dst, const Ark_BlurType& src)
{
    switch (src) {
        case ARK_BLUR_TYPE_WITHIN_WINDOW: dst = BlurType::WITHIN_WINDOW; break;
        case ARK_BLUR_TYPE_BEHIND_WINDOW: dst = BlurType::BEHIND_WINDOW; break;
        default: LOGE("Unexpected enum value in Ark_BlurType: %{public}d", src);
    }
}

template<>
EffectOption Convert(const Ark_BackgroundEffectOptions& src)
{
    EffectOption dst;
    dst.radius = OptConvert<Dimension>(src.radius).value_or(dst.radius);
    dst.saturation = OptConvert<float>(src.saturation).value_or(dst.saturation);
    dst.brightness = OptConvert<float>(src.brightness).value_or(dst.brightness);
    dst.color = OptConvert<Color>(src.color).value_or(dst.color);
    dst.adaptiveColor = OptConvert<AdaptiveColor>(src.adaptiveColor).value_or(dst.adaptiveColor);
    dst.blurOption = OptConvert<BlurOption>(src.blurOptions).value_or(dst.blurOption);
    dst.policy = OptConvert<BlurStyleActivePolicy>(src.policy).value_or(dst.policy);
    dst.blurType = OptConvert<BlurType>(src.type).value_or(dst.blurType);
    dst.inactiveColor = OptConvert<Color>(src.inactiveColor).value_or(dst.inactiveColor);
    return dst;
}

template<>
float Convert(const Ark_ForegroundEffectOptions& src)
{
    return Convert<float>(src.radius);
}

template<>
BlurStyleOption Convert(const Ark_BackgroundBlurStyleOptions& src)
{
    BlurStyleOption dst;
    dst.colorMode = OptConvert<ThemeColorMode>(src.colorMode).value_or(dst.colorMode);
    dst.adaptiveColor = OptConvert<AdaptiveColor>(src.adaptiveColor).value_or(dst.adaptiveColor);
    if (auto scaleOpt = OptConvert<float>(src.scale); scaleOpt) {
        dst.scale = static_cast<double>(*scaleOpt);
    }
    dst.blurOption = OptConvert<BlurOption>(src.blurOptions).value_or(dst.blurOption);
    dst.policy = OptConvert<BlurStyleActivePolicy>(src.policy).value_or(dst.policy);
    dst.blurType = OptConvert<BlurType>(src.type).value_or(dst.blurType);
    dst.inactiveColor = OptConvert<Color>(src.inactiveColor).value_or(dst.inactiveColor);
    return dst;
}


template<>
BlurStyleOption Convert(const Ark_ForegroundBlurStyleOptions& src)
{
    BlurStyleOption dst;
    dst.colorMode = OptConvert<ThemeColorMode>(src.colorMode).value_or(dst.colorMode);
    dst.adaptiveColor = OptConvert<AdaptiveColor>(src.adaptiveColor).value_or(dst.adaptiveColor);
    if (auto scaleOpt = OptConvert<float>(src.scale); scaleOpt) {
        dst.scale = static_cast<double>(*scaleOpt);
    }
    dst.blurOption = OptConvert<BlurOption>(src.blurOptions).value_or(dst.blurOption);
    return dst;
}

template<>
BorderWidthProperty Convert(const Ark_LocalizedEdgeWidths& src)
{
    BorderWidthProperty dst;
    LOGE("ARKOALA: Convert to [BorderWidthProperty] from [Ark_LocalizedEdgeWidths] is not supported\n");
    return dst;
}

template<>
OverlayOptions Convert(const Ark_OverlayOptions& src)
{
    OverlayOptions dst;
    auto align = Converter::OptConvert<Alignment>(src.align);
    if (align) {
        dst.align = align.value();
    }
    auto x = Converter::OptConvert<Dimension>(src.offset.value.x);
    if (x) {
        dst.x = x.value();
    }
    auto y = Converter::OptConvert<Dimension>(src.offset.value.y);
    if (y) {
        dst.y = y.value();
    }
    return dst;
}

template<>
ImageResizableSlice Convert(const Ark_EdgeWidths& src)
{
    ImageResizableSlice dst;
    dst.left = OptConvert<Dimension>(src.left).value_or(dst.left);
    dst.right = OptConvert<Dimension>(src.right).value_or(dst.right);
    dst.top = OptConvert<Dimension>(src.top).value_or(dst.top);
    dst.bottom = OptConvert<Dimension>(src.bottom).value_or(dst.bottom);
    return dst;
}

template<>
BorderWidthProperty Convert(const Ark_EdgeOutlineWidths& src)
{
    BorderWidthProperty dst;
    dst.leftDimen = OptConvert<Dimension>(src.left);
    Validator::ValidateNonNegative(dst.leftDimen);
    dst.topDimen = OptConvert<Dimension>(src.top);
    Validator::ValidateNonNegative(dst.topDimen);
    dst.rightDimen = OptConvert<Dimension>(src.right);
    Validator::ValidateNonNegative(dst.rightDimen);
    dst.bottomDimen = OptConvert<Dimension>(src.bottom);
    Validator::ValidateNonNegative(dst.bottomDimen);
    dst.multiValued = true;
    return dst;
}

template<>
BorderRadiusProperty Convert(const Ark_OutlineRadiuses& src)
{
    BorderRadiusProperty dst;
    dst.radiusTopLeft = OptConvert<Dimension>(src.topLeft);
    dst.radiusTopRight = OptConvert<Dimension>(src.topRight);
    dst.radiusBottomLeft = OptConvert<Dimension>(src.bottomLeft);
    dst.radiusBottomRight = OptConvert<Dimension>(src.bottomRight);
    dst.multiValued = true;
    return dst;
}

template<>
BorderColorProperty Convert(const Ark_LocalizedEdgeColors& src)
{
    BorderColorProperty dst;
    LOGE("Converter::AssignTo(std::optional<BorderColorProperty> &, const Ark_LocalizedEdgeColors&)"
        " handles invalid structure"
    );
    // the src.left/.right should be used instead .start/.end, interface_sdk-js/issues/IB0DVD
    dst.leftColor = OptConvert<Color>(src.start);
    dst.topColor = OptConvert<Color>(src.top);
    dst.rightColor = OptConvert<Color>(src.end);
    dst.bottomColor = OptConvert<Color>(src.bottom);
    dst.multiValued = true;
    return dst;
}

template<>
void AssignCast(std::optional<BorderStyle>& dst, const Ark_OutlineStyle& src)
{
    switch (src) {
        case ARK_OUTLINE_STYLE_DOTTED: dst = BorderStyle::DOTTED; break;
        case ARK_OUTLINE_STYLE_DASHED: dst = BorderStyle::DASHED; break;
        case ARK_OUTLINE_STYLE_SOLID: dst = BorderStyle::SOLID; break;
        default: LOGE("Unexpected enum value in Ark_OutlineStyle: %{public}d", src);
    }
}

template<>
BorderStyleProperty Convert(const Ark_OutlineStyle& src)
{
    BorderStyleProperty dst;
    if (auto styleOpt = OptConvert<BorderStyle>(src); styleOpt) {
        dst.SetBorderStyle(*styleOpt);
    }
    return dst;
}

template<>
BorderStyleProperty Convert(const Ark_EdgeOutlineStyles& src)
{
    BorderStyleProperty dst;
    dst.styleLeft = OptConvert<BorderStyle>(src.left);
    dst.styleRight = OptConvert<BorderStyle>(src.right);
    dst.styleTop = OptConvert<BorderStyle>(src.top);
    dst.styleBottom = OptConvert<BorderStyle>(src.bottom);
    dst.multiValued = true;
    return dst;
}
} // namespace Converter
} // namespace OHOS::Ace::NG

namespace OHOS::Ace::NG::GeneratedModifier {
constexpr int32_t CASE_0 = 0;
constexpr int32_t CASE_1 = 1;
constexpr int32_t CASE_2 = 2;

namespace CommonMethodModifier {
int64_t GetFormAnimationTimeInterval(const RefPtr<PipelineBase>& pipelineContext)
{
    CHECK_NULL_RETURN(pipelineContext, 0);
    return (GetMicroTickCount() - pipelineContext->GetFormAnimationStartTime()) / MICROSEC_TO_MILLISEC;
}

void WidthImpl(Ark_NativePointer node,
               const Ark_Length* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto result = Converter::Convert<CalcLength>(*value);
    if (AceType::TypeId(frameNode) == CounterNode::TypeId()) {
        if (result.GetDimensionContainsNegative().IsNegative()) {
            return;
        }
        CounterModelNG::SetWidth(frameNode, result);
    } else {
        if (result.GetDimensionContainsNegative().IsNegative()) {
            ViewAbstract::ClearWidthOrHeight(frameNode, true);
            return;
        }
        ViewAbstract::SetWidth(frameNode, result);
    }
}
void HeightImpl(Ark_NativePointer node,
                const Ark_Length* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto result = Converter::Convert<CalcLength>(*value);
    if (AceType::TypeId(frameNode) == CounterNode::TypeId()) {
        if (result.GetDimensionContainsNegative().IsNegative()) {
            return;
        }
        CounterModelNG::SetHeight(frameNode, result);
    } else {
        if (result.GetDimensionContainsNegative().IsNegative()) {
            ViewAbstract::ClearWidthOrHeight(frameNode, false);
            return;
        }
        ViewAbstract::SetHeight(frameNode, result);
    }
}
void DrawModifierImpl(Ark_NativePointer node,
                      const Ark_Union_DrawModifier_Undefined* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CommonMethodModelNG::SetDrawModifier(frameNode, convValue);
}
void ResponseRegionImpl(Ark_NativePointer node,
                        const Ark_Union_Array_Rectangle_Rectangle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    if (auto convArray = Converter::OptConvert<std::vector<DimensionRect>>(*value); convArray) {
        ViewAbstract::SetResponseRegion(frameNode, *convArray);
    } else {
        ViewAbstract::SetResponseRegion(frameNode, { DimensionRect() });
    }
}
void MouseResponseRegionImpl(Ark_NativePointer node,
                             const Ark_Union_Array_Rectangle_Rectangle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    if (auto convArray = Converter::OptConvert<std::vector<DimensionRect>>(*value); convArray) {
        ViewAbstract::SetMouseResponseRegion(frameNode, *convArray);
    } else {
        ViewAbstract::SetMouseResponseRegion(frameNode, { DimensionRect() });
    }
}
void SizeImpl(Ark_NativePointer node,
              const Ark_SizeOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto width = Converter::OptConvert<Ark_Length>(value->width);
    if (width) {
        WidthImpl(node, &width.value());
    }
    auto height = Converter::OptConvert<Ark_Length>(value->height);
    if (height) {
        HeightImpl(node, &height.value());
    }
}
void ConstraintSizeImpl(Ark_NativePointer node,
                        const Ark_ConstraintSizeOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto minWidth = Converter::OptConvert<CalcLength>(value->minWidth);
    if (minWidth) {
        ViewAbstract::SetMinWidth(frameNode, minWidth.value());
    }
    auto minHeight = Converter::OptConvert<CalcLength>(value->minHeight);
    if (minHeight) {
        ViewAbstract::SetMinHeight(frameNode, minHeight.value());
    }
    auto maxWidth = Converter::OptConvert<CalcLength>(value->maxWidth);
    if (maxWidth) {
        ViewAbstract::SetMaxWidth(frameNode, maxWidth.value());
    }
    auto maxHeight = Converter::OptConvert<CalcLength>(value->maxHeight);
    if (maxHeight) {
        ViewAbstract::SetMaxHeight(frameNode, maxHeight.value());
    }
}
void TouchableImpl(Ark_NativePointer node,
                   Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::SetTouchable(frameNode, static_cast<bool>(value));
}
void HitTestBehaviorImpl(Ark_NativePointer node,
                         Ark_HitTestMode value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    NG::HitTestMode hitTestModeNG = static_cast<NG::HitTestMode>(value);
    ViewAbstract::SetHitTestMode(frameNode, hitTestModeNG);
}
void OnChildTouchTestImpl(Ark_NativePointer node,
                          const Callback_Array_TouchTestInfo_TouchResult* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CommonMethodModelNG::SetOnChildTouchTest(frameNode, convValue);
}
void LayoutWeightImpl(Ark_NativePointer node,
                      const Ark_Union_Number_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto weight = Converter::OptConvert<float>(*value);
    if (weight) {
        ViewAbstract::SetLayoutWeight(frameNode, weight.value());
    }
}
void PaddingImpl(Ark_NativePointer node,
                 const Ark_Union_Padding_Length_LocalizedPadding* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    ViewAbstract::SetPadding(frameNode, Converter::OptConvert<PaddingProperty>(*value));
}
void MarginImpl(Ark_NativePointer node,
                const Ark_Union_Margin_Length_LocalizedMargin* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    ViewAbstract::SetMargin(frameNode, Converter::OptConvert<PaddingProperty>(*value));
}
void BackgroundColorImpl(Ark_NativePointer node,
                         const Ark_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    if (AceType::TypeId(frameNode) == CounterNode::TypeId()) {
        CounterModelNG::SetBackgroundColor(frameNode, Converter::OptConvert<Color>(*value));
    } else {
        ViewAbstract::SetBackgroundColor(frameNode, Converter::OptConvert<Color>(*value));
    }
}
void PixelRoundImpl(Ark_NativePointer node,
                    const Ark_PixelRoundPolicy* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto convValue = Converter::Convert<uint8_t>(*value);
    ViewAbstract::SetPixelRound(frameNode, convValue);
}
void BackgroundImageSizeImpl(Ark_NativePointer node,
                             const Ark_Union_SizeOptions_ImageSize* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    ViewAbstract::SetBackgroundImageSize(frameNode, Converter::OptConvert<BackgroundImageSize>(*value));
}
void BackgroundImagePositionImpl(Ark_NativePointer node,
                                 const Ark_Union_Position_Alignment* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto varValue = Converter::OptConvert<BackgroundImagePositionType>(*value);
    BackgroundImagePosition bgImgPosition;
    AnimationOption option = ViewStackProcessor::GetInstance()->GetImplicitAnimationOption();
    double valueX = 0.0;
    double valueY = 0.0;
    DimensionUnit typeX = DimensionUnit::PX;
    DimensionUnit typeY = DimensionUnit::PX;
    if (varValue) {
        if (auto arkPosition = std::get_if<Ark_Position>(&varValue.value()); arkPosition) {
            auto position =
                Converter::Convert<std::pair<std::optional<Dimension>, std::optional<Dimension>>>(*arkPosition);
            CalcDimension x;
            CalcDimension y;
            if (position.first) {
                x = position.first.value();
            }
            if (position.second) {
                y = position.second.value();
            }
            valueX = x.ConvertToPx();
            valueY = y.ConvertToPx();
            if (x.Unit() == DimensionUnit::PERCENT) {
                valueX = x.Value();
                typeX = DimensionUnit::PERCENT;
            }
            if (y.Unit() == DimensionUnit::PERCENT) {
                valueY = y.Value();
                typeY = DimensionUnit::PERCENT;
            }
        } else if (auto arkAlign = std::get_if<Ark_Alignment>(&varValue.value()); arkAlign) {
            auto alignment = Converter::OptConvert<std::pair<double, double>>(*arkAlign);
            if (alignment) {
                bgImgPosition.SetIsAlign(true);
                typeX = DimensionUnit::PERCENT;
                typeY = DimensionUnit::PERCENT;
                valueX = alignment.value().first;
                valueY = alignment.value().second;
            }
        }
    }
    bgImgPosition.SetSizeX(AnimatableDimension(valueX, typeX, option));
    bgImgPosition.SetSizeY(AnimatableDimension(valueY, typeY, option));
    ViewAbstract::SetBackgroundImagePosition(frameNode, bgImgPosition);
}
void BackgroundEffectImpl(Ark_NativePointer node,
                          const Ark_BackgroundEffectOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto convValue = Converter::Convert<EffectOption>(*value);
    ViewAbstract::SetBackgroundEffect(frameNode, convValue);
}
void BackgroundImageResizableImpl(Ark_NativePointer node,
                                  const Ark_ResizableOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    ImageResizableSlice convValue {};
    convValue = Converter::OptConvert<ImageResizableSlice>(value->slice).value_or(convValue);
    // lattice .. This parameter does not take effect for the backgroundImageResizable API.
    ViewAbstract::SetBackgroundImageResizableSlice(frameNode, convValue);
}
void ForegroundEffectImpl(Ark_NativePointer node,
                          const Ark_ForegroundEffectOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto convValue = Converter::OptConvert<float>(*value);
    Validator::ValidateNonNegative(convValue);
    ViewAbstract::SetForegroundEffect(frameNode, convValue);
}
void VisualEffectImpl(Ark_NativePointer node,
                      const Ark_CustomObject* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CommonMethodModelNG::SetVisualEffect(frameNode, convValue);
}
void BackgroundFilterImpl(Ark_NativePointer node,
                          const Ark_CustomObject* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CommonMethodModelNG::SetBackgroundFilter(frameNode, convValue);
}
void ForegroundFilterImpl(Ark_NativePointer node,
                          const Ark_CustomObject* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CommonMethodModelNG::SetForegroundFilter(frameNode, convValue);
}
void CompositingFilterImpl(Ark_NativePointer node,
                           const Ark_CustomObject* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CommonMethodModelNG::SetCompositingFilter(frameNode, convValue);
}
void OpacityImpl(Ark_NativePointer node,
                 const Ark_Union_Number_Resource* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto result = Converter::OptConvert<float>(*value);
    if (result) {
        ViewAbstract::SetOpacity(frameNode, result.value());
    }
}
void BorderImpl(Ark_NativePointer node,
                const Ark_BorderOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto style = Converter::OptConvert<BorderStyleProperty>(value->style);
    if (style){
        ViewAbstract::SetBorderStyle(frameNode, style.value());
    }
    auto width = Converter::OptConvert<BorderWidthProperty>(value->width);
    if (width) {
        ViewAbstract::SetBorderWidth(frameNode, width.value());
    }
    auto color = Converter::OptConvert<BorderColorProperty>(value->color);
    if (color) {
        ViewAbstract::SetBorderColor(frameNode, color.value());
    }
    auto radius = Converter::OptConvert<BorderRadiusProperty>(value->radius);
    if (radius) {
        ViewAbstract::SetBorderRadius(frameNode, radius.value());
    }
    auto dashGap = Converter::OptConvert<BorderWidthProperty>(value->dashGap);
    if (dashGap) {
        ViewAbstract::SetDashGap(frameNode, dashGap.value());
    }
    auto dashWidth = Converter::OptConvert<BorderWidthProperty>(value->dashWidth);
    if (dashWidth) {
        ViewAbstract::SetDashWidth(frameNode, dashWidth.value());
    }
}
void BorderStyleImpl(Ark_NativePointer node,
                     const Ark_Union_BorderStyle_EdgeStyles* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto style = Converter::OptConvert<BorderStyleProperty>(*value);
    if (style){
        ViewAbstract::SetBorderStyle(frameNode, style.value());
    }
}
void BorderWidthImpl(Ark_NativePointer node,
                     const Ark_Union_Length_EdgeWidths_LocalizedEdgeWidths* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto width = Converter::OptConvert<BorderWidthProperty>(*value);
    if (width) {
        ViewAbstract::SetBorderWidth(frameNode, width.value());
    }
}
void BorderColorImpl(Ark_NativePointer node,
                     const Ark_Union_ResourceColor_EdgeColors_LocalizedEdgeColors* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto color = Converter::OptConvert<BorderColorProperty>(*value);
    if (color) {
        ViewAbstract::SetBorderColor(frameNode, color.value());
    }
}
void BorderRadiusImpl(Ark_NativePointer node,
                      const Ark_Union_Length_BorderRadiuses_LocalizedBorderRadiuses* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto radiuses = Converter::OptConvert<BorderRadiusProperty>(*value);
    if (radiuses) {
        ViewAbstract::SetBorderRadius(frameNode, radiuses.value());
    }
}
void BorderImageImpl(Ark_NativePointer node,
                     const Ark_BorderImageOption* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    RefPtr<BorderImage> borderImage = AceType::MakeRefPtr<BorderImage>();
    if (value->source.tag != Ark_Tag::ARK_TAG_UNDEFINED && value->source.value.selector == NUM_3) {
        Gradient gradient;
        gradient.CreateGradientWithType(GradientType::LINEAR);
        auto repeat = Converter::OptConvert<bool>(value->source.value.value2.repeating);
        if (repeat) {
            gradient.SetRepeat(repeat.value());
        }
        auto linear = gradient.GetLinearGradient();
        linear->angle = Converter::OptConvert<Dimension>(value->source.value.value2.angle);
        auto direction = Converter::OptConvert<GradientDirection>(value->source.value.value2.direction);
        if (direction) {
            Converter::AssignLinearGradientDirection(linear, direction.value());
        }
        Converter::AssignGradientColors(&gradient, &value->source.value.value2.colors);
        ViewAbstract::SetBorderImageGradient(frameNode, gradient);
    } else {
        auto info = Converter::OptConvert<ImageSourceInfo>(value->source);
        if (info) {
            borderImage->SetSrc(info.value().GetSrc());
        }
    }
    auto repeat = Converter::OptConvert<BorderImageRepeat>(value->repeat);
    if (repeat) {
        borderImage->SetRepeatMode(repeat.value());
    }
    auto fill = Converter::OptConvert<bool>(value->fill);
    if (fill) {
        borderImage->SetNeedFillCenter(fill.value());
    }
    if (value->outset.tag != Ark_Tag::ARK_TAG_UNDEFINED) {
        switch (value->outset.value.selector) {
            case CASE_0: {
                auto outset = Converter::OptConvert<Dimension>(value->outset.value.value0);
                if (outset) {
                    borderImage->SetEdgeOutset(BorderImageDirection::LEFT, outset.value());
                    borderImage->SetEdgeOutset(BorderImageDirection::RIGHT, outset.value());
                    borderImage->SetEdgeOutset(BorderImageDirection::TOP, outset.value());
                    borderImage->SetEdgeOutset(BorderImageDirection::BOTTOM, outset.value());
                }
                break;
            }
            case CASE_1: {
                auto left = Converter::OptConvert<Dimension>(value->outset.value.value1.left);
                auto top = Converter::OptConvert<Dimension>(value->outset.value.value1.top);
                auto right = Converter::OptConvert<Dimension>(value->outset.value.value1.right);
                auto bottom = Converter::OptConvert<Dimension>(value->outset.value.value1.bottom);
                if (left) {
                    borderImage->SetEdgeOutset(BorderImageDirection::LEFT, left.value());
                }
                if (top) {
                    borderImage->SetEdgeOutset(BorderImageDirection::TOP, top.value());
                }
                if (right) {
                    borderImage->SetEdgeOutset(BorderImageDirection::RIGHT, right.value());
                }
                if (bottom) {
                    borderImage->SetEdgeOutset(BorderImageDirection::BOTTOM, bottom.value());
                }
                break;
            }
            case CASE_2:
                LOGE("ARKOALA: CommonMethod::BorderImageImpl: LocalizedEdgeWidths.CustomObject is not supported.\n");
                break;
            default:
                LOGE("ARKOALA: CommonMethod::BorderImageImpl: Unexpected selector: %{public}d\n",
                    value->outset.value.selector);
                return;
        }
    }
    if (value->slice.tag != Ark_Tag::ARK_TAG_UNDEFINED) {
        switch (value->slice.value.selector) {
            case CASE_0: {
                auto slice = Converter::OptConvert<Dimension>(value->slice.value.value0);
                if (slice) {
                    borderImage->SetEdgeSlice(BorderImageDirection::LEFT, slice.value());
                    borderImage->SetEdgeSlice(BorderImageDirection::RIGHT, slice.value());
                    borderImage->SetEdgeSlice(BorderImageDirection::TOP, slice.value());
                    borderImage->SetEdgeSlice(BorderImageDirection::BOTTOM, slice.value());
                }
                break;
            }
            case CASE_1: {
                auto left = Converter::OptConvert<Dimension>(value->slice.value.value1.left);
                auto top = Converter::OptConvert<Dimension>(value->slice.value.value1.top);
                auto right = Converter::OptConvert<Dimension>(value->slice.value.value1.right);
                auto bottom = Converter::OptConvert<Dimension>(value->slice.value.value1.bottom);
                if (left) {
                    borderImage->SetEdgeSlice(BorderImageDirection::LEFT, left.value());
                }
                if (top) {
                    borderImage->SetEdgeSlice(BorderImageDirection::TOP, top.value());
                }
                if (right) {
                    borderImage->SetEdgeSlice(BorderImageDirection::RIGHT, right.value());
                }
                if (bottom) {
                    borderImage->SetEdgeSlice(BorderImageDirection::BOTTOM, bottom.value());
                }
                break;
            }
            case CASE_2:
                LOGE("ARKOALA: CommonMethod::BorderImageImpl: LocalizedEdgeWidths.CustomObject is not supported.\n");
                break;
            default:
                LOGE("ARKOALA: CommonMethod::BorderImageImpl: Unexpected selector: %{public}d\n",
                    value->slice.value.selector);
                return;
        }
    }
    if (value->width.tag != Ark_Tag::ARK_TAG_UNDEFINED) {
        switch (value->width.value.selector) {
            case CASE_0: {
                auto width = Converter::OptConvert<Dimension>(value->width.value.value0);
                if (width) {
                    borderImage->SetEdgeWidth(BorderImageDirection::LEFT, width.value());
                    borderImage->SetEdgeWidth(BorderImageDirection::RIGHT, width.value());
                    borderImage->SetEdgeWidth(BorderImageDirection::TOP, width.value());
                    borderImage->SetEdgeWidth(BorderImageDirection::BOTTOM, width.value());
                }
                break;
            }
            case CASE_1: {
                auto left = Converter::OptConvert<Dimension>(value->width.value.value1.left);
                auto top = Converter::OptConvert<Dimension>(value->width.value.value1.top);
                auto right = Converter::OptConvert<Dimension>(value->width.value.value1.right);
                auto bottom = Converter::OptConvert<Dimension>(value->width.value.value1.bottom);
                if (left) {
                    borderImage->SetEdgeWidth(BorderImageDirection::LEFT, left.value());
                }
                if (top) {
                    borderImage->SetEdgeWidth(BorderImageDirection::TOP, top.value());
                }
                if (right) {
                    borderImage->SetEdgeWidth(BorderImageDirection::RIGHT, right.value());
                }
                if (bottom) {
                    borderImage->SetEdgeWidth(BorderImageDirection::BOTTOM, bottom.value());
                }
                break;
            }
            case CASE_2:
                LOGE("ARKOALA: CommonMethod::BorderImageImpl: LocalizedEdgeWidths.CustomObject is not supported.\n");
                break;
            default:
                LOGE("ARKOALA: CommonMethod::BorderImageImpl: Unexpected selector: %{public}d\n",
                    value->slice.value.selector);
                return;
        }
    }
    ViewAbstract::SetBorderImage(frameNode, borderImage);
}

void OutlineImpl(Ark_NativePointer node,
                 const Ark_OutlineOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto borderWidthOpt = Converter::OptConvert<BorderWidthProperty>(value->width);
    ViewAbstract::SetOuterBorderWidth(frameNode, borderWidthOpt.value_or(BorderWidthProperty()));

    auto borderRadiusOpt = Converter::OptConvert<BorderRadiusProperty>(value->radius);
    ViewAbstract::SetOuterBorderRadius(frameNode, borderRadiusOpt.value_or(BorderRadiusProperty()));

    auto borderColorsOpt = Converter::OptConvert<BorderColorProperty>(value->color);
    ViewAbstract::SetOuterBorderColor(frameNode, borderColorsOpt.value_or(BorderColorProperty()));

    auto borderStylesOpt = Converter::OptConvert<BorderStyleProperty>(value->style);
    ViewAbstract::SetOuterBorderStyle(frameNode, borderStylesOpt.value_or(BorderStyleProperty()));
}
void OutlineStyleImpl(Ark_NativePointer node,
                      const Ark_Union_OutlineStyle_EdgeOutlineStyles* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto borderStylesOpt = Converter::OptConvert<BorderStyleProperty>(*value);
    ViewAbstract::SetOuterBorderStyle(frameNode, borderStylesOpt.value_or(BorderStyleProperty()));
}
void OutlineWidthImpl(Ark_NativePointer node,
                      const Ark_Union_Dimension_EdgeOutlineWidths* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto borderWidthOpt = Converter::OptConvert<BorderWidthProperty>(*value);
    ViewAbstract::SetOuterBorderWidth(frameNode, borderWidthOpt.value_or(BorderWidthProperty()));
}
void OutlineColorImpl(Ark_NativePointer node,
                      const Ark_Union_ResourceColor_EdgeColors_LocalizedEdgeColors* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto borderColorsOpt = Converter::OptConvert<BorderColorProperty>(*value);
    ViewAbstract::SetOuterBorderColor(frameNode, borderColorsOpt.value_or(BorderColorProperty()));
}
void OutlineRadiusImpl(Ark_NativePointer node,
                       const Ark_Union_Dimension_OutlineRadiuses* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto borderRadiusOpt = Converter::OptConvert<BorderRadiusProperty>(*value);
    ViewAbstract::SetOuterBorderRadius(frameNode, borderRadiusOpt.value_or(BorderRadiusProperty()));
}

void ForegroundColorImpl(Ark_NativePointer node,
                         const Ark_Union_ResourceColor_ColoringStrategy* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto var = Converter::OptConvert<ColorOrStrategy>(*value);
    if (var && var->index() == 1) {
        const auto& color = std::get<1>(*var);
        if (color) {
            ViewAbstract::SetForegroundColor(frameNode, color.value());
        } else {
            LOGI("#### CommonMethod::ForegroundColorImpl: color is empty");
        }
    } else {
        LOGE("#### CommonMethod::ForegroundColorImpl: strategy handling is not implemented!");
    }
}
void OnClick0Impl(Ark_NativePointer node,
                  const Callback_ClickEvent_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto onClick = [callback = CallbackHelper(*value)](GestureEvent& info) {
        callback.Invoke(Converter::ArkValue<Ark_ClickEvent>(info));
    };
    NG::ViewAbstract::SetOnClick(frameNode, std::move(onClick));
}
void OnClick1Impl(Ark_NativePointer node,
                  const Callback_ClickEvent_Void* event,
                  const Ark_Number* distanceThreshold)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(event);
    CHECK_NULL_VOID(distanceThreshold);
    auto onEvent = [callback = CallbackHelper(*event)](GestureEvent& info) {
        callback.Invoke(Converter::ArkValue<Ark_ClickEvent>(info));
    };
    auto convValue = Converter::Convert<float>(*distanceThreshold);

    if (frameNode->GetTag() == "Span") {
        SpanModelNG::SetOnClick(reinterpret_cast<UINode *>(node), std::move(onEvent));
    } else {
        ViewAbstract::SetOnClick(frameNode, std::move(onEvent), convValue);
    }
}
void OnHoverImpl(Ark_NativePointer node,
                 const Callback_Boolean_HoverEvent_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CommonMethodModelNG::SetOnHover(frameNode, convValue);
}
void OnAccessibilityHoverImpl(Ark_NativePointer node,
                              const AccessibilityCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CommonMethodModelNG::SetOnAccessibilityHover(frameNode, convValue);
}
void HoverEffectImpl(Ark_NativePointer node,
                     Ark_HoverEffect value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto hoverEffect = Converter::OptConvert<OHOS::Ace::HoverEffectType>(value);
    if (hoverEffect) {
        ViewAbstract::SetHoverEffect(frameNode, hoverEffect.value());
    }
}
void OnMouseImpl(Ark_NativePointer node,
                 const Callback_MouseEvent_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CommonMethodModelNG::SetOnMouse(frameNode, convValue);
}
void OnTouchImpl(Ark_NativePointer node,
                 const Callback_TouchEvent_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto onEvent = [frameNode](TouchEventInfo& eventInfo) {
        Ark_TouchEvent onTouch{};
        onTouch.axisHorizontal.tag = Ark_Tag::ARK_TAG_UNDEFINED;
        onTouch.axisVertical.tag = Ark_Tag::ARK_TAG_UNDEFINED;
        onTouch.changedTouches.array = nullptr;
        onTouch.changedTouches.length = 0;
        auto changedTouches = eventInfo.GetChangedTouches();
        if (!changedTouches.empty()) {
            std::vector<Ark_TouchObject> array;
            for (auto& info : changedTouches) {
                array.push_back(Converter::ArkValue<Ark_TouchObject>(info));
            }
            onTouch.changedTouches.array = &array[0];
            onTouch.changedTouches.length = changedTouches.size();
        }
        onTouch.pressure.tag = Ark_Tag::ARK_TAG_FLOAT32;
        onTouch.pressure.f32 = 0.0f;
        onTouch.source = static_cast<Ark_SourceType>(eventInfo.GetSourceDevice());
        onTouch.sourceTool = static_cast<Ark_SourceTool>(0);
        onTouch.target.area.globalPosition.x.tag = Ark_Tag::ARK_TAG_UNDEFINED;
        onTouch.target.area.globalPosition.y.tag = Ark_Tag::ARK_TAG_UNDEFINED;
        onTouch.target.area.height.type = 0;
        onTouch.target.area.height.unit = 1;
        onTouch.target.area.height.value = 0;
        onTouch.target.area.width.type = 0;
        onTouch.target.area.width.unit = 1;
        onTouch.target.area.width.value = 0;
        onTouch.target.area.position.x.tag = Ark_Tag::ARK_TAG_UNDEFINED;
        onTouch.target.area.position.y.tag = Ark_Tag::ARK_TAG_UNDEFINED;
        onTouch.tiltX.tag = Ark_Tag::ARK_TAG_FLOAT32;
        onTouch.tiltX.f32 = 0;
        onTouch.tiltY.tag = Ark_Tag::ARK_TAG_FLOAT32;
        onTouch.tiltY.f32 = 0;
        onTouch.timestamp.tag = Ark_Tag::ARK_TAG_INT32;
        onTouch.timestamp.i32 = eventInfo.GetTimeStamp().time_since_epoch().count();
        onTouch.type = static_cast<Ark_TouchType>(0);
        onTouch.touches.array = nullptr;
        onTouch.touches.length = 0;
        auto touches = eventInfo.GetTouches();
        if (!touches.empty()) {
            std::vector<Ark_TouchObject> array;
            for (auto& info : touches) {
                array.push_back(Converter::ArkValue<Ark_TouchObject>(info));
            }
            onTouch.touches.array = &array[0];
            onTouch.touches.length = touches.size();
        }

        GetFullAPI()->getEventsAPI()->getCommonMethodEventsReceiver()->onTouch(frameNode->GetId(), onTouch);
    };
    ViewAbstract::SetOnTouch(frameNode, std::move(onEvent));
}
void OnKeyEventImpl(Ark_NativePointer node,
                    const Callback_KeyEvent_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CommonMethodModelNG::SetOnKeyEvent(frameNode, convValue);
}
void OnKeyPreImeImpl(Ark_NativePointer node,
                     const Callback_KeyEvent_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CommonMethodModelNG::SetOnKeyPreIme(frameNode, convValue);
}
void FocusableImpl(Ark_NativePointer node,
                   Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::SetFocusable(frameNode, static_cast<bool>(value));
}
void OnFocusImpl(Ark_NativePointer node,
                 const Callback_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto onEvent = [frameNode]() {
        GetFullAPI()->getEventsAPI()->getCommonMethodEventsReceiver()->onFocus(frameNode->GetId());
    };
    ViewAbstract::SetOnFocus(frameNode, std::move(onEvent));
}
void OnBlurImpl(Ark_NativePointer node,
                const Callback_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto onEvent = [frameNode]() {
        GetFullAPI()->getEventsAPI()->getCommonMethodEventsReceiver()->onBlur(frameNode->GetId());
    };
    ViewAbstract::SetOnBlur(frameNode, std::move(onEvent));
}
void TabIndexImpl(Ark_NativePointer node,
                  const Ark_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CommonMethodModelNG::SetTabIndex(frameNode, convValue);
}
void DefaultFocusImpl(Ark_NativePointer node,
                      Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::Convert<bool>(value);
    //CommonMethodModelNG::SetDefaultFocus(frameNode, convValue);
}
void GroupDefaultFocusImpl(Ark_NativePointer node,
                           Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::Convert<bool>(value);
    //CommonMethodModelNG::SetGroupDefaultFocus(frameNode, convValue);
}
void FocusOnTouchImpl(Ark_NativePointer node,
                      Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::Convert<bool>(value);
    //CommonMethodModelNG::SetFocusOnTouch(frameNode, convValue);
}
void FocusBoxImpl(Ark_NativePointer node,
                  const Ark_FocusBoxStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CommonMethodModelNG::SetFocusBox(frameNode, convValue);
}
void AnimationImpl(Ark_NativePointer node,
                   const Ark_AnimateParam* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);

    if (frameNode->IsFirstBuilding()) {
        // the node sets attribute value for the first time. No animation is generated.
        return;
    }

    auto container = Container::CurrentSafely();
    CHECK_NULL_VOID(container);
    auto pipelineContextBase = container->GetPipelineContext();
    CHECK_NULL_VOID(pipelineContextBase);
    if (pipelineContextBase->IsFormAnimationFinishCallback() && pipelineContextBase->IsFormRender() &&
        GetFormAnimationTimeInterval(pipelineContextBase) > DEFAULT_DURATION) {
        TAG_LOGW(
            AceLogTag::ACE_FORM, "[Form animation] Form finish callback triggered animation cannot exceed 1000ms.");
        return;
    }

    if (value) {
        AnimationOption option = Converter::Convert<AnimationOption>(*value);
        Validator::ValidateAnimationOption(option, pipelineContextBase->IsFormRender());

        if (pipelineContextBase->IsFormAnimationFinishCallback() && pipelineContextBase->IsFormRender() &&
            option.GetDuration() > (DEFAULT_DURATION - GetFormAnimationTimeInterval(pipelineContextBase))) {
            option.SetDuration(DEFAULT_DURATION - GetFormAnimationTimeInterval(pipelineContextBase));
            TAG_LOGW(AceLogTag::ACE_FORM, "[Form animation]  Form animation SetDuration: %{public}lld ms",
                static_cast<long long>(DEFAULT_DURATION - GetFormAnimationTimeInterval(pipelineContextBase)));
        }

        LOGI("ARKOALA CommonMethod::AnimationImpl: onFinish callback don`t supported yet");
        // we need to support onFinish callback and set it to options:

        if (SystemProperties::GetRosenBackendEnabled()) {
            option.SetAllowRunningAsynchronously(true);
        }
        ViewContextModelNG::openAnimationInternal(option);
    } else {
        AnimationOption option = AnimationOption();
        ViewContextModelNG::closeAnimationInternal(option, true);
    }
}
void Transition0Impl(Ark_NativePointer node,
                     const Ark_Union_TransitionOptions_TransitionEffect* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CommonMethodModelNG::SetTransition0(frameNode, convValue);
}
void Transition1Impl(Ark_NativePointer node,
                     const Ark_Materialized* effect,
                     const Ark_Union_TransitionFinishCallback_Undefined* onFinish)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(effect);
    //auto convValue = Converter::Convert<type>(effect);
    //auto convValue = Converter::OptConvert<type>(effect); // for enums
    //CommonMethodModelNG::SetTransition1(frameNode, convValue);
}
void MotionBlurImpl(Ark_NativePointer node,
                    const Ark_MotionBlurOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CommonMethodModelNG::SetMotionBlur(frameNode, convValue);
}
void BrightnessImpl(Ark_NativePointer node,
                    const Ark_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = value
        ? std::optional(Dimension(Converter::Convert<float>(*value))) : std::nullopt;
    Validator::ValidateNonNegative(convValue);
    ViewAbstract::SetBrightness(frameNode, convValue);
}
void ContrastImpl(Ark_NativePointer node,
                  const Ark_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = value
        ? std::optional(Dimension(Converter::Convert<float>(*value))) : std::nullopt;
    Validator::ValidateNonNegative(convValue);
    ViewAbstract::SetContrast(frameNode, convValue);
}
void GrayscaleImpl(Ark_NativePointer node,
                   const Ark_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = value
        ? std::optional(Dimension(Converter::Convert<float>(*value))) : std::nullopt;
    Validator::ValidateNonNegative(convValue);
    ViewAbstract::SetGrayScale(frameNode, convValue);
}
void ColorBlendImpl(Ark_NativePointer node,
                    const Ark_Union_Color_String_Resource* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CommonMethodModelNG::SetColorBlend(frameNode, convValue);
}
void SaturateImpl(Ark_NativePointer node,
                  const Ark_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = value
        ? std::optional(Dimension(Converter::Convert<float>(*value))) : std::nullopt;
    Validator::ValidateNonNegative(convValue);
    ViewAbstract::SetSaturate(frameNode, convValue);
}
void SepiaImpl(Ark_NativePointer node,
               const Ark_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = value
        ? std::optional(Dimension(Converter::Convert<float>(*value))) : std::nullopt;
    Validator::ValidateNonNegative(convValue);
    ViewAbstract::SetSepia(frameNode, convValue);
}
void InvertImpl(Ark_NativePointer node,
                const Ark_Union_Number_InvertOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CommonMethodModelNG::SetInvert(frameNode, convValue);
}
void HueRotateImpl(Ark_NativePointer node,
                   const Ark_Union_Number_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CommonMethodModelNG::SetHueRotate(frameNode, convValue);
}
void UseShadowBatchingImpl(Ark_NativePointer node,
                           Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::Convert<bool>(value);
    ViewAbstract::SetUseShadowBatching(frameNode, convValue);
}
void UseEffectImpl(Ark_NativePointer node,
                   Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::Convert<bool>(value);
    ViewAbstract::SetUseEffect(frameNode, convValue);
}
void RenderGroupImpl(Ark_NativePointer node,
                     Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::Convert<bool>(value);
    ViewAbstract::SetRenderGroup(frameNode, convValue);
}
void FreezeImpl(Ark_NativePointer node,
                Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    // auto convValue = Converter::Convert<bool>(value);
    // ViewAbstract::SetFreeze(frameNode, convValue);
}
void TranslateImpl(Ark_NativePointer node,
                   const Ark_TranslateOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);

    TranslateOpt options = Converter::Convert<TranslateOpt>(*value);

    CalcDimension x = options.x.value_or(CalcDimension(0.0));
    CalcDimension y = options.y.value_or(CalcDimension(0.0));
    CalcDimension z = options.z.value_or(CalcDimension(0.0));
    ViewAbstract::SetTranslate(frameNode, TranslateOptions(x, y, z));
}
void ScaleImpl(Ark_NativePointer node,
               const Ark_ScaleOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);

    ScaleOpt scaleOptions = Converter::Convert<ScaleOpt>(*value);

    float scaleX = scaleOptions.x.value_or(1.0f);
    float scaleY = scaleOptions.y.value_or(1.0f);
    ViewAbstract::SetScale(frameNode, VectorF(scaleX, scaleY));

    CalcDimension centerX = scaleOptions.centerX.value_or(0.5_pct);
    CalcDimension centerY = scaleOptions.centerY.value_or(0.5_pct);
    ViewAbstract::SetPivot(frameNode, DimensionOffset(centerX, centerY));
}
void GridSpanImpl(Ark_NativePointer node,
                  const Ark_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CommonMethodModelNG::SetGridSpan(frameNode, convValue);
}
void GridOffsetImpl(Ark_NativePointer node,
                    const Ark_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CommonMethodModelNG::SetGridOffset(frameNode, convValue);
}
void RotateImpl(Ark_NativePointer node,
                const Ark_RotateOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CommonMethodModelNG::SetRotate(frameNode, convValue);
}
void TransformImpl(Ark_NativePointer node,
                   const Ark_CustomObject* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CommonMethodModelNG::SetTransform(frameNode, convValue);
}
void OnAppearImpl(Ark_NativePointer node,
                  const Callback_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto onEvent = [frameNode]() {
        GetFullAPI()->getEventsAPI()->getCommonMethodEventsReceiver()->onAppear(frameNode->GetId());
    };
    ViewAbstract::SetOnAppear(frameNode, std::move(onEvent));
}
void OnDisAppearImpl(Ark_NativePointer node,
                     const Callback_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto onEvent = [frameNode]() {
        GetFullAPI()->getEventsAPI()->getCommonMethodEventsReceiver()->onDisAppear(frameNode->GetId());
    };
    ViewAbstract::SetOnDisappear(frameNode, std::move(onEvent));
}
void OnAttachImpl(Ark_NativePointer node,
                  const Callback_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CommonMethodModelNG::SetOnAttach(frameNode, convValue);
}
void OnDetachImpl(Ark_NativePointer node,
                  const Callback_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CommonMethodModelNG::SetOnDetach(frameNode, convValue);
}
void OnAreaChangeImpl(Ark_NativePointer node,
                      const Callback_Area_Area_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto onEvent = [frameNode](
        const Rect& oldRect, const Offset& oldOrigin, const Rect& rect, const Offset& origin) {
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
        auto previousOffset = oldRect.GetOffset();

        Ark_Area previous;
        previous.width.unit = static_cast<int32_t>(DimensionUnit::VP);
        previous.width.value = static_cast<float>(PipelineBase::Px2VpWithCurrentDensity(oldRect.Width()));
        previous.height.unit = static_cast<int32_t>(DimensionUnit::VP);
        previous.height.value = static_cast<float>(PipelineBase::Px2VpWithCurrentDensity(oldRect.Height()));
        previous.position.x.value.unit = static_cast<int32_t>(DimensionUnit::VP);
        previous.position.x.value.value = static_cast<float>(PipelineBase::Px2VpWithCurrentDensity(
            previousOffset.GetX()));
        previous.position.y.value.unit = static_cast<int32_t>(DimensionUnit::VP);
        previous.position.y.value.value = static_cast<float>(PipelineBase::Px2VpWithCurrentDensity(
            previousOffset.GetY()));
        previous.globalPosition.x.value.unit = static_cast<int32_t>(DimensionUnit::VP);
        previous.globalPosition.x.value.value = static_cast<float>(PipelineBase::Px2VpWithCurrentDensity(
            previousOffset.GetX() + oldOrigin.GetX()));
        previous.globalPosition.y.value.unit = static_cast<int32_t>(DimensionUnit::VP);
        previous.globalPosition.y.value.value = static_cast<float>(PipelineBase::Px2VpWithCurrentDensity(
            previousOffset.GetY() + oldOrigin.GetY()));

        Ark_Area current;
        auto currentOffset = rect.GetOffset();
        current.width.unit = static_cast<int32_t>(DimensionUnit::VP);
        current.width.value = static_cast<float>(PipelineBase::Px2VpWithCurrentDensity(rect.Width()));
        current.height.unit = static_cast<int32_t>(DimensionUnit::VP);
        current.height.value = static_cast<float>(PipelineBase::Px2VpWithCurrentDensity(rect.Height()));
        current.position.x.value.unit = static_cast<int32_t>(DimensionUnit::VP);
        current.position.x.value.value = static_cast<float>(PipelineBase::Px2VpWithCurrentDensity(
            currentOffset.GetX()));
        current.position.y.value.unit = static_cast<int32_t>(DimensionUnit::VP);
        current.position.y.value.value = static_cast<float>(PipelineBase::Px2VpWithCurrentDensity(
            currentOffset.GetY()));
        current.globalPosition.x.value.unit = static_cast<int32_t>(DimensionUnit::VP);
        current.globalPosition.x.value.value = static_cast<float>(PipelineBase::Px2VpWithCurrentDensity(
            currentOffset.GetX() + origin.GetX()));
        current.globalPosition.y.value.unit = static_cast<int32_t>(DimensionUnit::VP);
        current.globalPosition.y.value.value = static_cast<float>(PipelineBase::Px2VpWithCurrentDensity(
            currentOffset.GetY() + origin.GetY()));

        GetFullAPI()->getEventsAPI()->getCommonMethodEventsReceiver()->onAreaChange(
            frameNode->GetId(), previous, current);
    };
    auto areaChangeCallback = [areaChangeFunc = std::move(onEvent)](const RectF& oldRect,
                                  const OffsetF& oldOrigin, const RectF& rect, const OffsetF& origin) {
        areaChangeFunc(Rect(oldRect.GetX(), oldRect.GetY(), oldRect.Width(), oldRect.Height()),
            Offset(oldOrigin.GetX(), oldOrigin.GetY()), Rect(rect.GetX(), rect.GetY(), rect.Width(), rect.Height()),
            Offset(origin.GetX(), origin.GetY()));
    };
    ViewAbstract::SetOnAreaChanged(frameNode, std::move(areaChangeCallback));
}
void VisibilityImpl(Ark_NativePointer node,
                    Ark_Visibility value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::SetVisibility(frameNode, static_cast<VisibleType>(value));
}
void FlexGrowImpl(Ark_NativePointer node,
                  const Ark_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CommonMethodModelNG::SetFlexGrow(frameNode, convValue);
}
void FlexShrinkImpl(Ark_NativePointer node,
                    const Ark_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CommonMethodModelNG::SetFlexShrink(frameNode, convValue);
}
void FlexBasisImpl(Ark_NativePointer node,
                   const Ark_Union_Number_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CommonMethodModelNG::SetFlexBasis(frameNode, convValue);
}
void AlignSelfImpl(Ark_NativePointer node,
                   Ark_ItemAlign value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto align = Converter::OptConvert<OHOS::Ace::FlexAlign>(value);
    if (align) {
        ViewAbstract::SetAlignSelf(frameNode, align.value());
    }
}
void DisplayPriorityImpl(Ark_NativePointer node,
                         const Ark_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto result = Converter::OptConvert<int>(*value);
    if (result) {
        ViewAbstract::SetDisplayIndex(frameNode, result.value());
    }
}
void ZIndexImpl(Ark_NativePointer node,
                const Ark_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto result = Converter::OptConvert<int>(*value);
    if (result) {
        ViewAbstract::SetZIndex(frameNode, result.value());
    }
}
void DirectionImpl(Ark_NativePointer node,
                   Ark_Direction value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto direction = Converter::OptConvert<TextDirection>(value);
    if (direction) {
        ViewAbstract::SetLayoutDirection(frameNode, direction.value());
    }
}
void AlignImpl(Ark_NativePointer node,
               Ark_Alignment value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto alignment = Converter::OptConvert<Alignment>(value);
    if (alignment) {
        ViewAbstract::SetAlign(frameNode, alignment.value());
    }
}
void PositionImpl(Ark_NativePointer node,
                  const Ark_Union_Position_Edges_LocalizedEdges* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    switch (value->selector) {
        case CASE_0: {
            auto x = Converter::ConvertOrDefault(value->value0.x, Dimension());
            auto y = Converter::ConvertOrDefault(value->value0.y, Dimension());
            ViewAbstract::SetPosition(frameNode, { x, y });
            break;
        }
        case CASE_1: {
            auto result = Converter::ConvertOrDefault(value->value1, EdgesParam());
            ViewAbstract::SetPositionEdges(frameNode, result);
            break;
        }
        case CASE_2:
            LOGE("ARKOALA: LocalizedEdges is not fully support.");
            ViewAbstract::SetPositionLocalizedEdges(frameNode, true);
            break;

        default:
            LOGE("ARKOALA:PositionImpl: Unexpected value->selector: %{public}d\n", value->selector);
            return;
    }
}
void MarkAnchorImpl(Ark_NativePointer node,
                    const Ark_Union_Position_LocalizedPosition* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CommonMethodModelNG::SetMarkAnchor(frameNode, convValue);
}
void OffsetImpl(Ark_NativePointer node,
                const Ark_Union_Position_Edges_LocalizedEdges* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto varOpt = Converter::OptConvert<OffsetOrEdgesParam>(*value);
    CHECK_NULL_VOID(varOpt);
    if (auto offset = std::get_if<std::optional<OffsetT<Dimension>>>(&varOpt.value()); offset) {
        ViewAbstract::SetOffset(frameNode, offset->value());
    } else if (auto edges = std::get_if<std::optional<EdgesParamOptions>>(&varOpt.value()); edges) {
        ViewAbstract::SetOffsetEdges(frameNode, edges->value().value);
        ViewAbstract::SetOffsetLocalizedEdges(frameNode, edges->value().isLocalized);
    } else {
        LOGE("ARKOALA CommonMethod::OffsetImpl: incorrect value");
    }
}
void EnabledImpl(Ark_NativePointer node,
                 Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::SetEnabled(frameNode, static_cast<bool>(value));
}
void UseSizeTypeImpl(Ark_NativePointer node,
                     const Ark_Literal_Union_Number_Literal_Number_offset_span_lg_md_sm_xs* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CommonMethodModelNG::SetUseSizeType(frameNode, convValue);
}
void AlignRules0Impl(Ark_NativePointer node,
                     const Ark_AlignRuleOption* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CommonMethodModelNG::SetAlignRules0(frameNode, convValue);
}
void AlignRules1Impl(Ark_NativePointer node,
                     const Ark_LocalizedAlignRuleOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CommonMethodModelNG::SetAlignRules1(frameNode, convValue);
}
void AspectRatioImpl(Ark_NativePointer node,
                     const Ark_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto result = Converter::OptConvert<float>(*value);
    if (result) {
        auto ratio = result.value();
        if (ratio <= 0.0) {
            if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_TEN)) {
                ViewAbstract::ResetAspectRatio(frameNode);
                return;
            } else {
                ratio = 1.0;
            }
        }
        ViewAbstract::SetAspectRatio(frameNode, ratio);
    }
}
void ClickEffectImpl(Ark_NativePointer node,
                     const Ark_Union_ClickEffect_Undefined* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CommonMethodModelNG::SetClickEffect(frameNode, convValue);
}
void OnDragStartImpl(Ark_NativePointer node,
                     const Callback_DragEvent_String_Union_CustomBuilder_DragItemInfo* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CommonMethodModelNG::SetOnDragStart(frameNode, convValue);
}
void OnDragEnterImpl(Ark_NativePointer node,
                     const Callback_DragEvent_String_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CommonMethodModelNG::SetOnDragEnter(frameNode, convValue);
}
void OnDragMoveImpl(Ark_NativePointer node,
                    const Callback_DragEvent_String_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CommonMethodModelNG::SetOnDragMove(frameNode, convValue);
}
void OnDragLeaveImpl(Ark_NativePointer node,
                     const Callback_DragEvent_String_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CommonMethodModelNG::SetOnDragLeave(frameNode, convValue);
}
void OnDropImpl(Ark_NativePointer node,
                const Callback_DragEvent_String_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CommonMethodModelNG::SetOnDrop(frameNode, convValue);
}
void OnDragEndImpl(Ark_NativePointer node,
                   const Callback_DragEvent_String_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CommonMethodModelNG::SetOnDragEnd(frameNode, convValue);
}
void AllowDropImpl(Ark_NativePointer node,
                   const Ark_Union_Array_UniformDataType_Undefined* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CommonMethodModelNG::SetAllowDrop(frameNode, convValue);
}
void DraggableImpl(Ark_NativePointer node,
                   Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::Convert<bool>(value);
    //CommonMethodModelNG::SetDraggable(frameNode, convValue);
}
void DragPreviewImpl(Ark_NativePointer node,
                     const Ark_Union_CustomBuilder_DragItemInfo_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CommonMethodModelNG::SetDragPreview(frameNode, convValue);
}
void OnPreDragImpl(Ark_NativePointer node,
                   const Callback_PreDragStatus_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CommonMethodModelNG::SetOnPreDrag(frameNode, convValue);
}
void LinearGradientImpl(Ark_NativePointer node,
                        const Ark_Type_CommonMethod_linearGradient_value* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    Gradient gradient;
    gradient.CreateGradientWithType(GradientType::LINEAR);
    auto repeat = Converter::OptConvert<bool>(value->repeating);
    if (repeat) {
        gradient.SetRepeat(repeat.value());
    }
    auto linear = gradient.GetLinearGradient();
    linear->angle = Converter::OptConvert<Dimension>(value->angle);
    auto direction = Converter::OptConvert<GradientDirection>(value->direction);
    if (direction) {
        Converter::AssignLinearGradientDirection(linear, direction.value());
    }
    Converter::AssignGradientColors(&gradient, &value->colors);
    ViewAbstract::SetLinearGradient(frameNode, gradient);
}
void SweepGradientImpl(Ark_NativePointer node,
                       const Ark_Type_CommonMethod_sweepGradient_value* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    Gradient gradient;
    gradient.CreateGradientWithType(GradientType::SWEEP);
    auto repeat = Converter::OptConvert<bool>(value->repeating);
    if (repeat) {
        gradient.SetRepeat(repeat.value());
    }
    auto sweep = gradient.GetSweepGradient();
    auto centerX = Converter::OptConvert<Dimension>(value->center.value0);
    auto centerY = Converter::OptConvert<Dimension>(value->center.value1);
    auto startAngle = Converter::OptConvert<Dimension>(value->start);
    auto endAngle = Converter::OptConvert<Dimension>(value->end);
    auto rotation = Converter::OptConvert<Dimension>(value->rotation);
    if (centerX) sweep->centerX = centerX.value();
    if (centerY) sweep->centerY = centerY.value();
    if (startAngle) sweep->startAngle = startAngle.value();
    if (endAngle) sweep->endAngle = endAngle.value();
    if (rotation) sweep->rotation = rotation.value();
    Converter::AssignGradientColors(&gradient, &value->colors);
    ViewAbstract::SetSweepGradient(frameNode, gradient);
}
void RadialGradientImpl(Ark_NativePointer node,
                        const Ark_Type_CommonMethod_radialGradient_value* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    Gradient gradient = Converter::Convert<Gradient>(*value);
    ViewAbstract::SetRadialGradient(frameNode, gradient);
}
void MotionPathImpl(Ark_NativePointer node,
                    const Ark_MotionPathOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CommonMethodModelNG::SetMotionPath(frameNode, convValue);
}
void ShadowImpl(Ark_NativePointer node,
                const Ark_Union_ShadowOptions_ShadowStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto shadow = Converter::OptConvert<Shadow>(*value);
    if (shadow) {
        ViewAbstract::SetBackShadow(frameNode, shadow.value());
    }
}
void Clip0Impl(Ark_NativePointer node,
               Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::SetClipEdge(frameNode, Converter::Convert<bool>(value));
}
void Clip1Impl(Ark_NativePointer node,
               const Ark_Type_CommonMethod_clip_value* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    LOGE("ARKOALA CommonMethod::Clip1Impl: Deprecated interface!");
    if (!value) {
        ViewAbstract::SetClipEdge(frameNode, false);
        return;
    }
    auto clipTypeOpt = Converter::OptConvert<ClipType>(*value);
    if (clipTypeOpt) {
        if (auto arkBool = std::get_if<Ark_Boolean>(&clipTypeOpt.value()); arkBool) {
            ViewAbstract::SetClipEdge(frameNode, Converter::Convert<bool>(*arkBool));
            return;
        } else if (auto arkCircle = std::get_if<Ark_CircleAttribute>(&clipTypeOpt.value()); arkCircle) {
            LOGE("ARKOALA CommonMethod::Clip1Impl: Ark_CircleAttribute is not supported yet!");
        } else if (auto arkEllipse = std::get_if<Ark_EllipseAttribute>(&clipTypeOpt.value()); arkEllipse) {
            LOGE("ARKOALA CommonMethod::Clip1Impl: Ark_EllipseAttribute is not supported yet!");
        } else if (auto arkPath = std::get_if<Ark_PathAttribute>(&clipTypeOpt.value()); arkPath) {
            LOGE("ARKOALA CommonMethod::Clip1Impl: Ark_PathAttribute is not supported yet!");
        } else if (auto arkRect = std::get_if<Ark_RectAttribute>(&clipTypeOpt.value()); arkRect) {
            LOGE("ARKOALA CommonMethod::Clip1Impl: Ark_RectAttribute is not supported yet!");
        }
    }
    ViewAbstract::SetClipEdge(frameNode, false);
}
void ClipShapeImpl(Ark_NativePointer node,
                   const Ark_Union_CircleShape_EllipseShape_PathShape_RectShape* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CommonMethodModelNG::SetClipShape(frameNode, convValue);
}
void Mask0Impl(Ark_NativePointer node,
               const Ark_Materialized* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CommonMethodModelNG::SetMask0(frameNode, convValue);
}
void Mask1Impl(Ark_NativePointer node,
               const Ark_Type_CommonMethod_mask_value* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CommonMethodModelNG::SetMask1(frameNode, convValue);
}
void MaskShapeImpl(Ark_NativePointer node,
                   const Ark_Union_CircleShape_EllipseShape_PathShape_RectShape* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CommonMethodModelNG::SetMaskShape(frameNode, convValue);
}
void KeyImpl(Ark_NativePointer node,
             const Ark_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto convValue = Converter::Convert<std::string>(*value);
    //CommonMethodModelNG::SetKey(frameNode, convValue);
}
void IdImpl(Ark_NativePointer node,
            const Ark_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    std::string id = Converter::Convert<std::string>(*value);
    if (id.empty()) {
        return;
    }
    ViewAbstract::SetInspectorId(frameNode, id);
}
void GeometryTransition0Impl(Ark_NativePointer node,
                             const Ark_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto convValue = Converter::Convert<std::string>(*value);
    //CommonMethodModelNG::SetGeometryTransition0(frameNode, convValue);
}
void GeometryTransition1Impl(Ark_NativePointer node,
                             const Ark_String* id,
                             const Opt_GeometryTransitionOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(id);
    //auto convValue = Converter::OptConvert<type>(id); // for enums
    //CommonMethodModelNG::SetGeometryTransition1(frameNode, convValue);
}
void StateStylesImpl(Ark_NativePointer node,
                     const Ark_StateStyles* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CommonMethodModelNG::SetStateStyles(frameNode, convValue);
}
void RestoreIdImpl(Ark_NativePointer node,
                   const Ark_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CommonMethodModelNG::SetRestoreId(frameNode, convValue);
}
void SphericalEffectImpl(Ark_NativePointer node,
                         const Ark_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CommonMethodModelNG::SetSphericalEffect(frameNode, convValue);
}
void LightUpEffectImpl(Ark_NativePointer node,
                       const Ark_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CommonMethodModelNG::SetLightUpEffect(frameNode, convValue);
}
void PixelStretchEffectImpl(Ark_NativePointer node,
                            const Ark_PixelStretchEffectOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CommonMethodModelNG::SetPixelStretchEffect(frameNode, convValue);
}
void AccessibilityGroupImpl(Ark_NativePointer node,
                            Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::Convert<bool>(value);
    //CommonMethodModelNG::SetAccessibilityGroup(frameNode, convValue);
}
void AccessibilityText0Impl(Ark_NativePointer node,
                            const Ark_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto convValue = Converter::Convert<std::string>(*value);
    //CommonMethodModelNG::SetAccessibilityText0(frameNode, convValue);
}
void AccessibilityText1Impl(Ark_NativePointer node,
                            const Ark_Resource* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CommonMethodModelNG::SetAccessibilityText1(frameNode, convValue);
}
void AccessibilityTextHintImpl(Ark_NativePointer node,
                               const Ark_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto convValue = Converter::Convert<std::string>(*value);
    //CommonMethodModelNG::SetAccessibilityTextHint(frameNode, convValue);
}
void AccessibilityDescription0Impl(Ark_NativePointer node,
                                   const Ark_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto convValue = Converter::Convert<std::string>(*value);
    //CommonMethodModelNG::SetAccessibilityDescription0(frameNode, convValue);
}
void AccessibilityDescription1Impl(Ark_NativePointer node,
                                   const Ark_Resource* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CommonMethodModelNG::SetAccessibilityDescription1(frameNode, convValue);
}
void AccessibilityLevelImpl(Ark_NativePointer node,
                            const Ark_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto convValue = Converter::Convert<std::string>(*value);
    //CommonMethodModelNG::SetAccessibilityLevel(frameNode, convValue);
}
void AccessibilityVirtualNodeImpl(Ark_NativePointer node,
                                  const Callback_Any* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CommonMethodModelNG::SetAccessibilityVirtualNode(frameNode, convValue);
}
void ObscuredImpl(Ark_NativePointer node,
                  const Array_ObscuredReasons* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CommonMethodModelNG::SetObscured(frameNode, convValue);
}
void ReuseIdImpl(Ark_NativePointer node,
                 const Ark_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto convValue = Converter::Convert<std::string>(*value);
    //CommonMethodModelNG::SetReuseId(frameNode, convValue);
}
void RenderFitImpl(Ark_NativePointer node,
                   Ark_RenderFit value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(value);
    //auto convValue = Converter::OptConvert<type>(value); // for enums
    //CommonMethodModelNG::SetRenderFit(frameNode, convValue);
}
void GestureModifierImpl(Ark_NativePointer node,
                         const Ark_Materialized* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CommonMethodModelNG::SetGestureModifier(frameNode, convValue);
}
void BackgroundBrightnessImpl(Ark_NativePointer node,
                              const Ark_BackgroundBrightnessOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto rate = Converter::Convert<float>(value->rate);
    auto lightUpDegree = Converter::Convert<float>(value->lightUpDegree);
    ViewAbstract::SetDynamicLightUp(frameNode, rate, lightUpDegree);
}
void OnGestureJudgeBeginImpl(Ark_NativePointer node,
                             const Callback_GestureInfo_BaseGestureEvent_GestureJudgeResult* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CommonMethodModelNG::SetOnGestureJudgeBegin(frameNode, convValue);
}
void OnGestureRecognizerJudgeBeginImpl(Ark_NativePointer node,
                                       const GestureRecognizerJudgeBeginCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CommonMethodModelNG::SetOnGestureRecognizerJudgeBegin(frameNode, convValue);
}
void ShouldBuiltInRecognizerParallelWithImpl(Ark_NativePointer node,
                                             const ShouldBuiltInRecognizerParallelWithCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CommonMethodModelNG::SetShouldBuiltInRecognizerParallelWith(frameNode, convValue);
}
void MonopolizeEventsImpl(Ark_NativePointer node,
                          Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::Convert<bool>(value);
    //CommonMethodModelNG::SetMonopolizeEvents(frameNode, convValue);
}
void OnTouchInterceptImpl(Ark_NativePointer node,
                          const Callback_TouchEvent_HitTestMode* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CommonMethodModelNG::SetOnTouchIntercept(frameNode, convValue);
}
void OnSizeChangeImpl(Ark_NativePointer node,
                      const SizeChangeCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CommonMethodModelNG::SetOnSizeChange(frameNode, convValue);
}
void CustomPropertyImpl(Ark_NativePointer node,
                        const Ark_String* name,
                        const Ark_Union_Object_Undefined* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(name);
    //auto convValue = Converter::OptConvert<type>(name); // for enums
    //CommonMethodModelNG::SetCustomProperty(frameNode, convValue);
}
void ExpandSafeAreaImpl(Ark_NativePointer node,
                        const Opt_Array_SafeAreaType* types,
                        const Opt_Array_SafeAreaEdge* edges)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(types);
    //auto convValue = Converter::OptConvert<type>(types); // for enums
    //CommonMethodModelNG::SetExpandSafeArea(frameNode, convValue);
}
void BackgroundImpl(Ark_NativePointer node,
                    const Callback_Any* builder,
                    const Opt_Literal_Alignment_align* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(builder);
    //auto convValue = Converter::OptConvert<type>(builder); // for enums
    //CommonMethodModelNG::SetBackground(frameNode, convValue);
    LOGE("CommonMethodModifier::BackgroundImpl, not implemented due to no the CustomBuilder");
}
void BackgroundImageImpl(Ark_NativePointer node,
                         const Ark_Union_ResourceStr_PixelMap* src,
                         const Opt_ImageRepeat* repeat)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(src);
    LOGE("CommonMethodModifier::BackgroundImageImpl, the PixelMap support not implemented");
    std::optional<ImageSourceInfo> sourceInfo = Converter::OptConvert<ImageSourceInfo>(*src);
    ViewAbstract::SetBackgroundImage(frameNode, sourceInfo);

    auto imageRepeat = repeat ? Converter::OptConvert<ImageRepeat>(*repeat) : std::nullopt;
    ViewAbstract::SetBackgroundImageRepeat(frameNode, imageRepeat);
}
void BackgroundBlurStyleImpl(Ark_NativePointer node,
                             Ark_BlurStyle value,
                             const Opt_BackgroundBlurStyleOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    BlurStyleOption convValue;
    if (options) {
        if (auto opt = Converter::OptConvert<BlurStyleOption>(*options); opt) {
            convValue = *opt;
        }
    }
    if (auto style = Converter::OptConvert<BlurStyle>(value); style) {
        convValue.blurStyle = *style;
    }
    ViewAbstract::SetBackgroundBlurStyle(frameNode, convValue);
}
void ForegroundBlurStyleImpl(Ark_NativePointer node,
                             Ark_BlurStyle value,
                             const Opt_ForegroundBlurStyleOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    BlurStyleOption convValue;
    if (options) {
        if (auto opt = Converter::OptConvert<BlurStyleOption>(*options); opt) {
            convValue = *opt;
        }
    }
    if (auto style = Converter::OptConvert<BlurStyle>(value); style) {
        convValue.blurStyle = *style;
    }
    ViewAbstract::SetForegroundBlurStyle(frameNode, convValue);
}
void FocusScopeIdImpl(Ark_NativePointer node,
                      const Ark_String* id,
                      const Opt_Boolean* isGroup)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(id);
    //auto convValue = Converter::OptConvert<type>(id); // for enums
    //CommonMethodModelNG::SetFocusScopeId(frameNode, convValue);
}
void FocusScopePriorityImpl(Ark_NativePointer node,
                            const Ark_String* scopeId,
                            const Opt_FocusPriority* priority)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(scopeId);
    //auto convValue = Converter::OptConvert<type>(scopeId); // for enums
    //CommonMethodModelNG::SetFocusScopePriority(frameNode, convValue);
}
void GestureImpl(Ark_NativePointer node,
                 Ark_GestureControl_GestureType gesture,
                 const Opt_GestureMask* mask)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(gesture);
    //auto convValue = Converter::OptConvert<type>(gesture); // for enums
    //CommonMethodModelNG::SetGesture(frameNode, convValue);
}
void PriorityGestureImpl(Ark_NativePointer node,
                         Ark_GestureControl_GestureType gesture,
                         const Opt_GestureMask* mask)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(gesture);
    //auto convValue = Converter::OptConvert<type>(gesture); // for enums
    //CommonMethodModelNG::SetPriorityGesture(frameNode, convValue);
}
void ParallelGestureImpl(Ark_NativePointer node,
                         Ark_GestureControl_GestureType gesture,
                         const Opt_GestureMask* mask)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(gesture);
    //auto convValue = Converter::OptConvert<type>(gesture); // for enums
    //CommonMethodModelNG::SetParallelGesture(frameNode, convValue);
}
void BlurImpl(Ark_NativePointer node,
              const Ark_Number* value,
              const Opt_BlurOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto blur = Converter::OptConvert<float>(*value);
    auto blurOptions = Converter::OptConvert<BlurOption>(*options);
    if (blurOptions) {
        CalcDimension dimensionBlur(blur ? blur.value() : 0, DimensionUnit::PX);
        ViewAbstract::SetFrontBlur(frameNode, dimensionBlur, blurOptions.value());
    }
}
void LinearGradientBlurImpl(Ark_NativePointer node,
                            const Ark_Number* value,
                            const Ark_LinearGradientBlurOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(value);
    //auto convValue = Converter::OptConvert<type>(value); // for enums
    //CommonMethodModelNG::SetLinearGradientBlur(frameNode, convValue);
}
void SystemBarEffectImpl(Ark_NativePointer node)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(undefined);
    //auto convValue = Converter::OptConvert<type>(undefined); // for enums
    //CommonMethodModelNG::SetSystemBarEffect(frameNode, convValue);
}
void BackdropBlurImpl(Ark_NativePointer node,
                      const Ark_Number* value,
                      const Opt_BlurOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto radius = Converter::OptConvert<Dimension>(*value);
    auto option = nullptr == options ? std::nullopt : Converter::OptConvert<BlurOption>(*options);
    ViewAbstract::SetBackdropBlur(frameNode, radius, option);
}
void SharedTransitionImpl(Ark_NativePointer node,
                          const Ark_String* id,
                          const Opt_sharedTransitionOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(id);
    auto modelId = Converter::Convert<std::string>(*id);
    auto modelOptions = std::make_shared<SharedTransitionOption>();
    if (options) {
        if (auto transOpt = Converter::OptConvert<SharedTransitionOption>(*options); transOpt) {
            *modelOptions = std::move(*transOpt);
        }
    }
    ViewAbstract::SetSharedTransition(frameNode, modelId, modelOptions);
}
void ChainModeImpl(Ark_NativePointer node,
                   Ark_Axis direction,
                   Ark_ChainStyle style)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(direction);
    //auto convValue = Converter::OptConvert<type>(direction); // for enums
    //CommonMethodModelNG::SetChainMode(frameNode, convValue);
}
void DragPreviewOptionsImpl(Ark_NativePointer node,
                            const Ark_DragPreviewOptions* value,
                            const Opt_DragInteractionOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(value);
    //auto convValue = Converter::OptConvert<type>(value); // for enums
    //CommonMethodModelNG::SetDragPreviewOptions(frameNode, convValue);
}
void OverlayImpl(Ark_NativePointer node,
                 const Ark_Union_String_CustomBuilder_ComponentContent* value,
                 const Opt_OverlayOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto overlay = Converter::OptConvert<OverlayOptions>(*options);
    if (overlay) {
        Converter::VisitUnion(*value,
            [&overlay](const Ark_String& src) {overlay->content = Converter::Convert<std::string>(src);},
            [](const auto& src) {
                LOGE("OverlayImpl() CustomBuilder & ComponentContent not implemented");
            },
            []() {
                LOGE("OverlayImpl(): Invalid union argument");
            });
        ViewAbstract::SetOverlay(frameNode, overlay.value());
    }
}
void BlendModeImpl(Ark_NativePointer node,
                   Ark_BlendMode value,
                   const Opt_BlendApplyType* type)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(value);
    //auto convValue = Converter::OptConvert<type>(value); // for enums
    //CommonMethodModelNG::SetBlendMode(frameNode, convValue);
}
void AdvancedBlendModeImpl(Ark_NativePointer node,
                           const Ark_Union_BlendMode_Blender* effect,
                           const Opt_BlendApplyType* type)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(effect);
    //auto convValue = Converter::OptConvert<type>(effect); // for enums
    //CommonMethodModelNG::SetAdvancedBlendMode(frameNode, convValue);
}
void BindPopupImpl(Ark_NativePointer node,
                   Ark_Boolean show,
                   const Ark_Union_PopupOptions_CustomPopupOptions* popup)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(show);
    //auto convValue = Converter::OptConvert<type>(show); // for enums
    //CommonMethodModelNG::SetBindPopup(frameNode, convValue);
}
void BindMenu0Impl(Ark_NativePointer node,
                   const Ark_Union_Array_MenuElement_CustomBuilder* content,
                   const Opt_MenuOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(content);
    //auto convValue = Converter::OptConvert<type>(content); // for enums
    //CommonMethodModelNG::SetBindMenu0(frameNode, convValue);
}
void BindMenu1Impl(Ark_NativePointer node,
                   Ark_Boolean isShow,
                   const Ark_Union_Array_MenuElement_CustomBuilder* content,
                   const Opt_MenuOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(isShow);
    //auto convValue = Converter::OptConvert<type>(isShow); // for enums
    //CommonMethodModelNG::SetBindMenu1(frameNode, convValue);
}
void BindContextMenu0Impl(Ark_NativePointer node,
                          const Callback_Any* content,
                          Ark_ResponseType responseType,
                          const Opt_ContextMenuOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(content);
    //auto convValue = Converter::OptConvert<type>(content); // for enums
    //CommonMethodModelNG::SetBindContextMenu0(frameNode, convValue);
}
void BindContextMenu1Impl(Ark_NativePointer node,
                          Ark_Boolean isShown,
                          const Callback_Any* content,
                          const Opt_ContextMenuOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(isShown);
    //auto convValue = Converter::OptConvert<type>(isShown); // for enums
    //CommonMethodModelNG::SetBindContextMenu1(frameNode, convValue);
}
void BindContentCover0Impl(Ark_NativePointer node,
                           const Ark_Union_Boolean_Undefined* isShow,
                           const Callback_Any* builder,
                           const Opt_ModalTransition* type)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(isShow);
    //auto convValue = Converter::OptConvert<type>(isShow); // for enums
    //CommonMethodModelNG::SetBindContentCover0(frameNode, convValue);
}
void BindContentCover1Impl(Ark_NativePointer node,
                           const Ark_Union_Boolean_Undefined* isShow,
                           const Callback_Any* builder,
                           const Opt_ContentCoverOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(isShow);
    //auto convValue = Converter::OptConvert<type>(isShow); // for enums
    //CommonMethodModelNG::SetBindContentCover1(frameNode, convValue);
}
void BindSheetImpl(Ark_NativePointer node,
                   const Ark_Union_Boolean_Undefined* isShow,
                   const Callback_Any* builder,
                   const Opt_SheetOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(isShow);
    //auto convValue = Converter::OptConvert<type>(isShow); // for enums
    //CommonMethodModelNG::SetBindSheet(frameNode, convValue);
}
void OnVisibleAreaChangeImpl(Ark_NativePointer node,
                             const Array_Number* ratios,
                             const VisibleAreaChangeCallback* event)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(ratios);
    CHECK_NULL_VOID(event);
    std::vector<float> rawRatioVec = Converter::Convert<std::vector<float>>(*ratios);
    size_t size = rawRatioVec.size();
    std::vector<double> ratioVec;
    for (size_t i = 0; i < size; i++) {
        double ratio = static_cast<double>(rawRatioVec[i]);
        if (LessOrEqual(ratio, VISIBLE_RATIO_MIN)) {
            ratio = VISIBLE_RATIO_MIN;
        }

        if (GreatOrEqual(ratio, VISIBLE_RATIO_MAX)) {
            ratio = VISIBLE_RATIO_MAX;
        }
        ratioVec.push_back(ratio);
    }

    auto onVisibleAreaChange = [frameNode](bool visible, double ratio) {
        Ark_Boolean isExpanding = Converter::ArkValue<Ark_Boolean>(visible);
        Ark_Number currentRatio = Converter::ArkValue<Ark_Number>(static_cast<float>(ratio));
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
        GetFullAPI()->getEventsAPI()->getCommonMethodEventsReceiver()->onVisibleAreaChange(
            frameNode->GetId(), isExpanding, currentRatio);
    };

    ViewAbstract::SetOnVisibleChange(frameNode, std::move(onVisibleAreaChange), ratioVec);
}
void KeyboardShortcutImpl(Ark_NativePointer node,
                          const Ark_Union_String_FunctionKey* value,
                          const Array_ModifierKey* keys,
                          const Opt_Callback_Void* action)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(value);
    //auto convValue = Converter::OptConvert<type>(value); // for enums
    //CommonMethodModelNG::SetKeyboardShortcut(frameNode, convValue);
}
} // CommonMethodModifier
const GENERATED_ArkUICommonMethodModifier* GetCommonMethodModifier()
{
    static const GENERATED_ArkUICommonMethodModifier ArkUICommonMethodModifierImpl {
        CommonMethodModifier::WidthImpl,
        CommonMethodModifier::HeightImpl,
        CommonMethodModifier::DrawModifierImpl,
        CommonMethodModifier::ResponseRegionImpl,
        CommonMethodModifier::MouseResponseRegionImpl,
        CommonMethodModifier::SizeImpl,
        CommonMethodModifier::ConstraintSizeImpl,
        CommonMethodModifier::TouchableImpl,
        CommonMethodModifier::HitTestBehaviorImpl,
        CommonMethodModifier::OnChildTouchTestImpl,
        CommonMethodModifier::LayoutWeightImpl,
        CommonMethodModifier::PaddingImpl,
        CommonMethodModifier::MarginImpl,
        CommonMethodModifier::BackgroundColorImpl,
        CommonMethodModifier::PixelRoundImpl,
        CommonMethodModifier::BackgroundImageSizeImpl,
        CommonMethodModifier::BackgroundImagePositionImpl,
        CommonMethodModifier::BackgroundEffectImpl,
        CommonMethodModifier::BackgroundImageResizableImpl,
        CommonMethodModifier::ForegroundEffectImpl,
        CommonMethodModifier::VisualEffectImpl,
        CommonMethodModifier::BackgroundFilterImpl,
        CommonMethodModifier::ForegroundFilterImpl,
        CommonMethodModifier::CompositingFilterImpl,
        CommonMethodModifier::OpacityImpl,
        CommonMethodModifier::BorderImpl,
        CommonMethodModifier::BorderStyleImpl,
        CommonMethodModifier::BorderWidthImpl,
        CommonMethodModifier::BorderColorImpl,
        CommonMethodModifier::BorderRadiusImpl,
        CommonMethodModifier::BorderImageImpl,
        CommonMethodModifier::OutlineImpl,
        CommonMethodModifier::OutlineStyleImpl,
        CommonMethodModifier::OutlineWidthImpl,
        CommonMethodModifier::OutlineColorImpl,
        CommonMethodModifier::OutlineRadiusImpl,
        CommonMethodModifier::ForegroundColorImpl,
        CommonMethodModifier::OnClick0Impl,
        CommonMethodModifier::OnClick1Impl,
        CommonMethodModifier::OnHoverImpl,
        CommonMethodModifier::OnAccessibilityHoverImpl,
        CommonMethodModifier::HoverEffectImpl,
        CommonMethodModifier::OnMouseImpl,
        CommonMethodModifier::OnTouchImpl,
        CommonMethodModifier::OnKeyEventImpl,
        CommonMethodModifier::OnKeyPreImeImpl,
        CommonMethodModifier::FocusableImpl,
        CommonMethodModifier::OnFocusImpl,
        CommonMethodModifier::OnBlurImpl,
        CommonMethodModifier::TabIndexImpl,
        CommonMethodModifier::DefaultFocusImpl,
        CommonMethodModifier::GroupDefaultFocusImpl,
        CommonMethodModifier::FocusOnTouchImpl,
        CommonMethodModifier::FocusBoxImpl,
        CommonMethodModifier::AnimationImpl,
        CommonMethodModifier::Transition0Impl,
        CommonMethodModifier::Transition1Impl,
        CommonMethodModifier::MotionBlurImpl,
        CommonMethodModifier::BrightnessImpl,
        CommonMethodModifier::ContrastImpl,
        CommonMethodModifier::GrayscaleImpl,
        CommonMethodModifier::ColorBlendImpl,
        CommonMethodModifier::SaturateImpl,
        CommonMethodModifier::SepiaImpl,
        CommonMethodModifier::InvertImpl,
        CommonMethodModifier::HueRotateImpl,
        CommonMethodModifier::UseShadowBatchingImpl,
        CommonMethodModifier::UseEffectImpl,
        CommonMethodModifier::RenderGroupImpl,
        CommonMethodModifier::FreezeImpl,
        CommonMethodModifier::TranslateImpl,
        CommonMethodModifier::ScaleImpl,
        CommonMethodModifier::GridSpanImpl,
        CommonMethodModifier::GridOffsetImpl,
        CommonMethodModifier::RotateImpl,
        CommonMethodModifier::TransformImpl,
        CommonMethodModifier::OnAppearImpl,
        CommonMethodModifier::OnDisAppearImpl,
        CommonMethodModifier::OnAttachImpl,
        CommonMethodModifier::OnDetachImpl,
        CommonMethodModifier::OnAreaChangeImpl,
        CommonMethodModifier::VisibilityImpl,
        CommonMethodModifier::FlexGrowImpl,
        CommonMethodModifier::FlexShrinkImpl,
        CommonMethodModifier::FlexBasisImpl,
        CommonMethodModifier::AlignSelfImpl,
        CommonMethodModifier::DisplayPriorityImpl,
        CommonMethodModifier::ZIndexImpl,
        CommonMethodModifier::DirectionImpl,
        CommonMethodModifier::AlignImpl,
        CommonMethodModifier::PositionImpl,
        CommonMethodModifier::MarkAnchorImpl,
        CommonMethodModifier::OffsetImpl,
        CommonMethodModifier::EnabledImpl,
        CommonMethodModifier::UseSizeTypeImpl,
        CommonMethodModifier::AlignRules0Impl,
        CommonMethodModifier::AlignRules1Impl,
        CommonMethodModifier::AspectRatioImpl,
        CommonMethodModifier::ClickEffectImpl,
        CommonMethodModifier::OnDragStartImpl,
        CommonMethodModifier::OnDragEnterImpl,
        CommonMethodModifier::OnDragMoveImpl,
        CommonMethodModifier::OnDragLeaveImpl,
        CommonMethodModifier::OnDropImpl,
        CommonMethodModifier::OnDragEndImpl,
        CommonMethodModifier::AllowDropImpl,
        CommonMethodModifier::DraggableImpl,
        CommonMethodModifier::DragPreviewImpl,
        CommonMethodModifier::OnPreDragImpl,
        CommonMethodModifier::LinearGradientImpl,
        CommonMethodModifier::SweepGradientImpl,
        CommonMethodModifier::RadialGradientImpl,
        CommonMethodModifier::MotionPathImpl,
        CommonMethodModifier::ShadowImpl,
        CommonMethodModifier::Clip0Impl,
        CommonMethodModifier::Clip1Impl,
        CommonMethodModifier::ClipShapeImpl,
        CommonMethodModifier::Mask0Impl,
        CommonMethodModifier::Mask1Impl,
        CommonMethodModifier::MaskShapeImpl,
        CommonMethodModifier::KeyImpl,
        CommonMethodModifier::IdImpl,
        CommonMethodModifier::GeometryTransition0Impl,
        CommonMethodModifier::GeometryTransition1Impl,
        CommonMethodModifier::StateStylesImpl,
        CommonMethodModifier::RestoreIdImpl,
        CommonMethodModifier::SphericalEffectImpl,
        CommonMethodModifier::LightUpEffectImpl,
        CommonMethodModifier::PixelStretchEffectImpl,
        CommonMethodModifier::AccessibilityGroupImpl,
        CommonMethodModifier::AccessibilityText0Impl,
        CommonMethodModifier::AccessibilityText1Impl,
        CommonMethodModifier::AccessibilityTextHintImpl,
        CommonMethodModifier::AccessibilityDescription0Impl,
        CommonMethodModifier::AccessibilityDescription1Impl,
        CommonMethodModifier::AccessibilityLevelImpl,
        CommonMethodModifier::AccessibilityVirtualNodeImpl,
        CommonMethodModifier::ObscuredImpl,
        CommonMethodModifier::ReuseIdImpl,
        CommonMethodModifier::RenderFitImpl,
        CommonMethodModifier::GestureModifierImpl,
        CommonMethodModifier::BackgroundBrightnessImpl,
        CommonMethodModifier::OnGestureJudgeBeginImpl,
        CommonMethodModifier::OnGestureRecognizerJudgeBeginImpl,
        CommonMethodModifier::ShouldBuiltInRecognizerParallelWithImpl,
        CommonMethodModifier::MonopolizeEventsImpl,
        CommonMethodModifier::OnTouchInterceptImpl,
        CommonMethodModifier::OnSizeChangeImpl,
        CommonMethodModifier::CustomPropertyImpl,
        CommonMethodModifier::ExpandSafeAreaImpl,
        CommonMethodModifier::BackgroundImpl,
        CommonMethodModifier::BackgroundImageImpl,
        CommonMethodModifier::BackgroundBlurStyleImpl,
        CommonMethodModifier::ForegroundBlurStyleImpl,
        CommonMethodModifier::FocusScopeIdImpl,
        CommonMethodModifier::FocusScopePriorityImpl,
        CommonMethodModifier::GestureImpl,
        CommonMethodModifier::PriorityGestureImpl,
        CommonMethodModifier::ParallelGestureImpl,
        CommonMethodModifier::BlurImpl,
        CommonMethodModifier::LinearGradientBlurImpl,
        CommonMethodModifier::SystemBarEffectImpl,
        CommonMethodModifier::BackdropBlurImpl,
        CommonMethodModifier::SharedTransitionImpl,
        CommonMethodModifier::ChainModeImpl,
        CommonMethodModifier::DragPreviewOptionsImpl,
        CommonMethodModifier::OverlayImpl,
        CommonMethodModifier::BlendModeImpl,
        CommonMethodModifier::AdvancedBlendModeImpl,
        CommonMethodModifier::BindPopupImpl,
        CommonMethodModifier::BindMenu0Impl,
        CommonMethodModifier::BindMenu1Impl,
        CommonMethodModifier::BindContextMenu0Impl,
        CommonMethodModifier::BindContextMenu1Impl,
        CommonMethodModifier::BindContentCover0Impl,
        CommonMethodModifier::BindContentCover1Impl,
        CommonMethodModifier::BindSheetImpl,
        CommonMethodModifier::OnVisibleAreaChangeImpl,
        CommonMethodModifier::KeyboardShortcutImpl,
    };
    return &ArkUICommonMethodModifierImpl;
}

}
