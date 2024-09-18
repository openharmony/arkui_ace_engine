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
namespace NavDestinationInterfaceModifier {
void SetNavDestinationOptionsImpl(Ark_NativePointer node)
{
}
} // NavDestinationInterfaceModifier
namespace NavDestinationAttributeModifier {
void TitleImpl(Ark_NativePointer node,
               const Type_NavDestinationAttribute_title_Arg0* value,
               const Opt_NavigationTitleOptions* options)
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
void OnShownImpl(Ark_NativePointer node,
                 Ark_Function callback)
{
}
void OnHiddenImpl(Ark_NativePointer node,
                  Ark_Function callback)
{
}
void OnBackPressedImpl(Ark_NativePointer node,
                       Ark_Function callback)
{
}
void ModeImpl(Ark_NativePointer node,
              enum Ark_NavDestinationMode value)
{
}
void BackButtonIconImpl(Ark_NativePointer node,
                        const Type_NavDestinationAttribute_backButtonIcon_Arg0* value)
{
}
void MenusImpl(Ark_NativePointer node,
               const Type_NavDestinationAttribute_menus_Arg0* value)
{
}
void OnReadyImpl(Ark_NativePointer node,
                 Ark_Function callback)
{
}
void OnWillAppearImpl(Ark_NativePointer node,
                      Ark_Function callback)
{
}
void OnWillDisappearImpl(Ark_NativePointer node,
                         Ark_Function callback)
{
}
void OnWillShowImpl(Ark_NativePointer node,
                    Ark_Function callback)
{
}
void OnWillHideImpl(Ark_NativePointer node,
                    Ark_Function callback)
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
void SystemTransitionImpl(Ark_NativePointer node,
                          enum Ark_NavigationSystemTransitionType type)
{
}
} // NavDestinationAttributeModifier
const GENERATED_ArkUINavDestinationModifier* GetNavDestinationModifier()
{
    static const GENERATED_ArkUINavDestinationModifier ArkUINavDestinationModifierImpl {
        NavDestinationInterfaceModifier::SetNavDestinationOptionsImpl,
        NavDestinationAttributeModifier::TitleImpl,
        NavDestinationAttributeModifier::HideTitleBar0Impl,
        NavDestinationAttributeModifier::HideTitleBar1Impl,
        NavDestinationAttributeModifier::OnShownImpl,
        NavDestinationAttributeModifier::OnHiddenImpl,
        NavDestinationAttributeModifier::OnBackPressedImpl,
        NavDestinationAttributeModifier::ModeImpl,
        NavDestinationAttributeModifier::BackButtonIconImpl,
        NavDestinationAttributeModifier::MenusImpl,
        NavDestinationAttributeModifier::OnReadyImpl,
        NavDestinationAttributeModifier::OnWillAppearImpl,
        NavDestinationAttributeModifier::OnWillDisappearImpl,
        NavDestinationAttributeModifier::OnWillShowImpl,
        NavDestinationAttributeModifier::OnWillHideImpl,
        NavDestinationAttributeModifier::IgnoreLayoutSafeAreaImpl,
        NavDestinationAttributeModifier::SystemBarStyleImpl,
        NavDestinationAttributeModifier::RecoverableImpl,
        NavDestinationAttributeModifier::SystemTransitionImpl,
    };
    return &ArkUINavDestinationModifierImpl;
}

}
