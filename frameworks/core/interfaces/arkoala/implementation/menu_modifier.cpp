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

#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace MenuInterfaceModifier {
void SetMenuOptionsImpl(Ark_NativePointer node)
{
}
} // MenuInterfaceModifier
namespace MenuAttributeModifier {
void FontSizeImpl(Ark_NativePointer node,
                  const Ark_Length* value)
{
}
void FontImpl(Ark_NativePointer node,
              const Ark_Font* value)
{
}
void FontColorImpl(Ark_NativePointer node,
                   const ResourceColor* value)
{
}
void RadiusImpl(Ark_NativePointer node,
                const Type_MenuAttribute_radius_Arg0* value)
{
}
void MenuItemDividerImpl(Ark_NativePointer node,
                         const Type_MenuAttribute_menuItemDivider_Arg0* options)
{
}
void MenuItemGroupDividerImpl(Ark_NativePointer node,
                              const Type_MenuAttribute_menuItemGroupDivider_Arg0* options)
{
}
void SubMenuExpandingModeImpl(Ark_NativePointer node,
                              enum Ark_SubMenuExpandingMode mode)
{
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
