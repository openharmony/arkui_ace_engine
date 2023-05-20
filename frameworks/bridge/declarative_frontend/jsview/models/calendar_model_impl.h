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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_MODELS_CALENDAR_MODEL_IMPL_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_MODELS_CALENDAR_MODEL_IMPL_H

#include "core/components/calendar/calendar_component_v2.h"
#include "core/components_ng/pattern/calendar/calendar_model.h"

namespace OHOS::Ace::Framework {
class CalendarModelImpl : public OHOS::Ace::CalendarModel {
public:
    void Create(const CalendarModelData& calendarModelData) override;
    void SetOffDays(const std::string& offDays) override;
    void SetShowHoliday(const bool showHoliday) override;
    void SetShowLunar(const bool showLunar) override;
    void SetStartOfWeek(const int32_t startOfWeek) override;
    void SetNeedSlide(const bool needSlide) override;
    void SetSelectedChangeEvent(std::function<void(const std::string&)>&& selectedChangeEvent) override;
    void SetOnRequestDataEvent(std::function<void(const std::string&)>&& requestData) override;
    void SetDirection(const int32_t dir) override;
    void SetCurrentDayStyle(const CurrentDayStyleData& currentDayStyleData,
        const CurrentDayStyleData& CurrentDayStyleDataImpl) override;
    void SetNonCurrentDayStyle(const NonCurrentDayStyleData& nonCurrentDayStyleData) override;
    void SetTodayStyle(const TodayStyleData& style) override;
    void SetWeekStyle(const WeekStyleData& style) override;
    void SetWorkStateStyle(const WorkStateStyleData& style) override;

private:
    static RefPtr<CalendarComponentV2> GetComponent();
};
} // namespace OHOS::Ace::Framework
#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_MODELS_CALENDAR_MODEL_IMPL_H
