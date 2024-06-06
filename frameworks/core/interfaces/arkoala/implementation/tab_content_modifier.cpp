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
    namespace TabContentInterfaceModifier {
        void _setTabContentOptionsImpl(Ark_NativePointer node) {
        }
    } // TabContentInterfaceModifier
    namespace TabContentAttributeModifier {
        void TabBar_stringResourceCustomBuildericonstringResourcetextstringResourceImpl(Ark_NativePointer node, const Type_TabContentAttribute_tabBar_Arg0* value) {
        }
        void TabBar_SubTabBarStyleBottomTabBarStyleImpl(Ark_NativePointer node, const Type_TabContentAttribute_tabBar1_Arg0* value) {
        }
        void OnWillShowImpl(Ark_NativePointer node, Ark_Function event) {
        }
        void OnWillHideImpl(Ark_NativePointer node, Ark_Function event) {
        }
    } // TabContentAttributeModifier
    const GENERATED_ArkUITabContentModifier* GetTabContentModifier() {
        static const GENERATED_ArkUITabContentModifier ArkUITabContentModifierImpl {
            TabContentInterfaceModifier::_setTabContentOptionsImpl,
            TabContentAttributeModifier::TabBar_stringResourceCustomBuildericonstringResourcetextstringResourceImpl,
            TabContentAttributeModifier::TabBar_SubTabBarStyleBottomTabBarStyleImpl,
            TabContentAttributeModifier::OnWillShowImpl,
            TabContentAttributeModifier::OnWillHideImpl,
        };
        return &ArkUITabContentModifierImpl;
    }

}
