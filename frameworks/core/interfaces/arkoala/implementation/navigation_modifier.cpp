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
void SetNavigationOptions0Impl(Ark_NativePointer node)
{
}
void SetNavigationOptions1Impl(Ark_NativePointer node,
                               const Ark_Materialized* pathInfos)
{
}
} // NavigationInterfaceModifier
namespace NavigationAttributeModifier {
void NavBarWidthImpl(Ark_NativePointer node,
                     const Ark_Length* value)
{
}
void NavBarPositionImpl(Ark_NativePointer node,
                        enum Ark_NavBarPosition value)
{
}
void NavBarWidthRangeImpl(Ark_NativePointer node,
                          const Type_NavigationAttribute_navBarWidthRange_Arg0* value)
{
}
void MinContentWidthImpl(Ark_NativePointer node,
                         const Ark_Length* value)
{
}
void ModeImpl(Ark_NativePointer node,
              enum Ark_NavigationMode value)
{
}
void BackButtonIconImpl(Ark_NativePointer node,
                        const Type_NavigationAttribute_backButtonIcon_Arg0* value)
{
}
void HideNavBarImpl(Ark_NativePointer node,
                    Ark_Boolean value)
{
}
void TitleImpl(Ark_NativePointer node,
               const Type_NavigationAttribute_title_Arg0* value,
               const Opt_NavigationTitleOptions* options)
{
}
void SubTitleImpl(Ark_NativePointer node,
                  const Ark_String* value)
{
}
void HideTitleBar0Impl(Ark_NativePointer node,
                       Ark_Boolean value)
{
}
void HideTitleBar1Impl(Ark_NativePointer node,
                       Ark_Boolean hide,
                       Ark_Boolean animated)
{
}
void HideBackButtonImpl(Ark_NativePointer node,
                        Ark_Boolean value)
{
}
void TitleModeImpl(Ark_NativePointer node,
                   enum Ark_NavigationTitleMode value)
{
}
void MenusImpl(Ark_NativePointer node,
               const Type_NavigationAttribute_menus_Arg0* value)
{
}
void ToolBarImpl(Ark_NativePointer node,
                 const Type_NavigationAttribute_toolBar_Arg0* value)
{
}
void ToolbarConfigurationImpl(Ark_NativePointer node,
                              const Type_NavigationAttribute_toolbarConfiguration_Arg0* value,
                              const Opt_NavigationToolbarOptions* options)
{
}
void HideToolBar0Impl(Ark_NativePointer node,
                      Ark_Boolean value)
{
}
void HideToolBar1Impl(Ark_NativePointer node,
                      Ark_Boolean hide,
                      Ark_Boolean animated)
{
}
void OnTitleModeChangeImpl(Ark_NativePointer node,
                           Ark_Function callback)
{
}
void OnNavBarStateChangeImpl(Ark_NativePointer node,
                             Ark_Function callback)
{
}
void OnNavigationModeChangeImpl(Ark_NativePointer node,
                                Ark_Function callback)
{
}
void NavDestinationImpl(Ark_NativePointer node,
                        Ark_Function builder)
{
}
void CustomNavContentTransitionImpl(Ark_NativePointer node,
                                    Ark_Function delegate)
{
}
void IgnoreLayoutSafeAreaImpl(Ark_NativePointer node,
                              const Opt_Array_LayoutSafeAreaType* types,
                              const Opt_Array_LayoutSafeAreaEdge* edges)
{
}
void SystemBarStyleImpl(Ark_NativePointer node,
                        const Opt_CustomObject* style)
{
}
void RecoverableImpl(Ark_NativePointer node,
                     const Opt_Boolean* recoverable)
{
}
} // NavigationAttributeModifier
const GENERATED_ArkUINavigationModifier* GetNavigationModifier()
{
    static const GENERATED_ArkUINavigationModifier ArkUINavigationModifierImpl {
        NavigationInterfaceModifier::SetNavigationOptions0Impl,
        NavigationInterfaceModifier::SetNavigationOptions1Impl,
        NavigationAttributeModifier::NavBarWidthImpl,
        NavigationAttributeModifier::NavBarPositionImpl,
        NavigationAttributeModifier::NavBarWidthRangeImpl,
        NavigationAttributeModifier::MinContentWidthImpl,
        NavigationAttributeModifier::ModeImpl,
        NavigationAttributeModifier::BackButtonIconImpl,
        NavigationAttributeModifier::HideNavBarImpl,
        NavigationAttributeModifier::TitleImpl,
        NavigationAttributeModifier::SubTitleImpl,
        NavigationAttributeModifier::HideTitleBar0Impl,
        NavigationAttributeModifier::HideTitleBar1Impl,
        NavigationAttributeModifier::HideBackButtonImpl,
        NavigationAttributeModifier::TitleModeImpl,
        NavigationAttributeModifier::MenusImpl,
        NavigationAttributeModifier::ToolBarImpl,
        NavigationAttributeModifier::ToolbarConfigurationImpl,
        NavigationAttributeModifier::HideToolBar0Impl,
        NavigationAttributeModifier::HideToolBar1Impl,
        NavigationAttributeModifier::OnTitleModeChangeImpl,
        NavigationAttributeModifier::OnNavBarStateChangeImpl,
        NavigationAttributeModifier::OnNavigationModeChangeImpl,
        NavigationAttributeModifier::NavDestinationImpl,
        NavigationAttributeModifier::CustomNavContentTransitionImpl,
        NavigationAttributeModifier::IgnoreLayoutSafeAreaImpl,
        NavigationAttributeModifier::SystemBarStyleImpl,
        NavigationAttributeModifier::RecoverableImpl,
    };
    return &ArkUINavigationModifierImpl;
}

}
