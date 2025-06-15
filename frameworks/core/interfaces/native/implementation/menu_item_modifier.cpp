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
#include "core/components_ng/pattern/menu/menu_item/menu_item_model_ng.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/interfaces/native/generated/interface/node_api.h"

namespace OHOS::Ace::NG {
using SelectIconType = std::variant<bool, std::optional<std::string>, Ark_SymbolGlyphModifier>;
}

namespace OHOS::Ace::NG::Converter {
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
    return nullptr;
}

template<>
void AssignCast(std::optional<std::function<void(WeakPtr<NG::FrameNode>)>>& dst, const Ark_SymbolGlyphModifier& src)
{
    LOGE("MenuItemModifier::SetMenuItemOptionsImpl symbolStart and symbolEnd attributes are stubs.");
    dst = std::nullopt;
}
}

namespace OHOS::Ace::NG::GeneratedModifier {
namespace MenuItemModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                Ark_Int32 flags)
{
    return nullptr;
}
} // MenuItemModifier
namespace MenuItemInterfaceModifier {
void SetMenuItemOptionsImpl(Ark_NativePointer node,
                            const Opt_Union_MenuItemOptions_CustomBuilder* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    Converter::VisitUnion(value->value,
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
                    return callback.BuildSync(node);
                };
                menuItemProps.buildFunc = builder;
            }
            menuItemProps.startApply = nullptr;
            auto symbolStart = Converter::OptConvert<Ark_SymbolGlyphModifier>(value0.symbolStartIcon);
            if (symbolStart.has_value()) {
                auto startApply =
                    Converter::OptConvert<std::function<void(WeakPtr<NG::FrameNode>)>>(symbolStart.value());
                menuItemProps.startApply = startApply ? startApply.value() : nullptr;
            }
            menuItemProps.endApply = nullptr;
            auto symbolEnd = Converter::OptConvert<Ark_SymbolGlyphModifier>(value0.symbolEndIcon);
            if (symbolEnd.has_value()) {
                auto endApply = Converter::OptConvert<std::function<void(WeakPtr<NG::FrameNode>)>>(symbolEnd.value());
                menuItemProps.endApply = endApply ? endApply.value() : nullptr;
            }
            LOGE("MenuItemModifier::SetMenuItemOptionsImpl symbolStart and symbolEnd attributes are stubs.");
        },
        [frameNode, node](const CustomNodeBuilder& value1) {
            RefPtr<UINode> customNode;
            customNode = CallbackHelper(value1).BuildSync(node);
            if (customNode) {
            }
        },
        []() {}
    );
}
} // MenuItemInterfaceModifier
namespace MenuItemAttributeModifier {
void SelectedImpl(Ark_NativePointer node,
                  Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    MenuItemModelNG::SetSelected(frameNode, Converter::Convert<bool>(value));
}
void SelectIconImpl(Ark_NativePointer node,
                    const Ark_Union_Boolean_ResourceStr_SymbolGlyphModifier* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto iconOpt = Converter::OptConvert<SelectIconType>(*value);
    if (iconOpt.has_value()) {
        if (auto iconPtr = std::get_if<bool>(&(*iconOpt)); iconPtr) {
            MenuItemModelNG::SetSelectIcon(frameNode, *iconPtr);
        }
        if (auto iconStrPtr = std::get_if<std::optional<std::string>>(&(*iconOpt)); iconStrPtr) {
            MenuItemModelNG::SetSelectIcon(frameNode, true);
        }
        LOGE("MenuItemModifier::SelectIconImpl is not implemented, Ark_CustomObject is not supported!");
    }
}
void OnChangeImpl(Ark_NativePointer node,
                  const Callback_Boolean_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto onChange = [arkCallback = CallbackHelper(*value)](const bool param) {
        arkCallback.Invoke(Converter::ArkValue<Ark_Boolean>(param));
    };
    MenuItemModelNG::SetOnChange(frameNode, onChange);
}
void ContentFontImpl(Ark_NativePointer node,
                     const Ark_Font* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto fontOpt = Converter::OptConvert<Font>(*value);
    if (fontOpt.has_value()) {
        MenuItemModelNG::SetFontFamily(frameNode, fontOpt.value().fontFamilies);
    } else {
    }
}
void ContentFontColorImpl(Ark_NativePointer node,
                          const Ark_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    MenuItemModelNG::SetFontColor(frameNode, Converter::OptConvert<Color>(*value));
}
void LabelFontImpl(Ark_NativePointer node,
                   const Ark_Font* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto fontOpt = Converter::OptConvert<Font>(*value);
    if (fontOpt.has_value()) {
        MenuItemModelNG::SetLabelFontFamily(frameNode, fontOpt.value().fontFamilies);
    } else {
    }
}
void LabelFontColorImpl(Ark_NativePointer node,
                        const Ark_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    MenuItemModelNG::SetLabelFontColor(frameNode, Converter::OptConvert<Color>(*value));
}
void _onChangeEvent_selectedImpl(Ark_NativePointer node,
                                 const Callback_Boolean_Void* callback)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(callback);
    WeakPtr<FrameNode> weakNode = AceType::WeakClaim(frameNode);
    auto onEvent = [arkCallback = CallbackHelper(*callback), weakNode](bool selected) {
        PipelineContext::SetCallBackNode(weakNode);
        arkCallback.Invoke(Converter::ArkValue<Ark_Boolean>(selected));
    };
}
} // MenuItemAttributeModifier
const GENERATED_ArkUIMenuItemModifier* GetMenuItemModifier()
{
    static const GENERATED_ArkUIMenuItemModifier ArkUIMenuItemModifierImpl {
        MenuItemModifier::ConstructImpl,
        MenuItemInterfaceModifier::SetMenuItemOptionsImpl,
        MenuItemAttributeModifier::SelectedImpl,
        MenuItemAttributeModifier::SelectIconImpl,
        MenuItemAttributeModifier::OnChangeImpl,
        MenuItemAttributeModifier::ContentFontImpl,
        MenuItemAttributeModifier::ContentFontColorImpl,
        MenuItemAttributeModifier::LabelFontImpl,
        MenuItemAttributeModifier::LabelFontColorImpl,
        MenuItemAttributeModifier::_onChangeEvent_selectedImpl,
    };
    return &ArkUIMenuItemModifierImpl;
}

}
