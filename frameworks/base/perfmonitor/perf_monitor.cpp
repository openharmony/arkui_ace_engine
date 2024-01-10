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
#include <sys/time.h>

#include "base/perfmonitor/perf_monitor.h"

#include "base/log/ace_trace.h"
#include "base/log/event_report.h"
#include "base/log/jank_frame_report.h"
#include "base/log/log.h"
#include "base/perfmonitor/perf_constants.h"
#include "base/utils/system_properties.h"
#include "core/common/ace_application_info.h"
#include "render_service_client/core/transaction/rs_interfaces.h"

namespace OHOS::Ace {
using namespace std;
PerfMonitor* PerfMonitor::pMonitor = nullptr;
constexpr int64_t SCENE_TIMEOUT = 10000000000;
constexpr int64_t RESPONSE_TIMEOUT = 1000000000;
constexpr float SINGLE_FRAME_TIME = 16600000;
const int32_t JANK_SKIPPED_THRESHOLD = SystemProperties::GetJankFrameThreshold();

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
                if (data.isDisplayAnimator) {
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
    if (totalFrames == 0) {
        beginVsyncTime = GetCurrentRealTimeNs();
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
    if (sceneId == PerfConstants::APP_LIST_FLING) {
        return true;
    }
    return false;
}

void SceneRecord::Reset()
{
    beginVsyncTime = 0;
    endVsyncTime = 0;
    maxFrameTime = 0;
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
    if (pMonitor == nullptr) {
        pMonitor = new PerfMonitor();
    }
    return pMonitor;
}

void PerfMonitor::Start(const std::string& sceneId, PerfActionType type, const std::string& note)
{
    std::lock_guard<std::mutex> Lock(mMutex);
    int64_t inputTime = GetInputTime(sceneId, type, note);
    SceneRecord* record = GetRecord(sceneId);
    if (record == nullptr) {
        record = new SceneRecord();
        record->InitRecord(sceneId, type, mSourceType, note, inputTime);
        mRecords.insert(std::pair<std::string, SceneRecord*> (sceneId, record));
        RecordBaseInfo(record);
        AceAsyncTraceBegin(0, sceneId.c_str());
    }
}

void PerfMonitor::End(const std::string& sceneId, bool isRsRender)
{
    std::lock_guard<std::mutex> Lock(mMutex);
    SceneRecord* record = GetRecord(sceneId);
    if (record != nullptr) {
        RecordBaseInfo(record);
        record->Report(sceneId, mVsyncTime, isRsRender);
        ReportAnimateEnd(sceneId, record);
        RemoveRecord(sceneId);
        AceAsyncTraceEnd(0, sceneId.c_str());
    }
}

void PerfMonitor::RecordInputEvent(PerfActionType type, PerfSourceType sourceType, int64_t time)
{
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

void PerfMonitor::SetFrameTime(int64_t vsyncTime, int64_t duration, double jank)
{
    std::lock_guard<std::mutex> Lock(mMutex);
    mVsyncTime = vsyncTime;
    int32_t skippedFrames = static_cast<int32_t> (jank);
    for (auto it = mRecords.begin(); it != mRecords.end();) {
        if (it->second != nullptr) {
            (it->second)->RecordFrame(vsyncTime, duration, skippedFrames);
            if ((it->second)->IsTimeOut(vsyncTime + duration)) {
                delete it->second;
                mRecords.erase(it++);
                continue;
            }
            if ((it->second)->IsFirstFrame()) {
                ReportAnimateStart(it->first, it->second);
            }
        }
        it++;
    }
}

void PerfMonitor::ReportJankFrameApp(double jank)
{
    if (jank >= static_cast<double>(JANK_SKIPPED_THRESHOLD)) {
        JankInfo jankInfo;
        jankInfo.skippedFrameTime = static_cast<int64_t>(jank * SINGLE_FRAME_TIME);
        RecordBaseInfo(nullptr);
        jankInfo.baseInfo = baseInfo;
        EventReport::ReportJankFrameApp(jankInfo);
    }
}

void PerfMonitor::SetPageUrl(const std::string& pageUrl)
{
    baseInfo.pageUrl = pageUrl;
}

std::string PerfMonitor::GetPageUrl()
{
    return baseInfo.pageUrl;
}

void PerfMonitor::RecordBaseInfo(SceneRecord* record)
{
    baseInfo.pid = AceApplicationInfo::GetInstance().GetPid();
    baseInfo.bundleName = AceApplicationInfo::GetInstance().GetPackageName();
    baseInfo.versionCode = AceApplicationInfo::GetInstance().GetAppVersionCode();
    baseInfo.versionName = AceApplicationInfo::GetInstance().GetAppVersionName();
    baseInfo.processName = AceApplicationInfo::GetInstance().GetProcessName();
    baseInfo.abilityName = AceApplicationInfo::GetInstance().GetAbilityName();
    if (record != nullptr) {
        baseInfo.note = record->note;
    }
}

SceneRecord* PerfMonitor::GetRecord(const std::string& sceneId)
{
    if (mRecords.find(sceneId) != mRecords.end()) {
        return mRecords[sceneId];
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
    if ((sceneId == PerfConstants::ABILITY_OR_PAGE_SWITCH
        && GetCurrentRealTimeNs() - time > RESPONSE_TIMEOUT)
        || sceneId == PerfConstants::VOLUME_BAR_SHOW) {
        return true;
    }
    if (sceneId == PerfConstants::PC_APP_CENTER_GESTURE_OPERATION ||
        sceneId == PerfConstants::PC_GESTURE_TO_RECENT ||
        sceneId == PerfConstants::PC_SHORTCUT_SHOW_DESKTOP ||
        sceneId == PerfConstants::PC_SHORTCUT_RESTORE_DESKTOP ||
        sceneId == PerfConstants::PC_SHOW_DESKTOP_GESTURE_OPERATION ||
        sceneId == PerfConstants::PC_ALT_TAB_TO_RECENT ||
        sceneId == PerfConstants::PC_SHORTCUT_TO_RECENT ||
        sceneId == PerfConstants::PC_EXIT_RECENT ||
        sceneId == PerfConstants::PC_SHORTCUT_TO_APP_CENTER ||
        sceneId == PerfConstants::PC_SHORTCUT_EXIT_APP_CENTER) {
        return true;
    }
    return false;
}
} // namespace OHOS::Ace
