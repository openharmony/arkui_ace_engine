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
#include "core/common/ace_application_info.h"
#include "core/common/ace_engine.h"

namespace OHOS::Ace {
namespace {

constexpr char EVENT_KEY_ERROR_TYPE[] = "ERROR_TYPE";
constexpr char EVENT_KEY_UID[] = "UID";
constexpr char EVENT_KEY_PID[] = "PID";
constexpr char EVENT_KEY_SESSIONID[] = "SESSION_ID";
constexpr char EVENT_KEY_PACKAGE_NAME[] = "PACKAGE_NAME";
constexpr char EVENT_KEY_PROCESS_NAME[] = "PROCESS_NAME";
constexpr char EVENT_KEY_MESSAGE[] = "MSG";
constexpr char EVENT_KEY_CMD[] = "CMD";
constexpr char EVENT_KEY_REASON[] = "REASON";
constexpr char EVENT_KEY_SUMMARY[] = "SUMMARY";
constexpr char EVENT_NAME_JS_ERROR[] = "JS_ERROR";
constexpr char STATISTIC_DURATION[] = "DURATION";
constexpr char EVENT_KEY_STARTTIME[] = "STARTTIME";
constexpr char EVENT_KEY_VERSION_CODE[] = "VERSION_CODE";
constexpr char EVENT_KEY_VERSION_NAME[] = "VERSION_NAME";
constexpr char EVENT_KEY_BUNDLE_NAME[] = "BUNDLE_NAME";
constexpr char EVENT_KEY_ABILITY_NAME[] = "ABILITY_NAME";
constexpr char EVENT_KEY_PAGE_URL[] = "PAGE_URL";
constexpr char EVENT_KEY_JANK_STATS[] = "JANK_STATS";
constexpr char EVENT_KEY_JANK_STATS_VER[] = "JANK_STATS_VER";
constexpr char EVENT_KEY_APP_PID[] = "APP_PID";
constexpr char EVENT_KEY_SCENE_ID[] = "SCENE_ID";
constexpr char EVENT_KEY_INPUT_TIME[] = "INPUT_TIME";
constexpr char EVENT_KEY_ANIMATION_START_LATENCY[] = "ANIMATION_START_LATENCY";
constexpr char EVENT_KEY_ANIMATION_END_LATENCY[] = "ANIMATION_END_LATENCY";
constexpr char EVENT_KEY_E2E_LATENCY[] = "E2E_LATENCY";
constexpr char EVENT_KEY_UNIQUE_ID[] = "UNIQUE_ID";
constexpr char EVENT_KEY_MODULE_NAME[] = "MODULE_NAME";
constexpr char EVENT_KEY_DURITION[] = "DURITION";
constexpr char EVENT_KEY_TOTAL_FRAMES[] = "TOTAL_FRAMES";
constexpr char EVENT_KEY_TOTAL_MISSED_FRAMES[] = "TOTAL_MISSED_FRAMES";
constexpr char EVENT_KEY_MAX_FRAMETIME[] = "MAX_FRAMETIME";
constexpr char EVENT_KEY_MAX_SEQ_MISSED_FRAMES[] = "MAX_SEQ_MISSED_FRAMES";
constexpr char EVENT_KEY_SOURCE_TYPE[] = "SOURCE_TYPE";
constexpr char EVENT_KEY_NOTE[] = "NOTE";

constexpr int32_t MAX_PACKAGE_NAME_LENGTH = 128;

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
    auto packageName = AceApplicationInfo::GetInstance().GetPackageName();
    if (packageName.size() > MAX_PACKAGE_NAME_LENGTH) {
        StrTrim(packageName);
    }
    HiSysEventWrite(OHOS::HiviewDFX::HiSysEvent::Domain::ACE, eventInfo.eventType,
        OHOS::HiviewDFX::HiSysEvent::EventType::FAULT,
        EVENT_KEY_ERROR_TYPE, eventInfo.errorType,
        EVENT_KEY_PACKAGE_NAME, packageName);
}

void EventReport::SendJsCardRenderTimeEvent(
    const std::string& sessionID,
    const std::string& timeType,
    uint64_t timeDelay)
{
    HiSysEventWrite(OHOS::HiviewDFX::HiSysEvent::Domain::ACE, timeType,
        OHOS::HiviewDFX::HiSysEvent::EventType::STATISTIC,
        EVENT_KEY_SESSIONID, sessionID,
        STATISTIC_DURATION, timeDelay);
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
    const std::string& packageName, const std::string& reason, const std::string& summary)
{
    HiSysEventWrite(OHOS::HiviewDFX::HiSysEvent::Domain::ACE, EVENT_NAME_JS_ERROR,
        OHOS::HiviewDFX::HiSysEvent::EventType::FAULT,
        EVENT_KEY_PACKAGE_NAME, packageName,
        EVENT_KEY_REASON, reason,
        EVENT_KEY_SUMMARY, summary);
}

void EventReport::ANRRawReport(RawEventType type, int32_t uid, const std::string& packageName,
    const std::string& processName, const std::string& msg)
{
    int32_t pid = getpid();
    std::string cmd = " ";
    std::string eventName = "";
    if (type == RawEventType::WARNING) {
        eventName = "UI_BLOCK_3S";
        cmd = "p=" + std::to_string(pid);
    } else if (type == RawEventType::FREEZE) {
        eventName = "UI_BLOCK_6S";
        cmd = DUMP_LOG_COMMAND;
    } else {
        eventName = "UI_BLOCK_RECOVERED";
    }
    std::string uidStr = std::to_string(uid);
    HiSysEventWrite(OHOS::HiviewDFX::HiSysEvent::Domain::ACE, eventName,
        OHOS::HiviewDFX::HiSysEvent::EventType::FAULT,
        EVENT_KEY_UID, uidStr,
        EVENT_KEY_PACKAGE_NAME, packageName,
        EVENT_KEY_PROCESS_NAME, processName,
        EVENT_KEY_MESSAGE, msg,
        EVENT_KEY_CMD, cmd);
}

void EventReport::ANRShowDialog(int32_t uid, const std::string& packageName,
    const std::string& processName, const std::string& msg)
{
    int32_t pid = getpid();
    std::string eventName = "UI_BLOCK_DIALOG";
    std::string uidStr = std::to_string(uid);
    std::string pidStr = std::to_string(pid);
    HiSysEventWrite(OHOS::HiviewDFX::HiSysEvent::Domain::ACE, eventName,
        OHOS::HiviewDFX::HiSysEvent::EventType::FAULT,
        EVENT_KEY_UID, uidStr,
        EVENT_KEY_PID, pidStr,
        EVENT_KEY_PACKAGE_NAME, packageName,
        EVENT_KEY_PROCESS_NAME, processName,
        EVENT_KEY_MESSAGE, msg);
}

void EventReport::JankFrameReport(int64_t startTime, int64_t duration, const std::vector<uint16_t>& jank,
    const std::string& pageUrl, uint32_t jankStatusVersion)
{
    std::string eventName = "JANK_STATS_APP";
    auto app_version_code = AceApplicationInfo::GetInstance().GetAppVersionCode();
    auto app_version_name = AceApplicationInfo::GetInstance().GetAppVersionName();
    auto packageName = AceApplicationInfo::GetInstance().GetPackageName();
    auto abilityName = AceApplicationInfo::GetInstance().GetAbilityName();
    HiSysEventWrite(OHOS::HiviewDFX::HiSysEvent::Domain::ACE, eventName,
        OHOS::HiviewDFX::HiSysEvent::EventType::STATISTIC,
        EVENT_KEY_STARTTIME, startTime,
        STATISTIC_DURATION, duration,
        EVENT_KEY_VERSION_CODE, app_version_code,
        EVENT_KEY_VERSION_NAME, app_version_name,
        EVENT_KEY_BUNDLE_NAME, packageName,
        EVENT_KEY_ABILITY_NAME, abilityName,
        EVENT_KEY_PAGE_URL, pageUrl,
        EVENT_KEY_JANK_STATS, jank,
        EVENT_KEY_JANK_STATS_VER, jankStatusVersion);
}

void EventReport::SendEventInner(const EventInfo& eventInfo)
{
    auto packageName = AceApplicationInfo::GetInstance().GetPackageName();
    StrTrim(packageName);
    HiSysEventWrite(OHOS::HiviewDFX::HiSysEvent::Domain::ACE, eventInfo.eventType,
            OHOS::HiviewDFX::HiSysEvent::EventType::FAULT,
            EVENT_KEY_ERROR_TYPE, eventInfo.errorType,
            EVENT_KEY_PACKAGE_NAME, packageName);
}

void EventReport::ReportEventComplete(DataBase& data)
{
    std::string eventName = "INTERACTION_COMPLETED_LATENCY";
    const auto& appPid = data.baseInfo.pid;
    const auto& bundleName = data.baseInfo.bundleName;
    const auto& processName = data.baseInfo.processName;
    const auto& abilityName = data.baseInfo.abilityName;
    const auto& pageUrl = data.baseInfo.pageUrl;
    const auto& versionCode = data.baseInfo.versionCode;
    const auto& versionName = data.baseInfo.versionName;
    const auto& sceneId = data.sceneId;
    const auto& sourceType = GetSourceTypeName(data.sourceType);
    auto inputTime = data.inputTime;
    ConvertRealtimeToSystime(data.inputTime, inputTime);
    const auto& animationStartLantency = (data.beginVsyncTime - data.inputTime) / NS_TO_MS;
    const auto& animationEndLantency = (data.endVsyncTime - data.beginVsyncTime) / NS_TO_MS;
    const auto& e2eLatency = animationStartLantency + animationEndLantency;
    const auto& note = data.baseInfo.note;
    HiSysEventWrite(OHOS::HiviewDFX::HiSysEvent::Domain::ACE, eventName,
        OHOS::HiviewDFX::HiSysEvent::EventType::STATISTIC,
        EVENT_KEY_APP_PID, appPid,
        EVENT_KEY_BUNDLE_NAME, bundleName,
        EVENT_KEY_PROCESS_NAME, processName,
        EVENT_KEY_ABILITY_NAME, abilityName,
        EVENT_KEY_PAGE_URL, pageUrl,
        EVENT_KEY_VERSION_CODE, versionCode,
        EVENT_KEY_VERSION_NAME, versionName,
        EVENT_KEY_SCENE_ID, sceneId,
        EVENT_KEY_SOURCE_TYPE, sourceType,
        EVENT_KEY_INPUT_TIME, static_cast<uint64_t>(inputTime),
        EVENT_KEY_ANIMATION_START_LATENCY, static_cast<uint64_t>(animationStartLantency),
        EVENT_KEY_ANIMATION_END_LATENCY, static_cast<uint64_t>(animationEndLantency),
        EVENT_KEY_E2E_LATENCY, static_cast<uint64_t>(e2eLatency),
        EVENT_KEY_NOTE, note);
}

void EventReport::ReportEventJankFrame(DataBase& data)
{
    std::string eventName = "INTERACTION_APP_JANK";
    const auto& uniqueId = data.beginVsyncTime / NS_TO_MS;
    const auto& sceneId = data.sceneId;
    const auto& bundleName = data.baseInfo.bundleName;
    const auto& processName = data.baseInfo.processName;
    const auto& abilityName = data.baseInfo.abilityName;
    const auto& pageUrl = data.baseInfo.pageUrl;
    const auto& versionCode = data.baseInfo.versionCode;
    const auto& versionName = data.baseInfo.versionName;
    auto startTime = data.beginVsyncTime;
    ConvertRealtimeToSystime(data.beginVsyncTime, startTime);
    const auto& durition = (data.endVsyncTime - data.beginVsyncTime) / NS_TO_MS;
    const auto& totalFrames = data.totalFrames;
    const auto& totalMissedFrames = data.totalMissed;
    const auto& maxFrameTime = data.maxFrameTime / NS_TO_MS;
    const auto& maxSeqMissedFrames = data.maxSuccessiveFrames;
    const auto& note = data.baseInfo.note;
    HiSysEventWrite(OHOS::HiviewDFX::HiSysEvent::Domain::ACE, eventName,
        OHOS::HiviewDFX::HiSysEvent::EventType::STATISTIC,
        EVENT_KEY_UNIQUE_ID, static_cast<int32_t>(uniqueId),
        EVENT_KEY_SCENE_ID, sceneId,
        EVENT_KEY_PROCESS_NAME, processName,
        EVENT_KEY_MODULE_NAME, bundleName,
        EVENT_KEY_ABILITY_NAME, abilityName,
        EVENT_KEY_PAGE_URL, pageUrl,
        EVENT_KEY_VERSION_CODE, versionCode,
        EVENT_KEY_VERSION_NAME, versionName,
        EVENT_KEY_STARTTIME, static_cast<uint64_t>(startTime),
        EVENT_KEY_DURITION, static_cast<uint64_t>(durition),
        EVENT_KEY_TOTAL_FRAMES, totalFrames,
        EVENT_KEY_TOTAL_MISSED_FRAMES, totalMissedFrames,
        EVENT_KEY_MAX_FRAMETIME, static_cast<uint64_t>(maxFrameTime),
        EVENT_KEY_MAX_SEQ_MISSED_FRAMES, maxSeqMissedFrames,
        EVENT_KEY_NOTE, note);
}
} // namespace OHOS::Ace
