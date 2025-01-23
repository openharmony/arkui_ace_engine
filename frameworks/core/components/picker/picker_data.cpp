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

#include "core/components/picker/picker_data.h"

#include "base/i18n/localization.h"

namespace OHOS::Ace {
namespace {
constexpr uint32_t MAX_YEAR = 5000;
constexpr uint32_t MAX_MONTH = 12;
}

PickerDate PickerDate::Current()
{
    PickerDate date;
    auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    auto local = std::localtime(&now);
    if (local == nullptr) {
        LOGE("get localtime failed.");
        return date;
    }
    date.SetYear(local->tm_year + 1900); // local date start from 1900
    date.SetMonth(local->tm_mon + 1);    // local month start from 0 to 11, need add one.
    date.SetDay(local->tm_mday);
    date.SetWeek(local->tm_wday);
    return date;
}

uint32_t PickerDate::GetMaxDay(uint32_t year, uint32_t month)
{
    if (month == 2) { // days count in february is different between leap year and other.
        bool leapYear = IsLeapYear(year);
        return (leapYear ? 29 : 28); // leap year's february has 29 days, other has 28 days.
    }

    switch (month) {
        case 1:        // january
        case 3:        // march
        case 5:        // may
        case 7:        // july
        case 8:        // august
        case 10:       // october
        case 12:       // december
            return 31; // upper months has 31 days
        default:
            return 30; // other month has 30 days
    }
}

bool PickerDate::IsLeapYear(uint32_t year)
{
    if (year % 100 == 0) {        // special case: year can divided by 100
        return (year % 400 == 0); // leap year equal that can divided by 400.
    }

    return (year % 4 == 0); // other case, leap year equal that can divided by 4.
}

PickerDate PickerDate::AdjustDateToRange(const PickerDate& date, const PickerDate& start, const PickerDate& end)
{
    PickerDate adjustedDate = date;
    if (start.ToDays() > date.ToDays()) {
        adjustedDate = start;
    } else if (end.GetYear() > 0 && end.ToDays() < date.ToDays()) {
        adjustedDate = end;
    }
    return adjustedDate;
}

bool PickerDate::IsDateInRange(const PickerDate& date, const PickerDate& start, const PickerDate& end)
{
    if (start.GetYear() > 0 &&
        (date.GetYear() < start.GetYear() ||
            (date.GetYear() == start.GetYear() &&
                (date.GetMonth() < start.GetMonth() ||
                    (date.GetMonth() == start.GetMonth() && date.GetDay() < start.GetDay()))))) {
        return false;
    }
    if (end.GetYear() > 0 &&
        (date.GetYear() > end.GetYear() ||
            (date.GetYear() == end.GetYear() &&
                (date.GetMonth() > end.GetMonth() ||
                    (date.GetMonth() == end.GetMonth() && date.GetDay() > end.GetDay()))))) {
        return false;
    }
    return true;
}

std::string PickerDate::ToString(bool jsonFormat, int32_t status) const
{
    if (!jsonFormat) {
        DateTime date;
        date.year = year_;
        date.month = month_ ? month_ - 1 : 0; // W3C's month start from 0 to 11
        date.day = day_;
        return Localization::GetInstance()->FormatDateTime(date, DateTimeStyle::FULL, DateTimeStyle::NONE);
    }

    return std::string("{\"year\":") + std::to_string(year_) + ",\"month\":" + std::to_string(month_) +
           ",\"day\":" + std::to_string(day_) + ",\"status\":" + std::to_string(status) + "}";
}

uint32_t PickerDate::ToDays() const
{
    uint32_t days = 0;
    days += day_ ? day_ - 1 : 0; // day start from 1
    // month start from 1
    for (uint32_t month = 1; month < month_; ++month) {
        days += PickerDate::GetMaxDay(year_, month);
    }
    // year start from 1900 or 1
    uint32_t startYear = 1900;
    if (year_ < startYear) {
        startYear = 1;
    }
    for (uint32_t year = startYear; year < year_; ++year) {
        // leap year has 366 days, other year has 365 days.
        days += (PickerDate::IsLeapYear(year) ? 366 : 365);
    }
    return days;
}

void PickerDate::FromDays(uint32_t days)
{
    for (year_ = 1900; year_ <= 2100; ++year_) { // year start from 1900 to 2100.
        // leap year has 366 days, other year has 365 days;
        uint32_t daysInYear = (PickerDate::IsLeapYear(year_) ? 366 : 365);
        if (days < daysInYear) {
            break;
        } else {
            days -= daysInYear;
        }
    }

    for (month_ = 1; month_ <= 12; ++month_) { // month start from 1 to 12
        uint32_t daysInMonth = PickerDate::GetMaxDay(year_, month_);
        if (days < daysInMonth) {
            break;
        } else {
            days -= daysInMonth;
        }
    }

    day_ = days + 1; // days is index start form 0 and day start form 1.
}

bool comparePickerDateRange(
    const std::pair<PickerDate, PickerDate>& pair, const std::pair<PickerDate, PickerDate>& other)
{
    if (pair.first == other.first) {
        return pair.second < other.second;
    }
    return pair.first < other.first;
}

void PickerDate::SortAndMergeDisabledDateRange(std::vector<std::pair<PickerDate, PickerDate>>& disableDateRange)
{
    if (disableDateRange.empty()) {
        return;
    }
    std::sort(disableDateRange.begin(), disableDateRange.end(), comparePickerDateRange);
    std::vector<std::pair<PickerDate, PickerDate>> mergedRange;
    for (const auto& range : disableDateRange) {
        if (!mergedRange.empty() && (range.first.ToDays() - 1) <= mergedRange.back().second.ToDays()) {
            mergedRange.back().second =
                mergedRange.back().second < range.second ? range.second : mergedRange.back().second;
        } else {
            mergedRange.push_back(range);
        }
    }
    disableDateRange.clear();
    disableDateRange = mergedRange;
}

PickerDate PickerDate::GetAvailableNextDay(const PickerDate& date, const PickerDate& start, const PickerDate& end,
    std::vector<std::pair<PickerDate, PickerDate>>& disableDateRange, bool isAdd)
{
    PickerDate retDate = PickerDate(0, 0, 0);
    if ((end.GetYear() != 0 && end < date) || (start.GetYear() != 0 && date < start)) {
        return retDate;
    }
    if (isAdd) {
        for (const auto& range : disableDateRange) {
            if (range.first <= date && date <= range.second) {
                return end.GetYear() != 0 && end < range.second ? retDate : NextDay(range.second);
            }
        }
        return date;
    } else {
        for (const auto& range : disableDateRange) {
            if (range.first <= date && date <= range.second) {
                return start.GetYear() != 0 && range.first < start ? retDate : PrevDay(range.first);
            }
        }
        return date;
    }
}

PickerDate PickerDate::PrevDay(const PickerDate& dateObj)
{
    PickerDate date = dateObj;
    if (date.GetDay() > 1) {
        date.SetDay(date.GetDay() - 1);
        return date;
    }
    if (date.GetMonth() == 1) {
        date.SetMonth(MAX_MONTH);
        auto getYear = date.GetYear();
        date.SetYear(date.GetYear() == 1 ? MAX_YEAR : (getYear > 0 ? getYear - 1 : 0));
    } else {
        auto getMonth = date.GetMonth();
        date.SetMonth(getMonth > 0 ? getMonth - 1 : 0);
    }
    date.SetDay(PickerDate::GetMaxDay(date.GetYear(), date.GetMonth()));
    return date;
}

PickerDate PickerDate::NextDay(const PickerDate& dateObj)
{
    PickerDate date = dateObj;
    auto maxDay = PickerDate::GetMaxDay(date.GetYear(), date.GetMonth());
    if (maxDay > date.GetDay()) {
        date.SetDay(date.GetDay() + 1);
        return date;
    }
    date.SetDay(1);
    if (date.GetMonth() < MAX_MONTH) {
        date.SetMonth(date.GetMonth() + 1);
        return date;
    }
    date.SetMonth(1);
    date.SetYear(date.GetYear() == MAX_YEAR ? 1 : date.GetYear() + 1);
    return date;
}

PickerTime PickerTime::Current()
{
    PickerTime time;
    auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    auto local = std::localtime(&now);
    if (local == nullptr) {
        LOGE("get localtime failed.");
        return time;
    }
    time.SetHour(local->tm_hour);
    time.SetMinute(local->tm_min);
    time.SetSecond(local->tm_sec);
    return time;
}

std::string PickerTime::ToString(bool jsonFormat, bool hasSecond, int32_t status) const
{
    if (!jsonFormat) {
        if (!hasSecond) {
            // use char ':' to split.
            return std::to_string(hour_) + ":" + std::to_string(minute_);
        }
        // use char ':' to split.
        return std::to_string(hour_) + ":" + std::to_string(minute_) + ":" + std::to_string(second_);
    }

    if (!hasSecond) {
        // use json format chars
        return std::string("{\"hour\":") + std::to_string(hour_) + ",\"minute\":" + std::to_string(minute_) +
            ",\"status\":" + std::to_string(status) + "}";
    }
    // use json format chars
    return std::string("{\"hour\":") + std::to_string(hour_) + ",\"minute\":" + std::to_string(minute_) +
            ",\"second\":" + std::to_string(second_) + ",\"status\":" + std::to_string(status) + "}";
}

uint32_t PickerTime::ToMinutes() const
{
    constexpr static uint32_t minInHour = 60;
    return minute_ + hour_ * minInHour;
}

PickerDateTime PickerDateTime::Current()
{
    PickerDateTime dateTime;
    dateTime.SetDate(PickerDate::Current());
    dateTime.SetTime(PickerTime::Current());
    return dateTime;
}

std::string PickerDateTime::ToString(bool jsonFormat, int32_t status) const
{
    if (!jsonFormat) {
        return date_.ToString(jsonFormat);
    }

    return std::string("{\"year\":") + std::to_string(date_.GetYear()) +
           ",\"month\":" + std::to_string(date_.GetMonth()) +
           ",\"day\":" + std::to_string(date_.GetDay()) +
           ",\"hour\":" + std::to_string(time_.GetHour()) +
           ",\"minute\":" + std::to_string(time_.GetMinute()) +
           ",\"status\":" + std::to_string(status) + "}";
}

/*
 * Lunar information in 200 years from 1900.
 * <p>
 * | 0 - 11(bit) | 12 - 15(bit) |
 * month      leap month
 * If last 4bit is 1111 or 0000 means no leap month.
 * If the last 4bit in next data is 1111, the days of leap month is 30 days,
 * otherwise, the days of leap month is 29days.
 */
const uint16_t LunarCalculator::LUNAR_INFO[] = {
    0x6aa0, 0xbaa3, 0xab50,
    0x4bd8, 0x4ae0, 0xa570, 0x54d5, 0xd260, 0xd950, 0x5554, 0x56af,
    0x9ad0, 0x55d2, 0x4ae0, 0xa5b6, 0xa4d0, 0xd250, 0xd295, 0xb54f,
    0xd6a0, 0xada2, 0x95b0, 0x4977, 0x497f, 0xa4b0, 0xb4b5, 0x6a50,
    0x6d40, 0xab54, 0x2b6f, 0x9570, 0x52f2, 0x4970, 0x6566, 0xd4a0,
    0xea50, 0x6a95, 0x5adf, 0x2b60, 0x86e3, 0x92ef, 0xc8d7, 0xc95f,
    0xd4a0, 0xd8a6, 0xb55f, 0x56a0, 0xa5b4, 0x25df, 0x92d0, 0xd2b2,
    0xa950, 0xb557, 0x6ca0, 0xb550, 0x5355, 0x4daf, 0xa5b0, 0x4573,
    0x52bf, 0xa9a8, 0xe950, 0x6aa0, 0xaea6, 0xab50, 0x4b60, 0xaae4,
    0xa570, 0x5260, 0xf263, 0xd950, 0x5b57, 0x56a0, 0x96d0, 0x4dd5,
    0x4ad0, 0xa4d0, 0xd4d4, 0xd250, 0xd558, 0xb540, 0xb6a0, 0x95a6,
    0x95bf, 0x49b0, 0xa974, 0xa4b0, 0xb27a, 0x6a50, 0x6d40, 0xaf46,
    0xab60, 0x9570, 0x4af5, 0x4970, 0x64b0, 0x74a3, 0xea50, 0x6b58,
    0x5ac0, 0xab60, 0x96d5, 0x92e0, 0xc960, 0xd954, 0xd4a0, 0xda50,
    0x7552, 0x56a0, 0xabb7, 0x25d0, 0x92d0, 0xcab5, 0xa950, 0xb4a0,
    0xbaa4, 0xad50, 0x55d9, 0x4ba0, 0xa5b0, 0x5176, 0x52bf, 0xa930,
    0x7954, 0x6aa0, 0xad50, 0x5b52, 0x4b60, 0xa6e6, 0xa4e0, 0xd260,
    0xea65, 0xd530, 0x5aa0, 0x76a3, 0x96d0, 0x4afb, 0x4ad0, 0xa4d0,
    0xd0b6, 0xd25f, 0xd520, 0xdd45, 0xb5a0, 0x56d0, 0x55b2, 0x49b0,
    0xa577, 0xa4b0, 0xaa50, 0xb255, 0x6d2f, 0xada0, 0x4b63, 0x937f,
    0x49f8, 0x4970, 0x64b0, 0x68a6, 0xea5f, 0x6b20, 0xa6c4, 0xaaef,
    0x92e0, 0xd2e3, 0xc960, 0xd557, 0xd4a0, 0xda50, 0x5d55, 0x56a0,
    0xa6d0, 0x55d4, 0x52d0, 0xa9b8, 0xa950, 0xb4a0, 0xb6a6, 0xad50,
    0x55a0, 0xaba4, 0xa5b0, 0x52b0, 0xb273, 0x6930, 0x7337, 0x6aa0,
    0xad50, 0x4b55, 0x4b6f, 0xa570, 0x54e4, 0xd260, 0xe968, 0xd520,
    0xdaa0, 0x6aa6, 0x56df, 0x4ae0, 0xa9d4, 0xa4d0, 0xd150, 0xf252,
    0xd520, 0xdd45, 0xb5a0, 0x56d0
};

bool PickerStringFormatter::inited_ = false;
const std::string PickerStringFormatter::empty_;
std::vector<std::string> PickerStringFormatter::years_; // year from 1900 to 2100,count is 201
std::vector<std::string> PickerStringFormatter::solarMonths_; // solar month from 1 to 12,count is 12
std::vector<std::string> PickerStringFormatter::solarDays_; // solar day from 1 to 31, count is 31
std::vector<std::string> PickerStringFormatter::lunarMonths_; // lunar month from 1 to 24, count is 24
std::vector<std::string> PickerStringFormatter::lunarDays_; // lunar day from 1 to 30, count is 30
std::vector<std::string> PickerStringFormatter::tagOrder_; // order of year month day

void PickerStringFormatter::Init()
{
    if (inited_) {
        return;
    }
    years_.resize(201); // year from 1900 to 2100,count is 201
    solarMonths_.resize(12); // solar month from 1 to 12,count is 12
    solarDays_.resize(31); // solar day from 1 to 31, count is 31
    lunarMonths_.resize(24); // lunar month from 1 to 24, count is 24
    lunarDays_.resize(30); // lunar day from 1 to 30, count is 30
    // init year from 1900 to 2100
    for (uint32_t year = 1900; year <= 2100; ++year) {
        DateTime date;
        date.year = year;
        years_[year - 1900] = Localization::GetInstance()->FormatDateTime(date, "y"); // index start from 0
    }
    // init solar month from 1 to 12
    auto months = Localization::GetInstance()->GetMonths(true);
    for (uint32_t month = 1; month <= 12; ++month) {
        if (month - 1 < months.size()) {
            solarMonths_[month - 1] = months[month - 1];
            continue;
        }
        DateTime date;
        date.month = month - 1; // W3C's month start from 0 to 11
        solarMonths_[month - 1] = Localization::GetInstance()->FormatDateTime(date, "M"); // index start from 0
    }
    // init solar day from 1 to 31
    for (uint32_t day = 1; day <= 31; ++day) {
        DateTime date;
        date.day = day;
        solarDays_[day - 1] = Localization::GetInstance()->FormatDateTime(date, "d"); // index start from 0
    }
    // init lunar month from 1 to 24 which is 1th, 2th, ... leap 1th, leap 2th ...
    for (uint32_t index = 1; index <= 24; ++index) {
        uint32_t month = (index > 12 ? index - 12 : index);
        bool isLeap = (index > 12);
        lunarMonths_[index - 1] = Localization::GetInstance()->GetLunarMonth(month, isLeap); // index start from 0
    }
    // init lunar day from 1 to 30
    for (uint32_t day = 1; day <= 30; ++day) {
        lunarDays_[day - 1] = Localization::GetInstance()->GetLunarDay(day); // index start from 0
    }
    inited_ = true;
    Localization::GetInstance()->SetOnChange([]() { PickerStringFormatter::inited_ = false; });
}

const std::string& PickerStringFormatter::GetYear(uint32_t year)
{
    Init();
    if (!(1900 <= year && year <= 2100)) { // year in [1900,2100]
        return empty_;
    }
    return years_[year - 1900]; // index in [0, 200]
}

const std::string& PickerStringFormatter::GetSolarMonth(uint32_t month)
{
    Init();
    if (!(1 <= month && month <= 12)) { // solar month in [1,12]
        return empty_;
    }
    return solarMonths_[month - 1]; // index in [0,11]
}

const std::string& PickerStringFormatter::GetSolarDay(uint32_t day)
{
    Init();
    if (!(1 <= day && day <= 31)) { // solar day in [1,31]
        return empty_;
    }
    return solarDays_[day - 1]; // index in [0,30]
}

const std::string& PickerStringFormatter::GetLunarMonth(uint32_t month, bool isLeap)
{
    Init();
    uint32_t index = (isLeap ? month + 12 : month); // leap month is behind 12 index
    if (!(1 <= index && index <= 24)) { // lunar month need in [1,24]
        return empty_;
    }
    return lunarMonths_[index - 1]; // index in [0,23]
}

const std::string& PickerStringFormatter::GetLunarDay(uint32_t day)
{
    Init();
    if (!(1 <= day && day <= 30)) { // lunar day need in [1,30]
        return empty_;
    }
    return lunarDays_[day - 1]; // index in [0,29]
}

const std::vector<std::string>& PickerStringFormatter::GetTagOrder()
{
    tagOrder_.clear();
    Localization::GetInstance()->GetDateColumnFormatOrder(tagOrder_);
    return tagOrder_;
}

} // namespace OHOS::Ace
