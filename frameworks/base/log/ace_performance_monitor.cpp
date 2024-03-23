/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include "base/log/ace_performance_monitor.h"

#include <cinttypes>

#include "base/log/ace_trace.h"
#include "base/utils/system_properties.h"

namespace OHOS::Ace {
using namespace std;
using namespace std::chrono;
ScopedMonitor::ScopedMonitor(MonitorTag tag) : tag_(tag)
{
    if (!SystemProperties::GetAcePerformanceMonitorEnabled()) {
        return;
    }
    begin_ = steady_clock::now();
    ArkUIPerfMonitor::GetInstance().SetRecordingStatus(tag_, MonitorStatus::RUNNING);
}

ScopedMonitor::~ScopedMonitor()
{
    if (!SystemProperties::GetAcePerformanceMonitorEnabled()) {
        return;
    }
    auto end = steady_clock::now();
    ArkUIPerfMonitor::GetInstance().RecordTimeSlice(tag_, duration_cast<nanoseconds>(end - begin_).count());
}

ArkUIPerfMonitor& ArkUIPerfMonitor::GetInstance()
{
    static ArkUIPerfMonitor instance;
    return instance;
}

ArkUIPerfMonitor::ArkUIPerfMonitor()
{
    InitPerfMonitor();
}

void ArkUIPerfMonitor::StartPerf()
{
    if (!SystemProperties::GetAcePerformanceMonitorEnabled()) {
        ClearPerfMonitor();
        return;
    }
    begin_ = steady_clock::now();
    ClearPerfMonitor();
}

void ArkUIPerfMonitor::FinishPerf()
{
    if (!SystemProperties::GetAcePerformanceMonitorEnabled()) {
        ClearPerfMonitor();
        return;
    }
    end_ = steady_clock::now();
    FlushPerfMonitor();
    ClearPerfMonitor();
}

void ArkUIPerfMonitor::RecordTimeSlice(MonitorTag tag, int64_t duration)
{
    SetRecordingStatus(tag, MonitorStatus::IDLE);
    if (tag == MonitorTag::STATIC_API) {
        if (!monitorStatus_) {
            return;
        }
        propertyNum_++;
    }
    timeSlice_[tag] += duration;
}

void ArkUIPerfMonitor::RecordNodeNum(uint64_t num)
{
    nodeNum_ += num;
}

void ArkUIPerfMonitor::SetRecordingStatus(MonitorTag tag, MonitorStatus status)
{
    if (tag == MonitorTag::STATIC_API) {
        return;
    }
    switch (status) {
        case MonitorStatus::RUNNING:
            ++monitorStatus_;
            break;
        case MonitorStatus::IDLE:
            --monitorStatus_;
            break;
    }
}

void ArkUIPerfMonitor::InitPerfMonitor()
{
    monitorStatus_ = 0;
    ClearPerfMonitor();
}

void ArkUIPerfMonitor::ClearPerfMonitor()
{
    timeSlice_[MonitorTag::COMPONENT_CREATION] = 0;
    timeSlice_[MonitorTag::COMPONENT_LIFECYCLE] = 0;
    timeSlice_[MonitorTag::COMPONENT_UPDATE] = 0;
    timeSlice_[MonitorTag::JS_CALLBACK] = 0;
    timeSlice_[MonitorTag::STATIC_API] = 0;
    propertyNum_ = 0;
    nodeNum_ = 0;
}

void ArkUIPerfMonitor::FlushPerfMonitor()
{
    auto total = static_cast<int64_t>(duration_cast<nanoseconds>(end_ - begin_).count());
    auto frameWork = total - timeSlice_[MonitorTag::COMPONENT_CREATION] - timeSlice_[MonitorTag::COMPONENT_LIFECYCLE] -
                     timeSlice_[MonitorTag::COMPONENT_UPDATE] - timeSlice_[MonitorTag::JS_CALLBACK] +
                     timeSlice_[MonitorTag::STATIC_API];
    ACE_SCOPED_TRACE("ArkUIPerfMonitor[%" PRIu64 ", %" PRIu64 " ,%" PRId64 ", %" PRId64 "]", nodeNum_, propertyNum_,
        total, frameWork);
}

} // namespace OHOS::Ace
