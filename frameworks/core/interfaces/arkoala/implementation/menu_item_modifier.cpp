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
    namespace MenuItemInterfaceModifier {
        void _setMenuItemOptionsImpl(Ark_NativePointer node, const Opt_Type_MenuItemInterface__setMenuItemOptions_Arg0* value) {
        }
    } // MenuItemInterfaceModifier
    namespace MenuItemAttributeModifier {
        void SelectedImpl(Ark_NativePointer node, Ark_Boolean value) {
        }
        void SelectIconImpl(Ark_NativePointer node, const Type_MenuItemAttribute_selectIcon_Arg0* value) {
        }
        void OnChangeImpl(Ark_NativePointer node, Ark_Function callback) {
        }
        void ContentFontImpl(Ark_NativePointer node, const Font* value) {
        }
        void ContentFontColorImpl(Ark_NativePointer node, const ResourceColor* value) {
        }
        void LabelFontImpl(Ark_NativePointer node, const Font* value) {
        }
        void LabelFontColorImpl(Ark_NativePointer node, const ResourceColor* value) {
        }
    } // MenuItemAttributeModifier
    const GENERATED_ArkUIMenuItemModifier* GetMenuItemModifier() {
        static const GENERATED_ArkUIMenuItemModifier ArkUIMenuItemModifierImpl {
            MenuItemInterfaceModifier::_setMenuItemOptionsImpl,
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
