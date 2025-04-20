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
namespace NavigationModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                Ark_Int32 flags)
{
    return {};
}
} // NavigationModifier
namespace NavigationInterfaceModifier {
void SetNavigationOptions0Impl(Ark_NativePointer node)
{
}
void SetNavigationOptions1Impl(Ark_NativePointer node,
                               Ark_NavPathStack pathInfos)
{
}
} // NavigationInterfaceModifier
namespace NavigationAttributeModifier {
void NavBarWidthImpl(Ark_NativePointer node,
                     const Opt_Length* value)
{
}
void NavBarPositionImpl(Ark_NativePointer node,
                        const Opt_NavBarPosition* value)
{
}
void NavBarWidthRangeImpl(Ark_NativePointer node,
                          const Opt_Tuple_Dimension_Dimension* value)
{
}
void MinContentWidthImpl(Ark_NativePointer node,
                         const Opt_Length* value)
{
}
void ModeImpl(Ark_NativePointer node,
              const Opt_NavigationMode* value)
{
}
void BackButtonIcon0Impl(Ark_NativePointer node,
                         const Opt_Union_String_PixelMap_Resource_SymbolGlyphModifier* value)
{
}
void BackButtonIcon1Impl(Ark_NativePointer node,
                         const Opt_Union_String_PixelMap_Resource_SymbolGlyphModifier* icon,
                         const Opt_ResourceStr* accessibilityText)
{
}
void HideNavBarImpl(Ark_NativePointer node,
                    const Opt_Boolean* value)
{
}
void SubTitleImpl(Ark_NativePointer node,
                  const Opt_String* value)
{
}
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
void TitleModeImpl(Ark_NativePointer node,
                   const Opt_NavigationTitleMode* value)
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
void ToolBarImpl(Ark_NativePointer node,
                 const Opt_CustomNodeBuilder* value)
{
}
void HideToolBar0Impl(Ark_NativePointer node,
                      const Opt_Boolean* value)
{
}
void HideToolBar1Impl(Ark_NativePointer node,
                      const Opt_Boolean* hide,
                      const Opt_Boolean* animated)
{
}
void EnableToolBarAdaptationImpl(Ark_NativePointer node,
                                 const Opt_Boolean* value)
{
}
void OnTitleModeChangeImpl(Ark_NativePointer node,
                           const Opt_Callback_NavigationTitleMode_Void* value)
{
}
void OnNavBarStateChangeImpl(Ark_NativePointer node,
                             const Opt_Callback_Boolean_Void* value)
{
}
void OnNavigationModeChangeImpl(Ark_NativePointer node,
                                const Opt_Callback_NavigationMode_Void* value)
{
}
void NavDestinationImpl(Ark_NativePointer node,
                        const Opt_Callback_String_Opt_Object_Void* value)
{
}
void CustomNavContentTransitionImpl(Ark_NativePointer node,
                                    const Opt_Type_NavigationAttribute_customNavContentTransition_delegate* value)
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
void EnableDragBarImpl(Ark_NativePointer node,
                       const Opt_Boolean* value)
{
}
void EnableModeChangeAnimationImpl(Ark_NativePointer node,
                                   const Opt_Boolean* value)
{
}
void TitleImpl(Ark_NativePointer node,
               const Opt_Type_NavigationAttribute_title_value* value,
               const Opt_NavigationTitleOptions* options)
{
}
void ToolbarConfigurationImpl(Ark_NativePointer node,
                              const Opt_Union_Array_ToolbarItem_CustomBuilder* value,
                              const Opt_NavigationToolbarOptions* options)
{
}
void IgnoreLayoutSafeAreaImpl(Ark_NativePointer node,
                              const Opt_Array_LayoutSafeAreaType* types,
                              const Opt_Array_LayoutSafeAreaEdge* edges)
{
}
} // NavigationAttributeModifier
const GENERATED_ArkUINavigationModifier* GetNavigationModifier()
{
    static const GENERATED_ArkUINavigationModifier ArkUINavigationModifierImpl {
        NavigationModifier::ConstructImpl,
        NavigationInterfaceModifier::SetNavigationOptions0Impl,
        NavigationInterfaceModifier::SetNavigationOptions1Impl,
        NavigationAttributeModifier::NavBarWidthImpl,
        NavigationAttributeModifier::NavBarPositionImpl,
        NavigationAttributeModifier::NavBarWidthRangeImpl,
        NavigationAttributeModifier::MinContentWidthImpl,
        NavigationAttributeModifier::ModeImpl,
        NavigationAttributeModifier::BackButtonIcon0Impl,
        NavigationAttributeModifier::BackButtonIcon1Impl,
        NavigationAttributeModifier::HideNavBarImpl,
        NavigationAttributeModifier::SubTitleImpl,
        NavigationAttributeModifier::HideTitleBar0Impl,
        NavigationAttributeModifier::HideTitleBar1Impl,
        NavigationAttributeModifier::HideBackButtonImpl,
        NavigationAttributeModifier::TitleModeImpl,
        NavigationAttributeModifier::Menus0Impl,
        NavigationAttributeModifier::Menus1Impl,
        NavigationAttributeModifier::ToolBarImpl,
        NavigationAttributeModifier::HideToolBar0Impl,
        NavigationAttributeModifier::HideToolBar1Impl,
        NavigationAttributeModifier::EnableToolBarAdaptationImpl,
        NavigationAttributeModifier::OnTitleModeChangeImpl,
        NavigationAttributeModifier::OnNavBarStateChangeImpl,
        NavigationAttributeModifier::OnNavigationModeChangeImpl,
        NavigationAttributeModifier::NavDestinationImpl,
        NavigationAttributeModifier::CustomNavContentTransitionImpl,
        NavigationAttributeModifier::SystemBarStyleImpl,
        NavigationAttributeModifier::RecoverableImpl,
        NavigationAttributeModifier::EnableDragBarImpl,
        NavigationAttributeModifier::EnableModeChangeAnimationImpl,
        NavigationAttributeModifier::TitleImpl,
        NavigationAttributeModifier::ToolbarConfigurationImpl,
        NavigationAttributeModifier::IgnoreLayoutSafeAreaImpl,
    };
    return &ArkUINavigationModifierImpl;
}

}
