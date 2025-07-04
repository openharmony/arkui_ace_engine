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
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(undefined);
    //auto convValue = Converter::OptConvert<type>(undefined); // for enums
    //NavDestinationModelNG::SetSetNavDestinationOptions(frameNode, convValue);
}
} // NavDestinationInterfaceModifier
namespace NavDestinationAttributeModifier {
void SetHideTitleBar0Impl(Ark_NativePointer node,
                          const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //NavDestinationModelNG::SetSetHideTitleBar0(frameNode, convValue);
}
void SetHideBackButtonImpl(Ark_NativePointer node,
                           const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //NavDestinationModelNG::SetSetHideBackButton(frameNode, convValue);
}
void SetOnShownImpl(Ark_NativePointer node,
                    const Opt_Callback_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //NavDestinationModelNG::SetSetOnShown(frameNode, convValue);
}
void SetOnHiddenImpl(Ark_NativePointer node,
                     const Opt_Callback_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //NavDestinationModelNG::SetSetOnHidden(frameNode, convValue);
}
void SetOnBackPressedImpl(Ark_NativePointer node,
                          const Opt_Callback_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //NavDestinationModelNG::SetSetOnBackPressed(frameNode, convValue);
}
void SetModeImpl(Ark_NativePointer node,
                 const Opt_NavDestinationMode* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //NavDestinationModelNG::SetSetMode(frameNode, convValue);
}
void SetBackButtonIcon0Impl(Ark_NativePointer node,
                            const Opt_Union_ResourceStr_PixelMap_SymbolGlyphModifier* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //NavDestinationModelNG::SetSetBackButtonIcon0(frameNode, convValue);
}
void SetMenus0Impl(Ark_NativePointer node,
                   const Opt_Union_Array_NavigationMenuItem_CustomBuilder* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //NavDestinationModelNG::SetSetMenus0(frameNode, convValue);
}
void SetOnReadyImpl(Ark_NativePointer node,
                    const Opt_Callback_NavDestinationContext_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //NavDestinationModelNG::SetSetOnReady(frameNode, convValue);
}
void SetOnWillAppearImpl(Ark_NativePointer node,
                         const Opt_Callback_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //NavDestinationModelNG::SetSetOnWillAppear(frameNode, convValue);
}
void SetOnWillDisappearImpl(Ark_NativePointer node,
                            const Opt_Callback_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //NavDestinationModelNG::SetSetOnWillDisappear(frameNode, convValue);
}
void SetOnWillShowImpl(Ark_NativePointer node,
                       const Opt_Callback_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //NavDestinationModelNG::SetSetOnWillShow(frameNode, convValue);
}
void SetOnWillHideImpl(Ark_NativePointer node,
                       const Opt_Callback_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //NavDestinationModelNG::SetSetOnWillHide(frameNode, convValue);
}
void SetSystemBarStyleImpl(Ark_NativePointer node,
                           const Opt_window_SystemBarStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //NavDestinationModelNG::SetSetSystemBarStyle(frameNode, convValue);
}
void SetRecoverableImpl(Ark_NativePointer node,
                        const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //NavDestinationModelNG::SetSetRecoverable(frameNode, convValue);
}
void SetSystemTransitionImpl(Ark_NativePointer node,
                             const Opt_NavigationSystemTransitionType* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //NavDestinationModelNG::SetSetSystemTransition(frameNode, convValue);
}
void SetBindToScrollableImpl(Ark_NativePointer node,
                             const Opt_Array_Scroller* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //NavDestinationModelNG::SetSetBindToScrollable(frameNode, convValue);
}
void SetBindToNestedScrollableImpl(Ark_NativePointer node,
                                   const Opt_Array_NestedScrollInfo* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //NavDestinationModelNG::SetSetBindToNestedScrollable(frameNode, convValue);
}
void SetOnActiveImpl(Ark_NativePointer node,
                     const Opt_Callback_NavDestinationActiveReason_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //NavDestinationModelNG::SetSetOnActive(frameNode, convValue);
}
void SetOnInactiveImpl(Ark_NativePointer node,
                       const Opt_Callback_NavDestinationActiveReason_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //NavDestinationModelNG::SetSetOnInactive(frameNode, convValue);
}
void SetCustomTransitionImpl(Ark_NativePointer node,
                             const Opt_NavDestinationTransitionDelegate* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //NavDestinationModelNG::SetSetCustomTransition(frameNode, convValue);
}
void SetOnNewParamImpl(Ark_NativePointer node,
                       const Opt_Callback_Union_Object_Undefined_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //NavDestinationModelNG::SetSetOnNewParam(frameNode, convValue);
}
void SetPreferredOrientationImpl(Ark_NativePointer node,
                                 const Opt_CustomObject* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //NavDestinationModelNG::SetSetPreferredOrientation(frameNode, convValue);
}
void SetEnableNavigationIndicatorImpl(Ark_NativePointer node,
                                      const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //NavDestinationModelNG::SetSetEnableNavigationIndicator(frameNode, convValue);
}
void SetTitleImpl(Ark_NativePointer node,
                  const Opt_Union_String_CustomBuilder_NavDestinationCommonTitle_NavDestinationCustomTitle_Resource* value,
                  const Opt_NavigationTitleOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(value);
    //auto convValue = Converter::OptConvert<type>(value); // for enums
    //NavDestinationModelNG::SetSetTitle(frameNode, convValue);
}
void SetHideTitleBar1Impl(Ark_NativePointer node,
                          const Opt_Boolean* hide,
                          const Opt_Boolean* animated)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(hide);
    //auto convValue = Converter::OptConvert<type>(hide); // for enums
    //NavDestinationModelNG::SetSetHideTitleBar1(frameNode, convValue);
}
void SetBackButtonIcon1Impl(Ark_NativePointer node,
                            const Opt_Union_ResourceStr_PixelMap_SymbolGlyphModifier* icon,
                            const Opt_ResourceStr* accessibilityText)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(icon);
    //auto convValue = Converter::OptConvert<type>(icon); // for enums
    //NavDestinationModelNG::SetSetBackButtonIcon1(frameNode, convValue);
}
void SetMenus1Impl(Ark_NativePointer node,
                   const Opt_Union_Array_NavigationMenuItem_CustomBuilder* items,
                   const Opt_NavigationMenuOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(items);
    //auto convValue = Converter::OptConvert<type>(items); // for enums
    //NavDestinationModelNG::SetSetMenus1(frameNode, convValue);
}
void SetToolbarConfigurationImpl(Ark_NativePointer node,
                                 const Opt_Union_Array_ToolbarItem_CustomBuilder* toolbarParam,
                                 const Opt_NavigationToolbarOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(toolbarParam);
    //auto convValue = Converter::OptConvert<type>(toolbarParam); // for enums
    //NavDestinationModelNG::SetSetToolbarConfiguration(frameNode, convValue);
}
void SetHideToolBarImpl(Ark_NativePointer node,
                        const Opt_Boolean* hide,
                        const Opt_Boolean* animated)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(hide);
    //auto convValue = Converter::OptConvert<type>(hide); // for enums
    //NavDestinationModelNG::SetSetHideToolBar(frameNode, convValue);
}
void SetIgnoreLayoutSafeAreaImpl(Ark_NativePointer node,
                                 const Opt_Array_LayoutSafeAreaType* types,
                                 const Opt_Array_LayoutSafeAreaEdge* edges)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(types);
    //auto convValue = Converter::OptConvert<type>(types); // for enums
    //NavDestinationModelNG::SetSetIgnoreLayoutSafeArea(frameNode, convValue);
}
void SetEnableStatusBarImpl(Ark_NativePointer node,
                            const Opt_Boolean* enabled,
                            const Opt_Boolean* animated)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(enabled);
    //auto convValue = Converter::OptConvert<type>(enabled); // for enums
    //NavDestinationModelNG::SetSetEnableStatusBar(frameNode, convValue);
}
} // NavDestinationAttributeModifier
const GENERATED_ArkUINavDestinationModifier* GetNavDestinationModifier()
{
    static const GENERATED_ArkUINavDestinationModifier ArkUINavDestinationModifierImpl {
        NavDestinationModifier::ConstructImpl,
        NavDestinationInterfaceModifier::SetNavDestinationOptionsImpl,
        NavDestinationAttributeModifier::SetHideTitleBar0Impl,
        NavDestinationAttributeModifier::SetHideBackButtonImpl,
        NavDestinationAttributeModifier::SetOnShownImpl,
        NavDestinationAttributeModifier::SetOnHiddenImpl,
        NavDestinationAttributeModifier::SetOnBackPressedImpl,
        NavDestinationAttributeModifier::SetModeImpl,
        NavDestinationAttributeModifier::SetBackButtonIcon0Impl,
        NavDestinationAttributeModifier::SetMenus0Impl,
        NavDestinationAttributeModifier::SetOnReadyImpl,
        NavDestinationAttributeModifier::SetOnWillAppearImpl,
        NavDestinationAttributeModifier::SetOnWillDisappearImpl,
        NavDestinationAttributeModifier::SetOnWillShowImpl,
        NavDestinationAttributeModifier::SetOnWillHideImpl,
        NavDestinationAttributeModifier::SetSystemBarStyleImpl,
        NavDestinationAttributeModifier::SetRecoverableImpl,
        NavDestinationAttributeModifier::SetSystemTransitionImpl,
        NavDestinationAttributeModifier::SetBindToScrollableImpl,
        NavDestinationAttributeModifier::SetBindToNestedScrollableImpl,
        NavDestinationAttributeModifier::SetOnActiveImpl,
        NavDestinationAttributeModifier::SetOnInactiveImpl,
        NavDestinationAttributeModifier::SetCustomTransitionImpl,
        NavDestinationAttributeModifier::SetOnNewParamImpl,
        NavDestinationAttributeModifier::SetPreferredOrientationImpl,
        NavDestinationAttributeModifier::SetEnableNavigationIndicatorImpl,
        NavDestinationAttributeModifier::SetTitleImpl,
        NavDestinationAttributeModifier::SetHideTitleBar1Impl,
        NavDestinationAttributeModifier::SetBackButtonIcon1Impl,
        NavDestinationAttributeModifier::SetMenus1Impl,
        NavDestinationAttributeModifier::SetToolbarConfigurationImpl,
        NavDestinationAttributeModifier::SetHideToolBarImpl,
        NavDestinationAttributeModifier::SetIgnoreLayoutSafeAreaImpl,
        NavDestinationAttributeModifier::SetEnableStatusBarImpl,
    };
    return &ArkUINavDestinationModifierImpl;
}

}
