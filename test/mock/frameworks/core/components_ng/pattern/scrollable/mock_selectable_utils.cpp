/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

namespace OHOS::Ace::NG {
RefPtr<FrameNode> SelectableUtils::FindItemParentNode(const RefPtr<FrameNode>& frameNode)
{
    (void)frameNode;
    return nullptr;
}

bool SelectableUtils::IsSelectableItem(const RefPtr<FrameNode>& frameNode)
{
    (void)frameNode;
    return false;
}

bool SelectableUtils::IsSelectedItemNode(const RefPtr<FrameNode>& frameNode)
{
    (void)frameNode;
    return false;
}

std::optional<int32_t> SelectableUtils::GetBadgeNumber(const RefPtr<FrameNode>& frameNode)
{
    (void)frameNode;
    return std::nullopt;
}

std::vector<RefPtr<FrameNode>> SelectableUtils::GetVisibleSelectedItems(const RefPtr<FrameNode>& frameNode)
{
    (void)frameNode;
    return {};
}

bool SelectableUtils::IsGatherSelectedItemsAnimationEnabled(const RefPtr<FrameNode>& frameNode)
{
    (void)frameNode;
    return false;
}

bool SelectableUtils::IsDefaultMultiSelectStyleEnabled(const RefPtr<FrameNode>& frameNode)
{
    (void)frameNode;
    return false;
}

void SelectableUtils::BindContextMenu(FrameNode* frameNode)
{
    (void)frameNode;
}

void SelectableUtils::PublishMenuStatus(bool isShowing, const RefPtr<FrameNode>& menuNode)
{
    (void)isShowing;
    (void)menuNode;
}
} // namespace OHOS::Ace::NG
