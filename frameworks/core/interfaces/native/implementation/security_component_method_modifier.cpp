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
void WidthImpl(Ark_NativePointer node,
               const Ark_Length* value);
void HeightImpl(Ark_NativePointer node,
                const Ark_Length* value);
void SizeImpl(Ark_NativePointer node,
              const Ark_SizeOptions* value);
void ConstraintSizeImpl(Ark_NativePointer node,
                        const Ark_ConstraintSizeOptions* value);
void OffsetImpl(Ark_NativePointer node,
                const Ark_Union_Position_Edges_LocalizedEdges* value);
} // namespace CommonMethodModifier
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
    auto valueOpt = Converter::OptConvert<Dimension>(*value);
    Validator::ValidateNonNegative(valueOpt);
    SecurityComponentModelNG::SetIconSize(frameNode, valueOpt);
}
void LayoutDirectionImpl(Ark_NativePointer node,
                         Ark_SecurityComponentLayoutDirection value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto layoutDirection = Converter::OptConvert<SecurityComponentLayoutDirection>(value);
    SecurityComponentModelNG::SetTextIconLayoutDirection(frameNode, layoutDirection);
}
void PositionImpl(Ark_NativePointer node,
                  const Ark_Position* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    ViewAbstract::SetPosition(frameNode, Converter::Convert<OffsetT<Dimension>>(*value));
}
void MarkAnchorImpl(Ark_NativePointer node,
                    const Ark_Position* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    ViewAbstract::MarkAnchor(frameNode, Converter::Convert<OffsetT<Dimension>>(*value));
}
void OffsetImpl(Ark_NativePointer node,
                const Ark_Union_Position_Edges_LocalizedEdges* value)
{
    CommonMethodModifier::OffsetImpl(node, value);
}
void FontSizeImpl(Ark_NativePointer node,
                  const Ark_Length* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto fontSize = Converter::OptConvert<Dimension>(*value);
    Validator::ValidatePositive(fontSize);
    Validator::ValidateNonPercent(fontSize);
    SecurityComponentModelNG::SetFontSize(frameNode, fontSize);
}
void FontStyleImpl(Ark_NativePointer node,
                   Ark_FontStyle value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    SecurityComponentModelNG::SetFontStyle(frameNode, Converter::OptConvert<Ace::FontStyle>(value));
}
void FontWeightImpl(Ark_NativePointer node,
                    const Ark_Union_Number_FontWeight_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    SecurityComponentModelNG::SetFontWeight(frameNode, Converter::OptConvert<FontWeight>(*value));
}
void FontFamilyImpl(Ark_NativePointer node,
                    const Ark_Union_String_Resource* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    std::optional<StringArray> families;
    if (auto fontfamiliesOpt = Converter::OptConvert<Converter::FontFamilies>(*value); fontfamiliesOpt) {
        families = fontfamiliesOpt->families;
    }
    SecurityComponentModelNG::SetFontFamily(frameNode, families);
}
void FontColorImpl(Ark_NativePointer node,
                   const Ark_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto fontColor = Converter::OptConvert<Color>(*value);
    SecurityComponentModelNG::SetFontColor(frameNode, fontColor);
}
void IconColorImpl(Ark_NativePointer node,
                   const Ark_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto iconColor = Converter::OptConvert<Color>(*value);
    SecurityComponentModelNG::SetIconColor(frameNode, iconColor);
}
void BackgroundColorImpl(Ark_NativePointer node,
                         const Ark_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto сolor = Converter::OptConvert<Color>(*value);
    SecurityComponentModelNG::SetBackgroundColor(frameNode, сolor);
}
void BorderStyleImpl(Ark_NativePointer node,
                     Ark_BorderStyle value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::OptConvert<BorderStyle>(value);
    SecurityComponentModelNG::SetBackgroundBorderStyle(frameNode, optValue);
}
void BorderWidthImpl(Ark_NativePointer node,
                     const Ark_Length* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto convValue = Converter::OptConvert<Dimension>(*value);
    Validator::ValidateNonNegative(convValue);
    SecurityComponentModelNG::SetBackgroundBorderWidth(frameNode, convValue);
}
void BorderColorImpl(Ark_NativePointer node,
                     const Ark_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto color = Converter::OptConvert<Color>(*value);
    SecurityComponentModelNG::SetBackgroundBorderColor(frameNode, color);
}
void BorderRadiusImpl(Ark_NativePointer node,
                      const Ark_Length* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto convValue = Converter::OptConvert<Dimension>(*value);
    Validator::ValidateNonNegative(convValue);
    SecurityComponentModelNG::SetBackgroundBorderRadius(frameNode, convValue);
}
void PaddingImpl(Ark_NativePointer node,
                 const Ark_Union_Padding_Dimension* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
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
                       const Ark_Length* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto valueOpt = Converter::OptConvert<Dimension>(*value);
    Validator::ValidateNonNegative(valueOpt);
    SecurityComponentModelNG::SetTextIconSpace(frameNode, valueOpt);
}
void KeyImpl(Ark_NativePointer node,
             const Ark_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto convValue = Converter::Convert<std::string>(*value);
    ViewAbstract::SetInspectorId(frameNode, convValue);
}
void WidthImpl(Ark_NativePointer node,
               const Ark_Length* value)
{
    CommonMethodModifier::WidthImpl(node, value);
}
void HeightImpl(Ark_NativePointer node,
                const Ark_Length* value)
{
    CommonMethodModifier::HeightImpl(node, value);
}
void SizeImpl(Ark_NativePointer node,
              const Ark_SizeOptions* value)
{
    CommonMethodModifier::SizeImpl(node, value);
}
void ConstraintSizeImpl(Ark_NativePointer node,
                        const Ark_ConstraintSizeOptions* value)
{
    CommonMethodModifier::ConstraintSizeImpl(node, value);
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
        SecurityComponentMethodModifier::BorderRadiusImpl,
        SecurityComponentMethodModifier::PaddingImpl,
        SecurityComponentMethodModifier::TextIconSpaceImpl,
        SecurityComponentMethodModifier::KeyImpl,
        SecurityComponentMethodModifier::WidthImpl,
        SecurityComponentMethodModifier::HeightImpl,
        SecurityComponentMethodModifier::SizeImpl,
        SecurityComponentMethodModifier::ConstraintSizeImpl,
    };
    return &ArkUISecurityComponentMethodModifierImpl;
}

}
