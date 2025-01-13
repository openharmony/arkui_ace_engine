/*
 * Copyright (c) 2021-2022 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_PICKER_PICKER_DATA_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_PICKER_PICKER_DATA_H

#include "base/utils/utils.h"


namespace OHOS::Ace {

enum DatePickerType {
    TIME = 0,
    DATE,
};

enum class DatePickerMode : uint32_t {
    DATE = 0,
    YEAR_AND_MONTH = 1,
    MONTH_AND_DAY = 2,
};

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

private:
    uint32_t year_ = 0;
    uint32_t month_ = 0;
    uint32_t day_ = 0;
    uint32_t week_ = 0;
};

class PickerTime final {
public:
    PickerTime() = default;
    PickerTime(uint32_t hour, uint32_t minute, uint32_t second) : hour_(hour), minute_(minute), second_(second) {}

    ~PickerTime() = default;

    static PickerTime Current();

    uint32_t GetHour() const
    {
        return hour_;
    }
    void SetHour(uint32_t value)
    {
        hour_ = value;
    }

    uint32_t GetMinute() const
    {
        return minute_;
    }
    void SetMinute(uint32_t value)
    {
        minute_ = value;
    }

    uint32_t GetSecond() const
    {
        return second_;
    }
    void SetSecond(uint32_t value)
    {
        second_ = value;
    }

    std::string ToString(bool jsonFormat, bool hasSecond, int32_t status = -1) const;
    uint32_t ToMinutes() const;

private:
    uint32_t hour_ = 0;
    uint32_t minute_ = 0;
    uint32_t second_ = 0;
};

class PickerDateTime final {
public:
    PickerDateTime() = default;
    PickerDateTime(const PickerDate& date, const PickerTime& time) : date_(date), time_(time) {}

    ~PickerDateTime() = default;

    static PickerDateTime Current();

    const PickerDate& GetDate() const
    {
        return date_;
    }
    void SetDate(const PickerDate& value)
    {
        date_ = value;
    }

    const PickerTime& GetTime() const
    {
        return time_;
    }
    void SetTime(const PickerTime& value)
    {
        time_ = value;
    }

    std::string ToString(bool jsonFormat, int32_t status = -1) const;

private:
    PickerDate date_;
    PickerTime time_;
};

class LunarCalculator {
public:
    static uint32_t GetLunarLeapMonth(uint32_t lunarYear)
    {
        if (lunarYear >= YEAR_START + LUNAR_INFO_SIZE) {
            return 0;
        }
        uint32_t leapMonth = LUNAR_INFO[lunarYear - YEAR_START] & 0xf; // use 0xf to get leap month info
        return leapMonth == 0xf ? 0 : leapMonth;
    }

    static uint32_t GetLunarLeapDays(uint32_t lunarYear)
    {
        if (lunarYear >= YEAR_START - 1 + LUNAR_INFO_SIZE) {
            return 0;
        }
        return GetLunarLeapMonth(lunarYear) > 0 ? ((LUNAR_INFO[lunarYear - YEAR_START + 1] & 0xf) == 0xf ? 30 : 29)
                                                : 0; // big month 30 days other 29
    }

    static uint32_t GetLunarYearDays(uint32_t lunarYear)
    {
        if (lunarYear >= YEAR_START + LUNAR_INFO_SIZE) {
            return 0;
        }
        uint32_t totalDays = 348;                          // lunar year has (12 * 29 =) 348 days at least
        for (uint32_t i = 0x8000; i > 0x8; i >>= 1) { // get month info from bit of LUNAR_INFO
            totalDays += ((LUNAR_INFO[lunarYear - YEAR_START] & i) != 0) ? 1 : 0;
        }

        return totalDays + GetLunarLeapDays(lunarYear);
    }

    static uint32_t GetLunarMonthDays(uint32_t lunarYear, uint32_t lunarMonth)
    {
        if (lunarYear >= YEAR_START + LUNAR_INFO_SIZE) {
            return 0;
        }
        uint32_t month = static_cast<uint32_t>(lunarMonth);
        // big month 30 days other 29
        return ((LUNAR_INFO[lunarYear - YEAR_START] & (0x10000u >> (month % MAX_MONTH))) != 0) ? 30 : 29;
    }

private:
    static constexpr uint32_t YEAR_START = 1897; // start year reference with LUNAR_INFO
    static constexpr int32_t LUNAR_INFO_SIZE = 207;
    static constexpr uint32_t MAX_MONTH = 13;
    static const uint16_t LUNAR_INFO[];
};

class PickerStringFormatter {
public:
    static const std::string& GetYear(uint32_t year);

    static const std::string& GetSolarMonth(uint32_t month);

    static const std::string& GetSolarDay(uint32_t day);

    static const std::string& GetLunarMonth(uint32_t month, bool isLeap);

    static const std::string& GetLunarDay(uint32_t day);

    static const std::vector<std::string>& GetTagOrder();

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
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_PICKER_PICKER_DATA_H
