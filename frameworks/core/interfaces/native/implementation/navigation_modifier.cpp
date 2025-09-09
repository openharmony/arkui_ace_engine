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

#include "arkoala_api_generated.h"

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/navigation/navigation_model_data.h"
#include "core/components_ng/pattern/navigation/navigation_model_static.h"
#include "core/components_ng/pattern/navigation/navigation_pattern.h"
#include "core/components_ng/pattern/navigation/navigation_transition_proxy.h"
#include "core/interfaces/native/implementation/nav_path_stack_peer_impl.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace {
constexpr uint32_t SAFE_AREA_TYPE_LIMIT = 3;
constexpr uint32_t SAFE_AREA_EDGE_LIMIT = 4;
constexpr uint32_t SAFE_AREA_EDGE_SYSTEM = 0;
constexpr uint32_t SAFE_AREA_EDGE_TOP = 0;
constexpr uint32_t SAFE_AREA_EDGE_BOTTOM = 1;
} // namespace
namespace NavigationModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id, Ark_Int32 flags)
{
    auto frameNode = NavigationModelStatic::CreateFrameNode(id);
    CHECK_NULL_RETURN(frameNode, nullptr);
    frameNode->IncRefCount();
    return AceType::RawPtr(frameNode);
}
} // namespace NavigationModifier
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
} // namespace NavigationInterfaceModifier
namespace NavigationAttributeModifier {
void NavBarWidthImpl(Ark_NativePointer node,
                     const Opt_Length* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto result = Converter::OptConvert<Dimension>(*value);
    NavigationModelStatic::SetNavBarWidth(frameNode, result.value());
}
void NavBarPositionImpl(Ark_NativePointer node,
                        const Opt_NavBarPosition* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    Opt_NavBarPosition def;
    def.value = ARK_NAV_BAR_POSITION_START;
    auto barDef = static_cast<NG::NavBarPosition>(def.value);
    if (value->tag == InteropTag::INTEROP_TAG_UNDEFINED) {
        NavigationModelStatic::SetNavBarPosition(frameNode, barDef);
        return;
    }
    auto barPosition = static_cast<NG::NavBarPosition>(value->value);
    NavigationModelStatic::SetNavBarPosition(frameNode, barPosition);
}
void NavBarWidthRangeImpl(Ark_NativePointer node,
                          const Opt_Tuple_Dimension_Dimension* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (value->tag == InteropTag::INTEROP_TAG_UNDEFINED) {
        NavigationModelStatic::SetMinNavBarWidth(frameNode, NG::DEFAULT_MIN_NAV_BAR_WIDTH);
        NavigationModelStatic::SetMaxNavBarWidth(frameNode, NG::DEFAULT_MAX_NAV_BAR_WIDTH);
        return;
    }
    auto min = Converter::Convert<CalcDimension>(value->value.value0);
    auto max = Converter::Convert<CalcDimension>(value->value.value1);

    if (LessNotEqual(min.Value(), 0.0)) {
        min.SetValue(0);
    }
    NavigationModelStatic::SetMinNavBarWidth(frameNode, min);
    if (LessNotEqual(max.Value(), 0.0)) {
        max.SetValue(0);
    }
    NavigationModelStatic::SetMaxNavBarWidth(frameNode, max);
}
void MinContentWidthImpl(Ark_NativePointer node,
                         const Opt_Length* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (value->tag == InteropTag::INTEROP_TAG_UNDEFINED) {
        NavigationModelStatic::SetMinContentWidth(frameNode, DEFAULT_MIN_CONTENT_WIDTH);
        return;
    }
    auto mincontent = Converter::Convert<CalcDimension>(value->value);

    if (LessNotEqual(mincontent.Value(), 0.0)) {
        mincontent = DEFAULT_MIN_CONTENT_WIDTH;
    }

    NavigationModelStatic::SetMinContentWidth(frameNode, mincontent);
}
void ModeImpl(Ark_NativePointer node,
              const Opt_NavigationMode* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (value->tag == InteropTag::INTEROP_TAG_UNDEFINED) {
        NavigationModelStatic::SetUsrNavigationMode(frameNode, NavigationMode::AUTO);
        return;
    }
    auto navigationMode = static_cast<NavigationMode>(value->value);
    NavigationModelStatic::SetUsrNavigationMode(frameNode, navigationMode);
}
void BackButtonIcon0Impl(Ark_NativePointer node, const Opt_Union_String_PixelMap_Resource_SymbolGlyphModifier* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    std::string src;
    std::string bundleName;
    std::string moduleName;
    std::vector<std::string> nameList;
    NG::ImageOption imageOption;
    std::function<void(WeakPtr<NG::FrameNode>)> iconSymbol = nullptr;
    RefPtr<PixelMap> pixMap = nullptr;
    bool isValidImage = false;
    if (value->tag != InteropTag::INTEROP_TAG_UNDEFINED) {
        auto valueType = Converter::Convert<int32_t>(value->value.selector);
        const uint32_t stringType = 0;
        const uint32_t pixelType = 1;
        const uint32_t resourceType = 2;
        const uint32_t symbolType = 3;
        switch (valueType) {
            case stringType: {
                src = Converter::Convert<std::string>(value->value.value0);
                imageOption.noPixMap = true;
                imageOption.isValidImage = true;
                break;
            }
            case pixelType: {
                pixMap = Converter::OptConvert<RefPtr<PixelMap>>(value->value.value1).value_or(nullptr);
                break;
            }
            case resourceType: {
                Converter::ResourceConverter converter(value->value.value2);
                src = converter.ToString().value_or("");
                imageOption.noPixMap = true;
                imageOption.isValidImage = true;
                break;
            }
            case symbolType: {
                break;
            }
            default:
                break;
        }
    }
    nameList.emplace_back(bundleName);
    nameList.emplace_back(moduleName);
    NavigationModelStatic::SetBackButtonIcon(frameNode, iconSymbol, src, imageOption, pixMap, nameList);
}
void BackButtonIcon1Impl(Ark_NativePointer node,
                         const Opt_Union_String_PixelMap_Resource_SymbolGlyphModifier* icon,
                         const Opt_ResourceStr* accessibilityText)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(icon);
    CHECK_NULL_VOID(accessibilityText);
    std::string src;
    std::string bundleName;
    std::string moduleName;
    std::vector<std::string> nameList;
    NG::ImageOption imageOption;
    std::function<void(WeakPtr<NG::FrameNode>)> iconSymbol = nullptr;
    RefPtr<PixelMap> pixMap = nullptr;
    bool isValidImage = false;
    std::string backButtonAccessibilityText;
    if (icon->tag != InteropTag::INTEROP_TAG_UNDEFINED) {
        auto valueType = Converter::Convert<int32_t>(icon->value.selector);
        const uint32_t stringType = 0;
        const uint32_t pixelType = 1;
        const uint32_t resourceType = 2;
        const uint32_t symbolType = 3;
        switch (valueType) {
            case stringType: {
                src = Converter::Convert<std::string>(icon->value.value0);
                imageOption.noPixMap = true;
                imageOption.isValidImage = true;
                break;
            }
            case pixelType: {
                pixMap = Converter::OptConvert<RefPtr<PixelMap>>(icon->value.value1).value_or(nullptr);
                break;
            }
            case resourceType: {
                Converter::ResourceConverter converter(icon->value.value2);
                src = converter.ToString().value_or("");
                imageOption.noPixMap = true;
                imageOption.isValidImage = true;
                break;
            }
            case symbolType: {
                break;
            }
            default:
                break;
        }
    }
    if (accessibilityText->tag != InteropTag::INTEROP_TAG_UNDEFINED) {
        auto accessType = Converter::Convert<int32_t>(accessibilityText->value.selector);
        if (accessType == 0) {
            backButtonAccessibilityText = Converter::Convert<std::string>(accessibilityText->value.value0);
        } else if (accessType == 1) {
            Converter::ResourceConverter converter(accessibilityText->value.value1);
            backButtonAccessibilityText = converter.ToString().value_or("");
        }
    }
    nameList.emplace_back(bundleName);
    nameList.emplace_back(moduleName);
    NavigationModelStatic::SetBackButtonIcon(
        frameNode, iconSymbol, src, imageOption, pixMap, nameList, true, backButtonAccessibilityText);
}
void HideNavBarImpl(Ark_NativePointer node,
                    const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto isHide = Converter::OptConvert<bool>(*value).value_or(false);
    NavigationModelStatic::SetHideNavBar(frameNode, isHide);
}
void SubTitleImpl(Ark_NativePointer node, const Opt_String* value) {}
void HideTitleBar0Impl(Ark_NativePointer node, const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto hide = false;
    if (value->tag != InteropTag::INTEROP_TAG_UNDEFINED) {
        hide = Converter::OptConvert<bool>(*value).value_or(false);
    }
    NavigationModelStatic::SetHideTitleBar(frameNode, hide, false);
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
    NavigationModelStatic::SetHideTitleBar(frameNode, isHide, isAnimated);
}
void HideBackButtonImpl(Ark_NativePointer node, const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto isHide = false;
    if (value->tag != InteropTag::INTEROP_TAG_UNDEFINED) {
        isHide = Converter::OptConvert<bool>(*value).value_or(false);
    }
    NavigationModelStatic::SetHideBackButton(frameNode, isHide);
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
    NavigationModelStatic::SetTitleMode(frameNode, titleMode);
}
void Menus0Impl(Ark_NativePointer node, const Opt_Union_Array_NavigationMenuItem_CustomBuilder* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    NG::NavigationMenuOptions options;
    if (value->tag != InteropTag::INTEROP_TAG_UNDEFINED) {
        auto typeValue = value->value.selector;
        if (typeValue == 0) {
            auto menuItemArray = Converter::Convert<std::vector<NG::BarItem>>(value->value.value0);
            NavigationModelStatic::SetMenuItems(frameNode, std::move(menuItemArray));
        } else if (typeValue == 1) {
            CallbackHelper(value->value.value1).BuildAsync([frameNode](const RefPtr<UINode>& uiNode) {
                NavigationModelStatic::SetCustomMenu(frameNode, std::move(uiNode));
            }, node);
        }
    }
    NavigationModelStatic::SetMenuOptions(frameNode, std::move(options));
}
void Menus1Impl(Ark_NativePointer node,
                const Opt_Union_Array_NavigationMenuItem_CustomBuilder* items,
                const Opt_NavigationMenuOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(items);
    CHECK_NULL_VOID(options);
    NG::NavigationMenuOptions menuOptions;
    if (items->tag != InteropTag::INTEROP_TAG_UNDEFINED) {
        auto typeValue = items->value.selector;
        if (typeValue == 0) {
            auto menuItemArray = Converter::Convert<std::vector<NG::BarItem>>(items->value.value0);
            NavigationModelStatic::SetMenuItems(frameNode, std::move(menuItemArray));
        } else if (typeValue == 1) {
            CallbackHelper(items->value.value1).BuildAsync([frameNode](const RefPtr<UINode>& uiNode) {
                NavigationModelStatic::SetCustomMenu(frameNode, std::move(uiNode));
            }, node);
        }
    }
    if (options->tag != InteropTag::INTEROP_TAG_UNDEFINED &&
        options->value.moreButtonOptions.tag != InteropTag::INTEROP_TAG_UNDEFINED) {
        NG::NavigationBackgroundOptions bgOptions =
            Converter::Convert<NG::NavigationBackgroundOptions>(options->value.moreButtonOptions.value);
        menuOptions.mbOptions.bgOptions = bgOptions;
    }
    NavigationModelStatic::SetMenuOptions(frameNode, std::move(menuOptions));
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
    NavigationModelStatic::SetHideToolBar(frameNode, isHide, false);
}
void HideToolBar1Impl(Ark_NativePointer node, const Opt_Boolean* hide, const Opt_Boolean* animated)
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
    NavigationModelStatic::SetHideToolBar(frameNode, isHide, isAnimated);
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
void OnNavBarStateChangeImpl(Ark_NativePointer node, const Opt_Callback_Boolean_Void* value)
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
void NavDestinationImpl(Ark_NativePointer node, const Opt_Callback_String_Opt_Object_Void* value) {}
void CustomNavContentTransitionImpl(
    Ark_NativePointer node, const Opt_Type_NavigationAttribute_customNavContentTransition_delegate* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (value->tag == InteropTag::INTEROP_TAG_UNDEFINED) {
        NavigationModelStatic::SetIsCustomAnimation(frameNode, false);
        return;
    }
    auto onNavigationAnimation = [callback = CallbackHelper(value->value)](RefPtr<NG::NavDestinationContext> from,
        RefPtr<NG::NavDestinationContext> to, NG::NavigationOperation operation) -> NG::NavigationTransition {
        NG::NavigationTransition transition;
        transition.isValid = false;
        auto fromContext = Converter::ArkValue<Ark_NavContentInfo>(from);
        auto toContext = Converter::ArkValue<Ark_NavContentInfo>(to);
        auto navOperation = static_cast<Ark_NavigationOperation>(operation);
        auto resultOpt = callback.InvokeWithOptConvertResult<NG::NavigationTransition, Opt_NavigationAnimatedTransition, Callback_Opt_NavigationAnimatedTransition_Void>(fromContext, toContext, navOperation);
        return resultOpt.value_or(transition);
    };
    NavigationModelStatic::SetIsCustomAnimation(frameNode, true);
    NavigationModelStatic::SetCustomTransition(frameNode, std::move(onNavigationAnimation));
}
void SystemBarStyleImpl(Ark_NativePointer node, const Opt_SystemBarStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    if (value->tag == InteropTag::INTEROP_TAG_UNDEFINED) {
        return;
    }
    auto contentColor = Converter::Convert<Color>(value->value.statusBarContentColor.value);
    NavigationModelStatic::SetSystemBarStyle(frameNode, contentColor);
}
void RecoverableImpl(Ark_NativePointer node, const Opt_Boolean* value) {}
void EnableDragBarImpl(Ark_NativePointer node, const Opt_Boolean* value) {}
void EnableModeChangeAnimationImpl(Ark_NativePointer node, const Opt_Boolean* value) {}
void TitleImpl(Ark_NativePointer node, const Opt_Type_NavigationAttribute_title_value* value,
    const Opt_NavigationTitleOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NavigationTitlebarOptions titleOptions;
    if (options->tag != InteropTag::INTEROP_TAG_UNDEFINED) {
        titleOptions = Converter::OptConvert<NavigationTitlebarOptions>(options->value).value_or(titleOptions);
    }
    NavigationModelStatic::SetTitlebarOptions(frameNode, std::move(titleOptions));
    NavigationTitleInfo info;
    if (value->tag == InteropTag::INTEROP_TAG_UNDEFINED) {
        info.hasMainTitle = true;
        info.hasSubTitle = false;
        info.title = "";
        info.subtitle = "";
        NavigationModelStatic::ParseCommonTitle(frameNode, info);
        return;
    }
    auto selector = Converter::Convert<int32_t>(value->value.selector);
    const int8_t mainSelector = 0;
    if (selector == mainSelector) {
        info.title = Converter::OptConvert<std::string>(value->value.value0).value_or("");
        info.hasMainTitle = true;
        info.hasSubTitle = false;
        NavigationModelStatic::ParseCommonTitle(frameNode, info);
        return;
    }
    const int8_t customTitleSelector = 1;
    if (selector == customTitleSelector) {
        CallbackHelper(value->value.value1)
            .BuildAsync(
                [frameNode](const RefPtr<UINode>& uiNode) {
                    CalcDimension titleHeight;
                    NavigationModelStatic::SetTitleHeight(frameNode, titleHeight, false);
                    NavigationModelStatic::SetCustomTitle(frameNode, uiNode);
                },
                node);
        return;
    }
    const int8_t commonTitleSelector = 2;
    if (selector == commonTitleSelector) {
        info.title = Converter::OptConvert<std::string>(value->value.value2.main).value_or("");
        info.subtitle = Converter::OptConvert<std::string>(value->value.value2.sub).value_or("");
        info.hasSubTitle = true;
        info.hasMainTitle = true;
        NavigationModelStatic::ParseCommonTitle(frameNode, info);
    }
    const int8_t navigationCustomTitleSelector = 3;
    if (selector == navigationCustomTitleSelector) {
        auto titleHeightSelector = value->value.value3.height.selector;
        const int8_t titleHeightType = 0;
        const int8_t lengthType = 1;
        if (titleHeightSelector == titleHeightType) {
            auto titleWithSub = static_cast<uint32_t>(value->value.value3.height.value0);
            if (titleWithSub == 0) {
                NavigationModelStatic::SetTitleHeight(frameNode, NG::SINGLE_LINE_TITLEBAR_HEIGHT);
            } else if (titleWithSub == 1) {
                NavigationModelStatic::SetTitleHeight(frameNode, NG::DOUBLE_LINE_TITLEBAR_HEIGHT);
            }
        } else if (titleHeightSelector == lengthType) {
            CalcDimension length = Converter::Convert<CalcDimension>(value->value.value3.height.value1);
            if (length.Value() < 0) {
                NavigationModelStatic::SetTitleHeight(frameNode, Dimension());
            } else {
                NavigationModelStatic::SetTitleHeight(frameNode, length);
            }
        }
        CallbackHelper(value->value.value3.builder)
            .BuildAsync(
                [frameNode](const RefPtr<UINode>& uiNode) { NavigationModelStatic::SetCustomTitle(frameNode, uiNode); },
                node);
    }
}
void ToolbarConfigurationImpl(Ark_NativePointer node,
                              const Opt_Union_Array_ToolbarItem_CustomBuilder* items,
                              const Opt_NavigationToolbarOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(items);
    NG::NavigationToolbarOptions toolbarOptions;
    if (items->tag != InteropTag::INTEROP_TAG_UNDEFINED) {
        auto typeValue = items->value.selector;
        if (typeValue == 0) {
            NG::MoreButtonOptions toolbarMoreButtonOptions;
            if (options->tag != InteropTag::INTEROP_TAG_UNDEFINED &&
                options->value.moreButtonOptions.tag != InteropTag::INTEROP_TAG_UNDEFINED) {
                NG::NavigationBackgroundOptions bgOptions =
                    Converter::Convert<NG::NavigationBackgroundOptions>(options->value.moreButtonOptions.value);
                toolbarMoreButtonOptions.bgOptions = bgOptions;
            }
            NavigationModelStatic::SetToolbarMorebuttonOptions(frameNode, std::move(toolbarMoreButtonOptions));
            auto toolbarItemArray = Converter::Convert<std::vector<NG::BarItem>>(items->value.value0);
            NavigationModelStatic::SetToolbarConfiguration(frameNode, std::move(toolbarItemArray));
        } else if (typeValue == 1) {
            CallbackHelper(items->value.value1)
                .BuildAsync(
                    [frameNode](
                        const RefPtr<UINode>& uiNode) { NavigationModelStatic::SetCustomToolBar(frameNode, uiNode); },
                    node);
        }
    }

    if (options->tag != InteropTag::INTEROP_TAG_UNDEFINED) {
        NG::NavigationBackgroundOptions bgOptions =
            Converter::Convert<NG::NavigationBackgroundOptions>(options->value);
        toolbarOptions.bgOptions = bgOptions;
    }
    if (options->tag != InteropTag::INTEROP_TAG_UNDEFINED) {
        NG::NavigationBarOptions brOptions =
            Converter::Convert<NG::NavigationBarOptions>(options->value);
        toolbarOptions.brOptions = brOptions;
    }
    NavigationModelStatic::SetToolbarOptions(frameNode, std::move(toolbarOptions));
}
void IgnoreLayoutSafeAreaImpl(Ark_NativePointer node,
                              const Opt_Array_LayoutSafeAreaType* types,
                              const Opt_Array_LayoutSafeAreaEdge* edges)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NG::IgnoreLayoutSafeAreaOpts opts { .type = NG::SAFE_AREA_TYPE_SYSTEM, .edges = NG::SAFE_AREA_EDGE_ALL };
    if (types->tag != InteropTag::INTEROP_TAG_UNDEFINED) {
        auto typeRawArray = Converter::Convert<std::vector<uint32_t>>(types->value);
        uint32_t safeAreaType = NG::SAFE_AREA_TYPE_NONE;
        for (auto typeValue : typeRawArray) {
            if (typeValue >= SAFE_AREA_TYPE_LIMIT || typeValue == SAFE_AREA_EDGE_SYSTEM) {
                safeAreaType = NG::SAFE_AREA_TYPE_SYSTEM;
                break;
            }
        }
        opts.type = safeAreaType;
    }
    if (edges->tag != InteropTag::INTEROP_TAG_UNDEFINED) {
        auto edgeRawArray = Converter::Convert<std::vector<uint32_t>>(edges->value);
        uint32_t safeAreaEdge = NG::SAFE_AREA_EDGE_NONE;
        for (auto edgeValue : edgeRawArray) {
            if (edgeValue >= SAFE_AREA_EDGE_LIMIT) {
                safeAreaEdge = NG::SAFE_AREA_EDGE_ALL;
                break;
            }
            if (edgeValue == SAFE_AREA_EDGE_TOP || edgeValue == SAFE_AREA_EDGE_BOTTOM) {
                safeAreaEdge |= (1 << edgeValue);
            }
        }
        opts.edges = safeAreaEdge;
    }
    NavigationModelStatic::SetIgnoreLayoutSafeArea(frameNode, opts);
}
} // namespace NavigationAttributeModifier
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

} // namespace OHOS::Ace::NG::GeneratedModifier
