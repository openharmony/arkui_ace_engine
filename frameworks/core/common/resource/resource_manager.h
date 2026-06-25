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

#include <cstdint>
#include <shared_mutex>
#include <string>

#include "base/memory/ace_type.h"
#include "core/common/lru/count_limit_lru.h"

namespace OHOS::Ace {

class ResourceAdapter;
class ResourceConfiguration;
class ResourceObject;

struct ResourceErrorInfo {
    ResourceErrorInfo(int32_t nodeId, std::string sourceKey, std::string sourceTag, std::string nodeTag,
        int64_t errorTime, int32_t state);
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
    ~ResourceManager();

    static ResourceManager& GetInstance();

    RefPtr<ResourceAdapter> GetOrCreateResourceAdapter(const RefPtr<ResourceObject>& resourceObject);

    std::string MakeCacheKey(const std::string& bundleName, const std::string& moduleName, int32_t instanceId);

    void AddResourceAdapter(const std::string& bundleName, const std::string& moduleName, int32_t instanceId,
        RefPtr<ResourceAdapter>& resourceAdapter, bool replace = false);

    void UpdateMainResourceAdapter(const std::string& bundleName, const std::string& moduleName, int32_t instanceId,
        RefPtr<ResourceAdapter>& resourceAdapter);

    bool IsResourceAdapterRecord(const std::string& bundleName, const std::string& moduleName, int32_t instanceId);

    std::string GetCacheKeyInstanceId(const std::string& key);

    RefPtr<ResourceAdapter> GetResourceAdapter(
        const std::string& bundleName, const std::string& moduleName, int32_t instanceId);

    RefPtr<ResourceAdapter> GetResourceAdapter(int32_t instanceId);

    void UpdateResourceConfig(const std::string& bundleName, const std::string& moduleName, int32_t instanceId,
        const ResourceConfiguration& config, bool themeFlag = false);

    void RemoveResourceAdapter(const std::string& bundleName, const std::string& moduleName, int32_t instanceId);

    void Reset();

    void UpdateColorMode(
        const std::string& bundleName, const std::string& moduleName, int32_t instanceId, ColorMode colorMode);

    void RegisterMainResourceAdapter(const std::string& bundleName, const std::string& moduleName, int32_t instanceId,
        const RefPtr<ResourceAdapter>& resAdapter);

    void DumpResLoadError();

    void AddResourceLoadError(ResourceErrorInfo errorInfo);

    void SetResourceCacheSize(size_t cacheSize);

private:
    ResourceManager();

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