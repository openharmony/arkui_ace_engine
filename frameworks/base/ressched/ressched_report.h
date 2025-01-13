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
}

using ReportDataFunc = void (*)(uint32_t resType, int64_t value,
    const std::unordered_map<std::string, std::string>& payload);

ReportDataFunc ACE_EXPORT LoadReportDataFunc();

class ACE_EXPORT ResSchedReport final {
public:
    static ResSchedReport& GetInstance();
    void ResSchedDataReport(const char* name, const std::unordered_map<std::string, std::string>& param = {});
    void ResSchedDataReport(uint32_t resType, int32_t value = 0,
        const std::unordered_map<std::string, std::string>& payload = {});
    void OnTouchEvent(const TouchEvent& touchEvent);
    void OnKeyEvent(const KeyEvent& event);
    void LoadPageEvent(int32_t value);
    void OnAxisEvent(const AxisEvent& axisEvent);
    void AxisEventReportEnd();

private:
    ResSchedReport() {}
    ~ResSchedReport() {}
    void HandleTouchDown(const TouchEvent& touchEvent);
    void HandleTouchUp(const TouchEvent& touchEvent);
    bool IsRateLimit(int64_t maxCount, std::chrono::seconds durTime,
        int64_t& keyEventCount, std::chrono::steady_clock::time_point& startTime);
    bool IsPerSecRateLimit();
    bool IsPerMinRateLimit();
    void HandleKeyDown(const KeyEvent& event);
    void HandleKeyUp(const KeyEvent& event);
    void HandleTouchMove(const TouchEvent& touchEvent);
    void HandleTouchCancel(const TouchEvent& touchEvent);
    void HandleTouchPullDown(const TouchEvent& touchEvent);
    void HandleTouchPullUp(const TouchEvent& touchEvent);
    void HandleTouchPullMove(const TouchEvent& touchEvent);
    double GetUpVelocity(const TouchEvent& lastMoveInfo,
        const TouchEvent& upEventInfo);
    void RecordTouchEvent(const TouchEvent& touchEvent, bool enforce = false);

    void HandleAxisBegin(const AxisEvent& axisEvent);
    void HandleAxisUpdate(const AxisEvent& axisEvent);
    void HandleAxisEnd(const AxisEvent& axisEvent);

    void RecordAxisEvent(const AxisEvent& axisEvent, bool enforce = false);
    double GetAxisUpVelocity(const AxisEvent& lastAxisEvent, const AxisEvent& curAxisEvent);

    ReportDataFunc reportDataFunc_ = nullptr;
    bool loadPageOn_ = false;
    bool loadPageRequestFrameOn_ = false;
    TouchEvent curTouchEvent_;
    TouchEvent lastTouchEvent_;
    AxisEvent curAxisEvent_;
    AxisEvent lastAxisEvent_;
    Offset averageDistance_;
    bool isInSlide_ = false;
    bool isInTouch_ = false;
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
