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

#include "core/common/resource/pattern_resource_manager.h"

namespace OHOS::Ace {
void PatternResourceManager::AddResource(const std::string& key,
    const RefPtr<ResourceObject>& resObj,
    std::function<void(const RefPtr<ResourceObject>&)>&& updateFunc)
{
    (void)key;
    (void)resObj;
    (void)updateFunc;
}

void PatternResourceManager::AddResCache(const std::string& key, const std::string& value)
{
    (void)key;
    (void)value;
}

std::string PatternResourceManager::GetResCacheMapByKey(const std::string& key)
{
    (void)key;
    return "";
}

void PatternResourceManager::RemoveResource(const std::string& key)
{
    (void)key;
}

void PatternResourceManager::ReloadResources() {}

bool PatternResourceManager::Empty()
{
    return true;
}

void PatternResourceManager::ParsePropertyValue(
    const RefPtr<ResourceObject>& resObj, RefPtr<PropertyValueBase> value, bool adaptMaterial)
{
    (void)resObj;
    (void)value;
    (void)adaptMaterial;
}

const std::vector<std::string>& PatternResourceManager::GetResKeyArray()
{
    static std::vector<std::string> empty;
    return empty;
}
} // namespace OHOS::Ace
