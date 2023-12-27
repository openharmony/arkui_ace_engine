/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include "core/common/lru/count_limit_lru.h"

namespace OHOS::Ace {
template<typename T>
void CountLimitLRU::CacheWithCountLimitLRU(const std::string& key, const T& cacheObj,
    std::list<CacheNode<T>>& cacheList,
    std::unordered_map<std::string, typename std::list<CacheNode<T>>::iterator>& cache,
    const std::atomic<size_t>& capacity)
{
    auto iter = cache.find(key);
    if (iter == cache.end()) {
        if (cache.size() == capacity) {
            cache.erase(cacheList.back().cacheKey);
            cacheList.pop_back();
        }
        cacheList.emplace_front(key, cacheObj);
        cache.emplace(key, cacheList.begin());
    } else {
        iter->second->cacheObj = cacheObj;
        cacheList.splice(cacheList.begin(), cacheList, iter->second);
        iter->second = cacheList.begin();
    }
}

template<typename T>
T CountLimitLRU::GetCacheObjWithCountLimitLRU(const std::string& key, std::list<CacheNode<T>>& cacheList,
    std::unordered_map<std::string, typename std::list<CacheNode<T>>::iterator>& cache)
{
    auto iter = cache.find(key);
    if (iter != cache.end()) {
        cacheList.splice(cacheList.begin(), cacheList, iter->second);
        iter->second = cacheList.begin();
        return iter->second->cacheObj;
    }
    return nullptr;
}

template<typename T>
void CountLimitLRU::RemoveCacheObjFromCountLimitLRU(const std::string& key, std::list<CacheNode<T>>& cacheList,
    std::unordered_map<std::string, typename std::list<CacheNode<T>>::iterator>& cache)
{
    auto iter = cache.find(key);
    if (iter != cache.end()) {
        cacheList.erase(iter->second);
        cache.erase(key);
    }
}
} // namespace OHOS::Ace
