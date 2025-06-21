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
#include "core/components_ng/pattern/stack/stack_model_ng.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace NavDestinationModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                Ark_Int32 flags)
{
    // auto frameNode = NavDestinationModelNG::CreateFrameNode(id);
    // CHECK_NULL_RETURN(frameNode, nullptr);
    // frameNode->IncRefCount();
    // return AceType::RawPtr(frameNode);
    return nullptr;
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
                       Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    // NavDestinationModelNG::SetHideTitleBar(frameNode, Converter::Convert<bool>(value));
}
void HideTitleBar1Impl(Ark_NativePointer node,
                       Ark_Boolean hide,
                       Ark_Boolean animated)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NavDestinationModelNG::SetHideTitleBar(
        frameNode, Converter::Convert<bool>(hide), Converter::Convert<bool>(animated));
}
void OnShownImpl(Ark_NativePointer node,
                 const Callback_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto onShownEvent = [arkCallback = CallbackHelper(*value)]() {
        arkCallback.Invoke();
    };
    NavDestinationModelNG::SetOnShown(frameNode, std::move(onShownEvent));
}
void OnHiddenImpl(Ark_NativePointer node,
                  const Callback_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto onHiddenEvent = [arkCallback = CallbackHelper(*value)]() {
        arkCallback.Invoke();
    };
    NavDestinationModelNG::SetOnHidden(frameNode, std::move(onHiddenEvent));
}
void OnBackPressedImpl(Ark_NativePointer node,
                       const Callback_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto onBackPressedEvent = [arkCallback = CallbackHelper(*value)]() -> bool {
        return arkCallback.InvokeWithOptConvertResult<bool, Ark_Boolean, Callback_Boolean_Void>().value_or(false);
    };
    // NavDestinationModelNG::SetOnBackPressed(frameNode, std::move(onBackPressedEvent));
}
void ModeImpl(Ark_NativePointer node,
              Ark_NavDestinationMode value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto mode = Converter::OptConvert<NavDestinationMode>(value);
    NavDestinationModelNG::SetNavDestinationMode(frameNode, mode.value());
}
void BackButtonIconImpl(Ark_NativePointer node,
                        const Ark_Union_ResourceStr_PixelMap_SymbolGlyphModifier* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    LOGE("ARKOALA NavDestination.BackButtonIconImpl -> Method is not implemented, Ark_CustomObject is not supported!");
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //NavDestinationModelNG::SetBackButtonIcon(frameNode, convValue);
}
void MenusImpl(Ark_NativePointer node,
               const Ark_Union_Array_NavigationMenuItem_CustomBuilder* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    LOGE("ARKOALA NavDestination.MenusImpl -> Method is not implemented, CustomBuilder is not supported!");
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //NavDestinationModelNG::SetMenus(frameNode, convValue);
}
void OnReadyImpl(Ark_NativePointer node,
                 const Callback_NavDestinationContext_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    LOGE("ARKOALA NavDestination.OnReadyImpl -> Method is not implemented.");
    //auto convValue = [frameNode](input values) { code }
    //NavDestinationModelNG::SetOnReady(frameNode, convValue);
}
void OnWillAppearImpl(Ark_NativePointer node,
                      const Callback_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto onWillAppearEvent = [arkCallback = CallbackHelper(*value)]() {
        arkCallback.Invoke();
    };
    // NavDestinationModelNG::SetOnWillAppear(frameNode, std::move(onWillAppearEvent));
}
void OnWillDisappearImpl(Ark_NativePointer node,
                         const Callback_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto onWillDisappearEvent = [arkCallback = CallbackHelper(*value)]() {
        arkCallback.Invoke();
    };
    // NavDestinationModelNG::SetOnWillDisAppear(frameNode, std::move(onWillDisappearEvent));
}
void OnWillShowImpl(Ark_NativePointer node,
                    const Callback_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto onWillShowEvent = [arkCallback = CallbackHelper(*value)]() {
        arkCallback.Invoke();
    };
    // NavDestinationModelNG::SetOnWillShow(frameNode, std::move(onWillShowEvent));
}
void OnWillHideImpl(Ark_NativePointer node,
                    const Callback_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto onWillHideEvent = [arkCallback = CallbackHelper(*value)]() {
        arkCallback.Invoke();
    };
    // NavDestinationModelNG::SetOnWillHide(frameNode, std::move(onWillHideEvent));
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
    // NavDestinationModelNG::SetRecoverable(frameNode, convValue);
}
void SystemTransitionImpl(Ark_NativePointer node,
                          Ark_NavigationSystemTransitionType value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(value);
    //auto convValue = Converter::OptConvert<type>(value); // for enums
    //NavDestinationModelNG::SetSystemTransition(frameNode, convValue);
    LOGE("ARKOALA NavDestination.SystemTransitionImpl -> Method is not implemented. "
         "No handlers for Ark_NavigationSystemTransitionType in model");
}
void TitleImpl(Ark_NativePointer node,
               const Ark_Type_NavDestinationAttribute_title_value* value,
               const Opt_NavigationTitleOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    LOGE("ARKOALA NavDestination.TitleImpl -> Method is not implemented. Ark_CustomObject is not supported!");
}
void ToolbarConfigurationImpl(Ark_NativePointer node,
                              const Ark_Union_Array_ToolbarItem_CustomBuilder* toolbarParam,
                              const Opt_NavigationToolbarOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(toolbarParam);
    //auto convValue = Converter::OptConvert<type>(toolbarParam); // for enums
    //NavDestinationModelNG::SetToolbarConfiguration(frameNode, convValue);
}
void HideToolBarImpl(Ark_NativePointer node,
                     Ark_Boolean hide,
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

    NG::IgnoreLayoutSafeAreaOpts opts { .type = NG::SAFE_AREA_TYPE_SYSTEM, .edges = NG::SAFE_AREA_EDGE_ALL };
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
} // NavDestinationAttributeModifier
const GENERATED_ArkUINavDestinationModifier* GetNavDestinationModifier()
{
    static const GENERATED_ArkUINavDestinationModifier ArkUINavDestinationModifierImpl {
        NavDestinationModifier::ConstructImpl,
        NavDestinationInterfaceModifier::SetNavDestinationOptionsImpl,
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
        NavDestinationAttributeModifier::SystemBarStyleImpl,
        NavDestinationAttributeModifier::RecoverableImpl,
        NavDestinationAttributeModifier::SystemTransitionImpl,
        NavDestinationAttributeModifier::TitleImpl,
        NavDestinationAttributeModifier::ToolbarConfigurationImpl,
        NavDestinationAttributeModifier::HideToolBarImpl,
        NavDestinationAttributeModifier::IgnoreLayoutSafeAreaImpl,
    };
    return &ArkUINavDestinationModifierImpl;
}

}
