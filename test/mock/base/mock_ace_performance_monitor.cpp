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
    if (tag_ == MonitorTag::STATIC_API) {
        ArkUIPerfMonitor::GetInstance().RecordPropertyUpdate();
    }
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

void ArkUIPerfMonitor::RecordNodeNum(uint64_t num) {}

void ArkUIPerfMonitor::RecordPropertyUpdate() {}

void ArkUIPerfMonitor::InitPerfMonitor() {}

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

void ArkUIPerfMonitor::FlushPerfMonitor() {}

} // namespace OHOS::Ace
