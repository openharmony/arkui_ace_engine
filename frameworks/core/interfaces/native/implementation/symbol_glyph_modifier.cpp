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
#include "core/components_ng/pattern/symbol/symbol_effect_options.h"
#include "core/interfaces/native/implementation/symbol_effect_peer.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/components_ng/pattern/symbol/symbol_model_ng.h"
#include "core/components_ng/pattern/symbol/symbol_model_static.h"
#include "core/interfaces/native/utility/validators.h"
#include "arkoala_api_generated.h"

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
void AssignCast(std::optional<TextFontWeight>& dst, const Ark_Number& src)
{
    auto intVal = src.i32;
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
constexpr float SCALE_LIMIT = 1.f;
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
    CHECK_NULL_VOID(value);
    auto convValue = Converter::OptConvert<Converter::SymbolData>(*value);
    if (convValue.has_value() && convValue->symbol.has_value()) {
        SymbolModelNG::InitialSymbol(frameNode, convValue->symbol.value());
    }
}
} // SymbolGlyphInterfaceModifier
namespace SymbolGlyphAttributeModifier {
void FontSizeImpl(Ark_NativePointer node,
                  const Opt_Union_Number_String_Resource* value)
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
void FontColorImpl(Ark_NativePointer node,
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
void FontWeightImpl(Ark_NativePointer node,
                    const Opt_Union_Number_FontWeight_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<TextFontWeight>(*value);
    std::optional<Ace::FontWeight> fontWeightValue;
    if (convValue.has_value()) {
        fontWeightValue = static_cast<Ace::FontWeight>(convValue.value());
    }
    SymbolModelStatic::SetFontWeight(frameNode, fontWeightValue);
}
void EffectStrategyImpl(Ark_NativePointer node,
                        const Opt_SymbolEffectStrategy* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<SymbolEffectType>(*value);
    SymbolModelStatic::SetSymbolEffect(frameNode, EnumToInt(convValue));
}
void RenderingStrategyImpl(Ark_NativePointer node,
                           const Opt_SymbolRenderingStrategy* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<Converter::RenderingStrategy>(*value);
    SymbolModelStatic::SetRenderingStrategy(frameNode, EnumToInt(convValue));
}
void MinFontScaleImpl(Ark_NativePointer node,
                      const Opt_Union_Number_Resource* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = value ? Converter::OptConvert<float>(*value) : std::nullopt;
    Validator::ValidatePositive(convValue);
    Validator::ValidateLessOrEqual(convValue, SCALE_LIMIT);
    SymbolModelStatic::SetMinFontScale(frameNode, convValue);
}
void MaxFontScaleImpl(Ark_NativePointer node,
                      const Opt_Union_Number_Resource* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = value ? Converter::OptConvert<float>(*value) : std::nullopt;
    Validator::ValidatePositive(convValue);
    Validator::ValidateGreatOrEqual(convValue, SCALE_LIMIT);
    SymbolModelStatic::SetMaxFontScale(frameNode, convValue);
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
void SymbolEffect0Impl(Ark_NativePointer node,
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
    if (isActive) {
        auto optBool = Converter::OptConvert<bool>(*isActive);
        if (optBool.has_value()) {
            symbolEffectOptions.SetIsActive(optBool.value());
        } else {
            symbolEffectOptions.SetIsActive(false);
        }
    }
    SymbolModelNG::SetSymbolEffectOptions(frameNode, symbolEffectOptions);
}

void SymbolEffect1Impl(Ark_NativePointer node,
                       const Opt_SymbolEffect* symbolEffect,
                       const Opt_Number* triggerValue)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optSymbolEffect = Converter::GetOptPtr(symbolEffect);
    NG::SymbolEffectOptions symbolEffectOptions;
    if (optSymbolEffect.has_value()) {
        ParseSymbolEffectOptions(symbolEffectOptions, optSymbolEffect.value());
    }
    if (triggerValue) {
        auto optTriggerNumb = Converter::OptConvert<int32_t>(*triggerValue);
        if (optTriggerNumb.has_value()) {
            symbolEffectOptions.SetTriggerNum(optTriggerNumb.value());
        }
    }
    SymbolModelNG::SetSymbolEffectOptions(frameNode, symbolEffectOptions);
}
} // SymbolGlyphAttributeModifier
const GENERATED_ArkUISymbolGlyphModifier* GetSymbolGlyphModifier()
{
    static const GENERATED_ArkUISymbolGlyphModifier ArkUISymbolGlyphModifierImpl {
        SymbolGlyphModifier::ConstructImpl,
        SymbolGlyphInterfaceModifier::SetSymbolGlyphOptionsImpl,
        SymbolGlyphAttributeModifier::FontSizeImpl,
        SymbolGlyphAttributeModifier::FontColorImpl,
        SymbolGlyphAttributeModifier::FontWeightImpl,
        SymbolGlyphAttributeModifier::EffectStrategyImpl,
        SymbolGlyphAttributeModifier::RenderingStrategyImpl,
        SymbolGlyphAttributeModifier::MinFontScaleImpl,
        SymbolGlyphAttributeModifier::MaxFontScaleImpl,
        SymbolGlyphAttributeModifier::SymbolEffect0Impl,
        SymbolGlyphAttributeModifier::SymbolEffect1Impl,
    };
    return &ArkUISymbolGlyphModifierImpl;
}

}
