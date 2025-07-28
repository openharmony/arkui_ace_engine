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
#include "core/interfaces/native/generated/interface/node_api.h"
#include "core/interfaces/native/utility/callback_helper.h"
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
namespace NavDestinationModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                Ark_Int32 flags)
{
    RefPtr<FrameNode> frameNode = nullptr;
    auto contentCreator = []() {
        // empty content creator to be done
    };
    frameNode = NavDestinationModelStatic::CreateFrameNode(id, std::move(contentCreator));
    CHECK_NULL_RETURN(frameNode, nullptr);
    frameNode->IncRefCount();
    return AceType::RawPtr(frameNode);
}
} // namespace NavDestinationModifier
namespace NavDestinationInterfaceModifier {
void SetNavDestinationOptionsImpl(Ark_NativePointer node)
{
    // "No need to implement this method"
}
} // namespace NavDestinationInterfaceModifier
namespace NavDestinationAttributeModifier {
void HideTitleBar0Impl(Ark_NativePointer node,
                       const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NavDestinationModelStatic::SetHideTitleBar(frameNode, Converter::OptConvert<bool>(*value).value_or(false));
}
void HideTitleBar1Impl(Ark_NativePointer node, const Opt_Boolean* hide, const Opt_Boolean* animated)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NavDestinationModelStatic::SetHideTitleBar(frameNode, Converter::OptConvert<bool>(*hide).value_or(false),
        Converter::OptConvert<bool>(*animated).value_or(false));
}
void HideBackButtonImpl(Ark_NativePointer node,
                        const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    // auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    // NavDestinationModelNG::SetHideBackButton(frameNode, convValue);
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
    NavDestinationModelStatic::SetOnShown(frameNode, std::move(onShownEvent));
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
    auto onHiddenEvent = [arkCallback = CallbackHelper(*optValue)]() { arkCallback.Invoke(); };
    NavDestinationModelStatic::SetOnHidden(frameNode, std::move(onHiddenEvent));
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
    NavDestinationModelStatic::SetOnBackPressed(frameNode, std::move(onBackPressedEvent));
}
void OnResultImpl(Ark_NativePointer node,
                  const Opt_Callback_Object_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    // auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    // NavDestinationModelNG::SetOnResult(frameNode, convValue);
}
void ModeImpl(Ark_NativePointer node,
              const Opt_NavDestinationMode* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto mode = Converter::OptConvert<NavDestinationMode>(*value).value_or(NavDestinationMode::STANDARD);
    NavDestinationModelStatic::SetNavDestinationMode(frameNode, mode);
}
void BackButtonIcon0Impl(Ark_NativePointer node,
                         const Opt_Union_ResourceStr_PixelMap_SymbolGlyphModifier* value)
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
        const uint32_t stringResourceType = 0;
        const uint32_t pixelType = 1;
        const uint32_t symbolType = 2;
        switch (valueType) {
            case stringResourceType: {
                // src = Converter::Convert<std::string>(value->value.value0);
                auto strType = Converter::Convert<int32_t>(value->value.value0.selector);
                if (strType == 0) {
                    src = Converter::Convert<std::string>(value->value.value0.value0);
                } else if (strType == 1) {
                    Converter::ResourceConverter converter(value->value.value0.value1);
                    src = converter.ToString().value_or("");
                }
                imageOption.noPixMap = true;
                imageOption.isValidImage = true;
                break;
            }
            case pixelType: {
                pixMap = Converter::OptConvert<RefPtr<PixelMap>>(value->value.value1).value_or(nullptr);
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
    NavDestinationModelStatic::SetBackButtonIcon(frameNode, iconSymbol, src, imageOption, pixMap, nameList);
}
void BackButtonIcon1Impl(Ark_NativePointer node,
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
void Menus0Impl(Ark_NativePointer node,
                const Opt_Union_Array_NavigationMenuItem_CustomBuilder* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    NG::NavigationMenuOptions options;
    if (value->tag != InteropTag::INTEROP_TAG_UNDEFINED) {
        auto typeValue = value->value.selector;
        if (typeValue == 0) {
            auto menuItemArray = Converter::Convert<std::vector<NG::BarItem>>(value->value.value0);
            NavDestinationModelStatic::SetMenuItems(frameNode, std::move(menuItemArray));
        } else if (typeValue == 1) {
            CallbackHelper(value->value.value1).BuildAsync([frameNode](const RefPtr<UINode>& uiNode) {
                NavDestinationModelStatic::SetCustomMenu(frameNode, std::move(uiNode));
            }, node);
        }
    }
    NavDestinationModelStatic::SetMenuOptions(frameNode, std::move(options));
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
void OnReadyImpl(Ark_NativePointer node,
                 const Opt_Callback_NavDestinationContext_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    if (value->tag == InteropTag::INTEROP_TAG_UNDEFINED) {
        return;
    }
    auto onReady = [readyCallback = CallbackHelper(value->value)](RefPtr<NG::NavDestinationContext> context) {
        Ark_NavDestinationContext arkContext = Converter::ArkValue<Ark_NavDestinationContext>(context);
        readyCallback.Invoke(arkContext);
    };
    NavDestinationModelStatic::SetOnReady(frameNode, std::move(onReady));
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
    NavDestinationModelStatic::SetOnWillAppear(frameNode, std::move(onWillAppearEvent));
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
    NavDestinationModelStatic::SetOnWillDisAppear(frameNode, std::move(onWillDisappearEvent));
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
    NavDestinationModelStatic::SetOnWillShow(frameNode, std::move(onWillShowEvent));
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
    NavDestinationModelStatic::SetOnWillHide(frameNode, std::move(onWillHideEvent));
}
void SystemBarStyleImpl(Ark_NativePointer node,
                        const Opt_SystemBarStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    // auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    // NavDestinationModelNG::SetSystemBarStyle(frameNode, convValue);
    LOGE("ARKOALA NavDestination.SystemBarStyleImpl -> Method is not implemented, Opt_CustomObject is not supported!");
}
void RecoverableImpl(Ark_NativePointer node,
                     const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = value ? Converter::OptConvert<bool>(*value) : std::nullopt;
    NavDestinationModelStatic::SetRecoverable(frameNode, convValue);
}

void SystemTransitionImpl(Ark_NativePointer node,
                          const Opt_NavigationSystemTransitionType* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    if (value->tag == InteropTag::INTEROP_TAG_UNDEFINED) {
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
void BindToScrollableImpl(Ark_NativePointer node,
                          const Opt_Array_Scroller* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    // auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    // NavDestinationModelNG::SetBindToScrollable(frameNode, convValue);
}
void BindToNestedScrollableImpl(Ark_NativePointer node,
                                const Opt_Array_NestedScrollInfo* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    // auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    // NavDestinationModelNG::SetBindToNestedScrollable(frameNode, convValue);
}
void OnActiveImpl(Ark_NativePointer node,
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
        arkCallback.Invoke(arkValue);
    };
    NavDestinationModelStatic::SetOnActive(frameNode, std::move(onActiveEvent));
}

void OnInactiveImpl(Ark_NativePointer node,
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
        arkCallback.Invoke(arkValue);
    };
    NavDestinationModelStatic::SetOnInactive(frameNode, std::move(onInactiveEvent));
}

void CustomTransitionImpl(Ark_NativePointer node,
                          const Opt_NavDestinationTransitionDelegate* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    // auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    // NavDestinationModelNG::SetCustomTransition(frameNode, convValue);
}
void OnNewParamImpl(Ark_NativePointer node,
                    const Opt_Callback_Object_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    // auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    // NavDestinationModelNG::SetOnNewParam(frameNode, convValue);
}
void PreferredOrientationImpl(Ark_NativePointer node,
                              const Opt_Orientation* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    // auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    // NavDestinationModelNG::SetPreferredOrientation(frameNode, convValue);
}
void EnableNavigationIndicatorImpl(Ark_NativePointer node,
                                   const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    // auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    // NavDestinationModelNG::SetEnableNavigationIndicator(frameNode, convValue);
}
void TitleImpl(Ark_NativePointer node,
               const Opt_Type_NavDestinationAttribute_title_value* value,
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
            CalcDimension length = Converter::Convert<CalcDimension>(value->value.value3.height.value1);
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
void ToolbarConfigurationImpl(Ark_NativePointer node, const Opt_Union_Array_ToolbarItem_CustomBuilder* toolbarParam,
    const Opt_NavigationToolbarOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(toolbarParam);
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
void HideToolBarImpl(Ark_NativePointer node, const Opt_Boolean* hide, const Opt_Boolean* animated)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(hide);
    CHECK_NULL_VOID(animated);
    auto isHide = false;
    if (hide->tag != InteropTag::INTEROP_TAG_UNDEFINED) {
        isHide = Converter::OptConvert<bool>(*hide).value_or(false);
    }
    bool isAnimated = false;
    if (animated->tag != InteropTag::INTEROP_TAG_UNDEFINED) {
        isAnimated = Converter::OptConvert<bool>(*animated).value_or(false);
    }
    NavDestinationModelStatic::SetHideToolBar(frameNode, isHide, isAnimated);
}
void IgnoreLayoutSafeAreaImpl(
    Ark_NativePointer node, const Opt_Array_LayoutSafeAreaType* types, const Opt_Array_LayoutSafeAreaEdge* edges)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
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
    NavDestinationModelStatic::SetIgnoreLayoutSafeArea(frameNode, opts);
}
void EnableStatusBarImpl(Ark_NativePointer node, const Opt_Boolean* enabled, const Opt_Boolean* animated)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    // auto convValue = Converter::Convert<type>(enabled);
    // auto convValue = Converter::OptConvert<type>(enabled); // for enums
    // NavDestinationModelNG::SetEnableStatusBar(frameNode, convValue);
}
} // namespace NavDestinationAttributeModifier
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

} // namespace OHOS::Ace::NG::GeneratedModifier
