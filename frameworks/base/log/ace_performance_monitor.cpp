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

namespace OHOS::Ace {
using namespace std;
using namespace std::chrono;
ScopedMonitor::ScopedMonitor(MonitorTag tag) : tag_(tag)
{
    begin_ = steady_clock::now();
    if (tag == MonitorTag::STATIC_API) {
        ArkUIPerfMonitor::GetInstance().RecordPropertyUpdate();
    }
}

ScopedMonitor::~ScopedMonitor()
{
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
    begin_ = steady_clock::now();
    ClearPerfMonitor();
}

void ArkUIPerfMonitor::FinishPerf()
{
    end_ = steady_clock::now();
    FlushPerfMonitor();
    ClearPerfMonitor();
}

void ArkUIPerfMonitor::RecordTimeSlice(MonitorTag tag, int64_t duration)
{
    timeSlice_[tag] += duration;
}

void ArkUIPerfMonitor::RecordNodeNum(uint64_t num)
{
    node_num_ += num;
}

void ArkUIPerfMonitor::RecordPropertyUpdate()
{
    property_++;
}

void ArkUIPerfMonitor::InitPerfMonitor()
{
    ClearPerfMonitor();
}

void ArkUIPerfMonitor::ClearPerfMonitor()
{
    timeSlice_[MonitorTag::COMPONENT_CREATION] = 0;
    timeSlice_[MonitorTag::COMPONENT_LIFECYCLE] = 0;
    timeSlice_[MonitorTag::COMPONENT_UPDATE] = 0;
    timeSlice_[MonitorTag::JS_CALLBACK] = 0;
    timeSlice_[MonitorTag::STATIC_API] = 0;
    property_ = 0;
    node_num_ = 0;
}

void ArkUIPerfMonitor::FlushPerfMonitor()
{
    auto total = static_cast<int64_t>(duration_cast<nanoseconds>(end_ - begin_).count());
    auto frameWork = total - timeSlice_[MonitorTag::COMPONENT_CREATION] - timeSlice_[MonitorTag::COMPONENT_LIFECYCLE] -
                     timeSlice_[MonitorTag::COMPONENT_UPDATE] - timeSlice_[MonitorTag::JS_CALLBACK] +
                     timeSlice_[MonitorTag::STATIC_API];
    ACE_SCOPED_TRACE(
        "ArkUIPerfMonitor[%" PRIu64 ", %" PRIu64 " ,%" PRId64 ", %" PRId64 "]", node_num_, property_, total, frameWork);
}

} // namespace OHOS::Ace