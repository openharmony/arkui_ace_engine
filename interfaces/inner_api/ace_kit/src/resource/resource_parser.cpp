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

#include "base/utils/string_utils.h"
#include "base/utils/system_properties.h"
#include "core/common/container.h"
#include "core/common/resource/resource_manager.h"
#include "core/common/resource/resource_object.h"
#include "core/components/theme/resource_adapter.h"

namespace OHOS::Ace::Kit {
static RefPtr<Ace::ResourceAdapter> CreateResourceAdapter(const ResourceInfo& info)
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

bool ResourceParser::GetDimension(const ResourceInfo& resourceInfo, Ace::CalcDimension& dimension)
{
    auto resourceAdapter = CreateResourceAdapter(resourceInfo);
    if (!resourceAdapter) {
        return false;
    }

    auto resType = resourceInfo.type;
    if (resourceInfo.resId == UNKNOWN_RESOURCE_ID) {
        if (resourceInfo.params.empty()) {
            return false;
        }

        auto param = resourceInfo.params[0];
        if (resType == static_cast<int32_t>(ResourceType::STRING)) {
            auto value = resourceAdapter->GetStringByName(param);
            return StringUtils::StringToCalcDimensionNG(value, dimension, false, DimensionUnit::VP);
        }
        if (resType == static_cast<int32_t>(ResourceType::INTEGER)) {
            auto value = std::to_string(resourceAdapter->GetIntByName(param));
            return StringUtils::StringToDimensionWithUnitNG(value, dimension, DimensionUnit::VP);
        }
        dimension = resourceAdapter->GetDimensionByName(param);
        return true;
    } else {
        if (resType == static_cast<int32_t>(ResourceType::STRING)) {
            auto value = resourceAdapter->GetString(static_cast<uint32_t>(resourceInfo.resId));
            return StringUtils::StringToCalcDimensionNG(value, dimension, false, DimensionUnit::VP);
        }
        if (resType == static_cast<int32_t>(ResourceType::INTEGER)) {
            auto value = std::to_string(resourceAdapter->GetInt(static_cast<uint32_t>(resourceInfo.resId)));
            return StringUtils::StringToDimensionWithUnitNG(value, dimension, DimensionUnit::VP);
        }
        if (resType == static_cast<int32_t>(ResourceType::FLOAT)) {
            dimension = resourceAdapter->GetDimension(static_cast<uint32_t>(resourceInfo.resId));
            return true;
        }
    }
    return false;
}

bool ResourceParser::GetColor(const ResourceInfo& resourceInfo, Ace::Color& color)
{
    auto resourceAdapter = CreateResourceAdapter(resourceInfo);
    if (!resourceAdapter) {
        return false;
    }

    if (resourceInfo.resId == UNKNOWN_RESOURCE_ID) {
        color = resourceAdapter->GetColorByName(resourceInfo.params[0]);
    } else {
        color = resourceAdapter->GetColor(resourceInfo.resId);
    }
    return true;
}

bool ResourceParser::GetString(const ResourceInfo& resourceInfo, std::string& str)
{
    auto resourceAdapter = CreateResourceAdapter(resourceInfo);
    if (!resourceAdapter) {
        return false;
    }

    if (resourceInfo.resId == UNKNOWN_RESOURCE_ID) {
        str = resourceAdapter->GetStringByName(resourceInfo.params[0]);
    } else {
        str = resourceAdapter->GetString(resourceInfo.resId);
    }
    return true;
}

bool ResourceParser::GetMediaPath(const ResourceInfo& resourceInfo, std::string& mediaPath)
{
    auto resourceAdapter = CreateResourceAdapter(resourceInfo);
    if (!resourceAdapter) {
        return false;
    }

    if (resourceInfo.resId == UNKNOWN_RESOURCE_ID) {
        mediaPath = resourceAdapter->GetMediaPathByName(resourceInfo.params[0]);
    } else {
        mediaPath = resourceAdapter->GetMediaPath(resourceInfo.resId);
    }
    return true;
}

bool ResourceParser::GetInt(const ResourceInfo& resourceInfo, int32_t& intRes)
{
    auto resourceAdapter = CreateResourceAdapter(resourceInfo);
    if (!resourceAdapter) {
        return false;
    }

    if (resourceInfo.resId == UNKNOWN_RESOURCE_ID) {
        intRes = resourceAdapter->GetIntByName(resourceInfo.params[0]);
    } else {
        intRes = resourceAdapter->GetInt(resourceInfo.resId);
    }
    return true;
}

bool ResourceParser::GetDouble(const ResourceInfo& resourceInfo, double& doubleRes)
{
    auto resourceAdapter = CreateResourceAdapter(resourceInfo);
    if (!resourceAdapter) {
        return false;
    }

    if (resourceInfo.resId == UNKNOWN_RESOURCE_ID) {
        doubleRes = resourceAdapter->GetDoubleByName(resourceInfo.params[0]);
    } else {
        doubleRes = resourceAdapter->GetDouble(resourceInfo.resId);
    }
    return true;
}

bool ResourceParser::GetPluralString(const ResourceInfo& resourceInfo, int count, std::string& str)
{
    auto resourceAdapter = CreateResourceAdapter(resourceInfo);
    if (!resourceAdapter) {
        return false;
    }

    if (resourceInfo.resId == UNKNOWN_RESOURCE_ID) {
        str = resourceAdapter->GetPluralStringByName(resourceInfo.params[0], count);
    } else {
        str = resourceAdapter->GetPluralString(resourceInfo.resId, count);
    }
    return true;
}

bool ResourceParser::GetBoolean(const ResourceInfo& resourceInfo, bool& boolRes)
{
    auto resourceAdapter = CreateResourceAdapter(resourceInfo);
    if (!resourceAdapter) {
        return false;
    }

    if (resourceInfo.resId == UNKNOWN_RESOURCE_ID) {
        boolRes = resourceAdapter->GetBooleanByName(resourceInfo.params[0]);
    } else {
        boolRes = resourceAdapter->GetBoolean(resourceInfo.resId);
    }
    return true;
}

bool ResourceParser::GetIntArray(const ResourceInfo& resourceInfo, std::vector<uint32_t>& intArray)
{
    auto resourceAdapter = CreateResourceAdapter(resourceInfo);
    if (!resourceAdapter) {
        return false;
    }

    if (resourceInfo.resId == UNKNOWN_RESOURCE_ID) {
        intArray = resourceAdapter->GetIntArrayByName(resourceInfo.params[0]);
    } else {
        intArray = resourceAdapter->GetIntArray(resourceInfo.resId);
    }
    return true;
}

bool ResourceParser::GetStringArray(const ResourceInfo& resourceInfo, std::vector<std::string>& strArray)
{
    auto resourceAdapter = CreateResourceAdapter(resourceInfo);
    if (!resourceAdapter) {
        return false;
    }

    if (resourceInfo.resId == UNKNOWN_RESOURCE_ID) {
        strArray = resourceAdapter->GetStringArrayByName(resourceInfo.params[0]);
    } else {
        strArray = resourceAdapter->GetStringArray(resourceInfo.resId);
    }
    return true;
}

bool ResourceParser::GetSymbol(const ResourceInfo& resourceInfo, uint32_t& symbolRes)
{
    auto resourceAdapter = CreateResourceAdapter(resourceInfo);
    if (!resourceAdapter) {
        return false;
    }

    if (resourceInfo.resId == UNKNOWN_RESOURCE_ID) {
        symbolRes = resourceAdapter->GetSymbolByName(resourceInfo.params[0].c_str());
    } else {
        symbolRes = resourceAdapter->GetSymbolById(resourceInfo.resId);
    }
    return true;
}

bool ResourceParser::GetMediaData(const ResourceInfo& resourceInfo, size_t& len, std::unique_ptr<uint8_t[]>& dest)
{
    auto resourceAdapter = CreateResourceAdapter(resourceInfo);
    if (!resourceAdapter) {
        return false;
    }

    // resourceId is invalid
    if (resourceInfo.resId == UNKNOWN_RESOURCE_ID) {
        return resourceAdapter->GetMediaData(resourceInfo.params[0].c_str(), len, dest);
    }
    return resourceAdapter->GetMediaData(resourceInfo.resId, len, dest);
}

} // namespace OHOS::Ace::Kit
