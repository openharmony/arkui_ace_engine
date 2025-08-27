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

#include "render_service_client/core/transaction/rs_interfaces.h"
#include "base/log/ace_trace.h"
#include "base/log/log_wrapper.h"
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

uint32_t GetJankRange(double jank)
{
    if (jank < 6.0f) {
        return JANK_FRAME_6_FREQ;
    }
    if (jank < 15.0f) {
        return JANK_FRAME_15_FREQ;
    }
    if (jank < 20.0f) {
        return JANK_FRAME_20_FREQ;
    }
    if (jank < 36.0f) {
        return JANK_FRAME_36_FREQ;
    }
    if (jank < 48.0f) {
        return JANK_FRAME_48_FREQ;
    }
    if (jank < 60.0f) {
        return JANK_FRAME_60_FREQ;
    }
    if (jank < 120.0f) {
        return JANK_FRAME_120_FREQ;
    }
    return JANK_FRAME_180_FREQ;
}

int64_t GetCurrentRealTimeNs()
{
    struct timespec ts = { 0, 0 };
    if (clock_gettime(CLOCK_MONOTONIC, &ts) != 0) {
        return 0;
    }
    return (ts.tv_sec * NS_TO_S + ts.tv_nsec);
}

void ClockTimeCalibration(int64_t &now)
{
    int64_t realTime = GetCurrentRealTimeNs();
    if (now - realTime >= NS_TO_MS || realTime - now >= NS_TO_MS) {
        ACE_SCOPED_TRACE("ClockTimeCalibration realTime = %ld, now = %ld",
            static_cast<long>(realTime), static_cast<long>(now));
        now = realTime;
    }
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

JankFrameReport& JankFrameReport::GetInstance()
{
    static thread_local JankFrameReport instance;
    return instance;
}

JankFrameReport::JankFrameReport()
{
    frameJankRecord_ = std::vector<uint16_t>(JANK_SIZE, 0);
    jankFrameCount_ = 0;
    prevFrameUpdateCount_ = 0;
    currentFrameUpdateCount_ = 0;
    recordStatus_ = JANK_IDLE;
    startTime_ = 0;
    prevEndTimeStamp_ = 0;
    refreshPeriod_ = 16666666;
    needReport_ = false;
    hasJsAnimation_ = false;
    animatorEndTime_ = 0;
    jsAnimationDelayJank_ = 0;
}

void JankFrameReport::JankFrameRecord(int64_t timeStampNanos, const std::string& windowName)
{
    if (refreshPeriod_ <= 0) {
        return;
    }
    int64_t now = GetSteadyTimestamp<std::chrono::nanoseconds>();
    ClockTimeCalibration(now);
    int64_t durationTmp = now - std::max(timeStampNanos, prevEndTimeStamp_);
    int64_t duration = (now <= timeStampNanos) ? 0 : durationTmp;
    double jank = double(duration) / refreshPeriod_;
    // perf monitor jank frame
    PerfMonitor::GetPerfMonitor()->SetFrameTime(timeStampNanos, duration, jank, windowName);
    RecordJankStatus(jank);
    prevFrameUpdateCount_ = currentFrameUpdateCount_;
    RecordPreviousEnd();
}

void JankFrameReport::JsAnimationToRsRecord()
{
    int64_t now = GetSteadyTimestamp<std::chrono::nanoseconds>();
    if (hasJsAnimation_ && animatorEndTime_ != 0) {
        int64_t jsAnimationDuration = now - animatorEndTime_;
        jsAnimationDelayJank_ = double(jsAnimationDuration) / refreshPeriod_;
    }
}

void JankFrameReport::RecordJankStatus(double jank)
{
    if (recordStatus_ == JANK_IDLE && animatorEndTime_ == 0) {
        return;
    }
    if (animatorEndTime_ != 0) {
        hasJsAnimation_ = false;
        animatorEndTime_ = 0;
        jsAnimationDelayJank_ = 0;
    }
    // on need to record
    if (jank <= 1.0f) {
        return;
    }
    // skip first frame
    if (prevFrameUpdateCount_ == 0 && (currentFrameUpdateCount_ >= 0)) {
        return;
    };
    needReport_ = true;
    frameJankRecord_[GetJankRange(jank)]++;
    if (jank >= 6.0f) {
        jankFrameCount_++;
        ACE_SCOPED_TRACE("JANK_STATS_APP skippedTime=%lld(ms)",
            static_cast<long long>(jank * refreshPeriod_ / NS_TO_MS));
        ACE_COUNT_TRACE(jankFrameCount_, "JANK FRAME %s", pageUrl_.c_str());
    }
    PerfMonitor::GetPerfMonitor()->ReportJankFrameApp(jank);
}

void JankFrameReport::RecordPreviousEnd()
{
    prevEndTimeStamp_ = GetSteadyTimestamp<std::chrono::nanoseconds>();
}

void JankFrameReport::ClearFrameJankRecord()
{
    std::fill(frameJankRecord_.begin(), frameJankRecord_.end(), 0);
    jankFrameCount_ = 0;
    recordStatus_ = JANK_IDLE;
    currentFrameUpdateCount_ = 0;
    needReport_ = false;
    hasJsAnimation_ = false;
    jsAnimationDelayJank_ = 0;
    animatorEndTime_ = 0;
}

void JankFrameReport::SetFrameJankFlag(JankFrameFlag flag)
{
    recordStatus_++;
    if (recordStatus_ == 1) {
        animatorEndTime_ = 0;
        hasJsAnimation_ = false;
    }
}

void JankFrameReport::ClearFrameJankFlag(JankFrameFlag flag)
{
    if (recordStatus_ > 0) {
        if (recordStatus_ == 1) {
            animatorEndTime_ = GetSteadyTimestamp<std::chrono::nanoseconds>();
        }
        recordStatus_--;
    }
    if (recordStatus_ == JANK_IDLE) {
        currentFrameUpdateCount_ = 0;
    }
}

void JankFrameReport::RecordFrameUpdate()
{
    currentFrameUpdateCount_++;
}

void JankFrameReport::ResetFrameJankClock()
{
    startTime_ = GetSystemTimestamp<std::chrono::milliseconds>();
    SteadyTimeRecorder::Begin();
}

void JankFrameReport::StartRecord(const std::string& pageUrl)
{
    ResetFrameJankClock();
    pageUrl_ = ParsePageUrl(pageUrl);
}

void JankFrameReport::FlushRecord()
{
    Rosen::RSInterfaces::GetInstance().ReportJankStats();
    if (needReport_) {
        LOGI("%{public}s", std::string("jank report,pageUrl:")
                               .append(pageUrl_)
                               .append(",startTime:")
                               .append(std::to_string(startTime_))
                               .append("duration:")
                               .append(std::to_string(SteadyTimeRecorder::End()))
                               .c_str());
        EventReport::JankFrameReport(startTime_, SteadyTimeRecorder::End(), frameJankRecord_, pageUrl_);
    }
    ClearFrameJankRecord();
}

void JankFrameReport::ReportJSAnimation()
{
    if (animatorEndTime_ != 0) {
        hasJsAnimation_ = true;
    }
}

void JankFrameReport::RecordAnimateEnd()
{
    prevEndTimeStamp_ = GetSteadyTimestamp<std::chrono::nanoseconds>();
}
} // namespace OHOS::Ace
