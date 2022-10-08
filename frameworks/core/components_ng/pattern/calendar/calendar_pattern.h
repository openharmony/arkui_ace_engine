/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_CALENDAR_CALENDAR_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_CALENDAR_CALENDAR_PATTERN_H

#include <cstdint>
#include <optional>

#include "base/memory/referenced.h"
#include "core/components/calendar/calendar_data_adapter.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/calendar/calendar_controller_ng.h"
#include "core/components_ng/pattern/calendar/calendar_event_hub.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/swiper/swiper_event_hub.h"

namespace OHOS::Ace::NG {

class CalendarPattern : public Pattern {
    DECLARE_ACE_TYPE(CalendarPattern, Pattern);

public:
    CalendarPattern() = default;
    ~CalendarPattern() override = default;

    RefPtr<EventHub> CreateEventHub() override
    {
        return MakeRefPtr<CalendarEventHub>();
    }

    bool IsAtomicNode() const override
    {
        return false;
    }

    ObtainedMonth GetCurrentMonthData() const
    {
        return currentMonth_;
    }

    void SetCurrentMonthData(const ObtainedMonth& currentData)
    {
        currentMonth_ = currentData;
    }

    ObtainedMonth GetPreMonthData() const
    {
        return preMonth_;
    }

    void SetPreMonthData(const ObtainedMonth& preData)
    {
        preMonth_ = preData;
    }

    ObtainedMonth GetNextMonthData() const
    {
        return nextMonth_;
    }

    void SetNextMonthData(const ObtainedMonth& nextData)
    {
        nextMonth_ = nextData;
    }

    CalendarDay GetCalendarDay() const
    {
        return calendarDay_;
    }

    void SetCalendarDay(const CalendarDay& calendarDay)
    {
        calendarDay_ = calendarDay;
    }

    void SetMoveDirection(NG::Direction moveDirection)
    {
        moveDirection_ = moveDirection;
    }

    NG::Direction GetMoveDirection()
    {
        return moveDirection_;
    }

    void SetBackToToday(bool backToToday)
    {
        backToToday_ = backToToday;
    }

    void SetGoTo(bool goTo)
    {
        goTo_ = goTo;
    }

    RefPtr<CalendarControllerNg> GetCalendarControllerNg() const
    {
        return calendarControllerNg_;
    }

    void SetCalendarControllerNg(const RefPtr<CalendarControllerNg>& calendarController);

    void FireFirstRequestData();
    void FireGoToRequestData(int32_t year, int32_t month, int32_t day);

private:
    void OnAttachToFrameNode() override;
    bool OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, bool skipMeasure, bool skipLayout) override;
    void OnModifyDone() override;
    void FireRequestData(MonthState monthState);
    void JumpTo(const RefPtr<FrameNode>& preFrameNode, const RefPtr<FrameNode>& curFrameNode,
        const RefPtr<FrameNode>& nextFrameNode, const RefPtr<FrameNode>& swiperFrameNode);

    RefPtr<CalendarControllerNg> calendarControllerNg_;
    CalendarDay calendarDay_;
    int32_t goToCalendarDay_;
    ObtainedMonth currentMonth_;
    ObtainedMonth preMonth_;
    ObtainedMonth nextMonth_;
    NG::Direction moveDirection_;
    bool initialize_ = true;
    bool backToToday_ = false;
    bool goTo_ = false;
    ACE_DISALLOW_COPY_AND_MOVE(CalendarPattern);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_CALENDAR_CALENDAR_PATTERN_H
