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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_NAVIGATION_NAVIGATION_LAYOUT_UTIL_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_NAVIGATION_NAVIGATION_LAYOUT_UTIL_H

#include <cstdint>

#include "base/memory/referenced.h"
#include "core/components_ng/layout/layout_algorithm.h"
#include "core/components_ng/layout/layout_wrapper.h"
#include "core/components_ng/pattern/navigation/navdestination_node_base.h"
#include "core/components_ng/pattern/navigation/navdestination_layout_property_base.h"

namespace OHOS::Ace::NG {

class NavigationLayoutUtil {
public:
    static bool CheckWhetherNeedToHideToolbar(
        const RefPtr<NavDestinationNodeBase>& nodeBase, const SizeF& navigationSize);
    static void UpdateTitleBarMenuNode(const RefPtr<NavDestinationNodeBase>& nodeBase, const SizeF& navigationSize);
    static float MeasureToolBar(LayoutWrapper* layoutWrapper, const RefPtr<NavDestinationNodeBase>& nodeBase,
        const RefPtr<NavDestinationLayoutPropertyBase>& layoutPropertyBase, const SizeF& navigationSize);
    static float MeasureToolBarDivider(
        LayoutWrapper* layoutWrapper, const RefPtr<NavDestinationNodeBase>& nodeBase,
        const RefPtr<NavDestinationLayoutPropertyBase>& layoutPropertyBase,
        const SizeF& navigationSize, float toolBarHeight);
    static float LayoutToolBar(
        LayoutWrapper* layoutWrapper, const RefPtr<NavDestinationNodeBase>& nodeBase,
        const RefPtr<NavDestinationLayoutPropertyBase>& layoutPropertyBase, bool isNeedToCreatePaddingAndBorder);
    static void LayoutToolBarDivider(
        LayoutWrapper* layoutWrapper, const RefPtr<NavDestinationNodeBase>& nodeBase,
        const RefPtr<NavDestinationLayoutPropertyBase>& layoutPropertyBase, float toolbarHeight,
        bool isNeedToCreatePaddingAndBorder);
    static void UpdateContentSafeAreaPadding(const RefPtr<NavDestinationNodeBase>& nodeBase, float titleBarHeight);
    static bool EnableToolBarAdaptation(const RefPtr<NavDestinationNodeBase>& nodeBase);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_NAVIGATION_NAVIGATION_LAYOUT_UTIL_H