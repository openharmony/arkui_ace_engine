/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include "base/perfmonitor/perf_monitor.h"

#include "base/log/ace_trace.h"
#include "base/log/event_report.h"
#include "base/perfmonitor/perf_constants.h"
#include "base/perfmonitor/perf_interfaces.h"
#include "base/ressched/ressched_report.h"
#include "base/utils/system_properties.h"
#include "core/common/ace_application_info.h"
#include "render_service_client/core/transaction/rs_interfaces.h"
#ifdef OHOS_STANDARD_SYSTEM
#include "event_handler.h"
#endif

namespace OHOS::Ace {
using namespace std;
PerfMonitor* PerfMonitor::pMonitor = nullptr;
std::once_flag PerfMonitor::initFlag;
constexpr int64_t SCENE_TIMEOUT = 10000000000;
constexpr int64_t RESPONSE_TIMEOUT = 600000000;
constexpr int64_t STARTAPP_FRAME_TIMEOUT = 1000000000;
constexpr float SINGLE_FRAME_TIME = 16600000;
const int32_t JANK_SKIPPED_THRESHOLD = SystemProperties::GetJankFrameThreshold();
const int32_t DEFAULT_JANK_REPORT_THRESHOLD = 3;
constexpr uint32_t DEFAULT_VSYNC = 16;
// Obtain the last three digits of the full path
constexpr uint32_t PATH_DEPTH = 3;

constexpr uint32_t JANK_FRAME_6_LIMIT = 0;
constexpr uint32_t JANK_FRAME_15_LIMIT = 1;
constexpr uint32_t JANK_FRAME_20_LIMIT = 2;
constexpr uint32_t JANK_FRAME_36_LIMIT = 3;
constexpr uint32_t JANK_FRAME_48_LIMIT = 4;
constexpr uint32_t JANK_FRAME_60_LIMIT = 5;
constexpr uint32_t JANK_FRAME_120_LIMIT = 6;
constexpr uint32_t JANK_FRAME_180_LIMIT = 7;
constexpr uint32_t JANK_STATS_SIZE = 8;

uint32_t GetJankLimit(double jank)
{
    if (jank < 6.0f) {
        return JANK_FRAME_6_LIMIT;
    }
    if (jank < 15.0f) {
        return JANK_FRAME_15_LIMIT;
    }
    if (jank < 20.0f) {
        return JANK_FRAME_20_LIMIT;
    }
    if (jank < 36.0f) {
        return JANK_FRAME_36_LIMIT;
    }
    if (jank < 48.0f) {
        return JANK_FRAME_48_LIMIT;
    }
    if (jank < 60.0f) {
        return JANK_FRAME_60_LIMIT;
    }
    if (jank < 120.0f) {
        return JANK_FRAME_120_LIMIT;
    }
    return JANK_FRAME_180_LIMIT;
}

std::string ParsePageUrl(const std::string& pagePath)
{
    std::string res;
    std::vector<std::string> paths;
    StringUtils::StringSplitter(pagePath, '/', paths);
    uint32_t pathSize = paths.size();
    if (pathSize < PATH_DEPTH) {
        return pagePath;
    }
    for (uint32_t i = pathSize - PATH_DEPTH; i < pathSize; i++) {
        res = res + "/" + paths[i];
    }
    return res;
}

static int64_t GetCurrentRealTimeNs()
{
    struct timespec ts = { 0, 0 };
    if (clock_gettime(CLOCK_MONOTONIC, &ts) != 0) {
        return 0;
    }
    return (ts.tv_sec * NS_TO_S + ts.tv_nsec);
}

static int64_t GetCurrentSystimeMs()
{
    auto timeNow = std::chrono::system_clock::now();
    auto tmp = std::chrono::duration_cast<std::chrono::milliseconds>(timeNow.time_since_epoch());
    int64_t curSystime = tmp.count();
    return curSystime;
}

void ConvertRealtimeToSystime(int64_t realTime, int64_t& sysTime)
{
    int64_t curRealTime = GetCurrentRealTimeNs();
    if (curRealTime == 0) {
        sysTime = 0;
        return;
    }
    int64_t curSysTime = GetCurrentSystimeMs();
    sysTime = curSysTime - (curRealTime - realTime) / NS_TO_MS;
}

std::string GetSourceTypeName(PerfSourceType sourceType)
{
    std::string type = "";
    switch (sourceType) {
        case PERF_TOUCH_EVENT:
            type = "TOUCHSCREEN";
            break;
        case PERF_MOUSE_EVENT:
            type = "MOUSE";
            break;
        case PERF_TOUCH_PAD:
            type = "TOUCHPAD";
            break;
        case PERF_JOY_STICK:
            type = "JOYSTICK";
            break;
        case PERF_KEY_EVENT:
            type = "KEY_EVENT";
            break;
        default :
            type = "UNKNOWN_SOURCE";
            break;
    }
    return type;
}

void ConvertToRsData(OHOS::Rosen::DataBaseRs &dataRs, DataBase& data)
{
    dataRs.eventType = static_cast<int32_t>(data.eventType);
    dataRs.sceneId = data.sceneId;
    dataRs.appPid = data.baseInfo.pid;
    dataRs.uniqueId = data.beginVsyncTime / NS_TO_MS;
    dataRs.inputTime = data.inputTime;
    dataRs.beginVsyncTime = data.beginVsyncTime;
    dataRs.endVsyncTime = data.endVsyncTime;
    dataRs.versionCode = data.baseInfo.versionCode;
    dataRs.versionName = data.baseInfo.versionName;
    dataRs.bundleName = data.baseInfo.bundleName;
    dataRs.processName = data.baseInfo.processName;
    dataRs.abilityName = data.baseInfo.abilityName;
    dataRs.pageUrl = data.baseInfo.pageUrl;
    dataRs.sourceType = GetSourceTypeName(data.sourceType);
    dataRs.note = data.baseInfo.note;
    dataRs.isDisplayAnimator = data.isDisplayAnimator;
}

void ReportPerfEventToRS(DataBase& data)
{
    OHOS::Rosen::DataBaseRs dataRs;
    ConvertToRsData(dataRs, data);
    switch (dataRs.eventType) {
        case EVENT_RESPONSE:
            {
                ACE_SCOPED_TRACE("EVENT_REPORT_RESPONSE_RS sceneId = %s, uniqueId = %lld",
                    dataRs.sceneId.c_str(), static_cast<long long> (dataRs.uniqueId));
                Rosen::RSInterfaces::GetInstance().ReportEventResponse(dataRs);
                break;
            }
        case EVENT_COMPLETE:
            {
                if (data.needReportRs) {
                    ACE_SCOPED_TRACE("EVENT_REPORT_COMPLETE_RS sceneId = %s, uniqueId = %lld",
                        dataRs.sceneId.c_str(), static_cast<long long> (dataRs.uniqueId));
                    Rosen::RSInterfaces::GetInstance().ReportEventComplete(dataRs);
                }
                break;
            }
        case EVENT_JANK_FRAME:
            {
                ACE_SCOPED_TRACE("EVENT_REPORT_JANK_RS sceneId = %s, uniqueId = %lld",
                    dataRs.sceneId.c_str(), static_cast<long long> (dataRs.uniqueId));
                Rosen::RSInterfaces::GetInstance().ReportEventJankFrame(dataRs);
                break;
            }
        default :
            break;
    }
}

void ReportPerfEventToUI(DataBase data)
{
    switch (data.eventType) {
        case EVENT_COMPLETE:
            if (!data.needReportRs) {
                EventReport::ReportEventComplete(data);
            }
            break;
        case EVENT_JANK_FRAME:
            if (data.totalFrames > 0) {
                EventReport::ReportEventJankFrame(data);
            }
            break;
        default :
            break;
    }
}

void SceneRecord::InitRecord(const std::string& sId, PerfActionType aType, PerfSourceType sType, const std::string& nt,
    int64_t time)
{
    sceneId = sId;
    actionType = aType;
    sourceType = sType;
    note = nt;
    inputTime = time;
    beginVsyncTime = GetCurrentRealTimeNs();
    isDisplayAnimator = IsDisplayAnimator(sceneId);
}

bool SceneRecord::IsTimeOut(int64_t nowTime)
{
    if (nowTime - beginVsyncTime > SCENE_TIMEOUT) {
        return true;
    }
    return false;
}

void SceneRecord::RecordFrame(int64_t vsyncTime, int64_t duration, int32_t skippedFrames)
{
    int64_t currentTimeNs = GetCurrentRealTimeNs();
    if (totalFrames == 0) {
        beginVsyncTime = currentTimeNs;
        isFirstFrame = true;
    } else {
        isFirstFrame = false;
    }
    skippedFrames = static_cast<int32_t>(duration / SINGLE_FRAME_TIME);
    if (!isFirstFrame && skippedFrames >= 1) {
        if (isSuccessive) {
            seqMissFrames = seqMissFrames + skippedFrames;
        } else {
            seqMissFrames = skippedFrames;
            isSuccessive = true;
        }
        if (maxSuccessiveFrames < seqMissFrames) {
            maxSuccessiveFrames = seqMissFrames;
        }
        totalMissed += skippedFrames;
    } else {
        isSuccessive = false;
        seqMissFrames = 0;
    }
    if (!isFirstFrame && duration > maxFrameTime) {
        maxFrameTime = duration;
        maxFrameTimeSinceStart = (currentTimeNs - beginVsyncTime) / NS_TO_MS;
    }
    totalFrames++;
}

void SceneRecord::Report(const std::string& sceneId, int64_t vsyncTime, bool isRsRender)
{
    if (isRsRender || vsyncTime <= beginVsyncTime) {
        endVsyncTime = GetCurrentRealTimeNs();
    } else {
        endVsyncTime = vsyncTime;
    }
    needReportRs = !isRsRender;
}

bool SceneRecord::IsFirstFrame()
{
    return isFirstFrame;
}

bool SceneRecord::IsDisplayAnimator(const std::string& sceneId)
{
    if (sceneId == PerfConstants::APP_LIST_FLING || sceneId == PerfConstants::APP_SWIPER_SCROLL
        || sceneId == PerfConstants::SNAP_RECENT_ANI
        || sceneId == PerfConstants::WINDOW_RECT_RESIZE
        || sceneId == PerfConstants::WINDOW_RECT_MOVE
        || sceneId == PerfConstants::META_BALLS_TURBO_CHARGING_ANIMATION
        || sceneId == PerfConstants::ABILITY_OR_PAGE_SWITCH_INTERACTIVE
        || sceneId == PerfConstants::LAUNCHER_SPRINGBACK_SCROLL) {
        return true;
    }
    return false;
}

void SceneRecord::Reset()
{
    beginVsyncTime = 0;
    endVsyncTime = 0;
    maxFrameTime = 0;
    maxFrameTimeSinceStart = 0;
    maxHitchTime = 0;
    maxHitchTimeSinceStart = 0;
    maxSuccessiveFrames = 0;
    seqMissFrames = 0;
    totalMissed = 0;
    totalFrames = 0;
    isSuccessive = false;
    isFirstFrame = false;
    sceneId = "";
    actionType = UNKNOWN_ACTION;
    sourceType = UNKNOWN_SOURCE;
    note = "";
}

PerfMonitor* PerfMonitor::GetPerfMonitor()
{
    std::call_once(initFlag, &PerfMonitor::InitInstance);
    return pMonitor;
}

void PerfMonitor::InitInstance()
{
    pMonitor = new PerfMonitor();
}

void PerfMonitor::Start(const std::string& sceneId, PerfActionType type, const std::string& note)
{
    std::lock_guard<std::mutex> Lock(mMutex);
    if (IsScrollJank(sceneId)) {
        PerfInterfaces::SetScrollState(true);
    }
    NotifySdbJankStatsEnd(sceneId);
    if (apsMonitor_ != nullptr) {
        apsMonitor_->SetApsScene(sceneId, true);
    }

    int64_t inputTime = GetInputTime(sceneId, type, note);
    SceneRecord* record = GetRecord(sceneId);
    if (IsSceneIdInSceneWhiteList(sceneId)) {
        isExceptAnimator = true;
        SetVsyncLazyMode();
    }
    ACE_SCOPED_TRACE("Animation start and current sceneId=%s", sceneId.c_str());
    if (record == nullptr) {
        currentSceneId = sceneId;
        record = new SceneRecord();
        record->InitRecord(sceneId, type, mSourceType, note, inputTime);
        mRecords.insert(std::pair<std::string, SceneRecord*> (sceneId, record));
        RecordBaseInfo(record);
        AceAsyncTraceBegin(0, sceneId.c_str());
    }
    if (sceneId == PerfConstants::ABILITY_OR_PAGE_SWITCH) {
        ResSchedReport::GetInstance().ResSchedDataReport("ability_or_page_switch_start");
    }
}

void PerfMonitor::StartCommercial(const std::string& sceneId, PerfActionType type, const std::string& note)
{
    std::lock_guard<std::mutex> Lock(mMutex);
    if (IsScrollJank(sceneId)) {
        PerfInterfaces::SetScrollState(true);
    }
    if (apsMonitor_ != nullptr) {
        apsMonitor_->SetApsScene(sceneId, true);
    }

    int64_t inputTime = GetInputTime(sceneId, type, note);
    SceneRecord* record = GetRecord(sceneId);
    if (IsSceneIdInSceneWhiteList(sceneId)) {
        isExceptAnimator = true;
    }
    ACE_SCOPED_TRACE_COMMERCIAL("Animation start and current sceneId=%s", sceneId.c_str());
    if (record == nullptr) {
        currentSceneId = sceneId;
        record = new SceneRecord();
        record->InitRecord(sceneId, type, mSourceType, note, inputTime);
        mRecords.insert(std::pair<std::string, SceneRecord*> (sceneId, record));
        RecordBaseInfo(record);
        AceAsyncTraceBeginCommercial(0, sceneId.c_str());
    }
}

void PerfMonitor::End(const std::string& sceneId, bool isRsRender)
{
    std::lock_guard<std::mutex> Lock(mMutex);
    if (IsScrollJank(sceneId)) {
        PerfInterfaces::SetScrollState(false);
    }
    NotifySbdJankStatsBegin(sceneId);
    if (apsMonitor_ != nullptr) {
        apsMonitor_->SetApsScene(sceneId, false);
    }

    SceneRecord* record = GetRecord(sceneId);
    ACE_SCOPED_TRACE("Animation end and current sceneId=%s", sceneId.c_str());
    if (record != nullptr) {
        if (IsSceneIdInSceneWhiteList(sceneId)) {
            isExceptAnimator = false;
            SetVsyncLazyMode();
        }
        RecordBaseInfo(record);
        record->Report(sceneId, mVsyncTime, isRsRender);
        ReportAnimateEnd(sceneId, record);
        RemoveRecord(sceneId);
        AceAsyncTraceEnd(0, sceneId.c_str());
    }
    if (sceneId == PerfConstants::ABILITY_OR_PAGE_SWITCH) {
        ResSchedReport::GetInstance().ResSchedDataReport("ability_or_page_switch_end");
    }
}

void PerfMonitor::EndCommercial(const std::string& sceneId, bool isRsRender)
{
    std::lock_guard<std::mutex> Lock(mMutex);
    if (IsScrollJank(sceneId)) {
        PerfInterfaces::SetScrollState(false);
    }
    if (apsMonitor_ != nullptr) {
        apsMonitor_->SetApsScene(sceneId, false);
    }

    SceneRecord* record = GetRecord(sceneId);
    ACE_SCOPED_TRACE_COMMERCIAL("Animation end and current sceneId=%s", sceneId.c_str());
    if (record != nullptr) {
        if (IsSceneIdInSceneWhiteList(sceneId)) {
            isExceptAnimator = false;
        }
        RecordBaseInfo(record);
        record->Report(sceneId, mVsyncTime, isRsRender);
        ReportAnimateEnd(sceneId, record);
        RemoveRecord(sceneId);
        AceAsyncTraceEndCommercial(0, sceneId.c_str());
    }
}

void PerfMonitor::RecordInputEvent(PerfActionType type, PerfSourceType sourceType, int64_t time)
{
    std::lock_guard<std::mutex> Lock(mMutex);
    mSourceType = sourceType;
    if (time <= 0) {
        time = GetCurrentRealTimeNs();
    }
    switch (type) {
        case LAST_DOWN:
            {
                ACE_SCOPED_TRACE("RecordInputEvent: last_down=%lld(ns)", static_cast<long long>(time));
                mInputTime[LAST_DOWN] = time;
                break;
            }
        case LAST_UP:
            {
                ACE_SCOPED_TRACE("RecordInputEvent: last_up=%lld(ns)", static_cast<long long>(time));
                mInputTime[LAST_UP] = time;
                isResponseExclusion = true;
                SetVsyncLazyMode();
                break;
            }
        case FIRST_MOVE:
            {
                ACE_SCOPED_TRACE("RecordInputEvent: first_move=%lld(ns)", static_cast<long long>(time));
                mInputTime[FIRST_MOVE] = time;
                break;
            }
        default:
            break;
    }
}

void PerfMonitor::SetFrameTime(int64_t vsyncTime, int64_t duration, double jank, const std::string& windowName)
{
    std::lock_guard<std::mutex> Lock(mMutex);
    mVsyncTime = vsyncTime;
    int32_t skippedFrames = static_cast<int32_t> (jank);
    for (auto it = mRecords.begin(); it != mRecords.end();) {
        if (it->second != nullptr) {
            (it->second)->RecordFrame(vsyncTime, duration, skippedFrames);
            if ((it->second)->IsTimeOut(vsyncTime + duration)) {
                CheckTimeOutOfExceptAnimatorStatus(it->second->sceneId);
                delete it->second;
                it = mRecords.erase(it);
                continue;
            }
            if ((it->second)->IsFirstFrame()) {
                ReportAnimateStart(it->first, it->second);
            }
        }
        it++;
    }
    ProcessJank(jank, windowName);
    JankFrameStatsRecord(jank);
}

void PerfMonitor::ReportJankFrameApp(double jank)
{
    if (jank >= static_cast<double>(JANK_SKIPPED_THRESHOLD) && !isBackgroundApp) {
        JankInfo jankInfo;
        jankInfo.skippedFrameTime = static_cast<int64_t>(jank * SINGLE_FRAME_TIME);
        RecordBaseInfo(nullptr);
        jankInfo.baseInfo = baseInfo;
        EventReport::ReportJankFrameApp(jankInfo);
    }
}

void PerfMonitor::SetPageUrl(const std::string& pageUrl)
{
    baseInfo.pageUrl = ParsePageUrl(pageUrl);
}

std::string PerfMonitor::GetPageUrl()
{
    return baseInfo.pageUrl;
}

void PerfMonitor::SetPageName(const std::string& pageName)
{
    baseInfo.pageName = pageName;
}

std::string PerfMonitor::GetPageName()
{
    return baseInfo.pageName;
}

void PerfMonitor::ReportPageShowMsg(const std::string& pageUrl, const std::string& bundleName,
                                    const std::string& pageName)
{
    std::string parsePageUrl = ParsePageUrl(pageUrl);
    EventReport::ReportPageShowMsg(parsePageUrl, bundleName, pageName);
}

void PerfMonitor::RecordBaseInfo(SceneRecord* record)
{
    baseInfo.pid = AceApplicationInfo::GetInstance().GetPid();
    baseInfo.bundleName = AceApplicationInfo::GetInstance().GetPackageName();
    baseInfo.versionCode = static_cast<int32_t>(AceApplicationInfo::GetInstance().GetAppVersionCode());
    baseInfo.versionName = AceApplicationInfo::GetInstance().GetAppVersionName();
    baseInfo.processName = AceApplicationInfo::GetInstance().GetProcessName();
    baseInfo.abilityName = AceApplicationInfo::GetInstance().GetAbilityName();
    if (record != nullptr) {
        baseInfo.note = record->note;
    }
}

SceneRecord* PerfMonitor::GetRecord(const std::string& sceneId)
{
    auto iter = mRecords.find(sceneId);
    if (iter != mRecords.end()) {
        return iter->second;
    }
    return nullptr;
}

void PerfMonitor::RemoveRecord(const std::string& sceneId)
{
    std::map <std::string, SceneRecord*>::iterator iter = mRecords.find(sceneId);
    if (iter != mRecords.end()) {
        if (iter->second != nullptr) {
            delete iter->second;
        }
        mRecords.erase(iter);
    }
}

int64_t PerfMonitor::GetInputTime(const std::string& sceneId, PerfActionType type, const std::string& note)
{
    int64_t inputTime = 0;
    switch (type) {
        case LAST_DOWN:
            inputTime = mInputTime[LAST_DOWN];
            break;
        case LAST_UP:
            inputTime = mInputTime[LAST_UP];
            break;
        case FIRST_MOVE:
            inputTime = mInputTime[FIRST_MOVE];
            break;
        default:
            break;
    }
    if (inputTime <= 0 || IsExceptResponseTime(inputTime, sceneId)) {
        ACE_SCOPED_TRACE("GetInputTime: now time");
        inputTime = GetCurrentRealTimeNs();
    }
    return inputTime;
}

void PerfMonitor::ReportAnimateStart(const std::string& sceneId, SceneRecord* record)
{
    if (record == nullptr) {
        return;
    }
    DataBase data;
    FlushDataBase(record, data);
    ReportPerfEvent(EVENT_RESPONSE, data);
}

void PerfMonitor::ReportAnimateEnd(const std::string& sceneId, SceneRecord* record)
{
    if (record == nullptr) {
        return;
    }
    DataBase data;
    FlushDataBase(record, data);
    ReportPerfEvent(EVENT_JANK_FRAME, data);
    ReportPerfEvent(EVENT_COMPLETE, data);
}

void PerfMonitor::FlushDataBase(SceneRecord* record, DataBase& data)
{
    if (record == nullptr) {
        return;
    }
    data.sceneId = record->sceneId;
    data.inputTime = record->inputTime;
    data.beginVsyncTime = record->beginVsyncTime;
    if (data.beginVsyncTime < data.inputTime) {
        data.inputTime = data.beginVsyncTime;
    }
    data.endVsyncTime = record->endVsyncTime;
    if (data.beginVsyncTime > data.endVsyncTime) {
        data.endVsyncTime = data.beginVsyncTime;
    }
    data.maxFrameTime = record->maxFrameTime;
    data.maxFrameTimeSinceStart = record->maxFrameTimeSinceStart;
    data.maxHitchTime = record->maxHitchTime;
    data.maxHitchTimeSinceStart = record->maxHitchTimeSinceStart;
    data.maxSuccessiveFrames = record->maxSuccessiveFrames;
    data.totalMissed = record->totalMissed;
    data.totalFrames = record->totalFrames;
    data.needReportRs = record->needReportRs;
    data.isDisplayAnimator = record->isDisplayAnimator;
    data.sourceType = record->sourceType;
    data.actionType = record->actionType;
    data.baseInfo = baseInfo;
}

void PerfMonitor::ReportPerfEvent(PerfEventType type, DataBase& data)
{
    switch (type) {
        case EVENT_RESPONSE:
            data.eventType = EVENT_RESPONSE;
            break;
        case EVENT_COMPLETE:
            data.eventType = EVENT_COMPLETE;
            break;
        case EVENT_JANK_FRAME:
            data.eventType = EVENT_JANK_FRAME;
            break;
        default :
            break;
    }
    ReportPerfEventToUI(data);
    ReportPerfEventToRS(data);
}

bool PerfMonitor::IsExceptResponseTime(int64_t time, const std::string& sceneId)
{
    int64_t currentRealTimeNs = GetCurrentRealTimeNs();
    static set<std::string> exceptSceneSet = {
        PerfConstants::APP_LIST_FLING, PerfConstants::SCREEN_ROTATION_ANI,
        PerfConstants::SHOW_INPUT_METHOD_ANIMATION, PerfConstants::HIDE_INPUT_METHOD_ANIMATION,
        PerfConstants::APP_TRANSITION_FROM_OTHER_APP, PerfConstants::APP_TRANSITION_TO_OTHER_APP,
        PerfConstants::VOLUME_BAR_SHOW, PerfConstants::PC_APP_CENTER_GESTURE_OPERATION,
        PerfConstants::PC_GESTURE_TO_RECENT, PerfConstants::PC_SHORTCUT_SHOW_DESKTOP,
        PerfConstants::PC_ALT_TAB_TO_RECENT, PerfConstants::PC_SHOW_DESKTOP_GESTURE_OPERATION,
        PerfConstants::PC_SHORTCUT_RESTORE_DESKTOP, PerfConstants::PC_SHORTCUT_TO_RECENT,
        PerfConstants::PC_EXIT_RECENT, PerfConstants::PC_SHORTCUT_TO_APP_CENTER_ON_RECENT,
        PerfConstants::PC_SHORTCUT_TO_APP_CENTER, PerfConstants::PC_SHORTCUT_EXIT_APP_CENTER,
        PerfConstants::WINDOW_TITLE_BAR_MINIMIZED, PerfConstants::WINDOW_RECT_MOVE,
        PerfConstants::APP_EXIT_FROM_WINDOW_TITLE_BAR_CLOSED, PerfConstants::WINDOW_TITLE_BAR_RECOVER,
        PerfConstants::LAUNCHER_APP_LAUNCH_FROM_OTHER, PerfConstants::WINDOW_RECT_RESIZE,
        PerfConstants::WINDOW_TITLE_BAR_MAXIMIZED, PerfConstants::LAUNCHER_APP_LAUNCH_FROM_TRANSITION
    };
    if (exceptSceneSet.find(sceneId) != exceptSceneSet.end()) {
        return true;
    }
    if ((sceneId == PerfConstants::ABILITY_OR_PAGE_SWITCH && currentRealTimeNs - time > RESPONSE_TIMEOUT)
        || (sceneId == PerfConstants::CLOSE_FOLDER_ANI && currentRealTimeNs - time > RESPONSE_TIMEOUT)) {
        return true;
    }
    return false;
}

// for jank frame app
bool PerfMonitor::IsExclusionFrame()
{
    ACE_SCOPED_TRACE("IsExclusionFrame: isResponse(%d) isStartApp(%d) isBg(%d) isExcluWindow(%d) isExcAni(%d)",
        isResponseExclusion, isStartAppFrame, isBackgroundApp, isExclusionWindow, isExceptAnimator);
    return isResponseExclusion || isStartAppFrame || isBackgroundApp || isExclusionWindow || isExceptAnimator;
}

void PerfMonitor::SetVsyncLazyMode()
{
#ifdef OHOS_STANDARD_SYSTEM
    static bool lastExcusion = false;
    bool needExcusion = isResponseExclusion || isStartAppFrame || isBackgroundApp ||
                        isExclusionWindow || isExceptAnimator;
    if (lastExcusion == needExcusion) {
        return;
    }

    lastExcusion = needExcusion;
    ACE_VSYNC_MODE_SCOPED_TRACE("SetVsyncLazyMode: isResponse(%d) isStartApp(%d) isBg(%d) isExcluWindow(%d) "
        "isExcAni(%d)",
        isResponseExclusion, isStartAppFrame, isBackgroundApp, isExclusionWindow, isExceptAnimator);
    OHOS::AppExecFwk::EventHandler::SetVsyncLazyMode(needExcusion);
#endif
}

void PerfMonitor::SetAppStartStatus()
{
    ACE_FUNCTION_TRACE();
    isStartAppFrame = true;
    SetVsyncLazyMode();
    startAppTime = GetCurrentRealTimeNs();
}

void PerfMonitor::CheckInStartAppStatus()
{
    if (isStartAppFrame) {
        int64_t curTime = GetCurrentRealTimeNs();
        if (curTime - startAppTime >= STARTAPP_FRAME_TIMEOUT) {
            isStartAppFrame = false;
            startAppTime = curTime;
            SetVsyncLazyMode();
        }
    }
}

void PerfMonitor::SetAppForeground(bool isShow)
{
    isBackgroundApp = !isShow;
    SetVsyncLazyMode();
}

void PerfMonitor::CheckExclusionWindow(const std::string& windowName)
{
    isExclusionWindow = false;
    if (windowName == "softKeyboard1" ||
        windowName == "SCBWallpaper1" ||
        windowName == "SCBStatusBar15") {
        isExclusionWindow = true;
    }
    SetVsyncLazyMode();
}

void PerfMonitor::CheckResponseStatus()
{
    if (isResponseExclusion) {
        isResponseExclusion = false;
        SetVsyncLazyMode();
    }
}

void PerfMonitor::ProcessJank(double jank, const std::string& windowName)
{
    // single frame behavior report
    CheckExclusionWindow(windowName);
    ReportJankFrame(jank, windowName);
    CheckInStartAppStatus();
    CheckResponseStatus();
}

void PerfMonitor::ReportJankFrame(double jank, const std::string& windowName)
{
    if (jank >= static_cast<double>(DEFAULT_JANK_REPORT_THRESHOLD)) {
        JankInfo jankInfo;
        jankInfo.skippedFrameTime = static_cast<int64_t>(jank * SINGLE_FRAME_TIME);
        jankInfo.windowName = windowName;
        RecordBaseInfo(nullptr);
        jankInfo.baseInfo = baseInfo;
        jankInfo.filterType = GetFilterType();
        if (!mRecords.empty()) {
            jankInfo.sceneId = currentSceneId;
        } else {
            jankInfo.sceneId = DEFAULT_SCENE_ID;
        }
        jankInfo.realSkippedFrameTime = jankInfo.filterType == 0 ? jankInfo.skippedFrameTime : 0;
        EventReport::ReportJankFrameUnFiltered(jankInfo);
        if (!IsExclusionFrame()) {
            EventReport::ReportJankFrameFiltered(jankInfo);
        }
    }
}

bool PerfMonitor::IsSceneIdInSceneWhiteList(const std::string& sceneId)
{
    if (sceneId == PerfConstants::LAUNCHER_APP_LAUNCH_FROM_ICON ||
        sceneId == PerfConstants::LAUNCHER_APP_LAUNCH_FROM_DOCK ||
        sceneId == PerfConstants::LAUNCHER_APP_LAUNCH_FROM_MISSON ||
        sceneId == PerfConstants::LAUNCHER_APP_SWIPE_TO_HOME ||
        sceneId == PerfConstants::LAUNCHER_APP_BACK_TO_HOME ||
        sceneId == PerfConstants::EXIT_RECENT_2_HOME_ANI ||
        sceneId == PerfConstants::APP_SWIPER_FLING ||
        sceneId == PerfConstants::ABILITY_OR_PAGE_SWITCH ||
        sceneId == PerfConstants::SCREENLOCK_SCREEN_OFF_ANIM) {
            return true;
        }
    return false;
}

bool PerfMonitor::IsScrollJank(const std::string& sceneId)
{
    if (sceneId == PerfConstants::APP_LIST_FLING ||
        sceneId == PerfConstants::APP_SWIPER_SCROLL ||
        sceneId == PerfConstants::APP_SWIPER_FLING) {
        return true;
    }
    return false;
}

void PerfMonitor::CheckTimeOutOfExceptAnimatorStatus(const std::string& sceneId)
{
    if (IsSceneIdInSceneWhiteList(sceneId)) {
        isExceptAnimator = false;
        SetVsyncLazyMode();
    }
}

int32_t PerfMonitor::GetFilterType() const
{
    int32_t filterType = (isBackgroundApp << 4) | (isResponseExclusion << 3) | (isStartAppFrame << 2)
        | (isExclusionWindow << 1) | isExceptAnimator;
    return filterType;
}

void PerfMonitor::RecordWindowRectResize(OHOS::Ace::WindowSizeChangeReason reason, const std::string& bundleName)
{
    switch (reason) {
        case OHOS::Ace::WindowSizeChangeReason::DRAG_START:
            Start(PerfConstants::WINDOW_RECT_RESIZE, PerfActionType::LAST_DOWN, bundleName.c_str());
            break;
        case OHOS::Ace::WindowSizeChangeReason::DRAG_END:
            End(PerfConstants::WINDOW_RECT_RESIZE, true);
            break;
        default:
            break;
    }
}

void PerfMonitor::ClearJankFrameRecord()
{
    std::fill(jankFrameRecord.begin(), jankFrameRecord.end(), 0);
    jankFrameTotalCount = 0;
    jankFrameRecordBeginTime = 0;
}

void SetJankFrameRecord(OHOS::Rosen::AppInfo &appInfo, int64_t startTime, int64_t endTime)
{
    appInfo.pid = AceApplicationInfo::GetInstance().GetPid();
    appInfo.bundleName = AceApplicationInfo::GetInstance().GetPackageName();
    appInfo.versionCode = static_cast<int32_t>(AceApplicationInfo::GetInstance().GetAppVersionCode());
    appInfo.versionName = AceApplicationInfo::GetInstance().GetAppVersionName();
    appInfo.processName = AceApplicationInfo::GetInstance().GetProcessName();
    appInfo.startTime = startTime;
    appInfo.endTime = endTime;
}

void PerfMonitor::JankFrameStatsRecord(double jank)
{
    if (isStats == true && jank > 1.0f && !jankFrameRecord.empty()) {
        jankFrameRecord[GetJankLimit(jank)]++;
        jankFrameTotalCount++;
    }
}

void PerfMonitor::NotifySbdJankStatsBegin(const std::string& sceneId)
{
    static set<std::string> backToHomeScene = {
        PerfConstants::LAUNCHER_APP_BACK_TO_HOME,
        PerfConstants::LAUNCHER_APP_SWIPE_TO_HOME,
        PerfConstants::INTO_HOME_ANI,
        PerfConstants::PASSWORD_UNLOCK_ANI,
        PerfConstants::FACIAL_FLING_UNLOCK_ANI,
        PerfConstants::FACIAL_UNLOCK_ANI,
        PerfConstants::FINGERPRINT_UNLOCK_ANI
    };
    if (backToHomeScene.find(sceneId) != backToHomeScene.end()) {
        ACE_SCOPED_TRACE("NotifySbdJankStatsBegin");
        NotifyAppJankStatsBegin();
    }
}

void PerfMonitor::NotifySdbJankStatsEnd(const std::string& sceneId)
{
    static set<std::string> appLaunch = {
        PerfConstants::LAUNCHER_APP_LAUNCH_FROM_DOCK,
        PerfConstants::LAUNCHER_APP_LAUNCH_FROM_ICON,
        PerfConstants::LAUNCHER_APP_LAUNCH_FROM_NOTIFICATIONBAR,
        PerfConstants::LAUNCHER_APP_LAUNCH_FROM_NOTIFICATIONBAR_IN_LOCKSCREEN,
        PerfConstants::LAUNCHER_APP_LAUNCH_FROM_RECENT,
        PerfConstants::START_APP_ANI_FORM,
        PerfConstants::SCREENLOCK_SCREEN_OFF_ANIM
    };
    if (appLaunch.find(sceneId) != appLaunch.end()) {
        ACE_SCOPED_TRACE("NotifySdbJankStatsEnd");
        NotifyAppJankStatsEnd();
    }
}


void PerfMonitor::NotifyAppJankStatsBegin()
{
    ACE_SCOPED_TRACE("NotifyAppJankStatsBegin");
    int64_t duration = GetCurrentSystimeMs() - jankFrameRecordBeginTime;
    if (!isStats) {
        if (jankFrameRecord.empty()) {
            jankFrameRecord = std::vector<uint16_t>(JANK_STATS_SIZE, 0);
        }
        isStats = true;
        NotifyRsJankStatsBegin();
        return;
    }
    if (duration >= DEFAULT_VSYNC) {
        ReportJankStatsApp(duration);
        NotifyRsJankStatsEnd(GetCurrentSystimeMs());
        ClearJankFrameRecord();
        NotifyRsJankStatsBegin();
    }
}

void PerfMonitor::NotifyAppJankStatsEnd()
{
    if (!isStats) {
        return;
    }
    ACE_SCOPED_TRACE("NotifyAppJankStatsEnd");
    int64_t endTime = GetCurrentSystimeMs();
    NotifyRsJankStatsEnd(endTime);
    isStats = false;
    int64_t duration = endTime - jankFrameRecordBeginTime;
    ReportJankStatsApp(duration);
}

void PerfMonitor::ReportJankStatsApp(int64_t duration)
{
    ACE_SCOPED_TRACE("ReportJankStatsApp count=%" PRId32 ";duration=%" PRId64 ";beginTime=%" PRId64 ";",
        jankFrameTotalCount, duration, jankFrameRecordBeginTime);
    if (duration > DEFAULT_VSYNC && jankFrameTotalCount > 0 && jankFrameRecordBeginTime > 0) {
        EventReport::JankFrameReport(jankFrameRecordBeginTime, duration, jankFrameRecord,
            baseInfo.pageUrl, JANK_STATS_VERSION);
    }
    ClearJankFrameRecord();
}

void PerfMonitor::NotifyRsJankStatsBegin()
{
    ACE_SCOPED_TRACE("NotifyRsJankStatsBegin");
    OHOS::Rosen::AppInfo appInfo;
    jankFrameRecordBeginTime = GetCurrentSystimeMs();
    SetJankFrameRecord(appInfo, jankFrameRecordBeginTime, 0);
    Rosen::RSInterfaces::GetInstance().ReportRsSceneJankStart(appInfo);
}

void PerfMonitor::NotifyRsJankStatsEnd(int64_t endTime)
{
    ACE_SCOPED_TRACE("NotifyRsJankStatsEnd");
    OHOS::Rosen::AppInfo appInfo;
    SetJankFrameRecord(appInfo, jankFrameRecordBeginTime, endTime);
    Rosen::RSInterfaces::GetInstance().ReportRsSceneJankEnd(appInfo);
}

void PerfMonitor::SetApsMonitor(const std::shared_ptr<ApsMonitor>& apsMonitor)
{
    apsMonitor_ = apsMonitor;
}

} // namespace OHOS::Ace
