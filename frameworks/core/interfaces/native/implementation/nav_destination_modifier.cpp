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
namespace NavDestinationModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                Ark_Int32 flags)
{
    return {};
}
} // NavDestinationModifier
namespace NavDestinationInterfaceModifier {
void SetNavDestinationOptionsImpl(Ark_NativePointer node)
{
}
} // NavDestinationInterfaceModifier
namespace NavDestinationAttributeModifier {
void HideTitleBar0Impl(Ark_NativePointer node,
                       const Opt_Boolean* value)
{
}
void HideTitleBar1Impl(Ark_NativePointer node,
                       const Opt_Boolean* hide,
                       const Opt_Boolean* animated)
{
}
void HideBackButtonImpl(Ark_NativePointer node,
                        const Opt_Boolean* value)
{
}
void OnShownImpl(Ark_NativePointer node,
                 const Opt_Callback_Void* value)
{
}
void OnHiddenImpl(Ark_NativePointer node,
                  const Opt_Callback_Void* value)
{
}
void OnBackPressedImpl(Ark_NativePointer node,
                       const Opt_Callback_Boolean* value)
{
}
void OnResultImpl(Ark_NativePointer node,
                  const Opt_Callback_Object_Void* value)
{
}
void ModeImpl(Ark_NativePointer node,
              const Opt_NavDestinationMode* value)
{
}
void BackButtonIcon0Impl(Ark_NativePointer node,
                         const Opt_Union_ResourceStr_PixelMap_SymbolGlyphModifier* value)
{
}
void BackButtonIcon1Impl(Ark_NativePointer node,
                         const Opt_Union_ResourceStr_PixelMap_SymbolGlyphModifier* icon,
                         const Opt_ResourceStr* accessibilityText)
{
}
void Menus0Impl(Ark_NativePointer node,
                const Opt_Union_Array_NavigationMenuItem_CustomBuilder* value)
{
}
void Menus1Impl(Ark_NativePointer node,
                const Opt_Union_Array_NavigationMenuItem_CustomBuilder* items,
                const Opt_NavigationMenuOptions* options)
{
}
void OnReadyImpl(Ark_NativePointer node,
                 const Opt_Callback_NavDestinationContext_Void* value)
{
}
void OnWillAppearImpl(Ark_NativePointer node,
                      const Opt_Callback_Void* value)
{
}
void OnWillDisappearImpl(Ark_NativePointer node,
                         const Opt_Callback_Void* value)
{
}
void OnWillShowImpl(Ark_NativePointer node,
                    const Opt_Callback_Void* value)
{
}
void OnWillHideImpl(Ark_NativePointer node,
                    const Opt_Callback_Void* value)
{
}
void SystemBarStyleImpl(Ark_NativePointer node,
                        const Opt_SystemBarStyle* value)
{
}
void RecoverableImpl(Ark_NativePointer node,
                     const Opt_Boolean* value)
{
}
void SystemTransitionImpl(Ark_NativePointer node,
                          const Opt_NavigationSystemTransitionType* value)
{
}
void BindToScrollableImpl(Ark_NativePointer node,
                          const Opt_Array_Scroller* value)
{
}
void BindToNestedScrollableImpl(Ark_NativePointer node,
                                const Opt_Array_NestedScrollInfo* value)
{
}
void OnActiveImpl(Ark_NativePointer node,
                  const Opt_Callback_NavDestinationActiveReason_Void* value)
{
}
void OnInactiveImpl(Ark_NativePointer node,
                    const Opt_Callback_NavDestinationActiveReason_Void* value)
{
}
void CustomTransitionImpl(Ark_NativePointer node,
                          const Opt_NavDestinationTransitionDelegate* value)
{
}
void OnNewParamImpl(Ark_NativePointer node,
                    const Opt_Callback_Object_Void* value)
{
}
void PreferredOrientationImpl(Ark_NativePointer node,
                              const Opt_Orientation* value)
{
}
void EnableNavigationIndicatorImpl(Ark_NativePointer node,
                                   const Opt_Boolean* value)
{
}
void TitleImpl(Ark_NativePointer node,
               const Opt_Type_NavDestinationAttribute_title_value* value,
               const Opt_NavigationTitleOptions* options)
{
}
void ToolbarConfigurationImpl(Ark_NativePointer node,
                              const Opt_Union_Array_ToolbarItem_CustomBuilder* toolbarParam,
                              const Opt_NavigationToolbarOptions* options)
{
}
void HideToolBarImpl(Ark_NativePointer node,
                     const Opt_Boolean* hide,
                     const Opt_Boolean* animated)
{
}
void IgnoreLayoutSafeAreaImpl(Ark_NativePointer node,
                              const Opt_Array_LayoutSafeAreaType* types,
                              const Opt_Array_LayoutSafeAreaEdge* edges)
{
}
void EnableStatusBarImpl(Ark_NativePointer node,
                         const Opt_Boolean* enabled,
                         const Opt_Boolean* animated)
{
}
} // NavDestinationAttributeModifier
const GENERATED_ArkUINavDestinationModifier* GetNavDestinationModifier()
{
    static const GENERATED_ArkUINavDestinationModifier ArkUINavDestinationModifierImpl {
        NavDestinationModifier::ConstructImpl,
        NavDestinationInterfaceModifier::SetNavDestinationOptionsImpl,
        NavDestinationAttributeModifier::HideTitleBar0Impl,
        NavDestinationAttributeModifier::HideTitleBar1Impl,
        NavDestinationAttributeModifier::HideBackButtonImpl,
        NavDestinationAttributeModifier::OnShownImpl,
        NavDestinationAttributeModifier::OnHiddenImpl,
        NavDestinationAttributeModifier::OnBackPressedImpl,
        NavDestinationAttributeModifier::OnResultImpl,
        NavDestinationAttributeModifier::ModeImpl,
        NavDestinationAttributeModifier::BackButtonIcon0Impl,
        NavDestinationAttributeModifier::BackButtonIcon1Impl,
        NavDestinationAttributeModifier::Menus0Impl,
        NavDestinationAttributeModifier::Menus1Impl,
        NavDestinationAttributeModifier::OnReadyImpl,
        NavDestinationAttributeModifier::OnWillAppearImpl,
        NavDestinationAttributeModifier::OnWillDisappearImpl,
        NavDestinationAttributeModifier::OnWillShowImpl,
        NavDestinationAttributeModifier::OnWillHideImpl,
        NavDestinationAttributeModifier::SystemBarStyleImpl,
        NavDestinationAttributeModifier::RecoverableImpl,
        NavDestinationAttributeModifier::SystemTransitionImpl,
        NavDestinationAttributeModifier::BindToScrollableImpl,
        NavDestinationAttributeModifier::BindToNestedScrollableImpl,
        NavDestinationAttributeModifier::OnActiveImpl,
        NavDestinationAttributeModifier::OnInactiveImpl,
        NavDestinationAttributeModifier::CustomTransitionImpl,
        NavDestinationAttributeModifier::OnNewParamImpl,
        NavDestinationAttributeModifier::PreferredOrientationImpl,
        NavDestinationAttributeModifier::EnableNavigationIndicatorImpl,
        NavDestinationAttributeModifier::TitleImpl,
        NavDestinationAttributeModifier::ToolbarConfigurationImpl,
        NavDestinationAttributeModifier::HideToolBarImpl,
        NavDestinationAttributeModifier::IgnoreLayoutSafeAreaImpl,
        NavDestinationAttributeModifier::EnableStatusBarImpl,
    };
    return &ArkUINavDestinationModifierImpl;
}

}
