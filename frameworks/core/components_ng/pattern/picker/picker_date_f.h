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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_PICKER_PICKER_DATE_F_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_PICKER_PICKER_DATE_F_H

#include <optional>

namespace OHOS::Ace {

class PickerDateF {
public:
    std::optional<uint32_t> year;
    std::optional<uint32_t> month;
    std::optional<uint32_t> day;
    bool lunar = false;
    bool leap = false;

    PickerDateF() = default;
    ~PickerDateF() = default;

    static PickerDateF CreateYear(uint32_t year)
    {
        PickerDateF date;
        date.year = year;
        return date;
    }

    static PickerDateF CreateMonth(uint32_t month, bool lunar = false, bool leap = false)
    {
        PickerDateF date;
        date.month = month;
        date.lunar = lunar;
        date.leap = leap;
        return date;
    }

    static PickerDateF CreateDay(uint32_t day, bool lunar = false)
    {
        PickerDateF date;
        date.day = day;
        date.lunar = lunar;
        return date;
    }

    static PickerDateF CreateMonthDay(uint32_t month, uint32_t day, bool lunar = false, bool leap = false)
    {
        PickerDateF date;
        date.month = month;
        date.day = day;
        date.lunar = lunar;
        date.leap = leap;
        return date;
    }

    bool operator==(const PickerDateF& other) const
    {
        return year == other.year && month == other.month && day == other.day && lunar == other.lunar &&
               leap == other.leap;
    }
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_PICKER_PICKER_DATE_F_H
