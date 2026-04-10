/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_TEST_MOCK_RESOURCE_MOCK_RESOURCE_ADAPTER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_TEST_MOCK_RESOURCE_MOCK_RESOURCE_ADAPTER_H

#include "gmock/gmock.h"

#include "core/components/theme/resource_adapter.h"

namespace OHOS::Ace {
class MockResourceAdapter : public ResourceAdapter {
    DECLARE_ACE_TYPE(MockResourceAdapter, ResourceAdapter);

public:
    MockResourceAdapter() = default;
    ~MockResourceAdapter() override = default;
    
    /**
     * @brief Initialize resource adapter with resource information
     * @param resourceInfo The resource configuration information
     */
    MOCK_METHOD1(Init, void(const ResourceInfo& resourceInfo));
    
    /**
     * @brief Update resource configuration
     * @param config The resource configuration to update
     * @param themeFlag Whether this is a theme-related configuration update
     */
    MOCK_METHOD2(UpdateConfig, void(const ResourceConfiguration& config, bool themeFlag));
    
    /**
     * @brief Get theme style by theme ID
     * @param themeId The theme identifier
     * @return The theme style object
     */
    MOCK_METHOD1(GetTheme, RefPtr<ThemeStyle>(int32_t themeId));
    
    /**
     * @brief Get color resource by resource ID
     * @param resId The resource identifier
     * @return The color value
     */
    MOCK_METHOD1(GetColor, Color(uint32_t resId));
    
    /**
     * @brief Get dimension resource by resource ID
     * @param resId The resource identifier
     * @return The dimension value
     */
    MOCK_METHOD1(GetDimension, Dimension(uint32_t resId));
    
    /**
     * @brief Get string resource by resource ID
     * @param resId The resource identifier
     * @return The string value
     */
    MOCK_METHOD1(GetString, std::string(uint32_t resId));
    
    /**
     * @brief Get double resource by resource ID
     * @param resId The resource identifier
     * @return The double value
     */
    MOCK_METHOD1(GetDouble, double(uint32_t resId));
    
    /**
     * @brief Get integer resource by resource ID
     * @param resId The resource identifier
     * @return The integer value
     */
    MOCK_METHOD1(GetInt, int32_t(uint32_t resId));
    
    /**
     * @brief Get plural string resource
     * @param resId The resource identifier
     * @param quantity The quantity for plural selection
     * @return The plural string
     */
    MOCK_METHOD2(GetPluralString, std::string(uint32_t resId, int quantity));
    
    /**
     * @brief Get media path by resource ID
     * @param resId The resource identifier
     * @return The media file path
     */
    MOCK_METHOD1(GetMediaPath, std::string(uint32_t resId));
    
    /**
     * @brief Get rawfile path by file name
     * @param fileName The rawfile name
     * @return The rawfile path
     */
    MOCK_METHOD1(GetRawfile, std::string(const std::string& fileName));
    
    /**
     * @brief Get raw file data by file name
     * @param rawFile The rawfile name
     * @param len Output parameter for data length
     * @param dest Output parameter for data buffer
     * @return True if successful, false otherwise
     */
    MOCK_METHOD3(GetRawFileData, bool(const std::string& rawFile, size_t& len, std::unique_ptr<uint8_t[]>& dest));
    
    /**
     * @brief Get media data by resource ID
     * @param resId The resource identifier
     * @param len Output parameter for data length
     * @param dest Output parameter for data buffer
     * @return True if successful, false otherwise
     */
    MOCK_METHOD3(GetMediaData, bool(uint32_t resId, size_t& len, std::unique_ptr<uint8_t[]>& dest));
    
    /**
     * @brief Get media data by resource name
     * @param resName The resource name
     * @param len Output parameter for data length
     * @param dest Output parameter for data buffer
     * @return True if successful, false otherwise
     */
    MOCK_METHOD3(GetMediaData, bool(const std::string& resName, size_t& len, std::unique_ptr<uint8_t[]>& dest));
    
    /**
     * @brief Update resource manager with bundle and module info
     * @param bundleName The bundle name
     * @param moduleName The module name
     */
    MOCK_METHOD2(UpdateResourceManager, void(const std::string& bundleName, const std::string& moduleName));
    
    /**
     * @brief Get boolean resource by resource ID
     * @param resId The resource identifier
     * @return The boolean value
     */
    MOCK_CONST_METHOD1(GetBoolean, bool(uint32_t resId));
    
    /**
     * @brief Get integer array resource by resource ID
     * @param resId The resource identifier
     * @return The integer array
     */
    MOCK_CONST_METHOD1(GetIntArray, std::vector<uint32_t>(uint32_t resId));
    
    /**
     * @brief Get resource data as stream by resource ID
     * @param resId The resource identifier
     * @param dest The output stream
     * @return True if successful, false otherwise
     */
    MOCK_CONST_METHOD2(GetResource, bool(uint32_t resId, std::ostream& dest));
    
    /**
     * @brief Get resource data as stream by resource name
     * @param resId The resource name
     * @param dest The output stream
     * @return True if successful, false otherwise
     */
    MOCK_CONST_METHOD2(GetResource, bool(const std::string& resId, std::ostream& dest));
    
    /**
     * @brief Get resource ID by name and type
     * @param resName The resource name
     * @param resType The resource type
     * @param resId Output parameter for the resource ID
     * @return True if found, false otherwise
     */
    MOCK_CONST_METHOD3(GetIdByName, bool(const std::string& resName, const std::string& resType, uint32_t& resId));
    
    /**
     * @brief Get string array resource by resource ID
     * @param resId The resource identifier
     * @return The string array
     */
    MOCK_CONST_METHOD1(GetStringArray, std::vector<std::string>(uint32_t resId));
    
    // Add missing GetName methods that are required by ResourceWrapper
    // These methods allow resource lookup by name instead of ID
    
    /**
     * @brief Get color resource by resource name
     * @param resName The resource name
     * @return The color value
     */
    MOCK_METHOD1(GetColorByName, Color(const std::string& resName));
    
    /**
     * @brief Get dimension resource by resource name
     * @param resName The resource name
     * @return The dimension value
     */
    MOCK_METHOD1(GetDimensionByName, Dimension(const std::string& resName));
    
    /**
     * @brief Get string resource by resource name
     * @param resName The resource name
     * @return The string value
     */
    MOCK_METHOD1(GetStringByName, std::string(const std::string& resName));
    
    /**
     * @brief Get double resource by resource name
     * @param resName The resource name
     * @return The double value
     */
    MOCK_METHOD1(GetDoubleByName, double(const std::string& resName));
    
    /**
     * @brief Get integer resource by resource name
     * @param resName The resource name
     * @return The integer value
     */
    MOCK_METHOD1(GetIntByName, int32_t(const std::string& resName));
    
    /**
     * @brief Get plural string resource by resource name
     * @param resName The resource name
     * @param count The quantity for plural selection
     * @return The plural string
     */
    MOCK_METHOD2(GetPluralStringByName, std::string(const std::string& resName, int count));
    
    /**
     * @brief Get media path by resource name
     * @param resName The resource name
     * @return The media file path
     */
    MOCK_METHOD1(GetMediaPathByName, std::string(const std::string& resName));
    
    /**
     * @brief Get boolean resource by resource name
     * @param resName The resource name
     * @return The boolean value
     */
    MOCK_CONST_METHOD1(GetBooleanByName, bool(const std::string& resName));
    
    /**
     * @brief Get integer array resource by resource name
     * @param resName The resource name
     * @return The integer array
     */
    MOCK_CONST_METHOD1(GetIntArrayByName, std::vector<uint32_t>(const std::string& resName));
    
    /**
     * @brief Get string array resource by resource name
     * @param resName The resource name
     * @return The string array
     */
    MOCK_CONST_METHOD1(GetStringArrayByName, std::vector<std::string>(const std::string& resName));
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_TEST_MOCK_RESOURCE_MOCK_RESOURCE_ADAPTER_H
