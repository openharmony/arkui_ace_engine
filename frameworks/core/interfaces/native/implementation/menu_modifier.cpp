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
#include "core/components_ng/pattern/menu/menu_model_ng.h"
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
    return nullptr;
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
                  const Ark_Length* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    MenuModelNG::SetFontSize(frameNode, Converter::Convert<Dimension>(*value));
}
void FontImpl(Ark_NativePointer node,
              const Ark_Font* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto fontOpt = Converter::OptConvert<Font>(*value);
    if (fontOpt.has_value()) {
        MenuModelNG::SetFontFamily(frameNode, fontOpt.value().fontFamilies);
    }
}
void FontColorImpl(Ark_NativePointer node,
                   const Ark_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    MenuModelNG::SetFontColor(frameNode, Converter::OptConvert<Color>(*value));
}
void RadiusImpl(Ark_NativePointer node,
                const Ark_Union_Dimension_BorderRadiuses* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);

    auto radiusesOpt = Converter::OptConvert<BorderRadiusesType>(*value);
    if (radiusesOpt) {
        if (auto radiusPtr = std::get_if<std::optional<Dimension>>(&(*radiusesOpt)); radiusPtr) {
            Validator::ValidateNonNegative(*radiusPtr);
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
                         const Opt_DividerStyleOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto divider = Converter::OptConvert<V2::ItemDivider>(*value);
}
void MenuItemGroupDividerImpl(Ark_NativePointer node,
                              const Opt_DividerStyleOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto divider = Converter::OptConvert<V2::ItemDivider>(*value);
}
void SubMenuExpandingModeImpl(Ark_NativePointer node,
                              Ark_SubMenuExpandingMode value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
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
