/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

namespace OHOS::Ace {
ResourceManager& ResourceManager::GetInstance()
{
    static ResourceManager instance;
    return instance;
}

RefPtr<ResourceAdapter> ResourceManager::GetOrCreateResourceAdapter(const RefPtr<ResourceObject>& resourceObject)
{
    (void)resourceObject;
    return nullptr;
}

void ResourceManager::UpdateResourceConfig(const std::string& bundleName, const std::string& moduleName,
    int32_t instanceId, const ResourceConfiguration& config, bool themeFlag)
{
    (void)bundleName;
    (void)moduleName;
    (void)instanceId;
    (void)config;
    (void)themeFlag;
}

void ResourceManager::UpdateColorMode(
    const std::string& bundleName, const std::string& moduleName, int32_t instanceId, ColorMode colorMode)
{
    (void)bundleName;
    (void)moduleName;
    (void)instanceId;
    (void)colorMode;
}

void ResourceManager::RegisterMainResourceAdapter(const std::string& bundleName, const std::string& moduleName,
    int32_t instanceId, const RefPtr<ResourceAdapter>& resAdapter)
{
    (void)bundleName;
    (void)moduleName;
    (void)instanceId;
    (void)resAdapter;
}

void ResourceManager::DumpResLoadError() {}
} // namespace OHOS::Ace
