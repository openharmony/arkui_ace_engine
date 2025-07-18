/*
 * Copyright (c) 2021-2024 Huawei Device Co., Ltd.
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

#include <unistd.h>

#include "hisysevent.h"
#include "xcollie/xcollie.h"
#include "xcollie/xcollie_define.h"

#include "core/common/ace_engine.h"
#ifdef RESOURCE_SCHEDULE_SERVICE_ENABLE
#include "res_sched_client.h"
#include "res_type.h"
#endif // RESOURCE_SCHEDULE_SERVICE_ENABLE

namespace OHOS::Ace {
    FRCSceneFpsInfo EventReport::curFRCSceneFpsInfo_;
    int64_t EventReport::calTime_ = 0;
    int32_t EventReport::calFrameRate_ = 0;
    std::unordered_map<int64_t, int32_t> EventReport::formEventTimerMap_ = {};
    std::mutex EventReport::formEventTimerMutex_;
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
constexpr char EVENT_KEY_MODULE_NAME[] = "MODULE_NAME";
constexpr char ACTION_NAME[] = "ACTION_NAME";
constexpr char EVENT_KEY_PAGE_NODE_COUNT[] = "PAGE_NODE_COUNT";
constexpr char EVENT_KEY_PAGE_NODE_THRESHOLD[] = "PAGE_NODE_THRESHOLD";
constexpr char EVENT_KEY_PAGE_DEPTH[] = "PAGE_DEPTH";
constexpr char EVENT_KEY_PAGE_DEPTH_THRESHOLD[] = "PAGE_DEPTH_THRESHOLD";
constexpr char EVENT_KEY_FUNCTION_NAME[] = "FUNCTION_NAME";
constexpr char EVENT_KEY_FUNCTION_EXECUTE_TIME[] = "FUNCTION_EXECUTE_TIME";
constexpr char EVENT_KEY_FUNCTION_TIME_THRESHOLD[] = "FUNCTION_TIME_THRESHOLD";
constexpr char EVENT_KEY_NOTIFY_HOVER_STATUS_CHANGE[] = "NOTIFY_HOVER_STATUS_CHANGE";
constexpr char EVENT_KEY_FOLDER_STATUS[] = "FOLDER_STATUS";
constexpr char EVENT_KEY_HOVER_TIME[] = "HOVER_TIME";
constexpr char EVENT_KEY_IS_HOVER_MODE[] = "IS_HOVER_MODE";
constexpr char EVENT_KEY_APP_ROTATION[] = "APP_ROTATION";
constexpr char EVENT_KEY_WINDOW_MODE[] = "WINDOW_MODE";
constexpr char EVENT_KEY_NON_MANUAL_POSTCARD_ACTION[] = "NON_MANUAL_POSTCARD_ACTION";
constexpr char EVENT_KEY_TEXTFIELD_ERROR[] = "TEXTFIELD_ERROR";
constexpr char EVENT_KEY_TEXTFIELD_ERROR_TYPE[] = "TEXTFIELD_ERROR_TYPE";
constexpr char EVENT_KEY_CLIPBOARD_FAIL_TYPE[] = "EVENT_KEY_CLIPBOARD_FAIL_TYPE";
constexpr char EVENT_KEY_FRAME_NODE_ID[] = "FRAME_NODE_ID";
constexpr char EVENT_KEY_CLIPBOARD_FAIL[] = "CLIPBOARD_FAIL";
constexpr char EVENT_KEY_PAGE_NAME[] = "PAGE_NAME";
constexpr char EVENT_KEY_FORM_NAME[] = "FORM_NAME";
constexpr char EVENT_KEY_DIMENSION[] = "DIMENSION";
constexpr char EVENT_KEY_SCENE[] = "SCENE";
constexpr char EVENT_KEY_PACNAME[] = "PACNAME";
constexpr char EVENT_KEY_DURATION_60[] = "DURATION_60";
constexpr char EVENT_KEY_DURATION_72[] = "DURATION_72";
constexpr char EVENT_KEY_DURATION_90[] = "DURATION_90";
constexpr char EVENT_KEY_DURATION_120[] = "DURATION_120";
constexpr int32_t FRAME_60 = 60;
constexpr int32_t FRAME_72 = 72;
constexpr int32_t FRAME_90 = 90;
constexpr int32_t FRAME_120 = 120;

constexpr int32_t MAX_PACKAGE_NAME_LENGTH = 128;

constexpr char DUMP_LOG_COMMAND[] = "B";

constexpr char CLICK_TITLE_MAXIMIZE_MENU[] = "CLICK_TITLE_MAXIMIZE_MENU";
constexpr char DOUBLE_CLICK_TITLE[] = "DOUBLE_CLICK_TITLE";
constexpr char CURRENTPKG[] = "CURRENTPKG";
constexpr char STATECHANGE[] = "STATECHANGE";
constexpr char MAXMENUITEM[] = "MAXMENUITEM";
constexpr char SCENE_BOARD_UE_DOMAIN[] = "SCENE_BOARD_UE";
#ifdef VSYNC_TIMEOUT_CHECK
constexpr char UI_VSYNC_TIMEOUT[] = "UI_VSYNC_TIMEOUT";
constexpr char EVENT_KEY_WINDOW_ID[] = "WINDOW_ID";
constexpr char EVENT_KEY_INSTANCE_ID[] = "INSTANCE_ID";
constexpr char EVENT_KEY_VSYNC_TIMESTAMP[] = "VSYNC_TIMESTAMP";
#endif
constexpr char EVENT_KEY_RICH_EDITOR_ERROR[] = "RICH_EDITOR_ERROR";
constexpr char EVENT_KEY_SPAN_LENGTH[] = "SPAN_LENGTH";
constexpr char EVENT_KEY_TEXT_LENGTH[] = "TEXT_LENGTH";
constexpr char EVENT_KEY_SPAN_INDEX[] = "SPAN_INDEX";
constexpr char ACCESSIBILITY_FAIL[] = "ACCESSIBILITY_FAIL";
constexpr char PAGE_NODE_OVERFLOW[] = "PAGE_NODE_OVERFLOW";
constexpr char PAGE_DEPTH_OVERFLOW[] = "PAGE_DEPTH_OVERFLOW";
constexpr char UI_LIFECIRCLE_FUNCTION_TIMEOUT[] = "UI_LIFECIRCLE_FUNCTION_TIMEOUT";
constexpr char UIEXTENSION_TRANSPARENT_DETECTED[] = "UIEXTENSION_TRANSPARENT_DETECTED";
constexpr char EVENT_KEY_SCROLLABLE_ERROR[] = "SCROLLABLE_ERROR";
constexpr char EVENT_KEY_NODE_TYPE[] = "NODE_TYPE";
constexpr char EVENT_KEY_SUB_ERROR_TYPE[] = "SUB_ERROR_TYPE";
constexpr char EVENT_KEY_TARGET_API_VERSION[] = "TARGET_API_VERSION";
constexpr char EVENT_KEY_REUSED_NODE_SKIP_MEASURE[] = "REUSED_NODE_SKIP_MEASURE";
constexpr char EVENT_KEY_PAGE_SLID_INFO[] = "PAGE_SLID_INFO";
constexpr char EVENT_KEY_GESTURE_VELOCITY[] = "GESTURE_VELOCITY";
constexpr char EVENT_KEY_VELOCITY_SCALE[] = "VELOCITY_SCALE";
constexpr char EVENT_KEY_DRAG_GAIN[] = "DRAG_GAIN";
constexpr char EVENT_KEY_MAX_FLING_VELOCITY[] = "MAX_FLING_VELOCITY";
constexpr char EVENT_KEY_SLIP_FACTOR[] = "SLIP_FACTOR";
constexpr char EVENT_KEY_FRICTION[] = "FRICTION";
constexpr char EVENT_KEY_FORM_ID[] = "FORM_ID";
constexpr char EVENT_KEY_ERROR_NAME[] = "ERROR_NAME";
constexpr char EVENT_KEY_ERROR_CODE[] = "ERROR_CODE";
constexpr char FORM_NODE_ERROR[] = "FORM_NODE_ERROR";
constexpr int32_t WAIT_MODIFY_TIMEOUT = 10;
constexpr int32_t WAIT_MODIFY_FAILED = 1;

void StrTrim(std::string& str)
{
    if (str.size() > MAX_PACKAGE_NAME_LENGTH) {
        str = str.substr(0, MAX_PACKAGE_NAME_LENGTH);
    }
}

} // namespace

void EventReport::SendEvent(const EventInfo& eventInfo)
{
    auto packageName = Container::CurrentBundleName();
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

void EventReport::FrameRateDurationsStatistics(int32_t expectedRate, const std::string& scene, NG::SceneStatus status)
{
    switch (status) {
        case NG::SceneStatus::START: {
            curFRCSceneFpsInfo_ = FRCSceneFpsInfo();
            calTime_ = 0;
            calFrameRate_ = 0;
            return;
        }
        case NG::SceneStatus::RUNNING: {
            if (calTime_ == 0) {
                calTime_ = GetSysTimestamp();
                calFrameRate_ = expectedRate;
            }
            if (expectedRate != calFrameRate_) {
                int64_t endTime = GetSysTimestamp();
                int64_t duration = endTime - calTime_;
                calTime_ = endTime;
            AddFrameRateDuration(calFrameRate_, duration);
            }
            calFrameRate_ = expectedRate;
            return;
        }
        case NG::SceneStatus::END: {
            int64_t endTime = GetSysTimestamp();
            int64_t duration = endTime - calTime_;
            calTime_ = endTime;
            AddFrameRateDuration(calFrameRate_, duration);
            EventReport::SendDiffFrameRatesDuring(scene, curFRCSceneFpsInfo_);
            return;
        }
        default:
            return;
    }
}

void EventReport::AddFrameRateDuration(int32_t frameRate, int64_t duration)
{
    switch (frameRate) {
        case FRAME_120: {
            curFRCSceneFpsInfo_.duration_120 += duration;
            break;
        }
        case FRAME_90: {
            curFRCSceneFpsInfo_.duration_90 += duration;
            break;
        }
        case FRAME_72: {
            curFRCSceneFpsInfo_.duration_72 += duration;
            break;
        }
        case FRAME_60: {
            curFRCSceneFpsInfo_.duration_60 += duration;
            break;
        }
        default:
            break;
    }
}

void EventReport::SendDiffFrameRatesDuring(const std::string& scene, const FRCSceneFpsInfo& curFRCSceneFpsInfo_)
{
    auto packageName = Container::CurrentBundleName();
    std::string eventName = "FRC_SCENE_INFO";
    if (packageName.size() > MAX_PACKAGE_NAME_LENGTH) {
        StrTrim(packageName);
    }
    int32_t frameRateDuring_60_ms = static_cast<int32_t>(curFRCSceneFpsInfo_.duration_60 / NS_TO_MS);
    int32_t frameRateDuring_72_ms = static_cast<int32_t>(curFRCSceneFpsInfo_.duration_72 / NS_TO_MS);
    int32_t frameRateDuring_90_ms = static_cast<int32_t>(curFRCSceneFpsInfo_.duration_90 / NS_TO_MS);
    int32_t frameRateDuring_120_ms = static_cast<int32_t>(curFRCSceneFpsInfo_.duration_120 / NS_TO_MS);
    HiSysEventWrite(OHOS::HiviewDFX::HiSysEvent::Domain::ACE, eventName,
        OHOS::HiviewDFX::HiSysEvent::EventType::BEHAVIOR,
        EVENT_KEY_SCENE, scene,
        EVENT_KEY_PACNAME, packageName,
        EVENT_KEY_DURATION_120, frameRateDuring_120_ms,
        EVENT_KEY_DURATION_90, frameRateDuring_90_ms,
        EVENT_KEY_DURATION_72, frameRateDuring_72_ms,
        EVENT_KEY_DURATION_60, frameRateDuring_60_ms);
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

void EventReport::ReportAccessibilityFailEvent(const std::string& actionName)
{
    auto packageName = Container::CurrentBundleName();
    auto abilityName = AceApplicationInfo::GetInstance().GetAbilityName();
    auto processName = AceApplicationInfo::GetInstance().GetProcessName();
    HiSysEventWrite(OHOS::HiviewDFX::HiSysEvent::Domain::ACE, ACCESSIBILITY_FAIL,
        OHOS::HiviewDFX::HiSysEvent::EventType::FAULT,
        EVENT_KEY_BUNDLE_NAME, packageName,
        EVENT_KEY_ABILITY_NAME, abilityName,
        EVENT_KEY_PROCESS_NAME, processName,
        ACTION_NAME, actionName);
}

void EventReport::SendFormException(FormExcepType type)
{
    EventInfo eventInfo = {
        .eventType = EXCEPTION_FORM,
        .errorType = static_cast<int32_t>(type),
    };

    SendEventInner(eventInfo);
}

#ifdef VSYNC_TIMEOUT_CHECK
void EventReport::SendVsyncException(VsyncExcepType type, uint32_t windowId, int32_t instanceId, uint64_t timeStamp)
{
    auto packageName = Container::CurrentBundleName();
    StrTrim(packageName);
    HiSysEventWrite(OHOS::HiviewDFX::HiSysEvent::Domain::ACE, UI_VSYNC_TIMEOUT,
        OHOS::HiviewDFX::HiSysEvent::EventType::FAULT,
        EVENT_KEY_ERROR_TYPE, static_cast<int32_t>(type),
        EVENT_KEY_PACKAGE_NAME, packageName,
        EVENT_KEY_WINDOW_ID, windowId,
        EVENT_KEY_INSTANCE_ID, instanceId,
        EVENT_KEY_VSYNC_TIMESTAMP, timeStamp);
}
#endif

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
    auto packageName = Container::CurrentBundleName();
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
    auto packageName = Container::CurrentBundleName();
    StrTrim(packageName);
    HiSysEventWrite(OHOS::HiviewDFX::HiSysEvent::Domain::ACE, eventInfo.eventType,
            OHOS::HiviewDFX::HiSysEvent::EventType::FAULT,
            EVENT_KEY_ERROR_TYPE, eventInfo.errorType,
            EVENT_KEY_PACKAGE_NAME, packageName);
}

void EventReport::ReportDragInfo(const DragInfo& dragInfo)
{
    HiSysEventWrite(
        OHOS::HiviewDFX::HiSysEvent::Domain::DRAG_UE,
        dragInfo.dragBehavior,
        OHOS::HiviewDFX::HiSysEvent::EventType::BEHAVIOR,
        "PNAMEID", dragInfo.pNameId,
        "PVERSIONID", dragInfo.pVersionId,
        "ISCROSSING", dragInfo.isCrossing,
        "RESULT", dragInfo.result,
        "HOSTNAME", dragInfo.hostName,
        "SUMMARYTYPE", dragInfo.summaryType,
        "SUMMARYNUM", dragInfo.summaryNum,
        "ALLOW_DROP_TYPE", dragInfo.allowDropType);
}

void EventReport::ReportRichEditorInfo(const RichEditorInfo& richEditorInfo)
{
    auto packageName = Container::CurrentBundleName();
    auto appVersionCode = AceApplicationInfo::GetInstance().GetAppVersionCode();
    auto appVersionName = AceApplicationInfo::GetInstance().GetAppVersionName();
    StrTrim(packageName);
    StrTrim(appVersionName);
    HiSysEventWrite(
        OHOS::HiviewDFX::HiSysEvent::Domain::ACE, EVENT_KEY_RICH_EDITOR_ERROR,
        OHOS::HiviewDFX::HiSysEvent::EventType::FAULT,
        EVENT_KEY_BUNDLE_NAME, packageName,
        EVENT_KEY_VERSION_CODE, appVersionCode,
        EVENT_KEY_VERSION_NAME, appVersionName,
        EVENT_KEY_ERROR_TYPE, static_cast<int32_t>(richEditorInfo.errorType),
        EVENT_KEY_SPAN_LENGTH, richEditorInfo.spanLength,
        EVENT_KEY_TEXT_LENGTH, richEditorInfo.textLength,
        EVENT_KEY_SPAN_INDEX, richEditorInfo.spanIndex);
}

void EventReport::ReportDoubleClickTitle(int32_t stateChange)
{
    auto packageName = Container::CurrentBundleName();
    StrTrim(packageName);
    HiSysEventWrite(SCENE_BOARD_UE_DOMAIN, DOUBLE_CLICK_TITLE,
        OHOS::HiviewDFX::HiSysEvent::EventType::BEHAVIOR,
        CURRENTPKG, packageName,
        STATECHANGE, stateChange);
}

void EventReport::ReportClickTitleMaximizeMenu(int32_t maxMenuItem, int32_t stateChange)
{
    auto packageName = Container::CurrentBundleName();
    StrTrim(packageName);
    HiSysEventWrite(SCENE_BOARD_UE_DOMAIN, CLICK_TITLE_MAXIMIZE_MENU,
        OHOS::HiviewDFX::HiSysEvent::EventType::BEHAVIOR,
        CURRENTPKG, packageName,
        MAXMENUITEM, maxMenuItem,
        STATECHANGE, stateChange);
}

void EventReport::ReportPageNodeOverflow(const std::string& pageUrl, int32_t nodeCount, int32_t threshold)
{
    auto packageName = Container::CurrentBundleName();
    StrTrim(packageName);
    HiSysEventWrite(OHOS::HiviewDFX::HiSysEvent::Domain::ACE, PAGE_NODE_OVERFLOW,
        OHOS::HiviewDFX::HiSysEvent::EventType::FAULT,
        EVENT_KEY_PACKAGE_NAME, packageName,
        EVENT_KEY_PAGE_URL, pageUrl,
        EVENT_KEY_PAGE_NODE_COUNT, nodeCount,
        EVENT_KEY_PAGE_NODE_THRESHOLD, threshold);
}

void EventReport::ReportPageDepthOverflow(const std::string& pageUrl, int32_t depth, int32_t threshold)
{
    auto packageName = Container::CurrentBundleName();
    StrTrim(packageName);
    HiSysEventWrite(OHOS::HiviewDFX::HiSysEvent::Domain::ACE, PAGE_DEPTH_OVERFLOW,
        OHOS::HiviewDFX::HiSysEvent::EventType::FAULT,
        EVENT_KEY_PACKAGE_NAME, packageName,
        EVENT_KEY_PAGE_URL, pageUrl,
        EVENT_KEY_PAGE_DEPTH, depth,
        EVENT_KEY_PAGE_DEPTH_THRESHOLD, threshold);
}

void EventReport::ReportFunctionTimeout(const std::string& functionName, int64_t time, int32_t threshold)
{
    auto packageName = Container::CurrentBundleName();
    StrTrim(packageName);
    HiSysEventWrite(OHOS::HiviewDFX::HiSysEvent::Domain::ACE, UI_LIFECIRCLE_FUNCTION_TIMEOUT,
        OHOS::HiviewDFX::HiSysEvent::EventType::FAULT,
        EVENT_KEY_PACKAGE_NAME, packageName,
        EVENT_KEY_FUNCTION_NAME, functionName,
        EVENT_KEY_FUNCTION_EXECUTE_TIME, time,
        EVENT_KEY_FUNCTION_TIME_THRESHOLD, threshold);
}

void EventReport::ReportHoverStatusChange(
    int32_t foldStatus, int32_t time, bool isHoverMode, int32_t appRotation, int32_t windowMode)
{
    auto packageName = Container::CurrentBundleName();
    auto abilityName = AceApplicationInfo::GetInstance().GetAbilityName();
    HiSysEventWrite(OHOS::HiviewDFX::HiSysEvent::Domain::ACE, EVENT_KEY_NOTIFY_HOVER_STATUS_CHANGE,
        OHOS::HiviewDFX::HiSysEvent::EventType::BEHAVIOR,
        EVENT_KEY_BUNDLE_NAME, packageName,
        EVENT_KEY_ABILITY_NAME, abilityName,
        EVENT_KEY_FOLDER_STATUS, foldStatus,
        EVENT_KEY_HOVER_TIME, time,
        EVENT_KEY_IS_HOVER_MODE, isHoverMode,
        EVENT_KEY_WINDOW_MODE, windowMode,
        EVENT_KEY_APP_ROTATION, appRotation);
}

void EventReport::ReportNonManualPostCardActionInfo(const std::string& formName, const std::string& bundleName,
    const std::string& abilityName, const std::string& moduleName, int32_t dimension)
{
    HiSysEventWrite(OHOS::HiviewDFX::HiSysEvent::Domain::ACE, EVENT_KEY_NON_MANUAL_POSTCARD_ACTION,
        OHOS::HiviewDFX::HiSysEvent::EventType::BEHAVIOR,
        EVENT_KEY_FORM_NAME, formName,
        EVENT_KEY_BUNDLE_NAME, bundleName,
        EVENT_KEY_ABILITY_NAME, abilityName,
        EVENT_KEY_MODULE_NAME, moduleName,
        EVENT_KEY_DIMENSION, dimension);
}

void EventReport::ReportUiExtensionTransparentEvent(const std::string& pageUrl, const std::string& bundleName,
    const std::string& moduleName)
{
    auto app_version_code = AceApplicationInfo::GetInstance().GetAppVersionCode();
    auto app_version_name = AceApplicationInfo::GetInstance().GetAppVersionName();
    HiSysEventWrite(OHOS::HiviewDFX::HiSysEvent::Domain::ACE, UIEXTENSION_TRANSPARENT_DETECTED,
        OHOS::HiviewDFX::HiSysEvent::EventType::FAULT,
        EVENT_KEY_PAGE_NAME, pageUrl,
        EVENT_KEY_VERSION_CODE, app_version_code,
        EVENT_KEY_VERSION_NAME, app_version_name,
        EVENT_KEY_BUNDLE_NAME, bundleName,
        EVENT_KEY_MODULE_NAME, moduleName);
}

void EventReport::ReportScrollableErrorEvent(
    const std::string& nodeType, ScrollableErrorType errorType, const std::string& subErrorType)
{
    auto packageName = Container::CurrentBundleName();
    auto app_version_code = AceApplicationInfo::GetInstance().GetAppVersionCode();
    auto app_version_name = AceApplicationInfo::GetInstance().GetAppVersionName();
    auto target_api_version = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    StrTrim(packageName);
    StrTrim(app_version_name);
    HiSysEventWrite(OHOS::HiviewDFX::HiSysEvent::Domain::ACE, EVENT_KEY_SCROLLABLE_ERROR,
        OHOS::HiviewDFX::HiSysEvent::EventType::FAULT,
        EVENT_KEY_NODE_TYPE, nodeType,
        EVENT_KEY_ERROR_TYPE, static_cast<int32_t>(errorType),
        EVENT_KEY_SUB_ERROR_TYPE, subErrorType,
        EVENT_KEY_BUNDLE_NAME, packageName,
        EVENT_KEY_TARGET_API_VERSION, target_api_version,
        EVENT_KEY_VERSION_CODE, app_version_code,
        EVENT_KEY_VERSION_NAME, app_version_name);
}

void EventReport::ReportTextFieldErrorEvent(int32_t frameNodeId, int32_t depth, const std::string& errorType)
{
    auto packageName = Container::CurrentBundleName();
    HiSysEventWrite(OHOS::HiviewDFX::HiSysEvent::Domain::ACE, EVENT_KEY_TEXTFIELD_ERROR,
        OHOS::HiviewDFX::HiSysEvent::EventType::FAULT, EVENT_KEY_PACKAGE_NAME, packageName, EVENT_KEY_FRAME_NODE_ID,
        frameNodeId, EVENT_KEY_PAGE_DEPTH, depth, EVENT_KEY_TEXTFIELD_ERROR_TYPE, errorType);
}

void EventReport::ReportClipboardFailEvent(const std::string& errorType)
{
    auto packageName = Container::CurrentBundleName();
    HiSysEventWrite(OHOS::HiviewDFX::HiSysEvent::Domain::ACE, EVENT_KEY_CLIPBOARD_FAIL,
        OHOS::HiviewDFX::HiSysEvent::EventType::FAULT, EVENT_KEY_PACKAGE_NAME, packageName,
        EVENT_KEY_CLIPBOARD_FAIL_TYPE, errorType);
}

void EventReport::ReportReusedNodeSkipMeasureApp()
{
    auto progressName = AceApplicationInfo::GetInstance().GetProcessName();
    HiSysEventWrite(OHOS::HiviewDFX::HiSysEvent::Domain::ACE, EVENT_KEY_REUSED_NODE_SKIP_MEASURE,
        OHOS::HiviewDFX::HiSysEvent::EventType::STATISTIC, EVENT_KEY_PACKAGE_NAME, progressName);
}

void EventReport::ReportPageSlidInfo(NG::SlidInfo &slidInfo)
{
    HiSysEventWrite(OHOS::HiviewDFX::HiSysEvent::Domain::ACE, EVENT_KEY_PAGE_SLID_INFO,
        OHOS::HiviewDFX::HiSysEvent::EventType::BEHAVIOR,
        EVENT_KEY_GESTURE_VELOCITY, slidInfo.gestureVelocity,
        EVENT_KEY_VELOCITY_SCALE, slidInfo.velocityScale, EVENT_KEY_DRAG_GAIN,
        slidInfo.gain, EVENT_KEY_MAX_FLING_VELOCITY, slidInfo.maxFlingVelocity,
        EVENT_KEY_SLIP_FACTOR, slidInfo.slipFactor, EVENT_KEY_FRICTION,
        slidInfo.friction);
}

void EventReport::StartFormModifyTimeoutReportTimer(int64_t formId, const std::string &bundleName,
    const std::string &formName)
{
    auto timeoutCallback = [formId, bundleName, formName](void *) {
        LOGE("ModifyTimeout, cardId: %{public}" PRId64, formId);
        HiSysEventWrite(
            OHOS::HiviewDFX::HiSysEvent::Domain::FORM_MANAGER,
            "FORM_ERROR",
            OHOS::HiviewDFX::HiSysEvent::EventType::FAULT,
            EVENT_KEY_FORM_ID, formId,
            EVENT_KEY_BUNDLE_NAME, bundleName,
            EVENT_KEY_FORM_NAME, formName,
            EVENT_KEY_ERROR_NAME, FORM_NODE_ERROR,
            EVENT_KEY_ERROR_TYPE, WAIT_MODIFY_FAILED,
            EVENT_KEY_ERROR_CODE, 0);
    };
    const std::string taskName = "FormPattern_WaitModifyDone_" + std::to_string(formId);
    EventReport::StopFormModifyTimeoutReportTimer(formId);
    int32_t timerId = OHOS::HiviewDFX::XCollie::GetInstance().SetTimer(
        taskName, WAIT_MODIFY_TIMEOUT, timeoutCallback, nullptr, HiviewDFX::XCOLLIE_FLAG_NOOP);
    std::lock_guard<std::mutex> lock(EventReport::formEventTimerMutex_);
    EventReport::formEventTimerMap_[formId] = timerId;
    LOGI("StartFormModifyTimeoutReportTimer, cardId: %{public}" PRId64 ", timerId: %{public}d", formId, timerId);
}

void EventReport::StopFormModifyTimeoutReportTimer(int64_t formId)
{
    std::lock_guard<std::mutex> lock(EventReport::formEventTimerMutex_);
    auto iter = EventReport::formEventTimerMap_.find(formId);
    if (iter == EventReport::formEventTimerMap_.end()) {
        return;
    }
    int32_t timerId = iter->second;
    LOGI("StopFormModifyTimeoutReportTimer, timerId:%{public}d", timerId);
    OHOS::HiviewDFX::XCollie::GetInstance().CancelTimer(timerId);
    EventReport::formEventTimerMap_.erase(iter);
}

} // namespace OHOS::Ace
