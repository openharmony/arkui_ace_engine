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

#ifndef FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_INCLUDE_RESOURCE_RESOURCE_PARSER_H
#define FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_INCLUDE_RESOURCE_RESOURCE_PARSER_H

#include <string>

#include "ui/properties/color.h"
#include "ui/base/geometry/dimension.h"
#include "ui/resource/resource_info.h"

namespace OHOS::Ace::Kit {
class ACE_FORCE_EXPORT ResourceParser {
public:
    static bool GetDimension(const ResourceInfo& resourceInfo, Ace::Dimension& dimension);
    static bool GetColor(const ResourceInfo& resourceInfo, Ace::Color& color);
    static bool GetString(const ResourceInfo& resourceInfo, std::string& str);
    static bool GetMediaPath(const ResourceInfo& resourceInfo, std::string& mediaPath);
    static bool GetInt(const ResourceInfo& resourceInfo, int32_t& intRes);
    static bool GetDouble(const ResourceInfo& resourceInfo, double& doubleRes);
    static bool GetPluralString(const ResourceInfo& resourceInfo, int count, std::string& str);
    static bool GetBoolean(const ResourceInfo& resourceInfo, bool& boolRes);
    static bool GetIntArray(const ResourceInfo& resourceInfo, std::vector<uint32_t>& intArray);
    static bool GetStringArray(const ResourceInfo& resourceInfo, std::vector<std::string>& strArray);
    static bool GetSymbol(const ResourceInfo& resourceInfo, uint32_t& symbolRes);
};
} // namespace OHOS::Ace::Kit

#endif // FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_INCLUDE_RESOURCE_RESOURCE_PARSER_H
