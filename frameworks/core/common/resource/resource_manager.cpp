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

#include "core/common/resource/resource_manager.h"

#include <mutex>
#include <utility>
#include <vector>

#include "base/log/dump_log.h"
#include "base/log/log.h"
#include "base/utils/resource_configuration.h"
#include "base/utils/string_utils.h"
#include "base/utils/time_util.h"
#include "core/common/resource/resource_object.h"
#include "core/components/theme/resource_adapter.h"

namespace OHOS::Ace {
namespace {
const std::string DEFAULT_BUNDLE_NAME = "";
const std::string DEFAULT_MODULE_NAME = "";
} // namespace

ResourceErrorInfo::ResourceErrorInfo(
    int32_t nodeId, std::string sourceKey, std::string sourceTag, std::string nodeTag, int64_t errorTime, int32_t state)
    : nodeId(nodeId), sourceKey(std::move(sourceKey)), sourceTag(std::move(sourceTag)), nodeTag(std::move(nodeTag)),
      errorTime(errorTime), state(state)
{}

ResourceManager::ResourceManager() = default;

ResourceManager::~ResourceManager() = default;

ResourceManager& ResourceManager::GetInstance()
{
    static ResourceManager instance;
    return instance;
}

RefPtr<ResourceAdapter> ResourceManager::GetOrCreateResourceAdapter(const RefPtr<ResourceObject>& resourceObject)
{
    CHECK_NULL_RETURN(resourceObject, nullptr);
    int32_t instanceId = resourceObject->GetInstanceId();
    std::string bundleName = resourceObject->GetBundleName();
    std::string moduleName = resourceObject->GetModuleName();

    auto resourceAdapter = GetResourceAdapter(bundleName, moduleName, instanceId);
#ifdef CROSS_PLATFORM
    if (resourceAdapter == nullptr) {
        std::string fullModuleName = bundleName + "." + moduleName;
        resourceAdapter = GetResourceAdapter(bundleName, fullModuleName, instanceId);
    }
#endif
    if (resourceAdapter == nullptr) {
        int32_t actualInstanceId = instanceId;
        resourceAdapter = ResourceAdapter::CreateNewResourceAdapter(bundleName, moduleName, actualInstanceId);
        if (!resourceAdapter) {
            return GetResourceAdapter(DEFAULT_BUNDLE_NAME, DEFAULT_MODULE_NAME, instanceId);
        }
        AddResourceAdapter(bundleName, moduleName, actualInstanceId, resourceAdapter);
    }
    return resourceAdapter;
}

std::string ResourceManager::MakeCacheKey(
    const std::string& bundleName, const std::string& moduleName, int32_t instanceId)
{
    if (bundleName.empty() && moduleName.empty()) {
        return std::to_string(instanceId);
    }
    return bundleName + "." + moduleName + "." + std::to_string(instanceId);
}

void ResourceManager::AddResourceAdapter(const std::string& bundleName, const std::string& moduleName,
    int32_t instanceId, RefPtr<ResourceAdapter>& resourceAdapter, bool replace)
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

void ResourceManager::UpdateMainResourceAdapter(const std::string& bundleName, const std::string& moduleName,
    int32_t instanceId, RefPtr<ResourceAdapter>& resourceAdapter)
{
    std::unique_lock<std::shared_mutex> lock(mutex_);
    auto defaultKey = MakeCacheKey("", "", instanceId);
    auto key = MakeCacheKey(bundleName, moduleName, instanceId);
    resourceAdapters_[key] = resourceAdapter;
    resourceAdapters_[defaultKey] = resourceAdapter;
}

bool ResourceManager::IsResourceAdapterRecord(
    const std::string& bundleName, const std::string& moduleName, int32_t instanceId)
{
    std::shared_lock<std::shared_mutex> lock(mutex_);
    auto key = MakeCacheKey(bundleName, moduleName, instanceId);
    if (resourceAdapters_.find(key) != resourceAdapters_.end()) {
        return true;
    }
    return cache_.find(key) != cache_.end();
}

std::string ResourceManager::GetCacheKeyInstanceId(const std::string& key)
{
    std::vector<std::string> splitter;
    StringUtils::StringSplitter(key, '.', splitter);
    return splitter.back();
}

RefPtr<ResourceAdapter> ResourceManager::GetResourceAdapter(
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

RefPtr<ResourceAdapter> ResourceManager::GetResourceAdapter(int32_t instanceId)
{
    std::shared_lock<std::shared_mutex> lock(mutex_);
    auto key = MakeCacheKey("", "", instanceId);
    if (resourceAdapters_.find(key) != resourceAdapters_.end()) {
        return resourceAdapters_.at(key);
    }
    return nullptr;
}

void ResourceManager::RegisterMainResourceAdapter(const std::string& bundleName, const std::string& moduleName,
    int32_t instanceId, const RefPtr<ResourceAdapter>& resAdapter)
{
    std::unique_lock<std::shared_mutex> lock(mutex_);
    auto key = MakeCacheKey(bundleName, moduleName, instanceId);
    resourceAdapters_.emplace(key, resAdapter);
}

void ResourceManager::UpdateResourceConfig(const std::string& /*bundleName*/, const std::string& /*moduleName*/,
    int32_t instanceId, const ResourceConfiguration& config, bool themeFlag)
{
    std::unique_lock<std::shared_mutex> lock(mutex_);
    std::string compareId = std::to_string(instanceId);
    for (auto iter = resourceAdapters_.begin(); iter != resourceAdapters_.end(); ++iter) {
        if (GetCacheKeyInstanceId(iter->first) == compareId) {
            iter->second->UpdateConfig(config, themeFlag);
        }
    }
    for (auto iter = cacheList_.begin(); iter != cacheList_.end(); ++iter) {
        if (GetCacheKeyInstanceId(iter->cacheKey) == compareId) {
            iter->cacheObj->UpdateConfig(config, themeFlag);
        }
    }
}

void ResourceManager::UpdateColorMode(
    const std::string& /*bundleName*/, const std::string& /*moduleName*/, int32_t instanceId, ColorMode colorMode)
{
    std::unique_lock<std::shared_mutex> lock(mutex_);
    std::string compareId = std::to_string(instanceId);
    for (auto iter = resourceAdapters_.begin(); iter != resourceAdapters_.end(); ++iter) {
        if (GetCacheKeyInstanceId(iter->first) == compareId) {
            iter->second->UpdateColorMode(colorMode);
        }
    }
    for (auto iter = cacheList_.begin(); iter != cacheList_.end(); ++iter) {
        if (GetCacheKeyInstanceId(iter->cacheKey) == compareId) {
            iter->cacheObj->UpdateColorMode(colorMode);
        }
    }
}

void ResourceManager::RemoveResourceAdapter(
    const std::string& bundleName, const std::string& moduleName, int32_t instanceId)
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

void ResourceManager::Reset()
{
    std::unique_lock<std::shared_mutex> lock(mutex_);
    cacheList_.clear();
    cache_.clear();
    TAG_LOGI(AceLogTag::ACE_RESOURCE, "The cache of Resource has been released!");
}

void ResourceManager::DumpResLoadError()
{
    std::unique_lock<std::shared_mutex> lock(errorMutex_);
    auto resLoadErrorSize = resourceErrorList_.size();
    DumpLog::GetInstance().Print("----------ResourceLoadWrrorInfo----------");
    if (resLoadErrorSize == 0) {
        DumpLog::GetInstance().Print("No resource load error have occurred.");
        return;
    }

    DumpLog::GetInstance().Print("ResourceLoadErrorTimes: " + std::to_string(resLoadErrorSize));
    for (const auto& nodeError : resourceErrorList_) {
        DumpLog::GetInstance().Print(
            1, "Node: " + std::to_string(nodeError.nodeId) + ", nodeTag: " + nodeError.nodeTag +
                   ", sourceKey: " + nodeError.sourceKey + ", sourceTag: " + nodeError.sourceTag + ", errorCode: " +
                   std::to_string(nodeError.state) + ", errorTime: " + ConvertTimestampToStr(nodeError.errorTime));
    }
}

void ResourceManager::AddResourceLoadError(ResourceErrorInfo errorInfo)
{
    std::unique_lock<std::shared_mutex> lock(errorMutex_);
    resourceErrorList_.emplace_front(errorInfo);
    if (resourceErrorList_.size() > MAX_DUMP_LIST_SIZE) {
        resourceErrorList_.pop_back();
    }
}

void ResourceManager::SetResourceCacheSize(size_t cacheSize)
{
    capacity_.store(cacheSize);
    while (cache_.size() > capacity_) {
        cache_.erase(cacheList_.back().cacheKey);
        cacheList_.pop_back();
    }
}
} // namespace OHOS::Ace