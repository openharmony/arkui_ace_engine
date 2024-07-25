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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_RESOURCE_RESOURCE_MANAGER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_RESOURCE_RESOURCE_MANAGER_H

#include <climits>
#include <functional>
#include <map>
#include <mutex>
#include <shared_mutex>
#include <string>
#include <utility>

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "base/utils/resource_configuration.h"
#include "core/common/resource/resource_object.h"
#include "core/components/theme/resource_adapter.h"
#include "core/common/lru/count_limit_lru.h"

namespace OHOS::Ace {
constexpr char DEFAULT_RESOURCE_KEY[] = "";

class ACE_FORCE_EXPORT ResourceManager final : public AceType {
    DECLARE_ACE_TYPE(ResourceManager, AceType);

public:
    ~ResourceManager() = default;

    static ResourceManager& GetInstance();

    RefPtr<ResourceAdapter> GetOrCreateResourceAdapter(RefPtr<ResourceObject>& resourceObject);

    std::string MakeCacheKey(const std::string& bundleName, const std::string& moduleName)
    {
        if (bundleName.empty() && moduleName.empty()) {
            return DEFAULT_RESOURCE_KEY;
        }
        return bundleName + "." + moduleName;
    }

    void AddResourceAdapter(const std::string& bundleName, const std::string& moduleName,
        RefPtr<ResourceAdapter>& resourceAdapter, bool replace = false)
    {
        std::unique_lock<std::shared_mutex> lock(mutex_);
        if (bundleName.empty() && moduleName.empty()) {
            resourceAdapters_[DEFAULT_RESOURCE_KEY] = resourceAdapter;
        } else {
            auto key = MakeCacheKey(bundleName, moduleName);
            if (replace) {
                CountLimitLRU::RemoveCacheObjFromCountLimitLRU<RefPtr<ResourceAdapter>>(key, cacheList_, cache_);
            }
            CountLimitLRU::CacheWithCountLimitLRU<RefPtr<ResourceAdapter>>(
                key, resourceAdapter, cacheList_, cache_, capacity_);
        }
    }

    bool IsResourceAdapterRecord(const std::string& bundleName, const std::string& moduleName)
    {
        std::shared_lock<std::shared_mutex> lock(mutex_);
        auto key = MakeCacheKey(bundleName, moduleName);
        if (resourceAdapters_.find(key) != resourceAdapters_.end()) {
            return true;
        }
        return cache_.find(key) != cache_.end();
    }

    RefPtr<ResourceAdapter> GetResourceAdapter(const std::string& bundleName, const std::string& moduleName)
    {
        std::unique_lock<std::shared_mutex> lock(mutex_);
        auto key = MakeCacheKey(bundleName, moduleName);
        auto mapIter = resourceAdapters_.find(key);
        if (mapIter != resourceAdapters_.end()) {
            return mapIter->second;
        } else if (key == DEFAULT_RESOURCE_KEY) {
            TAG_LOGW(AceLogTag::ACE_RESOURCE,
                "Get default resourceAdapter failed, don't get resource while UIContent not initialized yet");
            return ResourceAdapter::Create();
        }

        auto resAdapter = CountLimitLRU::GetCacheObjWithCountLimitLRU<RefPtr<ResourceAdapter>>(key, cacheList_, cache_);
        if (resAdapter != nullptr) {
            return resAdapter;
        }

        return nullptr;
    }

    RefPtr<ResourceAdapter> GetResourceAdapter()
    {
        std::shared_lock<std::shared_mutex> lock(mutex_);
        auto key = MakeCacheKey("", "");
        return resourceAdapters_.at(key);
    }

    void UpdateResourceConfig(const ResourceConfiguration& config, bool themeFlag = false)
    {
        std::unique_lock<std::shared_mutex> lock(mutex_);
        for (auto iter = resourceAdapters_.begin(); iter != resourceAdapters_.end(); ++iter) {
            iter->second->UpdateConfig(config, themeFlag);
        }
        for (auto iter = cacheList_.begin(); iter != cacheList_.end(); ++iter) {
            iter->cacheObj->UpdateConfig(config, themeFlag);
        }
    }

    void RemoveResourceAdapter(const std::string& bundleName, const std::string& moduleName)
    {
        std::unique_lock<std::shared_mutex> lock(mutex_);
        std::string key = MakeCacheKey(bundleName, moduleName);
        if (resourceAdapters_.find(key) != resourceAdapters_.end()) {
            resourceAdapters_.erase(key);
        }
        if (!bundleName.empty() && !moduleName.empty()) {
            CountLimitLRU::RemoveCacheObjFromCountLimitLRU<RefPtr<ResourceAdapter>>(key, cacheList_, cache_);
        }
    }

    void Reset()
    {
        std::unique_lock<std::shared_mutex> lock(mutex_);
        cacheList_.clear();
        cache_.clear();
        TAG_LOGI(AceLogTag::ACE_RESOURCE, "The cache of Resource has been released!");
    }

    void UpdateColorMode(ColorMode colorMode)
    {
        std::unique_lock<std::shared_mutex> lock(mutex_);
        for (auto iter = resourceAdapters_.begin(); iter != resourceAdapters_.end(); ++iter) {
            iter->second->UpdateColorMode(colorMode);
        }
        for (auto iter = cacheList_.begin(); iter != cacheList_.end(); ++iter) {
            iter->cacheObj->UpdateColorMode(colorMode);
        }
    }

    void RegisterMainResourceAdapter(
        const std::string& bundleName, const std::string& moduleName, const RefPtr<ResourceAdapter>& resAdapter);

private:
    ResourceManager() = default;

    std::unordered_map<std::string, RefPtr<ResourceAdapter>> resourceAdapters_;
    std::shared_mutex mutex_;

    std::atomic<size_t> capacity_ = 3;
    std::list<CacheNode<RefPtr<ResourceAdapter>>> cacheList_;
    std::unordered_map<std::string, std::list<CacheNode<RefPtr<ResourceAdapter>>>::iterator> cache_;
};
} // namespace OHOS::Ace

#endif