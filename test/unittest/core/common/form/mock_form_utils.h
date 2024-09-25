/*
 * Copyright (c) 2023-2024 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_TEST_UNITTEST_CORE_COMMON_FORM_MOCK_FORM_TUILS_H
#define FOUNDATION_ACE_TEST_UNITTEST_CORE_COMMON_FORM_MOCK_FORM_TUILS_H

#include <string>

#include "core/components/form/resource/form_utils.h"

namespace OHOS::Ace {
class MockFormUtils final : public FormUtils {
public:
    MockFormUtils() = default;
    ~MockFormUtils() = default;

    int32_t RouterEvent(const int64_t formId, const std::string& action, const int32_t containerId,
        const std::string& defualtbundleName)
    {
        return 1;
    }

    int32_t RequestPublishFormEvent(const AAFwk::Want& want, const std::string& formBindingDataStr, int64_t& formId,
        std::string& errMsg)
    {
        return 1;
    }
    
    int32_t BackgroundEvent(const int64_t formId, const std::string& action, const int32_t containerId,
        const std::string& defualtbundleName)
    {
        return 1;
    }
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_TEST_UNITTEST_CORE_COMMON_FORM_MOCK_FORM_TUILS_H