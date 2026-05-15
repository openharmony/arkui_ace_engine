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

#ifndef FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_INCLUDE_UI_RESOURCE_RESOURCE_PARSE_UTILS_H
#define FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_INCLUDE_UI_RESOURCE_RESOURCE_PARSE_UTILS_H

#include <functional>
#include <string>

#include "ui/base/ace_type.h"
#include "ui/base/geometry/calc_dimension.h"
#include "ui/resource/node_info.h"
#include "ui/resource/resource_object.h"

namespace OHOS::Ace {

class ResourceWrapper;

class ACE_FORCE_EXPORT ResourceParseUtilsBase : public AceType {
    DECLARE_ACE_TYPE(ResourceParseUtilsBase, AceType);

public:
    static void CompleteResourceObjectFromColor(RefPtr<ResourceObject>& resObj,
        Color& color, const NG::NodeInfo& nodeInfo);
    static bool ParseResString(const RefPtr<ResourceObject>& resObj, std::string& result);
    static bool ParseResString(const RefPtr<ResourceObject>& resObj, std::u16string& result);
    static bool ParseResColor(const RefPtr<ResourceObject>& resObj, Color& result, bool adaptMaterial = false);
    static bool ParseResColorWithColorMode(const RefPtr<ResourceObject>& resObj, Color& result,
        const ColorMode& colorMode);
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
        return type == static_cast<int32_t>(ResourceObjectParamType::FLOAT) ||
            type == static_cast<int32_t>(ResourceObjectParamType::INT);
    }

protected:
    static bool needReload_;

    static void InvertColorWithResource(const RefPtr<ResourceObject>& resObj, Color& result,
        const ColorMode& colorMode);
    static bool ParseColorWithColorMode(const RefPtr<ResourceObject>& resObj, Color& result,
        const ColorMode& colorMode);
    static bool ParseResColorWithName(const RefPtr<ResourceObject>& resObj, Color& result,
        RefPtr<ResourceWrapper>& resourceWrapper, const ColorMode& colorMode);
    static bool ParseResColorWithId(const RefPtr<ResourceObject>& resObj, Color& result,
        RefPtr<ResourceWrapper>& resourceWrapper, const ColorMode& colorMode, bool adaptMaterial = false);
    static bool ParseResStringObj(const std::vector<ResourceObjectParams>& params,
        RefPtr<ResourceWrapper>& resourceWrapper, std::string& result, int32_t type);
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_INCLUDE_UI_RESOURCE_RESOURCE_PARSE_UTILS_H
