/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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
#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_V2_TABS_TABS_ELEMENT_CPP
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_V2_TABS_TABS_ELEMENT_CPP

#include "core/components_v2/tabs/tabs_element.h"

#include "core/components/tab_bar/tab_bar_element.h"
#include "core/components_v2/tabs/tabs_helper.h"

namespace OHOS::Ace::V2 {

void TabsElement::PerformBuild()
{
    tabBarPendingItems_.clear();
    ComponentGroupElement::PerformBuild();

    if (!tabBarPendingItems_.empty()) {
        auto tabBarElement = AceType::DynamicCast<TabBarElement>
            (TabsHelper::FindFirstChildOfType<TabBarElement>(AceType::Claim(this)));
        if (!tabBarElement) {
            tabBarPendingItems_.clear();
            LOGE("TabBar missing");
            return;
        }
        for (const auto& item : tabBarPendingItems_) {
            tabBarElement->GetTabBarComponent()->UpdateItemStyle(item);
            tabBarElement->UpdateChild(nullptr, item);
        }
    }
    tabBarPendingItems_.clear();
    auto tabsComponent = AceType::DynamicCast<TabsComponent>(component_);
    CHECK_NULL_VOID(tabsComponent);
    isVertical_ = (tabsComponent->GetDirection() == FlexDirection::COLUMN ||
                       tabsComponent->GetDirection() == FlexDirection::COLUMN_REVERSE);
}

bool TabsElement::RequestNextFocus(bool vertical, bool reverse, const Rect& rect)
{
    if (isVertical_ != vertical) {
        return false;
    }
    return GoToNextFocus(reverse, rect);
}

} // namespace OHOS::Ace::V2

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_V2_TABS_TABS_ELEMENT_CPP
