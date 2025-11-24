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
#include "core/interfaces/native/generated/interface/arkoala_api_generated.h"
#include "core/interfaces/native/implementation/symbol_glyph_modifier_peer.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/interfaces/native/utility/validators.h"

namespace OHOS::Ace::NG {
using BorderRadiusesType = std::variant<std::optional<Dimension>, BorderRadiusProperty>;
}

namespace OHOS::Ace::NG::Converter {
template<>
BorderRadiusesType Convert(const Ark_Number& src)
{
    return Converter::OptConvert<Dimension>(src);
}

template<>
BorderRadiusesType Convert(const Ark_String& src)
{
    return Converter::OptConvert<Dimension>(src);
}

template<>
BorderRadiusesType Convert(const Ark_Resource& src)
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

template<>
DividerMode Convert(const Ark_DividerStyleOptions& src)
{
    DividerMode mode = OptConvert<DividerMode>(src.mode).value_or(DividerMode::FLOATING_ABOVE_MENU);
    return mode;
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
void SetFontImpl(Ark_NativePointer node,
                 const Opt_Font* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto fontOpt = Converter::OptConvertPtr<Font>(value);
    if (fontOpt.has_value()) {
        // Implement Reset value
        MenuModelStatic::SetFontSize(frameNode, fontOpt.value().fontSize);
        MenuModelStatic::SetFontWeight(frameNode, fontOpt.value().fontWeight);
        MenuModelStatic::SetFontStyle(frameNode, fontOpt.value().fontStyle);
        MenuModelStatic::SetFontFamily(frameNode, fontOpt.value().fontFamilies);
    }
}
void SetFontColorImpl(Ark_NativePointer node,
                      const Opt_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    MenuModelStatic::SetFontColor(frameNode, Converter::OptConvertPtr<Color>(value));
}
void SetRadiusImpl(Ark_NativePointer node,
                   const Opt_Union_Dimension_BorderRadiuses* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto radiusesOpt = Converter::OptConvertPtr<BorderRadiusesType>(value);
    if (radiusesOpt) {
        // Implement Reset value
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
void SetMenuItemDividerImpl(Ark_NativePointer node,
                            const Opt_DividerStyleOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto divider = Converter::OptConvert<V2::ItemDivider>(*value);
    auto mode = Converter::OptConvert<DividerMode>(*value);
    MenuModelStatic::SetItemDivider(frameNode, divider, mode);
}
void SetMenuItemGroupDividerImpl(Ark_NativePointer node,
                                 const Opt_DividerStyleOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto divider = Converter::OptConvert<V2::ItemDivider>(*value);
    auto mode = Converter::OptConvert<DividerMode>(*value);
    MenuModelStatic::SetItemGroupDivider(frameNode, divider, mode);
}
void SetSubMenuExpandingModeImpl(Ark_NativePointer node,
                                 const Opt_SubMenuExpandingMode* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    MenuModelStatic::SetExpandingMode(frameNode, Converter::OptConvertPtr<SubMenuExpandingMode>(value));
}
void SetSubMenuExpandSymbolImpl(Ark_NativePointer node, const Opt_SymbolGlyphModifier* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto expandSymbol = Converter::OptConvert<Ark_SymbolGlyphModifier>(*value);
    if (expandSymbol && *expandSymbol) {
        MenuModelStatic::SetExpandSymbol(frameNode, (*expandSymbol)->symbolApply);
        PeerUtils::DestroyPeer(*expandSymbol);
    } else {
        MenuModelStatic::SetExpandSymbol(frameNode, nullptr);
    }
}
} // MenuAttributeModifier
const GENERATED_ArkUIMenuModifier* GetMenuModifier()
{
    static const GENERATED_ArkUIMenuModifier ArkUIMenuModifierImpl {
        MenuModifier::ConstructImpl,
        MenuInterfaceModifier::SetMenuOptionsImpl,
        MenuAttributeModifier::SetFontImpl,
        MenuAttributeModifier::SetFontColorImpl,
        MenuAttributeModifier::SetRadiusImpl,
        MenuAttributeModifier::SetMenuItemDividerImpl,
        MenuAttributeModifier::SetMenuItemGroupDividerImpl,
        MenuAttributeModifier::SetSubMenuExpandingModeImpl,
        MenuAttributeModifier::SetSubMenuExpandSymbolImpl,
    };
    return &ArkUIMenuModifierImpl;
}

}
