/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#include "core/components/calendar/calendar_data_adapter.h"

#include <fstream>
#include <streambuf>

#include "base/i18n/localization.h"
#include "base/json/json_util.h"
#include "base/log/log.h"
#include "base/utils/date_util.h"
#include "base/utils/string_utils.h"
#include "core/common/platform_bridge.h"

namespace OHOS::Ace {
namespace {

constexpr int32_t CALENDAR_DAYS_FIVE_ROW_COUNT = 35;
constexpr int32_t CALENDAR_DAYS_SIX_ROW_COUNT = 42;

bool ParseDayNumberProp(const std::unique_ptr<JsonValue>& item, const std::string& key, int32_t& value)
{
    if (!item) {
        LOGE("item is nullptr");
        return false;
    }
    if (!item->Contains(key)) {
        LOGE("parse day number error, not find key:%{public}s", key.c_str());
        return false;
    }

    auto dayValue = item->GetValue(key);
    if (dayValue->IsNumber()) {
        value = dayValue->GetInt();
        return true;
    } else {
        LOGW("parse day number type error");
        return false;
    }
}

} // namespace

std::string CalendarDataAdapter::cachePath_;

CalendarDataAdapter::CalendarDataAdapter(
    const CalendarDataAdapterAction& dataAdapterAction, const WeakPtr<PipelineContext>& pipelineContext)
    : dataAdapterAction_(dataAdapterAction), pipelineContext_(pipelineContext)
{
    Date currentDate = Date::Current();
    today_.day = currentDate.day;
    today_.month.year = currentDate.year;
    today_.month.month = currentDate.month - 1;
}

bool CalendarDataAdapter::ParseData(int32_t indexOfContainer, const std::string& source, CalendarDaysOfMonth& result)
{
    static const std::string daysKey = "days";
    auto sourceJsonValue = JsonUtil::ParseJsonString(source);
    calendarCache_[indexOfContainer].clear();
    if (!sourceJsonValue || !sourceJsonValue->Contains(daysKey)) {
        LOGE("not find days");
        return false;
    }

    auto daysValue = sourceJsonValue->GetValue(daysKey);
    if (!daysValue || !daysValue->IsArray() || daysValue->GetArraySize() <= 0) {
        LOGE("calendar days not array");
        return false;
    }

    int daySize = daysValue->GetArraySize();
    if (daySize != CALENDAR_DAYS_FIVE_ROW_COUNT && daySize != CALENDAR_DAYS_SIX_ROW_COUNT) {
        LOGE("calendar days size cannot support, size = %{public}d", daySize);
        return false;
    }

    for (int32_t index = 0; index < daySize; ++index) {
        auto item = daysValue->GetArrayItem(index);
        if (!item) {
            continue;
        }
        CalendarDay dayInfo;
        if (!ParseDayNumberProp(item, CalendarDay::INDEX, dayInfo.index)) {
            continue;
        }
        if (!ParseDayNumberProp(item, CalendarDay::DAY, dayInfo.day)) {
            continue;
        }
        if (!ParseDayNumberProp(item, CalendarDay::MONTH, dayInfo.month.month)) {
            continue;
        }
        if (!ParseDayNumberProp(item, CalendarDay::YEAR, dayInfo.month.year)) {
            continue;
        }
        if (dayInfo.day == CALENDAR_FIRST_DAY_NUM_OF_MONTH && result.firstDayIndex == CALENDAR_INVALID) {
            result.firstDayIndex = dayInfo.index;
        }

        if (dayInfo.month == result.month) {
            result.lastDayIndex = dayInfo.index;
        }

        // mark weekend
        SetOffDays(dayInfo);
        // Mark today.
        dayInfo.today = dayInfo.month == today_.month && dayInfo.day == today_.day;
        if (dayInfo.today) {
            result.today = dayInfo.index;
        }
        // Get lunarDay information.
        dayInfo.lunarMonth = item->GetString(CalendarDay::LUNAR_MONTH, "");
        dayInfo.lunarDay = item->GetString(CalendarDay::LUNAR_DAY, "");
        // Get mark information.
        dayInfo.dayMark = item->GetString(CalendarDay::DAY_MARK, "");
        dayInfo.dayMarkValue = item->GetString(CalendarDay::DAY_MARK_VALUE, "");
        result.days.push_back(dayInfo);
        calendarCache_[indexOfContainer].push_back(item->ToString());
    }
    dayOfMonthCache_[indexOfContainer] = result;
    return true;
}

void CalendarDataAdapter::RequestData(const CalendarDataRequest& request)
{
    auto context = pipelineContext_.Upgrade();
    auto weak = AceType::WeakClaim(this);
    if (!context) {
        return;
    }
    if (cardCalendar_) {
        indexMap_[request.indexOfContainer] = request.month;
        auto json = JsonUtil::Create(true);
        json->Put("month", request.month.month);
        json->Put("year", request.month.year);
        json->Put("currentMonth", currentMonth_.month);
        json->Put("currentYear", currentMonth_.year);
        if (requestDataEvent_) {
            requestDataEvent_(json->ToString());
        }
        auto iter = monthCache_.find(request.month);
        if (iter != monthCache_.end()) {
            auto monthDataJson = JsonUtil::ParseJsonString(monthCache_[iter->first]);
            ParseMonthData(monthDataJson);
        }
        context->GetTaskExecutor()->PostTask(
            [weak]() {
                auto dataAdapter = weak.Upgrade();
                if (!dataAdapter) {
                    LOGW("dataAdapter is null");
                    return;
                }
                dataAdapter->RequestNextData();
            },
            TaskExecutor::TaskType::UI);
    } else {
        GetCacheData(request);
        context->GetMessageBridge()->SendMessage(dataAdapterAction_.GetAction(request.month.year, request.month.month),
            [weak, request](const std::string& result) {
                auto dataAdapter = weak.Upgrade();
                if (!dataAdapter) {
                    LOGE("date adapter is nullptr");
                    return;
                }
                dataAdapter->HandleDataRequestResult(request, result);
                dataAdapter->SaveCacheData(request, result);
            });
    }
}

bool CalendarDataAdapter::GetCacheData(const CalendarDataRequest& request)
{
    std::string filePath = cachePath_;
    filePath.append("/")
        .append(std::to_string(request.month.year))
        .append(std::to_string(request.month.month))
        .append(Localization::GetInstance()->GetLanguageTag());

    std::ifstream file(filePath, std::ifstream::in | std::ifstream::binary);
    bool isDataCached = false;
    if (file.is_open()) {
        std::string result((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
        if (!result.empty()) {
            CalendarDaysOfMonth daysOfMonth;
            daysOfMonth.month = request.month;
            if (request.indexOfContainer >= 0 && request.indexOfContainer < CALENDAR_CACHE_PAGE) {
                if (!ParseData(request.indexOfContainer, result, daysOfMonth)) {
                    return false;
                }
                NotifyDataChanged(daysOfMonth, request.indexOfContainer);
            }
        }
        isDataCached = true;
    }
    return isDataCached;
}

void CalendarDataAdapter::SaveCacheData(const CalendarDataRequest& request, const std::string& result)
{
    auto context = pipelineContext_.Upgrade();
    auto bkTaskExecutor = SingleTaskExecutor::Make(context->GetTaskExecutor(), TaskExecutor::TaskType::BACKGROUND);

    bkTaskExecutor.PostTask([request, result]() {
        std::string url = cachePath_;
        url.append("/")
            .append(std::to_string(request.month.year))
            .append(std::to_string(request.month.month))
            .append(Localization::GetInstance()->GetLanguageTag());
        std::ofstream outFile(url, std::fstream::out);
        if (!outFile) {
            LOGE("the file open failed");
            return;
        }
        outFile.write(reinterpret_cast<const char*>(result.c_str()), result.size());
    });
}

void CalendarDataAdapter::ParseCardCalendarData(const std::string& source)
{
    if (source.empty()) {
        return;
    }
    auto sourceJson = JsonUtil::ParseJsonString(source);
    if (!sourceJson->IsValid() || !sourceJson->IsArray()) {
        return;
    }

    auto child = sourceJson->GetChild();
    while (child->IsValid()) {
        ParseMonthData(child);
        child = child->GetNext();
    }
}

void CalendarDataAdapter::UpdateCardCalendarAttr(const CardCalendarAttr& attr)
{
    showLunar_ = attr.showLunar;
    startDayOfWeek_ = attr.startDayOfWeek;
    cardCalendar_ = attr.cardCalendar;
    offDays_ = attr.offDays;
    SetRequestDataEvent(attr.requestData);
    for (const auto& listen : allListeners_) {
        listen->UpdateCardCalendarAttr(attr);
    }
}

void CalendarDataAdapter::ParseMonthData(const std::unique_ptr<JsonValue>& monthData)
{
    CalendarMonth calendarMonth;
    calendarMonth.month = monthData->GetInt("month", -1);
    calendarMonth.year = monthData->GetInt("year", -1);
    monthCache_[calendarMonth] = monthData->ToString();

    int32_t indexOfContainer;
    for (const auto& index : indexMap_) {
        if (index.second == calendarMonth) {
            indexOfContainer = index.first;
        }
    }
    static const int32_t miniIndex = 0;
    static const int32_t maxIndex = 2;
    if (indexOfContainer < miniIndex || indexOfContainer > maxIndex) {
        return;
    }
    auto data = monthData->GetValue("data");
    if (!data) {
        return;
    }
    auto child = data->GetChild();
    CalendarDaysOfMonth result;
    result.month = calendarMonth;
    while (child->IsValid()) {
        CalendarDay dayInfo;
        dayInfo.day = child->GetInt("day");
        dayInfo.index = child->GetInt("index");
        dayInfo.month.month = child->GetInt("month");
        dayInfo.month.year = child->GetInt("year");
        dayInfo.lunarDay = child->GetString("lunarDay", "");
        dayInfo.dayMark = child->GetString("dayMark", "");
        dayInfo.dayMarkValue = child->GetString("dayMarkValue", "");
        dayInfo.isFirstOfLunar = child->GetBool("isFirstOfLunar", false);
        dayInfo.hasSchedule = child->GetBool("hasSchedule", false);
        dayInfo.markLunarDay = child->GetBool("markLunarDay", false);
        SetOffDays(dayInfo);
        result.days.push_back(dayInfo);
        child = child->GetNext();
    }
    dayOfMonthCache_[indexOfContainer] = result;
    NotifyDataChanged(result, indexOfContainer);
}

void CalendarDataAdapter::SetOffDays(CalendarDay& dayInfo)
{
    auto weekday = Date::CalculateWeekDay(dayInfo.month.year, dayInfo.month.month + 1, dayInfo.day);
    std::vector<std::string> days;
    StringUtils::StringSpliter(offDays_, ',', days);
    bool setOffDay = true;
    for (const auto& day : days) {
        auto num = StringUtils::StringToInt(day);
        if (num < 0 || num > 6) {
            setOffDay = false;
            break;
        }
        if (num == weekday) {
            dayInfo.weekend = true;
            return;
        }
    }
    if (!setOffDay) {
        if (weekday == 5 || weekday == 6) { // set default weekend
            dayInfo.weekend = true;
        }
    }
}

} // namespace OHOS::Ace
