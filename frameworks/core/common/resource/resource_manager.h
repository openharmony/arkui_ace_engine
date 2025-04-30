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

struct ResourceErrorInfo {
    ResourceErrorInfo(int32_t nodeId, std::string sourceKey, std::string sourceTag, std::string nodeTag,
        int64_t errorTime, int32_t state)
        : nodeId(nodeId), sourceKey(std::move(sourceKey)), sourceTag(std::move(sourceTag)),
          nodeTag(std::move(nodeTag)), errorTime(errorTime), state(state) {}
    int32_t nodeId;
    std::string sourceKey;
    std::string sourceTag;
    std::string nodeTag;
    int64_t errorTime;
    int32_t state;
};

class ACE_FORCE_EXPORT ResourceManager final : public AceType {
    DECLARE_ACE_TYPE(ResourceManager, AceType);

public:
    ~ResourceManager() = default;

    static ResourceManager& GetInstance();

    RefPtr<ResourceAdapter> GetOrCreateResourceAdapter(RefPtr<ResourceObject>& resourceObject);

    std::string MakeCacheKey(const std::string& bundleName, const std::string& moduleName, int32_t instanceId)
    {
        if (bundleName.empty() && moduleName.empty()) {
            return std::to_string(instanceId);
        }
        return bundleName + "." + moduleName + "." + std::to_string(instanceId);
    }

    void AddResourceAdapter(const std::string& bundleName, const std::string& moduleName, int32_t instanceId,
        RefPtr<ResourceAdapter>& resourceAdapter, bool replace = false)
    {
        std::unique_lock<std::shared_mutex> lock(mutex_);
        if (bundleName.empty() && moduleName.empty()) {
            resourceAdapters_[std::to_string(instanceId)] = resourceAdapter;
        } else {
            auto key = MakeCacheKey(bundleName, moduleName, instanceId);
            if (replace) {
                CountLimitLRU::RemoveCacheObjFromCountLimitLRU<RefPtr<ResourceAdapter>>(key, cacheList_, cache_);
            }
            CountLimitLRU::CacheWithCountLimitLRU<RefPtr<ResourceAdapter>>(
                key, resourceAdapter, cacheList_, cache_, capacity_);
        }
    }

    void UpdateMainResourceAdapter(const std::string& bundleName, const std::string& moduleName, int32_t instanceId,
        RefPtr<ResourceAdapter>& resourceAdapter)
    {
        auto defaultKey = MakeCacheKey("", "", instanceId);
        auto key = MakeCacheKey(bundleName, moduleName, instanceId);
        resourceAdapters_[key] = resourceAdapter;
        resourceAdapters_[defaultKey] = resourceAdapter;
    }

    bool IsResourceAdapterRecord(const std::string& bundleName, const std::string& moduleName, int32_t instanceId)
    {
        std::shared_lock<std::shared_mutex> lock(mutex_);
        auto key = MakeCacheKey(bundleName, moduleName, instanceId);
        if (resourceAdapters_.find(key) != resourceAdapters_.end()) {
            return true;
        }
        return cache_.find(key) != cache_.end();
    }

    RefPtr<ResourceAdapter> GetResourceAdapter(
        const std::string& bundleName, const std::string& moduleName, int32_t instanceId)
    {
        std::unique_lock<std::shared_mutex> lock(mutex_);
        auto key = MakeCacheKey(bundleName, moduleName, instanceId);
        auto mapIter = resourceAdapters_.find(key);
        if (mapIter != resourceAdapters_.end()) {
            if (instanceId == -1) {
                TAG_LOGW(AceLogTag::ACE_RESOURCE, "Get resourceAdapter without UI!");
            }
            return mapIter->second;
        } else if (bundleName.empty() && moduleName.empty()) {
            TAG_LOGW(AceLogTag::ACE_RESOURCE,
                "Get default resourceAdapter %{public}d failed, don't get resource while UIContent not initialized yet",
                instanceId);
            return ResourceAdapter::Create();
        }

        auto resAdapter = CountLimitLRU::GetCacheObjWithCountLimitLRU<RefPtr<ResourceAdapter>>(key, cacheList_, cache_);
        if (resAdapter != nullptr) {
            return resAdapter;
        }

        return nullptr;
    }

    RefPtr<ResourceAdapter> GetResourceAdapter(int32_t instanceId)
    {
        std::shared_lock<std::shared_mutex> lock(mutex_);
        auto key = MakeCacheKey("", "", instanceId);
        if (resourceAdapters_.find(key) != resourceAdapters_.end()) {
            return resourceAdapters_.at(key);
        }
        return nullptr;
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

    void RemoveResourceAdapter(const std::string& bundleName, const std::string& moduleName, int32_t instanceId)
    {
        std::unique_lock<std::shared_mutex> lock(mutex_);
        std::string key = MakeCacheKey(bundleName, moduleName, instanceId);
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

    void RegisterMainResourceAdapter(const std::string& bundleName, const std::string& moduleName, int32_t instanceId,
        const RefPtr<ResourceAdapter>& resAdapter);

    void DumpResLoadError();

    void AddResourceLoadError(ResourceErrorInfo errorInfo)
    {
        std::unique_lock<std::shared_mutex> lock(errorMutex_);
        resourceErrorList_.emplace_front(errorInfo);
        if (resourceErrorList_.size() > MAX_DUMP_LIST_SIZE) {
            resourceErrorList_.pop_back();
        }
    }

    void SetResourceCacheSize(size_t cacheSize) {
        capacity_.store(cacheSize);
    }

private:
    ResourceManager() = default;

    static const size_t MAX_DUMP_LIST_SIZE = 100;
    std::unordered_map<std::string, RefPtr<ResourceAdapter>> resourceAdapters_;
    std::shared_mutex mutex_;

    std::atomic<size_t> capacity_ = 3;
    std::list<CacheNode<RefPtr<ResourceAdapter>>> cacheList_;
    std::unordered_map<std::string, std::list<CacheNode<RefPtr<ResourceAdapter>>>::iterator> cache_;
    std::shared_mutex errorMutex_;
    std::list<ResourceErrorInfo> resourceErrorList_;
};
} // namespace OHOS::Ace

#endif