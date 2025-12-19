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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_STATISTIC_EVENT_REPORTRE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_STATISTIC_EVENT_REPORTRE_H

#include <map>
#include <memory>
#include <queue>
#include <string>

namespace OHOS::Ace {
class PipelineBase;
enum class StatisticEventType {
    FA_APP_START = 0,
    CALL_SET_CACHE_RANGE,
    TEXT_INPUT_ONWILLINSERT,
    TEXT_INPUT_ONDIDINSERT,
    TEXT_INPUT_ONWILLDELETE,
    TEXT_INPUT_ONDIDDELETE,
    TEXT_AREA_ONWILLINSERT,
    TEXT_AREA_ONDIDINSERT,
    TEXT_AREA_ONWILLDELETE,
    TEXT_AREA_ONDIDDELETE,
    SEARCH_ONWILLINSERT,
    SEARCH_ONDIDINSERT,
    SEARCH_ONWILLDELETE,
    SEARCH_ONDIDDELETE,
};

struct StatisticAppInfo {
    std::string bundleName;
};

struct StatisticEventInfo {
    std::string eventName;
    int32_t eventCount = 0;
};

class StatisticEventReporter : public std::enable_shared_from_this<StatisticEventReporter> {
public:
    StatisticEventReporter();
    ~StatisticEventReporter() = default;
    void SendEvent(StatisticEventType eventType);
    void TryReportStatisticEvents(PipelineBase* pipeline);
    void ForceReportStatisticEvents();
private:
    void ReportStatisticEvents(const std::map<StatisticEventType, StatisticEventInfo>& events);
    std::string ConvertToEventName(StatisticEventType eventType);
    int32_t totalEventCount_ = 0;
    StatisticAppInfo appInfo_;
    std::map<StatisticEventType, StatisticEventInfo> statisitcEventMap_;
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_STATISTIC_EVENT_REPORTRE_H