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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TABS_TAB_BAR_ITEM_ACCESSIBILITY_PROPERTY_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TABS_TAB_BAR_ITEM_ACCESSIBILITY_PROPERTY_H

#include "base/utils/utils.h"
#include "core/components_ng/pattern/tabs/tab_bar_pattern.h"
#include "core/components_ng/property/accessibility_property.h"

namespace OHOS::Ace::NG {
class TabBarItemAccessibilityProperty : public AccessibilityProperty {
    DECLARE_ACE_TYPE(TabBarItemAccessibilityProperty, AccessibilityProperty);

public:
    TabBarItemAccessibilityProperty() = default;

    ~TabBarItemAccessibilityProperty() override = default;

    bool IsSelected() const override
    {
        auto tabBarItem = host_.Upgrade();
        CHECK_NULL_RETURN(tabBarItem, false);
        auto tabBar = AceType::DynamicCast<FrameNode>(tabBarItem->GetParent());
        CHECK_NULL_RETURN(tabBar, false);
        auto layoutProperty = tabBar->GetLayoutProperty<TabBarLayoutProperty>();
        CHECK_NULL_RETURN(layoutProperty, false);
        auto selectedIndex = layoutProperty->GetIndicatorValue(0);
        auto index = tabBar->GetChildFlatIndex(tabBarItem->GetId()).second;
        return index == selectedIndex;
    }

    void ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const override
    {
        AccessibilityProperty::ToJsonValue(json, filter);
        json->PutExtAttr("label", GetGroupText(true).c_str(), filter);
    }

private:
    ACE_DISALLOW_COPY_AND_MOVE(TabBarItemAccessibilityProperty);
};
} // namespace OHOS::Ace::NG

#endif
