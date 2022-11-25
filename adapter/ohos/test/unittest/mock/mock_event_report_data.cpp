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
#include "mock_event_report_data.h"

namespace OHOS::Ace {

bool MockEventReportData::SendEvent(const EventInfo& eventInfo)
{
    EventReport::SendEvent(eventInfo);
    return true;
}

bool MockEventReportData::SendJsCardRenderTimeEvent(
    const std::string& sessionID,
    const std::string& timeType,
    uint64_t timeDelay)
{
    EventReport::SendJsCardRenderTimeEvent(sessionID, timeType, timeDelay);
    return true;
}

bool MockEventReportData::SendComponentException(ComponentExcepType type)
{
    EventReport::SendComponentException(type);
    return true;
}

bool MockEventReportData::SendAPIChannelException(APIChannelExcepType type)
{
    EventReport::SendAPIChannelException(type);
    return true;
}

bool MockEventReportData::SendJsException(JsExcepType type)
{
    EventReport::SendJsException(type);
    return true;
}

bool MockEventReportData::SendAnimationException(AnimationExcepType type)
{
    EventReport::SendAnimationException(type);
    return true;
}

bool MockEventReportData::SendInternalException(InternalExcepType type)
{
    EventReport::SendInternalException(type);
    return true;
}

bool MockEventReportData::SendAccessibilityException(AccessibilityExcepType type)
{
    EventReport::SendAccessibilityException(type);
    return true;
}

bool MockEventReportData::SendFormException(FormExcepType type)
{
    EventReport::SendFormException(type);
    return true;
}

bool MockEventReportData::JsEventReport(int32_t eventType, const std::string& jsonStr)
{
    EventReport::JsEventReport(eventType, jsonStr);
    return true;
}

bool MockEventReportData::JsErrReport(
    const std::string& packageName, const std::string& reason, const std::string& summary)
{
    EventReport::JsErrReport(packageName, reason, summary);
    return true;
}

bool MockEventReportData::ANRRawReport(RawEventType type, int32_t uid, const std::string& packageName,
    const std::string& processName, const std::string& msg)
{
    EventReport::ANRRawReport(type, uid, packageName, processName, msg);
    return true;
}

bool MockEventReportData::ANRShowDialog(int32_t uid, const std::string& packageName,
    const std::string& processName, const std::string& msg)
{
    EventReport::ANRShowDialog(uid, packageName, processName, msg);
    return true;
}
} // namespace OHOS::Ace
