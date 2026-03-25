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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_RESOURCE_MOCK_RESOURCE_WRAPPER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_RESOURCE_MOCK_RESOURCE_WRAPPER_H

#include "gmock/gmock.h"

#include "base/geometry/dimension.h"
#include "base/image/pixel_map.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "base/utils/device_config.h"
#include "base/utils/system_properties.h"
#include "core/common/resource/resource_wrapper.h"
#include "core/components/common/properties/color.h"
#include "core/components/theme/resource_adapter.h"
#include "core/components/theme/theme_constants.h"

namespace OHOS::Ace {
class MockResourceWrapper : public ResourceWrapper {
    DECLARE_ACE_TYPE(MockResourceWrapper, ResourceWrapper);

public:
    /**
     * @brief Construct mock resource wrapper with theme constants and resource adapter
     * @param themeConstants Theme constants for resource lookup
     * @param resourceAdapter Resource adapter for resource access
     */
    MockResourceWrapper(RefPtr<ThemeConstants>& themeConstants, RefPtr<ResourceAdapter>& resourceAdapter)
        : ResourceWrapper(themeConstants, resourceAdapter)
    {}
    
    /**
     * @brief Destructor for mock resource wrapper
     */
    ~MockResourceWrapper() override = default;
    
    /**
     * @defgroup ThemeConstantsMethods Theme Constants Methods
     * @{
     */
    
    // ThemeConstants methods
    
    /**
     * @brief Get color resource by ID
     * @param key The resource ID
     * @return The color value
     */
    MOCK_METHOD1(GetColor, Color(uint32_t key));

    /**
     * @brief Get color resource by name
     * @param resName The resource name
     * @return The color value
     */
    MOCK_METHOD1(GetColorByName, Color(const std::string& resName));

    /**
     * @brief Get dimension resource by ID
     * @param key The resource ID
     * @return The dimension value
     */
    MOCK_METHOD1(GetDimension, Dimension(uint32_t key));

    /**
     * @brief Get dimension resource by name
     * @param resName The resource name
     * @return The dimension value
     */
    MOCK_METHOD1(GetDimensionByName, Dimension(const std::string& resName));

    /**
     * @brief Get integer resource by ID
     * @param key The resource ID
     * @return The integer value
     */
    MOCK_METHOD1(GetInt, int32_t(uint32_t key));

    /**
     * @brief Get integer resource by name
     * @param resName The resource name
     * @return The integer value
     */
    MOCK_METHOD1(GetIntByName, int32_t(const std::string& resName));

    /**
     * @brief Get double resource by ID
     * @param key The resource ID
     * @return The double value
     */
    MOCK_METHOD1(GetDouble, double(uint32_t key));

    /**
     * @brief Get double resource by name
     * @param resName The resource name
     * @return The double value
     */
    MOCK_METHOD1(GetDoubleByName, double(const std::string& resName));

    /**
     * @brief Get string resource by ID
     * @param key The resource ID
     * @return The string value
     */
    MOCK_METHOD1(GetString, std::string(uint32_t key));

    /**
     * @brief Get string resource by name
     * @param resName The resource name
     * @return The string value
     */
    MOCK_METHOD1(GetStringByName, std::string(const std::string& resName));

    /**
     * @brief Get plural string resource by ID
     * @param key The resource ID
     * @param count The quantity for plural selection
     * @return The plural string
     */
    MOCK_METHOD2(GetPluralString, std::string(uint32_t key, int count));

    /**
     * @brief Get plural string resource by name
     * @param resName The resource name
     * @param count The quantity for plural selection
     * @return The plural string
     */
    MOCK_METHOD2(GetPluralStringByName, std::string(const std::string& resName, int count));

    /**
     * @brief Get boolean resource by ID
     * @param key The resource ID
     * @return The boolean value
     */
    MOCK_METHOD1(GetBoolean, bool(uint32_t key));

    /**
     * @brief Get boolean resource by name
     * @param resName The resource name
     * @return The boolean value
     */
    MOCK_METHOD1(GetBooleanByName, bool(const std::string& resName));

    /**
     * @brief Get integer array resource by ID
     * @param key The resource ID
     * @return The integer array
     */
    MOCK_METHOD1(GetIntArray, std::vector<uint32_t>(uint32_t key));

    /**
     * @brief Get integer array resource by name
     * @param resName The resource name
     * @return The integer array
     */
    MOCK_METHOD1(GetIntArrayByName, std::vector<uint32_t>(const std::string& resName));

    /**
     * @brief Get string array resource by ID
     * @param key The resource ID
     * @return The string array
     */
    MOCK_METHOD1(GetStringArray, std::vector<std::string>(uint32_t key));

    /**
     * @brief Get string array resource by name
     * @param resName The resource name
     * @return The string array
     */
    MOCK_METHOD1(GetStringArrayByName, std::vector<std::string>(const std::string& resName));
    
    /**
     * @defgroup MediaMethods Media Resource Methods
     * @{
     */

    /**
     * @brief Get media file path by resource ID
     * @param key The resource ID
     * @return The media file path
     */
    MOCK_METHOD1(GetMediaPath, std::string(uint32_t key));

    /**
     * @brief Get media file path by name
     * @param resName The resource name
     * @return The media file path
     */
    MOCK_METHOD1(GetMediaPathByName, std::string(const std::string& resName));

    /**
     * @brief Get rawfile path by file name
     * @param fileName The rawfile name
     * @return The rawfile path
     */
    MOCK_METHOD1(GetRawfile, std::string(const std::string& fileName));

    /**
     * @brief Get rawfile description
     * @param rawfileName The rawfile name
     * @param rawfileDescription Output parameter for rawfile description
     * @return True if successful, false otherwise
     */
    MOCK_METHOD2(GetRawFileDescription, bool(const std::string& rawfileName, RawfileDescription& rawfileDescription));

    /**
     * @brief Close rawfile description
     * @param rawfileName The rawfile name
     * @return True if successful, false otherwise
     */
    MOCK_METHOD1(CloseRawFileDescription, bool(const std::string& rawfileName));

    /**
     * @brief Get rawfile file descriptor
     * @param rawfileName The rawfile name
     * @param rawfileDescription Output parameter for rawfile description
     * @return True if successful, false otherwise
     */
    MOCK_METHOD2(GetRawFD, bool(const std::string& rawfileName, RawfileDescription& rawfileDescription));
    MOCK_METHOD2(GetMediaById, bool(const int32_t& resId, std::string& mediaPath));
    MOCK_METHOD1(GetSymbolByName, uint32_t(const char* name));
    MOCK_METHOD1(GetSymbolById, uint32_t(uint32_t resId));
    MOCK_METHOD0(UpdateColorMode, void());
    MOCK_METHOD3(GetMediaData, bool(uint32_t resId, size_t& len, std::unique_ptr<uint8_t[]>& dest));
    MOCK_METHOD5(GetMediaData, bool(uint32_t resId, size_t& len, std::unique_ptr<uint8_t[]>& dest,
                                         const std::string& bundleName, const std::string& moduleName));
    MOCK_METHOD3(GetRawFileData, bool(const std::string& rawFile, size_t& len, std::unique_ptr<uint8_t[]>& dest));
    MOCK_METHOD5(GetRawFileData, bool(const std::string& rawFile, size_t& len, std::unique_ptr<uint8_t[]>& dest,
                                           const std::string& bundleName, const std::string& moduleName));
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_RESOURCE_MOCK_RESOURCE_WRAPPER_H
