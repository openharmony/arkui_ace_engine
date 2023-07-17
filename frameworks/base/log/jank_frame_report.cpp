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

#include "base/log/jank_frame_report.h"

#include <chrono>

#include "render_service_client/core/transaction/rs_interfaces.h"

#include "base/perfmonitor/perf_monitor.h"
#include "base/log/event_report.h"

namespace OHOS::Ace {
namespace {
constexpr uint32_t JANK_FRAME_6_FREQ = 0;
constexpr uint32_t JANK_FRAME_15_FREQ = 1;
constexpr uint32_t JANK_FRAME_20_FREQ = 2;
constexpr uint32_t JANK_FRAME_36_FREQ = 3;
constexpr uint32_t JANK_FRAME_48_FREQ = 4;
constexpr uint32_t JANK_FRAME_60_FREQ = 5;
constexpr uint32_t JANK_FRAME_120_FREQ = 6;
constexpr uint32_t JANK_FRAME_180_FREQ = 7;
constexpr uint32_t JANK_SIZE = 8;

using namespace std;
using namespace std::chrono;

template<class T>
int64_t GetSystemTimestamp()
{
    return duration_cast<T>(system_clock::now().time_since_epoch()).count();
}

template<class T>
int64_t GetSteadyTimestamp()
{
    return duration_cast<T>(steady_clock::now().time_since_epoch()).count();
}

class SteadyTimeRecorder {
public:
    static steady_clock::time_point begin;
    static void Begin()
    {
        begin = steady_clock::now();
    }
    static int64_t End()
    {
        auto end = steady_clock::now();
        return duration_cast<milliseconds>(end - begin).count();
    }
};

steady_clock::time_point SteadyTimeRecorder::begin {};
} // namespace

std::vector<uint16_t> JankFrameReport::frameJankRecord_(JANK_SIZE, 0);
JankFrameFlag JankFrameReport::recordStatus_ = JANK_IDLE;
int64_t JankFrameReport::startTime_ = 0;
int64_t JankFrameReport::prevEndTimeStamp_ = 0;
int64_t JankFrameReport::refreshPeriod_ = 0;
std::string JankFrameReport::pageUrl_;
bool JankFrameReport::needReport_ = false;

void JankFrameReport::JankFrameRecord(int64_t timeStampNanos)
{
    if (refreshPeriod_ <= 0) {
        return;
    }
    int64_t now = GetSteadyTimestamp<std::chrono::nanoseconds>();
    int64_t duration = now - std::max(timeStampNanos, prevEndTimeStamp_);
    double jank = double(duration) / refreshPeriod_;
    // perf monitor jank frame
    PerfMonitor::GetPerfMonitor()->SetFrameTime(timeStampNanos, duration, jank);
    if (jank <= 1.0f || recordStatus_ == JANK_IDLE) {
        return;
    }
    needReport_ = true;
    if (jank < 6.0f) {
        frameJankRecord_[JANK_FRAME_6_FREQ]++;
        return;
    }
    if (jank < 15.0f) {
        frameJankRecord_[JANK_FRAME_15_FREQ]++;
        return;
    }
    if (jank < 20.0f) {
        frameJankRecord_[JANK_FRAME_20_FREQ]++;
        return;
    }
    if (jank < 36.0f) {
        frameJankRecord_[JANK_FRAME_36_FREQ]++;
        return;
    }
    if (jank < 48.0f) {
        frameJankRecord_[JANK_FRAME_48_FREQ]++;
        return;
    }
    if (jank < 60.0f) {
        frameJankRecord_[JANK_FRAME_60_FREQ]++;
        return;
    }
    if (jank < 120.0f) {
        frameJankRecord_[JANK_FRAME_120_FREQ]++;
        return;
    }
    frameJankRecord_[JANK_FRAME_180_FREQ]++;
}

void JankFrameReport::SetRefreshPeriod(int64_t refreshPeriod)
{
    refreshPeriod_ = refreshPeriod;
}

void JankFrameReport::RecordPreviousEnd()
{
    prevEndTimeStamp_ = GetSteadyTimestamp<std::chrono::nanoseconds>();
}

void JankFrameReport::ClearFrameJankRecord()
{
    std::fill(frameJankRecord_.begin(), frameJankRecord_.end(), 0);
    recordStatus_ = JANK_IDLE;
    needReport_ = false;
}

void JankFrameReport::SetFrameJankFlag(JankFrameFlag flag)
{
    recordStatus_++;
}

void JankFrameReport::ClearFrameJankFlag(JankFrameFlag flag)
{
    if (recordStatus_ > 0) {
        recordStatus_--;
    }
}

void JankFrameReport::ResetFrameJankClock()
{
    startTime_ = GetSystemTimestamp<std::chrono::milliseconds>();
    SteadyTimeRecorder::Begin();
}

void JankFrameReport::StartRecord(const std::string& pageUrl)
{
    if (startTime_ == 0) {
        ResetFrameJankClock();
    }
    pageUrl_ = pageUrl;
}

void JankFrameReport::FlushRecord()
{
    Rosen::RSInterfaces::GetInstance().ReportJankStats();
    if (needReport_) {
        EventReport::JankFrameReport(startTime_, SteadyTimeRecorder::End(), frameJankRecord_, pageUrl_);
    }
    ClearFrameJankRecord();
    ResetFrameJankClock();
}
} // namespace OHOS::Ace
