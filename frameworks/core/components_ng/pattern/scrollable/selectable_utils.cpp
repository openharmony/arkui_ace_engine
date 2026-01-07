/*
 * Copyright (c) 2025-2026 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/scrollable/selectable_utils.h"

#include "core/components_ng/pattern/scrollable/selectable_container_pattern.h"
#include "core/components_ng/pattern/scrollable/selectable_item_event_hub.h"
#include "core/components_ng/pattern/scrollable/selectable_item_pattern.h"

namespace OHOS::Ace {
SINGLETON_INSTANCE_IMPL(NG::SelectableUtils);
}

namespace OHOS::Ace::NG {
namespace {
RefPtr<FrameNode> FindItemParentNode(const RefPtr<FrameNode>& frameNode)
{
    CHECK_NULL_RETURN(frameNode, nullptr);
    auto parentType = frameNode->GetTag() == V2::GRID_ITEM_ETS_TAG ? V2::GRID_ETS_TAG : V2::LIST_ETS_TAG;
    auto uiNode = frameNode->GetParent();
    CHECK_NULL_RETURN(uiNode, nullptr);
    while (uiNode->GetTag() != parentType) {
        uiNode = uiNode->GetParent();
        CHECK_NULL_RETURN(uiNode, nullptr);
    }
    return AceType::DynamicCast<FrameNode>(uiNode);
}

PreviewBadge GetSelectedPreviewBadge(const RefPtr<FrameNode>& frameNode)
{
    PreviewBadge badge;
    CHECK_NULL_RETURN(frameNode, badge);
    auto parent = FindItemParentNode(frameNode);
    CHECK_NULL_RETURN(parent, badge);
    auto pattern = parent->GetPattern<SelectableContainerPattern>();
    CHECK_NULL_RETURN(pattern, badge);
    if (pattern->GetEditModeOptions().getPreviewBadge) {
        return pattern->GetEditModeOptions().getPreviewBadge();
    }
    return badge;
}
} // namespace

bool SelectableUtils::IsSelectableItem(const RefPtr<FrameNode>& frameNode)
{
    CHECK_NULL_RETURN(frameNode, false);
    auto itemPattern = frameNode->GetPattern<SelectableItemPattern>();
    return itemPattern != nullptr;
}

bool SelectableUtils::IsSelectedItemNode(const RefPtr<FrameNode>& frameNode)
{
    CHECK_NULL_RETURN(frameNode, false);
    auto itemPattern = frameNode->GetPattern<SelectableItemPattern>();
    CHECK_NULL_RETURN(itemPattern, false);
    return itemPattern->IsSelected();
}

std::optional<int32_t> SelectableUtils::GetBadgeNumber(const RefPtr<FrameNode>& frameNode)
{
    auto badgeNumber = frameNode->GetDragPreviewOption().GetCustomerBadgeNumber();
    if (badgeNumber.has_value()) {
        return badgeNumber;
    }
    if (IsGatherSelectedItemsAnimationEnabled(frameNode)) {
        auto badge = GetSelectedPreviewBadge(frameNode);
        if (badge.mode == PreviewBadgeMode::USER_SET) {
            badgeNumber = badge.count > 1 ? badge.count : 1;
        }
        if (badge.mode == PreviewBadgeMode::NO_BADGE) {
            badgeNumber = 1;
        }
    }
    return badgeNumber;
}

std::vector<RefPtr<FrameNode>> SelectableUtils::GetVisibleSelectedItems(const RefPtr<FrameNode>& frameNode)
{
    std::vector<RefPtr<FrameNode>> result;
    CHECK_NULL_RETURN(frameNode, result);
    auto itemPattern = frameNode->GetPattern<SelectableItemPattern>();
    CHECK_NULL_RETURN(itemPattern, result);

    auto parentType = frameNode->GetTag() == V2::GRID_ITEM_ETS_TAG ? V2::GRID_ETS_TAG : V2::LIST_ETS_TAG;
    auto uiNode = frameNode->GetParent();
    CHECK_NULL_RETURN(uiNode, result);
    while (uiNode->GetTag() != parentType) {
        uiNode = uiNode->GetParent();
        CHECK_NULL_RETURN(uiNode, result);
    }
    auto fatherNode = AceType::DynamicCast<FrameNode>(uiNode);
    CHECK_NULL_RETURN(fatherNode, result);
    auto scrollPattern = fatherNode->GetPattern<SelectableContainerPattern>();
    CHECK_NULL_RETURN(scrollPattern, result);
    return scrollPattern->GetVisibleSelectedItems();
}

bool SelectableUtils::IsGatherSelectedItemsAnimationEnabled(const RefPtr<FrameNode>& frameNode)
{
    CHECK_NULL_RETURN(frameNode, false);
    CHECK_NULL_RETURN(SelectableUtils::IsSelectedItemNode(frameNode), false);
    auto parent = FindItemParentNode(frameNode);
    CHECK_NULL_RETURN(parent, false);
    auto pattern = parent->GetPattern<SelectableContainerPattern>();
    CHECK_NULL_RETURN(pattern, false);
    auto scrollableEvent = pattern->GetScrollableEvent();
    CHECK_NULL_RETURN(scrollableEvent, pattern->GetEditModeOptions().enableGatherSelectedItemsAnimation);
    return pattern->GetEditModeOptions().enableGatherSelectedItemsAnimation &&
           scrollableEvent->IsSwipeActionCollapsed();
}

void SelectableUtils::BindContextMenu(FrameNode* frameNode)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<SelectableItemEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->BindContextMenu();
}

void SelectableUtils::PublishMenuStatus(bool isShowing, const RefPtr<FrameNode>& menuNode)
{
    if (isShowing) {
        menuNode_ = menuNode;
    } else {
        auto frameNode = menuNode_.Upgrade();
        CHECK_NULL_VOID(frameNode);
        auto eventHub = frameNode->GetEventHub<SelectableItemEventHub>();
        CHECK_NULL_VOID(eventHub);
        eventHub->RestoreGatherNode();
    }
}
} // namespace OHOS::Ace::NG