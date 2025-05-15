/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_RESOURCE_PATTERN_REOURCE_MANAGER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_RESOURCE_PATTERN_REOURCE_MANAGER_H

#include <functional>
#include <map>
#include <string>
#include <unordered_map>

#include "base/memory/ace_type.h"

#include "core/common/resource/resource_object.h"

namespace OHOS::Ace {
class PatternResourceManager final : public AceType {
    DECLARE_ACE_TYPE(PatternResourceManager, AceType);

public:
    PatternResourceManager() = default;
    ~PatternResourceManager() override = default;

    void AddResource(
        const std::string& key,
        const RefPtr<ResourceObject>& resObj,
        std::function<void(const RefPtr<ResourceObject>&)>&& updateFunc);

    void AddResCache(const std::string& key, const std::string& value);

    std::string GetResCacheMapByKey(const std::string& key);

    void RemoveResource(const std::string& key);

    void ReloadResources();

    bool Empty();

private:
    struct ResourceUpdater {
        RefPtr<ResourceObject> obj;
        std::function<void(const RefPtr<ResourceObject>&)> updateFunc;
    };
    std::unordered_map<std::string, ResourceUpdater> resMap_;
    std::unordered_map<std::string, std::map<bool, std::string>> resCacheMap_;
};
}
#endif
