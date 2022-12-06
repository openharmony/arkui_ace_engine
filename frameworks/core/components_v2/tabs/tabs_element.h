/*
 * Copyright (c) 2021-2022 Huawei Device Co., Ltd.
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
#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_V2_TABS_TABS_ELEMENT_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_V2_TABS_TABS_ELEMENT_H

#include <vector>

#include "core/components/tab_bar/tab_bar_element.h"
#include "core/pipeline/base/component_group_element.h"

namespace OHOS::Ace::V2 {

class TabsElement : public ComponentGroupElement, public FocusGroup {
    DECLARE_ACE_TYPE(TabsElement, FocusGroup, ComponentGroupElement);
public:
    void PerformBuild() override;
    void AddPendingTabBarItem(const RefPtr<TabBarItemComponent>& item)
    {
        tabBarPendingItems_.push_back(item);
    }
    bool RequestNextFocus(bool vertical, bool reverse, const Rect& rect) override;

private:
    // In case TabBar is at the end position, we create TabBarItems before
    // TabBar itself and have to store them here till TabBar created.
    std::vector<RefPtr<TabBarItemComponent>> tabBarPendingItems_;
    bool isVertical_ = true;
};

} // namespace OHOS::Ace::V2

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_V2_TABS_TABS_ELEMENT_H
