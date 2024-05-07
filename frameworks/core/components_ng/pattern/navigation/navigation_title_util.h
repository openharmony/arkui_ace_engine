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
    static RefPtr<FrameNode> CreateMenuItems(const int32_t menuNodeId, const std::vector<NG::BarItem>& menuItems,
        RefPtr<TitleBarNode> titleBarNode, const bool isButtonEnabled);
    static void BuildMoreItemNodeAction(const RefPtr<FrameNode>& buttonNode, const RefPtr<BarItemNode>& barItemNode,
        const RefPtr<FrameNode>& barMenuNode, const RefPtr<TitleBarNode>& titleBarNode);

    static RefPtr<FrameNode> CreateMenuItemNode(
        RefPtr<NavigationBarTheme> theme, const BarItem& menuItem, bool isButtonEnabled);
    static RefPtr<FrameNode> CreateMenuItemButton(RefPtr<NavigationBarTheme> theme);
    static RefPtr<BarItemNode> CreateBarItemNode(const bool isButtonEnabled);
    static RefPtr<FrameNode> CreateBarItemTextNode(const std::string& text);
    static RefPtr<FrameNode> CreateBarItemIconNode(const BarItem& barItem, bool isButtonEnabled);
    static void InitTitleBarButtonEvent(const RefPtr<FrameNode>& buttonNode, const RefPtr<FrameNode>& iconNode,
        bool isMoreButton,  BarItem menuItem = BarItem(), bool isButtonEnabled = true);
    static void UpdateBarItemNodeWithItem(
        const RefPtr<BarItemNode>& barItemNode, const BarItem& barItem, bool isButtonEnabled);
    static void BuildMoreIemNode(const RefPtr<BarItemNode>& barItemNode, bool isButtonEnabled);
    static uint32_t GetOrInitMaxMenuNums(RefPtr<NavigationBarTheme>& theme, RefPtr<TitleBarNode> titleBarNode);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_NAVIGATION_NAVIGATION_TITLE_UTIL_H