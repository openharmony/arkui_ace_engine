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

#include "core/components/common/layout/constants.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/navigation/navigation_model_ng.h"
#include "core/interfaces/arkoala/utility/converter.h"
#include "core/interfaces/arkoala/utility/reverse_converter.h"
#include "core/interfaces/arkoala/generated/interface/node_api.h"

namespace OHOS::Ace::NG::Converter {
template<>
void AssignCast(std::optional<NavBarPosition>& dst, const Ark_NavBarPosition& src)
{
    switch (src) {
        case ARK_NAV_BAR_POSITION_START: dst = NavBarPosition::START; break;
        case ARK_NAV_BAR_POSITION_END: dst = NavBarPosition::END; break;
        default: LOGE("Unexpected enum value in Ark_NavBarPosition: %{public}d", src);
    }
}

template<>
void AssignCast(std::optional<NavigationMode>& dst, const Ark_NavigationMode& src)
{
    switch (src) {
        case ARK_NAVIGATION_MODE_STACK: dst = NavigationMode::STACK; break;
        case ARK_NAVIGATION_MODE_SPLIT: dst = NavigationMode::SPLIT; break;
        case ARK_NAVIGATION_MODE_AUTO: dst = NavigationMode::AUTO; break;
        default: LOGE("Unexpected enum value in Ark_NavigationMode: %{public}d", src);
    }
}

template<>
void AssignCast(std::optional<NavigationTitleMode>& dst, const Ark_NavigationTitleMode& src)
{
    switch (src) {
        case ARK_NAVIGATION_TITLE_MODE_FREE: dst = NavigationTitleMode::FREE; break;
        case ARK_NAVIGATION_TITLE_MODE_FULL: dst = NavigationTitleMode::FULL; break;
        case ARK_NAVIGATION_TITLE_MODE_MINI: dst = NavigationTitleMode::MINI; break;
        default: LOGE("Unexpected enum value in Ark_NavigationTitleMode: %{public}d", src);
    }
}
} // namespace OHOS::Ace::NG::Converter

namespace OHOS::Ace::NG::GeneratedModifier {
namespace NavigationInterfaceModifier {
void SetNavigationOptions0Impl(Ark_NativePointer node)
{
    // no need to handle method without options
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
    CHECK_NULL_VOID(value);
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    // need to check Resource to Dimension convertion
    LOGE("ARKOALA NavBarWidthImpl convertion from Resource to Dimension is not implemented.");
    NavigationModelNG::SetNavBarWidth(frameNode, Converter::Convert<Dimension>(*value));
}
void NavBarPositionImpl(Ark_NativePointer node,
                        enum Ark_NavBarPosition value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NavigationModelNG::SetNavBarPosition(frameNode, Converter::OptConvert<NavBarPosition>(value));
}
void NavBarWidthRangeImpl(Ark_NativePointer node,
                          const Type_NavigationAttribute_navBarWidthRange_Arg0* value)
{
    CHECK_NULL_VOID(value);
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    // need to check Resource to Dimension convertion
    LOGE("ARKOALA NavBarWidthImpl convertion from Resource to Dimension is not implemented.");
    std::pair<Dimension, Dimension> tupleValue =
        Converter::Convert<std::pair<Dimension, Dimension>>(*value);
    NavigationModelNG::SetMinNavBarWidth(frameNode, tupleValue.first);
    NavigationModelNG::SetMaxNavBarWidth(frameNode, tupleValue.second);
}
void MinContentWidthImpl(Ark_NativePointer node,
                         const Ark_Length* value)
{
    CHECK_NULL_VOID(value);
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    // need to check Resource to Dimension convertion
    LOGE("ARKOALA MinContentWidthImpl convertion from Resource to Dimension is not implemented.");
    NavigationModelNG::SetMinContentWidth(frameNode, Converter::Convert<Dimension>(*value));
}
void ModeImpl(Ark_NativePointer node,
              enum Ark_NavigationMode value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NavigationModelNG::SetUsrNavigationMode(frameNode, Converter::OptConvert<NavigationMode>(value));
}
void BackButtonIconImpl(Ark_NativePointer node,
                        const Type_NavigationAttribute_backButtonIcon_Arg0* value)
{
}
void HideNavBarImpl(Ark_NativePointer node,
                    Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NavigationModelNG::SetHideNavBar(frameNode, Converter::Convert<bool>(value));
}
void TitleImpl(Ark_NativePointer node,
               const Type_NavigationAttribute_title_Arg0* value,
               const Opt_NavigationTitleOptions* options)
{
}
void SubTitleImpl(Ark_NativePointer node,
                  const Ark_String* value)
{
    CHECK_NULL_VOID(value);
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NavigationModelNG::SetSubtitle(frameNode, Converter::Convert<std::string>(*value));
}
void HideTitleBar0Impl(Ark_NativePointer node,
                       Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NavigationModelNG::SetHideTitleBar(frameNode, Converter::Convert<bool>(value));
}
void HideTitleBar1Impl(Ark_NativePointer node,
                       Ark_Boolean hide,
                       Ark_Boolean animated)
{
    LOGE("ARKOALA, NavigationModifier::HideTitleBar1Impl: animated API is not implemented in ace_engine");
}
void HideBackButtonImpl(Ark_NativePointer node,
                        Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NavigationModelNG::SetHideBackButton(frameNode, Converter::Convert<bool>(value));
}
void TitleModeImpl(Ark_NativePointer node,
                   enum Ark_NavigationTitleMode value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NavigationModelNG::SetTitleMode(frameNode, Converter::OptConvert<NavigationTitleMode>(value));
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
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NavigationModelNG::SetHideToolBar(frameNode, Converter::Convert<bool>(value));
}
void HideToolBar1Impl(Ark_NativePointer node,
                      Ark_Boolean hide,
                      Ark_Boolean animated)
{
    LOGE("ARKOALA, NavigationModifier::HideToolBar1Impl: animated API is not implemented in ace_engine");
}
void OnTitleModeChangeImpl(Ark_NativePointer node,
                           Ark_Function callback)
{
}
void OnNavBarStateChangeImpl(Ark_NativePointer node,
                             Ark_Function callback)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto onNavBarStateChange = [frameNode](bool isVisible) {
        auto arkIsVisible = Converter::ArkValue<Ark_Boolean>(isVisible);
        GetFullAPI()->getEventsAPI()->getNavigationEventsReceiver()->onNavBarStateChange(
            frameNode->GetId(), arkIsVisible);
    };
    NavigationModelNG::SetOnNavBarStateChange(frameNode, std::move(onNavBarStateChange));
}
void OnNavigationModeChangeImpl(Ark_NativePointer node,
                                Ark_Function callback)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto onModeChange = [frameNode](NG::NavigationMode mode) {
        auto arkMode = Converter::ArkValue<Ark_NavigationMode>(mode);
        GetFullAPI()->getEventsAPI()->getNavigationEventsReceiver()->onNavigationModeChange(
            frameNode->GetId(), arkMode);
    };
    NavigationModelNG::SetOnNavigationModeChange(frameNode, std::move(onModeChange));
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
    CHECK_NULL_VOID(recoverable);
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NavigationModelNG::SetRecoverable(frameNode, Converter::OptConvert<bool>(*recoverable));
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
