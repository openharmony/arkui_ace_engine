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

#ifndef FOUNDATION_ACE_FRAMEWORKS_COMPONENTS_NG_PROPERTY_A11Y_HELPER_H
#define FOUNDATION_ACE_FRAMEWORKS_COMPONENTS_NG_PROPERTY_A11Y_HELPER_H

#include <cstddef>
#include <cstdint>
#include <string>
#include <unordered_map>

#if defined(OHOS_STANDARD_SYSTEM) and !defined(ACE_UNITTEST)
#include "accessibility_element_info.h"
// The inclusion of accessibility_element_info.h is necessary for this module.
#else
namespace OHOS::Accessibility {
class ExtraElementInfo {
public:
    /**
     * @brief Copy the ExtraElementInfo
     * @param keyStr The key of extraElementValueStr.
     * @param valueStr The value of extraElementValueStr.
     */
    int32_t SetExtraElementInfo(const std::string& keyStr, const std::string& valueStr)
    {
        extraElementValueStr_[keyStr] = valueStr;
        return 0;
    }

    /**
     * @brief Copy the ExtraElementInfo
     * @param keyStr The key of extraElementValueInt.
     * @param valueInt The val of extraElementValueInt.
     */
    int32_t SetExtraElementInfo(const std::string& keyStr, const int32_t valueInt)
    {
        extraElementValueInt_[keyStr] = valueInt;
        return 0;
    }

    const std::unordered_map<std::string, std::string>& GetExtraElementInfoValueStr() const
    {
        return extraElementValueStr_;
    }

    const std::unordered_map<std::string, int32_t>& GetExtraElementInfoValueInt() const
    {
        return extraElementValueInt_;
    }

private:
    std::unordered_map<std::string, std::string> extraElementValueStr_;
    std::unordered_map<std::string, int32_t> extraElementValueInt_;
};
}
#endif
#endif // FOUNDATION_ACE_FRAMEWORKS_COMPONENTS_NG_PROPERTY_A11Y_HELPER_H
