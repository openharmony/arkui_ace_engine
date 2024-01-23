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
#include "base/utils/system_properties.h"
#include "base/utils/time_util.h"
#include "base/utils/utils.h"
#include "core/common/container.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/property/property.h"
#include "core/event/time/time_event_proxy.h"
#include "core/pipeline/base/render_context.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t TOTAL_SECONDS_OF_HOUR = 60 * 60;
constexpr int32_t BASE_YEAR = 1900;
constexpr int32_t INTERVAL_OF_U_SECOND = 1000000;
constexpr int32_t MICROSECONDS_OF_MILLISECOND = 1000;
constexpr int32_t MILLISECONDS_OF_SECOND = 1000;
constexpr int32_t TOTAL_SECONDS_OF_MINUTE = 60;
const std::string DEFAULT_FORMAT = "hms";
const std::string FORM_FORMAT = "hm";
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
    CUR_SHORT_YEAR_INDEX = 9,
    CUR_SHORT_MONTH_INDEX = 10,
    CUR_SHORT_DAY_INDEX = 11,
    CUR_CENTISECOND_INDEX = 12,
    CUR_SHORT_WEEK_INDEX = 13,
    CUR_MAX_INDEX
};
enum class TextClockElementLen {
    ONLY_ONE_DATE_ELEMENT = 1,
    SHORT_YEAR_IN_YEAR_INDEX = 2,
    YEAR_FORMAT_MIN_LEN = 2,
    MON_DAY_FORMAT_MAX_LEN = 2,
    MON_DAY_FORMAT_MIN_LEN = 1,
    CENTISECOND_FORMAT_LEN = 2,
    MILLISECOND_FORMAT_LEN = 3,
    YEAR_WEEK_FORMAT_MAX_LEN = 4,
};
enum class TextClockWeekType {
    WEEK_FULL_TYPE = 1,
    WEEK_SHORT_TYPE = 2,
};
} // namespace

TextClockPattern::TextClockPattern()
{
    textClockController_ = MakeRefPtr<TextClockController>();
}

void TextClockPattern::OnAttachToFrameNode()
{
    InitTextClockController();
    InitUpdateTimeTextCallBack();
    auto* eventProxy = TimeEventProxy::GetInstance();
    if (eventProxy) {
        eventProxy->Register(WeakClaim(this));
    }
}

void TextClockPattern::OnDetachFromFrameNode(FrameNode* frameNode)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    pipeline->RemoveVisibleAreaChangeNode(host->GetId());
    pipeline->RemoveFormVisibleChangeNode(host->GetId());
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
    if (layoutProperty->GetTextShadow().has_value()) {
        textLayoutProperty->UpdateTextShadow(layoutProperty->GetTextShadow().value());
    }
    if (layoutProperty->GetFontFeature().has_value()) {
        textLayoutProperty->UpdateFontFeature(layoutProperty->GetFontFeature().value());
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
    delayTask_.Cancel();
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
            textClock->delayTask_.Cancel();
        }
    });
}

void TextClockPattern::OnVisibleChange(bool isVisible)
{
    if (isVisible && !isSetVisible_) {
        isSetVisible_ = isVisible;
        UpdateTimeText();
    } else if (!isVisible) {
        isSetVisible_ = isVisible;
        delayTask_.Cancel();
    }
}

void TextClockPattern::OnVisibleAreaChange(bool visible)
{
    if (visible && !isInVisibleArea_) {
        isInVisibleArea_ = visible;
        UpdateTimeText();
    } else if (!visible) {
        isInVisibleArea_ = visible;
        delayTask_.Cancel();
    }
}

void TextClockPattern::OnFormVisibleChange(bool visible)
{
    if (visible && !isFormVisible_) {
        isFormVisible_ = visible;
        UpdateTimeText();
    } else if (!visible) {
        isFormVisible_ = visible;
        delayTask_.Cancel();
    }
}

void TextClockPattern::RegistVisibleAreaChangeCallback()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);

    auto areaCallback = [weak = WeakClaim(this)](bool visible, double ratio) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->OnVisibleAreaChange(visible);
    };
    pipeline->RemoveVisibleAreaChangeNode(host->GetId());
    pipeline->AddVisibleAreaChangeNode(host, 0.0f, areaCallback, false);

    if (isForm_) {
        pipeline->RemoveFormVisibleChangeNode(host->GetId());
        auto formCallback = [weak = WeakClaim(this)](bool visible) {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            pattern->OnFormVisibleChange(visible);
        };
        pipeline->AddFormVisibleChangeNode(host, formCallback);
    }
}

void TextClockPattern::InitUpdateTimeTextCallBack()
{
    auto context = UINode::GetContext();
    if (context) {
        isForm_ = context->IsFormRender();
    }
    RegistVisibleAreaChangeCallback();
}

void TextClockPattern::UpdateTimeText()
{
    if (!isStart_ || !isSetVisible_ || !isInVisibleArea_ || !isFormVisible_) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto textNode = GetTextNode();
    CHECK_NULL_VOID(textNode);
    auto textLayoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(textLayoutProperty);

    std::string currentTime = GetCurrentFormatDateTime();
    if (currentTime.empty()) {
        return;
    }

    textLayoutProperty->UpdateContent(currentTime); // update time text.
    auto textContext = textNode->GetRenderContext();
    CHECK_NULL_VOID(textContext);
    textContext->SetClipToFrame(false);
    textContext->UpdateClipEdge(false);
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_PARENT);
    textNode->MarkModifyDone();
    RequestUpdateForNextSecond();
    if (currentTime != prevTime_) {
        FireChangeEvent();
    }
    prevTime_ = currentTime;
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
    if (isForm_) {
        time_t current = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        auto* timeZoneTime = std::localtime(&current);
        // delay to next minute
        int32_t tempTime = (TOTAL_SECONDS_OF_MINUTE - timeZoneTime->tm_sec) * MILLISECONDS_OF_SECOND;
        delayTime += (tempTime - MILLISECONDS_OF_SECOND);
    }

    auto context = UINode::GetContext();
    CHECK_NULL_VOID(context);
    CHECK_NULL_VOID(context->GetTaskExecutor());
    delayTask_.Reset([weak = WeakClaim(this)] {
        auto textClock = weak.Upgrade();
        CHECK_NULL_VOID(textClock);
        if (!textClock->isStart_) {
            return;
        }
        textClock->UpdateTimeText();
    });
    context->GetTaskExecutor()->PostDelayedTask(delayTask_, TaskExecutor::TaskType::UI, delayTime);
}

std::string TextClockPattern::GetCurrentFormatDateTime()
{
    time_t current = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    auto* timeZoneTime = std::localtime(&current);
    if (!std::isnan(hourWest_)) {
        current = current - int32_t(hourWest_ * TOTAL_SECONDS_OF_HOUR);
        timeZoneTime = std::gmtime(&current); // Convert to UTC time.
    }
    CHECK_NULL_RETURN(timeZoneTime, "");
    DateTime dateTime; // This is for i18n date time.
    dateTime.year = timeZoneTime->tm_year + BASE_YEAR;
    dateTime.month = timeZoneTime->tm_mon;
    dateTime.day = timeZoneTime->tm_mday;
    dateTime.hour = timeZoneTime->tm_hour;
    dateTime.minute = timeZoneTime->tm_min;
    dateTime.second = timeZoneTime->tm_sec;
    if (Container::LessThanAPIVersion(PlatformVersion::VERSION_ELEVEN) && !isForm_) {
        return Localization::GetInstance()->FormatDateTime(dateTime, GetFormat());
    }
    dateTime.week = timeZoneTime->tm_wday; // 0-6

    // parse input format
    formatElementMap.clear();
    bool is24H = is24H_;
    ParseInputFormat(is24H);

    // get date time from third party
    std::string dateTimeFormat = DEFAULT_FORMAT; // the format to get datetime value from the thirdlib
    dateTimeFormat = "yyyyMMdd";
    dateTimeFormat += is24H ? "HH" : "hh";
    dateTimeFormat += "mmss";
    dateTimeFormat += "SSS";
    std::string dateTimeValue = Localization::GetInstance()->FormatDateTime(dateTime, dateTimeFormat);

    // parse data time
    std::string tempdateTimeValue = dateTimeValue;
    std::string strAmPm = GetAmPm(tempdateTimeValue);
    if (!strAmPm.empty()) {
        tempdateTimeValue.replace(tempdateTimeValue.find(strAmPm), strAmPm.length(), "");
    }
    std::vector<std::string> curDateTime = ParseDateTimeValue(tempdateTimeValue);
    curDateTime[(int32_t)(TextClockElementIndex::CUR_AMPM_INDEX)] = strAmPm;

    // parse week
    curDateTime[(int32_t)(TextClockElementIndex::CUR_WEEK_INDEX)] = GetWeek(false, timeZoneTime->tm_wday);
    curDateTime[(int32_t)(TextClockElementIndex::CUR_SHORT_WEEK_INDEX)] = GetWeek(true, timeZoneTime->tm_wday);
    // splice date time
    std::string outputDateTime = SpliceDateTime(curDateTime);
    if ((curDateTime[(int32_t)(TextClockElementIndex::CUR_YEAR_INDEX)] == "1900") || (outputDateTime == "")) {
        if (isForm_) {
            TextClockFormatElement tempFormatElement;
            std::vector<std::string> formSplitter = { "h", ":", "m" };
            formatElementMap.clear();
            tempFormatElement.formatElement = formSplitter[0];
            tempFormatElement.elementKey = 'h';
            tempFormatElement.formatElementNum = (int32_t)(TextClockElementIndex::CUR_HOUR_INDEX);
            formatElementMap[0] = tempFormatElement;
            tempFormatElement.formatElement = formSplitter[1];
            tempFormatElement.elementKey = ':';
            tempFormatElement.formatElementNum = (int32_t)(TextClockElementIndex::CUR_MAX_INDEX);
            formatElementMap[1] = tempFormatElement;
            tempFormatElement.formatElement = formSplitter[2];
            tempFormatElement.elementKey = 'm';
            tempFormatElement.formatElementNum = (int32_t)(TextClockElementIndex::CUR_MINUTE_INDEX);
            formatElementMap[2] = tempFormatElement;
            outputDateTime = SpliceDateTime(curDateTime);
        } else {
            outputDateTime = dateTimeValue;
        }
    }
    return outputDateTime;
}

void TextClockPattern::ParseInputFormat(bool& is24H)
{
    std::string inputFormat = (GetFormat() == DEFAULT_FORMAT) ? "aa h:m:s" : GetFormat();
    if (inputFormat == FORM_FORMAT && isForm_) {
        inputFormat = "h:m";
    }
    std::vector<std::string> formatSplitter;
    auto i = 0;
    auto j = 0;
    auto len = static_cast<int32_t>(inputFormat.length());
    std::string tempFormat = "";
    TextClockFormatElement tempFormatElement;
    tempFormatElement.formatElement = "";
    tempFormatElement.formatElementNum = 0;
    for (tempFormat = inputFormat[i]; i < len; i++) {
        if (inputFormat[i] == 'H') {
            is24H = true;
        }
        if ((i + 1) < len) {
            if (inputFormat[i] == inputFormat[i + 1]) {
                tempFormat += inputFormat[i + 1]; // the same element format
                tempFormatElement.formatElementNum++;
            } else {
                tempFormatElement.formatElement = tempFormat;
                tempFormatElement.formatElementNum++;
                GetDateTimeIndex(inputFormat[i], tempFormatElement);
                tempFormatElement.elementKey = inputFormat[i];
                formatElementMap[j] = tempFormatElement;
                j++;
                // clear current element
                tempFormat = "";
                tempFormat += inputFormat[i + 1]; // the next element format
                tempFormatElement.formatElement = "";
                tempFormatElement.formatElementNum = 0;
            }
        } else { // the last element
            tempFormatElement.formatElement = tempFormat;
            tempFormatElement.formatElementNum++;
            GetDateTimeIndex(inputFormat[i], tempFormatElement);
            tempFormatElement.elementKey = inputFormat[i];
            formatElementMap[j] = tempFormatElement;
        }
    }
}

void TextClockPattern::GetDateTimeIndex(const char& element, TextClockFormatElement& tempFormatElement)
{
    switch (element) {
        case 'y':
            if (tempFormatElement.formatElementNum >= (int32_t)(TextClockElementLen::YEAR_WEEK_FORMAT_MAX_LEN)) {
                tempFormatElement.formatElementNum = (int32_t)(TextClockElementIndex::CUR_YEAR_INDEX);
            } else {
                tempFormatElement.formatElementNum = (int32_t)(TextClockElementIndex::CUR_SHORT_YEAR_INDEX);
            }
            break;
        case 'M':
            if (tempFormatElement.formatElementNum >= (int32_t)(TextClockElementLen::MON_DAY_FORMAT_MAX_LEN)) {
                tempFormatElement.formatElementNum = (int32_t)(TextClockElementIndex::CUR_MONTH_INDEX);
            } else {
                tempFormatElement.formatElementNum = (int32_t)(TextClockElementIndex::CUR_SHORT_MONTH_INDEX);
            }
            break;
        case 'd':
            if (tempFormatElement.formatElementNum >= (int32_t)(TextClockElementLen::MON_DAY_FORMAT_MAX_LEN)) {
                tempFormatElement.formatElementNum = (int32_t)(TextClockElementIndex::CUR_DAY_INDEX);
            } else {
                tempFormatElement.formatElementNum = (int32_t)(TextClockElementIndex::CUR_SHORT_DAY_INDEX);
            }
            break;
        case 'E':
            if (tempFormatElement.formatElementNum >= (int32_t)(TextClockElementLen::YEAR_WEEK_FORMAT_MAX_LEN)) {
                tempFormatElement.formatElementNum = (int32_t)(TextClockElementIndex::CUR_WEEK_INDEX);
            } else {
                tempFormatElement.formatElementNum = (int32_t)(TextClockElementIndex::CUR_SHORT_WEEK_INDEX);
            }
            break;
        case 'a':
            tempFormatElement.formatElementNum = (int32_t)(TextClockElementIndex::CUR_AMPM_INDEX);
            break;
        case 'H':
        case 'h':
            tempFormatElement.formatElementNum = (int32_t)(TextClockElementIndex::CUR_HOUR_INDEX);
            break;
        case 'm':
            tempFormatElement.formatElementNum = (int32_t)(TextClockElementIndex::CUR_MINUTE_INDEX);
            break;
        case 's':
            tempFormatElement.formatElementNum = (int32_t)(TextClockElementIndex::CUR_SECOND_INDEX);
            break;
        case 'S':
            if (tempFormatElement.formatElementNum >= (int32_t)(TextClockElementLen::MILLISECOND_FORMAT_LEN)) {
                tempFormatElement.formatElementNum = (int32_t)(TextClockElementIndex::CUR_MILLISECOND_INDEX);
            } else {
                tempFormatElement.formatElementNum = (int32_t)(TextClockElementIndex::CUR_CENTISECOND_INDEX);
            }
            break;
        default:
            break;
    }
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

std::vector<std::string> TextClockPattern::ParseDateTimeValue(const std::string& strDateTimeValue)
{
    std::string dateTimeValue = strDateTimeValue;
    std::vector<std::string> curDateTime = { "1900", "0", "1", "0", "0", "0", "0", "", "0", "", "", "", "", "" };
    auto dateFirstSplit = dateTimeValue.find('/');
    auto dateSecondSplit = dateTimeValue.find('/', dateFirstSplit + 1);
    auto dateThirdSplit =
        (dateTimeValue.find(',') != std::string::npos) ? dateTimeValue.find(',') : dateTimeValue.find(' ');
    if (curDateTime.size() != (int32_t)(TextClockElementIndex::CUR_MAX_INDEX)) {
        return curDateTime;
    }
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

        // get short date
        curDateTime[(int32_t)(TextClockElementIndex::CUR_SHORT_YEAR_INDEX)] =
            (curDateTime[(int32_t)(TextClockElementIndex::CUR_YEAR_INDEX)].length() >
                (int32_t)(TextClockElementLen::YEAR_FORMAT_MIN_LEN))
                ? curDateTime[(int32_t)(TextClockElementIndex::CUR_YEAR_INDEX)].substr(
                    (int32_t)(TextClockElementLen::SHORT_YEAR_IN_YEAR_INDEX),
                    (int32_t)(TextClockElementLen::YEAR_FORMAT_MIN_LEN))
                : curDateTime[(int32_t)(TextClockElementIndex::CUR_YEAR_INDEX)];
        if (curDateTime[(int32_t)(TextClockElementIndex::CUR_MONTH_INDEX)].length() >
            (int32_t)(TextClockElementLen::MON_DAY_FORMAT_MIN_LEN)) {
            curDateTime[(int32_t)(TextClockElementIndex::CUR_SHORT_MONTH_INDEX)] =
                (curDateTime[(int32_t)(TextClockElementIndex::CUR_MONTH_INDEX)].substr(0, 1) == "0")
                    ? curDateTime[(int32_t)(TextClockElementIndex::CUR_MONTH_INDEX)].substr(1, 1)
                    : curDateTime[(int32_t)(TextClockElementIndex::CUR_MONTH_INDEX)];
        }
        if (curDateTime[(int32_t)(TextClockElementIndex::CUR_DAY_INDEX)].length() >
            (int32_t)(TextClockElementLen::MON_DAY_FORMAT_MIN_LEN)) {
            curDateTime[(int32_t)(TextClockElementIndex::CUR_SHORT_DAY_INDEX)] =
                (curDateTime[(int32_t)(TextClockElementIndex::CUR_DAY_INDEX)].substr(0, 1) == "0")
                    ? curDateTime[(int32_t)(TextClockElementIndex::CUR_DAY_INDEX)].substr(1, 1)
                    : curDateTime[(int32_t)(TextClockElementIndex::CUR_DAY_INDEX)];
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
        curDateTime[(int32_t)(TextClockElementIndex::CUR_CENTISECOND_INDEX)] =
            (curDateTime[(int32_t)(TextClockElementIndex::CUR_MILLISECOND_INDEX)].length() >
                (int32_t)(TextClockElementLen::CENTISECOND_FORMAT_LEN))
                ? curDateTime[(int32_t)(TextClockElementIndex::CUR_MILLISECOND_INDEX)].substr(
                    0, (int32_t)(TextClockElementLen::CENTISECOND_FORMAT_LEN))
                : curDateTime[(int32_t)(TextClockElementIndex::CUR_MILLISECOND_INDEX)];
    }
    return curDateTime;
}

// abstractItem: true:get letter  false:get non letter
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

// isShortType: false:full type week, true:short type week
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

std::string TextClockPattern::SpliceDateTime(const std::vector<std::string>& curDateTime)
{
    std::string format = "";
    std::string tempFormat = "";
    bool oneElement = false;
    if (((int32_t)(formatElementMap.size()) == (int32_t)TextClockElementLen::ONLY_ONE_DATE_ELEMENT) &&
        ((strcmp(Localization::GetInstance()->GetLanguage().c_str(), "zh") == 0))) {
        oneElement = true; // year,month or day need Chinese suffix when Chinese system
    }
    auto it = formatElementMap.begin();
    while (it != formatElementMap.end()) {
        tempFormat = CheckDateTimeElement(curDateTime, it->second.elementKey, it->second.formatElementNum, oneElement);
        if (tempFormat.empty()) {
            tempFormat = Abstract(it->second.formatElement, false); // get non letter splitter
        }
        format += tempFormat;
        it++;
    }
    return format;
}

std::string TextClockPattern::CheckDateTimeElement(const std::vector<std::string>& curDateTime, const char& element,
    const int32_t& elementIndex, const bool& oneElement)
{
    std::string format = "";
    std::string curDateTimeElement = "yMdHhmsSaE";
    if (curDateTimeElement.find(element) != std::string::npos) {
        format = curDateTime[elementIndex];
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
    if (isForm_) {
        CHECK_NULL_RETURN(textClockLayoutProperty, FORM_FORMAT);
        std::string result = textClockLayoutProperty->GetFormat().value_or(FORM_FORMAT);
        if (result.find("s") != std::string::npos || result.find("S") != std::string::npos) {
            return FORM_FORMAT;
        }
        return result;
    }
    CHECK_NULL_RETURN(textClockLayoutProperty, DEFAULT_FORMAT);
    return textClockLayoutProperty->GetFormat().value_or(DEFAULT_FORMAT);
}

float TextClockPattern::GetHoursWest() const
{
    auto textClockLayoutProperty = GetLayoutProperty<TextClockLayoutProperty>();
    CHECK_NULL_RETURN(textClockLayoutProperty, NAN);
    if (textClockLayoutProperty->GetHoursWest().has_value()) {
        return textClockLayoutProperty->GetHoursWest().value();
    }
    return NAN;
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

void TextClockPattern::OnTimeChange()
{
    is24H_ = SystemProperties::Is24HourClock();
    UpdateTimeText();
}
} // namespace OHOS::Ace::NG
