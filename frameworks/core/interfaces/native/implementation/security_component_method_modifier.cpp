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
#include "core/interfaces/native/utility/converter.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace SecurityComponentMethodModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                Ark_Int32 flags)
{
    return {};
}
void IconSizeImpl(Ark_NativePointer node,
                  const Ark_Length* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //SecurityComponentMethodModelNG::SetIconSize(frameNode, convValue);
}
void LayoutDirectionImpl(Ark_NativePointer node,
                         Ark_SecurityComponentLayoutDirection value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(value);
    //auto convValue = Converter::OptConvert<type>(value); // for enums
    //SecurityComponentMethodModelNG::SetLayoutDirection(frameNode, convValue);
}
void PositionImpl(Ark_NativePointer node,
                  const Ark_Position* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //SecurityComponentMethodModelNG::SetPosition(frameNode, convValue);
}
void MarkAnchorImpl(Ark_NativePointer node,
                    const Ark_Position* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //SecurityComponentMethodModelNG::SetMarkAnchor(frameNode, convValue);
}
void OffsetImpl(Ark_NativePointer node,
                const Ark_Union_Position_Edges_LocalizedEdges* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //SecurityComponentMethodModelNG::SetOffset(frameNode, convValue);
}
void FontSizeImpl(Ark_NativePointer node,
                  const Ark_Length* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //SecurityComponentMethodModelNG::SetFontSize(frameNode, convValue);
}
void FontStyleImpl(Ark_NativePointer node,
                   Ark_FontStyle value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(value);
    //auto convValue = Converter::OptConvert<type>(value); // for enums
    //SecurityComponentMethodModelNG::SetFontStyle(frameNode, convValue);
}
void FontWeightImpl(Ark_NativePointer node,
                    const Ark_Union_Number_FontWeight_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //SecurityComponentMethodModelNG::SetFontWeight(frameNode, convValue);
}
void FontFamilyImpl(Ark_NativePointer node,
                    const Ark_Union_String_Resource* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //SecurityComponentMethodModelNG::SetFontFamily(frameNode, convValue);
}
void FontColorImpl(Ark_NativePointer node,
                   const Ark_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //SecurityComponentMethodModelNG::SetFontColor(frameNode, convValue);
}
void IconColorImpl(Ark_NativePointer node,
                   const Ark_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //SecurityComponentMethodModelNG::SetIconColor(frameNode, convValue);
}
void BackgroundColorImpl(Ark_NativePointer node,
                         const Ark_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //SecurityComponentMethodModelNG::SetBackgroundColor(frameNode, convValue);
}
void BorderStyleImpl(Ark_NativePointer node,
                     Ark_BorderStyle value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(value);
    //auto convValue = Converter::OptConvert<type>(value); // for enums
    //SecurityComponentMethodModelNG::SetBorderStyle(frameNode, convValue);
}
void BorderWidthImpl(Ark_NativePointer node,
                     const Ark_Length* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //SecurityComponentMethodModelNG::SetBorderWidth(frameNode, convValue);
}
void BorderColorImpl(Ark_NativePointer node,
                     const Ark_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //SecurityComponentMethodModelNG::SetBorderColor(frameNode, convValue);
}
void BorderRadius0Impl(Ark_NativePointer node,
                       const Ark_Length* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //SecurityComponentMethodModelNG::SetBorderRadius0(frameNode, convValue);
}
void BorderRadius1Impl(Ark_NativePointer node,
                       const Ark_Union_Dimension_BorderRadiuses* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //SecurityComponentMethodModelNG::SetBorderRadius1(frameNode, convValue);
}
void PaddingImpl(Ark_NativePointer node,
                 const Ark_Union_Padding_Dimension* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //SecurityComponentMethodModelNG::SetPadding(frameNode, convValue);
}
void TextIconSpaceImpl(Ark_NativePointer node,
                       const Ark_Length* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //SecurityComponentMethodModelNG::SetTextIconSpace(frameNode, convValue);
}
void KeyImpl(Ark_NativePointer node,
             const Ark_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto convValue = Converter::Convert<std::string>(*value);
    //SecurityComponentMethodModelNG::SetKey(frameNode, convValue);
}
void WidthImpl(Ark_NativePointer node,
               const Ark_Length* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //SecurityComponentMethodModelNG::SetWidth(frameNode, convValue);
}
void HeightImpl(Ark_NativePointer node,
                const Ark_Length* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //SecurityComponentMethodModelNG::SetHeight(frameNode, convValue);
}
void SizeImpl(Ark_NativePointer node,
              const Ark_SizeOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //SecurityComponentMethodModelNG::SetSize(frameNode, convValue);
}
void ConstraintSizeImpl(Ark_NativePointer node,
                        const Ark_ConstraintSizeOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //SecurityComponentMethodModelNG::SetConstraintSize(frameNode, convValue);
}
void AlignImpl(Ark_NativePointer node,
               Ark_Alignment value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(value);
    //auto convValue = Converter::OptConvert<type>(value); // for enums
    //SecurityComponentMethodModelNG::SetAlign(frameNode, convValue);
}
void AlignRules0Impl(Ark_NativePointer node,
                     const Ark_AlignRuleOption* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //SecurityComponentMethodModelNG::SetAlignRules0(frameNode, convValue);
}
void AlignRules1Impl(Ark_NativePointer node,
                     const Ark_LocalizedAlignRuleOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //SecurityComponentMethodModelNG::SetAlignRules1(frameNode, convValue);
}
void IdImpl(Ark_NativePointer node,
            const Ark_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto convValue = Converter::Convert<std::string>(*value);
    //SecurityComponentMethodModelNG::SetId(frameNode, convValue);
}
void MinFontScaleImpl(Ark_NativePointer node,
                      const Ark_Union_Number_Resource* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //SecurityComponentMethodModelNG::SetMinFontScale(frameNode, convValue);
}
void MaxFontScaleImpl(Ark_NativePointer node,
                      const Ark_Union_Number_Resource* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //SecurityComponentMethodModelNG::SetMaxFontScale(frameNode, convValue);
}
void MaxLinesImpl(Ark_NativePointer node,
                  const Ark_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //SecurityComponentMethodModelNG::SetMaxLines(frameNode, convValue);
}
void MinFontSizeImpl(Ark_NativePointer node,
                     const Ark_Union_Number_String_Resource* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //SecurityComponentMethodModelNG::SetMinFontSize(frameNode, convValue);
}
void MaxFontSizeImpl(Ark_NativePointer node,
                     const Ark_Union_Number_String_Resource* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //SecurityComponentMethodModelNG::SetMaxFontSize(frameNode, convValue);
}
void HeightAdaptivePolicyImpl(Ark_NativePointer node,
                              Ark_TextHeightAdaptivePolicy value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(value);
    //auto convValue = Converter::OptConvert<type>(value); // for enums
    //SecurityComponentMethodModelNG::SetHeightAdaptivePolicy(frameNode, convValue);
}
void EnabledImpl(Ark_NativePointer node,
                 Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::Convert<bool>(value);
    //SecurityComponentMethodModelNG::SetEnabled(frameNode, convValue);
}
void ChainModeImpl(Ark_NativePointer node,
                   Ark_Axis direction,
                   Ark_ChainStyle style)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(direction);
    //auto convValue = Converter::OptConvert<type>(direction); // for enums
    //SecurityComponentMethodModelNG::SetChainMode(frameNode, convValue);
}
} // SecurityComponentMethodModifier
const GENERATED_ArkUISecurityComponentMethodModifier* GetSecurityComponentMethodModifier()
{
    static const GENERATED_ArkUISecurityComponentMethodModifier ArkUISecurityComponentMethodModifierImpl {
        SecurityComponentMethodModifier::ConstructImpl,
        SecurityComponentMethodModifier::IconSizeImpl,
        SecurityComponentMethodModifier::LayoutDirectionImpl,
        SecurityComponentMethodModifier::PositionImpl,
        SecurityComponentMethodModifier::MarkAnchorImpl,
        SecurityComponentMethodModifier::OffsetImpl,
        SecurityComponentMethodModifier::FontSizeImpl,
        SecurityComponentMethodModifier::FontStyleImpl,
        SecurityComponentMethodModifier::FontWeightImpl,
        SecurityComponentMethodModifier::FontFamilyImpl,
        SecurityComponentMethodModifier::FontColorImpl,
        SecurityComponentMethodModifier::IconColorImpl,
        SecurityComponentMethodModifier::BackgroundColorImpl,
        SecurityComponentMethodModifier::BorderStyleImpl,
        SecurityComponentMethodModifier::BorderWidthImpl,
        SecurityComponentMethodModifier::BorderColorImpl,
        SecurityComponentMethodModifier::BorderRadius0Impl,
        SecurityComponentMethodModifier::BorderRadius1Impl,
        SecurityComponentMethodModifier::PaddingImpl,
        SecurityComponentMethodModifier::TextIconSpaceImpl,
        SecurityComponentMethodModifier::KeyImpl,
        SecurityComponentMethodModifier::WidthImpl,
        SecurityComponentMethodModifier::HeightImpl,
        SecurityComponentMethodModifier::SizeImpl,
        SecurityComponentMethodModifier::ConstraintSizeImpl,
        SecurityComponentMethodModifier::AlignImpl,
        SecurityComponentMethodModifier::AlignRules0Impl,
        SecurityComponentMethodModifier::AlignRules1Impl,
        SecurityComponentMethodModifier::IdImpl,
        SecurityComponentMethodModifier::MinFontScaleImpl,
        SecurityComponentMethodModifier::MaxFontScaleImpl,
        SecurityComponentMethodModifier::MaxLinesImpl,
        SecurityComponentMethodModifier::MinFontSizeImpl,
        SecurityComponentMethodModifier::MaxFontSizeImpl,
        SecurityComponentMethodModifier::HeightAdaptivePolicyImpl,
        SecurityComponentMethodModifier::EnabledImpl,
        SecurityComponentMethodModifier::ChainModeImpl,
    };
    return &ArkUISecurityComponentMethodModifierImpl;
}

}
