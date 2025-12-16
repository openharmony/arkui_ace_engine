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

#include "core/components_ng/pattern/text/symbol_span_model_ng.h"
#include "core/components_ng/pattern/text/symbol_span_model_static.h"
#include "core/interfaces/native/utility/ace_engine_types.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/interfaces/native/utility/validators.h"
#include "arkoala_api_generated.h"
#include "frameworks/core/components_ng/pattern/symbol/constants.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace SymbolSpanModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                Ark_Int32 flags)
{
    auto frameNode = SymbolSpanModelStatic::CreateFrameNode(id);
    CHECK_NULL_RETURN(frameNode, nullptr);
    frameNode->IncRefCount();
    return AceType::RawPtr(frameNode);
}
} // SymbolSpanModifier
namespace SymbolSpanInterfaceModifier {
void SetSymbolSpanOptionsImpl(Ark_NativePointer node,
                              const Ark_Resource* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto convValue = Converter::OptConvert<Converter::SymbolData>(*value);
    if (convValue.has_value() && convValue->symbol.has_value()) {
        SymbolSpanModelStatic::InitialSymbol(frameNode, convValue->symbol.value());
        SymbolSpanModelStatic::SetFontFamilies(frameNode, convValue->symbolFamilyName);
        SymbolSpanModelStatic::SetSymbolType(frameNode, convValue->symbolType);
    }
}
} // SymbolSpanInterfaceModifier
namespace SymbolSpanAttributeModifier {
void SetFontSizeImpl(Ark_NativePointer node,
                     const Opt_Union_F64_String_Resource* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::OptConvertPtr<Dimension>(value);
    Validator::ValidateNonNegative(optValue);
    Validator::ValidateNonPercent(optValue);
    SymbolSpanModelStatic::SetFontSize(frameNode, optValue);
}
void SetFontColorImpl(Ark_NativePointer node,
                      const Opt_Array_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optColorVec = Converter::OptConvert<std::vector<std::optional<Color>>>(*value);
    std::vector<Color> colorVec;
    if (!optColorVec) {
        SymbolSpanModelNG::ResetFontColor(frameNode);
        return;
    }
    for (std::optional<Color> color: *optColorVec) {
        if (color.has_value()) {
            colorVec.emplace_back(color.value());
        }
    }
    SymbolSpanModelNG::SetFontColor(frameNode, colorVec);
}
void SetFontWeightImpl(Ark_NativePointer node,
                       const Opt_Union_I32_FontWeight_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<Ace::FontWeight>(value);
    SymbolSpanModelStatic::SetFontWeight(frameNode, convValue);
}
void SetEffectStrategyImpl(Ark_NativePointer node,
                           const Opt_SymbolEffectStrategy* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<SymbolEffectType>(value);
    SymbolSpanModelStatic::SetSymbolEffect(frameNode, EnumToInt(convValue));
}
void SetRenderingStrategyImpl(Ark_NativePointer node,
                              const Opt_SymbolRenderingStrategy* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<Converter::RenderingStrategy>(value);
    SymbolSpanModelStatic::SetSymbolRenderingStrategy(frameNode, EnumToInt(convValue));
}
void SetKeyImpl(Ark_NativePointer node,
                const Opt_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<std::string>(value);
    if (!convValue) {
        // keep the same processing
        return;
    }
    ViewAbstract::SetInspectorId(frameNode, *convValue);
}
void SetIdImpl(Ark_NativePointer node,
               const Opt_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto id = Converter::OptConvertPtr<std::string>(value);
    ViewAbstract::SetInspectorId(frameNode, *id);
}
} // SymbolSpanAttributeModifier
const GENERATED_ArkUISymbolSpanModifier* GetSymbolSpanModifier()
{
    static const GENERATED_ArkUISymbolSpanModifier ArkUISymbolSpanModifierImpl {
        SymbolSpanModifier::ConstructImpl,
        SymbolSpanInterfaceModifier::SetSymbolSpanOptionsImpl,
        SymbolSpanAttributeModifier::SetFontSizeImpl,
        SymbolSpanAttributeModifier::SetFontColorImpl,
        SymbolSpanAttributeModifier::SetFontWeightImpl,
        SymbolSpanAttributeModifier::SetEffectStrategyImpl,
        SymbolSpanAttributeModifier::SetRenderingStrategyImpl,
        SymbolSpanAttributeModifier::SetKeyImpl,
        SymbolSpanAttributeModifier::SetIdImpl,
    };
    return &ArkUISymbolSpanModifierImpl;
}

}
