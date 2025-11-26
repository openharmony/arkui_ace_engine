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

#include "core/common/statistic_event_reporter.h"

#include "base/thread/task_executor.h"
#include "core/common/ace_application_info.h"
#include "core/common/statistic_event_adapter.h"
#include "core/pipeline/pipeline_base.h"

namespace OHOS::Ace {
namespace {
constexpr int32_t MAX_PENDING_EVENT_COUNT = 20;
}
StatisticEventReporter::StatisticEventReporter()
{
    appInfo_.bundleName = AceApplicationInfo::GetInstance().GetPackageName();
    appInfo_.abilityName = AceApplicationInfo::GetInstance().GetAbilityName();
    appInfo_.versionName = AceApplicationInfo::GetInstance().GetAppVersionName();
    appInfo_.versionCode = AceApplicationInfo::GetInstance().GetAppVersionCode();
}

std::string StatisticEventReporter::ConvertToEventName(StatisticEventType eventType)
{
    switch (eventType) {
        case StatisticEventType::FA_APP_START:
            return "FA_APP_START";
        default:
            return "";
    }
}

void StatisticEventReporter::SendEvent(StatisticEventType eventType)
{
    auto iter = statisitcEventMap_.find(eventType);
    if (iter == statisitcEventMap_.end()) {
        std::string eventName = ConvertToEventName(eventType);
        if (eventName == "") {
            return;
        }
        statisitcEventMap_[eventType] = { eventName, 1 };
    } else {
        iter->second.eventCount++;
    }
    totalEventCount_++;
}

void StatisticEventReporter::ReportStatisticEvents(const std::map<StatisticEventType, StatisticEventInfo>& events)
{
    StatisticEventAdapter::ReportStatisticEvents(appInfo_, events);
}

void StatisticEventReporter::TryReportStatisticEvents(PipelineBase* pipeline)
{
    CHECK_NULL_VOID(pipeline);
    if (totalEventCount_ < MAX_PENDING_EVENT_COUNT) {
        return;
    }
    auto executor = pipeline->GetTaskExecutor();
    CHECK_NULL_VOID(executor);
    std::map<StatisticEventType, StatisticEventInfo> statisitcEvents;
    std::swap(statisitcEvents, statisitcEventMap_);
    totalEventCount_ = 0;
    executor->PostTask(
        [statisitcEvents = std::move(statisitcEvents), reporter = shared_from_this()] () {
            if (reporter) {
                reporter->ReportStatisticEvents(statisitcEvents);
            }
        }, TaskExecutor::TaskType::BACKGROUND, "ReportStatisticEvents");
}

void StatisticEventReporter::ForceReportStatisticEvents()
{
    if (statisitcEventMap_.size() == 0) {
        return;
    }
    std::map<StatisticEventType, StatisticEventInfo> statisitcEvents;
    std::swap(statisitcEvents, statisitcEventMap_);
    totalEventCount_ = 0;
    ReportStatisticEvents(statisitcEvents);
}
} // namespace OHOS::Ace