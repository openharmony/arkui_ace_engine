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
    MOCK_METHOD0(Create, RefPtr<ResourceAdapter>());
    MOCK_METHOD1(Init, void(const ResourceInfo& resourceInfo));
    MOCK_METHOD2(UpdateConfig, void(const ResourceConfiguration& config, bool themeFlag));
    MOCK_METHOD1(GetTheme, RefPtr<ThemeStyle>(int32_t themeId));
    MOCK_METHOD1(GetColor, Color(uint32_t resId));
    MOCK_METHOD1(GetDimension, Dimension(uint32_t resId));
    MOCK_METHOD1(GetString, std::string(uint32_t resId));
    MOCK_METHOD1(GetDouble, double(uint32_t resId));
    MOCK_METHOD1(GetInt, int32_t(uint32_t resId));
    MOCK_METHOD2(GetPluralString, std::string(uint32_t resId, int quantity));
    MOCK_METHOD1(GetMediaPath, std::string(uint32_t resId));
    MOCK_METHOD1(GetRawfile, std::string(const std::string& fileName));
    MOCK_METHOD3(GetRawFileData, bool(const std::string& rawFile, size_t& len, std::unique_ptr<uint8_t[]>& dest));
    MOCK_METHOD3(GetMediaData, bool(uint32_t resId, size_t& len, std::unique_ptr<uint8_t[]>& dest));
    MOCK_METHOD3(GetMediaData, bool(const std::string& resName, size_t& len, std::unique_ptr<uint8_t[]>& dest));
    MOCK_METHOD2(UpdateResourceManager, void(const std::string& bundleName, const std::string& moduleName));
    MOCK_CONST_METHOD1(GetBoolean, bool(uint32_t resId));
    MOCK_CONST_METHOD1(GetIntArray, std::vector<uint32_t>(uint32_t resId));
    MOCK_CONST_METHOD2(GetResource, bool(uint32_t resId, std::ostream& dest));
    MOCK_CONST_METHOD2(GetResource, bool(const std::string& resId, std::ostream& dest));
    MOCK_CONST_METHOD3(GetIdByName, bool(const std::string& resName, const std::string& resType, uint32_t& resId));
    MOCK_CONST_METHOD1(GetStringArray, std::vector<std::string>(uint32_t resId));
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_TEST_MOCK_RESOURCE_MOCK_RESOURCE_ADAPTER_H
