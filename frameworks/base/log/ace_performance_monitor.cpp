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

#include <sstream>

#include "base/json/json_util.h"
#include "base/log/ace_trace.h"
#include "core/common/container.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace {
using namespace std;
using namespace std::chrono;
namespace {
void GetTimePoint(TimePoint& now)
{
    if (SystemProperties::GetAcePerformanceMonitorEnabled()) {
        now = steady_clock::now();
    }
}
} // namespace

ScopedMonitor::ScopedMonitor(MonitorTag tag, int32_t instanceId) : tag_(tag), instanceId_(instanceId)
{
    if (instanceId == -1) {
        return;
    }
    GetTimePoint(begin_);
    ArkUIPerfMonitor::GetPerfMonitor(instanceId)->SetRecordingStatus(tag_, MonitorStatus::RUNNING);
}

ScopedMonitor::~ScopedMonitor()
{
    if (instanceId_ == -1) {
        return;
    }
    GetTimePoint(end_);
    ArkUIPerfMonitor::GetPerfMonitor(instanceId_)->RecordTimeSlice(
        tag_, duration_cast<nanoseconds>(end_ - begin_).count());
}

std::shared_ptr<ArkUIPerfMonitor> ArkUIPerfMonitor::GetPerfMonitor(int32_t instanceId)
{
    auto container = Container::GetContainer(instanceId);
    if (!container) {
        return std::make_shared<ArkUIPerfMonitor>();
    }
    auto pipeline = container->GetPipelineContext();
    if (!pipeline) {
        return std::make_shared<ArkUIPerfMonitor>();
    }
    return pipeline->GetPerfMonitor();
}

ArkUIPerfMonitor::ArkUIPerfMonitor()
{
    InitPerfMonitor();
}

void ArkUIPerfMonitor::StartPerf()
{
    GetTimePoint(begin_);
    ClearPerfMonitor();
}

void ArkUIPerfMonitor::FinishPerf()
{
    GetTimePoint(end_);
    FlushPerfMonitor();
    ClearPerfMonitor();
}

void ArkUIPerfMonitor::RecordTimeSlice(MonitorTag tag, int64_t duration)
{
    SetRecordingStatus(tag, MonitorStatus::IDLE);
    if (tag == MonitorTag::STATIC_API) {
        propertyNum_++;
        if (!monitorStatus_) {
            return;
        }
        timeSlice_[tag] += duration;
        return;
    }
    if (monitorStatus_ == 0) {
        timeSlice_[tag] += duration;
    }
}

void ArkUIPerfMonitor::RecordStateMgmtNode(int64_t num)
{
    stateMgmtNodeNum_ += num;
}

void ArkUIPerfMonitor::RecordLayoutNode(int64_t num)
{
    layoutNodeNum_ += num;
}

void ArkUIPerfMonitor::RecordRenderNode(int64_t num)
{
    renderNodeNum_ += num;
}

void ArkUIPerfMonitor::RecordDisplaySyncRate(int32_t displaySyncRate)
{
    displaySyncRate_ = displaySyncRate;
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
    timeSlice_[MonitorTag::OTHER] = 0;
    propertyNum_ = 0;
    stateMgmtNodeNum_ = 0;
    layoutNodeNum_ = 0;
    renderNodeNum_ = 0;
    displaySyncRate_ = 0;
}

void ArkUIPerfMonitor::FlushPerfMonitor()
{
    auto total = static_cast<int64_t>(duration_cast<nanoseconds>(end_ - begin_).count());
    auto frameWork = total - timeSlice_[MonitorTag::COMPONENT_CREATION] - timeSlice_[MonitorTag::COMPONENT_LIFECYCLE] -
                     timeSlice_[MonitorTag::COMPONENT_UPDATE] - timeSlice_[MonitorTag::JS_CALLBACK] +
                     timeSlice_[MonitorTag::STATIC_API] - timeSlice_[MonitorTag::OTHER];
#if ORIGIN_PERF_MONITOR
    auto json = JsonUtil::Create(true);
    json->Put("state_mgmt", stateMgmtNodeNum_);
    json->Put("layout", layoutNodeNum_);
    json->Put("render", renderNodeNum_);
    json->Put("property", propertyNum_);
    json->Put("total", total);
    json->Put("framework", frameWork);
    json->Put("display_sync_rate", displaySyncRate_);
    ACE_SCOPED_TRACE("ArkUIPerfMonitor %s", json->ToString().c_str());
#else
    std::ostringstream oss;
    oss << "{\'state_mgmt\':" << stateMgmtNodeNum_;
    oss << ",\'layout\':" << layoutNodeNum_;
    oss << ",\'render\':" << renderNodeNum_;
    oss << ",\'property\':" << propertyNum_;
    oss << ",\'total\':" << total;
    oss << ",\'framework\':" << frameWork;
    oss << ",\'display_sync_rate\':" << displaySyncRate_;
    oss << "}";
    ACE_SCOPED_TRACE("ArkUIPerfMonitor %s", oss.str().c_str());
#endif
}
} // namespace OHOS::Ace
