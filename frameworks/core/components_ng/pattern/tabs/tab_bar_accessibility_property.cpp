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

#include "core/components_ng/pattern/tabs/tab_bar_accessibility_property.h"

#include "base/log/log.h"
#include "base/utils/utils.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/swiper/swiper_pattern.h"
#include "core/components_ng/pattern/tabs/tab_bar_pattern.h"
#include "core/components_ng/pattern/tabs/tabs_node.h"

namespace OHOS::Ace::NG {
int32_t TabBarAccessibilityProperty::GetCollectionItemCounts() const
{
    auto frameNode = host_.Upgrade();
    CHECK_NULL_RETURN(frameNode, 0);
    auto tabsFrameNode = AceType::DynamicCast<TabsNode>(frameNode->GetParent());
    CHECK_NULL_RETURN(tabsFrameNode, false);
    auto swiperFrameNode = AceType::DynamicCast<FrameNode>(tabsFrameNode->GetTabs());
    CHECK_NULL_RETURN(swiperFrameNode, false);
    auto swiperPattern = swiperFrameNode->GetPattern<SwiperPattern>();
    CHECK_NULL_RETURN(swiperPattern, false);
    return swiperPattern->TotalCount();
}

bool TabBarAccessibilityProperty::IsScrollable() const
{
    auto frameNode = host_.Upgrade();
    CHECK_NULL_RETURN(frameNode, false);
    auto tabBarPattern = frameNode->GetPattern<TabBarPattern>();
    CHECK_NULL_RETURN(tabBarPattern, false);
    auto tabBarLayoutProperty = tabBarPattern->GetLayoutProperty<TabBarLayoutProperty>();
    CHECK_NULL_RETURN(tabBarLayoutProperty, false);
    if (tabBarLayoutProperty->GetTabBarMode().value_or(TabBarMode::FIXED) == TabBarMode::SCROLLABLE &&
        GetCollectionItemCounts() > 1 && tabBarPattern->CanScroll()) {
        return true;
    }
    return false;
}

int32_t TabBarAccessibilityProperty::GetBeginIndex() const
{
    if (GetCollectionItemCounts() < 1) {
        return AccessibilityProperty::GetBeginIndex();
    } else {
        return 0;
    }
}

int32_t TabBarAccessibilityProperty::GetCurrentIndex() const
{
    auto frameNode = host_.Upgrade();
    CHECK_NULL_RETURN(frameNode, -1);
    auto tabBarPattern = frameNode->GetPattern<TabBarPattern>();
    CHECK_NULL_RETURN(tabBarPattern, -1);
    if (GetCollectionItemCounts() < 1) {
        return AccessibilityProperty::GetCurrentIndex();
    }
    auto indicator = tabBarPattern->GetIndicator();
    return indicator;
}

void TabBarAccessibilityProperty::SetSpecificSupportAction()
{
    auto frameNode = host_.Upgrade();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<TabBarPattern>();
    CHECK_NULL_VOID(pattern);
    if (IsScrollable()) {
        if (!(pattern->IsAtTop())) {
            AddSupportAction(AceAction::ACTION_SCROLL_BACKWARD);
        }
        if (!(pattern->IsAtBottom())) {
            AddSupportAction(AceAction::ACTION_SCROLL_FORWARD);
        }
    }
}
} // namespace OHOS::Ace::NG
