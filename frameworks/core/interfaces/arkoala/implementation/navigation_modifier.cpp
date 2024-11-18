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
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(pathInfos);
    //auto convValue = Converter::OptConvert<type_name>(*pathInfos);
    //NavigationModelNG::SetSetNavigationOptions1(frameNode, convValue);
}
} // NavigationInterfaceModifier
namespace NavigationAttributeModifier {
void NavBarWidthImpl(Ark_NativePointer node,
                     const Ark_Length* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    // need to check Resource to Dimension conversion
    LOGE("ARKOALA NavBarWidthImpl conversion from Resource to Dimension is not implemented.");
    NavigationModelNG::SetNavBarWidth(frameNode, Converter::Convert<Dimension>(*value));
}
void NavBarPositionImpl(Ark_NativePointer node,
                        Ark_NavBarPosition value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    NavigationModelNG::SetNavBarPosition(frameNode, Converter::OptConvert<NavBarPosition>(value));
}
void NavBarWidthRangeImpl(Ark_NativePointer node,
                          const Ark_Tuple_Dimension_Dimension* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    // need to check Resource to Dimension conversion
    LOGE("ARKOALA NavBarWidthImpl conversion from Resource to Dimension is not implemented.");
    std::pair<Dimension, Dimension> tupleValue =
        Converter::Convert<std::pair<Dimension, Dimension>>(*value);
    NavigationModelNG::SetMinNavBarWidth(frameNode, tupleValue.first);
    NavigationModelNG::SetMaxNavBarWidth(frameNode, tupleValue.second);
}
void MinContentWidthImpl(Ark_NativePointer node,
                         const Ark_Length* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    // need to check Resource to Dimension conversion
    LOGE("ARKOALA MinContentWidthImpl conversion from Resource to Dimension is not implemented.");
    NavigationModelNG::SetMinContentWidth(frameNode, Converter::Convert<Dimension>(*value));
}
void ModeImpl(Ark_NativePointer node,
              Ark_NavigationMode value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    NavigationModelNG::SetUsrNavigationMode(frameNode, Converter::OptConvert<NavigationMode>(value));
}
void BackButtonIconImpl(Ark_NativePointer node,
                        const Ark_Union_String_PixelMap_Resource_SymbolGlyphModifier* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //NavigationModelNG::SetBackButtonIcon(frameNode, convValue);
}
void HideNavBarImpl(Ark_NativePointer node,
                    Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    NavigationModelNG::SetHideNavBar(frameNode, Converter::Convert<bool>(value));
}
void SubTitleImpl(Ark_NativePointer node,
                  const Ark_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    NavigationModelNG::SetSubtitle(frameNode, Converter::Convert<std::string>(*value));
}
void HideTitleBar0Impl(Ark_NativePointer node,
                       Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    NavigationModelNG::SetHideTitleBar(frameNode, Converter::Convert<bool>(value));
}
void HideTitleBar1Impl(Ark_NativePointer node,
                       Ark_Boolean hide,
                       Ark_Boolean animated)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(hide);
    //auto convValue = Converter::OptConvert<type>(hide); // for enums
    //NavigationModelNG::SetHideTitleBar1(frameNode, convValue);
    LOGE("ARKOALA, NavigationModifier::HideTitleBar1Impl: animated API is not implemented in ace_engine");
}
void HideBackButtonImpl(Ark_NativePointer node,
                        Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    NavigationModelNG::SetHideBackButton(frameNode, Converter::Convert<bool>(value));
}
void TitleModeImpl(Ark_NativePointer node,
                   Ark_NavigationTitleMode value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    NavigationModelNG::SetTitleMode(frameNode, Converter::OptConvert<NavigationTitleMode>(value));
}
void MenusImpl(Ark_NativePointer node,
               const Ark_Union_Array_NavigationMenuItem_CustomBuilder* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //NavigationModelNG::SetMenus(frameNode, convValue);
}
void ToolBarImpl(Ark_NativePointer node,
                 const Ark_Union_Object_CustomBuilder* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //NavigationModelNG::SetToolBar(frameNode, convValue);
}
void HideToolBar0Impl(Ark_NativePointer node,
                      Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    NavigationModelNG::SetHideToolBar(frameNode, Converter::Convert<bool>(value));
}
void HideToolBar1Impl(Ark_NativePointer node,
                      Ark_Boolean hide,
                      Ark_Boolean animated)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(hide);
    //auto convValue = Converter::OptConvert<type>(hide); // for enums
    //NavigationModelNG::SetHideToolBar1(frameNode, convValue);
    LOGE("ARKOALA, NavigationModifier::HideToolBar1Impl: animated API is not implemented in ace_engine");
}
void OnTitleModeChangeImpl(Ark_NativePointer node,
                           const Callback_NavigationTitleMode_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //NavigationModelNG::SetOnTitleModeChange(frameNode, convValue);
}
void OnNavBarStateChangeImpl(Ark_NativePointer node,
                             const Callback_Boolean_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto onNavBarStateChange = [frameNode](bool isVisible) {
        auto arkIsVisible = Converter::ArkValue<Ark_Boolean>(isVisible);
        GetFullAPI()->getEventsAPI()->getNavigationEventsReceiver()->onNavBarStateChange(
            frameNode->GetId(), arkIsVisible);
    };
    NavigationModelNG::SetOnNavBarStateChange(frameNode, std::move(onNavBarStateChange));
}
void OnNavigationModeChangeImpl(Ark_NativePointer node,
                                const Callback_NavigationMode_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto onModeChange = [frameNode](NG::NavigationMode mode) {
        auto arkMode = Converter::ArkValue<Ark_NavigationMode>(mode);
        GetFullAPI()->getEventsAPI()->getNavigationEventsReceiver()->onNavigationModeChange(
            frameNode->GetId(), arkMode);
    };
    NavigationModelNG::SetOnNavigationModeChange(frameNode, std::move(onModeChange));
}
void NavDestinationImpl(Ark_NativePointer node,
                        const Callback_String_Unknown_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //NavigationModelNG::SetNavDestination(frameNode, convValue);
}
void CustomNavContentTransitionImpl(Ark_NativePointer node,
                                    const Type_NavigationAttribute_customNavContentTransition_delegate* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //NavigationModelNG::SetCustomNavContentTransition(frameNode, convValue);
}
void SystemBarStyleImpl(Ark_NativePointer node,
                        const Ark_Union_SystemBarStyle_Undefined* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //NavigationModelNG::SetSystemBarStyle(frameNode, convValue);
}
void RecoverableImpl(Ark_NativePointer node,
                     const Ark_Union_Boolean_Undefined* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    NavigationModelNG::SetRecoverable(frameNode,
        value ? Converter::OptConvert<bool>(*value) : std::nullopt);
}
void TitleImpl(Ark_NativePointer node,
               const Ark_Type_NavigationAttribute_title_value* value,
               const Opt_NavigationTitleOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(value);
    //auto convValue = Converter::OptConvert<type>(value); // for enums
    //NavigationModelNG::SetTitle(frameNode, convValue);
}
void ToolbarConfigurationImpl(Ark_NativePointer node,
                              const Ark_Union_Array_ToolbarItem_CustomBuilder* value,
                              const Opt_NavigationToolbarOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(value);
    //auto convValue = Converter::OptConvert<type>(value); // for enums
    //NavigationModelNG::SetToolbarConfiguration(frameNode, convValue);
}
void IgnoreLayoutSafeAreaImpl(Ark_NativePointer node,
                              const Opt_Array_LayoutSafeAreaType* types,
                              const Opt_Array_LayoutSafeAreaEdge* edges)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(types);
    //auto convValue = Converter::OptConvert<type>(types); // for enums
    //NavigationModelNG::SetIgnoreLayoutSafeArea(frameNode, convValue);
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
        NavigationAttributeModifier::SubTitleImpl,
        NavigationAttributeModifier::HideTitleBar0Impl,
        NavigationAttributeModifier::HideTitleBar1Impl,
        NavigationAttributeModifier::HideBackButtonImpl,
        NavigationAttributeModifier::TitleModeImpl,
        NavigationAttributeModifier::MenusImpl,
        NavigationAttributeModifier::ToolBarImpl,
        NavigationAttributeModifier::HideToolBar0Impl,
        NavigationAttributeModifier::HideToolBar1Impl,
        NavigationAttributeModifier::OnTitleModeChangeImpl,
        NavigationAttributeModifier::OnNavBarStateChangeImpl,
        NavigationAttributeModifier::OnNavigationModeChangeImpl,
        NavigationAttributeModifier::NavDestinationImpl,
        NavigationAttributeModifier::CustomNavContentTransitionImpl,
        NavigationAttributeModifier::SystemBarStyleImpl,
        NavigationAttributeModifier::RecoverableImpl,
        NavigationAttributeModifier::TitleImpl,
        NavigationAttributeModifier::ToolbarConfigurationImpl,
        NavigationAttributeModifier::IgnoreLayoutSafeAreaImpl,
    };
    return &ArkUINavigationModifierImpl;
}

}
