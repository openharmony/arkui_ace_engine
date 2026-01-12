/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "common_statistic_event.h"

#include "hisysevent.h"
#include "ui_service_hilog.h"

namespace OHOS {
namespace Ace {
namespace {
constexpr int32_t MAX_PENDING_EVENT_COUNT = 50;
const char* EVENT_NAME = "EVENT_NAME";
const char* EVENT_COUNT = "EVENT_COUNT";
const char* BUNDLE_NAME = "BUNDLE_NAME";
}
std::string& StatisticEvent::GetEventName()
{
    return eventName_;
}

void StatisticEvent::SetReportInterval(int32_t reportInterval)
{
    reportInterval_ = reportInterval;
}

int32_t StatisticEvent::GetReportInterval() const
{
    return reportInterval_;
}

void StatisticEvent::ReportEvent()
{
    LOGD("ReportCommonStatistiEvent eventName: %{public}s", eventName_.c_str());
    HiSysEventWrite(OHOS::HiviewDFX::HiSysEvent::Domain::ACE, "UI_STATISTIC_EVENT",
        OHOS::HiviewDFX::HiSysEvent::EventType::STATISTIC,
        EVENT_NAME, eventName_,
        EVENT_COUNT, eventCounts_,
        BUNDLE_NAME, extraInfos_);
}

bool StatisticEvent::AggregateEvent(const AppInfoParcel& newAppInfo, const StatisticEventInfoParcel& newEventInfo)
{
    bool isReported = false;
    std::string newExtraInfo = newEventInfo.GetSubEventName() + "|" +  newAppInfo.GetBundleName();
    for (size_t i = 0; i < extraInfos_.size(); ++i) {
        if (extraInfos_[i] != newExtraInfo) {
            continue;
        }
        eventCounts_[i] += newEventInfo.GetEventCount();
        return isReported;
    }
    extraInfos_.push_back(newExtraInfo);
    eventCounts_.push_back(newEventInfo.GetEventCount());
    if (extraInfos_.size() >= MAX_PENDING_EVENT_COUNT) {
        ReportEvent();
        isReported = true;
    }
    return isReported;
}
} // namespace Ace
} // namespace OHOS