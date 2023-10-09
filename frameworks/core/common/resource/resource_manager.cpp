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

#include <memory>
#include <string>

#include "base/log/log_wrapper.h"
#include "base/memory/referenced.h"
#include "core/components/theme/resource_adapter.h"

namespace OHOS::Ace {
namespace {
const std::string DEFAULT_BUNDLE_NAME = "";
const std::string DEFAULT_MODULE_NAME = "";
}

ResourceManager& ResourceManager::GetInstance()
{
    static ResourceManager instance;
    return instance;
}

RefPtr<ResourceAdapter> ResourceManager::GetOrCreateResourceAdapter(RefPtr<ResourceObject>& resourceObject)
{
    std::string bundleName = resourceObject->GetBundleName();
    std::string moduleName = resourceObject->GetModuleName();

    auto isResourceAdapterRecord = IsResourceAdapterRecord(bundleName, moduleName);
    if (!isResourceAdapterRecord) {
        LOGI("create new resource adapter, bundleName: %{public}s, moduleName: %{public}s", bundleName.c_str(), moduleName.c_str());
        auto resourceAdapter = ResourceAdapter::CreateNewResourceAdapter(bundleName, moduleName);
        if (resourceAdapter == nullptr) {
            LOGW("resourceAdapter is null of bundleName: %{public}s, moduleName: %{public}s!, use default", bundleName.c_str(), moduleName.c_str());
            return GetResourceAdapter(DEFAULT_BUNDLE_NAME, DEFAULT_MODULE_NAME);
        }
        AddResourceAdapter(bundleName, moduleName, resourceAdapter);
    }
    return GetResourceAdapter(bundleName, moduleName);
}

} // namespace OHOS::Ace