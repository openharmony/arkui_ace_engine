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

#include "core/components_ng/base/frame_node.h"
#include "core/interfaces/arkoala/utility/converter.h"
#include "core/components_ng/pattern/symbol/symbol_model_ng.h"
#include "core/interfaces/arkoala/utility/validators.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG {
namespace GeneratedModifier {
namespace SymbolGlyphInterfaceModifier {
void SetSymbolGlyphOptionsImpl(Ark_NativePointer node,
                               const Opt_Resource* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto convValue = Converter::OptConvert<Converter::SymbolData>(value->value);
    if (convValue.has_value() && convValue->symbol.has_value()) {
        SymbolModelNG::InitialSymbol(frameNode, convValue->symbol.value());
    }
}
} // SymbolGlyphInterfaceModifier
namespace SymbolGlyphAttributeModifier {
void FontSizeImpl(Ark_NativePointer node,
                  const Ark_Union_Number_String_Resource* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto convValue = Converter::OptConvert<Dimension>(*value);
    Validator::ValidateNonNegative(convValue);
    Validator::ValidateNonPercent(convValue);
    SymbolModelNG::SetFontSize(frameNode, convValue);
}
void FontColorImpl(Ark_NativePointer node,
                   const Array_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto optFontColors = Converter::Convert<std::vector<std::optional<Color>>>(*value);
    std::vector<Color> fontColors;
    for (auto color : optFontColors) {
        if (color.has_value())
            fontColors.emplace_back(color.value());
    };
    SymbolModelNG::SetFontColor(frameNode, fontColors);
}
void FontWeightImpl(Ark_NativePointer node,
                    const Ark_Union_Number_FontWeight_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto convValue = Converter::OptConvert<Ace::FontWeight>(*value);
    SymbolModelNG::SetFontWeight(frameNode, convValue);
}
void EffectStrategyImpl(Ark_NativePointer node,
                        Ark_SymbolEffectStrategy value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<SymbolEffectType>(value); // for enums
    SymbolModelNG::SetSymbolEffect(frameNode, EnumToInt(convValue));
}
void RenderingStrategyImpl(Ark_NativePointer node,
                           Ark_SymbolRenderingStrategy value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<RenderingStrategy>(value); // for enums
    SymbolModelNG::SetRenderingStrategy(frameNode, EnumToInt(convValue));
}
void SymbolEffect0Impl(Ark_NativePointer node,
                       const Ark_SymbolEffect* symbolEffect,
                       const Opt_Boolean* isActive)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(symbolEffect);
    LOGE("Ark_SymbolEffect is not implemented yet.");
}
void SymbolEffect1Impl(Ark_NativePointer node,
                       const Ark_SymbolEffect* symbolEffect,
                       const Opt_Number* triggerValue)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(symbolEffect);
    LOGE("Ark_SymbolEffect is not implemented yet.");
}
} // SymbolGlyphAttributeModifier
const GENERATED_ArkUISymbolGlyphModifier* GetSymbolGlyphModifier()
{
    static const GENERATED_ArkUISymbolGlyphModifier ArkUISymbolGlyphModifierImpl {
        SymbolGlyphInterfaceModifier::SetSymbolGlyphOptionsImpl,
        SymbolGlyphAttributeModifier::FontSizeImpl,
        SymbolGlyphAttributeModifier::FontColorImpl,
        SymbolGlyphAttributeModifier::FontWeightImpl,
        SymbolGlyphAttributeModifier::EffectStrategyImpl,
        SymbolGlyphAttributeModifier::RenderingStrategyImpl,
        SymbolGlyphAttributeModifier::SymbolEffect0Impl,
        SymbolGlyphAttributeModifier::SymbolEffect1Impl,
    };
    return &ArkUISymbolGlyphModifierImpl;
}
}
}