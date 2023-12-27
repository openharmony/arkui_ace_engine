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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_LRU_COUNT_LIMIT_LRU_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_LRU_COUNT_LIMIT_LRU_H
#include <atomic>
#include <list>
#include <string>
#include <unordered_map>
#include <utility>

#include "base/memory/ace_type.h"

namespace OHOS::Ace {
template<typename T>
struct CacheNode {
    CacheNode(std::string key, const T& obj) : cacheKey(std::move(key)), cacheObj(obj) {}
    std::string cacheKey;
    T cacheObj;
};

class CountLimitLRU : public AceType {
    DECLARE_ACE_TYPE(CountLimitLRU, AceType);

public:
    template<typename T>
    static void CacheWithCountLimitLRU(const std::string& key, const T& cacheObj, std::list<CacheNode<T>>& cacheList,
        std::unordered_map<std::string, typename std::list<CacheNode<T>>::iterator>& cache,
        const std::atomic<size_t>& capacity);

    template<typename T>
    static T GetCacheObjWithCountLimitLRU(const std::string& key, std::list<CacheNode<T>>& cacheList,
        std::unordered_map<std::string, typename std::list<CacheNode<T>>::iterator>& cache);

    template<typename T>
    static void RemoveCacheObjFromCountLimitLRU(const std::string& key, std::list<CacheNode<T>>& cacheList,
        std::unordered_map<std::string, typename std::list<CacheNode<T>>::iterator>& cache);
};
} // namespace OHOS::Ace

#include "count_limit_lru.inl"
#endif
