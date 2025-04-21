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

#ifndef FOUNDATION_ACE_INTERFACE_INNERAPI_BASE_RESOURCE_H
#define FOUNDATION_ACE_INTERFACE_INNERAPI_BASE_RESOURCE_H

#include <cstdint>
#include <optional>
#include <string>
#include <vector>

namespace OHOS {
namespace Ace {
namespace Drawable {
enum class ResourceObjectParamType { NONE, INT, STRING, FLOAT };

struct ResourceObjectParams {
    std::optional<std::string> value;
    ResourceObjectParamType type = ResourceObjectParamType::NONE;
};

class Resource {
public:
    Resource() = default;
    Resource(int32_t id, int32_t type, const std::vector<ResourceObjectParams>& params,
        const std::string& bundleName, const std::string& moduleName)
        : id_(id), type_(type), params_(params), bundleName_(bundleName), moduleName_(moduleName) {};
    ~Resource() = default;

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

    std::string ToString() const
    {
        std::string result;
        result.append("id:");
        result.append(std::to_string(id_));
        result.append("type:");
        result.append(std::to_string(type_));
        result.append("bundleName:");
        result.append(bundleName_);
        result.append("moduleName:");
        result.append(moduleName_);
        return result;
    }

private:
    int32_t id_;
    int32_t type_;
    std::vector<ResourceObjectParams> params_;
    std::string bundleName_;
    std::string moduleName_;
};
} // namespace Drawable
} // namespace Ace
} // namespace OHOS

#endif // FOUNDATION_ACE_INTERFACE_INNERAPI_BASE_RESOURCE_H
