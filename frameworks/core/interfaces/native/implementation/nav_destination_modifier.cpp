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
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/pattern/navrouter/navdestination_event_hub.h"
#include "core/components_ng/pattern/navrouter/navdestination_model_static.h"
#include "core/interfaces/native/implementation/symbol_glyph_modifier_peer.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"

#include "nav_destination_scrollable_processor_static.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace {
constexpr uint32_t SAFE_AREA_TYPE_LIMIT = 3;
constexpr uint32_t SAFE_AREA_EDGE_LIMIT = 4;
constexpr uint32_t SAFE_AREA_EDGE_SYSTEM = 0;
constexpr uint32_t SAFE_AREA_EDGE_TOP = 0;
constexpr uint32_t SAFE_AREA_EDGE_BOTTOM = 1;
} // namespace
namespace NavDestinationModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                Ark_Int32 flags)
{
    RefPtr<FrameNode> frameNode = nullptr;
    auto contentCreator = []() {
        // empty content creator to be done
    };
    auto navPathInfo = AceType::MakeRefPtr<NavigationContext::JSNavPathInfoStatic>();
    frameNode = NavDestinationModelStatic::CreateFrameNode(id, navPathInfo, std::move(contentCreator));
    CHECK_NULL_RETURN(frameNode, nullptr);
    frameNode->IncRefCount();
    NavDestinationModelStatic::SetScrollableProcessor(frameNode,
        []() { return AceType::MakeRefPtr<NavDestinationScrollableProcessorStatic>(); });
    return AceType::RawPtr(frameNode);
}
} // namespace NavDestinationModifier
namespace NavDestinationInterfaceModifier {
void SetNavDestinationOptionsImpl(Ark_NativePointer node,
                                  const Opt_NavDestinationModuleInfo* moduleInfo)
{
    // "No need to implement this method"
}
} // namespace NavDestinationInterfaceModifier
namespace NavDestinationAttributeModifier {
void SetHideTitleBar0Impl(Ark_NativePointer node,
                          const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NavDestinationModelStatic::SetHideTitleBar(frameNode, Converter::OptConvertPtr<bool>(value).value_or(false));
}
void SetHideBackButtonImpl(Ark_NativePointer node,
                           const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NavDestinationModelStatic::SetHideBackButton(frameNode, Converter::OptConvertPtr<bool>(value).value_or(false));
}
void SetOnShownImpl(Ark_NativePointer node,
                    const Opt_Callback_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        NavDestinationModelStatic::SetOnShown(frameNode, nullptr);
        return;
    }
    auto onShownEvent = [arkCallback = CallbackHelper(*optValue)](int32_t reason) {
        arkCallback.InvokeSync();
    };
    NavDestinationModelStatic::SetOnShown(frameNode, std::move(onShownEvent));
}
void SetOnHiddenImpl(Ark_NativePointer node,
                     const Opt_Callback_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        NavDestinationModelStatic::SetOnHidden(frameNode, nullptr);
        return;
    }
    auto onHiddenEvent = [arkCallback = CallbackHelper(*optValue)](int32_t reason) { arkCallback.InvokeSync(); };
    NavDestinationModelStatic::SetOnHidden(frameNode, std::move(onHiddenEvent));
}
void SetOnBackPressedImpl(Ark_NativePointer node,
                          const Opt_Callback_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        NavDestinationModelStatic::SetOnBackPressed(frameNode, nullptr);
        return;
    }
    auto onBackPressedEvent = [arkCallback = CallbackHelper(*optValue)]() -> bool {
        return arkCallback.InvokeWithOptConvertResult<bool, Ark_Boolean, Callback_Boolean_Void>().value_or(false);
    };
    NavDestinationModelStatic::SetOnBackPressed(frameNode, std::move(onBackPressedEvent));
}
void SetOnResultImpl(Ark_NativePointer node,
                     const Opt_Callback_Union_Object_Idlize_Stdlib_Null_Undefined_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
}
void SetModeImpl(Ark_NativePointer node,
                 const Opt_NavDestinationMode* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto mode = Converter::OptConvertPtr<NavDestinationMode>(value).value_or(NavDestinationMode::STANDARD);
    NavDestinationModelStatic::SetNavDestinationMode(frameNode, mode);
}
void SetOnReadyImpl(Ark_NativePointer node,
                    const Opt_Callback_NavDestinationContext_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    if (value->tag == InteropTag::INTEROP_TAG_UNDEFINED) {
        NavDestinationModelStatic::SetOnReady(frameNode, nullptr);
        return;
    }
    auto onReady = [readyCallback = CallbackHelper(value->value)](RefPtr<NG::NavDestinationContext> context) {
        Ark_NavDestinationContext arkContext = Converter::ArkValue<Ark_NavDestinationContext>(context);
        readyCallback.InvokeSync(arkContext);
    };
    NavDestinationModelStatic::SetOnReady(frameNode, std::move(onReady));
}
void SetOnWillAppearImpl(Ark_NativePointer node,
                         const Opt_Callback_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        NavDestinationModelStatic::SetOnWillAppear(frameNode, nullptr);
        return;
    }
    auto onWillAppearEvent = [arkCallback = CallbackHelper(*optValue)]() {
        arkCallback.InvokeSync();
    };
    NavDestinationModelStatic::SetOnWillAppear(frameNode, std::move(onWillAppearEvent));
}
void SetOnWillDisappearImpl(Ark_NativePointer node,
                            const Opt_Callback_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        NavDestinationModelStatic::SetOnWillDisAppear(frameNode, nullptr);
        return;
    }
    auto onWillDisappearEvent = [arkCallback = CallbackHelper(*optValue)]() {
        arkCallback.InvokeSync();
    };
    NavDestinationModelStatic::SetOnWillDisAppear(frameNode, std::move(onWillDisappearEvent));
}
void SetOnWillShowImpl(Ark_NativePointer node,
                       const Opt_Callback_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        NavDestinationModelStatic::SetOnWillShow(frameNode, nullptr);
        return;
    }
    auto onWillShowEvent = [arkCallback = CallbackHelper(*optValue)]() {
        arkCallback.InvokeSync();
    };
    NavDestinationModelStatic::SetOnWillShow(frameNode, std::move(onWillShowEvent));
}
void SetOnWillHideImpl(Ark_NativePointer node,
                       const Opt_Callback_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        NavDestinationModelStatic::SetOnWillHide(frameNode, nullptr);
        return;
    }
    auto onWillHideEvent = [arkCallback = CallbackHelper(*optValue)]() {
        arkCallback.InvokeSync();
    };
    NavDestinationModelStatic::SetOnWillHide(frameNode, std::move(onWillHideEvent));
}
void SetSystemBarStyleImpl(Ark_NativePointer node,
                           const Opt_window_SystemBarStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    auto contentColor = optValue ? Converter::OptConvert<Color>(optValue->statusBarContentColor): std::nullopt;
    if (!contentColor) {
        // Implement Reset value
        return;
    }
    NavDestinationModelStatic::SetSystemBarStyle(frameNode, *contentColor);
}
void SetRecoverableImpl(Ark_NativePointer node,
                        const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<bool>(value);
    NavDestinationModelStatic::SetRecoverable(frameNode, convValue);
}
void SetSystemTransitionImpl(Ark_NativePointer node,
                             const Opt_NavigationSystemTransitionType* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    if (value->tag == InteropTag::INTEROP_TAG_UNDEFINED) {
        NavDestinationModelStatic::SetSystemTransitionType(frameNode, NG::NavigationSystemTransitionType::DEFAULT);
        return;
    }

    constexpr int32_t JS_ENUM_TRANSITIONTYPE_NONE = 1;
    constexpr int32_t JS_ENUM_TRANSITIONTYPE_TITLE = 2;
    constexpr int32_t JS_ENUM_TRANSITIONTYPE_CONTENT = 3;
    constexpr int32_t JS_ENUM_TRANSITIONTYPE_FADE = 4;
    constexpr int32_t JS_ENUM_TRANSITIONTYPE_EXPLODE = 5;
    constexpr int32_t JS_ENUM_TRANSITIONTYPE_SLIDE_RIGHT = 6;
    constexpr int32_t JS_ENUM_TRANSITIONTYPE_SLIDE_BOTTOM = 7;

    auto systemTransitionvalue = static_cast<int32_t>(value->value);
    auto res = NG::NavigationSystemTransitionType::DEFAULT;
    switch (systemTransitionvalue) {
        case JS_ENUM_TRANSITIONTYPE_NONE:
             res =NG::NavigationSystemTransitionType::NONE;
             break;
        case JS_ENUM_TRANSITIONTYPE_TITLE:
             res =NG::NavigationSystemTransitionType::TITLE;
             break;
        case JS_ENUM_TRANSITIONTYPE_CONTENT:
             res =NG::NavigationSystemTransitionType::CONTENT;
             break;
        case JS_ENUM_TRANSITIONTYPE_FADE:
             res =NG::NavigationSystemTransitionType::FADE;
             break;
        case JS_ENUM_TRANSITIONTYPE_EXPLODE:
             res =NG::NavigationSystemTransitionType::EXPLODE;
             break;
        case JS_ENUM_TRANSITIONTYPE_SLIDE_RIGHT:
             res =NG::NavigationSystemTransitionType::SLIDE_RIGHT;
             break;
        case JS_ENUM_TRANSITIONTYPE_SLIDE_BOTTOM:
             res =NG::NavigationSystemTransitionType::SLIDE_BOTTOM;
             break;
        default:
             res =NG::NavigationSystemTransitionType::DEFAULT;
             break;
    }

    NavDestinationModelStatic::SetSystemTransitionType(frameNode, res);
}
void SetBindToScrollableImpl(Ark_NativePointer node,
                             const Opt_Array_Scroller* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto bindFunc = [&value](const RefPtr<NG::NavDestinationScrollableProcessor>& processor) {
        auto jsProcessor = AceType::DynamicCast<NavDestinationScrollableProcessorStatic>(processor);
        CHECK_NULL_VOID(jsProcessor);
        jsProcessor->BindToScrollable(value);
    };
    NavDestinationModelStatic::UpdateBindingWithScrollable(frameNode, std::move(bindFunc));
}
void SetBindToNestedScrollableImpl(Ark_NativePointer node,
                                   const Opt_Array_NestedScrollInfo* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto bindFunc = [&value](const RefPtr<NG::NavDestinationScrollableProcessor>& processor) {
        auto jsProcessor = AceType::DynamicCast<NavDestinationScrollableProcessorStatic>(processor);
        CHECK_NULL_VOID(jsProcessor);
        jsProcessor->BindToNestedScrollable(value);
    };
    NavDestinationModelStatic::UpdateBindingWithScrollable(frameNode, std::move(bindFunc));
}
void SetOnActiveImpl(Ark_NativePointer node,
                     const Opt_Callback_NavDestinationActiveReason_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // tbd: Reset value
        return;
    }
    auto onActiveEvent = [arkCallback = CallbackHelper(*optValue)](int32_t activeValue) {
        Ark_NavDestinationActiveReason arkValue = static_cast<Ark_NavDestinationActiveReason>(activeValue);
        arkCallback.InvokeSync(arkValue);
    };
    NavDestinationModelStatic::SetOnActive(frameNode, std::move(onActiveEvent));
}
void SetOnInactiveImpl(Ark_NativePointer node,
                       const Opt_Callback_NavDestinationActiveReason_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // tbd: Reset value
        return;
    }
    auto onInactiveEvent = [arkCallback = CallbackHelper(*optValue)](int32_t inactiveValue) {
        Ark_NavDestinationActiveReason arkValue = static_cast<Ark_NavDestinationActiveReason>(inactiveValue);
        arkCallback.InvokeSync(arkValue);
    };
    NavDestinationModelStatic::SetOnInactive(frameNode, std::move(onInactiveEvent));
}
void SetCustomTransitionImpl(Ark_NativePointer node,
                             const Opt_NavDestinationTransitionDelegate* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    if (value->tag == InteropTag::INTEROP_TAG_UNDEFINED) {
        NavDestinationModelStatic::SetCustomTransition(frameNode, nullptr);
        return;
    }
    auto onNavigationAnimation = [callback = CallbackHelper(value->value)](NG::NavigationOperation operation,
        bool isEnter)-> std::optional<std::vector<NG::NavDestinationTransition>> {
        std::vector<NG::NavDestinationTransition> allTransitions;
        auto navOperation = static_cast<Ark_NavigationOperation>(operation);
        auto arkIsEnter = Converter::ArkValue<Ark_Boolean>(isEnter);
        auto resultOpt = callback.InvokeWithOptConvertResult<std::optional<std::vector<NG::NavDestinationTransition>>,
            Opt_Array_NavDestinationTransition,
            Callback_Opt_Array_NavDestinationTransition_Void>(navOperation, arkIsEnter);
        return resultOpt.value_or(allTransitions);
    };
    NavDestinationModelStatic::SetCustomTransition(frameNode, onNavigationAnimation);
}
void SetOnNewParamImpl(Ark_NativePointer node,
                       const Opt_Callback_Union_Object_Idlize_Stdlib_Null_Undefined_Void* value)
{
}
void SetPreferredOrientationImpl(Ark_NativePointer node,
                                 const Opt_window_Orientation* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto ori = Converter::OptConvertPtr<Orientation>(value).value_or(Orientation::UNSPECIFIED);
    NavDestinationModelStatic::SetPreferredOrientation(frameNode, ori);
}
void SetEnableNavigationIndicatorImpl(Ark_NativePointer node,
                                      const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto enabled = false;
    if (value->tag != InteropTag::INTEROP_TAG_UNDEFINED) {
        enabled = Converter::OptConvert<bool>(*value).value_or(false);
    }
    NavDestinationModelStatic::SetEnableNavigationIndicator(frameNode, enabled);
}
void EnableNavigationIndicatorImpl(Ark_NativePointer node,
                                   const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::optional<bool> navigationIndicator;
    if (value->tag != InteropTag::INTEROP_TAG_UNDEFINED) {
        navigationIndicator = Converter::Convert<bool>(value->value);
    }
    NavDestinationModelStatic::SetEnableNavigationIndicator(frameNode, navigationIndicator);
}
void SetTitleImpl(Ark_NativePointer node,
                  const Opt_Union_String_CustomBuilder_NavDestinationCommonTitle_NavDestinationCustomTitle_Resource* value,
                  const Opt_NavigationTitleOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NavigationTitlebarOptions titleOptions;
    if (options->tag != InteropTag::INTEROP_TAG_UNDEFINED) {
        titleOptions = Converter::OptConvert<NavigationTitlebarOptions>(options->value).value_or(titleOptions);
    }
    NavDestinationModelStatic::SetTitlebarOptions(frameNode, std::move(titleOptions));
    NavigationTitleInfo info;
    if (value->tag == InteropTag::INTEROP_TAG_UNDEFINED) {
        info.hasMainTitle = true;
        info.hasSubTitle = false;
        info.title = "";
        info.subtitle = "";
        NavDestinationModelStatic::ParseCommonTitle(frameNode, info);
        return;
    }
    auto selector = Converter::Convert<int32_t>(value->value.selector);
    const int8_t mainSelector = 0;
    if (selector == mainSelector) {
        info.title = Converter::OptConvert<std::string>(value->value.value0).value_or("");
        info.hasMainTitle = true;
        info.hasSubTitle = false;
        NavDestinationModelStatic::ParseCommonTitle(frameNode, info);
        return;
    }
    const int8_t customTitleSelector = 1;
    if (selector == customTitleSelector) {
        CallbackHelper(value->value.value1)
            .BuildAsync(
                [frameNode](const RefPtr<UINode>& uiNode) {
                    CalcDimension titleHeight;
                    NavDestinationModelStatic::SetTitleHeight(frameNode, titleHeight, false);
                    NavDestinationModelStatic::SetCustomTitle(frameNode, uiNode);
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
        NavDestinationModelStatic::ParseCommonTitle(frameNode, info);
    }
    const int8_t navigationCustomTitleSelector = 3;
    if (selector == navigationCustomTitleSelector) {
        auto titleHeightSelector = value->value.value3.height.selector;
        const int8_t titleHeightType = 0;
        const int8_t lengthType = 1;
        if (titleHeightSelector == titleHeightType) {
            auto titleWithSub = static_cast<uint32_t>(value->value.value3.height.value0);
            if (titleWithSub == 0) {
                NavDestinationModelStatic::SetTitleHeight(frameNode, NG::SINGLE_LINE_TITLEBAR_HEIGHT);
            } else if (titleWithSub == 1) {
                NavDestinationModelStatic::SetTitleHeight(frameNode, NG::DOUBLE_LINE_TITLEBAR_HEIGHT);
            }
        } else if (titleHeightSelector == lengthType) {
            CalcDimension length = Converter::OptConvert<CalcDimension>(value->value.value3.height.value1)
                .value_or(Dimension());
            if (length.Value() < 0) {
                NavDestinationModelStatic::SetTitleHeight(frameNode, Dimension());
            } else {
                NavDestinationModelStatic::SetTitleHeight(frameNode, length);
            }
        }
        CallbackHelper(value->value.value3.builder)
            .BuildAsync(
                [frameNode](
                    const RefPtr<UINode>& uiNode) { NavDestinationModelStatic::SetCustomTitle(frameNode, uiNode); },
                node);
        return;
    }
    const int8_t resourceType = 4;
    if (selector == resourceType) {
        Converter::ResourceConverter converter(value->value.value4);
        info.title = converter.ToString().value_or("");
        info.hasMainTitle = true;
        info.hasSubTitle = false;
        NavDestinationModelStatic::ParseCommonTitle(frameNode, info);
        return;
    }
}
void SetHideTitleBar1Impl(Ark_NativePointer node,
                          const Opt_Boolean* hide,
                          const Opt_Boolean* animated)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NavDestinationModelStatic::SetHideTitleBar(frameNode, Converter::OptConvertPtr<bool>(hide).value_or(false),
        Converter::OptConvertPtr<bool>(animated).value_or(false));
}
void SetBackButtonIconImpl(Ark_NativePointer node,
                            const Opt_Union_ResourceStr_PixelMap_SymbolGlyphModifier* icon,
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
        const uint32_t stringResourceType = 0;
        const uint32_t pixelType = 1;
        const uint32_t symbolType = 2;
        switch (valueType) {
            case stringResourceType: {
                // src = Converter::Convert<std::string>(value->value.value0);
                auto strType = Converter::Convert<int32_t>(icon->value.value0.selector);
                if (strType == 0) {
                    src = Converter::Convert<std::string>(icon->value.value0.value0);
                } else if (strType == 1) {
                    Converter::ResourceConverter converter(icon->value.value0.value1);
                    src = converter.ToString().value_or("");
                }
                imageOption.noPixMap = true;
                imageOption.isValidImage = true;
                break;
            }
            case pixelType: {
                pixMap = Converter::OptConvert<RefPtr<PixelMap>>(icon->value.value1).value_or(nullptr);
                break;
            }
            case symbolType: {
                iconSymbol = icon->value.value2->symbolApply;
                PeerUtils::DestroyPeer(icon->value.value2);
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
    NavDestinationModelStatic::SetBackButtonIcon(
        frameNode, iconSymbol, src, imageOption, pixMap, nameList, true, backButtonAccessibilityText);
}
void SetMenusImpl(Ark_NativePointer node,
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
            NavDestinationModelStatic::SetMenuItems(frameNode, std::move(menuItemArray));
        } else if (typeValue == 1) {
            CallbackHelper(items->value.value1).BuildAsync([frameNode](const RefPtr<UINode>& uiNode) {
                NavDestinationModelStatic::SetCustomMenu(frameNode, std::move(uiNode));
            }, node);
        }
    }
    if (options->tag != InteropTag::INTEROP_TAG_UNDEFINED &&
        options->value.moreButtonOptions.tag != InteropTag::INTEROP_TAG_UNDEFINED) {
        NG::NavigationBackgroundOptions bgOptions =
            Converter::Convert<NG::NavigationBackgroundOptions>(options->value.moreButtonOptions.value);
        menuOptions.mbOptions.bgOptions = bgOptions;
    }
    NavDestinationModelStatic::SetMenuOptions(frameNode, std::move(menuOptions));
}
void SetToolbarConfigurationImpl(Ark_NativePointer node,
                                 const Opt_Union_Array_ToolbarItem_CustomBuilder* toolbarParam,
                                 const Opt_NavigationToolbarOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(toolbarParam);
    if (options->tag != InteropTag::INTEROP_TAG_UNDEFINED) {
        auto isHideItemText = Converter::OptConvert<bool>(options->value.hideItemValue).value_or(false);
        NavDestinationModelStatic::SetHideItemText(frameNode, isHideItemText);
    } else {
        NavDestinationModelStatic::SetHideItemText(frameNode, false);
    }
    NG::NavigationToolbarOptions toolbarOptions;
    if (toolbarParam->tag != InteropTag::INTEROP_TAG_UNDEFINED) {
        auto typeValue = toolbarParam->value.selector;
        if (typeValue == 0) {
            NG::MoreButtonOptions toolbarMoreButtonOptions;
            if (options->tag != InteropTag::INTEROP_TAG_UNDEFINED &&
                options->value.moreButtonOptions.tag != InteropTag::INTEROP_TAG_UNDEFINED) {
                NG::NavigationBackgroundOptions bgOptions =
                    Converter::Convert<NG::NavigationBackgroundOptions>(options->value.moreButtonOptions.value);
                toolbarMoreButtonOptions.bgOptions = bgOptions;
            }
            NavDestinationModelStatic::SetToolbarMorebuttonOptions(frameNode, std::move(toolbarMoreButtonOptions));
            auto toolbarItemArray = Converter::Convert<std::vector<NG::BarItem>>(toolbarParam->value.value0);
            NavDestinationModelStatic::SetToolbarConfiguration(frameNode, std::move(toolbarItemArray));
        } else if (typeValue == 1) {
            CallbackHelper(toolbarParam->value.value1)
                .BuildAsync(
                    [frameNode](const RefPtr<UINode>& uiNode) {
                        NavDestinationModelStatic::SetCustomToolBar(frameNode, uiNode);
                    },
                    node);
        }
    } else {
        NavDestinationModelStatic::SetToolbarMorebuttonOptions(frameNode, NG::MoreButtonOptions());
        NavDestinationModelStatic::SetToolbarConfiguration(frameNode, std::vector<NG::BarItem>());
        NavDestinationModelStatic::SetCustomToolBar(frameNode, nullptr);
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
    NavDestinationModelStatic::SetToolBarOptions(frameNode, std::move(toolbarOptions));
}
void SetHideToolBarImpl(Ark_NativePointer node,
                        const Opt_Boolean* hide,
                        const Opt_Boolean* animated)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto isHide = Converter::OptConvertPtr<bool>(hide).value_or(false);
    auto isAnimated = Converter::OptConvertPtr<bool>(animated).value_or(false);
    NavDestinationModelStatic::SetHideToolBar(frameNode, isHide, isAnimated);
}
void SetIgnoreLayoutSafeAreaImpl(Ark_NativePointer node,
                                 const Opt_Array_LayoutSafeAreaType* types,
                                 const Opt_Array_LayoutSafeAreaEdge* edges)
{
    constexpr int32_t LAYOUT_SAFE_AREA_TYPE_LIMIT = 2;
    constexpr int32_t LAYOUT_SAFE_AREA_EDGE_LIMIT = 6;
    auto frameNode = reinterpret_cast<FrameNode*>(node);
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
    NavDestinationModelStatic::SetIgnoreLayoutSafeArea(frameNode, opts);
}
void SetEnableStatusBarImpl(Ark_NativePointer node,
                            const Opt_Boolean* enabled,
                            const Opt_Boolean* animated)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(enabled);
    CHECK_NULL_VOID(animated);
    std::optional<std::pair<bool, bool>> statusBar;
    if (enabled->tag != InteropTag::INTEROP_TAG_UNDEFINED) {
        auto enable = Converter::Convert<bool>(enabled->value);
        bool animate = false;
        if (animated->tag != InteropTag::INTEROP_TAG_UNDEFINED) {
            animate = Converter::Convert<bool>(animated->value);
        }
        statusBar = std::make_pair(enable, animate);
    }
    NavDestinationModelStatic::SetEnableStatusBar(frameNode, statusBar);
}
} // namespace NavDestinationAttributeModifier
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
        NavDestinationAttributeModifier::SetOnResultImpl,
        NavDestinationAttributeModifier::SetModeImpl,
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
        NavDestinationAttributeModifier::SetBackButtonIconImpl,
        NavDestinationAttributeModifier::SetMenusImpl,
        NavDestinationAttributeModifier::SetToolbarConfigurationImpl,
        NavDestinationAttributeModifier::SetHideToolBarImpl,
        NavDestinationAttributeModifier::SetIgnoreLayoutSafeAreaImpl,
        NavDestinationAttributeModifier::SetEnableStatusBarImpl,
    };
    return &ArkUINavDestinationModifierImpl;
}

} // namespace OHOS::Ace::NG::GeneratedModifier
