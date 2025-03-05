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

#include "core/components_ng/pattern/list/list_item_accessibility_property.h"

#if defined(OHOS_STANDARD_SYSTEM) and !defined(ACE_UNITTEST)
#include "accessibility_element_info.h"
#endif

#include "core/components_ng/pattern/list/list_item_pattern.h"

namespace OHOS::Ace::NG {
bool ListItemAccessibilityProperty::IsSelected() const
{
    auto frameNode = host_.Upgrade();
    CHECK_NULL_RETURN(frameNode, false);
    auto listItemPattern = frameNode->GetPattern<ListItemPattern>();
    CHECK_NULL_RETURN(listItemPattern, false);
    return listItemPattern->IsSelected();
}

void ListItemAccessibilityProperty::SetSpecificSupportAction()
{
    auto frameNode = host_.Upgrade();
    CHECK_NULL_VOID(frameNode);
    auto listItemPattern = frameNode->GetPattern<ListItemPattern>();
    CHECK_NULL_VOID(listItemPattern);

    auto swiperIndex = listItemPattern->GetSwiperIndex();
    auto swipeActionState = listItemPattern->GetSwipeActionState();

    if (listItemPattern->HasStartNode()) {
        if (swipeActionState == SwipeActionState::EXPANDED && swiperIndex == ListItemSwipeIndex::SWIPER_START) {
            AddSupportAction(AceAction::ACTION_SCROLL_FORWARD);
        } else if (swipeActionState == SwipeActionState::COLLAPSED) {
            AddSupportAction(AceAction::ACTION_SCROLL_BACKWARD);
        }
    }
    if (listItemPattern->HasEndNode()) {
        if (swipeActionState == SwipeActionState::EXPANDED && swiperIndex == ListItemSwipeIndex::SWIPER_END) {
            AddSupportAction(AceAction::ACTION_SCROLL_BACKWARD);
        } else if (swipeActionState == SwipeActionState::COLLAPSED) {
            AddSupportAction(AceAction::ACTION_SCROLL_FORWARD);
        }
    }
    AddSupportAction(AceAction::ACTION_SELECT);
    AddSupportAction(AceAction::ACTION_CLEAR_SELECTION);
}

void ListItemAccessibilityProperty::GetExtraElementInfo(Accessibility::ExtraElementInfo& extraElementInfo)
{
#if defined(OHOS_STANDARD_SYSTEM) and !defined(ACE_UNITTEST)
    auto frameNode = host_.Upgrade();
    CHECK_NULL_VOID(frameNode);
    auto listItemPattern = frameNode->GetPattern<ListItemPattern>();
    CHECK_NULL_VOID(listItemPattern);
    extraElementInfo.SetExtraElementInfo("ListItemIndex", listItemPattern->GetIndexInList());
    std::string stateStr;
    switch (listItemPattern->GetSwipeActionState()) {
        case SwipeActionState::COLLAPSED:
            stateStr = "collapsed";
            break;
        case SwipeActionState::EXPANDED:
            stateStr = "expanded";
            break;
        case SwipeActionState::ACTIONING:
            break;
    }

    if (!listItemPattern->HasStartNode() && !listItemPattern->HasEndNode()) {
        stateStr = "disabled";
    }

    std::string axisStr;
    switch (listItemPattern->GetAxis()) {
        case Axis::VERTICAL:
            axisStr = "vertical";
            break;
        case Axis::HORIZONTAL:
            axisStr = "horizontal";
            break;
        case Axis::FREE:
            axisStr = "free";
            break;
        case Axis::NONE:
            axisStr = "none";
            break;
    }
    extraElementInfo.SetExtraElementInfo("expandedState", stateStr);
    extraElementInfo.SetExtraElementInfo("direction", axisStr);
#endif
}
} // namespace OHOS::Ace::NG
