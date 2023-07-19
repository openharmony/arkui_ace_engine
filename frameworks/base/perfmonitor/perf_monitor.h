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

#ifndef ARKUI_PERF_MONITOR_H
#define ARKUI_PERF_MONITOR_H

#include <mutex>
#include <string>
#include <map>

#include "base/utils/macros.h"

namespace OHOS::Ace {
constexpr int32_t US_TO_MS = 1000;
constexpr int32_t NS_TO_MS = 1000000;
constexpr int32_t NS_TO_S = 1000000000;
void ConvertUptimeToSystime(int64_t uptime, int64_t& systime);

enum PerfActionType {
    ERROR_TYPE = -1,
    LAST_DOWN = 0,
    LAST_UP = 1,
    FIRST_MOVE = 2
};

enum PerfSourceType {
    UNKNOWN_TYPE = -1,
    PERF_TOUCH_EVENT = 0,
    PERF_MOUSE_EVENT = 2
};

enum PerfEventType {
    EVENT_ERROR = -1,
    EVENT_RESPONSE = 0,
    EVENT_COMPLETE = 1,
    EVENT_JANK_FRAME = 2
};

struct BaseInfo {
    int32_t pid {-1};
    std::string versionCode {""};
    std::string versionName {""};
    std::string bundleName {""};
    std::string processName {""};
    std::string abilityName {""};
    std::string pageUrl {""};
};

struct DataBase {
    std::string sceneId {""};
    int32_t maxFrameTime {0};
    int32_t maxSuccessiveFrames {0};
    int32_t totalMissed {0};
    int32_t totalFrames {0};
    int64_t inputTime {0};
    int64_t beginVsyncTime {0};
    int64_t endVsyncTime {0};
    bool needReportToRS {false};
    PerfEventType eventType {EVENT_ERROR};
    BaseInfo baseInfo;
};

class SceneRecord {
public:
    void InitRecord(const std::string& sId, PerfActionType type, const std::string& nt);
    void RecordFrame(int64_t vsyncTime, int64_t durition, int32_t skippedFrames);
    void Report(const std::string& sceneId, int64_t vsyncTime);
    bool IsTimeOut(int64_t nowTime);
    bool IsFirstFrame();
    void Reset();
public:
    int64_t beginVsyncTime {0};
    int64_t endVsyncTime {0};
    int32_t maxFrameTime {0};
    int32_t maxSuccessiveFrames {0};
    int32_t totalMissed {0};
    int32_t totalFrames {0};
    std::string sceneId {""};
    PerfActionType actionType {ERROR_TYPE};
    std::string note {""};
};

class ACE_FORCE_EXPORT PerfMonitor {
public:
    void Start(const std::string& sceneId, PerfActionType type, const std::string& note);
    void End(const std::string& sceneId, bool isJsApi);
    void RecordInputEvent(PerfActionType type, PerfSourceType sourceType, int64_t time);
    int64_t GetInputTime(PerfActionType type);
    void SetFrameTime(int64_t vsyncTime, int64_t durition, double jank);
    void SetPageUrl(const std::string& pageUrl);
    std::string GetPageUrl();
    static PerfMonitor* GetPerfMonitor();
    static PerfMonitor* pMonitor;

private:
    SceneRecord* GetRecord(const std::string& sceneId);
    void RemoveRecord(const std::string& sceneId);
    void ReportAnimateStart(const std::string& sceneId, SceneRecord* record);
    void ReportAnimateEnd(const std::string& sceneId, SceneRecord* record, bool needCompleteTime);
    void FlushDataBase(SceneRecord* record, DataBase& data, bool needCompleteTime);
    void ReportPerfEvent(PerfEventType type, DataBase& data);
    void RecordBaseInfo();
private:
    int64_t firstMoveTime {0};
    int64_t lastInputDownTime {0};
    int64_t lastInputUpTime {0};
    int64_t mVsyncTime {0};
    BaseInfo baseInfo;
    mutable std::mutex mMutex;
    std::map<std::string, SceneRecord*> mRecords;
};
} // namespace OHOS::Ace
#endif // ARKUI_PERF_MONITOR_H
