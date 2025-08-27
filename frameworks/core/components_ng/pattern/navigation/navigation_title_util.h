/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_NAVIGATION_NAVIGATION_TITLE_UTIL_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_NAVIGATION_NAVIGATION_TITLE_UTIL_H

#include "base/memory/referenced.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/pattern/button/button_layout_property.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/image/image_layout_property.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/menu/menu_view.h"
#include "core/components_ng/pattern/menu/wrapper/menu_wrapper_pattern.h"
#include "core/components_ng/pattern/navigation/bar_item_event_hub.h"
#include "core/components_ng/pattern/navigation/bar_item_pattern.h"
#include "core/components_ng/pattern/navigation/navdestination_node_base.h"
#include "core/components_ng/pattern/navigation/navigation_event_hub.h"
#include "core/components_ng/pattern/navigation/navigation_stack.h"
#include "core/components_ng/pattern/navigation/title_bar_layout_property.h"
#include "core/components_ng/pattern/navigation/title_bar_node.h"
#include "core/components_ng/pattern/navrouter/navdestination_context.h"
#include "core/components_ng/pattern/navrouter/navdestination_event_hub.h"
#include "core/components_ng/pattern/navrouter/navdestination_group_node.h"
#include "core/components_ng/pattern/navrouter/navdestination_layout_algorithm.h"
#include "core/components_ng/pattern/navrouter/navdestination_layout_property.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/syntax/shallow_builder.h"

namespace OHOS::Ace::NG {

class NavigationTitleUtil {
public:
    static RefPtr<FrameNode> CreateMenuItems(const int32_t menuNodeId,
        const std::vector<NG::BarItem>& menuItems, const RefPtr<NavDestinationNodeBase>& navDestinationNodeBase,
        bool isButtonEnabled, const std::string& field, const std::string& parentId,
        bool isCreateLandscapeMenu = false);
    static void BuildMoreItemNodeAction(const RefPtr<FrameNode>& buttonNode, const RefPtr<BarItemNode>& barItemNode,
        const RefPtr<FrameNode>& barMenuNode, const MenuParam& menuParam);

    static bool BuildMoreButton(bool isButtonEnabled, const RefPtr<NavigationBarTheme>& theme,
        const RefPtr<NavDestinationNodeBase>& nodeBase, const RefPtr<FrameNode>& menuNode,
        std::vector<OptionParam>&& params, const std::string& field, const std::string& parentId,
        bool isCreateLandscapeMenu);
    static RefPtr<FrameNode> CreateMenuItemNode(
        const RefPtr<NavigationBarTheme>& theme, const BarItem& menuItem, bool isButtonEnabled);
    static RefPtr<FrameNode> CreateMenuItemButton(const RefPtr<NavigationBarTheme>& theme);
    static RefPtr<BarItemNode> CreateBarItemNode(const bool isButtonEnabled, const RefPtr<NavigationBarTheme>& theme);
    static RefPtr<FrameNode> CreateBarItemTextNode(const std::string& text);
    static RefPtr<FrameNode> CreateBarItemIconNode(
        const BarItem& barItem, bool isButtonEnabled, const RefPtr<NavigationBarTheme>& theme);
    static void InitTitleBarButtonEvent(const RefPtr<FrameNode>& buttonNode, const RefPtr<FrameNode>& iconNode,
        bool isMoreButton, const BarItem& menuItem = BarItem(), bool isButtonEnabled = true);
    static void SetAccessibility(const RefPtr<FrameNode>& node, const std::string& message);
    static void UpdateBarItemNodeWithItem(const RefPtr<BarItemNode>& barItemNode, const BarItem& barItem,
        bool isButtonEnabled, const RefPtr<NavigationBarTheme>& theme);
    static void BuildMoreIemNode(
        const RefPtr<BarItemNode>& barItemNode, bool isButtonEnabled, const RefPtr<NavigationBarTheme>& theme);
    static uint32_t GetOrInitMaxMenuNums(
        const RefPtr<NavigationBarTheme>& theme, const RefPtr<NavDestinationNodeBase>& navDestinationNodeBase);
    static std::string GetTitleString(const RefPtr<TitleBarNode>& titleBarNode, bool isCustom);
    static std::string GetSubtitleString(const RefPtr<TitleBarNode>& titleBarNode);

    static void SetInnerChildId(const RefPtr<FrameNode>& node, const std::string& field, const std::string& nodeTag,
        const std::string& nodeValue, const std::string& parentId)
    {
        // navigation/navdestination Field + nodeTag + nodeValue + parentId
        std::string id;
        id.append(field);
        id.append(nodeTag);
        id.append("__");
        id.append(nodeValue);
        id.append("__");
        id.append(parentId);
        CHECK_NULL_VOID(node);
        node->UpdateInspectorId(id);
    }

    static float ParseCalcDimensionToPx(const std::optional<CalcDimension>& value, const float titleBarWidth);

    static void CreateOrUpdateMainTitle(const RefPtr<TitleBarNode>& titleBarNode,
        const NG::NavigationTitleInfo& titleInfo, bool ignoreMainTitle);
    static void CreateOrUpdateSubtitle(const RefPtr<TitleBarNode>& titleBarNode,
        const NG::NavigationTitleInfo& titleInfo);
    static void CreateOrUpdateDestinationMainTitle(const RefPtr<TitleBarNode>& titleBarNode,
        const NG::NavigationTitleInfo& titleInfo);
    static void CreateOrUpdateDestinationSubtitle(const RefPtr<TitleBarNode>& titleBarNode,
        const NG::NavigationTitleInfo& titleInfo);

    static float CalculateTitlebarOffset(const RefPtr<UINode>& titleBarNode);
    static void FoldStatusChangedAnimation(const RefPtr<FrameNode>& host);

    static bool IsNeedHoverModeAction(const RefPtr<TitleBarNode>& titleBarNode);

    static RefPtr<FrameNode> CreatePopupDialogNode(const RefPtr<FrameNode> targetNode,
        const std::vector<NG::BarItem>& menuItems, int32_t index, int32_t themeScopeId);
    static RefPtr<FrameNode> CreateSymbolDialog(
        const std::string& message, const RefPtr<FrameNode>& targetNode, int32_t themeScopeId);
    static void UpdateTitleOrToolBarTranslateYAndOpacity(const RefPtr<NavDestinationNodeBase>& nodeBase,
        const RefPtr<FrameNode>& barNode, float translate, bool isTitle);
    static bool IsTitleBarHasOffsetY(const RefPtr<FrameNode>& titleBarNode);
    static bool SetTitleAnimationElapsedTime(AnimationOption& option, const RefPtr<FrameNode>& pushEnterNode);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_NAVIGATION_NAVIGATION_TITLE_UTIL_H