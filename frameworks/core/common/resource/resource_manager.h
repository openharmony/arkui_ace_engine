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

namespace OHOS::Ace {

class ResourceManager : public AceType {
    DECLARE_ACE_TYPE(ResourceManager, AceType);

public:
    ~ResourceManager() = default;

    static ResourceManager& GetInstance();

    RefPtr<ResourceAdapter> GetOrCreateResourceAdapter(RefPtr<ResourceObject>& resourceObject);

    void AddResourceAdapter(
        const std::string& bundleName, const std::string& moduleName, RefPtr<ResourceAdapter>& resourceAdapter)
    {
        std::unique_lock<std::shared_mutex> lock(mutex_);
        resourceAdapters_.emplace(std::make_pair(bundleName, moduleName), resourceAdapter);
    }

    bool IsResourceAdapterRecord(const std::string& bundleName, const std::string& moduleName)
    {
        std::shared_lock<std::shared_mutex> lock(mutex_);
        auto adaptId = std::make_pair(bundleName, moduleName);
        auto iter = resourceAdapters_.find(adaptId);
        return iter != resourceAdapters_.end();
    }

    RefPtr<ResourceAdapter> GetResourceAdapter(const std::string& bundleName, const std::string& moduleName)
    {
        std::shared_lock<std::shared_mutex> lock(mutex_);
        auto adaptId = std::make_pair(bundleName, moduleName);
        return resourceAdapters_.at(adaptId);
    }

    RefPtr<ResourceAdapter> GetResourceAdapter()
    {
        std::shared_lock<std::shared_mutex> lock(mutex_);
        auto adaptId = std::make_pair("", "");
        return resourceAdapters_.at(adaptId);
    }

    void UpdateResourceConfig(const ResourceConfiguration& config)
    {
        std::unique_lock<std::shared_mutex> lock(mutex_);
        for (auto iter = resourceAdapters_.begin(); iter != resourceAdapters_.end(); ++iter) {
            iter->second->UpdateConfig(config);
        }
    }

    void Reset()
    {
        resourceAdapters_.clear();
    }

private:
    ResourceManager() = default;

    std::map<std::pair<std::string, std::string>, RefPtr<ResourceAdapter>> resourceAdapters_;
    std::shared_mutex mutex_;
};
} // namespace OHOS::Ace

#endif