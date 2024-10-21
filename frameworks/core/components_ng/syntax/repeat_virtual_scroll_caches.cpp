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

#include "core/components_ng/syntax/repeat_virtual_scroll_caches.h"

#include "core/components_ng/base/view_stack_processor.h"

namespace OHOS::Ace::NG {

bool KeySorterClass::operator()(const std::string& left, const std::string& right) const
{
    return virtualScroll_->CompareKeyByIndexDistance(left, right);
}

RepeatVirtualScrollCaches::RepeatVirtualScrollCaches(
    const std::map<std::string, std::pair<bool, uint32_t>>& cacheCountL24ttype,
    const std::function<void(uint32_t)>& onCreateNode,
    const std::function<void(const std::string&, uint32_t)>& onUpdateNode,
    const std::function<std::list<std::string>(uint32_t, uint32_t)>& onGetKeys4Range,
    const std::function<std::list<std::string>(uint32_t, uint32_t)>& onGetTypes4Range)

    : // each ttype incl default has own L2 cache size
      cacheCountL24ttype_(cacheCountL24ttype),
      // request TS to create new sub-tree for given index or update existing
      // update subtree cached for (old) index
      // API might need to change to tell which old item to update
      onCreateNode_(onCreateNode), onUpdateNode_(onUpdateNode), onGetTypes4Range_(onGetTypes4Range),
      onGetKeys4Range_(onGetKeys4Range)
{
}

std::optional<std::string> RepeatVirtualScrollCaches::GetKey4Index(uint32_t index, bool allowFetch)
{
    if (key4index_.find(index) != key4index_.end()) {
        return key4index_[index];
    }

    if (!allowFetch) {
        return std::nullopt;
    }

    // need to rebuild L1 after fetch ?
    const bool rebuildL1 =
        key4index_.size() == 0 && HasOverlapWithLastActiveRange(index, index);

    // allow to fetch extended range of keys if rebuildL1 is needed
    FetchMoreKeysTTypes(index, index, rebuildL1 == true);

    if (rebuildL1) {
        // check for each L1 entry if its key is includes in newly received keys
        // only keep these in L1
        RebuildL1WithKey([&](const std::string &key) { return index4Key_.find(key) != index4Key_.end(); });
    }

    return GetKey4Index(index, false);
}

/**
 * does given range overlap the last active range?
 */
bool RepeatVirtualScrollCaches::HasOverlapWithLastActiveRange(uint32_t from, uint32_t to)
{
    const auto lastFrom = lastActiveRanges_[0].first;
    const auto lastTo = lastActiveRanges_[0].second;
    if (lastFrom <= lastTo) {
        return to >= lastFrom && from <= lastTo;
    } else {
        return to <= lastTo || to >= lastFrom || from <= lastTo || from >= lastFrom;
    }
}

/**
 * get more index -> key and index -> ttype from TS side
 */
bool RepeatVirtualScrollCaches::FetchMoreKeysTTypes(uint32_t from, uint32_t to, bool allowFetchMore)
{
    if (from > to) {
        return false;
    }

    if (allowFetchMore) {
        // following a key4index_/ttype4index_ purge fetch the whole range
        const auto rangeStart = lastActiveRanges_[0].first;
        const auto rangeEnd = lastActiveRanges_[0].second;

        if (rangeStart <= rangeEnd) {
            return FetchMoreKeysTTypes(from, std::max(to, rangeEnd), false);
        } else {
            const bool v1 = FetchMoreKeysTTypes(0, rangeEnd, false);
            const bool v2 = FetchMoreKeysTTypes(rangeStart, std::numeric_limits<int>::max(), false);
            return v1 || v2;
        }
    }

    TAG_LOGD(AceLogTag::ACE_REPEAT, "from:%{public}d, to:%{public}d",
        static_cast<int32_t>(from),  static_cast<int32_t>(to));

    // always request the same range for keys and ttype
    // optimism by merging the two calls into one
    const std::list<std::string> keysFrom = onGetKeys4Range_(from, to);
    const std::list<std::string> ttypesFrom = onGetTypes4Range_(from, to);
    if ((keysFrom.size() == 0) || (ttypesFrom.size() == 0) || (keysFrom.size() != ttypesFrom.size())) {
        TAG_LOGE(AceLogTag::ACE_REPEAT,
            "fail to fetch keys and/or ttyypes: requested range %{public}d - %{public}d. "
            "Received number of keys: %{public}d, of ttypes: %{public}d",
            static_cast<int32_t>(from), static_cast<int32_t>(to),
            static_cast<int32_t>(keysFrom.size()), static_cast<int32_t>(ttypesFrom.size()));
            return false;
    }
    TAG_LOGD(AceLogTag::ACE_REPEAT,
        "Received number of keys: %{public}d, of ttypes: %{public}d:",
        static_cast<int32_t>(keysFrom.size()), static_cast<int32_t>(ttypesFrom.size()));

    // fill-in index <-> key maps
    auto from1 = from;
    for (const auto& key : keysFrom) {
        key4index_[from1] = key;
        index4Key_[key] = from1;

        const auto cacheItemIter = node4key_.find(key);
        if (cacheItemIter != node4key_.end()) {
            // TS onGetKeys4Range_ has made any needed updates for this key -> UINode
            cacheItemIter->second.isValid=true;
        }
        from1++;
    }

    // fill-in index <-> ttype maps
    from1 = from;
    for (const auto& ttype : ttypesFrom) {
        ttype4index_[from1] = ttype;
        index4ttype_[ttype] = from1;
        from1++;
    }

    // false when nothing was fetched
    return from1 > from;
}

// get UINode for given index without create.
RefPtr<UINode> RepeatVirtualScrollCaches::GetCachedNode4Index(uint32_t index)
{
    TAG_LOGD(AceLogTag::ACE_REPEAT, "index %{public}d", static_cast<int32_t>(index));

    const auto& key = GetKey4Index(index, false);
    const auto& node4Key = GetCachedNode4Key(key);
    const auto& ttype = GetTType4Index(index);

    if (!key.has_value() || !ttype.has_value() || !node4Key.has_value()) {
        TAG_LOGD(AceLogTag::ACE_REPEAT, "no CachedItem for index %{public}d", static_cast<int32_t>(index));
        return nullptr;
    }
    auto uiNode = node4Key.value().item;
    const auto& node4Ttype = GetCachedNode4Key4Ttype(key, ttype);
    if (node4Ttype != uiNode) {
    // STATE_MGMT_NOTE check if the node4Ttype is a nullptr instead
        // UINode for key exists, but the requested ttype is different from the ttype used
        // to render the returned UINode
        // STATE_MGMT_NOTE how to handle ?
        TAG_LOGD(AceLogTag::ACE_REPEAT,
            "index %{public}d -> %{public}s, templateId %{public}s, "
            "found UINode %{public}s that has been created from a different template.",
            static_cast<int32_t>(index), key.value().c_str(),
            ttype.value().c_str(), DumpUINode(uiNode).c_str());
        // mark as not valid, needs fresh render or update other UINode
        // what to do with existing item?
        // STATE_MGMT_NOTE: Can not just del like this?
        // how to fix: call to RepeatVirtualScrollNode::DropFromL1
        node4key_.erase(key.value());
        RemoveKeyFromL1(key.value());
        return nullptr;
    }

    if (!node4Key.value().isValid) {
        // impossible situation: TS onKeyIndex shoul;d have updated repeatItem.index already!
        TAG_LOGW(AceLogTag::ACE_REPEAT,
            "index %{public}d -> %{public}s, templateId %{public}s, "
            "found UINode %{public}s marked inValid. Internal error!",
            static_cast<int32_t>(index), key.value().c_str(), ttype.value().c_str(), DumpUINode(uiNode).c_str());
        UpdateSameKeyItem(key.value(), index);
        node4key_[key.value()].isValid = true;
    }

    return node4Key.value().item;
}

void RepeatVirtualScrollCaches::AddKeyToL1(const std::string& key, bool shouldTriggerReuse)
{
    activeNodeKeysInL1_.emplace(key);

    if (!shouldTriggerReuse) {
        return;
    }

    RefPtr<UINode> child;
    const auto& it = node4key_.find(key);
    if (it != node4key_.end() && it->second.item) {
        child = it->second.item->GetFrameChildByIndex(0, false);
    }
    CHECK_NULL_VOID(child);

    // if node is already reused, do nothing
    if (reusedNodeIds_.emplace(child->GetId()).second == false) {
        return;
    }

    // fire OnReuse to trigger node pattern handlers
    TAG_LOGD(AceLogTag::ACE_REPEAT, "OnReuse() nodeId:%{public}d key:%{public}s", child->GetId(), key.c_str());
    child->OnReuse();
}


 void RepeatVirtualScrollCaches::RemoveKeyFromL1(const std::string& key, bool shouldTriggerRecycle)
 {
    activeNodeKeysInL1_.erase(key);

    if (!shouldTriggerRecycle) {
        return;
    }

    RefPtr<UINode> child;
    const auto& it = node4key_.find(key);
    if (it != node4key_.end() && it->second.item) {
        child = it->second.item->GetFrameChildByIndex(0, false);
    }
    CHECK_NULL_VOID(child);

    // if node is not reused currently, do nothing
    if (reusedNodeIds_.erase(child->GetId()) == 0) {
        return;
    }

    // fire OnRecycle to trigger node pattern handlers
    TAG_LOGD(AceLogTag::ACE_REPEAT, "OnRecycle() nodeId:%{public}d key:%{public}s", child->GetId(), key.c_str());
    child->OnRecycle();
}

/** scenario:
 *         Repeat gets updated due to data change.
 *         1. TS calls RepeatVirtualScrollNode,
 *            then calls this function.
 * 2. RepeatVirtualScrollNode requests layout to rebuild the UI
 * 3. layout sends RepeatVirtualScrollNode::GetFrameChild calls
 * 4. how to service GetFrameChild  call:
 *   - first check for L1 keys (same template type) if any can be updated.
 *     These UINodes remain in the render tree.
 *   - if no L1 item, the look for L2 keys (same template type)
 */
void RepeatVirtualScrollCaches::InvalidateKeyAndTTypeCaches()
{
    TAG_LOGD(AceLogTag::ACE_REPEAT,
        "invalidating index-> key and index->ttype mapping, layout needs to request all UINodes again  .. ");
    key4index_.clear();
    index4Key_.clear();
    ttype4index_.clear();
    index4ttype_.clear();
    // mark all cached UINodes need to update.
    // TS onKey4Index will fetch key-> RepeatItem and uupdate RepeatItem.index if changed
    // Call UpdateDirty2 to make partial updates right away
    // Therefore, on return GetKeys4Range can set node4key -> CacheItem back to isValid.true
    // for all retained keys.
    for (auto& [key, item] : node4key_) {
        item.isValid = false;
    }

    // we do not request new index <-> because we are still
    // inside observed Repeat rerender.
    // instead for FetchMoreKeysTTypes will fetch the entire range
}

/**
 * scenario: scroll, try to update an existing UINode
 *
 * find an key / UINode in L2 and update the UINode to
 *   render the data source item 'forIndex'.
 */
RefPtr<UINode> RepeatVirtualScrollCaches::UpdateFromL2(uint32_t forIndex)
{
    TAG_LOGD(AceLogTag::ACE_REPEAT, "forIndex:%{public}d",  static_cast<int32_t>(forIndex));

    const auto iterTType = ttype4index_.find(forIndex);
    if (iterTType == ttype4index_.end()) {
        TAG_LOGD(AceLogTag::ACE_REPEAT, "no ttype for index %{public}d",  static_cast<int32_t>(forIndex));
        return nullptr;
    }
    const auto& ttype = iterTType->second;
    const auto iterNewKey = key4index_.find(forIndex);
    if (iterNewKey == key4index_.end()) {
        TAG_LOGD(AceLogTag::ACE_REPEAT, "no key for index %{public}d",  static_cast<int32_t>(forIndex));
        return nullptr;
    }
    const std::string& forKey = iterNewKey->second;

    const auto& oldKey = GetL2KeyToUpdate(ttype);
    if (!oldKey) {
        // no key for this ttype available to update
        TAG_LOGD(AceLogTag::ACE_REPEAT,
            "for index %{public}d, ttype %{public}s, no UINode found to update",
            static_cast<int32_t>(forIndex), ttype.c_str());
        return nullptr;
    }

    TAG_LOGD(AceLogTag::ACE_REPEAT,
        "for index %{public}d, from ld key %{public}s requesting TS to update child UINodes ....",
        static_cast<int32_t>(forIndex), oldKey.value().c_str());

    // call TS to do the RepeatItem update
    onUpdateNode_(oldKey.value(), forIndex);

    TAG_LOGD(AceLogTag::ACE_REPEAT,
        "for index %{public}d, from old key %{public}s requesting TS to update child UINodes - done ",
        static_cast<int32_t>(forIndex), oldKey.value().c_str());

    return UINodeHasBeenUpdated(ttype, oldKey.value(), forKey);
}

void RepeatVirtualScrollCaches::UpdateSameKeyItem(const std::string& key, uint32_t index)
{
    // call TS to do the RepeatItem update
    onUpdateNode_(key, index);
}

RefPtr<UINode> RepeatVirtualScrollCaches::CreateNewNode(uint32_t forIndex)
{
    TAG_LOGD(AceLogTag::ACE_REPEAT, "forIndex: %{public}d",  static_cast<int32_t>(forIndex));

    // get key
    const auto iter = key4index_.find(forIndex);
    if (iter == key4index_.end()) {
        TAG_LOGE(AceLogTag::ACE_REPEAT, "fail to create node of %{public}d",  static_cast<int32_t>(forIndex));
        return nullptr;
    }
    const auto& forKey = iter->second;

    ACE_SCOPED_TRACE("RepeatVirtualScrollCaches::CreateNewNode index[%d] -> key[%s]",
        static_cast<int32_t>(forIndex), forKey.c_str());

    // see if node already created, just for safety
    const auto nodeIter = node4key_.find(forKey);
    if (nodeIter != node4key_.end()) {
        // have a node for this key already, just return
        return nodeIter->second.item;
    }

    // need to create a new node for key

    // get ttype
    const auto ttypeIter = ttype4index_.find(forIndex);
    if (ttypeIter == ttype4index_.end()) {
        TAG_LOGE(AceLogTag::ACE_REPEAT, "fail to create %{public}d node due to type is missing", forIndex);
        return nullptr;
    }
    const auto& ttype = ttypeIter->second;

    // swap the ViewStackProcessor instance for secondary while we run the item builder function
    // so that its results can easily be obtained from it, does not disturb main ViewStackProcessor
    NG::ScopedViewStackProcessor scopedViewStackProcessor;
    auto* viewStack = NG::ViewStackProcessor::GetInstance();

    // call TS side
    onCreateNode_(forIndex);

    const auto& node4Index = viewStack->Finish();

    if (!node4Index) {
        TAG_LOGE(AceLogTag::ACE_REPEAT,
            "New Node create: For index %{public}d -> key %{public}s -> ttype %{public}s "
            "item builder FAILED to gen FrameNode. ERROR",
            forIndex, forKey.c_str(), ttype.c_str());
        return nullptr;
    }

    // add node to node4key4ttype_
    const auto node4KeyIter = node4key4ttype_.find(ttype);
    if (node4KeyIter != node4key4ttype_.end()) {
        node4KeyIter->second[forKey] = node4Index;
    } else {
        std::unordered_map<std::string, RefPtr<UINode>> node4Key;
        node4Key[forKey] = node4Index;
        node4key4ttype_[ttype] = std::move(node4Key);
    }

    // add node to node4key_
    node4key_[forKey] = CacheItem { true, node4Index };
    TAG_LOGD(AceLogTag::ACE_REPEAT,
        "New Node create: For index %{public}d -> key %{public}s -> ttype %{public}s created new Node %{public}s . ",
        forIndex, forKey.c_str(), ttype.c_str(), DumpUINode(node4Index).c_str());
    return node4Index;
}

void RepeatVirtualScrollCaches::ForEachL1IndexUINode(std::map<int32_t, RefPtr<UINode>>& children)
{
    for (const auto& key : activeNodeKeysInL1_) {
        const auto& cacheItem = node4key_[key];
        const auto& indexIter = index4Key_.find(key);
        if (indexIter == index4Key_.end()) {
            TAG_LOGE(AceLogTag::ACE_REPEAT, "fail to get index for %{public}s key", key.c_str());
            continue;
        }
        children.emplace(indexIter->second, cacheItem.item);
    }
}

void RepeatVirtualScrollCaches::RecycleItemsByIndex(int32_t index)
{
    auto keyIter = key4index_.find(index);
    if (keyIter != key4index_.end()) {
        // STATE_MGMT_NOTE
        // can not just remove from L1, also need to detach from tree!
        // how to fix cause a call to RepeatVirtualScrollNode::DropFromL1 in
        TAG_LOGD(
            AceLogTag::ACE_REPEAT, "remove index %{public}d -> key %{public}s from L1", index, keyIter->second.c_str());

        ACE_SCOPED_TRACE(
            "RepeatVirtualScrollCaches::RecycleItemsByIndex index[%d] -> key [%s]", index, keyIter->second.c_str());

        // don't fire OnRecycle here, as we manage reuse/recycle indepedently
        RemoveKeyFromL1(keyIter->second, false);
    }
}

/**
 * iterate over all entries of L1 and call function for each entry
 * if function returns true, entry is added to rebuild L1
 * cbFunc return true, key
 * cbFunc returns false drop from L1
 */
bool RepeatVirtualScrollCaches::RebuildL1(const std::function<bool(int32_t index, const RefPtr<UINode>& node)>& cbFunc)
{
    std::unordered_set<std::string> l1Copy;
    std::swap(l1Copy, activeNodeKeysInL1_);
    bool modified = false;
    for (const auto& key : l1Copy) {
        const auto& indexIter = index4Key_.find(key);
        if (indexIter == index4Key_.end()) {
            continue;
        }
        const auto& cacheItem = node4key_[key];
        int32_t index = static_cast<int32_t>(indexIter->second);
        if (cbFunc(index, cacheItem.item)) {
            AddKeyToL1(key, false);
        } else {
            RemoveKeyFromL1(key);
            modified = true;
        }
    }
    return modified;
}

bool RepeatVirtualScrollCaches::RebuildL1WithKey(const std::function<bool(const std::string& key)>& cbFunc)
{
    std::unordered_set<std::string> l1Copy;
    std::swap(l1Copy, activeNodeKeysInL1_);
    bool modified = false;
    for (const auto& key : l1Copy) {
        if (cbFunc(key)) {
            AddKeyToL1(key, false);
        } else {
            RemoveKeyFromL1(key);
            modified = true;
        }
    }
    return modified;
}

RefPtr<UINode> RepeatVirtualScrollCaches::DropFromL1(const std::string& key)
{
    const auto& cacheItem4Key = GetCachedNode4Key(key);
    if (!cacheItem4Key.has_value()) {
        return nullptr;
    }
    auto uiNode = cacheItem4Key.value().item;
    RemoveKeyFromL1(key);
    return uiNode;
}

void RepeatVirtualScrollCaches::SetLastActiveRange(uint32_t from, uint32_t to)
{
    // STATE_MGMT_NOTE, only update when from or to != stActiveRanges_[0] ?
    lastActiveRanges_[1] = lastActiveRanges_[0];
    lastActiveRanges_[0] = { from, to };

    const auto updatedPermissableCacheCount = to - from + 1;
    for (auto iter = cacheCountL24ttype_.begin(); iter != cacheCountL24ttype_.end(); iter++) {
        std::pair<bool, uint32_t>& optCacheCount = iter->second;
        if (optCacheCount.first == false) {
            // Repeat.template({ cachedCount }) options not specified
            if (optCacheCount.second < updatedPermissableCacheCount) {
                TAG_LOGD(AceLogTag::ACE_REPEAT,
                    "Growing permissable size of spare nodes cache for ttype '%{public}s' to %{public}d .",
                    iter->first.c_str(), updatedPermissableCacheCount);
                optCacheCount.second = updatedPermissableCacheCount;
            }
        }
    }
}

/**
 * Get the Index of frameNode in L1 / active range
 * return -1 if not find the frameNode
 */
int32_t RepeatVirtualScrollCaches::GetFrameNodeIndex(const RefPtr<FrameNode>& frameNode) const
{
    for (const auto& key : activeNodeKeysInL1_) {
        const auto nodeIter = node4key_.find(key);
        if (nodeIter == node4key_.end() || !nodeIter->second.item) {
            continue;
        }
        const auto& node = nodeIter->second.item->GetFrameChildByIndex(0, true);
        if (node != frameNode) {
            continue;
        }
        const auto& indexIter = index4Key_.find(key);
        if (indexIter == index4Key_.end()) {
            return -1;
        }
        return indexIter->second;
    }
    return -1;
}

/**
 * intended scenario: scroll
 * servicing GetFrameChild, search for key that can be updated.
 *
 * return a key whose UINode can be updated
 * the key must not be in L1, i.e. activeNodeKeysInL1_
 * the given ttype must match the template type the UINode for this key
 * has been rendered for (this info is available from node4key4ttype_)
 */
std::optional<std::string> RepeatVirtualScrollCaches::GetL2KeyToUpdate(
    const std::optional<std::string>& ttype) const
{
    if (!ttype.has_value()) {
        return std::nullopt;
    }

    const auto itNodes = node4key4ttype_.find(ttype.value());
    if (itNodes == node4key4ttype_.end()) {
        return std::nullopt;
    }
    const auto& keys2UINode = itNodes->second;
    std::set<std::string, KeySorterClass> l2Keys = GetSortedL2KeysForTType(keys2UINode);
    auto keyIter = l2Keys.rbegin();
    if (keyIter == l2Keys.rend()) {
        TAG_LOGD(AceLogTag::ACE_REPEAT,
            "for ttype %{public}s no key in L2 that could be updated. ",
            ttype.value().c_str());
        return std::nullopt;
    }
    TAG_LOGD(AceLogTag::ACE_REPEAT,
        "for ttype %{public}s found key '%{public}s' from L2 to update. ",
        ttype.value().c_str(), keyIter->c_str());
    return *keyIter;
}

/**
 * scenario: UI rebuild following key invalidation by TS side
 * L1 includes keys that are no longer used, the linked UINodes
 * should be updated.
 *
 * This function checks all L1 keys (of active UINodes) if the key
 * can still be found from
 * (previously updated following invalidation) key -> index map and
 *
 */
std::optional<std::string> RepeatVirtualScrollCaches::GetL1KeyToUpdate(const std::string& ttype) const
{
    for (const auto& keyIter : activeNodeKeysInL1_) {
        const std::string& key = keyIter;
        if (index4Key_.find(key) == index4Key_.end()) {
            // key is no longer used
            // check if key rendered the expected ttype
            const auto ttypeIter = node4key4ttype_.find(ttype);
            if (ttypeIter != node4key4ttype_.end()) {
                const std::unordered_map<std::string, RefPtr<UINode>>& node4Key = ttypeIter->second;
                if (node4Key.find(key) != node4Key.end()) {
                    TAG_LOGD(AceLogTag::ACE_REPEAT, "for ttype %{public}s found key to update %{public}s in L1. ",
                        ttype.c_str(), key.c_str());
                    return key;
                }
            }
        }
    }
    TAG_LOGD(AceLogTag::ACE_REPEAT, "for ttype %{public}s no key in L1 that could be updated. ", ttype.c_str());
    return std::nullopt;
}

/**
 * scenario: UINode of fromKey has been updated to render data for 'forKey'
 *     the template type (ttype) remains unchanged
 *     update node4key4ttype_ and node4key_ entries to use new key point to same UINode
 */
RefPtr<UINode> RepeatVirtualScrollCaches::UINodeHasBeenUpdated(
    const std::string& ttype, const std::string& fromKey, const std::string& forKey)
{
    // 1. update fromKey -> forKey in node4key4ttype_
    for (auto& node4KeyIter : node4key4ttype_) {
        node4KeyIter.second.erase(forKey);
    }
    const auto nodesIter = node4key4ttype_.find(ttype);
    if (nodesIter != node4key4ttype_.end()) {
        auto& node4key = nodesIter->second;
        auto iter = node4key.find(fromKey);
        if (iter != node4key.end()) {
            auto node = iter->second;
            node4key.erase(iter);
            node4key.emplace(forKey, node);
        }
    }

    // 2. update the key: fromKey to forKey in node4key_
    auto iter = node4key_.find(fromKey);
    if (iter != node4key_.end()) {
        auto cachedItem = iter->second;
        cachedItem.isValid = true;
        node4key_.erase(iter);
        node4key_.emplace(forKey, cachedItem);
        return cachedItem.item;
    }
    TAG_LOGE(AceLogTag::ACE_REPEAT, "fail to update L2 : %{public}s, %{public}s, %{public}s, ", ttype.c_str(),
        fromKey.c_str(), forKey.c_str());
    return nullptr;
}

/** scenario: keys cache has been updated
 *
 * find which keys in key -> UINode map are no longer used
 * returned set entries are pairs:
 *   pair.first: is this key a L1 item,
 *   pair.second: key
 */
void RepeatVirtualScrollCaches::FindUnusedKeys(std::set<std::pair<bool, std::string>>& result) const
{
    for (const auto& iter : node4key_) {
        const std::string key = iter.first;
        const auto indexIter = index4Key_.find(key);
        if (indexIter == index4Key_.end()) {
            // key is no longer used
            // is it in L1 ?
            const bool keyInL1 = (index4Key_.find(key) != index4Key_.end());
            result.emplace(keyInL1, key);
        }
    }
}

/**
 * scenario: in idle process , following GetChildren()
 * execute purge()
 *
 * enforce L2 cacheCount for each ttype
 * logical L2 cache is map key->UINode map filtered out L1 keys
 * purge by by deleting UINodes, delete their entry from
 *   node4key4ttype_ and node4key_
 *
 */
bool RepeatVirtualScrollCaches::Purge()
{
    uint32_t deletedCount = 0;
    for (auto& itTType : node4key4ttype_) {
        const auto& ttype = itTType.first;
        auto& uiNode4Key = itTType.second;

        // size of the unused node pool L2
        // defined either in template { caacheCount }
        // or set dynamically by framework to maximum number of items in L1
        uint32_t cacheCount = (cacheCountL24ttype_.find(ttype) == cacheCountL24ttype_.end())
                                  ? 0 // unknown ttype should never happen
                                  : cacheCountL24ttype_[ttype].second;
        TAG_LOGD(AceLogTag::ACE_REPEAT, "Cache::Purge cacheCount %{public}d",  static_cast<int32_t>(cacheCount));
        std::set<std::string, KeySorterClass> l2Keys = GetSortedL2KeysForTType(uiNode4Key);

        // l2_keys is sorted by increasing distance from lastActiveRange
        // will drop those keys and their UINodes with largest distance
        // improvement idea: in addition to distance from range use the
        // scroll direction for selecting these keys
        auto safeDist = std::min(cacheCount, static_cast<uint32_t>(l2Keys.size()));
        auto itL2Key = std::next(l2Keys.begin(), safeDist);

        while (itL2Key != l2Keys.end()) {
            // delete remaining keys
            TAG_LOGD(AceLogTag::ACE_REPEAT,
                "   ... purging spare node cache item old key '%{public}s' -> node %{public}s, ttype: '%{public}s', "
                "permissable spare nodes count %{public}d",
                itL2Key->c_str(), DumpUINodeWithKey(*itL2Key).c_str(), ttype.c_str(),
                static_cast<int32_t>(cacheCount));
            uiNode4Key.erase(*itL2Key);
            node4key_.erase(*itL2Key);
            // check out transition case.
            itL2Key++;
            deletedCount += 1;
        }
    }
    if (deletedCount > 0) {
        TAG_LOGD(AceLogTag::ACE_REPEAT, "Purged total %d items.",  static_cast<int32_t>(deletedCount));
        ACE_SCOPED_TRACE("RepeatVirtualScrollCaches::Purge %d items",  static_cast<int32_t>(deletedCount));
    }
    return (deletedCount > 0);
}

/**
 * given key return the index position (reverse lookup)
 * invalidated keys (after Repeat rerender/ data change)
 * are keys for which no index exists anymore,
 * method returns uint max value for these.
 * int max value causes that distance from active range is max
 * these keys will be selected for update first.
 */
uint32_t RepeatVirtualScrollCaches::GetIndex4Key(const std::string& key) const
{
    auto it = index4Key_.find(key);
    if (it != index4Key_.end()) {
        return it->second;
    }
    // key is no longer used
    // return max uint32_t value
    return UINT32_MAX;
}

std::optional<std::string> RepeatVirtualScrollCaches::GetTType4Index(uint32_t index)
{
    const auto it = ttype4index_.find(index);
    if (it == ttype4index_.end()) {
        return std::nullopt;
    }
    return it->second;
}

std::optional<CacheItem> RepeatVirtualScrollCaches::GetCachedNode4Key(const std::optional<std::string>& key)
{
    if (!key.has_value()) {
        return std::nullopt;
    }
    const auto it = node4key_.find(key.value());
    if (it == node4key_.end()) {
        return std::nullopt;
    }
    return it->second;
}

RefPtr<UINode> RepeatVirtualScrollCaches::GetCachedNode4Key4Ttype(
    const std::optional<std::string>& key, const std::optional<std::string>& ttype)
{
    // if key and ttype given, search for UINode of givenkey and ttype
    //  in caches, i.e. in node4key4ttype
    if (!key.has_value() || !ttype.has_value()) {
        return nullptr;
    }
    const auto it0 = node4key4ttype_.find(ttype.value());
    if (it0 == node4key4ttype_.end()) {
        return nullptr;
    }
    const auto it1 = it0->second.find(key.value());
    if (it1 == it0->second.end()) {
        return nullptr;
    }
    return it1->second;
}

/**
 *  for given index return distance from active range,
 *  or 0 if within active range
 *  distance is uint max for invalidated keys
 *
 * instead of just using previous active range
 * use the ranges informed by previous two SetActiveRaneg calls.
 * Obtain the scroll direction and use it to calc the distance.
 * Items left 'behind' when scrolling get larger distance and are more
 * likely updated or purged from L2 cache.
 */
uint32_t RepeatVirtualScrollCaches::GetDistanceFromRange(uint32_t index) const
{
    // distance is uint max for invalidated keys
    if (index == UINT32_MAX) {
        return UINT32_MAX;
    }
    uint32_t last[2] = { lastActiveRanges_[0].first, lastActiveRanges_[0].second };
    uint32_t prev[2] = { lastActiveRanges_[1].first, lastActiveRanges_[1].second };

    // this is experimental optimization, based on scrolling detection
    // here we assume this is a scrolling, if previous range and last range has
    // not empty intersection

    // if scrolling up, return 0 for any lower index
    if (last[0] < prev[0] && prev[0] < last[1]) {
        if (index < last[0]) {
            return 0;
        }
    }

    // if scrolling down, return 0 for any greater index
    if (last[0] < prev[1] && prev[1] < last[1]) {
        if (index > last[1]) {
            return 0;
        }
    }

    // this is not scrolling
    if (index < last[0]) {
        return last[0] - index;
    }

    if (index > last[1]) {
        return index - last[1];
    }

    return 0;
}

/**
 * scenario: find L1 key that should be updated
 * choose the key whose index is the furthest away from active range
 * given two keys compare their distFromRange
 */
bool RepeatVirtualScrollCaches::CompareKeyByIndexDistance(const std::string& key1, const std::string& key2) const
{
    return GetDistanceFromRange(GetIndex4Key(key1)) < GetDistanceFromRange(GetIndex4Key(key2));
}

/**
 * scenario: find L1 key(s) that should be updated
 *
 * return a sorted set of L2 keys, sorted by increasing distance from active range
 */
std::set<std::string, KeySorterClass> RepeatVirtualScrollCaches::GetSortedL2KeysForTType(
    const std::unordered_map<std::string, RefPtr<UINode>>& uiNode4Key) const
{
    KeySorterClass sorter(this);
    std::set<std::string, KeySorterClass> l2Keys(sorter);
    for (const auto& itUINode : uiNode4Key) {
        const auto& key = itUINode.first;
        if (activeNodeKeysInL1_.find(key) == activeNodeKeysInL1_.end()) {
            // key is not in L1
            // add to l2Keys
            l2Keys.emplace(key);
        }
    }
    return l2Keys;
}

std::string RepeatVirtualScrollCaches::DumpL1() const
{
    std::string result =
        "L1 (visible + pre-rendered items, their count defined by List/Grid.cacheCount: total number=" +
        std::to_string(activeNodeKeysInL1_.size()) + "--------------\n";
    for (const auto& it : activeNodeKeysInL1_) {
        const std::string& key = it;
        auto indexIter = index4Key_.find(key);
        if (indexIter == index4Key_.end()) {
            continue;
        }
        result += "  index " + std::to_string(indexIter->second) + " -> key: '" + key +
                  "', node: " + DumpUINodeWithKey(key) + "\n";
    }
    return result;
}

std::string RepeatVirtualScrollCaches::DumpL2() const
{
    std::unordered_map<std::string, RefPtr<UINode>> allCaches;
    for (const auto& [item, cacheItem] : node4key_) {
        allCaches.try_emplace(item, cacheItem.item);
    }
    std::set<std::string, KeySorterClass> l2KeyResult = GetSortedL2KeysForTType(allCaches);

    std::string result = "RecycleItem: Spare items available for update, not on render tree: size=" +
                         std::to_string(l2KeyResult.size()) + "--------------\n";
    for (const auto& it : l2KeyResult) {
        result += "   old key '" + it + "', node: " + DumpUINodeWithKey(it) + "\n";
    }
    return result;
}

std::string RepeatVirtualScrollCaches::DumpKey4Index() const
{
    std::string result = "key4index_: size=" + std::to_string(key4index_.size()) + "--------------\n";
    for (const auto& it : key4index_) {
        result += "   " + std::to_string(it.first) + " -> \"" + it.second +
                  "\", node: " + DumpUINodeWithKey(it.second) + "\n";
    }
    result += "index4Key_: size=" + std::to_string(index4Key_.size()) + "--------------\n";
    for (const auto& it : index4Key_) {
        result += "   \"" + it.first + "\" -> " + std::to_string(it.second) + "\n";
    }
    return result;
}

std::string RepeatVirtualScrollCaches::DumpTType4Index() const
{
    std::string result = "ttype4index_: size=" + std::to_string(ttype4index_.size()) + "--------------\n";
    for (const auto& it : ttype4index_) {
        result += "   " + std::to_string(it.first) + " -> \"" + it.second + "\n";
    }
    result += "index4ttype_: size=" + std::to_string(index4ttype_.size()) + "--------------\n";
    for (const auto& it : index4ttype_) {
        result += "   \"" + it.first + "\" -> " + std::to_string(it.second) + "\n";
    }
    return result;
}

std::string RepeatVirtualScrollCaches::DumpUINode4Key() const
{
    std::string result = "node4key_: size=" + std::to_string(node4key_.size()) + "--------------\n";
    for (const auto& it : node4key_) {
        result += "   \"" + it.first + "\" -> node: " + it.second.item->GetTag() + "(" +
                  std::to_string(it.second.item->GetId()) + ") \n";
    }
    return result;
}

std::string RepeatVirtualScrollCaches::DumpUINode4Key4TType() const
{
    std::string result = "node4key4ttype_: size=" + std::to_string(node4key4ttype_.size()) + "--------------\n";
    for (const auto& ttypeIter : node4key4ttype_) {
        const auto& ttype = ttypeIter.first;
        const auto& node4key = ttypeIter.second;
        result += "ttype " + ttype + ": node4key: size=" + std::to_string(node4key.size()) + "--------------\n";
        for (const auto& it : node4key) {
            result += "   \"" + it.first + "\" -> node: " + it.second->GetTag() + "(" +
                      std::to_string(it.second->GetId()) + ") \n";
        }
    }
    return result;
}

std::string RepeatVirtualScrollCaches::DumpUINodeWithKey(const std::string& key) const
{
    const auto it = node4key_.find(key);
    return (it == node4key_.end()) ? "no UINode on file"
                                   : it->second.item->GetTag() + "(" + std::to_string(it->second.item->GetId()) + ")";
}

std::string RepeatVirtualScrollCaches::DumpUINode(const RefPtr<UINode>& node) const
{
    return (node == nullptr) ? "UINode nullptr" : node->GetTag() + "(" + std::to_string(node->GetId()) + ")";
}
} // namespace OHOS::Ace::NG
