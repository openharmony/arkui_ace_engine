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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_DATE_PICKER_PICKER_DATE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_DATE_PICKER_PICKER_DATE_H

#include <string>
#include <utility>
#include <vector>

#include "base/utils/utils.h"

namespace OHOS::Ace {

class ACE_FORCE_EXPORT PickerDate final {
public:
    PickerDate() = default;
    PickerDate(uint32_t year, uint32_t month, uint32_t day) : year_(year), month_(month), day_(day) {}

    ~PickerDate() = default;

    static PickerDate Current();

    static uint32_t GetMaxDay(uint32_t year, uint32_t month);

    static bool IsLeapYear(uint32_t year);

    static PickerDate AdjustDateToRange(const PickerDate& date, const PickerDate& start, const PickerDate& end);

    static bool IsDateInRange(const PickerDate& date, const PickerDate& start, const PickerDate& end);

    static void SortAndMergeDisabledDateRange(std::vector<std::pair<PickerDate, PickerDate>>& disableDateRange);

    static PickerDate GetAvailableNextDay(const PickerDate& date, const PickerDate& start, const PickerDate& end,
        std::vector<std::pair<PickerDate, PickerDate>>& disableDateRange, bool isAdd);

    static PickerDate PrevDay(const PickerDate& dateObj);

    static PickerDate NextDay(const PickerDate& dateObj);

    uint32_t GetYear() const
    {
        return year_;
    }
    void SetYear(uint32_t value)
    {
        year_ = value;
    }

    uint32_t GetMonth() const
    {
        return month_;
    }
    void SetMonth(uint32_t value)
    {
        month_ = value;
    }

    uint32_t GetDay() const
    {
        return day_;
    }
    void SetDay(uint32_t value)
    {
        day_ = value;
    }

    uint32_t GetWeek() const
    {
        return week_;
    }
    void SetWeek(uint32_t value)
    {
        week_ = value;
    }

    std::string ToString(bool jsonFormat, int32_t status = -1) const;

    uint32_t ToDays() const;
    void FromDays(uint32_t days);

    bool operator<(const PickerDate& other) const
    {
        if (year_ != other.year_) {
            return year_ < other.year_;
        }
        if (month_ != other.month_) {
            return month_ < other.month_;
        }
        return day_ < other.day_;
    }

    bool operator<=(const PickerDate& other) const
    {
        if (year_ != other.year_) {
            return year_ < other.year_;
        }
        if (month_ != other.month_) {
            return month_ < other.month_;
        }
        return day_ <= other.day_;
    }

    bool operator==(const PickerDate& other) const
    {
        return year_ == other.year_ && month_ == other.month_ && day_ == other.day_;
    }

private:
    uint32_t year_ = 0;
    uint32_t month_ = 0;
    uint32_t day_ = 0;
    uint32_t week_ = 0;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_DATE_PICKER_PICKER_DATE_H
