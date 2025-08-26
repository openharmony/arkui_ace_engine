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

#include "core/components_ng/syntax/arkoala_lazy_node.h"

#include "core/components_ng/pattern/list/list_item_pattern.h"

namespace OHOS::Ace::NG {
void ArkoalaLazyNode::DoSetActiveChildRange(
    int32_t start, int32_t end, int32_t cacheStart, int32_t cacheEnd, bool showCache)
{
    TAG_LOGD(AceLogTag::ACE_LAZY_FOREACH,
        "nodeId: %{public}d: DoSetActiveChildRange(%{public}d, %{public}d, %{public}d, %{public}d, %{public}d)",
        GetId(), start, end, cacheStart, cacheEnd, static_cast<int32_t>(showCache));
    struct Range {
        int32_t start;
        int32_t end;
    };
    const Range liveRange { start - cacheStart, end + cacheEnd };
    if (updateRange_) {
        updateRange_(liveRange.start, liveRange.end);
    }

    const auto activeRange = showCache ? liveRange : Range { start, end };
    std::list<RefPtr<UINode>> toRemove;
    for (const auto& [index, nodeWeak] : items_) {
        auto node = nodeWeak.Upgrade();
        if (!node) {
            continue;
        }
        const auto indexMapped = ConvertFromToIndexRevert(index);
        if (indexMapped < liveRange.start || indexMapped > liveRange.end) {
            RemoveChild(node);
        } else {
            node->SetActive(indexMapped >= activeRange.start && indexMapped <= activeRange.end);
        }
    }

    items_.RemoveIf([liveRange, weak = WeakClaim(this)](const uint32_t& k, const auto& _) {
        const auto idx = static_cast<int32_t>(k);
        auto arkoalaLazyNode = weak.Upgrade();
        if (!arkoalaLazyNode) {
            return idx < liveRange.start || idx > liveRange.end;
        }
        const auto indexMapped = arkoalaLazyNode->ConvertFromToIndexRevert(idx);
        return indexMapped < liveRange.start || indexMapped > liveRange.end;
    });
}

RefPtr<UINode> ArkoalaLazyNode::GetFrameChildByIndex(uint32_t index, bool needBuild, bool isCache, bool addToRenderTree)
{
    const auto indexCasted = static_cast<int32_t>(index);
    TAG_LOGD(AceLogTag::ACE_LAZY_FOREACH,
        "nodeId: %{public}d: GetFrameChildByIndex(%{public}d, %{public}d, %{public}d, %{public}d)",
        GetId(), indexCasted, static_cast<int32_t>(needBuild), static_cast<int32_t>(isCache),
        static_cast<int32_t>(addToRenderTree));

    const auto indexMapped = ConvertFromToIndex(indexCasted);
    auto item = GetChildByIndex(indexMapped);
    if (!item && !needBuild) {
        return nullptr;
    }
    if (createItem_) {
        item = createItem_(indexMapped);
    }
    CHECK_NULL_RETURN(item, nullptr);
    items_.Put(indexMapped, item);
    AddChild(item);

    if (isCache) {
        item->SetJSViewActive(false, true);
    } else if (addToRenderTree) {
        item->SetActive(true);
    }

    auto childNode = item->GetFrameChildByIndex(0, needBuild);
    if (onMoveEvent_) {
        InitDragManager(AceType::DynamicCast<FrameNode>(childNode));
    }
    return childNode;
}

RefPtr<UINode> ArkoalaLazyNode::GetChildByIndex(int32_t index)
{
    auto item = items_.Get(index);
    return item ? item->Upgrade() : nullptr;
}

RefPtr<FrameNode> ArkoalaLazyNode::GetFrameNode(int32_t index)
{
    return AceType::DynamicCast<FrameNode>(GetFrameChildByIndex(index, false, false, false));
}

void ArkoalaLazyNode::OnDataChange(int32_t changeIndex, int32_t count, NotificationType type)
{
    // temp: naive data reset
    for (const auto& [index, nodeWeak] : items_) {
        auto node = nodeWeak.Upgrade();
        if (index >= changeIndex) {
            RemoveChild(node);
        }
    }
    items_.RemoveIf([changeIndex](const uint32_t& k, const auto& _) {
        const auto idx = static_cast<int32_t>(k);
        return idx >= changeIndex;
    });

    auto parent = GetParent();
    int64_t accessibilityId = GetAccessibilityId();
    if (parent) {
        parent->NotifyChange(changeIndex, count, accessibilityId, type);
        parent->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    }
}

void ArkoalaLazyNode::SetOnMove(std::function<void(int32_t, int32_t)>&& onMove)
{
    if (onMove && !onMoveEvent_) {
        TAG_LOGI(AceLogTag::ACE_LAZY_FOREACH, "activate onMove");
        InitAllChildrenDragManager(true);
    } else if (!onMove && onMoveEvent_) {
        TAG_LOGI(AceLogTag::ACE_LAZY_FOREACH, "deactivate onMove");
        InitAllChildrenDragManager(false);
    }
    onMoveEvent_ = onMove;
}

void ArkoalaLazyNode::SetOnMoveFromTo(std::function<void(int32_t, int32_t)>&& onMoveFromTo)
{
    onMoveFromTo_ = onMoveFromTo;
}

void ArkoalaLazyNode::SetItemDragEvent(std::function<void(int32_t)>&& onLongPress,
    std::function<void(int32_t)>&& onDragStart, std::function<void(int32_t, int32_t)>&& onMoveThrough,
    std::function<void(int32_t)>&& onDrop)
{
    if (onMoveEvent_) {
        onLongPressEvent_ = onLongPress;
        onDragStartEvent_ = onDragStart;
        onMoveThroughEvent_ = onMoveThrough;
        onDropEvent_ = onDrop;
    }
}

void ArkoalaLazyNode::MoveData(int32_t from, int32_t to)
{
    if (from == to) {
        return;
    }
    // move the child in children_ list.
    auto& children = ModifyChildren();
    if (children.empty()) {
        TAG_LOGI(AceLogTag::ACE_LAZY_FOREACH, "children is empty.");
        return;
    }
    auto startIter = children.begin();
    auto startOpt = items_.GetKey(*startIter);
    if (!startOpt.has_value()) {
        TAG_LOGI(AceLogTag::ACE_LAZY_FOREACH, "cannot find start child in items.");
        return;
    }
    int32_t childrenStartIndex = ConvertFromToIndexRevert(startOpt.value());
    auto fromIter = children.begin();
    std::advance(fromIter, from - childrenStartIndex);
    if (fromIter == children.end()) {
        TAG_LOGI(AceLogTag::ACE_LAZY_FOREACH, "from index out of range.");
        return;
    }
    auto child = *fromIter;
    TraversingCheck(child);
    fromIter = children.erase(fromIter);
    std::advance(fromIter, to - from);
    children.insert(fromIter, child);
    
    UpdateMoveFromTo(from, to);
    onMoveFromTo_(from, to);
    MarkNeedSyncRenderTree(true);
    MarkNeedFrameFlushDirty(PROPERTY_UPDATE_MEASURE_SELF_AND_PARENT | PROPERTY_UPDATE_BY_CHILD_REQUEST);
}

int32_t ArkoalaLazyNode::GetFrameNodeIndex(const RefPtr<FrameNode>& node, bool /*isExpanded*/)
{
    if (node == nullptr) {
        TAG_LOGI(AceLogTag::ACE_LAZY_FOREACH, "GetFrameNodeIndex node is null");
        return -1;
    }
    // todo: if repeat and lazyforeach can be distinguished, index can be get directly from items_ map.
    for (const auto& [index, nodeWeak] : items_) {
        auto iterNode = nodeWeak.Upgrade();
        if (!iterNode) {
            continue;
        }
        RefPtr<FrameNode> frameNode = AceType::DynamicCast<FrameNode>(iterNode->GetFrameChildByIndex(0, false));
        if (frameNode == node) {
            return ConvertFromToIndexRevert(index);
        }
    }
    return -1;
}

void ArkoalaLazyNode::UpdateMoveFromTo(int32_t from, int32_t to)
{
    if (moveFromTo_) {
        moveFromTo_.value().second = to;
        if (moveFromTo_.value().second == moveFromTo_.value().first) {
            moveFromTo_.reset();
        }
    } else {
        moveFromTo_ = { from, to };
    }
}

void ArkoalaLazyNode::FireOnMove(int32_t from, int32_t to)
{
    // 1. update items_ map.
    UpdateItemsForOnMove();
    // 2. reset moveFromTo_.
    ResetMoveFromTo();
    // 3. call onMoveFromTo_ to notify TS to update its _activeItems.
    // -1 used to reset moveFromTo_ in TS.
    onMoveFromTo_(-1, -1);
    // 4. call base class to fire onMove event defined by user.
    ForEachBaseNode::FireOnMove(from, to);
}

void ArkoalaLazyNode::UpdateItemsForOnMove()
{
    if (!moveFromTo_) {
        return;
    }

    int32_t from = moveFromTo_.value().first;
    int32_t to = moveFromTo_.value().second;
    if (from == to) {
        return;
    }

    int32_t rangeStart = std::min(from, to);
    int32_t rangeEnd = std::max(from, to);
    UniqueValuedMap<int32_t, WeakPtr<UINode>, WeakPtr<UINode>::Hash> tempItems = std::move(items_);
    items_.Clear();
    for (const auto& [index, nodeWeak] : tempItems) {
        auto node = nodeWeak.Upgrade();
        if (!node) {
            continue;
        }
        if (index < rangeStart || index > rangeEnd) {
            items_.Put(index, node);
            continue;
        }
        int32_t newIndex = ConvertFromToIndexRevert(index);
        items_.Put(newIndex, node);
    }
}

void ArkoalaLazyNode::InitDragManager(const RefPtr<FrameNode>& child)
{
    CHECK_NULL_VOID(child);
    auto parentNode = GetParentFrameNode();
    CHECK_NULL_VOID(parentNode);
    if (parentNode->GetTag() != V2::LIST_ETS_TAG) {
        return;
    }
    auto pattern = child->GetPattern<ListItemPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->InitDragManager(AceType::Claim(this));
}

void ArkoalaLazyNode::InitAllChildrenDragManager(bool init)
{
    auto parentNode = GetParentFrameNode();
    CHECK_NULL_VOID(parentNode);
    if (parentNode->GetTag() != V2::LIST_ETS_TAG) {
        return;
    }
    for (const auto& [index, nodeWeak] : items_) {
        auto child = nodeWeak.Upgrade();
        if (!child) {
            continue;
        }
        auto childNode = child->GetFrameChildByIndex(0, false);
        auto listItem = AceType::DynamicCast<FrameNode>(childNode);
        if (!listItem) {
            continue;
        }

        auto pattern = listItem->GetPattern<ListItemPattern>();
        if (!pattern) {
            continue;
        }
        if (init) {
            pattern->InitDragManager(AceType::Claim(this));
        } else {
            pattern->DeInitDragManager();
        }
    }
}
} // namespace OHOS::Ace::NG