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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_SYNTAX_REPEAT_VIRTUAL_SCROLL_CACHES_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_SYNTAX_REPEAT_VIRTUAL_SCROLL_CACHES_H

#include <cstdint>
#include <functional>
#include <map>
#include <optional>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>

#include "base/memory/referenced.h"
#include "core/components_ng/base/ui_node.h"

namespace OHOS::Ace::NG {

// custom sorting for std::set only works with struct
// with operator() inside
class RepeatVirtualScrollCaches;
struct CacheItem {
    bool isValid = false;
    RefPtr<UINode> item;
};

class RepeatVirtualScrollCaches {
public:
    RepeatVirtualScrollCaches(const std::map<std::string, std::pair<bool, uint32_t>>& cacheCountL24ttype,
        const std::function<void(uint32_t)>& onCreateNode,
        const std::function<void(const std::string&, uint32_t)>& onUpdateNode,
        const std::function<std::list<std::string>(uint32_t, uint32_t)>& onGetKeys4Range,
        const std::function<std::list<std::string>(uint32_t, uint32_t)>& onGetTypes4Range,
        bool reusable = true);

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
    void InvalidateKeyAndTTypeCaches();

    /**
     * scenario: scroll, try to update an existing UINode
     *
     * find an key / UINode in L2 and update the UINode to
     *   render the data source item 'forIndex'.
     */
    RefPtr<UINode> UpdateFromL2(uint32_t forIndex);

    void UpdateSameKeyItem(const std::string& key, uint32_t index);

    /**
     * request TS to create a new node for given index / key/
     */
    RefPtr<UINode> CreateNewNode(uint32_t forIndex);

    // iterate over L1 keys, not allowed to modify L1
    void ForEachL1IndexUINode(std::map<int32_t, RefPtr<UINode>>& children);

    void RecycleItemsByIndex(int32_t index);

    /**
     * for given index get key
     * fetch from TS if not in cache (if allowFetch == true)
     * return false if index out of range
     */
    std::optional<std::string> GetKey4Index(uint32_t index, bool allowFetch);

    /**
     * iterate over all entries of L1 and call function for each entry
     * if function returns true, entry is added to rebuild L1, otherwise it is moved to L2
     * cbFunc return true, [index, key] pair stays in L1 (index remains unchanged)
     * cbFunc returns false, enqueue key in L2
     */
    bool RebuildL1(const std::function<bool(int32_t index, const RefPtr<UINode>& node)>& cbFunc);

    /**
     * dito with only key as cb function parameter
     */
    bool RebuildL1WithKey(const std::function<bool(const std::string& key)>& cbFunc);
    
    /*
        drop L1 entry with given index from L1
        keep it in L2
        return the affected UINode
        caller responsibility to detach this UINode from the UI tree!
    */
    RefPtr<UINode> DropFromL1(const std::string& key);

    int32_t GetFrameNodeIndex(const RefPtr<FrameNode>& frameNode) const;

    /**
     * scenario: in idle process , following GetChildren()
     *
     * enforce L2 cacheCount for each ttype
     * by deleting UINodes, delete their entry from
     * node4key4ttype_ and node4key_
     * any other processing steps needed before UINode
     * tree can be deleted
     */
    bool Purge();

    /**
     * return the cached UINode for given index
     *
     * resolve index -> key -> UINode
     *
     */
    RefPtr<UINode> GetCachedNode4Index(uint32_t forIndex);

    void AddKeyToL1(const std::string& key, bool shouldTriggerReuse = true);

    void AddKeyToL1WithNodeUpdate(const std::string& key, uint32_t index, bool shouldTriggerRecycle);

    void RemoveKeyFromL1(const std::string& key, bool shouldTriggerRecycle = true);

    bool CheckTTypeChanged(uint32_t index);

    bool IsInL1Cache(const std::string& key) const
    {
        return activeNodeKeysInL1_.find(key) != activeNodeKeysInL1_.end();
    }

    const std::unordered_map<std::string, CacheItem>& GetAllNodes() const
    {
        return node4key_;
    }

    /**
     * memorize last active range(s)
     */
    void SetLastActiveRange(uint32_t from, uint32_t to);
    std::pair<uint32_t, uint32_t> GetLastActiveRange() { return lastActiveRanges_[0]; };

    // formatting internal structures to string for debug output
    // and possibly in modified form for DFX in the future
    std::string DumpL1() const;
    std::string DumpL2() const;
    std::string DumpKey4Index() const;
    std::string DumpTType4Index() const;
    std::string DumpUINode4Key4TType() const;
    std::string DumpUINode4Key() const;

    std::string DumpUINodeWithKey(const std::string& key) const;
    std::string DumpUINode(const RefPtr<UINode>& node) const;

private:
    /**
     * intended scenario: scroll
     * servicing GetFrameChild, search for key that can be updated.
     *
     * return a key whose UINode can be updated
     * the key must not be in L1, i.e. activeNodeKeysInL1_
     * the given ttype must match the template type the UINode for this key
     * has been rendered for (this info is available from node4key4ttype_)
     */
    std::optional<std::string> GetL2KeyToUpdate(const std::optional<std::string>& ttype) const;

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
    std::optional<std::string> GetL1KeyToUpdate(const std::string& ttype) const;

    /**
     * scenario: UINode of fromKey has been updated to render data for 'forKey'
     *     the template type (ttype) remains unchanged
     *     update node4key4ttype_ and node4key_ entries to use new key point to same UINode
     */
    RefPtr<UINode> UINodeHasBeenUpdated(
        const std::string& ttype, const std::string& fromKey, const std::string& forKey);

    /** scenario: keys cache has been updated
     *
     * find which keys in key -> UINode map are no longer used
     * returned set entries are pairs:
     *   pair.first: is this key a L1 item,
     *   pair.second: key
     */
    void FindUnusedKeys(std::set<std::pair<bool, std::string>>& result) const;

    /**
     * given key return the index position (reverse lookup)
     * invalidated keys (after Repeat rerender/ data change)
     * are keys for which no index exists anymore,
     * method returns int max value for these.
     * int max value causes that distance from active range is max
     * these keys will be selected for update first.
     */
    uint32_t GetIndex4Key(const std::string& key) const;

    /**
     * find UINode for given key, irrespective of ttype in ttype4index_
     */
    std::optional<std::string> GetTType4Index(uint32_t index);

    /** find in node4key_ */
    std::optional<CacheItem> GetCachedNode4Key(const std::optional<std::string>& key);
    
    /**
     *  if key and ttype given, search for UINode of given key and ttype
     * in caches, i.e. in node4key4ttype
    * return nullptr in all other cases
    */
    RefPtr<UINode> GetCachedNode4Key4Ttype(
        const std::optional<std::string>& key, const std::optional<std::string>& ttype);

    /**
     *  for given index return distance from active range,
     *  or 0 if within active range
     *  distance is int max for invalidated keys
     */
    uint32_t GetDistanceFromRange(uint32_t index) const;
    /**
     * scenario: find L1 key that should be updated
     * choose the key whose index is the furthest away from active range
     * given two keys compare their distFromRange
     */
    bool CompareKeyByIndexDistance(const std::string& key1, const std::string& key2) const;

    std::set<std::string> GetL2KeysForTType(
        const std::unordered_map<std::string, RefPtr<UINode>>& uiNode4Key) const;

    /**
     * does given range overlap the last active range?
     */
    bool HasOverlapWithLastActiveRange(uint32_t from, uint32_t to);

    /**
     * get more index -> key and index -> ttype from TS side
     * may request additional keys if allowFetchMore is true
     */
    bool FetchMoreKeysTTypes(uint32_t from, uint32_t to, bool allowFetchMore = true);

    // Map ttype -> cacheSize. Each ttype incl default has own L2 size
    std::map<std::string, std::pair<bool, uint32_t>> cacheCountL24ttype_;

    // request TS to create new sub-tree for given index or update existing
    // update subtree cached for (old) index
    // API might need to change to tell which old item to update
    std::function<void(uint32_t)> onCreateNode_;
    std::function<void(const std::string&, uint32_t)> onUpdateNode_;

    // get index -> key for given range
    // resulting list starts with 'from' but might end before 'to' if Array shorter
    std::function<std::list<std::string>(uint32_t, uint32_t)> onGetTypes4Range_;

    // get index -> ttype for given range
    // resulting list starts with 'from' but might end before 'to' if Array shorter
    std::function<std::list<std::string>(uint32_t, uint32_t)> onGetKeys4Range_;

    // memorize active ranges of past 2 (last, prev)
    // from SetActiveChildRange calls and use to calc scroll direction
    // active range:= visible range + pre-render items above and below
    // number of pre-render items defined by Gird/List.cacheCount and informed
    // as cacheStart and cacheEnd in SetActiveChildRange
    std::pair<uint32_t, uint32_t> lastActiveRanges_[2] = { { 0, 0 }, { 0, 0 } };

    // keys of active nodes, UINodes must be on the UI tree,
    // this list is also known as L1
    // all keys not in this set are in "L2"
    std::unordered_set<std::string> activeNodeKeysInL1_;

    // L1
    // index -> key and reverse
    // lazy request from TS side can be invalidated
    std::unordered_map<uint32_t, std::string> key4index_;
    std::unordered_map<std::string, uint32_t> index4Key_;

    // index -> ttype
    // lazy request from TS side can be invalidated
    std::unordered_map<uint32_t, std::string> ttype4index_;
    std::unordered_map<std::string, uint32_t> index4ttype_;

    // Map ttype -> Map key -> UINode
    std::unordered_map<std::string, std::unordered_map<std::string, RefPtr<UINode>>> node4key4ttype_;

    // Map Map key -> UINode
    std::unordered_map<std::string, CacheItem> node4key_;

    // for tracking reused/recycled nodes
    std::unordered_set<int32_t> reusedNodeIds_;

    // used to record whether a PostIdleTask is requeired after RebuildL1WithKey
    bool isModified_ = false;

    // reuse node in L2 cache or not
    bool reusable_ = true;
}; // class NodeCache

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_SYNTAX_REPEAT_VIRTUAL_SCROLL_CACHES_H
