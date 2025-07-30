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
#include "core/components_ng/pattern/security_component/security_component_model_ng.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/validators.h"
#include "core/interfaces/native/generated/interface/node_api.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::Converter {
template<>
void AssignCast(std::optional<SecurityComponentLayoutDirection>& dst, const Ark_SecurityComponentLayoutDirection& src)
{
    switch (src) {
        case ARK_SECURITY_COMPONENT_LAYOUT_DIRECTION_HORIZONTAL:
            dst = SecurityComponentLayoutDirection::HORIZONTAL;
            break;
        case ARK_SECURITY_COMPONENT_LAYOUT_DIRECTION_VERTICAL:
            dst = SecurityComponentLayoutDirection::VERTICAL;
            break;
        default:
            LOGE("Unexpected enum value in Ark_SecurityComponentLayoutDirection: %{public}d", src);
    }
}
template<>
OffsetT<Dimension> Convert(const Ark_Position& src)
{
    OffsetT<Dimension> offset;
    auto x = Converter::OptConvert<Dimension>(src.x);
    auto y = Converter::OptConvert<Dimension>(src.y);
    if (x.has_value()) {
        offset.SetX(x.value());
    }
    if (y.has_value()) {
        offset.SetY(y.value());
    }
    return offset;
}
template<>
PaddingPropertyT<Dimension> Convert(const Ark_Padding& src)
{
    PaddingPropertyT<Dimension> padding;
    padding.left = Converter::OptConvert<Dimension>(src.left);
    padding.top = Converter::OptConvert<Dimension>(src.top);
    padding.right = Converter::OptConvert<Dimension>(src.right);
    padding.bottom = Converter::OptConvert<Dimension>(src.bottom);
    return padding;
}
template<>
PaddingPropertyT<Dimension> Convert(const Ark_Length& src)
{
    PaddingPropertyT<Dimension> padding;
    auto value = Converter::Convert<Dimension>(src);
    padding.left = value;
    padding.top = value;
    padding.right = value;
    padding.bottom = value;
    return padding;
}
} //namespace OHOS::Ace::NG::Converter

namespace OHOS::Ace::NG::GeneratedModifier {
namespace CommonMethodModifier {
void Width0Impl(Ark_NativePointer node,
    const Opt_Length* value);
void Height0Impl(Ark_NativePointer node,
    const Opt_Length* value);
void SizeImpl(Ark_NativePointer node,
    const Opt_SizeOptions* value);
void ConstraintSizeImpl(Ark_NativePointer node,
    const Opt_ConstraintSizeOptions* value);
void OffsetImpl(Ark_NativePointer node,
    const Opt_Union_Position_Edges_LocalizedEdges* value);
void IdImpl(Ark_NativePointer node,
    const Opt_String* value);
void AlignRules0Impl(Ark_NativePointer node,
    const Opt_AlignRuleOption* value);
void AlignRules1Impl(Ark_NativePointer node,
    const Opt_LocalizedAlignRuleOptions* value);
void EnabledImpl(Ark_NativePointer node,
    const Opt_Boolean *value);
void ChainModeImpl(Ark_NativePointer node,
    const Opt_Axis *direction,
    const Opt_ChainStyle *style);
} // namespace CommonMethodModifier
namespace SecurityComponentMethodModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                Ark_Int32 flags)
{
    return {};
}
void IconSizeImpl(Ark_NativePointer node,
                  const Opt_Length* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto valueOpt = Converter::OptConvert<Dimension>(*value);
    Validator::ValidateNonNegative(valueOpt);
    SecurityComponentModelNG::SetIconSize(frameNode, valueOpt);
}
void LayoutDirectionImpl(Ark_NativePointer node,
                         const Opt_SecurityComponentLayoutDirection* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto layoutDirection = Converter::OptConvert<SecurityComponentLayoutDirection>(*value);
    SecurityComponentModelNG::SetTextIconLayoutDirection(frameNode, layoutDirection);
}
void PositionImpl(Ark_NativePointer node,
                  const Opt_Position* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<OffsetT<Dimension>>(*value);
    if (!convValue) {
        // TODO: Reset value
        return;
    }
    // ViewAbstract::SetPosition(frameNode, *convValue);
}
void MarkAnchorImpl(Ark_NativePointer node,
                    const Opt_Position* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
}
void OffsetImpl(Ark_NativePointer node,
                const Opt_Union_Position_Edges_LocalizedEdges* value)
{
    CommonMethodModifier::OffsetImpl(node, value);
}
void FontSizeImpl(Ark_NativePointer node,
                  const Opt_Length* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto fontSize = Converter::OptConvert<Dimension>(*value);
    Validator::ValidatePositive(fontSize);
    Validator::ValidateNonPercent(fontSize);
    SecurityComponentModelNG::SetFontSize(frameNode, fontSize);
}
void FontStyleImpl(Ark_NativePointer node,
                   const Opt_FontStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    SecurityComponentModelNG::SetFontStyle(frameNode, Converter::OptConvert<Ace::FontStyle>(*value));
}
void FontWeightImpl(Ark_NativePointer node,
                    const Opt_Union_Number_FontWeight_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    SecurityComponentModelNG::SetFontWeight(frameNode, Converter::OptConvert<FontWeight>(*value));
}
void FontFamilyImpl(Ark_NativePointer node,
                    const Opt_Union_String_Resource* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    std::optional<StringArray> families;
    if (auto fontfamiliesOpt = Converter::OptConvert<Converter::FontFamilies>(*value); fontfamiliesOpt) {
        families = fontfamiliesOpt->families;
    }
    Validator::ValidateNonEmpty(families);
    SecurityComponentModelNG::SetFontFamily(frameNode, families);
}
void FontColorImpl(Ark_NativePointer node,
                   const Opt_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto fontColor = Converter::OptConvert<Color>(*value);
    SecurityComponentModelNG::SetFontColor(frameNode, fontColor);
}
void IconColorImpl(Ark_NativePointer node,
                   const Opt_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto iconColor = Converter::OptConvert<Color>(*value);
    SecurityComponentModelNG::SetIconColor(frameNode, iconColor);
}
void BackgroundColorImpl(Ark_NativePointer node,
                         const Opt_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto сolor = Converter::OptConvert<Color>(*value);
    SecurityComponentModelNG::SetBackgroundColor(frameNode, сolor);
}
void BorderStyleImpl(Ark_NativePointer node,
                     const Opt_BorderStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::OptConvert<BorderStyle>(*value);
    SecurityComponentModelNG::SetBackgroundBorderStyle(frameNode, optValue);
}
void BorderWidthImpl(Ark_NativePointer node,
                     const Opt_Length* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<Dimension>(*value);
    Validator::ValidateNonNegative(convValue);
    SecurityComponentModelNG::SetBackgroundBorderWidth(frameNode, convValue);
}
void BorderColorImpl(Ark_NativePointer node,
                     const Opt_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto color = Converter::OptConvert<Color>(*value);
    SecurityComponentModelNG::SetBackgroundBorderColor(frameNode, color);
}
void BorderRadius0Impl(Ark_NativePointer node,
                       const Opt_Length* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<Dimension>(*value);
    Validator::ValidateNonNegative(convValue);
    SecurityComponentModelNG::SetBackgroundBorderRadius(frameNode, convValue);
}
void BorderRadius1Impl(Ark_NativePointer node,
                       const Opt_Union_Dimension_BorderRadiuses* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<BorderRadiusProperty>(*value);
    SecurityComponentModelNG::SetBackgroundBorderRadius(frameNode, convValue);
}
void PaddingImpl(Ark_NativePointer node,
                 const Opt_Union_Padding_Dimension* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto padding = Converter::OptConvert<PaddingPropertyT<Dimension>>(*value);
    if (padding) {
        SecurityComponentModelNG::SetBackgroundPadding(frameNode, padding->left, padding->right, padding->top,
            padding->bottom);
    } else {
        SecurityComponentModelNG::SetBackgroundPadding(frameNode, std::nullopt, std::nullopt, std::nullopt,
            std::nullopt);
    }
}
void TextIconSpaceImpl(Ark_NativePointer node,
                       const Opt_Length* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto valueOpt = Converter::OptConvert<Dimension>(*value);
    Validator::ValidateNonNegative(valueOpt);
    SecurityComponentModelNG::SetTextIconSpace(frameNode, valueOpt);
}
void KeyImpl(Ark_NativePointer node,
             const Opt_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<std::string>(*value);
    if (!convValue) {
        // TODO: Reset value
        return;
    }
}
void WidthImpl(Ark_NativePointer node,
               const Opt_Length* value)
{
    CommonMethodModifier::Width0Impl(node, value);
}
void HeightImpl(Ark_NativePointer node,
                const Opt_Length* value)
{
    CommonMethodModifier::Height0Impl(node, value);
}
void SizeImpl(Ark_NativePointer node,
              const Opt_SizeOptions* value)
{
    CommonMethodModifier::SizeImpl(node, value);
}
void ConstraintSizeImpl(Ark_NativePointer node,
                        const Opt_ConstraintSizeOptions* value)
{
    CommonMethodModifier::ConstraintSizeImpl(node, value);
}
void AlignImpl(Ark_NativePointer node,
               const Opt_Alignment* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<Alignment>(*value);
    SecurityComponentModelNG::SetAlign(frameNode, convValue);
}
void AlignRules0Impl(Ark_NativePointer node,
                     const Opt_AlignRuleOption* value)
{
    CommonMethodModifier::AlignRules0Impl(node, value);
}
void AlignRules1Impl(Ark_NativePointer node,
                     const Opt_LocalizedAlignRuleOptions* value)
{
    CommonMethodModifier::AlignRules1Impl(node, value);
}
void IdImpl(Ark_NativePointer node,
            const Opt_String* value)
{
    CommonMethodModifier::IdImpl(node, value);
}
void MinFontScaleImpl(Ark_NativePointer node,
                      const Opt_Union_Number_Resource* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto minFontScale = Converter::OptConvert<float>(*value);
    Validator::ValidatePositive(minFontScale);
    const auto maxValue = 1.f;
    Validator::ValidateLessOrEqual(minFontScale, maxValue);
    SecurityComponentModelNG::SetMinFontScale(frameNode, minFontScale);
}
void MaxFontScaleImpl(Ark_NativePointer node,
                      const Opt_Union_Number_Resource* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto maxFontScale = Converter::OptConvert<float>(*value);
    const auto minValue = 1.f;
    Validator::ValidateGreatOrEqual(maxFontScale, minValue);
    SecurityComponentModelNG::SetMaxFontScale(frameNode, maxFontScale);
}
void MaxLinesImpl(Ark_NativePointer node,
                  const Opt_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto maxLines = Converter::OptConvert<int32_t>(*value);
    Validator::ValidateNonNegative(maxLines);
    SecurityComponentModelNG::SetMaxLines(frameNode, maxLines);
}
void MinFontSizeImpl(Ark_NativePointer node,
                     const Opt_Union_Number_String_Resource* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto fontSize = Converter::OptConvert<Dimension>(*value);
    Validator::ValidateNonNegative(fontSize);
    Validator::ValidateNonPercent(fontSize);
    SecurityComponentModelNG::SetAdaptMinFontSize(frameNode, fontSize);
}
void MaxFontSizeImpl(Ark_NativePointer node,
                     const Opt_Union_Number_String_Resource* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto fontSize = Converter::OptConvert<Dimension>(*value);
    Validator::ValidateNonNegative(fontSize);
    Validator::ValidateNonPercent(fontSize);
    SecurityComponentModelNG::SetAdaptMaxFontSize(frameNode, fontSize);
}
void HeightAdaptivePolicyImpl(Ark_NativePointer node,
                              const Opt_TextHeightAdaptivePolicy* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<TextHeightAdaptivePolicy>(*value);
    SecurityComponentModelNG::SetHeightAdaptivePolicy(frameNode, convValue);
}
void EnabledImpl(Ark_NativePointer node,
                 const Opt_Boolean* value)
{
    CommonMethodModifier::EnabledImpl(node, value);
}
void ChainModeImpl(Ark_NativePointer node,
                   const Opt_Axis* direction,
                   const Opt_ChainStyle* style)
{
    CommonMethodModifier::ChainModeImpl(node, direction, style);
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
