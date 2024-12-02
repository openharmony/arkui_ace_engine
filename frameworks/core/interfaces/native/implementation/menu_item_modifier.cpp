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
#include "core/components_ng/pattern/menu/menu_item/menu_item_model_ng.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/generated/interface/node_api.h"

namespace OHOS::Ace::NG {
using SelectIconType = std::variant<bool, std::optional<std::string>, void*>;
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
SelectIconType Convert(const Ark_CustomObject& src)
{
    return nullptr;
}
}

namespace OHOS::Ace::NG::GeneratedModifier {
namespace MenuItemModifier {
Ark_NativePointer ConstructImpl()
{
    return 0;
}
} // MenuItemModifier
namespace MenuItemInterfaceModifier {
void SetMenuItemOptionsImpl(Ark_NativePointer node,
                            const Opt_Union_MenuItemOptions_CustomBuilder* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //MenuItemModelNG::SetSetMenuItemOptions(frameNode, convValue);
    LOGE("MenuItemModifier::SetMenuItemOptionsImpl is not implemented, Ark_CustomObject is not supported!");
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
            MenuItemModelNG::SetSelectIconSrc(frameNode, *iconStrPtr);
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
    auto onChange = [frameNode](bool selected) {
        GetFullAPI()->getEventsAPI()->getMenuItemEventsReceiver()->onChange(frameNode->GetId(), selected);
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
        MenuItemModelNG::SetFontSize(frameNode, fontOpt.value().fontSize);
        MenuItemModelNG::SetFontWeight(frameNode, fontOpt.value().fontWeight);
        MenuItemModelNG::SetFontStyle(frameNode, fontOpt.value().fontStyle);
        MenuItemModelNG::SetFontFamily(frameNode, fontOpt.value().fontFamilies);
    } else {
        MenuItemModelNG::SetFontSize(frameNode, std::nullopt);
        MenuItemModelNG::SetFontWeight(frameNode, std::nullopt);
        MenuItemModelNG::SetFontStyle(frameNode, std::nullopt);
        MenuItemModelNG::SetFontFamily(frameNode, std::nullopt);
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
        MenuItemModelNG::SetLabelFontSize(frameNode, fontOpt.value().fontSize);
        MenuItemModelNG::SetLabelFontWeight(frameNode, fontOpt.value().fontWeight);
        MenuItemModelNG::SetLabelFontStyle(frameNode, fontOpt.value().fontStyle);
        MenuItemModelNG::SetLabelFontFamily(frameNode, fontOpt.value().fontFamilies);
    } else {
        MenuItemModelNG::SetLabelFontSize(frameNode, std::nullopt);
        MenuItemModelNG::SetLabelFontWeight(frameNode, std::nullopt);
        MenuItemModelNG::SetLabelFontStyle(frameNode, std::nullopt);
        MenuItemModelNG::SetLabelFontFamily(frameNode, std::nullopt);
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
    };
    return &ArkUIMenuItemModifierImpl;
}

}
