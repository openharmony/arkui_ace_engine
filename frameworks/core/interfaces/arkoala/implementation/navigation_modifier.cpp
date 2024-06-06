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
    namespace NavigationInterfaceModifier {
        void _setNavigationOptions_Impl(Ark_NativePointer node) {
        }
        void _setNavigationOptions_NavPathStackImpl(Ark_NativePointer node, const Ark_Materialized* pathInfos) {
        }
    } // NavigationInterfaceModifier
    namespace NavigationAttributeModifier {
        void NavBarWidthImpl(Ark_NativePointer node, const Ark_Length* value) {
        }
        void NavBarPositionImpl(Ark_NativePointer node, Ark_Int32 value) {
        }
        void NavBarWidthRangeImpl(Ark_NativePointer node, const Type_NavigationAttribute_navBarWidthRange_Arg0* value) {
        }
        void MinContentWidthImpl(Ark_NativePointer node, const Ark_Length* value) {
        }
        void ModeImpl(Ark_NativePointer node, Ark_Int32 value) {
        }
        void BackButtonIconImpl(Ark_NativePointer node, const Type_NavigationAttribute_backButtonIcon_Arg0* value) {
        }
        void HideNavBarImpl(Ark_NativePointer node, Ark_Boolean value) {
        }
        void TitleImpl(Ark_NativePointer node, const Type_NavigationAttribute_title_Arg0* value, const Opt_NavigationTitleOptions* options) {
        }
        void SubTitleImpl(Ark_NativePointer node, const Ark_String* value) {
        }
        void HideTitleBarImpl(Ark_NativePointer node, Ark_Boolean value) {
        }
        void HideBackButtonImpl(Ark_NativePointer node, Ark_Boolean value) {
        }
        void TitleModeImpl(Ark_NativePointer node, Ark_Int32 value) {
        }
        void MenusImpl(Ark_NativePointer node, const Type_NavigationAttribute_menus_Arg0* value) {
        }
        void ToolBarImpl(Ark_NativePointer node, const Type_NavigationAttribute_toolBar_Arg0* value) {
        }
        void ToolbarConfigurationImpl(Ark_NativePointer node, const Type_NavigationAttribute_toolbarConfiguration_Arg0* value, const Opt_NavigationToolbarOptions* options) {
        }
        void HideToolBarImpl(Ark_NativePointer node, Ark_Boolean value) {
        }
        void OnTitleModeChangeImpl(Ark_NativePointer node, Ark_Function callback) {
        }
        void OnNavBarStateChangeImpl(Ark_NativePointer node, Ark_Function callback) {
        }
        void OnNavigationModeChangeImpl(Ark_NativePointer node, Ark_Function callback) {
        }
        void NavDestinationImpl(Ark_NativePointer node, Ark_Function builder) {
        }
        void CustomNavContentTransitionImpl(Ark_NativePointer node, Ark_Function delegate) {
        }
        void IgnoreLayoutSafeAreaImpl(Ark_NativePointer node, const Opt_Array_Ark_LayoutSafeAreaType* types, const Opt_Array_Ark_LayoutSafeAreaEdge* edges) {
        }
        void SystemBarStyleImpl(Ark_NativePointer node, const Opt_Ark_CustomObject* style) {
        }
    } // NavigationAttributeModifier
    const GENERATED_ArkUINavigationModifier* GetNavigationModifier() {
        static const GENERATED_ArkUINavigationModifier ArkUINavigationModifierImpl {
            NavigationInterfaceModifier::_setNavigationOptions_Impl,
            NavigationInterfaceModifier::_setNavigationOptions_NavPathStackImpl,
            NavigationAttributeModifier::NavBarWidthImpl,
            NavigationAttributeModifier::NavBarPositionImpl,
            NavigationAttributeModifier::NavBarWidthRangeImpl,
            NavigationAttributeModifier::MinContentWidthImpl,
            NavigationAttributeModifier::ModeImpl,
            NavigationAttributeModifier::BackButtonIconImpl,
            NavigationAttributeModifier::HideNavBarImpl,
            NavigationAttributeModifier::TitleImpl,
            NavigationAttributeModifier::SubTitleImpl,
            NavigationAttributeModifier::HideTitleBarImpl,
            NavigationAttributeModifier::HideBackButtonImpl,
            NavigationAttributeModifier::TitleModeImpl,
            NavigationAttributeModifier::MenusImpl,
            NavigationAttributeModifier::ToolBarImpl,
            NavigationAttributeModifier::ToolbarConfigurationImpl,
            NavigationAttributeModifier::HideToolBarImpl,
            NavigationAttributeModifier::OnTitleModeChangeImpl,
            NavigationAttributeModifier::OnNavBarStateChangeImpl,
            NavigationAttributeModifier::OnNavigationModeChangeImpl,
            NavigationAttributeModifier::NavDestinationImpl,
            NavigationAttributeModifier::CustomNavContentTransitionImpl,
            NavigationAttributeModifier::IgnoreLayoutSafeAreaImpl,
            NavigationAttributeModifier::SystemBarStyleImpl,
        };
        return &ArkUINavigationModifierImpl;
    }

}
