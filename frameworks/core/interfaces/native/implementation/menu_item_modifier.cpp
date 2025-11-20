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
#include "core/components_ng/pattern/menu/menu_item/menu_item_model_static.h"
#include "core/interfaces/native/implementation/symbol_glyph_modifier_peer.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"

namespace OHOS::Ace::NG {
namespace {
using SelectIconType = std::variant<bool, std::optional<std::string>, std::optional<SymbolGlyphModifierPeer *>>;
std::optional<bool> ProcessBindableSelected(FrameNode* frameNode, const Opt_Union_Boolean_Bindable_Boolean *value)
{
    std::optional<bool> result;
    Converter::VisitUnionPtr(value,
        [&result](const Ark_Boolean& src) {
            result = Converter::OptConvert<bool>(src);
        },
        [&result, frameNode](const Ark_Bindable_Boolean& src) {
            result = Converter::OptConvert<bool>(src.value);
            WeakPtr<FrameNode> weakNode = AceType::WeakClaim(frameNode);
            auto onEvent = [arkCallback = CallbackHelper(src.onChange), weakNode](bool selected) {
                PipelineContext::SetCallBackNode(weakNode);
                arkCallback.Invoke(Converter::ArkValue<Ark_Boolean>(selected));
            };
            MenuItemModelStatic::SetSelectedChangeEvent(frameNode, std::move(onEvent));
        },
        [] {});
    return result;
}
} // namespace

namespace Converter {
template<>
SelectIconType Convert(const Ark_Boolean& src)
{
    return Converter::Convert<bool>(src);
}

template<>
SelectIconType Convert(const Ark_ResourceStr& src)
{
    return Converter::OptConvert<std::string>(src);
}

template<>
SelectIconType Convert(const Ark_Resource& src)
{
    return Converter::OptConvert<std::string>(src);
}

template<>
SelectIconType Convert(const Ark_String& src)
{
    return Converter::OptConvert<std::string>(src);
}

template<>
SelectIconType Convert(const Ark_SymbolGlyphModifier& src)
{
    return Converter::OptConvert<Ark_SymbolGlyphModifier>(src);
}

template<>
void AssignCast(std::optional<std::function<void(WeakPtr<NG::FrameNode>)>>& dst, const Ark_SymbolGlyphModifier& src)
{
    LOGE("MenuItemModifier::SetMenuItemOptionsImpl symbolStart and symbolEnd attributes are stubs.");
    dst = std::nullopt;
}
} // namespace Converter
} // namespace OHOS::Ace::NG

namespace OHOS::Ace::NG::GeneratedModifier {
namespace MenuItemModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                Ark_Int32 flags)
{
    auto frameNode = MenuItemModelStatic::CreateFrameNode(id);
    CHECK_NULL_RETURN(frameNode, nullptr);
    frameNode->IncRefCount();
    return AceType::RawPtr(frameNode);
}
} // MenuItemModifier
namespace MenuItemInterfaceModifier {
void SetMenuItemOptionsImpl(Ark_NativePointer node,
                            const Opt_Union_MenuItemOptions_CustomNodeBuilder* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    Converter::VisitUnionPtr(value,
        [frameNode, node](const Ark_MenuItemOptions& value0) {
            MenuItemProperties menuItemProps;
            std::optional<std::string> content = Converter::OptConvert<std::string>(value0.content);
            menuItemProps.content = content ? content.value() : "";
            menuItemProps.startIcon = Converter::OptConvert<ImageSourceInfo>(value0.startIcon);
            menuItemProps.endIcon = Converter::OptConvert<ImageSourceInfo>(value0.endIcon);
            menuItemProps.labelInfo = Converter::OptConvert<std::string>(value0.labelInfo);
            menuItemProps.buildFunc = std::nullopt;
            auto builderOpt = Converter::OptConvert<CustomNodeBuilder>(value0.builder);
            if (builderOpt.has_value()) {
                auto builder = [callback = CallbackHelper(builderOpt.value()), node]() -> RefPtr<UINode> {
                    auto subMenuNode = callback.BuildSync(node);
                    ViewStackProcessor::GetInstance()->Push(subMenuNode);
                    return subMenuNode;
                };
                menuItemProps.buildFunc = builder;
            }
            MenuItemModelStatic::AddRowChild(frameNode, menuItemProps);
            MenuItemModelStatic::UpdateMenuProperty(frameNode, menuItemProps);
            auto symbolStart = Converter::OptConvert<Ark_SymbolGlyphModifier>(value0.symbolStartIcon);
            if (symbolStart && *symbolStart) {
                MenuItemModelStatic::SetSymbolStartIcon(frameNode, (*symbolStart)->symbolApply);
                PeerUtils::DestroyPeer(*symbolStart);
            }
            auto symbolEnd = Converter::OptConvert<Ark_SymbolGlyphModifier>(value0.symbolEndIcon);
            if (symbolEnd && *symbolEnd) {
                MenuItemModelStatic::SetSymbolEndIcon(frameNode, (*symbolEnd)->symbolApply);
                PeerUtils::DestroyPeer(*symbolEnd);
            }
        },
        [frameNode, node](const CustomNodeBuilder& value1) {
            CallbackHelper(value1).BuildAsync([frameNode](const RefPtr<UINode>& uiNode) {
                MenuItemModelStatic::AddChild(frameNode, uiNode);
                }, node);
        },
        []() {}
    );
}
} // MenuItemInterfaceModifier
namespace MenuItemAttributeModifier {
void SetSelectedImpl(Ark_NativePointer node,
                     const Opt_Union_Boolean_Bindable_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = ProcessBindableSelected(frameNode, value);
    MenuItemModelStatic::SetSelected(frameNode, convValue);
}
void SetSelectIconImpl(Ark_NativePointer node,
                       const Opt_Union_Boolean_ResourceStr_SymbolGlyphModifier* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto iconOpt = Converter::OptConvertPtr<SelectIconType>(value);
    if (iconOpt.has_value()) {
        // Implement Reset value
        if (auto iconPtr = std::get_if<bool>(&(*iconOpt)); iconPtr) {
            MenuItemModelStatic::SetSelectIcon(frameNode, *iconPtr);
        }
        if (auto iconStrPtr = std::get_if<std::optional<std::string>>(&(*iconOpt)); iconStrPtr) {
            MenuItemModelStatic::SetSelectIcon(frameNode, true);
            MenuItemModelStatic::SetSelectIconSrc(frameNode, *iconStrPtr);
        }
        if (auto iconSymbolPtr = std::get_if<std::optional<SymbolGlyphModifierPeer *>>(&(*iconOpt));
            (iconSymbolPtr && (*iconSymbolPtr) && (*(*iconSymbolPtr)))) {
            MenuItemModelStatic::SetSelectIcon(frameNode, true);
            MenuItemModelStatic::SetSelectIconSymbol(frameNode, (*(*iconSymbolPtr))->symbolApply);
            PeerUtils::DestroyPeer(*(*iconSymbolPtr));
        }
    }
}
void SetOnChangeImpl(Ark_NativePointer node,
                     const Opt_synthetic_Callback_Boolean_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // Implement Reset value
        return;
    }
    auto onChange = [arkCallback = CallbackHelper(*optValue)](const bool param) {
        arkCallback.Invoke(Converter::ArkValue<Ark_Boolean>(param));
    };
    MenuItemModelStatic::SetOnChange(frameNode, onChange);
}
void SetContentFontImpl(Ark_NativePointer node,
                        const Opt_arkui_component_units_Font* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto fontOpt = Converter::OptConvertPtr<Font>(value);
    if (fontOpt.has_value()) {
        MenuItemModelStatic::SetFontSize(frameNode, fontOpt.value().fontSize);
        MenuItemModelStatic::SetFontWeight(frameNode, fontOpt.value().fontWeight);
        MenuItemModelStatic::SetFontStyle(frameNode, fontOpt.value().fontStyle);
        MenuItemModelStatic::SetFontFamily(frameNode, fontOpt.value().fontFamilies);
    } else {
        MenuItemModelStatic::SetFontSize(frameNode, std::nullopt);
        MenuItemModelStatic::SetFontWeight(frameNode, std::nullopt);
        MenuItemModelStatic::SetFontStyle(frameNode, std::nullopt);
        MenuItemModelStatic::SetFontFamily(frameNode, std::nullopt);
    }
}
void SetContentFontColorImpl(Ark_NativePointer node,
                             const Opt_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    MenuItemModelStatic::SetFontColor(frameNode, Converter::OptConvertPtr<Color>(value));
}
void SetLabelFontImpl(Ark_NativePointer node,
                      const Opt_arkui_component_units_Font* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto fontOpt = Converter::OptConvertPtr<Font>(value);
    if (fontOpt.has_value()) {
        MenuItemModelStatic::SetLabelFontSize(frameNode, fontOpt.value().fontSize);
        MenuItemModelStatic::SetLabelFontWeight(frameNode, fontOpt.value().fontWeight);
        MenuItemModelStatic::SetLabelFontStyle(frameNode, fontOpt.value().fontStyle);
        MenuItemModelStatic::SetLabelFontFamily(frameNode, fontOpt.value().fontFamilies);
    } else {
        MenuItemModelStatic::SetLabelFontSize(frameNode, std::nullopt);
        MenuItemModelStatic::SetLabelFontWeight(frameNode, std::nullopt);
        MenuItemModelStatic::SetLabelFontStyle(frameNode, std::nullopt);
        MenuItemModelStatic::SetLabelFontFamily(frameNode, std::nullopt);
    }
}
void SetLabelFontColorImpl(Ark_NativePointer node,
                           const Opt_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    MenuItemModelStatic::SetLabelFontColor(frameNode, Converter::OptConvertPtr<Color>(value));
}
} // MenuItemAttributeModifier
const GENERATED_ArkUIMenuItemModifier* GetMenuItemModifier()
{
    static const GENERATED_ArkUIMenuItemModifier ArkUIMenuItemModifierImpl {
        MenuItemModifier::ConstructImpl,
        MenuItemInterfaceModifier::SetMenuItemOptionsImpl,
        MenuItemAttributeModifier::SetSelectedImpl,
        MenuItemAttributeModifier::SetSelectIconImpl,
        MenuItemAttributeModifier::SetOnChangeImpl,
        MenuItemAttributeModifier::SetContentFontImpl,
        MenuItemAttributeModifier::SetContentFontColorImpl,
        MenuItemAttributeModifier::SetLabelFontImpl,
        MenuItemAttributeModifier::SetLabelFontColorImpl,
    };
    return &ArkUIMenuItemModifierImpl;
}

}
