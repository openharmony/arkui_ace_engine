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
        return Color();
    }

    Dimension GetDimension(uint32_t resId) override
    {
        return Dimension();
    }

    std::string GetString(uint32_t resId) override
    {
        return "";
    }

    std::vector<std::string> GetStringArray(uint32_t resId) const override
    {
        return std::vector<std::string>();
    }

    double GetDouble(uint32_t resId) override
    {
        return 0;
    }

    int32_t GetInt(uint32_t resId) override
    {
        return 0;
    }
};
} // namespace OHOS::Ace

#endif