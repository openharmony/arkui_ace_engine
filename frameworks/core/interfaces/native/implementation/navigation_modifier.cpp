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
#include "core/components_ng/pattern/navigation/navigation_model_ng.h"
#include "core/components_ng/pattern/navigation/navigation_pattern.h"
#include "core/components_ng/pattern/navigation/navigation_transition_proxy.h"
#include "core/interfaces/native/implementation/nav_path_stack_peer_impl.h"
#include "core/interfaces/native/implementation/symbol_glyph_modifier_peer.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace {
constexpr uint32_t SAFE_AREA_TYPE_LIMIT = 3;
constexpr uint32_t SAFE_AREA_EDGE_LIMIT = 4;
constexpr uint32_t SAFE_AREA_EDGE_SYSTEM = 0;
constexpr uint32_t SAFE_AREA_EDGE_TOP = 0;
constexpr uint32_t SAFE_AREA_EDGE_BOTTOM = 1;
constexpr uint32_t INVALID_VALUE = 0;
constexpr uint32_t DEFAULT_NAV_BAR_WIDTH = 240;

std::optional<Dimension> ProcessBindableNavBarWidth(FrameNode* frameNode, const Opt_Union_Length_Bindable* value)
{
    std::optional<Dimension> result;
    Converter::VisitUnionPtr(value,
        [&result](const Ark_Length& src) {
            result = Converter::OptConvert<Dimension>(src);
        },
        [&result, frameNode](const Ark_Bindable_Arkui_Component_Units_Length& src) {
            result = Converter::OptConvert<Dimension>(src.value);
            // Need to provide callback
        },
        [] {});
    return result;
}
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
void SetNavigationOptionsImpl(Ark_NativePointer node,
                              const Opt_NavPathStack* pathInfos,
                              const Opt_NavigationModuleInfo* moduleInfo)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(pathInfos);
    auto navigationPattern = frameNode->GetPattern<NavigationPattern>();
    CHECK_NULL_VOID(navigationPattern);
    auto pathStack = pathInfos->value;
    CHECK_NULL_VOID(pathStack);
    auto navigationStack = pathStack->GetNavPathStack();
    navigationPattern->SetNavigationStack(navigationStack, false);
    // update path stack need to sync stack immediately
    navigationStack->InvokeOnStateChanged();
}
} // namespace NavigationInterfaceModifier

namespace NavigationAttributeModifier {
void SetNavBarWidthImpl(Ark_NativePointer node,
                        const Opt_Union_Length_Bindable* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    Dimension def(DEFAULT_NAV_BAR_WIDTH, DimensionUnit::VP);
    auto result = ProcessBindableNavBarWidth(frameNode, value);
    if (!result) {
        NavigationModelStatic::SetNavBarWidth(frameNode, def);
        return;
    }
    auto resultVal = result->Value();
    if (resultVal <= INVALID_VALUE) {
        NavigationModelStatic::SetNavBarWidth(frameNode, def);
        return;
    }
    NavigationModelStatic::SetNavBarWidth(frameNode, *result);
}
void SetNavBarPositionImpl(Ark_NativePointer node,
                           const Opt_NavBarPosition* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
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
void SetNavBarWidthRangeImpl(Ark_NativePointer node,
                             const Opt_Tuple_Dimension_Dimension* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    if (value->tag == InteropTag::INTEROP_TAG_UNDEFINED) {
        NavigationModelStatic::SetMinNavBarWidth(frameNode, NG::DEFAULT_MIN_NAV_BAR_WIDTH);
        NavigationModelStatic::SetMaxNavBarWidth(frameNode, NG::DEFAULT_MAX_NAV_BAR_WIDTH);
        return;
    }
    auto min = Converter::OptConvert<CalcDimension>(value->value.value0).value_or(Dimension());
    auto max = Converter::OptConvert<CalcDimension>(value->value.value1).value_or(Dimension());

    if (LessNotEqual(min.Value(), 0.0)) {
        min.SetValue(0);
    }
    NavigationModelStatic::SetMinNavBarWidth(frameNode, min);
    if (LessNotEqual(max.Value(), 0.0)) {
        max.SetValue(0);
    }
    NavigationModelStatic::SetMaxNavBarWidth(frameNode, max);
}
void SetMinContentWidthImpl(Ark_NativePointer node,
                            const Opt_Dimension* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<CalcDimension>(value);
    if (!convValue) {
        NavigationModelStatic::SetMinContentWidth(frameNode, DEFAULT_MIN_CONTENT_WIDTH);
        return;
    }
    auto mincontent = *convValue;

    if (LessNotEqual(mincontent.Value(), 0.0)) {
        mincontent = DEFAULT_MIN_CONTENT_WIDTH;
    }

    NavigationModelStatic::SetMinContentWidth(frameNode, mincontent);
}
void SetModeImpl(Ark_NativePointer node,
                 const Opt_NavigationMode* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        NavigationModelStatic::SetUsrNavigationMode(frameNode, NavigationMode::AUTO);
        return;
    }
    auto navigationMode = static_cast<NavigationMode>(*optValue);
    NavigationModelStatic::SetUsrNavigationMode(frameNode, navigationMode);
}
void SetHideNavBarImpl(Ark_NativePointer node,
                       const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto isHide = Converter::OptConvertPtr<bool>(value).value_or(false);
    NavigationModelStatic::SetHideNavBar(frameNode, isHide);
}
void SetHideTitleBar0Impl(Ark_NativePointer node,
                          const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto hide = Converter::OptConvertPtr<bool>(value).value_or(false);
    NavigationModelStatic::SetHideTitleBar(frameNode, hide, false);
}
void SetHideBackButtonImpl(Ark_NativePointer node,
                           const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto isHide = Converter::OptConvertPtr<bool>(value).value_or(false);
    NavigationModelStatic::SetHideBackButton(frameNode, isHide);
}
void SetTitleModeImpl(Ark_NativePointer node,
                      const Opt_NavigationTitleMode* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    NavigationTitleMode titleMode = NavigationTitleMode::FREE;
    if (value->tag != InteropTag::INTEROP_TAG_UNDEFINED) {
        titleMode = static_cast<NavigationTitleMode>(value->value);
    }
    NavigationModelStatic::SetTitleMode(frameNode, titleMode);
}
void SetHideToolBar0Impl(Ark_NativePointer node,
                         const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto isHide = Converter::OptConvertPtr<bool>(value).value_or(false);
    NavigationModelStatic::SetHideToolBar(frameNode, isHide, false);
}
void SetEnableToolBarAdaptationImpl(Ark_NativePointer node,
                                    const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NavigationModelStatic::SetEnableToolBarAdaptation(frameNode, Converter::OptConvertPtr<bool>(value).value_or(true));
}
void SetOnTitleModeChangeImpl(Ark_NativePointer node,
                              const Opt_Callback_NavigationTitleMode_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        auto eventHub = frameNode->GetEventHub<NavigationEventHub>();
        CHECK_NULL_VOID(eventHub);
        eventHub->SetOnTitleModeChange(nullptr);
        return;
    }
    auto titleChange = [titleCallback = CallbackHelper(*optValue)](NavigationTitleMode titleMode) {
        Ark_NavigationTitleMode mode = static_cast<Ark_NavigationTitleMode>(titleMode);
        titleCallback.InvokeSync(mode);
    };
    auto eventChange = [eventChange = CallbackHelper(*optValue)](const BaseEventInfo* info) {
        auto eventInfo = TypeInfoHelper::DynamicCast<NavigationTitleModeChangeEvent>(info);
        if (!eventInfo) {
            return;
        }
        Ark_NavigationTitleMode titleMode = Ark_NavigationTitleMode::ARK_NAVIGATION_TITLE_MODE_FREE;
        if (eventInfo->IsMiniBar()) {
            titleMode = Ark_NavigationTitleMode::ARK_NAVIGATION_TITLE_MODE_MINI;
        }
        eventChange.InvokeSync(titleMode);
    };
    auto eventHub = frameNode->GetEventHub<NavigationEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnTitleModeChange(eventChange);
}
void SetOnNavBarStateChangeImpl(Ark_NativePointer node,
                                const Opt_Callback_Boolean_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    auto eventHub = frameNode->GetEventHub<NavigationEventHub>();
    CHECK_NULL_VOID(eventHub);
    if (!optValue) {
        eventHub->SetOnNavBarStateChange(nullptr);
        return;
    }
    auto stateCallback = [changeCallback = CallbackHelper(*optValue)](bool isVisible) {
        auto visible = Converter::ArkValue<Ark_Boolean>(isVisible);
        changeCallback.InvokeSync(visible);
    };
    eventHub->SetOnNavBarStateChange(stateCallback);
}
void SetOnNavigationModeChangeImpl(Ark_NativePointer node,
                                   const Opt_Callback_NavigationMode_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // Implement Reset value
        return;
    }
    auto modeCallback = [changeCallback = CallbackHelper(*optValue)](NavigationMode mode) {
        auto navigationMode = Converter::ArkValue<Ark_NavigationMode>(mode);
        changeCallback.InvokeSync(navigationMode);
    };
    auto eventHub = frameNode->GetEventHub<NavigationEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnNavigationModeChange(modeCallback);
}
void SetNavDestinationImpl(Ark_NativePointer node,
                           const Opt_PageMapBuilder* value)
{
}
void SetCustomNavContentTransitionImpl(Ark_NativePointer node,
                                       const Opt_Type_NavigationAttribute_customNavContentTransition* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        NavigationModelStatic::SetIsCustomAnimation(frameNode, false);
        NavigationModelStatic::SetCustomTransition(frameNode, nullptr);
        return;
    }
    auto onNavigationAnimation = [callback = CallbackHelper(*optValue)](RefPtr<NG::NavDestinationContext> from,
        RefPtr<NG::NavDestinationContext> to, NG::NavigationOperation operation) -> NG::NavigationTransition {
        NG::NavigationTransition transition;
        transition.isValid = false;
        auto fromContext = Converter::ArkValue<Ark_NavContentInfo>(from);
        auto toContext = Converter::ArkValue<Ark_NavContentInfo>(to);
        auto navOperation = static_cast<Ark_NavigationOperation>(operation);
        auto resultOpt = callback.InvokeWithOptConvertResult<NG::NavigationTransition, Opt_NavigationAnimatedTransition,
            Callback_Opt_NavigationAnimatedTransition_Void>(fromContext, toContext, navOperation);
        return resultOpt.value_or(transition);
    };
    NavigationModelStatic::SetIsCustomAnimation(frameNode, true);
    NavigationModelStatic::SetCustomTransition(frameNode, std::move(onNavigationAnimation));
}
void SetSystemBarStyleImpl(Ark_NativePointer node,
                           const Opt_window_SystemBarStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    auto contentColor = optValue ? Converter::OptConvert<Color>(optValue->statusBarContentColor): std::nullopt;
    if (!contentColor) {
        // Implement Reset value
        return;
    }
    NavigationModelStatic::SetSystemBarStyle(frameNode, *contentColor);
}
void SetRecoverableImpl(Ark_NativePointer node,
                        const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    NavigationModelStatic::SetRecoverable(frameNode, Converter::OptConvertPtr<bool>(value).value_or(false));
}
void SetEnableDragBarImpl(Ark_NativePointer node,
                          const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    NavigationModelStatic::SetEnableDragBar(frameNode, Converter::OptConvertPtr<bool>(value).value_or(false));
}
void SetEnableModeChangeAnimationImpl(Ark_NativePointer node,
                                      const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    NavigationModelStatic::SetEnableModeChangeAnimation(frameNode,
        Converter::OptConvertPtr<bool>(value).value_or(true));
}
void SetBackButtonIconImpl(Ark_NativePointer node,
                            const Opt_Union_String_PixelMap_Resource_SymbolGlyphModifier* icon,
                            const Opt_ResourceStr* accessibilityText)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
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
        const int32_t stringType = 0;
        const int32_t pixelType = 1;
        const int32_t resourceType = 2;
        const int32_t symbolType = 3;
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
                iconSymbol = icon->value.value3->symbolApply;
                PeerUtils::DestroyPeer(icon->value.value3);
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
void SetTitleImpl(Ark_NativePointer node,
                  const Opt_Union_ResourceStr_CustomBuilder_NavigationCommonTitle_NavigationCustomTitle* value,
                  const Opt_NavigationTitleOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    CHECK_NULL_VOID(options);
    NavigationTitlebarOptions titleOptions;
    if (options->tag != InteropTag::INTEROP_TAG_UNDEFINED) {
        auto pipelineContext = frameNode->GetContext();
        CHECK_NULL_VOID(pipelineContext);
        auto theme = pipelineContext->GetTheme<NavigationBarTheme>();
        CHECK_NULL_VOID(theme);
        auto blurStyle = static_cast<BlurStyle>(theme->GetTitlebarBackgroundBlurStyle());
        if (blurStyle != BlurStyle::NO_MATERIAL) {
            BlurStyleOption blurStyleOption;
            blurStyleOption.blurStyle = blurStyle;
            titleOptions.bgOptions.blurStyleOption = blurStyleOption;
            titleOptions.bgOptions.color = Color::TRANSPARENT;
        }
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
            CalcDimension length = Converter::OptConvert<CalcDimension>(value->value.value3.height.value1)
                .value_or(Dimension());
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
void SetHideTitleBar1Impl(Ark_NativePointer node,
                          const Opt_Boolean* hide,
                          const Opt_Boolean* animated)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto isHide = Converter::OptConvertPtr<bool>(hide).value_or(false);
    auto isAnimated = Converter::OptConvertPtr<bool>(animated).value_or(false);
    NavigationModelStatic::SetHideTitleBar(frameNode, isHide, isAnimated);
}
void SetMenusImpl(Ark_NativePointer node,
                   const Opt_Union_Array_NavigationMenuItem_CustomBuilder* items,
                   const Opt_NavigationMenuOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
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
    } else {
        std::vector<NG::BarItem> emptyVector;
        NavigationModelStatic::SetMenuItems(frameNode, std::move(emptyVector));
    }
    if (options->tag != InteropTag::INTEROP_TAG_UNDEFINED &&
        options->value.moreButtonOptions.tag != InteropTag::INTEROP_TAG_UNDEFINED) {
        NG::NavigationBackgroundOptions bgOptions =
            Converter::Convert<NG::NavigationBackgroundOptions>(options->value.moreButtonOptions.value);
        menuOptions.mbOptions.bgOptions = bgOptions;
    }
    NavigationModelStatic::SetMenuOptions(frameNode, std::move(menuOptions));
}
void SetToolbarConfigurationImpl(Ark_NativePointer node,
                                 const Opt_Union_Array_ToolbarItem_CustomBuilder* value,
                                 const Opt_NavigationToolbarOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    CHECK_NULL_VOID(options);
    if (options->tag != InteropTag::INTEROP_TAG_UNDEFINED) {
        auto isHideItemText = Converter::OptConvert<bool>(options->value.hideItemValue).value_or(false);
        NavigationModelStatic::SetHideItemText(frameNode, isHideItemText);
    } else {
        NavigationModelStatic::SetHideItemText(frameNode, false);
    }
    NG::NavigationToolbarOptions toolbarOptions;
    if (value->tag != InteropTag::INTEROP_TAG_UNDEFINED) {
        auto typeValue = value->value.selector;
        if (typeValue == 0) {
            NG::MoreButtonOptions toolbarMoreButtonOptions;
            if (options->tag != InteropTag::INTEROP_TAG_UNDEFINED &&
                options->value.moreButtonOptions.tag != InteropTag::INTEROP_TAG_UNDEFINED) {
                NG::NavigationBackgroundOptions bgOptions =
                    Converter::Convert<NG::NavigationBackgroundOptions>(options->value.moreButtonOptions.value);
                toolbarMoreButtonOptions.bgOptions = bgOptions;
            }
            NavigationModelStatic::SetToolbarMorebuttonOptions(frameNode, std::move(toolbarMoreButtonOptions));
            auto toolbarItemArray = Converter::Convert<std::vector<NG::BarItem>>(value->value.value0);
            NavigationModelStatic::SetToolbarConfiguration(frameNode, std::move(toolbarItemArray));
        } else if (typeValue == 1) {
            CallbackHelper(value->value.value1)
                .BuildAsync(
                    [frameNode](
                        const RefPtr<UINode>& uiNode) { NavigationModelStatic::SetCustomToolBar(frameNode, uiNode); },
                    node);
        }
    } else {
        NavigationModelStatic::SetToolbarMorebuttonOptions(frameNode, NG::MoreButtonOptions());
        NavigationModelStatic::SetToolbarConfiguration(frameNode, std::vector<NG::BarItem>());
        NavigationModelStatic::SetCustomToolBar(frameNode, nullptr);
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
void SetHideToolBar1Impl(Ark_NativePointer node,
                         const Opt_Boolean* hide,
                         const Opt_Boolean* animated)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto isHide = Converter::OptConvertPtr<bool>(hide).value_or(false);
    auto isAnimated = Converter::OptConvertPtr<bool>(animated).value_or(false);
    NavigationModelStatic::SetHideToolBar(frameNode, isHide, isAnimated);
}
void SetIgnoreLayoutSafeAreaImpl(Ark_NativePointer node,
                                 const Opt_Array_LayoutSafeAreaType* types,
                                 const Opt_Array_LayoutSafeAreaEdge* edges)
{
    constexpr int32_t LAYOUT_SAFE_AREA_TYPE_LIMIT = 2;
    constexpr int32_t LAYOUT_SAFE_AREA_EDGE_LIMIT = 6;
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(types);
    CHECK_NULL_VOID(edges);
    NG::IgnoreLayoutSafeAreaOpts opts {
        .type = NG::LAYOUT_SAFE_AREA_TYPE_SYSTEM,
        .rawEdges = NG::LAYOUT_SAFE_AREA_EDGE_ALL
    };
    if (types->tag != InteropTag::INTEROP_TAG_UNDEFINED) {
        auto typeRawArray = Converter::Convert<std::vector<uint32_t>>(types->value);
        uint32_t safeAreaType = NG::LAYOUT_SAFE_AREA_TYPE_NONE;
        for (auto typeValue : typeRawArray) {
            if (typeValue > LAYOUT_SAFE_AREA_TYPE_LIMIT) {
                safeAreaType = NG::SAFE_AREA_TYPE_SYSTEM;
                break;
            }
            safeAreaType |= (1 << safeAreaType);
        }
        opts.type = safeAreaType;
    }
    if (edges->tag != InteropTag::INTEROP_TAG_UNDEFINED) {
        auto edgeRawArray = Converter::Convert<std::vector<uint32_t>>(edges->value);
        uint32_t safeAreaEdge = NG::SAFE_AREA_EDGE_NONE;
        for (auto edgeValue : edgeRawArray) {
            if (edgeValue >= LAYOUT_SAFE_AREA_EDGE_LIMIT) {
                safeAreaEdge = NG::LAYOUT_SAFE_AREA_EDGE_ALL;
                break;
            }
            if (edgeValue == SAFE_AREA_EDGE_TOP || edgeValue == SAFE_AREA_EDGE_BOTTOM) {
                safeAreaEdge |= (1 << edgeValue);
            }
        }
        opts.rawEdges = safeAreaEdge;
    }
    NavigationModelStatic::SetIgnoreLayoutSafeArea(frameNode, opts);
}

void SetDividerImpl(Ark_NativePointer node, const Opt_NavigationDividerStyle* style)
{
    CHECK_NULL_VOID(style);
    auto frameNode = reinterpret_cast<NavigationGroupNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (style->tag == InteropTag::INTEROP_TAG_UNDEFINED) {
        NavigationModelNG::UpdateDividerVisibility(frameNode, false);
        return;
    }
    NavigationModelNG::UpdateDividerVisibility(frameNode, true);
    auto color = Converter::OptConvert<Color>(style->value.color);
    if (color.has_value()) {
        NavigationModelStatic::UpdateDefineColor(frameNode, true);
        NavigationModelNG::UpdateDividerColor(frameNode, color.value_or(Color()), nullptr);
    } else {
        NavigationModelStatic::UpdateDefineColor(frameNode, false);
    }
    auto startMargin = Converter::OptConvert<CalcDimension>(style->value.startMargin).value_or(Dimension(0.0f));
    NavigationModelNG::UpdateDividerStartMargin(frameNode, startMargin, nullptr);
    auto endMargin = Converter::OptConvert<CalcDimension>(style->value.endMargin).value_or(Dimension(0.0f));
    NavigationModelNG::UpdateDividerEndMargin(frameNode, endMargin, nullptr);
}
} // namespace NavigationAttributeModifier

const GENERATED_ArkUINavigationModifier* GetNavigationModifier()
{
    static const GENERATED_ArkUINavigationModifier ArkUINavigationModifierImpl {
        NavigationModifier::ConstructImpl,
        NavigationInterfaceModifier::SetNavigationOptionsImpl,
        NavigationAttributeModifier::SetNavBarWidthImpl,
        NavigationAttributeModifier::SetNavBarPositionImpl,
        NavigationAttributeModifier::SetNavBarWidthRangeImpl,
        NavigationAttributeModifier::SetMinContentWidthImpl,
        NavigationAttributeModifier::SetModeImpl,
        NavigationAttributeModifier::SetHideNavBarImpl,
        NavigationAttributeModifier::SetHideTitleBar0Impl,
        NavigationAttributeModifier::SetHideBackButtonImpl,
        NavigationAttributeModifier::SetTitleModeImpl,
        NavigationAttributeModifier::SetHideToolBar0Impl,
        NavigationAttributeModifier::SetEnableToolBarAdaptationImpl,
        NavigationAttributeModifier::SetOnTitleModeChangeImpl,
        NavigationAttributeModifier::SetOnNavBarStateChangeImpl,
        NavigationAttributeModifier::SetOnNavigationModeChangeImpl,
        NavigationAttributeModifier::SetCustomNavContentTransitionImpl,
        NavigationAttributeModifier::SetSystemBarStyleImpl,
        NavigationAttributeModifier::SetRecoverableImpl,
        NavigationAttributeModifier::SetEnableDragBarImpl,
        NavigationAttributeModifier::SetDividerImpl,
        NavigationAttributeModifier::SetEnableModeChangeAnimationImpl,
        NavigationAttributeModifier::SetBackButtonIconImpl,
        NavigationAttributeModifier::SetTitleImpl,
        NavigationAttributeModifier::SetHideTitleBar1Impl,
        NavigationAttributeModifier::SetMenusImpl,
        NavigationAttributeModifier::SetToolbarConfigurationImpl,
        NavigationAttributeModifier::SetHideToolBar1Impl,
        NavigationAttributeModifier::SetIgnoreLayoutSafeAreaImpl,
    };
    return &ArkUINavigationModifierImpl;
}

} // namespace OHOS::Ace::NG::GeneratedModifier
