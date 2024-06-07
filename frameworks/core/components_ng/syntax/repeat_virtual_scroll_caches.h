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

#include <algorithm>
#include <functional>
#include <limits>
#include <map>
#include <queue>
#include <set>
#include <string>

#include "base/memory/ace_type.h"
#include "base/utils/macros.h"
#include "base/utils/utils.h"
#include "core/components_ng/base/ui_node.h"

namespace OHOS::Ace::NG {

// custom sorting for std::set only works with struct 
// with operator() inside
class RepeatVirtualScrollCaches;
struct KeySorterClass {
public:
    const RepeatVirtualScrollCaches* thiz_;

    KeySorterClass(const RepeatVirtualScrollCaches* thiz)
    {
        thiz_ = thiz;
    }
    bool operator()(const std::string& a, const std::string& b) const;
};

class RepeatVirtualScrollCaches {
     friend struct KeySorterClass;
public:
    /**
      * for given index get key
      * fetch from TS if not in cache
      * return false if index out of range
     */
    std::pair<bool, std::string> getKey4Index(uint32_t index);

public:
    RepeatVirtualScrollCaches(const uint32_t l2_cacheCount, const std::function<void(uint32_t)>& onCreateNode,
        const std::function<void(const std::string&, uint32_t)>& onUpdateNode,
        const std::function<std::list<std::string>(uint32_t, uint32_t)>& onGetKeys4Range,
        const std::function<std::list<std::string>(uint32_t, uint32_t)>& onGetTypes4Range);

public:
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
    void invalidateKeyAndTTypeCaches();

public:
    /**
         * scenario: scroll, try to update an existing UINode
         *
         * find an key / UINode in L2 and update the UINode to
         *   render the data source item 'forIndex'.
         */
    RefPtr<UINode> updateFromL2(uint32_t forIndex);

    /**
      * request TS to create a new node for given index / key/
     */
    RefPtr<UINode> createNewNode(uint32_t forIndex);

    // iterate over L1 keys, not allowed to modify L1
    void forEachL1IndexUINode(std::function<void(uint32_t index, RefPtr<UINode> node)> cbFunc);

private:
    /**
         * intended scenario: scroll
         * servicing GetFrameChild, search for key that can be updated.
         *
         * return a key whose UINode can be updated
         * the key must not be in L1, i.e. l1_activeNodeKeys_
         * the given ttype must match the template type the UINode for this key
         * has been rendered for (this info is available from node4key4ttype_)
         */
    std::pair<bool, std::string> getL2KeyToUpdate(const std::string ttype) const;

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
    std::pair<bool, std::string> getL1KeyToUpdate(const std::string ttype) const;

    /**
         * scenario: UINode of fromKey has been updated to render data for 'forKey'
         *     the template type (ttype) remains unchanged
         *     update node4key4ttype_ and node4key_ entries to use new key point to same UINode
         */
    RefPtr<UINode> uiNodeHasBeenUpdated(std::string ttype, std::string fromKey, std::string forKey);

    /** scenario: keys cache has been updated
         *
         * find which keys in key -> UINode map are no longer used
         * returned set entries are pairs:
         *   pair.first: is this key a L1 item,
         *   pair.second: key
         */
    void findUnusedKeys(std::set<std::pair<bool, std::string>>& result) const;


public:
    /**
      * iterate over all entries of L1 and call function for each entry
      * if function returns true, entry is added to rebuild L1, otherwise it is moved to L2
      * cbFunc return true, [index, key] pair stays in L1 (index remains unchanged)
      * cbFunc returns false, enqueue key in L2
      */
    void rebuildL1(std::function<bool(std::string key, RefPtr<UINode> node)> cbFunc);

    /**
         * scenario: in idle process , following GetChildren()
         *
         * enforce L2 cacheCount for each ttype
         * by deleting UINodes, delete their entry from
         *   node4key4ttype_ and node4key_
         *   FIXME haoyu: any other processing steps needed before UINode
         *                tree can be deleted
         */
    bool purge();

    /**
      * return the UINode for given index
      * bool return indicates if in L1
      * 
      * resolve index -> key -> UINode
      * 
     */
    std::pair<bool, RefPtr<UINode>> getNode4Index(uint32_t forIndex) const;

    void addKeyToL1(const std::string key)
    {
        l1_activeNodeKeys_.emplace(key);
    }

     void MemorizeActiveRange(uint32_t from, uint32_t to) {
          lastActiveRange_.first = from; 
          lastActiveRange_.second = to;
     }

private:
    /**
         * given ley return the index position (reverse lookup)
         * invalidated keys (after Repeat rerender/ data change)
         * are keys for which no index exists anymore,
         * method returns int max value for these.
         * int max value causes that distance from active range is max
         * these keys will be selected for update first.
         */
    uint32_t getIndex4Key2(const std::string& key) const;

    /**
         *  for given index return distance from active range,
         *  or 0 if within active range
         *  distance is int max for invalidated keys
         */
    int32_t distFromRange(uint32_t index) const;
    /**
         * scenario: find L1 key that should be updated
         * choose the key whose index is the furthest away from active range
         * given two keys compare their distFromRange
         */
    bool cmpKeyByIndexDistance(const std::string& key1, const std::string& key2) const;

    /**
         * scenario: find L1 key(s) that should be updated
         *
         * return a sorted set of L2 keys, sorted by increasing distance from active range
         */
    std::function<bool(const std::string, const std::string)> l2KeyDistanceComparator =
        [&](const std::string& keyA, const std::string& keyB) -> bool { return cmpKeyByIndexDistance(keyA, keyB); };
    decltype(l2KeyDistanceComparator) l2KeyDistanceComparatorType;

    std::set<std::string, KeySorterClass> getSortedL2KeysForTType(
        const std::map<std::string, RefPtr<UINode>>& uiNode4Key) const;

    /**
      * get more index -> key and index -> ttype from TS side
     */
    void FetchMoreKeysTTypes(uint32_t from, uint32_t to);

public:
    // formatting internal structures to string for debug output
    // and possibly in modified form for DFX in the future
    const std::string dumpL1() const;
    const std::string dumpL2() const;
    const std::string dumpKey4Index() const;
    const std::string dumpTType4Index() const;
    const std::string dumpUINode4Key4TType() const;
    const std::string dumpUINode4Key() const;

    const std::string dumpUINodeWithKey(std::string key) const;
    const std::string dumpUINode(const RefPtr<UINode>& node) const;

private:
    // FIXME each ttype incl default has own L2 size
    // uint32_t l2CacheCount_;

    // request TS to create new sub-tree for given index or update existing
    // update subtree cached for (old) index
    // FIXME API might need to change to tell which old item to update
    std::function<void(uint32_t)> onCreateNode_;
    std::function<void(const std::string&, uint32_t)> onUpdateNode_;

    // get index -> key for given range
    // resulting list starts with 'from' but might end before 'to' if Array shorter
    std::function<std::list<std::string>(uint32_t, uint32_t)> onGetTypes4Range_;

    // get index -> ttype for given range
    // resulting list starts with 'from' but might end before 'to' if Array shorter
    std::function<std::list<std::string>(uint32_t, uint32_t)> onGetKeys4Range_;

     // TODO Denis: memorize active ranges of past 2 
     // SetActiveRange calls and use to calc scroll direction
    std::pair<uint32_t, uint32_t> lastActiveRange_;

    // keys of active nodes, UINodes must be on the render tree, 
    // this list is also known as L1
    // all keys not in this set are in "L2"
    std::set<std::string> l1_activeNodeKeys_;

    // L1
    // index -> key and reverse
    // lazy request from TS side can be invalidated
    std::map<uint32_t, std::string> key4index_;
    std::map<std::string, uint32_t> index4Key_;

    // index -> ttype
    // lazy request from TS side can be invalidated
    std::map<uint32_t, std::string> ttype4index_;
    std::map<std::string, uint32_t> index4ttype_;

    // Map ttype -> cacheSize
    std::map<std::string, uint32_t> cacheCountL24ttype_;

    // Map ttype -> Map key -> UINode
    std::map<std::string, std::map<std::string, RefPtr<UINode>>> node4key4ttype_;

    // Map Map key -> UINode
    std::map<std::string, RefPtr<UINode>> node4key_;
}; // class NodeCache

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_SYNTAX_REPEAT_VIRTUAL_SCROLL_CACHES_H
