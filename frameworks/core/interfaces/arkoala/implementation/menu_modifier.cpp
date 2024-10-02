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
#include "core/components_ng/pattern/menu/menu_model_ng.h"
#include "core/components_ng/property/border_property.h"
#include "core/interfaces/arkoala/utility/converter.h"
#include "core/interfaces/arkoala/utility/reverse_converter.h"
#include "core/interfaces/arkoala/utility/validators.h"
#include "core/interfaces/arkoala/generated/interface/node_api.h"

namespace OHOS::Ace::NG {
using BorderRadiusesType = std::variant<std::optional<Dimension>, BorderRadiusProperty>;
}

namespace OHOS::Ace::NG::Converter {
template<>
BorderRadiusProperty Convert(const Ark_BorderRadiuses& src)
{
    auto border = BorderRadiusProperty();
    border.radiusTopLeft = OptConvert<Dimension>(src.topLeft);
    border.radiusTopRight = OptConvert<Dimension>(src.topRight);
    border.radiusBottomLeft = OptConvert<Dimension>(src.bottomLeft);
    border.radiusBottomRight = OptConvert<Dimension>(src.bottomRight);
    return border;
}

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
    return dst;
}
}

namespace OHOS::Ace::NG::GeneratedModifier {
namespace MenuInterfaceModifier {
void SetMenuOptionsImpl(Ark_NativePointer node)
{
    // No implementation is required
}
} // MenuInterfaceModifier
namespace MenuAttributeModifier {
void FontSizeImpl(Ark_NativePointer node,
                  const Ark_Length* value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    MenuModelNG::SetFontSize(frameNode, Converter::Convert<Dimension>(*value));
}
void FontImpl(Ark_NativePointer node,
              const Ark_Font* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto fontOpt = Converter::OptConvert<Font>(*value);
    if (fontOpt.has_value()) {
        MenuModelNG::SetFontSize(frameNode, fontOpt.value().fontSize);
        MenuModelNG::SetFontWeight(frameNode, fontOpt.value().fontWeight);
        MenuModelNG::SetFontStyle(frameNode, fontOpt.value().fontStyle);
        MenuModelNG::SetFontFamily(frameNode, fontOpt.value().fontFamilies);
    }
}
void FontColorImpl(Ark_NativePointer node,
                   const ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    MenuModelNG::SetFontColor(frameNode, Converter::OptConvert<Color>(*value));
}
void RadiusImpl(Ark_NativePointer node,
                const Type_MenuAttribute_radius_Arg0* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);

    auto radiusesOpt = Converter::OptConvert<BorderRadiusesType>(*value);
    if (radiusesOpt) {
        if (auto radiusPtr = std::get_if<std::optional<Dimension>>(&(*radiusesOpt)); radiusPtr) {
            Validator::ValidateNonNegative(*radiusPtr);
            MenuModelNG::SetBorderRadius(frameNode, *radiusPtr);
        }
        if (auto radiusPtr = std::get_if<BorderRadiusProperty>(&(*radiusesOpt)); radiusPtr) {
            Validator::ValidateNonNegative(radiusPtr->radiusTopLeft);
            Validator::ValidateNonNegative(radiusPtr->radiusTopRight);
            Validator::ValidateNonNegative(radiusPtr->radiusBottomLeft);
            Validator::ValidateNonNegative(radiusPtr->radiusBottomRight);
            MenuModelNG::SetBorderRadius(frameNode,
                radiusPtr->radiusTopLeft, radiusPtr->radiusTopRight,
                radiusPtr->radiusBottomLeft, radiusPtr->radiusBottomRight);
        }
    }
}
void MenuItemDividerImpl(Ark_NativePointer node,
                         const Type_MenuAttribute_menuItemDivider_Arg0* options)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(options);
    auto divider = Converter::OptConvert<V2::ItemDivider>(*options);
    MenuModelNG::SetItemDivider(frameNode, divider);
    LOGE("MenuModifier::MenuItemDividerImpl is not implemented, Ark_CustomObject is not supported!");
}
void MenuItemGroupDividerImpl(Ark_NativePointer node,
                              const Type_MenuAttribute_menuItemGroupDivider_Arg0* options)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(options);
    auto divider = Converter::OptConvert<V2::ItemDivider>(*options);
    MenuModelNG::SetItemGroupDivider(frameNode, divider);
    LOGE("MenuModifier::MenuItemGroupDividerImpl is not implemented, Ark_CustomObject is not supported!");
}
void SubMenuExpandingModeImpl(Ark_NativePointer node,
                              enum Ark_SubMenuExpandingMode mode)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    MenuModelNG::SetExpandingMode(frameNode, Converter::OptConvert<SubMenuExpandingMode>(mode));
}
} // MenuAttributeModifier
const GENERATED_ArkUIMenuModifier* GetMenuModifier()
{
    static const GENERATED_ArkUIMenuModifier ArkUIMenuModifierImpl {
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
