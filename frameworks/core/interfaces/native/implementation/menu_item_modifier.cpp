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
#include "core/interfaces/native/utility/converter.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace MenuItemModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                Ark_Int32 flags)
{
    return {};
}
} // MenuItemModifier
namespace MenuItemInterfaceModifier {
void SetMenuItemOptionsImpl(Ark_NativePointer node,
                            const Opt_Union_MenuItemOptions_CustomBuilder* value)
{
}
} // MenuItemInterfaceModifier
namespace MenuItemAttributeModifier {
void SelectedImpl(Ark_NativePointer node,
                  const Opt_Boolean* value)
{
}
void SelectIconImpl(Ark_NativePointer node,
                    const Opt_Union_Boolean_ResourceStr_SymbolGlyphModifier* value)
{
}
void OnChangeImpl(Ark_NativePointer node,
                  const Opt_Callback_Boolean_Void* value)
{
}
void ContentFontImpl(Ark_NativePointer node,
                     const Opt_Font* value)
{
}
void ContentFontColorImpl(Ark_NativePointer node,
                          const Opt_ResourceColor* value)
{
}
void LabelFontImpl(Ark_NativePointer node,
                   const Opt_Font* value)
{
}
void LabelFontColorImpl(Ark_NativePointer node,
                        const Opt_ResourceColor* value)
{
}
void _onChangeEvent_selectedImpl(Ark_NativePointer node,
                                 const Callback_Opt_Boolean_Void* callback)
{
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
