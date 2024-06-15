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

#include <cstdint>
#include <optional>
#include <unordered_map>
#include <unordered_set>

#include "base/log/log_wrapper.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/pipeline/base/element_register.h"

namespace OHOS::Ace::NG {

bool KeySorterClass::operator()(const std::string& left, const std::string& right) const
{
    return virtualScroll_->CompareKeyByIndexDistance(left, right);
}

RepeatVirtualScrollCaches::RepeatVirtualScrollCaches(const std::map<std::string, uint32_t>& cacheCountL24ttype,
    const std::function<void(uint32_t)>& onCreateNode,
    const std::function<void(const std::string&, uint32_t)>& onUpdateNode,
    const std::function<std::list<std::string>(uint32_t, uint32_t)>& onGetKeys4Range,
    const std::function<std::list<std::string>(uint32_t, uint32_t)>& onGetTypes4Range)
    : // each ttype incl default has own L2 cache size
      cacheCountL24ttype_(cacheCountL24ttype),
      // request TS to create new sub-tree for given index or update existing
      // update subtree cached for (old) index
      // FIXME API might need to change to tell which old item to update
      onCreateNode_(onCreateNode), onUpdateNode_(onUpdateNode), onGetTypes4Range_(onGetTypes4Range),
      onGetKeys4Range_(onGetKeys4Range)
{}

std::optional<std::string> RepeatVirtualScrollCaches::GetKey4Index(uint32_t index)
{
    auto it = key4index_.find(index);
    if (it == key4index_.end()) {
        // request more keys from TS key gen
        if (!FetchMoreKeysTTypes(index, index)) {
            return std::nullopt;
        }
    }
    return key4index_[index];
}

/**
 * get more index -> key and index -> ttype from TS side
 */
bool RepeatVirtualScrollCaches::FetchMoreKeysTTypes(uint32_t from, uint32_t to)
{
    // always request the same range for keys and ttype
    // TODO optimism by merging the two calls into one
    std::list<std::string> keysFrom = onGetKeys4Range_(from, to);
    std::list<std::string> ttypesFrom = onGetTypes4Range_(from, to);
    auto requestCount = to - from + 1;
    auto keySize = keysFrom.size();
    if (keySize != requestCount) {
        TAG_LOGE(AceLogTag::ACE_REPEAT, "fail to fetch keys: requst %{public}d, fetch %{public}d",
            static_cast<int32_t>(keySize), requestCount);
        return false;
    }
    auto ttypeSize = ttypesFrom.size();
    if (ttypeSize != requestCount) {
        TAG_LOGE(AceLogTag::ACE_REPEAT, "fail to fetch keys: requst %{public}d, fetch %{public}d",
            static_cast<int32_t>(keySize), requestCount);
        return false;
    }

    // fill-in index maps
    auto from1 = from;
    for (const auto& key : keysFrom) {
        key4index_[from1] = key;
        index4Key_[key] = from1;
        from1++;
    }
    from1 = from;
    for (const auto& ttype : ttypesFrom) {
        ttype4index_[from1] = ttype;
        index4ttype_[ttype] = from1;
        from1++;
    }
    return true;
}

// get UINode for given index without create.
RefPtr<UINode> RepeatVirtualScrollCaches::GetNode4Index(uint32_t index) const
{
    const auto it = key4index_.find(index);
    if (it == key4index_.end()) {
        TAG_LOGD(AceLogTag::ACE_REPEAT, "no UINode for index %{public}d", static_cast<int32_t>(index));
        return nullptr;
    }

    const std::string& key4Index = it->second;
    const auto nodeIter = node4key_.find(key4Index);
    if (nodeIter == node4key_.end()) {
        TAG_LOGE(AceLogTag::ACE_REPEAT, "no UINode for index %{public}d and key %{public}s",
            static_cast<int32_t>(index), key4Index.c_str());
        return nullptr;
    }
    return nodeIter->second;
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
    key4index_.clear();
    index4Key_.clear();
    ttype4index_.clear();
    index4ttype_.clear();

    // request new index -> key and index -> ttype
    // only fetch keys for the active range
    // note the updated key -> index reverse lookup is used
    // to decide if a key is still used and its UINode
    // should be packed. If key is not in the reverse map then
    // its UINode is subject to update.
    //
    FetchMoreKeysTTypes(lastActiveRanges_[0].first, lastActiveRanges_[0].second);
}

/**
 * scenario: scroll, try to update an existing UINode
 *
 * find an key / UINode in L2 and update the UINode to
 *   render the data source item 'forIndex'.
 */
RefPtr<UINode> RepeatVirtualScrollCaches::UpdateFromL2(uint32_t forIndex)
{
    const auto iterTType = ttype4index_.find(forIndex);
    if (iterTType == ttype4index_.end()) {
        TAG_LOGD(AceLogTag::ACE_REPEAT, "no ttype for index %{public}d", forIndex);
        return nullptr;
    }
    const auto& ttype = iterTType->second;
    const auto iterNewKey = key4index_.find(forIndex);
    if (iterNewKey == key4index_.end()) {
        TAG_LOGW(AceLogTag::ACE_REPEAT, "no key for index %{public}d", forIndex);
        return nullptr;
    }
    const std::string& forKey = iterNewKey->second;

    const auto& oldKey = GetL2KeyToUpdate(ttype);
    if (!oldKey) {
        // no key for this ttype available to update
        TAG_LOGW(AceLogTag::ACE_REPEAT, "for index %{public}d, ttype %{public}s, no UINode found to update", forIndex,
            ttype.c_str());
        return nullptr;
    }

    // call TS to do the RepeatItem update
    onUpdateNode_(oldKey.value(), forIndex);

    return HasUINodeBeenUpdated(ttype, oldKey.value(), forKey);
}

RefPtr<UINode> RepeatVirtualScrollCaches::CreateNewNode(uint32_t forIndex)
{
    // key key
    const auto iter = key4index_.find(forIndex);
    if (iter == key4index_.end()) {
        TAG_LOGE(AceLogTag::ACE_REPEAT, "fail to create node of %{public}d", forIndex);
        return nullptr;
    }
    const auto& forKey = iter->second;

    // see if node already created, just for safety
    const auto nodeIter = node4key_.find(forKey);
    if (nodeIter != node4key_.end()) {
        // have a node for this key already, just return
        return nodeIter->second;
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
            "New Node create: For index %{public}d -> key %{public}s -> ttype %{public}s item builder FAILED to gen "
            "FrameNode. ERROR",
            forIndex, forKey.c_str(), ttype.c_str());
        return nullptr;
    }

    // add node to node4key4ttype_
    const auto node4KeyIter = node4key4ttype_.find(ttype);
    if (node4KeyIter != node4key4ttype_.end()) {
        node4KeyIter->second.emplace(forKey, node4Index);
    } else {
        std::unordered_map<std::string, RefPtr<UINode>> node4Key;
        node4Key[forKey] = node4Index;
        node4key4ttype_.emplace(ttype, std::move(node4Key));
    }

    // add node to node4key_
    node4key_.emplace(forKey, node4Index);
    return node4Index;
}

void RepeatVirtualScrollCaches::ForEachL1IndexUINode(
    const std::function<void(uint32_t index, const RefPtr<UINode>& node)>& cbFunc)
{
    for (const auto& key : activeNodeKeysInL1_) {
        const RefPtr<UINode>& node = node4key_[key];
        const auto& indexIter = index4Key_.find(key);
        if (indexIter == index4Key_.end()) {
            TAG_LOGE(AceLogTag::ACE_REPEAT, "fail to get index for %{public}s key", key.c_str());
            continue;
        }
        cbFunc(indexIter->second, node);
    }
}

void RepeatVirtualScrollCaches::RecycleItemsByIndex(int32_t index)
{
    auto keyIter = key4index_.find(index);
    if (keyIter != key4index_.end()) {
        activeNodeKeysInL1_.erase(keyIter->second);
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
        const auto& node = node4key_[key];
        int32_t index = indexIter->second;
        if (cbFunc(index, node)) {
            activeNodeKeysInL1_.emplace(key);
        } else {
            modified = true;
        }
    }
    return modified;
}

/**/
void RepeatVirtualScrollCaches::SetLastActiveRange(uint32_t from, uint32_t to)
{
    lastActiveRanges_[1] = lastActiveRanges_[0];
    lastActiveRanges_[0] = { from, to };
}

/**
 * Get the Index of frameNode
 * return -1 if not find the frameNode
 */
int32_t RepeatVirtualScrollCaches::GetFrameNodeIndex(const RefPtr<FrameNode>& frameNode) const
{
    for (const auto& key : activeNodeKeysInL1_) {
        const auto nodeIter = node4key_.find(key);
        if (nodeIter == node4key_.end() || !nodeIter->second) {
            continue;
        }
        const auto& node = nodeIter->second->GetFrameChildByIndex(0, true);
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
std::optional<std::string> RepeatVirtualScrollCaches::GetL2KeyToUpdate(const std::string& ttype) const
{
    const auto itNodes = node4key4ttype_.find(ttype);
    if (itNodes == node4key4ttype_.end()) {
        return std::nullopt;
    }
    const auto& keys2UINode = itNodes->second;
    std::set<std::string, KeySorterClass> l2Keys = GetSortedL2KeysForTType(keys2UINode);
    auto keyIter = l2Keys.rbegin();
    if (keyIter == l2Keys.rend()) {
        return std::nullopt;
    }
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
                    return key;
                }
            }
        }
    }
    return std::nullopt;
}

/**
 * scenario: UINode of fromKey has been updated to render data for 'forKey'
 *     the template type (ttype) remains unchanged
 *     update node4key4ttype_ and node4key_ entries to use new key point to same UINode
 */
RefPtr<UINode> RepeatVirtualScrollCaches::HasUINodeBeenUpdated(
    const std::string& ttype, const std::string& fromKey, const std::string& forKey)
{
    // 1. update fromKey -> forKey in node4key4ttype_
    const auto nodesIter = node4key4ttype_.find(ttype);
    if (nodesIter != node4key4ttype_.end()) {
        auto& node4key = nodesIter->second;
        auto iter = node4key.find(fromKey);
        if (iter != node4key.end()) {
            const auto& node = iter->second;
            node4key.erase(iter);
            node4key.emplace(forKey, node);
        }
    }

    // 2. update the key: fromKey to forKey in node4key_
    auto iter = node4key_.find(fromKey);
    if (iter != node4key_.end()) {
        const auto& node = iter->second;
        node4key_.erase(iter);
        node4key_.emplace(forKey, node);
        return node;
    }
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
    bool didMakeChanges = false;
    for (auto& itTType : node4key4ttype_) {
        const auto& ttype = itTType.first;
        auto& uiNode4Key = itTType.second;
        const uint32_t cacheCount = cacheCountL24ttype_[ttype];
        std::set<std::string, KeySorterClass> l2Keys = GetSortedL2KeysForTType(uiNode4Key);

        // l2_keys is sorted by increasing distance from lastActiveRange
        // will drop those keys and their UINodes with largest distance
        // improvement idea: in addition to distance from range use the
        // scroll direction for selecting these keys
        auto safeDist = std::min(cacheCount, static_cast<uint32_t>(l2Keys.size()));
        auto itL2Key = std::next(l2Keys.begin(), safeDist);

        while (itL2Key != l2Keys.end()) {
            // delete remaining keys
            uiNode4Key.erase(*itL2Key);
            node4key_.erase(*itL2Key);
            // TODO: check out transition case.
            itL2Key++;
            didMakeChanges = true;
        }
    }
    return didMakeChanges;
}

/**
 * given key return the index position (reverse lookup)
 * invalidated keys (after Repeat rerender/ data change)
 * are keys for which no index exists anymore,
 * method returns int max value for these.
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
    return std::numeric_limits<uint32_t>::max();
}

/**
 *  for given index return distance from active range,
 *  or 0 if within active range
 *  distance is int max for invalidated keys
 *
 * TODO Denis: instead of just using previous active range
 * use the ranges informed by previous two SetActiveRaneg calls.
 * Obtain the scroll direction and use it to calc the distance.
 * Items left 'behind' when scrolling get larger distance and are more
 * likely updated or purged from L2 cache.
 */
int32_t RepeatVirtualScrollCaches::GetDistanceFromRange(uint32_t index) const
{
    int32_t last[2] = { lastActiveRanges_[0].first, lastActiveRanges_[0].second };
    int32_t prev[2] = { lastActiveRanges_[1].first, lastActiveRanges_[1].second };

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
    std::string result = "activeNodeKeysInL1_: size=" + std::to_string(activeNodeKeysInL1_.size()) + "--------------\n";
    for (const auto& it : activeNodeKeysInL1_) {
        const std::string& key = it;
        result += "\", node: " + DumpUINodeWithKey(key) + "\n";
    }
    return result;
}

std::string RepeatVirtualScrollCaches::DumpL2() const
{
    std::set<std::string, KeySorterClass> l2KeyResult = GetSortedL2KeysForTType(node4key_);

    std::string result =
        "l2_keys (sorted by distance): size=" + std::to_string(l2KeyResult.size()) + "--------------\n";
    for (const auto& it : l2KeyResult) {
        result += "   \"" + it + "\", node: " + DumpUINodeWithKey(it) + "\n";
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

std::string RepeatVirtualScrollCaches::DumpUINode4Key4TType() const
{
    std::string result = "node4key_: size=" + std::to_string(node4key_.size()) + "--------------\n";
    for (const auto& it : node4key_) {
        result += "   \"" + it.first + "\" -> node: " + it.second->GetTag() + "(" + std::to_string(it.second->GetId()) +
                  ") \n";
    }
    return result;
}

std::string RepeatVirtualScrollCaches::DumpUINode4Key() const
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
                                   : it->second->GetTag() + "(" + std::to_string(it->second->GetId()) + ")";
}

std::string RepeatVirtualScrollCaches::DumpUINode(const RefPtr<UINode>& node) const
{
    return (node == nullptr) ? "UINode nullptr" : node->GetTag() + "(" + std::to_string(node->GetId()) + ")";
}
} // namespace OHOS::Ace::NG
