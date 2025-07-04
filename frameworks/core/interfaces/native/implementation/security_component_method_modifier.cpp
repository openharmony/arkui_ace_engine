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
void SetIconSizeImpl(Ark_NativePointer node,
                     const Opt_Dimension* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //SecurityComponentMethodModelNG::SetSetIconSize(frameNode, convValue);
}
void SetLayoutDirectionImpl(Ark_NativePointer node,
                            const Opt_SecurityComponentLayoutDirection* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //SecurityComponentMethodModelNG::SetSetLayoutDirection(frameNode, convValue);
}
void SetPositionImpl(Ark_NativePointer node,
                     const Opt_Position* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //SecurityComponentMethodModelNG::SetSetPosition(frameNode, convValue);
}
void SetMarkAnchorImpl(Ark_NativePointer node,
                       const Opt_Position* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //SecurityComponentMethodModelNG::SetSetMarkAnchor(frameNode, convValue);
}
void SetOffsetImpl(Ark_NativePointer node,
                   const Opt_Union_Position_Edges_LocalizedEdges* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //SecurityComponentMethodModelNG::SetSetOffset(frameNode, convValue);
}
void SetFontSizeImpl(Ark_NativePointer node,
                     const Opt_Dimension* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //SecurityComponentMethodModelNG::SetSetFontSize(frameNode, convValue);
}
void SetFontStyleImpl(Ark_NativePointer node,
                      const Opt_FontStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //SecurityComponentMethodModelNG::SetSetFontStyle(frameNode, convValue);
}
void SetFontWeightImpl(Ark_NativePointer node,
                       const Opt_Union_I32_FontWeight_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //SecurityComponentMethodModelNG::SetSetFontWeight(frameNode, convValue);
}
void SetFontFamilyImpl(Ark_NativePointer node,
                       const Opt_Union_String_Resource* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //SecurityComponentMethodModelNG::SetSetFontFamily(frameNode, convValue);
}
void SetFontColorImpl(Ark_NativePointer node,
                      const Opt_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //SecurityComponentMethodModelNG::SetSetFontColor(frameNode, convValue);
}
void SetIconColorImpl(Ark_NativePointer node,
                      const Opt_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //SecurityComponentMethodModelNG::SetSetIconColor(frameNode, convValue);
}
void SetBackgroundColorImpl(Ark_NativePointer node,
                            const Opt_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //SecurityComponentMethodModelNG::SetSetBackgroundColor(frameNode, convValue);
}
void SetBorderStyleImpl(Ark_NativePointer node,
                        const Opt_BorderStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //SecurityComponentMethodModelNG::SetSetBorderStyle(frameNode, convValue);
}
void SetBorderWidthImpl(Ark_NativePointer node,
                        const Opt_Dimension* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //SecurityComponentMethodModelNG::SetSetBorderWidth(frameNode, convValue);
}
void SetBorderColorImpl(Ark_NativePointer node,
                        const Opt_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //SecurityComponentMethodModelNG::SetSetBorderColor(frameNode, convValue);
}
void SetBorderRadiusImpl(Ark_NativePointer node,
                         const Opt_Dimension* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //SecurityComponentMethodModelNG::SetSetBorderRadius(frameNode, convValue);
}
void SetPaddingImpl(Ark_NativePointer node,
                    const Opt_Union_Padding_Dimension* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //SecurityComponentMethodModelNG::SetSetPadding(frameNode, convValue);
}
void SetTextIconSpaceImpl(Ark_NativePointer node,
                          const Opt_Dimension* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //SecurityComponentMethodModelNG::SetSetTextIconSpace(frameNode, convValue);
}
void SetKeyImpl(Ark_NativePointer node,
                const Opt_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //SecurityComponentMethodModelNG::SetSetKey(frameNode, convValue);
}
void SetWidthImpl(Ark_NativePointer node,
                  const Opt_Length* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //SecurityComponentMethodModelNG::SetSetWidth(frameNode, convValue);
}
void SetHeightImpl(Ark_NativePointer node,
                   const Opt_Length* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //SecurityComponentMethodModelNG::SetSetHeight(frameNode, convValue);
}
void SetSizeImpl(Ark_NativePointer node,
                 const Opt_SizeOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //SecurityComponentMethodModelNG::SetSetSize(frameNode, convValue);
}
void SetConstraintSizeImpl(Ark_NativePointer node,
                           const Opt_ConstraintSizeOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //SecurityComponentMethodModelNG::SetSetConstraintSize(frameNode, convValue);
}
void SetAlignImpl(Ark_NativePointer node,
                  const Opt_Alignment* alignType)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = alignType ? Converter::OptConvert<type>(*alignType) : std::nullopt;
    //SecurityComponentMethodModelNG::SetSetAlign(frameNode, convValue);
}
void SetAlignRules0Impl(Ark_NativePointer node,
                        const Opt_AlignRuleOption* alignRule)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = alignRule ? Converter::OptConvert<type>(*alignRule) : std::nullopt;
    //SecurityComponentMethodModelNG::SetSetAlignRules0(frameNode, convValue);
}
void SetAlignRules1Impl(Ark_NativePointer node,
                        const Opt_LocalizedAlignRuleOptions* alignRule)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = alignRule ? Converter::OptConvert<type>(*alignRule) : std::nullopt;
    //SecurityComponentMethodModelNG::SetSetAlignRules1(frameNode, convValue);
}
void SetIdImpl(Ark_NativePointer node,
               const Opt_String* description)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = description ? Converter::OptConvert<type>(*description) : std::nullopt;
    //SecurityComponentMethodModelNG::SetSetId(frameNode, convValue);
}
void SetChainModeImpl(Ark_NativePointer node,
                      const Opt_Axis* direction,
                      const Opt_ChainStyle* style)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(direction);
    //auto convValue = Converter::OptConvert<type>(direction); // for enums
    //SecurityComponentMethodModelNG::SetSetChainMode(frameNode, convValue);
}
void SetMinFontScaleImpl(Ark_NativePointer node,
                         const Opt_Union_Number_Resource* scale)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = scale ? Converter::OptConvert<type>(*scale) : std::nullopt;
    //SecurityComponentMethodModelNG::SetSetMinFontScale(frameNode, convValue);
}
void SetMaxFontScaleImpl(Ark_NativePointer node,
                         const Opt_Union_Number_Resource* scale)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = scale ? Converter::OptConvert<type>(*scale) : std::nullopt;
    //SecurityComponentMethodModelNG::SetSetMaxFontScale(frameNode, convValue);
}
void SetMaxLinesImpl(Ark_NativePointer node,
                     const Opt_Number* line)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = line ? Converter::OptConvert<type>(*line) : std::nullopt;
    //SecurityComponentMethodModelNG::SetSetMaxLines(frameNode, convValue);
}
void SetMinFontSizeImpl(Ark_NativePointer node,
                        const Opt_Union_Number_String_Resource* minSize)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = minSize ? Converter::OptConvert<type>(*minSize) : std::nullopt;
    //SecurityComponentMethodModelNG::SetSetMinFontSize(frameNode, convValue);
}
void SetMaxFontSizeImpl(Ark_NativePointer node,
                        const Opt_Union_Number_String_Resource* maxSize)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = maxSize ? Converter::OptConvert<type>(*maxSize) : std::nullopt;
    //SecurityComponentMethodModelNG::SetSetMaxFontSize(frameNode, convValue);
}
void SetHeightAdaptivePolicyImpl(Ark_NativePointer node,
                                 const Opt_TextHeightAdaptivePolicy* policy)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = policy ? Converter::OptConvert<type>(*policy) : std::nullopt;
    //SecurityComponentMethodModelNG::SetSetHeightAdaptivePolicy(frameNode, convValue);
}
void SetEnabledImpl(Ark_NativePointer node,
                    const Opt_Boolean* respond)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = respond ? Converter::OptConvert<type>(*respond) : std::nullopt;
    //SecurityComponentMethodModelNG::SetSetEnabled(frameNode, convValue);
}
} // SecurityComponentMethodModifier
const GENERATED_ArkUISecurityComponentMethodModifier* GetSecurityComponentMethodModifier()
{
    static const GENERATED_ArkUISecurityComponentMethodModifier ArkUISecurityComponentMethodModifierImpl {
        SecurityComponentMethodModifier::ConstructImpl,
        SecurityComponentMethodModifier::SetIconSizeImpl,
        SecurityComponentMethodModifier::SetLayoutDirectionImpl,
        SecurityComponentMethodModifier::SetPositionImpl,
        SecurityComponentMethodModifier::SetMarkAnchorImpl,
        SecurityComponentMethodModifier::SetOffsetImpl,
        SecurityComponentMethodModifier::SetFontSizeImpl,
        SecurityComponentMethodModifier::SetFontStyleImpl,
        SecurityComponentMethodModifier::SetFontWeightImpl,
        SecurityComponentMethodModifier::SetFontFamilyImpl,
        SecurityComponentMethodModifier::SetFontColorImpl,
        SecurityComponentMethodModifier::SetIconColorImpl,
        SecurityComponentMethodModifier::SetBackgroundColorImpl,
        SecurityComponentMethodModifier::SetBorderStyleImpl,
        SecurityComponentMethodModifier::SetBorderWidthImpl,
        SecurityComponentMethodModifier::SetBorderColorImpl,
        SecurityComponentMethodModifier::SetBorderRadiusImpl,
        SecurityComponentMethodModifier::SetPaddingImpl,
        SecurityComponentMethodModifier::SetTextIconSpaceImpl,
        SecurityComponentMethodModifier::SetKeyImpl,
        SecurityComponentMethodModifier::SetWidthImpl,
        SecurityComponentMethodModifier::SetHeightImpl,
        SecurityComponentMethodModifier::SetSizeImpl,
        SecurityComponentMethodModifier::SetConstraintSizeImpl,
        SecurityComponentMethodModifier::SetAlignImpl,
        SecurityComponentMethodModifier::SetAlignRules0Impl,
        SecurityComponentMethodModifier::SetAlignRules1Impl,
        SecurityComponentMethodModifier::SetIdImpl,
        SecurityComponentMethodModifier::SetChainModeImpl,
        SecurityComponentMethodModifier::SetMinFontScaleImpl,
        SecurityComponentMethodModifier::SetMaxFontScaleImpl,
        SecurityComponentMethodModifier::SetMaxLinesImpl,
        SecurityComponentMethodModifier::SetMinFontSizeImpl,
        SecurityComponentMethodModifier::SetMaxFontSizeImpl,
        SecurityComponentMethodModifier::SetHeightAdaptivePolicyImpl,
        SecurityComponentMethodModifier::SetEnabledImpl,
    };
    return &ArkUISecurityComponentMethodModifierImpl;
}

}
