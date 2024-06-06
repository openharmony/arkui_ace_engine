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

#include <functional>
#include <map>
#include <queue>
#include <set>
#include <algorithm>

#include "base/memory/ace_type.h"
#include "base/utils/macros.h"
#include "base/utils/utils.h"
#include "core/components_ng/base/ui_node.h"

namespace OHOS::Ace::NG {

class RepeatVirtualScrollCaches {
public:
    RepeatVirtualScrollCaches(
        const uint32_t l2_cacheCount,
        const std::function<std::list<std::string>(uint32_t, uint32_t)>& onGetKeys4Range,
        const std::function<std::list<std::string>(uint32_t, uint32_t)>& onGetTypes4Range);

    // L1 cache
    //
    // is Map index -> key

    // find index in L1 cache:
    // pair.first false if not found, in this case pair.second is not set to proper value
    // pair.first true indicates found and result in pair.second
    std::pair<bool, std::string> getL1Key4Index(uint32_t index) const;

    // get UINode from L1 cache
    RefPtr<UINode> getL1Node4Index(uint32_t index) const;

    // add key to L1, caller needs ti make sure it is not in L2
    void addKeyToL1(uint32_t index, std::string key);

    // add key to L1, key is removed from L2 if it is there
    void addOrMoveKeyToL1(uint32_t index, std::string key);

    // remove entry with given index from L1
    bool removeFromL1ByIndex(uint32_t index);

    // iterate over all entries of L1 and call function for each entry
    // that function must not mutate L1
    void forEachL1IndexKey(std::function<void(int32_t, std::string)> cbFunc) const;

    // iterate over all entries of L1 and call function for each entry
    // that function must not mutate L1
    void forEachL1IndexUINode(std::function<void(int32_t, RefPtr<UINode>)> cbFunc) const;

    // iterate over all entries of L1 and call function for each entry
    // if function returns true, entry is added to rebuild L1, otherwise it is moved to L2
    // cbFunc return true, [index, key] pair stays in L1 (index remains unchanged)
    // cbFunc returns false, enqueue key in L2
    void rebuildL1(std::function<bool(int32_t, RefPtr<UINode>)> cbFunc);

    // update the key in L1 index -> key
    void updateL1Keys(std::function<std::string(int32_t index)> cbFunc);
    
    const std::string dumpL1() const;

    // L2 cache
    //
    // is queue of keys

    // min L2 size is 1
    void setL2CacheCount(int32_t totalCount)
    {
        l2CacheCount_ = totalCount > 0 ? totalCount : 1; 
    }
    
    uint32_t getL2CacheCount() const {
        return l2CacheCount_;
    }
    // purge, re-use form front of queue
    // hence the end of the queue is the 'safest' place for a key to 
    // stay in the L2 on next purge / re-use.
    // adding to queue can be from front or end, depending on the judgement 
    // if this item is up for re-use or purge or should stay in L2
    // add so the key is most safe to stay in L2 on next purge or re0seu
    void queueKeyL2(std::string key);

    // add so that the key is most likely to be purged or re-used.
    void queueToFrontKeyL2(std::string key);;

    // same as queueKeyL2 but makes sure the item is removed from L1
    void moveAndQueueKeyL2(uint32_t index, std::string key);

    // get the key at the front of the L2 queue, if any
    std::pair<bool, std::string> deQueueKeyL2();

    // return true of key is in L2
    bool hasKeyL2(std::string key) const;

    uint32_t sizeL2() const {
        return l2_queue_.size();
    }
    
    // remove key from queue
    // return true if it was found and removed
    bool removeKeyL2(std::string key);

    const std::string dumpL2() const;

    // keygen cache
    //
    // caches maps btw index and key to avoid having to call TS every time
    // resetKeyGenCache is called from TS whenever the mapping needs to change
    void fetchMoreKeys(uint32_t from, uint32_t to);

    std::pair<bool, std::string> getKey4Index(uint32_t index);

    // only for cached entries
    std::pair<bool, uint32_t> getIndex4Key(std::string key) const;

    // function called upon TS telling eys have changed
    void resetKeyGenCache();
    
    const std::string dumpKey4Index() const;

    // uinode4Key
    //
    // is a map key -> UINode
    RefPtr<UINode> getUINode4Key(std::string key) const;
    bool dropUINode4Key(std::string key);

    void addUINodeByIndex(uint32_t index, RefPtr<UINode> node);

    void addUINodeByKey(std::string key, RefPtr<UINode> node);

    const std::string dumpUINode4Key() const;
    const std::string dumpUINodeWithKey(std::string key) const;

    // enforce L2 cache size
    // shrink L2 to specified size,
    // remove additional nodes also from node4key_
    // leave key4index_ caches untouched
    bool purge();
    
private:
    uint32_t l2CacheCount_;
    std::function<std::list<std::string>(uint32_t, uint32_t)> onGetKeys4Range_;
    std::function<std::list<std::string>(uint32_t, uint32_t)> onGetTypes4Range_;
    std::map<uint32_t, std::string> l1_index2key_;
    std::list<std::string> l2_queue_;
    std::map<uint32_t, std::string> key4index_;
    std::map<std::string, uint32_t> index4Key_;
    std::map<std::string, RefPtr<UINode>> node4key_;
}; // class NodeCache

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_SYNTAX_REPEAT_VIRTUAL_SCROLL_CACHES_H
