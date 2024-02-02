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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_RESOURCE_RESOURCE_OBJECT_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_RESOURCE_RESOURCE_OBJECT_H

#include <cstdint>
#include <optional>
#include <string>
#include <vector>

#include "base/memory/ace_type.h"

namespace OHOS::Ace {
enum class ResourceObjectParamType { NONE, INT, STRING, FLOAT };

struct ResourceObjectParams {
    std::optional<std::string> value;
    ResourceObjectParamType type = ResourceObjectParamType::NONE;
};

class ResourceObject : public AceType {
    DECLARE_ACE_TYPE(ResourceObject, AceType);

public:
    ResourceObject(int32_t id, int32_t type, const std::vector<ResourceObjectParams>& params,
        const std::string& bundleName, const std::string& moduleName)
        : id_(id), type_(type), params_(params), bundleName_(bundleName), moduleName_(moduleName) {};
    ResourceObject(const std::string& bundleName, const std::string& moduleName)
        : id_(-1), type_(-1), params_(std::vector<ResourceObjectParams>()), bundleName_(bundleName),
          moduleName_(moduleName) {};
    ~ResourceObject() = default;

    int32_t GetId() const
    {
        return id_;
    }

    int32_t GetType() const
    {
        return type_;
    }

    std::vector<ResourceObjectParams> GetParams() const
    {
        return params_;
    }

    std::string GetBundleName() const
    {
        return bundleName_;
    }

    std::string GetModuleName() const
    {
        return moduleName_;
    }

private:
    int32_t id_;
    int32_t type_;
    std::vector<ResourceObjectParams> params_;
    std::string bundleName_;
    std::string moduleName_;
};
} // namespace OHOS::Ace

#endif