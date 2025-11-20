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
#include "core/components_ng/pattern/progress/progress_model_ng.h"
#include "core/components_ng/pattern/progress/progress_model_static.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/validators.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG {
constexpr float PROGRESS_MAX_VALUE = 100.f;
constexpr float PROGRESS_DEFAULT_STROKE_WIDTH = 4.0f;
constexpr int32_t PROGRESS_MIN_SCALE_COUNT = 2;
struct ProgressOptions {
    double value = 0;
    double total = PROGRESS_MAX_VALUE;
    ProgressType type = ProgressType::LINEAR;
};

auto g_setLinearStyle = [](FrameNode* frameNode, const Ark_LinearStyleOptions& options) {
    // strokeWidth
    auto strokeWidth = Converter::OptConvertFromArkLength(options.strokeWidth.value, DimensionUnit::VP);
    Validator::ValidatePositive(strokeWidth);
    Validator::ValidateNonPercent(strokeWidth);
    ProgressModelStatic::SetStrokeWidth(frameNode, strokeWidth);
    // enableScanEffect
    ProgressModelStatic::SetLinearSweepingEffect(frameNode,
        Converter::OptConvert<bool>(options.enableScanEffect));
    // strokeRadius
    auto strokeRadius = Converter::OptConvert<Dimension>(options.strokeRadius);
    Validator::ValidateNonNegative(strokeRadius);
    Validator::ValidateNonPercent(strokeRadius);
    ProgressModelStatic::SetStrokeRadius(frameNode, strokeRadius);
    // enableSmoothEffect
    ProgressModelStatic::SetSmoothEffect(frameNode, Converter::OptConvert<bool>(options.enableSmoothEffect));
};

auto g_setRingStyle = [](FrameNode* frameNode, const Ark_RingStyleOptions& options) {
    // strokeWidth
    auto strokeWidth = Converter::OptConvertFromArkLength(options.strokeWidth.value, DimensionUnit::VP);
    Validator::ValidatePositive(strokeWidth);
    Validator::ValidateNonPercent(strokeWidth);
    ProgressModelStatic::SetStrokeWidth(frameNode, strokeWidth);
    // shadow
    ProgressModelStatic::SetPaintShadow(frameNode, Converter::OptConvert<bool>(options.shadow));
    // enableScanEffect
    ProgressModelStatic::SetRingSweepingEffect(frameNode, Converter::OptConvert<bool>(options.enableScanEffect));
    // status
    ProgressModelStatic::SetProgressStatus(frameNode, Converter::OptConvert<ProgressStatus>(options.status));
    // enableSmoothEffect
    ProgressModelStatic::SetSmoothEffect(frameNode, Converter::OptConvert<bool>(options.enableSmoothEffect));
};

auto g_setCapsuleStyle = [](FrameNode* frameNode, const Ark_CapsuleStyleOptions& options) {
    // borderWidth
    auto borderWidth = Converter::OptConvert<Dimension>(options.borderWidth);
    Validator::ValidateNonNegative(borderWidth);
    Validator::ValidateNonPercent(borderWidth);
    ProgressModelStatic::SetBorderWidth(frameNode, borderWidth);
    // borderColor
    ProgressModelStatic::SetBorderColor(frameNode, Converter::OptConvert<Color>(options.borderColor));
    // borderRadius
    auto borderRadius = Converter::OptConvert<Dimension>(options.borderRadius);
    Validator::ValidateNonNegative(borderRadius);
    Validator::ValidateNonPercent(borderRadius);
    ProgressModelStatic::SetBorderRadius(frameNode, borderRadius);
    // enableScanEffect
    ProgressModelStatic::SetSweepingEffect(frameNode, Converter::OptConvert<bool>(options.enableScanEffect));
    // showDefaultPercentage
    ProgressModelStatic::SetShowText(frameNode, Converter::OptConvert<bool>(options.showDefaultPercentage));
    // content
    ProgressModelStatic::SetText(frameNode, Converter::OptConvert<std::string>(options.content));
    // fontColor
    ProgressModelStatic::SetFontColor(frameNode, Converter::OptConvert<Color>(options.fontColor));
    // font
    auto font = Converter::OptConvert<Font>(options.font);
    if (font.has_value()) {
        ProgressModelStatic::SetFontSize(frameNode, font.value().fontSize);
        ProgressModelStatic::SetFontWeight(frameNode, font.value().fontWeight);
        ProgressModelStatic::SetItalicFontStyle(frameNode, font.value().fontStyle);
        ProgressModelStatic::SetFontFamily(frameNode, font.value().fontFamilies);
    } else {
        ProgressModelStatic::SetFontSize(frameNode, std::nullopt);
        ProgressModelStatic::SetFontWeight(frameNode, std::nullopt);
        ProgressModelStatic::SetItalicFontStyle(frameNode, std::nullopt);
        ProgressModelStatic::SetFontFamily(frameNode, std::nullopt);
    }
    // enableSmoothEffect
    ProgressModelStatic::SetSmoothEffect(frameNode, Converter::OptConvert<bool>(options.enableSmoothEffect));
};

auto g_setProgressStyle = [](FrameNode* frameNode, const Ark_ProgressStyleOptions& options) {
    // strokeWidth
    auto strokeWidth = Converter::OptConvertFromArkLength(options.strokeWidth.value, DimensionUnit::VP);
    Validator::ValidatePositive(strokeWidth);
    Validator::ValidateNonPercent(strokeWidth);
    ProgressModelStatic::SetStrokeWidth(frameNode, strokeWidth);
    // scaleCount
    auto scaleCount = Converter::OptConvert<int32_t>(options.scaleCount);
    Validator::ValidateGreatOrEqual(scaleCount, PROGRESS_MIN_SCALE_COUNT);
    ProgressModelStatic::SetScaleCount(frameNode, scaleCount);
    // scaleWidth
    auto scaleWidth = Converter::OptConvert<Dimension>(options.scaleWidth);
    Validator::ValidatePositive(scaleWidth);
    Validator::ValidateNonPercent(scaleWidth);
    if (scaleWidth.has_value()) {
        auto strokeWidthValue = PROGRESS_DEFAULT_STROKE_WIDTH;
        auto scaleWidthValue = scaleWidth.value().Value();
        if (strokeWidth.has_value()) {
            strokeWidthValue = strokeWidth.value().Value();
        }
        if (GreatNotEqual(scaleWidthValue, strokeWidthValue)) {
            scaleWidth.reset();
        }
    }
    ProgressModelStatic::SetScaleWidth(frameNode, scaleWidth);
    // enableSmoothEffect
    ProgressModelStatic::SetSmoothEffect(frameNode, Converter::OptConvert<bool>(options.enableSmoothEffect));
};

auto g_setUndefinedStyle = [](FrameNode* frameNode) {
    // strokeWidth
    ProgressModelStatic::SetStrokeWidth(frameNode, std::nullopt);
    // enableScanEffect
    ProgressModelStatic::SetLinearSweepingEffect(frameNode, std::nullopt);
    // strokeRadius
    ProgressModelStatic::SetStrokeRadius(frameNode, std::nullopt);
    // shadow
    ProgressModelStatic::SetPaintShadow(frameNode, std::nullopt);
    // status
    ProgressModelStatic::SetProgressStatus(frameNode, std::nullopt);
    // borderWidth
    ProgressModelStatic::SetBorderWidth(frameNode, std::nullopt);
    // borderColor
    ProgressModelStatic::SetBorderColor(frameNode, std::nullopt);
    // showDefaultPercentage
    ProgressModelStatic::SetShowText(frameNode, std::nullopt);
    // content
    ProgressModelStatic::SetText(frameNode, std::nullopt);
    // fontColor
    ProgressModelStatic::SetFontColor(frameNode, std::nullopt);
    // font
    ProgressModelStatic::SetFontSize(frameNode, std::nullopt);
    ProgressModelStatic::SetFontWeight(frameNode, std::nullopt);
    ProgressModelStatic::SetItalicFontStyle(frameNode, std::nullopt);
    ProgressModelStatic::SetFontFamily(frameNode, std::nullopt);
    // scaleCount
    ProgressModelStatic::SetScaleCount(frameNode, std::nullopt);
    // scaleWidth
    ProgressModelStatic::SetScaleWidth(frameNode, std::nullopt);
    // enableSmoothEffect
    ProgressModelStatic::SetSmoothEffect(frameNode, std::nullopt);
};
} // OHOS::Ace::NG

namespace OHOS::Ace::NG::Converter {
template<>
ProgressOptions Convert(const Ark_ProgressOptions& src)
{
    ProgressOptions options;
    // value
    options.value = static_cast<double>(Converter::Convert<float>(src.value));
    // total
    auto total = Converter::OptConvert<float>(src.total);
    if (total) {
        options.total = static_cast<double>(total.value());
    }
    // type
    auto type = Converter::OptConvert<ProgressType>(src.type);
    if (type) {
        options.type = type.value();
    }
    return options;
}

template<>
void AssignCast(std::optional<ProgressType>& dst, const Ark_ProgressType& src)
{
    switch (src) {
        case ARK_PROGRESS_TYPE_LINEAR: dst = ProgressType::LINEAR; break;
        case ARK_PROGRESS_TYPE_RING: dst = ProgressType::RING; break;
        case ARK_PROGRESS_TYPE_ECLIPSE: dst = ProgressType::MOON; break;
        case ARK_PROGRESS_TYPE_SCALE_RING: dst = ProgressType::SCALE; break;
        case ARK_PROGRESS_TYPE_CAPSULE: dst = ProgressType::CAPSULE; break;
        default: LOGE("Unexpected enum value in Ark_ProgressType: %{public}d", src);
    }
}

template<>
void AssignCast(std::optional<ProgressType>& dst, const Ark_ProgressStyle& src)
{
    switch (src) {
        case ARK_PROGRESS_STYLE_LINEAR: dst = ProgressType::LINEAR; break;
        case ARK_PROGRESS_STYLE_RING: dst = ProgressType::RING; break;
        case ARK_PROGRESS_STYLE_ECLIPSE: dst = ProgressType::MOON; break;
        case ARK_PROGRESS_STYLE_SCALE_RING: dst = ProgressType::SCALE; break;
        case ARK_PROGRESS_STYLE_CAPSULE: dst = ProgressType::CAPSULE; break;
        default: LOGE("Unexpected enum value in Ark_ProgressStyle: %{public}d", src);
    }
}

template<>
void AssignCast(std::optional<ProgressStatus>& dst, const Ark_ProgressStatus& src)
{
    switch (src) {
        case ARK_PROGRESS_STATUS_LOADING: dst = ProgressStatus::LOADING; break;
        case ARK_PROGRESS_STATUS_PROGRESSING: dst = ProgressStatus::PROGRESSING; break;
        default: LOGE("Unexpected enum value in Ark_ProgressStatus: %{public}d", src);
    }
}
} // OHOS::Ace::NG::Converter

namespace OHOS::Ace::NG::GeneratedModifier {
namespace ProgressModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                Ark_Int32 flags)
{
    auto frameNode = ProgressModelNG::CreateFrameNode(id, 0, 100, NG::ProgressType::LINEAR);
    CHECK_NULL_RETURN(frameNode, nullptr);
    frameNode->IncRefCount();
    return AceType::RawPtr(frameNode);
}
} // ProgressModifier
namespace ProgressInterfaceModifier {
void SetProgressOptionsImpl(Ark_NativePointer node,
                            const Ark_ProgressOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(options);
    auto convValue = Converter::Convert<ProgressOptions>(*options);
    auto value = convValue.value;
    auto total = convValue.total;
    if (LessOrEqual(total, 0)) {
        total = PROGRESS_MAX_VALUE;
    }
    if (GreatNotEqual(value, total)) {
        value = total;
    } else if (LessOrEqual(value, 0)) {
        value = 0;
    }
    ProgressModelStatic::Initialize(frameNode, 0.0, value, 0.0, total, convValue.type);
}
} // ProgressInterfaceModifier
namespace ProgressAttributeModifier {
void SetValueImpl(Ark_NativePointer node,
                  const Opt_Float64* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<double>(value);
    ProgressModelStatic::SetValue(frameNode, convValue);
}
void SetColorImpl(Ark_NativePointer node,
                  const Opt_Union_ResourceColor_LinearGradient* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    Converter::VisitUnion(
        *value,
        [frameNode](const Ark_ResourceColor& resourceColor) {
            std::optional<Color> colorOpt = Converter::OptConvert<Color>(resourceColor);
            std::optional<Gradient> gradientOpt = std::nullopt;
            if (colorOpt) {
                Gradient gradient;
                GradientColor endSideColor;
                GradientColor beginSideColor;
                endSideColor.SetLinearColor(LinearColor(colorOpt.value()));
                endSideColor.SetDimension(Dimension(0.0));
                beginSideColor.SetLinearColor(LinearColor(colorOpt.value()));
                beginSideColor.SetDimension(Dimension(1.0));
                gradient.AddColor(endSideColor);
                gradient.AddColor(beginSideColor);
                gradientOpt = gradient;
            }
            ProgressModelStatic::SetGradientColor(frameNode, gradientOpt);
            ProgressModelStatic::SetColor(frameNode, colorOpt);
        },
        [frameNode](const Ark_LinearGradient& linearGradient) {
            ProgressModelStatic::SetGradientColor(frameNode, Converter::OptConvert<Gradient>(linearGradient));
        },
        // Implement Reset value
        [frameNode]() {
            ProgressModelStatic::SetGradientColor(frameNode, std::nullopt);
            ProgressModelStatic::SetColor(frameNode, std::nullopt);
        });
}
void SetStyleImpl(Ark_NativePointer node,
                  const Opt_Union_LinearStyleOptions_RingStyleOptions_CapsuleStyleOptions_ProgressStyleOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    Converter::VisitUnion(
        *value, [frameNode](const Ark_LinearStyleOptions& options) { g_setLinearStyle(frameNode, options); },
        [frameNode](const Ark_RingStyleOptions& options) { g_setRingStyle(frameNode, options); },
        [frameNode](const Ark_CapsuleStyleOptions& options) { g_setCapsuleStyle(frameNode, options); },
        [frameNode](const Ark_ProgressStyleOptions& options) { g_setProgressStyle(frameNode, options); },
        // Implement Reset value
        [frameNode]() { g_setUndefinedStyle(frameNode); });
}
void SetPrivacySensitiveImpl(Ark_NativePointer node,
                             const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<bool>(value);
    ProgressModelStatic::SetPrivacySensitive(frameNode, convValue);
}
} // ProgressAttributeModifier
const GENERATED_ArkUIProgressModifier* GetProgressModifier()
{
    static const GENERATED_ArkUIProgressModifier ArkUIProgressModifierImpl {
        ProgressModifier::ConstructImpl,
        ProgressInterfaceModifier::SetProgressOptionsImpl,
        ProgressAttributeModifier::SetValueImpl,
        ProgressAttributeModifier::SetColorImpl,
        ProgressAttributeModifier::SetStyleImpl,
        ProgressAttributeModifier::SetPrivacySensitiveImpl,
    };
    return &ArkUIProgressModifierImpl;
}

}
