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

#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/base/frame_node.h"
#include "arkoala_api_generated.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/generated/interface/node_api.h"
#include "core/components_ng/pattern/navrouter/navdestination_model_ng.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace NavDestinationModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                Ark_Int32 flags)
{
    auto frameNode = NavDestinationModelNG::CreateFrameNode(id);
    CHECK_NULL_RETURN(frameNode, nullptr);
    frameNode->IncRefCount();
    return AceType::RawPtr(frameNode);
}
} // NavDestinationModifier
namespace NavDestinationInterfaceModifier {
void SetNavDestinationOptionsImpl(Ark_NativePointer node)
{
    // "No need to implement this method"
}
} // NavDestinationInterfaceModifier
namespace NavDestinationAttributeModifier {
void HideTitleBar0Impl(Ark_NativePointer node,
                       const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NavDestinationModelNG::SetHideTitleBar(frameNode, Converter::OptConvert<bool>(*value).value_or(false));
}
void HideTitleBar1Impl(Ark_NativePointer node,
                       const Opt_Boolean* hide,
                       const Opt_Boolean* animated)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NavDestinationModelNG::SetHideTitleBar(frameNode,
        Converter::OptConvert<bool>(*hide).value_or(false),
        Converter::OptConvert<bool>(*animated).value_or(false));
}
void HideBackButtonImpl(Ark_NativePointer node,
                        const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //NavDestinationModelNG::SetHideBackButton(frameNode, convValue);
}
void OnShownImpl(Ark_NativePointer node,
                 const Opt_Callback_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // TODO: Reset value
        return;
    }
    auto onShownEvent = [arkCallback = CallbackHelper(*optValue)]() {
        arkCallback.Invoke();
    };
    NavDestinationModelNG::SetOnShown(frameNode, std::move(onShownEvent));
}
void OnHiddenImpl(Ark_NativePointer node,
                  const Opt_Callback_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // TODO: Reset value
        return;
    }
    auto onHiddenEvent = [arkCallback = CallbackHelper(*optValue)]() {
        arkCallback.Invoke();
    };
    NavDestinationModelNG::SetOnHidden(frameNode, std::move(onHiddenEvent));
}
void OnBackPressedImpl(Ark_NativePointer node,
                       const Opt_Callback_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // TODO: Reset value
        return;
    }
    auto onBackPressedEvent = [arkCallback = CallbackHelper(*optValue)]() -> bool {
        return arkCallback.InvokeWithOptConvertResult<bool, Ark_Boolean, Callback_Boolean_Void>().value_or(false);
    };
    NavDestinationModelNG::SetOnBackPressed(frameNode, std::move(onBackPressedEvent));
}
void OnResultImpl(Ark_NativePointer node,
                  const Opt_Callback_Object_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //NavDestinationModelNG::SetOnResult(frameNode, convValue);
}
void ModeImpl(Ark_NativePointer node,
              const Opt_NavDestinationMode* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto mode = Converter::OptConvert<NavDestinationMode>(*value);
    NavDestinationModelNG::SetNavDestinationMode(frameNode, mode.value());
}
void BackButtonIcon0Impl(Ark_NativePointer node,
                         const Opt_Union_ResourceStr_PixelMap_SymbolGlyphModifier* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    LOGE("ARKOALA NavDestination.BackButtonIconImpl -> Method is not implemented, Ark_CustomObject is not supported!");
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //NavDestinationModelNG::SetBackButtonIcon0(frameNode, convValue);
}
void BackButtonIcon1Impl(Ark_NativePointer node,
                         const Opt_Union_ResourceStr_PixelMap_SymbolGlyphModifier* icon,
                         const Opt_ResourceStr* accessibilityText)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(icon);
    //auto convValue = Converter::OptConvert<type>(icon); // for enums
    //NavDestinationModelNG::SetBackButtonIcon1(frameNode, convValue);
}
void Menus0Impl(Ark_NativePointer node,
                const Opt_Union_Array_NavigationMenuItem_CustomBuilder* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    LOGE("ARKOALA NavDestination.MenusImpl -> Method is not implemented, CustomBuilder is not supported!");
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //NavDestinationModelNG::SetMenus0(frameNode, convValue);
}
void Menus1Impl(Ark_NativePointer node,
                const Opt_Union_Array_NavigationMenuItem_CustomBuilder* items,
                const Opt_NavigationMenuOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(items);
    //auto convValue = Converter::OptConvert<type>(items); // for enums
    //NavDestinationModelNG::SetMenus1(frameNode, convValue);
}
void OnReadyImpl(Ark_NativePointer node,
                 const Opt_Callback_NavDestinationContext_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    LOGE("ARKOALA NavDestination.OnReadyImpl -> Method is not implemented.");
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //NavDestinationModelNG::SetOnReady(frameNode, convValue);
}
void OnWillAppearImpl(Ark_NativePointer node,
                      const Opt_Callback_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // TODO: Reset value
        return;
    }
    auto onWillAppearEvent = [arkCallback = CallbackHelper(*optValue)]() {
        arkCallback.Invoke();
    };
    NavDestinationModelNG::SetOnWillAppear(frameNode, std::move(onWillAppearEvent));
}
void OnWillDisappearImpl(Ark_NativePointer node,
                         const Opt_Callback_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // TODO: Reset value
        return;
    }
    auto onWillDisappearEvent = [arkCallback = CallbackHelper(*optValue)]() {
        arkCallback.Invoke();
    };
    NavDestinationModelNG::SetOnWillDisAppear(frameNode, std::move(onWillDisappearEvent));
}
void OnWillShowImpl(Ark_NativePointer node,
                    const Opt_Callback_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // TODO: Reset value
        return;
    }
    auto onWillShowEvent = [arkCallback = CallbackHelper(*optValue)]() {
        arkCallback.Invoke();
    };
    NavDestinationModelNG::SetOnWillShow(frameNode, std::move(onWillShowEvent));
}
void OnWillHideImpl(Ark_NativePointer node,
                    const Opt_Callback_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // TODO: Reset value
        return;
    }
    auto onWillHideEvent = [arkCallback = CallbackHelper(*optValue)]() {
        arkCallback.Invoke();
    };
    NavDestinationModelNG::SetOnWillHide(frameNode, std::move(onWillHideEvent));
}
void SystemBarStyleImpl(Ark_NativePointer node,
                        const Opt_SystemBarStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //NavDestinationModelNG::SetSystemBarStyle(frameNode, convValue);
    LOGE("ARKOALA NavDestination.SystemBarStyleImpl -> Method is not implemented, Opt_CustomObject is not supported!");
}
void RecoverableImpl(Ark_NativePointer node,
                     const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = value ? Converter::OptConvert<bool>(*value) : std::nullopt;
    NavDestinationModelNG::SetRecoverable(frameNode, convValue);
}
void SystemTransitionImpl(Ark_NativePointer node,
                          const Opt_NavigationSystemTransitionType* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //NavDestinationModelNG::SetSystemTransition(frameNode, convValue);
    LOGE("ARKOALA NavDestination.SystemTransitionImpl -> Method is not implemented. "
         "No handlers for Ark_NavigationSystemTransitionType in model");
}
void BindToScrollableImpl(Ark_NativePointer node,
                          const Opt_Array_Scroller* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //NavDestinationModelNG::SetBindToScrollable(frameNode, convValue);
}
void BindToNestedScrollableImpl(Ark_NativePointer node,
                                const Opt_Array_NestedScrollInfo* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //NavDestinationModelNG::SetBindToNestedScrollable(frameNode, convValue);
}
void OnActiveImpl(Ark_NativePointer node,
                  const Opt_Callback_NavDestinationActiveReason_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //NavDestinationModelNG::SetOnActive(frameNode, convValue);
}
void OnInactiveImpl(Ark_NativePointer node,
                    const Opt_Callback_NavDestinationActiveReason_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //NavDestinationModelNG::SetOnInactive(frameNode, convValue);
}
void CustomTransitionImpl(Ark_NativePointer node,
                          const Opt_NavDestinationTransitionDelegate* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //NavDestinationModelNG::SetCustomTransition(frameNode, convValue);
}
void OnNewParamImpl(Ark_NativePointer node,
                    const Opt_Callback_Object_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //NavDestinationModelNG::SetOnNewParam(frameNode, convValue);
}
void PreferredOrientationImpl(Ark_NativePointer node,
                              const Opt_Orientation* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //NavDestinationModelNG::SetPreferredOrientation(frameNode, convValue);
}
void EnableNavigationIndicatorImpl(Ark_NativePointer node,
                                   const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //NavDestinationModelNG::SetEnableNavigationIndicator(frameNode, convValue);
}
void TitleImpl(Ark_NativePointer node,
               const Opt_Type_NavDestinationAttribute_title_value* value,
               const Opt_NavigationTitleOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    LOGE("ARKOALA NavDestination.TitleImpl -> Method is not implemented. Ark_CustomObject is not supported!");
}
void ToolbarConfigurationImpl(Ark_NativePointer node,
                              const Opt_Union_Array_ToolbarItem_CustomBuilder* toolbarParam,
                              const Opt_NavigationToolbarOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(toolbarParam);
    //auto convValue = Converter::OptConvert<type>(toolbarParam); // for enums
    //NavDestinationModelNG::SetToolbarConfiguration(frameNode, convValue);
}
void HideToolBarImpl(Ark_NativePointer node,
                     const Opt_Boolean* hide,
                     const Opt_Boolean* animated)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(hide);
    //auto convValue = Converter::OptConvert<type>(hide); // for enums
    //NavDestinationModelNG::SetHideToolBar(frameNode, convValue);
}
void IgnoreLayoutSafeAreaImpl(Ark_NativePointer node,
                              const Opt_Array_LayoutSafeAreaType* types,
                              const Opt_Array_LayoutSafeAreaEdge* edges)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);

    NG::SafeAreaExpandOpts opts { .type = NG::SAFE_AREA_TYPE_SYSTEM, .edges = NG::SAFE_AREA_EDGE_ALL };
    auto typesOpt = types ? Converter::OptConvert<Array_LayoutSafeAreaType>(*types) : std::nullopt;
    uint32_t safeAreaType = NG::SAFE_AREA_TYPE_NONE;
    if (typesOpt) {
        for (int i = 0; i < typesOpt->length; ++i) {
            auto value = typesOpt->array[i];
            if (value == ARK_LAYOUT_SAFE_AREA_TYPE_SYSTEM) {
                safeAreaType = NG::SAFE_AREA_TYPE_SYSTEM;
                break;
            }
        }
        opts.type = safeAreaType;
    }

    auto edgesOpt = types ? Converter::OptConvert<Array_LayoutSafeAreaEdge>(*edges) : std::nullopt;
    uint32_t safeAreaEdge = NG::SAFE_AREA_EDGE_NONE;
    if (edgesOpt) {
        for (int i = 0; i < edgesOpt->length; ++i) {
            auto value = edgesOpt->array[i];
            if (value == ARK_LAYOUT_SAFE_AREA_EDGE_TOP) {
                safeAreaEdge = NG::SAFE_AREA_EDGE_TOP;
                break;
            } else if (value == ARK_LAYOUT_SAFE_AREA_EDGE_BOTTOM) {
                safeAreaEdge = NG::SAFE_AREA_EDGE_BOTTOM;
                break;
            }
        }
        opts.edges = safeAreaEdge;
    }
    NavDestinationModelNG::SetIgnoreLayoutSafeArea(frameNode, opts);
}
void EnableStatusBarImpl(Ark_NativePointer node,
                         const Opt_Boolean* enabled,
                         const Opt_Boolean* animated)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(enabled);
    //auto convValue = Converter::OptConvert<type>(enabled); // for enums
    //NavDestinationModelNG::SetEnableStatusBar(frameNode, convValue);
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
