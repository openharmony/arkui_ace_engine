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
#include "core/components_ng/pattern/menu/menu_model_static.h"
#include "core/components_ng/property/border_property.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/interfaces/native/utility/validators.h"
#include "core/interfaces/native/generated/interface/node_api.h"

namespace OHOS::Ace::NG {
using BorderRadiusesType = std::variant<std::optional<Dimension>, BorderRadiusProperty>;
}

namespace OHOS::Ace::NG::Converter {
template<>
BorderRadiusesType Convert(const Ark_Length& src)
{
    return Converter::OptConvert<Dimension>(src);
}

template<>
BorderRadiusesType Convert(const Ark_BorderRadiuses& src)
{
    return Converter::Convert<BorderRadiusProperty>(src);
}

template<>
V2::ItemDivider Convert(const Ark_DividerStyleOptions& src)
{
    auto dst = V2::ItemDivider{}; // this struct is initialized by default
    auto colorOpt = OptConvert<Color>(src.color);
    if (colorOpt.has_value()) {
        dst.color = colorOpt.value();
    }
    auto strokeWidth = OptConvert<Dimension>(src.strokeWidth);
    Validator::ValidateNonNegative(strokeWidth);
    if (strokeWidth.has_value()) {
        dst.strokeWidth = strokeWidth.value();
    }
    auto startMargin = OptConvert<Dimension>(src.startMargin);
    Validator::ValidateNonNegative(startMargin);
    if (startMargin.has_value()) {
        dst.startMargin = startMargin.value();
    }
    auto endMargin = OptConvert<Dimension>(src.endMargin);
    Validator::ValidateNonNegative(endMargin);
    if (endMargin.has_value()) {
        dst.endMargin = endMargin.value();
    }
    return dst;
}
}

namespace OHOS::Ace::NG::GeneratedModifier {
namespace MenuModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                Ark_Int32 flags)
{
    auto frameNode = MenuModelStatic::CreateFrameNode(id);
    CHECK_NULL_RETURN(frameNode, nullptr);
    frameNode->IncRefCount();
    return AceType::RawPtr(frameNode);
}
} // MenuModifier
namespace MenuInterfaceModifier {
void SetMenuOptionsImpl(Ark_NativePointer node)
{
    // No implementation is required
}
} // MenuInterfaceModifier
namespace MenuAttributeModifier {
void FontSizeImpl(Ark_NativePointer node,
                  const Opt_Length* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    MenuModelStatic::SetFontSize(frameNode, Converter::OptConvert<Dimension>(*value));
}
void FontImpl(Ark_NativePointer node,
              const Opt_Font* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto fontOpt = Converter::OptConvert<Font>(*value);
    if (fontOpt.has_value()) {
        // TODO: Reset value
        MenuModelStatic::SetFontSize(frameNode, fontOpt.value().fontSize);
        MenuModelStatic::SetFontWeight(frameNode, fontOpt.value().fontWeight);
        MenuModelStatic::SetFontStyle(frameNode, fontOpt.value().fontStyle);
        MenuModelStatic::SetFontFamily(frameNode, fontOpt.value().fontFamilies);
    }
}
void FontColorImpl(Ark_NativePointer node,
                   const Opt_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    MenuModelStatic::SetFontColor(frameNode, Converter::OptConvert<Color>(*value));
}
void RadiusImpl(Ark_NativePointer node,
                const Opt_Union_Dimension_BorderRadiuses* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto radiusesOpt = Converter::OptConvert<BorderRadiusesType>(*value);
    if (radiusesOpt) {
        // TODO: Reset value
        if (auto radiusPtr = std::get_if<std::optional<Dimension>>(&(*radiusesOpt)); radiusPtr) {
            Validator::ValidateNonNegative(*radiusPtr);
            MenuModelStatic::SetBorderRadius(frameNode, *radiusPtr);
        }
        if (auto radiusPtr = std::get_if<BorderRadiusProperty>(&(*radiusesOpt)); radiusPtr) {
            Validator::ValidateNonNegative(radiusPtr->radiusTopLeft);
            Validator::ValidateNonNegative(radiusPtr->radiusTopRight);
            Validator::ValidateNonNegative(radiusPtr->radiusBottomLeft);
            Validator::ValidateNonNegative(radiusPtr->radiusBottomRight);
            MenuModelStatic::SetBorderRadius(frameNode,
                radiusPtr->radiusTopLeft, radiusPtr->radiusTopRight,
                radiusPtr->radiusBottomLeft, radiusPtr->radiusBottomRight);
        }
    }
}
void MenuItemDividerImpl(Ark_NativePointer node,
                         const Opt_DividerStyleOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto divider = Converter::OptConvert<V2::ItemDivider>(*value);
    MenuModelStatic::SetItemDivider(frameNode, divider, std::nullopt);
}
void MenuItemGroupDividerImpl(Ark_NativePointer node,
                              const Opt_DividerStyleOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto divider = Converter::OptConvert<V2::ItemDivider>(*value);
    MenuModelStatic::SetItemGroupDivider(frameNode, divider, std::nullopt);
}
void SubMenuExpandingModeImpl(Ark_NativePointer node,
                              const Opt_SubMenuExpandingMode* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    MenuModelStatic::SetExpandingMode(frameNode, Converter::OptConvert<SubMenuExpandingMode>(*value));
}
} // MenuAttributeModifier
const GENERATED_ArkUIMenuModifier* GetMenuModifier()
{
    static const GENERATED_ArkUIMenuModifier ArkUIMenuModifierImpl {
        MenuModifier::ConstructImpl,
        MenuInterfaceModifier::SetMenuOptionsImpl,
        MenuAttributeModifier::FontSizeImpl,
        MenuAttributeModifier::FontImpl,
        MenuAttributeModifier::FontColorImpl,
        MenuAttributeModifier::RadiusImpl,
        MenuAttributeModifier::MenuItemDividerImpl,
        MenuAttributeModifier::MenuItemGroupDividerImpl,
        MenuAttributeModifier::SubMenuExpandingModeImpl,
    };
    return &ArkUIMenuModifierImpl;
}

}
