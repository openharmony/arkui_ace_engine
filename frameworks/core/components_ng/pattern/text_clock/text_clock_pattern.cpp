/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/text_clock/text_clock_pattern.h"

#include <ctime>
#include <string>
#include <sys/time.h>

#include "base/i18n/localization.h"
#include "base/utils/time_util.h"
#include "base/utils/utils.h"
#include "core/common/container.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/property/property.h"
#include "core/pipeline/base/render_context.h"

namespace OHOS::Ace::NG {
namespace {
#ifdef WINDOWS_PLATFORM
constexpr int32_t TOTAL_MINUTE_OF_HOUR = 60;
#endif
constexpr int32_t TOTAL_SECONDS_OF_HOUR = 60 * 60;
constexpr int32_t BASE_YEAR = 1900;
constexpr int32_t INTERVAL_OF_U_SECOND = 1000000;
constexpr int32_t MICROSECONDS_OF_MILLISECOND = 1000;
const std::string DEFAULT_FORMAT = "hms";
constexpr char TEXTCLOCK_WEEK[] = "textclock.week";
constexpr char TEXTCLOCK_YEAR[] = "textclock.year";
constexpr char TEXTCLOCK_MONTH[] = "textclock.month";
constexpr char TEXTCLOCK_DAY[] = "textclock.day";

enum class TextClockElementIndex {
    CUR_YEAR_INDEX = 0,
    CUR_MONTH_INDEX = 1,
    CUR_DAY_INDEX = 2,
    CUR_HOUR_INDEX = 3,
    CUR_MINUTE_INDEX = 4,
    CUR_SECOND_INDEX = 5,
    CUR_MILLISECOND_INDEX = 6,
    CUR_AMPM_INDEX = 7,
    CUR_WEEK_INDEX = 8,
};
enum class TextClockElementLen {
    ONLY_ONE_DATE_ELEMENT = 1,
    YEAR_FORMAT_MIN_LEN = 2,
    MON_DAY_FORMAT_MAX_LEN = 2,
    MILLISECOND_FORMAT_LEN = 3,
    YEAR_WEEK_FORMAT_MAX_LEN = 4,
};
enum class TextClockWeekType {
    WEEK_FULL_TYPE = 1,
    WEEK_SHORT_TYPE = 2,
};

std::unordered_map<char, TextClockElementIndex> curDateTimeMap = { { 'y', TextClockElementIndex::CUR_YEAR_INDEX },
    { 'M', TextClockElementIndex::CUR_MONTH_INDEX }, { 'd', TextClockElementIndex::CUR_DAY_INDEX },
    { 'H', TextClockElementIndex::CUR_HOUR_INDEX }, { 'h', TextClockElementIndex::CUR_HOUR_INDEX },
    { 'm', TextClockElementIndex::CUR_MINUTE_INDEX }, { 's', TextClockElementIndex::CUR_SECOND_INDEX },
    { 'S', TextClockElementIndex::CUR_MILLISECOND_INDEX }, { 'a', TextClockElementIndex::CUR_AMPM_INDEX },
    { 'E', TextClockElementIndex::CUR_WEEK_INDEX } };

int32_t GetSystemTimeZone()
{
#ifndef WINDOWS_PLATFORM
    return timezone / TOTAL_SECONDS_OF_HOUR;
#else
    struct timeval currentTime;
    struct timezone timeZone;
    gettimeofday(&currentTime, &timeZone);
    int32_t timeZoneHour = timeZone.tz_minuteswest / TOTAL_MINUTE_OF_HOUR;
    return timeZoneHour;
#endif
}

/**
 *  The East time zone is usually represented by a positive number
 *  and the west by a negative number.
 */
int32_t GetGMT(int32_t hoursWest)
{
    return -hoursWest;
}
} // namespace

TextClockPattern::TextClockPattern()
{
    textClockController_ = MakeRefPtr<TextClockController>();
}

void TextClockPattern::OnAttachToFrameNode()
{
    InitTextClockController();
    InitUpdateTimeTextCallBack();
}

void TextClockPattern::UpdateTextLayoutProperty(
    RefPtr<TextClockLayoutProperty>& layoutProperty, RefPtr<TextLayoutProperty>& textLayoutProperty)
{
    if (layoutProperty->GetFontSize().has_value()) {
        textLayoutProperty->UpdateFontSize(layoutProperty->GetFontSize().value());
    }
    if (layoutProperty->GetFontWeight().has_value()) {
        textLayoutProperty->UpdateFontWeight(layoutProperty->GetFontWeight().value());
    }
    if (layoutProperty->GetTextColor().has_value()) {
        textLayoutProperty->UpdateTextColor(layoutProperty->GetTextColor().value());
    }
    if (layoutProperty->GetFontFamily().has_value()) {
        textLayoutProperty->UpdateFontFamily(layoutProperty->GetFontFamily().value());
    }
    if (layoutProperty->GetItalicFontStyle().has_value()) {
        textLayoutProperty->UpdateItalicFontStyle(layoutProperty->GetItalicFontStyle().value());
    }
}

void TextClockPattern::OnModifyDone()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto textNode = GetTextNode();
    CHECK_NULL_VOID(textNode);
    auto textLayoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(textLayoutProperty);
    auto textClockProperty = host->GetLayoutProperty<TextClockLayoutProperty>();
    CHECK_NULL_VOID(textClockProperty);
    textLayoutProperty->UpdateTextOverflow(TextOverflow::NONE);
    UpdateTextLayoutProperty(textClockProperty, textLayoutProperty);
    hourWest_ = GetHoursWest();
    UpdateTimeText();
}

void TextClockPattern::InitTextClockController()
{
    CHECK_NULL_VOID(textClockController_);
    if (textClockController_->HasInitialized()) {
        return;
    }
    textClockController_->OnStart([wp = WeakClaim(this)]() {
        auto textClock = wp.Upgrade();
        if (textClock) {
            textClock->isStart_ = true;
            textClock->UpdateTimeText();
        }
    });
    textClockController_->OnStop([wp = WeakClaim(this)]() {
        auto textClock = wp.Upgrade();
        if (textClock) {
            textClock->isStart_ = false;
        }
    });
}

void TextClockPattern::InitUpdateTimeTextCallBack()
{
    if (!timeCallback_) {
        timeCallback_ = ([wp = WeakClaim(this)]() {
            auto textClock = wp.Upgrade();
            if (textClock) {
                textClock->UpdateTimeText();
            } else {
                LOGE("textClock is empty.");
            }
        });
    }
}

void TextClockPattern::UpdateTimeText()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto textNode = GetTextNode();
    CHECK_NULL_VOID(textNode);
    auto textLayoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(textLayoutProperty);

    std::string currentTime = GetCurrentFormatDateTime();
    if (currentTime.empty()) {
        LOGE("Get current format date time failed.");
        return;
    }
    textLayoutProperty->UpdateContent(currentTime); // update time text.
    auto textContext = textNode->GetRenderContext();
    CHECK_NULL_VOID(textContext);
    textContext->SetClipToFrame(false);
    textContext->UpdateClipEdge(false);
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    textNode->MarkModifyDone();
    if (isStart_) {
        RequestUpdateForNextSecond();
    }
}

void TextClockPattern::RequestUpdateForNextSecond()
{
    struct timeval currentTime {};
    gettimeofday(&currentTime, nullptr);
    /**
     * 1 second = 1000 millisecond = 1000000 microsecond.
     * Millisecond is abbreviated as msec. Microsecond is abbreviated as usec.
     * unit of [delayTime] is msec, unit of [tv_usec] is usec
     * when [tv_usec] is 000100, (INTERVAL_OF_U_SECOND - timeUsec) / MICROSECONDS_OF_MILLISECOND = 999 msec
     * which will cause the delay task still arriving in current second, because 999000 + 000100 = 999100 < 1 second
     * so add an additional millisecond to modify the loss of precision during division
     */
    int32_t delayTime =
        (INTERVAL_OF_U_SECOND - static_cast<int32_t>(currentTime.tv_usec)) / MICROSECONDS_OF_MILLISECOND +
        1; // millisecond

    auto context = UINode::GetContext();
    CHECK_NULL_VOID(context);
    context->GetTaskExecutor()->PostDelayedTask(
        [wp = WeakClaim(this)] {
            auto textClock = wp.Upgrade();
            CHECK_NULL_VOID(textClock);
            if (!textClock->isStart_) {
                return;
            }
            textClock->UpdateTimeTextCallBack();
        },
        TaskExecutor::TaskType::UI, delayTime);
}

void TextClockPattern::UpdateTimeTextCallBack()
{
    if (timeCallback_) {
        timeCallback_();
    }
    FireChangeEvent();
}

std::string TextClockPattern::GetCurrentFormatDateTime()
{
    auto offset = GetGMT(hourWest_);
    time_t current = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    auto utcTime = std::gmtime(&current); // Convert to UTC time.
    auto utcTimeSecond = std::mktime(utcTime);
    // UTC time(timezone is GMT 0) add time zone offset.
    time_t targetTimeZoneTime = utcTimeSecond + offset * TOTAL_SECONDS_OF_HOUR;
    auto* timeZoneTime = std::localtime(&targetTimeZoneTime);
    CHECK_NULL_RETURN(timeZoneTime, "");
    DateTime dateTime; // This is for i18n date time.
    dateTime.year = timeZoneTime->tm_year + BASE_YEAR;
    dateTime.month = timeZoneTime->tm_mon;
    dateTime.day = timeZoneTime->tm_mday;
    dateTime.hour = timeZoneTime->tm_hour;
    dateTime.minute = timeZoneTime->tm_min;
    dateTime.second = timeZoneTime->tm_sec;
    if (Container::LessThanAPIVersion(PlatformVersion::VERSION_ELEVEN)) {
        std::string time = Localization::GetInstance()->FormatDateTime(dateTime, GetFormat());
        return time;
    }
    dateTime.week = timeZoneTime->tm_wday;       // 0-6
    std::string dateTimeFormat = DEFAULT_FORMAT; // the format to get datetime value from the thirdlib
    int32_t weekType = 0;                        // 0:no week, 1:full type week, 2:short type week
    bool is24H = false;                          // false: 12H  true:24H
    int32_t month = 0;                           // 0:no month, 1:M, 2:MM
    int32_t day = 0;                             // 0:no day, 1:d, 2:dd
    bool isMilliSecond = false;                  // false:centisecond true:millisecond
    std::vector<std::string> inputFormatSplitter = ParseInputFormat(is24H, weekType, month, day, isMilliSecond);
    dateTimeFormat = "yyyy";
    dateTimeFormat += (month == 1) ? "M" : "MM";
    dateTimeFormat += (day == 1) ? "d" : "dd";
    dateTimeFormat += is24H ? "HH" : "hh";
    dateTimeFormat += "mmss";
    dateTimeFormat += isMilliSecond ? "SSS" : "SS";
    std::string dateTimeValue = Localization::GetInstance()->FormatDateTime(dateTime, dateTimeFormat);
    std::string tempdateTimeValue = dateTimeValue;
    std::string strAmPm = GetAmPm(tempdateTimeValue);
    if (!strAmPm.empty()) {
        tempdateTimeValue.replace(tempdateTimeValue.find(strAmPm), strAmPm.length(), "");
    }
    std::vector<std::string> curDateTime = ParseDateTimeValue(tempdateTimeValue);
    curDateTime[(int32_t)(TextClockElementIndex::CUR_AMPM_INDEX)] = strAmPm;
    if (weekType > 0) {
        curDateTime[(int32_t)(TextClockElementIndex::CUR_WEEK_INDEX)] =
            GetWeek((bool)(weekType - 1), timeZoneTime->tm_wday);
    }
    std::string outputDateTime = SpliceDateTime(curDateTime, inputFormatSplitter);
    outputDateTime =
        ((curDateTime[(int32_t)(TextClockElementIndex::CUR_YEAR_INDEX)] == "1900") || (outputDateTime == ""))
            ? dateTimeValue : outputDateTime;
    return outputDateTime;
}

std::vector<std::string> TextClockPattern::ParseInputFormat(
    bool& is24H, int32_t& weekType, int32_t& month, int32_t& day, bool& isMilliSecond)
{
    std::string inputFormat = (GetFormat() == DEFAULT_FORMAT) ? "aa h:m:s" : GetFormat();
    std::vector<std::string> formatSplitter;
    auto i = 0;
    auto j = 0;
    auto len = inputFormat.length();
    std::string tempFormat = "";
    auto milliSecond = 0;
    auto week = 0;
    for (tempFormat = inputFormat[i]; i < (int32_t)len; i++) {
        switch (inputFormat[i]) {
            case 'H':
                is24H = true;
                break;
            case 'S':
                milliSecond++;
                break;
            case 'E':
                week++;
                break;
            case 'M':
                month++;
                break;
            case 'd':
                day++;
                break;
            default:
                break;
        }
        if (inputFormat[i] == inputFormat[i + 1]) {
            tempFormat += inputFormat[i + 1]; // the same element format
        } else {
            formatSplitter.push_back(tempFormat);
            tempFormat = "";
            tempFormat += inputFormat[i + 1]; // the next element format
            j++;
        }
    }
    if (milliSecond >= (int32_t)(TextClockElementLen::MILLISECOND_FORMAT_LEN)) { // SSS
        isMilliSecond = true;
    }
    if (week >= (int32_t)(TextClockElementLen::YEAR_WEEK_FORMAT_MAX_LEN)) { // EEEE
        weekType = (int32_t)(TextClockWeekType::WEEK_FULL_TYPE);
    }
    if ((week > 0) && (week < (int32_t)(TextClockElementLen::YEAR_WEEK_FORMAT_MAX_LEN))) { // E EE EEE
        weekType = (int32_t)(TextClockWeekType::WEEK_SHORT_TYPE);
    }
    return formatSplitter;
}

std::vector<std::string> TextClockPattern::ParseDateTimeValue(const std::string& strDateTimeValue)
{
    std::string dateTimeValue = strDateTimeValue;
    std::vector<std::string> curDateTime = { "1900", "0", "1", "0", "0", "0", "0", "", "0" };
    auto dateFirstSplit = dateTimeValue.find('/');
    auto dateSecondSplit = dateTimeValue.find('/', dateFirstSplit + 1);
    auto dateThirdSplit =
        (dateTimeValue.find(',') != std::string::npos) ? dateTimeValue.find(',') : dateTimeValue.find(' ');
    if ((dateFirstSplit != std::string::npos) && (dateSecondSplit != std::string::npos) &&
        (dateThirdSplit != std::string::npos) && (dateSecondSplit > dateFirstSplit) &&
        (dateThirdSplit > dateSecondSplit)) {
        std::string dateFirst = dateTimeValue.substr(0, dateFirstSplit);
        std::string dateSecond = dateTimeValue.substr(dateFirstSplit + 1, dateSecondSplit - dateFirstSplit - 1);
        std::string dateThird = dateTimeValue.substr(dateSecondSplit + 1, dateThirdSplit - dateSecondSplit - 1);
        if (dateFirstSplit > (int32_t)(TextClockElementLen::MON_DAY_FORMAT_MAX_LEN)) {
            curDateTime[(int32_t)(TextClockElementIndex::CUR_YEAR_INDEX)] = dateFirst;
            curDateTime[(int32_t)(TextClockElementIndex::CUR_MONTH_INDEX)] = dateSecond;
            curDateTime[(int32_t)(TextClockElementIndex::CUR_DAY_INDEX)] = dateThird;
        } else {
            curDateTime[(int32_t)(TextClockElementIndex::CUR_YEAR_INDEX)] = dateThird;
            curDateTime[(int32_t)(TextClockElementIndex::CUR_MONTH_INDEX)] = dateFirst;
            curDateTime[(int32_t)(TextClockElementIndex::CUR_DAY_INDEX)] = dateSecond;
        }
        dateTimeValue.erase(0, dateThirdSplit);
        if (dateTimeValue.find(" ") != std::string::npos) {
            dateTimeValue.replace(dateTimeValue.find(" "), 1, "");
        }
        if (dateTimeValue.find(",") != std::string::npos) {
            dateTimeValue.replace(dateTimeValue.find(","), 1, "");
        }
        auto timeFirstSplit = dateTimeValue.find(':');
        auto timeSecondSplit = dateTimeValue.find(':', timeFirstSplit + 1);
        auto timeThirdSplit =
            (dateTimeValue.find('.') != std::string::npos) ? dateTimeValue.find('.') : (dateTimeValue.length() - 1);
        if ((timeFirstSplit != std::string::npos) && (timeSecondSplit != std::string::npos) &&
            (timeThirdSplit != std::string::npos) && (timeSecondSplit > timeFirstSplit) &&
            (timeThirdSplit > timeSecondSplit)) {
            curDateTime[(int32_t)(TextClockElementIndex::CUR_HOUR_INDEX)] = dateTimeValue.substr(0, timeFirstSplit);
            curDateTime[(int32_t)(TextClockElementIndex::CUR_MINUTE_INDEX)] =
                dateTimeValue.substr(timeFirstSplit + 1, timeSecondSplit - timeFirstSplit - 1);
            curDateTime[(int32_t)(TextClockElementIndex::CUR_SECOND_INDEX)] =
                dateTimeValue.substr(timeSecondSplit + 1, timeThirdSplit - timeSecondSplit - 1);
            curDateTime[(int32_t)(TextClockElementIndex::CUR_MILLISECOND_INDEX)] =
                (timeThirdSplit < (dateTimeValue.length() - 1))
                    ? dateTimeValue.substr(timeThirdSplit + 1, (dateTimeValue.length() - 1 - timeThirdSplit))
                    : "";
        }
    }
    return curDateTime;
}

std::string TextClockPattern::GetAmPm(const std::string& dateTimeValue)
{
    std::string language = Localization::GetInstance()->GetLanguage();
    std::string curAmPm = "";
    if (dateTimeValue != "") {
        if ((strcmp(language.c_str(), "zh") == 0)) {
            // getChinese
            auto space = dateTimeValue.find(" ");
            auto colon = dateTimeValue.find(":");
            if ((space != std::string::npos) && (colon != std::string::npos) && (space < colon)) {
                auto letterNum = GetDigitNumber(dateTimeValue.substr(space, colon - space));
                curAmPm = dateTimeValue.substr(space + 1, colon - letterNum - space - 1);
            }
        } else {
            // getLetter
            curAmPm += Abstract(dateTimeValue, true);
        }
    }
    return curAmPm;
}

std::string TextClockPattern::Abstract(const std::string& strSource, const bool& abstractItem)
{
    std::string strTemp = "";
    for (char str : strSource) {
        if (abstractItem ? (std::isalpha(str)) : !(std::isalpha(str))) {
            strTemp += str;
        }
    }
    return strTemp;
}

int32_t TextClockPattern::GetDigitNumber(const std::string& strSource)
{
    auto letterNum = 0;
    for (char str : strSource) {
        if (std::isdigit(str)) {
            letterNum++;
        }
    }
    return letterNum;
}

std::string TextClockPattern::GetWeek(const bool& isShortType, const int32_t& week)
{
    std::string language = Localization::GetInstance()->GetLanguage();
    std::vector<std::string> weeks = Localization::GetInstance()->GetWeekdays(isShortType);
    std::string curWeek = "";

    if (week < (int32_t)weeks.size()) {
        if ((strcmp(language.c_str(), "zh") == 0) && isShortType) {
            // chinese E/EE/EEE
            curWeek = Localization::GetInstance()->GetEntryLetters(TEXTCLOCK_WEEK) + weeks[week];
        } else {
            curWeek = weeks[week];
        }
    }
    return curWeek;
}

std::string TextClockPattern::SpliceDateTime(
    const std::vector<std::string>& curDateTime, const std::vector<std::string>& inputFormatSplitter)
{
    std::string format = "";
    std::string tempFormat = "";
    bool oneElement = false;
    if (((int32_t)(inputFormatSplitter.size()) == (int32_t)TextClockElementLen::ONLY_ONE_DATE_ELEMENT) &&
        ((strcmp(Localization::GetInstance()->GetLanguage().c_str(), "zh") == 0))) {
        oneElement = true;
    }
    for (auto i = 0; i < (int32_t)(inputFormatSplitter.size()); i++) {
        std::unordered_map<char, TextClockElementIndex>::iterator it = curDateTimeMap.begin();
        while (it != curDateTimeMap.end()) {
            tempFormat =
                CheckDateTimeElement(curDateTime, inputFormatSplitter[i], it->first, (int32_t)it->second, oneElement);
            if (!tempFormat.empty()) {
                break;
            }
            it++;
        }

        if (tempFormat.empty()) {
            tempFormat = Abstract(inputFormatSplitter[i], false);
        }
        format += tempFormat;
    }
    return format;
}

std::string TextClockPattern::CheckDateTimeElement(const std::vector<std::string>& curDateTime, const std::string& str,
    const char& element, const int32_t& elementIndex, const bool& oneElement)
{
    std::string format = "";
    if (str.find(element) != std::string::npos) {
        if ((element == 'y') && (str.length() < (int32_t)(TextClockElementLen::YEAR_WEEK_FORMAT_MAX_LEN))) {
            format =
                curDateTime[elementIndex].substr((int32_t)((int32_t)(TextClockElementLen::YEAR_WEEK_FORMAT_MAX_LEN) -
                                                           (int32_t)(TextClockElementLen::YEAR_FORMAT_MIN_LEN)),
                    (int32_t)(TextClockElementLen::YEAR_FORMAT_MIN_LEN));
        } else {
            format = curDateTime[elementIndex];
        }
        if ((oneElement)) {
            switch (element) {
                case 'y':
                    format += Localization::GetInstance()->GetEntryLetters(TEXTCLOCK_YEAR);
                    break;
                case 'M':
                    format += Localization::GetInstance()->GetEntryLetters(TEXTCLOCK_MONTH);
                    break;
                case 'd':
                    format += Localization::GetInstance()->GetEntryLetters(TEXTCLOCK_DAY);
                    break;
                default:
                    break;
            }
        }
    }
    return format;
}

void TextClockPattern::FireChangeEvent() const
{
    auto textClockEventHub = GetEventHub<TextClockEventHub>();
    CHECK_NULL_VOID(textClockEventHub);
    textClockEventHub->FireChangeEvent(std::to_string(GetMilliseconds() / MICROSECONDS_OF_MILLISECOND));
}

std::string TextClockPattern::GetFormat() const
{
    auto textClockLayoutProperty = GetLayoutProperty<TextClockLayoutProperty>();
    CHECK_NULL_RETURN(textClockLayoutProperty, DEFAULT_FORMAT);
    return textClockLayoutProperty->GetFormat().value_or(DEFAULT_FORMAT);
}

int32_t TextClockPattern::GetHoursWest() const
{
    auto textClockLayoutProperty = GetLayoutProperty<TextClockLayoutProperty>();
    auto tz = GetSystemTimeZone();
    CHECK_NULL_RETURN(textClockLayoutProperty, tz);
    if (textClockLayoutProperty->GetHoursWest().has_value()) {
        return NearEqual(textClockLayoutProperty->GetHoursWest().value(), INT_MAX)
                   ? tz
                   : textClockLayoutProperty->GetHoursWest().value();
    }
    return tz;
}

RefPtr<FrameNode> TextClockPattern::GetTextNode()
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, nullptr);
    auto textNode = AceType::DynamicCast<FrameNode>(host->GetLastChild());
    CHECK_NULL_RETURN(textNode, nullptr);
    if (textNode->GetTag() != V2::TEXT_ETS_TAG) {
        return nullptr;
    }
    return textNode;
}
} // namespace OHOS::Ace::NG
