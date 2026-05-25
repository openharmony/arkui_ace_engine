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
#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_RICH_EDITOR_LRU_CACHE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_RICH_EDITOR_LRU_CACHE_H

#include <list>
#include <unordered_map>
#include "base/memory/referenced.h"

namespace OHOS::Ace::NG {
template<typename KeyType, typename ValueType>
class LRUMap : public Referenced {
public:
    using Iterator = typename std::list<std::pair<KeyType, ValueType>>::iterator;

    LRUMap() {}
    LRUMap(size_t initialCapacity) : capacity(initialCapacity) {}

    Iterator Get(const KeyType& key)
    {
        auto it = cacheMap.find(key);
        if (it == cacheMap.end()) {
            return cacheList.end(); // Return end iterator if not found
        }

        // Move the accessed item to the front of the list
        cacheList.splice(cacheList.begin(), cacheList, it->second);

        return it->second;
    }

    Iterator End()
    {
        return cacheList.end();
    }

    size_t Size()
    {
        return cacheMap.size();
    }

    void Erase(const KeyType& key)
    {
        auto it = cacheMap.find(key);
        if (it != cacheMap.end()) {
            cacheList.erase(it->second);
            cacheMap.erase(it);
        }
    }

    void Clear()
    {
        cacheList.clear();
        cacheMap.clear();
    }

    void Put(const KeyType& key, const ValueType& value)
    {
        auto it = cacheMap.find(key);
        if (it != cacheMap.end()) {
            // Update existing item and move to front
            cacheList.splice(cacheList.begin(), cacheList, it->second);
            it->second->second = value;
        } else {
            // Insert new item
            if (cacheList.size() >= capacity) {
                // Remove least recently used item
                auto last = cacheList.end();
                last--;
                cacheMap.erase(last->first);
                cacheList.pop_back();
            }
            cacheList.emplace_front(key, value);
            cacheMap[key] = cacheList.begin();
        }
    }

    void SetCapacity(size_t newCapacity)
    {
        capacity = newCapacity;
        while (cacheList.size() > capacity) {
            auto last = cacheList.end();
            last--;
            cacheMap.erase(last->first);
            cacheList.pop_back();
        }
    }

private:
    size_t capacity = SIZE_MAX;
    std::list<std::pair<KeyType, ValueType>> cacheList;
    std::unordered_map<KeyType, Iterator> cacheMap;
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_RICH_EDITOR_LRU_CACHE_H