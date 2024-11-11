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
#include "core/interfaces/arkoala/utility/converter.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace MenuItemInterfaceModifier {
void SetMenuItemOptionsImpl(Ark_NativePointer node,
                            const Opt_Union_MenuItemOptions_CustomBuilder* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //MenuItemModelNG::SetSetMenuItemOptions(frameNode, convValue);
}
} // MenuItemInterfaceModifier
namespace MenuItemAttributeModifier {
void SelectedImpl(Ark_NativePointer node,
                  Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::Convert<bool>(value);
    //MenuItemModelNG::SetSelected(frameNode, convValue);
}
void SelectIconImpl(Ark_NativePointer node,
                    const Ark_Union_Boolean_ResourceStr_SymbolGlyphModifier* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //MenuItemModelNG::SetSelectIcon(frameNode, convValue);
}
void OnChangeImpl(Ark_NativePointer node,
                  const Callback_Boolean_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //MenuItemModelNG::SetOnChange(frameNode, convValue);
}
void ContentFontImpl(Ark_NativePointer node,
                     const Ark_Font* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //MenuItemModelNG::SetContentFont(frameNode, convValue);
}
void ContentFontColorImpl(Ark_NativePointer node,
                          const Ark_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //MenuItemModelNG::SetContentFontColor(frameNode, convValue);
}
void LabelFontImpl(Ark_NativePointer node,
                   const Ark_Font* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //MenuItemModelNG::SetLabelFont(frameNode, convValue);
}
void LabelFontColorImpl(Ark_NativePointer node,
                        const Ark_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //MenuItemModelNG::SetLabelFontColor(frameNode, convValue);
}
} // MenuItemAttributeModifier
const GENERATED_ArkUIMenuItemModifier* GetMenuItemModifier()
{
    static const GENERATED_ArkUIMenuItemModifier ArkUIMenuItemModifierImpl {
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
