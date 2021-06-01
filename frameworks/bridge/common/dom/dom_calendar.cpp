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

#include "frameworks/bridge/common/dom/dom_calendar.h"

#include "base/utils/string_utils.h"
#include "frameworks/bridge/common/utils/utils.h"

namespace OHOS::Ace::Framework {
namespace {

constexpr uint32_t METHOD_GO_TO_ARGS_SIZE = 1;
const char GO_TO_ARG_KEY_YEAR[] = "year";
const char GO_TO_ARG_KEY_MONTH[] = "month";
const char GO_TO_ARG_KEY_DAY[] = "day";

} // namespace

DomCalendar::DomCalendar(NodeId nodeId, const std::string& nodeName)
    : DOMNode(nodeId, nodeName),
      calendarComponent_(AceType::MakeRefPtr<CalendarComponent>(std::to_string(nodeId), nodeName))
{
    if (IsRightToLeft()) {
        calendarComponent_->SetTextDirection(TextDirection::RTL);
    }
}

bool DomCalendar::SetSpecializedAttr(const std::pair<std::string, std::string>& attr)
{
    static const LinearMapNode<bool (*)(const std::string&, DomCalendar&)> calendarAttrOperators[] = {
        { DOM_CALENDAR_DATA,
            [](const std::string& value, DomCalendar& calendar) {
                calendar.calendarComponent_->SetCalendarData(value);
                return true;
            } },
        { DOM_CALENDAR_CARD_CALENDAR,
            [](const std::string& value, DomCalendar& calendar) {
                calendar.calendarComponent_->SetCardCalendar(StringToBool(value));
                return true;
            } },
        { DOM_CALENDAR_DATE,
            [](const std::string& value, DomCalendar& calendar) {
                CalendarDay day;
                auto isLegal = StringUtils::StringToCalendarDay(value, day);
                if (isLegal) {
                    calendar.calendarComponent_->SetCalendarDate(day);
                    return true;
                }
                return false;
            } },
        { DOM_CALENDAR_DATE_ADAPTER,
            [](const std::string& value, DomCalendar& calendar) {
                return calendar.ParseDataAdapter(value);
            } },
        { DOM_CALENDAR_OFF_DAYS,
            [](const std::string& value, DomCalendar& calendar) {
                calendar.calendarComponent_->SetOffDays(value);
                return true;
            } },
        { DOM_CALENDAR_SHOW_HOLIDAY,
            [](const std::string& value, DomCalendar& calendar) {
                calendar.calendarComponent_->SetShowHoliday(StringToBool(value));
                return true;
            } },
        { DOM_CALENDAR_SHOW_LUNAR,
            [](const std::string& value, DomCalendar& calendar) {
                calendar.calendarComponent_->SetShowLunar(StringToBool(value));
                return true;
            } },
        { DOM_CALENDAR_START_DAY_OF_WEEK,
            [](const std::string& value, DomCalendar& calendar) {
                auto indexOfWeek = StringToInt(value);
                if (0 <= indexOfWeek && indexOfWeek < 7) {
                    calendar.calendarComponent_->SetStartDayOfWeek(indexOfWeek);
                    return true;
                }
                return false;
            } },
        { DOM_VERTICAL,
            [](const std::string& value, DomCalendar& calendar) {
                calendar.calendarComponent_->SetAxis(StringToBool(value) ? Axis::VERTICAL : Axis::HORIZONTAL);
                return true;
            } },
    };
    auto operatorIter =
        BinarySearchFindIndex(calendarAttrOperators, ArraySize(calendarAttrOperators), attr.first.c_str());
    if (operatorIter != -1) {
        return calendarAttrOperators[operatorIter].value(attr.second, *this);
    }
    return false;
}

void DomCalendar::CallSpecializedMethod(const std::string& method, const std::string& args)
{
    if (method == DOM_CALENDAR_METHOD_GO_TO) {
        HandleGoTo(args);
    }
}

bool DomCalendar::AddSpecializedEvent(int32_t pageId, const std::string& event)
{
    if (event == DOM_CALENDAR_EVENT_SELECTED_CHANGE) {
        selectedChangeEvent_ = EventMarker(GetNodeIdForEvent(), event, pageId);
        calendarComponent_->SetSelectedChangeEvent(selectedChangeEvent_);
        return true;
    } else if (event == DOM_CALENDAR_EVENT_REQUEST_DATA) {
        requestDataEvent_ = EventMarker(GetNodeIdForEvent(), event, pageId);
        calendarComponent_->SetRequestDataEvent(requestDataEvent_);
        return true;
    }
    return false;
}

bool DomCalendar::ParseDataAdapter(const std::string& value)
{
    std::unique_ptr<JsonValue> dataAdapterValue = JsonUtil::ParseJsonString(value);
    if (!dataAdapterValue) {
        LOGE("data adapter format is error");
        return false;
    }
    std::unique_ptr<JsonValue> bundleNameValue = dataAdapterValue->GetValue("bundleName");
    if (!bundleNameValue || !bundleNameValue->IsString()) {
        LOGE("get bundleName failed");
        return false;
    }
    std::unique_ptr<JsonValue> abilityNameValue = dataAdapterValue->GetValue("abilityName");
    if (!abilityNameValue || !abilityNameValue->IsString()) {
        LOGE("get abilityName failed");
        return false;
    }
    std::unique_ptr<JsonValue> messageCodeValue = dataAdapterValue->GetValue("messageCode");
    if (!messageCodeValue || !messageCodeValue->IsNumber()) {
        LOGE("get messageCode failed");
        return false;
    }
    std::string bundleName = bundleNameValue->GetString();
    std::string abilityName = abilityNameValue->GetString();
    int32_t messageCode = messageCodeValue->GetInt();
    CalendarDataAdapterAction dataAdapterAction {
        { .bundleName = bundleName, .abilityName = abilityName, .messageCode = messageCode }
    };
    calendarComponent_->SetDataAdapterAction(dataAdapterAction);
    return true;
}

void DomCalendar::HandleGoTo(const std::string& args)
{
    std::unique_ptr<JsonValue> argsValue = JsonUtil::ParseJsonString(args);
    if (!argsValue || !argsValue->IsArray() || argsValue->GetArraySize() != METHOD_GO_TO_ARGS_SIZE) {
        LOGE("parse args error: %{private}s", args.c_str());
        return;
    }
    auto gotoArg = argsValue->GetArrayItem(0);
    if (!gotoArg || !gotoArg->Contains(GO_TO_ARG_KEY_YEAR) || !gotoArg->Contains(GO_TO_ARG_KEY_MONTH)) {
        LOGE("calendar goto arg no year or month");
        return;
    }

    std::unique_ptr<JsonValue> yearValue = gotoArg->GetValue(GO_TO_ARG_KEY_YEAR);
    if (!yearValue || !yearValue->IsNumber()) {
        LOGE("get year failed");
        return;
    }

    std::unique_ptr<JsonValue> monthValue = gotoArg->GetValue(GO_TO_ARG_KEY_MONTH);
    if (!monthValue || !monthValue->IsNumber()) {
        LOGE("get month failed");
        return;
    }
    int32_t year = yearValue->GetInt();
    int32_t month = monthValue->GetInt();
    // default selected first day of month
    int32_t day = -1;

    std::unique_ptr<JsonValue> dayValue = gotoArg->GetValue(GO_TO_ARG_KEY_DAY);
    if (dayValue && dayValue->IsNumber()) {
        day = dayValue->GetInt();
    }
    calendarComponent_->GoTo(year, month, day);
}
} // namespace OHOS::Ace::Framework
