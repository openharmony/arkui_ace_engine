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

namespace OHOS::Ace::NG {

RepeatVirtualScrollCaches::RepeatVirtualScrollCaches(
    const uint32_t l2_cacheCount,
    const std::function<std::list<std::string>(uint32_t, uint32_t)>& onGetKeys4Range,
    const std::function<std::list<std::string>(uint32_t, uint32_t)>& onGetTypes4Range)
    : l2CacheCount_(l2_cacheCount > 0 ? l2_cacheCount : 1), // min L2 size is 1
      onGetKeys4Range_(onGetKeys4Range), onGetTypes4Range_(onGetTypes4Range)
{}

// L1 cache
//
// is Map index -> key

// find index in L1 cache:
// pair.first false if not found, in this case pair.second is not set to proper value
// pair.first true indicates found and result in pair.second
std::pair<bool, std::string> RepeatVirtualScrollCaches::getL1Key4Index(uint32_t index) const
{
    const auto it = l1_index2key_.find(index);
    if (it == l1_index2key_.end()) {
        return std::pair<bool, std::string>(false, "");
    } else {
        return std::pair<bool, std::string>(true, it->second);
    }
}

// get UINode from L1 cache
RefPtr<UINode> RepeatVirtualScrollCaches::getL1Node4Index(uint32_t index) const
{
    const auto pair = getL1Key4Index(index);
    return pair.first ? getUINode4Key(pair.second) : nullptr;
}

// add key to L1, caller needs ti make sure it is not in L2
void RepeatVirtualScrollCaches::addKeyToL1(uint32_t index, std::string key)
{
    l1_index2key_[index] = key;
}

// add key to L1, key is removed from L2 if it is there
void RepeatVirtualScrollCaches::addOrMoveKeyToL1(uint32_t index, std::string key)
{
    l1_index2key_[index] = key;
    removeKeyL2(key);
}

// remove entry with given index from L1
bool RepeatVirtualScrollCaches::removeFromL1ByIndex(uint32_t index)
{
    return l1_index2key_.erase(index) > 0;
}

// iterate over all entries of L1 and call function for each entry
// that function must not mutate L1
void RepeatVirtualScrollCaches::forEachL1IndexKey(std::function<void(int32_t, std::string)> cbFunc) const
{
    for (auto pair : l1_index2key_) {
        cbFunc(pair.first, pair.second);
    }
}

// iterate over all entries of L1 and call function for each entry
// that function must not mutate L1
void RepeatVirtualScrollCaches::forEachL1IndexUINode(std::function<void(int32_t, RefPtr<UINode>)> cbFunc) const
{
    for (auto pair : l1_index2key_) {
        cbFunc(pair.first, getUINode4Key(pair.second));
    }
}
// iterate over all entries of L1 and call function for each entry
// if function returns true, entry is added to rebuild L1, otherwise it is moved to L2
// cbFunc return true, [index, key] pair stays in L1 (index remains unchanged)
// cbFunc returns false, enqueue key in L2
void RepeatVirtualScrollCaches::rebuildL1(std::function<bool(int32_t, RefPtr<UINode>)> cbFunc)
{
    std::map<uint32_t, std::string> l1_index2key__copy;
    std::swap(l1_index2key__copy, l1_index2key_);
    for (auto pair : l1_index2key__copy) {
        if (cbFunc(pair.first, node4key_[pair.second])) {
            l1_index2key_[pair.first] = pair.second;
        } else {
            // items removed from L1 are considered first candidate for purge or re-use
            // hence, put to front of L2 queue
            queueToFrontKeyL2(pair.second);
        }
    }
}

void RepeatVirtualScrollCaches::updateL1Keys(std::function<std::string(int32_t index)> cbFunc)
{
    std::map<uint32_t, std::string> l1_index2key__copy;
    std::swap(l1_index2key__copy, l1_index2key_);
    for (auto pair : l1_index2key__copy) {
        l1_index2key_[pair.first] = cbFunc(pair.first);
    }
}

const std::string RepeatVirtualScrollCaches::dumpL1() const
{
    std::string result = "l1_index2key_: size=" + std::to_string(l1_index2key_.size()) + "--------------\n";
    for (auto it : l1_index2key_) {
        result += "   " + std::to_string(it.first) + " -> \"" + it.second +
                  "\", node: " + dumpUINodeWithKey(it.second) + "\n";
    }
    return result;
}

// L2 cache
//
// is queue of keys
// add key to back of queue, or reset its position to back of queue
void RepeatVirtualScrollCaches::queueKeyL2(std::string key)
{
    const auto it = std::find(l2_queue_.begin(), l2_queue_.end(), key);
    if (it != l2_queue_.end()) {
        // if already in L2, take it out from its current position
        l2_queue_.erase(it);
    }
    // add at the end
    l2_queue_.emplace_back(key);
}

// add key to front of queue, or reset its position to back of queue
void RepeatVirtualScrollCaches::queueToFrontKeyL2(std::string key)
{
    const auto it = std::find(l2_queue_.begin(), l2_queue_.end(), key);
    if (it != l2_queue_.end()) {
        // if already in L2, take it out from its current position
        l2_queue_.erase(it);
    }
    // add at front of queue, first to be re-used or purged
    l2_queue_.emplace_front(key);
}

void RepeatVirtualScrollCaches::moveAndQueueKeyL2(uint32_t index, std::string key)
{
    removeFromL1ByIndex(index);
    const auto it = std::find(l2_queue_.begin(), l2_queue_.end(), key);
    if (it != l2_queue_.end()) {
        // if already in L2, take it out from its current position
        l2_queue_.erase(it);
    }
    l2_queue_.emplace_back(key);
}

// get the key at the front of the L2 queue, if any
std::pair<bool, std::string> RepeatVirtualScrollCaches::deQueueKeyL2()
{
    const auto it = l2_queue_.begin();
    if (it != l2_queue_.end()) {
        const std::string result = *it;
        l2_queue_.erase(it);
        return std::pair<bool, std::string>(true, result);
    }
    return std::pair<bool, std::string>(false, "");
}

// return true of key is in L2
bool RepeatVirtualScrollCaches::hasKeyL2(std::string key) const
{
    return (std::find(l2_queue_.begin(), l2_queue_.end(), key) != l2_queue_.end());
}

// remove key from queue
// return true if it was found and removed
bool RepeatVirtualScrollCaches::removeKeyL2(std::string key)
{
    const auto it = std::find(l2_queue_.begin(), l2_queue_.end(), key);
    if (it != l2_queue_.end()) {
        l2_queue_.erase(it);
        return true;
    }
    return false;
}

const std::string RepeatVirtualScrollCaches::dumpL2() const
{
    std::string result = "l2_queue_: size=" + std::to_string(l2_queue_.size()) + "--------------\n";
    for (auto it : l2_queue_) {
        result += "   \"" + it + "\", node: " + dumpUINodeWithKey(it) + "\n";
    }
    return result;
}

bool RepeatVirtualScrollCaches::purge()
{
    if (l2_queue_.size() <= l2CacheCount_) {
        LOGE("L2 size %{public}d does not exceed cacheCount %{public}d, nothing to do.", (int)l2_queue_.size(),
            (int)l2CacheCount_);
        return false;
    }

    LOGE("L2 size %{public}d  exceeds cacheCount %{public}d, purging ...", (int)l2_queue_.size(), (int)l2CacheCount_);

    // rebuild node4key_
    std::map<std::string, RefPtr<UINode>> node4key_copy;
    std::swap(node4key_, node4key_copy);

    // rebuild node4key_ step 1: re-insert nodes for L1 keys
    forEachL1IndexKey([&, node4key_copy](int32_t index, std::string key) {
        const auto node4keyIter = node4key_copy.find(key);
        if (node4keyIter != node4key_copy.end()) {
            // re-insert node for L1 Key to node4key_
            node4key_[key] = node4keyIter->second;
        }
    });

    // rebuild node4key_ step 2: rebuild L2 up to permissable size
    // at the same time re-insert keys to node4key_
    std::list<std::string> l2_queue_copy;
    std::swap(l2_queue_, l2_queue_copy);

    auto l2KeyIter = l2_queue_copy.end();
    l2KeyIter--;
    do {
        // re-insert first 'l2_cacheCount_' items into rebuild l2
        l2_queue_.emplace_back(*l2KeyIter);

        const auto node4keyIter = node4key_copy.find(*l2KeyIter);
        if (node4keyIter != node4key_copy.end()) {
            // re-insert node for L1 Key to node4key_
            node4key_[*l2KeyIter] = node4keyIter->second;
        }

        l2KeyIter--;
    } while (l2_queue_.size() < l2CacheCount_);

    return true;
} // purge

// keygen cache
//
// caches maps btw index and key to avoid having to call TS every time
// resetKeyGenCache is called from TS whenever the mapping needs to change
void RepeatVirtualScrollCaches::fetchMoreKeys(uint32_t from, uint32_t to)
{
    auto result = onGetKeys4Range_(from, to);
    for (auto it : result) {
        key4index_[from] = it;
        index4Key_[it] = from;
        from++;
    }
}

std::pair<bool, std::string> RepeatVirtualScrollCaches::getKey4Index(uint32_t index)
{
    auto it = key4index_.find(index);
    if (it == key4index_.end()) {
        // request more keys from TS key gen
        fetchMoreKeys(index, index + 4);
        it = key4index_.find(index);
        if (it == key4index_.end()) {
            return std::pair<bool, std::string>(false, "");
        }
    }
    return std::pair<bool, std::string>(true, it->second);
}

// only for cached entries
std::pair<bool, uint32_t> RepeatVirtualScrollCaches::getIndex4Key(std::string key) const
{
    const auto it = index4Key_.find(key);
    if (it == index4Key_.end()) {
        return std::pair<bool, uint32_t>(false, -1);
    } else {
        return std::pair<bool, uint32_t>(true, it->second);
    }
}

// function called upon TS telling eys have changed
void RepeatVirtualScrollCaches::resetKeyGenCache()
{
    key4index_.clear();
    index4Key_.clear();


}

const std::string RepeatVirtualScrollCaches::dumpKey4Index() const
{
    std::string result = "key4index_: size=" + std::to_string(key4index_.size()) + "--------------\n";
    for (auto it : key4index_) {
        result += "   " + std::to_string(it.first) + " -> \"" + it.second +
                  "\", node: " + dumpUINodeWithKey(it.second) + "\n";
    }
    result += "index4Key_: size=" + std::to_string(index4Key_.size()) + "--------------\n";
    for (auto it : index4Key_) {
        result += "   \"" + it.first + "\" -> " + std::to_string(it.second) + "\n";
    }
    return result;
}

// uinode4Key
//
// is a map key -> UINode
RefPtr<UINode> RepeatVirtualScrollCaches::getUINode4Key(std::string key) const
{
    const auto it = node4key_.find(key);
    return (it == node4key_.end()) ? nullptr : it->second;
}

bool RepeatVirtualScrollCaches::dropUINode4Key(std::string key)
{
    return node4key_.erase(key) > 0;
}
void RepeatVirtualScrollCaches::addUINodeByIndex(uint32_t index, RefPtr<UINode> node)
{
    const auto pair = getKey4Index(index);
    if (pair.first) {
        addUINodeByKey(pair.second, node);
    } else {
        // FIXME throw ERROR
    }
}
void RepeatVirtualScrollCaches::addUINodeByKey(std::string key, RefPtr<UINode> node)
{
    node4key_[key] = node;
}

const std::string RepeatVirtualScrollCaches::dumpUINode4Key() const
{
    std::string result = "node4key_: size=" + std::to_string(node4key_.size()) + "--------------\n";
    for (auto it : node4key_) {
        result += "   \"" + it.first + "\" -> node: " + it.second->GetTag() + "(" + std::to_string(it.second->GetId()) +
                  ") \n";
    }
    return result;
}

const std::string RepeatVirtualScrollCaches::dumpUINodeWithKey(std::string key) const
{
    const auto it = node4key_.find(key);
    return (it == node4key_.end()) ? "no UINode on file"
                                   : it->second->GetTag() + "(" + std::to_string(it->second->GetId()) + ")";
}

} // namespace OHOS::Ace::NG
