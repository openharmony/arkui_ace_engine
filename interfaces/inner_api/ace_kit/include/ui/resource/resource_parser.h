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

#include <memory>
#include <string>

#include "ui/properties/color.h"
#include "ui/base/geometry/calc_dimension.h"
#include "ui/resource/resource_info.h"

namespace OHOS::Ace::Kit {
/**
 * @brief Resource parser for resolving various resource types.
 *        Provides static methods to parse resources by ID or name from resource files.
 *        Supports cross-module resource access through bundleName and moduleName.
 *
 * @note All methods are static and thread-safe. Returns true on success, false on failure.
 */
class ACE_FORCE_EXPORT ResourceParser {
public:
    /**
     * @brief Parse dimension resource.
     *        Supports parsing from resource ID or resource name.
     *        Can convert STRING or INTEGER resource types to dimension.
     *
     * @param resourceInfo Resource information containing ID, type, and optional params.
     *                   Use resId for ID-based lookup or params[0] for name-based lookup.
     * @param dimension Output parameter for the parsed dimension value.
     * @return true if parsing succeeded, false otherwise.
     *
     * @note When resource type is STRING or INTEGER, converts string to dimension with VP unit.
     */
    static bool GetDimension(const ResourceInfo& resourceInfo, Ace::CalcDimension& dimension);

    /**
     * @brief Parse color resource.
     *        Supports parsing from resource ID or resource name.
     *
     * @param resourceInfo Resource information containing ID, type, and optional params.
     * @param color Output parameter for the parsed color value.
     * @return true if parsing succeeded, false otherwise.
     */
    static bool GetColor(const ResourceInfo& resourceInfo, Ace::Color& color);

    /**
     * @brief Parse string resource.
     *        Supports parsing from resource ID or resource name.
     *
     * @param resourceInfo Resource information containing ID, type, and optional params.
     * @param str Output parameter for the parsed string value.
     * @return true if parsing succeeded, false otherwise.
     */
    static bool GetString(const ResourceInfo& resourceInfo, std::string& str);

    /**
     * @brief Parse media file path resource.
     *        Supports parsing from resource ID or resource name.
     *
     * @param resourceInfo Resource information containing ID, type, and optional params.
     * @param mediaPath Output parameter for the parsed media file path.
     * @return true if parsing succeeded, false otherwise.
     */
    static bool GetMediaPath(const ResourceInfo& resourceInfo, std::string& mediaPath);

    /**
     * @brief Parse integer resource.
     *        Supports parsing from resource ID or resource name.
     *
     * @param resourceInfo Resource information containing ID, type, and optional params.
     * @param intRes Output parameter for the parsed integer value.
     * @return true if parsing succeeded, false otherwise.
     */
    static bool GetInt(const ResourceInfo& resourceInfo, int32_t& intRes);

    /**
     * @brief Parse double resource.
     *        Supports parsing from resource ID or resource name.
     *
     * @param resourceInfo Resource information containing ID, type, and optional params.
     * @param doubleRes Output parameter for the parsed double value.
     * @return true if parsing succeeded, false otherwise.
     */
    static bool GetDouble(const ResourceInfo& resourceInfo, double& doubleRes);

    /**
     * @brief Parse plural string resource based on count.
     *        Supports parsing from resource ID or resource name.
     *
     * @param resourceInfo Resource information containing ID, type, and optional params.
     * @param count The count used to select the appropriate plural form.
     * @param str Output parameter for the parsed plural string.
     * @return true if parsing succeeded, false otherwise.
     *
     * @note Plural strings are used for localization where different forms are needed
     *       based on numeric values (e.g., "1 item", "2 items").
     */
    static bool GetPluralString(const ResourceInfo& resourceInfo, int count, std::string& str);

    /**
     * @brief Parse boolean resource.
     *        Supports parsing from resource ID or resource name.
     *
     * @param resourceInfo Resource information containing ID, type, and optional params.
     * @param boolRes Output parameter for the parsed boolean value.
     * @return true if parsing succeeded, false otherwise.
     */
    static bool GetBoolean(const ResourceInfo& resourceInfo, bool& boolRes);

    /**
     * @brief Parse integer array resource.
     *        Supports parsing from resource ID or resource name.
     *
     * @param resourceInfo Resource information containing ID, type, and optional params.
     * @param intArray Output parameter for the parsed integer array.
     * @return true if parsing succeeded, false otherwise.
     */
    static bool GetIntArray(const ResourceInfo& resourceInfo, std::vector<uint32_t>& intArray);

    /**
     * @brief Parse string array resource.
     *        Supports parsing from resource ID or resource name.
     *
     * @param resourceInfo Resource information containing ID, type, and optional params.
     * @param strArray Output parameter for the parsed string array.
     * @return true if parsing succeeded, false otherwise.
     */
    static bool GetStringArray(const ResourceInfo& resourceInfo, std::vector<std::string>& strArray);

    /**
     * @brief Parse symbol resource ID.
     *        Supports parsing from resource ID or resource name.
     *
     * @param resourceInfo Resource information containing ID, type, and optional params.
     * @param symbolRes Output parameter for the parsed symbol resource ID.
     * @return true if parsing succeeded, false otherwise.
     *
     * @note Symbols are typically used for icons or glyphs in text rendering.
     */
    static bool GetSymbol(const ResourceInfo& resourceInfo, uint32_t& symbolRes);

    /**
     * @brief Parse media data and load into memory.
     *        Supports parsing from resource ID or resource name.
     *
     * @param resourceInfo Resource information containing ID, type, and optional params.
     * @param len Output parameter for the length of the media data in bytes.
     * @param dest Output parameter for the unique pointer to the media data buffer.
     * @return true if parsing and loading succeeded, false otherwise.
     *
     * @note Caller owns the returned unique_ptr and must ensure proper memory management.
     */
    static bool GetMediaData(const ResourceInfo& resourceInfo, size_t& len, std::unique_ptr<uint8_t[]>& dest);
};
} // namespace OHOS::Ace::Kit

#endif // FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_INCLUDE_RESOURCE_RESOURCE_PARSER_H
