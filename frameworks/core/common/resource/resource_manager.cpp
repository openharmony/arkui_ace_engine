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

RefPtr<ResourceAdapter> ResourceManager::GetOrCreateResourceAdapter(const RefPtr<ResourceObject>& resourceObject)
{
    int32_t instanceId = resourceObject->GetInstanceId();
    std::string bundleName = resourceObject->GetBundleName();
    std::string moduleName = resourceObject->GetModuleName();

    auto resourceAdapter = GetResourceAdapter(bundleName, moduleName, instanceId);
    if (resourceAdapter == nullptr) {
        resourceAdapter = ResourceAdapter::CreateNewResourceAdapter(bundleName, moduleName);
        if (!resourceAdapter) {
            return GetResourceAdapter(DEFAULT_BUNDLE_NAME, DEFAULT_MODULE_NAME, instanceId);
        }
        AddResourceAdapter(bundleName, moduleName, instanceId, resourceAdapter);
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
