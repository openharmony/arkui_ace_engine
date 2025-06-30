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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_RESOURCE_REOURCE_PARSE_UTILS_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_RESOURCE_REOURCE_PARSE_UTILS_H

#include <functional>
#include <map>
#include <string>

#include "base/memory/ace_type.h"
#include "core/common/resource/resource_manager.h"
#include "core/common/resource/resource_wrapper.h"
#include "core/common/resource/resource_object.h"

namespace OHOS::Ace {

enum class ResourceType : uint32_t {
    COLOR = 10001,
    FLOAT,
    STRING,
    PLURAL,
    BOOLEAN,
    INTARRAY,
    INTEGER,
    PATTERN,
    STRARRAY,
    MEDIA = 20000,
    RAWFILE = 30000,
    SYMBOL = 40000
};

class ResourceParseUtils final : public AceType {
    DECLARE_ACE_TYPE(ResourceParseUtils, AceType);

public:
    static RefPtr<ThemeConstants> GetThemeConstants(const RefPtr<ResourceObject>& resObj);
    static bool ParseResString(const RefPtr<ResourceObject>& resObj, std::string& result);
    static bool ParseResString(const RefPtr<ResourceObject>& resObj, std::u16string& result);
    static bool ParseResColor(const RefPtr<ResourceObject>& resObj, Color& result);
    static bool ParseResourceToDouble(const RefPtr<ResourceObject>& resObj, double& result);
    static bool ParseResInteger(const RefPtr<ResourceObject>& resObj, int32_t& result);
    static bool ParseResInteger(const RefPtr<ResourceObject>& resObj, uint32_t& result);
    static bool ParseResIntegerArray(const RefPtr<ResourceObject>& resObj, std::vector<uint32_t>& result);
    static bool ParseResStrArray(const RefPtr<ResourceObject>& resObj, std::vector<std::string>& result);
    static bool ParseResFontFamilies(const RefPtr<ResourceObject>& resObj, std::vector<std::string>& result);
    static bool ParseResDouble(const RefPtr<ResourceObject>& resObj, double& result);
    static bool ParseResBool(const RefPtr<ResourceObject>& resObj, bool& result);
    static bool ParseResMedia(const RefPtr<ResourceObject>& resObj, std::string& result);
    static bool ParseResResource(const RefPtr<ResourceObject>& resObj, CalcDimension& result);
    static bool ParseResDimensionFpNG(const RefPtr<ResourceObject>& resObj,
        CalcDimension& result, bool isSupportPercent = true);
    static bool ParseResDimensionVpNG(const RefPtr<ResourceObject>& resObj,
        CalcDimension& result, bool isSupportPercent = true);
    static bool ParseResDimensionNG(const RefPtr<ResourceObject>& resObj, CalcDimension& result,
        DimensionUnit defaultUnit, bool isSupportPercent = true);
    static bool ParseResDimension(const RefPtr<ResourceObject>& resObj, CalcDimension& result,
        DimensionUnit defaultUnit);
    static bool ParseResDimensionVp(const RefPtr<ResourceObject>& resObj, CalcDimension& result);
    static bool ParseResDimensionFp(const RefPtr<ResourceObject>& resObj, CalcDimension& result);
    static bool ParseResDimensionPx(const RefPtr<ResourceObject>& resObj, CalcDimension& result);
    template<class T>
    static bool ConvertFromResObjNG(const RefPtr<ResourceObject>& resObj, T& result);
    template<class T>
    static bool ConvertFromResObj(const RefPtr<ResourceObject>& resObj, T& result);

    static bool IsNumberType(int32_t type)
    {
        return type == static_cast<int32_t>(ResourceType::FLOAT) ||
            type == static_cast<int32_t>(ResourceType::PLURAL) ||
            type == static_cast<int32_t>(ResourceType::INTEGER);
    }

    template<typename T>
    static bool ParseResInteger(const RefPtr<ResourceObject>& resObj, T& result)
    {
        CHECK_NULL_RETURN(resObj, false);
        auto resIdNum = resObj->GetId();
        auto type = resObj->GetType();
        auto resourceAdapter = ResourceManager::GetInstance().GetOrCreateResourceAdapter(resObj);
        RefPtr<ThemeConstants> themeConstants = nullptr;
        auto resourceWrapper = AceType::MakeRefPtr<ResourceWrapper>(themeConstants, resourceAdapter);
        if (resIdNum == -1) {
            auto param = resObj->GetParams()[0];
            if (type == static_cast<int32_t>(ResourceType::INTEGER)) {
                result = static_cast<T>(resourceWrapper->GetIntByName(param.value.value()));
                return true;
            }
            return false;
        }
        if (type == static_cast<int32_t>(ResourceType::INTEGER)) {
            result = static_cast<T>(resourceWrapper->GetInt(resIdNum));
            return true;
        }
        return false;
    }

    static void SetIsReloading(bool isReloading)
    {
        isReloading_ = isReloading;
    }

    static bool IsReloading()
    {
        return isReloading_;
    }

private:
    static void InvertColorWithResource(const RefPtr<ResourceObject>& resObj, Color& result,
        const ColorMode& colorMode);
    static bool ParseResColorWithName(const RefPtr<ResourceObject>& resObj, Color& result,
        RefPtr<ResourceWrapper>& resourceWrapper, const ColorMode& colorMode);
    static bool ParseResStringObj(const std::vector<ResourceObjectParams>& params,
        RefPtr<ResourceWrapper>& resourceWrapper, std::string& result, int32_t type);
    static bool isReloading_;
};
}
#endif
