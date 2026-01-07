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

#ifndef OHOS_ACE_UI_SERVICE_COMMON_STATISTIC_EVENT_H
#define OHOS_ACE_UI_SERVICE_COMMON_STATISTIC_EVENT_H

#include "ui_service_statistic_event.h"

namespace OHOS {
namespace Ace {
class StatisticEvent {
public:
    explicit StatisticEvent(const std::string& eventName): eventName_(eventName) {};
    ~StatisticEvent() = default;
    void SetReportInterval(int32_t reportInterval);
    std::string& GetEventName();
    int32_t GetReportInterval() const;
    virtual void ReportEvent();
    virtual bool AggregateEvent(const AppInfoParcel& newAppInfo, const StatisticEventInfoParcel& newEventInfo);
private:
    int32_t reportInterval_ = 0;
    std::string eventName_;
    std::vector<int32_t> eventCounts_;
    std::vector<std::string> extraInfos_;
};
}  // namespace Ace
}  // namespace OHOS
#endif  // OHOS_ACE_UI_SERVICE_COMMON_STATISTIC_EVENT_H