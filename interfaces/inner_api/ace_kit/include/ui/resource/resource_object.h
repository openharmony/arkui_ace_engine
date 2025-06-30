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

#ifndef FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_INCLUDE_RESOURCE_RESOURCE_OBJECT_H
#define FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_INCLUDE_RESOURCE_RESOURCE_OBJECT_H

#include <cstdint>
#include <optional>
#include <string>
#include <vector>

#include "ui/base/ace_type.h"
#include "ui/properties/color.h"

namespace OHOS::Ace {
enum class ResourceObjectParamType { NONE, INT, STRING, FLOAT };

struct ResourceObjectParams {
    std::optional<std::string> value;
    ResourceObjectParamType type = ResourceObjectParamType::NONE;
};

class ResourceObject : public AceType {
    DECLARE_ACE_TYPE(ResourceObject, AceType);

public:
    ResourceObject() = default;
    ResourceObject(int32_t id, int32_t type, const std::vector<ResourceObjectParams>& params,
        const std::string& bundleName, const std::string& moduleName, int32_t instanceId)
        : id_(id), type_(type), instanceId_(instanceId), params_(params), bundleName_(bundleName),
          moduleName_(moduleName) {};
    ResourceObject(const std::string& bundleName, const std::string& moduleName, int32_t instanceId)
        : id_(-1), type_(-1), instanceId_(instanceId), params_(std::vector<ResourceObjectParams>()),
          bundleName_(bundleName), moduleName_(moduleName) {};
    ~ResourceObject() = default;

    int32_t GetId() const
    {
        return id_;
    }

    int32_t GetType() const
    {
        return type_;
    }

    int32_t GetInstanceId() const
    {
        return instanceId_;
    }

    void SetInstanceId(int32_t instanceId)
    {
        instanceId_ = instanceId;
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

    const Color& GetColor() const
    {
        return color_;
    }

    void SetColor(const Color color)
    {
        color_ = color;
    }

    void SetNodeTag(const std::string nodeTag)
    {
        nodeTag_ = nodeTag;
    }

    const std::string& GetNodeTag() const
    {
        return nodeTag_;
    }

    bool IsResource() const
    {
        return isResource_;
    }

    void SetIsResource(bool isResource)
    {
        isResource_ = isResource;
    }

    void SetColorMode(ColorMode colorMode)
    {
        colorMode_ = colorMode;
    }

    const ColorMode& GetColorMode() const
    {
        return colorMode_;
    }

    void SetHasDarkRes(bool hasDarkRes)
    {
        hasDarkRes_ = hasDarkRes;
    }

    bool HasDarkResource() const
    {
        return hasDarkRes_;
    }

private:
    int32_t id_;
    int32_t type_;
    int32_t instanceId_;
    Color color_;
    std::vector<ResourceObjectParams> params_;
    std::string bundleName_;
    std::string moduleName_;
    std::string nodeTag_;
    ColorMode colorMode_ = ColorMode::COLOR_MODE_UNDEFINED;
    bool isResource_ = true;
    bool hasDarkRes_ = false;
};
} // namespace OHOS::Ace

#endif