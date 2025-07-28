/*
 * Copyright (c) 2021-2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_BASE_RESSCHED_RESSCHED_REPORT_H
#define FOUNDATION_ACE_FRAMEWORKS_BASE_RESSCHED_RESSCHED_REPORT_H

#include <chrono>
#include <string>
#include <unordered_map>

#include "base/utils/macros.h"
#include "base/utils/noncopyable.h"
#include "core/event/touch_event.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "base/geometry/offset.h"
#include "core/event/axis_event.h"

namespace OHOS::Ace {
namespace ResDefine {
constexpr int32_t LOAD_PAGE_START_EVENT = 0;
constexpr int32_t LOAD_PAGE_COMPLETE_EVENT = 1;
constexpr int32_t LOAD_PAGE_NO_REQUEST_FRAME_EVENT = 2;
constexpr double JUDGE_DISTANCE = 3.125;
constexpr int64_t INVALID_DATA = -1;
}

struct ResEventInfo {
    TimeStamp timeStamp;
    Offset offset;
    SourceTool sourceTool = SourceTool::UNKNOWN;
};

struct ReportConfig {
    bool isReportTid = false;
    uint64_t tid = 0;
};

using ReportDataFunc = void (*)(uint32_t resType, int64_t value,
    const std::unordered_map<std::string, std::string>& payload);

using ReportSyncEventFunc = int32_t (*)(const uint32_t resType, const int64_t value,
    const std::unordered_map<std::string, std::string>& payload, std::unordered_map<std::string, std::string>& reply);

ReportDataFunc ACE_EXPORT LoadReportDataFunc();
ReportSyncEventFunc ACE_EXPORT LoadReportSyncEventFunc();

class ACE_EXPORT ResSchedReport final {
public:
    static ResSchedReport& GetInstance();
    void ResSchedDataReport(const char* name, const std::unordered_map<std::string, std::string>& param = {},
        int64_t tid = ResDefine::INVALID_DATA);
    void TriggerModuleSerializer();
    void ResSchedDataReport(uint32_t resType, int32_t value = 0,
        const std::unordered_map<std::string, std::string>& payload = {});
    void ResScheSyncEventReport(const uint32_t resType, const int64_t value,
        const std::unordered_map<std::string, std::string>& payload,
        std::unordered_map<std::string, std::string>& reply);
    bool AppWhiteListCheck(const std::unordered_map<std::string, std::string>& payload,
        std::unordered_map<std::string, std::string>& reply);
    void OnTouchEvent(const TouchEvent& touchEvent, const ReportConfig& config);
    void OnKeyEvent(const KeyEvent& event);
    void LoadPageEvent(int32_t value);
    void OnAxisEvent(const AxisEvent& axisEvent);
    void AxisEventReportEnd();
    void HandlePageTransition(const std::string& fromPage, const std::string& toPage, const std::string& mode);
    static std::atomic<int32_t> createPageCount; // not consider multi-instances.
    static bool triggerExecuted; // not consider multi-instances.
    int64_t GetTid();
    int64_t GetPid();
    pthread_t GetPthreadSelf();

private:
    ResSchedReport();
    ~ResSchedReport() {}
    void HandleTouchDown(const TouchEvent& touchEvent, const ReportConfig& config);
    void HandleTouchUp(const TouchEvent& touchEvent, const ReportConfig& config);
    bool IsRateLimit(int64_t maxCount, std::chrono::seconds durTime,
        int64_t& keyEventCount, std::chrono::steady_clock::time_point& startTime);
    bool IsPerSecRateLimit();
    bool IsPerMinRateLimit();
    void HandleKeyDown(const KeyEvent& event);
    void HandleKeyUp(const KeyEvent& event);
    void HandleTouchMove(const TouchEvent& touchEvent, const ReportConfig& config);
    void HandleTouchCancel(const TouchEvent& touchEvent, const ReportConfig& config);
    void HandleTouchPullDown(const TouchEvent& touchEvent, const ReportConfig& config);
    void HandleTouchPullUp(const TouchEvent& touchEvent, const ReportConfig& config);
    void HandleTouchPullMove(const TouchEvent& touchEvent, const ReportConfig& config);
    double GetUpVelocity(const ResEventInfo& lastMoveInfo,
        const ResEventInfo& upEventInfo);
    void RecordTouchEvent(const TouchEvent& touchEvent, bool enforce = false);

    void HandleAxisBegin(const AxisEvent& axisEvent);
    void HandleAxisUpdate(const AxisEvent& axisEvent);
    void HandleAxisEnd(const AxisEvent& axisEvent);

    void RecordAxisEvent(const AxisEvent& axisEvent, bool enforce = false);
    double GetAxisUpVelocity(const ResEventInfo& lastAxisEvent, const ResEventInfo& curAxisEvent);

    ReportDataFunc reportDataFunc_ = nullptr;
    ReportSyncEventFunc reportSyncEventFunc_ = nullptr;
    CancelableCallback<void()> delayTask_;
    bool loadPageOn_ = false;
    bool loadPageRequestFrameOn_ = false;
    ResEventInfo curTouchEvent_;
    ResEventInfo lastTouchEvent_;
    ResEventInfo curAxisEvent_;
    ResEventInfo lastAxisEvent_;
    static thread_local Offset averageDistance_;
    static thread_local bool isInSlide_;
    static thread_local bool isInTouch_;
    double dpi_ = PipelineBase::GetCurrentDensity();
    std::chrono::steady_clock::time_point startTimeMS = std::chrono::steady_clock::now();
    std::chrono::steady_clock::time_point startTimeS = std::chrono::steady_clock::now();
    int64_t keyEventCountMS = -1;
    int64_t keyEventCountS = -1;
};

class ACE_EXPORT ResSchedReportScope final {
public:
    ACE_DISALLOW_COPY_AND_MOVE(ResSchedReportScope);

    explicit ResSchedReportScope(const std::string& name,
        const std::unordered_map<std::string, std::string>& param = {});
    ~ResSchedReportScope();

private:
    std::string name_;
    std::unordered_map<std::string, std::string> payload_;
};
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_BASE_RESSCHED_RESSCHED_REPORT_H
