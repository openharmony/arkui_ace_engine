/*
 * Copyright (c) 2021-2026 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_DATE_PICKER_PICKER_STRING_FORMATTER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_DATE_PICKER_PICKER_STRING_FORMATTER_H

#include <string>
#include <vector>

#include "base/utils/utils.h"

namespace OHOS::Ace {

class PickerStringFormatter {
public:
    ACE_FORCE_EXPORT static const std::string& GetYear(uint32_t year);

    ACE_FORCE_EXPORT static const std::string& GetSolarMonth(uint32_t month);

    ACE_FORCE_EXPORT static const std::string& GetSolarDay(uint32_t day);

    ACE_FORCE_EXPORT static const std::string& GetLunarMonth(uint32_t month, bool isLeap);

    ACE_FORCE_EXPORT static const std::string& GetLunarDay(uint32_t day);

    ACE_FORCE_EXPORT static const std::vector<std::string>& GetTagOrder();

private:
    static void Init();

    static bool inited_;

    static const std::string empty_;

    static std::vector<std::string> years_; // year from 1900 to 2100,count is 201

    static std::vector<std::string> solarMonths_; // solar month from 1 to 12,count is 12
    static std::vector<std::string> solarDays_; // solar day from 1 to 31, count is 31

    static std::vector<std::string> lunarMonths_; // lunar month from 1 to 24, count is 24
    static std::vector<std::string> lunarDays_; // lunar day from 1 to 30, count is 30
    static std::vector<std::string> tagOrder_; // year month day tag order
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_DATE_PICKER_PICKER_STRING_FORMATTER_H
