/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_TEST_MOCK_RESOURCE_MOCK_RESOURCE_ADAPTER_V2_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_TEST_MOCK_RESOURCE_MOCK_RESOURCE_ADAPTER_V2_H

#include "core/components/theme/resource_adapter.h"

namespace OHOS::Ace {
class MockResourceAdapterV2 : public ResourceAdapter {
    DECLARE_ACE_TYPE(MockResourceAdapterV2, ResourceAdapter);

public:
    MockResourceAdapterV2() = default;
    ~MockResourceAdapterV2() = default;

    Color GetColor(uint32_t resId) override
    {
        Color data;
        return GetMockResourceData(resId, data) ? data : Color();
    }

    Dimension GetDimension(uint32_t resId) override
    {
        Dimension data;
        return GetMockResourceData(resId, data) ? data : Dimension();
    }

    std::string GetString(uint32_t resId) override
    {
        std::string data;
        return GetMockResourceData(resId, data) ? data : "";
    }

    std::vector<std::string> GetStringArray(uint32_t resId) const override
    {
        std::vector<std::string> data;
        return GetMockResourceData(resId, data) ? data : std::vector<std::string>();
    }

    double GetDouble(uint32_t resId) override
    {
        double data = 0.0f;
        return GetMockResourceData(resId, data) ? data : 0;
    }

    int32_t GetInt(uint32_t resId) override
    {
        int32_t data = 0;
        return GetMockResourceData(resId, data) ? data : 0;
    }

private:
    static bool GetMockResourceData(uint32_t id, Color& data);
    static bool GetMockResourceData(uint32_t id, Dimension& data);
    static bool GetMockResourceData(uint32_t id, std::string& data);
    static bool GetMockResourceData(uint32_t id, std::vector<std::string>& data);
    static bool GetMockResourceData(uint32_t id, double& data);
    static bool GetMockResourceData(uint32_t id, int32_t& data);
};

void ResetMockResourceData();
void AddMockResourceData(uint32_t id, const Color& data);
void AddMockResourceData(uint32_t id, const Dimension& data);
void AddMockResourceData(uint32_t id, const std::string& data);
void AddMockResourceData(uint32_t id, const std::vector<std::string>& data);
void AddMockResourceData(uint32_t id, const double& data);
void AddMockResourceData(uint32_t id, const int32_t& data);

} // namespace OHOS::Ace

#endif