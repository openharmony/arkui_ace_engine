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
#include "core/interfaces/native/node/navigation_modifier.h"

#include "core/components_ng/pattern/navigation/navigation_model_ng.h"
#include "core/components_ng/pattern/navigation/nav_bar_pattern.h"

namespace OHOS::Ace::NG {
constexpr int32_t NAV_BAR_POSITION_RANGE_MODIFIER = 1;
constexpr int32_t NAVIGATION_MODE_RANGE_MODIFIER = 2;
constexpr int32_t DEFAULT_NAV_BAR_WIDTH_FOR_MODIFIER = 240;
constexpr int32_t DEFAULT_SAFE_AREA_TYPE = 0b1;
constexpr int32_t DEFAULT_SAFE_AREA_EDGE = 0b1111;
void SetHideToolBar(ArkUINodeHandle node, ArkUI_Bool hide, ArkUI_Bool animated)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NavigationModelNG::SetHideToolBar(frameNode, hide, animated);
}

void ResetHideToolBar(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NavigationModelNG::SetHideToolBar(frameNode, false, false);
}

void SetEnableModeChangeAnimation(ArkUINodeHandle node, ArkUI_Bool isEnable)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NavigationModelNG::SetEnableModeChangeAnimation(frameNode, isEnable);
}

void ResetEnableModeChangeAnimation(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NavigationModelNG::SetEnableModeChangeAnimation(frameNode, true);
}

void SetSplitPlaceholder(ArkUINodeHandle node, ArkUINodeHandle splitPlaceholder)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto splitPlaceholderNode = reinterpret_cast<FrameNode*>(splitPlaceholder);
    CHECK_NULL_VOID(splitPlaceholderNode);
    NavigationModelNG::SetSplitPlaceholder(frameNode, splitPlaceholderNode);
}

void ResetSplitPlaceholder(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NavigationModelNG::ResetSplitPlaceholder(frameNode);
}

void SetMinContentWidth(ArkUINodeHandle node, ArkUI_Float32 value, int unit, void* minContentWidthRawPtr)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NavigationModelNG::ResetResObj(frameNode, NavigationPatternType::NAVIGATION, "navigation.minContentWidth");
    CalcDimension width = Dimension(value, static_cast<OHOS::Ace::DimensionUnit>(unit));
    if (!SystemProperties::ConfigChangePerform() || !minContentWidthRawPtr) {
        NavigationModelNG::SetMinContentWidth(frameNode, width);
    } else {
        auto* minContentWidth = reinterpret_cast<ResourceObject*>(minContentWidthRawPtr);
        auto minContentWidthResObj = AceType::Claim(minContentWidth);
        NavigationModelNG::SetMinContentWidth(frameNode, minContentWidthResObj);
    }
}

void ResetMinContentWidth(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NavigationModelNG::ResetResObj(frameNode, NavigationPatternType::NAVIGATION, "navigation.minContentWidth");
    NavigationModelNG::SetMinContentWidth(frameNode, DEFAULT_MIN_CONTENT_WIDTH);
}

void SetMinNavBarWidth(ArkUINodeHandle node, ArkUI_Float32 minValue, int minUnit, void* minNavBarWidthRawPtr)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NavigationModelNG::ResetResObj(
        frameNode, NavigationPatternType::NAVIGATION, "navigation.navBarWidthRange.minNavBarWidth");
    CalcDimension minNavBarWidth = Dimension(minValue, static_cast<OHOS::Ace::DimensionUnit>(minUnit));
    if (LessNotEqual(minNavBarWidth.Value(), 0.0)) {
        minNavBarWidth = DEFAULT_MIN_NAV_BAR_WIDTH;
    }

    if (!SystemProperties::ConfigChangePerform() || !minNavBarWidthRawPtr) {
        NavigationModelNG::SetMinNavBarWidth(frameNode, minNavBarWidth);
    } else {
        auto* minNavBarWidthObj = reinterpret_cast<ResourceObject*>(minNavBarWidthRawPtr);
        auto minNavBarWidthResObj = AceType::Claim(minNavBarWidthObj);
        NavigationModelNG::SetMinNavBarWidth(frameNode, minNavBarWidthResObj);
    }
}

void ResetMinNavBarWidth(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NavigationModelNG::ResetResObj(
        frameNode, NavigationPatternType::NAVIGATION, "navigation.navBarWidthRange.minNavBarWidth");
    CalcDimension minNavBarWidth = DEFAULT_MIN_NAV_BAR_WIDTH;
    NavigationModelNG::SetMinNavBarWidth(frameNode, minNavBarWidth);
}

void SetMaxNavBarWidth(ArkUINodeHandle node, ArkUI_Float32 maxValue, int maxUnit, void* maxNavBarWidthRawPtr)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NavigationModelNG::ResetResObj(
        frameNode, NavigationPatternType::NAVIGATION, "navigation.navBarWidthRange.maxNavBarWidth");
    CalcDimension maxNavBarWidth = Dimension(maxValue, static_cast<OHOS::Ace::DimensionUnit>(maxUnit));
    if (LessNotEqual(maxNavBarWidth.Value(), 0.0)) {
        maxNavBarWidth = DEFAULT_MAX_NAV_BAR_WIDTH;
    }

    if (!SystemProperties::ConfigChangePerform() || !maxNavBarWidthRawPtr) {
        NavigationModelNG::SetMaxNavBarWidth(frameNode, maxNavBarWidth);
    } else {
        auto* maxNavBarWidthObj = reinterpret_cast<ResourceObject*>(maxNavBarWidthRawPtr);
        auto maxNavBarWidthResObj = AceType::Claim(maxNavBarWidthObj);
        NavigationModelNG::SetMaxNavBarWidth(frameNode, maxNavBarWidthResObj);
    }
}

void ResetMaxNavBarWidth(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NavigationModelNG::ResetResObj(
        frameNode, NavigationPatternType::NAVIGATION, "navigation.navBarWidthRange.maxNavBarWidth");
    CalcDimension maxNavBarWidth = DEFAULT_MAX_NAV_BAR_WIDTH;
    NavigationModelNG::SetMaxNavBarWidth(frameNode, maxNavBarWidth);
}

void SetNavBarWidth(ArkUINodeHandle node, ArkUI_Float32 value, int unit, void* widthRawPtr)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NavigationModelNG::ResetResObj(frameNode, NavigationPatternType::NAVIGATION, "navigation.navBarWidth");
    CalcDimension width = Dimension(value, static_cast<OHOS::Ace::DimensionUnit>(unit));
    if (!SystemProperties::ConfigChangePerform() || !widthRawPtr) {
        NavigationModelNG::SetNavBarWidth(frameNode, width);
    } else {
        auto* widthObj = reinterpret_cast<ResourceObject*>(widthRawPtr);
        auto widthResObj = AceType::Claim(widthObj);
        NavigationModelNG::SetNavBarWidth(frameNode, widthResObj);
    }
}

void ResetNavBarWidth(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NavigationModelNG::ResetResObj(frameNode, NavigationPatternType::NAVIGATION, "navigation.navBarWidth");
    CalcDimension navBarWidth;
    navBarWidth.SetValue(DEFAULT_NAV_BAR_WIDTH_FOR_MODIFIER);
    NavigationModelNG::SetNavBarWidth(frameNode, navBarWidth);
}

void SetNavBarPosition(ArkUINodeHandle node, int32_t value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (value >= 0 && value <= NAV_BAR_POSITION_RANGE_MODIFIER) {
        NavigationModelNG::SetNavBarPosition(frameNode, static_cast<NG::NavBarPosition>(value));
    } else {
        NavigationModelNG::SetNavBarPosition(frameNode, NG::NavBarPosition::START);
    }
}

void ResetNavBarPosition(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NavigationModelNG::SetNavBarPosition(frameNode, NG::NavBarPosition::START);
}

void SetHideNavBar(ArkUINodeHandle node, ArkUI_Bool hideNavBar)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NavigationModelNG::SetHideNavBar(frameNode, hideNavBar);
}

void ResetHideNavBar(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NavigationModelNG::SetHideNavBar(frameNode, false);
}

void SetSubtitle(ArkUINodeHandle node, const char* subtitle)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::string value = subtitle;
    NavigationModelNG::SetSubtitle(frameNode, value);
}

void ResetSubtitle(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NavigationModelNG::SetSubtitle(frameNode, "");
}

void SetHideBackButton(ArkUINodeHandle node, ArkUI_Bool hideBackButton)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NavigationModelNG::SetHideBackButton(frameNode, hideBackButton);
}

void ResetHideBackButton(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NavigationModelNG::SetHideBackButton(frameNode, false);
}

void SetTitleMode(ArkUINodeHandle node, int32_t value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NavigationModelNG::SetTitleMode(frameNode, static_cast<NG::NavigationTitleMode>(value));
}

void ResetTitleMode(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NavigationModelNG::SetTitleMode(frameNode, NG::NavigationTitleMode::FREE);
}

void SetUsrNavigationMode(ArkUINodeHandle node, int32_t value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (value >= 0 && value <= NAVIGATION_MODE_RANGE_MODIFIER) {
        NavigationModelNG::SetUsrNavigationMode(frameNode, static_cast<NG::NavigationMode>(value));
    } else {
        NavigationModelNG::SetUsrNavigationMode(frameNode, NG::NavigationMode::AUTO);
    }
}
void ResetUsrNavigationMode(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NavigationModelNG::SetUsrNavigationMode(frameNode, NG::NavigationMode::AUTO);
}

void SetNavHideTitleBar(ArkUINodeHandle node, ArkUI_Bool hide, ArkUI_Bool animated)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NavigationModelNG::SetHideTitleBar(frameNode, hide, animated);
}

void ResetNavHideTitleBar(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NavigationModelNG::SetHideTitleBar(frameNode, false, false);
}

void SetNavIgnoreLayoutSafeArea(ArkUINodeHandle node, const char* typeStr, const char* edgesStr)
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
        NavigationModelNG::SetIgnoreLayoutSafeArea(frameNode, opts);
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
    NavigationModelNG::SetIgnoreLayoutSafeArea(frameNode, opts);
}

void ResetNavIgnoreLayoutSafeArea(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NG::SafeAreaExpandOpts opts;
    opts.type = DEFAULT_SAFE_AREA_TYPE;
    opts.edges = DEFAULT_SAFE_AREA_EDGE;
    NavigationModelNG::SetIgnoreLayoutSafeArea(frameNode, opts);
}

void UpdateNavigationTitlebarOptions(FrameNode* frameNode, ArkUINavigationTitlebarOptions options)
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
        NavigationModelNG::SetTitlebarOptions(AceType::RawPtr(frameNode), std::move(localFinalOptions));
        frameNode->MarkModifyDone();
        frameNode->MarkDirtyNode();
    };
    auto pattern = frameNode->GetPattern();
    CHECK_NULL_VOID(pattern);
    pattern->AddResObj("navigationModifier.titlebarOptions", resObj, std::move(updateFunc));
}

void SetNavTitle(ArkUINodeHandle node, ArkUINavigationTitleInfo titleInfo, ArkUINavigationTitlebarOptions options,
    void* titleRawPtr, void* subtitleRawPtr)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NavigationModelNG::ResetResObj(frameNode, NavigationPatternType::TITLE_BAR, "navigation.title.commonMainTitle");
    NavigationModelNG::ResetResObj(frameNode, NavigationPatternType::TITLE_BAR, "navigation.title.commonSubTitle");
    NavigationModelNG::ResetResObj(frameNode, NavigationPatternType::NAVIGATION, "navigationModifier.titlebarOptions");
    std::string mainTitleString = std::string(titleInfo.mainTitle);
    std::string subTitleString = std::string(titleInfo.subTitle);
    NG::NavigationTitleInfo ngTitleInfo = { titleInfo.hasSubTitle, titleInfo.hasMainTitle,
        subTitleString, mainTitleString };
    if (SystemProperties::ConfigChangePerform() && (titleRawPtr || subtitleRawPtr)) {
        auto* title = reinterpret_cast<ResourceObject*>(titleRawPtr);
        auto titleResObj = AceType::Claim(title);
        auto* subtitle = reinterpret_cast<ResourceObject*>(subtitleRawPtr);
        auto subtitleResObj = AceType::Claim(subtitle);
        NavigationModelNG::ParseCommonTitle(frameNode, titleResObj, subtitleResObj);
    } else {
        NavigationModelNG::ParseCommonTitle(frameNode, ngTitleInfo);
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
    NavigationModelNG::SetTitlebarOptions(frameNode, std::move(finalOptions));
    if (SystemProperties::ConfigChangePerform()) {
        UpdateNavigationTitlebarOptions(frameNode, options);
    }
}

void ResetNavTitle(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NavigationModelNG::ResetResObj(frameNode, NavigationPatternType::TITLE_BAR, "navigation.title.commonMainTitle");
    NavigationModelNG::ResetResObj(frameNode, NavigationPatternType::TITLE_BAR, "navigation.title.commonSubTitle");
    NavigationModelNG::ResetResObj(frameNode, NavigationPatternType::NAVIGATION, "navigationModifier.titlebarOptions");
    NG::NavigationTitleInfo ngTitleInfo = { false, false, "", "" };
    NavigationModelNG::ParseCommonTitle(frameNode, ngTitleInfo);
    NavigationTitlebarOptions options;
    NavigationModelNG::SetTitlebarOptions(frameNode, std::move(options));
}

void UpdateNavigationMenuItem(FrameNode* frameNode, ArkUIBarItem* items, ArkUI_Uint32 length)
{
    CHECK_NULL_VOID(frameNode);
    RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>("", "", -1);
    auto&& updateFunc = [wekNode = AceType::WeakClaim(frameNode),
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
        auto localMenuItems = menuItems;
        auto frameNode = wekNode.Upgrade();
        CHECK_NULL_VOID(frameNode);
        NavigationModelNG::SetMenuItems(AceType::RawPtr(frameNode), std::move(localMenuItems));
        frameNode->MarkModifyDone();
        frameNode->MarkDirtyNode();
    };
    auto pattern = frameNode->GetPattern();
    CHECK_NULL_VOID(pattern);
    pattern->AddResObj("navigationModifier.menuItems", resObj, std::move(updateFunc));
}

void SetNavMenus(ArkUINodeHandle node, ArkUIBarItem* items, ArkUI_Uint32 length)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NavigationModelNG::ResetResObj(frameNode, NavigationPatternType::NAVIGATION, "navigationModifier.menuItems");
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
    NavigationModelNG::SetMenuItems(frameNode, std::move(menuItems));
    if (!SystemProperties::ConfigChangePerform()) {
        return;
    }
    UpdateNavigationMenuItem(frameNode, items, length);
}

void ResetNavMenus(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NavigationModelNG::ResetResObj(frameNode, NavigationPatternType::NAVIGATION, "navigationModifier.menuItems");
    std::vector<NG::BarItem> menuItems;
    NavigationModelNG::SetMenuItems(frameNode, std::move(menuItems));
}

void SetNavMenuItemAction(ArkUINodeHandle node, void* action, ArkUI_Uint32 index)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto actionFunc = reinterpret_cast<std::function<void()>*>(action);
    NavigationModelNG::SetMenuItemAction(frameNode, std::move(*actionFunc), index);
}

void SetNavMenuItemSymbol(ArkUINodeHandle node, void* symbol, ArkUI_Uint32 index)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto iconFunc = reinterpret_cast<std::function<void(WeakPtr<NG::FrameNode>)>*>(symbol);
    NavigationModelNG::SetMenuItemSymbol(frameNode, std::move(*iconFunc), index);
}

void SetNavigationRecoverable(ArkUINodeHandle node, ArkUI_Bool recoverable)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NavigationModelNG::SetRecoverable(frameNode, recoverable);
}

void ResetNavigationRecoverable(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    // default value of navigation's recoverable is false
    NavigationModelNG::SetRecoverable(frameNode, false);
}

void SetEnableDragBar(ArkUINodeHandle node, ArkUI_Bool enableDragBar)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NavigationModelNG::SetEnableDragBar(frameNode, enableDragBar);
}

void ResetEnableDragBar(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    // default value of navigation's enableDragBar is false
    NavigationModelNG::SetEnableDragBar(frameNode, false);
}

void SetCustomTitle(ArkUINodeHandle node, ArkUINodeHandle titleNode)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto* customTitleFrameNode = reinterpret_cast<FrameNode*>(titleNode);
    CHECK_NULL_VOID(customTitleFrameNode);
    NavigationModelNG::SetCustomTitle(frameNode, AceType::Claim(customTitleFrameNode));
}

ArkUINodeHandle GetCustomTitle(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, nullptr);
    auto titleNode = NavigationModelNG::GetCustomTitle(frameNode);
    CHECK_NULL_RETURN(titleNode, nullptr);
    return reinterpret_cast<ArkUINodeHandle>(AceType::RawPtr(titleNode));
}

void SetTitleHeight(ArkUINodeHandle node, const struct ArkUIDimensionType height)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    Dimension titleHeight = Dimension(height.value, static_cast<OHOS::Ace::DimensionUnit>(height.units));
    NavigationModelNG::SetTitleHeight(frameNode, titleHeight, true);
}

void SetTitlebarOptions(ArkUINodeHandle node, ArkUINavigationTitlebarOptions opts)
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
    NavigationModelNG::SetTitlebarOptions(frameNode, std::move(finalOptions));
}

void SetOnCoordScrollStartAction(ArkUINodeHandle node, void (*onCoordScrollStartAction)(ArkUINodeHandle node))
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto onCoordScrollStartActionCallBack = [node = AceType::WeakClaim(frameNode), onCoordScrollStartAction]() {
        auto frameNode = node.Upgrade();
        auto nodeHandle = reinterpret_cast<ArkUINodeHandle>(AceType::RawPtr(frameNode));
        onCoordScrollStartAction(nodeHandle);
    };
    NavigationModelNG::SetOnCoordScrollStartAction(frameNode, std::move(onCoordScrollStartActionCallBack));
}

void SetOnCoordScrollUpdateAction(ArkUINodeHandle node,
    void (*onCoordScrollUpdateAction)(ArkUINodeHandle node, ArkUI_Float32 currentOffset))
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto onCoordScrollUpdateActionCallBack =
        [node = AceType::WeakClaim(frameNode), onCoordScrollUpdateAction](float currentOffset)->void {
            auto frameNode = node.Upgrade();
            auto nodeHandle = reinterpret_cast<ArkUINodeHandle>(AceType::RawPtr(frameNode));
            onCoordScrollUpdateAction(nodeHandle, currentOffset);
        };
    NavigationModelNG::SetOnCoordScrollUpdateAction(frameNode, std::move(onCoordScrollUpdateActionCallBack));
}

void SetOnCoordScrollEndAction(ArkUINodeHandle node, void (*onCoordScrollEndAction)(ArkUINodeHandle node))
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto onCoordScrollEndActionCallBack = [node = AceType::WeakClaim(frameNode), onCoordScrollEndAction]() {
        auto frameNode = node.Upgrade();
        auto nodeHandle = reinterpret_cast<ArkUINodeHandle>(AceType::RawPtr(frameNode));
        onCoordScrollEndAction(nodeHandle);
    };
    NavigationModelNG::SetOnCoordScrollEndAction(frameNode, std::move(onCoordScrollEndActionCallBack));
}

void SetSystemBarStyle(ArkUINodeHandle node, ArkUI_Uint32 value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    RefPtr<SystemBarStyle> style = SystemBarStyle::CreateStyleFromColor(value);
    NavigationModelNG::SetSystemBarStyle(frameNode, style);
}

void ResetSystemBarStyle(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NavigationModelNG::SetSystemBarStyle(frameNode, nullptr);
}

void SetEnableToolBarAdaptation(ArkUINodeHandle node, ArkUI_Bool enable)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NavigationModelNG::SetEnableToolBarAdaptation(frameNode, enable);
}

void ResetEnableToolBarAdaptation(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NavigationModelNG::SetEnableToolBarAdaptation(frameNode, false);
}

void SetOnNavigationModeChange(ArkUINodeHandle node, void* callback)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (callback) {
        auto onModeChange = reinterpret_cast<std::function<void(NG::NavigationMode)>*>(callback);
        NavigationModelNG::SetOnNavigationModeChange(frameNode, std::move(*onModeChange));
    } else {
        NavigationModelNG::SetOnNavigationModeChange(frameNode, nullptr);
    }
}

void ResetOnNavigationModeChange(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NavigationModelNG::SetOnNavigationModeChange(frameNode, nullptr);
}

void SetOnTitleModeChange(ArkUINodeHandle node, void* callback, void* eventInfoFunc)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (callback && eventInfoFunc) {
        auto onTitleModeChange = reinterpret_cast<std::function<void(NG::NavigationTitleMode)>*>(callback);
        auto eventInfo = reinterpret_cast<std::function<void(const BaseEventInfo*)>*>(eventInfoFunc);
        NavigationModelNG::SetOnTitleModeChange(frameNode, std::move(*onTitleModeChange), std::move(*eventInfo));
    } else {
        NavigationModelNG::SetOnTitleModeChange(frameNode, nullptr, nullptr);
    }
}

void ResetOnTitleModeChange(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NavigationModelNG::SetOnTitleModeChange(frameNode, nullptr, nullptr);
}

void SetNavigationIsCustomAnimation(ArkUINodeHandle node, ArkUI_Bool isCustom)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NavigationModelNG::SetIsCustomAnimation(frameNode, isCustom);
}

void ResetNavigationIsCustomAnimation(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NavigationModelNG::SetIsCustomAnimation(frameNode, false);
}

void SetToolBar(ArkUINodeHandle node, ArkUIBarItem* items, ArkUI_Uint32 length)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(items);
    std::vector<NG::BarItem> toolBarItems;
    for (uint32_t i = 0; i < length; i++) {
        NG::BarItem menuItem;
        if (items[i].text.isSet) {
            menuItem.text = items[i].text.value;
        }
        if (items[i].icon.isSet) {
            menuItem.icon = items[i].icon.value;
        }
        toolBarItems.push_back(menuItem);
        if (items[i].text.value) {
            delete[] items[i].text.value;
            items[i].text.value = nullptr;
        }
        if (items[i].icon.value) {
            delete[] items[i].icon.value;
            items[i].icon.value = nullptr;
        }
    }
    NavigationModelNG::SetToolBarItems(frameNode, std::move(toolBarItems));
}

void ResetToolBar(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::vector<NG::BarItem> toolBarItems;
    NavigationModelNG::SetToolBarItems(frameNode, std::move(toolBarItems));
}

void SetOnNavBarStateChange(ArkUINodeHandle node, void* callback)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (callback) {
        auto onNavBarStateChange = reinterpret_cast<std::function<void(bool)>*>(callback);
        NavigationModelNG::SetOnNavBarStateChange(frameNode, std::move(*onNavBarStateChange));
    } else {
        NavigationModelNG::SetOnNavBarStateChange(frameNode, nullptr);
    }
}

void ResetOnNavBarStateChange(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NavigationModelNG::SetOnNavBarStateChange(frameNode, nullptr);
}

void SetBeforeCreateLayoutWrapperCallBack(ArkUINodeHandle node, void (*beforeCreateLayoutWrapper)(ArkUINodeHandle node))
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto beforeCreateLayoutWrapperCallBack = [node = AceType::WeakClaim(frameNode), beforeCreateLayoutWrapper]() {
        auto frameNode = node.Upgrade();
        auto nodeHandle = reinterpret_cast<ArkUINodeHandle>(AceType::RawPtr(frameNode));
        beforeCreateLayoutWrapper(nodeHandle);
    };
    NavigationModelNG::SetBeforeCreateLayoutWrapperCallBack(frameNode, std::move(beforeCreateLayoutWrapperCallBack));
}
namespace NodeModifier {
const ArkUINavigationModifier* GetNavigationModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const ArkUINavigationModifier modifier = {
        .setHideToolBar = SetHideToolBar,
        .resetHideToolBar = ResetHideToolBar,
        .setEnableModeChangeAnimation = SetEnableModeChangeAnimation,
        .resetEnableModeChangeAnimation = ResetEnableModeChangeAnimation,
        .setHideNavBar = SetHideNavBar,
        .resetHideNavBar = ResetHideNavBar,
        .setTitleMode = SetTitleMode,
        .resetTitleMode = ResetTitleMode,
        .setHideBackButton = SetHideBackButton,
        .resetHideBackButton = ResetHideBackButton,
        .setSubtitle = SetSubtitle,
        .resetSubtitle = ResetSubtitle,
        .resetUsrNavigationMode = ResetUsrNavigationMode,
        .setUsrNavigationMode = SetUsrNavigationMode,
        .setNavHideTitleBar = SetNavHideTitleBar,
        .resetNavHideTitleBar = ResetNavHideTitleBar,
        .setNavBarPosition = SetNavBarPosition,
        .resetNavBarPosition = ResetNavBarPosition,
        .setMinContentWidth = SetMinContentWidth,
        .resetMinContentWidth = ResetMinContentWidth,
        .setMaxNavBarWidth = SetMaxNavBarWidth,
        .resetMaxNavBarWidth = ResetMaxNavBarWidth,
        .setMinNavBarWidth = SetMinNavBarWidth,
        .resetMinNavBarWidth = ResetMinNavBarWidth,
        .setNavBarWidth = SetNavBarWidth,
        .resetNavBarWidth = ResetNavBarWidth,
        .setNavIgnoreLayoutSafeArea = SetNavIgnoreLayoutSafeArea,
        .resetNavIgnoreLayoutSafeArea = ResetNavIgnoreLayoutSafeArea,
        .setNavTitle = SetNavTitle,
        .resetNavTitle = ResetNavTitle,
        .setNavMenus = SetNavMenus,
        .resetNavMenus = ResetNavMenus,
        .setNavMenuItemAction = SetNavMenuItemAction,
        .setNavMenuItemSymbol = SetNavMenuItemSymbol,
        .setRecoverable = SetNavigationRecoverable,
        .resetRecoverable = ResetNavigationRecoverable,
        .setEnableDragBar = SetEnableDragBar,
        .resetEnableDragBar = ResetEnableDragBar,
        .setCustomTitle = SetCustomTitle,
        .getCustomTitle = GetCustomTitle,
        .setTitleHeight = SetTitleHeight,
        .setTitlebarOptions = SetTitlebarOptions,
        .setOnCoordScrollStartAction = SetOnCoordScrollStartAction,
        .setOnCoordScrollUpdateAction = SetOnCoordScrollUpdateAction,
        .setOnCoordScrollEndAction = SetOnCoordScrollEndAction,
        .setSystemBarStyle = SetSystemBarStyle,
        .resetSystemBarStyle = ResetSystemBarStyle,
        .setSplitPlaceholder = SetSplitPlaceholder,
        .resetSplitPlaceholder = ResetSplitPlaceholder,
        .setEnableToolBarAdaptation = SetEnableToolBarAdaptation,
        .resetEnableToolBarAdaptation = ResetEnableToolBarAdaptation,
        .setOnNavigationModeChange = SetOnNavigationModeChange,
        .resetOnNavigationModeChange = ResetOnNavigationModeChange,
        .setOnTitleModeChange = SetOnTitleModeChange,
        .resetOnTitleModeChange = ResetOnTitleModeChange,
        .setNavigationIsCustomAnimation = SetNavigationIsCustomAnimation,
        .resetNavigationIsCustomAnimation = ResetNavigationIsCustomAnimation,
        .setToolBar = SetToolBar,
        .resetToolBar = ResetToolBar,
        .setOnNavBarStateChange = SetOnNavBarStateChange,
        .resetOnNavBarStateChange = ResetOnNavBarStateChange,
        .setBeforeCreateLayoutWrapperCallBack = SetBeforeCreateLayoutWrapperCallBack,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line

    return &modifier;
}

const CJUINavigationModifier* GetCJUINavigationModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const CJUINavigationModifier modifier = {
        .setHideToolBar = SetHideToolBar,
        .resetHideToolBar = ResetHideToolBar,
        .setEnableModeChangeAnimation = SetEnableModeChangeAnimation,
        .resetEnableModeChangeAnimation = ResetEnableModeChangeAnimation,
        .setHideNavBar = SetHideNavBar,
        .resetHideNavBar = ResetHideNavBar,
        .setTitleMode = SetTitleMode,
        .resetTitleMode = ResetTitleMode,
        .setHideBackButton = SetHideBackButton,
        .resetHideBackButton = ResetHideBackButton,
        .setSubtitle = SetSubtitle,
        .resetSubtitle = ResetSubtitle,
        .resetUsrNavigationMode = ResetUsrNavigationMode,
        .setUsrNavigationMode = SetUsrNavigationMode,
        .setNavHideTitleBar = SetNavHideTitleBar,
        .resetNavHideTitleBar = ResetNavHideTitleBar,
        .setNavBarPosition = SetNavBarPosition,
        .resetNavBarPosition = ResetNavBarPosition,
        .setMinContentWidth = SetMinContentWidth,
        .resetMinContentWidth = ResetMinContentWidth,
        .setMaxNavBarWidth = SetMaxNavBarWidth,
        .resetMaxNavBarWidth = ResetMaxNavBarWidth,
        .setMinNavBarWidth = SetMinNavBarWidth,
        .resetMinNavBarWidth = ResetMinNavBarWidth,
        .setNavBarWidth = SetNavBarWidth,
        .resetNavBarWidth = ResetNavBarWidth,
        .setNavIgnoreLayoutSafeArea = SetNavIgnoreLayoutSafeArea,
        .resetNavIgnoreLayoutSafeArea = ResetNavIgnoreLayoutSafeArea,
        .setEnableToolBarAdaptation = SetEnableToolBarAdaptation,
        .resetEnableToolBarAdaptation = ResetEnableToolBarAdaptation,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line

    return &modifier;
}
}
} // namespace OHOS::Ace::NG
