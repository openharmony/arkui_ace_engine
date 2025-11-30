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

#include "core/components_ng/pattern/scrollable/selectable_utils.h"

#include "core/components_ng/pattern/scrollable/selectable_container_pattern.h"
#include "core/components_ng/pattern/scrollable/selectable_item_event_hub.h"
#include "core/components_ng/pattern/scrollable/selectable_item_pattern.h"

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

bool SelectableUtils::IsGatherSelectedItemsAnimationEnabled(RefPtr<FrameNode>& frameNode)
{
    CHECK_NULL_RETURN(frameNode, false);
    CHECK_NULL_RETURN(SelectableUtils::IsSelectedItemNode(frameNode), false);
    auto parent = FindItemParentNode(frameNode);
    CHECK_NULL_RETURN(parent, false);
    auto pattern = parent->GetPattern<SelectableContainerPattern>();
    CHECK_NULL_RETURN(pattern, false);
    return pattern->GetEditModeOptions().enableGatherSelectedItemsAnimation;
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