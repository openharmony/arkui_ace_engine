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

#include "base/log/event_report.h"

#include <ctime>
#include <string>
#include <unistd.h>

#include "hisysevent.h"

#include "base/json/json_util.h"
#include "core/common/ace_engine.h"

namespace OHOS::Ace {
namespace {

constexpr char EVENT_KEY_ERROR_TYPE[] = "ERROR_TYPE";
constexpr char EVENT_KEY_UID[] = "UID";
constexpr char EVENT_KEY_PACKAGE_NAME[] = "PACKAGE_NAME";
constexpr char EVENT_KEY_PROCESS_NAME[] = "PROCESS_NAME";
constexpr char EVENT_KEY_MESSAGE[] = "MESSAGE";
constexpr char EVENT_KEY_CMD[] = "CMD";
constexpr char EVENT_KEY_TIME[] = "TIME";
constexpr char EVENT_KEY_JS_ERR_RAW_CODE[] = "JS_ERR_RAW_CODE";
constexpr char EVENT_KEY_REASON[] = "REASON";
constexpr char EVENT_KEY_SUMMARY[] = "SUMMARY";

constexpr int32_t MAX_PACKAGE_NAME_LENGTH = 128;
constexpr int32_t JS_CRASH_RAW_EVENT_ID = 5002;
constexpr int32_t JS_ERR_RAW_CODE = 3;
constexpr int32_t UIP_WARNING_EVENT_ID = 10257;
constexpr int32_t UIP_FREEZE_EVENT_ID = 10258;
constexpr int32_t UIP_RECOVER_EVENT_ID = 10280;

constexpr char DUMP_LOG_COMMAND[] = "B";

void StrTrim(std::string& str)
{
    if (str.size() > MAX_PACKAGE_NAME_LENGTH) {
        str = str.substr(0, MAX_PACKAGE_NAME_LENGTH);
    }
}

} // namespace

void EventReport::SendEvent(const EventInfo& eventInfo)
{
    auto packageName = AceEngine::Get().GetPackageName();
    if (packageName.size() > MAX_PACKAGE_NAME_LENGTH) {
        StrTrim(packageName);
    }
    OHOS::HiviewDFX::HiSysEvent::Write(OHOS::HiviewDFX::HiSysEvent::Domain::ACE, std::to_string(eventInfo.eventType),
        OHOS::HiviewDFX::HiSysEvent::EventType::FAULT,
        EVENT_KEY_ERROR_TYPE, eventInfo.errorType,
        EVENT_KEY_PACKAGE_NAME, packageName);
}

void EventReport::SendAppStartException(AppStartExcepType type)
{
    EventInfo eventInfo = {
        .eventType = EXCEPTION_FRAMEWORK_APP_START,
        .errorType = static_cast<int32_t>(type),
    };

    SendEventInner(eventInfo);
}

void EventReport::SendPageRouterException(PageRouterExcepType type, const std::string& pageUrl)
{
    EventInfo eventInfo = {
        .eventType = EXCEPTION_FRAMEWORK_PAGE_ROUTER,
        .errorType = static_cast<int32_t>(type),
        .pageUrl = pageUrl,
    };

    SendEventInner(eventInfo);
}

void EventReport::SendComponentException(ComponentExcepType type)
{
    EventInfo eventInfo = {
        .eventType = EXCEPTION_COMPONENT,
        .errorType = static_cast<int32_t>(type),
    };

    SendEventInner(eventInfo);
}

void EventReport::SendAPIChannelException(APIChannelExcepType type)
{
    EventInfo eventInfo = {
        .eventType = EXCEPTION_API_CHANNEL,
        .errorType = static_cast<int32_t>(type),
    };

    SendEventInner(eventInfo);
}

void EventReport::SendRenderException(RenderExcepType type)
{
    EventInfo eventInfo = {
        .eventType = EXCEPTION_RENDER,
        .errorType = static_cast<int32_t>(type),
    };

    SendEventInner(eventInfo);
}

void EventReport::SendJsException(JsExcepType type)
{
    EventInfo eventInfo = {
        .eventType = EXCEPTION_JS,
        .errorType = static_cast<int32_t>(type),
    };

    SendEventInner(eventInfo);
}

void EventReport::SendAnimationException(AnimationExcepType type)
{
    EventInfo eventInfo = {
        .eventType = EXCEPTION_ANIMATION,
        .errorType = static_cast<int32_t>(type),
    };

    SendEventInner(eventInfo);
}

void EventReport::SendEventException(EventExcepType type)
{
    EventInfo eventInfo = {
        .eventType = EXCEPTION_EVENT,
        .errorType = static_cast<int32_t>(type),
    };

    SendEventInner(eventInfo);
}

void EventReport::SendInternalException(InternalExcepType type)
{
    EventInfo eventInfo = {
        .eventType = EXCEPTION_INTERNATIONALIZATION,
        .errorType = static_cast<int32_t>(type),
    };

    SendEventInner(eventInfo);
}

void EventReport::SendAccessibilityException(AccessibilityExcepType type)
{
    EventInfo eventInfo = {
        .eventType = EXCEPTION_ACCESSIBILITY,
        .errorType = static_cast<int32_t>(type),
    };

    SendEventInner(eventInfo);
}

void EventReport::SendFormException(FormExcepType type)
{
    EventInfo eventInfo = {
        .eventType = EXCEPTION_FORM,
        .errorType = static_cast<int32_t>(type),
    };

    SendEventInner(eventInfo);
}

void EventReport::JsEventReport(int32_t eventType, const std::string& jsonStr)
{
    if (!JsonUtil::ParseJsonString(jsonStr)) {
        LOGE("jsonStr is not a JsonArray.");
        return;
    }
}

void EventReport::JsErrReport(
    int32_t uid, const std::string& packageName, const std::string& reason, const std::string& summary)
{
    OHOS::HiviewDFX::HiSysEvent::Write(OHOS::HiviewDFX::HiSysEvent::Domain::ACE, std::to_string(JS_CRASH_RAW_EVENT_ID),
        OHOS::HiviewDFX::HiSysEvent::EventType::FAULT,
        EVENT_KEY_TIME, std::to_string((int32_t)std::time(nullptr)),
        EVENT_KEY_UID, std::to_string(uid),
        EVENT_KEY_JS_ERR_RAW_CODE, std::to_string(JS_ERR_RAW_CODE),
        EVENT_KEY_PACKAGE_NAME, packageName,
        EVENT_KEY_REASON, reason,
        EVENT_KEY_SUMMARY, summary);
}

void EventReport::ANRRawReport(RawEventType type, int32_t uid, const std::string& packageName,
    const std::string& processName, const std::string& msg)
{
    int32_t pid = getpid();
    int32_t eventId = 0;
    std::string cmd = " ";
    if (type == RawEventType::WARNING) {
        eventId = UIP_WARNING_EVENT_ID;
        cmd = "p=" + std::to_string(pid);
    } else if (type == RawEventType::FREEZE) {
        eventId = UIP_FREEZE_EVENT_ID;
        cmd = DUMP_LOG_COMMAND;
    } else {
        eventId = UIP_RECOVER_EVENT_ID;
    }
    std::string eventIdStr = std::to_string(eventId);
    std::string uidStr = std::to_string(uid);
    OHOS::HiviewDFX::HiSysEvent::Write(OHOS::HiviewDFX::HiSysEvent::Domain::ACE, eventIdStr,
        OHOS::HiviewDFX::HiSysEvent::EventType::FAULT,
        EVENT_KEY_UID, uidStr,
        EVENT_KEY_PACKAGE_NAME, packageName,
        EVENT_KEY_PROCESS_NAME, processName,
        EVENT_KEY_MESSAGE, msg,
        EVENT_KEY_CMD, cmd);
}

void EventReport::SendEventInner(const EventInfo& eventInfo)
{
    auto packageName = AceEngine::Get().GetPackageName();
    StrTrim(packageName);
    OHOS::HiviewDFX::HiSysEvent::Write(OHOS::HiviewDFX::HiSysEvent::Domain::ACE, std::to_string(eventInfo.eventType),
            OHOS::HiviewDFX::HiSysEvent::EventType::FAULT,
            EVENT_KEY_ERROR_TYPE, eventInfo.errorType,
            EVENT_KEY_PACKAGE_NAME, packageName);
}

} // namespace OHOS::Ace
