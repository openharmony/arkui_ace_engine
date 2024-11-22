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
#include <vector>
#include <algorithm>
#include <memory>

#include "base/utils/macros.h"
#include "base/utils/aps_monitor.h"
#include "core/common/window_animation_config.h"

namespace OHOS::Ace {
constexpr int32_t US_TO_MS = 1000;
constexpr int32_t NS_TO_MS = 1000000;
constexpr int32_t NS_TO_S = 1000000000;
constexpr char DEFAULT_SCENE_ID[] = "NONE_ANIMATION";

enum PerfActionType {
    UNKNOWN_ACTION = -1,
    LAST_DOWN = 0,
    LAST_UP = 1,
    FIRST_MOVE = 2
};

enum PerfSourceType {
    UNKNOWN_SOURCE = -1,
    PERF_TOUCH_EVENT = 0,
    PERF_MOUSE_EVENT = 1,
    PERF_TOUCH_PAD = 2,
    PERF_JOY_STICK = 3,
    PERF_KEY_EVENT = 4
};

enum PerfEventType {
    UNKNOWN_EVENT = -1,
    EVENT_RESPONSE = 0,
    EVENT_COMPLETE = 1,
    EVENT_JANK_FRAME = 2
};

struct BaseInfo {
    int32_t pid {-1};
    int32_t versionCode {0};
    std::string versionName {""};
    std::string bundleName {""};
    std::string processName {""};
    std::string abilityName {""};
    std::string pageUrl {""};
    std::string pageName {""};
    std::string note {""};
};

struct DataBase {
    std::string sceneId {""};
    int32_t maxSuccessiveFrames {0};
    int32_t totalMissed {0};
    int32_t totalFrames {0};
    int64_t inputTime {0};
    int64_t beginVsyncTime {0};
    int64_t endVsyncTime {0};
    int64_t maxFrameTime {0};
    int64_t maxFrameTimeSinceStart {0};
    int64_t maxHitchTime {0};
    int64_t maxHitchTimeSinceStart {0};
    bool needReportRs {false};
    bool isDisplayAnimator {false};
    PerfSourceType sourceType {UNKNOWN_SOURCE};
    PerfActionType actionType {UNKNOWN_ACTION};
    PerfEventType eventType {UNKNOWN_EVENT};
    BaseInfo baseInfo;
};

struct JankInfo {
    int64_t skippedFrameTime {0};
    std::string windowName {""};
    std::string sceneId {""};
    int32_t filterType {0};
    BaseInfo baseInfo;
};

void ConvertRealtimeToSystime(int64_t realTime, int64_t& sysTime);
std::string GetSourceTypeName(PerfSourceType sourceType);
std::string ParsePageUrl(const std::string& pagePath);

class SceneRecord {
public:
    void InitRecord(const std::string& sId, PerfActionType aType, PerfSourceType sType, const std::string& nt,
        int64_t time);
    void RecordFrame(int64_t vsyncTime, int64_t duration, int32_t skippedFrames);
    void Report(const std::string& sceneId, int64_t vsyncTime, bool isRsRender);
    bool IsTimeOut(int64_t nowTime);
    bool IsFirstFrame();
    bool IsDisplayAnimator(const std::string& sceneId);
    void Reset();
public:
    int64_t inputTime {0};
    int64_t beginVsyncTime {0};
    int64_t endVsyncTime {0};
    int64_t  maxFrameTime {0};
    int64_t maxFrameTimeSinceStart {0};
    int64_t maxHitchTime {0};
    int64_t maxHitchTimeSinceStart {0};
    int32_t maxSuccessiveFrames {0};
    int32_t totalMissed {0};
    int32_t totalFrames {0};
    int32_t seqMissFrames {0};
    bool isSuccessive {false};
    bool isFirstFrame {false};
    bool needReportRs {false};
    bool isDisplayAnimator {false};
    std::string sceneId {""};
    PerfActionType actionType {UNKNOWN_ACTION};
    PerfSourceType sourceType {UNKNOWN_SOURCE};
    std::string note {""};
};

class ACE_FORCE_EXPORT PerfMonitor {
public:
    void Start(const std::string& sceneId, PerfActionType type, const std::string& note);
    void End(const std::string& sceneId, bool isRsRender);
    void RecordInputEvent(PerfActionType type, PerfSourceType sourceType, int64_t time);
    int64_t GetInputTime(const std::string& sceneId, PerfActionType type, const std::string& note);
    void SetFrameTime(int64_t vsyncTime, int64_t duration, double jank, const std::string& windowName);
    void ReportJankFrameApp(double jank);
    void SetPageUrl(const std::string& pageUrl);
    std::string GetPageUrl();
    void SetPageName(const std::string& pageName);
    std::string GetPageName();
    void SetAppForeground(bool isShow);
    void SetAppStartStatus();
    static PerfMonitor* GetPerfMonitor();
    static PerfMonitor* pMonitor;
    void SetApsMonitor(const std::shared_ptr<ApsMonitor>& apsMonitor);
    void ReportPageShowMsg(const std::string& pageUrl, const std::string& bundleName,
                           const std::string& pageName);
    void RecordWindowRectResize(OHOS::Ace::WindowSizeChangeReason reason,
                           const std::string& bundleName);

private:
    SceneRecord* GetRecord(const std::string& sceneId);
    void RemoveRecord(const std::string& sceneId);
    void ReportAnimateStart(const std::string& sceneId, SceneRecord* record);
    void ReportAnimateEnd(const std::string& sceneId, SceneRecord* record);
    void FlushDataBase(SceneRecord* record, DataBase& data);
    void ReportPerfEvent(PerfEventType type, DataBase& data);
    void RecordBaseInfo(SceneRecord* record);
    bool IsExceptResponseTime(int64_t time, const std::string& sceneId);
    int32_t GetFilterType() const;
private:
    std::shared_ptr<ApsMonitor> apsMonitor_ = nullptr;
    std::map<PerfActionType, int64_t> mInputTime;
    int64_t mVsyncTime {0};
    PerfSourceType mSourceType {UNKNOWN_SOURCE};
    BaseInfo baseInfo;
    mutable std::mutex mMutex;
    std::map<std::string, SceneRecord*> mRecords;

    // for jank frame app
    bool isResponseExclusion {false};
    bool isStartAppFrame {false};
    bool isBackgroundApp {false};
    bool isExclusionWindow {false};
    int64_t startAppTime {0};
    std::string currentSceneId {""};
    // filter common discarded frames in white list
    bool isExceptAnimator {false};
    bool IsSceneIdInSceneWhiteList(const std::string& sceneId);
    void CheckTimeOutOfExceptAnimatorStatus(const std::string& sceneId);
    bool IsExclusionFrame();
    void CheckInStartAppStatus();
    void CheckExclusionWindow(const std::string& windowName);
    void CheckResponseStatus();
    void ProcessJank(double jank, const std::string& windowName);
    void ReportJankFrame(double jank, const std::string& windowName);
};
} // namespace OHOS::Ace
#endif // ARKUI_PERF_MONITOR_H
