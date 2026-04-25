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

#include "base/log/dump_log.h"
#include "base/utils/time_util.h"

namespace OHOS::Ace {
namespace {
const std::string DEFAULT_BUNDLE_NAME = "";
const std::string DEFAULT_MODULE_NAME = "";
} // namespace

ResourceManager& ResourceManager::GetInstance()
{
    static ResourceManager instance;
    return instance;
}

RefPtr<ResourceAdapter> ResourceManager::GetOverrideResourceAdapterLocked(const std::string& key, int32_t instanceId)
{
    auto stackIter = overrideResourceAdapters_.find(instanceId);
    if (stackIter == overrideResourceAdapters_.end() || stackIter->second.empty()) {
        return nullptr;
    }
    const auto& adapters = stackIter->second.back().adapters;
    auto adapterIter = adapters.find(key);
    if (adapterIter == adapters.end()) {
        return nullptr;
    }
    return adapterIter->second;
}

ResourceManager::ResourceAdapterMap ResourceManager::GetBaseResourceAdaptersForInstanceLocked(int32_t instanceId)
{
    ResourceAdapterMap adapters;
    const auto compareId = std::to_string(instanceId);
    for (const auto& [key, adapter] : resourceAdapters_) {
        if (GetCacheKeyInstanceId(key) == compareId) {
            adapters[key] = adapter;
        }
    }
    for (const auto& cacheNode : cacheList_) {
        if (GetCacheKeyInstanceId(cacheNode.cacheKey) == compareId) {
            adapters[cacheNode.cacheKey] = cacheNode.cacheObj;
        }
    }
    return adapters;
}

void ResourceManager::AddResourceAdapterLocked(const std::string& bundleName, const std::string& moduleName,
    int32_t instanceId, RefPtr<ResourceAdapter>& resourceAdapter, bool replace)
{
    if (bundleName.empty() && moduleName.empty()) {
        resourceAdapters_[std::to_string(instanceId)] = resourceAdapter;
        return;
    }
    auto key = MakeCacheKey(bundleName, moduleName, instanceId);
    if (replace) {
        CountLimitLRU::RemoveCacheObjFromCountLimitLRU<RefPtr<ResourceAdapter>>(key, cacheList_, cache_);
    }
    CountLimitLRU::CacheWithCountLimitLRU<RefPtr<ResourceAdapter>>(key, resourceAdapter, cacheList_, cache_, capacity_);
}

RefPtr<ResourceAdapter> ResourceManager::AddOverrideResourceAdapterForNewBaseLocked(
    const std::string& key, int32_t instanceId, const RefPtr<ResourceAdapter>& resourceAdapter)
{
    auto stackIter = overrideResourceAdapters_.find(instanceId);
    if (stackIter == overrideResourceAdapters_.end() || stackIter->second.empty() || !resourceAdapter) {
        return nullptr;
    }
    RefPtr<ResourceAdapter> effectiveAdapter;
    ConfigurationChange configChange { .colorModeUpdate = true };
    for (auto& overrideRecord : stackIter->second) {
        ResourceConfiguration config;
        config.SetColorMode(overrideRecord.colorMode);
        auto overrideAdapter = resourceAdapter->GetOverrideResourceAdapter(config, configChange);
        effectiveAdapter = overrideAdapter ? overrideAdapter : resourceAdapter;
        overrideRecord.adapters[key] = effectiveAdapter;
    }
    return effectiveAdapter;
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
        std::unique_lock<std::shared_mutex> lock(mutex_);
        AddResourceAdapterLocked(bundleName, moduleName, actualInstanceId, resourceAdapter);
        auto key = MakeCacheKey(bundleName, moduleName, actualInstanceId);
        auto overrideAdapter = AddOverrideResourceAdapterForNewBaseLocked(key, actualInstanceId, resourceAdapter);
        if (overrideAdapter) {
            return overrideAdapter;
        }
    }
    return resourceAdapter;
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

void ResourceManager::PushOverrideColorMode(
    const std::string& /*bundleName*/, const std::string& /*moduleName*/, int32_t instanceId, ColorMode colorMode)
{
    std::unique_lock<std::shared_mutex> lock(mutex_);
    OverrideResourceRecord overrideRecord;
    overrideRecord.colorMode = colorMode;
    auto effectiveAdapters = GetBaseResourceAdaptersForInstanceLocked(instanceId);
    ResourceConfiguration config;
    config.SetColorMode(colorMode);
    ConfigurationChange configChange { .colorModeUpdate = true };
    for (const auto& [key, adapter] : effectiveAdapters) {
        if (!adapter) {
            continue;
        }
        auto overrideAdapter = adapter->GetOverrideResourceAdapter(config, configChange);
        overrideRecord.adapters[key] = overrideAdapter ? overrideAdapter : adapter;
    }
    overrideResourceAdapters_[instanceId].emplace_back(std::move(overrideRecord));
}

void ResourceManager::PopOverrideColorMode(int32_t instanceId)
{
    std::unique_lock<std::shared_mutex> lock(mutex_);
    auto stackIter = overrideResourceAdapters_.find(instanceId);
    if (stackIter == overrideResourceAdapters_.end() || stackIter->second.empty()) {
        return;
    }
    stackIter->second.pop_back();
    if (stackIter->second.empty()) {
        overrideResourceAdapters_.erase(stackIter);
    }
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
        DumpLog::GetInstance().Print(1, "Node: " + std::to_string(nodeError.nodeId) +
            ", nodeTag: " + nodeError.nodeTag + ", sourceKey: " + nodeError.sourceKey +
            ", sourceTag: " + nodeError.sourceTag +
            ", errorCode: " + std::to_string(nodeError.state) + ", errorTime: " +
            ConvertTimestampToStr(nodeError.errorTime));
    }
}
} // namespace OHOS::Ace
