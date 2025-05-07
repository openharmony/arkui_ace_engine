/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include "ui/base/ace_type.h"
#include "ui/resource/resource_parser.h"

#include "base/utils/system_properties.h"
#include "core/common/container.h"
#include "core/common/resource/resource_manager.h"
#include "core/common/resource/resource_wrapper.h"

namespace OHOS::Ace::Kit {
static RefPtr<Ace::ResourceAdapter> CreateResourceWrapper(const ResourceInfo& info)
{
    auto bundleName = info.bundleName;
    auto moduleName = info.moduleName;

    RefPtr<Ace::ResourceAdapter> resourceAdapter = nullptr;
    if (bundleName.has_value() && moduleName.has_value()) {
        auto resourceObject = AceType::MakeRefPtr<Ace::ResourceObject>(
            bundleName.value_or(""), moduleName.value_or(""), Container::CurrentIdSafely());
        resourceAdapter = Ace::ResourceManager::GetInstance().GetOrCreateResourceAdapter(resourceObject);
    } else {
        resourceAdapter = Ace::ResourceManager::GetInstance().GetResourceAdapter(Container::CurrentIdSafely());
    }
    return resourceAdapter;
}

bool ResourceParser::GetDimension(const ResourceInfo& resourceInfo, Ace::Dimension& dimension)
{
    auto resourceWrapper = CreateResourceWrapper(resourceInfo);
    if (!resourceWrapper) {
        return false;
    }

    if (resourceInfo.resId == UNKNOWN_RESOURCE_ID) {
        dimension = resourceWrapper->GetDimensionByName(resourceInfo.params[0]);
    } else {
        dimension = resourceWrapper->GetDimension(resourceInfo.resId);
    }
    return true;
}

bool ResourceParser::GetColor(const ResourceInfo& resourceInfo, Ace::Color& color)
{
    auto resourceWrapper = CreateResourceWrapper(resourceInfo);
    if (!resourceWrapper) {
        return false;
    }

    if (resourceInfo.resId == UNKNOWN_RESOURCE_ID) {
        color = resourceWrapper->GetColorByName(resourceInfo.params[0]);
    } else {
        color = resourceWrapper->GetColor(resourceInfo.resId);
    }
    return true;
}

bool ResourceParser::GetString(const ResourceInfo& resourceInfo, std::string& str)
{
    auto resourceWrapper = CreateResourceWrapper(resourceInfo);
    if (!resourceWrapper) {
        return false;
    }

    if (resourceInfo.resId == UNKNOWN_RESOURCE_ID) {
        str = resourceWrapper->GetStringByName(resourceInfo.params[0]);
    } else {
        str = resourceWrapper->GetString(resourceInfo.resId);
    }
    return true;
}

bool ResourceParser::GetMediaPath(const ResourceInfo& resourceInfo, std::string& mediaPath)
{
    auto resourceWrapper = CreateResourceWrapper(resourceInfo);
    if (!resourceWrapper) {
        return false;
    }

    if (resourceInfo.resId == UNKNOWN_RESOURCE_ID) {
        mediaPath = resourceWrapper->GetMediaPathByName(resourceInfo.params[0]);
    } else {
        mediaPath = resourceWrapper->GetMediaPath(resourceInfo.resId);
    }
    return true;
}

bool ResourceParser::GetInt(const ResourceInfo& resourceInfo, int32_t& intRes)
{
    auto resourceWrapper = CreateResourceWrapper(resourceInfo);
    if (!resourceWrapper) {
        return false;
    }

    if (resourceInfo.resId == UNKNOWN_RESOURCE_ID) {
        intRes = resourceWrapper->GetIntByName(resourceInfo.params[0]);
    } else {
        intRes = resourceWrapper->GetInt(resourceInfo.resId);
    }
    return true;
}

bool ResourceParser::GetDouble(const ResourceInfo& resourceInfo, double& doubleRes)
{
    auto resourceWrapper = CreateResourceWrapper(resourceInfo);
    if (!resourceWrapper) {
        return false;
    }

    if (resourceInfo.resId == UNKNOWN_RESOURCE_ID) {
        doubleRes = resourceWrapper->GetDoubleByName(resourceInfo.params[0]);
    } else {
        doubleRes = resourceWrapper->GetDouble(resourceInfo.resId);
    }
    return true;
}

bool ResourceParser::GetPluralString(const ResourceInfo& resourceInfo, int count, std::string& str)
{
    auto resourceWrapper = CreateResourceWrapper(resourceInfo);
    if (!resourceWrapper) {
        return false;
    }

    if (resourceInfo.resId == UNKNOWN_RESOURCE_ID) {
        str = resourceWrapper->GetPluralStringByName(resourceInfo.params[0], count);
    } else {
        str = resourceWrapper->GetPluralString(resourceInfo.resId, count);
    }
    return true;
}

bool ResourceParser::GetBoolean(const ResourceInfo& resourceInfo, bool& boolRes)
{
    auto resourceWrapper = CreateResourceWrapper(resourceInfo);
    if (!resourceWrapper) {
        return false;
    }

    if (resourceInfo.resId == UNKNOWN_RESOURCE_ID) {
        boolRes = resourceWrapper->GetBooleanByName(resourceInfo.params[0]);
    } else {
        boolRes = resourceWrapper->GetBoolean(resourceInfo.resId);
    }
    return true;
}

bool ResourceParser::GetIntArray(const ResourceInfo& resourceInfo, std::vector<uint32_t>& intArray)
{
    auto resourceWrapper = CreateResourceWrapper(resourceInfo);
    if (!resourceWrapper) {
        return false;
    }

    if (resourceInfo.resId == UNKNOWN_RESOURCE_ID) {
        intArray = resourceWrapper->GetIntArrayByName(resourceInfo.params[0]);
    } else {
        intArray = resourceWrapper->GetIntArray(resourceInfo.resId);
    }
    return true;
}

bool ResourceParser::GetStringArray(const ResourceInfo& resourceInfo, std::vector<std::string>& strArray)
{
    auto resourceWrapper = CreateResourceWrapper(resourceInfo);
    if (!resourceWrapper) {
        return false;
    }

    if (resourceInfo.resId == UNKNOWN_RESOURCE_ID) {
        strArray = resourceWrapper->GetStringArrayByName(resourceInfo.params[0]);
    } else {
        strArray = resourceWrapper->GetStringArray(resourceInfo.resId);
    }
    return true;
}

bool ResourceParser::GetSymbol(const ResourceInfo& resourceInfo, uint32_t& symbolRes)
{
    auto resourceWrapper = CreateResourceWrapper(resourceInfo);
    if (!resourceWrapper) {
        return false;
    }

    if (resourceInfo.resId == UNKNOWN_RESOURCE_ID) {
        symbolRes = resourceWrapper->GetSymbolByName(resourceInfo.params[0].c_str());
    } else {
        symbolRes = resourceWrapper->GetSymbolById(resourceInfo.resId);
    }
    return true;
}

bool ResourceParser::GetMediaData(const ResourceInfo& resourceInfo, size_t& len, std::unique_ptr<uint8_t[]>& dest)
{
    auto resourceWrapper = CreateResourceWrapper(resourceInfo);
    if (!resourceWrapper) {
        return false;
    }

    // resourceId is invalid
    if (resourceInfo.resId == UNKNOWN_RESOURCE_ID) {
        return resourceWrapper->GetMediaData(resourceInfo.params[0].c_str(), len, dest);
    }
    return resourceWrapper->GetMediaData(resourceInfo.resId, len, dest);
}

} // namespace OHOS::Ace::Kit
