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
#include "core/common/ace_application_info.h"
#include "render_service_client/core/transaction/rs_interfaces.h"

namespace OHOS::Ace {
using namespace std;
PerfMonitor* PerfMonitor::pMonitor = nullptr;
constexpr int64_t SCENE_TIMEOUT = 10000000000;

static int64_t GetCurrentSystimeMs()
{
    auto timeNow = std::chrono::system_clock::now();
    auto tmp = std::chrono::duration_cast<std::chrono::milliseconds>(timeNow.time_since_epoch());
    int64_t curSystime = tmp.count();
    return curSystime;
}

void ConvertUptimeToSystime(int64_t uptime, int64_t& systime)
{
    struct timespec ts = { 0, 0 };
    if (clock_gettime(CLOCK_MONOTONIC, &ts) != 0) {
        systime = 0;
        return;
    }
    int64_t nowUptime = ts.tv_sec * NS_TO_S + ts.tv_nsec;
    int64_t curSystime = GetCurrentSystimeMs();
    systime = curSystime - (nowUptime - uptime) / NS_TO_MS;
}

void ConvertToRsData(OHOS::Rosen::DataBaseRs &dataRs, DataBase& data)
{
    dataRs.eventType = static_cast<int32_t>(data.eventType);
    dataRs.sceneId = data.sceneId;
    dataRs.appPid = data.baseInfo.pid;
    dataRs.uniqueId = data.inputTime / NS_TO_MS;
    dataRs.inputTime = data.inputTime;
    dataRs.beginVsyncTime = data.beginVsyncTime;
    dataRs.endVsyncTime = data.endVsyncTime;
    dataRs.versionCode = data.baseInfo.versionCode;
    dataRs.versionName = data.baseInfo.versionName;
    dataRs.bundleName = data.baseInfo.bundleName;
    dataRs.processName = data.baseInfo.processName;
    dataRs.abilityName = data.baseInfo.abilityName;
    dataRs.pageUrl = data.baseInfo.pageUrl;
}

void ReportPerfEventToRS(OHOS::Rosen::DataBaseRs& dataRs)
{
    switch (dataRs.eventType) {
        case EVENT_RESPONSE:
            Rosen::RSInterfaces::GetInstance().ReportEventResponse(dataRs);
            break;
        case EVENT_COMPLETE:
            Rosen::RSInterfaces::GetInstance().ReportEventComplete(dataRs);
            break;
        case EVENT_JANK_FRAME:
            Rosen::RSInterfaces::GetInstance().ReportEventJankFrame(dataRs);
            break;
        default :
            break;
    }
}

void ReportPerfEventToUI(DataBase data)
{
    switch (data.eventType) {
        case EVENT_COMPLETE:
            EventReport::ReportEventComplete(data);
            break;
        case EVENT_JANK_FRAME:
            if (data.totalMissed <= 0) {
                return;
            }
            EventReport::ReportEventJankFrame(data);
            break;
        default :
            break;
    }
}

void SceneRecord::InitRecord(const std::string& sId, PerfActionType type, const std::string& nt)
{
    sceneId = sId;
    actionType = type;
    note = nt;
}

bool SceneRecord::IsTimeOut(int64_t nowTime)
{
    if (nowTime - beginVsyncTime > SCENE_TIMEOUT) {
        return true;
    }
    return false;
}

void SceneRecord::RecordFrame(int64_t vsyncTime, int64_t durition, int32_t skippedFrames)
{
    if (IsFirstFrame()) {
        beginVsyncTime = vsyncTime;
    }
    if (skippedFrames >= 1) {
        if (durition > maxFrameTime) {
            maxFrameTime = durition;
            maxSuccessiveFrames = skippedFrames;
        }
        totalMissed += (skippedFrames - 1);
    }
    totalFrames++;
}

void SceneRecord::Report(const std::string& sceneId, int64_t vsyncTime)
{
    endVsyncTime = vsyncTime;
}

bool SceneRecord::IsFirstFrame()
{
    if (totalFrames == 0) {
        return true;
    }
    return false;
}

void SceneRecord::Reset()
{
    sceneId = "";
    beginVsyncTime = 0;
    endVsyncTime = 0;
    maxFrameTime = 0;
    maxSuccessiveFrames = 0;
    totalMissed = 0;
    totalFrames = 0;
    actionType = ERROR_TYPE;
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
    AceAsyncTraceBegin(0, sceneId.c_str());
    std::lock_guard<std::mutex> Lock(mMutex);
    SceneRecord* record = GetRecord(sceneId);
    if (record != nullptr) {
        record->Reset();
        record->InitRecord(sceneId, type, note);
    } else {
        record = new SceneRecord();
        record->InitRecord(sceneId, type, note);
        mRecords.insert(std::pair<std::string, SceneRecord*> (sceneId, record));
    }
    ReportAnimateStart(sceneId, record);
}

void PerfMonitor::End(const std::string& sceneId, bool isJsApi)
{
    std::lock_guard<std::mutex> Lock(mMutex);
    RecordBaseInfo();
    SceneRecord* record = GetRecord(sceneId);
    if (record != nullptr) {
        record->Report(sceneId, mVsyncTime);
        ReportAnimateEnd(sceneId, record, !isJsApi);
        RemoveRecord(sceneId);
    }
    AceAsyncTraceEnd(0, sceneId.c_str());
}

void PerfMonitor::RecordInputEvent(PerfActionType type, PerfSourceType sourceType, int64_t time)
{
    switch (type) {
        case LAST_DOWN:
            lastInputDownTime = time;
            break;
        case LAST_UP:
            lastInputUpTime = time;
            break;
        case FIRST_MOVE:
            firstMoveTime = time;
            break;
        default:
            break;
    }
}

void PerfMonitor::SetFrameTime(int64_t vsyncTime, int64_t durition, double jank)
{
    std::lock_guard<std::mutex> Lock(mMutex);
    mVsyncTime = vsyncTime;
    int32_t skippedFrames = static_cast<int32_t> (jank);
    for (auto it = mRecords.begin(); it != mRecords.end();) {
        if (it->second != nullptr) {
            (it->second)->RecordFrame(vsyncTime, durition, skippedFrames);
            if ((it->second)->IsTimeOut(vsyncTime + durition)) {
                delete it->second;
                mRecords.erase(it++);
                continue;
            }
        }
        it++;
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

void PerfMonitor::RecordBaseInfo()
{
    baseInfo.pid = AceApplicationInfo::GetInstance().GetPid();
    baseInfo.bundleName = AceApplicationInfo::GetInstance().GetPackageName();
    baseInfo.versionCode = AceApplicationInfo::GetInstance().GetAppVersionCode();
    baseInfo.versionName = AceApplicationInfo::GetInstance().GetAppVersionName();
    baseInfo.processName = AceApplicationInfo::GetInstance().GetProcessName();
    baseInfo.abilityName = AceApplicationInfo::GetInstance().GetAbilityName();
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

int64_t PerfMonitor::GetInputTime(PerfActionType type)
{
    int64_t inputTime = 0;
    switch (type) {
        case LAST_DOWN:
            inputTime = lastInputDownTime;
            break;
        case LAST_UP:
            inputTime = lastInputUpTime;
            break;
        case FIRST_MOVE:
            inputTime = firstMoveTime;
            break;
        default:
            inputTime = lastInputDownTime;
            break;
    }
    return inputTime;
}

void PerfMonitor::ReportAnimateStart(const std::string& sceneId, SceneRecord* record)
{
    if (record == nullptr) {
        return;
    }
    DataBase data;
    FlushDataBase(record, data, true);
    ReportPerfEvent(EVENT_RESPONSE, data);
}

void PerfMonitor::ReportAnimateEnd(const std::string& sceneId, SceneRecord* record, bool needCompleteTime)
{
    if (record == nullptr) {
        return;
    }
    DataBase data;
    FlushDataBase(record, data, needCompleteTime);
    ReportPerfEvent(EVENT_JANK_FRAME, data);
    ReportPerfEvent(EVENT_COMPLETE, data);
}

void PerfMonitor::FlushDataBase(SceneRecord* record, DataBase& data, bool needCompleteTime)
{
    if (record == nullptr) {
        return;
    }
    data.sceneId = record->sceneId;
    data.inputTime = GetInputTime(record->actionType);
    data.beginVsyncTime = record->beginVsyncTime;
    data.endVsyncTime = record->endVsyncTime;
    data.maxFrameTime = record->maxFrameTime;
    data.maxSuccessiveFrames = record->maxSuccessiveFrames;
    data.totalMissed = record->totalMissed;
    data.totalFrames = record->totalFrames;
    data.needReportToRS = needCompleteTime;
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
    if (data.needReportToRS) {
        OHOS::Rosen::DataBaseRs dataRs;
        ConvertToRsData(dataRs, data);
        ReportPerfEventToRS(dataRs);
    }
    ReportPerfEventToUI(data);
}
} // namespace OHOS::Ace
