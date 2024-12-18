/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include "core/interfaces/native/node/nav_destination_modifier.h"

#include "core/components_ng/pattern/navrouter/navdestination_model_ng.h"

namespace OHOS::Ace::NG {
constexpr int32_t DEFAULT_SAFE_AREA_TYPE = 0b1;
constexpr int32_t DEFAULT_SAFE_AREA_EDGE = 0b1111;
void SetHideTitleBar(ArkUINodeHandle node, ArkUI_Bool hideTitle, ArkUI_Bool animated)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NavDestinationModelNG::SetHideTitleBar(frameNode, hideTitle, animated);
}

void ResetHideTitleBar(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NavDestinationModelNG::SetHideTitleBar(frameNode, false, false);
}

void SetNavDestinationHideToolBar(ArkUINodeHandle node, ArkUI_Bool hide, ArkUI_Bool animated)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NavDestinationModelNG::SetHideToolBar(frameNode, hide, animated);
}

void ResetNavDestinationHideToolBar(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NavDestinationModelNG::SetHideToolBar(frameNode, false, false);
}

void SetNavDestinationMode(ArkUINodeHandle node, int32_t value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NavDestinationModelNG::SetNavDestinationMode(frameNode, static_cast<NG::NavDestinationMode>(value));
}

void ResetNavDestinationMode(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NavDestinationModelNG::SetNavDestinationMode(frameNode, NG::NavDestinationMode::STANDARD);
}

void SetNavDestinationSystemTransition(ArkUINodeHandle node, int32_t value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NavDestinationModelNG::SetSystemTransitionType(frameNode, static_cast<NG::NavigationSystemTransitionType>(value));
}

void ResetNavDestinationSystemTransition(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NavDestinationModelNG::SetSystemTransitionType(frameNode, NG::NavigationSystemTransitionType::DEFAULT);
}

void SetIgnoreLayoutSafeArea(ArkUINodeHandle node, const char* typeStr, const char* edgesStr)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NG::SafeAreaExpandOpts opts { .type = NG::SAFE_AREA_TYPE_SYSTEM, .edges = NG::SAFE_AREA_EDGE_ALL };
    uint32_t safeAreaType = NG::SAFE_AREA_TYPE_NONE;
    uint32_t safeAreaEdge = NG::SAFE_AREA_EDGE_NONE;
    std::string safeAreaTypeStr = std::string(typeStr);
    std::string safeAreaEdgeStr = std::string(edgesStr);
    if (safeAreaTypeStr == "" || safeAreaEdgeStr == "") {
        NG::SafeAreaExpandOpts opts { .type = NG::SAFE_AREA_TYPE_NONE, .edges = NG::SAFE_AREA_EDGE_NONE};
        NavDestinationModelNG::SetIgnoreLayoutSafeArea(frameNode, opts);
        return;
    }
    std::string delimiter = "|";
    size_t pos = 0;
    std::string type;
    std::string edges;
    while ((pos = safeAreaTypeStr.find(delimiter)) != std::string::npos) {
        type = safeAreaTypeStr.substr(0, pos);
        safeAreaType |= (1 << StringUtils::StringToUint(type));
        safeAreaTypeStr.erase(0, pos + delimiter.length());
    }
    safeAreaType |= (1 << StringUtils::StringToUint(safeAreaTypeStr));
    pos = 0;
    while ((pos = safeAreaEdgeStr.find(delimiter)) != std::string::npos) {
        edges = safeAreaEdgeStr.substr(0, pos);
        safeAreaEdge |= (1 << StringUtils::StringToUint(edges));
        safeAreaEdgeStr.erase(0, pos + delimiter.length());
    }
    safeAreaEdge |= (1 << StringUtils::StringToUint(safeAreaEdgeStr));
    opts.type = safeAreaType;
    opts.edges = safeAreaEdge;
    NavDestinationModelNG::SetIgnoreLayoutSafeArea(frameNode, opts);
}

void ResetIgnoreLayoutSafeArea(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NG::SafeAreaExpandOpts opts;
    opts.type = DEFAULT_SAFE_AREA_TYPE;
    opts.edges = DEFAULT_SAFE_AREA_EDGE;
    NavDestinationModelNG::SetIgnoreLayoutSafeArea(frameNode, opts);
}

void SetTitle(ArkUINodeHandle node, ArkUINavigationTitleInfo titleInfo, ArkUINavigationTitlebarOptions options)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::string mainTitleString = std::string(titleInfo.mainTitle);
    std::string subTitleString = std::string(titleInfo.subTitle);
    NG::NavigationTitleInfo ngTitleInfo = { titleInfo.hasSubTitle, titleInfo.hasMainTitle,
        subTitleString, mainTitleString };
    NavDestinationModelNG::ParseCommonTitle(frameNode, ngTitleInfo);
    NG::NavigationTitlebarOptions finalOptions;
    if (options.colorValue.isSet) {
        finalOptions.bgOptions.color = Color(options.colorValue.value);
    }
    if (options.blurStyle.isSet) {
        finalOptions.bgOptions.blurStyle = static_cast<BlurStyle>(options.blurStyle.value);
    }
    if (options.barStyle.isSet) {
        finalOptions.brOptions.barStyle = static_cast<NG::BarStyle>(options.barStyle.value);
    }
    if (options.paddingStart.isSet) {
        finalOptions.brOptions.paddingStart = CalcDimension(static_cast<double>(options.paddingStart.dimension.value),
            static_cast<DimensionUnit>(options.paddingStart.dimension.units));
    }
    if (options.paddingEnd.isSet) {
        finalOptions.brOptions.paddingEnd = CalcDimension(static_cast<double>(options.paddingEnd.dimension.value),
            static_cast<DimensionUnit>(options.paddingEnd.dimension.units));
    }
    if (options.enableHoverMode.isSet) {
        finalOptions.enableHoverMode = options.enableHoverMode.value;
    }
    NavDestinationModelNG::SetTitlebarOptions(frameNode, std::move(finalOptions));
}

void ResetTitle(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NG::NavigationTitleInfo ngTitleInfo = { false, false, "", "" };
    NavDestinationModelNG::ParseCommonTitle(frameNode, ngTitleInfo);
    NavigationTitlebarOptions options;
    NavDestinationModelNG::SetTitlebarOptions(frameNode, std::move(options));
}

void SetMenus(ArkUINodeHandle node, ArkUIBarItem* items, ArkUI_Uint32 length)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(items);
    std::vector<NG::BarItem> menuItems;
    for (uint32_t i = 0; i < length; i++) {
        NG::BarItem menuItem;
        if (items[i].text.isSet) {
            menuItem.text = items[i].text.value;
        }
        if (items[i].icon.isSet) {
            menuItem.icon = items[i].icon.value;
        }
        if (items[i].isEnable.isSet) {
            menuItem.isEnabled = items[i].isEnable.value;
        }
        menuItems.push_back(menuItem);
        if (items[i].text.value) {
            delete[] items[i].text.value;
            items[i].text.value = nullptr;
        }
        if (items[i].icon.value) {
            delete[] items[i].icon.value;
            items[i].icon.value = nullptr;
        }
    }
    NavDestinationModelNG::SetMenuItems(frameNode, std::move(menuItems));
}

void ResetMenus(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::vector<NG::BarItem> menuItems;
    NavDestinationModelNG::SetMenuItems(frameNode, std::move(menuItems));
}

void SetMenuItemAction(ArkUINodeHandle node, void* action, ArkUI_Uint32 index)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto actionFunc = reinterpret_cast<std::function<void()>*>(action);
    NavDestinationModelNG::SetMenuItemAction(frameNode, std::move(*actionFunc), index);
}

void SetMenuItemSymbol(ArkUINodeHandle node, void* symbol, ArkUI_Uint32 index)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto iconFunc = reinterpret_cast<std::function<void(WeakPtr<NG::FrameNode>)>*>(symbol);
    NavDestinationModelNG::SetMenuItemSymbol(frameNode, std::move(*iconFunc), index);
}

void SetNavDestinationRecoverable(ArkUINodeHandle node, ArkUI_Bool recoverable)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NavDestinationModelNG::SetRecoverable(frameNode, recoverable);
}

void ResetNavDestinationRecoverable(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    // default value of navdestination's recoverable is true
    NavDestinationModelNG::SetRecoverable(frameNode, true);
}

namespace NodeModifier {
const ArkUINavDestinationModifier* GetNavDestinationModifier()
{
    static const ArkUINavDestinationModifier modifier = {
        SetHideTitleBar,
        ResetHideTitleBar,
        SetNavDestinationHideToolBar,
        ResetNavDestinationHideToolBar,
        SetNavDestinationMode,
        ResetNavDestinationMode,
        SetIgnoreLayoutSafeArea,
        ResetIgnoreLayoutSafeArea,
        SetTitle,
        ResetTitle,
        SetMenus,
        ResetMenus,
        SetMenuItemAction,
        SetMenuItemSymbol,
        SetNavDestinationRecoverable,
        ResetNavDestinationRecoverable,
        SetNavDestinationSystemTransition,
        ResetNavDestinationSystemTransition
    };

    return &modifier;
}

const CJUINavDestinationModifier* GetCJUINavDestinationModifier()
{
    static const CJUINavDestinationModifier modifier = {
        SetHideTitleBar,
        ResetHideTitleBar,
        SetNavDestinationHideToolBar,
        ResetNavDestinationHideToolBar,
        SetNavDestinationMode,
        ResetNavDestinationMode,
        SetIgnoreLayoutSafeArea,
        ResetIgnoreLayoutSafeArea,
        SetNavDestinationSystemTransition,
        ResetNavDestinationSystemTransition
    };

    return &modifier;
}
}
} // namespace OHOS::Ace::NG
