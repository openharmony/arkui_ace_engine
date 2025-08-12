/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#ifndef FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_NAVDESTINATION_NAVDESTINATION_MODEL_STATIC_H
#define FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_NAVDESTINATION_NAVDESTINATION_MODEL_STATIC_H

#include <optional>
#include <string>

#include "core/components_ng/pattern/navigation/navigation_declaration.h"
#include "core/components_ng/pattern/navigation/navigation_options.h"
#include "core/components_ng/pattern/navrouter/navdestination_context.h"
#include "core/components_ng/pattern/navrouter/navdestination_group_node.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT NavDestinationModelStatic {
public:
    static void SetBackButtonIcon(FrameNode* frameNode, const std::function<void(WeakPtr<NG::FrameNode>)>& iconSymbol,
        const std::string& src, const ImageOption& imageOption, RefPtr<PixelMap>& pixMap,
        const std::vector<std::string>& nameList, bool userDefinedAccessibilityText = false,
        const std::string& backButtonAccessibilityText = "");
    static void SetMenuItems(FrameNode* frameNode, std::vector<NG::BarItem>&& menuItems);
    static void SetMenuOptions(FrameNode* frameNode, NavigationMenuOptions&& opt);
    static void CreateBackButton(const RefPtr<NavDestinationGroupNode>& navDestinationNode);
    static void CreateImageButton(const RefPtr<NavDestinationGroupNode>& navDestinationNode);
    static RefPtr<NG::FrameNode> CreateFrameNode(int32_t nodeId, std::function<void()>&& deepRenderFunc = nullptr);
    static void SetSystemTransitionType(FrameNode* frameNode, NG::NavigationSystemTransitionType type);
    static void SetOnActive(FrameNode* frameNode, std::function<void(int32_t)>&& onActive);
    static void SetOnInactive(FrameNode* frameNode, std::function<void(int32_t)>&& onInactive);
    static void SetHideTitleBar(FrameNode* frameNode, bool hideTitleBar, bool animated = false);
    static void SetOnShown(FrameNode* frameNode, std::function<void()>&& onShow);
    static void SetOnHidden(FrameNode* frameNode, std::function<void()>&& onHidden);
    static void SetOnBackPressed(FrameNode* frameNode, std::function<bool()>&& onBackPressed);
    static void SetNavDestinationMode(FrameNode* frameNode, const std::optional<NavDestinationMode>& mode);
    static void SetOnReady(FrameNode* frameNode, std::function<void(RefPtr<NavDestinationContext>)>&& onReady);
    static void SetOnWillAppear(FrameNode* frameNode, std::function<void()>&& willAppear);
    static void SetOnWillDisAppear(FrameNode* frameNode, std::function<void()>&& willDisAppear);
    static void SetOnWillShow(FrameNode* frameNode, std::function<void()>&& willShow);
    static void SetOnWillHide(FrameNode* frameNode, std::function<void()>&& willHide);
    static void SetRecoverable(FrameNode* frameNode, const std::optional<bool>& recoverable);
    static void SetTitlebarOptions(FrameNode* frameNode, NavigationTitlebarOptions&& opt);
    static void ParseCommonTitle(FrameNode* frameNode, const NG::NavigationTitleInfo& titleInfo);
    static void SetHideToolBar(FrameNode* frameNode, bool hideToolBar, bool animated = false);
    static void SetIgnoreLayoutSafeArea(FrameNode* frameNode, const NG::IgnoreLayoutSafeAreaOpts& opts);
    static void SetToolbarConfiguration(FrameNode* frameNode, std::vector<NG::BarItem>&& toolBarItems);
    static void SetToolBarOptions(FrameNode* frameNode, NavigationToolbarOptions&& opt);
    static void SetToolbarMorebuttonOptions(FrameNode* frameNode, MoreButtonOptions&& opt);
    static void SetCustomMenu(FrameNode* frameNode, const RefPtr<UINode>& customNode);
    static void SetCustomTitle(FrameNode* frameNode, const RefPtr<UINode>& customNode);
    static void SetCustomToolBar(FrameNode* frameNode, const RefPtr<UINode>& customNode);
    static void SetTitleHeight(FrameNode* frameNode, const Dimension& titleHeight, bool isValid = true);
};
} // namespace OHOS::Ace::NG

#endif // FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_NAVDESTINATION_NAVDESTINATION_MODEL_STATIC_H