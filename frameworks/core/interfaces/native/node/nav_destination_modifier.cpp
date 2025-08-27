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
#include "core/components_ng/pattern/navrouter/navdestination_pattern.h"

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

void SetNavDestinationHideBackButton(ArkUINodeHandle node, ArkUI_Bool hideBackButton)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NavDestinationModelNG::SetHideBackButton(frameNode, hideBackButton);
}

void ResetNavDestinationHideBackButton(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NavDestinationModelNG::SetHideBackButton(frameNode, false);
}

void SetNavDestinationBackgroundColor(ArkUINodeHandle node, uint32_t color, void* bgColorRawPtr)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto* bgColor = reinterpret_cast<ResourceObject*>(bgColorRawPtr);
    auto backgroundColorResObj = AceType::Claim(bgColor);
    NavDestinationModelNG::SetBackgroundColor(frameNode, Color(color), true, backgroundColorResObj);
}

void ResetNavDestinationBackgroundColor(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    Color backgroundColor;
    NavDestinationModelNG::SetBackgroundColor(frameNode, backgroundColor, false, nullptr);
}

void SetNavDestinationBackgroundColorWithColorSpace(
    ArkUINodeHandle node, ArkUI_Uint32 color, ArkUI_Int32 colorSpace, void* bgColorRawPtr)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto* bgColor = reinterpret_cast<ResourceObject*>(bgColorRawPtr);
    auto backgroundColorResObj = AceType::Claim(bgColor);
    Color backgroundColor { color };
    if (ColorSpace::DISPLAY_P3 == colorSpace) {
        backgroundColor.SetColorSpace(ColorSpace::DISPLAY_P3);
    } else {
        backgroundColor.SetColorSpace(ColorSpace::SRGB);
    }
    NavDestinationModelNG::SetBackgroundColor(frameNode, backgroundColor, true, backgroundColorResObj);
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
    NG::IgnoreLayoutSafeAreaOpts opts { .type = NG::SAFE_AREA_TYPE_SYSTEM, .edges = NG::SAFE_AREA_EDGE_ALL };
    uint32_t safeAreaType = NG::SAFE_AREA_TYPE_NONE;
    uint32_t safeAreaEdge = NG::SAFE_AREA_EDGE_NONE;
    std::string safeAreaTypeStr = std::string(typeStr);
    std::string safeAreaEdgeStr = std::string(edgesStr);
    if (safeAreaTypeStr == "" || safeAreaEdgeStr == "") {
        NG::IgnoreLayoutSafeAreaOpts opts { .type = NG::SAFE_AREA_TYPE_NONE, .edges = NG::SAFE_AREA_EDGE_NONE};
        NavDestinationModelNG::SetIgnoreLayoutSafeArea(frameNode, opts);
        return;
    }
    std::string delimiter = "|";
    size_t pos = 0;
    std::string type;
    std::string edges;
    while ((pos = safeAreaTypeStr.find(delimiter)) != std::string::npos) {
        type = safeAreaTypeStr.substr(0, pos);
        safeAreaType |= IgnoreLayoutSafeAreaOpts::TypeToMask(StringUtils::StringToUint(type));
        safeAreaTypeStr.erase(0, pos + delimiter.length());
    }
    if (safeAreaTypeStr != "") {
        safeAreaType |= IgnoreLayoutSafeAreaOpts::TypeToMask(StringUtils::StringToUint(safeAreaTypeStr));
    }
    pos = 0;
    while ((pos = safeAreaEdgeStr.find(delimiter)) != std::string::npos) {
        edges = safeAreaEdgeStr.substr(0, pos);
        safeAreaEdge |= IgnoreLayoutSafeAreaOpts::EdgeToMask(StringUtils::StringToUint(edges));
        safeAreaEdgeStr.erase(0, pos + delimiter.length());
    }
    if (safeAreaEdgeStr != "") {
        safeAreaEdge |= IgnoreLayoutSafeAreaOpts::EdgeToMask(StringUtils::StringToUint(safeAreaEdgeStr));
    }
    opts.type = safeAreaType;
    opts.rawEdges = safeAreaEdge;
    NavDestinationModelNG::SetIgnoreLayoutSafeArea(frameNode, opts);
}

void ResetIgnoreLayoutSafeArea(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NG::IgnoreLayoutSafeAreaOpts opts;
    opts.type = DEFAULT_SAFE_AREA_TYPE;
    opts.rawEdges = DEFAULT_SAFE_AREA_EDGE;
    NavDestinationModelNG::SetIgnoreLayoutSafeArea(frameNode, opts);
}

void UpdateNavDestinationTitlebarOptions(FrameNode* frameNode, ArkUINavigationTitlebarOptions options)
{
    CHECK_NULL_VOID(frameNode);
    RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>("", "", -1);
    auto&& updateFunc = [wekNode = AceType::WeakClaim(frameNode), options](
                            const RefPtr<ResourceObject>& resObj) mutable {
        options.ReloadResources();
        NG::NavigationTitlebarOptions finalOptions;
        if (options.colorValue.isSet) {
            finalOptions.bgOptions.color = Color(options.colorValue.value);
        }
        if (options.blurStyle.isSet) {
            BlurStyleOption blurStyleOption;
            blurStyleOption.blurStyle = static_cast<BlurStyle>(options.blurStyle.value);
            finalOptions.bgOptions.blurStyleOption = blurStyleOption;
        }
        if (options.barStyle.isSet) {
            finalOptions.brOptions.barStyle = static_cast<NG::BarStyle>(options.barStyle.value);
        }
        if (options.paddingStart.isSet) {
            finalOptions.brOptions.paddingStart =
                CalcDimension(static_cast<double>(options.paddingStart.dimension.value),
                    static_cast<DimensionUnit>(options.paddingStart.dimension.units));
        }
        if (options.paddingEnd.isSet) {
            finalOptions.brOptions.paddingEnd =
                CalcDimension(static_cast<double>(options.paddingEnd.dimension.value),
                    static_cast<DimensionUnit>(options.paddingEnd.dimension.units));
        }
        if (options.enableHoverMode.isSet) {
            finalOptions.enableHoverMode = options.enableHoverMode.value;
        }
        auto localFinalOptions = finalOptions;
        auto frameNode = wekNode.Upgrade();
        CHECK_NULL_VOID(frameNode);
        NavDestinationModelNG::SetTitlebarOptions(AceType::RawPtr(frameNode), std::move(localFinalOptions));
        frameNode->MarkModifyDone();
        frameNode->MarkDirtyNode();
    };
    auto pattern = frameNode->GetPattern();
    CHECK_NULL_VOID(pattern);
    pattern->AddResObj("navDestination.titlebarOptions", resObj, std::move(updateFunc));
}

void SetTitle(ArkUINodeHandle node, ArkUINavigationTitleInfo titleInfo, ArkUINavigationTitlebarOptions options,
    void* titleRawPtr, void* subtitleRawPtr)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NavDestinationModelNG::ResetResObj(
        frameNode, NavDestinationPatternType::TITLE_BAR, "navDestination.title.commonMainTitle");
    NavDestinationModelNG::ResetResObj(
        frameNode, NavDestinationPatternType::TITLE_BAR, "navDestination.title.commonSubTitle");
    NavDestinationModelNG::ResetResObj(
        frameNode, NavDestinationPatternType::NAV_DESTINATION, "navDestination.titlebarOptions");
    std::string mainTitleString = std::string(titleInfo.mainTitle);
    std::string subTitleString = std::string(titleInfo.subTitle);
    NG::NavigationTitleInfo ngTitleInfo = { titleInfo.hasSubTitle, titleInfo.hasMainTitle,
        subTitleString, mainTitleString };
    if (SystemProperties::ConfigChangePerform() && (titleRawPtr || subtitleRawPtr)) {
        auto* title = reinterpret_cast<ResourceObject*>(titleRawPtr);
        auto titleResObj = AceType::Claim(title);
        auto* subtitle = reinterpret_cast<ResourceObject*>(subtitleRawPtr);
        auto subtitleResObj = AceType::Claim(subtitle);
        NavDestinationModelNG::ParseCommonTitle(frameNode, titleResObj, subtitleResObj);
    } else {
        NavDestinationModelNG::ParseCommonTitle(frameNode, ngTitleInfo);
    }
    NG::NavigationTitlebarOptions finalOptions;
    if (options.colorValue.isSet) {
        finalOptions.bgOptions.color = Color(options.colorValue.value);
    }
    if (options.blurStyle.isSet) {
        BlurStyleOption blurStyleOption;
        blurStyleOption.blurStyle = static_cast<BlurStyle>(options.blurStyle.value);
        finalOptions.bgOptions.blurStyleOption = blurStyleOption;
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
    if (SystemProperties::ConfigChangePerform()) {
        UpdateNavDestinationTitlebarOptions(frameNode, options);
    }
}

void ResetTitle(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NavDestinationModelNG::ResetResObj(
        frameNode, NavDestinationPatternType::TITLE_BAR, "navDestination.title.commonMainTitle");
    NavDestinationModelNG::ResetResObj(
        frameNode, NavDestinationPatternType::TITLE_BAR, "navDestination.title.commonSubTitle");
    NavDestinationModelNG::ResetResObj(
        frameNode, NavDestinationPatternType::NAV_DESTINATION, "navDestination.titlebarOptions");
    NG::NavigationTitleInfo ngTitleInfo = { false, false, "", "" };
    NavDestinationModelNG::ParseCommonTitle(frameNode, ngTitleInfo);
    NavigationTitlebarOptions options;
    NavDestinationModelNG::SetTitlebarOptions(frameNode, std::move(options));
}

void UpdateNavDestSymbolAndAction(const RefPtr<FrameNode>& frameNode, std::vector<NG::BarItem>& menuItems)
{
    auto navDestinationGroupNode = AceType::DynamicCast<NavDestinationGroupNode>(frameNode);
    CHECK_NULL_VOID(navDestinationGroupNode);
    auto navDestinationPattern = navDestinationGroupNode->GetPattern<NavDestinationPattern>();
    CHECK_NULL_VOID(navDestinationPattern);
    auto titleBarMenuItems = navDestinationPattern->GetTitleBarMenuItems();
    for (size_t i = 0; i < menuItems.size() && i < titleBarMenuItems.size(); i++) {
        menuItems[i].action = titleBarMenuItems[i].action;
        if (titleBarMenuItems[i].iconSymbol.has_value()) {
            menuItems[i].iconSymbol = titleBarMenuItems[i].iconSymbol.value();
        }
    }
}

void UpdateNavDestinationMenuItem(FrameNode* frameNode, ArkUIBarItem* items, ArkUI_Uint32 length)
{
    CHECK_NULL_VOID(frameNode);
    RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>("", "", -1);
    auto updateFunc = [wekNode = AceType::WeakClaim(frameNode),
                          items = std::vector<ArkUIBarItem>(items, items + length)](
                          const RefPtr<ResourceObject>& resObj) mutable {
        for (uint32_t i = 0; i < items.size(); i++) {
            items[i].ReloadResources();
        }
        std::vector<NG::BarItem> menuItems;
        for (uint32_t i = 0; i < items.size(); i++) {
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
            if (items[i].text.value && !items[i].isStringText) {
                delete[] items[i].text.value;
                items[i].text.value = nullptr;
            }
            if (items[i].icon.value && !items[i].isStringIcon) {
                delete[] items[i].icon.value;
                items[i].icon.value = nullptr;
            }
        }
        auto frameNode = wekNode.Upgrade();
        CHECK_NULL_VOID(frameNode);
        UpdateNavDestSymbolAndAction(frameNode, menuItems);
        auto localMenuItems = menuItems;
        NavDestinationModelNG::SetMenuItems(AceType::RawPtr(frameNode), std::move(localMenuItems));
        frameNode->MarkModifyDone();
        frameNode->MarkDirtyNode();
    };
    auto pattern = frameNode->GetPattern();
    CHECK_NULL_VOID(pattern);
    pattern->AddResObj("navDestinationModifer.menuItems", resObj, std::move(updateFunc));
}

void SetMenus(ArkUINodeHandle node, ArkUIBarItem* items, ArkUI_Uint32 length)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(items);
    NavDestinationModelNG::ResetResObj(
        frameNode, NavDestinationPatternType::NAV_DESTINATION, "navDestination.menuItems");
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
        if (!SystemProperties::ConfigChangePerform()) {
            if (items[i].text.value) {
                delete[] items[i].text.value;
                items[i].text.value = nullptr;
            }
            if (items[i].icon.value) {
                delete[] items[i].icon.value;
                items[i].icon.value = nullptr;
            }
        } else {
            if (items[i].text.value && !items[i].isStringText) {
                delete[] items[i].text.value;
                items[i].text.value = nullptr;
            }
            if (items[i].icon.value && !items[i].isStringIcon) {
                delete[] items[i].icon.value;
                items[i].icon.value = nullptr;
            }
        }
    }
    NavDestinationModelNG::SetMenuItems(frameNode, std::move(menuItems));
    if (!SystemProperties::ConfigChangePerform()) {
        return;
    }
    UpdateNavDestinationMenuItem(frameNode, items, length);
}

void ResetMenus(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NavDestinationModelNG::ResetResObj(
        frameNode, NavDestinationPatternType::NAV_DESTINATION, "navDestination.menuItems");
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

void SetNavDestinationCustomTitle(ArkUINodeHandle node, ArkUINodeHandle titleNode)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto* customTitleFrameNode = reinterpret_cast<FrameNode*>(titleNode);
    CHECK_NULL_VOID(customTitleFrameNode);
    NavDestinationModelNG::SetCustomTitle(frameNode, AceType::Claim(customTitleFrameNode));
}

ArkUINodeHandle GetNavDestinationCustomTitle(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, nullptr);
    auto titleNode = NavDestinationModelNG::GetCustomTitle(frameNode);
    CHECK_NULL_RETURN(titleNode, nullptr);
    return reinterpret_cast<ArkUINodeHandle>(AceType::RawPtr(titleNode));
}

void SetNavDestinationTitleHeight(ArkUINodeHandle node, const struct ArkUIDimensionType height)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    Dimension titleHeight = Dimension(height.value, static_cast<OHOS::Ace::DimensionUnit>(height.units));
    NavDestinationModelNG::SetTitleHeight(frameNode, titleHeight, true);
}

void SetNavDestinationTitlebarOptions(ArkUINodeHandle node, ArkUINavigationTitlebarOptions opts)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NG::NavigationTitlebarOptions finalOptions;
    if (opts.colorValue.isSet) {
        finalOptions.bgOptions.color = Color(opts.colorValue.value);
    }
    if (opts.barStyle.isSet) {
        finalOptions.brOptions.barStyle = static_cast<NG::BarStyle>(opts.barStyle.value);
    }
    if (opts.enableHoverMode.isSet) {
        finalOptions.enableHoverMode = opts.enableHoverMode.value;
    }
    NavDestinationModelNG::SetTitlebarOptions(frameNode, std::move(finalOptions));
}

void SetNavDestinationOnCoordScrollStartAction(
    ArkUINodeHandle node, void (*onCoordScrollStartAction)(ArkUINodeHandle node))
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto onCoordScrollStartActionCallBack = [node = AceType::WeakClaim(frameNode), onCoordScrollStartAction]() {
        auto frameNode = node.Upgrade();
        CHECK_NULL_VOID(frameNode);
        auto nodeHandle = reinterpret_cast<ArkUINodeHandle>(AceType::RawPtr(frameNode));
        CHECK_NULL_VOID(onCoordScrollStartAction);
        onCoordScrollStartAction(nodeHandle);
    };
    NavDestinationModelNG::SetOnCoordScrollStartAction(frameNode, std::move(onCoordScrollStartActionCallBack));
}

void ResetNavDestinationOnCoordScrollStartAction(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NavDestinationModelNG::SetOnCoordScrollStartAction(frameNode, nullptr);
}

void SetNavDestinationOnCoordScrollUpdateAction(ArkUINodeHandle node,
    void (*onCoordScrollUpdateAction)(ArkUINodeHandle node, ArkUI_Float32 offset, ArkUI_Float32 currentOffset))
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto onCoordScrollUpdateActionCallBack =
        [node = AceType::WeakClaim(frameNode), onCoordScrollUpdateAction](float offset, float currentOffset)->void {
            auto frameNode = node.Upgrade();
            CHECK_NULL_VOID(frameNode);
            auto nodeHandle = reinterpret_cast<ArkUINodeHandle>(AceType::RawPtr(frameNode));
            CHECK_NULL_VOID(onCoordScrollUpdateAction);
            onCoordScrollUpdateAction(nodeHandle, offset, currentOffset);
        };
    NavDestinationModelNG::SetOnCoordScrollUpdateAction(frameNode, std::move(onCoordScrollUpdateActionCallBack));
}

void ResetNavDestinationOnCoordScrollUpdateAction(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NavDestinationModelNG::SetOnCoordScrollUpdateAction(frameNode, nullptr);
}

void SetNavDestinationOnCoordScrollEndAction(ArkUINodeHandle node, void (*onCoordScrollEndAction)(ArkUINodeHandle node))
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto onCoordScrollEndActionCallBack = [node = AceType::WeakClaim(frameNode), onCoordScrollEndAction]() {
        auto frameNode = node.Upgrade();
        CHECK_NULL_VOID(frameNode);
        auto nodeHandle = reinterpret_cast<ArkUINodeHandle>(AceType::RawPtr(frameNode));
        CHECK_NULL_VOID(onCoordScrollEndAction);
        onCoordScrollEndAction(nodeHandle);
    };
    NavDestinationModelNG::SetOnCoordScrollEndAction(frameNode, std::move(onCoordScrollEndActionCallBack));
}

void ResetNavDestinationOnCoordScrollEndAction(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NavDestinationModelNG::SetOnCoordScrollEndAction(frameNode, nullptr);
}

void SetNavDestinationSystemBarStyle(ArkUINodeHandle node, ArkUI_Uint32 value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    RefPtr<SystemBarStyle> style = SystemBarStyle::CreateStyleFromColor(value);
    NavDestinationModelNG::SetSystemBarStyle(frameNode, style);
}

void ResetNavDestinationSystemBarStyle(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NavDestinationModelNG::SetSystemBarStyle(frameNode, nullptr);
}

void SetCustomBackButtonNode(ArkUINodeHandle node, ArkUINodeHandle backButtonNode)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto* backButton = reinterpret_cast<FrameNode*>(backButtonNode);
    CHECK_NULL_VOID(backButton);
    NavDestinationModelNG::SetCustomBackButtonNode(frameNode, backButton);
}

void SetPreferredOrientation(ArkUINodeHandle node, ArkUI_Int32 ori)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::optional<Orientation> orientation;
    if (ori >= static_cast<int32_t>(Orientation::BEGIN) && ori <= static_cast<int32_t>(Orientation::END)) {
        orientation = static_cast<Orientation>(ori);
    }
    NavDestinationModelNG::SetPreferredOrientation(frameNode, orientation);
}

void ResetPreferredOrientation(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NavDestinationModelNG::SetPreferredOrientation(frameNode, std::nullopt);
}

void SetEnableStatusBar(ArkUINodeHandle node, ArkUIOptionalBool enable, ArkUIOptionalBool animated)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::optional<std::pair<bool, bool>> statusBar;
    if (enable.isSet) {
        std::pair<bool, bool> config;
        config.first = enable.value;
        config.second = false;
        if (animated.isSet) {
            config.second = animated.value;
        }
        statusBar = config;
    }
    NavDestinationModelNG::SetEnableStatusBar(frameNode, statusBar);
}

void ResetEnableStatusBar(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::optional<std::pair<bool, bool>> statusBar;
    NavDestinationModelNG::SetEnableStatusBar(frameNode, statusBar);
}

void SetEnableNavigationIndicator(ArkUINodeHandle node, ArkUIOptionalBool enable)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::optional<bool> navigationIndicator;
    if (enable.isSet) {
        navigationIndicator = enable.value;
    }
    NavDestinationModelNG::SetEnableNavigationIndicator(frameNode, navigationIndicator);
}

void ResetEnableNavigationIndicator(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::optional<bool> navigationIndicator;
    NavDestinationModelNG::SetEnableNavigationIndicator(frameNode, navigationIndicator);
}

void SetNavDestinationOnShown(ArkUINodeHandle node, void* callback)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (callback) {
        auto onShown = reinterpret_cast<std::function<void()>*>(callback);
        NavDestinationModelNG::SetOnShown(frameNode, std::move(*onShown));
    } else {
        NavDestinationModelNG::SetOnShown(frameNode, nullptr);
    }
}

void ResetNavDestinationOnShown(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NavDestinationModelNG::SetOnShown(frameNode, nullptr);
}

void SetNavDestinationOnHidden(ArkUINodeHandle node, void* callback)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (callback) {
        auto onHidden = reinterpret_cast<std::function<void()>*>(callback);
        NavDestinationModelNG::SetOnHidden(frameNode, std::move(*onHidden));
    } else {
        NavDestinationModelNG::SetOnHidden(frameNode, nullptr);
    }
}

void ResetNavDestinationOnHidden(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NavDestinationModelNG::SetOnHidden(frameNode, nullptr);
}

void SetNavDestinationOnWillHide(ArkUINodeHandle node, void* callback)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (callback) {
        auto onWillHide = reinterpret_cast<std::function<void()>*>(callback);
        NavDestinationModelNG::SetOnWillHide(frameNode, std::move(*onWillHide));
    } else {
        NavDestinationModelNG::SetOnWillHide(frameNode, nullptr);
    }
}

void ResetNavDestinationOnWillHide(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NavDestinationModelNG::SetOnWillHide(frameNode, nullptr);
}

void SetNavDestinationOnWillAppear(ArkUINodeHandle node, void* callback)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (callback) {
        auto onWillAppear = reinterpret_cast<std::function<void()>*>(callback);
        NavDestinationModelNG::SetOnWillAppear(frameNode, std::move(*onWillAppear));
    } else {
        NavDestinationModelNG::SetOnWillAppear(frameNode, nullptr);
    }
}

void ResetNavDestinationOnWillAppear(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NavDestinationModelNG::SetOnWillAppear(frameNode, nullptr);
}

void SetNavDestinationOnWillShow(ArkUINodeHandle node, void* callback)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (callback) {
        auto onWillShow = reinterpret_cast<std::function<void()>*>(callback);
        NavDestinationModelNG::SetOnWillShow(frameNode, std::move(*onWillShow));
    } else {
        NavDestinationModelNG::SetOnWillShow(frameNode, nullptr);
    }
}

void ResetNavDestinationOnWillShow(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NavDestinationModelNG::SetOnWillShow(frameNode, nullptr);
}

void SetNavDestinationOnWillDisappear(ArkUINodeHandle node, void* callback)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (callback) {
        auto onWillDisappear = reinterpret_cast<std::function<void()>*>(callback);
        NavDestinationModelNG::SetOnWillDisAppear(frameNode, std::move(*onWillDisappear));
    } else {
        NavDestinationModelNG::SetOnWillDisAppear(frameNode, nullptr);
    }
}

void ResetNavDestinationOnWillDisappear(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NavDestinationModelNG::SetOnWillDisAppear(frameNode, nullptr);
}

void SetNavDestinationOnBackPressed(ArkUINodeHandle node, void* callback)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (callback) {
        auto onBackPressed = reinterpret_cast<std::function<bool()>*>(callback);
        NavDestinationModelNG::SetOnBackPressed(frameNode, std::move(*onBackPressed));
    } else {
        NavDestinationModelNG::SetOnBackPressed(frameNode, nullptr);
    }
}
void ResetNavDestinationOnBackPressed(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NavDestinationModelNG::SetOnBackPressed(frameNode, nullptr);
}

void SetNavDestinationOnReady(ArkUINodeHandle node, void* callback)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (callback) {
        auto onReady = reinterpret_cast<std::function<void(RefPtr<NavDestinationContext>)>*>(callback);
        NavDestinationModelNG::SetOnReady(frameNode, std::move(*onReady));
    } else {
        NavDestinationModelNG::SetOnReady(frameNode, nullptr);
    }
}

void ResetNavDestinationOnReady(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NavDestinationModelNG::SetOnReady(frameNode, nullptr);
}

void SetNavDestinationIsCustomTitleBarSize(ArkUINodeHandle node, ArkUI_Bool isCustom)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NavDestinationModelNG::SetIsCustomTitleBarSize(frameNode, isCustom);
}

void ResetNavDestinationIsCustomTitleBarSize(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NavDestinationModelNG::SetIsCustomTitleBarSize(frameNode, false);
}

void SetNavDestinationBeforeCreateLayoutWrapperCallBack(
    ArkUINodeHandle node, void (*beforeCreateLayoutWrapper)(ArkUINodeHandle node))
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto beforeCreateLayoutWrapperCallBack = [node = AceType::WeakClaim(frameNode), beforeCreateLayoutWrapper]() {
        auto frameNode = node.Upgrade();
        auto nodeHandle = reinterpret_cast<ArkUINodeHandle>(AceType::RawPtr(frameNode));
        beforeCreateLayoutWrapper(nodeHandle);
    };
    NavDestinationModelNG::SetBeforeCreateLayoutWrapperCallBack(
        frameNode, std::move(beforeCreateLayoutWrapperCallBack));
}

void SetTitleAnimationElapsedTime(ArkUINodeHandle node, ArkUI_Int32 elapsedTime)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NavDestinationModelNG::SetTitleAnimationElapsedTime(frameNode, static_cast<int32_t>(elapsedTime));
}
namespace NodeModifier {
const ArkUINavDestinationModifier* GetNavDestinationModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const ArkUINavDestinationModifier modifier = {
        .setHideTitleBar = SetHideTitleBar,
        .resetHideTitleBar = ResetHideTitleBar,
        .setNavDestinationHideToolBar = SetNavDestinationHideToolBar,
        .resetNavDestinationHideToolBar = ResetNavDestinationHideToolBar,
        .setNavDestinationHideBackButton = SetNavDestinationHideBackButton,
        .resetNavDestinationHideBackButton = ResetNavDestinationHideBackButton,
        .setNavDestinationMode = SetNavDestinationMode,
        .resetNavDestinationMode = ResetNavDestinationMode,
        .setIgnoreLayoutSafeArea = SetIgnoreLayoutSafeArea,
        .resetIgnoreLayoutSafeArea = ResetIgnoreLayoutSafeArea,
        .setNavDestinationBackgroundColor = SetNavDestinationBackgroundColor,
        .resetNavDestinationBackgroundColor = ResetNavDestinationBackgroundColor,
        .setNavDestinationBackgroundColorWithColorSpace = SetNavDestinationBackgroundColorWithColorSpace,
        .setTitle = SetTitle,
        .resetTitle = ResetTitle,
        .setMenus = SetMenus,
        .resetMenus = ResetMenus,
        .setMenuItemAction = SetMenuItemAction,
        .setMenuItemSymbol = SetMenuItemSymbol,
        .setRecoverable = SetNavDestinationRecoverable,
        .resetRecoverable = ResetNavDestinationRecoverable,
        .setNavDestinationSystemTransition = SetNavDestinationSystemTransition,
        .resetNavDestinationSystemTransition = ResetNavDestinationSystemTransition,
        .setNavDestinationCustomTitle = SetNavDestinationCustomTitle,
        .getNavDestinationCustomTitle = GetNavDestinationCustomTitle,
        .setNavDestinationTitleHeight = SetNavDestinationTitleHeight,
        .setNavDestinationTitlebarOptions = SetNavDestinationTitlebarOptions,
        .setNavDestinationOnCoordScrollStartAction = SetNavDestinationOnCoordScrollStartAction,
        .resetNavDestinationOnCoordScrollStartAction = ResetNavDestinationOnCoordScrollStartAction,
        .setNavDestinationOnCoordScrollUpdateAction = SetNavDestinationOnCoordScrollUpdateAction,
        .resetNavDestinationOnCoordScrollUpdateAction = ResetNavDestinationOnCoordScrollUpdateAction,
        .setNavDestinationOnCoordScrollEndAction = SetNavDestinationOnCoordScrollEndAction,
        .resetNavDestinationOnCoordScrollEndAction = ResetNavDestinationOnCoordScrollEndAction,
        .setNavDestinationSystemBarStyle = SetNavDestinationSystemBarStyle,
        .resetNavDestinationSystemBarStyle = ResetNavDestinationSystemBarStyle,
        .setCustomBackButtonNode = SetCustomBackButtonNode,
        .setPreferredOrientation = SetPreferredOrientation,
        .resetPreferredOrientation = ResetPreferredOrientation,
        .setEnableStatusBar = SetEnableStatusBar,
        .resetEnableStatusBar = ResetEnableStatusBar,
        .setEnableNavigationIndicator = SetEnableNavigationIndicator,
        .resetEnableNavigationIndicator = ResetEnableNavigationIndicator,
        .setNavDestinationOnShown = SetNavDestinationOnShown,
        .resetNavDestinationOnShown = ResetNavDestinationOnShown,
        .setNavDestinationOnHidden = SetNavDestinationOnHidden,
        .resetNavDestinationOnHidden = ResetNavDestinationOnHidden,
        .setNavDestinationOnWillHide = SetNavDestinationOnWillHide,
        .resetNavDestinationOnWillHide = ResetNavDestinationOnWillHide,
        .setNavDestinationOnWillAppear = SetNavDestinationOnWillAppear,
        .resetNavDestinationOnWillAppear = ResetNavDestinationOnWillAppear,
        .setNavDestinationOnWillShow = SetNavDestinationOnWillShow,
        .resetNavDestinationOnWillShow = ResetNavDestinationOnWillShow,
        .setNavDestinationOnWillDisappear = SetNavDestinationOnWillDisappear,
        .resetNavDestinationOnWillDisappear = ResetNavDestinationOnWillDisappear,
        .setNavDestinationOnBackPressed = SetNavDestinationOnBackPressed,
        .resetNavDestinationOnBackPressed = ResetNavDestinationOnBackPressed,
        .setNavDestinationOnReady = SetNavDestinationOnReady,
        .resetNavDestinationOnReady = ResetNavDestinationOnReady,
        .setNavDestinationIsCustomTitleBarSize = SetNavDestinationIsCustomTitleBarSize,
        .resetNavDestinationIsCustomTitleBarSize = ResetNavDestinationIsCustomTitleBarSize,
        .setNavDestinationBeforeCreateLayoutWrapperCallBack = SetNavDestinationBeforeCreateLayoutWrapperCallBack,
        .setTitleAnimationElapsedTime = SetTitleAnimationElapsedTime,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line

    return &modifier;
}

const CJUINavDestinationModifier* GetCJUINavDestinationModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const CJUINavDestinationModifier modifier = {
        .setHideTitleBar = SetHideTitleBar,
        .resetHideTitleBar = ResetHideTitleBar,
        .setNavDestinationHideToolBar = SetNavDestinationHideToolBar,
        .resetNavDestinationHideToolBar = ResetNavDestinationHideToolBar,
        .setNavDestinationHideBackButton = SetNavDestinationHideBackButton,
        .resetNavDestinationHideBackButton = ResetNavDestinationHideBackButton,
        .setNavDestinationMode = SetNavDestinationMode,
        .resetNavDestinationMode = ResetNavDestinationMode,
        .setIgnoreLayoutSafeArea = SetIgnoreLayoutSafeArea,
        .resetIgnoreLayoutSafeArea = ResetIgnoreLayoutSafeArea,
        .setNavDestinationSystemTransition = SetNavDestinationSystemTransition,
        .resetNavDestinationSystemTransition = ResetNavDestinationSystemTransition,
        .setPreferredOrientation = SetPreferredOrientation,
        .resetPreferredOrientation = ResetPreferredOrientation,
        .setEnableStatusBar = SetEnableStatusBar,
        .resetEnableStatusBar = ResetEnableStatusBar,
        .setEnableNavigationIndicator = SetEnableNavigationIndicator,
        .resetEnableNavigationIndicator = ResetEnableNavigationIndicator,
        .setNavDestinationBackgroundColorWithColorSpace = SetNavDestinationBackgroundColorWithColorSpace,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line

    return &modifier;
}
}
} // namespace OHOS::Ace::NG
