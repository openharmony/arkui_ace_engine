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

#include "core/components_ng/syntax/repeat_virtual_scroll_2_caches.h"

#include <cstdint>
#include <optional>
#include <unordered_map>
#include <unordered_set>

#include "base/log/log_wrapper.h"
#include "base/memory/referenced.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"

namespace OHOS::Ace::NG {

using CacheItem = RepeatVirtualScroll2Caches::CacheItem;
using OptCacheItem = RepeatVirtualScroll2Caches::OptCacheItem;
using GetFrameChildResult = RepeatVirtualScroll2Caches::GetFrameChildResult;

RefPtr<RepeatVirtualScroll2CacheItem> RepeatVirtualScroll2CacheItem::MakeCacheItem(RefPtr<UINode>& node, bool isL1)
{
    return MakeRefPtr<RepeatVirtualScroll2CacheItem>(node, isL1);
}

RepeatVirtualScroll2Caches::RepeatVirtualScroll2Caches(
    const std::function<std::pair<RIDType, uint32_t>(IndexType)>& onGetRid4Index)
    : onGetRid4Index_(onGetRid4Index)
{}

/**
 * Return a FrameNode child for give index
 */
GetFrameChildResult RepeatVirtualScroll2Caches::GetFrameChild(IndexType index, bool needBuild)
{
    TAG_LOGD(AceLogTag::ACE_REPEAT, "GetFrameChild(index %{public}d, needBuild: %{public}d)", index,
        static_cast<int32_t>(needBuild));
    index = ConvertFromToIndex(index);
    OptCacheItem optCacheItem = GetL1CacheItem4Index(index);
    if (optCacheItem.has_value()) {
        return std::pair<uint32_t, CacheItem>(OnGetRid4IndexResult::UNCHANGED_NODE, optCacheItem.value());
    }

    if (!needBuild) {
        return std::pair<uint32_t, CacheItem>(OnGetRid4IndexResult::NO_NODE, nullptr);
    }

    optCacheItem = CallOnGetRid4Index(index);
    return optCacheItem.has_value()
               ? std::pair<uint32_t, CacheItem>(OnGetRid4IndexResult::UPDATED_NODE, optCacheItem.value())
               : std::pair<uint32_t, CacheItem>(OnGetRid4IndexResult::NO_NODE, nullptr);
}

/**
 * Function called from TS:
 * purge UINode with given id
 * i.e. remove map entry rid -> CacheItem
 */
void RepeatVirtualScroll2Caches::RemoveNode(RIDType rid)
{
    TAG_LOGD(AceLogTag::ACE_REPEAT, "RemoveNode(rid : %{public}d)", static_cast<int32_t>(rid));

    DropFromL1ByRid(rid);

    const auto iter = cacheItem4Rid_.find(rid);
    if (iter != cacheItem4Rid_.end()) {
        cacheItem4Rid_.erase(iter);
    }
}

/**
 * Function called from TS:
 * drop RID from L1
 * mark CacheItem for rid as invalid
 */
void RepeatVirtualScroll2Caches::SetInvalid(RIDType rid)
{
    TAG_LOGD(AceLogTag::ACE_REPEAT, "SetInvalid(rid : %{public}d)", static_cast<int32_t>(rid));
    DropFromL1ByRid(rid);
}

/**
 * drop given rid from the L1
 * see DropFromL1ByIndex
 */
void RepeatVirtualScroll2Caches::DropFromL1ByRid(RIDType rid)
{
    for (const auto iter : l1Rid4Index_) {
        if (iter.second == rid) {
            DropFromL1ByIndex(iter.first);
            return;
        }
    }
}

/**
 * drop given index from the L1
 * update CacheItem.isL1
 * do not modify IsActive or render tree status
 *
 */
void RepeatVirtualScroll2Caches::DropFromL1ByIndex(IndexType index)
{
    const std::optional<RIDType>& ridOpt = GetRID4Index(index);
    if (ridOpt.has_value()) {
        const auto cacheIter = cacheItem4Rid_.find(ridOpt.value());
        if (cacheIter != cacheItem4Rid_.end()) {
            UpdateIsL1(cacheIter->second, false);
        }
    }

    const auto iter = l1Rid4Index_.find(index);
    if (iter != l1Rid4Index_.end()) {
        l1Rid4Index_.erase(iter);
        TAG_LOGD(AceLogTag::ACE_REPEAT, "DropFromL1ByIndex: removed index %{public}d -> rid %{public}d from L1",
            static_cast<int32_t>(index), static_cast<int32_t>(ridOpt.value()));
    }
}

/**
 * returns index if given rid is in L1Rid4Index
 */
std::optional<IndexType> RepeatVirtualScroll2Caches::GetL1Index4Rid(RIDType rid)
{
    for (auto l1Iter : l1Rid4Index_) {
        if (l1Iter.second == rid) {
            return l1Iter.first;
        }
    }
    return std::nullopt;
}

void RepeatVirtualScroll2Caches::UpdateL1Rid4Index(std::map<int32_t, uint32_t> l1Rd4Index,
    std::unordered_set<uint32_t> ridNeedToRecycle)
{
    TAG_LOGD(AceLogTag::ACE_REPEAT, "UpdateL1Rid4Index");

    l1Rid4Index_ = l1Rd4Index;
    TAG_LOGD(AceLogTag::ACE_REPEAT, "L1Rid4Index: %{public}s", DumpL1Rid4Index().c_str());

    ForEachCacheItem([&](RIDType rid, const CacheItem& cacheItem) {
        if (ridNeedToRecycle.find(rid) != ridNeedToRecycle.end()) {
            UpdateIsL1(cacheItem, false);
        }
        UpdateIsL1(cacheItem, GetL1Index4RID(rid) != std::nullopt);
        TAG_LOGD(AceLogTag::ACE_REPEAT, "DumpCacheItem: %{public}s", DumpCacheItem(cacheItem).c_str());
    });
}

std::optional<IndexType> RepeatVirtualScroll2Caches::GetL1Index4RID(RIDType rid) const
{
    for (const auto iter : l1Rid4Index_) {
        if (iter.second == rid) {
            return iter.first;
        }
    }
    return std::nullopt;
}

/**
 * Get the Index of frameNode in L1 / active range
 * if UINode found
 */
std::optional<IndexType> RepeatVirtualScroll2Caches::GetL1Index4Node(const RefPtr<FrameNode>& frameNode) const
{
    if (frameNode == nullptr) {
        return std::nullopt;
    }

    for (const auto iter : l1Rid4Index_) {
        const IndexType index = iter.first;
        const RIDType rid = iter.second;

        OptCacheItem cacheItemOpt = GetCacheItem4RID(rid);
        if (cacheItemOpt.has_value() && cacheItemOpt.value()->node_ == frameNode) {
            return ConvertFromToIndexRevert(index); // index in index -> RID
        }
    }
    return std::nullopt;
}

OptCacheItem RepeatVirtualScroll2Caches::CallOnGetRid4Index(IndexType index)
{
    TAG_LOGD(AceLogTag::ACE_REPEAT, "CallOnGetRid4Index(index %{public}d: calling TS", index);

    // swap the ViewStackProcessor instance for secondary while we run the item builder function
    // so that its results can easily be obtained from it, does not disturb main ViewStackProcessor
    NG::ScopedViewStackProcessor scopedViewStackProcessor;
    auto* viewStack = NG::ViewStackProcessor::GetInstance();

    const std::pair<RIDType, uint32_t> result = onGetRid4Index_(index);
    if (result.second == OnGetRid4IndexResult::CREATED_NEW_NODE) {
        // case: new node was created successfully
        // get it from ViewStackProcessor
        RefPtr<UINode> node4Index = viewStack->Finish();
        if (node4Index == nullptr) {
            TAG_LOGE(AceLogTag::ACE_REPEAT,
                "CallOnGetRid4Index(index %{public}d: New Node creation failed. No node on ViewStackProcessor. "
                "Internal error!", static_cast<int32_t>(index));
            return nullptr;
        }
        const RIDType rid = result.first;
        return GetNewRid4Index(index, rid, node4Index);
    } // case OnGetRid4IndexResult::CREATED_NEW_NODE)

    if (result.second == OnGetRid4IndexResult::UPDATED_NODE) {
        // case: TS updated existing node that's in the cache already
        const RIDType rid = result.first;
        return GetUpdatedRid4Index(index, rid);
    } // case OnGetRid4IndexResult::UPDATED_NODE

    // TS was not able to deliver UINode
    TAG_LOGE(AceLogTag::ACE_REPEAT, "New node creation failed for index %{public}d. TS unable to create/update node. "
        "Application error!", static_cast<int32_t>(index));
    return std::nullopt;
}

OptCacheItem RepeatVirtualScroll2Caches::GetNewRid4Index(IndexType index, RIDType rid, RefPtr<UINode>& node4Index)
{
    if (rid == 0) {
        TAG_LOGE(AceLogTag::ACE_REPEAT, "CallOnGetRid4Index(index %{public}d: Node creation failed. Invalid rid. "
            "Internal error!", static_cast<int32_t>(index));
        return std::nullopt;
    }
    // add to L1 index -> rid
    l1Rid4Index_[index] = rid;
    // add to cache
    cacheItem4Rid_[rid] = RepeatVirtualScroll2CacheItem::MakeCacheItem(node4Index, true);
    TAG_LOGD(AceLogTag::ACE_REPEAT, "REPEAT TRACE ABNORMAL (after startup) ...CallOnGetRid4Index"
        "(index %{public}d -> rid %{public}d) returns CacheItem with newly created node %{public}s .",
        index, static_cast<int32_t>(rid), DumpCacheItem(cacheItem4Rid_[rid]).c_str());
    ACE_SCOPED_TRACE("RepeatVirtualScroll:CallOnGetRid4Index CREATED_NEW_NODE [index] %d, [rid] %d, [item] %s",
        index, static_cast<int32_t>(rid), DumpCacheItem(cacheItem4Rid_[rid]).c_str());
    return cacheItem4Rid_[rid];
}

OptCacheItem RepeatVirtualScroll2Caches::GetUpdatedRid4Index(IndexType index, RIDType rid)
{
    if (rid == 0) {
        TAG_LOGE(AceLogTag::ACE_REPEAT, "Node update for index %{public}d failed. Invalid rid. "
            "Internal error!", static_cast<int32_t>(index));
        return std::nullopt;
    }
    const auto& optCacheItem = GetCacheItem4RID(rid);
    if (!optCacheItem.has_value() || optCacheItem.value()->node_ == nullptr) {
        TAG_LOGE(AceLogTag::ACE_REPEAT, "Node update for index %{public}d failed. No node in CacheItem. "
            "Internal error!", static_cast<int32_t>(index));
        return std::nullopt;
    }
    // add to L1 but do not Set Active or add to render tree.
    l1Rid4Index_[index] = rid;
    UpdateIsL1(optCacheItem.value(), true);
    TAG_LOGD(AceLogTag::ACE_REPEAT,
        "CallOnGetRid4Index(index %{public}d -> rid %{public}d): returns CacheItem with updated node "
        "%{public}s .", index, static_cast<int32_t>(rid), DumpCacheItem(cacheItem4Rid_[rid]).c_str());
    ACE_SCOPED_TRACE("RepeatVirtualScroll:CallOnGetRid4Index UPDATED_NODE [index] %d, [rid] %d, [item] %s",
        index, static_cast<int32_t>(rid), DumpCacheItem(cacheItem4Rid_[rid]).c_str());
    return optCacheItem;
}

/**
 * return CacheItem for RID, if it exists
 * do not check and CacheItem flags
 */
OptCacheItem RepeatVirtualScroll2Caches::GetCacheItem4RID(RIDType rid) const
{
    auto cacheIter = cacheItem4Rid_.find(rid);
    if (cacheIter != cacheItem4Rid_.end()) {
        return cacheIter->second;
    }
    return std::nullopt;
}

/**
 * if L1 includes RID for index, return it
 */
std::optional<RIDType> RepeatVirtualScroll2Caches::GetRID4Index(IndexType index) const
{
    auto ridIter = l1Rid4Index_.find(index);
    if (ridIter != l1Rid4Index_.end()) {
        return ridIter->second;
    }
    return std::nullopt;
}

OptCacheItem RepeatVirtualScroll2Caches::GetL1CacheItem4Index(IndexType index)
{
    const auto iter = l1Rid4Index_.find(index);
    if (iter == l1Rid4Index_.end()) {
        TAG_LOGE(AceLogTag::ACE_REPEAT, "GetL1CacheItem4Index(index: %{public}d) returns nullptr, new index", index);
        return std::nullopt;
    }

    const RIDType rid = iter->second;
    const auto cacheItemIter = cacheItem4Rid_.find(rid);
    if (cacheItemIter != cacheItem4Rid_.end() && cacheItemIter->second->node_ != nullptr &&
        cacheItemIter->second->isL1_) {
        TAG_LOGD(AceLogTag::ACE_REPEAT, "GetL1CacheItem4Index(index: %{public}d) returns L1 %{public}s .",
            index, DumpCacheItem(cacheItemIter->second).c_str());
        return cacheItemIter->second;
    }
    TAG_LOGE(
        AceLogTag::ACE_REPEAT, "GetL1CacheItem4Index(index: %{public}d) returns nullptr. Invalid CacheItem.", index);
    return std::nullopt;
}

bool RepeatVirtualScroll2Caches::RebuildL1(const std::function<bool(int32_t index, CacheItem& node)>& cbFunc)
{
    std::map<IndexType, RIDType> l1Copy;
    std::swap(l1Copy, l1Rid4Index_);
    bool modified = false;

    for (const auto l1Iter : l1Copy) {
        const IndexType index = l1Iter.first;
        const RIDType rid = l1Iter.second;

        OptCacheItem optCacheItem = GetCacheItem4RID(rid);
        if (optCacheItem.has_value()) {
            IndexType indexMapped = ConvertFromToIndexRevert(index);
            if (optCacheItem.value()->node_ != nullptr && cbFunc(indexMapped, optCacheItem.value())) {
                // keep in L1
                l1Rid4Index_[index] = rid;
                // don't trigger reuse here
                UpdateIsL1(optCacheItem.value(), true, false);
            } else {
                UpdateIsL1(optCacheItem.value(), false);
                optCacheItem.value()->isActive_ = false;
                optCacheItem.value()->isOnRenderTree_ = false;
                modified = true;
            }
        }
    }
    return modified;
}

void RepeatVirtualScroll2Caches::ForEachL1Node(
    const std::function<void(IndexType index, RIDType rid, const RefPtr<UINode>& node)>& cbFunc)
{
    for (const auto l1Iter : l1Rid4Index_) {
        const IndexType index = l1Iter.first;
        const RIDType rid = l1Iter.second;
        OptCacheItem optCacheItem = GetCacheItem4RID(rid);
        if (optCacheItem.has_value()) {
            cbFunc(index, rid, optCacheItem.value()->node_);
        }
    }
}

void RepeatVirtualScroll2Caches::ForEachL1NodeWithOnMove(const std::function<void(const RefPtr<UINode>& node)>& cbFunc)
{
    std::map<IndexType, RIDType> mappedL1Rid4Index;
    for (const auto& iter : l1Rid4Index_) {
        const IndexType index = ConvertFromToIndex(iter.first);
        const RIDType rid = iter.second;
        mappedL1Rid4Index.emplace(index, rid);
    }
    for (const auto& iter : mappedL1Rid4Index) {
        const RIDType rid = iter.second;
        OptCacheItem optCacheItem = GetCacheItem4RID(rid);
        if (optCacheItem.has_value()) {
            cbFunc(optCacheItem.value()->node_);
        }
    }
}

void RepeatVirtualScroll2Caches::ForEachCacheItem(
    const std::function<void(RIDType rid, const CacheItem& cacheItem)>& cbFunc)
{
    for (auto cacheItemIter : cacheItem4Rid_) {
        cbFunc(cacheItemIter.first, cacheItemIter.second);
    }
}

void RepeatVirtualScroll2Caches::UpdateMoveFromTo(int32_t from, int32_t to)
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

std::string RepeatVirtualScroll2Caches::DumpUINode(const RefPtr<UINode>& node) const
{
    return (node == nullptr) ? "UINode: nullptr"
                             : "UINode: " + node->GetTag() + "(" + std::to_string(node->GetId()) + ")";
}

std::string RepeatVirtualScroll2Caches::DumpCacheItem(const CacheItem& cacheItem) const
{
    return (cacheItem->node_ == nullptr)
               ? "UINode nullptr"
               : DumpUINode(cacheItem->node_) + ", isL1: " + std::to_string(cacheItem->isL1_) +
                     ", isActive: " + std::to_string(cacheItem->isActive_);
}

std::string RepeatVirtualScroll2Caches::DumpUINodeCache() const
{
    std::string result =
        "All UINodes in cache (cacheItem4Rid_): size=" + std::to_string(cacheItem4Rid_.size()) + "--------------\n";
    for (const auto& cacheItemIIter : cacheItem4Rid_) {
        const auto optIndex4Rid = GetL1Index4RID(cacheItemIIter.first);
        result += "  rid: " + std::to_string(cacheItemIIter.first) + " -> " +
                  DumpCacheItem(cacheItemIIter.second).c_str() + " L1 active node index " +
                  (optIndex4Rid.has_value() ? std::to_string(optIndex4Rid.value()) : "N/A") + "\n";
    }
    return result;
}

std::string RepeatVirtualScroll2Caches::DumpL1Rid4Index() const
{
    std::string result = "l1Rid4Index size=" + std::to_string(l1Rid4Index_.size()) + "--------------\n";

    for (const auto mapIter : l1Rid4Index_) {
        const OptCacheItem optCacheItem = GetCacheItem4RID(mapIter.second);
        result +=
            " index " + std::to_string(mapIter.first) + " -> cacheItem(rid: " + std::to_string(mapIter.second) +
            "): " + (optCacheItem.has_value() ? DumpCacheItem(optCacheItem.value()).c_str() : "CacheItem N/A ERROR") +
            "\n";
    }
    return result;
}

void RepeatVirtualScroll2Caches::UpdateIsL1(const CacheItem& cacheItem, bool isL1, bool shouldTriggerRecycleOrReuse)
{
    cacheItem->isL1_ = isL1;
    if (!shouldTriggerRecycleOrReuse) {
        return;
    }
    CHECK_NULL_VOID(cacheItem->node_);
    auto child = cacheItem->node_->GetFrameChildByIndex(0, false);
    CHECK_NULL_VOID(child);
    if (isL1) {
        if (recycledNodeIds_.erase(child->GetId()) == 0) {
            return;
        }
        child->OnReuse();
    } else {
        if (recycledNodeIds_.emplace(child->GetId()).second == false) {
            return;
        }
        child->OnRecycle();
    }
}

} // namespace OHOS::Ace::NG
