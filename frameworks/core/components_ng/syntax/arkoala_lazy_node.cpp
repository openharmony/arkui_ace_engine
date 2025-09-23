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
        if (index < liveRange.start || index > liveRange.end) {
            RemoveChild(node);
        } else {
            node->SetActive(index >= activeRange.start && index <= activeRange.end);
        }
    }

    items_.RemoveIf([liveRange](const uint32_t& k, const auto& _) {
        const auto idx = static_cast<int32_t>(k);
        return idx < liveRange.start || idx > liveRange.end;
    });
}

RefPtr<UINode> ArkoalaLazyNode::GetFrameChildByIndex(uint32_t index, bool needBuild, bool isCache, bool addToRenderTree)
{
    const auto indexCasted = static_cast<int32_t>(index);
    TAG_LOGD(AceLogTag::ACE_LAZY_FOREACH,
        "nodeId: %{public}d: GetFrameChildByIndex(%{public}d, %{public}d, %{public}d, %{public}d)",
        GetId(), indexCasted, static_cast<int32_t>(needBuild), static_cast<int32_t>(isCache),
        static_cast<int32_t>(addToRenderTree));

    auto item = GetChildByIndex(indexCasted);
    if (!item && !needBuild) {
        return nullptr;
    }
    if (createItem_) {
        item = createItem_(indexCasted);
    }
    CHECK_NULL_RETURN(item, nullptr);
    items_.Put(indexCasted, item);
    AddChild(item);

    if (isCache) {
        item->SetJSViewActive(false, true);
    } else if (addToRenderTree) {
        item->SetActive(true);
    }

    return item->GetFrameChildByIndex(0, needBuild);
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
} // namespace OHOS::Ace::NG