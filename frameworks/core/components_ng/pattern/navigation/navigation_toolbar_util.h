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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_NAVIGATION_NAVIGATION_TOOLBAR_UTIL_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_NAVIGATION_NAVIGATION_TOOLBAR_UTIL_H

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/pattern/navigation/navdestination_node_base.h"
#include "core/components_ng/pattern/navigation/navigation_declaration.h"
#include "core/components_ng/pattern/navigation/navigation_options.h"

namespace OHOS::Ace::NG {
struct FieldProperty {
    std::string parentId;
    std::string field;
};
class NavigationToolbarUtil {
public:
    static void CreateToolBarDividerNodeIfNeeded(const RefPtr<NavDestinationNodeBase>& nodeBase);
    static void SetToolbarConfiguration(const RefPtr<NavDestinationNodeBase>& nodeBase,
        std::vector<NG::BarItem>&& toolBarItems, bool enabled, const FieldProperty& fieldProperty);
    static void SetCustomToolBar(const RefPtr<NavDestinationNodeBase>& nodeBase, const RefPtr<AceType>& customNode);
    static void SetToolbarOptions(const RefPtr<NavDestinationNodeBase>& nodeBase, NavigationToolbarOptions&& opt);
    static void MountToolBar(
        const RefPtr<NavDestinationNodeBase>& nodeBase, bool& needRunToolBarAnimation);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_NAVIGATION_NAVIGATION_TOOLBAR_UTIL_H