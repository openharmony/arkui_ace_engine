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

#include "core/interfaces/native/node/node_api.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/base/frame_node.h"
#include "arkoala_api_generated.h"
#include "core/interfaces/arkoala/utility/converter.h"
#include "core/interfaces/arkoala/generated/interface/node_api.h"
#include "core/components_ng/pattern/navrouter/navdestination_model_ng.h"

namespace OHOS::Ace::NG {
namespace Converter {

template<>
void AssignCast(std::optional<NavDestinationMode>& dst, const Ark_NavDestinationMode& src)
{
    switch (src) {
        case ARK_NAV_DESTINATION_MODE_STANDARD: dst = NavDestinationMode::STANDARD; break;
        case ARK_NAV_DESTINATION_MODE_DIALOG: dst = NavDestinationMode::DIALOG; break;
        default: LOGE("Unexpected enum value in Ark_NavDestinationMode: %{public}d", src);
    }
}
} // namespace Converter
} // namespace OHOS::Ace::NG

namespace OHOS::Ace::NG::GeneratedModifier {
namespace NavDestinationInterfaceModifier {
void SetNavDestinationOptionsImpl(Ark_NativePointer node)
{
    // "No need to implement this method"
}
} // NavDestinationInterfaceModifier
namespace NavDestinationAttributeModifier {
void TitleImpl(Ark_NativePointer node,
               const Ark_Type_NavDestinationAttribute_title_value* value,
               const Opt_NavigationTitleOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    LOGE("ARKOALA NavDestination.TitleImpl -> Method is not implemented.");
}
void HideTitleBar0Impl(Ark_NativePointer node,
                       Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    NavDestinationModelNG::SetHideTitleBar(frameNode, Converter::Convert<bool>(value));
}
void HideTitleBar1Impl(Ark_NativePointer node,
                       Ark_Boolean hide,
                       Ark_Boolean animated)
{
     auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    NavDestinationModelNG::SetHideTitleBar(frameNode, Converter::Convert<bool>(hide));
    LOGE("ARKOALA NavDestination.HideTitleBar1Impl -> Method is not fully implemented.");
}
void OnShownImpl(Ark_NativePointer node,
                 Ark_Function callback)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto onShownEvent = [frameNode]() {
        GetFullAPI()->getEventsAPI()->getNavDestinationEventsReceiver()->onShown(frameNode->GetId());
    };
    NavDestinationModelNG::SetOnShown(frameNode, std::move(onShownEvent));
}
void OnHiddenImpl(Ark_NativePointer node,
                  Ark_Function callback)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto onHiddenEvent = [frameNode]() {
        GetFullAPI()->getEventsAPI()->getNavDestinationEventsReceiver()->onHidden(frameNode->GetId());
    };
    NavDestinationModelNG::SetOnHidden(frameNode, std::move(onHiddenEvent));
}
void OnBackPressedImpl(Ark_NativePointer node,
                       Ark_Function callback)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto onBackPressedEvent = [frameNode]() -> bool {
        GetFullAPI()->getEventsAPI()->getNavDestinationEventsReceiver()->onBackPressed(frameNode->GetId());
        return true;
    };
    NavDestinationModelNG::SetOnBackPressed(frameNode, std::move(onBackPressedEvent));
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
    LOGE("ARKOALA NavDestination.BackButtonIconImpl -> Method is not implemented.");
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //NavDestinationModelNG::SetBackButtonIcon(frameNode, convValue);
}
void MenusImpl(Ark_NativePointer node,
               const Ark_Union_Array_NavigationMenuItem_CustomBuilder* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    LOGE("ARKOALA NavDestination.MenusImpl -> Method is not implemented.");
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //NavDestinationModelNG::SetMenus(frameNode, convValue);
}
void OnReadyImpl(Ark_NativePointer node,
                 Ark_Function callback)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    LOGE("ARKOALA NavDestination.OnReadyImpl -> Method is not implemented.");
    //auto convValue = [frameNode](input values) { code }
    //NavDestinationModelNG::SetOnReady(frameNode, convValue);
}
void OnWillAppearImpl(Ark_NativePointer node,
                      Ark_Function callback)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto onWillAppearEvent = [frameNode]() {
        GetFullAPI()->getEventsAPI()->getNavDestinationEventsReceiver()->onWillAppear(frameNode->GetId());
        return true;
    };
    NavDestinationModelNG::SetOnWillAppear(frameNode, std::move(onWillAppearEvent));
    LOGE("ARKOALA NavDestination.OnWillAppear -> Method work incorrect.");
}
void OnWillDisappearImpl(Ark_NativePointer node,
                         Ark_Function callback)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto onWillDisappearEvent = [frameNode]() {
        GetFullAPI()->getEventsAPI()->getNavDestinationEventsReceiver()->onWillDisappear(frameNode->GetId());
        return true;
    };
    NavDestinationModelNG::SetOnWillDisAppear(frameNode, std::move(onWillDisappearEvent));
    LOGE("ARKOALA NavDestination.OnWillDisAppear -> Method work incorrect.");
}
void OnWillShowImpl(Ark_NativePointer node,
                    Ark_Function callback)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto onWillShowEvent = [frameNode]() {
        GetFullAPI()->getEventsAPI()->getNavDestinationEventsReceiver()->onWillShow(frameNode->GetId());
        return true;
    };
    NavDestinationModelNG::SetOnWillShow(frameNode, std::move(onWillShowEvent));
    LOGE("ARKOALA NavDestination.OnWillShow -> Method work incorrect.");
}
void OnWillHideImpl(Ark_NativePointer node,
                    Ark_Function callback)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto onWillHideEvent = [frameNode]() {
        GetFullAPI()->getEventsAPI()->getNavDestinationEventsReceiver()->onWillHide(frameNode->GetId());
        return true;
    };
    NavDestinationModelNG::SetOnWillHide(frameNode, std::move(onWillHideEvent));
    LOGE("ARKOALA NavDestination.OnWillHide -> Method work incorrect.");
}
void IgnoreLayoutSafeAreaImpl(Ark_NativePointer node,
                              const Opt_Array_LayoutSafeAreaType* types,
                              const Opt_Array_LayoutSafeAreaEdge* edges)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    LOGE("ARKOALA NavDestination.IgnoreLayoutSafeAreaImpl -> Method is not implemented.");
    //auto convValue = Converter::Convert<type>(types);
    //auto convValue = Converter::OptConvert<type>(types); // for enums
    //NavDestinationModelNG::SetIgnoreLayoutSafeArea(frameNode, convValue);
}
void SystemBarStyleImpl(Ark_NativePointer node,
                        const Opt_CustomObject* style)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = style ? Converter::OptConvert<type>(*style) : std::nullopt;
    //NavDestinationModelNG::SetSystemBarStyle(frameNode, convValue);
    LOGE("ARKOALA NavDestination.SystemBarStyleImpl -> Method is not implemented.");
}
void RecoverableImpl(Ark_NativePointer node,
                     const Opt_Boolean* recoverable)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = recoverable ? Converter::OptConvert<type>(*recoverable) : std::nullopt;
    //NavDestinationModelNG::SetRecoverable(frameNode, convValue);
    LOGE("ARKOALA NavDestination.RecoverableImpl -> Method is not implemented.");
}
void SystemTransitionImpl(Ark_NativePointer node,
                          Ark_NavigationSystemTransitionType type)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(type);
    //auto convValue = Converter::OptConvert<type>(type); // for enums
    //NavDestinationModelNG::SetSystemTransition(frameNode, convValue);
    LOGE("ARKOALA NavDestination.SystemTransitionImpl -> Method is not implemented.");
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
