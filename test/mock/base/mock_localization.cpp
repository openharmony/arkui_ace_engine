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

#include "base/i18n/localization.h"

namespace OHOS::Ace {
namespace {
constexpr int32_t DAY_COUNTS_OF_WEEK = 7;
constexpr int32_t MONTH_COUNTS_OF_YEAR = 12;
} // namespace

struct LocaleProxy final {};
Localization::~Localization() = default;

void Localization::SetLocaleImpl(const std::string& language, const std::string& countryOrRegion,
    const std::string& script, const std::string& selectLanguage, const std::string& keywordsAndValues)
{
    languageTag_ = language;
}

std::string Localization::GetFontLocale()
{
    return fontLocale_;
}

std::shared_ptr<Localization> Localization::GetInstance()
{
    static auto instance = std::make_shared<Localization>();
    return instance;
}

bool Localization::GetDateOrder(std::vector<std::string>& outOrder)
{
    outOrder.clear();
    if (languageTag_ == "ug") {
        outOrder.emplace_back("month");
        outOrder.emplace_back("day");
        outOrder.emplace_back("year");
    } else if (languageTag_ == "zh") {
        outOrder.emplace_back("year");
        outOrder.emplace_back("month");
        outOrder.emplace_back("day");
    } else if (languageTag_ == "false") {
        return false;
    }
    return true;
}

std::string Localization::FormatDuration(uint32_t duration, const std::string& format)
{
    return "08:00:00";
}

const std::string Localization::FormatDateTime(DateTime dateTime, const std::string& format)
{
    return "08:00:00";
}

const std::string Localization::FormatDateTime(DateTime dateTime, DateTimeStyle dateStyle, DateTimeStyle timeStyle)
{
    return "08:00:00";
}

std::string Localization::GetEntryLetters(const std::string& lettersIndex)
{
    return "";
}

std::string Localization::GetErrorDescription(const std::string& errorIndex)
{
    return "";
}

const std::string Localization::FormatDuration(uint32_t duration, bool needShowHour)
{
    return "08:00:00";
}

std::vector<std::string> Localization::GetMonths(bool isShortType, const std::string& calendarType)
{
    std::vector<std::string> months;
    for (int32_t i = 0; i < MONTH_COUNTS_OF_YEAR; i++) {
        months.push_back(std::to_string(i));
    }
    return months;
}

std::string Localization::GetLanguage()
{
    return "Chinese";
}

std::string Localization::GetLunarMonth(uint32_t month, bool isLeapMonth)
{
    return "";
}

std::string Localization::GetLunarDay(uint32_t dayOfMonth)
{
    return "";
}

LunarDate Localization::GetLunarDate(Date date)
{
    LunarDate dateRet;
    dateRet.year = date.year;
    dateRet.month = date.month;
    dateRet.day = date.day;
    return dateRet;
}

std::vector<std::string> Localization::GetAmPmStrings()
{
    std::vector<std::string> amPms;
    return amPms;
}

bool Localization::GetHourFormat(bool& isAmPm, bool& hasZero)
{
    return false;
}

// Mock get weekdays, 7 days in a week.
std::vector<std::string> Localization::GetWeekdays(bool isShortType)
{
    std::vector<std::string> weekdays;
    for (int32_t i = 0; i < DAY_COUNTS_OF_WEEK; i++) {
        weekdays.push_back(std::to_string(i));
    }
    return weekdays;
}

std::string Localization::NumberFormat(double number)
{
    return std::to_string(number);
}
} // namespace OHOS::Ace
