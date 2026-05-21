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

#include "core/components_ng/pattern/symbol/symbol_effect_options.h"
#include "core/components_ng/pattern/symbol/symbol_model_ng.h"
#include "core/interfaces/native/implementation/color_shader_style_peer_impl.h"
#include "core/interfaces/native/implementation/linear_gradient_style_peer_impl.h"
#include "core/interfaces/native/implementation/radial_gradient_style_peer_impl.h"
#include "core/components_ng/pattern/symbol/symbol_model_static.h"
#include "core/interfaces/native/implementation/symbol_effect_peer.h"
#include "core/interfaces/native/utility/ace_engine_types.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/validators.h"

namespace OHOS::Ace {
enum class TextFontWeight {
    W100 = 0,
    W200,
    W300,
    W400,
    W500,
    W600,
    W700,
    W800,
    W900,
    BOLD,
    NORMAL,
    BOLDER,
    LIGHTER,
    MEDIUM,
    REGULAR,
};
}
namespace OHOS::Ace::NG::Converter {

template<>
void AssignCast(std::optional<TextFontWeight>& dst, const Ark_FontWeight& src)
{
    switch (src) {
        case ARK_FONT_WEIGHT_LIGHTER: dst = TextFontWeight::LIGHTER; break;
        case ARK_FONT_WEIGHT_NORMAL: dst = TextFontWeight::NORMAL; break;
        case ARK_FONT_WEIGHT_REGULAR: dst = TextFontWeight::REGULAR; break;
        case ARK_FONT_WEIGHT_MEDIUM: dst = TextFontWeight::MEDIUM; break;
        case ARK_FONT_WEIGHT_BOLD: dst = TextFontWeight::BOLD; break;
        case ARK_FONT_WEIGHT_BOLDER: dst = TextFontWeight::BOLDER; break;
        default: LOGE("Unexpected enum value in Ark_FontWeight: %{public}d", src);
    }
}

template<>
void AssignCast(std::optional<TextFontWeight>& dst, const Ark_Int32& src)
{
    auto intVal = static_cast<int32_t>(src);
    if (intVal >= 0) {
        auto strVal = std::to_string(intVal);
        std::optional<Ace::FontWeight> fontWeight;
        if (auto [parseOk, val] = StringUtils::ParseFontWeight(strVal); parseOk) {
            fontWeight = val;
        }
        if (fontWeight.has_value()) {
            dst = static_cast<TextFontWeight>(fontWeight.value());
        }
    }
}

template<>
void AssignCast(std::optional<TextFontWeight>& dst, const Ark_String& src)
{
    std::optional<Ace::FontWeight> fontWeight;
    if (auto [parseOk, val] = StringUtils::ParseFontWeight(src.chars); parseOk) {
        fontWeight = val;
    }
    if (fontWeight.has_value()) {
        dst = static_cast<TextFontWeight>(fontWeight.value());
    }
}
}
namespace OHOS::Ace::NG::GeneratedModifier {
constexpr float DEFAULT_GRADIENT_ANGLE = 180.0f;
static const std::unordered_map<SDKGradientDirection, float> GRADIENT_DIRECTION_TO_ANGLE = {
    {SDKGradientDirection::Left,        270.0f},
    {SDKGradientDirection::Top,           0.0f},
    {SDKGradientDirection::Right,        90.0f},
    {SDKGradientDirection::Bottom,      180.0f},
    {SDKGradientDirection::LeftTop,     315.0f},
    {SDKGradientDirection::LeftBottom,  225.0f},
    {SDKGradientDirection::RightTop,     45.0f},
    {SDKGradientDirection::RightBottom, 135.0f},
    {SDKGradientDirection::None,        180.0f}
};
namespace SymbolGlyphModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                Ark_Int32 flags)
{
    auto frameNode = SymbolModelNG::CreateFrameNode(id);
    CHECK_NULL_RETURN(frameNode, nullptr);
    frameNode->IncRefCount();
    return AceType::RawPtr(frameNode);
}
} // SymbolGlyphModifier
namespace SymbolGlyphInterfaceModifier {
void SetSymbolGlyphOptionsImpl(Ark_NativePointer node,
                               const Opt_Resource* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<Converter::SymbolData>(value);
    if (convValue.has_value() && convValue->symbol.has_value()) {
        SymbolModelStatic::InitialSymbol(frameNode, convValue->symbol.value());
        SymbolModelStatic::SetFontFamilies(frameNode, convValue->symbolFamilyName);
        SymbolModelStatic::SetSymbolType(frameNode, convValue->symbolType);
    }
}
} // SymbolGlyphInterfaceModifier
namespace SymbolGlyphAttributeModifier {
constexpr float COLOR_COEFFICIENT = 100.0f;

void SetFontSizeImpl(Ark_NativePointer node,
                     const Opt_Union_F64_String_Resource* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    std::optional<Dimension> convValue = std::nullopt;
    if (value->tag != INTEROP_TAG_UNDEFINED) {
        convValue = Converter::OptConvertFromArkNumStrRes(value->value);
    }
    Validator::ValidateNonNegative(convValue);
    Validator::ValidateNonPercent(convValue);
    SymbolModelStatic::SetFontSize(frameNode, convValue);
}
void SetFontColorImpl(Ark_NativePointer node,
                      const Opt_Array_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optFontColors = Converter::OptConvert<std::vector<std::optional<Color>>>(*value);
    std::vector<Color> fontColors;
    if (optFontColors.has_value()) {
        for (auto color : optFontColors.value()) {
            if (color.has_value())
                fontColors.emplace_back(color.value());
        };
    }
    SymbolModelNG::SetFontColor(frameNode, fontColors);
}
void SetSymbolColorImpl(Ark_NativePointer node,
    const Opt_Union_Array_ResourceColor_Array_ColorMetricsExt_Array_Union_ResourceColor_ColorMetricsExt* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optFontColors = value ? Converter::OptConvert<std::vector<std::optional<Color>>>(*value) : std::nullopt;
    std::vector<Color> fontColors;
    if (optFontColors.has_value()) {
        fontColors.reserve(optFontColors->size());
        for (const auto& color : optFontColors.value()) {
            if (color.has_value()) {
                fontColors.emplace_back(color.value());
            }
        }
    }
    SymbolModelNG::SetFontColor(frameNode, fontColors);
}
void SetFontWeight0Impl(Ark_NativePointer node,
                        const Opt_Union_I32_FontWeight_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<TextFontWeight>(value);
    std::optional<Ace::FontWeight> fontWeightValue;
    if (convValue.has_value()) {
        fontWeightValue = static_cast<Ace::FontWeight>(convValue.value());
    }
    SymbolModelStatic::SetFontWeight(frameNode, fontWeightValue);
}
void SetEffectStrategyImpl(Ark_NativePointer node,
                           const Opt_SymbolEffectStrategy* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<SymbolEffectType>(value);
    SymbolModelStatic::SetSymbolEffect(frameNode, EnumToInt(convValue));
}
void SetRenderingStrategyImpl(Ark_NativePointer node,
                              const Opt_SymbolRenderingStrategy* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<Converter::RenderingStrategy>(value);
    SymbolModelStatic::SetRenderingStrategy(frameNode, EnumToInt(convValue));
}
bool ParseSymbolEffectOptions(NG::SymbolEffectOptions& options, Ark_SymbolEffect symbolEffect)
{
    options.SetEffectType(symbolEffect->type);
    if (symbolEffect->scope.has_value()) {
        options.SetScopeType(symbolEffect->scope.value());
    }
    if (symbolEffect->direction.has_value()) {
        options.SetCommonSubType(symbolEffect->direction.value());
    }
    if (symbolEffect->fillStyle.has_value()) {
        options.SetFillStyle(symbolEffect->fillStyle.value());
    }
    return true;
}
void SetSymbolEffect0Impl(Ark_NativePointer node,
                          const Opt_SymbolEffect* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optSymbolEffect = Converter::GetOptPtr(value);
    NG::SymbolEffectOptions symbolEffectOptions;
    if (optSymbolEffect.has_value()) {
        ParseSymbolEffectOptions(symbolEffectOptions, optSymbolEffect.value());
    }
    SymbolModelNG::SetSymbolEffect(frameNode, symbolEffectOptions);
}
void SetMinFontScaleImpl(Ark_NativePointer node,
                         const Opt_Union_F64_Resource* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<float>(value);
    SymbolModelStatic::SetMinFontScale(frameNode, convValue);
}
void SetMaxFontScaleImpl(Ark_NativePointer node,
                         const Opt_Union_F64_Resource* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<float>(value);
    SymbolModelStatic::SetMaxFontScale(frameNode, convValue);
}

float DirectionToAngle(SDKGradientDirection direction)
{
    auto it = GRADIENT_DIRECTION_TO_ANGLE.find(direction);
    return (it != GRADIENT_DIRECTION_TO_ANGLE.end()) ? it->second : DEFAULT_GRADIENT_ANGLE;
}

float DirectionToAngle(const std::optional<GradientDirection> linearX, const std::optional<GradientDirection> linearY)
{
    if (linearX.has_value() && linearY.has_value()) {
        if (linearX.value() == GradientDirection::LEFT && linearY.value() == GradientDirection::TOP) {
            return DirectionToAngle(SDKGradientDirection::LeftTop);
        } else if (linearX.value() == GradientDirection::LEFT && linearY.value() == GradientDirection::BOTTOM) {
            return DirectionToAngle(SDKGradientDirection::LeftBottom);
        } else if (linearX.value() == GradientDirection::RIGHT && linearY.value() == GradientDirection::TOP) {
            return DirectionToAngle(SDKGradientDirection::RightTop);
        } else if (linearX.value() == GradientDirection::RIGHT && linearY.value() == GradientDirection::BOTTOM) {
            return DirectionToAngle(SDKGradientDirection::RightBottom);
        } else if (linearX.value() == GradientDirection::LEFT) {
            return DirectionToAngle(SDKGradientDirection::Left);
        } else if (linearX.value() == GradientDirection::RIGHT) {
            return DirectionToAngle(SDKGradientDirection::Right);
        } else if (linearY.value() == GradientDirection::TOP) {
            return DirectionToAngle(SDKGradientDirection::Top);
        } else if (linearY.value() == GradientDirection::BOTTOM) {
            return DirectionToAngle(SDKGradientDirection::Bottom);
        }
    } else if (linearX.has_value()) {
        if (linearX.value() == GradientDirection::LEFT) {
            return DirectionToAngle(SDKGradientDirection::Left);
        } else if (linearX.value() == GradientDirection::RIGHT) {
            return DirectionToAngle(SDKGradientDirection::Right);
        }
    } else if (linearY.has_value()) {
        if (linearY.value() == GradientDirection::TOP) {
            return DirectionToAngle(SDKGradientDirection::Top);
        } else if (linearY.value() == GradientDirection::BOTTOM) {
            return DirectionToAngle(SDKGradientDirection::Bottom);
        }
    }
    return DirectionToAngle(SDKGradientDirection::None);
}

void ConvertGradientDirection(std::optional<GradientDirection>& dst, const Ark_GradientDirection& src)
{
    switch (src) {
        case Ark_GradientDirection::ARK_GRADIENT_DIRECTION_LEFT: dst = GradientDirection::LEFT; break;
        case Ark_GradientDirection::ARK_GRADIENT_DIRECTION_TOP: dst = GradientDirection::TOP; break;
        case Ark_GradientDirection::ARK_GRADIENT_DIRECTION_RIGHT: dst = GradientDirection::RIGHT; break;
        case Ark_GradientDirection::ARK_GRADIENT_DIRECTION_BOTTOM: dst = GradientDirection::BOTTOM; break;
        case Ark_GradientDirection::ARK_GRADIENT_DIRECTION_LEFT_TOP: dst = GradientDirection::LEFT_TOP; break;
        case Ark_GradientDirection::ARK_GRADIENT_DIRECTION_LEFT_BOTTOM: dst = GradientDirection::LEFT_BOTTOM; break;
        case Ark_GradientDirection::ARK_GRADIENT_DIRECTION_RIGHT_TOP: dst = GradientDirection::RIGHT_TOP; break;
        case Ark_GradientDirection::ARK_GRADIENT_DIRECTION_RIGHT_BOTTOM: dst = GradientDirection::RIGHT_BOTTOM; break;
        case Ark_GradientDirection::ARK_GRADIENT_DIRECTION_NONE: dst = GradientDirection::NONE; break;
        default: LOGE("Unexpected enum value in Ark_GradientDirection: %{public}d", src);
    }
}

void ProcessLinearGradient(const Opt_LinearGradientOptions& linearGradientOpt, SymbolGradient& symbolGradient)
{
    CHECK_NULL_VOID(linearGradientOpt.tag != InteropTag::INTEROP_TAG_UNDEFINED);
    auto options = linearGradientOpt.value;
    Gradient gradient;
    gradient.CreateGradientWithType(GradientType::LINEAR);
    auto repeat = Converter::OptConvert<bool>(options.repeating);
    if (repeat) {
        gradient.SetRepeat(repeat.value());
    }
    auto linear = gradient.GetLinearGradient();
    CHECK_NULL_VOID(linear);
    std::optional<float> degreeOpt;
    constexpr float DEFAULT_ANGLE = 180.0f;
    Converter::ConvertAngleWithDefault(options.angle, degreeOpt, DEFAULT_ANGLE);
    if (degreeOpt) {
        linear->angle = CalcDimension(degreeOpt.value(), DimensionUnit::PX);
        degreeOpt.reset();
    }
    std::optional<GradientDirection> direction;
    auto directionSrc = options.direction;
    if (directionSrc.tag != InteropTag::INTEROP_TAG_UNDEFINED) {
        ConvertGradientDirection(direction, directionSrc.value);
    }
    if (direction.has_value()) {
        Converter::AssignLinearGradientDirection(linear, direction.value());
    }
    Converter::AssignGradientColors(&gradient, &options.colors);
    symbolGradient.type = SymbolGradientType::LINEAR_GRADIENT;
    const auto& colors = gradient.GetColors();
    for (const auto& gradientColor : colors) {
        symbolGradient.symbolColor.emplace_back(gradientColor.GetColor());
        symbolGradient.symbolOpacities.emplace_back(static_cast<float>(
            gradientColor.GetDimension().Value() / COLOR_COEFFICIENT));
    }
    symbolGradient.repeating = gradient.GetRepeat();
    if (linear->angle.has_value()) {
        symbolGradient.angle = linear->angle.value().Value();
    } else {
        float angle = DirectionToAngle(linear->linearX, linear->linearY);
        symbolGradient.angle = angle;
    }
}

void ProcessRadialGradient(const Opt_RadialGradientOptions& radialGradientOpt, SymbolGradient& symbolGradient)
{
    CHECK_NULL_VOID(radialGradientOpt.tag != InteropTag::INTEROP_TAG_UNDEFINED);
    Gradient gradient = Converter::Convert<Gradient>(radialGradientOpt.value);
    symbolGradient.type = SymbolGradientType::RADIAL_GRADIENT;
    auto radialGradientValue = gradient.GetRadialGradient();
    CHECK_NULL_VOID(radialGradientValue);
    const auto& colors = gradient.GetColors();
    for (const auto& gradientColor : colors) {
        symbolGradient.symbolColor.emplace_back(gradientColor.GetColor());
        symbolGradient.symbolOpacities.emplace_back(static_cast<float>(
            gradientColor.GetDimension().Value() / COLOR_COEFFICIENT));
    }
    symbolGradient.repeating = gradient.GetRepeat();
    symbolGradient.radialCenterX = radialGradientValue->radialCenterX;
    symbolGradient.radialCenterY = radialGradientValue->radialCenterY;
    symbolGradient.radius = radialGradientValue->radialVerticalSize;
}

SymbolGradient ProcessShaderStyleForSymbol(Ark_ShaderStyleProxy shaderStyleProxy, FrameNode* frameNode)
{
    SymbolGradient gradient;
    auto colorOpt = Converter::OptConvert<Color>(shaderStyleProxy.color);
    auto linearGradientOpt = shaderStyleProxy.linearGradientOptions;
    auto radialGradientOpt = shaderStyleProxy.radialGradientOptions;
    bool hasLinear = linearGradientOpt.tag != InteropTag::INTEROP_TAG_UNDEFINED;
    bool hasRadial = radialGradientOpt.tag != InteropTag::INTEROP_TAG_UNDEFINED;
    CHECK_NULL_RETURN(colorOpt.has_value() || hasLinear || hasRadial, gradient);
    if (!hasLinear && !hasRadial) {
        SymbolModelNG::ResetShaderStyle(frameNode);
        return gradient;
    }

    if (colorOpt.has_value()) {
        gradient.type = SymbolGradientType::COLOR_SHADER;
        gradient.symbolColor.push_back(colorOpt.value());
    } else if (hasLinear) {
        ProcessLinearGradient(linearGradientOpt, gradient);
    } else if (hasRadial) {
        ProcessRadialGradient(radialGradientOpt, gradient);
    } else {
        SymbolModelNG::ResetShaderStyle(frameNode);
    }
    return gradient;
}

void SetShaderStyleImpl(Ark_NativePointer node,
                        const Opt_Union_Array_Opt_ShaderStyleProxy_ShaderStyleProxy* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::vector<SymbolGradient> gradients;
    auto optUnionArrayShaderStyle = Converter::GetOptPtr(value);
    if (!optUnionArrayShaderStyle.has_value()) {
        SymbolModelNG::ResetShaderStyle(frameNode);
        return;
    }
    auto valueSelector = optUnionArrayShaderStyle.value().selector;
    if (valueSelector == 0) {
        gradients.reserve(optUnionArrayShaderStyle.value().value0.length);
        for (int32_t i = 0; i < optUnionArrayShaderStyle.value().value0.length; ++i) {
            Opt_ShaderStyleProxy optShaderStyle =  optUnionArrayShaderStyle.value().value0.array[i];
            if (optShaderStyle.tag == InteropTag::INTEROP_TAG_UNDEFINED) {
                continue;
            }
            SymbolGradient gradient = ProcessShaderStyleForSymbol(optShaderStyle.value, frameNode);
            gradients.emplace_back(std::move(gradient));
        }
        SymbolModelNG::SetShaderStyle(frameNode, gradients);
    } else if (valueSelector == 1) {
        auto shaderStyleProxy = optUnionArrayShaderStyle.value().value1;
        SymbolGradient gradient = ProcessShaderStyleForSymbol(shaderStyleProxy, frameNode);
        gradient.gradientType = GradientDefinedStatus::GRADIENT_TYPE;
        gradients.emplace_back(std::move(gradient));
        SymbolModelNG::SetShaderStyle(frameNode, gradients);
    } else {
        return;
    }
}
void SetSymbolShadowImpl(Ark_NativePointer node,
                         const Opt_ShadowOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto shadowOptions = Converter::OptConvertPtr<SymbolShadow>(value);
    SymbolModelStatic::SetSymbolShadow(frameNode, shadowOptions);
}

void SetFontWeight1Impl(Ark_NativePointer node,
                        const Opt_Union_I32_FontWeight_ResourceStr* value,
                        const Opt_FontWeightConfigs* fontWeightConfigs)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    Converter::FontWeightInt defaultWeight = {};
    auto convertedWeight = Converter::OptConvertPtr<Converter::FontWeightInt>(value).value_or(defaultWeight);
    if (!convertedWeight.fixed.has_value()) {
        convertedWeight.fixed = Ace::FontWeight::NORMAL;
    }
    SymbolModelStatic::SetFontWeight(frameNode, convertedWeight.fixed);
    if (!fontWeightConfigs || fontWeightConfigs->tag == INTEROP_TAG_UNDEFINED) {
        SymbolModelNG::ResetVariableFontWeight(frameNode);
        SymbolModelNG::ResetEnableVariableFontWeight(frameNode);
        SymbolModelNG::ResetEnableDeviceFontWeightCategory(frameNode);
        return;
    }
    if (fontWeightConfigs->value.enableVariableFontWeight.tag != INTEROP_TAG_UNDEFINED) {
        if (convertedWeight.variable.has_value()) {
            SymbolModelNG::SetVariableFontWeight(frameNode, convertedWeight.variable.value());
        } else {
            SymbolModelNG::ResetVariableFontWeight(frameNode);
        }
        SymbolModelNG::SetEnableVariableFontWeight(frameNode, fontWeightConfigs->value.enableVariableFontWeight.value);
    } else {
        SymbolModelNG::ResetVariableFontWeight(frameNode);
        SymbolModelNG::SetEnableVariableFontWeight(frameNode, false);
    }
    if (fontWeightConfigs->value.enableDeviceFontWeightCategory.tag != INTEROP_TAG_UNDEFINED) {
        SymbolModelNG::SetEnableDeviceFontWeightCategory(frameNode,
            fontWeightConfigs->value.enableDeviceFontWeightCategory.value);
    } else {
        SymbolModelNG::SetEnableDeviceFontWeightCategory(frameNode, true);
    }
}
void SetSymbolEffect1Impl(Ark_NativePointer node,
                          const Opt_SymbolEffect* symbolEffect,
                          const Opt_Boolean* isActive)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optSymbolEffect = Converter::GetOptPtr(symbolEffect);
    NG::SymbolEffectOptions symbolEffectOptions;
    if (optSymbolEffect.has_value()) {
        ParseSymbolEffectOptions(symbolEffectOptions, optSymbolEffect.value());
    }
    auto optBool = Converter::OptConvertPtr<bool>(isActive);
    if (optBool.has_value()) {
        symbolEffectOptions.SetIsActive(optBool.value());
    }
    SymbolModelNG::SetSymbolEffect(frameNode, symbolEffectOptions);
}
void SetSymbolEffect2Impl(Ark_NativePointer node,
                          const Opt_SymbolEffect* symbolEffect,
                          const Opt_Int32* triggerValue)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optSymbolEffect = Converter::GetOptPtr(symbolEffect);
    NG::SymbolEffectOptions symbolEffectOptions;
    if (optSymbolEffect.has_value()) {
        ParseSymbolEffectOptions(symbolEffectOptions, optSymbolEffect.value());
    }
    auto optTriggerNumb = Converter::OptConvertPtr<int32_t>(triggerValue);
    if (optTriggerNumb.has_value()) {
        symbolEffectOptions.SetTriggerNum(optTriggerNumb.value());
    }
    SymbolModelNG::SetSymbolEffect(frameNode, symbolEffectOptions);
}
} // SymbolGlyphAttributeModifier
const GENERATED_ArkUISymbolGlyphModifier* GetSymbolGlyphStaticModifier()
{
    static const GENERATED_ArkUISymbolGlyphModifier ArkUISymbolGlyphModifierImpl {
        SymbolGlyphModifier::ConstructImpl,
        SymbolGlyphInterfaceModifier::SetSymbolGlyphOptionsImpl,
        SymbolGlyphAttributeModifier::SetFontSizeImpl,
        SymbolGlyphAttributeModifier::SetFontColorImpl,
        SymbolGlyphAttributeModifier::SetSymbolColorImpl,
        SymbolGlyphAttributeModifier::SetFontWeight0Impl,
        SymbolGlyphAttributeModifier::SetEffectStrategyImpl,
        SymbolGlyphAttributeModifier::SetRenderingStrategyImpl,
        SymbolGlyphAttributeModifier::SetSymbolEffect0Impl,
        SymbolGlyphAttributeModifier::SetMinFontScaleImpl,
        SymbolGlyphAttributeModifier::SetMaxFontScaleImpl,
        SymbolGlyphAttributeModifier::SetShaderStyleImpl,
        SymbolGlyphAttributeModifier::SetSymbolShadowImpl,
        SymbolGlyphAttributeModifier::SetFontWeight1Impl,
        SymbolGlyphAttributeModifier::SetSymbolEffect1Impl,
        SymbolGlyphAttributeModifier::SetSymbolEffect2Impl,
    };
    return &ArkUISymbolGlyphModifierImpl;
}

}
