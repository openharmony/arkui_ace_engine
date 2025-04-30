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
#include "core/components_ng/pattern/navigation/navigation_pattern.h"
#include "core/components_ng/pattern/navigation/navigation_model_data.h"
#include "core/components_ng/pattern/navigation/navigation_model_ng.h"
#include "core/interfaces/native/implementation/nav_path_stack_peer_impl.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace NavigationModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                Ark_Int32 flags)
{
    auto frameNode = NavigationModelNG::CreateFrameNode(id);
    CHECK_NULL_RETURN(frameNode, nullptr);
    frameNode->IncRefCount();
    return AceType::RawPtr(frameNode);
}
} // NavigationModifier
namespace NavigationInterfaceModifier {
void SetNavigationOptions0Impl(Ark_NativePointer node)
{
}
void SetNavigationOptions1Impl(Ark_NativePointer node,
                               Ark_NavPathStack pathInfos)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(pathInfos);
    auto navigationPattern = frameNode->GetPattern<NavigationPattern>();
    CHECK_NULL_VOID(navigationPattern);
    auto navigationStack = pathInfos->GetNavPathStack();
    navigationPattern->SetNavigationStack(navigationStack);
    navigationStack->SetOnStateChangedCallback(nullptr);
}
} // NavigationInterfaceModifier
namespace NavigationAttributeModifier {
void NavBarWidthImpl(Ark_NativePointer node,
                     const Opt_Length* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto result = Converter::OptConvert<Dimension>(*value);
    NavigationModelNG::SetNavBarWidth(frameNode, result.value());
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
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (value->tag == InteropTag::INTEROP_TAG_UNDEFINED) {
        NavigationModelNG::SetUsrNavigationMode(frameNode, NavigationMode::AUTO);
        return;
    }
    auto navigationMode = static_cast<NavigationMode>(value->value);
    NavigationModelNG::SetUsrNavigationMode(frameNode, navigationMode);
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
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto isHide = Converter::OptConvert<bool>(*value).value_or(false);
    NavigationModelNG::SetHideNavBar(frameNode, isHide);
}
void SubTitleImpl(Ark_NativePointer node,
                  const Opt_String* value)
{
}
void HideTitleBar0Impl(Ark_NativePointer node,
                       const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto hide = false;
    if (value->tag != InteropTag::INTEROP_TAG_UNDEFINED) {
        hide = Converter::OptConvert<bool>(*value).value_or(false);
    }
    NavigationModelNG::SetHideTitleBar(frameNode, hide, false);
}
void HideTitleBar1Impl(Ark_NativePointer node,
                       const Opt_Boolean* hide,
                       const Opt_Boolean* animated)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto isHide = false;
    if (hide->tag != InteropTag::INTEROP_TAG_UNDEFINED) {
        isHide = Converter::OptConvert<bool>(*hide).value_or(false);
    }
    bool isAnimated = false;
    if (animated->tag != InteropTag::INTEROP_TAG_UNDEFINED) {
        isAnimated = Converter::OptConvert<bool>(*animated).value_or(false);
    }
    NavigationModelNG::SetHideTitleBar(frameNode, isHide, isAnimated);
}
void HideBackButtonImpl(Ark_NativePointer node,
                        const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto isHide = false;
    if (value->tag != InteropTag::INTEROP_TAG_UNDEFINED) {
        isHide = Converter::OptConvert<bool>(*value).value_or(false);
    }
    NavigationModelNG::SetHideBackButton(frameNode, isHide);
}
void TitleModeImpl(Ark_NativePointer node,
                   const Opt_NavigationTitleMode* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NavigationTitleMode titleMode = NavigationTitleMode::FREE;
    if (value->tag != InteropTag::INTEROP_TAG_UNDEFINED) {
        titleMode = static_cast<NavigationTitleMode>(value->value);
    }
    NavigationModelNG::SetTitleMode(frameNode, titleMode);
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
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto isHide = false;
    if (value->tag != InteropTag::INTEROP_TAG_UNDEFINED) {
        isHide = Converter::OptConvert<bool>(*value).value_or(false);
    }
    NavigationModelNG::SetHideToolBar(frameNode, isHide, false);
}
void HideToolBar1Impl(Ark_NativePointer node,
                      const Opt_Boolean* hide,
                      const Opt_Boolean* animated)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto isHide = false;
    if (hide->tag != InteropTag::INTEROP_TAG_UNDEFINED) {
        isHide = Converter::OptConvert<bool>(*hide).value_or(false);
    }
    bool isAnimated = false;
    if (animated->tag != InteropTag::INTEROP_TAG_UNDEFINED) {
        isAnimated = Converter::OptConvert<bool>(*animated).value_or(false);
    }
    NavigationModelNG::SetHideToolBar(frameNode, isHide, isAnimated);
}
void EnableToolBarAdaptationImpl(Ark_NativePointer node,
                                 const Opt_Boolean* value)
{
}
void OnTitleModeChangeImpl(Ark_NativePointer node,
                           const Opt_Callback_NavigationTitleMode_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (value->tag == InteropTag::INTEROP_TAG_UNDEFINED) {
        return;
    }
    auto titleChange = [titleCallback = CallbackHelper(value->value)](NavigationTitleMode titleMode) {
        Ark_NavigationTitleMode mode = static_cast<Ark_NavigationTitleMode>(titleMode);
        titleCallback.Invoke(mode);
    };
    auto eventChange = [eventChange = CallbackHelper(value->value)](const BaseEventInfo* info) {
        auto eventInfo = TypeInfoHelper::DynamicCast<NavigationTitleModeChangeEvent>(info);
        if (!eventInfo) {
            return;
        }
        Ark_NavigationTitleMode titleMode = Ark_NavigationTitleMode::ARK_NAVIGATION_TITLE_MODE_FREE;
        if (eventInfo->IsMiniBar()) {
            titleMode = Ark_NavigationTitleMode::ARK_NAVIGATION_TITLE_MODE_MINI;
        }
        eventChange.Invoke(titleMode);
    };
    auto eventHub = frameNode->GetEventHub<NavigationEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnTitleModeChange(eventChange);
}
void OnNavBarStateChangeImpl(Ark_NativePointer node,
                             const Opt_Callback_Boolean_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (value->tag == InteropTag::INTEROP_TAG_UNDEFINED) {
        return;
    }
    auto stateCallback = [changeCallback = CallbackHelper(value->value)](bool isVisible) {
    auto visible = Converter::ArkValue<Ark_Boolean>(isVisible);
        changeCallback.Invoke(visible);
    };
    auto eventHub = frameNode->GetEventHub<NavigationEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnNavBarStateChange(stateCallback);
}
void OnNavigationModeChangeImpl(Ark_NativePointer node,
                                const Opt_Callback_NavigationMode_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (value->tag == InteropTag::INTEROP_TAG_UNDEFINED) {
        return;
    }
    auto modeCallback = [changeCallback = CallbackHelper(value->value)](NavigationMode mode) {
        auto navigationMode = Converter::ArkValue<Ark_NavigationMode>(mode);
        changeCallback.Invoke(navigationMode);
    };
    auto eventHub = frameNode->GetEventHub<NavigationEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnNavigationModeChange(modeCallback);
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
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NavigationTitlebarOptions titleOptions;
    if (options->tag != InteropTag::INTEROP_TAG_UNDEFINED) {
        titleOptions = Converter::OptConvert<NavigationTitlebarOptions>(options->value).value_or(titleOptions);
    }
    NavigationModelNG::SetTitlebarOptions(frameNode, std::move(titleOptions));
    NavigationTitleInfo info;
    if (value->tag == InteropTag::INTEROP_TAG_UNDEFINED) {
        info.hasMainTitle = true;
        info.hasSubTitle = false;
        info.title = "";
        info.subtitle = "";
        NavigationModelNG::ParseCommonTitle(frameNode, info);
        return;
    }
    auto selector = Converter::Convert<int32_t>(value->value.selector);
    const int8_t mainSelector = 0;
    if (selector == mainSelector) {
        info.title = Converter::OptConvert<std::string>(value->value.value0).value_or("");
        info.hasMainTitle = true;
        info.hasSubTitle = false;
        NavigationModelNG::ParseCommonTitle(frameNode, info);
        return;
    }
    const int8_t commonTitleSelector = 2;
    if (selector == commonTitleSelector) {
        info.title = Converter::OptConvert<std::string>(value->value.value2.main).value_or("");
        info.subtitle = Converter::OptConvert<std::string>(value->value.value2.sub).value_or("");
        info.hasSubTitle = true;
        info.hasMainTitle = true;
        NavigationModelNG::ParseCommonTitle(frameNode, info);
    }
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
