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

namespace OHOS::Ace {
using namespace std::chrono;
ScopedMonitor::ScopedMonitor(MonitorTag tag) : tag_(tag)
{
    begin_ = steady_clock::now();
    end_ = steady_clock::now();
    ArkUIPerfMonitor::GetInstance().SetRecordingStatus(tag_, MonitorStatus::RUNNING);
}

ScopedMonitor::~ScopedMonitor() = default;

ArkUIPerfMonitor& ArkUIPerfMonitor::GetInstance()
{
    static ArkUIPerfMonitor instance;
    return instance;
}

ArkUIPerfMonitor::ArkUIPerfMonitor() {}

void ArkUIPerfMonitor::StartPerf() {}

void ArkUIPerfMonitor::FinishPerf() {}

void ArkUIPerfMonitor::RecordTimeSlice(MonitorTag tag, int64_t duration) {}

void ArkUIPerfMonitor::RecordStateMgmtNode(int64_t num) {}

void ArkUIPerfMonitor::RecordLayoutNode(int64_t num) {}

void ArkUIPerfMonitor::RecordRenderNode(int64_t num) {}

void ArkUIPerfMonitor::RecordDisplaySyncRate(int32_t displaySyncRate) {}

void ArkUIPerfMonitor::SetRecordingStatus(MonitorTag tag, MonitorStatus status) {}

void ArkUIPerfMonitor::InitPerfMonitor() {}

void ArkUIPerfMonitor::ClearPerfMonitor()
{
    timeSlice_[MonitorTag::COMPONENT_CREATION] = 0;
    timeSlice_[MonitorTag::COMPONENT_LIFECYCLE] = 0;
    timeSlice_[MonitorTag::COMPONENT_UPDATE] = 0;
    timeSlice_[MonitorTag::JS_CALLBACK] = 0;
    timeSlice_[MonitorTag::STATIC_API] = 0;
    propertyNum_ = 0;
    stateMgmtNodeNum_ = 0;
    layoutNodeNum_ = 0;
    renderNodeNum_ = 0;
    monitorStatus_ = 0;
}

void ArkUIPerfMonitor::FlushPerfMonitor() {}

} // namespace OHOS::Ace
